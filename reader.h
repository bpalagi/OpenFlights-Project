/**
 * @file reader.h
 * Reader class which can take a file and return workable dat.
 */

#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "airport_node.h"

using namespace std;

class Reader {
    public:
        /**
         * Default constructor.
         */
        Reader();

        /**
         * Constructor with file names.
         */
        Reader(string airportFileName, string flightFileName);

        /**
         * Destructor.
         */
        ~Reader();

        /**
         * Changes the "airportFileName" member variable.
         */
        void assignAirportFile(string fileName);

        /**
         * Changes the "flightFileName" member variable.
         */
        void assignFlightFile(string fileName);

        /**
         * Takes the data from airportFileName and put it into the airports[] array. This method also clears the current data and
         * initializes a new array for airports[].
         * 
         * @param end_index - last line from which data is loaded, not-inclusive
         */
        void readAirports(int end_index);

        /**
         * For every line in flightFileName, create an edge for each node it concerns. Airport ID roughly corresponds to
         * index in airports[] array.
         */
        void readFlights(int end_index);

        /**
         * Returns a pointer to the data in airports[].
         */
        AirportNode** getAirports();

        /**
         * Clears all airport data but does not reassign file names.
         */
        void deleteData();
    
        /**
         * Returns the number of lines in a file.
         */ 
        int getFileLength(string fileName);

        /**
         * Takes in a line of text from the airport file and returns a pointer to a new AirportNode*.
         */
        AirportNode* readAirportLine(string line);

        /**
         * Takes in a line of text from the flight file and creates an edge between the two airports.
         */
        void readFlightLine(string line);

        /**
         * Given an airport name for which to search, return the index of that airport in the array (equivalent to its ID).
         */
        int bfs(AirportNode* node);

    private:
        
        string airportFileName;
        string flightFileName;

        /**
         * Array of AirportNode*s hosted on heap.
         */
        AirportNode** airports;
};
