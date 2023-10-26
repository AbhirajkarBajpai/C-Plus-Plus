#include <iostream>
#include <vector>
#include <queue>

// Define a structure to represent a process
struct Process {
    int id;         // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int remaining;  // Remaining burst time

    Process(int id, int arrival, int burst)
        : id(id), arrival(arrival), burst(burst), remaining(burst) {}
};

// Comparison function to sort processes by arrival time
bool compareArrivalTime(const Process& a, const Process& b) {
    return a.arrival < b.arrival;
}

int main() {
    int n; // Number of processes
    std::cout << "Enter the number of processes: ";
    std::cin >> n;

    std::vector<Process> processes;
    for (int i = 0; i < n; i++) {
        int arrival, burst;
        std::cout << "Enter arrival time and burst time for Process " << i + 1 << ": ";
        std::cin >> arrival >> burst;
        processes.push_back(Process(i + 1, arrival, burst));
    }

    // Sort processes by arrival time
    std::sort(processes.begin(), processes.end(), compareArrivalTime);

    // Priority queue to store processes by remaining burst time
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    int currentTime = 0;
    int completed = 0;

    std::cout << "Gantt Chart:" << std::endl;
    
    while (completed < n) {
        // Add processes to the priority queue with remaining burst time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= currentTime && processes[i].remaining > 0) {
                pq.push(std::make_pair(processes[i].burst, processes[i].id));
            }
        }

        if (!pq.empty()) {
            std::pair<int, int> shortestJob = pq.top();
            pq.pop();
            int processId = shortestJob.second;

            std::cout << "P" << processId << " | ";

            // Decrement remaining burst time for the selected process
            processes[processId - 1].remaining--;

            if (processes[processId - 1].remaining == 0) {
                completed++;
                int completionTime = currentTime + 1;
                std::cout << "Completion time: " << completionTime << std::endl;
                processes[processId - 1].remaining = -1; // Mark the process as completed
            }
        } else {
            std::cout << "Idle | ";
        }

        currentTime++;
    }

    return 0;
}
