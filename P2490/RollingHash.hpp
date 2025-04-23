#ifndef ROLLING_HASH_HPP
#define ROLLING_HASH_HPP

#include <iostream>
#include <vector>
#include <string>

class RollingHash {
private:
    typedef long long ll;
    typedef std::pair<ll, ll> pll;
    ll p1, p2;
    const int B = 131;
    int n;
    std::vector<pll> Binvs;
    std::vector<pll> Bpow;
    std::string str;
    std::vector<pll> HashSum;

    inline ll qpow(ll base, ll exp, ll mod) {
        ll res = 1;
        for(base %= mod; exp; exp >>= 1) {
            if (exp & 1) res = (res * base) % mod;
            base = (base * base) % mod;
        }
        return res;
    }
    inline ll modInv(ll n, ll mod) { return qpow(n, mod - 2, mod); }

public:
    RollingHash() : n(0) {
        p1 = 19260817;
        p2 = 1e9 + 7;
        const int maxLen = 5000;
        HashSum.resize(maxLen + 1);
        Binvs.resize(maxLen + 1);
        Bpow.resize(maxLen + 1);

        HashSum[0] = {0, 0};

        ll Binv1 = modInv(B, p1);
        ll Binv2 = modInv(B, p2);
        Binvs[0] = {1, 1};
        for (int i = 1; i <= maxLen; ++i) {
            Binvs[i].first = (Binvs[i-1].first * Binv1) % p1;
            Binvs[i].second = (Binvs[i-1].second * Binv2) % p2;
        }

        Bpow[0] = {1, 1};
        for (int i = 1; i <= maxLen; ++i) {
            Bpow[i].first = (Bpow[i-1].first * B) % p1;
            Bpow[i].second = (Bpow[i-1].second * B) % p2;
        }

    };

    ~RollingHash(){};
    pll getp(){ return pll (p1,p2); };

    void append(char c) {
        n++;
        int x = c - 'a' + 1;
        ll res1 = x * Binvs[n].first % p1;
        ll res2 = x * Binvs[n].second % p2;
        HashSum[n] = { (HashSum[n-1].first + res1) % p1, (HashSum[n-1].second + res2) % p2 };
        str += c;
    }

    pll getHash(int l, int r) {
        ll res1 = (HashSum[r].first - HashSum[l-1].first + p1) % p1;
        ll res2 = (HashSum[r].second - HashSum[l-1].second + p2) % p2;
        res1 = res1 * Bpow[r].first % p1;
        res2 = res2 * Bpow[r].second % p2;
        return {res1, res2};
    }
};

#endif