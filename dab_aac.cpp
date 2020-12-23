
#include "raon_tuner.h"
#include "dabplus_decoder.h"
#include <iostream>

DabPlusServiceComponentDecoder *dabplus_decoder;

class CoutMscObserver: public MscObserver {
    void mscData(const std::vector<uint8_t>& data) {
        dabplus_decoder->componentDataInput(data, false);
    }
};

void usage() {
  std::cout << "Usage: dab_aac frequency subchannel bitrate\n"
               "Examples: \n\n"
               "  dab_aac 222064000 17 40 # Tune in to Capital XTRA\n"
               "\n"
               "Arguments:\n"
               "  frequency\n"
               "     The dab frequency to tune in to in Hz. e.g 225648000\n"
               "  subchannel\n"
               "     The subchannel on the frequency to receive\n"
               "  bitrate\n"
               "     The bitrate dab+ stream\n"
               "\n";
}

int main(int argc, char *argv[]) {

    if(argc != 4) {
        usage();
        return EXIT_FAILURE;
    }

	RaonTunerInput *tuner = new RaonTunerInput();
    CoutMscObserver *mscObserver = new CoutMscObserver();
    dabplus_decoder = new DabPlusServiceComponentDecoder();
    dabplus_decoder->setSubchannelBitrate(atoi(argv[3]));

	tuner->initialize();
    tuner->tuneFrequency(atoi(argv[1]));
    tuner->openSubChannel(atoi(argv[2]));
    tuner->setMscObserver(mscObserver);

    while(1) {
        tuner->readData();
    }
	delete tuner;
    return 0;
}
