#include <iostream> 
#include <vector> 
#include <chrono>

using namespace std;

extern vector<vector<int>> adj;
extern vector<int> weight;
extern vector<int> Vertex_Table; // Start from 0
extern vector<int> Edge_Table;

void toCSR(int V, vector<vector<int>> adj)
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
	auto CSR_end = chrono::system_clock::now();
	cout << "total elapsed time of convertion to CSR: " << chrono::duration_cast<chrono::duration<double>>(CSR_end - CSR_start).count() << "seconds" << "\n";
}