# [ABC290F] Maximum Diameter

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc290/tasks/abc290_f

長さ $ N $ の正整数列 $ X=(X_1,X_2\ldots,X_N) $ に対して、$ f(X) $ を以下のように定めます。

- $ N $ 頂点の木であって、$ i\ (1\ \leq\ i\ \leq\ N) $ 番目の頂点の次数が $ X_i $ であるようなものを良い木と呼ぶ。 良い木が存在するならば、$ f(X) $ は良い木の直径の最大値。良い木が存在しないならば、$ f(X)=0 $。
 
ただし、木の $ 2 $ 頂点の間の距離は一方から他方へ移動するときに用いる辺の本数の最小値であり、 木の直径は任意の $ 2 $ 頂点の間の距離の最大値として定められます。

長さ $ N $ の正整数列 $ X $ としてあり得るもの全てに対する $ f(X) $ の総和を $ 998244353 $ で割った余りを求めてください。 なお、$ f(X) $ の総和は有限値になることが証明できます。

$ T $ 個のテストケースが与えられるので、それぞれについて答えを求めてください。

## 说明/提示

### 制約

- $ 1\leq\ T\ \leq\ 2\times\ 10^5 $
- $ 2\ \leq\ N\ \leq\ 10^6 $
- 入力は全て整数
 
### Sample Explanation 1

$ N=3 $ の場合について、 例えば、 - $ X=(1,1,1) $ のとき、次数が $ 1,1,1 $ となる $ 3 $ 頂点の木は存在しないため、$ f(X)=0 $ です。 - $ X=(2,1,1) $ のとき、良い木は以下の図のものに限られます。この木の直径は $ 2 $ であるため、$ f(X)=2 $ です。 !\[3 頂点の木\](https://img.atcoder.jp/abc290/7b4cd8233d2ee3eb307023bebaebd906.jpg) $ X=(2,1,1),(1,2,1),(1,1,2) $ のとき $ f(X)=2 $ であり、それ以外の $ X $ のとき $ f(X)=0 $ であるため、答えは $ 6 $ です。

## 样例 #1

### 输入

```
10
2
3
5
8
13
21
34
55
89
144```

### 输出

```
1
6
110
8052
9758476
421903645
377386885
881422708
120024839
351256142```

# 题解

## 作者：TKXZ133 (赞：9)

[Maximum Diameter](https://www.luogu.com.cn/problem/AT_abc290_f)

### 题目大意

定义长度为 $n$ 的序列 $a$ 的权值为：

- 所有的 $n$ 个点的第 $i$ 个点的度数为 $a_i$ 的树的直径最大值，如果不存在这样的树，其权值为 $0$。

给定 $n$，求所有长度为 $n$ 的序列的权值和。

### 思路分析

$n$ 个点的树的边数为 $n-1$，总度数为 $2n-2$，故序列 $a$ 的权值不为 $0$ 当且仅当 $\sum a=2n-2$ 且 $a_i>0$，因此我们只需要考虑这样的序列即可。

考虑如何根据给定序列构造出直径最大的树，设 $a$ 中有 $k$ 个 $1$，也就是树上有 $k$ 个叶子节点，那么我们可以将剩下的 $n-k$ 个节点全部串在一起，再在两端放上两个叶子节点，用 $n-k+2$ 个点构造出一条长 $n-k+1$ 的链，其余的叶子节点挂在链上，显然这是最优方案，直径为 $n-k+1$。

考虑计数。枚举 $k$，那么叶子节点的选择方案数为 ${n \choose k}$。而非叶子节点的度数必须大于 $1$，且有 $n-k$ 个，又因为剩余的可用度数为 $2n-2-k$，所以这个问题等价于将 $2n-2-k$ 个相同的球放在 $n-k$ 个盒子里，且每个盒子的球必须大于 $1$，由插板法易得其方案数为：

$${(2n-2-k)-2(n-k)+(n-k)-1\choose (2n-2-k)-2(n-k)}={n-3\choose k-2}$$

再算上直径产生的贡献，故我们所求式即：

$$\sum_{k=1}^n{n\choose k}{n-3\choose k-2}(n-k+1)$$

这个式子可以 $O(n)$ 计算，但这显然不够，我们需要继续化简。

我们有以下两个式子：

- 吸收恒等式：$k{n\choose k}=n{n-1\choose k-1}$

- 范德蒙德卷积：$\sum\limits_{i=0}^k{n\choose i}{m\choose k-i}={n+m\choose k}$

一式可以直接拆组合数简单证明，二式通过组合意义显然成立。

然后我们就可以通过以上两个式子对所求式进行化简了：

$$\begin{aligned}
\sum_{k=1}^n{n\choose k}{n-3\choose k-2}(n-k+1)&=
-\sum_{k=1}^n{n\choose k}{n-3\choose k-2}(k-2+1-n)\\&=
-\sum_{k=1}^n{n\choose k}{n-3\choose k-2}(k-2)+(n-1)\sum_{k=1}^n{n\choose k}{n-3\choose k-2}\\&=
(n-1)\sum_{k=1}^n{n\choose k}{n-3\choose k-2}-(n-3)\sum_{k=1}^n{n\choose k}{n-4\choose k-3}\\&=
(n-1)\sum_{k=1}^n{n\choose k}{n-3\choose n-k-1}-(n-3)\sum_{k=1}^n{n\choose k}{n-4\choose n-k-1}\\&=
(n-1){2n-3\choose n-1}-(n-3){2n-4\choose n-3}
\end{aligned}$$

化到这样就可以 $O(1)$ 计算了，只需要 $O(n)$ 预处理组合数就行了。

### 代码

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;
const int N = 2002000, L = 2000000, mod = 998244353;
#define int long long

int fac[N], inv[N];
int T, n;

int q_pow(int a, int b){
    int res = 1;
    while (b) {
        if (b & 1) res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

int C(int n, int m){
    if(n < m || n < 0 || m < 0) return 0;
    return fac[n] * (inv[m] * inv[n - m] % mod) % mod;
}

signed main(){
    fac[0] = 1;
    for (int i = 1; i <= L; i ++) fac[i] = fac[i - 1] * i % mod;
    inv[L] = q_pow(fac[L], mod - 2);
    for (int i = L; i >= 1; i --) inv[i - 1] = inv[i] * i % mod;
    scanf("%lld", &T);
    while (T --) {
        scanf("%lld", &n);
        int res1 = (n - 1) * C(2 * n - 3, n - 1) % mod;
        int res2 = (n - 3) * C(2 * n - 4, n - 3) % mod;
        int ans = (res1 - res2 + mod) % mod;
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：Register_int (赞：7)

好题，好题。赛时卡点切了。

首先考虑已知度数集合构造最长链。将所有度数 $>1$ 的节点与两个度数 $=1$ 的节点构成一条链，其余的叶子节点挂接在中段剩余度数上即可。可以证明构造的合法性与最优性。

接下来考虑计数部分。总度数显然为边数 $\times2$，即 $2n-2$。容易发现影响最终长度的仅有叶子节点个数，因此钦定 $k$ 个节点一定为叶子节点（度数为 $1$），其余可以直接划分。可分配的总度数为 $(2n-2)-k$ 个，而我们需要强制让每个节点都不是叶子节点（度数 $>1$），因此需要在每个节点的度数上减去 $1$，总共即减去 $n-k$，总度数为 $(2n-2)-k-(n-k)=n-2$。再根据插板法，得到总方案数为 $\dbinom nk\dbinom{n-3}{n-k-1}$，直径则为 $n-k+1$。

正式推之前，我们需要两个前置知识：

- 恒等式 $k\dbinom nk=n\dbinom{n-1}{k-1}$。
- 范德蒙德卷积 $\sum^k_i\dbinom ni\dbinom m{k-i}=\dbinom{n+m}k$。

那么，我们开始。

$$
\begin{aligned}
&\sum^n_{k=1}\dbinom nk\dbinom{n-3}{n-k-1}(n-k+1)\\
=&\sum^n_{k=1}\dbinom nk\dbinom{n-3}{n-k-1}(n-k-1+2)\\
=
&\left(\sum^n_{k=1}\dbinom nk\dbinom{n-3}{n-k-1}(n-k-1)\right)+2\sum^n_{k=1}\dbinom nk\dbinom{n-3}{n-k-1}\\
=&\left(\sum^n_{k=1}\dbinom nk\dbinom{n-4}{n-k-2}(n-3)\right)+2\dbinom{2n-3}{n-1}\\
=&\left((n-3)\sum^n_{k=1}\dbinom nk\dbinom{n-4}{n-k-2}\right)+2\dbinom{2n-3}{n-1}\\
=&\ (n-3)\dbinom{2n-4}{n-2}+2\dbinom{2n-3}{n-1}
\end{aligned}
$$

预处理组合数即可，时间复杂度 $O(n+T)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

const int MAXN = 2e6 + 10;
const int mod = 998244353;

inline 
ll qpow(ll b, ll p) {
    ll res = 1;
    while (p) {
        if (p & 1) res = res * b % mod;
        b = b * b % mod, p >>= 1;
    }
    return res;
}

ll fac[MAXN], ifac[MAXN];

inline 
void init(int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = qpow(fac[n], mod - 2);
	for (int i = n; i; i--) ifac[i - 1] = ifac[i] * i % mod;
}

inline 
ll c(ll n, ll m) {
	if (n < 0 || m < 0 || n < m) return 0;
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int t, n; ll f[MAXN], ans;

int main() {
	for (init(2e6), scanf("%d", &t); t--;) {
		scanf("%d", &n);
		printf("%lld\n", ((n - 3) * c(2 * n - 4, n - 2) + 2 * c(2 * n - 3, n - 1)) % mod);
	}
}
```

---

## 作者：do_while_true (赞：3)

没动脑子就 gf 一路写下来了......实际上就是把插板法的 gf 写了一下/zk

---

首先考虑一下一个 $X$ 合法是什么情况，那就是总和是 $2n-2$ 并且保证 $0<X_i<n$。

证明就考虑贪心构造一下，每个 $1$ 挂在一个 $\geq 2$ 的上面，不断挂使得最后只剩下两个 $1$ 和一堆 $2$，再把它们串起来就行。

然后就能发现，这样也同时构造出了最大的直径（容易发现这是上界），那就是 度数 $\geq 2$ 的个数 + 1．

然后枚举度数为 1 的有 $k$ 个，此时答案为 $n-k+1$，先仅考虑度数 $\geq 2$ 内部的顺序，最后乘上 $\binom{n}{k}$ 以插入度数为 1 的。这样要算的方案数就是：

$$
\begin{aligned}
&[z^{2n-2-k}](z^2+z^3+\cdots+z^{n-1})^{n-k}
\\
=&[z^{2n-2-k-2(n-k)}](1+z+z^2+\cdots+z^{n-3})^{n-k}
\\
=&[z^{k-2}](1+z+z^2+\cdots+z^{n-3})^{n-k}
\end{aligned}
$$

由于 $k\leq n-1$，那么 $n-3\geq k-2$，所以：

$$
\begin{aligned}
=&[z^{k-2}](1+z+z^2+z^3+\cdots)^{n-k}
\\
=&[z^{k-2}]\left(\frac{1}{1-z}\right)^{n-k}
\end{aligned}
$$

已经化到我们熟悉的形式了，根据广义二项式定理它的系数就是 $\binom{n-k+k-2-1}{k-2}=\binom{n-3}{k-2}$，最后答案的推导也是平凡的。

$$
\begin{aligned}
&\sum_{k=2}^{n-1}\binom{n}{k}\binom{n-3}{k-2}(n-k+1)
\\
=&(n-1)\sum_{k=2}^{n-1}\binom{n}{k}\binom{n-3}{k-2}-\sum_{k=2}^{n-1}\binom{n}{k}\binom{n-3}{k-2}(k-2)
\\
=&(n-1)\sum_{k=2}^{n-1}\binom{n}{n-k}\binom{n-3}{k-2}-(n-3)\sum_{k=3}^{n-1}\binom{n}{n-k}\binom{n-4}{k-3}
\\
=&(n-1)\binom{2n-3}{n-2}-(n-3)\binom{2n-4}{n-3}
\end{aligned}
$$

倒数第二步同时用了对称恒等式和吸收恒等式，最后一步则是范德蒙德卷积。

Code：https://atcoder.jp/contests/abc290/submissions/39046485

---

## 作者：TernaryTree (赞：2)

好题力荐！！！！！！！！111

考虑数列中 $1$ 的数量即为叶子个数 $k$，而考虑一条链，两端一定是叶子，剩下的叶子直接挂在链上，类似一条蜈蚣。所以我们可以得到在直径上的点的最大数量是 $n-k+2$，于是直径就是 $n-k+1$。

因为树有 $n-1$ 条边，每条边 $2$ 个端点，所以能构造出树的度数序列一定满足 $\sum X_i=2n-2$。于是我们使用插板法可以得到这样一个式子：

$$ans=\sum_{k=1}^n\binom{n}{k}\binom{n-3}{n-k-1}(n-k+1)$$

考虑把后面那个东西拆出来，得到

$$\sum_{k=1}^n\binom{n}{k}\binom{n-3}{n-k-1}(n-k-1)+2\sum_{k=1}^n\binom{n}{k}\binom{n-3}{n-k-1}$$

也就是

$$(n-3)\sum_{k=1}^n\binom{n}{k}\binom{n-4}{n-k-2}+2\sum_{k=1}^n\binom{n}{k}\binom{n-3}{n-k-1}$$

显然的范德蒙德卷积，于是得到最终答案

$$(n-3)\binom{2n-4}{n-2}+2\binom{2n-3}{n-1}$$

预处理阶乘及逆元，复杂度 $\Theta(n+q)$。

---

## 作者：王熙文 (赞：1)

## 思路

首先有一个重要结论：若给定一棵树每个节点的度数 $d$，则树的最长直径为 $n-1-\sum\limits_{i=1}^n \max(d_i-2,0)$。

证明：

首先证明最长直径不会更大。最长直径即为 $n-1$ 减去不在直径上的边。将点分成两部分：在直径上的点和不在直径上的点。若有一个在直径的点 $d_i\ge 2$，则一定有 $d_i-2$ 条不在直径上的边。若有一个不在直径上的点 $d_i\ge2$，则一定有 $d_i-1$ 条（注意，这里不是 $d_i$，因为不能算上来自直径那里的边，那条边已经算过了）不在直径上的点。因此至少有 $\sum\limits_{i=1}^n \max(d_i-2,0)$ 条不在直径上的点。

接下来考虑构造一个直径为 $n-1-\sum\limits_{i=1}^n \max(d_i-2,0)$ 的树。由上文可知，想要达到这个数，就得让 $d_i\ge 2$ 的点都在直径上。那么它们伸出来的边就得让 $d_i=1$ 的点填上。设 $d_i=1$ 的点个数为 $cnt$，则由度数总和为 $2n-2$（每个边贡献两个度数）可得 $\sum\limits_{i=1}^n \max(d_i-2,0)=2n-2-cnt-2(n-cnt)=cnt-2$。将 $d_i=1$ 中的两个点放到直径两边堵住，剩下的去填直径上 $d_i \ge 2$ 伸出来的边，正好用完，所以这样构造是可行的。而且也达到了最大值。

接下来，可以发现上面式子的值只与 $d_i=1$ 的个数有关，因此枚举 $d_i=1$ 的个数 $cnt$。那么 $n-1-\sum\limits_{i=1}^n \max(d_i-2,0)=n-1-(cnt-2)=n+1-cnt$。那这样的序列有多少个呢？首先 $d_i=1$ 的位置一共有 $C_n^i$ 个。接下来的问题是：将剩下的度数总和 $2n-2-cnt$ 拆成 $n-cnt$ 个在 $[2,n-1]$ 之间的数，求方案数。

先将每一个数减去 $1$，则总和减去了 $n-cnt$，问题转化为：将总和 $n-2$ 拆成 $n-cnt$ 个在 $[1,n-2]$ 之间的数，求方案数。此时可以发现值域的上界已经没有用了。那么这个问题可以用插板法解决。一共有 $n-3$ 个空，要插 $n-cnt-1$ 个板子，方案数即为 $C_{n-3}^{n-cnt-1}$。

综上，答案即为

$$\sum_{i=2}^{n-1} (n+1-i)C_n^iC_{n-3}^{n-i-1}$$

上面将 $cnt$ 替换成 $i$ 了。

注意到后面的东西似乎可以用范德蒙德卷积做，但是因为乘了一个 $n+1-i$ 所以无法直接做。考虑拆开：

$$(n+1)\sum_{i=2}^{n-1} C_n^i C_{n-3}^{n-i-1}-\sum_{i=2}^{n-1} i C_n^i C_{n-3}^{n-i-1}$$

$$=(n+1)C_{2n-3}^{n-1}-\sum_{i=2}^{n-1} i \dfrac{n!}{(n-i)!i!} \cdot C_{n-3}^{n-i-1}$$

$$=(n+1)C_{2n-3}^{n-1}-n \sum_{i=2}^{n-1} \dfrac{(n-1)!}{(n-i)!(i-1)!} \cdot C_{n-3}^{n-i-1}$$

$$=(n+1)C_{2n-3}^{n-1}-n\sum_{i=2}^{n-1} C_{n-1}^{i-1} C_{n-3}^{n-i-1}$$

$$=(n+1)C_{2n-3}^{n-1} - nC_{2n-4}^{n-2}$$

直接求即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mod 998244353
int qpow(int a,int b)
{
	int ans=1;
	while(b)
	{
		if(b&1) ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int jc[2000010],invjc[2000010];
int C(int n,int m)
{
	if(n<m || n<0 || m<0) return 0;
	return jc[n]*invjc[n-m]%mod*invjc[m]%mod;
}
int n;
signed main()
{
	jc[0]=1; for(int i=1; i<=2e6; ++i) jc[i]=jc[i-1]*i%mod;
	invjc[(int)2e6]=qpow(jc[(int)2e6],mod-2); for(int i=2e6-1; i>=0; --i) invjc[i]=invjc[i+1]*(i+1)%mod;
	int t; cin>>t; while(t--)
	{
		cin>>n; cout<<((n+1)*C(2*n-3,n-1)%mod-n*C(2*n-4,n-2)%mod+mod)%mod<<'\n';
	}
	return 0;
}
```

---

## 作者：_lfe (赞：0)

# Maximum Diameter
[Maximum Diameter](https://www.luogu.com.cn/problem/AT_abc290_f)
## 题意
求所有长度为 $n$ 的正整数序列的权值和。  
其中序列 $a$ 的权值定义为所有满足 $deg_i = a_i$ 的树的直径最大值，若没有满足的树则权值为 $0$。
## Solution
首先考虑什么样的序列会对答案产生贡献（即能构造出合法的树）。  
不难发现，一个序列能构造出合法的树，当且仅当 $\sum a_i = 2 (n-1)$ 且 $\forall a_i > 0$。

接下来我们考虑对于一个合法的序列，构造出的树的直径最大值是多少。
由于序列已经合法，所以我们只要保证度数满足，每个点具体连向谁并不重要。

于是我们考虑先构造出一条最长的链作为直径。  
进一步地，我们考虑什么样的点可以出现在这条链上。

我们发现，不考虑链的端点，只要一个点的度数大于 $1$，我们都一定可以将它插进链上的某一个位置，又因为要使直径最大，所以我们将所有度数大于 $1$ 的点都放在链上，再算上两个端点，此时直径长度为 $\sum [deg_i>1] + 1$。

到这里，我们发现只需枚举有多少个点的度数大于 $1$，并算出这样的序列有多少个，就能得到答案。

具体地，我们一共有 $2(n-1)$ 的度数可以分配，首先，我们会给每个点分配一个度数，因为每个点度数至少为 $1$，还剩下 $n-2$ 个度数可以自由分配。  
接下来，设有 $i$ 个点的度数大于 $1$，则我们需要从 $n$ 个点中先选出 $i$ 个度数大于 $1$ 的点，方案数为 $\binom{n}{i}$。  
然后我们将 $n-2$ 个度数分给这 $i$ 个点，且每个点至少分 $1$ 个，方案数为球盒模型的 $\binom{n-1}{m-1}$，在这里是 $\binom{n-3}{i-1}$。  
然后我们再将方案数乘上直径长度 $i+1$ 就得到了一个 $i$ 对答案的贡献。

形式化地：
$$
ans = \sum\limits_{i=1}^{n-2} \binom{n}{i} \binom{n-3}{i-1} (i+1)
$$
这里 $n = 2$ 需要特判，我的理解是当没有球没有盒子的时候球盒模型会错掉？

然而这里的时间复杂度是 $O(Tn)$ 的，需要我们进一步优化。

这里需要一点点组合数学的知识：
- **吸收恒等式：**
  $$k\binom{n}{k} = n\binom{n-1}{k-1}$$

- **范德蒙德卷积：**
  $$\sum_{i=0}^{k} \binom{n}{i} \binom{m}{k-i} = \binom{n+m}{k}$$

于是我们观察刚刚的式子，注意力惊人地发现它和范德蒙德卷积的形式较为相似，唯一不一样的就是后面 $i+1$ 的系数。

所以我们尝试将 $i+1$ 处理掉。  
具体地，我们发现，$i-1$ 这个系数可以通过 $\binom{n-3}{i-1}$ 用吸收恒等式消去。  
所以我们考虑从 $i+1$ 中分离出 $i-1$，即 $i+1 = (i-1) + 2$。


令 $k = n-2$，当组合数中出现负数时，我们令其值为 $0$，于是求和下界可以从 $i=0$ 开始。  
为了清晰一点所以每一步都慢慢推的，有一点点长。

$$
\begin{align*}
ans &= \sum\limits_{i=0}^{n-2} \binom{n}{i} \binom{n-3}{i-1} (i+1)\\
&= \sum\limits_{i=0}^{n-2} \binom{n}{i} \binom{n-3}{i-1} (i-1+2)\\
&= \sum\limits_{i=0}^{n-2} (i+1)\binom{n}{i} \binom{n-3}{i-1} + 2\sum\limits_{i=0}^{n-2} \binom{n}{i} \binom{n-3}{i-1}\\
&= \sum\limits_{i=0}^{n-2} (i+1)\binom{n}{i} \binom{n-3}{i-1} + 2\sum\limits_{i=0}^{n-2} \binom{n}{i} \binom{n-3}{(n-3)-(i-1)}\\
&= \sum\limits_{i=0}^{n-2} (i+1)\binom{n}{i} \binom{n-3}{i-1} + 2\sum\limits_{i=0}^{k} \binom{n}{i} \binom{n-3}{k-i}\\
&= \sum\limits_{i=0}^{n-2} (i+1)\binom{n}{i} \binom{n-3}{i-1} + 2\binom{2n-3}{k}\\
&= \sum\limits_{i=0}^{n-2} (i+1)\binom{n-3}{i-1} \binom{n}{i} + 2\binom{2n-3}{k}\\
&= \sum\limits_{i=0}^{n-2} (n-3)\binom{n-4}{i-2} \binom{n}{i} + 2\binom{2n-3}{k}\\
&= (n-3)\sum\limits_{i=0}^{n-2} \binom{n-4}{(n-4)-(i-2)} \binom{n}{i} + 2\binom{2n-3}{k}\\
&= (n-3)\sum\limits_{i=0}^{k} \binom{n-4}{k-i} \binom{n}{i} + 2\binom{2n-3}{k}\\
&= (n-3)\binom{2n-4}{k} + 2\binom{2n-3}{k}\\
&= (n-3)\binom{2n-4}{n-2} + 2\binom{2n-3}{n-2}\\
\end{align*}
$$

至此，我们发现拆完后的两个部分都能通过范德蒙德卷积 $O(1)$ 求出，本题得解，总复杂度 $O(n+T)$。

---

## 作者：strcmp (赞：0)

并不很难的计数题，用来练手很舒服。

首先 $n$ 个结点的树，度数和必定为 $2n - 2$，所以我们只考虑总和恰好为 $2n - 2$ 的序列。

同样，当 $n \ne 1$ 的时候至少有两个点度数为 $1$，根据鸽巢原理易得。

考虑我们如何生成直径，直径是一条链，那么结点数为 $k$ 的链有 $2$ 个点度数为 $1$，$k - 2$ 个点度数为 $2$（只保留链的边的话）。

对于这类计数题，我们不可避免的要先考虑 $f(X)$ 到底是什么。

于是我们肯定是先考虑 $X$ 中度数恰好等于 $1$ 的那些点，拉出来两个点钦定它们是链的头尾。假设度数为 $1$ 的点有 $k$ 个。

然后再考虑剩下 $n - k$ 个度数大于 $1$ 的点，把它们全部钦定为链的中间部分，再把 $k - 2$ 个叶子接到度数没用完的点上。

显然只要度数和是 $2n - 2$，那么我们的构造必然能满足要求。

于是设 $X$ 有 $k$ 个 $1$，则 $f(X) = n - k + 1$。

如果直接拆贡献枚举 $k$，后面相当于计数 $n - k$ 个数总和为 $2n - k - 2$，且每个数都必须 $\ge 2$。

这是经典插板法问题，设 $y = n - k,\,x = 2n - k - 2$，则答案为：

$$
\binom{x - 2y + y - 1}{x - 2y} = \binom{x - y - 1}{x - 2y} = \binom{n - 3}{k - 2}
$$

那么答案为：

$$
\sum (n - k + 1)\binom{n}{k}\binom{n - 3}{k - 2} = \sum (n - k + 1)\binom{n}{k}\binom{n - 3}{n - k - 1}
$$

时间复杂度 $\Theta(Tn)$，还不太行。

发现很可写成范德蒙德卷积。

先把平凡的乘积分离。

$$
\begin{aligned}
& \sum (n - k + 1)\binom{n}{k}\binom{n - 3}{n - k - 1}\\
& = \sum (n - k - 1)\binom{n}{k}\binom{n - 3}{n - k - 1} + 2 \left( \sum \binom{n}{k}\binom{n - 3}{n - k - 1}\right)\\
& = (n - 3)\left(\sum \binom{n}{k}\binom{n - 4}{n - k - 2}\right) +  2 \left( \sum \binom{n}{k}\binom{n - 3}{n - k - 1}\right)
\end{aligned}
$$

范德蒙德卷积。

$$
(n - 3)\binom{2n - 4}{n - 2} + 2\binom{2n - 3}{n - 1}
$$

直接做即可，时间复杂度 $\Theta(T + n)$，可以通过。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
#define mid (l + r >> 1)
using namespace std;
typedef long long int ll;
using ull = unsigned long long int;
using pii = pair<int, int>;
constexpr int maxn = 2e6 + 10, mx = 2e6 + 5, mod = 998244353;
inline ll ksm(ll a, int b = mod - 2) { ll ls = 1; while (b) (b & 1) && (ls = ls * a % mod), a = a * a % mod, b >>= 1; return ls; }
int T, n; ll fc[maxn], iv[maxn];
inline ll C(int n, int m) { return fc[n] * iv[m] % mod * iv[n - m] % mod; }
int main() {
	fc[0] = iv[0] = 1; 
	rep(i, 1, mx) fc[i] = fc[i - 1] * i % mod; iv[mx] = ksm(fc[mx]);
	per(i, mx - 1, 1) iv[i] = iv[i + 1] * (i + 1) % mod;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		printf("%lld\n", ((C(2 * n - 4, n - 2) * (n - 3) % mod + mod) % mod + C(2 * n - 3, n - 1) * 2 % mod) % mod);
	}
	return 0;
}
```

---

## 作者：xuyiyang (赞：0)

### [[ABC290F] Maximum Diameter](https://www.luogu.com.cn/problem/AT_abc290_f)
### Solution
首先 $n$ 个节点二叉树的度数和是 $2n-2$ 的。证明显然。所以题目中的“所有”其实就是诈骗。然后开始考虑对一个序列 $X$ 构造最长直径，发现当两叶子为直径两端，中间为一条链，其余叶子挂链上即可。$\\$
此直径的最长性是显然的，来证明合法性。对于非叶子节点 $u$，则它一定不是链的两端，在周围挂 $d_u-2$ 个叶子节点即可。令叶子节点数为 $c$，$\sum (d_u-2)+c=2n-2$，则说明一定能构造出。$\\$
于是我们枚举叶子节点个数，对于剩余节点插板为 $\binom{2n-2-k-(n-k)-1}{n-k-1}=\binom{n-3}{n-k-1}$ 则答案为：
$$\sum \limits _ {k = 0}\binom{n}{k}\binom{n-3}{n-k-1}(n-k+1)$$
然后我们动用蒙德范德卷积：
$$\sum \limits _ {k=0}\binom{r}{k}\binom{s}{n-k}=\binom{r+s}{n}$$
证明考虑组合意义，枚举在 $r$ 个小球中选 $k$ 个再在 另 $s$ 个小球中选 $n-k$ 个就是在 $r+s$ 个小球中选 $n$ 个。
$$\begin{aligned}\sum \limits _ {k = 0}\binom{n}{k}\binom{n-3}{n-k-1}(n-k-1) &= \sum \limits _{k=0}\binom{n}{k}\binom{n-3}{n-k-1}(n-k-1)+2\sum \limits _ {k=0}\binom{n}{k}\binom{n-3}{n-k-1} \\ &= (n-3)\sum \limits _ {k=0}\binom{n}{k}\binom{n-4}{n-k-2}+2\sum \limits _ {k=0}\binom{n}{k}\binom{n-3}{n-k-1} \\ &= (n-3)\binom{2n-4}{n-2}+2\binom{2n-3}{n-1}\end{aligned}$$
其中第一步的拆项是为了构成吸收恒等式来去掉第三个因子。然后就可以 $\mathcal O(1)$ 回答了。
```cpp
int fact[N << 1], inv[N << 1];

int binom(int x, int y) {
	if (x < y) return 0;
	return (LL)fact[x] * inv[y] % mod * inv[x - y] % mod;
}

void mian() {
	fact[0] = inv[0] = inv[1] = 1;
	for (int i = 2; i < N; i ++ ) inv[i] = (LL)(mod - mod / i) * inv[mod % i] % mod;
	for (int i = 1; i < N; i ++ ) {
		fact[i] = (LL)fact[i - 1] * i % mod;
		inv[i] = (LL)inv[i - 1] * inv[i] % mod;
	} 
	int T; scanf("%d", &T);
	while (T -- ) {
		int n; scanf("%d", &n);
		printf("%lld\n", ((LL)(n - 3) * binom(2 * n - 4, n - 2) % mod + 2 * binom(2 * n - 3, n - 1) % mod) % mod);
	}
}
```

---

## 作者：AzusidNya (赞：0)

### [ABC290F] Maximum Diameter

考虑如果给了一个度数序列，怎么求出它的最长直径的长度。

注意到直径其实是原树的一个子图，将这个子图单独拎出来后应该满足有两个点度数为 $1$，其它点度数等于 $2$。

那么可以将原树所有度数不小于 $2$ 的节点全部拿出来，每个节点提供两条边连成一条链，这样就一定能得到对于这个度数序列直径最长的树。

而直径的长度就是不小于 $2$ 的点的数量加上 $1$。

直接推式子。
$$
\begin{aligned}
\sum _{\sum_{i = 1} ^n a_i = 2n - 2} \left(\sum _{i = 1} ^{n} [a_i \ge 2] + 1\right)
&= \sum _{\sum_{i = 1} ^n a_i = 2n - 2} (n + 1 - \sum _{i = 1} ^{n} [a_i = 1]) \\
&= \binom {2n - 3}{n - 1}(n + 1) - \sum _{\sum_{i = 1} ^n a_i = 2n - 2} \sum _{i = 1} ^{n} [a_i = 1]
\end {aligned}
$$
前面已经 $O(1)$ 了。考虑化简后面的式子。

交换求和顺序后就变成了简单的插板法。
$$
\begin {aligned}
\sum _{\sum_{i = 1} ^n a_i = 2n - 2} \sum _{i = 1} ^{n} [a_i = 1] &= \sum _{i = 1} ^{n} \sum _{\sum_{i = 1} ^n a_i = 2n - 2} [a_i = 1] \\
&= n \sum _{\sum_{i = 1} ^{n - 1} a_i = 2n - 3} 1 \\
&= n\binom {2n - 4}{n - 2}
\end {aligned}
$$
结合起来是
$$
ans = (n + 1)\binom {2n - 3}{n - 1} - n\binom {2n - 4}{n - 2}
$$
预处理阶乘和逆元后就做完了，单次询问时间复杂度 $O(1)$。

---

## 作者：happybob (赞：0)

很厉害一个题。

先考虑对于一个固定的度数序列 $d$，答案是什么。考虑这样一个构造：选择两个度数为 $1$ 的点，然后将所有 $d_i \geq 2$ 的点与两个叶子挂成一条链，其余所有叶子挂在链上。设 $k$ 为 $\sum \limits_{i=1}^n [d_i=1]$，则答案为 $n-1-(k-2)=n-k+1$。

故我们直接枚举叶子个数，从 $2$ 到 $n-1$，然后来推式子。

$ans=\sum \limits_{i=2}^{n-1} \dbinom{n}{i}\dbinom{n-3}{n-i-1}(n-i+1)$。

这个前面是直接选 $i$ 个方案，中间是插板，后面是贡献。

于是我们得到了一个 $O(Tn)$ 的做法，还不足以通过，考虑化简。

首先把 $n+1$ 提出来。

$ans = (n+1) \sum \limits_{i=2}^{n-1} \dbinom{n}{i} \dbinom{n-3}{n-i-1} - \sum \limits_{i=2}^{n-1}\dbinom{n}{i} \dbinom{n-3}{n-i-1}i$。

考虑范德蒙德卷积结论，即 $\sum \limits_{i=0}^k \dbinom{n}{i} \dbinom{m}{k-i} = \dbinom{n+m}{k}$。证明考虑组合意义：有 $n+m$ 个物品，恰好 $n$ 个有属性 A，另外 $m$ 个有属性 B。选出 $k$ 个式子，既可以直接按照后面的方式组合数，也可以枚举 $i$ 选择属性 A 然后选择属性 B。

于是容易把式子前半部分变成 $(n+1)\dbinom{2n-3}{n-1}$。

后半部分为 $\sum \limits_{i=2}^{n-1}\dbinom{n}{i} \dbinom{n-3}{n-i-1}i$。

经典套路是把 $i$ 变成 $\dbinom{i}{1}$，则变为 $\sum \limits_{i=2}^{n-1}\dbinom{n}{i} \dbinom{i}{1} \dbinom{n-3}{n-i-1}$。

容易知道 $\dbinom{n}{i}\dbinom{i}{1} = \dbinom{n}{1} \dbinom{n-1}{i-1}$。然后把 $\dbinom{n}{1}=n$ 放到前面，变为了 $n \sum \limits_{i=2}^{n-1} \dbinom{n-1}{i-1}\dbinom{n-3}{n-i-1}$。继续运用范德蒙德卷积结论就变为 $n\dbinom{2n-4}{n-2}$。

故答案为 $(n+1)\dbinom{2n-3}{n-1}-n\dbinom{2n-4}{n-2}$，预处理阶乘和阶乘逆元即可做到 $O(n+T)$ 的时间复杂度。

---

## 作者：Disjoint_cat (赞：0)

**【置顶】本题解中有一些乱搞内容，如果想要纯粹的正解请右转其他大佬的题解。**

## ABC290F Maximum diameter

### 1. 题意

对于一个长度为 $n$ 的序列 $P$，定义 $f(P)$ 为：

- 如果存在一棵 $n$ 个结点的树，使得第 $i$ 个节点的度数为 $P_i$，则 $f(P)$ 为这棵树的直径长度的最大值。
- 否则 $f(P)=0$。

现在给你一个 $n$，求所有长度为 $n$ 的序列的 $f$ 值的和。

多测，$T\le2\times10^5,n\le10^6$。

### 2. 题解

#### (1) 把 $f(P)$ 具象化

首先你会发现“所有序列”根本就是扯淡，只有满足 $\sum\limits_{i=1}^nP_i=2n-2$ 的 $P$ 才有树符合条件。

然后，“直径长度的最大值”还是一个问题。

不过我们可以发现，树中所有非叶节点是联通的。我们不妨让他们连成一条链，然后两边各连一个叶子节点，直径的长度就是最长的。

所以有 $f(P)=(P$ 中所有满足 $P_i\ge2$ 的 $i$ 的个数 $)+1$。

然后我们就完全把树抛开了。

接下来怎么计算呢？

#### (2) 统计答案

设 $ans_n$ 为 $n$ 的最终答案。

我们可以考虑有 $k(2\le k<n)$ 个叶子的时候，对答案产生多少贡献。

首先，要在 $n$ 个点中选择 $k$ 个作为叶子，即 $\dbinom{n}{k}$。

其次，要把剩下的度数分给 $(n-k)$ 个点，一共有 $2n-2-k$ 个度数，每个点的度数至少为 $2$，根据小学奥数的知识，贡献要乘上 $\dbinom{(2n-2-k)-(n-k)-1}{(n-k)-1}=\dbinom{n-3}{n-k-1}=\dbinom{n-3}{k-2}$。

最后在乘上直径长度 $(n-k+1)$。

于是我们得到了答案：

$$ans_n=\sum\limits_{k=2}^{n-1}\dbinom{n}{k}\cdot\dbinom{n-3}{k-2}\cdot(n-k+1)$$

（注意这里要特判 $n=2$）

做完了。

但还没有完全做完。

### (3) 优化

上面的做法时间复杂度是 $O(Tn)$，会 TLE。（悲

对着式子想了半天，没想到什么优化的思路。

于是开始乱搞。

首先，打表。

$$ans_2=1,ans_3=6,ans_4=26,ans_5=110,ans_6=462,ans_7=1932,ans_8=8052,ans_9=33462,\ldots$$

……看不出任何规律。

于是上 [OEIS](https://oeis.org) 搜。

……搜不到。

于是开始瞪眼大法。

突然发现相邻两项的商接近 $4$。

于是，搞出 $g_x=ans_{x+1}-4\cdot ans_x$。

$$g_2=2,g_3=2,g_4=6,g_5=22,g_6=84,g_7=324,g_8=1254,\ldots$$

发现全是偶数。于是，令 $h_x=\dfrac{g_x}{2}$：

$$h_2=1,h_3=1,h_4=3,h_5=11,h_6=42,h_7=162,h_8=627,\ldots$$

发现 $h$ 可以在 OEIS 上[搜到](https://oeis.org/search?q=1%2C1%2C3%2C11%2C42%2C162%2C627&language=english&go=Search)。

$$h_{n+2}=\dfrac{cat_n\cdot(n^2+2)}{n+2}$$

（其中 $cat$ 是 [$\text{Catalan}$ 数](https://baike.baidu.com/item/%E5%8D%A1%E7%89%B9%E5%85%B0%E6%95%B0/6125746?fromtitle=catalan%E6%95%B0%E5%88%97&fromid=10814050&fr=aladdin)）

$h$ 可以线性计算。

$$ans_{x+1}=4\cdot ans_x+2\cdot h_x\ (x\ge2),ans_2=1$$

然后这题就真的做完了。

### 3. 代码

这里就不放了，代码戳[这里](https://atcoder.jp/contests/abc290/submissions/39046485)。

---

## 作者：honglan0301 (赞：0)

## 题意简述
定义数列 $x_i\ (x_i∈N^+)$ 的权值为 满足对于 $∀i∈N^+,i\leq n$ 都有点 $i$ 的度数等于 $x_i$ 的 $n$ 个节点的树的最大直径（如不存在则为 $0$）。共 $T\ (T\leq 2\times 10^5)$ 组数据，每组数据给出正整数 $n\ (n\leq 10^6)$, 求出所有长为 $n$ 的数列的权值和。

## 题目分析
题意比较迷惑，首先容易知道 $n$ 个点的树各点度数之和为 $2\times n-2$, 因为树有 $n-1$ 条边，那么接下来我们尝试对于一个合法的 $x_i$ 求最大直径。

注意到有一个直径的求法是每次删掉叶节点，直到树被删空，那么要求直径最大即要求删点的轮数最多。第一轮删点的数量显然是固定的，而之后的每轮必至少删掉两个点（否则度数和 $\leq 2\times n'-2$, 矛盾），而又能贪心地发现之后必可以构造出每轮只删两个点的方案（剩下一条链）。于是对于一个含 $i$ 个 $1$ 的数列 $x_i$, 其对应的最大直径是 $2+(n-i-1)=n-i+1$, 构造是一条长为 $n-i-1$ 的链上挂了 $i$ 个点。

于是用上述想法，我们可以 $O(Tn)$ 地做本题，即 

$$ans(n)=\sum_{i=2}^{n-1}((n-i+1)\times C_n^i\times C_{n-3}^{n-i-1})$$

接下来我们来优化。

$$
\begin{aligned}
ans(n)&=\sum_{i=2}^{n-1}((n-i+1)\times C_n^i\times C_{n-3}^{n-i-1}) \\
&=\sum_{i=2}^{n-1}((n-i)\times C_n^{n-i}\times C_{n-3}^{i-2}+C_n^{n-i}\times C_{n-3}^{i-2}) \\
&=\sum_{i=2}^{n-1}(n\times C_{n-1}^{n-i-1}\times C_{n-3}^{i-2}+C_n^{n-i}\times C_{n-3}^{i-2}) \\
&=n\times C_{2n-4}^{n-3}+C_{2n-3}^{n-2}
\end{aligned}
$$

到此我们可以预处理后 $O(1)$ 计算了，其中最后一步是因为 $C_n^i=\sum_{j=0}^{i}(C_m^j\times C_{n-m}^{i-j})$，即范德蒙德卷积，组合意义显然。但可惜我赛时不会这个东西，于是挂掉了，不会做。

## 代码

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
#define mod 998244353
#define int long long

int t,n,dp[2000005],jc[2000005],ny[2000005];

int ksm(int x,int k)
{
	int na=1,nx=x;
	for(int i=1;i<=k;i<<=1)
	{
		if(i&k) {na*=nx; na%=mod;}
		nx*=nx; nx%=mod;
	}
	return na;
}
void init()
{
	jc[0]=1;
	for(int i=1;i<=2000000;i++) jc[i]=(jc[i-1]*i)%mod;
	ny[2000000]=ksm(jc[2000000],mod-2);
	for(int i=1999999;i>=0;i--) ny[i]=(ny[i+1]*(i+1))%mod;
}
int c(int x,int y) {return (jc[x]*ny[y])%mod*ny[x-y]%mod;}

void ans(int i) {dp[i]=(i*c(2*i-4,i-3)%mod+c(2*i-3,i-2))%mod;}

signed main()
{
	cin>>t; init();
	while(t--)
	{
		cin>>n; if(n==2) {cout<<"1"<<endl; continue;}
		ans(n); cout<<dp[n]<<endl;
	}
}
```


---

## 作者：ダ月 (赞：0)

### 题意分析：

多组询问，给定一个正整数 $n$，表示树的 $n$ 个节点。定义集合 $S$ 为这 $n$ 个节点的度数。定义 $f(S)$ 为当前在 $S$ 的限制下树的最大直径。求所有 $f(S)$ 的和。

### 题目分析：

定义大小为 $n$ 的可重正整数集合 $S$，$S_i$ 表示第 $i$ 个节点的度数。

结论 $1$：对于任何一棵有 $n$ 个节点的树，度数和为 $2n-2$。即 $\sum_{x\in S}x=2n-2$。结论显然。

结论 $2$：对于一棵树的直径，直径是集合 $S$ 内大于等于 $2$ 的整数的个数。当然，也有例外，就是树变成一个菊花图的时候，最大直径为 $2$。结论显然。

结论 $3$：

$\begin{aligned}\sum f(S)&=\sum(\text{S 中大于等于 2 的正整数个数+1})\\&
=(\sum_{x\in S}x=2n-2\text{ 的个数})+\sum(\text{所有 S 中大于等于 2 的正整数个数})\\&=
(\sum_{x\in S}x=2n-2\text{ 的个数})+n\times(\sum_{x\in S}x=2n-2 \text{并且 }x_1\ge2\text{ 的个数})
\end{aligned}$

考虑插板法，可以继续往下推：

$\begin{aligned}\text{原式}=&\binom{2n-3}{n-1}+\binom{2n-4}{n-1}\times n\end{aligned}$。

可以预处理，然后 $O(1)$ 询问。

代码如下：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=998244353;
const int N=3e6+10;
ll QP(ll x,ll y){ll ans=1;for(;y;y>>=1,x=x*x%mod)if(y&1) ans=ans*x%mod;return ans;}
ll fac[N],nfac[N];
void init(){
	fac[0]=1;for(int i=1;i<=N-10;i++) fac[i]=fac[i-1]*i%mod;
	nfac[N-10]=QP(fac[N-10],mod-2);for(int i=N-11;i>=0;i--) nfac[i]=nfac[i+1]*(i+1)%mod;
} 
ll C(ll x,ll y){if(x<y||x<0||y<0) return 0;return nfac[y]*nfac[x-y]%mod*fac[x]%mod;}
int main(){
	init();
	ll T,n;
	scanf("%d",&T);
	while(T--){
		scanf("%lld",&n);
		printf("%lld\n",(C(2*n-3,n-1)+C(2*n-4,n-1)*n)%mod);
	}return 0;
}
```

时间复杂度：$O(n+T)$。


---

## 作者：Missa (赞：0)

吸收恒等式、范德蒙德卷积。

为什么我能切黄题的场我都没打啊 /ll

------------------------

先考虑确定度数数组时怎么做。显然 $\sum x_i = 2n-2$。

手玩一下发现答案是 $\sum [x_i > 1] + 1$。

证明？$x_i=1$ 就是叶子，考虑到最多两片叶子参与构造直径，就做完了。把其它点上下串起来，前后各放一片叶子，如果仍缺少度数则往下挂儿子。因为 $\sum x_i=2n-2$，点一定刚好用完。

枚举 $\sum [x_i>1]$，然后枚举具体分配方案，最后在总数中选出有值的数字。

设共 $k$ 数，具体分配方案：预先每数减一 $n-2$ 分为 $k$ 份非零。

$$
=\sum_{k=1}^{n-2} \binom{n-3}{k-1} \binom{n}{k} (k+1) 
$$

它很范德蒙德卷积啊，但是有个 $k+1$，要把它吸收掉。

熟知的吸收恒等式：$\displaystyle \binom{n}{k} = \dfrac{n}{k} \binom{n-1}{k-1}$。化一下即 $\displaystyle  k\binom{n}{k} = n\binom{n-1}{k-1}$。

$$
=\sum_{k=1}^{n-2} n\binom{n-3}{k-1} \binom{n-1}{k-1} + \sum_{k=1}^{n-2} \binom{n-3}{k-1} \binom{n}{k}
$$

它的上指标是定值，下指标差也是定值，这不反转下指标做范德蒙德卷积：

$$
= n \sum_{k=1}^{n-2} \binom{n-3}{k-1} \binom{n-1}{n-k} + \sum_{k=1}^{n-2} \binom{n-3}{k-1} \binom{n}{n-k} 
$$

$$
= n \binom{2n-4}{n-1} + \binom{2n-3}{n-1}
$$

$\square$.

再给我一次机会，我绝对不会错过这场在周日的 abc。

---

## 作者：xuanxuan001 (赞：0)

听同学说这次 ABC 的 F 比 G 难，所以写完 G 后又破格看了看 F。

我实在想不明白 G 那么水是怎么在 kenkoooo 上评出 2400 的难度的，你上 ARCAGC 随便拿个 2400 的题都跟这个没法比啊。

F 官方题解的那个推导挺神奇的，根本没往那边想，所以又搞出了一个奇怪的做法，所以就发篇题解。

第一步的推导挺显然的，我记得是之前有一次牛客练习赛的 B，但不同的是那个只需要处理一次询问。不难发现合法的 $X$ 其实就是要满足每个数都是正整数且和为 $2(n-1)$，而题面中所谓的 $f(X)$ 其实就是 $X$ 中不为 1 的位置的个数加一。

那么先特判掉 $n=2$，对于剩下的情况一定会存在至少一个不为 1 的位置。

然后我就开始和官方做法越走越远了，和官方做法不一样的是，我直接转而考虑枚举 $i$ 并求出 $f(X)=i$ 的 $X$ 的数量~~主要是打牛客的时候就是这么推的~~。

那么会发现这个数量其实就是先一个组合数枚举出哪些位置不为 1，然后隔板法求出分配方案的数量。

那么答案其实就是

$$
\sum\limits_{i=1}^{n-2}iC_n^iC_{n-3}^{i-1}
$$

那么把组合数拆开并将 $i$ 减去 1，得到

$$
\sum\limits_{i=0}^{n-3}(i+1)\dfrac{(n-3)!n!}{(i-1)!i!(n-i-2)!(n-i)!}
$$

那么我们设 $a_i = \dfrac{i+1}{(i-1)!i!}$，$b_i = \dfrac 1{(n-i-2)!(n-i)!}$。

那么答案其实就是 $(n-3)!n!\sum\limits_{i=0}^{n-3}a_ib_{n-i}$。

然后你会发现这是个经典的 NTT，直接做就行了，询问时直接取出第 $n$ 项的值即可。

虽然一般的 NTT 题都很不好写，但这个其实还可以，因为你只需要在回答这些问题前做一次就行了，而且大小是固定的，直接上板子就行了。

代码难度和时间复杂度都被标算吊打，但我不知道为什么这样都还会有人比我跑得慢，而且还有不少。

代码（感觉讲的比较清楚了~~莫名自信~~，所以就不写注释了）：
```
#include<cstdio>
#define TY ll
#define MAXN 2097152
#define MAXM 1000002
#define debug if( 1 &&putchar('>'))
#define FOR(i,a,b) for(TY i=(a);i<=(b);i=-~i)
#define fOR(i,a,b) for(TY i=(a);i<(b);i=-~i)
#define ROF(i,a,b) for(TY i=(a);i>=(b);i=~-i)
#define rOF(i,a,b) for(TY i=(a);i>(b);i=~-i)
using namespace std;
typedef long long ll;
const TY M=998244353,dvn=998243877;
typedef unsigned long long ull;
TY _abs(TY a){return a<0?-a:a;}
TY maxn(TY a,TY b){return a>b?a:b;}
TY minn(TY a,TY b){return a<b?a:b;}
inline void updmx(TY &x,TY y){if(x<y)x=y;}
inline void updmn(TY &x,TY y){if(x>y)x=y;}
inline void add(TY &x,TY y){if((x+=y)>=M)x-=M;}
TY gcd(TY a,TY b){return b?gcd(b,a%b):a;}
TY qp(TY a,TY b){TY ans=1;do{if(1&b)ans=ans*a%M;a=a*a%M;}while(b>>=1);return ans;}
char getc(){char ch=getchar();while(ch==' '||ch=='\n'||ch=='\r')ch=getchar();return ch;}
TY qr(){
	char ch=getchar();TY s=0,x=1;
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')x=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())s=s*10+ch-'0';return x*s;
}void qw(TY a){if(a>9)qw(a/10);putchar(a%10+'0');}
void qw(TY a,char ch){
	if(a<0){a=-a;putchar('-');}
	if(a>9)qw(a/10);putchar(a%10+'0');
	if(ch)putchar(ch);
}TY T=qr(),fc[MAXM],dv[MAXM],r[MAXN],a[MAXN],b[MAXN],pw,w,tmp=M-1,p,q,n;
int main(){
	fOR(i,fc[0]=dv[0]=dv[1]=1,MAXM)fc[i]=fc[i-1]*i%M;
	fOR(i,2,MAXM)dv[i]=M-M/i*dv[M%i]%M;
	fOR(i,2,MAXM)dv[i]=dv[i]*dv[i-1]%M;
	for(TY i=1;i<MAXN;i<<=1)fOR(j,0,i)r[j|i]=(r[j]<<=1)|1;
	fOR(i,1,MAXM){
		if(i>1)b[r[i]]=dv[i-2]*dv[i]%M;
		a[r[i]]=(i+1)*dv[i-1]%M*dv[i]%M;
	}for(TY i=1;i<MAXN;i<<=1){
		w=qp(3,tmp>>=1);
		for(TY j=0;j<MAXN;j+=(i<<1)){
			pw=1;fOR(k,0,i){
				p=a[j|k];q=a[j|k|i]*pw%M;
				if((a[j|k]=p+q)>=M)a[j|k]-=M;
				if((a[j|k|i]=p-q)<0)a[j|k|i]+=M;
				p=b[j|k];q=b[j|k|i]*pw%M;
				if((b[j|k]=p+q)>=M)b[j|k]-=M;
				if((b[j|k|i]=p-q)<0)b[j|k|i]+=M;pw=pw*w%M;
			}
		}
	}fOR(i,0,MAXN)a[i]=a[i]*b[i]%M;tmp=M-1;
	fOR(i,1,MAXN)if(r[i]>i)a[i]^=a[r[i]]^=a[i]^=a[r[i]];
	for(TY i=1;i<MAXN;i<<=1){
		w=qp(3,M-1-(tmp>>=1));
		for(TY j=0;j<MAXN;j+=(i<<1)){
			pw=1;fOR(k,0,i){
				p=a[j|k];q=a[j|k|i]*pw%M;
				if((a[j|k]=p+q)>=M)a[j|k]-=M;
				if((a[j|k|i]=p-q)<0)a[j|k|i]+=M;pw=pw*w%M;
			}
		}
	}fOR(i,0,MAXN)a[i]=a[i]*dvn%M;
	while(T--){
		if((n=qr())==2){printf("1\n");continue;}
		qw(a[n]*fc[n]%M*fc[n-3]%M,'\n');
	}return 0;
}
```

---

