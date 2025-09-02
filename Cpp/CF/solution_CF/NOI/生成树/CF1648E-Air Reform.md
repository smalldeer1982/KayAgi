# Air Reform

## 题目背景

可以在 [P13548](https://www.luogu.com.cn/problem/P13548) 评测本题。

## 题目描述

伯兰德是一个拥有发达航空网络的大国。全国共有 $n$ 个城市，这些城市一直由 Berlaflot 航空公司运营。该公司在 $m$ 对城市间运营双向航班，第 $i$ 条航线连接城市 $a_i$ 和 $b_i$，票价为 $c_i$，双向价格相同。

已知通过 Berlaflot 的航班，可以从任意城市到达任意其他城市（可能需要中转）。对于一条由多段航班组成的路径，其总费用等于其中最贵一段的费用。更正式地说，从城市 $t_1$ 到 $t_k$（中转 $k-2$ 次），路径费用为 $t_1$ 到 $t_2$，$t_2$ 到 $t_3$，……，$t_{k-1}$ 到 $t_k$ 这些航班中费用的最大值。当然，所有航段都必须由 Berlaflot 执飞。

最近，S8 Airlines 新进入了伯兰德市场。S8 Airlines 在所有未被 Berlaflot 连接的城市对之间开通了双向航班。也就是说，任意一对城市之间，要么有 Berlaflot 的航班，要么有 S8 Airlines 的航班。

S8 Airlines 的航班费用如下：对于通过 S8 Airlines 连接的城市 $x$ 和 $y$，其票价等于 Berlaflot 网络下 $x$ 和 $y$ 之间所有路径中费用最小的那一条（即路径上的最大航段费用最小）。

已知通过 S8 Airlines 的航班，也可以在所有城市之间互达，且路径费用定义同上，也是路径上最大航段费用。

由于 S8 Airlines 的竞争，Berlaflot 决定进行航空改革，调整自家航班票价：对于 Berlaflot 的第 $i$ 条航班（连接 $a_i$ 和 $b_i$），新票价应等于 S8 Airlines 网络下 $a_i$ 和 $b_i$ 之间的最小路径费用。请帮 Berlaflot 计算每条航班改革后的新票价。


## 说明/提示

### 说明

在第一个测试样例中，S8 Airlines 会在以下城市对之间开通航班：（1,3）、（1,4）、（2,4）。

城市 1 和 3 之间的 S8 航班费用为 2，因为 Berlaflot 网络下最小路径费用为 2（1-2 票价 1，2-3 票价 2，最大为 2）。

城市 1 和 4 之间的 S8 航班费用为 3，因为 Berlaflot 网络下最小路径费用为 3（1-2 票价 1，2-3 票价 2，3-4 票价 3，最大为 3）。

城市 2 和 4 之间的 S8 航班费用为 3，因为 Berlaflot 网络下最小路径费用为 3（2-3 票价 2，3-4 票价 3，最大为 3）。

航空改革后，Berlaflot 的航线 1-2 的票价变为 3，因为 S8 Airlines 网络下 1 和 2 之间最小路径费用为 3（1-4 票价 3，2-4 票价 3，最大为 3）。

航线 2-3 的票价也变为 3，因为 S8 网络下 2 和 3 的最小路径费用为 3（2-4 票价 3，1-4 票价 3，1-3 票价 2，最大为 3）。

航线 3-4 的票价也变为 3，因为 S8 网络下 3 和 4 的最小路径费用为 3（1-3 票价 2，1-4 票价 3，最大为 3）。

第二个测试样例中，S8 Airlines 会在城市对（1,4）、（2,3）、（2,5）、（3,4）、（3,5）之间开通航班，票价分别为 1、1、2、1、2。


## 样例 #1

### 输入

```
3
4 3
1 2 1
2 3 2
4 3 3
5 5
1 2 1
1 3 1
2 4 1
4 5 2
5 1 3
6 6
1 2 3
2 3 1
3 6 5
3 4 2
4 5 4
2 4 2```

### 输出

```
3 3 3 
1 1 1 2 2 
4 4 5 3 4 4```

# 题解

## 作者：Alex_Wei (赞：10)

> F. [CF1648E Air Reform](https://www.luogu.com.cn/problem/CF1648E) *3200

我今天就是要用 kruskal 过了这道题！

建出原图 $G$ 的最小生成树 $T$，则 $G$ 上任意两点 $u, v$ 的最短路即 $T$ 上 $u, v$ 之间边权最大值。

更进一步地，建出原图 $G$ 的 kruskal 重构树 $T$，对于 $T$ 上的每个非叶子节点 $u$，设其权值为 $w$，那么对于 $G$ 的补图 $G'$，所有 $u$ 的左子树的叶子节点与所有右子树的叶子节点之间有权值为 $w$ 的边（前提是连边的点对在原图上无连边）。

我们希望求出 $G'$ 的最小生成树 $T'$。但是 $G'$ 上的边太多，我们无法使用朴素的最小生成树算法，必须进行优化。

考虑 kruskal 求最小生成树的过程，每次找到权值最小的边，若两端在最小生成树上不连通，则加入最小生成树。因此，我们按权值从小到大依次考虑 $T$ 上每个非叶子节点带来的影响。

权值从小到大在重构树上对应着深度从深到浅，所以我们先递归考虑当前节点的左右儿子，再考虑当前节点。

设当前节点为 $u$，其左子树所有叶子节点为 $L$，右子树所有叶子节点为 $R$。在递归处理左右子树时，$L$ 和 $R$ 在 $G'$ 上已经形成了若干连通块。设 $L$ 形成的连通块集合为 $S_L = \{GL_i\}$，$R$ 形成的连通块集合为 $S_R = \{GR_i\}$，每个 $GL_i$ 均由若干 $L$ 当中的节点组成，$GR_i$ 同理。

考虑合并 $S_L$ 和 $S_R$。

枚举 $S_L$ 内所有连通块 $GL_i$，然后枚举 $GL_i$ 内所有节点 $x$，然后枚举 $S_R$ 内所有连通块 $GR_j$，然后枚举 $GR_j$ 内所有节点 $y$，如果 $x, y$ 之间没有连边，那么它们在补图上直接相连，就把 $GR_j$ 从 $S_R$ 中删去，并合并到 $GL_i$ 当中。

注意，由于可能出现 $GL_i$ 和 $GL_k$ 同时与 $GR_j$ 合并使得它们连通的情况，所以对于每个 $GL_i$ 处理完要丢进 $S_R$ 里面去。

看起来很暴力对吧。只要你加上启发式合并，它的复杂度就变成了惊人的 $\log ^ 2n$。

我们来证明这一点。考虑枚举 $x, y$ 的复杂度。

因为一旦 $x, y$ 之间在 $G$ 上没有直接连边，那么必然有两个连通块被合并。据此可证明，使得 $x, y$ 没有直接连边的次数为 $\mathcal{O}(n)$。

合并连通块的复杂度由启发式合并保证，用 `set` 维护每个连通块，这部分时间复杂度 $\mathcal{O}(n\log ^ 2 n)$。

所以只需保证直接连边的 $x, y$ 不会被枚举太多次即可。直接连边的 $x, y$ 每次被枚举一定形如，在此之前 $x$ 作为 $GL_i$ 的某个点在 $GL_i$ 被丢进 $S_R$ 时合并进 $R$，使得 $y$ 作为接下来被枚举到的 $GL_i$ 的某个点，且 $x$ 作为 $GR_i$ 的某个点（其实还有一种情况是在 LCA 处，一个作为 $GL_i$ 里面的点，另一个作为 $GR_j$ 里面的点被枚举到，不过这部分由于原图每条边只会贡献一次，所以枚举次数为 $\mathcal{O}(m)$）。由于我们对 $|L|$ 和 $|R|$ 的合并也是启发式的，所以一个点作为 $L$ 中的某个点被合并进 $R$ 的次数不超过 $\log n$，故使得 $x, y$ 之间直接连边的次数为 $\mathcal{O}(m\log n)$。

因为每次查询 $x, y$ 之间是否有连边的时间复杂度为 $\mathcal{O}(\log n)$，所以总时间复杂度为 $\mathcal{O}(m\log ^ 2 n)$。

合并两个连通块时需要在补图 $G'$ 的最小生成树 $T'$ 上的连通块代表元之间连权值为 $w(u)$ 的边。求出 $T'$ 后回答询问就是很简单的询问树上两点之间边权最大值，树上倍增做即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int K = 18;
const int N = 4e5 + 5;
int n, m, dn;
int val[N], ans[N], sz[N];
int node, fa[N], ls[N], rs[N];
int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
struct edge {
	int u, v, w, id;
	bool operator < (const edge &r) const {return w < r.w;}
} e[N];
struct Tree {
	int dep[N], mx[K][N], fa[K][N];
	vector <pair <int, int>> e[N];
	void init() {for(int i = 1; i <= n; i++) e[i].clear();}
	void add(int u, int v, int w) {
		// cerr << "add " << u << " " << v << " " << w << endl;
		e[u].push_back(make_pair(v, w)), e[v].push_back(make_pair(u, w));
	}
	void dfs(int id, int f) {
		// cerr << "dfs " << id << " " << f << endl;
		fa[0][id] = f, dep[id] = dep[f] + 1;
		for(auto it : e[id]) {
			int to = it.first;
			if(to == f) continue;
			mx[0][to] = it.second, dfs(to, id);
			// cerr << "mx " << to << " " << mx[0][to] << endl;
		}
	}
	int dist(int u, int v) {
		int ans = 0;
		if(dep[u] < dep[v]) swap(u, v);
		for(int i = 17; ~i; i--) if(dep[fa[i][u]] >= dep[v]) ans = max(ans, mx[i][u]), u = fa[i][u];
		if(u == v) return ans;
		for(int i = 17; ~i; i--)
			if(fa[i][u] != fa[i][v])
				ans = max(ans, max(mx[i][u], mx[i][v])), u = fa[i][u], v = fa[i][v];
		return max(ans, max(mx[0][u], mx[0][v]));
	}
	void build() {
		dfs(1, 0);
		for(int i = 1; i <= 17; i++)
			for(int j = 1; j <= n; j++) {
				fa[i][j] = fa[i - 1][fa[i - 1][j]];
				mx[i][j] = max(mx[i - 1][j], mx[i - 1][fa[i - 1][j]]);
			}
	}
} tr;
set <int> g[N], s[N], ind[N];
void merge(set <int> &x, set <int> &y, int w) {
	// cerr << "add edge " << *x.begin() << " " << *y.begin() << " " << w << endl;
	tr.add(*x.begin(), *y.begin(), w);
	if(x.size() < y.size()) swap(x, y);
	for(int it : y) x.insert(it);
	y.clear();
}
void calc(int id) {
	if(id <= n) return s[id].insert(id), sz[id] = 1, void();
	int u = ls[id], v = rs[id];
	calc(u), calc(v), sz[id] = sz[u] + sz[v];
	if(sz[u] > sz[v]) swap(u, v);
	for(int it : s[u]) {
		set <int> tmp = ind[it];
		for(int x : tmp) {
			set <int> tmp2 = s[v];
			for(int y : tmp2) {
				bool found = 0;
				for(int z : ind[y]) if(g[x].find(z) == g[x].end()) {found = 1; break;}
				if(found) merge(ind[it], ind[y], val[id]), s[v].erase(y);
			}
		}
		s[v].insert(it);
	}
	swap(s[id], s[v]);
}
void solve() {
	cin >> n >> m;
	dn = 0, node = n, tr.init(); // init
	// for(int i = 1; i <= n; i++) assert(g[i].empty());
	for(int i = 1; i <= n; i++) ind[i].clear(), ind[i].insert(i);
	for(int i = 1; i <= n << 1; i++) fa[i] = i, g[i].clear(), s[i].clear();
	for(int i = 1; i <= m; i++) scanf("%d %d %d", &e[i].u, &e[i].v, &e[i].w), e[i].id = i;
	sort(e + 1, e + m + 1);
	for(int i = 1; i <= m; i++) {
		int u = find(e[i].u), v = find(e[i].v);
		if(u == v) continue;
		val[++node] = e[i].w, fa[u] = fa[v] = node;
		ls[node] = u, rs[node] = v;
		// cerr << node << " " << u << " " << v << endl;
	}
	for(int i = 1; i <= m; i++) g[e[i].u].insert(e[i].v), g[e[i].v].insert(e[i].u);
	calc(node);
	tr.build(); // ADD THIS LINE =.=
	for(int i = 1; i <= m; i++) ans[e[i].id] = tr.dist(e[i].u, e[i].v);
	for(int i = 1; i <= m; i++) printf("%d ", ans[i]);
	cout << endl;
}
int main() {
	// freopen("1.in", "r", stdin);
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}

/*
2022/5/2
start thinking at 9:35

首先建出原图的 MST.
考虑添加一条边连通点集 S, T 的时候, S 和 T 之间所有不出现在原图上的点对连权值为 v 的边.
再求出补图 MST.
树上倍增即为所求.

问题出在第 2, 3 步.
补图的边是相当多的, 考虑优化这两步.
考虑启发式合并.
将补图上连通的点合并成一个 set.
用 set 存所有出边, 然后还要给所有点重编号, 保证任意时刻 set 里面的点都是区间.
kruskal 重构树.

有点难写.

start coding at 10:20
finish debugging at 11:59
*/
```

---

## 作者：xtx1092515503 (赞：8)

[portal](https://www.luogu.com.cn/problem/CF1648E)

首先原图中最短路是“最大值最小”的描述，那么自然想到 Kruskal 重构树。则两点间的最短路为其在 Kruskal 重构树上的 LCA 的权值。

那么考虑补图。显然我们也要把补图的 Kruskal 重构树建出来。

但是我们显然无法在补图上执行 Kruskal 算法——因为边数是 $O(n^2)$ 的。

怎么办呢？我们发现，可以先求出补图的 **最小生成树**，然后根据最小生成树可以简单求出 Kruskal 重构树。

但是最小生成树应该怎么求呢？

答案不是 Prim 或 Kruskal 这两种常见的算法，而是 ~~未曾设想的道路~~ Boruvka 算法。

> Boruvka 算法是维护若干连通块的过程。
>
> 其会执行若干轮。在每一轮中，从每个连通块出发找到其与任一其它连通块间 **边权最小的边**。然后，连接这所有的边（只要其两个端点不位于同一连通块中）。
>
> 重复执行，直到仅剩一个连通块。
>
> - 正确性证明：每个连通块要与其它连通块连通，显然经由该最小边权边是最优的。
>
>     假如出现了环，则显然环上每条边的边权都相等且最小（不然就不会成环）。那么就扔掉一条边，用剩下的边连成一个大连通块即可。
>
> - 复杂度证明：每轮中，每个连通块必然与另一个连通块合并。故每轮会让连通块数量减半，至多执行 $\log n$ 轮。

可以发现，Boruvka 算法并不要求求出每条边的边权，只要你能够对于每个点求出其与不在同一个连通块中的点间的最小边权即可。

考虑本题。我们考虑二分一个点 $x$ 在 Kruskal 重构树上的祖先，并且判定这个祖先是否可以作为从这个点出发的连边。

考虑判定条件。

- 这个祖先的子树中存在与 $x$ 不在同一个连通块中的点。
- 上述点中存在 **在原图中与 $x$ 无边直接相连** 的点。

其中第二条限制较易遗忘，这是因为 **补图** 中不存在原图中有的边。

那么考虑如何判定。我们事实上可以不使用二分，而是找到在 Kruskal 重构树的 dfs 序上，在 $x$ 之前/之后且满足上述条件的首个点，然后找到二者 LCA 的较深者，即为我们需要的点。

考虑对之前之后各维护一个指针。显然随着 Boruvka 算法的执行，之前的指针会不断前移，之后的指针会不断后移。

那么我们用数据结构维护每个连通块，然后每次在数据结构中找到指针之后下一个不在数据结构中的点，假如这个点对应的边出现在原图中就再次寻找即可。可以发现失配的总次数是 $O(m)$ 级别的。

考虑用什么数据结构维护。事实上，只需每轮都重构连通块即可——因为一共仅执行 $O(\log n)$ 轮。暴力维护连续的来自同一连通块的段，然后查询后继之类就直接跳即可。可以发现这样可以做到线性查询。

复杂度对数。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200100;
int T,n,E,cnt,ord[N],dsu[N<<1],val[N<<1];
struct EDGE{int x,y,z;};
vector<int>v[N],u[N<<1];
vector<int>::iterator itf[N],itb[N];
inline int find(const int&x){return dsu[x]==x?x:dsu[x]=find(dsu[x]);}
int dfn[N<<1],rev[N<<1],tot,lim,dep[N<<1],st[20][N<<2],LG[N<<2],fir[N<<1];
inline int MIN(const int&x,const int&y){return dep[x]<dep[y]?x:y;}
inline bool dfncmp(const int&x,const int&y){return dfn[x]<dfn[y];}
inline int LCA(int x,int y){
	x=fir[x],y=fir[y];if(x>y)swap(x,y);
	int k=LG[y-x+1];
	return MIN(st[k][x],st[k][y-(1<<k)+1]);
}
void dfs(int x){
	if(x<=n)dfn[x]=++tot,rev[tot]=x;
	st[0][++lim]=x,fir[x]=lim;
	for(auto y:u[x])dep[y]=dep[x]+1,dfs(y),st[0][++lim]=x;
}
void Kruskal(EDGE*e,int m){
	cnt=n,tot=lim=0;
	for(int i=1;i<=m;i++)ord[i]=i;
	sort(ord+1,ord+m+1,[&](int x,int y){return e[x].z<e[y].z;});
	for(int i=1;i<=n;i++)dsu[i]=i;
	for(int i=1,x,y,z;i<=m;i++)
		if((x=find(e[ord[i]].x))!=(y=find(e[ord[i]].y)))
		val[z=++cnt]=e[ord[i]].z,
		u[z].push_back(x),u[z].push_back(y),
		dsu[x]=dsu[y]=dsu[z]=z;
	dfs(cnt);
	for(int i=2;i<=lim;i++)LG[i]=LG[i>>1]+1;
	for(int j=1;j<=LG[lim];j++)for(int i=1;i+(1<<j)-1<=lim;i++)
		st[j][i]=MIN(st[j-1][i],st[j-1][i+(1<<j-1)]);
	for(int i=1;i<=cnt;i++)u[i].clear();
}
int lp[N],rp[N];
int fp[N],bp[N];
int mn[N],mx[N],my[N],m;
EDGE e[N],f[N];
void mina(){
	scanf("%d%d",&n,&m),E=0;
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].z),
		v[e[i].x].push_back(e[i].y),v[e[i].y].push_back(e[i].x);
	Kruskal(e,m);
	for(int i=1;i<=n;i++){
		sort(v[i].begin(),v[i].end(),dfncmp);
		itf[i]=itb[i]=lower_bound(v[i].begin(),v[i].end(),i,dfncmp);
		if(itf[i]!=v[i].begin())itf[i]--;
		fp[i]=bp[i]=dfn[i];
	}
	for(int i=1;i<=n;i++)dsu[i]=i;
	while(E<n-1){
		for(int l=1,r=1;l<=n;l=r){
			for(r=l;r<=n&&find(rev[l])==find(rev[r]);r++);
			for(int i=l;i<r;i++)lp[i]=l,rp[i]=r-1;
		}
		for(int i=1;i<=n;i++)mn[i]=0x3f3f3f3f,mx[i]=my[i]=-1;
//		for(int i=1;i<=n;i++)printf("[%d,%d]",lp[i],rp[i]);puts("");
		for(int i=1;i<=n;i++){
			while(fp[i]){
				if(find(rev[fp[i]])==find(i)){fp[i]=lp[fp[i]]-1;continue;}
				while(itf[i]!=v[i].begin()&&dfn[*itf[i]]>fp[i])itf[i]--;
				if(dfn[*itf[i]]==fp[i])fp[i]--;
				else break;
			}
			while(bp[i]<=n){
				if(find(rev[bp[i]])==find(i)){bp[i]=rp[bp[i]]+1;continue;}
				while(itb[i]!=v[i].end()&&dfn[*itb[i]]<bp[i])itb[i]++;
				if(itb[i]!=v[i].end()&&dfn[*itb[i]]==bp[i])bp[i]++;
				else break;
			}
			int z=0x3f3f3f3f,y=-1;
			if(fp[i]){
				int Z=val[LCA(rev[fp[i]],i)];
				if(Z<z)z=Z,y=rev[fp[i]];
			}
			if(bp[i]<=n){
				int Z=val[LCA(i,rev[bp[i]])];
				if(Z<z)z=Z,y=rev[bp[i]];
			}
			if(z<mn[find(i)])mn[find(i)]=z,mx[find(i)]=i,my[find(i)]=y;
		}
		for(int i=1;i<=n;i++)if(dsu[i]==i){
			int j=find(my[i]);
			if(j==i)continue;
//			printf("LINK:%d,%d:%d\n",mx[i],my[i],mn[i]);
			dsu[i]=j;
			++E,f[E].x=mx[i],f[E].y=my[i],f[E].z=mn[i];
		}
	}
	Kruskal(f,E);
	for(int i=1;i<=m;i++)printf("%d ",val[LCA(e[i].x,e[i].y)]);puts("");
	for(int i=1;i<=n;i++)v[i].clear();
}
int main(){
	scanf("%d",&T);
	while(T--)mina();
	return 0;
}
```



---

## 作者：cwfxlh (赞：3)

# [CF1648E](https://www.luogu.com.cn/problem/CF1648E)    

首先建出 Kruskal 重构树，两点的最短路就是两点 lca 的权值。尝试求出补图的最小生成树。我们考虑使用 Boruvka 算法，进行 $\log n$ 轮，每次找到对于每个连通块最近的连通块。     

容易发现，在 Kruskal 重构树上，深度越深的点权值越小。于是如果 $dfn_i<dfn_j<dfn_u$，则 $dis(i,j)<dis(i,k)$，这告诉我们，只需要对于每个点找到它在 dfs 序上前后第一个可以连边的地方即可。可以连边的限制有两个，首先不能在同一个连通块，另外两点之间在原图不能有连边。对于每个点求出最近的合法点，对每个连通块找到最小的边，合并即可。     

这里给出一种找到合法点对的实现方式，复杂度是 $(n+m)\log n$ 的，可能不是很精细但足以通过。枚举连通块，维护一个 set 记录所有不在当前连通块的点，然后枚举连通块里的点，去 set 里找到前驱后继，如果找到的点在原图中存在连边，则往前/后跳。发现每次跳和查找的复杂度都是 $\log n$ 的，失配的次数也是 $O(m)$ 的，于是这一步的总复杂度就是 $(n+m)\log n$。最后代码复杂度 $(n+m)\log^2 n$。    

代码：   

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
struct Edge{
	int st;
	int ed;
	int val;
}E[500003],E2[500003];
set<int>E3[500003];
int totE;
int bcj[500003],totP,nxt[500003][2],bt[500003][2],e[500003][2];
int v[500003],son[500003][2],dep[500003],F[500003][21],dfn[500003],idx,wz[500003],sum,lj[500003][3];
vector<int>lst[500003];
int finf(int now){
	if(bcj[now]!=now)bcj[now]=finf(bcj[now]);
	return bcj[now];
}
bool comp(Edge X,Edge Y){return X.val<Y.val;}
void dfs(int now){
	if(now<=n){
		dfn[now]=++idx;
		wz[idx]=now;
	}
	for(int i=1;;i++){
		if(F[F[now][i-1]][i-1]==0)break;
		F[now][i]=F[F[now][i-1]][i-1];
	}
	if(son[now][0]){
		F[son[now][0]][0]=now;
		dep[son[now][0]]=dep[now]+1;
		dfs(son[now][0]);
	}
	if(son[now][1]){
		F[son[now][1]][0]=now;
		dep[son[now][1]]=dep[now]+1;
		dfs(son[now][1]);
	}
	return;
}
int _lca(int X,int Y){
	if(dep[X]<dep[Y])swap(X,Y);
	int c=20;
	while(c--)if(dep[F[X][c]]>=dep[Y])X=F[X][c];
	c=20;
	while(c--)if(F[X][c]!=F[Y][c])X=F[X][c],Y=F[Y][c];
	if(X==Y)return X;
	return F[X][0];
}
set<int>R;
set<pair<int,int> >R2;
bool chk(int X,int Y){
	auto p=E3[X].lower_bound(Y);
	if(p!=E3[X].end()&&(*p)==Y)return true;
	return false;
}
void cg(){
	for(int i=1;i<=n;i++)R2.insert(make_pair(i,wz[i]));
	for(auto i:R){
		for(auto j:lst[i])R2.erase(make_pair(dfn[j],j));
		for(auto j:lst[i]){
			auto p=R2.lower_bound(make_pair(dfn[j],j));
			while(p!=R2.begin()&&(p==R2.end()||(*p).first>dfn[j]||chk((*p).second,j)))p--;
			if(p!=R2.end()&&(*p).first<dfn[j]&&(!chk((*p).second,j)))nxt[dfn[j]][0]=(*p).first;
			p=R2.lower_bound(make_pair(dfn[j],j));
			while(p!=R2.end()&&chk((*p).second,j))p++;
			if(p!=R2.end()&&(!chk((*p).second,j)))bt[dfn[j]][0]=(*p).first;
		}
		for(auto j:lst[i])R2.insert(make_pair(dfn[j],j));
	}
	return;
}
int stk[500003],tot;
void Merge(int X,int Y){
	if(lst[X].size()<lst[Y].size())swap(X,Y);
	stk[++tot]=Y;
	bcj[Y]=X;
	for(auto u:lst[Y])lst[X].emplace_back(u);
	lst[Y].clear();
	lst[Y].shrink_to_fit();
	return;
}
int main(){
	//freopen("CF1648E.in", "r", stdin);
	//freopen("CF1648E.out","w",stdout);
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		cin>>n>>m;
		for(int i=1;i<=n*2;i++){
			for(int j=0;j<=20;j++)F[i][j]=0;
			son[i][0]=son[i][1]=0;
			dfn[i]=wz[i]=0;
			lst[i].clear();
			lst[i].shrink_to_fit();
		}
		totE=idx=0;
		R.clear();
		R2.clear();
		for(int i=1;i<=n;i++)E3[i].clear();
		for(int i=1;i<=m;i++){
			cin>>E[i].st>>E[i].ed>>E[i].val;
			e[i][0]=E[i].st;
			e[i][1]=E[i].ed;
			E3[E[i].st].insert(E[i].ed);
			E3[E[i].ed].insert(E[i].st);
		}
		sort(E+1,E+m+1,comp);
		for(int i=1;i<=n;i++)bcj[i]=i;
		totP=n;
		for(int i=1;i<=m;i++){
			if(finf(E[i].st)==finf(E[i].ed))continue;
			totP++;
			bcj[totP]=totP;
			v[totP]=E[i].val;
			son[totP][0]=finf(E[i].st);
			son[totP][1]=finf(E[i].ed);
			bcj[finf(E[i].st)]=bcj[finf(E[i].ed)]=totP;
		}
		dep[totP]=1;
		dfs(totP);
		sum=n;
		R.clear();
		for(int i=1;i<=n;i++){
			bcj[i]=i;
			lst[i].emplace_back(i);
			R.insert(i);
		}
		while(sum>1){
			for(int i=1;i<=n;i++){
				bcj[i]=finf(i);
				nxt[i][0]=bt[i][0]=-1;
			}
			cg();
			for(int i=1;i<=n;i++){
				if(nxt[i][0]!=-1)nxt[i][1]=v[_lca(wz[i],wz[nxt[i][0]])];
				if(bt[i][0]!=-1)bt[i][1]=v[_lca(wz[i],wz[bt[i][0]])];
			}
			for(auto j:R){
				lj[j][0]=lj[j][1]=lj[j][2]=-1;
				for(auto u:lst[j]){
					if(nxt[dfn[u]][0]!=-1&&(lj[j][2]==-1||nxt[dfn[u]][1]<lj[j][2])){
						lj[j][0]=u;
						lj[j][1]=wz[nxt[dfn[u]][0]];
						lj[j][2]=nxt[dfn[u]][1];
					}
					if(bt[dfn[u]][0]!=-1&&(lj[j][2]==-1||bt[dfn[u]][1]<lj[j][2])){
						lj[j][0]=u;
						lj[j][1]=wz[bt[dfn[u]][0]];
						lj[j][2]=bt[dfn[u]][1];
					}
				}
			}
			tot=0;
			for(auto j:R){
				if(lj[j][0]!=-1){
					if(finf(lj[j][0])==finf(lj[j][1]))continue;
					E2[++totE].st=lj[j][0];
					E2[totE].ed=lj[j][1];
					E2[totE].val=lj[j][2];
					Merge(finf(lj[j][0]),finf(lj[j][1]));
				}
			}
			sum-=tot;
			for(int i=1;i<=tot;i++)R.erase(stk[i]);
		}
		sort(E2+1,E2+totE+1,comp);
		for(int i=1;i<=n;i++)bcj[i]=i;
		totP=n;
		for(int i=1;i<=totE;i++){
			if(finf(E2[i].st)==finf(E2[i].ed))continue;
			totP++;
			bcj[totP]=totP;
			v[totP]=E2[i].val;
			son[totP][0]=finf(E2[i].st);
			son[totP][1]=finf(E2[i].ed);
			bcj[finf(E2[i].st)]=bcj[finf(E2[i].ed)]=totP;
		}
		for(int i=1;i<=n*2;i++){
			for(int j=0;j<=20;j++)F[i][j]=0;
		}
		dep[totP]=1;
		dfs(totP);
		for(int i=1;i<=m;i++)cout<<v[_lca(e[i][0],e[i][1])]<<" ";
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：wishapig (赞：3)

# CF1648E Air Reform

~~头铁老哥直接冲 $3$ 只 $\log$ 喜提最劣解~~

**提前声明这不是标算**

---

首先对于原图按边权从小到大建 Kruskal 重构树，那么补图中边 $(u,v)$ 的权值就是 $u,v$ 在重构树上最近公共祖先的点权。

然后，按题目意思，我们需要再对补图如法炮制，建出重构树之后求边权，但可惜的是补图的边数远远超过了可以承受的范围。

而且，直接在考虑通过原图的 Kruskal 重构树来确定补图的 Kruskal 重构树也是很困难的（似乎可以按边数做数据分治但我不是很清楚）。

于是我们考虑不求重构树，而是求补图的**最小生成树**。因为最小生成树一定是最小瓶颈生成树，那么求出补图最小生成树之后只需要求 $(u,v)$ 链上的最大边权就是答案。

但怎么求最小生成树呢？补图上边数非常大，而且边权可以表示为（某种意义上的）一个函数（即两点 LCA 对应的点权），考虑使用 Boruvka 算法求解最小生成树。

那么需要解决的就是对每个节点 $u$，求出补图中一端为 $u$，另一端不在 $u$ 连通块内的边权最小的边。考虑补图的性质：不包含原图上的边，而且边权为两点 LCA 对应的点权，我们可以从 $u$ 向上倍增到深度最大的一个祖先 $p$ 满足 $p$ 子树内存在 既不在 $u$ 所在连通块内也不在原图中与 $u$ 相连 的点，这个可以记出 dfn 之后转化为区间问题。

然后就三个 $\log$ 了，~~稍微卡卡常就跑过去了~~。

```c++
int Find1(int u){ return fth[u]==u?u:fth[u]=Find1(fth[u]); }
int Find2(int u){ return bel[u]==u?u:bel[u]=Find2(bel[u]); }
void dfs1(int u, int f){
	fa[u][0]=f; dfn[u]=INF;
	for (int i=1; i<=17; i++) fa[u][i]=fa[fa[u][i-1]][i-1];
	if (u<=n){ dfn[u]=End[u]=++Time; return; }
	for (int v:KG[u]){
		dfs1(v,u);
		dfn[u]=min(dfn[u],dfn[v]);
		End[u]=max(End[u],End[v]);
	}
}
void update(int x, int y){
	int now=Leaf[x]; vex[now]=y==-1?id[x]:-1;
	for (now>>=1; now; now>>=1) vex[now]=max(vex[ls],vex[rs]);
	for (; x<=n; x+=x&-x) BIT[x]+=y;
}
int query(int now, int l, int r, int x, int y){
	if (l==x && r==y) return vex[now];
	int mid=(l+r)>>1;
	if (mid>=y) return query(ls,l,mid,x,y);
	else if (mid<x) return query(rs,mid+1,r,x,y);
	else return max(query(ls,l,mid,x,mid),query(rs,mid+1,r,mid+1,y));
}
void dfs2(int u, int f, int lst){
	Fa[u][0]=f; dep[u]=dep[f]+1; mx[u][0]=lst;
	for (int i=1; i<=17; i++){
		Fa[u][i]=Fa[Fa[u][i-1]][i-1];
		mx[u][i]=max(mx[u][i-1],mx[Fa[u][i-1]][i-1]);
	}
	for (auto v:NG[u])
		if (v.first!=f) dfs2(v.first,u,v.second);
}
int query(int u, int v){
	if (u==v) return 0;
	if (dep[u]<dep[v]) swap(u,v);
	int d=dep[u]-dep[v],ans=0;
	for (int i=17; ~i; i--)
		if (d&(1<<i)) ans=max(ans,mx[u][i]),u=Fa[u][i];
	if (u==v) return ans;
	for (int i=17; ~i; i--)
		if (Fa[u][i]^Fa[v][i]){
			ans=max(ans,max(mx[u][i],mx[v][i]));
			u=Fa[u][i],v=Fa[v][i];
		}
	return max(ans,max(mx[u][0],mx[v][0]));
}
void build(int now, int l, int r){
	if (l==r) return vex[now]=id[l],Leaf[l]=now,void();
	int mid=(l+r)>>1;
	build(ls,l,mid); build(rs,mid+1,r);
	vex[now]=max(vex[ls],vex[rs]);
}
inline int Query(int x, int y){
	int res=0;
	for (; y; y-=y&-y) res+=BIT[y];
	for (x--; x; x-=x&-x) res-=BIT[x];
	return res;
}
inline int read(){
	char ch=getchar(); int num=0;
	while (ch<'0' || ch>'9') ch=getchar();
	while (ch>='0' && ch<='9') num=(num<<3)+(num<<1)+ch-'0',ch=getchar();
	return num;
}
void P(int x){
	if (!x) return;
	P(x/10); putchar(x%10+'0');
}
inline void Print(int x){
	if (!x) puts("0 ");
	else P(x),putchar(' ');
}
void solve(){
	n=read(),m=read(); Time=0;
	for (int i=1; i<=m; i++){
		E[i].u=read(),E[i].v=read(),E[i].w=read(); E[i].id=i;
		G[E[i].u].push_back(E[i].v);
		G[E[i].v].push_back(E[i].u);
	}
	sort(E+1,E+1+m); siz=n;
	for (int i=1; i<=n; i++) fth[i]=i;
	for (int i=1; i<=m; i++){
		int x=Find1(E[i].u),y=Find1(E[i].v);
		if (x!=y){
			siz++; fth[x]=fth[y]=fth[siz]=siz; val[siz]=E[i].w;
			KG[siz].push_back(x),KG[siz].push_back(y);
		}
	}
	dfs1(siz,0);
	for (int i=1; i<=n; i++) id[dfn[i]]=i,bel[i]=i;
	build(1,1,n);
	while (1){
		int cnt=0;
		for (int i=1; i<=n; i++){
			int p=Find2(i);
			if (!vis[p]) vis[p]=++cnt;
			vec[vis[p]].push_back(i);
		}
		for (int i=1; i<=n; i++) vis[Find2(i)]=0;
		if (cnt==1){ vec[1].clear(); break; }
		for (int i=1; i<=cnt; i++){
			int Eu=0,Ev=0,Ew=INF;
			for (int u:vec[i]){ cur[dfn[u]]++; if (cur[dfn[u]]==1) update(dfn[u],1); }
			for (int u:vec[i]){
				int pos=u;
				for (int v:G[u]){ cur[dfn[v]]++; if (cur[dfn[v]]==1) update(dfn[v],1); }
				for (int i=17; ~i; i--)
					if (fa[u][i] && Query(dfn[fa[u][i]],End[fa[u][i]])==End[fa[u][i]]-dfn[fa[u][i]]+1) u=fa[u][i];
				u=fa[u][0]; 
				if (u){
					int v=query(1,1,n,dfn[u],End[u]);
					if (v!=-1 && val[u]<Ew) Ew=val[u],Eu=pos,Ev=v;
				}
				for (int v:G[pos]){ cur[dfn[v]]--; if (cur[dfn[v]]==0) update(dfn[v],-1); }
			}
			for (int u:vec[i]){ cur[dfn[u]]--; if (cur[dfn[u]]==0) update(dfn[u],-1); }
			edge[i][0]=Eu,edge[i][1]=Ev,edge[i][2]=Ew;
		}
		for (int i=1; i<=cnt; i++){
			if (edge[i][2]==INF) continue;
			int x=Find2(edge[i][0]),y=Find2(edge[i][1]);
			if (x!=y){
				bel[x]=y;
				NG[edge[i][0]].push_back(make_pair(edge[i][1],edge[i][2]));
				NG[edge[i][1]].push_back(make_pair(edge[i][0],edge[i][2]));
			}
		}
		for (int i=1; i<=cnt; i++) vec[i].clear();
	}
	dfs2(1,0,0);
	for (int i=1; i<=m; i++) ans[E[i].id]=query(E[i].u,E[i].v);
	for (int i=1; i<=m; i++) Print(ans[i]); puts("");
	for (int i=1; i<=n; i++){
		bel[i]=cur[i]=BIT[i]=Leaf[i]=id[i]=0;
		for (int j=0; j<=17; j++) Fa[i][j]=mx[i][j]=0;
		while (!G[i].empty()) G[i].pop_back();
		while (!NG[i].empty()) NG[i].pop_back();
	}
	for (int i=1; i<=siz; i++){
		for (int j=0; j<=17; j++) fa[i][j]=0;
		dfn[i]=End[i]=val[i]=fth[i]=dep[i]=0;
		while (!KG[i].empty()) KG[i].pop_back();
	}
	for (int i=1; i<=m; i++) ans[i]=0;
}
```



---

## 作者：Albert_van (赞：1)

就是 $m$ 组询问**补图的最小生成树**上的树链最大值。有两种基本思路求这棵树。

第一种，Kruskal，基于找到最小的边使两端点不连通。考虑补图中 $(x,y)$ 的边权，它是原图最小生成树上的树链最大值。从小到大枚举补图的边，相当于从小到大枚举原图最小生成树的边 $(u,v,w)$，然后：

令原图上，连接这条边之前，$u$ 所在连通块为 $S$，$v$ 所在连通块为 $T$，那么对于 $x\in S,y\in T$，必然有补图中 $(x,y)$ 的边权恰为 $w$。当然这建立在补图中 $(x,y)$ 这条边存在的前提下。

所以直接模拟这个过程，暴力枚举 $x$ 所在补图连通块 $X$（显然 $X\subseteq S$），然后不断地去寻找 $y$ 所在补图连通块 $Y(Y\subseteq T)$。为了判断 $X$ 与 $Y$ 是否可以合并，枚举 $x\in X$ 和 $y\in T$，观察 $(x,y)$ 这条边在原图是否不存在即可。

四重循环。这个复杂度分三部分。其一，合并 $X$ 与 $Y$。启发式合并即可总计 $\mathcal O(n\log n)$。

其二，寻找 $Y$ 的过程中枚举 $y$。注意到每对 $(x,y)$ 至多枚举一次，$y$ 会被跳过当且仅当原图存在边 $(x,y)$。所以总共 $\mathcal O(m)$。

其三，合并 $X$ 与 $Y$ 的次数。显然是 $\mathcal O(n)$。

然后注意到判断 $(x,y)$ 原图是否有边是 $\Theta(\log m)$ 的。于是令 $m=\Omega(n)$ 则总复杂度 $\mathcal O(m\log m)$。这个应该是 CF 的 std。

---

第二种，Boruvka，基于对每个点找到离开所在连通块的最小边。对原图建出 Kruskal 重构树，补图中 $(x,y)$ 边权为 $w_{\operatorname {lca(x,y)}}$。

问题转化为，对于所有叶子结点 $u$，找到其最深的祖先 $a$，满足 $a$ 的子树内存在一个 $v$ 使得： 

- $v$ 不在 $u$ 的连通块内；

- 原图中 $(u,v)$ 无边。

考虑连通块在重构树上形如一段 dfn 区间。合并连通块就是合并区间，同时子树也是一段 dfn 区间，于是二分一下即可找到 $a$。

对于原图无边这个限制，枚举 $u$ 的所有 $k$ 个出点，然后把查询区间暴力分成 $\mathcal O(k)$ 个子段。这样一次 Boruvka 的过程只会查 $\mathcal O(m)$ 个区间。

总复杂度 $\mathcal O(n\log^2 n)$。

个人写的是第一种思路。有点难调。

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <cstring>

using namespace std;

namespace fIO{
	char c;void re(int &x){
		x=0;c=getchar();
		while(c<'0'||c>'9') c=getchar();
		while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	}
	char st[20];int tp;
	void wr(int n){
		while(n) st[++tp]=n%10+48,n/=10;
		while(tp) putchar(st[tp--]);
	}
}using fIO::re;using fIO::wr;

const int N=231231;

struct U{
	int anc[N];
	void set(int n){for(int i=1;i<=n;++i) anc[i]=i;}
	int qry(int x){return anc[x]==x?x:anc[x]=qry(anc[x]);}
	bool sam(int x,int y){return qry(x)==qry(y);}
	void mrg(int x,int y){anc[qry(x)]=qry(y);}
}O,B;

namespace AT{
	struct edg{int v,w;};
	vector<edg> vc[N];
	void lnk(int x,int y,int w){
		vc[x].push_back((edg){y,w});vc[y].push_back((edg){x,w});
	}
	int f[N][18],anc[N][18],dep[N];
	void build(int now,int lst){
		anc[now][0]=lst;dep[now]=dep[lst]+1;
		for(int i=1;(1<<i)<dep[now];++i) anc[now][i]=anc[anc[now][i-1]][i-1],
			f[now][i]=max(f[now][i-1],f[anc[now][i-1]][i-1]);
		for(auto[v,w]:vc[now]) if(v!=lst) f[v][0]=w,build(v,now);
	}
	int qry(int x,int y){
		int res=0;if(dep[x]<dep[y]) swap(x,y);
		for(int i=17;~i;--i) if((1<<i)<=dep[x]-dep[y])
			res=max(res,f[x][i]),x=anc[x][i];
		for(int i=17;~i;--i) if(anc[x][i]!=anc[y][i])
			res=max(res,max(f[x][i],f[y][i])),x=anc[x][i],y=anc[y][i];
		if(x!=y) res=max(res,max(f[x][0],f[y][0]));
		return res;
	}
	void clr(int n){
		for(int i=1;i<=n;++i) vc[i].clear(),memset(anc[i],0,sizeof(anc[i]));
	}
}

set<int> blk[N],sub[N];

int merg(int X,int Y){
	if(blk[X].size()>blk[Y].size()) swap(X,Y);
	for(int x:blk[X]) blk[Y].insert(x);
	return Y;
}

vector<int> vc[N],del;int pos[N];

void mrgsub(int &u,int &v,int w){
	if(sub[B.qry(u)].size()>sub[B.qry(v)].size()) swap(u,v);
	int pu=u,pv=v;u=B.qry(u);v=B.qry(v);
	for(int X:sub[u]){
		del.clear();int p=X;
		for(int Y:sub[v]){
			for(int x:blk[X]){
				bool flg=0;for(int y:blk[Y]){
					auto it=lower_bound(vc[x].begin(),vc[x].end(),y);
					if(it==vc[x].end()||*it!=y){
					flg=1;p=merg(p,Y);del.push_back(Y);AT::lnk(x,y,w);break;
				}}
				if(flg) break;
			}
		}
		for(int Y:del) sub[v].erase(Y);
		sub[v].insert(p);
	}
	B.mrg(u,v);u=pu;v=pv;
}

struct edg{int x,y,w,id;}e[N];

int ans[N];

int main()
{
	int T;re(T);while(T--){
		int n,m;re(n);re(m);O.set(n);B.set(n);AT::clr(n);
		for(int i=1;i<=n;++i) pos[i]=i,vc[i].clear(),
			sub[i].clear(),sub[i].insert(i),blk[i].clear(),blk[i].insert(i);
		for(int i=1;i<=m;++i) re(e[i].x),re(e[i].y),re(e[i].w),e[i].id=i,
			vc[e[i].x].push_back(e[i].y),vc[e[i].y].push_back(e[i].x);
		for(int i=1;i<=n;++i) sort(vc[i].begin(),vc[i].end());
		sort(e+1,e+m+1,[](edg u,edg v){return u.w<v.w;});
		for(int i=1;i<=m;++i) if(!O.sam(e[i].x,e[i].y))
			mrgsub(e[i].x,e[i].y,e[i].w),O.mrg(e[i].x,e[i].y);
		AT::build(1,0);
		for(int i=1;i<=m;++i) ans[e[i].id]=AT::qry(e[i].x,e[i].y);
		for(int i=1;i<=m;++i) wr(ans[i]),putchar(' ');puts("");
	}
}
```

---

## 作者：sunkuangzheng (赞：1)

$\textbf{CF1648E *3200}$

> - 给定一张 $n$ 个点 $m$ 条边的带权无向图，建立其补图 $G'$，$G'$ 上边 $u,v$ 的权值是原图上 $u,v$ 的最小瓶颈路。
> - 对于原图上的每条边 $u,v$，求其在补图 $G'$ 上的最小瓶颈路。
> - $1 \le n,m \le 2 \cdot 10^5$。

_想题十分钟，写题半小时，调题两小时_。

如果我们能建出补图的 kruskal 重构树，那么查询就只需要在上面查 LCA，但是边数是 $\mathcal O(n^2)$ 级别的，考虑模拟 Kruskal。

建出原图的 Kruskal 重构树，按点权从小到大枚举 LCA 点 $x$，那么所有 LCA 为 $x$ 的点对在补图上的边权都是 $val_x$。枚举 $siz$ 较小的儿子 $U$ 里的叶子 $u$，考虑如何快速在另一个儿子 $V$ 里找到一个和 $u$ 不在一个连通块里的叶子 $v$，我们只需要用线段树维护叶子 dfn 序上的连通块编号，查询 $\min / \max$。合并一次会导致连通块数量 $-1$，因此合并次数是 $\mathcal O(n)$ 的。合并时按秩合并并在线段树里修改连通块信息。

需要处理的细节是，如果查到的 $v$ 本身和 $u$ 在补图上没有边，我们可以直接把 $v$ 标记成 $\inf$ 然后继续查询。由于补图只缺少 $m$ 条边，故这一部分均摊下来复杂度也是 $\mathcal O(m)$ 的。

总复杂度 $\mathcal O(n \log^2 n + m \log n)$。


```cpp
/**
 *    author: sunkuangzheng
 *    created: 11.09.2024 07:26:17
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 4e5+5;
using namespace std;
int T,n,m,df[N],tt,a[N],dfn[N],nfd[N],ct,u,v,w,p[N],bl[N],sz[N],st[20][N]; 
vector<tuple<int,int,int>> gr,rg; vector<int> g[N],tp;
int fd(int x){return x == df[x] ? x : df[x] = fd(df[x]);}
int cmp(int u,int v){return dfn[u] < dfn[v] ? u : v;}
struct sg{
    struct nd{int mx,mn;}t[N*4]; int bl[N];
    nd mg(nd a,nd b){
        if(bl[nfd[a.mx]] == 1e9) return b;
        if(bl[nfd[b.mx]] == 1e9) return a;
        return nd{bl[nfd[a.mx]] > bl[nfd[b.mx]] ? a.mx : b.mx,bl[nfd[a.mn]] < bl[nfd[b.mn]] ? a.mn : b.mn};
    }
    void bd(int s,int l,int r){
        if(l == r) return bl[nfd[l]] = ::bl[nfd[l]],t[s] = {l,l},void();
        int mid = (l + r) / 2; bd(s*2,l,mid),bd(s*2+1,mid+1,r);
        t[s] = mg(t[s*2],t[s*2+1]);
    }void upd(int s,int l,int r,int x,int k){
        if(l == r) return bl[nfd[l]] = k,void();
        int mid = (l + r) / 2;
        if(x <= mid) upd(s*2,l,mid,x,k); else upd(s*2+1,mid+1,r,x,k);
        t[s] = mg(t[s*2],t[s*2+1]);
    }nd qry(int s,int l,int r,int ql,int qr){ 
        if(ql <= l && r <= qr) return t[s];
        int mid = (l + r) / 2;
        if(ql > mid) return qry(s*2+1,mid+1,r,ql,qr);
        if(qr <= mid) return qry(s*2,l,mid,ql,qr);
        return mg(qry(s*2,l,mid,ql,qr),qry(s*2+1,mid+1,r,ql,qr));
    }
}sg;
struct rdsu{
    int fa[N]; vector<int> g[N];
    int fd(int x){return x == fa[x] ? x : fd(fa[x]);}
    void init(int n){for(int i = 1;i <= n;i ++) fa[i] = bl[i] = i,g[i].clear(),g[i].push_back(i);}
    void mg(int u,int v){
        if(u = fd(u),v = fd(v),u == v) return ;
        if(g[u].size() < g[v].size()) swap(u,v);
        for(int i : g[v]) bl[i] = u,sg.upd(1,1,n,dfn[i],u),g[u].push_back(i);
        g[v].clear(),fa[v] = u;
    }
}d;
void dfs1(int u){
    if(!g[u].size()) dfn[u] = ++ct,nfd[ct] = u,sz[u] = 1; else dfn[u] = 1e9,sz[u] = 0;
    for(int v : g[u]) dfs1(v),dfn[u] = min(dfn[u],dfn[v]),sz[u] += sz[v];
}void build(){
    sort(gr.begin(),gr.end()),tt = n;
    for(int i = 1;i <= 2 * n;i ++) g[i].clear(),df[i] = i; 
    for(auto [w,u,v] : gr){
        if(u = fd(u),v = fd(v),u == v) continue;
        a[++tt] = w,df[u] = df[v] = tt,g[tt].push_back(u),g[tt].push_back(v);
    }
}void dfs2(int u){if(!g[u].size()) tp.push_back(u);for(int v : g[u]) dfs2(v);}
void dfs3(int u,int f){st[0][dfn[u] = ++ct] = f;for(int v : g[u]) dfs3(v,u);}
int lca(int u,int v){
    if(u == v) return u;
    if((u = dfn[u]) > (v = dfn[v])) swap(u,v);
    int k = __lg(v - u);
    return cmp(st[k][u+1],st[k][v-(1<<k)+1]);
}void los(){
    cin >> n >> m; map<pair<int,int>,int> mp;
    for(int i = 1;i <= m;i ++) cin >> u >> v >> w,gr.emplace_back(w,u,v),mp[{u,v}] = mp[{v,u}] = 1;
    rg = gr,build(),ct = 0,dfs1(tt);
    iota(p+1,p+tt-n+1,n+1),sort(p+1,p+tt-n+1,[&](int x,int y){return a[x] < a[y];});
    d.init(n),sg.bd(1,1,n); gr.clear();
    for(int i = 1;i <= tt - n;i ++){
        u = p[i],tp.clear(); 
        if(sz[g[u][0]] > sz[g[u][1]]) swap(g[u][0],g[u][1]);
        dfs2(g[u][0]); int l = dfn[g[u][1]],r = dfn[g[u][1]] + sz[g[u][1]] - 1;
        for(int j : tp){
            vector<int> tm;
            for(;;){
                int xm = nfd[sg.qry(1,1,n,l,r).mx];
                if(bl[xm] == bl[j] || sg.bl[xm] == 1e9){
                    int xm = nfd[sg.qry(1,1,n,l,r).mn];
                    if(bl[xm] == bl[j] || sg.bl[xm] == 1e9){
                        for(int i : tm) sg.upd(1,1,n,dfn[i],bl[i]);
                        break;
                    }else{
                        if(!mp[{j,xm}]) d.mg(xm,j),gr.emplace_back(a[u],xm,j);
                        sg.upd(1,1,n,dfn[xm],1e9),tm.push_back(xm);
                    }
                }else{
                    if(!mp[{j,xm}]) d.mg(xm,j),gr.emplace_back(a[u],xm,j);
                    sg.upd(1,1,n,dfn[xm],1e9),tm.push_back(xm);
                }
            }
        }
    }build(),ct = 0,dfs3(tt,0); 
    for(int j = 1;j <= __lg(tt);j ++) for(int i = 1;i + (1 << j) - 1 <= tt;i ++)
        st[j][i] = cmp(st[j-1][i],st[j-1][i+(1<<j-1)]);
    for(auto [w,u,v] : rg) cout << a[lca(u,v)] << " ";
    cout << "\n",gr.clear();
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    for(cin >> T;T --;) los();
}
```

---

## 作者：Arghariza (赞：0)

这个做法虽然常数较大，但不仅是 $O((n+m)\log n+\alpha n)$ 的，而且很好想也很好写。

考虑求补图 $G'$ 的最小生成树或者 Kruskal 重构树。（为了方便理解，下面的说明中，带撇的表示补图，不带的表示原图。）

先求出原图的重构树 $T$，那么补图上 $w'(u,v)=w_{lca(u,v)}$。

考虑 Boruvka 求补图的最小生成树，那么需要对于每个点 $u$，求出满足条件的点 $v$：

- $u$ 和 $v$ 目前不在同一个连通块内。
- $(u,v)\notin E$，即 $(u,v)$ 在原图没有连边。 
- $w'(u,v)$ 最小。

相当于在 $T$ 上 $u$ 的祖先集合 $anc(u)$ 中找一个**最深的**点 $x$，满足 $x$ 子树内存在叶子 $v$ 和 $u$ 不是同一个颜色且和 $u$ 没有连边，这样的 $v$ 就是我们找的点。

根据虚树那套理论，就相当于将所有点按照 dfn 排序，所有满足条件的点中 $v$ 取 $u$ 的前驱/后继。于是对于确定的 $u$，需要考虑的 $v$ 就减少到了 $O(1)$ 个。求出它们并取 $\min$ 即可。

考虑限制第一个条件即颜色不同，这应该是个经典 trick。预处理 dfn 排序后每个前缀/后缀的最大坐标值和次大坐标值/最小坐标值和次小坐标值，并强制让两个值颜色不同。这样可以 $O(1)$ 找到任意位置颜色不同于 $c$ 的前驱/后继。

那么我们从 $u$ 开始一直跳前驱/后继，这样跳到的点一定是可以满足第一个条件的。直到跳到一个点 $v$ 和 $u$ 在原图中没有连边即可。均摊是 $O(m)$ 的，因为每条边只可能被两个点跳到并继续。判断 $u,v$ 是否连边可以用哈希表 $O(1)$ 解决。

然后我们就把最小生成树建出来了。然后询问相当于路径边权最小值，这个再建一个 Kruskal 重构树就能 $O(n\log n)-O(1)$ 解决了。

复杂度 $O((n+m)\log n+\alpha n)$。代码是赶时间写的，可能可读性不高。如果把一些地方换成两个 $\log$ 的实现的话可能还会更好写。

```cpp
#include <bits/stdc++.h>
#define eb emplace_back
#define mp make_pair
#define fi first
#define se second
#define F(i, x, y) for (int i = (x); i <= (y); i++)
#define R(i, x, y) for (int i = (x); i >= (y); i--)
#define FIO(FILE) freopen(FILE".in", "r", stdin), freopen(FILE".out", "w", stdout)

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
bool Mbe;

const int N = 2e5 + 5;
const int M = 4e5 + 5;
const int Q = 1e5 + 7;
const int inf = 1e9;

template <class T> 
class Hash {	

	private:
	
		int tot, ct;
		int hd[Q + 5], nd[N << 1];
		
		struct E { 
			pi to; int nxt; T w; 
		} e[N << 1];
		
	public:
	
		void c() { 
			F (i, 1, ct) {
				hd[nd[i]] = 0;
			}
			tot = ct = 0; 
		}
		
		T & operator [] (pi x) {
			int u = (200001ll * x.fi + x.se) % Q + 1;
			for (int i = hd[u]; i; i = e[i].nxt) {
				if (e[i].to == x) {
					return e[i].w;
				}
			}
			if (!hd[u]) {
				nd[++ct] = u;
			}
			e[++tot] = (E) { x, hd[u], T(0) }, hd[u] = tot;
			return e[tot].w;
		}
		
		bool count(pi x) {
			int u = (200001ll * x.fi + x.se) % Q + 1;
			for (int i = hd[u]; i; i = e[i].nxt) {
				if (e[i].to == x) {
					return 1;
				}
			}
			return 0;
		}
		
		vector<pair<pi, T>> l() {
			vector<pair<pi, T>> res;
			F (i, 1, ct) {
				int u = nd[i];	
				for (int i = hd[u]; i; i = e[i].nxt) {
					res.eb(e[i].to, e[i].w);
				}
			}
			return res;
		}
};

int n, m, dc1, dc2;
int w1[M], w2[M], dfn[M], rdf[M], id[M], f[M][20], g[M][20], lg[M];

pi out[N];
pi ed[N];

vector<int> T1[M], T2[M];
Hash<bool> Me;

struct E {
	
	int u, v, w, i;
	
	E () { }
	E (int _u, int _v, int _w) : u(_u), v(_v), w(_w) { }
	
} e[N];

vector<E> T;

struct DSU {
	
	int sz;
	int f[N];
	
	void i() {
		F (i, 1, n) {
			f[i] = i;
		}
		sz = n;
	}
	
	int g(int x) {
		if (x == f[x]) {
			return x;
		}
		return f[x] = g(f[x]);
	}
	
	void m(int x, int y, int w) {
		int _x = x, _y = y;
		if ((x = g(x)) == (y = g(y))) {
			return;
		}
		T.eb(E(_x, _y, w));
		f[x] = y, sz--;
	}
	
} D;

struct KRT {
	
	int rt;
	int f[M];
	
	void i() {
		rt = n;
		F (i, 1, n) {
			f[i] = i;
		}
	}
	
	int g(int x) {
		if (x == f[x]) {
			return x;
		}
		return f[x] = g(f[x]);
	}
	
	void m(int x, int y, int w, int o) {
		x = g(x), y = g(y);
		if (x == y) {
			return;
		}
		rt++;
		f[x] = f[y] = f[rt] = rt;
		if (!o) {
			w1[rt] = w;
			T1[rt].eb(x);
			T1[rt].eb(y);
		} else {
			w2[rt] = w;
			T2[rt].eb(x);
			T2[rt].eb(y);
		}
	}
	
} K1, K2;

struct Info { 
	int x, y, cx, cy;
	Info () { }
	Info (int _x, int _y, int _cx, int _cy) :
		x(_x), y(_y), cx(_cx), cy(_cy) { }
};

Info gtmn(Info l, Info r) {
	if (l.x > r.x) {
		swap(l, r);
	}
	if (l.y > r.x && l.cx != r.cx) {
		l.y = r.x, l.cy = r.cx;
	} else if (l.y > r.y && l.cx != r.cy) {
		l.y = r.y, l.cy = r.cy;
	}
	return l;
}

Info gtmx(Info l, Info r) {
	if (l.x < r.x) {
		swap(l, r);
	}
	if (l.y < r.x && l.cx != r.cx) {
		l.y = r.x, l.cy = r.cx;
	} else if (l.y < r.y && l.cx != r.cy) {
		l.y = r.y, l.cy = r.cy;
	}
	return l;
}

Info pr[M], sf[M];

void clr() {
	F (i, 1, K1.rt) {
		T1[i].clear();
	}
	F (i, 1, K2.rt) {
		T2[i].clear();
	}
	Me.c();
	T.clear();
	dc1 = dc2 = 0;
}

int gt(int x, int y, int o) {
	if (!o) {
		return dfn[x] < dfn[y] ? x : y;
	} else {
		return id[x] < id[y] ? x : y;
	}
}

void dfs1(int u, int fa) {
	rdf[dfn[u] = ++dc1] = u;
	f[dc1][0] = fa;
	for (int v : T1[u]) {
		dfs1(v, u);
	}
}

void dfs2(int u, int fa) {
	g[id[u] = ++dc2][0] = fa;
	for (int v : T2[u]) {
		dfs2(v, u);
	}
}

int lca(int u, int v, int o) {
	if (u == v) {
		return u;
	}
	if (!o) {
		u = dfn[u], v = dfn[v];
	} else {
		u = id[u], v = id[v];
	}
	if (u > v) {
		swap(u, v);
	}
	u++;
	int len = lg[v - u + 1];
	if (!o) {
		return gt(f[u][len], f[v - (1 << len) + 1][len], o);
	} else {
		return gt(g[u][len], g[v - (1 << len) + 1][len], o);
	}
}

void chk(pi &x, pi y) {
	x = min(x, y);
}

int pre(int i, int c) {
	if (pr[i - 1].cx != c) {
		return pr[i - 1].x;
	} else {
		return pr[i - 1].y;
	}
}

int suf(int i, int c) {
	if (sf[i + 1].cx != c) {
		return sf[i + 1].x;
	} else {
		return sf[i + 1].y;
	}
}

void boruvka() {
	D.i();
	while (D.sz != 1) {
		F (i, 1, n) {
			out[i] = mp(inf, 0);
		}
		pr[0] = Info(0, 0, 0, 0);
		sf[K1.rt + 1] = Info(inf, 0, inf, 0);
		F (i, 1, K1.rt) {
			if (rdf[i] <= n) {
				pr[i] = gtmx(pr[i - 1], Info(i, 0, D.g(rdf[i]), 0));
			} else {
				pr[i] = pr[i - 1];
			}
		}
		R (i, K1.rt, 1) {
			if (rdf[i] <= n) {
				sf[i] = gtmn(sf[i + 1], Info(i, inf, D.g(rdf[i]), 0));
			} else {
				sf[i] = sf[i + 1];
			}
		}
		F (u, 1, n) {
			int col = D.g(u), v, lc;
			v = pre(dfn[u], col);
			while (v && Me.count(mp(u, rdf[v]))) {
				v = pre(v, col);
			}
			if (v) {
				v = rdf[v], lc = lca(u, v, 0);
				chk(out[col], mp(w1[lc], D.g(v)));
				chk(out[D.g(v)], mp(w1[lc], col));
			}
			v = suf(dfn[u], col);
			while (v != inf && Me.count(mp(u, rdf[v]))) {
				v = suf(v, col);
			}
			if (v != inf) {
				v = rdf[v], lc = lca(u, v, 0);
				chk(out[col], mp(w1[lc], D.g(v)));
				chk(out[D.g(v)], mp(w1[lc], col));
			}
		}
		F (i, 1, n) {
			if (D.g(i) != i || !out[i].se) {
				continue;
			}
			D.m(i, out[i].se, out[i].fi);
		}
	}
}

void solve() {
	cin >> n >> m;
	lg[1] = 0;
	F (i, 2, 2 * n - 1) {
		lg[i] = lg[i >> 1] + 1;
	}
	F (i, 1, m) {
		int u, v, w;
		cin >> u >> v >> w;
		e[i] = E(u, v, w), ed[i] = mp(u, v);
		Me[mp(u, v)] = Me[mp(v, u)] = 1;
	}
	sort(e + 1, e + m + 1, [](E &x, E &y) {
		return x.w < y.w;
	});
	K1.i();
	F (i, 1, m) {
		int u = e[i].u, v = e[i].v, w = e[i].w;
		K1.m(u, v, w, 0);
	}
	dfs1(K1.rt, 0);
	F (j, 1, lg[K1.rt]) {
		F (i, 1, K1.rt - (1 << j) + 1) {
			f[i][j] = gt(f[i][j - 1], f[i + (1 << (j - 1))][j - 1], 0);
		}
	}
	boruvka();
	sort(T.begin(), T.end(), [](E &x, E &y) {
		return x.w < y.w;
	});
	K2.i();
	for (E i : T) {
		K2.m(i.u, i.v, i.w, 1);
	}
	dfs2(K2.rt, 0);
	F (j, 1, lg[K2.rt]) {
		F (i, 1, K2.rt - (1 << j) + 1) {
			g[i][j] = gt(g[i][j - 1], g[i + (1 << (j - 1))][j - 1], 1);
		}
	}
	F (i, 1, m) {
		int u = ed[i].fi, v = ed[i].se;
		cout << w2[lca(u, v, 1)] << ' ';
	}
	cout << '\n';
	clr();
}

bool Med;
int main() {
	// FIO("");
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Mbe - &Med) / 1048576.0 << " MB\n";
	int T = 1;
	cin >> T;
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}
/*
求出原图的重构树，然后 Boruvka 求补图的最小生成树。

根据虚树的理论，$u$ 向 dfn 序前驱/后继连边，边权为最低的 lca 的权值。

同时要求颜色不同且原图中没有连边。

颜色不同可以通过求后缀最小/次小值和前缀最大/次大值解决，有连边就继续跳，均摊为 $O((n+m)\log n+\alpha n)$。
*/
```

---

## 作者：StayAlone (赞：0)

试图建出补图的最小生成树，这样查询两点的最短路就是查询两点的路径 $\max$。

考虑 Kruskal 的过程。从小到大加入边，对于原图，若要加入边 $(u, v, w)$，则在补图中， $u$ 所在连通块的点与 $v$ 所在连通块的点的距离均为 $w$。

同时发现，假如我们同时维护原图连通块和补图连通块，补图连通块一定是原图连通块的子集。因为若在原图不连通，补图中边权一定是后面加入的边权。

本质上，就是在维护原图最小生成树时，合理地找到补图的一些连通块合并。若恰当地启发式合并，复杂度就能做到 $\mathcal O(n\log n)$。

具体地，将补图连通块的点挂在一个代表元上，再将这些代表元挂在其原图连通块的代表元上。加入边 $(u, v, w)$ 时，找到 $u$ 连通块，找到 $v$ 连通块，直接暴力枚举二者内部补图连通块的点对，判断能否合并。只有边在原图中存在时不可合并，因此失败的次数为 $\mathcal O(m)$，加上判断边是否存在，复杂度为 $\mathcal O(m\log n)$。提前要对边排序，复杂度 $\mathcal O(m\log m)$。

总时间复杂度 $\mathcal O(m\log nm + n\log n)$。用 set 实现会多一个 $\log$。

```cpp
int n, m, ans[MAXN]; vector <int> lnk[MAXN], del;

il bool check(int x, int y) {
	auto it = lower_bound(begin(lnk[x]), end(lnk[x]), y);
	return it != lnk[x].end() && *it == y;
}

struct {
	int pa[MAXN];
	
	il void init() {
		rep1(i, 1, n) pa[i] = i;
	}
	
	il int fpa(int x) {
		return x ^ pa[x] ? pa[x] = fpa(pa[x]) : x;
	}
	
	il bool chk(int x, int y) {
		return fpa(x) == fpa(y);
	}
	
	il void merge(int x, int y) {
		pa[fpa(x)] = y;
	}
} O;
set <int> blk[MAXN], sub[MAXN];

struct {
	vector <pii> lnk[MAXN];
	int f[MAXN][20], mx[MAXN][20], dep[MAXN];
	
	il void clear() {
		rep1(i, 1, n) lnk[i].clear();
	}
	
	il void add(int x, int y, int w) {
		lnk[x].eb(y, w); lnk[y].eb(x, w);
	}
	
	il void init(int x, int p) {
		f[x][0] = p; dep[x] = dep[p] + 1;
		rep1(j, 1, 18) f[x][j] = f[f[x][j - 1]][j - 1], mx[x][j] = max(mx[x][j - 1], mx[f[x][j - 1]][j - 1]);
		for (auto [v, w] : lnk[x]) if (v ^ p) mx[v][0] = w, init(v, x);
	}
	
	il int query(int x, int y) {
		int ans = 0;
		if (dep[x] < dep[y]) swap(x, y);
		rep2(i, 18, 0) if (dep[x] - dep[y] >= 1 << i) gmax(ans, mx[x][i]), x = f[x][i];
		if (x == y) return ans;
		rep2(i, 18, 0) if (f[x][i] ^ f[y][i]) gmax(ans, max(mx[x][i], mx[y][i])), x = f[x][i], y = f[y][i];
		return max({ans, mx[x][0], mx[y][0]});
	}
} Q;

il int merge(int x, int y) {
	if (blk[x].size() > blk[y].size()) swap(x, y);
	for (auto p : blk[x]) blk[y].emplace(p);
	return blk[x].clear(), y;
}

il void mrgsub(int u, int v, int w) {
	u = O.fpa(u); v = O.fpa(v);
	if (sub[u].size() > sub[v].size()) swap(u, v);
	for (auto X : sub[u]) {
		del.clear(); int p = X;
		for (auto Y : sub[v]) {
			for (auto x : blk[p]) {
				bool flg = 0;
				for (auto y : blk[Y]) if (!check(x, y)) {
					flg = 1; p = merge(p, Y);
					del.eb(Y); Q.add(x, y, w);
					break;
				}
				if (flg) break;
			}
		}
		for (auto Y : del) sub[v].erase(Y);
		sub[v].emplace(p);
	} O.merge(u, v); sub[u].clear();
}

struct edge {
	int x, y, w, id;
	
	il void input() {
		read(x, y, w);
		lnk[x].eb(y); lnk[y].eb(x);
	}
	
	il bool operator < (const edge &p) const {
		return w < p.w;
	}
} a[MAXN];

int main() {
	for (int T = read(); T--; ) {
		read(n, m); O.init(); Q.clear();
		rep1(i, 1, n) lnk[i].clear(), sub[i].clear(), sub[i].emplace(i), blk[i].clear(), blk[i].emplace(i);
		rep1(i, 1, m) a[i].input(), a[i].id = i;
		rep1(i, 1, n) sort(begin(lnk[i]), end(lnk[i]));
		sort(a + 1, a + 1 + m);
		rep1(i, 1, m) if (!O.chk(a[i].x, a[i].y)) mrgsub(a[i].x, a[i].y, a[i].w);
		Q.init(1, 0);
		rep1(i, 1, m) ans[a[i].id] = Q.query(a[i].x, a[i].y);
		rep1(i, 1, m) printf("%d ", ans[i]); puts("");
	}
	return 0;
}
```

---

## 作者：Petit_Souris (赞：0)

带 data structure tag，难度先 -400，然后就会做了。

整个问题思考的过程是很套路化的。首先拿到手看到瓶颈路问题，先建出 Kruskal 重构树，这样两点间路径的最长边最短路就是 LCA 的点权。

接下来我们要对补图也求瓶颈路，希望求出补图的 Kruskal 重构树。但是边数是 $\mathcal O(n^2)$ 的，不能直接建出边，因此我们不妨退一步，转而求最小生成树，再在最小生成树上做路径最值查询。

稠密图的最小生成树问题直接上 Boruvka 算法，现在梳理一下每轮合并我们需要做什么：要对每个点找到与他不在同一连通块内的、原图中没有边相连的，瓶颈路最小的点，也就是找到与之 LCA 最深的点。由经典结论，我们知道这个点一定是当前点在 dfs 序上的前驱后继中的一个。

考虑如何维护这件事情。一个简单的想法是建立一个 set，每次枚举一个连通块，把对应点从 set 中临时删除，对于每个点做一次二分，如果二分到的点和当前点有连边就继续向前 / 向后找，计算完后再把所有点加回去。单轮的复杂度是 $\mathcal O((n+m)\log n)$ 的，因为失配次数不超过 $2m$。

还能再进一步吗？发现二分其实是无意义的，因为我们完全可以预处理出所有的同连通块连续段，并对每个点维护前后两个指针，表示当前正在考虑的备选前驱 / 后继。每次出现原图中连边的点就将指针前移，如果出现同连通块的点就直接跳过这一段连续段，也容易均摊分析出 $\mathcal O(n+m)$ 的复杂度（需要用 $\mathcal O(n\log n)-\mathcal O(1)$ LCA）。

求出最小生成树之后就是个简单的路径 max 查询问题了，可以倍增或者用你喜欢的其他做法。

注意判有无边如果用 map 复杂度将退化到 $\mathcal O(n\log ^2n)$，因此可以用哈希表保证复杂度为 $\mathcal O(n\log n)$。总复杂度为 $\mathcal O(n\log n\alpha(n))$，瓶颈在于并查集。

细节比较多，且有点卡常。

```cpp
#include<bits/stdc++.h>
typedef int ll;
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
const ll N=2e5+9,INF=2e9;
ll T,n,m,tot,fa[N*2],wp[N*2],id[N*2];
ll pre[N],suf[N],rev[N],w[N],npre[N],nsuf[N];
ll dfn[N*2],tim,ord[N*4],dep[N*2],fir[N*2];
ll dep2[N],fa2[20][N],st[20][N],lc[22][N*4],lg[N*4];
struct Edg{
    ll u,v,w;
}e[N*2];
vector<ll>to[N*2],vec[N];
vector<pii>to2[N];
unordered_map<long long,ll>mp;
struct Node{
    ll a,b,c;
    bool operator<(const Node&q)const{return a<q.a;}
}mn[N];
pii qq[N];
ll find(ll x){
    return id[x]==x?x:id[x]=find(id[x]);
}
void dfs1(ll x,ll f){
    dep[x]=dep[f]+1,dfn[x]=++tim,ord[tim]=x,fir[x]=tim;
    for(ll y:to[x]){
        if(y==f)continue;
        dfs1(y,x);
        ord[++tim]=x;
    }
}
void Init(){
    rep(i,2,tot*2)lg[i]=lg[i/2]+1;
    rep(i,1,2*tot-1)lc[0][i]=ord[i];
    rep(k,1,lg[2*tot-1]){
        rep(i,1,tot*2-(1<<k)){
            if(dep[lc[k-1][i]]<dep[lc[k-1][i+(1<<(k-1))]])lc[k][i]=lc[k-1][i];
            else lc[k][i]=lc[k-1][i+(1<<(k-1))];
        }
    }
}
ll LCA(ll x,ll y){
    x=fir[x],y=fir[y];
    if(x>y)swap(x,y);
    ll r=y,l=x;
    ll p=lg[r-l+1];
    if(dep[lc[p][l]]<dep[lc[p][r-(1<<p)+1]])return lc[p][l];
    return lc[p][r-(1<<p)+1];
}
ll Q(ll x,ll y){
    ll lca=LCA(x,y);
    return wp[lca];
}
void dfs3(ll x,ll f){
    fa2[0][x]=f,dep2[x]=dep2[f]+1;
    if(x==1)st[0][x]=INF;
    rep(i,1,18){
        fa2[i][x]=fa2[i-1][fa2[i-1][x]];
        st[i][x]=max(st[i-1][x],st[i-1][fa2[i-1][x]]);
    }
    for(pii e:to2[x]){
        ll y=e.first;
        if(y==f)continue;
        st[0][y]=e.second;
        dfs3(y,x);
    }
}
ll Query(ll x,ll y){
    if(dep2[x]<dep2[y])swap(x,y);
    ll d=dep2[x]-dep2[y],res=0;
    per(i,18,0){
        if((d>>i)&1){
            res=max(res,st[i][x]);
            x=fa2[i][x];
        }
    }
    per(i,18,0){
        if(fa2[i][x]!=fa2[i][y]){
            res=max({res,st[i][x],st[i][y]});
            x=fa2[i][x],y=fa2[i][y];
        }
    }
    if(x==y)return res;
    return max({res,st[0][x],st[0][y]});
}
long long C(ll x,ll y){return 1ll*x*(n+2)+y;}
void solve(){
    mp.clear();
    n=read(),m=read();
    rep(i,1,m)e[i].u=read(),e[i].v=read(),e[i].w=read();
    rep(i,1,m)qq[i]={e[i].u,e[i].v};
    rep(i,1,m)mp[C(e[i].u,e[i].v)]=mp[C(e[i].v,e[i].u)]=1;
    sort(e+1,e+m+1,[&](Edg a,Edg b){
        return a.w<b.w;
    });
    rep(i,0,n*2)to[i].clear(),to2[i].clear(),wp[i]=0,dep[i]=0;
    rep(i,0,19){
        rep(j,0,n+1)st[i][j]=fa2[i][j]=0;
    }
    iota(id+1,id+n+1,1);
    tot=n;
    tim=0;
    rep(i,1,m){
        ll u=e[i].u,v=e[i].v,w=e[i].w;
        if(find(u)==find(v))continue;
        tot++;
        to[tot].push_back(find(u));
        to[tot].push_back(find(v));
        id[find(u)]=id[find(v)]=id[tot]=tot;
        wp[tot]=w;
    }
    rep(i,0,tot+1)fa[i]=dep[i]=0;
    iota(id+1,id+n+1,1);
    dfs1(tot,0);
    Init();
    ll ec=0;
    rep(i,1,n)w[i]=i;
    sort(w+1,w+n+1,[&](ll x,ll y){
        return dfn[x]<dfn[y];
    });
    w[0]=w[n+1]=0;
    rep(i,1,n)rev[w[i]]=i,npre[i]=i-1,nsuf[i]=i+1;
    pre[0]=0,suf[n+1]=n+1;
    while(ec<n-1){
        rep(i,1,n)mn[i]=(Node){INF,0,0},vec[i].clear();
        rep(i,1,n)vec[find(i)].push_back(i);
        rep(i,1,n){
            if(find(w[i-1])==find(w[i]))pre[i]=pre[i-1];
            else pre[i]=i-1;
        }
        per(i,n,1){
            if(find(w[i+1])==find(w[i]))suf[i]=suf[i+1];
            else suf[i]=i+1;
        }
        rep(i,1,n){
            if(find(i)==i){
                for(ll j:vec[i]){
                    ll rid=rev[j],p=npre[rid];
                    while(p>=1){
                        if(find(j)==find(w[p]))p=pre[p];
                        else if(mp.count(C(j,w[p])))p--;
                        else break;
                    }
                    if(p>=1)mn[i]=min(mn[i],(Node){Q(j,w[p]),j,w[p]});
                    npre[rid]=p;
                    p=nsuf[rid];
                    while(p<=n){
                        if(find(j)==find(w[p]))p=suf[p];
                        else if(mp.count(C(j,w[p])))p++;
                        else break;
                    }
                    if(p<=n)mn[i]=min(mn[i],(Node){Q(j,w[p]),j,w[p]});
                    nsuf[rid]=p;
                }
            }
        }
        rep(i,1,n){
            if(find(i)==i){
                ll j=mn[i].b,k=mn[i].c,w=mn[i].a;
                if(find(j)==find(k))continue;
                ec++;
                id[find(j)]=find(k);
                to2[k].push_back({j,w});
                to2[j].push_back({k,w});
            }
        }
    }
    dfs3(1,0);
    rep(i,1,m)write(Query(qq[i].first,qq[i].second)),putchar(' ');
    putchar('\n');
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    T=read();
    while(T--)solve();
    return 0;
}
```

---

## 作者：EuphoricStar (赞：0)

被一道题创了三天![](//图.tk/0)

---

我们先考虑如何求给定两点在原图的最短路。套路地，建出 Kruskal 重构树，最短路就是两点 $\text{LCA}$ 的权值。

对于在补图的最短路，我们希望如法炮制，建出补图的 Kruskal 重构树。但是由于边数太多无法跑 Kruskal。不妨退一步，建出补图的最小生成树，那么两点的最短路就是这两点在最小生成树上的简单路径的最大边权。

求一个稠密图的最小生成树，可以考虑 Boruvka 算法。其思想基于每个点的最短邻边一定在最小生成树上，流程是每轮对每个连通块找到一条连向另一连通块的最短边，然后合并两端点。因为每轮连通块数量至少减半，所以一共会进行 $O(\log n)$ 轮。

于是现在我们考虑对每个点 $u$，求出它连出去的最小出边，并且边的另一端点不和 $u$ 在同一连通块。我们不妨倍增找到 $u$ 在 Kruskal 重构树上的最浅祖先，使得它包含的所有叶子不是都和 $u$ 在同一连通块。

考虑把 Kruskal 重构树拍平到序列上，那么每个点的子树管辖 dfn 序在 $[l_i, r_i]$ 中的叶子。设 $f_i$ 为 $i$ 所在连通块的代表元，$g_i$ 为 dfn 序为 $i$ 的点，$d_i$ 为最大的 $j$ 使得 $\forall k \in [j, i], f_{g_k} = f_{g_i}$，也就是说 $g_{d_i - 1}$ 是 $i$ 在 dfn 序上往左第一个与 $g_i$ 不在同一连通块的点。

考虑倍增到 $u$ 的一个祖先 $v$ 后，如何判定 $v$ 子树管辖的叶子不是都和 $u$ 在同一连通块，并且如果这个条件满足，还要找到这样的一个叶子。如果 $g_{r_v}$ 不和 $u$ 在同一连通块，那么 $g_{r_v}$ 即为所求。否则，dfn 序在 $[d_{r_v}, r_v]$ 中的叶子都和 $u$ 在同一连通块，若 $d_{r_v} > l_v$，那么 $g_{d_{r_v} - 1}$ 即为所求，否则 $v$ 不满足条件。

但是有个问题，因为我们求的是补图的最小生成树，所以找到的边不能是原图上有的边。考虑判定 $v$ 是否满足条件时，对于所有 $u$ 在原图上连出去的边 $(u, w)$，$l_w$ 把 $[l_v, r_v]$ 分成了 $O(deg_u)$ 个小区间。因为 $O(\sum deg_u) = O(m)$，所以我们可以暴力找到 $O(deg_u)$ 个小区间，再按照上面的方法判定即可。

时间复杂度 $O(m (\log^2 n + \log m))$。

[code](https://codeforces.com/problemset/submission/1648/216520630)

---

