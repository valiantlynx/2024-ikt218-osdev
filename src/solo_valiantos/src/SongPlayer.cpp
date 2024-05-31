#include "song.h"
#include "pit.h"
#include "io.h"
#include "timer.h"
#include "stdlib.h"
#include "stddef.h"
#include "idt.h"
#include "stdio.h"
// #include "SongPlayer.h"


void enable_speaker()
{
    // current state of the PC speaker control register
    uint8_t speaker_state = inb(PC_SPEAKER_PORT);
    // if bits 0 and 1 are not set (0 means that the speaker is disabled)
    if (speaker_state != (speaker_state | 3))
    {
        // If bits 0 and 1 are not set, set bits 0 and 1 to 1
        outb(PC_SPEAKER_PORT, speaker_state | 3);
    }
}

void disable_speaker()
{
    uint8_t speaker_state = inb(PC_SPEAKER_PORT);
    outb(PC_SPEAKER_PORT, speaker_state & 0xFC);
}

void play_sound(uint32_t frequency)
{
    if (frequency == 0)
    {
        return;
    }

    auto divisor = (uint16_t)(PIT_BASE_FREQUENCY / frequency);

    // Set up the PIT
    outb(PIT_CMD_PORT, 0b10110110);
    outb(PIT_CHANNEL2_PORT, (uint8_t)(divisor & 0xFF));
    outb(PIT_CHANNEL2_PORT, (uint8_t)(divisor >> 8));
}

void stop_sound()
{
    disable_speaker();
}

extern uint32_t tick;
void play_song_impl(Song *song)
{
    uint32_t start_tick = tick;
    for (uint32_t i = 0; i < song->length; i++)
    {
        Note note = song->notes[i];
        play_sound(note.frequency);
        uint32_t note_end_tick = start_tick + note.duration;
        while (tick < note_end_tick)
        {
            // Wait note duration to pass
        }
        disable_speaker(); 
        start_tick = note_end_tick; // Update start_tick to the end of the current note
    }
}

void play_song(Song *song)
{
    play_song_impl(song);
}

