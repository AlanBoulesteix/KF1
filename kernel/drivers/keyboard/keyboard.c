#include "../../includes/kb.h"

char scancode_to_ascii(uint8_t scan_code, KeyboardState *state) {
    // Unshifted characters (normal state)
    static const char unshifted[] = {
        0, 0, '1', '2', '3', '4', '5', '6', 
        '7', '8', '9', '0', '-', '=', '\b', '\t',
        'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
        'o', 'p', '[', ']', '\n', 0, 'a', 's',
        'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
        '\'', '`', 0, '\\', 'z', 'x', 'c', 'v',
        'b', 'n', 'm', ',', '.', '/', 0, '*',
        0, ' ', 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, '7',
        '8', '9', '-', '4', '5', '6', '+', '1',
        '2', '3', '0', '.', 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };

    // Shifted characters (Shift or Caps Lock active)
    static const char shifted[] = {
        0,  0,  '!', '@', '#', '$', '%', '^', 
        '&', '*', '(', ')', '_', '+', '\b', '\t', 
        'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 
        'O', 'P', '{', '}', '\n', 0,  'A', 'S', 
        'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', 
        '"', '~', 0,  '|', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', '<', '>', '?', 0,  '*', 
        0, ' ', 0, 0, 0, 0, 0, 0,  
        0, 0, 0, 0, 0, 0, 0, '7',
        '8', '9', '-', '4', '5', '6', '+', '1', 
        '2', '3', '0', '.', 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0
    };

    // Handle Caps Lock (only affects letters)
    bool caps_affects_key = (
        (scan_code >= 0x10 && scan_code <= 0x17) || // q-w-e-r-t-y-u-i
        (scan_code >= 0x1E && scan_code <= 0x26) || // a-s-d-f-g-h-j-k-l
        (scan_code >= 0x2C && scan_code <= 0x32)    // z-x-c-v-b-n-m
    );

    bool shifted = state->shift;
    if (caps_affects_key && state->caps_lock) {
        shifted = !shifted; // Caps Lock inverts Shift for letters
    }

    if (scan_code >= sizeof(unshifted)) return 0;
    return shifted ? shifted[scan_code] : unshifted[scan_code];
}


    if (scan_code >= sizeof(unshifted)) return 0;

    bool shifted = state->shift ^ state->caps_lock; // XOR: Shift or Caps Lock (but not both)
    return shifted ? shifted[scan_code] : unshifted[scan_code];
}


void    keyboard_handler(uint8_t scancode) {
    scancode_to_ascii[scancode]
}