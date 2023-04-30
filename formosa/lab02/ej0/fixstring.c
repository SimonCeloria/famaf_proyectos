#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"

unsigned int fstring_length(fixstring s) {
    unsigned int len=0u;
    while ((len<FIXSTRING_MAX) && (s[len]!='\0')){
        len++;
    }
    return len;
}

bool fstring_eq(fixstring s1, fixstring s2) {
    bool iseq=true;
    unsigned int i=0u;
    unsigned int len=fstring_length(s1);
    if (len == fstring_length(s2)){
        while (i<len && iseq){
            if (s1[i]!=s2[i]){
                iseq=false;
            }
            i++;
        }
    }
    else{
        iseq=false;
    }

    return iseq;
}

bool fstring_less_eq(fixstring s1, fixstring s2) {
    bool is_less_or_eq=true;
    unsigned int i=0u;
    unsigned int len1=fstring_length(s1);
    unsigned int len2=fstring_length(s2);
    while (i<len1 && is_less_or_eq){
        if(s1[i]>s2[i] || (s1[i]=='\0' && len1>len2)){
            is_less_or_eq=false;
        }
        i++;
    }
    
    return is_less_or_eq;
}
