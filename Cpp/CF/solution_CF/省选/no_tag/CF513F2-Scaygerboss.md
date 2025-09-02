# Scaygerboss

## 题目描述

Cthulhu decided to catch Scaygerboss. Scaygerboss found it out and is trying to hide in a pack of his scaygers. Each scayger except Scaygerboss is either a male or a female. Scaygerboss's gender is "other".

Scaygers are scattered on a two-dimensional map divided into cells. A scayger looks nerdy and loveable if it is staying in the same cell with exactly one scayger of a gender that is different from its own gender. Cthulhu will not be able to catch Scaygerboss if all the scaygers on the map look nerdy and loveable.

The scaygers can move around at different speeds. For each scayger, we are given the time it takes this scayger to move from a cell to an adjacent cell. Cells are adjacent if they share a common side. At any point of time, each cell that does not contain an obstacle can be occupied by an arbitrary number of scaygers. Scaygers cannot move to cells with obstacles.

Calculate minimal time in order to make all scaygers look nerdy and loveable if they move optimally toward this goal.

## 说明/提示

Consider the first sample test. The scaygers are hiding on a 4 by 4 map. Scaygerboss initially resides in the cell $ (2,1) $ and can move between cells in 1 unit of time. There are also 2 male and 3 female scaygers on the map. One of the females initially is in the cell $ (1,1) $ , and all the other scaygers are in the cell $ (2,1) $ . All the scaygers move between cells in 2 units of time. If Scaygerboss and the female scayger from the cell $ (1,1) $ move to the cell $ (1,2) $ , and a male and a female scayger from those residing in the cell $ (2,1) $ move to the cell $ (1,1) $ , then all the scaygers will look nerdy and lovable in 2 units of time.

## 样例 #1

### 输入

```
4 4 2 3
....
.###
####
####
2 1 1
2 1 2
2 1 2
2 1 2
2 1 2
1 1 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 4 2 2
....
.###
2 1 1
2 1 2
2 1 2
2 1 2
2 1 2
```

### 输出

```
-1
```

# 题解

## 作者：CQ_Bob (赞：4)

简单题，考虑二分答案。

很显然，额外的那个神奇的棋子最终的颜色是唯一的，因为要使它们两两配对，只能是 $a=b$。即神奇的棋子最终的颜色是 $a,b$ 中较小的一个。

对于无解的情况，要么 $a \ne b$，要么不存在答案。

令 $M$ 为当前二分的答案。我们将所有红点与源点连边，将所有蓝点与汇点连边。建立 $n \times m$ 给点，表示格子。对于红点，若红点 $x$ 与格子 $y$ 的最短路径不大于 $M$，则 $x$ 向 $y$ 的入点连边，表示在 $M$ 时间内 $x$ 能够走到 $y$。蓝点同理，只是将入点改为出点。

之所以我们将格子拆成了入点和出点，是因为一个格子最后只会有不超过一对红蓝点。所以拆点之后连一条流量为 $1$ 的边就能限制了。

然后跑网络流求最大流就行了，$M$ 的可行条件是所有红点都有蓝点匹配，即最大流数量为 $a$ 或者 $b$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define pii pair<int,int>
#define x first
#define y second
#define gc getchar()
#define rd read()
#define debug() puts("------------")

namespace yzqwq{
	il int read(){
		int x=0,f=1;char ch=gc;
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
		while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
		return x*f;
	}
	il int qmi(int a,int b,int p){
		int ans=1;
		while(b){
			if(b&1) ans=ans*a%p;
			a=a*a%p,b>>=1;
		}
		return ans;
	}
	il auto max(auto a,auto b){return (a>b?a:b);}
	il auto min(auto a,auto b){return (a<b?a:b);}
	il int gcd(int a,int b){
		if(!b) return a;
		return gcd(b,a%b);
	}
	il int lcm(int a,int b){
		return a/gcd(a,b)*b;
	}
	il void exgcd(int a,int b,int &x,int &y){
		if(!b) return x=1,y=0,void(0);
		exgcd(b,a%b,x,y);
		int t=x;
		x=y,y=t-a/b*x;
		return ;
	}
	mt19937 rnd(time(0));
}
using namespace yzqwq;

const int N=2e6+10,M=30,K=40000;
int n,m,male,female;
struct node{
	int x,y,v,id;
}p1[K],p2[K];
int Dis[M][M];
int s,t,ans;
int ne[N],e[N],w[N],h[K],h2[K],idx;
int dep[K],vis[K];
char ch[M][M];
map<int,map<int,int>> ddd; 
int dx[10]={-1,1,0,0},dy[10]={0,0,1,-1};
int ct,id[M][M];

il void add(int a,int b,int c){
	ne[++idx]=h[a],e[idx]=b,w[idx]=c,h[a]=idx;
	ne[++idx]=h[b],e[idx]=a,w[idx]=0,h[b]=idx;
}

il bool bfs(){
	for(re int i=s;i<=t;++i)
		h2[i]=h[i],vis[i]=0,dep[i]=1e18;
	queue<int> qu;
	qu.push(s),dep[s]=0,vis[s]=1;
	while(!qu.empty()){
		int now=qu.front();qu.pop();
		for(re int i=h[now];i;i=ne[i]){
			int j=e[i];
			if(dep[j]>dep[now]+1&&w[i]){
				dep[j]=dep[now]+1;
				if(!vis[j]){
					vis[j]=1,
					qu.push(j);
				}
			}
		}
	}
	if(dep[t]>=1e18) return 0;
	return 1;
}
il int dfs(int now,int Min){
	if(now==t) return ans+=Min,Min;
	int use=0;
	for(re int i=h2[now];i;i=ne[i]){
		int j=e[i];h2[now]=i;
		if(dep[j]==dep[now]+1&&w[i]){
			int use_=dfs(j,min(Min-use,w[i]));
			if(use<0) continue;
			use+=use_;
			w[i]-=use_,w[i^1]+=use_;
			if(use==Min) break;
		}
	}
	return use;
}
il void dinic(){
	while(bfs()) dfs(s,1e18);
	return ;
}

il void Bfs(int x,int y,int Id,bool fl,int mid,int pay){
	for(re int i=0;i<=n+1;++i)
	for(re int j=0;j<=m+1;++j)
		Dis[i][j]=1e18;
	queue<pii> qu;qu.push({x,y}),Dis[x][y]=0;
	while(!qu.empty()){
		pii now=qu.front();qu.pop();
		if(Dis[now.x][now.y]>mid) continue;
		if(!fl) add(Id,id[now.x][now.y],1);
		else add(n*m+id[now.x][now.y],Id,1);
		for(re int i=0;i<4;++i){
			int X=now.x+dx[i],Y=now.y+dy[i];
			if(X<1||X>n||Y<1||Y>m||Dis[X][Y]<=Dis[now.x][now.y]+pay||ch[X][Y]=='#'||ch[now.x][now.y]=='#') continue;
			Dis[X][Y]=Dis[now.x][now.y]+pay,qu.push({X,Y});
		}
	}
	return ;
}
il bool check(int mid){
	for(re int i=s;i<=t;++i) 
		h[i]=0;idx=1,ans=0;
	for(re int i=1;i<=male;++i) 
		add(s,p1[i].id,1);
	for(re int i=1;i<=female;++i) 
		add(p2[i].id,t,1);
	for(re int i=1;i<=male;++i) 
		Bfs(p1[i].x,p1[i].y,p1[i].id,0,mid,p1[i].v);
	for(re int i=1;i<=female;++i) 
		Bfs(p2[i].x,p2[i].y,p2[i].id,1,mid,p2[i].v);
	for(re int i=1;i<=n;++i)
	for(re int j=1;j<=m;++j) 
		add(id[i][j],n*m+id[i][j],1);
	dinic();
	return ans>=male;
}

il void solve(){
	n=rd,m=rd,male=rd,female=rd;
	s=0,t=4*n*m+1;
	for(re int i=1;i<=n;++i)
	for(re int j=1;j<=m;++j)
		cin>>ch[i][j];
	int X=rd,Y=rd,V=rd;
	for(re int i=1;i<=male;++i) p1[i]={rd,rd,rd,++ct};
	for(re int i=1;i<=female;++i) p2[i]={rd,rd,rd,++ct};
	if(male<female) p1[++male]={X,Y,V,++ct};
	else p2[++female]={X,Y,V,++ct};
	for(re int i=1;i<=n;++i)
	for(re int j=1;j<=m;++j)
		id[i][j]=++ct; 
	if(male!=female) return printf("-1\n"),void(0);
	int l=0,r=1e12,Ans=-1;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid)) Ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%lld\n",Ans);
	return ;
}

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int t=1;while(t--)
	solve();
	return 0;
}
```

---

## 作者：Mashu77 (赞：2)

首先 
$|a−b|=
1$，否则无解。然后就变成 
$k$
 个红棋子与 
$k$
 个蓝棋子。

乍一看是二分图匹配。但实际上每个格子只能容纳一对棋子，故不能直接套用。

类似二分图，我们不难想到用网络流来解决这种匹配问题。因为每个棋子到任意格子的距离是已知的，故尝试二分答案。

首先将每个格子拆为入点和出点，其间连一条边。依次考虑红棋子 
$i$
 与格子 
$j$，如果 
$i$
 到 
$j$
 的时间不大于当前二分的 
$m
i
d$，则从 
$i$
 连一条边到 
$j$
 的入点。同理，如果蓝棋子 
$i$
 到格子 
$j$
 的时间不大于 
$m
i
d$，则从 
$j$
 的出点连一条边到 
$i$。再从源点到所有红棋子连边，从所有蓝棋子到汇点连边。所有边的容量均为 
$1$。跑最大流，判断其是否等于 
$k$
 即可。

这种做法的时间复杂度为 
$O
(
n^
6
\log
a
)$，其中 
$a$
 为最大时间。显然不能通过。

发现瓶颈在于二分答案。因为网络流有一个很好的性质：往网络中加边，不必重构网络，直接跑就可以得出新的最大流。于是尝试另一种方式：对于所有连接棋子与格子的边，按照其时间从小到大加入。每加一条边跑一次最大流。则当最大流等于 
$k$
 时，加入的边的时间就是答案。复杂度为 
$O(n^4×n^4)=
O
(
n^
8
)$。

这样就有新的优化空间了。考虑将边分块：设有 
$t$
 条边，每 
$\sqrt
t$
 条分为一组。每次加入一组并跑最大流。当最大流等于 
$k$
 时，再将这组的边重新一条条加入。这样的复杂度为 
$O
(
\sqrt{n^4}×n^4)=
O
(
n^
6
)$
。可以通过。

但实际上因为大常数，你还是会 TLE on test 87。解决办法是卡常，或者像我一样：分块套分块。设一个阈值 
$α$，先将块长设为 
$t^
α$，等最大流等于 
$k$
 时，再将当前块分块，块长为 
$t^{
α^
2}$。则复杂度为 $\displaystyle O((t^{1-\alpha}+t^{\alpha(1-\alpha)}+t^{\alpha^2})\times n^4)$，易知 
$\alpha=\frac{\sqrt5-1}{2}$，化简一下就是 
$n^{
5.528}$。可以通过。

---

## 作者：Pink_Dove (赞：0)

[AC 记录](https://codeforces.com/contest/311/submission/310519486)

[更 pass 的食用体验](https://yumomeow.github.io/2025/03/10/solution-CF513F/)
### 题意
有 $a+b+1$ 个会动的棋子，在一个大小为 $n\times m$ 的棋盘上，棋盘上有一些点有障碍。棋子中，有 $a$ 个红色棋子，$b$ 个红色棋子，和 $1$ 个既能当作红棋子又能当作蓝棋子的通配棋子。每个棋子有自己的初始位置 $(x_i,y_i)$ 和速度 $t_i$，其中 $t_i$ 表示自己走到相邻的格子所需要的时间。

一个局面是好的，当且仅当对于每个格子，要么这个格子上没有棋子，要么这个格子上恰好存在一个红棋子与一个蓝棋子。你可以控制所有棋子的移动。请问最少多少时间后能达到处于一个好的局面。

### 题解
首先考虑如何消除通配棋子的影响。要满足条件红色棋子数量一定等于蓝色棋子数量，所以我们将通配棋子给少的一方，如果仍不相等则输出 `-1`。这样我们就将所有棋子划分到两个数量相等的集合。

因为棋子的任意移动我们不太好处理，考虑二分答案，用网络流求解。建立三列点，分别为红色棋子、蓝色棋子和网格上的每一个点，将网格上的点拆成入点和出点，连一条容量为 $1$ 的边满足每个格子上恰好两个棋子的限制。

从 $s$ 向红色棋子连边，蓝色棋子向 $t$ 连边。设当前答案为 $mid$，每次以每个棋子为起点 bfs 求出到其他所有点的距离，若 $\le mid$ 则可达，若是红色棋子则由棋子向入点连边，否则由出点向棋子连边，跑最大流即可。

每一个连接红色棋子、棋盘、蓝色棋子的路径表示一个格子上同时有两个棋子，提供 $1$ 的流量。若流量 $\ge \frac{a+b+1}{2}$ 则表示可以满足限制。需要卡常。

### 代码
```cpp
#include<iostream>
#include<cstring>
#include<queue>
#define int long long
#define reg register
#define il inline
using namespace std;
const int N=3010,M=2e6+10,INF=0x3f3f3f3f3f3f3f3f;
int n,m,a,b,r,c,t,dis[23][23],idx,hsh[23][23][2];
int S,T,cur[N],head[N],dep[N],tot;
int dx[]={0,1,0,-1},dy[]={1,0,-1,0};
char mp[50][50];
struct Edge{int to,nxt,f;}e[M];
struct Node{int x,y,t,id;}ma[510],fe[510];
il void add(int u,int v,int c){
    e[++tot]={v,head[u],c};head[u]=tot;
    e[++tot]={u,head[v],0};head[v]=tot;
}
il bool bfs(){
    queue<int> q;q.push(S);
    memset(dep,-1,sizeof(dep));
    dep[S]=0;cur[S]=head[S];
    while(q.size()){
        int u=q.front();q.pop();
        for(reg int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(dep[v]==-1&&e[i].f){
                dep[v]=dep[u]+1;
                cur[v]=head[v];
                if(v==T) return 1;
                q.push(v);
            }
        }
    }
    return 0;
}
il int find(int u,int limit){
    if(u==T) return limit;
    int flow=0;
    for(reg int i=cur[u];i&&flow<limit;i=e[i].nxt){
        int v=e[i].to;cur[u]=i;
        if(dep[v]==dep[u]+1&&e[i].f){
            int t=find(v,min(e[i].f,limit-flow));
            if(!t) dep[v]=-1;
            e[i].f-=t;e[i^1].f+=t;flow+=t;
        }
    }
    return flow;
}
il int Dinic(){
    int r=0;
    while(bfs()){
        int flow;
        while(flow=find(S,INF)) r+=flow;
    }
    return r;
}
il void getdis(Node now,int limit,bool op){
    queue<pair<int,int> > q;
    memset(dis,0x3f,sizeof(dis));
    q.push({now.x,now.y});dis[now.x][now.y]=0;
    while(q.size()){
        int x=q.front().first,y=q.front().second;q.pop();
        if(dis[x][y]>limit) continue;
        if(!op) add(now.id,hsh[x][y][0],1);
        else add(hsh[x][y][1],now.id,1);//两种情况
        for(reg int i=0;i<4;i++){
            int tx=x+dx[i],ty=y+dy[i];
            if(tx<=n&&ty<=m&&tx>0&&ty>0&&dis[tx][ty]>dis[x][y]+now.t&&mp[tx][ty]!='#'){
                dis[tx][ty]=dis[x][y]+now.t;q.push({tx,ty});
            }
        }
    }
    return;
}
il bool check(int x){
    tot=1;memset(head,0,sizeof(head));
    for(reg int i=1;i<=a;i++) add(S,ma[i].id,1),getdis(ma[i],x,0);
    for(reg int i=1;i<=b;i++) add(fe[i].id,T,1),getdis(fe[i],x,1);//根据距离连边
    for(reg int i=1;i<=n;i++) for(reg int j=1;j<=m;j++) add(hsh[i][j][0],hsh[i][j][1],1);//入点和出点连边
    return Dinic()>=a;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>a>>b;
    for(reg int i=1;i<=n;i++)for(reg int j=1;j<=m;j++)cin>>mp[i][j];
    cin>>r>>c>>t;
    for(reg int i=1;i<=a;i++) cin>>ma[i].x>>ma[i].y>>ma[i].t,ma[i].id=++idx;
    for(reg int i=1;i<=b;i++) cin>>fe[i].x>>fe[i].y>>fe[i].t,fe[i].id=++idx;
    if(a<b) ma[++a].x=r,ma[a].y=c,ma[a].t=t,ma[a].id=++idx;
    else fe[++b].x=r,fe[b].y=c,fe[b].t=t,fe[b].id=++idx;
    for(reg int i=1;i<=n;i++)for(reg int j=1;j<=m;j++)for(reg int k=0;k<=1;k++) hsh[i][j][k]=++idx;
    S=++idx;T=++idx;
    if(a!=b){
        cout<<-1;
        return 0;
    }
    int l=0,ans=-1;r=1e12;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) r=mid-1,ans=mid;
        else l=mid+1;
    }
    cout<<ans;
    return 0;
}

---

## 作者：SunsetSamsara (赞：0)

## CF513F2

### 题意

有 $a + b + 1$ 个会动的棋子，在一个大小为 $n\times m$ 的棋盘上，棋盘上有一些点有障碍。棋子中，有 $a$ 个红色棋子，$b$ 个蓝色棋子，和 $1$ 个既能当作红棋子又能当作蓝棋子的通配棋子。

一个局面是好的，当且仅当对于每个格子，要么这个格子上没有棋子，要么这个格子上恰好存在一个红棋子与一个蓝棋子。

每个棋子有自己的初始位置 $(x_i,y_i)$ 和速度 $t_i$，其中 $t_i$ 表示自己走到相邻的格子所需要的时间。

你可以控制所有棋子的移动。请问最少多少时间后能达到处于一个好的局面。

### 标签

思维，二分，网络流

### 做法

首先如果 $|a - b| \neq 1$，那么怎么变换通配棋子都不能符合条件，无解。

显然需要把通配棋子变为少的那一方，问题就变成了无通配棋子的情形。

接下来考虑二分答案，看在时间 $t$ 能不能走到一个好的局面。

将每个格子拆成入点和出点，入点和出点间连上一条流量为 $1$ 的边，表示至多存在一个蓝棋子和红棋子。

源点向蓝棋子连流量为 $1$ 的边，汇点向红棋子连流量为 $1$ 的边。将每个蓝棋子向时间 $t$ 内能到的点的入点连边，将每个红棋子向时间 $t$ 内能到的点的出点连边。

这样一条流量为 $1$ 的路径就表示蓝棋子要到达位置 $p$，红棋子也要到达位置 $p$，就表示一对匹配的棋子。

于是就判断时间为 $t$ 时能不能匹配 $\dfrac{a+b+1}2$ 个棋子，就是判断最大流是否为 $k$。

预处理时对于所有的蓝棋子和红棋子进行 bfs 用于判断时间 $t$ 时能到达哪些点。

注意到连出的图是一个二分图，此时 dinic 算法复杂度为 $O(E\sqrt V)$。其中 $V = 2 + a + b + 1 + n\times m \le 3nm$，$E \le a + b + 1 + n\times m + (a + b + 1) \times (n\times m) \le 2n^2m^2$，一次判断的复杂度为 $O(n^{2.5}m^{2.5})$，总复杂度就是 $O(n^{2.5}m^{2.5}\log V)$，可以通过。

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
const int N = 30;
int n, m, k;
char a[N][N];
int tot;
int id1[N][N];
int id2[N][N];
int x[N * N * 2], y[N * N * 2], v[N * N * 2];
lld dis[N * N * 2][N][N];
bool vis[N * N * 2][N][N];
inline void bfs(int t, int x, int y) {
	memset(dis[t], 0x7f, sizeof(dis[t]));
	memset(vis[t], 0, sizeof(vis[t]));
	queue<pair<int, int>> q;
	q.push(make_pair(x, y));
	dis[t][x][y] = 0;
	vis[t][x][y] = 1;
	for (; q.size(); ) {
		int x = q.front().first, y = q.front().second; q.pop();
		if (!vis[t][x][y - 1] && a[x][y - 1] == '.') q.push(make_pair(x, y - 1)), dis[t][x][y - 1] = dis[t][x][y] + v[t], vis[t][x][y - 1] = 1;
		if (!vis[t][x][y + 1] && a[x][y + 1] == '.') q.push(make_pair(x, y + 1)), dis[t][x][y + 1] = dis[t][x][y] + v[t], vis[t][x][y + 1] = 1;
		if (!vis[t][x - 1][y] && a[x - 1][y] == '.') q.push(make_pair(x - 1, y)), dis[t][x - 1][y] = dis[t][x][y] + v[t], vis[t][x - 1][y] = 1;
		if (!vis[t][x + 1][y] && a[x + 1][y] == '.') q.push(make_pair(x + 1, y)), dis[t][x + 1][y] = dis[t][x][y] + v[t], vis[t][x + 1][y] = 1;
	}
}
int s, t;
struct edge {
	int to, nxt;
	lld val;
} es[1000010];
int head[10010];
int ecnt = 1;
inline void addedge(int fr, int to, lld val) {
	es[++ ecnt] = (edge){to, head[fr], val};
	head[fr] = ecnt;
}
int dep[30010];
int cur[30010];
inline int bfs(int s, int t) {
	for (int i = 0; i <= tot; ++ i) dep[i] = 0, cur[i] = head[i];
	static int q[30010], qhead, qtail;
	qhead = 1, qtail = 0;
	q[++ qtail] = s, dep[s] = 1;
	int u;
	while (qhead <= qtail) {
		u = q[qhead ++];
		for (int e = head[u], v; e; e = es[e].nxt) {
			v = es[e].to;
			if (es[e].val && !dep[v]) {
				dep[v] = dep[u] + 1;
				q[++ qtail] = v;
			}
		}
	}
	return dep[t];
}
inline lld dfs(const int &u, const int &t, const lld &flow) {
	if (u == t) return flow;
	lld ret = 0;
	for (int e = cur[u], v; e && ret < flow; e = es[e].nxt) {
		cur[u] = e;
		v = es[e].to;
		if (es[e].val && dep[v] == dep[u] + 1) {
			lld x = dfs(v, t, min(es[e].val, flow - ret));
			if (x) es[e].val -= x, es[e ^ 1].val += x, ret += x;
		}
	}
	if (ret < flow) dep[u] = -1;
	return ret;
}
inline lld dinic(int s, int t) {
	lld ans = 0, x;
	while (bfs(s, t)) for (; x = dfs(s, t, 0x3f3f3f3f3f3f3f3fll); ans += x);
	return ans;
}
inline bool check(lld x) {
	for (int i = 0; i <= tot; ++ i) head[i] = 0;
	ecnt = 1;
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= m; ++ j) {
			addedge(id1[i][j], id2[i][j], 1);
			addedge(id2[i][j], id1[i][j], 0);
		}
	for (int i = 1; i <= k; ++ i) addedge(s, i, 1), addedge(i, s, 0);
	for (int i = k + 1; i <= 2 * k; ++ i) addedge(i, t, 1), addedge(t, i, 1);
	for (int i = 1; i <= k; ++ i) {
		for (int a = 1; a <= n; ++ a)
			for (int b = 1; b <= m; ++ b)
				if (dis[i][a][b] <= x) {
//					printf("%d, %d, %d: %d\n", i, a, b, dis[i][a][b]);
					addedge(i, id1[a][b], 1);
					addedge(id1[a][b], i, 0);
				}
	}
	for (int i = k + 1; i <= 2 * k; ++ i) {
		for (int a = 1; a <= n; ++ a)
			for (int b = 1; b <= m; ++ b) {
//				printf("%d, %d -> %d (%lld)\n", a, b, i, dis[i][a][b]);
				if (dis[i][a][b] <= x) {
					addedge(id2[a][b], i, 1);
					addedge(i, id2[a][b], 0);
				}
			}
	}
	int c = dinic(s, t);
//	printf("%lld %d\n", x, c);
	return c == k;
}
int main() {
	int p, q;
	scanf("%d%d%d%d", &n, &m, &p, &q);
	if (abs(p - q) != 1) {
		puts("-1");
		return 0;
	}
	for (int i = 1; i <= n; ++ i)
		scanf("%s", a[i] + 1);
	k = max(p, q);
	for (int i = 1; i <= 2 * k; ++ i) scanf("%d%d%d", x + i, y + i, v + i), ++ tot;
	if (k != q) {
		swap(x[1], x[p + 1]);
		swap(y[1], y[p + 1]);
		swap(v[1], v[p + 1]);
	}
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= m; ++ j)
			id1[i][j] = ++ tot;
	for (int i = 1; i <= n; ++ i)
		for (int j = 1; j <= m; ++ j)
			id2[i][j] = ++ tot;
	bfs(1, x[1], y[1]);
	for (int i = 1; i <= 2 * k; ++ i) bfs(i, x[i], y[i]);
	s = ++ tot, t = ++ tot;
//	printf("%d\n", check(6));
	lld l = 0, r = 0x3f3f3f3f3f3f3f3fll, mid;
	for (; l < r; ) {
		mid = (l + r) >> 1;
		if (check(mid)) r = mid;
		else l = mid + 1;
	}
	if (l == 0x3f3f3f3f3f3f3f3fll) puts("-1");
	else printf("%lld\n", l);
}
```

---

## 作者：AlicX (赞：0)

## Solution 

场切题啊。

首先考虑通配棋子的去处，如果第一类棋子的数量小于第二类棋子的数量，就分配到第一类，否则分配到第二类。然后判断第一类棋子和第二类棋子数量是否相等，如果不相等则无解。

然后求出每个棋子到棋盘上每一个可到达的点的最短路，用 `bfs` 完成即可。然后二分出最小时间 $mid$，把第一类棋子与源点连边，第二类棋子与汇点连边，对于一颗棋子，如果可以在 $mid$ 时间内到达一个点，则向那个点连边。因为规定最后每一个点上只能有一对棋子，所以考虑拆点，由入点向出点连一条流量为 $1$ 的边即可。

常数略大，需要轻微卡常。

```cpp
#include<bits/stdc++.h> 
#define int long long  
#define x first 
#define y second 
#define il inline 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
il int read(){ 
	int x=0,f=1; char ch=getchar(); 
	while(ch<'0'||ch>'9'){ if(ch=='-') f=-1; ch=getchar(); } 
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar(); 
	return x*f; 
} 
const int Maxn=30; 
const int N=1e6+10; 
const int INF=1e18+7; 
int n,m; 
int s,t; 
int k1,k2; 
int h[N],idx=0; 
int dis[N],now[N]; 
struct Edge{ 
	int w; 
	int to,ne; 
}e[N<<1]; 
il void add(int u,int v,int w){ 
	e[idx].w=w,e[idx].to=v,e[idx].ne=h[u],h[u]=idx++; 
	e[idx].w=0,e[idx].to=u,e[idx].ne=h[v],h[v]=idx++; 
} 
il bool bfs(){ 
	queue<int> q; 
	for(int i=s;i<=t;i++) dis[i]=INF,now[i]=h[i];  
	q.push(s); dis[s]=0; 
	while(!q.empty()){ 
		int u=q.front(); q.pop(); 
		for(int i=h[u];i!=-1;i=e[i].ne){ 
			int to=e[i].to; 
			if(!e[i].w) continue; 
			if(dis[to]==INF){ 
				dis[to]=dis[u]+1; 
				q.push(to); if(to==t) return true; 
			} 
		} 
	} return false; 
} 
il int Dinic(int u,int flow){ 
	int ans=0; 
	if(u==t) return flow; 
	for(int i=now[u];i!=-1;i=e[i].ne){ 
		int to=e[i].to; now[u]=i; 
		if(!e[i].w) continue; 
		if(dis[to]==dis[u]+1){ 
			int res=Dinic(to,min(e[i].w,flow)); 
			if(!res) continue; 
			ans+=res,flow-=res; 
			e[i].w-=res,e[i^1].w+=res; 
			if(!flow) break; 
		} 
	} return ans; 
} 
char a[Maxn][Maxn]; 
struct Node{ 
	int x,y,t; 
}a1[Maxn*Maxn],a2[Maxn*Maxn]; 
#define id(x,y) (x-1)*m+y 
int dist[2*Maxn*Maxn][Maxn][Maxn]; 
int dx[4]={0,0,-1,1},dy[4]={-1,1,0,0}; 
il void init(int u,int sx,int sy,int t){ 
	for(int k=1;k<=n;k++){ 
		for(int p=1;p<=m;p++){ 
			dist[u][k][p]=INF; 
		} 
	} dist[u][sx][sy]=0; 
	queue<pii> q; q.push({sx,sy}); 
	while(!q.empty()){ 
		int x=q.front().x,y=q.front().y; q.pop(); 
		for(int d=0;d<4;d++){ 
			int x0=x+dx[d],y0=y+dy[d]; 
			if(dist[u][x0][y0]==INF&&x0>=1&&x0<=n&&y0>=1&&y0<=m&&a[x0][y0]=='.'){
				dist[u][x0][y0]=dist[u][x][y]+t; q.push({x0,y0}); 
			} 
		} 
	} 
} 
il bool check(int mid){ 
	idx=0; s=0,t=k1+k2+n*m*2+1; 
	for(int i=s;i<=t;i++) h[i]=-1; 
	for(int i=1;i<=k1;i++){ 
		add(s,i,1); 
		for(int k=1;k<=n;k++){ 
			for(int p=1;p<=m;p++){ 
				if(dist[i][k][p]<=mid) add(i,id(k,p)+k1+k2,1); 
			} 
		} 
	} for(int i=1;i<=k2;i++){ 
		add(i+k1,t,1); 
		for(int k=1;k<=n;k++){ 
			for(int p=1;p<=m;p++){ 
				if(dist[i+k2][k][p]<=mid) add(id(k,p)+k1+k2+n*m,i+k1,1); 
			} 
		} 
	} for(int i=1;i<=n;i++){ 
		for(int j=1;j<=m;j++){ 
			if(a[i][j]=='#') continue; 
			add(id(i,j)+k1+k2,k1+k2+id(i,j)+n*m,1); 
		} 
	} int ans=0; 
	while(bfs()) ans+=Dinic(s,INF); 
	return ans>=k1; 
} 
signed main(){ 
	n=read(),m=read(),k1=read(),k2=read(); 
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>a[i][j]; 
	int X=read(),Y=read(),T=read(); 
	for(int i=1;i<=k1;i++) a1[i].x=read(),a1[i].y=read(),a1[i].t=read(); 
	for(int i=1;i<=k2;i++) a2[i].x=read(),a2[i].y=read(),a2[i].t=read(); 
	if(k1<k2) a1[++k1]={X,Y,T}; else a2[++k2]={X,Y,T}; if(k1!=k2){ puts("-1"); return 0; } 
	for(int i=1;i<=k1;i++) init(i,a1[i].x,a1[i].y,a1[i].t); 
	for(int i=1;i<=k2;i++) init(i+k1,a2[i].x,a2[i].y,a2[i].t); 
	int l=0,r=1e12,res=-1; 
	while(l<=r){ 
		int mid=l+r>>1; 
		if(check(mid)) r=mid-1,res=mid; 
		else l=mid+1; 
	} printf("%lld\n",res); 
	return 0; 
} 
```

---

## 作者：_zhy (赞：0)


首先如果 $|a - b| \not= 1$ 肯定无解，因为根本不能保证两两配对。

然后为了方便求时间，我们先通过 bfs 求出两两点之间的最小距离（不能到达为极大值）。

然后对于输入的每个史莱姆，我们把它和它它的可达点以及最小时间存下来。

那个史莱姆王，把它当成公的或母的处理即可（哪个少一只就当成哪个处理）。

然后二分答案，如果 $mid$ 大于等于最小时间，就连边。

建边方法：

- 因为每个点最多容纳 $1$ 对，所以我们将一个点拆成两个，它们之间容量为 $1$。

- 公的连在可达点的一边，母的连在另一边，容量也是 $1$。

- 分别将源点 $s$ 和汇点 $t$ 和每个公的以及每个母的连起来，由于每只数量为一，故容量为 $1$。

最后跑一遍最大流，如果最大流等于 $\max(a, b)$，就说明当前 $mid$ 满足条件。

一个优化：我们可以将每条边按最小时间排序，这样在建边的时候当当前边的时间大于 $mid$ 时，就可以直接 break 了。

#### code

```cpp
#include <cstdio>
#include <queue>
#include <algorithm>
#include <cmath>
#include <utility>
#define inf 1e15
#define LL long long

using namespace std;

const int N = 1e4 + 5, M = 5e5 + 5, dx[4] = { 0, 0, 1, -1 }, dy[4] = { 1, -1, 0, 0 };

struct Edge {
    int to, next;
    LL c;
};
struct node {
    int n, tot, head[N], h[N], now[N];
    LL flow;
    Edge edge[M << 1];
    queue<int> q;
    inline node() { tot = 1; }
    inline void add(int u, int v, int c) {
        edge[++tot].to = v, edge[tot].c = c;
        edge[tot].next = head[u], head[u] = tot;
    }
    inline bool bfs(int s, int t) {
        while (!q.empty())
			q.pop();
        for (int i = 1; i <= n; i++)
			h[i] = n + 1, now[i] = head[i];
        q.push(s), h[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = head[u]; i; i = edge[i].next) {
                int v = edge[i].to;
                LL c = edge[i].c;
                if (c && h[v] == n + 1) {
                    h[v] = h[u] + 1;
                    q.push(v);
                }
            }
        }
        return h[t] != n + 1;
    }
    inline LL dfs(int u, LL flo, int t) {
        if (u == t)
            return flo;
        LL x = 0;
        for (int i = now[u]; i; i = edge[i].next) {
            now[u] = i;
            int v = edge[i].to;
            LL c = edge[i].c;
            if (c && h[v] == h[u] + 1) {
                LL fl = dfs(v, min(flo - x, c), t);
                edge[i].c -= fl, edge[i ^ 1].c += fl;
                x += fl;
                if (x == flo)
                    break;
            }
        }
        return x;
    }
    inline void dinic(int s, int t) {
        flow = 0;
        while (bfs(s, t))
			flow += dfs(s, inf, t);
    }
} F;
int n, m, a, b, tot, r, c, S, T;
char xx[25][25];
LL dis[25][25][25][25], t, L, R, ans = -1;
queue<pair<int, int> > q;
struct Node {
    int u, v;
    LL w;
} e[M];

inline void bfs(int sx, int sy) {
    while (!q.empty()) q.pop();
    dis[sx][sy][sx][sy] = 0;
    q.push(make_pair(sx, sy));
    while (!q.empty()) {
        int ux = q.front().first, uy = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int tx = ux + dx[i], ty = uy + dy[i];
            if (tx < 1 || ty < 1 || tx > n || ty > m || dis[sx][sy][tx][ty] < inf || xx[tx][ty] == '#')
                continue;
            dis[sx][sy][tx][ty] = dis[sx][sy][ux][uy] + 1;
            q.push(make_pair(tx, ty));
        }
    }
}

inline bool check(LL mid) {
    for (int i = 1; i <= F.n; i++) F.head[i] = 0;
    F.tot = 1;
    for (int i = 1; i <= tot; i++)
        if (e[i].w <= mid)
            F.add(e[i].u, e[i].v, 1), F.add(e[i].v, e[i].u, 0);
        else
            break;
    F.n = max(a, b) * 2 + n * m * 2 + 2;
    F.dinic(S, T);
    return F.flow == max(a, b);
}

inline bool cmp(Node X, Node Y) { return X.w < Y.w; }

int main() {
    scanf("%d %d %d %d", &n, &m, &a, &b);
    if (abs(a - b) != 1)
        return puts("-1"), 0;
    for (int i = 1; i <= n; i++) {
        scanf(" ");
        for (int j = 1; j <= m; j++)
			xx[i][j] = getchar();
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int k = 1; k <= n; k++)
                for (int l = 1; l <= m; l++)
					dis[i][j][k][l] = inf;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (xx[i][j] == '.')
                bfs(i, j);
    int ma = max(a, b);
    S = 2 * ma + n * m * 2 + 1, T = S + 1;
    if (a < b) {
        scanf("%d %d %lld", &r, &c, &t);
        e[++tot].u = S, e[tot].v = ma, e[tot].w = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (dis[r][c][i][j] < inf)
                    e[++tot].u = ma, e[tot].v = 2 * ma + (i - 1) * m + j, e[tot].w = dis[r][c][i][j] * t;
    } else if (b < a) {
        scanf("%d %d %lld", &r, &c, &t);
        e[++tot].u = ma * 2, e[tot].v = T, e[tot].w = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (dis[r][c][i][j] < inf)
                    e[++tot].u = 2 * ma + (i - 1) * m + n * m + j, e[tot].v = ma * 2, e[tot].w = dis[r][c][i][j] * t;
    }
    for (int k = 1; k <= a; k++) {
        scanf("%d %d %lld", &r, &c, &t);
        e[++tot].u = S, e[tot].v = k, e[tot].w = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (dis[r][c][i][j] < inf)
                    e[++tot].u = k, e[tot].v = 2 * ma + (i - 1) * m + j, e[tot].w = dis[r][c][i][j] * t;
    }
    for (int k = 1; k <= b; k++) {
        scanf("%d %d %lld", &r, &c, &t);
        e[++tot].u = k + ma, e[tot].v = T, e[tot].w = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (dis[r][c][i][j] < inf)
                    e[++tot].u = 2 * ma + (i - 1) * m + n * m + j, e[tot].v = k + ma, e[tot].w = dis[r][c][i][j] * t;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            e[++tot].u = 2 * ma + (i - 1) * m + j, e[tot].v = 2 * ma + n * m + (i - 1) * m + j;
    a = b = ma;
    L = 0, R = 1e12;
    sort(e + 1, e + tot + 1, cmp);
    while (L <= R) {
        LL mid = L + R >> 1;
        if (check(mid))
            ans = mid, R = mid - 1;
        else
            L = mid + 1;
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

