#include <iostream>
#include <fstream>
#include <vector>
#include <minheap.cpp>
#include "AVL.cpp"

using namespace std;
#define MAX_DIST 5000;

void readCSV() {
    ifstream fileIn(R"(C:\Users\Zane\Desktop\Development\C++\DataStructures_TeamProject3\airports.csv)");
    string lineText;
    //Airport object
    AVLNode airports;

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

        // Create airport object
        Airport origin;
        origin.code = originAirport;
        origin.city = originCity;
        Airport destination;
        destination.code = destinationAirport;
        destination.city = destinationCity;
        AVLNode* originNode = airports.insertAirport(origin);
        AVLNode* destinationNode = airports.insertAirport(destination);
        airports.addConnection(originNode, destinationNode, distance, cost);
    }
    // Close the file
    fileIn.close();
}

//Shortest paths:

void shortestPath(std::string src, std::string dest) {
    std::vector<SearchNode> nodes = new std::vector<SearchNode>(140); 
    MinHeap heap = new MinHeap(140); //140 total airports
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

int main(){
    readCSV();
    return 0;
}