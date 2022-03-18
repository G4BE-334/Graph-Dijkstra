#include <iostream>
#include <cstring>

using namespace std;

const int V = 15;

// LaPaz and SantaCruz alltogether to work as a string
string cities[V] = {"Mohave", "Coconino", "Navajo", "Apache", "Greenlee", "Cochise", "SantaCruz", "Pima", "Pinal", "Graham", "Gila", "Yavapai", "LaPaz", "Yuma", "Maricopa"};


int adjMatrix[V][V] = {0};

bool visited[V] = {false};

void display(int aM[V][V]) {
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			cout << adjMatrix[i][j] << "\t";
		}
		cout << endl;
	}
}

// Print the neighbors of a city
void getNeighbors(string city) {
	for (int i = 0; i < V; i ++) {
		if (cities[i] == city) {
			for (int j = 0; j < V; j ++) {
				if (adjMatrix[i][j] != 0) {
					cout << city << " has " << cities[j] << " as neighbor" << endl;
				}
			}
		}
	}
}

// Get the index of the neighbor city with the closest distance
int getMinNeighbor(int city) {
	int min = 1000;
	int neig = 1000;
	for (int i = 0; i < V; i++) {
		if (adjMatrix[city][i] != 0 && adjMatrix[city][i] < min && !visited[i]) {
			min = adjMatrix[city][i];
			neig = i;
		}
	}
	return neig;
}

// Get the shortest distance from a city to any other
int getMinDistance(int city) {
	int min = 1000;
	int neig = 1000;
	for (int i = 0; i < V; i++) {
		if (adjMatrix[city][i] != 0 && adjMatrix[city][i] < min && !visited[i]) {
			min = adjMatrix[city][i];
			neig = i;
		}
	}
	return min;
}

// Function to detect typos
// It was used in the beggining to make sure the distance between the cities were correct
void detectTypo(int aM[V][V]) {
	bool typo = false;
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (aM[i][j] != aM[j][i]) {
				cout << "Error detected at " << i << " " << j << endl;
				typo = true;
			}
		}
	}
	if (!typo) {
		cout << "No typos detected for this graph! Good job on hardcoding all these values without making a mistake :)" << endl;
	} 
}

// Get any path from one city to another
int getPath(int aM[V][V], string from, string to) {
	int start, end, temp;
	bool check = false;

	int distance = 0;
	for (int i = 0; i < V; i++) {
		if (cities[i] == from) {
			start = i;
			if (check){break;}
			check = true;
		}
		else if (cities[i] == to) {
			end = i;
			temp = end;
			if (check){break;}
			check = true;
		}
		visited[i] = false;
	}
	if (aM[start][end] != 0) {
		distance = aM[start][end];
		return distance;
	}
	// Increase temp to check the next vertex 
	temp++;
	while (aM[start][end] == 0) {
		// if temp is at the end go to the beggining
		if (temp == V) { temp = 0;}
		if (aM[start][temp] != 0 && !visited[temp]) {
			cout << "From " << cities[start] << " to " << cities[temp] << " is " << aM[start][temp] << " units." << endl;
			visited[start] = true;
			distance = distance + aM[start][temp];
			start = temp;
		}
		temp++; 
	}
	cout << "From " << cities[start] << " to " << cities[end] << " is " << aM[start][end] << " units." << endl;
	distance = distance + aM[start][end];
	return distance;
}

// Dijkstra Algorithm 
int shortestDistance(int aM[V][V], string from, string to) {
	int start, end, temp;
	int sptSet[V], temp2[V] = {1000};
	bool check = false;

	int distance, count = 0;
	for (int i = 0; i < V; i++) {
		if (cities[i] == from) {
			start = i;
			if (check){break;}
			check = true;
		}
		else if (cities[i] == to) {
			end = i;
			temp = end;
			if (check){break;}
			check = true;
		}
		visited[i] = false;
	}
	sptSet[count] = start;
	count++;
	visited[start] = true;

	if (aM[start][end] != 0) {
		distance = aM[start][end];
		return distance;
	}
	temp = start;
	temp2[start] = 0;
	while (temp2[end] == 0) {
		if (count == 1) {
			temp = getMinNeighbor(temp);
			temp2[temp] = getMinDistance(start);
			sptSet[count] = temp;
			count++;
			visited[temp] = true;
		}
		else {
		    int min = 1000;
            for (int i = 0; i < V; i++) {
                if (sptSet[i] >= 0 && sptSet[i] < V) {
                    int city = sptSet[i];
                    int maybeMin = getMinDistance(city) + temp2[city];
                    if (maybeMin < min) {
                        min = maybeMin;
                        temp = getMinNeighbor(sptSet[i]);
                    }
                }
            }
            sptSet[count] = temp;
            temp2[temp] = min;
            visited[temp] = true;
            count++;
		}
	}
	distance = temp2[end];
	return distance;
}

int main() {
	adjMatrix[0][1] = 14;
	adjMatrix[0][11] = 14;
	adjMatrix[0][12] = 9;

	adjMatrix[1][0] = 14;
	adjMatrix[1][11] = 9;
	adjMatrix[1][2] = 9;
	adjMatrix[1][10] = 17;

	adjMatrix[2][1] = 9;
	adjMatrix[2][3] = 5;
	adjMatrix[2][9] = 20;
	adjMatrix[2][10] = 13;

	adjMatrix[3][2] = 5;
	adjMatrix[3][4] = 17;
	adjMatrix[3][9] = 19;
	
	adjMatrix[4][3] = 17;
	adjMatrix[4][9] = 4;
	adjMatrix[4][5] = 16;
	
	adjMatrix[5][4] = 16;
	adjMatrix[5][9] = 12;
	adjMatrix[5][6] = 8;
	adjMatrix[5][7] = 9;

	adjMatrix[6][5] = 8;
	adjMatrix[6][7] = 6;


	adjMatrix[7][5] = 9;
	adjMatrix[7][6] = 6;
	adjMatrix[7][9] = 12;
	adjMatrix[7][8] = 7;
	adjMatrix[7][13] = 23;
	adjMatrix[7][14] = 10;

	adjMatrix[8][7] = 7;
	adjMatrix[8][9] = 13;
	adjMatrix[8][10] = 5;
	adjMatrix[8][14] = 6;

	adjMatrix[9][3] = 19;
	adjMatrix[9][4] = 4;
	adjMatrix[9][5] = 12;
	adjMatrix[9][7] = 12;
	adjMatrix[9][8] = 13;
	adjMatrix[9][10] = 7;
	adjMatrix[9][2] = 20;

	adjMatrix[10][1] = 17;
	adjMatrix[10][2] = 13;
	adjMatrix[10][9] = 7;
	adjMatrix[10][8] = 5;
	adjMatrix[10][14] = 8;
	adjMatrix[10][11] = 18;

	adjMatrix[11][1] = 9;
	adjMatrix[11][10] = 18;
	adjMatrix[11][14] = 9;
	adjMatrix[11][12] = 15;
	adjMatrix[11][0] = 14;

	adjMatrix[12][11] = 15;
	adjMatrix[12][14] = 15;
	adjMatrix[12][13] = 11;
	adjMatrix[12][0] = 9;
	
	adjMatrix[13][7] = 23;
	adjMatrix[13][14] = 18;
	adjMatrix[13][12] = 11;
	
	adjMatrix[14][10] = 8;
	adjMatrix[14][7] = 10;
	adjMatrix[14][8] = 6;
	adjMatrix[14][13] = 18;
	adjMatrix[14][12] = 15;
	adjMatrix[14][11] = 9;

	display(adjMatrix);
	cout << "\nCities in order, equivalent distances displayed above:" << endl;
	for (int i = 0; i < V; i++) {
		cout << cities[i] << endl;
	}

	int algo;

	while (algo != 0) {
		cout << "\nWhat are you looking for (0 to stop)?" << endl;
		cout << "(1)\tSee a random path between 2 cities " << endl;
		cout << "(2)\tGet the shortest distance between 2 cities - Dijkstra Algorithm " << endl;
		cin >> algo;

		if (algo == 1) {
			string from, to;
			cout << "Please enter the city you want to leave from: " << endl;
			cin >> from;
			cout << "Please enter the city you want to go to: " << endl;
			cin >> to;
			
			int CN = getPath(adjMatrix, from, to);
			cout << "The total distance from " << from << " to " << to << " in this path is " << CN << " units." << endl;
		}
		else if (algo == 2) {
			string fromSD, toSD;
	
			cout << "Please enter the city you want to leave from: " << endl;
			cin >> fromSD;
			cout << "Please enter the city you want to go to: " << endl;
			cin >> toSD;
			cout << "The shortest distance from " << fromSD << " to " << toSD << " is " << shortestDistance(adjMatrix, fromSD, toSD) << " units" << endl;
		}
		else if (algo == 0){break;}
		else{cout << "Please select an eligible option" << endl;} 
	}

	cout << "Thank you for using the program :)\n Goodbye";
	
	
	




} 