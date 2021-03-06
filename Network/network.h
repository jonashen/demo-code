#ifndef NETWORK_H
#define NETWORK_H
#include <string>
#include <vector>
#include "user.h"

class Network {
 public:
    Network();
    //~Network();
    int read_friends(const char *filename);
    int write_friends(const char *filename);
    void add_user(std::string username, int yr, int zipcode);
    int add_connection(std::string name1, std::string name2);
    int remove_connection(std::string name1, std::string name2);
    int get_id(std::string username);
    std::vector<User>* network_ptr();
    
    // a shortest path starting at user from and ending
    // at user to. If no path exists, returns empty vector
    std::vector<int> shortest_path(int from, int to);
    
    // a list of the components of the network
    std::vector<std::vector<int> > groups();
    
    // suggested friends with highest score for this user.
    // fills in score at the given pointer.
    // if no suggestions exist, give empty vector and
    // set score to be -1
    std::vector<int> suggest_friends(int who, int& score);
    
    std::vector<int> bfs(User user);

 private:
    std::vector<User> User_Network;
  
};

#endif
