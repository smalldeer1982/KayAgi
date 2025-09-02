# Rendez-vous de Marian et Robin

## 题目描述

In the humble act of meeting, joy doth unfold like a flower in bloom.



Absence makes the heart grow fonder. Marian sold her last ware at the Market at the same time Robin finished training at the Major Oak. They couldn't wait to meet, so they both start without delay.

The travel network is represented as $ n $ vertices numbered from $ 1 $ to $ n $ and $ m $ edges. The $ i $ -th edge connects vertices $ u_i $ and $ v_i $ , and takes $ w_i $ seconds to travel (all $ w_i $ are even). Marian starts at vertex $ 1 $ (Market) and Robin starts at vertex $ n $ (Major Oak).

In addition, $ h $ of the $ n $ vertices each has a single horse available. Both Marian and Robin are capable riders, and could mount horses in no time (i.e. in $ 0 $ seconds). Travel times are halved when riding. Once mounted, a horse lasts the remainder of the travel. Meeting must take place on a vertex (i.e. not on an edge). Either could choose to wait on any vertex.

Output the earliest time Robin and Marian can meet. If vertices $ 1 $ and $ n $ are disconnected, output $ -1 $ as the meeting is cancelled.

## 说明/提示

In the first test case, Marian rides from vertex $ 1 $ to vertex $ 2 $ , Robin waits.

In the second test case, vertices $ 1 $ and $ 3 $ are not connected.

In the third test case, both Marian and Robin travel to vertex $ 2 $ to meet.

In the fourth test case, Marian travels to vertex $ 2 $ without a horse, mounts the horse at vertex $ 2 $ and rides to vertex $ 3 $ to meet Robin.

In the fifth test case, Marian travels to vertex $ 2 $ without a horse, mounts the horse at vertex $ 2 $ and rides back to vertex $ 1 $ and then to vertex $ 3 $ . Robin waits.

## 样例 #1

### 输入

```
6
2 1 1
1
1 2 10
3 1 2
2 3
1 2 10
3 3 1
2
1 2 4
1 3 10
2 3 6
4 3 2
2 3
1 2 10
2 3 18
3 4 16
3 2 1
2
1 2 4
1 3 16
7 7 1
3
1 5 2
2 6 12
1 2 12
6 4 8
7 3 4
6 3 4
7 6 4```

### 输出

```
5
-1
6
19
14
12```

# 题解

## 作者：thh_loser (赞：3)

# CF2014E Rendez-vous de Marian et Robin题解

[题目链接](https://www.luogu.com.cn/problem/CF2014E)

## 题意

给定一个 $n$ 个点的图，其中 $h$ 个点有马，到达该点后在后面经过的的每一条边时间变成一半。现在给定两个人从两个点出发，求两个人在某一点相遇的最小时间（两个人都可以在某一时间停下来）。

## 思路

由于并没有要求同时到达，这就是一道比较简单的分层图，定义第一层为原本的图，第二层为骑上马后边权变为原图一半的图，然后我们可以对于每一个有马的点建一条到达第二层，边权为 $0$ 的边，最后对于两个人的起点分别跑一次 dijkstra，答案即为所有点两个点的距离之和的最小值。

## code

```c++
#include<bits/stdc++.h>
#define N 200010
#define ll long long
using namespace std;
int t;
int n,m,h;
int fir[N*5],ne[N*5],to[N*5],w[N*5],tot;
ll d[N<<1],d2[N<<1];
bool vis[N];
void add(int x,int y,int z){
	ne[++tot]=fir[x];
	fir[x]=tot;
	to[tot]=y;
	w[tot]=z;
}
void dij(int s){
	for(int i=1;i<=n*2;i++){
		d[i]=1e13;
		vis[i]=0;
	}
	priority_queue<pair<int,int> >q;
	d[s]=0;
	q.push(make_pair(0,s));
	while(!q.empty()){//dijkstra模板 
		int x=q.top().second;
		q.pop();
		if(vis[x])continue;
		vis[x]=1;
		for(int i=fir[x];i;i=ne[i]){
			int e=to[i];
			if(d[e]>d[x]+w[i]){
				d[e]=d[x]+w[i];
				if(!vis[e])q.push(make_pair(-d[e],e));
			}
		}
	}	
}
int main(){
	cin>>t;
	while(t--){
		scanf("%d%d%d",&n,&m,&h);
		for(int i=1,x;i<=h;i++){
			scanf("%d",&x);
			add(x,x+n,0);//可以通向下一层 
		}
		for(int i=1,u,v,z;i<=m;i++){
			scanf("%d%d%d",&u,&v,&z);
			add(u,v,z);
			add(v,u,z);
			add(u+n,v+n,z/2);
			add(v+n,u+n,z/2);//下面一层代价变为一半 
		}
		dij(1);
		for(int i=1;i<=n*2;i++)d2[i]=d[i];
		dij(n);
		ll mn=1e13;
		for(int i=1;i<=n;i++){
			mn=min(mn,max(min(d[i],d[i+n]),min(d2[i],d2[i+n])));//在每一个点中取最小值 
		}
		cout<<(mn>=1e13?-1:mn)<<"\n";
		for(int i=1;i<=n*2;i++)fir[i]=0;//多测记得初始化 
		tot=0;
	}
	return 0;
}

```

---

## 作者：damnM3bro (赞：2)

本题中，走一条边有两种状态，可以考虑分层图最短路。\
由于边权只有原值和减半值两种情况，因此建两层图。

第一层原图，第二层边权减半。第一层点编号为 $1\sim n$，第二层为 $n+1\sim 2n$。

对于每个 $i(i\in[1,n])$，建边 $i\rightarrow i+n$，边权为 $0$。

分别以 $1,n$ 为起点跑 dijkstra，枚举相遇点即可得到答案。

---

## 作者：WRT_Partisan (赞：1)

# 题解：CF2014E Rendez-vous de Marian et Robin

[题目链接](https://www.luogu.com.cn/problem/CF2014E)

## 题目大意

有一个 $n$ 个节点的有边权无向图，两个人分别在点 $1$ 和点 $n$。图中有 $h$ 个点有马，到达有马的点后，以后经过每一条边都只花费原来边权一半的时间。求两个人在某一点相遇的最小时间（人可以停下等待）。

## 解题思路

可以使用分层图。

第一层图是原图，第二层图是边权减半后的图。对于每个有马的点，将两层图的节点连接起来，边权为 $0$。

然后分别从点 $1$ 和点 $n$ 跑 dijkstra（边权非负，可使用堆优化），再算出在每个点相遇所用的时间，求一个最小值即为答案。

## 代码

因为有多组测试数据，注意数组、图和优先队列的清空。

```cpp
/*
 * @FilePath: \c++\CF2014E.cpp
 * @Author: WRT_Partisan
 * @Date: 2024-11-23 12:23:29
 */
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef unsigned long long ull;
constexpr int INF = 1000000000000;
struct Node
{
    int x, k;
};
struct Node2
{
    int dis, x;
    bool operator<(const Node2 &a) const
    {
        return this->dis > a.dis;
    }
};
int t, n, m, h, a[200005], dis1[400005], disn[400005], u, v, w, ans;
bool book[400005];
vector<Node> mp[400005];
priority_queue<Node2> q;
signed main()
{
    scanf("%lld", &t);
    while (t--)
    {
        ans = INF;
        for (int i = 1; i <= 100000; i++)
            mp[i].clear();
        scanf("%lld%lld%lld", &n, &m, &h);
        for (int i = 1; i <= h; i++)
        {
            scanf("%lld", &a[i]);
            mp[a[i]].push_back({a[i] + n, 0});
        }
        for (int i = 1; i <= m; i++)
        {
            scanf("%lld%lld%lld", &u, &v, &w);
            mp[u].push_back({v, w});
            mp[v].push_back({u, w});
            mp[u + n].push_back({v + n, w / 2});
            mp[v + n].push_back({u + n, w / 2});
        }
        for (int i = 1; i <= n * 2; i++)
            dis1[i] = disn[i] = INF;
        memset(book, 0, sizeof(book));
        dis1[1] = 0;
        q.push({dis1[1], 1});
        while (!q.empty())
        {
            int t = q.top().x;
            q.pop();
            if (book[t])
                continue;
            book[t] = 1;
            for (auto &i : mp[t])
            {
                if (book[i.x] == 0 && dis1[t] + i.k < dis1[i.x])
                {
                    dis1[i.x] = dis1[t] + i.k;
                    q.push({dis1[i.x], i.x});
                }
            }
        }
        memset(book, 0, sizeof(book));
        disn[n] = 0;
        q.push({disn[n], n});
        while (!q.empty())
        {
            int t = q.top().x;
            q.pop();
            if (book[t])
                continue;
            book[t] = 1;
            for (auto &i : mp[t])
            {
                if (book[i.x] == 0 && disn[t] + i.k < disn[i.x])
                {
                    disn[i.x] = disn[t] + i.k;
                    q.push({disn[i.x], i.x});
                }
            }
        }
        for (int i = 1; i <= n; i++)
        {
            if (dis1[i] == INF || disn[i] == INF)
                continue;
            ans = min(ans, max(min(dis1[i], dis1[i + n]), min(disn[i], disn[i + n])));
        }
        printf("%lld\n", ans >= INF ? -1 : ans);
    }
    return 0;
}
```

---

## 作者：zengziqvan (赞：1)

### 前言

好难受，赛时 $\operatorname{long\;long}$ 没开全导致赛后被 hack。

### 形式化题意

给定一张 $n$ 个点、$m$ 条边的无向图，第 $i$ 条边长 $w_i$ 个单位长度。其中有 $k$ 个点，如果走上去，以后走的路长度变为原来的一半，但总体只能减少一次。

两个人分别在 $1$、$n$ 两个点上，两个人同时出发，每一秒走一个单位长度，问两人走到同一个点上至少要多少秒。

如果无法到同一个点上输出 `-1`。

### 题目分析

考虑分层图。

分层图指的是建多层图，每层图都有实际的意义，每层之间用题目给的条件建若干特殊边连接。

对于这道题建两层图：第一层为原图，第二层为边权 $\div 2$ 的图。

考虑如何才能从第一层跑到第二层：发现跑的路程减半当且仅当走到 $k$ 个点之一。

所以在两个图的 $k$ 个对应点之间互相连边。

减半的代价显然为 $0$，故这些边的边权为 $0$。

从第一层的 $1$ 点和 $n$ 点分别跑最短路并记录它们到各个点之间的距离。

枚举所有点 $i$，在点 $i$ 相遇的最优时间显然是两个人到 $i$ 所用时间的较大值。

时间复杂度 $\operatorname{O}(n\log n)$。

### 代码

```c++
const int N=4e5+10;
int t,n,m,h,vis[N],vis2[N];
LL dis[N],dis2[N];
vector<pair<int,int>>e[N];
void Dijkstra1() {
	FOR(i,1,n<<1) dis[i]=1e18,vis[i]=0;
	dis[1]=0;
	priority_queue<pair<int,int>>q;
	q.push({0,1});
	while(q.size()) {
		int x=q.top().se;q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		for(pair<int,int>o:e[x]) {
			int y=o.fr,z=o.se;
			if(dis[y]>dis[x]+z) {
				dis[y]=dis[x]+z;
				q.push({-dis[y],y});
			}
		}
	}
}
void Dijkstra2() {
	FOR(i,1,n<<1) dis2[i]=1e18,vis2[i]=0;
	dis2[n]=0;
	priority_queue<pair<int,int>>q;
	q.push({0,n});
	while(q.size()) {
		int x=q.top().se;q.pop();
		if(vis2[x]) continue;
		vis2[x]=1;
		for(pair<int,int>o:e[x]) {
			int y=o.fr,z=o.se;
			if(dis2[y]>dis2[x]+z) {
				dis2[y]=dis2[x]+z;
				q.push({-dis2[y],y});
			}
		}
	}
}
void solve() {
	cin>>n>>m>>h;
	FOR(i,1,h) {
		int x=read();
		e[x].pb({n+x,0});
		e[n+x].pb({x,0});
	}
	FOR(i,1,m) {
		int u=read(),v=read(),w=read();
		e[u].pb({v,w});
		e[v].pb({u,w});
		e[u+n].pb({v+n,w/2});
		e[v+n].pb({u+n,w/2});
	}
	Dijkstra1();
	Dijkstra2();
	LL ans=1e18;
	FOR(i,1,n) {
		cmin(ans,max(dis[i],dis2[i]));
		cmin(ans,max(dis[i+n],dis2[i]));
		cmin(ans,max(dis[i],dis2[i+n]));
		cmin(ans,max(dis[i+n],dis2[i+n]));
	}
	if(ans==1e18) puts("-1");
	else cout<<ans<<"\n";
	FOR(i,1,n<<1) e[i].clear();
}
main() {
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

最短路（分层图/拆点？）。

把每个点分为是否已经有马两个状态，从 $1$ 和 $n$ 两点分别跑 dijkstra 即可。最后统计答案为枚举两人最终相遇的节点把四种情况取最大值的最小值。

# Code

```cpp
#include<bits/stdc++.h>
std::vector<std::pair<int,int> >v[200005];
long long dis[2][200005][2];
bool vis[2][200005][2];
bool sig[200005];
int n;
inline void dijkstra(int T){
	for(int i=1;i<=n;++i)
		dis[T][i][0]=dis[T][i][1]=0x3f3f3f3f3f3f3f3f,
		vis[T][i][0]=vis[T][i][1]=false;
	std::priority_queue<std::tuple<long long,int,int> >q;
	dis[T][T?n:1][sig[T?n:1]]=0;
	q.emplace(0,T?n:1,sig[T?n:1]);
	while(!q.empty()){
		int t1=std::get<1>(q.top()),tp=std::get<2>(q.top());q.pop();
		if(vis[T][t1][tp])continue;
		vis[T][t1][tp]=true;
		for(const auto&i:v[t1])
			if(dis[T][i.first][tp|(sig[i.first])]>dis[T][t1][tp]+(tp?i.second>>1:i.second))
				q.emplace(-(dis[T][i.first][tp|(sig[i.first])]=dis[T][t1][tp]+(tp?i.second>>1:i.second)),i.first,tp|(sig[i.first]));
	}
}
int T,m,q;
long long ans;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&n,&m,&q);
		for(int i=1;i<=n;++i)
			v[i].clear(),sig[i]=false;
		for(int x;q--;)
			scanf("%d",&x),sig[x]=true;
		for(int x,y,z;m--;)
			scanf("%d%d%d",&x,&y,&z),
			v[x].emplace_back(y,z),v[y].emplace_back(x,z);
		dijkstra(0);dijkstra(1);
		ans=0x3f3f3f3f3f3f3f3f;
		for(int i=1;i<=n;++i)
			ans=std::min(ans,std::max(std::min(dis[0][i][0],dis[0][i][1]),std::min(dis[1][i][0],dis[1][i][1])));
		if(ans==0x3f3f3f3f3f3f3f3f)ans=-1;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：cxoi1711 (赞：0)

## 题目传送门：[Rendez-vous de Marian et Robin](https://www.luogu.com.cn/problem/CF2014E)
## 思路：
这题是一道有点水的分层图，我们要从起点和终点为开始各自跑一遍 Dijkstra 算法，将图上每一个点拆成两个点，分别为已经有马和还未有马，答案即为所有点两个点的距离之和的最小值。有一点类似于模版题，只要将最短路算法套进去，改一些东西就行了。
## AC Code:
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t,n,m,h;int fir[1000050],ne[1000050],to[1000050],w[1000050],ck;
ll d[400040],d2[400040];bool used[200020];
void acwing(int x,int y,int z){
 ne[++ck]=fir[x];fir[x]=ck; to[ck]=y; w[ck]=z;
}
void dijkstra(int s){
 for(int i=1;i<=n*2;i++)
 {
   d[i]=10000000000000; used[i]=0; 
 }
 priority_queue<pair < int, int > > q ; d[s]=0;q.push (make_pair (0 , s ) ) ;
 while (!q.empty())
 {
  int x= q.top().second;q.pop();if(used[x]==1) continue;used[x]=1;
  for(int i=fir[x];i;i=ne[i])
  {
   int e=to[i];
   if(d[e] > d[x] + w[i]  )
   {
    d[e]=d[x]+w[i];
    if(!used[e])q.push(make_pair(-d[e],e));
   }
  }
 } 
}
signed main(){
 cin>>t;
 while(t--)
 {
  cin>>n>>m>>h;
  for(int i=1;i<=h;i++)
  {
   int x;cin>>x; acwing(x,x+n,0);
  }
  for(int i=1;i<=m;i++)
  { 
   int u,v,z;cin>>u>>v>>z;
   acwing(u,v,z);acwing(v,u,z);
   acwing(u+n,v+n,z/2);acwing(v+n,u+n,z/2);
  }
  dijkstra(1); 
  for(int i=1;i<=n*2;i++)d2[i]=d[i]; 
  dijkstra(n); ll mn=10000000000000;
  for(int i=1;i<=n;i++)
  {
   ll ii=min(d[i],d[i+n]);
   ll iii=min(d2[i],d2[i+n]);
   mn=min(mn,max(ii,iii));
  }
  if(mn>=10000000000000)cout<<"-1\n";else cout<<mn<<endl;
  for(int i=1;i<=n*2;i++)fir[i]=0;ck=0;
 }
}
``````

---

## 作者：SuyctidohanQ (赞：0)

### 题目分析

可以使用分层图。

定义第一层为原本的图，第二层为骑上马后边权变为原图一半的图。我们可以对于每一个有马的点建一条到达第二层并且边权为 $0$ 的边。

然后分别从点 $1$ 和 $n$ 跑 dijkstra，算出在每个点相遇所用的时间，求一个最小值即为答案。

### 代码实现

```cpp
#include <bits/stdc++.h>
#define ll long long 
using namespace std;
void read ();
const ll INF = 1000000000000, MAXN = 4e5 + 10;
struct node {
    ll x, k;
};
struct node2 {
    ll dis, x;
    bool operator < (const node2 &a) const {
        return this -> dis > a.dis;
    }
};
ll T, n, m, h, a[MAXN], dis1[MAXN], disn[MAXN], u, v, w, ans = INF;
bool book[MAXN];
vector <node> vec[MAXN];
priority_queue <node2> q;
void read () {
    ans = INF;
    for (ll i = 1; i <= 1e5; i ++) vec[i].clear ();
    cin >> n >> m >> h;
    for (ll i = 1; i <= h; i ++) {
        cin >> a[i];
        vec[a[i]].push_back ({a[i] + n, 0});
    }
    for (ll i = 1; i <= m; i ++) {
        cin >> u >> v >> w;
        vec[u].push_back ({v, w}); vec[v].push_back ({u, w}); vec[u + n].push_back ({v + n, w / 2}); vec[v + n].push_back ({u + n, w / 2});
    }
    for (ll i = 1; i <= n * 2; i ++) dis1[i] = disn[i] = INF;
    memset (book, false, sizeof (book));
    dis1[1] = 0;
    q.push ({dis1[1], 1});
    while (!q.empty ()) {
        int topp = q.top().x;
        q.pop();
        if (book[topp]) continue;
        book[topp] = true;
        for (auto &i : vec[topp]) {
            if (book[i.x] == false && dis1[topp] + i.k < dis1[i.x]) {
                dis1[i.x] = dis1[topp] + i.k;
                q.push ({dis1[i.x], i.x});
            }
        }
    }
    memset (book, false, sizeof (book));
    disn[n] = 0;
    q.push ({disn[n], n});
    while (!q.empty ()) {
        int topp = q.top ().x;
        q.pop ();
        if (book[topp]) continue;
        book[topp] = true;
        for (auto &i : vec[topp]) {
            if (book[i.x] == false && disn[topp] + i.k < disn[i.x]) {
                disn[i.x] = disn[topp] + i.k;
                q.push({disn[i.x], i.x});
            }
        }
    }
    for (ll i = 1; i <= n; i ++) {
        if (dis1[i] == INF || disn[i] == INF) continue;
        ans = min (ans, max (min (dis1[i], dis1[i + n]), min (disn[i], disn[i + n])));
    }
    cout << (ans >= INF ? -1 : ans) << endl;	
}
int main () {
	cin >> T;
    while (T --) read ();
    return 0;
}
```

---

## 作者：sad_lin (赞：0)

本题特殊在骑上马后全部的边权减半，我们就可以**分层图**做。

连边时在第一层连一条原权值的边，在第二层连一条权值减半的边，如果这个点有马，第一层向第二层连一条权值为 $0$ 的边，然后我们分别从 $1$ 号点和 $n$ 号点跑 dijkstra。

枚举相遇的点，他们可能在第一层或第二层相遇，取最小值即可 $\max\{{\min{\{ dis1_i,dis1_{i+n}\}},\min{\{ dis2_i,dis2_{i+n}\}}\}}$。

**注意：关于 SPFA，他死了。**

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register 
const int N=1e6+10;
const int mod=998244353;
using namespace std;

int n,m,h;

struct ss{
	int v,w,next;
}a[N];
int head[N];
int cnt=1;
void add(int u,int v,int w){
	a[++cnt].v=v;
	a[cnt].w=w;
	a[cnt].next=head[u];
	head[u]=cnt;
}

int dis1[N],dis2[N];
int vis[N];

struct sa{
	int dis,id;
};

bool operator < (const sa &g,const sa &h){
	return g.dis>h.dis;
}

void spfa(int *dis,int k){
	priority_queue<sa> q;
	
	for(re int i=1;i<=2*n;i++){
		dis[i]=1e18;
		vis[i]=0; 
	} 
	dis[k]=0;
	q.push({0,k});
	while(!q.empty()){
		int x=q.top().id;
		q.pop();
		if(vis[x]){
			continue;
		}
		vis[x]=1;
		for(re int i=head[x];i;i=a[i].next){
			int y=a[i].v,w=a[i].w;
			if(dis[y]>dis[x]+w){
				dis[y]=dis[x]+w;
				q.push({dis[y],y});
			}
		}
	}
}

void solve(){
	cin>>n>>m>>h;
	
	for(re int i=1;i<=h;i++){
		int x;
		cin>>x;
		add(x,x+n,0);
	}
	
	for(re int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w);
		add(u+n,v+n,w/2);
		add(v+n,u+n,w/2);
	}
	
	spfa(dis1,1);
	spfa(dis2,n);
	
	int ans=1e18;
	
	for(re int i=1;i<=n;i++){	
		ans=min(ans,max(min(dis1[i],dis1[i+n]),min(dis2[i],dis2[i+n])));
	}
	if(ans>=1e18){
		ans=-1;
	}
	cout<<ans<<"\n";
	for(re int i=1;i<=cnt;i++){
		a[i].next=a[i].v=a[i].w=0;
	}
	for(re int i=1;i<=2*n;i++){
		head[i]=0;
	} 
	cnt=1;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 
	int t;
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：Hide_In_The_Shadow (赞：0)

双源分层图最短路。不了解分层图的可以先尝试 [P4568 ](https://www.luogu.com.cn/problem/P4568)。

将图分为 M 和 R 分别无马和有马总共四层图，对有马点打上标记，然后跑 dj 即可。

最后对两人能跑到的同一点的最小时间取最大值，再在所有点中取最小值即为答案。

复杂度 $O(m\log m)$。

```c++
#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define fio std::ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
using namespace std;
template<typename T>inline void read(T &x){
	x=0;
	char c=getchar();
	T ret=0;
	while(!isdigit(c))ret|=!(c^'-'),c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
	if(ret)x=(~x)+1;
	return;
}
template<typename T>inline void print(T x){
	if(x<0)putchar('-'),x=(~x)+1;
	if(x>9)print(x/10);
	putchar((x-x/10*10)^48);
	return;
}
template<typename T>inline void wr1(T x){
	print(x);
	putchar(' ');
	return;
}
template<typename T>inline void wr2(T x){
	print(x);
	putchar('\n');
	return;
}
int t,n,m,h,tot,head[214514];
struct  edg
{
    int v,nex;
    ll w;
}e[214514<<1];
void add(int u,int v,ll w){
    e[++tot].v=v;
    e[tot].w=w;
    e[tot].nex=head[u];
    head[u]=tot;
}
bool a[214514],vis[214514][2][2];
ll dis[214514][2][2],ans;
void dj(){
    dis[1][0][a[1]]=0;
    dis[n][1][a[n]]=0;
    priority_queue<pair<ll,pair<int,pii>>>q;
    q.push({0,{1,{0,a[1]}}});
    q.push({0,{n,{1,a[n]}}});
    while(!q.empty()){
        int x=q.top().second.first,tp=q.top().second.second.first,hr=q.top().second.second.second;//x：当前节点，tp：当前人，hr：有没有马
        q.pop();
        if(vis[x][tp][hr])continue;
        vis[x][tp][hr]=1;
        for(int i=head[x];i;i=e[i].nex){
            int v=e[i].v;
            ll w=e[i].w;
            if(hr)w>>=1;
            if(dis[v][tp][hr|a[v]]>dis[x][tp][hr]+w){
                dis[v][tp][hr|a[v]]=dis[x][tp][hr]+w;
                q.push({-dis[v][tp][hr|a[v]],{v,{tp,hr|a[v]}}});
            }
        }
    }
}
int main(){
	read(t);
    while(t--){
        read(n);
        read(m);
        read(h);
        for(int i=1;i<=n;++i){
            a[i]=vis[i][0][0]=vis[i][0][1]=vis[i][1][0]=vis[i][1][1]=false;
            head[i]=0;
            dis[i][0][0]=dis[i][0][1]=dis[i][1][0]=dis[i][1][1]=LONG_LONG_MAX>>2;
        }
        ans=LONG_LONG_MAX;
        for(int i=1;i<=h;++i){
            int H;
            read(H);
            a[H]=1;
        }
        for(int i=1;i<=m;++i){
            int u,v;
            ll w;
            read(u);
            read(v);
            read(w);
            add(u,v,w);
            add(v,u,w);
        }
        dj();
        for(int i=1;i<=n;++i){
            if((vis[i][0][0]|vis[i][0][1])&(vis[i][1][0]|vis[i][1][1]))ans=min(ans,max(min(dis[i][0][0],dis[i][0][1]),min(dis[i][1][0],dis[i][1][1])));
        }
        if(ans==LONG_LONG_MAX)ans=-1;
        wr2(ans);
    }
	return 0;
}
```

---

## 作者：conti123 (赞：0)

### 前言

大无语，只有我认为难度排序是 $H<F<E<G$ 吗？

### 分析

考虑最短路，发现多出了 马 这个东西，于是考虑在原基础上多开一维，即 $dis[i][j]$ 表示到 $i$ 节点，有没有骑马的最短所需时间。

则可得 $ans=\min_{i=1}^n\max(\min(dis1[i][0],dis1[i][1]),\min(disn[i][0],disn[i][1]))$

即两人到 $i$ 节点的最短时间再取个 $\max$。

考虑转移，和正常的 dijkstra，然后看看这个节点是不是有马可以骑，有的话就直接改变第二维，后面都不会变了，贪心可证。

### Code
```cpp
struct fy{
	int id,w,op;
};
bool operator < (fy x,fy y){
	return x.w>y.w;
}
void bfs(int id,int st){
	dis[id][st][0]=0;
	std::priority_queue<fy>Q;
	Q.push({st,0,0});
	while(!Q.empty()){
		fy u=Q.top();Q.pop();
		if(vis[id][u.id][u.op])
			continue;
		vis[id][u.id][u.op]=1;
		bool ok=u.op|a[u.id];//看是否有马骑
		for(auto [v,w]:E[u.id]){
			int dist=ok?w/2:w;
			if(dis[id][u.id][u.op]+dist<dis[id][v][ok]){
				dis[id][v][ok]=dis[id][u.id][u.op]+dist;
				Q.push({v,dis[id][v][ok],ok});
			}
		}
	}
}
void solve(){
	std::cin>>n>>m>>k;
	for(int i=1;i<=k;i++){
		int x;
		std::cin>>x;
		a[x]=1;
	}
	for(int i=1;i<=m;i++){
		int x,y,z;
		std::cin>>x>>y>>z;
		E[x].push_back({y,z});
		E[y].push_back({x,z});
	}
	for(int i=1;i<=n;i++){
		dis[0][i][0]=
		dis[0][i][1]=
		dis[1][i][0]=
		dis[1][i][1]=1e18;
		vis[0][i][0]=
		vis[0][i][1]=
		vis[1][i][0]=
		vis[1][i][1]=0;
	}
	ans=1e18;//记得开大点
	bfs(0,1);
	bfs(1,n);
	for(int i=1;i<=n;i++){
		ans=std::min(ans,std::max(std::min(dis[0][i][0],dis[0][i][1]),std::min(dis[1][i][0],dis[1][i][1])));
	}
	if(ans==1e18)
		ans=-1;
	std::cout<<ans<<"\n";
	for(int i=1;i<=n;i++)
		a[i]=0,E[i].clear();
}
```

---

## 作者：Jerry_heng (赞：0)

（一）

从起点和终点为开始分别跑一遍 Dijkstra，将图上每一个点分为两个点，分别为已经有马和还未有马。

统计答案时对每个点询问一遍两遍 Dijkstra 的和即可。

（二）

AC 代码。

```cpp
//2024-09-21 23:18:11
#include<bits/stdc++.h>
#define db double
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define mkp make_pair
#define pii pair<int,int>
#define int long long
using namespace std;
bool MBE;
inline int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f; 
}
const int mxn=4e5+10,inf=1e18;
int n,m,h,dis1[mxn],dis2[mxn];
bool vis[mxn],p[mxn];
vector<pii>E[mxn];
void dij(int s,int *dis){
    for(int i=1;i<=n*2;i++)
        dis[i]=inf;
    for(int i=1;i<=n*2;i++)
        vis[i]=0;
    dis[s]=0;
    priority_queue<pii,vector<pii>,greater<pii> >q;
    q.push(mkp(0,s));
    if(p[s])dis[n+s]=0,q.push(mkp(0,n+s));
    while(!q.empty()){
        int u=q.top().se;q.pop();
        if(vis[u])continue;
        vis[u]=1;
        int t=(u>n)?(u-n):u;
        for(auto [v,w]:E[t]){
            if(u>n){
                if(dis[v+n] >dis[u]+w/2){
                    dis[v+n]=dis[u]+w/2;
                    if(!vis[v+n])q.push(mkp(dis[v+n],v+n));
                }
            }
            else{
                if(p[v]){
                    if(dis[v+n]>dis[u]+w){
                        dis[v+n]=dis[u]+w;
                        if(!vis[v+n])q.push(mkp(dis[v+n],v+n));
                    }
                }
                else{
                    if(dis[v]>dis[u]+w){
                        dis[v]=dis[u]+w;
                        if(!vis[v])q.push(mkp(dis[v],v));
                    }
                }
            }
        }
    }
}
signed main(){
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    int T=read();
    while(T--){    
        n=read(),m=read(),h=read();
        for(int i=1;i<=n;i++)
            p[i]=0,E[i].clear();
        for(int i=1;i<=h;i++){
            int x=read();
            p[x]=1;
        }
        for(int i=1;i<=m;i++){
            int u=read(),v=read(),w=read();
            E[u].eb(v,w),E[v].eb(u,w);
        }
        dij(1,dis1),dij(n,dis2);
        int ans=inf;
        for(int i=1;i<=n;i++){
            ans=min(ans,max(min(dis1[i],dis1[i+n]),min(dis2[i],dis2[i+n])));
        }
        if(ans>=inf)puts("-1");
        else printf("%lld\n",ans);
    }
    bool MED;
    cerr<<(&MED-&MBE)/1048576.0<<" MB, "<<1000*clock()/CLOCKS_PER_SEC<<" ms\n";

    return 0;
}
```

---

