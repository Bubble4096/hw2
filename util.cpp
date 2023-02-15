#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{ 
    stringstream ss(rawWords);
    string word;
    set<std::string> word_set;


   while(ss >> word){
    

       string clean_word = "";

       for(size_t i = 0; i < word.size(); i++)
        {
         if(ispunct(word[i]) == false)
         {
            clean_word += word[i];
         } 
         else if(ispunct(word[i]) == true)
         {
           if(clean_word.size() > 1)
           {
            word_set.insert(clean_word);
           }
           clean_word = "";
         }
        }
        // if word is completely clean
        if(clean_word.size() > 1)
        {
          word_set.insert(clean_word);
        }
        clean_word = "";

      
    }
    
    return word_set; 

}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
