/*****************************************
** File: Browser.cpp
** Project: CMSC 202 Project 5, Fall 2024
** Author: Romain Dzeinse
** Release Date: 11/15/2024
** Submission Date: 12/1/2024
** Section: 11
** E-mail: romaind1@gl.umbc.edu
**
******************************************/


#include "Browser.h"
#include "Stack"


Browser::Browser(string filename){
    m_fileName = filename;
    m_currentPage = nullptr;
}
Browser::~Browser(){
    if(m_currentPage != nullptr){
        delete m_currentPage;
        m_currentPage = nullptr;
    }
    while(m_forwardStack.GetSize() != 0)
        delete m_forwardStack.Pop();
    
    while(m_backStack.GetSize() != 0)
        delete m_backStack.Pop();
}

void Browser::StartBrowser(){
    LoadFile();
    cout << "Welcome ot the Browser History Simulator" << endl;
    cout << "Current Website:" << endl;

    if(m_currentPage != nullptr)        // checks to see if there is a curren page, if yes prints it
        cout << "\033[32m" << *m_currentPage << "\033[0m" << endl;     // give us the value of the current page
    cout << endl;
    Menu();     // calls main menu function and starts the fun part
}

void Browser::Menu(){
    int choice, userSteps = 1;
    do{
        cout << "What would you like to do? " << endl;
        cout << "1. Display Browser Histroy" << endl;
        cout << "2. Go Back" << endl;
        cout << "3. Go Forward" << endl;
        cout << "4. Visit Site" << endl;
        cout << "5. Exit" << endl;
        cout << ">>> ";
        cin >> choice;
        
        switch(choice){
            case 1:
                Display();
                break;
            case 2:
                Back(userSteps);
                break;
            case 3:
                Forward(userSteps);
                break;
            case 4:
                NewVisit();
                break;
        }
    } while(choice != 5);
    cout << "\033[31mEnding Browser History Simulator\033[0m" << endl;
}

void Browser::Visit(const string &url, int timestamp){  // Validate a new page that has been added
    NavigationEntry *newSite = new NavigationEntry(url, timestamp);     // dynamically allocate a new page and then pass it the values from the parameters
    if(m_currentPage != nullptr)    // if the current page is nullptr, then you already have a current page
        m_backStack.Push(m_currentPage);    // if it != nullptr, then you want to pusg the current page onto the backstack
    m_currentPage = newSite;    // then set the current page equal to the newSite
}

void Browser::NewVisit(){
    string url;
    cout << "Enter the URL of thre new site: " << endl;
    cin.ignore();
    cout << ">>> ";
    getline(cin, url);
    
    auto nowTime = chrono::system_clock::now();
    time_t nowTimeAsTimeT = chrono::system_clock::to_time_t(nowTime);
    int64_t timeStamp = static_cast<int64_t>(nowTimeAsTimeT);

    Visit(url, timeStamp);
    cout << "Current Website:" << endl;
    if(m_currentPage != nullptr)  // this is the same as setting it equal to nullptr
        cout << "\033[32m" << *m_currentPage << "\033[0m" << endl;
    cout << endl;
}



// ***********CHECK your FOR LOOP AGAIN**************
void Browser::Display(){
    cout << endl;
    cout << "\033[33m*****Back Stack*****\033[0m" << endl;
    if(m_backStack.IsEmpty()){
        cout << "\033[31mBack Stack is Empty\033[0m" << endl;
    }
    else{
        cout << "THE SIZE IS: " << m_backStack.GetSize() << endl;
        for(unsigned int i=0; i<=m_backStack.GetSize(); i++){
            cout << i+1 << ". \033[32m" << *m_backStack.At(i) << "\033[0m" << endl;
        }
    }
    cout << endl;
    cout << "\033[33m*****Forward Stack*****\033[0m" << endl;
    if(m_forwardStack.IsEmpty()){
        cout << "\033[31mForward Stack is Empty\033[0m" << endl;
    }
    else{
        for(unsigned int i=0; i<m_forwardStack.GetSize(); i++){
            cout << i+1 << ". \033[32m" << *m_forwardStack.At(i) << "\033[0m" << endl;
        }
    }
    cout << endl;
    cout << "\033[35m*****Current Website*****\033[0m" << endl;
    if(m_currentPage == nullptr){     // same as satting to nullptr
        cout << "\033[31mNo current Page\033[0m" << endl;
    }
    else{   // if there is a current page, display it
        cout << "\033[32m" << *m_currentPage << "\033[0m" << endl;
    }
    cout << endl;
}

NavigationEntry Browser::Back(int steps){
    if(m_backStack.GetSize() == 0){
        cout << "Current Website: " << endl;
        cout << "\033[32m" << *m_currentPage << "033[0m" << endl;
        return *m_currentPage; 
    }
    // move back specific number of steps, this is based on the varibale
    for(int i = 0; i<steps && m_backStack.GetSize() > 0; i++){
        m_forwardStack.Push(m_currentPage);     // add onto the forward stack
        m_currentPage = m_backStack.Pop();      // and remove from backstack and put on the current page
    }
    // display new current page
    cout << "Current Website: " << endl;
    if(m_currentPage != nullptr){
        cout << "\033[32m" << *m_currentPage << "\033[0m" << endl;
    }
    else{
        cout << "\033[31mNo current page\033[0m" << endl; 
    }
    cout << endl;

    return GetCurrentPage();  // return the current page we just changed
}

NavigationEntry Browser::Forward(int steps){
    if(m_forwardStack.GetSize() == 0){
        cout << "Current Website: " << endl;
        cout << "\033[32m" << *m_currentPage << "\033[0m" << endl;
        cout << endl;
        return GetCurrentPage(); 
    }
    // move back specific number of steps, this is based on the varibale
    for(int i = 0; i<(steps && m_forwardStack.GetSize() > 0); i++){
        m_backStack.Push(m_currentPage);     // add onto the back stack
        m_currentPage = m_forwardStack.Pop();      // and remove from forward stack and put in the current page
    }

    // display new current page
    cout << "Current Website: " << endl;
    if(m_currentPage != nullptr){
        cout << "\033[32m" << *m_currentPage << "033[0m" << endl;
    }
    else{
        cout << "\033[31mNo current page\033[0m" << endl; 
    }
    cout << endl;

    return GetCurrentPage();      // again, return the current page we just changed
}

NavigationEntry Browser::GetCurrentPage() const{
    return *m_currentPage;
}

void Browser::LoadFile(){
    ifstream inputFile;
    string siteUrl, tStamp;     // the site url and the time stamp

    inputFile.open(m_fileName);
    if(inputFile.is_open()){
        while(getline(inputFile, siteUrl, DELIMITER) && getline(inputFile, tStamp)){
            Visit(siteUrl, stoi(tStamp));
        }
        inputFile.close();
    }
}
