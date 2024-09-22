long foo(int i, unsigned int n) {
    long ret;
    if (n == 0) return 1;
    if (i == 0) return 0;
    if (n == 1) return i;

    ret = foo(i,n/2) * foo(i,n/2);

    if (n%2) {
        ret *= i;
    }
    return ret;
}
// Optimized
long foo(int i, unsigned int n) {
    long ret;
    if (n == 0) return 1;
    if (i == 0) return 0;
    if (n == 1) return i;

    ret = foo(i,n/2);
    ret *= ret;

    if (n%2) {
        ret *= i;
    }
    return ret;
}
