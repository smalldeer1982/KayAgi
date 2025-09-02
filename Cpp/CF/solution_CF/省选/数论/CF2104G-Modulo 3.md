# Modulo 3

## 题目描述

给定基环内向森林，每个点有且仅有一条出边 $g_i$，可能有自环。

所有点的初始颜色均为 $1$，你可以执行如下操作**任意次**（可以为零次）：

- 选择一个顶点 $u \in [1,n]$，再选择一种颜色 $c \in [1,k]$，将 $u$ 能到达的所有点（包括 $u$ 本身）染成颜色 $c$。

你需要求出，最终能形成的不同的图的数量，**答案对 $3$ 取模**。

两个图不同，当且仅当存在一个编号为 $i$ 的节点，它的颜色在两图中不同。

现在有 $q$ 次修改操作，每次给定 $x,y,k$：

- 将 $g_x$ 修改为 $y$。
- 对于本次输入的 $k$，输出答案，对 $3$ 取模。

对 $g_x$ 的修改操作是永久的，对后面有影响。但是在每次询问答案时，所有顶点的初始颜色都是 $1$。

## 说明/提示

$1 \le n, q \le 2 \times 10^5$。

## 样例 #1

### 输入

```
4 5
2 3 1 4
4 3 1
2 1 2
3 4 3
4 1 5
2 4 4```

### 输出

```
1
2
0
2
1```

## 样例 #2

### 输入

```
8 10
7 4 6 8 7 7 1 4
1 7 5
2 3 3
8 6 1
3 1 3
7 2 5
5 2 4
2 7 4
4 6 5
5 2 3
4 5 1```

### 输出

```
1
0
1
0
2
1
1
2
0
1```

# 题解

## 作者：IkunTeddy (赞：8)

# 题目分析

首先我们发现，一个环上的点一定会被染成一种颜色。
所以我们考虑先缩一下点。

那么现在一定是一个 DAG。然后我们发现只要按照拓扑序染色，那么每个点想是什么颜色就能是什么颜色。

设 DAG 上的点个数为 $cnt$，颜色数为 $k$，那么答案为 $k^{cnt}$。

由于原图每个点只有一条出边，所以强连通分量只能是一个环，且每个点最多在一个环里出现。

问题转化成统计图上环的数量。

还是由于每个点只有一条出边，我们可以把**有向边看成无向边**。

那么维护连通块修改不是很方便，所以我们先用**线段树分治变成只加边**。

但是在加入一条边 $(x,y)$ 且 $x,y$ 联通时，我们就需要查询 $x,y$ 的树上距离。这一步当然可以 LCT 做，但是我们还没用到题目中模 3 的性质。

在答案统计中，点数是放在指数上的，根据欧拉定理，它应该是模 2。

所以距离只有 0 和 1 两种，在此基础下异或跟加减法的结果一样，所以直接用带权并查集即可。

时间复杂度 $O(n\log^2 n)$。

顺带一提，可以 LCT 维护基环树，做到 $O(n\log n)$。

# Code

就放 LCT 维护基环树了。


```cpp
#include<bits/stdc++.h>
using namespace std;
//
const int maxn=2e5+10;
const int mod=3;
int n,q;
int to[maxn];
int vis[maxn];
int res;
inline int Pow(int x,int y){
	x%=mod;
	int s=1;
	for(;y;x=x*x%mod,y>>=1)if(y&1)s=s*x%mod;
	return s;
}
struct node{
	int fa,son[2];
	int sz,val;
	int tagr,tagm;
	node(){fa=son[0]=son[1]=sz=val=tagr=0,tagm=-1;}
}tree[maxn];
inline void init(){for(int i=1;i<=n;i++)tree[i].sz=1;}
inline int isroot(int v){return v!=tree[tree[v].fa].son[0]&&v!=tree[tree[v].fa].son[1];}
inline int get(int v){return v==tree[tree[v].fa].son[1];}
inline void connect(int f,int v,int type){tree[f].son[type]=v;if(v)tree[v].fa=f;}
inline void pushup(int v){
	tree[v].sz=tree[tree[v].son[0]].sz+tree[tree[v].son[1]].sz+1;
}
inline void reverse(int v){
	swap(tree[v].son[0],tree[v].son[1]);
	tree[v].tagr^=1;
}
inline void modify(int v,int k){
	tree[v].val=k;
	tree[v].tagm=k;
}
inline void pushdown(int v){
	if(tree[v].tagr){
		reverse(tree[v].son[0]);
		reverse(tree[v].son[1]);
		tree[v].tagr=0;
	}
	if(tree[v].tagm!=-1){
		modify(tree[v].son[0],tree[v].tagm);
		modify(tree[v].son[1],tree[v].tagm);
		tree[v].tagm=-1;
	}
}
inline void pushtag(int v){if(!isroot(v))pushtag(tree[v].fa);pushdown(v);}
inline void rotate(int v){
	int f=tree[v].fa,g=tree[f].fa,chk=get(v);
	if(!isroot(f))tree[g].son[get(f)]=v;
	tree[v].fa=g;
	connect(f,tree[v].son[chk^1],chk);
	connect(v,f,chk^1);
	pushup(f);
	pushup(v);
}
inline void splay(int v){
	pushtag(v);
	while(!isroot(v)){
		int f=tree[v].fa;
		if(!isroot(f))rotate(get(f)==get(v)?f:v);
		rotate(v);
	}
}
inline void access(int v){
	int p=0;
	while(v){
		splay(v);
		tree[v].son[1]=p;
		pushup(v);
		p=v,v=tree[v].fa;
	}
}
inline void mkroot(int v){
	access(v);
	splay(v);
	reverse(v);
}
inline int findroot(int v){
	access(v);
	splay(v);
	while(tree[v].son[0])v=tree[v].son[0];
	splay(v);
	return v;
}
inline void split(int x,int y){
	mkroot(x);
	access(y);
	splay(y);
}
inline void link(int x,int y){
	mkroot(x),mkroot(y);
	tree[x].fa=y;
}
inline void cut(int x,int y){
	split(x,y);
	tree[y].son[0]=tree[x].fa=0;
	pushup(y);
}
inline int ask(int x){
	access(x),splay(x);
	return tree[x].val;
}
inline void insert(int p){
	int x=p,y=to[p];
	if(findroot(x)!=findroot(y))link(x,y);
	else{
		split(x,y);
		res-=tree[y].sz-1;
		modify(y,p);
		vis[p]=1;
	}
}
inline void delet(int p){
	int x=p,y=to[p];
	if(vis[p]){
		split(x,y);
		res+=tree[y].sz-1;
		modify(y,0);
		vis[p]=0;		
	}else if(ask(y)==ask(x)&&ask(x)){
		p=ask(x);
		split(p,to[p]);
		res+=tree[to[p]].sz-1;
		modify(to[p],0);
		vis[p]=0;
		cut(x,y);
		link(p,to[p]);
	}else cut(x,y);
}
int main(){
	cin>>n>>q;
	init();
	res=n;
	for(int i=1;i<=n;i++){
		cin>>to[i];
		insert(i);
	}
	while(q--){
		int x,y,k;
		cin>>x>>y>>k;
		delet(x);
		to[x]=y;
		insert(x);
		cout<<Pow(k,res)<<'\n';
	}
	
	return 0;
}
```

---

## 作者：wanggk (赞：3)

[cnblogs](https://www.cnblogs.com/wanggk/p/-/CF2104G)

### 题解

设 $m$ 为**缩点**后的点数，那么最终的方案数就是 $k^m$。

又因为答案对 $3$ 取模，由费马小定理可知 $k^m \equiv k^{m \mod 2} \pmod 3$，因此只需要求 $m$ 的奇偶性。

基环森林每个连通块只有一个环，可以用并查集在出现环的时候将 $m$ 异或上两点距离（的奇偶性）。用带权并查集就好了。

本题还带修改，那么对边做线段树分治就可以了。

### 代码

```cpp
#include<bits/stdc++.h>
#define mk make_pair
#define For(i,il,ir) for(int i=(il);i<=(ir);++i)
#define Rof(i,ir,il) for(int i=(ir);i>=(il);--i)
using namespace std;
typedef pair<int,int> pii;
const int maxn=2e5+10;

int n,Q;
int k[maxn];
int pa[maxn],pt[maxn];

#define mid (l+r>>1)
pii opz;
int opx,opy;
vector<pii> tr[maxn<<2];
void update(int o,int l,int r){
    if(opx<=l && r<=opy){
        tr[o].push_back(opz);
        return;
    }
    if(opx<=mid) update(o<<1,l,mid);
    if(opy>mid) update(o<<1|1,mid+1,r);
}
void update(int l,int r,pii v){ opx=l,opy=r,opz=v;update(1,0,Q); }

int tp,ans;
pii st[maxn];
int fa[maxn],val[maxn],h[maxn];

int fd(int x,int &v){ v=0; while(x^fa[x]) v^=val[x],x=fa[x]; return x; }
void merge(int x,int y){
    int vx,vy;
    x=fd(x,vx),y=fd(y,vy);
    if(x==y) ans^=vx^vy;
    else{
        if(h[x]>h[y]) swap(x,y);
        st[++tp]=make_pair(x,h[x]==h[y]);
        fa[x]=y,val[x]=vx^vy^1,h[y]+=(h[x]==h[y]);
    }
}
void undo(int tar){
    while(tp>tar){
        int x=st[tp].first,d=st[tp].second;
        h[fa[x]]-=d,fa[x]=x,val[x]=0,tp--;
    }
}

int res[maxn];
void dfs(int o,int l,int r){
    int pretp=tp,preans=ans;
    for(pii c:tr[o]) merge(c.first,c.second);
    if(l==r) res[l]=ans;
    else dfs(o<<1,l,mid),dfs(o<<1|1,mid+1,r);
    undo(pretp); ans=preans;
}
signed main()
{
    scanf("%d%d",&n,&Q);
    For(i,1,n) scanf("%d",&pa[i]),fa[i]=i,h[i]=1;
    For(i,1,Q){
        int x,y;
        scanf("%d%d%d",&x,&y,&k[i]);
        update(pt[x],i-1,mk(x,pa[x]));
        pa[x]=y,pt[x]=i;
    }
    For(i,1,n) update(pt[i],Q,mk(i,pa[i]));

    ans=n&1;dfs(1,0,Q);
    For(i,1,Q) printf("%d\n",k[i]%3?(res[i]?k[i]%3:1):0);
    return 0;
}
```

---

## 作者：Genius_Star (赞：1)

板子题。

### 思路：

显然对于一个环上的点，怎么染色方案都是相同的；故可以先缩点，设缩点后有 $cnt$ 个点，方案数显然是 $k^{cnt}$。

由于 $k^{cnt} \equiv k^{cnt \bmod (p - 1)} \pmod p$，这里 $p = 3, p - 1 = 2$，所以问题本质上是求 $cnt$ 的奇偶性，即求环的数量的奇偶性。

没啥好说的，不用奇偶性也能作；由于是内向基环树森林，所以每个联通块最多只有一个环，且每个点最多只在一个环上。

故考虑使用 LCT 维护动态加边删边，初始所有点自成一个环 $cnt = n$，对于一个加边操作 $(x, y)$：

- 若 $x, y$ 在一个联通块内，则形成了一个新的环，那么需要减去在 $x \to y$ 路径上的点的贡献（它们原本是自己为环），即 $cnt \gets cnt - \operatorname{dis}(u, v) + 1$（此时不需要加边）。

- 否则不在一个联通块内，直接加边即可。

删边 $(x, y)$ 就有些细节了：

- 若删的边是之前加边时没有加的，即加了这条边后形成了一个环；然后又删掉这条边，大环没了，以每个点自成一个环的小环又有了，故 $cnt \gets cnt + \operatorname{dis}(u, v) - 1$。

- 若删的边是之前加过的，且在环上，那么找到对应这个环之前没有加在 LCT 中的那个边，先删再加；这里也需要 $cnt \gets cnt + \operatorname{dis}(u', v') - 1$（这里 $(u', v')$ 是之前在环上但是没加进 LCT 的边）。

- 否则直接删。

这里我们需要支持路径覆盖为一个边 $p$，表示这个路径上的点是通过 $p$ 这条边形成一个环的。

时间复杂度为 $O(N \log N)$。

---

## 作者：xzy090626 (赞：0)

我们考虑单次询问，考虑到环上的点必须被染成同种颜色（因为两两可达），因此可以考虑缩点，这样缩点后的 DAG 上每个点都可以被染成任意一种颜色，设有 $m$ 个点，答案就是 $k^m$。

现在考虑加入修改操作。由于每次修改相当于加一条边的同时删去一条边，而删边非常难维护，我们不妨把它当成每条边有一个固定的有效区间 $[l,r]$，这样就可以用线段树分治维护，只需要支持加边即可。

现在我们只需要根据加边操作维护当前的图缩点后的点的个数即可。注意到由于有且仅有一个环，设环上有 $x$ 个点，那么 $m=n-x+1$。

根据扩展欧拉定理，我们又知道答案仅与 $x\bmod 2$ 有关。因此，只需要维护当前图上环的长度。

考虑如何求边的长度？当我们加入 $u\rightarrow v$ 这条边的时候，如果 $u\leftarrow v$ 在图上已经存在，那可以藉此求出环的长度。具体地，维护它们在基环树上的距离，$+1$ 就是环的长度。而由于 $\bmod 2$ 的特殊性，只需要维护其异或值即可。

现在考虑使用带权并查集来维护图上两两点之间的距离。我们知道加入这条边之前图中若有环，则与这条边无关；因此可以默认当前图是一颗边定向的树。于是我们直接维护每个点 $x$ 到其父亲 $fa_x$ 的距离，合并时需要启发式合并，并支持撤销操作。当 $u,v$ 已经在同一连通块内时，则通过 $dis_u,dis_v$ 求出其距离即可。

复杂度 $O(n\log^2n)$，还是很不错的题目。

---

