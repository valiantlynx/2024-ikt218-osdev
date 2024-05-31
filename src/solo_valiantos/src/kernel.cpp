extern "C" void kernel_main() {
    const char* startMessage = "Hello World!";
    volatile char* VideoMemory = (volatile char*)0xb8000; // assignment 2
    unsigned int i = 0, j = 0;

    while (i < 80 * 25 * 2) {
        VideoMemory[i] = ' '; 
        VideoMemory[i + 1] = 0x19; 
        i += 2;
    }

    i = 0;

    while (startMessage[j] != '\0') {
        VideoMemory[i] = startMessage[j];
        VideoMemory[i + 1] = 0x0C; // text color
        j++;
        i += 2;
    }
}
