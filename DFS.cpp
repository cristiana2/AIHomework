#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int n;
vector<vector<int>> dist;
vector<bool> visited;
int minLongestEdge = INT_MAX;

void dfs(int curr, int count, int cost, int longestEdge) {
    if (count == n && dist[curr][0] > 0) {
        minLongestEdge = min(minLongestEdge, max(longestEdge, dist[curr][0]));
        return;
    }

    for (int i = 0; i < n; ++i) {
        if (!visited[i] && dist[curr][i] > 0) {
            visited[i] = true;
            dfs(i, count + 1, cost + dist[curr][i], max(longestEdge, dist[curr][i]));
            visited[i] = false;
        }
    }
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

    visited.assign(n, false);
    visited[0] = true;
    dfs(0, 1, 0, 0);

    cout << "Minimum longest edge in the best route: " << minLongestEdge << endl;
    return 0;
}
