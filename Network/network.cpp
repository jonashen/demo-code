#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <iterator>
#include "network.h"
#include "user.h"

using namespace std;

Network::Network()
{
}

/*****/
int Network::read_friends(const char *filename)
{
    ifstream inFile(filename);
    
    string line;
    int line_num = 0;
    while ( getline(inFile,line) )
        line_num++;
    
    if(line_num%5 != 1)
    {
        inFile.close();
        return -1;
    }  //not correct format
    
    else
    {
        inFile.clear();                 // clear fail and eof bits
        inFile.seekg(0, ios::beg);      // start from beginning
        
        char temp[80];
        int people = 0;
        inFile >> temp;
        people = atoi(temp);
        
        int num, year, zip;
        string fname, lname, name;
        std::vector<int> friends;
        
        for (int j = 0; j < people; j++)
        {
            inFile >> temp; num = atoi(temp);
            inFile >> temp; fname = temp;
            inFile >> temp; lname = temp;
            inFile >> temp; year = atoi(temp);
            inFile >> temp; zip = atoi(temp);
            //this one removes \n from last line
            getline(inFile, line); 
            getline(inFile, line);
            
            stringstream ss(line);
            int c[80];
            int num_friends = 0;
            
            for(int i = 0; i < line.length(); i++)
            {
                if(line[i]==' ' && line[i]!='\n') num_friends++;
            }
            
            for (int k = 0; k < num_friends+1;k++)
            {
                ss >> c[k];
                friends.push_back(c[k]);
            }
            
            name = fname + " " + lname;
            User_Network.push_back(User(num, name, year, zip, friends));
            friends.clear();
        }
            
        inFile.close();
    }
    
    return 0;
}

/*****/
int Network::write_friends(const char *filename)
{
    ofstream outFile (filename);
    vector<int>* friendList;
    
    if (!outFile) return -1;
    
    else
    {
        outFile << User_Network.size() << '\n';
        for(int i = 0; i < User_Network.size(); i++)
        {
            outFile << User_Network[i].get_id() << '\n';
            outFile << '\t' << User_Network[i].get_name() << '\n';
            outFile << '\t' <<  User_Network[i].get_yob() << '\n';
            outFile << '\t' <<  User_Network[i].get_zip() << '\n';
            outFile << '\t';
            
            friendList = User_Network[i].friends_ptr();
            for (int j = 0; j < friendList->size(); j++)
                outFile << friendList->at(j) << ' ';
        
            outFile << '\n';
        }
    }
    
    outFile.close();
    return 0;
}


/*****/
void Network::add_user(std::string username, int yr, int zipcode)
{
    std::vector<int> friends;
    int num = User_Network.size();
    User_Network.push_back(User(num, username, yr, zipcode, friends));
}


/*****/
int Network::add_connection(std::string name1, std::string name2)
{
    int n1 = 101, n2 = 101; //1 more than the max users
    for(int i = 0; i < User_Network.size(); i++)
    {
        if(User_Network[i].get_name() == name1)
            n1 = User_Network[i].get_id();
        
        else if(User_Network[i].get_name() == name2)
            n2 = User_Network[i].get_id();
    }
    
    if(n1 == 101 || n2 == 101) return -1;
    
    else
    {
        User_Network[n1].add_friend(n2);
        User_Network[n2].add_friend(n1);
    }
    
    return 0;
}


/*****/
int Network::remove_connection(std::string name1, std::string name2)
{
    int n1 = 101, n2 = 101;
    for(int i = 0; i < User_Network.size(); i++)
    {
        if(User_Network[i].get_name() == name1)
            n1 = User_Network[i].get_id();
        
        else if(User_Network[i].get_name() == name2)
            n2 = User_Network[i].get_id();
    }
    
    if(n1 == 101 || n2 == 101) return -1;
    
    else
    {
        User_Network[n1].delete_friend(n2);
        User_Network[n1].delete_friend(n1);
    }
    
    return 0;
}


/*****/
int Network::get_id(std::string username)
{
    int n1 = -1;
    for(int i = 0; i < User_Network.size(); i++)
    {
        if(User_Network[i].get_name() == username)
            n1 = User_Network[i].get_id();
    }
    
    return n1;
}


/*****/
std::vector<User>* Network::network_ptr()
{
    return &User_Network;
}


/*****/
vector<int> Network::bfs(User user) //used on one user
{
    int user_num = user.get_id();
    vector<int> this_network;
    this_network.push_back(user_num);
    
    
    vector<int>* friendsList = User_Network[user_num].friends_ptr();
    
    User_Network[user_num].depth = 0;
    User_Network[user_num].predecessor = -1;
    
    //copies this.friends to the network
    for (int i = 0; i < friendsList->size(); i++)
    {
        int a = friendsList->at(i);
        this_network.push_back(a);
        //initial depth is 1
        User_Network[a].depth = 1;
        //initial predecessor is friend
        User_Network[a].predecessor = user_num;
    }

    //rechecks this network excluding first user
    for (int j = 1; j < this_network.size(); j++)
    {
        int b = this_network[j];
        //checks friend list of new user
        friendsList = User_Network[b].friends_ptr();
        //iterates through each friend of user
        for (int k = 0; k < friendsList->size(); k++)
        {
            bool indicator = false;
            //if friend is already in network, indicator is true;
            for (int l = 0; l < this_network.size(); l++)
            {
                if(this_network[l] == friendsList->at(k))
                {
                    indicator = true;
                    break;
                }
            }
            
            if (!indicator)
            {
                int c = friendsList->at(k);
                this_network.push_back(c);
                User_Network[c].depth = User_Network[b].depth + 1;
                User_Network[c].predecessor = b;
            }
        }
    }
    
    return this_network;
}


/*****/
vector<int> Network::shortest_path(int from, int to)
{
    int f = from;
    int t = to;
    vector<int> list = bfs(User_Network[f]);
    vector<int> path;
    vector<int> test = *User_Network[t].friends_ptr();
    
    
    bool check = false; //checks if both are in same network
    for (int i = 0; i < list.size(); i++)
        if (list[i] == t) check = true;
    
    if(!check) return path;
    if(!test.empty()) path.push_back(t); //if no friends, return none
    
    User temp = User_Network[t]; //temp user
    int p = temp.predecessor;
    
    while (p != -1)
    {
        path.push_back(p);
        temp = User_Network[p];
        p = temp.predecessor;
    }
    
    reverse(path.begin(), path.end()); //reverse path
    
    return path;
}


/*****/
vector<vector<int> > Network::groups()
{
    vector<int> indicator; //indicator vector
    
    for (int a = 0; a < User_Network.size(); a++)
        indicator.push_back(-1);
    //creates network from first user
    vector<int> network = bfs(User_Network[0]);
    vector<vector<int> > big_network;
    big_network.push_back(network);
    //sets indicator to 1
    for(int j = 0; j < network.size(); j++)
    {
        indicator[network[j]] = 1;
    }
    
    for (int k = 0; k < User_Network.size(); k++)
    {
        //checks to see any remaining unchecked users
        if (indicator[k] == -1)
        {
            //creates new network from unchecked user
            network = bfs(User_Network[k]);
            //sets every user in new network to checked
            for (int l = 0; l < network.size(); l++)
            {
                indicator[network[l]] = 1;
            }
            
            big_network.push_back(network);
        }
    }
    
    return big_network;
}


/*****/
vector<int> Network::suggest_friends(int who, int& score)
{
    vector<int> yourNetwork = bfs(User_Network[who]); //PEOPLE IN YOUR NETWORK
    vector<int> scores; //scores vector TO SEE EACH PERSON'S SCORE
    //YOUR LIST OF FRIENDS
    vector<int>* yourFriends = User_Network[who].friends_ptr();
    //DELETE YOU AND YOUR FRIENDS FROM NETWORK
    yourNetwork.erase(find(yourNetwork.begin(),yourNetwork.end(),who));
    for (int b = 0; b < yourFriends->size(); b++)
        yourNetwork.erase(find(yourNetwork.begin(),yourNetwork.end(),yourFriends->at(b)));
    
    for (int a = 0; a < yourNetwork.size(); a++)
        scores.push_back(0);

    for (int z = 0; z < yourNetwork.size(); z++) {
        cout << yourNetwork[z] << "\n"; }
    
    vector<int>* theirFriends; //THEIR LIST OF FRIENDS YO
    int highest_score = 0;
    //iterate thru indicator to see possibilities
    for (int d = 0; d < yourNetwork.size(); d++)
    {
        theirFriends = User_Network[yourNetwork[d]].friends_ptr();
        
        int their_score = 0;
        //CHECK YOUR FRIENDS WITH THEIRS
        for (int e = 0; e < theirFriends->size(); e++)
        {
            for (int f = 0; f < yourFriends->size(); f++)
            {
                if(yourFriends->at(f) == theirFriends->at(e)) their_score++;
            }
            
            scores[d] = their_score;
            //set highest score
            if(their_score > highest_score) highest_score = their_score;
        }
    }
    
    vector<int> new_friends;
    //checks to see how many highest score
    for (int d = 0; d < scores.size(); d++)
        if(scores[d] == highest_score) new_friends.push_back(yourNetwork[d]);
    
    score = highest_score;
    return new_friends;
}