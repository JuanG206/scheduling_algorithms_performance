#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <climits>  // Include this header for INT_MAX

struct Process {
    int pid;               // ID del proceso
    int arrival_time;      // Tiempo de llegada del proceso
    int burst_time;        // Tiempo de ráfaga (duración del proceso)
    int remaining_time;    // Tiempo restante para completar el proceso (para algoritmos preemptivos)
    int priority;          // Prioridad del proceso (usada en prioridad)
    int completion_time;   // Tiempo de finalización del proceso
    int waiting_time;      // Tiempo de espera del proceso
    int turnaround_time;   // Tiempo de retorno (turnaround) del proceso
    
    Process(int id, int at, int bt, int pr = 0) :
        pid(id), arrival_time(at), burst_time(bt), remaining_time(bt), priority(pr),
        completion_time(0), waiting_time(0), turnaround_time(0) {}
};

std::vector<Process> generate_processes(int n) {
    std::vector<Process> processes;
    for (int i = 0; i < n; ++i) {
        int arrival_time = rand() % 10;
        int burst_time = 1 + rand() % 10;
        int priority = 1 + rand() % 5;
        processes.push_back(Process(i + 1, arrival_time, burst_time, priority));
    }
    return processes;
}

void fcfs_scheduling(std::vector<Process>& processes) {
    std::sort(processes.begin(), processes.end(), [](Process& a, Process& b) {
        return a.arrival_time < b.arrival_time;
    });
    int current_time = 0;
    for (auto& process : processes) {
        if (current_time < process.arrival_time)
            current_time = process.arrival_time;
        process.waiting_time = current_time - process.arrival_time;
        process.completion_time = current_time + process.burst_time;
        process.turnaround_time = process.completion_time - process.arrival_time;
        current_time += process.burst_time;
    }
}

void sjf_scheduling(std::vector<Process>& processes, bool preemptive) {
    int current_time = 0;
    int completed = 0;
    std::vector<bool> is_completed(processes.size(), false);
    while (completed < processes.size()) {
        int idx = -1;
        int min_burst = INT_MAX;
        for (int i = 0; i < processes.size(); i++) {
            if (processes[i].arrival_time <= current_time && !is_completed[i]) {
                if (preemptive && processes[i].remaining_time < min_burst) {
                    min_burst = processes[i].remaining_time;
                    idx = i;
                } else if (!preemptive && processes[i].burst_time < min_burst) {
                    min_burst = processes[i].burst_time;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            if (preemptive) {
                processes[idx].remaining_time--;
                if (processes[idx].remaining_time == 0) {
                    processes[idx].completion_time = current_time + 1;
                    processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
                    processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
                    is_completed[idx] = true;
                    completed++;
                }
                current_time++;
            } else {
                current_time += processes[idx].burst_time;
                processes[idx].completion_time = current_time;
                processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
                processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
                is_completed[idx] = true;
                completed++;
            }
        } else {
            current_time++;
        }
    }
}

void round_robin_scheduling(std::vector<Process>& processes, int time_quantum) {
    std::queue<Process*> queue;
    int current_time = 0;
    
    // Initialize the queue with processes that have arrived by current_time
    for (auto& process : processes)
        if (process.arrival_time <= current_time)
            queue.push(&process);

    while (!queue.empty()) {
        Process* process = queue.front();
        queue.pop();

        if (process->remaining_time > time_quantum) {
            current_time += time_quantum;
            process->remaining_time -= time_quantum;
            for (auto& p : processes) {
                if (p.arrival_time <= current_time && p.remaining_time > 0 && &p != process) {
                    queue.push(&p);
                }
            }
            queue.push(process);  // Re-queue the process
        } else {
            current_time += process->remaining_time;
            process->remaining_time = 0;
            process->completion_time = current_time;
            process->turnaround_time = process->completion_time - process->arrival_time;
            process->waiting_time = process->turnaround_time - process->burst_time;
        }
    }
}

void print_processes(const std::vector<Process>& processes) {
    std::cout << "PID\tArrival\tBurst\tPriority\tCompletion\tWaiting\tTurnaround\n";
    for (const auto& process : processes) {
        std::cout << process.pid << "\t"
                  << process.arrival_time << "\t"
                  << process.burst_time << "\t"
                  << process.priority << "\t\t"
                  << process.completion_time << "\t\t"
                  << process.waiting_time << "\t"
                  << process.turnaround_time << "\n";
    }
}

void calculate_metrics(const std::vector<Process>& processes) {
    int total_waiting_time = 0, total_turnaround_time = 0;
    for (const auto& process : processes) {
        total_waiting_time += process.waiting_time;
        total_turnaround_time += process.turnaround_time;
    }
    double avg_waiting_time = static_cast<double>(total_waiting_time) / processes.size();
    double avg_turnaround_time = static_cast<double>(total_turnaround_time) / processes.size();
    std::cout << "Average Waiting Time: " << avg_waiting_time << "\n";
    std::cout << "Average Turnaround Time: " << avg_turnaround_time << "\n";
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    int n = 5;  // Número de procesos
    int time_quantum = 3;  // Quantum para Round Robin

    std::vector<Process> processes = generate_processes(n);

    std::cout << "\nFCFS Scheduling:\n";
    fcfs_scheduling(processes);
    print_processes(processes);
    calculate_metrics(processes);

    std::cout << "\nSJF Scheduling (Non-Preemptive):\n";
    sjf_scheduling(processes, false);
    print_processes(processes);
    calculate_metrics(processes);

    std::cout << "\nRound Robin Scheduling:\n";
    round_robin_scheduling(processes, time_quantum);
    print_processes(processes);
    calculate_metrics(processes);

    return 0;
}

