# Heights and Pairs

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abl/tasks/abl_f

$ 2N $ 人の人 ($ 1 $ 番から $ 2N $ 番まで) がいます。 人 $ i $ の身長は $ h_i $ です。

以下の条件を満たすように、$ N $ 個の人のペアを作る方法は何通りありますか？ 答えを modulo $ 998,244,353 $ で求めてください。

- どの人もちょうど一つのペアに含まれる。
- どのペアも、そのペアに属する二人の人の身長が異なる。

ある $ p $ と $ q $ に対し、人 $ p $ と人 $ q $ がペアになったかどうかが異なる場合、異なる方法であるとみなします。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 50,000 $
- $ 1\ \leq\ h_i\ \leq\ 100,000 $
- 入力は全て整数である。

### Sample Explanation 1

二通りあります: - ペア (人 $ 1 $, 人 $ 3 $) とペア (人 $ 2 $, 人 $ 4 $) を作る。 - ペア (人 $ 1 $, 人 $ 4 $) とペア (人 $ 2 $, 人 $ 3 $) を作る。

## 样例 #1

### 输入

```
2
1
1
2
3```

### 输出

```
2```

## 样例 #2

### 输入

```
5
30
10
20
40
20
10
10
30
50
60```

### 输出

```
516```

# 题解

## 作者：songhongyi (赞：1)

题意：求有多少中完美匹配使得每组匹配的两个点权值都不相同。

考虑容斥。首先有，$2n$ 个数完美匹配方案数为 $\dfrac{(2n)!}{n!2^n}$。设其为 $P_n$。

设 $f_i$ 表示存在 $i$ 对相同匹配的方案数。我们只需要钦定 $i$ 对相同，剩下的随意匹配，因此只需要考虑 $f'_i$ 表示有多少种方法钦定出 $i$ 对相同的匹配，则自然有 $f_i = f'_i \cdot P_{n-i}$。

接下来考虑如何求 $f'_i$。不妨设 $c_i$ 表示 $i$ 在原序列中的出现次数，$a_i$ 表示 $i$ 选了多少组。那么有：
$$
f'_i = \sum_{\sum a_j=i} \prod \binom {c_j}{2a_j}P(a_j)
$$
注意到这个式子的形式，这是一个经典的多项式卷积（P6012）考虑：
$$
g_i = \sum \binom{c_i}{2j}P(j) \cdot x^j
$$
则有：
$$
f'_i = [x^i]\prod g_j
$$
而注意到 $\sum c_i =2n$，因此可以用启发式合并的方法计算这个卷积（即使用优先队列每次把大小最小的两个合并成一个），其复杂度为 $O(n \log^2 n)$。

而根据我们的推导，最终答案为：
$$
\sum_{i=0}^{n}(-1)^if_i = \sum_{i=0}^{n}(-1)^i\cdot f'_iP_{n-i}
$$
注意正确地使用 `priority_queue`。

```cpp
//
// Problem: Heights and Pairs
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_abl_f
// Memory Limit: 1 MB
// Time Limit: 2000 ms

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int pmod = 998244353;
template < unsigned pmod > struct modint
{
    unsigned v;
    modint() : v( 0 ) {}
    template < class T > modint( T x )
    {
        x %= ( int )pmod, v = x < 0 ? x + pmod : x;
    }
    modint operator+() const
    {
        return *this;
    }
    modint operator-() const
    {
        return modint( 0 ) - *this;
    }
    modint inv() const
    {
        return qpow( *this, pmod - 2 );
    }
    friend int raw( const modint& self )
    {
        return self.v;
    }
    template < class T > friend modint qpow( modint a, T b )
    {
        modint r = 1;
        for ( ; b; b >>= 1, a *= a )
            if ( b & 1 )
                r *= a;
        return r;
    }
    modint& operator+=( const modint& rhs )
    {
        if ( v += rhs.v, v >= pmod )
            v -= pmod;
        return *this;
    }
    modint& operator-=( const modint& rhs )
    {
        if ( v -= rhs.v, v >= pmod )
            v += pmod;
        return *this;
    }
    modint& operator*=( const modint& rhs )
    {
        v = 1ull * v * rhs.v % pmod;
        return *this;
    }
    modint& operator/=( const modint& rhs )
    {
        return *this *= rhs.inv();
    }
    friend modint operator+( modint lhs, const modint& rhs )
    {
        return lhs += rhs;
    }
    friend modint operator-( modint lhs, const modint& rhs )
    {
        return lhs -= rhs;
    }
    friend modint operator*( modint lhs, const modint& rhs )
    {
        return lhs *= rhs;
    }
    friend modint operator/( modint lhs, const modint& rhs )
    {
        return lhs /= rhs;
    }
    friend bool operator==( const modint& lhs, const modint& rhs )
    {
        return lhs.v == rhs.v;
    }
    friend bool operator!=( const modint& lhs, const modint& rhs )
    {
        return lhs.v != rhs.v;
    }
};
typedef modint< pmod > mint;
int glim( const int& x )
{
    return 1 << ( 32 - __builtin_clz( x ) );
}
int bitctz( const int& x )
{
    return __builtin_ctz( x );
}
vector< mint > getWns( mint G )
{
    vector< mint > wns( 23 );
    int cnt = 0;
    generate( wns.begin(), wns.end(), [=]() mutable { return qpow( G, ( pmod - 1 ) >> ++cnt ); } );
    return wns;
}
const vector< mint > wns = getWns( 3 );
void ntt( vector< mint >& a, const int& op )
{
    const int n = a.size();
    for ( int i = 1, r = 0; i < n; i++ )
    {
        r ^= n - ( 1 << ( bitctz( n ) - bitctz( i ) - 1 ) );
        if ( i < r )
            swap( a[ i ], a[ r ] );
    }
    vector< mint > w( n );
    for ( int k = 1, len = 2; len <= n; k <<= 1, len <<= 1 )
    {
        const mint wn = wns[ bitctz( k ) ];
        for ( int i = raw( w[ 0 ] = 1 ); i < k; i++ )
            w[ i ] = w[ i - 1 ] * wn;
        for ( int i = 0; i < n; i += len )
        {
            for ( int j = 0; j < k; j++ )
            {
                const mint x = a[ i + j ], y = a[ i + j + k ] * w[ j ];
                a[ i + j ] = x + y, a[ i + j + k ] = x - y;
            }
        }
    }
    if ( op == -1 )
    {
        const mint iz = mint( 1 ) / n;
        for ( int i = 0; i < n; i++ )
            a[ i ] *= iz;
        reverse( a.begin() + 1, a.end() );
    }
}
vector< mint > multiple( vector< mint > a, vector< mint > b )
{
    int rLen = a.size() + b.size() - 1, len = glim( rLen );
    a.resize( len ), ntt( a, 1 );
    b.resize( len ), ntt( b, 1 );
    for ( int i = 0; i < len; i++ )
        a[ i ] *= b[ i ];
    ntt( a, -1 ), a.resize( rLen );
    return a;
}
const int MAXN = 1e5 + 10;
int c[ MAXN ];
mint fac[ MAXN ], ifac[ MAXN ], pw[ MAXN ], P[ MAXN ];
void init( int n )
{
    fac[ 0 ] = 1;
    pw[ 0 ] = 1;
    for ( int i = 1; i <= n; i++ )
    {
        fac[ i ] = fac[ i - 1 ] * i;
        pw[ i ] = 2 * pw[ i - 1 ];
    }
    ifac[ 0 ] = ifac[ 1 ] = 1;
    for ( int i = 2; i <= n; i++ )
    {
        ifac[ i ] = ( pmod - pmod / i ) * ifac[ pmod % i ];
    }
    for ( int i = 1; i <= n; i++ )
    {
        ifac[ i ] = ifac[ i - 1 ] * ifac[ i ];
    }
    for ( int i = 0; i <= n; i++ )
    {
        P[ i ] = fac[ i + i ] * ifac[ i ] / pw[ i ];
    }
}
mint C( int n, int m )
{
    if ( m > n or m < 0 )
    {
        return 0;
    }
    return fac[ n ] * ifac[ n - m ] * ifac[ m ];
}
auto cmp = []( auto a, auto b ) { return a.size() > b.size(); };
priority_queue< vector< mint >, vector< vector< mint > >,
                function< int( vector< mint >, vector< mint > ) > >
    q( cmp );
int main()
{
    int n;
    cin >> n;
    init( n + n );
    for ( int i = 1; i <= n + n; i++ )
    {
        int t;
        cin >> t;
        c[ t ]++;
    }
    q.emplace( vector< mint >( { 1 } ) );
    for ( int i = 1; i <= 1e5; i++ )
    {
        if ( c[ i ] )
        {
            vector< mint > tmp( c[ i ] / 2 + 1 );
            for ( int j = 0; j + j <= c[ i ]; j++ )
            {
                tmp[ j ] = C( c[ i ], j + j ) * P[ j ];
            }
            q.emplace( tmp );
        }
    }
    while ( q.size() != 1 )
    {
        auto a = q.top();
        q.pop();
        auto b = q.top();
        q.pop();
        q.emplace( multiple( a, b ) );
    }
    auto res = q.top();
    mint ans = 0;
    for ( int i = 0; i < res.size() and i <= n; i++ )
    {
        if ( i & 1 )
        {
            ans -= res[ i ] * P[ n - i ];
        }
        else
        {
            ans += res[ i ] * P[ n - i ];
        }
    }
    cout << ans.v << endl;
}
```

---

