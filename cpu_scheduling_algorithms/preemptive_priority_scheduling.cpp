#include <iostream>
#include <vector>
#include <algorithm>

// Define a structure to represent a process with priority
struct Process {
    int id;         // Process ID
    int priority;   // Priority (lower number indicates higher priority)
    int burst;      // Burst time
    int remaining;  // Remaining burst time

    Process(int id, int priority, int burst)
        : id(id), priority(priority), burst(burst), remaining(burst) {}
};

// Comparison function for sorting processes by priority
bool comparePriority(const Process& a, const Process& b) {
    return a.priority < b.priority;
}

// Preemptive Priority Scheduling algorithm
void preemptivePriorityScheduling(std::vector<Process>& processes) {
    int currentTime = 0;
    int completed = 0;

    // Sort processes by priority (lower priority first)
    std::sort(processes.begin(), processes.end(), comparePriority);

    std::cout << "Gantt Chart:" << std::endl;

    while (completed < processes.size()) {
        int highestPriority = INT_MAX;
        int selectedProcess = -1;

        // Find the process with the highest priority that has arrived and has remaining burst time
        for (int i = 0; i < processes.size(); i++) {
            if (processes[i].remaining > 0 && processes[i].priority < highestPriority && processes[i].id != selectedProcess) {
                highestPriority = processes[i].priority;
                selectedProcess = processes[i].id;
            }
        }

        if (selectedProcess != -1) {
            std::cout << "P" << selectedProcess << " | ";
            processes[selectedProcess - 1].remaining--;

            if (processes[selectedProcess - 1].remaining == 0) {
                completed++;
                int completionTime = currentTime + 1;
                std::cout << "Completion time: " << completionTime << std::endl;
            }
        } else {
            std::cout << "Idle | ";
        }

        currentTime++;
    }
}

int main() {
    // Create a vector of processes with their priority and burst time
    std::vector<Process> processes = {
        Process(1, 2, 6),
        Process(2, 1, 8),
        Process(3, 3, 4),
        Process(4, 1, 5)
    };

    // Run Preemptive Priority Scheduling algorithm
    preemptivePriorityScheduling(processes);

    return 0;
}
