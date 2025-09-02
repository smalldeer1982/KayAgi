# [ARC168E] Subsegments with Large Sums

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc168/tasks/arc168_e

長さ $ N $ の正整数列 $ A=(A_1,A_2,\cdots,A_N) $ が与えられます．

この数列を $ K $ 個の非空な連続部分列に分割することを考えます． この $ K $ 個の連続部分列のうち，要素の総和が $ S $ 以上であるものの個数を**スコア**と呼ぶことにします． スコアの最大値を求めてください．

## 说明/提示

### 制約

- $ 1\ \leq\ K\ \leq\ N\ \leq\ 250000 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- $ 1\ \leq\ S\ \leq\ 10^{15} $
- 入力される値はすべて整数．
 
### Sample Explanation 1

数列を $ (1),(4,2),(8) $ と分割すると，スコアが $ 2 $ になります． これより大きいスコアは達成できないため，答えは $ 2 $ です．

## 样例 #1

### 输入

```
4 3 6
1 4 2 8```

### 输出

```
2```

## 样例 #2

### 输入

```
10 5 2
1 1 1 1 1 1 1 1 1 1```

### 输出

```
5```

## 样例 #3

### 输入

```
10 5 3
1 1 1 1 1 1 1 1 1 1```

### 输出

```
2```

## 样例 #4

### 输入

```
20 6 946667802
786820955 250480341 710671229 946667801 19271059 404902145 251317818 22712439 520643153 344670307 274195604 561032101 140039457 543856068 521915711 857077284 499774361 419370025 744280520 249168130```

### 输出

```
6```

# 题解

## 作者：Harry27182 (赞：18)


### 简要题意
给定一个长度为 $n$ 的序列 $a$，将 $a$ 划分为 $k$ 个连续段，最大化满足连续段中元素和 $\geq s$ 的连续段数。

### 题解
首先发现是恰好 $k$ 个连续段，这种类型的题套路地考虑 wqs 二分，然后你会惊喜的发现这玩意不是凸的，我的思考也就卡在这里了。

正确的做法是观察到答案具有单调性，所以可以考虑先二分答案转为判定性问题。这时候问题就被转化为，在令答案为 $x$ 的前提下，是否能够划分出 $k$ 个连续段。可以考虑更形式化地描述这个问题，具体的，设 $f_x$ 表示选出 $x$ 段的最小代价，每一段的代价使用 $r-l$ 来刻画，不难发现能够划分出 $k$ 个连续段等价于 $f_x\leq n-k$。所以可以考虑快速求出 $f_x$。

发现 $f_x$ 也是求出恰好答案为 $x$ 的方案数，而且这个函数看起来就是凸的。感性理解就是优先选择代价小的，更加严谨的证明可以参考官方题解。所以可以对 $f$ 进行 wqs 二分。然后内层的 dp 就是套路地记录一个 pair 表示最小代价和对应的最小个数，转移要么不选当前点，要么选以当前点为右端点的代价最小的一个区间，从对应位置转移。这一部分比较简单。

然后就做完了，时间复杂度 $O(n\log^2 n)$，可以通过本题。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
pair<int,int>dp[250005];int pre[250005],a[250005],sum[250005],n,k,s;
void solve(int x)
{
	for(int i=1;i<=n;i++)
	{
		dp[i]=dp[i-1];
		if(pre[i])dp[i]=min(dp[i],{dp[pre[i]-1].first+(i-pre[i])-x,dp[pre[i]-1].second+1});
	}
}
bool check(int x)
{
	int l=1,r=n,pos=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		solve(mid);
		if(dp[n].second<=x)l=mid+1,pos=mid;
		else r=mid-1;
	}
	solve(pos);
	return dp[n].first+pos*x<=n-k;
}
signed main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>k>>s;
    for(int i=1;i<=n;i++)cin>>a[i],sum[i]=sum[i-1]+a[i];
    for(int i=1,p=0;i<=n;i++)
    {
    	while(sum[i]-sum[p]>=s)p++;
    	pre[i]=p;
	}
    int l=1,r=k,res=0;
    while(l<=r)
    {
    	int mid=(l+r)>>1;
    	if(check(mid))res=mid,l=mid+1;
    	else r=mid-1;
	}
	cout<<res;
	return 0;
}
```

---

## 作者：Rosabel (赞：7)

谨以此文献给 wqs 二分初学者和像我一样对 wqs 二分算法理解得不够透彻的 ~~whk 选手~~。本文偏重讲解思考过程，对于 $f$ 函数凸性的证明请参考官方题解。

题目很简洁，就是给定长度为 $n$ 的序列，分成 $k$ 个非空段，要求最大化和至少为 $S$ 的子段数。

分析题目中所给的条件和要求，共有三个：

- 非空段个数为 $k$。
- 能贡献答案的子段和至少为 $S$。
- 最大化能贡献答案的子段个数 $x$。

第二个条件显然不太好作为突破口。考虑第一个和第三个。第一个显然直接 wqs 二分。但是发现作为这个 wqs 二分的函数 $f_i$ 转移没有决策单调性，函数也没有凸性，说明直接利用第一个条件好像有些困难。

我们再考虑第三个条件，最大化想到二分答案。而显然答案具有单调性。于是将问题转化为给定 $x$，判断是否存在合法构造方案使得非空段数为 $k$。

这一步就很像 wqs 二分了。注意到给定 $x$，那么对于任意的非空段数 $j$，判断构造方案可行性的函数 $g_j$ 也是单调的，说明此时可以通过求解非空段数 $j$ 的最大值，判断 $j$ 和 $k$ 的大小关系以得出答案。（可以无需关注 $g$ 的含义，因为与下文无关）。

求解非空段数最大值，则其对偶问题是最小化贡献段总长度大小（非贡献段全压缩成长度为 $1$ 的段，所以无需考虑）。设每一段贡献段 $[l_i,r_i]$ 对答案的贡献为 $r_i-l_i$。则 $f_x$ 就为 $\sum_{1\le i\le x}r_i-l_i$。

可以感性理解 $f_i$ 是下凸函数。（贡献段少的时候尽量选长度小的贡献少，贡献段多的时候只能选剩下长度大的，贡献也大，此处证明请参考官方题解）。增函数也是显然。对于上/下凸函数和增/减函数的判断很重要，影响后面 wqs 二分的细节。

$f$ 函数需要满足的条件是 $f\le n-k$。后面的就是 wqs 二分模板了。分析一下时间复杂度，外层二分 $x$，内层 wqs 二分和 $\Theta(n)$ 的 DP。总时间复杂度为 $\Theta(n\log^2n)$。

感觉还是很慢？可不可以消掉一个 $\log$？注意到两个 $\log$ 的来源都是二分。发现这外层二分的范围和 wqs 二分的答案范围一样，而且均具有单调性，考虑是否可以合并这两个二分。外层二分的 $x$ 进入内层二分斜率求解。由于外层答案、内层斜率均具有单调性，所以可以通过直接二分斜率直接判断是否可行而不需要与 $x$ 再做比较。这样就把外层二分省去从而优化成 $\Theta(n\log n)$。

还有一些小细节，比如最优解在 $f$ 函数中可能是一条线段中的中点，所以 wqs 二分求出满足答案的最右顶点，然后在线段慢慢移动（从 $i$ 调到 $i+1$ 答案更新复杂度是 $\Theta(1)$ 的，从图像上看增加斜率即可，而斜率已知）直到找到最优解。

记得和 $k$ 取 $\min$。

[code](https://atcoder.jp/contests/arc168/submissions/55608129)

辛辛苦苦写的，点个赞再走吧 awa

---

## 作者：Missa (赞：7)

有点意思的简单题。

答案有可二分性。合并两段，显然仍然合法。

考虑如何 check。因为答案可以被二分，我们尝试求恰好 $x$ 段就行了。

想法设计一个与 $x$ 有关的凸函数，这个函数大概是 $\sum_{i=1}^x w(l_i, r_i)$ 的形式，每一个 $[l, r]$ 都是合法的一段，且互相不重叠。这样就能记录段数，并为每一段附加权值了。

取 $w(l, r) = r - l$，合法等价于 $\sum w(l, r) \leq n-k$，要求每一段 $[l, r]$ 都合法。

设 $f(x)$ 为：划分出 $x$ 个合法段 $[l_i, r_i]$，$w(l_i, r_i)$ 之和。下面搬运官方题解对这个函数具有凸性的证明。（它是一个下凸壳，因为取一段的代价是越来越高的。）

假设 $B_1 \sim B_m$ 是 $m$ 个极短合法段。因为极短，两两不具有包含关系。因此我们假定这 $m$ 段右端点、左端点均递增。

设 $f(p)$ 对应的方案的极短合法段的编号是 $x_1 \sim x_{p}$，$f(p+2)$ 对应的方案的极短合法段的编号是 $y_1 \sim y_{p+2}$。先延长每一段左端点让它们两两相接，假设没有一个 $y$ 被完整包含到 $x$ 中，$y$ 最多只能有 $p+1$ 个，矛盾。因此设 $y_{i+1}$ 被包含于 $x_i$ 中，取 $x_1 \sim x_{i-1}, y_{i+1} \sim y_{p+2}$ 和 $x_1 \sim y_i, x_i \sim x_{p}$ 构成两个长度为 $p+1$ 的合法解，因此有 $2f(p+1) \leq f(p) + f(p+2)$，凸性得证。

![](https://cdn.luogu.com.cn/upload/image_hosting/l1qibcef.png)

（延长左端点前的图，可以证明延长后存在一个 $y_{i}$ 被包含于 $x_i$ 中，$y_i$ 与 $y_{i+1}$ 不一定相接，但这不影响。）

因此，我们得到了一个 $O(n \log^2 n)$ 的做法，[代码](https://atcoder.jp/contests/arc168/submissions/47865554)。

- 二分是否分为恰好 $x$ 段是可以的。注意这里的上界是 $k$。
- 设 $f(x)$ 为：分成恰好 $x$ 段的 $\sum w(l, r)$ 的最小值。这是一个下凸壳，因此对其进行 wqs 二分找到 $f(x)$。如果这个最小值不超过 $n-k$ 就认为可以分成 $x$ 段。

瓶颈其实在单点求值，在求一个点时重复求出了一些信息。对于 $(x, f(x))$ 组成的下凸壳，注意到我们需要的是 $y$ 坐标不超过 $n-k$ 的点的横坐标的最大值，当切线的斜率单调变化时，切到的点是否合法也是单调的，因此不用二分点，直接二分切线的斜率就够了。

因此我们得到了一个 $O(n \log n)$ 做法，[代码（官方代码）](https://atcoder.jp/contests/arc168/submissions/47619573)。

---

## 作者：EuphoricStar (赞：6)

尝试二分答案，问题变为要求恰好选 $x$ 段 $\ge s$，最大化选的段数。

发现我们不是很会算段数的 $\max$，考虑给每个段 $[l, r]$ 一个长度减一即 $r - l$ 的代价，于是变成了算代价的 $\min$。

设 $f(x)$ 为分成的若干段中包含恰好 $x$ 个 $\ge s$ 段，每一段 $[l, r]$ 的代价定义为 $r - l$，代价的 $\min$。那么一个答案 $x$ 合法当且仅当 $f(x) \le n - k$。若一段 $< s$ 那么它没有贡献，所以最优的情况一定是一个数自成一段，代价就是 $0$。于是我们只用考虑 $\ge s$ 的代价之和。

发现 $f(x)$ 下凸（感性理解就是选的段的代价会越来越大），那么 $(x, f(x))$ 构成一个下凸包的右半边（即斜率 $> 0$ 的部分）。套路地 wqs 二分斜率 $k$，选一个 $\ge s$ 段的代价变成 $r - l - k$，在此基础上求选出若干段的代价 $\min$ 和在取到这个 $\min$ 的前提下至少选了多少段即可。

上面那个问题显然可以 dp 求出。dp 数组单调，所以只用考虑最近的一个合法转移点转移过来（即对于每个 $i$ 满足 $\sum\limits_{k = j}^i a_k \ge s$ 的最小的 $j$）即可。

预处理每个位置的最近合法转移点，总时间复杂度 $O(n \log^2 n)$。

[code](https://atcoder.jp/contests/arc168/submissions/48841659)

---

## 作者：xxzx (赞：5)

划分成 $k$ 段这种限制，思考 wqs 二分，但是段数和关于划分段数的函数并不是凸的。

考虑选出 $x$ 段两两不相交的合法连续段(和 $\ge s$)，连续段长度和为 $len$，则它能划分出的段数为集合 $[x,x+n-len]$。对于 $x(x\le k)$，需要满足的条件即 $x+n-len\ge k$，将 $x$ 的贡献分给每一个连续段，限制相当于 $\sum(r-l)\le n-k$。

设 $f_x$ 为选出 $x$ 个合法连续段的方案中 $\sum(r-l)$ 的最小值。答案即最大的 $x$，满足 $f_x\le n-k$。

可以发现，$f_x$ 关于 $x$ 是下凸的。

感性理解：先选代价小的连续段，选越多的连续段，代价越大。

证明：设 $f_x$ 对应的划分方案中极短连续段的标号为 $a_1,\dots,a_x$，$f_{x+2}$ 对应的划分方案中极短连续段的标号为 $b_1,\dots,b_{x+2}$。若 $a$ 中不存在一个连续段完全包含 $b$ 中的一个连续段，则 $b$ 中最多只有 $x+1$ 个连续段，矛盾。因此，$a,b$ 中的连续段一定存在包含关系。考虑最左端被包含的两个连续段，一定形如 $a_i$ 包含 $b_{i}$。则可以分成 $a_1,\dots,a_{i-1},b_{i+1},\dots,b_{x+2}$ 和 $b_{1},\dots,b_{i},a_{i},\dots,a_{x}$ 两组，且满足组内连续段两两互不相交。因此 $2f_{x+1}\le f_x+f_{x+2}$，即函数下凸。

注意到 wqs 二分时，二分到的直线可能同时与多个点相切，且左半段的点合法，右半段不合法，先找到满足最左端点合法的最大斜率，此时，直线上最右端点一定是不合法的端点，一个个往后找点，碰到不合法点就退出，那么过程中的点都一定在直线上，跳一个点是 $O(1)$ 的。具体实现见代码。

时间复杂度 $O(n \log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=3e5+10;
ll n,K,s,sum[N];
int a[N],pre[N];
pair<ll,ll> f[N];
bool check(int k) {
    for(int i=1;i<=n;i++) {
        f[i]=f[i-1];
        if(pre[i]>=0) f[i]=min(f[i],{f[pre[i]].first+i-pre[i]-1-k,f[pre[i]].second+1});
    }
    return (f[n].first+f[n].second*k<=n-K);
}
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>K>>s;
    for(int i=1;i<=n;i++) cin>>a[i], sum[i]=sum[i-1]+a[i];
    for(int i=1,p=0;i<=n;i++) {
        while(sum[i]-sum[p]>=s) p++;
        pre[i]=p-1;
    }
    int l=0, r=n;
    while(l+1<r) {
        int mid=(l+r)/2;
        if(check(mid)) l=mid;
        else r=mid;
    }
    check(l);
    int x=min(f[n].second,K), y=f[n].first+f[n].second*l;
    while(y+l<=n-K&&x<K) x++, y+=l; // 多个合法点可能都在直线 y=lx 上
    cout<<x<<endl;

    return 0;
}
```

---

## 作者：dead_X (赞：5)

## 思路
首先你发现 $<K$ 的段显然分成长度为 $1$ 是最优的，将分成 $M$ 段改成至少分成 $M$ 段就和原题面等价了。

然后钦定选 $x$ 段 $\geq K$，至少分成的段数 $f(x)$ 显然是单调降的，所以可以直接二分。

二分之后是经典套路，再进行一次 wqs 二分即可，记一段的价值是 $1-(r_i-l_i)\cdot d$，二分使得最优决策的段数 $\geq x$ 的时候 $d$ 尽量大，就可以取到最小的 $\sum(r_i-l_i)$ 了。

时间复杂度 $O(n\log n\log a)$。
## 代码
```cpp
// Problem: E - Subsegments with Large Sums
// Contest: AtCoder - ALGO ARTIS Programming Contest 2023 Autumn（AtCoder Regular Contest 168）
// URL: https://atcoder.jp/contests/arc168/tasks/arc168_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//泥の分際で私だけの大切を奪おうだなん
#include<bits/stdc++.h>
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
using namespace std;
#define int long long
#define ld long double
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int to[1000003];
int a[1000003];
pair<int,int> f[1000003];
int n=read(),m=read(),k=read();
int chk(int d)
{
	ld l=0,r=1;
	int A=0,B=0;
	while(r-l>1e-9)
	{
		ld mid=0.5L*(l+r);
		auto F=[&](pair<int,int> x)
		{return x.first+x.second*mid;};
		auto G=[&](pair<int,int> x,int k)
		{auto [y,z]=x;return make_pair(y+1,z-k);};
		for(int i=1; i<=n; ++i)
		{
			f[i]=f[i-1];
			if(a[i]>=k)
			{
				if(F(G(f[to[i]],i-to[i]))>F(f[i]))
					f[i]=G(f[to[i]],i-to[i]);
			}
             else puts("HaitangSuki");
		}
		if(f[n].first>=d)
			A=f[n].first,B=f[n].second,l=mid;
		else r=mid;
	}
	if(A<d) return -1;
	while(A>d) --A,B+=round(1.0/l);
	return A+n+B;
}
signed main()
{
	for(int i=1; i<=n; ++i) a[i]=a[i-1]+read();
	for(int i=1; i<=n; ++i)
	{
		to[i]=to[i-1];
		while(a[i]-a[to[i]+1]>=k) ++to[i];
	}
	int l=1,r=0,ans=0;
	for(int i=n; a[i]>=k; i=to[i]) ++r;
	r=min(r,m);
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(chk(mid)>=m) ans=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：JWRuixi (赞：4)

### 题意

给定序列 $\{a_n\}$，两个参数 $k, S$，求将序列划分为 $k$ 段，最大化和 $\ge S$ 的段数。

$k \le n \le 2.5 \times 10^5, a_i \le 10^9, S \le 10^{15}$。

### 分析

这一类的分段最优化问题都可以直接考虑 DP，朴素 DP 需要记录的信息分为三类：考虑了哪些点、分了几段、有几段产生贡献。直接记录复杂度 $\mathcal O(n^2)$，优化尝试去掉其中一维。

这些信息显然时没有决策单调性的，所以考虑是否存在凸性。如果记录前两个信息是无法优化的，我们尝试记录一、三，维护二。

我们考虑只保留有贡献的段，设区间 $[l_i, r_i]$ 的代价为 $C_i = r_i - l_i$。那么相当于找到最大的 $x$，是的划分出 $x$ 段不交的区间，满足 $f(x) = \sum\limits_{t = 1}^x C_t \le n - k$。可以设计 $dp_{i, j}$：考虑 $1 \sim i$，贡献为 $j$，$f(j)$ 的最小值。

设 $g(x) = \min f(x)$，直觉上 $g(x)$ 关于 $x$ 是存在凸性的，因为肯定是先取优的在取劣的。证明：假设一种 $g(p)$ 的方案区间分别是 $X_{1 \sim p}$，对应的起点分别是 $x_{1 \sim p}$；一种 $g(p + 2)$ 的方案区间分别是 $Y_{1 \sim p + 2}$，对应的起点分别是 $y_{1 \sim p + 2}$。

引理 $1$：$X, Y$ 两种方案间不存在完全包含关系，若区间 $X_i \subset Y_i$，那么令 $Y_i \gets X_i$ 一定更优，与最有方案的定义相悖。

引理 $2$：如果 $\exists i, x_i \le y_{i + 1} < y_{i + 2} \le x_{i + 1}$，则 $x_1, \dots, x_{i}, y_{i + 2}, \dots, y_{p + 2}$ 和 $y_1, \dots y_{i + 1}, x_{i + 1}, \dots x_{p}$ 分别是两种合法的 $f(p + 1)$ 的方案（由引理 $1$ 显然）。

不妨假设 $x_0 = y_0 = 0, x_{p + 1} = y_{p + 3} = n + 1$，显然 $y_1 > x_0$，如果 $\not \exists x_i \le y_{i + 1} < y_{i + 2} \le x_{i + 1}$，则 $\forall i, x_i \le y_{i + 1}$。于是有 $n + 1 = x_{p + 1} \le y_{p + 2} \le n$，矛盾，所以必然存在引理 $2$ 所述情景。所以 $2g(p + 1) \le g(p) + g(p + 2)$，$(p, g(p))$ 的图像是凸的。

我们考虑对图像进行 wqs 二分，最后进行局部微调（一个斜率可以对应多个点）。设计 $dp_i$ 维护 $1 \sim i$，最小代价、以及代价最小的前提下最少选多少个区间。因为贪心策略告诉我们产生贡献的区间是极小的和 $\ge S$ 的子段，所以转移点只有一个。

复杂度 $\mathcal O(n\log n)$。

### Code

提交记录：<https://atcoder.jp/contests/arc168/submissions/50269443>。

---

## 作者：Z1qqurat (赞：3)

退役 whk 选手跑来修锅了/ll，之前的版本有个地方错完了。

### wqs 二分图像形式

wqs 二分，又称为带权二分，可以概括为**凸优化，（带权）二分斜率**，具体啥意思？来看它的一般形式：

> 有一些物品，每个物品有权值，设 $F(x)$ 为恰好选了 $x$ 个物品时的最大/小总权值，满足 $F(x+1)-F(x)\le F(x)-F(x-1)$，也就是说在方案最优的情况下，选择一个新的最优物品的贡献单调不增/不减，$F(x)$ 呈凸性。每次求一个具体的 $F(x)$ 的时候就可以使用 wqs 二分了。接下来我们都只考虑下凸的情况，而上凸是类似的。

举个例子：Luogu P2619。

这里我们设 $F(x)$ 表示恰好选择 $x$ 条白色边的最小生成树权值。考虑到一定存在这么一个 $t$ 使得 $\forall x\le t$，每次都存在一条可选白边的权值小于目前最大的可替换黑边，所以这一段的 $F(x)\downarrow$；而对于 $\forall x>t$，每次新选一条白边都只能使得边权和更大了，所以 $F(x)\uparrow$。那么就是说，**$F$ 是一个下凸函数。**

我们现在要求出 $F(need)$ 的值，考虑这样一件事情：**对于一个下凸的函数图像 $F$，每一种特定斜率的直线中至多有一条和 $F$ 相切，而且随着这个斜率的增长，这个切点的横坐标递增。**

这很显然吧！画个图就明白了。

![](https://pic.imgdb.cn/item/65f5860d9f345e8d037f7c09.png)

那么考虑到这条性质，我们如果能够快速求出某个斜率下直线和凸壳的切点，就可以通过这个切点坐标判断要减小/增大当前枚举的直线斜率，容易发现这其实是一个单调性，考虑直接二分直线斜率，然后 check 的时候求出切点坐标就能得出切点处的 $F$ 值。

这里容易发现，其实对于一个凸包顶点 $(x,y)$，和凸包切于它的直线应该有很多条，且这些直线的斜率一定是连续的。而在满足点都是整点的情况下对每个 $(x,y)$ 一定可以找到一个斜率为整数的切线，所以二分 $k$ 的时候只二分整数就能保证正确性并且降低复杂度。

考虑怎么求出已知斜率的直线和凸壳的切点位置：考虑 $(x,y)$ 的图像含义，指刚好有 $x$ 条白边，权值和为 $y$ 的生成树。**其实就是说要找到一个合适的 $b$ 使得 $y=kx+b$ 和凸壳相切，而容易发现，这就是在找一个最小的 $b$ 使得存在一个凸壳上的横坐标 $x$ 满足 $F(x)=kx+b\Rightarrow b=F(x)-kx$，就是在求最小的 $F(x)-kx$ 值**（类似地，如果是一个上凸函数，那么就是要找到最大的 $b$ 使得存在 $F(x)=kx+b$，也就是要求出 $F(x)-kx$ 的最大值）。这相当于给每条白边额外加上 $-k$ 的附加权值，求出的最小生成树边权和就是最小的 $F(x)-kx$。于是我们二分斜率 $k$，然后给所有白边加上 $-k$ 的附加权值，如果最后求出的最小生成树白边数 $>need$（也就是切点的横坐标大于询问点的横坐标，说明要左移），$k$ 要减小；否则 $k$ 要增大。最终得到的 $y=kx+b$ 与凸包的交点横坐标就是 $need$。

![](https://pic.imgdb.cn/item/65f586139f345e8d037f9f3c.png)

一个细节，如果有白边黑边权值相等的情况怎么办？试着白边优先选择，那么最后可能出现这样的情况：$cnt(k-1)<need,cnt(k)>need$，其中 $k$ 是当前斜率，$cnt$ 表示最小生成树内的白边数，而由于题目保证有解，这种情况一定可以通过将若干条白边替换为黑边的情况转化为可行解。复杂度 $\mathcal{O}(m\log m \log V)$，其中 $m\log m$ 是 Kruskal 的复杂度，$V$ 取边权值域即可。（注意实际上二分的值域要是 $[-V,V]$，斜率可能为负数）。

[Submission.](https://www.luogu.com.cn/record/147738382)

### 简单应用 ARC168E

> 简要题意：有一个长度为 $n$ 的序列 $a$，现在要求将其划分为恰好 $m$ 个非空段，最大化这些段中 $a$ 和 $\ge s$ 的段数。
> 数据范围：$1\le m\le n\le 2.5\times 10^5$，$1\le a_i\le 10^9,1\le s\le 10^{15}$。

看起来很像 wqs 二分的形式：选择一些物品，然后对选择的物品的类型有一些限制。设 $F(x)$ 表示恰好划分为 $x$ 段时，$\ge s$ 的段数最大值。发现它不是凸的，考虑二分答案，转化问题形式：二分出当前的 $\ge s$ 段数 $need$，那么记函数 $F(x)$ 表示选了 $x$ 个 $\ge s$ 不交连续段，能将整个序列划分为的最大段数。这么做是因为如果能划分为 $y$ 段且有 $x$ 个 $\ge s$ 不交连续段，那么划分为 $x\le y'<y$ 段时能得到的 $\ge s$ 不交连续段至少也有 $x$ 个。所以如果满足 $F(x)\ge m$，那么当前二分的 $x$ 就是可行的。

问题就在于给定一个 $x$，怎么求 $F(x)$。发现这个贡献不太好计算，换一种刻画方式：记 $G(x)$ 为选了 $x$ 个 $\ge s$ 不交连续段，所划分为的段产生的贡献总和最小值。设划分出来的一个段 $[l,r]$ 产生的贡献为 $r-l$，那么 $F(x)=n-G(x)$。容易发现如果确定了选出的 $x$ 个 $\ge s$ 不交连续段，那么剩下未选入的点在划分中一定独立成段，这样才能最大化 $F(x)$，而这些段对 $G(x)$ 的贡献就是 $0$。所以 $G(x)$ 实际上只需要记录选出的 $x$ 个 $\ge s$ 不交连续段产生的贡献总和。这时候容易发现 $G(x)$ 是下凸的。

于是我们可以使用 wqs 二分来求 $G(x)$，每次二分的斜率 $k$ 相当于就是给选择的每个连续段将权值改为 $r-l-k$，然后求最小的贡献和。容易想到一个 dp，设 $f_i$ 表示考虑了前 $i$ 个位置，选出若干个不交的 $\ge s$ 连续段产生的最小贡献和。那么每次只需要考虑 $i$ 是否被选到某个连续段里面了，没选就是 $f_{i-1}$，选了就是从最大的满足 $j\le i,\sum\limits_{p=j}^i a_j\ge s$ 的 $j$，对应的 $f_{j-1}+i-j-k$ 转移而来（基于 $a_i\ge 1$），这样预处理转移点就可以 $\mathcal{O}(n)$ dp了。问题是还要求出取到 $f_n$ 的横坐标也就是此时所选的连续段数量，dp 的时候顺便维护一个满足最小化当前 $f_i$ 前提且选的段数最小的量即可。wqs 二分的 check 是 $\mathcal{O}(n)$ 的，wqs 二分的斜率范围是 $\mathcal{O}(n)$，外层二分答案值域 $\mathcal{O}(m)$，总复杂度 $\mathcal{O}(n\log n\log m)$。

[Submission.](https://atcoder.jp/contests/arc168/submissions/48841659)

---

## 作者：orz_z (赞：3)

套路地考虑 `wqs` 二分，记 $f(x)$ 表示分成 $x$ 段，$\ge s$ 的段数的最大值。

但是发现，$\ge s$ 的段可以拼上旁边一个小段，构成一段坐标系上的横条，所以 $f(x)$ 其实并不是凸的。

由上的性质，可以知道，答案关于 $k$ 具有单调性，我们尝试定义 $g(x)$ 表示 $\ge s$ 的段有 $x$ 个的情况下，划分的最大段数。

但是最大段数的计算需要涉及到已选的段长，我们重新定义 $g(x)=\sum_{i=1}^{x} r_i-l_i$ 即 $\ge s$ 的段的长度减一的和的最小值，若 $g(x)\le n-k$，则我们声称可以划分成 $k$ 段。

感性理解起来，$g(x)$ 特别容易凸，于是我们对 $g$ 进行 `wqs` 二分，`dp` 记录前缀最小代价及对应下的最小个数，转移考虑从以当前点为右端点的最近合法点转移即可。

时间复杂度 $\mathcal O(n\log^2 n)$。

```cpp
// LUOGU_RID: 139532006
//#pragma GCC optimize("Ofast,no-stack-protector")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
//#pragma GCC optimize("Ofast,fast-math")
//#pragma GCC target("avx,avx2")
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
//#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
 #define int long long
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;
#define F(i, a, b) for(int i = a; i <= (b); ++i)
#define F2(i, a, b) for(int i = a; i < (b); ++i)
#define dF(i, a, b) for(int i = a; i >= (b); --i)
template<typename T> void debug(string s, T x) {
	cerr << "[" << s << "] = [" << x << "]\n";
}
template<typename T, typename... Args> void debug(string s, T x, Args... args) {
	for (int i = 0, b = 0; i < (int)s.size(); i++) if (s[i] == '(' || s[i] == '{') b++;
	else if (s[i] == ')' || s[i] == '}') b--;
	else if (s[i] == ',' && b == 0) {
		cerr << "[" << s.substr(0, i) << "] = [" << x << "] | ";
		debug(s.substr(s.find_first_not_of(' ', i + 1)), args...);
		break;
	}
}
#ifdef ONLINE_JUDGE
#define Debug(...)
#else
#define Debug(...) debug(#__VA_ARGS__, __VA_ARGS__)
#endif
#define pb push_back
#define fi first
#define se second
#define Mry fprintf(stderr, "%.3lf MB\n", (&Med - &Mbe) / 1048576.0)
#define Try cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
typedef long long ll;
// namespace Fread {const int SIZE = 1 << 17; char buf[SIZE], *S, *T; inline char getchar() {if (S == T) {T = (S = buf) + fread(buf, 1, SIZE, stdin); if (S == T) return '\n';} return *S++;}}
// namespace Fwrite {const int SIZE = 1 << 17; char buf[SIZE], *S = buf, *T = buf + SIZE; inline void flush() {fwrite(buf, 1, S - buf, stdout), S = buf;} inline void putchar(char c) {*S++ = c;if (S == T) flush();} struct NTR {~NTR() {flush();}} ztr;}
// #ifdef ONLINE_JUDGE
// #define getchar Fread::getchar
// #define putchar Fwrite::putchar
// #endif
inline int ri() {
	int x = 0;
	bool t = 0;
	char c = getchar();
	while (c < '0' || c > '9') t |= c == '-', c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return t ? -x : x;
}
inline void wi(int x) {
	if (x < 0) {
		putchar('-'), x = -x;
	}
	if (x > 9) wi(x / 10);
	putchar(x % 10 + 48);
}
inline void wi(int x, char s) {
	wi(x), putchar(s);
}
bool Mbe;
// mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
const int mod = 998244353;
const int inf = 0x3f3f3f3f;
const ll infll = 0x3f3f3f3f3f3f3f3f;
const int _ = 3e5 + 5;

int n, k, s, a[_], sum[_], pre[_];

pii f[_];

void work(int x) {
	F(i, 1, n) {
		f[i] = f[i - 1];
		if(pre[i]) f[i] = min(f[i], make_pair(f[pre[i] - 1].fi + (i - pre[i]) - x, f[pre[i] - 1].se + 1));
	}
}

bool chk(int lim) {
	int l = 1, r = n, mid, res = 0;
	while(l <= r) {
		mid = (l + r) >> 1;
		work(mid);
		if(f[n].se <= lim) l = mid + 1, res = mid;
		else r = mid - 1;
	}
	work(res);
	return f[n].fi + res * lim <= n - k;
}

bool Med;
signed main() {
	// Mry;
	n = ri(), k = ri(), s = ri();
	F(i, 1, n) a[i] = ri(), sum[i] = sum[i - 1] + a[i];
	int l = 0;
	F(i, 1, n) {
		while(sum[i] - sum[l] >= s) l++;
		pre[i] = l;
	}
	l = 1;
	int r = k, ans = 0;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(chk(mid)) l = mid + 1, ans = mid;
		else r = mid - 1;
	}
	cout << ans << '\n';
	// Try;
	return 0;
}
```



---

## 作者：Loser_Syx (赞：2)

不妨二分答案 $x$，不难发现存在单调性，两段合法的可以合并成一段。

于是题目转化成了，划分 $x$ 段 $\geq s$ 的是否可行。

容易发现选 $x$ 段的这种题一般都存在凸的函数，所以我们使用 wqs 二分。

我们定义 $g_i$ 表示有 $i$ 段 $\geq k$ 的最小代价，代价可以用 $r - l$ 来定义。

这时就不难发现 $g_i = \sum_{j=1}^i r_j-l_j$ 是凸的，wqs 二分便可以用上了。

对应二分的 check 可以考虑使用 `pair` 存储最小代价和最小个数进行 dp，$i$ 可以从最左边的合法点转移而来，这个可以预处理。

二分答案的 $x$ 如果满足条件便有 $g_n \leq n - k$。

复杂度 $O(n \log^2 n)$。

```cpp
const int N = 3e5 + 19;
pii dp[N]; int L[N], a[N];
signed main() {
	int n = read(), k = read(), s = read();
	for (int i = 1; i <= n; ++i) read(a[i]);
	for (int i = 1; i <= n; ++i) a[i] += a[i-1];
	for (int i = 1; i <= n; ++i) {
		L[i] = L[i-1];
		for (; a[i] - a[L[i]] >= s; ++L[i]); 
	}
	int l = 1, r = k + 1;
	auto go = [&](int x) -> void {
		for (int i = 1; i <= n; ++i) {
			dp[i] = dp[i-1]; 
			if (L[i]) dp[i] = min(make_pair(dp[L[i] - 1].F + i - L[i] - x, dp[L[i] - 1].S + 1), dp[i]);
		}
	};
	auto check = [&](int x) -> bool {
		int pl = 1, pr = n + 1;
		while (pl < pr) {
			int pmid = (pl + pr) >> 1;
			go(pmid);
			if (dp[n].S <= x) pl = pmid + 1;
			else pr = pmid;
		} go(--pl);
		return dp[n].F + pl * x <= n - k;
	};
	while (l < r) {
		int mid = (l + r) >> 1;
		if (check(mid)) l = mid + 1;
		else r = mid;
	} write(l - 1, '\n');
	return 0;
}
```

---

## 作者：冷却心 (赞：1)

wqs 二分好题。

看到恰好分成 $k$ 段，于是往 wqs 二分去想，如果记 $f(k)$ 表示分成 $k$ 段的答案，你会发现这个不是凸的，然后我就烧烤半天毫无头猪。

换个地方考虑，我们发现答案是有单调性的，我们记 $f(x)$ 表示答案为 $x$，即选出正好 $x$ 个和大于 $S$ 的区间是最多能分成多少段，则 $f(x)$ 是递减的，我们需要找到最大的 $x$ 满足 $k\leq f(x)$。于是我们考虑二分答案 $x$，从而变成一个判定性问题：从序列中选出大于等于 $x$ 段和大于 $S$ 的区间，能否有一种方案使得区间总数大于 $k$。所以这里区间总数越大越好，于是有轻微贪心，我们记 $p_i$ 表示最后一个到 $i$ 的区间和大于等于 $S$ 的位置，那么如果选择一个合法区间以 $i$ 结尾，那么一定左端点是 $p_i$，而非小于 $p_i$，并且除了合法区间以外的区间一定是单个数，这样选择的个数最多。这个 $p_i$ 可以直接双指针。

我们不妨想想如何清新地刻画这个区间个数，我们记一个区间的权值为其长度减一，那么你对原序列的一种划分区间方案中所有区间的权值之和就是 $n$ 减去区间个数。于是我们的判定变成了：把序列划分成 $k$ 段，并且有恰好 $x$ 段和大于 $S$ 的区间，求所有区间的权值之和最小值。如果最小值小于等于 $n-k$ 说明 $x$ 合法，否则不合法。

然后考虑这个子问题，发现我们记 $g(i)$ 表示当 $x=i$ 时上面这个问题的最小值，发现这是个凸函数（依照主流观点，向下凸出，是个下凸壳）。于是上 wqs 二分即可。

感性理解一下凸性，即证 $g(i+1)-g(i)\geq g(i)-g(i-1)$。我们考虑这两次的决策，反证法，如果 $g(i+1)-g(i)< g(i)-g(i-1)$，也就是说，当前第 $i+1$ 次选择的区间的贡献小于第 $i$ 次选择的区间，因为我们要求的是最小值，那么显然前者可以在第 $i$ 次就选择，使得 $g(i)$ 减小，从而使得 $g(i)-g(i+1)\leq g(i-1)-g(i)$。

笔者代码实现中与上述描述唯一不同的是我记录的是 $p_i - 1$ 而不是 $p_i$。

[https://atcoder.jp/contests/arc168/submissions/63405440](https://atcoder.jp/contests/arc168/submissions/63405440)。

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc168_e)

**题目大意**

> 给定 $a_1\sim a_n$，将其分成 $k$ 个非空区间，最大化元素和 $\ge s$ 的区间个数。
>
> 数据范围：$n\le 2.5\times 10^5$。

**思路分析**

作为一道数列分段题，先观察代价函数，发现 $w(l,r)=[\sum_{i=l}^r a_i\ge s]$ 不具有四边形不等式，答案也没有凸性。

但我们可以进行一些观察，对于元素和 $<s$ 的区间，很显然只要长度为 $1$ 保证非空即可。

因此可以二分，假设有 $x$ 个区间 $\ge s$，那么他们占据的总长度不超过 $n-(k-x)$。

我们只要计算分 $x$ 个 $\ge s$ 的段时，区间总长的最小值，发现最小总长关于 $x$ 有凸性，此时就可以 wqs 二分了。

时间复杂度 $\mathcal O(n\log^2n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2.5e5+5;
int n,k,pre[MAXN];
ll S,sum[MAXN];
array <ll,2> dp[MAXN];
array<ll,2> wqs(ll p) {
	dp[0]={0,0};
	for(int i=1;i<=n;++i) {
		dp[i]=dp[i-1];
		if(~pre[i]) dp[i]=min(dp[i],{dp[pre[i]][0]+i-pre[i]-p,dp[pre[i]][1]+1});
	}
	return dp[n];
}
bool chk(int x) {
	int l=1,r=n,z=0;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(wqs(mid)[1]<=x) z=mid,l=mid+1;
		else r=mid-1;
	}
	return wqs(z)[0]+1ll*x*z<=n-(k-x);
}
signed main() {
	scanf("%d%d%lld",&n,&k,&S);
	for(int i=1;i<=n;++i) scanf("%lld",&sum[i]),sum[i]+=sum[i-1];
	for(int i=1,j=-1;i<=n;++i) {
		while(sum[i]-sum[j+1]>=S) ++j;
		pre[i]=j;
	}
	int l=1,r=k,z=0;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(chk(mid)) z=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",z);
	return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

通过标签点进来的，建议洛谷完善近期 $\rm CF$ 和 $\rm AT$ 的标签系统。

第一反应肯定是对外层的 $k$ 使用 $\rm wqs$ 二分——但是随便打个表都发现，没有凸性。那么考虑二分答案，求出如果我们强制性要求分成 $k$ 段 $\ge s$ 的区间，那么可以剩下多少个元素。显然最优策略是把这些元素单独成段。

如果我们想求出 $dp_{t}$ 为把序列分为 $t$ 个 $\ge s$ 的区间最多能有多少段，那么对于一段 $[l,r]$ 的区间，我们实际上损失了 $r-l$ 段：所以我们要最小化 $\sum r-l$。发现这时候后 $dp$ 对于 $t$ 有凸性，就可以 $\rm wqs$ 二分了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=250000+10;
int n,k,s,mx,tmp,a[MAXN],dp[MAXN],len[MAXN];
void solve(int dt) {
	memset(dp,0x3f,sizeof(0x3f)),memset(len,0,sizeof(len));
	dp[0]=len[0]=0;
	int tpos=0;
	ffor(i,1,n) {
		dp[i]=dp[i-1],len[i]=len[i-1];	
		if(a[i]>=s) {
			while(a[i]-a[tpos+1]>=s) tpos++;
			if(make_pair(dp[tpos]+i-tpos-1-dt,-len[tpos]-1)<make_pair(dp[i],-len[i])) dp[i]=dp[tpos]+i-tpos-1-dt,len[i]=len[tpos]+1;
		}
	}
	return ;
}
int calc(int cnt) {
	int l=0,r=n,ans=0x3f3f3f3f;
	while(l<=r) {
		int mid=l+r>>1;
		solve(mid);
		if(len[n]>=cnt) ans=dp[n]+mid*cnt,r=mid-1;
		else l=mid+1;
	}
	return ans;
}
int bfind(int l,int r) {
	int ans=0,mid;
	while(l<=r) {
		mid=l+r>>1;
		if(n-calc(mid)>=k) ans=mid,l=mid+1;
		else r=mid-1;	
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k>>s;ffor(i,1,n) cin>>a[i],a[i]+=a[i-1];
	cout<<min(bfind(1,n),k);
	return 0;
}
```

---

## 作者：Aigony (赞：0)

想到了 wqs 二分并不影响我不会 /ng

二分答案 $x$。则我们要在恰好有 $x$ 段 $\ge S$ 的情况下最大化选择的段数。发现 $x$ 越大至多能选的段数越少，因此有单调性。

最大化段数这个目标很奇怪，考虑转化：令一段 $[l,r]$ 的权值为 $r-l$，目标变为最小化权值和。在这步转化后，我们发现对于一个和小于 $S$ 的段，如果把它拆成一个数一段则可以对答案贡献为 $0$。也就是说，仅需考虑 $\ge S$ 的段的权值对答案的贡献。

此时的限制条件仍有两维，无法直接 dp，考虑用 wqs 二分降维。

设 $f(x)$ 表示恰好 $x$ 段 $\ge S$ 时的最小权值和，感性理解：因为我们是从小往大选段的，$x$ 越大，新选一段所需要的代价就越大。因此 $f(x)$ 下凸。

二分斜率 $k$，令一段的权值为 $r-l-k$，dp 最小化权值的同时记录至少选取的段数。由于选多了一定不合算，$dp_i$ 只会从前面最近的合法的 $j$ 转移，预处理即可 $\mathcal{O}(1)$ 转移。

总时间复杂度为 $\mathcal{O}(n\log^2 n)$。

---

## 作者：jr_zch (赞：0)

# Subsegments with Large Sums

## 题目大意

给定一个序列，要求分为 $k$ 段，令第 $i$ 段和为 $sum_i$，求可能的 $\sum_{i=1}^k [sum_i \geq s]$ 的最大值。

## 解题思路

绝大多数人在做这道题的时候看见了分为 $k$ 段的关键词，便想直接上 $\text{wqs}$ 二分。

有显然的 $\text{DP}$：

设 $f_{i,j}$ 表示前 $i$ 个项，分了 $j$ 段，满足要求的段数最大值。

原序列 $a$ 的前缀和为 $b$。

$$
f_{i,j}=\max_{k=0}^{i-1} (f_{k,j-1}+[b_i-b_k \geq s])
$$

$f_{n,i}$ 并不具有凸性，随便手玩发现 $f_{n,i}$ 前半段是一条直线，后半段是一个阶梯：

![](https://cdn.luogu.com.cn/upload/image_hosting/zx2yapy5.png)

所以不能直接套 $\text{wqs}$ 二分。

到这里有一种方向是去尝试贪心地选择一些和 $\geq s$ 的段，使得这样的段数最多的情况下，未被选择的空闲点数也尽量多，这样就可以处理出后面阶梯的下降点位置了。

尝试了几种策略之后，容易发现这样的最优划分不那么容易直接贪出来，这里很容易误入歧途，所以一定要多画多找反例。

不如返璞归真，无路可走的时候再读一遍题，发现答案是单调的。

考虑二分答案，问题变为将序列分为 $k$ 段，使得和 $\geq s$ 的段数至少为 $mid$ 段是否可行。

不如反向思考，先选 $mid$ 段合法区间，再看空闲点是否有至少 $k-mid$ 个，也就是互换 $\text{DP}$ 状态的第二维和值。

预处理每个右端点 $i$ 对应的最近的，和 $\geq s$ 的左端点位置 $l_i$，这样我们就得到了所有 $n$ 个合法区间。

设 $f_{i,j}$ 表示前 $i$ 个数，选了 $j$ 个互不相交的合法区间，空闲点最多有多少个。

$$
f_{i,j}=\max_{k=0}^{i-1}(f_{k,j-1}+(l_i-k-1))~|~l_i>k
$$

感性理解，每次选择合法区间时，一定会选当前能选的最短的区间来使得空闲点尽量的多，所以原函数差分递减，满足凸性。

严谨证明的话直接设 $w(k,i)=l_i-k-1$，易证 $w$ 满足四边形不等式，所以原函数具有凸性。

直接套 $\text{wqs}$ 求就可以了，时间复杂度 $O(n \log_2 n \log_2 V)$。

回顾算法流程，在内层二分的时候，我们其实有很多的信息没有利用起来，对于二分到的任意一个切点，我们都已经可以直接判断这个点是否合法。

所以直接二分斜率，判断该斜率对应的切点是否合法，省去了一层二分，时间复杂度 $O(n \log V)$。

注意这里需要特殊讨论一下三点共线的情况，按照正常的 $\text{wqs}$ 二分流程，我们每次让权值相同时的区间段数尽量少，那么最后得到的是共线的点中最靠左的点。

由于这些点所对应的截距相同，尝试去右移答案点再判定即可。

## $\text{Code}$：

### $O(n \log_2 n \log_2 V)$：$581 \text{ms}$
```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int maxn=2.5e5+7;
int n,k,lim,cnt;
int a[maxn],s[maxn],lpos[maxn],f[maxn],g[maxn];

void dp(int val){
	for(int i=1;i<=n;i++) f[i]=g[i]=0;
	for(int i=1;i<=n;i++){
		if(lpos[i]>0){
			f[i]=f[lpos[i]-1]-val;
			g[i]=g[lpos[i]-1]+1;
		}
		if(f[i-1]+1>f[i]){
			f[i]=f[i-1]+1;
			g[i]=g[i-1];
		}else if(f[i-1]+1==f[i]) g[i]=min(g[i],g[i-1]);
	}
	return ;
}

bool check(int x){
	int l=-3e5,r=3e5,res=0,c=0;
	//wqs 二分 
	while(l<=r){
		int mid=l+r>>1ll;
		dp(mid);
		if(g[n]<=x) res=f[n],c=mid,r=mid-1;
		else l=mid+1;
	}
	return res+x*c>=k-x;
}

signed main(){
	memset(lpos,-1,sizeof(lpos));
	scanf("%lld%lld%lld",&n,&k,&lim);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),s[i]=s[i-1]+a[i];
	for(int i=1;i<=n;i++){
		lpos[i]=upper_bound(s,s+i,s[i]-lim)-s;
		if(lpos[i]>0) cnt++;
	}
	//二分答案 
	int l=0,r=min(k,cnt),ans=0;
	while(l<=r){
		int mid=l+r>>1ll;
		if(check(mid)) l=mid+1,ans=mid;
		else r=mid-1;
	}
	printf("%lld",ans);
	return 0;
}
```

### $O(n \log_2 V)$：$70 \text{ms}$

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int maxn=2.5e5+7;
int n,k,lim,cnt;
int a[maxn],s[maxn],lpos[maxn],f[maxn],g[maxn];

bool check(int x){
	for(int i=1;i<=n;i++) f[i]=g[i]=0;
	for(int i=1;i<=n;i++){
		if(lpos[i]>0){
			f[i]=f[lpos[i]-1]-x;
			g[i]=g[lpos[i]-1]+1;
		}
		if(f[i-1]+1>f[i]){
			f[i]=f[i-1]+1;
			g[i]=g[i-1];
		}else if(f[i-1]+1==f[i]) g[i]=min(g[i],g[i-1]);
	}
	if(g[n]>min(k,cnt)) return 0;
	//判断该切点是否合法 
	return f[n]+g[n]*x>=k-g[n];
}

signed main(){
	memset(lpos,-1,sizeof(lpos));
	scanf("%lld%lld%lld",&n,&k,&lim);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),s[i]=s[i-1]+a[i];
	for(int i=1;i<=n;i++){
		lpos[i]=upper_bound(s,s+i,s[i]-lim)-s;
		if(lpos[i]>0) cnt++;
	}
	int l=-3e5,r=1,ans=0,fans=0,c=0;
	while(l<=r){
		int mid=l+r>>1ll;
		if(check(mid)) r=mid-1,c=mid,fans=f[n],ans=g[n];
		else l=mid+1;
	}
	//尝试将切点右移 
	for(int i=ans+1;i<=min(k,cnt);i++) if(fans+c*i>=k-i) ans=i;
	printf("%lld",ans);
	return 0;
}
```

---

