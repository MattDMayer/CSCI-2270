#include "Graph.hpp"
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

void Graph::addVertex(string name)
{
    vertex *newVertex = new vertex;
    newVertex->name=name;
    vertices.push_back(newVertex);
    return;
}

void Graph::addEdge(string v1, string v2)
{
	for (unsigned int i=0; i<vertices.size(); i++) {
		if (vertices[i]->name == v1) 
        {
			for (unsigned int j=0; j<vertices.size(); j++) 
            {
				if (vertices[j]->name == v2) 
                { 
					adjVertex adjv;
					adjv.v=vertices[j];
					vertices[i]->adj.push_back(adjv);
					adjVertex adjv2;
					adjv2.v=vertices[i];
					vertices[j]->adj.push_back(adjv2);
				}
			}
		}
	}
}

void Graph::displayEdges()
{
	for(int i=0;i<vertices.size();i++)
	{
		cout<<vertices[i]->name<<" --> ";
		for(int j=0;j<vertices[i]->adj.size();j++)
		{
			if(j<vertices[i]->adj.size()-1)
			{
				cout<<vertices[i]->adj[j].v->name<<" ";
			}
			else
			{
				cout<<vertices[i]->adj[j].v->name<<endl;
			}
		}
	}
}

void Graph::breadthFirstTraverse(string sourceVertexName)
{
	vertex *start;
	for(int i=0;i<vertices.size();i++)
	{
		if(vertices[i]->name==sourceVertexName)
		{
			start=vertices[i];
		}
	}
	start->visited=true;
	queue<vertex*> q;
	vertex *n;
	start->distance=0;
	int dist = 0;
	q.push(start);
	cout<<"Starting vertex (root): " <<start->name<<"-> ";
	while(q.empty()==false)
	{
		n=q.front();
		q.pop();
		for(int i=0;i<n->adj.size();i++)
		{
			if(n->adj[i].v->visited==false)
			{
				n->adj[i].v->visited=true;
				dist=n->distance+1;
				n->adj[i].v->distance=dist;
				cout<<n->adj[i].v->name<<"("<<n->adj[i].v->distance<<") ";
				q.push(n->adj[i].v);
			}
		}
	}
}

void componentsHelper(vertex* root)
{
	root->visited=true;
	for(int i=0;i<root->adj.size();i++)
	{
		if(root->adj[i].v->visited==false)
		{
			componentsHelper(root->adj[i].v);
		}
	}
}

int Graph::getConnectedBuildings()
{
	int components=0;
	for(int i=0;i<vertices.size();i++)
	{
		if(vertices[i]->visited==false)
		{
			components++;
			componentsHelper(vertices[i]);
		}
	}
	return components;
}