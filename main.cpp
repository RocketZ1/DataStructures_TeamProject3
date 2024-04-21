#include <iostream>
#include <fstream>
#include "Graph.h"
#include "minheap.cpp"
using namespace std;

Graph* readCSV() {
    ifstream fileIn("C:\\Users\\JJord\\Team Project\\DataStructures_TeamProject3\\airports.csv");
    string lineText;
    //Airport object
    Graph* airports = new Graph();

    // Get rid of column name line
    getline(fileIn, lineText);

    while (getline (fileIn, lineText)) {
        // Output the text from the file
        string originAirport = lineText.substr(0, 3);
        string destinationAirport = lineText.substr(4, 3);
        int originCityNamePos = lineText.find('\"', 9);
        string originCity = lineText.substr(9, originCityNamePos-9);
        lineText = lineText.substr(originCityNamePos+3, lineText.size()-9);
        int destinationCityNamePos = lineText.find("\"");
        string destinationCity = lineText.substr(0, destinationCityNamePos);
        lineText = lineText.substr(destinationCityNamePos+2, lineText.size()-destinationCityNamePos);
        int distancePos = lineText.find(",");
        int distance = stoi(lineText.substr(0, distancePos));
        lineText = lineText.substr(distancePos+1, lineText.size()-distancePos);
        int cost = stoi(lineText);

        // Read all variables from file
        // Create airport object
        Airport origin;
        origin.code = originAirport;
        origin.city = originCity;
        Airport destination;
        destination.code = destinationAirport;
        destination.city = destinationCity;
        airports->addAirport(origin);
        airports->addAirport(destination);
        airports->addConnection(searchAirport(airports->getRoot(), origin.code), searchAirport(airports->getRoot(), destination.code), distance, cost);
    }
    
    // Close the file
    fileIn.close();
    return airports;
}

/*
void shortestPath(std::string src, std::string dest) {
    std::vector<SearchNode>* nodes = new std::vector<SearchNode>(140); 
    MinHeap* heap = new MinHeap(140); //140 total airports
    std::string curNode = src;
    
    for (int i = 0; i < nodes.size(); i++) {
        nodes[i].distance = MAX_DIST;
        nodes[i].visited = false;
    }
    distances[0] = 0;

    int verticiesVisited = 0;
    while (verticiesVisited < distances.size()) {
        
    }

}
*/
int main(){

    Graph* airports = readCSV();
    AVLNode* root = airports->getRoot();
    cout << root->airport.code << std::endl;
    cout << root->airport.city << std::endl;
    cout << root->airport.connections[0]->airport.code << std::endl;
    cout << root->airport.connections[0]->airport.city << std::endl;
    cout << root->airport.distances[0] << std::endl;
    cout << root->airport.costs[0] << std::endl;



    delete heap;
    return 0;
}