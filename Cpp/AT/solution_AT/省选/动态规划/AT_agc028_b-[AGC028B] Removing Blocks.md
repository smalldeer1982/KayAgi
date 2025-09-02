# [AGC028B] Removing Blocks

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc028/tasks/agc028_b

$ N $ 個のブロックが一列に並んでおり、左から右へ順に $ 1 $ から $ N $ の番号がついています。 それぞれのブロックには重さが定まっており、ブロック $ i $ の重さは $ A_i $ です。 すぬけ君は、これらのブロックに対して次の操作を $ N $ 回行います。

- まだ取り除かれていないブロックを $ 1 $ つ選んで取り除く。 この操作のコストは、取り除くブロックと連結なブロック（取り除くブロック自身も含む）の重さの総和となる。 $ 2 $ つのブロック $ x $, $ y $ ( $ x\ \leq\ y $ ) が連結であるとは、すべての $ z $ ( $ x\ \leq\ z\ \leq\ y $ ) について、ブロック $ z $ が取り除かれていないことを意味する。

ブロックを取り除く順番はちょうど $ N! $ 通りあります。 $ N! $ 通りのすべての順番について $ N $ 回の操作のコストの合計を求め、その総和を求めてください。 ただし、答えは非常に大きくなることがあるので、$ 10^9+7 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 入力はすべて整数である。

### Sample Explanation 1

ブロック $ 1 $, $ 2 $ の順で取り除く場合を考えます。 まず、最初の操作では、ブロック $ 1 $ と $ 2 $ が連結なので、操作のコストは $ 1+2=3 $ です。 次の操作では、ブロック $ 2 $ しか残っていないので、操作のコストは $ 2 $ です。 よって、この順で取り除く場合のコストの合計は $ 3+2=5 $ です。 ブロック $ 2 $, $ 1 $ の順で取り除く場合を考えます。 まず、最初の操作では、ブロック $ 1 $ と $ 2 $ が連結なので、操作のコストは $ 1+2=3 $ です。 次の操作では、ブロック $ 1 $ しか残っていないので、操作のコストは $ 1 $ です。 よって、この順で取り除く場合のコストの合計は $ 3+1=4 $ です。 上記より、答えは $ 5+4=9 $ となります。

## 样例 #1

### 输入

```
2
1 2```

### 输出

```
9```

## 样例 #2

### 输入

```
4
1 1 1 1```

### 输出

```
212```

## 样例 #3

### 输入

```
10
1 2 4 8 16 32 64 128 256 512```

### 输出

```
880971923```

# 题解

## 作者：CXY07 (赞：31)

> 题目链接：[\[AGC028B\] Removing Blocks](https://www.luogu.com.cn/problem/AT4436)

> **本题解同步发布于 [My Blog](http://www.cxy07.blog/index.php/archives/122/)**

题意：

> 给定长度为 $n$ 的序列 $\{a_n\}$，现需将 $n$ 个元素全部删除。删除元素 $i$ 的时候，设包括 $i$ 的极长未被删除区间为 $[l,r]$，则代价为 $\sum_{p=l}^r a_p$。

> 求 $n!$ 种删除顺序的代价和。

> $1\le n\le 10^5, 1\le a_i\le 10^9$。

随机一个排列，代价的期望 $\times n!$ 就是答案。

考虑计算每个元素在某一个固定顺序中，贡献到代价中的次数。建立基于删除时间的小根笛卡尔树，则笛卡尔树上一个节点对答案的贡献是子树内 $a_i$ 之和。

子树贡献转变为每个节点的深度贡献，设 $h_i$ 是 $i$ 号点的深度，令根节点深度为 $1$，则代价为 $\sum_{i=1}^n h_i\times a_i$。

因此现在需要求的就是每一个 $h_i$ 的期望 $E(h_i)$。而计算 $h_i$ 等价于计算有多少个 $x$ 是 $i$ 的祖先。

考虑一个排列，若 $x<i$ 且 $x$ 是 $i$ 的祖先，则 $x,x+1,\cdots i-1$ 都应比 $i$ 后删除，这样的方案数占总方案数的 $\dfrac{(i-x)!}{(i-x+1)!}=\dfrac{1}{i-x+1}$。因为只有这 $i-x+1$ 个元素的相对顺序是重要的，其中恰好有 $\dfrac{1}{i-x+1}$ 个排列满足 $i$ 在最前面被删除。

同理，当 $x>i$，$x$ 是 $i$ 的祖先的概率是 $\dfrac{1}{x-i+1}$。

因此有：

$$
E(h_i)=\sum_{x=1}^{i-1} \dfrac{1}{i-x+1}+\sum_{i+1}^{n}\dfrac{1}{x-i+1}+1
$$

设：

$$
s_x=\sum_{i=1}^x \dfrac{1}{i}
$$

则：

$$
E(h_i)=s_{i}+s_{n-i+1}-2+1=s_i+s_{n-i+1}-1
$$

因此答案为：

$$
n!\times \sum_{i=1}^n (s_i+s_{n-i+1}-1)\times a_i
$$

时间复杂度 $\mathcal{O}(n)$。

```cpp
//Code By CXY07
#include<bits/stdc++.h>
using namespace std;

//#define FILE
#define int long long
#define file(FILENAME) freopen(FILENAME".in", "r", stdin), freopen(FILENAME".out", "w", stdout)
#define randint(l, r) (rand() % ((r) - (l) + 1) + (l))
#define LINE() cout << "LINE = " << __LINE__ << endl
#define debug(x) cout << #x << " = " << x << endl
#define abs(x) ((x) < 0 ? (-(x)) : (x))
#define inv(x) qpow((x), mod - 2)
#define lowbit(x) ((x) & (-(x)))
#define ull unsigned long long
#define pii pair<int, int>
#define LL long long
#define mp make_pair
#define pb push_back
#define scd second
#define vec vector
#define fst first
#define endl '\n'

const int MAXN = 1e5 + 10;
const int INF = 2e9;
const double eps = 1e-6;
const double PI = acos(-1);
const int mod = 1e9 + 7;
//const int mod = 998244353;
//const int G = 3;
//const int base = 131;

int n, m, Ans = 0;
int a[MAXN], sum[MAXN], Inv[MAXN];

template<typename T> inline bool read(T &a) {
	a = 0; char c = getchar(); int f = 1;
	while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
	while(c >= '0' && c <= '9') {a = a * 10 + (c ^ 48); c = getchar();}
	return a *= f, true;
}

template<typename A, typename ...B>
inline bool read(A &x, B &...y) {return read(x) && read(y...);}

signed main () {
#ifdef FILE
	freopen(".in", "r", stdin);
	freopen(".out", "w", stdout);
#endif
	read(n); Inv[1] = 1;
	for(int i = 1; i <= n; ++i) read(a[i]);
	for(int i = 2; i <= n; ++i) Inv[i] = Inv[mod % i] * (mod - mod / i) % mod;
	for(int i = 1; i <= n; ++i) sum[i] = (sum[i - 1] + Inv[i]) % mod;
	for(int i = 1; i <= n; ++i) (Ans += (sum[i] + sum[n - i + 1] - 1) * a[i]) %= mod;
	for(int i = 1; i <= n; ++i) Ans = Ans * i % mod;
	printf("%lld\n", Ans);
	return 0;
}
```

---

## 作者：KemononeRou (赞：24)

其它的题解都太妙了，我想不到，这里提供一个不如其它题解巧妙的做法。

先考虑枚举第 $t$ 次操作，再枚举一个在前 $t-1$ 次操作没有砖块被移除，并且会在第 $t$ 次操作移除一个砖块的极长区间 $[l,r]$。

不妨假设 $l>1,r<n$，在前 $t-1$ 次操作中会将 $l-1$ 与 $r+1$ 移除。

记 $a_i$ 表示砖块移除代价的前缀和，那么 $[l,r]$ 中第一次有砖块被移除就会产生 $(a_r-a_{l-1})(r-l+1)$ 的贡献。

前 $t-1$ 次操作会将 $l-1$ 与 $r+1$ 移除，有 $\mathrm{A}_{t-1}^2$ 种方案。

前 $t-1$ 次操作还剩下 $t-3$ 次操作，不能移除 $[l,r]$ 与 $l-1$ 和 $r+1$，有 $\mathrm{A}_{n-(r-l+1)-2}^{t-3}$ 种方案。

后 $n-t$ 次操作任意排列，有 $\mathrm{A}_{n-t}^{n-t}$ 种方案。

因此 $[l,r]$ 在第 $t$ 次操作时有砖块被移除对答案的贡献为 $(a_r-a_{l-1})(r-l+1)\mathrm{A}_{t-1}^2\mathrm{A}_{n-(r-l+1)-2}^{t-3}\mathrm{A}_{n-t}^{n-t}\quad(1<l\leq r<n,t>2)$。

同理，

$l>1,r=n,t>1$ 时对答案的贡献为 $(a_n-a_{l-1})(n-l+1)\mathrm{A}_{t-1}^1\mathrm{A}_{l-2}^{t-2}\mathrm{A}_{n-t}^{n-t}$。

$l=1,r<n,t>1$ 时对答案的贡献为 $a_rr\mathrm{A}_{t-1}^1\mathrm{A}_{n-r-1}^{t-2}\mathrm{A}_{n-t}^{n-t}$。

$l=1,r=n,t=1$ 时对答案的贡献为 $a_nn\mathrm{A}_{n-1}^{n-1}$。

于是我们得到了一个 $O(n^3)$ 做法，只需要计算出下面这四个式子的值再加起来即可。

- $a_nn\mathrm{A}_{n-1}^{n-1}$。

- $\sum\limits_{t=2}^n\sum\limits_{l=t}^{n}(a_n-a_{l-1})(n-l+1)\mathrm{A}_{t-1}^1\mathrm{A}_{l-2}^{t-2}\mathrm{A}_{n-t}^{n-t}$。

- $\sum\limits_{t=2}^n\sum\limits_{r=1}^{n-t+1}a_rr\mathrm{A}_{t-1}^1\mathrm{A}_{n-r-1}^{t-2}\mathrm{A}_{n-t}^{n-t}$。

- $\sum\limits_{t=3}^n\sum\limits_{l=2}^{n-1}\sum\limits_{r=(t-1)-(n-l-1)}^l(a_r-a_{l-1})(r-l+1)\mathrm{A}_{t-1}^2\mathrm{A}_{n-(r-l+1)-2}^{t-3}\mathrm{A}_{n-t}^{n-t}$。

下面化简式子的过程中会直接将 $\mathrm{A}_n^m$ 替换成 $\dfrac{n!}{(n-m)!}$。

会用到的一些简单的组合恒等式有

- $\sum\limits_{i=0}^n\binom{l}{m}=\binom{n+1}{m+1}$。

- $(n+1)\binom{n}{m}=(m+1)\binom{n+1}{m+1}$。

第一个显然是 $a_nn!$。

第二个先交换求和顺序，把不包含 $t$ 的式子提到前面

$$\sum_{l=2}^n(a_n-a_{l-1})(n-l+1)\sum_{t=2}^l(t-1)\dfrac{(l-2)!}{(l-t)!}(n-t)!$$

$$\sum_{l=2}^n(a_n-a_{l-1})(n-l+1)(l-2)!\sum_{t=2}^l(t-1)\dfrac{(n-t)!}{(l-t)!}$$

$$\sum_{l=2}^n(a_n-a_{l-1})(n-l+1)(l-2)!(n-l)!\sum_{t=2}^l(t-1)\binom{n-t}{n-l}$$

考虑快速计算 $\sum\limits_{t=2}^l(t-1)\binom{n-t}{n-l}$。

其实可以考虑计算这样一个东西：$\sum\limits_{i=0}^{n-1}i\binom{n-i-1}{m-1}$。

这里有一个常见套路，将 $i$ 变成 $n-(n-i)$。

于是我们就只需计算 $n\sum\limits_{i=0}^{n-1}\binom{n-i-1}{m-1}$ 与 $\sum\limits_{i=0}^{n-1}(n-i)\binom{n-i-1}{m-1}$ 的值即可。

前面的式子由第一个恒等式可知是 $n\binom{n}{m}$。

后面的式子由第二个恒等式可知是 $\sum\limits_{i=0}^{n-1}\binom{n-i}{m}$，再由第一个恒等式可知是 $\binom{n+1}{m+1}$。

同理可知 $\sum\limits_{t=2}^l(t-1)\binom{n-t}{n-l}=n\binom{n-1}{n-l+1}-(n-l+1)\binom{n}{n-l+2}$。

最终的结果就是

$$\sum_{l=2}^n(a_n-a_{l-1})(n-l+1)(l-2)!(n-l)!\left(n\binom{n-1}{n-l+1}-(n-l+1)\binom{n}{n-l+2}\right)$$

第三个式子做法与第二个式子相同，最终结果是

$$\sum_{r=1}^{n-1}a_rr(n-r-1)!(r-1)!\left(n\binom{n-1}{r}-r\binom{n}{r+1}\right)$$

最后一个式子三个 $\sum$ 不太好做，我们发现对于一个长度固定的区间 $[l,r]$，他们对答案的贡献的一连串乘积只有 $a_r-a_{l-1}$ 这里不同。

我们可以记 $f_x$ 表示 $r-l+1=x$ 且 $l>1,r<n$ 的 $a_r-a_{l-1}$ 之和，$f$ 也是很好求的。

$$f_x=\sum_{i=x+1}^{n-1} a_{i}-a_{i-x}=\sum_{i=x+1}^{n-1}a_i-\sum_{i=1}^{n-x-1}a_i$$

对 $a$ 做一遍前缀和即可。

那么第四个式子就可以变为

$$\sum_{t=3}^{n}\sum_{x=1}^{n-t+1}xf_x(t-1)(t-2)\dfrac{(n-x-2)!}{(n-x-t+1)!}(n-t)!$$

和先前一样的方法化简，我们会得到这样一个式子

$$\sum_{x=1}^{n-2}xf_x(n-x-2)!(x-1)!\sum_{t=3}^{n-x+1}(t-1)(t-2)\binom{n-t}{x-1}$$

和先前一样，也只需快速计算 $\sum_{t=3}^{n-x+1}(t-1)(t-2)\binom{n-t}{x-1}$ 的值。

首先将 $(t-1)(t-2)$ 拆成 $t^2-3t+2$，然后分别求 $\sum\limits_{t=3}^{n-x+1}t^2\binom{n-t}{x-1}$，$\sum\limits_{t=3}^{n-x+1}-3t\binom{n-t}{x-1}$，$\sum\limits_{t=3}^{n-x+1}2\binom{n-t}{x-1}$ 的值。


第三个根据第一个恒等式可知是 $2\binom{n-2}{x}$。

第二个根据上面的套路可知是 $-3(n+1)\binom{n-2}{x}+3x\binom{n-1}{x+1}$。

第一个的 $t^2$ 好像不会推啊？

上面的套路为了与 $\binom{n-i-1}{m}$ 凑出组合恒等式消掉系数，将 $i$ 变为 $n-(n-i)$。

所以我们这里考虑与 $\binom{n-t}{x-1}$ 凑出一个或几个组合恒等式消掉系数，考虑凑出个 $n-t+1$，将 $t^2$ 变为 $(n+1)t-t(n-t+1)$。

于是变成了 $(n+1)\sum_{t=3}^{n-x-1}t\binom{n-t}{x-1}-x\sum_{t=3}^{n-x-1}t\binom{n-t+1}{x}$。

如果你掌握了上面的套路，那到这里相信你已经会推了，所以我就直接放最终的结果

$$\sum_{x=1}^{n-2}xf_x(n-x-2)!(x-1)!\left(n(n-1)\binom{n-2}{x}-2nx\binom{n-1}{x+1}+x(x+1)\binom{n}{x+2}\right)$$

将四个式子算出来求和就是最终的答案，时间复杂度 $O(n)$。

[Code](https://www.luogu.com.cn/paste/3bezwdfv)

---

## 作者：E_huan (赞：14)

求总贡献转化为求期望，再从笛卡尔树的角度思考得到式子。

首先不难发现，每移除一个，砖块就可以分成两边（如果移除的是端点处，其中一边可能为空）。此后移除左边某个砖块时右边砖块不会有贡献，右边同理。

也就是说，在砖块 $i$ 被移除之前，它会在“每层”贡献一次。

对于任意一对砖块 $x$，$y$ $(x<y)$，删除 $x$ 的时候 $y$ 有贡献当且仅当 $x$ 是 $x$，$x+1$，$x+2$，...，$y$ 中第一个被删除的节点。

理解题意之后仍然不好下手，考虑把计算代价的和转化成计算 “ 期望 $\times$ 方案数 ”，方案数显然是 $n!$，难点在于求期望贡献。

发现如果对于删除时间建立一颗小根笛卡尔树，每个节点贡献次数就是其深度。

问题又转化成了考虑期望深度，发现对于 $x<y$，删除 $x$ 时 $y$ 能贡献的概率是 $\frac{1}{y-x+1}$ （即 $x$ 是 $[x,y]$ 这 $y-x+1$ 个数中第一个被删除的）。这里的意思是，不论 $x'(x'<x)$ 删除时 $y$ 是否有贡献，删除 $x$ 时 $y$ 能贡献的概率都是 $\frac{1}{y-x+1}$。
同理，对于 $x>y$，删除 $x$ 时 $y$ 能贡献的概率是 $\frac{1}{x-y+1}$。

那么 $y$ 的期望深度就是 $\sum\limits_{1 \le x<y}  \frac{1}{y-x+1} +  \sum\limits_{y<x \le n}\frac{1}{x-y+1} +1 $ 。

最终的答案就是“ 期望深度 $\times$ 权值 $\times$ 总方案数 ”。

可以预处理 $1 \sim n$ 的倒数的前缀和实现 $O(n)$，求 $1 \sim n$ 倒数的逆元也可以线性。

注意由于上式的 $x$ 是不能等于 $y$ 的，所以求前缀和时不算 $inv[1]$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100010,mod=1000000007;
int n,_n=1,s[N],inv[N];
inline void add(int &x,int y)
{
    x+=y;
    if(x>=mod) x-=mod;
}
int main()
{
    scanf("%d",&n);
    inv[1]=1;
    s[1]=0;
    for(int i=2;i<=n;i++) 
    {
        _n=1ll*_n*i%mod;
        inv[i]=(mod-1ll*(mod/i)*inv[mod%i]%mod);
        s[i]=s[i-1];
        add(s[i],inv[i]); 
    }
    int ans=0;
    for(int i=1,a;i<=n;i++)
    {
        scanf("%d",&a);
        add(ans,1ll*a*_n%mod*((s[i]+s[n-i+1]+1)%mod)%mod);
    } 
    printf("%d\n",(ans+mod)%mod);
    return 0;
}
```

---

## 作者：听取MLE声一片 (赞：9)

非正解，打标找规律。

容易发现只需要统计每个位置出现的次数在乘上每个位置的值即可。

这样的题应该是有一个简单的式子，所以尝试打表找出规律。

首先把表的前几项打出来：

| # | 1 | 2 | 3 | 4 | 5 | 6 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------:  |
| 1: | $1$ |  |  |  |  |  | 
| 2: | $3$ | $3$ |  |  |  |  | 
| 3: | $11$ | $12$ | $11$ |  |  |  | 
| 4: | $50$ | $56$ | $56$ | $50$ |  |  | 
| 5: | $274$ | $310$ | $320$ | $310$ | $274$ |  | 
| 6: | $1764$ | $2004$ | $2100$ | $2100$ | $2004$ | $1764$ |

发现表是有对称性的。

这些数增长很快啊！不过对于某一列，第 $i$ 行的答案减去第 $i-1$ 行的答案乘 $i$ 就比较小了。

尝试对第一列这么操作，减完后发现是一个阶乘。

$$f_{i,1}=f_{i-1,1}\times i+(i-1)!$$

这个结构很好啊，后面直接启动！

$$f_{i,2}=f_{i-1,2}\times i+(i-1)!+(i-2)!$$

继续搞发现启动失败，找不到规律了。

这些东西全部都带阶乘，对于第 $i$ 行每行先除以一个 $i!$。

第一列除以阶乘以后变成了一个调和级数，感觉性质非常好。

令第 $n$ 个调和数为 $H_n$。

第 $i$ 行第二列变成了 $H_{i-1}+\frac{1}{2}$，性质更好了。

大胆猜测答案是由两个调和级数加起来的。

注意到对于某一行是一单峰的，而且在单调递增部分中增加的越来越少，猜测是把调和级数的最后一个数删掉然后在另一个调和级数后再加一个。

拿 $\frac{320}{120}=\frac{8}{3}$ 验证一下，发现它等于 $H_3+H_3-1$，猜测是对的。

再因为对称性，总结出第 $i$ 行第 $j$ 列的答案是 $H_j+H_{i-j+1}-1$。

测一下样例发现是对的，启动成功！

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<ctime>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=1e5+10;
const int mod=1e9+7;
int n,ans,a[N],f[N],g[N];
signed main()
{
	g[1]=1;
	for(int i=2;i<N;i++)
		g[i]=g[mod%i]*(mod-mod/i)%mod;
	for(int i=1;i<N;i++)
		f[i]=(f[i-1]+g[i])%mod;
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		int x=i,y=n-i+1;
		ans+=(f[x]+f[y]-1)*a[i]%mod;
	}
	for(int i=1;i<=n;i++)
		ans=ans*i%mod;
	cout<<ans;
	return 0;
}

```

---

## 作者：_FL_ (赞：5)

因为本人太菜看不懂题解区各种神奇的做法，所以提供一个自己的非常自然而简单的思路。  

肯定是去想计算每个 $a_i$ 对答案的贡献次数 $x_i$，而这个贡献次数可以分为 $i$ 左边删数造成的贡献和右边删数造成的贡献。  

左边和右边对称，不妨以左边为例，这相当于一个长度为 $i$ 的序列，每次可以在序列中删除任意长度的一段后缀，求删空的次数之和。  

不妨计算期望删空次数，最后乘 $n!$，把这个次数设出来，即设 $f_i$ 表示删空长度为 $i$ 的序列的期望次数，则 $f_i=\dfrac{1}{i}\sum\limits_{j=0}^{i-1}(f_j+1)$，这可以简单 $O(n)$ 预处理。  

则 $x_i=f_i+f_{n-i+1}-1$，直接计算即可。时间复杂度 $O(n)$。  

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
typedef long long ll;
namespace IO {
	template<typename T = int>
	inline T rd() {
		char ch = getchar();
		T x = 0;
		bool C1 = 0;
		while (ch < '0' || ch > '9') C1 |= ch == '-', ch = getchar();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
		return C1 ? ~(x - 1) : x;
	}
	template<typename T>
	inline void wr(T x) {
		if (x < 0) x = ~(x - 1), putchar('-');
		if (x > 9) wr(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace IO;
mt19937 mand(time(0));
const ll rwt = 1;
const double rwd = 1.0;
void cmx(int &x, int y);
void cmn(int &x, int y);
int imax(int x, int y);
int imin(int x, int y);
int iabs(int x);
int Mand(int x, int y);
int qpow(int x, int k);
void smd(int &x, int y);
void dmd(int &x, int y);
void pmd(int &x, int y);
int amd(int x, int y);
int mmd(int x, int y);
const int mod = 1e9 + 7;
const int N = 1e5 + 5;
int Inv[N], dp[N], t, n, ans;
void Solve();
signed main() {
	Inv[0] = Inv[1] = 1;
	for (int i = 2; i <= N - 3; i++) {
		Inv[i] = rwt * Inv[mod % i] * (mod - mod / i) % mod;
	}
	t = 1;
	while (t--) {
		Solve();
	}
	return 0;
}
void Solve() {
	int T1 = 1;
	dp[0] = 0, dp[1] = 1;
	for (int i = 2; i <= N - 3; i++) {
		dp[i] = rwt * T1 * Inv[i] % mod;
		smd(dp[i], 1);
		smd(T1, dp[i]);
	}
	n = rd();
	for (int i = 1; i <= n; i++) {
		int x = rd();
		smd(ans, rwt * x * mmd(amd(dp[i], dp[n - i + 1]), 1) % mod);
	}
	for (int i = 2; i <= n; i++) {
		pmd(ans, i);
	}
	wr(ans), putchar('\n');
	return;
}
void cmx(int &x, int y) {
	x = (y > x ? y : x);
	return;
}
void cmn(int &x, int y) {
	x = (y < x ? y : x);
	return;
}
int imax(int x, int y) {
	return (x < y ? y : x);
}
int imin(int x, int y) {
	return (x < y ? x : y);
}
int iabs(int x) {
	return (x < 0 ? -x : x);
}
int Mand(int x, int y) {
	return (mand() % (y - x + 1) + (y - x + 1)) % (y - x + 1) + x;
}
int qpow(int x, int k) {
	int Ans = 1;
	for (int i = k; i; i >>= 1, pmd(x, x)) {
		if (i & 1) {
			pmd(Ans, x);
		}
	}
	return Ans;
}
void smd(int &x, int y) {
	x = (x + y >= mod ? x + y - mod : x + y);
	return;
}
void dmd(int &x, int y) {
	x = (x - y < 0 ? x - y + mod : x - y);
	return;
}
void pmd(int &x, int y) {
	x = rwt * x * y % mod;
	return;
}
int amd(int x, int y) {
	return (x + y >= mod ? x + y - mod : x + y);
}
int mmd(int x, int y) {
	return (x - y < 0 ? x - y + mod : x - y);
}
```


---

## 作者：Albedo (赞：5)


## Solution

我们直接考虑对于第 $ i $ 个数，他所能做的总贡献是多少。
很显然，他所能做的贡献是与他删除时的区间有关的，我们考虑枚举那个区间，记为 $ [l,r] $ 。

那么考虑如何算贡献，我们发现，如果 $ [l,r] $ 这个区间是要被算到的，那么 $ l-1 $ 和 $ r+1 $ 一定要在他们之间被删掉，因为 $ i $ 被算贡献时这个区间还存在，所以剩余 $ r-l $ 个数一定是在 $ i $ 之后删的，知道了这个，就可以算方案数了，我们记 $ l-1 $ 和 $ r+1 $ 存在的数的数目为 $ tot $ ，那么有方案数为 $ T $ 。
$$
T=\frac{n!}{(r-l+1+tot)!}\times(r-l)!\times tot!
$$
具体解释上文已有，而这段区间所能贡献的价值就是方案数与区间重量的乘积，为 $ T\times (pre[r]-pre[l-1]) $ 。

而我们其实可以观察到，$ i $ 与总价值的表达式并无关系，所以可以省去一重循环，则区间 $ [l,r] $ 的真正价值为 $ T\times (pre[r]-pre[l-1])\times(r-l+1) $ 。

然而这样子还是不够快，所以我们考虑加速，而如何加速？

我们发现，$ tot $ 不为 $ 2 $ 的情况仅有 $ l=1 $ 和 $ r=n $ ，那我们可以把这一部分的贡献先算出来，然后剩下的情况就是 $ tot=2 $ 了，然后我们考虑枚举长度，就可以先算出 $ T $ 的值，但接下来还有一个问题，那么接下来就是这个值的快速求值：
$$
\sum_{l=2}^{n-1-len+1} pre[l+len-1]-pre[l-1]
$$
不会真的有人不会吧。

## Code

```c++
long long sum,len,g[1001010],down,fre,lim,tot,now,a[1001010],MOD,pre[1001010],ans,fac[1001010],ifac[1001010],lft,rit,val,n,i;
long long C(long long n,long long m)
{
	if ((n<0)||(m<0)||(n<m)) return 0;
	return fac[n]*ifac[n-m] % MOD*ifac[m] % MOD;
}
int main()
{
	//ios::sync_with_stdio(0);cin.tie();cout.tie();
	n=read();MOD=1e9+7;
	fac[0]=1;
	for (i=1;i<=n;i++) fac[i]=fac[i-1]*i % MOD;
	ifac[n]=pow(fac[n],MOD-2,MOD);
	for (i=n-1;i>=0;i--) ifac[i]=ifac[i+1]*(i+1) % MOD;
	for (i=1;i<=n;i++) a[i]=read(),pre[i]=pre[i-1]+a[i];
	for (lft=1;lft<=n;lft++)
	        {
		   down=lft;
		   if (lft!=1) down=n;
	       for (rit=down;rit<=n;rit++)
	            {
	            	val=(pre[rit]-pre[lft-1]) % MOD;
	            	//lft-1 & rit+1 is very important ，有 rit-lft 个数一定要在 i的后面，tot个数一定要在i的前面。 
	            	tot=0;
	            	if (lft-1>=1) tot++;
					if (rit+1<=n) tot++;
					fre=n-1-tot-(rit-lft);
					if (fre<0) continue;
					lim=tot+1+rit-lft;//rit++,len++,now
					               //a           b                              c                   d  
					ans=ans+(fac[n]*val % MOD*ifac[lim] % MOD*fac[tot] % MOD*fac[rit-lft] % MOD*(rit-lft+1) % MOD);
					//abcd->(a+a[rit])*(b/(len+tot+1))*(c*len))*(d+1)
					//(a+a[rit])*(d+1)=ad+a[rit]*d+
					//我们考虑调换顺序 
					ans%=MOD; 
				}
		  }
	for (len=1;len<=n-2;len++)
	      {
	      	//val:fac[len-1]*len*fac[n]
	      	//((lft>1)&&(rit<n))
	      	//val:fac[len-1]*len*fac[n]*ifac[len]*fac[0]
	      	lft=2+len-1;rit=n-1-len+1;
	      	sum+=pre[rit]-pre[lft-1];
	      	sum%=MOD;
	      	g[len]=sum;
	      	if (len>(n-1)/2) g[len]=g[n-2-len+1];
	      	now=fac[len-1]*len % MOD*fac[n] % MOD*ifac[len+2] % MOD*fac[2] % MOD*g[len] % MOD;
	      	ans=(ans+now) % MOD;
		  }
	printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：tanyulin (赞：2)

提供一个不用期望的做法。
考虑一个区间 $[l,r]$ 的贡献，就是这段区间的和乘上有多少排列的权值要用到这段区间。
现在讨论**有多少排列的权值有这段区间**。
这段区间会被用到当且仅当 $l-1$ 和 $r+1$ 均出现在 $l\sim r$ 的前面，即把这个区间分裂出来。
为了避免出错，这里进行分类讨论：
+ 如果这个区间靠边，则仅需要 $l-1$ 或 $r+1$ 在前面，个数为 $\frac{n!}{len+1}$（$len$ 为区间长度）。
+ 如果这个区间不靠边，则需要 $l-1$ 或 $r+1$ 都在区间前面出现，个数为 $\frac{2n!}{(len+1)(len+2)}$。
  **关于这个式子的理解**：
  先只考虑 $l-1$，方案数为 $\frac{n!}{len+1}$，现在对于 $l-1$ 和这个区间的**合法排列（即 $l-1$ 出现在区间前面）**，$r+1$ 有 $len+2$ 种放法插入期间，其中合法的只有 $2$ 种，即放在 $l-1$ 的前面或者后面，相当于每 $len+2$ 种方案取 $2$ 种方案。

容易发现，这个方案数只跟**区间长度及是否靠边有关，与区间的位置无关**，因此现在只需要统计长度为 $len$ 的区间的权值和，这是比较容易的，考虑每个数在长为 $len$ 的线段从左往右滑的过程中被覆盖几次，很容易预处理。
所以枚举区间长度统计答案就行了。  
**细节**：
+ 长度为 $n$ 的区间单独讨论。
+ 在统计长度为 $len$ 的答案时是否靠边也要讨论。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp(x,y) make_pair(x,y)
#define all(x) x.begin(),x.end()
#define eb(x) emplace_back(x)
const int mod=1e9+7,N=1e5+10;
typedef long long LL;
typedef pair<int,int> pii;
template<typename T>inline void read(T &x)
{
    int f=1;
    x=0;
    char c=getchar();
    while(!isdigit(c))
    {
    if(c=='-') f=-1;
    c=getchar();
    } 
    while(isdigit(c)) x=x*10+c-'0',c=getchar();
    x*=f;
}
template<typename T,typename ...L>inline void read(T &x,L &...l){read(x),read(l...);}
template<typename T>inline void print(T x)
{
    if(x<0) putchar('-'),x=-x;
    char c[30];
    int t=0;
    do{
        c[t++]=x%10+'0',x/=10;
    }while(x);
    while(t) putchar(c[--t]);
    putchar('\n');
}
template<typename T,typename ...L>inline void print(T x,L ...l){print(x),print(l...);}
template<typename T,typename L>inline void chkmx(T &x,L y){(x<y) && (x=y);}
template<typename T,typename L>inline void chkmn(T &x,L y){(x>y) && (x=y);}
int inc(const int &a,const int &b){return a+b>=mod?a+b-mod:a+b;}
int dec(const int &a,const int &b){return a-b<0?a-b+mod:a-b;}
int mul(const int &a,const int &b){return 1ll*a*b%mod;}
int sqr(const int &a){return 1ll*a*a%mod;}
void Inc(int &a,const int &b){a=a+b>=mod?a+b-mod:a+b;}
void Dec(int &a,const int &b){a=a-b<0?a-b+mod:a-b;}
void Mul(int &a,const int &b){a=1ll*a*b%mod;}
void Sqr(int &a){a=1ll*a*a%mod;}
int qmi(int a,int b)
{
    int res=1;
    while(b)
    {
        if(b&1) Mul(res,a);
        Sqr(a),b>>=1;
    }
    return res;
}
int n,a[N],s[N],b[N],ans,fac[N],infac[N];
void init()
{
    fac[0]=infac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=mul(fac[i-1],i);
    infac[n]=qmi(fac[n],mod-2);
    for(int i=n;i>=1;i--)
        infac[i-1]=mul(infac[i],i);
}
int main()
{
    read(n);
    init();
    for(int i=1;i<=n;i++) read(a[i]);
    for(int i=1;i<=n/2;i++) b[i]=inc(b[i-1],mul(i,inc(a[i],a[n-i+1])));
    for(int i=1;i<=n;i++) s[i]=inc(s[i-1],a[i]);
    ans=mul(fac[n],s[n]);
    //Inc(ans,inc(mul(fac[n-1],s[n-1]),mul(fac[n-1],dec(s[n],s[1]))));
    for(int i=1;i<=n-1;i++)
    {
        int cnt=mul(mul(2,fac[n]),mul(qmi(i+1,mod-2),qmi(i+2,mod-2)));
        int lim=min(i,n-i+1)-1;
        int ss=dec(inc(b[lim],mul(lim+1,dec(s[n-lim],s[lim]))),inc(s[i],dec(s[n],s[n-i])));
        Inc(ans,mul(cnt,ss));
        Inc(ans,inc(mul(s[i],mul(fac[n],qmi(i+1,mod-2))),mul(dec(s[n],s[n-i]),mul(fac[n],qmi(i+1,mod-2)))));
    }
    cout<<ans<<endl;
    return 0;
}

```

---

## 作者：cmll02 (赞：2)

对于两个位置 $u,v~(|u-v|=k)$，考虑在什么情况下 $v$ 会对 $u$ 产生贡献。

在删除序列中要求 $v$ 要在所有在 $u,v$ 之间的其他数前面。

容易发现这样的序列有 $\dfrac{n!}{k+1}$ 个（简单理解就是 $u$ 到 $v$ 这 $k+1$ 个数中 $v$ 必须放在首位）。

同样方法可以算出 $u>v$ 时的贡献。

然后就是优化这一坨东西。前缀和一下预处理出 $\sum\limits_{i=1}^n\dfrac 1 i$，然后就做完了。

[代码评测记录](https://atcoder.jp/contests/agc028/submissions/26055923)

---

## 作者：b6e0_ (赞：1)

**无需转期望或笛卡尔树的一步到位简单组合思路。**

观察到最终的答案是每个 $a_i$ 乘上位置 $i$ 的一个系数 $x_i$ 的和，而系数 $x_i$ 只和 $n$ 有关。考虑求出所有 $x_i$。

考虑解决一个更弱的问题：所有 $a_i$ 中只有 $a_1=1$，其他为 $0$，即求出 $x_1$。令 $f_n$ 表示答案。根据题意，一个长度为 $n$ 的排列 $p$ 答案为：
$$w(p)=\sum_{i=1}^n[\nexists j<i,p_j<p_i]$$
则：
$$f_n=\sum_pw(p)$$
考虑由 $f_{n-1}$ 递推至 $f_n$。考虑往一个长度为 $n-1$ 的排列中插入一个数 $n$，得到长度为 $n$ 的排列。注意到对于任何 $p$，只有这个 $n$ 插入在 $p$ 开头时 $w(p)$ 才会增加 $1$。所以：
$$f_n=nf_{n-1}+(n-1)!$$
有了系数 $x_1$，我们考虑原问题。对于一个排列 $p$ 和一个下标 $i$，将 $p$ 中 $\le i$ 和 $\ge i$ 的元素分别拿出来，顺序不变，得到两个新序列 $p_1,p_2$，再将 $p_1$ 中的值域翻转（即所有元素 $p_{1,j}$ 变为 $i-p_{1,j}+1$）、$p_2$ 中每个元素减去 $i-1$，则 $p$ 对 $x_i$ 的贡献就是 $w(p_1)+w(p_2)-1$，则：
$$\begin{aligned}x_i&=\sum_pw(p_1)+w(p_2)-1\\&=\sum_pw(p_1)+\sum_pw(p_2)-n!\\&=\sum_{p_1}w(p_1)\cdot A_n^{n-i}+\sum_{p_2}w(p_2)\cdot A_n^{i-1}-n!\\&=n!\left(\frac{f_i}{i!}+\frac{f_{n-i+1}}{(n-i+1)!}-1\right)\end{aligned}$$
其中 $A_n^m$ 为排列数。

令 $g_n=\dfrac{f_n}{n!}$，则根据上面 $f_n$ 的递推式易得 $g_n=g_{n-1}+\dfrac1n$，最终的答案即为：
$$n!\sum_{i=1}^na_i(g_i+g_{n-i+1}-1)$$
式子和其他题解一样。时空复杂度均为 $\mathcal O(n)$。代码过于简单，没必要放了。

---

## 作者：Odalys (赞：1)

**[AGC028B] Removing Blocks**

直接做不太好做，考虑随机一个排列，它的代价和的期望乘上一个 $n!$ 就是答案。
 
考虑删除一个点，它其实是把此时序列贡献统计了之后重划分为了互不贡献的两边，这有点像笛卡尔树的过程，于是我们建立基于删除时间的小根笛卡尔树，此时一个点权的贡献就是 $A_u\times dep_u$ 

根据期望的线性性，我们常常要考虑一个位置对答案的贡献，于是可以考虑一个点的期望深度。

考虑计算 $E(dep_y)$ ，此时，对于 $y<x$ ，考虑 $y$ 对 $x$ 深度的贡献，则当且仅当 $y$ 是 $y...x$ 中第一个被删除的节点，概率是 ${(x-y)!\over (x-y+1)！}={1\over (x-y+1)}$ 。

则答案就是：
$$
n!\sum_{x=1}^n E(dep_x) \times A_x\\
n!\sum_{x=1}^n (\sum_{y<x}{1\over x-y+1}+\sum_{y>x}{1\over y-x+1}+1) \times A_i
$$
预处理一个 $\sum {1\over i}$ 的前缀和数组就好了。

---

## 作者：GIFBMP (赞：1)

总和不好计算，因此考虑计算期望，再乘上 $n!$，得到答案。

我们发现，删点的过程可以看成在当前区间 $[l,r]$ 选择一个下标 $x$，然后对于 $[l,x-1]$ 和 $[x+1,r]$ 分别建立笛卡尔树的过程。那么就容易得出，一个节点 $x$ 的期望贡献等于 $a_x\times dep_x$ 其中，$dep_x$ 代表 $x$ 在笛卡尔树上的期望深度。

注意到 $dep_x$ 等于 $x$ 的祖先数量加一，因此，$dep_x$ 的计算可以转化为求 $x$ 的祖先数量的期望。

那么对于 $1\le i<x$ 的节点，$i$ 是 $x$ 的祖先当且仅当在区间 $[i,x]$ 中，$x$ 最先被删除，因此 $i$ 是 $x$ 的祖先的概率为 $\dfrac{1}{x-i+1}$。

对于 $x<i\le n$ 的节点也同理，概率为 $\dfrac{1}{i-x+1}$。

综上所述：

$$E(dep_x)=\sum_{i=1}^{x-1}\dfrac{1}{x-i+1}+\sum_{i=x+1}^n\dfrac{1}{i-x+1}+1$$

$$=\sum_{i=2}^x\dfrac{1}{i}+\sum_{i=2}^{n-x+1}\dfrac{1}{i}+1$$

$$=\sum_{i=1}^x\dfrac{1}{i}+\sum_{i=1}^{n-x+1}\dfrac{1}{i}-1$$

因此只要预处理出所有 $\sum_{i=1}^k\frac{1}{i}$ 即可。

时间复杂度：$\Theta(n)$ 或 $\Theta(n\log n)$（根据求逆元的方法而定）。

Code:

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std ;
const int MAXN = 2e5 + 10 , mod = 1e9 + 7 ;
typedef long long ll ;
int n , a[MAXN] ;
ll qpow (ll x , ll p = mod - 2) {
	ll ret = 1 ;
	for (; p ; p >>= 1 , x = x * x % mod)
		if (p & 1) ret = ret * x % mod ;
	return ret ;
}
ll h[MAXN] , fac[MAXN] , inv[MAXN] , ans ;
int main () {
	scanf ("%d" , &n) ;
	fac[0] = 1 ;
	for (int i = 1 ; i <= n ; i++)
		scanf ("%d" , &a[i]) , fac[i] = fac[i - 1] * i % mod ;
	for (int i = 1 ; i <= n ; i++)
		inv[i] = (qpow (i) + inv[i - 1]) % mod ;
	for (int i = 1 ; i <= n ; i++) {
		h[i] = (inv[i] + inv[n - i + 1] - 1 + mod) % mod ;
		ans = (ans + h[i] * a[i] % mod) % mod ;
	}
	ans = ans * fac[n] % mod ;
	printf ("%lld\n" , ans) ;
	return 0 ;
}
```

---

## 作者：Yansuan_HCl (赞：0)

所有情况太多了。若固定操作序列，则可以计算。

想象删数的过程。删除一个数，对答案的贡献是两边连续的一段；删除之后，一整段被劈成两段。记每次删除，对答案有贡献的区间为 $[l,r]$，则可以发现，这样的区间**要么不交，要么包含。** 因此，可以考虑建树。

可以用每次删除的点来代表这段区间。把区间向**包含它的最小区间**连边。这样，每个点的删除时间满足小根堆。每次删除会把一段区间劈成两段，所以这是一棵二叉树。钦定二叉树的左右子树等于劈成的左右区间，则点的下标满足二叉搜索树的性质。（即该树是笛卡尔树）。

至此答案就是 $E=\sum sum_u$，其中 $sum$ 是子树 $a$ 的和。

知道了一个序列的情况，可以考虑计算**期望**，乘上 $n!$ 就是答案。上式并不好算。

把 $u$ 的贡献拆分成 $u$ 到根的路径上的每个点贡献一次，答案为 $E=\sum a_u E(d_u)$，$d$ 为深度。

计算深度的贡献，一种方法是枚举深度，并计算概率，但这样复杂度较高。回到**深度的定义**：即有多少点为 $u$ 的祖先。**可以枚举每个点** $v$，计算其为点 $u$ 祖先的概率。

按照刚才建树的方式，我们可以发现：

- $v$ 代表的区间必定包含 $u$ 代表的区间。
- 推论：从 $u$ 到 $v$ 的路径上的任意区间都包含 $u$ 代表的区间。

这就要求，$[u,v]$ 这一段中不能被早于 $v$ 的点劈开。否则 $v$ 代表的区间与 $u$ 代表的区间不会包含。即，$[u,v]$ 中 $v$ 的删除必定最早。这样就可以直接算概率了，分类讨论 $u,v$ 的左右关系即可。

```cpp
#include <bits/stdc++.h>
#define ms(x, v) memset(x, v, sizeof(x))
#define il __attribute__((always_inline))
#define U(i,l,r) for(int i(l),END##i(r);i<=END##i;++i)
#define D(i,r,l) for(int i(r),END##i(l);i>=END##i;--i)
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
template <typename T> using BS = basic_string<T>;

//const int SZ(1 << 23);
//unsigned char buf[SZ], *S, *Q;
//#define getchar() ((S==Q)&&(Q=buf+fread(S=buf,1,SZ,stdin)),S==Q?EOF:*S++)
template <typename T>
void rd(T& s) {
	int c = getchar();
	T f = 1; s = 0;
	while (!isdigit(c)) { if (c == '-') f = -1; c = getchar(); }
	while (isdigit(c)) { s = s * 10 + (c ^ 48); c = getchar(); }
	s *= f;
}
template <typename T, typename... Y>
void rd(T& x, Y&... y) { rd(x), rd(y...); }
template <typename T>
void pr(T s, bool f = 1) {
    if (s < 0) { printf("-"); s = -s; }
    if (!s) return void(f ? printf("0") : 0);
    pr(s / 10, 0);
    printf("%d", (signed)(s % 10));
}
#define meow(...) fprintf(stderr, __VA_ARGS__)

// 操作有时间的关系。建出笛卡尔树。笛卡尔树保证点相邻、时间堆
// 对于一棵树，答案为 \sum siz_u
// *考虑把每个点的贡献拆开
// *每个点对于自己到根的路径贡献一次
// 变成 \sum dep_u
// 祖先上的点删除都早于自己
// 分根的左右子树讨论
// 对于 i 为根的左子树(rt >= i)
// 深度为 d 的期望即祖先个数
// 对于每个点 v，累加其成为 u 的祖先的期望

// 结论：v 是 u 的祖先，当且仅当 [u,v] 中 v 第一个被删除
// 若有比 v 删除更早的，且下标小于 v (记为 w)
// 则 u 在 w 的左子树，v 在 w 的右子树
// 这样，v 为 u 的祖先的概率为 1/(u-v+1)

const int N = 100005;
const ll P = 1000000007;
ll qpow(ll x, ll t) { ll v = 1; for (; t; (x *= x) %= P, t >>= 1) if (t & 1) (v *= x) %= P; return v; }
ll inv[N];
void genFac() {
	U (i, 1, N - 1) inv[i] = qpow(i, P - 2);
	U (i, 1, N - 1) (inv[i] += inv[i - 1]) %= P;
}
int n; ll a[N];

int main() {
	genFac();
	rd(n); U (i, 1, n) rd(a[i]);

	ll ans = 0, fac = 1;
	U (i, 1, n) {
		(ans += a[i] * ((inv[i] + inv[n - i + 1] - 1) % P) % P) %= P;
		(fac *= i) %= P;
	}
	printf("%lld", ans * fac % P);
}
```

---

## 作者：Hjcc187 (赞：0)


> 求 $n!$ 种方案的代价和。

随机一个排列，答案就是 代价的期望$\times n!$。

根据期望线性性，代价的期望即为 每个数期望被贡献的次数$\times$权值。

考虑随机删除整个序列 $i$ 被计算贡献的期望次数。

在 $j$ 被删除时 $i$ 被贡献的条件为 $i$ 和 $j$ 联通，即 $[i,j]$ 均未被删除，即 $j$ 为 $[i,j]$ 中最先被删除的元素。

不难发现，在 $j$ 被删除时 $i$ 被贡献的概率为： $\dfrac{1}{|i - j| + 1}$

根据期望线性性，$i$ 被贡献的期望次数为：

$$\sum_{j = 1}^{n}\dfrac{1}{|i - j| + 1}$$

即：

$$\left(\sum_{j = 1}^{i - 1}\dfrac{1}{j + 1}\right) + \left(\sum_{j = 1}^{n - i}\dfrac{1}{j + 1}\right) + 1$$

因此答案为：

$$n! \times \sum_{i = 1}^{n}a_i\left(\left(\sum_{j = 1}^{i - 1}\dfrac{1}{j + 1}\right) + \left(\sum_{j = 1}^{n - i}\dfrac{1}{j + 1}\right) + 1\right)$$

预处理每个 $\sum\limits_{j = 1}^{x}\dfrac{1}{j + 1}$ 即可 $\mathcal O(n)$ 通过此题。

```cpp
#include <stdio.h>
#define long long long
#define mod 1000000007ll

using namespace std;

long n;
long a[100100];
long sum[100100];

inline long inv(long x) {
  long re = 1;
  long pow = mod - 2;
  while (pow) {
    if (pow & 1) {
      re = re * x % mod;
    }
    x = x * x % mod;
    pow >>= 1;
  }
  return re;
}

int main() {
  scanf("%lld", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", a + i);
  }
  long p = 1;
  for (int i = 1; i <= n; i++) {
    sum[i] = inv(i);
    p = p * i % mod;
  }
  for (int i = 2; i <= n; i++) {
    sum[i] = (sum[i - 1] + sum[i]) % mod;
  }
  long ans = 0;
  for (int i = 1; i <= n; i++) {
    ans = (ans + a[i] * (sum[i] + sum[n - i + 1] - 1) % mod) % mod;
  }
  printf("%lld", ans * p % mod);
}
```


---

## 作者：LinkyChristian (赞：0)

看到对所有方案求价值总和，我们将其转化为期望计算。

考虑一个点什么时候被记入答案。当被删除的点 $a_j$ 位于 $a_i$ 左边，这次删除能将 $a_i$ 记入贡献，当且仅当此时 $a_{j+1},\dots,a_i$ 没有被删除。也就是说，$a_{j+1},\dots,a_i$ 的删除时间在 $a_i$ 之后。那么将 $a_j,\dots,a_i$ 按删除时间排序后，$a_j$ 必须排在第一位。由于 $a_j,\dots,a_i$ 的排列总数有 $(j-i+1)!$ 种，其中 $a_j$ 排在第一位的方案数共有 $(j-i)!$ 种。因此 $a_j$ 被删除时能将 $a_i$ 记入贡献的概率为：

$$
\frac{(j-i)!}{(j-i+1)!}=\frac{1}{j-i+1}
$$

同理可得，当 $a_j$ 在 $a_i$ 右边时，删除 $a_j$ 将 $a_i$ 记入贡献的概率为 $\frac{1}{i-j+1}$

因此 $a_i$ 对答案的总贡献为：

$$
\sum_{j=1}^{i-1} \frac{1}{j-i+1} +1+ \sum_{j=i+1}^{n} \frac{1}{i-j+1} = \sum_{i=2}^{i} \frac{1}{i} + \sum_{i=2}^{n-i} \frac{1}{i} +1
$$

答案即为：

$$
n!\sum_{i=1}^n a_i (\sum_{i=2}^{i} \frac{1}{i} + \sum_{i=2}^{n-i} \frac{1}{i} +1)
$$

显然，预处理出 $\sum_{i=2}^{i} \frac{1}{i}$ 即可 $O(n)$ 完成此题。

---

