#include <iostream>
#include <deque>
#include <vector>

class Process {
public:
    std::string process_name;
    int arrival_time;
    int stop_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;

    Process(const std::string& name, int arrival, int burst)
        : process_name(name), arrival_time(arrival), stop_time(arrival), burst_time(burst), waiting_time(0), turnaround_time(0) {}
};

class MLFQ {
private:
    int number_of_queues;
    std::vector<int> time_slices;
    std::deque<Process> ready_queue;
    int current_time;
    std::deque<Process> finish_queue;

public:
    MLFQ(int num_queues, const std::vector<int>& slices, const std::deque<Process>& queue, int time)
        : number_of_queues(num_queues), time_slices(slices), ready_queue(queue), current_time(time) {}

    std::vector<std::string> calculate_sequence_of_finish_queue() {
        std::vector<std::string> sequence;
        for (const Process& process : finish_queue) {
            sequence.push_back(process.process_name);
        }
        return sequence;
    }

    std::vector<int> calculate_waiting_time(const std::deque<Process>& queue) {
        std::vector<int> waiting_times;
        for (const Process& process : queue) {
            waiting_times.push_back(process.waiting_time);
        }
        return waiting_times;
    }

    std::vector<int> calculate_turnaround_time(const std::deque<Process>& queue) {
        std::vector<int> turnaround_times;
        for (const Process& process : queue) {
            turnaround_times.push_back(process.turnaround_time);
        }
        return turnaround_times;
    }

    std::vector<int> calculate_completion_time(const std::deque<Process>& queue) {
        std::vector<int> completion_times;
        for (const Process& process : queue) {
            completion_times.push_back(process.stop_time);
        }
        return completion_times;
    }

    std::vector<int> calculate_remaining_burst_time_of_processes(const std::deque<Process>& queue) {
        std::vector<int> remaining_burst_times;
        for (const Process& process : queue) {
            remaining_burst_times.push_back(process.burst_time);
        }
        return remaining_burst_times;
    }

    int update_waiting_time(Process& process) {
        process.waiting_time += current_time - process.stop_time;
        return process.waiting_time;
    }

    std::deque<Process> first_come_first_served(std::deque<Process> ready_queue) {
        std::deque<Process> finished;
        while (!ready_queue.empty()) {
            Process current_process = ready_queue.front();
            ready_queue.pop_front();

            if (current_time < current_process.arrival_time) {
                current_time = current_process.arrival_time;
            }

            update_waiting_time(current_process);
            current_time += current_process.burst_time;
            current_process.burst_time = 0;
            current_process.turnaround_time = current_time - current_process.arrival_time;
            current_process.stop_time = current_time;
            finished.push_back(current_process);
        }
        finish_queue.insert(finish_queue.end(), finished.begin(), finished.end());
        return finished;
    }

    std::deque<Process> round_robin(std::deque<Process> ready_queue, int time_slice) {
        std::deque<Process> finished;
        for (int i = 0; i < ready_queue.size(); ++i) {
            Process current_process = ready_queue.front();
            ready_queue.pop_front();

            if (current_time < current_process.arrival_time) {
                current_time = current_process.arrival_time;
            }

            update_waiting_time(current_process);

            if (current_process.burst_time > time_slice) {
                current_time += time_slice;
                current_process.burst_time -= time_slice;
                current_process.stop_time = current_time;
                ready_queue.push_back(current_process);
            } else {
                current_time += current_process.burst_time;
                current_process.burst_time = 0;
                current_process.stop_time = current_time;
                current_process.turnaround_time = current_time - current_process.arrival_time;
                finished.push_back(current_process);
            }
        }
        finish_queue.insert(finish_queue.end(), finished.begin(), finished.end());
        return finished;
    }

    std::deque<Process> multi_level_feedback_queue() {
        for (int i = 0; i < number_of_queues - 1; ++i) {
            std::deque<Process> finished = round_robin(ready_queue, time_slices[i]);
            ready_queue.insert(ready_queue.end(), finished.begin(), finished.end());
        }
        first_come_first_served(ready_queue);
        return finish_queue;
    }
};

int main() {
    std::vector<int> time_slices = {17, 25};
    std::deque<Process> queue = {
        Process("P1", 0, 53),
        Process("P2", 0, 17),
        Process("P3", 0, 68),
        Process("P4", 0, 24)
    };

    MLFQ mlfq(3, time_slices, queue, 0);
    mlfq.multi_level_feedback_queue();

    std::cout << "Waiting Time:\t\t";
    for (int time : mlfq.calculate_waiting_time(queue)) {
        std::cout << time << "\t";
    }
    std::cout << "\n";

    std::cout << "Completion Time:\t";
    for (int time : mlfq.calculate_completion_time(queue)) {
        std::cout << time << "\t";
    }
    std::cout << "\n";

    std::cout << "Turnaround Time:\t";
    for (int time : mlfq.calculate_turnaround_time(queue)) {
        std::cout << time << "\t";
    }
    std::cout << "\n";

    std::cout << "Sequence of Finished Processes: ";
    for (const std::string& name : mlfq.calculate_sequence_of_finish_queue()) {
        std::cout << name << "\t";
    }
    std::cout << "\n";

    return 0;
}
