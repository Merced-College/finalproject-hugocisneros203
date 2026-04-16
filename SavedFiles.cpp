#include "SavedFiles.h"
#include <fstream>
#include <iostream>
#include <sstream>

SavedFiles::SavedFiles(const std::string& filename) : filename(filename) {}

// File format per line:
// taskName|priorityInt|completedBool
// Last line: POINTS|value
void SavedFiles::saveTasks(const std::vector<Task>& tasks, int points) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "  [Warning] Could not save tasks to file.\n";
        return;
    }

    for (const Task& t : tasks) {
        int pInt = static_cast<int>(t.getPriority());
        int done = t.isCompleted() ? 1 : 0;
        file << t.getName() << "|" << pInt << "|" << done << "\n";
    }

    // Save points on the last line
    file << "POINTS|" << points << "\n";

    file.close();
    std::cout << "  Tasks saved to " << filename << "\n";
}

bool SavedFiles::loadTasks(std::vector<Task>& tasks, int& points) const {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false; // File doesn't exist yet — that's okay
    }

    tasks.clear();
    points = 0;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        // Check if it's the points line
        if (line.substr(0, 7) == "POINTS|") {
            points = std::stoi(line.substr(7));
            continue;
        }

        // Parse task line: name|priority|completed
        std::istringstream ss(line);
        std::string name, pStr, dStr;
        if (std::getline(ss, name, '|') &&
            std::getline(ss, pStr, '|') &&
            std::getline(ss, dStr, '|')) {

            Priority p = intToPriority(std::stoi(pStr));
            Task t(name, p);
            t.setCompleted(dStr == "1");
            tasks.push_back(t);
        }
    }

    file.close();
    return true;
}
