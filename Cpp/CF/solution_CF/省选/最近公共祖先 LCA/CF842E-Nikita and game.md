# Nikita and game

## 题目描述

Nikita plays a new computer game. There are $ m $ levels in this game. In the beginning of each level a new class appears in the game; this class is a child-class of the class $ y_{i} $ (and $ y_{i} $ is called parent-class for this new class). Thus, the classes form a tree. Initially there is only one class with index $ 1 $ .

Changing the class to its neighbour (child-class or parent-class) in the tree costs $ 1 $ coin. You can not change the class back. The cost of changing the class $ a $ to the class $ b $ is equal to the total cost of class changes on the path from $ a $ to $ b $ in the class tree.

Suppose that at $ i $ -th level the maximum cost of changing one class to another is $ x $ . For each level output the number of classes such that for each of these classes there exists some other class $ y $ , and the distance from this class to $ y $ is exactly $ x $ .

## 样例 #1

### 输入

```
4
1
1
2
1
```

### 输出

```
2
2
2
3
```

## 样例 #2

### 输入

```
4
1
1
2
3
```

### 输出

```
2
2
2
2
```

# 题解

## 作者：skylee (赞：11)

# [CF842E]Nikita and game

### 题目链接：

[CF842E](http://codeforces.com/contest/842/problem/E)

### 博客地址：

[[CF842E]Nikita and game - skylee](https://www.cnblogs.com/skylee03/p/9081983.html)

### 题目大意：

一棵树初始只有一个编号为$1$的根结点。$n(n\le3\times10^5)$次操作，每次新增一个点作为$p_i$的子结点，询问更新后有多少点可以作为树直径的端点。

### 思路：

根据直径的一些性质，不难发现所有直径的相交部分一定是连续的一段。我们可以由此将所有可以作为端点的点分为三类：

1. 在连续段左边的点
2. 在连续段右边的点
3. 无所谓左边和右边的点（此时相交部分变成了一个点）

设集合$S_1$中为$1$类点，集合$S_2$中为$2$类点，而$3$类点归为其中任意一个集合都可以。不难发现，从$S_1,S_2$中分别随机选取一个点，两个点之间的路径一定是树的直径。

每次新加入一个点后，分别与$S_1$和$S_2$中任意一个点求距离，记为$d_1,d_2$。记当前树的直径为$maxd$，新加入的点为$i$。若$\max(d_1,d_2)>maxd$，则直径可以被更新。若$d_1$是新的$maxd$，则新的$S_2=\{i\}$。但原$S_2$中的元素并不一定全部失效，对于那些原本应当归为第$3$类的点$j$，若$dis(i,j)=d_1$，则将其归为$S_1$中。若$d_2$是新的$maxd$同理。

若$\max(d_1,d_2)=maxd$，将$i$加入到相应的点集即可。

点集$S_1,S_2$具有无序性，用`std::vector`即可实现（并不需要用`std::set`），插入和清空都是$\mathcal O(1)$，而LCA求距离时间复杂度$\mathcal O(\log n)$。总的时间复杂度为$\mathcal O(n\log n)$。而那些用`std::set`的虽然同样也是$\mathcal O(n\log n)$，但常熟要大不少，所以我的`std::vector`轻松跑到[Rank2](http://codeforces.com/contest/842/submission/38575307)，比那些`std::set`不知道快到哪里去了（Rank1手写数组）。

### 源代码：

```cpp
#include<cstdio>
#include<cctype>
#include<vector>
#include<algorithm>
inline int getint() {
	register char ch;
	while(!isdigit(ch=getchar()));
	register int x=ch^'0';
	while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
	return x; 
}
const int N=3e5+2,logN=19;
int dep[N],anc[N][logN];
inline int lg2(const float &x) {
	return ((unsigned&)x>>23&255)-127;
}
inline void add_vertex(const int &x,const int &par) {
	dep[x]=dep[anc[x][0]=par]+1;
	for(register int i=1;i<=lg2(dep[x]);i++) {
		anc[x][i]=anc[anc[x][i-1]][i-1];
	}
}
inline int lca(int x,int y) {
	if(dep[x]<dep[y]) std::swap(x,y);
	for(register int i=lg2(dep[x]-dep[y]);i>=0;i--) {
		if(dep[anc[x][i]]>=dep[y]) x=anc[x][i];
	}
	for(register int i=lg2(dep[x]);i>=0;i--) {
		if(anc[x][i]!=anc[y][i]) {
			x=anc[x][i];
			y=anc[y][i];
		}
	}
	return x==y?x:anc[x][0];
}
inline int dist(const int &x,const int &y) {
	return dep[x]+dep[y]-dep[lca(x,y)]*2;
}
std::vector<int> s1,s2;
int main() {
	add_vertex(1,0);
	s1.push_back(1);
	const int n=getint()+1;
	s1.reserve(n);
	s2.reserve(n);
	for(register int i=2,maxd=0;i<=n;i++) {
		add_vertex(i,getint());
		int d1=s1.empty()?0:dist(i,s1[0]);
		int d2=s2.empty()?0:dist(i,s2[0]);
		if(std::max(d1,d2)>maxd) {
			maxd=std::max(d1,d2);
			if(maxd==d1) {
				for(register int &x:s2) {
					if(dist(x,i)==d1) {
						s1.push_back(x);
					}
				}
				s2.clear();
			} else {
				for(register int &x:s1) {
					if(dist(x,i)==d2) {
						s2.push_back(x);
					}
				}
				s1.clear();
			}
		}
		if(std::max(d1,d2)==maxd) {
			(maxd==d1?s2:s1).push_back(i);
		}
		printf("%lu\n",s1.size()+s2.size());
	}
	return 0;
}
```



---

## 作者：suxxsfe (赞：8)

https://www.luogu.com.cn/problem/CF842E  

考虑树的直径有性质：当存在多条直径，若长度为偶数，则它们交于一点，且为直径中点；若长度为奇数，则交于中间那条边。  

于是记录下直径的中点（或中间那条边），同时对每个点维护到中点的距离  
那么查询的时候，答案就是这个距离的最大值个数。  
要是中间是边的情况，就对两个端点分别记录，拿最大值个数和次大值个数乘一乘大概就行。  
或者你再把每条边变成一个虚点。

然后加叶子，对于加的这个叶子的父亲，看一下是不是当前的最大值或次大值，根据当前直径长度的奇偶性讨论，要移动到旁边的点/边上。  
移动完信息的变更发现是先把某子树内的距离都减一，再把剩下部分都加一。  

然后这个东西dfs+线段树就完了，离线下把整个树建好搞 dfs 序，每次加叶子变成激活一个节点，而未激活的节点不允许标记推上去  


---

## 作者：Liuxizai (赞：3)

[My Blog](https://liuxizai.ac.cn/archives/solutions-2023-10.html#CF842E%20Nikita%20and%20game)

如果随便画出一棵树所有直径的形态，我们会发现所有直径一定会共用中点或中间的边，大多数时候直径会分成两个部分，每一部分产生若干分支，对应若干可行的直径端点，从两个部分分别任取端点都能组成一条直径。

这启发我们用两个 `std::vector` 分别维护这两个部分的直径端点，每次新增点时：

- Case 1. 若接在某个直径端点上，则直径长度增加，所在部分的直径端点全部失效，替换为这个新增的点；
- Case 2. 若不接在直径端点上，分别从两个部分任选端点计算距离，检查这个点能否成为直径端点，如果能的话应该被分在哪个部分。

这样有一个问题，直径长度为奇数时，直径中点可能能将所有直径分成三个及以上的部分，直接维护极其复杂。

一个好的方法是，仍然将直径端点划分到两个集合，每次发生 Case 1 时检查当前集合的点能否加入另一集合。

这种做法正确性显然，但时间复杂度并不明晰。

我们将两个集合称为「左集合」和「右集合」。上面所说的「部分」，明确的定义是在所有直径端点构成的虚树上，直径中点的一棵子树，接下来我们为了方便称这个结构为「块」。显然，在块中的某个直径端点下接一个新点会导致这个块变成一条链，其余的端点都会被删去。

我们要求，右集合中有且仅有一个块，而左集合中可以有多个块。在代码实现时，只要每次新增点时都优先加入左集合即可。如果真的任意在左右集合中加点，复杂度会退化（[link](https://www.luogu.com.cn/discuss/706926)）。

这样，如果在左集合中加点，该点所在的块变为一条链，其余左集合中的块被删去或加入右集合，并且，由于直径中点的移动，所有块加入右集合后会合并为一个块。如果在右集合中加点，右集合直接变为一条链，不会发生直径端点在集合间的转移。

这样，每个直径端点至多只会被转移一次，总复杂度视求 lca、算距离的方式不同为 $O(m)$ 或 $O(m\log m)$。

[Submission #227813933](https://codeforces.com/contest/842/submission/227813933)

---

## 作者：critnos (赞：1)

某个点能否成为直径端点当且仅当他距离某个直径端点距离为直径。加入某个点时，如果直径不变则只有这个点可能被加入答案集合。如果直径增加则会删除答案集合中某些点。

所以每个点对答案的贡献是个区间，直接二分即可。

---

## 作者：N1K_J (赞：1)

非常好的题目，是我的大脑旋转。（

## 思路

因为看到很多题解这一部分证明不太详细，所以准备完整写一遍。

首先，注意到直径的性质：

> 若一个树有多条直径，那么这些直径的中间（可能是一个点，可能是一条边）必然想通

证明请见 [OI-Wiki](https://oi-wiki.org/graph/tree-diameter/#%E6%80%A7%E8%B4%A8)

那么可以注意到的是，一个树上所有直径的端点一定分别在这个点或线的两侧，我们不妨分别用集合 $s$ 与集合 $t$ 记录。

另外，我们维护树直径的长度 $d$。

下面，考虑新加入一个点：

首先，可以发现 $s$ 与 $t$ 中的点分别在直径中间的两侧，就像这样：



若新加入的点 $id$ 使得直径边长，不妨设 $id$ 在原直径中间靠 $s$ 的一侧，显然，另一点一定是 $t$ 中的点。

下给出证明：

若另一点 $id_0 \notin s$ 且 $id_0 \notin t$，则一定存在 $t$ 中一点使 $dis(x,id)>dis$，否则不符合 $t$ 的定义

若另一点 $id_0 \in s$，则原直径长度 $<$ 原直径中间到 $s$ 中一点的距离 $+1$。这相当于 $t$ 是空集（这一定不成立）或 $t$ 中任意一点到直径中点距离为 $1$，那么有：$s,t$ 中任意一点到直径中点距离为 $1$。

这个图就是一个菊花图，新加入一个点需是直径中点的子节点，但这样不会改变直径（还是 $2$）。矛盾

综上得证

因此，新加入一点后，将这一点与 $s$ 中任意一点，$t$ 中任意一点计算距离，查看是否大于 $d$。

若大于，不放设 $id$ 在 $s$ 一侧，只要将 $s$ 中的数检查一遍，看一下会不会距离 $id$ 也为新直径，是就丢到 $t$。反之同理。

接下来考虑不变，这一部分就很简单了，如果 $id$ 到 $t$ 中一点距离为 $d$，将 $id$ 加入 $s$，反之同理。

考虑到题目所求，输出 $s$ 和 $t$ 的大小之和就可以。

## 细节

写到这里基本可以开始写代码了，但是还是有两个很容易错细节：

1. 如果 $id$ 到 $s,t$ 中一点距离都是 $d$ 怎么办？

第一次写很容易把 $id$ 既加入 $s$ 又加入 $t$。这样一来，输出时相当于 $id$ 被算了两次。所以这种情况随便加一个就好。

2. 怎么交上去的输出和我本地不一样？

这是因为 [未定义行为](https://www.luogu.com.cn/blog/StudyingFather/undefined-behavior)。

> CF 上的 c++14 是 32 位，c++20 是 64 位。 vector 的 size 是 32 位整数，在 32 位机子下用 lld 输出会有问题。

因此，如果你用 `%lld` 输出 `vector.size()`，应当换为 `%d` 或 c++20 提交。

## 代码实现

计算两个点之间的距离可以用倍增 LCA。

```cpp
//c++20
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 300010;
ll n;
vector<ll> s,t;
ll anc[N][30],dep[N];
ll d = 0;
void add(ll id,ll fa){
	anc[id][0] = fa;dep[id] = dep[fa]+1;
	for(ll j = 1; (1<<j)<=dep[id]; j++){
		anc[id][j] = anc[anc[id][j-1]][j-1];
	}
}
ll lca(ll u,ll v){
	if(dep[v]>dep[u]) swap(u,v);
	for(ll j = 25; j >= 0&&dep[u]>dep[v]; j--){
		if((1<<j)<=dep[u]&&dep[u]-(1<<j)>=dep[v]) u = anc[u][j];
	}
	//u = v;
	if(u==v) return u;
	for(ll j = 25; j >= 0; j--){
		if((1<<j)>dep[u]) continue;
		if(anc[u][j]!=anc[v][j]) u = anc[u][j],v = anc[v][j];
	}
	return anc[u][0];
}
ll dis(ll x,ll y){
	return dep[x]+dep[y]-2*dep[lca(x,y)];
}
int main(){
	scanf("%lld",&n);
	dep[1] = 0;
	s.push_back(1);
	for(ll id = 2; id <= n+1; id++){
		ll u;
		scanf("%lld",&u);
		add(id,u);
		ll dis1 = 0,dis2 = 0;
		if(!s.empty()) dis1 = max(dis1,dis(id,s[0]));
		if(!t.empty()) dis2 = max(dis2,dis(id,t[0]));
		if(dis1>d||dis2>d){
			d = max(dis1,dis2);
			if(d==dis1){
				for(auto v : t){
					if(dis(id,v)==d) s.push_back(v);
				}
				t.clear();
				t.push_back(id);
			} else if(d==dis2){
				for(auto v : s){
					if(dis(id,v)==d) t.push_back(v);
				}
				s.clear();
				s.push_back(id);
			}
		} else {
			if(dis1==d) t.push_back(id);
			else if(dis2==d) s.push_back(id);//要else，不然会算重（只要是否存在这个端点，无论放在s还是t不会影响后面的计算） 
		}
		printf("%lld\n",s.size()+t.size());
	}
	return 0;
}
```



---

## 作者：RDFZchenyy (赞：0)

### 题意简述

一棵树初始只有一个编号为 1 的根结点。

$n$ 次操作，每次新增一个点作为 $p_i$ 的子结点，询问更新后有多少点可以作为树直径的端点。

$n\le3\times10^5$。

> 请注意：这里提供的方法是暴力方法，不是主流方法。

### 提示

什么时候直径的长度会变化？什么时候直径的长度不会变化？这启发我们什么？

### 答案

直径的长度会变化当且仅当将一个节点接到了加之前为直径的一个节点下方，其他时候直径的长度不会变化。

直径的长度变化时，可能的点集即变为当前点和与其相距最远的点构成的集合。

直径的长度不变化时，只**可能**新增加一个点，就是新接进的点。

据此，题目转化为设计一种数据结构，使得支持新接入一个点，支持查询到某一个点距离最远的点的个数。

### 解法分析

按照提示，我们接下来只需要设计一种数据结构。

我们考虑暴力地向上跳父节点，然后统计不是从本子树的父亲节点的子树内的最大深度，这明显无法通过本题。

我们考虑到希望跳父节点的次数尽可能少，于是建立点分树。

> 注：这可能也可以使用树链剖分解决。

接下来问题变为对于每个节点，维护一些可重集，每次询问所有可重集除去其中一个可重集的并的最大值及其出现次数。

由于最大值类信息不具有可加性，考虑将每个节点的子结点当成一个序列并编号。

使用线段树维护这个序列，然后每次合并除去的节点的左右两个区间，得到答案。

实际实现时，将整棵点分树标号后存到一起即可。

线段树维护复杂度 $O(\log n)$，点分树暴力跳 $O(\log n)$ 层。

综合复杂度 $O(n\log^2n)$，分析可以通过，实际在略微卡常数（将 `vector<int>` 全部使用邻接表/普通数组替换后）即可通过本题。

### 示例代码

见云剪切板，链接：<https://www.luogu.com.cn/paste/cr85uf3o>

---

## 作者：Mirasycle (赞：0)

我们要维护的就是支持动态加叶子节点的树的直径端点。

一个很显然的思路就是提前建立整颗树，然后预处理一下以便后面可以快速查询两点距离。然后动态加点删点，维护直径集合。类比结论：到树上某点距离最远的点一定是直径端点之一。我们可以得到，到新加入叶子节点最远的点也是直径端点之一。

于是不断 $\operatorname{check}$，新入叶子节点无法构成直径端点直接舍弃。如果可以成直径端点，且直径长度不变就直接加入集合中。如果长度增加就舍弃那些不能与该叶子节点构成新直径的端点。这样子时间复杂度是 $O(n^2)$ 的。

观察到上述做法复杂度高的原因是可能出现多条直径/直径端点。于是这里要用到一个很关键的性质:
> 树的所有直径必定交于一点/一条边。

这条性质提供了一个让我们把直径端点划分的基础。

### 中心为边

假设目前是交于一条边，那么我们只需要维护这条边两端的直径端点集合，分别记为 $L,R$。

每次 $\operatorname{check}$ 的时候直接从 $L,R$ 两个集合中分别任选一点算距离即可。

然后选择是否加入对应的 $L/R$ 集合内即可。遇到接到了 $L/R$ 集合端点的情况，我们直接舍弃整个集合即可。

### 中心为点
但是当交点是一个点的时候就很难办了，因为会出现不止两个集合。

但是其实如果算叶子到某直径端点的距离，两个集合还是可以用的。因为叶子必然只能在一个子树内，而两个集合肯定会分出至少两个子树。

可以这个删除就难办了，考虑新来了一个叶子节点接在了某个直径上，和它同一集合的可能会舍弃，也可能可以构成直径。不能暴力 $\operatorname{check}$ 吧。

有一个很神仙的做法就是，观察到在中心为点的情况下我们如果往一个直径端点上加点，直径必然会移动到一条边上(具体来说就是往该子树的边上移动)。此时又会变成严格两个集合。于是我们每次加点都往 $L$ 内加点，保持 $R$ 是一个完整的子树内的点。然后当 $R$ 内被接上了一个点，那么我们直接舍弃 $R$ 即可。如果 $L$ 上被接上了一个点，那么我们可以暴力 $\operatorname{check}$ 是否舍弃，还是保留。根据上面的观察，保留之后的点必然会从 $L$ 集合迁移至 $R$ 集合。而如果 $R$ 集合不符合要求是直接会被舍弃的，所以综上每个点只会被 $\operatorname{check}$ 至多一次(也就是迁移那次)。

注意我们并不需要维护中心具体在哪，因为点和边的做法可以统一。

所以时间复杂度 $O(n\log n)$，瓶颈在于求 lca。


```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define fi first
#define se second
#define make_pair mp
using namespace std;
typedef long long ll;
const int maxn=3e5+10;
const int maxlog=20;
void chkmax(int &x,int y){ x=x>y?x:y; }
void chkmin(int &x,int y){ x=x<y?x:y; }
vector<int> G[maxn],L,R; int n;
struct LCA{
	int dfn[maxn],pa[maxlog][maxn];
	int dep[maxn],lg[maxn],tot=0;
	void dfs(int u,int father){
		pa[0][dfn[u]=++tot]=father; dep[u]=dep[father]+1;
		for(auto v:G[u]) 
			if(v!=father) dfs(v,u);
	}
	int cmp(int x,int y){ return dfn[x]<dfn[y]?x:y; }
	int lca(int u,int v){
		if(u==v) return u;
		u=dfn[u]; v=dfn[v];
		if(u>v) swap(u,v);
		u++; int k=lg[v-u+1];
		return cmp(pa[k][u],pa[k][v-(1<<k)+1]);
	}
	void init(){
		dfs(1,0); lg[1]=0; 
		for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
		for(int k=1;(1<<k)<=n;k++)
			for(int i=1;i+(1<<k)-1<=n;i++)
				pa[k][i]=cmp(pa[k-1][i],pa[k-1][i+(1<<k-1)]);
	}
	int dis(int x,int y){ return dep[x]+dep[y]-2*dep[lca(x,y)]; }
}t;
void solve(){
	R.pb(1); int d=1;
	for(int i=2;i<=n;i++){
		int dl,dr; dl=dr=0;
		if(L.size()) dl=t.dis(i,L[0]);
		if(R.size()) dr=t.dis(i,R[0]);
		if(max(dl,dr)>d){
			if(dl<=dr){
				for(auto z:L)
					if(t.dis(z,i)==dr) R.pb(z);
				L.clear(); L.pb(i);
			}else{ R.clear(); R.pb(i); }
			d=max(dl,dr);
		}else if(max(dl,dr)==d){
			if(dl>dr) R.pb(i);
			else L.pb(i);
		}
		cout<<L.size()+R.size()<<"\n";
	}
}
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n; n++;
	for(int i=2;i<=n;i++){
		int fa; cin>>fa;
		G[fa].pb(i);
	}
	t.init(); solve();
	return 0;
}
```

---

## 作者：wxzzzz (赞：0)

### 思路

记录两个集合 $s1,s2$ 表示可作为直径左右端点的集合，即：

1. $\forall x\in s1,y\in s2:\operatorname{dis}(x,y)=maxd$，其中 $maxd$ 为直径长度。

1. 令 $(m1,m2)$ 为直径中点（$m1=m2$）或中边（$m1\ne m2$），有 $\forall x1,x2\in s1:|\{x1\to m1\}\cap\{x2\to m1\}|>0,\forall y1,y2\in s2:|\{y1\to m2\}\cap\{y2\to m2\}|>0$。

对于新加入的点 $u$，若 $u$ 和 $s1$ 中某个点 $v$ 可更新直径（$v$ 可任选）：

1. 原 $s1$ 更新为 $\{u\}$。

1. 暴力尝试将 $s1$ 中每个点加入 $s2$。

否则对 $s2$ 类似操作。

因为某个点被弹出 $s1$ 后不可能再进 $s1$，被弹出 $s2$ 后不可能再进 $s2$，因此每个点的势能为 $O(1)$，总复杂度 $O(n\log n)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, maxd, d[300005], s[300005], ft[300005][25];
set<int> s1, s2;
int LCA(int x, int y) {
    if (d[x] > d[y])
        swap(x, y);

    for (int i = 20; i >= 0; i--)
        if (d[ft[y][i]] >= d[x])
            y = ft[y][i];

    if (x == y)
        return x;

    for (int i = 20; i >= 0; i--)
        if (ft[x][i] != ft[y][i])
            x = ft[x][i], y = ft[y][i];

    return ft[x][0];
}
int dis(int x, int y) {
    return d[x] + d[y] - d[LCA(x, y)] * 2;
}
int main() {
    cin >> m;
    n = 1;
    s1.insert(n);

    while (m--) {
        n++;
        cin >> ft[n][0];
        d[n] = d[ft[n][0]] + 1;

        for (int i = 1; i <= 20; i++)
            ft[n][i] = ft[ft[n][i - 1]][i - 1];

        int now, dis1 = 0, dis2 = 0;

        if (s1.size())
            dis1 = dis(n, *s1.begin());

        if (s2.size())
            dis2 = dis(n, *s2.begin());

        now = max(dis1, dis2);

        if (now > maxd) {
            maxd = now;

            if (dis1 >= dis2) {
                for (auto i : s2)
                    if (dis(i, n) == maxd)
                        s1.insert(i);

                s2.clear();
                s2.insert(n);
            } else {
                for (auto i : s1)
                    if (dis(i, n) == maxd)
                        s2.insert(i);

                s1.clear();
                s1.insert(n);
            }
        } else if (dis1 == maxd)
            s2.insert(n);
        else if (dis2 == maxd)
            s1.insert(n);

        cout << s1.size() + s2.size() << '\n';
    }

    return 0;
}
```

---

## 作者：SoyTony (赞：0)

直径的一个重要性质：所有直径交于一点或一边。

不妨把边拆成点，这样就一定交于一点了，考虑动态维护这个交点 $rt$ 以及到 $rt$ 的最大距离 $D$。

加入一个节点 $v$，设 $d=\mathrm{dist}(rt,v)$，进行讨论。

- 若 $d<D$，不影响答案。

- 若 $d=D$，记 $u$ 为 $(rt,v)$ 路径上距 $rt$ 最近的节点，那么使 $sum_u$ 增加 $1$，表示其子树内贡献增加 $1$。

- 若 $d>D$，此时 $rt$ 将移动至 $u$（定义同上），考虑怎么计算答案，容易发现在 $u$ 为根的情况下，$v$ 所在子树一定只有一个端点，而 $rt$ 子树内端点个数为上一次答案减去以 $rt$ 为根时 $u$ 子树内端点个数，其余子树内没有端点。因此要动态维护就是 $rt$ 相邻节点的子树端点个数，这部分是容易的。

提交记录：[Submission - CodeForces](https://codeforces.com/contest/842/submission/227076112)

---

