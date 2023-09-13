// Tower Kit documentation https://tower.hardwario.com/
// SDK API description https://sdk.hardwario.com/
// Forum https://forum.hardwario.com/

#include <application.h>
#include "icons.h"

// info screen structure
typedef struct {
    const uint8_t *icon;
    const char *title;
    void (*render)(bool redraw, void *param);
    void *param;
} info_screen_t;

// Pointer to GFX instance
twr_gfx_t *pgfx;
twr_gfx_caps_t gfx_caps;

// LED instance
twr_led_t led;
twr_led_t lcdLed[3];

// Button instance
// twr_button_t button;

// Thermometer instance
twr_tmp112_t tmp112;

// Runtime variables
float temperature = 0.0f;
float battery_level = 1.0f;
float battery_voltage = 0.0f;
bool battery_present = false;

float progress[2] = {1.0, 1.0};

uint32_t time_offset = 50;
twr_tick_t last_update = 0;

const twr_font_t *font_time = &twr_font_ubuntu_13;
const uint8_t render_time_height = 13;
uint16_t render_time_width = 0;

void render_screen(int screen, bool redraw);
void render_info_screen_dashboard(bool redraw, void *param);
void render_info_screen_device(bool redraw, void *param);

info_screen_t screens[] = {
    {icon24_dashboard, "Prehled", render_info_screen_dashboard, NULL},
    {icon24_thermometer_sun, "Meteo", NULL, NULL},
    {icon24_thermometer_home, "Vnitrni", NULL, NULL},
    {icon24_photovoltaics_current, "FVE aktualne", NULL, NULL},
    {icon24_photovoltaics_cumulative, "FVE statistiky", NULL, NULL},
    {icon24_hardwario, "Zarizeni", render_info_screen_device, NULL},
};
int screen = 0;
const int screens_count = sizeof(screens) / sizeof(screens[0]);
bool screen_locked = false;
bool screen_auto = false;
#define SCREEN_TIMEOUT_HOME 30*1000
#define SCREEN_TIMEOUT_AUTO 10*1000
twr_tick_t screen_timeout = SCREEN_TIMEOUT_HOME;
twr_tick_t screen_timestamp = 0;


void update_progress(int loc, float value);

void tmp112_event_handler(twr_tmp112_t *self, twr_tmp112_event_t event, void *event_param)
{
    if (event == TWR_TMP112_EVENT_UPDATE)
    {
        float celsius;
        // Read temperature
        twr_tmp112_get_temperature_celsius(self, &celsius);

        twr_log_debug("APP: temperature: %.2f °C", celsius);

        twr_radio_pub_temperature(TWR_RADIO_PUB_CHANNEL_R1_I2C0_ADDRESS_ALTERNATE, &celsius);
        temperature = celsius;
    }
}

// set LED mode with specified color
// color is bitmap of RGB bits (0x01 = red, 0x02 = green, 0x04 = blue)
void led_mode_rgb(int color, twr_led_mode_t mode) {
    for (int i = 0; i < 3; i++) {
        twr_led_set_mode(&lcdLed[i], (color & (1 << i)) ? mode : TWR_LED_MODE_OFF);
    }
}

// pulse LED with specified color
// color is bitmap of RGB bits (0x01 = red, 0x02 = green, 0x04 = blue)
void led_pulse_rgb(int color, int duration) {
    for (int i = 0; i < 3; i++) {
        if (color & (1 << i))
            twr_led_pulse(&lcdLed[i], duration);
    }
}

// change screen
void screen_change(int new_screen) {
    if (new_screen < 0) new_screen = screens_count - 1;
    if (new_screen >= screens_count) new_screen = 0;
    screen = new_screen;
    if (screen_locked) screen_locked = false;
    if ((!screen_locked && screen > 0) || screen_auto) {
        screen_timestamp = twr_tick_get();
        update_progress(1, 0.0);
    } else {
        update_progress(1, 1.0);
    }
    render_screen(screen, true);
}

void screen_auto_toggle(void) {
    screen_auto = !screen_auto;
    screen_timestamp = twr_tick_get();
    screen_locked = false;
    screen_timeout = screen_auto ? SCREEN_TIMEOUT_AUTO : SCREEN_TIMEOUT_HOME;
    update_progress(1, 0.0);
}

void lcd_event_handler(twr_module_lcd_event_t event, void *param)
{
    (void) param;

    switch (event) {
    case TWR_MODULE_LCD_EVENT_LEFT_CLICK:
        led_pulse_rgb(0x04, 200);
        screen_change(screen-1);
        break;

    case TWR_MODULE_LCD_EVENT_LEFT_HOLD:
        led_pulse_rgb(0x04, 200);
        screen_auto_toggle();
        break;

    case TWR_MODULE_LCD_EVENT_RIGHT_CLICK:
        led_pulse_rgb(0x04, 200);
        screen_change(screen+1);
        break;

    case TWR_MODULE_LCD_EVENT_RIGHT_HOLD:
        led_pulse_rgb(0x04, 200);
        if (!screen_locked && screen_auto) screen_auto_toggle();
        screen_locked = !screen_locked;
        if (screen_locked) {
            update_progress(1, 1.0);
        } else {
            screen_timestamp = twr_tick_get();
        }
        break;

    case TWR_MODULE_LCD_EVENT_BOTH_HOLD:
        break;

    default:
        break;
    }
}

// Battery module event handler
void battery_event_handler(twr_module_battery_event_t event, void *event_param)
{
    (void) event_param;

    // Log battery event
    twr_log_debug("battery_event_handler(): Battery event: %i", event);

    // If battery module is not present, return
    if (!twr_module_battery_is_present())
    {
        return;
    }

    // If battery event is error, set LED to red color
    if (event == TWR_MODULE_BATTERY_EVENT_ERROR)
    {
        led_mode_rgb(0x01, TWR_LED_MODE_BLINK);
    }

    // If battery event is update, read voltage and set LED color based on battery level
    if (event == TWR_MODULE_BATTERY_EVENT_UPDATE)
    {
        float voltage;
        if (twr_module_battery_get_voltage(&voltage))
        {
            twr_log_debug("battery_event_handler(): Battery voltage: %.2f V", voltage);
            battery_voltage = voltage;
        }
        int charge;
        if (twr_module_battery_get_charge_level(&charge))
            battery_level = (float)charge / 100.0f;
    }
}

void render_time(bool redraw) {
    static uint32_t last_minutes = 0xFFFFFFFF;
    uint32_t now = twr_tick_get() / 1000 + time_offset;
    uint32_t minutes = now / 60;
    if (!redraw && minutes == last_minutes) return;
    last_minutes = minutes;
    uint16_t xo = gfx_caps.width - render_time_width;
    twr_gfx_set_font(pgfx, font_time);
    twr_gfx_draw_fill_rectangle(pgfx, xo, 0, gfx_caps.width, render_time_height, false);
    twr_gfx_printf(pgfx, xo, 0, true, "%02d:%02d", (now/(60*60))%24, (now/(60))%60);
    // twr_gfx_update(pgfx);
}

// draw icon
void draw_icon(int x, int y, const uint8_t *icon) {
    uint8_t w = icon[0];
    uint8_t h = icon[1];
    uint8_t bytes = (w + 7) / 8;
    uint8_t mask = 0x80;
    for (uint8_t j = 0; j < h; j++) {
        for (uint8_t i = 0; i < w; i++) {
            twr_gfx_draw_pixel(pgfx, x + i, y + j, icon[2 + j * bytes + i / 8] & (mask >> (i % 8)));
        }
    }
}

// draw rotated icon by rot * 90 degrees
void draw_icon_rot(int x, int y, int rot, const uint8_t *icon) {
    uint8_t w = icon[0];
    uint8_t h = icon[1];
    uint8_t bytes = (w + 7) / 8;
    uint8_t mask = 0x80;
    rot %= 4;
    for (uint8_t j = 0; j < h; j++) {
        for (uint8_t i = 0; i < w; i++) {
            bool pixel = icon[2 + j * bytes + i / 8] & (mask >> (i % 8));
            switch (rot) {
            case 0:
                twr_gfx_draw_pixel(pgfx, x + i, y + j, pixel);
                break;
            case 1:
                twr_gfx_draw_pixel(pgfx, x + h - j - 1, y + i, pixel);
                break;
            case 2:
                twr_gfx_draw_pixel(pgfx, x + w - i - 1, y + h - j - 1, pixel);
                break;
            case 3:
                twr_gfx_draw_pixel(pgfx, x + j, y + w - i - 1, pixel);
                break;
            default:
                break;
            }
        }
    }
}

char * approx_time(int seconds) {
    static char buf[32];
    if (seconds < 60) {
        snprintf(buf, sizeof(buf), "%ds", seconds);
    } else if (seconds < 60*60) {
        snprintf(buf, sizeof(buf), "%dm", seconds/60);
    } else if (seconds < 24*60*60) {
        snprintf(buf, sizeof(buf), "%dh", seconds/(60*60));
    } else {
        snprintf(buf, sizeof(buf), "%dd", seconds/(24*60*60));
    }
    return buf;
}

void update_progress(int loc, float value) {
    loc %= 2;
    if (progress[loc] != value) {
        progress[loc] = value;
        draw_progress_bar(loc);
        // twr_gfx_update(pgfx);
    }
}

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128
#define SCREEN_STATUS_HEIGHT 14
#define SCREEN_BUTTON_HEIGHT 14
#define SCREEN_BUTTON_SPACING 2
#define SCREEN_BUTTON_SIZE 12
#define SCREEN_BORDER 3
#define SCREEN_ICON_SIZE 24
#define SCREEN_ICON_X (1)
#define SCREEN_ICON_Y (SCREEN_STATUS_HEIGHT + SCREEN_BORDER + 1)
#define SCREEN_TITLE_X (SCREEN_ICON_X + 24 + 2)
#define SCREEN_TITLE_Y (SCREEN_STATUS_HEIGHT + SCREEN_BORDER + 1)
#define SCREEN_TITLE_HEIGHT 16
#define SCREEN_STATUS_BATTERY_X (80)
#define SCREEN_STATUS_REFRESH_X (32)
#define COLOR_FG 1
#define COLOR_BG 0
const uint8_t * const icon_battery[] = {
    icon12_battery_0,
    icon12_battery_25,
    icon12_battery_50,
    icon12_battery_75,
    icon12_battery_100,
    icon12_no_battery,
};
#define BATTERY_LEVELS (sizeof(icon_battery) / sizeof(icon_battery[0]))
#define BATTERY_LEVEL() (battery_present ? ((int)((battery_level+1.0/((BATTERY_LEVELS-2)*2.0)) * (BATTERY_LEVELS-2))) : BATTERY_LEVELS-1)

// draw progress bar
void draw_progress_bar(int loc) {
    loc %= 2;
    int x = (int)(SCREEN_WIDTH * progress[loc]);
    int y = loc > 0 ? SCREEN_HEIGHT - SCREEN_BUTTON_HEIGHT - SCREEN_BORDER -1 : SCREEN_STATUS_HEIGHT;
    twr_gfx_draw_fill_rectangle(pgfx, 0, y, x-1, y+SCREEN_BORDER-1, COLOR_FG);
    twr_gfx_draw_fill_rectangle_dithering(pgfx, x, y, SCREEN_WIDTH-1, y+SCREEN_BORDER-1, 0x5A5A);
}

// Info screen base
/* 
parameters:
    icon - icon to display
    title - title to display
    redraw - if true, clear screen and redraw everything

TODO - refresh only necessary info instead of full redraw every time
TODO - animation during update
TODO - upper progress bar (actions)
TODO - lower progress bar (screen switching)
TODO - button icon highlight (inverted???)
*/
void render_info_screen_base(const uint8_t *icon, const char *title, bool redraw) {
    int btn_w = 2 * SCREEN_BUTTON_SIZE + SCREEN_BUTTON_SPACING;
    int btn_spc = (SCREEN_WIDTH - 3 * btn_w) / 6;
    if (redraw) {
        twr_gfx_clear(pgfx);

        // Border lines / progress bars
        // twr_gfx_draw_fill_rectangle(pgfx, 0, SCREEN_STATUS_HEIGHT, SCREEN_WIDTH-1, SCREEN_STATUS_HEIGHT+SCREEN_BORDER, COLOR_FG);
        // twr_gfx_draw_fill_rectangle(pgfx, 0, SCREEN_HEIGHT-SCREEN_BUTTON_HEIGHT-1-SCREEN_BORDER, SCREEN_WIDTH-1, SCREEN_HEIGHT-SCREEN_BUTTON_HEIGHT-1, COLOR_FG);
        draw_progress_bar(0);
        draw_progress_bar(1);

        // info screen content (icon + title)
        draw_icon(SCREEN_ICON_X, SCREEN_ICON_Y, icon);
        twr_gfx_set_font(pgfx, &twr_font_ubuntu_15);
        int w = twr_gfx_calc_string_width(pgfx, title);
        twr_gfx_draw_string(pgfx, SCREEN_TITLE_X+(SCREEN_WIDTH-SCREEN_TITLE_X-w)/2, SCREEN_TITLE_Y, title, COLOR_FG);

        // Header
        draw_icon(SCREEN_STATUS_REFRESH_X, 1, icon12_refresh);

        // Footer
        #define btn_y (SCREEN_HEIGHT - SCREEN_BUTTON_SIZE - (SCREEN_BUTTON_HEIGHT - SCREEN_BUTTON_SIZE) / 2)
        draw_icon(btn_spc, btn_y, icon12_previous);
        draw_icon(btn_spc + SCREEN_BUTTON_SIZE + SCREEN_BUTTON_SPACING, btn_y, icon12_clock);
        draw_icon(SCREEN_WIDTH/2 - SCREEN_BUTTON_SPACING/2 - SCREEN_BUTTON_SIZE, btn_y, icon12_menu);
        draw_icon(SCREEN_WIDTH/2 + SCREEN_BUTTON_SPACING/2, btn_y, icon12_refresh);
        draw_icon(SCREEN_WIDTH - btn_spc - 2 * SCREEN_BUTTON_SIZE - SCREEN_BUTTON_SPACING, btn_y, icon12_next);
    }

    // Footer
    static bool last_locked = false;
    if (redraw || last_locked != screen_locked) {
        last_locked = screen_locked;
        draw_icon(SCREEN_WIDTH - btn_spc - SCREEN_BUTTON_SIZE, btn_y, screen_locked ? icon12_lock : icon12_unlock);
    }

    static bool last_auto = false;
    if (redraw || last_auto != screen_auto) {
        last_auto = screen_auto;
        draw_icon(btn_spc + SCREEN_BUTTON_SIZE + SCREEN_BUTTON_SPACING, btn_y, screen_auto ? icon12_pause : icon12_play);
    }

    // Header
    static int last_battery_level = -1;
    if (redraw || last_battery_level != BATTERY_LEVEL()) {
        // twr_log_debug("render_info_screen_base(): battery: last=%d, new=%d", last_battery_level, BATTERY_LEVEL());
        last_battery_level = BATTERY_LEVEL();
        draw_icon(SCREEN_STATUS_BATTERY_X, 1, icon_battery[last_battery_level]);
    }

    static int last_screen = -1;
    if (redraw || last_screen != screen) {
        last_screen = screen;
        twr_gfx_set_font(pgfx, &twr_font_ubuntu_13);
        twr_gfx_draw_fill_rectangle(pgfx, 0, 0, SCREEN_STATUS_REFRESH_X-1, SCREEN_STATUS_HEIGHT-1, COLOR_BG);
        twr_gfx_printf(pgfx, 0, 0, COLOR_FG, "%d/%d", screen+1, screens_count);
    }
    static twr_tick_t last_update = 0;

    // TODO - animation during update
    static char last_update_str[32] = "";
    char * update_str = approx_time((twr_tick_get()-last_update)/1000);
    if (redraw || strcmp(last_update_str, update_str) != 0) {
        strncpy(last_update_str, update_str, sizeof(last_update_str));
        twr_gfx_set_font(pgfx, &twr_font_ubuntu_13);
        twr_gfx_draw_fill_rectangle(pgfx, SCREEN_STATUS_REFRESH_X+12+1, 0, SCREEN_STATUS_BATTERY_X-1, SCREEN_STATUS_HEIGHT-1, COLOR_BG);
        twr_gfx_draw_string(pgfx, SCREEN_STATUS_REFRESH_X+12+1, 0, update_str, COLOR_FG);
    }
    render_time(redraw);
}


void render_screen(int screen, bool redraw) {
    // twr_log_debug("render_screen(): base");
    render_info_screen_base(screens[screen].icon, screens[screen].title, redraw);
    if (screens[screen].render != NULL) {
        // twr_log_debug("render_screen(): content");
        screens[screen].render(redraw, screens[screen].param);
    }
    // twr_log_debug("render_screen(): gfx_update");
    twr_gfx_update(pgfx);
}

void render_info_screen_dashboard(bool redraw, void *param) {
    (void) param;
    char buf[32];

    if (redraw) {
        twr_gfx_set_font(pgfx, &twr_font_ubuntu_13);
        // twr_gfx_draw_string(pgfx, 1, SCREEN_TITLE_Y+SCREEN_TITLE_HEIGHT+28-2*13, "tepl.", COLOR_FG);
        twr_gfx_draw_string(pgfx, 1, SCREEN_TITLE_Y+SCREEN_TITLE_HEIGHT+28-1*13, "venku", COLOR_FG);
        twr_gfx_draw_string(pgfx, 1, SCREEN_TITLE_Y+SCREEN_TITLE_HEIGHT+30+24-1*13, "uvnitr", COLOR_FG);
        draw_icon(1, SCREEN_HEIGHT-SCREEN_BUTTON_HEIGHT-SCREEN_BORDER-18, icon16_photovoltaics);
    }

    // outside temperature
    static float temperature_out = -12.3f;  // TODO mockup
    static float last_temperature_out = 0.0f;
    if (redraw || last_temperature_out != temperature_out) {
        last_temperature_out = temperature_out;
        twr_gfx_set_font(pgfx, &twr_font_ubuntu_28);
        snprintf(buf, sizeof(buf), "%2.1f°C", temperature_out);
        int w = twr_gfx_calc_string_width(pgfx, buf);
        twr_gfx_draw_fill_rectangle(pgfx, SCREEN_WIDTH - w, SCREEN_TITLE_Y+SCREEN_TITLE_HEIGHT, SCREEN_WIDTH-1, SCREEN_TITLE_Y+SCREEN_TITLE_HEIGHT+28, COLOR_BG);
        twr_gfx_draw_string(pgfx, SCREEN_WIDTH - w, SCREEN_TITLE_Y+SCREEN_TITLE_HEIGHT, buf, COLOR_FG);
    }

    // inside temperature
    static float last_temperature_in = 0.0f;
    if (redraw || last_temperature_in != temperature) {
        last_temperature_in = temperature;
        twr_gfx_set_font(pgfx, &twr_font_ubuntu_28);
        snprintf(buf, sizeof(buf), "%2.1f°C", temperature);
        int w = twr_gfx_calc_string_width(pgfx, buf);
        twr_gfx_draw_fill_rectangle(pgfx, SCREEN_WIDTH - w, SCREEN_TITLE_Y+SCREEN_TITLE_HEIGHT+30, SCREEN_WIDTH-1, SCREEN_TITLE_Y+SCREEN_TITLE_HEIGHT+30+24, COLOR_BG);
        twr_gfx_draw_string(pgfx, SCREEN_WIDTH - w, SCREEN_TITLE_Y+SCREEN_TITLE_HEIGHT+30, buf, COLOR_FG);
    }

    // photovoltaics power and battery
    const int batt_ofs = SCREEN_WIDTH / 2 + 8;
    bool batt_charging = false;     // TODO mockup
    static char last_power_str[32] = "";
    static int last_batt_level = -1;
    static bool last_batt_charging = false;
    snprintf(buf, sizeof(buf), "%1.2fkW", 1.234);
    int batt_level = (int)(battery_level*100);
    if (redraw || strcmp(last_power_str, buf) != 0 || batt_level != last_batt_level || batt_charging != last_batt_charging) {
        strncpy(last_power_str, buf, sizeof(last_power_str));
        last_batt_level = batt_level;
        twr_gfx_set_font(pgfx, &twr_font_ubuntu_15);
        twr_gfx_draw_fill_rectangle(pgfx, 2 + 16, SCREEN_HEIGHT-SCREEN_BUTTON_HEIGHT-SCREEN_BORDER-16, SCREEN_WIDTH-1, SCREEN_HEIGHT-SCREEN_BUTTON_HEIGHT-SCREEN_BORDER-2, COLOR_BG);
        twr_gfx_draw_string(pgfx, 2 + 16, SCREEN_HEIGHT-SCREEN_BUTTON_HEIGHT-SCREEN_BORDER-17, buf, COLOR_FG);
        snprintf(buf, sizeof(buf), "%d%%", batt_level);
        int w = twr_gfx_calc_string_width(pgfx, buf);
        draw_icon(batt_ofs, SCREEN_HEIGHT-SCREEN_BUTTON_HEIGHT-SCREEN_BORDER-18, batt_charging ? icon16_battery_in : icon16_battery_out);
        twr_gfx_draw_string(pgfx, SCREEN_WIDTH - w, SCREEN_HEIGHT-SCREEN_BUTTON_HEIGHT-SCREEN_BORDER-17, buf, COLOR_FG);
    }
}

void render_info_screen_device(bool redraw, void *param) {
    (void) param;
    char buf[32];

    if (redraw) {
        twr_gfx_set_font(pgfx, &twr_font_ubuntu_13);
        // twr_gfx_draw_string(pgfx, 1, SCREEN_TITLE_Y+SCREEN_TITLE_HEIGHT+28-2*13, "tepl.", COLOR_FG);
        twr_gfx_draw_string(pgfx, 1, SCREEN_TITLE_Y+SCREEN_TITLE_HEIGHT+28-1*13, "teplota", COLOR_FG);
        twr_gfx_draw_string(pgfx, 1, SCREEN_TITLE_Y+SCREEN_TITLE_HEIGHT+30+24-1*13, "baterie", COLOR_FG);
    }

    // temperature
    static float last_temperature = 0.0f;
    if (redraw || last_temperature != temperature) {
        last_temperature = temperature;
        twr_gfx_set_font(pgfx, &twr_font_ubuntu_28);
        snprintf(buf, sizeof(buf), "%2.1f°C", temperature);
        int w = twr_gfx_calc_string_width(pgfx, buf);
        twr_gfx_draw_fill_rectangle(pgfx, SCREEN_WIDTH - w, SCREEN_TITLE_Y+SCREEN_TITLE_HEIGHT, SCREEN_WIDTH-1, SCREEN_TITLE_Y+SCREEN_TITLE_HEIGHT+28, COLOR_BG);
        twr_gfx_draw_string(pgfx, SCREEN_WIDTH - w, SCREEN_TITLE_Y+SCREEN_TITLE_HEIGHT, buf, COLOR_FG);
    }

    // battery voltage
    static char last_voltage_str[32] = "";
    snprintf(buf, sizeof(buf), "%1.2fV", battery_voltage);
    if (redraw || strcmp(last_voltage_str, buf) != 0) {
        strncpy(last_voltage_str, buf, sizeof(last_voltage_str));
        twr_gfx_set_font(pgfx, &twr_font_ubuntu_28);
        int w = twr_gfx_calc_string_width(pgfx, buf);
        twr_gfx_draw_fill_rectangle(pgfx, SCREEN_WIDTH - w, SCREEN_TITLE_Y+SCREEN_TITLE_HEIGHT+30, SCREEN_WIDTH-1, SCREEN_TITLE_Y+SCREEN_TITLE_HEIGHT+30+24, COLOR_BG);
        twr_gfx_draw_string(pgfx, SCREEN_WIDTH - w, SCREEN_TITLE_Y+SCREEN_TITLE_HEIGHT+30, buf, COLOR_FG);
    }

    // battery level
    static char last_infoline[32] = "";
    snprintf(buf, sizeof(buf), "up %s, bat %d%%", approx_time(twr_tick_get()/1000), (int)(battery_level*100));
    if (redraw || strcmp(last_infoline, buf) != 0) {
        strncpy(last_infoline, buf, sizeof(last_infoline));
        twr_gfx_set_font(pgfx, &twr_font_ubuntu_15);
        int w = twr_gfx_calc_string_width(pgfx, buf);
        twr_gfx_draw_fill_rectangle(pgfx, 1, SCREEN_HEIGHT-SCREEN_BUTTON_HEIGHT-SCREEN_BORDER-16, SCREEN_WIDTH-1, SCREEN_HEIGHT-SCREEN_BUTTON_HEIGHT-SCREEN_BORDER-2, COLOR_BG);
        twr_gfx_draw_string(pgfx, SCREEN_WIDTH - w, SCREEN_HEIGHT-SCREEN_BUTTON_HEIGHT-SCREEN_BORDER-16, buf, COLOR_FG);
    }
}

void demo_icon(void) {
    const uint8_t * all_icons12[] = {
        icon12_play,
        icon12_pause,
        icon12_unlock,
        icon12_lock,
        icon12_previous,
        icon12_next,
        icon12_menu,
        icon12_back,
        icon12_home,
        icon12_confirm,
        icon12_clock,
        icon12_thermometer,
        icon12_refresh,
        icon12_in_progress,
        icon12_no_battery,
        icon12_battery_100,
        icon12_battery_75,
        icon12_battery_50,
        icon12_battery_25,
        icon12_battery_0,
    };

    const uint8_t * all_icons24[] = {
        icon24_dashboard,
        icon24_photovoltaics_current,
        icon24_photovoltaics_cumulative,
        icon24_thermometer_home,
        icon24_thermometer_sun,
        icon24_hardwario,
    };

    for (size_t i = 0; i < sizeof(all_icons12) / sizeof(all_icons12[0]); i++) {
        draw_icon(16*(i%8), 16+16*(i/8), all_icons12[i]);
    }
    for (size_t i = 0; i < sizeof(all_icons24) / sizeof(all_icons24[0]); i++) {
        draw_icon(25*(i%5), 64+25*(i/5), all_icons24[i]);
    }
    // draw_icon(20, 0, icon8_arrow_up);
    // draw_icon(30, 0, icon8_arrow_down);
    // draw_icon(40, 0, icon8_arrow_right);
    twr_gfx_update(pgfx);
}

void demo_font(void) {
    int y = 0;
    twr_gfx_set_font(pgfx, &twr_font_ubuntu_11);
    twr_gfx_draw_string(pgfx, 0, y, "Fnt 11", true);
    y += 13;
    twr_gfx_set_font(pgfx, &twr_font_ubuntu_13);
    twr_gfx_draw_string(pgfx, 0, y, "Fnt 13", true);
    y += 15;
    twr_gfx_set_font(pgfx, &twr_font_ubuntu_15);
    twr_gfx_draw_string(pgfx, 0, y, "Fnt 15", true);
    y += 17;
    twr_gfx_set_font(pgfx, &twr_font_ubuntu_24);
    twr_gfx_draw_string(pgfx, 0, y, "Fnt 24", true);
    y += 26;
    twr_gfx_set_font(pgfx, &twr_font_ubuntu_28);
    twr_gfx_draw_string(pgfx, 0, y, "Fnt 28", true);
    y += 30;
    twr_gfx_set_font(pgfx, &twr_font_ubuntu_33);
    twr_gfx_draw_string(pgfx, 0, y, "Fnt 33", true);
    y += 35;
    twr_gfx_update(pgfx);
}

// Application initialization function which is called once after boot
void application_init(void)
{
    // Initialize logging
    twr_log_init(TWR_LOG_LEVEL_DUMP, TWR_LOG_TIMESTAMP_ABS);
    twr_log_debug("Init: LED");

    // Initialize LED
    twr_led_init(&led, TWR_GPIO_LED, false, 0);
    twr_led_pulse(&led, 2000);

    const twr_led_driver_t* driver = twr_module_lcd_get_led_driver();
    for (int i = 0; i < 3; i++)
    {
        twr_led_init_virtual(&lcdLed[i], i, driver, 1);
        twr_led_set_mode(&lcdLed[i], TWR_LED_MODE_OFF);
        twr_led_pulse(&lcdLed[i], 500);
    }


    // Initialize button
    // twr_button_init(&button, TWR_GPIO_BUTTON, TWR_GPIO_PULL_DOWN, 0);
    // twr_button_set_event_handler(&button, button_event_handler, NULL);

    // Initialize thermometer on core module
    twr_log_debug("Init: Thermometer");
    twr_tmp112_init(&tmp112, TWR_I2C_I2C0, 0x49);
    twr_tmp112_set_event_handler(&tmp112, tmp112_event_handler, NULL);
    twr_tmp112_set_update_interval(&tmp112, 10000);

    // Initialize battery module
    // battery_present = twr_module_battery_is_present();
    // if (battery_present) {
    //     twr_module_battery_init();
    //     twr_module_battery_set_event_handler(battery_event_handler, NULL);
    // }

    // LCD Module
    twr_log_debug("Init: LCD");
    twr_module_lcd_init();
    twr_module_lcd_set_event_handler(lcd_event_handler, NULL);

    pgfx = twr_module_lcd_get_gfx();
    // twr_gfx_set_rotation(pgfx, TWR_MODULE_LCD_ROTATION_0);
    gfx_caps = twr_gfx_get_caps(pgfx);
    twr_gfx_set_font(pgfx, font_time);
    render_time_width = twr_gfx_calc_string_width(pgfx, "00:00");

    twr_log_debug("Init: LED render_screen()");
    // twr_gfx_clear(pgfx);
    // demo_font();
    // demo_icon();
    // render_info_screen_base(icon24_dashboard, "Prehled");
    // render_info_screen_dashboard(NULL);
    render_screen(screen, true);
    twr_gfx_update(pgfx);

    // Initialize radio
    twr_log_debug("Init: Radio");
    twr_radio_init(TWR_RADIO_MODE_NODE_SLEEPING);
    // Send radio pairing request
    // twr_radio_pairing_request("infobox", FW_VERSION);
    twr_log_debug("Init done.");
}

// Application task function (optional) which is called peridically if scheduled
void application_task(void)
{
    static int counter = 0;

    // Log task run and increment counter
    // twr_log_debug("APP: Task run (count: %d)", ++counter);
    twr_tick_t now = twr_tick_get();
    counter++;
    if (counter % 4 == 0) {
        battery_level -= 0.01;
        if (battery_level < 0.0f) {
            battery_level = 1.0f;
        }
    }
    if ((!screen_locked && screen > 0) || screen_auto) {
        twr_tick_t screen_time = now - screen_timestamp;
        update_progress(1, (float)screen_time / (float)screen_timeout);
        if (screen_time > screen_timeout) {
            screen_change(screen_auto ? screen+1 : 0);
        }
    }
    // render_time();
    render_screen(screen, false);
    // twr_gfx_update(pgfx);
    twr_tick_t duration = twr_tick_get() - now;
    twr_log_debug("APP: Task run (count: %d, duration: %lld ms)", counter, duration);

    // Plan next run of this task in N ms
    twr_scheduler_plan_current_from_now(1000);
}
