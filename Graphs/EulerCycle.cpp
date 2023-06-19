/*
Find Euler path in a graph
*/

#include <iostream>
#include <vector>
#include <utility>
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

int main() {
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

    for (int v : fleurys(g)) {
        std::cout << v << std::endl;
    }

    return 0;
}