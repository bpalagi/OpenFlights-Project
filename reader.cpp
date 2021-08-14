/**
 * @file reader.cpp
 */

#include "reader.h"
#include "airport_node.h"
#include "airport_node.cpp"

using namespace std;

Reader::Reader() {
    airportFileName = "";
    flightFileName = "";
}

Reader::Reader(string airportFileName, string flightFileName) {
    this->airportFileName = airportFileName;
    this->flightFileName = flightFileName;
}

Reader::~Reader() {
    deleteData();
}

void Reader::assignAirportFile(string fileName) {
    airportFileName = fileName;
}

void Reader::assignFlightFile(string fileName) {
    flightFileName = fileName;
}

void Reader::readAirports(int end_index) { // end_index NOT inclusive
    deleteData();
    airports = new AirportNode*[end_index]; // clears data and initializes new array based on end_index.
    
    ifstream file;
    file.open(airportFileName); // opens up input file stream.

    string line;

    if (file.is_open()) {
        int index = 1;
        while (getline(file,line) && index < end_index) { // for each new line, generate a new AirportNode based on the data.
            airports[index] = readAirportLine(line);
            index++;
        }
    }

    file.close();
}

void Reader::readFlights(int end_index) {
    ifstream file;
    file.open(flightFileName); // opens up input file stream.

    string line;

    if (file.is_open()) {
        int index = 0;
        while (getline(file,line) && index < end_index) { // for each new line, generate a new AirportNode based on the data.
            readFlightLine(line);
            index++;
        }
    }

    file.close();
}

AirportNode** Reader::getAirports() {
    return airports;
}

void Reader::deleteData() {
    /*int size = sizeof(airports);
    for (int i = 0; i < size; i++) {
        delete airports[i];
    }*/
}

AirportNode* Reader::readAirportLine(string line){
    if (line.size() == 0) return new AirportNode();

    //split up line by commas
    stringstream stream(line); 
    
    string substr;
    getline(stream, substr, ',');
    int id = std::stoi(substr, nullptr);
    
    getline(stream, substr, ',');
    string name = substr;

    getline(stream, substr, ',');
    string city = substr;

    getline(stream, substr, ',');
    string country = substr;

    getline(stream, substr, ',');
    string IATA = substr;

    getline(stream, substr, ',');
    string ICAO = substr;

    getline(stream, substr, ',');
    double latitude = std::stod(substr, nullptr);
    
    getline(stream, substr, ',');
    double longitude = std::stod(substr, nullptr);

    getline(stream, substr, ',');
    double altitude = std::stod(substr, nullptr);
    
    getline(stream, substr, ',');
    double timezone = std::stod(substr, nullptr);
    
    getline(stream, substr, ',');
    string DST = substr;

    return new AirportNode(id, name, city, country, IATA, ICAO, latitude, longitude,
            altitude, timezone, DST);
}

void Reader::readFlightLine(string line){
    // airline airlineID source sourceID destination destinationID codeshare stops equipment

    if (line.size() == 0) return;

    //split up line by commas
    stringstream stream(line); 
    
    string substr;
    getline(stream, substr, ',');
    //airline
    
    getline(stream, substr, ',');
    //airlineID

    getline(stream, substr, ',');
    string source = substr;

    getline(stream, substr, ',');
    int sourceID = std::stoi(substr, nullptr);

    getline(stream, substr, ',');
    string destination = substr;

    getline(stream, substr, ',');
    int destinationID = std::stoi(substr, nullptr);

    // source to destination
    airports[sourceID]->addEdge(airports[destinationID]);

    // destination to source
    airports[destinationID]->addEdge(airports[sourceID]);
}

int Reader::getFileLength(string fileName) {
    int counter = 0;
    
    ifstream file;
    file.open(fileName, ios::in);

    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            counter++;
        }
    }

    file.close();

    return counter;
}

int Reader::bfs(AirportNode* node) {
    
}