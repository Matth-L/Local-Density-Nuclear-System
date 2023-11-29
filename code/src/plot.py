import numpy as np
import matplotlib.pyplot as plt


mat = np.loadtxt('bin/test.csv',delimiter=',',dtype=float)

plt.pcolormesh(mat)
plt.xlabel("Values of z [fm]")
plt.ylabel("Values of x [fm]")
plt.title("Plot of the nuclear density")
plt.legend()
plt.show()