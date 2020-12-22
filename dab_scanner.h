#ifndef DABSCANNER_H
#define DABSCANNER_H

#include "dab_scanner.h"

#include <map>
#include "fic_decoder.h"
#include "raon_tuner.h"

class DabScannerObserver {
public:
	virtual void serviceFound(
        const uint32_t frequency, 
        std::string ensemble_name, 
        std::string service_name, 
        uint8_t subchannel, 
        bool dab_plus
    ) {}
};

class DabScanner: public FICDecoderObserver, FicObserver {
public:
    DabScanner(RaonTunerInput* tuner, DabScannerObserver* observer);
    void startFrequencyScan();

private:
    static constexpr uint32_t DAB_FREQUENCIES[] {
        174928000, //5A
        176640000, //5B
        178352000, //5C
        180064000, //5D
        181936000, //6A
        183648000, //6B
        185360000, //6C
        187072000, //6D
        188928000, //7A
        190640000, //7B
        192352000, //7C
        194064000, //7D
        195936000, //8A
        197648000, //8B
        199360000, //8C
        201072000, //8D
        202928000, //9A
        204640000, //9B
        206352000, //9C
        208064000, //9D
        209936000, //10A
        210096000, //10N
        211648000, //10B
        213360000, //10C
        215072000, //10D
        216928000, //11A
        217008000, //11N
        218640000, //11B
        220352000, //11C
        222064000, //11D
        223936000, //12A
        224096000, //12N
        225648000, //12B
        227360000, //12C
        229072000, //12D
        230784000, //13A
        232496000, //13B
        234208000, //13C
        235776000, //13D
        237488000, //13E
        239200000  //13F
    };

    RaonTunerInput* m_tuner;
    DabScannerObserver* m_scanner_observer;
    std::string m_ensemble_label;
    std::map<int,LISTED_SERVICE> m_listed_services;

    void ficData(uint8_t* data, int len);
    void FICChangeService(const LISTED_SERVICE&);
	void FICChangeEnsemble(const FIC_ENSEMBLE&);

	void FICChangeUTCDateTime(const FIC_DAB_DT&)  {};
	void FICDiscardedFIB() {};

public:
	DabScanner();
	~DabScanner();
};

#endif