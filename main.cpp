#include <iostream>
#include <fstream>
#include "AVL.cpp"

using namespace std;

// Returns the AVL Graph
AVLNode* readCSV() {
    ifstream fileIn(R"(C:\Users\Zane\Desktop\Development\C++\DataStructures_TeamProject3\airports.csv)");
    string lineText;
    //Airport object
    AVLNode* airports = new AVLNode();

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

        AVLNode* originNode = airports->insertAirport(origin);
        AVLNode* destinationNode = airports->insertAirport(destination);
        airports->addConnection(originNode, destinationNode, distance, cost);
    }
    // Close the file
    fileIn.close();
    return airports;
}

void printAVLTree(AVLNode *airports){
    // Height Display
    for(int i = 0; i < airports->getHeight(); i++){
        cout << "-";
    }
    cout << airports->getAirport().code << endl;
    if(airports->getLeft() != nullptr){
        cout << "L";
        printAVLTree(airports->getLeft());
    }
    if(airports->getRight() != nullptr){
        cout << "R";
        printAVLTree(airports->getRight());
    }
}


int main(){
    // Builds the AVL Graph from the CSV data
    AVLNode* airports = readCSV();
    printAVLTree(airports);


    return 0;
}