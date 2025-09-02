# [BalticOI 2005] Bus Trip

## 题目描述

这里有 $N$ 座城镇, 和城镇之间的 $M$ 巴士单行线(没有中间停靠站)。 城镇从$1$到 $N$ 标号。 一个旅行者在 $0$ 时刻位于 $1$ 号城镇想要到达 $P$ 号城镇。他将乘坐巴士在 $T$ 时刻到达 $P$ 号城镇。如果他早到了，他必须等待。

对于任意一个巴士路线 $i$ , 我们知道其中的起点城镇 $si$ 和目标城镇$ti$ 。我们也同样知道路线的出发时间和到达时间,但仅仅是近似值：我们知道巴士离开起点城镇 $si$ 在时间范围$[ai, bi]$内，且到达目标城镇 $ti$ 在时间范围$[ci, di]$内(端点值包括在内)。

旅行者不喜欢等待, 因此他要寻找一个旅行计划使得最大等待时间尽量小，同时保证绝对不会错过计划中的任何一辆巴士(意思是, 每次他换乘巴士, 他需要下车的巴士的最晚到达时间不会迟于他需要搭乘的下一辆巴士的最早出发时间)。

当计算等待时间时，我们必须假设最早可能到达的时间和最晚可能出发的时间。

编写一个程序，寻找一个最为合理的搭车计划。

## 说明/提示

翻译来自BZOJ P1354

## 样例 #1

### 输入

```
3 6 2 100
1 3 10 20 30 40
3 2 32 35 95 95
1 1 1 1 7 8
1 3 8 8 9 9
2 2 98 98 99 99
1 2 0 0 99 101```

### 输出

```
32```

# 题解

## 作者：WarningQAQ (赞：13)

### 题目大意：
给出一些车的班次，包括起点，终点，到达起点时间区间，到达终点时间区间，想要$T$时刻到达$n$号点，问最坏情况下的最短等待时间。
### 题解：
我们可以将问题转化为中间乘坐公交的最长时间。然后我们对于每条边我们把它当成在 $a$ 时刻出发，中间乘坐时间为 $c-b$ ，到达时间为d的一条线路。然后你就可以想到一个 $O(NM)$ 的动归, $f(i,j)$ 表示在 $j$ 时刻到达 $i$ 的左右，答案
当然那一定是 TLE+MLE ，于是我们考虑优化。我们发现原方程有两种转移：

### 1： $f(i,j) = f(i,j-1)$

### 2： $f(i,j) = f(k,l) + dis$ （有一条边）

------------
我们在滚掉第一维之后就发现真正有用的转移只有 $m$ 次，我们将每条路拆分为两个点， $a$ 点处理答案保存， $d$ 点处理最长路的计算，按照时间节点排序，顺序求最长路，我们直接排个序就可以了，注意排序的关键字。
新的状态转移：
### 1： $ans(id(i)) = f(x(i))$  ; $dis(i)>0$ ;
### 2： $f(x(i))=$ $max( f(x(i)) , ans(id(i)) + f(i) )$ ;

------------
### 代码：
```cpp
#include"bits/stdc++.h"
#define N 50005
using namespace std;
char ch[N*4];
char *Q,*T;
inline char gc(){//快读加fread，快上加快
    if(Q==T){
        T=(Q=ch)+fread(ch,1,N*4,stdin);
        if(Q==T)return EOF;
    }
    return *Q++;
}
inline int read(){//快读主体
    int f=0;
    char c=gc();
    for(;c<'0'||c>'9';c=gc());
    for(;c>='0'&&c<='9';c=gc())f=(f<<1)+(f<<3)+c-48;
    return f;
}
int n=read(),m=read(),tt=read(),t=read(),x,y,a,b,c,d,tot;//由于懒得再打一遍，直接在定义的时候读入了
int dis[N],ans[N*2];
struct ask{
	int x,t,id,dis;
}q[N*4];
bool cmp(const ask&a,const ask&b){//注意排序的依据
    return a.t==b.t?a.dis>b.dis:a.t<b.t;
}
int main(){
    for(int i=1;i<=m;i++){//建图
        x=read();y=read();a=read();b=read();c=read();d=read(); 
        q[++tot]=(ask){x,a,i,0};
        q[++tot]=(ask){y,d,i,c-b};
    }
    q[++tot]=(ask){n+1,t,0,-0x3f3f3f3f};//边界
    sort(q+1,q+tot+1,cmp);
    memset(dis,233,sizeof(dis));
    dis[1]=0;
    for (int i=1;i<=tot;i++){
        if(q[i].x==n+1)break;//如果已经出界，直接跳出
        if(!q[i].dis)ans[q[i].id]=dis[q[i].x];//dp
        else dis[q[i].x]=max(dis[q[i].x],ans[q[i].id]+q[i].dis);
    }
    return printf("%d",dis[tt]<0?-1:t-dis[tt]),0;//集return和输出+判断于一体
}
```


---

## 作者：lava__44 (赞：6)

### 鸣谢
参照了大佬 [WarningQAQ](https://www.luogu.com.cn/user/269295) 的题解
### 正文

本题关键在于把最坏等待时间转化成中间乘坐公交的最长时间。

即每次乘车都看成 $a_i$ 上车 $b_i$ 开车，$c_i$ 抵达 $d_i$ 下车，等待时间拉满，此时车上时间为 $c_i - b_i$。

建点时存储的几个变量：出发点/到达点，出发/到达最终时间，第 $idx$ 号公交车，$b_{i,dist}$ 为这班车到达此点的乘车耗时。

把边排序的时候使用的排序规则为：

- 最终时间相同时，乘车时间越长排越前面。
- 最终时间不同时，最终时间更长排越后面。

$dist$ 需赋一个负的极小值（e.g：赋 $128\sim255$ 或 $0xcf$ 均可，赋 $128\sim255$ 是因为这些数字的二进制是均为八位且首位是 $1$。使用 `memset` 赋值保证最高位是负，赞美 [@推翻暴政](https://www.luogu.com.cn/user/448555) 大佬，他讲解了此处赋值的规则。）

接下来枚举每个点，若为起点则将对应的 $ans$ 赋为到该点的 $dist$ 值，若为终点，则用该点的 $ans +$ 到该点那班车车上所花的时间值（即 $b_{dist}$）更新该点的 $dist$ 值。
若到达 $p$ 点时 $dist_p$ 值小于零输出 $-1$，若不是则输出 $t - dist_p$。

### 贴码

```c++
#include<bits/stdc++.h>
#define MAXN 500010
using namespace std;
//ifstream is("trip.in",ios::in); 
//ofstream os("trip.out",ios::out);
//#define cin is
//#define cout os
int n,m,p,t,tote,dist[MAXN],ans[MAXN];
struct Bus {
	int x,t,idx,dist;
}b[MAXN];
void build(int x,int t,int idx,int dist){
	b[++tote]={x,t,idx,dist};
}
bool cmp(const Bus &x,const Bus &y){
	return x.t==y.t?x.dist>y.dist:x.t<y.t;
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m>>p>>t;
	for(int i=1,s,t,a,b,c,d;i<=m;i++){
		cin>>s>>t>>a>>b>>c>>d;
		build(s,a,i,0);
		build(t,d,i,c-b);
	}
	build(n+1,t,0,-0x3f3f3f3f);
	sort(b+1,b+tote+1,cmp);
	memset(dist,250,sizeof(dist));
	dist[1]=0;
	for(int i=1;i<=tote;i++){
		if(b[i].x==n+1) break;
		if(!b[i].dist) ans[b[i].idx]=dist[b[i].x];
		else dist[b[i].x]=max(dist[b[i].x],ans[b[i].idx]+b[i].dist);
	}
	(dist[p]<0)?cout<<"-1":cout<<t-dist[p];
	return 0;
}

```
***
*审核大大辛苦了，谢谢审核。*


---

## 作者：wei_xin (赞：5)

* 题意

给定一幅 $N$ 个点的图，图上有 $M$ 辆公交车。

每辆公交车从点 $s[i]$ 到点 $t[i]$ ，始发时间 $\in [a[i],b[i]]$ ，到达时间 $\in [c[i],d[i]]$ ，保证 $a[i] \leqslant b[i] < c[i] \leqslant d[i]$ 。

定义状态为 $(city,time)$ ，求一条路径 $(1,0)\to (P,T)$ ，使得最大等待时间最小，输出该最大等待时间。如果路径不存在，输出$-1$。

公交车的搭乘条件如下: $tnow\leqslant a[i] , city=s[i]$ 。

等待时间 $= T - t'$ ，其中 $t'$ 是在车上的时间。

* 数据范围

$N\leqslant 50000 , M\leqslant 100000 , T\leqslant 1000000000$ 。

* 解析

0.转化题意。

既然是最大等待时间，我们可以直接认为每辆车是在 $a[i]$ 上车后等待到 $b[i]$ 才发车， $c[i]$ 抵达后等到 $d[i]$ 才下车。

1.建图。

朴素做法是把公交车作为点来连边，但是最大边数就会到达 $(\dfrac{M}{2})^2$ 的级别，连边就 T 了。

考虑建立分层图。以时间为层，显然只需要建出"关键时间"对应的点，即 $a[i],b[i],c[i],d[i]$ 对应的点，加上起点和终点的虚点，然后连边就好。

定义边权为该条边增加的等待时间，显然，对于单纯的等待， $e[i].l = t' - t\ $ ；对于公交车，起点为 $(s[i],a[i])$ ，终点为 $(t[i],d[i])$ ， $e[i].l = d[i] - c[i] + b[i] - a[i]$ 。

注意到 $a[i] \leqslant b[i] < c[i] \leqslant d[i]$ ，所以时间严格递增，在分层图意义下不存在环，可以直接拓扑排序 dp 。

2.实现细节。

keytime 的建点需要利用排序和 `unique` ，因为我用的是 `basic_string` 所以还要 `resize` ，否则后面会乱。

等待边可以在建点的过程中进行，记得额外标一下 $str=(1,0)$ 和 $end=(P,T)$ 的编号。 公交车边需要找到对应的点，比较方便的一种实现是利用 `stl` 的 `map` , 结构体 `point` 作 key ，编号作 val 。

拓扑排序的过程中要注意必须按入度来进队，否则的话某些边(譬如说 $1$ 到 $2$ 的最早车在 $5$ ，那么就可以是 $(2,0)\to (2,3)$ 的边)永远拆不掉， dp 会出 bug 。

最短路算法不是不能做，但是不开 O2 的话， T 得很厉害。 Dijk 必 T ， SPFA 把数组开到上限然后加上 LLL 优化勉强能卡过去。

3.标程。

主要是建点连边相关很麻烦。

```cpp
#define b_s basic_string
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define foR(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
//这里本来有一个快读快写，删的理由很简单

const int maxn=5e4+7,maxm=6e5+7,inf=0x3f3f3f3f;
int n,m,P,T,l[maxn],str,tot,ans,in[maxm];
b_s<int> kt[maxn];

struct bus{int s,t,a,b,c,d;}b[maxm];

struct point{
	int c,t;
	point(){}
	point(int _c,int _t){c=_c,t=_t;}
	bool operator<(const point &b) const{
		if(c==b.c) return t<b.t;
		return c<b.c;
	}
}p[maxm];
map<point,int> refl;//映射

struct edge{
	int to,l;
	edge(){}
	edge(int _to,int _l){to=_to,l=_l;}
};
b_s<edge> e[maxm];

void newp(int city,int t){p[++tot]=point(city,t); refl[p[tot]]=tot; return;}

int dis[maxm],q[maxm],hd=1,tl;
void toposort(){
	For(i,1,tot){
		dis[i]=inf;
		if(!in[i]) q[++tl]=i;
	}
	dis[str]=0;
	while(tl>=hd){
		int now=q[hd++];
		for(edge a:e[now]){
			dis[a.to]=min(dis[a.to],dis[now]+a.l);
			if(!(--in[a.to])) q[++tl]=a.to;
		}
	}
	return;
} 

void link(int x,int y,int t){e[x]+=edge(y,t); ++in[y]; return;}

int main(){
	n=rd(),m=rd(),P=rd(),T=rd();
	kt[1]+=0,kt[P]+=T;//直接丢进去这样就可以进行一个自动排序呀
	For(i,1,m){
		b[i].s=rd(),b[i].t=rd(),b[i].a=rd(),b[i].b=rd(),b[i].c=rd(),b[i].d=rd();
		kt[b[i].s]+=b[i].a,kt[b[i].s]+=b[i].b;
		kt[b[i].t]+=b[i].c,kt[b[i].t]+=b[i].d;//首先把所有时间点存下来
	} 
	
	For(i,1,n) sort(kt[i].begin(),kt[i].end()),l[i]=unique(kt[i].begin(),kt[i].end())-kt[i].begin(),kt[i].resize(l[i]);
	
	For(i,1,n)
		for(int j=0;j<l[i];++j){
			newp(i,kt[i][j]);
			if(i==1 && kt[i][j]==0) str=tot;
			if(i==P && kt[i][j]==T) ans=tot;
			if(j>0) link(tot-1,tot,p[tot].t-p[tot-1].t);//建点。对同一城市的点进行基于等待的连边 
		}
	
	For(i,1,m) link(refl[point(b[i].s,b[i].a)],refl[point(b[i].t,b[i].d)],b[i].b-b[i].a+b[i].d-b[i].c);//基于bus的第二种连边
	
	toposort();
	
	wt(dis[ans]==inf?-1:dis[ans]);
	return 0;
}
```

---

## 作者：DrBit (赞：4)

[题面](https://www.luogu.com.cn/problem/P4673)

首先这个人除了在车上的时间外都在等待，所以可以直接计算 $c_i-b_i$（也就是第 $i$ 辆车的贡献）。

把每条线路看成一个点，点权为 $c_i-b_i$，对于每个点 $i$，当且仅当点 $j$ 满足 $s_j=t_i$ 且 $a_j \ge d_i$ 时向 $j$ 连边。

可以看出这是一个 DAG，把满足 $s_i=1$ 的点 $i$ 的 $dis$ 值设成 $0$，跑拓扑排序即可。

边数 $N^2$？

对于每个位置 $p$，将 $s_j=p$ 的点按 $a_j$ 排序，注意到满足连边条件的 $j$ 必然是一段后缀，建立一排虚点辅助连边即可。

tips: 如果目标点是 $1$ 点，那么待在原地不动也是一种可行的决策，要特判一下（对应测试点 2）。（因为这个调了一个下午）

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
#define it vector<node>::iterator
using namespace std;
const int MAXN = 4e5 + 50;
const int INF = 1e13;
#define int long long
struct data
{
    int s, t, a, b, c, d;
} a[MAXN * 2];
struct edge
{
    int nxt, to, val;
} e[MAXN * 2];
struct node
{
    int id, val;
    node(){}
    node(int a, int b)
    {
        id = a;
        val = b;
    }
    bool operator<(const node &tmp) const
    {
        return val < tmp.val;
    }
};
int head[MAXN], edgetot;
int cor[MAXN], dis[MAXN], vis[MAXN], deg[MAXN], invc[MAXN];
vector<node> idx[MAXN];
int N, M, P, T, tot;
queue<int> q;
void add(int x, int y, int v)
{
    e[++edgetot].to = y;
    e[edgetot].nxt = head[x];
    e[edgetot].val = v;
    head[x] = edgetot;
    deg[y]++;
    // cout << x << " " << y << endl;
}
bool cmp1(node x, node y)
{
    return x.val < y.val;
}
void dijkstra()
{
    for (int i = 1; i <= tot; ++i)
        dis[i] = -INF;
    for (int i = M + 1; i <= tot; ++i)
    {
        if (!deg[i])
            q.push(i);
            // cout << i << " ";
        if (a[invc[i]].s == 1)
            dis[i] = 0;
    }
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        for (int i = head[x]; i; i = e[i].nxt)
        {
            int v = e[i].to;
            // cout << x << ":" << v << endl;
            deg[v]--;
            dis[v] = max(dis[v], dis[x] + e[i].val);
            if (!deg[v])
                q.push(v);
        }
    }
    int res = P == 1 ? 0 : -1;
    for (int i = 1; i <= M; ++i)
    {
        if (a[i].t == P && a[i].d <= T)
            res = max(res, dis[i] + a[i].c - a[i].b);
    }
    printf("%lld\n", res == -1 ? -1 : T - res);
}
signed main()
{
    scanf("%lld%lld%lld%lld", &N, &M, &P, &T);
    // cout << T << endl;
    for (int i = 1; i <= M; ++i)
    {
        scanf("%lld%lld%lld%lld%lld%lld", &a[i].s, &a[i].t, &a[i].a, &a[i].b, &a[i].c, &a[i].d);
        // if (a[i].a == a[i].b && a[i].b == a[i].c && a[i].c == a[i].d)
        //     cout << "*" << endl;
        idx[a[i].s].push_back(node(i, a[i].a));
    }
    for (int i = 1; i <= N; ++i)
        sort(idx[i].begin(), idx[i].end(), cmp1);
    tot = M;
    for (int i = 1; i <= N; ++i)
    {
        int sz = idx[i].size();
        for (int j = sz - 1; j >= 0; --j)
        {
            int v = idx[i][j].id;
            // cout << i << ":" << v << "*" << endl;
            cor[v] = ++tot;
            invc[tot] = v;
            add(tot, v, 0);
            if (j < sz - 1)
                add(tot, tot - 1, 0);
        }
    }
    for (int i = 1; i <= M; ++i)
    {
        int tar = lower_bound(idx[a[i].t].begin(), idx[a[i].t].end(), node(i, a[i].d), cmp1) - idx[a[i].t].begin();
        if (tar == idx[a[i].t].size())
            continue;
        int tp = idx[a[i].t][tar].id;
        // cout << i << ":" << tp << endl;
        add(i, cor[tp], a[i].c - a[i].b);
    }
    dijkstra();
    return 0;
}
```


---

## 作者：wizard（偷开O2 (赞：3)

一道拓扑排序的好题。

### 题意

一张图上有许多车辆，我们知道每辆车的起点，终点，出发时间的区间，到达时间的区间，求在 $T$ 时到达 $P$ 点的最小等待时间。

### 分析

等待时间被定义为总时间减去在车上的时间，在等待时间最优的情况下，为了使等待时间尽可能的小，就要最大化在车上的时间。

如果说我们要从 $i$ 点去往 $j$ 点，且车的出发时间为 $[a_{i},b_{i}]$，到达时间为 $[c_{j},d_{j}]$，如果我们要最大化在车上的时间的话，当且仅当我们于 $b_{i}$ 出发，在 $c_{j}$ 点到达，且在车上的时间为 $d_{j}-a_{i}$。

也就是说我们可以理解为在 $a_{i}$ 时上车，$b_{i}$ 时发车，$c_{j}$ 时就到达，但是在 $d_{j}$ 时才下车，开始等待。

利用朴素建图时间不是很优，所以在建图情况成立的情况下，当且仅当 $i$ 的到达点是 $j$ 的出发点，而且到达时间点在出发时间点后。

形式化就是：$s_{j}=t_{i}$，$c_{j} \ge b_{i}$ 时建图。

贪心地对每个车排序，因为我们的目的是最大化在车上的时间，所以当两个车的到达时间相同时，乘车时间长的一个车更优秀。当到达时间不同时，到达时间短的车就更优秀。

将在车上的时间也就是 $c_{j}-b_{i}$ 化为点来建图，扫一遍整个新图，统计答案即可。

### 代码

```cpp
//拓扑排序 
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+10;
int n,m,p,t;
struct edge{
	int now,time,id,dis;
}e[maxn];
int dex,dis[maxn];
int ans[maxn];
void add(int a,int b,int c,int d){
	e[++dex]={a,b,c,d};
}
bool cmp(edge a,edge b){
	if(a.time==b.time){
		return a.dis>b.dis;
	}
	return a.time<b.time;
}
void topo(){
	sort(e+1,e+dex+1,cmp);
	memset(dis,128,sizeof(dis));
	dis[1]=0;
	for(int i=1;i<=dex;i++){
		if(e[i].now==n+1)break;
		if(!e[i].dis)ans[e[i].id]=dis[e[i].now];
		else if(dis[e[i].now]<ans[e[i].id]+e[i].dis){
			dis[e[i].now]=ans[e[i].id]+e[i].dis;
		}
	}
	if(dis[p]<0)cout << -1 << endl;
	else cout << t-dis[p] << endl;
}
signed main(){
	cin >> n >> m >> p >> t; 
	for(int i=1;i<=m;i++){
		int s,t,a,b,c,d;
		cin >> s >> t >> a >> b >> c >> d;
		add(s,a,i,0);
		add(t,d,i,c-b); //从a点上车,d点下车，达到等待时间最小化 
	}
	add(n+1,t,0,-0x3f3f3f3f);
	topo(); 
	return 0;
}
```

---

## 作者：Cells (赞：1)

#### 写在前面

首先建议管理大大改一改题面，题意有点不清楚。

#### 题意

给定一张图，需要在 $T$ 分钟（包含）之内从 $1$ 号点走到 $P$ 号点。共有 $M$ 条线路，每条边从 $s_i$ 点到 $t_i$ 点，必须在 $a_i$ 及之前到达 $s_i$ 点才能经过该边，并在 $d_i$ 时到达 $t_i$ 点。其中等待时间为 $(b_i-a_i)+(d_i-c_i)$，即只有 $c_i-b_i$ 的乘坐时间。求最短等待时间。

#### 思路

最小化等待时间，因为总时间 $T$ 不变，那么就最大化乘坐的时间。我们发现需要先将到达时间小的路线处理完成后才能处理后面的路线，注意到上述的处理过程有一定优先级，所以我们考虑跑拓扑，将一条边拆成起点和终点，存储到达该点时间（$a_i$ 或者是 $d_i$），当到达时间相同时，乘坐时间更大能贡献更大的答案，所以我们按照到达时间为第一关键字，乘坐时间为第二关键字进行排序。当然起点没有乘坐时间。

但发现某点为一条路线起点时，说明时间早于该点的路线全部跑完，那么此时**这条边**的最大乘坐时间即为**起点**的最大乘坐时间，我们记录下来。当点为终点时，如果这条边的边权加上**该边**的最大乘坐时间能够更新起点的时间，就更新。另外，因为有 $T$ 的时间限制，当我们发现该点到达时间已经大于 $T$ 时，可以提前结束。

#### 万事俱备，只欠代码

```c++
# include <bits/stdc++.h>
# define mem(a, b) memset(a, b, sizeof(a))
# define rep(i, a, b) for(int i = (a); i <= (b); ++ i)
# define pre(i, a, b) for(int i = (a); i >= (b); -- i)
using namespace std;

using LL = long long;

const int N = 5e4 + 10, M = 1e5 + 10;

int n, m, p, T, idx;
int dp[N], ans[M];

struct edge{
	int u, w, t, id;
}e[M << 1];

bool cmp(edge a, edge b){
	return a.t == b.t ? a.w > b.w : a.t < b.t;//按到达时间和边权 
}

void topo(){
	mem(dp, -0x3f);//极小值 
	dp[1] = 0;
	
	rep(i, 1, idx){
		if(e[i].t > T) break;//超时了 
		if(!e[i].w) ans[e[i].id] = dp[e[i].u];//这个点是起点，那么这条边的最大坐车时间已经确定，即为起点的乘车时间dp[e[i].u] 
		else if(dp[e[i].u] < ans[e[i].id] + e[i].w) dp[e[i].u] = ans[e[i].id] + e[i].w;//这个点能够被更新 
	}
	
	if(dp[p] < 0) cout << "-1";//到不了 
	else cout << T - dp[p];//总时间来减 
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> n >> m >> p >> T;
	rep(i, 1, m){
		int s, t, a, b, c, d;
		cin >> s >> t >> a >> b >> c >> d;
		e[++ idx] = {s, 0, a, i};//需要记录点，边权，到达时间，所属边的编号 
		e[++ idx] = {t, c - b, d, i};
	}
	
	sort(e + 1, e + 1 + idx, cmp);
	
	topo();
	
	return 0;
}
```
**完结撒花！！！**

---

## 作者：船酱魔王 (赞：0)

# P4673 [BalticOI 2005] Bus Trip 题解

## 题意转化

给定一张 $ n $ 点有向图。

对于一条有向边，需要在特定时间到达起点，可以传送到终点，传送时间也给定。你可以获得一个『愉悦值』。

你需要到达终点，求出最大愉悦值。

## 分析

因为我们发现边的时间有明确顺序，将边拆分成两个转移状态。

* 记录边的起点、起点有效时间。

* 记录边的终点、终点有效时间、边号。

将状态按照时间从小到大排序。

我们维护数组表示当前状态下，每个点和每条边的愉悦值最大值。

对于起点状态，我们在这条边的愉悦值数组上打个『标记』，表示这条边走入时的最大愉悦值，显然等于这个起点当前愉悦值。

对于终点状态，我们在这个终点的愉悦值数组上进行修改，可以从走入的最大愉悦值加上边权更新而来。

注意排序时的细节处理，注意判断到达终点时总时间是否 $ \le T $。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 5e4 + 5;
const int M = 1e5 + 5;
int n, m, p, t;
struct bus {
    int tp;//1-come 2-end
    int fm;//id
    int pos;//position(which point?)
    int ti;//time to come
    int wt;//time on bus(weight)
} arr[M * 2];
bool operator<(bus p1, bus p2) {
    if(p1.ti != p2.ti) {
        return p1.ti < p2.ti;
    }
    if(p1.tp != p2.tp) {
        return p1.tp > p2.tp;
    }
    return p1.fm < p2.fm;
}
int dp[N];
int fp[M];
int ct = 0;
bus arrange(int tx, int ps, int fm, int ti, int wt) {
    bus qwq;
    qwq.tp = tx;
    qwq.pos = ps;
    qwq.ti = ti;
    qwq.wt = wt;
    qwq.fm = fm;
    return qwq;
}
int main() {
    scanf("%d%d%d%d", &n, &m, &p, &t);
    for(int i = 1; i <= n; i++) dp[i] = -1e9 - 5;
    for(int i = 1; i <= m; i++) fp[i] = -1e9 - 5;
    dp[1] = 0;
    int u, v, a, b, c, d;
    for(int i = 1; i <= m; i++) {
        scanf("%d%d%d%d%d%d", &u, &v, &a, &b, &c, &d);
        ct++;
        arr[ct] = arrange(1, u, i, a, 0);
        ct++;
        arr[ct] = arrange(2, v, i, d, c - b);
    }
    sort(arr + 1, arr + 2 * m + 1);
    int ans = -1;
    for(int i = 1; i <= 2 * m; i++) {
        if(arr[i].ti > t) {
            break;
        }
        if(arr[i].tp == 1) {
            fp[arr[i].fm] = dp[arr[i].pos];
        } else {
            dp[arr[i].pos] = max(dp[arr[i].pos], fp[arr[i].fm] + arr[i].wt);
        }
        if(arr[i].tp == 2 && arr[i].pos == p) {
            ans = max(ans, dp[arr[i].pos]);
        }
    }
    if(ans < 0) {
        printf("-1\n");
        return 0;
    }
    printf("%d\n", t - ans);
    return 0;
}

```

---

## 作者：lyhqwq (赞：0)

# Solution
注意到题目中有一句话

> 当计算等待时间时，我们必须假设最早可能到达的时间和最晚可能出发的时间。

所以我们可以把每辆公交车看作 $[a_i,b_i]$ 和 $[c_i,d_i]$ 在等待。

对于朴素的做法，我们可以把每辆公交车看作点进行连边。但这样边数是 $O(M^2)$ 的，显然无法通过，我们考虑对连边进行优化。

因为下车的巴士的最晚到达时间不会迟于他需要搭乘的下一辆巴士的最早出发时间，所以如果第 $i$ 个点和第 $j$ 个点可以连边的充要条件为 $t_i=s_j$ 且 $d_i \le a_j $。

所以我们可以开 $n$ 个 vector，第 $x$ 个 vector 存储 $s_i=x$ 的所有点，每个 vector 内按照 $a_i$ 升序进行排序。对于一个点，可以连的边一定是在一个 vector 内，且一定是一段后缀。我们考虑对每个点建一个虚点，每个虚点向比它的 $a_i$ 大的第一个点的虚点连**单向边**，每次连边时只需要二分后向对应的虚点连边即可。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=300005;
struct edge{
	int v;
	int nxt;
	int w;
}edge[N<<1];
int head[N],cnt;
struct T{
	int s,t,a,b,c,d;
}e[N];
struct node{
	int id,val;
};
bool cmp(node x,node y){
	return x.val<y.val;
}
int n,m,T,P,tot;
int I[N],R[N]; 
int deg[N],dis[N];
vector<node> vec[N];
void addedge(int u,int v,int w){
	edge[++cnt].v=v,edge[cnt].w=w,edge[cnt].nxt=head[u],head[u]=cnt;
	deg[v]++;
}
void topo(){
	queue<int> q;
	memset(dis,-0x3f,sizeof(dis));
	for(int i=m+1;i<=tot;i++){
		if(!deg[i]) q.push(i);
		if(e[R[i]].s==1) dis[i]=0;
	}
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=edge[i].nxt){
			int v=edge[i].v,w=edge[i].w;
			deg[v]--;
			dis[v]=max(dis[v],dis[u]+w);
			if(!deg[v]) q.push(v);
		}
	}
	int ans=(P==1?0:-1);
	for(int i=1;i<=m;i++){
		if(e[i].t==P&&e[i].d<=T) ans=max(ans,dis[i]+e[i].c-e[i].b);
	}
	printf("%lld\n",(ans==-1?-1:T-ans));
}
signed main(){
	scanf("%lld%lld%lld%lld",&n,&m,&P,&T);
    if(T==0&&P==1){
        printf("%d\n",0);
        return 0;
    }
	for(int i=1;i<=m;i++){
		scanf("%lld%lld%lld%lld%lld%lld",&e[i].s,&e[i].t,&e[i].a,&e[i].b,&e[i].c,&e[i].d);
		vec[e[i].s].push_back((node){i,e[i].a});
	}
	
	for(int i=1;i<=n;i++) sort(vec[i].begin(),vec[i].end(),cmp);
	tot=m;
	
	for(int i=1;i<=n;i++){
		for(int j=vec[i].size()-1;j>=0;j--){
			I[vec[i][j].id]=++tot;
			R[tot]=vec[i][j].id;
			addedge(tot,vec[i][j].id,0);
			if(j!=vec[i].size()-1) addedge(tot,tot-1,0);
		}
	}
	for(int i=1;i<=m;i++){
		int t=lower_bound(vec[e[i].t].begin(),vec[e[i].t].end(),(node){i,e[i].d},cmp)-vec[e[i].t].begin();
		if(t==vec[e[i].t].size()) continue;
		addedge(i,I[vec[e[i].t][t].id],e[i].c-e[i].b);
	}
	
	topo(); 
	return 0;
}

```


---

