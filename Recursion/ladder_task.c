int ladder(int n) {
    if (n < 0) { return 0; }
    if (n == 1 || n == 0) { return 1; }
    return ladder(n - 1) + ladder(n - 2) + ladder(n - 3);
}