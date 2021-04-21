#include <bits/stdc++.h>
#include "Graph.h"
#include "Timer.h"
using namespace std;



// void dfs(map<int, multiset<int>>& g, int u, set<int>& visited);

bool isForest(map<int, multiset<int>> g);

// bool isReachable(map<int, multiset<int>> g, int u, int v);

// vector<int> getNeighbourV2(map<int, multiset<int>> g, int w, set<int> v2);

map<int, multiset<int>> getInducedGraph(map<int, multiset<int>> g, set<int> V);

// map<int, multiset<int>> deleteVertex(map<int, multiset<int>> g, int vertex);

set<int> fvsPartitionSolver(map<int, multiset<int>> g, set<int> v1, set<int> v2, int K, bool& found, RRTimeLog& time);

