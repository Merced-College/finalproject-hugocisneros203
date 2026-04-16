#include "Points.h"
#include <iostream>

Points::Points() : totalPoints(0) {}

int Points::getPointValue(Priority p) const {
    switch (p) {
        case Priority::HIGH:   return 30;
        case Priority::MEDIUM: return 20;
        case Priority::LOW:    return 10;
        default:               return 0;
    }
}

void Points::addPoints(Priority p) {
    totalPoints += getPointValue(p);
}

void Points::subtractPoints(Priority p) {
    totalPoints -= getPointValue(p);
    if (totalPoints < 0) totalPoints = 0; // Never go below zero
}

int Points::getTotal() const {
    return totalPoints;
}

void Points::display() const {
    std::cout << "  Total Points: " << totalPoints << " pts\n";
}
