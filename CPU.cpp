#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef long double LD;
typedef pair < int, int > PII;
typedef pair < LL, LL > PLL;
typedef pair < LD, LD > PDD;

#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define dbl(k, x) fixed << setprecision(k) << (x)

template < typename _T > inline void _DBG(const char *s, _T x) { cerr << s << " = " << x << "\n"; }
template < typename _T, typename... args > void _DBG(const char *s, _T x, args... a) { while(*s != ',') cerr << *s++; cerr << " = " << x << ','; _DBG(s + 1, a...); }

#ifdef LOCAL
#define _upgrade ios_base::sync_with_stdio(0);
#define DBG(...) _DBG(#__VA_ARGS__, __VA_ARGS__)
#else
#define _upgrade ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define DBG(...) (__VA_ARGS__)
#define cerr if(0) cout
#endif

// ********************** CODE ********************** //

typedef unsigned long long ULL;
typedef vector < string > sol;

const int N = 70;
const int MX = 64 * 500 + 1;
const ULL LOW = 0xffffffffLL;
const ULL UPP = ~LOW;
const ULL LOW8 = 0xffLL;
const ULL UPP8 = 0xff00LL;

struct triple {
    ULL a, b, c;
};

int n;
triple T[N];

void read()
{
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> T[i].a >> T[i].b >> T[i].c;
}

void print(const sol &s)
{
    cout << sz(s) << "\n";
    for(auto &x: s)
        cout << x << "\n";
}

/////////////////////////////////////////////////

sol ans;
ULL reg[4];

void adec(int r)
{
    string s = "a";
    s[0] += r;
    ans.push_back("dec r" + s + "x");
    reg[r]--;
}

void ainc(int r)
{
    string s = "a";
    s[0] += r;
    ans.push_back("inc r" + s + "x");
    reg[r]++;
}

void anot(int r)
{
    string s = "a";
    s[0] += r;
    ans.push_back("not r" + s + "x");
    reg[r] = ~reg[r];
}

void aand(int r1, int r2)
{
    string s1 = "a", s2 = "a";
    s1[0] += r1; s2[0] += r2;
    ans.push_back("and r" + s1 + "x r" + s2 + "x");
    reg[r1] &= reg[r2];
}

void aor(int r1, int r2)
{
    string s1 = "a", s2 = "a";
    s1[0] += r1; s2[0] += r2;
    ans.push_back("or r" + s1 + "x r" + s2 + "x");
    reg[r1] |= reg[r2];
}

void axor(int r1, int r2)
{
    string s1 = "a", s2 = "a";
    s1[0] += r1; s2[0] += r2;
    ans.push_back("xor r" + s1 + "x r" + s2 + "x");
    reg[r1] ^= reg[r2];
}

void axorL32(int r1, int r2)
{
    string s1 = "a", s2 = "a";
    s1[0] += r1; s2[0] += r2;
    ans.push_back("xor e" + s1 + "x e" + s2 + "x");
    ULL tmp1 = reg[r1] & LOW;
    ULL tmp2 = reg[r2] & LOW;
    tmp1 ^= tmp2;
    reg[r1] = (reg[r1] & (~LOW)) | (tmp1 & LOW);
}

void ashl(int r1, int r2)
{
    string s1 = "a", s2 = "a";
    s1[0] += r1; s2[0] += r2;
    ans.push_back("shl r" + s1 + "x r" + s2 + "x");
    reg[r1] <<= reg[r2];
}

void ashr(int r1, int r2)
{
    string s1 = "a", s2 = "a";
    s1[0] += r1; s2[0] += r2;
    ans.push_back("shr r" + s1 + "x r" + s2 + "x");
    reg[r1] >>= reg[r2];
}

void aadd(int r1, int r2)
{
    string s1 = "a", s2 = "a";
    s1[0] += r1; s2[0] += r2;
    ans.push_back("add r" + s1 + "x r" + s2 + "x");
    reg[r1] += reg[r2];
}

void asub(int r1, int r2)
{
    string s1 = "a", s2 = "a";
    s1[0] += r1; s2[0] += r2;
    ans.push_back("sub r" + s1 + "x r" + s2 + "x");
    reg[r1] -= reg[r2];
}

void amul(int r1, int r2)
{
    string s1 = "a", s2 = "a";
    s1[0] += r1; s2[0] += r2;
    ans.push_back("mul r" + s1 + "x r" + s2 + "x");
    reg[r1] *= reg[r2];
}

void adiv(int r1, int r2)
{
    string s1 = "a", s2 = "a";
    s1[0] += r1; s2[0] += r2;
    ans.push_back("div r" + s1 + "x r" + s2 + "x");
    reg[r1] /= reg[r2];
}

void amod(int r1, int r2)
{
    string s1 = "a", s2 = "a";
    s1[0] += r1; s2[0] += r2;
    ans.push_back("mod r" + s1 + "x r" + s2 + "x");
    reg[r1] %= reg[r2];
}

void amov(int r1, int r2)
{
    string s1 = "a", s2 = "a";
    s1[0] += r1; s2[0] += r2;
    ans.push_back("mov r" + s1 + "x r" + s2 + "x");
    reg[r1] = reg[r2];
}

void aclear()
{
    ans.clear();
    for(int i = 0; i < 4; i++)
        reg[i] = 0;
}

//////////////////////////////////////////////////

void adecL8(int r)
{
    string s = "a";
    s[0] += r;
    ans.push_back("dec " + s + "l");
    ULL tmp = reg[r] & LOW8;
    tmp--;
    reg[r] = (reg[r] & (~LOW8)) | (tmp & LOW8);
}

void aincL8(int r)
{
    string s = "a";
    s[0] += r;
    ans.push_back("inc " + s + "l");
    ULL tmp = reg[r] & LOW8;
    tmp++;
    reg[r] = (reg[r] & (~LOW8)) | (tmp & LOW8);
}

void aandL8(int r1, int r2)
{
    string s1 = "a", s2 = "a";
    s1[0] += r1; s2[0] += r2;
    ans.push_back("and " + s1 + "l " + s2 + "l");

    ULL tmp1 = reg[r1] & LOW8;
    ULL tmp2 = reg[r2] & LOW8;
    tmp1 &= tmp2;

    reg[r1] = (reg[r1] & ~(LOW8)) | (tmp1 & LOW8);
}

void aorL8(int r1, int r2)
{
    string s1 = "a", s2 = "a";
    s1[0] += r1; s2[0] += r2;
    ans.push_back("or " + s1 + "l " + s2 + "l");

    ULL tmp1 = reg[r1] & LOW8;
    ULL tmp2 = reg[r2] & LOW8;
    tmp1 |= tmp2;

    reg[r1] = (reg[r1] & ~(LOW8)) | (tmp1 & LOW8);
}

void axorL8(int r1, int r2)
{
    string s1 = "a", s2 = "a";
    s1[0] += r1; s2[0] += r2;
    ans.push_back("xor " + s1 + "l " + s2 + "l");

    ULL tmp1 = reg[r1] & LOW8;
    ULL tmp2 = reg[r2] & LOW8;
    tmp1 ^= tmp2;

    reg[r1] = (reg[r1] & ~(LOW8)) | (tmp1 & LOW8);
}

void aaddL8(int r1, int r2)
{
    string s1 = "a", s2 = "a";
    s1[0] += r1; s2[0] += r2;
    ans.push_back("add " + s1 + "l " + s2 + "l");

    ULL tmp1 = reg[r1] & LOW8;
    ULL tmp2 = reg[r2] & LOW8;
    tmp1 += tmp2;

    reg[r1] = (reg[r1] & ~(LOW8)) | (tmp1 & LOW8);
}

void asubL8(int r1, int r2)
{
    string s1 = "a", s2 = "a";
    s1[0] += r1; s2[0] += r2;
    ans.push_back("sub " + s1 + "l " + s2 + "l");

    ULL tmp1 = reg[r1] & LOW8;
    ULL tmp2 = reg[r2] & LOW8;
    tmp1 -= tmp2;

    reg[r1] = (reg[r1] & ~(LOW8)) | (tmp1 & LOW8);
}

void amulL8(int r1, int r2)
{
    string s1 = "a", s2 = "a";
    s1[0] += r1; s2[0] += r2;
    ans.push_back("mul " + s1 + "l " + s2 + "l");

    ULL tmp1 = reg[r1] & LOW8;
    ULL tmp2 = reg[r2] & LOW8;
    tmp1 *= tmp2;

    reg[r1] = (reg[r1] & ~(LOW8)) | (tmp1 & LOW8);
}

void amovL8(int r1, int r2)
{
    string s1 = "a", s2 = "a";
    s1[0] += r1; s2[0] += r2;
    ans.push_back("mov " + s1 + "l " + s2 + "l");

    ULL tmp1 = reg[r1] & LOW8;
    ULL tmp2 = reg[r2] & LOW8;
    tmp1 = tmp2;

    reg[r1] = (reg[r1] & ~(LOW8)) | (tmp1 & LOW8);
}

//////////////////////////////////////////////////

void adecU8(int r)
{
    string s = "a";
    s[0] += r;
    ans.push_back("dec " + s + "h");
    ULL tmp = (reg[r] & UPP8) >> 8;
    tmp--;
    reg[r] = (reg[r] & (~UPP8)) | ((tmp << 8) & UPP8);
}

void aincU8(int r)
{
    string s = "a";
    s[0] += r;
    ans.push_back("inc " + s + "h");
    ULL tmp = (reg[r] & UPP8) >> 8;
    tmp++;
    reg[r] = (reg[r] & (~UPP8)) | ((tmp << 8) & UPP8);
}

void aandU8(int r1, int r2)
{
    string s1 = "a", s2 = "a";
    s1[0] += r1; s2[0] += r2;
    ans.push_back("and " + s1 + "h " + s2 + "h");

    ULL tmp1 = (reg[r1] & UPP8) >> 8;
    ULL tmp2 = (reg[r2] & UPP8) >> 8;
    tmp1 &= tmp2;

    reg[r1] = (reg[r1] & ~(UPP8)) | ((tmp1 << 8) & UPP8);
}

void amovU8(int r1, int r2)
{
    string s1 = "a", s2 = "a";
    s1[0] += r1; s2[0] += r2;
    ans.push_back("mov " + s1 + "h " + s2 + "h");

    ULL tmp1 = (reg[r1] & UPP8) >> 8;
    ULL tmp2 = (reg[r2] & UPP8) >> 8;
    tmp1 = tmp2;

    reg[r1] = (reg[r1] & ~(UPP8)) | ((tmp1 << 8) & UPP8);
}

void aorU8(int r1, int r2)
{
    string s1 = "a", s2 = "a";
    s1[0] += r1; s2[0] += r2;
    ans.push_back("or " + s1 + "h " + s2 + "h");

    ULL tmp1 = (reg[r1] & UPP8) >> 8;
    ULL tmp2 = (reg[r2] & UPP8) >> 8;
    tmp1 |= tmp2;

    reg[r1] = (reg[r1] & ~(UPP8)) | ((tmp1 << 8) & UPP8);
}

void axorU8(int r1, int r2)
{
    string s1 = "a", s2 = "a";
    s1[0] += r1; s2[0] += r2;
    ans.push_back("xor " + s1 + "h " + s2 + "h");

    ULL tmp1 = (reg[r1] & UPP8) >> 8;
    ULL tmp2 = (reg[r2] & UPP8) >> 8;
    tmp1 ^= tmp2;

    reg[r1] = (reg[r1] & ~(UPP8)) | ((tmp1 << 8) & UPP8);
}

void aaddU8(int r1, int r2)
{
    string s1 = "a", s2 = "a";
    s1[0] += r1; s2[0] += r2;
    ans.push_back("add " + s1 + "h " + s2 + "h");

    ULL tmp1 = (reg[r1] & UPP8) >> 8;
    ULL tmp2 = (reg[r2] & UPP8) >> 8;
    tmp1 += tmp2;

    reg[r1] = (reg[r1] & ~(UPP8)) | ((tmp1 << 8) & UPP8);
}

void asubU8(int r1, int r2)
{
    string s1 = "a", s2 = "a";
    s1[0] += r1; s2[0] += r2;
    ans.push_back("sub " + s1 + "h " + s2 + "h");

    ULL tmp1 = (reg[r1] & UPP8) >> 8;
    ULL tmp2 = (reg[r2] & UPP8) >> 8;
    tmp1 -= tmp2;

    reg[r1] = (reg[r1] & ~(UPP8)) | ((tmp1 << 8) & UPP8);
}

void amulU8(int r1, int r2)
{
    string s1 = "a", s2 = "a";
    s1[0] += r1; s2[0] += r2;
    ans.push_back("mul " + s1 + "h " + s2 + "h");

    ULL tmp1 = (reg[r1] & UPP8) >> 8;
    ULL tmp2 = (reg[r2] & UPP8) >> 8;
    tmp1 *= tmp2;

    reg[r1] = (reg[r1] & ~(UPP8)) | ((tmp1 << 8) & UPP8);
}

//////////////////////////////////////////////////

void aaddLU8(int r1, int r2)
{
    string s1 = "a", s2 = "a";
    s1[0] += r1; s2[0] += r2;
    ans.push_back("add " + s1 + "l " + s2 + "h");

    ULL tmp1 = (reg[r1] & LOW8);
    ULL tmp2 = (reg[r2] & UPP8) >> 8;
    tmp1 += tmp2;

    reg[r1] = (reg[r1] & ~(LOW8)) | (tmp1 & LOW8);
}

///////////////////////////////////////////////////

int cntone(ULL x)
{
    int res = 1;
    vector < int > v;
    while(x > 0)
    {
        v.push_back(x & 1);
        x /= 2;
    }
    while(!v.empty())
    {
        if(v.back()) res++;
        v.pop_back();
        if(sz(v)) res++;
    }
    return res;
}

LD avg_n[100], avg_d[100];

void setone(int r, ULL x)
{
    bool neg = false;
    ULL y = x;
    avg_n[1] += min(cntone(x), cntone(~x) + 1);
    avg_d[1]++;
    if(cntone(x) > cntone(~x) + 1)
    {
        neg = true;
        x = ~x;   
    }
    axor(r, r);
    vector < int > v;
    while(x > 0)
    {
        v.push_back(x & 1);
        x /= 2;
    }
    while(!v.empty())
    {
        if(v.back()) ainc(r);
        v.pop_back();
        if(sz(v)) aadd(r, r);
    }
    if(neg) anot(r);
    assert(reg[r] == y);
}

int cntone2r(ULL x)
{
    int res = 0;    
    res += 4;

    ULL x1 = x & LOW, x2 = (x & UPP) >> 32, p = 1;

    for(int i = 0; i < 32; i++)
    {
        if((x1 & p) == p) res++;
        if((x2 & p) == p) res++;
        res++;
        p *= 2;
    }
    res += 2;
    return res;
}

void setone2r(int r, int r1, int r2, ULL x)
{
    bool neg = false;
    ULL y = x;
    avg_n[4] += min(cntone2r(x), cntone2r(~x) + 1);
    avg_d[4]++;
    if(cntone2r(x) > cntone2r(~x) + 1)
    {
        neg = true;
        x = ~x;
    }

    axor(r, r);
    axor(r1, r1);
    axor(r2, r2);
    ainc(r2);

    ULL x1 = x & LOW, x2 = (x & UPP) >> 32, p = 1;

    for(int i = 0; i < 32; i++)
    {
        if((x1 & p) == p) aadd(r, r2);
        if((x2 & p) == p) aadd(r1, r2);
        aadd(r2, r2);
        p *= 2;
    }
    amul(r1, r2);
    aadd(r, r1);

    if(neg) anot(r);
    assert(reg[r] == y);
}

int cntreg(vector < pair < int, ULL > > vec)
{
    ULL x = 1;
    int res = 1;
    res += sz(vec);
    res++;

    ULL m = 0;
    for(auto y: vec)
        m = max(m, y.second);
    int b = 0;
    while(b < 64 && x <= m)
    {
        for(auto y: vec)
            if((y.second & x) == x) res++;
        b++; x *= 2;
        if(b < 64 && x <= m) res++;
    }
    return res;
}

void setreg(int r, vector < pair < int, ULL > > vec)
{
    int mask = 0, best = 1e9;
    for(int ma = 0; ma < (1 << sz(vec)); ma++)
    {
        auto v = vec;
        for(int j = 0; j < sz(v); j++)
            if((ma >> j) & 1) v[j].second = ~v[j].second;
        if(cntreg(v) + __builtin_popcount(ma) < best)
        {
            best = cntreg(v) + __builtin_popcount(ma);
            mask = ma;
        }
    }
    avg_n[sz(vec)] += best;
    avg_d[sz(vec)]++;

    for(int j = 0; j < sz(vec); j++)
        if((mask >> j) & 1) vec[j].second = ~vec[j].second;

    ULL x = 1;
    axor(r, r);
    for(auto j: vec)
        axor(j.first, j.first);
    ainc(r);

    ULL m = 0;
    for(auto y: vec)
        m = max(m, y.second);
    int b = 0;
    while(b < 64 && x <= m)
    {
        for(auto y: vec)
            if((y.second & x) == x) aadd(y.first, r);
        b++; x *= 2;
        if(b < 64 && x <= m) aadd(r, r);
    }

    for(int j = 0; j < sz(vec); j++)
        if((mask >> j) & 1) anot(vec[j].first);
}

int cntreg2(vector < pair < int, ULL > > vec)
{
    int res = 1 + sz(vec);

    for(int i = 48; i >= 0; i -= 16)
    {
        ULL p = 1;
        res++;

        auto lo = vec, up = vec;
        for(auto &y: lo) y.second >>= i;
        for(auto &y: up) y.second >>= (i + 8);

        for(int j = 0; j < 8; j++)
        {
            for(auto y: lo)
                if((y.second & p) == p) res++;
            
            for(auto y: up)
                if((y.second & p) == p) res++;
            
            if(j == 4 && i == 48)
                res++;

            p *= 2;
            res++;
        }

        res += sz(vec);
    }

    return res;
}

void setreg2(int r, vector < pair < int, ULL > > vec)
{
    int mask = 0, best = 1e9;
    for(int ma = 0; ma < (1 << sz(vec)); ma++)
    {
        auto v = vec;
        for(int j = 0; j < sz(v); j++)
            if((ma >> j) & 1) v[j].second = ~v[j].second;
        if(cntreg2(v) + __builtin_popcount(ma) < best)
        {
            best = cntreg2(v) + __builtin_popcount(ma);
            mask = ma;
        }
    }
    avg_n[sz(vec) + 3] += best;
    avg_d[sz(vec) + 3]++;

    for(int j = 0; j < sz(vec); j++)
        if((mask >> j) & 1) vec[j].second = ~vec[j].second;

    axor(r, r);
    for(auto j: vec)
        axor(j.first, j.first);

    for(int i = 48; i >= 0; i -= 16)
    {
        ULL p = 1;
        aincU8(r);

        auto lo = vec, up = vec;
        for(auto &y: lo) y.second >>= i;
        for(auto &y: up) y.second >>= (i + 8);

        for(int j = 0; j < 8; j++)
        {
            for(auto y: lo)
                if((y.second & p) == p) aaddLU8(y.first, r);
            
            for(auto y: up)
                if((y.second & p) == p) aaddU8(y.first, r);
            
            if(j == 4 && i == 48)
                aaddLU8(r, r);

            p *= 2;
            aaddU8(r, r);
        }

        assert(reg[r] == 16);

        if(i != 0)
        {
            for(auto y: vec)
                ashl(y.first, r);
        }
    }

    for(int j = 0; j < sz(vec); j++)
        if((mask >> j) & 1) anot(vec[j].first);
}

int cntreg3(vector < pair < int, ULL > > vec)
{
    int res = 5;

    ULL p1 = 1LL << 0;
    ULL p2 = 1LL << 32;
    ULL p3 = p1 + p2;

    ULL br[] = {reg[0], reg[1], reg[2], reg[3]};

    for(int i = 0; i < 32; i++)
    {
        for(auto &y: vec)
        {
            if((y.second ^ reg[y.first]) & p2)
            {
                reg[y.first] ^= p3;
                res++;
            }
            if((y.second ^ reg[y.first]) & p1)
            {
                reg[y.first] ^= p1;
                res++;
            }
        }
        res++;
        p1 *= 2;
        p2 *= 2;
        p3 *= 2;
    }

    for(int i = 0; i < 4; i++)
        reg[i] = br[i];

    return res;
}

void setreg3(int r, vector < pair < int, ULL > > vec)
{
    int mask = 0, best = 1e9;
    for(int ma = 0; ma < (1 << sz(vec)); ma++)
    {
        auto v = vec;
        for(int j = 0; j < sz(v); j++)
            if((ma >> j) & 1) v[j].second = ~v[j].second;
        if(cntreg3(v) + __builtin_popcount(ma) < best)
        {
            best = cntreg3(v) + __builtin_popcount(ma);
            mask = ma;
        }
    }
    avg_n[sz(vec) + 5] += best;
    avg_d[sz(vec) + 5]++;

    for(int j = 0; j < sz(vec); j++)
        if((mask >> j) & 1) vec[j].second = ~vec[j].second;

    axor(r, r);
    aincU8(r);
    // 8 -> 16 -> 32
    amul(r, r);
    amul(r, r);
    ainc(r);

    ULL p1 = 1LL << 0;
    ULL p2 = 1LL << 32;
    ULL p3 = p1 + p2;

    for(int i = 0; i < 32; i++)
    {
        for(auto &y: vec)
        {
            if((y.second ^ reg[y.first]) & p2)
            {
                axor(y.first, r);
            }
            if((y.second ^ reg[y.first]) & p1)
            {
                axorL32(y.first, r);
            }
        }
        aadd(r, r);
        p1 *= 2;
        p2 *= 2;
        p3 *= 2;
    }

    for(int j = 0; j < sz(vec); j++)
        if((mask >> j) & 1) anot(vec[j].first);
}

////////////////////////////////////////////////////////

sol task11()
{
    aclear();
    for(int i = 1; i <= n; i++)
    {
        setone2r(0, 1, 2, T[i].a);
        //setone(0, T[i].a);
        setone2r(1, 2, 3, T[i].b);
        //setone(1, T[i].b);
        setone(2, T[i].c);
    }
    return ans;
}

sol task12()
{
    aclear();
    for(int i = 1; i <= n; i++)
    {
        setreg(3, {{0, T[i].a}, {1, T[i].b}, {2, T[i].c}});

        assert(T[i].a == reg[0]);
        assert(T[i].b == reg[1]);
        assert(T[i].c == reg[2]);
    }
    return ans;
}

sol task13()
{
    aclear();
    for(int i = 1; i <= n; i++)
    {
        setreg2(3, {{0, T[i].a}, {1, T[i].b}, {2, T[i].c}});

        assert(T[i].a == reg[0]);
        assert(T[i].b == reg[1]);
        assert(T[i].c == reg[2]);
    }
    return ans;
}

sol task14()
{
    aclear();
    for(int i = 1; i <= n; i++)
    {
        setreg3(3, {{0, T[i].a}, {1, T[i].b}, {2, T[i].c}});

        assert(T[i].a == reg[0]);
        assert(T[i].b == reg[1]);
        assert(T[i].c == reg[2]);
    }
    return ans;
}

sol task21()
{
    aclear();
    bool ok = true;
    for(int i = 1; i <= n; i++)
    {
        setreg(3, {{0, T[i].a}, {1, T[i].a ^ T[i].b}, {2, T[i].a ^ T[i].c}});
        axor(1, 0);
        axor(2, 0);

        ok &= (__builtin_popcountll(T[i].a ^ T[i].b) <= 2);
        ok &= (__builtin_popcountll(T[i].a ^ T[i].c) <= 2);

        assert(T[i].a == reg[0]);
        assert(T[i].b == reg[1]);
        assert(T[i].c == reg[2]);
    }
    return ans;
}

sol task22()
{
    aclear();
    bool ok = true;
    for(int i = 1; i <= n; i++)
    {
        setreg2(3, {{0, T[i].a}, {1, T[i].a ^ T[i].b}, {2, T[i].a ^ T[i].c}});
        axor(1, 0);
        axor(2, 0);

        ok &= (__builtin_popcountll(T[i].a ^ T[i].b) <= 2);
        ok &= (__builtin_popcountll(T[i].a ^ T[i].c) <= 2);

        assert(T[i].a == reg[0]);
        assert(T[i].b == reg[1]);
        assert(T[i].c == reg[2]);
    }
    return ans;
}

sol task23()
{
    aclear();
    bool ok = true;
    for(int i = 1; i <= n; i++)
    {
        axor(1, 1);
        axor(2, 2);
        setreg3(3, {{0, T[i].a}, {1, T[i].a ^ T[i].b}, {2, T[i].a ^ T[i].c}});
        axor(1, 0);
        axor(2, 0);

        ok &= (__builtin_popcountll(T[i].a ^ T[i].b) <= 2);
        ok &= (__builtin_popcountll(T[i].a ^ T[i].c) <= 2);

        assert(T[i].a == reg[0]);
        assert(T[i].b == reg[1]);
        assert(T[i].c == reg[2]);
    }
    return ans;
}

sol task31()
{
    aclear();
    bool ok = true;
    for(int i = 1; i <= n; i += 8)
    {
        ULL d = T[i].b - T[i].a;
        for(int j = i; j < i + 8; j++)
        {
            ok &= (T[j].a < T[j].b && T[j].b < T[j].c);
            ok &= (T[j].b - T[j].a == d && T[j].c - T[j].b == d);
        }
    }
    if(!ok)
        return sol(MX);
    
    for(int i = 1; i <= n; i += 8)
    {
        ULL d = T[i].b - T[i].a;
        setone2r(3, 0, 1, d);
        assert(d == reg[3]);
        for(int j = i; j < i + 8; j++)
        {
            setone2r(0, 1, 2, T[j].a);
            amov(1, 0);
            aadd(1, 3);
            amov(2, 1);
            aadd(2, 3);

            assert(T[j].a == reg[0]);
            assert(T[j].b == reg[1]);
            assert(T[j].c == reg[2]);              
        }
    }

    return ans;
}

sol task32()
{
    aclear();
    bool ok = true;
    for(int i = 1; i <= n; i += 8)
    {
        ULL d = T[i].b - T[i].a;
        for(int j = i; j < i + 8; j++)
        {
            ok &= (T[j].a < T[j].b && T[j].b < T[j].c);
            ok &= (T[j].b - T[j].a == d && T[j].c - T[j].b == d);
        }
    }
    if(!ok)
        return sol(MX);
    
    for(int i = 1; i <= n; i += 8)
    {
        ULL d = T[i].b - T[i].a;
        setreg3(0, {{3, d}});
        assert(d == reg[3]);
        for(int j = i; j < i + 8; j++)
        {
            setreg3(1, {{0, T[j].a}});
            amov(1, 0);
            aadd(1, 3);
            amov(2, 1);
            aadd(2, 3);

            assert(T[j].a == reg[0]);
            assert(T[j].b == reg[1]);
            assert(T[j].c == reg[2]);              
        }
    }

    return ans;
}

sol task41()
{
    aclear();

    int tmp = 0;
    for(int i = 1; i <= n; i++)
    {
            if(i > 1 && T[i - 1].c == T[i].a)
            {
                amov(0, 2);
                setreg3(3, {{1, T[i].b}, {2, T[i].c}});
                tmp++;
            }
            else
                setreg3(3, {{0, T[i].a}, {1, T[i].b}, {2, T[i].c}});

        assert(T[i].a == reg[0]);
        assert(T[i].b == reg[1]);
        assert(T[i].c == reg[2]);
    }
    //cerr << tmp << "\n\n";

    return ans;
}

sol task42()
{
    aclear();
    bool ok = true;
    for(int i = 1; i <= n; i++)
    {
        if(i > 1 && T[i].a == T[i - 1].c)
        {
            amov(0, 2);
            setreg2(3, {{1, T[i].a ^ T[i].b}, {2, T[i].a ^ T[i].c}});
            axor(1, 0);
            axor(2, 0);
        }
        else
        {
            setreg2(3, {{0, T[i].a}, {1, T[i].a ^ T[i].b}, {2, T[i].a ^ T[i].c}});
            axor(1, 0);
            axor(2, 0);
        }
        
        ok &= (__builtin_popcountll(T[i].a ^ T[i].b) <= 2);
        ok &= (__builtin_popcountll(T[i].a ^ T[i].c) <= 2);

        assert(T[i].a == reg[0]);
        assert(T[i].b == reg[1]);
        assert(T[i].c == reg[2]);
    }
    return ans;
}

sol task43()
{
    aclear();
    bool ok = true;
    for(int i = 1; i <= n; i++)
    {
        if(i > 1 && T[i].a == T[i - 1].c)
        {
            amov(0, 2);
            axor(1, 1);
            axor(2, 2);
            setreg3(3, {{1, T[i].a ^ T[i].b}, {2, T[i].a ^ T[i].c}});
            axor(1, 0);
            axor(2, 0);
        }
        else
        {
            axor(1, 1);
            axor(2, 2);
            setreg3(3, {{0, T[i].a}, {1, T[i].a ^ T[i].b}, {2, T[i].a ^ T[i].c}});
            axor(1, 0);
            axor(2, 0);    
        }
        
        ok &= (__builtin_popcountll(T[i].a ^ T[i].b) <= 2);
        ok &= (__builtin_popcountll(T[i].a ^ T[i].c) <= 2);

        assert(T[i].a == reg[0]);
        assert(T[i].b == reg[1]);
        assert(T[i].c == reg[2]);
    }
    return ans;
}

sol task51()
{
    aclear();
    bool ok = true;
    ULL k = T[1].a + T[1].b + T[1].c;
    for(int i = 1; i <= n; i++)
        ok &= (k == T[i].a + T[i].b + T[i].c);
    if(!ok)
        return sol(MX);
    
    setone2r(3, 0, 1, k);

    for(int i = 1; i <= n; i++)
    {
        ULL a = min({T[i].a, T[i].b, T[i].c});
        ULL c = max({T[i].a, T[i].b, T[i].c});
        ULL b = T[i].a + T[i].b + T[i].c - a - c;
        setreg(2, {{0, a}, {1, b}});
        amov(2, 3);
        asub(2, 0);
        asub(2, 1);

        assert(a == reg[0]);
        assert(b == reg[1]);
        assert(c == reg[2]);          
    }

    return ans;
}

sol task52()
{
    aclear();
    bool ok = true;
    ULL k = T[1].a + T[1].b + T[1].c;
    for(int i = 1; i <= n; i++)
        ok &= (k == T[i].a + T[i].b + T[i].c);
    if(!ok)
        return sol(MX);
    
    setone2r(3, 0, 1, k);

    for(int i = 1; i <= n; i++)
    {
        ULL a = min({T[i].a, T[i].b, T[i].c});
        ULL c = max({T[i].a, T[i].b, T[i].c});
        ULL b = T[i].a + T[i].b + T[i].c - a - c;
        setreg2(2, {{0, a}, {1, b}});
        amov(2, 3);
        asub(2, 0);
        asub(2, 1);

        assert(a == reg[0]);
        assert(b == reg[1]);
        assert(c == reg[2]);          
    }

    return ans;
}

sol task53()
{
    aclear();
    bool ok = true;
    ULL k = T[1].a + T[1].b + T[1].c;
    for(int i = 1; i <= n; i++)
        ok &= (k == T[i].a + T[i].b + T[i].c);
    if(!ok)
        return sol(MX);
    
    setone2r(3, 0, 1, k);

    for(int i = 1; i <= n; i++)
    {
        ULL a = min({T[i].a, T[i].b, T[i].c});
        ULL c = max({T[i].a, T[i].b, T[i].c});
        ULL b = T[i].a + T[i].b + T[i].c - a - c;
        setreg2(2, {{0, a}, {1, b ^ a}});
        axor(1, 0);
        amov(2, 3);
        asub(2, 0);
        asub(2, 1);

        assert(a == reg[0]);
        assert(b == reg[1]);
        assert(c == reg[2]);          
    }

    return ans;
}

sol task54()
{
    aclear();
    bool ok = true;
    ULL k = T[1].a + T[1].b + T[1].c;
    for(int i = 1; i <= n; i++)
        ok &= (k == T[i].a + T[i].b + T[i].c);
    if(!ok)
        return sol(MX);
    
    setone2r(3, 0, 1, k);

    for(int i = 1; i <= n; i++)
    {
        ULL a = min({T[i].a, T[i].b, T[i].c});
        ULL c = max({T[i].a, T[i].b, T[i].c});
        ULL b = T[i].a + T[i].b + T[i].c - a - c;
        setreg3(2, {{0, a}, {1, b}});
        amov(2, 3);
        asub(2, 0);
        asub(2, 1);

        assert(a == reg[0]);
        assert(b == reg[1]);
        assert(c == reg[2]);          
    }

    return ans;
}

int main()
{
    _upgrade
    
    read();
    vector < sol > sols;
 
    sols.push_back(task11());
    sols.push_back(task12());
    sols.push_back(task13());
    sols.push_back(task14());

    sols.push_back(task21());
    sols.push_back(task22());
    sols.push_back(task23());
    
    sols.push_back(task31());
    sols.push_back(task32());

    sols.push_back(task41());
    sols.push_back(task42());
    sols.push_back(task43());

    sols.push_back(task51());
    sols.push_back(task52());
    sols.push_back(task53());
    sols.push_back(task54());
    
    sort(all(sols), [&](const sol &s1, const sol &s2) {
        return sz(s1) < sz(s2);
    });
    
    //for(int i = 1; i <= 8; i++) cerr << fixed << setprecision(2) << avg_n[i] / avg_d[i] << "\n"; cerr << "\n";
    
    assert(sz(sols[0]) > 0);
    print(sols[0]);

	return 0;
}
