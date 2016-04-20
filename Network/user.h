#ifndef USER_H
#define USER_H
#include <vector>
#include <string>

class User {
 public:
    User(int num, std::string name, int year, int zip, std::vector<int> friends);
    //~User();
    void add_friend(int num_id);
    void delete_friend(int num_id);
    std::string get_name();
    int get_id();
    int get_yob();
    int get_zip();
    std::vector<int>* friends_ptr();
    int depth;
    int predecessor;

 private:
    int id_num;
    std::string full_name;
    int birth_year;
    int zip_code;
    std::vector<int> friend_list;
};


#endif