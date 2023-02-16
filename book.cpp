#include <sstream>
#include <iomanip>
#include <string>
#include "book.h"
#include "util.h"
using namespace std;

Book::Book(string category, string name, double price, int qty, string IBSN, string Author) :
    Product(category, name, price, qty),
    IBSN_(IBSN),
    Author_(Author)

{

}


 set<string> Book::keywords() const

{
    string raw_words = "";
    raw_words += name_;
    raw_words += " ";
    raw_words += Author_;
    set<string> keywords_set = parseStringToWords(raw_words);
    keywords_set.insert(IBSN_);
 
    return keywords_set;
}

string Book::displayString() const

{
    
    stringstream ss;
    ss << fixed << setprecision(2) << price_;

    string quantity = to_string(qty_);
    string ret_val = name_ + "\n" + "Author: " + Author_ + " ISBN: " + IBSN_ + "\n" + ss.str() + " " + quantity + " left." ;
    return ret_val;

}

void Book::dump(std::ostream& os) const
{
  Product::dump(os);
  os << IBSN_ << "\n" << Author_  << "\n";

}

