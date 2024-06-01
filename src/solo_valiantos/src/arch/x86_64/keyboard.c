#include "drivers/keyboard.h"
#include "interrupts/io/io.h" // For port I/O functions
#include "interrupts/irq/irq.h" // For registering IRQ handlers

#define KEYBOARD_DATA_PORT 0x60

// Keyboard buffer
#define KEYBUF_SIZE 256
unsigned char keybuf[KEYBUF_SIZE];
unsigned int keybuf_head = 0;
unsigned int keybuf_tail = 0;

// Keyboard scancode to ASCII lookup table for a Norwegian layout
unsigned char scancode_to_ascii[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
    '9', '0', '+', '\\', '\b', /* Backspace */
    '\t', /* Tab */
    'q', 'w', 'e', 'r', /* 19 */
    't', 'y', 'u', 'i', 'o', 'p', 'å', '[', '\n', /* Enter key */
    0, /* 29 - Control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'ø', /* 39 */
    'æ', '\'', 0, /* Left shift */
    '<', 'z', 'x', 'c', 'v', 'b', 'n', /* 49 */
    'm', ',', '.', '-', 0, /* Right shift */
    '*',
    0, /* Alt */
    ' ', /* Space bar */
    0, /* Caps lock */
    0, /* F1 key */
    0, /* F2 key */
    0, /* F3 key */
    0, /* F4 key */
    0, /* F5 key */
    0, /* F6 key */
    0, /* F7 key */
    0, /* F8 key */
    0, /* F9 key */
    0, /* F10 key */
    0, /* Num lock */
    0, /* Scroll lock */
    0, /* Home key */
    0, /* Up Arrow */
    0, /* Page Up */
    '-',
    0, /* Left Arrow */
    0,
    0, /* Right Arrow */
    '+',
    0, /* End key */
    0, /* Down Arrow */
    0, /* Page Down */
    0, /* Insert Key */
    0, /* Delete Key */
    0, 0, 0, 0, /* F11 Key */
    0, 0, 0, 0, /* F12 Key */
    0, /* All other keys are undefined */
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