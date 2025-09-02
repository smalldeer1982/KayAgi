# Digital Village (Extreme Version)

## 题目描述

**这是问题的极端版本。在三个版本中，$n$ 和 $m$ 的约束条件不同。只有所有版本的问题都解决了，你才能进行 hack。**

Pak Chanek 正在为 Khuntien 村设置互联网连接。这个村庄可以表示为一个连通的简单图，其中有 $n$ 栋房屋和 $m$ 条互联网电缆，每条电缆连接房屋 $u_i$ 和房屋 $v_i$，并且具有延迟 $w_i$。

有 $p$ 栋房屋需要互联网。Pak Chanek 最多可以在 $k$ 栋房屋中安装服务器。需要互联网的房屋将连接到其中一个服务器。但是，由于每条电缆都有其延迟，对于需要互联网的房屋 $s_i$，其经历的延迟将是该房屋与其连接的服务器之间电缆的**最大**延迟。

对于每个 $k = 1,2,\ldots,n$，帮助 Pak Chanek 确定所有需要互联网的房屋所能达到的最小**总**延迟。

## 样例 #1

### 输入

```
2
9 8 5
2 5 6 8 9
1 2 1
1 3 2
3 4 10
4 5 3
4 6 5
1 7 10
7 8 4
7 9 2
3 3 2
3 1
1 2 1
2 3 3
1 3 2```

### 输出

```
34 19 9 4 0 0 0 0 0
2 0 0```

# 题解

## 作者：ChrysanthBlossom (赞：8)

no slope trick！

分享一个不用维护凸包 min+ 卷积的智慧做法。该做法来自于 CF 官解下边的一个[评论](https://codeforces.com/blog/entry/134873?#comment-1206685)，这里就当是一个翻译和解释了。

首先建出 Kruskal 重构树，两点间路径最长边的最小值显然等于 lca 对应的边的边权。于是问题转化为给定一棵树的若干叶子（我们称这些点为特殊点），要求再选择 $k$ 个叶子（可重），定义一个点是好的当且仅当它的子树里面有叶子是 $k$ 个中的一个，求每个特殊点的最近好祖先的权值的和。

接着到了最智慧的一步：**设 $f_u$ 表示 $u$ 对应的边权（若 $u$ 为叶子则认为其为 $0$），$g_u$ 表示 $u$ 子树内特殊点的数量，$p_u$ 表示 $u$ 的父亲（若没有则为 $0$，同时认为 $f_0=0$），$val_u=g_u \times (f_u-f_{p_u})$，那么对于一个选点的方案，其价值为所有子树内有点被选的点的 $val$ 的和！**

这个的证明是简单的。考虑将特殊点一个个加入。设此时加入的特殊点为 $x$，它的最近好祖先为 $y$，那么它一个产生的贡献自然是 $f_y$，并且这个同时可以拆成 $(f_y-f_{p_y})+(f_{p_y}-f_{p_{p_y}})+...$。把这每个式子算到对应的 $val$ 里面，会发现对于子树内有点被选的点 $u$，$f_u-f_{p_u}$ 正好被统计 $g_u$ 次；对于子树内没有点被选的点 $u$，它自然也不可能是一个点的好祖先，自己子树里自然也没有点是一个特殊点最近好祖先，因此它一次也不会被统计。（大概有点[这题](https://www.luogu.com.cn/problem/P4211)把 dep 拆开来的味道）

这样搞完就简单了，因为接下来直接做一个类似于长剖贪心的过程，每次选一个到根路径点权和最小的点，然后把中间所有点的点权抹掉，做 $n$ 次就是答案了。本题的数据范围允许你这么搞，但其实可以写得更简单。考虑做“短剖”（？），kruskal 的时候维护每个连通块里的到根点权和最小的叶子，合并的时候取两个连通块的更小的叶子，并将小的叶子向大的连条有向边，然后对小的的点权和进行修改。最后求答案的时候，先把整个图最小叶子放到一个小根堆里，然后循环取叶子，每次取完之后把它连着的点放到堆里。这样甚至都不用真正地把 Kruskal 重构树给建出来，常数也小多了。

[代码](https://codeforces.com/contest/2021/submission/285024181)

---

## 作者：Albert_van (赞：2)

[题](https://www.luogu.com.cn/problem/CF2021E3) [题](https://mirror.codeforces.com/contest/2021/problem/E3)。虽然已经有人在下面管这叫 KRT（Kruskal Reconstruction Tree）了，但感觉 Kruskal 重构树在国外普及度还是不高。首先把 KRT 建出来，问题：一棵 $2n-1$ 个结点的二叉树，每个非叶子结点有权值 $w(u)(w(u)\le w(\operatorname{fa}_u))$，给定叶子集合 $S$，对 $k\in[1,n]$ 回答：选出一个大小为 $k$ 的叶子集合 $T$，$\sum_{x\in S}\min_{y\in T}{w(\operatorname{lca}(x,y))}$ 的最小值。记 $c(u)$ 表示 $u$ 子树中 $S$ 集合内叶子个数，以下两种做法。

DP。令 $f_{u,i}$ 表示仅考虑 $u$ 子树，选出 $T$ 的大小为 $i$，答案最小值。转移：
$$
f_{u,i}=\min\{f_{L,i}+w(u)\times c(R),f_{R,i}+w(u)\times c(L),\min_{k\in[1,i)}\{f_{L,k}+f_{R,i-k}\}\}(i\in[1,c(u)])
$$
其中 $L,R$ 分别为 $u$ 的左右儿子。看到最后一项 $(\min,+)$ 卷积，直接思考凸性。从两个角度说明“$f_{u,i}$ 在 $u$ 固定时关于 $i$ 下凸”这个事情：

- 归纳。对于最后一项转移，两个下凸函数做闵可夫斯基和得到的仍然是下凸函数。对于前两项转移，感性理解，因为 $w(u)\le w(\operatorname{fa}_u),c(u)\le c(\operatorname{fa}_u)$，所以 $w(u)\times c(u)$ 在 $u$ 往根移动时单调不减。也就是说，对于 $i<j$，相较于 $f_{u,j}$，$f_{u,i}$ 在 $u$ 的子树中必然与更小的 $w(v)\times c(v)$ 取过 $\min$，前两项转移在 $f_{u,i}$ 下凸的前提下进一步缩小 $f_{u,i}-f_{u,j}$，不改变凸性。

- 观察。显然在选择 $i$ 个叶子后添加第 $i+1$ 个叶子带来的代价减量 $f_{u,i}-f_{u,i+1}$ 单调不增。

于是强制规定 $f_{u,0}=w(\operatorname{fa}_u)\times c(u)$，转移就只剩下了一个闵可夫斯基和。考虑拿它做 $(\min,+)$ 卷积的过程，每次选择 $f_{L,i}-f_{L,i+1}$ 与 $f_{R,i}-f_{R,i+1}$ 中较大者。那么对每个 $u$ 拿 `multiset` 维护所有的 $f_{u,i+1}-f_{u,i}$，树上启发式合并即可。

注意实现细节。因为每次都钦定 $f_{u,0}$，所以 $f_u$ 转移到 $f_{\operatorname{fa}(u)}$ 时直接让 $f_{u,0}\gets f_{u,0}+(w(\operatorname{fa}_u)-w(u))$。复杂度 $\mathcal O(n\log^2 n)$，[记录](https://mirror.codeforces.com/contest/2021/submission/285126676)。

---

贪心。考虑把 $w(\operatorname{lca})$ 下放到 $S$ 中各个叶子到 $\operatorname{lca}$ 链上的每条边算贡献。问题：选出一个大小为 $k$ 的 $T$，最小化：
$$
\sum_u c(u)(w(\operatorname{fa}_u)-w(u))[u\text{子树中没有叶子被选中}]
$$
也即最大化：
$$
\sum_u c(u)(w(\operatorname{fa}_u)-w(u))[u\text{子树中有至少一个叶子被选中}]
$$
令 $a_u=c(u)(w(\operatorname{fa}_u)-w(u))$，相当于要选出 $k$ 个叶子，最大化虚树点权和，这是经典贪心问题，每次选择最大权链即可。具体地，对每个点预处理出 $f_u$ 表示 $u$ 到所有叶子的链中，$\sum a$ 的最大值，$g_u$ 表示这条链是从哪个儿子转移过来的。维护按 $f$ 排序的堆，初始加入根，每次取出一个点沿着 $g$ 一直跳到叶子，把这条链旁边的点全部加入堆中即可，[记录](https://mirror.codeforces.com/contest/2021/submission/285131082)。

---

## 作者：strcmp (赞：2)

延迟只跟路径的最大值有关系，启发我们建立 kruskal 重构树。

最小生成树是最小瓶颈生成树，所以重构树有极好的性质。

对于重构树结点 $u$，其叶子（也就是原图结点）互相之间的路径边权最大值的最小值恰好就是 $u$ 的值。

于是就可以 dp 了。

设 $p_i$ 代表 $i$ 是否是需要联网的点（是那么就是 $1$ 否则就是 $0$），$s_i$ 为重构树结点 $i$ 的叶子结点树。$f_{u,\,i}$ 代表重构树结点 $u$ 的子树内建 $i$ 个服务器的最小总延迟。

设 $x,\,y$ 是重构树结点 $u$ 的两个儿子结点，$w$ 是重构树结点 $u$ 的点权。初值显然为 $f_{x,\,0} = p_x \times w,\,f_{y,\,0} = p_y \times w$。

转移是 $\min+$ 卷积：

$$
f_{u,\,i + j} \leftarrow \min(f_{u,\,i + j},\,f_{x,\,i} + f_{y,\,j}) \{ 0 \le i \le s_x \wedge 0 \le j \le s_y \}
$$

我们断言：$f_{u,\,x}$ 在 $u$ 固定的时候上凸。

感性理解：

1. 交换服务器安排的顺序不影响答案。

2. 每次增加一个服务器，能减少的贡献是越来越少的。

对于凸性的 $\text{min+}$ 卷积合并，可以使用闵可夫斯基和合并凸包。

具体的，直接对两边差分，我们相当于选出长度和为 $i$ 的两个前缀的最小值。差分是单调的所以归并一下取前 $i$ 大就是最优的。

合并使用 `multiset` 启发式合并，时间复杂度 $\Theta(n \log^2 n)$，可以通过。如果使用可并堆合并时间复杂度 $\Theta(n \log n)$。

实际上可以不显式的建 kruskal 重构树。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define pb push_back
using namespace std;
typedef long long int ll;
using ull = unsigned long long int;
using pil = pair<int, ll>;
using ms = multiset<ll>;
const int maxn = 2e5 + 10, mod = 1e9 + 7;
struct edge { int u, v, w; } e[maxn]; ms s[maxn];
int T, n, m, p, fa[maxn], c[maxn], siz[maxn]; ll ans[maxn];
int fd(int x) { return fa[x] == x ? x : fa[x] = fd(fa[x]); }
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &m, &p); int x;
		rep(i, 1, p) scanf("%d", &x), c[x] = 1;
		rep(i, 1, m) scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
		rep(i, 1, n) fa[i] = i, siz[i] = 1, s[i].clear(), s[i].insert(0), ans[i] = 0;
		sort(e + 1, e + m + 1, [&](edge p1, edge p2) {return p1.w < p2.w; });
		rep(i, 1, m) {
			int u = fd(e[i].u), v = fd(e[i].v);
			if (u != v) {
				if (siz[u] < siz[v]) swap(u, v);
				rep(j, 0, 1) {
					ll w = (ll)c[u] * e[i].w - ans[u], d = *s[u].begin(); 
					s[u].erase(s[u].begin()); ans[u] += w; s[u].insert(d - w); swap(u, v);
				}
				fa[v] = u, siz[u] += siz[v], c[u] += c[v], ans[u] += ans[v];
				for (auto x : s[v]) s[u].insert(x); s[v].clear();
			}
		}
		int rt = fd(1);
		for (auto x : s[rt]) ans[rt] += x, printf("%lld ", ans[rt]);
		puts(""); s[rt].clear(); rep(i, 1, n) c[i] = 0;
	}
	return 0;
}
```

---

## 作者：_ANIG_ (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF2021E3)

定义两个点的距离为这两个点路径上的边权的最大值的最小值。

给定若干个黑点，选 $k$ 个关键点使得每个黑点到最近的关键点的距离之和最小。

求出原图的 kruskal 重构树，于是两个点的距离转化为这两个点在树上的 lca 的权值。

树形 dp，设 $f_{x,k}$ 表示 $x$ 的子树内选了 $k$ 个关键点，$x$ 子树内的黑点的贡献之和的最小值。

转移的时候做一下背包。

然后处理一下某个儿子的子树不存在关键点的情况。

此时，新增的贡献就是这个儿子的子树的黑点数量乘上 $x$ 的权值。

这样做复杂度 $O(n^2)$。

注意到 $f_x$ 是凸的，所以可以闵可夫斯基和做卷积。

用可并堆或启发式合并维护，总复杂度 $O(n\log n)$ 或 $O(n\log^2 n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=4e5+5,inf=1e18;
struct edge{
	int x,y,z;
	friend bool operator<(edge a,edge b){
		return a.z<b.z;
	}
};
vector<edge>bn;
int t,n,m,fas[N],mk[N],k,idx,sz[N],bk[N],dy[N],val[N],son[N][2],siz[N];
priority_queue<int,vector<int>,greater<int> >f[N];
int fd(int x){
	if(x==fas[x])return x;
	return fas[x]=fd(fas[x]);
}
void dfs(int x){
	while(f[x].size())f[x].pop();
	if(x<=n){
	    f[x].push(0);
		if(bk[x])sz[x]=1;
		siz[x]=1;
		return;
	}
	dfs(son[x][0]);
	dfs(son[x][1]);
	siz[x]=siz[son[x][0]]+siz[son[x][1]];
	sz[x]=sz[son[x][0]]+sz[son[x][1]];
	int w1=f[son[x][0]].top(),w2=f[son[x][1]].top();
	f[son[x][0]].pop();
	f[son[x][0]].push(w1-(val[x]-val[son[x][0]])*sz[son[x][0]]);
	f[son[x][1]].pop();
	f[son[x][1]].push(w2-(val[x]-val[son[x][1]])*sz[son[x][1]]);
	swap(f[x],f[son[x][0]]);
	if(f[x].size()<f[son[x][1]].size())swap(f[x],f[son[x][1]]);
	while(f[son[x][1]].size())f[x].push(f[son[x][1]].top()),f[son[x][1]].pop();
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		for(int i=1;i<=n;i++)bk[i]=0;
		for(int i=1;i<=idx;i++)val[i]=0;
		bn.clear();
		for(int i=1;i<=idx;i++)siz[i]=sz[i]=0;
		cin>>n>>m>>k;
		for(int i=1;i<=k;i++){
			int x;
			cin>>x;
			bk[x]=1;
		}
		for(int i=1;i<=m;i++){
			int x,y,z;
			cin>>x>>y>>z;
			bn.push_back({x,y,z});
		}
		sort(bn.begin(),bn.end());
		for(int i=1;i<=n;i++)fas[i]=i,dy[i]=i;
		idx=n;
		for(auto [x,y,z]:bn){
			x=fd(x);y=fd(y);
			if(x==y)continue;
			idx++;
			son[idx][0]=dy[x];
			son[idx][1]=dy[y];
			val[idx]=z;
			fas[x]=y;
			dy[y]=idx;
		}
		int rt=dy[fd(1)];
		dfs(rt);
		int nw=val[rt]*sz[rt];
		for(int i=1;i<=n;i++){
			if(f[rt].size())nw+=f[rt].top(),f[rt].pop();
			cout<<nw<<" ";
		}
		cout<<"\n";
	}
}
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/CF2021E3)

**题目大意**

> 给定 $n$ 个点 $m$ 条带权边的无向连通图，给定 $p$ 个点 $x_1\sim x_p$，对于 $k=1\sim n$，算出选择 $k$ 个关键点 $w_1\sim w_k$ 后，$\sum_{i=1}^p\min_{j=1}^k\mathrm{dis}(x_i,w_j)$ 的最小值，其中 $\mathrm{dis}$ 定义为路径上最小的最大边权。
>
> 数据范围：$n,m\le 2\times 10^5$。

**思路分析**

两点之间的距离很显然用 Kruskal 重构树刻画，即为两点间 $\mathrm{LCA}$ 的权值。

那么一组点集 $w$ 的权值就是每个 $x_i$ 到 $w$ 构成的虚树的 $\mathrm{LCA}$ 权值之和。

把权值差分，把 $u$ 的权值变成根的权值减去 $1\to u$ 路径上的边权和。

那么某个节点 $u$ 对答案的贡献就是 $u$ 的边权乘上子树内 $x_i$ 个数，记为 $v_u$，当且仅当 $u$ 子树内有 $w$ 中的点时有效。

此时贡献关于每个节点 $u$ 独立，答案就是定值减去 $w$ 构成的虚树的 $v$ 之和。

那么我们就要对每个 $k$ 求出：选 $k$ 条到根的链，最大化链并上权值和，这是经典贪心结论，取出每条长链并排序即可。

时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=4e5+5;
int n,m,q,dsu[MAXN],val[MAXN],fa[MAXN],ls[MAXN],rs[MAXN],cov[MAXN];
int find(int x) { return x^dsu[x]?dsu[x]=find(dsu[x]):x; }
ll f[MAXN];
vector <ll> dis;
void dfs(int x) {
	if(!val[x]) return f[x]=0,void();
	dfs(ls[x]),dfs(rs[x]);
	ll c1=f[ls[x]]+1ll*(val[x]-val[ls[x]])*cov[ls[x]];
	ll c2=f[rs[x]]+1ll*(val[x]-val[rs[x]])*cov[rs[x]];
	dis.push_back(min(c1,c2)),f[x]=max(c1,c2);
}
void solve() {
	cin>>n>>m>>q;
	int _=n;
	for(int x;q--;) cin>>x,cov[x]=1;
	vector <array<int,3>> E(m);
	for(auto &e:E) cin>>e[1]>>e[2]>>e[0];
	for(int i=1;i<=n;++i) dsu[i]=i;
	sort(E.begin(),E.end());
	for(auto e:E) {
		int u=find(e[1]),v=find(e[2]),w=e[0];
		if(u==v) continue;
		val[++n]=w,dsu[n]=dsu[u]=dsu[v]=n;
		fa[u]=fa[v]=n,ls[n]=u,rs[n]=v;
		cov[n]=cov[u]+cov[v];
	}
	dis.clear(),dfs(n),dis.push_back(f[n]);
	ll tot=0;
	for(ll x:dis) tot+=x;
	sort(dis.begin(),dis.end(),greater<ll>());
	for(int i=0;i<_;++i) {
		if(i<(int)dis.size()) tot-=dis[i];
		cout<<tot<<" ";
	}
	cout<<"\n";
	for(int i=1;i<=n;++i) dsu[i]=val[i]=fa[i]=ls[i]=rs[i]=cov[i]=f[i]=0;
}
signed main() {
	ios::sync_with_stdio(false);
	int _; cin>>_;
	while(_--) solve();
	return 0;
}
```

---

## 作者：Erine (赞：1)

深刻的好题，可能是我不会闵可夫斯基和，总之学到了很多。

看到题面中所谓“边权最大值”的形式果断考虑 kruskal 重构树。把重构树建出来，接下来比较显然地考虑树形 dp。于是有 $f_{u,i}$ 表示 $u$ 子树里选了 $i$ 个点，答案的最小值。

考虑转移。你可以往左边放 $j$ 个，右边放 $i-j$ 个。如果 $j,i-j\ge 1$，直接从 $f_{ls,j}+f_{rs,i-j}$ 转移，因为你显然不会跨过当前这个点，这是不优的。否则如果 $j=0$，说明左边的点一定要跨过来去找右边的，这样比较优，造成的贡献是 $siz_{ls}w_u+f_{rs,i-j}$，$i-j=0$ 的情况同理。

好，我们发现这样是一个树上背包，这样做到了平方，可以通过 E1E2。观察到转移瓶颈是一个 $(\min, +)$ 卷积形式，而且所有的 $f_u$ 都是一个下凸壳。接下来讲述凸壳 $(\min, +)$ 卷积的做法：

考虑差分。原函数凸，差分数组单调。$(\min,+)$ 卷积等价于选出长度和为 $i$ 的前缀，使得前缀和最小。注意到这就是归并，进一步理解，实际上对凸壳做 $(\min,+)$ 卷积就是把差分数组合并在一起，排序，再前缀和。

那我们 $j=0$ 的特殊处理呢？那我们贡献扔到后面算，每次做完 $u$ 就把 $f_{u,0}$ 设成 $siz_uw_{fa_u}$，那再上面跑的时候就是标准的 $(\min,+)$ 卷积形式了。你可能会问，改变了 $f_{u,0}$ 会不会让它不凸了，就没办法归并。事实上，原来做闵的时候 $f_{u,0}$ 会等于 $f_{ls,0}+f_{rs,0}$ 也就是 $siz_uw_u$，那么变成 $siz_uw_{fa_u}$ 是不降的，因为 $w_u\le w_{fa_u}$，也就是说凸性质仍然不变。

于是我们使用 multiset 维护差分数组，启发式合并即可！！复杂度是 2log，可以可并堆做到 1log。

```cpp
void dfs(int u) {
	if (u <= (n + 1) / 2) {
		d[u].insert(w[pa[u]] * siz[u]);
		return;
	}
	int l = ch[u][0], r = ch[u][1];
	dfs(l), dfs(r);
	if (d[l].size() < d[r].size()) d[l].swap(d[r]);
	d[u].swap(d[l]);
	for (int i : d[r]) d[u].insert(i);
	multiset<int>().swap(d[r]);
	if (u != n) {
		auto x = prev(d[u].end());
		d[u].insert(*x + (w[pa[u]] - w[u]) * siz[u]);
		d[u].erase(x); 
	}
}
```

---

## 作者：int_R (赞：1)

[更好的阅读体验](https://www.cnblogs.com/int-R/p/18451392/CF2021E3)

考虑建出 kruskal 重构树，设 $f_{i,j}$ 为 $i$ 子树中选了 $j$ 个点的答案最小值。记 $cnt_x$ 为 $x$ 子树中有多少个关键点，$w_x$ 为 kruskal 重构树上的权值。

转移时合并两个子树 $f_{x,i}=\min f{u,j}+f{v_{i-j}}$，还有一种转移是 $f_{x,i}=f_{v,i}+cnt_{u}\times w_x$，意义是所有左子树中的点都要跑到右子树中去，经过的最大的边权就是 $w_x$。另一侧同理。

所以实际上我们每次转移后 $f_{x,0}\gets cnt_x\times w_{fa_x}$，然后就是 $(\min,+)$ 卷积的形式，显然有凸性，可以闵可夫斯基和优化。

我们考虑记录 $f_{x,i}-f_{x,i+1}(i\in[0,siz_x-1])$，这个单调递减。每次手动给 $f_{x,0}$ 赋值时相当于将最大值拿出来加上 $cnt_x\times (w_{fa_x}-w_x)$，因为修改前的 $f_{x,0}=f_{u,0}+f_{v,0}=cnt_x\times w_x$，所以需要取出来最大值。于是 set 启发式合并即可，时间复杂度 $O(n\log^2 n)$。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#define ll long long
using namespace std;
const int MAXN=4e5+10;
int T,n,m,p,s[MAXN],cnt[MAXN],siz[MAXN],fa[MAXN],w[MAXN];
int u[MAXN],v[MAXN],R[MAXN];ll ans[MAXN];multiset <ll> f[MAXN];
struct node{int x,y,w;}e[MAXN];
inline bool cmp(node x,node y){return x.w<y.w;}
inline int find(int x)
    {return fa[x]==x?x:fa[x]=find(fa[x]);}
void dfs(int x,int fa=0)
{
    if(!u[x]&&!v[x])
        {f[R[x]=x].insert(cnt[x]*w[fa]),siz[x]=1;return ;}
    dfs(u[x],x),dfs(v[x],x);
    cnt[x]=cnt[u[x]]+cnt[v[x]],siz[x]=siz[u[x]]+siz[v[x]];
    if(siz[u[x]]>siz[v[x]]) swap(u[x],v[x]);
    R[x]=R[v[x]];int p=R[u[x]];
    for(auto it=f[p].begin();it!=f[p].end();++it)
        f[R[x]].insert(*it);
    f[p].clear();auto it=f[R[x]].end();--it;
    ll W=*it+1ll*cnt[x]*(w[fa]-w[x]);
    f[R[x]].erase(it);if(fa) f[R[x]].insert(W);
}
inline void work()
{
    cin>>n>>m>>p;
    for(int i=1;i<=(n<<1);++i)
        fa[i]=i,u[i]=v[i]=cnt[i]=0;
    for(int i=1;i<=p;++i)
        cin>>s[i],cnt[s[i]]=1;
    for(int i=1;i<=m;++i)
        cin>>e[i].x>>e[i].y>>e[i].w;
    sort(e+1,e+1+m,cmp);int tot=n;
    for(int i=1;i<=m;++i)
    {
        if(find(e[i].x)==find(e[i].y)) continue;
        int fax=find(e[i].x),fay=find(e[i].y);
        w[++tot]=e[i].w,fa[u[tot]=fax]=fa[v[tot]=fay]=tot;
    }
    ans[n]=0;dfs(tot);auto it=f[R[tot]].begin();
    for(int i=n-1;i;--i) ans[i]=ans[i+1]+*it,++it;
    for(int i=1;i<=n;++i) cout<<ans[i]<<' ';
    cout<<'\n';f[R[tot]].clear();return ;
}
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
    cin>>T;while(T--) work();return 0;
}
```

---

## 作者：lfxxx (赞：0)

首先建出 kruskal 重构树。

房屋到一个服务器的代价就是两点在重构树上的 LCA 所代表的边的边权。

然后我们观察一下，对于一个子树而言，假若子树中存在至少一个服务器，那么子树内的所有点与这个服务器匹配，代价为子树根的权值，是优于与子树外任意服务器匹配的，因为重构树上一个点的权值小于等于其所有祖先的权值。

因此一个子树对子树外而言只有两种状态，子树内存在至少一台服务器使得子树内所有需要联网的房屋全部满足要求，或者子树内一台服务器都不存在。

因此设计状态 $f_{u,i}$ 表示子树 $u$ 内有 $i$ 台服务器时子树 $u$ 内需要联网的房屋的最小花费之和，再令 $sz_u$ 表示 $u$ 子树内需要联网的房屋数量，有 $f_{u,i} = \min(\min(f_{ls,i} + sz_{rs} \times w_u,f_{rs,i} + sz_{ls} \times w_u),\min_{1 \leq j < i}(f_{ls,j} + f_{rs,i-j}))$。

这个形式有点丑，但是不妨令 $f_{u,0} = sz_u \times w_{fa}$，那么你发现 $f_{u,i}$ 就是由 $f_{ls,i}$ 与 $f_{rs,i}$ 先做闵可夫斯基和再将 $f_{u,0}$ 增加一个非负数得到。

dp 的边界条件是 $f_{u,0} = sz_u \times w_{fa},f_{u,1} = 0$，此时 $f_{u,i}$ 是凸的，因此在经过上述合并操作后依然是凸的，所以直接用可并堆维护差分数组即可做到 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5+114;
int ls[maxn<<1],rs[maxn<<1];
int w[maxn<<1];
int fa[maxn<<1];
int found(int u){
    return fa[u]=(fa[u]==u?u:found(fa[u]));
}
int n,m,p,tot;
pair<int,pair<int,int> > e[maxn];
const int inf = 1e9+114;
int root[maxn<<1];
int g[maxn<<1];
struct node{
    int v,ls,rs,dist;
    node(){
        v=ls=rs=dist=0;
    }
}tr[maxn];//大根堆
int cnt;
void pushup(int cur){
    if(tr[tr[cur].ls].dist<tr[tr[cur].rs].dist) swap(tr[cur].ls,tr[cur].rs);
    tr[cur].dist=tr[tr[cur].rs].dist+1;
}
int merge(int a,int b){
    if(a==0||b==0) return a+b;
    if(tr[a].v>tr[b].v){
        tr[a].rs=merge(tr[a].rs,b);
        pushup(a);
        return a;
    }
    tr[b].rs=merge(tr[b].rs,a);
    pushup(b);
    return b;
}
int sz[maxn<<1];
void dp(int u,int fa){
    if(u<=n){
        g[u]=sz[u]*w[fa];
        cnt++;
        tr[cnt].v=g[u];
        root[u]=cnt;
        return ;
    }
    dp(ls[u],u),dp(rs[u],u);
    root[u]=merge(root[ls[u]],root[rs[u]]);
    g[u]=g[ls[u]]+g[rs[u]];
    sz[u]=sz[ls[u]]+sz[rs[u]];
    tr[root[u]].v+=sz[u]*w[fa]-g[u];
    g[u]=sz[u]*w[fa];
    return ;
}
void work(){
    cin>>n>>m>>p;
    tot=n;
    for(int i=1;i<=p;i++){
        int x;
        cin>>x;
        sz[x]=1;
    }
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=m;i++) cin>>e[i].second.first>>e[i].second.second>>e[i].first;
    sort(e+1,e+m+1);
    for(int i=1;i<=m;i++){
        int u=found(e[i].second.first),v=found(e[i].second.second);
        if(u!=v){
            tot++;
            ls[tot]=u,rs[tot]=v;
            fa[tot]=fa[u]=fa[v]=tot;
            w[tot]=e[i].first;
        }
    }
    w[0]=inf;
    dp(tot,0);
    for(int i=1;i<=n;i++){
        g[tot]-=tr[root[tot]].v;
        root[tot]=merge(tr[root[tot]].ls,tr[root[tot]].rs);
        cout<<g[tot]<<' ';
    }
    cout<<'\n';
    for(int i=1;i<=cnt;i++) tr[i]=node();
    for(int i=1;i<=tot;i++) sz[i]=g[i]=root[i]=ls[i]=rs[i]=w[i]=fa[i]=0;
    cnt=tot=0;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}
```

---

## 作者：Petit_Souris (赞：0)

首先肯定要建出 Kruskal 重构树，现在两个点之间的距离就是他们在重构树上的 LCA 的点权。

考虑树形 dp，把距离的贡献在对应的 LCA 处结算。设 $f_{u,i}$ 表示 $u$ 子树内放了 $i$ 个服务器的最小代价，那么转移就是枚举两边分别放了多少，做一个 $(\min,+)$ 卷积。如果有一边没有服务器，那么子树里的点都得走到目前的点，会加上一个 $w_u\times sz_{son}$ 的贡献。

根据树形背包复杂度分析得到 $\mathcal O(n^2)$ 的结果，可以通过 E1 E2。考虑优化，很容易猜测到这个东西是凸的，所以想到维护 $f$ 的差分数组，那么 $(\min,+)$ 卷积就是对两个差分数组的归并。用堆维护即可，如果用一种你喜欢的可并堆来做，是 $\mathcal O(n\log n)$ 的，如果直接启发式合并是 $\mathcal O(n\log ^2n)$ 的。

不过既然是凸的，应该也可以直接根据贡献从大到小贪心选？感觉是有道理的啊，不过我没写过。


```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=2e5+9,INF=1e18;
ll T,n,m,P,a[N],w[N<<1],sz[N<<1],tot,ans[N];
ll fa[N<<1],Fa[N<<1],ch[N<<1][2],dt[N];
struct Edg{
    ll u,v,w;
}e[N];
priority_queue<ll>dp[N<<1];
void dfs(ll x){
    if(x<=n){
        if(sz[x])dp[x].push(w[Fa[x]]*sz[x]);
        return ;
    }
    dfs(ch[x][0]),dfs(ch[x][1]);
    sz[x]=sz[ch[x][0]]+sz[ch[x][1]];
    if(sz[ch[x][0]]>sz[ch[x][1]])swap(ch[x][0],ch[x][1]);
    while(!dp[ch[x][0]].empty()){
        ll v=dp[ch[x][0]].top();
        dp[ch[x][0]].pop();
        dp[ch[x][1]].push(v);
    }
    swap(dp[x],dp[ch[x][1]]);
    priority_queue<ll>().swap(dp[ch[x][0]]);
    priority_queue<ll>().swap(dp[ch[x][1]]);
    if(!dp[x].empty()&&x!=tot){
        ll dt=(w[Fa[x]]-w[x])*sz[x];
        ll v=dp[x].top();dp[x].pop();
        dp[x].push(v+dt);
    }
}
ll find(ll x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}
void solve(){
    n=read(),m=read(),P=read();
    rep(i,0,n*2+1)priority_queue<ll>().swap(dp[i]);
    rep(i,0,n*2+1)sz[i]=ch[i][0]=ch[i][1]=w[i]=0;
    rep(i,1,P)a[i]=read(),sz[a[i]]=1;
    rep(i,1,m)e[i].u=read(),e[i].v=read(),e[i].w=read();
    sort(e+1,e+m+1,[&](Edg a,Edg b){
        return a.w<b.w;
    });
    iota(fa+1,fa+n+1,1ll);
    tot=n;
    rep(i,1,m){
        ll u=find(e[i].u),v=find(e[i].v);
        if(u==v)continue;
        tot++;
        fa[tot]=fa[u]=fa[v]=tot,w[tot]=e[i].w;
        Fa[u]=Fa[v]=tot;
        ch[tot][0]=u,ch[tot][1]=v;
    }
    dfs(tot);
    while(dp[tot].size()<n)dp[tot].push(0);
    dp[tot].pop();
    rep(i,1,n-1)dt[i]=dp[tot].top(),dp[tot].pop();
    ans[n]=0;
    per(i,n-1,1)ans[i]=ans[i+1]+dt[i];
    rep(i,1,n)write(ans[i]),putchar(' ');
    putchar('\n');
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    T=read();
    while(T--)solve();
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：wrkwrkwrk (赞：0)

首先，我们看一下有效的边是什么：应当是最小生成树的边。
> 考虑每个服务器和其控制的房屋，则选择最小生成树的边不会使得答案更劣。

显然最小生成树是树，考虑形成最小生成树的过程，当存在一条新的边树边时候，考虑生成一个新点代表这个边来表示合并过程，显然生成的树是二叉树。

![](https://cdn.luogu.com.cn/upload/image_hosting/nkcizo0x.png)

考虑了所有的边后，会得到如下的树：
![](https://cdn.luogu.com.cn/upload/image_hosting/i9vkbz38.png)

现在选 $k$ 服务器相当于选择 $k$ 条自根到叶子的链，使得每个叶节点到链上点的“深度”和最小。（深度为原来边权，特别的，叶子为 $0$）。

考虑 $dp$，定义 $dp_{i,j}$ 表示到第 $i$ 个点为止，选 $j$ 个儿子的最小答案。

若不选儿子，则其有深度差和叶子个数乘积的权值差。

状态转移方程为：
$$dp_{i,j}=\min _{a+b=j}dp_{l,a}+[a=0]((dep_i-dep_l)\times size_l))\\+dp_{r,b}+[b=0]((dep_i-dep_r)\times size_r)$$

直接暴力转移即可通过 E1，根据叶子个数转移即可通过 E2，注意到这个 $\min +$ 卷积的形式，转移应当满足凸性，根据闵可夫斯基和的选择最小的连续差分，用 set 处理差分，转移时修改和启发式合并，即可通过 E3。

三个做法的时间复杂度分别为 $O(n^3),O(n^2),O(n \log^2 n)$。

使用可并堆可以达到 $O(n \log n)$。

以下为 E3 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
bool st;
namespace _wrk{;
int s[1000006];
int f[1000006];
int siz[1000006];
int fin(int x){
	return f[x]==x?x:f[x]=fin(f[x]);
}
vector<int>g[1000006];
int dc[1000006];
int id[1000006];
int sic[1000006];
int n,m,p;
multiset<int>dp[1000006];
int dp0[1000006];
int res[1000006];
int dep[1000006];
void dfs(int now){
	if(now<=n){
		sic[now]=1;
		dp[now]={0};
		dp0[now]=0;
		return;
	}
	sic[now]=0;
	for(auto x:g[now]){
		dfs(x);
		sic[now]+=sic[x];
	} 
	dp[now].clear();
	int l=g[now][0],r=g[now][1];
	dp0[l]+=(dep[now]-dep[l])*sic[l];
	dp0[r]+=(dep[now]-dep[r])*sic[r];
	auto c=*dp[l].begin();dp[l].erase(dp[l].begin());dp[l].insert(c-(dep[now]-dep[l])*sic[l]);
	c=*dp[r].begin();dp[r].erase(dp[r].begin());dp[r].insert(c-(dep[now]-dep[r])*sic[r]);
	dp0[now]=dp0[l]+dp0[r];
	if(dp[l].size()<dp[r].size()){
		dp[now].swap(dp[r]);
		for(auto p:dp[l])dp[now].insert(p);
	}else{
		dp[now].swap(dp[l]);
		for(auto p:dp[r])dp[now].insert(p);
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		cin>>n>>m>>p;
		for(int i=1;i<=p;i++)cin>>s[i];
		vector<pair<int,pair<int,int>>>ed;
		for(int i=1;i<=m;i++){
			int a,b,c;
			cin>>a>>b>>c;
			ed.push_back({c,{a,b}});
		}
		for(int i=1;i<=n;i++)f[i]=i,siz[i]=res[i]=0;
		for(int i=1;i<=p;i++){
			siz[s[i]]++;
		}
//		for(int i=p;i<=n;i++)ans[i]=0;
		for(int i=1;i<=2*n;i++)dc[i]=0,id[i]=i,g[i].clear(),dep[i]=0,dp0[i]=0;
		int head=n+1;
		sort(ed.begin(),ed.end());
		for(auto y:ed){
			int u=y.second.first,v=y.second.second;
			if(fin(u)!=fin(v)){            
				if(!siz[fin(u)])swap(u,v);
				if(siz[fin(u)]&&siz[fin(v)]){
					
					res[fin(u)]=min(res[fin(u)]+y.first*siz[fin(v)],res[fin(v)]+y.first*siz[fin(u)]);
					g[head].push_back(id[fin(u)]);
					g[head].push_back(id[fin(v)]);
					dep[head]=y.first;
					id[fin(u)]=head;
					dc[head]=res[fin(u)];
					head++;
				}
				siz[fin(u)]+=siz[fin(v)];
				f[fin(v)]=fin(u);
			} 
		}
		dfs(head-1);
		vector<int>ans(n+1);
		ans[0]=dp0[head-1];
		int nc=1;
		for(auto x:dp[head-1]){
			ans[nc]=ans[nc-1]+x;
			nc++; 
		}
		for(int i=1;i<=n;i++)cout<<ans[i]<<' ';
		cout<<'\n';
	}
	return 0;
}
}
bool en;
signed main(){
	   return _wrk::main();
}
```

---

