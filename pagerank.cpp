#include <iostream> 
#include <vector> 
#include <fstream>
#include <queue>
#include <chrono>
#include <stdio.h>
#include <cstdio>
#include <omp.h>
#include <unistd.h>
#include "CSR_convert.h"

using namespace std;
using namespace std::chrono;

#define INF 10000000
extern char* optarg;
vector<vector<int>> adj;
vector<int> weight;
vector<int> Vertex_Table = { 0 }; // Start from 0
vector<int> Edge_Table;
bool do_print=false;
int n_it;

void numiter();
void enable_print();
void addEdge(int, int);

void Pagerank(int, vector<double>, int);//pagerank

int main(int argc, char**argv)
{
	auto start = chrono::system_clock::now();
	vector<double> rank;
	int weight;
	int V;
	int src;
	int destination;
	int option=0;
	FILE *fp;
	fp = fopen(argv[1], "r");
	V = atoi(argv[2]);
	adj.resize(V + 1);
	while (!feof(fp)) {
		fscanf(fp, "%d %d", &src, &destination);
		addEdge(src, destination);
	}
	while((option=getopt(argc, argv, "pn:"))!=EOF){
		switch(option)
		{
			case 'p':enable_print();break;
			case 'n':numiter();break;
		}
	}
	rank.resize(V);
	toCSR(V, adj);
	Pagerank(V, rank, n_it);
	auto end = chrono::system_clock::now();
	cout << "\ntotal elapsed time : " << chrono::duration_cast<chrono::duration<double>>(end - start).count() << "seconds" << "\n";
	return 0;
}
void numiter(){
	n_it=atoi(optarg);
}
void enable_print(){
	do_print=true;
}
void addEdge(int u, int v) {
	adj[u].push_back(v);
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
	if(do_print){
		cout << "\nPagerank algorithm" << " iteration " << num_iter << "\n";
		for (int i = 0; i < V; i++) {
			cout << i << " : " << rank[i] << "\n";
		}
	}
	auto pagerank_end = chrono::system_clock::now();
	cout << "elapsed time for pagerank algorithm : " << chrono::duration_cast<chrono::duration<double>>(pagerank_end - pagerank_start).count() << "seconds" << "\n";
}
