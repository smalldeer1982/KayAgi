# [BalticOI 2019] 山谷 (Day1)

## 题目背景

**译自 [BalticOI 2019](http://boi2019.eio.ee/tasks/) Day1 T3.** ***[Alpine valley](http://boi2019.eio.ee/wp-content/uploads/2019/04/valley.en_.pdf)***

## 题目描述

在阿尔卑斯山谷中，有 $N$ 个村庄，编号为 $1 \ldots N$，这些村庄通过 $N-1$ 条边连接起来，形成了一个树型结构。

虽然任意两个村庄间都能相互抵达，但路途花费的时间可能令人难以接受，尤其是当你想要购买一些生活必需品的时候——因为所有村庄中，只有其中 $S$ 个村庄有商店。

今年冬天，由于大雪的原因，情况变得更糟。因此，你需要到达 $E$ 号村庄——那里有连接山区和外界的唯一通道，亦或是在山谷中的商店里购买足够接下来几个月生活的物资。今天早上，你在收音机里听到了所有道路中有一条道路无法通行的消息，但是你并不知道具体是哪一条道路。

你现在想知道你和你的朋友是否可以离开山谷，如果不能离开，则需要知道你们离最近商店的距离。由于你还不知道哪条道路无法通行，并且你的朋友们居住在不同的村庄，因此你需要回答 $Q$ 组询问，每组询问给出一条被封锁的道路和你朋友所在村庄的位置。

## 说明/提示

### 样例解释 1

本样例对应下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/v6u2t5hk.png)

在该图（以及接下来一张图）中，用灰色标记的点为商店所在点，图上的边按照「编号 / 长度」的顺序进行标注。

### 样例解释 2

本样例对应下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/sdxj2iz6.png)

### 子任务

对于所有数据，均满足：$1 \leq S,E,A,B,C,I,R \leq N$，且 $1 \leq W \leq 10^9$。

各子任务的分值与数据规模如下：

- 子任务 1（9 分）：$1 \leq N \leq 100,1 \leq Q \leq 10000$，且所有道路均满足 $|A-B|=1$。
- 子任务 2（27 分）：$1 \leq N \leq 1000,1 \leq Q \leq 1000$。
- 子任务 3（23 分）：$1 \leq N \leq 10^5,1 \leq Q \leq 10^5$，且 $S=N$。
- 子任务 4（41 分）：$1 \leq N \leq 10^5,1 \leq Q \leq 10^5$。

## 样例 #1

### 输入

```
5 2 3 1
1 2 3
1 3 2
3 4 1
3 5 2
2
4
2 2
2 5
4 5```

### 输出

```
escaped
3
oo```

## 样例 #2

### 输入

```
10 2 5 4
7 2 3
4 8 3
9 10 1
6 7 3
9 2 3
10 1 2
8 2 2
5 2 1
3 8 2
8
7
2 1
1 5
8 4
6 2
7 7```

### 输出

```
8
escaped
escaped
escaped
0```

# 题解

## 作者：yangjintian (赞：13)

### [原题链接](https://www.luogu.com.cn/problem/P6227)

---

## 题目大意：

一颗 $N$ 个节点的以 $E$ 为根的树，每条边有权值 $W_i$，有 $S$ 个特殊点和 $Q$ 次询问。
每次询问第 $I$ 条边不能经过，并给定一个起点 $R$。

1.若能走到根节点，则输出 escaped。

2.若走不到根节点也走不到任意个特殊点，则输出 oo。

3.若走不到根节点但能走到特殊点，则输出最近特殊点的距离。

## 解题思路：

先给张图，方便理解（图很丑，看懂就行 QWQ）

![](https://cdn.luogu.com.cn/upload/image_hosting/k5v9ezv9.png)

---

我们设深度大的那个点为 $P$。

### 第一种情况输出 escaped ：

那就说明 $R$ 到 $E$ 的路没被断开，也就是 $R$ 不在 $P$ 的子树内，所以 $\operatorname{lca}(R , P) \ne P$。
$\,$

### 第二种情况输出 oo ：

到不了根节点且到不了特殊点，说明 $R$ 在 $P$ 的子树内，即 $\operatorname{lca}(R , P) = P$ 且 $P$ 的子树内（包含 $P$）没有商店。
$\,$

### 第三种情况：

到不了根节点，但能到特殊点。

找的特殊点的范围一定在 $P$ 的子树内,即 $\operatorname{lca}(R , P) = P$。

暴力 DFS 找复杂度是 $O(n^2)$ 的，考虑优化，这种树上问题的优化很多很多都是用**倍增**的。

注意到 $ans = \min(c[R] - c[i] + nearshop[i])$。

其中 $i$ 为 $R$ 的祖先（包括 $R$）,$c[i]$ 表示从 $i$ 到根节点的距离，$nearshop[i]$ 表示**子树内**离 $i$ 最近的特殊点的距离。

$c[R]$ 可以提出来，那只要倍增找最小的 $nearshop[i] - c[i]$ 就可以了。

我们可以设 $go[i][j]$ 表示从节点 $i$ 往上走 $2^j$ 步到的点，$f[i][j]$表示  $i$ ~ $go[i][j]$ 的所有节点中最小的 $nearshop[i] - c[i]$。

最终答案即为 $c[R]$ + 找到的最小 $nearshop[i] - c[i]$。

---

### 易错 or 代码中难理解的点（☆）
* 开 long long。
* 找最近特殊点必须只找**子树内**的，找外面的如果边被断开就没办法了，倍增的话就倍增到 $P$ 就行了。或者其实那个子树外的特殊点是合法的，但那下次往上跳的时候一定会统计到的。
* 当 $P = R$ 时，答案是不会更新的，所以手动判断一下。

---

## 代码实现（细节有点多，放注释里了，非常仔细的，看一看吧 QWQ）:


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int Num = 1e5 + 5;
int n, s, q, e;
int go[Num][20], dep[Num], u[Num], v[Num], shop_num[Num];
// shop_num[i] 表示i及i的子树内有多少商店 
ll c[Num], near_shop[Num], f[Num][20], p[Num]; //这几个都要开long long!!! 
//!!!只用统计子树内的最近商店，子树外的以后会统计到或根本用不到
bool mark[Num];
struct edge {
	int to;
	ll w;
};
vector<edge> g[Num];
inline ll read() {
	ll s = 0, f = 1; char c = getchar();
	while (c < '0' || c>'9') { if (c == '-')f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { s = s * 10 + c - '0'; c = getchar(); }
	return s * f;
}
void dfs_pretreat(int x, int fa) {   //pretreat  v.预处理
	go[x][0] = fa; dep[x] = dep[fa] + 1;
	if (mark[x])shop_num[x]++;
	for (int i = 0; i < g[x].size(); i++) {
		int t = g[x][i].to;
		if (t == fa)continue;
		c[t] = c[x] + g[x][i].w;
		dfs_pretreat(t, x);
		shop_num[x] += shop_num[t];
	}
}
void dfs_shop(int x, int fa) {
	if (mark[x])near_shop[x] = 0;
	for (int i = 0; i < g[x].size(); i++) {
		int t = g[x][i].to;
		if (t == fa)continue;
		dfs_shop(t, x);
		near_shop[x] = min(near_shop[x], near_shop[t] + g[x][i].w);
		//只找子树内的最近商店
	}
}
int lca(int x, int y) {
	if (dep[x] < dep[y])swap(x, y); //让x成为深度大的点
	for (int i = 18; i >= 0; i--)if (dep[go[x][i]] >= dep[y])x = go[x][i];
	for (int i = 18; i >= 0; i--)if (go[x][i] != go[y][i])x = go[x][i], y = go[y][i];
	return (x == y) ? x : go[x][0];
}
void solve(int I, int R) {
	if (dep[u[I]] < dep[v[I]])swap(u[I], v[I]);
	int point = u[I];
	int LCA = lca(R, point);
	if (LCA != point) {  //escaped 优先级大于 oo
		cout << "escaped\n";
		return;
	}
	if (LCA == point && shop_num[point] == 0) {
		cout << "oo\n";
		return;
	}
	ll ans = (ll)0x3f3f3f3f3f3f, pos = R;
	for (int i = 18; i >= 0; i--) {
		if (dep[go[pos][i]] >= dep[point]) {
			ans = min(ans, f[pos][i]);  //先更新再跳
			pos = go[pos][i];
		}
	}
	if (point == R)ans = near_shop[R] - c[R]; //往上跳不了时
	cout << ans + c[R] << endl;
}
int main() {
	n = read(), s = read(), q = read(), e = read(); //e是根节点
	for (int i = 1; i < n; i++) {
		u[i] = read(), v[i] = read();
		int w = read();
		g[u[i]].push_back(edge{ v[i],w });
		g[v[i]].push_back(edge{ u[i],w });
	}
	for (int i = 1; i <= s; i++)mark[read()] = 1;
	dfs_pretreat(e, e);   //e是根节点
	memset(near_shop, 0x3f, sizeof(near_shop)); //要设为无穷大!!!
	dfs_shop(e, e);		  //!!!只用统计子树内的最近商店，子树外的以后会统计到
	for (int t = 1; t <= 18; t++)
		for (int i = 1; i <= n; i++)
			go[i][t] = go[go[i][t - 1]][t - 1];
	for (int i = 1; i <= n; i++)p[i] = near_shop[i] - c[i];  
	//p临时存一下，因为f[i][t]需要表示走2^t步 
	for (int i = 1; i <= n; i++)f[i][0] = min(p[i],p[go[i][0]]);
	//如果i为商店,f[i][0]不需要置为0!!!
	for (int t = 1; t <= 18; t++)
		for (int i = 1; i <= n; i++)
			f[i][t] = min(f[i][t - 1], f[go[i][t - 1]][t - 1]);
	//找c[R] + min{ near_shop[i] - c[i]  }  i∈子树 v[I]
	//f[i][j] 表示在 i ~ go[i][j] 这些点中， (near_shop[]-c[]) 最小是多少(典型倍增思想)，最后加上c[R]就为最终answer
	while (q--) {
		int a = read(), b = read();
		solve(a, b);
	}
	return 0;
}
```

---

[推荐一些树上问题的有意思的题目QWQ](https://www.luogu.com.cn/training/348760)

---

## 作者：Zimo_666 (赞：8)

### P6227 [BalticOI 2019 Day1] 山谷

### Description

给一棵树，一个根，一些特殊补给点，一些询问。求解如下问题：断掉一条边 $u\to v$，这样以后你能否从给定的 $R_i$ 走到根，若能输出 `escaped`。不能到达根且不能到达任何一个特殊补给点输出 `oo`。若不能到达根但可以到达特殊补给点输出边权和最小值。

### Solution

我们考虑断边 $u\to v$ 之后的情形，为方便描述我们设 $fa_v=u$。

我们考虑不能从给定的 $R_i$ 走到根的情况，即 $\operatorname{LCA}(v,R)= v$ 时，则我们有如果能走到根，则必有 $\operatorname{LCA}(v,R)\ne v$，则第一种情况解决完毕。

下面考虑设 $\_shop_i$ 表示 $i$ 及 $i$ 的子树内特殊补给点的个数，可以考虑使用 dfs 进行预处理，那么不能到达根且不能到达任何一个补给点的充要条件为 $\operatorname{LCA}(v,R)=v$ 且 $\_shop_v=0$。

最后考虑最难的一种情况，即不能到达根但可以到达特殊补给点。设 $dis_i$ 表示编号为 $i$ 的点到根的边权和，设到达的最近特殊补给点编号为 $id$，设 $R$ 和 $id$ 的 $\operatorname{LCA}$ 为 $\_lca$ ，设这个 $\operatorname{LCA}$ 到 $id$ 的距离为 $W_{\_lca}$，则我们有 $Ans=dis_R-dis_{\_lca}+W_{\_lca}$。我们考虑复杂度瓶颈，即不能暴力枚举所有 $v$ 子树内的点作为 $\operatorname{LCA}$，则我们考虑倍增优化。

设 $f_{i,j}$ 表示编号为 $i$ 的点向上跳 $2^j$ 步范围内最近的满足上段条件的 $\operatorname{LCA}$ 所产生的贡献 $-dis_{\_lca}+W_{\_lca}$。则我们有如果该点为特殊补给点则 $f_{i,0}=0$。而后我们考虑预处理 $f_{i,j}=\min(f_{i,j-1},f_{fat_{i,j-1},j-1})$。

每次询问枚举跳 $2^j$ 步，每次如果 $dep_{fat_{x,j}}\ge dep_v$（即不能跳出被截断的子树）就继续往上跳找答案，即 $res=\min(res,f_{x,j})$，最后 $ans=\min(ans,f_{v,0})$。别忘了这时的 $ans$ 不是最终答案，需要 $Ans=ans+dis_R$。得出最后的 $Ans$。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,s,q,e;
const int N=2e5+7;
vector<pair<int,int> > G[N<<1];
int top[N<<1];
int fa[N<<1],bgs[N<<1],dep[N<<1],siz[N<<1];
int U[N<<1],V[N<<1],W[N<<1];
int shop[N<<1];
int f[N][30];
int _shop[N<<1];
int fat[N][30];
int dis[N];

void dfs(int x,int fat){
	if(shop[x]) f[x][0]=0;
	_shop[x]=shop[x];
  dep[x]=dep[fat]+1;
  fa[x]=fat;siz[x]=1;
  for(auto it:G[x]){
    int k=it.first,w=it.second;
    if(k!=fat){
    	dis[k]=dis[x]+w;
      dfs(k,x);
      f[x][0]=min(f[x][0],f[k][0]+w);
      _shop[x]+=_shop[k];
      siz[x]+=siz[k];
      if(siz[k]>siz[bgs[x]]) bgs[x]=k;
    }
  }
}

void DFS(int x,int fat,int tp){
  top[x]=tp;
  if(bgs[x]){
  	DFS(bgs[x],x,tp);
  }
  for(auto it:G[x]){
    int k=it.first;
    if(k!=fat&&k!=bgs[x]) DFS(k,x,k);
  }
}

int lca(int x,int y){
  while(top[x]^top[y]) dep[top[x]]>dep[top[y]]?x=fa[top[x]]:y=fa[top[y]];
  return dep[x]<dep[y]?x:y;
}

void work(int I,int R){
	int u=U[I],v=V[I];
	if(fa[v]!=u) swap(u,v);
	if(lca(v,R)!=v) return printf("escaped\n"),void();
	if(lca(v,R)==v&&_shop[v]==0) return printf("oo\n"),void();
	int x=R;
	int res=0x3f3f3f3f3f3f3f3fll;
	for(int j=18;j>=0;j--){
		if(dep[fat[x][j]]>=dep[v]){
			res=min(res,f[x][j]);
			x=fat[x][j];
		}
	}
	res=min(res,f[v][0]);
	res+=dis[R];
	printf("%lld\n",res);
}

void debug(){
	for(int i=1;i<=n;i++) printf("%lld ",dis[i]);
	puts("");
}

signed main(){
	memset(f,0x3f,sizeof f);
	scanf("%lld%lld%lld%lld",&n,&s,&q,&e);
	for(int i=1;i<n;i++){
		int u,v,w;
		scanf("%lld%lld%lld",&u,&v,&w);
		G[u].push_back(make_pair(v,w)),G[v].push_back(make_pair(u,w));
		U[i]=u,V[i]=v,W[i]=w;
	}
	for(int i=1;i<=s;i++) {int pos;scanf("%lld",&pos);shop[pos]=1;}
	dfs(e,0),DFS(e,0,e);
	for(int i=1;i<=n;i++){
		f[i][0]-=dis[i];
	}
	for(int i=1;i<=n;i++) fat[i][0]=fa[i];
	for(int j=1;j<=18;j++){
		for(int i=1;i<=n;i++){
			fat[i][j]=fat[fat[i][j-1]][j-1];
			f[i][j]=min(f[i][j-1],f[fat[i][j-1]][j-1]);
		}
	}
	for(int i=1;i<=q;i++) {int I,R;scanf("%lld%lld",&I,&R),work(I,R);}
}
```

---

## 作者：NashChen (赞：5)

# 【题意简述】

给你一棵有 $N$ 个点，根为 $E$ 的树，标记树上共 $S$ 个节点。

处理 $Q$ 组询问 $(I,R)$：当边 $I$ 被删去时，判断点 $R$ 属于以下哪一种情况

1. 有一条到根的路径，输出 `"escaped"`

2. 没有到根的路径，但能到达被标记的点，输出到**最近的**有标记的点的距离

3. 既没有到根的路径，也没有到任意一个有标记的点的路径，输出 `"oo"`

# 【解题思路】

设被删掉的边 $I$ 的两个节点为 $u,v$，不妨设 $fa[v]=u$

边I被删掉，对整棵树的影响是 $v$ 的子树从原来的树上被分离出来

### 第1问

$R$ 与根连通，当且仅当 $R$ 不在 $v$ 的子树里。

利用已有的操作来表达，就是

$$LCA(v,R)\not=v$$

### 第3问

$R$ 既没有到根的路径，也没有到任意一个被标记的点的路径，当且仅当 $v$ 的子树里没有点被标记，且 $R$ 在 $v$ 的子树里

在dfs建立起有根树结构的时候，预处理出每个点的子树里的标记个数。设 $v$ 的子树内标记个数为 $shop[v]$。这一问的判断式就是

$$LCA(v,R)=v,\text{且} shop[v]=0$$

### 第2问

排除第1问和第3问之后，$R$ 一定在 $v$ 的子树内。

设点 $u$ 到子树上最近的被标记的节点的距离为 $f[u]$，有

$$f[u]= \begin{cases}
0 && u\text{有标记}\\
\min\{f[v]+weig[e]\mid v\in son(u)\} && u\text{无标记}
\end{cases}$$

显然，离 $R$ 最近的有标记点的距离，只会出现在 $min\{f[u]\mid u\in path(v,R)\}$ 里

假设我们要求的目标点为 $x$ 。设 $dis[i]$ 为 $i$ 到根的距离，则

$$\begin{aligned}
Ans&=dis[x]+dis[R]-2\times dis[LCA(x,R)]\\
&=(dis[x]-dis[LCA(x,R)])-dis[LCA(x,R)]+dis[R]\\
&=f[lca(x,R)]-dis[lca(x,R)]+dis[R]\\
&=min\{f[i]-dis[i]\mid i\in path(v,R)\}+dis[R]
\end{aligned}$$

设

$$val[i]=f[i]-dis[i];$$

我们只需要预处理出每个节点 $i$ 的 $val[i]$，并且树链剖分维护最小值，对于每个询问，查询

$$min\{val[i]\mid i\in path(v,R)\}$$

就可以得到答案

$$min\{val[i]\mid i\in path(v,R)\}+dis[R]$$

# 【代码】

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXV= 100005;
const long long INF= 1234567890123456ll;
	
int N,S,Q,E,orig[MAXV<<1],targ[MAXV<<1],nex[MAXV<<1],head[MAXV],cur;
long long weig[MAXV<<1];

int fa[MAXV],dep[MAXV],siz[MAXV],shop[MAXV];
int wson[MAXV],topfa[MAXV],dfn[MAXV],dfsclk=0;
long long Segtree[MAXV<<2],f[MAXV],dis[MAXV];

long long Query(int a,int b,int k,int l,int r){
	if(a<=l && r<=b) return Segtree[k];
	if(b<l || r<a) return INF;
	int mid= (l+r)>>1;
	long long v1= Query(a,b,k<<1,l,mid);
	long long v2= Query(a,b,k<<1|1,mid+1,r);
	return min(v1,v2);
}

void Update(int a,long long c,int k,int l,int r){
	if(a<l || r<a) return;
	if(l==r){
		Segtree[k]= c;
		return;
	}
	int mid= (l+r)>>1;
	Update(a,c,k<<1,l,mid);
	Update(a,c,k<<1|1,mid+1,r);
	Segtree[k]= min(Segtree[k<<1],Segtree[k<<1|1]);
	return;
}

long long TQuery(int a,int b){
	long long res= INF;
	while(topfa[a]!=topfa[b]){
		if(dep[topfa[a]]>dep[topfa[b]]) swap(a,b);
		res= min(res,Query(dfn[topfa[b]],dfn[b],1,1,N));
		b= fa[topfa[b]];
	}
	if(dfn[a]>dfn[b]) swap(a,b);
	res= min(res,Query(dfn[a],dfn[b],1,1,N));
	return res;	
}

int lca(int a,int b){
	while(topfa[a]!=topfa[b]){
		if(dep[topfa[a]]>dep[topfa[b]])
			swap(a,b);
		b=fa[topfa[b]];
	}
	return (dep[a]<dep[b])?a:b;
}

void subdivtree(int u){
	dfn[u]= ++dfsclk;
	if(wson[u]) topfa[wson[u]]=topfa[u],subdivtree(wson[u]);
	for(int e=head[u];e;e=nex[e]){
		int v=targ[e];
		if(fa[u]==v || v==wson[u]) continue;
		topfa[v]= v;subdivtree(v);
	}
	return;
}

void buildtree(int u){
	if(shop[u]) f[u]= 0;
	siz[u]= 1;
	for(int e=head[u];e;e=nex[e]){
		int v= targ[e];
		if(v==fa[u]) continue;
		fa[v]= u;
		dep[v]= dep[u]+1;
		dis[v]= dis[u]+weig[e];
		buildtree(v);
		shop[u]+= shop[v];
		siz[u]+= siz[v];
		f[u]= min(f[u],f[v]+weig[e]);
		if(siz[wson[u]]<siz[v]) wson[u]=v;
	}
	return;
}

void AddEdge(int u,int v,int w){
	nex[++cur]= head[u];
	head[u]= cur;
	orig[cur]= u;
	targ[cur]= v;
	weig[cur]= w;
	return;
}

void Input(){
	scanf("%d%d%d%d",&N,&S,&Q,&E);
	int x,y,c;long long z;
	for(int i=1;i<=N-1;++i){
		scanf("%d%d%lld",&x,&y,&z);
		AddEdge(x,y,z);
		AddEdge(y,x,z);
	}
	for(int i=1;i<=S;++i){
		scanf("%d",&c);
		shop[c]= 1;
	}
	return;
}

int main(){
	Input();
	for(int i=1;i<=N;++i)
		f[i]=INF;
	buildtree(E);
	topfa[E]= E;
	subdivtree(E);
	for(int i=1;i<=N;++i) Update(dfn[i],f[i]-dis[i],1,1,N);
	while(Q--){
		int I,R;
		scanf("%d%d",&I,&R);
		int u= orig[I<<1],
			v= targ[I<<1];
		if(fa[u]==v) swap(u,v);
		if(lca(v,R)!=v) puts("escaped");
		else if(!shop[v]) puts("oo");
		else printf("%lld\n",TQuery(R,v)+dis[R]);
	}
	return 0;
}
```

---

## 作者：hsfzLZH1 (赞：4)

### 题目大意

给定一棵 $n$ 个结点的树和一个结点 $e$ ，其中有 $s$ 个结点有商店， $q$ 次询问，每次询问给出一个编号 $I$ 和结点 $R$ ，切断编号为 $I$ 的边后，若 $R$ 与 $e$ 连通，输出 `escaped` ；若不连通，输出 $R$ 与最近的有商店结点的距离，若没有这样的结点，输出 `oo` 。

$1\le n,q\le 10^5$ 

### 解题思路

以 $e$ 为根建树。先判断切断 $I$ 后 $R$ 与 $e$ 是否连通。设 $I=(u,v)$ ，若 $u,v$ 同时是 $R$ 在树上的祖先，则切断后 $R$ 与 $e$ 不连通，否则一定连通。判断一个结点 $u$ 是否为 $R$ 的祖先，可以求 $LCA(u,R)$ ，若等于 $u$ 则 $u$ 为 $R$ 的祖先。

若不连通，则询问的就是 $R$ 与 **以 $u,v$ 中的儿子为根的子树** 中最近的有商店结点的距离，不妨设 $u,v$ 中的儿子为 $p$ 。

我们预处理出对于以每个结点 $x$ 为根的子树中，离 $x$ 最近的商店结点的距离 $v_x$ 。对于每次询问，我们要求的答案就是 $\min\{v_x+dist(R,x)\}$ ，其意义为 “从 $R$ 出发的路径，经过深度最浅的点就是 $x$ ，可以到达的最近的商店的距离，其中 $x$ 取遍树上 $R,p$ 两点之间路径上的点”。

维护树链信息，可以使用树链剖分。但是，本题需要维护的信息与询问点 $R$ 到树链上一点的距离有关，而这个询问点是不固定的。怎么办呢？观察到 $p$ 必是 $R$ 的祖先，链上任意两点都有祖先后代关系。设结点 $x$ 所在重链深度最深的结点为 $low(x)$ 。我们在线段树上维护的值是 $v_x+dist(x,low(x))$ 。设一条重链上 **查询的** 深度最浅的点为 $x$ ，深度最深的点为 $y$ ， $t$ 为任意结点，则因为 $low(t)=low(y)$ ，所以有

$v_t+dist(t,low(t))-dist(y,low(y))+dist(R,y)=v_t+dist(R,t)$ 

查询时，只需查询区间 $[x,y]$ 的最小值，减去 $dist(y,low(y))$ ，加上 $dist(R,y)$ ，就是这条重链的最小答案。

时间复杂度为 $O(n\log n)$ 。

### 参考代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define int long long
const int maxn=200010;
const int inf=2e18;
int n,s,q,e,cur,h[maxn],nxt[maxn],p[maxn],w[maxn],ans,bann;
int lg[maxn],fa[maxn][20],dep[maxn],dist[maxn],c[maxn],I,r;
int siz[maxn],son[maxn],cnt,dfn[maxn],rnk[maxn],top[maxn],v[maxn];
int low[maxn],val[maxn],minn[maxn*4];
struct Edge{int a,b,w;}edge[maxn];
bool tf[maxn];
void add_edge(int x,int y,int z)
{
	cur++;
	nxt[cur]=h[x];
	h[x]=cur;
	p[cur]=y;
	w[cur]=z;
}
void dfs(int x,int f)
{
	siz[x]=1;
	for(int j=h[x];j;j=nxt[j])if(p[j]!=f)
	{
		fa[p[j]][0]=x;dep[p[j]]=dep[x]+1;dist[p[j]]=dist[x]+w[j];
		dfs(p[j],x);
		siz[x]+=siz[p[j]];if(!son[x]||siz[son[x]]<siz[p[j]])son[x]=p[j]; 
	}
}
void dfs3(int x,int t)
{
	dfn[x]=++cnt;rnk[cnt]=x;top[x]=t;
	if(son[x])dfs3(son[x],t);
	for(int j=h[x];j;j=nxt[j])if(p[j]!=fa[x][0]&&p[j]!=son[x])dfs3(p[j],p[j]);
} 
int LCA(int x,int y)
{
	if(dep[x]<dep[y])swap(x,y);
	int k=dep[x]-dep[y];for(int j=lg[k];j>=0;j--)if(k&(1<<j))x=fa[x][j];
	if(x==y){return x;}
	k=dep[x];
	for(int j=lg[k];j>=0;j--)if(fa[x][j]!=fa[y][j])x=fa[x][j],y=fa[y][j];
	return fa[x][0];
}
int dis(int x,int y){int t=LCA(x,y);return dist[x]+dist[y]-dist[t]*2;}
void dfs2(int x,int fa,int d)
{
	if(tf[x])ans=min(ans,d);
	for(int j=h[x];j;j=nxt[j])if(p[j]!=fa&&p[j]!=bann)dfs2(p[j],x,d+w[j]);
}
void pre(int x,int fa)
{
	if(tf[x])v[x]=0;else v[x]=inf;
	for(int j=h[x];j;j=nxt[j])if(p[j]!=fa)
	{
		pre(p[j],x);
		v[x]=min(v[x],v[p[j]]+w[j]);
	}
}
#define lc (o<<1)
#define rc (o<<1|1)
void build(int o,int l,int r)
{
	if(l==r){minn[o]=val[l];return;}
	int mid=(l+r)>>1;
	build(lc,l,mid);build(rc,mid+1,r);
	minn[o]=min(minn[lc],minn[rc]);
}
int query(int o,int l,int r,int ql,int qr)
{
	if(l>qr||r<ql)return inf;
	if(ql<=l&&r<=qr)return minn[o];
	int mid=(l+r)>>1;
	return min(query(lc,l,mid,ql,qr),query(rc,mid+1,r,ql,qr));
}
main()
{
	scanf("%lld%lld%lld%lld",&n,&s,&q,&e);
	for(int i=1;i<n;i++)scanf("%lld%lld%lld",&edge[i].a,&edge[i].b,&edge[i].w),
	add_edge(edge[i].a,edge[i].b,edge[i].w),add_edge(edge[i].b,edge[i].a,edge[i].w);
	for(int i=1;i<=s;i++)scanf("%lld",c+i),tf[c[i]]=true;
	for(int i=2;i<=n;i++)lg[i]=lg[i/2]+1;
	dep[e]=1;dfs(e,-1);dfs3(e,e);
	for(int i=1;i<=lg[n];i++)for(int j=1;j<=n;j++)fa[j][i]=fa[fa[j][i-1]][i-1];
	pre(e,-1);
	int lst=1;
	for(int i=2;i<=n+1;i++)
	{
		if(top[rnk[i]]!=top[rnk[i-1]])
		{
			for(int j=lst;j<=i-1;j++)low[rnk[j]]=rnk[i-1],val[j]=v[rnk[j]]+dis(rnk[j],rnk[i-1]);
			lst=i;
		}
	}
	build(1,1,n);
	while(q--)
	{
		scanf("%lld%lld",&I,&r);
		if(LCA(edge[I].a,r)==edge[I].a&&LCA(edge[I].b,r)==edge[I].b)
		{
			int x=LCA(edge[I].a,edge[I].b);if(x==edge[I].a)x=edge[I].b;else x=edge[I].a;int y=r;
			int ret=inf,fx=top[x],fy=top[y];
			while(fx!=fy)
	    	{
	    		ret=min(ret,query(1,1,n,dfn[fy],dfn[y])-dis(low[y],y)+dis(r,y));y=fa[fy][0];
		    	fx=top[x];fy=top[y];
		    }
		    ret=min(ret,query(1,1,n,dfn[x],dfn[y])-dis(low[y],y)+dis(r,y));
		    if(ret>=1e18)printf("oo\n");
		    else printf("%lld\n",ret);
		}
		else printf("escaped\n");
	}
	return 0;
}
```

---

## 作者：Monomial (赞：3)

题意大致为在一棵树上每次删去一条边，询问钦定的根 $E$ 和给定的点 $R$ 是否连通，若不连通输出 $R$ 连通块内离 $R$ 最近的商店的距离。

这个问题看上去在线分类讨论的会有点多，我们考虑离线下来，这样分成两种情况。其中我们设删去的边 **深度较大** 的点为 $x$。

- $R$ 不在 $x$ 子树内

这种情况 $R$ 一定和 $E$ 连通。因为若 $R$ 不在 $x$ 子树内，那么 $x$ 必不是 $R$ 的祖先节点，删去的边就一定不在 $E$ 到 $R$ 的路径上。

- $R$ 在 $x$ 子树内

和上面类似，可得这种情况 $E$ 和 $R$ 不连通，$R$ 就相当于在以 $x$ 为根的子树中，这时我们就需要求这棵子树中离 $R$ 最近的商店的距离。那么可以不断换根。我们考虑用线段树配合 dfs 序维护节点深度，每次换根是只需要对其子树内的点深度 $-W$，子树外的 $+W$ 即可，这个是区间修改，时间复杂度 $\mathcal{O}(\log n)$，查询也只需要查原树 $x$ 的子树内最小深度即可，这个也是 $\mathcal{O}(\log n)$ 的。

注意非商店的点的深度初始化时要赋成尽量大的值。

总时间复杂度 $\mathcal{O}((n+q) \log n)$，可过。

---

## 作者：decoqwq (赞：3)

考虑题目的两问，第一问是删除一条边后某个点是否与一个定点联通，第二问是删除一条边后距离某一点最近的“标记点”，第一问显然可以让定点为根，求出全树 $\text{dfs}$ 序，如果查询点在删除的边中较深的点的子树中，那么一定是不联通的。

第二问考虑一个 $\text{dp}$，即一个点到其子树中最近标记点的距离，如果子树中没有标记点则为 $\inf$，容易得到 $f_u=\min\limits_{v\in son_u} (f_v+dis_{u,v})$，查询只需要查询当前点到删除边较深点上最小的 $f$，这个可以用倍增在 $O(nlogn)$ 的时间复杂度内维护。

总复杂度 $O(nlogn+qlogn)$

```cpp
/*  Never Island  */
/*deco loves Chino*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
struct edge
{
	int next,to,dis;
}e[200010];
int cnt,head[100010],n,q,s,ee,fa[100010][20],st[100010][20];
int in[100010],out[100010],val[100010],dep[100010];
int tx[100010],ty[100010],tot;
void add(int u,int v,int d)
{
	e[++cnt].to=v;
	e[cnt].next=head[u];
	e[cnt].dis=d;
	head[u]=cnt;
}
void dfs(int u)
{
	in[u]=++tot;
	for(int i=head[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==fa[u][0])
		{
			continue;
		}
		fa[v][0]=u;
		dep[v]=dep[u]+e[i].dis;
		dfs(v);
		val[u]=min(val[u],val[v]+e[i].dis);
	}
	out[u]=tot;
}
signed main()
{
	cin>>n>>s>>q>>ee;
	for(int i=1;i<n;i++)
	{
		int x,y,z;
		scanf("%lld%lld%lld",&tx[i],&ty[i],&z);
		add(tx[i],ty[i],z);
		add(ty[i],tx[i],z);
	}
	for(int i=1;i<=n;i++)
	{
		val[i]=1ll<<60;
	}
	for(int i=1;i<=s;i++)
	{
		int x;
		scanf("%lld",&x);
		val[x]=0;
	}
	dfs(ee);
	for(int i=1;i<=n;i++)
	{
		st[i][0]=val[i]-dep[i];
		if(i<n)
		{
			if(dep[tx[i]]<dep[ty[i]])
			{
				swap(tx[i],ty[i]);
			}
		}
	}
	for(int j=1;j<=18;j++)
	{
		for(int i=1;i<=n;i++)
		{
			fa[i][j]=fa[fa[i][j-1]][j-1];
			st[i][j]=min(st[i][j-1],st[fa[i][j-1]][j-1]);
		}
	}
	for(int i=1;i<=q;i++)
	{
		int x,y;
		scanf("%lld%lld",&x,&y);
		if(in[tx[x]]<=in[y]&&in[y]<=out[tx[x]])
		{
			int ans=1ll<<60,qaq=y;
			for(int i=18;i>=0;i--)
			{
				if(dep[fa[qaq][i]]>=dep[tx[x]])
				{
					ans=min(ans,st[qaq][i]+dep[y]);
					qaq=fa[qaq][i];
				}
			}
			ans=min(ans,st[tx[x]][0]+dep[y]);
			if(ans==1ll<<60)
			{
				cout<<"oo\n";
			}
			else
			{
				cout<<ans<<"\n";
			}
		}
		else
		{
			cout<<"escaped\n";
		}
	}
	return 0;
}
```

---

## 作者：ln001 (赞：1)

## 题意：
给定一颗有边权的有根树，根为 $E$，给定 $S$ 个关键点。对于每个询问，**临时**断开指定的一条边，求从询问给出的点出发，**能否到达根**。若不能到达，则求出能走到的**距离该点最近的关键点**，**可能没有**能到达的关键点。

## 做法
对于断开的边，只**考虑深度较大的那个端点**，称其为 $y$，称询问中给出的起点为 $x$。

对于第一种情况，能到达根，即 $x$ 不在 $y$ 子树中。当且仅当 $x, y$ 两点的最近公共祖先不是 $y$，比较好做。

对于第三种情况，即不能到达根，也不能到达关键点，直接判 $y$ 子树中是否有关键点就行，显然此时 $x$ 在 $y$ 的子树中。

下文称 $len_{i, j}$ 表示 $i, j$ 两点的距离，令 $dep_i$ 等于 $len_{root, i}$。称 $shop_x$ 表示 $x$ 为根的子树中，距离 $x$ 最近的关键点与 $x$ 的**距离**。

假设 $x$ 能走到的距离最近的关键点为 $z$，有 $len_{x, z}$ 等于 $dep_x + dep_z - 2 \times dep_{lca(x, z)}$，分离出 $dep_x$，则 $z$ 满足 $dep_z - 2 \times dep_{lca(x, z)} = len_{z, {lca(x, z)}} - dep_{lca(x, z)}$ 最小。暴力的做法直接枚举 lca，$x, z$ 的最近公共祖先需要满足 $shop_{lca} - dep_{lca}$ 最小。$z$ 就是距离该 lca 最近的关键点。

可以用倍增优化。

---

## 作者：MspAInt (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P6227)

难度虚高。

显然以出口为根比较好处理，先预处理一遍倍增 LCA。

* `escaped`：断开的道路不在起点到出口的路径上，$P$ 表示断路两端深度较大的点，则 $\operatorname{lca}(R,P)\not=P$。
* `oo`：非 `escaped` 情况下（$\operatorname{lca}(R,P)=P$）$P$ 的子树内不存在商店。
* 最近商店距离：假设决定走到商店 $K$，$dis_u$ 表示 $u$ 到根节点的距离，则答案为 $dis_R-dis_{\operatorname{lca(K,R)}}+dis_K-dis_{\operatorname{lca(K,R)}}$，$dis_K-dis_{\operatorname{lca(K,R)}}$ 的最小值是可以预处理的，设为 $sp_{\operatorname{lca(K,R)}}$，则上式为 $dis_R-dis_{\operatorname{lca(K,R)}}+sp_{\operatorname{lca(K,R)}}=dis_R-(dis_{\operatorname{lca(K,R)}}-sp_{\operatorname{lca(K,R)}})$。括号里的东西用倍增预处理最大值即可最小化答案。

以上均可做到单次 $\log n$，记得开 `long long`。

代码中的变量名和题解中的含义可能不同。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct edge{int to,w;};
int n,m,q,rt,dep[N],f[N][18],X[N],Y[N];
bool shop[N];
long long dis[N],p[N][18],ped[N];
vector<edge>e[N];
void dfs1(int u){
    if(shop[u])dis[u]=0;else dis[u]=1e18;
    dep[u]=dep[f[u][0]]+1;
    for(int i=1;(1<<i)<dep[u];i++)f[u][i]=f[f[u][i-1]][i-1];
    for(auto x:e[u]){
        int v=x.to,l=x.w;
        if(v!=f[u][0]){
            f[v][0]=u;ped[v]=ped[u]+l;
            dfs1(v);
            dis[u]=min(dis[u],dis[v]+l);
        }
    }
    return;
}
void dfs2(int u){
    p[u][0]=ped[f[u][0]]-dis[f[u][0]];
    for(int i=1;i<=17;i++)p[u][i]=max(p[u][i-1],p[f[u][i-1]][i-1]);
    for(auto x:e[u])if(x.to!=f[u][0])dfs2(x.to);
    return;
}
int lca(int x,int y){
    if(dep[x]<dep[y])swap(x,y);
    for(int i=17;i>=0;i--)if(dep[f[x][i]]>=dep[y])x=f[x][i];
    if(x==y)return x;
    for(int i=17;i>=0;i--)if(f[x][i]!=f[y][i])x=f[x][i],y=f[y][i];
    return f[x][0];
}
long long query(int u,int top){
    int v=u;
    long long Max=-1e18;
    for(int i=17;i>=0;i--)if(dep[f[v][i]]>=dep[top])Max=max(Max,p[v][i]),v=f[v][i];
    return min(ped[u]-Max,dis[u]);
}
signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    scanf("%d%d%d%d",&n,&m,&q,&rt);
    for(int i=1,z;i<n;i++){
        scanf("%d%d%d",&X[i],&Y[i],&z);
        e[X[i]].push_back({Y[i],z});e[Y[i]].push_back({X[i],z});
    }
    memset(p,-0x7f,sizeof(p));
    for(int i=1,x;i<=m;i++)scanf("%d",&x),shop[x]=1;
    dfs1(rt);dfs2(rt);
    // for(int i=1;i<=n;i++)printf("%lld ",dis[i]);puts("");
    for(int i=1,k,c;i<=q;i++){
        scanf("%d%d",&k,&c);
        int pos=dep[X[k]]>dep[Y[k]]?X[k]:Y[k];
        if(lca(pos,c)!=pos)puts("escaped");
        else if(dis[pos]==1e18)puts("oo");
        else printf("%lld\n",query(c,pos));
    }
    // system("pause");
    return 0;
}
```

[record](https://www.luogu.com.cn/record/122189354)

---

## 作者：2huk (赞：1)

类似题是 [CF2033G](https://www.luogu.com.cn/problem/CF2033G)。[我的题解](https://www.luogu.com.cn/article/04w4e8nz)。这两道题思想几乎完全一样。

既然 $E$ 这个点这么特殊，不妨把 $E$ 定为这棵树的根。

断掉树边 $(fa_u, u)$ 后，$x$ **不**能到达根，等价于 $x$ 在 $u$ 的子树中，或者说 $lca(u,x)=u$。不满足这个的先判掉。

如果 $x$ 确实不能到达根，那么它能到达的点一定是 $u$ 的子树。于是问题变成了：

- 求 $u$ 的子树内，距离 $x$ 最近的 **关键点**（关键点就是题目中的商店，下同）。

这个答案有两种情况：在 $x$ 的子树内，和不在 $x$ 的子树内但在 $u$ 的子树内。对于前者，我们可以找到这颗子树内 **深度** 最小的点（这里深度指到根的边权和）。可以用 dfs 序拍到序列上然后 RMQ。

对于不在 $x$ 的子树内但在 $u$ 的子树内的情况，不妨枚举这个答案点和 $x$ 的 LCA。不妨令 $x \sim u$ 这条路径上的点分别是 $p_0,p_1,\dots,p_k$（$p_0=x,p_k=u$）。可以发现它们的 LCA 一定在 $p$ 中。

令 $f(x)$ 表示在 $\text{Subtree}(fa_u) / \text{Subtree}(u)$ 中的关键点到 $fa_x$ 的最近距离。其中 $\text{Subtree}(u)$ 表示 $u$ 所在的子树内的点的集合。

下面是一个例子，其中 $4,5$ 是关键点，$f(2)=+\infty,f(3)=4,f(4)=f(5)=0$。

![](https://cdn.luogu.com.cn/upload/image_hosting/ipt1n512.png)

不难发现答案为 $\min f(p_{i-1}) + dis(x,p_i)$。表示 $p_i$ 是 $x$ 和答案点的 LCA。$dis(i,j)$ 表示树上 $i \sim j$ 的边权和。

先考虑 $f(u)$ 怎么求。仍然是 dfs 序。令 $u$ 的子树的 dfs 序为 $[L_u,R_u]$。那么需要求的是 $[L_{fa_u},L_u+1]$ 和 $[R_u+1,R_{fa_u}]$ 中的深度的最小值。

然后考虑 $\min f(p_{i-1}) + dis(x,p_i)$ 怎么快速求。首先这个 $dis$ 可以差分，得到 $dis(1, x) + \min f(p_{i-1})-dis(1,p_i)$。而且 $p_i$ 是 $p_{i-1}$ 的父亲。于是我们令 $g(u) = f(u) - dis(1,fa_u)$。那么答案为 $dis(1,x) + \min_{i=0}^{k-1} g(p_i)$。

那么 $\min_{i=0}^{k-1} g(p_i)$ 怎么求？倍增即可。

代码太丑了不放了。

---

## 作者：xiao7_Mr_10_ (赞：0)

## 前言

距离上次写好题分享已经过了一个月了。

这次写是因为发现这个问题的思想很套路且比较实用。

题意：给你一颗 $n$ 个节点，根节点为 $rt$ 的树，带边权。其中，有 $m$ 个特殊点，$q$ 个询问。一条询问 $(id,u)$ 表示不经过第 $id$ 条边，起点为 $u$ 然后分析答案，格式如下：

1. 若能走到根节点，则输出 escaped。

2. 若走不到根节点也走不到任意个特殊点，则输出 oo。

3. 若走不到根节点但能走到特殊点，则输出**最近特殊点**的距离。

## Step 1 分析问题

先考虑答案是什么。

首先，为了下文叙述方便，我们设 $R$ 为第 $id$ 条边**深度较大**的那个点。

- 如果能走到根节点，说明 $u$ 并不在 $R$ 的子树中。也就是 $lca(u,R) \ne R$，此时属于情况 $1$。

- 如果不能走到根节点也不能走到任意特殊点，说明 $u$ 一定在 $R$ 的子树中。也就是 $lca(u,R) = R$，而且 $R$ 的子树中没有一个特殊点，此时属于情况 $2$。

考虑第 $3$ 种情况，如何快速预处理答案，一个直观的想法就是暴力搜索预处理然后 $O(nm)$ 的复杂度。但是这样有很多无效计算。

那我们不妨设 $g_{i}$ 为以 $i$ 为根的子树中的特殊点和 $i$ 的最小距离。然后考虑从 $u$ 开始一直跳跃到 $R$ 然后计入答案。为了方便计算，我们可以再预处理 $dis$ 数组表示节点 $u$ 离树的根节点的距离。

所以答案就可以表示为最小的 $dis_{u} - dis_{i}+g_{i}$。其中 $i$ 代表的是从 $u$ 至 $R$ 的路径上的点。注意，$u$ 和 $R$ 也**包括其中**。

## Step 2 算法实现

我们的目的是快速计算出这个值，显然我们可以通过树链剖分的方式快速查找链上的最小值，时间复杂度为 $O(n \log n^2)$。

但是注意到实际上链是不带修改的，所以可以用**倍增**的思想解决这个问题。

首先，我们发现实际上 $dis_{u}$ 是不变的，所以我们需要找到最小的 $g_{i}-dis_{i}$。将其看做树的点权，问题就变成了查一条链上的最小值。

所以，我们设 $f(i,j)$ 表示从 $i$ 点跳 $2^j$ 个祖先会跳到哪里。再设 $st(i,j)$ 表示从 $i$ 点跳 $2^j$ 个祖先的链上能够取得的最小的 $g_{i}-dis_{i}$。

转移也比较简单，令 $f(i,j-1)$ 为 $x$。

$f(i,j)=f(x,j-1)$。

$st(i,j)=\min(st(i,j-1),st(x,j-1))$。

最后统计答案即可。

## Step3 实现和一些细节

实际上实现的细节有很多，例如 $st(i,0)$ 的初始化需要将 $i$ 点的贡献也计算。

**注意**，有可能出现 $u = R$ 的情况，而此时我们并不会倍增的求解，所以我们要特判下。

时间复杂度是 $O((n+q) \log n)$ 的。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+5;
struct Point{
	int v,val;
};
vector <Point> e[N];
int n,m,q,root,g[N],st[N][20],logn,x,u,v,w,f[N][20],siz[N],de[N],dis[N],u1[N],v1[N];
bool vis[N];
void dfs(int u,int fa){
	de[u]=de[fa]+1;
	if(vis[u])siz[u]=1,g[u]=0;
	for(int i = 0;i < e[u].size();i++){
		int v=e[u][i].v;
		if(v==fa)continue;
		f[v][0]=u,dis[v]=dis[u]+e[u][i].val;
		dfs(v,u);
		g[u]=min(g[u],g[v]+e[u][i].val),siz[u]+=siz[v];
	}
}
int calc(int id){
	return g[id]-dis[id];
}
int lca(int x,int y){
	if(de[x]<de[y])swap(x,y);
	for(int i = 0,p = de[x]-de[y];p;i++,p>>=1)
		if(p&1) 
			x=f[x][i];	
	if(x==y)return x;
	for(int i = logn;i >= 0;i--)
		if(f[x][i]!=f[y][i])
			x=f[x][i],y=f[y][i];
	return f[x][0];
}
void work(int id,int y){
	u=u1[id],v=v1[id];
	if(de[u]<de[v])swap(u,v);
	int lca1=lca(u,y);
	if(lca1!=u){
		cout << "escaped\n";
		return;
	}
	if(lca1==u&&!siz[lca1]){
		cout << "oo\n";
		return;
	}
	int ans=1e18,now=y;
	for(int i = logn;i >= 0;i--)
		if(de[f[now][i]]>=de[u])
			ans=min(ans,st[now][i]),now=f[now][i];
	if(u==y)ans=calc(u);
	cout << ans+dis[y] << "\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> q >> root;
	logn=log2(n);
	for(int i= 1;i < n;i++){
		cin >> u >> v >> w;u1[i]=u,v1[i]=v;
		e[u].push_back((Point){v,w});
		e[v].push_back((Point){u,w});
	}
	for(int i = 1;i <= m;i++){
		cin >> x;
		vis[x]=1;
	}
	memset(g,0x3f,sizeof(g));
	dfs(root,root);
	for(int i = 1;i <= n;i++)st[i][0]=min(calc(i),calc(f[i][0]));
	for(int j = 1;j <= logn;j++){
		for(int i = 1;i <= n;i++){
			f[i][j]=f[f[i][j-1]][j-1];
			st[i][j]=min(st[i][j-1],st[f[i][j-1]][j-1]);
		}
	}
	for(int i = 1;i <= q;i++){
		cin >> u >> v;
		work(u,v);
	}
	return 0;
}
```

---

## 作者：cike_bilibili (赞：0)

# 题意
给定一棵树和一个出口 $e$，以及许多关键点 $s$，多次询问删除某条边后能否走到出口，或能否走到一个关键点，以及最短距离。

# 思路
## 走到出口
这个部分是比较好想的，我们可以以 $e$ 点为根建树，令删边靠下的点为 $p$，起点为 $d$，当且仅当 $d$ 点在 $p$ 点的子树内，即 $LCA(p,d)=p$ 时，不可到达出口。

## 走到商店

显然，如果 $d$ 点无法到达出口，即无法到达根节点时，$d$ 点必在 $p$ 点子树内。

考虑树形 DP，设状态 $f[i]$ 表示在 $i$ 点子树内离 $i$ 最近的商店距它的距离，则有：

$$ \begin{cases} f[i]=0 & i \in s \\ f[i]=\min(f[x]+len(i,x))& x \in son(i) \end{cases}$$

其中，$s$ 为商店的集合，$len(i,x)$ 表示点 $i$ 与点 $x$ 直接连接的边的长度，$son(i)$ 为 $i$ 点的儿子集合。 

DP 完毕后，考虑答案求解，设起点 $d$ 与点 $p$ 的路径上任意一点为点 $k$，则有 $ans=dis[d]-dis[k]+f[k]$，其中 $dis[x]$ 为点 $x$ 到根的距离，显然 $dis[d]$ 为定值，所以用 ST 表维护 $dis[k]-f[k]$ 的最大值即可。

# AC code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int ans=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		ans=(ans<<1)+(ans<<3)+ch-'0';
		ch=getchar();
	}
	return w*ans;
}
int n,s,q,e;
struct node{
	int to;
	int next;
	int w;
}ed[200005];
int cnt;
int h[100005];
int d[100005];
int D[100005][25];//st
void add(int x,int y,int val){
	ed[++cnt]={y,h[x],val};
	h[x]=cnt;
}
int dep[100005];
int dep_w[100005];
int f[100005][25];//st
bool sh[100005];
void dfs(int x,int fa){
	f[x][0]=fa;
	dep[x]=dep[fa]+1;
	for(int i=h[x];i;i=ed[i].next){
		int v=ed[i].to;
		if(v==fa)continue;
		dep_w[v]=dep_w[x]+ed[i].w;
		dfs(v,x);
	}
}
void init(){
	for(int j=1;j<=20;j++){
		for(int i=1;i<=n;i++){
	//		cout<<i<<' '<<j<<' '<<f[i][j]<<endl;
			f[i][j]=f[f[i][j-1]][j-1];
			D[i][j]=max(D[i][j-1],D[f[i][j-1]][j-1]);
		}
	}
}
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=20;i>=0;i--){
		if(f[x][i]&&dep[f[x][i]]>=dep[y])x=f[x][i];
	}
	if(x==y)return x;
	for(int i=20;i>=0;i--){
		if(f[x][i]&&f[y][i]&&f[x][i]!=f[y][i]){
			x=f[x][i];
			y=f[y][i];
		}
	}
	return f[x][0];
}
void dp(int x,int fa){
	if(sh[x])d[x]=0;
	for(int i=h[x];i;i=ed[i].next){
		int v=ed[i].to;
		if(v==fa)continue;
		dp(v,x);
		d[x]=min(d[x],d[v]+ed[i].w);
	}
}
int jump(int x,int p){
	int ans=dep_w[x]-d[x];
	for(int i=20;i>=0;i--){
		if(f[x][i]&&dep[f[x][i]]>=dep[p])ans=max(ans,D[x][i]),x=f[x][i];
	}
	return ans;
}
signed main(){
	n=read();
	s=read();
	q=read();
	e=read();
	memset(d,0x3f,sizeof d);
	for(int i=1;i<n;i++){
		int x=read(),y=read(),w=read();
		add(x,y,w);
		add(y,x,w);
	}
	dfs(e,0);
	
	for(int i=1;i<=s;i++){
		int x=read();
		sh[x]=1;
	}
	dp(e,0);
	for(int i=1;i<=n;i++){
		D[i][0]=dep_w[f[i][0]]-d[f[i][0]];
	}
	init();
	while(q--){
		int i=read(),dd=read();
		int u=ed[i*2-1].to,v=ed[i*2].to;
		int p=f[u][0]==v?u:v;
		if(LCA(p,dd)!=p){
			printf("escaped\n");
			continue;
		}
		if(d[p]>1e18){
			printf("oo\n");
			continue;
		}
		printf("%lld\n",dep_w[dd]-jump(dd,p));
	}
}
```


---

## 作者：EricWan (赞：0)

很有意思的题，模拟赛时被新初一做出来了（我初二，连部分分都不会），这题很有意思，但细节太多。

## Step 1

预处理 [LCA](https://www.luogu.com.cn/problem/P3379)，倍增真的在这题更好用（虽然我用 ST）。

## Step 2

预处理：

1. $\text{S}_i$ 记录子树内是否有商店；
2. $\text{L}_i$ 记录每个节点的子树内离那个节点最近的商店离它的距离。

## Step 3

将前面 Step 2 中的第二个进行倍增处理，设 $\text{anc}_{i,j}$ 为节点 $i$ 的 $j$ 级祖先（它是自己的 $0$ 级祖先，它的父亲是它的 $1$ 级祖先，以此类推）。并且设置 $\text{f}_{i,j}$ 为以 $\text{anc}_{i,2^{^j}}$ 为根的子树内距离 $i$ 最近的商店与 $i$ 的距离。

## Step 4

处理询问（设 $I$ 号道路连接 $X$ 与 $Y$，且 $Y$ 是 $X$ 的父亲）：

+ $\text{LCA}\big(X,R\big)\neq X$，说明可以逃走，输出 `escaped`；

+ $\text{LCA}\big(X,R\big)=X$，说明不可以逃走，再分两种情况：

	+ $\text{S}_X=\text{false}$，说明无法走到任何商店，输出 `oo`；
    
    + 通过 $\text{L}_R$ 和 $\text{f}$ 倍增求出结果。

---
总结一下，这题代码量很长而思维难度也不低，是个很有意思的题。~~而且出在模拟赛中一定很毒瘤（教练别骂我）。~~

---

## 作者：happybob (赞：0)

先考虑能否逃出。

我们不妨设删去的边的两点编号为 $u,v$，其中 $u$ 是 $v$ 的父亲。

容易发现当且仅当 $R$ 在 $v$ 的子树中时无法逃出，即 $R$ 和 $v$ 的 LCA 为 $v$。可以通过树剖等处理。

我们假设不能逃出，那么需要考虑能否到商店。因为已经无法逃出，那么 $R$ 可以走到 $v$ 的子树中的任意一个点。因此只需要处理 $c_u$ 表示以 $u$ 为根的子树中商店个数，那么只需要判断 $c_v$ 是否是正数即可。 

假设 $c_v > 0$，那么我们需要求到最近商店的距离。我们设 $f_u$ 表示 $u$ 到其子树中某个商店的最近距离，若没有商店，则 $f_u = \inf$。容易通过朴素的 DP 求出，即 $f_u = \min \limits_{j \in son_u} (f_j + w(u, j))$，$w$ 是边权。

考虑 $R$ 能到的商店，分为两部分，一部分是在 $R$ 子树内的，显然直接求 $f_R$ 即可。另一部分是在 $v$ 子树内，$R$ 子树外的。我们设 $k$ 为 $v \sim R$ 路径上的一个点，那么 $k$ 对答案的贡献是 $f_k + dis(k, R)$，$dis$ 是两点之间边权和。

不妨设 $d_u$ 表示 $u$ 到根节点的边权和，由于 $k$ 是 $R$ 的祖先，所以 $dis(k, R) = d_R - d_k$。贡献可转化为 $f_k - d_k + d_R$。容易发现 $d_R$ 不变。于是只需要求 $f_k - d_k$ 最小值即可。树剖维护，使用 ST 表可以做到 $O(n \log n)$。我的实现是 $O(n \log^2 n)$ 的线段树。

除此之外，也可以用线性 RMQ 和线性 LCA 的黑科技优化到 $O(n)$。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <climits>
using namespace std;

#define int long long

const int N = 1e5 + 5, INF = 1e15;

vector<pair<int, int> > G[N];

int n, s, q, e;
long long cnt[N], f[N], sum[N];
bool p[N];
long long val[N];
int U[N], V[N];

void dfs(int u, int fa, int v)
{
	sum[u] = sum[fa] + 1LL * v;
	cnt[u] = p[u];
	if (p[u])
	{
		f[u] = 0;
	}
	for (auto j : G[u])
	{
		if (j.first != fa)
		{
			dfs(j.first, u, j.second);
			cnt[u] += cnt[j.first];
			f[u] = min(f[u], f[j.first] + j.second);
		}
	}
}

class SegmentTree
{
public:
	struct Node
	{
		int l, r;
		long long minn;
	}tr[N << 2];
	void pushup(int u)
	{
		tr[u].minn = min(tr[u << 1].minn, tr[u << 1 | 1].minn);
	}
	void build(int u, int l, int r, long long* a)
	{
		tr[u] = { l, r, a[l] };
		if (l == r) return;
		int mid = l + r >> 1;
		build(u << 1, l, mid, a);
		build(u << 1 | 1, mid + 1, r, a);
		pushup(u);
	}
	long long query(int u, int l, int r)
	{
		if (tr[u].l >= l and tr[u].r <= r) return tr[u].minn;
		int mid = tr[u].l + tr[u].r >> 1;
		long long res = 1e18;
		if (l <= mid) res = query(u << 1, l, r);
		if (r > mid) res = min(res, query(u << 1 | 1, l, r));
		return res;
	}
};

class TreeCut
{
public:
	SegmentTree sgt;
	int id[N], sz[N], dep[N], fa[N], son[N], top[N], idx;
	long long na[N];
	void dfs1(int u, int f)
	{
		fa[u] = f;
		sz[u] = 1;
		dep[u] = dep[f] + 1;
		for (auto j : G[u])
		{
			if (j.first != f)
			{
				dfs1(j.first, u);
				sz[u] += sz[j.first];
				if (sz[son[u]] < sz[j.first]) son[u] = j.first;
			}
		}
	}
	void dfs2(int u, int tf)
	{
		top[u] = tf;
		id[u] = ++idx;
		na[idx] = val[u];
		if (!son[u]) return;
		dfs2(son[u], tf);
		for (auto j : G[u])
		{
			if (j.first != fa[u] && j.first != son[u]) dfs2(j.first, j.first);
		}
	}
	void Init()
	{
		dfs1(e, 0);
		dfs2(e, e);
		sgt.build(1, 1, n, na);
	}
	int LCA(int u, int v)
	{
		while (top[u] ^ top[v])
		{
			if (dep[top[u]] < dep[top[v]]) swap(u, v);
			u = fa[top[u]];
		}
		return (dep[u] < dep[v] ? u : v);
	}
	long long query(int u, int v)
	{
		long long res = 1e18;
		while (top[u] ^ top[v])
		{
			if (dep[top[u]] < dep[top[v]]) swap(u, v);
			res = min(res, sgt.query(1, id[top[u]], id[u]));
			u = fa[top[u]];
		}
		if (dep[u] < dep[v]) swap(u, v);
		res = min(res, sgt.query(1, id[v], id[u]));
		return res;
	}
}tc;

signed main()
{
	scanf("%lld%lld%lld%lld", &n, &s, &q, &e);
	f[n] = INF;
	for (int i = 1; i < n; i++)
	{
		f[i] = INF;
		int u, v, w;
		scanf("%lld%lld%lld", &u, &v, &w);
		G[u].emplace_back(make_pair(v, w));
		G[v].emplace_back(make_pair(u, w));
		U[i] = u, V[i] = v;
	}
	for (int i = 1; i <= s; i++)
	{
		int u;
		scanf("%lld", &u);
		p[u] = 1;
	}
	dfs(e, 0, 0);
	for (int i = 1; i <= n; i++)
	{
		val[i] = f[i] - sum[i];
	}
	tc.Init();
	while (q--)
	{
		int I, R;
		scanf("%lld%lld", &I, &R);
		int u = U[I], v = V[I];
		if (tc.fa[u] == v) swap(u, v);
		int lca = tc.LCA(R, v);
		if (lca != v)
		{
			printf("escaped\n");
		}
		else if (cnt[v] > 0)
		{
			long long va = tc.query(v, R);
			printf("%lld\n", va + sum[R]);
		}
		else
		{
			printf("oo\n");
		}
	}
	return 0;
}
```


---

