#include "simpleNode.h"


SimpleNode::SimpleNode(){}

SimpleNode::SimpleNode(int i, string n, string IA, double lat, double lon)
    : id(i), name(n), IATA(IA), latitude(lat), longitude(lon){}

int SimpleNode::getID(){
    return id;
}

string SimpleNode::getName(){
    return name;
}

string SimpleNode::getIATA(){
    return IATA;
}

double SimpleNode::getLatitude(){
    return latitude;
}

double SimpleNode::getLongitude(){
    return longitude;
}