# [ARC102E] Stop. Otherwise...

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc102/tasks/arc102_c

高橋君は、互いに区別できない $ K $ 面サイコロを $ N $ 個振ります。なお、$ K $ 面サイコロとは、$ 1 $ 以上 $ K $ 以下のすべての整数の目の出る可能性のあるサイコロのことを指します。 各 $ i=2,3,...,2K $ に対し、以下の値を $ 998244353 $ で割ったあまりをそれぞれ求めてください。

- どの異なる $ 2 $ つのサイコロの出目の和も $ i $ にならないような出目の組の場合の数

なお、サイコロ同士は区別しないことに注意してください。したがって、$ 2 $ つの出目の組が異なるとは、ある目 $ k $ が存在し、出目 $ k $ の個数が異なることを指します。

## 说明/提示

### 制約

- $ 1\ \leq\ K\ \leq\ 2000 $
- $ 2\ \leq\ N\ \leq\ 2000 $
- $ K,N $ は整数である

### Sample Explanation 1

\- $ i=2 $ のとき、出目の組 $ (1,2,2),(1,2,3),(1,3,3),(2,2,2),(2,2,3),(2,3,3),(3,3,3) $ が条件を満たすので、このときの答えは $ 7 $ です。 - $ i=3 $ のとき、出目の組 $ (1,1,1),(1,1,3),(1,3,3),(2,2,2),(2,2,3),(2,3,3),(3,3,3) $ が条件を満たすので、このときの答えは $ 7 $ です。 - $ i=4 $ のとき、出目の組 $ (1,1,1),(1,1,2),(2,3,3),(3,3,3) $ が条件を満たすので、このときの答えは $ 4 $ です。

## 样例 #1

### 输入

```
3 3```

### 输出

```
7
7
4
7
7```

## 样例 #2

### 输入

```
4 5```

### 输出

```
36
36
20
20
20
36
36```

## 样例 #3

### 输入

```
6 1000```

### 输出

```
149393349
149393349
668669001
668669001
4000002
4000002
4000002
668669001
668669001
149393349
149393349```

# 题解

## 作者：坑队友的小白 (赞：9)

首先考虑对于单个 $x~(x\in[2,2K])$ 可以怎么求。

对于点数 $i~(i\in[1,K])$ 进行分情况讨论。

- $x-i\in[1,K]$ ，那么点数集合中 $i$ 和 $x-i$ 只能至多出现其中一种，我们称 $i$ 和 $x-i$ 是 “一对数”。
- 当 $x-i=i$ 的时候，点数集合中只能出现至多一个 $i$ 。
- $x-i\not\in [1,K]$，那么没有限制，可以随便取。

接下来考虑 $dp$。

设 $f(i,j)$ 表示考虑了 $i$ 对数（不考虑 $x-i=i$ 的情况），其中选择了 $j$ 个数的组成的集合个数，很容易想到：
$$
f(i,j)=f(i-1,j)+2 \times \sum_{k=1}^j f(i-1,j-k)
$$

同样的，设 $g(i,j)$ 表示考虑了 $i$ 个没有限制的数，其中选择了 $j$ 个数组成的集合数，同理可以得到：
$$
g(i,j)=\sum_{k=0}^j g(i-1,j-k)
$$
上述两个 $dp$ 都可以使用前缀和优化。

接着对于每一个 $x$，求出满足三个条件的数各有多少个，然后将各自的方案数乘起来就行了。

```cpp
#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int maxn = 2e3 + 5;
const LL MOD = 998244353;

int n, m;
LL f[maxn][maxn], g[maxn][maxn];

int main() {
    scanf("%d%d", &m, &n);
    f[0][0] = g[0][0] = 1;
    LL s0, s1;
    for (int i = 1; i <= m; i++) {
        s0 = s1 = 0;
        for (int j = 0; j <= n; j++)
            f[i][j] = (f[i - 1][j] + s0 * 2 % MOD) % MOD,
            s0 = (s0 + f[i - 1][j]) % MOD,
            g[i][j] = (g[i - 1][j] + (j > 0 ? g[i][j - 1] : 0)) % MOD;
    }
    for (int i = 2; i <= (m << 1); i++) {
        int c1 = 0, c2 = (i % 2 == 0), c3; LL ans = 0;
        for (int j = 1; j <= m; j++) c1 += (i - j > m || i - j <= 0);
        c3 = (m - c1 - c2) >> 1;
        for (int j = 0; j <= n; j++) ans = (ans + f[c3][j] * g[c1][n - j] % MOD) % MOD;
        if (c2) for (int j = 0; j < n; j++) ans = (ans + f[c3][j] * g[c1][n - j - 1] % MOD) % MOD;
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：namespace_std (赞：8)

题意：

对所有 $i=2,...,2k$，求出元素取值范围在 $[1,k]$ 之内，且满足任意两个**位置不同**的数的和不等于 $i$ 的无序 $n$ 元组个数。

分析：

我们发现，由于问题具有对称性，$i=k+1+x$ 时的答案和$i=k+1-x$ 时相同。

因此我们只需要考虑 $2 \leq i \leq k+1$ 的情况。

此时，我们可以枚举有 $t$ 个数小于 $i$ ，此时还剩下 $n-t$ 个数大于等于 $i$ 。

此时，这 $n-t$ 个数可以在 $[i,k]$ 内任意选择，方案数为 $C_{k-i+n-t}^{n-t}$ 。

继续考虑剩下的 $t$ 个数。

记 $F(i,j)$ 表示 $[1,i]$ 内取出 $j$ 个单调不减的数，且没有任意两个数的和为 $i+1$ 的方案数。

显然答案是 $\Sigma_{t=0}^{n} C_{k-i+n-t}^{n-t}*F(i-1,t)$ 。

注意到一件事情：当 $i=k+1$ 的时候，上述式子中的 $C_{k-i+n-t}^{n-t}$ 可能没有意义。

但是我们会发现，当 $i=k+1$ 的时候，答案等于 $F(k,t)$ ，直接返回即可。

此时，我们只需要预处理出 $F(i,j)$ ，便可以在 $O(n^2)$ 的时间内计算出所有的 $i$ 个答案。

考虑 $F(i,j)$ 的组合意义。

首先，当 $j=0$ 时，显然 $F(i,j)=1$。

- 当 $i$ 是奇数时：

我们枚举是否选择 $(i+1)/2$ 。

如果选择了，那只能选择 $1$ 个，状态等价于 $F(i-1,j-1)$ 。

否则，状态等价于 $F(i-1,j)$ 。

所以，$F(i,j)=F(i-1,j)+F(i-1,j-1)$。

- 当 $i$ 是偶数时：

如果我们既不选择 $1$ 也不选择 $i$ ，状态等价于 $F(i-2,j)$ 。

如果我们选择了 $x$ 个 $i$ ，状态等价于 $F(i-2,j-x)$。

选择了 $x$ 个 $1$ 的时候同理。

所以，$F(i,j)=2*\Sigma_{k=0}^{j-1}F(i-2,k)+F(i-2,j)$ 。

上式直接求是 $O(n^3)$ 的，但是显然可以前缀和优化为 $O(n^2)$ 。

并且，通过~~打表~~严格的数学归纳，我们可以发现，当 $i$ 为偶数时，$F(i,j)=F(i-1,j)+F(i,j-1)$ 。

综上，我们在 $O(n^2)$ 的时间复杂度内解决了这道题。

Code:

```cpp
#include<cstdio>
#include<cstring>
typedef long long ll;
const ll mod=998244353;
int k,n;
ll C[4444][4444],Lim[2222][2222];     //Lim(i,j)=F(i,j)
ll ans[6666];
inline ll qpow(ll x,ll k)
{ll r=1;for(;k;k>>=1,(x*=x)%=mod)if(k&1)(r*=x)%=mod;return r;}
inline ll solve(int v)
{
	register int i;
	ll ret=0;
    if(v>k)return Lim[v-1][n];        //特判v=k+1
	for(i=0;i<=n;i++)
		(ret+=Lim[v-1][i]*C[n+k-v-i][n-i])%=mod;
	return ret;
}
int main()
{
	scanf("%d%d",&k,&n);
	register int i,ii;
	for(i=0;i<=4040;i++)C[i][0]=C[i][i]=1;
	for(i=0;i<=2020;i++)Lim[i][0]=1;
	for(i=1;i<=4040;i++)
		for(ii=1;ii<i;ii++)
			C[i][ii]=(C[i-1][ii-1]+C[i-1][ii])%mod;
	for(i=1;i<=2020;i++)
		for(ii=1;ii<=2020;ii++)
		{
			if(i&1)Lim[i][ii]=(Lim[i-1][ii-1]+Lim[i-1][ii])%mod;
			else Lim[i][ii]=(Lim[i-1][ii]+Lim[i][ii-1])%mod;
		}
	for(i=2;i<=k+1;i++)ans[i]=solve(i);
	for(i=k+2;i<=k*2;i++)ans[i]=ans[k*2+2-i];
	for(i=2;i<=k*2;i++)printf("%lld\n",ans[i]);
}
```

---

## 作者：lx_zjk (赞：6)

~~好像大佬们用的都是容斥，但菜鸡不会容斥~~


我们考虑对每个$x$ 计算答案

我们将数分$3$种情况讨论

### 第一种是$i \lt k$ 并且$x - i \lt k$

这种情况我们发现$i$和$x-i$只能选一种

### 第二种是$i \geq x$

这种情况选数是无限制的，我们可以随便选。

### 第三种是$i = x - i$ $(x为偶数时)$

这种情况$i$要么选$1$次要么不选。

## 计算答案
首先第$3$中数要么选要么不选，所以如果存在第$3$种数，我们可以大(小)力分类讨论选这个数还是不选。

那么我们只需要枚举第一类数选了$i$个，那么第二类数就只能选$n-i$个(或者$n-i-1$，选了第$3$类数)。

那么答案就是$\sum_{i=0}^n f_i \times g_{n-i}$

$f[i]$是第一类数选$i$个的方案数，$g[i]$ 是第二类数选$i$个的方案数。

对于第二类数，因为选数是没有限制的，所以我们可以直接用组合数计算方案，假设选定区间是$[i, j]$ ，要选$k$个数，那么答案就是$\binom{j-i+k}{k}$

对于第一类数直接$dp$ 很容易重复，我们考虑设计新的状态。

$f[i][j][0]$表示选到了第$i$种数，选了$j$个数，这类数没有选。

$f[i][j][1]$表示选到了第$i$种数，选了$j$个数，这类数选了$i$

$f[i][j][2]$表示选到了第$i$种数，选了$j$个数，这类数选了$x-i$

转移显然。

计算答案时，我们算出最大的$i$满足$x-i \lt k$

然后答案就是
$$
\sum_{i=0}^n (f[K][i][0]+f[K][i][1]+f[K][i][2]) \binom{k-x+n-i}{n-i}
$$

### code
```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <queue>

using namespace std;

template <typename T> void chkmax(T &x, T y) {x = x > y ? x : y;}
template <typename T> void chkmin(T &x, T y) {x = x > y ? y : x;}

typedef long long ll;

const int INF = 2139062143;

#define DEBUG(x) std::cerr << #x << " = " << x << std::endl

template <typename T> void read (T &x) {
    x = 0; bool f = 1; char ch;
    do {ch = getchar(); if (ch == '-') f = 0;} while (ch > '9' || ch < '0');
    do {x = x * 10 + ch - '0'; ch = getchar();} while (ch >= '0' && ch <= '9');
    x = f ? x : -x;
}

template <typename T> void write (T x) {
    if (x < 0) x = ~x + 1, putchar ('-');
    if (x > 9) write (x / 10);
    putchar (x % 10 + '0');
}

#define int ll

const int N = 4000 + 5;
const int mod = 998244353;

int n, k, f[N][N][3], ret[N], fac[N], invfac[N];

inline int qpow(int a, int b) {
    int ret = 1;
    while(b) {
        if(b & 1) ret = 1ll * ret * a % mod;
        a = 1ll * a * a % mod;
        b >>= 1;
    }
    return ret;
}

inline void init(int NN) {
    fac[0] = 1;
    for(int i = 1; i <= NN; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
    invfac[NN] = qpow(fac[NN], mod - 2);
    for(int i = NN - 1; i >= 0; i--) invfac[i] = 1ll * invfac[i + 1] * (i + 1) % mod;
}

inline int C(int n, int m) {
    return 1ll * fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}

inline int calc(int i, int j, int k) {
    return C(j - i + k, k) % mod;
}

signed main() {
    read(k); read(n); init(n + k);
    f[0][0][0] = 1;
    for(int i = 1; i <= k; i++) {
        f[i][0][0] = f[i - 1][0][0];
        for(int j = 1; j <= n; j++) {
            f[i][j][0] = (f[i - 1][j][1] + f[i - 1][j][2] + f[i - 1][j][0]) % mod;
            f[i][j][1] = (f[i][j - 1][1] + f[i][j - 1][0]) % mod;
            f[i][j][2] = (f[i][j - 1][2] + f[i][j - 1][0]) % mod;
        }
    }
    for(int i = 2; i <= k + 1; i++) {
        if(i % 2 == 0) {
            int K = i / 2 - 1, ans = 0; 
            if(i <= k) {
                for(int j = 0; j <= n; j++) {
                    if(n - j - 1 >= 0) ans = (ans + 1ll * (f[K][j][1] + f[K][j][2] + f[K][j][0]) % mod * calc(i, k, n - j - 1) % mod) % mod;
                    ans = (ans + 1ll * (f[K][j][1] + f[K][j][2] + f[K][j][0]) % mod * calc(i, k, n - j) % mod) % mod;
                }   
            } else {
                ans = (ans + (f[K][n][1] + f[K][n][2] + f[K][n][0]) % mod + (f[K][n - 1][1] + f[K][n - 1][2] + f[K][n - 1][0]) % mod) % mod;
            }
            ret[i] = ret[k * 2 + 2 - i] = ans;
        } else {
            int K = i / 2, ans = 0; 
            if(i <= k) {
                for(int j = 0; j <= n; j++) {
                    ans = (ans + 1ll * (f[K][j][1] + f[K][j][2] + f[K][j][0]) % mod * calc(i, k, n - j) % mod) % mod;
                }
            } else {
                ans = (f[K][n][1] + f[K][n][2] + f[K][n][0]) % mod;
            }
            ret[i] = ret[k * 2 + 2 - i] = ans;
        }
    }
    for(int i = 2; i <= 2 * k; i++) printf("%lld\n", ret[i]);
    return 0;
}
```

---

## 作者：Soulist (赞：4)


有 $n$ 个骰子，每个骰子有 $K$ 个面，上面有 $1$ 到 $K$。骰子都是一样的。

现在对于 $[2,2K]$ 中的每一个数 $x$，要求出任意投这个 $n$ 个骰子使得不存在任意两个骰子的点数和为 $x$ 的方案数。

- $n,K\le 2000$

---

$\rm Sol:$

设考虑到的数为 $y$

考虑假设权值 $i$ 出现了，那么 $y-i$ 就不能出现，所以这样的权值会因为 $y$ 而两两配对。

枚举一个 $y$，将权值进行两两配对，这样会有 $\frac{y}{2}$ 个配对权值以及 $K-x$ 个单独权值，还有一个仅能出现一次的 $\frac{y}{2}$（如果 $y$ 为奇数）（若 $y\le K$，另一边处理方式类似）

然后由于骰子本质相同，我们只需要每种权值的出现次数即可，考虑配对权值贡献的 OGF 必然形如：

$$1+2x+2x^2+...=\frac{x+1}{1-x}$$

考虑仅能出现一次的权值的 OGF 必然形如：

$$1+x$$

考虑单独权值的 OGF 必然形如：

$$1+x+2x+...=\frac{1}{1-x}$$

于是我们得到答案为：

$$\frac{(1+x)^m}{(1-x)^k}$$

$m,k$ 需要根据 $y$ 进行推算，然后需要考虑展开式里面的 $[x^n]$ 前面的系数即可，将答案视为 $(1+x)^m\cdot (1-x)^{-k}[x^n]$，前者的系数为 $\binom{m}{i}x^i$，后者为 $\binom{k+i-1}{i}[x^i]$，对于某个 $y$，计算答案显然为一个 $\mathcal O(n)$ 的卷积，所以暴力即可，复杂度为 $\mathcal O(nK)$ 

---

## 作者：yanghanyv (赞：3)

~~这是一个没有必要的复杂做法，但我考场上第一时间想到的就是这个做法。~~

## 分析
首先观察样例。发现答案有对称性，所以我们只需要求出 $\left[2,k+1\right]$ 区间内的答案。又发现相邻两项答案是一样的，所以只需要处理其中奇数情况的答案。

## 推式子
设 $f_s$ 表示点数和不为 $2s+1$ 时的方案数，此时有 $s$ 对不能同时出现的点数，写出暴力计算的式子。
$$
f_s = \sum\limits_{i=1}^{k-s}\sum\limits_{j=1}^{s}\binom{n-1}{i-1}\binom{s}{j}\binom{k-2s}{i-j}2^{j}
$$

上面的式子中，$i$ 表示总共出现了 $i$ 种点数，其中互斥的 $s$ 对点数中出现了 $j$ 对。

发现两个含有 $i$ 的组合数似乎可以范德蒙德卷积，于是交换一下 $i$ 和 $j$ 的位置。
$$
\begin{aligned}
f_s 
&= \sum\limits_{i=1}^{s}2^{i}\binom{s}{i}\sum\limits_{j=1}^{k-s}\binom{n-1}{j-1}\binom{k-2s}{j-i}\\
&= \sum\limits_{i=1}^{s}2^{i}\binom{s}{i}\sum\limits_{j=1}^{k-s}\binom{n-1}{n-j}\binom{k-2s}{j-i}\\
&= \sum\limits_{i=1}^{s}2^{i}\binom{s}{i}\binom{n+k-2s-1}{n-i}\\
\end{aligned}
$$

在用过范德蒙德卷积后，这个式子求和的复杂度为 $\mathrm{O(k)}$ ，我们要计算 $\mathrm{O(n)}$ 个询问，所以总复杂度为 $\mathrm{O(nk)}$。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e3+5;
const int MOD=998244353;
void exgcd(int a,int &x,int b,int &y){
	if(!b){
		x=1;
		y=0;
	}else{
		exgcd(b,y,a%b,x);
		y-=a/b*x;
	}
}
int Inv(int x){
	int res,y;
	exgcd(x,res,MOD,y);
	return (res%MOD+MOD)%MOD;
}
int Add(int a,int b){
	return a+b>=MOD?a+b-MOD:a+b;
}
int Sub(int a,int b){
	return a-b<0?a-b+MOD:a-b;
}
int Mul(int a,int b){
	return 1ll*a*b%MOD;
}
int Div(int a,int b){
	return 1ll*a*Inv(b)%MOD;
}
int qpow(int a,int b){
	int res=1;
	while(b){
		if(b&1){
			res=Mul(res,a);
		}
		a=Mul(a,a);
		b>>=1;
	}
	return res;
}
int n,k,f[2*N],fac[2*N],infac[2*N];
int C(int n,int m){
	return n>=m?Mul(fac[n],Mul(infac[m],infac[n-m])):0;
}
int main(){
	scanf("%d%d",&k,&n);
	fac[0]=1;
	for(int i=1;i<=n+k;i++){
		fac[i]=Mul(fac[i-1],i);
	}
	infac[n+k]=Inv(fac[n+k]);
	for(int i=n+k-1;i>=0;i--){
		infac[i]=Mul(infac[i+1],i+1);
	}
	for(int i=1;2*i<=k+1;i++){
		for(int j=0;j<=min(i,n);j++){
			f[2*i]=Add(f[2*i],Mul(Mul(qpow(2,j),C(i,j)),C(n+k-2*i-1,n-j)));
		}
	}
	for(int i=1;2*i<=k;i++){
		f[2*i+1]=f[2*k+2-2*i]=f[2*k+2-2*i-1]=f[2*i];
	}
	for(int i=2;i<=2*k;i++){
		printf("%d\n",f[i]);
	}
	return 0;
}
```

---

## 作者：YksKuusiTAlv (赞：3)

## 碎碎念

首先枚举每个数之后有一个显然的推组合恒等式的做法，最后一篇题解讲的很详细了，dp 做法不过也就是强行去 dp 组合恒等式，没有什么启发性，直到我看到了题解区里面的容斥做法，诶我一开始就想的容斥想了一会不会做啊，这还能容斥？？！想了一会才发现，**我对容斥已经思维定式了，这题的容斥，很简单，但是并非简单的对个数容斥。**

## sol

首先肯定要枚举 $x$ 去算答案，要求是不能有两个凑出 $x$ ，我们枚举有多少对加起来 $=x$ ，然后发现每个骰子可能在多个对里面，我们根本无法计算钦定的方案数。

考虑容斥的本质，就是让不合法的被计算 0 遍，而不是傻傻的枚举不合法个数。

“不合法” 是我们规定的，只要他有 $=x$ 的对就不合法，那我们何必对一种 $y+z=x$ 的 $(y,z)$ 钦定多次呢，这样只会徒增我们钦定的难度？

我们只考虑钦定有多少 **种** 无序对 $(y,z)$ 满足 $y+z=x$ ，假设一共有 $r_x$ 种，容斥之后组合数选一选再把剩下的插板分配即可。

$$Ans_x=\sum_{t=0}^{r_x} (-1)^t \binom {r_x} t \binom {n-2t+K-1}{K-1}$$

---

## 作者：P2441M (赞：2)

[原题链接](https://atcoder.jp/contests/arc102/tasks/arc102_c)

## 简述题意
有 $n$ 个**互不区分**的骰子，每个骰子有 $K$ 个面，上面有 $1$ 到 $K$。两个局面不同当且仅当存在一个点数 $i$ 使得投出 $i$ 的数量不同。对于 $[2,2K]$ 中的每一个数 $x$，求出任意投这个 $n$ 个骰子使得不存在任意两个骰子的点数和为 $x$ 的方案数。答案对 $998244353$ 取模。

## 题解
有 DP 做法，但我直接大力容斥不用动脑。

对于每个 $x\in[2,2K]$ 求解答案。不存在任意两个骰子的点数和为 $x$，等价于点数集合**恰好 $0$ 对** $p$ 和 $x-p$ 同时存在。可以发现我们更容易计算**至少 $i$ 对** $p$ 和 $x-p$ 同时存在，所以考虑二项式反演计算这个东西。

我们先求出有整数对 $(p,x-p)$ 的个数 $y$，其中 $p\leq x-p$。容易列出不等式 $1\leq p\leq x-p\leq k$，其解集为 $\left[\max(x-k,1),\lfloor x/2\rfloor\right]$，因此 $y=\lfloor x/2\rfloor-\max(x-k,1)+1$。

然后我们组合计算**至少 $i$ 对** $p$ 和 $x-p$ 同时存在的方案数 $g_i$。选出这些数对显然有 $\binom{y}{i}$ 种方案。对于剩下的 $n-2i$ 个骰子，它们投出的数无限制，总方案数可以插板算出来，等价于把 $n-2i$ 个骰子分成 $k$ 组（分到第 $j$ 组表示这个骰子投出来的数是 $j$），组内可空，方案数为 $\binom{n-2i+k-1}{k-1}$。所以，我们有
$$
g_i=\binom{y}{i}\times\binom{n-2i+k-1}{k-1}
$$

套一个裸的二项式反演上去就有
$$
ans=\sum_{i=0}^{y}(-1)^ig_i
$$

于是我们就轻松切了这道题。时间复杂度为 $O(nk)$。

具体实现时，计算组合数 $\binom{n}{m}$ 记得在 $n<m$ 时算作 $0$。

## 代码
```cpp
#include <iostream>

using namespace std;

#define lowbit(x) ((x) & -(x))
#define add_mod(x, v) (x) = ((ll)(x) + (v)) % MOD
#define mul_mod(x, v) (x) = (1ll * (x) * (v)) % MOD
#define sub_mod(x, v) (x) = (((ll)(x) - (v)) % MOD + MOD) % MOD
#define chk_min(x, v) (x) = min((x), (v))
#define chk_max(x, v) (x) = max((x), (v))
typedef long long ll;
typedef pair<int, int> pii;
const int MAX_S = 4e3 + 5, MOD = 998244353;

int n, k, y;
int fac[MAX_S], inv_fac[MAX_S];
ll ans;

ll quick_power(ll a, ll b) {
	ll res = 1;
	for (; b; b >>= 1) {
		if (b & 1) mul_mod(res, a);
		mul_mod(a, a);
	}
	return res;
}

void preproc(int lim) {
	fac[0] = 1;
	for (int i = 1; i <= lim; ++i) fac[i] = 1ll * fac[i - 1] * i % MOD;
	inv_fac[lim] = quick_power(fac[lim], MOD - 2);
	for (int i = lim - 1; i >= 0; --i) inv_fac[i] = 1ll * inv_fac[i + 1] * (i + 1) % MOD;
}

int comb(int n, int m) {
	if (n < m) return 0;
	return 1ll * fac[n] * inv_fac[m] % MOD * inv_fac[n - m] % MOD;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> k >> n;
    preproc(n + k);
    for (int x = 2; x <= (k << 1); ++x) {
    	y = (x >> 1) - max(x - k, 1) + 1;
    	ans = 0;
    	for (int i = 0, c = 1; i <= y; ++i, c = -c) {
    		add_mod(ans, 1ll * comb(y, i) * comb(n - (i << 1) + k - 1, k - 1) % MOD * c % MOD);
    		ans = (ans + MOD) % MOD;
    	}
    	cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：Prean (赞：2)

这题明明很简单啊，为什么要容斥啊？

对于每个 $k$ 分别算答案。

将 $i$ 和 $k-i$ 配对，问题变成了每一组最多选一个。需要注意的是当 $2\mid k$ 的时候需要枚举 $\frac{k}{2}$ 选还是不选。

假设现在有 $x$ 组包含两个数，$y$ 组包一两个数，问题等价于在 $x+y$ 个数中任意选，被选到的 $x$ 附带一个 $2$ 的权值。

直接枚举有几个选到了 $x$，几个选到了 $y$，答案就是:
$$\sum_{i=0}^{n}F_{x,i}G_{y,n-i}$$
其中 $F_{n,m}$ 表示 $n$ 个数加起来和为 $m$ 的方案数，每个数的权值为 $2^{[x_i>0]}$，$G_{n,m}$ 类似。

显然有的是 $F_{n,m}=2(\sum_{i=0}^{m-1}F_{n-1,i})+F_{n-1,m},G_{n,m}=\sum_{i=0}^{m-1}G_{n-1,i}+G_{n-1,m}$

前缀和优化，复杂度 $O(n^2)$ 可以通过。
```cpp
#include<cstdio>
const int M=2005,mod=998244353;
int n,k,ans[M],S1[M],S2[M],F[M][M],G[M][M];
inline int calc(const int&n,const int&x,const int&y){
	int ans(0);for(int i=0;i<=n;++i)ans=(ans+1ll*F[x][i]*G[y][n-i])%mod;return ans;
}
signed main(){
	scanf("%d%d",&k,&n);S1[0]=S2[0]=F[0][0]=G[0][0]=1;
	for(int i=1;i<=k;++i){
		for(int j=1;j<=n;++j)S1[j]=(S1[j-1]+F[i-1][j])%mod,S2[j]=(S2[j-1]+G[i-1][j])%mod;
		for(int j=0;j<=n;++j)F[i][j]=(2ll*(j?S1[j-1]:0)+F[i-1][j])%mod,G[i][j]=((j?S2[j-1]:0)+G[i-1][j])%mod;
	}
	for(int i=1;i<=k;++i){
		const int&c=i/2;if(c*2==i)ans[i]=calc(n,c,k-2*c);else ans[i]=(calc(n,c,k-2*c-1)+calc(n-1,c,k-2*c-1))%mod;
	}
	for(int i=1;i<=k-1;++i)printf("%d\n",ans[i]);printf("%d\n",ans[k]);for(int i=k-1;i>=1;--i)printf("%d\n",ans[i]);
}
```

---

## 作者：WeWantToRun (赞：1)

题解区都写的好复杂。

枚举 $i$，那考虑容易的 $i$ 为奇数的情况，他会有 $(i-1)/2$ 个数对要求不能全部选择（比如 $i=5$ 的时候数对是 $(1,4),(2,3)$）。那么枚举这些数对里我选了多少个，使得选择的数对有一个数出现在了答案里，假设有 $j$ 个数对，那么就转化成今年杭州站的 J，也就是有 $P $ 个可选可不选的数和 $Q$ 个必须选的数，求选择方案数，那这个方案容易求得是 $C(P+Q+1,Q+1)$。所以说对于这个 $j$ 的答案就是 $C(P+Q+1,Q+1)\times C((i-1)/2,j)\times 2^j$，其中 $P,Q$ 都可以算出来。这个式子因为我要在这么多个数对里选 $j$ 对，每一对有两种选法。然后如果 $i$ 是偶数那么 $i/2$ 要么选一个要么不选，两种都可以转化为上面的情况。代码就不贴了。

---

## 作者：13402805827wuaiyang (赞：1)

这是生成函数的另一种做法。

容易发现答案是对称的，所以我们只需要求解 $x\in [2,K+1]$ 中的答案。

我们考虑的对象是大小为 $s$ 的骰子的个数。可以注意到，对于每个要求解的 $x$，我们会产生 $T$ 对互相限制的二元组（具体而言，$T=\min(x-1,k)$），每组中的和为 $x$ ,而这些组其它方面都一样，所以我们可以将一个组作为一个对象考虑。

对于一个组，其选出 $0$ 个骰子（不选）的方案数为 $1$，其余为 $2$。所以其的生成函数为：

$$
1+\sum_{i=1}^\infin 2x^i=1+\frac{2x}{1-x}=\frac{1+x}{1-x}
$$

一种特殊情况是点数为 $\frac{x}{2}$ 的骰子（如果存在的话），不过这种情况我们之后特判可以解决。（其只可能选一个或是不选）

对于没有受到限制的骰子种类，其的选择方案数为：
$$
\sum^\infin_{i=0}x^i=\frac{1}{1-x}
$$

对于同一个 $T$ ,我们需要考虑的一类对象有 $\lfloor \frac T2 \rfloor$ 个，需要考虑的二类对象有 $k-T$ 个（无论点数为 $\frac x2$ 的骰子选没选）。那么整体的式子就是：
$$
(\frac{1+x}{1-x})^{\lfloor \frac T2\rfloor}(\frac{1}{1-x})^{k-T}
$$

之前的题解要把这个东西展开，但是实际上不用。我们可以发现 $T$ 每次的变化幅度是很小的，所以我们可以直接维护这个式子（展开式）。

总复杂度 $O(nk)$。

注意多项式除法可以以多项式乘法的逆过程实现。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2005,mod=998244353;
int n,k,f[N];
inline void c1(){// /(1-x) 
	for(int i=0;i<=n;i++) (f[i+1]-=f[i]*-1)%=mod;
}
inline void c2(){// *(1+x) 
	for(int i=n;i>=0;i--) (f[i+1]+=f[i]*1)%=mod;
}
inline void c3(){// *(1-x) 
	for(int i=n;i>=0;i--) (f[i+1]+=f[i]*-1)%=mod;
}
inline int calc(int T){
	return ((f[n]+(T%2?f[n-1]:0))%mod+mod)%mod;
}
int ans[N*2];
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>k>>n;
	
	f[0]=1;
	for(int i=1;i<=k;i++) c1();
	int T=0;
	for(int s=1;s<=k+1;s++){
		int NT=min(s-1,k);
		if(NT>T){
			if(NT/2!=T/2) c2();
			else c3();
		}
		T=NT;
		if(s!=1) ans[s-1]=calc(T);
	}
	for(int i=1;i<=k;i++) ans[k+i]=ans[k-i];
	for(int i=1;i<=k*2-1;i++) cout<<ans[i]<<"\n";
	return 0;
}
```

---

## 作者：intel_core (赞：1)

考虑两数相加不为 $m$ 条件的等价条件。注意到可以算出两数相加为 $m$ 的数对的数量，再单独讨论一下不能选两次的数即可。

在计算 $m$ 的答案时，先处理出 $x,y$ 依次表示二选一的数对数量和只能选一个的数是否存在。

然后考虑容斥，钦定 $i$ 个二选一的数对不能选，贡献是 $(-1)^i2^{x-i}(C_{k-x-y-i+n-1}^{k-x-y-i-1}+yC_{k-x-y-i+n-2}^{k-x-y-i-1})$。

预处理组合数即可 $O(n^2)$ 计算。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=4e3+10;
#define int long long
const int MOD=998244353;
int n,m,c[NR][NR],pw[NR];

void add(int &x,int y){x=(x+y)%MOD;}
signed main(){
	cin>>n>>m;
	pw[0]=1;
	for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2%MOD;
	for(int i=0;i<=n+m;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++)c[i][j]=(c[i-1][j]+c[i-1][j-1])%MOD;
	}
	for(int i=2;i<=2*n;i++){
		int x=min((i-1)/2,n-i/2),y=n-2*x-(i%2==0),z=(i%2==0),ans=0;
		for(int j=0;j<=x;j++){
			if(j&1)add(ans,-c[x][j]*pw[x-j]%MOD*(c[n-j-z-x+m-1][n-j-z-x-1]+z*c[n-j-z-x+m-2][n-j-z-x-1])%MOD);
			else add(ans,c[x][j]*pw[x-j]%MOD*(c[n-j-z-x+m-1][n-j-z-x-1]+z*c[n-j-z-x+m-2][n-j-z-x-1])%MOD);
		}
		cout<<(ans+MOD)%MOD<<endl;
	}
	return 0;
}
```

---

## 作者：Terac (赞：1)

为啥可以爆标题解区没人说？

你考虑怎么对单个 $x$ 求答案，求出满足 $i+j=x,i<j$ 的 $(i,j)$ 数量 $m=\left\lfloor \dfrac{x}{2}\right\rfloor-\max(1,x-k)$。

考虑容斥，$ans_m=\sum\limits_{i=0}^m(-1)^i\dbinom{m}{i}\dbinom{n+k-1-2i}{k-1}$。表示钦定选了 $i$ 对和为 $x$ 后的方案数，剩下的可自由分配的骰子个数即 $n-2i$，直接插板法求得。$x$ 的答案即为 $ans_m$，至此可以 $O(nk)$ 解决该问题。

令 $f_i=1,g_i=(-1)^i\dbinom{n+k-1-2i}{k-1}$。$ans$ 的 EGF 即为 $f$ 的 EGF 卷上 $g$ 的 EGF。多项式乘法可做到 $O(k\log k)$。所以此题完全可以出到 $k\le 10^6$。

---

## 作者：Purslane (赞：0)

# Solution

如果给了限制 $x$ 相当于：$\forall i+j=x$，如果 $i=j$ 则**这种数最多出现一个**，否则 $i$ 和 $j$ **有一个未出现**。

相当于给了你若干个数，他们分为三种：

1. 只能选 $1$ 个。
2. 只有一种形态，该是多少就是多少。
3. 如果这个数**选了**，就有了两种形态，二选一。

当 $x$ 给定的时候，三种形态的数的个数就确定了。注意第一种数只有 $0$ 或 $1$ 个，可以直接枚举，因此我们只需要考虑二三两种情况。

设 $f_{i,j}$ 表示，有 $j$ 种可能的第二种数，将 $i$ 个**互不区分**的数染上这些颜色的方案数；$g_{i,j}$ 指的是第三种数。

转移都可以简单的前缀和优化。计算答案时只需要枚举两种数是如何分配。复杂度为 $O(nk)$。

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2000+10,MOD=998244353;
int n,k,f[MAXN][MAXN],g[MAXN][MAXN];
int solve(int n,int c1,int c2) {
	int ans=0;
	ffor(j,0,n) ans=(ans+f[c1][j]*g[c2][n-j])%MOD;
	return ans;	
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>k>>n;
	f[0][0]=g[0][0]=1;
	ffor(i,1,k) {
		int pre=0;
		ffor(j,0,n) f[i][j]=(pre+f[i-1][j])%MOD,pre=f[i][j];
		pre=0;
		ffor(j,0,n) g[i][j]=(2*pre+g[i-1][j])%MOD,pre=(pre+g[i-1][j])%MOD;
	}
	ffor(i,2,k+k) {
		int c1=0,c2=0,flg=0;
		ffor(j,1,k) {
			if(j+j==i) flg=1;
			else if(i-j>=1&&i-j<=k&&i-j>j) c2++;
			else if(i-j<1||i-j>k) c1++;
		}
		int ans=solve(n,c1,c2);
		if(flg) ans=(ans+solve(n-1,c1,c2))%MOD;
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

