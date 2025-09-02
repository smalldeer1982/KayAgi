# Catch the Mole(Hard Version)

## 题目描述

This is the hard version of the problem. The only difference is the limit on the number of queries.

This is an interactive problem.

You are given a tree of $ n $ nodes with node $ 1 $ as its root node.

There is a hidden mole in one of the nodes. To find its position, you can pick an integer $ x $ ( $ 1 \le x \le n $ ) to make an inquiry to the jury. Next, the jury will return $ 1 $ when the mole is in subtree $ x $ . Otherwise, the judge will return $ 0 $ . If the judge returns $ 0 $ and the mole is not in root node $ 1 $ , the mole will move to the parent node of the node it is currently on.

Use at most $ 160 $ operations to find the current node where the mole is located.

## 说明/提示

In the first test case, the mole is in node $ 2 $ initially.

For the query "? 2", the jury returns $ 1 $ because the mole is in subtree $ 2 $ . After this query, the mole does not move.

The answer $ 2 $ is the current node where the mole is located, so the answer is considered correct.

In the second test case, the mole is in node $ 6 $ initially.

For the query "? 2", the jury returns $ 0 $ because the mole is not in subtree $ 2 $ . After this query, the mole moves from node $ 6 $ to node $ 5 $ .

For the query "? 6", the jury returns $ 0 $ because the mole is not in subtree $ 6 $ . After this query, the mole moves from node $ 5 $ to node $ 4 $ .

For the query "? 4", the jury returns $ 1 $ because the mole is in subtree $ 4 $ . After this query, the mole does not move.

The answer $ 4 $ is the current node where the mole is located, so the answer is considered correct.

Please note that the example is only for understanding the statement, and the queries in the example do not guarantee to determine the unique position of the mole.

## 样例 #1

### 输入

```
2
2
1 2

1

6
1 2
1 3
1 4
4 5
5 6

0

0

1```

### 输出

```
? 2

! 2






? 2

? 6

? 4

! 4```

# 题解

## 作者：Alex_Wei (赞：20)

### [CF1990E2 Catch the Mole(Hard Version)](https://www.luogu.com.cn/problem/CF1990E2)

首先，如果鼹鼠在某个点到根的链上，那么可以通过二分求出答案。

如果鼹鼠在询问结果为 $0$ 时不向上移动，那么最坏情况下需要 $n$ 次询问。这说明利用询问结果为 $0$ 时鼹鼠向上移动的特性是必要的。基本的想法是：如果有 $k$ 个 $0$，那么鼹鼠一定不在最大深度小于 $k$ 的子树内。

我们希望通过询问，将鼹鼠的位置限制在某个点到根的链上。考虑从根到叶子依次确定链的形态：对于当前点，如何确定这条链向哪个儿子延伸呢？

设 $B = \sqrt n$。

**$2B + \log_2 n$：根号分治**

首先选择任意叶子 $x$，询问该叶子。如果结果为 $1$，则答案为 $x$。否则再询问 $B$ 次该叶子，得到 $B + 1$ 个 $0$。这样，任何最大深度不超过 $B$ 的子树都不含鼹鼠。

除去当前点的最大深度不超过 $B$ 的子树，依次询问每棵子树（除最后一棵）。若询问结果为 $1$，则向对应儿子方向延伸。如果所有询问结果均为 $0$，则向最后一个儿子延伸。设儿子个数为 $c$，则我们通过 $c - 1$ 次询问排除了至少 $(c - 1)B$ 个结点，因为每棵子树的大小不小于 $B$。而排除的点的数量不会超过 $n$，所以此部分最多 $\frac n B = B$ 次询问。

**$\sqrt {2}B + \log_2 n$：等差数列求和**

假设还有 $k$ 次询问的机会，且鼹鼠在当前点的某个最大深度小于 $k$ 的子树内，则不需要向该子树延伸，因为就算鼹鼠在子树内，向其它儿子延伸也会使得接下来 $k$ 次询问的结果为 $0$，进而使得鼹鼠最终跳出该子树，跳到当前点到根的路径上。

每次询问会排除掉大小不小于剩余询问次数的子树，并将剩余询问次数减 $1$。设初始询问次数为 $k$，则 $k$ 只需满足 $\sum_{i = 1} ^ k i \geq n$，即 $k\geq \sqrt {2n} = \sqrt 2 B$。[代码](https://codeforces.com/contest/1990/submission/271881888)。

**能不能再给力一点啊？**

考虑鼹鼠所有的可能位置，一定是一个连通块。

设共有 $m$ 个可能位置，询问点为 $x$，其子树内有 $c_x$ 个可能位置，子树外有 $m - c_x$ 个可能位置，子树外的可能位置有 $d_x$ 个叶子。

- 若结果为 $1$，则所有的可能位置为 $x$ 子树内原来的可能位置，$m' = c_x$。
- 若结果为 $0$，则所有的可能位置为 $x$ 子树外原来的可能位置的父结点，$m'\leq m - c_x - d_x + 1$。

设 $f$ 使得 $c_f > m - 2\sqrt m$ 且 $f$ 最小，取 $x$ 为 $f$ 的 $c_x$ 最大的儿子，询问 $x$。

若结果为 $1$，则 $m' = c_x$。因为 $c_x \leq m - 2\sqrt m$，所以 $m'\leq m - 2\sqrt m$。

若结果为 $0$，则 $m' \leq m - c_x - d_x + 1$。因为 $c_x(d_x + 1)\geq c_f - 1 \geq m - 2\sqrt m$，所以 $c_x + d_x + 1 \geq 2\sqrt{m - 2\sqrt m}$。对较大的 $m$ 有
$$
m'\leq m + 2 - 2\sqrt {m - 2\sqrt m} = m + 2 -  2\sqrt {(\sqrt m - 1) ^ 2 - 1}\leq m -  2\sqrt m + 5
$$
由 $1 + 3 + \cdots + (2k - 1) = k ^ 2$ 可知操作次数为 $\sqrt n + O(1)$，在所有测试点上使用的询问次数不超过 $73$。[代码](https://codeforces.com/contest/1990/submission/271897094)。由于数据较水，取阈值为 $\frac m 2$ 也可以使用不超过 $73$ 次询问。

至此达到了本题的询问次数下界：对于每棵子树为长 $\sqrt n$ 的链的星星，最差情况下需要 $\sqrt n$ 次询问才能知道鼹鼠在哪棵子树。

---

## 作者：xiaruize (赞：7)

考虑随机化，设当前可行的点集为 $S$，每次询问从 $S$ 中随机选取一个点，按照题意模拟，直至剩下 $1$ 个点。

上述做法是可以通过的，下面说明操作次数为什么合法。

每次选取一个点，因为当前的老鼠的位置是未知的，所以我们认为回答为 $0$ 和 $1$ 的概率是相等的，而随机选取下，平均每次会使得 $\frac{|S|}{2}$ 个点不合法，所以期望询问次数是 $\mathcal{O}(\log{n})$ 的。虽然随机算法不稳定，但是 $160$ 次仍然足够。

~~望各位大佬手下留情，不要对着卡啊/kk~~

[code](https://codeforces.com/contest/1990/submission/271702428)

---

## 作者：Gold14526 (赞：6)

$\rm Problem(Hard\ Version):$[Catch the Mole](https://www.luogu.com.cn/problem/CF1990E2)

**本篇题解解决了出题人提出的 $100$ 次询问加强版。**

### 题意

**这是一道交互题**

给出一棵 $n$ 个点的树，一个隐藏的鼹鼠在其中一个节点。

每次你可以以 ```? x``` 的格式询问一个节点 $x$。

- 如果返回 $0$，说明鼹鼠不在以 $x$ 为根的子树中。随后，如果鼹鼠不在根节点，那么他会往父节点移动一次。
- 如果返回 $1$，说明鼹鼠在以 $x$ 为根的子树中。

你需要定位这个鼹鼠，以 ```! x``` 的格式回答，说明询问结束之后鼹鼠在 $x$ 节点。

$\rm Easy\ Version:$ 询问次数不超过 $300$ 次。

$\rm Hard\ Version:$ 询问次数不超过 $160$ 次。

$\rm Bonus:$ 询问次数不超过 $100$ 次。

### Hint

1.  如果一次询问的结果为 $0$，你可以删除这棵子树。
2.  如果询问对象是一个叶节点，当返回为 $1$ 时，答案为该节点，否则，鼹鼠将会向上移动一格。
3.  如果一棵子树的返回为 $1$，那么我们可以通过上一条把它赶出这个子树。

### Hard Version

（为方便描述，下面将“以 $x$ 为根的子树”简称作“子树 $x$”）

首先，如果我们已经确定了鼹鼠一定在从根节点开始的一条链上，那么通过二分查找，可以用最多 $13$ 次询问找到这只鼹鼠。

于是，问题变为用 $147$ 次询问如何将其确定在这样一条链上。

定义节点 $x$ 到根的距离为 $dep_x$，到子树 $x$ 内最深的节点的距离为 $ped_x$。

通过 Hint3，不难想到如果我们已经确定了鼹鼠在子树 $x$ 里，那么我们可以通过 $ped_x$ 次操作将其赶出这棵子树，使其在一条满足要求的链上。

考虑每次查询一个 $x$ 使得 $ped_x=\sqrt{n}$，如果返回 $0$ 就删除子树 $x$，否则用 $\sqrt{n}$ 次将鼹鼠赶到一条满足要求的链上，如果没有这样的子树，即所有 $ped_x$ 都小于 $\sqrt{n}$，那么直接用 $\sqrt{n}$ 次使其到达根节点。

不难发现如果删除的话，每次会删除至少 $\sqrt{n}$ 个节点，所以最多只能删 $\sqrt{n}$ 次，所以询问次数最多为 $2\sqrt{n}$，不超过 $141$，足以通过此题。

### Bonus

我们需要通过不超过 $87$ 次操作将鼹鼠赶到一条满足要求的链上。

每次，我们找一个点 $x$，使得以 $x$ 为根的子树为一条链，而且以 $x$ 的父亲为根的子树不为一条链。

这样的好处在于，如果我们确定鼹鼠在子树 $x$ 里，我们无需将其赶出这棵子树，可以直接二分。

如果鼹鼠不在这棵子树里，我们删除这棵子树和所有的叶子节点，然后重复以上操作即可。

不过，这种做法下，我们的时间复杂度为 $O(tn^2)$，高达 $2.5\times10^9$，于是，我们需要优化找符合要求的点 $x$ 的过程。

考虑找一个叶子节点倍增往上跳，用线段树维护子树大小来确定子树 $x$ 是否是一条链，这样最终时间复杂度为 $O(tn\log^2 n)$，足以通过本题。

### 代码

代码拼了许多模板，写得有点长。

```cpp
#include<bits/stdc++.h>
#define cint const int
#define iint inline int
#define ll long long
#define cll const long long
#define ill inline long long
using namespace std;
iint read()
{
	int num=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		num=(num<<1)+(num<<3)+(ch-'0');
		ch=getchar();
	}
	return num;
}
int n;
int head[5001],f[5001][13],a[5001],deg[5001],dfn[5001],l[5001],r[5001];
struct edge{
	int to,nxt;
}e[10000];
int tot;
struct que{
	int a[5001],h,t;
	inline void clear(){h=0,t=-1;}
	inline void push(cint x){a[++t]=x;}
	inline void pop(){++h;}
	iint front(){return a[h];}
	iint size(){return t-h+1;}
	inline bool empty(){return t<h;}
}leaf;
bool query(cint x)
{
	printf("? %d\n",x);
	fflush(stdout);
	return read();
}
inline void add_edge(cint u,cint v)
{
	e[++tot]=edge{v,head[u]};
	head[u]=tot;
	e[++tot]=edge{u,head[v]};
	head[v]=tot;
}
void dfs(cint now)
{
	l[now]=dfn[now]=++tot;
	for(int i=head[now];i;i=e[i].nxt)
	{
		if(e[i].to==f[now][0])continue;
		++deg[now];
		f[e[i].to][0]=now;
		dfs(e[i].to);
	}
	r[now]=tot;
}
inline void init()
{
	for(int k=1;k<=12;++k)
	{
		for(int i=1;i<=n;++i)
		{
			f[i][k]=f[f[i][k-1]][k-1];
		}
	}
	leaf.clear();
	for(int i=1;i<=n;++i)
	{
		if(!deg[i])
		{
			leaf.push(i);
		}
	}
}
namespace A{
	namespace T{
		struct node{
			int l,r,sum;
		}t[20001];
		int idx[5001];
		void Build(cint p,cint l,cint r)
		{
			t[p].l=l;
			t[p].r=r;
			if(l==r)
			{
				t[p].sum=1;
				idx[l]=p;
				return;
			}
			cint mid=l+r>>1;
			Build(p<<1,l,mid);
			Build(p<<1|1,mid+1,r);
			t[p].sum=t[p<<1].sum+t[p<<1|1].sum;
		}
		void build()
		{
			Build(1,1,n);
		}
		inline void update(cint x)
		{
			for(int i=idx[x];i;i>>=1)
			{
				--t[i].sum;
			}
		}
		int Ask(cint p,cint l,cint r)
		{
			if(t[p].l>r||t[p].r<l)return 0;
			if(t[p].l>=l&&t[p].r<=r)return t[p].sum;
			return Ask(p<<1,l,r)+Ask(p<<1|1,l,r);
		}
		int ask(cint l,cint r)
		{
			return Ask(1,l,r);
		}
	}
	iint size(cint x)
	{
		return T::ask(l[x],r[x]);
	}
	iint find(int x)
	{
		int len=1;
		for(int i=12;i>=0;--i)
		{
			if(f[x][i]==0)continue;
			if(size(f[x][i])==len+(1<<i))
			{
				len+=1<<i;
				x=f[x][i];
			}
		}
		return x;
	}
	inline bool check()
	{
		return query(find(leaf.front()));
	}
	inline void del()
	{
		for(int i=leaf.front();;i=f[i][0])
		{
			--deg[i];
			if(deg[i]>0)break;
			T::update(dfn[i]);
		}
		leaf.pop();
		for(int i=leaf.size();i;--i)
		{
			cint x=leaf.front();
			leaf.pop();
			--deg[f[x][0]];
			T::update(dfn[x]);
			if(!deg[f[x][0]])
			{
				leaf.push(f[x][0]);
			}
		}
	}
}
namespace B{
	int find(cint l,cint r)
	{
		cint mid=l+r>>1;
		if(l>=r)return a[mid];
		if(query(a[mid]))return find(l,mid);
		if(a[r]==1)
		{
			if(mid+1==r)return 1;
			return find(mid+2,r);
		}
		return find(mid+2,r+1);
	}
	void solve()
	{
		int x=leaf.front();
		tot=0;
		while(x)
		{
			a[++tot]=x;
			x=f[x][0];
		}
		printf("! %d\n",find(1,tot));
		fflush(stdout);
	}
}
void solve()
{
	n=read();
	for(int i=1;i<=n;++i)
	{
		head[i]=0;
		deg[i]=0;
	}
	tot=0;
	for(int i=1;i<n;++i)
	{
		add_edge(read(),read());
	}
	tot=0;
	dfs(1);
	init();
	A::T::build();
	while(!A::check())A::del();
	B::solve();
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int T=read();
	while(T--)solve();
	return 0;
}
```

---

## 作者：快乐的大童 (赞：6)

### 题意
给你一颗树，大小为 $n$。初始有一颗黑点在树上某个节点，你每次可以查询 $x$ 表示黑点是否在 $x$ 的子树内，且若答案为否则黑点会移动到父亲节点上。你需要在 160 次查询内找到黑点**当前**在哪个节点（不要求求出初始位置）。

$n\le 5000$，Easy Ver. 查询次数 300。
### 分析
由于每次失败的查询（答案为否的查询）会使得黑点上移，考虑设一个阈值 $B=\sqrt n$（叫根号分治可能不太准确），那么在 $B$ 次失败的查询后，如果黑点初始位置和根节点之间的链 $\le B$，那么黑点最终会移动到根节点处。

如果令“长链”表示链长 $>B$ 的链，那么黑点初始在这些“长链”的情况可以通过暴力查询长度恰好为 $B$ 的链端点完成。如果一次查询是失败的，那么黑点不可能出现在查询点的子树内，那么直接把子树删掉就行。每次删掉的点数量至少是 $B$ 个，所以这部分总查询次数不超过 $B$。

如果这些查询全部都是失败的，那么我们最终会剩下若干条最大深度不超过 $B$ 的链，直接暴力查询 $B$ 次叶子，然后返回根节点 1 即可。查询次数 $2\sqrt n$。

如果存在一次查询是成功的，那么此时黑点一定在这棵子树内（~~废话~~），而且子树深度为 $B$。

我们考虑二分出黑点的位置，但是有可能该子树内还存在着多个子树，我们无法确定黑点具体在哪棵子树。此时我们只需要再查询 $B$ 次叶子，由于子树深度为 $B$，那么查询后黑点一定会在根节点到子树根节点的这条链上，那么我们有了具体上下界，就可以二分了。查询次数 $2\sqrt n+\log n$。


---


关于二分：我们二分的是**二分前黑点的位置**，而不是二分时黑点当前的位置，考虑设一个变量 $cnt$ 代表二分时进行了多少次失败的查询，即黑点上移的距离，那么每次二分出 $mid$ 实际上查询的是 $mid$ 的 $cnt$ 级祖先，也就是查询黑点二分前是不是在 $mid$ 的子树里。

实现细节：最开始查询的时候，每进行一次失败的查询，需要删掉一整棵子树，然后求出新的长度为 $B$ 的链的端点。这部分实际上可以 $O(n)$ 暴力 dfs、暴力删除，由于查询次数只有 $\sqrt n$ 次，所以时间复杂度是 $O(Tn\sqrt n)$ 的。同理，二分时由于要查询某点 $k$ 级祖先，实际上也可以暴力。

代码：[https://codeforces.com/contest/1990/submission/271766814](https://codeforces.com/contest/1990/submission/271766814)

---

## 作者：luogu_gza (赞：4)

观察到 $n=5000$，操作次数是 $160$。

发现大致是类似于 $\sqrt n$ 的，尝试了一下发现是 $2 \sqrt n$。

但是貌似还多了 $18$ 次，我们猜测这是 $\log n$。

目标就是 $2 \sqrt n+\log n$。

什么情况下会出现 $2 \sqrt n$ 呢？我猜测这一定是 $B+\frac nB$ 然后均值出来的。

那么目标就是 $\log n+ B + \frac nB$。

---

$\log n$ 明显是二分得到的，不难想到寻找到鼹鼠的行动路径，然后在路径上二分。

我们先让鼹鼠行动 $B$ 次（方法是询问一个叶子 $B$ 次，但是如果我们运气好鼹鼠就在这个叶子上——返回了 $1$，那么直接回答这个叶子即可），这样的话我们搜索时就可以排除掉深度 $<B$ 的子树，因为鼹鼠往上爬了 B 次，不可能在这个子树上。

我们来进行 dfs。

举行了 `dfs(u)` 代表行动路径必定有 $u \to 1$。

+ 如果没有深度 $\geq B$ 的子树，那么其实鼹鼠已经被你抓到了，就在 $u$ 上。

+ 如果有深度 $\geq B$ 的子树，询问子树根，看返回值。如果返回值为 $1$，那么鼹鼠就在这个子树中，继续 dfs 下去。如果搜到最后返回值全部为 $0$，那么很不对劲，其实鼹鼠就在 $u$ 上！

这个方法很深刻，但是会被链干掉，我就是卡在了这一步。

其实你询问到最后一颗子树，如果前面的都“太失望了没有”，那么其实一定在这颗子树上（虽然还可能在 $u$ 上）。

此时理性分析一下发现每次 dfs 可以干掉一个深度 $\geq B$ 的子树（至少有 $B$ 个点）所以这一部分次数是 $\frac nB$。

至此就做完了，算下来的话需要 $155$ 次操作，还留下五次，挺有意思。

代码易，不放了。

---

## 作者：WeWantToRun (赞：3)

大家好，我不知道 $160$ 是什么啊！

考虑每次询问如果得到 $1$，那么可以删除子树外所有点。如果得到 $0$，那么可以删除子树内所有点、所有叶子，同时把当前剩下连通块根节点的父亲（如果有）加回来。

通过贪心的思想，考虑想要效率更高的找到解，于是每次可以询问最坏情况下删除节点数最多的那个点，直到只剩一个点。

感觉上，选择最优的一个点至少能够删除 $2\sqrt N$ 个点。但是在非常多次操作下，不可能把每次操作删除的点都卡到最小。实际上，提交记录中最多的询问次数只有六十多次。

---

## 作者：WaterSun (赞：2)

[更好的阅读体验](https://www.cnblogs.com/WaterSun/p/18324262)

# 思路

我们先随便选择一个叶子结点，查询 $B$ 次。如果是返回的结果是 $1$，说明鼹鼠就在这个叶子结点；否则它将向上跳 $B$ 次。

此时，我们得到一个关键结论，如果一棵子树最大深度小于等于 $B$，那么鼹鼠一定不在这棵子树中，因为鼹鼠无论如何都跳了 $B$ 次。

我们希望找到鼹鼠行动的链，找到了就可以直接二分找到其位置。

令当前到达的节点为 $u$，查询所有 $u$ 的子节点 $v$，并把最大深度小于等于 $B$ 的子树跳掉。当 $v$ 查询出来过后结果为 $1$，说明此时鼹鼠在 $v$ 子树中，向下递归即可。

但是，这样 naive 的想法显然是有问题的，可以被链给创飞。

观察到，当我们即将查询 $u$ 的最后一个满足最大深度大于 $B$ 的子树时，前面所有的子树都不行，那么鼹鼠一定在 $v$ 子树。

这样做的好处就是，每一次递归都会减少一个深度大于 $B$ 的子树，那么最多只会查询 $\frac{n}{B}$ 次。

接下来就只需要在我们找到的这条链上二分即可。

查询次数是 $B + \frac{n}{B} + \log n$ 的，当 $B = \sqrt{n}$ 时取得最小值 $2\sqrt{n} + \log n$。

# Code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 5010;
int n,B;
int d[N];
vector<int> v,g[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline bool ask(int u){
    printf("? %d\n",u); fflush(stdout);
    return read();
}

inline void print(int u){
    printf("! %d\n",u); fflush(stdout);
}

inline void dfs1(int u,int fa){
    d[u] = 1;
    for (int v:g[u]){
        if (v == fa) continue;
        dfs1(v,u); d[u] = max(d[u],d[v] + 1);
    }
}

inline void dfs2(int u,int fa){
    v.push_back(u);
    vector<int> s;
    for (int v:g[u]){
        if (v == fa || d[v] <= B) continue;
        s.push_back(v);
    }
    for (re int i = 1;i < s.size();i++){
        int v = s[i];
        if (ask(v)) return dfs2(v,u);
    }
    if (!s.empty()) dfs2(s.front(),u);
}

inline void solve(){
    v.clear();
    n = read(); B = sqrt(n);
    fill(d + 1,d + n + 1,0);
    for (re int i = 1;i <= n;i++) g[i].clear();
    for (re int i = 1,a,b;i < n;i++){
        a = read(),b = read();
        g[a].push_back(b); g[b].push_back(a);
    }
    for (re int i = 2;i <= n;i++){
        if (g[i].size() == 1){
            for (re int j = 1;j <= B;j++){
                if (ask(i)) return print(i);
            }
            break;
        }
    }
    dfs1(1,0); dfs2(1,0);
    int l = 0,r = v.size() - 1;
    while (l < r){
        int mid = l + r + 1 >> 1;
        if (ask(v[mid])) l = mid;
        else{
            r = max(0,mid - 2);
            if (l) l--;
        }
    }
    print(v[l]);
}

int main(){
    int T; T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：_Kenma_ (赞：2)

# CF1990 E1/E2 解题报告

## 写作背景
赛后 VP，一个小时不到过了 ABCD，发现 E 是交互题 F 是不可做题，遂开摆。

就在开摆时，机房学长走过来并对我口胡了一个~~假~~做法，但这给我了很多的启发，于是开始拼板子。终于在结束前 $10$ min 调完并通过，于是就有了这篇题解。

## 正文

### 思路分析

由于 EV 和 HV 的区别仅在于询问次数的限制，我在打比赛时并没有将两道题割裂开来思考。

我们从询问次数上入手分析。$n$ 为 $5000$，询问次数限制为 $160$ 或 $300$。估测发现我们需要一个询问次数为 $O(\sqrt n)$ 的~~优秀~~做法。

学长给我的启发在于，他提出了一个 $O(\log n)$ 的找重心的类似于点分治的做法，但是很遗憾他没有实践自己的想法。同时我们发现，$160$ 或 $300$ 的上界对于 $O(\sqrt n)$ 的做法来说过于宽松了，~~不符合CF 的出题人的风格~~。综上，我想到，正解可能是 $O(\sqrt n +\log n)$ 的~~神秘~~做法。

想要实现带有 $\log$ 的做法，我们不难想到 ~~树剖~~、~~倍增~~、二分。但是在树上无法直接进行二分，所以我们考虑将 树上二分 转化为 序列二分。~~（越听越像树剖）~~

****重点来了。****

我们考虑这样一种转化方式。当我们询问的节点 $x$ 的子树是一条链的时候，如果老鼠在子树内，显然可以二分出老鼠的位置，否则，我们可以去掉以 $x$ 为根的子树，并将当前所有叶子节点删除，因为老鼠向上跳了一层，必定不在叶子节点上。同时，为了保证询问的次数正确，我们需要选择链顶，也就是说，我们选择的 $x$ 需要满足它的子树是一条链，同时它父亲的子树不是一条链。

关于这个方法询问次数小于 $O(\sqrt n + \log n)$ 的证明放在最后。~~其实是咕咕咕了~~。

### 代码实现

在具体实现时，我采取了树剖的方法。我维护了每个节点子树的 $size$ 大小。每次删点时，相当于做了一次从根节点到当前节点的路径修改，这可以用线段树来维护。而每次寻找合法的 $x$,可以根据 $x$ 的 $size$ 大小来确定。

感觉实现细节不是很多，并且文章篇幅有点长，就不放代码了（逃。

### 补：来自学长的询问次数正确性证明


以下用 $qes$ 代替已进行询问次数。

首先，如果此节点在这条链上，直接二分即可，询问次数 $O(\log n)$。

然后考虑不在这条链上的情况，每次询问过后链长（剩余可选择的链顶节点于子树内最深节点的深度差）一定是大于 $qes$ 的，当 $qes$ 接近于 $O(\sqrt n)$ 时，因为链是一定不交的，所以这样的链一定不会超过 $O(\sqrt n)$ 个，这样节点一定不会超过 $O(\sqrt n)$ 个，此时最多再进行 $O(\sqrt n)$ 次询问，因此返回为 $0$ 的询问次数一定不会超过 $O(\sqrt n)$。

要让这种方法进行更多次的询问，或者说使这种做法达到它的理论询问上界，一个简单的想法就是让每次询问的链长尽量小，因此使每次询问的链长都与当前询问次数相等，此时 $\frac {qes*(qes-1)} 2 = n$，$qes \approx \sqrt {2 \times n}$，最后二分 $O(\log n)$。       ——机房学长

****让我们感谢他来救场！****

---

## 作者：Hoks (赞：0)

## 前言
菜狗的第一场 VP，结果跳到幽默场了，好吧只能说我更幽默。

肯定直接开 hard version 了。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
交互题，没思路咋办。

考虑下按照做交互题的经验，应该就两种了：
1. 把情况逐渐缩小做。
2. 把给我们的操作特异化，取极值特殊化操作。

那这题好像没有熟悉的 $\max,\min$ 这种方便取极值的操作，那应该就是第一种了。

还是不是很好想，我们考虑从询问次数入手。

询问次数 $160$，而 $n$ 的范围是 $5000$，算一下可以接受 $\log^2 n$，而且卡的比较满。

但是我们好像想不到任何有关于 $\log n$ 上再来个 $\log n$ 的思路。

那只能跳出 $\log$ 的思路了，不难发现的是 $\sqrt{n}$ 大约是 $70$。

那么卡满的一个询问次数就是 $2\sqrt{n}$，这个感觉应该是从根号分治里来的。

那考虑下对什么根号分治吧。

我们考虑对于深度根号分治，把深度小于等于阈值 $B$ 的全部搞掉。

那怎么搞掉呢，考虑直接对着一个叶子问 $B$ 次，那么就可以把所有深度小于等于 $B$ 的点都跑到 $1$ 上了。

接着考虑剩下来的部分有什么优势。

我们考虑在这颗树上，把深度小于等于 $B$ 的点全删掉，那么剩下的连通块最多 $\lceil\frac{n}{B}\rceil$。

那么我们只要确定一下在那颗子树里，再往下走确定一条所在的链，剩下的部分就可以 $\log n$ 二分处理，这个时候询问次数是 $2\sqrt{n}+\log n$，$150$ 次左右，刚好卡满。

但这个时候如果树的深度一大就又被创飞了。

这个时候呢，我们可以发现，实际上如果只有一条路可以走了，那么肯定就在这条路上了，此时就不用询问了，这样就完成了这题。

~~有的消愁宏定义 $mid$，然后先给 $l,r$ 赋值再记录答案，难评。~~
## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,M=70,INF=0x3f3f3f3f,mod=998244353;
int n,s,st,a[N],dep[N];vector<int>e[N],b;
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    // #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='.'||c=='#'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void add(int u,int v){e[u].emplace_back(v),e[v].emplace_back(u);}
inline int query(int x){cout<<"? "<<x<<endl;cin>>x;s+=!x;return x;}
inline void dfs(int u,int ff)
{
    dep[u]=dep[ff]+1;a[u]=1;
    for(auto v:e[u]) if(v!=ff) dfs(v,u),a[u]=max(a[v]+1,a[u]);
}
inline void dfs1(int u,int ff)
{
    b.emplace_back(u);vector<int> c;
    for(auto v:e[u])
    {
        if(v==ff||a[v]<=s) continue;
        c.emplace_back(v);
    }
    for(int i=0;i<(int)c.size()-1;i++) if(query(c[i])) return dfs1(c[i],u);
    if(c.size()) dfs1(c.back(),u);
}
inline void solve()
{
    n=read();for(int i=1;i<=n;i++) e[i].clear();s=0;b.clear();
    for(int i=1,u;i<n;i++) u=read(),add(u,read());dfs(1,0);
    int x=0;for(int i=1;i<=n;i++) if(a[i]==1) x=i;b.emplace_back(1);
    if(query(x)) return cout<<"! "<<x<<endl,void();
    for(int i=1;i<M;i++) query(x);dfs1(1,1);
    int l=1,r=b.size()-1,ss=0,ans=0;
    while(l<=r)
    {
        int mid=(l+r)>>1;x=mid>ss?mid-ss:-1;
        if(x==-1){l=mid+1;ans=mid;continue;}
        if(query(b[x])) l=mid+1,ans=mid;
        else r=mid-1,ss++;
    }
    if(ans>ss) return cout<<"! "<<b[ans-ss]<<endl,void();
    return cout<<"! "<<1<<endl,void();
}
signed main()
{
    int T=read();while(T--) solve();
    genshin:;flush();return 0;
}
```

---

## 作者：Federico2903 (赞：0)

## 思路

每一次出现一个失败的操作，鼹鼠会往上跑一步。

也就是说，当有 $k$ 个失败的操作时，鼹鼠一定不会出现在最大深度 $\le k$ 的子树中。

如果树是一条链是简单的，二分即可。

那么我们可以先执行 $\sqrt n$ 次询问叶子的操作，如果返回 $1$ 皆大欢喜，因为答案就在这里。

做完这样的操作会使得最大深度 $\le \sqrt n$ 的子树中没有鼹鼠。接下来我们考虑通过 dfs 把树简化为一条链。

设失败的操作出现了 $x$ 次了。

从 $1$ 号节点开始，我们找出其所有满足最大深度 $> x$ 的子树，依次询问。当得到 $1$ 的答案时直接向其递归，否则我们就排除了至少 $x$ 个节点。

因为我们询问了 $\sqrt n$ 次叶子，所以 $x \ge \sqrt n$，则上述操作至多执行 $\sqrt n$ 次。

非常美妙的做法，但是这会**被链卡操作次数**。

怎么办呢。我们找出儿子的时候只询问前 $siz - 1$ 个，如果都是 $0$ 就直接进入最后一个儿子就能规避这个问题了。

最后到达叶子的时候，从 $1$ 号节点到叶子的这条链上一定有鼹鼠，二分即可。

总操作次数应为 $2 \sqrt n + \log n$。

## AC 代码

```cpp
#ifdef ONLINE_JUDGE
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt")
#include <immintrin.h>
#include <emmintrin.h>
#endif

#include <bits/stdc++.h>

#define rep(i, a, b) for(int i = (a), i##end = (b); i <= i##end; i++)
#define _rep(i, a, b) for(int i = (a), i##end = (b); i >= i##end; i--)
#define ec first
#define fb second
#define dl make_pair
#define dk(...) make_tuple(__VA_ARGS__)

using namespace std;

typedef long long ll;
typedef pair <int, int> pii;

int read() {
	int x = 0, f = 1; char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return x * f;
}

template <typename _Tp>
void print(_Tp x) {
	if (x < 0) x = (~x + 1), putchar('-');
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

int T, n, zc;

void found(int vert) { cout << "! " << vert << endl; }
int ask(int vert) {
	cout << "? " << vert << endl;
	int x = read();
	if (x) return 1;
	else return zc++, 0;
}

const int MAXN = 5005;
vector <int> G[MAXN];
int dep[MAXN], pdep[MAXN];
int s[MAXN << 2], top;

void dfs0(int u, int fa) {
	dep[u] = 1;
	pdep[u] = pdep[fa] + 1;
	for (auto v : G[u]) {
		if (v == fa) continue;
		dfs0(v, u);
		dep[u] = max(dep[u], dep[v] + 1);
	}
}

void dfs1(int u, int fa) {
	s[++top] = u;
	vector <int> son;
	for (auto v : G[u]) {
		if (v == fa || dep[v] <= zc) continue;
		son.push_back(v);
	}
	rep (i, 0, son.size() - 2) {
		if (ask(son[i])) return dfs1(son[i], u);
	}
	if (son.size()) dfs1(son.back(), u);
}


void solve() {
	zc = 0;
	top = 0;
	n = read();
	rep (i, 1, n) vector <int>().swap(G[i]);
	rep (i, 1, n - 1) {
		int u = read(), v = read();
		G[u].push_back(v);
		G[v].push_back(u);
	}
	const int B = 70;
	int leaf = 0;
	dfs0(1, 1);
	rep (i, 1, n) if (dep[i] == 1) leaf = i;
	if (ask(leaf)) return found(leaf);
	else rep (i, 1, B - 1) ask(leaf);
	dfs1(1, 1);
	int l = 1, r = top, mid = 0, cnt = 0, ans = 0;
	while (l <= r) {
		mid = (l + r) >> 1;
		int pt = mid > cnt ? mid - cnt : 0;
		if (!pt) { l = mid + 1; ans = mid; continue; }
		if (ask(s[pt])) l = mid + 1, ans = mid;
		else r = mid - 1, cnt++;
	}
	if (ans > cnt) found(s[ans - cnt]);
	else found(1);
}

signed main() {
	T = read();
	while (T --> 0) solve();
	return 0;
}
```

---

## 作者：Iceturky (赞：0)

[Link](https://www.luogu.com.cn/problem/CF1990E2)

感觉我的做法比较奇怪，但感觉很对。

发现 $N$ 比较小，考虑暴力一点的做法。

考虑如何查找所需次数最少，经典想法就是子树大小接近 $\frac{num}{2}$ ，$num$ 是现在还存在的树的大小（每一次若不存在于子树内则砍掉子树再加回来每一个剩余点的父亲，再砍掉所有叶子，若存在则砍掉除子树之外的部分）。

然后暴力维护这一棵树，如果用 set 来维护则复杂度是单次查询 $O(n\log n)$ 。

为什么这样能较优？考虑极端情况——菊花图，这样的情况下，子树大小是距离 $\frac{num}{2}$ 相当远的。

但是注意到每一次若不在子树中则会向上走一格。而菊花图叶子非常多。这种策略在菊花图时能跑的非常快。

那么在链的情况下呢？容易发现若是链，则 $\frac{num}{2}$ 是非常容易接近的一个数。所以其也能跑的非常快。

我估计一个上界是 $O(\sqrt n)$ 级别的，若有读者能够提出证明欢迎发在评论区。

实现方法则是用 set 维护一个点集，表示这些点可能会存在 mole 。按照dfn排序后倒序处理子树和，类似dp。

然后找到子树和最接近 $\frac{num}{2}$ 且最小的点，对其查询。

若 mole 在其子树内则遍历点集，删掉子树外的点。若不在则删掉子树内的点，再将子树外的点删掉，其父亲加入。

容易发现每一种操作可能涉及的点数量都是 $O(n)$ 。这样单次询问即为 $O(n\log n)$ 。

容易发现删掉子树内/外所有点相当于dfn序列上的一个区间覆盖，可以使用差分预处理，但将父亲插入较难实现。可以找出一个点距离其子树内叶子最远距离，然后考虑一次整体上移造成的影响：删掉所有叶子，加入根的父亲（若有）。删叶子可以通过刚刚所说的预处理子树内距叶子最远距离来实现，加入父亲只会造成 $O(1)$ 级别的影响。这样可以把复杂度优化到 $O(n)$ 。

但是单 $\log$ 的方法在 test 2 ILE 了，线性没调出来，后来写了个 [vector 暴力删](https://codeforces.com/contest/1990/submission/271780444) 过了。有点太逆天了。

其原理与用 set 维护一样，同样是删除与去重。但是由于 vector 删除复杂度高且去重也要手动所以不优。

以下是 $O(n^2)$ 的 vector 暴力删做法代码。

code

```cpp
const int N=5e3+5;

struct edge{
	int v,nxt;
}e[N<<1];
int head[N],tott;
void add(int u,int v){e[++tott]={v,head[u]},head[u]=tott;}

vector<int> vec;

int dep[N],dfn[N],cnt;
int L[N],R[N];
int fa[N];
void dfs(int u,int faa){
	L[u]=dfn[u]=++cnt;
	dep[u]=dep[faa]+1;
	fa[u]=faa;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==faa)
			continue;
		dfs(v,u);
	}R[u]=cnt;
}

bool cmp(int x,int y){
	return dep[x]==dep[y]?dfn[x]<dfn[y]:dep[x]<dep[y];
}

bool tag[N];
int sum[N];
bool ask(){
	int id=vec.back();
	int num=vec.size()/2;
	for(int i=vec.size()-1;i>=0;i--){
		int v=vec[i];
		sum[v]++;
		if(abs(sum[v]-num)<abs(sum[id]-num)||
		  (abs(sum[v]-num)==abs(sum[id]-num)&&sum[v]<sum[id]))
			id=v;
		if(tag[fa[v]])
			sum[fa[v]]+=sum[v];
	}
	for(int i:vec)
		sum[i]=0;//清空
	cout<<"? "<<id<<endl;
	int opt=read();
	if(opt){
		for(int i=0;i<vec.size();i++){
			int v=vec[i];
			if(dfn[v]>R[id]||dfn[v]<L[id]){
				tag[v]=0;
				vec.erase(vec.begin()+i);
				i--;
			}
		}
	}else{
		for(int i=0;i<vec.size();i++){
			int v=vec[i];
			if(dfn[v]<=R[id]&&dfn[v]>=L[id]){
				tag[v]=0;
				vec.erase(vec.begin()+i);
				i--;
			}else if(v!=1){
				tag[v]=0;
				tag[fa[v]]=1;
				vec[i]=fa[v];
				if(i>0&&vec[i]==vec[i-1]){//去重，在按照深度及dfn序排序后，若同时将数列中每一个点替换为其父亲，则相同的数字一定出现在连续的一段
					vec.erase(vec.begin()+i);
					i--;
				}
			}
		}
	}
	if(vec.size()==1){
		cout<<"! "<<vec[0]<<endl;
		vector<int> tmp;
		swap(tmp,vec);//清空vector
		return 1;
	}return 0;
}

signed main(){
	signed _T=read();
	while(_T--){
		int n=read();
		for(int i=1;i<n;i++){
			int u=read(),v=read();
			add(u,v),add(v,u);
		}
		dfs(1,0);//预处理
		for(int i=1;i<=n;i++)
			vec.pb(i),tag[i]=1;//tag表示还存在于点集内
		sort(all(vec),cmp);
		while(!ask());
		for(int i=1;i<=n;i++)
			head[i]=tag[i]=0;
		tott=0;
		cnt=0;
	}
	return 0;
}
```

---

## 作者：Acoipp (赞：0)

首先要求次数小于等于 $160$ 次，一个直观的解法就是考虑链和菊花都可以通过的构造。

链的话显然链上二分就可以了，这一部分不算难，就是要注意边界情况，需要耗费 $\log$ 次操作。

但是这种做法会被菊花图卡，于是我们可以疯狂询问一个点，使得子树深度大于等于我们询问的这个点的次数的点才可能作为答案。

容易发现经过上述操作之后这棵树的形态缩减了很多，然后对于有分叉的节点（节点儿子数量大于等于 $2$）依次询问鼹鼠在哪个子树即可，最后优化成一条链再二分就可以了。

设最开始操作同一个点的次数是 $B$，那么我们需要让 $\frac nB+B+\log n$ 最小，得 $B = \sqrt{n}$，算出来恰好比 $160$ 小一点点。

代码如下，仅供参考：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 5005
using namespace std;
vector<ll> op[N];
ll T,n,i,x,y,dep[N],maxdep[N],leav,step,get_ans,sta[N],top,l,r,vis[N],CNT;
inline bool cmp(ll a,ll b){return maxdep[a]>maxdep[b];}
inline void dfs(ll x,ll fa){
	ll son = 0;
	maxdep[x] = dep[x];
	for(ll i=0;i<op[x].size();i++){
		if(op[x][i]==fa) continue;
		son++;
		dep[op[x][i]] = dep[x]+1,dfs(op[x][i],x);
		maxdep[x] = max(maxdep[x],maxdep[op[x][i]]);
	}
	if(son==0) leav=x;
}
inline bool calc(ll x){return maxdep[x]-dep[x]>=step;}
inline void dfs2(ll x,ll fa){
	if(!calc(x)){
		vis[x] = 1;
		return ;
	}
	vector<ll> v;
	v.clear();
	for(ll i=0;i<op[x].size();i++){
		if(op[x][i]==fa) continue;
		if(maxdep[op[x][i]]-dep[x]<=step){
			vis[op[x][i]] = 1;
			continue;
		}
		v.push_back(op[x][i]);
	}
	if(v.size()>1){
		for(ll i=0;i<v.size();i++){
			assert(CNT+1<=300),cout<<"? "<<v[i]<<endl,CNT++;
			cout.flush();
			ll temp;
			cin>>temp;
			cout.flush();
			if(temp==0) vis[v[i]]=1,step++;
		}
	}
	for(ll i=0;i<v.size();i++){
		if(!vis[v[i]]){
			dfs2(v[i],x);
			return ;
		}
	}
}
inline void dfs3(ll x,ll fa){
	sta[++top] = x;
	for(ll i=0;i<op[x].size();i++){
		if(op[x][i]==fa) continue;
		if(vis[op[x][i]]) continue;
		dfs3(op[x][i],x);
		return ;
	}
}
ll basic = 71;
int main(){
	ios::sync_with_stdio(false);
	cin>>T;
	for(ll test_case=1;test_case<=T;test_case++){
		step=0,get_ans=0,top=0,CNT=0;
		cin>>n;
		for(i=1;i<n;i++) cin>>x>>y,op[x].push_back(y),op[y].push_back(x);
		for(i=1;i<=n;i++) vis[i]=0;
		dfs(1,-1);
		for(i=1;i<=basic;i++){
			assert(CNT+1<=300),cout<<"? "<<leav<<endl,CNT++;
			cout.flush();
			ll temp;
			cin>>temp;
			cout.flush();
			if(temp==1) break;
			step++;
		}
		if(i<=basic){
			cout<<"! "<<leav<<endl,cout.flush();
			goto end;
		}
		dfs2(1,-1);
		dfs3(1,-1);
		l=1,r=top;
//		for(ll i=1;i<=r;i++) cout<<sta[i]<<" ";
//		cout<<endl;
		while(r>l&&!calc(sta[r])) r--;
		while(l<r){
			ll mid = (l+r+1)/2;
			ll temp;
			cout<<"? "<<sta[mid]<<endl;
			cout.flush();
			cin>>temp;
			cout.flush();
			if(temp==1) l=mid;
			else l--,r=mid-2,step++;
			l = max(l,1ll),r = max(r,1ll);
			while(r>l&&!calc(sta[r])) r--;
		}
		cout<<"! "<<sta[l]<<endl,cout.flush();
		end:;
		for(i=1;i<=n;i++) op[i].clear();
	}
	return 0;
}
```

---

## 作者：happybob (赞：0)

请先阅读 [Easy Version 题解](https://www.luogu.com.cn/article/eclk7fbf)。

树分块后，考虑我们的询问瓶颈其实在于找到答案上方的第一个关键点后，我们要进行两倍链长次询问以确定什么时候这个点移动到了关键点。

优化的一个想法是考虑在里面再做一次分块状物，既每 $k$ 次询问叶子后询问一次关键点，然而很不幸地，这个做法的最坏次数略微超过了询问次数限制。

考虑另一个做法。先对叶子进行链长次操作，保证这个点已经到了关键点上面，然后进行二分。取链长为 $64$ 可以通过。

[Submission Link](https://codeforces.com/contest/1990/submission/271698337)。

---

