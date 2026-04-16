#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

// SoundPlayer handles audio feedback using console beeps.
// Uses ANSI escape or system beep (\a) for cross-platform support.
class SoundPlayer {
public:
    // Plays a happy sound when a task is completed
    void playHappy();

    // Plays a sad sound when a task is marked incomplete
    void playSad();
};

#endif
