
#include "Graph.h"
#include <vector>
#include <string>
#include <queue>
#include <math.h>
#include <stdlib.h>
using namespace std;
/**
    Function prototype:
    void Graph(int)

    Function description:
    Constructor for game
    Takes an int n and creates a random graph with n vertices.
    Gives user a start and destination

    Example:
    Graph g=Graph(16);

    Pre-conditions: input < number of sample cities and should be
    above ~9 for a reasonably sized board
    Post-conditions: Random Graph generated and user initialized
**/
Graph::Graph(int difficulty)
{
    srand(time(NULL));
    //String of city names
    string cities[]={"Boulder","Baltimore","Chicago","D","E","F","G","H","I","J","K","L","M","N","O","P"};
    //adds all cities to graph
    for(int i=0;i<difficulty;i++){
        addVertex(cities[i]);
        vertices[i].visited=false;
    }
    //Add random edges. Goal is number of edges = sqrt(number of cities)
    //for each vertex v...
    for(int i=0;i<vertices.size();i++){
        //if v hasn't been visited
        if(!vertices[i].visited){
            //cout<<vertices[i].name<<endl;
            //to fill all edges
            for(int j=vertices[i].adj.size();j<sqrt(vertices.size());j++){
                bool found=false;
                vertex temp;
                //gets random vertex until one qualifies
                while(!found){
                    temp=vertices[rand()%vertices.size()];
                    found=true;
                    for(int k=0;k<vertices[i].adj.size();k++){
                        if(vertices[i].adj[k].v->name==temp.name){
                            found=false;
                        }
                    }
                    if(temp.name==vertices[i].name||temp.adj.size()>sqrt(vertices.size())){
                        found=false;
                    }
                }
                //cout<<"-"<<temp.name<<endl;
                //add edges to both vertices
                int weight=rand()%100+100;
                addEdge(vertices[i].name,temp.name,weight);
                addEdge(temp.name,vertices[i].name,weight);
            }
            //v is visited
            vertices[i].visited=true;
        }
    }
    //random start
    you.start=&vertices[rand()%vertices.size()];
    you.currentLocation=you.start;
    you.destination=you.start;
    //random destination > 1 move away
    while(you.destination==you.start||pathLength(you.start->name,you.destination->name)<1){
        you.destination=&vertices[rand()%vertices.size()];
    }
    you.totalDistance=0;
}
Graph::~Graph(){

}
/**
    Function prototype:
    void addVertex(string)

    Function description:
    Takes a string s
    Adds a vertex with the name s to the graph

    Example:
    Graph g;
    g.addVertex("Boulder");

    Pre-conditions: name is a valid ascii string
    Post-conditions: New vertex appended to vertices

**/
void Graph::addVertex(string name){
    vertex newV;
    newV.name=name;
    newV.visited=false;
    newV.district=-1;
    vertices.push_back(newV);
}
/**
    Function prototype:
    void addEdge(string,string,int)

    Function description:
    Takes two vertex names and a weight.
    Adds the second vertex the the list of adjacent vertices of the first vertex

    Example:
    Graph g;
    g.addVertex("Boulder");
    g.addVertex("Chicago");
    g.addEdge("Boulder","Chicago",100);

    Pre-condition: vertices named already added
    Post-condition: the first vertex has a new adjacent vertex
**/
void Graph::addEdge(std::string v1, std::string v2, int weight){
    adjVertex newAdj;
    int startI;
    int endV;
    //parse vertices for indexes
    for(int i=0;i<vertices.size();i++){
        if(vertices[i].name==v1){
            startI=i;
        }else if(vertices[i].name==v2){
            endV=i;
        }
    }
    //add edge
    newAdj.v=&vertices[endV];
    newAdj.weight=weight;
    vertices[startI].adj.push_back(newAdj);
}
/**
    Function prototype:
    void displayEdges()

    Function description:
    displays all vertices and their adjacent vertices in the format:
    for all vertices:
        district:name-->adj1***adj2***adjN

    Example:
    Graph g;
    g.displayEdges();

    Pre-condition: None
    Post-condition: None
**/
void Graph::displayEdges(){
    for(int i=0;i<vertices.size();i++){
        cout<<vertices[i].district<<":"<<vertices[i].name<<"-->";
        for(int j=0;j<vertices[i].adj.size();j++){
            if(j>0){
                cout<<"***";
            }
            cout<<vertices[i].adj[j].v->name;
        }
        cout<<endl;
    }
}
void Graph::resetBFT(){
    for(int i=0;i<vertices.size();i++){
        vertices[i].visited=false;
    }
}
void Graph::findDistricts(){
    districts=0;
    resetBFT();
    findDistricts(vertices[0].name);
}
/**
    Function prototype:
    void findDistricts(string)

    Function description:
    Takes a name to start at, iterates districts, and assigns all connected cities the district.
    Calls itself until all vertices have a district

    Example:
    Graph g;
    g.addVertex("Austin");
    g.addVertex("Boulder");
    g.addVertex("Chicago");
    g.addEdge("Austin","Boulder",100);
    g.findDistricts(Austin);

    Pre-condtion: at least one vertex added, visited=false for all vertices
    Post-condition: districts assigned
**/
void Graph::findDistricts(std::string startingCity){
    districts++;
    queue<vertex*> bfq;
    vertex v;
    int i;
    //get start index
    for(i=0;i<vertices.size();i++){
        if(startingCity==vertices[i].name){
            break;
        }
    }
    vertices[i].visited=true;
    vertices[i].district=districts;

    //BFT to find all connected vertices
    bfq.push(&vertices[i]);
    //cout<<vertices[i].district<<endl;
    while(!bfq.empty()){
        v=*bfq.front();
        //cout<<"start "<<v.adj.size()<<endl;
        bfq.pop();
        //cout<<"start "<<v.adj.size()<<endl;
        for(i=0;i<v.adj.size();i++){
            if(v.adj[i].v->visited==false){
                v.adj[i].v->visited=true;
                //bfq.push(v.adj[i].v);
                string name=v.adj[i].v->name;
                //cout<<name<<endl;
                for(int j=0;j<vertices.size();j++){
                    if(vertices[j].name==name){
                        vertices[j].visited=true;
                        vertices[j].district=districts;
                        bfq.push(&vertices[j]);
                    }
                }
            }
        }
    }
    //call self again if any district not found
    for(i=0;i<vertices.size();i++){
        if(vertices[i].district==-1){
            //cout<<vertices[i].name<<endl;
            findDistricts(vertices[i].name);
            return;
        }else{
            //cout<<vertices[i].name<<endl;
        }
    }
}
struct queueVertex{
    int distance;
    vector<vertex> path;
};
/**
    Function prototype:
    void findShortestPath(string,string)

    Function description:
    taking the names of the start and destination, it finds and outputs the
    shortest path between the vertices, ignoring the weight of edges

    Example:
    Graph g;
    g.addVertex("A");
    g.addVertex("B");
    g.addEdge("A","B",2);
    g.findShortestPath("A","B");

    Pre-condition: Graph created
    names given are valid and in same district
    Post-condition: None
**/
void Graph::findShortestPath(std::string start, std::string finish){
    vector<vertex> path;
    int distance;
    queue<queueVertex> bfq;
    vertex null;
    null.name="";
    vertex startV=null;
    vertex endV=null;
    vertex v;
    int i = 0;
    //get start and destination vertices
    for(i=0; i<vertices.size();i++) {
        if (start==vertices[i].name) {
            startV = vertices[i];
        }else if(finish==vertices[i].name){
            endV =vertices[i];
        }
    }
    //special cases
    if(startV.name==null.name||endV.name==null.name){
        cout<< "One or more cities doesn't exist"<< endl;
        return;
    }
    if(startV.district!=endV.district){
        cout<< "No safe path between cities" <<endl;
        return;
    }
    if(startV.district==-1||endV.district==-1){
        cout<< "Please identify the districts before checking distances"<<endl;
        return;
    }
    //BFT
    resetBFT();
    startV.visited = true;
    queueVertex qv;
    qv.distance=0;
    qv.path.push_back(startV);
    bfq.push(qv);
    while (!bfq.empty()) {
        qv = bfq.front();
        bfq.pop();
        v=qv.path[qv.path.size()-1];
        for(i=0;i<v.adj.size();i++) {
            if (v.adj[i].v->visited==false) {
                path=qv.path;
                v.adj[i].v->visited = true;
                distance=qv.distance+1;
                path.push_back(*v.adj[i].v);
                queueVertex temp;
                temp.path=path;
                temp.distance=distance;
                if(v.adj[i].v->name==finish){
                    cout<<temp.distance;
                    for(int j=0;j<temp.path.size();j++){
                        cout<<","<<temp.path[j].name;
                    }
                    cout<<endl;
                    return;
                }else{
                    bfq.push(temp);
                }
            }
        }
    }

}
/**
    Function prototype:
    void Dijkstra(string,string)

    Function description:
    using Dijkstra's algorithm, outputs the shortest path between the vertices inputted

    Example:
    Graph g;
    g.addVertex("A");
    g.addVertex("B");
    g.addEdge("A","B",2);
    g.Dijkstra("A","B");

    Pre-condition: Graph created
    Post-condition: None
**/
void Graph::Dijkstra(std::string starting, std::string destination){
    //cout<<"test"<<endl;
    vertex *start;
    vertex *finish;
    vector<vertex*> solved;
    int minDistance;
    //get start and destination
    //set visited=false and distance to ~MAX_INT
    for(int i=0;i<vertices.size();i++){
        vertices[i].visited=false;
        vertices[i].distance=2147000000;
        vertices[i].previous=NULL;
        if(vertices[i].name==starting){
            start=&vertices[i];
        }
        if(vertices[i].name==destination){
            finish=&vertices[i];
        }
    }
    //special cases
    if(start==NULL||finish==NULL){
        cout<<"One or more cities doesn't exist"<<endl;
        return;
    }
    if(start->district!=finish->district){
        cout<<"No safe path between cities"<<endl;
        return;
    }
    if(start->district==-1){
        cout<<"Please identify the districts before checking distances"<<endl;
        return;
    }
    //Dijkstra's
    start->visited=true;
    start->distance=0;
    solved.push_back(start);
    while(!finish->visited){
        minDistance=2147000000;
        vertex *temp;
        vertex *temp2;
        for(int i=0;i<solved.size();i++){
            vertex *u=solved[i];
            for(int j=0;j<u->adj.size();j++){
                vertex *v=u->adj[j].v;
                int tempD=u->distance+u->adj[j].weight;
                //cout<<v->name<<" "<<tempD<<endl;
                if(!v->visited){
                    //v->visited=true;
                    if(tempD<minDistance){
                        temp=v;
                        temp2=u;
                        temp->distance=tempD;
                        minDistance=tempD;
                    }
                }
            }
        }
        //cout<<temp->name<<endl;
        temp->visited=true;
        //cout<<temp->name<<" "<<u->name<<endl;
        temp->previous=temp2;
        solved.push_back(temp);

    }
    //output path
    vertex *temp=finish;
    vector<vertex*> path;
    cout<<finish->distance;
    while(temp!=NULL){
        //cout<<temp->name<<endl;
        path.insert(path.begin(),temp);
        temp=temp->previous;
    }
    for(int i=0;i<path.size();i++){
        cout<<","<<path[i]->name;
    }
    cout<<endl;

}
/**
    Function prototype:
    void aStar(string,string)

    Function description:
    Using the A* algorithm, finds and outputs the shortest path between the vertices named
    Uses pathLength function for heuristic function

    Example:
    Graph g;
    g.addVertex("A");
    g.addVertex("B");
    g.addEdge("A","B",2);
    g.aStar("A","B");

    Pre-condition: Graph created
    names are valid and in the same grid
    Post-condition: None
**/
void Graph::aStar(std::string startName,std::string finishName){
    vector<vertex*> solved;
    vector<vertex*> toBeSolved;
    vector<vertex*> path;
    vertex *start;
    vertex *finish;
    vertex *temp=new vertex;
    for(int i=0;i<vertices.size();i++){
        if(vertices[i].name==startName){
            start=&vertices[i];
        }
        if(vertices[i].name==finishName){
            finish=&vertices[i];
        }
    }
    start->distance=0;
    start->distEst=start->distance+100*pathLength(start->name,finish->name);
    start->previous=NULL;
    toBeSolved.push_back(start);
    while(!toBeSolved.empty()){
        temp=toBeSolved[0];
        int tempI=0;
        //cout<<"toBeSolved:"<<endl;
        //cout<<temp->name<<endl;
        for(int i=1;i<toBeSolved.size();i++){
            //cout<<toBeSolved[i]->name<<endl;
            if(toBeSolved[i]->distEst<temp->distEst){
                temp=toBeSolved[i];
                tempI=i;
            }
        }
        //cout<<"temp:"<<endl;
        //cout<<temp->name<<endl;
        if(temp->name==finish->name){
            while(temp!=NULL){
                path.insert(path.begin(),temp);
                temp=temp->previous;
            }
            cout<<finish->distance;
            for(int i=0;i<path.size();i++){
                cout<<","<<path[i]->name;
            }
            cout<<endl;
            return;
        }
        toBeSolved.erase(toBeSolved.begin()+tempI);
        //cout<<"test"<<endl;
        solved.push_back(temp);
        for(int i=0;i<temp->adj.size();i++){
            adjVertex neighbor=temp->adj[i];
            //cout<<"neighbor:"<<endl;
            //cout<<neighbor.v->name<<endl;
            bool test=true;
            for(int j=0;j<solved.size();j++){
                if(neighbor.v->name==solved[j]->name){
                    //cout<<"solved"<<endl;
                    test=false;
                }
            }
            if(test){
                int tempDist=temp->distance+neighbor.weight;
                for(int j=0;j<toBeSolved.size();j++){
                    if(neighbor.v->name==toBeSolved[j]->name){
                        //cout<<"been added"<<endl;
                        test=false;
                    }
                }
                if(test||tempDist<neighbor.v->distance){
                    //cout<<"stuff gotta change"<<endl;
                    neighbor.v->previous=temp;
                    neighbor.v->distance=tempDist;
                    neighbor.v->distEst=neighbor.v->distance+100*pathLength(neighbor.v->name,finish->name);
                    if(test){
                        //cout<<"added to queue"<<endl;
                        toBeSolved.push_back(neighbor.v);
                    }
                }

            }
        }
    }
    return;
}
/**
    Function prototype:
    int pathLength(string,string)

    Function description:
    Using a BFT search, it returns the number of edges between the named vertices

    Example:
    Graph g;
    g.addVertex("A");
    g.addVertex("B");
    g.addEdge("A","B",2);
    int dist=g.pathLength("A","B");

    Pre-conditions: The names given are valid and in the same district
    Post-conditions: returns number of edges between vertices

**/
int Graph::pathLength(std::string start,std::string finish){
    vector<vertex> path;
    int distance=0;
    queue<queueVertex> bfq;
    vertex null;
    null.name="";
    vertex startV=null;
    vertex endV=null;
    vertex v;
    int i = 0;
    for(i=0; i<vertices.size();i++) {
            vertices[i].visited=false;
        if (start==vertices[i].name) {
            startV = vertices[i];
        }else if(finish==vertices[i].name){
            endV =vertices[i];
        }
    }
    resetBFT();
    startV.visited = true;
    queueVertex qv;
    qv.distance=0;
    qv.path.push_back(startV);
    bfq.push(qv);
    while (!bfq.empty()) {
        qv = bfq.front();
        bfq.pop();
        v=qv.path[qv.path.size()-1];
        for(i=0;i<v.adj.size();i++) {
            if (v.adj[i].v->visited==false) {
                path=qv.path;
                v.adj[i].v->visited = true;
                distance=qv.distance+1;
                path.push_back(*v.adj[i].v);
                queueVertex temp;
                temp.path=path;
                temp.distance=distance;
                if(v.adj[i].v->name==finish){
                    return temp.distance;
                }else{
                    bfq.push(temp);
                }
            }
        }
    }
}
/**
    Function prototype:
    void play()

    Function description:
    PLays the game taking user input and traversing through the graph.
    Once finished, displays other search algorithms

    Example:
    Graph g=Graph(16);
    g.play();

    Pre-conditions: Graph created with vertices and edges
    Districts found
    Post-conditions: None


**/
void Graph::play(){
    string input;
    cout<<"You are at: "<<you.currentLocation->name<<endl;
    cout<<"Your goal is: "<<you.destination->name<<endl;
    cout<<"Your adjacent locations are:"<<endl;
    for(int i=0;i<you.currentLocation->adj.size();i++){
        cout<<you.currentLocation->adj[i].v->name<<" - "<<you.currentLocation->adj[i].weight<<endl;
    }
    cout<<"Choose one:"<<endl;
    getline(cin,input);
    for(int i=0;i<you.currentLocation->adj.size();i++){
        if(you.currentLocation->adj[i].v->name==input){
            int weight=you.currentLocation->adj[i].weight;
            you.currentLocation=you.currentLocation->adj[i].v;
            you.totalDistance+=weight;
            break;
        }
    }
    if(you.currentLocation!=you.destination){
        play();
    }else{
        cout<<"You win!"<<endl;
        cout<<"Total distance: "<<you.totalDistance<<endl;
        cout<<"Paths with various algorithms:"<<endl;
        cout<<"Dijkstra's algorithm: "<<endl;
        Dijkstra(you.start->name,you.destination->name);
        cout<<"A* search algorithm: "<<endl;
        aStar(you.start->name,you.destination->name);
        cout<<"BFT search (ignores distance):"<<endl;
        findShortestPath(you.start->name,you.destination->name);
        cout<<"Graph:"<<endl;
        displayEdges();
    }


}
