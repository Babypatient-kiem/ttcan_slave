#include "fake_handlers.h"


DEFINE_FAKE_VALUE_FUNC1(can_dl_status_t, can_ll_driver_can_init, uint8_t);
DEFINE_FAKE_VALUE_FUNC3(size_t, can_ll_driver_can_write, const uint8_t, const uint8_t*, const size_t);
DEFINE_FAKE_VALUE_FUNC3(size_t, can_ll_driver_can_read,  const uint8_t, uint8_t*, const size_t);
DEFINE_FAKE_VALUE_FUNC1(can_dl_status_t, can_ll_driver_can_deinit, uint8_t);


can_dl_status_t
can_ll_driver_can_init_test (const uint8_t peripheral)
{
    if(peripheral != 0) {
        return CAN_DL_STATUS_INIT_ERR_INVALID_CAN;
    } else {
        return CAN_DL_STATUS_OK;
    }
}

size_t
can_ll_driver_can_write_test (const uint8_t  peripheral,
                              const uint8_t *data,
                              const size_t   len)
{
}

size_t
can_ll_driver_can_read_test (const uint8_t peripheral,
                             uint8_t      *data,
                             const size_t  len)
{
}

can_dl_status_t
can_ll_driver_can_deinit_test (const uint8_t peripheral)
{
}

void setup_fake_can() {
    can_ll_driver_can_init_fake.custom_fake = can_ll_driver_can_init_test;
    can_ll_driver_can_read_fake.custom_fake = can_ll_driver_can_read_test;
    can_ll_driver_can_write_fake.custom_fake = can_ll_driver_can_write_test;
    can_ll_driver_can_deinit_fake.custom_fake = can_ll_driver_can_deinit_test;
}