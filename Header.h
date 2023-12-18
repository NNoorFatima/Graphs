#pragma once
#include "queue"
#include <iostream>
using namespace std;

class Graph 
{

    int vertices;
    bool** adjMatrix;

public:
    Graph(int ver)
    {
        vertices = ver;
        adjMatrix = new bool*[vertices];
        for (int i = 0; i < vertices;i++)
        {
            adjMatrix[i] = new bool[vertices];
            for (int j = 0; j < vertices; j++)
            {
                adjMatrix[i][j] = false;
            }
        }
    }
    int getNumVertices() const
    {
        return vertices;
    }
    bool isEdge(int i, int j)
    {
        return adjMatrix[i][j];
    }
    void addEdge(int i, int j) 
    {
        adjMatrix[i][j] = 1;
        adjMatrix[j][i] = 1;
    }
    void print() 
    {
        for (int i = 0; i < vertices; i++)
        {
            for (int j = 0; j < vertices; j++)
            {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    void addVertex() 
    {
        int n = 1+vertices;
        bool** n_mat = new bool* [n];
        for (int i = 0; i < n; i++)
        {
            n_mat[i] = new bool[n];
        }
        for (int i = 0; i < vertices;i++)
        {
            for (int j = 0; j < vertices; j++)
            {
                n_mat[i][j] = adjMatrix[i][j];
            }
            n_mat[i][vertices] = 0;
        }
        for (int j = 0; j < n; j++) 
        {
            n_mat[vertices][j] = 0;
        }
        for (int i = 0; i < vertices; i++)
            delete[] adjMatrix[i];
        
        delete[] adjMatrix;
        adjMatrix = n_mat;
        vertices = n;
    }
    ~Graph()
    {
        for (int i = 0; i < vertices;i++)
        {
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;
    }
};

class GraphNode
{
public:
    GraphNode* next;
    int data;
    GraphNode(int d) 
    {
        data = d;
        next = nullptr;
    }
};

class Graphh 
{
    GraphNode** graph;
    int vertices;
public:
    Graphh(int m)
    {
        vertices = m;
        graph = new GraphNode * [vertices];
        for (int i = 0; i < vertices; i++)
        {
            graph[i] = NULL;
        }
    }
    void insertEdge(int i, int j)
    {
        GraphNode* newNode = new GraphNode(j);
        newNode->next = graph[i];
        graph[i] = newNode;
        newNode = new GraphNode(i);
        newNode->next = graph[j];
        graph[j] = newNode;
    }
    void display() 
    {
        cout << "Adjacency List is :" << endl;
        for (int i = 0; i < vertices; i++)
        {
            GraphNode* current = graph[i];
            cout << "Vertex " << i << " : ";
            while (current != nullptr)
            {
                cout << current->data << " ";
                current = current->next;
            }
            cout << endl;
        }
    }
    ~Graphh() 
    {
        for (int i = 0; i < vertices;i++)
        {
            GraphNode* cur = graph[i];
            while (cur != nullptr) 
            {
                GraphNode* temp = cur;
                cur = cur->next;
                delete temp;
            }
        }
        delete[] graph;
    }
    int countCycles()
    {   
        int* visited = new int[vertices];
        int cycleCount = 0;
        for (int i = 0; i < vertices; i++)
            visited[i] = 0;
      
        for (int i = 0; i < vertices; i++)
        {
            if (visited[i]!=1)
            {
                int stack[1000]; 
                int Top = 0;
                stack[Top++] = i;
                while (Top > 0) 
                {
                    int current = stack[--Top];
                    if (visited[current]!=1) 
                    {
                        visited[current] = 1;
                        GraphNode* neighbor = graph[current];
                        while (neighbor != nullptr)
                        {
                            if (!visited[neighbor->data]) 
                            {
                                stack[Top++] = neighbor->data;
                            }
                            else
                            {
                                if (neighbor->data != current) 
                                    cycleCount++;
                            }
                            neighbor = neighbor->next;
                        }
                    }
                }
            }
        }
        delete[] visited;
        cycleCount /= 2;
        cycleCount--;
        return cycleCount;
    }
    void bfsTraversal(int m)
    {
        bool* visited = new bool[vertices];
        for (int i = 0; i < vertices; i++)
            visited[i] = 0;
        queue<int> queue;
        queue.push(m);
        visited[m] = 1;
        cout << "BFS Traversal starting from node " << m << ": ";
        while (queue.empty()!=1) 
        {
            int current = queue.front();
            queue.pop();
            cout << current << " ";
            GraphNode* neighbor = graph[current];
            while (neighbor != nullptr)
            {
                if (!visited[neighbor->data]) 
                {
                    queue.push(neighbor->data);
                    visited[neighbor->data] = true;
                }
                neighbor = neighbor->next;
            }
        }
        cout << endl;
        delete[] visited;
    }

};
