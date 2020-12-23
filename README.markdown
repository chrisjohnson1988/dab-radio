# DAB Radio

This repository contains some command line tools which can control DAB radio dongles which are often sold as Android DAB dongles. I believe these dongles are based upon the MTV318 chip manufactured by Roantech. These tuners have a 10 bit adc which is able to get better reception of weaker transmissions than rtl-sdr based tuners (which only have an 8 bit adc). The **ADMTV315** by Analog Devices seems to be the best fit when looking for a datasheet to document how to control the tuner. The tuner I have has the vendor id `0x16c0` and product ids `0x05dc`.

My main aim for this project is to add DAB radio stations to [tvheadend](https://tvheadend.org/) by producing an `.m3u` file which can be added as an IPTV feed (leveraging the pipe:// syntax). See [Custom MPEG-TS Input](https://tvheadend.org/projects/tvheadend/wiki/Custom_MPEG-TS_Input0)

## Installation

In order to build the project, your system will require

- libusb-dev
- g++
- make

To build the code:

        cd /opt
        git clone https://github.com/chrisjohnson1988/dab-radio
        cd dab-radio
        make

Grant access to the usb device. Create a file /etc/udev/rules.d/50-dab-radio.rules with the following content

        SUBSYSTEMS=="usb", ATTR{idVendor}=="16c0", ATTR{idProduct}="05dc", GROUP="users", MODE="0666"

## Scanning for Stations

Running `/opt/dab-radio/dab_scan` will produce a `dab.m3u` playlist in the `/opt/dab-radio`. This can be added to TV Headend as an **IPTV Automatic Network** under **Configuration > DVB Inputs >> Networks**. A full scan takes approximately 2 minutes and will produce a m3u file with content similar to this:


        #EXTM3U
        #EXTINF:-1, BBC Radio 1
        pipe:///opt/dab-radio/dab_mpegts 'BBC National DAB' 'BBC Radio 1' 225648000 1 mp2
        #EXTINF:-1, BBC Radio 2
        pipe:///opt/dab-radio/dab_mpegts 'BBC National DAB' 'BBC Radio 2' 225648000 2 mp2
        #EXTINF:-1, BBC Radio 3
        pipe:///opt/dab-radio/dab_mpegts 'BBC National DAB' 'BBC Radio 3' 225648000 3 mp2
        #EXTINF:-1, BBC Radio 4
        pipe:///opt/dab-radio/dab_mpegts 'BBC National DAB' 'BBC Radio 4' 225648000 4 mp2

## Future work

Multiple radio stations are broadcast on the same frequency, segmented on different logical subchannels. Ideally, all the subchannels would be muxed on to the same mpegts stream resulting in each frequency being listed in the m3u file once.

## Credits
The code in this project is based on:

- https://github.com/Opendigitalradio/dablin
- https://github.com/hradio/omri-usb