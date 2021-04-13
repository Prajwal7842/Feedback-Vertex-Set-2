#include <bits/stdc++.h>
#include "FvsPartitionSolver.h"
using namespace std;


map<int, int> originalDegree;


void dfs(map<int, multiset<int>>& g, int u, set<int>& visited) {
    if(visited.count(u)) return ;
    visited.emplace(u);
    for(auto v : g[u]) {
        if(visited.count(v) == 0) {
            dfs(g, v, visited);
        }
    }
}


bool isForest(map<int, multiset<int>>& g) {
    set<int> left;
    for(auto i : g) left.emplace(i.first);
    while((int)(left.size()) > 0) {
        set<int> visited;
        auto u = *left.begin();
        dfs(g, u, visited);

        int nV = visited.size(), nE = 0;
        for(auto v : visited) nE += g[v].size();
        nE /= 2;
        if(nE != (nV + 1)) {
            return 0;
        }
        for(auto v : visited) {
            left.erase(v);
        }
    }
    return 1;
}

bool isReachable(map<int, multiset<int>> g, int u, int v) {
    set<int> visited;
    dfs(g, u, visited);
    return (visited.count(v) == 1);
}


vector<int> getNeighbourV2(map<int, multiset<int>> g, int w, set<int> v2) {
    vector<int> neigh;
    for(int i : g[w]) {
        if(v2.count(i)) {
            neigh.push_back(i);
        }
    }
    return neigh;
}

map<int, multiset<int>> getInducedGraph(map<int, multiset<int>> g, set<int> V) {
    map<int, multiset<int>> newg = g;
    for(int vertex : V) {
        newg.erase(vertex);
    }
    for(auto &u : newg) {
        vector<int> removeVertex;
        for(int v : u.second) {
            if(V.count(v) == 0) {
                removeVertex.push_back(v);
            }
        }
        for(auto v : removeVertex) {
            u.second.erase(v);
        }
    }
    return newg;
}

map<int, multiset<int>> deleteVertex(map<int, multiset<int>> g, int vertex) {
    map<int, multiset<int>> newg = g;
    newg.erase(vertex);
    for(auto &i : newg) {
        i.second.erase(vertex);
    }
    return newg;
} 

set<int> fvsPartitionSolver(map<int, multiset<int>> g, set<int> v1, set<int> v2, int K, bool& found) {
    set<int> solution;
    if(K <= 0 && isForest(g) == 0) {
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
        vector<int> neighV2 = getNeighbourV2(gv1, w, v2);
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

                    set<int> sol = fvsPartitionSolver(newg, newv1, v2, K-1, found);
                    if(found == 1) {
                        sol.emplace(w);
                    }
                    return sol;
                }
            }
        }

        // Now Apply Branching steps on w.
        
        // Case 1 : w is part of solution.
        map<int, multiset<int>> newg = deleteVertex(g, w);
        set<int> newv1 = v1;
        newv1.erase(w);
        set<int> sol = fvsPartitionSolver(newg, newv1, v2, K-1, found);
        if(found == 1) {
            sol.emplace(w);
            return sol;
        }
         
        // Case 2 : w is not part of solution.
        set<int> newv2 = v2;
        v2.emplace(w);
        set<int> sol2 = fvsPartitionSolver(g, newv1, newv2, K, found);
        if(found == 1) {
            return sol2;
        }
        return solution;
    }

    // Pick any vertex w of degree <= 1.
    for(auto w : v1) {
        if((int)(gv1[w].size()) <= 1) {
            if(originalDegree[w] <= 1) {
                map<int, multiset<int>> newg = deleteVertex(g, w);
                set<int> newv1 = v1;
                newv1.erase(w);
                set<int> sol = fvsPartitionSolver(newg, newv1, v2, K, found);
                return sol;
            }
            else {
                vector<int> vertexV1, vertexV2;
                for(int v : gv1[w]) {
                    if(v1.count(v)) {
                        vertexV1.push_back(v);
                    }
                    else {
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
                set<int> sol = fvsPartitionSolver(newg, v1, v2, K, found);
            }
        }
    }

    // For safety.
    return solution;
}
