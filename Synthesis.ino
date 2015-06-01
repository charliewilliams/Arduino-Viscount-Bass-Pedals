
// Based on the known pedal state
// switch the synths on and off

#include <Oscil.h>

#define HIRES_SINWAVE 1 // no big deal which one to use
#if HIRES_SINWAVE
#include <tables/sin8192_int8.h>
#include <tables/smoothsquare8192_int8.h>
#include <tables/saw8192_int8.h>


static const int SIN_CELLS = 8192;
static const int8_t* SIN_DATA = SAW8192_DATA; //SMOOTHSQUARE8192_DATA; //SIN8192_DATA;
#else
#include <tables/sin2048_int8.h>
static const int SIN_CELLS = SIN2048_NUM_CELLS;
static const int8_t* SIN_DATA = SIN2048_DATA;
#endif

static const int MASTER_BITSHIFT = 5; // bigger numbers are quieter
Oscil <SIN_CELLS, AUDIO_RATE> oscils[NUM_KEYS];
float freqs[NUM_KEYS] = {261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440.000, 466.164, 493.883, 523.251};
//float freqs[NUM_KEYS] = {523.251, 493.883, 466.164, 440.000, 415.305, 391.995, 369.994, 349.228, 329.628, 311.127, 293.665, 277.183, 261.626};
float octave = 2.0; // bigger numbers are lower

void setupAudio() {

  for (int i = 0; i < NUM_KEYS; i++) {

    
    oscils[i] = Oscil <SIN_CELLS, AUDIO_RATE> (SIN_DATA);
    oscils[i].setFreq(freqs[NUM_KEYS - i - 1] / octave);
  }
}

int updateAudio() {

  int sample = 0.0;

  for (int i = 0; i < NUM_KEYS; i++) {

    unsigned int env = envelope[i].next();

//    if (env > 4)
      sample += oscils[i].next() * env;
  }

  return sample >> MASTER_BITSHIFT;
}
