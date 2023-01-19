/******************************************************************************

K Means Algorithm
Author: Amirtha Varshini

*******************************************************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cmath>
#include <memory>

using namespace std;

// x,y - coordinates on the 2D XY plane
// cluster_id - assigned cluster, by default -1(not assigned)
struct data {
	double x, y;
	int cluster_id = -1;
};

int main()
{

	vector<data> data_points; //vector of data coordinates
	unsigned int t, k; // t - number of iterations to be performed on the algo, k - amount of clusters
	string input_filename; 
    cout<<"Enter the number of iterations to be performed on the algo, amount of clusters and the input file name" << "\n";;
    cin >> t >> k >> input_filename;
    try {
        ifstream file(input_filename); 
	    while (!file.eof()) {
            data temp;
            file >> temp.x >> temp.y;
            data_points.push_back(temp);
	    }
	    file.close();
    } catch (const std::exception& e) {
        std::cout << "Caught exception \"" << e.what() << "\"\n";
        return 0;
    }
	
	// finding bounding box of data points	
	auto temp = max_element(data_points.begin(), data_points.end(), [](data a, data b) {return a.x < b.x; }); // finds iterator to the greatest element in the rang
	int max_x = temp->x;
	temp = max_element(data_points.begin(), data_points.end(), [](data a, data b) {return a.y < b.y; });
	int max_y = temp->y;
	temp = min_element(data_points.begin(), data_points.end(), [](data a, data b) {return a.x < b.x; });
	int min_x = temp->x;
	temp = min_element(data_points.begin(), data_points.end(), [](data a, data b) {return a.y < b.y; });
	int min_y = temp->y;

	// initial centers with rand coordinates within bounding box
	vector<data> centers(k);
	for (unsigned int i = 0; i < k; i++) {
		centers[i].x = rand() % (max_x - min_x + 1) + min_x;
		centers[i].y = rand() % (max_y - min_y + 1) + min_y;
	}

	// for loop over number of iterations
	for (unsigned int i = 0; i < t; i++) {
		// distance calculation from data point to centers for every point 
		for (unsigned int j = 0; j < data_points.size(); j++) {
			double* dists = new double[k];
			for (unsigned int p = 0; p < k; p++) {
				double a = abs(data_points[j].y - centers[p].y);	// y distance
				double b = abs(data_points[j].x - centers[p].x);	// x distance
				dists[p] = sqrt(pow(a, 2) + pow(b, 2));	// L2 distance from point to center
			}
			// assign cluster with closest center
			data_points[j].cluster_id = min_element(dists, dists + k) - dists;
			delete[] dists;
		}
		// calculating new centers
		unique_ptr<double[]> sum_x(new double[k], default_delete<double[]>());
		unique_ptr<double[]> sum_y(new double[k], default_delete<double[]>());
		unique_ptr<int[]> count = make_unique<int[]>(k);
		// init with 0, sum_x and sum_y represent sum of coordinates of the points belonging to a particular cluster in x and y axis, respectively
		for (unsigned int p = 0; p < k; p++) {
			sum_x[p] = 0;
			sum_y[p] = 0;
			count[p] = 0;
		}
        // iterate over each data point and find the total number of points belong to each cluster id in count
		for (unsigned int f = 0; f < data_points.size(); f++) {
			sum_x[data_points[f].cluster_id] += data_points[f].x;
			sum_y[data_points[f].cluster_id] += data_points[f].y;
			count[data_points[f].cluster_id]++;
		}
		// set new centers to average coordinate of points in cluster
		for (unsigned int f = 0; f < k; f++) {
			centers[f].x =sum_x[f] / count[f];
			centers[f].y = sum_y[f] / count[f];
		}
	}

    // Output is saved in output.txt
	ofstream ofile("output.txt"); 
	ofile << "The cluster ids and their centres are as follows" <<"\n";
	for (unsigned int f = 0; f < k; f++) {
			ofile << f << "( " << centers[f].x << "," << centers[f].y << " )\n";
		}
	ofile << "<data point number> <cluster number>" <<"\n";
	for (unsigned int i = 0; i < data_points.size(); i++) {
		ofile << i << " " << data_points[i].cluster_id << "\n";
	}
	
	ofile.close();
}
