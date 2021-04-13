#include <bits/stdc++.h>
#include "Graph.h"
using namespace std;

void Graph :: addEdge(string u, string v) {
	edgeList.push_back({u, v});
}

void Graph :: printGraph() {
	for(auto i : adjList) { 
		cout << i.first << " -> ";
		for(auto j : i.second) {
			cout << j << " ";
		}
		cout << endl;
	}
}