#include <iostream> 
#include <vector> 
#include <fstream>
#include <queue>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <cstdio>
#include <omp.h>
#include "CSR_convert.h"

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

//int findMin(int, int[], bool[]);//find minimum distance in dijkstra algorithm
void printSolution(int[], int);
void dijkstra(int, int);

int main(int argc, char**argv)
{
	auto start = chrono::system_clock::now();
	vector<double> rank;
	int weight;
	int V;
	int src;
	int destination;
	FILE *fp;
	fp = fopen(argv[1], "r");
	V = atoi(argv[2]);
	adj.resize(V + 1);
	while (!feof(fp)) {
		fscanf(fp, "%d %d", &src, &destination);
		addEdge(src, destination);
	}
	rank.resize(V);
	toCSR(V, adj, rank);
	dijkstra(V, 0);
	auto end = chrono::system_clock::now();
	cout << "\ntotal elapsed time : " << chrono::duration_cast<chrono::duration<double>>(end - start).count() << "seconds" << "\n";
	return 0;
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
	//printSolution(dist, V);
	auto dijkstra_end = chrono::system_clock::now();
	cout << "elapsed time for dijkstra algorithm : " << chrono::duration_cast<chrono::duration<double>>(dijkstra_end - dijkstra_start).count() << "seconds" << "\n";
}
