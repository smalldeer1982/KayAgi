# Koishi Loves Number Theory

## 题目描述

Koishi 十分喜欢数论。


她的朋友 Flandre 为了检测她和数论是不是真爱，给了她一个问题。


已知 $f(n)=\sum_{i=0}^nx^i$

给定 $x$ 和 $N$ 个数 $a_i$，求 $\mathrm{lcm}(f(a_1),f(a_2),...,f(a_N))$ 对 $10^9+7$ 取模。


按照套路，呆萌的 Koishi 当然假装不会做了，于是她来向你请教这个问题，希望你能在 $1$ 秒内给她答案。


## 说明/提示

$\mathrm{lcm}$ 表示若干个数的**最小公倍数**。


对于 $10\%$ 的数据，$1\leq N\leq 100$，$0\leq a_i\leq 9$，$x=2$。

对于另外 $20\%$ 的数据，$1\leq N\leq 50$，$0\leq a_i\leq 100$，$2\leq x\leq 10$。

对于另外 $30\%$ 的数据，$1\leq N\leq 16$，$0\leq a_i\leq 10^9$，$2\leq x\leq 10^{18}$。

对于 $100\%$ 的数据，$1\leq N\leq 100$，$0\leq a_i\leq 10^9$，$2\leq x\leq 10^{18}$，且 $x\not\equiv 1\pmod{10^9+7}$。


## 样例 #1

### 输入

```
3 5
1 2 4 5 0```

### 输出

```
44044```

# 题解

## 作者：dovely_seele (赞：20)

可能我阅读理解能力不太好，没看懂其他题解（

首先根据等比数列求和公式 $f(n)$ 显然等于 $\frac{x^{n+1}-1}{x-1}$，分母 $x-1$ 是个定值可以直接先扔出来。所以就是让你求一堆形如 $x^a-1$ 的数的最小公倍数。

首先考虑只有两个数的情况，这时 lcm 也就是乘积除以 gcd。 根据具体数学习题 4.38，$gcd(x^a-1,x^b-1)=x^{gcd(a,b)}-1$。书上是用辗转相除证的，其实不用也可以。

首先显然 $x^{gcd(a,b)}-1$ 是两数的公约数（参考具体数学习题 4.22），然后只需要证明它是最大的即可。接下来的一步比较有意思：找两个正整数 $n, m$ 使得 $na=mb+gcd(a,b)$（根据 exgcd，肯定能找到这两个数），那么 $gcd(x^a-1,x^b-1)|x^b-1|x^{mb}-1$，所以 $gcd(x^a-1,x^b-1)|x^{gcd(a,b)}(x^{mb}-1)$，而后者展开之后就是 $x^{mb+gcd(a,b)}-x^{gcd(a,b)}=x^{na}-x^{gcd(a,b)}$，由于已知 $x^{na}$ 除以 $gcd(x^a-1,x^b-1)$ 的余数是 $1$，所以 $x^{gcd(a,b)}$ 除以 $gcd(x^a-1,x^b-1)$ 的余数也是 1，也就是说 $gcd(x^a-1,x^b-1)|x^{gcd(a,b)}-1$，所以它一定是最大的。

现在如果换成多个数如何求 lcm 呢？两个数取 lcm 之后已经不是 $x^a-1$ 的形式，无法再套用前面的结论。手玩一下 $n=3$ 和 $n=4$ 的情况可以发现一个集合的 lcm 就是所有大小为奇数的子集的 gcd 乘积除以所有大小为偶数的子集的 gcd 乘积。（这很好理解，因为求 gcd 本质上就是求两个约数集合的交。）

我们用 map 维护一个集合中所有子集中每个 gcd 的出现次数（由于 gcd 也是 $x^a-1$ 的形式，只需要记录指数即可），由于这些 gcd 显然至少是其中一个数的约数，所以集合最多也只有 $O(n\sqrt{V})$ 个元素。然后每次加入一个元素，这时新的集合的所有子集可以分为两类：包含新元素和不包含新元素的，后者 gcd 的乘积就是原来集合的 lcm，前者就是把原来集合的每一个子集 gcd 和新的数取 gcd 后取倒数（因为集合的大小奇偶性反转了），遍历一遍 map 算完了再将两者加起来即可。粗略估算一下，时间复杂度算上 map 的一个 log 是 $O(n^2\sqrt{V}logn)$，而且严重不满，可以通过。（输出答案的时候不要忘记乘以一开始丢掉的 $x-1$ 的逆元）

说的不太清楚，看代码吧。

```
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;
map<long long, long long> s, seele;
long long qp(long long n, long long m, long long p) {
    long long ans = 1, base = n;
    while (m) {
        if (m & 1) (ans *= base) %= p;
        (base *= base) %= p; m >>= 1;
    }
    return ans;
}
int main() {
long long x, n, t, prod=1; cin>> x>> n; x %= (long long)(1e9+7); for (int i=1; i<=n; i++) {
cin>> t; ++t; seele.clear(); for (auto it: s) seele[it.first] = it.second; for (auto it : seele) s[__gcd(it.first, t)] -= it.second; s[t]++;
} for (auto it: s) (prod *= it.second> 0?qp(qp(x, it.first, 1e9+7) - 1, it.second, 1e9+7): qp(qp(qp(x, it.first, 1e9+7) - 1, -it.second, 1e9+7), 1e9+5, 1e9+7)) %= (long long)(1e9+7); cout << prod * qp(x-1, 1e9+5, 1e9+7) % (long long)(1e9+7);
}
```

---

## 作者：Soulist (赞：11)


感觉挺有意思的。

定义 $f(n)=\sum_{k=0}^n x^k$，其中 $x$ 为常数。

给定 $x$ 和 $N$ 个自然数 $a_i$，求 $\textrm{lcm}\{f(a_1),f(a_2)...f(a_n)\}$

$N\le 100,a_i\le 10^{9},2\le x\le 10^{18}$

---

$\rm Sol:$

$$f(n)=\frac{x^n-1}{x-1}$$

注意到：

$$\textrm{lcm}(\frac{a}{c}, \frac{b}{c})=\frac{\textrm{lcm}(a,b)}{c}$$

于是所求为：

$$\frac{\textrm{lcm}\{x^{a_1}-1,x^{a_2}-1\cdots x^{a_n}-1\}}{x-1}$$

接下来，通过一定的手玩，我们可以证明~~瞎猜~~一个结论：$\gcd(x^{a}-1,x^{b}-1)=x^{\gcd(a,b)}-1$。

可以这样考虑，设 $f(n)=x^n-1$，我们先证明 $\gcd(f(n),f(m+n))=\gcd(f(n),f(m))$

事实上，注意到：

$$\begin{aligned}
    &\gcd(x^n-1,x^{n+m}-1)
    \\&=\gcd(x^n-1,(x^n-1)(x^m-1)+(x^n-1)+(x^m-1))
    \\&=\gcd(x^n-1,x^m-1)
\end{aligned}$$

于是对于 $\gcd(f(x),f(y))$，如果有 $x<y$，那么 $\gcd(f(x),f(y))=\gcd(f(x), f(y-x))$，换而言之辗转相除成立，于是我们有 $\gcd(f(x),f(y))=f(\gcd(x,y))$

此时我们所求为 $\textrm{lcm}$，我们可以通过 $\min-\max$ 反演来通过 $\gcd$ 计算答案（直接考虑贡献并容斥可以得到相似的结果，但是与 $\min-\max$ 容斥的推导是相似的）

注意到 $\rm lcm$ 是对于每个质因子指数取 $\max$，而 $\gcd$ 为对于每个质因子指数取 $\min$，在考虑每个质因子下，我们计算一些数的 $\rm lcm$ 可以轻易的通过 $\gcd$ 表示：

$$\begin{aligned}
    &p^{\max(k_1...k_n)}=\prod_{S\subseteq{T},S\ne \varnothing} p^{(-1)^{|S|+1}\min(k\in S)}
    \\&\textrm{lcm}(T)=\prod p^{\sum_{S\subseteq T,S\ne \varnothing}(-1)^{|S|+1}\min(k\in S)}
    \\&\textrm{lcm}(T)=\prod_{S\subseteq T,S\ne \varnothing} \prod p^{(-1)^{|S|+1}\min(k\in S)}
    \\&\textrm{lcm}(T)=\prod_{S\subseteq T,S\ne \varnothing} \gcd(S)^{(-1)^{|S|+1}}
\end{aligned}$$

当我们转换为 $\gcd$ 的形式后，根据一开始的结论，我们可以不计算这种极大的数的 $\gcd$ 而是转为计算下标的 $\gcd$ 并做乘法。

每个数 $a$ 可以得到的 $\gcd$ 有且仅有其约数，对于每个约数，其贡献为 $\sum (-1)^{|S|}[\gcd(S)=x]$，我们可以考虑套路莫比乌斯反演，设 $F(x)$ 表示至少，那么 $F(x)=\sum(-1)^{|S|+1}[x|k,\forall k\in S]$，设 $cnt$ 为这种 $k$ 的数量，那么 $F(x)=\sum_{j=1}^{cnt} \binom{cnt}{j} (-1)^{j+1}$，容易知道 $F(x)=1$

然后我们做一边容斥/反演即可得到答案，复杂度为 $\mathcal O((N\cdot \sigma(w))^2+N\times \sqrt{w})$，然而相同的约数我们不需要重复遍历，所以实际复杂度会更小。~~跑得非常快~~

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
#define rep( i, s, t ) for( register int i = (s); i <= (t); ++ i )
#define drep( i, s, t ) for( register int i = (t); i >= (s); -- i )
#define re register
#define int long long
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N = 100 + 5 ; 
const int M = 5000 + 5 ; 
const int P = 1e9 + 7 ; 
const int I = 1e9 + 6 ; 
int n, X, top, st[N * 1926], w[N], cnt, F[M] ; 
int fpow( int x, int k ) {
	int ans = 1, base = x ; 
	while(k) {
		if(k & 1) ans = ans * base % P ;
		base = base * base % P, k >>= 1 ; 
	} return ans ; 
}
signed main()
{
	X = gi() % P, n = gi() ; 
	rep( i, 1, n ) {
		int x = gi() + 1, k = sqrt(x) ; 
		for( re int i = 1; i <= k; ++ i ) {
			if( x % i ) continue ; 
			st[++ top] = i, st[++ top] = x / i ; 
		}
	}
	sort( st + 1, st + top + 1 ) ;
	rep( i, 1, top ) if( st[i] != st[i - 1] ) w[++ cnt] = st[i] ; 
	drep( i, 1, cnt ) {
		F[i] = 1 ; 
		rep( j, i + 1, cnt ) if( w[j] % w[i] == 0 ) F[i] = ( F[i] - F[j] + I ) % I  ;
	}
	int ans = 1 ; 
	rep( i, 1, cnt ) {
		int dx = fpow( X, w[i] ) - 1 ; 
		F[i] = ( F[i] % I + I ) % I ; 
		ans = ans * fpow( dx, F[i] ) % P ; 
	}
	cout << ans * fpow( X - 1, P - 2 ) % P << endl ; 
	return 0 ;
}
```

---

## 作者：w (赞：9)

官方题解： https://www.luogu.org/discuss/show?postid=7867


---

## 作者：Purslane (赞：2)

# Solution

首先注意到：

$$
\operatorname{lcm}_{u \in \{1,2,\dots,n\}} a_u = \prod_{S \subseteq \{1,2,\dots,n\}} (\gcd_{u \in S} a_u)^{(-1)^{|S|-1}} 
$$

> 为什么要做这个“反演”呢？因为求这一堆很大东西的 $\rm lcm$ 是挺困难的，但是求它们的 $\rm gcd$ 是有规律的。那种“求一些数 $\rm lcm$ 对 $998244353$ 取模”的题，一般有特殊规律，不然在中间对答案取模是会出错的。

根据幼儿园数论知识，当 $x \in \mathbb Z_{\ge 2}$ 时，$\gcd(x^a-1,x^b-1) = x^{\gcd(a,b)}-1$。而 $f(n) = \dfrac{x^{n+1}-1}{x-1}$，因此 $\gcd(f(a),f(b)) = f(\gcd(a+1,b+1)-1)$。

我们把 $\gcd_{u\in S} (a_u+1) = v$ 的 $S$ 全部算出来。注意到 $v$ 必须是某个数的因子，因此其个数只有 $O(n d(V))$ 级别。

复杂度 $O(n^2d(V) \log \square)$，那个 $\square$ 看起来无关紧要，没有分析了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=100+10,MOD=1e9+7;
int n,x,ans=1,inv,a[MAXN];
map<pair<int,int>,int> dp[MAXN];
int qpow(int base,int p) {
	base%=MOD;
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
int f(int n) {return (qpow(x,n)-1)*inv%MOD;}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>x>>n,inv=qpow(x-1,MOD-2);
	ffor(i,1,n) cin>>a[i],a[i]++;
	dp[0][{0,0}]=1;
	ffor(i,1,n) {
		dp[i]=dp[i-1];
		for(auto pr:dp[i-1]) {
			int val=pr.first.first,op=pr.first.second,cnt=pr.second;
			dp[i][{__gcd(val,a[i]),op^1}]=(dp[i][{__gcd(val,a[i]),op^1}]+cnt)%MOD;
		}
	}
	for(auto pr:dp[n]) {
		int val=pr.first.first,op=pr.first.second,cnt=pr.second;
		if(val==0) continue ;
		if(op) ans=ans*qpow(f(val),cnt)%MOD;
		else ans=ans*qpow(qpow(f(val),(MOD-2)),cnt)%MOD;
	}
	cout<<(ans%MOD+MOD)%MOD;
	return 0;
}
```

---

## 作者：SunsetSamsara (赞：1)

## P3598

### 题意

求对于每一个 $1 \le t \le n$ 的 $\operatorname{lcm}(\sum\limits_{i=0}^{a_t}x^i)$。

### 标签

数学

### 做法

昂，一个不一样的做法。

首先 $\sum\limits_{i=0}^{a_t}x^i = \frac{x^{a_t + 1} - 1}{x - 1}$，所以由 $\operatorname{lcm}(\frac x d, \frac y d) = \frac {\operatorname{lcm}(x, y)} {d}$ 得原式为 $\frac{\operatorname{lcm}(x^{a_t + 1} - 1)} x - 1$。

先把所有的 $a_t$ 加上 $1$，问题就变成了求 $\operatorname{lcm}(x^{a_t + 1} - 1)$。直接求 $\operatorname{lcm}$ 不好求，考虑求 $\gcd$。进行辗转相除法：

$$
\begin{aligned}
\gcd(x ^ n - 1, x ^ m - 1) &= \gcd(x ^ n - 1 - x ^ {n - m}(x ^ m - 1), x ^ m - 1)\\
&= \gcd(x ^ n - 1 - x ^ n + x ^ {n - m}, x ^ m - 1)\\
&= \gcd(x ^ {n - m} - 1, x^m - 1)
\end{aligned}
$$

发现可以转变为指数上的辗转相减法，于是 $\gcd$ 就是 $x ^ {\gcd(n, m)} - 1$。

接下来考虑求 $\operatorname{lcm}$。

先证明一个公式 $\gcd(\operatorname{lcm}(x, y), z) = \operatorname{lcm}(\gcd(x, z), \gcd(y, z))$。

考虑每个质因子 $p$，设 $p$ 在 $x, y, z$ 中的幂次分别为 $a, b, c$，那么质因子 $p$ 对 $\gcd(\operatorname{lcm}(x, y), z)$ 的贡献就是 $\min(\max(a, b), c)$，对 $\operatorname{lcm}(\gcd(x, z), \gcd(y, z))$ 的贡献就是 $\max(\min(a, c), \min(b, c))$。

显然有 $\min(\max(a, b), c) = \max(\min(a, c), \min(b, c))$，于是质因子 $p$ 对左式和右式的贡献相等，等式自然成立。

又因为有 $\operatorname{lcm}(x, y) = \frac {xy} {\gcd(x, y)}$，所以有：

$$
\begin{aligned}
\operatorname{lcm}(a_1, a_2, \cdots, a_n) &= \operatorname{lcm}(\operatorname{lcm}(a_1, a_2, \cdots, a_{n - 1}), a_n)\\
&= \frac {\operatorname{lcm}(a_1, a_2, \cdots, a_{n - 1}) \cdot a_n} {\gcd(\operatorname{lcm}(a_1, a_2, \cdots, a_{n - 1}),a_n)}\\
&= \frac {\operatorname{lcm}(a_1, a_2, \cdots, a_{n - 1}) \cdot a_n} {\operatorname{lcm}(\gcd(a_1, a_n), \gcd(a_2, a_n), \cdots, \gcd(a_{n - 1},a_n))}
\end{aligned}
$$

于是这样就把一个规模为 $n$ 的问题转化成了两个大小为 $n - 1$ 的问题。但是直接这样做复杂度是 $O(2 ^ n)$ 的，明显过不去。考虑进行优化。

发现可以记忆化，不同的 $a$ 构成的相同的集合答案相同，所以可以对 $a$ 进行排序后进行记忆化。又发现相同的 $a$ 只会有一次贡献，因此可以进行 `unique` 后再进行剩余操作。

实践证明这个记忆化是十分强的。因为有记忆化的操作，并且这个搜索的过程会产生极大量的重复，发现对于每一个搜索的序列都具有 $\{\gcd(a_i, \gcd(a_t, a_{t + 1}, \cdots, a_n))\}$ 也即序列 $a$ 中每个数都与相同的后缀 $\gcd$ 取 $\gcd$ 的形式。后缀至多 $n$ 个，长度至多 $n$ 种，总共有 $O(n^2)$ 个序列，每种序列的操作都是 $O(L \log L)$ 的，其中 $L$ 为序列长度，所以最终复杂度是 $O(n ^ 3 \log n)$ 的，完全可过。

思路简单，代码短，复杂度正确，常数小，最优解，是非常优质的做法。

### 代码

```cpp
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <map>
#include <set>
typedef long long lld;
using namespace std;
const int mod = 1e9 + 7;
lld x;
int n;
inline lld qpow(lld a, lld b, lld p) {
	lld ret = 1;
	for (; b; b >>= 1, a = a * a % p)
		if (b & 1) ret = ret * a % p;
	return ret;
}
int ans, cur;
map<vector<int>, int> mp;
inline int solve(vector<int> &a) {
	sort(a.begin(), a.end());
	a.erase(unique(a.begin(), a.end()), a.end());
	if (!a.size()) return 1;
	if (a.size() == 1) return qpow(x, a[0], mod) - 1;
	if (mp.count(a)) return mp[a];
	vector<int> b = a; b.pop_back(); int pre = solve(b);
	b.clear(); for (unsigned i = 0; i < a.size() - 1; ++ i) b.push_back(__gcd(a[i], a.back())); int res = solve(b);
	return mp[a] = 1ll * pre * (qpow(x, a.back(), mod) - 1) % mod * qpow(res, mod - 2, mod) % mod;
}
vector<int> a;
int main() {
	scanf("%lld%d", &x, &n);
	x %= mod;
	for (int i = 1, t; i <= n; ++ i) {
		scanf("%d", &t);
		++ t;
		a.push_back(t);
	}
	printf("%lld\n", (1ll * ((solve(a) % mod + mod) % mod) * qpow(x - 1, mod - 2, mod) % mod + mod) % mod);
}
```

---

## 作者：daniEl_lElE (赞：0)

首先根据小学数学 $f(n)=\frac{x^n-1}{x-1}$。

其次根据初中数学 $\gcd(f(a),f(b))=f(\gcd(a,b))$。

然后根据归纳可得 $\gcd(f(a_1),f(a_2),\dots,f(a_m))=f(\gcd(a_1,a_2,\dots,a_m))$。

我们发现我们现在要求 $\operatorname{lcm}$，而我们容易对于一系列 $a_i$ 求出 $\gcd$，不难想到 $\min-\max$ 容斥。（在这里是 $\gcd-\operatorname{lcm}$） 

于是，我们将问题转化为了对于每个 $p$ 有多少大小为奇数或偶数的 $a$ 的子集 $T$ 满足 $\gcd_{v\in T}v=p$。

套路地转化为 $p|\gcd_{v\in T}v$，于是我们只需要对于每个 $p$ 计算出有多少 $v\in a$ 满足 $p|v$，然后预处理系数（直接算也行），容斥回去即可。

考虑到 $a\leq10^9$，我们需要把所有 $a$ 的因数取出来取一个并集，在并集上做容斥。总复杂度 $O(n\sqrt{a_i}+nd(a_i)\omega(a_i))$。根据[这张表](https://cdn.luogu.com.cn/upload/image_hosting/j4ds5pcn.png)，可以发现是很快的。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7;
int a[105],cnt;
map<int,int> mp1,mp2;
vector<int> vc1,vc2;
int num[100005];
int C[105][105];
int qp(int a,int b){
	a%=mod;
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
}
signed main(){
	for(int i=0;i<=100;i++) C[i][0]=1;
	for(int i=1;i<=100;i++) for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%(mod-1);
	int x,n; cin>>x>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]++;
		for(int j=1;j*j<=a[i];j++){
			if(a[i]%j==0){
				if(!mp1[j]) vc1.push_back(j),mp1[j]=1;
				if(!mp1[a[i]/j]) vc1.push_back(a[i]/j),mp1[a[i]/j]=1;
			}
		}
		int t=a[i];
		for(int j=2;j*j<=t;j++){
			if(t%j==0){
				if(!mp2[j]) vc2.push_back(j),mp2[j]=1;
				while(t%j==0) t/=j;
			}
		}
		if((t!=1)&&(!mp2[t])) vc2.push_back(t),mp2[t]=1;
	}
	sort(vc1.begin(),vc1.end());
	for(auto v:vc1) mp1[v]=++cnt;
	for(int i=1;i<=n;i++){
		for(int j=1;j*j<=a[i];j++){
			if(a[i]%j==0){
				num[mp1[j]]++;
				if(j*j!=a[i]) num[mp1[a[i]/j]]++;
			}
		}
	}
	for(int i=1;i<=cnt;i++){
		int tmp=0;
		for(int j=1;j<=num[i];j++){
			if(j&1) (tmp+=C[num[i]][j])%=(mod-1);
			else (tmp+=(mod-1)-C[num[i]][j])%=(mod-1);
		}
		num[i]=tmp;
	}
	for(auto v:vc2){
		for(int i=1;i<=cnt;i++){
			int to=mp1[vc1[i-1]*v];
			if(to){
				(num[i]+=(mod-1)-num[to])%=(mod-1);
			}
		}
	}
	int ans=1;
	for(int i=1;i<=cnt;i++){
		(ans*=qp(qp(x,vc1[i-1])-1,num[i]))%=mod;
	}
	cout<<ans*qp(x-1,mod-2)%mod;
	return 0;
}

```

---

## 作者：orz_z (赞：0)



有
$$
\gcd(x^a-1,x^b-1)=x^{\gcd(a,b)}-1
$$
和
$$
\operatorname{lcm}(S)=\prod_{T\subset S}\gcd(T)^{(-1)^{|T|-1}}
$$
于是现在就是要求固定长度和 $\gcd$ 下的子集个数。

一种是发现状态数很少，直接开 `map` 推过去。

另一种是直接莫反。

$10^9$ 下的因子个数最多 $1344$ 个。
$$
ans=\prod_d (x^d-1)^{f(d)}\\
f(n)=\sum_{n|d}\mu(\frac{d}{n})g(c(n))\\
g(n)=\sum_{i=1}^{n}(-1)^{i-1}\begin{pmatrix}n \\ i\end{pmatrix}
$$
$c(n)$ 是倍数出现次数。

发现 $g(n)=1$。


但是这样中间枚举倍数时复杂度会转到值域上。

考虑另一种莫反，记 $F(x)$ 表示 $\gcd$ 至少为 $x$ 时的转移系数之和。
$$
F(x)=\sum (-1)^{|S|+1}[x|k,\forall k\in S]
$$
发现 $F$ 就是 $g$，所以 $F(x)=1$。

我们现在要容斥出 $\gcd$ 为 $x$ 的转移系数，那么用 $F(x)$ 减去会出现的 $x|y$ 且 $x\ne y$ 的 $F(y)$ 即可。

做完了。

深层次地，$\mu$ 应该是指的对于值域上的数的容斥，对于值域很大但可能出现的数很少的情况下，可以考虑第二种莫反。

---

## 作者：C6H14 (赞：0)

[传送门](https://www.luogu.com.cn/problem/P3598)

## 题目大意

令 $\operatorname{f}(n)=\sum \limits_{i=0}^n x^i$，求 $
\operatorname{lcm} (\operatorname{f}(a_1),\dots,\operatorname{f}(a_n)) \mod (10^9+7)
$，其中 $1 \leqslant n \leqslant 100$，$0 \leqslant a_i \leqslant10^9$，$2 \leqslant x \leqslant 10^{18}$。

## 分析

一道~~人类智慧的~~数学题。

出题人说过数据保证 $x-1$ 不是 $10^9+7$ 的倍数，所以大胆将 $\operatorname{f}(n)$ 化简为 $\dfrac{x^{n+1}-1}{x-1}$，那么答案就可以表示为 $\dfrac{\operatorname{lcm}(x^{a_1}-1,\dots,x^{a_n}-1)}{x-1}$。

然后作为一名蒟蒻，~~显然我毫无思路~~，直接想 $n=2$ 的情况，显然这时候答案可以表示为 $\dfrac{(x^{a_1}-1)(x^{a_2}-1)}{(x-1) \cdot \gcd (x^{a_1}-1,x^{a_2}-1)}$，关键在于怎么求 $\gcd$。

手玩一下 $x=2$ 的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/t4hu5vp7.png)

观察这些数字，我们可以看到 $a_i=4$ 和 $a_i=6$ 的 $\gcd$ 恰好是 $3$，也就是 $a_i=2$ 的情况。

而这三个数的关系是 $\gcd(4,6)=2$，于是我们~~瞎猜~~合理推断：

$$
\gcd(x^a-1,x^b-1)=x^{\gcd(a,b)}-1
$$

~~随便~~证明一下 $(a > b)$：

$$
\begin{aligned}
\gcd(x^a-1,x^b-1) & = \gcd(x^a-1-x^b+1,x^b-1) \\
& = \gcd((x^{a-b}-1)x^b,x^b-1) \\
& = \gcd(x^{a-b}-1,x^b-1)
\end{aligned}
$$

可以辗转相除，所以猜测成立。

下一步考虑对于 $n > 2$ 的时候怎么将 $\operatorname{lcm}$ 转化为 $\gcd$。

考虑质因数分解，对于一个特定的质数 $p$，设它在 $n$ 质因数分解后出现的次数为 $\operatorname{v}_p(n)$，那么 $\operatorname{v}_p(\operatorname{lcm}(a_1,\cdots,a_n))=\max(\operatorname{v}_p(a_1),\cdots,\operatorname{v}_p(a_n))$，$\operatorname{v}_p(\gcd(a_1,\cdots,a_n))=\min(\operatorname{v}_p(a_1),\cdots,\operatorname{v}_p(a_n))$。

由 $\min-\max$ 容斥可得 $\operatorname{v}_p(\operatorname{lcm}(a_1,\cdots,a_n))=\sum \limits_{S \subseteq {\{1,2,\cdots,n\}}} (-1)^{\left| S\right|-1} \operatorname{v}_p(\gcd \limits_{k \in S}(a_k))$，综合起来就是 $\operatorname{lcm}(a_1,\cdots,a_n)$ 为 $\{ a_i\}$ 中所有奇数元子集各自 $\gcd$ 的积除以所有偶数元子集各自 $\gcd$ 的积。

注意到 $\gcd$ 的数量不多，可以不断将新的数和前面已求得的所有 $\gcd$ 都操作一次，更新 $\gcd$ 的数量以及答案。

---

