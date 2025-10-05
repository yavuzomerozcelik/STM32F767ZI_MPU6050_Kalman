/*
 * kalmanfilter.h
 *
 *  Created on: Oct 5, 2025
 *      Author: PAVİLİON
 */

#ifndef INC_KALMANFILTER_H_
#define INC_KALMANFILTER_H_

#include <stdint.h>

typedef struct {
    float Q_angle; // Process noise variance for the accelerometer
    float Q_bias;  // Process noise variance for the gyro bias
    float R_measure; // Measurement noise variance
    float angle;   // The angle calculated by the Kalman filter
    float bias;    // The gyro bias calculated by the Kalman filter
    float P[2][2]; // Error covariance matrix
} Kalman_t;

void Kalman_Init(Kalman_t *kalman);
float Kalman_Update(Kalman_t *kalman, float newAngle, float newRate, float dt);

#endif /* INC_KALMANFILTER_H_ */

