#include "catch2/catch_all.hpp"
#include <catch2/catch_session.hpp>
#include "ttcan_slave_driver.h"
#include "mock_target.h"
#include "fff.h"

// Define FFF globals
DEFINE_FFF_GLOBALS;
/* Create mock functions */
FAKE_VALUE_FUNC2(can_dl_status_t, can_ll_driver_timer_init, uint8_t, uint32_t);
FAKE_VALUE_FUNC1(can_dl_status_t, can_ll_driver_timer_start, uint8_t);
FAKE_VALUE_FUNC2(can_dl_status_t, can_ll_driver_timer_reload, uint8_t, uint64_t);
FAKE_VALUE_FUNC1(can_dl_status_t, can_ll_driver_can_init, uint8_t);
FAKE_VALUE_FUNC0(can_dl_status_t, can_ll_driver_nvm_init);
ttcan_timeslots_t slots[10];
static uint8_t tx_buffer[512];
static uint8_t rx_buffer[512];


TEST_CASE("init_function", "![init]")
{
    can_dl_ctx_t ctx;
    /* Todo! Populate the slots with info */
    ctx.num_of_time_slots  = 10;
    ctx.time_slots         = slots;
    ctx.can_port           = 0;
    ctx.timer_channel      = 0;
    ctx.rx_buffer          = rx_buffer;
    ctx.tx_buffer          = tx_buffer;
    ctx.rx_buf_len         = sizeof(rx_buffer);
    ctx.tx_buf_len         = sizeof(tx_buffer);
    can_dl_status_t status = can_dl_slave_init(&ctx);
    REQUIRE(status == CAN_DL_STATUS_OK);
    REQUIRE(can_ll_driver_timer_init_fake.call_count == 1);
    REQUIRE(can_ll_driver_nvm_init_fake.call_count == 1);
    REQUIRE(can_ll_driver_can_init_fake.call_count == 1);
    status = can_dl_slave_deinit(&ctx);
    REQUIRE(status == CAN_DL_STATUS_OK);
}

TEST_CASE("init_function", "![register_node]")
{
    can_dl_ctx_t ctx;
    /* Todo! Populate the slots with info */
    ctx.num_of_time_slots  = 10;
    ctx.time_slots         = slots;
    ctx.can_port           = 0;
    ctx.timer_channel      = 0;
    ctx.tick_frequency     = 1000;
    ctx.timer_channel      = 0;
    ctx.rx_buffer          = rx_buffer;
    ctx.tx_buffer          = tx_buffer;
    ctx.rx_buf_len         = sizeof(rx_buffer);
    ctx.tx_buf_len         = sizeof(tx_buffer);
    can_dl_status_t status = can_dl_slave_init(&ctx);
    REQUIRE(status == CAN_DL_STATUS_OK);
}

TEST_CASE("init_function", "![param_check]") {
    can_dl_ctx_t ctx;
    /* Todo! Populate the slots with info */
    ctx.num_of_time_slots  = 10;
    ctx.time_slots         = slots;
    ctx.can_port           = 0;
    ctx.timer_channel      = 0;
    ctx.tick_frequency     = 1000;
    ctx.timer_channel      = 0;
    ctx.rx_buffer          = rx_buffer;
    ctx.tx_buffer          = tx_buffer;
    ctx.rx_buf_len         = sizeof(rx_buffer);
    ctx.tx_buf_len         = sizeof(tx_buffer);
    can_dl_status_t status = can_dl_slave_init(&ctx);
    REQUIRE(status == CAN_DL_STATUS_OK);
    status = can_dl_slave_init(NULL);
    REQUIRE(status == CAN_DL_STATUS_INIT_ERR_PARAM_NULL);
    // A value Higher then our defined `CAN_DL_CAN_PERIPHERALS`
    ctx.can_port = 100; 
    status = can_dl_slave_init(&ctx);
    REQUIRE(status == CAN_DL_STATUS_INIT_ERR_INVALID_CAN);
    
}

int
main (int argc, char *argv[])
{
    // your setup ...

    int result = Catch::Session().run(argc, argv);

    // your clean-up...

    return result;
}