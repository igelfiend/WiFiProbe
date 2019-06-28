# WiFiProbe

## June 28th, 2019 Added ##
* Provided code refactor;
* Appended config file usage (server-ip, server-port, wlan physical address);
* JSON structure was updated into:
{
    'id': 'xxxxxxxxxxxx',
    'packets': [
    {
         'ch': 11,
         'ssid': '',
         'seq_num': 20528,
         'timestamp': 1561536816,
         'source': 'xxxxxxxxxxxx',
         'rssi': -37
    },
    {
        'ch': 11,
        'ssid': 'ntrlab',
        'seq_num': 45536,
        'timestamp': 1561536816,
        'source': 'xxxxxxxxxxxx',
        'rssi': -34
    }]
}


## May 27th, 2018 Added ##
For Openwrt LEDE *Device or resource busy (-16)* problems, please make sure other apps which will occupy wireless interfaces like hostapd is uninstalled. And to obtain data this app needs, you should turn your WLAN card into *monitor* mode using command *iw*.

(This app is only tested using 802.11n WLAN card, so I cannot guarantee the performance using 802.11ac WLAN card, although it should work in theroy.)

## May 25th, 2018 Added ##

Depends Missing Problem Solved. Thanks for figoym(sorry for not understanding you at once) and Tianyi.

## Introdution
Openwrt WiFi Probe, with http post to send data to server.
You need to have a OpenwrtSDK to compile the source code. When it is done, you will get a IPK like "Scannerxxxxx.ipk".
Switch your wireless network adapter to "monitor" mode, install this IPK, and tape Scanner in the shell. Then the node is sending data to your server.

When you get the IPK, make sure your Openwrt Router firmware has pcap & pthread installed.(Using muti-thread & pcap)

The data it sends is a json-form. Have fun.

About more details, please read my CSDN.
http://blog.csdn.net/sunhaobo1996/

PS:Using libpcap to open an active Network interface, so you need to download libpcap and install it on your computer, or you will meet some .h header missing problems.[Their website](http://www.tcpdump.org/#latest-releases)
