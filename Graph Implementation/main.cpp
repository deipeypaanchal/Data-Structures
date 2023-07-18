// Author: Deipey Paanchal
// Graph Implementation

#include <iostream>
#include <vector>
#include "header.h" // Including the header file
using namespace std;

// Main function
int main()
{
    std::string filename;
    std::cout << "Enter the file name (include '.txt'):" << std::endl;
    std::cin >> filename;
    Graph<std::string, double> graph(filename); // Creating object

    // Check if the graph is not empty
    bool quit = false;
    if (!graph.empty()) 
    {
        while (!quit)
        {
            int choice = 0;
            std::cout << "----------------------------" << std::endl
                      << " What would you like to do ? " << std::endl
                      << "----------------------------" << std::endl;
            std::cout << "1. Find edges incident on a vertex" << std::endl
                      << "2. Find a path in the graph" << std::endl
                      << "3. Insert an edge" << std::endl
                      << "4. Erase a vertex" << std::endl
                      << "5. Quit" << std::endl;
            std::cin >> choice;

            std::string vertex1;
            std::string vertex2;
            std::string edgestring;

            switch (choice)
            {
            case 1: // Use edges function to get all edges and then find all edges with vertex connected to it and then print start and end and weight
                std::cout << "Enter a vertex label: ";
                std::cin.ignore(); 
                std::getline(std::cin, vertex1); // Get the vertex label from the user
                graph.listEdgesIncident(vertex1); // List all edges incident on the given vertex
                break;
            case 2: // Find a path
                std::cout << "Enter a starting vertex:"; // Get the starting vertex from the user
                std::cin.ignore();
                std::getline(std::cin, vertex1);
                std::cout << "Enter a ending vertex:"; // Get the ending vertex from the user
                std::getline(std::cin, vertex2);
                graph.findPath(vertex1, vertex2); // Find a path between the two vertices
                break;
            case 3: // Insert an edge using userInsertEdge
                std::cout << "Enter a starting vertex:";
                std::cin.ignore();
                std::getline(std::cin, vertex1); // Get the starting vertex from the user
                std::cout << "Enter a ending vertex:";
                std::getline(std::cin, vertex2); // Get the ending vertex from the user
                std::cout << "Enter a weight for the edge:"; // Prompting for weight

                std::getline(std::cin, edgestring); // Get the weight of the edge from the user 
                graph.userInsertEdge(vertex1, vertex2, edgestring); // Insert the edge into the graph
                break;
            case 4: // Remove vertex using eraseVertex
                std::cout << "Enter the Id of a vertex you wish to remove:" << endl;
                std::cin.ignore();
                std::getline(std::cin, vertex1); // Get the vertex to remove from the user
                graph.eraseVertex(vertex1); // Remove the vertex and all its incident edges from the graph

                break;
            case 5:
                quit = true; // Quit to exit the loop
                break;
            }
        }
    }

    return 0;
}