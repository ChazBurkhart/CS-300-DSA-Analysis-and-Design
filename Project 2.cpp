//============================================================================
// Name        : LinkedList.cpp
// Author      : Chaz Burkhart
// Version     : 1.0
// Description : Project 2
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>
#include <iomanip>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================


// define a structure to hold course information
struct Course {
    string courseId; // unique identifier
    string title;
    string prereq1;
    string prereq2;

};

//============================================================================
// Linked-List class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a linked-list.
 */
class LinkedList {

private:
    //Internal structure for list entries, housekeeping variables
    struct Node {
        Course course;
        Node *next;

        // default constructor
        Node() {
            next = nullptr;
        }

        // initialize with a course
        Node(Course aCourse) {
            course = aCourse;
            next = nullptr;
        }
    };

    Node* head;
    Node* tail;
    int size = 0;

public:
    LinkedList();
    virtual ~LinkedList();
    void Append(Course course);
    void Prepend(Course course);
    void PrintList();
    void SortList();
    Course Search(string courseId);
    int Size();
};


/**
 * Default constructor
 */
LinkedList::LinkedList() {
    //set head and tail equal to null

	head = nullptr;
	tail = nullptr;

}

/**
 * Destructor
 */
LinkedList::~LinkedList() {
    // start at the head
    Node* current = head;
    Node* temp;

    // loop over each node, detach from list then delete
    while (current != nullptr) {
        temp = current; // hang on to current node
        current = current->next; // make current the next node
        delete temp; // delete the orphan node
    }
}

/**
 * Append a new course to the end of the list
 */
void LinkedList::Append(Course course) {
    //Create new node
    //if there is nothing at the head...
            // new node becomes the head and the tail
    //else
        // make current tail node point to the new node
        // and tail becomes the new node
    //increase size count

	Node* newNode = new Node;		//create a new node
	newNode ->course = course;
	newNode ->next = nullptr;

	if (head == nullptr) {			//If the list is null new node is now both head and tail
		head = newNode;
		tail = newNode;
	}
	else {
		tail->next = newNode;		//Tail points to new node
		tail = newNode;				//new node is tail
	}

	++size;
	return;
}


/**
 * Simple output of all courses in the list
 *
 */
void LinkedList::PrintList() {
    // start at the head

    // while loop over each node looking for a match
        //output current courseId and title
        //set current equal to next

	// Sort the courses by courseId using a for loop

	Node* temp = head;

	cout << "Here is a sample schedule:" << endl << endl;

	while(temp != nullptr){								// While not null, print course courseId and title
		cout << temp->course.courseId << "  | ";
		cout << setw(35) << left << temp->course.title << endl;
		temp = temp->next;								//Move to next node
		}
	return;

}


/**
 * Simple sort of all courses in the list
 *
 */
void LinkedList::SortList() {

		Node* cur1 = head;
		Node* cur2 = head->next;
		Node* temp = new Node;						//Create temp node
		temp ->course.courseId = "";				//Create empty node/course

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < (size - 1); j++){
				if(cur1->course.courseId < cur2->course.courseId) {		// If check the course ID and swap if smaller
					temp->course = cur1->course;
					cur1->course = cur2->course;
					cur2->course = temp->course;
				}
				cur2 = cur2->next;										// Cycle to next node

			}
			cur2 = head;
			cur1 = head->next;
			for (int k = 0; k < i; k++)
				cur1 = cur1->next;
		}
		return;
}

/**
 * Search for the specified courseId
 *
 * @param courseId The course ID to search for
 */
Course LinkedList::Search(string courseId) {
    // special case if matching node is the head
        // make head point to the next node in the list
        //decrease size count
        //return

    // start at the head of the list

    // keep searching until end reached with while loop (next != nullptr)
        // if the current node matches, return it
        // else current node is equal to next node

     //return course

	Node* temp = head;
	Node* place = new Node;							//Create temp node
	place ->course.courseId = "";					//Create empty node/course

	while (temp != nullptr){						//While the current node isn't null
		if (temp->course.courseId == courseId){		//If course is found return course
			return temp->course;
		}
		temp = temp->next;							//If not found move to next node
	}
	return place->course;	//If all nodes were searched and course not found return empty course
}


int LinkedList::Size() {
    return size;
}


//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the course information
 *
 * @param course struct containing the course info
 */
void displayCourse(Course course) {
    cout << course.courseId << ", " << course.title << endl;	// Print Course ID and Title
    cout << "Prerequisites: ";									// Print prerequisites
    	if (course.prereq1.length() > 2) {						// If the prerequisite 1 exists
    		cout << course.prereq1;								// Print prerequisite 1
    		if (course.prereq2.length() > 2) {					// If the prerequisite 2 exists
    			cout << ", " << course.prereq2;					// Print prerequisite 2
			}
    	}
    	else {													// If no prerequisite exists
    		cout << "None";										// Print none
    	}
    	cout << endl;
    return;
}



/**
 * Load a CSV file containing courses into a LinkedList
 *
 * @return a LinkedList containing all the courses read
 */
void loadCourses(string csvPath, LinkedList *list) {

    // initialize the CSV Parser
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // initialize a course using data from current row (i)
        	Course course;
            course.courseId = file[i][0];
            course.title = file[i][1];
            course.prereq1 = file[i][2];
            course.prereq2 = file[i][3];

            // add this course to the end
            list->Append(course);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
    cout << endl;
}



/**
 * The one and only main() method
 *
 * @param arg[1] path to CSV file to load from (optional)
 * @param arg[2] the course Id to use when searching the list (optional)
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, courseKey;
    csvPath = "ABCU.csv";

    LinkedList courseList;

    Course course;

    int choice = 0;
    while (choice != 4) {
        cout << "Welcome to the course planner." << endl << endl;
        cout << "  1. Load Data Structure." << endl;
        cout << "  2. Print Course List." << endl;
        cout << "  3. Print Course." << endl;
        cout << "  4. Exit" << endl << endl;
        cout << "What would you like to do? ";
        cin >> choice;



		switch (choice) {
			case 1: 		// Load CSV file
				cout << "Loading CSV file " << csvPath << endl;
				loadCourses(csvPath, &courseList);

				break;


			case 2:			// Run Sort Function then Run Print List Function
				courseList.SortList();
				courseList.PrintList();
				cout << endl;

				break;

			case 3:			// Search for Course, then display course information
				cout << "What course do you want to know about? ";
				cin >> courseKey;

				course = courseList.Search(courseKey);

				if (!course.courseId.empty()) {			// If course ID is not empty, display course information
					displayCourse(course);
					cout << endl;
				}
				else {			// If course not found or doesn't match
					cout << "Course Id " << courseKey << " not found.";
					cout << " Please make sure the course ID is capitalized." << endl;
				}

				break;

			case 4:				// Exit Program
				break;


			default:			// Not one of the cases
				cout << choice << " is not a valid option."<< endl << endl;

        }


	}

	cout << "Thank you for using the course planner!" << endl;

	return 0;
}

