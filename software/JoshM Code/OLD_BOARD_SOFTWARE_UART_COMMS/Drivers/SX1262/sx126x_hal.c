#include "sx126x_hal.h"

/**
 * Radio data transfer - write
 */
sx126x_hal_status_t sx126x_hal_write( const void* context, const uint8_t* command, const uint16_t command_length,
                                      const uint8_t* data, const uint16_t data_length )
{
    // Switch to TX Mode
    HAL_GPIO_WritePin(SX126X_ANT_SW_GPIO_Port, SX126X_ANT_SW_Pin, GPIO_PIN_SET); // need to define ANT pins
  
    // uint32_t start = HAL_GetTick();  // Get the current tick count   

    // // Wait until SX1262 is not busy
    // while(sx126x_is_busy())
    // {
    //     if ((HAL_GetTick() - start) > SX126X_BUSY_TIMEOUT)
    //     {
    //         return SX126X_HAL_STATUS_ERROR;  // Return an error if timeout occurs
    //     }

    //     HAL_Delay(1) // Small delay to prevent system lockup
    // }

    // Pulls NSS pin low to start communication
    HAL_GPIO_WritePin(SX126X_NSS_GPIO_Port, SX126X_NSS_Pin, GPIO_PIN_RESET); 
    
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
    HAL_GPIO_WritePin(SX126X_NSS_GPIO_Port, SX126X_NSS_Pin, GPIO_PIN_RESET); 

    return SX126X_HAL_STATUS_OK;
}

/**
 * Radio data transfer - read
 */
sx126x_hal_status_t sx126x_hal_read( const void* context, const uint8_t* command, const uint16_t command_length,
                                     uint8_t* data, const uint16_t data_length )
{
    // Switch to RX mode
    HAL_GPIO_WritePin(SX126X_ANT_SW_GPIO_Port, SX126X_ANT_SW_Pin, GPIO_PIN_RESET); // need to define ANT pins

    // uint32_t start = HAL_GetTick();  // Get the current tick count    

    // // Wait until SX1262 is not busy
    // while(sx126x_is_busy())
    // {
    //     if ((HAL_GetTick() - start) > SX126X_BUSY_TIMEOUT)
    //     {
    //         return SX126X_HAL_STATUS_ERROR;  // Return an error if timeout occurs
    //     }

    //     HAL_Delay(1) // Small delay to prevent system lockup
    // }

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

/**
 * Reset the radio
 */
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

/**
 * Wake the radio up
 */
sx126x_hal_status_t sx126x_hal_wakeup( const void* context )
{
    // wakeup the radio
    uint8_t data = SX126X_NOP; // Send a NOP (0x00) command to wake up the chip
    HAL_SPI_Transmit(context, &data, 1, HAL_MAX_DELAY);

    return SX126X_HAL_STATUS_OK;
}
