#include <sstream>
#include <iomanip>
#include <string>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(string category, string name, double price, int qty, string genre, string rating) : Product(category, name, price, qty),
                                                                                                 genre_(genre),
                                                                                                 rating_(rating)

{
}

set<string> Movie::keywords() const

{
    string raw_words = "";
    raw_words += name_;
    raw_words += " "; // space separator
    raw_words += genre_;
    set<string> keywords_set = parseStringToWords(raw_words);

    return keywords_set;
}

string Movie::displayString() const

{
    // display with formatting
    stringstream ss;
    ss << fixed << setprecision(2) << price_;

    string quantity = to_string(qty_);
    string ret_val = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + ss.str() + " " + quantity + " left.";
    return ret_val;
}

void Movie::dump(std::ostream &os) const
{
    Product::dump(os);
    os << genre_ << "\n"
       << rating_ << "\n";
}
