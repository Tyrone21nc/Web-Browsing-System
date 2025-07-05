/*Title: Stack.cpp
  Author: Prof. Dixon
  Date: 11/14/2024
  Description: This class defines a templated stack using a linked list
*/
#include <iostream>
#include <stdexcept>
using namespace std;

//Templated node class used in templated linked list
template <class T>
class Node {
public:
  Node( const T& data ); //Constructor
  T& GetData(); //Gets data from node
  void SetData( const T& data ); //Sets data in node
  Node<T>* GetNext(); //Gets next pointer
  void SetNext( Node<T>* next ); //Sets next pointer
private:
  T m_data;
  Node<T>* m_next;
};

//Overloaded constructor for Node
template <class T>
Node<T>::Node( const T& data ) {
  m_data = data;
  m_next = NULL;
}

//Returns the data from a Node
template <class T>
T& Node<T>::GetData() {
  return m_data;
}


//Sets the data in a Node
template <class T>
void Node<T>::SetData(const T& data ) {
  m_data = data;
}

//Gets the pointer to the next Node
template <class T>
Node<T>* Node<T>::GetNext() {
  return m_next;
}

//Sets the next Node
template <class T>
void Node<T>::SetNext( Node<T>* next ) {
  m_next = next;
}

//**********Stack Class Declaration***********
template <typename T> //Indicates linked list is templated
class Stack {
public:
  // Name: Stack (Default constructor)
  // Description: Creates a new Stack object
  // Preconditions: None
  // Postconditions: Creates a new Stack object
  Stack();
  // Name: ~Stack
  // Description: Stack destructor - deallocates all nodes in linked list
  // Preconditions: None
  // Postconditions: All nodes are deleted. Size is 0. No memory leaks.
  ~Stack();
  // Name: Stack (Copy constructor)
  // Description: Creates a new Stack object based on existing stack
  // Preconditions: None
  // Postconditions: Creates a new Stack object from existing stack
  //                 in separate memory space
  Stack(const Stack& source);
  // Name: Stack<T>& operator= (Assignment operator)
  // Description: Makes two stacks identical based on source.
  // Preconditions: None
  // Postconditions: Two stacks with same number of nodes and same values
  //                 in each node in a separate memory space
  Stack<T>& operator=(const Stack& other);
  // Name: Push
  // Description: Adds a new node to the top of the stack
  // Preconditions: None
  // Postconditions: Adds a new node to the top of the stack
  void Push(const T& value);
  // Name: Pop
  // Description: If stack is empty, throw runtime_error("Stack is empty");
  //              Temporarily stores data from node at the top of the stack.
  //              Removes the node from the top of the stack. Returns the stored data.
  // Preconditions: Stack has at least one node
  // Postconditions: See description 
  T Pop();
  // Name: Peek
  // Description: If stack is empty, throw runtime_error("Stack is empty");
  //              Returns the stored data from top node.
  // Preconditions: Stack has at least one node
  // Postconditions: See description
  T Peek() const;
  // Name: At
  // Description: If stack is empty, throw runtime_error("Stack is empty")
  //              Returns stored data from number of the node passed to function.
  //              At(3) would return the data from the fourth node.
  // Preconditions: Stack has at least one node
  // Postconditions: Returns data from number of node starting at m_top
  T At(int num);
  // Name: IsEmpty
  // Description: Returns if the stack has any nodes.
  // Preconditions: Stack has at least one node
  // Postconditions: If stack has no nodes, returns true. Else false.
  bool IsEmpty() const;
  // Name: RemoveBottom
  // Description: If stack is empty, throw runtime_error("Stack is empty")
  //              Temporarily stores data from node at the bottom of the stack.
  //              Removes node from bottom of the stack. Returns the stored data.
  //              Similar to Pop but opposite end of stack
  // Preconditions: Stack has at least one node
  // Postconditions: Removes node from bottom of stack and returns data
  T RemoveBottom();
  // Name: Display
  // Description: If stack is empty, outputs that the stack is empty
  //              Otherwise, iterates through stack and displays data in each node
  // Preconditions: Stack has at least one node
  // Postconditions: Displays data from each node in stack
  void Display();
  // Name: GetSize
  // Description: Returns the number of nodes in the stack
  // Preconditions: None
  // Postconditions: Returns the number of nodes in the stack.
  size_t GetSize() const;  
private:
  Node<T>* m_top; //Top node in stack
  size_t m_size; //Number of nodes in stack
};

//*********************STACK FUNCTIONS IMPLEMENTED HERE******************

template <typename T>
Stack<T>::Stack(): m_top(nullptr), m_size(0) {}

template <typename T>
Stack<T>::~Stack(){
  Node<T> *cur = m_top;
  while(cur != nullptr){
    cur = m_top->GetNext();
    delete m_top;
    m_size--;
  }
  delete cur;
  m_top = nullptr;

}

template <typename T>
Stack<T>::Stack(const Stack& source){
  m_top = nullptr, m_size = 0;  // setting the current top to point to nullptr and the size curr size to be 0;
  if(source.m_top == nullptr){  // check if the first node isn't the last
    return;  // if yes then return nothing
  }
  // Give curr the value of the top of the stack in parameters
  // Give the top and bottom of the stack a value of nullptr bc we don't know they're value yet
  Node<T> *curr = source.m_top;
  Node<T> *newStack = nullptr;
  Node<T> *lastNodeOfNewStack = nullptr;
  while(curr != nullptr){
    // create a new node for the new Stack
    Node<T> *curNewNode = new Node<T>(curr->GetData());   // then give it the data of the parameter

    if(newStack == nullptr){  // if the new Stack is completely empty, meaning the Stack is empty, then set it equal to the source new stack 
      newStack = curNewNode;
    }
    else{
      lastNodeOfNewStack->SetNext(curNewNode);  // if lastNode is the only node in the stack, make the last node point a new node which is the value of the cur new node
    }
    lastNodeOfNewStack = curNewNode;

    curr = curr->GetNext();   // Iterate to the next node
    m_size++;   // increment value of size
  }
  m_top = newStack;
  if(m_size != source.m_size)  // if for some reason, the size isn't the same, make it the same
    m_size = source.m_size;
  
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack &other){
  if(this != &other){

    // we want to delete everything that was previously there
    // Node<T> *tempNode = m_top;
    // while(tempNode != nullptr){
    //     tempNode = m_top;
    //     m_top = m_top->GetNext();
    //     delete temp;
    //     m_size--;
    // }
    size_t tempSize = m_size;
    while(tempSize != 0){   // we can just pop
      Pop();
      tempSize--;
    }
    
    // Now we want to repopulate the new Stack
    Node<T> *tempNode = other.m_top;  
    m_top = nullptr;
    while(tempNode != nullptr){
      Push(tempNode->GetData());
      tempNode = tempNode->GetNext();
    }
    delete tempNode;
  }
  return *this;
}

template <typename T>
void Stack<T>::Push(const T& value){
  Node<T> *newNode = new Node<T>(value);  // creating a new node with the given user value
  newNode->SetNext(m_top);    // then make it point to m_top, because pancake
  m_top = newNode;  // then make it the new Node, because pancake
  m_size++;  // then increment
}

template <typename T>
T Stack<T>::Pop(){
  if(m_size <= 0){  // if the size is <= 0, then it is empty
    throw runtime_error("Stack is empty. Cannot Pop from empty Stack");
  }
  Node<T> *tempNode = m_top;  // create a new Node and give it the value of the top node
  T tempNodeData = tempNode->GetData();  // create a new variable of type T and give it the value of the tempNode
  m_top = m_top->GetNext();  // now make the top have the value of the next one on the stack
  m_size--;  // decrement the size of the Stack
  delete tempNode;
  return tempNodeData;  // return the data of the tempNode
}

template <typename T>
T Stack<T>::Peek() const {
  if(m_size <= 0){
    throw runtime_error("Stack is empty. Cannot Peek from empty Stack");
  }
  return m_top->GetData();
}

template <typename T>
T Stack<T>::At(int num){
  if(m_size <= 0){    // If stack is empty, then throw an out of range statement
    throw runtime_error("Stack is empty. Cannot get the At from an empty Stack");
  }
  size_t dupSize = m_size;
  Node<T> *temp = m_top;
  while(dupSize != unsigned(num)){    // check if the sizes are the same
    temp = temp->GetNext(); // if not, go to the next node
    dupSize--;              // and decrement the size
  }
  return temp->GetData();   // if ur at that size, return the data of the node at that number

}

template <typename T>
bool Stack<T>::IsEmpty() const{
  if(!m_top){   // if the value of m_top is nullptr, then it must be empty
    return true;  // so return true
  }
  return false;   // otherwise, m_top must have the value of a Node
}

template <typename T>
T Stack<T>::RemoveBottom(){
  if(IsEmpty()){
    throw runtime_error("Stack is empty. Cannot revome the bottom from an empty Stack");
  }
  /*
  if(m_top->GetNext() == nullptr){
    T data = m_top->GetData();
    delete m_top;
    m_top = nullptr;
    m_size--;
    return data;
  }
  Node<T> *curNode = m_top;
  while(curNode->GetNext() != nullptr && curNode->GetNext()->GetNext() != nullptr){
    curNode = curNode->GetNext();
  }
  Node<T> *bottomNode = curNode->GetNext();
  T bottomData = bottomNode->GetData();
  delete bottomNode;
  curNode->SetNext(nullptr);
  m_size--;
  return bottomData;
*/
  
  Node<T> *bottomOfStack = m_top;
  Node<T> *curNode = m_top;
  while (curNode->GetNext() != nullptr && curNode->GetNext()->GetNext() != nullptr){
    curNode = curNode->GetNext();
  }
  bottomOfStack = curNode->GetNext();
  T bottomData = bottomOfStack->GetData();
  delete bottomOfStack;
  m_size--;
  curNode->SetNext(nullptr);
  return bottomData;
  
}

template <typename T>
void Stack<T>::Display(){
  if(IsEmpty()){
    cout << "Stack is empty" << endl;
  }
  else{
    Node<T> *currNode = m_top;    
    while(currNode != nullptr){
      cout << currNode->GetData() << "  ";
      currNode = currNode->GetNext();
    }
    cout << endl;
  }
}

template <typename T>
size_t Stack<T>::GetSize() const{
  return m_size;
}

