#include<bits/stdc++.h>
#include<omp.h>

using namespace std;

int V, E;

void parallelDfsUtil(int src, vector<bool>&vis, vector<int> adj[])
{
    vis[src] = true;
    cout << src << " ";

    #pragma omp parallel for
    for (int i = 0; i < adj[src].size();i++)
    {
        int n = adj[src][i];
        if(!vis[n])
            parallelDfsUtil(n, vis, adj);
    }
}

void parallelDfs(int src,vector<int> adj[])
{
    vector<bool> vis(V, false);
    parallelDfsUtil(src, vis, adj);
}

void parallelBfs(int src, vector<int> adj[])
{
    vector<bool> vis(V, false);
    queue<int> q;

    vis[src] = true;
    q.push(src);

    while(!q.empty())
    {
        int v = q.front();
        q.pop();

        cout << v << " ";
#pragma omp parallel for
        for (int i = 0; i < adj[v].size();i++)
        {
            int n = adj[v][i];
            if(!vis[n])
            {
                vis[n] = true;
                q.push(n);
            }
        }
    }

}

int main()
{
    cout<<"\nEnter no of vertices:- ";
    cin >> V;
    cout<<"\nEnter no of edges:- ";
    cin >> E;
    vector<int> adj[V];

    for (int i = 0; i < E;i++)
    {
        cout << "\nEnter edge no " << i + 1 << ":- ";
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int src;
    cout<<"\nEnter src:- ";
    cin >> src;

    cout << "\nDFS:-\n";
    parallelDfs(src, adj);

    cout << "\nBFS:-\n";
    parallelBfs(src, adj);
}