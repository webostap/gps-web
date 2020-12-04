#pragma once

typedef unsigned long long ul; 

inline int int_len(int a) {
    int len = 0;
    do ++len; while (a /= 10);
    return len;
}
inline long long int_pow(int a, int b) {
    int c = 1;
    for (int i = 0; i < b; i++)
        c*= a;
    return c;
}

class Gen {
public:

    Gen(int _seed) : seed(_seed) {}
    virtual double next() = 0;

protected:
    ul seed, mod = 0;
};

class GenClassic : public Gen {
public:
    GenClassic(int _seed) : Gen(_seed) {}

protected:
    ul depth = int_len(seed);
    ul mod = int_pow(10, depth);
    ul div = int_pow(10, depth / 2);
};

class MidSquare : public GenClassic {

public:
    MidSquare(int _seed) : GenClassic(_seed) {}

    double next() override {
        seed = seed * seed / div % mod;
        return static_cast<double>(seed) / mod;
    }
};

class MidMulti : public GenClassic {

private:
    ul last = seed, tmp = seed;

public:
    MidMulti(int _seed) : GenClassic(_seed) {}

    double next() override {
        tmp = seed;
        seed = last * seed / div % mod;
        last = tmp;
        return static_cast<double>(seed) / mod;
    }
};

class MixSum : public GenClassic {

private:
    ul div = int_pow(10, depth / 4);
    ul cut = mod / div;

public:
    MixSum(int _seed) : GenClassic(_seed) {}

    double next() override {
        ul beg = seed / div;
        ul end = seed % cut;
        ul left = seed / cut;
        ul right = seed % div;
        ul a = right * cut + beg;
        ul b = end * div + left;
        seed = (a + b) % mod;
        return static_cast<double>(seed) / mod;
    }
};
class LCG : public Gen {

private:
    ul mod = (int_pow(2, 31) - 1), a = 16807, c = 0;

public:
    LCG(int _seed) : Gen(_seed) {}

    double next() override {
        seed = (a * seed + c) % mod;
        return static_cast<double>(seed) / mod;
    }
};
