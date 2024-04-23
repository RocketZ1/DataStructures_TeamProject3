#include <iostream>
#include <fstream>
#include "Graph.h"
using namespace std;
#define MAX_DIST 5000;
struct Graphs {
    Graph* airports;
    Graph* undirectedAirports;
};

// Returns the AVL Graph
Graphs * readCSV() {
    ifstream fileIn(R"(C:\Users\VenaFL\Downloads\DataStructures_TeamProject3\DataStructures_TeamProject3\airports.csv)");
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

//Shortest Paths:

//Call shortest path on every airport in destState


int findIndexOfCode(const std::vector<SearchNode>& nodes, std::string codeToFind) {
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i].code == codeToFind)
            return i;
    }
    return -1;
}

// Helper function to get shortest path from source to j
void getPath(std::vector<int>& parent, int j, std::vector<SearchNode>& nodes, std::vector<string>& output) {
    // Base Case: If j is source
    if (parent[j] == -1) {
        output.push_back(nodes[j].code);
        return;
    }

    getPath(parent, parent[j], nodes, output);
    output.push_back(nodes[j].code);
}

// Function to get total cost of the shortest path
int getTotalCost(vector<string> pathCodes, Graph* graph) {
    int totalCost = 0;
    AVLNode* curNode;
    for (int i = 0; i < pathCodes.size() - 1; i++) {
        curNode = searchAirport(graph->getRoot(),pathCodes[i]);
        for (int connect = 0; connect < curNode->airport.connections.size(); connect++) {
            if (curNode->airport.connections[connect]->airport.code == pathCodes[i+1]) {
                totalCost += curNode->airport.costs[connect];
            }
        }
    }
    return totalCost;
}

void shortestPath(std::string src, std::string dest, Graph* graph) {
    std::vector<SearchNode> nodes; // Vector to hold all airport codes
    MinHeap* heap = new MinHeap(140); // Assuming 140 total airports

    // Adds all node names (airport codes) to the vector
    pushAirportCodesToVector(graph->getRoot(), nodes);

    // Initialize all nodes with distance as MAX_DIST and unvisited
    for (int i = 0; i < nodes.size(); i++) {
        nodes[i].distance = MAX_DIST;
        nodes[i].visited = false;
    }

    // Set distance of source node to 0
    int curIndex = findIndexOfCode(nodes, src);
    nodes[curIndex].distance = 0;

    // Add the source node to the min heap
    heap->insert(nodes[curIndex].code, nodes[curIndex].distance);

    // Parent array to store the parent of each node on the shortest path tree
    std::vector<int> parent(nodes.size(), -1);

    // Dijkstra's algorithm
    while (!heap->isEmpty()) {
        // Get current node by choosing the node with minimum cost from the heap
        AVLNode* curNode = searchAirport(graph->getRoot(), heap->getMin().code);
        curIndex = findIndexOfCode(nodes, curNode->airport.code);

        // Update distances in the nodes vector if a shorter path is found
        for (int i = 0; i < curNode->airport.connections.size(); i++) {
            AVLNode* connectionNode = curNode->airport.connections[i];
            int indexOfConnection = findIndexOfCode(nodes, connectionNode->airport.code);

            // Ignore connection if it has been visited
            if (nodes[indexOfConnection].visited) {
                continue;
            }

            // If distance to reach curNode + distance to reach connectionNode < its current cost
            int newDistance = nodes[curIndex].distance + curNode->airport.distances[i];
            if (newDistance < nodes[indexOfConnection].distance) {
                nodes[indexOfConnection].distance = newDistance;
                heap->insert(connectionNode->airport.code, newDistance);

                // Update parent of connectionNode
                parent[indexOfConnection] = curIndex;
            }
        }

        // Mark current node as visited after checking all connections
        nodes[curIndex].visited = true;
    }

    // Print the shortest path from src to dest
    vector<string> pathStrings;
    int destIndex = findIndexOfCode(nodes, dest);
    getPath(parent, destIndex, nodes, pathStrings);
    string outputString;

    if (nodes[destIndex].distance != 5000) {
        cout << "Shortest route from " << src << " to " << dest << ": ";

        for (string code : pathStrings) {
            if (code == dest) {
                outputString += code;
                continue;
            }
            outputString += code + "->";

        }
        cout << outputString << endl;
        cout << "The length is " << nodes[destIndex].distance << ". The cost is " << getTotalCost(pathStrings, graph) << "." << std::endl;
    }

    else {
        std::cout << "Shortest route from " << src << " to " << dest << ": None" << std::endl;
    }
}

void shortestPathToStateHelper(AVLNode* node, string src, string destState, Graph* graph) {
    if (node == NULL || node->airport.city.length() < 2)
        return;

    string nodeState = node->airport.city.substr(node->airport.city.length() - 2);
    if (nodeState == destState) {
        shortestPath(src,node->airport.code, graph);
        cout << endl;
    }
    shortestPathToStateHelper(node->left, src, destState, graph);
    shortestPathToStateHelper(node->right, src, destState, graph);
}

void shortestPathToState(string src, string dest, Graph* graph) {
    //Extract state
    string destState = dest.substr(dest.length() - 2);
    shortestPathToStateHelper(graph->getRoot(), src, destState, graph);
}


//End Shortest Path's


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


    Graphs* graphs = readCSV();
    Graph* airports = graphs->airports;
    Graph* undirectedAirports = graphs->undirectedAirports;
    AVLNode* root = airports->getRoot();
//    cout << root->airport.code << std::endl;
//    cout << root->airport.city << std::endl;
//    cout << root->airport.connections[0]->airport.code << std::endl;
//    cout << root->airport.connections[0]->airport.city << std::endl;
//    cout << root->airport.distances[0] << std::endl;
//    cout << root->airport.costs[0] << std::endl;
//    root = undirectedAirports->getRoot();
//    cout << root->airport.code << std::endl;
//    cout << root->airport.city << std::endl;
//    cout << root->airport.connections[0]->airport.code << std::endl;
//    cout << root->airport.connections[0]->airport.city << std::endl;
//    cout << root->airport.distances[0] << std::endl;
//    cout << root->airport.costs[0] << std::endl;


    shortestPathToState("MIA", "IL", airports);
    //totalFlightConnections(airports, root);
//    cout << root->airport.code << std::endl;
//    cout << root->airport.city << std::endl;
//    cout << root->airport.connections[0]->airport.code << std::endl;
//    cout << root->airport.connections[0]->airport.city << std::endl;
//    cout << root->airport.distances[0] << std::endl;
//    cout << root->airport.costs[0] << std::endl;
    return 0;
}