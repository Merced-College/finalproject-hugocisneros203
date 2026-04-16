#include <iostream>
#include <string>
#include <limits>
#include "TaskManager.h"

// -------------------------------------------
// Helper: clear bad input from cin
// -------------------------------------------
void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// -------------------------------------------
// Display the main menu
// -------------------------------------------
void showMenu() {
    std::cout << "\n========================================\n";
    std::cout << "         STUDENT TASK MANAGER\n";
    std::cout << "========================================\n";
    std::cout << "  1. Add a task\n";
    std::cout << "  2. Remove a task\n";
    std::cout << "  3. Mark task as complete\n";
    std::cout << "  4. Mark task as incomplete\n";
    std::cout << "  5. View all tasks\n";
    std::cout << "  6. View stats & points\n";
    std::cout << "  7. Save tasks\n";
    std::cout << "  8. Load tasks\n";
    std::cout << "  9. Exit\n";
    std::cout << "========================================\n";
    std::cout << "  Enter choice: ";
}

// -------------------------------------------
// Main entry point
// -------------------------------------------
int main() {
    TaskManager manager;
    int choice = 0;

    std::cout << "\nWelcome to the Student Task Manager!\n";
    std::cout << "Trying to load saved tasks...\n";
    manager.load();

    while (true) {
        showMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            clearInput();
            std::cout << "  Please enter a number.\n";
            continue;
        }
        clearInput();

        // ---- Add a task ----
        if (choice == 1) {
            std::string name;
            int pChoice = 0;

            std::cout << "  Task name: ";
            std::getline(std::cin, name);
            if (name.empty()) {
                std::cout << "  Task name cannot be empty.\n";
                continue;
            }

            std::cout << "  Priority (1=High, 2=Medium, 3=Low): ";
            std::cin >> pChoice;
            clearInput();

            if (pChoice < 1 || pChoice > 3) {
                std::cout << "  Invalid priority. Defaulting to Low.\n";
                pChoice = 3;
            }

            manager.addTask(name, intToPriority(pChoice));
        }

        // ---- Remove a task ----
        else if (choice == 2) {
            manager.displayTasks();
            std::cout << "  Enter task number to remove: ";
            int idx;
            std::cin >> idx;
            clearInput();
            manager.removeTask(idx);
        }

        // ---- Mark complete ----
        else if (choice == 3) {
            manager.displayTasks();
            std::cout << "  Enter task number to complete: ";
            int idx;
            std::cin >> idx;
            clearInput();
            manager.completeTask(idx);
        }

        // ---- Mark incomplete ----
        else if (choice == 4) {
            manager.displayTasks();
            std::cout << "  Enter task number to mark incomplete: ";
            int idx;
            std::cin >> idx;
            clearInput();
            manager.uncompleteTask(idx);
        }

        // ---- View tasks ----
        else if (choice == 5) {
            manager.displayTasks();
        }

        // ---- Stats & points ----
        else if (choice == 6) {
            manager.displayStats();
        }

        // ---- Save ----
        else if (choice == 7) {
            manager.save();
        }

        // ---- Load ----
        else if (choice == 8) {
            manager.load();
        }

        // ---- Exit ----
        else if (choice == 9) {
            std::cout << "  Saving before exit...\n";
            manager.save();
            std::cout << "  Goodbye! Keep being productive!\n";
            break;
        }

        else {
            std::cout << "  Invalid option. Please choose 1-9.\n";
        }
    }

    return 0;
}
