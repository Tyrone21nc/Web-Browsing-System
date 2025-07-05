#include <iostream>
#include <string>
using namespace std;
#include "Stack.cpp"

// To test just queue follow these instructions:
//   1. make stest
//   2. make stest2
// This tests some of the important functions in Stack.
// You should add additional tests to make sure everything in the class works.
// During grading, we will test all functions in the Stack class.

int main () {
  //Test 1 - Default Constructor, Push, and Display
  cout << "Test 1 - Default Constructor, Push, and Display Test" << endl;
  int test1 = 10;
  int test2 = 20;
  int test3 = 30;
  //Test Default Constructor
  Stack <int> *newLS1 = new Stack <int>();
  //Push 3 nodes into Stack
  newLS1->Push(test1);
  newLS1->Push(test2);
  newLS1->Push(test3);
  cout << "\033[32mI pushed 3 nodes\033[0m" << endl;
  cout << "After 3 Pushs size: " << newLS1->GetSize() << endl;
  newLS1->Display();

  cout << "End Test 1 - Constructor, Push, and Display Test" << endl << endl;
    
  //Test 2 - Copy Constructor and Assignment Operator
  cout << "Test 2 - Copy Constructor Running" << endl;
  //Test Copy constructor
  Stack <int> *newLS2 = new Stack <int>(*newLS1);
  newLS2->Display();
  
  cout << "size below should match. Location should not" << endl;
  cout << "Source size: " << newLS1->GetSize() << " and Copied size: "
       << newLS2->GetSize() << endl;
  cout << "Source location: " << &newLS1 << " and Copied location: " << &newLS2 << endl;
  cout << "End Test 2 - Copy Constructor" << endl << endl;
  cout << "\033[32mCopy Constructor complete\033[0m" << endl;
  
  //Test 3 - Overloaded Assignment Operator
  cout << "Test 3 - Overloaded Assignment Operator Running" << endl;
  //Create new Stack using constructor
  Stack <int> *newLS3 = new Stack <int>();
  //Update using overloaded assignment operator
  
  *newLS3 = *newLS1;
  
  newLS3->Display(); //Display contents of newLS3
  cout << "size below should match. Location should not" << endl;
  cout << "Source size: " << newLS1->GetSize() << " and Assigned size: " << newLS3->GetSize() << endl;
  cout << "Source location: " << &newLS1 << " and Assigned location: " << &newLS3 << endl;
  cout << "End Test 3 - Assignment" << endl << endl;
  cout << "\033[32mOverloaded Assignemnt Operator is compelte\033[0m" << endl;
  
  //Test 4 - Test Pop
  cout << "Test 4 - Pop" << endl;
  cout << "size before: " << newLS1->GetSize() << " ";
  newLS1->Pop();
  cout << "size after: " << newLS1->GetSize() << endl;
  cout << "End Test 4 - Pop" << endl << endl;
  cout << "\033[32mPopped Successfully\033[0m" << endl;
  
  //Test 5 - Test GetSize
  cout << "Test 5 - GetSize Running" << endl;
  //Test size()
  cout << "Outputting GetSize" << endl;
  cout << newLS2->GetSize() << endl;
  cout << "End Test 5 - GetSize" << endl << endl;
  cout << "\033[32mSize returned successfully\033[0m" << endl;

  //Test 6 - Test At
  cout << "Test 6 - Returning At" << endl; 
  // Test At()
  newLS2->Display();
  cout << "The value at location 3 is: " << newLS2->At(3) << endl << endl;
  cout << "\033[32mAt returned successfully\033[0m" << endl;

  //Test 7 - Test Remove Bottom
  cout << "Test 6 - Removing from the bottom" << endl; 
  newLS2->Display();
  newLS2->RemoveBottom();
  cout << "Removing from the bottom" << endl; 
  newLS2->Display();

  
  
  /*
  //Test 6 - Test Destructor
  cout << "Test 6 - Test Destructor" << endl;
  cout << "delete newLS1" << endl;
  cout << "\033[31mSTUFF\033[0m" << endl;
  delete newLS1;
  cout << "delete newLS2" << endl;
  delete newLS2;
  cout << "delete newLS3" << endl;
  delete newLS3;
  cout << "End Test 6 - Destructors" << endl;
  cout << "\033[33mDESTRUCTOR COMPLETE\033[0m" << endl;
  */
  
  return 0;
}
