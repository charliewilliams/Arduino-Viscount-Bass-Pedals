
// Based on the known pedal state
// switch the synths on and off

#include <Oscil.h>
#include <tables/sin2048_int8.h>

Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> oscils[NUM_KEYS];
float freqs[NUM_KEYS] = {261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440.000, 466.164, 493.883, 523.251};
float octave = 2.0;

// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
//Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);

void setupAudio() {

  for (int i = 0; i < NUM_KEYS; i++) {
    oscils[i] = Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> (SIN2048_DATA);
    oscils[i].setFreq(freqs[i] / octave);
  }
}

int updateAudio() {
  // this would make more sense with a higher resolution signal
  // but still benefits from using HIFI to avoid the 16kHz pwm noise

  int sample = 0;

  for (int i = 0; i < NUM_KEYS; i++) {

    Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> oscar = oscils[i];

    sample |= oscar.next() << 6; // 8 bits scaled up to 14 bits
  }

  return sample;
}
