#pragma once
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "simpleNode.h"
#include "simpleEdge.h"

using namespace std;

class Graph{
    public:
        Graph();
        Graph(string flightData, string airportData);
        
        //map airportID's to AirportNode's
        //      the Node's will know their own edges
        map<int, SimpleNode> nodeMap;
        unordered_map<string, int> idFromIATA;
        double distance(int startID, int destID);
    private:
        
};