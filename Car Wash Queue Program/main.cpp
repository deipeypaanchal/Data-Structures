/*
>> Author: Deipey Paanchal

>> This program is designed for a Car Wash Shop that implements a queue using templated circularly linked list.
>> Multiple classes and inheritance has been used. 
*/

#include <iostream>
#include <string>
#include "header.h"
using namespace std;

    // Constructor to initialize vehicle make, model, and license
    Vehicle::Vehicle(string m0, string m1, string l)
    {
        make = m0;
        model = m1;
        license = l;
    }

    // Virtual method to wash the vehicle
    void Vehicle::wash()
    {
        std::cout << "Washing Vehicle\n";
    }

    // Getters
    string Vehicle::getMake() const { return make; }
    string Vehicle::getModel() const { return model; }
    string Vehicle::getLicense() const { return license; }

    // Setters
    void Vehicle::setMake(string m) { make = m; }
    void Vehicle::setModel(string m) { model = m; }
    void Vehicle::setLicense(string l) { license = l; }



    // Constructor
    Car::Car(string m0, string m1, string l) : Vehicle(m0, m1, l) {}

    // Method to wash the car
    void Car::wash()
    {
        cout << "\nWashing Car (" << make << ", " << model << ", " << license << ")...\n\nCAR WASHED SUCCESSFULLY\n";
    }



    Truck::Truck(string m0, string m1, string l) : Vehicle(m0, m1, l) {}

    // Method to wash the truck
    void Truck::wash()
    {
        cout << "\nWashing Truck (" << make << ", " << model << ", " << license << ")...\n\nTRUCK WASHED SUCCESSFULLY\n";
    }


// Class for nodes in a circularly linked list
template <class T>
    Node<T>::Node(T value)
    {
        data = value;
        next = NULL;
    }


// Class for a circularly linked list queue
template <class T>


    Queue<T>::Queue()
    {
        head = NULL;
        tail = NULL;
        size = 0;
    }

    // Insert a new item at the end of the queue
    template <class T>
    void Queue<T>::enqueue(T value)
    {
        Node<T>* newNode = new Node<T>(value);
        if (head == NULL)
        {
            head = newNode; // if the queue is empty, set the head and tail to the new node
            tail = newNode;
            tail->next = head; // set the next of the tail to the head to make the list circular
        }
        else
        {
            tail->next = newNode; // if the queue is not empty, add the new node to the tail
            tail = newNode;       // set the tail to the new node
            tail->next = head;    // set the next of the tail to the head to make the list circular
        }
        size++; // increment the size of the queue
    }

    // Remove and return the first item in the queue
    template <class T>
    T Queue<T>::dequeue()
    {
        if (head == NULL)
        {
            throw "\nQUEUE IS EMPTY!!!"; // if the queue is empty, throw an exception
        }
        T value = head->data; // get the data of the head
        if (head == tail)     // if there is only one item in the queue
        {
            head = NULL; // set the head and tail to NULL
            tail = NULL;
        }
        else
        {
            head = head->next; // set the head to the next item
            tail->next = head; // set the next of the tail to the head to make the list circular
        }
        size--;       // decrement the size of the queue
        return value; // return the data of the head
    }

    // Check if the queue is empty
    template <class T>
    bool Queue<T>::isEmpty()
    {
        return (head == NULL); // return true if the head is NULL, false otherwise
    }

    // Return the number of items in the queue
    template <class T>
    int Queue<T>::getSize()
    {
        return size; // return the size of the queue
    }

    // Return the first item in the queue without removing it
    template <class T>
    T Queue<T>::peek()
    {
        if (head == NULL)
        {
            throw "\nQUEUE IS EMPTY!!!"; // if the queue is empty, throw an exception
        }
        return head->data; // return the data of the head
    }

    // Function to print the items in the queue
    template <class T>
    void Queue<T>::printQueue()
    {
        // Check if the queue is empty
        if (head == NULL)
        {
            cout << "\nQUEUE IS EMPTY!!!\n";
        }
        else
        {
            // Start at the head node and initialize a counter
            Node<T>* current = head;
            int i = 1;

            // Traverse the circularly linked list
            do
            {
                // Print the index of the item
                cout << i << ". ";

                // Check if the item is a Car object
                Car* car = dynamic_cast<Car*>(current->data);
                if (car)
                {
                    // Print the make, model, and license of the Car object
                    cout << car->make << " " << car->model << " (" << car->license << ")";
                }
                else
                {
                    // Check if the item is a Truck object
                    Truck* truck = dynamic_cast<Truck*>(current->data);
                    if (truck)
                    {
                        // Print the make, model, and license of the Truck object
                        cout << truck->make << " " << truck->model << " (" << truck->license << ")";
                    }
                }

                // Move to the next node, increment the counter, and print a newline
                cout << endl;
                current = current->next;
                i++;

            } while (current != head); // Repeat until we reach the head node again
        }
    }


int main()
{
    // Create a Queue of Vehicle pointers
    Queue<Vehicle*> carWash;

    // Print welcome message and menu options
    cout << "\nWelcome to Car Wash Queue...\n\n";
    cout << "This program can perform following features:\n";
    cout << "1. Add a car to the queue\n";
    cout << "2. Add a truck to the queue\n";
    cout << "3. Print the vehicles in the queue\n";
    cout << "4. Wash the next vehicle in the queue\n";
    cout << "5. Quit\n";

    // Loop to continuously prompt the user for their choice of operation
    while (true)
    {
        cout << "\n1. ADD CAR 2. ADD TRUCK 3. PRINT 4. WASH 5. QUIT\nPlease enter your operation choice(1-5): ";
        int choice;
        cin >> choice;

        // Perform the appropriate action based on the user's choice
        if (choice == 1)
        {
            // Add a car to the queue
            string make, model, license;
            cout << "\nEnter make of car: ";
            cin >> make;
            cout << "Enter model of car: ";
            cin >> model;
            cout << "Enter license of car: ";
            cin >> license;
            carWash.enqueue(new Car(make, model, license));
            cout << "\nCAR ADDED SUCCESSFULLY IN THE QUEUE\n";
        }
        else if (choice == 2)
        {
            // Add a truck to the queue
            string make, model, license;
            cout << "\nEnter make of truck: ";
            cin >> make;
            cout << "Enter model of truck: ";
            cin >> model;
            cout << "Enter license of truck: ";
            cin >> license;
            carWash.enqueue(new Truck(make, model, license));
            cout << "\nTRUCK ADDED SUCCESSFULLY IN THE QUEUE\n";
        }
        else if (choice == 3)
        {
            // Print the vehicles in the queue
            cout << "\n==================== CURRENT QUEUE ====================\n";
            carWash.printQueue();
        }
        else if (choice == 4)
        {
            // Wash the next vehicle in the queue
            try
            {
                Vehicle* item = carWash.peek();
                item->wash();
                carWash.dequeue();
                delete item;
            }
            catch (const char* msg)
            {
                // Handle any errors that occur during washing
                cerr << msg << endl;
            }
        }
        else if (choice == 5)
        {
            // Quit the program
            cout << "\nBye!\n";
            break;
        }
        else
        {
            // Handle an invalid choice
            cout << "Invalid choice. Please enter a number between 1 and 5.\n";
        }
    }
    return 0;
}
