#include <iostream>
#include "dijkstras.h"

using namespace std;

int main() {
    string filename = "medium.txt";
    Graph G;

    file_to_graph(filename, G);
    cout << "Graph loaded successfully. Number of vertices: " << G.numVertices << endl;

    int source =  4;
    int destination = 7;

    vector<int> previous(G.numVertices, -1);
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    cout << "Shortest path distance from " << source << " to " << destination << " is " << distances[destination] << endl;

    vector<int> path = extract_shortest_path(distances, previous, destination);
    cout << "Shortest path: ";
    print_path(path, distances[destination]);

    return 0;
}