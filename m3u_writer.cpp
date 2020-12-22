#include <iostream>
#include "m3u_writer.h"

M3UWriter::M3UWriter() {
    m3u.open("out.m3u");
};

M3UWriter::~M3UWriter() {
    m3u.close();
};

void M3UWriter::serviceFound(
    const uint32_t frequency, 
    std::string ensemble_name, 
    std::string service_name, 
    uint8_t subchannel, 
    bool dab_plus
) {

    m3u << +frequency << " " << +subchannel << " " << +dab_plus << " " << ensemble_name << " - " << service_name << std::endl;
};