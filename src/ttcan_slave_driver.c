#include "ttcan_slave_driver.h"
#include "config_ttcan.h"

typedef union
{
    struct
    {
        uint8_t  prefix_id : 1;
        uint16_t schedule_id : 14;
        uint16_t data_id : 14;
    } bit;
    uint32_t raw : 29;
} ttcan_frame_header_t;

typedef union
{
    uint8_t  bytes[8];
    uint64_t timestamp;
} ttcan_timestamp_t;


enum schedule_id
{
    DATA_ID_SYNC       = 0,
    DATA_ID_ARB = 1,
    DATA_ARB_DATA      = 7,
};

static inline uint8_t
param_check (const size_t val, const size_t min, const size_t max)
{
    return ((val > max) || (val < min));
}

static inline can_dl_status_t
check_init_params (can_dl_ctx_t *ctx)
{
    if (NULL == ctx)
    {
        return CAN_DL_STATUS_INIT_ERR_PARAM_NULL;
    }
    if (param_check(ctx->can_port, 0, CAN_DL_CAN_PERIPHERALS))
    {
        return CAN_DL_STATUS_INIT_ERR_INVALID_CAN;
    }
    if (param_check(ctx->timer_channel, 0, CAN_DL_TIMER_CHANNELS))
    {
        return CAN_DL_STATUS_INIT_ERR_INVALID_TIMER;
    }
    if (ctx->tx_buffer == NULL || param_check(ctx->tx_buf_len, 8, SIZE_MAX-1)) {
        return CAN_DL_STATUS_INIT_ERR_INVALID_TX_BUF;
    }
    if(ctx->rx_buffer == NULL || param_check(ctx->tx_buf_len, 8, SIZE_MAX-1)) {
        return CAN_DL_STATUS_INIT_ERR_INVALID_RX_BUF;
    }
    return CAN_DL_STATUS_OK;
}

can_dl_status_t
can_dl_slave_init (can_dl_ctx_t *ctx)
{
    can_dl_status_t status = check_init_params(ctx);
    if (CAN_DL_STATUS_OK != status)
    {
        return status;
    }
    ctx->curr_timeslot = 0;
    lwrb_init(&(ctx->rx_msgs), ctx->rx_buffer, ctx->rx_buf_len);
    lwrb_init(&(ctx->tx_msgs), ctx->tx_buffer, ctx->tx_buf_len);
    status = CAN_LL_DRIVER_CAN_INIT(ctx->can_port);
    if (CAN_DL_STATUS_OK != status)
    {
        return status;
    }
    status = CAN_LL_DRIVER_TIMER_INIT(ctx->timer_channel, ctx->tick_frequency);
    if (CAN_DL_STATUS_OK != status)
    {
        return status;
    }
    status = CAN_LL_DRIVER_TIMER_START(ctx->timer_channel);
    if (CAN_DL_STATUS_OK != status)
    {
        return status;
    }
    status = CAN_LL_DRIVER_NVM_INIT();

    return status;
}

size_t
can_dl_slave_transmit (const can_dl_ctx_t      *ctx,
                       const ttcan_timeslots_t *time_slot,
                       const uint8_t           *data,
                       size_t                   len)
{
    return 0;
}

size_t
can_dl_slave_receive (const can_dl_ctx_t      *ctx,
                      const ttcan_timeslots_t *time_slot,
                      uint8_t                 *data,
                      size_t                   len)
{
    return 0;
}

can_dl_status_t
can_dl_slave_deinit (can_dl_ctx_t *ctx)
{
    return CAN_DL_STATUS_OK;
}

void
can_dl_slave_cb_handler (can_dl_ctx_t *ctx, uint8_t *rx_data, uint8_t len)
{
    ttcan_frame_header_t frame_header;
    if (ctx == NULL || rx_data == NULL || len > 9)
    {
        return;
    }
    frame_header.raw = rx_data[0];
    switch (frame_header.bit.schedule_id)
    {
        case DATA_ID_SYNC: {
            ttcan_timestamp_t tm;
            if (len != 9)
            {
                return;
            }
            for (uint8_t i = 0; i < len; i++)
            {
                tm.bytes[i] = rx_data[i];
            }
            CAN_LL_DRIVER_TIMER_RELOAD(ctx->timer_channel, tm.timestamp);
        }
        case DATA_ID_ARB: {
            char sensor_msg[CAN_DL_DEFAULT_FRAME_SIZE];
            lwrb_peek(&(ctx->tx_msgs), 0, sensor_msg, CAN_DL_DEFAULT_FRAME_SIZE);
        }
    }
}

void can_dl_slave_new_slot_handler(can_dl_ctx_t *ctx) {
    if(ctx->curr_timeslot < ctx->num_of_time_slots) {
        ctx->curr_timeslot++;
    } else {
        ctx->curr_timeslot = 0;
    }
}