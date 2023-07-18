/*
>> Author: Deipey Paanchal
>> This program is designed to keep track of music instruments sales using a singly linked list at a music shop.
>> It uses a linked list as well as two classes called "Node" and "Instrument" in order to store and manage information. 
>> This is a C++ program that implements a linked list of a custom class "Instrument" using a template class "Node". 
>> The linked list class "LinkedList" provides functions to add, remove, and print the instruments in the list. 
>> The linked list is implemented using pointers to the nodes, with the "head" and "tail" pointers keeping track of the beginning and end of the list, respectively. 
>> The linked list is constructed with both the head and tail pointers initialized to NULL, and nodes are added to the end of the list using the "add" function.
>> The "remove" function finds and removes a node with specific data from the list
>> The "printList" function prints all the elements in the list. 
>> Input validation is done to make sure the user is entering the expected data type values.
*/

#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Template class definition for a node in a linked list
template <typename T>
class Node
{
public:
    T data;        // Data stored in the node
    Node<T> *next; // Pointer to the next node in the list
    
    // Constructor for creating a new node
    Node(T data)
    {
        this->data = data;
        next = NULL;
    }
};

template <typename T>
class LinkedList
{
private:
    Node<T> *head;
    Node<T> *tail;

public:
    // This is the constructor of the class which initializes the head and tail pointers to NULL
    LinkedList()
    {
        head = tail = NULL;
    }
    
    // This function is to add the instruments from the Linked List
    void add()
    {
        string type, brand, customerName, dateSold;
        double price;
        cout << "Enter the type of instrument: ";
        cin >> type;
        cout << "Enter the brand of instrument: ";
        cin >> brand;
        // Loop is used to make sure the user is inserting the expected data type value
        while (true)
        {
            cout << "Enter the price of instrument in $: ";
            cin >> price;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "INVALID INPUT.\n";
            }
            else
            {
                break;
            }
        }
        cout << "Enter the name initials of Customer (Example: If the name is John Doe, Enter JD): ";
        cin >> customerName;
        cout << "Enter the date sold in format (mm/dd/yyyy): ";
        cin >> dateSold;

        T data = T(type, brand, price, customerName, dateSold);

        Node<T> *temp = new Node<T>(data);

        // When the linked list is empty
        if (head == NULL) 
        {
            head = tail = temp;
        }
        // Adding new nodes at the end of linked list
        else
        {
            tail->next = temp;
            tail = temp;
        }
    }

    // This function is to remove the instruments from the Linked List
    void remove()
    {
        string type, brand, customerName, dateSold;
        double price;
        // Prompting user for the details of intrument to be removed
        cout << "Enter the type of instrument to be removed: ";
        cin >> type;
        cout << "Enter the brand of instrument to be removed: ";
        cin >> brand;
        // Loop is used to make sure the user is inserting the expected data type value
        while (true)
        {
            cout << "Enter the price of instrument in $: ";
            cin >> price;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "INVALID INPUT.\n";
            }
            else
            {
                break;
            }
        }
        cout << "Enter the name initials of Customer (Example: If the name is John Doe, Enter JD): ";
        cin >> customerName;
        cout << "Enter the date sold in format (mm/dd/yyyy): ";
        cin >> dateSold;

        T data = T(type, brand, price, customerName, dateSold);

        Node<T> *temp = head;
        Node<T> *prev = NULL;
        // While loop is used to traverse through the linkedlist
        while (temp != NULL && (temp->data.type != data.type || temp->data.brand != data.brand || temp->data.price != data.price || temp->data.customerName != data.customerName || temp->data.dateSold != data.dateSold))
        {
            prev = temp;
            temp = temp->next;
        }
        // Throwing error message if it does not exist in the linked list
        if (temp == NULL)
        {
            cout << "DATA NOT FOUND." << endl;
            return;
        }
        // When node to be removed is the head of linked list
        if (prev == NULL)
        {
            head = temp->next;
            delete temp;
        }
        else
        {
            prev->next = temp->next;
            delete temp;
        }
        cout << "REMOVED SUCCESSFULLY." << endl;
    }

    // This function prints the list of instruments for the user
    void printList()
    {
        Node<T> *temp = head;
        while (temp != NULL)
        {
            // This line of code must be used with overloading
            // cout << temp->data << endl;
            
            // This line of code must be used with getters and setters
            cout << temp->data.type << " " << temp->data.brand << " " << temp->data.price << " " << temp->data.customerName << " " << temp->data.dateSold << endl;
            temp = temp->next;
        }
    }
};

class Instrument
{
private:
    // Five private member variables
    string type, brand, customerName, dateSold;
    double price;

public:
    // The default constructor initializes the class with default values
    Instrument() {}
    
    // This constructor initializes the class with the values provided as arguments and sets them to the corresponding member variables
    Instrument(string type, string brand, double price, string customerName, string dateSold)
    {
        this->type = type;
        this->brand = brand;
        this->price = price;
        this->customerName = customerName;
        this->dateSold = dateSold;
    }

    // Getters
    string getType() const { return type; }
    string getBrand() const { return brand; }
    double getPrice() const { return price; }
    string getCustomerName() const { return customerName; }
    string getDateSold() const { return dateSold; }

    // Setters
    void setType(string type) { this->type = type; }
    void setBrand(string brand) { this->brand = brand; }
    void setPrice(double price) { this->price = price; }
    void setCustomerName(string customerName) { this->customerName = customerName; }
    void setDateSold(string dateSold) { this->dateSold = dateSold; }
    
    // Assigning a friend class so that it can access the private elements
    friend class LinkedList<Instrument>;

    // Overloading is an alternative option to remove getters and setters
    // In our project we have used getters and setters as it is comparatively more secured 
    // friend ostream &operator<<(ostream &os, const Instrument &instrument)
    // {
    //     os << instrument.type << " " << instrument.brand << " " << instrument.price << " " << instrument.customerName << " " << instrument.dateSold;
    //     return os;
    // }
};

int main(void)
{
    LinkedList<Instrument> list;

    int code;
    cout << "\nWelcome to Music Shop Sales List...\n";
    cout << "This program can perform following features:\n";
    cout << "1. Add an instrument\n2. Remove an instrument\n3. Print list of instruments\n4. Quit\n\n";

    // For loop is used to keep prompting user until they decides to quit the program
    for(;;)
    {
        cout << "1. ADD 2. REMOVE 3. PRINT 4. QUIT\nPlease enter your operation choice(1-4): ";
        cin >> code;
        // Verfying if the input is valid
        // User is expected to enter an int value. Code might not behave properly if a string is used for an int input.
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        // Switch case is used for performing the results based on the user input
        switch (code)
        {
        case 1:
            cout << "\n******************** ADD INSTRUMENT ********************\n";
            list.add();
            break;
        case 2:
            cout << "\n******************** REMOVE INSTRUMENT ********************\n";
            list.remove();
            break;
        case 3:
            cout << "\n******************** LIST OF INSTRUMENTS ********************\n";
            list.printList();
            break;
        case 4:
            cout << "\nBye!\n";
            return 0;
        default:
            cout << "Invalid code! Please try again.\n";
        }
        cout << "\n";
    }

    return 0;
}
