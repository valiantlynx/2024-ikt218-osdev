#include "keyboard.h"
#include "io.h" // For port I/O functions
#include "irq.h" // For registering IRQ handlers

#define KEYBOARD_DATA_PORT 0x60

// Keyboard buffer
#define KEYBUF_SIZE 256
unsigned char keybuf[KEYBUF_SIZE];
unsigned int keybuf_head = 0;
unsigned int keybuf_tail = 0;

// Keyboard scancode to ASCII lookup table for a simple US layout
unsigned char scancode_to_ascii[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
    '9', '0', '-', '=', '\b', /* Backspace */
    '\t', /* Tab */
    'q', 'w', 'e', 'r', /* 19 */
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /* Enter key */
    0, /* 29 - Control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
    '\'', '`', 0, /* Left shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', /* 49 */
    'm', ',', '.', '/', 0, /* Right shift */
    '*',
    0, /* Alt */
    ' ', /* Space bar */
    0, /* Caps lock */
    // rest of the characters... # TODO: get an ai to do this or copy from some source on the internet
};

void keyboard_handler() {
    unsigned char scancode = inb(KEYBOARD_DATA_PORT);
    // Check if the scancode corresponds to a key press (and not release)
    if (scancode < 128) {
        unsigned char ascii = scancode_to_ascii[scancode];
        // Simple print for demonstration
        terminal_write_char(ascii); // Assume you have this function
    }
}

void initialize_keyboard() {
    register_irq_handler(1, keyboard_handler); // Register keyboard_handler for IRQ1
}