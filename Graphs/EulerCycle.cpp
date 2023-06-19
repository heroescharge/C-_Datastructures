/*
Find Euler path in a graph
*/

#include <iostream>
#include <vector>
#include <utility>
#include <stack>
#include <algorithm>
#include "UndirectedGraph.h"


std::vector<int> fleurys(UndirectedGraph g) {
    std::vector<int> path;
    int currVertex = 0;
    path.push_back(currVertex);
    do {
        bool nonbridgeExists = false;
        int nextVertex;
        for (int v : g.edges(currVertex)) {
            if (!g.isBridge(currVertex, v)) {
                nonbridgeExists = true;
                nextVertex = v;
                break;
            }
        }
        if (!nonbridgeExists) {
            nextVertex = g.edges(currVertex)[0];
        }

        path.push_back(nextVertex);
        g.disconnect(currVertex, nextVertex);
        currVertex = nextVertex;
    }
    while (g.edgeSize() > 0);


    return path;
}


std::vector<int> hierholzers(std::vector<std::vector<int>> graph) {
    std::vector<int> path;
    std::stack<int> vertices;

    vertices.emplace(0);

    while (vertices.size() > 0) {
        int currVertex = vertices.top();
        if (graph[currVertex].size() > 0) {
            int nextVertex = graph[currVertex].back();
            graph[currVertex].pop_back();
            graph[nextVertex].erase(std::find(graph[nextVertex].begin(), graph[nextVertex].end(), currVertex)); // For Undir graphs

            vertices.emplace(nextVertex);
        }
        else {
            path.push_back(vertices.top());
            vertices.pop();
        }
    }

    return path;
}

int main() {
    // TEST 1
    UndirectedGraph g(12);
    g.connect(0, 1);
    g.connect(0, 2);
    g.connect(0, 7);
    
    g.connect(1, 2);
    g.connect(3, 4);
    g.connect(3, 7);

    g.connect(4, 6);
    g.connect(5, 6);
    g.connect(5, 7);
    g.connect(7, 8);
    g.connect(0,8);

    g.connect(9, 10);
    g.connect(10, 11);
    g.connect(9, 11);
    g.connect(6, 9);
    g.connect(6, 11);
    g.connect(8, 9);
    g.connect(8, 11);

    // TEST 2
    UndirectedGraph h(13);
    h.connect(0, 1);
    h.connect(0, 2);
    h.connect(1, 2);

    h.connect(2, 3);
    h.connect(2, 4);
    h.connect(3, 4);

    h.connect(4, 5);
    h.connect(5, 6);
    h.connect(6, 7);
    h.connect(7, 8);
    h.connect(8, 12);
    h.connect(12, 4);

    h.connect(8, 9);
    h.connect(9, 10);
    h.connect(10, 11);
    h.connect(8, 11);    

    std::cout << "FLEURYS:" << std::endl;
    for (int v : fleurys(h)) {
        std::cout << v << std::endl;
    }

    std::cout << std::endl;
    std::cout << "HIERHOLZERS:" << std::endl;
    for (int v : hierholzers(h.adjacencyList())) {
        std::cout << v << std::endl;
    }

    return 0;
}