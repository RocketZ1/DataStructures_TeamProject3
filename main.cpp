#include <iostream>
#include <fstream>
#include "Graph.h"
#include "minheap.cpp"
using namespace std;
struct Graphs {
    Graph* airports;
    Graph* undirectedAirports;
};

// Returns the AVL Graph
Graph* readCSV() {
    ifstream fileIn(R"(C:\Users\Zane\Desktop\Development\C++\DataStructures_TeamProject3\airports.csv)");
    string lineText;
    //Airport object
    Graph* airports = new Graph();
    Graph* undirectedAirports = new Graph();

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
        undirectedAirports->addAirport(origin);
        undirectedAirports->addAirport(destination);
        undirectedAirports->addConnectionUndirected(searchAirport(undirectedAirports->getRoot(), origin.code), searchAirport(undirectedAirports->getRoot(), destination.code), distance, cost);
    }
    
    // Close the file
    fileIn.close();
    Graphs graphs =  {airports, undirectedAirports};
    return graphs;
}

// Prompt #5
void findConnections(AVLNode* root, vector<AVLNode*> *inboundAirports, string &code){
    if (root != nullptr) {
        findConnections(root->left, inboundAirports, code);

        for(AVLNode * airport : root->airport.connections){
            if(airport->airport.code == code){
                inboundAirports->push_back(airport);
            }
        }

        findConnections(root->right, inboundAirports, code);
    }
}

void totalFlightConnections(Graph* graph, AVLNode* root){
    if (root != nullptr) {
        totalFlightConnections(graph, root->left);

        cout << root->airport.code << endl;
        vector<AVLNode*> outboundAirports = root->airport.connections;
        vector<AVLNode*> *inboundAirports = new vector<AVLNode*>;
        findConnections(graph->getRoot(), inboundAirports, root->airport.code);
        cout << "Outbound Flights: ";
        for(AVLNode * outboundAirport : outboundAirports){
            cout << outboundAirport->airport.code << " ";
        }
        cout << endl;
        cout << "Inbound Flights: ";
        for(AVLNode * inboundAirport : *inboundAirports) {
            cout << inboundAirport->airport.code << " ";
        }
        cout << endl << endl;
        totalFlightConnections(graph, root->right);
    }
}

// End prompt #5

int main(){
    Graphs graphs = readCSV();
    Graph* airports = graphs.airports;
    Graph* undirectedAirports = graphs.undirectedAirports;
    AVLNode* root = airports->getRoot();
    cout << root->airport.code << std::endl;
    cout << root->airport.city << std::endl;
    cout << root->airport.connections[0]->airport.code << std::endl;
    cout << root->airport.connections[0]->airport.city << std::endl;
    cout << root->airport.distances[0] << std::endl;
    cout << root->airport.costs[0] << std::endl;
    root = undirectedAirports->getRoot();
    cout << root->airport.code << std::endl;
    cout << root->airport.city << std::endl;
    cout << root->airport.connections[0]->airport.code << std::endl;
    cout << root->airport.connections[0]->airport.city << std::endl;
    cout << root->airport.distances[0] << std::endl;
    cout << root->airport.costs[0] << std::endl;



    totalFlightConnections(airports, root);
//    cout << root->airport.code << std::endl;
//    cout << root->airport.city << std::endl;
//    cout << root->airport.connections[0]->airport.code << std::endl;
//    cout << root->airport.connections[0]->airport.city << std::endl;
//    cout << root->airport.distances[0] << std::endl;
//    cout << root->airport.costs[0] << std::endl;
    return 0;
}