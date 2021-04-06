import numpy as np
import matplotlib.pyplot as plt
from matplotlib.collections import LineCollection
#coord1 = [[1, 0], [0, 1], [2, 1], [1, 0]]
#coord2 = coord1 * 2
#	coordX0 = np.array([1, 3, 5, 7, 9, np.nan])
coordX0 = np.array([1, 3, 5, 7, 9])
#	coordY0 = np.array([0, 0, 0, 0, 0, np.nan])
coordY0 = np.array([0, 0, 0, 0, 0])
coord0 = np.stack((coordX0, coordY0), axis = 1)

coordX1 = np.array([0, 2, 4, 6, 8, 10])
coordY1 = np.array([1, 1, 1, 1, 1, 1])
coord1 = np.stack((coordX1, coordY1), axis = 1)

coordX2 = np.array([1, 3, 5, 7, 9, 11])
coordY2 = np.array([2, 2, 2, 2, 2, 2])
coord2 = np.stack((coordX2, coordY2), axis = 1)

#	coordX3 = np.array([np.nan, 2, 4, 6, 8, 10])
coordX3 = np.array([2, 4, 6, 8, 10])
#	coordY3 = np.array([np.nan, 3, 3, 3, 3, 3])
coordY3 = np.array([3, 3, 3, 3, 3])
coord3 = np.stack((coordX3, coordY3), axis = 1)

coordX = np.concatenate((coordX0, coordX1, coordX2, coordX3))
coordY = np.concatenate((coordY0, coordY1, coordY2, coordY3))

edges = [[0, 5], [0, 6], [5, 6], [6, 1], [1, 7], [7, 6], [7, 2], [2, 8], [8, 3], [8, 7], [3, 9], [9, 4], [9, 8], [4, 10], [10, 9],
		 [5, 11], [11, 6], [6, 12], [12, 7], [7, 13], [13, 8], [8, 14], [14, 9], [9, 15], [15, 10], [10, 16],
		 [11, 12], [12, 13], [13, 14], [14, 15], [15, 16],
		 [11, 17], [17, 12], [12, 18], [18, 13], [13, 19], [19, 14], [14, 20], [20, 15], [15, 21], [21, 16]]
points = np.concatenate((coord0, coord1, coord2, coord3))

print (points[0])
'''
lc = LineCollection(points[edges])
fig = plt.figure()
plt.gca().add_collection(lc)
plt.xlim(points[:,0].min(), points[:,0].max())
plt.ylim(points[:,1].min(), points[:,1].max())
plt.plot(points[:,0], points[:,1], 'ro')
fig.savefig('full_figure.png')
'''
x = coordX.flatten()
y = coordY.flatten()

#print (x)
#print (y)
edgesT = np.transpose(edges)
#print(edgesT)

plt.plot(x[edgesT], y[edgesT], linestyle='-', color='y',
        markerfacecolor='red', marker='o')

plt.show()


	#	coord.append(coord[0]) #repeat the first point to create a 'closed loop'

#	xs, ys = zip(*coord2) #create lists of x and y values

#plt.figure()
#plt.plot(xs,ys)
#plt.show() # if you need...
