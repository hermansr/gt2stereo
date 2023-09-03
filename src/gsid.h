#ifndef GSID_H
#define GSID_H

#define NUMSIDREGS 0x19
#define SIDWRITEDELAY 9 // lda $xxxx,x 4 cycles, sta $d400,x 5 cycles
#define SIDWAVEDELAY 4 // and $xxxx,x 4 cycles extra

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
  float distortionrate;
  float distortionpoint;
  float distortioncfthreshold;
  float type3baseresistance;
  float type3offset;
  float type3steepness;
  float type3minimumfetresistance;
  float type4k;
  float type4b;
  float voicenonlinearity;
} FILTERPARAMS;

typedef struct
{
  unsigned int freq;
  unsigned int pulse;
  unsigned int adsr;
  unsigned char wave;
  unsigned char envelope_counter;
} SID_STATE_VOICE;

typedef struct
{
  SID_STATE_VOICE voice[3];
  unsigned int filter_cutoff;
  unsigned char filter_res_rout;
  unsigned char filter_mode_volume;
} SID_STATE;

void sid_init(int speed, unsigned m, unsigned ntsc, unsigned interpolate, unsigned customclockrate, unsigned usefp);
int sid_fillbuffer(short *lptr, short *rptr, int samples);
unsigned char sid_getorder(unsigned char index);
void sid_readstate(SID_STATE* state, int num_sid);

#ifndef GSID_C
extern unsigned char sidreg[NUMSIDREGS];
extern unsigned char sidreg2[NUMSIDREGS];
extern FILTERPARAMS filterparams;
#endif

#ifdef __cplusplus
}
#endif

#endif
