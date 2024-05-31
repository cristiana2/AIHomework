#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <climits>

using namespace std;

int n;
vector<vector<int>> dist;

struct State {
    int city, cost, longestEdge, visited, estimate;

    bool operator>(const State& other) const {
        return estimate > other.estimate;
    }
};

int heuristic(int visited, int longestEdge) {
    int remainingCost = 0;
    for (int i = 0; i < n; ++i) {
        if (!(visited & (1 << i))) {
            int minEdge = INT_MAX;
            for (int j = 0; j < n; ++j) {
                if (i != j && dist[i][j] > 0) {
                    minEdge = min(minEdge, dist[i][j]);
                }
            }
            remainingCost += minEdge;
        }
    }
    return max(longestEdge, remainingCost);
}

int aStarSearch() {
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({0, 0, 0, 1, heuristic(1, 0)});

    int minLongestEdge = INT_MAX;

    while (!pq.empty()) {
        auto [curr, cost, longestEdge, visited, estimate] = pq.top();
        pq.pop();

        if (visited == (1 << n) - 1 && dist[curr][0] > 0) {
            minLongestEdge = min(minLongestEdge, max(longestEdge, dist[curr][0]));
            continue;
        }

        for (int i = 0; i < n; ++i) {
            if (!(visited & (1 << i)) && dist[curr][i] > 0) {
                int newLongestEdge = max(longestEdge, dist[curr][i]);
                int newVisited = visited | (1 << i);
                pq.push({i, cost + dist[curr][i], newLongestEdge, newVisited, heuristic(newVisited, newLongestEdge)});
            }
        }
    }

    return minLongestEdge;
}

int main() {
    // Example input
    n = 4;
    dist = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    int result = aStarSearch();
    cout << "Minimum longest edge in the best route: " << result << endl;

    return 0;
}
