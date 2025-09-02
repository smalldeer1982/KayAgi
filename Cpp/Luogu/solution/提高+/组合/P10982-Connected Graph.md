# Connected Graph

## 题目背景

本题是 P4841 [集训队作业2013] 城市规划 的弱化版，去除了原题中的多项式部分。

## 题目描述

求 $n$ 个结点的有标号无向连通图个数。

## 说明/提示

数据保证 $1\leq n \leq 1000$。

## 样例 #1

### 输入

```
3```

### 输出

```
4```

## 样例 #2

### 输入

```
4```

### 输出

```
38```

# 题解

## 作者：Starrykiller (赞：7)

最不毒瘤的一集。

考虑容斥：用 $n$ 个点的有标号无向图数量减去 $n$ 个点的有标号**不连通**无向图数量。

前者是我们熟知的：$f(n)=2^{n(n-1)/2}$。也就是每条边都可以有或者没有。

注意到不连通的无向图中，$1$ 号节点一定在某一个连通块中，我们枚举这个连通块就可以避免算重/算漏。


那么我们设 $g(n)$ 为 $n$ 个点的有标号**连通**无向图数量，得到了

$$g(n)=f(n)-\sum_{i=1}^{n-1}{n-1\choose i-1}g(i)f(n-i)$$

也就是：选择 $(i-1)$ 个节点与 $1$ 组成大小为 $i$ 的连通块；剩下的部分随意。

时间复杂度 $\Theta(n^2)$。值得注意的是，这本质上就是对 $f(n)$ 做「连通化递推」——也就是对 $[z^n]F(z)=f(n)$ 取 $\ln$。这就是 $\Theta(n^2)$ 做多项式 $\ln$ 的方法。同理，我们还有「逆连通化递推」——也就是取 $\exp$。更多内容，可参阅多项式与生成函数相关资料。

小圆抱抱 www

---

## 作者：wangbinfeng (赞：4)

[![](https://img.shields.io/badge/题目-P10982_Connected_Graph-green)
![](https://img.shields.io/badge/难度-提高+/省选−-blue)
![](https://img.shields.io/badge/考点-计数类_DP-red)
![](https://img.shields.io/badge/题型-传统题-yellow)](https://www.luogu.com.cn/problem/P10982)
[![](https://img.shields.io/badge/作者-wangbinfeng(387009)-purple)](https://www.luogu.com.cn/user/387009)

---
考虑到，**$n$ 个节点的连通图个数**等于 **$n$ 个节点的图的个数**减去 **$n$ 个节点不连通的图的个数**。

对于 $n$ 个点的图可以发现其最多有 $\frac {n\times(n-1)}{2}$ 条边，每条边可以选或者不选，共计 $2^{\frac {n\times(n-1)}{2}}$ 种方案。

对于 $n$ 个节点不连通的图，发现可以由**①一个连通的 _包含一个固定节点_ 的有 $k$ 个节点的子图**和**②一个与之不连通的任意的子图**构成。①的值可以用之前的数据（即 $ans_k$），而②因为剩下共计 $n-k$ 个节点，$\frac{(n-k)\times(n-k-1)}{2}$ 条边，可知能贡献 $2^{\frac{(n-k)\times(n-k-1)}{2}}$ 种方案。注意到①选择 $k$ 个节点的方案有 $C_{n-1}^{k-1}$ 种，故最终转移方程为 $\displaystyle ans_n=2^{\frac {n\times(n-1)}{2}}-\sum_{k=1}^{n-1}\left(C_{n-1}^{k-1}\times ans_k\times 2^{\frac{(n-k)\times(n-k-1)}{2}}\right)$。

按照转移方程实现即可，时间复杂度 $\Theta(n^2)$，不要忘记取模，且模数需要用 `long long` 存储。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1000 + 9, mod = 1004535809LL;
int n, pw[maxn * maxn], c[maxn][maxn], f[maxn];
signed main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cin >> n, pw[0] = 1;
	for (int i = 1; i <= n * n; i++)
		pw[i] = pw[i - 1] * 2 % mod; // O(n) 预处理出 2 的若干次方
	for (int i = 0; i <= n; i++)	 // 预处理出组合数
		for (int j = 0; j <= i; j++)
			if (!j)
				c[i][j] = 1;
			else
				c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
	for (int i = 1; i <= n; i++)
	{
		f[i] = pw[i * (i - 1) / 2];
		for (int j = 1; j < i; j++)
			f[i] = (f[i] - f[j] * c[i - 1][j - 1] % mod * pw[(i - j) * (i - j - 1) / 2] % mod + mod) % mod;
	}
	cout << f[n];
}
```

---
[![](https://jrenc.azurewebsites.net/api/signature?code=zHZRCCItO-yB8t7d2KyitELFDwADnXIotkeeIQL3juyNAzFucnyrWA%3D%3D&name=thanks%20for%20reading%20%20%20%20%20%20%20%20by%20%40wangbinfeng(387009)&animate=true&speed=0.7&color=purple)](https://www.luogu.com.cn/user/387009)
$$\color{grey}{\tiny{\texttt{发现上面的签名是动图了吗？}}}$$

---

## 作者：Mirasycle (赞：2)

图计数入门题。

记 $e_i$ 表示 $i$ 个的完全图的边数 ${i\choose 2}$，设 $f_i$ 表示 $i$ 个点的标号联通图。

考虑使用容斥，先 $f_i\gets 2^{e_i}$，然后再扣除不合法的方案数。不合法的方案必定是需要不联通的，不联通图可以被划分为至少两个内部联通点集（集合之间不联通），如果直接枚举的话不好确定对象，不妨把只枚举其中一个内部联通且和外部不联通的集合，这个集合确定之后，我们可以发现外面是可以任意选择的，不管外面怎么选，都能被划分为至少两个之间不联通的点集。

但是我们钦定的这个联通的点集，会在一个拥有多个联通块的图中被计算多次（每个联通块可以作为被钦定联通的集合），发现这张图中 $1$ 号点所在联通块唯一，于是我们就强行要求包含 $1$ 号点所有在联通块这样子就唯一了。

我们直接枚举被钦定联通的集合大小，然后组合数是分配系数，由于 $1$ 号点已经被要求在集合中了，所有只需要从剩下的 $i-1$ 个点中选择 $j-1$ 个就行了。最后 $2^{e_{i-j}}$ 代表剩余部分随便选的方案数。

$$f_i=2^{e_i}-\sum\limits_{j=1}^{i-1}f_j\times {i-1\choose j-1}\times 2^{e_{i-j}}$$

时间复杂度 $O(n^2)$。


```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
const int maxn=1e3+10;
const int mod=1004535809;
void add(int &x,int y){ x=x+y>=mod?x+y-mod:x+y; }
void sub(int &x,int y){ x=x<y?x-y+mod:x-y; }
void cmax(int &x,int y){ x=x>y?x:y; }
void cmin(int &x,int y){ x=x<y?x:y; }
int f[maxn],pw[maxn*maxn],C[maxn][maxn],n;
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n; C[0][0]=1; pw[0]=1;
	for(int i=1;i<=n*n;i++) pw[i]=2ll*pw[i-1]%mod;
	for(int i=1;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
	f[1]=1;
	for(int i=2;i<=n;i++){
		f[i]=pw[C[i][2]];
		for(int j=1;j<i;j++)
			sub(f[i],1ll*f[j]*C[i-1][j-1]%mod*pw[C[i-j][2]]%mod);
	}
	cout<<f[n];
	return 0;
}
```

---

## 作者：xiezheyuan (赞：2)

## 简要题意

求 $n$ 个点有标号无向连通图数量，答案对 $1004535809$ 取模。

- 本题：$1\leq n\leq 10^3$
- 加强版 P4841 \[集训队作业2013\] 城市规划：$1\leq n\leq 1.3\times 10^5$

## 思路

### 本题

首先考虑 dp，设 $f(i)$ 表示 $i$ 个点的有标号无向连通图数量，然后考虑转移。

设 $g(i)$ 表示 $i$ 个点的有标号无向图数量，不难得到：

$$
g(i)=2^{\binom{n}{i}}
$$

然后考虑如何求出 $f(i)$，正难则反，可以改为求出 $i$ 个点的有标号无向不连通图数量，不妨枚举 $1$ 所在的连通块大小 $j$。

那么 $j$ 所在的连通块构成了一个连通图 $f(j)$，其余部分构成了一个任意图 $g(i-j)$，然后再乘上 $\binom{i-1}{j-1}$ 表示选出的和 $1$ 在一个连通块的点。综上所述，转移为：

$$
f(i)=g(i)-\sum_{j=1}^{i-1}\binom{i-1}{j-1}f(j)g(i-j)
$$

时间复杂度 $O(n^2)$。

### 加强版：P4841 \[集训队作业2013\] 城市规划

前置知识：多项式求逆，多项式乘法。另外使用多项式对数函数或分治 FFT 也可以完成本题。

考虑如何优化到 $O(n\log n)$。

将式子变形得：

$$
g(i)=\sum_{j=1}^{i}\binom{i-1}{j-1}f(j)g(i-j)
$$

将二项式系数拆开得：

$$
g(i)=\sum_{j=1}^{i}\frac{f(j)}{(j-1)!}\cdot \frac{g(i-j)}{(i-j)!}\cdot (i-1)!
$$

将 $(i-1)!$ 移动到左边：

$$
\frac{g(i)}{(i-1)!}=\sum_{j=1}^{i}\frac{f(j)}{(j-1)!}\cdot \frac{g(i-j)}{(i-j)!}
$$

右边的和式是卷积的形式，可以考虑构造幂级数：

$$
\begin{aligned}
&\mathbf{F}=\sum_{j=1}^{+\infty}\frac{f(j)}{(j-1)!}x^j\\
&\mathbf{G}=\sum_{j=0}^{+\infty} \frac{g(j)}{j!}x^j\\
&\mathbf{G'}=\sum_{j=1}^{+\infty} \frac{g(j)}{(j-1)!}x^j
\end{aligned}
$$

其实这些都是 EGF，不过在这里用处不大就是了。$\mathbf{G'}$ 很像 $\mathbf{G}$ 的导数形式，这不是巧合（参考多项式对数函数的组合意义）。

则有 $\mathbf{G'}=\mathbf{F}\cdot \mathbf{G}$，进而有 $\mathbf{F}=\mathbf{G}^{-1}\cdot \mathbf{G'}$，对 $\mathbf{G}$ 求逆，然后与 $\mathbf{G'}$ 卷积即可。

答案就是 $(n-1)!\cdot [x^n]\mathbf{F}$。

时间复杂度 $O(n\log n)$。

## 代码

### 本题

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;

const int N = 1005;
const int mod = 1004535809, inv4 = 753401857;
int n, f[N], g[N], fact[N], inv[N];

int Add(int x, int y){ return (x + y >= mod) ? (x + y - mod) : (x + y); }
int Sub(int x, int y){ return (x - y < 0) ? (x - y + mod) : (x - y); }
int Mul(int x, int y){ return 1ll * x * y % mod; }
int binom(int x, int y){ return Mul(fact[x], Mul(inv[y], inv[x - y])); }
int fastpow(int x, int y){
    int res = 1;
    while(y){
        if(y & 1) res = Mul(res, x);
        x = Mul(x, x);
        y >>= 1;
    }
    return res;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for(int i=1;i<=n;i++) g[i] = fastpow(2, (1ll * i * (i - 1) / 2) % (mod - 1));
    fact[0] = inv[0] = inv[1] = fact[1] = 1;
    for(int i=2;i<=n;i++){
        fact[i] = Mul(fact[i - 1], i);
        inv[i] = Mul(inv[mod % i], mod - mod / i);
    }
    for(int i=2;i<=n;i++) inv[i] = Mul(inv[i - 1], inv[i]);
    f[1] = 1;
    for(int i=2;i<=n;i++){
        f[i] = g[i];
        for(int j=1;j<i;j++){
            int tmp = Mul(binom(i - 1, j - 1), Mul(f[j], g[i - j]));
            f[i] = Sub(f[i], tmp);
        }
    }
    cout << f[n] << '\n';
    return 0;
}

// Written by xiezheyuan
```

### 加强版：P4841 \[集训队作业2013\] 城市规划

多项式模板过长未展示。

```cpp
int n, fact[N], factinv[N], f[N], g1[N], g1inv[N], pw[N];

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    fact[0] = factinv[1] = fact[1] = factinv[0] = 1;
    for(int i=2;i<=n;i++){
        fact[i] = Mul(fact[i-1], i);
        factinv[i] = Mul(factinv[i-1], fastpow(i, mod-2));
    }
    pw[0] = 1;
    for(int i=1;i<=n;i++) pw[i] = fastpow(2, (1ll * i * (i - 1) / 2) % (mod-1));
    for(int i=0;i<=n;i++) g1[i] = Mul(pw[i], factinv[i]);
    inv(g1, g1inv, n);
    for(int i=1;i<=n;i++) f[i] = Mul(pw[i], factinv[i - 1]);
    mul(f, g1inv, n, n);
    cout << Mul(f[n], fact[n - 1]);
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：LostKeyToReach (赞：2)

组合数学+容斥好题。

我们设 $f_i$ 为 $i$ 个节点构成的无向连通图的方案数。

首先我们知道，$n$ 个节点的无向图总数为 $2^{\frac{n(n-1)}{2}}$ 个（最多 $\frac{n(n-1)}{2}$ 条边，可选可不选）。我们再根据容斥原理，可得有无向连通图个数等于无向图个数减去无向不连通图个数。那无向不连通图怎么求呢？我们可以发现，这种图构成了至少 $2$ 个连通块，我们不妨枚举标号为 $1$ 的点所在的连通块大小 $x$，那么我们要选 $x - 1$ 个点和 $1$ 构成大小为 $x$ 的连通块，这里有 $\binom{n - 1}{x - 1}$ 种选法。剩下的 $n - (x - 1) - 1 = n - x$ 个节点自己构成一张无向图，方案数为 $2^{\frac{(n-x)(n-x-1)}{2}}$ 种，但因为还要乘上 $x$ 个节点构成的无向连通图的方案数（前面只选了点），那么答案为 $f_x \times \binom{n - 1}{x - 1} \times 2^{\frac{(n-x)(n-x-1)}{2}}$。

这样的话，我们很容易得到状态转移方程：

$$
f_i = 2^{\frac{i(i-1)}{2}}-\sum_{j=1}^{i-1}f_j \times \binom{i - 1}{j - 1} \times 2^{\frac{(i-j)(i-j-1)}{2}}.
$$

预处理后直接转移即可，时间复杂度 $O(n^2)$。

参考代码如下：

```cpp
#include <iostream>
using namespace std;
const int p = 1004535809;
int f[1008];
int pw[1000006];
int fac[1006], ifac[1006];
int n;
int qpow(int a, int b, int p) {
    int ans = 1;
    while (b) {
        if (b & 1) {
            ans = 1ll * ans * a % p;
        }
        a = 1ll * a * a % p;
        b >>= 1;
    }
    return ans;
}
int comb(int n, int m) {
    return 1ll * fac[n] * ifac[m] % p * ifac[n - m] % p;
}
int main() {
    cin >> n;
    pw[0] = fac[0] = 1;
    for (int i = 1; i <= n * n; i++) {
        pw[i] = 1ll * pw[i - 1] * 2 % p;
    }
    for (int i = 1; i <= n; i++) {
        fac[i] = 1ll * fac[i - 1] * i % p;
    }
    ifac[n] = qpow(fac[n], p - 2, p);
    for (int i = n - 1; ~i; --i) {
        ifac[i] = 1ll * ifac[i + 1] * (i + 1) % p;
    }
    for (int i = 1; i <= n; i++) {
        f[i] = pw[i * (i - 1) / 2];
        for (int j = 1; j < i; j++) {
            f[i] = f[i] - 1ll * f[j] * comb(i - 1, j - 1) % p * pw[(i - j) * (i - j - 1) / 2] % p;
            f[i] = (f[i] % p + p) % p;
        }
    }
    cout << f[n];
}
```

---

## 作者：modfish_ (赞：0)

## 思路
注意到如果不要求连通，答案就是 $2^{\frac{n(n-1)}{2}}$。

那么考虑把所有不连通的都减掉，不过这仍然是比较困难的，至少我没有想到（因为我菜）。

于是，我想到了：设 $f_{k,i}$ 表示对有 $k$ 个连通块、$i$ 个点的无向图计数（**考虑连通块的顺序**）。答案即为 $f_{1,n}$。

而注意到一个可能的转移：

$$f_{k,i}=\sum_{j=1}^{i-1}f_{k-1,j}f_{1,i-j}\binom{i}{j}$$

也就是一个一个加连通块，并重新分配编号，注意：这个转移考虑了加入连通块的顺序，所以不考虑顺序的答案是 $\displaystyle\frac{f_{k,i}}{k!}$。

把组合数拆一下：

$$\frac{f_{k,i}}{i!}=\sum_{j=1}^{i-1}\frac{f_{k-1,j}}{j!}\times\frac{f_{1,i-j}}{(i-j)!}$$

记 $h_{k,i}=\displaystyle\frac{f_{k,i}}{i!}$，则：

$$h_{k,i}=\sum_{j=1}^{i-1}h_{k-1,j}\times h_{1,i-j}$$

这是一个再典不过的卷积形式，考虑令：

$$H_k(x)=\sum_{i=0}^{\infty}h_{k,i}x^i$$

且 $h_{k,0}=0$。那么：

$$H_k(x)=H_{k-1}(x)\times H_1(x)$$

递推一下就是：

$$H_k(x)=H_1(x)^k$$

再令 $G(x)=\displaystyle\sum_{k=1}^{\infty}\frac{H_k(x)}{k!}$，那么：

$$[x^i]G(x)=\sum_{k=1}^\infty\frac{h_{k,i}}{k!}=\frac{1}{i!}\sum_{k=1}^\infty\frac{f_{k,i}}{k!}$$

注意其组合意义：已知 $\displaystyle\frac{f_{k,i}}{k!}$ 是有 $k$ 个连通块、$i$ 个点的无向图，那再对 $k$ 求和就是不限制连通块个数、有 $i$ 个点的图，依据我们一开始的结论，有：

$$[x^i]G(x)=\frac{2^{\frac{n(n-1)}{2}}}{i!}$$

也就是说 $G(x)$ 可求，又因为：

$$G(x)=\sum_{k=1}^\infty\frac{H_k(x)}{k!}=\sum_{k=1}^\infty\frac{H_1(x)^k}{k!}$$

由泰勒展开公式：

$$e^x=1+\frac{x}{1!}+\frac{x^2}{2!}+\dots$$

所以：

$$G(x)=e^{H_1(x)}-1$$

即：

$$H_1(x)=\ln(G(x)+1)$$

多项式 ln 即可反求 $H_1(x)$，答案就是 $[x^n]H_1(x)$。时间复杂度 $O(n\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn = 2000005, p = 1004535809, g1 = 3;

ll fac[maxn], infa[maxn];
ll G[maxn], G_[maxn], ans[maxn];

ll qpow(ll a, ll x){
    ll res = 1;
    while(x){
        if(x & 1) res = res * a % p;
        a = a * a % p;
        x >>= 1;
    }
    return res;
}
int rev[maxn], L = 0;
void getrev(int n){
    for(int i = 1; i < n; i ++) rev[i] = (rev[i >> 1] >> 1) + ((i & 1) ? (n >> 1) : 0);
}
void NTT(ll *f, int n, int op){
    if(L != n) getrev(n), L = n;
    for(int i = 1; i < n; i ++) if(i < rev[i]) swap(f[i], f[rev[i]]);
    ll gi = qpow(g1, p - 2);
    for(int t = 1; t < n; t <<= 1){
        ll gn = qpow(op ? g1 : gi, (p - 1) / (t << 1));
        for(int i = 0; i < n; i += (t << 1)){
            ll g2 = 1;
            for(int j = 0; j < t; j ++){
                ll z1 = f[i + j], z2 = g2 * f[i + j + t] % p;
                f[i + j] = (z1 + z2) % p, f[i + j + t] = (z1 + p - z2) % p;
                g2 = g2 * gn % p;
            }
        }
    }
    if(!op){
        ll li = qpow(n, p - 2);
        for(int i = 0; i < n; i ++) f[i] = f[i] * li % p;
    }
}
ll A[maxn], B[maxn];
void mult(ll *f, ll *g, int n){
    for(int i = 0; i < n >> 1; i ++) A[i] = f[i], B[i] = g[i];
    for(int i = n >> 1; i < n; i ++) A[i] = B[i] = 0;
    NTT(A, n, 1), NTT(B, n, 1);
    for(int i = 0; i < n; i ++) f[i] = A[i] * B[i] % p;
    NTT(f, n, 0);
}
ll C[maxn], D[maxn];
void inv(ll *f, int n){
    for(int i = 0; i <= n << 1; i ++) C[i] = 0;
    C[0] = qpow(f[0], p - 2);
    for(int k = 1; k <= n; k <<= 1){
        for(int i = 0; i < k; i ++) D[i] = C[i];
        for(int i = k; i < k << 1; i ++) D[i] = 0;
        mult(D, f, k << 1);
        D[0] = (2 + p - D[0]) % p;
        for(int i = 1; i < k << 1; i ++) D[i] = (p - D[i]) % p;
        mult(C, D, k << 1);
    }
    for(int i = 0; i < n; i ++) f[i] = C[i];
}

int main(){
    int n;
    scanf("%d", &n);
    int m = 1;
    while(m <= n << 1) m <<= 1;
    fac[0] = 1;
    for(int i = 1; i <= m; i ++) fac[i] = fac[i - 1] * i % p;
    infa[m] = qpow(fac[m], p - 2);
    for(int i = m; i >= 1; i --) infa[i - 1] = infa[i] * i % p;
    for(int i = 1; i <= m; i ++) G[i] = qpow(2, (1ll * i * (i - 1) / 2) % (p - 1)) * infa[i] % p, G_[i - 1] = G[i] * i % p;
    G[0] = 1;
    inv(G, m);
    mult(G, G_, m);
    for(int i = 0; i < m; i ++) ans[i + 1] = G[i] * qpow(i + 1, p - 2) % p;
    printf("%lld\n", ans[n] * fac[n] % p);
    return 0;
}
```

---

## 作者：lzyqwq (赞：0)

选自我的[多项式与生成函数学习笔记](https://www.luogu.com.cn/article/ismqu7s9)。

> - 求 $n$ 个点有标号无向连通图的个数，对 $1004535809$ 取模。
> - $n\le 2\times 10^5$。

记 $f_n$ 为 $n$ 个点有标号无向连通图的个数，$g_n$ 为 $n$ 个点有标号无向图的个数，有 $g_n=2^{\binom{n}{2}}$，考虑每条边选或不选。

考虑钦定 $1$ 号点所在连通块大小，得到 $g_n$ 的另一种形式：

$$g_n=\sum\limits_{i=1}^n\dbinom{n-1}{i-1}f_ig_{n-i}$$

将上式变形：

$$\dfrac{g_n}{(n-1)!}=\sum\limits_{i=1}^n\dfrac{f_i}{(i-1)!}\cdot \dfrac{g_{n-i}}{(n-i)!}$$

考虑设：

$$F(x)=\sum\limits_{i=1}^n\dfrac{f_i}{(i-1)!}x^i\\G(x)=\sum\limits_{i=0}^n\dfrac{g_i}{i
!}x^i\\H(x)=\sum\limits_{i=1}^n\dfrac{g_i}{(i-1)!}x^i$$

根据变形后的等式，可以发现对于 $i\in [1,n]\cap\mathbb{Z}$，$[x^i](F(x)G(x))=[x^i]H(x)$。

那么 $F(x)G(x)\bmod x^{n+1}=H(x)\bmod x^{n+1}$。对两边同时乘以 $G(x)$ 模 $x^{n+1}$ 意义下的逆 $G^{-1}(x)$ 可以得到：

$$F(x)\bmod x^{n+1}=H(x)G^{-1}(x)\bmod x^{n+1}$$

那么可以计算出 $F(x)\bmod x^{n+1}$，就可以知道 $[x^n]F(x)$。答案就是将其乘上 $(n-1)!$。

时间复杂度 $\mathcal{O}(n\log n)$，空间复杂度 $\mathcal{O}(n)$。


```cpp
#include <bits/stdc++.h>
using namespace std; const int N = 1 << 20;
namespace Poly {
	using ll = long long; using poly = vector<ll>;
	const ll M = 1004535809, G = 3; int R[N];
	poly get(int n) { return poly(n + 1); } int dg(poly &a) { return a.size() - 1; }
	ll qp(ll x, ll y) {
		ll r = 1; for (; y; y >>= 1, x = x * x % M) if (y & 1) r = r * x % M;
		return r;
	}
	void init(int n) {
		for (int i = 0; i < n; ++i) {
			R[i] = R[i >> 1] >> 1; if (i & 1) R[i] |= n >> 1;
		}
	}
	void NTT(poly &a, int n, bool o = 0) {
		if (o) init(n);
		for (int i = 0; i < n; ++i) if (i < R[i]) swap(a[i], a[R[i]]);
		for (int i = 2; i <= n; i <<= 1) {
			ll g = qp(G, (M - 1) / i), w, u, v;
			for (int j = 0; j < n; j += i) {
				w = 1;
				for (int k = j; k < j + (i >> 1); ++k, w = w * g % M)
					u = a[k], v = w * a[k + (i >> 1)] % M,
					a[k] = (u + v) % M, a[k + (i >> 1)] = (u - v + M) % M;
			}
		}
	}
	poly operator+(poly a, poly b) {
		int n = max(a.size(), b.size()); a.resize(n); b.resize(n);
		poly c = get(n - 1); for (int i = 0; i < n; ++i) c[i] = (a[i] + b[i]) % M;
		return c;
	}
	poly operator-(poly a, poly b) {
		int n = max(a.size(), b.size()); a.resize(n); b.resize(n);
		poly c = get(n - 1);
		for (int i = 0; i < n; ++i) c[i] = (a[i] - b[i] + M) % M; return c;
	}
	poly operator*(poly a, poly b) {
		int n = a.size(), m = b.size(), L = 1; while (L < n + m - 1) L <<= 1;
		a.resize(L); b.resize(L); NTT(a, L, 1); NTT(b, L);
		for (int i = 0; i < L; ++i) a[i] = a[i] * b[i] % M; NTT(a, L);
		poly c = get(n + m - 2); ll inv = qp(L, M - 2); c[0] = a[0] * inv % M;
		for (int i = 1; i < n + m - 1; ++i) c[i] = a[L - i] * inv % M; return c;
	}
	poly mod(poly a, int n) { a.resize(n, 0); return a; }
	poly inv(poly a, int n) {
		poly c = get(0), d = get(0); c[0] = qp(a[0], M - 2); d[0] = 2;
		for (int i = 1; (1 << i - 1) < n; ++i)
			c = mod(c * (d - mod(a, 1 << i) * c), 1 << i);
		return mod(c, n);
	}
}
using namespace Poly; int n; poly f, g, h; ll p[N];
int main() {
	cin >> n; f = g = h = get(n); g[0] = 1;
	for (ll i = p[0] = 1; i <= n; ++i)
		p[i] = p[i - 1] * i % M,
		g[i] = qp(2, i * (i - 1) >> 1) * qp(p[i], M - 2) % M,
		h[i] = qp(2, i * (i - 1) >> 1) * qp(p[i - 1], M - 2) % M;
	f = mod(h * inv(g, n + 1), n + 1); cout << f[n] * p[n - 1] % M; return 0;
}
```

---

## 作者：bssmessi (赞：0)

因为直接求 $n$ 个点的连通图个数较难处理，我们考虑正难则反，将答案表示为 $n$ 个点的图的总个数减去 $n$ 个点的不连通图个数。

我们设 $f_{i}$ 为 $i$ 个点的连通图个数，$j$ 为点 $1$ 所在的连通块的大小。我们可以选择两两点之间是否连边，因此总方案数为 $2^{\frac{i(i-1)}{2}}$，在剩下的 $i-1$ 个点中选 $j-1$ 个点去构成的大小为 $j$ 的点 $1$ 所在的连通块的方案数就为 $C_{i-1}^{j-1}f_{j}$，而剩下的点我们并不在意是否连通，因此随意连边，则方案数为 $2^{\frac{(i-j)(i-j-1)}{2}}$，用乘法原理相乘即可，所以我们有：
$$f_{i}=2^{\frac{i(i-1)}{2}}-\sum_{j=1}^{i-1}C_{i-1}^{j-1}f_{j}2^{\frac{(i-j)(i-j-1)}{2}}$$
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1010,M=5e5+10,mod=1004535809;
int n,f[N],c[N][N],pw[M]={1};
int getc(int n,int m){return c[m+1][n+1];}
signed main(){
	cin>>n;
	for(int i=1;i<=5e5;i++) pw[i]=2*pw[i-1]%mod;
	c[1][1]=1;
	for(int i=2;i<=n;i++){
		for(int j=1;j<=n;j++) c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
	}
	for(int i=1;i<=n;i++){
		f[i]=pw[i*(i-1)/2];
		for(int j=1;j<=i-1;j++) f[i]=(f[i]-f[j]*getc(j-1,i-1)%mod*pw[(i-j)*(i-j-1)/2]%mod+mod)%mod;
	}
	cout<<f[n];
	return 0;
}
```

---

## 作者：可爱的小棉羊 (赞：0)

没有搞 Poly，直接秒了。

考虑先没有连通这个条件，设为 $g_n$，一共有 $\binom n2$ 条边，答案是 $g_n=2^{\binom n2}$。

然后我们设答案为 $f_n$。

我们思考，不妨扣掉那些不连通的图，我们枚举与 $1$ 这个点的连通块大小，设为 $i$，先选 $i-1$ 个点为 $\binom{n-1}{i-1}$，然后这是个连通块，剩下的 $n-i$ 个无限制乘一起为 $f_ig_{n-i}$。

答案为：

$$f_n=g_n-\sum_{i=1}^n\binom{n-1}{i-1}f_ig_{n-i}$$

做完了。

代码如下：


```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod =1004535809;
long long fpow(long long a,long long b){
	long long ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
long long n,f[1005],fac[1005];
long long C(long long n,long long m){
	return fac[n]*(fpow(fac[m]*fac[n-m]%mod,mod-2))%mod;
}
long long g(long long n){
	return fpow(2,n*(n-1)/2);
}
int main(){
	cin>>n;
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	f[0]=1;
	for(int i=1;i<=n;i++){
		f[i]=g(i);
		for(int j=0;j<i;j++){
			f[i]=(f[i]-f[j]*C(i-1,j-1)%mod*g(i-j)%mod+mod)%mod;
		}
	}
	cout<<f[n]<<"\n";
}
```

---

## 作者：__O_v_O__ (赞：0)

设 $f_n$ 为 $n$ 个点连通图个数，$g_n$ 为 $n$ 个点无向图个数。

因为最多能连 $\binom{n}{2}$ 条边，而每条边可以选择连或不连，所以 $g_n＝2^{\binom{n}{2}}$。

我们枚举图中最大连通块的点数 $j$，可以得到 $f$ 和 $g$ 的关系式：$g_n=\sum\limits_{j=1}^n\binom{n-1}{j-1}f_jg_{n-j}$。

把 $f_n$ 提出来，得到 $g_n=\sum\limits_{i=1}^{n-1}\binom{n-1}{j-1}f_jg_{n-j}+f_n$。

移项可得 $f_n=g_n-\sum\limits_{i=1}^{n-1}\binom{n-1}{j-1}f_jg_{n-j}$，递推即可，复杂度 $O(n^2)$。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mo=1004535809;
int n,fa[1000001],in[1000001];
int f[1000001],g[1000001];
int po(int a,int b){
	int an=1;
	while(b){
		if(b&1)an=an*a%mo;
		a=a*a%mo,b>>=1;
	}
	return an;
}int ny(int x){
	return po(x,mo-2)%mo;
}
int ca(int x,int y){//计算C
	return fa[x]*in[y]%mo*in[x-y]%mo;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n,fa[0]=in[0]=1;
	for(int i=1;i<=n;i++)fa[i]=fa[i-1]*i%mo;
	for(int i=1;i<=n;i++)in[i]=ny(fa[i]);//处理阶乘逆元
	for(int i=1;i<=n;i++)
		g[i]=po(2,ca(i,2))%mo;
	for(int i=1;i<=n;i++){//递推
		f[i]=g[i];
		for(int j=1;j<i;j++){
			int tp=ca(i-1,j-1)*f[j]%mo*g[i-j]%mo;
			f[i]=(f[i]-tp+mo)%mo;
		}
	}
	cout<<f[n];
	return 0;
}
```

---

