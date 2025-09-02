# painting

## 题目背景

Wolfycz很喜欢画画（雾

## 题目描述

Wolfycz喜欢网格图，他希望在网格图上画上一些黑格子，使得每一列都恰好有一个黑格子。但是黑格子太乱了不好看，所以Wolfycz希望黑格子按列号依次连线是下降的，具体来讲，每列黑格子所在行号不得小于前一列黑格子所在行号（我们令左上角为第一行第一列）

Wolfycz觉得这样画出来的图非常漂亮，但是Wolfycz有时候觉得连线要严格下降才好看（即每列黑格子所在行号必须大于前一列黑格子所在行号），有时候觉得连线只要不上升就好看（即每列黑格子所在行号不得小于前一列黑格子所在行号）。现在Wolfycz想知道，对于一个$N×M$的网格图，他能画出多少个好看的图？两个图不相同，当且仅当存在某一列的黑格子，它在两个图中对应的行号不同

UPD：$N$行$M$列

## 说明/提示

对于$20\%$的数据，$T\leqslant 5,N\leqslant 8,M\leqslant 8$

对于另外$20\%$的数据，$N=1$或$M=1$

对于另外$20\%$的数据，$N\leqslant 10^6,M\leqslant 10^6$

对于$100\%$的数据，$T\leqslant 50,N\leqslant 10^{18},M\leqslant 10^6$

## 样例 #1

### 输入

```
5
5 2 1
5 3 0
3 4 0
8 4 1
6 2 1```

### 输出

```
10
35
15
70
15```

# 题解

## 作者：xiaomuyun (赞：8)

[题目传送门](https://www.luogu.com.cn/problem/P5135)
## 前置知识

众所周知，组合有两种：非重组合和可重组合。非重组合的公式是 $C^m_n$，可重组合的是 $C^m_{n+m-1}$。既然已经在题目标签里看到了“组合数学”（？），我们就可以想办法将这两种组合与这道题结合在一起。

## 题目分析

我们通过 $opt$ 的值来分类讨论。

### $opt$ 的值为 $1$

因为 Wolfycz 想要的是 $m$ 个不相等的行数，我们可以把连线忽略不管，因为我们只要得到了 $m$ 个不相等的行数，将它们排序一下就是严格下降的连线了。因此可以发现，这不就是求非重组合吗？的确，只要用一下上文所说的非重组合的公式即可（刚刚说的排序其实是题外话，因为我们并不需要求出一个组合，只是求组合数而已）。

### $opt$ 的值为 $0$

和上面那种情况差不多，我们看一下就可以发现，随便弄出 $m$ 个可以相等的行数，然后将它们排一下序，它们就肯定会变成不上升的连线。因此这就是可重组合。和上面的情况一样，用可重组合的公式（$C^m_{n+m-1}$）即可。

## 代码实现

（下面用 Lucas 定理其实是大材小用，把 Lucas 部分删掉直接用普通的 $C$ 算组合数应该也可以）

```cpp
#include<cstdio>
#define int long long
using namespace std;
const int maxn=1e6;
const int mod=1e9+7;
int t,n,m,opt,inv[maxn+1];
inline int pow(int a,int b,int p){
	int res=1;
	while(b){
		if(b&1) res=res*a%p;
		b>>=1,a=a*a%p;
	}
	return res;
}
inline int C(int n,int m,int p){
	if(m>n) return 0;
	int x=1,y=1;
	for(int i=1;i<=m;++i) x=x*(n-i+1)%p,y=y*i%p;
	return x*pow(y,p-2,p)%p;//用逆元求组合数
}
inline int Lucas(int n,int m,int p){
	if(m==0) return 1;
	return C(n%p,m%p,p)*Lucas(n/p,m/p,p)%p;
}
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld%lld",&n,&m,&opt);
		if(opt==1) printf("%lld\n",Lucas(n,m,mod));
		else printf("%lld\n",Lucas(n+m-1,m,mod));
	}
	return 0;
}
```

## 写在最后

希望这篇题解能让大家有所收获，有所收获的同时不要忘了留下一个免费的赞（

---

## 作者：daniEl_lElE (赞：5)

基础组合数学，难度貌似没有紫吧（

## 分析

对于 $opt=0,1$ 分别考虑一下。

### case 1: $opt=1$

考虑从 $n$ 行中选择不同的 $m$ 行。此时，将所有选出的行排序，我们发现正好每一行可以对应一列的选择。所以，当 $opt=1$ 时，答案就是从 $n$ 行中选择不同的 $m$ 行的方案数，也就是 $C_n^m$。

### case 2: $opt=0$

考虑从 $n$ 行中选择可以相同的 $m$ 行。此时，将所有选出的行排序，我们发现正好每一行可以对应一列的选择。所以，当 $opt=0$ 时，答案就是从 $n$ 行中选择可以相同的 $m$ 行的方案数，也就是 $C_{n+m-1}^m$。

其实，以上两个 $opt=0,1$ 正好对应着排列组合两种选择方案，也是比较基础的排列组合内容。

在实现时，可以直接按照最基本的计算 $C_i^j=\dfrac{i\times(i-1)\times(i-2)\times\dots\times(i-j+1)}{j!}$。单次询问复杂度 $O(m)$，即可通过此题。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int __int128
using namespace std;
int m[15],n;
int fac[1000005],inv[1000005];
const int mod=1000000007;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return ans;
}
signed main(){
	long long t;
	cin>>t;
	while(t--){
		long long N,M,OPT;
		cin>>N>>M>>OPT;
		int n=N,m=M,opt=OPT;
		if(!opt){
			n=n+m-1;
		}
		int cur=1;
		for(int i=n;i>=n-m+1;i--){
			cur*=i;
			cur%=mod;
		}
		int dvd=1;
		for(int i=1;i<=m;i++){
			dvd*=i;
			dvd%=mod;
		}
		long long ans=(cur*qp(dvd,mod-2))%mod;
		cout<<ans<<endl;
	}
    return 0;
}
```

---

## 作者：Wolfycz (赞：3)

我们考虑转化题意，题目要求

$$\sum\limits_{i_1=1}^n\sum\limits_{i_2=i_1+opt}^n...\sum\limits_{i_m=i_{m-1}+opt}^n1$$

然后我们分情况讨论一下

- 若opt=1，那么答案即为$\binom{n}{m}$
- 若opt=0，那么序列$i_1,i_2,...,i_m$必然是个不减序列，我们令$A_k=i_k+k$，那么序列$A$必然是个严格递增序列，并且取值在$(1,n+m]$，所以答案即为$\binom{n+m-1}{m}$（插板法同样可以解决）

然后注意求$\binom{n}{m}$需要for循环，复杂度$O(Tm)$

```cpp
/*program from Wolfycz*/
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define inf 0x7f7f7f7f
using namespace std;
typedef long long ll;
typedef unsigned int ui;
typedef unsigned long long ull;
inline char gc(){
    static char buf[1000000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
inline int frd(){
    int x=0,f=1;char ch=gc();
    for (;ch<'0'||ch>'9';ch=gc())	if (ch=='-')    f=-1;
    for (;ch>='0'&&ch<='9';ch=gc())	x=(x<<1)+(x<<3)+ch-'0';
    return x*f;
}
inline int read(){
    int x=0,f=1;char ch=getchar();
    for (;ch<'0'||ch>'9';ch=getchar())	if (ch=='-')	f=-1;
    for (;ch>='0'&&ch<='9';ch=getchar())	x=(x<<1)+(x<<3)+ch-'0';
    return x*f;
}
inline void print(int x){
    if (x<0)    putchar('-'),x=-x;
    if (x>9)	print(x/10);
    putchar(x%10+'0');
}
const int N=1e6,p=1e9+7;
int inv[N+10];
int C(ll n,int m){
    if (n<m)	return 0;
    int res=1;
    for (int i=1;i<=m;i++)	res=1ll*res*((n-i+1)%p)%p*inv[i]%p;
    return res;
}
int main(){
    inv[1]=1;
    for (int i=2;i<=N;i++)	inv[i]=1ll*(p-p/i)*inv[p%i]%p;
    for (int Data=read();Data;Data--){
        ll n; int m,opt;
        scanf("%lld%d%d",&n,&m,&opt);
        printf("%d\n",opt?C(n,m):C(n+m-1,m));
    }
    return 0;
}
```

---

## 作者：Tzs_yousa (赞：1)

~~这题，紫的？？算了不管了反正这样水个紫题解也不错~~
## 题意
在每一列涂一个黑格子，使每列黑格子连起来严格递减或非严格递减。
## 解法
先说严格递减的情况，这种情况我们是从 $n$ 行种找出 $m$ 行来涂黑，同时保证，这 $m$ 行两两之间都不相等，所以就是 $C(n,m)$。

然后是非严格递减的情况，当前列和下一列可能相等可能不等，那我们就相当于总共多了 $m - 1$ 种选择；另一种解释“隔板法”：除了第一列，假设后面的每一列都必定下降一个，然后就没有相等的可能了，于是就是 $C(n + m - 1, m)$，这个东西也不好解释，可以去学一学高中数学，感受一下实际意义能便于理解。

## lucas 定理
可以看到 $n$ 非常大，随便一乘就爆了，而且模数事质数，那我们就可以用卢卡斯定理啊。

那就直接上定理。

$C(n, m) = C(\frac{n}{p}, \frac{m}{p})$ $\times$ $C(n\ \bmod p, m \bmod p)$

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
const int mod = 1e9 + 7;
using namespace std;
int t, n, m, op, fac[1000010];
int quick_pow(int a, int b)
{
	int res = 1;
	while(b)
	{
		if(b & 1) (res *= a) %= mod;
		(a *= a) %= mod;
		b >>= 1;
	}
	return res;
}
int C(int x, int y)
{
	if(x < y) return 0;
	if(x < mod && y < mod)
	{
		int a = 1, b = 1;
		for (int i = x; i >= x - y + 1; i--) (a *= i) %= mod;
		return a * quick_pow(fac[y], mod - 2) % mod;//费马小定理求逆元
	}
	return C(x / mod, y / mod) * C(x % mod, y % mod) % mod;
}
signed main()
{
	scanf("%lld", &t);
	fac[0] = fac[1] = 1;
	for (int i = 2; i <= 1000000; i++) fac[i] = (fac[i - 1] * i) % mod;
	while(t--)
	{
		scanf("%lld%lld%lld", &n, &m, &op);
		if(op == 1) printf("%lld\n", C(n, m));
		else printf("%lld\n", C(n + m - 1, m));
	}
	return 0;
}
```


---

## 作者：littlez_meow (赞：0)

二合一题。

来点大材小用（？）的推式子。

[题目指路](https://www.luogu.com.cn/problem/P5135)。

## 思路

把每列黑格子的行号记录下来，得到一个值域在 $[1,n]$，长为 $m$ 的序列。

### $opt=0$

序列单调不降，直接意识到这是一个 $1$ 行 $m$ 列的半标准杨表。

使用[半标准杨表钩长公式](https://en.wikipedia.org/wiki/Hook_length_formula#Related_formulas)，答案为：

$$\prod\limits_{i=1}^m\dfrac{n+i-1}{m-i+1}$$

上下展开，得到：

$$\dfrac{n\times(n+1)\times\cdots\times(n+m-1)}{m!}$$

发现其为组合数 $\dbinom{n+m-1}{m}$。

### $opt=1$

考虑将第 $m$ 个数减 $0$，第 $m-1$ 个数减 $1$……第 $m-i$ 个数减 $i$。这样得到的序列变成了值域为 $[1,n-m+1]$ 的单调不降序列，套用上面的推导得到答案为 $\dbinom{n}{m}$。

计算组合数暴力乘，时间复杂度 $O(Tm)$。

用隔板法也可以推，但是这种办法能解决[二维情况](https://www.luogu.com.cn/problem/P8114)。

## 代码

```cpp
#include<bits/stdc++.h>
#define F(i,a,b) for(int i(a),i##i##end(b);i<=i##i##end;++i)
#define R(i,a,b) for(int i(a),i##i##end(b);i>=i##i##end;--i) 
#define ll long long
using namespace std;
const int MOD=1e9+7;
int m;
ll n;
bool opt;
inline ll qpow(ll base,int expo){
	ll res(1);
	while(expo){
		(expo&1)&&(res=res*base%MOD);
		base=base*base%MOD,expo>>=1;
	}
	return res;
}
inline ll C(ll x,int y){
	ll ans(1),inv(1);
	F(i,0,y-1){
		ans=(x-i)%MOD*ans%MOD;
		inv=inv*(i+1)%MOD;
	}
	return ans*qpow(inv,MOD-2)%MOD;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int T;
	for(cin>>T;T;--T){
		cin>>n>>m>>opt;
		cout<<(opt?C(n,m):C(n+m-1,m))<<"\n";
	} 
    return 0;
}
```

不喜勿喷 qwq~

---

## 作者：Ruiqun2009 (赞：0)

~~这题远远没有紫的难度~~

若 `opt=1`，那么很明显是要我们求 $\binom{n}{m}$。

若 `opt=0`，我们可以先求出连线严格下降的方案数，即上一问。答案是 $\binom{n}{m}$。

然后我们考虑将相同的元素插进这个序列。使用插板法可得答案是 $\binom{n+m-1}{m}$。

我的实现方式是使用定义 $\binom{n}{m}=\frac{\prod\limits_{i=m}^ni}{m!}$。上面直接暴力乘，下面[快速阶乘算法](https://www.luogu.com.cn/blog/SomeMusical-MathBoy/fast-factorial) $\Theta(\sqrt{w}\log w)$ 预处理，$\Theta(\sqrt w)$ 单次询问（其中 $w$ 为 $m$ 的值域）。

由于本题模数固定，可以使用编译器自带取模优化（如果写三模数 NTT 那么内部可以采用蒙哥马利模乘加速）。

代码有一点长。已省略 `cin,cout` 的实现。
```cpp
// #define __MY_USE_LONG_DOUBLE__
// @code long double is not used in this problem
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string.h>
#include <type_traits>
#include <unordered_map>
#include <cstdint>
#include <utility>
// here is cin,cout
namespace OY {
template <typename _ModType, _ModType _P>
struct Modular {
    static constexpr _ModType mod() { return _P; }
    static constexpr _ModType mod(uint64_t __a) { return __a % _P; }
    static constexpr _ModType plus(_ModType __a, _ModType __b) {
        if (__a += __b; __a >= _P) __a -= _P;
        return __a;
    }
    static constexpr _ModType minus(_ModType __a, _ModType __b) {
        if (__a += _P - __b; __a >= _P) __a -= _P;
        return __a;
    }
    static constexpr _ModType multiply(uint64_t __a, uint64_t __b) {
        if constexpr (std::is_same<_ModType, uint64_t>::value) return multiply_ld(__a, __b);
        else return multiply_64(__a, __b);
    }
    static constexpr _ModType multiply_64(uint64_t __a, uint64_t __b) { return mod(__a * __b); }
    static constexpr _ModType multiply_128(uint64_t __a, uint64_t __b) { return __uint128_t(__a) * __b % _P; }
    static constexpr _ModType multiply_ld(uint64_t __a, uint64_t __b) {
        if (std::__countl_zero(__a) + std::__countl_zero(__b) >= 64) return multiply_64(__a, __b);
        int64_t res = __a * __b - uint64_t(1.L / _P * __a * __b) * _P;
        if (res < 0) res += _P;
        else if (res >= _P) res -= _P;
        return res;
    }
    static constexpr _ModType pow(uint64_t __a, uint64_t __n) {
        if constexpr (std::is_same<_ModType, uint64_t>::value) return pow_ld(__a, __n);
        else return pow_64(__a, __n);
    }
    static constexpr _ModType pow_64(uint64_t __a, uint64_t __n) {
        _ModType res = 1, b = mod(__a);
        while (__n) {
            if (__n & 1) res = multiply_64(res, b);
            b = multiply_64(b, b);
            __n >>= 1;
        }
        return res;
    }
    static constexpr _ModType pow_128(uint64_t __a, uint64_t __n) {
        _ModType res = 1, b = mod(__a);
        while (__n) {
            if (__n & 1) res = multiply_128(res, b);
            b = multiply_128(b, b);
            __n >>= 1;
        }
        return res;
    }
    static constexpr _ModType pow_ld(uint64_t __a, uint64_t __n) {
        _ModType res = 1, b = mod(__a);
        while (__n) {
            if (__n & 1) res = multiply_ld(res, b);
            b = multiply_ld(b, b);
            __n >>= 1;
        }
        return res;
    }
    template <typename _Tp>
    static constexpr _Tp divide(_Tp __a) { return __a / _P; }
    template <typename _Tp>
    static constexpr std::pair<_Tp, _Tp> divmod(_Tp __a) {
        _Tp quo = __a / _P, rem = __a - quo * _P;
        return {quo, rem};
    }
};
template <uint32_t _P>
using Modular32 = Modular<uint32_t, _P>;
template <uint64_t _P>
using Modular64 = Modular<uint64_t, _P>;
}
namespace OY {
template <typename _ModType, _ModType _P, bool _IsPrime = false>
struct StaticModInt {
    using mint = StaticModInt<_ModType, _P, _IsPrime>;
    _ModType m_val;
    static_assert(_P > 1 && _P < 1ull << 63);
    constexpr StaticModInt() : m_val(0) {}
    template <typename _Tp, std::enable_if_t<std::is_signed_v<_Tp>, bool> = true>
    constexpr StaticModInt(_Tp __val) : m_val(0) {
        int64_t x = int64_t(__val) % int64_t(mod());
        if (x < 0) x += mod();
        m_val = x;
    }
    template <typename _Tp, std::enable_if_t<std::is_unsigned_v<_Tp>, bool> = true>
    constexpr StaticModInt(_Tp __val) : m_val(__val % mod()) {}
    static constexpr mint raw(_ModType __val) {
        mint res;
        res.m_val = __val;
        return res;
    }
    static constexpr _ModType mod() { return _P; }
    constexpr _ModType val() const { return m_val; }
    constexpr mint pow(uint64_t __n) const { return Modular<_ModType, _P>::pow(m_val, __n); }
    constexpr mint inv() const {
        if constexpr (_IsPrime) return inv_Fermat();
        else return inv_exgcd();
    }
    constexpr mint inv_exgcd() const {
        _ModType x = mod(), y = m_val, m0 = 0, m1 = 1;
        while (y) {
            _ModType z = x / y;
            x -= y * z;
            m0 -= m1 * z;
            std::swap(x, y);
            std::swap(m0, m1);
        }
        if (m0 >= mod()) m0 += mod() / x;
        return raw(m0);
    }
    constexpr mint inv_Fermat() const { return pow(mod() - 2); }
    constexpr mint &operator++() {
        if (++m_val == mod()) m_val = 0;
        return *this;
    }
    constexpr mint &operator--() {
        if (m_val == 0) m_val = mod();
        m_val--;
        return *this;
    }
    constexpr mint operator++(int) {
        mint old(*this);
        ++*this;
        return old;
    }
    constexpr mint operator--(int) {
        mint old(*this);
        --*this;
        return old;
    }
    constexpr mint &operator+=(const mint &__other) {
        m_val = Modular<_ModType, _P>::plus(m_val, __other.m_val);
        return *this;
    }
    constexpr mint &operator-=(const mint &__other) {
        m_val = Modular<_ModType, _P>::minus(m_val, __other.m_val);
            return *this;
    }
    constexpr mint &operator*=(const mint &__other) {
        m_val = Modular<_ModType, _P>::multiply(m_val, __other.m_val);
        return *this;
    }
    constexpr mint &operator/=(const mint &__other) { return *this *= __other.inv(); }
    constexpr mint operator+() const { return *this; }
    constexpr mint operator-() const { return raw(m_val ? mod() - m_val : 0); }
    constexpr bool operator==(const mint &__other) const { return m_val == __other.m_val; }
    constexpr bool operator!=(const mint &__other) const { return m_val != __other.m_val; }
    constexpr bool operator<(const mint &__other) const { return m_val < __other.m_val; }
    constexpr bool operator>(const mint &__other) const { return m_val > __other.m_val; }
    constexpr bool operator<=(const mint &__other) const { return m_val <= __other.m_val; }
    constexpr bool operator>=(const mint &__other) const { return m_val <= __other.m_val; }
    template <typename _Tp>
    constexpr explicit operator _Tp() const { return _Tp(m_val); }
    constexpr friend mint operator+(const mint &a, const mint &b) { return mint(a) += b; }
    constexpr friend mint operator-(const mint &a, const mint &b) { return mint(a) -= b; }
    constexpr friend mint operator*(const mint &a, const mint &b) { return mint(a) *= b; }
    constexpr friend mint operator/(const mint &a, const mint &b) { return mint(a) /= b; }
    template <typename _Istream>
    friend _Istream &operator>>(_Istream &is, mint &self) { return is >> self.m_val; }
    template <typename _Ostream>
    friend _Ostream &operator<<(_Ostream &os, const mint &self) { return os << self.m_val; }
};
template <uint32_t _P, bool _IsPrime>
using StaticModInt32 = StaticModInt<uint32_t, _P, _IsPrime>;
template <uint64_t _P, bool _IsPrime>
using StaticModInt64 = StaticModInt<uint64_t, _P, _IsPrime>;
}
using mint = OY::StaticModInt32<1000000007, true>;
using std::vector;
#ifdef __MY_USE_LONG_DOUBLE__
#define double long double
#define llround llroundl
const double pi = acosl(-1.0L);
const double two = 2.0L;
#else
const double pi = acos(-1.0);
const double two = 2.0;
#endif
template <typename T>
struct cp_base {
    T m_real, m_imag;
    inline constexpr cp_base(const T& r, const T& i) : m_real(r), m_imag(i) {}
    inline constexpr cp_base(const T& r = T()) : m_real(r), m_imag(0) {}
    inline constexpr cp_base<T> operator+(const cp_base<T> &o) const
    { return cp_base<T>(m_real + o.m_real, m_imag + o.m_imag); }
    inline constexpr cp_base<T> operator-(const cp_base<T> &o) const
    { return cp_base<T>(m_real - o.m_real, m_imag - o.m_imag); }
    inline constexpr cp_base<T> operator*(const cp_base<T> &o) const
    { return cp_base<T>(m_real * o.m_real - m_imag * o.m_imag, m_real * o.m_imag + m_imag * o.m_real); }
    inline constexpr cp_base<T> conj() const
    { return cp_base<T>(m_real, -m_imag); }
    inline constexpr T real() const { return m_real; }
    inline constexpr T imag() const { return m_imag; }
    inline constexpr T& real() { return m_real; }
    inline constexpr T& imag() { return m_imag; }
};
typedef cp_base<double> cp;
static vector<size_t> rev;
vector<cp> omegas;
inline void get_rev(size_t len, int x) {
    if (len == rev.size()) return;
    rev.resize(len);
    for (size_t i = 0; i < len; i++) rev[i] = rev[i >> 1ull] >> 1ull | (i & 1ull) << x;
    omegas.resize(len);
    for (size_t i = 0; i < len; i++) omegas[i] = cp(std::cos(two * pi / len * i), std::sin(two * pi / len * i));
}
inline void FFT(vector<cp>& a, size_t n, bool type) {
    for (size_t i = 1ull; i < n; ++i) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
    for (size_t i = 2ull; i <= n; i <<= 1ull) for (size_t j = 0ull, l = (i >> 1ull), ch = n / i; j < n; j += i) for (size_t k = j, now = 0ull; k < j + l; k++) {
        cp x = a[k], y = a[k + l] * (type ? omegas[now] : omegas[now].conj());
        a[k] = x + y;
        a[k + l] = x - y;
        now += ch;
    }
    if (!type) {
        for (size_t i = 0; i < n; i++) {
            a[i].real() /= n;
            a[i].imag() /= n;
        }
    }
}
inline void mul(size_t n, size_t m, const vector<mint>& a, const vector<mint>& b, vector<mint>& c, size_t len) {
    const size_t up = sqrt(mint::mod());
    mint v1, v2, v3;
    vector<cp> P(len, cp(0, 0)), Q(len, cp(0, 0)), R(len, cp(0, 0));
    for (size_t i = 0ull; i < n; i++) P[i] = cp(a[i].val() % up, a[i].val() / up);
    for (size_t i = 0ull; i < m; i++) R[i] = cp(b[i].val() % up, b[i].val() / up);
    FFT(P, len, true);
    FFT(R, len, true);
    Q[0] = P[0].conj();
    for (size_t i = 1ull; i < len; i++) Q[i] = P[len - i].conj();
    for (size_t i = 0ull; i < len; i++) {
        P[i] = P[i] * R[i];
        Q[i] = Q[i] * R[i];
    }
    FFT(P, len, false);
    FFT(Q, len, false);
    c.resize(n + m - 1);
    for (size_t i = 0ull; i < n + m - 1; i++) {
        v1 = llround((P[i].real() + Q[i].real()) / two);
        v2 = llround((Q[i].real() - P[i].real()) / two);
        v3 = llround(P[i].imag());
        c[i] = v1 + v2 * up * up + v3 * up;
    }
}
static vector<mint> fac, mfac, invfac, minvfac, inv, minv;
inline void init(size_t n, mint m) {
    size_t tmp = n << 1ull | 1ull;
    tmp++;
    fac.resize(tmp);
    mfac.resize(tmp);
    invfac.resize(tmp);
    minvfac.resize(tmp);
    inv.resize(tmp);
    minv.resize(tmp);
    fac[0] = mfac[0] = 1ull;
    for (size_t i = 1ull; i < tmp; i++) {
        fac[i] = fac[i - 1ull] * i;
        mfac[i] = mfac[i - 1ull] * (m - n + i - 1ull);
    }
    tmp--;
    invfac[tmp] = fac[tmp].inv();
    minvfac[tmp] = mfac[tmp].inv();
    for (size_t i = tmp; i; i--) {
        invfac[i - 1ull] = invfac[i] * i;
        minvfac[i - 1ull] = minvfac[i] * (m - n + i - 1ull);
        inv[i] = invfac[i] * fac[i - 1ull];
        minv[i] = minvfac[i] * mfac[i - 1ull];
    }
    minv[0] = 1ull;
}
inline void LagrangeInterpolation_ex(size_t n, mint m, const vector<mint>& a, vector<mint> &b) {
    vector<mint> f, g;
    size_t len = 1ull;
    int x = -1;
    while (len < n * 3ull + 2ull) len <<= 1ull, x++;
    get_rev(len, x);
    f.resize(len);
    g.resize(len);
    init(n, m);
    for (size_t i = 0ull; i <= n; i++) {
        f[i] = invfac[i] * invfac[n - i] * a[i];
        ((n - i) & 1ull) && (f[i] = -f[i]);
    }
    for (size_t i = 0; i <= (n << 1); i++) g[i] = minv[i + 1];
    mul(n + 1ull, n << 1ull | 1ull, f, g, f, len);
    b.resize(n + 1ull);
    for (size_t i = n; i <= (n << 1ull); i++) b[i - n] = mfac[i + 1ull] * minvfac[i - n] * f[i];
}
static vector<mint> mc;
size_t sval;
inline void prepare(mint n) {
    static vector<mint> md;
    int pos = 0;
    sval = sqrt(n.val()) + 1e-6;
    mint s(sval);
    mc.reserve(sval);
    md.reserve(sval);
    mint invs = s.inv();
    static vector<size_t> st;
    st.resize(log2(sval) + 5);
    for (size_t i = sval; i > 1ull; i >>= 1ull) st[++pos] = i;
    mc.resize(2ull);
    md.resize(2ull);
    mc[0] = 1ull;
    mc[1] = s + 1ull;
    for (size_t l = st[pos]; pos; l = st[--pos]) {
        LagrangeInterpolation_ex(l >> 1ull, mint((l >> 1ull) + 1ull), mc, md);
        mc.resize(mc.size() << 1ull);
        std::copy(md.begin(), md.end(), mc.begin() + md.size());
        LagrangeInterpolation_ex(mc.size() - 1ull, invs * (l >> 1ull), mc, md);
        for (size_t i = 0ull, iend = mc.size(); i < iend; i++) mc[i] *= md[i];
        if (l & 1ull) for (size_t i = 0; i <= l; i++) mc[i] *= s * i + l;
        else mc.resize(l + 1ull);
    }
}
inline mint get_fac(unsigned long long v) {
    mint res(1);
    unsigned long long iend = v / sval;
    for (unsigned long long i = 0ull; i < iend; i++) res *= mc[i];
    for (unsigned long long i = 1ull * iend * sval + 1ull, iendd = v; i <= iendd; i++) res *= i;
    return res;
}
int main() {
    prepare(mint(1000005));
    int T = 0;
    unsigned long long n, m;
    int opt;
    mint ans, tmp;
    cin >> T;
    while (T--) {
        cin >> n >> m >> opt;
        if (!opt) n = n + m - 1;
        if (n < m) {
            cout << '0' << '\n';
            continue;
        }
        ans = 1;
        for (unsigned long long i = n, iend = n - m + 1; i >= iend; i--) ans *= i;
        tmp = get_fac(m);
        cout << ans / tmp << '\n';
    }
    return 0;
}
```
~~成功把紫题做成黑题~~

---

