#include "bits/stdc++.h"
#include "FVS.h"

uint32_t next(uint32_t v) {
    uint32_t t = v | (v - 1);
    // printf("v:%d, shift %d\n", v, __builtin_ctz(v) + 1);
    return (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(v) + 1));  
}

std::vector<int> filter(const std::vector<int> v, uint32_t mask) {
    std::vector<int> res;
    while (mask) {
        res.push_back(v[__builtin_ctz(mask)]);
        mask &= mask - 1;
    }   
    return res;
}

std::set<std::vector<int>> get_subsets(const std::vector<int> arr, int k) {   
    std::set<std::vector<int>> s;
    uint32_t max = (1 << arr.size());
    for (uint32_t v = (1 << k) - 1; v < max; v = next(v)) {
        // printf("k%d, v:%d\n", k, v);
        s.insert(filter(arr, v));
    }
    return s;
}

set<int> setDifference(set<int> a, set<int> b) {
    set<int> c = a;
    for(auto i : b) c.erase(i);
    return c;
}

void printset(set<int> s){
	for(auto i: s){
		printf("%d ", i);
	}
	printf("\n");
}

void printvector(vector<int> s){
	for(auto i: s){
		printf("%d ", i);
	}
	printf("\n");
}

void printGraph(map<int, multiset<int>> adjList) {
    for(auto i : adjList) { 
        printf("%d->", i.first);
        for(auto j : i.second) {
            printf("%d ", j);
        }
        printf("\n");
    }
}

void printGraphEdges(map<int, multiset<int>> adjList) {
    for(auto i : adjList) { 
        for(auto j : i.second) {
            printf("%d %d\n", i.first, j);
        }
    }
    printf("\n\n");
}

void solve(Graph& graph) {
	graph.printGraph();
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
    set<int> solution;
    for(int i=0; i < K; i++) {
        V.emplace(vertexSet[i]);
        solution.emplace(vertexSet[i]);
    }
    V.emplace(vertexSet[K]);
    // Iterative Step :
    bool found = 0;
    for(int i = K+1; i < l; i ++) {
        found = 0;
        V.emplace(vertexSet[i]);
        solution.emplace(vertexSet[i]);
        // printf("---------------------------------------\ni: %d\n", i);
        // printset(solution);
        // Compression step
        // printf("----------------\n");
        for(int j = 1; j <= K; j ++) {
            // printf("----------------\nj: %d\n", j);
            vector<int> sub(solution.begin(), solution.end());
            set<vector<int>> subsets = get_subsets(sub, j);
            // For each of the disjoint problem
            for(auto vec : subsets) {
                // printf("----------\nj: %d\n", j);
                // printf("Guess sol: ");
                // printvector(vec);
                set<int> F = solution;
                set<int> F2(vec.begin(), vec.end());
                // Vertices in the disjoint graph.
                set<int> disjoint_vertices = setDifference(V, F2);
                set<int> v1 = setDifference(V, F);
                set<int> v2 = setDifference(F, F2);
                map<int, multiset<int>> newg = getInducedGraph(g, disjoint_vertices);
                // printGraph(newg);
                // printGraphEdges(newg);
                set<int> disj_sol = fvsPartitionSolver(newg, v1, v2, K-j, found);
                if(found == 1) {
                    solution = disj_sol;
                    for(auto v: vec) solution.emplace(v);
                    printf("Sol: ");
                    printset(solution);
                    set<int> temp = setDifference(V, solution);
                    if(isForest(getInducedGraph(g, temp))==0){
                        printf("---Error--\n");
                        return;
                    }
                    break;
                }
            }
            if(found == 1) break;
        }
        if(found == 0) break;
    }
    // cout<<graph.solution.size()<<"\n";
    if(found == 0) {
        printf("----No Solution-----\n");
    } else {
        printf("----Solution-----\n");
        printset(solution);
        graph.solution = solution;
    }
    // Print solution
}