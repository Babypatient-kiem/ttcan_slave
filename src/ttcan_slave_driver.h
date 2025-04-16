#ifndef TTCAN_SLAVE_DRIVER_H
#define TTCAN_SLAVE_DRIVER_H
#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>
#include <stddef.h>
#include "private/ttcan_dl_types.h"
#include <lwrb/lwrb.h>

    typedef struct
    {
        uint8_t            node_id;
        uint8_t            can_port;
        uint8_t            timer_channel;
        ttcan_timeslots_t *time_slots;
        size_t             num_of_time_slots;
        uint16_t           curr_timeslot;
        uint32_t           tick_frequency;
        size_t             rx_buf_len;
        size_t             tx_buf_len;
        uint8_t           *rx_buffer;
        uint8_t           *tx_buffer;
        lwrb_t             tx_msgs;
        lwrb_t             rx_msgs;

    } can_dl_ctx_t;

    can_dl_status_t can_dl_slave_init(can_dl_ctx_t *ctx);
    size_t          can_dl_slave_transmit(const can_dl_ctx_t      *ctx,
                                          const ttcan_timeslots_t *time_slot,
                                          const uint8_t           *data,
                                          size_t                   len);
    size_t          can_dl_slave_receive(const can_dl_ctx_t      *ctx,
                                         const ttcan_timeslots_t *time_slot,
                                         uint8_t                 *data,
                                         size_t                   len);
    can_dl_status_t can_dl_slave_deinit(can_dl_ctx_t *ctx);

    void can_dl_slave_cb_handler(can_dl_ctx_t *ctx,
                                 uint8_t      *rx_data,
                                 uint8_t       len);
    
    void can_dl_slave_new_slot_handler(can_dl_ctx_t *ctx);
#ifdef __cplusplus
}
#endif

#endif /* TTCAN_SLAVE_DRIVER_H */
