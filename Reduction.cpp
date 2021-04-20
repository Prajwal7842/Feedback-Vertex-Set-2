#include <bits/stdc++.h>
#include "Graph.h"
#include "Reduction.h"
#include "Timer.h"
using namespace std;


void delete_vertex(map<int, multiset<int>>& g, int u) {
	g.erase(u);
	for(auto &i: g){
		i.second.erase(u);
	}
}

// If there exists a vertex u of degree at most one, delete u.
bool rule1(map<int, multiset<int>>& g) {
	// If there exists a vertex u of degree at most one, delete u.
	vector<int> removeVertex;
	for(auto i : g) {
		if((int)(i.second.size()) == 0) {
			removeVertex.push_back(i.first);
		}
		if((int)(i.second.size()) == 1) {
			removeVertex.push_back(i.first);
		}
	}
	if((int)(removeVertex.size()) == 0) return 0;
	for(int i : removeVertex) {
		delete_vertex(g, i);
	}
	return 1;
}

// If there exists a vertex u of degree two, delete u and add an edge connecting its two endpoints.
bool rule3(map<int, multiset<int>>& g) {
	// If there exists a vertex u of degree two, delete u and add an edge connecting its two endpoints.
	map<int, pair<int, int>> merge;
	for(auto i : g) {
		if((int)(i.second.size()) == 2) {
			set<int> st(i.second.begin(), i.second.end());
			if((int)(st.size()) == 2) { // Check if neighbours of degree 2 vertex are different.
				pair<int, int> neighbours = {-1, -1};
				auto v = st.begin();
				neighbours.first = *v;
				v ++;
				neighbours.second = *v;
				merge[i.first] = neighbours;
				break;
			}
		}
	}
	if(merge.size() == 0) return 0;
	// for(auto i : merge) {
	// 	cout << i.first << " -> " << i.second.first << " " << i.second.second << endl;
	// }
	auto v = *merge.begin();
	g.erase(v.first);
	g[v.second.first].emplace(v.second.second);
	g[v.second.second].emplace(v.second.first);
	g[v.second.first].erase(v.first);
	g[v.second.second].erase(v.first);
 	return 1;
}


// If there exists an edge e of multiplicity more than two, reduce its multiplicity to two.
bool rule4(map<int, multiset<int>>& g) {
	map<int, pair<int, int>> edgeDelete;
	for(auto i: g){
		set<int> st(i.second.begin(), i.second.end());
		for(auto j: st) {
			int count = i.second.count(j);
			if(count > 2) {
				pair<int, int> edgeCount = {-1, -1};
				edgeCount.first = j;
				edgeCount.second = count;
				edgeDelete[i.first] = edgeCount;
			}
		}
	}
	if(edgeDelete.size() == 0) return 0;
	for(auto i: edgeDelete) {
		// i.second.second is the count of the number of edges, so -2, means at max two will remain.
		for(int j=0; j<i.second.second-2; j++){
			auto itr = g[i.first].find(i.second.first);
			if(itr!=g[i.first].end()){
					g[i.first].erase(itr);
			}
		}
	}
	// Since this is the structure of the graph is not changed.
	return 0;
}

int countEdges(map<int, multiset<int>> g) {
	int count = 0;
	for(auto i: g) {
		count += i.second.size();
	}
	return count;
}

void reduce(Graph& graph, RRTimeLog &time) {
	bool changes_to_graph = true;
	while(changes_to_graph){
    auto now = high_resolution_clock::now();
    auto total_duration = duration_cast<minutes>(now - time.start_time);
    if(total_duration.count() >= 30) {
      cout<<"TIMEOUT\n";
      exit(0);
    }
    changes_to_graph = false;
    bool running;
    std::chrono::_V2::system_clock::time_point start, end;
    int initialVertex, finalVertex, initialEdges, finalEdges;


    running = true;
    start = high_resolution_clock::now();
    initialVertex = graph.adjList.size();
    initialEdges = countEdges(graph.adjList);
    while(running) {
      running = rule1(graph.adjList);
      changes_to_graph = changes_to_graph || running;
    }
    finalVertex = graph.adjList.size();
    finalEdges = countEdges(graph.adjList);
    end = high_resolution_clock::now();
    time.time_rr1 += duration_cast<milliseconds>(end - start);
    time.vertex_reduced_1 += initialVertex - finalVertex;
    time.edge_reduced_1 += initialEdges - finalEdges;

    running = true;
    start = high_resolution_clock::now();
    initialVertex = graph.adjList.size();
    initialEdges = countEdges(graph.adjList);
    while(running) {
      running = rule3(graph.adjList);
      changes_to_graph = changes_to_graph || running;
    }
    finalVertex = graph.adjList.size();
    finalEdges = countEdges(graph.adjList);
    end = high_resolution_clock::now();
    time.time_rr3 += duration_cast<milliseconds>(end - start);
    time.vertex_reduced_3 += initialVertex - finalVertex;
    time.edge_reduced_3 += initialEdges - finalEdges;

    running = true;
    start = high_resolution_clock::now();
    initialVertex = graph.adjList.size();
    initialEdges = countEdges(graph.adjList);
    while(running) {
      running = rule4(graph.adjList);
      changes_to_graph = changes_to_graph || running;
    }
    finalVertex = graph.adjList.size();
    finalEdges = countEdges(graph.adjList);
    end = high_resolution_clock::now();
    time.time_rr4 += duration_cast<milliseconds>(end - start);
    time.vertex_reduced_4 += initialVertex - finalVertex;
    time.edge_reduced_4 += initialEdges - finalEdges;
	}
}
