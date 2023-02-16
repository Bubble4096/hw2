#include "MyDataStore.h"
#include "util.h"

using namespace std;

MyDataStore::~MyDataStore()
{
  // loop through users vectors then delete all users

  for (size_t i = 0; i < user_vect_.size(); i++)
  {
    delete user_vect_[i];
  }

  // loop through products vectors then delete all users

  for (size_t j = 0; j < totalProducts_.size(); j++)
  {
    delete totalProducts_[j];
  }
}

void MyDataStore::addProduct(Product *p)
{
  // add product to total products vector
  totalProducts_.push_back(p);

  // create set of product key words
  set<string> product_keywords = p->keywords();

  // sort product to map by keywords
  for (set<string>::iterator it = product_keywords.begin(); it != product_keywords.end(); it++)
  {
    string current_key_word = *it;

    // key word exists in keyword map
    if (keywords_map.find(*it) != keywords_map.end())
    { // add product to "hit" of key word
      ((keywords_map.find(*it))->second).insert(p);
    }
    // keyword not in map
    else
    { // add keyword to map, set product as hit
      set<Product *> new_set;
      new_set.insert(p);
      keywords_map.insert({current_key_word, new_set});
    }
  }
}

void MyDataStore::addUser(User *u)
{
  // add user to total users
  totalUsers_.insert({u->getName(), u});

  // create user cart
  vector<Product *> new_cart;
  carts_.insert({u->getName(), new_cart});
  user_vect_.push_back(u);
}

vector<Product *> MyDataStore::search(vector<string> &terms, int type)
{

  size_t i = terms.size();
  vector<Product *> product_hits;
  set<Product *> set1;
  set<Product *> set2;
  set<Product *> compare_set;
  int set1_pos = 0;               // first position
  int set2_pos = 1;               // second position
  string word1 = terms[set1_pos]; // first word

  if (i == 1) // one term entered
  {
    if (keywords_map.find(terms[0]) == keywords_map.end()) // term not found in keyword map
    {
      cout << "No Results Found" << endl;
    }
    else
    {
      compare_set = keywords_map.find(terms[0])->second; // term found in keyword map
    }
  }
  else // more than one term entered
  {

    // first term is not in keyword map
    if (keywords_map.find(word1) == keywords_map.end())
    {
      string other_word = terms[set2_pos];
      compare_set = keywords_map.find(other_word)->second;
    }
    // first and second word in keyword map
    else
    {
      set1 = keywords_map.find(word1)->second;

      while (i > 1) // while there are still terms to search
      {

        if (i != terms.size()) // after first round, increment position of second word
        {
          set2_pos++;
        }
        string word2 = terms[set2_pos]; // nth comparison word(could be 2nd term, third term, etc)

        // second word not in map
        if (keywords_map.find(word2) == keywords_map.end())
        {
          compare_set = set1;
          i = terms.size();
          break;

          // second word in map
        }
        else
        {
          set2 = (keywords_map.find(word2))->second;
          // and search
          if (type == 0)
          {
            compare_set = setIntersection(set1, set2);
          }
          // or search
          else if (type == 1)
          {
            compare_set = setUnion(set1, set2);
          }
          // move valid set to set1, then compare with set nth(set 2)
          set1 = compare_set;
          i--;
        }
      }
    }
  }

  for (set<Product *>::iterator it = compare_set.begin(); it != compare_set.end(); ++it)
  {
    product_hits.push_back(*it);
  }
  // return vector of product * that match search criterion

  return product_hits;
}

void MyDataStore::dump(std::ostream &ofile)
{
  // call dump functions of each product + formatting
  ofile << "<products>" << endl;
  for (size_t i = 0; i < totalProducts_.size(); i++)
  {
    totalProducts_[i]->dump(ofile);
  }
  ofile << "</products>" << endl;

  ofile << "<users>" << endl;
  for (size_t i = 0; i < user_vect_.size(); i++)
  {
    user_vect_[i]->dump(ofile);
  }
  ofile << "</users>" << endl;
}

void MyDataStore::viewcart(string user_name)
{

  if (totalUsers_.find(user_name) != totalUsers_.end()) // username validation
  {
    map<string, vector<Product *>>::iterator it = carts_.find(user_name);

    // iterate through product vectors of user
    for (size_t i = 0; i < (it->second).size(); i++)
    {
      vector<Product *> products =
          it->second;
      string info = products[i]->displayString();
      size_t index = i + 1;
      cout << "Item " << index << " " << endl
           << info << endl;
    }
  }
  else // user not vaid
  {
    cout << "Invalid username" << endl;
  }
}

void MyDataStore::add(string user_name, size_t hit_result_index, vector<Product *> hits_vect)
{
  // user validation
  bool user_exists;
  if (totalUsers_.find(user_name) != totalUsers_.end())
  {
    user_exists = true;
  }
  else
  {
    user_exists = false;
  }

  // invalid user or hits #
  if (user_exists != true || hit_result_index > hits_vect.size() || hit_result_index < 0)
  {
    cout << "Invalid request" << endl;
  }
  // valid user and hits number
  else
  {
    map<string, vector<Product *>>::iterator it = carts_.find(user_name);
    // add hit to product vector of user
    it->second.push_back(hits_vect[hit_result_index - 1]);
  }
}

void MyDataStore::buycart(string user_name)
{
  vector<Product *> leftover_cart;

  if (carts_.find(user_name) == carts_.end()) // invalid user
  {
    cout << "Invalid username" << endl;
  }
  else // valid user
  {
    vector<Product *> user_cart = (carts_.find(user_name))->second;
    Product *curr_product;
    User *curr_user = (totalUsers_.find(user_name)->second);

    for (size_t i = 0; i < user_cart.size(); i++)
    {
      curr_product = user_cart[i];

      // check quantity and can user afford
      int qty = curr_product->getQty();
      double money = curr_user->getBalance();
      double price = curr_product->getPrice();
      double diff = money - price;

      if (qty > 0 && diff > 0)
      {
        // update product qty and user money
        curr_product->subtractQty(1);
        curr_user->deductAmount(price);
      }
      else
      {
        // push product that user cant buy to leftover cart
        leftover_cart.push_back(curr_product);
      }
    }
    // set user cart to leftovers cart
    carts_.find(user_name)->second = leftover_cart;
  }
}