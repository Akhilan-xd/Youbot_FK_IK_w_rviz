import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Create 3D data
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Sample data
x = np.array([0.145139, 0.0549935])
y = np.array([0.0271015, 0.000541192])
z = np.array([0.581, 0.535])

# Plot 3D line
ax.plot(x, y, z, label='3D Line', linestyle='dotted', color='b')
ax.scatter(x, y, z, color='r', label='Points')  # Mark the points
ax.set_xlabel('X-axis')
ax.set_ylabel('Y-axis')
ax.set_zlabel('Z-axis')
ax.legend()
plt.show()

# Calculate Euclidean distance
x1, y1, z1 = x[0], y[0], z[0]
x2, y2, z2 = x[1], y[1], z[1]
distance = np.sqrt((x2 - x1)**2 + (y2 - y1)**2 + (z2 - z1)**2)

print(f"The Euclidean distance between the points is: {distance:.4f} units")
