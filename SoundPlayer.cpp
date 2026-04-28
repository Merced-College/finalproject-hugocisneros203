#include "SoundPlayer.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstdio>

// -----------------------------------------------------------
// Writes a WAV file from raw 16-bit PCM samples
// -----------------------------------------------------------
static void writeWav(const std::string& filename,
                     const std::vector<int16_t>& samples,
                     int sampleRate = 44100)
{
    std::ofstream f(filename, std::ios::binary);

    int numSamples    = (int)samples.size();
    int dataSize      = numSamples * 2;
    int chunkSize     = 36 + dataSize;
    int byteRate      = sampleRate * 2;
    int16_t blockAlign   = 2;
    int16_t bitsPerSample = 16;
    int16_t numChannels  = 1;
    int16_t audioFmt     = 1;
    int16_t fmtSize16    = 16;
    int     fmtSize      = 16;

    f.write("RIFF", 4);
    f.write(reinterpret_cast<const char*>(&chunkSize), 4);
    f.write("WAVE", 4);
    f.write("fmt ", 4);
    f.write(reinterpret_cast<const char*>(&fmtSize), 4);
    f.write(reinterpret_cast<const char*>(&audioFmt), 2);
    f.write(reinterpret_cast<const char*>(&numChannels), 2);
    f.write(reinterpret_cast<const char*>(&sampleRate), 4);
    f.write(reinterpret_cast<const char*>(&byteRate), 4);
    f.write(reinterpret_cast<const char*>(&blockAlign), 2);
    f.write(reinterpret_cast<const char*>(&bitsPerSample), 2);
    f.write("data", 4);
    f.write(reinterpret_cast<const char*>(&dataSize), 4);
    f.write(reinterpret_cast<const char*>(samples.data()), dataSize);
}

// -----------------------------------------------------------
// Append a sine-wave tone to a sample buffer
// -----------------------------------------------------------
static void addTone(std::vector<int16_t>& buf,
                    double freq, double duration,
                    int sampleRate = 44100, double volume = 0.6)
{
    int n = (int)(sampleRate * duration);
    for (int i = 0; i < n; i++) {
        double env = (i > (int)(n * 0.8))
                     ? (double)(n - i) / (n * 0.2) : 1.0;
        double s = volume * env * std::sin(2.0 * M_PI * freq * i / sampleRate);
        buf.push_back((int16_t)(s * 32767.0));
    }
}

static void addSilence(std::vector<int16_t>& buf,
                       double duration, int sampleRate = 44100)
{
    int n = (int)(sampleRate * duration);
    for (int i = 0; i < n; i++) buf.push_back(0);
}

// -----------------------------------------------------------
// Play a WAV file with whichever player is available
// -----------------------------------------------------------
static void playWav(const std::string& filename)
{
#if defined(__APPLE__)
    std::string cmd = "afplay " + filename + " 2>/dev/null &";
#else
    std::string cmd =
        "(aplay " + filename + " 2>/dev/null || "
        " paplay " + filename + " 2>/dev/null || "
        " ffplay -nodisp -autoexit " + filename + " 2>/dev/null) &";
#endif
    std::system(cmd.c_str());
}

// -----------------------------------------------------------
// Happy melody: ascending C4-E4-G4-C5-E5 fanfare
// -----------------------------------------------------------
void SoundPlayer::playHappy()
{
    const int SR = 44100;
    std::vector<int16_t> buf;

    addTone(buf, 261.63, 0.10, SR);  addSilence(buf, 0.03, SR); // C4
    addTone(buf, 329.63, 0.10, SR);  addSilence(buf, 0.03, SR); // E4
    addTone(buf, 392.00, 0.10, SR);  addSilence(buf, 0.03, SR); // G4
    addTone(buf, 523.25, 0.15, SR);  addSilence(buf, 0.03, SR); // C5
    addTone(buf, 659.25, 0.25, SR);                              // E5

    writeWav("/tmp/happy.wav", buf, SR);
    playWav("/tmp/happy.wav");

    std::cout << "  *** Great job! Task complete! ***\n";
}

// -----------------------------------------------------------
// Sad melody: descending A4-F4-D4-A3 minor drop
// -----------------------------------------------------------
void SoundPlayer::playSad()
{
    const int SR = 44100;
    std::vector<int16_t> buf;

    addTone(buf, 440.00, 0.18, SR);  addSilence(buf, 0.04, SR); // A4
    addTone(buf, 349.23, 0.18, SR);  addSilence(buf, 0.04, SR); // F4
    addTone(buf, 293.66, 0.18, SR);  addSilence(buf, 0.04, SR); // D4
    addTone(buf, 220.00, 0.35, SR);                              // A3

    writeWav("/tmp/sad.wav", buf, SR);
    playWav("/tmp/sad.wav");

    std::cout << "  ... Task marked incomplete. You got this!\n";
}

