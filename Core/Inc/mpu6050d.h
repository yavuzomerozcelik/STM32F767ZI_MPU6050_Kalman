/*
 * mpu6050d.h
 *
 *  Created on: Sep 23, 2025
 *      Author: PAVİLİON
 */

#ifndef INC_MPU6050D_H_
#define INC_MPU6050D_H_

#include "stm32f7xx_hal.h"
#include <stdint.h>

/* MPU6050 I2C adresi (8-bit format, HAL için) */
#define MPU6050_ADDR 0xD0
#define MPU6050_DEVICE_ID 0x68

#define WHO_AM_I_REG       0x75
#define PWR_MGMT_1_REG     0x6B
#define SMPLRT_DIV_REG     0x19
#define ACCEL_CONFIG_REG   0x1C
#define GYRO_CONFIG_REG    0x1B
#define ACCEL_XOUT_H       0x3B
#define GYRO_XOUT_H_REG    0x43
#define TEMP_OUT_H_REG     0x41

typedef struct{
	I2C_HandleTypeDef *hi2c;
	int16_t x_axis, y_axis,z_axis;
	int16_t gyro_x ,gyro_y ,gyro_z;
	int16_t temp;

}MPU6050d;

uint8_t MPU6050D_Init( MPU6050d *dev ,I2C_HandleTypeDef *I2C_Handle);
uint8_t controlWhoIam(MPU6050d *dev);

HAL_StatusTypeDef MPU6050D_ReadAccelameter(MPU6050d *dev);
HAL_StatusTypeDef MPU6050D_ReadGyroscope(MPU6050d *dev);
HAL_StatusTypeDef MPU6050D_ReadTempature(MPU6050d *dev);

HAL_StatusTypeDef ReadRegister(MPU6050d *dev ,uint8_t reg ,uint8_t *data);
HAL_StatusTypeDef ReadRegisters(MPU6050d *dev ,uint8_t reg ,uint8_t *data,uint8_t length);

HAL_StatusTypeDef WriteRegister(MPU6050d *dev ,uint8_t reg ,uint8_t *data);


#endif /* INC_MPU6050D_H_ */
