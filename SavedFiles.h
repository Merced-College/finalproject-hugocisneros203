#ifndef SAVEDFILES_H
#define SAVEDFILES_H

#include <vector>
#include <string>
#include "Task.h"

// SavedFiles handles reading and writing tasks to a .txt file
// so the user's tasks persist between sessions.
class SavedFiles {
private:
    std::string filename;

public:
    SavedFiles(const std::string& filename = "tasks.txt");

    // Save all tasks to the file
    void saveTasks(const std::vector<Task>& tasks, int points) const;

    // Load tasks from the file; returns false if file doesn't exist
    bool loadTasks(std::vector<Task>& tasks, int& points) const;
};

#endif
