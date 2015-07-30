
// Based on the known pedal state
// switch the synths on and off

#include <Oscil.h>
#include <Line.h>
#include <tables/sin8192_int8.h>
#include <tables/smoothsquare8192_int8.h>
#include <tables/saw8192_int8.h>

static const int NUM_CELLS = 8192;
static const int8_t* WAVE_DATA = SIN8192_DATA; //SMOOTHSQUARE8192_DATA; //SIN8192_DATA; //SAW8192_DATA
static const int8_t* MOD_DATA = SAW8192_DATA;

static const int MASTER_BITSHIFT = 5; // bigger numbers are quieter
Oscil <NUM_CELLS, AUDIO_RATE> oscil1, oscil2;
float freqs[NUM_KEYS] = {261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440.000, 466.164, 493.883, 523.251};
float octaveDetune = 1.005;
float octave = 3.0; // bigger numbers are lower

void setupAudio() {

oscil1 = Oscil <NUM_CELLS, AUDIO_RATE> (WAVE_DATA);
oscil2 = Oscil <NUM_CELLS, AUDIO_RATE> (MOD_DATA);
}

int updateAudio() {

  int sample = 0;

  for (int i = 0; i < NUM_KEYS; i++) {

    unsigned int env = envelope[i].next();
    sample += (oscils[i].next() + modulators[i].next() + rand(10)) * env;
  }

  unsigned int nEnv = noiseEnvelope.next();
  sample += rand(100) * nEnv - 50.;

  return (sample) >> MASTER_BITSHIFT;
}

