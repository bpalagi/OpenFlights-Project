#include "Graph.h"
#include <math.h>

using namespace std;

Graph::Graph(){};

Graph::Graph(string flightData, string airportData){
    
    // inserting airport nodes

    ifstream file;
    string line;
    file.open(airportData);

    while (getline(file,line)) {
        //split up line by commas
    
        stringstream stream(line); 
        
        string substr;
        getline(stream, substr, ',');
        int id = stoi(substr, nullptr);
        getline(stream, substr, ',');
        string name = substr;
        getline(stream, substr, ',');
        getline(stream, substr, ',');
        getline(stream, substr, ',');
        string IATA = substr.substr(1,3);
        getline(stream, substr, ',');
        getline(stream, substr, ',');
        double latitude = stod(substr, nullptr);
        getline(stream, substr, ',');
        double longitude = stod(substr, nullptr);

        SimpleNode node(id, name, IATA, latitude, longitude);
        nodeMap.insert(pair<int,SimpleNode>(node.getID(),node));
        idFromIATA.insert(pair<string,int>(IATA,id));

    }

    file.close();

    // insert flight path edges

    file.open(flightData);

    while (getline(file,line)) {
        //split up line by commas
        stringstream stream(line); 

        string substr;
        getline(stream, substr, ',');
        getline(stream, substr, ',');
        getline(stream, substr, ',');
        getline(stream, substr, ',');

        if (!isdigit(substr.at(0))) continue;

        int sourceID = stoi(substr, nullptr);
        getline(stream, substr, ',');
        getline(stream, substr, ',');

        if (!isdigit(substr.at(0))) continue;

        int destID = stoi(substr, nullptr);


        int dist = distance(sourceID,destID);
        SimpleEdge node(sourceID, destID, dist);

        if (nodeMap[sourceID].destinations.find(destID) == nodeMap[sourceID].destinations.end()){
            nodeMap[sourceID].destinations.insert(pair<int, SimpleEdge>(destID, node));
        }
    }

    file.close();
}

double Graph::distance(int sourceID, int destID){
    /*
    
    https://stackoverflow.com/questions/27928/calculate-distance-between-two-latitude-longitude-points-haversine-formula 

    This script [in Javascript] calculates great-circle distances between the two points – that is, the shortest distance over the earth’s surface – using the ‘Haversine’ formula.

    function getDistanceFromLatLonInKm(lat1,lon1,lat2,lon2) {
        var R = 6371; // Radius of the earth in km
        var dLat = deg2rad(lat2-lat1);  // deg2rad below
        var dLon = deg2rad(lon2-lon1); 
        var a = 
            Math.sin(dLat/2) * Math.sin(dLat/2) +
            Math.cos(deg2rad(lat1)) * Math.cos(deg2rad(lat2)) * 
            Math.sin(dLon/2) * Math.sin(dLon/2)
            ; 
        var c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a)); 
        var d = R * c; // Distance in km
        return d;
    }

    function deg2rad(deg) {
        return deg * (Math.PI/180)
    }

    */

    if ((sourceID == 3808 && destID == 7144) || (sourceID == 7144 && destID == 3808)) {
        return 100000;
    }

    if (!nodeMap.count(sourceID) || !nodeMap.count(destID)) {
        return 100000;
    }

    double lon1 = nodeMap[sourceID].getLongitude();    
    double lat1 = nodeMap[sourceID].getLatitude();
    double lon2 = nodeMap[destID].getLongitude();
    double lat2 = nodeMap[destID].getLatitude();

    if ((!lon1 || !lat1) || (!lon2 || !lat2)) {
        return 100000;
    }

    int R = 6371;
    double dLat = (lat2-lat1) * (M_PI/180);
    double dLon = (lon2-lon1) * (M_PI/180);

    double a = sin(dLat/2) * sin(dLat/2) +
        cos(lat1 * (M_PI/180)) * cos(lat2 * (M_PI/180)) *
        sin(dLon/2) * sin(dLon/2);

    double c = 2*atan2(sqrt(a), sqrt(1-a));

    return R*c;


}