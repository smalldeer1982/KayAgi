# Now or later

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=246&page=show_problem&problem=3587

[PDF](https://uva.onlinejudge.org/external/11/p1146.pdf)

# 题解

## 作者：Doubeecat (赞：5)

> [UVA1146 Now or later](https://www.luogu.com.cn/problem/UVA1146)
> 
> 有 $n$ 架飞机需要着陆。 每架飞机都可以选择“早着陆”和“晚着陆”两种方式之一，且必须选择一种。 第 $i$ 架飞机的早着陆时间为 $E_i$，晚着陆时间为 $L_i$，不得在其他时间着陆。 你的任务是为这些飞机安排着陆方式，使得相邻两个着陆时间间隔的最小值（称为安全间隔）应尽量大。
>
> $n \leq 2000,0 \leq t \leq 10 ^ 7$

## 解题思路：

二分 + 2-SAT

首先分析一下题面，观察到**最小值最大**这个点就首先考虑二分。

二分时间间隔 $t$，接下来考虑如何判定在给定安全时间内是否有可行方案。

可以发现，对于一个飞机我们显然可以拆成两个点来处理，一个点表示早降落时间，一个点表示晚降落时间。

然后我们对于飞机两两考虑，我们记 $x_i$ 为第 $i$ 架飞机早到时间，$y_i$ 为第 $i$ 架飞机晚到时间，$x_j$ 为第 $j$ 架飞机早到时间，$y_j$ 为第 $j$ 架飞机早到时间，其中 $x_i > x_j$。

则如果 $x_i - x_j < t$，两个飞机肯定不能一起早着陆，也就是说，如果第 $i$ 架飞机早着陆，则第 $j$ 架飞机必须晚着陆，反之亦然。这里就出现了我们非常熟悉的**二元关系**，考虑使用 2-SAT 解决问题，在每次check的时候重新建图。

上面的约束条件转化为连边就是 $x_i \to y_j,y_i \to x_j$，这样子边的个数是 $n^2$ 级别的，加上二分，时间复杂度为 $O(n^2 \log t)$。

这题比较恶心的一点在于 UVA 原题卡了前向星，建议使用 `vector` （UVA 上是默认开 `-O2` 的），以及点数至少要开到两倍的 $n$

## 代码：

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
using namespace std;
#define ll long long


const int N = 1e4 + 10;

int dfn[N],low[N],c[N],cnt,num,n;
bool ins[N];

stack <int> s;
vector <int> G[N];

void tarjan(int x) {
    dfn[x] = low[x] = ++cnt;
    s.push(x);ins[x] = 1;
    for (int i = 0;i < G[x].size();++i) {
        int v = G[x][i];
        if (!dfn[v]) {
            tarjan(v);
            low[x] = min(low[x],low[v]);
        } else if (ins[v]) {
            low[x] = min(low[x],dfn[v]);
        }
    }   
    if (dfn[x] == low[x]) {
        int y;c[x] = ++num;
        do {
            y = s.top();s.pop();
            c[y] = num;ins[y] = 0;
        } while (x != y);
    }
}

int a[N][2];

bool check(int cap) {
    for (int i = 1;i <= 2 * n;++i) G[i].clear();
    memset(dfn,0,sizeof dfn);
    memset(low,0,sizeof low);
    memset(c,0,sizeof c);
    memset(ins,0,sizeof ins);
    cnt = num = 0;
    for (int i = 1;i <= n;++i) {
        for (int qwq = 0;qwq <= 1;++qwq) {
            for (int j = i + 1;j <= n;++j) {
                for (int qaq = 0;qaq <= 1;++qaq) {
                    if (abs(a[i][qwq] - a[j][qaq]) < cap) {
                        G[i + n * qwq].push_back(j + n * (qaq ^ 1));
                        G[j + n * qaq].push_back(i + n * (qwq ^ 1));
                    }
                }
            }
        }
    }//重新建图的过程
    for (int i = 1;i <= 2 * n;++i) if (!dfn[i]) tarjan(i);
    for (int i = 1;i <= n;++i) {
        if (c[i] == c[i+n]) return 0;
    }
    return 1;
}

void solve() {
    memset(ins,0,sizeof ins);
    tot = 0;
    int l = 0,r = 0,ans = 0;
    for (int i = 1;i <= n;++i) scanf("%d %d\n",&a[i][0],&a[i][1]),r = max(r,a[i][1]);
    while (l < r - 1) {
        int mid = (l + r) >> 1;
        if (check(mid)) l = mid;
        else r = mid;
    }
    cout << l << endl;
    return ;
}

signed main() {
    while (scanf("%d\n",&n) != EOF) solve();
    return 0;
}
```

---

## 作者：hicc0305 (赞：4)

一看就是一道2-SAT的题目，通过二分求出答案，通过2-SAT来检验是否可行

假设我们现在二分出安全时间为t，枚举出两架飞机i，j。i1是i飞机早着陆的时间，i2是晚着陆的时间，j1，j2同理。则如果abs(i1-j1)<t这两架飞机就无法都选择先降落，所以我们将i1->j2连一条边，j1->i2连一条边，表示选i1必须选j2，选j1就必须选i2，连完以后，我们检验是否存在矛盾情况，即一架飞机的两个降落时间都必须选就能判断当前的t是否可行

代码如下
```cpp
#include<cstdio> 
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,cnt=0,p=0;
int a[2*2010],f[2*2010],s[2*2010];
int head[2*2010*2010],nxt[2*2010*2010],to[2*2010*2010];
void addedge(int x,int y)
{
	cnt++;
	nxt[cnt]=head[x];
	head[x]=cnt;
	to[cnt]=y;
}
bool dfs(int x)
{
	int v;
	if(x%2==0) v=x-1;
	else v=x+1;
	if(f[x]) return 1;
	if(f[v]) return 0;
	f[x]=1;
	s[++p]=x;
	for(int i=head[x];i!=-1;i=nxt[i])
		if(!dfs(to[i])) return 0;
	return 1;
}
bool judge()//判断是否可行
{
	for(int i=1;i<2*n;i+=2)
		if(!f[i] && !f[i+1])
		{
			p=0;
			if(!dfs(i))
			{
				while(p>0) f[s[p--]]=0;
				if(!dfs(i+1)) return 0;//如果这架飞机两个时间都不行，就不行
			}
		}
	return 1;
}
int main()
{
	while(scanf("%d",&n)!=EOF)
	{
		int l=0,r=0;
		for(int i=1;i<n*2;i+=2)
			scanf("%d%d",&a[i],&a[i+1]),r=max(r,a[i+1]);
		while(l<=r)
		{
			cnt=0;
			memset(f,0,sizeof(f));
			memset(head,-1,sizeof(head));
			int mid=(l+r)/2;//二分t
			for(int i=1;i<=n*2;i++)
				for(int j=i+i%2+1;j<=n*2;j++)//如上文描述进行连边
					if(abs(a[i]-a[j])<mid)
					{
						int u,v;
						if(i%2==0) u=i-1;
						else u=i+1;
						if(j%2==0) v=j-1;
						else v=j+1; 
						addedge(i,v),addedge(j,u);
					}
			if(judge()) l=mid+1;
			else r=mid-1;
		}
		cout<<l-1<<endl;
	}
	return 0;
}

```

---

## 作者：cosf (赞：2)

## [UVA1146 Now or later](https://www.luogu.com.cn/problem/UVA1146)

~~话说现在 UVa 是不是炸了？~~

十一月六号 UVa 竟然神奇地修好了。

首先，可以把 [那道题](https://www.luogu.com.cn/problem/AT_arc069_d) 切了。过了那道题这题就显得非常简单。

## 思路

### 二分

可以发现，直接求答案非常难。于是我们可以想到用二分答案的方法。

我们二分一个答案，看看能否满足要求即可。

### 2-Sat

我们令 $x_i$ 表示 $i$ 降落的时间。这里不分它是早到（$E_i$）还是晚到（$L_i$）。我们只需要令 $\bar{x}_i$ 表示 $i$ 的另一个降落时间即可。

那么，当我们钦定了 $mid$ 作为答案时，显然对于所有 $|x_i - x_j| \lt mid$ 的 $i, j$，都是两者只能取其一的。这就是典型的 2-Sat 模型。我们可以连两条边 $<x_i, \bar{x}_j>, <x_j, \bar{x}_i>$。相当于 $x_i$ 递推至 $\bar{x}_j$，以及 $x_j$ 递推至 $\bar{x}_i$。如果发现有 $x_i$ 与 $\bar{x}_i$ 互相递推，那么显然就矛盾了。

具体怎么做，就是一个 2-Sat 板子，用强连通分量算法。

到此，这单次 $O(n^2\log t)$ 的复杂度**应该**能通过本题，因为我没有尝试这个复杂度的代码。

### 线段树优化建边

我们能发现，对于一个 $x_i$，我们要将所有 $|x_i - x_j| < mid$ 的 $j$，将 $x_i$ 连一条边到 $\bar{x}_j$。可以发现，满足这个条件的 $x_j$ 一定是一个区间内的。想到区间，我们就可以用线段树。

具体来说，我们可以建立一系列**虚点** $x'_i$，而与之对应的 $x_i$ 则是**实点**。则对于每一个 $x_i$，它要连接到的 $\bar{x}_j$ 所对应的 $\bar{x}'_j$ 的位置一定是属于一个区间的。

注意，$x_i$ 与 $\bar{x}'_i$ 在位置上是相同的。但是，它们的本质是不同的。也就是说，连接到 $\bar{x}'_i$ 并不意味着连接到 $x_i$。

怎么建边？我们可以先将所有虚点连向与之对应的实点。然后给虚点建一棵线段树。线段树除了叶子结点的其他点都给自己两个子节点连边。这样，例如你想连边到 $i \in [1, 3]$ 的每一个 $\bar{x}'_i$，你只需要连接到代表区间 $[1, 2]$ 和 $[3, 3]$ 的线段树点即可。其他的边在建树的时候已经连好了。

最终，边数优化到了 $O(n\log n)$ 级别的。单次测试复杂度 $O(n\log n\log t)$。

## 代码

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <cstring>
using namespace std;

#define MAXN 4005

#define rev(x) (x > n ? x - n : x + n) // 它的对应点，也就是 \bar{x}

using ll = long long;
using pli = pair<ll, int>;

int n;

pli val[MAXN];

namespace SCC // 强连通分量
{
    vector<int> e[MAXN << 2];
    int dfn[MAXN << 2], low[MAXN << 2];
    int idx;

    stack<int> stk;
    bool ins[MAXN << 2];

    int scc[MAXN << 2];
    int cnt;

    void tarjan(int p)
    {
        dfn[p] = low[p] = ++idx;
        stk.push(p);
        ins[p] = true;
        for (int u : e[p])
        {
            if (!dfn[u])
            {
                tarjan(u);
                low[p] = min(low[p], low[u]);
            }
            else if (ins[u])
            {
                low[p] = min(low[p], dfn[u]);
            }
        }
        if (low[p] == dfn[p])
        {
            cnt++;
            while (stk.top() != p)
            {
                int t = stk.top();
                scc[t] = cnt;
                ins[t] = false;
                stk.pop();
            }
            scc[p] = cnt;
            ins[p] = false;
            stk.pop();
        }
    }
};

namespace SGT
{
    struct Tree
    {
        int l, r;
        int v;
    } t[MAXN << 2];
    int idx;
    void build(int p, int l, int r)
    {
        t[p] = {l, r, ++idx};
        if (l == r)
        {
            SCC::e[idx].push_back(rev(val[l].second)); // 虚向实连边
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        SCC::e[t[p].v].push_back(t[p << 1].v);
        SCC::e[t[p].v].push_back(t[p << 1 | 1].v);
    }
    void update(int p, int l, int r, int f) // 从 f 向区间 [l, r] 连边
    {
        if (l > r)
        {
            return;
        }
        if (l <= t[p].l && t[p].r <= r)
        {
            SCC::e[f].push_back(t[p].v);
            return;
        }
        int mid = (t[p].l + t[p].r) >> 1;
        if (mid >= l)
        {
            update(p << 1, l, r, f);
        }
        if (mid < r)
        {
            update(p << 1 | 1, l, r, f);
        }
    }
};

bool check(ll mid)
{
    SGT::idx = 2 * n;
    SCC::idx = 0;
    for (int i = 1; i <= n * 8; i++)
    {
        SCC::e[i].clear();
    }
    while (SCC::stk.size())
    {
        SCC::stk.pop();
    }
    memset(SCC::ins, 0, sizeof(SCC::ins));
    memset(SCC::dfn, 0, sizeof(SCC::dfn));
    memset(SCC::low, 0, sizeof(SCC::low));
    memset(SCC::scc, 0, sizeof(SCC::scc));
    SGT::build(1, 1, 2 * n);
    for (int i = 1; i <= 2 * n; i++)
    {
        int l = upper_bound(val + 1, val + 2 * n + 1, pli{val[i].first - mid, 0x3ffff3ff}) - val; // 不要写错
        int r = lower_bound(val + 1, val + 2 * n + 1, pli{val[i].first + mid, -1}) - val - 1;
        SGT::update(1, l, i - 1, val[i].second);
        SGT::update(1, i + 1, r, val[i].second);
    }
    for (int i = 1; i <= 2 * n; i++)
    {
        if (!SCC::dfn[i])
        {
            SCC::tarjan(i);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (SCC::scc[i] == SCC::scc[i + n])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    while (cin >> n)
    {
        for (int i = 1; i <= n; i++)
        {
            cin >> val[i].first >> val[i + n].first;
            val[i].second = i;
            val[i + n].second = i + n;
        }
        sort(val + 1, val + 2 * n + 1);
        ll l = 0, r = val[2 * n].first - val[1].first + 1;
        while (l < r - 1)
        {
            ll mid = (l + r) >> 1;
            bool res = check(mid);
            if (res)
            {
                l = mid;
            }
            else
            {
                r = mid;
            }
        }
        cout << l << endl;
    }
    return 0;
}

```


---

## 作者：registerGen (赞：1)

[可能更好的阅读体验](https://registergen.github.io/post/solution-uva1391/)

我来补一个 Tarjan 解 2-SAT 问题的代码。

---

本题为 2-SAT + 二分答案练习题。

# Solution

题目让求的是 **最大值的最小值**，考虑二分答案。

题目中每个飞机 **要么是一种状态，要么是另一种状态**，考虑 2-SAT。

然后就是个板子了。。

二分着陆时间间隔的最小值 $x$。

枚举每两个飞机 $i,j$ 的 $4$ 种状态：

||飞机 $i$ 早着陆|飞机 $i$ 晚着陆|
|:-:|:-:|:-:|
|**飞机 $j$ 早着陆**|||
|**飞机 $j$ 晚着陆**|||

设现在枚举的这个情况中，$i$ 的着陆时间为 $a$，$j$ 的着陆时间为 $b$，则若 $|a-b|<x$ 那么就要在相应的状态间连边（此时这两个状态只能二选一）。

建图建好了，题也就做完了。

# Code

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
#include<cstring>

const int N=4000; // 注意数组大小，要开两倍

int n,a[N+10][2];
std::vector<int> G[N+10];
int dfn[N+10],low[N+10],cnt,stk[N+10],inStk[N+10],top,col[N+10],totScc;

// Tarjan
void DFS(int u)
{
	dfn[u]=low[u]=++cnt;
	stk[++top]=u,inStk[u]=1;
	for(size_t i=0;i<G[u].size();i++)
	{
		int v=G[u][i];
		if(!dfn[v])DFS(v),low[u]=std::min(low[u],low[v]);
		else if(inStk[v])low[u]=std::min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u])
	{
		int v;totScc++;
		do v=stk[top--],inStk[v]=0,col[v]=totScc;while(u!=v);
	}
}

// 二分的配套函数 check()
inline bool check(int x)
{
	// 清空图和 Tarjan 要用的数组
	for(int i=1;i<=2*n;i++)
		G[i].clear();
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	cnt=0;
	memset(stk,0,sizeof(stk));
	memset(inStk,0,sizeof(inStk));
	top=0;
	memset(col,0,sizeof(col));
	totScc=0;
	// 建图
	// i 号点表示第 i 个飞机早着陆，i + n 号点表示第 i 个飞机晚着陆
	for(int i=1;i<=n;i++)
		for(int ii=0;ii<=1;ii++)
			for(int j=i+1;j<=n;j++)
				for(int jj=0;jj<=1;jj++)
				{
					if(abs(a[i][ii]-a[j][jj])<x)
					{
						G[i+n*ii].push_back(j+n*(1^jj));
						G[j+n*jj].push_back(i+n*(1^ii));
					}
				}
	// 2-SAT 标准过程
	for(int i=1;i<=2*n;i++)
		if(!dfn[i])DFS(i);
	for(int i=1;i<=n;i++)
		if(col[i]==col[i+n])return 0;
	return 1;
}

inline void solve()
{
	int l=0,r=0,ans=-1;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i][0],&a[i][1]);
		r=std::max(std::max(a[i][0],a[i][1]),r);
	}
	// 二分
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid))ans=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",ans);
}

int main()
{
	while(scanf("%d",&n)!=EOF)
		solve();
	return 0;
}
```

---

## 作者：andyli (赞：1)

“最小值尽量大”的典型处理方法是二分查找最终答案$P$。这样，原来的问题转化为了判定问题“是否存在一个调度方案，使得相邻两个着陆时间差总是不小于$P$”，而这个问题可以进一步转化为：任意两个着陆时间差总是不小于$P$。令bool变量$x_i$表示第$i$架飞机是否早着陆，则唯一的限制就是“时间差小于$P$的两个着陆时间不能同时满足”。例如，若$E_i$和$L_i$的时间差小于$P$，则不能同时满足$x_i=true$和$x_j=false$。每一组不能同时满足的着陆时间对应于一个子句，则整个约束条件对应于一个$2-SAT$问题的实例，包含$n$个变量和不超过$n(n-1)/2$个子句。

考虑到还要在所有$O(n^2)$种可能的答案中二分查找，总时间复杂度为$O(n^2\log n)$。考虑到时间的范围比较大，也可以直接二分时间的数值，时间复杂度为$O(n^2\log T)$，其中$T$为所有时间的最大值。

代码如下：
```cpp
#include <algorithm>
#include <cstring>
#include <vector>
#include <cstdio>
using namespace std;
const int maxn = 20005;

class TwoSAT
{
  public:
	int n;
	vector<int> G[maxn << 1];
	bool mark[maxn << 1];
	int S[maxn << 1], c;

	bool dfs(int x)
	{
		if (mark[x ^ 1])
			return false;
		if (mark[x])
			return true;
		mark[x] = true;
		S[c++] = x;
		for (size_t i = 0; i < G[x].size(); i++)
			if (!dfs(G[x][i]))
				return false;
		return true;
	}

	void add_clause(int x, int xval, int y, int yval)
	{
		x = (x << 1) + xval;
		y = (y << 1) + yval;
		G[x ^ 1].push_back(y);
		G[y ^ 1].push_back(x);
	}

	bool solve()
	{
		for (int i = 0; i < (n << 1); i += 2)
			if (!mark[i] && !mark[i + 1])
				if (c = 0; !dfs(i))
				{
					while (c > 0)
						mark[S[--c]] = false;
					if (!dfs(i + 1))
						return false;
				}
		return true;
	}

	void init(int n)
	{
		this->n = n;
		for (int i = 0; i < (n << 1); i++)
			G[i].clear();
		memset(mark, 0, sizeof(mark));
	}
} solver;

int T[maxn][2], n;
bool check(int diff)
{
	solver.init(n);
	for (int i = 0; i < n; i++)
		for (int a = 0; a < 2; a++)
			for (int j = i + 1; j < n; j++)
				for (int b = 0; b < 2; b++)
					if (abs(T[i][a] - T[j][b]) < diff)
						solver.add_clause(i, a ^ 1, j, b ^ 1);
	return solver.solve();
}

int main()
{
	while (~scanf("%d", &n) && n)
	{
		int L = 0, R = 0;
		for (int i = 0; i < n; i++)
			for (int a = 0; a < 2; a++)
				scanf("%d", &T[i][a]), R = max(R, T[i][a]);
		while (L < R)
		{
			int M = L + ((R - L + 1) >> 1);
			if (check(M))
				L = M;
			else
				R = M - 1;
		}
		printf("%d\n", L);
	}
	return 0;
}
```

---

## 作者：DerrickLo (赞：0)

显然的答案具有二段性，所以我们可以二分答案。

那么这个问题就是一个 2-sat 问题，一个飞机早着陆和晚着陆可以分成两个节点，如果两个节点之间的时间差小于 $mid$，那么就连一条边，然后判断可不可行即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[4005][2],dfn[4005],low[4005],fr[4005],cnt,top,st[4005],ins[4005];
vector<int> ve[4005];
void tarjan(int u){
	dfn[u]=low[u]=++cnt,st[++top]=u,ins[u]=1;
	for(int v:ve[u]){
		if(!dfn[v])tarjan(v),low[u]=min(low[u],low[v]);
		else if(ins[v])low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		cnt++;
		do{
			fr[st[top]]=cnt;
			ins[st[top]]=0;
		}while(st[top--]!=u);
	}
}
bool check(int mid){
	for(int i=1;i<=2*n;i++)ve[i].clear();
	memset(dfn,0,sizeof dfn);
	memset(low,0,sizeof low);
	memset(fr,0,sizeof fr);
	memset(st,0,sizeof st);
	memset(ins,0,sizeof ins);
	top=cnt=0;
	for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)for(int ii=0;ii<2;ii++)for(int jj=0;jj<2;jj++){
		if(abs(a[i][ii]-a[j][jj])<mid){
			ve[i+n*ii].emplace_back(j+n*(1-jj));
			ve[j+n*jj].emplace_back(i+n*(1-ii));
		}
	}
	for(int i=1;i<=2*n;i++)if(!dfn[i])tarjan(i);
	for(int i=1;i<=n;i++)if(fr[i]==fr[n+i])return 0;
	return 1;
}
signed main(){
	while(cin>>n){
		for(int i=1;i<=n;i++)cin>>a[i][0]>>a[i][1];
		int l=0,r=1e7+10,ans=0;
		while(l<=r){
			int mid=l+r>>1;
			if(check(mid))ans=mid,l=mid+1;
			else r=mid-1;
		}
		cout<<ans<<"\n"; 
	}
	return 0;
}
```

---

## 作者：Crazyouth (赞：0)

**分析**

[强化版](https://www.luogu.com.cn/problem/AT_arc069_d)。

不错的 2-SAT 练手题。看到最小值最大，不难想到二分答案 $d$。对于每一个二分出来的 $d$，通过 2-SAT 判断是否合法。具体地，若两个降落时间 $x,y$ 满足 $|x-y|<d$，则 $x$ 或 $y$ 不能降落，于是 2-SAT 的条件就出来了。若这组 2-SAT 无解，就说明这个 $d$ 不合法，反之亦然，继续二分。另外，多测不清空，爆零两行泪。

P.S. 值得注意，UVA 貌似卡链式前向星，请使用 vector 存图。

**AC Code**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e4+10;
vector<int> G[N];
int ins[N],scc[N],dfn[N],low[N],scccnt=0,dfncnt=0,a[N][2],n;//a[i][0]是早降落，a[i][1]是晚降落
stack<int> st;
void tarjan(int u)
{
	dfn[u]=low[u]=++dfncnt;
	ins[u]=1;
	st.push(u);
	for(auto v:G[u])
	{
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(ins[v]) low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u])
	{
		scccnt++;
		while(st.top()!=u)
		{
			scc[st.top()]=scccnt;
			ins[st.top()]=0;
			st.pop();
		}
		scc[st.top()]=scccnt;
		ins[st.top()]=0;
		st.pop();
	}
}
int check(int d)
{
	for(int i=1;i<=(n<<1);i++) G[i].clear();
	memset(dfn,0,sizeof dfn);
	memset(low,0,sizeof low);
	memset(scc,0,sizeof scc);
	memset(ins,0,sizeof ins);
	scccnt=dfncnt=0;
	for(int i=1;i<=n;i++)
	for(int x1=0;x1<=1;x1++)
	for(int j=i+1;j<=n;j++)
	for(int x2=0;x2<=1;x2++)
	{
		if(abs(a[i][x1]-a[j][x2])<d)
		{
			G[i+n*x1].push_back(j+n*(1-x2));
			G[j+n*x2].push_back(i+n*(1-x1));
		}
	}//清空，重新建图
	for(int i=1;i<=(n<<1);i++) if(!dfn[i]) tarjan(i);
	for(int i=1;i<=n;i++) if(scc[i]==scc[i+n]) return 0;
	return 1;
}
int main()
{
	while(cin>>n)
	{
		memset(ins,0,sizeof ins);
		int l=0,r=0;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i][0]>>a[i][1];
			r=max(r,a[i][1]);
		}
		while(l<r-1)//二分答案
		{
			int mid=(l+r)>>1;
			if(check(mid)) l=mid;
			else r=mid;
		}
		cout<<l<<endl;
	}
	return 0;
}

---

## 作者：GenesisQ (赞：0)

## UVA1391 Now or Later

**题目描述**

有 $n$ 架飞机需要着陆。 每架飞机都可以选择“早着陆”和“晚着陆”两种方式之一，且必须选择一种。 第 $i$ 架飞机的早着陆时间为 $E_i$，晚着陆时间为 $L_i$，不得在其他时间着陆。 你的任务是为这些飞机安排着陆方式，使得相邻两个着陆时间间隔的最小值（称为安全间隔）应尽量大。

**分析**

最小值最大的问题很容易想到是用二分查找最终答案$P$,这样原来的问题就转化为了二分求$P$的最小值,满足任意两个着陆时间差总是不小于$P$。

那么我们可以用$\,bool$ 变量 $x_i$ 来表示第 $i$ 架飞机是否早着陆，则唯一的限制是时间差小于 $P$ 的两个着陆时间不能同时满足。

---

我们为每架飞机 $i$ 设置两个结点 $2i$ 和 $2i+1$，如果标记了 $2i$ 代表飞机晚着陆 ， 如果标记了 $2i+1$ 则代表飞机早着陆。

对于每组 $abs(L_i - L_j) < P$ 或 $abs(E_i - E_j) < P$ 的飞机 $i,\,j$，我们连接 $2i\,-\!>2j\,xor\,1$ 和 $2j\,-\!>2i\,xor\, 1$ 两条有向边。


---

建好图之后就是一个普通的 $2-SAT$ 问题了，从某一个没有赋值 $x_i$ 的顶点开始，我们假定它为假，那么标记结点 $2i$ ，并且沿着有向边标记所有能标记的结点，如果标记过程中发现某个变量对应的两个结点都被标记，那么$x_i$为假这个假设就不成立，需要修改为$x_i$ 为真，然后重新标记。

需要注意的是，这个算法并没有回溯过程，否则时间复杂度将不可承受，如果当前变量不管是真还是假都引起矛盾，那么可以说明这个问题无解。

**代码**

```cpp
#include <iostream>
#include <cmath>
#include <memory.h>
#include <stack>
#include <vector>
#define rep(i, x, y) for(int i = x; i < y; i++)
#define set(a, i) memset(a, i, sizeof a)
using namespace std;
const int N = 4005;
vector<int> V[N];
int n, l, r, mid, ed;
int t[N][2];
bool flag[N];
stack<int> s;
bool dfs(int x)
{
	 if(flag[x]) return true;
	 if(flag[x ^ 1]) return false;
	 flag[x] = true; s.push(x);
	 for(int i = 0; i < V[x].size(); i++)
		  if(!dfs(V[x][i])) return false;
	 return true;
}
bool col()
{
	 rep(i, 0, n) if(!flag[2 * i] && !flag[2 * i + 1])
	 {
		  if(!dfs(2 * i))
		  {
			   while(!s.empty()) flag[s.top()] = false, s.pop();
			   if(!dfs(2 * i + 1)) return false;
		  }
	 }
	 return true;
}
bool check(int val)
{
	 set(flag, 0); 
	 rep(i, 0, 2 * n) V[i].clear();
	 while(!s.empty()) s.pop();
	 rep(i, 0, n) rep(p, 0, 2) rep(j, i + 1, n) rep(q, 0, 2)
		  if(abs(t[i][p] - t[j][q]) < val) 
		  {
			   V[2 * i + p].push_back(2 * j + !q);
			   V[2 * j + q].push_back(2 * i + !p);
		  }
	 return col();
}
int main()
{
	 while(cin >> n)
	 {
		  rep(i, 0, n) cin >> t[i][0] >> t[i][1];
		  l = r = 0;
		  rep(i, 0, n) r = max(max(t[i][0], t[i][1]), r);
		  while(l + 1 < r)
		  {
			   int mid = l + r >> 1;
			   if(check(mid)) l = mid;
					else r = mid;
		  }
		  cout << l << endl;
	 }
	 return 0;
}
```


---

## 作者：happybob (赞：0)

板子。

考虑二分答案，每个点只有两种选择，并且对于任意两个点之间有一些逻辑关系。假设二分的是 $x$，则 $|a_i-a_j| < x$ 表示 $i$ 和 $j$ 不能同时选早着陆。对于其他的也一样。

显然这是个 2-SAT 问题，直接做就可以了，复杂度平方对数。

可以使用线段树优化建图做到线性对数平方。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

const int N = 4005;

int n, a[N], b[N];
vector<int> G[N];
int dfn[N], low[N], idx;
int stk[N], top;
bool in_stk[N];
int id[N], cnt;

void tarjan(int u)
{
	stk[++top] = u;
	dfn[u] = low[u] = ++idx;
	in_stk[u] = 1;
	for (auto& j : G[u])
	{
		if (!dfn[j])
		{
			tarjan(j);
			low[u] = min(low[u], low[j]);
		}
		else if (in_stk[j])
		{
			low[u] = min(low[u], dfn[j]);
		}
	}
	if (dfn[u] == low[u])
	{
		int y = 0;
		cnt++;
		do
		{
			y = stk[top--];
			in_stk[y] = 0;
			id[y] = cnt;
		} while (y != u);
	}
}

inline bool check(int x)
{
	for (int i = 1; i <= 2 * n; i++) G[i].clear(), G[i].shrink_to_fit(), dfn[i] = low[i] = in_stk[i] = 0;
	cnt = 0;
	idx = 0;
	top = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (i == j) continue;
			if (abs(a[i] - a[j]) < x && abs(a[i] - b[j]) < x)
			{
				G[i].emplace_back(i + n);
			}
			else
			{
				if (abs(a[i] - a[j]) < x)
				{
					G[i].emplace_back(j + n);
				}
				else if (abs(a[i] - b[j]) < x) G[i].emplace_back(j);
			}
			if (abs(b[i] - a[j]) < x && abs(b[i] - b[j]) < x)
			{
				G[i + n].emplace_back(i);
			}
			else
			{
				if (abs(b[i] - a[j]) < x) G[i + n].emplace_back(j + n);
				else if (abs(b[i] - b[j]) < x) G[i + n].emplace_back(j);
			}
		}
	}
	for (int i = 1; i <= 2 * n; i++)
	{
		if (!dfn[i]) tarjan(i);
	}
	for (int i = 1; i <= n; i++) if (id[i] == id[i + n]) return 0;
	return 1;
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	while (cin >> n)
	{
		for (int i = 1; i <= n; i++)
		{
			cin >> a[i] >> b[i];
		}
		int l = 0, r = 10000001, ans = -1;
		while (l <= r)
		{
			int mid = l + r >> 1;
			if (check(mid)) ans = mid, l = mid + 1;
			else r = mid - 1;
		}
		cout << ans << "\n";
	}
	return 0;
}
```


---

