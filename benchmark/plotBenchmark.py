import numpy as np
import matplotlib.pyplot as plt

mat = np.loadtxt("benchmark.csv", delimiter=",", dtype=float)

fig, ax = plt.subplots()

ax.plot(mat, label="Benchmark Time")
ax.set_title("Benchmark Time Series")
ax.set_xlabel("Version number")
ax.set_ylabel("Time (MS)")
ax.set_yscale("log")  # Set the y-axis to a logarithmic scale

ax.legend()

plt.show()
