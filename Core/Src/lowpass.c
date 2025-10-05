/*
 * lowpass.c
 *
 *  Created on: Sep 23, 2025
 *      Author: PAVİLİON
 */
#include "lowpass.h"

void lowPass_Init(lowPass *fir ){
	fir->inp =0.0f;
	fir->out[0]=0.0f;
    fir->out[1]=0.0f;
    fir->coffA=0.24f;

}
float lowPass_Update(lowPass *fir,float input){
	fir->inp=input;
	fir->out[0]=fir->out[1];
	fir->out[1]=fir->coffA*fir->inp + (1-fir->coffA)*fir->out[0];
 return fir->out[1];
}

