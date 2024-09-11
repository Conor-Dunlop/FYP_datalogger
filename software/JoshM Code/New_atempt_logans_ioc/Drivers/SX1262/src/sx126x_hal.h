/**
 * @file      sx126x_hal.h
 *
 * @brief     Hardware Abstraction Layer for SX126x
 *
 * The Clear BSD License
 * Copyright Semtech Corporation 2021. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (subject to the limitations in the disclaimer
 * below) provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Semtech corporation nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY
 * THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
 * NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SEMTECH CORPORATION BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SX126X_HAL_H
#define SX126X_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include <stdint.h>
#include <stdbool.h>

#include "stm32g4xx_hal.h"
#include "stm32g4xx_hal_gpio.h"
#include "stm32g4xx_hal_spi.h"
#include "gpio.c"

#include "sx126x.c"
#include "sx126x.h"
#include "sx126x_hal.h"
#include "sx126x_regs.h"
#include "spi.h"


// SX1262 pins defined in gpio.c

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC MACROS -----------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC CONSTANTS --------------------------------------------------------
 */

/**
 * @brief Write this to SPI bus while reading data, or as a dummy/placeholder
 */
#define SX126X_NOP ( 0x00 )

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC TYPES ------------------------------------------------------------
 */

typedef enum sx126x_hal_status_e
{
    SX126X_HAL_STATUS_OK    = 0,
    SX126X_HAL_STATUS_ERROR = 3,
} sx126x_hal_status_t;

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS PROTOTYPES ---------------------------------------------
 */

/**
 * Radio data transfer - write
 *
 * @remark Shall be implemented by the user
 *
 * @param [in] context          Radio implementation parameters
 * @param [in] command          Pointer to the buffer to be transmitted
 * @param [in] command_length   Buffer size to be transmitted
 * @param [in] data             Pointer to the buffer to be transmitted
 * @param [in] data_length      Buffer size to be transmitted
 *
 * @returns Operation status
 */
sx126x_hal_status_t sx126x_hal_write( const void* context, const uint8_t* command, const uint16_t command_length,
                                      const uint8_t* data, const uint16_t data_length )
{
    // Switch to TX Mode
    HAL_GPIO_WritePin(SX126X_ANT_SW_GPIO_Port, SX126X_ANT_SW_Pin, GPIO_PIN_SET); // need to define ANT pins
  
    uint32_t start = HAL_GetTick();  // Get the current tick count   

    // Wait until SX1262 is not busy
    while(sx126x_is_busy())
    {
        if ((HAL_GetTick() - start) > SX126X_BUSY_TIMEOUT)
        {
            return SX126X_HAL_STATUS_ERROR;  // Return an error if timeout occurs
        }

        HAL_Delay(1) // Small delay to prevent system lockup
    }

    // Pulls NSS pin low to start communication
    HAL_GPIO_WritePin(SX126X_NSS_GPIO_Port, SX126X_NSS_PIN, GPIO_PIN_RESET); 
    
    // Assuming context contains the SPI handle (e.g., SPI_HandleTypeDef)
    HAL_StatusTypeDef hal_status;

    // Send the command
    hal_status = HAL_SPI_Transmit(context, (uint8_t*)command, command_length, HAL_MAX_DELAY);
    if (hal_status != HAL_OK) return SX126X_HAL_STATUS_ERROR;

    // Send the data
    if (data != NULL && data_length > 0)
    {
        hal_status = HAL_SPI_Transmit(context, (uint8_t*)data, data_length, HAL_MAX_DELAY);
        if (hal_status != HAL_OK) return SX126X_HAL_STATUS_ERROR;
    }

    // Pulls NSS pin high to end communication   
    HAL_GPIO_WritePin(SX126X_NSS_GPIO_Port, SX126X_NSS_PIN, GPIO_PIN_RESET); 

    return SX126X_HAL_STATUS_OK;
}



sx126x_hal_status_t sx126x_hal_read( const void* context, const uint8_t* command, const uint16_t command_length,
                                     uint8_t* data, const uint16_t data_length )
{
    // Switch to RX mode
    HAL_GPIO_WritePin(SX126X_ANT_SW_GPIO_Port, SX126X_ANT_SW_Pin, GPIO_PIN_RESET); // need to define ANT pins

    uint32_t start = HAL_GetTick();  // Get the current tick count    

    // Wait until SX1262 is not busy
    while(sx126x_is_busy())
    {
        if ((HAL_GetTick() - start) > SX126X_BUSY_TIMEOUT)
        {
            return SX126X_HAL_STATUS_ERROR;  // Return an error if timeout occurs
        }

        HAL_Delay(1) // Small delay to prevent system lockup
    }

    // Pulls NSS pin low to start communication
    HAL_GPIO_WritePin(SX126X_NSS_GPIO_Port, SX126X_NSS_Pin, GPIO_PIN_RESET);


    // Assuming context contains the SPI handle (e.g., SPI_HandleTypeDef)
    HAL_StatusTypeDef hal_status;

    // Send the command
    hal_status = HAL_SPI_Transmit(context, (uint8_t*)command, command_length, HAL_MAX_DELAY);
    if (hal_status != HAL_OK) return SX126X_HAL_STATUS_ERROR;

    // Receive the data
    hal_status = HAL_SPI_Receive(context, data, data_length, HAL_MAX_DELAY);
    if (hal_status != HAL_OK) return SX126X_HAL_STATUS_ERROR;

    // Pulls NSS pin high to end communication  
    HAL_GPIO_WritePin(SX126X_NSS_GPIO_Port, SX126X_NSS_Pin, GPIO_PIN_SET);

    return SX126X_HAL_STATUS_OK;
}


sx126x_hal_status_t sx126x_hal_reset( const void* context ) // written
{
    // reset the radio
    // Assuming context contains the reset pin information (e.g., GPIO port and pin)
    // STM32 HAL function to reset the GPIO pin
    HAL_GPIO_WritePin(SX126X_RESET_GPIO_Port, SX126X_RESET_Pin, GPIO_PIN_RESET); // define pins
    HAL_Delay(1); // Delay for 1 ms
    HAL_GPIO_WritePin(SX126X_RESET_GPIO_Port, SX126X_RESET_Pin, GPIO_PIN_SET);
    HAL_Delay(6); // Delay for 6 ms to allow the chip to reset properly
    
    return SX126X_HAL_STATUS_OK;
}
sx126x_hal_status_t sx126x_hal_wakeup( const void* context )
{
    // wakeup the radio
    uint8_t data = SX126X_NOP; // Send a NOP (0x00) command to wake up the chip
    HAL_SPI_Transmit(context, &data, 1, HAL_MAX_DELAY);

    return SX126X_HAL_STATUS_OK;
}


#ifdef __cplusplus
}
#endif

#endif  // SX126X_HAL_H

/* --- EOF ------------------------------------------------------------------ */
