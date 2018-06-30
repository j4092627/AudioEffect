#include <stdio.h>
#include <stdlib.h>
#include "baseEffect.h"
#include "sigFilter.h"
#include "lpf.h"
#include "hpf.h"

int MODE;

sigFilter::sigFilter(void) {;}
sigFilter::~sigFilter() {;}
void sigFilter::init(int mode) {
	MODE = mode;
}
void sigFilter::process(float *ibuf, float *obuf, int num_frames, int num_chn)
{
	/*Allocate ibuf signal into different channels*/
	float *ibufTemp[num_chn],*obufTemp[num_chn];
	for(int i=0;i<num_chn;i++)
	{
		ibufTemp[i]= (float*)malloc(num_frames*sizeof(float));
	}
	for(int i=0;i<num_frames;i++)
	{
		for(int j=0;j<num_chn;j++)
		{
			ibufTemp[j][i] = ibuf[i*num_chn+ j];
		}
	}
	/*LPF*/
	if(MODE == 1)
	{
		for (int i=0; i<num_chn; i++) {
			obufTemp[i] = (float*)malloc(num_frames*sizeof(float));
	        for (int j=0; j<num_frames; j++) {
	            obufTemp[i][j] = 0;
	            for(int k=0;k<28;k++)
	            {
	            	if((j-k)>=0)
	            	{
	            		obufTemp[i][j] += ibufTemp[i][j-k]*lpf[k]; 
	            	}
	            }
	        }
    	}
	}
	/*HPF*/
	if(MODE == 2)
	{
		for (int i=0; i<num_chn; i++) {
			obufTemp[i] = (float*)malloc(num_frames*sizeof(float));
	        for (int j=0; j<num_frames; j++) {
	            obufTemp[i][j] = 0;
	            for(int k=0;k<28;k++)
	            {
	            	if((j-k)>=0)
	            	{
	            		obufTemp[i][j] += ibufTemp[i][j-k]*hpf[k]; 
	            	}
	            }
	        }
    	}
	}
	/*Interleaved*/
	for(int i=0;i<num_frames;i++)
	{
		for(int j=0;j<num_chn;j++)
		{
			obuf[i*num_chn+j] = obufTemp[j][i];
		}
	}
}