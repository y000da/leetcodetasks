int triangle_numbers(int n) {
    if (n < 1) return 0;
    if (n == 1) return 1;
    return n + triangle_numbers(n - 1);        
}