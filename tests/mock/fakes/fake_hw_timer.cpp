#include "fake_handlers.h"
#include <thread>
#include <atomic>
#include <chrono>
#include <functional>
#include <memory>
#include <stdio.h>

DEFINE_FAKE_VALUE_FUNC2(can_dl_status_t,
                        can_ll_driver_timer_init,
                        uint8_t,
                        uint32_t);
DEFINE_FAKE_VALUE_FUNC1(can_dl_status_t, can_ll_driver_timer_start, uint8_t);
DEFINE_FAKE_VALUE_FUNC1(can_dl_status_t, can_ll_driver_timer_update, uint8_t);
DEFINE_FAKE_VALUE_FUNC2(can_dl_status_t,
                        can_ll_driver_timer_reload,
                        uint8_t,
                        uint64_t);
DEFINE_FAKE_VALUE_FUNC2(can_dl_status_t,
                        can_ll_driver_timer_delay,
                        uint8_t,
                        uint32_t);
DEFINE_FAKE_VALUE_FUNC1(can_dl_status_t, can_ll_driver_timer_stop, uint8_t);

class SoftwareTimer
{
public:
    SoftwareTimer (std::chrono::milliseconds interval)
        : interval(interval)
        , running(false)
        , update(false)
        , tick_count(1)
    {
    }

    void start ()
    {
        running = true;
        thread  = std::thread([this] () {
            while (running)
            {
                std::this_thread::sleep_for(interval);
                if (!running)
                {
                    break;
                }
                ++tick_count;
            }
        });
    }

    void stop ()
    {
        running = false;
        if (thread.joinable())
        {
            thread.join();
        }
    }

    void reset ()
    {
        tick_count = 1;
    }
    std::uint64_t get_tick_count () const
    {
        return tick_count.load();
    }

    ~SoftwareTimer ()
    {
        stop(); // Ensure clean shutdown
    }

private:
    std::chrono::milliseconds  interval;
    std::function<void()>      callback;
    std::atomic<bool>          running;
    std::atomic<bool>          update;
    size_t updated_val;
    std::atomic<std::uint64_t> tick_count;
    std::thread                thread;
};

std::shared_ptr<SoftwareTimer> sw_timer;

can_dl_status_t
can_ll_driver_timer_init_test (const uint8_t  peripheral,
                               const uint32_t frequency)
{
    if (peripheral != 0)
    {
        return CAN_DL_STATUS_INIT_ERR_INVALID_TIMER;
    }
    sw_timer = std::make_shared<SoftwareTimer>(
        std::chrono::milliseconds(1000 / frequency));
    return CAN_DL_STATUS_OK;
}

can_dl_status_t
can_ll_driver_timer_start_test (const uint8_t periperal)
{
    sw_timer->stop();
    sw_timer->reset();
    sw_timer->start();
    return CAN_DL_STATUS_OK;
}
can_dl_status_t
can_ll_driver_timer_update_test (const uint8_t peripheral)
{
    
    return CAN_DL_STATUS_OK;
}
can_dl_status_t
can_ll_driver_timer_reload_test (const uint8_t  peripheral,
                                 const uint64_t reload)
{
    return CAN_DL_STATUS_OK;
}

can_dl_status_t
can_ll_driver_timer_delay_test (const uint8_t peripheral, const uint32_t delay)
{
    return CAN_DL_STATUS_OK;
}

can_dl_status_t
can_ll_driver_timer_stop_test (const uint8_t peripheral)
{
    sw_timer->stop();
    sw_timer->reset();
    return CAN_DL_STATUS_OK;
}

size_t
get_timer_tick ()
{
    size_t tick_count = sw_timer->get_tick_count();
    printf("Main thread sees tick_count = %d\n", tick_count);
    return tick_count;
}

void
setup_fake_timer ()
{
    can_ll_driver_timer_init_fake.custom_fake  = can_ll_driver_timer_init_test;
    can_ll_driver_timer_start_fake.custom_fake = can_ll_driver_timer_start_test;
    can_ll_driver_timer_update_fake.custom_fake
        = can_ll_driver_timer_update_test;
    can_ll_driver_timer_reload_fake.custom_fake
        = can_ll_driver_timer_reload_test;
    can_ll_driver_timer_delay_fake.custom_fake = can_ll_driver_timer_delay_test;
    can_ll_driver_timer_stop_fake.custom_fake  = can_ll_driver_timer_stop_test;
}