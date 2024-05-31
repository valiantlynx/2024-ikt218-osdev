#ifndef SONG_H
#define SONG_H

#include "frequencies.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
//#include "SongPlayer.h"


//  a single musical note
typedef struct
{
    uint32_t frequency; // freq of the note in Hz (e.g., A4 = 440 Hz)
    uint32_t duration;  // duration of note in ms
} Note;

//a song
typedef struct
{
    Note *notes;     // Pointer to an array of Note structs
    uint32_t length; // no. of notes in the song
} Song;

// a song player
typedef struct
{
    void (*play_song)(Song *song); // Func pointer to a func that plays a song
} SongPlayer;

// Returns a pointer to a newly created SongPlayer object
SongPlayer *create_song_player();
void play_song_impl(Song *song);

static Note music_1[] = {
    {E5, 250},
    {R, 125},
    {E5, 125},
    {R, 125},
    {E5, 125},
    {R, 125},
    {C5, 125},
    {E5, 125},
    {G5, 125},
    {R, 125},
    {G4, 125},
    {R, 250},

    {C5, 125},
    {R, 250},
    {G4, 125},
    {R, 125},
    {E4, 125},
    {R, 125},
    {A4, 125},
    {B4, 125},
    {R, 125},
    {A_SHARP4, 125},
    {A4, 125},
    {R, 125},
    {G4, 125},
    {E5, 125},
    {G5, 125},
    {A5, 125},
    {F5, 125},
    {G5, 125},
    {R, 125},
    {E5, 125},
    {C5, 125},
    {D5, 125},
    {B4, 125},
    {R, 125},

    {C5, 125},
    {R, 250},
    {G4, 125},
    {R, 125},
    {E4, 125},
    {R, 125},
    {A4, 125},
    {B4, 125},
    {R, 125},
    {A_SHARP4, 125},
    {A4, 125},
    {R, 125},
    {G4, 125},
    {E5, 125},
    {G5, 125},
    {A5, 125},
    {F5, 125},
    {G5, 125},
    {R, 125},
    {E5, 125},
    {C5, 125},
    {D5, 125},
    {B4, 125},
    {R, 125},
};

static Note starwars_theme[] = {
    // Opening phrase
    {A4, 500},
    {A4, 500},
    {A4, 500},
    {F4, 375},
    {C5, 125},
    {A4, 500},
    {F4, 375},
    {C5, 125},
    {A4, 1000},
    {E5, 500},
    {E5, 500},
    {E5, 500},
    {F5, 375},
    {C5, 125},

    // Next phrase
    {G4, 500},
    {F4, 375},
    {C5, 125},
    {A4, 1000},
    {A5, 500},
    {A4, 375},
    {A4, 125},
    {A5, 500},
    {G5, 375},
    {F5, 125},
    {E5, 125},
    {D5, 125},
    {C5, 250},
    {B4, 250},
    {A4, 500},

    // End note
    {R, 500}};

static Note battlefield_1942_theme[] = {
    // Attempt at the opening part of the Battlefield 1942 theme
    {E4, 500},
    {G4, 500},
    {B4, 300},
    {E5, 200},
    {D5, 200},
    {B4, 300},
    {G4, 500},
    {B4, 300},
    {E5, 200},
    {D5, 200},
    {B4, 300},
    {G4, 500},
    {B4, 300},
    {E5, 200},
    {G5, 200},
    {E5, 300},

    // Continue with the next part of the melody
    {D5, 200},
    {B4, 300},
    {G4, 500},
    {E4, 500},
    {G4, 500},
    {B4, 300},
    {E5, 200},
    {D5, 200},
    {B4, 300},
    {G4, 500},
    {B4, 300},
    {E5, 200},
    {D5, 200},
    {B4, 300},
    {G4, 500},
    {B4, 300},
    {E5, 200},
    {G5, 200},
    {E5, 300},
    {D5, 200},
    {B4, 300},
    {G4, 500},

    // TODO: Repeat or modify as needed
    // ...

    // End note
    {R, 500}};

static Note music_2[] = {
    {A4, 200}, {E5, 200}, {A5, 200}, {R, 100}, {A5, 200}, {A5, 200}, {Gs5, 200}, {A5, 200}, {R, 100}, {E5, 200}, {R, 100}, {E5, 200}, {R, 100}, {E5, 200}, {R, 100}, {E5, 200}, {A4, 200}, {E5, 200}, {A5, 200}, {R, 100}, {A5, 200}, {A5, 200}, {Gs5, 200}, {A5, 200}, {R, 100}, {E5, 200}, {R, 100}, {E5, 200}, {R, 100}, {E5, 200}, {R, 100}, {E5, 200}, {A4, 200}, {E5, 200}, {A5, 200}, {R, 100}, {A5, 200}, {A5, 200}, {Gs5, 200}, {A5, 200}, {R, 100}, {E5, 200}, {R, 100}, {E5, 200}, {R, 100}, {E5, 200}, {R, 100}, {E5, 200}};

static Note music_3[] = {
    {E4, 200}, {E4, 200}, {F4, 200}, {G4, 200}, {G4, 200}, {F4, 200}, {E4, 200}, {D4, 200}, {C4, 200}, {C4, 200}, {D4, 200}, {E4, 200}, {E4, 400}, {R, 200}, {D4, 200}, {D4, 200}, {E4, 200}, {F4, 200}, {F4, 200}, {E4, 200}, {D4, 200}, {C4, 200}, {A4, 200}, {A4, 200}, {A4, 200}, {G4, 400}};

static Note music_4[] = {
    {C4, 500}, {D4, 500}, {E4, 500}, {C4, 500}, {C4, 500}, {D4, 500}, {E4, 500}, {C4, 500}, {E4, 500}, {F4, 500}, {G4, 1000}, {E4, 500}, {F4, 500}, {G4, 1000}, {G4, 250}, {A4, 250}, {G4, 250}, {F4, 250}, {E4, 500}, {C4, 500}, {G4, 250}, {A4, 250}, {G4, 250}, {F4, 250}, {E4, 500}, {C4, 500}, {C4, 500}, {G3, 500}, {C4, 1000}, {C4, 500}, {G3, 500}, {C4, 1000}};

static Note music_5[] = {
    {E4, 375},
    {C4, 375},
    {D4, 375},
    {A3, 375},
    {B3, 375},
    {D4, 375},
    {C4, 375},
    {A3, 375},
    {E4, 375},
    {C4, 375},
    {D4, 375},
    {A3, 375},
    {B3, 375},
    {D4, 375},
    {C4, 375},
    {A3, 375},
};

static Note music_6[] = {
    {F4, 250},
    {F4, 250},
    {F4, 250},
    {C5, 250},
    {A_SHARP4, 250},
    {G_SHARP4, 250},
    {F4, 500},
    {F4, 250},
    {F4, 250},
    {F4, 250},
    {C5, 250},
    {A_SHARP4, 250},
    {G_SHARP4, 250},
    {F4, 500},
    {A_SHARP4, 250},
    {A_SHARP4, 250},
    {A_SHARP4, 250},
    {F5, 250},
    {D5, 250},
    {C5, 250},
    {A_SHARP4, 500},
    {A_SHARP4, 250},
    {A_SHARP4, 250},
    {A_SHARP4, 250},
    {F5, 250},
    {D5, 250},
    {C5, 250},
    {A_SHARP4, 500},
};

static Note music_7[] = {
    {C4, 500},  // Whole note, 1 second
    {D4, 500},  // Whole note, 1 second
    {E4, 500},  // Whole note, 1 second
    {F4, 250},  // Quarter note, 0.5 seconds
    {G4, 250},  // Quarter note, 0.5 seconds
    {A4, 500},  // Whole note, 1 second
    {G4, 250},  // Quarter note, 0.5 seconds
    {F4, 250},  // Quarter note, 0.5 seconds
    {E4, 500},  // Whole note, 1 second
    {D4, 500},  // Whole note, 1 second
    {C4, 1000}, // Double whole note, 2 seconds
    {R, 500},   // Rest, 0.5 seconds to separate phrases or end the piece
};

#endif
