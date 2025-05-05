#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cctype>
typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
      unsigned long long w[5] = {0};
      std::string lowerStr;

      for(char c : k) {
            lowerStr += std::tolower(c);
        }

      int len = lowerStr.length();
      int wIndex = 4;

      for(int i = len; i > 0 && wIndex >= 0; i -= 6, --wIndex) {
          int start = std::max(0, i - 6);
          int powIndex = 0;
          for(int j = i - 1; j >= start; --j) {
                HASH_INDEX_T val = letterDigitToNumber(lowerStr[j]);
                w[wIndex] += val * static_cast<unsigned long long>(std::pow(36, powIndex));
                ++powIndex;
            }
        }

        HASH_INDEX_T result = 0;
         for(int i = 0; i < 5; i++){
            result += rValues[i] * w[i];
         }

         return result;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        
        if(std::isdigit(letter))return letter - '0' + 26;
        else if (std::isalpha(letter)) return letter - 'a';
         
         return 0;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
