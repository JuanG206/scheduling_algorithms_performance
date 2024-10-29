import matplotlib.pyplot as plt
import numpy as np

# Data
algorithms = ['FCFS', 'SJF (Non-Preemptive)', 'Round Robin']
average_waiting_time = [8.6, 4.0, 12.6]
average_turnaround_time = [12.8, 8.2, 16.8]

# Set the position of bar on X axis
bar_width = 0.35
r1 = np.arange(len(algorithms))
r2 = [x + bar_width for x in r1]

# Create the bars
plt.bar(r1, average_waiting_time, color='b', width=bar_width, edgecolor='grey', label='Average Waiting Time')
plt.bar(r2, average_turnaround_time, color='g', width=bar_width, edgecolor='grey', label='Average Turnaround Time')

# Add labels
plt.xlabel('Algorithms', fontweight='bold')
plt.xticks([r + bar_width / 2 for r in range(len(algorithms))], algorithms)
plt.ylabel('Time (in units)')
plt.title('Average Waiting Time and Turnaround Time for Scheduling Algorithms')

# Add legend
plt.legend()

# Show the plot
plt.tight_layout()
plt.grid(axis='y')
plt.savefig('scheduling_algorithms_performance.png')  # Save the figure
plt.show()

