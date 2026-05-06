import numpy as np
import os, sys
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
import scipy.stats as stats
from pathlib import Path
desktop = Path.home() / "Desktop"

LOG_FILES = [
    desktop / "timestamp_fdm_log.csv",
    desktop / "timestamp_hil_sensor_log.csv",
    desktop / "timestamp_hil_gps_log.csv",
    desktop / "execution_time_log.csv"
]

for log_file in LOG_FILES:
    dataset=[]
    file = open(log_file, 'r')
    next(file)  # skip header line

    prev = None 
    for line in file:
        t = float(line.split(',')[0])
        if prev is not None:
            dataset.append(t - prev)

        prev = t
    file.close()
    dataset = np.array(dataset)

    #stats
    mu = np.mean(dataset)
    sigma = np.std(dataset)
    dmin = np.min(dataset)
    dmax = np.max(dataset)
    N = len(dataset)
    var = np.var(dataset)

    # summery 
    print("\n-----------------------------------")
    print(log_file, ": ")
    print(f"Samples: {N}")
    print(f"Min Δt: {dmin:.6f} s")
    print(f"Max Δt: {dmax:.6f} s")
    print(f"Mean Δt: {mu:.6f} s")
    print(f"Std Dev: {sigma:.6f} s")
    print(f"Variance: {var:.14f} s")

    # data at each sample index (dt at each iteration)
    itera = 0
    num_samples = []
    for i in dataset: 
        itera += 1
        num_samples.append(itera)
    plt.plot(num_samples, dataset)
    plt.title("Δt at Each Sample Index")
    plt.xlabel("Sample index")
    plt.ylabel("Δt (seconds)")
    plt.legend()
    plt.grid(alpha=0.3)
    plt.show()

    # reset for next for loop iteration
    num_samples.clear()