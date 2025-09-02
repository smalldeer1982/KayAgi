# Appropriate Team

## 题目描述

Since next season are coming, you'd like to form a team from two or three participants. There are $ n $ candidates, the $ i $ -th candidate has rank $ a_i $ . But you have weird requirements for your teammates: if you have rank $ v $ and have chosen the $ i $ -th and $ j $ -th candidate, then $ GCD(v, a_i) = X $ and $ LCM(v, a_j) = Y $ must be met.

You are very experienced, so you can change your rank to any non-negative integer but $ X $ and $ Y $ are tied with your birthdate, so they are fixed.

Now you want to know, how many are there pairs $ (i, j) $ such that there exists an integer $ v $ meeting the following constraints: $ GCD(v, a_i) = X $ and $ LCM(v, a_j) = Y $ . It's possible that $ i = j $ and you form a team of two.

 $ GCD $ is the greatest common divisor of two number, $ LCM $ — the least common multiple.

## 说明/提示

In the first example next pairs are valid: $ a_j = 1 $ and $ a_i = [2, 4, 6, 8, 10, 12] $ or $ a_j = 2 $ and $ a_i = [2, 4, 6, 8, 10, 12] $ . The $ v $ in both cases can be equal to $ 2 $ .

In the second example next pairs are valid:

- $ a_j = 1 $ and $ a_i = [1, 5, 7, 11] $ ;
- $ a_j = 2 $ and $ a_i = [1, 5, 7, 11, 10, 8, 4, 2] $ ;
- $ a_j = 3 $ and $ a_i = [1, 3, 5, 7, 9, 11] $ ;
- $ a_j = 6 $ and $ a_i = [1, 3, 5, 7, 9, 11, 12, 10, 8, 6, 4, 2] $ .

## 样例 #1

### 输入

```
12 2 2
1 2 3 4 5 6 7 8 9 10 11 12
```

### 输出

```
12
```

## 样例 #2

### 输入

```
12 1 6
1 3 5 7 9 11 12 10 8 6 4 2
```

### 输出

```
30
```

# 题解

## 作者：yybyyb (赞：1)

[强行插入博客链接Edu48题解](https://www.cnblogs.com/cjyyb/p/9426296.html)

先对于$y$ 分解质因数，这个东西可以泼辣的肉。  
然而题解给了一种很神仙的方法。  
首先你对于所有小于$y^{1/3}$的数暴力分解，  
这样子最多剩下一个大于$y^{1/3}$的质数，或者是$y^{1/3}$的平方。  
因为题目是要找到一个合法的$v$，所以在分解的时候只需要考虑和所有$a_i$相关的质因子。  
和$a_i$无关的质因子是可以直接忽视掉的，所以再利用每个$a_i$来求剩下的那个大因子。  
首先你拿到$a_i$，把它所有小于y含有的小于$y^{1/3}$的质因子除掉，  
然后剩下的部分和$y$求个$gcd$检查是否合法。  
最终分解出来的质因子数量并不会很多。大概不会超过$20$个吧。  

回到题目，如果$y\%x\neq 0$，直接判$0$。  
现在的条件是$x|y$。我们分$a_i$和$a_j$考虑。  
首先$a_i$一定是$x$的倍数，不妨令$a_i=kx$，  
把$k$用$y$的所有因数分解，状压未含有哪些因数，统计每个状压结果的个数。  
然后对于这个状压结果，计算超集和。  

再对于每个$a_j$考虑可以和它产生贡献的$a_i$  
因为$v$是$y$的因数，而又是$x$的倍数，并且$(v,a_i)=x$  
所以$v$只能含有$a_i$不含有的那部分因数，也就是上面状压的结果。  
那么，对于每个$a_j$，我们求出最大的$v$就可以直接利用超集和计算符合条件的数的个数了。  
考虑怎么求出最大的$v$满足$lcm(v,a_j)=y$  
我们从最小值开始，$v$的最小值是$x$，  
每次让$v$乘上$y/lcm(v,a_i)$就好了，直到$lcm=y$终止。  
那么只需要求出所有不含有$v$这些质因数的$a_i$了。  
也就是所有不含有$v/x$这些质因数的$k$，那么直接美滋滋的用超集和可以很容易的计算啦。  
~~第一次用C++11，感觉很爽啊~~  
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
#define MAX 200300
#define ll long long
ll a[MAX],c[MAX],x,y,all[MAX];
vector<ll> p;
ll divide(ll x){for(ll d:p)while(x%d==0)x/=d;return x;}
int n;
ll Multi(ll a,ll b,ll MOD)
{
    ll s=0;
    while(b){if(b&1)s=(s+a)%MOD;a=(a+a)%MOD;b>>=1;}
    return s;
}
ll fpow(ll a,ll b,ll MOD)
{
    ll s=1;
    while(b){if(b&1)s=Multi(s,a,MOD);a=Multi(a,a,MOD);b>>=1;}
    return s;
}
bool Miller_Rabin(ll x)
{
    if(x==2)return true;
    for(int tim=10;tim;--tim)
    {
        ll a=rand()%(x-2)+2;
        if(fpow(a,x-1,x)!=1)return false;
        ll p=x-1;
        while(!(p&1))
        {
            p>>=1;ll nw=fpow(a,p,x);
            if(Multi(nw,nw,x)==1&&nw!=1&&nw!=x-1)return false;
        }
    }
    return true;
}
ll Pollard_rho(ll n,int c)
{
    ll i=0,k=2,x=rand()%(n-1)+1,y=x;
    while(233)
    {
        ++i;x=(Multi(x,x,n)+c)%n;
        ll d=__gcd((y-x+n)%n,n);
        if(d!=1&&d!=n)return d;
        if(x==y)return n;
        if(i==k)y=x,k<<=1;
    }
}
vector<ll> fac;
void Fact(ll n,int c)
{
    if(n==1)return;
    if(Miller_Rabin(n)){fac.push_back(n);return;}
    ll pp=n;while(pp>=n)pp=Pollard_rho(n,c--);
    Fact(pp,c);Fact(n/pp,c);
}
int get(ll x)
{
	int S=0;
	for(int j=0,l=p.size();j<l;++j)
		if(x%p[j]==0)S|=1<<j;
	return S;
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>x>>y;
	if(y%x){cout<<0<<endl;return 0;}
	for(int i=1;i<=n;++i)cin>>a[i];
	Fact(y,123);
	sort(fac.begin(),fac.end());
	for(int i=0,l=fac.size();i<l;++i)
		if(i==0||fac[i]!=fac[i-1])p.push_back(fac[i]);
	for(int i=1;i<=n;++i)
		if(a[i]%x==0)
		{
			int S=get(a[i]/x);
			++c[((1<<p.size())-1)^S];
		}
	for(int i=0;i<MAX;++i)
	{
		for(int j=i;j;j=(j-1)&i)all[j]+=c[i];
		all[0]+=c[i];
	}
	ll ans=0;
	for(int i=1;i<=n;++i)
	{
		if(y%a[i])continue;
		ll cur=x;
		while(233)
		{
			ll lcm=(a[i]/__gcd(a[i],cur))*cur;
			if(lcm==y)break;
			cur*=y/lcm;
		}
		cur/=x;ans+=all[get(cur)];
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：ywy_c_asm (赞：0)

对于这类问题我们应该从质数的次幂上考虑。

我们将$y$分解质因数，这最多只有15个，设$cnt_{p}(x)$为$p$在$x$中的指数。显然对于一对合法的$a_i$和$a_j$和$v$，由于$gcd$和$lcm$的定义，一定对每个$p$有$cnt_p(x)=\min(cnt_p(a_i),cnt_p(v))$以及$cnt_p(y)=\max(cnt_p(a_j),cnt_p(v))$，显然$cnt_p(v)$取值在$[cnt_p(x),cnt_p(y)]$这段区间内。考虑每个$a_i$，首先得有$x|a_i$，如果$cnt_p(a_i)>cnt_p(x)$，那么必须要有$cnt_p(v)=cnt_p(x)$，否则$cnt_p(v)$可以任取。同样的对于$y$也是如此。我们仅考虑$cnt_p(x)!=cnt_p(y)$的$p$（如果相等的话$x,y,v,a_i,a_j$这一项肯定都得取$cnt_p(x)$不用管），如果一个$a_i$有必须$cnt_p(v)=cnt_p(x)$的限制，而另一个$a_j$又有必须$cnt_p(v)=cnt_p(y)$的限制，那么$a_i$和$a_j$一定是不能组成对的，否则一定存在一个合法的$cnt_p(v)$。那么我们对每个$a_i,a_j$搞出一个有限制的二进制集合$S_i$，对应位为1说明有限制，那么$a_i,a_j$能够合法当且仅当$S_i\&S_j=0$，这个FWT一下就好了。

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>
#define ll long long
#define abs(_o) ((_o < 0) ? -(_o) : _o)
using namespace std;
namespace ywy {
	inline ll get() {
	    ll n = 0;
	    char c;
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            break;
	        if (c == '-')
	            goto s;
	    }
	    n = c - '0';
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 + c - '0';
	        else
	            return (n);
	    }
	s:
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 - c + '0';
	        else
	            return (n);
	    }
	}
	inline ll gcd(ll a, ll b) {
	    while (b) {
	        ll r = a % b;
	        a = b;
	        b = r;
	    }
	    return (a);
	}
	inline ll gsc(ll a, ll b, ll p) {
	    if (a <= 1000000000 && b <= 1000000000)
	        return ((a * b) % p);
	    // ll ans=0,tmp=a;while(b){
	    //	if(b&1)ans=(ans+tmp)%p;tmp<<=1;tmp%=p;b>>=1;
	    //}return(ans);
	    ll res = a * b - ((ll)((long double)a * b / p)) * p;
	    return res < 0 ? res + p : res % p;
	}
	inline ll mi(ll a, ll b, ll p) {
	    ll ans = 1, tmp = a;
	    while (b) {
	        if (b & 1)
	            ans = gsc(ans, tmp, p);
	        tmp = gsc(tmp, tmp, p);
	        b >>= 1;
	    }
	    return (ans);
	}
	int pri[10] = { 2, 3, 5, 7, 11, 13 };
	inline int check(ll n) {
	    if (n == 46856248255981ll)
	        return (0);
	    if (n == 1)
	        return (0);
	    if (n == 2 || n == 3 || n == 5 || n == 7)
	        return (1);
	    if (!(n & 1))
	        return (0);
	    if (n % 3 == 0)
	        return (0);
	    if (n % 5 == 0)
	        return (0);
	    if (n % 7 == 0)
	        return (0);
	    for (register int i = 0; i < 6; i++) {
	        if (n == pri[i])
	            return (1);
	        if (n % pri[i] == 0)
	            return (0);
	        ll tmp = n - 1;
	        while (1) {
	            ll cjr = mi(pri[i], tmp, n);
	            if (cjr == n - 1)
	                break;
	            if (cjr != 1)
	                return (0);
	            if (tmp & 1)
	                break;
	            tmp >>= 1;
	        }
	    }
	    return (1);
	}
	inline ll exrand() {
	    ll a = rand(), b = rand(), c = rand(), d = rand();
	    return ((a << 48) | (b << 32) | (c << 16) | d);
	}
	inline ll rho(ll n, ll c) {
	    ll x = exrand() % n, y = x;
	    int k = 2;
	    while (1) {
	        ll ji = 1;
	        for (register int i = 1; i <= k; i++) {
	            x = (gsc(x, x, n) + c) % n;
	            ji = gsc(ji, abs(y - x), n);
	        }
	        ll g = gcd(ji, n);
	        if (g > 1)
	            return (g);
	        y = x;
	        k <<= 1;
	    }
	    return (n);
	}
	ll maxn = 0;
	vector<ll> p;
	inline void pol(ll n, ll c) {
	    if (n == 1)
	        return;
	    if (check(n)) {
	        p.push_back(n);
	        return;
	    }
	    while (1) {
	        ll cjr = rho(n, c);
	        if (cjr != n) {
	            while (n % cjr == 0) n /= cjr;
	            pol(cjr, c);
	            pol(n, c);
	            return;
	        }
	        c--;
	    }
	}
	ll ints[200001], f[200001], g[200001];
	int cntx[33], cnty[33];
	inline void fwt(int n, ll *f, int op) {
	    for (register int bit = 2; bit <= n; bit <<= 1) {
	        for (register int i = 0; i < n; i += bit) {
	            for (register int j = i; j < i + (bit >> 1); j++) f[j] = f[j] + op * f[j + (bit >> 1)];
	        }
	    }
	}
	void ywymain() {
	    int n = get();
	    ll x = get(), y = get();
	    if (y % x != 0) {
	        cout << 0 << endl;
	        return;
	    }
	    for (register int i = 1; i <= n; i++) ints[i] = get();
	    srand(19260817);
	    pol(y, 19260817);
	    int s = 0;
	    for (register int i = 0; i < p.size(); i++) {
	        ll tmp = x;
	        while (tmp % p[i] == 0) tmp /= p[i], cntx[i]++;
	        tmp = y;
	        while (tmp % p[i] == 0) tmp /= p[i], cnty[i]++;
	        if (cntx[i] != cnty[i])
	            s |= (1 << i);
	    }
	    for (register int i = 1; i <= n; i++) {
	        if (ints[i] % x == 0) {
	            int t = 0;
	            for (register int j = 0; j < p.size(); j++) {
	                int cnt = 0;
	                ll tmp = ints[i];
	                while (tmp % p[j] == 0) cnt++, tmp /= p[j];
	                if (cnt != cntx[j])
	                    t |= (1 << j);
	            }
	            f[t]++;
	        }
	        if (y % ints[i] == 0) {
	            int t = 0;
	            for (register int j = 0; j < p.size(); j++) {
	                int cnt = 0;
	                ll tmp = ints[i];
	                while (tmp % p[j] == 0) cnt++, tmp /= p[j];
	                if (cnt != cnty[j])
	                    t |= (1 << j);
	            }
	            g[t]++;
	        }
	    }
	    fwt(1 << p.size(), f, 1);
	    fwt(1 << p.size(), g, 1);
	    for (register int i = 0; i < (1 << p.size()); i++) f[i] *= g[i];
	    fwt(1 << p.size(), f, -1);
	    ll ans = 0;
	    for (register int i = 0; i < (1 << p.size()); i++)
	        if (!(i & s))
	            ans += f[i];
	    cout << ans << endl;
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：1saunoya (赞：0)

**先把 $Y$ 拆掉，然后再用 $Y$ 的质因子去拆 $X$。**

这样就规避了 **rho** 的问题。

定义 $f_x$ 是 $x$ 这个状态的位与 $y$ 不同的个数。

$g_x$ 是 $x$ 这个状态的位与 $x$ 不同的个数。


然后就是 **FWTAND**。

答案就是 $(f\times g)_0$。

```cpp
/*
 _      _  _ _ _ _ _   _      _
\_\   /_/ \_\_\_\_\_\ \_\   /_/
 \_\ /_/      \_\      \_\ /_/
  \_\_/       \_\       \_\_/
   \_\         \_\       \_\
   \_\     \_\ \_\       \_\
   \_\      \_\\_\       \_\
*/
//#pragma GCC optimize ("O3")
//#pragma GCC target ("sse4")
#include <bits/stdc++.h>
//#define int ll
using ll = int64_t;
using uint = uint32_t;
using ull = uint64_t;
using str = std::string;
#define fi first
#define se second
using pii = std::pair<int, int>;
using pil = std::pair<int, ll>;
using pli = std::pair<ll, int>;
template<class T> using V = std::vector<T>;
struct _ { _() { std::ios::sync_with_stdio(false), std::cin.tie(nullptr); } };
template<class T> void rd(T &x) { std::cin >> x; }
template<class T> void pt(const T &x, const str &s = "") { std::cout << x << s; }
template<class T, class ...Args> void rd(T &x, Args &...args) { rd(x); rd(args...); }
template<class T> V<T> rdV(int N) { V<T> A(N); for (auto &x: A) { rd(x); } return A; }
#define gV(T, x) rdV<T>(x)
template<class T> void pt(const V<T> &A) { for (auto x : A) { pt(x, " "); } pt('\n'); }
template<class T> void cmax(T &x, const T &y) { x = (x > y) ? x : y; }
template<class T> void cmin(T &x, const T &y) { x = (x < y) ? x : y; }
template<class T> T maxV(const V<T> &A) { T res = *A.begin(); for (auto x : A) cmax(res, x); return res; }
template<class T> T minV(const V<T> &A) { T res = *A.begin(); for (auto x : A) cmin(res, x); return res; }
#define sz(V) (int)V.size()
#define all(V) V.begin(), V.end()
#define pb emplace_back
#define rp(i, n) for (int i = 0; i < n; i++)
#define pr(i, n) for (int i = n - 1; i >= 0; i--)
#define rep(i, x, y) for (int i = x; i <= y; i++)
#define per(i, x, y) for (int i = x; i >= y; i--)
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
V<ll> p = {2, 3};
void fwt(int *a, int lim) {
	if (lim == 1) {
		return;
	} else {
		lim /= 2;
	}
	for (int i = 0; i < lim; i++) {
		a[i] += a[i + lim];
	}
	fwt(a, lim);
	fwt(a + lim, lim);
}
std::map<ll, int> factor(ll x) {
	std::map<ll, int> map;
	for (auto i : p) {
		if (x % i == 0) {
			int &cnt = map[i] = 0;
			do {
				x /= i;
				++cnt;
			} while (x % i == 0);
		}
	}
	if (x > 1) {
		map[x] += 1;
	}
	return map;
}
int n;
ll x, y;
ll solve(V<ll> v, ll x, ll y) {
	for (int i = 5; i < 1e6; i += 2) {
		p.pb(i);
	}
	for (auto i : v) {
		ll o = std::__gcd(i, x);
		if (o != 1 && o != y) {
			p.pb(o);			
		}
		o = std::__gcd(i, y);
		if (o != 1 && o != y) {
			p.pb(o);
		}
	}
	std::sort(all(p));
	p.resize(std::unique(all(p)) - p.begin());
	auto vy = factor(y);
	p = {};
	for (auto i : vy) {
		p.pb(i.first);
	}
	auto vx = factor(x);
	V<ll> p0;
	for (auto i : p) {
		if (vx[i] != vy[i]) {
			p0.pb(i);
		}
	}
	V<ll> v0, v1;
	for (auto i : v) {
		auto fc = factor(i);
		if (i % x == 0) {
			int s = 0, idx = 0;
			for (auto i : p0) {
				if (fc[i] != vx[i]) {
					s |= 1 << idx;	
				}
				++idx;
			}
			v0.pb(s);
		}
		if (y % i == 0) {
			int s = 0, idx = 0;
			for (auto i : p0) {
				if (fc[i] != vy[i]) {
					s |= 1 << idx;
				}
				++idx;
			}
			v1.pb(s);
		}
	}
	V<int> b0(262144), b1(262144);
	for (auto i : v0) {
		++b0[i];
	}
	for (auto i : v1) {
		++b1[i];
	}
	fwt(b0.data(), 262144);
	fwt(b1.data(), 262144);
	V<ll> res(262144);
	rp(i, 262144) {
		res[i] = 1ll * b0[i] * b1[i];
	}
	ll ans = 0;
	int sgn[] = {1, -1};
	rp(i, 262144) {
		ans += sgn[__builtin_popcount(i) & 1] * res[i];
	}
	return ans;
}
int main() {
	rd(n, x, y);
	auto v = gV(ll, n);
	pt((y % x) ? 0 : solve(v, x, y));
	return 0;
}
```

---

