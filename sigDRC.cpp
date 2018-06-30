#include "baseEffect.h"
#include "sigDRC.h"

sigDRC::sigDRC(void) {;}
sigDRC::~sigDRC() {;}
void sigDRC::init(int mode) {;}
void sigDRC::process(float *ibuf, float *obuf, int num_frames, int num_chn)
{
	int sgn;
	float abs_buf;
	float a[2]={3,1/3};
	float xlo[2]={0.0,0.25};
	float b[2]={0,0.75};

    /* copy input to output */
    for (int i=0; i<num_frames; i++) {
        for (int j=0; j<num_chn; j++) {
            //obuf[i*num_chn + j] = ibuf[i*num_chn +j];
            if(ibuf[i*num_chn + j] < -0.25 || ibuf[i*num_chn + j] > 0.25)
            {
            	sgn = (ibuf[i*num_chn + j]<0)? -1:1;
            	abs_buf = sgn*ibuf[i*num_chn + j];
				obuf[i*num_chn + j] = sgn*(a[1]*(abs_buf-xlo[1])+b[1]);
            }
            else
            {
            	sgn = (ibuf[i*num_chn + j]<0)? -1:1;
            	abs_buf = sgn*ibuf[i*num_chn + j];
				obuf[i*num_chn + j] = sgn*(a[0]*(abs_buf-xlo[0])+b[0]);
            }
        }
    }
}
