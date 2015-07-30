
// Based on the known pedal state
// switch the synths on and off


#include <Line.h>




static const int MASTER_BITSHIFT = 5; // bigger numbers are quieter


void setupAudio() {

  oscil1 = Oscil <NUM_CELLS, AUDIO_RATE> (SIN_DATA);
  oscil2 = Oscil <NUM_CELLS, AUDIO_RATE> (SAW_DATA);
}

int updateAudio() {

  int sample = 0;

  for (int i = 0; i < NUM_KEYS; i++) {
    unsigned int env = envelope[i].next();
    int noise = rand(10) - 5;
    sample += (oscil1.next() + oscil2.next() + noise) * env;
  }

  unsigned int nEnv = noiseEnvelope.next();
  sample += rand(50) * nEnv - 25.;

  return sample >> MASTER_BITSHIFT;
}

