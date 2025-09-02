# [USACO22JAN] Tests for Haybales G

## 题目描述

Farmer John 的奶牛们决定为 Farmer Nhoj 农场的奶牛们举办一场编程竞赛。为了使问题尽可能有趣，他们花费了大量时间来构造具有挑战性的测试用例。特别是对于一个问题，「Haybales」，奶牛们需要你的帮助来设计具有挑战性的测试用例。这有关解决以下这个有些奇妙的问题：

有一个有序整数数组 $x_1 \leq x_2 \leq \dotsb \leq x_N$（$1 \leq N \leq 10^5$），和一个整数 $K$。你不知道这个数组以及 $K$，但你知道对于每个索引 $i$ 使得 $x_{j_i} \leq x_i + K$ 的最大索引 $j_i$。保证有 $i\le j_i$ 以及 $j_1\le j_2\le \cdots \le j_N\le N$。

给定这些信息，Farmer John 的奶牛需要构造任意一个数组以及整数 $K$ 与该信息一致。构造需要满足对于所有 $i$ 有 $0 \leq x_i \leq 10^{18}$，并且 $1 \leq K \leq 10^{18}$。

可以证明这一定是可行的。请帮助 Farmer John 的奶牛们解决这一问题！

## 说明/提示

【样例解释】

输出样例为数组 $a=[1,6,17,22,27,32]$ 以及 $K=6$。 $j_1=2$ 被满足是由于 $a_2=6 \le 1+6=a_1+K$ 而 $a_3=17>1+6=a_1+K$，从而 $a_2$ 是最大的不超过 $a_1+K$ 的元素。类似地：

- $j_2=2$ 被满足是由于 $a_2=6 \le 6+6$ 而 $a_3=17>6+6$；
- $j_3=4$ 被满足是由于 $a_4=22 \le 17+6$ 而 $a_5=27>17+6$；
- $j_4=5$ 被满足是由于 $a_5=27 \le 22+6$ 而 $a_5=32>22+6$；
- $j_5=6$ 被满足是由于 $a_6=32 \le 27+6$ 且 $a_6$ 是数组的最后一个元素；
- $j_6=6$ 被满足是由于 $a_6=32 \le 32+6$ 且 $a_6$ 是数组的最后一个元素。

对于输入样例，这并不是唯一正确的输出。例如，你也可以输出数组 $[1,2,4,5,6,7]$ 和 $K=1$。

【数据范围】

- 所有测试点的 $50\%$ 满足 $N \le 5000$。
- 其余测试点没有额外限制。

【说明】

本题采用自行编写的 [Special Judge](https://www.luogu.com.cn/paste/kzgvkesl)。如果对此有疑问或想要 hack，请[私信编写者](https://www.luogu.com.cn/chat?uid=137367)或[发帖](https://www.luogu.com.cn/discuss/lists?forumname=P8098)。

## 样例 #1

### 输入

```
6
2 2 4 5 6 6```

### 输出

```
6
1
6
17
22
27
32```

# 题解

## 作者：耶梦加得 (赞：15)

首先，这是道构造题~~废话~~。其中 50 分的部分分可以用差分约束来做（与正解无关）。

经过实践，我们发现题目给的这个 $j_i$ 相当不友好，不如统统加上 $1$，这样它就代表第一个大于 $x_i+K$ 的数所在位置，这个条件相对比较好转化。

~~但也还是没那么好想。~~

我们建立一棵有 $n+1$ 个节点的树，对于每个节点，与父亲 $j_i+1$ 连一条边。易知根为 $n + 1$。

![样例解释，来自官方题解（好丑）](https://cdn.luogu.com.cn/upload/image_hosting/a0onictu.png)

~~这是有多经费不足才画出这种东西（恼）~~

由于 $j_i$ 不降，可以发现层次高（即靠近根节点，见图）的节点编号一定大于层次低的节点。并且 $j_i+1$ 层次恰好比 $i$ 大 $1$ ~~还是废话。~~

又根据构造条件，$x[j_i+1]$ 应当大约比 $x[i]$ 大 $K$。由此可以猜测每个节点权值为 $d[i] * K + x'(0 \le x' < K)$。

接下来确定 $x'$ 如何赋值。首先我们对于同一层的节点，按照编号从大到小考虑，由于加边顺序从小到大，用链式前向星可以自然地实现这一点（当然 vector 也无非就是倒序循环的事情）。

我们要使得同一层排在后面的节点，$x'$ 都小于它的任意子节点，与此同时，它自己的 $x'$ 要大于它的任意儿子。

~~自己的孩子归自己管，别人管不着~~

我们发现 $dfs$ 序完美地**不**符合这个条件。于是我们令 $x' = K - dfn[i]$。~~（逃~~

（官方样例解释实在太丑，不放了）

由于 $x' \ge 0$，令 $K \ge n + 1$ 即可。~~不过要注意规定的 $x_i$ 范围。~~

```cpp
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
#include<vector>
#define miu 100007
using namespace std;
inline int read() {
    register int x = 0; register char ch = getchar();
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') {x = x * 10 + ch - 48; ch = getchar();}
    return x;
}
struct edge {
    int v, nxt;
}e[miu];
int head[miu], eid;
inline void insert(int x, int y) {
    e[++eid].v = y; e[eid].nxt = head[x]; head[x] = eid;
}
int ans[miu], d[miu], bonus, n, k;
void dfs(int x) {
    ans[x] = bonus--;
    for(int i = head[x]; i; i = e[i].nxt) {
        int to = e[i].v;
        d[to] = d[x] + 1;
        dfs(to);
    }
}
int suc;
signed main() {
    n = read(); k = n + 2; bonus = n + 1;
    for(int i = 1; i <= n; ++i) {
        suc = read(); insert(++suc, i);
    }
    dfs(n + 1);
    printf("%d\n", k);
    for(int i = 1; i <= n; ++i) {
        printf("%lld\n", 1ll * k * (d[1] - d[i]) + ans[i]);
    }
    return 0;
}

```


---

## 作者：Little09 (赞：3)

第一眼拿到这题，想到的应该直接就是差分约束！不妨令 $K=n+1$，对于每个条件（第 $i$ 个点输入是 $j$）是这样的约束关系：

$$a_j-a_i\le K(1)$$

$$a_{j+1}-a_i\ge K+1(2)$$


再补充上：

$$a_{i+1}-a_i \ge 0(3)$$

按照以上三个条件连边即可。于是你发现样例就过了，提交发现居然 $50\%$。然后发现 SPFA 死了。以下是 Luogu $48$ 分代码（通过 $50\%$）：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=5e5+5;
const ll inf=100000000000000000;
ll dis[N],v[2*N];
int vis[N],n,m,k;
int cnt,nxt[2*N],t[2*N],h[2*N],num[2*N];
inline void add(int x,int y,int z) //x-y<=z
{
	swap(x,y);
	t[++cnt]=y;
	v[cnt]=z;
	nxt[cnt]=h[x];
	h[x]=cnt;
}
queue <int> q;
void spfa(int s)
{
	for (int i=1;i<=n;i++) dis[i]=inf,vis[i]=0;
	dis[s]=0,vis[s]=1,num[s]=1;
	q.push(s);
	while (!q.empty())
	{
		int u=q.front();
		q.pop();
		vis[u]=0;
		for (int i=h[u];i;i=nxt[i])
		{
			if (dis[t[i]]>dis[u]+v[i])
			{
				dis[t[i]]=dis[u]+v[i];
				if (vis[t[i]]==0)
				{
					vis[t[i]]=1;
					num[t[i]]++;
					if (num[t[i]]>n)
					{
						printf("NO");
						exit(0);
					}
					q.push(t[i]);
				}
			}
		}
	}
}
inline int read()
{
	char C=getchar();
	int F=1,ANS=0;
	while (C<'0'||C>'9')
	{
		if (C=='-') F=-1;
		C=getchar();
	}
	while (C>='0'&&C<='9')
	{
		ANS=ANS*10+C-'0';
		C=getchar();
	}
	return F*ANS;
} 
int main()
{
	n=read(),k=n+1;
	for (int i=1;i<=n;i++)
	{
		int x=read();
		if (x!=i) add(x,i,k);
		if (x!=n) add(i,x+1,-k-1);
	}
	for (int i=1;i<=n;i++) add(i,0,0);
	for (int i=1;i<n;i++) add(i,i+1,0);
	spfa(0);
	printf("%d\n",k);
	for (int i=1;i<=n;i++) printf("%lld\n",dis[i]+inf);
	return 0;
}
```

因为存在负权边，所以不能使用 Dij 等其他最短路算法。那么怎么解决负权？

先把原序列切成几段，每碰到一个 $i=j_i$ 的就切一下。显然段和段之间不影响。对于每一个段，我们再考虑分层。最后一个是第 $0$ 层，其他的第 $i$ 个就是 $j_i$ 的层数再加一。

我们令第 $i$ 层的初始权值为 $-iK$。这样会发现，条件 $(1)$ 中的 $i,j$ 必然隔一层，那么 $K$ 就消掉了。条件 $(2)$ 中 $i,j+1$ 割一层或两层，两层的话就不用考虑，否则 $K$ 也消掉了。条件 $(3)$ 对于同一层的照样做就行了。

于是原来的条件的权值只有 $0$ 和 $1$ 了，容易发现图变成了 DAG，因此可以线性求出最长路。

记得把每个数改为非负整数，还有段和段之间的间隔要注意。

```cpp
// By: Little09
// Problem: P8098 [USACO22JAN] Tests for Haybales G
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8098
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=5e5+5;
const ll inf=100000000000000000;
ll dis[N],v[2*N],k;
int a[N];
bool used[N];
int n,m;
int cnt,nxt[2*N],t[2*N],h[2*N],d[N];
inline void add(int x,int y,int z) //x-y>=z
{
	swap(x,y);
	t[++cnt]=y;
	v[cnt]=z;
	nxt[cnt]=h[x];
	h[x]=cnt;
	d[y]++;
}
queue<int>q;
void topo(int s,int l,int r)
{
	for (int i=l;i<=r;i++) dis[i]=0,used[i]=0;
    q.push(s);
    dis[s]=0;
    for (int i=l;i<=r;i++) if (d[i]==0) q.push(i);
    while (!q.empty())
    {
    	int u=q.front();
    	q.pop();
    	for (int i=h[u];i;i=nxt[i])
    	{
    		d[t[i]]--;
    		dis[t[i]]=max(dis[t[i]],dis[u]+v[i]);
    		if (d[t[i]]==0) q.push(t[i]);
    	}
    }
}
inline int read()
{
	char C=getchar();
	int F=1,ANS=0;
	while (C<'0'||C>'9')
	{
		if (C=='-') F=-1;
		C=getchar();
	}
	while (C>='0'&&C<='9')
	{
		ANS=ANS*10+C-'0';
		C=getchar();
	}
	return F*ANS;
} 
int deth[N];
void work(int l,int r,ll qwq)
{
	deth[r]=0;
	for (int i=0;i<=cnt;i++)
	{
		nxt[i]=0,v[i]=0,t[i]=0;
	}
	for (int i=l;i<=r;i++) h[i]=0,d[i]=0;
	h[0]=0,d[0]=0;
	cnt=0;
	for (int i=r-1;i>=l;i--) deth[i]=deth[a[i]]+1;
	for (int i=l;i<r;i++)
	{
		if (deth[i]==deth[i+1])
		{
			add(i+1,i,0);
		}
	}
	for (int i=l;i<r;i++)
	{
		add(i,a[i],0);
		if (a[i]+1<=r&&deth[a[i]+1]==deth[a[i]]) 
			add(a[i]+1,i,1);
	}
	for (int i=l;i<=r;i++) add(i,0,0);
	topo(0,l,r);
	for (int i=l;i<=r;i++) dis[i]-=1ll*deth[i]*k;
	for (int i=r;i>=l;i--) dis[i]-=dis[l];
	for (int i=l;i<=r;i++) dis[i]+=qwq;
	
}
int main()
{
	n=read(),k=n+1;
	for (int i=1;i<=n;i++) a[i]=read();
	int las=1;
	ll tmp=0;
	for (int i=1;i<=n;i++)
	{
		if (a[i]==i) 
		{
			work(las,i,tmp+k+1);
			las=i+1,tmp=dis[i];
		}
	}
	printf("%lld\n",k);
	for (int i=1;i<=n;i++) printf("%lld\n",dis[i]);
	return 0;
}
```


---

## 作者：zhiyangfan (赞：3)

> 有一个长为 $n$ 的递增的整数数组满足 $x_1\le x_2\le \cdots\le x_n$ 和一个整数 $k$。你不知道这个数组 $x$ 和这个整数 $k$，但你知道对于每个下标 $i$ 满足 $x_{j_i}\le x_i+k$ 的最大下标 $j_i$。保证 $i\le j_i$，且 $j_1\le j_2\le \cdots\le j_n\le n$。通过 $j$ 数组，构造一个任意数组 $x$ 和整数 $k$ 满足上述条件，需要满足 $1\le x_i,k\le 10^{18}$，可以证明答案一定存在。($1\le n\le 10^5$)

神仙构造题。考虑把题目中的关系描述为树形的关系，具体来讲是连 $j_i+1\rightarrow i$ 的边，这样能形成一棵外向树，其中父子关系 $u\rightarrow v$ 表示 $u$ 是第一个满足 $x_u>x_v+k$ 的下标。显然这样会多出一个虚节点 $n+1$，它就是根，且不管怎么样都可以防止形成森林。

接下来我们发现对于树上同一层的结点，我们关心的是它们之间比较“微小”的数量变化，而对于不同层的结点我们关心的是“较大”的数量变化。能发现，这里大小的定义就是与 $k$ 的关系，父亲结点和儿子结点之间的差“大约”是 $k$，而同层只需要考虑递增的条件微调一下即可。

有了这个发现，我们就可以定义每个结点的权值是 $h_ik+y_i(0\le x_i<k)$，其中 $h_i$ 是该点距离最深的叶子结点的距离，可以形象理解为高度。我们发现这个权值完全符合刚刚的分析，不同层之间差的大约是 $k$，还有 $y_i$ 之间的小小调整，而同层之间只有 $y_i$ 之间的小小调整。现在的目标就是恰当的给 $y_i$ 赋值了。

给 $y_i$ 赋值的限制在于满足原题递增的限制，因为一旦数组递增，其他的限制都能被满足。我们发现，如果从根节点开始 $\rm dfs$，每次访问子节点都按照编号从大到访问，满足 $y_i$ 按照访问次序递减，就能满足条件。首先因为 $h_ik$，高层一定大于低层，而又因为 $i\le j_i$，高层编号一定大于低层编号，所以大体上的递增是满足的。而每次我们又是按照编号从大到小访问子节点的，同层的又能保证递增（容易发现不同的父亲结点对应的儿子集合的编号是个区间且不会相交，且是按照父亲结点的大小排列的），所以整体满足递增。

至于 $k$ 的选择，因为 $y_i$ 要 $n$ 个结点人手一个，还要保证单调递减（这是因为父亲结点和儿子结点之间的关系是 $<$，所以 $y_i$ 也要单调递减），所以 $k$ 选 $n+1$ 就好，每次 $-1$。好了，分析完这么多，实现一遍 $\rm dfs$ 就能搞定，时间复杂度 $\mathcal{O}(n)$。
```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
const int N = 1e5 + 10; std::vector<int> T[N]; int dep[N], x[N], now, mx;
void dfs(int u, int depth)
{
	dep[u] = depth; x[u] = now--;
	for (auto v : T[u]) dfs(v, depth + 1);
}
int main()
{
	int n; scanf("%d", &n);
	for (int i = 1, j; i <= n; ++i) scanf("%d", &j), T[j + 1].push_back(i);
	for (int i = 1; i <= n + 1; ++i) std::sort(T[i].begin(), T[i].end(), [](const int& a, const int& b) { return a > b; });
	now = n + 1; dfs(n + 1, 0); for (int i = 1; i <= n + 1; ++i) mx = std::max(mx, dep[i]);
	printf("%d\n", n + 1);
	for (int i = 1; i <= n; ++i) printf("%lld\n", 1ll * (mx - dep[i]) * (n + 1) + x[i]);
	return 0;
}
```

---

## 作者：喵仔牛奶 (赞：1)

## Solution

结合题目的不降性质可以发现，$j_i+1$ 是第一个满足 $x_j>x_i+k$ 的位置。

连边 $(j_i+1)\to i$，形成了一棵以 $n+1$ 为根的树。对于 $p\to q$，限制为以下两个：
- $x_p>x_q+k$；
- $x_{p-1}\le x_q+k$。

令 $d_i$ 为 $i$ 的深度，可以发现 $d_1\le d_2\le\cdots\le d_n$，归纳证明不难。我们令 $x_i=k\times(d_1-d_i)$ 即可满足第一个限制。

考虑第二个限制，我们需要微调一下，设给 $x_i$ 加上 $t_i$。首先对于 $p\to q$，要有 $t_p\ge t_q$，且 $\forall u\in[q+1,p),t_i\le t_q$。

可以发现一种方式是遍历树是从大到小遍历儿子，设 $u$ 是第 $b_i$ 个被遍历到的点，令 $t_u=n-b_i$。不难发现对于 $p\to q$，遍历到 $q$ 时，$[q+1,p)$ 里面的点都没有遍历过，满足条件。

由于 $t_i\in[0,n)$，可以任意选择一个 $\ge n$ 的 $k$。代码里选择了 $k=n$。

## Code

```cpp
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
using namespace std;
namespace Milkcat {
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 1e6 + 5;
	LL n, ct, k, fa[N], d[N], dfn[N];
	vector<int> G[N];
	void dfs(int x) {
		dfn[x] = ct --, sort(ALL(G[x]), greater<int>());
		for (int y : G[x])
			d[y] = d[x] + 1, dfs(y);
	}
	int main() {
		cin >> n;
		REP(i, 1, n) cin >> fa[i], G[fa[i] + 1].pb(i);
		ct = n + 1, dfs(n + 1), k = n;
		cout << k << '\n';
		REP(i, 1, n)
			cout << k * (d[1] - d[i]) + dfn[i] << '\n';
		return 0;
	}
}
```

---

## 作者：IamZZ (赞：1)

**G组练习总结#9**

思维构造题，限制很宽松，在数据范围限制上没有为难人~~纯纯就是构造难度~~。

### 题目大意

FJ 给 FN 的奶牛出了一道题目，叫 Haybales，这个题目现在出好了哈，他决定向全世界招募免费劳工给他出样例！

这个样例可不好出，具体来说，FJ 会给我们一个长度为 $n(n\leq10^5)$ 的序列 $j$，而我们要构造一个同样长度的序列 $x$ 要满足以下条件：

首先，序列 $x$ 必须单调不下降；

其次，对于所有 $x_i$ 满足 $0\leq x_i\leq10^{18}$；

最后，我们要自己定一个 $k(1\leq k\leq10^{18})$，对于 $\forall i$，$j_i$ 是最右边一个满足 $x_{j_i}\leq x_i+k$ 的位置。

题目保证 $j$ 单调不下降，且一定有可行构造。

现在，选手们，请开始你的表演！

### 解题思路

USACO 官方题解给的思路，看大家写得都差不多。

题目给的限制我们可以稍微转化一下，$j_i$ 是最右边的……那就说明，$j_i+1$ 一定是第一个不满足条件的位置？

没错，那我们可以确定一些位置之间会至少有的固定的 $k$ 大小差距，我们不妨把给所有的点分层，每一层之间都会差 $k$ 的大小关系。

按照这个方法，我们可以把限制条件转化成节点之间的关系，比如，把 $j_i+1$ 定为 $i$ 的父亲，表示 $j_i+1$ 一定要与 $i$ 处在不同的层。

我们可以发现，这个“图”建出来之后，会是一个有 $n+1$ 个点 $n$ 条边的树（引入了 $n+1$ 号点）！

看看图理解一下？

![](https://cdn.luogu.com.cn/upload/image_hosting/h07uqyj3.png)

没错，按照这个方式分层，我们就可以处理好 $k$ 这个限制，第 $p$ 层的每一个节点都会比 $p-1$ 的每一个节点大至少 $k$。

但是，结束了吗？

别忘了我们还有第二个限制，$x$ 单调不下降……

我们设 $i$ 点的最终值为 $d_i\times k+v_i$，如何设置 $v_i$，让单调性的限制得以满足？

观察一下性质，同一层里，编号大的 $v$ 要比编号小的大，父亲的 $v$ 比儿子的大。

那我们好像可以推出最终的构造方法了：

设一开始 $v=n+1$，先访问编号大的节点的子树，给父亲赋 $x$ 后 $x-1$，往下递归，子树处理完后再处理后面的子树。

因为不同子树之间没有相互影响，我们这样构造是正确的。

这时我们也可以发现，让 $k=n+1$，可以杜绝越级的现象了，多方便！

复杂度 $\Theta(n)$，而最大的答案也不过 $10^{10}$ 次方级别，没有超出限制。

完结撒花(●'◡'●)

### 参考代码

```c++
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N=1e5+5;
int n,x,c,m,d[N],v[N];
ll w;
struct edge
{
	int t,e,h;
}e[N];
void add(int u,int v)
{
	++c;
	e[c].t=v;
	e[c].e=e[u].h;
	e[u].h=c;
	return ;
}
void search(int p)
{
	int i;
	v[p]=x,--x,m=max(m,d[p]);//赋值
	for(i=e[p].h;i;i=e[i].e)
	{
		d[e[i].t]=d[p]+1;//这时的层数是反的，要拿d[1]减一下
		search(e[i].t);
	}
	return ;
}
int main()
{
	int i;
	scanf("%d",&n);
	for(i=1;i<=n;++i)//链式前向星可以很好的解决访问最大编号的问题，因为前向星是倒序访问，我们只要正序加边就好啦~
	  scanf("%d",&x),add(x+1,i);//分层
	x=n+1;//给所有v[i]赋值
	search(n+1);
	for(i=1;i<=n;++i)
	  d[i]=m-d[i];//处理正确的层数
	printf("%d\n",n+1);//简易处理k
	for(i=1;i<=n;++i)
	  w=1ll*(n+1)*d[i]+v[i],printf("%lld\n",w);//计算答案
	return 0;
}
```





---

## 作者：凑个热闹吖 (赞：1)

# [[USACO22JAN] Tests for Haybales G](https://www.luogu.com.cn/problem/P8098)

这是一道极为简单的构造题。

# Solution

>- 对于每一个最大索引 $j_i$，如果 $j_i \neq i$，我们连一条 $j_i$ 向 $i$ 的边，最后很容易就发现形成了若干棵树（根节点为 $j_i = i$ 的节点）。

>- 如果用 vector 存边，很容易就可以发现对于一棵树，节点编号是从下到上，从左到右依次加一的。

举个例子，对于 

`5 5 5 6 7 7 7`

建出来的树如下。

![](https://cdn.luogu.com.cn/upload/image_hosting/8gl6shfv.png)

>- 对于树上的每一个点，将值设为
$$Ans_i = diff - depth_i \times k + dfn_i$$

>> 其中 $diff$，$k$ 可以随便设（只要够大就行），$depth_i$ 为 $i$ 节点的深度，$dfn_i$ 为 $i$ 节点的 dfs 序。

>- 证明正确性：~~显然易证~~

>- 每处理完一棵树 $diff$ 都要加上一个较大的数，以免两棵树之间互相干扰。

# Code

```
#include<bits/stdc++.h>
#define rep(i , m , n) for(register int i = m; i <= n; i++)
#define int long long

using namespace std;
const int Dif = 1e12;
int k = 1e6 , diff = 1e12;
vector<int> e[100005];
int n , a[100005] , tot = 0;
void Change(int u , int dep){
	for(int i = 0; i < e[u].size(); i++)a[e[u][i]] = diff - k * dep + tot , tot++ , Change(e[u][i] , dep + 1);
}
signed main(){
	scanf("%lld" , &n);
	rep(i , 1 , n){
		int x;
		scanf("%lld" , &x);
		if(x != i)e[x].push_back(i);
		else a[i] = diff , tot = 1 , Change(i , 1) , diff += Dif;
	}
	printf("%lld\n" , k);
	rep(i , 1 , n)printf("%lld\n" , a[i]);
	return 0;
}
```


---

## 作者：End1essSummer (赞：0)

解：构造。

(用柿子证明了高赞题解里的一些结论)

我们发现一个最基础的，我们可以把原来的式子变一下：$x_{j_i+1} > x_i+K$ 意义在于 $j_i+1$ 是第一个比 $i$ 大的。

然后我们可以去连边，将其变为一棵树，这一棵树从上自下应该是递减的。而且我们希望他们之间的差肯定要小于我们设的 $K$ 嘛。

再观察一下：由于我们后面的数是一定大于前面的数的！所以如果我们对原来这棵树跑一遍后序遍历的 dfs，那么跑出来的 $dfn$ 是不是一定**不**满足我们得出来的关系呢？

(这一步真的太绝了...)

那么这是否也就意味着，我们把 $dfn_i$ 全部都换成 $n-dfn_i$ 就可以至少在任意一条链上满足这个条件？？

ok，事实证明这一点应该是比较正确的，然后我们把视角往回转到题目的限制条件，这一点该如何解决呢？即：

$x_{j_i} \leq x_i + K$ 且 $j_i$ 是满足此条件的最大索引。

或者说 $x_{j_i+1} > x_i+K$ 且 $j_i+1$ 是满足此条件的最小索引。

因为刚才我们小小的做了一些操作，我们现在把它拿到一个树上来考虑，早上好油哀思诶丝哦，现在我有 $dfn$ 序列。

假设说现在有一点 $now$，我们把它的儿子设为 $son$，那么一定有：

$ n - dfn_{son} + nums_{son} + K \leq n - dfn_{now} + nums_{now}$

$ dfn_{son} - dfn_{now} + nums_{now} - nums_{son} \geq K$

由于我们并不知道 $son$ 究竟是它众多儿子中的哪一个，我们在这个式子中的  $dfn_{son} - dfn_{now}$ 不妨按照上界 $-1$ 进行求取，这样的话才能保住等号同时让其他值也成立：

$nums_{now} - nums_{son} \geq K+1$

我们可以看到一个非常有趣的现象，如果说我们想要满足题目要求的话：即对于一个点来说，除了他的 $n-dfn[i]$ 本身，它的 $x[i]$ 居然还跟其深度 $deep[i]$ 有关联，具体而言，一些节点深度越浅，那么他的相应的值就越高！

那么我们直接将剩下一部分设为 $(deep[1]-deep[i]) \times K$ 不就好啦？现在 $x[i] = (deep[1]-deep[i]) \times K + n-dfn[i] $。

（ 1 一定是个叶子结点，具体为何自己体会。）

接下来的话我们发现一个问题，那么就是 $K$ 的下界还没有定啊？？

比较简单的考虑方法是，现在假设说有这样一棵树，他的根是 $n+1$，并且有两个儿子 $son_l$，$son_r$。其中左儿子非常非常大，它的子树有 $n-1$ 个点，而它的右儿子非常非常小，只有它孤零零的一个点。那么为了满足前文条件，我们是否就有：

$ n - dfn_{son_r} + nums_{son_r} \leq n - dfn_{son_l} + nums_{son_l} + K$       

$\Rightarrow dfn_{son_l} - dfn_{son_r} \leq K$

左柿子在极端情况下，通过挪动左儿子子树内的点可使的值为 $n$，因此


$\Rightarrow n \leq K$

这也就是说，只要 $K$ 取到大于等于 $n$ 的情况，就一定能使任意方案成立！

那么 $K$ 出来了，往这道题 $x[i]$ 的表达式一套，答案就出来了。

结束。

---

## 作者：littleKtian (赞：0)

对于所有的 $i$，从点 $i$ 往点 $j_i$ 连边（$i=j_i$ 的不连），于是有若干个树，且每棵树内包含的点序号为一个连续段。

对每棵树分别处理。

把序号最大的点（也就是满足 $i=j_i$ 的点）看作根，对于所有点，将其的所有儿子按序号从小到大的顺序从左往右放置，深度相同的点放在同一行。可以发现序号大小满足从最底行往上，从左往右点的序号依次 $+1$。

从根开始按从左往右的顺序进行 dfs，设 $dep_i$ 表示点 $i$ 的深度，$dfn_i$ 表示 dfs 序，将点 $i$ 的权值设为 $-dep_i\times K+dfn_i$ 即可满足（$K$ 即为题意中的 $K$，其值只要足够大即可）。

根据这棵树的结构容易证明是对的。

最后调节一下，将点权全部改为非负，相邻树之间调节一下差值即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,j[100005],lt;
ll x[100005],d=3e12;
int dr()
{
	int xx=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')xx=xx*10+ch-'0',ch=getchar();
	return xx*f;
}
vector<int> b[100005];int dfn;
void work(int xh,ll dd)
{
	++dfn,x[xh]=dd+dfn;
	sort(b[xh].begin(),b[xh].end());
	for(int i=0,in=b[xh].size();i<in;i++)
	{
		int v=b[xh][i];work(v,dd-d);
	}
}
int main()
{
	n=dr();
	for(int i=1;i<=n;i++)
	{
		j[i]=dr();
		if(j[i]==i)
		{
			work(i,0);
			ll mn=x[lt+1];
			for(int k=lt+1;k<=i;k++)x[k]-=mn;
			if(lt)for(int k=lt+1;k<=i;k++)x[k]+=x[lt]+d+1;
			lt=i;
		}
		else b[j[i]].push_back(i);
	}
	printf("%lld\n",d);
	for(int i=1;i<=n;i++)printf("%lld\n",x[i]);
}
```


---

