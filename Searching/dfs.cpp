#include <bits/stdc++.h>
using namespace std;

int dfs(vector<vector<int>>& g, int x, int y) {
    if (x < 0 || y < 0 || x >= g.size() || y >= g[0].size() || g[x][y] == 0 || g[x][y] == -1) return 1;

    g[x][y] = -1;

    vector<int> dx = {0, 0, 1, -1}, dy = {1, -1, 0, 0};
    int ans = 0;
    for (int i = 0; i < 4; i++) {
        ans += dfs(g, x + dx[i], y + dy[i]);
    }
    return ans;
}

int main() {
    vector<vector<int>> g = {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1}};
    cout << dfs(g, 1, 1) << endl;
    return 0;
}