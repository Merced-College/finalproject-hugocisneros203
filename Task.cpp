#include "Task.h"
#include <iostream>
#include <iomanip>

// ----------------------------
// Free helper functions
// ----------------------------

std::string priorityToString(Priority p) {
    switch (p) {
        case Priority::HIGH:   return "High";
        case Priority::MEDIUM: return "Medium";
        case Priority::LOW:    return "Low";
        default:               return "Unknown";
    }
}

Priority intToPriority(int n) {
    switch (n) {
        case 1:  return Priority::HIGH;
        case 2:  return Priority::MEDIUM;
        default: return Priority::LOW;
    }
}

// ----------------------------
// Task class implementation
// ----------------------------

Task::Task(const std::string& name, Priority priority)
    : name(name), priority(priority), completed(false) {}

std::string Task::getName() const {
    return name;
}

Priority Task::getPriority() const {
    return priority;
}

bool Task::isCompleted() const {
    return completed;
}

void Task::setCompleted(bool status) {
    completed = status;
}

void Task::display(int index) const {
    std::string status = completed ? "[DONE]" : "[    ]";
    std::string pLabel = "(" + priorityToString(priority) + ")";

    std::cout << "  " << index << ". " << status
              << " " << std::left << std::setw(30) << name
              << " " << pLabel << "\n";
}
