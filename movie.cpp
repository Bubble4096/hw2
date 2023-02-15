#include <sstream>
#include <iomanip>
#include <string>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(string category, string name, double price, int qty, string genre, string rating) :
    Product(category, name, price, qty),
    genre_(genre),
    rating_(rating)

{

}


set<string> Movie::keywords() const

{
    string raw_words = "";
    raw_words += name_;
    raw_words += " ";
    raw_words += genre_;
    set<string> keywords_set = parseStringToWords(raw_words);
 
    return keywords_set;
      
    // product name, genre
    // set conditions for one char or apostraphes etc
}

string Movie::displayString() const

{
    string price = to_string(price_);
    string quantity = to_string(qty_);
    string ret_val = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + price + " " + quantity + " left." ;
    return ret_val;

}

void Movie::dump(std::ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_  << "\n";

}
