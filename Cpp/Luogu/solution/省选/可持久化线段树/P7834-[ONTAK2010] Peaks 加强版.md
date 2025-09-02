# [ONTAK2010] Peaks 加强版

## 题目背景

原题链接：[P4197 Peaks](https://www.luogu.com.cn/problem/P4197)

## 题目描述

给定一张 $n$ 个点、$m$ 条边的无向图，第 $i$ 个点的权值为 $a_i$，边有边权。

有 $q$ 组询问，每组询问给定三个整数 $u, x, k$，求从 $u$ 开始只经过权值 $\leq x$ 的边所能到达的权值第 $k$ 大的点的权值，如果不存在输出 $-1$。

**本题强制在线。即：每次查询输入的是 $u', x', k'$，则 $u = (u' \operatorname{xor} \text{lastans}) \bmod n + 1$，$k$ 的解密方式与之相同，$x = x' \operatorname{xor} \text{lastans}$**。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq n \leq 10^5$，$0 \leq m, q \leq 5 \times 10^5$，$1 \leq s, t \leq n$，$1 \leq a_i, w \leq 10^9$，$0 \leq u', x', k' < 2^{31}$。

## 样例 #1

### 输入

```
10 11 3
1 2 3 4 5 6 7 8 9 10
1 4 4
2 5 3
9 8 2
7 8 10
7 1 4
6 7 1
6 4 8
2 1 5
10 8 10
3 4 7
3 4 6
0 5 5
1 6 8
7 8 1```

### 输出

```
1
-1
8```

# 题解

## 作者：LawrenceSivan (赞：26)

# _Kruskal 重构树_

updated：感谢 @cyffff 指出错误

## 前言

听了 @[Wankupi](https://www.luogu.com.cn/user/128771) 学长讲了这个东西。

于是就爬过来学了。

确实是很有意思的东西。

不过貌似也很小众，几乎不咋用。

但是性质确实很优美。

特殊的题目也有奇效。

## 前置知识

1. _Kruskal_ 算法求解最小生成树。

2. 倍增

3. 主席树

至于为什么需要这些玩意，~~其实并不必要~~

在题目里会用到的。

## 定义

这个东西我找遍了各大词条，并没有一个合适的定义。

于是可以跳过。


## 实现过程

在执行 _kruskal_ 的过程中，我们先将边进行排序（排序的方式决定了重构树的性质），之后遍历每一条边，查看这条边的两个端点是否在同一个并查集之内。如果不在，那么就新建一个节点 $node$,**这个点的点权等于这条边的边权**。

有一张图画的好啊！

![](https://cdn.luogu.com.cn/upload/image_hosting/kbflkzrt.png)

图片来源：@[asd369 ](https://www.luogu.com.cn/blog/asd369-zzh/p4197-peaks)



具体做法：

首先找到两个端点在并查集中的根，之后检查是否在一个并查集中。然后连边就可以了。

```cpp
namespace Kruskal{
	inline void add(int u,int v){
		nxt[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
	}
	
	struct node{
		int u,v,dis;
		
		inline bool operator < (const node &a)const{
			return dis<a.dis;
		}
	}e[maxm<<1];

	int ff[maxn];
	
	inline void init(){
		for(re int i=1;i<maxn;i++){
			ff[i]=i;
		}
	}
	
	int find(int x){
		return x==ff[x]?x:ff[x]=find(ff[x]);
	}
	
	int val[maxn<<1],tot;
	
	inline void kruskal(){
		sort(e+1,e+1+m);
		
		init();
		
		for(re int i=1;i<=m;i++){
			int x=find(e[i].u),y=find(e[i].v);
			if(x!=y){
				val[++tot]=e[i].dis;
				ff[x]=ff[y]=ff[tot]=tot;
				add(tot,x);add(tot,y);
				fa[x][0]=fa[y][0]=tot;
			}
		}
	}
	
}
```

## 性质

- 1. _Kruskal_ 重构树是一棵树（~~这不是废话？！~~

而且他还是一棵二叉树（~~虽然看上去也是废话~~

还是一棵有根树，根节点就是最后新建的节点。

- 2. 若原图不连通，那么建出来的 _Kruskal_ 重构树就是一个森林。

- 3. 如果一开始按照边权升序排序，那么建出的 _Kruskal_ 重构树就是一个大根堆，反之就是小根堆。

- 4. 若一开始按照边权升序排序，那么 `lca(u,v)` 的权值代表了原图中 $u$ 到 $v$ 路径上最大边权的最小值。反之就是最小边权的最大值。

- 5. _Kruskal_ 重构树中的叶子结点必定是原图中的节点，其余的节点都是原图的一条边。

- 6. _Kruskal_ 重构树建好以后会比原图多出 $n-1$ 个节点（如果原图联通的话）

一条一条来看：

对于性质 $1$ 和 $2$，比较显然，我们就不说了。

对于性质 $3$ 和 $4$，由于一开始对边权升序排序，所以我们首先遍历到的边一定是权值最小的。

于是对于 _Kruskal_ 重构树中的某一个节点，它的子树中任意一个节点的权值一定小于它本身。

那么可以知道，权值越小的深度越大，权值越大的深度越小。

于是这是大根堆性质。

有了大根堆性质，我们可以发现，由于边权升序，其实就是求解最小生成树的过程，于是能出现在 _Kruskal_ 重构树中的节点必然是要满足也出现在原图的最小生成树中的，那么在找 `LCA` 的过程中，找到的必然是在 _Kruskal_ 重构树上这条路径中深度最小的点，也就是权值最大的。对于原图来说，这个权值最大的恰好是从 $u$ 到 $v$ 最小值。

>若一个点能通过一条路径到达，那么我们走最小生成树上的边也一定能到达该节点。

于是满足了最大值最小的性质。

同理降序也能够得出最小值最大的性质。

对于性质 $5$，可以画图解决。

对于性质 $6$，可以发现，建出 _Kruskal_ 重构树的过程其实也就是求解最小生成树的过程，那么 _Kruskal_ 重构树中新增加的节点数也就是最小生成树中的边数。而最小生成树中的边数最多是 $n-1$ 条，于是 _Kruskal_ 重构树中新增加的节点数也就是   $n-1$ 个。 

## 应用

根据上面的性质们，_Kruskal_ 重构树有几种常见用法：

### u->v路径上的最大值最小 or u->v路径上的最小值最大

这就是上面的性质 $3$ 和 $4$ 了。

于是直接套板子就行了。

也给我们一个提示，遇到这种**最大值最小**或者**最小值最大**这种类似的语句，可以不急着想二分，还可以想想 _Kruskal_ 重构树。

例题就是 [P1967 [NOIP2013 提高组] 货车运输](https://www.luogu.com.cn/problem/P1967)

求解路径上最小值最大。

将边降序排序，建出 _Kruskal_ 重构树，注意处理一下有可能是个森林。

`lca` 怎么搞都行，不过我喜欢树剖，比较优雅。

查询在 _Kruskal_ 重构树中 `lca(u,v)` 的权值就好了。

```cpp
//#define LawrenceSivan

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define re register
const int maxn=1e5+5;
#define INF 0x3f3f3f3f

int n,m,tot,q;

struct node{
	int u,v,dis;

	inline bool operator < (const node &a)const{
		return dis>a.dis;
	}
}a[maxn<<1];

int head[maxn],to[maxn<<1],nxt[maxn<<1],cnt;

int val[maxn<<1];

inline void add(int u,int v){
	to[++cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
}

int dep[maxn],size[maxn],fa[maxn],son[maxn],top[maxn];

bool vis[maxn];

void dfs1(int u,int f){
	size[u]=1;
	vis[u]=true;
	fa[u]=f;
	dep[u]=dep[f]+1;
	for(re int i=head[u];i;i=nxt[i]){
		int v=to[i];
		if(v==f)continue;
		dfs1(v,u);
		size[u]+=size[v];
		if(size[v]>size[son[u]])son[u]=v;
	}
}

void dfs2(int u,int topf){
	top[u]=topf;
	if(!son[u])return;
	dfs2(son[u],topf);
	for(re int i=head[u];i;i=nxt[i]){
		int v=to[i];
		if(v==fa[u]||v==son[u])continue;
		dfs2(v,v);
	}
}

inline int lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}

int ff[maxn];

int find(int x){
	return x==ff[x]?x:ff[x]=find(ff[x]);
}

inline void init(){
	for(re int i=1;i<maxn;i++){
		ff[i]=i;
	}
}

inline void Kruskal(){
	sort(a+1,a+1+m);

	init();

	for(re int i=1;i<=m;i++){
		int x=find(a[i].u),y=find(a[i].v);
		if(x!=y){
			val[++tot]=a[i].dis;
			ff[tot]=ff[x]=ff[y]=tot;
			add(tot,x);
			add(tot,y);
		}
	} 

	for(re int i=1;i<=tot;i++){
		if(!vis[i]){
			int f=find(i);
			dfs1(f,0);
			dfs2(f,f);
		}
	}
}

inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

int main(){
#ifdef LawrenceSivan
    freopen("aa.in","r",stdin);
    freopen("aa.out","w",stdout);
#endif
    n=read();m=read();tot=n;

    for(re int i=1;i<=m;i++){
    	a[i].u=read();a[i].v=read();a[i].dis=read();
    }

    Kruskal();

    q=read();
    while(q--){
		int u=read(),v=read();
		if(find(u)!=find(v))puts("-1");
		else printf("%d\n",val[lca(u,v)]);
    }



	return 0;
}
```

### 从 u 出发只经过边权不超过 x 的边能到达的节点

根据性质 $3$，可以发现，只需要找到边权升序的 _Kruskal_ 重构树中找到深度最小的，点权不超过 $x$ 的节点，那么这个节点的子树即为所求。

找这个点一般用树上倍增

我不要！！！！~~树剖党声嘶力竭~~

没办法这玩意还是倍增好

我们考虑当前我们找到的这个节点为 $x$，然后我们倍增枚举它的祖先，由于是升序排序，所以它祖先的点的点权必然大于等于它的点权，于是，我们倍增的时候只要判断如果它的祖先的点权就好了。

```cpp
inline void kruskal(){
		sort(e+1,e+1+m);
		
		init();
		
		for(re int i=1;i<=m;i++){
			int x=find(e[i].u),y=find(e[i].v);
			if(x!=y){
				val[++tot]=e[i].dis;
				ff[x]=ff[y]=ff[tot]=tot;
				add(tot,x);add(tot,y);
				fa[x][0]=fa[y][0]=tot;
			}
		}
		dfs(tot);
	}


namespace BIN{
	int fa[maxn<<1][21],range[maxn<<1][2];

	void dfs(int u){
		for(re int i=1;i<=20;i++){
			fa[u][i]=fa[fa[u][i-1]][i-1];
		}
		
		...
	}
}

int main(){
	while(q--){
		int u=read(),x=read();
		for(re int i=20;~i;i--){
			if(fa[u][i]&&val[fa[u][i]]<=x)v=fa[u][i];
		}
	}
}
```

大概就是这样的。

例题：[P4197 Peaks](https://www.luogu.com.cn/problem/P4197) & [P7834 [ONTAK2010] Peaks 加强版](https://www.luogu.com.cn/problem/P7834)

这个题其实也能用线段树合并做。（指的是前面那个，这个题是强制在线的，用不了线段树合并，感谢@cyffff 指出错误）

主体思路是裸的，多出来的就是一个第 $k$ 大。

~~这就是为啥我说需要主席树当做前置知识~~

然后子树区间第 $k$ 大，dfs 序 + 主席树大力维护就行了。

码农题，不好，思维题，好！

~~但是思维题不会做嘤嘤嘤~~

其实还是有很多细节问题的。

首先问题就是关于无解情况的判断。

肯定是对于一个满足条件的子树，子树中节点个数不足 $k$ 个。

需要注意的是，由于 _Kruskal_ 重构树的性质 $5$，我们知道在 _Kruskal_ 重构树中只有叶子节点才是会对答案产生贡献的，于是我们需要统计的子树大小并不是我们以往统计的那样，而是只统计叶子节点。

实现也很简单：

```cpp
void dfs(int u){
    for(re int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa[u][0])continue;
        fa[v][0]=u;
        dfs(v);
        size[u]+=size[v];
    }
    if(!size[u])size[u]=1;
}
```

剩下的部分其实就好说很多了。

注意一下离散化就行了。

```cpp
//#define LawrenceSivan

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define re register
const int maxn=2e5+5;
const int maxm=5e5+5;
#define INF 0x3f3f3f3f

int n,m,q,tmp,num,last;

int a[maxn],b[maxn]; 

int head[maxn<<1],to[maxn<<1],nxt[maxn<<1],cnt;


namespace SegmentTree{
    inline void Discretization(){
        sort(b+1,b+1+n);
        tmp=unique(b+1,b+1+n)-b-1;
        for(re int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+1+tmp,a[i])-b;
    }

    struct SegmentTree{
        int lc,rc,v;
        #define ls(x) st[x].lc
        #define rs(x) st[x].rc
    }st[maxn<<6];

    int segtot,root[maxn<<1];

    void build(int &rt,int l,int r){
        rt=++segtot;
        if(l==r)return;

        int mid=(l+r)>>1;
        build(ls(rt),l,mid);
        build(rs(rt),mid+1,r);
    }

    int modify(int rt,int l,int r,int x){
        int t=++segtot;
        ls(t)=ls(rt),rs(t)=rs(rt);
        st[t].v=st[rt].v+1;

        if(l==r)return t;

        int mid=(l+r)>>1;
        if(x<=mid)ls(t)=modify(ls(t),l,mid,x);
        else rs(t)=modify(rs(t),mid+1,r,x);

        return t;
    }

    int query(int x,int y,int l,int r,int k){
        int xx=st[rs(y)].v-st[rs(x)].v;

        if(l==r)return l;

        int mid=(l+r)>>1;
        if(k<=xx)return query(rs(x),rs(y),mid+1,r,k);
        else return query(ls(x),ls(y),l,mid,k-xx);
    }
    
}

using namespace SegmentTree;

namespace BIN{
    int fa[maxn<<1][30],pos[maxn<<1],st1[maxn<<1],ed[maxn<<1],size[maxn<<1];

    void dfs(int u){
        pos[++num]=u;st1[u]=num;
        for(re int i=1;i<=25;i++){
            fa[u][i]=fa[fa[u][i-1]][i-1];
        }
        for(re int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v==fa[u][0])continue;
            fa[v][0]=u;
            dfs(v);
            size[u]+=size[v];
        }
        if(!size[u])size[u]=1;
        ed[u]=num;
    }
}

using namespace BIN;

namespace Kruskal{
    inline void add(int u,int v){
        nxt[++cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt;
    }
    
    struct node{
        int u,v,dis;
        
        inline bool operator < (const node &a)const{
            return dis<a.dis;
        }
    }e[maxm];

    int ff[maxn<<1];
    
    inline void init(){
        for(re int i=1;i<maxn;i++){
            ff[i]=i;
        }
    }
    
    int find(int x){
        return x==ff[x]?x:ff[x]=find(ff[x]);
    }
    
    int val[maxn<<1],tot;

    inline void kruskal(){
        sort(e+1,e+1+m);
        
        init();
        
        for(re int i=1;i<=m;i++){
            int x=find(e[i].u),y=find(e[i].v);
            if(x!=y){
                val[++tot]=e[i].dis;
                ff[x]=ff[y]=ff[tot]=tot;
                add(tot,x);add(tot,y);
            }
        }
        
        dfs(tot);
    }
    
}

using namespace Kruskal;

inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

int main(){
#ifdef LawrenceSivan
    freopen("aa.in","r",stdin);
    freopen("aa.out","w",stdout);
#endif
    n=read();m=read();q=read();tot=n;
    for(re int i=1;i<=n;i++){
        a[i]=b[i]=read();
    }

    Discretization();
    
    for(re int i=1;i<=m;i++){
        e[i].u=read();
        e[i].v=read();
        e[i].dis=read();
    }
    
    kruskal();

    for(re int i=1;i<=tot;i++){
        root[i]=root[i-1];
        if(pos[i]<=n)root[i]=modify(root[i-1],1,tmp,a[pos[i]]);
     }
    
    while(q--){
        int v=read(),x=read(),k=read();
        v=(v^last)%n+1;k=(k^last)%n+1;x=x^last;
        for(re int i=25;~i;i--){
            if(fa[v][i]&&val[fa[v][i]]<=x)v=fa[v][i];
        }
        if(size[v]<k){
            puts("-1");
            last=0;
            continue;
        }
        else printf("%d\n",last=b[query(root[st1[v]-1],root[ed[v]],1,tmp,k)]);
    }
    
    
    return 0;
}
```

---

## 作者：Gao_yc (赞：12)

[题目传送门](https://www.luogu.com.cn/problem/P7834)

### 前置芝士：Kruskal 重构树、主席树。

### $ \mathcal{Solution} $：

看到只经过权值 $\le x$ 的边可以想到建立 Kruskal 重构树。

然后对于重构树中 点 $u$ 的任意权值 $\le x$ 的祖先节点，其子树中的点必定可以由 $u$ 经过权值 $\le x$ 的边到达，因此我们只要找到深度最小的祖先节点满足点权（重构树中的） $\le x$，很容易通过树上倍增实现。

找到这个祖先节点后，问题转化为求重构树中一个子树中原先点权第 $k$ 大的点的点权。

子树可以转化为 dfs 序上的一段区间，也就是求重构树的 dfs 序的静态区间第 $k$ 大。

静态区间第 $k$ 大、强制在线，经典的不能再经典的主席树了。

时间复杂度 $\mathcal{O}(m \log m)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
const int inf=0x3f3f3f3f;
int n,m,q,a[N],b[N],aa[N],cnt,ans;//a 数组是原图中的点权，aa数组是重构树中的点权
int s[N];
int dfn[N],en[N],tot;
int fa[N];
int f[N][25];
int ch[N][2];
struct edge
{
	int u,v,w;
}e[N];
bool cmp(edge A,edge B){return A.w<B.w;}
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void dfs(int x)
{
	if(!x) return;
	for(int i=1;i<=20;++i) f[x][i]=f[f[x][i-1]][i-1];
	dfn[x]=++tot;
	s[tot]=a[x];
	dfs(ch[x][0]);
	dfs(ch[x][1]);
	en[x]=tot;
}
void kruskal()
{
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=2*n;++i) fa[i]=i;
	cnt=n;
	for(int i=1;i<=m;++i)
	{
		int fu=find(e[i].u),fv=find(e[i].v);
		if(fu==fv) continue;
		aa[++cnt]=e[i].w;
		fa[fu]=fa[fv]=cnt;
		ch[cnt][0]=fu;ch[cnt][1]=fv;
		f[fu][0]=f[fv][0]=cnt;
	}
	for(int i=1;i<=cnt;++i) if(fa[i]==i) dfs(i);
}
//以下为主席树 
int cnt2,r[N],t[N<<5],L[N<<5],R[N<<5];
int build(int l,int r)
{
	int rt=++cnt2,mid=(l+r)>>1;
	if(l==r) return rt;
	L[rt]=build(l,mid);
	R[rt]=build(mid+1,r);
	return rt;
}
int update(int pre,int l,int r,int k)
{
	if(!k) return pre;
	int rt=++cnt2,mid=(l+r)>>1;
	t[rt]=t[pre]+1,L[rt]=L[pre],R[rt]=R[pre];
	if(l==r) return rt;
	if(k<=mid) L[rt]=update(L[pre],l,mid,k);
	else R[rt]=update(R[pre],mid+1,r,k);
	return rt;
}
int query(int u,int v,int l,int r,int k)
{
	if(l==r) return l;
	if(t[v]-t[u]<k) return 0;
	int x=t[R[v]]-t[R[u]],mid=(l+r)>>1;
	if(x<k) return query(L[u],L[v],l,mid,k-x);
	else return query(R[u],R[v],mid+1,r,k);
}
//以上为主席树 
int main()
{
//	freopen("","r",stdin);
//	freopen("","w",stdout);
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;++i) scanf("%d",a+i),b[i]=a[i];
	sort(b+1,b+n+1);
	int nn=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;++i) a[i]=lower_bound(b+1,b+nn+1,a[i])-b;
	for(int i=1;i<=m;++i) scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
	aa[0]=inf;
	kruskal();
	r[0]=build(1,nn);
	for(int i=1;i<=cnt;++i) r[i]=update(r[i-1],1,nn,s[i]);
	int u,x,k;
	while(q--)
	{
		scanf("%d%d%d",&u,&x,&k);
		u=(u^ans)%n+1,x^=ans,k=(k^ans)%n+1;
		for(int i=20;i>=0;--i) if(f[u][i]&&aa[f[u][i]]<=x) u=f[u][i];
		ans=b[query(r[dfn[u]-1],r[en[u]],1,nn,k)];
		if(!ans) puts("-1");
		else printf("%d\n",ans);
	}
    return 0;
}

```


---

## 作者：ExplodingKonjac (赞：6)

### [【原题链接】](https://www.luogu.com.cn/problem/P7834)

## 题目分析

墙裂建议先做完 [$\text{Peaks}$](https://www.luogu.com.cn/problem/P4197)

看到题解区全部都是 Kruskal 重构树，然而蒟蒻表示并不会 qwq。

我们知道不加强制在线的 Peaks 是可以使用暴力并查集+离线+线段树合并水过的。（说句闲话，我的这种写法在 Peaks 拿了最优解，此时 $2021.9.18$。）

方法就是，给每个点开一棵权值线段树，然后从小到大把边和询问排序，依次加边并处理询问。我们可以用并查集来处理连通块的信息，每次合并时同时将两个线段树也合并。查询时就可以直接在线段树上二分找第 $k$ 大。

有了强制在线后，一般的处理就是使用可持久化。将并查集和其内层的线段树都进行可持久化处理，按照边权从小到大添加，每加入一条边就建立一个新的版本，查询时可以使用二分查找找出应查询的相应版本。

思路很简单，但是代码实现和调试难度就。。。

## 代码实现

此代码可 $127.59\text{MB}$ 极限过题
```cpp
#include <bits/stdc++.h>
using namespace std;

/*
  省略100多行的快读快些模板
  即以下代码中的qin、qout
*/

int n,m,q,maxx,ans,a[100005],b[100005],zt[500005];
struct Edge
{
	int u,v,w;
	inline bool operator <(const Edge &b)const
		{ return w<b.w; }
}e[500005];

class PersistantSegTree
{
 private:
	static struct TreeNode{ int sum,lc,rc; }t[5000005];
	static int cnt;
	int rt;
	static void __merge(int &dst,int &src)
	{
		if(!dst || !src)	dst|=src;
		else
		{
			t[++cnt]=t[dst],dst=cnt;
			__merge(t[dst].lc,t[src].lc);
			__merge(t[dst].rc,t[src].rc);
			t[dst].sum+=t[src].sum;
		}
	}
	static void __modify(int p,int &i,int l=1,int r=maxx)
	{
		t[i?i:(i=++cnt)].sum++;
		if(l!=r)
		{
			int mid=(l+r)>>1;
			if(mid>=p)	__modify(p,t[i].lc,l,mid);
			else	__modify(p,t[i].rc,mid+1,r);
		}
	}
	static int __getKth(int k,int i)
	{
		int l=1,r=maxx,mid,sz;
		if(k>t[i].sum || k<1)	return -1;
		while(l<r)
		{
			mid=(l+r)>>1,sz=t[t[i].rc].sum;
			if(sz>=k)	i=t[i].rc,l=mid+1;
			else	k-=sz,i=t[i].lc,r=mid;
		}
		return b[l];
	}
 public:
	PersistantSegTree(): rt(0){}
	inline void merge(PersistantSegTree &b)
		{ __merge(rt,b.rt); }
	inline void modify(int p)	{ __modify(p,rt); }
	inline int getKth(int k)	{ return __getKth(k,rt); }
};
PersistantSegTree::TreeNode PersistantSegTree::t[]={};
int PersistantSegTree::cnt=0;

class PersistantUnionSet
{
 private:
	struct TreeNode
	{
		int fa,dep,lc,rc;
		PersistantSegTree tr;
	}t[4000005];
	int cnt,rt[500005];
	void __build(int l,int r,int &i)
	{
		i=++cnt;
		if(l==r)
		{
			t[i].fa=l,t[i].dep=1;
			t[i].tr.modify(lower_bound(b+1,b+maxx+1,a[l])-b);
		}
		else
		{
			int mid=(l+r)>>1;
			__build(l,mid,t[i].lc),__build(mid+1,r,t[i].rc);
		}
	}
	void modify(int p,int x,int &i,int l=1,int r=n)
	{
		t[++cnt]=t[i],i=cnt;
		if(l==r)	t[i].fa=x;
		else
		{
			int mid=(l+r)>>1;
			if(mid>=p)	modify(p,x,t[i].lc,l,mid);
			else	modify(p,x,t[i].rc,mid+1,r);
		}
	}
	int query(int p,int i,int l=1,int r=n)
	{
		if(l==r)	return i;
		else
		{
			int mid=(l+r)>>1;
			if(mid>=p)	return query(p,t[i].lc,l,mid);
			else	return query(p,t[i].rc,mid+1,r);
		}
	}
 public:
	PersistantUnionSet(): cnt(0){ memset(t,0,sizeof(t)); }
	inline void build()	{ __build(1,n,rt[0]); }
	inline void update(int v)	{ rt[v]=rt[v-1]; }
	inline int findFa(int x,int v)
	{
		int f=t[query(x,rt[v])].fa;
		return x==f?x:findFa(f,v);
	}
	inline void link(int x,int y,int v)
	{
		x=findFa(x,v),y=findFa(y,v);
		if(x==y)	return;
		int &r=rt[v],dx=t[query(x,r)].dep,dy=t[query(y,r)].dep;
		if(dx<dy)	swap(x,y);
		int i;
		modify(y,x,r),modify(x,x,r);
		t[i=query(x,r)].tr.merge(t[query(y,r)].tr);
		if(dx==dy)	t[i].dep++;
	}
	inline int getKth(int x,int k,int v)
		{ return t[query(findFa(x,v),rt[v])].tr.getKth(k); }
}s;

int main()
{
	qin>>n>>m>>q;
	for(int i=1;i<=n;i++)	qin>>a[i],b[i]=a[i];
	for(int i=1;i<=m;i++)	qin>>e[i].u>>e[i].v>>e[i].w;
	sort(b+1,b+n+1),maxx=unique(b+1,b+n+1)-b-1;
	s.build(),sort(e+1,e+m+1);
	for(int i=1;i<=m;i++)
		s.update(i),s.link(e[i].u,e[i].v,i),zt[i]=e[i].w;
	while(q--)
	{
		int x,y,k,i;
		qin>>x>>y>>k;
		x=(x^ans)%n+1,k=(k^ans)%n+1,y^=ans;
		i=upper_bound(zt+1,zt+m+1,y)-zt-1;
		qout.writeln(ans=s.getKth(x,k,i));
		if(ans==-1)	ans=0;
	}
	return 0;
}

```


---

## 作者：ZCETHAN (赞：5)

[传送门](https://www.luogu.com.cn/problem/P7834)
## 题目大意
感觉题目描述已经足够清楚了。
## Solution
这道题需要的东西有点多，我们不妨先来分解一下题目的需求。

- 经过权值 $\le x$ 的边所能到达的点。

马上想到最小生成树，很明显了，和货车运输一样。不赘述了。

- 所有点中权值第 $k$ 大。

好的，又是裸的静态区间第 $k$ 大。由于是强制在线，所以一发主席树就结束了。

好接下来我们把这两个玩意儿结合一下，哦，然后我们掏出一个克鲁斯卡尔重构树就做完了。

>我是 fyy，我一眼秒了，感觉这题没啥技巧啊。

好的我具体讲一下。我们对于图做一次重构树，然后在大法师的时候顺便记一下每个节点子树中涵盖的叶节点的 $dfn$ 区间，并据此建主席树，然后直接回答询问就可以了，还是比较模板的，注意细节就可以了。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf (1<<30)
#define INF (1ll<<60)
using namespace std;
const int MAXN=3e6+10;
struct Tree{
	int l,r,ls,rs;
	int sum;
}tr[MAXN];
int ntot,T[MAXN];
int build(int l,int r){
	int i=++ntot;
	tr[i].l=l;tr[i].r=r;
	if(l==r) return i;
	int mid=l+r>>1;
	tr[i].ls=build(l,mid);
	tr[i].rs=build(mid+1,r);
	return i;
}
int upd(int pre,int x){
	int i=++ntot;
	tr[i]=tr[pre];tr[i].sum++;
	if(tr[i].l==tr[i].r) return i;
	int mid=tr[i].l+tr[i].r>>1;
	if(x<=mid) tr[i].ls=upd(tr[pre].ls,x);
	else tr[i].rs=upd(tr[pre].rs,x);
	return i;
}
int query(int L,int R,int k){
	if(tr[L].l==tr[L].r) return tr[L].l;
	int dif=tr[tr[R].ls].sum-tr[tr[L].ls].sum;
	if(k<=dif) return query(tr[L].ls,tr[R].ls,k);
	else return query(tr[L].rs,tr[R].rs,k-dif);
}//主席树求区间第 k 小
struct Edge{
	int x,y,w;
	void input(){
		scanf("%d%d%d",&x,&y,&w);
	}bool friend operator<(Edge a,Edge b){
		return a.w<b.w;
	}
}E[MAXN];
int to[MAXN],head[MAXN],nxt[MAXN],edgec;
void add(int u,int v){
	to[++edgec]=v;
	nxt[edgec]=head[u];
	head[u]=edgec;
}
int f[MAXN],h[MAXN],lsh[MAXN],val[MAXN],num;
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
int fa[MAXN][20],lb[MAXN],rb[MAXN],tot;
void dfs(int x,int fat){
	fa[x][0]=fat;
	for(int i=1;i<20;i++)
		fa[x][i]=fa[fa[x][i-1]][i-1];
	lb[x]=tot;
	if(head[x]==-1){
		lb[x]=tot;rb[x]=++tot;//包含子节点的区间，注意是左开右闭的
		T[tot]=upd(T[tot-1],lower_bound(lsh+1,lsh+1+num,h[x])-lsh);
		return;
	}
	for(int i=head[x];~i;i=nxt[i])
		dfs(to[i],x);
	rb[x]=tot;
}
int main()
{
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++)
		scanf("%d",&h[i]),lsh[i]=h[i];
	sort(lsh+1,lsh+1+n);
	num=unique(lsh+1,lsh+1+n)-lsh-1;
	for(int i=1;i<=m;i++)
		E[i].input();
	sort(E+1,E+1+m);
	for(int i=1;i<=n+m;i++)
		f[i]=i;
	int cnt=n;
	memset(val,0,sizeof(val));
	memset(head,-1,sizeof(head));
	for(int i=1;i<=m;i++){
		int fx=find(E[i].x),fy=find(E[i].y);
		if(fx==fy) continue;
		f[fx]=f[fy]=++cnt;
		add(cnt,fx);add(cnt,fy);
		val[cnt]=E[i].w;
	}T[0]=build(1,num);
	dfs(cnt,0);
	int lastans=0; val[0]=0x3f3f3f3f;
	for(int _=1;_<=q;_++){
		int v,x,k;
		scanf("%d%d%d",&v,&x,&k);
		v=(v^lastans)%n+1;k=(k^lastans)%n+1;
		x=x^lastans;
		for(int i=19;i>=0;i--)
			if(fa[v][i]&&val[fa[v][i]]<=x)
				v=fa[v][i];
		int l=lb[v],r=rb[v];
		if(r-l<k) puts("-1"),lastans=0;
		else printf("%d\n",lastans=lsh[query(T[l],T[r],r-l-k+1)]);//求第 k 大，就是求第 len-k 小
	}
}
```
# End

---

## 作者：peterwuyihong (赞：3)

[前置芝士](https://www.luogu.com.cn/blog/Peterprpr/p1967-noip2013-ti-gao-zu-huo-ju-yun-shu-ji-lu)

题意：给一个无向图，每个点存在一个点权，进行若干次强制在线询问，从点 $u$ 出发，只经过权值 $\le x$ 的边，到达第 $k$ 大的点。

你先做出来一个 $\text{Kruskal}$ 重构树，边权从小到大排序，建出来一个顶上点权代表拥有这个点权，你可以在这个子树下的点构成的图里随便走。

然后对于每次询问倍增地跳父亲，一直跳到一个点权 $\le x$ 的最浅点，这样这个点的子树就是可以走到的点。

然后你维护主席树，用 $\text{dfn}$ 序跑就行了。

现在是 $18:35$，我看我什么时候写完。

现在是 $20:00$，我写完了。

```cpp
#define maxn 1000010
int n,m,Q;
int a[maxn],b[maxn];
int head[maxn],Next[maxn<<1],ver[maxn<<1],tot;
void add(int x,int y){
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
}
struct prpr{
	int x,y,z;
}q[maxn];
int fa[maxn],rk[maxn];
int get(int x){
	if(x==fa[x])return x;
	return fa[x]=get(fa[x]);
}
int fx,fy,cnt;
int siz[maxn];
int t,FA[maxn][20];
struct qrqr{
	int lc,rc,sm;
}tree[maxn*24];
int _g_;
int rt[maxn];
int insert(int now,int pos,int l=1,int r=b[0]){
	int rt=++_g_;
	tree[rt]=tree[now];tree[rt].sm++;
	if(l==r)return _g_;
	int mid=(l+r)>>1;
	if(pos<=mid)tree[rt].lc=insert(tree[now].lc,pos,l,mid);
	else tree[rt].rc=insert(tree[now].rc,pos,mid+1,r);
	return rt;
}
int ask(int p,int q,int k,int l=1,int r=b[0]){
	if(l==r)return l;
	int cnt=tree[tree[q].lc].sm-tree[tree[p].lc].sm;
	int mid=(l+r)>>1;
	if(k<=cnt)return ask(tree[p].lc,tree[q].lc,k,l,mid);
	return ask(tree[p].rc,tree[q].rc,k-cnt,mid+1,r);
}
int dfn[maxn],____;
void dfs(int x){
	dfn[x]=++____;
	rk[____]=x;
	siz[x]=1;
	for(int i=head[x];i;i=Next[i]){
		int y=ver[i];
		FA[y][0]=x;
		for(int j=1;j<=t;j++)FA[y][j]=FA[FA[y][j-1]][j-1];
		dfs(y);
		siz[x]+=siz[y];
	}
}
int u,x,k,cc,lst;
int val[maxn];
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
	cin>>n>>m>>Q;
	for(int i=1;i<=n;i++)cin>>a[i],b[i]=a[i];
	sort(b+1,b+n+1);
	b[0]=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+b[0]+1,a[i])-b;
	for(int i=1;i<=m;i++)
		cin>>q[i].x>>q[i].y>>q[i].z;
	sort(q+1,q+m+1,[&](prpr a,prpr b){return a.z<b.z;});
	cnt=n;
	for(int i=1;i<=n+m;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		fx=get(q[i].x),fy=get(q[i].y);
		if(fx==fy)continue;
		fa[fx]=fa[fy]=++cnt;
		add(cnt,fx),add(cnt,fy);
		val[cnt]=q[i].z;
	}
	t=ceil(log(n)/log(2));
	dfs(cnt);
	for(int i=1;i<=____;i++){//直接枚举dfn，我觉得很妙啊
		if(!head[rk[i]])rt[i]=insert(rt[i-1],a[rk[i]]);
		else rt[i]=rt[i-1];
	}
	val[0]=INT_MAX;
	while(Q--){
		cin>>u>>x>>k;
		u=(u^lst)%n+1,x=x^lst,k=(k^lst)%n+1;
		for(int i=t;~i;i--)
		if(val[FA[u][i]]<=x)u=FA[u][i];
		if(tree[rt[dfn[u]+siz[u]-1]].sm-tree[rt[dfn[u]-1]].sm<k)cout<<-1<<endl,lst=0;
		else cout<<(lst=b[ask(rt[dfn[u]-1],rt[dfn[u]+siz[u]-1],tree[rt[dfn[u]+siz[u]-1]].sm-tree[rt[dfn[u]-1]].sm-k+1)])<<endl;
	}
#ifndef ONLINE_JUDGE
	cerr<<endl<<(double)clock()/CLOCKS_PER_SEC;
#endif
}
```
我自己代码都不认识了。。。。

处理树上问题真是麻烦，细节要考虑周到。

我才不会告诉你们我的[原版记录](https://www.luogu.com.cn/record/list?pid=P4197&user=100325&page=1)$\text{TLE}$ 的原因是并查集写假了呢。

---

## 作者：Endt (赞：1)

# Peaks 加强版（强制在线版）-题解

### 题面

在有 $n$ 座山峰，每座山峰有高度 $h_i$。有些山峰之间有双向道路相连，共 $m$ 条路径，每条路径有一个困难值。现在有 $Q$ 组询问，每组询问询问从点 $p$ 开始只经过困难值小于等于 $x$ 的路径所能到达的山峰中第 $k$ 高的山峰，如果无解输出 `-1`。

### 算法标签

- Kruskal 重构树

- 可持久化线段树（主席树）

- 倍增

- 离散化

### 题目分析

寻找只经过困难值小于等于 $x$ 的路径所能到达的山峰，即寻找点 $p$ 与哪些点之间的路径最大边权小于等于 $x$。Kruskal 重构树（从小到大便排序）之后，两个节点的 $\mathrm{LCA}$ 点值即为图上这两点间路径最大边权的最小值，所以我们就可以使用这一算法处理图，处理完成之后这棵树构成一个大根堆。

我们从点 $p$ 开始走，很显然，当我们只能往上走到权值小于 $x$ 的点，如果再往上，就会遇到边权更大的边了。这种单调的性质使我们能够使用倍增向上跳到这个点。$\mathrm{LCA}(p,q)$ 在这个点以下的 $q$ 肯定都是这个点子树中的节点。我们要求的就转换为了这个点子树中高度第 $k$ 高的山峰。这就可以用主席树了。


### 实现细节

按照 Kruskal 重构出来的 dfs 序建立主席树，记录每个节点子树管辖范围的开始对应根节点和结束对应根节点。原图中的节点在重构的树中全是叶子节点，所以插入操作只在叶子节点存在。接着就是主席树求第 $k$ 大的板子了。

### 完整代码

```cpp
#include<bits/stdc++.h>

#define  Int  long long int
#define  Tem  template
#define  Pub  public

using std::min;using std::max;

int n,m,q;
Int h[100005];
Int num[100005],newn;//对h的需离散化 

class Edge{//边 
Pub:int a,b;Int c;
}e[500005];
class HJT{//主席树 
Pub:int size;
    int ls,rs;
}t[5000000];
int root[100005];
int cnt_HJT;
int ins(int RT,int L,int R,int x){//主席树插入 
    int rt=++cnt_HJT;
    t[rt]=t[RT];
    ++t[rt].size;
    if(L<R){
        int M=(L+R)/2;
        if(x<=M)
            t[rt].ls=ins(t[RT].ls,L,M,x);
        else
            t[rt].rs=ins(t[RT].rs,M+1,R,x);
    }
    return rt;
}
int kth(int RT1,int RT2,int L,int R,int k){//主席树查询 
    if(t[RT2].size-t[RT1].size<k)return -1;
    if(L==R)return L|R;
    int M=(L+R)/2;
    if(t[t[RT2].rs].size-t[t[RT1].rs].size>=k)
        return kth(t[RT1].rs,t[RT2].rs,M+1,R,k);
    else
        return kth(t[RT1].ls,t[RT2].ls,L,M,k-(t[t[RT2].rs].size-t[t[RT1].rs].size));
}

class Node{//重构树的节点 
Pub:Int c[20],cc;
    int ls,rs,fa[20];
    int boss;
    int lrt,rrt;
}d[200005];
int cnt_node;

int Boss(int x){//并查集路径压缩 
    if(d[x].boss!=x)d[x].boss=Boss(d[x].boss);
    return d[x].boss;
}
void Merge(int x,int y,Int c){//并查集合并与重构树新建节点 
    x=Boss(x),y=Boss(y);
    if(x==y)return;
    d[x].fa[0]=d[x].boss=d[y].fa[0]=d[y].boss=++cnt_node;
    d[x].c[0]=d[y].c[0]=c;
    d[cnt_node].boss=cnt_node;
    d[cnt_node].cc=c;
    d[cnt_node].ls=x;d[cnt_node].rs=y;
}
void kruskal(){//Kruskal重构树 
    for(int i=1;i<=n;++i)d[i].boss=i;
    std::sort(e+1,e+1+m,[](Edge a,Edge b)->bool{return a.c<b.c;});
    for(int i=1;i<=m;++i)
        Merge(e[i].a,e[i].b,e[i].c);
}

int cnt_rt;
void dfs(int x){//倍增预处理 
    if(x==0)return;
    d[x].lrt=cnt_rt;
    for(int i=1;i<=18;++i){
        d[x].fa[i]=d[d[x].fa[i-1]].fa[i-1];
        d[x].c[i]=max(d[x].c[i-1],d[d[x].fa[i-1]].c[i-1]);
    }
    if(x<=n){
        root[cnt_rt+1]=ins(root[cnt_rt],1,newn,h[x]);
        ++cnt_rt;
    }
    dfs(d[x].ls);dfs(d[x].rs);
    d[x].rrt=cnt_rt;
}

int lastans;
void query(int st,Int x,int k){//查询 
    for(int i=18;i>=0;--i)
        if(d[st].c[i]<=x&&d[st].fa[i])
            st=d[st].fa[i];
    int ans;
    if(d[st].cc>x)ans=-1;
    else ans=kth(root[d[st].lrt],root[d[st].rrt],1,newn,k);
    if(ans==-1)printf("-1\n"),lastans=0;
    else printf("%lld\n",num[ans]),lastans=num[ans];
}

int main(){
    scanf("%d%d%d",&n,&m,&q);
    cnt_node=n;
    
    for(int i=1;i<=n;++i){
        scanf("%lld",&h[i]);
        num[i]=h[i];
    }
    std::sort(num+1,num+1+n);
    newn=std::unique(num+1,num+1+n)-num-1;
    for(int i=1;i<=n;++i)
        h[i]=std::lower_bound(num+1,num+1+newn,h[i])-num;
    
    for(int i=1;i<=m;++i)
        scanf("%d%d%lld",&e[i].a,&e[i].b,&e[i].c);
    kruskal();
    dfs(cnt_node);
    while(~--q){
        int st;Int x;int k;
        scanf("%d%lld%d",&st,&x,&k);//注意强制在线的转换 
        st=st^lastans;
        x=x^lastans;
        k=k^lastans;
        query(st,x,k);
    }
    
    return 0;
}
```

---

## 作者：I_am_Accepted (赞：1)

### Preface

加强版 $=$ 强制在线

做法：$\text{Kruskal}$ 重构树 $+\text{DFS}$ 序 $+$ 主席树

### Analysis

先造出 $\text{Kruskal}$ 重构树，预处理倍增跳祖先，那问题转化成：

**每次给 $x,k$，在线求 $x$ 子树内叶子权值第 $k$ 大。**

我们求出重构树的 $\text{DFS}$ 序，这样就将树上转化成数组问题了，然后就是 [P3834 【模板】可持久化线段树 2](https://www.luogu.com.cn/problem/P3834) 了。

### Code

代码长，毕竟是算法叠加题。

```cpp
//Said no more counting dollars. We'll be counting stars.
#include<bits/stdc++.h>
using namespace std;
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define mem(x,y) memset(x,y,sizeof(x))
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define Fe(x,y) for(int x=head[y];x;x=e[x].nxt)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define fin(s) freopen(s,"r",stdin)
#define fout(s) freopen(s,"w",stdout)
#define file(s) fin(s".in");fout(s".out")
#define cerr cerr<<'_'
#define debug cerr<<"Passed line #"<<__LINE__<<endl
template<typename T>T ov(T x){cerr<<"Value: "<<x<<endl;return x;}
#define ll long long
const ll mod=1000000007;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
inline void mad(ll &a,ll b){a=(a+b)%mod;while(a<0)a+=mod;}
inline void mmu(ll &a,ll b){a=a*b%mod;while(a<0)a+=mod;}
#define inv(a) pw(a,mod-2)
#define int long long
#define N 100002
#define M 500002
#define C 17
#define gc getchar
#define pc putchar
inline int read(){
	int x=0;char c=gc();bool f=0;
	while(!isdigit(c)){if(c=='-')f=1;c=gc();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+c-48;c=gc();}
	if(f)x=-x;return x;
}
inline void write(int x){if(x<0){pc('-');x=-x;}if(x>9)write(x/10);pc(x%10+'0');}
const int inf=1e17;
#define mid ((l+r)>>1)
//P7834
struct Edge{
	int u,v,val;
	friend bool operator<(Edge x,Edge y){return x.val<y.val;}
}g[M];
struct node{int ls,rs,sz;}t[(2*C+4)*N];
int n,m,q,a[N],f[2*N][C+1],son[2*N][2],Rt[2*N],lim,root[2*N],b[2*N],so[N],lis,tot=0,id[N],L[2*N],R[2*N],tim=0;
inline int grt(int x){return Rt[x]==x?x:Rt[x]=grt(Rt[x]);}
void build(int rt,int l,int r){
	if(l==r) return ;
	build(t[rt].ls=++tot,l,mid);
	build(t[rt].rs=++tot,mid+1,r);
}
void add(int lt,int rt,int l,int r,int id){
	if(l==r){
		t[rt].sz=t[lt].sz+1;
		return ;
	}
	if(id<=mid){
		t[rt].rs=t[lt].rs;
		add(t[lt].ls,t[rt].ls=++tot,l,mid,id);
	}else{
		t[rt].ls=t[lt].ls;
		add(t[lt].rs,t[rt].rs=++tot,mid+1,r,id);
	}
	t[rt].sz=t[t[rt].ls].sz+t[t[rt].rs].sz;
//	cerr<<rt<<":"<<l<<" "<<r<<" "<<id<<":"<<t[rt].sz<<endl;
}
void dfs(int rt){
	L[rt]=tim;
	if(rt>n){
		dfs(son[rt][0]);
		dfs(son[rt][1]);
	}else{
		id[++tim]=rt;
	}
	R[rt]=tim;
}
int que(int lt,int rt,int l,int r,int k){
	if(l==r) return l;
	int rsz=t[t[rt].rs].sz-t[t[lt].rs].sz;
//	cerr<<lt<<" "<<rt<<":"<<l<<"~"<<r<<" "<<k<<" rsz: "<<t[t[rt].rs].sz<<"-"<<t[t[lt].rs].sz<<endl;
	if(rsz>=k) return que(t[lt].rs,t[rt].rs,mid+1,r,k);
	else return que(t[lt].ls,t[rt].ls,l,mid,k-rsz);
}
signed main(){
	n=read();m=read();q=read();
	For(i,1,n) so[i]=a[i]=read();
	sort(so+1,so+1+n);
	lis=unique(so+1,so+1+n)-so-1;
	For(i,1,n) a[i]=lower_bound(so+1,so+1+lis,a[i])-so;
//	For(i,1,n) cerr<<a[i]<<" "; cerr<<endl;
	For(i,1,2*n-1) Rt[i]=i;
	lim=n;
	For(i,1,m) g[i].u=read(),g[i].v=read(),g[i].val=read();
	sort(g+1,g+1+m);
	int x,y,z;
	For(i,1,m){
		x=grt(g[i].u);y=grt(g[i].v);
		if(x==y) continue;
		Rt[x]=Rt[y]=f[x][0]=f[y][0]=++lim;
		son[lim][0]=x;
		son[lim][1]=y;
		b[lim]=g[i].val;
	}
//	For(i,n+1,lim) cerr<<i<<" "<<son[i][0]<<endl<<i<<" "<<son[i][1]<<endl;
	For(j,1,C) For(i,1,lim) f[i][j]=f[f[i][j-1]][j-1];
	b[0]=inf;
	For(i,1,lim) if(f[i][0]==0) dfs(i);
	build(root[0]=++tot,1,lis);
//	For(i,1,n) cerr<<id[i]<<" "; cerr<<endl;
	For(i,1,n){
//		cerr<<i<<"^^^"<<endl;
		add(root[i-1],root[i]=++tot,1,lis,a[id[i]]);
	}
	int ans=0;
	For(i,1,q){
		x=(read()^ans)%n+1;
		y=read()^ans;
		z=(read()^ans)%n+1;
//		cerr<<x<<" "<<y<<" "<<z<<endl;
		Rof(j,C,0) if(b[f[x][j]]<=y) x=f[x][j];
//		cerr<<x<<"##"<<endl;
		if(R[x]-L[x]<z){
			ans=0;
			puts("-1");
		}else{
//			cerr<<L[x]<<"%%%"<<R[x]<<endl;
			ans=so[que(root[L[x]],root[R[x]],1,lis,z)];
			write(ans);pc('\n');
		}
	}
return 0;}
```

---

## 作者：WhiteLabs (赞：1)

看见有篇题解说这玩意用倍增做.

作为树剖党表示，这道题是难不住树链剖分的 QWQ


------------

### $kruskal$ 重构树

根据重构树的性质，显然图上两点间的最大边权即为重构树上两点的 $LCA$ 的点权。

最小生成树能够维护连通关系。所有在原图连通的点在最小生成树上都是连通的。~~（也是显然）~~

由于 $kruskal$ 是从小到大连的边，则树上两点的 $LCA$ 即为联通的图上能使两点连通的 两点间边权最小的边，也就是说如果想让两点连通，就必须用这条边

而从一个点 $u$ 出发，边权不超过 $x$ 能到达的点有且仅有：其朝上一直走走到的最远的，点权 $<=x$ 的那个点 的子树中的所有点

**简要证明：**

一、因为 $kruskal$ 重构树的性质，对于一个点，其子树上的所有点是且仅是都可以通过不超过其点权的边相互到达的点

如果有这么一个点权 $>x$ 的点，是起点的祖先。想要从起点到达那个点必须经过点权 $>x$ 的点，然而点权 $>x$ 的那个点就是起点和那个点的 $LCA$

由于 $LCA$ 即为联通的两点间边权最大的边转换成重构树上的点，其点权是最小生成树两点间链上的边权，

则想要从起点到达终点，就必须经过那个点权的边权。如果这个最小生成树上的边权都 $>x$ 了，则从起点只经过边权 $<=x$ 的点是无法到达终点的。

二、而能通过不超过 $x$ 边权的边相连的点也必会连到一个根点权 $<=x$ 的子树里，不会跨过经过那个点权 $>x$ 的点

综上，充分性和必要性都得到了证明。


------------

### 树链剖分

在处理“找到点 $u$ 最远的点权不超过 $x$ 的祖先”的问题时，很容易想到用树剖往上跳。

对于一个链，首先判断下目标位置是否在这个链上：
+ 如果在链上，则直接二分查找（明显就变成一个二分板子了）
+ 如果不在链上，就看一下继续往上的那条链中是否存在答案。是的话就往上跳，否则就取链的 $top$ ；也不难想到。

------------

具体看代码，有注释。

然后区间 $k$ 大就拿主席树维护即可。

感觉这道题离散化有点麻烦，在查询时还得给输入的 $x$ 找到离散后的值，而不离散化也可以过。

~~实际上是因为我太菜~~

当然倍增或树剖+二分的部分也可以用 $LCT$ 写，~~虽然码量貌似更多了~~。

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch&15);ch=getchar();}
	return x*f;
}

const int N=1e5+7,M=5e5+7;

int n,m,q;
int H[N],indeg[N<<1];
int nn,val[N<<1];

struct Node {
	int u,v,w;
	bool operator < (const Node &x) const{return w<x.w;}
}E[M];

struct T{int v,next;}edge[N<<2];
int f[N<<1],cnt;
void insert(int u,int v){//从u向v，有根树
	edge[++cnt]=T{v,f[u]};f[u]=cnt;
	edge[++cnt]=T{u,f[v]};f[v]=cnt;
	indeg[v]++;
}

int Fa[N<<1];//虚拟节点也占N个
void init(){for(int i=1;i<=(n<<1);i++)Fa[i]=i;}
int find_fa(int x){return x==Fa[x]?x:Fa[x]=find_fa(Fa[x]);}

void kruskal(){
	sort(E+1,E+m+1);
	init();
	for(int i=1;i<=m;i++){
		int u=E[i].u,v=E[i].v,w=E[i].w;
		int fu=find_fa(u),fv=find_fa(v);
		if(fu^fv){
			val[++nn]=w;
			Fa[fu]=Fa[fv]=nn;
			insert(nn,fu),insert(nn,fv);
		}
	}
}

int fa[N<<1],deep[N<<1],size[N<<1],hea_s[N<<1];
void dfs1(int u,int fath){
	fa[u]=fath;deep[u]=deep[fath]+1;size[u]=1;
	for(int i=f[u];i;i=edge[i].next){
		int v=edge[i].v;
		if(v==fath) continue;
		dfs1(v,u);size[u]+=size[v];
		if(size[v]>size[hea_s[u]]) hea_s[u]=v;
	}
}
int SEQ,dfs_s[N<<1],seq_s[N<<1],top[N<<1];
void dfs2(int u,int t){
	top[u]=t;dfs_s[u]=++SEQ;seq_s[SEQ]=u;
	if(hea_s[u]) dfs2(hea_s[u],t);
	else return;
	for(int i=f[u];i;i=edge[i].next){
		int v=edge[i].v;
		if(v^fa[u]&&v^hea_s[u]) dfs2(v,v);
	}
}

int Upper_bound(int a[],int l,int r,int x){//注意到时候从top往u是从大到小排序的数列，手动实现一个
    while(r-l>7){//果然在这里还是这么处理边界比较省事
        int mid=(l+r)>>1;
        if(a[mid]<=x) r=mid-1;
        else l=mid;
    }
//    return l;
    for(int i=r;i>=l;i--) if(a[i]>x) return i;
	return -1;
}
int val_s[N<<1];
int findpos(int u,int x){//找到u的祖先中最后一个val<=x的点。保证进入函数时u合法(<=x)
//	cout<<"find:"<<u<<endl;
	if(val[top[u]]>x){
//		for(int i=dfs_s[top[u]];i<=dfs_s[u]+1;i++) cout<<"bins:"<<val_s[i]<<endl;
		return seq_s[Upper_bound(val_s,dfs_s[top[u]],dfs_s[u],x)+1];//答案在这条链上
	}
	else if((!fa[top[u]])||val[fa[top[u]]]>x) return top[u];//top合法而fa[top]不合法
	else return findpos(fa[top[u]],x);//否则就继续往上面的那条连上找
}//非叶子节点都是虚拟节点，所以不用担心会跑到原图节点上权值为0的问题

//vector <int> vec;
//inline void prework(){
//	for(int i=1;i<=n;i++) vec.push_back(H[i]);
//	sort(vec.begin(),vec.end());
//	vec.erase(unique(vec.begin(),vec.end()),vec.end());
//}
//inline int getid(int x){
//    return lower_bound(vec.begin(),vec.end(),x)-vec.begin()+1;
//}

#define _L 0
#define _R 1e9+7
#define mid ((l+r)>>1)

int rt[N<<1],ls[N<<6],rs[N<<6],sum[N<<6];
int NUM;
void update(int &NEW,int OLD,int l,int r,int x){
	NEW=++NUM;ls[NEW]=ls[OLD],rs[NEW]=rs[OLD],sum[NEW]=sum[OLD]+1;
	if(l==r) return;
	x<=mid?update(ls[NEW],ls[OLD],l,mid,x):update(rs[NEW],rs[OLD],mid+1,r,x);
}
int kth(int x,int y,int l,int r,int k){//注意，还是第k大而不是第k小
	if(k>sum[y]-sum[x]) return 0x3f3f3f3f;//判越界
	if(l==r) return l;
	int s=sum[rs[y]]-sum[rs[x]];
	if(k<=s) return kth(rs[x],rs[y],mid+1,r,k);
	else return kth(ls[x],ls[y],l,mid,k-s);
}

int query(int u,int x,int k){
	int root=findpos(u,x);
//	cout<<root<<' '<<u<<endl;
//	cout<<rt[dfs_s[root]+size[root]-1]<<' '<<rt[dfs_s[root]-1]<<endl;
	int ans=kth(rt[dfs_s[root]-1],rt[dfs_s[root]+size[root]-1],_L,_R,k);
	return ans^0x3f3f3f3f?ans:-1;
}//若root=u，则只能走到自己这个叶子节点，就哪也去不了，返回-1

int main(){
	n=read(),m=read(),q=read();
	nn=n;
	int u,v,w;
	for(int i=1;i<=n;i++) H[i]=read();
	for(int i=1;i<=m;i++){
		u=read(),v=read(),w=read();
		E[i]=Node{u,v,w};
	}
	kruskal();
	for(int i=1;i<=nn;i++) if(!indeg[i]) dfs1(i,0),dfs2(i,i);//对于每个根进行转有根树树剖
	for(int i=1;i<=nn;i++) val_s[i]=val[seq_s[i]];//序号对应的权值，这样把相邻序号的点的权值放到一块，能二分查找
	for(int i=1;i<=nn;i++)
		if(seq_s[i]<=n) update(rt[i],rt[i-1],_L,_R,H[seq_s[i]]);//序号序列上建主席树
		else rt[i]=rt[i-1];//注意只把存在于原图上的点记录到主席树上，虚拟节点就不新update了
	int x,k;
	int lastans=0;
	for(int i=1;i<=q;i++){
		u=(read()^lastans)%n+1,x=(read()^lastans),k=(read()^lastans)%n+1;
//		for(int i=u;i;i=fa[i]) cout<<i<<' '<<val[i]<<endl;
		int ans=query(u,x,k);
		lastans=~ans?ans:0;
		printf("%d\n",~ans?ans:-1);
	}
	return 0;
}

#undef _L
#undef _R
#undef mid
```


---

## 作者：MuYC (赞：1)

下面称 `Kruscal` 建树的时候的产生的点的权值为 “权值”，题目中给的点权称作 “贡献”。

+ 先是对于原图跑最小生成树的同时建立 `Kruscal` 重构树
+ 随后 dfs 遍历整棵树，维护好倍增数组以及给叶子节点（原图节点）编号，并且处理出每个非叶子节点 $u$ 为根的子树中包含的叶子节点的编号 最大 / 最小值。
+ 按照编号的顺序将叶子节点的 "贡献" 插入主席树中。
+ 查询的时候就倍增找到询问的点 $u$ 在树中最远的一个满足权值 $\leq x$ 的节点 $p$（因为深度越浅，权值越大），它为根的子树里面任意一个点跟 $u$ 的 `LCA` 的权值一定会 $\leq p$ 的权值。
+ 求 $p$ 为根的子树中包含的叶子节点的 “贡献” 第 $k$ 大，因为编号连续，可以通过主席树区间查询。

时间复杂度：$O(m \log n + n \log n)$，空间复杂度：$O(n \log n)$

#### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
    int x = 0, flag = 1;
    char ch = getchar();
    for( ; ch > '9' || ch < '0' ; ch = getchar()) if(ch == '-') flag = -1;
    for( ; ch >= '0' && ch <= '9' ; ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
    return x * flag;
}
const int MAXN = 2e5 + 50, MAXM = 5e5 + 50;
int n, m, f[MAXM + MAXN], tot, rt, start[MAXN], q, V[MAXN];
int fa[MAXN][20], L[MAXN], dfn_id[MAXN], R[MAXN], dep[MAXN], A[MAXN], now = 0;
int head, tail, Rt[MAXN], cnt = 0;
vector <int> Son[MAXN];
struct Edge {
    int from, to, w;
} e[MAXM << 1];
int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }
bool cmp(Edge a, Edge b) { return a.w < b.w; }
struct SegmentTree {
    int ls, rs, Sum;
} T[MAXN * 16];

inline void DFS(int x, int from) {
    fa[x][0] = from, dep[x] = dep[from] + 1;
    L[x] = 1e9 + 7, R[x] = 0;
    for(int i = 1 ; i <= log2(dep[x]) ; i ++)
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    if(!Son[x].size()) L[x] = R[x] = ++ now, dfn_id[now] = x;
    for(int i = 0 ; i < Son[x].size(); i ++) {
        int to = Son[x][i];
        DFS(to, x);
        L[x] = min(L[to], L[x]);
        R[x] = max(R[to], R[x]);
    }
    return ;
}
inline int insert(int x, int l, int r, int pos) {
    int cur = ++ cnt, mid = (l + r) >> 1;
    T[cur] = T[x], T[cur].Sum ++;
    if(l == r) return cur;
    if(pos <= mid) T[cur].ls = insert(T[x].ls, l, mid, pos);
    else T[cur].rs = insert(T[x].rs, mid + 1, r, pos);
    return cur;
}
inline int Getfa(int x, int s) {
    for(int i = log2(dep[x]) ; i >= 0 ; i --)
        if(fa[x][i] != 0 && V[fa[x][i]] <= s) x = fa[x][i];
    return x;
}
inline int GetAns(int u, int v, int l, int r, int k) {
    int S = T[T[v].rs].Sum - T[T[u].rs].Sum, mid = (l + r) >> 1;
    if(l == r) return l;
    if(S >= k) return GetAns(T[u].rs, T[v].rs, mid + 1, r, k);
    else return GetAns(T[u].ls, T[v].ls, l, mid, k - S);
}
signed main() {
    //freopen("out","w",stdout);
    n = read(), m = read(), q = read(), rt = n;
    for(int i = 1 ; i <= n ; i ++) A[i] = read(); 
    for(int i = 1 ; i <= m ; i ++) {
        int u = read(), v = read(), w = read();
        e[i] = (Edge) { u, v, w };
    }
    for(int i = 1 ; i <= n + m ; i ++) f[i] = i;
    sort(e + 1, e + 1 + m, cmp);
    for(int i = 1 ; i <= m ; i ++) {
        int u = find(e[i].from), v = find(e[i].to);
        if(u != v) {
            rt ++, f[u] = f[v] = f[rt] = rt;
            V[rt] = e[i].w;
            Son[rt].push_back(u), Son[rt].push_back(v);
        }
    } DFS(rt, 0);
    int Ans = 0;
    for(int i = 1 ; i <= n ; i ++) 
        Rt[i] = insert(Rt[i - 1], 1, 1e9, A[dfn_id[i]]);
    for(int i = 1 ; i <= q ; i ++) {
        int u = (read() ^ Ans) % n + 1, x = read() ^ Ans, k = (read() ^ Ans) % n + 1;
        u = Getfa(u, x);
        if(R[u] - L[u] + 1 < k) Ans = 0, printf("-1\n");
        else Ans = GetAns(Rt[L[u] - 1], Rt[R[u]], 1, 1e9, k), printf("%d\n", Ans);
    }
    return 0;
}
```

---

## 作者：0htoAi (赞：0)

我是帮 Leasier 验这道题的。

## 算法思路：

简单来说，这道题可以用 Kruskal 重构树加可持久化线段树来做。Kruskal是处理不大于或不小于问题的，可持久化线段树是解决区间第几相关问题的，恰好可以解决这道题。

## 具体解题过程：

将输入的边按照权值由小到大建立 Kruskal 重构树，跑一边 dfs 求出这棵重构树的 dfs 序，将 dfs 序对应节点的权值建立一棵可持久化线段树来维护。对于每个询问将 $v$ 倍增向上跳到权值小于 $x$ 且深度最浅的一个点 $u$，根据 kruskal 重构树的性质，以 $u$ 为根的子树的点权（重构树中的点权为原来的边权）也一定小于 $x$，所以就在 $u$ 的 dfs 序的起点和终点这一段区间找第 $k$ 大的就行了。



## 小细节：

$1.$ 点权要离散化。

$2.$ 查询第 $k$ 大而不是第 $k$ 小。

$3.$ 可持久化线段树只需要维护 dfs 序上小于等于 $n$ 的节点，因为只有这些节点是叶子节点（或者叫真实节点）。



## 代码：

```cpp
#include <bits/stdc++.h>

using namespace std;
const int MAXN=5e6+50;

struct Edge
{
	int x,y,Len,Next;
}e[MAXN],et[MAXN];
int elast[MAXN],elastt[MAXN];
int Tot=0,tott=0;
int father[MAXN];
int N,M,Q,Cnt;
void Addt(int x,int y,int Len)
{
	tott++;
	et[tott].x=x;
	et[tott].y=y;
	et[tott].Len=Len;
	et[tott].Next=elastt[x];
	elastt[x]=tott;
}
void Add(int x,int y)
{
	Tot++;
	e[Tot].x=x;
	e[Tot].y=y;
	e[Tot].Next=elast[x];
	elast[x]=Tot;
}
int Size[MAXN];
bool cmp(Edge a,Edge b)
{
	return a.Len<b.Len;
}
void StartFather()
{
	for(int i=1;i<=2*N;i++)
	father[i]=i;
	for(int i=1;i<=N;i++)
	Size[i]=1;
}
int getfather(int x)
{
	if(father[x]!=x)
	father[x]=getfather(father[x]);
	return father[x];
}
int Nowf;
int dis[MAXN];

void Kruskal()
{
	StartFather();
	sort(et+1,et+M+1,cmp);
	
	for(int i=1;i<=M&&Nowf<N*2-1;i++)
	{
		int fx=getfather(et[i].x),fy=getfather(et[i].y);
		if(fx!=fy)
		{
			Nowf++;
			father[fx]=Nowf;
			father[fy]=Nowf;
			Add(Nowf,fx);
			Add(Nowf,fy);
			dis[Nowf]=et[i].Len;
			Size[Nowf]=Size[fx]+Size[fy];
		}
	}
}
int K,f[MAXN][45],depth[MAXN];
int Nowid=0;
struct DFSXU
{
	int In,Out;
}Dot[MAXN];
int DFSXU[MAXN];
void dfs(int u,int fa)
{
	depth[u]=depth[fa]+1;
	f[u][0]=fa;
	for(int j=1;;j++)
	{
		f[u][j]=f[f[u][j-1]][j-1];
		if(f[u][j]==0)
		{
			K=max(K,j-1);
			break;
		}
	}
	Nowid++;
	Dot[u].In=Nowid;
	DFSXU[Nowid]=u;
	for(int j=elast[u];j;j=e[j].Next)
	{
		int v=e[j].y;
		if(v!=fa)
		{
			dfs(v,u);
		}
	}
	Dot[u].Out=Nowid;
}


struct Tr
{
	int Sum;
	int Ls,Rs;
}tr[MAXN];


int tot=0;
int A[MAXN],lsh[MAXN];
int h[MAXN];
int Tree[MAXN];
int build(int l,int r)
{
	int u=++tot;
	tr[u].Sum=0;
	if(l==r)
	return u;
	int mid=l+r>>1;
	tr[u].Ls=build(l,mid);
	tr[u].Rs=build(mid+1,r);
	return u;
}
int update(int u,int x,int y,int k)
{
	int u1=++tot;
	tr[u1].Sum=tr[u].Sum+1;
	if(x==y)
	{
		tr[u1].Ls=tr[u].Ls;
		tr[u1].Rs=tr[u].Rs;
		return u1;
	}
	int mid=x+y>>1;
	if(k<=mid)
	{
		tr[u1].Ls=update(tr[u].Ls,x,mid,k);
		tr[u1].Rs=tr[u].Rs;
	}
	else
	{
		tr[u1].Ls=tr[u].Ls;
		tr[u1].Rs=update(tr[u].Rs,mid+1,y,k);
	}

	return u1;
}

int Query(int u1,int u2,int l,int r,int k)
{
	if(l==r)
	return l;
	int mid=l+r>>1;
	if(tr[tr[u2].Ls].Sum-tr[tr[u1].Ls].Sum>=k)
	{
		return Query(tr[u1].Ls,tr[u2].Ls,l,mid,k);
	}
	else
	{
		return Query(tr[u1].Rs,tr[u2].Rs,mid+1,r,k-tr[tr[u2].Ls].Sum+tr[tr[u1].Ls].Sum);
	}
}
int Hash[MAXN];
int main()
{
	scanf("%d%d%d",&N,&M,&Q);
	Nowf=N;
	for(int i=1;i<=N;i++)
	{
		scanf("%d",&h[i]);
		lsh[i]=h[i];
	}
	for(int i=1;i<=M;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		Addt(a,b,c);
	}
	Kruskal();
	dfs(Nowf,0);
	sort(lsh+1,lsh+N+1);
	Cnt=unique(lsh+1,lsh+N+1)-lsh-1;
	Tree[0]=build(1,Cnt);
	for(int i=1;i<=Nowf;i++)
	{
		if(DFSXU[i]<=N)
		{
			int tt=lower_bound(lsh+1,lsh+Cnt+1,h[DFSXU[i]])-lsh;
			Tree[i]=update(Tree[i-1],1,Cnt,tt);
		}else{
			Tree[i]=Tree[i-1];
		}
	}
	int LastAns=0;
	while(Q--)
	{
		int v,x,k;
		scanf("%d%d%d",&v,&x,&k);
		v^=LastAns;
		x^=LastAns;
		k^=LastAns;
		v=v%N+1;
		k=k%N+1;
		for(register int i=log2(depth[v]);i>=0;--i)
		{
			if(dis[f[v][i]]<=x&&f[v][i]!=0)
			{
				v=f[v][i];
			}
		}
		int Ans;
		if(Size[v]<k)
			Ans=-1;
		else
			Ans=lsh[Query(Tree[Dot[v].In-1],Tree[Dot[v].Out],1,Cnt,Size[v]-k+1)];
		printf("%d\n",Ans);
		if(Ans!=-1)
		LastAns=Ans;
		else
		LastAns=0;
	}
}
```

---

