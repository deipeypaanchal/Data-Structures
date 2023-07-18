// Header file for Vehicle, Car, Truck, Node and Queue classes
// Inheritance is used for Car and Truck. Both classes inherits from Vehicle class.

#ifndef HEADER_FILE_H
#define HEADER_FILE_H

#include <iostream>
#include <string>

using namespace std;

// Base class for Vehicles
class Vehicle
{
public:
	string make, model, license;

	// Constructor to initialize vehicle make, model, and license
	Vehicle(string m0, string m1, string l);

	// Virtual method to wash the vehicle
	virtual void wash();

	// Getters
	string getMake() const;
	string getModel() const;
	string getLicense() const;

	// Setters
	void setMake(string m);
	void setModel(string m);
	void setLicense(string l);
};

// Class for cars, which inherit from Vehicle
class Car : public Vehicle
{
public:
	// Constructor
	Car(string m0, string m1, string l);

	// Method to wash the car
	void wash();
};

class Truck : public Vehicle
{
public:
	// Constructor
	Truck(string m0, string m1, string l);

	// Method to wash the truck
	void wash();
};

// Class for nodes in a circularly linked list
template <typename T>
class Node
{
public:
	T data;
	Node<T> *next;
	Node<T>(T value);
};

// Class for a circularly linked list queue
template <typename T>
class Queue
{
private:
	Node<T> *head; // pointer to the head of the queue
	Node<T> *tail; // pointer to the tail of the queue
	int size;	   // number of items in the queue

public:
	Queue<T>();

	// Insert a new item at the end of the queue
	void enqueue(T value);

	// Remove and return the first item in the queue
	T dequeue();

	// Check if the queue is empty
	bool isEmpty();

	// Return the number of items in the queue
	int getSize();

	// Return the first item in the queue without removing it
	T peek();

	// Function to print the items in the queue
	void printQueue();
};

#endif
