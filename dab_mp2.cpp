#include "raon_tuner.h"
#include <iostream>

class CoutMscObserver: public MscObserver {
    void mscData(const std::vector<uint8_t>& data) {
        for (auto i: data)
            std::cout << i; 
    }
};

void usage() {
  std::cout << "Usage: dab_mp2 frequency subchannel\n"
               "Examples: \n\n"
               "  dab_mp2 225648000 1 # Tune in to BBC Radio 1\n"
               "\n"
               "Arguments:\n"
               "  frequency\n"
               "     The dab frequency to tune in to in Hz. e.g 225648000\n"
               "  subchannel\n"
               "     The subchannel on the frequency to receive\n"
               "\n";
}

int main(int argc, char *argv[]) {

    if(argc != 3) {
        usage();
        return EXIT_FAILURE;
    }

	RaonTunerInput *tuner = new RaonTunerInput();
    CoutMscObserver *mscObserver = new CoutMscObserver();
	tuner->initialize();
    tuner->tuneFrequency(atoi(argv[1]));
    tuner->openSubChannel(atoi(argv[2]));
    tuner->setMscObserver(mscObserver);

    while(1) {
        tuner->readData();
    }
	delete tuner;
    return EXIT_SUCCESS;
}
