#ifndef MANIKIN_DL_TYPES_H
#define MANIKIN_DL_TYPES_H
#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>
    typedef union
    {
        struct
        {
            uint8_t  id;
            uint16_t slot_type;
        } bit;
        uint32_t raw : 24;
    } ttcan_timeslots_t;

    typedef enum
    {
        CAN_DL_STATUS_OK,
        CAN_DL_STATUS_INIT_ERR_PARAM_NULL,
        CAN_DL_STATUS_INIT_ERR_INVALID_CAN,
        CAN_DL_STATUS_INIT_ERR_INVALID_TIMER,
        CAN_DL_STATUS_INIT_ERR_INVALID_TX_BUF,
        CAN_DL_STATUS_INIT_ERR_INVALID_RX_BUF,
        CAN_DL_STATUS_INIT_ERR_CAN_FAIL,
        CAN_DL_STATUS_INIT_ERR_TIMER_FAIL,
        CAN_DL_STATUS_INIT_ERR_NVM_FAIL 
    } can_dl_status_t;


    typedef enum {
        TTCAN_DATA_ENTRY_READ,
        TTCAN_DATA_ENTRY_WRITE
    } ttcan_data_entry_type_t;


    typedef struct {
        uint8_t node_id;
        uint16_t update_rate;
        ttcan_data_entry_type_t entry_type;
    } ttcan_data_entry_t;

#ifdef __cplusplus
}
#endif

#endif /* MANIKIN_DL_TYPES_H */