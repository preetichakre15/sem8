#include <iostream>
#include <queue>
#include <stack>
#include <omp.h>

using namespace std;

// Graph representation (adjacency list)
const int MAX_NODES = 100;
vector<int> adj[MAX_NODES];

// Arrays to keep track of visited nodes and levels (for BFS)
bool visited[MAX_NODES];
int level[MAX_NODES];

// Parallel Breadth First Search (BFS)
void parallelBFS(int startNode) {
    queue<int> q;
    q.push(startNode);
    visited[startNode] = true;
    level[startNode] = 0;

    while (!q.empty()) {
        #pragma omp parallel
        {
            #pragma omp for
            for (int i = 0; i < q.size(); i++) {
                int currentNode;
                #pragma omp critical
                {
                    currentNode = q.front();
                    q.pop();
                }

                for (int neighbor : adj[currentNode]) {
                    if (!visited[neighbor]) {
                        #pragma omp critical
                        {
                            visited[neighbor] = true;
                            level[neighbor] = level[currentNode] + 1;
                            q.push(neighbor);
                        }
                    }
                }
            }
        }
    }
}

// Parallel Depth First Search (DFS)
void parallelDFS(int startNode) {
    stack<int> s;
    s.push(startNode);

    while (!s.empty()) {
        #pragma omp parallel
        {
            #pragma omp for
            for (int i = 0; i < s.size(); i++) {
                int currentNode;
                #pragma omp critical
                {
                    currentNode = s.top();
                    s.pop();
                }

                if (!visited[currentNode]) {
                    #pragma omp critical
                    {
                        visited[currentNode] = true;
                    }

                    // Process the node (e.g., print or store result)

                    for (int neighbor : adj[currentNode]) {
                        #pragma omp critical
                        {
                            s.push(neighbor);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    // Example graph
    adj[0] = {1, 2};
    adj[1] = {0, 3, 4};
    adj[2] = {0, 5, 6};
    adj[3] = {1};
    adj[4] = {1};
    adj[5] = {2};
    adj[6] = {2};

    // Initialize visited array
    fill(visited, visited + MAX_NODES, false);

    // Perform parallel BFS
    parallelBFS(0);

    // Print BFS levels
    for (int i = 0; i < MAX_NODES; i++) {
        if (visited[i]) {
            cout << "Node " << i << " is at level " << level[i] << endl;
        }
    }

    // Reset visited and level arrays
    fill(visited, visited + MAX_NODES, false);
    fill(level, level + MAX_NODES, 0);

    // Perform parallel DFS
    parallelDFS(0);

    // Print visited nodes
    for (int i = 0; i < MAX_NODES; i++) {
        if (visited[i]) {
            cout << "Node " << i << " is visited." << endl;
        }
    }

    return 0;
}