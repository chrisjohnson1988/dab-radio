#include <iostream>
#include "dab_scanner.h"
#include "fic_decoder.h"

constexpr uint32_t DabScanner::DAB_FREQUENCIES[];

FICDecoder *decoder;
uint8_t collection_count = 0;

DabScanner::DabScanner(RaonTunerInput* tuner, DabScannerObserver* observer): m_tuner{tuner}, m_scanner_observer{observer} {
    decoder = new FICDecoder(this, false);
    m_tuner->setFicObserver(this);

    std::cout << "Creating Scanner" << std::endl;
};

DabScanner::~DabScanner() {
    std::cout << "Destroying Scanner" << std::endl;
};

void DabScanner::startFrequencyScan() {

    for(auto freq: DAB_FREQUENCIES) {
        // reset for new frequency
        collection_count = 0;
        decoder->Reset();
        m_tuner->tuneFrequency(freq);
        m_listed_services.clear();
        m_ensemble_label = "";
        
        while(collection_count < 200) {
            m_tuner->readData();
            collection_count++;
        }
        
        for(auto const& x : m_listed_services) {
            m_scanner_observer->serviceFound(
                freq, 
                m_ensemble_label, 
                FICDecoder::ConvertLabelToUTF8(x.second.label, nullptr), 
                x.second.audio_service.subchid, 
                x.second.audio_service.dab_plus,
                x.second.subchannel.bitrate
            );
        }
    }
};

void DabScanner::FICChangeService(const LISTED_SERVICE& service) {
    collection_count = 0;
    m_listed_services[service.sid] = service;
};

void DabScanner::FICChangeEnsemble(const FIC_ENSEMBLE& ensemble) {
    m_ensemble_label = FICDecoder::ConvertLabelToUTF8(ensemble.label, nullptr);
}

void DabScanner::ficData(uint8_t* data, int len) {
    decoder->Process(data, len);
}