#include <iostream>
#include "NavigationEntry.h"

NavigationEntry::NavigationEntry(){
    m_url = "";
    m_timeStamp = 0;
}

NavigationEntry::NavigationEntry(const string &url, const int &timestamp){
    m_url = url;
    m_timeStamp = timestamp;
}

string NavigationEntry::GetURL() const{
    return m_url;
}

int NavigationEntry::GetTimeStamp() const{
    return m_timeStamp;
}

void NavigationEntry::SetURL(const string &url) {
    m_url = url;
}
void NavigationEntry::SetTimeStamp(const int &time) {
    m_timeStamp = time;
}

bool NavigationEntry::IsEmpty() const{
    return m_url == ""? true: false;    
}

// string NavigationEntry::DisplayTimeStamp(int64_t timestand){} // which is already done for you in the .h file

ostream &operator<<(ostream &out, NavigationEntry &E){
    out << "URL: " << E.GetURL() << "   Visited On: " << E.DisplayTimeStamp(E.GetTimeStamp());
    return out;
}
