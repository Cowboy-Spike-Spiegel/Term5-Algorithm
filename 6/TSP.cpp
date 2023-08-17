#include<iostream>
#include<vector>

using namespace std;

// global variables
bool debug = 0;
int district_size;	// districts size
int **districts;		// store distances
int *best_path;
int distance_best = 0;
int distance_tmp = 0;
int *path;

void Tsp(int i);
void swap(int& a, int& b);
void insert_print(int* array, int init_index, int end_index, string insert);

int main(int argc, char* argv[]) {
	// select mode
	if(argc >= 2)
		debug = 1;

	// get districts size
	cin >> district_size;

	// initialize first path
	path = new int[district_size+2];
	for (int i = 1; i <= district_size; i++)
		path[i] = i;
	path[district_size+1] = 1;

	// initialize matrix for dis
	districts = new int*[district_size+1];
	for (int i=0; i <= district_size; i++)
		districts[i] = new int[district_size+1];
	for (int i=1; i <= district_size; i++)
		for (int j = 1; j <= district_size; j++)
			cin >> districts[i][j];

	// allocate best_path
	best_path = new int[district_size+1];

	// start to find district 2
	cout << "\nStart to find:\n";
	Tsp(2);

	// output answer
	cout << "\nThe best path is:\n";
	for (int i = 1; i <= district_size; i++)
		cout << best_path[i] << " -> ";
	cout << "1.\nThe distance of this path is " << distance_best << ".\n";
}

void Tsp(int layer) {
	// output information of this layer
	if(debug) cout << "\n-----Layer: " << layer << "-----\nCurrent path:\n ** ";
	insert_print(path, 1, layer, " -> ");
	if(debug) cout << "Current distance:\n ** " << distance_tmp << "\n";
	
	// has reached the deepest layer, should back to district-1
	if (layer > district_size) {
		int last_distance = districts[path[district_size]][path[1]];
		if(debug) cout << "Has reached the deepest. Add " << last_distance << " back to district-1\n";

		// find the better path, update the best_path
		if (last_distance > 0 && (distance_tmp+last_distance < distance_best || distance_best == 0)) {
			distance_best = distance_tmp + last_distance;
			cout << "Better than best_path: update this one for best_path with distance=" << distance_best << ".\n";
			for (int i=1; i <= district_size; i++)
				best_path[i] = path[i];
		}
		else
			cout << "ACTION: Worse than best_path: abandon this one.\n";
	}

	// not reach the deepest layer. still call new TSP for next layer
	else {
		if(debug) cout << "Has not reached the deepest.\n";

		// traverse the layer
		for (int i=layer; i <= district_size; i++) {
			// tmp better than best, continue
			if (districts[path[layer-1]][path[i]] > 0 &&
			(distance_tmp+districts[path[layer-1]-1][path[i]] < distance_best || distance_best == 0)) {

				// swap & distance_tmp add x[layer-1] -> x[layer]
				swap(path[layer], path[i]);
				distance_tmp += districts[path[layer-1]][path[layer]];
				if(debug) {
					cout << "\tSwap before call: layer=" << layer << ", i=" << i << ".\n\t";
					insert_print(path, 1, district_size, " -> ");
				}

				// continue call new TSP for next layer
				if(debug) cout << "\tCall TSP(" << layer+1 << ")\n";
				Tsp(layer+1);
				if(debug) cout << "\tReturn TSP(" << layer+1 << ")\n";

				// restore x and distance
				distance_tmp -= districts[path[layer-1]][path[layer]];
				swap(path[layer], path[i]);
				if(debug) {
					cout << "\tSwap after return: layer=" << layer << ", i=" << i << ".\n\t";
					insert_print(path, 1, district_size, " -> ");
				}
			}
			else
				cout << "ACTION: Current distance worse than best_path: pruning this one.\n";
		}
	}
}

void insert_print(int* array, int init_index, int end_index, string insert) {
	for(int i=init_index; i < end_index; i++)
			cout << array[i] << insert;
		cout << array[end_index] << "\n";
}

void swap(int& a, int& b) {
	int temp;
	temp = a;
	a = b;
	b = temp;
}