#ifndef FAKE_HANDLERS_H
#define FAKE_HANDLERS_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "private/ttcan_dl_types.h"

#include <stdint.h>
#include <stddef.h>

#include "mock_target.h"
#include "fff.h"

    /* Create mock functions */
    DECLARE_FAKE_VALUE_FUNC2(can_dl_status_t,
                             can_ll_driver_timer_init,
                             uint8_t,
                             uint32_t);
    DECLARE_FAKE_VALUE_FUNC1(can_dl_status_t,
                             can_ll_driver_timer_start,
                             uint8_t);
    DECLARE_FAKE_VALUE_FUNC1(can_dl_status_t,
                             can_ll_driver_timer_update,
                             uint8_t);
    DECLARE_FAKE_VALUE_FUNC2(can_dl_status_t,
                             can_ll_driver_timer_reload,
                             uint8_t,
                             uint64_t);
    DECLARE_FAKE_VALUE_FUNC2(can_dl_status_t,
                             can_ll_driver_timer_delay,
                             uint8_t,
                             uint32_t);
    DECLARE_FAKE_VALUE_FUNC1(can_dl_status_t,
                             can_ll_driver_timer_stop,
                             uint8_t);

    DECLARE_FAKE_VALUE_FUNC1(can_dl_status_t, can_ll_driver_can_init, uint8_t);
    DECLARE_FAKE_VALUE_FUNC3(size_t,
                             can_ll_driver_can_write,
                             const uint8_t,
                             const uint8_t *,
                             const size_t);
    DECLARE_FAKE_VALUE_FUNC3(
        size_t, can_ll_driver_can_read, const uint8_t, uint8_t *, const size_t);
    DECLARE_FAKE_VALUE_FUNC1(can_dl_status_t,
                             can_ll_driver_can_deinit,
                             uint8_t);

    DECLARE_FAKE_VALUE_FUNC0(can_dl_status_t, can_ll_driver_nvm_init);
    DECLARE_FAKE_VALUE_FUNC3(can_dl_status_t,
                             can_ll_driver_nvm_write,
                             uint32_t,
                             const uint8_t *,
                             size_t);
    DECLARE_FAKE_VALUE_FUNC3(
        can_dl_status_t, can_ll_driver_nvm_read, uint32_t, uint8_t *, size_t);
    DECLARE_FAKE_VALUE_FUNC0(can_dl_status_t, can_ll_driver_nvm_deinit);

    void setup_fake_timer();

    size_t get_timer_tick();

    void setup_fake_can();

    void setup_fake_nvm();

#ifdef __cplusplus
}
#endif
#endif /* FAKE_HANDLERS_H */