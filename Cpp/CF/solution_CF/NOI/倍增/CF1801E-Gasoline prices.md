# Gasoline prices

## 题目背景

可以在 [P13528](https://www.luogu.com.cn/problem/P13528) 评测本题。

## 题目描述

伯利兰是一个由 $n$ 个城市组成的庞大国家。伯利兰的公路网络可以被看作是一棵有根树，也就是说全国一共有 $n - 1$ 条道路，并且任意两个城市之间都恰好有一条路径相连，且不会重复经过同一个城市。为了方便表示，每个城市 $i$ 都有一个固定的城市 $p_i$，它表示从城市 $i$ 出发前往城市 $1$ 时，首先要到达的城市。换句话说，如果将树的根设为城市 $1$，那么 $p_i$ 就是城市 $i$ 的父节点。

每个城市都有一个加油站。每个加油站的油价都有一个固定的区间，在这个区间内可以选择任意一个价格。城市 $i$ 的加油站油价可以是 $l_i$ 到 $r_i$ 之间的任意整数（包括两端）。

伯利兰的国王是个顾家的好父亲，他连续 $m$ 年每年都迎来了两位儿子的出生。国王的孩子们从小就参与国家事务，每年年末，他们会检查油价是否公平。自出生起，第 $i$ 年出生的两个孩子分别负责检查从城市 $a_i$ 到城市 $b_i$ 的路径，以及从城市 $c_i$ 到城市 $d_i$ 的路径上的油价。

检查的方式如下：两个孩子分别同时从城市 $a_i$ 和 $c_i$ 出发。第一个孩子沿着从 $a_i$ 到 $b_i$ 的路径前进，第二个孩子则沿着从 $c_i$ 到 $d_i$ 的路径前进。他们会依次检查：起点 $a_i$ 和 $c_i$ 的油价是否相同，然后检查路径上的第二个城市是否油价相同，依此类推，直到终点 $b_i$ 和 $d_i$ 的油价也要一致。保证从 $a_i$ 到 $b_i$ 的路径长度和从 $c_i$ 到 $d_i$ 的路径长度相同。

所有加油站都必须严格遵守法律，因此所有的油价检查都不能出现违规。请你帮助伯利兰的加油站计算，在 $m$ 年内，他们有多少种合法的油价设置方式。换句话说，对于每个 $i$ 从 $1$ 到 $m$，请计算在前 $i$ 年出生的所有王子进行检查后，所有检查都不出现违规，且每个加油站的油价在允许区间内的情况下，总共有多少种油价分配方案。由于答案可能很大，请对 $10^9 + 7$ 取模输出。


## 说明/提示

### 样例解释

以第一个样例为例：

- 在头两位王子出生后，城市 $1$ 和城市 $2$ 的油价必须相同。可以在允许的区间内为城市 $1$ 和 $2$ 选择相同的油价方式有 $2$ 种。剩下城市 $3$ 和 $4$ 的油价分别有 $3$ 种和 $3$ 种选择。总方案数为 $2 \times 3 \times 3 \times 1 = 18$。
- 第二对王子检查的是 $1-2$ 和 $2-1$，这要求城市 $1$ 和 $2$ 的油价一致，这个条件已经满足，因此方案数不变。
- 第三对王子检查的是 $3-1-2-4$ 和 $4-2-1-3$，这要求城市 $3$ 和 $4$ 的油价相同，城市 $1$ 和 $2$ 的油价也要相同。城市 $1$ 和 $2$ 已经一致，而城市 $3$ 和 $4$ 可以有 $2$ 种相同的油价选择。总方案数为 $2 \times 2 \times 1 = 6$。
- 第四对王子检查的是 $3-1-2-4$ 和 $3-1-2-5$，这要求城市 $4$ 和 $5$ 的油价一致，而城市 $3$ 和 $4$ 已经一致，因此 $3$、$4$、$5$ 三个城市的油价都要一致。城市 $3$ 的油价不能超过 $3$，城市 $5$ 的油价不能低于 $4$，因此不存在满足条件的方案，答案为 $0$。

## 样例 #1

### 输入

```
5
1 1 2 2
2 4
1 3
1 3
2 4
4 4
4
1 1 2 2
1 2 2 1
3 4 4 3
3 4 3 5```

### 输出

```
18
18
4
0```

## 样例 #2

### 输入

```
8
1 2 3 4 5 8 6
3 7
2 6
3 8
5 10
5 8
2 9
3 8
6 8
4
1 3 7 6
4 1 5 7
1 7 7 1
1 8 2 7```

### 输出

```
720
120
120
1```

# 题解

## 作者：jun头吉吉 (赞：8)

## 题意

有一棵树，树上有 $n$ 个点，每个点上有一个整数，第 $i$ 个点上数字范围是 $l_i$ 到 $r_i$。

$q$ 次询问每次会**新增**一个限制，每次给出 $a,b,c,d$，保证 $a\to b$ 的长度与 $c\to d$ 的长度相同，要求 $a\to b$ 路径上的第 $i$ 个点和 $c\to d$ 第 $i$ 个点上的数字相同。

每次询问后输出写数字的方案数对 $10^9+7$ 取模。

## 题解

我们把两个需要相同的点用并查集合并。然后并查集每一个集合的贡献就是 $\max(0,\min_{i\in S}r_i-\max_{i\in S}l_i+1)$，然后答案就是所有集合的贡献乘起来。

然后只有 $\mathcal O(n)$ 次有效的合并操作，所以只要每一次合并的两个点原来不在一个集合，这部分的复杂度就是正确的。

然后我们要找到 $a\to b$ 路径上和 $c\to d$ 路径上第一个不是同一个集合的。刚才的并查集用按秩合并，就能知道每一个点现在是哪一个集合，然后找到第一个不同的直接二分+哈希即可。

然后获取 Hash 的时候要一条链求和，链求和可以用树状数组在 $\mathcal O(\log n)$ 时间内单次询问，所以总复杂度是 $\mathcal O(n\log^2n)$。

最后就是在 CF 上用哈希会不会被叉的问题，事实上你不要像T宝那样 hash base 选 $10$，随机选一个数就不太会被叉了。

## 代码
```cpp
const int N=2e5+10;
int n,q,fa[N];vector<int>e[N];
int sz[N],dfn[N],idfn[N],cnt,top[N],dep[N];
mint ans=1;int pa[N],l[N],r[N];set<int>ids[N];
int find(int x){return x==pa[x]?x:pa[x]=find(pa[x]);}
void dfs1(int u){
	sz[u]=1;dep[u]=dep[fa[u]]+1;
	for(auto v:e[u])dfs1(v),sz[u]+=sz[v];
}
void dfs2(int u){
	dfn[u]=++cnt,idfn[cnt]=u;
	if(!top[u])top[u]=u;
	if(!e[u].size())return;
	pair<int,int>mx(0,0);for(auto v:e[u])chkmx(mx,mp(sz[v],v));
	top[mx.se]=top[u];dfs2(mx.se);
	for(auto v:e[u])if(v!=mx.se)dfs2(v);
}
int lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=fa[top[x]];
	}
	return dep[x]>=dep[y]?y:x;
}
int getdep(int x,int d){
	assert(dep[x]>=d);
	while(dep[top[x]]>d)x=fa[top[x]];
	return idfn[dfn[top[x]]+d-dep[top[x]]];
}
struct mytree{
	struct BIT{
		mint t[N];
		void add(int x,mint v){for(;x<=n;x+=lowbit(x))t[x]+=v;}
		void add(int l,int r,mint v){add(l,v);add(r+1,-v);}
		mint qry(int x){mint res=0;for(;x;x-=lowbit(x))res+=t[x];return res;}
	}T;
	mint val[N];
	void mdf(int x,mint v){
		T.add(dfn[x],dfn[x]+sz[x]-1,v-val[x]);
		val[x]=v;
	}
	mint get(int x,int y){
		assert(dfn[y]<=dfn[x]&&dfn[x]<dfn[y]+sz[y]);
		return T.qry(dfn[x])-T.qry(dfn[fa[y]]);
	}
}A,B;mint pw[N],ipw[N];
int getkth(int u,int v,int l,int k){
	int len=dep[u]+dep[v]-2*dep[l]+1;
	if(k<=dep[u]-dep[l]+1)return getdep(u,dep[u]-k+1);
	else return getdep(v,dep[v]-len+k);
}
mint get(int u,int v,int l,int k){
	if(k<=dep[u]-dep[l]+1){
		int up=getdep(u,dep[u]-k+1);
		return B.get(u,up)*pw[dep[u]];
	}else{
		int len=dep[u]+dep[v]-2*dep[l]+1;
		int up=getdep(v,dep[v]-len+k);
		return (B.get(u,l)-B.val[l])*pw[dep[u]]+A.get(up,l)*ipw[dep[l]]*pw[dep[u]-dep[l]];
		// dep[l] -> dep[u]-dep[l]
	}
}
void merge(int x,int y){
	x=find(x),y=find(y);
	assert(x!=y);
	if(ids[x].size()<ids[y].size())swap(x,y);
	//insert y -> x
	pa[y]=x;
	ans/=r[y]-l[y]+1;
	ans/=r[x]-l[x]+1;
	chkmx(l[x],l[y]);chkmn(r[x],r[y]);
	ans*=max(0,r[x]-l[x]+1);
	for(auto u:ids[y])ids[x].insert(u),A.mdf(u,x*pw[dep[u]]),B.mdf(u,x*ipw[dep[u]]);
}
signed main(){
	pw[0]=1,pw[1]=rint(N,2*N);for(int i=2;i<N;i++)pw[i]=pw[i-1]*pw[1];
	ipw[0]=1,ipw[1]=1/pw[1];for(int i=2;i<N;i++)ipw[i]=ipw[i-1]*ipw[1];
	read(n);for(int i=2;i<=n;i++)read(fa[i]),e[fa[i]].pb(i);
	dfs1(1);dfs2(1);
	for(int i=1;i<=n;i++)read(l[i],r[i]),ans*=r[i]-l[i]+1,pa[i]=i,ids[i].insert(i);
	for(int i=1;i<=n;i++)A.mdf(i,i*pw[dep[i]]),B.mdf(i,i*ipw[dep[i]]);
	read(q);while(q--){
		int a,b,c,d;read(a,b,c,d);
		int l1=lca(a,b),l2=lca(c,d);
		int len=dep[a]+dep[b]-2*dep[l1]+1;
		while(get(a,b,l1,len)!=get(c,d,l2,len)){
			int l=1,r=len,ans=0;
			while(l<=r){
				if(get(a,b,l1,mid)!=get(c,d,l2,mid))ans=mid,r=mid-1;
				else l=mid+1;
			}
			merge(getkth(a,b,l1,ans),getkth(c,d,l2,ans));
		}
		writeln(ans.x);
	}
}
```

---

## 作者：Fzrcy (赞：7)


### 思路

设 $x_i$ 为从 $a$ 到 $b$ 的简单路径上的节点， $y_i$ 从 $c$ 到 $d$ 的简单路径上的节点。

那么每次操作就是使 $x_i$ 的汽油价格和 $y_i$ 一致，这个东西是具有传递性的，可以用并查集维护。

直接暴力做的复杂度是无法通过本题的。~~太对不起1024MB的内存了~~。

考虑维护更多的信息。不明显的，我们可以用并查集维护长度为 $2^i$ 的段。

具体地，设 $f2[i][x]$ 表示以 $x$ 为端点的向上长度为 $2^i$ 的的段所在的集合（方向向上）， $f2[i][x+n]$ 表示以 $x$ 为端点的向上长度为 $2^i$ 的的段（方向向下）所在的集合。

仍然考虑暴力合并两个长度为 $2^i$ 的段：

1. 若 $i=0$ 则直接合并两个点。

2. 若 $f2[i][x]$ 和 $f2[i][y]$ 在同一个集合中，直接退出。

3. 否则递归分别合并两个长度 $2^{i-1}$ 的段，并合并 $f2[i][x]$ 和 $f2[i][y]$ 所在的集合。

在实际中合并两个逆向的段和合并两个同向的段略有不同，请读者注意。

暴力合并两个点：

```cpp
// 合并两个点
void merge(int x,int y){
    x=find(x,f1),y=find(y,f1);
    if(x==y)return;
    ans=1ll*ans*1ll*ksm(max(0ll,1ll*(R[x]-L[x]+1)),mod-2)%mod;
    ans=1ll*ans*1ll*ksm(max(0ll,1ll*(R[y]-L[y]+1)),mod-2)%mod; // 撤销贡献
    f1[x]=y;
    L[y]=max(L[x],L[y]);
    R[y]=min(R[x],R[y]);
    ans=1ll*ans*1ll*1ll*max(0ll,1ll*(R[y]-L[y]+1))%mod; // 加上新贡献
}
```

暴力合并两个长度为 $2^i$ 的同向段：

```cpp
// 合并同向等长段
void merge1(int x,int y,int ith){
    if(find(x,f2[ith])==find(y,f2[ith]))return; // 剪枝
    if(ith==0)return merge(x,y),void(); // 直接合并
    f2[ith][find(x,f2[ith])]=find(y,f2[ith]); // 并查集合并
    merge1(x,y,ith-1);
    merge1(ST[x][ith-1],ST[y][ith-1],ith-1); // 暴力合并两个子段
}
```

暴力合并两个长度为 $2^i$ 的逆向段：

```cpp
// 合并逆向等长段
void merge2(int x,int y,int ith){
    if(find(x,f2[ith])==find(y+n,f2[ith]))return; // 剪枝
    if(ith==0)return merge(x,y),void();
    f2[ith][find(x+n,f2[ith])]=find(y,f2[ith]);// 并查集合并
    f2[ith][find(x,f2[ith])]=find(y+n,f2[ith]);
    merge2(x,ST[y][ith-1],ith-1); // 与合并同向等长段不同
    merge2(ST[x][ith-1],y,ith-1); // 暴力合并两个子段
}
```

### 总代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN=2e5+11,mod=1e9+7;

int ST[MAXN][18],depth[MAXN];

int h[MAXN],nt[MAXN<<1],to[MAXN<<1],linkcnt;

int L[MAXN],R[MAXN],n,ans=1;

int f1[MAXN],f2[18][MAXN<<1];

int ksm(int x,int y){
    int cur=1;
    for(;y;y>>=1,x=1ll*x*x%mod)if(y&1)cur=1ll*cur*x%mod;
    return cur;
}

// UNION_FIND_SETS
int find(int u,int *UNION_FIND_SETS){
    return UNION_FIND_SETS[u]==u?u:UNION_FIND_SETS[u]=find(UNION_FIND_SETS[u],UNION_FIND_SETS);
}

void link(int u,int v){
    nt[++linkcnt]=h[u],h[u]=linkcnt,to[linkcnt]=v;
}

void dfs_init(int u,int father){
    depth[u]=depth[father]+1;

    f1[u]=u;
    for(int i=0; i<=17; i++)
        f2[i][u]=u,f2[i][u+n]=u+n;

    ST[u][0]=father;
    for(int i=1; i<=17; i++)
        ST[u][i]=ST[ST[u][i-1]][i-1];

    for(int i=h[u]; i; i=nt[i]){
        if(to[i]==father)continue;
        dfs_init(to[i],u);
    }
}

int LCA(int u,int v){
    if(depth[u]<=depth[v])swap(u,v);
    for(int i=17; i>=0; i--)if(depth[ST[u][i]]>=depth[v])u=ST[u][i];
    if(u==v)return u;
    for(int i=17; i>=0; i--)if(ST[u][i]!=ST[v][i])u=ST[u][i],v=ST[v][i];
    return ST[u][0];
}

int kth_fa(int u,int dist){
    for(int i=0; i<=17; i++)
        if(((1<<i)&dist))u=ST[u][i];
    return u;
}

// 合并两个点
void merge(int x,int y){
    x=find(x,f1),y=find(y,f1);
    if(x==y)return;
    ans=1ll*ans*1ll*ksm(max(0ll,1ll*(R[x]-L[x]+1)),mod-2)%mod;
    ans=1ll*ans*1ll*ksm(max(0ll,1ll*(R[y]-L[y]+1)),mod-2)%mod;
    f1[x]=y;
    L[y]=max(L[x],L[y]);
    R[y]=min(R[x],R[y]);
    ans=1ll*ans*1ll*1ll*max(0ll,1ll*(R[y]-L[y]+1))%mod;
}

// 合并同向等长段
void merge1(int x,int y,int ith){
    if(find(x,f2[ith])==find(y,f2[ith]))return;
    if(ith==0)return merge(x,y),void();
    f2[ith][find(x,f2[ith])]=find(y,f2[ith]);
    merge1(x,y,ith-1);
    merge1(ST[x][ith-1],ST[y][ith-1],ith-1);
}

// 合并逆向等长段
void merge2(int x,int y,int ith){
    if(find(x,f2[ith])==find(y+n,f2[ith]))return;
    if(ith==0)return merge(x,y),void();
    f2[ith][find(x+n,f2[ith])]=find(y,f2[ith]);
    f2[ith][find(x,f2[ith])]=find(y+n,f2[ith]);
    merge2(x,ST[y][ith-1],ith-1);
    merge2(ST[x][ith-1],y,ith-1);
}

int main(){
    scanf("%d",&n);
    for(int i=2; i<=n; i++){
        static int f;
        scanf("%d",&f);
        link(f,i);
    }
    dfs_init(1,0);
    for(int i=1; i<=n; i++){
        scanf("%d %d",&L[i],&R[i]);
        ans=1ll*1ll*ans*max(0ll,1ll*(R[i]-L[i]+1))%mod;
    }
    int Q_sum;
    scanf("%d",&Q_sum);
    for(int Text=1; Text<=Q_sum; Text++){
        int a,b,c,d,lca_of_a_b,lca_of_c_d,T;
        scanf("%d %d %d %d",&a,&b,&c,&d);
        
        lca_of_a_b=LCA(a,b);
        lca_of_c_d=LCA(c,d);
        
        // 合并同向等长段
        T=min(depth[a]-depth[lca_of_a_b],depth[c]-depth[lca_of_c_d]);
        for(int i=17; i>=0; i--)if((T&(1<<i)))merge1(a,c,i),a=ST[a][i],c=ST[c][i];

        T=min(depth[b]-depth[lca_of_a_b],depth[d]-depth[lca_of_c_d]);
        for(int i=17; i>=0; i--)if((T&(1<<i)))merge1(b,d,i),b=ST[b][i],d=ST[d][i];

        // 合并逆向等长段
        if(a==lca_of_a_b){
            T=depth[b]-depth[lca_of_a_b]+1;
            for(int i=17; i>=0; i--){
                if((T&(1<<i))){
                    T^=(1<<i);
                    merge2(b,kth_fa(c,T),i);
                    b=ST[b][i];
                }
            }
        }
        else{
            T=depth[a]-depth[lca_of_a_b]+1;
            for(int i=17; i>=0; i--){
                if((T&(1<<i))){
                    T^=(1<<i);
                    merge2(a,kth_fa(d,T),i);
                    a=ST[a][i];
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
```


---

## 作者：yizhiming (赞：4)

算是补充另一篇树上并查集。

[Link](https://www.luogu.com.cn/problem/CF1801E)

## 题目大意

给定一棵 $n$ 个点的树，每个节点有一个权值区间 $[l_i,r_i]$ 表示这个点的取值范围，有 $q$ 次询问，每次给定 $a,b,c,d$，表示要求 $a\rightarrow b$ 的路径点的权值与 $c\rightarrow d$ 的权值对应相等，并求出满足条件的方案数，对 $10^9+7$ 取模，要注意询问之间不独立。

$1\leq n,q \leq 2\times 10^5,1\leq l_i \leq r_i < 10^9+7$。

## 题目分析

首先这个题是一个[序列问题](https://www.luogu.com.cn/problem/P3295)转换成的，建议先去做一下这道题。

这篇题解是补充，故不详细解释，将上面的序列问题转换成树上，原本的倍增形式由序列下标，变成了树上倍增祖先，所以问题就相当于将查询分成若干条链，对每部分进行并查集维护即可。

不难发现由于两条路径的长度需要一样，那么将两个点都尽可能地往上跳，对于这部分，我们需要将两段路径正序合并起来，处理完这一部分后，一定会有一个端点在路径顶端，所以对于其中一个路径往上倍增跳，这部分是倒序合并，所以要维护两个方向的并查集。

这道题还有一个不同就是每次修改都要输出方案，而上面那道题只需要输出一次，所以考虑每次修改的时候递归下去，若当前区间已经被合并了则退出，否则拆成两个小区间接着递归，直到单点的时候，求个逆元将原贡献去掉，再算上新贡献即可。

考虑一共只有 $n\log n$ 个不同的并查集，所以这部分复杂度正确。

## Code

这部分才是精华，我怎么调代码都会超时，改着改着就变成了另外一篇题解的样子，后来才发现那篇也会超时。。。

首先在并查集查询的时候不传当前层数，而传当前层数的对应数组的指针，虽然不知道为什么但是这样会变快。

因为有倍增，所以请将并查集和树上的倍增数组的较小的一维移到前面。

还有最为关键的一点，只路径压缩并查集的话，复杂度是 $O(n\log^2 n)$ 的，在阴间数据下会超时，所以要额外加上按秩合并，将复杂度优化成 $O(n\log n \alpha(n))$，其中 $\alpha(n)$ 是反阿克曼函数，原谅我不知道这玩意怎么打。

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
//#define int long long 
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N = 2e5+5;
int Mod = 1e9+7;
int f[20][N*2],fa[20][N],siz[20][N],K = 17,n,m;//f并查集，fa树上 
int head[N],tote,ans;
struct aa{
	int nxt,to;
}edge[N*2];
void link(int u,int v){
	edge[++tote].nxt = head[u];edge[tote].to = v;head[u] = tote;
}
int ksm(int x,int y){
	int res = 1;
	while(y){
		if(y&1){
			res = (1ll*res*x)%Mod;
		}
		x = (1ll*x*x)%Mod;
		y>>=1;
	}
	return res;
}
int dep[N],L[N],R[N];
void dfs(int u){
	for(int i=head[u];i;i=edge[i].nxt){
		int now = edge[i].to;
		fa[0][now] = u;
		dep[now] = dep[u]+1;
		dfs(now);
	}
}
int Lca(int x,int y){
	if(x==y){
		return x;
	}
	if(dep[x]<dep[y]){
		swap(x,y);
	}
	for(int i=K;i>=0;i--){
		if(dep[fa[i][x]]>=dep[y]){
			x = fa[i][x];
		}
	}
	if(x==y){
		return x;
	}
	for(int i=K;i>=0;i--){
		if(fa[i][x]!=fa[i][y]){
			x = fa[i][x];y = fa[i][y];
		}
	}
	return fa[0][x];
}
int find(int x,int *ff){
	if(ff[x]!=x){
		ff[x] = find(ff[x],ff);
	}
	return ff[x];
}
int getfa(int x,int k){
	for(int i=K;i>=0;i--){
		if((k>>i)&1){
			x = fa[i][x];
		}
	}
	return x;
}
void hb(int x,int y,int k){
	x = find(x,f[k]);y = find(y,f[k]);
	if(siz[k][x]>siz[k][y]){
		swap(x,y);
	}
	siz[k][y]+=(siz[k][x]==siz[k][y]);
	f[k][x] = y;
}
void mer(int x,int y){
	x = find(x,f[0]);y = find(y,f[0]);
	if(x==y){
		return;
	}
//	cout<<"XY:"<<L[x]<<" "<<R[x]<<" "<<L[y]<<" "<<R[y]<<" "<<ans<<" "<<x<<" "<<y<<"\n";
	ans = 1ll*ans*ksm(R[x]-L[x]+1,Mod-2)%Mod;
	ans = 1ll*ans*ksm(R[y]-L[y]+1,Mod-2)%Mod;
	if(siz[0][x]>siz[0][y]){
		swap(x,y);
	}
	f[0][x] = y;
	L[y] = max(L[y],L[x]);
	R[y] = min(R[y],R[x]);
	ans = 1ll*ans*max(0ll,1ll*(R[y]-L[y]+1))%Mod;
}
void merge1(int x,int y,int k){
	int u = find(x,f[k]),v = find(y,f[k]);
	if(u==v){
		return;
	}
	if(k==0){
		mer(x,y);
		return;
	}
	hb(x,y,k);
//	f[k][u] = v;
	merge1(x,y,k-1);
	merge1(fa[k-1][x],fa[k-1][y],k-1);
}
void merge2(int x,int y,int k){
	if(find(x,f[k])==find(y+n,f[k])){
		return;
	}
	if(k==0){
		mer(x,y);
		return;
	}
	hb(x,y+n,k);
	hb(x+n,y,k);
//	f[k][find(x,f[k])] = find(y+n,f[k]);
//	f[k][find(x+n,f[k])] = find(y,f[k]);
	merge2(x,fa[k-1][y],k-1);
	merge2(fa[k-1][x],y,k-1);
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n = read();
	for(int i=2;i<=n;i++){
		int x = read();
		link(x,i);
	}
	ans = 1;
	for(int i=1;i<=n;i++){
		L[i] = read();R[i] = read();
		ans = 1ll*ans*max(0ll,1ll*(R[i]-L[i]+1))%Mod;
	}
//	cout<<"ANS:"<<ans<<"\n";
	dep[1] = 1;
	dfs(1);
	for(int j=1;j<=K;j++){
		for(int i=1;i<=n;i++){
			fa[j][i] = fa[j-1][fa[j-1][i]];
		}
	}
	for(int i=0;i<=K;i++){
		for(int j=1;j<=n;j++){
			f[i][j] = j;
			f[i][j+n] = j+n;
			siz[i][j] = 1;
			siz[i][j+n] = 1;
		}
	}
	m = read();
	int a,b,c,d;
	while(m--){
		a = read();b = read();c = read();d = read();
		if(!ans){
			cout<<0<<"\n";
			continue;
		}
		int L1 = Lca(a,b),L2 = Lca(c,d); 
		int k = min(dep[a]-dep[L1],dep[c]-dep[L2]);
//		cout<<"LCA:"<<L1<<" "<<L2<<"\n";
//		cout<<"K1:"<<k<<"\n";
		for(int i=K;i>=0;i--){
			if((k>>i)&1){
				merge1(a,c,i);
				a = fa[i][a];
				c = fa[i][c]; 
			}
		}
		k = min(dep[b]-dep[L1],dep[d]-dep[L2]);
//		cout<<"K2:"<<k<<"\n"; 
		for(int i=K;i>=0;i--){
			if((k>>i)&1){
				merge1(b,d,i);
				b = fa[i][b];
				d = fa[i][d];
			}
		}
		if(a==L1){
			k = dep[b]-dep[L1]+1;
			for(int i=K;i>=0;i--){
				if((k>>i)&1){
					k^=(1<<i);
					merge2(b,getfa(c,k),i);
					b = fa[i][b];
				}
			}
		}else{
			k = dep[a]-dep[L1]+1;
			for(int i=K;i>=0;i--){
				if((k>>i)&1){
					k^=(1<<i);
					merge2(a,getfa(d,k),i);
					a = fa[i][a];
				}
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}



```

和那篇题解的作者聊了一下，认为是评测机波动卡掉了他的代码。

很久之前交了没过审，才想起来重交一遍。

---

## 作者：xieziheng (赞：2)

在鸽了一年后我终于写出来这道题。

容易发现每次操作就相当于把路径上对应点的区间取交，有合并性，所以就是合并对应点。

暴力就是写个并查集。

发现真正进行合并的总操作次数不超过 $n-1$。

所以考虑每次找到路径上第一个能合并的点，就是这个点前面所有对应的点都已经合并过了。考虑哈希每个点当前对应的父亲。定义长度为 $k$ 的序列 $a$ 的哈希值为 $\sum_{i=1}^{k} a_i p^{i-1}$ （因为这样比较好哈希）。那么每次只需要二分找到路径上第一个 $x,y$ 使得 $a$ 到 $x$ 的路径与 $c$ 到 $y$ 的哈希值不同即可。

每次会更改并查集中的父亲变化的点的哈希值，所以启发式合并。而根据哈希的定义，修改会改一整个子树，所以要写个 BIT。

由于只会合并 $\mathcal{O}(n)$ 次，二分套上倍增加启发式合并，所以总复杂度 $\mathcal{O}(n \log^2 n)$。

代码巨大难写，可以写个求 $k$ 级祖先，好写点，注意求路径哈希值要开两个 BIT 再分类讨论一下。

好像单模数 $10^9+7$ 也没被卡？

```cpp
#include <bits/stdc++.h>
#define il inline
using namespace std;
typedef long long ll;
const ll mod=1e9+7,mul=19260817;
il ll qp(ll a,ll b){
    ll ans=1ll;
    while(b){
        if(b&1) ans=(ans*a)%mod;
        a=(a*a)%mod,b>>=1;
    }
    return ans;
}
il ll inv(ll a){return qp(a,mod-2ll);}
il int read(){
    int x=0,c=getchar();
    while(!isdigit(c)) c=getchar();
    while(isdigit(c)) x=x*10+c-48,c=getchar();
    return x;
}
il void ad(ll &x,ll y){x=(x+y>=mod?x+y-mod:x+y);}
il void dl(ll &x,ll y){x=(x<y?x-y+mod:x-y);}
il ll ad1(ll x,ll y){return (x+y>=mod?x+y-mod:x+y);}
il ll dl1(ll x,ll y){return (x<y?x-y+mod:x-y);}
const int N=2e5+5;
int n,m,fa[N][20],de[N],dfn[N],cnt,id[N],s[N],lg[N],f[N],siz[N];ll l[N],r[N],ans;
ll h[N],pw[N],iv[N];
struct BIT{
    ll t[N],val[N];
    il BIT(){memset(t,0,sizeof(t));memset(val,0,sizeof(val));}
    il void add(int x,ll v){while(x<=n) ad(t[x],v),x+=(x&-x);}
    il ll get(int x){ll ret=0ull;while(x) ad(ret,t[x]),x-=(x&-x);return ret;}
    il void update(int x,ll v){add(dfn[x],dl1(v,val[x])),add(dfn[x]+s[x],dl1(val[x],v)),val[x]=v;}
    il ll calc(int x){return get(dfn[x]);}
}A,B;
vector<int> e[N],g[N];
int find(int x){return x==f[x]?x:f[x]=find(f[x]);}
il void Union(int x,int y){
    x=find(x),y=find(y);if(x==y) return ;
    if(siz[x]<siz[y]) swap(x,y);
    f[y]=x,siz[x]+=siz[y];
    ans=(ans*inv(r[x]-l[x]+1ll)%mod*inv(r[y]-l[y]+1ll))%mod;
    l[x]=max(l[x],l[y]),r[x]=min(r[x],r[y]);if(l[x]>r[x]) ans=0ll;else ans=(ans*(r[x]-l[x]+1ll))%mod;
    for(int u:g[y]) g[x].push_back(u),A.update(u,(1ll*x*pw[de[u]])%mod),B.update(u,(1ll*x*iv[de[u]])%mod);
}
void dfs(int x){
    de[x]=de[fa[x][0]]+1,dfn[x]=++cnt,id[cnt]=x,s[x]=1;
    for(int i=1;i<=18;++i) fa[x][i]=fa[fa[x][i-1]][i-1];
    for(int y:e[x]) dfs(y),s[x]+=s[y];
}
il int lca(int x,int y){
    if(de[x]<de[y]) swap(x,y);
    while(de[x]>de[y]) x=fa[x][lg[de[x]-de[y]]];
    if(x==y) return x;
    for(int i=18;i>=0;--i) if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
il int jump(int x,int k){//k-th ancestor of x
    for(int i=18;i>=0;--i) if(k>=(1<<i)) k-=(1<<i),x=fa[x][i];
    return x;
}
il int getk(int x,int y,int z,int k){//k-th point on path x-y
    int u=de[x]+de[y]-2*de[z]+1;
    if(z==x) return jump(y,u-k);
    if(k<=de[x]-de[z]+1) return jump(x,k-1);
    return jump(y,u-k);
}
il ll get(int x,int y,int z){
    if(x==z) return ((A.calc(y)-A.calc(fa[x][0])+mod)*iv[de[x]])%mod;
    int w=de[x]-2*de[z];ll u=((B.calc(x)-B.calc(z)+mod)*pw[de[x]])%mod,v=((A.calc(y)-A.calc(fa[z][0])+mod)*(w>=0?pw[w]:iv[-w]))%mod;
    return ad1(u,v);
}
il int ck(int a,int b,int x,int c,int d,int y,int k){
    int u=getk(a,b,x,k),v=getk(c,d,y,k),p=0,q=0;
    if(k<=de[a]-de[x]+1) p=u;else p=x;
    if(k<=de[c]-de[y]+1) q=v;else q=y;
    return get(a,u,p)==get(c,v,q);
}
il void init(){
    pw[0]=iv[0]=1ull;ll x=qp(mul,mod-2ll);
    for(int i=1;i<=n;++i) pw[i]=(pw[i-1]*mul)%mod,iv[i]=(iv[i-1]*x)%mod;
    for(int i=2;i<=n;++i) lg[i]=lg[i>>1]+1;
}
int a,b,c,d,len,x,y,z,u,v,w,L,R,mid,ret;
int main(){
    scanf("%d",&n);ans=1ll,init();
    for(int i=2;i<=n;++i) fa[i][0]=read(),e[fa[i][0]].push_back(i);
    for(int i=1;i<=n;++i) l[i]=read(),r[i]=read(),f[i]=i,siz[i]=1,g[i].push_back(i),ans=(ans*(r[i]-l[i]+1ll))%mod;
    dfs(1);
    for(int i=1;i<=n;++i) A.update(i,(1ll*i*pw[de[i]])%mod),B.update(i,(1ll*i*iv[de[i]])%mod);
    scanf("%d",&m);
    while(m--){
        a=read(),b=read(),c=read(),d=read();
        if(!ans){puts("0");continue;}
        x=lca(a,b),y=lca(c,d),len=de[a]+de[b]-2*de[x]+1;
        while(get(a,b,x)!=get(c,d,y)){
            L=1,R=len,ret=0;
            while(L<=R){
                mid=(L+R)>>1;
                if(!ck(a,b,x,c,d,y,mid)) ret=mid,R=mid-1;
                else L=mid+1;
            }
            u=getk(a,b,x,ret),v=getk(c,d,y,ret);
            Union(u,v);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：Leasier (赞：2)

首先有一个巨 tm 恶心的树剖后线段树维护正反区间哈希再加上启发式合并的做法，赛时一眼看了出来但是这咋写啊……

考虑把 dfs 序 reverse 一下拼在后面，则我们现在只需要维护两个区间的对应项在区间中的合并。

人类智慧地，考虑将区间 $[l, r]$ 类似 ST 表地拆成两个长为 $2^t$ 的区间，现在我们只需要维护长为 $2$ 的幂的区间合并。

考虑分治下去。对于 $[x, x + 2^t - 1], [y, y + 2^t - 1]$ 的合并，当 $t = 0$，我们在最底层并查集上进行操作即可；否则在 $t$ 这层并查集上进行合并，若成功地进行一次合并操作则将其下传到 $(x, y, t - 1), (x + 2^{t - 1}, y + 2^{t - 1}, t - 1)$ 继续合并即可。

时间复杂度为 $O((n + m) \log^2 n)$。

代码：
```cpp
#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>

using namespace std;

typedef long long ll;

typedef struct {
	int nxt;
	int end;
} Edge;

const int mod = 1e9 + 7;
int cnt = 0;
ll ans = 1;
int root[27][400007], fa[200007], head[200007], depth[200007], size[200007], hs[200007], dfn[200007], top[200007], l[200007], r[200007], L[400007], R[400007];
Edge edge[200007];

inline void init(int n){
	int m = log2(n);
	for (register int i = 0; i <= m; i++){
		for (register int j = 1; j <= n; j++){
			root[i][j] = j;
		}
	}
}

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

void dfs1(int u){
	depth[u] = depth[fa[u]] + 1;
	size[u] = 1;
	for (register int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		dfs1(x);
		size[u] += size[x];
		if (hs[u] == 0 || size[hs[u]] < size[x]) hs[u] = x;
	}
}

void dfs2(int u, int cur_top, int &id){
	dfn[u] = ++id;
	top[u] = cur_top;
	if (hs[u] != 0){
		dfs2(hs[u], cur_top, id);
		for (register int i = head[u]; i != 0; i = edge[i].nxt){
			int x = edge[i].end;
			if (x != hs[u]) dfs2(x, x, id);
		}
	}
}

inline ll sqr(int n){
	return (ll)n * n % mod;
}

int get_root(int x, int y){
	if (root[x][y] == y) return y;
	return root[x][y] = get_root(x, root[x][y]);
}

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

inline void merge1(int k, int x, int y){
	int x_root = get_root(k, x), y_root = get_root(k, y);
	if (x_root != y_root){
		root[k][x_root] = y_root;
		if (k == 0){
			ans = ans * quick_pow((ll)max(R[x_root] - L[x_root] + 1, 0) * max(R[y_root] - L[y_root] + 1, 0) % mod, mod - 2, mod) % mod;
			L[y_root] = max(L[y_root], L[x_root]);
			R[y_root] = min(R[y_root], R[x_root]);
			ans = ans * max(R[y_root] - L[y_root] + 1, 0) % mod;
		} else {
			k--;
			merge1(k, x, y);
			merge1(k, x + (1 << k), y + (1 << k));
		}
	}
}

inline vector<pair<int, int> > get_segment(int u, int v, int n){
	int op = 0, size;
	vector<pair<int, int> > ans, vec[7];
	while (top[u] != top[v]){
		if (depth[top[u]] < depth[top[v]]){
			swap(u, v);
			op ^= 1;
		}
		vec[op].push_back(make_pair(dfn[top[u]], dfn[u]));
		u = fa[top[u]];
	}
	if (depth[u] < depth[v]){
		swap(u, v);
		op ^= 1;
	}
	vec[op].push_back(make_pair(dfn[v], dfn[u]));
	size = vec[0].size();
	for (register int i = 0; i < size; i++){
		ans.push_back(make_pair(n - vec[0][i].second + 1, n - vec[0][i].first + 1));
	}
	for (register int i = (int)vec[1].size() - 1; i >= 0; i--){
		ans.push_back(vec[1][i]);
	}
	return ans;
}

inline void merge2(int l1, int l2, int k){
	int t = log2(k);
	merge1(t, l1, l2);
	merge1(t, l1 + k - (1 << t), l2 + k - (1 << t));
}

int main(){
	int n = read(), k = n * 2, id = 0, m;
	init(k);
	for (register int i = 2; i <= n; i++){
		fa[i] = read();
		add_edge(fa[i], i);
	}
	dfs1(1);
	dfs2(1, 1, id);
	for (register int i = 1; i <= n; i++){
		l[i] = read();
		r[i] = read();
		ans = ans * sqr(r[i] - l[i] + 1) % mod;
	}
	for (register int i = 1; i <= n; i++){
		int t = k - dfn[i] + 1;
		L[dfn[i]] = L[t] = l[i];
		R[dfn[i]] = R[t] = r[i];
		merge1(0, dfn[i], t);
	}
	m = read();
	for (register int i = 1; i <= m; i++){
		int a = read(), b = read(), c = read(), d = read();
		vector<pair<int, int> > v1 = get_segment(a, b, k), v2 = get_segment(c, d, k);
		while (!v1.empty() && !v2.empty()){
			int len1, len2, len3;
			pair<int, int> &pr1 = v1.back(), &pr2 = v2.back();
			len1 = pr1.second - pr1.first + 1;
			len2 = pr2.second - pr2.first + 1;
			len3 = min(len1, len2);
			merge2(pr1.second - len3 + 1, pr2.second - len3 + 1, len3);
			if (len1 == len3){
				v1.pop_back();
			} else {
				pr1.second -= len3;
			}
			if (len2 == len3){
				v2.pop_back();
			} else {
				pr2.second -= len3;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：zesqwq (赞：1)

~~cf 最优解，嘿嘿~~

~~不是为什么我 $\text{base}=251$ 没被叉~~

本做法为经典的树链剖分 $+$ 哈希，但是是一种比题解区现有题解常数更小的解法。

---

首先我们把这个问题变成序列上的问题。

我们把原序列 $\text{reverse}$ 一下接到原序列的末尾。

我们发现如果把 $1$ 当作根，那么两点间的路径就是从下至上的一条路径和从上至下的一条路径，我们可以先树剖，从下至上的 $O(\log n)$ 段 $\text{dfs}$ 序递减不好维护，我们把他对应为 $\text{reverse}$ 后的一段，从上到下的 $O(\log n)$ 段 $\text{dfs}$ 序递增，自然可以形成 $O(\log n)$ 个区间。

最后就变成了区间上的问题，参考代码如下：

```cpp
inline int ano(int x) { return (n << 1) - x + 1; }
inline vector<pair<int, int>> geta(int u, int g) { //从下至上的路径拆分
    vector<pair<int, int>> ans;
    while (top[u] != top[g])
        ans.push_back({ano(dfn[u]), ano(dfn[top[u]])}), u = fat[top[u]];
    return ans.push_back({ano(dfn[u]), ano(dfn[g])}), ans;
}
inline vector<pair<int, int>> getb(int u, int g) { //从上至下的路径拆分
    vector<pair<int, int>> ans2;
    while (top[u] != top[g])
        ans2.push_back({dfn[top[u]], dfn[u]}), u = fat[top[u]];
    if (u != g) ans2.push_back({dfn[g] + 1, dfn[u]});
    reverse(ans2.begin(), ans2.end());
    return ans2;
}
```
---

接着考虑序列上的问题，~~然而赛时 cmk 告诉了我假题面，坏~~，我们发现总的有效合并次数是 $O(n)$ 次的，于是我们要快速定位到这 $O(n)$ 次合并。

具体来讲，我们使用哈希的方式，我们将 $\text{hash}_{l,r}= \sum_{x=l}^rf(\text{id}_x)\times \text{base}^x$，$\text{id}$ 表示 $x$ 所在集合编号，$f$ 是随机映射函数，这个东西是好用树状数组 $+$ 启发式合并来维护的。

假如我们要合并 $[l_1,r_1]$ 与 $[l_2,r_2]$ 且他们的哈希不同，那么我们：

1. $l_1 = r_1$ 时合并 $l_1,l_2$ 即可;
2. 否则令 $mid_1 = \lfloor\dfrac{l_1+r_1}2\rfloor,mid_2 = \lfloor\dfrac{l_2+r_2}2\rfloor$ 递归判定 $[l_1, mid_1] \& [l_2,mid_2]$ 与 $(mid_1,r_1] \& (mid_2,r_2]$ 即可。

时间复杂度 $O(n\log^2n)$，但是瓶颈处的 $\log$ 来自于 $\text{dsu}$，树链剖分和树状数组，跑得飞快。

---

## 作者：larsr (赞：0)

暴力用并查集维护复杂度很大。考虑如果 $a$ 和 $b$ 之间没有祖先关系，可以把 $a\to b$ 拆成 $a\to lca$ 和 $lca\to b$，再利用倍增拆成 $O(\log n)$ 条路径。$c\to d$ 同理。

对分出来的路径分成两类：向上和向下。

路径用并查集维护关系。考虑合并两个长度为 $2^k$ 的路径：

- 若在同一个集合，则无需操作。
- 否则，先在并查集合并这两条路径，把长为 $2^k$ 的路径分成两个长为 $2^{k-1}$ 的路径递归合并，如果 $k=0$，直接合并两个点即可。

总共有 $O(n\log n)$ 条路径，所以最多合并 $O(n\log n)$ 次，所以复杂度 $O(n\log n\alpha(n\log n))$。

[sub](https://codeforces.com/contest/1801/submission/303883306)

---

## 作者：happybob (赞：0)

首先，考虑使用并查集维护相等的点集合，答案是每个森林的最小 $r$ 减去最大 $l$ 加 $1$ 的乘积。注意判断答案是否为 $0$。

容易发现并查集的真正合并次数至多为 $n-1$。现在问题是如何快速定位这些操作。

考虑在并查集合并的时候启发式合并，这样每次合并时可以快速更新每个点所在森林的根而不是使用路径压缩，然后维护树上有序路径哈希，每次限制二分找到第一个并查集上根不同的一对点，然后合并，重复此操作即可。复杂度 $O(n \log^2 n)$。

[Submission Link.](https://codeforces.com/contest/1801/submission/261513180)

---

## 作者：gdf_yhm (赞：0)

[CF1801E](https://www.luogu.com.cn/problem/CF1801E)

### 思路

并查集将权值相同的连在一起，取可行区间的并集。可以 $O(n^2)$。考虑优化，总共只有 $n-1$ 次有效合并，只要没有重复检查已经连通的点就可以保证复杂度。

倍增 $u$ 向上 $2^i$ 个祖先的状态，代表从下往上和从上往下的区间。将两条路径倍增合并，$O(\log n)$ 次合并等长区间。每次合并时向下一层递归合并，如果已经是一个连通块的及时退出。一直到单点合并时，去掉旧贡献加上新贡献。复杂度 $O(n\log n)$。

卡常方面，将倍增的 $\log n$ 一维放在 $n$ 一维前面，路径压缩加按秩合并，不开 ```long long```。实在过不了再交几次。

### code

```cpp
int n,q,ans=1;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int l[maxn],r[maxn];
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=1ll*ans*a%mod;
		a=1ll*a*a%mod;
		b>>=1;
	}
	return ans;
}
int fa[18][maxn],dep[maxn];
int f[18][maxn<<1],siz[18][maxn<<1];
int fd(int x,int k){
	if(x==f[k][x])return x;
	return f[k][x]=fd(f[k][x],k);
}
void merge(int x,int y,int id){
	// if(!id)cout<<x<<" "<<y<<"\n";
	x=fd(x,id),y=fd(y,id);
	if(x==y)return ;
	if(siz[id][x]<siz[id][y])swap(x,y);
	if(!id){
		ans=1ll*ans*ksm(max(0,r[x]-l[x]+1))%mod;
		ans=1ll*ans*ksm(max(0,r[y]-l[y]+1))%mod;
		l[x]=max(l[x],l[y]),r[x]=min(r[x],r[y]);
		ans=1ll*ans*max(0,r[x]-l[x]+1)%mod;
		// cout<<x<<" "<<y<<" "<<ans<<"\n";
	}
	f[id][y]=x,siz[id][x]+=siz[id][y];
}
void dfs(int u){
	dep[u]=dep[fa[0][u]]+1;
	for(int i=1;i<=17;i++)fa[i][u]=fa[i-1][fa[i-1][u]];
	for(int i=0;i<=17;i++)f[i][u]=u,siz[i][u]=1,f[i][u+n]=u+n,siz[i][u+n]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		fa[0][v]=u;dfs(v);
	}
}
int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	for(int i=17;~i;i--)if(dep[fa[i][u]]>=dep[v])u=fa[i][u];
	if(u==v)return u;
	for(int i=17;~i;i--)if(fa[i][u]!=fa[i][v])u=fa[i][u],v=fa[i][v];
	return fa[0][u];
}
int kth(int u,int k){
	for(int i=17;~i;i--)if(k&(1<<i))u=fa[i][u];
	return u;
}
void mer1(int u,int v,int id){
	if(fd(u,id)==fd(v,id))return ;
	if(!id){
		merge(u,v,id);
		return ;
	}
	merge(u,v,id);
	mer1(u,v,id-1),mer1(fa[id-1][u],fa[id-1][v],id-1);
}
void mer2(int u,int v,int id){
	if(fd(u,id)==fd(v+n,id))return ;
	if(!id){
		merge(u,v,id);
		return ;
	}
	merge(u+n,v,id),merge(u,v+n,id);
	mer2(u,fa[id-1][v],id-1),mer2(fa[id-1][u],v,id-1);
}
void work(){
	n=read();
	for(int i=2;i<=n;i++){
		int u=read();
		add(u,i);
	}
	dfs(1);
	for(int i=1;i<=n;i++){
		l[i]=read(),r[i]=read();
		ans=1ll*ans*max(0,r[i]-l[i]+1)%mod;
	}
	q=read();
	while(q--){
		int a=read(),b=read(),c=read(),d=read(),tp1=lca(a,b),tp2=lca(c,d);
		int dis=min(dep[a]-dep[tp1],dep[c]-dep[tp2]);
		for(int i=17;~i;i--)if(dis&(1<<i))mer1(a,c,i),a=fa[i][a],c=fa[i][c];
		dis=min(dep[b]-dep[tp1],dep[d]-dep[tp2]);
		for(int i=17;~i;i--)if(dis&(1<<i))mer1(b,d,i),b=fa[i][b],d=fa[i][d];
		// cout<<tp1<<" "<<tp2<<" "<<ans<<"\n";
		if(a==tp1){
			dis=dep[b]-dep[tp1]+1;
			for(int i=17;~i;i--)if(dis&(1<<i))dis^=(1<<i),mer2(b,kth(c,dis),i),b=fa[i][b];
		}
		else{
			dis=dep[a]-dep[tp1]+1;
			for(int i=17;~i;i--)if(dis&(1<<i))dis^=(1<<i),mer2(a,kth(d,dis),i),a=fa[i][a];
		}
		printf("%d\n",ans);
	}
}
```

---

## 作者：SunsetSamsara (赞：0)

## CF1801E

### 题意

给定一个 $n$ 个节点的树, 每个点上有一个数, 取值范围为 $[l_i,r_i]$。

$q$ 次询问, 每次会新增一个限制, 每次给出四个整数 $a,b,c,d$, 保证 $a→b$ 和 $c→d$ 的长度相同, 对于每个 $i$ 要求两条路径上的第 $i$ 个点的取值相同。

每次询问后输出写数字的方案数, 对 $10^9+7$ 取模.

### 标签

树，并查集，倍增

### 做法

首先有序列版本 [【SCOI2016】萌萌哒](https://www.luogu.com.cn/problem/P3295)。

这个树上版本就是序列版本的做法将倍增长度变为倍增祖先，不过要分类讨论方向相同的路径与方向相反的路径。

发现如果两段序列 $a, b$ 相等，两端序列 $b, c$ 也相等，那么 $a, c$ 显然也相等。于是考虑使用并查集。

于是问题就变成了如何合并两个长度为 $2^i$ 的序列。

如果两个序列长度都为 $1$，那么将答案除以原来这两个点的方案数 $(R_x - L_x + 1) \times (R_y - L_y + 1)$，再乘上新的方案数 $\min\{R_x,R_y\} - \max\{L_x,L_y\} + 1$。因为要保留修改，再将 $L_x$ 和 $L_y$ 设置为 $\max\{L_x, L_y\}$。

对于长度不为 $1$ 的路径，就将两段路径暴力拆成各自的两个子路径再在并查集上合并。

对于方向相同的路径与方向相反的路径要分开考虑。

### 代码

```cpp
#pragma GCC optimize("O2")
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <map>
#include <set>
typedef long long lld;
using namespace std;
const int N = 200010;
const int mod = 1e9 + 7;
int n;
int L[N], R[N];
int ans;
int STfa[N][19], dep[N];
vector<int> G[N];
int f1[N], f2[19][N << 1];
inline int qpow(int a, int b, int mod) {
	int ret = 1;
	for (; b; b >>= 1, a = 1ll * a * a % mod)
		if (b & 1) ret = 1ll * ret * a % mod;
	return ret;
}
inline int find(int u, int *fa) {
	return (fa[u] == u) ? u : (fa[u] = find(fa[u], fa));
}
inline void dfs(int u, int fa) {
	dep[u] = dep[fa] + 1;
	f1[u] = u;
	for (int i = 0; i <= 18; ++ i) f2[i][u] = u, f2[i][u + n] = u + n;
	STfa[u][0] = fa;
	for (int i = 1; i <= 18; ++ i) STfa[u][i] = STfa[STfa[u][i - 1]][i - 1];
	for (int v : G[u]) dfs(v, u);
}
inline int LCA(int u, int v) {
	if (dep[u] <= dep[v]) swap(u, v);
	for (int i = 18; ~i; -- i) if (dep[STfa[u][i]] >= dep[v]) u = STfa[u][i];
	if (u == v) return u;
	for (int i = 18; ~i; -- i) if (STfa[u][i] != STfa[v][i]) u = STfa[u][i], v = STfa[v][i];
	return STfa[u][0];
}
inline int jmp(int u, int dist) {
	for (int i = 0; i <= 18; ++ i)
		if (((1 << i) & dist))
			u = STfa[u][i];
	return u;
}
inline void merge(int x, int y) {
	x = find(x, f1), y = find(y, f1);
	if (x == y) return;
	ans = 1ll * ans * qpow(max(0, R[x] - L[x] + 1), mod - 2, mod) % mod;
	ans = 1ll * ans * qpow(max(0, R[y] - L[y] + 1), mod - 2, mod) % mod;
	f1[x] = y;
	L[y] = max(L[x], L[y]);
	R[y] = min(R[x], R[y]);
	ans = 1ll * ans * max(0, R[y] - L[y] + 1) % mod;
}
inline void merge1(int x, int y, int d) {
	if (find(x, f2[d]) == find(y, f2[d])) return;
	if (!d) {
		merge(x, y);
		return;
	}
	f2[d][find(x, f2[d])] = find(y, f2[d]);
	merge1(x, y, d - 1);
	merge1(STfa[x][d - 1], STfa[y][d - 1], d - 1);
}
inline void merge2(int x, int y, int d) {
	if (find(x, f2[d]) == find(y + n, f2[d])) return;
	if (!d) {
		merge(x, y);
		return;
	}
	f2[d][find(x + n, f2[d])] = find(y, f2[d]);
	f2[d][find(x, f2[d])] = find(y + n, f2[d]);
	merge2(x, STfa[y][d - 1], d - 1);
	merge2(STfa[x][d - 1], y, d - 1);
}
int main() {
	int q;
	scanf("%d", &n);
	for (int i = 2, f; i <= n; ++ i) {
		scanf("%d", &f);
		G[f].push_back(i);
	}
	dfs(1, 0);
	ans = 1;
	for (int i = 1; i <= n; ++ i) {
		scanf("%d%d", L + i, R + i);
		ans = 1ll * ans * max(0ll, 1ll * (R[i] - L[i] + 1)) % mod;
	}
	scanf("%d", &q);
	int a, b, c, d, l1, l2, T;
	for (; q --; ) {
		scanf("%d%d%d%d", &a, &b, &c, &d);
		l1 = LCA(a, b), l2 = LCA(c, d);
		T = min(dep[a] - dep[l1], dep[c] - dep[l2]);
		for (int i = 18; ~i; -- i) if ((T & (1 << i))) merge1(a, c, i), a = STfa[a][i], c = STfa[c][i];
		T = min(dep[b] - dep[l1], dep[d] - dep[l2]);
		for (int i = 18; ~i; -- i) if ((T & (1 << i))) merge1(b, d, i), b = STfa[b][i], d = STfa[d][i];
		if (a == l1) {
			T = dep[b] - dep[l1] + 1;
			for (int i = 18; ~i; -- i)
				if ((T & (1 << i))) {
					T ^= (1 << i);
					merge2(b, jmp(c, T), i);
					b = STfa[b][i];
				}
		} else {
			T = dep[a] - dep[l1] + 1;
			for (int i = 18; ~i; -- i)
				if ((T & (1 << i))) {
					T ^= (1 << i);
					merge2(a, jmp(d, T), i);
					a = STfa[a][i];
				}
		}
		printf("%d\n", ans);
	}
}

```

---

