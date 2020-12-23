#include <iostream>
#include "m3u_writer.h"

M3UWriter::M3UWriter() {
    m3u.open("dab.m3u");
    m3u << "#EXTM3U" << std::endl;
};

M3UWriter::~M3UWriter() {
    m3u.close();
};

void M3UWriter::serviceFound(
    const uint32_t frequency,
    std::string ensemble_name,
    std::string service_name,
    uint8_t subchannel,
    bool dab_plus,
    uint16_t bitrate
) {

    m3u << "#EXTINF:-1, " << service_name << std::endl;
    m3u << "pipe:///opt/dab-radio/dab_mpegts '" << ensemble_name << "' '" << service_name << "' " << +frequency << " " << +subchannel << " ";
    if(dab_plus) {
        m3u << "aac" << " " << +bitrate;
    } else {
        m3u <<  "mp2";
    }
    m3u << std::endl;
};