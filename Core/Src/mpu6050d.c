/*
 * mpu6050d.c
 *
 *  Created on: Sep 23, 2025
 *      Author: Yavuz Ömer Özçelik
 */

#ifndef SRC_MPU6050D_C_
#define SRC_MPU6050D_C_
#include "mpu6050d.h"

uint8_t MPU6050D_Init( MPU6050d *dev ,I2C_HandleTypeDef *I2C_Handle){
	dev->hi2c =I2C_Handle;

	uint8_t data ,control;
	uint8_t err_numb=0;

	if(ReadRegister(dev,WHO_AM_I_REG ,&control ) != HAL_OK){
		err_numb ++;

	}
	if(control != MPU6050_DEVICE_ID ){
		err_numb ++;
		return 1;
	}

	data=0x0;
	if(WriteRegister(dev,PWR_MGMT_1_REG ,&data) != HAL_OK){
		err_numb++;
	}


	data=0x0; //  sample rate en hızlısı olsun
	if(WriteRegister(dev,SMPLRT_DIV_REG ,&data) != HAL_OK){
		err_numb++;
	}

	data=0x0;  // +-2g
	if(WriteRegister(dev,ACCEL_CONFIG_REG ,&data) != HAL_OK){
			err_numb++;
		}

	data=0x0; //(+-250)
	if(WriteRegister(dev,GYRO_CONFIG_REG ,&data) != HAL_OK){
				err_numb++;
			}

	return err_numb;
}
HAL_StatusTypeDef MPU6050D_ReadAccelameter(MPU6050d *dev){
	HAL_StatusTypeDef status;
    uint8_t acc_buffer[6];
	status=ReadRegisters(dev,ACCEL_XOUT_H ,acc_buffer,6);
	int16_t x_raw= (int16_t)(acc_buffer[0]<<8) | acc_buffer[1];
	int16_t y_raw= (int16_t )(acc_buffer[2]<<8) | acc_buffer[3];
	int16_t  z_raw= (int16_t )(acc_buffer[4]<<8) | acc_buffer[5];
	dev->x_axis = x_raw/16384 *9.81;
	dev->y_axis = y_raw/16384 *9.81;
	dev->z_axis = z_raw/16384 *9.81;
	return status;
}
HAL_StatusTypeDef MPU6050D_ReadGyroscope(MPU6050d *dev){
	HAL_StatusTypeDef status;
	uint8_t acc_buffer[6];
	status=ReadRegisters(dev,GYRO_CONFIG_REG ,acc_buffer,6);
	int16_t gyrox_raw= (int16_t)(acc_buffer[0]<<8) | acc_buffer[1];
	int16_t gyroy_raw= (int16_t)(acc_buffer[2]<<8) | acc_buffer[3];
	int16_t gyroz_raw= (int16_t)(acc_buffer[4]<<8) | acc_buffer[5];
	dev->gyro_x = gyrox_raw/16384 *9.81;
	dev->gyro_y = gyroy_raw/16384 *9.81;
	dev->gyro_z = gyroz_raw/16384 *9.81;
	return status;
}
HAL_StatusTypeDef MPU6050D_ReadTempature(MPU6050d *dev){
	HAL_StatusTypeDef status;
	uint8_t acc_buffer[2];
    status=ReadRegisters(dev,TEMP_OUT_H_REG ,acc_buffer,2);
    int16_t temp_raw= (int16_t)(acc_buffer[0]<<8) | acc_buffer[1];
    dev->temp = temp_raw /340 +36.53;

    return status;
}
uint8_t controlWhoIam(MPU6050d *dev){
	uint8_t data;
	ReadRegister(dev, WHO_AM_I_REG , &data);
	return data;
}

HAL_StatusTypeDef ReadRegister(MPU6050d *dev ,uint8_t reg ,uint8_t *data){
	return HAL_I2C_Mem_Read(dev->hi2c,  MPU6050_ADDR , reg, I2C_MEMADD_SIZE_8BIT,data,1, HAL_MAX_DELAY);
}
HAL_StatusTypeDef ReadRegisters(MPU6050d *dev ,uint8_t reg ,uint8_t *data,uint8_t length){
	return HAL_I2C_Mem_Read(dev->hi2c,  MPU6050_ADDR , reg, I2C_MEMADD_SIZE_8BIT,data,length, HAL_MAX_DELAY);
}

HAL_StatusTypeDef WriteRegister(MPU6050d *dev ,uint8_t reg ,uint8_t *data){
	return HAL_I2C_Mem_Write(dev->hi2c,  MPU6050_ADDR , reg, I2C_MEMADD_SIZE_8BIT,data, 1 , HAL_MAX_DELAY);
}

#endif /* SRC_MPU6050D_C_ */
