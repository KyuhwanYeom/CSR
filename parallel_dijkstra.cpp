#include <iostream> 
#include <vector> 
#include <fstream>
#include <queue>
#include <chrono>
#include <thread>
#include <omp.h>
#include <unistd.h>
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
bool do_print=false;

struct Edge {
	bool exist_Edge;
	int weight;
};
void enable_print();
struct Edge findEdge(int, int); //find where Edge is visited and exist
void addEdge(int, int);

void printVector(vector<int>);//print CSR

void printSolution(int[], int);
void dijkstra_multithread(int, int);

int main(int argc, char**argv)
{
	auto start = chrono::system_clock::now();
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
	if(getopt(argc, argv, "p")=='p') enable_print();
	toCSR(V, adj);
	dijkstra_multithread(V, 0);
	auto end = chrono::system_clock::now();
	cout << "\ntotal elapsed time : " << chrono::duration_cast<chrono::duration<double>>(end - start).count() << "seconds" << "\n";
	return 0;
}

void enable_print(){
	do_print=true;
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
void dijkstra_multithread(int V, int start) {
	auto dijkstra_start = chrono::system_clock::now();
	int cost;
	priority_queue<pair<int, int>> pq;
	pq.push({ 0,start });

	for (int i = 0; i < V; i++) dist[i] = INF;
	dist[start] = 0;
	while (!pq.empty()) {
		int d = -pq.top().first;
		int cur = pq.top().second;
		pq.pop();
		if (dist[cur] < d) continue;
		for (int i = 0; i < Vertex_Table[cur + 1] - Vertex_Table[cur]; i++) {
			if (findEdge(cur, Edge_Table[Vertex_Table[cur]+i]).exist_Edge) cost = d + 1;
			else cost = INF;
			if (cost < dist[Edge_Table[Vertex_Table[cur] + i]]) {
				dist[Edge_Table[Vertex_Table[cur] + i]] = cost;
				pq.push(make_pair(-cost, Edge_Table[Vertex_Table[cur] + i]));
			}
		}
	}
	if(do_print) printSolution(dist, V);
	auto dijkstra_end = chrono::system_clock::now();
	cout << "elapsed time for dijkstra algorithm : " << chrono::duration_cast<chrono::duration<double>>(dijkstra_end - dijkstra_start).count() << "seconds" << "\n";
}
