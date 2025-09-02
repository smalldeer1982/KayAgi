# Lucky Tickets

## 题目描述

在 Berland，所有公交车票都有编号。一个编号由 $n$ 位数字组成（$n$ 是偶数）。只有 $k$ 个十进制数字 $d_1, d_2, \dots, d_k$ 可以用来组成车票编号。如果 $0$ 在这些数字中，则编号可以有前导零。例如，如果 $n = 4$ 且只能使用数字 $0$ 和 $4$，那么 $0000$、$4004$、$4440$ 是合法的车票编号，而 $0002$、$00$、$44443$ 不是。

如果一张车票的前 $n/2$ 位数字之和等于后 $n/2$ 位数字之和，则称这张车票是幸运的。

请计算 Berland 中不同幸运车票的数量。由于答案可能很大，请输出对 $998244353$ 取模后的结果。

## 说明/提示

在第一个样例中，共有 $6$ 张幸运车票：$1111$、$1818$、$1881$、$8118$、$8181$ 和 $8888$。

在第二个样例中，只有一种车票编号，由 $20$ 个数字 $6$ 组成。这张车票是幸运的，所以答案是 $1$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 2
1 8
```

### 输出

```
6
```

## 样例 #2

### 输入

```
20 1
6
```

### 输出

```
1
```

## 样例 #3

### 输入

```
10 5
6 1 4 0 3
```

### 输出

```
569725
```

## 样例 #4

### 输入

```
1000 7
5 4 0 1 8 3 2
```

### 输出

```
460571165
```

# 题解

## 作者：NaCly_Fish (赞：13)

注：下文中的 $k$ 都表示可用的数中最大值。

看了一下提交记录，似乎都写的 $\Theta(nk \log nk)$ 的做法，，  
来写一发不用 fft 的 $\Theta(nk^2)$ 做法，此题中 $k$ 较小，因此跑的飞快。
****
题目中要求两边相等的方案数，而两边之间互不影响；所以只用算出一边的和分别为 $0,1,2,\dots$ 的方案数，平方和即是答案。

设 $S$ 为可用的数集合，则每个格子填数方案的生成函数为
$$f(x)=\sum_{t\in S}x^t$$
显然 $f(x)^{n/2}$ 就是答案的生成函数。  

$f(x)$ 最多只有 $9$ 次，考虑如何快速计算它的幂：  
（不过相信很多同学都会，可以不看）
$$g(x)=f(x)^t$$
$$g'(x)f(x)=tf'(x)g(x)$$
提取一下系数就能发现，计算一项的复杂度只和 $f(x)$ 有关，暴力按式子算就是 $\Theta(k)$ 的，总时间复杂度就是 $\Theta(nk^2)$。

这个方法常数小，还好写，~~不知高到哪里去了~~。
```cpp
#pragma GCC optimize (2)
#pragma GCC optimize ("unroll-loops")
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define N 1000003
#define p 998244353
#define ll long long
#define reg register
using namespace std;

int n,k;
int f[N],g[N],inv[N];
ll ans = 1;

int main(){
    int x,siz = 0,t = 0;
    scanf("%d%d",&n,&k);
    if(k==1){
        putchar('1');
        return 0;
    }
    n >>= 1;
    for(reg int i=1;i<=k;++i){
        scanf("%d",&x);
        f[x] = 1,t = max(t,x);
    }
    for(reg int i=0;i<=t&&f[i]==0;++i) siz = max(siz,i+1);
    if(siz>0){
        for(reg int i=0;i<=t;++i) f[i] = f[i+siz];
        t -= siz;
    }
    inv[1] = g[0] = 1;
    int tt = t*n;
    for(reg int i=2;i<=tt;++i) inv[i] = (ll)(p-p/i)*inv[p%i]%p;
    for(reg int i=0;i!=tt;++i){
        int tmp = 0;
        for(reg int j=0;j<=min(i,t-1);++j) tmp = (tmp+(ll)(j+1)*f[j+1]%p*g[i-j])%p;
        tmp = (ll)tmp*n%p;
        for(reg int j=max(0,i-t);j!=i;++j) tmp = (tmp-(ll)(j+1)*g[j+1]*f[i-j])%p;
        g[i+1] = (ll)tmp*inv[i+1]%p;
        ans += (ll)g[i+1]*g[i+1]%p;
    }
    printf("%lld",ans%p);
	return 0;	
}
```

---

## 作者：Dilute (赞：5)

其实我很想吐槽这题

我比赛的时候疯狂$\color{red}\text{WA on test 16}$

然后死活找不出来哪儿错了

我觉得我数组开小了

于是我开到$MLE$都没有过掉

最后一看

被一个`n = 2`的点卡掉了……

才出4题，罚时爆炸，上黄失败，掉分哭唧唧

------

首先我们看到题，我们可以想到一个朴素的$DP$方法：

我们用$f[i][j]$来表示在前$i$个里面取到和为$j$的方案数

然后我们可以列出$DP$方程，即$f[i][j] = \displaystyle\sum_{u = 1}^{k} f[i - 1][j - d[u]]$

那么显然，答案就是$\displaystyle \sum_{i = 1}^{n * 5}f[\frac{n}{2}][i] $

~~然而这个朴素的DP是$O(n^2)$的~~

我们考虑如何优化这个$DP$方程

我们想想看卷积的公式

$c[i] = \displaystyle \sum_{j = 0}^{i} a[j] * b[i - j]$

我们再试着改写一下原来的$DP$方程

我们令$g[u]$为$1$当且仅当$u \in d$，否则$g[u] = 0$

那么式子就可以改写成

$f[i][j] = \displaystyle\sum_{u = 1}^{j} f[i - 1][j - u] * g[u]$

我一看，这下子$f[i]$不就是$f[i - 1]$和$g$这两个多项式的卷积了吗

我们再考虑$f[0]$，显然$f[0] = \{1, 0, 0, 0... \}$

然后我们发现任何多项式乘上$f[0]$都等于它本身

于是我们发现最终的答案就是$g$这个多项式的$\frac{n}{2}$次幂

然后我们就可以愉快的用多项式快速幂解决这个问题了

注意多项式的长度要动态开，否则会T飞～

这里我用的是$NTT$，毕竟模数是$998244353$，取模比起$FFT$方便不少...

```cpp
#include<bits/stdc++.h>
// o^r^z w^x^w

#define ll long long
#define INF 2147483647
#define mod 998244353

int pi = acos(-1);
const int G = 3;

inline int inp(){
    char c = getchar();
    while(c < '0' || c > '9')
        c = getchar();
    int sum = 0;
    while(c >= '0' && c <= '9'){
        sum = sum * 10 + c - '0';
        c = getchar();
    }
    return sum;
}

ll powmod(ll a, int b){
    ll sum = 1;
    while(b){
        if(b & 1){
            sum *= a;
            sum %= mod;
        }
        a *= a;
        a %= mod;
        b >>= 1;
    }
    return sum;
}

int g[8000010], num[8000010];
int len, r[8000010];
int a[8000010], b[8000010], c[8000010];
int wn[8000010];
int invlim;
#define add(a, b) ((a) + (b) >= mod ? (a) + (b) - mod : (a) + (b))
#define mine(a, b) ((a) < (b) ? (a) - (b) + mod : (a) - (b))
#define mul(a, b) ((ll)(a) * (ll)(b) % mod)

inline void ntt(int *a, int f){
	for(int i = 0; i < len; i++)
        if(i < r[i])
            std::swap(a[i], a[r[i]]);
	for(int i = 1; i < len; i <<= 1){
		wn[0] = 1;
        wn[1] = powmod(G, (mod - 1) / (i << 1));
		for(int j = 2; j < i; j++)
            wn[j] = mul(wn[j - 1], wn[1]);
		for(int j = 0; j < len; j += i << 1){
			int *L = a + j;
            int *R = L + i;
		    for(int k = 0; k < i; k++){
				const int t = mul(wn[k], R[k]);
				R[k] = mine(L[k], t);
                L[k] = add(L[k], t);
			}
		}
	}
	if(f == -1){
		std::reverse(a + 1, a + len);
		for(int i = 0; i < len; i++)
            a[i] = mul(a[i], invlim);
	}
}

void init(int n){
    len = 1;
    int lg = 0;
    while(len <= n)
        len <<= 1, lg++;
    for(int i = 0; i < len; i++)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) << (lg - 1));
    invlim = powmod(len, mod - 2);
}

int main(){
    int n = inp() >> 1;
    int k = inp();
    memset(g, 0, sizeof(g));
    for(int i = 1; i <= k; i++){
        int x = inp();
        g[x] = 1;
    }
    int pownum = n - 1;
    memcpy(num, g, sizeof(g));
    init(20);
    while(pownum){
        // printf("%d\n", pownum);
        if(pownum & 1){
            int maxw = 0;
            for(int i = 1; i <= 5000000; i++)
                if(g[i] > 0)
                    maxw = i;
            init(maxw << 2);
            ntt(g, 1);
            ntt(num, 1);
            for(int i = 0; i <= len; i++)
                num[i] = mul(num[i], g[i]);
            ntt(g, -1);
            ntt(num, -1);
        }
        int maxw = 0;
        for(int i = 1; i <= 5000000; i++)
            if(g[i] > 0)
                maxw = i;
        init(maxw << 2);
        ntt(g, 1);
        for(int i = 0; i <= len; i++)
            g[i] = mul(g[i], g[i]);
        ntt(g, -1);
        pownum >>= 1;
    }
    int ans = 0;
    for(int i = 0; i <= len; i++)
        ans = add(ans, mul(num[i], num[i]));
    printf("%d\n", ans);
}
```

---

## 作者：huayucaiji (赞：4)

## 前言

挺简单的一道题，NTT 入门。

对于之后理解生成函数应该有很大帮助。

## 解法

先想想这个计数怎么计。

设选 $\frac{n}{2}$ 个数和为 $s$ 的方案数为 $f_s$。那么最后我们求得答案就是：

$$\sum\limits_{s=0}^\frac{9n}{2} {f_s}^2$$

~~这个读者自证不难~~

那么问题来了，怎样快速求出 $f_s$？我们可以想到构造多项式来解决。

比如对于样例一：

```plain
4 2
1 8
```

我们可以构造一个多项式 $g(x)=x+x^8$。也就是，把每个可以选用的数字，作为次数的那一项前的系数设为 $1$，其余为 $0$。

这样有什么好处呢？

再来看这个样例，我们求的是选择 $2$ 个数和为 $s$ 的方案数。那么我们就将 $g(x)$ 平方，得到 $x^2+2x^9+x^{16}$，这样就代表 $f_2=1,f_9=2,f_{16}=1$。

这其实是用到了多项式乘法次数相加，系数相乘的性质。这个相加也就是我们的数字相加。因此这样计算是可以的。

所以最后归纳一下，我们要做以下步骤：

1. 构造 $g(x)$。
2. 计算 $h(x)=g(x)^{\frac{n}{2}}$。
3. 根据公式求出 $ans$。

## 代码

~~不会有人想用 FFT 吧，不会吧，不会吧。~~

~~小丑竟是我自己。~~

```cpp
//Don't act like a loser.
//This code is written by huayucaiji
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int MAXN=3e6+10;
const int G=3;
const int MOD=998244353;

int n,k;
int f[MAXN],r[MAXN];


int qpow(int x,int y) {
	int ret=1;
	while(y) {
		if(y&1) {
			ret=x*ret%MOD;
		}
		y>>=1;
		x=x*x%MOD;
	}
	return ret;
}

void NTT(int A[],int d,int inv) {
	for(int i=0;i<d;i++) {
		if(i<r[i]) {
			swap(A[i],A[r[i]]);
		}
	}
	
	for(int len=1;len<d;len<<=1) {
		int gn=qpow(G,(MOD-1)/(len*2));
		for(int i=0;i<d;i+=len<<1) {
			int g=1;
			for(int k=0;k<len;k++,g=g*gn%MOD) {
				int x=A[i+k];
				int y=g*A[i+k+len]%MOD;
				A[i+k]=(x+y)%MOD;
				A[i+k+len]=(x-y+MOD)%MOD;
			}
		}
	}
	
	if(inv==-1) {
		reverse(A+1,A+d);
		int g=qpow(d,MOD-2);
		for(int i=0;i<d;i++) {
			A[i]=A[i]*g%MOD;
		}
	}
}

signed main() {
	n=read();k=read();
	while(k--) {
		f[read()]=1;
	}
	
	int d=1,bit=0;
	while(d<=n/2*9) {
		d<<=1;
		bit++;
	}
	for(int i=0;i<d;i++) {
		r[i]=(r[i>>1]>>1)|((i&1)<<(bit-1));
	}
	
	NTT(f,d,1);
	for(int i=0;i<d;i++) {
		f[i]=qpow(f[i],n/2);
	}
	NTT(f,d,-1);
	
	int ans=0;
	for(int i=0;i<d;i++) {
		ans=(ans+f[i]*f[i]%MOD)%MOD;
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：wcyQwQ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1096G)

[可能更好的阅读体验](https://chenyu-w.github.io./2023/03/05/CF1096G%20Lucky%20Tickets/)

简单的多项式题。

## 分析

首先设能填的数的集合为 $S$，设 $F(x) = \sum_{i \in S}x^i$，然后不难发现选 $p$ 个数，和为 $q$ 的方案数即为 $[x^q]F^p(x)$，所以我们枚举那个相等的和，最终的答案即为 $\sum_i \left([x^i]F^\frac{n}{2}(x)\right)^2$，直接 $\text{NTT}$ 即可。

## 代码

```c++
#include <bits/stdc++.h>
#define L(i, j, k) for (int i = (j); i <= (k); i++)
#define R(i, j, k) for (int i = (j); i >= (k); i--)
#define G(i, u) for (int i = h[(u)]; ~i; i = ne[i])
#define ll long long
#define ld long double
#define ull unsigned long long

using namespace std;
const int N = 2e7 + 10, mod = 998244353, G = 3;
int a[N], rev[N];

inline int read() {
    int x = 0, y = 1; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') y = -1; c = getchar();}
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * y;
}

inline int mul(int x, int y) {return 1ll * x * y % mod;}

inline int qpow(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = mul(res, a);
		a = mul(a, a);
		b >>= 1;
	}
	return res;
}

inline void ntt(int a[], int n, int flg) {
	L(i, 0, n - 1) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int mid = 1; mid < n; mid <<= 1) {
		int W = qpow(G, (mod - 1) / (mid << 1));
		if (flg == -1) W = qpow(W, mod - 2);
		for (int i = 0; i < n; i += (mid << 1)) {
			int w = 1;
			L(j, i, i + mid - 1) {
				int x = a[j], y = mul(w, a[j + mid]);
				a[j] = (x + y) % mod, a[j + mid] = (x - y + mod) % mod;
				w = mul(w, W);
			}
		}
	}
}

int main() {
	int n = read() / 2, m = read();
	while (m--) a[read()] = 1;
	int k = 1, l = 0;
	while (k <= 10 * n) k <<= 1, l++;
	L(i, 0, k - 1) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (l - 1));
	ntt(a, k, 1);
	L(i, 0, k - 1) a[i] = qpow(a[i], n);
	ntt(a, k, -1);
	int invK = qpow(k, mod - 2);
	L(i, 0, 10 * n) a[i] = mul(a[i], invK);
	int res = 0;
	L(i, 0, 10 * n) res = (res + mul(a[i], a[i])) % mod;
	printf("%d\n", res);
    return 0;
}
```



 

---

## 作者：ghj1222 (赞：0)

设$a_i$表示数字$i$是否被钦定

我们可以构造一个多项式

$$f(i)=\sum_{0\le i \le 9}a_ix^i$$

这个多项式没啥有趣的，不过我们给他进行$n/2$次方后，你会发现，第$i$项的系数就是拼成$i$的方案数

根据生成函数那套理论

我们只需要输出

$$\sum_{i\ge 0}\left([x^i]\left(\sum_{0\le i \le 9}a_ix^i\right)^{\frac n 2}\right)^2$$

根据策爷论文，我们用$[x^n]f(x)$表示$f(x)$的$n$次项系数

用NTT+多项式快速幂即可A

温馨提示：倍增快速幂能过 时间复杂度大概是$O(n\log^2n)$

然后是我的常数非常大的代码= =

```cpp
#include <bits/stdc++.h>
using namespace std;

const int p = 998244353;

int qpow(int x, int y)
{
	int res = 1;
	while (y > 0)
	{
		if (y & 1)
			res = res * (long long)x % p;
		x = x * (long long)x % p;
		y >>= 1;
	}
	return res;
}

int r[5000010];

void ntt(vector<int> &a, int len, int flag)
{
	for (int i = 0; i < len; i++)
		if (r[i] < i)
			swap(a[i], a[r[i]]);
	for (int i = 1; i < len; i <<= 1)
	{
		int g1 = qpow(3, (p - 1) / (i * 2));
		for (int j = 0; j < len; j += i << 1)
		{
			for (int g = 1, k = 0; k < i; k++, g = g * (long long)g1 % p)
			{
				int t = g * (long long)a[j + k + i] % p;
				a[j + k + i] = ((a[j + k] - t) % p + p) % p;
				a[j + k] = (a[j + k] + t) % p;
			}
		}
	}
	if (flag == -1)
	{
		reverse(a.begin() + 1, a.end());
		int inv = qpow(len, p - 2);
		for (int i = 0; i < len; i++)
			a[i] = a[i] * (long long)inv % p;
	}
}

vector<int> operator*(vector<int> a, vector<int> b)
{
	int lena = a.size(), lenb = b.size();
	int len = 1;
	while (len <= lena + lenb)
		len <<= 1;
	for (int i = 0; i < len; i++)
		r[i] = (r[i >> 1] >> 1) | ((len >> 1) * (i & 1));
	a.resize(len);
	b.resize(len);
	ntt(a, len, 1);
	ntt(b, len, 1);
	for (int i = 0; i < len; i++)
		a[i] = a[i] * (long long)b[i] % p;
	ntt(a, len, -1);
	a.resize(lena + lenb - 1);
	return a;
}

vector<int> poly_qpow(vector<int> a, int b)
{
	vector<int> res;
	res.resize(1);
	res[0] = 1;
	while (b > 0)
	{
		if (b & 1)
			res = res * a;
		a = a * a;
		b >>= 1;
	}
	return res;
}

int main()
{
	int n, k;
	vector<int> init;
	init.resize(10);
	cin >> n >> k;
	for (int i = 0; i < 10; i++)
		init[i] = 0;
	for (int x, i = 1; i <= k; i++)
		cin >> x, init[x] = 1;
	init = poly_qpow(init, n / 2);
	int ans = 0;
	for (int i : init)
		ans = (ans + i * (long long)i % p) % p;
	cout << ans << endl;
	return 0;
}
```

---

## 作者：LJC00118 (赞：0)

看到背包问题就会想到卷积，因为背包的转移和卷积的形式相同

对于最开始的 $ k $ 个数构造生成函数，计算 $ n / 2 $ 次幂，每一位的平方加起来就是答案啦

```cpp
#pragma GCC target("avx")
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define Fast_cin ios::sync_with_stdio(false), cin.tie();
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> " << endl;
using namespace std;

typedef unsigned long long ull;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') fu = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

const int P = 998244353;

inline int add(int x, int y) {
    x += y;
    if(x >= P) x -= P;
    return x;
}

inline int sub(int x, int y) {
    x -= y;
    if(x < 0) x += P;
    return x;
}

inline int mul(int x, int y) {
    return (ll)x * y % P;
}

inline int fpow(int x, int y) {
    int ans = 1;
    while(y) {
        if(y & 1) ans = mul(ans, x);
        y >>= 1; x = mul(x, x);
    }
    return ans;
}

namespace ntt {
    int base = 1, root = -1, maxbase = -1;
    vector <int> roots = {0, 1}, rev = {0, 1};
    
    void init() {
        int tmp = P - 1; maxbase = 0;
        while(!(tmp & 1)) {
            tmp >>= 1;
            maxbase++;
        }
        root = 2;
        while(1) {
            if(fpow(root, 1 << maxbase) == 1 && fpow(root, 1 << (maxbase - 1)) != 1) break;
            root++;
        }
    }
    
    void ensure_base(int nbase) {
        if(maxbase == -1) init();
        if(nbase <= base) return;
        assert(nbase <= maxbase);
        rev.resize(1 << nbase);
        for(register int i = 1; i < (1 << nbase); i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (nbase - 1));
        roots.resize(1 << nbase);
        while(base < nbase) {
            int z = fpow(root, 1 << (maxbase - base - 1));
            for(register int i = (1 << (base - 1)); i < (1 << base); i++) {
                roots[i << 1] = roots[i];
                roots[i << 1 | 1] = mul(roots[i], z);
            }
            base++;
        } 
    }
    
    void dft(vector <int> &a) {
        int n = a.size(), zeros = __builtin_ctz(n);
        ensure_base(zeros);
        int shift = base - zeros;
        for(register int i = 0; i < n; i++) if(i < (rev[i] >> shift)) swap(a[i], a[rev[i] >> shift]);
        for(register int mid = 1; mid < n; mid <<= 1) {
            for(register int i = 0; i < n; i += (mid << 1)) {
                for(register int j = 0; j < mid; j++) {
                    int x = a[i + j], y = mul(a[i + j + mid], roots[mid + j]);
                    a[i + j] = add(x, y); a[i + j + mid] = sub(x, y);
                }
            }
        }
    }
    
    vector <int> pmul(vector <int> a, vector <int> b, bool is_sqr = false) {
        int need = a.size() + b.size() - 1, nbase = 0;
        while((1 << nbase) < need) nbase++;
        ensure_base(nbase); int size = 1 << nbase;
        a.resize(size); dft(a); if(!is_sqr) b.resize(size), dft(b); else b = a;
        int inv = fpow(size, P - 2);
        for(register int i = 0; i < size; i++) a[i] = mul(a[i], mul(b[i], inv));
        reverse(a.begin() + 1, a.end()); dft(a); a.resize(need); return a;
    }
    
    vector <int> psqr(vector <int> a) { return pmul(a, a, 1); }
    
    vector <int> inv(vector <int> a, int size) {
    	if(size == 1) return vector <int> { fpow(a[0], P - 2) };
    	vector <int> b = inv(a, size >> 1); a = pmul(a, psqr(b)); b.resize(size);
    	for(register int i = 0; i < size; i++) b[i] = sub(add(b[i], b[i]), a[i]);
    	return b;
    }
    
    vector <int> pinv(vector <int> a) {
    	int nbase = 0; while((1 << nbase) < a.size()) nbase++;
    	return inv(a, 1 << nbase);
    }
}
using ntt::pmul;
using ntt::psqr;

vector <int> wxw, ans;
int n, k, sum;

int main() {
	read(n); read(k); wxw.resize(10); 
	for(register int i = 1; i <= k; i++) {
		int t; read(t); wxw[t] = 1;
	}
	n >>= 1; ans = wxw; n--;
	while(n) {
		if(n & 1) ans = pmul(ans, wxw);
		n >>= 1; wxw = psqr(wxw);
	}
	for(register int i = 0; i < ans.size(); i++) sum = add(sum, mul(ans[i], ans[i]));
	cout << sum << endl;
	return 0;
}
```

---

