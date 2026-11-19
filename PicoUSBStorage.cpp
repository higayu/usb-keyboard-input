#include "bsp/board_api.h"
#include "tusb.h"
int main() {
    board_init();
    tusb_init();
    while (true) tud_task();
}
