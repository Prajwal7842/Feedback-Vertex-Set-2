#pragma once
#include <bits/stdc++.h>
using namespace std;

class Graph {
public:
	map<int, multiset<int>> adjList;
	int K;
	vector<pair<string, string>> edgeList;
	map<string, int> strToInt;
	map<int, string> intToStr;
	set<int> undeletableVertices;
	set<int> solution;

	void addEdge(string u, string v);

	void printGraph();
	
};