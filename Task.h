#ifndef TASK_H
#define TASK_H

#include <string>

// Priority levels for sorting tasks
enum class Priority {
    HIGH = 1,
    MEDIUM = 2,
    LOW = 3
};

// Converts Priority enum to a readable string
std::string priorityToString(Priority p);

// Converts integer (1/2/3) to Priority enum
Priority intToPriority(int n);

class Task {
private:
    std::string name;
    Priority priority;
    bool completed;

public:
    // Constructor
    Task(const std::string& name, Priority priority);

    // Getters
    std::string getName() const;
    Priority getPriority() const;
    bool isCompleted() const;

    // Setters
    void setCompleted(bool status);

    // Display this task to console
    void display(int index) const;
};

#endif
