#include "bits/stdc++.h"

using namespace std;

vector<vector<int>> adj_matrix, inv_adj;
vector<int> visited, order, component;

void dfs1(int node)
{
    visited[node] = true;

    for (auto v : adj_matrix[node])
        if (!visited[v])
            dfs1(v);

    order.push_back(node);
}

void dfs2(int node)
{
    visited[node] = true;

    for (auto v : inv_adj[node])
        if (!visited[v])
            dfs2(v);

    component.push_back(node);
}

void kosaraju(int n)
{
    // build topologically sorted order of nodes in vector 'order'
    for (int i = 0; i < n; i++)
        if (!visited[i])
            dfs1(i);

    reverse(order.begin(), order.end());
    int num_components = 0;

    visited.clear();
    visited.resize(n, 0);
    for (int i = 0; i < n; i++)
    {
        if (visited[order[i]])
            continue;
        num_components++;
        component.clear();
        dfs2(order[i]);

        cout << "Strongly Connected Component " << num_components << ": ";
        for (auto u : component)
        {
            cout << u + 1 << " ";
        }
        cout << "\n";
    }
}

int main()
{
    // n : number of nodes in the graph.
    // m : number of edges in the graph.
    int n, m;
    cin >> n >> m;

    // resizing adjacency lists.
    adj_matrix.resize(n, vector<int>(0));
    inv_adj.resize(n, vector<int>(0));
    visited.resize(n, 0);
    order.clear(), component.clear();

    // taking edges as input. "x y" means there is an edge from x to y. Input should be 1 indexed.
    int x, y;
    for (int i = 0; i < m; i++)
    {
        cin >> x >> y;
        x--, y--;
        adj_matrix[x].push_back(y);
        inv_adj[y].push_back(x);
    }

    kosaraju(n);
}