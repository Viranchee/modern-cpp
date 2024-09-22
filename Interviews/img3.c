
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* foo(char *in) {
    int wordBegin = 0;
    int currentIdx = 0;
    char *word = NULL;
    int maxWordLen = -1;

    if (in == NULL) {
        return NULL;
    }
    for (; in[currentIdx]; currentIdx++) {
        if (in[currentIdx] == ' ') {
            int wordLen = (currentIdx - wordBegin);
            if (wordLen > maxWordLen) {
                word = (char*)malloc(wordLen+1);
                strncpy(word, in + wordBegin, wordLen);
                word[wordLen] = '\0';
                maxWordLen = wordLen;
            }
            wordBegin = currentIdx+1;
        }
    }

    if (wordBegin < currentIdx) {
        int wordLen = (currentIdx - wordBegin);
        if (wordLen > maxWordLen) {
            word = (char*)malloc(wordLen+1);
            strncpy(word, in + wordBegin, wordLen);
            word[wordLen] = '\0';
        }
    }
    return word;
}
