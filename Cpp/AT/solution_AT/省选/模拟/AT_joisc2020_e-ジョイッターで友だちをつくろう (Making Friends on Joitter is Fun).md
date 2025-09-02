# ジョイッターで友だちをつくろう (Making Friends on Joitter is Fun)

## 题目描述

Joitter 是一款社交软件，已经有 $n$ 个人正在使用，都没有互相关注。从现在起的 $m$ 天内，每天会有用户 ${A_i}$ 关注用户 $B_i$ 的事件。官方准备在这 $m$ 天中举办一个活动，此活动的内容是：如果存在 3 个用户 $x$ , $y$ , $z$ 其中 $x$ 关注了 $y$ 但没有关注 $z$ ，同时 $y$ 与 $z$ 互相关注，那么让用户 $x$ 关注用户 $z$ ，重复进行直到不再存在这样的用户。

------------
官方还没有开始举行这个活动，官方想知道 $\forall i \in [1,m] $ 若活动在第 $i$ 天开始，活动结束后每个用户关注其他用户数量和的最大值是多少。

------------

## 说明/提示

【数据约定】
对于所有数据， $1\le n \le 10^5$ , $1 \le m \le 3*10^5 $ ，保证 :

- $ 1 \le A_i , B_i \le n (1 \le i \le m) $;
- $ A_i \neq B_i (1 \le i \le m) $;
- $ (A_i , B_i) \neq ( A_j , B_j) (1 \le i \le m) $。

# 题解

## 作者：DaiRuiChen007 (赞：0)

# JOISC2020E 题解

[Problem Link](https://qoj.ac/problem/3556)

**题目大意**

> 给 $n$ 个点，$m$ 次操作加入一条有向边，然后按如下规则不断更新整个图：若 $x\to u,u\leftrightarrow v$ 则连接 $x\to v$。
>
> 数据范围：$n\le 10^5,m\le 3\times 10^5$。

**思路分析**

容易发现双向连边关系具有传递性，因此每个点连向的一定是一个完整的双向边构成的连通块。

因此我们只要维护所有双向连边关系构成的连通块即可，对每个连通块维护入点和出点的集合，每次相当于合并两个集合。

使用启发式合并 $x,y$，每次暴力更改大小小的一侧集合 $y$，把所有端点指向 $x$ 即可。

时间复杂度 $\mathcal O(m\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1e5+5;
unordered_set <int> in[MAXN],out[MAXN];
//in:all node link u, out: every dsu linked
int n,m,siz[MAXN],dsu[MAXN];
ll ans=0;
inline int find(int x) { return dsu[x]^x?(dsu[x]=find(dsu[x])):x; }
inline void link(int u,int v) {
	u=find(u),v=find(v); if(u==v) return ;
	if(in[u].size()+out[u].size()<in[v].size()+out[v].size()) swap(u,v);
	ans-=1ll*siz[u]*in[u].size()+1ll*siz[v]*in[v].size();
	vector <int> nxt;
	for(int x:out[v]) if(out[x].count(u)) nxt.push_back(x);
	for(int x:in[v]) {
		x=find(x);
		if(out[u].count(x)) nxt.push_back(x);
		out[x].erase(v),out[x].insert(u);
	} 
	dsu[v]=u,siz[u]+=siz[v];
	for(int x:in[v]) in[u].insert(x);
	for(int x:out[v]) out[u].insert(x);
	ans+=1ll*siz[u]*in[u].size();
	for(int x:nxt) link(u,x);
}
signed main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) siz[i]=1,dsu[i]=i,in[i].insert(i);
	for(int i=1,u,v;i<=m;++i) {
		scanf("%d%d",&u,&v);
		int x=find(u),y=find(v);
		if(x!=y) {
			if(!out[y].count(x)) {
				if(!in[y].count(u)) ans+=siz[y],in[y].insert(u),out[x].insert(y);
			} else link(u,v);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```



---

## 作者：Hellsing_Alucard (赞：0)


比较显然的结论:

$a\Longleftrightarrow b,b\Longleftrightarrow c$，则 $a\Longleftrightarrow c$。

看一眼数据范围，肯定不能每条边都一一加上，肯定会超时。

观察，每个连通块的贡献都为 $size[x]\times(size[x]-1)$。

想到只维护连通块之间的边。

手动模拟加边情况：

加入边 $[u,v]$，如果这条边在同一个联通图，跳过。

如果 $u$ 有一条连向 $v$ 所在连通图的边，那么 $u$ 一定已经连向了 $v$ 本身，跳过。

再判断有无一条边可以从 $v$ 所在的连通图连向 $u$ 所在的连通图。

如果 $v$ 所在的连通图不能够连向 $u$ 所在的连通图，就直接记录这条边，然后答案加上 $v$ 连通块的大小。

如果能够连向，那么这两个连通块都可以合并成一个。

那么把答案中的两个连通块去掉，合并之后再加上。

把 $v$ 所在的连通图合并在 $u$ 所在的联通图上。

$v$ 连通图伸出和射入的边去掉，然后全连在 $u$ 的图上，bfs 循环加边，最后再统计答案。


```cpp

inline int clac(int u){
    return siz[u]*(siz[u]-1)+in[u].size()*siz[u];
}
inline void merge(int xx,int yy){
    queue<pii>q;
    q.push({xx,yy});
    while(q.size()){
        pii u=q.front();q.pop();
        int x=u.first,y=u.second;
        int fux=find(x),fuy=find(y);
        if(fux==fuy||in[fuy].count(x))continue;
        auto it=out[fuy].lower_bound({fux,0});
        if(it==out[fuy].end()||it->first!=fux){
            in[fuy].insert(x);
            out[fux].insert({fuy,x});
            ans+=siz[fuy];
            continue;
        }
        ans-=clac(fux)+clac(fuy);
        for(auto t:out[fuy]){
            int tx=t.first,ty=t.second;
            in[tx].erase(ty);
            if(tx==fux)continue;
            q.push({ty,tx});
            ans-=siz[tx];
        }
        for(auto t:in[fuy]){
            int ft=find(t);
            out[ft].erase({fuy,t});
            if(ft!=fux)q.push({t,fux});
        }
        fa[fuy]=fux;siz[fux]+=siz[fuy];
        ans+=clac(fux);
        in[fuy].clear();
        out[fuy].clear();
    }
}
```

然而，会超时。

考虑优化，想到启发式合并。

```cpp
	if(in[fux].size()+out[fux].size()<in[fuy].size()+out[fuy].size()){
            swap(fux,fuy);
            swap(x,y);
        }
```
时间复杂度变为 $O(n\log^2n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define ull unsigned long long
#define i128 __int128
#define ldo long double
#define dle double
#define up(a,b,c) for(int a=b;a<=c;a++)
#define dn(a,b,c) for(int a=b;a>=c;a--)
#define pii pair<int,int>
#define lc k<<1
#define rc k<<1|1

const int N=1e6+7;
const int mod=59027;

namespace IO{
    inline int read(){
        char c=getchar();int x=0,fh=0;
        while(c<'0'||c>'9'){fh|=c=='-';c=getchar();}
        while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
        return fh?-x:x;
    }
    inline void wt(int x){
        if(x<0){x=-x;putchar('-');}
        if(x>9)wt(x/10);
        putchar((x%10)^48);
    }
    inline void write(int x,bool op){
        wt(x);
        putchar(op?'\n':' ');
    }
}using namespace IO;
int fa[N];
inline int find(int x){
    if(x==fa[x])return x;
    return fa[x]=find(fa[x]);
}
set<int>in[N];
set<pii>out[N];
int n,m,siz[N];
int ans;
inline int clac(int u){
    return siz[u]*(siz[u]-1)+in[u].size()*siz[u];
}
inline void merge(int xx,int yy){
    queue<pii>q;
    q.push({xx,yy});
    while(q.size()){
        pii u=q.front();q.pop();
        int x=u.first,y=u.second;
        int fux=find(x),fuy=find(y);
        if(fux==fuy||in[fuy].count(x))continue;
        auto it=out[fuy].lower_bound({fux,0});
        if(it==out[fuy].end()||it->first!=fux){
            in[fuy].insert(x);
            out[fux].insert({fuy,x});
            ans+=siz[fuy];
            continue;
        }
        if(in[fux].size()+out[fux].size()<in[fuy].size()+out[fuy].size()){
            swap(fux,fuy);
            swap(x,y);
        }
        ans-=clac(fux)+clac(fuy);
        for(auto t:out[fuy]){
            int tx=t.first,ty=t.second;
            in[tx].erase(ty);
            if(tx==fux)continue;
            q.push({ty,tx});
            ans-=siz[tx];
        }
        for(auto t:in[fuy]){
            int ft=find(t);
            out[ft].erase({fuy,t});
            if(ft!=fux)q.push({t,fux});
        }
        fa[fuy]=fux;siz[fux]+=siz[fuy];
        ans+=clac(fux);
        in[fuy].clear();
        out[fuy].clear();
    }
}
signed main(){
    int u,v;
    n=read();m=read();
    up(i,1,n)fa[i]=i,siz[i]=1;
    up(i,1,m){
        u=read();v=read();
        merge(u,v);
        write(ans,1);
    }
    return 0;
}

```









---

