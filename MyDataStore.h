#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include <map>



class MyDataStore : public DataStore {

public:  
    virtual ~MyDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    void viewcart(std::string user_name);
    void add(std::string user_name, size_t hit_result_index, std::vector<Product*> hits_vect);
   // void buycart();
private: 
    std::map<std::string, std::set<Product*>> keywords_map;
    std::map<std::string, User*> totalUsers_;
    std::map<std::string, std::vector<Product*>> carts_;
    std::vector<Product*> totalProducts_;
    std::vector<User*> user_vect_;

};
#endif