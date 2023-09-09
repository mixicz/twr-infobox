# Hardwario Tower infobox

Firmware for information box built on Hardwario Tower platform with core and LCD modules.

It uses protobuf encoded data split to multiple base64 encoded chunks to receive data to display. It can work in online mode (always listening with enabled radio) or offline mode (requesting data in periodic intervals for battery powered operation).

This firmware supports following info screens:
* TODO customizable dashboard,
* TODO meteorological data (temperatures, humidity, pressure),
* TODO photo-voltaics current stats,
* TODO photo-voltaics daily cumulative stats,

## Controls

* left button:
    * short press - switch to previous screen / menu item,
    * long press - auto rotate screens / exit menu,

* right button:
    * short press - switch to next screen / confirm current selection,
    * long press - lock current screen / go back one level in menu,

* both buttons:
    * short press - enter menu / exit menu,
    * long press - refresh data,

## Screens

### Infoscreen generic
    |   |   |   |   |   |   |   |   
    1/5 Status icons and text  00:00 --
    +------------------------------+ 
    | AAAAAA  Screen title         | --
    | AAAAAA  (15px)               | 
    | AAAAAA        BBBBBBBBBBBBBB | --
    |               BBBBBBBBBBBBBB |
    | Primary data  BBBBBBBBBBBBBB | --
    | description   BBBBBBBBBBBBBB |
    |                              | --
    |               CCCCCCCCCCCCCC |
    | Sec. data     CCCCCCCCCCCCCC | --
    | description   CCCCCCCCCCCCCC |
    |                              | --
    |             Additional data  |
    +------------------------------+ --
    UU / VV     WW / XX      YY / ZZ 

* 1/5 - screen number / total number of screens (13px)
* Status icons (12×12):
    * refresh - time since last data refresh / data refresh in progress
    * battery - battery voltage
* 00:00 - current time
* A - current screen icon (24×24)
* B - primary data (28px)
* C - secondary data (24px)
* button icons (12×12):
    * U - left button icon - short press
    * V - left button icon - long press 
    * W - both buttons icon - short press
    * X - both buttons icon - long press
    * Y - right button icon - short press
    * Z - right button icon - long press

### Dashboard
* outside temperature
* inside temperature
* PV current power
* PV battery percentage
* PV battery charge status

### Meteorological data
* outside temperature
* outside humidity
* outside pressure
* outside luminosity

### In-house climate
* inside temperature (primary)
* inside temperature (local)
* attic temperature
* server room temperature

### Photo-voltaics current stats
* current power
* battery percentage
* battery charge status
* battery charge power
* house consumption
* grid status

### Photo-voltaics daily cumulative stats
* today's generated energy
* today's sold energy
* TODO

### Device info
* temperature
* battery voltage
* uptime
* battery percentage

# Communication

## Emmited events
### temperature
TODO

### battery voltage
TODO

### capabilites
TODO

### data request
TODO

## Accepted data
### time (TIM)
TODO

### meteorological data (MET)
TODO

### photo-voltaics current stats (PVC)
TODO

### photo-voltaics daily cumulative stats (PVD)
TODO

# Development

## Screen definition
In initial version, static compiled-in screens are used. Each screen is drawn by a function

# License

This project is licensed under the [MIT License](https://opensource.org/licenses/MIT/) - see the [LICENSE](LICENSE) file for details.
