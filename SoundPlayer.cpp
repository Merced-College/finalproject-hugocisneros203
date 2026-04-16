#include "SoundPlayer.h"
#include <iostream>

// Plays happy beeps and a celebratory message
void SoundPlayer::playHappy() {
    // Three quick beeps using the system bell character
    std::cout << "\a";
    std::cout << "  *** Great job! Task complete! ***\n";
}

// Plays a sad beep and an encouraging message
void SoundPlayer::playSad() {
    std::cout << "\a";
    std::cout << "  ... Task marked incomplete. You got this!\n";
}
