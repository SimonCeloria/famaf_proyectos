#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"

unsigned int fstring_length(fixstring s) {
    unsigned int length = 0u;

    while((s[length] != '\0')) {
        length = length + 1;
    }
    return length;
}

bool fstring_eq(fixstring s1, fixstring s2) {
    unsigned int i = 0u;
    bool res = true;


    while((s1[i] != '\0') || (s2[i] != '\0')) {
        if (s1[i] != s2[i])
        {
            res = false;
        }
        i = i + 1;
    }

    return res;

}

bool fstring_less_eq(fixstring s1, fixstring s2) {
    bool res = true;
    unsigned int i = 0;
    unsigned int length1 = fstring_length(s1);
    unsigned int length2 = fstring_length(s2);

    while(i < length1 && res) {
        if ((s1[i] > s2[i]) || (s1[i]=='\0' && length1 > length2))
        {
            res = false;
        }
        i = i + 1;
    }

    return res;
}

