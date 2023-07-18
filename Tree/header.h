// Author: Deipey Paanchal

// This is a header guard. It prevents the header file from being included multiple times in the same program.
#ifndef HEADER_H
#define HEADER_H

// Standard library headers
#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <algorithm>

// Definition of the TreeNode class
template <typename T1, typename T2>
class TreeNode
{
public:
    // Member variables
    T1 level;
    T1 order;
    T2 edge;
    T2 contents;
    TreeNode<T1, T2> *parent;
    std::vector<TreeNode<T1, T2> *> children;
    
    // Constructor
    TreeNode(T1 _level, T1 _order, T2 _edge, T2 _contents)
    {
        contents = _contents;
        order = _order;
        level = _level;
        edge = _edge;
        parent = NULL;
        children = std::vector<TreeNode<T1, T2> *>();
    }
};

// Definition of the LinkedTree class
template <typename T1, typename T2>
class LinkedTree
{
public:
    // Member variable
    TreeNode<T1, T2> *root;
    
    // Constructor
    LinkedTree()
    {
        root = NULL;
    }
    
    // Method for adding a child to a parent node
    void addChild(TreeNode<T1, T2> *parent, TreeNode<T1, T2> *child);
    
    // Methods for counting internal and external nodes
    int countInternalNodes();
    int countInternalNodes(TreeNode<T1, T2> *node);
    int countExternalNodes();
    int countExternalNodes(TreeNode<T1, T2> *node);
    
    // Methods for computing height and getting the root data
    int height(TreeNode<T1, T2> *node);
    int height();
    T2 getRootData();
    
    // Methods for printing internal and external nodes' data
    void printInternalNodesData();
    void printInternalNodesData(TreeNode<T1, T2> *node);
    void printExternalNodesData() const;
    void printExternalNodesData(TreeNode<T1, T2> *node) const;
    
    // Methods for checking whether the tree is binary, perfect, proper, and balanced
    bool isBinary(TreeNode<T1, T2> *node);
    bool isBinary();
    bool isPerfect(TreeNode<T1, T2> *node);
    bool isPerfect();
    bool isProper(TreeNode<T1, T2> *node);
    bool isProper();
    bool isBalanced(TreeNode<T1, T2> *node);
    bool isBalanced();
    
    // Method for finding a node in the tree
    TreeNode<int, std::string> *findNode(TreeNode<T1, T2> *currentNode, const T1 &searchData) const;
    
    // Methods for exploring and printing the tree
    void explore(LinkedTree<int, std::string> &tree);
    void explore();
    void printTree(TreeNode<T1, T2> *node, int depth) const;
    void printTree() const;
};

// End of header guard
#endif
