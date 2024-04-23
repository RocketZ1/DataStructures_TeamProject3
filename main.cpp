#include <iostream>
#include <fstream>
#include <algorithm> //for std::reverse
#include "Graph.h"
using namespace std;
#define MAX_DIST 5000
struct Graphs {
    Graph* airports;
    Graph* undirectedAirports;
};

// Returns the AVL Graph
Graphs * readCSV() {
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
    Graphs * graphs = new Graphs{airports, undirectedAirports};
    return graphs;
}

// Prompt #5
void findConnections(AVLNode* root, vector<AVLNode*> *inboundAirports, string &code){
    if (root != nullptr && !root->airport.code.empty()) {
        findConnections(root->left, inboundAirports, code);

        for(AVLNode * airport : root->airport.connections){
            if(airport->airport.code == code){
                inboundAirports->push_back(root);
            }
        }

        findConnections(root->right, inboundAirports, code);
    }
}

struct totalFlightConnectionHelperStruct {
    string code;
    vector<AVLNode*> outboundAirports;
    vector<AVLNode*> *inboundAirports;
    bool beenPrinted = false;
};

totalFlightConnectionHelperStruct* totalFlightConnectionsHelper(Graph* graph, AVLNode* root, vector<totalFlightConnectionHelperStruct*>* flightConnectionsContainer){
    if (root != nullptr && !root->airport.code.empty()) {
        totalFlightConnectionsHelper(graph, root->left, flightConnectionsContainer);

        vector<AVLNode*> outboundAirports = root->airport.connections;
        vector<AVLNode*> *inboundAirports = new vector<AVLNode*>;
        findConnections(graph->getRoot(), inboundAirports, root->airport.code);
        totalFlightConnectionHelperStruct* container = new totalFlightConnectionHelperStruct
                {root->airport.code, outboundAirports, inboundAirports, false};
        flightConnectionsContainer->push_back(container);
        // Debug text
//        cout << "Outbound Flights: ";
//        for(AVLNode * outboundAirport : outboundAirports){
//            cout << outboundAirport->airport.code << " ";
//        }
//        cout << endl;
//        cout << "Inbound Flights: ";
//        for(AVLNode * inboundAirport : *inboundAirports) {
//            cout << inboundAirport->airport.code << " ";
//        }
//        cout << endl << endl;
        totalFlightConnectionsHelper(graph, root->right, flightConnectionsContainer);
    }
}

void totalFlightConnections(Graph* graph, AVLNode* root){
    vector<totalFlightConnectionHelperStruct*>* flightConnections = new vector<totalFlightConnectionHelperStruct*>;
    totalFlightConnectionsHelper(graph, root, flightConnections);
    vector<string> printedAirports;
    totalFlightConnectionHelperStruct* largestAirport = flightConnections[0][0];
    cout << "Airport\t\tConnections"<<endl;
    while(printedAirports.size() < flightConnections->size()){
        for(int i = 0; i < flightConnections->size(); i++){
            if(flightConnections[0][i]->beenPrinted) continue;
            int tripSize = flightConnections[0][i]->outboundAirports.size() + flightConnections[0][i]->inboundAirports->size();
            if(largestAirport->inboundAirports->size()+largestAirport->outboundAirports.size() < tripSize){
                largestAirport = flightConnections[0][i];
            }
        }

        cout << largestAirport->code << "\t\t" << largestAirport->outboundAirports.size() + largestAirport->inboundAirports->size()<<endl;
        printedAirports.push_back(largestAirport->code);
        largestAirport->beenPrinted = true;
        // reset for next loop
        for(int i = 0; i < flightConnections->size(); i++){
            if(flightConnections[0][i]->beenPrinted) continue;
            largestAirport = flightConnections[0][i];
        }
    }
}

// End prompt #5

//Shortest Paths:

int findIndexOfCode(const std::vector<SearchNode>& nodes, std::string codeToFind) {
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i].code == codeToFind)
            return i;
    }
    return -1;
}
void getPathIterative(std::vector<int>& parent, int destIndex, std::vector<SearchNode>& nodes, std::vector<string>& output) {
    // Start from the destination node
    int currentIndex = destIndex;

    // Traverse back using parent pointers until reaching the source node
    while (currentIndex != -1) {


        // Add the code of the current node to the output
        output.push_back(nodes[currentIndex].code);

        // Move to the parent node
        currentIndex = parent[currentIndex];
    }

    // Reverse the output
    std::reverse(output.begin(), output.end());
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
    MinHeap* heap = new MinHeap(size(graph->getRoot()));

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

//Call shortest path on every airport in destState
void shortestPathToState(string src, string dest, Graph* graph) {
    //Extract state

    string destState = dest.substr(dest.length() - 2);
    cout << "The shortest paths from " << src << " to " << destState << " are:" << endl;
    shortestPathToStateHelper(graph->getRoot(), src, destState, graph);
}

void shortestPathWithStops(std::string src, std::string dest, int numStops, Graph* graph) {
    std::vector<SearchNode> nodes; // Vector to hold all airport codes
    MinHeap* heap = new MinHeap(140); // Assuming 140 total airports

    // Adds all node names (airport codes) to the vector
    pushAirportCodesToVector(graph->getRoot(), nodes);

    // Initialize all nodes with distance as MAX_DIST and unvisited
    for (int i = 0; i < nodes.size(); i++) {
        nodes[i].distance = MAX_DIST;
        nodes[i].visited = false;
    }

    // Set distance of source node to 0, stops = 0
    int curIndex = findIndexOfCode(nodes, src);
    nodes[curIndex].distance = 0;
    nodes[curIndex].stops = 0;

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


            //Set the connection stop number to be curStops + 1, unless its the dest node
            int curStops = nodes[curIndex].stops;
            //Make this path unavailable if this is true
            if (connectionNode->airport.code == dest && curStops != numStops) {
                continue;
            }
            else if (connectionNode->airport.code == dest) {
                nodes[indexOfConnection].stops = curStops;
            }
            else {
                nodes[indexOfConnection].stops = curStops + 1;
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

    if (nodes[destIndex].distance != MAX_DIST) {
        cout << "Shortest route from " << src << " to " << dest << ": ";

        for (string code : pathStrings) {
            if (code == dest) {
                outputString += code;
                continue;
            }
            outputString += code + "->";

        }
        cout << outputString << endl;
        cout << "The length is " << nodes[destIndex].distance << ". The cost is " << getTotalCost(pathStrings, graph) << ". " << "Number of stops: " << numStops << std::endl;
    }

    else {
        std::cout << "Shortest route from " << src << " to " << dest << ": None" << std::endl;
    }
}

//End Shortest Path's



struct Edge {
    string origin, dest;
    int weight;
    Edge(string origin, string dest, int weight) : origin(origin), dest(dest), weight(weight) {}
};

struct Visit {
    string vertex;
    bool visited;
    Visit(string vertex, bool visited) : vertex(vertex), visited(visited) {}
};

void traverseAndAdd(AVLNode* node, vector<Visit>& visited) {
    if (node == nullptr) {
        return;
    }
    Visit visit(node->airport.code, false);
    visited.push_back(visit);

    traverseAndAdd(node->left, visited);
    traverseAndAdd(node->right, visited);
}

vector<Visit> addValuesToVisited(Graph* graph) {
    vector<Visit> visited;

    AVLNode* root = graph->getRoot();

    traverseAndAdd(root, visited);

    return visited;
}

void visit(vector<Visit>& visited, string vertex) {
    for (int i = 0; i < visited.size(); i++) {
        if (visited[i].vertex == vertex) {
            visited[i].visited = true;
            return;
        }
    }
}

bool isVisited(vector<Visit>& visited, string vertex) {
    for (int i = 0; i < visited.size(); i++) {
        if (visited[i].vertex == vertex) {
            return visited[i].visited;
        }
    }
    return false;
}

bool isAllVisited(vector<Visit>& visited) {
    for (int i = 0; i < visited.size(); i++) {
        if (!visited[i].visited) {
            return false;
        }
    }
    return true;
}

void prim(Graph* graph) {
    AVLNode* root = graph->getRoot();
    int numVertices = size(root);
    vector<pair<pair<string, string>, int>> mst;
    vector<Visit> visited;
    MinHeap* heap = new MinHeap(numVertices * numVertices);
    visited = addValuesToVisited(graph);
    visit(visited, root->airport.code);

    for (int i = 0; i < root->airport.connections.size(); i++) {
        heap->insert(root->airport.connections[i]->airport.code, root->airport.code, root->airport.costs[i]);
    }
    while (!heap->isEmpty()) {
        SearchNode minNode = heap->getMin();

        string origin = minNode.origin;
        string dest = minNode.code;

        if (!isVisited(visited, dest)) {
            mst.push_back({{origin, dest}, minNode.distance});
            visit(visited, dest);

            AVLNode* curNode = searchAirport(graph->getRoot(), dest);
            for (int i = 0; i < curNode->airport.connections.size(); i++) {
                if (!isVisited(visited, curNode->airport.connections[i]->airport.code)) {
                    heap->insert(curNode->airport.connections[i]->airport.code, curNode->airport.code, curNode->airport.costs[i]);
                }
            }

        }
    }
    cout << "Minimal Spanning Tree:" << endl;
    int total = 0;
    for (int i = 0; i < mst.size(); i++) {
        cout << mst[i].first.first << " - " << mst[i].first.second << " " << mst[i].second << endl;
        total += mst[i].second;
    }
    cout << "Total cost of MST: " << total << endl;
    if (!isAllVisited(visited)) {
        cout << "The Graph Is Not Connected" << endl;
    }
    return;
}

void printMST(vector<pair<pair<string, string>, int>> mst) {
    for (int i = 0; i < mst.size(); i++) {
        cout << mst[i].first.first << " " << mst[i].first.second << " " << mst[i].second << endl;
    }
}

int main(){
    Graphs* graphs = readCSV();
    Graph* airports = graphs->airports;
    Graph* undirectedAirports = graphs->undirectedAirports;
    AVLNode* root = airports->getRoot();
    totalFlightConnections(airports, root);

    prim(undirectedAirports);



    //shortestPathWithStops("MIA", "DTW", 3, airports);
//    shortestPathToState("MIA", "IL", airports);


    return 0;
}