char* dup(char a[100]) {
    char copy[100];
    int i = 0;
    for (; (i < 100) && a[i]; i++) {
        copy[i] = a[i];
    }
    copy[i] = 0;
    return copy;
}

