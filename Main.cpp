#include <bits/stdc++.h>
#include "input.h"
#include "Reduction.h"
#include "Graph.h"
#include "checker.h"
#include "FVS.h"
using namespace std;



int32_t main(int32_t argc, char*argv[]) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);


	if(argc != 4) {
		cout<<"Usage : "<<argv[0]<<"<InputFileName> "<<"<outputFileName> "<<"<value K>"<<endl;
		return 0;
	}
	freopen(argv[2], "a", stdout);

	Graph graph;
	graph.K = atoi(argv[3]);;
	readInput(graph, argv[1]);

	auto start = high_resolution_clock::now();
	RRTimeLog time1;
	time1.start_time = start;
	cout<<argv[1]<<",";
	reduce(graph, time1);
	if(solve(graph, time1) == 0) {
		cout<<"false"<<",";
	} else {
		auto end = high_resolution_clock::now();
		if(check(graph.adjList, graph.solution)) {
			auto duration = duration_cast<milliseconds>(end - start);
			cout<<duration.count()<<",";
			time1.logMsg();
		}
	}
	cout<<endl;
	return 0;
}