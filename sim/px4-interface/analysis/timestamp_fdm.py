import numpy as np
import os
import matplotlib.pyplot as plt

"""
"timestamp_fdm_log.txt")
LOG_PATH_SENSOR      = os.path.join(desktop, "timestamp_hil_sensor_log.txt")
LOG_PATH_GPS         = os.path.join(desktop, "timestamp_hil_gps_log.txt")
LOG_PATH_STATE_Q     = os.path.join(desktop, "timestamp_hil_state_q_log.txt")
LOG_PATH_HEARTBEAT   = os.path.join(desktop, "timestamp_heartbeat_sent_log.txt")

"""
# add path
desktop = os.path.expanduser("~/Desktop")
file = os.path.join(desktop, "timestamp_hil_sensor_log.txt")

# load the file created and extract the relative info (actual delta time at each step)
values = []
with open(file, "r") as timestamp_file:
    for line in timestamp_file:
        line = line.strip()
        if "hil_sensor sent to px4 - timestamp: " in line:
            dt_str = line.split("hil_sensor sent to px4 - timestamp: ")[1].strip()
            dt = float(dt_str)
            values.append(dt)
data = np.array(values)


# plot the bell curve - config for the appearance of the curve 
plt.hist(data, bins =50, density=True, alpha=0.6)

# guassian distribution 
mu = np.mean(data)
sigma = np.std(data)

x = np.linspace(min(data), max(data), 200)
gaussian = (1/(sigma*np.sqrt(2*np.pi))) * np.exp(-(x-mu)**2 / (2*sigma**2))


# plot results
plt.plot(x, gaussian)
plt.title("HIL_SENSOR Timing Bell Curve")
plt.xlabel("dt (seconds)")
plt.ylabel("Probability Density")
plt.show()


"""

print("Mean:", mu)
print("Std Dev:", sigma)

"""
