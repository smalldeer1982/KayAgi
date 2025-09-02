# Mivik 写书

## 题目背景

Mivik 想当大作家。

## 题目描述

Mivik 的键盘上有 $m$ 个不同的按键，对应着 $m$ 个不同的字符。由于 Mivik 不会写文章，所以他只好**等概率**随机乱按了 $n$ 个键，打出了一篇文章。

Mivik 定义一篇文章的复杂度是这篇文章所有**非空**本质不同子串的数目。我们认为两个字符串本质不同当且仅当它们的长度不同或者它们有任意一位上的字符不同。例如，文章 `abaa` 的复杂度是 8，因为它一共有 `a`、`b`、`ab`、`ba`、`aa`、`aba`、`baa`、`abaa` 这 8 个非空的本质不同子串。

Mivik 现在想知道，这篇文章期望的复杂度是多少。由于 Mivik 不喜欢奇形怪状的小数，你只需要输出期望的复杂度对 $10^9+7$ 取模后的值。

## 说明/提示

### 样例解释

样例一：假设键盘上的字符分别为 `a` 和 `b`，那么可能打出来的文章一共有 `aa`、`ab`、`ba`、`bb` 四种，它们的复杂度分别为 2、3、3、2，因此答案为 $\frac{2+3+3+2}{4}=\frac{5}{2}$，对 $10^9+7$ 取模后得到 500000006。

### 数据范围

对于全部数据，有 $1\le n\le 20$，$1\le m\le 5\cdot 10^6$。

Subtask 1 (10 pts)：满足 $1\le n, m\le 7$。

Subtask 2 (20 pts)：满足 $1\le n\le 5$。

Subtask 3 (20 pts)：满足 $1\le n\le 10$。

Subtask 4 (50 pts)：无特殊限制。

## 样例 #1

### 输入

```
2 2```

### 输出

```
500000006```

## 样例 #2

### 输入

```
3 3```

### 输出

```
5```

## 样例 #3

### 输入

```
3 4```

### 输出

```
250000007```

# 题解

## 作者：Mivik (赞：20)

[欢迎到我的博客查看](https://mivik.gitee.io/2020/solution/mivik-string-contest-writing/)

## Subtask 1

直接枚举 + 后缀全家桶暴力即可。

## Subtask 2 & 3

首先我们先简单转化一下题面，变为统计长度为 $n$，字符集大小为 $m$ 的所有字符串，每一个字符串的本质不同子串个数之和，记其为 $S(n,m)$。

善于找规律的同学应该能发现当 $n$ 固定的时候 $S(n,m)$ 是关于 $m$ 的一个 $n$ 次多项式。于是我们可以先用上面的暴力对于每一个 $n$ 求出 $m=1\sim (n+1)$ 时的值，然后插值得出多项式即可。

## 满分做法

我们发现 $n=20$ 时我们需要求出 $m=1\sim 21$ 时的值，但这个东西是完全没法在考试时限内算出来的（话说有没有少爷机跑出来了啊（雾））。有经验的同学应该能注意到 $n=20$ 暗示了我们这道题的时间复杂度可能是 $O(2^n)$ （？？？），于是我们开始思考。

反向思考，我们考虑每一个长度小于等于 $n$ 且字符集大小为 $m$ 的字符串被多少个长度为 $n$，字符集大小为 $m$ 的字符串包含了。显然枚举这小的子字符串也是要超时的，不过我们考虑到对于一些子字符串，包含它们的指定字符串数量是相同的。更具体的，如果 $w$ 是一个字符串，我们令 $c_w(x)$ 为关于 $x$ 的一个函数，它的第 $i$ 项为系数为 1 当且仅当 $w$ 有一个长度为 $i$ 的周期（我们规定所有字符串都有一个长度为 0 的周期）；否则这一项系数为 0。令 $e_{w,i}$ 为长度为 $i$，字符集为 $m$ 的包含 $w$ 的字符串数量，然后另 $E_w(x)$ 为它关于 $i$ 的普通生成函数。有一个结论：
$$
E_w(x)=\frac{x^{|w|}}{(1-mx)(x^{|w|}+(1-mx)c_w(x))}
$$
这个的证明可以参看 [本次考试 T4 的题解](https://mivik.blog.luogu.org/mivik-string-open-contest-solution-title)。不过有同学要问了，这道题模数 $1e9+7$ 怎么做求逆？$MTT$ 吗？~~但由于 $n$ 只有 20，所以我们直接暴力乘法就好了。~~

然后我们考虑 $O(2^n)$ 枚举所有的 $c_w(x)$，然后算出 $E_w(x)$ 再乘上有多少个字符串 $w$ 的 $c_w(x)$ 为当前枚举的这个东西。我们现在考虑对于一个 $c_w(x)$ 怎么求出有多少个 $w$ 的 $c_w(x)$ 为当前枚举的值。形式化的，对于每一个 $i\in [0,L-1]$，我们知道一个字符串是否有长度为 $i$ 的周期，现在我们要求出满足条件的长度为 $L$ 的字符串个数。我们用二进制数 $v$ 代表这个 $c_w(x)$（因为系数只有 0 和 1），然后记 $f_v$ 为上面那个我们要求的值。

考虑容斥。我们先不考虑 `不能有长度为 $x$ 的周期` 这个条件，我们只考虑有指定的一些周期的字符串共有多少个，记为 $S_v$。这个可以用并查集简单地做到 $O(n^2)$，也没必要继续优化了（$n$ 才 20 啊喂）。具体地说，如果我们用并查集得到了有这些周期的字符串被分割为了 $K$ 个字符必须相同的下标集合，然后就有 $S_v=m^K$。

然后运用容斥定理，我们对于每一个 $v$，得到它的 $f_v$ 就应该是：
$$
f_v=S_v-\sum_{j|i\sub j}f_j
$$
然后我们就可以插出多项式从而做出这道题了，不过由于 $n$ 并不是很大所以直接交这个打表程序上去也是可以通过的。时间复杂度 $O(3^n\cdot n^2\log n)$，$\log$ 是多项式求逆的复杂度。

注意到长度为 $n$ 的合法（即 $f_v$ 不为 0）的 $v$ 的数量远小于 $2^n$，下表给出了对于每一个 $n$ 合法的 $v$ 数量（注意这个数量是和 $m$ 无关的，当然 $m=1$ 除外，证明见 `Leo J. Guibas and Andrew M. Odlyzko. Periods in strings. J. of Combinatorial Theory series A, 30:19–42, 1981.` 的 Section 5 Theorem 5.1），具体详见 [OEIS A005434](http://oeis.org/A005434)：

| n    | 数量 |
| ---- | ---- |
| 1    | 1    |
| 2    | 2    |
| 3    | 3    |
| 4    | 4    |
| 5    | 6    |
| ...  | ...  |
| 20   | 116  |

所以最后时间复杂度应该是 $O(\min\left\{A005434(n)\cdot 2^n,3^n\right\}\cdot n^2\log n)$ 的，实际常数很小。

注：关于上面最开始提到的 $S(n,m)$ 是关于 $m$ 的多项式一点，从上面 $f_v$ 的推导其实可以看出。

[代码](https://paste.ubuntu.com/p/BbMRk3jGpY/)

运行代码需要用到的 [mivik.h](https://mivik.gitee.io/mivik.h)

---

## 作者：Huasushis (赞：11)

[此处食用效果更佳](https://blog.huasushis.cn/2023/P1316%20Mivik%20%E5%86%99%E4%B9%A6%20%E9%A2%98%E8%A7%A3/)

# 前情提要

[洛谷 P1316](https://www.luogu.com.cn/problem/P1316)

标准题解实在是过于复杂，但是这道题可以用容斥来做。由于很少做容斥的题，题解看了一个下午才看懂，于是便准备讲一个更清楚的（新手向，如十分累赘，请大佬勿喷）。

# 题目分析

总的情况数已知，这道题实际上相当于求解每个字符串的不同子串的个数和。

那么这道题为什么能用容斥呢？我们考虑一个确定的字符串，长度为 $x$，考虑其贡献，就是包含这个字符串的文章的个数。那么怎么求呢？我们考虑其出现在第一位，第二位，一直到 $n - x + 1$ 位。接着我们就会发现可能会出现重复，比如在一个字符串中出现两次、三次……这时如果还不知道怎么对一个字符串进行容斥的请先了解请~~再次学习小学奥数~~访问 [oi wiki](oi-wiki.org)。

但是一个一个枚举子串是不可能的，我们发现，有一些子串性质是一样的。就比如一种出现方式在很多子串中都有贡献，那此时我们就有了新的思路，我们先枚举子串的长度 $x$，然后去枚举一个子串在哪些位置出现（就是子串第一个字符的位置），记为 $S$，从 $1$ 到 $2 ^ {n - x + 1} - 1$，代表哪些出现在哪些位置。此时一个满足这种出现方式的子串的贡献即为 $(-1) ^ {\rm{popcount}(S) + 1}$。

那么有多少种子串能像这样的格式重复出现呢？我们发现在文章中这样的子串可能会有重叠，于是我们使用一个并查集来维护子串中每一位是否应该与另一位上的字符相同，相同的就连在一起了，统计一个子串中能自由选择的有 $a$ 块，然后加上文章中不会被覆盖的位置有 $b$ 个，也就是说相当于有 $m^{a + b}$ 种选择，于是我们就求出了这种情况的方案数，贡献即为 $(-1) ^ {\rm{popcount}(S) + 1} \times m^{a + b}$。统计过程可以用位运算优化一下，详情见代码。

## 代码
 
```cpp
#include <bits/stdc++.h>
#define mod 1000000007ll
using namespace std;
using ll = long long;
int n;
ll m;
ll qp(ll x, ll y) {
	ll ans = 1;
	while (y) {
		if (y & 1) ans = ans * x % mod;
		y >>= 1;
		x = x * x % mod;
	}
	return ans;
}
ll ans;
int fa[25];
int getfa(int x) {
	return x == fa[x] ? x : fa[x] = getfa(fa[x]);
}
void sol(int x) {
	int a = (1 << (n - x + 1)), b = (1 << x) - 1; //a 是枚举出现位置，b 相当于一个掩膜
	for (int i = 1; i < a; ++i) {
		int c = 0, tot = 0;
		for (int j = 0; j < x; ++j) fa[j] = j;
		for (int j = 0; j < n; ++j) {
			c = (c << 1) | ((i >> j) & 1); //存储最近 x 位的情况
			c &= b;
			if (!c) {
				++tot;   //没有被其它字符串覆盖
			} else {
				int t = c - (c & -c), tmp = getfa(__builtin_ctz(c)); //合并应该相同的字符
				while (t) {
					fa[getfa(__builtin_ctz(t))] = tmp;
					t -= t & -t;
				}
			}
		}
		for (int j = 0; j < x; ++j) tot += (j == fa[j]); //加上不同的数量
		ll tmp = qp(m, tot);
		if (__builtin_parity(i)) { //出现奇数次加，偶数次减，容斥
			ans = (ans + tmp) % mod;
		} else {
			ans = (ans - tmp + mod) % mod;
		}
	}
}
int main() {
	scanf("%d%lld", &n, &m);
	for (int i = 1; i <= n; ++i) sol(i);
	printf("%lld", ans * qp(qp(m, n), mod - 2) % mod); //最后除以总的方案数就是期望
	return 0;
}
```
 

# 后记

这个容斥应该算是很经典的，非常适合像我一样的组合蒟蒻食用。

---

## 作者：7KByte (赞：8)

我认为出题人想麻烦了。

我们考虑计算一个串的答案，所有子串数是 $\dfrac{n(n + 1)}{2}$，但是会存在一些本质相同的串被重复计算，所以我们考虑容斥使得每个本质相同的串只出现一次。

具体方法是枚举起点集合 $S$，其中 $x\in S$ 表示**原串的一个子串**多次出现的**左端点**集合，然后长度相同的子串本质上是相同的，可以一起容斥。

时间复杂度是 $\mathcal{O}(n^22^n)$，实际效率在 $n=24$ 时只用 $3s$，感觉更像大常数的 $n2^n$，更准确的上界不会证明。

```cpp
#define M 1050000
int n, m, ans, bt[M], mt[M], fa[26], pw[26];
int get(int x){return fa[x] == x ? x : fa[x] = get(fa[x]);}
void calc(int x){
	int s = n - x + 1, o = (1 << x) - 1, w = (1 << s) - 1;
	rp(i, w){
		int c = 0, k = 0;
		rep(j, 0, x - 1)fa[j] = j;
		rep(j, 0, n - 1){
			c = (c << 1) | (1 & (i >> j)), c &= o;
			if(c){
				int p = get(mt[c & -c]), t = c - (c & -c); 
				for(; t; t -= t & -t)fa[get(mt[t & -t])] = p;
			}
			else k++;
		}
		rep(j, 0, x - 1)k += fa[j] == j;
		if(bt[i])ad(ans, pw[k]);
		else su(ans, pw[k]);
	}
}
int main() {
	read(n, m);
	int w = (1 << n) - 1;
	rep(i, 0, n)mt[1 << i] = i;
	pw[0] = 1; rp(i, n)pw[i] = pw[i - 1] * 1LL * m % P;
	rp(i, w)bt[i] = (i & 1) ^ (bt[i >> 1]);
	rp(i, n)calc(i);
	int inv = Pow(m, P - 2);
	rp(i, n)ans = ans * 1LL * inv % P;
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：Reunite (赞：4)

入门容斥。

## 一
----

可以发现，不同长度的子串，其贡献是独立的，所以可以先枚举子串长度，然后考虑对于长度为 $len$ 的子串对答案的贡献。

因为 $n$ 很小，这个 $20$ 看起来就很像状压的样子，不过这里只需要对于每个 $len$，二进制枚举其**一定**出现的串头位置。因为直接做的话会有重复，所以考虑容斥。

现在问题转化为，已知在哪些位置一定是我们钦定出现的串头（也就是压状态的 $s$），和枚举的子串长度 $len$，对答案有哪些贡献。直接状压加并查集，得到没有约束的位置有 $cnt$ 个，则贡献为：

$$(-1)^{popcount(s)}\times m^{cnt}$$

时间复杂度为 $O(n^22^n\alpha(n))$，因为常数小所以跑的飞快。当然我觉得精细实现的话可以做到 $O(n \log_2{n}2^n\alpha(n))$。

## 二
---
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define int long long
#define mod 1000000007
using namespace std;

int n,m;
ll pw[25],ans;
int fa[25];

int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}

inline void work(int len){
	for(int s=1;s<(1<<(n-len+1));s++){
		for(int i=1;i<=len;i++) fa[i]=i;
		int a[25],tt=0,mp[25]={0};
		for(int i=1;i<=n;i++)
			if(s&(1<<(i-1))) a[++tt]=i;
		for(int i=1;i<=tt;i++)
			for(int j=1;j<=len;j++) mp[a[i]+j-1]|=(1<<j);
		int ss=0;
		for(int i=1;i<=n;i++){
			int xx[25]={0},mm=0;
			for(int j=1;j<=len;j++)
				if(mp[i]&(1<<j)) xx[++mm]=j;
			for(int j=2;j<=mm;j++){
				int u=Find(xx[1]),v=Find(xx[j]);
				if(u!=v) fa[u]=v;
			}
		}
		for(int i=1;i<=n;i++) ss+=(mp[i]==0);
		for(int i=1;i<=len;i++) ss+=(Find(i)==i);
		ans=(ans+pw[ss]*(tt&1?1:-1)+mod)%mod;
	}
}

inline ll calc(ll x,int k){
	ll tmp=1;
	while(k){
		if(k&1) tmp=tmp*x%mod;
		x=x*x%mod;
		k>>=1;
	}
	return tmp;
}

signed main(){
	scanf("%d%d",&n,&m);
	pw[0]=1;
	for(int i=1;i<=n;i++) pw[i]=pw[i-1]*m%mod;
	for(int i=1;i<=n;i++) work(i);
	printf("%lld\n",ans*calc(calc(m,n),mod-2)%mod);

	return 0;
}

```

---

## 作者：rainygame (赞：0)

很神的容斥题！

假设有一个长度为 $x$ 的子串 $s$，假设它在字符串中出现了 $c$ 次，出现的开头位置集合为 $S$（显然有 $\lvert S\rvert=c$），那么它对答案的贡献系数为 $(-1)^{\text{popc(S)+1}}$。

如何计算出现的方案数？首先对于没有被 $s$ 碰到的点，可以取 $m$ 种字符。对于被 $s$ 碰到的点，如果被碰到多次，那么这两个位置就必须相同，用并查集维护。最后贡献即为 $m^a$，其中 $a$ 表示连通块个数。

最后除以 $m^n$ 计算期望即可。由于 $\sum\limits_{i=1}^n 2^i < 2^{n+1}$，所以复杂度为 $O(n^22^n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD(1e9+7);

int n, m, ans; int f[21], c[21];
int find(int x){return f[x] == x ? x : f[x] = find(f[x]);}
int qpow(int x, int k=MOD-2){int res(1); for (; k; k>>=1, (x*=x)%=MOD) if (k&1) (res*=x)%=MOD; return res;}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;
    for (int x(1); x<=n; ++x){
        for (int i(1); i<(1<<(n-x+1)); ++i){
            memset(c, -1, sizeof(c)); iota(f, f+x+1, 0);
            for (int j(0); j<n-x+1; ++j) if (i>>j&1){
                for (int k(0); k<x; ++k) if (~c[j+k]) f[find(k)] = find(c[j+k]); else c[j+k] = k;
            }
            int nw(0); for (int j(0); j<x; ++j) nw += f[j] == j; for (int j(0); j<n; ++j) nw += c[j] == -1; nw = qpow(m, nw);
            (ans += __builtin_parity(i) ? nw : MOD-nw) %= MOD;
        }
    }
    cout << ans*qpow(qpow(m, n))%MOD;

    return 0;
}
```

---

