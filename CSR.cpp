#include <iostream> 
#include <vector> 
#include <fstream>
#include <queue>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <cstdio>
#include <omp.h>

using namespace std;
using namespace std::chrono;

#define INF 10000000
vector<vector<int>> adj;
vector<int> weight;
vector<int> Vertex_Table = { 0 }; // Start from 0
vector<int> Edge_Table;
int dist[10000000];
bool visited[10000000];

struct Edge {
	bool exist_Edge;
	int weight;
};

struct Edge findEdge(int, int); //find where Edge is visited and exist
void addEdge(int, int);

void printVector(vector<int>);//print CSR
void toCSR(int, vector<vector<int>> adj, vector<double>);

//int findMin(int, int[], bool[]);//find minimum distance in dijkstra algorithm
void printSolution(int[], int);
void dijkstra(int, int);
void dijkstra_multithread(int, int);

void Pagerank(int, vector<double>, int);//pagerank
void Pagerank_multithread(int, vector<double>, int);

int main(int argc, char**argv)
{
	auto start = chrono::system_clock::now();
	adj.resize(100000);
	vector<double> rank;
	int weight;
	int V;
	int src;
	int destination;
	FILE *fp;
	fp = fopen(argv[1], "r");
	V = atoi(argv[2]);
	while (!feof(fp)) {
		fscanf(fp, "%d %d", &src, &destination);
		addEdge(src, destination);
	}
	rank.resize(V);
	toCSR(V, adj, rank);
	//dijkstra_multithread(V, 0);
	auto end = chrono::system_clock::now();
	cout << "\ntotal elapsed time : " << chrono::duration_cast<chrono::duration<double>>(end - start).count() << "seconds" << "\n";
}

// Utility Function to print  vectors 
void printVector(vector<int> V)
{
	cout << "[ ";
	for (int i = 0; i < V.size(); i++) cout << V[i] << " ";
	cout << "]\n";
}

// Generate  three vectors
void toCSR(int V, vector<vector<int>> adj, vector<double> rank)
{
	auto CSR_start = chrono::system_clock::now();
	int n = V;
	int i, j;
	int NNZ = 0;
	for (i = 0; i < V; i++) {
		for (j = 0; j < adj[i].size(); j++) {
			//weight.push_back(adj[i][j]);
			Edge_Table.push_back(adj[i][j]);

			// Count Number of Non Zero  
			NNZ++;
		}
		Vertex_Table.push_back(NNZ);
	}
	for (int i = Vertex_Table.size(); i < Edge_Table.size(); i++) Vertex_Table.push_back(NNZ);
	//cout << "weight = ";
	//printVector(weight);
	//cout << "Vertex_Table = ";
	//printVector(Vertex_Table);
	//cout << "Edge_Table = ";
	//printVector(Edge_Table);
	auto CSR_end = chrono::system_clock::now();
	cout << "total elapsed time of convertion to CSR: " << chrono::duration_cast<chrono::duration<double>>(CSR_end - CSR_start).count() << "seconds" << "\n";
	//Pagerank(V, rank, 10);
	Pagerank_multithread(V, rank, 10);
}

int findMin(int V, int dist[], bool visited[]) { //find minimum weight edge and return index
	int min = INF;
	int min_index;
	for (int v = 0; v < V; v++) {
		if (!visited[v] && dist[v] <= min) {
			min = dist[v];
			min_index = v;
		}
	}
	return min_index;
}
struct Edge findEdge(int u, int v) {
	struct Edge e1 = { false, INF };
	int temp_index = 0;
	for (int i = Vertex_Table[u]; i < Vertex_Table[u + 1]; i++) {
		if (Edge_Table[i] == v) {
			e1.exist_Edge = true;
			temp_index = i;
		}
	}
	if (e1.exist_Edge) e1.weight = 1;
	return e1;
}

void addEdge(int u, int v) {
	adj[u].push_back(v);
}

void printSolution(int dist[], int n)
{
	cout << "\nDijkstra algorithm\nVertex   Distance from Source 0\n";
	for (int i = 0; i < n; i++) cout << i << " " << dist[i] << "\n";
}
void dijkstra(int V, int start) {
	auto dijkstra_start = chrono::system_clock::now();
	for (int i = 0; i < V; i++) dist[i] = INF;
	dist[start] = 0;
	for (int i = 0; i < V - 1; i++) {
		int u = findMin(V, dist, visited);
		for (int v = 0; v < V; v++) {
			if (!visited[v] && findEdge(u, v).exist_Edge && dist[u] != INF) {
				if (dist[u] + findEdge(u, v).weight < dist[v]) dist[v] = dist[u] + findEdge(u, v).weight;
			}
		}
		visited[u] = true;
	}
	printSolution(dist, V);
	auto dijkstra_end = chrono::system_clock::now();
	cout << "elapsed time for dijkstra algorithm : " << chrono::duration_cast<chrono::duration<double>>(dijkstra_end - dijkstra_start).count() << "seconds" << "\n";

}
void dijkstra_multithread(int V, int start) {
	auto dijkstra_start = chrono::system_clock::now();
	omp_set_num_threads(4);
	for (int i = 0; i < V; i++) dist[i] = INF;
	dist[start] = 0;
#pragma omp parallel for
	for (int i = 0; i < V - 1; i++) {
		int u = findMin(V, dist, visited);
		for (int v = 0; v < V; v++) {
			if (!visited[v] && findEdge(u, v).exist_Edge && dist[u] != INF) {
				if (dist[u] + findEdge(u, v).weight < dist[v]) dist[v] = dist[u] + findEdge(u, v).weight;
			}
		}
		visited[u] = true;
	}
	//printSolution(dist, V);
	auto dijkstra_end = chrono::system_clock::now();
	cout << "elapsed time for dijkstra algorithm : " << chrono::duration_cast<chrono::duration<double>>(dijkstra_end - dijkstra_start).count() << "seconds" << "\n";
}
void Pagerank(int V, vector<double> rank, int num_iter) {
	auto pagerank_start = chrono::system_clock::now();
	for (int i = 0; i < V; i++) rank[i] = 1.0 / V; //set pagerank value
	double d = 0.85;//damping factor
	for (int k = 0; k < num_iter; k++) {
		double sol = 0;
		vector<double> tmp;
		tmp.resize(V);
		for (int i = 0; i < V; i++) {
			if (Vertex_Table[i + 1] == Vertex_Table[i]) sol += rank[i];
			for (int j = Vertex_Table[i]; j < Vertex_Table[i + 1]; j++) {
				tmp[Edge_Table[j]] += rank[i] / (Vertex_Table[i + 1] - Vertex_Table[i]);
			}
		}
		for (int i = 0; i < V; i++) {
			tmp[i] = (1 - d) / V + d*(tmp[i] + sol / V);
			rank[i] = tmp[i];
		}
	}
	/*cout << "\nPagerank algorithm" << " iteration " << num_iter << "\n";
	for (int i = 0; i < V; i++) {
	cout << i << " : " << rank[i] << "\n";
	}*/
	auto pagerank_end = chrono::system_clock::now();
	cout << "elapsed time for pagerank algorithm : " << chrono::duration_cast<chrono::duration<double>>(pagerank_end - pagerank_start).count() << "seconds" << "\n";
}
void Pagerank_multithread(int V, vector<double> rank, int num_iter) {
	auto pagerank_start = chrono::system_clock::now();
	omp_set_num_threads(4);
	for (int i = 0; i < V; i++) rank[i] = 1.0 / V; //set pagerank value
	double d = 0.85;//damping factor
#pragma omp parallel for
	for (int k = 0; k < num_iter; k++) {
		double sol = 0;
		vector<double> tmp;
		tmp.resize(V);
		for (int i = 0; i < V; i++) {
			if (Vertex_Table[i + 1] == Vertex_Table[i]) sol += rank[i];
			for (int j = Vertex_Table[i]; j < Vertex_Table[i + 1]; j++) {
				tmp[Edge_Table[j]] += rank[i] / (Vertex_Table[i + 1] - Vertex_Table[i]);
			}
		}
		for (int i = 0; i < V; i++) {
			tmp[i] = (1 - d) / V + d*(tmp[i] + sol / V);
			rank[i] = tmp[i];
		}
	}
	/*cout << "\nPagerank algorithm" << " iteration " << num_iter << "\n";
	for (int i = 0; i < V; i++) {
	cout << i << " : " << rank[i] << "\n";
	}*/
	auto pagerank_end = chrono::system_clock::now();
	cout << "elapsed time for pagerank algorithm : " << chrono::duration_cast<chrono::duration<double>>(pagerank_end - pagerank_start).count() << "seconds" << "\n";
}