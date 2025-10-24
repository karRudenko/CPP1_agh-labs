#include "Match.h"
#include <iostream>
#include <cstring>
using namespace std;



//  if (strstr(text, pattern)) {
//         return true;
//     }
//     return false;

//functions
#ifdef IMPLEMENT_MATCH  // if we dont mark the flag, so this part wont be seen by compalier
bool match(const char* text, const char* pattern) {
    size_t n = strlen(text);
    size_t m = strlen(pattern);

    if (m > n) return false;    // if word is bigger than text, so its no sense chekking the matching

    for (size_t i = 0; i <= n - m; i++) {
        size_t k = 0;
        for (; k < m; k++) {
            if (text[i + k] != pattern[k])
                break;          // if we break, so something isnt matching, so k wont have all size of pattern
        }
        if (k == m)  // if we come to the end of pattern, so all letters are the same
            return true;
    }

    return false;
}

#endif
