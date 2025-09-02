# [CERC2015] Export Estimate

## 题目描述

#### 题意翻译：

Luka 拥有一个地理数据公司保持着详细的城市地图和出口相关的数据。但是通常客户不想要完整的地图。相反，他们更想要一个只包含主要街道的简单地图：

1. 所有优先级小于 $p$ 的街道被删除

1. 对于每一个路口点 $i$ 从 $1$ 到 $n$（按照这个顺序处理）：

   (a)如果这个路口没有连接到任何街道，它就会被删除。

   (b)如果路口 $i$ 正好连接到通向路口 $a$ 和 $b$ 的两个不同的街道 $x$ 和 $y$，并且 $a$ 和 $b$ 两个路口都与路口 $i$ 不同，那么 $i$ 就会根据下面的过程进行收缩：

   i.删除道路 $x$ 和道路 $y$；

   ii.删除路口 $i$；

   iii.加入一条连接路口 $a$ 和 $b$ 的新道路 $z$；

最初，图中没有环（即一条连接到自身的边）或者平行的边（即在同一对交点之间有一条以上的边），但在收缩的过程中可能会形成环和平行边。

请注意，在步骤2.（b）之前，$x$ 和 $y$ 都不能是环（即 $a$ 和 $b$ 必须和 $i$ 不同），但是新增的 $z$ 可以是一个环（即 $a$ 和 $b$ 可能是相同的）。

给定一个地图和一系列的出口的询问,每个询问找到路口的数量和街道地图出口的数量。

## 样例 #1

### 输入

```
6 7 
1 2 20 
2 3 80 
2 5 100 
3 5 50 
3 4 100 
5 6 90 
4 6 100 
4 
25 75 85 95```

### 输出

```
2 3 
1 1 
2 1 
4 2
```

## 样例 #2

### 输入

```
10 14 
2 7 150 
1 2 100 
2 3 150 
3 1 200 
1 4 60 
4 5 20 
2 5 100 
5 6 90 
6 7 120 
7 5 130 
6 8 50 
8 9 200 
9 10 200 
10 7 200 
5 
300 50 95 100 110```

### 输出

```
0 0 
6 9 
4 5 
4 5 
5 4```

# 题解

## 作者：JoshAlMan (赞：8)

发现两种操作均不影响每个点的度数，第二个操作可以看作把一个点连向两个点转化成了一个边。

而点边的删除的条件都是点的度数，因此考虑点的顺序并不影响图的结构，只会影响删除/留下点的编号，但这个东西对我们没用。

那么我们就可以用一个经典的思路，把边从大到小排序，依此插入边，考虑当前的图对应的点边结构是多少，然后加入那些处于这个状态的答案。我们考虑何种情况的一个点会被删除：

* 度数 $= 0$ 的点。
* 度数 $= 2$ 的点且**最终状态并不是一个自环**。并不是一个自环的条件只能在纯粹的环（即所处联通块只有一个简单环，没有其他冗余的东西）中取到，想象一下它会以此把编号最小的点换成一条边，最终会留下一个编号最大的点的自环。而其他情况，不可能出现度数为 $2$ 的点连的是自环的情况，如果不构成一个环，那么原来图里没自环，连接的两个方向点必不可能缩成同一个点（大小为 $2$ 的纯粹环）。如果构成一个环，但环上有其他杂边，那么不会缩成只有一个点，因为必然有一个点度数 $> 2$。

因此最终状态点的数量 $= $ $n\ - $ 度数为 $0$ 的点数 $-$ 度数为 $2$ 的点数 $+ $ 纯粹的环数

然后再考虑何种情况边的数量会改变：

* 度数 $= 2$ 的点且**最终状态并不是一个自环** 的点，会让两条边数变成一条边，道理同上。

因此最终状态点的数量 $= $ $m\ - $  度数为 $2$ 的点数 $+ $ 纯粹的环数。

其他东西维护都比较简单，纯粹的环数等价于该联通块每个点度数 $= 2$。用一个并查集维护联通块中度数为 $2$ 的点数就好了。

时间复杂度可以做到线性（不排序，用桶，并查集两个优化做到常数）。

---

## 作者：Y_B_X (赞：4)

[原题链接](https://www.luogu.com.cn/problem/P4350)

题意：  
给定一张无向连通图，每次询问时保留边权 $\geq t$ 的边，并对这张图进行如下操作:  
+ 从小到大枚举每个点 $i$ ，若其度数为 $0$ 直接删去。  
+ 若其度数为 $2$ ，则找出连向 $i$ 的点 $u,v$（可能相同），并删去点 $i$ 以及连向 $u,v$ 的两条边，再添加 $u,v$ 一条边。（$u,v$ 相同时形成一个自环）

## $\text{Sulotion}$

如果将询问按 $t$ 从大到小排序，那每次需要的图就由之前的加上一些边得到，边权递减。

先考虑每个操作流程对点与边的影响。

设一个度数为 $k$ 的点称为 $k$ **度点**。则可以发现在第一、第二个流程中受影响的点仅有 $0$ 度点与 $2$ 度点。

每个 $0$ 度点会将点的总量减 $1$ ，而每个 $2$ 度点会将点总数减 $1$ ，且将边总数减 $1$ 。而每个对 $2$ 度点的操作不会影响其他点的度数。

所以只需统计出 $0$ 度点与 $2$ 度点的个数 $sum_0,sum_2$ ，以及出现过得边的个数 $edg$ 。那总点数就是 $n-sum_0-sum_2$, 总边数就是 $edge-sum_2$ 。由于是动态加边，可以用**并查集**维护连通块内 $2$ 度点与 $0$ 度点个数。

但事实上并非如此，在某个连同图是一个**单纯的环**时会出现问题。

因为按照上文说法这个环会没有点剩余，而环上所有点都为 $2$ 度点。但它最终剩余的是一个自环，点数与变数要加上 $1$ 。设纯环个数为 $k$，则最终点与边数为 $n-sum_0,-sum_2+k$ 与 $edge-sum_2+k$ 。

而由于纯环上所有点都为二度点，并查集同时维护点的个数后是容易判定的。

时间复杂度 $O(n\alpha(n))$

代码：（个人认为实现方法还算简单）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int n,m,s,x,y,v,ax,ay;
int s_nd2,s_nd0,s_cyc;
struct node{
	int x,y,w;
	bool operator <(const node &x)const{return w>x.w;}
}e[N],q[N],ans[N];
int f[N],sz[N],sz2[N],deg[N];bool cyc[N];char ch;
inline int getf(int x){while(x^f[x])x=f[x]=f[f[x]];return x;}
inline void read(int &x){
	x=0;ch=getchar();while(ch<48)ch=getchar();
	while(ch>47)x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
}
void write(int x){if(x>9)write(x/10);putchar(48+x%10);}
main(){
	read(n),read(m);register int i,j=0,s,t;
	for(i=1;i<=m;++i)read(x),read(y),read(v),e[i]=(node){x,y,v};
	read(s);for(i=1;i<=s;++i)read(v),q[i]=(node){i,0,v};
	sort(e+1,e+m+1);sort(q+1,q+s+1);
	s_nd0=n;
	for(i=1;i<=n;++i)sz[i]=1,f[i]=i;
	for(i=1;i<=s;++i){
		while(e[j+1].w>=q[i].w&&j<m){
			++j;
			x=e[j].x,y=e[j].y;ax=getf(x),ay=getf(y);
			if(!deg[x])--s_nd0;if(deg[x]==2)--s_nd2,--sz2[ax];
			if(!deg[y])--s_nd0;if(deg[y]==2)--s_nd2,--sz2[ay];
			++deg[x];++deg[y];
			s_cyc-=cyc[ax];cyc[ax]=0;
			if(ax^ay)f[ay]=ax,s_cyc-=cyc[ay],sz[ax]+=sz[ay],sz2[ax]+=sz2[ay];
			if(deg[x]==2)++s_nd2,++sz2[ax];
			if(deg[y]==2)++s_nd2,++sz2[ax];
			if(sz2[ax]==sz[ax])cyc[ax]=1,++s_cyc;
		}
		ans[q[i].x]=(node){n-s_nd0-s_nd2+s_cyc,j-s_nd2+s_cyc};
	}
	for(i=1;i<=s;++i)write(ans[i].x),putchar(' '),write(ans[i].y),putchar('\n');
}
```



---

## 作者：Trote_w (赞：3)

- 很容易想到从大到小加边。

- 观察发现只有度数为0或2的结点会被删除。
- 度数为0直接就删除了
- 度数为2的还会删除两条边并加入一条边（即删除一条边）

- 但额外的，如果是一个单纯的环，不可能被完全删掉，会剩余一个点和一条自环。

所以

- 当前点数=总点数-度数为2的点-度数为0的点+单纯的环的数量
- 当前边数=当前加入的边数-度数为2的点+单纯的环的数量

接下来考虑如何计算单纯的环的数量，注意到一个环内所有节点的度数均为2，则它就是一个单纯的环了，所以我们可以使用并查集维护。

以上。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mem(a) memset(a,0,sizeof(a))


const int mn=3e5+5;

int n,m,c;

struct edge{
    int u,v,w;
    int nxt(int p){
    	return u==p?v:u;
    }
    bool operator < (const edge &e) const{
    	return w>e.w;
    }
}e[mn];

struct Q{
	int u,id;
	bool operator < (const Q &e) const{
		return u>e.u;
	}
}q[mn];

int ansn[mn],ansm[mn];

namespace union_find_set{
    int f[mn];
    int sz[mn],esz[mn];
    void init(int n){
    	for(int i=1;i<=n;i++){
			f[i]=i;sz[i]=1,esz[i]=0
			;
    	}
    }
    int sf(int x){
        if (f[x]==x) return x;
        if (sf(f[x])!=f[x]){
            f[x]=sf(f[x]);
        }
        return f[x];
    }
    void Union(int u,int v){
    	u=sf(u);v=sf(v);
    	if (u!=v){
			f[u]=v;
            sz[v]+=sz[u];
            esz[v]+=esz[u];
            sz[u]=esz[u]=0;
    	}
    }
}using namespace union_find_set;

int dc[mn],cy;
int d[mn];

bool iscycle(int u){
	u=sf(u);
	return sz[u]==esz[u];
}

void add(int u){
	if (sf(e[u].u)!=sf(e[u].v)){
		if (iscycle(e[u].u)) cy--;
		if (iscycle(e[u].v)) cy--;
	}
	else if (iscycle(e[u].u)) cy--;


	dc[d[e[u].u]]--;
	if (d[e[u].u]==2) esz[sf(e[u].u)]--;
	d[e[u].u]++;
	dc[d[e[u].u]]++;
	if (d[e[u].u]==2) esz[sf(e[u].u)]++;

	dc[d[e[u].v]]--;
	if (d[e[u].v]==2) esz[sf(e[u].v)]--;
	d[e[u].v]++;
	dc[d[e[u].v]]++;
	if (d[e[u].v]==2) esz[sf(e[u].v)]++;

    Union(e[u].u,e[u].v);
    if (iscycle(e[u].v)) cy++;

}

void solve(){
	init(n);
	dc[0]=n;

	int ecnt=0;
    for(int i=1;i<=c;i++){
		while(ecnt<m&&e[ecnt+1].w>=q[i].u) {
			add(++ecnt);
		}
		ansn[q[i].id]=n-dc[0]-dc[2]+cy;
		ansm[q[i].id]=ecnt-dc[2]+cy;
    }

}

int main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
	}
	sort(e+1,e+m+1);
	scanf("%d",&c);
	for(int i=1;i<=c;i++) scanf("%d",&q[i].u),q[i].id=i;
	sort(q+1,q+c+1);

    solve();

	for(int i=1;i<=c;i++){
		printf("%d %d\n",ansn[i],ansm[i]);
	}
	return 0;
}

```

---

## 作者：End_Sunset (赞：1)

## 简要题意
> 给你一个无向带权图，每次询问给定一个阈值，要求去掉权值小于阈值的边的子图中，按编号遍历每一个非孤立点，将 deg 恰好为 2 且不是自环的点的两边收缩为一条边，去掉该点，求非孤立点数量及边数。

## 思路
手玩一下。
* 考虑特殊情况,发现一条链会被收缩为 2点1边。
* 考虑较普遍的情况，考虑在主链上添加支链，发现收缩后链的交点会被保留。
* 考虑更普遍的情况，对于树，收缩后变成儿子数量不为 1 的节点构成的虚树。
* 这启发我们从点的 deg 考虑其是否会被收缩。

## 分析
### step1
为保证复杂度，对于每一个询问我们一定不能按照编号一个一个操作，根据以上的手玩思路猜结论：
> 结论1：对于单个询问，点不被删去当且仅当该点 deg 不为 2，无论节点操作顺序如何。

证明：
实际上，对于该结论，后者只是前者的充分不必要条件，我们暂且认为该结论是对的，其必要性的满足条件将在 **step 3** 进行讨论。其充分性的证明如下 ：
* case1 收缩点的邻点不同，那么收缩不会改变其相邻点的 deg。
* case2 收缩点的邻点相同，即该点与其唯一邻点存在重边，那么收缩会使邻点的 deg 减 1，并使邻点出现自环，那么即使邻点原先 deg 为 3 ，该邻点也会因为自环而不会被收缩。
  
  这保证了无论如何改变节点编号，deg 不为 2 的点一定不会被删去。假如我们已经证明其必要性，那么我们可以通过计算 deg 为 2 的点来算出非孤立的点数。

### step 2
显然我们不能对于每个询问都重构图，于是我们按询问的阈值排序，不断添加边，维护 deg 为 2 的点的个数 num。

非孤立点的个数显然，考虑如何通过 num 得到边答案。
> 结论2： 剩余边数为不小于阈值的边数减去 num

证明：每删去一个点，则删去两边，添加一条边，结论显然。

我们似乎已经得到了无论思路还是代码都是绿题难度的解法？

### step 3
手玩样例1发现 **step 1** 的结论1并不完全正确，对于 case2，当收缩前邻点的 deg 为 2 时，其可以因为自环免于被收缩，我们钦定其为 case3。因而结论1的必要性在 case3 的情景下是错误的。考虑什么时候出现 case3，由于题面保证无重边和自环，case2 的重边只有可能由三元环的一条边收缩而来。这启发我们一个结论。
> 结论3：对于询问，在每一次收缩前，每一个最多一点与外界链接的多元简单环对应着一个 case2, 每一个孤立多元简单环都对应着一个 case3。

证明：归纳地证明，手玩一下，一个孤立的简单 $n$ 元环只有可能通过一个孤立简单 $n+1$ 元环收缩而来。同样地一个孤立简单 $n+1$ 元环都会收缩为 $n$ 元环。最后他们会变成 case3 的二元环，被操作为一个一元环。

如果我们不考虑 case3，那么每一个孤立多元环被完全消灭，而实际它会变成一个一元环，错误地统计会使答案中的边数和点数少 1 。于是我们可以在维护 deg 为 2 点数 num 的同时，维护孤立简单多元环的个数 tag，最后在答案上均加上 tag 即可。

### step 4
如何维护 tag？连通块为简单多元环当且仅当其所有点的 deg 均为2，我们只要在联通块 merge 时维护 size 和 连通块中的 num 即可，若二者相等则 tag 增 1。 

## 后记
事实上如果不考虑证明，这三个结论和其实现方式都是完全无法匹配其标签难度的，而结论的正确性也是一眼的。此题真正难度在于读懂不那么人话的翻译。

## 实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define fst first
#define scd second
#define pii pair<int, int>
#define mkp make_pair
#define llg long long
const int N=5e5+5,mod=1e9+7,inf=1e9;

int deg[N],fa[N],siz[N],val[N];
int nod,del,edg,tag,n,m,q;
struct edge{
	int u,v,w;
}e[N];
bool cmp(edge a,edge b){
	return a.w<b.w;
}
pii p[N],ans[N];

int find(int x){
	return ((fa[x]==x) ? x : fa[x]=find(fa[x]));
}
void merge(int x,int y){
	if(x==y) return;
	fa[x]=y;
	siz[y]+=siz[x],val[y]+=val[x];
}
void solve(int u,int v){
	int x=find(u),y=find(v);
	nod+=(!deg[u])+(!deg[v]);
	del-=(deg[u]==2)+(deg[v]==2); 
	tag-=(siz[x]==val[x])+(x!=y)*(siz[y]==val[y]);
	val[x]-=(deg[u]==2); val[y]-=(deg[v]==2);
	
	edg++; merge(x,y);
	
	deg[u]++; deg[v]++;
	del+=(deg[u]==2)+(deg[v]==2);
	val[y]+=(deg[u]==2); val[y]+=(deg[v]==2);
	tag+=(siz[y]==val[y]);
}

int main(){
	cin>>n>>m;
	for(int i=1; i<=n; i++) siz[i]=1,fa[i]=i;
	for(int i=1; i<=m; i++){
		int u,v,w;
		cin>>u>>v>>w;
		e[i]={u,v,w};
	}	
	sort(e+1,e+m+1,cmp);
	cin>>q;
	for(int i=1; i<=q; i++){
		cin>>p[i].fst; p[i].scd=i;
	}
	sort(p+1,p+q+1);
	for(int i=q,j=m; i; i--){
		for(; j&&e[j].w>=p[i].fst; j--)
			solve(e[j].u,e[j].v);
		ans[p[i].scd]=mkp(nod-del+tag,edg-del+tag);
	}
	for(int i=1; i<=q; i++) cout<<ans[i].fst<<" "<<ans[i].scd<<"\n"; 
}
```

---

## 作者：dyc2022 (赞：1)

[更好的阅读体验](https://www.cnblogs.com/dyc2022/p/19033729)
***
很简单的一道题，但是原来的翻译太唐了 /tuu

我们考虑离线，把边的优先级和询问的值均从大到小排序。这样我们只剩下加边操作。

操作有有以下三种情况：

1. 将度数为 $0$ 的点删除。这种操作会让点数 $-1$ 并且不会影响到其他点的度数。
2. 将度数为 $2$ 的点的两个邻居之间链边并将这个点删除。这种操作会让点数、边数都 $-1$ 并且不会影响到其他点的度数。
3. 特别地，如果一个点是个自环，则经过一次操作 2 后点数和边数都不变。

我们只要找出有多少次 3 的情况就能算出最后剩几个点几条边了。

如果一个连通块有度数 $ \not = 2$ 的点，则这个点不管多少次操作都不会变。一个连通块会删除出自环，一定是这个连通块本身就是一个简单环。

我们写一个并查集，维护一个连通块的形态是否是链或简单环，如果是链，还要维护链的两个端点。一次合并的时候，如果是在两条链的端点出合并，那么会合并出一条更长的链。如果实在同一条链的两个端点处合并，那么就会合并处一个环。至于度数为 $0$ 或 $2$ 的点可以很简单在加边的过程中动态维护。

那么这道题就做完了，复杂度为 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define N 300006
using namespace std;
int n,m,m_now,q,c0,c2,deg[N],vertex[N],edge[N];
pair<int,int> ask[N];
struct Edge{
    int u,v,w;
    void read(){scanf("%lld%lld%lld",&u,&v,&w);}
}E[N];
struct Node{
    int is_chain,c1,c2;
    int is_ring;
    int fa;
    void init(int i){is_chain=1,c1=c2=fa=i,is_ring=0;}
}f[N];
struct UFS{
    int ring_cnt;
    void init(){for(int i=1;i<=n;i++)f[i].init(i);}
    int find(int k){return f[k].fa==k?k:f[k].fa=find(f[k].fa);}
    void merge(int u,int v)
    {
        int fu=find(u),fv=find(v);
        if(fu!=fv)
        {
            if(f[fu].is_chain&&f[fv].is_chain)
            {
                f[fu].is_chain=0;
                if(f[fu].c1==u&&f[fv].c1==v)
                    f[fu].is_chain=1,f[fu].c1=f[fu].c2,f[fu].c2=f[fv].c2;
                else if(f[fu].c1==u&&f[fv].c2==v)
                    f[fu].is_chain=1,f[fu].c1=f[fu].c2,f[fu].c2=f[fv].c1;
                else if(f[fu].c2==u&&f[fv].c1==v)
                    f[fu].is_chain=1,f[fu].c1=f[fu].c1,f[fu].c2=f[fv].c2;
                else if(f[fu].c2==u&&f[fv].c2==v)
                    f[fu].is_chain=1,f[fu].c1=f[fu].c1,f[fu].c2=f[fv].c1;
            } else f[fu].is_chain=f[fv].is_chain=0;
            ring_cnt-=f[fu].is_ring,f[fu].is_ring=0;
            ring_cnt-=f[fv].is_ring,f[fv].is_ring=0;
            f[fv].fa=fu;
        } else {
            ring_cnt-=f[fu].is_ring,f[fu].is_ring=0;
            if(f[fu].is_chain)
            {
                int mn_c=min(f[fu].c1,f[fv].c2),mx_c=max(f[fu].c1,f[fv].c2);
                int mn_uv=min(u,v),mx_uv=max(u,v);
                if(mn_c==mn_uv&&mx_c==mx_uv)f[fu].is_ring=1,ring_cnt++;
            }
            f[fu].is_chain=0;
        }
    }
}S;
void addedge(int u,int v)
{
    if(!deg[u])c0--;if(!deg[v])c0--;
    if(deg[u]==2)c2--;if(deg[v]==2)c2--;
    deg[u]++,deg[v]++,m_now++,S.merge(u,v);
    if(deg[u]==2)c2++;if(deg[v]==2)c2++;
}
main()
{
    scanf("%lld%lld",&n,&m),S.init(),c0=n;
    for(int i=1;i<=m;i++)E[i].read();
    sort(E+1,E+1+m,[](Edge x,Edge y){
         return x.w>y.w;
    });
    scanf("%lld",&q);
    for(int i=1;i<=q;i++)
        scanf("%lld",&ask[i].first),ask[i].second=i;
    sort(ask+1,ask+1+q,[](pair<int,int> x,pair<int,int> y){
         return x.first>y.first;
    });
    for(int i=1,j=0;i<=q;i++)
    {
        while(j<m&&E[j+1].w>=ask[i].first)j++,addedge(E[j].u,E[j].v);
        vertex[ask[i].second]=n-c0-c2+S.ring_cnt,edge[ask[i].second]=m_now-c2+S.ring_cnt;
    }
    for(int i=1;i<=q;i++)
        printf("%lld %lld\n",vertex[i],edge[i]);
    return 0;
}
```

---

## 作者：FjswYuzu (赞：1)

大家很喜欢放一些细节题。

分析一个结论，也即如果一个点度数不为 $2$ 一定不会被删除，否则一定会被删除，留下的边就是留下的所有点的度数和除以二。

证明这个结论的话，首先一个点度数为 $1$ 一定不会多出现一条边连到它身上然后被删掉；然后度数大于等于 $3$ 这些边肯定还是不会动，唯一有必要分析的是三元环套一个单点的情况，容易发现会变成自环，这样也不可能被删掉。边的数量的结论是明显的。

那就先离线，权值从大到小加边。

打了一发，过不了样例……原因是出现了一个简单环，这样最后会留下一条边一个点。好像也就只有这个例外了。

那就用并查集维护单链的两个端点，合并的时候浅处理一下就好了。

细节比较多，可以看[完整代码](https://www.luogu.com.cn/paste/ohxbx7fd)。

---

## 作者：Fa_Nanf1204 (赞：0)

### 分析：
对于边权的处理，我们考虑将询问离线，将询问的权值和边权都从小到大排序，那这样就只用加边就行了。

考虑如何处理删边删点的过程，对其分类讨论：
- 对于度数为 $0$ 的点，直接删去，点数减 $1$，记这种点的个数为 $a$。
- 对于度数为 $2$ 的点，操作后点数减 $1$，边数减 $1$，且不影响其他点的度数，记这种点的个数为 $b$。
- 对于其他度数的点，不会被删去。
- 如果一个连通块构成了一个单纯的环，即所有连通块内的点的度数均为 $2$，则操作后会留下一个自环的点，此时不符合以上第 $2$ 种情况的处理方式，需要特殊处理，记这种连通块的个数为 $c$。

那么考虑计算答案，因为每次操作不影响其他点的度数，所以不用管顺序，答案点数即为 $n-a-b+c$，边数为 $m-b+c$，其中 $n$ 和 $m$ 分别为当前图上的总点数和总边数。考虑每次加边如何维护以上变量，其他都是好维护的，讲一下 $c$ 如何维护。用一个并查集，维护连通块是不是链或是不是环，如果是链需要维护链两端的点，每次加边合并时分类讨论一下即可。

代码私信领取。

---

## 作者：__ycx2010__ (赞：0)

先将 $t_k$ 排序，删边操作转换为加边。

观察发现 $2$ 操作中改变 $i$ 遍历的顺序，结果不变，对于 $(b)$，修改前后其他点的度数不变。

特殊情况是纯环，最后一个点会出现自环，根据题目描述无法删除，所以 $n' = n-cnt0-cnt2+纯环数量,m'=m-cnt2+纯环数量$。

于是问题变为维护动态加边的纯环数量，用并查集维护出连通块的点数和度数为 $2$ 的节点的点数即可。

时间复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 300010;
int fa[N], cnt[N], siz[N], d[N];
pair<int, int> ans[N];

struct Edge {
	int u, v, w;
} edge[N];

int find(int u) {
	return fa[u] == u ? u : fa[u] = find(fa[u]);
}

int is_hoop(int u) {
	if (find(u) == u) {
		return (cnt[u] == siz[u]);
	}
	return 0;
}

bool cmp(Edge AA, Edge BB) {
	return AA.w > BB.w;
}

int main() {
	int n, m, q;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i ++ ) fa[i] = i, siz[i] = 1;
	for (int i = 1; i <= m; i ++ ) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		edge[i] = {u, v, w};
	}
	sort(edge + 1, edge + m + 1, cmp);
	scanf("%d", &q);
	vector<pair<int, int>> v;
	for (int i = 1; i <= q; i ++ ) {
		int x;
		scanf("%d", &x);
		v.push_back({x, i});
	}
	sort(v.begin(), v.end());
	reverse(v.begin(), v.end());
	int j = 0, cnt0 = n, cnt2 = 0, mm = 0, huan = 0;
	for (auto t : v) {
		while (j + 1 <= m && edge[j + 1].w >= t.first) {
			j ++ ;
			int u = edge[j].u, v = edge[j].v, ch = 0;
			mm ++ ;
			d[u] ++ , d[v] ++ ;
			if (d[u] == 1) {
				cnt0 -- ;
			} else if (d[u] == 2) {
				cnt2 ++ ;
				ch ++ ;
			} else if (d[u] == 3) {
				cnt2 -- ;
				ch -- ;
			}
			if (d[v] == 1) {
				cnt0 -- ;
			} else if (d[v] == 2) {
				cnt2 ++ ;
				ch ++ ;
			} else if (d[v] == 3) {
				cnt2 -- ;
				ch -- ;
			}
			int uu = find(u), vv = find(v);
			if (uu == vv) {
				huan -= is_hoop(uu);
				cnt[uu] += ch;
				huan += is_hoop(uu);
			} else {
				huan -= is_hoop(uu);
				huan -= is_hoop(vv);
				fa[vv] = uu;
				cnt[uu] += cnt[vv] + ch;
				siz[uu] += siz[vv];
				huan += is_hoop(uu);
			}
		}
		int tn = n - cnt0 - cnt2 + huan;
		int tm = mm - cnt2 + huan;
		ans[t.second] = {tn, tm};
	}
	for (int i = 1; i <= q; i ++ )
		printf("%d %d\n", ans[i].first, ans[i].second); 
	return 0;
}
```

---

## 作者：james1BadCreeper (赞：0)

经验和输入格式几乎已经告诉我们在线不可做。考虑将边按照边权从大到小排序，这样只会有加边操作，也就是说点的度数只会增加。

表面上看，只有度数为 $0$ 的点和度数为 $2$ 的点会产生影响。当有点的度数 $0\rightarrow 1$ 时，点的个数会增加。当度数 $1\rightarrow 2$ 时，边、点的个数均会减少 $1$。当 $2\rightarrow 3$ 时，则复原。

理想很美好，现实很骨感。由于操作是按照顺序进行的，因此在操作过程中点的度数也会发生改变。但手搓几个情况后发现这事其实没有什么关系，只有在这个连通块自己是个环的时候会被删成一个点加一个自环。

我们发现并查集，然后再维护一下每个连通块上不同度数的点的个数可以很好地完成这个问题。

```cpp
#include <bits/stdc++.h>
using namespace std; 

int n, m, q; 
struct Edge {
    int u, v, w; 
    bool operator< (const Edge &a) const {
        if (w != a.w) return w > a.w; 
        return u > a.u; 
    }
} a[600005]; 
int tot, an1[300005], an2[300005]; 
int V, E; 

int fa[300005], sz[300005], sz2[300005], c[300005]; 
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
int deg[300005]; 

int main(void) {
    ios::sync_with_stdio(0); 
    cin >> n >> m; 
    for (int i = 1; i <= m; ++i) cin >> a[i].u >> a[i].v >> a[i].w; 
    cin >> q; tot = m; 
    for (int i = 1; i <= q; ++i) {
        int w; cin >> w; ++tot; 
        a[tot].v = i, a[tot].w = w; 
    }
    sort(a + 1, a + tot + 1); 
    for (int i = 1; i <= n; ++i) fa[i] = i, sz[i] = 1; 
    int d0 = n, d2 = 0, cyc = 0, ec = 0; 
    for (int i = 1; i <= tot; ++i) {
        if (a[i].u == 0) { 
            an1[a[i].v] = V, an2[a[i].v] = E; 
            continue; 
        }
        int u = a[i].u, v = a[i].v; 
        // cout << "T " << u << " " << v << "\n"; 
        int uu = find(u), vv = find(v); 
        if (!deg[u]) --d0; if (deg[u] == 2) --d2, --sz2[uu]; 
        if (!deg[v]) --d0; if (deg[v] == 2) --d2, --sz2[vv]; 
        ++deg[u]; ++deg[v]; 
        if (c[vv]) c[vv] = 0, --cyc; 
        if (uu != vv) {
            if (c[uu]) c[uu] = 0, --cyc; 
            fa[uu] = vv, sz[vv] += sz[uu], sz2[vv] += sz2[uu]; 
        }
        if (deg[u] == 2) ++d2, ++sz2[vv]; 
        if (deg[v] == 2) ++d2, ++sz2[vv]; 
        if (sz2[vv] == sz[vv]) c[vv] = 1, ++cyc; 
        V = n - d0 - d2 + cyc; 
        ++ec; E = ec - d2 + cyc; 
        // cout << d0 << " " << d2 << " " << cyc << "\n"; 
        // cout << sz[vv] << " " << sz2[vv] << "\n"; 
    }
    for (int i = 1; i <= q; ++i) cout << an1[i] << " " << an2[i] << "\n"; 
    return 0; 
}
```

---

