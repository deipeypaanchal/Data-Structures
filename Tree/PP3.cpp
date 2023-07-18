// Authors: Group25 (Brett and Deipey)
// This program is designed to implement a general tree to create decision trees using a linked structure
// Reading data from the file to create the decision tree
// Taking user input and printing the details of the prompted node

#include <iostream>
#include <vector>
#include <stdexcept>
#include "PP3Header.h"
using namespace std;

int safe_stoi(const string &str)
{
    try
    {
        return stoi(str);
    }
    catch (const invalid_argument &e)
    {
        cerr << " "
                  << " ";
    }
    catch (const out_of_range &e)
    {
        cerr << " "
                  << " ";
    }
    catch (...)
    {
        cerr << "Unknown exception occurred\n";
    }
    return 0;
}

// The function takes two TreeNode pointers, one for the parent node and one for the child node.
template <typename T1, typename T2>
void LinkedTree<T1, T2>::addChild(TreeNode<T1, T2> *parent, TreeNode<T1, T2> *child)
{
    child->parent = parent;
    if (parent != NULL)
    {
        parent->children.push_back(child);
    }
    else
    {
        root = child;
    }
}

// To count the number of internal nodes in the tree
template <typename T1, typename T2>
int LinkedTree<T1, T2>::countInternalNodes()
{
    return countInternalNodes(root);
}
template <typename T1, typename T2>
int LinkedTree<T1, T2>::countInternalNodes(TreeNode<T1, T2> *node)
{
    if (node == NULL)
    {
        return 0;
    }
    int count = 0;
    if (!node->children.empty() || node == root)
    {
        count++; // count this node as an internal node
    }
    for (TreeNode<T1, T2> *child : node->children)
    {
        count += countInternalNodes(child);
    }
    return count;
}

// To count the number of external nodes in the tree
template <typename T1, typename T2>
int LinkedTree<T1, T2>::countExternalNodes()
{
    return countExternalNodes(root);
}

template <typename T1, typename T2>
int LinkedTree<T1, T2>::countExternalNodes(TreeNode<T1, T2> *node)
{
    if (node == NULL)
    {
        return 0;
    }
    if (node->children.empty())
    {
        if (node != root)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    int count = 0;
    for (TreeNode<T1, T2> *child : node->children)
    {
        count += countExternalNodes(child);
    }
    return count;
}

// This function calculates the height of the tree
template <typename T1, typename T2>
int LinkedTree<T1, T2>::height(TreeNode<T1, T2> *node)
{
    if (node == NULL)
    {
        return -1;
    }
    int maxChildHeight = -1;
    for (TreeNode<T1, T2> *child : node->children)
    {
        int childHeight = height(child);
        if (childHeight > maxChildHeight)
        {
            maxChildHeight = childHeight;
        }
    }
    return maxChildHeight + 1;
}

// This function calculates the height of the tree and returns it.
template <typename T1, typename T2>
int LinkedTree<T1, T2>::height()
{
    if (root == NULL)
    {
        return -1;
    }
    else
    {
        return height(root);
    }
}

// This function returns the contents of the root node.
template <typename T1, typename T2>
T2 LinkedTree<T1, T2>::getRootData()
{
    if (root != NULL)
    {
        return root->contents;
    }
    else
    {
        throw invalid_argument("The tree is empty");
    }
}

// This function prints the contents of all internal nodes in the tree.
template <typename T1, typename T2>
void LinkedTree<T1, T2>::printInternalNodesData()
{
    printInternalNodesData(root);
}

// This is a recursive helper function for printInternalNodesData that prints the contents of internal nodes starting from a given node.
template <typename T1, typename T2>
void LinkedTree<T1, T2>::printInternalNodesData(TreeNode<T1, T2> *node)
{
    if (node == NULL)
    {
        return;
    }
    if (!node->children.empty() || node == root)
    {
        cout << node->contents << endl; // print contents of internal node
    }
    for (TreeNode<T1, T2> *child : node->children)
    {
        printInternalNodesData(child);
    }
}

// This function recursively prints the contents of all external nodes of the tree
template <typename T1, typename T2>
void LinkedTree<T1, T2>::printExternalNodesData(TreeNode<T1, T2> *node) const
{
    if (node == NULL)
    {
        return;
    }
    if (node->children.empty())
    {
        cout << node->contents << endl; // print contents of internal node
    }
    for (TreeNode<T1, T2> *child : node->children)
    {
        printExternalNodesData(child);
    }
}

// This function prints the contents of all external nodes of the tree by calling the recursive function on the root node
template <typename T1, typename T2>
void LinkedTree<T1, T2>::printExternalNodesData() const
{
    printExternalNodesData(root);
}

// This function recursively determines whether the tree rooted at the given node is a binary tree
template <typename T1, typename T2>
bool LinkedTree<T1, T2>::isBinary(TreeNode<T1, T2> *node)
{

    if (node == NULL)
    {
        return true;
    }
    if (node->children.size() > 2)
    {
        return false;
    }
    for (TreeNode<T1, T2> *child : node->children)
    {
        if (!isBinary(child))
        {
            return false;
        }
    }
    return true;
}

// This function checks whether the entire tree is a binary tree by calling the recursive function on the root node
template <typename T1, typename T2>
bool LinkedTree<T1, T2>::isBinary()
{
    return isBinary(root);
}

// This function checks whether the subtree rooted at "node" is perfect (has exactly 2^(height+1)-1 nodes)
template <typename T1, typename T2>
bool LinkedTree<T1, T2>::isPerfect(TreeNode<T1, T2> *node)
{
    if (node == NULL)
    {
        return true;
    }

    int height = this->height();
    int nodeCount = this->countInternalNodes() + this->countExternalNodes();
    double expectedNodeCount = pow(2, height + 1) - 1;

    return nodeCount == expectedNodeCount;
}

// This function checks whether the entire tree is perfect by calling isPerfect() on the root node
template <typename T1, typename T2>
bool LinkedTree<T1, T2>::isPerfect()
{
    if (root == NULL)
    {
        return true;
    }

    return isPerfect(root);
}

// This function checks whether the subtree rooted at "node" is proper (each internal node has exactly 2 children)
template <typename T1, typename T2>
bool LinkedTree<T1, T2>::isProper(TreeNode<T1, T2> *node)
{
    if (node == NULL)
    {
        return true;
    }
    if (!node->children.empty() && node->children.size() != 2)
    {
        return false; // if internal node has less than or more than 2 children, tree is not proper
    }
    for (TreeNode<T1, T2> *child : node->children)
    {
        if (!isProper(child))
        {
            return false; // if any child is not proper, then the whole tree is not proper
        }
    }
    return true; // tree is proper
}

// This function checks whether the entire tree is proper by calling isProper() on the root node
template <typename T1, typename T2>
bool LinkedTree<T1, T2>::isProper()
{
    if (root == NULL)
    {
        return true;
    }
    return isProper(root);
}

// This function checks whether the subtree rooted at "node" is balanced (the heights of the left and right subtrees differ by at most 1)
template <typename T1, typename T2>
bool LinkedTree<T1, T2>::isBalanced(TreeNode<T1, T2> *node)
{
    if (node == NULL)
    {
        return true;
    }
    int leftHeight = (node->children.size() > 0) ? height(node->children[0]) : -1;
    int rightHeight = (node->children.size() > 1) ? height(node->children[1]) : -1;
    bool leftBalanced = (node->children.size() > 0) ? isBalanced(node->children[0]) : true;
    bool rightBalanced = (node->children.size() > 1) ? isBalanced(node->children[1]) : true;
    return abs(leftHeight - rightHeight) <= 1 && leftBalanced && rightBalanced;
}

// This function searches for a given node in the tree and returns a pointer to that node
// It starts from the currentNode and recursively checks all the child nodes until it finds the desired node or reaches a leaf
// If the node is found, it returns a pointer to that node. Otherwise, it returns NULL
template <typename T1, typename T2>
bool LinkedTree<T1, T2>::isBalanced()
{
    return isBalanced(root);
}

template <typename T1, typename T2>
TreeNode<int, string> *LinkedTree<T1, T2>::findNode(TreeNode<T1, T2> *currentNode, const T1 &searchData) const
{
    if (currentNode == NULL)
    {
        return NULL;
    }
    if (currentNode->order == searchData)
    {
        return currentNode;
    }
    for (TreeNode<T1, T2> *child : currentNode->children)
    {
        TreeNode<T1, T2> *foundNode = findNode(child, searchData);
        if (foundNode != NULL)
        {
            return foundNode;
        }
    }
    return NULL;
}

// This function allows the user to explore a tree by entering a node position
// It asks the user to enter a position number or the word "exit"
// If the position is valid, it displays the contents of the node, its ancestors(parent), descendants(child), and siblings
// If the position is invalid, it displays an error message
template <typename T1, typename T2>
void LinkedTree<T1, T2>::explore(LinkedTree<int, string> &tree)
{
    while (true)
    {
        cout << "Which node would you like to explore (enter a position as a number of 'exit' to quit): ";
        string input;
        cin >> input;

        if (input == "exit")
        {
            cout << "Goodbye!\n";
            break;
        }

        int num = safe_stoi(input);
        TreeNode<int, string> *node = findNode(tree.root, num);
        if (node == NULL)
        {
            cout << "Invalid input. Please try again.\n" << endl;
            continue;
        }

        cout << "Node Contents: " << node->contents << endl;

        cout << "Ancestor: ";
        if (node->parent == NULL)
        {
            cout << "None" << endl;
        }
        else
        {
            cout << root->contents << endl;
        }

        //cout << "\n";
        if (node->children.empty())
        {
            cout << "Descentants: None" << endl;
        }
        else
        {
            for (TreeNode<int, string> *child : node->children)
            {
                cout << "Descendants: "<<child->contents << "\n";
            }
            //cout << endl;
        }

        //cout << "\n";
        if (node->parent == NULL)
        {
            cout << "Siblings: None\n" << endl;
        }
        else
        {
            for (TreeNode<int, string> *sibling : node->parent->children)
            {
                if (sibling != node)
                {
                    cout << "Siblings: " << sibling->contents << "\n";
                }
            }
            cout << endl;
        }
    }
}

// A recursive function to explore the tree starting from the root
template <typename T1, typename T2>
void LinkedTree<T1, T2>::explore()
{
    if (root == NULL)
    {
        cout << "Nothing is in the tree" << endl;
        return;
    }
    else
    {
        return explore(root);
    }
}

// A recursive function to print the tree in a structured way
template <typename T1, typename T2>
void LinkedTree<T1, T2>::printTree(TreeNode<T1, T2> *node, int depth) const
{
    if (node == NULL)
    {
        return;
    }

    for (int i = 0; i < depth; i++)
    {
        cout << "--";
    }

    if (node == root)
    {
        cout << node->edge << node->contents << endl;
    }
    else
    {
        cout << "[" << node->edge << "] " << node->contents << endl;
    }

    for (TreeNode<T1, T2> *child : node->children)
    {
        printTree(child, depth + 1);
    }
}

// A function to print the entire tree, starting from the root
template <typename T1, typename T2>
void LinkedTree<T1, T2>::printTree() const
{
    printTree(root, 0);
}

// This function reads in a file containing information about a tree structure and returns a LinkedTree object
// The file should have lines in the format: level \t order \t edgeLabel \t nodeLabel
// The function first creates a vector of TreeNode objects using the information from the file
// Then, it sorts the vector based on the preorder index of the nodes
// Finally, it constructs the tree by iterating through the vector and adding each node to its parent
// The root node is added to the tree separately
LinkedTree<int, string> readTreeFromFile(string filename)
{

    LinkedTree<int, string> myTree;
    vector<TreeNode<int, string> *> myNodes;
    vector<TreeNode<int, string> *>::iterator iter, end;

    int level, order;
    string edge, contents;

    ifstream myfile;
    myfile.open(filename);
    string line;

    if (!myfile.is_open())
    {
        cout << "Error opening file" << endl;
        return myTree;
    }
    while (getline(myfile, line))
    {
        istringstream ss(line);
        string substr;

        while (getline(ss, substr, '\t'))
        {

            level = safe_stoi(substr);
            getline(ss, substr, '\t');
            order = safe_stoi(substr);
            getline(ss, substr, '\t');
            edge = substr;
            getline(ss, substr, '\t');
            contents = substr;
            TreeNode<int, string> *newNode = new TreeNode<int, string>(level, order, edge, contents);
            myNodes.push_back(newNode);
        }
    }

    // sort nodes in ascending order of their preorder index
    bool sorted = false;
    while (!sorted)
    {
        sorted = true;
        for (int i = 1; i < myNodes.size(); i++)
        {
            if (myNodes[i]->order < myNodes[i - 1]->order)
            {
                swap(myNodes[i], myNodes[i - 1]);
                sorted = false;
            }
        }
    }

    for (iter = myNodes.begin(), end = myNodes.end(); iter != end; iter++)
    {
        if ((*iter)->level == 0)
        {
            myTree.root = *iter;
            myTree.addChild(NULL, *iter);
            continue;
        }

        // find the parent node with level one above
        auto parentIter = iter;
        do
        {
            parentIter--;
        } while (parentIter != myNodes.begin() && (*parentIter)->level != (*iter)->level - 1);
        TreeNode<int, string> *parentNode = *parentIter;

        myTree.addChild(parentNode, *iter);
    }

    myfile.close();
    return myTree;
}

// The main function of the program
int main()
{
    // Create a new LinkedTree object and initialize it with data from a file
    LinkedTree<int, string> myTree;
    myTree = readTreeFromFile("tree-car.txt");

    // print out some information about the tree
    myTree.printTree();

    cout << endl
              << "--------------------" << endl
              << "Tree Properties" << endl
              << "--------------------" << endl;

    cout << "Root: " << myTree.getRootData() << endl;
    cout << "Number of internal nodes: " << myTree.countInternalNodes() << endl;
    cout << "Number of external nodes: " << myTree.countExternalNodes() << endl;
    cout << "Tree Height: " << myTree.height() << endl
              << endl;

    cout << "Internal nodes:" << endl;
    myTree.printInternalNodesData();
    cout << endl
              << "External nodes:" << endl;
    myTree.printExternalNodesData();

    cout << endl
              << "--------------------" << endl
              << "Binary Tree Properties" << endl
              << "--------------------" << endl
              << endl;
    
    // Check if the tree is binary and print out the results
    if (myTree.isBinary())
    {
        cout << "The tree is binary" << endl;
        if (myTree.isPerfect())
        {
            cout << "The tree is perfect" << endl;
        }
        else
        {
            cout << "The tree is not perfect" << endl;
        }
        if (myTree.isProper())
        {
            cout << "The tree is proper" << endl;
        }
        else
        {
            cout << "The tree is not proper" << endl;
        }
        if (myTree.isBalanced())
        {
            cout << "The tree is balanced" << endl;
        }
        else
        {
            cout << "The tree is not balanced" << endl;
        }
    }
    else
    {
        cout << "Binary Tree: No" << endl;
    }
    
    // Explore the tree by displaying information about a node and its ancestors, descendants, and siblings
    myTree.explore(myTree);
    
    return 0;
}
