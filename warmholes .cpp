#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>

using namespace std;

// A structure to represent a point
struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};

// A structure to represent a wormhole
struct Wormhole {
    Point start, end;
    int cost;
    Wormhole(int x1, int y1, int x2, int y2, int _cost) 
        : start(x1, y1), end(x2, y2), cost(_cost) {}
};

// Function to calculate the Manhattan distance between two points
int manhattan_distance(Point p1, Point p2) {
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

// Dijkstra's algorithm to find the shortest path
int dijkstra(Point source, Point destination, vector<Wormhole>& wormholes) {
    // Priority queue to store the current point and the distance to it
    priority_queue<pair<int, Point>, vector<pair<int, Point>>, greater<pair<int, Point>>> pq;
    
    // A map to store the minimum distance to each point
    map<pair<int, int>, int> min_dist;
    
    // Initialize the distance to the source as 0
    pq.push({0, source});
    min_dist[{source.x, source.y}] = 0;

    while (!pq.empty()) {
        // Get the point with the minimum distance
        auto current = pq.top();
        pq.pop();
        int dist = current.first;
        Point cur_point = current.second;

        // If we have reached the destination, return the distance
        if (cur_point.x == destination.x && cur_point.y == destination.y) {
            return dist;
        }

        // Explore direct paths to the destination
        int direct_dist = manhattan_distance(cur_point, destination);
        if (min_dist.find({destination.x, destination.y}) == min_dist.end() || 
            dist + direct_dist < min_dist[{destination.x, destination.y}]) {
            min_dist[{destination.x, destination.y}] = dist + direct_dist;
            pq.push({dist + direct_dist, destination});
        }

        // Explore wormholes
        for (const auto& wormhole : wormholes) {
            // From the current point to the start of the wormhole
            int start_dist = manhattan_distance(cur_point, wormhole.start);
            if (min_dist.find({wormhole.start.x, wormhole.start.y}) == min_dist.end() || 
                dist + start_dist < min_dist[{wormhole.start.x, wormhole.start.y}]) {
                min_dist[{wormhole.start.x, wormhole.start.y}] = dist + start_dist;
                pq.push({dist + start_dist, wormhole.start});
            }
            
            // Use the wormhole (start to end with a given cost)
            int wormhole_cost = start_dist + wormhole.cost;
            if (min_dist.find({wormhole.end.x, wormhole.end.y}) == min_dist.end() || 
                dist + wormhole_cost < min_dist[{wormhole.end.x, wormhole.end.y}]) {
                min_dist[{wormhole.end.x, wormhole.end.y}] = dist + wormhole_cost;
                pq.push({dist + wormhole_cost, wormhole.end});
            }
            
            // From the current point to the end of the wormhole
            int end_dist = manhattan_distance(cur_point, wormhole.end);
            if (min_dist.find({wormhole.end.x, wormhole.end.y}) == min_dist.end() || 
                dist + end_dist < min_dist[{wormhole.end.x, wormhole.end.y}]) {
                min_dist[{wormhole.end.x, wormhole.end.y}] = dist + end_dist;
                pq.push({dist + end_dist, wormhole.end});
            }

            // Use the wormhole in reverse (end to start)
            int reverse_wormhole_cost = end_dist + wormhole.cost;
            if (min_dist.find({wormhole.start.x, wormhole.start.y}) == min_dist.end() || 
                dist + reverse_wormhole_cost < min_dist[{wormhole.start.x, wormhole.start.y}]) {
                min_dist[{wormhole.start.x, wormhole.start.y}] = dist + reverse_wormhole_cost;
                pq.push({dist + reverse_wormhole_cost, wormhole.start});
            }
        }
    }

    // If we reach here, the destination is unreachable (but it shouldn't happen)
    return -1;
}

int main() {
    int x1, y1, x2, y2, N;
    
    // Input the source and destination coordinates
    cin >> x1 >> y1 >> x2 >> y2;
    Point source(x1, y1);
    Point destination(x2, y2);

    // Input the number of wormholes
    cin >> N;
    vector<Wwormholes;
    for (int i = 0; i < N; i++) {
        int x1, y1, x2, y2, cost;
        cin >> x1 >> y1 >> x2 >> y2 >> cost;
        wormholes.push_back(Wormhole(x1, y1, x2, y2, cost));
    }

    // Find and output the minimum distance
    cout << dijkstra(source, destination, wormholes) << endl;

    return 0;
}