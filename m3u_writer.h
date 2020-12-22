
#ifndef M3UWRITER_H
#define M3UWRITER_H

#include <fstream>
#include "dab_scanner.h"

class M3UWriter: public DabScannerObserver {
public:

    M3UWriter();
    ~M3UWriter();

    void serviceFound(
        const uint32_t frequency, 
        std::string ensemble_name, 
        std::string service_name, 
        uint8_t subchannel, 
        bool dab_plus
    );

private:
    std::ofstream m3u;
};

#endif