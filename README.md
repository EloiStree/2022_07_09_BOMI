# 2022 07 09 BOMI
> BOMI is my bluetooth arduino toolbox to allows inject keyboard on computer from USB and BLE for Open macro Input.

Note:
- This is my first library. Feel free to help me contruct it.
- This library make part of bigger toolbox group called OMI for [Open Macro Input](https://github.com/EloiStree?tab=repositories&q=Open+Macro+Input&type=&language=&sort=).
- I only live of Donation and small job. Feel free to send a coffee: https://ko-fi.com/eloistree

  
I train myself on https://github.com/EloiStree/2022_06_17_HelloBLEMIDI  
Feel free to go there if you want to follow my learning path.  

## Working version

### HC and IR to USB
This first verison allows on an Arduino Leonardo to listen to Infra red command from TV Remote or Bluetooth command with HC05 and to convert them to midi push and/or keyboard action on the linked usb device:
- Commit: https://github.com/EloiStree/2022_07_09_BOMI/commit/6d4997109cc36131ab4e3fa312dc2ccda5601069
 - File: https://github.com/EloiStree/2022_07_09_BOMI/tree/main/examples/V0%20HC05%20IR%20To%20USB%20Keyboard
