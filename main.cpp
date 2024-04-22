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
Graphs* readCSV() {
    ifstream fileIn("airports.csv");
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
    Graphs * graphs = new Graphs{airports, undirectedAirports};
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

//void shortestPath(std::string src, std::string dest) {
//    std::vector<SearchNode> nodes(140); //140 total airports
//    MinHeap* heap = new MinHeap(140);
//    std::string curNode = src;
//
//    for (int i = 0; i < nodes.size(); i++) {
//        nodes[i].distance = MAX_DIST;
//        nodes[i].visited = false;
//    }
//
//    nodes[0].distance = 0;
//
//    int verticiesVisited = 0;
//    while (verticiesVisited < distances.size()) {
//
//    }
//
//}

Graph* primsAlgorithm(Graph airports) {
    Graph* mst = new Graph();
    int cost = 0;
    AVLNode* root = airports.getRoot();
    int totalAirports = size(root);
    MinHeap* heap = new MinHeap(totalAirports);
    SearchNode min;
    heap->insert(root->airport.code, 0);
    while(heap->size != 0) {
        min = heap->popMin();
        cost += min.distance;
        mst->addAirport(root->airport);
        mst->addConnectionUndirected(searchAirport(mst->getRoot(), min.code), root, min.distance, 0);
        root = searchAirport(airports.getRoot(), min.code);
        heap->visit(min.code);        
        for(int i = 0; i < root->airport.connections.size(); i++) {
            heap->insert(root->airport.connections[i]->airport.code, root->airport.costs[i]);
        }
    }
    return mst;
}

int main(){
    Graphs * graphs = readCSV();
    Graph* airports = graphs->airports;
    Graph* undirectedAirports = graphs->undirectedAirports;
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