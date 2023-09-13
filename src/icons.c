#include <icons.h>

const uint8_t icon8_arrow_up[] = {
    8, 8,
    0b00000000,
    0b00000000,
    0b00010000,
    0b00111000,
    0b01111100,
    0b11111110,
    0b00000000,
    0b00000000,
};

const uint8_t icon8_arrow_down[] = {
    8, 8,
    0b00000000,
    0b00000000,
    0b11111110,
    0b01111100,
    0b00111000,
    0b00010000,
    0b00000000,
    0b00000000,
};

const uint8_t icon8_arrow_right[] = {
    8, 8,
    0b00100000,
    0b00110000,
    0b00111000,
    0b00111100,
    0b00111000,
    0b00110000,
    0b00100000,
    0b00000000,
};

/*
TODO icon12:
- no battery
*/

const uint8_t icon12_play[] = {
    12, 12,
    0b00000000, 0b00000000,
    0b00011000, 0b00000000,
    0b00011100, 0b00000000,
    0b00011110, 0b00000000,
    0b00011111, 0b00000000,
    0b00011111, 0b10000000,
    0b00011111, 0b10000000,
    0b00011111, 0b00000000,
    0b00011110, 0b00000000,
    0b00011100, 0b00000000,
    0b00011000, 0b00000000,
    0b00000000, 0b00000000,
};

const uint8_t icon12_pause[] = {
    12, 12,
    0b00000000, 0b00000000,
    0b00111001, 0b11000000,
    0b00111001, 0b11000000,
    0b00111001, 0b11000000,
    0b00111001, 0b11000000,
    0b00111001, 0b11000000,
    0b00111001, 0b11000000,
    0b00111001, 0b11000000,
    0b00111001, 0b11000000,
    0b00111001, 0b11000000,
    0b00111001, 0b11000000,
    0b00000000, 0b00000000,
};

const uint8_t icon12_previous[] = {
    12, 12,
    0b00000000, 0b00110000,
    0b00000000, 0b11100000,
    0b00000011, 0b11000000,
    0b00001111, 0b10000000,
    0b00111111, 0b00000000,
    0b11111110, 0b00000000,
    0b11111110, 0b00000000,
    0b00111111, 0b00000000,
    0b00001111, 0b10000000,
    0b00000011, 0b11000000,
    0b00000000, 0b11100000,
    0b00000000, 0b00110000,
};

const uint8_t icon12_next[] = {
    12, 12,
    0b11000000, 0b00000000,
    0b01110000, 0b00000000,
    0b00111100, 0b00000000,
    0b00011111, 0b00000000,
    0b00001111, 0b11000000,
    0b00000111, 0b11110000,
    0b00000111, 0b11110000,
    0b00001111, 0b11000000,
    0b00011111, 0b00000000,
    0b00111100, 0b00000000,
    0b01110000, 0b00000000,
    0b11000000, 0b00000000,
};

const uint8_t icon12_menu[] = {
    12, 12,
    0b00000000, 0b00000000,
    0b01111111, 0b11100000,
    0b01111111, 0b11100000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
    0b01111111, 0b11100000,
    0b01111111, 0b11100000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
    0b01111111, 0b11100000,
    0b01111111, 0b11100000,
    0b00000000, 0b00000000,
};

const uint8_t icon12_lock[] = {
    12, 12,
    0b00011100, 0b00000000,
    0b00111110, 0b00000000,
    0b01100011, 0b00000000,
    0b01100011, 0b00000000,
    0b01100011, 0b00000000,
    0b11111111, 0b10000000,
    0b11111111, 0b10000000,
    0b11110111, 0b10000000,
    0b11110111, 0b10000000,
    0b11110111, 0b10000000,
    0b11111111, 0b10000000,
    0b11111111, 0b10000000,
};

const uint8_t icon12_unlock[] = {
    12, 12,
    0b00000000, 0b11000000,
    0b00000001, 0b11100000,
    0b00000011, 0b00110000,
    0b00000011, 0b00110000,
    0b00000011, 0b00110000,
    0b11111111, 0b10000000,
    0b11111111, 0b10000000,
    0b11110111, 0b10000000,
    0b11110111, 0b10000000,
    0b11110111, 0b10000000,
    0b11111111, 0b10000000,
    0b11111111, 0b10000000,
};

const uint8_t icon12_back[] = {
    12, 12,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00011000, 0b00000000,
    0b00111000, 0b00000000,
    0b01111111, 0b10000000,
    0b11111111, 0b11100000,
    0b01111111, 0b11110000,
    0b00111000, 0b01110000,
    0b00011000, 0b00110000,
    0b00000000, 0b00010000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
};

const uint8_t icon12_home[] = {
    12, 12,
    0b00000110, 0b00000000,
    0b00001111, 0b00000000,
    0b00011111, 0b10000000,
    0b00111111, 0b11000000,
    0b01111111, 0b11100000,
    0b11111111, 0b11110000,
    0b00111111, 0b11000000,
    0b00111001, 0b11000000,
    0b00111001, 0b11000000,
    0b00111001, 0b11000000,
    0b00111001, 0b11000000,
    0b00111001, 0b11000000,
};

const uint8_t icon12_confirm[] = {
    12, 12,
    0b00000000, 0b00000000,
    0b00000000, 0b01110000,
    0b00000000, 0b01110000,
    0b00000000, 0b01110000,
    0b00011000, 0b01110000,
    0b00111000, 0b01110000,
    0b01111111, 0b11110000,
    0b11111111, 0b11110000,
    0b01111111, 0b11110000,
    0b00111000, 0b00000000,
    0b00011000, 0b00000000,
    0b00000000, 0b00000000,
};

// TODO
const uint8_t icon12_clock[] = {
    12, 12,
    0b00001111, 0b00000000,
    0b00011111, 0b10000000,
    0b01110010, 0b11100000,
    0b01100010, 0b01100000,
    0b11000010, 0b00110000,
    0b11011110, 0b00110000,
    0b11011110, 0b00110000,
    0b11000000, 0b00110000,
    0b01100000, 0b01100000,
    0b01110000, 0b11100000,
    0b00011111, 0b10000000,
    0b00001111, 0b00000000,
};

const uint8_t icon12_refresh[] = {
    12, 12,
    0b00001111, 0b00010000,
    0b00011111, 0b10110000,
    0b01110000, 0b11110000,
    0b01100000, 0b11110000,
    0b11000001, 0b11110000,
    0b11000000, 0b00000000,
    0b11000000, 0b00000000,
    0b11000000, 0b00000000,
    0b01100000, 0b01100000,
    0b01110000, 0b11100000,
    0b00011111, 0b10000000,
    0b00001111, 0b00000000,
};

// TODO - keep only one icon12_in_progress and rotate it programmatically
const uint8_t icon12_in_progress[] = {
    12, 12,
    0b00001111, 0b10000000,
    0b00011111, 0b11100000,
    0b01111111, 0b11110000,
    0b01110000, 0b11110000,
    0b11100000, 0b01100000,
    0b11000000, 0b00000000,
    0b11000000, 0b00000000,
    0b11000000, 0b00010000,
    0b01100000, 0b00000000,
    0b01100000, 0b00100000,
    0b00110000, 0b10000000,
    0b00001111, 0b00000000,
};

const uint8_t icon12_no_battery[] = {
    12, 12,
    0b00001111, 0b00000000,
    0b00111111, 0b11000000,
    0b00011111, 0b10000000,
    0b00001111, 0b00000000,
    0b00100110, 0b01000000,
    0b00110000, 0b11000000,
    0b00111001, 0b11000000,
    0b00110000, 0b11000000,
    0b00100110, 0b01000000,
    0b00001111, 0b00000000,
    0b00011111, 0b10000000,
    0b00111111, 0b11000000,
};

const uint8_t icon12_battery_100[] = {
    12, 12,
    0b00001111, 0b00000000,
    0b00111111, 0b11000000,
    0b00111111, 0b11000000,
    0b00111111, 0b11000000,
    0b00111111, 0b11000000,
    0b00111111, 0b11000000,
    0b00111111, 0b11000000,
    0b00111111, 0b11000000,
    0b00111111, 0b11000000,
    0b00111111, 0b11000000,
    0b00111111, 0b11000000,
    0b00111111, 0b11000000,
};

const uint8_t icon12_battery_75[] = {
    12, 12,
    0b00001111, 0b00000000,
    0b00111111, 0b11000000,
    0b00111001, 0b11000000,
    0b00110000, 0b11000000,
    0b00111111, 0b11000000,
    0b00111111, 0b11000000,
    0b00111111, 0b11000000,
    0b00111111, 0b11000000,
    0b00111111, 0b11000000,
    0b00111111, 0b11000000,
    0b00111111, 0b11000000,
    0b00111111, 0b11000000,
};

const uint8_t icon12_battery_50[] = {
    12, 12,
    0b00001111, 0b00000000,
    0b00111111, 0b11000000,
    0b00111001, 0b11000000,
    0b00110000, 0b11000000,
    0b00110000, 0b11000000,
    0b00110000, 0b11000000,
    0b00111111, 0b11000000,
    0b00111111, 0b11000000,
    0b00111111, 0b11000000,
    0b00111111, 0b11000000,
    0b00111111, 0b11000000,
    0b00111111, 0b11000000,
};

const uint8_t icon12_battery_25[] = {
    12, 12,
    0b00001111, 0b00000000,
    0b00111111, 0b11000000,
    0b00111001, 0b11000000,
    0b00110000, 0b11000000,
    0b00110000, 0b11000000,
    0b00110000, 0b11000000,
    0b00110000, 0b11000000,
    0b00110000, 0b11000000,
    0b00111111, 0b11000000,
    0b00111111, 0b11000000,
    0b00111111, 0b11000000,
    0b00111111, 0b11000000,
};

const uint8_t icon12_battery_0[] = {
    12, 12,
    0b00001111, 0b00000000,
    0b00111111, 0b11000000,
    0b00111001, 0b11000000,
    0b00110000, 0b11000000,
    0b00110000, 0b11000000,
    0b00110000, 0b11000000,
    0b00110000, 0b11000000,
    0b00110000, 0b11000000,
    0b00110000, 0b11000000,
    0b00110000, 0b11000000,
    0b00111111, 0b11000000,
    0b00111111, 0b11000000,
};

const uint8_t icon12_thermometer[] = {
    12, 12,
    0b00011100, 0b00000000,
    0b00100010, 0b11100000,
    0b00100010, 0b00000000,
    0b00100010, 0b00000000,
    0b00111110, 0b11100000,
    0b00111110, 0b00000000,
    0b00111110, 0b00000000,
    0b00111110, 0b11100000,
    0b01111111, 0b00000000,
    0b01111111, 0b00000000,
    0b01111111, 0b00000000,
    0b00111110, 0b00000000,
};


/*
TODO icon16:
- photovoltaics
- battery charge
- battery discharge
*/

const uint8_t icon16_photovoltaics[] = {
    16, 16,
    0b00000100, 0b00000000,
    0b01000100, 0b10000000,
    0b00100001, 0b00000000,
    0b00001100, 0b00000000,
    0b11011110, 0b00000000,
    0b00011110, 0b11000000,
    0b00001100, 0b00000000,
    0b00100001, 0b00000000,
    0b01001000, 0b10000000,
    0b00001000, 0b00000000,
    0b00000000, 0b00000000,
    0b00011111, 0b10011111,
    0b00111111, 0b00111111,
    0b01111110, 0b01111110,
    0b11111100, 0b11111100,
    0b11111001, 0b11111000,
};

const uint8_t icon16_battery_in[] = {
    16, 16,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00111100, 0b00000000,
    0b11111111, 0b00000000,
    0b11100111, 0b00001000,
    0b11000011, 0b00011000,
    0b11000011, 0b00111000,
    0b11000011, 0b01111111,
    0b11000011, 0b01111111,
    0b11000011, 0b00111000,
    0b11111111, 0b00011000,
    0b11111111, 0b00001000,
    0b11111111, 0b00000000,
    0b11111111, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
};

const uint8_t icon16_battery_out[] = {
    16, 16,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00111100, 0b00000000,
    0b11111111, 0b00000000,
    0b11100111, 0b00001000,
    0b11000011, 0b00001100,
    0b11000011, 0b00001110,
    0b11000011, 0b01111111,
    0b11000011, 0b01111111,
    0b11000011, 0b00001110,
    0b11111111, 0b00001100,
    0b11111111, 0b00001000,
    0b11111111, 0b00000000,
    0b11111111, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
};

const uint8_t icon16_thermometer[] = {
    16, 16,
    0b00000000, 0b00000000,
    0b00000011, 0b10000000,
    0b00000100, 0b01011100,
    0b00000100, 0b01000000,
    0b00000100, 0b01000000,
    0b00000100, 0b01011100,
    0b00000111, 0b11000000,
    0b00000111, 0b11000000,
    0b00000111, 0b11011100,
    0b00000111, 0b11000000,
    0b00001111, 0b11100000,
    0b00011111, 0b11110000,
    0b00011111, 0b11110000,
    0b00011111, 0b11110000,
    0b00001111, 0b11100000,
    0b00000111, 0b11000000,
};


/*
TODO icon24:
*/
const uint8_t icon24_dashboard[] = {
    24, 24, 
    0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b11111111, 0b00000000,
    0b00000011, 0b11111111, 0b11000000,
    0b00000111, 0b11111111, 0b11000000,
    0b00001111, 0b10000001, 0b10010000,
    0b00011110, 0b00000000, 0b01100000,
    0b00111100, 0b00000000, 0b11101100,
    0b00111000, 0b00000001, 0b11011100,
    0b01110000, 0b00000111, 0b10001110,
    0b01110000, 0b00111111, 0b00001110,
    0b01110000, 0b01111111, 0b00001110,
    0b01110000, 0b01111110, 0b00001110,
    0b01111000, 0b01111110, 0b00011110,
    0b01111111, 0b01111110, 0b11111110,
    0b00111111, 0b10111101, 0b11111100,
    0b00001111, 0b10000001, 0b11110000,
    0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000,
    0b00111100, 0b00111100, 0b00111100,
    0b00100100, 0b00100100, 0b00100100,
    0b00111100, 0b00111100, 0b00111100,
    0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000,
};

const uint8_t icon24_photovoltaics_current[] = {
    24, 24,
    0b00000100, 0b00000000, 0b00000000,
    0b01000100, 0b01000000, 0b00001111,
    0b00100000, 0b10000000, 0b00011110,
    0b00001110, 0b00000000, 0b00111100,
    0b00011111, 0b00000000, 0b01111000,
    0b11011111, 0b01100000, 0b11111111,
    0b00011111, 0b00000001, 0b11111110,
    0b00001110, 0b00000000, 0b00011100,
    0b00100000, 0b10000000, 0b00111000,
    0b01000100, 0b01000000, 0b01100000,
    0b00000100, 0b00000000, 0b11000000,
    0b00000000, 0b00000001, 0b00000000,
    0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000,
    0b00000011, 0b11111001, 0b11111100,
    0b00000111, 0b11110011, 0b11111000,
    0b00001111, 0b11100111, 0b11110000,
    0b00011111, 0b11001111, 0b11100000,
    0b00111111, 0b10011111, 0b11000000,
    0b01111111, 0b00111111, 0b10000000,
    0b11111110, 0b01111111, 0b00000000,
    0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000,
};

const uint8_t icon24_photovoltaics_cumulative[] = {
    24, 24,
    0b00000100, 0b00000000, 0b00000000,
    0b01000100, 0b01000001, 0b11111111,
    0b00100000, 0b10000001, 0b11111111,
    0b00001110, 0b00000000, 0b11100001,
    0b00011111, 0b00000000, 0b01110000,
    0b11011111, 0b01100000, 0b00111000,
    0b00011111, 0b00000000, 0b00011100,
    0b00001110, 0b00000000, 0b00111000,
    0b00100000, 0b10000000, 0b01110000,
    0b01000100, 0b01000000, 0b11100001,
    0b00000100, 0b00000001, 0b11111111,
    0b00000000, 0b00000001, 0b11111111,
    0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000,
    0b00000011, 0b11111001, 0b11111100,
    0b00000111, 0b11110011, 0b11111000,
    0b00001111, 0b11100111, 0b11110000,
    0b00011111, 0b11001111, 0b11100000,
    0b00111111, 0b10011111, 0b11000000,
    0b01111111, 0b00111111, 0b10000000,
    0b11111110, 0b01111111, 0b00000000,
    0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000,
};

const uint8_t icon24_thermometer_home[] = {
    24, 24,
    0b00000000, 0b00000000, 0b00000000,
    0b00011100, 0b00000000, 0b01100000,
    0b00100010, 0b00000000, 0b11110000,
    0b00100010, 0b00000001, 0b11111000,
    0b00100010, 0b11000011, 0b11111100,
    0b00100010, 0b00000111, 0b11111110,
    0b00100010, 0b00001111, 0b11111111,
    0b00100010, 0b11000011, 0b11111100,
    0b00100010, 0b00000011, 0b10011100,
    0b00100010, 0b00000011, 0b10011100,
    0b00111110, 0b11000011, 0b10011100,
    0b00111110, 0b00000011, 0b10011100,
    0b00111110, 0b00000011, 0b10011100,
    0b00111110, 0b11000000, 0b00000000,
    0b00111110, 0b00000000, 0b00000000,
    0b00111110, 0b00000000, 0b00000000,
    0b00111110, 0b11000000, 0b00000000,
    0b01111111, 0b00000000, 0b00000000,
    0b11111111, 0b10000000, 0b00000000,
    0b11111111, 0b10000000, 0b00000000,
    0b11111111, 0b10000000, 0b00000000,
    0b11111111, 0b10000000, 0b00000000,
    0b01111111, 0b00000000, 0b00000000,
    0b00111110, 0b00000000, 0b00000000,
};

const uint8_t icon24_thermometer_sun[] = {
    24, 24,
    0b00000000, 0b00000000, 0b00100000,
    0b00011100, 0b00000010, 0b00100010,
    0b00100010, 0b00000001, 0b00000100,
    0b00100010, 0b00000000, 0b01110000,
    0b00100010, 0b11000000, 0b11111000,
    0b00100010, 0b00000110, 0b11111011,
    0b00100010, 0b00000000, 0b11111000,
    0b00100010, 0b11000000, 0b01110000,
    0b00100010, 0b00000001, 0b00000100,
    0b00100010, 0b00000010, 0b00100010,
    0b00111110, 0b11000000, 0b00100000,
    0b00111110, 0b00000000, 0b00000000,
    0b00111110, 0b00000000, 0b00000000,
    0b00111110, 0b11000000, 0b00000000,
    0b00111110, 0b00000000, 0b00000000,
    0b00111110, 0b00000000, 0b00000000,
    0b00111110, 0b11000000, 0b00000000,
    0b01111111, 0b00000000, 0b00000000,
    0b11111111, 0b10000000, 0b00000000,
    0b11111111, 0b10000000, 0b00000000,
    0b11111111, 0b10000000, 0b00000000,
    0b11111111, 0b10000000, 0b00000000,
    0b01111111, 0b00000000, 0b00000000,
    0b00111110, 0b00000000, 0b00000000,
};

const uint8_t icon24_hardwario[] = {
    24, 24,
    0b00111100, 0b00000000, 0b00111100,
    0b01111110, 0b00000000, 0b01111110,
    0b01111110, 0b00000000, 0b01111110,
    0b01111110, 0b00000000, 0b01111110,
    0b00111100, 0b00111100, 0b00111100,
    0b00011000, 0b01111110, 0b00011000,
    0b00011001, 0b11111110, 0b00011000,
    0b00011111, 0b11111110, 0b00011000,
    0b00011110, 0b00111100, 0b00011000,
    0b00011000, 0b00000000, 0b00111000,
    0b00000000, 0b00000011, 0b11111000,
    0b00000000, 0b00111111, 0b11000000,
    0b00000011, 0b11111100, 0b00000000,
    0b00011111, 0b11000000, 0b00000000,
    0b00011100, 0b00000000, 0b00011000,
    0b00011000, 0b00111100, 0b01111000,
    0b00011000, 0b01111111, 0b11111000,
    0b00011000, 0b01111111, 0b10011000,
    0b00011000, 0b01111110, 0b00011000,
    0b00111100, 0b00111100, 0b00111100,
    0b01111110, 0b00000000, 0b01111110,
    0b01111110, 0b00000000, 0b01111110,
    0b01111110, 0b00000000, 0b01111110,
    0b00111100, 0b00000000, 0b00111100,
};