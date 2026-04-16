#ifndef POINTS_h
#define POINTS_h

#include "Task.h"

// Points tracks the user's score based on task completion.
// High priority tasks are worth more points than low priority ones.
class Points {
private:
    int totalPoints;

    // Returns how many points a given priority is worth
    int getPointValue(Priority p) const;

public:
    Points();

    // Add points when a task is completed
    void addPoints(Priority p);

    // Subtract points when a task is marked incomplete
    void subtractPoints(Priority p);

    // Get the current total
    int getTotal() const;

    // Display current score
    void display() const;
};

#endif