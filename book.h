#ifndef book_H
#define book_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"


class Book : public Product {
public:  
    Book( std::string category,  std::string name, double price, int qty, std::string IBSN, std::string Author);
   
    std::set<std::string> keywords() const;
    
    std::string displayString() const;
    
    void dump(std::ostream& os) const;

protected: 
    
    std::string IBSN_;
    
    std::string Author_;

};
#endif