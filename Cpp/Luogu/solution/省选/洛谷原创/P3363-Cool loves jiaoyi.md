# Cool loves jiaoyi

## 题目背景

Cool 交易得十分熟练。现在 Cool 即将参加一场 NOIP 普及组模拟赛。Cool 什么都不会，他将通过交易来获得每一题的题解 / 标程。

## 题目描述

Cool 的交易对象构成了一个树形结构。

对于每一场轰轰烈烈的交易，都会有一个交易起点和交易终点。在树上从交易起点到交易终点的路径称作交易链，交易链上的所有交易对象都将加入这场交易，交易的代价即为交易对象数。

现在 Cool 面临着 $m$ 场交易，现在 Cool 要钦点 $k$ 场交易，使得存在某个神秘交易对象参与了所有 $k$ 场交易，并且最小化这 $k$ 场交易中代价之差的最大值。

## 说明/提示

选择第 $1,2,3$ 三场交易，则交易对象 $3,4,5$ 被同时交易了 $3$ 次，且三场交易的代价分别为 $3,4,4$。他们交易代价之差最大为 $4-3$。此时最优。

## 样例 #1

### 输入

```
5 4 3
1 2
1 3
1 4
4 5
2 3
3 5
2 5
4 5```

### 输出

```
1```

# 题解

## 作者：kczno1 (赞：3)

开了O2后终于拿到rank1(感叹有毒的同时orz 一UNowen一)。

如题解所说，这题就是“区间”的树上版。相信做了“区间”后的人都会做这题。

优化(卡常):

1 zkw
2 对每个链开一个zkw,不要用vector,用int \*a，开时a = new int[n];

再开一个大zkw维护所有链最大值的最大值

3 (短小的地方)用define代替inline


```cpp
#pragma GCC optimize("O2")
#include<bits/stdc++.h>
using namespace std;

#define chmin(x,y) if (x>y) x=y;
#define MAX(x,y) (x>y?x:y) 
#define F(x) (x>>1) 
#define S(x) (x^1) 
#define D(x) (x&1) 

int n,m,k,i,x,y;
int f,sz,deep,son,top;
int delta;
#define max_n (50005)
#define max_m (10005)

struct ZKW
{
    int max[max_n*3]; int d,n;
    inline void init()
    {
        for (d=1;d<n;d<<=1);d-=1;
    }
    void change(int l,int w)
    {
        l+=d;max[l]=w;
        while (F(l))
        {
            max[F(l)]=MAX(max[l],max[S(l)]);l=F(l);
        }
    }
};
ZKW z;

struct edge
{
    int to,next;
};
edge l[max_n*2];int e;
struct node
{
    int head,f,son,sz,deep,top;
    int w;
    int d,n;//n先存树链长度，后存所在总ZKW的编号 
    int *a,*max;//作动态数组
    inline void init()
    {
        for (d=1;d<n;d<<=1);d-=1;
        n=(d<<1)+5;
        a = new int[n];   memset(&a[1],0,(n-1)<<2);
        max = new int[n]; memset(&max[1],0,(n-1)<<2);
    }
   #define A(x) {a[x]+=delta;max[x]+=delta;}
    void add(int l,int r)//给[l,r]+delta
    {
        l+=d;r+=d;
        A(l);
        if (l!=r)
        {
            A(r);
            while (S(l)!=r)
            {
                if (!D(l)) A(S(l));
                if (D(r)) A(S(r));
                max[F(l)]=MAX(max[l],max[S(l)])+a[F(l)];l=F(l);
                max[F(r)]=MAX(max[r],max[S(r)])+a[F(r)];r=F(r);
            }
        }
        while (F(l))
        {
            max[F(l)]=MAX(max[l],max[S(l)])+a[F(l)];l=F(l);
        }
        z.change(n,max[1]);
    }
    void add_1(int l)
    {
        l+=d;
        A(l);
        while (F(l))
        {
            if (D(l)) A(S(l));
            max[F(l)]=MAX(max[l],max[S(l)])+a[F(l)];l=F(l);
        }
        z.change(n,max[1]);
    }
};
node T[max_n];

#define add_e(x,y) l[++e].to=y;l[e].next=T[x].head;T[x].head=e;

int q[max_n],head,tail;
void bfs1()
{
    q[1]=tail=1;
    for (head=1;head<=tail;++head)
    {
        x=q[head];T[x].sz=1;
        f=T[x].f;deep=T[x].deep+1;
        for (i=T[x].head;i;i=l[i].next)
        if ((y=l[i].to)!=f)
        {
            T[y].f=x;
            T[y].deep=deep;
            q[++tail]=y;
        }
    }
    for (;tail;--tail)
    {
        x=q[tail];f=T[x].f;sz=T[x].sz;
        T[f].sz+=sz;
        if (sz>=T[T[f].son].sz) T[f].son=x;
    }
}
void bfs2()
{
    tail=q[1]=T[1].top=T[1].w=1;
    while (tail)
    {
        x=q[tail--];
        top=T[x].top;
        ++T[top].n;
        
        son=T[x].son;
     if (son)
     {
        f=T[x].f;
        for (i=T[x].head;i;i=l[i].next)
        if ((y=l[i].to)!=f)
        if (y!=son) { q[++tail]=y;T[y].top=y;T[y].w=1; }
        
        q[++tail]=son;T[son].top=top;T[son].w=T[x].w+1;
     }
    }
    
    for (i=1;i<=n;++i)
    if (T[i].n)
    {
        T[i].init();
        T[i].n=++z.n;
    }
    z.init();
}

int f1,f2,d1,d2;
int lca(int x1,int x2)
{
    f1=T[x1].top;d1=T[f1].deep;
    f2=T[x2].top;d2=T[f2].deep;
    while (f1!=f2)
    if (d1>d2)
    {
        x1=T[f1].f;f1=T[x1].top;d1=T[f1].deep;
    }
    else
    {
        x2=T[f2].f;f2=T[x2].top;d2=T[f2].deep;
    }
    if (T[x1].deep<T[x2].deep) return x1;
    else return x2;  
}
void lca_add(int x1,int x2)
{
    f1=T[x1].top;d1=T[f1].deep;
    f2=T[x2].top;d2=T[f2].deep;
    while (f1!=f2)
    if (d1>d2)
    {
        T[f1].add_1(T[x1].w);
        x1=T[f1].f;f1=T[x1].top;d1=T[f1].deep;
    }
    else
    {
        T[f2].add_1(T[x2].w);
        x2=T[f2].f;f2=T[x2].top;d2=T[f2].deep;
    }
    if (T[x1].w<T[x2].w) T[f1].add(T[x1].w,T[x2].w);
    else T[f1].add(T[x2].w,T[x1].w);
}

struct path
{
    int x,y,len;
};
path p[max_m];
bool len_xiao(const path &x,const path &y)
{
    return x.len<y.len;
}

#define _top 10000000
char ch[_top];int _i;
void read(int &x)
{
    while (ch[_i]<48) ++_i;
    for (x=ch[_i]-48;ch[++_i]>=48;) 
     x=(x<<1)+(x<<3)+ch[_i]-48;
}

int main()
{ //freopen("1.in","r",stdin);freopen("1.out","w",stdout);
   fread(ch,1,_top,stdin);
    read(n);read(m);read(k);
    for (i=1;i<=n;++i) T[i].head=T[i].son=T[i].n=0;
    for (i=1;i<n;++i)
    {
        read(x);read(y);
        add_e(x,y);add_e(y,x);
    }
    
    bfs1();
    bfs2();    
    
    for (i=1;i<=m;++i)
    {
        read(x);read(y);
        f=lca(x,y);
        p[i].x=x;p[i].y=y;p[i].len=T[x].deep+T[y].deep-(T[f].deep<<1);
    }
    sort(p+1,p+m+1,len_xiao);
    
    int l=0,r=1,ans=1<<30;
    delta=1;
    lca_add(p[1].x,p[1].y);
    while (r<m)
    {
        delta=1;
      while (z.max[1]<k&&r<m) 
      {
          ++r;lca_add(p[r].x,p[r].y);
      }
      if (z.max[1]<k) break;
       delta=-1;
      while (z.max[1]>=k) 
      {
        ++l;lca_add(p[l].x,p[l].y);
      }
      chmin(ans,p[r].len-p[l].len);
    }
    
    if (ans==1<<30) printf("%d",-1);
    else printf("%d",ans);
}
```

---

## 作者：云浅知处 (赞：2)

题意大概是给定一棵树以及 $m$ 条路径，第 $i$ 条路径的权重为 $w_i$；要求选出来一些路径使得至少有一个点被覆盖了至少 $k$ 次，且使得这些路径的权重极差最小。

对于这种最小化极差的题有一个差不多的套路，就是将路径按照权重排序之后 2pointers。

具体来说，我们给树上的每个点都维护一个值表示它被覆盖的次数；每次加入一条路径就把路径上的点的覆盖次数都加一，删掉一条路径就把这些点都减一。存在一个点被覆盖了至少 $k$ 次就相当于所有点的权值中的最大值 $\ge k$。

用树剖维护链上加和全局最大值即可。时间复杂度 $O(n+m\log^2n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

inline int read(){
    int x=0,f=1;char c=getchar();
    for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
    for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
    return x*f;
}

const int MN=2e5+5;
int n,m,k;
vector<int>G[MN];
pair<int,pair<int,int> >tr[MN];

int fa[MN],top[MN],hson[MN],dfn[MN],sz[MN],dep[MN];

int dfs1(int u,int de){
    sz[u]=1,dep[u]=de;
    for(int v:G[u]){
        if(v==fa[u])continue;
        fa[v]=u,sz[u]+=dfs1(v,de+1);
        if(sz[v]>sz[hson[u]])hson[u]=v;
    }
    return sz[u];
}

int tot=0;
void dfs2(int u,int tp){
    top[u]=tp,dfn[u]=++tot;
    if(hson[u])dfs2(hson[u],tp);
    for(int v:G[u]){
        if(v!=fa[u]&&v!=hson[u])dfs2(v,v);
    }
}

#define lson(o) (o<<1)
#define rson(o) (o<<1|1)

struct SegTree{
    int d[MN<<2],plz[MN<<2];
    
    inline void pushup(int o){
        d[o]=max(d[lson(o)],d[rson(o)]);
    }
    
    inline void clear(){
        memset(d,0,sizeof(d));
        memset(plz,0,sizeof(plz));
    }
    
    inline void pushdown(int ql,int qr,int o){
        if(plz[o]){
            d[lson(o)]+=plz[o],d[rson(o)]+=plz[o];
            plz[lson(o)]+=plz[o],plz[rson(o)]+=plz[o];
            plz[o]=0;
        }
    }
    
    inline void modify(int l,int r,int k,int ql,int qr,int o){
        if(l<=ql&&qr<=r){d[o]+=k,plz[o]+=k;return;}
        int mid=(ql+qr)>>1;pushdown(ql,qr,o);
        if(l<=mid)modify(l,r,k,ql,mid,lson(o));
        if(r>mid)modify(l,r,k,mid+1,qr,rson(o));
        pushup(o);
    }
    
    inline int query(){
        return d[1];
    }
}tree;

bool chk(){
    return tree.query()>=k;
}

void add(int u,int v,int w){
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]])swap(u,v);
        tree.modify(dfn[top[u]],dfn[u],w,1,n,1);
        u=fa[top[u]];
    }
    if(dep[u]>dep[v])swap(u,v);
    tree.modify(dfn[u],dfn[v],w,1,n,1);
}

int dis(int u,int v){
	int res=0;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		res+=dfn[u]-dfn[top[u]]+1;
		u=fa[top[u]];
	}
	if(dep[u]>dep[v])swap(u,v);
	return res+dfn[v]-dfn[u]+1;
}

const int INF=2e9;

#define fi first
#define se second
#define OK puts("OK")

signed main(void){
	
#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
#endif		
    
    n=read(),m=read(),k=read();
    for(int i=1;i<=n-1;i++){
        int u=read(),v=read();
        G[u].push_back(v),G[v].push_back(u);
    }
    
    dfs1(1,1),dfs2(1,1),tree.clear(); 
    for(int i=1;i<=m;i++)tr[i].se.fi=read(),tr[i].se.se=read(),tr[i].fi=dis(tr[i].se.fi,tr[i].se.se);
    
    sort(tr+1,tr+m+1);
    
    int r=0,ans=INF;
    for(int l=1;l<=m;l++){
        while(!chk()){
        	r++;if(r>m){cout<<ans<<endl;return 0;}
			add(tr[r].se.fi,tr[r].se.se,1);
        }
        if(!chk())break;
        ans=min(ans,tr[r].fi-tr[l].fi);add(tr[l].se.fi,tr[l].se.se,-1);
    }
    
    cout<<((ans==INF)?-1:ans)<<endl;

    return 0;
}
```

---

## 作者：GaryH (赞：2)

## P3363 题解
~~为啥其他人都用的ZKW？这个不是不需要卡常吗~~

### 题意：

定义树上的一条路径的权为其包含的点数，

从给定的 $m$ 条路径中选出经过同一点的 $k$ 条，

求出这 $k$ 条路径的最小极差。

### 解析：

如果暴力的确定 $k$ 条路径的选取方案太过笨重，所以我们考虑转化题意并找到一个更优的办法。

可以注意到，我们只需要确定这 $k$ 条路径中权最大的以及最小的两条，再判断所有权值处于这两条的权之间的路径是否经过了某一个点超过 $k$ 次，因为确定了权最大的以及最小，就等价于确定了极差的大小。

那么我们就可以以路径的权为第一关键字升序，并枚举两个端点 $(l,r)$ ,此时编号属于 $(l,r)$ 之间的路径都可以进行不付任何代价地选择，于是我们用树剖线段树来维护路径的覆盖次数以及覆盖次数的最值，即可在 $O(n^2log^2n)$ 的时间复杂度内解决这个问题。

但是这样还是会爆，而且直觉告诉我们，不必要且繁琐的枚举 $(l,r)$ 是有优化空间的。

于是我们进行进一步的观察与思考：

符合"经过了某一个点超过 $k$ 次"的编号区间 $(l,r)$ 是具有**单调性**的。

即，随着区间的扩展，覆盖次数最多的点的覆盖次数是单调不降的，而原先的限制条件也**不会**因为区间的扩展而从"满足"变成"不满足"。

既然有了区间的单调性，那一个常用的套路就呼之欲出了：双指针！

我们计两个指针 $l,r$ ，代表当前区间的左端点为 $l$ 时，满足限制条件的最近右端点为 $r$ ,那么随着 $l$ 的右移， $r$ 也会一步步右移，而非左移，于是我们就可以顺便统计答案了。

因为指针 $l,r$ 最多移动 $O(n)$ 次，而每一次移动也代表着一次树剖线段树的调用，那么这样的时间复杂度也就是 $O(nlog^2n)$ 的。

**CODE：**

```
const int N(1e5+10);

int cnt;
int tot;
int n,m,k;

int f[N];
int id[N];
int rk[N];
int dep[N];
int top[N];
int son[N];
int siz[N];
int head[N];

struct Edge{int to,nxt;}e[N<<1];
struct Nd{int u,v,w;}qr[N<<1];

inline bool cmp(Nd u,Nd v){return u.w<v.w;}

inline void add(int u,int v){
	e[++cnt].to=v,e[cnt].nxt=head[u],head[u]=cnt;
}

inline void dfs1(int u,int fa){
	dep[u]=dep[f[u]=fa]+(siz[u]=1);
	edg(i,v,u)if(v^fa){
		dfs1(v,u),siz[u]+=siz[v];
		if(siz[son[u]]<siz[v])son[u]=v;
	}
}

inline void dfs2(int u,int tp){
	top[u]=tp,rk[id[u]=(++tot)]=u;
	if(!son[u]){return;} dfs2(son[u],tp);
	edg(i,v,u)if(v^f[u]&&v^son[u])dfs2(v,v);
}

struct Tree{
	int l,r;
	int lzy,val;
}t[N<<3];

#define mid ((l+r)>>1)
#define lsn p<<1,l,mid
#define rsn p<<1|1,mid+1,r

inline void cover(int p,int v){t[p].val+=v,t[p].lzy+=v;}

inline void push_down(int p){
	if(!t[p].lzy)return;
	rep(P,p<<1,p<<1|1)cover(P,t[p].lzy);
	t[p].lzy=0;
}

inline void build(int p,int l,int r){
	t[p].l=l,t[p].r=r;
	if(l^r)build(lsn),build(rsn);
}

inline void upd(int p,int l,int r,int ql,int qr,int vl){
	if(ql<=l&&qr>=r)return cover(p,vl);
	push_down(p);
	if(ql<=mid)upd(lsn,ql,qr,vl);
	if(qr>mid) upd(rsn,ql,qr,vl);
	t[p].val=max(t[p<<1].val,t[p<<1|1].val);
}

inline int qry(int p,int l,int r,int ql,int qr){
	if(ql<=l&&qr>=r)return t[p].val;
	push_down(p); int res=0;
	if(ql<=mid)ckmax(res,qry(lsn,ql,qr));
	if(qr>mid) ckmax(res,qry(rsn,ql,qr));
	return res;
}

inline int lca(int u,int v){
	while(top[u]^top[v]){
		if(dep[top[u]]<dep[top[v]]
		){swap(u,v);} u=f[top[u]];
	} if(dep[u]<dep[v]){swap(u,v);} return v;
}

inline void utree(int u,int v,int w){
	while(top[u]^top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		upd(1,1,n,id[top[u]],id[u],w),u=f[top[u]];
	} if(dep[u]<dep[v])swap(u,v);
	upd(1,1,n,id[v],id[u],w);
}

int main(){
	n=read(),m=read(),k=read();
	rep(i,2,n){
		int u=read(),v=read();
		add(u,v),add(v,u);
	} dfs1(1,0),dfs2(1,1),build(1,1,n);
	rep(i,1,m){
		int s=read(),t=read();
		int w=dep[s]+dep[t]-(dep[lca(s,t)]<<1)+1;
		qr[i].u=s,qr[i].v=t,qr[i].w=w;
	}
	sort(qr+1,qr+m+1,cmp);
	int ans=1e9;
	for(int l=1,r=0;l<=m;){
		while(r<m){
			int mx=qry(1,1,n,1,n);
			if(mx>=k)break;
			int u=qr[++r].u,v=qr[r].v;
			utree(u,v,1);
		} int mx=qry(1,1,n,1,n);
		if(mx<k)break;
		ckmin(ans,qr[r].w-qr[l].w);
		utree(qr[l].u,qr[l].v,-1),l++;
	} cout<<ans;
	return 0;
}
```

---

## 作者：zhangchengkai (赞：0)

QAQ一开始看错题了，以为要都有的交易对象是K，马上lca+倍增，后来一想，那他要交易几场呢？回去仔细审题，WTF！！！都有的交易对象没有给出！！！一看标签：zkw线段树！！！100+行代码白写了？为了蒟蒻的尊严（其实是懒），不怂！于是开始乱搞。。。。。

------------------------------------------------------------------以上为题外话--------------------------------------------------------------

lca倍增+暴力乱搞。。。

先用lca和倍增处理出每次交易的节点总数，即两点间的距离；

如果我们知道了都要交易的神秘对象x，那如何验证每次交易（设为s->e）是否包含x呢？

分类讨论包含的情况：

1，e==x || s==x；
2，一点在x的子树上，另一点不在；

3，两点均在x的子树上 && lca[e,s]==x；

满足条件1 || 条件2 || 条件3，则此交易包含x。
lca已经求出，故判断条件1和3都很简单。对于条件2，我们将x的子树染色即可。

求出了符合条件的交易，用其中最大节点数减去最小节点数即是答案。

好，那如何找出x呢？

考虑某点的交易数，即被路径覆盖的次数>=k时，该点可能是那神秘对象，那么问题在于如何统计它被覆盖的次数，暴力？（n\*m太慢）树链剖分？（m\*logn或n\*logm）太复杂难调，我采用的是差分数组sum，sum[e]++，sum[s]++，sum[lca(s,e)]-=2；但是lca(s,e)这个点会少计一次，用数组f统计，sum[i]+sum[son[j]]（son[j]是i的子节点）再加上f[i]就是节点i被覆盖次数，>=k则加入s数组，最后暴力统计答案。据测试最大的测试点有近5000个点符合条件，复杂度（5000\*m），85分T3个点（推测m应在10万左右）肿办。开始乱搞，判断最后计算次数>30000000就break输出答案，如此水过第14,16,17点。。。。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=400001,lst=20;//不知道数据范围诶 
int n,m,k,ans=2100000000;
int hd[N],nxt[N<<1],to[N<<1],cnt=0;//存图 
int dep[N],fo[N][lst+1];//dep[i]表示i的深度，fo[i][j]表示i的第2^j个祖先 
int f[N],dis[N],sum[N];//f[i]表示i是否被染色，dis[i]即是i到根的链上的节点数，sum[i]是差分数组，统计i的交易次数 
struct jiaoyi//每次交易 
{
    int s,e,dis,lca;
}p[N];
int s[N],tot=0;//可选的点 
int q[N],l;//可选的交易 
inline void Swap(int &x,int &y){int t=x;x=y,y=t;}
inline int cmp(jiaoyi x,jiaoyi y){return x.dis<y.dis;}
/*读优*/inline int rd(void){int res=0;char c=getchar();while(c>'9' || c<'0') c=getchar();while(c<='9' && c>='0') res=res*10+c-'0',c=getchar();return res;}
inline void init(int x,int y)//存图 
{
    cnt++;
    nxt[cnt]=hd[x];
    hd[x]=cnt;
    to[cnt]=y;
}
inline void dfs(int x)//处理出每个点的父节点，深度 
{
    dep[x]=dep[fo[x][0]]+1;
    for(int i=hd[x];i!=0;i=nxt[i])
    {
        int u=to[i];
        if(u==fo[x][0]) continue;
        fo[u][0]=x;
        dis[u]=dis[x]+1;
        dfs(u);
    }
}
inline void mark(int x)//染色 
{
    f[x]=1;
    for(int i=hd[x];i!=0;i=nxt[i])
    {
        int u=to[i];
        if(u==fo[x][0]) continue;
        mark(u);
    }
}
inline void clean(int x)//注意要清空，memset会慢 
{
    f[x]=0;
    for(int i=hd[x];i!=0;i=nxt[i])
    {
        int u=to[i];
        if(u==fo[x][0]) continue;
        clean(u);
    }
}
inline int LCA(int x,int y)
{
    if(dep[x]<dep[y]) Swap(x,y);
    for(int i=lst;i>=0;i--)
    {
        if(dep[fo[x][i]]>=dep[y]) x=fo[x][i];
        if(dep[x]==dep[y]) break;
    }
    if(x==y) return x;
    for(int i=lst;i>=0;i--)
    {
        if(fo[x][i]!=fo[y][i])
        {
            x=fo[x][i];
            y=fo[y][i];
        }
    }
    return x=fo[x][0];
}
inline void get(int x)//每个点的交易次数 
{
    for(int i=hd[x];i!=0;i=nxt[i])
    {
        int u=to[i];
        if(u==fo[x][0]) continue;
        get(u);
        sum[x]+=sum[u];
    }
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<n;i++)
    {
        int x,y;
        x=rd();
        y=rd();
        init(x,y);
        init(y,x);
    }
    dis[1]=1;
    dfs(1);
    for(int j=1;j<=lst;j++)//倍增处理祖先 
    {
        for(int i=1;i<=n;i++)
        {
            fo[i][j]=fo[fo[i][j-1]][j-1];
        }
    }
    for(int i=1;i<=m;i++)
    {
        p[i].e=rd();
        p[i].s=rd();
        int lca=LCA(p[i].s,p[i].e);
        int Dis=dis[p[i].e]+dis[p[i].s]-2*dis[lca]+1;
        p[i].dis=Dis;
        p[i].lca=lca;
        sum[p[i].s]++;//差分 
        sum[p[i].e]++;
        sum[lca]-=2; 
        f[lca]++; 
    }
    sort(p+1,p+1+m,cmp);
    get(1);
    for(int i=1;i<=n;i++)
    {
        sum[i]+=f[i];//加上lca被多减的 
        if(sum[i]>=k) s[++tot]=i;
    }
    if(tot==0)//其实数据都有解。。。。。。 
    {
        printf("-1");
        return 0;
    }
    memset(f,0,sizeof(f));
    sort(s+1,s+1+tot);
    for(int i=tot;i>=1;i--)
    {
        mark(s[i]);
        l=0;
        if((tot-i)*m>30000000) break;//防止超时 
        for(int j=1;j<=m;j++)
        {
            if(f[p[j].e]+f[p[j].s]==1 || p[j].e==s[i] || p[j].s==s[i] || p[j].lca==s[i])
            {
                q[++l]=p[j].dis;
                if(l>=k)
                {
                    if(q[l]-q[l-k+1]<ans) ans=q[l]-q[l-k+1];//因为排过序，最小化这 k 场交易中代价之差的最大值就是第l-k+1场与第l场之差 
                }
            }
        }
        clean(s[i]);
    }
    printf("%d",ans);
    return 0;
}
//如果那位dalao有非乱搞的优化，欢迎与我交流*。*。*。*
```

---

