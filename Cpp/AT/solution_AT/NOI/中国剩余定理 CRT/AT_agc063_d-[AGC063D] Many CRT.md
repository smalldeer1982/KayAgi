# [AGC063D] Many CRT

## 题目描述

给定正整数 $N,\ a,\ b,\ c,\ d$。

请判断是否存在非负整数 $x$，使得对于所有 $k=0,1,\ldots,N-1$，都有 $x\equiv a+kb\pmod{c+kd}$。如果存在，请输出所有满足条件的 $x$ 中最小的一个对 $998244353$ 取模的结果；如果不存在，请输出 $-1$。

## 说明/提示

## 限制

- $2\leq N\leq 10^6$
- $1\leq a,b,c,d\leq 10^6$

## 样例解释 1

满足 $x\equiv 1\pmod{3}$ 且 $x\equiv 3\pmod{7}$ 的最小非负整数为 $x=10$。

## 样例解释 2

不存在满足 $x\equiv 1\pmod{10}$ 且 $x\equiv 2\pmod{20}$ 的非负整数。

## 样例解释 3

满足条件的最小非负整数为 $x=0$。

## 样例解释 4

满足条件的最小非负整数为 $x=15977769171609124$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 1 2 3 4```

### 输出

```
10```

## 样例 #2

### 输入

```
2 1 1 10 10```

### 输出

```
-1```

## 样例 #3

### 输入

```
100 20 30 2 3```

### 输出

```
0```

## 样例 #4

### 输入

```
9 12 34 56 78```

### 输出

```
827501367```

# 题解

## 作者：Lynkcat (赞：9)

推一下式子：

$$x \equiv a+bk\ (\bmod c+dk)$$

两边同乘 $d$，这一步需要 $\gcd(c,d)=1$，我们先假设它成立

$$dx \equiv ad+bkd\ (\bmod c+dk)$$
$$dx \equiv ad-bc\ (\bmod c+dk)$$
设 $M=\text{lcm}_{k=0}^{n-1}(c+dk)$，则
$$dx \equiv ad-bc\ (\bmod \ M)$$

$$(My+(ad-bc)\bmod M)\equiv 0 \bmod d$$

如果我们能解出最小的 $y$ 满足 $(My+(ad-bc)\bmod M)\equiv 0 \bmod d$ 且 $0\leq My+(ad-bc)\bmod M$，那么 $x$ 即为 $\frac{My+(ad-bc)\bmod M}{d}$。

发现上面这个方程 $M$ 只需要其模 $d$ 的值，我们尝试通过分裂质因数的方法来计算 $M$，但是级别太大。

但是我们发现 $c+di$ 与 $c+dj$ 有公因数 $g$ 时，$g$ 也是 $c+dj-c-di=d(j-i)$ 的因数，所以 $g$ 要么是 $d$ 的因数要么是 $j-i$ 的因数，但实际不可能只是 $d$ 的因数，因为如果有 $g|c+di$ 且 $g|d$ 那么一定有 $g|c$，与 $\gcd(c,d)=1$ 相矛盾。所以有 $g\leq n$ ，也就是说我们用 $n$ 范围内的质因数做消除完后，剩余的数要么是 $1$ 要么是一个大于 $n$ 的质数且是唯一的，可以直接乘。



尝试对 $1e6$ 内的质因数 $i$ 去做消除，我们用 exgcd 求出最小的 $k$ 满足 $i|c+dk$，那么不难发现满足 $i|c+dj$ 的 $j$ 一定满足 $j=k+ix$，直接一个个暴力消就行了。

求出 $M$ 之后我们就可以直接枚举 $y$ 了，需要注意的一点是由于要满足 $0\leq My+(ad-bc)\bmod M$，我们需要得到 $(ad-bc)\bmod M$ 的值，但当 $ad-bc<0$ 且 $M$ 很大的情况我们无法得到 $(ad-bc)\bmod M$ 的值，这个时候只能直接用 $ad-bc$ 的值，然后跳过 $y=0$。

现在唯一需要解决的是更一般的情况，即 $\gcd(c,d)\not =1$。但是其实也是容易的，令 $g=\gcd(c,d)$，显然必须有 $x\equiv a\ (\bmod \ g),b\equiv 0\ (\bmod\ g)$。所以无解的情况是 $b$ 不为 $g$ 的倍数。

把 $x$ 与 $a$ 减去 $ a\bmod g$ 之后剩下的方程中的每个系数都是 $g$ 的倍数，可以直接除以 $g$ 做完之后再将 $x$ 乘 $g$，再加上 $ a\bmod g$ 即可。

可以做到 $\log \log$ 的复杂度。

```c++
// Problem: D - Many CRT
// Contest: AtCoder - AtCoder Grand Contest 063
// URL: https://atcoder.jp/contests/agc063/tasks/agc063_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define poly vector<int>
#define IOS ios::sync_with_stdio(false)
#define ll long long
#define mp make_pair
#define mt make_tuple
#define pa pair < int,int >
#define fi first
#define se second
#define inf 1e18
#define mod 998244353
#define sz(x) (int)((x).size())
#define int ll
#define N 1000005
using namespace std;
int val[N];

inline ll quickPower(ll x,ll y)
{
	ll res=1;
	while (y)
	{
		if (y&1) res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
#define LL ll
LL exgcd(LL a,LL b,LL &x,LL &y){
	LL d=a; if(b==0) x=1,y=0; else{
		d=exgcd(b,a%b,y,x),y-=a/b*x;
	}
	return d;
}
inline int jie(int a,int b,int c)
{
	ll x,y;
	LL d=exgcd(a,b,x,y);
	if (c%d)return -1;
	x*=c/d,y*=c/d;
	d=abs(d);
	LL p=b/d,q=a/d,k;
	
	
	if(y<0) 
	{
		k=(-y+q-1)/q,x-=p*k,y+=q*k;
	}
	else
	if(y>=0) 
	{
		k=(y)/q,x+=p*k,y-=q*k;
	}
	if(x<0) 
	{
		int o=(-x-p-1)/(-p);
		x-=p*o,y+=q*o;
	}
	if (x>=0&&y>=0)
	{
		int o=min(x/(-p),y/q);
		x+=p*o,y-=q*o;
	}
	if (y>=0) return x;
	return -1;
}
bool vis[N];
void BellaKira()
{
	int n,a,b,c,d;
	int aa,bb,cc,dd;
	
	cin>>n>>aa>>bb>>cc>>dd;
	int g=__gcd(cc,dd);
	if (bb%g!=0)
	{
		cout<<-1<<'\n';
		return;
	}
	int dela=aa%g;
	a=aa/g,b=bb/g,c=cc/g,d=dd/g;
	map<int,int>Mp;
	for (int i=0;i<n;i++)
	{
		val[i]=c+d*i;
	}
	int M=1,M1=1,rM=1;
	for (int i=2;i<=1000000;i++)
		if (!vis[i])
		{
			int mx=0;
			int o=jie(d,-i,-c);
			if (o!=-1&&o<n)
			{
				for (int j=o;j<n;j+=i)
				{
					int tt=0;
					while (val[j]%i==0) 
					{
						val[j]/=i;
						tt++;
					}
					mx=max(mx,tt);
				}
				while (mx--) 
				{
					M=M*i%d,M1=M1*i%mod;
					if (inf/rM<i) rM=inf+1;
					else rM*=i;
				}
			}
			for (int j=i+i;j<=1000000;j+=i) vis[j]=1;
		}
	for (int i=0;i<n;i++)
	{
		int u=val[i]; 
		{
			M=M*u%d,M1=M1*(u%mod)%mod;
			if (inf/rM<u) rM=inf+1;
			else rM*=u;
		}
	}
	int oo=a*d-b*c;
	if (rM!=inf+1) oo=(oo%rM+rM)%rM;
	for (int i=0;i<=d;i++)
	{
		if (i==0&&oo<0) continue;
		int o=(M*i+oo%d+d)%d;
		if (o%d==0)
		{
			cout<<((M1*i%mod+oo%mod+mod)%mod
			*quickPower(d,mod-2)%mod
			*g%mod+dela
			)%mod<<endl;
			return;
		}
	}
	cout<<"-1\n";
}
signed main()
{
	IOS;
	cin.tie(0);
	int T=1;
	while (T--)
	{
		BellaKira();
	}
}
```

---

## 作者：MatrixGroup (赞：3)

## 题意

求同余方程 $x\equiv a+bi\pmod{c+di},i=0,1,\cdots,n-1$ 的最小正整数解，模 $p=998{,}244{,}353$，或报告无解。

$2\le n\le10^6,a,b,c,d\le 10^6$

## 题解

先把 $\gcd(c,d)$ 除掉方便做题。具体地，令 $g=\gcd(c,d)$，则若 $g\nmid b$ 则无解（考察 $x\bmod g$），否则解 $x'\equiv \left\lfloor\dfrac ag\right\rfloor+\dfrac bgi\pmod{\dfrac cg+\dfrac dgi},i=0,1,\cdots,n-1$，则 $x=x'\cdot g+(a\bmod g)$。

考虑如何不考虑模 $p$ 计算出答案。你会怎么解下列同余方程？

$$
\begin{cases}
x\equiv 1\pmod 3\\
x\equiv 2\pmod 5\\
x\equiv 3\pmod 7
\end{cases}
$$

答案是：注意到 $2x\equiv -1\pmod {3,5,7}$，故 $x\equiv-\dfrac12\equiv 52\pmod {105}$。

考虑照搬这个思路。$dx\equiv da+dbi\equiv ad-bc\pmod{c+di}$，故 $x\equiv \dfrac{ad-bc}{d}\pmod {c+di}$。（显然因为 $c\perp d$ 所以 $d\perp (c+di)$）令 $L$ 为 $c+di$ 的最小公倍数，则答案是 $\dfrac{ad-bc}{d}\bmod L$。

注意到假如 $L\le2\times10^{12}$ 就可以直接算了。如果不呢？

令 $\dfrac{ad-bc}{d}=q+\dfrac{r}{d}$，其中 $0\le r<d$。不妨先求 $\dfrac{r}{d}\bmod L$。令 $\dfrac{r}{d}\equiv x\pmod L$，那么有 $r+Ly=dx$。令 $y$ 是 $[0,d)$ 中符合要求的那个整数，那么 $x=\dfrac{Ly+r}{d}$。它显然在 $[0,L)$ 之间（因为 $r<10^{12}<L$）！

$r$ 和 $d$ 都是 $\bmod p$ 已知的，只需知道 $L\bmod p$ 和 $y$ 就行了。而 $yL\equiv -r\pmod{d}$，也就是只需知道 $L\bmod d$ 就可以求出 $y$。综上所述，我们需要计算 $L$ 对一个数取模的结果。

考虑将 $L$ 质因数分解。对于 $p\le10^6$，可以枚举它们并用 `exgcd` 找出所有等差数列中能被它们整除的数。把它们除掉后，剩下的必然是 $p>10^6$ 的因子！（实现上的小技巧：容易证明剩下的不会出现重复的素数。）

质因数分解后容易求出以上两值。我们大胆猜测，$\dfrac{r}{d}$ 在模意义下不会是一个绝对值很小的整数，因此可以直接加上 $q$。考虑证明：若 $\dfrac{r}{d}\equiv u\pmod L,|u|\le|q|$，则 $L|(r-ud)$，又 $|r-ud|\le |r|+|ud|\le |r|+|qd|\le 2|r|+|qd+r|=2|r|+|ad-bc|<2\times10^{12}$，所以 $r-ud=0$，换言之 $d|r$，又 $0\le r<d$，故 $r=0$。此时 $\dfrac{ad-bc}{d}=q$，直接判断 $q$ 的正负性，输出 $q$ 或 $q+L$ 模 $p$ 即可。

设 $n,a,b,c,d$ 同阶，那么复杂度是 $O(n\max\limits_{i=1}^{n^2}\omega(i))$。

[实现](https://atcoder.jp/contests/agc063/submissions/46460149) 与所讲略有出入。

---

## 作者：Leasier (赞：2)

- Update on 2023.12.21：感谢 [thomaswmy](https://www.luogu.com.cn/user/531319)。

数论神题，但是 WA 了 7 发 /ng/youl/fn/jw

------------

原题中给出的 $x \equiv a + kb \pmod{c + kd}$ 的模数和余数与 $k$ 有关，考虑通过某些方式把余数中的 $k$ 扔掉。

考虑把余数中的 $kb$ 变成 $kd$ 的倍数。具体地，将同余式左右两边都乘上 $d$，得到 $dx \equiv ad + kbd \equiv ad - bc \pmod{c + kd}$。

- 事实上这里两个同余式间互为充要条件依赖 $\gcd(c, d) = 1$，下文将先默认此条件成立进行处理，最后我们再来讨论 $\gcd(c, d) > 1$ 的情况。

令 $p = \operatorname{lcm}_{i = 0}^{n - 1} (c + id)$，$u = ad - bc$，则 $dx \equiv u \pmod p$。

令 $v$ 为整数，且满足：

- $dx - vp = u, x = \frac{u + vp}{d}$。
- $vp \equiv -u \pmod d$。

设 $v = v_0 + kd$，则 $x = \dfrac{u + v_0 p}{d} + kp$。

- 当 $p \leq |u|$，我们可以直接解出 $k$ 的最佳取值。
- 当 $p > |u|$，若 $u < 0$ 且 $v_0 = 0$，则 $k = 1$；否则，$k = 0$。

现在问题变为如何求出 $p \bmod d, p \bmod 998244353$。

依次考虑每个质数 $P^2 \leq Q = c + (n - 1) d$，exgcd 解出满足 $P \mid c + id$ 的第一个 $i$，然后依次遍历所有符合条件的 $i$，最后再加上 $> Q$ 的质数的贡献即可。记得剩下的质数要去重。

最后，我们来考虑 $\gcd(c, d) > 1$ 的情况。

设 $g = \gcd(c, d)$，由于 $g \mid x - a, x - a - b$，则 $g \mid b$。

设 $a = a'g + r, b = b'g, c = c'g, d = d'g$，则我们只需要解出 $(a', b', c, d')$ 的答案 $x'$，令 $x = x'g + r$ 即可。

综上，时间复杂度为 $O(n \log n + (n + w) \log \log w)$，其中 $w$ 为值域 $10^6$。

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cmath>

using namespace std;

typedef long long ll;
typedef __int128 lll;

const int N = 1e6 + 7, mod = 998244353;
int prime[N];
ll val[N];
bool p[N];

inline int init(ll n){
	int cnt = 0;
	p[0] = p[1] = true;
	for (register ll i = 2; i <= n; i++){
		if (!p[i]) prime[++cnt] = i;
		for (register int j = 1; j <= cnt && i * prime[j] <= n; j++){
			p[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
	return cnt;
}

int gcd(int a, int b){
	return b == 0 ? a : gcd(b, a % b);
}

inline ll sqrt(ll n){
	ll ans = sqrt((double)n);
	while (ans * ans <= n) ans++;
	return ans - 1;
}

ll gcd(ll a, ll b){
	return b == 0 ? a : gcd(b, a % b);
}

void exgcd(ll a, ll b, ll &x, ll &y){
	if (b == 0){
		x = 1;
		y = 0;
		return;
	}
	ll t;
	exgcd(b, a % b, x, y);
	t = x;
	x = y;
	y = t - a / b * y;
}

inline ll inv(ll a, ll b){
	ll x, y;
	exgcd(a, b, x, y);
	return (x % b + b) % b;
}

inline ll solve(ll a, ll b, ll c){
	ll d = gcd(a, c);
	if (b % d != 0) return -1;
	a /= d;
	b /= d;
	c /= d;
	return b * inv(a, c) % c;
}

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

int main(){
	int n, a, b, c, d, g;
	cin >> n >> a >> b >> c >> d;
	g = gcd(c, d);
	if (b % g != 0){
		cout << -1;
		return 0;
	}
	int r, cnt, n_;
	ll x, up, y = 1, z = 1, v = 1, w;
	r = a % g;
	a /= g;
	b /= g;
	c /= g;
	d /= g;
	x = (ll)a * d - (ll)b * c;
	up = llabs(x) + 1;
	for (register int i = 0; i < n; i++){
		val[i] = c + (ll)i * d;
	}
	cnt = init(sqrt(val[n - 1]));
	for (register int i = 1; i <= cnt; i++){
		ll fst = solve(d, ((prime[i] - c) % prime[i] + prime[i]) % prime[i], prime[i]);
		if (fst == -1) continue;
		int power = 0;
		ll delta = prime[i] / gcd(d, prime[i]);
		for (register ll j = fst; j < n; j += delta){
			int cur_power = 0;
			while (val[j] % prime[i] == 0){
				val[j] /= prime[i];
				cur_power++;
			}
			if (power < cur_power) power = cur_power;
		}
		for (register int j = 1; j <= power; j++){
			y = y * prime[i] % mod;
			z = z * prime[i] % d;
			v = min((lll)v * prime[i], (lll)up);
		}
	}
	sort(val, val + n);
	n_ = unique(val, val + n) - val - 1;
	for (register int i = 0; i <= n_; i++){
		y = y * (val[i] % mod) % mod;
		z = z * (val[i] % d) % d;
		v = min((lll)v * val[i], (lll)up);
	}
	w = ((d - x) % d * inv(z, d) % d + d) % d;
	if (v < up){
		cout << (((x + w * v) / d % v + v) % v * g % mod + r) % mod;
	} else {
		int t;
		if (x >= 0 || w > 0){
			t = 0;
		} else {
			t = 1;
		}
		cout << ((((x + w * z) / d + w * (y - z) % mod * quick_pow(d, mod - 2, mod) % mod + t * y % mod) * g % mod + r) % mod + mod) % mod;
	}
	return 0;
}
```

---

