# GOT - Gao on a tree

## 题目描述

 There's a tree, with each vertex assigned a number. For each query (a, b, c), you are asked whether there is a vertex on the path from a to b, which is assigned number c?

## 样例 #1

### 输入

```
5 5
1 2 3 4 5
1 2
1 3
3 4
3 5
2 3 4
2 4 3
2 4 5
4 5 1
4 5 3```

### 输出

```
NotFind
Find
NotFind
NotFind
Find```

# 题解

## 作者：lzyqwq (赞：8)

[**更好的阅读体验**](https://www.cnblogs.com/MnZnOIerLzy/articles/17114585.html)

# $\texttt{Description}$

**[SPOJ 题目链接](https://www.spoj.com/problems/GOT/en/ "SPOJ 题目链接")**

**[洛谷题目链接](https://www.luogu.com.cn/problem/SP11985 "洛谷题目链接")**

> - 有一棵 $n$ 个节点的树，第 $i$ 个节点有颜色 $a_i$，$m$ 次询问，每次询问 $u,v$ 节点之间（含）是否存在颜色为 $w$ 的节点。
>
> - $n\le 10^5$，$m\le 2\times 10^5$，$0\le a_i,w\le n$。

# $\texttt{Solution}$

和[**洛谷 P3313**](https://www.luogu.com.cn/problem/P3313 "洛谷 P3313") 一样，对于这类维护颜色的问题，可以考虑使用**动态开点线段树**来解决。

首先进行**树链剖分**把树上路径问题转化成序列问题，然后对每种颜色建立线段树。由于是存在性的问题，可以考虑建树时将每个点权值赋成 $1$，维护区间**或和**。

对于每次询问，在颜色 $c$ 对应的线段树上跳链查询即可。

时间复杂度为 $\mathcal{O}((n+q)\log^2n)$，空间复杂度为 $\mathcal{O}(n\log n)$，可以接受。

# $\texttt{Code}$

代码实现时一些小细节：

- 多测清空。

- 我使用指针实现动态开点线段树，注意判左右儿子是不是 `NULL`。以及修改的时候参数传的是地址，否则修改的不是线段树本身，而是形参创造的一个副本（个人理解，轻喷）。

- 查询或合并左右儿子的时候如果遇到了 $1$ 就直接返回，因为已经说明存在性了。

[**评测记录**](https://www.luogu.com.cn/record/102039180 "**评测记录**")



```cpp
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define N 100005
#define ls x->lson
#define rs x->rson
using namespace std;
int n,q,a[N],h[N],t[N],d[N],f[N],sz[N],dfn[N];
struct node{
    bool v;
    node*lson,*rson;
}*rt[N];
vector<int>g[N];
void dfs1(int u,int fa){
    sz[u]=1;
    for(int v:g[u]){
        if(v^fa){
            d[v]=d[u]+1;
            dfs1(v,f[v]=u);
            sz[u]+=sz[v];
        }
    }
}
void dfs2(int u,int fa){
    for(int v:g[u]){
        if(v^fa){
            if((sz[v]<<1)>sz[u]){
                t[h[u]=v]=t[u];
            }else{
                t[v]=v;
            }
            dfs2(v,u);
        }
    }
}
void dfs3(int u,int fa){
    dfn[u]=++dfn[0];
    if(h[u]){
        dfs3(h[u],u);
    }
    for(int v:g[u]){
        if((v^fa)&&(v^h[u])){
            dfs3(v,u);
        }
    }
}
void add(node*&x,int l,int r,int k){
    if(x==NULL){
        x=new node;
    }
    if(l^r){
        int m=(l+r)>>1;
        if(k<=m){
            add(ls,l,m,k);
        }else{
            add(rs,m+1,r,k);
        }
        x->v=0;
        if(ls!=NULL){
            x->v|=ls->v;
        }
        if(x->v){
            return;
        }
        if(rs!=NULL){
            x->v|=rs->v;
        }
    }else{
        x->v=1;
    }
}
bool query(node*x,int l,int r,int ql,int qr){
    if(ql<=l&&r<=qr){
        return x->v;
    }
    int m=(l+r)>>1;
    bool v=0;
    if(ql<=m&&ls!=NULL){
        v|=query(ls,l,m,ql,qr);
    }
    if(v){
        return 1;
    }
    if(qr>m&&rs!=NULL){
        v|=query(rs,m+1,r,ql,qr);
    }
    return v;
}
bool chainquery(int x,int y,int c){
    bool v=0;
    while(t[x]^t[y]){
        if(d[t[x]]<d[t[y]]){
            swap(x,y);
        }
        v|=query(rt[c],1,n,dfn[t[x]],dfn[x]);
        if(v){
            return 1;
        }
        x=f[t[x]];
    }
    if(d[x]>d[y]){
        swap(x,y);
    }
    return query(rt[c],1,n,dfn[x],dfn[y]);
}
int main(){
    while(~scanf("%d%d",&n,&q)){
        for(int i=1;i<=n;++i){
            scanf("%d",a+i);
            g[i].clear();
            rt[i]=NULL;
            h[i]=0;
        }
        rt[dfn[0]=0]=NULL;
        for(int i=1,u,v;i<n;++i){
            scanf("%d%d",&u,&v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs1(1,0);
        dfs2(t[1]=1,0);
        dfs3(1,0);
        for(int i=1;i<=n;++i){
            add(rt[a[i]],1,n,dfn[i]);
        }
        for(int i=1,u,v,w;i<=q;++i){
            scanf("%d%d%d",&u,&v,&w);
            if(rt[w]==NULL){
                puts("NotFind");
                continue;
            }
            if(chainquery(u,v,w)){
                puts("Find");
            }else{
                puts("NotFind");
            }
        }
    }
}
```


---

## 作者：TKXZ133 (赞：8)

[SP11985 GOT](https://www.luogu.com.cn/problem/SP11985)

树链剖分 + vector + 二分跑得飞快，$O(n \log^2n)$ 只比 $O(n)$ 做法慢一倍。

### 思路：

前置知识：[树链剖分](https://oi-wiki.org//graph/hld/)。

题中颜色的范围是 $[1,n]$，十分良心，所以不需要进行离散化之类的操作。

询问点 a，b 之间的路径中是否有点权为 c 的点，不好做。所以我们可以利用 dfs 序转化问题。  

即，我们开 $10^5$ 个 vector，第 i 个 vector 中保存所有颜色为 i 的点的 dfs 序，并且使每一个 vector 中的数单调递增。  

这样我们就可以在树上按重链一段段的查询，每次在颜色对应的 vector 中二分查找是否有数在这条重链的的 dfs 序的范围中，如果有，颜色自然也就找到了。

时间复杂度为 $O(n \log ^2n)$，但常数较小。

### 做法与技巧：

在将 dfs 序加入 vector 时，我们可以循环 dfs 序，使得 vector 中的数单调递增，从而省去排序。

多测清空时，尽量少清空数组，这可以大大减少时间。

### 代码：

```
#include <bits/stdc++.h>
using namespace std;
const int N=200100;

int to[N],nxt[N],head[N],w[N];//链星
int top[N],fa[N],dfn[N],rnk[N],siz[N],dep[N],son[N];
// 重链顶端，节点父亲，dfs序，dfs序对应的点，节点子树大小，节点深度，节点的重儿子
int idx,cnt,n,m,in1,in2,in3;
vector <int> v[N];

void add(int u,int v){idx++;to[idx]=v;nxt[idx]=head[u];head[u]=idx;}
void Swap(int &x,int &y){int t=x;x=y;y=t;}

void dfs_1(int s,int gr){
    dep[s]=dep[gr]+1;fa[s]=gr;
    son[s]=-1;siz[s]=1;//赋初值
    for(int i=head[s];i;i=nxt[i]){
        int v=to[i];
        if(v==gr) continue;
        dfs_1(v,s);
        siz[s]+=siz[v];//更新子树大小
        if(son[s]==-1||siz[v]>siz[son[s]]) son[s]=v;//更新重儿子
    }
}

void dfs_2(int s,int tp){
    top[s]=tp;dfn[s]=++cnt;rnk[cnt]=s;//保存dfs序和dfs序对应的点
    if(son[s]==-1) return ;
    dfs_2(son[s],tp);
    for(int i=head[s];i;i=nxt[i]){
        int v=to[i];
        if(v!=son[s]&&v!=fa[s]) dfs_2(v,v);
    }
}

int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(head,0,sizeof head);
        memset(son,0,sizeof son);
        for(int i=1;i<N;i++) v[i].clear();//对每个vector分别清空
        idx=0;
        for(int i=1;i<=n;i++) scanf("%d",&w[i]);
        for(int i=1;i<n;i++){
            scanf("%d%d",&in1,&in2);
            add(in1,in2);add(in2,in1);
        }
        dfs_1(1,0);dfs_2(1,1);
        for(int i=1;i<=cnt;i++)//i表示dfs序
            v[w[rnk[i]]].push_back(i);//向i对应的点的点权对应的vector中加入i
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&in1,&in2,&in3);
            int x=in1,y=in2,c=in3;
            bool have=0;
            while(top[x]!=top[y]){//跳链
                if(dep[top[x]]<dep[top[y]]) Swap(x,y);
                auto it=lower_bound(v[c].begin(),v[c].end(),dfn[top[x]]);//在颜色所对应的vector中二分查找其重链顶的dfs序
                if(it!=v[c].end()&&*it<=dfn[x]){have=1;break;}//找到了就跑路
                x=fa[top[x]];
            }
            if(!have){//对剩余的一部分进行查找
                if(dfn[x]>dfn[y]) Swap(x,y);
                auto it=lower_bound(v[c].begin(),v[c].end(),dfn[x]);
                if(it!=v[c].end()&&*it<=dfn[y]) have=1;
            }
            if(have) puts("Find");
            else puts("NotFind");
        }
    }
    return 0;
}
```

### 其他：

与该题类似的题目：[P5838 Milk Visits G](https://www.luogu.com.cn/problem/P5838)（双倍经验）。

这是蒟蒻第一次写题解，如有错误请指出。

---

## 作者：RedreamMer (赞：7)

[$\Large\texttt{SP11985 GOT}$](https://www.luogu.com.cn/problem/SP11985)

[$\texttt{my cnblogs}$](https://www.cnblogs.com/RedreamMer/p/15036398.html)

怎么题解区还有树剖啊？数据结构不至于。

推荐一种码量极小的 $\mathcal O(n)$ 的写法。

前置知识：[$\texttt{Tarjan}$ 求 $\texttt{LCA}$ 的思想](https://www.cnblogs.com/RedreamMer/p/13708436.html)

## 思路

我们不需要数据结构，我们就用一些记录颜色的桶，根据我们 Tarjan 求 LCA 的思路，在 DFS 遍历的过程中，对于一个询问，我们只需要比较它们在 DFS 过程中记录的关于其询问的信息，就可以得出询问的答案。

对于遍历到一个点，我们可以（套路地）记录这个点到根节点其询问颜色的最深节点编号，对于一个询问我们记录两个点的这种信息，我们发现，如果这两个点之间有我们要找的颜色的点，那么这两个值必然是不同的，即必然有其中一个值属于 $[LCA, x]$ 这段区间内而不属于 $[LCA, y]$ 这段区间内。

对于查询两端的 LCA 这个节点，为了将它也统计进去，我们在记录颜色最低节点的时候记录为**当前链种**这个节点的儿子节点的编号，这样 LCA 也能判到，最后特判下询问的两个节点就好了。

其实很套路。

## 代码

口胡难懂，Code 棒棒。

```cpp
int a, b, d[N + 5], s[N + 5], ans[N + 5];
struct A {
	int o, d, c;
} ask[N + 5];
vector<int> st[N + 5], q[N + 5];

void dfs(int n, int fa) {
	int _d = d[s[fa]];
	d[s[fa]] = n;
	rep(i, 0, siz(q[n]) - 1) {
		int id = q[n][i];
		if (ask[id].o) ans[id] |= (d[ask[id].c] != ask[id].d);
		else {
			ask[id].o = 1;
			ask[id].d = d[ask[id].c];
		}
	}
	rep(i, 0, siz(st[n]) - 1) {
		int v = st[n][i];
		if (v == fa) continue;
		dfs(v, n);
	}
	d[s[fa]] = _d;
}

signed main() {
	// freopen("in1.in", "r", stdin);
	// freopen("out.out", "w", stdout);
	while (~scanf("%d%d", &a, &b)) {
		rep(i, 1, a) s[i] = read() + 1, st[i].clear();
		rep(i, 1, a + 1) q[i].clear();
		rep(i, 1, b) ask[i] = (A) {0, 0, 0};
		int x, y;
		rep(i, 1, a - 1) {
			x = read();
			y = read();
			st[x].PB(y);
			st[y].PB(x);
		}
		rep(i, 1, b) {
			x = read();
			y = read();
			ask[i].c = read() + 1;
			ans[i] = (s[x] == ask[i].c || s[y] == ask[i].c);
			q[x].PB(i);
			q[y].PB(i);
		}
		dfs(1, 0);
		rep(i, 1, b) puts(ans[i] ? "Find" : "NotFind");
		puts("");
	}
	return 0;
}
```

---

## 作者：Durancer (赞：3)

### 前言

这个题对 $\text{STL}$ 太不友好了qwq，极限卡时才过去了。

### 思路

我们要做的是查询两点的简单路径之间的点是否存在某一个特定的点值，由树剖的性质可以知道，我们每次查询的区间都是一段连续的标号，我们可以考虑用 $\text{vector}$ 把每一个颜色的标号存储下来，然后二分进行查找。

这里有一个小 $\text{trick}$ ，我们可以在建立 $\text{dfs}$ 序的同时放入相应颜色所在位置的标号，这样一定是升序排列的，就不需要对每一种颜色进行一遍排序了，大大节省了时间。

还有一点，这个题目如果用 $\text{STL}$ 做会有一些卡常，清空的时候注意尽量不要用 $\text{memset}$ ，最好是循环清空，否则会做很多不必要的工作。

### 代码实现

```cpp
/*

	对于连续的一段区间，弄一个vector，,存储每个颜色的标号
	
	然后用lower_bound查找即可 
	
	注意多重询问要清空 

*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<cmath>
#include<algorithm>
#include<map>
#include<vector>
using namespace std;
const int N=1e5+9;

#define mid ((l+r)>>1)
#define lson rt<<1,l,mid
#define rson rt<<1|1,mid+1,r

struct node{
	int last;
	int to;
}e[N<<1];
int head[N],e_cnt;
int top[N],siz[N],son[N],f[N];
int dep[N],id[N],cnt,col[N];
int n,T,maxn;
vector<int> g[N]; 
int read()
{
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=(x<<1)+(x<<3)+(s^'0');s=getchar();}
	return f*x;
}
void add(int from,int to)
{
	e[++e_cnt].last=head[from];
	e[e_cnt].to=to;
	head[from]=e_cnt;	
} 
//----------------------树剖--------------------
void dfs1(int x,int fa)
{
	dep[x]=dep[fa]+1;
	siz[x]=1;
	f[x]=fa;
	int maxnson=-1;
	for(int i=head[x];i;i=e[i].last)
	{
		int v=e[i].to;
		if(v==fa) continue;
		dfs1(v,x);
		siz[x]+=siz[v];
		if(maxnson<siz[v])
		{
			maxnson=siz[v];
			son[x]=v;
		}
	}	
}
void dfs2(int x,int topf)
{
	top[x]=topf;
	id[x]=++cnt;
	g[col[x]].push_back(id[x]);
	if(!son[x]) return;
	dfs2(son[x],topf);
	for(int i=head[x];i;i=e[i].last)
	{
		int v=e[i].to;
		if(v==f[x] or v==son[x])
			continue;
		dfs2(v,v);
	}
}
bool check(int l,int r,int k)
{
	vector<int>::iterator it=lower_bound(g[k].begin(),g[k].end(),l);
	if (it==g[k].end())
		return false;
	if(*it<=r)
		return true;
	else return false;
} 
bool Find(int x,int y,int k)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		if(check(id[top[x]],id[x],k))
			return true;	
		x=f[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	return check(id[x],id[y],k);
}
void clear()
{
	cnt=e_cnt=0;
	for(int i=0;i<=n;i++)
	{
		son[i]=0;
		head[i]=0;
		id[i]=0;
	}
	for(int i=0;i<=n;i++)
		g[i].clear();
	
}
int main()
{
	while(scanf("%d%d",&n,&T)!=EOF)
	{
		for(int i=1;i<=n;i++)
			col[i]=read();
		for(int i=1;i<n;i++)
		{
			int u=read();
			int v=read();
			add(u,v);
			add(v,u);
		}
		dfs1(1,0);
		dfs2(1,1);
//		for(int i=1;i<=maxn;i++)
//			sort(g[i].begin(),g[i].end());不需要排序 
		for(int i=1;i<=T;i++)
		{		
			int u=read();
			int v=read();
			int w=read();
			if(!Find(u,v,w))
				cout<<"NotFind"<<endl;
			else cout<<"Find"<<endl;
		} 
		clear(); 
	}
	return 0;
}
```

---

## 作者：1jia1 (赞：2)

这题用树剖+vector+二分十分方便，于是我打了个主席树。

这题最坑的地方在于有多组数据，我因此浪费了大量提交次数……

核心思路：每个点继承父亲的主席树。

```cpp
#include <cstdio>
#include <algorithm>
#define N 100001
using namespace std;
int n,m,num[N],h[N],cnt,fa[N][20],dep[N];
struct edge{
	int next,to;
}e[N<<1];
inline void adde(int u,int v)
{
	e[++cnt].next=h[u];
	h[u]=cnt;
	e[cnt].to=v;
	return;
}
inline int LCA(int x,int y);
class Presisdent_Tree{
	private:
		struct tree{
			int l,r,sum;
			tree *lson,*rson;
			inline void pushup(){sum=lson->sum+rson->sum;return;}
		}t[N*20],*tail,*null,*root[N];
		inline void init()
		{
			tail=t;
			null=tail++;//做一个null是因为懒得建初始树
			null->l=null->r=null->sum=0;
			null->lson=null->rson=null;
			for(int i=0;i<=N-1;i++)root[i]=null;
			return;
		}
		inline void insert(int l,int r,int val,tree *x,tree *&p)
		{
			p=tail++;
			*p=*x;
			p->sum++;
			if(l==r)return;
			int mid=l+r>>1;
			if(val<=mid)insert(l,mid,val,x->lson,p->lson);
			else insert(mid+1,r,val,x->rson,p->rson);
			return;
		}
		inline int ask(int l,int r,int val,tree *a,tree *b,tree *c,tree *d)
		{
			if(l==r)return a->sum+b->sum-c->sum-d->sum;
			int mid=l+r>>1;
			if(val<=mid)ask(l,mid,val,a->lson,b->lson,c->lson,d->lson);
			else ask(mid+1,r,val,a->rson,b->rson,c->rson,d->rson);
		}
		
	public:
		inline Presisdent_Tree(){init();return;}//开局の初始化
		inline void init2()//新数据の初始化
		{
			tail=t+1;
			for(int i=0;i<N;i++)root[i]=null;
			cnt=0;
			for(int i=1;i<=n;i++)h[i]=0;
			return;
		}
		inline void insert(int rot,int fa)
		{
			if(0<=num[rot]&&num[rot]<=n)insert(0,n,num[rot],root[fa],root[rot]);
			else root[rot]=root[fa];
			return;
		}
		inline int ask(int val,int x,int y)//查询链上某种颜色出现次数
		{
			int lca=LCA(x,y);
			return ask(0,n,val,root[x],root[y],root[lca],root[fa[lca][0]]);//简单容斥原理
		}
}hjt;
inline void dfs(int x)
{
	hjt.insert(x,fa[x][0]);
	for(int i=1;i<=18;i++)fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int i=h[x],v;i;i=e[i].next)
	{
		v=e[i].to;
		if(v==fa[x][0])continue;
		fa[v][0]=x;
		dep[v]=dep[x]+1;
		dfs(v);
	}
	return;
}
inline void build()
{
	dep[1]=1;
	dfs(1);
	return;
}
inline int LCA(int x,int y)//倍增求LCA
{
	if(dep[x]<dep[y])swap(x,y);
	for(int i=18;i>=0;i--)if(dep[fa[x][i]]>=dep[y])x=fa[x][i];
	if(x==y)return x;
	for(int i=18;i>=0;i--)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int main()
{
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		hjt.init2();
		for(int i=1;i<=n;i++)scanf("%d",&num[i]);
		for(int i=1,u,v;i<n;i++)
		{
			scanf("%d%d",&u,&v);
			adde(u,v),adde(v,u);
		}
		build();
		for(int i=1,u,v,w;i<=m;i++) 
		{
			scanf("%d%d%d",&u,&v,&w);
			printf("lca:%d\n",LCA(u,v));
			if(hjt.ask(w,u,v))puts("Find");
			else puts("NotFind");
		}
	}
	return 0;
}
```

---

## 作者：yukari1735 (赞：1)

给出一棵点数为 $n$ 的树，点有点权，$q$ 次询问求两点 $a,b$ 的简单路径上是否有点的点权为 $c$。

不妨先转化为序列来看，序列上求某个区间是否有元素为 $c$，直接可持久化权值树上查询叶子的值是否大于 $0$ 即可。

对于树上我们也可以类似地在树上建立可持久化权值树，序列上我们是从左到右依次插入，每棵树维护的是序列的一个前缀区间 $[1,i]$ 的值域。而在树上我们按照从根到叶子的顺序插入，每棵树维护的是从根 $s$ 到一个节点 $u$ 的路径上的值域。

于是我们就可以在这个东西上进行差分的操作，就和树上差分是一样的，对于路径 $p(u,v)$，我们先求出它们的 LCA $\phi(u,v)$，记 $\sigma(u,x)$ 为 $x$ 在根 $s$ 到节点 $u$ 的路径上的出现次数，那么 $\sigma(u,x)+\sigma(v,x)-\sigma(\phi(u,v),x)-\sigma(\mathbb{fa}[\phi(u,v)],x)$ 就是 $x$ 在 $p(u,v)$ 上的出现次数。

对于这个我们可以在四颗权值树上同时查找，单次时间复杂度 $O(\log n)$。

```cpp
//w = LCA , f = fa[ LCA ]。
int query( int u , int v , int w , int f , int l , int r , int p ){
	if( l == r ) return val( u ) + val( v ) - val( w ) - val( f );
	int mid = l + r >> 1;
	if( p <= mid ) return query( ls( u ) , ls( v ) , ls( w ) , ls ( f ) , l , mid , p );
	else return query( rs( u ) , rs( v ) , rs( w ) , rs( f ) , mid + 1 , r , p );
}
```

建树只需要对树 DFS 一遍，对于某一节点，以它的父亲为基础插入其点权即可。总时间复杂度 $O(n\log n)$。

```cpp
void dfs1( int u , int f ){
	modify( root[ u ] , root[ f ] , 0 , n , a[ u ] );
	int i; forE( u , i ){
		int v = ldt( i );
		if( v == f ) continue;
		dfs1( v , u );
	}
}
```

LCA 这部分就随意了。

注意的点是多测清空，以及含有点权 $c_i$ 为 $0$ 的节点，且 $c_i \leq n$，所以值域开到 $[0,n]$ 就可且不用离散化。

本人这里用的树剖 LCA。时间复杂度 $O((n+q)\log n)$。

Code Here：

```cpp
# include <cstdio>
# include <iostream>

namespace IO{
	inline int read(){
		int ret = 0;
		char u = getchar();
		while( ! isdigit( u ) ) u = getchar();
		while( isdigit( u ) ) ret = ret * 10 + u - '0' , u = getchar();
		return ret;
	}
}

using namespace std;

const int N = 1e5 + 225;

int n , q;
int a[ N ];

struct Edge{ int nxt , to; }edge[ N << 1 ];
int head[ N ] , eg;
inline void add_edge( int u , int v ){ edge[ ++ eg ] = { head[ u ] , v } , head[ u ] = eg; }
# define forE( u , i ) for( i = head[ u ] ; i ; i = edge[ i ] . nxt )
# define ldt( i ) edge[ i ] . to

int root[ N ] , nod;
struct Node{ int lc , rc , val; }t[ N << 5 ];
# define ls( u ) t[ u ] . lc
# define rs( u ) t[ u ] . rc
# define val( u ) t[ u ] . val

void build( int & u , int l , int r ){
	u = ++ nod;
	if( l == r ) return;
	int mid = l + r >> 1;
	build( ls( u ) , l , mid ) , build( rs( u ) , mid + 1 , r );
}

void modify( int & u , int _u , int l , int r , int p ){
	u = ++ nod , t[ u ] = t[ _u ] , ++ val( u );
	if( l == r ) return;
	int mid = l + r >> 1;
	if( p <= mid ) modify( ls( u ) , ls( _u ) , l , mid , p );
	else modify( rs( u ) , rs( _u ) , mid + 1 , r , p );
}

int dep[ N ] , fa[ N ] , siz[ N ] , ch[ N ];
void dfs1( int u , int f ){
	modify( root[ u ] , root[ f ] , 0 , n , a[ u ] );
	dep[ u ] = dep[ f ] + 1 , fa[ u ] = f , siz[ u ] = 1;
	int i; forE( u , i ){
		int v = ldt( i );
		if( v == f ) continue;
		dfs1( v , u );
		siz[ u ] += siz[ v ];
		if( siz[ v ] > siz[ ch[ u ] ] ) ch[ u ] = v;
	}
}

int tp[ N ];
void dfs2( int u , int top ){
	tp[ u ] = top;
	if( ch[ u ] ) dfs2( ch[ u ] , top );
	int i; forE( u , i ){
		int v = ldt( i );
		if( v == ch[ u ] || v == fa[ u ] ) continue;
		dfs2( v , v );
	}
}

int LCA( int u , int v ){
	while( tp[ u ] != tp[ v ] ){
		if( dep[ tp[ u ] ] < dep[ tp[ v ] ] ) swap( u , v );
		u = fa[ tp[ u ] ];
	}
	return dep[ u ] < dep[ v ] ? u : v;
}

int query( int u , int v , int w , int f , int l , int r , int p ){
	if( l == r ) return val( u ) + val( v ) - val( w ) - val( f );
	int mid = l + r >> 1;
	if( p <= mid ) return query( ls( u ) , ls( v ) , ls( w ) , ls ( f ) , l , mid , p );
	else return query( rs( u ) , rs( v ) , rs( w ) , rs( f ) , mid + 1 , r , p );
}

void solve(){
	for( int i = 1 ; i  <= q ; i ++ ){
		int u = IO :: read() , v = IO :: read() , x = IO :: read();
		int lca = LCA( u , v );
		if( query( root[ u ] , root[ v ] , root[ lca ] , root[ fa[ lca ] ] , 0 , n , x ) >= 1 ) printf( "Find\n" );
		else printf( "NotFind\n" );
	}
}

void input(){
	q = IO :: read();
	for( int i = 1 ; i <= n ; i ++ ) a[ i ] = IO :: read();
	for( int i = 1 ; i <= n - 1 ; i ++ ){
		int u = IO :: read() , v = IO :: read();
		add_edge( u , v ) , add_edge( v , u );
	}
}

void init(){
	for( int i = 1 ; i <= nod ; i ++ ) val( i ) = ls( i ) = rs( i ) = 0;
	for( int i = 1 ; i <= eg ; i ++ ) head[ i ] = ldt( i ) = edge[ i ] . nxt = 0;
	for( int i = 1 ; i <= n ; i ++ ) dep[ i ] = fa[ i ] = siz[ i ] = tp[ i ] = ch[ i ] = 0;
	nod = 0 , eg = 0;
}

int main(){
	while( scanf( "%d" , &n ) != EOF ){
		input();
		build( root[ 0 ] , 1 , n );
		dfs1( 1 , 0 );
		dfs2( 1 , 1 );
		solve();
		init();
	}
	system( "pause" );
	return 0;
}
```


---

## 作者：zhengrunzhe (赞：1)

题意：树上路径查是否有某颜色存在

#### 转化题意：树上路径某个颜色出现了多少次，看次数是不是>=1

算法1:

#### 主席树

[COT1](https://www.luogu.org/problem/P2633)

像这题这么做，差分主席树单点查询即可

时间复杂度$O(m log n)$

算法3:

#### 树剖+平衡树/动态开点线段树

每个颜色开个平衡树，插入拥有该颜色节点的dfn，树剖按dfn在颜色对应的平衡树/线段树内查区间size即可

时间复杂度$O(m log^2 n)$

算法3:

#### 树剖+vector二分

线段树/平衡树相对不好写常数大，因为不修改，考虑改成vector

每个颜色开个vector，递增插入拥有该颜色节点的dfn，二分即可

时间复杂度$O(m log^2 n)$
```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
using std::vector;
using std::lower_bound;
template<class type>inline const void read(type &in)
{
	in=0;char ch=getchar();bool f=0;
	while (ch<48||ch>57){if (ch=='-')f=1;ch=getchar();}
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
	if (f)in=-in;
}
template<class type>inline const void swap(type &a,type &b)
{
	type c=a;a=b;b=c;
}
const int N=1e5+10;
vector<int>v[N];
int col[N],n,m;
int head[N],edc,next[N<<1],to[N<<1];
inline const void link(int u,int v)
{
	next[++edc]=head[u];to[head[u]=edc]=v;
	next[++edc]=head[v];to[head[v]=edc]=u;
}
int dfn[N],top[N],wson[N],size[N],dep[N],fa[N],dfc;
inline const void dfs(int p)
{
	size[p]=1;
	for (int i=head[p];i;i=next[i])
	{
		int son=to[i];
		if (fa[p]==son)continue;
		fa[son]=p;dep[son]=dep[p]+1;
		dfs(son);size[p]+=size[son];
		if (size[son]>size[wson[p]])wson[p]=son;
	}
}
inline const void dfs(int p,int tp)
{
	top[p]=tp;
	if (col[p]>=0&&col[p]<=n)v[col[p]].push_back(dfn[p]=++dfc);
	if (wson[p])dfs(wson[p],tp);
	for (int i=head[p];i;i=next[i])
		if (!dfn[to[i]])
			dfs(to[i],to[i]);
}
inline const bool exist(int c,int l,int r)
{
	vector<int>::iterator p=lower_bound(v[c].begin(),v[c].end(),l);
	if (p==v[c].end())return 0;
	return *p<=r;
}
inline const bool query(int a,int b,int c)
{
	while (top[a]^top[b])
	{
		if (dep[top[a]]<dep[top[b]])swap(a,b);
		if (exist(c,dfn[top[a]],dfn[a]))return 1;
		a=fa[top[a]];
	}
	if (dep[a]>dep[b])swap(a,b);
	return exist(c,dfn[a],dfn[b]);
}
int main()
{
	while (scanf("%d%d",&n,&m)==2)
	{
		for (int i=1;i<=n;i++)read(col[i]);
		for (int a,b,i=1;i<n;i++)read(a),read(b),link(a,b);
		dfs(1);dfs(1,1);
		for (int a,b,c;m--;)read(a),read(b),read(c),puts(query(a,b,c)?"Find":"NotFind");
		for (int i=0;i<=n;i++)wson[i]=dfn[i]=head[i]=0,v[i].clear();
		dfc=edc=0;
	}
	return 0;
}
```


---

## 作者：KEBrantily (赞：1)

这题采用离线处理的方式。

将每个点的点权，以及每次询问的权值分别按从小到大排序。

初始我们有一棵树，每个节点都没有点权。

对于每次询问，将点权小于等于这次询问的权值的点添加上它原本的权值。然后判断一下询问的权值是否等于路径最大值，是则存在，不是则不存在。

这样我们只需要用到单点修改和区间求查询，树剖维护一下即可。

另外注意本题中 $c\ge 0$，题目可能会询问是否存在点权为 $0$ 的点，所以不要将节点初始值设为 $0$。

```cpp
int n,m,tot,cnt;
int head[maxn],ans[maxn];
int dfn[maxn],fa[maxn],top[maxn];
int siz[maxn],son[maxn],dep[maxn];
struct edge{int fr,to,nxt;}e[maxn<<1];
struct milk{
  int val,pos;
  bool operator < (const milk &b) const{
    return val<b.val;
  }
}t[maxn];
struct ques{
  int fr,to,c,pos;
  bool operator < (const ques &b) const{
    return c<b.c;
  }
}q[maxn];

namespace Seg{
  #define ls x<<1
  #define rs x<<1|1
  int maxx[maxn<<2];
  void cclear(){
    memset(maxx,-1,sizeof maxx);
  }
  
  void pushup(int x){
    maxx[x]=max(maxx[ls],maxx[rs]);
  }
  
  void update(int x,int l,int r,int pos,int val){
    if(l==r){
      maxx[x]=max(maxx[x],val);
      return;
    }
    int mid=l+r>>1;
    if(pos<=mid) update(ls,l,mid,pos,val);
    else update(rs,mid+1,r,pos,val);
    pushup(x);
  }
  
  int query(int x,int l,int r,int L,int R){
    if(L<=l&&R>=r) return maxx[x];
    int mid=l+r>>1,ans=-1;
    if(L<=mid) ans=max(ans,query(ls,l,mid,L,R));
    if(R>=mid+1) ans=max(ans,query(rs,mid+1,r,L,R));
    return ans;
  }
}

namespace Cut{
  void dfs1(int u,int fat){
    dep[u]=dep[fat]+1;
    siz[u]=1;fa[u]=fat;
    for(int i=head[u];i;i=e[i].nxt){
      int to=e[i].to;
      if(to==fat) continue;
      dfs1(to,u);siz[u]+=siz[to];
      if(siz[son[u]]<siz[to])son[u]=to;
    }
  }
  
  void dfs2(int u,int tp){
    top[u]=tp;dfn[u]=++cnt;
    if(son[u]) dfs2(son[u],tp);
    for(int i=head[u];i;i=e[i].nxt){
      int to=e[i].to;
      if(to==fa[u]||to==son[u]) continue;
      dfs2(to,to);
    }
  }
  
  int getmax(int x,int y){
    int ans=-1;
    while(top[x]!=top[y]){
      if(dep[top[x]]<dep[top[y]]) swap(x,y);
      ans=max(ans,Seg::query(1,1,n,dfn[top[x]],dfn[x]));
      x=fa[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    ans=max(ans,Seg::query(1,1,n,dfn[x],dfn[y]));
    return ans;
  }
}

void clear(){
  tot=0;cnt=0;Seg::cclear();
  memset(head,0,sizeof head);
  memset(son,0,sizeof son);
  memset(dfn,0,sizeof dfn);
  memset(siz,0,sizeof siz);
  memset(ans,0,sizeof ans);
}

int main(){
  while(scanf("%d%d",&n,&m)!=EOF){
    clear();
    for(int i=1;i<=n;i++) 
      t[i].val=read(),t[i].pos=i;
    for(int i=1,fr,to;i<n;i++){
      fr=read();to=read();
      add(fr,to);add(to,fr);
    }
    Cut::dfs1(1,0);Cut::dfs2(1,1);
    for(int i=1;i<=m;i++)
      q[i].fr=read(),q[i].to=read(),
      q[i].c=read(),q[i].pos=i;
    sort(t+1,t+n+1);sort(q+1,q+m+1);int Now=1;
    for(int i=1;i<=m;i++){
      while(Now<=n&&t[Now].val<=q[i].c){
        Seg::update(1,1,n,dfn[t[Now].pos],t[Now].val);
        Now++;
      }
      ans[q[i].pos]=(Cut::getmax(q[i].fr,q[i].to)==q[i].c);
    }
    for(int i=1;i<=m;i++) printf(ans[i]?"Find\n":"NotFind\n");
  }
  return 0;
}


```

---

## 作者：yzh_Error404 (赞：0)

显然是树剖题。

对于一个询问，我们需要知道这个区间中有没有某个颜色，考虑暴力的用 set 全部记录下来。

具体做法是对于每一个线段树的节点，暴力插入这个区间的颜色，查询的时候直接 count 即可。

时间复杂度是 $O(n\log^3n)$

代码实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=4e5+5;
struct node
{
    int to,nxt;
}e[MAXN];
int head[MAXN],cnt;
inline void add(int x,int y)
{
    e[++cnt].to=y;
    e[cnt].nxt=head[x];
    head[x]=cnt;
}
int siz[MAXN],hson[MAXN],fa[MAXN],dep[MAXN],val[MAXN];
inline void dfs1(int x,int f)
{
    fa[x]=f;
    dep[x]=dep[f]+1;
    siz[x]=1;
    int maxson=-1;
    for(register int i=head[x];i;i=e[i].nxt)
    {
        int y=e[i].to;
        if(y==f)continue;
        dfs1(y,x);
        siz[x]+=siz[y];
        if(siz[y]>maxson)
        {
            maxson=siz[y];
            hson[x]=y;
        }
    }
}
int top[MAXN],id[MAXN],nval[MAXN],now;
inline void dfs2(int x,int ltop)
{
    id[x]=++now;
    top[x]=ltop;
    nval[now]=val[x];
    if(!hson[x])return;
    dfs2(hson[x],ltop);
    for(register int i=head[x];i;i=e[i].nxt)
    {
        int y=e[i].to;
        if(y==hson[x]||y==fa[x])continue;
        dfs2(y,y);
    }
}
int n,q;
set<int>t[MAXN];
inline void build(int p,int l,int r)
{
    for(register int i=l;i<=r;i++)
        t[p].insert(nval[i]);
    if(l==r)return;
    int mid=(l+r)>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
}
inline int ask(int p,int l,int r,int a,int b,int k)
{
    if(r<a||l>b)return 0;
    if(l>=a&&r<=b)return t[p].count(k);
    int mid=(l+r)>>1;
    return ask(p<<1,l,mid,a,b,k)+ask(p<<1|1,mid+1,r,a,b,k);
}
inline int ask_ran(int x,int y,int k)
{
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]])swap(x,y);
        if(ask(1,1,n,id[top[x]],id[x],k))return 1;
        x=fa[top[x]];
    }
    if(dep[x]>dep[y])swap(x,y);
    return ask(1,1,n,id[x],id[y],k);
}
int main()
{
    
    while(scanf("%d%d",&n,&q)!=EOF)
    {
        cnt=now=0;
        memset(head,0,sizeof head);
        memset(hson,0,sizeof hson);
        for(register int i=1;i<=(n<<2);i++)
            t[i].clear();
        for(register int i=1;i<=n;i++)
            scanf("%d",&val[i]);
        for(register int i=1;i<n;i++)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            add(x,y);
            add(y,x);
        }
        dfs1(1,0);
        dfs2(1,1);
        build(1,1,n);
        for(register int i=1;i<=q;i++)
        {
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            if(ask_ran(x,y,z))puts("Find");
            else puts("NotFind");
        }
    }
    return 0;
}
```

---

## 作者：Strelitzia (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/SP11985)

---

[这道题的简单版？？](https://www.luogu.com.cn/problem/SP10628)

基本想法：树上主席树

我们想，序列上的主席树是如何求一个数是否出现，是差分的想法。

如求 $\texttt{[l,r]}$ 是用加入到 $\texttt{r}$ 的减去 $\texttt{l - 1}$ 的，剩下的就是 $\texttt{[l,r]}$ 之间的。

树上的路径也可以这样做，这里是统计点的颜色，所以用点差分。

也就是统计 $val_u + val_v - val_{lca(u,v)},val_{fa_{lca(u,v)}}$。

其实没有什么大的变化，就主要是 $\operatorname{query}$ 多传了几个参而已。

```cpp
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>void read(T &x) {
    T f = 1;x = 0;char s = getchar();
    while(s < '0' || s > '9') {if(s == '-')f = -1;s = getchar();}
    while(s >= '0' && s <= '9') {x = x * 10 + s - '0';s = getchar();}
    x *= f;
}
template<typename T>void print(T x) {
    if(x < 0) putchar('-'),x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

const int maxn = 100005;

int nxt[maxn << 1],ver[maxn << 1],head[maxn],tot;
void addEdge(int x,int y) {
	nxt[++ tot] = head[x];ver[tot] = y;head[x] = tot;
}

int l[maxn * 20],r[maxn * 20],val[maxn * 20];
int n,m,a[maxn],b[maxn],dep[maxn],root[maxn],fa[maxn][20],lg[maxn],num,cnt;

int newnode(int k) {
	l[++ cnt] = l[k];
	r[cnt] = r[k];
	val[cnt] = val[k];
	return cnt;
}

int build(int b,int e,int k) {
	k = ++ cnt;
	if (b == e) return k;
	int mid = b + e >> 1;
	l[k] = build(b,mid,l[k]);
	r[k] = build(mid + 1,e,r[k]);
	return k;
}

int update(int b,int e,int k,int x,int y) {
	k = newnode(k);
	if (b == e) val[k] += y;
	else {
		int mid = b + e >> 1;
		if (x <= mid) l[k] = update(b,mid,l[k],x,y);
		else r[k] = update(mid + 1,e,r[k],x,y);
		val[k] = val[l[k]] + val[r[k]];
	}
	return k;
}

int query(int L,int R,int fa,int faa,int b,int e,int k) {
	if (b == e) return val[L] + val[R] - val[fa] - val[faa];
	int mid = b + e >> 1;
	return mid >= k ? query(l[L],l[R],l[fa],l[faa],b,mid,k) : query(r[L],r[R],r[fa],r[faa],mid + 1,e,k);
}

int test(int L,int R,int fa,int faa,int b,int e,int k) {
	if (b == e) return b;
	int mid = b + e >> 1;
	return mid >= k ? query(l[L],l[R],l[fa],l[faa],b,mid,k) : query(r[L],r[R],r[fa],r[faa],mid + 1,e,k);
}

void dfs(int u,int faa) {
	fa[u][0] = faa;
	dep[u] = dep[faa] + 1;
	root[u] = update(1,num,root[faa],a[u],1);
	for (int i = 1 ; i <= lg[dep[u]]; ++ i) fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for (int i = head[u] ; i ; i = nxt[i]) {
		int v = ver[i];
		if (v == faa) continue;
		dfs(v,u);
	}
}

int LCA(int x, int y) {
	if(dep[x] < dep[y]) {
		int tmp = x;
		x = y;
		y = tmp;
	}
	while(dep[x] > dep[y]) x = fa[x][lg[dep[x] - dep[y]] - 1];
	if(x == y) return x;
	for(int k = lg[dep[x]] - 1; ~k ; --k)
		if(fa[x][k] != fa[y][k])
			x = fa[x][k], y = fa[y][k];
	return fa[x][0];
}

int main () {
	while (~scanf("%d",&n)) {
		memset(head,0,sizeof head);
		memset(val,0,sizeof val);
		memset(l,0,sizeof l);
		memset(r,0,sizeof r);
		tot = 0;num = n;
		
		read(m);
		
		for (int i = 1 ; i <= n ; ++ i) read(a[i]),b[i] = a[i],lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
		sort(b + 1,b + 1 + n);
		num = unique(b + 1,b + 1 + n) - b - 1;
		for (int i = 1 ; i <= n ; ++ i) a[i] = lower_bound(b + 1,b + 1 + num,a[i]) - b;
		
		root[0] = build(1,num,0);
		
		int x,y,k;
		for (int i = 1 ; i < n ; ++ i) {
			read(x);read(y);
			addEdge(x,y);addEdge(y,x);
		}
		
		dfs(1,0);
		
		for (int i = 1 ; i <= m ; ++ i) {
			read(x);read(y);read(k);
			int lca = LCA(x,y);
			int p = lower_bound(b + 1,b + num + 1,k) - b;
			if (b[p] == k) puts(query(root[x],root[y],root[lca],root[fa[lca][0]],1,num,p) ? "Find" : "NotFind");
			else puts("NotFind");
		}
	}
	return 0;
}
```

---

