#include "TaskManager.h"
#include <iostream>
#include <algorithm>

TaskManager::TaskManager() : savedFiles("tasks.txt") {}

// ----------------------------
// Private helpers
// ----------------------------

void TaskManager::sortTasks() {
    // Sort: incomplete tasks first by priority (High=1 < Medium=2 < Low=3),
    // then completed tasks after
    std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        if (a.isCompleted() != b.isCompleted())
            return !a.isCompleted(); // incomplete tasks come first
        return static_cast<int>(a.getPriority()) < static_cast<int>(b.getPriority());
    });
}

bool TaskManager::isValidIndex(int index) const {
    return (index >= 1 && index <= static_cast<int>(tasks.size()));
}

// ----------------------------
// Public operations
// ----------------------------

void TaskManager::addTask(const std::string& name, Priority priority) {
    tasks.push_back(Task(name, priority));
    sortTasks();
    std::cout << "  Task added: \"" << name << "\" [" << priorityToString(priority) << "]\n";
}

void TaskManager::removeTask(int index) {
    if (!isValidIndex(index)) {
        std::cout << "  Invalid task number.\n";
        return;
    }
    std::string name = tasks[index - 1].getName();

    // If the task was done, subtract its points before removing
    if (tasks[index - 1].isCompleted()) {
        points.subtractPoints(tasks[index - 1].getPriority());
    }

    tasks.erase(tasks.begin() + (index - 1));
    std::cout << "  Removed task: \"" << name << "\"\n";
}

void TaskManager::completeTask(int index) {
    if (!isValidIndex(index)) {
        std::cout << "  Invalid task number.\n";
        return;
    }
    Task& t = tasks[index - 1];
    if (t.isCompleted()) {
        std::cout << "  Task is already complete!\n";
        return;
    }
    t.setCompleted(true);
    points.addPoints(t.getPriority());
    soundPlayer.playHappy();
    sortTasks();
}

void TaskManager::uncompleteTask(int index) {
    if (!isValidIndex(index)) {
        std::cout << "  Invalid task number.\n";
        return;
    }
    Task& t = tasks[index - 1];
    if (!t.isCompleted()) {
        std::cout << "  Task is not completed yet.\n";
        return;
    }
    t.setCompleted(false);
    points.subtractPoints(t.getPriority());
    soundPlayer.playSad();
    sortTasks();
}

void TaskManager::displayTasks() const {
    if (tasks.empty()) {
        std::cout << "  No tasks yet. Add one!\n";
        return;
    }
    std::cout << "\n  ---- Your Tasks ----\n";
    for (int i = 0; i < static_cast<int>(tasks.size()); i++) {
        tasks[i].display(i + 1);
    }
    std::cout << "  --------------------\n";
}

void TaskManager::displayStats() const {
    int total = tasks.size();
    int done = 0;
    for (const Task& t : tasks)
        if (t.isCompleted()) done++;

    std::cout << "\n  ---- Stats ----\n";
    std::cout << "  Total tasks   : " << total << "\n";
    std::cout << "  Completed     : " << done << "\n";
    std::cout << "  Remaining     : " << (total - done) << "\n";
    points.display();
    std::cout << "  ---------------\n";
}

void TaskManager::save() {
    savedFiles.saveTasks(tasks, points.getTotal());
}

void TaskManager::load() {
    int loadedPoints = 0;
    if (savedFiles.loadTasks(tasks, loadedPoints)) {
        // Restore points by directly adjusting
        while (points.getTotal() < loadedPoints)
            points.addPoints(Priority::LOW); // increment gently

        // Simpler: just re-set via a workaround (see note in Points.h)
        // For simplicity we just report loaded points
        std::cout << "  Tasks loaded successfully!\n";
        sortTasks();
    } else {
        std::cout << "  No saved tasks found. Starting fresh.\n";
    }
}
