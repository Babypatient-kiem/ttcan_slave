#ifndef CONFIG_CAN_DL_H
#define CONFIG_CAN_DL_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "mock_target.h"

#define CAN_DL_CAN_PERIPHERALS 2
#define CAN_DL_TIMER_CHANNELS 16
#define CAN_DL_DEFAULT_FRAME_SIZE 16+2 /* MAX SENSOR SAMPLE SIZE + 2 bytes for header*/


/**
 * @brief CAN module functions
 */
#define CAN_LL_DRIVER_CAN_INIT(peripheral) can_ll_driver_can_init(peripheral)
#define CAN_LL_DRIVER_CAN_WRITE(peripheral, data, len) \
    can_ll_driver_can_write(peripheral, data, len)
#define CAN_LL_DRIVER_CAN_READ(peripheral, data, len) \
    can_ll_driver_can_read(peripheral, data, len)
#define CAN_LL_DRIVER_CAN_DEINIT(peripheral) \
    can_ll_driver_can_deinit(peripheral)

/**
 * @brief Non-volatile memory functions
 */
#define CAN_LL_DRIVER_NVM_INIT() can_ll_driver_nvm_init()
#define CAN_LL_DRIVER_NVM_WRITE(index, data, len) \
    can_ll_driver_nvm_write(index, data, len)
#define CAN_LL_DRIVER_NVM_READ(index, data, len) \
    can_ll_driver_nvm_read(index, data, len)
#define CAN_LL_DRIVER_NVM_DEINIT() can_ll_driver_nvm_deinit()

/**
 * @brief Timer module functions
 */
#define CAN_LL_DRIVER_TIMER_INIT(peripheral, frequency) \
    can_ll_driver_timer_init(peripheral, frequency)
#define CAN_LL_DRIVER_TIMER_START(peripheral) \
    can_ll_driver_timer_start(peripheral)
#define CAN_LL_DRIVER_TIMER_UPDATE(peripheral) \
    can_ll_driver_timer_update(peripheral)
#define CAN_LL_DRIVER_TIMER_RELOAD(peripheral, reload) \
    can_ll_driver_timer_reload(peripheral, reload)
#define CAN_LL_DRIVER_TIMER_DELAY(peripheral) \
    can_ll_driver_timer_delay(peripheral)
#define CAN_LL_DRIVER_TIMER_STOP(peripheral) \
    can_ll_driver_timer_stop(peripheral)

#ifdef __cplusplus
}
#endif
#endif /* CONFIG_CAN_DL_H */