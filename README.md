# Report: Process Scheduling Algorithm Simulation

## Project Purpose

The goal of this project is to simulate three process scheduling algorithms in an operating system: **FCFS (First-Come, First-Served)**, **SJF (Shortest Job First)**, and **Round Robin**. The simulation allows observing how these algorithms manage process execution, calculating key metrics such as waiting time and turnaround time. The purpose is to compare the performance of the algorithms based on these times and understand their behavior in different scheduling scenarios.

## Algorithm Description

### 1. **FCFS (First-Come, First-Served)**:
   - Processes are executed in the order they arrive at the system, without preemption.
   - This algorithm is simple but can result in high waiting times if a long process arrives before shorter ones.

### 2. **SJF (Shortest Job First)**:
   - Processes with the shortest burst time (execution time) are executed first.
   - It is implemented in two versions:
     - **Non-preemptive**: The currently running process is not interrupted.
     - **Preemptive**: If a new process with a shorter burst time arrives while another process is running, the current process is interrupted.

### 3. **Round Robin**:
   - Processes are executed in a cyclic manner, each getting a fixed time slice (quantum).
   - If a process doesn't finish in its quantum, it goes back to the queue to wait for the next round.

## Code Functionality

1. **Process Generation**:
   - Processes are created with random arrival times, burst times, and priorities. The number of processes is configurable.

2. **Process Scheduling**:
   - **FCFS**: Processes are sorted by arrival time and executed in that order.
   - **SJF**: The processes with the shortest burst time are executed first. In the preemptive version, if a process with a shorter burst arrives, the current process is interrupted.
   - **Round Robin**: Each process gets a fixed time quantum to execute. If it doesn't finish, it is requeued.

3. **Metric Calculation**:
   - After executing each algorithm, the waiting time, completion time, and turnaround time of each process are calculated.
   - Average waiting and turnaround times are computed to compare the performance of each algorithm.

## Execution Workflow

1. **Process Generation**: `n` processes are created with random arrival times, burst times, and priorities.

2. **Algorithm Execution**:
   - The three scheduling algorithms—FCFS, SJF (preemptive and non-preemptive), and Round Robin—are applied sequentially.

3. **Result Display**:
   - For each algorithm, the process details (PID, arrival time, burst time, completion time, waiting time, and turnaround time) are displayed.

4. **Metric Calculation**: The average waiting time and average turnaround time are calculated to evaluate each algorithm's performance.

## Conclusion

This project demonstrates how different scheduling algorithms affect process execution and allows comparing their performance in terms of efficiency. Algorithms like FCFS can result in high waiting times, while SJF and Round Robin provide a more balanced approach to CPU time distribution among processes.
