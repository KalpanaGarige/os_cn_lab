/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

// exp2_distance_vector.cpp
// Distance Vector Routing Simulation using Bellman-Ford logic
// Compile: g++ -std=c++17 exp2_distance_vector.cpp -o exp2_dv

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    int n;
    cout << "Enter number of nodes: ";
    cin >> n;

    vector<vector<int>> cost(n, vector<int>(n));

    cout << "Enter cost adjacency matrix (use " << INF << " for no link):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];
            if (i == j) cost[i][j] = 0;
        }
    }

    // Distance Vector table
    vector<vector<int>> dist = cost;

    bool changed = true;
    int iteration = 0;

    while (changed) {
        changed = false;
        iteration++;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {

                for (int k = 0; k < n; k++) {
                    if (cost[i][k] == INF || dist[k][j] == INF) 
                        continue;

                    int newDist = cost[i][k] + dist[k][j];

                    if (newDist < dist[i][j]) {
                        dist[i][j] = newDist;
                        changed = true;
                    }
                }
            }
        }

        if (iteration > n + 5) break;
    }

    cout << "\nFinal Distance Vector Table:\n";
    for (int i = 0; i < n; i++) {
        cout << "Node " << i << ":\n";
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF) cout << "  " << j << " : INF\n";
            else cout << "  " << j << " : " << dist[i][j] << "\n";
        }
        cout << "\n";
    }

    return 0;
}
