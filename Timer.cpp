#include <bits/stdc++.h>
#include "Timer.h"

using namespace std::chrono;
using namespace std;



void RRTimeLog :: logMsg() {
  cout<<time_rr1.count()<<","<<vertex_reduced_1<<","<<edge_reduced_1<<",";
  cout<<time_rr3.count()<<","<<vertex_reduced_3<<","<<edge_reduced_3<<",";
  cout<<time_rr4.count()<<","<<vertex_reduced_4<<","<<edge_reduced_4<<",";
}