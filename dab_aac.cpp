
#include "raon_tuner.h"
#include "dabplus_decoder.h"
#include <iostream>

//SuperframeFilter *filter;
DabPlusServiceComponentDecoder *dabplus_decoder;

class CoutMscObserver: public MscObserver {
    void mscData(const std::vector<uint8_t>& data) {
        dabplus_decoder->componentDataInput(data, false);
    }
};

int main() {

	RaonTunerInput *tuner = new RaonTunerInput();
    CoutMscObserver *mscObserver = new CoutMscObserver();
    // filter = new SuperframeFilter(nullptr, true, true);
    dabplus_decoder = new DabPlusServiceComponentDecoder();
    // dabplus_decoder->setSubchannelId(0x11);
    // dabplus_decoder->setAudioServiceComponentType(0x3F);
    dabplus_decoder->setSubchannelBitrate(40);

	tuner->initialize();
    tuner->tuneFrequency(222064000);
    tuner->openSubChannel(0x11);
    tuner->setMscObserver(mscObserver);
    // // setFrequency(222064000);
    // // clearAndSetupMscMemory();
    // // openSubChannel(0x11);

    while(1) {
        tuner->readData();
    }
	delete tuner;
    return 0;
}
