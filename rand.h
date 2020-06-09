#pragma once

inline int int_len(int a) {
    int len = 0;
    do ++len; while (a /= 10);
    return len;
}
inline long long pow(int a, int b) {
    int c = 1;
    for (int i = 0; i < b; i++)
        c*= a;
    return c;
}

class Gen {
public:

    Gen(int _seed) : seed(_seed) {};
    virtual double next() = 0;

protected:
    unsigned long long seed, mod = 0;
};

class GenClassic : public Gen {
public:
    GenClassic(int _seed) : Gen(_seed) {}

protected:
    unsigned long long depth = int_len(seed);
    unsigned long long mod = pow(10, depth);
    unsigned long long div = pow(10, depth / 2);
};

class MidSquare : public GenClassic {

public:
    MidSquare(int _seed) : GenClassic(_seed) {};

    double next() {
        seed = seed * seed / div % mod;
        return static_cast<double>(seed) / mod;
    }
};

class MidMulti : public GenClassic {

private:
    unsigned long long last = seed, tmp = seed;

public:
    MidMulti(int _seed) : GenClassic(_seed) {};

    double next() {
        tmp = seed;
        seed = last * seed / div % mod;
        last = tmp;
        return static_cast<double>(seed) / mod;
    }
};

class MixSum : public GenClassic {

private:
    unsigned long long div = pow(10, depth / 4);
    unsigned long long cut = mod / div;

public:
    MixSum(int _seed) : GenClassic(_seed) {};

    double next() {
        unsigned long long beg = seed / div;
        unsigned long long end = seed % cut;
        unsigned long long left = seed / cut;
        unsigned long long right = seed % div;
        unsigned long long a = right * cut + beg;
        unsigned long long b = end * div + left;
        seed = (a + b) % mod;
        return static_cast<double>(seed) / mod;
    }
};
class LCG : public Gen {

private:
    unsigned long long mod = (pow(2, 31) - 1), a = 16807, c = 0;

public:
    LCG(int _seed) : Gen(_seed) {};

    double next() {
        seed = (a * seed + c) % mod;
        return static_cast<double>(seed) / mod;
    }
};