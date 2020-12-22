#include "raon_tuner.h"
#include <iostream>

class CoutMscObserver: public MscObserver {
    void mscData(const std::vector<uint8_t>& data) {
        for (auto i: data)
            std::cout << i; 
    }
};

int main() {

	RaonTunerInput *tuner = new RaonTunerInput();
    CoutMscObserver *mscObserver = new CoutMscObserver();
	tuner->initialize();
    tuner->tuneFrequency(220352000);
    tuner->openSubChannel(8);
    tuner->setMscObserver(mscObserver);

    while(1) {
        tuner->readData();
    }
	delete tuner;
    return 0;
}
