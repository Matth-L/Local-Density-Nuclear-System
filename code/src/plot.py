import numpy as np
import matplotlib.pyplot as plt

mat = np.loadtxt('bin/test.csv',delimiter=',',dtype=float)
mat2 = np.loadtxt('bin/naive.csv',delimiter=',',dtype=float)

plt.figure(figsize=(10, 5))

plt.subplot(1, 2, 1)
plt.pcolormesh(mat)
plt.xlabel("Values of r [fm]")
plt.ylabel("Values of z [fm]")
plt.title("Plot of the nuclear density for mat")
plt.colorbar()

plt.subplot(1, 2, 2)
plt.pcolormesh(mat2)
plt.xlabel("Values of r [fm]")
plt.ylabel("Values of z [fm]")
plt.title("Plot of the nuclear density for naive")
plt.colorbar()

plt.tight_layout()
plt.show()