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

struct Edge {
	bool exist_Edge;
	int weight;
};

void addEdge(int, int);

void Pagerank_multithread(int, vector<double>, int);//pagerank

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
	toCSR(V, adj);
	Pagerank_multithread(V, rank, 10);
	auto end = chrono::system_clock::now();
	cout << "\ntotal elapsed time : " << chrono::duration_cast<chrono::duration<double>>(end - start).count() << "seconds" << "\n";
	return 0;
}

void addEdge(int u, int v) {
	adj[u].push_back(v);
}

void Pagerank_multithread(int V, vector<double> rank, int num_iter) {
	auto pagerank_start = chrono::system_clock::now();
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