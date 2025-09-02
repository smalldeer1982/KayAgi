# PermuTree (hard version)

## 题目描述

This is the hard version of the problem. The differences between the two versions are the constraint on $ n $ and the time limit. You can make hacks only if both versions of the problem are solved.

You are given a tree with $ n $ vertices rooted at vertex $ 1 $ .

For some permutation $ ^\dagger $ $ a $ of length $ n $ , let $ f(a) $ be the number of pairs of vertices $ (u, v) $ such that $ a_u < a_{\operatorname{lca}(u, v)} < a_v $ . Here, $ \operatorname{lca}(u,v) $ denotes the [lowest common ancestor](https://en.wikipedia.org/wiki/Lowest_common_ancestor) of vertices $ u $ and $ v $ .

Find the maximum possible value of $ f(a) $ over all permutations $ a $ of length $ n $ .

 $ ^\dagger $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

The tree in the first test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1856E2/b4446034dab04a6ae6c9b21c7c1f4229d9a4c572.png)One possible optimal permutation $ a $ is $ [2, 1, 4, 5, 3] $ with $ 4 $ suitable pairs of vertices:

- $ (2, 3) $ , since $ \operatorname{lca}(2, 3) = 1 $ and $ 1 < 2 < 4 $ ,
- $ (2, 4) $ , since $ \operatorname{lca}(2, 4) = 1 $ and $ 1 < 2 < 5 $ ,
- $ (2, 5) $ , since $ \operatorname{lca}(2, 5) = 1 $ and $ 1 < 2 < 3 $ ,
- $ (5, 4) $ , since $ \operatorname{lca}(5, 4) = 3 $ and $ 3 < 4 < 5 $ .

The tree in the third test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1856E2/d99652a679d9214ec6283dd777f9d3b7f1434695.png)The tree in the fourth test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1856E2/1b3604b93549da62e326378a176bbc03c4448da2.png)

## 样例 #1

### 输入

```
5
1 1 3 3```

### 输出

```
4```

## 样例 #2

### 输入

```
2
1```

### 输出

```
0```

## 样例 #3

### 输入

```
6
1 2 2 1 5```

### 输出

```
7```

## 样例 #4

### 输入

```
4
1 1 1```

### 输出

```
2```

# 题解

## 作者：ღꦿ࿐ (赞：23)

此处假设读者已经通过 E1，会 $O(n^2)$ 地解决本问题：

在每一个点时做的操作就是“把儿子大小构成的数集合分成差尽可能小的两部分”。

接下来来解决 E2：

首先一个观察就是单个问题“把儿子大小构成的数集合分成差尽可能小的两部分”是一个 $\sum siz_i \leq n$ 的背包可行性问题。没有 $O(n\log n)$ 的做法，常见的做法有三种：

- $\sum siz_i \leq n$ 所以 $siz_i $ 的种类只有 $\sqrt n$ 种，直接做余数分类  $O(n\sqrt n)$。
- 将每种 $siz_i$ 的个数进行二进制拆分，然后 ``bitset`` 压位复杂度 $O(\dfrac{n\sqrt n \log n} w)$，常数很小。
- 多项式卷积，NTT 或 FFT 合并，$O(n\log^2n)$，常数大。

令上方解决规模 $n$ 单层问题的复杂度为 $C(n)$。

如果每层都解决一次这样的问题，复杂度仍然是 $\sum C(siz_i)$ 的，这最坏仍然可以达到 $O(n^2)$。 

因为树 $siz$ 的构成是具有特殊性的，解决完这个问题后子问题的规模和这个问题的构成是密切相关的 （这显然弱于解决任意 $n$ 次上面问题）。

又因为我们只是想尽可能平均分两个集合，所以当重儿子的 $siz$ 大于其它儿子的 $siz$ 之和时，一定会选择将重儿子放在一个集合中，所有轻儿子放在另一集合，所以只有重儿子的 $siz$ 小于目前 $siz$ 的一半时我们才会进行背包，而如果重儿子的 $siz$ 小于目前 $siz$ 的一半，然后所有子问题的规模都变成了原来的一半，所以最坏复杂度为 $T(n)=2T(n/2)+C(n)$。



带入具体复杂度分析都是简单的主定理：


如果 $C(n)=O(n\sqrt n)$，$T(n)=2 T(n/2)+O(n\sqrt n)=O(n\sqrt n)$。

如果 $C(n)=O(\dfrac{n\sqrt n \log n} w)$，$T(n)=2 T(n/2)+O(\dfrac{n\sqrt n \log n} w)=O(\dfrac{n\sqrt n \log n} w)$。

如果 $C(n)=O(n \log^2 n)$，$T(n)=2 T(n/2)+O(n\log^2 n)=O(n\log^3n)$。

第三种理论最优，但是在题目数据范围下使用第二种，最坏耗时约 300ms，可以轻松通过。


一个实现上的小问题是需要使用动态大小的 ``bitset``，可以选择手写或者提前开好所有大小为 $2^k$ 的 ``bitset``，然后使用的时候选择最小的可用的。

[这里是代码](https://codeforces.com/contest/1856/submission/217355793)。



upd：可以证明更优秀的复杂度：直接进行二进制拆分的复杂度其实是 $C(n)=T(n)=O(\dfrac{n\sqrt n} {w})$ 的，具体的复杂度分析见 [这里](https://www.luogu.com.cn/blog/wangxiwen/solution-cf1856e2) 或者 [这里](https://atcoder.jp/contests/abc269/editorial/4854)，感谢 [@王熙文](https://www.luogu.com.cn/user/353688) 的指出，Orz。

---

## 作者：王熙文 (赞：18)

从题解区看来好像大家都觉得官方题解的思路是 $\mathcal O(\dfrac{n\sqrt{n}\log n}{w})$ 的，但是它其实没有 $\log $，下文会证明复杂度。

## 思路

假设读者已经知道了 E1 的思路。

题目可以转化成对于每个点将它的子树内所有点黑白染色，使得颜色不同且不在同一个当前节点的儿子的子树内的对数最大，求最大的对数的总和。

首先有一个结论：存在一个最优解使得当前点的每个儿子子树内的节点颜色相同。

证明：一个儿子子树内的节点对答案的贡献只与子树外的点有关，因此这个子树内的点在外面状态不变的情况下染黑或白的贡献是固定的，所以节点颜色一定相同。

此时又可以发现，因为每个儿子子树内的节点颜色都相同，所以对对数的限制，“不在同一个当前节点的儿子的子树内”就没有用了，因此现在可以将问题转化成了：将每个儿子的子树大小划分成两个集合，使得集合元素之和的积最大。

现在可以考虑求出来所有第一个集合的可能元素之和。这是一个经典的背包问题。将这个问题形式化表述：

> 当前有 $n$ 个物品，每个物品有重量 $a_i$。设 $m=\sum a_i$，请对于每个 $d \in [0,m]$ 求出是否可以选出一个集合 $S$ 使得 $\sum_{i|S} a_i = d$。

下面主要参考了 CF 上的[这篇博客](https://codeforces.com/blog/entry/98663)。

首先可以发现，不同的 $a_i$ 只有 $\mathcal O(\sqrt{m})$ 种。因为如果 $a_i > \sqrt{m}$，这样的 $i$ 一定 $\le \sqrt{m}$ 个。

因此现在将物品变成了有 $\sqrt{m}$ 个物品，每个物品有重量 $a_i$ 和出现次数 $c_i$。

接下来可以将 $c_i$ 进行二进制优化。将 $c_i$ 拆成 $2^0+2^1+\cdots + 2^{k_i} + x_i$，其中 $x_i < 2^{k_i+1}$，然后将这 $c_i$ 个物品变成 $k_i+2$ 个物品，重量为原先的重量乘上拆分出来对应的数。

拆分后，用 `bitset` 优化 dp 即可。使用 $vis$ 表示前 $i$ 个物品能凑出来哪些数，转移到 $i+1$ 时直接让 $vis$ 或上 $vis$ 左移 $a_{i+1}$ 即可。

这样做的复杂度看起来是 $\mathcal O(n+\dfrac{m\sqrt{m}\log m }{w})$ 的，但是我们可以证明，物品只有 $\mathcal O(m\sqrt{m})$ 个。

首先 $x_i$ 对应的物品只有 $\mathcal O(m\sqrt{m})$ 个。接下来考虑对每个 $2^j$ 对应的物品个数。设 $c_i$ 能拆分出 $2^j$ 的 $i$ 集合为 $S_j$。因为 $2^j$ 是被拆分出来的，所以 $\sum_{i \in S_j} 2^j \cdot a_i \le m,\sum_{i \in S_j} a_i \le \dfrac{m}{2^j}$。又因为 $a_i$ 互不相同，所以 $|S_j| \le \sqrt{\dfrac{2C}{2^j}}$。

那么 $\sum_{j} |S_j| \le \sqrt{2C}\sum_{j}\dfrac{1}{\sqrt{2^j}}$。考虑后面的求和，就是 $\dfrac{1}{\sqrt 1} + \dfrac{1}{\sqrt 2} + \dfrac{1}{\sqrt 4}+\dfrac{1}{\sqrt 8} + \cdots$。注意到 $\left(\dfrac{1}{\sqrt 1} + \dfrac{1}{\sqrt 4} + \cdots \right)=\left( 1+\dfrac{1}{2} +\cdots \right)< 2$，而 $\left(\dfrac{1}{\sqrt 2} + \dfrac{1}{\sqrt 8} + \cdots \right)< \left(\dfrac{1}{\sqrt 1} + \dfrac{1}{\sqrt 4} + \cdots\right)$，所以 $\sum_{j}\dfrac{1}{\sqrt{2^j}}<4$，$\sum_{j} |S_j| \le 4\sqrt {2C}$，是 $\mathcal O(\sqrt{C})$ 级别。

因此物品个数是 $\mathcal O(\sqrt{C})$ 级别，上述算法的复杂度为 $\mathcal O(n+\dfrac{m\sqrt m}{w})$。

回到原问题，我们现在仅仅以 $\mathcal O(\sum_v \dfrac{siz_u\sqrt{siz_u}}{w})$ 的时间解决了一个节点的问题，如果要求所有节点，这个复杂度还不行。

考虑如果有一个节点的一个儿子的子树大小占到了当前节点的子树大小一半，即 $2siz_v \ge siz_u-1$，选择方案一定为只选择当前儿子放到第一个集合，剩下的放到第二个集合。其他情况，递归下去的子树大小至少减半，递归树层数是 $\mathcal O(\log n)$。这样看来，好像还需要加一个 $\log$，但是实际上还是不用。

考虑计算递归树的第 $i$ 层的复杂度（根节点位于 $0$ 层）。设位于第 $i$ 层的节点集合为 $S_i$，这一层的运算量为 $T(i)=\sum_{j \in S_i} \dfrac{siz_j\sqrt{siz_j}}{w}$。因为每递归一层 $siz$ 至少除以二，所以 $T(i) \le \sum_{j \in S_i} \dfrac{siz_j\sqrt{\large\frac{n}{2^i}}}{w}=\dfrac{\sqrt n}{\sqrt 2^i w} \sum_{j\in S_i}siz_j \le \dfrac{n\sqrt n}{\sqrt2^i w}$。

对 $T(i)$ 求和即为整个算法的运算量：$\sum_i T(i) \le \sum_i \dfrac{n\sqrt{n}}{\sqrt 2^i w} = \dfrac{n\sqrt n}{w} \sum_i \dfrac{1}{\sqrt 2^i}$。考虑后面的求和，就是 $\sum_i \dfrac{1}{\sqrt{2^i}}$。上文已经分析过，$\sum_i \dfrac{1}{\sqrt{2^i}}<4$，所以 $\sum_i \dfrac{1}{\sqrt 2^i}<4$，$\sum_i T(i) \le \dfrac{4n\sqrt n}{w}$，算法复杂度为 $\mathcal O(\dfrac{n\sqrt n}{w})$。

## 代码

这题的一个细节是，对于每一个问题的 `bitset` 需要开动态的空间，但是 `bitset` 只能开静态的空间。有两种解决办法，一种是像下面给出的代码一样手写 `bitset`，另一种是使用神秘的 `template`，详见官方题解。

```cpp
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include<bits/stdc++.h>
using namespace std;
int n; vector<int> e[1000010];
int siz[1000010];
int cnt[1000010];
unsigned long long vis[(1000000>>6)+10];
void lshift(int n,int x)
{
	if((x&63)==0)
	{
		for(int i=n; i>=(x>>6); --i) vis[i]|=vis[i-(x>>6)];
	}
	else
	{
		for(int i=n; i>=(x>>6); --i)
		{
			int wzl=(i<<6)-x;
			vis[i]|=(wzl<0?0:vis[wzl>>6]>>(wzl&63))|(vis[(wzl>>6)+1]<<(64-(wzl&63)));
		}
	}
}
long long ans=0;
void dfs(int u)
{
	siz[u]=1;
	int ax=0;
	for(int v:e[u]) dfs(v),siz[u]+=siz[v],ax=max(ax,siz[v]);
	if(ax*2>=siz[u]-1) ans+=1ll*ax*(siz[u]-1-ax);
	else
	{
		for(int v:e[u]) ++cnt[siz[v]];
		memset(vis,0,((siz[u]-1>>6)+5)*8);
		vis[0]=1;
		for(int v:e[u])
		{
			if(cnt[siz[v]]==0) continue;
			int now=1;
			while(now<=cnt[siz[v]])
			{
				lshift(siz[u]-1>>6,siz[v]*now);
				cnt[siz[v]]-=now,now*=2;
			}
			if(cnt[siz[v]]!=0) lshift(siz[u]-1>>6,siz[v]*cnt[siz[v]]);
			cnt[siz[v]]=0;
		}
		int mid=(siz[u]-1)/2;
		for(int i=0; ; ++i)
		{
			if(vis[mid+i>>6]>>(mid+i&63)&1) { ans+=1ll*(mid+i)*(siz[u]-1-mid-i); break; }
			if(vis[mid-i>>6]>>(mid-i&63)&1) { ans+=1ll*(mid-i)*(siz[u]-1-mid+i); break; }
		}
	}
}
int main()
{
	ios::sync_with_stdio(false),cin.tie(0);
	cin>>n;
	for(int i=2; i<=n; ++i)
	{
		int f; cin>>f;
		e[f].push_back(i);
	}
	dfs(1);
	cout<<ans;
	return 0;
}
```

---

## 作者：EnofTaiPeople (赞：9)

我们需要对于每个节点，最大化其夹在某两个不同儿子的子树内节点的对数。

不需要出现一个子树里，有些比自己大，有些比自己小的情况，因为在其他子树固定时，这棵子树取比自己大或小的贡献是已知的，我们肯定会全部选贡献较大的那一个。

设比自己大的子树集合为 $S$，比自己小的子树集合为 $T$，则答案为 $\sum\limits_{a\in S,b\in T}sz_asz_b=(\sum\limits_{a\in S}sz_a)(\sum\limits_{b\in T}sz_b)$，问题变成了将儿子划分成两个集合，使其尽量接近，也即小一些的集合更接近 $A=\lfloor{\dfrac{sz_x-1}2}\rfloor$，这可以视作一个背包问题。

如果重儿子大小超过 $A$ 我们可以直接让重儿子作为集合 $S$，其他节点作为集合 $T$，否则所有儿子大小均会翻倍，这样所有的节点最多 $O(\log n)$ 次，所以此时的 $O(sz_x)$ 的计算是可以接受的。

发现这个背包并没有特殊性质，我曾猜测从大往小，加上之后不超过 $A$ 就加上，这样是错的，因为这个背包没有任何特殊性！

唯一就是元素大小之和较小，这里用分治 $NTT$ 可能摊不掉复杂度会达到 $O(n\log^3n)$，根本无法接受，于是思考暴力背包会在什么时候被卡掉，事实上一个菊花图就没了（$sz_a=1$ 的出现次数好多），于是得出将出现多次的绑在一起跑多重背包，因为最多只会有 $O(\sqrt{sz_x})$ 的本质不同大小，用类似单调队列优化（注意是类似，并不需要单调队列）的方法，可以做到 $O(sz_x^{1.5})$ 众所周知等比幂是可以摊的，于是总时间复杂度为 $O(n\sqrt n)$。

官方题解是二进制分组后用 `std::bitset` 优化，也是可行的，时间复杂度为 $O(\dfrac{n\sqrt n\log n}w)$ 比我的算法似乎更优，但由于 `std::bitset` 常数较大并且会卡满（常数不能除以二），所以实际速度不一定优，而且还需要使用模板库倍增尝试的……科技？

形如以下代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+6;
template<int len=1>void sol(int n){
    if(len<=n)return sol<min(len*2,N)>(n);
    bitset<len>st;st[n-1]=1;
}
int n;
int main(){
    cin>>n,sol(n),puts("AC");
    return 0;
}
```

可以倍增尝试 `std::bitset` 的大小是否合适，注意这是 `C++14` 才有的语法，使用 `C++11` 会编译错误，我认为将这个作为标算是**不合适的**。

[场上 AC 记录](https://codeforces.com/contest/1856/submission/217321012)

---

## 作者：Pengzt (赞：4)

[CF1856E2](https://www.luogu.com.cn/problem/CF1856E2)

默认已会 E1。

考虑对 E1 进行优化，发现瓶颈在于背包。

设当前子树以 $u$ 为根，容易发现 $\sum siz_{v_i}=siz_u-1$，显然要从这里下手。发现总值域较小是与普通背包不同的地方，要么个数少，要么值域小。不妨设背包的总容量为 $W$，则超过 $\sqrt{W}$ 的数不超过 $\sqrt{W}$ 个，即不同的物品最多只有 $\sqrt{W}$ 个，可直接化为多重背包，二进制拆分后再使用 bitset 即可，但这里比较特殊，时间复杂度为 $\dfrac{m\sqrt{m}}{w}$。

但这个复杂度依然是错误的，当树退化为一条链时就会被卡死。

类似于树剖的思想，当其重儿子的 $siz$ 大于等于 $\lfloor\dfrac{siz_u-1}{2}\rfloor$ 时可以直接 $\mathcal{O}(1)$ 做，否则就像前一种方法，但这时候所有的点的 $siz$ 都至少会变为 $siz_u$ 的一半，根据主定理，易得时间复杂度为 $\mathcal{O}(\dfrac{m\sqrt{m}}{w})$。

关于这里的多重背包的时间复杂度的具体证明可以看[这篇](https://www.luogu.com.cn/blog/wangxiwen/solution-cf1856e2)

[评测记录](https://codeforces.com/contest/1856/submission/218453076)

---

## 作者：hanjinghao (赞：4)

# 思路
提供一种时间复杂度为 $ O(n \sqrt n) $ 的做法。

我们的目标是对于每一个点，把它的子树划分成两个集合 $ S $ 和 $ T $，使得 $ S $ 中的子树大小之和与 $ T $ 中的子树大小之和的乘积最大。显然，我们要让两个集合中的子树大小之和尽可能接近。

对于广义的集合划分问题，我们只能用朴素的 $ 0/1 $ 背包来解决。但是这个问题有一个特殊性质—— $ x $ 的所有子树的大小之和等于 $ siz_x  - 1 $。这意味着，不同的大小最多只有 $ O(\sqrt {siz_x}) $ 种。因此，问题可以被转化为有 $ O(\sqrt {siz_x}) $ 种不同的物品，背包容量为 $ siz_x - 1 $ 的多重背包问题。具体地，我们可以在处理每一种物品的时候，把容量按照模它的大小的余数分组，用前缀和优化转移。

这还不够，我们还需要运用启发式合并的思想。我们把最大的子树拎出来（如果有多个，那就一起拎出来），对于其他子树，做一遍多重背包。最后统计答案的时候，尽可能往 $ \lfloor siz_x / 2 \rfloor $ 去凑。具体实现可以参考代码。

对于单个节点 $ x $，这么做的时间复杂度是 $ O((siz_x - 1 - maxsiz_x) \sqrt {siz_x - 1 - maxsiz_x}) $，其中，$ maxsiz_x $ 表示 $ x $ 的最大的子树的大小。

由主定理可知，总时间复杂度 $ T(n) = 2T(n / 2) + O(n \sqrt n) = O(n \sqrt n) $。

此外，我们还有一个小优化——当一个点的子树个数不超过 $ 4 $ 的时候，直接枚举划分方式。再加上快读，可以在三秒内通过。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

char buf[1000005];
int ppos, llen;

inline char gch()
{
	if (ppos == llen)
	{
		ppos = 0;
		llen = fread(buf, 1, 1000000, stdin);
	}
	if (ppos == llen) return -1;
	return buf[ppos++];
}

template < typename T >
inline const void read(T &x)
{
	bool flg = x = 0;
	char c;
	while ((c = gch()) < 48 || c > 57)
		flg |= c == '-';
	do
		x = (x << 1) + (x << 3) + (c ^ 48);
	while ((c = gch()) > 47 && c < 58);
	if (flg) x = -x;
}

const int N = 1e6 + 5;
int siz[N], cnt[N], s[N];
bool f[N], vis[N];
vector < int > G[N];

template < typename T >
inline void Chkmax(T &x, T y)
{
	if (y > x) x = y;
}

int main()
{
	int n;
	read(n);
	for (int i = 2; i <= n; ++i)
	{
		int x;
		read(x);
		G[x].emplace_back(i);
	}
	long long ans = 0ll;
	for (int i = n; i; --i)
	{
		siz[i] = 1;
		if (G[i].empty()) continue;
		if (G[i].size() == 1)
		{
			siz[i] += siz[G[i][0]];
			continue;
		}
		if (G[i].size() == 2)
		{
			siz[i] += siz[G[i][0]] + siz[G[i][1]];
			ans += (long long)siz[G[i][0]] * siz[G[i][1]];
			continue;
		}
		if (G[i].size() == 3)
		{
			siz[i] += siz[G[i][0]] + siz[G[i][1]] + siz[G[i][2]];
			ans += max((long long)siz[G[i][0]] * (siz[G[i][1]] + siz[G[i][2]]), max((long long)siz[G[i][1]] * (siz[G[i][0]] + siz[G[i][2]]), (long long)siz[G[i][2]] * (siz[G[i][0]] + siz[G[i][1]])));
			continue;
		}
		if (G[i].size() == 4)
		{
			siz[i] += siz[G[i][0]] + siz[G[i][1]] + siz[G[i][2]] + siz[G[i][3]];
			long long mxn = (long long)siz[G[i][0]] * (siz[i] - 1ll - siz[G[i][0]]);
			Chkmax(mxn, (long long)siz[G[i][1]] * (siz[i] - 1ll - siz[G[i][1]]));
			Chkmax(mxn, (long long)siz[G[i][2]] * (siz[i] - 1ll - siz[G[i][2]]));
			Chkmax(mxn, (long long)siz[G[i][3]] * (siz[i] - 1ll - siz[G[i][3]]));
			Chkmax(mxn, (long long)(siz[G[i][0]] + siz[G[i][1]]) * (siz[G[i][2]] + siz[G[i][3]]));
			Chkmax(mxn, (long long)(siz[G[i][0]] + siz[G[i][2]]) * (siz[G[i][1]] + siz[G[i][3]]));
			Chkmax(mxn, (long long)(siz[G[i][0]] + siz[G[i][3]]) * (siz[G[i][1]] + siz[G[i][2]]));
			ans += mxn;
			continue;
		}
		int mxsiz = 0;
		for (auto &j : G[i])
		{
			if (siz[j] > mxsiz) mxsiz = siz[j];
			++cnt[siz[j]];
			siz[i] += siz[j];
		}
		int sum = siz[i] - 1 - mxsiz * cnt[mxsiz];
		f[0] = 1;
		for (int j = 1; j <= sum; ++j)
			f[j] = 0;
		for (auto &j : G[i])
		{
			int cur = siz[j];
			if (cur != mxsiz && cnt[cur] && !vis[cur])
			{
				vis[cur] = 1;
				for (int k = 0; k < cur; ++k)
					s[k] = f[k];
				for (int k = cur; k <= sum; ++k)
				{
					s[k] = s[k - cur];
					if (f[k]) ++s[k];
				}
				int num = cur * (cnt[cur] + 1);
				for (int k = cur; k < num; ++k)
					if (!f[k])
					{
						if (s[k - cur]) f[k] = 1;
					}
				for (int k = num; k <= sum; ++k)
					if (!f[k])
					{
						if (s[k - cur] - s[k - num]) f[k] = 1;
					}
			}
		}
		int half = (siz[i] >> 1);
		long long maxn = 0ll;
		for (int j = min(sum, half); ~j; --j)
			if (f[j])
			{
				int tmp = min((half - j) / mxsiz, cnt[mxsiz]);
				int num = j + tmp * mxsiz;
				Chkmax(maxn, (long long)num * (siz[i] - 1ll - num));
				if (tmp != cnt[mxsiz])
				{
					++tmp;
					num += mxsiz;
					Chkmax(maxn, (long long)num * (siz[i] - 1ll - num));
				}
			}
		ans += maxn;
		for (auto &j : G[i])
			vis[siz[j]] = cnt[siz[j]] = 0;
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：EuphoricStar (赞：3)

考虑局部贪心，假设我们现在在 $u$，我们希望 $u$ 不同子树中的 $(v, w), a_v < a_u < a_w$ 的对数尽量多。

我们实际上只关心子树内 $a_u$ 的相对大小关系，不关心它们具体是什么。如果 $u$ 只有两个儿子 $v, w$，我们可以让 $v$ 子树内的 $a$ 全部小于 $w$ 子树内的 $a$，这样 $u$ 作为 $\text{LCA}$ 的贡献是 $sz_v \times sz_w$，是最大的。

那么对于 $u$ 有多个儿子的情况，推广可知相当于把 $u$ 的儿子分成 $S, T$ 两个集合，最大化 $\sum\limits_{v \in S} sz_v \times \sum\limits_{v \in T} sz_v$。考虑做一个 $sz_v$ 的 01 背包，若能把 $sz_v$ 分成大小为 $x$ 的集合，$u$ 对答案的贡献是 $x \times (sz_u - 1 - x)$。取这个的最大值即可。

01 背包暴力做即可，根据树形背包的那套理论，每个点对只会在 $\text{LCA}$ 处被统计，所以时间复杂度 $O(n^2)$，[可以通过 E1](https://codeforces.com/contest/1856/submission/217388158)。

对于 E2，我们肯定不能再暴力 01 背包了。发现我我们背包的复杂度跟 $sz_v$ 有关。联想到 dsu on tree，轻子树的大小之和为 $O(n \log n)$。于是我们考虑将 $u$ 的 $sz$ 最大的两个儿子拎出来，剩下的儿子做一个背包，然后再枚举那两个儿子选不选。

至于如何做背包，我们把 $sz_v$ 相同的物品看做一种有多个的物品，做单调队列优化多重背包即可。因为去掉两个最大子树后，$sz_v$ 之和为 $n \log n$，所以不同的 $sz_v$ 有 $O(\sqrt{n \log n})$ 种。

所以这么算下来复杂度其实是 $O(n \sqrt{n \log n} \log n)$，但是[它过了？？？](https://codeforces.com/contest/1856/submission/217389515)

---

## 作者：出言不逊王子 (赞：2)

我们发现这棵树长得很像二叉查找树，所以我们考虑像一棵二叉查找树一样去填数。

具体地，我们假设一棵子树是一个节点，那么我们选择部分节点将一个区间分配进去，填到一半时给根节点赋权值 $x$，剩下的再给其他子树。

这样一来，在根节点产生的贡献就是 $(\sum_{v=\text{son}_u} sz_v[val_v<x])\times (\sum_{v=\text{son}_u} sz_v[val_v>x])$。

根据基本不等式，我们考虑希望让左右两边的部分尽量少。

所以我们现在要解决一个问题：

有 $n$ 个物品，每个物品有重量 $a_i$。你需要选出一些物品，使得选出的物品的重量和与未选的物品的重量和的差的绝对值最小。

这个背包是 $O(n^2)$ 的，所以我们逐步优化。

首先，观察到不同的 $a_i$ 最多 $\sqrt n$ 个，因为 $a_i\le n$。

然后我们把问题转化成多重背包问题，套个二进制优化，复杂度变成了 $O(n\sqrt n)$。

然后我们发现我们只需要求是否满足一种方案，因此我们可以考虑把这个东西上 `bitset`，复杂度又除以了一个 $w$。

但是每次都清空 `bitset` 还是消耗很大，因此我们手写 `bitset`，或者像 `vector` 一样每次手写开出大小为 $2^k$ 的 `bitset` 即可。

---

## 作者：Lates (赞：1)

？？？板刷跳过的题居然能在模拟赛里遇到。

贪心策略是把每个点子树划分为两个集合使得两个集合差值尽量小。

然后他肯定不弱于背包了。就 bitset 上去。

考察扔树上给出的性质，由于 $\sum sz_y = sz_x\le n$，$y$ 是 $x$ 儿子，于是一共只有 $\sqrt n$ 种不同的 $sz_y$。对这个做二进制分组多重背包。

复杂度是 $O(\dfrac{n\sqrt n}{w})$，二进制分组的那个 log 咋没的不知道。不想学证明。

原来写的依托答辩，有没有佬教教这个 template 怎么用。

/bx LJ07

原来 ## 就可以..

还有我的写法要记得预处理 sz。（给自己看的）最后再 dfs 下去。

```cpp
#include <bits/stdc++.h>
#include <assert.h>
using namespace std;
mt19937 rad(time(0));
typedef long long ll;
typedef double db;
#define fin freopen("in.in","r",stdin);
#define fout freopen("out.out","w",stdout);
#define fiout freopen("in.in","w",stdout);
#define ep emplace_back
#define pii pair<int,int>
#define mp make_pair
#define fi first
#define se second
#define dd(x) cerr << #x" = " << x << '\n';
#define clrv(v) vector<int>().swap(v)
inline int read() {
	int x=0,v=1,ch=getchar();
	while('0'>ch||ch>'9') {
		if(ch=='-') v=0;
		ch=getchar();
	}while('0'<=ch&&ch<='9') {
		x=x*10+(ch^'0');
		ch=getchar();
	} return v?x:-x;
}
const int MAX=1e6+555;
int n,sz[MAX];
vector<int> G[MAX];

bitset<32> b32;
bitset<64> b64;
bitset<128> b128;
bitset<256> b256;
bitset<512> b512;
bitset<1024> b1024;
bitset<2048> b2048;
bitset<4096> b4096;
bitset<8192> b8192;
bitset<16384> b16384;
bitset<32768> b32768;
bitset<65536> b65536;
bitset<131072> b131072;
bitset<262144> b262144;
bitset<524288> b524288;

int cnt[MAX];
vector<int> v;
ll ans=0;
void solve(int x,int f);
void dfs(int x,int f) {
	int mx=0;sz[x]=1;
	for(int y:G[x]) if(y^f) dfs(y,x), sz[x]+=sz[y], mx=max(mx, sz[y]);
	if(mx * 2ll >= sz[x] - 1) {
		ans += 1ll * mx * (sz[x] - 1- mx);
	}else {
		solve(x,f);
	}
}
int fa[MAX]; 
void solve(int x,int f) {
	for(int p:v) cnt[p]=0; v.clear();
	for(int y:G[x]) if(y!=f) ++ cnt[sz[y]], v.ep(sz[y]);
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	vector<int> wp;
	for(int i:v) {
		int w=cnt[i],t=1;
		while(w) {
			wp.ep(min(w,t)*i);
			w-=min(w,t);
			t<<=1;
		}
	}
    ll res = 0;
    #define slv(t) \
        b##t=0; \
        b##t[0]=1; \
        for(int v:wp) b##t |= b##t << v; \
        for(int i=0;i<=(sz[x]-1)/2;++i) \
            if(b##t[i]) res = max(res, 1ll * i * (sz[x] - i - 1)); 

    if(sz[x] <= 64) { slv(32) }
    else if(sz[x] <= 128) { slv(64) }
    else if(sz[x] <= 256) { slv(128) }
    else if(sz[x] <= 512) { slv(256) }
    else if(sz[x] <= 1024) { slv(512) }
    else if(sz[x] <= 2048) { slv(1024) }
    else if(sz[x] <= 4096) { slv(2048) }
    else if(sz[x] <= 8192) { slv(4096) }
    else if(sz[x] <= 16384) { slv(8192) }
    else if(sz[x] <= 32768) { slv(16384) }
    else if(sz[x] <= 65536) { slv(32768) }
    else if(sz[x] <= 131072) { slv(65536) }
    else if(sz[x] <= 262144) { slv(131072) }
    else if(sz[x] <= 524288) { slv(262144) }
    else { slv(524288) } 

    ans += res;
}
signed main() {
    // fin;
	n=read();
	for(int i=1;i<n;++i) {
		int u,v;
		u=read(),v=read();
		G[u].ep(v);
		G[v].ep(u);
	}
	dfs(1,0);
	cout << ans;
	// for(int i=2;i<=n;++i) {	
	// 	fa[i]=read();
	// 	G[fa[i]].ep(i);
	// }
	// for(int i=n;i>=1;--i) {
	// 	sz[i] ++;
	// 	sz[fa[i]] += sz[i];
	// } 
	// dfs(1);
	// cout<<ans;
	return 0;
}
```

---

