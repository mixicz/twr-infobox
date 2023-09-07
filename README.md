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
    * short press - switch to next screen / menu item,
    * long press - auto rotate screens / exit menu,

* right button:
    * short press - switch to previous screen / confirm current selection,
    * long press - lock current screen / go back one level in menu,

* both buttons:
    * short press - enter menu / exit menu,
    * long press - reset device,

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
