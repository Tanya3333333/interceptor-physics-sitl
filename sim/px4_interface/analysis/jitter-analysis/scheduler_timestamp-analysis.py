import numpy as np
import os, sys
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
import scipy.stats as stats
from pathlib import Path


LOG_FILES = [
    "/home/sean/Desktop/timestamp_fdm_log.txt",
    "/home/sean/Desktop/timestamp_hil_sensor_log.txt",
    "/home/sean/Desktop/timestamp_hil_state_q_log.txt",
    "/home/sean/Desktop/timestamp_hil_gps_log.txt",
    "/home/sean/Desktop/timestamp_heartbeat_sent_log.txt"
]

dataset=[]


for log_file in LOG_FILES:
    file = open(log_file, 'r')
    for line in file:
        dt = float(line.split(":")[-1].strip())
        dataset.append(dt)

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

    # Gaussian
    x = np.linspace(dmin, dmax, 300)
    gaussian = (1/(sigma*np.sqrt(2*np.pi))) * np.exp(-(x-mu)**2/(2*sigma**2))
    plt.figure(figsize=(7,5))
    plt.hist(dataset, bins=50, density=True, alpha=0.6, label="Histogram")
    plt.plot(x, gaussian, linewidth=2, label="Gaussian Fit")
    plt.title("Gaussian Distribution")
    plt.xlabel("Δt (seconds)")
    plt.ylabel("Probability Density")
    plt.legend()
    plt.grid(alpha=0.3)
    plt.show()

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
    dataset.clear()
    
