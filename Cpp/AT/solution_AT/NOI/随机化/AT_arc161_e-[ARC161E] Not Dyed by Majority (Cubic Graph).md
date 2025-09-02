# [ARC161E] Not Dyed by Majority (Cubic Graph)

## 题目描述

给定一个正的**偶数** $N$，有一个包含 $N$ 个顶点、$\displaystyle\frac{3}{2}N$ 条边的连通简单无向图。顶点编号为 $1$ 到 $N$，第 $i$ 条边连接顶点 $A_i$ 和顶点 $B_i$。此外，每个顶点**恰好有 $3$ 条边相连**。

现在要将图中每个顶点染成黑色（`B`）或白色（`W`）。此时，将所有顶点的颜色（`B` 或 `W`）按照顶点编号顺序排列，得到的字符串称为**颜色序列**。

请判断，是否存在某种颜色序列，在对所有顶点进行如下操作一次后**不可能出现**。如果存在，请给出任意一个这样的颜色序列。

**操作：** 对于每个顶点 $k=1,2,\dots,N$，令 $C_k$ 为与其相连的顶点中占多数的颜色。然后，所有顶点同时将自己的颜色变为 $C_k$。

给定 $T$ 组测试数据，请分别回答每组数据。

## 说明/提示

### 限制条件

- $T\geq 1$
- $N\geq 4$
- 所有测试数据中 $N$ 的总和不超过 $5\times 10^4$
- $N$ 是**偶数**
- $1\leq A_i < B_i \leq N\ \left(1\leq i\leq \displaystyle\frac{3}{2}N\right)$
- $(A_i,B_i)\neq (A_j,B_j)\ \left(1\leq i<j\leq \displaystyle\frac{3}{2}N\right)$
- 给定的图是连通的
- 每个顶点 $k\ (1\leq k\leq N)$ 在 $A_i,B_i\ \left(1\leq i\leq \displaystyle\frac{3}{2}N\right)$ 中**恰好出现 $3$ 次**

### 样例解释 1

以第一个测试数据为例。要使顶点 $1$ 的颜色为 `B`，则操作前顶点 $2,3,4$ 中至少有 $2$ 个为 `B`。此时，$2,3,4$ 中至少有 $1$ 个，其相连的顶点中有至少 $2$ 个为 `B$，因此操作后颜色为 `B`。所以，`BWWW` 这个颜色序列在操作后是不可能出现的。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
4
1 2
1 3
1 4
2 3
2 4
3 4
10
1 2
1 3
1 4
2 3
2 4
3 5
4 5
5 6
6 7
6 8
7 9
7 10
8 9
8 10
9 10```

### 输出

```
BWWW
BWWWBWWWBB```

# 题解

## 作者：良心WA题人 (赞：8)

## 前言

有时候，学 OI 就得相信自己的直觉。谨记“因为这题如果不满足这个结论我就不会做，所以这个结论一定是对的。”

## 题意

给定一张图，要求你构造一个颜色序列（两种颜色），使得无论给每个点确定什么颜色（两个中的一个
），最后将每个点变成与其相邻的点中颜色数量更多的一个颜色后都无法变为给定的颜色序列。

## 思路

毫无头绪，那就猜。因为 [C 题](https://www.luogu.com.cn/problem/AT_arc161_c)在做的时候发现有解貌似很困难，那么一个符合直觉的结论为随意一个颜色序列有 $\ge\dfrac{1}{2}$ 的概率是无解的。这个结论证明十分困难，但是是对的，想要了解可以去看官方题解。

那么，这时候这个问题就变得比较平凡了。考虑如何判断一个颜色序列是否无解，不难想到三个边中不能同时有两个颜色与当前点要求的颜色不同，那么就是若干“若其中一个点填了颜色 $A$，则另外两个点都只能填颜色 $B$”的条件。显然是经典的 2-sat 问题。于是就成功地解决了这道题。

## 附

其实可以感性理解一下这个结论，这也是赛场上让我感觉这个结论是对的的原因（不过这并不影响我没敢做这道题）。**注意，这并不代表这个过程是严谨或完全正确的。**

对于每个点在 2-sat 上都会连接 $3\times 2$ 条边，也就是一共有 $3\times 2\times n$ 条边。而 2-sat 上一共只有 $2\times n$ 个点，则边数是三倍的点数。因为我们是随机的颜色序列，所以可以看作边是基本随机的，那么这样一个随机的就比较难不出现使得 2-sat 的两种情况在同一个强连通分量内的环。直觉上感觉概率应该不会低于 $\dfrac{1}{10}$，而就算是 $\dfrac{1}{10}$ 也大概率能在时间范围内找到解，所以可以大胆猜测这个结论是对的（实际上证明出来并不只有 $\dfrac{1}{10}$）。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=5e4+4;
vector<int>p[NN],g[NN*2];
int col[NN],dfn[NN*2],low[NN*2],scc[NN*2],scn,tim,xx[NN];
stack<int>sta;
void tarjan(int u)
{
	dfn[u]=low[u]=++tim;
	sta.push(u);
	for(int i=0;i<g[u].size();i++)
	{
		int v=g[u][i];
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(!scc[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
	{
		scn++;
		int x;
		do
		{
			x=sta.top();
			sta.pop();
			scc[x]=scn;
		}while(x!=u);
	}
}
int main()
{
	srand(time(0));
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			p[i].clear();
		for(int i=1;i<=n/2*3;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			p[u].push_back(v);
			p[v].push_back(u);
		}
		while(true)
		{
			for(int i=1;i<=n;i++)
				col[i]=rand()%2;
			for(int i=1;i<=n*2;i++)
			{
				g[i].clear();
				scc[i]=low[i]=dfn[i]=0;
			}
			scn=tim=0;
			for(int i=1;i<=n;i++)
				for(int j=0;j<3;j++)
					for(int k=0;k<3;k++)
						if(j!=k)
						{
							if(!col[i])
								g[p[i][j]].push_back(p[i][k]+n);
							else
								g[p[i][j]+n].push_back(p[i][k]);
						}
			for(int i=1;i<=n*2;i++)
				if(!dfn[i])
					tarjan(i);
			bool flag=false;
			for(int i=1;i<=n;i++)
				if(scc[i]==scc[i+n])
				{
					flag=true;
					break;
				}
			if(flag)
				break;
		}
		for(int i=1;i<=n;i++)
			putchar(col[i]?'B':'W');
		puts("");
	}
	return 0;
}
```

---

## 作者：EuphoricStar (赞：3)

给构造题提供了一种新的思路。

**如果答案在总方案数的占比较大，可以考虑随机化之后 check。**

例如本题，可以打表发现 $n = 10$ 时答案占总方案数的比 $> \frac{1}{2}$。考虑随机化，难点变成判断一个方案是否可行。考虑 2-SAT，如果一个点众数是 $\text{B}$，那么对于这个点的边，如果有一条边的另一个端点原本颜色是 $\text{W}$，那么其他两个原本颜色都是 $\text{B}$。反之同理。跑一遍 2-SAT 即可知道随出来的这个解是否合法。

至于这个结论的正确性，可以去看[官方题解](https://atcoder.jp/contests/arc161/editorial/6480 "官方题解")。

[code](https://atcoder.jp/contests/arc161/submissions/41821994)

---

## 作者：0x3F (赞：1)

人类智慧题。

我们考虑随机一组答案，判定使用 2-SAT 即可。具体地，如果答案中点 $A$ 颜色为 $1$，点 $A$ 与 $B,C,D$ 连边，那么添加限制：$B\operatorname{or}C,B\operatorname{or}D,C\operatorname{or}D$，颜色为 $0$ 类似。如果 2-SAT 问题无解，那么说明这组答案是合法的。

我们考虑这样的正确率。记初始颜色的总数 $2^N=X$。

只考虑 $1$ 号点附近的点。记 $A\leftrightarrow B$ 表示 $A,B$ 有边直接相连。记 $S=\left\{P\vert P\leftrightarrow Q,Q\leftrightarrow1,P\neq1\right\},T=\left\{P\vert P\leftrightarrow1\right\}$，则显然有 $\lvert S\rvert\le6$。

我们强制让 $S$ 中的点初始颜色全部相同，其他点初始颜色随意，那么这样的初始状态至少有 $\frac{X}{32}$ 个。此时，如果改变 $1$ 号点的初始颜色，那么 $T$ 外的点的最终颜色显然不受影响。而 $T$ 中的点的最终颜色必然是 $S$ 的初始颜色，因此也不受影响。

将 $1$ 号点颜色为 $0$ 和 $1$ 的情况两两配对，至少得到 $\frac{X}{64}$ 对不同的初始状态对应相同的最终状态。

因此，也至少有 $\frac{X}{64}$ 个最终状态，没有初始状态与之对应。故成功率 $\ge\frac{1}{64}$。

当然，实际的正确率比这还要大得多（具体地，至少 $48\%$），但是算到这里就足以证明该算法的正确性了。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int _ = 5e4 + 10;
const int __ = 1e5 + 10;
const int ___ = 3e5 + 10;
int Testcases, n, a[_], b[_], c[_];
bool col[_];
inline void Add(int u, int v) {
	if (a[u]) {
		if (b[u]) {
			c[u] = v;
		} else {
			b[u] = v;
		}
	} else {
		a[u] = v;
	}
}
int e, hd[__], nx[___], to[___];
inline void add(int u, int v) {
	e++;
	nx[e] = hd[u];
	to[e] = v;
	hd[u] = e;
}
int cnt, dfn[__], low[__], tp, stk[__], cc, tcol[__];
bool vis[__];
void dfs(int x) {
	low[x] = dfn[x] = ++cnt;
	stk[++tp] = x;
	vis[x] = true;
	for (int i = hd[x]; i; i = nx[i]) {
		int y = to[i];
		if (!dfn[y]) {
			dfs(y);
			low[x] = min(low[x], low[y]);
		} else if (vis[y]) {
			low[x] = min(low[x], dfn[y]);
		}
	}
	if (low[x] == dfn[x]) {
		cc++;
		while (stk[tp] != x) {
			tcol[stk[tp]] = cc;
			vis[stk[tp]] = false;
			tp--;
		}
		tcol[stk[tp]] = cc;
		vis[stk[tp]] = false;
		tp--;
	}
}
int main() {
	mt19937 rng(114514);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> Testcases;
	while (Testcases--) {
		cin >> n;
		for (int i = 1; i <= n+(n>>1); i++) {
			int u, v;
			cin >> u >> v;
			Add(u, v);
			Add(v, u);
		}
		while (true) {
			for (int i = 1; i <= n; i++) {
				col[i] = (bool)(uniform_int_distribution<int>(0, 1)(rng));
			}
			for (int i = 1; i <= n; i++) {
				if (col[i]) {
					add(a[i], b[i] + n);
					add(a[i], c[i] + n);
					add(b[i], a[i] + n);
					add(b[i], c[i] + n);
					add(c[i], a[i] + n);
					add(c[i], b[i] + n);
				} else {
					add(a[i] + n, b[i]);
					add(a[i] + n, c[i]);
					add(b[i] + n, a[i]);
					add(b[i] + n, c[i]);
					add(c[i] + n, a[i]);
					add(c[i] + n, b[i]);
				}
			}
			for (int i = 1; i <= (n<<1); i++) {
				if (!dfn[i]) dfs(i);
			}
			bool ok = true;
			for (int i = 1; i <= n; i++) {
				if (tcol[i] == tcol[i+n]) {
					ok = false;
				}
			}
			cc = cnt = e = 0;
			for (int i = 1; i <= (n<<1); i++) {
				dfn[i] = hd[i] = 0;
			}
			if (!ok) {
				for (int i = 1; i <= n; i++) {
					cout << "WB"[col[i]];
				}
				cout << endl;
				break;
			}
		}
		for (int i = 1; i <= n; i++) {
			a[i] = b[i] = c[i] = 0;
		}
	}
}
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc161_e)

**题目大意**

> 给定一张图，每个点度数为 $3$，给每个点赋值 $0/1$，定义一次变换是把每个点的权值**同时**变成其邻域权值的众数。
>
> 构造一个不可能是变换后结果的颜色序列。
>
> 数据范围：$n\le 5\times 10^4$。

**思路分析**

考虑如何 检验 $\{c_u\}$ 是否可以被 $\{d_u\}$ 生成，显然可以用 2-SAT 解决。

设 $c_u=0$，$N(u)=\{x,y,z\}$，那么 $d_x=1\implies d_y=0,d_z=0$，轮换后同理。

我们只要找到一个使得 2-SAT 无解的序列。

容易发现假如两个序列在变换后结果相同，那么就必定会产生一个序列不可生成。

考虑 $1$ 的邻域 $x,y,z$，以及他们的邻域 $\{1,x_0,x_1\},\{1,y_0,y_1\},\{1,z_0,z_1\}$：如果 $d_{x_0}=d_{x_1},d_{y_0}=d_{y_1},d_{z_0}=d_{z_1}$，那么无论 $d_1$ 是什么，答案都不会更改。

因此我们说明至少有 $\dfrac 1{16}$ 的序列会互相重复，那么期望 $\mathcal O(1)$ 次随机后能得到一组解。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;
mt19937 rnd(time(0));
vector <int> G[MAXN],E[MAXN];
int dfn[MAXN],low[MAXN],scc[MAXN],stk[MAXN],tp,scnt,dcnt;
bool ins[MAXN],col[MAXN];
void tarjan(int u) {
	dfn[u]=low[u]=++dcnt,stk[++tp]=u,ins[u]=true;
	for(int v:G[u]) {
		if(!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
		else if(ins[v]) low[u]=min(low[u],low[v]);
	}
	if(dfn[u]==low[u]) {
		int k; ++scnt;
		do k=stk[tp--],ins[k]=false,scc[k]=scnt;
		while(k!=u);
	}
}
void solve() {
	int n;
	scanf("%d",&n);
	auto link=[&](int i,int x,int j,int y) { G[i+x*n].push_back(j+y*n); };
	for(int i=1;i<=n;++i) E[i].clear();
	for(int i=1,u,v;i<=n*3/2;++i) {
		scanf("%d%d",&u,&v),E[u].push_back(v),E[v].push_back(u);
	}
	while(true) {
		tp=scnt=dcnt=0;
		for(int i=1;i<=n;++i) col[i]=rnd()&1;
		for(int i=1;i<=2*n;++i) G[i].clear(),dfn[i]=low[i]=scc[i]=stk[i]=ins[i]=0;
		for(int i=1;i<=n;++i) for(int x:E[i]) for(int y:E[i]) if(x^y) {
			link(x,col[i]^1,y,col[i]);
		}
		for(int i=1;i<=2*n;++i) if(!dfn[i]) tarjan(i);
		for(int i=1;i<=n;++i) if(scc[i]==scc[i+n]) {
			for(int j=1;j<=n;++j) putchar("WB"[col[j]]);
			puts("");
			return ;
		}
	}
}
signed main() {
	int cas; scanf("%d",&cas);
	while(cas--) solve();
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

这也太难了。难点在于：你能想到这种“构造”吗？

-------

考虑 SPJ 咋写。发现这是容易的：我们的限制只有，对于相邻的两个点 $u$ 和 $v$，$col_v \neq fin_u$（$col$ 指的是原始颜色序列，$fin$ 表示操作一次之后的序列），则 $u$ 的另外两个邻居的 $col$ 和 $fin_u$ 相同。这是简单的 2-SAT 问题。

-------

然后就是“构造”了：考虑随，随到答案为止。

证明也非常神奇：考虑构造一个点颜色的方案集合 $S$，使得 $f(s)$ 总能在 $f(t)$ 中找到对应，其中 $s \in S$，$t \notin S$，$f(s)$ 指的是序列 $s$ 操作的结果。则至少有 $|S|$ 个无解的序列。

而考虑取 $Q$ 为所有和 $1$ 存在公共邻居的点（包括 $1$），将 $Q$ 中所有颜色染成白色，其他点任意。发现把 $1$ 的颜色改变并不会影响最终的结果。

所以成功概率高达 $2^{-7}$。这个估计还特别愚蠢，实际高得多。反正总之，就是你随 $O(1)$ 次就能成功。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int tc,n,cs,dfn[MAXN],low[MAXN],in[MAXN],tot,cc[MAXN],col[MAXN];
vector<int> G[MAXN],T[MAXN];
stack<int> st;
void tarjan(int u) {
	dfn[u]=low[u]=++tot,in[u]=1,st.push(u);
	for(auto v:T[u]) {
		if(!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
		else if(in[v]) low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]) {
		++cs;
		while(1) {
			int v=st.top();
			st.pop();
			in[v]=0,cc[v]=cs;
			if(v==u) break ;	
		}
	}
	return ;
}
int check(void) {
	ffor(i,1,n+n) dfn[i]=low[i]=in[i]=0,tot=0,T[i].clear();
	tot=0;
	ffor(i,1,n) for(auto u:G[i]) for(auto v:G[i]) if(u!=v) T[u+(col[i]^1)*n].push_back(v+col[i]*n);
	ffor(i,1,n+n) if(!dfn[i]) tarjan(i);
	ffor(i,1,n) if(cc[i]==cc[i+n]) return 1;
	return 0;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>tc;
	while(tc--) {
		cin>>n;	
		ffor(i,1,n) G[i].clear();
		ffor(i,1,n*3/2) {
			int u,v;
			cin>>u>>v,G[u].push_back(v),G[v].push_back(u);
		}
		mt19937 myrand(time(NULL));
		while(1) {
			ffor(i,1,n) col[i]=myrand()&1;
			if(check()) {
				ffor(i,1,n) if(col[i]) cout<<"B";
				else cout<<"W";
				cout<<'\n';
				break ;	
			}
		}
	}
	return 0;
}
```

---

## 作者：complexor (赞：0)

很有意思的题。

首先考虑 spj 怎么实现，那么要解决两个问题：如何判断无解，如何判断解合法。

对于判断合法，假设 $u$ 操作后的颜色为 $c$，相邻的三个点为 $v_1,v_2,v_3$，那么限制就是操作前这三个点中至少有两个颜色为 $c$，或者说如果操作前 $v_1$ 颜色不是 $c$，那么 $v_2,v_3$ 的颜色必须是 $c$，$v_2,v_3$ 操作前的颜色不是 $c$ 同理。

那么一个操作后的颜色序列合法，当且仅当不存在满足上述要求的操作前的颜色序列，这就是一个 2-SAT 问题了，可以 $O(n)$ 解决。

对于判断无解，考虑如果无解，那么说明每个颜色序列都存在一个颜色序列操作一次后得到。这就构成了一个 $\{0,1\}^n$ 到自己的满射，那么它肯定也是双射。但这是不可能的，因为对于 $n$ 个点全染黑 和 $1$ 个点染白剩下 $n-1$ 个点染黑两种颜色序列，操作一次后的结果都是全黑，那么这不可能是单射，也就不是双射。所以本题不存在无解的情况。

接下来的做法很大胆，但绝大多数人可能都想过（不一定是对于这个题）：直接随机答案。

其实仔细想一想上面那个映射，大概可以感觉到有一种对称性，也就是有“一定比例”的颜色序列都不能被映射到。

具体一点，我们的想法是找到一个局部结构，如果这个局部中有 $a$ 种可能的颜色序列，只能映射到 $b(b<a)$ 种颜色序列，那么对于全局大概就有 $\frac{a-b}{a}$ 的序列可以作为答案。

考虑操作前的颜色序列。对于一个点 $x$、距离 $x$ 为 $1$ 的点 $y_1,y_2,y_3$、距离 $x$ 为 $2$ 的点 $z_{1,1},z_{1,2},z_{2,1},z_{2,2},z_{3,1},z_{3,2}$，只考虑 $x,z_{1,1},z_{1,2},z_{2,1},z_{2,2},z_{3,1},z_{3,2}$ 的颜色，其他点的颜色已经确定，那么有 $2^7=128$ 种颜色序列。而如果 $(z_{1,1},z_{1,2}),(z_{2,1},z_{2,2}),(z_{3,1},z_{3,2})$ 中每对点的颜色都一样，那么不管 $x$ 的颜色是什么，操作一次后的颜色序列都一样。这说明这 $128$ 种操作前的序列至多对应到 $128-8=120$ 种可能的序列。所以感性理解就有 $\frac{128-120}{128}=\frac{1}{16}$ 的序列是可以作为答案的。

这说明可以作为答案的颜色序列在 $\{0,1\}^n$ 中的占比是不超过 $O(1)$ 的，也就是期望随机不超过 $O(1)$ 次就能得到答案，所以总复杂度是 $O(n)$。

如果用占比为 $\frac{1}{16}$ 计算，那么随机 $300$ 次还找不到答案的概率不到 $4\times10^{-9}$，即使是 $10^6$ 组测试数据找不到答案的概率也只有不到 $0.004$。

事实上，可以证明答案在所有序列中的占比要比 $\frac{1}{16}$ 高得多，具体分析参考[官方题解](https://atcoder.jp/contests/arc161/editorial/6482)。

通过代码：
```cpp
#include <bits/stdc++.h>
typedef long long LL;
typedef std::pair<int, int> pii;
typedef unsigned long long ULL;
#define MP std::make_pair 
#define fi first
#define se second
char buf[1 << 20], *p1 = 0, *p2 = 0;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), (p1 == p2)) ? 0 : (*p1++))
int read()
{
    int s = 0; int f = 1, c = getchar();
    for (; !isdigit(c); c = getchar()) f ^= c == '-';
    for (; isdigit(c); c = getchar()) s = s * 10 + (c ^ 48);
    return f ? s : -s;
}
const int inf = 0x3f3f3f3f;
const LL INF = 0x3f3f3f3f3f3f3f3fll;
template<typename T> void Fmax(T &x, T y){ if (x < y) x = y; }
template<typename T> void Fmin(T &x, T y){ if (y < x) x = y; }
const int MAXN = 100005;
int n, m, col[MAXN], id[MAXN][2];
int e[MAXN][3], cnt[MAXN];
void init()
{
    n = read(), m = n / 2 * 3; 
    memset(cnt + 1, 0, n << 2);
    for (int i = 1; i <= m; i++)
    {
        int u = read(), v = read();
        e[u][cnt[u]++] = v, e[v][cnt[v]++] = u;
    }
    for (int i = 1; i <= n; i++)
        id[i][0] = (i - 1) << 1, id[i][1] = (i - 1) << 1 | 1;
}
namespace SAT
{
    int hd[MAXN], to[MAXN * 3], nxt[MAXN * 3], tot;
    void add(int x, int y){ to[++tot] = y, nxt[tot] = hd[x], hd[x] = tot; }
    int dfn[MAXN], low[MAXN], dcnt, st[MAXN], tp, N, bel[MAXN];
    bool inSt[MAXN];
    void init(int n){ tot = -1, memset(hd, -1, n << 3); }
    void dfs(int x)
    {
        dfn[x] = low[x] = ++dcnt;
        inSt[st[++tp] = x] = true;
        for (int e = hd[x], y; ~e; e = nxt[e])
            if (!dfn[y = to[e]]) dfs(y), Fmin(low[x], low[y]);
            else if (inSt[y]) Fmin(low[x], dfn[y]);
        if (low[x] == dfn[x])
        {
            ++N;
            for (int u = -1; u != x; )
                inSt[u = st[tp--]] = false, bel[u] = N;
        }
    }
    bool tarjan(int n)
    {
        memset(dfn, 0, n << 3);
        dcnt = N = 0;
        for (int i = 0; i < n * 2; i++)
            if (!dfn[i]) dfs(i);
        for (int i = 0; i < n; i++)
            if (bel[i << 1] == bel[i << 1 | 1])
                return false;
        return true;
    }
}
bool chk()
{
    SAT::init(n);
    for (int i = 1; i <= n; i++)
    {
        int o = col[i];
        SAT::add(id[e[i][0]][o ^ 1], id[e[i][1]][o]), SAT::add(id[e[i][0]][o ^ 1], id[e[i][2]][o]);
        SAT::add(id[e[i][1]][o ^ 1], id[e[i][0]][o]), SAT::add(id[e[i][1]][o ^ 1], id[e[i][2]][o]);
        SAT::add(id[e[i][2]][o ^ 1], id[e[i][0]][o]), SAT::add(id[e[i][2]][o ^ 1], id[e[i][1]][o]);
    }
    return !SAT::tarjan(n);
}
std::mt19937 rnd(time(0));
void mian()
{
    init();
    for (; ;)
    {
        for (int i = 1; i <= n; i++)
            col[i] = rnd() & 1;
        if (chk())
        {
            for (int i = 1; i <= n; i++)
                putchar("BW"[col[i]]);
            putchar('\n'); return ;
        }
    }  
}
int main()
{
    for (int Tcnt = read(); Tcnt--; ) mian();
    return 0;
}
```

---

## 作者：xxxxxzy (赞：0)

神奇。

答案在总方案数占比约等于 $\dfrac{1}{2}$。

然后这个 check 答案是容易的，如果 $u$ 的相邻节点 $v_1$ 选择了与 $u$ 目标异色的颜色，则 $v_2,v_3$ 必须选择与 $u$ 目标同色的颜色，这个容易 2 - sat 刻画。

时间期望 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pii pair<ll, ll>
#define mp make_pair
#define pb push_back
#define ld lower_bound
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define drep(i, a, b) for (int i = (a); i >= (b); i--)
#define ud upper_bound
#define mem(s, k) memset(s, k, sizeof(s))
#define fi first
#define se second
#define ull unsigned long long
#define vec vector <int>
#define fv inline void
#define fn inline static
using u16 = unsigned short; using u32 = unsigned; using u64 = unsigned ll; using u128 = __uint128_t;
using i16 = short; using i32 = ll; using i64 = ll; using i128 = __int128_t;
using namespace std;
const i32 N = 1e5 + 5;
i32 n, m, num, u, v, tot, tp, dfn[N], low[N], stk[N], ins[N], c[N], flg[N];
vector <i32> G[N], T[N];
mt19937 rd(time(0));
fv Tarjan(i32 u) {
  stk[++tp] = u, ins[u] = 1, dfn[u] = low[u] = ++tot;
  for (i32 v : G[u]) {
    if (!dfn[v]) Tarjan(v), low[u] = min(low[u], low[v]);
    else if (ins[v]) low[u] = min(low[u], dfn[v]);
  }
  if (dfn[u] == low[u]) {
    i32 x; num++;
    do {
      x = stk[tp--];
      ins[x] = 0, c[x] = num;
    } while (x != u);
  }
}
fn bool check() {
  rep (u, 1, n) { // +0 1 +n 0
    i32 v1 = T[u][0], v2 = T[u][1], v3 = T[u][2];
    if (flg[u]) {
      G[v1].pb(v2 + n), G[v1].pb(v3 + n);
      G[v2].pb(v1 + n), G[v2].pb(v3 + n);
      G[v3].pb(v1 + n), G[v3].pb(v2 + n); 
    } else {
      G[v1 + n].pb(v2), G[v1 + n].pb(v3);
      G[v2 + n].pb(v1), G[v2 + n].pb(v3);
      G[v3 + n].pb(v1), G[v3 + n].pb(v2);
    }
  }
  rep (i, 1, n * 2) if (!dfn[i]) Tarjan(i);
  rep (i, 1, n * 2) G[i].clear();
  tot = num = tp = 0;
  rep (i, 1, n * 2) dfn[i] = low[i] = ins[i] = 0;
  rep (i, 1, n) if (c[i] == c[i + n]) return 0;
  return 1;
}
fv rnd() {
  rep (i, 1, n) flg[i] = rd() % 2;
}
fv sol() {
  cin >> n; m = n / 2 * 3;
  rep (i, 1, m) cin >> u >> v, T[u].pb(v), T[v].pb(u);
  while (1) {
    rnd();
    if (!check()) break;
  }
  rep (i, 1, n) T[i].clear();
  rep (i, 1, n) cout << (flg[i] ? 'W' : 'B');
  cout << "\n";
}
int main() {
  i32 T = 1;
  cin >> T;
  while (T--) sol();
}
```

---

## 作者：Priestess_SLG (赞：0)

伟大的。考虑随便给每一个点赋值一个颜色，问题为如何 check 其是否合法。

看上去很困难，但是发现题目有一个优美的性质是说：**对于每一个点 $i$ 都有 $\deg(i)=3$。** 而题目中的一次操作是说，**同时把所有结点的颜色变为其连接结点中颜色的众数。** 将上述两条粗体字结合，就可以发现，每一个点连接的三个点中，如果有两个点同色，那么这个点就会变为这个颜色。根据抽屉原理可知必然存在这样的两个结点。

然后考虑逻辑化这个问题。考虑对于每一个点 $i$，为了尽量要求这个点和给定的颜色 $c_i$ 相同（这里令 $d_i$ 为 $c_i$ 的逆色），那么逻辑关系大致为：对于 $i$ 点的三个出边连接的结点 $i_1,i_2,i_3$，则若 $i_1$ 的颜色为 $d_i$，则 $i_2,i_3$ 的颜色必须均为 $c_i$。$i_2,i_3$ 的颜色为 $d_i$ 的情况同理。发现这个东西十分 2-Sat，因此直接建图，每一个点会建立 $6$ 条边，总边数为 $6n=O(n)$，直接跑 2-Sat 时间复杂度为 $O(n)$。若该 2-Sat 无解，则该颜色序列合法，直接输出她即可。

现在问题是如果该颜色序列不合法，怎么处理。容易想到多随机几次颜色序列，随机到合法的就输出，否则继续随机，直到合法为止。但是如果~~抽卡欧皇~~一直随不到，概率很大吗？考虑在本地随便造几个颜色序列跑一下，可以发现一次成功的概率略高于 $50\%$。考虑按 $50\%$ 计算，则随机 $k$ 次仍然失败的概率就是 $\frac1{2^k}$。考虑到 $k>30$ 的时候概率甚至不足 $\frac{1}{10^9}$，因此几乎不会出现到这种情况。于是问题解决。

代码：

```cpp
#pragma GCC optimize(3, "Ofast", "inline") 
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1e9 + 7;
const int N = 1000010;
vector<int> adj[N];
int col[N];
inline void generate(int n) {
    for (int i = 1; i <= n; ++i)
        col[i] = rand() & 1;
}
namespace TwoSat {
    vector<int> sat[N];
    inline void ae(int x, int y) {
        sat[x].emplace_back(y);
    }
    stack<int> stk;
    int dfn[N], low[N], bel[N], idx, tot, instk[N];
    void init(int lim) {
        idx = tot = 0;
        for (int i = 1; i <= lim; ++i) bel[i] = dfn[i] = low[i] = 0, sat[i].clear();
    }
    void tarjan(int x) {
        dfn[x] = low[x] = ++idx;
        instk[x] = 1, stk.emplace(x);
        for (int &v : sat[x])
            if (!dfn[v]) tarjan(v), low[x] = min(low[x], low[v]);
            else if (instk[v]) low[x] = min(low[x], dfn[v]);
        if (dfn[x] == low[x]) { ++tot;
            while (stk.top() != x) {
                int t = stk.top(); stk.pop();
                bel[t] = tot, instk[t] = 0;
            }
            int t = stk.top(); stk.pop();
            bel[t] = tot, instk[t] = 0;
        }
    }
    int check(int n) {
        for (int i = 1; i <= n + n; ++i)
            if (!dfn[i]) tarjan(i);
        int ok = 1;
        for (int i = 1; i <= n; ++i)
            ok &= (bel[i] != bel[i + n]);
        return ok;
    }
}
signed main() {
    srand(time(0));
    cin.tie(0)->sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; ++i) adj[i].clear();
        for (int i = 1; i <= n / 2 * 3; ++i) {
            int x, y; cin >> x >> y;
            adj[x].emplace_back(y);
            adj[y].emplace_back(x);
        }
        while (1) {
            generate(n);
            TwoSat::init(n + n);
            for (int i = 1; i <= n; ++i) {
                // i 表示 i 是小 0 ; i+n 表示 i 是小 1
                // 三种情况分类讨论
                // I. adj[i][0] 和 col[i] 不同
                TwoSat::ae(adj[i][0] + (1 ^ col[i]) * n, adj[i][1] + (col[i]) * n);
                TwoSat::ae(adj[i][0] + (1 ^ col[i]) * n, adj[i][2] + (col[i]) * n);
                // II. adj[i][1] 和 col[i] 不同
                TwoSat::ae(adj[i][1] + (1 ^ col[i]) * n, adj[i][0] + (col[i]) * n);
                TwoSat::ae(adj[i][1] + (1 ^ col[i]) * n, adj[i][2] + (col[i]) * n);
                // III. adj[i][2] 和 col[i] 不同
                TwoSat::ae(adj[i][2] + (1 ^ col[i]) * n, adj[i][0] + (col[i]) * n);
                TwoSat::ae(adj[i][2] + (1 ^ col[i]) * n, adj[i][1] + (col[i]) * n);
            }
            if (!TwoSat::check(n)) {
                for (int i = 1; i <= n; ++i)
                    cout << (col[i] ? 'B' : 'W');
                cout << '\n';
                break;
            }
        }
    }
}
```

---

## 作者：zyn_ (赞：0)

# [ARC161E] Not Dyed by Majority (Cubic Graph)

## 判定

考虑如何判定一个颜色序列是否“可作为操作后的颜色序列”？

设操作前的颜色序列为 $a_i$（不妨使 $a_i=0,1$ 代表黑和白），操作后的颜色序列为 $b_i$。对于点 $i$，$e_{i,j}$（$j=1,2,3$）为与 $i$ 有边相连的三个点。

由操作方法可知 $b_i$ 为 $a_{e_{i,1}}$，$a_{e_{i,2}}$，$a_{e_{i,3}}$ 的众数。

对每个 $i$ 有两种情况。

情况 $1$：$b_i=0$，则 $a_{e_{i,j}}$ 需满足 $6$ 个条件：对 $j\neq k$，若 $a_{e_{i,j}}$ 为 $1$ 则 $a_{e_{i,k}}$ 为 $0$。

情况 $2$：$b_i=1$，则 $a_{e_{i,j}}$ 需满足 $6$ 个条件：对 $j\neq k$，若 $a_{e_{i,j}}$ 为 $0$ 则 $a_{e_{i,k}}$ 为 $1$。

这是一个关于 $a_i$，有 $6n$ 个条件的 2-SAT 问题，可以 $O(n)$ 解决。

## 构造

构造一个不可“作为操作后的颜色序列”的序列。

可以随机生成一个颜色序列 $b_i$，判定其是否“可作为操作后的颜色序列”。若是，则输出 $b_i$，否则重新生成 $b_i$ 继续判定。

事实上，$n\gt 10$ 时，随机的 $b_i$ 不可“作为操作后的颜色序列”的概率是较大的，很快就能找到解。

而 $n\le 10$ 时，不同的 $b_i$ 只有 $2^n$ 个。题目没有要求处理无解的情况，因此可假设有解，则最多期望 $O(2^n)$ 就能找到解。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 100007
int T,n,a,b,e[N][3],c[N],d[N],scc[N],cnt;
bool clr[N],vis[N];
vector<int> f[N],g[N];
inline void addedge(int u,int v){f[u].push_back(v);g[v].push_back(u);}								 
void dfs1(int p){
	vis[p]=1;
	for(int i:f[p])if(!vis[i])dfs1(i);
	d[++cnt]=p;
}
void dfs2(int p){
	scc[p]=cnt;
	for(int i:g[p])if(!scc[i])dfs2(i);
}
bool solve(){
	for(int i=1;i<=n<<1;++i)vis[i]=scc[i]=0;
	cnt=0;
	for(int i=1;i<=n<<1;++i)if(!vis[i])dfs1(i);
	cnt=0;
	for(int i=n<<1;i>=1;--i)if(!scc[d[i]])++cnt,dfs2(d[i]);
	for(int i=1;i<=n;++i)if(scc[i]==scc[i+n])return 1;
	return 0;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)c[i]=0;
		for(int i=1;i<=n*3/2;++i)scanf("%d%d",&a,&b),e[a][c[a]++]=b,e[b][c[b]++]=a;
		while(1){
			for(int i=1;i<=n;++i)clr[i]=rand()&1;
			for(int i=1;i<=n<<1;++i)f[i].clear(),g[i].clear();
			for(int i=1;i<=n;++i)if(clr[i]){
				addedge(e[i][0],e[i][1]+n),addedge(e[i][0],e[i][2]+n);
				addedge(e[i][1],e[i][0]+n),addedge(e[i][1],e[i][2]+n);
				addedge(e[i][2],e[i][0]+n),addedge(e[i][2],e[i][1]+n);
			}else{
				addedge(e[i][0]+n,e[i][1]),addedge(e[i][0]+n,e[i][2]);
				addedge(e[i][1]+n,e[i][0]),addedge(e[i][1]+n,e[i][2]);
				addedge(e[i][2]+n,e[i][0]),addedge(e[i][2]+n,e[i][1]);
			}
			if(solve())break;
		}
		for(int i=1;i<=n;++i)putchar(clr[i]?'B':'W');
		puts("");
	}
	return 0;
}
```

---

## 作者：Register_int (赞：0)

通过~~打表~~ ~~瞎猜~~ 对概率大致的估计可以得知，随机一组解不满足条件的概率大于 $\dfrac12$。

考虑如何判断一个解是否可以操作出来。对于每个节点，只要确定了一个与该点相邻且颜色不同的点，都可以立即确定另两个点的颜色。枚举这三种情况，即可将原问题转化为可满足性问题，直接进行 $\text{2-SAT}$ 计算即可。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e5 + 10;

mt19937 eng(time(0));
uniform_int_distribution<int> dist(0, 1);

vector<int> g[MAXN];

inline 
void insert(int u, int v) {
	g[u].push_back(v);
}

struct edge {
	int v, nxt;
} e[MAXN * 3];

int head[MAXN], tot;

inline 
void add(int u, int v) {
	e[++tot] = { v, head[u] }, head[u] = tot;
}

int dfn[MAXN], low[MAXN], id;

int s[MAXN], top;

int scc[MAXN], cnt;

void tarjan(int u) {
	dfn[u] = low[u] = ++id, s[++top] = u;
	for (int i = head[u], v; i; i = e[i].nxt) {
		v = e[i].v;
		if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if (!scc[v]) low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		for (cnt++; ;) { int x = s[top--]; scc[x] = cnt; if (x == u) break; }
	}
}

inline 
void clear(int n) {
	cnt = id = top = tot = 0;
	for (int i = 1; i <= n << 1; i++) head[i] = 0;
	for (int i = 1; i <= n << 1; i++) dfn[i] = 0;
	for (int i = 1; i <= n << 1; i++) low[i] = 0;
	for (int i = 1; i <= n << 1; i++) scc[i] = 0;
}

int t, n, m, ans[MAXN];

inline 
bool check() {
	for (int i = 1, u, v, w; i <= n; i++) {
		u = g[i][0], v = g[i][1], w = g[i][2];
		if (ans[i]) {
			add(u, v + n), add(u, w + n);
			add(v, u + n), add(v, w + n);
			add(w, u + n), add(w, v + n);
		} else {
			add(u + n, v), add(u + n, w);
			add(v + n, u), add(v + n, w);
			add(w + n, u), add(w + n, v);
		}
	}
	for (int i = 1; i <= n << 1; i++) if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= n; i++) if (scc[i] == scc[i + n]) return 0;
	return 1;
}

int main() {
	for (scanf("%d", &t); t--;) {
		scanf("%d", &n), m = n * 3 >> 1;
		for (int i = 1; i <= n; i++) g[i].clear();
		for (int i = 1, u, v; i <= m; i++) scanf("%d%d", &u, &v), insert(u, v), insert(v, u);
		do {
			clear(n);
			for (int i = 1; i <= n; i++) ans[i] = dist(eng);
		} while (check());
		for (int i = 1; i <= n; i++) putchar(ans[i] ? 'B' : 'W'); puts("");
	}
}
```

---

