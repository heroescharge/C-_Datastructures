/*
Find diameter and center of a tree
*/

#include <iostream>
#include <vector>
#include <queue>

int findFarthestNode(std::vector<int> graph[], int node, int N) {
    std::queue<int> nodeQ;
    nodeQ.push(node);
    bool visited[N];
    for (int i = 0; i < N; i++) { visited[i] = false; }

    visited[node] = true;
    while (!nodeQ.empty()) {
        int nextNode = nodeQ.front();
        nodeQ.pop();

        for (int n : graph[nextNode]) {
            if (!visited[n]) {
                visited[n] = true;
                nodeQ.push(n);
            }
        }

        if (nodeQ.empty()) {
            return nextNode;
        }
    }

    std::cout << "ERROR: No farthest node found" << std::endl;
    return -1;
}

int findFarthestNodeDistance(std::vector<int> graph[], int node, bool visited[]) {
    int maxDistance = 0;

    visited[node] = true;
    for (int n : graph[node]) {
        if (!visited[n]) {
            maxDistance = std::max(maxDistance, 1 + findFarthestNodeDistance(graph, n, visited));
        }
    }

    return maxDistance;
}

std::vector<int> findPath(std::vector<int> graph[], int start, int end, int N) {
    std::queue<int> nodeQ;

    bool visited[N];
    for (int i = 0; i < N; i++) { visited[i] = false; }
    
    nodeQ.push(end);
    visited[end] = true;

    int distFromEnd[N];
    for (int i = 0; i < N; i++) { distFromEnd[i] = 0; }

    while (!nodeQ.empty()) {
        int nextNode = nodeQ.front();
        nodeQ.pop();

        for (int n : graph[nextNode]) {
            if (!visited[n]) {
                visited[n] = true;
                distFromEnd[n] = 1 + distFromEnd[nextNode];
                nodeQ.push(n);
            }
        }
    }

    std::vector<int> path;
    path.push_back(start);
    int nextNode = start;
    while (nextNode != end) {
        for (int n : graph[nextNode]) {
            if (distFromEnd[n] < distFromEnd[nextNode]) {
                nextNode = n;
                path.push_back(n);
                break;
            }
        }
    }

    return path;
}

int findCenter(std::vector<int> graph[], int N) {
    int endpt1 = findFarthestNode(graph, 0, N);
    int endpt2 = findFarthestNode(graph, endpt1, N);
    std::vector<int> path = findPath(graph, endpt1, endpt2, N);

    return path[path.size() / 2];
}

// Returns diameter of tree with N nodes
int findDiameter(std::vector<int> graph[], int N) {
    int endpoint = findFarthestNode(graph, 0, N); 

    bool visited[N];
    for (int i = 0; i < N; i++) { visited[i] = false; }
    return findFarthestNodeDistance(graph, endpoint, visited);
}

int main() {
    const int N = 9;

    std::vector<int> graph[N];
    graph[0].push_back(1); graph[1].push_back(0);
    graph[0].push_back(2); graph[2].push_back(0);
    graph[0].push_back(7); graph[7].push_back(0);
    
    graph[2].push_back(3); graph[3].push_back(2);
    graph[3].push_back(4); graph[4].push_back(3);
    graph[5].push_back(6); graph[6].push_back(5);
    graph[5].push_back(7); graph[7].push_back(5);
    graph[7].push_back(8); graph[8].push_back(7);
    
    std::cout << "Max Dist: " << findDiameter(graph, N) << std::endl;
    std::cout << "Center: " << findCenter(graph, N) << std::endl;

    return 0;
}