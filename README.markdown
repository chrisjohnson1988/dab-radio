# Dab Radio

This repository contains some command line tools which can control DAB radio dongles which are often sold as Android DAB dongles. I believe these dongles are based upon the MTV318 chip manufactured by Roantech. These tuners have a 10 bit adc which is able to get better reception of weaker transmissions than rtl-sdr based tuners (which only have an 8 bit adc). The **ADMTV315** by Analog Devices seems to be the best fit when looking for a datasheet to document how to control the tuner.

My main aim for this project is to add DAB radio stations to [tvheadend](https://tvheadend.org/) by producing an `.m3u` file which can be added as an IPTV feed (leveraging the pipe:// syntax). See [Custom MPEG-TS Input](https://tvheadend.org/projects/tvheadend/wiki/Custom_MPEG-TS_Input0)

## Credits
The code in this project is based on:

- https://github.com/Opendigitalradio/dablin
- https://github.com/hradio/omri-usb