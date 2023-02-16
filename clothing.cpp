#include <sstream>
#include <iomanip>
#include <string>
#include "clothing.h"
#include "util.h"


using namespace std;

Clothing::Clothing(string category, string name, double price, int qty, string size, string brand) :
    Product(category, name, price, qty),
    size_(size),
    brand_(brand)

{

}


set<string> Clothing::keywords() const

{   
    string raw_words = "";
    raw_words += name_;
    raw_words += " ";
    raw_words += brand_;
    set<string> keywords_set = parseStringToWords(raw_words);
 
    return keywords_set;
      
    // product name, author name
    // set conditions for one char or apostraphes etc


}

string Clothing::displayString() const

{
    stringstream ss;
    ss << fixed << setprecision(2) << price_;
    string price = to_string(price_);
    string quantity = to_string(qty_);
    string ret_val = name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + price + " " + quantity + " left." ;
    return ret_val;

}

void Clothing::dump(std::ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << "\n";

}

