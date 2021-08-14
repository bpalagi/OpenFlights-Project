#pragma once
#include <string>

using namespace std;

/**
 * Class that stores the two nodes connected by the edge and its weight (distance).
 */
class SimpleEdge{
    public:
        SimpleEdge(int source, int dest, double weight);
        int getSourceID();
        int getDestID();
        double getDistance();
        bool operator<(SimpleEdge & other);
        bool operator==(SimpleEdge & other);
    private:
        int sourceID;
        int destID;
        double distance;

};
