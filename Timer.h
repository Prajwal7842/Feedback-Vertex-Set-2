#pragma once
#include <bits/stdc++.h>

using namespace std::chrono;
using namespace std;

class RRTimeLog {
  public:
    std::chrono::_V2::system_clock::time_point start_time;

    std::chrono::milliseconds time_rr1 = 0s;
    std::chrono::milliseconds time_rr3 = 0s;
    std::chrono::milliseconds time_rr4 = 0s;
    int vertex_reduced_1 = 0;
    int vertex_reduced_3 = 0;
    int vertex_reduced_4 = 0;

    int edge_reduced_1 = 0;
    int edge_reduced_3 = 0;
    int edge_reduced_4 = 0;
    
    void logMsg();
};
