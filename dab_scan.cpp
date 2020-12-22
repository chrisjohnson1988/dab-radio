#include "raon_tuner.h"
#include "dab_scanner.h"
#include "m3u_writer.h"

int main() {

	M3UWriter *m3u_writer = new M3UWriter();
	RaonTunerInput *tuner = new RaonTunerInput();
	tuner->initialize();
	DabScanner *scanner = new DabScanner(tuner, m3u_writer);
	scanner->startFrequencyScan();

	delete tuner;
    return 0;
}
