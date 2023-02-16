#include "MyDataStore.h"
#include "util.h"

using namespace std;


 MyDataStore::~MyDataStore() 
{ 
/**/
    // delete users
/*
    while(user_vect_.size() > 0){
        delete user_vect_[0];
    }
*/
   for(size_t i = 0; i < user_vect_.size(); i++)
   {
    delete user_vect_[i];
   }
   /*

    // delete carts
    vector<vector<Product*>> cart_place_holder;
    for (map<string, vector<Product*>>::iterator it = carts_.begin(); it != carts_.end(); it++)
    {  
        cart_place_holder.push_back(it->second);
    }
    
    for(size_t i = 0; i < cart_place_holder.size(); i ++)
    {
        for(size_t j = 0; j < cart_place_holder[i].size(); i++ )
        {
            delete cart_place_holder[i][j];
        }
    }
    carts_.clear();

*/
/*
    // delete all the products
    while(totalProducts_.size() > 0){
        delete totalProducts_[0];
    }
    */
   for(size_t j = 0; j < totalProducts_.size(); j++)
   {
    delete totalProducts_[j];
   }
}


void MyDataStore::addProduct(Product* p)
{
  totalProducts_.push_back(p);
  
  // add keywords to map 
  set<string> product_keywords = p->keywords();

  for(set<string>::iterator it = product_keywords.begin(); it != product_keywords.end(); it++)
  {
    string current_key_word = *it;
    
    // key word exists in keyword map
    if(keywords_map.find(*it)!= keywords_map.end() )
    {
      ((keywords_map.find(*it))->second).insert(p);
    } 
    // keyword not in map
    else 
    {
      set<Product*> new_set;
      new_set.insert(p);
      keywords_map.insert({current_key_word, new_set});
    }
  }

}

void MyDataStore::addUser(User* u)
{
  
  totalUsers_.insert({u->getName(), u});


  // create user and cart 
  vector<Product*> new_cart;

  carts_.insert({u->getName(), new_cart});
  user_vect_.push_back(u);

}

vector<Product*> MyDataStore::search(vector<string>& terms, int type)
{
  // trojan data dog

size_t i = terms.size();
vector<Product*> product_hits;
set<Product*> set1;
set<Product*> set2;
set<Product*> compare_set;

int set1_pos = 0;
int set2_pos = 1;
string word1 = terms[set1_pos];

if(keywords_map.find(word1) == keywords_map.end())
{
   string other_word = terms[set2_pos];
   compare_set = keywords_map.find(other_word)->second;
} else
{
  set1 = keywords_map.find(word1)->second;



while(i > 1)
  { 

    if(i!=terms.size()){
      set2_pos++; 
    }
    string word2 = terms[set2_pos];

    if(keywords_map.find(word2) == keywords_map.end()){
      compare_set = set1;
      i = terms.size();
      break;
    } else {
    set2 = (keywords_map.find(word2))->second;
    // and search
      if(type == 0)
      {
        
        compare_set = setIntersection(set1, set2);

      }
    // or search
      else if (type == 1)
      {
        compare_set = setUnion(set1, set2);
      }
      set1 = compare_set;
      i--;
    }
  }
}

for(set<Product*>::iterator it = compare_set.begin(); it != compare_set.end(); ++it)
{
  product_hits.push_back(*it);
}
//return vector of product * that match search criterion

return product_hits;
}



void MyDataStore::dump(std::ostream& ofile)
{ 
  ofile << "<products>" <<endl;
  for(size_t i = 0; i < totalProducts_.size(); i++)
  {
    totalProducts_[i]->dump(ofile);
  }
  ofile << "</products>" <<endl;

  ofile << "<users>" <<endl;
  for(size_t i = 0; i < user_vect_.size(); i++)
  {
    user_vect_[i]->dump(ofile);
  }
  ofile << "</users>" <<endl;
}

void MyDataStore::viewcart(string user_name)
{

  
  if(totalUsers_.find(user_name) != totalUsers_.end()){
    map<string, vector<Product*>>::iterator it = carts_.find(user_name);
    for(size_t i = 0; i < (it->second).size(); i++)
    {
        vector<Product*> products =   
        it->second;
        string info = products[i]->displayString();
        size_t index = i+1;
        cout << index << " " << info << endl;
    }
  } else 
  {
    cout << "Invalid username" << endl;
  }

}

void MyDataStore::add(string user_name, size_t hit_result_index, vector<Product*> hits_vect)
{
  bool user_exists;
  if(totalUsers_.find(user_name) != totalUsers_.end()){
    user_exists = true;
  } else 
  {
    user_exists = false;
  }
  cout << "does user exist?" << boolalpha << user_exists << endl;

  // invalid user or hits #
  if(user_exists != true || hit_result_index >  hits_vect.size() || hit_result_index < 0){
    cout << "Invalid Command" << endl;
  } 
  // valid user and hits number
  else
  {
    map<string, vector<Product*>>:: iterator it = carts_.find(user_name);
    // add hit to product vector of user
    it->second.push_back(hits_vect[hit_result_index-1]);
  }
}

// void MyDataStore::buycart(string user_name)
// {
//   // vector<Product*> user_cart = 
//   // cout << "trying to buy cart" << endl;


// }