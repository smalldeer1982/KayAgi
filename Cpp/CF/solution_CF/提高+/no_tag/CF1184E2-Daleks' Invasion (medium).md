# Daleks' Invasion (medium)

## 题目描述

在一次成功的实地测试后，Heidi 正考虑在某些走廊上部署陷阱，但可能不会选择第一条走廊。为了避免在时间漩涡中遇到 Daleks，出于谨慎，她只考虑在当前 Daleks 计划中不会使用的那些走廊上布置陷阱——也就是说，只考虑那些不在最小生成树上的走廊。Heidi 知道所有不同走廊的能量需求现在都是不同的，并且 Daleks 只有一个唯一的计划要使用。

你的任务是计算每条 Heidi 考虑的走廊的 $E_{max}(c)$，其定义与简单版本相同——即，最大的 $e \le 10^9$，使得如果我们将走廊 $c$ 的能量改为 $e$，Daleks 可能会使用它——但现在需要对 Heidi 考虑的每一条走廊都计算。

## 说明/提示

如果 $m = n-1$，则无需输出任何内容。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 3
1 2 8
2 3 3
3 1 4
```

### 输出

```
4
```

# 题解

## 作者：Hoks (赞：4)

## 前言
重剖题单里的，刚好我的[总结文章](https://www.luogu.com.cn/blog/Hok/cute-tree-decomposition)里把这题当做了练习题，就写篇题解吧。

~~这题是 CF827D 弱化吧/kk。~~

## 题意分析
有关题意的话，洛谷上的翻译已经写的很详细易懂了。

接着考虑怎么处理。

首先我们优先考虑造出来一颗 MST，那么一条边就有两种可能性：

1. 在 MST 上。

2. 不在 MST 上。

但是题目中不用考虑第一种情况，所以我们只考虑第二种情况：

- 如果把这条边放进树中，必然会形成一个环，这个时候树就变成了基环树。

- 因为生成的是 MST，所以我们要去掉环上边权最大的一条边。

- 但我们又要保证去掉的这条边不能是非树边。

- 所以我们只需要查询这条边的两端点路径上的最大边权即可。

注意数组大小。

## 代码
```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (p<<1|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=100010,M=1e6+10,INF=0x3f3f3f3f3f3f3f3f;
struct edge{int v,nxt,w;}e[M<<1];
struct node{int x,y,w,id;}g[M];
int n,m,tot,cnt,yl;
int dfn[N],top[N],head[N],id[N],f[N],ans[M],lz[N<<2];
int fa[N],dep[N],si[N],son[N],a[N],t[N<<2],tt[N<<2];
bool mp[M];
static char buf[1000000],*paa=buf,*pd=buf;
#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
inline int read(void){
    int x(0),a(1);char fc(getchar());
    while(!isdigit(fc)){if(fc=='-') a=-1;fc=getchar();}
    while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
    return x*a;
}
inline void print(int x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) print(x/10);
	putchar(x%10+'0');
}
inline void add(int u,int v,int w){e[++tot].v=v,e[tot].nxt=head[u],head[u]=tot,e[tot].w=w;}
inline bool cmp(node x,node y){return x.w<y.w;}
inline int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
inline void dfs1(int u,int ff)
{
	dep[u]=dep[ff]+1,fa[u]=ff,si[u]=1;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==ff) continue;
		dfs1(v,u);si[u]+=si[v];a[v]=e[i].w;
		if(si[v]>si[son[u]]) son[u]=v;
	}
}
inline void dfs2(int u,int topf)
{
	top[u]=topf,dfn[u]=++cnt,id[cnt]=a[u];
	if(son[u]) dfs2(son[u],topf);
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}
inline void pushup(int p){t[p]=max(t[ls],t[rs]);}
inline void pushdown(int p)
{
	if(lz[p]!=INF)
	{
		lz[ls]=min(lz[ls],lz[p]),lz[rs]=min(lz[rs],lz[p]);
		tt[ls]=min(tt[ls],lz[p]),tt[rs]=min(tt[rs],lz[p]);
		lz[p]=INF;
	}
}
inline void build(int p,int l,int r)
{
	if(l==r) return void(t[p]=id[l]);
	build(ls,l,mid),build(rs,mid+1,r),pushup(p);
}
inline int query(int p,int l,int r,int s,int e)
{
	if(l>=s&&r<=e) return t[p];
	int res=0;if(mid>=s) res=query(ls,l,mid,s,e);
	if(mid<e) res=max(res,query(rs,mid+1,r,s,e));
	return res;
}
inline void modify(int p,int l,int r,int s,int e,int k)
{
	if(l>=s&&r<=e) return void(lz[p]=min(lz[p],k)),void(tt[p]=min(tt[p],k));
	pushdown(p);
	if(mid>=s) modify(ls,l,mid,s,e,k);
	if(mid<e) modify(rs,mid+1,r,s,e,k);
	tt[p]=min(tt[ls],tt[rs]);
}
inline int qry(int p,int l,int r,int s,int e)
{
	if(l>=s&&r<=e) return tt[p];pushdown(p);
	int res=0;if(mid>=s) res=qry(ls,l,mid,s,e);
	if(mid<e) res=max(res,qry(rs,mid+1,r,s,e));
	return res;
}
inline void modify(int i)
{
	int x=g[i].x,y=g[i].y,w=g[i].w;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		modify(1,1,cnt,dfn[top[x]],dfn[x],w);x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	modify(1,1,n,dfn[x]+1,dfn[y],w);
}
inline int query(int i)
{
	int x=g[i].x,y=g[i].y,res=0;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		res=max(query(1,1,cnt,dfn[top[x]],dfn[x]),res);x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	return max(res,query(1,1,n,dfn[x]+1,dfn[y]));
}
signed main()
{
	n=read(),m=read();memset(tt,0x3f,sizeof tt);memset(lz,0x3f,sizeof lz);
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1,u,v,w;i<=m;i++) u=g[i].x=read(),v=g[i].y=read(),w=g[i].w=read(),g[i].id=i;
	sort(g+1,g+1+m,cmp);
	for(int i=1,u,v,w;i<=m;i++)
	{
		u=g[i].x,v=g[i].y,w=g[i].w;
		if(find(u)==find(v)) continue;
		yl++;add(u,v,w),add(v,u,w);f[find(u)]=find(v);
		mp[i]=1;if(yl==n-1) break;
	}
	dfs1(1,0),dfs2(1,1),build(1,1,cnt);
	for(int i=1;i<=m;i++) if(!mp[i]) ans[g[i].id]=query(i),modify(i);
	for(int i=1,x;i<=m;i++) if(mp[i]) x=max(dfn[g[i].x],dfn[g[i].y]),ans[g[i].id]=-1;
	for(int i=1;i<=m;i++) if(ans[i]!=-1) print(ans[i]==INF?1e9:ans[i]),puts("");
	return 0;
}
```

---

## 作者：SoyTony (赞：1)

易、中、难三个版本中，主要是要懂得完整难版的做法（另两题的做法也会提到）
# easy version
只询问 $1$ 条边，可以二分这条边的值，每次检验用 $\text{Kruskal}$ 最小生成树检验。

注意这里边排序的方式应当是以边权升序为第一关键字，以边的编号升序为第二关键字。

例如存在边 $(1,2,3),(1,3,4),(2,3,3)$，这里的第一条边 $(1,2,3)$ 存在于一种最小生成树中，但是不按照编号排序可能使得我们得到的最小生成树不是包含第一条边的。

时间复杂度：$O(m\log m\log a)$，只修改一条边权值每次冒泡一下也可以快一点？
# medium version
询问所有非树边。

可以画出这个无向图以及其最小生成树，发现当我们将一条非树边变成树边时，其与树形成的一个环就要断开一条边，那么当这条边权值大于等于非树边权值时，也就可以替换了。

于是对于非树边要查询的是：其在树上对应的路径中权值最大值。

静态问题，树链剖分 + $\text{ST}$ 表即可解决问题，时间复杂度：$O(m
\log m+m\log n)$
# hard version
基于上一题的做法，需要处理树边。

发现非树边要考虑的是对应树上路径的树边，那么树边考虑的就是能覆盖它的非树边，换言之是与其形成环的非树边。

需要查询：与这条树边能形成环的非树边中的最小值。

区间取 $\min$ 操作是在钓鱼，中间不查询，于是直接权值从大到小排序改成区间赋值，线段树解决。

时间复杂度：$O(m\log m+m\log^2 n)$

# 本题代码

```cpp
int n,m;
struct Tree{
    struct G_Edge{
        int u,v,w,id;
        bool tag;
    }GE[maxm];
    int bel[maxn];
    int find(int x){
        if(x==bel[x]) return x;
        else return bel[x]=find(bel[x]);
    }
    struct T_Edge{
        int v,w;
        T_Edge()=default;
        T_Edge(int v_,int w_):v(v_),w(w_){}
    };
    vector<T_Edge> E[maxn];
    inline void add_edge(int u,int v,int w){
        E[u].push_back(T_Edge(v,w));
    }
    inline void Krusal(){
        sort(GE+1,GE+m+1,[&](G_Edge x,G_Edge y){
            return x.w<y.w;
        });
        for(int i=1;i<=n;++i) bel[i]=i;
        int cnt=0;
        for(int i=1;i<=m;++i){
            int u=GE[i].u,v=GE[i].v,w=GE[i].w;
            int fu=find(u),fv=find(v);
            if(fu==fv) continue;
            else{
                bel[fv]=fu;
                GE[i].tag=true;
                add_edge(u,v,w);
                add_edge(v,u,w);
                // printf("%d<->%d %d\n",u,v,w);
                ++cnt;
                if(cnt==n-1) break;
            }
        }
        sort(GE+1,GE+m+1,[&](G_Edge x,G_Edge y){
            return x.id<y.id;
        });
    }
    int fa[maxn],dep[maxn],siz[maxn],son[maxn],val[maxn];
    int top[maxn],dfn[maxn],dfncnt;
    int mx[maxn][18];
    void dfs1(int u,int f,int d){
        fa[u]=f,dep[u]=d,siz[u]=1;
        int maxson=-1;
        for(T_Edge e:E[u]){
            int v=e.v,w=e.w;
            if(v==f) continue;
            val[v]=w;
            dfs1(v,u,d+1);
            siz[u]+=siz[v];
            if(siz[v]>maxson) maxson=siz[v],son[u]=v;
        }
    }
    void dfs2(int u,int t){
        top[u]=t,dfn[u]=++dfncnt;
        mx[dfn[u]][0]=val[u];
        if(!son[u]) return;
        dfs2(son[u],t);
        for(T_Edge e:E[u]){
            int v=e.v;
            if(v==fa[u]||v==son[u]) continue;
            dfs2(v,v);
        }
    }
    inline void build_st(){
        mx[1][0]=0;
        for(int k=1;k<=17;++k){
            for(int i=1;i+(1<<k)-1<=n;++i){
                mx[i][k]=max(mx[i][k-1],mx[i+(1<<(k-1))][k-1]);
            }
        }
    }
    inline int query_st(int l,int r){
        int k=log2(r-l+1);
        return max(mx[l][k],mx[r-(1<<k)+1][k]);
    }
    inline int query(int u,int v){
        int res=0;
        while(top[u]!=top[v]){
            if(dep[top[u]]>dep[top[v]]) swap(u,v);
            res=max(res,query_st(dfn[top[v]],dfn[v]));
            v=fa[top[v]];
        }
        if(dep[u]>dep[v]) swap(u,v);
        if(u!=v) res=max(res,query_st(dfn[u]+1,dfn[v]));
        return res;
    }
}T;
int main(){
    n=read(),m=read();
    for(int i=1;i<=m;++i){
        T.GE[i].u=read(),T.GE[i].v=read(),T.GE[i].w=read(),T.GE[i].id=i;
        T.GE[i].tag=false;
    }
    T.Krusal();
    T.dfs1(1,0,0);
    T.dfs2(1,1);
    T.build_st();
    for(int i=1;i<=m;++i){
        if(T.GE[i].tag) continue;
        int u=T.GE[i].u,v=T.GE[i].v;
        int res=T.query(u,v);
        printf("%d\n",res);
    }
    return 0;
}
```

---

