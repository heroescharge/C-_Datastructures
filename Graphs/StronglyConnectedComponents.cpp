#include <iostream>
#include <vector>
#include <cstring>

std::vector<std::vector<int>> reverseEdges(std::vector<std::vector<int>> adjList) {
    int N = adjList.size();
    std::vector<std::vector<int>> reversedAdjList(N);
    for (int i = 0; i < N; i++) {
        for (int j : adjList[i]) {
            reversedAdjList[j].push_back(i);
        }
    }

    return reversedAdjList;
}

void dfsReversePost(int node, std::vector<std::vector<int>> adjList, std::vector<int> &reversePostOrder, bool visited[]) {
    visited[node] = true;

    for (int n : adjList[node]) {
        if (!visited[n]) {
            dfsReversePost(n, adjList, reversePostOrder, visited);
        }
    }

    reversePostOrder.push_back(node);
}

std::vector<int> computeReversePostOrder(std::vector<std::vector<int>> adjList) {
    int N = adjList.size();

    bool visited[N];
    memset(visited, false, N * sizeof(bool));

    std::vector<int> reversePostOrder;
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            dfsReversePost(i, adjList, reversePostOrder, visited);
        }
    }

    std::reverse(reversePostOrder.begin(), reversePostOrder.end());
    return reversePostOrder;
}

void dfsCount(int node, std::vector<std::vector<int>> adjList, bool visited[], int count, std::vector<int> &scc) {
    visited[node] = true;
    scc[node] = count;

    for (int n : adjList[node]) {
        if (!visited[n]) {
            dfsCount(n, adjList, visited, count, scc);
        }
    }
}

std::vector<int> computeSCC(std::vector<std::vector<int>> adjList) {
    int N = adjList.size();

    std::vector<int> reversePostOrder = computeReversePostOrder(reverseEdges(adjList));
    std::vector<int> scc(N);

    bool visited[N];
    memset(visited, false, N * sizeof(bool));

    int count = 0;
    for (int i : reversePostOrder) {
        if (!visited[i]) {
            dfsCount(i, adjList, visited, count, scc);
            count++;
        }
    }

    return scc;
}

int main() {
    std::vector<std::vector<int>> g(13);

    g[0].push_back(1);
    g[0].push_back(5);
    g[2].push_back(0);
    g[2].push_back(3);
    g[3].push_back(2);
    g[3].push_back(5);
    g[4].push_back(2);
    g[4].push_back(3);
    g[5].push_back(4);
    g[6].push_back(0);
    g[6].push_back(4);
    g[6].push_back(9);
    g[6].push_back(8);
    g[7].push_back(6);
    g[7].push_back(9);
    g[8].push_back(6);
    g[9].push_back(10);
    g[9].push_back(11);
    g[10].push_back(12);
    g[11].push_back(4);
    g[11].push_back(12);
    g[12].push_back(9);

    std::vector<int> scc = computeSCC(g);

    for (int i = 0; i < g.size(); i++) {
        std::cout << "Vertex " << i << ": " << scc[i] << std::endl;
    }

    return 0;
}