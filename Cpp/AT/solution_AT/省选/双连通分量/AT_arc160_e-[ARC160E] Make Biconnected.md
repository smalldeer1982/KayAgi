# [ARC160E] Make Biconnected

## 题目描述

给定一棵有 $N$ 个顶点的无向树 $G$。**$G$ 的所有顶点的度数都不超过 $3$。**  
顶点编号为 $1$ 到 $N$。边编号为 $1$ 到 $N-1$，第 $i$ 条边连接顶点 $u_i$ 和顶点 $v_i$。  
此外，每个顶点都有一个权值，第 $i$ 个顶点的权值为 $W_i$。

你可以在 $G$ 上添加 $0$ 条或多条边。若在顶点 $i$ 和顶点 $j$ 之间添加一条边，则需要花费 $W_i + W_j$ 的代价。

请输出一种添加边的方法，使得满足以下条件，并且总代价最小：

- $G$ 是二重顶点连通的。也就是说，对于 $G$ 中任意一个顶点 $v$，即使将 $v$ 及其所有相邻的边从 $G$ 中移除，$G$ 依然保持连通。

给定 $T$ 组测试数据，请分别输出每组的答案。

## 说明/提示

### 限制条件

- $1 \leq T \leq 2 \times 10^5$
- $3 \leq N \leq 2 \times 10^5$
- $1 \leq u_i, v_i \leq N$
- 输入给定的图是树
- 输入给定的图中所有顶点的度数不超过 $3$
- $1 \leq W_i \leq 10^9$
- $W_i$ 是整数
- 所有测试用例中 $N$ 的总和不超过 $2 \times 10^5$

### 样例解释 1

在第 $1$ 个测试用例中，连接顶点 $1$ 和顶点 $3$ 可以使 $G$ 满足题目要求。此时总代价为 $W_1 + W_3 = 2 + 5 = 7$。不存在总代价小于 $7$ 且满足条件的方案，因此这是最优解。  
在第 $2$ 个测试用例中，总代价为 $(W_7 + W_6) + (W_1 + W_5) = 1100000 + 10001 = 1110001$，这是最小的。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
3
2 3 5
1 2
2 3
7
1 10 100 1000 10000 100000 1000000
1 2
2 3
2 4
3 5
3 6
4 7```

### 输出

```
1
1 3
2
7 6
1 5```

# 题解

## 作者：Alan_Zhao (赞：9)

## 题解

首先，所有叶子节点一定需要选至少一次，因为如果有某个叶子没被选，那么与它相连的那个点就一定是割点。设叶子个数为 $k$，对 $k$ 的奇偶性分类讨论：

- 有偶数个叶子：一定能找到一个非叶子节点 $u$，使得以 $u$ 为根时，$u$ 的所有儿子的子树中叶子节点的个数都不超过 $\frac{k}{2}$。这样就一定能给每个叶子节点 $x$ 找到一个与它配对的叶子 $y$，使得 $\operatorname{LCA}(x,y)=u$。
- 有奇数个叶子：枚举一个叶子 $x$，对于剩下的 $k-1$ 个叶子用上述方法配对。考虑找到 $x$ 往上的第一个三度点 $v$，那么 $x$ 能和除了 $x\leadsto v$ 路径上的点以外的所有点配对。选取其中点权最小的即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define For(Ti,Ta,Tb) for(int Ti=(Ta);Ti<=(Tb);++Ti)
#define Dec(Ti,Ta,Tb) for(int Ti=(Ta);Ti>=(Tb);--Ti)
#define Debug(...) fprintf(stderr,__VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
using ll = long long;
const int N = 2e5 + 5;
int T, n, w[N], siz[N], mxsiz[N];
vector<int> e[N];
void DFS(int u, int fa) {
	siz[u] = (e[u].size() == 1);
	for (int v : e[u]) if (v != fa) {
		DFS(v, u);
		siz[u] += siz[v];
		mxsiz[u] = max(mxsiz[u], siz[v]);
	}
}
void GetLeaf(int u, int fa, vector<int>& leaf) {
	if (e[u].size() == 1) leaf.push_back(u);
	for (int v : e[u]) if (v != fa) GetLeaf(v, u, leaf);
}
int Min(int u, int v) {
	if (!u || !v) return u | v;
	return w[u] < w[v] ? u : v;
}
int mn[N];
void GetMin(int u, int fa) {
	mn[u] = u;
	for (int v : e[u]) if (v != fa) {
		GetMin(v, u);
		mn[u] = Min(mn[u], mn[v]);
	}
}
vector<int> cur{0};
int ansu, ansv;
ll ansval = 1e18;
void GetAns(int u, int fa, int dep, int mnu, int deep) {
	if (e[u].size() == 1) {
		ll val = w[Min(mnu, cur[deep - 1])];
		if (val < ansval) ansval = val, ansu = u, ansv = Min(mnu, cur[deep - 1]);
	}
	cur.push_back(Min(u, cur.back()));
	for (int v : e[u]) if (v != fa) {
		int mnv = mnu;
		for (int x : e[u]) if (x != v && x != fa) mnv = Min(mnv, mn[x]);
		GetAns(v, u, dep + 1, mnv, e[v].size() == 3 ? dep + 1 : deep);
	}
	cur.pop_back();
}
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> T;
	while (T--) {
		cin >> n;
		For(i, 1, n) cin >> w[i];
		For(i, 1, n - 1) {
			int u, v;
			cin >> u >> v;
			e[u].push_back(v), e[v].push_back(u);
		}
		DFS(1, 0);
		int rt = 0;
		For(i, 1, n) {
			mxsiz[i] = max(mxsiz[i], siz[1] - siz[i]);
			if (e[i].size() == 3 && mxsiz[i] <= siz[1] / 2) rt = i;
		}
		if (!rt) {
			For(i, 1, n) if (e[i].size() == 2 && mxsiz[i] <= siz[1] / 2) rt = i;
		}
		if (siz[1] % 2) {
			GetMin(rt, 0);
			GetAns(rt, 0, 1, 0, 1);
		}
		cout << (siz[1] + 1) / 2 << '\n';
		vector<vector<int>> leaf;
		for (int u : e[rt]) {
			vector<int> vec;
			GetLeaf(u, rt, vec);
			if (siz[1] % 2) {
				auto it = find(range(vec), ansu);
				if (it != vec.end()) vec.erase(it);
			}
			leaf.push_back(vec);
		}
		if (siz[1] % 2) cout << ansu << ' ' << ansv << '\n';
		auto Comp = [&](int x, int y) {
			return leaf[x].size() < leaf[y].size();
		};
		priority_queue<int, vector<int>, decltype(Comp)> q(Comp);
		For(i, 0, int(leaf.size()) - 1) q.push(i);
		while (1) {
			int i = q.top(); q.pop();
			int j = q.top(); q.pop();
			if (!leaf[i].size() && !leaf[j].size()) break;
			cout << leaf[i].back() << ' ' << leaf[j].back() << '\n';
			leaf[i].pop_back(), leaf[j].pop_back();
			q.push(i), q.push(j);
		}
		For(i, 1, n) e[i].clear(), mxsiz[i] = siz[i] = 0;
		ansval = 1e18, ansu = ansv = 0;
	}
	return 0;
}
```

---

## 作者：Schi2oid (赞：1)

### 题意简述 

给出一棵无向联通树，保证每个点的度数 $\le3$，点有点权，要求你加入若干条边，加入一条边的花费是其连接的两个点的点权之和。求最小花费，使得加完边后的整张图是点双连通的。

### 思路分析

称度数为 $1$ 的结点为叶子结点，那么所有叶子都应该至少被连边一次，故答案下界应为所有叶子的点权之和。对于叶子个数 $k$ 为偶数的情况，我们可以构造一种方案来达到此下界。具体来说，我们首先将所有叶子按照 dfs 序排列，分别称其为 $v_1,v_2,…,v_k$。$\forall i\in [1,\frac{k}{2}]$，在 $v_i$ 与 $v_{i+\frac{k}{2}}$ 之间连边。 

正确性证明：由于我们将叶子按照 $dfs$ 序排列，那么当我们删去图中某一点时，原树会被划分成 $d$ 棵子树（$ d\le3$），并且每棵子树所包含的叶子结点编号一定是连续的一段。

- $d=1$：显然成立；
- $d=2$：$(v_1,v_{1+\frac{k}{2}}),(v_{\frac{k}{2}},v_{k})$ 无法同时被割断，所以也成立；
- $d=3$：
  - 第二段和第三段之间有连边：说明第二段的左端点 $\le \frac{k}{2}$。此时 $(v_1,v_{1+\frac{k}{2}}),(v_{\frac{k}{2}},v_{k})$ 一定将第一段和第二、三段连接起来；
  - 第二段和第三段之间没有连边：说明第二段的左端点 $> \frac{k}{2}$。此时第一段中包含所有匹配对中的至少一个元素，故第一段与所有叶子联通。

证毕。

接下来考虑 $k$ 为奇数的情况。这意味着，除了所有叶子的点权之外，我们一定会至少再多花费一个点的点权。此时，考察全局点权最小的点，设其权值为 $w$，那么当前的下界就是所有叶子权值和加上 $w$。

首先，先抛开原问题，我们考虑如何连一条边，让一个叶子与其划分后形成的子树之外的部分相连。我们从这个叶子出发，每次向一个没有被经过过的点走去，直到我们发现接下来的一步有多个点可以走。那么，如果我们连的这条边所指向的结点是上述过程途经的点之一，将删去的点选择在这条边所指向的结点就可以割断这个叶子；但是如果指向的结点不是这些点之一，我们发现无论如何，这个叶子都不会被割断。

很自然地想到，如果存在一个叶子，全局点权最小点位于上述路径之外，我们就可以将这个与全局点权最小点连边，其余点套用上述 $k$ 为偶数的解法即可。由于这个叶子无论如何都不会被割断，而剩下的部分又是连通的，最终结果就一定是合法的。

考虑什么情况下，不存在这样的一个叶子。这意味着，全局点权最小点位于所有叶子的上述路径之上。也就是说，整张图形成一个类似菊花图的结构，由至多 $3$ 条链的一端交于同一点（这一点为全局点权最小点）构成。在这种情况下，我们发现反复花费 $w$ 且不使用其他点无法变成合法，且全局点权次小点一定可以与某个叶子相连，因此此时借助全局点权次小点一定是最优解。对于其余叶子，再套用上述 $k$ 为偶数的解法即可。

时间复杂度 $O(n)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int>edge[200005];
int w[200005];
int deg[200005];
int cnt[15];
int k=0,l[200005];
void dfs(int x,int f){
	if(edge[x].size()==1) l[++k]=x;
	for(int i=0;i<edge[x].size();i++){
		int v=edge[x][i];
		if(v==f) continue;
		dfs(v,x);
	}
}
bool dfs2(int x,int f,int p){
	if(deg[x]==3) return x==p;
	bool ret=(x==p);
	for(int i=0;i<edge[x].size();i++){
		int v=edge[x][i];
		if(v==f) continue;
		ret|=dfs2(v,x,p);
	}
	return ret;
}
int main(){
	int t,n,u,v;
	cin>>t;
	while(t--){
		scanf("%d",&n);
		k=0;
		for(int i=1;i<=n;i++) edge[i].clear();
		for(int i=1;i<=n;i++) deg[i]=0;
		memset(cnt,0,sizeof cnt);
		for(int i=1;i<=n;i++) scanf("%d",&w[i]);
		for(int i=1;i<n;i++){
			scanf("%d%d",&u,&v);
			edge[u].push_back(v);
			edge[v].push_back(u);
			deg[u]++;
			deg[v]++;
		}
		for(int i=1;i<=n;i++){
			if(deg[i]!=1){
				dfs(i,0);
				break;
			}
		}
		for(int i=1;i<=n;i++) cnt[deg[i]]++;
		if(k%2==0){
			printf("%d\n",k>>1);
			for(int i=1;i<=k>>1;i++) printf("%d %d\n",l[i],l[i+(k>>1)]);
		}
		else{
			int mn1=1000000001,mn2=1000000002,pos1=0,pos2=0;
			for(int i=1;i<=n;i++){
				if(w[i]<mn1) mn2=mn1,pos2=pos1,mn1=w[i],pos1=i;
				else if(w[i]<mn2) mn2=w[i],pos2=i;
			}
			printf("%d\n",(k+1)>>1);
			if(cnt[3]==1&&cnt[1]==3&&deg[pos1]==3){
				for(int i=1;i<=k;i++){
					if(!dfs2(l[i],0,pos2)){
						printf("%d %d\n",l[i],pos2);
						for(int j=i;j<k;j++) l[j]=l[j+1];
						break;
					}
				}
			}
			else{
				for(int i=1;i<=k;i++){
					if(!dfs2(l[i],0,pos1)){
						printf("%d %d\n",l[i],pos1);
						for(int j=i;j<k;j++) l[j]=l[j+1];
						break;
					}
				}
			}
			for(int i=1;i<=k>>1;i++) printf("%d %d\n",l[i],l[i+(k>>1)]);
		}
	}
	return 0;
}
```

---

## 作者：masterhuang (赞：0)

> 给你一棵由无向边组成的**二叉树**，树上每个点有权值 $w_i$ 。你可以把两个点之间连无向边，如果将 $u$ 与 $v$ 连边，代价是 $w_u + w_v$ 。 
>
> 请给出一种连边方式，使得连边后，图中去掉任何一个点仍然连通，即图是一个点双连通图。 在此基础上，你要使代价最小。
>
> $\sum n\le 2\times 10^5$​，多测

有点意思的**树论**题。

考虑所有叶子，一定要被连边连到，否则删其父亲就不行了。

于是如果叶子个数是偶数，我们**按照 dfs 序**依次配对即可。

即按 **dfs** 序排序完为 $a_{1},a_2,\cdots,a_{2n}$，匹配 $(a_{k},a_{k+n})$​ 即可。

---

否则一定有一个叶子连其他点（也可能是叶子）

考虑**按权值从小到大**，枚举这个其他点（可能是叶子）。

然后考虑它连哪些叶子是合法的。发现当且仅当它到叶子的路径上存在三度点（全是二度形成的单链和叶子显然不行）。

由于二叉树，此时容易注意到找不到合法叶子的点只有 $O(1)$ 个，于是直接枚举的时候 **dfs** 整棵树判断即可。

稍微用下基数排序啥的，复杂度显然能线性。

[record](https://atcoder.jp/contests/arc160/submissions/66686164)

---

## 作者：happybob (赞：0)

套路题。

根据经典结论，叶子数量为偶数时答案就是叶子点权和，容易证明下界，构造只需要求带权重心然后每次删最大的就行了。

叶子数量为奇数时，一个想法是删掉一个叶子然后做偶数的情况，再将这个叶子与剩余部分最小点连边。这个做法大致是对的，细节上有一些 corner 需要讨论，大概就是任意一个叶子的父亲都是二度点，删掉就会导致父亲变为叶子，处理方法也很简单，我们知道任意点双连通图可以被开耳分解构造，所以从某个叶子不断往上跳，直到第一个非二度点即可。具体地你需要考虑以每个点为根分别判断是否存在这样的叶子，但比较容易看出只有点权前 $O(1)$ 小的点作为根才有意义，所以复杂度是对的。

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc160_e)

**题目大意**

> 给一棵 $n$ 个点的二叉树，点有点权，加入一条边的代价时两端点点权和。
>
> 最小化加入边的代价和使得这张图变成点双连通图，给出构造。
>
> 数据范围：$n\le 2\times 10^5$。

**思路分析**

显然所有叶子都必须连一条边，否则删掉他的父亲就不连通了。

假设这棵树有偶数个叶子 $l_1\sim l_k$，我们可以把他们们两两匹配使得全图点双连通：

> 把叶子按 dfs 序排列，连接 $l_i,l_{i+k/2}$。
>
> 显然删掉一个点之后整棵树最多分成 dfs 序上的三个区间。
>
> 若分成区间数 $\le 2$ 时简单的。
>
> 否则讨论 $l_{k/2}$ 属于哪个区间，如果是第一个或第三个，那么这个区间和另外两个都连通。
>
> 如果在第二个区间，那么二三区间显然连通，并且第一个区间和 $l_{k/2+1}$ 连通，那么三个区间连通。

否则我们考虑给一个叶子和树上某个点连接，其他点用上述方式构造。

对于一个叶子 $x$，设他祖先里第一个三度点为 $p$，那么 $x\to p$ 的路径（包括 $p$）以外都合法。

那么我们可以用类似换根 dp 的方式求出删掉每个点的代价，选最小值即可。

时间复杂度 $\mathcal O(n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
vector <int> G[MAXN];
array <int,2> w[MAXN],f[MAXN],g[MAXN];
int deg[MAXN],lf[MAXN],k,id[MAXN];
void dfs1(int u,int fz) {
	if(deg[u]==1) lf[++k]=u,id[u]=k;
	f[u]=w[u];
	for(int v:G[u]) if(v^fz) dfs1(v,u),f[u]=min(f[u],f[v]);
	for(int i=0;i<(int)G[u].size();++i) if(G[u][i]==fz) {
		G[u].erase(G[u].begin()+i); break;
	}
}
void dfs2(int u,int fz,array<int,2> x,array<int,2> y) {
	//y: cur path, x: other subtree
	if(deg[u]==1) g[id[u]]=x;
	if(deg[u]==2) dfs2(G[u][0],u,x,min(y,w[u]));
	if(deg[u]==3) {
		dfs2(G[u][0],u,min({x,f[G[u][1]],y}),w[u]);
		dfs2(G[u][1],u,min({x,f[G[u][0]],y}),w[u]);
	}
}
void solve() {
	int n;
	scanf("%d",&n),k=0;
	for(int i=1;i<=n;++i) G[i].clear();
	for(int i=1;i<=n;++i) scanf("%d",&w[i][0]),w[i][1]=i;
	for(int i=1,u,v;i<n;++i) scanf("%d%d",&u,&v),G[u].push_back(v),G[v].push_back(u);
	int rt=0;
	for(int i=1;i<=n;++i) {
		deg[i]=G[i].size();
		if(deg[i]>=3) rt=i;
	}
	if(!rt) {
		puts("1");
		for(int i=1;i<=n;++i) if(deg[i]==1) printf("%d ",i);
		puts("");
		return ;
	}
	dfs1(rt,0);
	if(k%2==0) {
		printf("%d\n",k/2);
		for(int i=1;i<=k/2;++i) printf("%d %d\n",lf[i],lf[i+k/2]);
		return ;
	}
	printf("%d\n",(k+1)/2);
	dfs2(G[rt][0],rt,min(f[G[rt][1]],f[G[rt][2]]),w[rt]);
	dfs2(G[rt][1],rt,min(f[G[rt][2]],f[G[rt][0]]),w[rt]);
	dfs2(G[rt][2],rt,min(f[G[rt][0]],f[G[rt][1]]),w[rt]);
	int t=min_element(g+1,g+k+1)-g;
	printf("%d %d\n",lf[t],g[t][1]);
	for(int i=t+1;i<=k;++i) lf[i-1]=lf[i];
	--k;
	for(int i=1;i<=k/2;++i) printf("%d %d\n",lf[i],lf[i+k/2]);
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：FyFive (赞：0)

> 心态爆炸，赛后在 AT 上一题交了两面多……

#### 题意

给一棵树，每个点有点权，要连一些边，使得整棵树变成一个点双，每次连边的代价为两个端点的权值和，求最小的总代价，并输出方案。

#### 正文

如果不问方案而只问最小代价的话那简直不要太容易，丢到 ABC 去都行……

先考虑最小代价的值。

首先，每个叶子节点都要和其他点连边，也就是说对于最小代价，其值至少为树上叶子节点权值和。

接下来是构造出尽量接近最小值的连边方案，不难发现有以下两种情况。

令叶子节点个数为 $cnt$，

- 当 $cnt$ 为偶数时，将叶子两两配对即可；
- 否则，在两两配对之后，将剩下的一个叶子与权值尽量小的店连边。

考虑到连边之后整棵树要变成点双。也就是说，若定义一条新连的边，其端点在原树上的最短路径称之为这条边的原路径，那么对于所有的至少 $\displaystyle\frac{cnt}{2}$ 条原路径，不能存在某条原路径和其他原路径都没有交。

接下来考虑构造路径。

- 当 $cnt$ 为偶数时，只要保证所有的配对的点的 LCA 必定被其他原路径经过即可，不难发现只需要使相配对的点的欧拉序差值尽量大就行了。那么按照欧拉序将叶子节点存储到一个 $Leave$ 数组里，然后使 $Leave_i$ 与 $\displaystyle Leave_{i+\frac{cnt}{2}}$ 配对就行了；
- 当 $cnt$ 为奇数时，尝试将多出来的叶节点与权值最小的店连边。设权值最小的点是 $v$，第二小的是 $k$。
  - 如果 $v$ 本身就是叶节点，那么只需要让 $v$ 被连两次就行了。任选一个叶子节点 $l$，以 $l$ 为根以后当作偶数的情况连边，然后连接 $l$ 和 $v$ 即可。
  - 如果 $v$ 不是叶节点，那就找一棵 $v$ 的子树，如果子树内叶子数量大于 $1$，那么树内任意一个点与 $v$ 相连，剩下的按照偶数的方法连边即可。
  - 同时，如果只有三个叶子并且两两的 LCA 均为 $v$，此时是不能用 $v$ 连边的那么就用节点 $k$ 代替 $v$ 实现上述操作即可。

时间复杂度 $O(N)$。

#### 部分 Code
```cpp
...
void dfs(int nw,int fa)
{
    if(go[nw].size()<2&&fa) leaf[++onl]=nw;
    for(auto &u:go[nw])
    {
        if(fa==u) continue;
        dfs(u,nw);
    }
}
...
if(~ctt&1)
{
    onl=0; dfs(v,0); ctt>>=1; cout<<ctt<<endl;
    for(int i=1;i<=ctt;++i) cout<<leaf[i]<<' '<<leaf[i+ctt]<<endl;
    continue;
}
...
if(go[v].size()<2)
{
    for(int i=1;i<=n;++i) if(go[i].size()==1&&i!=v) k=i;
    onl=0; dfs(k,0); ctt>>=1; cout<<ctt+1<<endl<<k<<' '<<v<<endl;
    for(int i=1;i<=ctt;++i) cout<<leaf[i]<<' '<<leaf[i+ctt]<<endl;
}
else
{
    onl=0; ctt>>=1; cout<<ctt+1<<endl; bool ok=1;
    for(auto &u:go[v])
    {
        int on=onl;
        dfs(u,v);
        if(onl>on+1&&ok) ok=0,cout<<v<<' '<<leaf[onl--]<<endl;
    }
    for(int i=1;i<=ctt;++i) cout<<leaf[i]<<' '<<leaf[i+ctt]<<endl;
}
```

---

## 作者：xxxxxzy (赞：0)

这一场最弱智的题目。

看到要求形成点双，考虑把所有叶子提取出来考虑。

+ 有偶数个叶子：考虑把这些叶子两两相连，答案为 $\sum w_i$，需要把所有叶子按 $\text{dfn}$ 序排序，然后从 $i$ 叶子连往 $i + \dfrac{m}{2}$ 叶子，可以证明这样是对的。

+ 有奇数个叶子，枚举单独的叶子，剩下的按上面的方式算，发现单独的叶子可以连接到它祖先的第一个三度点以上的所有节点。

接下来就是实现问题，考虑先判断链，然后选取一个三度点做根节点。

对于奇数情况，会发现找到 $u$ 祖先的第一个三度点 $v$，$(u,v)$ 路径是一条单链。

用一个可重集先把所有点塞进去，然后暴力删除 $(u,v)$ 上的所有点，这么做复杂度是对的。

时间 $O(n \log n)$。

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
const i32 N = 5e5 + 5;
i32 n, rt, u, v, w[N], f[N];
vec G[N], L;
fv dfs2(i32 u, i32 fa) {
  f[u] = fa;
  if (G[u].size() == 1) L.pb(u);
  for (i32 v : G[u]) {
    if (v == fa) continue;
    dfs2(v, u);
  }
}
multiset <i32> S;
fn i32 qans(i32 u) {
  i32 x = u;
  while (G[x].size() < 3) S.erase(S.find(w[x])), x = f[x];
  S.erase(S.find(w[x]));
  i32 ans = *S.begin();
  x = u;
  while (G[x].size() < 3) S.insert(w[x]), x = f[x];
  S.insert(w[x]);
  return ans;
}
bool vis[N];
fv sol() {
  cin >> n;
  rep (i, 1, n) cin >> w[i], S.insert(w[i]), vis[i] = 0;
  rep (i, 1, n - 1) cin >> u >> v, G[u].pb(v), G[v].pb(u);
  rt = 0;
  rep (u, 1, n) if (G[u].size() >= 3) rt = u;
  if (!rt) {
    cout << "1\n";
    rep (i, 1, n) if (G[i].size() == 1) cout << i << " ";
    cout << "\n";
  } else {
    dfs2(rt, 0);
    if (L.size() & 1) {
      i32 sum = 0, tmp = 0, ans = 1e18, p = -1;
      for (i32 v : L) sum += w[v];
      for (i32 u : L) {
        i32 k = sum + qans(u);
        if (ans > k) ans = k, p = u;
      }
      cout << (L.size() + 1) / 2 << "\n";
      for (auto it = L.begin(); it != L.end(); it++) {
        if (*it == p) {
          L.erase(it);
          break;
        }
      }
      i32 sz = L.size();
      rep (i, 0, sz / 2 - 1) cout << L[i] << " " << L[i + (sz >> 1)] << "\n";
      cout << p << " ";
      i32 x = p;
      while (G[x].size() < 3) vis[x] = 1, x = f[x];
      vis[x] = 1;
      i32 mn = 1e18, pos = -1;
      rep (i, 1, n) if (!vis[i] && mn > w[i]) mn = w[i], pos = i;
      cout << pos << "\n"; 
    } else {
      i32 ans = 0, sum = 0;
      for (i32 v : L) ans += w[v];
      i32 sz = L.size();
      cout << (sz >> 1) << "\n";
      rep (i, 0, sz / 2 - 1) cout << L[i] << " " << L[i + (sz >> 1)] << "\n";
    }
  }
  rep (i, 1, n) G[i].clear();
  L.clear(); S.clear();
}
int main() {
//  IOS;
//  freopen("1.in", "r", stdin);
//  freopen("2.out", "w", stdout);
  i32 T = 1;
  cin >> T;
  while (T--) sol();
}
```

---

