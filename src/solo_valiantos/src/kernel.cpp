extern "C"
{
#include "libc/stdint.h"
#include "libc/stdio.h"
#include "libc/stdlib.h"
#include "memory/memory.h" 
#include "libc/stddef.h"
#include "libc/string.h"
#include "interrupts/pit/pit.h"
#include "drivers/vga.h"
#include "gdt/gdt.h"
#include "interrupts/idt/idt.h"
#include "interrupts/irq/timer.h"
#include "multiboot2.h"
#include "util.h"
#include "memory/memutils.h"
#include "memory/memory.h"
#include "interrupts/interrupts.h"
#include "../../solo_valiantos/src/apps/song/include/song/song.h"
}


// Existing global operator new overloads
void* operator new[](size_t size)
{
    return malloc(size);
}

void *operator new(size_t size)
{
    return malloc(size);
}


// Existing global operator delete overloads
void operator delete(void *ptr) noexcept
{
    free(ptr);
}

void operator delete[](void *ptr) noexcept
{
    free(ptr);
}


// Add sized-deallocation functions
void operator delete(void *ptr, size_t size) noexcept
{
    (void)size; //unused, added to match required signature
    free(ptr);
}

void operator delete[](void *ptr, size_t size) noexcept
{
    (void)size; // unused, added to match required signature
    free(ptr);
}

extern "C" int kernel_main(void); // Change return type to int
int kernel_main()
{

    // // Allocate some memory 
    // // using the kernel memory manager
    // // THIS IS PART OF THE ASSIGNMENT
    int counter = 0;

    void *some_memory = malloc(12345);
    void *memory2 = malloc(54321);
    void *memory3 = malloc(13331);
    char *memory4 = new char[1000]();

    //  External declarations if they are defined in other files
    // // extern Note music_1[];          // Ensure this is defined and accessible
    extern uint32_t music_1_length; // If maintained, or use sizeof

    Song *songs[] = {
        new Song({music_1, sizeof(music_1) / sizeof(Note)}),
        new Song({music_2, sizeof(music_2) / sizeof(Note)}),
        new Song({music_3, sizeof(music_3) / sizeof(Note)}),
        new Song({music_4, sizeof(music_4) / sizeof(Note)}),
        new Song({music_5, sizeof(music_5) / sizeof(Note)}),
        new Song({music_6, sizeof(music_6) / sizeof(Note)}),
        new Song({music_7, sizeof(music_7) / sizeof(Note)})};

    uint32_t n_songs = sizeof(songs) / sizeof(Song *);

    SongPlayer *player = create_song_player(); // Begin setup the song player

    for (int count = 0; count < 1; count++)
    { 
        for (uint32_t i = 0; i < n_songs; i++)
        { // loop to iterate through songs for n outer loop times
            printf("Playing Song...\n");
            player->play_song(songs[i]);
            printf("Finished playing the song.\n");
        }
    }

    while (true)
    {
        printf("[%d]: Sleeping with busy-waiting (HIGH CPU).\n", counter);
        sleep_busy(1000);
        printf("[%d]: Slept using busy-waiting.\n", counter++);

        printf("[%d]: Sleeping with interrupts (LOW CPU).\n", counter);
        sleep_interrupt(1000);
        printf("[%d]: Slept using interrupts.\n", counter++);
    }

    return 0;
}
