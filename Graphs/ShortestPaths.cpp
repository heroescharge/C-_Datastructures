#include <iostream>
#include <vector>
#include <utility>

struct Edge {
    // Directed edge from u to v with weight w
    int u;
    int v;
    int w;

    Edge(int u, int v, int w) {
        this->u = u;
        this->v = v;
        this->w = w;
    }

    bool operator>(const Edge other) const {
        return this->w > other.w;
    }
    bool operator<(const Edge other) const {
        return !(*this > other);
    }
    bool operator==(const Edge other) const {
        return this->w == other.w;
    }
    bool operator!=(const Edge other) const {
        return !(*this == other);
    }
};

std::pair<int, std::vector<Edge>> dijkstras(std::vector<std::vector<int>> adjList) {

}

int main() {
    std::vector<Edge> graph = std::vector<Edge> {
        Edge(4, 5, 35),
        Edge(4, 7, 37),
        Edge(5, 7, 28),
        Edge(0, 7, 16),
        Edge(1, 5, 32),
        Edge(0, 4, 38),
        Edge(2, 3, 17),
        Edge(1, 7, 19),
        Edge(0, 2, 26),
        Edge(1, 2, 36),
        Edge(1, 3, 29),
        Edge(2, 7, 34),
        Edge(6, 2, 40),
        Edge(3, 6, 52),
        Edge(6, 0, 58),
        Edge(6, 4, 93)
    };

    return 0;
}