
void* magic = (void*) 0xFFFFFFFFFFFFFFFFULL;

void write_int(const int n) {
    *((int *)magic) = n;
}

void write_char(const char c) {
    *((char *)magic) = c;
}

void write_string(const char* s) {
    do {
        char c = *s;
        if (c == 0) return;
        write_char(c);
        s++;
    } while(1);
}
    

int gcd(int u, int v) {
    if (u == v) return u;
    if (1 == u) return u;
    if (u > v) {u ^= v ^= u ^= v;}  // Exchange u and v if needed to ensure that u < v in what follows.
    return gcd(u, v-u);
}    

void start() {
    write_string("gcd(10, 25) = "); write_int(gcd(10, 25));
    write_string("gcd(21, 14) = "); write_int(gcd(21, 14));
    write_string("gcd(79, 83) = "); write_int(gcd(79, 83));
}
