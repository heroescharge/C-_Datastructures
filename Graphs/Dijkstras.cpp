#include "../Datastructures/IndexedPriorityQueue.cpp"
#include <cstring>

struct WeightedEdge {
    int from;
    int to;
    double weight;
};

std::vector<WeightedEdge> dijkstras(std::vector<std::vector<WeightedEdge>> adjList) {
    int numVertices = adjList.size();
    WeightedEdge source[numVertices];
    IndexedPQ<double> vertexPQ = IndexedPQ<double>(numVertices);

    vertexPQ.insert(0, 0);
    for (int i = 1; i < numVertices; i++) {
        vertexPQ.insert(i, std::numeric_limits<double>::infinity());
    }

    bool visited[numVertices];
    memset(visited, false, numVertices * sizeof(bool));

    while (!vertexPQ.isEmpty()) {
        int vertex = vertexPQ.peek();
        visited[vertex] = true;
        double distance = vertexPQ.getKey(vertex);
        vertexPQ.pop();

        for (WeightedEdge edge : adjList[vertex]) {
            if (visited[edge.to]) {
                continue;
            }
            double newDistance = distance + edge.weight;
            if (newDistance < vertexPQ.getKey(edge.to)) {
                vertexPQ.changeKey(edge.to, newDistance);
                source[edge.to] = edge;
            }
        }
    }

    std::vector<WeightedEdge> path = std::vector<WeightedEdge>();
    int currVertex = numVertices - 1;
    while (currVertex != 0) {
        WeightedEdge nextEdge = source[currVertex];
        path.push_back(nextEdge);
        currVertex = nextEdge.from;
    }

    return path;
}

std::vector<WeightedEdge> bellmanford(std::vector<std::vector<WeightedEdge>> adjList) {
    int numVertices = adjList.size();
    double distances[numVertices]; 
    distances[0] = 0;
    for (int i = 1; i < numVertices; i++) {
        distances[i] = std::numeric_limits<double>::infinity();
    }

    WeightedEdge source[numVertices];

    for (int it = 0; it < numVertices - 1; it++) {
        for (int i = 0; i < numVertices; i++) {
            for (WeightedEdge edge : adjList[i]) {
                double newDistance = distances[i] + edge.weight;
                if (newDistance < distances[edge.to]) {
                    distances[edge.to] = newDistance;
                    source[edge.to] = edge;
                }
            }
        }
    }
    
    std::vector<WeightedEdge> path = std::vector<WeightedEdge>();
    int currVertex = numVertices - 1;
    while (currVertex != 0) {
        WeightedEdge nextEdge = source[currVertex];
        path.push_back(nextEdge);
        currVertex = nextEdge.from;
    }

    return path;
}

int main() {
    std::vector<std::vector<WeightedEdge>> adjList = {
        {{0, 1, 7}, {0, 2, 12}},
        {{1, 2, 2}, {1, 3, 9}},
        {{2, 4, 10}},
        {{3, 5, 1}},
        {{4, 3, 4}, {4, 5, 5}},
        {}
    };

    for (WeightedEdge edge : dijkstras(adjList)) {
        std::cout << edge.from << " " << edge.to << " " << edge.weight << std::endl;
    }

    for (WeightedEdge edge : bellmanford(adjList)) {
        std::cout << edge.from << " " << edge.to << " " << edge.weight << std::endl;
    }
}