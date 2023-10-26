#include <iostream>
#include <vector>
#include <algorithm>

// Define a structure to represent a process with priority
struct Process {
    int id;         // Process ID
    int priority;   // Priority (lower number indicates higher priority)
    int burst;      // Burst time

    Process(int id, int priority, int burst)
        : id(id), priority(priority), burst(burst) {}
};

// Comparison function for sorting processes by priority
bool comparePriority(const Process& a, const Process& b) {
    return a.priority < b.priority;
}

// Priority Scheduling algorithm
void priorityScheduling(std::vector<Process>& processes) {
    // Sort processes by priority (lower priority first)
    std::sort(processes.begin(), processes.end(), comparePriority);

    // Initialize waiting times and turnaround times
    std::vector<int> waitingTimes(processes.size(), 0);
    std::vector<int> turnaroundTimes(processes.size(), 0);

    // Calculate waiting times and turnaround times
    waitingTimes[0] = 0;
    for (int i = 1; i < processes.size(); i++) {
        waitingTimes[i] = waitingTimes[i - 1] + processes[i - 1].burst;
    }
    for (int i = 0; i < processes.size(); i++) {
        turnaroundTimes[i] = waitingTimes[i] + processes[i].burst;
    }

    // Calculate average waiting time and average turnaround time
    double totalWaitingTime = 0;
    double totalTurnaroundTime = 0;
    for (int i = 0; i < processes.size(); i++) {
        totalWaitingTime += waitingTimes[i];
        totalTurnaroundTime += turnaroundTimes[i];
    }
    double averageWaitingTime = totalWaitingTime / processes.size();
    double averageTurnaroundTime = totalTurnaroundTime / processes.size();

    // Print the results
    std::cout << "Process ID\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < processes.size(); i++) {
        std::cout << processes[i].id << "\t\t" << processes[i].priority << "\t\t" << processes[i].burst << "\t\t" << waitingTimes[i] << "\t\t" << turnaroundTimes[i] << "\n";
    }
    std::cout << "Average Waiting Time = " << averageWaitingTime << "\n";
    std::cout << "Average Turnaround Time = " << averageTurnaroundTime << "\n";
}

int main() {
    // Create a vector of processes with their priority and burst time
    std::vector<Process> processes = {
        Process(1, 2, 10),
        Process(2, 1, 6),
        Process(3, 3, 8)
    };

    // Run the Priority Scheduling algorithm
    priorityScheduling(processes);

    return 0;
}
