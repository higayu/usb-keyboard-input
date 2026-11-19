#include "pico/stdlib.h"
#include "bsp/board_api.h"
#include "tusb.h"

// One-shot demonstration: open Windows PowerShell, without running commands.
static constexpr uint32_t WAIT_MS = 5000;
static constexpr uint8_t keys[] = {
    HID_KEY_P, HID_KEY_O, HID_KEY_W, HID_KEY_E, HID_KEY_R,
    HID_KEY_S, HID_KEY_H, HID_KEY_E, HID_KEY_L, HID_KEY_L,
    HID_KEY_ENTER
};
int main() {
    board_init();
    tusb_init();
    bool waiting = false, done = false;
    uint32_t start = 0, next = 0;
    unsigned step = 0;
    while (true) {
        tud_task();
        if (done) continue;
        uint32_t now = to_ms_since_boot(get_absolute_time());
        if (!tud_mounted() || tud_suspended()) {
            if (step != 0) done = true;
            waiting = false;
            continue;
        }
        if (!waiting) { waiting = true; start = now; }
        if (now - start < WAIT_MS || (int32_t)(now-next)<0 || !tud_hid_ready()) continue;
        uint8_t report[6] = {};
        uint8_t modifier = 0;
        if (step == 0) { modifier = KEYBOARD_MODIFIER_LEFTGUI; report[0] = HID_KEY_R; }
        else if (step >= 2 && step % 2 == 0) { report[0] = keys[(step-2)/2]; }
        if (!tud_hid_keyboard_report(0, modifier, report)) continue;
        ++step;
        next = now + (step == 2 ? 1200 : 100);
        if (step == 2 + 2*sizeof(keys)) done = true;
    }
}
