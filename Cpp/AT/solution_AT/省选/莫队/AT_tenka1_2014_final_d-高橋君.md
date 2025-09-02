# 高橋君

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tenka1-2014-final/tasks/tenka1_2014_final_d

文字列 $ S $ は、次の条件を満たすとき高橋君であるという。

> - $ S $ は、 `0`, `1`のみからなる文字列である。
> - $ S $ の長さがちょうど $ n $ である。
> - $ S $ は高々 $ k $ 個の `1` を含む。

高橋君の個数を $ 1000000007 $ で割った余りを求めよ。

## 说明/提示

### 部分点

$ 0≦k_i≦n_i≦3000 $ の条件を満たすテストケースに全て正解した場合、 $ 50 $ 点が得られる。

全てのテストケースに正解した場合、さらに $ 150 $ 点が得られる。

高橋君の個数を $ 1000000007 $ で割った余りをそれぞれ $ 1 $ 行ずつ、 $ T $ 行で出力せよ。出力の末尾には改行をいれること。

### Sample Explanation 1

$ n=1 $, $ k=1 $ の時、高橋君は、`0`, `1` の $ 2 $ つです。 $ n=3 $, $ k=2 $ の時、高橋君は、`000`, `001`, `010`, `011`, `100`, `101`, `110` の $ 7 $ つです。 大きな数の時には、 $ 1000000007 $ で割った余りを出力することに注意してください。

## 样例 #1

### 输入

```
10
1 1
3 2
5 2
8 3
12 0
642 246
2222 999
2525 21
50000 25000
100000 100000```

### 输出

```
2
7
16
93
1
321969783
856998846
371661809
969409843
607723520```

# 题解

## 作者：Mr_Wu (赞：14)

#### 题意

$T$个询问，每次询问给出$n,k$，你需要回答
$$
\sum_{i=0}^{k} C_n^i \mod 10^9+7
$$
数据范围：$1\le T\le 100000, 0\le n,k\le 100000$



#### 莫队

这题需要用普通莫队算法。

我们将每个询问$(n,k)$离线存下来，并用莫队处理区间问题的方法将其分块后排序。（$n$当做左端点，$k$当做右端点）

我们知道要想用莫队算法，就需要知道$(n,k)$的答案和$(n,k+1),(n,k-1),(n-1,k),(n+1,k)$这四种询问的答案的联系。也就是说当前指针指向$(n,k)$时，我们需要$O(1)$地算出上述询问的答案。



#### 组合数

先找$(n,k)$的答案和$(n,k+1),(n,k-1)$的答案的关系。

很容易就能发现：

$\sum_{i=0}^{k+1} C_n^i=(\sum_{i=0}^{k} C_n^i) + C_n^{k+1}$

$\sum_{i=0}^{k-1} C_n^i=(\sum_{i=0}^{k} C_n^i) - C_n^{k+1}$

然后我们来找$(n,k)$和$(n-1,k),(n+1,k)$的关系，注意到有这个等式：

$C_n^m=C_{n-1}^m+C_{n-1}^{m-1}$

所以我们可以这么推：

$\sum_{i=0}^{k} C_{n+1}^k=(\sum_{i=1}^{k} (C_n^k+C_n^{k-1}))+1$

$= (\sum_{i=1}^{k} C_n^k+\sum_{i=0}^{k-1}C_n^i)+1$

$= (2\times \sum_{i=0}^{k-1}C_n^i+C_n^k )+1$

$= 2\sum_{i=0}^{k}C_n^i-C_n^k$

然后反过来推出
$\sum_{i=0}^{k} C_{n-1}^i=\frac{1}{2}((\sum_{i=0}^{k} C_n^i)+C_{n-1}^{k})$

综上所述：

$\sum_{i=0}^{k+1} C_n^i=(\sum_{i=0}^{k} C_n^i) + C_n^{k+1} $

$\sum_{i=0}^{k-1} C_n^i=(\sum_{i=0}^{k} C_n^i) - C_n^{k}$

$\sum_{i=0}^{k} C_{n+1}^i=2\sum_{i=0}^{k}C_n^i-C_n^k$

$\sum_{i=0}^{k} C_{n-1}^i=\frac{1}{2}((\sum_{i=0}^{k} C_n^i)+C_{n-1}^{k})$

注意到我们在转移时需要以$O(1)$的复杂度求出单个逆元，所以预处理1-100000中每个数的逆元，以及阶乘的逆元，就能做到。



####  代码

```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

#define MOD 1000000007ll
#define MAXN 200005
typedef long long ll;
typedef unsigned long long ull;
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

ll read()
{
    char c = getchar();
    ll ret = 0;
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') ret = ret * 10 + c - '0', c = getchar();
    return ret;
}

int N;
ll blocklen, pn = 1, pk = 0, anst = 1, inv[MAXN], mul[MAXN], mulinv[MAXN], ans[MAXN], inv2 = (MOD + 1) >> 1; //pn, pk是莫队用的指针，anst是临时答案，mul是阶乘，mulinv是阶乘逆元，inv是逆元，ans存答案（因为离线存储打乱了顺序），inv2是2的逆元
struct query
{
    ll n, k, id, block;
} Q[MAXN];
bool cmp(query q1, query q2)
{
    if (q1.block != q2.block) return q1.block < q2.block;
    else return q1.k < q2.k;
}
ll ask(ll n, ll m)
{
    return ((mul[n] * mulinv[m]) % MOD * mulinv[n - m]) % MOD;
} //ask(n,m)询问C_n^m mod 10^9+7
void move(int t)
{
    switch(t)
    {
        case 1: anst = ((anst + ask(pn, pk + 1)) % MOD + MOD) % MOD, ++pk; break;
        case 2: anst = ((anst - ask(pn, pk)) % MOD + MOD) % MOD, --pk; break;
        case 3: anst = (((2 * anst) % MOD - ask(pn, pk)) % MOD + MOD) % MOD, ++pn; break;
        case 4: anst = ((inv2 * ((anst + ask(pn - 1, pk)) % MOD)) % MOD + MOD) % MOD, --pn; break;
    } //1为从(n,k)到(n,k+1)，2为到(n,k-1)，3为到(n+1,k)，4为到(n-1,k)
}

int main()
{
    N = read(), blocklen = sqrt(N);
    int i;
    inv[1] = 1, mul[0] = mulinv[0] = 1;
    for (i = 2; i <= 100000; ++i) inv[i] = ((MOD - MOD / i) * inv[MOD % i]) % MOD, mul[i] = (mul[i - 1] * (ll)i) % MOD; //线性求逆元
    for (i = 1; i <= 100000; ++i) mul[i] = (mul[i - 1] * i) % MOD, mulinv[i] = (mulinv[i - 1] * inv[i]) % MOD;
    for (i = 1; i <= N; ++i) Q[i].n = read(), Q[i].k = read(), Q[i].id = i, Q[i].block = Q[i].n / blocklen;
    sort(Q + 1, Q + N + 1, cmp);
    for (i = 1; i <= N; ++i)
    {
        while (pn < Q[i].n) move(3);
		while (pn > Q[i].n) move(4);
        while (pk < Q[i].k) move(1);
		while (pk > Q[i].k) move(2); //莫队板子
        ans[Q[i].id] = anst;
    }
    for (i = 1; i <= N; ++i) printf("%lld\n", ans[i]);
    return 0;
}
```



---

## 作者：ღꦿ࿐ (赞：8)

为啥这题解区一片莫队？？

很多时候需要用到多次查询组合数前缀和的话还是在线比较方便吧。

令 

$$

f(n,m)=\sum_{i=0}^m \binom n i
$$

显然有 $f(n,m)=f(n,m-1)+\binom n m$，考虑竖推，

$$

\begin{aligned}

f(n-1,m)&=\sum_{i=0}^m \binom {n-1} i\\

f(n,m)&=\sum_{i=0}^m \binom n i \\

&=\sum_{i=0}^m\left(\binom {n-1} {i-1}+\binom {n- 1} i \right) \\

&=2\sum_{i=0}^{m-1}\binom {n-1} i+\binom {n-1} i \\

&=2f(n-1,m)-\binom {n-1} m


\end{aligned}
$$

然后可以横竖推了。

因为保存的信息量是 $O(1)$ 的，所以直接在平面上撒 $O(n) $ 个点，然后由最近的点推过来就是 $O(\sqrt n)$ 的，具体实现可以在每隔 $\sqrt n$ 行处理一行，每行处理完后保留间隔为 $\sqrt n$ 的 $\sqrt n$ 个点就行了。

运用块长相关知识可以得到间隔是 $O(\dfrac n {\sqrt T})$ 时，时间 $O( n \sqrt {T})$，空间 $O(T)$。


相关：


[例](https://www.luogu.com.cn/problem/AT_tenka1_2014_final_d)

[例](https://atcoder.jp/contests/abc235/tasks/abc235_g)

[例](https://kedacun.ac/p/K1520)

[EI 的低复杂度做法](https://blog.csdn.net/EI_Captain/article/details/113142893)



---

## 作者：Arghariza (赞：6)

[可能更好的阅读体验](https://www.cnblogs.com/Ender32k/p/16096965.html)

- $\mathtt{description}$：

$t$ 组询问，每组给出 $n,k\le 10^5$，求 $\begin{aligned}\sum\limits_{i=0}^{k}\dbinom{n}{i}\end{aligned}$，
$t\le 10^5$。

- $\mathtt{Solution}$：

$n\to n+1$ 时：

$$\begin{aligned}\sum\limits_{i=0}^{k}\dbinom{n+1}{i}&=\sum\limits_{i=0}^{k}\begin{pmatrix}\dbinom{n}{i}+\dbinom{n}{i-1}\end{pmatrix}\\&=2\sum\limits_{i=0}^{k}\dbinom{n}{i}-\dbinom{n}{k}\end{aligned}$$

移项反解得 $n\to n-1$ 时：

$$\begin{aligned}\sum\limits_{i=0}^{k}\dbinom{n-1}{i}=\dfrac{\sum\limits_{i=0}^{k}\dbinom{n}{i}+\dbinom{n}{k}}{2}\end{aligned}$$

$k\to k+1$ 时：

$$\begin{aligned}\sum\limits_{i=0}^{k+1}\dbinom{n}{i}=\sum\limits_{i=0}^{k}\dbinom{n}{i}+\dbinom{n}{k+1}\end{aligned}$$

同理，$k\to k-1$ 时:

$$\begin{aligned}\sum\limits_{i=0}^{k-1}\dbinom{n}{i}=\sum\limits_{i=0}^{k}\dbinom{n}{i}-\dbinom{n}{k+1}\end{aligned}$$

注意到上面四个转移式的余项都为单个组合数，而预处理阶乘及逆元计算组合数时 $O(1)$ 的，所以上述四个转移也是 $O(1)$ 的。

莫队即可，复杂度 $O(n\sqrt n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
namespace mystd {
	inline int read() {
	    char c = getchar();
	    int x = 0, f = 1;
	    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
	    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + c - '0', c = getchar();
	    return x * f;
	}
	inline void write(int x) {
	    if (x < 0) x = ~(x - 1), putchar('-');
	    if (x > 9) write(x / 10);
	    putchar(x % 10 + '0');
	}
}
using namespace std;
using namespace mystd;

const int maxn = 2e5 + 200;// 不知道为啥要开大的空间，不然就过不去样例
const int mod = 1e9 + 7;
int n, l, r, b, c, mx, ans[maxn], fac[maxn], inv[maxn], ifac[maxn];
struct qry {
	int l, r, id;
	bool operator < (const qry &rhs) const {
		return l / b == rhs.l / b ? r < rhs.r : l < rhs.l;
	}
} q[maxn];

int C(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }
void addr() { c = ((c * 2 % mod - C(r++, l)) % mod + mod) % mod; }
void delr() { c = inv[2] * ((c + C(--r, l)) % mod) % mod; }
void addl() { c = ((c - C(r, l--)) % mod + mod) % mod; }
void dell() { c = (c + C(r, ++l)) % mod; }

signed main() {
	n = read(), b = sqrt(n); 
	for (int i = 1; i <= n; i++) {
		q[i] = (qry) { read(), read(), i };
		swap(q[i].l, q[i].r);
		mx = max(mx, q[i].r);
	}
	sort(q + 1, q + n + 1);
	r = 1, c = 1;
	fac[0] = inv[1] = ifac[0] = 1;
	for (int i = 1; i <= mx; i++) {
		if (i >= 2) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
		fac[i] = fac[i - 1] * i % mod;
		ifac[i] = ifac[i - 1] * inv[i] % mod;
	}
	for (int i = 1; i <= n; i++) {
		while (l > q[i].l) addl();
		while (l < q[i].l) dell();
		while (r < q[i].r) addr();
		while (r > q[i].r) delr();
		ans[q[i].id] = c;
	}
	for (int i = 1; i <= n; i++) write(ans[i]), puts("");
	return 0;
}

```

---

## 作者：SunsetSamsara (赞：4)

## 前置知识
数学，莫队
## 分析
因为出现 $i$ 个 $1$ 的情况有 $C^i_n$种，所以这题每个询问 $n,k$ 的答案就是 $\sum\limits_{i=0} \limits^k C^i_n$。

既然想到了莫队，那就想想如何转移。

当 $n$ 需要加上 $1$ 时：

因为 $C^i_{n+1}=C^i_n+C_n^{i-1}$，所以有
$$\sum\limits_{i=0} \limits^k C^i_{n+1}=\sum\limits_{i=1} \limits^k({C^i_n+C_n^{i-1}})+C_{n+1}^0$$

于是得到
$$\sum\limits_{i=0} \limits^k C^i_{n+1}=\sum\limits_{i=0} \limits^kC^i_n+\sum\limits_{i=0} \limits^kC_n^{i-1}+1$$

$$\sum\limits_{i=0} \limits^k C^i_{n+1}=2\sum\limits_{i=0} \limits^kC^i_n-1-C^k_n+1$$

$$\sum\limits_{i=0} \limits^k C^i_{n+1}=2\sum\limits_{i=0} \limits^kC^i_n-C^k_n$$

当 $n$ 需要减去 $1$ 时，同理有

$$\sum\limits_{i=0} \limits^k C^i_{n-1}=\dfrac{1}{2}(\sum\limits_{i=1} \limits^kC^i_n+C^k_{n-1})$$

当 $k$ 需要加上 $1$ 时，显然有

$$\sum\limits_{i=0} \limits^{k+1} C^i_n=\sum\limits_{i=0} \limits^k C^i_n+C^{k+1}_n$$

当 $k$ 需要减去 $1$ 时，显然有

$$\sum\limits_{i=0} \limits^{k-1} C^i_n=\sum\limits_{i=0} \limits^k C^i_n-C^{k-1}_n$$

最后注意到 $n$ 和 $k$ 的值域在 $10^5$ 之内，简单地预处理出每个数的逆元、阶乘与阶乘的逆元就可以 $O(1)$ 算出组合数了。

## 代码

```cpp
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#pragma GCC optimize("Ofast,fast-math")
#pragma GCC target("avx,avx2")
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
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
#define log() printf("Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__)
#define il inline __attribute__((always_inline))
const int mod = 1e9 + 7;
const int inv2 = (mod + 1) / 2;
const int N = 100010;
inline int qpow(int a, int b, int p) {
	int ret = 1;
	for (; b; b >>= 1, a = 1ll * a * a % p)
		if (b & 1) ret = 1ll * ret * a % p;
	return ret;
}
int T;
int inv[N], fac[N], ifac[N];
struct req {
	int n, k, blk, id;
} q[N];
int ANS[N];
int blksiz;
inline bool operator < (const req &x, const req &y) {
	return (x.blk ^ y.blk) ? (x.blk < y.blk) : (x.k < y.k);
}
inline int C(int n, int m) {
	return 1ll * ifac[n - m] * ifac[m] % mod * fac[n] % mod; 
}
int curn, curk, ans;
inline void addk() {
	ans = (ans + C(curn, ++ curk)) % mod;
}
inline void subk() {
	ans = (ans + mod - C(curn, curk --)) % mod;
}
inline void addn() {
	ans = ((ans << 1) % mod + mod - C(curn ++, curk)) % mod;
}
inline void subn() {
	ans = 1ll * (ans + C(-- curn, curk)) % mod * inv2 % mod;
}
int main() {
	fac[0] = 1;
	for (int i = 1; i < N; ++ i) fac[i] = 1ll * fac[i - 1] * i % mod;
	ifac[N - 1] = qpow(fac[N - 1], mod - 2, mod);
	for (int i = N - 2; ~i; -- i) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
	scanf("%d", &T);
	blksiz = sqrt(T);
	for (int i = 1; i <= T; ++ i)
		scanf("%d%d", &q[i].n, &q[i].k), q[i].id = i, q[i].blk = q[i].n / blksiz;
	sort(q + 1, q + T + 1);
	curn = 1; curk = 0; ans = 1;
	for (int i = 1; i <= T; ++ i) {
		for (; curn < q[i].n; addn());
		for (; curn > q[i].n; subn());
		for (; curk < q[i].k; addk());
		for (; curk > q[i].k; subk());
		ANS[q[i].id] = ans;
	}
	for (int i = 1; i <= T; ++ i)
		printf("%d\n", ANS[i]);
}
```

---

## 作者：mmdxmakioi (赞：2)

发现一个非常美妙的性质，就是 $\sum\limits^k_{i=0} \binom {n}{i} $ 能 $O(1)$ 转移到 $\sum\limits^k_{i=0} \binom {n+1}{i} $ 和 $\sum\limits^{k+1}_{i=0} \binom {n}{i} $。

发现如果要转移到 $\sum \binom {n+1}{i}$，观察杨辉三角发现就是乘二再减去 $\binom {n}{k}$。

另外一种转移是平凡的，略去。

所以可以莫队 $O(n\sqrt n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
int q;
int bl;
int fac[100001],ifac[100001];
int ksm(int a,int b)
{
	int rt=1;
	while(b!=0)
	{
		if(b&1)
		{
			rt*=a;
			rt%=MOD;
		}
		a*=a;
		a%=MOD;
		b>>=1;
	}
	return rt;
}
const int c2=ksm(2,MOD-2);
void init()
{
	int i,j;
	fac[0]=1;
	for(i=1;i<=100000;i++)fac[i]=fac[i-1]*i%MOD;
	ifac[0]=1;
	for(i=1;i<=100000;i++)ifac[i]=ksm(fac[i],MOD-2); 
}
int C(int x,int y)
{
//	cerr<<x<<' '<<y<<" wtdmd\n";
	return fac[x]*ifac[y]%MOD*ifac[x-y]%MOD;
}
struct node
{
	int l,r,id;
	bool operator < (const node &aa)const
	{
		if(l/bl==aa.l/bl)
		{
			return r<aa.r;
		}
		else
		{
			return l<aa.l;
		}
	}
}query[200001];
int ans[200001];
signed main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>q;bl=sqrt(q);
	init();
	int i,j;
	for(i=1;i<=q;i++)
	{
		cin>>query[i].r>>query[i].l;
		query[i].id=i;
	}
	sort(query+1,query+1+q);
	int l=query[1].l,r=query[1].r;
	int Ans=0;
	for(i=0;i<=l;i++)
	{		Ans+=C(r,i);
		Ans%=MOD;
	}
	ans[query[1].id]=Ans;
	for(i=2;i<=q;i++)
	{
		int L=query[i].l,R=query[i].r;
		while(r>R)
		{
			Ans+=C(r-1,l);
			Ans%=MOD;
			Ans*=c2;
			Ans%=MOD;
			r--; 
		}
		while(r<R)
		{
			Ans*=2;
			Ans%=MOD;
			Ans-=C(r,l);
			Ans+=MOD;
			Ans%=MOD;
			r++;
		}
		while(l<L)
		{
			l++;
			Ans+=C(r,l);
			Ans%=MOD;
		}
		while(l>L)
		{
			Ans-=C(r,l);
			Ans+=MOD;
			Ans%=MOD;
			l--;
		}
		
		ans[query[i].id]=Ans;
	}
	for(i=1;i<=q;i++)
	{
		cout<<ans[i]<<"\n";
	}
 } 
```


---

## 作者：JWRuixi (赞：2)

~~尽然看错了模数调了一晚上……~~

- 题意

$m$ 组询问，每次给定 $n,k$，求 $\sum\limits_{i=0}^k \binom{n}{i}$。

$1 \le n,m,k \le 10^5$。

- 分析

注意到数据范围非常的像根号算法，由于 $(n,k)$ 可以看作一个两个端点不断移动，所以可以考虑莫队。

$k$ 的移动非常简单，直接加上或减去 $\binom{n}{k}$ 即可，但是 $n$ 怎么移动呢？

记 $f(n,k)=\sum\limits_{i=0}^k \binom{n}{i}$，我们可以考虑有恒等式 $\binom{n}{k}=\binom{n-1}{k}+\binom{n-1}{k-1}$ 来对其做变形（~~不会有不会证这个不等式的把~~），于是有：

$$f(n,k)=\sum\limits_{i=0}^k \binom{n}{i}=1+\sum\limits_{i=1}^k \binom{n}{i}$$

$$=\binom{n-1}{0}+\sum\limits_{i=1}^{k} \binom{n-1}{i}+\sum\limits_{i=1}^k \binom{n-1}{i-1}$$

$$=2\times\sum\limits_{i=0}^{k-1} \binom{n-1}{i}+\binom{n-1}{k}$$

$$=2\times\sum\limits_{i=0}^k \binom{n-1}{i}-\binom{n-1}{k}$$

于是我们就学会如何移动 $n$ 了，那这道题就可以快乐的莫对了！

- code

```cpp
#include <bits/stdc++.h>
#define int long long
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
using namespace std;

namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using IO::read;
using IO::write;

const int maxn(1e5 + 500), i2(500000004), mod(1e9 + 7);
int n, m, sqn, ans[maxn], fac[maxn], inv[maxn], ifac[maxn];

void init () {
	fac[0] = inv[1] = ifac[0] = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	for (int i = 2; i <= n; i++) inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	for (int i = 1; i <= n; i++) ifac[i] = ifac[i - 1] * inv[i] % mod;
}

int c (int i, int j) {
	if (i < j) return 0;
	return fac[i] * ifac[i - j] % mod * ifac[j] % mod;
}

struct qNode {
	int l, r, id;
	inline bool operator < (const qNode &rhs) const {
		if (l / sqn == rhs.l / sqn) return (l / sqn) & 1 ? r < rhs.r : r > rhs.r;
		return l < rhs.l;
	}
} q[maxn];

signed main () {
	m = read(), sqn = sqrt(m);
	for (int i = 1; i <= m; i++) q[i] = {read(), read(), i};
	for (int i = 1; i <= m; i++) n = max({n, q[i].l, q[i].r});
	init();
	sort(q + 1, q + m + 1);
	for (int i = 1, l = 1, sum = 1, r = 0; i <= m; i++) {
		while (l < q[i].l) sum = (sum * 2 - c(l++, r) + mod) % mod;
		while (l > q[i].l) sum = (sum + c(--l, r)) % mod * i2 % mod;
		while (r < q[i].r) sum = (sum + c(l, ++r)) % mod;
		while (r > q[i].r) sum = (sum - c(l, r--) + mod) % mod;
		ans[q[i].id] = sum;
	}
	for (int i = 1; i <= m; i++) write(ans[i]), puts("");
}
```

---

## 作者：int_R (赞：1)

[高橋君](https://www.luogu.com.cn/problem/AT_tenka1_2014_final_d)

[更好的阅读体验](https://www.cnblogs.com/int-R/p/AT_tenka1_2014_final_d.html)

给定若干个 $n,m$，求 $\sum\limits_{i=0}^{m} \dbinom{n}{i}$。为方便，记 $C(n,m)=\dbinom{n}{m},S(n,m)=\sum\limits_{i=0}^{m} C(n,i)$。

我们知道 $C(n,m)=C(n-1,m-1)+C(n-1,m)$，那么：

$$S(n,m)=C(n-1,0)+\sum\limits_{i=1}^{m} C(n-1,i-1)+C(n-1,i)=2S(n-1,m)-C(n-1,m)$$

变形得到：

$$
S(n-1,m)=\dfrac{S(n,m)+C(n-1,m)}{2}
$$
$$
S(n+1,m)=2S(n,m)-C(n,m)
$$

同时又有：

$$
S(n,m-1)=S(n,m)-C(n,m)
$$
$$
S(n,m+1)=S(n,m)+C(n,m+1)
$$

所以发现 $n,m$ 可以 $O(1)$ 加减 $1$，用莫队维护，初始时 $S(0,0)=1$，时间复杂度 $O(W\sqrt q)$，$W$ 为值域，最大为 $10^5$。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<math.h>
using namespace std;
const int MAXN=1e5+10,MOD=1e9+7;
int t,N,len,bel[MAXN],ANS[MAXN];
long long P[MAXN],inv[MAXN],ans=1;
struct node{int n,m,pos;}p[MAXN];
inline bool cmp(node x,node y)
{
    if(bel[x.n]!=bel[y.n]) return x.n<y.n;
    return (bel[x.n]&1)?x.m<y.m:x.m>y.m;
}
inline long long C(int n,int m)
{
    if(n<m) return 0;
    return P[n]*inv[m]%MOD*inv[n-m]%MOD;
}
inline long long ksm(long long a,int b)
{
    long long ans=1;
    while(b)
    {
        if(b&1) ans=ans*a%MOD;
        a=a*a%MOD,b>>=1;
    }
    return ans;
}
int main()
{
#ifdef ONLINE_JUDGE
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
#endif
    cin>>t;
    for(register int i=1;i<=t;++i)
    {
        cin>>p[i].n>>p[i].m;
        N=max(N,p[i].n);p[i].pos=i;
    }
    len=N/sqrt(t);
    for(register int i=1;i<=N;++i) bel[i]=(i-1)/len+1;
    sort(p+1,p+t+1,cmp);
    P[0]=1;for(register int i=1;i<=N;++i) P[i]=P[i-1]*i%MOD;
    inv[N]=ksm(P[N],MOD-2);for(register int i=N-1;i>=0;--i) inv[i]=inv[i+1]*(i+1)%MOD;
    for(register int i=1,n=0,m=0;i<=t;++i)
    {
        while(n<p[i].n) ans=(ans*2-C(n,m))%MOD,++n;
        while(m>p[i].m) ans=(ans-C(n,m))%MOD,--m;
        while(n>p[i].n) ans=(ans+C(n-1,m))%MOD*500000004%MOD,--n;
        while(m<p[i].m) ans=(ans+C(n,m+1))%MOD,++m;
        ans=(ans+MOD)%MOD;ANS[p[i].pos]=ans;
    }
    for(register int i=1;i<=t;++i) cout<<ANS[i]<<'\n';
    return 0;
}
```

---

## 作者：User_Authorized (赞：0)

> [AtCoder 天下一プログラマーコンテスト2014 本戦 高橋君](https://atcoder.jp/contests/tenka1-2014-final/tasks/tenka1_2014_final_d)

## 题意

给定 $n, k$，求

$$\sum\limits_{i = 0}^{k}\dbinom{n}{i}$$

多测，$1 \le n, k, T \le 10^5$。

## 题解

[$\tt{cnblogs}$](https://www.cnblogs.com/User-Unauthorized/p/solution-AT_tenka1_2014_final_d.html)

可以考虑使用莫队求解，下文讲述如何移动指针。

### $n \rightarrow n + 1$

根据杨辉三角递推式 $\dbinom{n}{m} = \dbinom{n - 1}{m} + \dbinom{n - 1}{m - 1}$ 可以得出

$$\begin{aligned}
F(n + 1, m)
&= \sum\limits_{i = 0}^{m} \dbinom{n + 1}{i} \\
&= \sum\limits_{i = 0}^{m} \left(\dbinom{n}{i} + \dbinom{n}{i - 1}\right) \\
&= 2\sum\limits_{i = 0}^{m} \dbinom{n}{i} - \dbinom{n}{m} \\
&= 2 \cdot F(n, m) - \dbinom{n}{m}
\end{aligned}$$

### $m \rightarrow m + 1$

$$\begin{aligned}
F(n, m + 1)
&= \sum\limits_{i = 0}^{m + 1} \dbinom{n}{i} \\
&= \sum\limits_{i = 0}^{m} \dbinom{n}{i} + \dbinom{n}{m + 1}\\
&= F(n, m) + \dbinom{n}{m + 1}
\end{aligned}$$

这部分的复杂度为 $\mathcal{O}(n \sqrt{n})$。

总复杂度 $\mathcal{O}(n \sqrt{n})$，可以通过本题。

## Code

```cpp
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef ValueVector::iterator iterator;
typedef std::vector<iterator> IteratorVector;

constexpr valueType MOD = 1e9 + 7;

template<typename T1, typename T2, typename T3 = valueType>
void Inc(T1 &a, T2 b, const T3 &mod = MOD) {
    a = a + b;

    if (a >= mod)
        a -= mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Dec(T1 &a, T2 b, const T3 &mod = MOD) {
    a = a - b;

    if (a < 0)
        a += mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 mul(T1 a, T2 b, const T3 &mod = MOD) {
    return (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Mul(T1 &a, T2 b, const T3 &mod = MOD) {
    a = (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 pow(T1 a, T2 b, const T3 &mod = MOD) {
    T1 result = 1;

    while (b > 0) {
        if (b & 1)
            Mul(result, a, mod);

        Mul(a, a, mod);
        b = b >> 1;
    }

    return result;
}

namespace UU {
    valueType N, M;

    ValueVector Fact, InvFact, belong, ans;

    valueType C(valueType n, valueType m) {
        if (n < m)
            return 0;

        return mul(Fact[n], mul(InvFact[m], InvFact[n - m]));
    }

    struct Query {
        valueType n, m, id;

        Query(valueType n, valueType m, valueType id) : n(n), m(m), id(id) {}

        friend bool operator<(Query const &left, Query const &right) {
            if (belong[left.n] != belong[right.n])
                return belong[left.n] < belong[right.n];

            return left.m < right.m;
        }
    };

    std::vector<Query> query;

    void init(valueType n) {
        N = n;
        M = 0;

        Fact.resize(N + 1);
        InvFact.resize(N + 1);
        belong.resize(N + 1);

        valueType block = std::ceil(std::sqrt((double) N));

        for (valueType i = 1; i <= N; ++i)
            belong[i] = (i - 1) / block + 1;

        Fact[0] = 1;
        for (valueType i = 1; i <= N; ++i)
            Fact[i] = mul(Fact[i - 1], i);

        InvFact[N] = pow(Fact[N], MOD - 2);
        for (valueType i = N - 1; i >= 0; --i)
            InvFact[i] = mul(InvFact[i + 1], i + 1);
    }

    void add(valueType id, valueType n, valueType m) {
        query.emplace_back(n, m, id);
    }

    constexpr valueType Inv2 = (MOD + 1) / 2;

    void solve() {
        std::sort(query.begin(), query.end());

        M = (valueType) query.size();
        ans.resize(M);

        valueType nowN = 0, nowM = 0;
        valueType Ans = 1;

        for (auto const &iter : query) {
            while (nowM < iter.m) {
                ++nowM;

                Inc(Ans, C(nowN, nowM));
            }

            while (nowM > iter.m) {
                Dec(Ans, C(nowN, nowM));

                --nowM;
            }

            while (nowN < iter.n) {
                Mul(Ans, 2);
                Dec(Ans, C(nowN, nowM));

                ++nowN;
            }

            while (nowN > iter.n) {
                --nowN;

                Inc(Ans, C(nowN, nowM));
                Mul(Ans, Inv2);
            }

            ans[iter.id] = Ans;
        }
    }

    void output() {
        for (auto const &iter : ans)
            std::cout << iter << std::endl;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType M;

    std::cin >> M;

    UU::init(1e5);

    for (valueType i = 0; i < M; ++i) {
        valueType n, m;

        std::cin >> n >> m;

        UU::add(i, n, m);
    }

    UU::solve();

    UU::output();

    return 0;
}
```



---

## 作者：白简 (赞：0)

模拟赛出了一道复合题，后半部分就是这道。

#### 题目大意

给定 $T$ 个询问，对于每个询问，给出 $n,k$，求出
$$
\sum^{k}_{i=0}{n \choose i}
$$
答案对 $10^9+7$ 取模。

#### 思路

考虑 $n$ 和 $k$ 分别增加或减少 $1$ 的情况。

以下变换运用了帕斯卡法则：
$${n \choose k}={n - 1 \choose k}+{n - 1 \choose k - 1}$$
考虑当 $n$ 变为 $n+1$ 时，
$$
\begin{aligned}
& \ \ \ \ \  \sum^{k}_{i=0}{n+1 \choose i} \\

&= \sum^{k}_{i=0} \left( {n \choose i}+{n \choose i - 1} \right) \\

&= 2\sum^{k}_{i=0}{n \choose i} - {n \choose k}
\end{aligned}
$$
可以移项直接得到当 $n$ 变为 $n-1$ 的情况，
$$
\begin{aligned}
\sum^{k}_{i=0}{n - 1 \choose i} = \dfrac{1}{2} \left( \sum^{k}_{i=0}{n \choose i} + {n \choose k} \right)
\end{aligned}
$$
当 $k$ 变为 $k +1$ 时，
$$\sum^{k+1}_{i=0}{n \choose i}=\sum^{k}_{i=0}{n \choose i}+{n \choose k + 1}$$
当 $k$ 变为 $k-1$ 时，类似上面，
$$
\sum^{k-1}_{i=0}{n \choose i}=\sum^{k}_{i=0}{n \choose i}-{n \choose k}
$$

可以发现，上面四个转移只需要单个组合数，在预处理阶乘和逆元的条件下可以做到 $O(1)$ 求组合数，所以转移是 $O(1)$ 的。

考虑莫队进行转移，时间复杂度 $O(n \sqrt{n})$。
#### Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 100500;
const int Mod = 1e9 + 7;

int n, m;

int a[N];

template <typename Type>
void Inc(Type &x, Type y) {
    x += y;

    if (x >= Mod)
        x -= Mod;
    return;
}

template <typename Type>
void Dec(Type &x, Type y) {
    x = x - y;

    if (x < 0)
        x += Mod;
    return;
}

template <typename Type>
Type Mul(Type x, Type y) {
    return 1ll * x * y % Mod;
}

int Pow(int a, int b) {
    a = a % Mod;
    int res = 1;

    while (b) {
        if (b & 1)
            res = 1ll * res * a % Mod;
        b >>= 1;
        a = 1ll * a * a % Mod;
    }
    return res;
}

int Inv(int a) {
    return Pow(a, Mod - 2);
}

int fac[N], inv[N], Inv2 = Inv(2);

int C(int n, int m) {
    if (n < m || m < 0)
        return 0;

    return 1ll * fac[n] * inv[m] % Mod * inv[n - m] % Mod;
}

struct Option {
    int l, r, id, block;
} q[N];

int now = 1;

void Addl(int l, int r) {
    now = Mul(now, 2);
    Dec(now, C(l, r));
}

void Dell(int l, int r) {
    Inc(now, C(l - 1, r));
    now = Mul(now, Inv2);
}

void Addr(int l, int r) {
    Inc(now, C(l, r + 1));
}

void Delr(int l, int r) {
    Dec(now, C(l, r));
}

int ans[N],len;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> m;
    len = sqrt(m);

    for (int i = 1; i <= m; i++) {
        int y, k;
        cin >> y >> k;

        q[i].l = y;
        q[i].r = k;
        q[i].id = i;
        q[i].block = q[i].l / len;
    }

    int l = 0, r = 0;
    fac[0] = 1;
    for (int i = 1; i <= N - 500; i++)
        fac[i] = Mul(fac[i - 1], i);

    for (int i = 0; i <= N - 500; i++)
        inv[i] = Inv(fac[i]);

    sort(q + 1, q + m + 1,[](const Option &a, const Option &b) {
        if(a.block == b.block)
            return a.r < b.r;
        return a.block < b.block;
    });

    for (int i = 1; i <= m; i++) {
        while (l > q[i].l) {
            Dell(l, r);
            l--;
        }

        while (r < q[i].r) {
            Addr(l, r);
            r++;
        }

        while (l < q[i].l) {
            Addl(l, r);
            l++;
        }

        while (r > q[i].r) {
            Delr(l, r);
            r--;
        }

        ans[q[i].id] = now;
    }

    for (int i = 1; i <= m; i++)
        cout << ans[i] << "\n";
    return 0;
}
```

---

## 作者：diqiuyi (赞：0)

**思路**

观察到 $T,n,k \le 10^5$，然后发现 $k$ 可以轻松做到 $O(1)$ 移动，于是考虑莫队。 

考虑得到了 $[n,k]$ 的答案 $ans(n,k)$，如何 $O(1)$ 转移。

#### $[n,k+1]$

$ans(n,k+1)=ans(n,k)+C_n^{k+1}$。

#### $[n,k-1]$

$ans(n,k-1)=ans(n,k)-C_n^{k}$。

#### $[n+1,k]$

$ans(n+1,k)=\sum_{i=0}^kC_{n+1}^i$，似乎不好转移。

不过根据公式 $C_n^m=C_{n-1}^m+C_{n-1}^{m-1}$ 可知，

$ans(n+1,k)=\sum_{i=0}^kC_{n+1}^i=\sum_{i=0}^kC_n^i+\sum_{i=-1}^{k-1}C_n^i=2ans(n,k)-C_n^k$。

#### $[n-1,k]$

由 $ans(n,k)=2ans(n-1,k)-C_n^k$ 可知 $ans(n-1,k)=\dfrac{ans(n,k)-C_n^k}{2}$。

组合数可以 $O(1)$ 转移。

**CODE**
```cpp
#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;
int m,maxn,ans[100005],fac[100005],inv[100005],bl[100005],block,now=1;
struct qu{
	int n,k,id;
	bool operator <(qu x) const{
		return (bl[n]^bl[x.n])?n<x.n:k<x.k;
	}
}q[100005];
inline int Pow(int x,int y){
	int res=1;
	for(;y;y>>=1,x=1ll*x*x%mod)
		if(y&1)
			res=1ll*res*x%mod;
	return res;
}
inline int C(int n,int m){
	return 1ll*fac[n]*inv[n-m]%mod*inv[m]%mod;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>m,fac[0]=inv[0]=1;
	for(int i=1;i<=m;i++)
		cin>>q[i].n>>q[i].k,maxn=max(maxn,q[i].n),q[i].id=i;
	block=sqrt(maxn);
	for(int i=1;i<=maxn;i++)
		bl[i]=(i-1)/block+1,fac[i]=1ll*fac[i-1]*i%mod;
	inv[maxn]=Pow(fac[maxn],mod-2);
	for(int i=maxn-1;i;i--)
		inv[i]=1ll*inv[i+1]*(i+1)%mod;
	sort(q+1,q+m+1);
	for(int i=1,nt=0,kt=0;i<=m;i++){
		while(kt>q[i].k) now=(now-C(nt,kt)+mod)%mod,kt--;
		while(nt<q[i].n) nt++,now=((now<<1)%mod-C(nt-1,kt)+mod)%mod;
		while(nt>q[i].n) nt--,now=1ll*(now+C(nt,kt))%mod*inv[2]%mod;
		while(kt<q[i].k) now=(now+C(nt,++kt))%mod;
		ans[q[i].id]=now;
	}
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```

---

