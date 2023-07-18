// Author: Deipey Paanchal
// This is the header file for the main file

// Header guard to avoid multiple inclusion of the header
#ifndef HEADER_H
#define HEADER_H
using namespace std;

// Standard library headers
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <queue>

// Forward declaration of classes
template <typename T, typename E>
class Edge;
template <typename T, typename E>
// Vertex class declaration
class Vertex
{
public:
    T id;
    std::vector<Edge<T, E> *> edges;
    // Constructor
    Vertex(T id)
    {
        this->id = id;
    }
    // Get the vertex ID
    T &getId()
    {
        return this->id;
    }
    // Overloading the == operator to compare vertex objects
    bool operator==(const Vertex<T, E> &v) const
    {
        return this->id == v.id;
    }

    // Overloading the * operator to get the vertex ID
    T operator*()
    {
        return this->id;
    }

    // Function to print the incident edges of the vertex
    void incidentEdges()
    {
        for (Edge<T, E> *edge : edges)
        {
            std::cout << edge->start->id << " to " << edge->end->id << " is " << edge->weight << " mi" << std::endl;
        }
    }

    // Function to print the adjacent vertices of the vertex
    bool isAdjacentTo(Vertex<T, E> *v)
    {
        for (Edge<T, E> *edge : edges)
        {
            if (edge->start == v || edge->end == v)
            {
                return true;
            }
        }
        return false;
    }
};
// Edge class declaration
template <typename T, typename E>
class Edge
{
public:
    E weight;
    Vertex<T, E> *start;
    Vertex<T, E> *end;

    // Constructor
    Edge(E weight, Vertex<T, E> *start, Vertex<T, E> *end)
    {
        this->weight = weight;
        this->start = start;
        this->end = end;
    }

    // Return edge weight
    E operator*()
    {
        return this->weight;
    }
    E getWeight() const
    {
        return weight;
    }

    // Return the start and end vertices of the edge as a pair
    std::pair<Vertex<T, E> *, Vertex<T, E> *> endVertices()
    {
        return std::make_pair(start, end);
    }

    // Given one vertex of the edge, return the other vertex
    Vertex<T, E> *opposite(Vertex<T, E> *v)
    {
        if (v == start)
        {
            return end;
        }
        else if (v == end)
        {
            return start;
        }
        else
        {
            std::cout << "Error: vertex not incident on this edge" << std::endl;
            return NULL;
        }
    }

    // Check if the edge is adjacent to the given vertex
    bool isAdjacentTo(Vertex<T, E> *v)
    {
        return (v == start || v == end);
    }

    // Check if the edge is incident on the given vertex
    bool isIncidentOn(Vertex<T, E> *v)
    {
        return (v == start || v == end);
    }
};
// Graph class declaration
template <typename T, typename E>
class Graph
{
private:
    vector<Vertex<T, E> *> vertices;
    vector<pair<Vertex<T, E> *, Vertex<T, E> *>> vertexPairs;

public:
    Graph<T, E>(std::string file)
    {
        std::ifstream myfile(file);
        if (myfile.is_open())
        {

            // Read the first line to get the vertices
            std::string verticesLine;
            std::getline(myfile, verticesLine);
            std::istringstream verticesStream(verticesLine);

            T vertexId;

            while (std::getline(verticesStream >> std::ws, vertexId, ','))
            {
                // Inserting vertex
                insertVertex(vertexId);
            }

            // Read the rest of the lines to get the edges
            std::string line;
            while (std::getline(myfile, line))
            {
                std::istringstream edgeStream(line);
                T startId, endId;
                E weight;
                std::getline(edgeStream, startId, '\t');
                std::getline(edgeStream, endId, '\t');
                edgeStream >> weight;

                Vertex<T, E> *startVertex = NULL;
                Vertex<T, E> *endVertex = NULL;

                for (typename vector<Vertex<T, E> *>::iterator it = vertices.begin(); it != vertices.end(); ++it)
                {
                    if (startId == (*it)->getId())
                    {
                        startVertex = *it;
                    }

                    if (endId == (*it)->getId())
                    {
                        endVertex = *it;
                    }
                }
                // If starting vertex is NULL
                if (startVertex == NULL)
                {
                    startVertex = new Vertex<T, E>(startId);
                }
                // If end vertex is NULL
                if (endVertex == NULL)
                {
                    endVertex = new Vertex<T, E>(endId);
                }
                // Insert the edge
                insertEdge(startVertex, endVertex, weight);
            }
            // Thank you message
            std::cout << "Thank you. Your graph is ready." << std::endl;
            myfile.close(); // Closing file
        }
        else
        {
            std::cout << "Unable to open file" << std::endl; // If unable to open the file
        }
    }

    // Return a value for if the graph is empty
    bool empty()
    {
        return vertices.empty();
    }

    // Return a vector of all vertices in the graph
    vector<Vertex<T, E> *> getVertices()
    {
        return vertices;
    }

    // Return a vector of all edges in the graph
    vector<Edge<T, E> *> Edges()
    {
        vector<Edge<T, E> *> edges;
        for (Vertex<T, E> *vertex : vertices)
        {
            for (Edge<T, E> *edge : vertex->edges)
            {
                // Check if the edge has already been added to the vector
                bool found = false;
                for (Edge<T, E> *existingEdge : edges)
                {
                    if (*existingEdge == *edge)
                    {
                        found = true;
                        break;
                    }
                }
                // If the edge has not been added, add it to the vector
                if (!found)
                {
                    edges.push_back(edge);
                }
            }
        }
        return edges;
    }

    // Insert a new vertex with the given ID
    void insertVertex(T id)
    {
        bool found = false;
        for (typename vector<Vertex<T, E> *>::iterator it = vertices.begin(); it != vertices.end(); ++it)
        {
            if (id == (*it)->getId())
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            Vertex<T, E> *newVertex = new Vertex<T, E>(id);
            vertices.push_back(newVertex);
        }
    }

    // Insert a new edge with the given start and end vertices and weight
    void insertEdge(Vertex<T, E> *v1, Vertex<T, E> *v2, E weight)
    {
        Edge<T, E> *edge = new Edge<T, E>(weight, v1, v2);
        v1->edges.push_back(edge);
        v2->edges.push_back(edge);
        vertexPairs.push_back(std::make_pair(v1, v2));
    }

    // Function to erase vertex
    void eraseVertex(T id)
    {
        // Find the vertex with the given ID
        auto it = std::find_if(vertices.begin(), vertices.end(), [&](const Vertex<T, E> *v)
                               { return *v == id; });
        if (it == vertices.end())
        {
            std::cout << "Vertex not found" << std::endl;
            return;
        }
        Vertex<T, E> *vertex = *it;

        // Remove all edges incident on the vertex
        for (auto edge : vertex->edges)
        {
            Vertex<T, E> *oppositeVertex = edge->opposite(vertex);
            oppositeVertex->edges.erase(std::remove_if(
                                            oppositeVertex->edges.begin(), oppositeVertex->edges.end(),
                                            [&](const Edge<T, E> *e)
                                            { return e == edge; }),
                                        oppositeVertex->edges.end());
            delete edge;
        }
        vertex->edges.clear();

        // Remove the vertex from the vertices vector
        vertices.erase(it);
        delete vertex;
        std::cout << "Vertex removed" << std::endl;
    }

    // Function to erase edge
    void eraseEdge(Vertex<T, E> *v1, Vertex<T, E> *v2)
    {
        // Find the edge between v1 and v2
        Edge<T, E> *edgeToRemove = nullptr;
        for (Edge<T, E> *edge : v1->edges)
        {
            if (edge->isIncidentOn(v2))
            {
                edgeToRemove = edge;
                break;
            }
        }
        if (!edgeToRemove)
        {
            std::cout << "Edge not found" << std::endl;
            return;
        }

        // Remove the edge from both vertices
        v1->edges.erase(std::remove(v1->edges.begin(), v1->edges.end(), edgeToRemove), v1->edges.end());
        v2->edges.erase(std::remove(v2->edges.begin(), v2->edges.end(), edgeToRemove), v2->edges.end());

        // Delete the edge
        delete edgeToRemove;
    }

    // Function to list edge incident
    void listEdgesIncident(std::string label)
    {
        Vertex<T, E> *v1 = NULL;
        // Loop to iterate
        for (typename vector<Vertex<T, E> *>::iterator it = vertices.begin(); it != vertices.end(); ++it)
            if (label == (*it)->getId())
            {
                v1 = *it;
            }
        if (v1 == NULL)
        {
            std::cout << "Can't find that vertex" << std::endl;
            return;
        }
        (*v1).incidentEdges();
    }

    // Function to get the user input when they select to insert the edge
    void userInsertEdge(std::string v1, std::string v2, std::string edgestring)
    {

        Vertex<T, E> *start = NULL;
        for (typename vector<Vertex<T, E> *>::iterator it = vertices.begin(); it != vertices.end(); ++it)
            if (v1 == (*it)->getId())
            {
                start = *it;
            }
        if (start == NULL)
        {
            std::cout << "Can't find the first vertex" << std::endl;
            return;
        }
        Vertex<T, E> *end = NULL;
        for (typename vector<Vertex<T, E> *>::iterator it = vertices.begin(); it != vertices.end(); ++it)
            if (v2 == (*it)->getId())
            {
                end = *it;
            }
        if (end == NULL)
        {
            std::cout << "Can't find the second vertex" << std::endl;
            return;
        }

        double edgeWeight = std::stod(edgestring);
        if (start->isAdjacentTo(end))
        {
            for (typename vector<Edge<T, E> *>::iterator it = start->edges.begin(); it != start->edges.end(); ++it)
            {
                if ((*it)->getWeight() == edgeWeight)
                {
                    std::cout << "Error: edge already exist" << std::endl;
                    return;
                }
            }
        }
        // Insert the edge into graph
        insertEdge(start, end, edgeWeight);
        std::cout << "Edge inserted" << endl;
    }

    // Function to find the path
    void findPath(std::string v1, std::string v2)
    {
        Vertex<T, E> *start = NULL;
        for (typename vector<Vertex<T, E> *>::iterator it = vertices.begin(); it != vertices.end(); ++it)
            if (v1 == (*it)->getId())
            {
                start = *it;
                break;
            }
        if (start == NULL)
        {
            std::cout << "Can't find the first vertex" << std::endl;
            return;
        }
        Vertex<T, E> *end = NULL;
        for (typename vector<Vertex<T, E> *>::iterator it = vertices.begin(); it != vertices.end(); ++it)
            if (v2 == (*it)->getId())
            {
                end = *it;
                break;
            }
        if (end == NULL)
        {
            std::cout << "Can't find the second vertex" << std::endl;
            return;
        }

        // Check if start and end are adjacent
        for (typename vector<Edge<T, E> *>::iterator it = start->edges.begin(); it != start->edges.end(); ++it)
        {
            Vertex<T, E> *neighbor = (*it)->opposite(start);
            if (neighbor == end)
            {
                std::cout << "Vertices " << start->getId() << " and " << end->getId() << " are adjacent." << std::endl;
                return;
            }
        }
        unordered_map<Vertex<T, E> *, bool> visited;
        queue<Vertex<T, E> *> q;
        unordered_map<Vertex<T, E> *, Vertex<T, E> *> parent;
        q.push(start);
        visited[start] = true;
        parent[start] = NULL;
        // Loop till q is not empty
        while (!q.empty())
        {
            Vertex<T, E> *current = q.front();
            q.pop();
            if (current == end)
            {
                // Reconstruct the path from start to end
                vector<Vertex<T, E> *> path;
                Vertex<T, E> *v = end;
                while (v != NULL)
                {
                    path.push_back(v);
                    v = parent[v];
                }
                reverse(path.begin(), path.end());
                // Print the path
                for (typename vector<Vertex<T, E> *>::iterator it = path.begin(); it != path.end(); ++it)
                    if (it == --path.end())
                    {
                        std::cout << (*it)->getId();
                    }
                    else
                    {
                        std::cout << (*it)->getId() << " to ";
                    }
                std::cout << std::endl;
                return;
            }
            for (typename vector<Edge<T, E> *>::iterator it = current->edges.begin(); it != current->edges.end(); ++it)
            {
                Vertex<T, E> *neighbor = (*it)->opposite(current);
                if (!visited[neighbor])
                {
                    q.push(neighbor);
                    visited[neighbor] = true;
                    parent[neighbor] = current;
                }
            }
        }
        // If the end vertex was not found, there is no path from start to end
        std::cout << "No path found from " << start->getId() << " to " << end->getId() << std::endl;
    }
};

#endif