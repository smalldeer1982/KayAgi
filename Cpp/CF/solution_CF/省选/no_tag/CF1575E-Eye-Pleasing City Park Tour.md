# Eye-Pleasing City Park Tour

## 题目描述

There is a city park represented as a tree with $ n $ attractions as its vertices and $ n - 1 $ rails as its edges. The $ i $ -th attraction has happiness value $ a_i $ .

Each rail has a color. It is either black if $ t_i = 0 $ , or white if $ t_i = 1 $ . Black trains only operate on a black rail track, and white trains only operate on a white rail track. If you are previously on a black train and want to ride a white train, or you are previously on a white train and want to ride a black train, you need to use $ 1 $ ticket.

The path of a tour must be a simple path — it must not visit an attraction more than once. You do not need a ticket the first time you board a train. You only have $ k $ tickets, meaning you can only switch train types at most $ k $ times. In particular, you do not need a ticket to go through a path consisting of one rail color.

Define $ f(u, v) $ as the sum of happiness values of the attractions in the tour $ (u, v) $ , which is a simple path that starts at the $ u $ -th attraction and ends at the $ v $ -th attraction. Find the sum of $ f(u,v) $ for all valid tours $ (u, v) $ ( $ 1 \leq u \leq v \leq n $ ) that does not need more than $ k $ tickets, modulo $ 10^9 + 7 $ .

## 样例 #1

### 输入

```
5 0
1 3 2 6 4
1 2 1
1 4 0
3 2 1
2 5 0```

### 输出

```
45```

## 样例 #2

### 输入

```
3 1
1 1 1
1 2 1
3 2 0```

### 输出

```
10```

# 题解

## 作者：MyukiyoMekya (赞：5)

2log 和 1log 的点分、链分做法相信大家都会了。这里讲一下线性做法。

其实就是这位老哥的[做法](https://codeforces.com/contest/1575/submission/134392242) ，他现在还是速度榜第一。

考虑 $f,g_{u,0/1,d}$ 表示 $u$ 子树，最上面的连续段颜色，有几个连续段，的方案数以及和。

这玩意跟深度有关，所以可以直接长剖。

时间空间复杂度 $\mathcal O(n)$。

这里只讲我的实现方法。（部分参考了上面那位老哥实现）。

对每个节点开四个 `std::deque<std::pair<int,int> >` 来存 $f,g_{u,0/1}$ 和对应的前缀和。 

继承长儿子的时候就是要把两种颜色 dp 值合并，把 size 大的那个 swap 过来，

另一个暴力，因为每个颜色被干完后又会清零，所以复杂度对的。

选 size 大的原因是不用扩大空间，保证复杂度的正确性。

然后剩下的轻儿子怎么暴力怎么来就好了。

有一些小细节：

别真去用 `std::deque` 了，那玩意初始化空间常数毛估估有 100 倍（反正我是这样）

解决方法两个： 

1. 用传统方法手写内存池先根据算出的信息开好 dp 数组内存（参考磁暴）
2. 手写 deque（大致就是动态分配一些循环队列，然后满了就重构，开大 $\alpha$ 倍）

另外，请注意各种 $\mathcal O(1)$ 的小细节，

但是不影响正确性和整体复杂度而减少代码复杂度的 $\mathcal O(1)$ 小细节不用在意了，

~~否则可能真的调不出来了~~

[我的实现](https://codeforces.com/contest/1575/submission/140139766)

---

## 作者：EityDawn (赞：2)

# 思路：

统计两点间路径上颜色段数目 $\le k+1$ 的所有点对间路径上的点权之和。

点分治。对于当前的分治中心 $x$，$x$ 到其子树内的贡献很好求。现在需要考虑怎么合并新子树的答案。

记 $dis_i$ 为 $i$ 到分治中心的颜色段数目减 $1$，$val_i$ 为 $i$ 到分治中心的点权和，$col_i$ 为分治中心到 $i$ 的第一条边的颜色。

对于新子树的节点 $y$，若 $dis_y\le k$，我们还需求 $\sum_{dis_{z}\le k-dis_{y}} val_z+val_y-a_x$，其中 $z$ 还满足 $col_z=col_y$，而对于 $col_z\neq col_y$ 的 $z$，则需要求 $\sum_{dis_{z}\le k-dis_{y}-1} val_z+val_y-a_x$。显然可以开两个树状数组维护。

复杂度为 $O(n\log^2n)$。

```cpp
#include<bits/stdc++.h>
#define all(x) x.begin(),x.end()
#define mset(x,y) memset((x),(y),sizeof((x)))
#define mcpy(x,y) memcpy((x),(y),sizeof((y)))
#define FileIn(x) freopen(""#x".in","r",stdin)
#define FileOut(x) freopen(""#x".out","w",stdout)
#define debug(x) cerr<<""#x" = "<<(x)<<'\n'
#define Assert(x) if(!(x)) cerr<<"Failed: "#x" at line "<<__LINE__,exit(1)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 Int;
const int N=2e5+10,mod=1e9+7;
bool StM;
void Mod(int &x,int y)
{
    x+=y;
    if(x>=mod) x-=mod;
}
int n,k,m,a[N],rt=1;
struct edge{int to,val;};
vector<edge>G[N];
struct BIT{
    int c[N],d[N];
    #define lowbit(x) (x&-x)
    BIT(){mset(c,0);}
    void add(int x,int y)
    {
        ++x;
        while(x<=n)
            Mod(c[x],y),++d[x],x+=lowbit(x);
        return;
    } 
    void del(int x,int y)
    {
        ++x;
        while(x<=n)
            Mod(c[x],mod-y),--d[x],x+=lowbit(x);
    }
    int query(int x)
    {
        ++x;
        int sum=0;
        while(x)
            Mod(sum,c[x]),x-=lowbit(x);
        return sum;
    }
    int C(int x)
    {
        ++x;
        int sum=0;
        while(x)
            sum+=d[x],x-=lowbit(x);
        return sum;
    }
}t[2];
int siz[N],ma[N];
bool vis[N];
int Dis[N],Val[N],id[N];
int Son[N],top=0;
int All=0;
void GetMid(int now,int from)
{
    siz[now]=1,ma[now]=0;
    for(auto [to,val]:G[now])
    {
        if(to==from||vis[to]) continue;
        GetMid(to,now);
        siz[now]+=siz[to];
        ma[now]=max(ma[now],siz[to]);
    }
    ma[now]=max(ma[now],m-siz[now]);
    if(ma[now]<=m/2) rt=now;
}
void GetSon(int now,int from,int Sum,int dis,int col)
{
    Dis[now]=dis,Val[now]=(Sum+a[now])%mod;
    Son[++top]=now;
    for(auto [to,val]:G[now])
    {
        if(vis[to]||to==from) continue;
        if(val==col) GetSon(to,now,(Sum+a[now])%mod,dis,col);
        else GetSon(to,now,(Sum+a[now])%mod,dis+1,val);
    }
    return;
}
void Get(int now)
{
    Mod(All,a[now]);
    int l=0,r=0;
    for(auto [to,val]:G[now])
    {
        if(vis[to]) continue;
        int cur=top;
        GetSon(to,now,a[now],0,val);
        for(int i=cur+1;i<=top;i++)
        {
            if(Dis[Son[i]]<=k){
                Mod(All,Val[Son[i]]);
                l=1ll*t[val].C(k-Dis[Son[i]])*(Val[Son[i]]-a[now]+mod)%mod;
                Mod(l,t[val].query(k-Dis[Son[i]]));Mod(All,l);
                r=1ll*t[val^1].C(k-Dis[Son[i]]-1)*(Val[Son[i]]-a[now]+mod)%mod;
                Mod(r,t[val^1].query(k-Dis[Son[i]]-1));Mod(All,r);
            }
            id[Son[i]]=val;
        }
        for(int i=cur+1;i<=top;i++)
            t[val].add(Dis[Son[i]],Val[Son[i]]);
    }
    while(top)
        t[id[Son[top]]].del(Dis[Son[top]],Val[Son[top]]),top--;
    return;
}
void Calc(int now)
{
    vis[now]=1,Get(now);
    for(auto [to,now]:G[now])
    {  
        if(vis[to]) continue;
        GetMid(to,0),m=siz[to];
        GetMid(to,0),Calc(rt);
    }
    return;
}
void Main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1,x,y,z;i<n;i++)
    {
        cin>>x>>y>>z;
        G[x].push_back({y,z});
        G[y].push_back({x,z});
    }
    m=n,GetMid(rt,0);Calc(rt);
    cout<<All<<'\n';
}
bool EdM;
int main()
{
    cerr<<fabs(&StM-&EdM)/1024.0/1024.0<<" MB\n";
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int StT=clock();
    int T=1;
    while(T--) Main();
    int EdT=clock();
    cerr<<1e3*(EdT-StT)/CLOCKS_PER_SEC<<" ms\n";
    return 0;
}
```

---

## 作者：gdf_yhm (赞：1)

[CF1575E](https://www.luogu.com.cn/problem/CF1575E)

### 思路

点分治，记录当前子树到分治中心的权值和和换车次数。将新子树的答案合并时分类讨论分治中心到子树祖先 $u\to v$ 的颜色。树状数组维护前缀和。复杂度 $O(n\log^2 n)$。

### code

```cpp
int n,k,a[maxn],ans;
int head[maxn],tot;
struct nd{
	int nxt,to,fl;
}e[maxn<<1];
void add(int u,int v,int fl){e[++tot]={head[u],v,fl};head[u]=tot;}
int siz[maxn],w[maxn],rt,sum;
bool vis[maxn];
void getrt(int u,int fa){
	siz[u]=1,w[u]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa||vis[v])continue;
		getrt(v,u);
		siz[u]+=siz[v],w[u]=max(w[u],siz[v]);
	}
	w[u]=max(w[u],sum-siz[u]);
	if(w[u]<=sum/2)rt=u;
}
int dis[maxn],num[maxn],col[maxn];
vector<int> id[maxn];
int inc(int u,int v){(u+=v)>=mod&&(u-=mod);return u;}
void dfs(int u,int fa,int tp){
	siz[u]=1;dis[u]=inc(dis[fa],a[u]);
	id[tp].push_back(u);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa||vis[v])continue;
		col[v]=e[i].fl;num[v]=num[u]+(col[u]!=col[v]);
		dfs(v,u,tp);siz[u]+=siz[v];
	}
//	cout<<u<<" "<<tp<<" "<<dis[u]<<" "<<num[u]<<"\n";
}
struct bit{
	pii add(pii u,pii v){return {inc(u.fi,v.fi),inc(u.se,v.se)};}
	pii tree[maxn];
	#define lb(x) (x&(-x))
	void upd(int x,int m,pii w){
		while(x<=m)tree[x]=add(tree[x],w),x+=lb(x);
	}
	pii que(int x){
		pii res={0,0};
		while(x>0)res=add(res,tree[x]),x-=lb(x);
		return res;
	}
}t[2];
void sovle(int u){
	vis[u]=1;ans=inc(ans,a[u]);
	siz[u]=1;dis[u]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(vis[v])continue;
		id[v].clear();num[v]=1;col[v]=e[i].fl;dfs(v,u,v);siz[u]+=siz[v];
	}
	for(int i=1;i<=siz[u];i++)t[0].tree[i]=t[1].tree[i]={0,0};
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(vis[v])continue;
		for(int p:id[v]){
			pii res1=t[e[i].fl].que(min(k-num[p]+1,siz[u])),res2=t[e[i].fl^1].que(min(k-num[p],siz[u]));
			(ans+=(dis[p]+a[u])*(res1.se+res2.se)+res1.fi+res2.fi)%=mod;
			if(num[p]<=k)ans=inc(ans,inc(dis[p],a[u]));
		}
		for(int p:id[v])t[e[i].fl].upd(num[p],siz[u],{dis[p],1});
	}
//	cout<<u<<" "<<ans<<"\n";
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(vis[v])continue;
		sum=siz[v];getrt(v,u);sovle(rt);
	}
}
void work(){
	n=read();k=read()+1;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),fl=read();
		add(u,v,fl),add(v,u,fl);
	}
	sum=n;getrt(1,0);sovle(rt);
	printf("%lld\n",ans);
}
```

---

