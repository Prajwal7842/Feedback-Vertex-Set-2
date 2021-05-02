#include <bits/stdc++.h>
#include "Graph.h"
using namespace std;

void Graph :: addEdge(string u, string v) {
	// Function to add an edge in graph. 
	edgeList.push_back({u, v});
}

void Graph :: printGraph() {
	// Function to print the graph in adjacency list format.
	for(auto i : adjList) { 
		cout << i.first << " -> ";
		for(auto j : i.second) {
			cout << j << " ";
		}
		cout << endl;
	}
}