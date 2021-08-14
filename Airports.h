#pragma once

#include <vector>
#include <string>
#include <tuple>
#include <queue>
#include "Graph.h"
#include <algorithm>

using namespace std;

class Airports {
    public:
        Airports(string flightData, string airportData, string startCode, string destCode);
        bool pathExists();

        vector<string> bfs();
        tuple<vector<string>,double> dijkstras();
        tuple<vector<string>,double> astar();

        int getStartID(){return startID;};
        int getDestID(){return destID;};

        double hcost(int curr_id, int dest_id);
        int number_of_steps;
    private:
        int numAirports;
        int startID;
        int destID;
        Graph myGraph;
};
