import numpy as np
import matplotlib.pyplot as plt


mat = np.loadtxt('bin/test.csv',delimiter=',',dtype=float)

plt.pcolormesh(mat)
plt.xlabel("Values of r [fm]")
plt.ylabel("Values of z [fm]")
plt.title("Plot of the nuclear density")
plt.legend()
plt.show()