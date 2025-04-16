#include "fake_handlers.h"

DEFINE_FAKE_VALUE_FUNC0(can_dl_status_t, can_ll_driver_nvm_init);
DEFINE_FAKE_VALUE_FUNC3(can_dl_status_t, can_ll_driver_nvm_write, uint32_t, const uint8_t *, size_t);
DEFINE_FAKE_VALUE_FUNC3(can_dl_status_t, can_ll_driver_nvm_read, uint32_t, uint8_t*, size_t);
DEFINE_FAKE_VALUE_FUNC0(can_dl_status_t, can_ll_driver_nvm_deinit);


can_dl_status_t can_ll_driver_nvm_init_test() {
    return CAN_DL_STATUS_OK;
}
can_dl_status_t can_ll_driver_nvm_write_test(uint32_t       index,
                                        const uint8_t *data,
                                        size_t         len) {

                                        }
can_dl_status_t can_ll_driver_nvm_read_test(uint32_t index,
                                       uint8_t *data,
                                       size_t   len) {

                                       }
                                       
can_dl_status_t can_ll_driver_nvm_deinit_test() {

}

void setup_fake_nvm() {
    can_ll_driver_nvm_init_fake.custom_fake = can_ll_driver_nvm_init_test;
    can_ll_driver_nvm_write_fake.custom_fake = can_ll_driver_nvm_write_test;
    can_ll_driver_nvm_read_fake.custom_fake = can_ll_driver_nvm_read_test;
    can_ll_driver_nvm_deinit_fake.custom_fake = can_ll_driver_nvm_deinit_test;
}
