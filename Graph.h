#ifndef GRAPH_INCLUDED
#define GRAPH_INCLUDED
#include <vector>
#include <string>
#include <iostream>

struct vertex;

struct adjVertex{
    vertex *v;
    int weight;
};

struct vertex{
    std::string name;
    bool visited;
    std::vector<adjVertex> adj;
    int district;
    int distance;
    int distEst;
    vertex *previous;
};
struct user{
    vertex *start;
    vertex *currentLocation;
    vertex *destination;
    int totalDistance;
};
class Graph
{
public:
    Graph(int difficulty);
    ~Graph();
    void addEdge(std::string v1, std::string v2, int weight);
    void addVertex(std::string name);
    void displayEdges();
    void BFTraversal(std::string startingCity);
    void findDistricts();
    void findDistricts(std::string startingCity);
    void resetBFT();
    void findShortestPath(std::string start, std::string finish);
    void Dijkstra(std::string start, std::string finish);
    void aStar(std::string start, std::string finish);
    void turn();
    int pathLength(std::string start,std::string finish);
private:
    std::vector<vertex> vertices;
    int districts;
    user you;
};


#endif // GRAPH_INCLUDED
