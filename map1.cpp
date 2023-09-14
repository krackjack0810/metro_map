#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <limits>

using namespace std;

// Define the Delhi Metro station structure
struct MetroStation {
    string name;
    unordered_map<string, int> neighbors; // Adjacent stations and their distances
};

// Define the Delhi Metro graph class
class DelhiMetroGraph {
    unordered_map<string, MetroStation> stations;

public:
    // Add a new Metro station to the graph
    void addStation(const string& name) {
        stations[name] = MetroStation{name};
    }

    // Add a metro line between two stations with a given distance
    void addMetroLine(const string& station1, const string& station2, int distance) {
        stations[station1].neighbors[station2] = distance;
        stations[station2].neighbors[station1] = distance;
    }

    // Find the shortest path using Dijkstra's algorithm
    pair<vector<string>, int> shortestPathDijkstra(const string& start, const string& end) {
        unordered_map<string, int> distance;
        unordered_map<string, string> parent;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

        // Initialize distances to infinity
        for (const auto& station : stations) {
            distance[station.first] = numeric_limits<int>::max();
        }

        // Start from the source station
        distance[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            string current = pq.top().second;
            pq.pop();

            if (current == end) {
                // Found the shortest path to the destination
                vector<string> path;
                int totalDistance = distance[end];
                while (current != start) {
                    path.push_back(current);
                    current = parent[current];
                }
                path.push_back(start);
                reverse(path.begin(), path.end());
                return {path, totalDistance};
            }

            for (const auto& neighbor : stations[current].neighbors) {
                string nextStation = neighbor.first;
                int edgeWeight = neighbor.second;

                if (distance[current] + edgeWeight < distance[nextStation]) {
                    distance[nextStation] = distance[current] + edgeWeight;
                    parent[nextStation] = current;
                    pq.push({distance[nextStation], nextStation});
                }
            }
        }

        // No path found to the destination
        return {{}, -1};
    }
};

int main() {
    DelhiMetroGraph metroMap;

    // Adding Delhi Metro stations
    metroMap.addStation("Noida Sector 62");
    metroMap.addStation("Botanical Garden");
    metroMap.addStation("Yamuna Bank");
    metroMap.addStation("Rajiv Chowk");
    // Add more stations here...

    // Adding metro lines and distances
    metroMap.addMetroLine("Noida Sector 62", "Botanical Garden", 8);
    metroMap.addMetroLine("Botanical Garden", "Yamuna Bank", 10);
    metroMap.addMetroLine("Yamuna Bank", "Rajiv Chowk", 6);
    // Add more metro lines here...

    // Find the shortest path between two stations
    string startStation = "Noida Sector 62";
    string endStation = "Rajiv Chowk";
    pair<vector<string>, int> shortestPath = metroMap.shortestPathDijkstra(startStation, endStation);

    if (shortestPath.second != -1) {
        cout << "Shortest Path from " << startStation << " to " << endStation << ":\n";
        for (const string& station : shortestPath.first) {
            cout << station << " -> ";
        }
        cout << "Total Distance: " << shortestPath.second << " km" << endl;
    } else {
        cout << "No path found from " << startStation << " to " << endStation << endl;
    }

    return 0;
}

