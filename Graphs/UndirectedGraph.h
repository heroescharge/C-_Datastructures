#ifndef UNDIRECTED_GRAPH_H_INCLUDED
#define UNDIRECTED_GRAPH_H_INCLUDED
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

class UndirectedGraph {
private:
    int N;
    std::vector<std::vector<int>> graph;

public:
    UndirectedGraph(int N) {
        this->N = N;
        for (int i = 0; i < N; i++) {
            this->graph.push_back(std::vector<int>());
        }
    }

    int vertexSize() {
        return N;
    }

    int edgeSize() {
        int total = 0;
        for (int i = 0; i < N; i++) {
            total += graph[i].size();
        }

        return total / 2;
    }

    void connect(int a, int b) {
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    // This is inefficient, but assume O(1) as we can simply use hash tables
    // (this is for testing/practice purposes anyways...)
    void disconnect(int a, int b) {
        graph[a].erase(std::find(graph[a].begin(), graph[a].end(), b));
        graph[b].erase(std::find(graph[b].begin(), graph[b].end(), a));
    }

    std::vector<int> edges(int v) {
        return graph[v];
    }

    bool isConnected(int a, int b) {
        bool visited[N];
        for (int i = 0; i < N; i++) { visited[i] = false; }
        
        std::queue<int> vertexQ;
        vertexQ.push(a);
        visited[a] = true;
        while (!vertexQ.empty()) {
            int currVertex = vertexQ.front();
            vertexQ.pop();

            for (int v : graph[currVertex]) {
                if (!visited[v]) {
                    vertexQ.push(v);
                    visited[v] = true;
                }
            }

            if (visited[b]) {
                return true;
            }
        }

        return false;
    }

    bool isBridge(int a, int b) {
        UndirectedGraph g = *this;
        g.disconnect(a, b);
        return !g.isConnected(a, b);
    }

    std::vector<std::vector<int>> adjacencyList() {
        return graph;
    }
};
#endif