#ifndef movie_h
#define movie_h
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"


class Movie : public Product {
public:  
    Movie(const std::string category, const std::string name, double price, int qty, std::string Genre, std::string Rating);
    
    std::set<std::string> keywords() const;
    
    std::string displayString() const;
    
    void dump(std::ostream& os) const;

protected: 
    
    std::string genre_;
    
    std::string rating_;

};
#endif