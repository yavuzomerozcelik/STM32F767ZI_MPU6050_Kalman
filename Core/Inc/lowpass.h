/*
 * lowpass.h
 *
 *  Created on: Sep 23, 2025
 *      Author: PAVİLİON
 */

#ifndef INC_LOWPASS_H_
#define INC_LOWPASS_H_

typedef struct{
	float coffA;
	float inp, out[2];

}lowPass;

void lowPass_Init(lowPass *fir );
float lowPass_Update(lowPass *fir,float inp);


#endif /* INC_LOWPASS_H_ */
