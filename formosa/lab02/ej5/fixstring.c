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
    bool less_eq = true;
    unsigned int i = 0u;
    unsigned int len1 = fstring_length(s1);
    while( (i<len1) && less_eq ){
        if(s1[i]>s2[i]){
            less_eq = false;
        }
        if( (s2[i] == '\0') && (s1[i] != '\0') ){
            less_eq = false;
        }
        i++;
    }
    
    return less_eq;
}

void fstring_set(fixstring s1, const fixstring s2) {
    int i=0;
    while (i<FIXSTRING_MAX && s2[i]!='\0') {
        s1[i] = s2[i];
        i++;
    }
    s1[i] = '\0';
}

void fstring_swap(fixstring s1,  fixstring s2) {
    fixstring aux;
    fstring_set(aux, s1);
    fstring_set(s1, s2);
    fstring_set(s2, aux);
}


