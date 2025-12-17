import numpy as np
import os
import matplotlib.pyplot as plt

# ----------------------------
# Paths
# ----------------------------
desktop = os.path.expanduser("~/Desktop")

LOG_FILES = {
    "FDM Step Timing": os.path.join(desktop, "timestamp_fdm_log.txt"),
    "HIL_SENSOR Timing": os.path.join(desktop, "timestamp_hil_sensor_log.txt"),
    "HIL_GPS Timing": os.path.join(desktop, "timestamp_hil_gps_log.txt"),
    "HIL_STATE_Q Timing": os.path.join(desktop, "timestamp_hil_state_q_log.txt"),
    "HEARTBEAT Send Timing": os.path.join(desktop, "timestamp_heartbeat_sent_log.txt"),
}

KEYWORDS = {
    "FDM Step Timing": "fdm step dt:",
    "HIL_SENSOR Timing": "hil_sensor sent to px4 - timestamp:",
    "HIL_GPS Timing": "hil_gps sent to px4 - timestamp:",
    "HIL_STATE_Q Timing": "hil_state_quaternion sent to px4 - timestamp:",
    "HEARTBEAT Send Timing": "heartbeat sent to px4 - timestamp:",
}

# ----------------------------
# Helpers
# ----------------------------
def extract_dt_list(filepath, keyword):
    if not os.path.exists(filepath):
        print(f"File not found: {filepath}")
        return None

    values = []
    with open(filepath, "r") as f:
        for line in f:
            if keyword in line:
                try:
                    values.append(float(line.split(keyword)[1].strip()))
                except:
                    pass

    return np.array(values) if len(values) else None


# ----------------------------
# Main analysis
# ----------------------------
for title, path in LOG_FILES.items():
    keyword = KEYWORDS[title]
    data = extract_dt_list(path, keyword)

    if data is None:
        print(f"No valid data for {title}")
        continue

    # Statistics
    mu = np.mean(data)
    sigma = np.std(data)
    dmin = np.min(data)
    dmax = np.max(data)
    N = len(data)
    duration = np.sum(data)

    print("\n-----------------------------------")
    print(title)
    print(f"Samples: {N}")
    print(f"Min Δt: {dmin:.6f} s")
    print(f"Max Δt: {dmax:.6f} s")
    print(f"Mean Δt: {mu:.6f} s")
    print(f"Std Dev: {sigma:.6f} s")
    print(f"Log duration: {duration:.3f} s")

    # ----------------------------
    # Histogram + Gaussian
    # ----------------------------
    plt.figure(figsize=(7,5))
    plt.hist(data, bins=50, density=True, alpha=0.6, label="Histogram")

    x = np.linspace(dmin, dmax, 300)
    gaussian = (1/(sigma*np.sqrt(2*np.pi))) * np.exp(-(x-mu)**2/(2*sigma**2))
    plt.plot(x, gaussian, linewidth=2, label="Gaussian Fit")

    plt.title(f"{title} – Distribution")
    plt.xlabel("Δt (seconds)")
    plt.ylabel("Probability Density")
    plt.legend()
    plt.grid(alpha=0.3)
    plt.show()

    # ----------------------------
    # Time-domain (sample index)
    # ----------------------------
    spike_mask = data > (2.0 * mu)

    plt.figure(figsize=(10,4))
    plt.plot(data, linewidth=1, label="Δt")
    plt.scatter(np.where(spike_mask), data[spike_mask],
                color="red", s=12, label="Spikes (>2× mean)")

    plt.axhline(mu, linestyle="--", label="Mean")
    plt.axhline(mu + 3*sigma, linestyle="--", label="+3σ")
    plt.axhline(mu - 3*sigma, linestyle="--", label="-3σ")

    plt.title(f"{title} – Δt vs Sample Index")
    plt.xlabel("Sample index")
    plt.ylabel("Δt (seconds)")
    plt.legend()
    plt.grid(alpha=0.3)
    plt.show()

    # ----------------------------
    # Time-domain (real time)
    # ----------------------------
    time_axis = np.cumsum(data)

    plt.figure(figsize=(10,4))
    plt.plot(time_axis, data, linewidth=1, label="Δt")
    plt.scatter(time_axis[spike_mask], data[spike_mask],
                color="red", s=12, label="Spikes (>2× mean)")

    plt.axhline(mu, linestyle="--", label="Mean")

    plt.title(f"{title} – Δt vs Real Time")
    plt.xlabel("Time since start (seconds)")
    plt.ylabel("Δt (seconds)")
    plt.legend()
    plt.grid(alpha=0.3)
    plt.show()
