#include "user.h"
#include "user.cpp"
#include <iostream>

using namespace std;
int main() {
    
    vector<int> test; test.push_back(1);// = {1};
    //vector<int> test1;// = {1,2};
    //vector<int> test2;// = {1,2,3};
    
    //User(int num, std::string name, int year, int zip, std::vector<int> friends);
    User JS = User(0, "Jonathon Shen", 1997, 90007, test);
    //User SC = User(1, "Samantha Chang", 1997, 90089, test1);
    //User RB = User(2, "Ryan Bae", 1997, 69696,
    
    vector<int>* hi = JS.friends_ptr();
    cout << JS.get_name() << " " << JS.get_id() << " " << JS.get_yob() << " " << JS.get_zip() << hi->at(0) << endl;
}