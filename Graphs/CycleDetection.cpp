// Detect cyles in directed graph

#include <iostream>
#include <vector>
#include <cstring>

void dfs(int node, std::vector<std::vector<int>> adjList, bool currCycle[], bool visited[], bool &foundCycle) {
    // Stops remaining DFS searches if cycle has been found
    if (foundCycle) {
        return;
    }

    if (currCycle[node]) {
        foundCycle = true;
        return;
    }
    currCycle[node] = true;

    for (int n : adjList[node]) {
        if (!visited[n]) {
            dfs(n, adjList, currCycle, visited, foundCycle);
        }
    }
    currCycle[node] = false;
    visited[node] = true;
}

// Cycle detection for 
bool containsCycle(std::vector<std::vector<int>> adjList) {
    int N = adjList.size();

    bool currCycle[N];
    bool visited[N];
    memset(currCycle, false, adjList.size() * sizeof(bool));
    memset(visited, false, adjList.size() * sizeof(bool));

    bool foundCycle = false;

    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            dfs(i, adjList, currCycle, visited, foundCycle);
        }
    }

    return foundCycle;
}

int main() {
    std::vector<std::vector<int>> g(5);
    g[0].push_back(1);
    g[0].push_back(2);
    g[0].push_back(3);
    g[0].push_back(4);
    g[1].push_back(3);
    g[2].push_back(3);
    g[2].push_back(4);
    g[3].push_back(4);
    g[4].push_back(3);

    if (containsCycle(g)) {
        std::cout << "Cyclic" << std::endl;
    }
    else {
        std::cout << "Acyclic" << std::endl;
    }

    return 0;
}