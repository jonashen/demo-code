#include "user.h"

using namespace std;

User::User(int num, string name, int year, int zip, std::vector<int> friends)
{
    id_num = num;
    full_name = name;
    birth_year = year;
    zip_code = zip;
    friend_list = friends;
}

void User::add_friend(int num_id) //Adds a friend id
{
    friend_list.push_back(num_id);
}

void User::delete_friend(int num_id) //Deletes friend id
{
    for(int i = 0; i < friend_list.size(); i++)
    {
        if(friend_list[i] == num_id)
            friend_list.erase(friend_list.begin()+i);
    }
}

string User::get_name() // retrieves name
{
    return full_name;
}

int User::get_id() // retrieves id
{
    return id_num;
}

int User::get_yob() // retrieves year
{
    return birth_year;
}

int User::get_zip() // retrieves zip code
{
    return zip_code;
}

std::vector<int>* User::friends_ptr()
{
    return &friend_list;
}