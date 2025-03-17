#include "dijkstras.h"

using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
	vector<int> distances(G.numVertices, INF);
	vector<bool> visited(G.numVertices, false);
	previous.resize(G.numVertices, -1);

	distances[source] = 0;
	previous[source] = -1;

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
	minHeap.push({0, source});
	
	while (!minHeap.empty()) {
		int u = minHeap.top().second;
		minHeap.pop();

		if (visited[u]) continue;
		visited[u] = true;
		
		for (Edge edge : G[u]) {
			int v = edge.dst;
			int weight = edge.weight;
			if (!visited[v] && distances[u] + weight < distances[v]) {	
				distances[v] = distances[u] + weight;
				previous[v] = u;
				minHeap.push({distances[v], v});
			}
		}
	}
	return distances;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination){
	vector<int> shortest_path;
	for (int i = destination; i != -1; i = previous[i]) {
		shortest_path.push_back(i);
	}
	reverse(shortest_path.begin(), shortest_path.end());
	return shortest_path;
}

void print_path(const vector<int>& v, int total){
	int size = v.size();
	for (int i = 0; i < size; ++i) {
		cout << v[i] << ' ';
	}
	cout << endl << "Total cost is " << total << endl;
}
