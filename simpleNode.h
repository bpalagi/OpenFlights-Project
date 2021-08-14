#pragma once
#include <string>
#include <unordered_map>
#include "simpleEdge.h"

using namespace std;


/**
 * Class that stores an airport's ID, name, IATA, and coordinates, as well as a map that maps the destination IDs to its edges.
 */
class SimpleNode{
    public:
        SimpleNode();
        SimpleNode(int i, string n, string IA, double lat, double lon);
        int getID();
        string getName();
        string getIATA();
        double getLatitude();
        double getLongitude();

        unordered_map<int, SimpleEdge> destinations;

    private:
        int id;
        string name;
        string IATA;
        double latitude;
        double longitude;
};
