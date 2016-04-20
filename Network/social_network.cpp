#include "network.h"
#include "user.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cout << "Error: ./social_network filename" << endl;
        return 0;
    }
    
    Network network = Network();
    network.read_friends(argv[1]);

    while(true)
    {
        cout << "\n\n" << setfill('>') << setw(65) << '>' << '\n';
        cout << "Add a user:        1 First Last Year Zipcode" << '\n';
        cout << "Add connection:    2 First1 Last1 First2 Last2" << '\n';
        cout << "Remove connection: 3 First1 Last1 First2 Last2" << '\n';
        cout << "Print Users:       4" << '\n';
        cout << "List Friends:      5 First Last" << '\n';
        cout << "Write to File:     6 Filename" << '\n';
        cout << "Shortest Path:     7 First1 Last1 First2 Last2" << '\n';
        cout << "Disjoint Sets:     8" << '\n';
        cout << "Suggest Friends:   9 First Last" << '\n';
        cout << setfill('<') << setw(65) << '<' << "\n\n\n";
        cout << setfill(' ');

        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1: //adding a user
            {
                string fname, lname, username;
                int year, zipcode;
                cin >> fname >> lname >> year >> zipcode;
                username = fname + " " + lname;
                network.add_user(username, year, zipcode);
                cout << username << " added successfully!\n\n";
                continue;
            }
                
            case 2: //adding connections
            {
                string fname1, lname1, username1;
                string fname2, lname2, username2;
                
                cin >> fname1 >> lname1 >> fname2 >> lname2;
                username1 = fname1 + " " + lname1;
                username2 = fname2 + " " + lname2;
                
                int check = network.add_connection(username1, username2);
                
                if(check == 0)
                    cout << "Connection Successful!\n\n";
                
                else
                    cerr << "Error: User(s) Not Found.\n\n";
                
                continue;
            }
                
            case 3: //removing connections
            {
                string fname1, lname1, username1;
                string fname2, lname2, username2;
                
                cin >> fname1 >> lname1 >> fname2 >> lname2;
                username1 = fname1 + " " + lname1;
                username2 = fname2 + " " + lname2;
                
                int check = network.remove_connection(username1, username2);
                int check2 = network.remove_connection(username2, username1);
                
                if(check == 0 && check2 == 0)
                    cout << "Connection Removed!\n\n";
                
                else
                    cerr << "Error: Connection Unsuccessful.\n\n";
                
                continue;
            }
                
            case 4: //printing all users
            {
                cout << "ID" << setw(15) << "Name" << setw(25)
                     << "Year" << setw(10) << "Zip\n";
                cout << setfill('=') <<  setw(65) << '=' << "\n";
                
                vector<User>* user_database = network.network_ptr();
                
                for(int i = 0; i < user_database->size(); i++)
                {
                    cout << setfill(' ');
                    cout << user_database->at(i).get_id() << "." << setw(20)
                         << user_database->at(i).get_name() << setw(20)
                         << user_database->at(i).get_yob() << setw(10)
                         << user_database->at(i).get_zip() << '\n';
                }
                cout << '\n';
                continue;
            }
                
            case 5: //list friends
            {
                string fname, lname, username;
                cin >> fname >> lname;
                username = fname + " " + lname;
                int user_num = network.get_id(username);
                if(user_num == -1)
                {
                    cerr << "Error: User Not Found.\n\n";
                    continue;
                }
                //access network database of users
                vector<User>* user_database = network.network_ptr();
                //access friends
                vector<int>* friend_vector =
                    user_database->at(user_num).friends_ptr();
                
                cout << "ID" << setw(15) << "Name" << setw(25)
                     << "Year" << setw(10) << "Zip\n";
                cout << setfill('=') <<  setw(65) << '=' << "\n";
                
                for(int i = 0; i < friend_vector->size(); i++)
                {
                    int friend_id = friend_vector->at(i);
                    cout << setfill(' ');
                    cout << user_database->at(friend_id).get_id() << "." << setw(20)
                    << user_database->at(friend_id).get_name() << setw(20)
                    << user_database->at(friend_id).get_yob() << setw(10)
                    << user_database->at(friend_id).get_zip() << '\n';
                }
                cout << '\n';
                continue;
            }
                
            case 6: //writing to file
            {
                char filename[80];
                cin >> filename;
                int check = network.write_friends(filename);
                
                if(check != 0) cerr << "Error: Writing unsuccessful.\n\n";
                
                cout << "File Export Successful!\n\n";
                continue;
            }
                
            case 7: //shortest path
            {
                string fname1, lname1, username1;
                string fname2, lname2, username2;
                cin >> fname1 >> lname1 >> fname2 >> lname2;
                username1 = fname1 + " " + lname1;
                username2 = fname2 + " " + lname2;
                
                int u1 = network.get_id(username1);
                int u2 = network.get_id(username2);
                //access network database of users
                vector<User>* user_database = network.network_ptr();

                vector<int> path = network.shortest_path(u1, u2);
                
                if(path.empty())
                {
                    cout << "None";
                    continue;
                }
                
                else
                {
                    cout << "Distance: " << path.size() - 1 << '\n';
                    cout << user_database->at(path[0]).get_name();
                    //prints out everything but first
                    for(int i = 1; i < path.size(); i++)
                        cout << " -> " << user_database->at(path[i]).get_name();
                    
                    continue;
                }
                
                continue;
            }
                
            case 8: //printing all disjoint sets
            {
                vector<User>* user_database = network.network_ptr();
                
                vector<vector<int> > sets = network.groups();
                
                for (int i = 0; i < sets.size(); i++)
                {
                    vector<int> this_set = sets[i];
                    
                    cout << "Set " << i + 1 << " => ";
                    //prints first person
                    cout << user_database->at(this_set[0]).get_name();
                    
                    for (int j = 1; j < this_set.size(); j++)
                        cout << ", " << user_database->at(this_set[j]).get_name();
                    
                    cout << '\n';
                }
                
                continue;
            }
                
            case 9: //friend suggestion
            {
                string fname, lname, username;
                cin >> fname >> lname;
                
                username = fname + " " + lname;
                int user_num = network.get_id(username);
                if(user_num == -1)
                {
                    cerr << "Error: User Not Found";
                    continue;
                }
                    
                    
                vector<User>* user_database = network.network_ptr();
                int score = -1;
                
                vector<int> friends = network.suggest_friends(user_num, score);
                
                if(score == -1)
                {
                    cout << "None";
                    continue;
                }
                
                else
                {
                    cout << "The suggested friend(s) is/are: " << '\n';
                    
                    for (int i = 0; i < friends.size(); i++)
                    {
                        cout << user_database->at(friends[i]).get_name()
                        << '\t' << "Score: " << score << "\n";
                    }
                }
                continue;
            }
                
            default:
            {
                cout << "Exiting Program...\n\n\n";
                break;
            }
        }
        
        return 0;
    }
}
