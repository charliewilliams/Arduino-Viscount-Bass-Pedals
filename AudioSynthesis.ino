
// Based on the known pedal state
// switch the synths on and off

//#include <MozziGuts.h>
//#include <ADSR.h>
//
//#include <mozzi_rand.h>
//
//static const int MASTER_BITSHIFT = 5; // bigger numbers are quieter
//
//static const int NUM_CELLS = 8192;
//static const int8_t* SIN_DATA = SIN8192_DATA; //SIN8192_DATA; //SMOOTHSQUARE8192_DATA; //SIN8192_DATA; //SAW8192_DATA
//static const int8_t* SAW_DATA = SAW8192_DATA;
//
//Oscil <NUM_CELLS, AUDIO_RATE> oscil1, oscil2;
//float freqs[NUM_KEYS] = {261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440.000, 466.164, 493.883, 523.251};
//float octaveDetune = 1.005;
//float octave = 48.0; // bigger numbers are lower, must be a power of 2 for concert tuning
//
//ADSR <CONTROL_RATE, AUDIO_RATE> envelope[NUM_KEYS];
//ADSR <CONTROL_RATE, AUDIO_RATE> noiseEnvelope;
//
//void setupAudio() {
//
//  oscil1 = Oscil <NUM_CELLS, AUDIO_RATE> (SIN_DATA);
//  oscil2 = Oscil <NUM_CELLS, AUDIO_RATE> (SAW_DATA);
//
//  setupAudioControl();
//}
//
//void setupAudioControl() {
//
//  for (int i = 0; i < NUM_KEYS; i++) {
//    envelope[i] = ADSR<CONTROL_RATE, AUDIO_RATE>();// <CONTROL_RATE, AUDIO_RATE>();
//
//    envelope[i].setAttackLevel(255);
//    envelope[i].setDecayLevel(127);
//    envelope[i].setSustainLevel(64);
//    envelope[i].setReleaseLevel(0);
//    envelope[i].setTimes(50, 100, UINT_MAX, 750);
//    envelope[i].noteOff(); // or else you start with a bang
//  }
//
//  noiseEnvelope = ADSR<CONTROL_RATE, AUDIO_RATE>();
//
//  noiseEnvelope.setAttackLevel(255);
//  noiseEnvelope.setDecayLevel(10);
//  noiseEnvelope.setSustainLevel(0);
//  noiseEnvelope.setReleaseLevel(0);
//  noiseEnvelope.setTimes(50, 50, 50, 50);
//  noiseEnvelope.noteOff(); // or else you start with a bang
//}
//
//int updateAudio() {
//
//  int sample = 0;
//
//  for (int i = 0; i < NUM_KEYS; i++) {
//    unsigned int env = envelope[i].next();
//    int noise = rand(10) - 5;
//    sample += (oscil1.next() + oscil2.next() + noise) * env;
//  }
//
//  unsigned int nEnv = noiseEnvelope.next();
//  sample += rand(50) * nEnv - 25.;
//
//  return sample >> MASTER_BITSHIFT;
//}

