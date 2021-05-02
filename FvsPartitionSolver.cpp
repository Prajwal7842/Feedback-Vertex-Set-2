#include <bits/stdc++.h>
#include "FvsPartitionSolver.h"
#include "Timer.h"
using namespace std;


void dfs(map<int, multiset<int>>& g, int u, set<int>& visited) {
    /* Helper function to find connected compoenents in the graph. */
    if(visited.count(u)) return ;
    visited.emplace(u);
    for(auto v : g[u]) {
        if(visited.count(v) == 0) {
            dfs(g, v, visited);
        }
    }
}

bool isForest(map<int, multiset<int>> g) {
    /* Function to check whether the input graph is a forest or not */
    set<int> left;
    for(auto i : g) left.emplace(i.first);
    while((int)(left.size()) > 0) {
        set<int> visited;
        auto u = *left.begin();
        dfs(g, u, visited);

        int nV = visited.size(), nE = 0;
        for(auto v : visited) nE += g[v].size();
        nE /= 2;
        if(nE != (nV - 1)) {
            return 0;
        }
        for(auto v : visited) {
            left.erase(v);
        }
    }
    return 1;
}

bool isReachable(map<int, multiset<int>> g, int u, int v) {
    // Function to determine whether a vertex v is reachable from u or not. 
    if(u==v)
        return true;
    set<int> visited;
    dfs(g, u, visited);
    return (visited.count(v) == 1);
}


vector<int> getNeighbourV2(map<int, multiset<int>> g, int w, set<int> v2) {
    // Returns neighbours of all vertices  in set v2 from graph g.
    vector<int> neigh;
    for(int i : g[w]) {
        if(v2.count(i)) {
            neigh.push_back(i);
        }
    }
    return neigh;
}


void del_vertex(map<int, multiset<int>>& g, int u) {
    /* Function to delete a vertex from graph inplace and all edges assosciated with it. */
	g.erase(u);
	for(auto &i: g){
		i.second.erase(u);
	}
}

map<int, multiset<int>> getInducedGraph(map<int, multiset<int>> g, set<int> V) {
    // Returns induced subgraph on g from vertex set V.
    map<int, multiset<int>> newg = g;
    vector<int> removeVertex;
    for(auto v: g) {
        if(V.count(v.first) == 0){
            removeVertex.push_back(v.first);
        }
    }
    for(auto i: removeVertex) {
        del_vertex(newg, i);
    }
    return newg;
}

map<int, multiset<int>> deleteVertex(map<int, multiset<int>> g, int vertex) {
    // Function to delete a vertex from graph and all edges assosciated with  it and return a new graph.
    map<int, multiset<int>> newg = g;
    newg.erase(vertex);
    for(auto &i : newg) {
        i.second.erase(vertex);
    }
    return newg;
}

void printGraph1(map<int, multiset<int>> adjList) {
    // Utility function to print a graph. 
    for(auto i : adjList) { 
        printf("%d->", i.first);
        for(auto j : i.second) {
            printf("%d ", j);
        }
        printf("\n");
    }
}

void printGraphEdges1(map<int, multiset<int>> adjList) {
    // Utility function to print edges of the graph.
    for(auto i : adjList) { 
        for(auto j : i.second) {
            printf("%d %d\n", i.first, j);
        }
    }
    printf("\n\n");
}

set<int> fvsPartitionSolver(map<int, multiset<int>> g, set<int> v1, set<int> v2, int K, bool& found, RRTimeLog& time) {
    // Main branching solution to either find a solution or return NO.

    auto now = high_resolution_clock::now();
    auto total_duration = duration_cast<minutes>(now - time.start_time);
    if(total_duration.count() >= 30) {
        cout<<"TIMEOUT\n";
        exit(0);
    }
    set<int> solution;
    // Base Cases
    if(K < 0 || (K == 0 && isForest(g) == 0)) {
        found = 0;
        return solution;
    }
    if(K >= 0 && isForest(g) == 1) {
        found = 1;
        return solution;
    }
    
    map<int, multiset<int>> gv1 = getInducedGraph(g, v1);
    map<int, multiset<int>> gv2 = getInducedGraph(g, v2);
    for(int w : v1) {
        vector<int> neighV2 = getNeighbourV2(g, w, v2);
        int l = neighV2.size();
        if(l <= 1) {
            continue;
        }
        for(int i = 0; i < l - 1; i ++) {
            for(int j = i + 1; j < l; j ++) {
                if(isReachable(gv2, neighV2[i], neighV2[j])) {
                    // We know for sure that to remove the cycle from w -> a -> b -> w, we have to remove w.
                    map<int, multiset<int>> newg = deleteVertex(g, w);
                    set<int> newv1 = v1;
                    newv1.erase(w);

                    set<int> sol = fvsPartitionSolver(newg, newv1, v2, K-1, found, time);
                    if(found == 1) {
                        sol.emplace(w);
                    }
                    return sol;
                }
            }
        }

        // Now Apply Branching steps on w.
        
        // Case 1 : w is part of solution.
        map<int, multiset<int>> newg1 = deleteVertex(g, w);
        set<int> newv1 = v1;
        newv1.erase(w);
        set<int> sol1 = fvsPartitionSolver(newg1, newv1, v2, K-1, found, time);
        if(found == 1) {
            sol1.emplace(w);
            return sol1;
        }
         
        // Case 2 : w is not part of solution.
        set<int> newv2 = v2;
        newv2.emplace(w);
        set<int> sol2 = fvsPartitionSolver(g, newv1, newv2, K, found, time);
        if(found == 1) {
            return sol2;
        }
        return solution;
    }

    // Pick any vertex w of degree <= 1.
    for(auto w : v1) {
        if((int)(gv1[w].size()) <= 1) {
            if((int)(g[w].size()) <= 1) {
                map<int, multiset<int>> newg = deleteVertex(g, w);
                set<int> newv1 = v1;
                newv1.erase(w);
                set<int> sol = fvsPartitionSolver(newg, newv1, v2, K, found, time);
                return sol;
            } else {
                // w is a degree two vertex, with one vertex in v1 and another in v2.
                vector<int> vertexV1, vertexV2;
                for(int v : g[w]) {
                    if(v1.count(v)) {
                        vertexV1.push_back(v);
                    } else {
                        vertexV2.push_back(v);
                    }
                }
                map<int, multiset<int>> newg = deleteVertex(g, w);
                set<int> newv1 = v1;
                newv1.erase(w);
                for(auto u : vertexV1) {
                    for(auto v : vertexV2) {
                        newg[u].emplace(v);
                        newg[v].emplace(u);
                    }
                }
                set<int> sol = fvsPartitionSolver(newg, newv1, v2, K, found, time);
                return sol;
            }
        }
    }

    // For safety.
    return solution;
}
