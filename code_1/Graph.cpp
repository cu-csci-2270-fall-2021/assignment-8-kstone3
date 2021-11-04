#include "Graph.hpp"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;


void Graph::addVertex(string name){
    bool found = true;
    for(int i = 0; i<(int)vertices.size(); i++){
        if(vertices[i]->name == name){
            found = false;
            cout << name << " found." << endl;
            break;
        }
    }
    if(found){
        vertex* newVertex = new vertex();
        newVertex->name=name;
        vertices.push_back(newVertex);
    }
}

void Graph::addEdge(string v1, string v2){
    vertex* vx1 = new vertex();
    vertex* vx2 = new vertex();
    for(int i = 0; i<(int)vertices.size(); i++){
        if(vertices[i]->name == v1){
           vx1 = vertices[i];
        }
        if(vertices[i]->name == v2){
           vx2 = vertices[i];
        }
    }
    adjVertex e;
    e.v = vx2;
    (vx1->adj).push_back(e);
    adjVertex e1;
    e1.v = vx1;
    (vx2->adj).push_back(e1);    
}

void Graph::displayEdges(){
    for(int i = 0; i<(int)vertices.size(); i++){
        cout << vertices[i]->name << " --> ";
        for(int j = 0; j<(int)vertices[i]->adj.size(); j++){
            if((vertices[i]->adj[j].v->name != "") & (vertices[i]->adj[j].v->name != vertices[i]->name)){
                cout << vertices[i]->adj[j].v->name << " ";
            }
        }
        cout << endl;
    }
}

void Graph::breadthFirstTraverse(string sourceVertex){
    vertex* vStart = new vertex();
    for(int i = 0; i<(int)vertices.size(); i++){
        if(vertices[i]->name == sourceVertex){
            vStart = vertices[i];
        }
    }
    cout<< "Starting vertex (root): " << vStart->name << "-> ";
    vStart->visited = true;
    queue<vertex*> q;
    q.push(vStart);
    while(!q.empty()){
        vertex* n = q.front();
        q.pop();
        if(n->name != vStart->name){
            cout << n->name <<"("<< n->distance <<")"<< " ";
        }
        for(int i = 0; i<(int)n->adj.size(); i++){
            if((!n->adj[i].v->visited)){
                n->adj[i].v->visited = true;
                n->adj[i].v->distance = n->distance + 1;
                q.push(n->adj[i].v);
            }
        }
    }
    cout << endl << endl;
}

int Graph::getConnectedBuildings() {
    // vector<vertex*> v = getVertices();
    int num = 0;
    for(int i = 0; i<(int)vertices.size(); i++){
        if(!(vertices[i]->visited)){
            bfsHelper(vertices[i]->name);
            num++;
        }
    }
    return num;
}

void Graph::bfsHelper(string sourceVertex){
    vertex* vStart = new vertex();
    for(int i = 0; i<(int)vertices.size(); i++){
        if(vertices[i]->name == sourceVertex){
            vStart = vertices[i];
        }
    }
    vStart->visited = true;
    queue<vertex*> q;
    q.push(vStart);
    while(!q.empty()){
        vertex* n = q.front();
        q.pop();
        for(int i = 0; i<(int)n->adj.size(); i++){
            if((!n->adj[i].v->visited)){
                n->adj[i].v->visited = true;
                q.push(n->adj[i].v);
            }
        }
    }
}

