#include "simpleEdge.h"

SimpleEdge::SimpleEdge(int source, int dest, double weight)
    : sourceID(source), destID(dest), distance(weight) {};


int SimpleEdge::getSourceID(){
    return sourceID;
}

int SimpleEdge::getDestID(){
    return destID;
}

double SimpleEdge::getDistance(){
    return distance;
}

bool SimpleEdge::operator<(SimpleEdge & other){
    return distance < other.distance;
}

bool SimpleEdge::operator==(SimpleEdge & other){
    if (sourceID != other.sourceID || destID != other.destID)
        return false;
    return true;
}