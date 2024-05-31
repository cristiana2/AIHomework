#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>

using namespace std;

int n;
vector<vector<int>> dist;

struct State {
    int city, cost, longestEdge, visited;

    bool operator>(const State& other) const {
        return max(longestEdge, dist[city][0]) > max(other.longestEdge, dist[other.city][0]);
    }
};

int uniformCostSearch() {
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({0, 0, 0, 1});

    int minLongestEdge = INT_MAX;

    while (!pq.empty()) {
        auto [curr, cost, longestEdge, visited] = pq.top();
        pq.pop();

        if (visited == (1 << n) - 1 && dist[curr][0] > 0) {
            minLongestEdge = min(minLongestEdge, max(longestEdge, dist[curr][0]));
            continue;
        }

        for (int i = 0; i < n; ++i) {
            if (!(visited & (1 << i)) && dist[curr][i] > 0) {
                pq.push({i, cost + dist[curr][i], max(longestEdge, dist[curr][i]), visited | (1 << i)});
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

    int result = uniformCostSearch();
    cout << "Minimum longest edge in the best route: " << result << endl;

    return 0;
}
