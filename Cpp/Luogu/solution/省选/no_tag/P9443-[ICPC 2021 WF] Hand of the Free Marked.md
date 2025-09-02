# [ICPC 2021 WF] Hand of the Free Marked

## 题目描述

#### 简要题意
两个人 $A, B$ 玩一个游戏。规则如下 :

$A$ 有 $n$ 张互不相同的牌. 它们的**背面**有 $m$ 种不同的样式, 第 $i$ 种牌有 $a_i$ 张. 二人都对这套牌非常了解. 保证 $\sum\limits^{m}_{i=1}{a_i} = n$.

$B$ 在 $A$ 不在场的情况下从中随机抽出 $k$ 张, 然后选择一张牌倒置在桌面上. 然后 $B$ 可以以任意顺序重新排列其他牌并在桌面上依次排开, 并将倒置的牌放在序列的末尾. $A$ 和 $B$ 可以在游戏之前约定通过其他牌的排列顺序传递的信息.

随后 $A$ 需要根据桌面上牌的排列和倒置牌的背面说出倒置的牌具体是哪一张. 双方的目标都是使 $A$ 说出正确的牌。

现在给定 $m, a_i$ 和 $k$, 求二人均采取最佳策略的情况下, $A$ 的成功率是多少.

## 样例 #1

### 输入

```
4 1 28
```

### 输出

```
0.960000000000
```

## 样例 #2

### 输入

```
3 3 5 12 3
```

### 输出

```
0.854385964912
```

# 题解

## 作者：qiuzx (赞：2)

先考虑经典的 $m=1$ 的问题。此时相当于是对于所有 $k$ 元子集，需要用一个 $k-1$ 个数的排列来表示，满足这 $k-1$ 个数都在这个 $k$ 元子集中出现了。最大化成功的概率就是希望能将尽可能多的 $k$ 元子集映射到 $k-1$ 个数的排列上，使得不存在两个集合映射到同一排列。那么我们将所有 $k-1$ 个数的排列看作左部点，所有 $k$ 元子集看作右部点，一个左部点与右部点之间有边当且仅当左部点代表的排列被右部点代表的集合完全包含，则这张二分图的最大匹配就是我们需要求的值。

但显然我们无法把二分图建出来跑最大匹配。不过注意到这张图是一张半正则二分图，即所有左部点度数均相等，所有右部点度数也均相等。那么根据著名结论，这张图的最大匹配数等于左右两侧较小的点集大小。证明可以不妨设左边点数更少，则应用霍尔定理，那么从任意一个左部点的子集 $S$ 向右会连出去 $|S|d_l$ 条边，其中 $d_l$ 为左部点的度数，而由于每个右部点度数至多为 $d_r$，所以这些边至少对应 $\dfrac{|S|d_l}{d_r}$ 个右部点。因为左部点更少所有 $d_l\ge d_r$，从而 $\dfrac{|S|d_l}{d_r}\ge|S|$，即得证。

有了这个结论就容易做 $m=1$ 的问题了，因为此时所有 $k-1$ 个数的排列总共有 $\displaystyle\binom n{k-1}(k-1)!$ 个，而所有 $k$ 元子集总共有 $\displaystyle \binom nk$ 个，这样就知道了二分图左右两侧点的数量，即容易算出概率。

下面推广到 $m>1$ 的情形，一个想法就是仍然这样建一个二分图，不过此时左部点除了 $k-1$ 个数的排列以外还要额外考虑最后一个的种类。然而这个二分图并不是一个半正则二分图，甚至都不是连通的，所以自然无法直接用刚刚的结论。首先按照每个连通块拆开考虑最后求和，而一个连通块中所有右部点中每个种类在集合中的出现次数相等。换句话说，对于一个序列 $(x_1,\cdots,x_m)$，其中 $x_i$ 表示 $i$ 种类的点选择的个数，那么所有以这个序列作为出现次数的 $k$ 元子集会属于同一个连通块中。

由于 $k,m$ 很小，所以可以 $\displaystyle \binom{2m}m$ 爆搜所有连通块，现在假定确定了 $(x_1,\cdots,x_m)$，考虑如何计算这个连通块的最大匹配呢？注意到这个连通块仍然不是半正则的，因为在最后一张牌的种类不同的情况下，一个左部点可能会连出不同数量的边。不过所有右部点的度数仍然是相等的。此时需要发现这张二分图有一个很好的性质，就是如果我们将最后一张牌种类相同的左部点看作一类的话，那么首先这些点的度数是一样的，其次所有右部点向这些左部点的连边数目也是一样的。

这样我们设每一类不同的左部点分别有 $a_1,\cdots,a_l$ 个，且设每个右部点向每类左部点的连边数目分别为 $d_1,\cdots,d_l$，则反过来一类左部点向右部点的连边数目就是 $\dfrac{|R|d_i}{a_i}$，其中 $|R|$ 表示右部点的点集大小。我们在这张图上应用霍尔定理。如果右部点数目更少，那么对于每个右部点的子集 $S$，其在每一类左部点的出边数目至少为 $|S|d_i$，这样这一类点中相邻的点数目至少为 $\dfrac{|S|a_i}{|R|}$。对这个求和得到总数为 $\dfrac{|S||L|}{|R|}$，其中 $|L|$ 为左部点点集大小。由于左部点更多，所以这个总数不小于 $|S|$，因此存在右边到左边的完美匹配。

否则如果是左边的点更少，那么考虑一个左部点的子集 $S$，假设其在每一类点中分别对应 $S_1,S_2,\cdots,S_l$。那么对于一个 $S_i$ 来说，其到右侧点边数至少为 $\dfrac{|R||S_i|d_i}{a_i}$，从而右侧的点数至少为 $\dfrac{|R||S_i|}{a_i}$。取所有 $i$ 中 $\dfrac{|S_i|}{a_i}$ 最大的一个，假设这个值为 $k$，则 $S$ 向右至少有 $k|R|$ 个邻点。显然总点数 $|S|$ 必然 $\le k|L|$（因为若干不超过 $k$ 的数的加权平均不可能超过 $k$），所以 $|S|$ 不大于相邻的右部点的数量，因此此时存在左边到右边的完美匹配。

这样我们就证明了此时每个连通块的最大匹配数量等于左右两侧点数量的最小值。而左右两侧点的数量容易 $O(m^2)$ 计算，也可以做到 $O(m)$ 但没什么必要。这样爆搜连通块然后每次计算一下点集大小即可，复杂度 $O(\displaystyle\binom{2m}m m^2)$。

``` c++
#include <bits/stdc++.h>
#define INF 1000000000
#define LINF 1000000000000000000
#define MOD 1000000007
#define mod 998244353
#define F first
#define S second
#define ll long long
#define N 20
using namespace std;
long double ans=0,tot=0;
ll k,m,a[N],b[N];
void update()
{
	ll i,j,l;
	long double cur=1,hvs=0;
	for(i=0;i<m;i++)
	{
		for(j=1;j<=b[i];j++)
		{
			cur*=(double)(a[i]-j+1);
			cur/=(double)j;
		}
	}
	tot+=cur;
	for(i=0;i<m;i++)
	{
		if(!b[i])
		{
			continue;
		}
		long double nw=1;
		for(j=0;j<m;j++)
		{
			for(l=1;l<=b[j]-(j==i);l++)
			{
				nw*=(double)(a[j]-l+1);
				nw/=(double)l;
			}
		}
		for(j=1;j<k;j++)
		{
			nw*=(double)j;
		}
		hvs+=nw;
	}
	ans+=min(cur,hvs);
	return;
}
void dfs(ll x,ll s)
{
	if(x==m)
	{
		if(s==k)
		{
			update();
		}
		return;
	}
	ll i;
	for(i=0;i+s<=k&&i<=a[x];i++)
	{
		b[x]=i;
		dfs(x+1,s+i);
	}
	return;
}
int main(){
	ll i;
	cin>>k>>m;
	for(i=0;i<m;i++)
	{
		cin>>a[i];
	}
	dfs(0,0);
	printf("%.16Lf\n",ans/tot);
	return 0;
}

---

## 作者：masterhuang (赞：0)

推销[博客](https://www.cnblogs.com/HaHeHyt/p/17773631.html)！第 $15$ 篇。

下文计算复杂度时设 $k,m$ 同阶。

枚举每种样式选了多少个，设当前考虑的情况为样式 $1\sim m$ 分别选了 $c_{1,2,\cdots, m}$ 个，考虑此时猜中的概率。

先计算选出这种情况的方案数。为 $s=\prod\limits_{i=1}^m \dbinom{a_i}{c_i}$。

考虑**根据桌面上牌**表示的信息情况总数。

前 $k$ 张有 $(k-1)!$ 种排列方式，枚举倒置的牌，计算得：

$(k-1)!\times \sum\limits_{i=1}^ms\times \dfrac{\dbinom{a_i}{c_i-1}}{\dbinom{a_i}{c_i}}=(k-1)!\times \sum\limits_{i=1}^ms\times \dfrac{c_i}{a_i-c_i+1}$。

于是猜中的概率为 $(k-1)!\times \sum\limits_{i=1}^m\dfrac{c_i}{a_i-c_i+1}$，然后要与 $1$ 取 $\min$，直接 $O(m^2)$ 计算即可。

考虑这种情况出现的概率，发现是 $\dfrac{s}{\binom{n}{k}}$，用你喜欢的写法 $O(m^2)$ 算即可。

---

枚举**合法的** $c_{1,2,\cdots, m}$ 的情况直接 **dfs** 做即可，情况数上界为选若干非负整数和为 $k$ 的方案数。即 $\dbinom{k+m-1}{k}$。

当 $k,m$ 同阶时，情况数 $\dbinom{k+m-1}{k}\le \dbinom{2m}{m}$。

总复杂度就是 $O\left(m^2\dbinom{2m}{m}\right)$，随便过。

代码：

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LD long double
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);
using namespace std;
const int N=15;
int k,m,a[N],b[N];LL n;LD ans=1;
inline void calc()
{
	LD s=0;
	for(int i=1;i<=m;i++) s+=(LD)b[i]/(a[i]-b[i]+1);
	for(int i=1;i<k;i++) s*=i;
	if(s>=1) return;s=1-s;
	for(int i=1,K=0;i<=m;i++)
		for(int j=0;j<b[i];j++,K++) s*=(LD)(a[i]-j)/(b[i]-j)*(k-K)/(n-K);ans-=s;
}
void dfs(int v,int x)
{
	if(v==m+1){if(!x) calc();return;}
	for(int i=0;i<=min(a[v],x);i++) b[v]=i,dfs(v+1,x-i);
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);cin>>k>>m;
	for(int i=1;i<=m;i++) cin>>a[i],n+=a[i];
	dfs(1,k);printf("%.12Lf",ans);
	return 0;
}
```

---

