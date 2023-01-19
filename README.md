This program takes in the number of iterations to be performed, amount of clusters the data needs to be sperated into and a file containing points represented in xy-coordinates.
It returns the cluster id of each input point by performing the K-Means clustering algorithm.

Note about K Means:
K-means is a centroid-based clustering algorithm where each data point is assigned to a cluster based on the distance between it and a centroid.
Finding the K number of groups in the dataset is the objective. 
Each data point is assigned to a group iteratively, and over time, data points are clustered according to shared characteristics. 
In order to determine which group each data point should belong to, the goal is to reduce the sum of distances between the data points and the cluster centroid.

Sample input arguments:
5 2 input_k_means.txt
