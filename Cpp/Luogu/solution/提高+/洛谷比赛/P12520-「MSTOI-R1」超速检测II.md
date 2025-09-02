# 「MSTOI-R1」超速检测II

## 题目背景

以此纪念某位七年级参加 NOIP，八年级挂在 CSP-S T2 的大佬。

## 题目描述

小 D 新入职了某国的交管部门，他的第一个任务是负责国家的一条长度为 $L$ 的南北主干道的车辆超速检测。为了考考小 D，小 W 制造了一辆速度为 $ \infty $ 的汽车（这真的是汽车吗？），因此从点 $i$ 到点 $i+1$ 的时间可以为 $0$。

每一天早上，小 W 的车将会出现在主干道上，并从主干道上最南端   $1$ 号点的位置驶入向北行驶至最北端的 $n$ 号点。主干道上设置了 $m$ 组测速仪，其中第 $i$ 组测速仪测量主干道上任意一辆车从点 $l_i$ 到点 $r_i$ 所花费的时间。若这辆车的所花时间**小于**道路限制时间 $V_i$，那么这辆车就会被判定为超速。

然而，交通部门的政策总是朝令夕改。每天交通部门都会在凌晨增加或修改一条限制并在每天晚上将其删除或改回。~~为了睡懒觉，~~ 小 W 每天都会计算从 $ 1 $ 点到 $ n $ 点所需的最短时间。
由于 $n$ 很大，小 W 想要使用编程解决这个问题，然而他不会，于是小 W 找到了你。

## 说明/提示

对于 $20\%$ 的数据，$1\le n,m\le 100$，$1\le d\le 20$，$1\le V_i\le1000$。

对于 $50\%$ 的数据，$1\le n,m\le 1000$，$1\le d\le 1000$，$1\le V_i\le10^5$。

对于 $100\%$ 的数据，$1\le l_i<r_i\le n\leq 10^5$，$1\le V_i\le 10^9$ ，$1\le m,d\leq 10^5$。不存在任何一对初始限制使得 $l_i=l_j$ 且 $r_i=r_j$。

## 样例 #1

### 输入

```
5 6 4
1 2 3
2 3 4
3 4 5
4 5 6
1 5 25
1 4 10
1 2 3
1 5 17
2 3 1
2 4 20```

### 输出

```
25
18
25
29```

# 题解

## 作者：TallBanana (赞：8)

这里是验题人的超级复杂 tj。这个题我的评价是

![](https://cdn.luogu.com.cn/upload/image_hosting/u7ph7x1p.png)

**不带修的问题**：

* 结论：答案等于最大的 $\sum_{u\in S} V_u$，其中 $S$ 满足：
  * $S$ 是速度限制组成的集合。
  * $S$ 中的限制两两 $[l,r]$ 不交。

于是我们可以有一个很显然的 dp，$f_i$ 表示当前考虑到点 $i$，最大的 $\sum S$ 是多少。转移是 $f_{i}=\max (f_{i-1},f_{l}+v)$，其中 $l,v$ 是以 $i$ 为 $r$ 的一个速度限制。复杂度 $O(d(m+n))$。

> 对结论的证明：\
> 按照右端点大小顺序考虑每个限制。每次新考虑一个限制，然后我们只需要满足当前考虑过的限制是合法的即可。\
> 不妨令 $T$ 为与当前加入的这个限制 $[l,r]$ 有交的限制集合。\
> 如果转移取的是 $f_l+v$，那说明 $v$ 可以满足 $T$ 中的限制，而 $f_l$ 满足了前面的限制。\
> 如果转移取的是 $f_{i-1}$，那说明当前限制被 $T$ 中的满足了。

**考虑原问题**：

对于一个询问，发现我们不能选 $[l,r]$。所以如果询问的 $V$ 比原来的大，那么就好搞。否则我们需要特殊处理。考虑我们再做一个反着 dp 的数组 $g_i$，那么分讨：
* $[l,r]$ 没有被 $S$ 中的一个限制完全覆盖，这里的可能答案为 $\max_{i=l+1\sim r-1} f_i+g_i$，st 表处理。
* $[l,r]$ 被 $S$ 中的一个限制完全覆盖。这部分有点麻烦。我们在下面考虑这部分内容。

先离线，然后对点扫描线。以 $i$ 结尾的可能有询问或原本的限制。把询问按照左端点大小排序，把以 $i$ 结尾的询问加入线段树。对于原本的限制 $[l,i,V]$，我们把左端点在 $[l+1,i]$ 内的询问用 $f_l+g_i+V$ 进行更新。

然后我们按此操作，将整个序列反过来再做一边，于是对于一个原本的限制 $[l,r,V]$，我们对于 $l\le u\le v\le r$，且满足 $u\neq l \mathrm{\ or\ } v\neq r $ 的询问进行了更新。

于是我们完成了这个题目。复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL,LL> PII;
const LL N=1e5+10;
LL n,m,d,f[N],g[N],st[N][17],lg[N],ans[N],zsw[N];
vector<PII> L[N],R[N];
LL query(LL l,LL r)
{
	LL t=lg[r-l+1];
	return l>r?0:max(st[l][t],st[r-(1<<t)+1][t]);
}

namespace SegT
{
	struct node { LL l,r,val,tag; }t[N<<2];
	struct zxz { LL l,r,id; }a[N];
	vector<LL> ad[N];
	#define ls (k<<1)
	#define rs (k<<1|1)
	#define mid (l+r>>1)
	bool cmp(zxz a,zxz b) { return a.l<b.l; }
	void addtag(LL k,LL v)
	{
		t[k].tag=max(t[k].tag,v);
		t[k].val=max(t[k].val,v);
	}
	void pushdown(LL k)
	{
		addtag(ls,t[k].tag);
		addtag(rs,t[k].tag);
		t[k].tag=0;
	}
	void modify(LL k,LL l,LL r,LL L,LL R,LL mx)
	{
		if(l>R||L>r) return;
		if(L<=l&&r<=R) return addtag(k,mx);
		pushdown(k);
		modify(ls,l,mid,L,R,mx);
		modify(rs,mid+1,r,L,R,mx);
	}
	void miku(LL k,LL l,LL r,LL x)
	{
		if(l>x||r<x) return;
		if(l==r) return t[k].val=0,void();
		pushdown(k);
		miku(ls,l,mid,x);
		miku(rs,mid+1,r,x);
	}
	LL query(LL k,LL l,LL r,LL x)
	{
		if(l>x||r<x) return 0;
		if(l==r) return t[k].val;
		pushdown(k);
		return max(query(ls,l,mid,x),query(rs,mid+1,r,x));
	}
	void solve()
	{
		for(int i=1;i<=n;i++) zsw[i]=0,ad[i].clear();
		for(int i=1;i<=d;i++) miku(1,1,d,i);
		sort(a+1,a+d+1,cmp);
		for(LL i=1;i<=d;i++) zsw[a[i].l]=max(zsw[a[i].l],i);
		for(int i=1;i<=n;i++) zsw[i]=max(zsw[i],zsw[i-1]);
		for(int i=1;i<=d;i++) ad[a[i].r].push_back(i);
		for(int i=1;i<=n;i++)
		{
			for(auto j:ad[i]) miku(1,1,d,j);
			for(auto j:L[i]) 
				modify(1,1,d,zsw[j.first]+1,zsw[i],f[j.first]+j.second+g[i]);
		}
		for(int i=1;i<=d;i++)
			ans[a[i].id]=max(ans[a[i].id],query(1,1,d,i));
	}
}
using namespace SegT;
int main()
{
	scanf("%lld%lld%lld",&n,&m,&d);
	for(int i=1;i<=m;i++)
	{
		LL l,r,v;
		scanf("%lld%lld%lld",&l,&r,&v);
		L[r].push_back({l,v});
		R[l].push_back({r,v});
	}
	for(int i=1;i<=n;i++,f[i]=f[i-1])
		for(auto j:L[i]) f[i]=max(f[i],f[j.first]+j.second);
	for(int i=n;i>=1;i--,g[i]=g[i+1])
		for(auto j:R[i]) g[i]=max(g[i],g[j.first]+j.second);
	for(int i=1;i<=n;i++) st[i][0]=f[i]+g[i];
	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j+(1<<i)-1<=n;j++)
			st[j][i]=max(st[j][i-1],st[j+(1<<i-1)][i-1]);
	for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
	for(int i=1;i<=d;i++)
	{
		LL l,r,v;
		scanf("%lld%lld%lld",&l,&r,&v);
		a[i]=(zxz){l,r,i};
		ans[i]=max(f[l]+v+g[r],query(l+1,r-1));
	}
	solve();
	reverse(f+1,f+n+1);
	reverse(g+1,g+n+1);
	swap(f,g);
	for(int i=1;i<=n;i++) L[i].clear();
	for(int i=1;i<=n;i++)
		for(auto j:R[i])
			L[n-i+1].push_back({n-j.first+1,j.second});
	for(int i=1;i<=d;i++) a[i]=(zxz){n-a[i].r+1,n-a[i].l+1,a[i].id};
	solve();
	for(int i=1;i<=d;i++) printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：LiaoYF (赞：6)

![](https://cdn.luogu.com.cn/upload/image_hosting/5kpunfq8.png)

陈队 /bx。

## 做法


设到达点 $i$ 的时间为 $a_i$，则题目的限制 $(l,r,V)$ 相当于 $a_r - a_l \geq V$。这是一个[差分约束](https://oi-wiki.org/graph/diff-constraints/)的形式，连一条 $l$ 到 $r$，边权为 $V$ 的有向边，跑最长路即可得到最小的 $a_n$。连出来的图一定是一个 DAG，最长路可以使用拓补排序。可以获得 $50$ 分。

现在问题就是 DAG 每次修改一条边的边权，求最长路。设从 $1$ 到 $i$ 的最长路为 $dis_i$，从 $i$ 到 $n$ 的最长路为 $dis2_i$。操作为将边 $(u,v)$ 的边权修改为 $w$。

- 走修改的那条边，答案为 $dis_u+w+dis2_v$。
- 不走修改的那条边。因为这个图是一个拓补序为 $1,2,...,n$ 的 DAG，所以一条从 $1$ 到 $n$ 的路径不经过边 $(u,v)$ 的充要条件是经过了一个在区间 $(u,v)$ 之间的点，或者经过了一条越过 $(u,v)$ 的边。

对于第一种情况，答案为：$\max_{u+1\leq i \leq v-1} dis_i+dis2_i$，使用 st 表处理即可。

对于第二种情况，答案为：$\max_{(x, y,z) \in E , x \leq u, \, y \geq v} dis_x+z+dis2_y$，这是矩形求最大值，离线下来扫描线即可。注意实现的时候这条边不能与修改的边是同一条边。

最终，三种情况取最大值，得到答案。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define i128 __int128
#define ALL(x) x.begin(),x.end()
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif
using namespace std;
const int INF=1e18;
const int N=100005;
const int MOD=1e9+7,MOD2=998244353;
int n,m,q,dis[N],dis2[N];
struct edge{
    int u,v,w,id;
}a[N];
map<int,int> G[N],G2[N];
int ans[N];
vector<edge> b;
void adde(int u,int v,int w){
    if(!G[u].count(v)){
        G[u][v]=G2[v][u]=w;
        b.push_back({u,v,w});
    }
}
int st[N][20];
int querymax(int l,int r){
    if(l>r)return 0;
    int x=log2(r-l+1);
    return max(st[l][x],st[r-(1ll<<x)+1][x]);
}

void init(){
    for(int i=2;i<=n;i++){
        dis[i]=-INF;
    }
    for(int i=1;i<=n;i++){
        dis[i+1]=max(dis[i+1],dis[i]);
        for(auto[v,w]:G[i]){
            if(dis[i]+w>dis[v]){
                dis[v]=dis[i]+w;
            }
        }
    }

    for(int i=1;i<n;i++){
        dis2[i]=-INF;
    }
    for(int i=n;i>=1;i--){
        dis2[i-1]=max(dis2[i-1],dis2[i]);
        for(auto[v,w]:G2[i]){
            dis2[v]=max(dis2[v],dis2[i]+w);
        }
    }
    for(int i=1;i<=n;i++){
        st[i][0]=dis[i]+dis2[i];
    }
    for(int j=1;j<20;j++){
        for(int i=1;i+(1ll<<(j-1))<=n;i++){
            st[i][j]=max(st[i][j-1],st[i+(1ll<<(j-1))][j-1]);
        }
    }

}
struct BIT{
    int tr[N];
    inline int lowbit(int x){
        return x&(-x);
    }
    void modify(int x,int k){
        for(int i=x;i<=n;i+=lowbit(i)){
            tr[i]=max(tr[i],k);
        }
    }
    int query(int x){
        int res=0;
        for(int i=x;i;i-=lowbit(i)){
            res=max(res,tr[i]);
        }
        return res;
    }
}tr;
void solve(){
    b.push_back({0,INF,0});
    cin>>n>>m>>q;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        G[u][v]=G2[v][u]=w;
        b.push_back({u,v,w});
    }
    for(int i=1;i<=q;i++){
        cin>>a[i].u>>a[i].v>>a[i].w;
        a[i].id=i;
    }
    
    init();
    sort(a+1,a+q+1,[](edge x,edge y){return x.v!=y.v?x.v>y.v:x.u<y.u;});
    sort(b.begin(),b.end(),[](edge x,edge y){return x.v!=y.v?x.v>y.v:x.u<y.u;});
    int now=1;
    for(int i=1;i<=q;i++){
        while(now<b.size()&&b[now].v>=a[i].v){
            if(b[now].v==a[i].v&&b[now].u>=a[i].u)break;
            tr.modify(b[now].u,dis[b[now].u]+b[now].w+dis2[b[now].v]);
            now++;
        }
        ans[a[i].id]=dis[a[i].u]+a[i].w+dis2[a[i].v];
        ans[a[i].id]=max(ans[a[i].id],querymax(a[i].u+1,a[i].v-1));
        ans[a[i].id]=max(ans[a[i].id],tr.query(a[i].u));
        
    }

    for(int i=1;i<=q;i++){
        cout<<ans[i]<<"\n";
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int testcase,multitest=0;
    if(multitest)cin>>testcase;
    else testcase=1;
    while(testcase--){
        solve();
    }
    return 0;
}
```

---

