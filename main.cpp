#include <iostream>
#include <vector>
#include <fstream>
#include "Airports.h"

using namespace std;

int main() {
    string startLoc;
    string destLoc;

    while (true){
        cout << "Starting Location: ";
        cin >> startLoc;
        cout << "Destination Location: ";
        cin >> destLoc;

        if (startLoc.length() != 3 || destLoc.length() != 3){
            cout << "Please input the airport's 3 letter IATA code" << endl;
            continue;
        }
        else{
            bool flag = false;
            for (int i = 0; i< 3; i++){
                if (!isalpha(startLoc[i]) || !isalpha(destLoc[i])){
                    cout << "Please input the airport's 3 letter IATA code" << endl;
                    flag = true;
                }
                
                transform(startLoc.begin(), startLoc.end(),startLoc.begin(), ::toupper);
                transform(destLoc.begin(), destLoc.end(),destLoc.begin(), ::toupper);

                if (flag) break;
            }
            if (flag) continue;
        }
        break;
    }

    Airports flights("flight_data.txt","airport_data.txt", startLoc, destLoc);

    if (flights.getStartID() < 0 || flights.getDestID() < 0){
        cout << "Please use a proper IATA 3 character Airport ID, reset." << endl;
        return -1;
    }

    //BFS has large output so we will store it in a text file rather than writing to the terminal 
    vector<string> bfsVec = flights.bfs();
    ofstream bfsOut;
    bfsOut.open("bfs.txt");

    cout << "BFS starting at: " << startLoc << endl;
    bfsOut << "BFS starting at: " << startLoc << endl;

    for (size_t i = 0; i<bfsVec.size(); i++)
        bfsOut << bfsVec[i] << endl;

    cout << "BFS stored in bfs.txt" << endl;
    cout << "This list includes all destinations should you want to use this starting location again. " << endl;

    if (! flights.pathExists()){
        cout << "There are no flight paths connecting these airports, please reset." << endl;
        return -1;
    }

    cout << "Using Dijkstra's search algorithm to find the shortest path between " << startLoc << " and " << destLoc << "..." << endl;

    // runs Dijkstra and gets runtime stored in two chrono::system_clocks
    auto start_dij = std::chrono::system_clock::now();
    tuple<vector<string>, double> dijkstraPath = flights.dijkstras();
    auto end_dij = std::chrono::system_clock::now();
    int dij_steps = flights.number_of_steps;

    // runs A* and gets runtime stored in two chrono::system_clocks
    auto start_astar = std::chrono::system_clock::now();
    tuple<vector<string>, double> astarPath = flights.astar();
    auto end_astar = std::chrono::system_clock::now();
    int astar_steps = flights.number_of_steps;

    std::chrono::duration<double> dij_time = end_dij - start_dij;
    std::chrono::duration<double> astar_time = end_astar - start_astar;

    cout << "The shortest path is: " << endl;
    for (size_t i = 0; i < get<0>(dijkstraPath).size(); i++){
        if (i == get<0>(dijkstraPath).size()-1) cout << get<0>(dijkstraPath)[i] << endl;
        else cout << get<0>(dijkstraPath)[i] << " to ";
    }

    cout << "The distance of the path is: " << get<1>(dijkstraPath) << "km" << endl;
    cout << "Dijkstra's algorithm took " << dij_steps << " steps in " << dij_time.count() << " seconds." << endl;
    cout << "The A* algorithm took " << astar_steps << " steps in " << astar_time.count() << " seconds." << endl;

    return 0;
}