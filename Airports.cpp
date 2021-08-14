#include "Airports.h"

using namespace std;

Airports::Airports(string flightData, string airportData, string startCode, string destCode){
    numAirports = 14110;

    myGraph = Graph(flightData, airportData);
        
    unordered_map<string, int>::iterator it;

    it = myGraph.idFromIATA.find(startCode);

    if (it == myGraph.idFromIATA.end())
        startID = -1;
    else
        startID = it->second;

    it = myGraph.idFromIATA.find(destCode);
    if (it == myGraph.idFromIATA.end())
        destID = -1;
    else
        destID = it->second;
}

vector<string> Airports::bfs(){
    vector<bool> visited(numAirports);

    for (int i = 0; i < numAirports; i++)
        visited[i] = false;

    queue<int> Q;
    vector<int> idList;

    Q.push(startID);
    idList.push_back(startID);
    int curr;

    while (!Q.empty()){
        curr = Q.front();

        auto currMap = myGraph.nodeMap[curr].destinations;
        for (auto it = currMap.begin(); it != currMap.end(); it++){
            if(!visited[it->first]){
                visited[it->first] = true;
                Q.push(it->first);
                idList.push_back(it->first);
            }
        }

        Q.pop();
    }

    vector<string> ret;
    for(size_t i =0; i < idList.size(); i++)
        ret.push_back( myGraph.nodeMap[idList[i]].getIATA() + " , " + myGraph.nodeMap[idList[i]].getName());

    return ret;

}

bool Airports::pathExists(){
    vector<bool> visited(numAirports);

    for (int i = 0; i < numAirports; i++)
        visited[i] = false;

    queue<int> Q;

    Q.push(startID);
    int curr;

    while (!Q.empty()){
        curr = Q.front();

        auto currMap = myGraph.nodeMap[curr].destinations;
        for (auto it = currMap.begin(); it != currMap.end(); it++){
            if(!visited[it->first]){
                visited[it->first] = true;
                Q.push(it->first);
            }
        }

        Q.pop();
        if (curr == destID) return true;
    }

    return false;
}

tuple<vector<string>,double> Airports::dijkstras(){    
    vector<double> distance(numAirports + 1);
    vector<int> previous(numAirports + 1);
    vector<int> unvisited;   

    auto currMap = myGraph.nodeMap;
    for (auto it = currMap.begin(); it != currMap.end(); it++) {
        distance[it->first] = INT_MAX;
        unvisited.push_back(it->first);
    }

    distance[startID] = 0;
    previous[startID] = startID;

    int curr;
    number_of_steps = 0;
    while (!unvisited.empty()) {
        number_of_steps++;
        double minDist = INT_MAX;
        int minID;

        for (size_t i=0; i<unvisited.size(); i++) { 
            if (distance[unvisited[i]] < minDist) {
                minDist = distance[unvisited[i]];
                minID = i;
            }
        }

        curr = unvisited[minID];
        unvisited.erase(unvisited.begin()+minID);
        if (curr == destID) break;

        auto currMap = myGraph.nodeMap[curr].destinations;
        for (auto it = currMap.begin(); it != currMap.end(); it++) {
            double newDist = distance[curr] + (it->second).getDistance();
            if (newDist < distance[it->first]) {
                distance[it->first] = newDist;
                previous[it->first] = curr;
            }
        }
    }

    vector<int> previousContiguous;

    while (curr != startID){
        previousContiguous.push_back(curr);
        curr = previous[curr];
    }
    previousContiguous.push_back(startID);

    reverse(previousContiguous.begin(),previousContiguous.end());
    vector<string> shortestPath;

    for(size_t i = 0; i < previousContiguous.size(); i++)
        shortestPath.push_back(myGraph.nodeMap[previousContiguous[i]].getIATA());
    
    tuple<vector<string>,double> ret(shortestPath, distance[destID]);
    return ret;
}


tuple<vector<string>,double> Airports::astar(){
    vector<double> distance(numAirports);
    vector<int> previous(numAirports);
    vector<int> unvisited;   

    auto currMap = myGraph.nodeMap;
    for (auto it = currMap.begin(); it != currMap.end(); it++) {
        distance[it->first] = INT_MAX; // initialize each distance as infinite
        unvisited.push_back(it->first); // load each node's number into the unvisited vector
    }

    distance[startID] = 0;
    previous[startID] = startID;

    int curr;
    number_of_steps = 0;

    while (!unvisited.empty()) { 
        number_of_steps++;
        double minDist = INT_MAX;
        int minID;

        // find node with minimum fcost
        for (size_t i = 0; i < unvisited.size(); i++) { // for each node in unvisited
            if (distance[unvisited[i]] < minDist) { // find index of closest node
                minDist = distance[unvisited[i]];
                minID = i;
            }
        }

        curr = unvisited[minID];
        unvisited.erase(unvisited.begin() + minID); // remove new node from unvisited
        if (curr == destID) break; // termination step

        auto adjacent = myGraph.nodeMap[curr].destinations; // list of nodes to which the current node can travel

        for (auto it = adjacent.begin(); it != adjacent.end(); it++) {
            double newDist = distance[curr] + (it->second).getDistance() - hcost(it->first,destID);
            if (newDist < distance[it->first]) {
                distance[it->first] = newDist;
                previous[it->first] = curr;
            }
        }
    }

    vector<int> previousContiguous;

    while (curr != startID){
        previousContiguous.push_back(curr);
        curr = previous[curr];
    }
    previousContiguous.push_back(startID);

    reverse(previousContiguous.begin(),previousContiguous.end());
    vector<string> shortestPath;

    for(size_t i = 0; i < previousContiguous.size(); i++)
        shortestPath.push_back(myGraph.nodeMap[previousContiguous[i]].getIATA());
    
    tuple<vector<string>,double> ret(shortestPath, distance[destID]);
    return ret;
}

double Airports::hcost(int curr_id, int dest_id) {
    double scaling_factor = 0.4;
    return -1 * scaling_factor * myGraph.distance(curr_id,dest_id);
}
