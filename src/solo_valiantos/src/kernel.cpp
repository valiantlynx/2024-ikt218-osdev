extern "C"
{
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h" // For malloc and free
#include "memory.h" // Assuming it's part of your custom kernel headers
#include "stddef.h" // For size_t
#include "string.h"
#include "pit.h"
#include "vga.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "multiboot2.h"
#include "util.h"
#include "memutils.h"
#include "memory.h"
#include "interrupts.h" // Include the SongPlayer header
#include "../../solo_valiantos/src/apps/song/include/song/song.h"
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

void* operator new[](size_t size)
{
    return malloc(size);
}

void *operator new(size_t size)
{
    return malloc(size);
}

// Add sized-deallocation functions
void operator delete(void *ptr, size_t size) noexcept
{
    (void)size; // Size parameter is unused, added to match required signature
    free(ptr);
}

void operator delete[](void *ptr, size_t size) noexcept
{
    (void)size; // Size parameter is unused, added to match required signature
    free(ptr);
}

extern "C" int kernel_main(void); // Change return type to int
int kernel_main()
{
    int counter = 0;

    void *some_memory = malloc(12345);
    void *memory2 = malloc(54321);
    void *memory3 = malloc(13331);
    char *memory4 = new char[1000]();

    // External declarations if they are defined in other files
    // extern Note music_1[];          // Ensure this is defined and accessible
    extern uint32_t music_1_length; // If maintained, or use sizeof as shown

    Song *songs[] = {
        new Song({music_1, sizeof(music_1) / sizeof(Note)}),
        new Song({music_2, sizeof(music_2) / sizeof(Note)}),
        new Song({music_3, sizeof(music_3) / sizeof(Note)}),
        new Song({music_4, sizeof(music_4) / sizeof(Note)}),
        new Song({music_5, sizeof(music_5) / sizeof(Note)}),
        new Song({music_6, sizeof(music_6) / sizeof(Note)}),
        new Song({music_7, sizeof(music_7) / sizeof(Note)})};

    uint32_t n_songs = sizeof(songs) / sizeof(Song *);

    SongPlayer *player = create_song_player(); // Setup the song player

    for (int count = 0; count < 1; count++)
    { // Outer loop to run n times
        for (uint32_t i = 0; i < n_songs; i++)
        { // Inner loop to iterate through songs
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
