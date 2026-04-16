#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <vector>
#include "Task.h"
#include "SoundPlayer.h"
#include "Points.h"
#include "SavedFiles.h"

// TaskManager is the core class that coordinates all features:
// adding/removing tasks, sorting by priority, tracking points,
// triggering sounds, and saving/loading from a file.
class TaskManager {
private:
    std::vector<Task> tasks;
    SoundPlayer soundPlayer;
    Points points;
    SavedFiles savedFiles;

    // Sorts tasks: incomplete first by priority, then completed tasks
    void sortTasks();

    // Checks if an index entered by the user is valid
    bool isValidIndex(int index) const;

public:
    TaskManager();

    // Core operations
    void addTask(const std::string& name, Priority priority);
    void removeTask(int index);
    void completeTask(int index);
    void uncompleteTask(int index);

    // Display
    void displayTasks() const;
    void displayStats() const;

    // File operations
    void save();
    void load();
};

#endif
