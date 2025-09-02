# [ICPC 2015 WF] Tours

## 题目描述

给定一张 $n$ 个点 $m$ 条边的无向图，你需要选择一个颜色种类数 $k$，然后用这 $k$ 种颜色给每条边染色，要求对于图中任意一个简单环，每种颜色的边的数量都相同。求所有可行的 $k$。

保证图无重边，无自环。

## 样例 #1

### 输入

```
4 5
1 2
2 3
3 4
1 4
1 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
6 6
1 2
2 3
1 3
1 4
2 5
3 6
```

### 输出

```
1 3
```

# 题解

## 作者：x义x (赞：10)

参考资料：[yhx 博客](https://yhx-12243.github.io/OI-transit/records/lydsy4116%3Blg6914%3Bgym101239K.html)

> **题目大意.**
>
> 给定一个无向图。你要找出所有的 $k$，使得存在一种把边染色为 $1\sim k$ 的方案，满足任何一个简单环中每种颜色的边数量恰相等。保证图中至少有一个环。
>
> $n,m\le 10^3$。

考虑所有简单环，记 $u(cyc,i)$ 表示简单环 $cyc$ 包含了边 $i$，记 $w(c,i)$ 表示 $i$ 的颜色是否为 $c$。于是我们可以列出 $k$ 个方程组，其中第 $c$ 号如下：
$$
\forall cyc,\sum_iu(cyc,i)w(c,i)=|cyc|/k
$$
或者可以写成
$$
\forall cyc,\sum_iu(cyc,i)(kw(c,i)-1)=0
$$
我们自然会考虑把这个东西消元，消元的结果可以直接说明：**有什么除了环以外的，别的东西是 $0$**。当然我们暂时还不知道它是啥。

最好消元过程中还能保证每一行的系数都有意义，这样我们还能联系上一点图论知识。

值得注意的是下面这种消元方法：

> 我们可以获得任意两个环的交。
>
> 注意到 $cyc_1\operatorname{xor} cyc_2$ 必定也是环，从而
> $$
> \dfrac{cyc_1+cyc_2-(cyc_1\operatorname{xor} cyc_2)}2
> $$
> 即可。

可以发现环的交的异或还是环的交，于是我们可以获得交，交的交，交的交的交……最后会变成什么呢？

----

定义两个在某边双连通图 $G$ 上的边**切边等价**，当且仅当：在任何 $G$ 的简单环中，这两条边要么同时出现要么同时不出现。

- 显然地，切边等价是一个**等价关系**。（下面把切边等价记为 $\sim$）

- 易证：两条边切边等价等价于，从 $G$ 中删去这两条边后 $G$ 不连通。

- > 如果 $e_1\sim e_2$，那么删去 $e_1$ 后 $e_2$ 不能在任何环中，否则就是找到了一个不包含 $e_1$ 却包含 $e_2$ 的简单环；于是此时删去 $e_2$，$G$ 必不连通。
  >
  > 反之，若删去 $e_1$ 后 $e_2$ 是割边，根据类似的论述立即得 $e_1\sim e_2$。

- 易证：两条边切边等价等价于，**任取包含了它们的 $G$ 的生成树 $T$，不存在非树边跨过其中一条却不跨过另一条**。这个描述比前两者具体了很多。

自然地 $G$ 中的边被划为数个等价类 $E_i$。（$E_i$ 是易求的，删掉某边后求割边即可）

----

不错，最终能交出的恰好就是所有的 $E_i$。于是不妨把之前的方程组写成以 $E_i$ 为变元的形式。

显然 $E_i$ 要么完全包含于 $cyc$ 要么完全与之无交，所以原来的 $u(cyc,i)$ 记号仍可沿用。

记 $w(c,i)$ 为 $E_i$ 中颜色为 $c$ 的边的数量，则有
$$
\forall cyc,\sum_{i}u(cyc,i)(kw(c,i)-|E_i|)=0
$$
我们知道，这个方程组消元的结果必定是
$$
\forall i,kw(c,i)-|E_i|=0
$$
即，**对于任何 $E_i$，其染色都是"均匀"的**。没有别的性质了吗？是的没有了，这个新方程组已经显然满秩了。

显然 $\forall i$，$k$ 都是 $|E_i|$ 的因子。自然会考虑 $k=\gcd E_i$ 是否可行。实际上在 $E_i$ 内部乱填就行了，毕竟 $E_i$ 要么完全包含于 $cyc$ 要么完全与之无交。

----

对于本题，按理来说我们应该对每个边双连通分量分别按上述结论进行判定，但实际上对非割边直接跑就行了。

代码如下。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn = 2005;

int n;
vector<int> G[maxn];
int banu, banv;
namespace Tarjan {
	int dfn[maxn], low[maxn], idx;
	int ans, qaq[maxn];
	void Tarjan(int x, int fa) {
		dfn[x] = low[x] = ++idx;
		for (int y : G[x]) {
			if (x == banu && y == banv) continue;
			if (x == banv && y == banu) continue;
			if (y == fa) continue;
			if (!dfn[y]) Tarjan(y, x);
			low[x] = min(low[x], low[y]);
		}
		if (fa != 0 && low[x] == dfn[x]) ans++, qaq[x] = -fa;
		else qaq[x] = fa;
	}
	void clear() {
		memset(dfn, 0, sizeof(dfn));
		memset(low, 0, sizeof(low));
		memset(qaq, 0, sizeof(qaq));
		idx = ans = 0;
	}
}

int qaq[maxn], tans;

int main() {
	int m;
	scanf("%d%d", &n, &m);
	while (m--) {
		int u, v; scanf("%d%d", &u, &v);
		G[u].push_back(v), G[v].push_back(u);
	}
	Tarjan::clear();
	for (int i = 1; i <= n; i++)
		if (!Tarjan::dfn[i]) Tarjan::Tarjan(i, 0);

	memcpy(qaq, Tarjan::qaq, sizeof(qaq));
	tans = Tarjan::ans;
	int ans = 0;
	for (banu = 1; banu <= n; banu++)
	for (int i : G[banu]) {
		banv = i;
		if (banv == -qaq[banu]) continue;
		if (banu == -qaq[banv]) continue;
		Tarjan::clear();
		for (int i = 1; i <= n; i++)
			if (!Tarjan::dfn[i]) Tarjan::Tarjan(i, 0);
		ans = __gcd(ans, Tarjan::ans - tans + 1);
	}
	for (int i = 1; i <= ans; i++) if (ans % i == 0) printf("%d ", i);
}
```

---

## 作者：tzc_wk (赞：8)

[洛谷题面传送门](https://www.luogu.com.cn/problem/P6914)

神仙题。

~~深夜写题解感受真好~~

我们考虑两个简单环 $C_1,C_2$​​​，我们假设颜色种类数为 $k$​​​，那么我们需要有 $C_1,C_2$​​​ 均符合条件，而由于 $C_1\oplus C_2$​​​ 也是环，因此我们也必须有 $C_1\oplus C_2$​​​ 符合条件。不难发现 $C_1,C_2,C_1\oplus C_2$​​​ 这三个环是由 $C_1-(C_1\cap C_2),C_2-(C_1\cap C_2),C_1\cap C_2$​​​ 这三部分两两组合得到的，记 $X=C_1-(C_1\cap C_2),Y=C_2-(C_1\cap C_2),Z=C_1\cap C_2$​​​，那么 $C_1,C_2,C_1\oplus C_2$​​​ 这三个条件均符合条件可以等价于 $X+Y,X+Z,Y+Z$​​​ 均符合条件。因此我们猜测 $C_1,C_2,C_1\oplus C_2$​​​ 均符合条件的充要条件是 $X,Y,Z$​​​ 上的染色都是“均匀”的，事实也的确如此，充分性显然，必要性的话大概就如果 $X,Y,Z$​​​ 中某种颜色的出现次数大于其大小除以 $k$​​​，那么不妨设是 $X$​​​ 中颜色 $c$​​​ 的出现次数大于 $\dfrac{|X|}{k}$​，假设 $\Delta=cnt-\dfrac{|X|}{k}$​​​，其中 $cnt$​ 为颜色 $c$​ 在 $X$​ 中的出现次数。那么在 $Y$​ 中 $c$​ 的出现次数必然是 $\dfrac{|Y|}{k}-\Delta$，$Z$ 也同理，这样颜色 $c$ 在 $Y,Z$ 中的出现次数就是 $\dfrac{|Y|+|Z|}{k}-2\Delta$，不符合题意。

因此我们考虑这样一个过程：将所有简单环放入一个边集组成的集合 $S$。表示对于集合 $S$ 中的所有边集，其染色必须是均匀的。每次取出集合中两个有交的边集 $E_1,E_2$ 并将它们删除，然后将 $E_1-(E_1\cap E_2),E_2-(E_1\cap E_2),E_1\cap E_2$ 重新加入边集，重复以上步骤直至不能再操作为止。那么进行这样的步骤之后 $S$ 中的元素有什么性质呢？不难发现对于两条边 $e_1,e_2$，如果它们都在某个环上出现过，并且存在一个环 $C$ 满足 $e_1\in C,e_2\notin C$，那么 $e_1,e_2$ 最终肯定不在 $S$ 中的同一个边集中，因为咱们这个过程中只有 split，没有 merge，因此如果它们本来就不在同一个边集中，那么在接下来的过程中肯定就更不会在了。反之，而对于两条边 $e_1,e_2$，如果它们都在某个环上出现过，并且对于所有环 $C$，都有 $e_1,e_2$ 要么同时被包含在 $C$ 中，要么同时不属于 $C$，那么 $e_1,e_2$ 肯定自始至终不会被分开，最终也肯定在同一集合中，因此我们得到性质：

> Observation. 两条边 $e_1,e_2$ 最终在 $S$ 中的同一集合中的充要条件是，它们都在某个环上出现过，并且对于所有环 $C$，都有 $e_1,e_2$ 要么同时被包含在 $C$ 中，要么同时不属于 $C$。​

考虑怎么将这个性质与答案挂钩。注意到我们在处理 $S$ 中边集的过程中，始终有这样一条原则：对于 $S$ 中所有边集，其染色必须是均匀的，即所有颜色的边在这个边集中的出现次数必须相同。因此对于最终的 $S$，其符合条件的**必要条件**是 $\forall E\in S,k\mid E$。但这是否是充要条件呢？注意到如果 $k$ 符合上述约定，那如果 $S$ 中所有边集我们都对其进行均匀染色，那最终每个环肯定也是均匀的，因为最终每个边集中的每条边要么同时属于某个环，要么同时不属于，它们是一个整体，不会被拆开。

也就是说，我们只要求出最终 $S$ 中每个元素大小的 $\gcd$，设为 $d$，那么最终答案组成的集合肯定恰好包含所有 $d$ 的约数。考虑怎么求这个 $\gcd$。显然我们要求出每个边集的大小对吧，那么注意到对于两个边 $e_1,e_2$ 而言，其在同一个集合中等价于 $e_1,e_2$ 都不是割边（否则它们就不可能在某个简单环上），并且 $G$ 去掉 $e_1,e_2$ 后得到的图不连通。这下就好办了，枚举每一条非割边，然后统计删掉这条边后割边的数量，然后算下与原图中割边数量的差，然后求个 $\gcd$ 即可。

时间复杂度 $\mathcal O(m^2)$。据说可以用某些神奇的随机权值+XOR 哈希的方法实现更优秀的复杂度，但是我不会（

```cpp
const int MAXN=2000;
const int MAXM=2000;
int n,m,hd[MAXN+5],to[MAXM*2+5],nxt[MAXM*2+5],ec=1,ban=0,ans=0;
void adde(int u,int v){to[++ec]=v;nxt[ec]=hd[u];hd[u]=ec;}
int U[MAXN+5],V[MAXN+5];bool is[MAXM+5],_is[MAXM+5];
int dfn[MAXN+5],low[MAXN+5],tim=0,res=0,_res=0;
void tarjan(int x,int f){
	dfn[x]=low[x]=++tim;
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f||(e>>1)==ban) continue;
		if(!dfn[y]){
			tarjan(y,x);chkmin(low[x],low[y]);
			if(low[y]>dfn[x]) is[e>>1]=1,res++;
		} else chkmin(low[x],dfn[y]);
	}
}
void work(){
	memset(dfn,0,sizeof(dfn));memset(low,0,sizeof(low));tim=res=0;
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i,0);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&U[i],&V[i]);
		adde(U[i],V[i]);adde(V[i],U[i]);
	} work();memcpy(_is,is,sizeof(is));_res=res;
	for(int i=1;i<=m;i++) if(!_is[i]){
		ban=i;work();ans=__gcd(ans,res-_res+1);
	}
	for(int i=1;i<=m;i++) if(ans%i==0) printf("%d ",i);
	return 0;
}
```



---

## 作者：FutaRimeWoawaSete (赞：5)

**P6914**

从 ix35 论文来的！

深受震撼！！！！！！

---------------------------------------------------

我们考虑一个很奇怪的想法：如果你看过 ix35 的论文，你就会知道所有简单环都可以由环空间的一个基进行线性组合得来。

其中一个基的构造是，找到每个联通分量的 dfs 树，然后只找每条返祖边和树上路径组成的环构成一组基，所有的简单环都可以由这些基进行线性组合得到。

我们考虑切边等价。大胆猜结论：按照切边等价划分等价类，设第 $i$ 个等价类是 $U_i$，那么答案就是 $\gcd(|U_i|)$。

切边等价指的是，两条边 $e_1,e_2$ 等价当且仅当它们被覆盖的简单环集合相同。

ix35 之后使用了 FWT 进行说明，但是我们有一个更直观的理解思路：

- 在此之前，我们还是要阐明一个大多数题解证明的结论，即假设两个相交的环 $A,B$，我们拆成三部分 $S_1,S_2,S_3$ 分别表示 $A$ 对应在对称差的部分，$B$ 对应在对称差的部分和两个环的交，注意都是边集。可以发现 $S_1,S_2,S_3$ 必须平均划分颜色，否则经过讨论会不合法（这个感觉还是比较简单的，如果你真的没看懂看看其它题解的说法会清楚很多，过于~~平凡~~就不讲了）；

- 有了这个结论，我们就可以说明我们所需求的就是这些 $\gcd(|S_1|,|S_2|,|S_3|)$ 的 $\gcd$，我们可以证明的是我们只需要求出所有的切边等价类的 $\gcd$ 就行了。

- 显然每个切边等价类会被纳入 $\gcd$ 的贡献，即它们肯定是某两个环的交（否则切边等价类肯定会拓展，并且它们也不会细分了，否则就不是切边等价类了）

- 而其中的 $S_1,S_2$ 如果不是同一个切边等价类，那么它们肯定可以细分成**许多个切边等价类拼在一起**，根据更相减损法，最后要被纳入贡献的 $|S_1|$ 一定会被细分的若干个切边等价类 $U_1,U_2,U_3,\dots U_k$，在计算 $\gcd(|U_1|,|U_2|,|U_3|,\dots |U_k|)$ 时就已经被计算贡献了。

也许不太严谨？可能反倒是一种理解，如果你会直接数学证明是再好不过的！！！

然后就是怎么求所有切边等价类。一个确定性算法是，你发现根据切边等价的定义，同一切边等价类的边被覆盖的简单环集合相同，删去其中一条边，切边等价类剩余的边肯定都没有简单环覆盖，那么它就是割边，直接再跑 tarjan 就可以维护了。

我是一条笨笨军犬怎么办？ix35 的论文中提到一个想法：我们实际维护的时候只需要维护每条边被基中的环（树路径加一条非树边组成的环）的覆盖情况，相同就切边等价（其它环由基中的环线性组合得到），那么我们直接上 hash，先随便找棵 dfs 树，找到返祖边就随机一个权值上去，然后对于路径上的边打按位异或的树上差分标记，最后值相同的个就可以默认是切边等价的。

瓶颈在排序，你喜欢可以写 $O(n)$，code $O(n \log n)$。

也就比 $O(n ^ 2)$ 快一点。无语了。

```cpp
#include "bits/stdc++.h"
using namespace std;
#define ll long long
#define int ll
const int Len = 3005 + 5;
mt19937 rnd(time(0));
uniform_int_distribution<ll> op1(0 , (1ll << 62));
int n,m,head[Len],cnt,dfn[Len],low[Len],tim,ist[Len],vis[Len],dep[Len],fa[Len];
ll bot[Len],tbot[Len],cc[Len];int len,idd[Len];
struct node
{
	int next,to,ID;
}edge[Len << 1];
inline void add(int from,int to,int id)
{
	edge[++ cnt].to = to;
	edge[cnt].ID = id;
	edge[cnt].next = head[from];
	head[from] = cnt;
}
void tarjan(int u,int fa)
{
	dfn[u] = low[u] = ++ tim;
	for(int e = head[u] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(!dfn[to])
		{
			tarjan(to , u);
			low[u] = min(low[u] , low[to]);
			if(low[to] > dfn[u])
			{
				ist[edge[e].ID] = 1;
			}
		}
		else if(to != fa)
			low[u] = min(low[u] , dfn[to]);
	}
}
int ve[Len];
void dfs(int u,int f)
{
	//printf("###%d\n",u);
	dep[u] = dep[f] + 1;
	vis[u] = 1;
	fa[u] = f;
	for(int e = head[u] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		//printf("eee%d\n",edge[e].ID);
		if(to == f) continue;
		if(vis[to])
		{		
			if(dep[to] < dep[u] && dep[to] != dep[u] - 1)
			{
				ve[edge[e].ID] = 1;//printf("!!!%d\n",edge[e].ID);
				tbot[edge[e].ID] = op1(rnd);
				bot[u] ^= tbot[edge[e].ID] , bot[to] ^= tbot[edge[e].ID];
			}
		}
		else
		{
			idd[to] = edge[e].ID;
			ve[edge[e].ID] = 1;
			//printf("!!!%d\n",edge[e].ID);
			dfs(to , u);
		}
	}
}
void DFS(int u,int f)
{
	vis[u] = 1;
	for(int e = head[u] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == f) continue;
		if(dep[to] != dep[u] + 1) continue;
		DFS(to , u);
		bot[u] ^= bot[to];
	}
	//printf("%d %lld\n",u,bot[u]);
}
inline ll gcd(ll a,ll b)
{
	if(!b) return a;
	return gcd(b , a % b);
}
signed main()
{
	scanf("%lld %lld",&n,&m);
	for(int i = 1 ; i <= m ; i ++)
	{
		int x,y;scanf("%lld %lld",&x,&y);
		add(x , y , i) , add(y , x , i);
	}
	for(int i = 1 ; i <= n ; i ++) if(!dfn[i]) tarjan(i , 0);
	memset(vis , 0 , sizeof vis);
	for(int i = 1 ; i <= n ; i ++) if(!vis[i]) dfs(i , 0);
	memset(vis , 0 , sizeof vis);
	for(int i = 1 ; i <= n ; i ++) if(!vis[i]) DFS(i , 0);
	//for(int i = 1 ; i <= m ; i ++) if(!ve[i]) printf("xxx%d\n",i);
	for(int i = 2 ; i <= n ; i ++) 
	{
		if(ist[idd[i]]) continue;
		tbot[idd[i]] = bot[i];
	}
	for(int i = 1 ; i <= m ; i ++) 
	{
		if(ist[i]) continue;
		cc[++ len] = tbot[i];
	}
	sort(cc + 1 , cc + 1 + len);
	//printf("%d\n",len);
	//for(int i = 1 ; i <= len ; i ++) printf("%d %lld\n",i,cc[i]);
	ll GCD = 0;
	for(int l = 1 , r = 0 ; l <= len ; l = r + 1)
	{
		r = l;
		while(r + 1 <= len && cc[r + 1] == cc[l]) r ++;
		GCD = gcd(GCD , r - l + 1);
	}
	vector<int> Pt;
	for(int i = 2 ; i * i <= GCD ; i ++) 
	{
		if(GCD % i == 0) 
		{
			Pt.push_back(GCD / i);
			if(i * i != GCD) Pt.push_back(i);
		}
	}
	Pt.push_back(1);if(GCD != 1) Pt.push_back(GCD);
	sort(Pt.begin() , Pt.end());const int SZ = (int)Pt.size();for(int j = 0 ; j < SZ ; j ++) printf("%lld ",Pt[j]);
	return 0;
}
```

---

## 作者：tkdqmx (赞：4)

#### 切边等价

在一个边双连通图中，定义两条切边等价当且仅当在 $G$ 的任何一个简单环中这两条边要么同时出现，要么同时不出现。

定义等价于在 $G$ 中删去这两条边后 $G$ 不连通，等价于在 $G$ 的任意一棵生成树 $T$ 中，假设 $e_1$，$e_2$ 为树边，不存在任何一条非树边跨过其中一条边而不跨过另一条边。

求等价类时，考虑为每条非树边设置一个随机权值，定义树边的权值为所有跨过它的非树边的权值异或和，显然这是一个非确定性算法，但正确率很高，且确定性算法复杂度较高，所以该算法适用面更广。

对于树边，若权值为 $0$，则为割边，并可按权值划分等价类，权值计算可以通过树上差分完成。

#### ICPC2015 WF Tours

首先如果对于一个由多个简单环组成的环，若组成它的简单环均满足条件则它一定满足条件，我们就不用处理这种环，接下来考虑对于两个起点只出现一次的简单环 $A$，$B$，可以知道 $A \oplus B$ 也必须要满足条件，将这三个环拆分成 $A \cap B$，$A - A\cap B$ 和 $B - A\cap B$，可以证明 $A$，$B$ 和 $A \cap B$ 都是其中两个拆分的合并，接下来按此递归直到所有的边集无交，随后答案就是这些边集大小 $\gcd$ 的因数，而两条边在同一边集的条件就是在所有的简单环内必须同时出现/不出现，刚好就是切边等价类。

代码如下：
~~~cpp
#include<bits/stdc++.h>
using namespace std;
#define N 2005
vector<pair<int,int>> v[N];
int n,m,ans,tr[N],rk[N],vis[N],num[N],sam[N],use[N];
void dfs1(int x){
    vis[x]=1;
    for(auto [y,i]:v[x]){
        if(use[i]++)  continue;
        if(!vis[y])  {dfs1(y);continue;}
        tr[x]^=(rk[i]=num[i]=rand()),tr[y]^=num[i];
    }
}
void dfs2(int x){
    vis[x]=0;
    for(auto [y,i]:v[x]){
        if(!vis[y])  continue;
        dfs2(y),tr[x]^=(rk[i]=num[i]=tr[y]);
    }
}
int main(){
    srand(time(NULL)),scanf("%d%d",&n,&m);
    for(int i=1,x,y;i<=m;i++){
        scanf("%d%d",&x,&y);
        v[x].emplace_back(y,i),v[y].emplace_back(x,i);
    }
    for(int i=1;i<=n;i++)  if(vis[i]==0)  dfs1(i);
    for(int i=1;i<=n;i++)  if(vis[i]==1)  dfs2(i);
    sort(rk+1,rk+m+1);int cnt=unique(rk+1,rk+m+1)-rk-1;
    for(int i=1;i<=m;i++)  sam[lower_bound(rk+1,rk+cnt+1,num[i])-rk]++;
    for(int i=1;i<=cnt;i++)  if(rk[i])  ans=gcd(ans,sam[i]);
    for(int i=1;i<=ans;i++)  if(ans%i==0)  printf("%d ",i);
}
~~~

---

## 作者：MSqwq (赞：4)

其实这道题的关键在于找到每个简单环的边数，所以我们考虑如何处理简单环
显然，在一个简单环中，删去一条边，剩下的边就会变为割边  
所以就可以得出做法：枚举原图非桥边，删去该边，处理出新增的桥边数量，所有数量 $+1$ 的 $\gcd$ 所有的因数即为答案  

下面是代码:
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m;
struct qwe{
    ll next,to,id;
}e[5020];
struct qwq{
	ll a,b;
}a[2020];
ll k=1,elast[2020];
void add(ll x,ll y,ll z)
{
    e[++k].to=y;
    e[k].next=elast[x];
    e[k].id=z;
    elast[x]=k;
}
ll dfn[2020],low[2020],tot,ans,sum;
ll v[2020],v_[2020],_v[2020];
ll gcd(ll x,ll y)
{
	return y?gcd(y,x%y):x;
}
void tarjan(ll x,ll fa)
{
    dfn[x]=low[x]=++tot;
    int qwe;
    for(int i=elast[x];i;i=e[i].next)
    {
        if(i^fa^1)
        {
            qwe=e[i].to;
            if(dfn[qwe])low[x]=min(low[x],dfn[qwe]);
            else
            {
                tarjan(qwe,i);
                low[x]=min(low[x],low[qwe]);
                if(low[qwe]>dfn[x])_v[e[i].id]=1;
            }           
        }
    }
}
void clean()
{
    k=1;
    memset(elast,0,sizeof elast);
    memset(dfn,0,sizeof dfn);
    memset(low,0,sizeof low);
    memset(_v,0,sizeof _v);
}
int main()
{
	scanf("%lld%lld",&n,&m);
    for(int i=1;i<=m;i++)
    {
    	scanf("%lld%lld",&a[i].a,&a[i].b);
        add(a[i].a,a[i].b,i);
        add(a[i].b,a[i].a,i);
    }
    for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i,0);
    for(int i=1;i<=m;i++)v_[i]=_v[i];
    for(int i=1;i<=m;i++)
    {
        if(v_[i]!=0||v[i]!=0)continue;
        v[i]=1,sum=1;
        clean();
        for(int j=1;j<=m;j++)
        {
            if(j!=i)
            {
                add(a[j].a,a[j].b,j);
                add(a[j].b,a[j].a,j);               
            }
        }
        for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i,0);
        for(int i=1;i<=m;i++)
        {   
            if(v_[i]==0&&_v[i]!=0)
            {
                v[i]=1;
                sum++;
            }
        }
        ans=gcd(ans,sum);
    }
    for(int i=1;i<=ans;i++)if(ans%i==0)printf("%d ",i);
}
```



---

## 作者：Polaris_Australis_ (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P6914)

考虑环套环：

容易发现，环套环一共是三环，任意一条边一定属于且仅属于两个环，且所属环编号相同的边一定可以构成一条链。现在恰好有三类链，假设三个环编号分别为 $h_1,h_2,h_3$，三条链分别为 $l_1,l_2,l_3$，假设现在钦定有三种颜色，数量为 $x,y,z$，并给每个环（或链）给定一个二元组 $ele=(ele_1,ele_2)$，两个元素分别表示 $x-y,y-z$，根据题意可列出如下方程：

$$ele_{h_1}=ele_{h_2}=ele_{h_3}=(0,0)$$

由于两链组成一个环得：

$$\left\{\begin{array}{l}
ele_{l_1}+ele_{l_2}=ele_{h_1}\\
ele_{l_2}+ele_{l_3}=ele_{h_2}\\
ele_{l_1}+ele_{l_3}=ele_{h_3}
\end{array}\right.$$

联立得：

$$ele_{l_1}=ele_{l_2}=ele_{l_3}=(0,0)$$

由此可以推广到：所属环编号完全相同的边组成的链，每种颜色数量相等。这样问题就变成了对于所有这样的链，每种颜色数量都相同。

然后开始找这样的链。考虑使用 $\text{tarjan}$：观察图发现，桥边一定不在环上，不做考虑，对于非桥边，暴力枚举，把当前边删除，然后再跑一遍 $\text{tarjan}$，所有新增的桥边都是和当前所删的的边所属环编号完全相同的边，这些边共同组成一条符合上述条件的链。

求出所有链长的 $\gcd$，这个值的所有约数都是符合条件的答案。

代码：

```cpp
// Problem: P6914 [ICPC2015 WF]Tours
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6914
// Memory Limit: 500 MB
// Time Limit: 1875 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define int long long
#define maxy(x, y) x = max(x, y)
#define miny(x, y) x = min(x, y)
#define lowbit(x) (x & (-x))
#define fu(i, l, r) for (int i = l; i <= r; ++i)
#define fd(i, r, l) for (int i = r; i >= l; --i)
#define mem(x, y) memset(x, y, sizeof(x))
using namespace std;
namespace Std {
void read(int &x) {
  x = 0;
  int y = 1;
  char c = getchar();
  while (c < '0' || c > '9') {
    if (c == '-') y = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    x = (x << 1) + (x << 3) + (c & 15);
    c = getchar();
  }
  x *= y;
}
void write(int x) {
  if (x < 0) {
    putchar('-');
    write(-x);
    return;
  }
  if (x > 9) write(x / 10);
  putchar((x % 10) | 48);
}
int n, m, in[20001], to[20001], nxt[20001], head[5001],
    cnt = 1, dfn[5001], stack[5001], top = 0, tot = 0, low[5001], belong[5001];
bool mark[20010];
vector<int> ans, vec;
void add(int x, int y) {
  in[++cnt] = x;
  to[cnt] = y;
  nxt[cnt] = head[x];
  head[x] = cnt;
}
void tarjan(int x, int rt) {
  dfn[x] = low[x] = ++tot;
  stack[++top] = x;
  for (int i = head[x]; i; i = nxt[i]) {
    if (mark[i]) continue;
    if ((~rt) && (i == (rt ^ 1))) {
      continue;
    }
    if (!dfn[to[i]]) {
      tarjan(to[i], i);
      low[x] = min(low[x], low[to[i]]);
    } else {
      if (i) {
        low[x] = min(low[x], dfn[to[i]]);
      }
    }
  }
  if (low[x] == dfn[x]) {
    cnt++;
    int a = 0;
    while (x != a) {
      a = stack[top--];
      belong[a] = cnt;
    }
  }
}
int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }
int main() {
  read(n);
  read(m);
  for (int i = 1; i <= m; i++) {
    int x, y;
    read(x);
    read(y);
    add(x, y);
    add(y, x);
  }
  cnt = 0;
  for (int i = 1; i <= n; i++) {
    if (!dfn[i]) {
      tarjan(i, -1);
    }
  }
  int le = 0;
  fu(i, 1, m) if (belong[in[i * 2]] != belong[to[i * 2]]) mark[i * 2 + 1] =
      mark[i * 2] = 1;
  fu(i, 1, m) {
    if (belong[in[i * 2]] == belong[to[i * 2]] && (!mark[i * 2])) {
      mark[i * 2] = mark[i * 2 + 1] = 1;
      mem(dfn, 0);
      vec.push_back(i);
      tot = cnt = top = 0;
      fu(j, 1, n) {
        if (!dfn[j]) tarjan(j, -1);
      }
      int tle = 1;
      fu(j, 1, m) {
        if ((!mark[j * 2]) && belong[in[j * 2]] != belong[to[j * 2]]) {
          tle++;
          mark[j * 2] = mark[j * 2 + 1] = 1;
          vec.push_back(j);
        }
      }
      for (auto j : vec) mark[j * 2] = mark[j * 2 + 1] = 0;
      le = gcd(le, tle);
    }
  }
  for (int i = 1; i * i <= le; ++i) {
    if (!(le % i)) {
      ans.push_back(i);
      if (le / i != i) ans.push_back(le / i);
    }
  }
  sort(ans.begin(), ans.end());
  for (auto i : ans) printf("%lld ", i);
  return 0;
}
}  // namespace Std
#undef int
int main() { return Std::main(); }
```


---

## 作者：chenxia25 (赞：2)

我们称若干个不相交的简单环的并叫做复合环，也就是每个点为偶度的边集。如果每个简单环都满足条件，那么所有复合环显然也都满足条件。考虑两个简单环 $A,B$，那么 $A\oplus B$ 显然必定是复合环，它也要满足条件。我们将 $A\cup B$ 拆成三个不相交的部分：$S_1=A\cap B,S_2=A-A\cap B,S_3=B-A\cap B$，那么 $A,B,A\oplus B$ 都由其中恰好两个组成。直觉告诉我们 $S_1,S_2,S_3$ 这三个边集都要满足条件。显然它们满足条件是 $A,B,A\oplus B$ 的充分条件，但是必不必要呢？反证，不妨设 $S_1$ 中某个颜色数量偏少，那么 $S_2,S_3$ 的该颜色都要偏多，那么 $S_2\cup S_3$ 该颜色必定偏多，不行，必要性得证。

于是简单环 $A,B$ 就可以等价地拆成 $S_1,S_2,S_3$ 这三个不相交的边集来完成条件。然后还可以对其它的边集对（此时不只有简单环了）进行这样拆，直到场上剩下的所有边集都互不相交，就是每条边恰好属于一个类。

为什么要拆成**不相交**的边集们呢。因为这样有独立性，舒服啊。答案显然是最终每个类的大小的 gcd（不属于任何简单环的边类除外，很好理解吧）。

两条边在同一个类中的充要条件显然是它们所在简单环集合相等。这玩意好像还有个学名叫切边等价。考虑把所有这样的切边等价类求出来，好像还挺可做的，毕竟虽然简单环个数是指数级的，但是我们只需要判断两条边所在简单环集合是否相等，不需要真的求出来简单环集合。

数据范围给的是平方的，正好够我们对每对边判断它们切边等价。怎么判断？边所在简单环，想到边双理论。一条边不在任何简单环上当且仅当它是割边。而如果不是割边，那么把它割掉，虽然图还连通，但是它所在的所有简单环都消失。如果此时我们再跑 tarjan 判另一条边是否割边，如果是割边，说明它所在的简单环，割掉的边都在。这说明一个的所在简单环集合包含于另一个。而如果反过来判一下，不就可以确定是否相等了吗，不就完事了吗！复杂度平方，跑 $m$ 遍 tarjan，对每对边记录包含性，最后再 dfs 或者并查集划分出切边等价类。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
const int N=2010,M=2010;
int n,m;
int a[M],b[M],t[N][N];
vector<int> nei[N];
bool to[N][N];
int dfn[N],low[N],nowdfn;
bool cut[M];
int ban;
void tar(int x,int fa=0){
	dfn[x]=low[x]=++nowdfn;
	for(int i=0;i<nei[x].size();i++){
		int y=nei[x][i];
		if(x==a[ban]&&y==b[ban]||x==b[ban]&&y==a[ban])continue;
		if(y==fa){fa=-1;continue;}
		if(!dfn[y]){
			tar(y,x),low[x]=min(low[x],low[y]);
			if(dfn[x]<low[y])cut[t[x][y]]=true;
		}
		else low[x]=min(low[x],dfn[y]);
	}
}
struct ufset{
	int fa[M];
	ufset(){memset(fa,0,sizeof(fa));}
	int root(int x){return fa[x]?fa[x]=root(fa[x]):x;}
	void mrg(int x,int y){
		x=root(x),y=root(y);
		if(x!=y)fa[x]=y;
	}
}ufs;
int gcd(int x,int y){return y?gcd(y,x%y):x;}
int cnt[M];
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		a[i]=x,b[i]=y;
		nei[x].pb(y),nei[y].pb(x);
		t[x][y]=t[y][x]=i;
	}
	for(int i=1;i<=m;i++){
		ban=i;
		memset(dfn,0,sizeof(dfn)),nowdfn=0;
		memset(cut,0,sizeof(cut));
		for(int j=1;j<=n;j++)if(!dfn[j])tar(j);
		for(int j=1;j<=m;j++)if(cut[j])to[i][j]=true;
	}
	for(int i=1;i<=m;i++)for(int j=1;j<=m;j++)if(to[i][j]&&to[j][i])ufs.mrg(i,j);
	ban=0;
	memset(dfn,0,sizeof(dfn)),nowdfn=0;
	memset(cut,0,sizeof(cut));
	for(int i=1;i<=n;i++)if(!dfn[i])tar(i);
	for(int i=1;i<=m;i++)cnt[ufs.root(i)]++;
	int ans=0;
	for(int i=1;i<=m;i++)if(!cut[i])ans=gcd(ans,cnt[i]);
	for(int i=1;i<=m;i++)if(ans%i==0)cout<<i<<" ";
	return 0;
}
```



---

## 作者：_Cheems (赞：0)

题意：给一张简单无向图，求有多少个 $k$，满足可以为边染上 $k$ 种颜色的一种，使得任意简单环每种颜色边的数量相同。$n,m\le 2\times 10^3$。

对于若干不相交简单环构成的复合环不用管，因为子环合法它也合法。

然后考虑两个相交的简单环 $A,B$，必然存在环 $A\oplus B$。拆为三部分 $A\cap B,A-A\cap B,B-A\cap B$，则任选其二都能构成一个简单环。猜测 $A,B,A\oplus B$ 合法当且仅当这三部分合法。充分性显然，必要性反证即可。

对于两个相交的“残缺”的链或环（即进行分解得来的部分），也能这样分解，证明考虑补上残缺的部分、对它们原先属于的环讨论即可。不断递归该过程，直到划分为若干不相交部分，显然 $k$ 合法当且仅当 $k$ 是每个独立边集大小的公约数。

不难发现，划分的结果和切边等价的等价类划分完全一致。注意丢掉割边（不出现在简单环上）。经典套路可以 $O(n+m)$，不过排序需要 $O(m\log m)$。
#### 代码
偷懒写了 $O(n^2)$。


```cpp
#include<bits/stdc++.h>
using namespace std;

#define ull unsigned long long
#define pir pair<int, int>
const int N = 2e3 + 5;
int n, m, u, v, ans, dfn[N], df;
ull w[N];
mt19937 rnd(time(0));
vector<int> s;
vector<pir> to[N];
pir fa[N];
 
inline void dfs(int u, int from){
	dfn[u] = ++df;
	for(auto _ : to[u]){
		int v = _.first, id = _.second;
		if(v == from) continue;
		if(!dfn[v]) fa[v] = {u, id}, dfs(v, u);
		else if(dfn[v] < dfn[u]){
			w[id] = rnd();
			int now = u;
			while(now ^ v){
				pir __ = fa[now];
				w[__.second] ^= w[id];
				now = __.first;
			}
		}
	}
}
signed main(){
	cin >> n >> m;
	for(int i = 1; i <= m; ++i) scanf("%d%d", &u, &v), to[u].push_back({v, i}), to[v].push_back({u, i});
	for(int i = 1; i <= n; ++i) if(!dfn[i]) dfs(i, 0);
	sort(w + 1, w + 1 + m);
	for(int i = 1, ct = 0; i <= m; ++i){
		++ct;
		if(i == m || w[i] != w[i + 1]){
			if(w[i] > 0) s.push_back(ct);
			ct = 0;
		}
	}
	for(int i = 1; i <= m; ++i){
		bool fl = true;
		for(auto j : s) fl &= (j % i == 0);
		if(fl) printf("%d ", i);
	}
	return 0;
}

```

---

