#include "catch2/catch_all.hpp"
#include <catch2/catch_session.hpp>
#include <fakes/fake_handlers.h>
#include <chrono>
#include <thread>

DEFINE_FFF_GLOBALS;
ttcan_timeslots_t slots[10];
static uint8_t tx_buffer[512];
static uint8_t rx_buffer[512];

TEST_CASE("master_node", "![sync]")
{
    setup_fake_can();
    setup_fake_nvm();
    setup_fake_timer();
    can_dl_ctx_t ctx;
    /* Todo! Populate the slots with info */
    ctx.num_of_time_slots  = 10;
    ctx.time_slots         = slots;
    ctx.can_port           = 0;
    ctx.timer_channel      = 0;
    ctx.tick_frequency     = 100;
    ctx.rx_buffer          = rx_buffer;
    ctx.tx_buffer          = tx_buffer;
    ctx.rx_buf_len         = sizeof(rx_buffer);
    ctx.tx_buf_len         = sizeof(tx_buffer);
    can_dl_status_t status = can_dl_slave_init(&ctx);
    REQUIRE(status == CAN_DL_STATUS_OK);
    REQUIRE(can_ll_driver_timer_init_fake.call_count == 1);
    REQUIRE(can_ll_driver_timer_start_fake.call_count == 1);
    REQUIRE(can_ll_driver_nvm_init_fake.call_count == 1);
    REQUIRE(can_ll_driver_can_init_fake.call_count == 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    size_t tick = get_timer_tick();
    REQUIRE(tick > 9);
    status = can_dl_slave_deinit(&ctx);
    REQUIRE(status == CAN_DL_STATUS_OK);
}


int
main (int argc, char *argv[])
{
    // your setup ...

    int result = Catch::Session().run(argc, argv);

    // your clean-up...

    return result;
}