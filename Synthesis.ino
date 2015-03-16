
// Based on the known pedal state
// switch the synths on and off

#include <Oscil.h>
//#include <tables/sin2048_int8.h>
#include <tables/sin8192_int8.h>

// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
//Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);

static const float MASTER_GAIN = 0.02;

//static const int SIN_CELLS = SIN2048_NUM_CELLS;
//static const int8_t* SIN_DATA = SIN2048_DATA;
static const int SIN_CELLS = 8192;
static const int8_t* SIN_DATA = SIN8192_DATA;

Oscil <SIN_CELLS, AUDIO_RATE> oscils[NUM_KEYS];
float freqs[NUM_KEYS] = {261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440.000, 466.164, 493.883, 523.251};
float octave = 2.0;

void setupAudio() {

  for (int i = 0; i < NUM_KEYS; i++) {

    oscils[i] = Oscil <SIN_CELLS, AUDIO_RATE> (SIN_DATA);
    oscils[i].setFreq(freqs[i] / octave);
  }
}

int updateAudio() {

  int sample = 0.0;

  for (int i = 0; i < NUM_KEYS; i++) {
    sample += oscils[i].next() * envelope[i].next();
  }

  return sample * MASTER_GAIN;
}
