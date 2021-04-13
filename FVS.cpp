#include "bits/stdc++.h"
#include "FVS.h"

uint32_t next(uint32_t v) {
    uint32_t t = v | (v - 1);
    return (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(v) + 1));  
}

std::vector<int> filter(const std::vector<int>& v, int mask) {
    std::vector<int> res;
    while (mask) {
        res.push_back(v[__builtin_ctz(mask)]);
        mask &= mask - 1;
    }   
    return res;
}

std::set<std::vector<int>> get_subsets(const std::vector<int>& arr, int k) {   
    std::set<std::vector<int>> s;
    uint32_t max = (1 << arr.size());
    for (uint32_t v = (1 << k) - 1; v < max; v = next(v)) {
        s.insert(filter(arr, v));
    }
    return s;
}

set<int> setDifference(set<int> a, set<int> b) {
    set<int> c = a;
    for(auto i : b) c.erase(i);
    return c;
}

void solve(Graph& graph) {
    map<int, multiset<int>> g;
    int K = graph.K;

    for(auto i : graph.adjList) {
        for(auto j : i.second) {
            g[i.first].emplace(j);
        }
    }
    vector<int> vertexSet;
    for(auto i : g) vertexSet.push_back(i.first);
    int l = vertexSet.size();
    set<int> V;
    // Iterative Step :
    set<int> solution; 
    for(int i = 0; i < l; i ++) {
        if((int)(solution.size()) < K + 1) {
            solution.emplace(vertexSet[i]);
        }
        if(i < K + 2) {
            V.emplace(vertexSet[i]);
        }
        else {
            map<int, multiset<int>> newg = getInducedGraph(g, V);
            for(int j = 0; j <= K; j ++) {
                bool found = 0;
                vector<int> sub(solution.begin(), solution.end());
                set<vector<int>> subsets = get_subsets(sub, j);
                for(auto vec : subsets) {
                    set<int> F = solution;
                    set<int> F2(vec.begin(), vec.end());
                    set<int> v1 = setDifference(V, F);
                    set<int> v2 = setDifference(F, F2);
                    set<int> sol = fvsPartitionSolver(g, v1, v2, K-j, found);
                    if(found == 1) {
                        solution = sol;
                        break;
                    }
                }
                if(found == 1) break;
            }
        }
    }
    
    // Print solution
}

int main() {}