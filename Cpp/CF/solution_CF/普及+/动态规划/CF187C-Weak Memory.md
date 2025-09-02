# Weak Memory

## 题目描述

Zart PMP is qualified for ICPC World Finals in Harbin, China. After team excursion to Sun Island Park for snow sculpture art exposition, PMP should get back to buses before they leave. But the park is really big and he does not know how to find them.

The park has $ n $ intersections numbered $ 1 $ through $ n $ . There are $ m $ bidirectional roads that connect some pairs of these intersections. At $ k $ intersections, ICPC volunteers are helping the teams and showing them the way to their destinations. Locations of volunteers are fixed and distinct.

When PMP asks a volunteer the way to bus station, he/she can tell him the whole path. But the park is fully covered with ice and snow and everywhere looks almost the same. So PMP can only memorize at most $ q $ intersections after each question (excluding the intersection they are currently standing). He always tells volunteers about his weak memory and if there is no direct path of length (in number of roads) at most $ q $ that leads to bus station, the volunteer will guide PMP to another volunteer (who is at most $ q $ intersections away, of course). ICPC volunteers know the area very well and always tell PMP the best way. So if there exists a way to bus stations, PMP will definitely find it.

PMP's initial location is intersection $ s $ and the buses are at intersection $ t $ . There will always be a volunteer at intersection $ s $ . Your job is to find out the minimum $ q $ which guarantees that PMP can find the buses.

## 说明/提示

The first sample is illustrated below. Blue intersections are where volunteers are located. If PMP goes in the path of dashed line, it can reach the buses with $ q=3 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF187C/c6f84f7d8e65e3d0b7f7fc6b41fb9b6c090dc4ed.png)In the second sample, PMP uses intersection 6 as an intermediate intersection, thus the answer is 3.

## 样例 #1

### 输入

```
6 6 3
1 3 6
1 2
2 3
4 2
5 6
4 5
3 4
1 6
```

### 输出

```
3
```

## 样例 #2

### 输入

```
6 5 3
1 5 6
1 2
2 3
3 4
4 5
6 3
1 5
```

### 输出

```
3
```

# 题解

## 作者：Sakuya_maid (赞：5)

[CF题目链接](https://codeforces.com/contest/187/problem/C)

[洛谷题目链接](https://www.luogu.com.cn/problem/CF187C)

因为是远古场，这题用 dij 重复入队更新点的做法也是能过得，比如题解区的其余几篇，都是用优先队列，点是可以一直被更新的，在 $n = 1\times10^5$，$m = 2\times 10^5$ 的情况下，没被卡只是远古场数据水而已，我要讲的做法是二分 $+$ 并查集 $+$ bfs，这种做法是稳定 $n \log n$ 的。

首先，明显可以二分这个最小能量，通过那些关键能补全的点去更新其他能到的点，这一能更新到的就类似是一整块连通块，这个更新的距离范围不超过被二分的值，能走到的点则用并查集进行存储。

注意这里是两个点 $u+v+1 \le x$，（$x$ 是被二分的能量的值）才可以进行不同连通块的合并，最后查找 $s$ 和 $t$ 是否在同一块连通块来确定二分的返回值。

这里有个关键点，就是若 $t$ 与 $u$ 或 $v$ 都足够近，但 $u$ 与 $v$ 之间过远，如果最开始没有给 $t$ 打上是特殊点的标记就是不合理的，会 Wa on 11。

```c
    auto check = [&](int x)->bool{
        vector<int>fa(n + 1), dist(n + 1), ss(n + 1);
        queue<int>q;
        auto find = [&](auto self, int x) -> int{
            return fa[x] == x ? x : fa[x] = self(self, fa[x]);
        };

        auto merge = [&](int x, int y)->void{
            if(find(find, x) != find(find, y)){
                fa[find(find, x)] = find(find, y);
            }
        };

        for(int i = 1; i <= n; ++ i){
            fa[i] = i;
            if(vis[i])q.push(i), ss[i] = i;
        }

        while(q.size()){
            auto u = q.front();
            q.pop();
            for(auto v : g[u]){
                if(!ss[v]){
                    ss[v] = ss[u];
                    dist[v] = dist[u] + 1;
                    merge(v, u);
                    if(dist[v] < x)q.push(v);
                }else{
                    if(dist[v] + dist[u] + 1 <= x){
                        merge(u, v);
                    }
                }
            }
        }

        return  find(find, s) == find(find, t);
    };
```

[提交记录](https://codeforces.com/contest/187/submission/241131292)


---

## 作者：YCS_GG (赞：1)

### CF187C Weak Memory

这题显然没紫题难度，最多绿

既然让能量最小可以考虑二分答案变成可行性问题

因为操作只会$-1$或者补满，所以某个点当前能量最大一定“有利于”接下来点的转移(不会更劣)

那就二分最小能量跑$bfs$即可

```cpp
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int N = 100010;
struct Edge {
    int v;
    int nxt;
} edge[N * 4];
int head[N], ecnt;
void add(int u, int v) {
    edge[++ecnt].v = v;
    edge[ecnt].nxt = head[u];
    head[u]        = ecnt;
}
int pos[N];
int dis[N];
int n, m, k, s, t;
struct Data {
    int x, w;
    bool operator<(const Data &b) const {
        return w < b.w;
    }
};
priority_queue<Data> q;
bool check(int x) {
    while (!q.empty())
        q.pop();
    memset(dis, -1, sizeof(dis));
    dis[s] = x;
    q.push({s, x});
    while (!q.empty()) {
        Data now = q.top();
        q.pop();
        if (now.w == 0) {
            continue;
        }
        for (int i = head[now.x]; i; i = edge[i].nxt) {
            int v = edge[i].v;
            int w = now.w - 1;
            if (v == t)
                return true;
            if (pos[v]) {
                w = x;
            }
            if (dis[v] < w) {
                dis[v] = w;
                q.push({v, w});
            }
        }
    }
    return false;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> k;
    for (int i = 1; i <= k; i++) {
        int tmp;
        cin >> tmp;
        pos[tmp] = 1;
    }
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
        add(b, a);
    }
    cin >> s >> t;
    int l = 1, r = n, ans = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            r   = mid - 1;
            ans = mid;
        } else {
            l = mid + 1;
        }
    }
    cout << ans;
}
```



---

## 作者：Velix (赞：1)

第一眼看上去这题非常明显要用BFS，但是由于特殊点的存在，使得这道题处理起来非常棘手。

这时候就要请出我们的神器了：

### 堆！

堆在这题里用来处理特殊点时非常简单，只要处理到特殊点时，将特殊点的路径长度赋值为$0$就行了，非常方便。答案就在每次取出时用取出点的最短路径长与$ans$比较并取最大的就行了。（看起来非常像dijkstra，但跟dijkstra相比少了vis数组）

有一些地方要注意：

当循环到结束点时就可以停止了，没必要继续下去；

当循环时发现循环到的点权值比目前的值小的话，可以直接退出了（否则会WA）。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
struct dd{
	int to,next;
}a[500001];
int q,head[100001],dis[100001],start,over,n,m,sn,ans;
bool spe[100001];
void add(int xx,int yy)
{
	a[++q].to=yy;
	a[q].next=head[xx];
	head[xx]=q;
}
struct ss{
	int dis;
	int pos;
	bool operator <(const ss &t)const
	{
		return t.dis<dis;
	}
}u,ert;
priority_queue<ss> que;
void bfs()
{
	dis[start]=0;
	u.dis=0;
	u.pos=start;
	que.push(u);
	while(!que.empty())
	{
		u=que.top();
		que.pop();
		if(u.dis>dis[u.pos])continue;
		ans=max(ans,u.dis);
		if(u.pos==over)return;
		if(spe[u.pos])dis[u.pos]=0;
		for(int i=head[u.pos];i;i=a[i].next)
			if(dis[a[i].to]>dis[u.pos]+1)
			{
				dis[a[i].to]=dis[u.pos]+1;
				ert.dis=dis[a[i].to];
				ert.pos=a[i].to;
				que.push(ert);
			}
	}
}
int main()
{
	int x,y,z;	
	for(int i=1;i<=100000;i++) dis[i]=1073741824;
	cin>>n>>m>>sn;
	for(int i=1;i<=sn;i++)
	{
		scanf("%d",&x);
		spe[x]=1;		
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	cin>>start>>over;
	bfs();
	if(dis[over]!=1073741824)cout<<ans;
	else cout<<-1;
}
```


---

## 作者：ZLCT (赞：0)

# CF187C Weak Memory
## 题目翻译
给定一个无向图，给定 $k$ 个加油站，现在要从 $S$ 走到 $T$，你每走到一个加油站都可以加满油，每走一条边消耗一升油，求油箱容量最少多少升。
## 法1
感觉这个题是一个经典的套路，但是好像没有太多人选择这种做法？可能都觉得复杂度感觉不太对。\
我们先考虑没有加油站该怎么做，显然就是跑一遍最短路求出 $S\rightarrow T$ 的最短距离。\
那加上这些加油站对于我们的最短路有什么影响呢？\
我们设 $d_u$ 表示到达一个点油箱里用的最少油量。\
那么本来我们的 $d_u$ 就是 $S\rightarrow u$ 的最短路，我们这里设 $dis(u,v)$ 表示从 $u\rightarrow v$ 的最短路。那么现在我们有了加油站后就可以选择前往最近的加油站加满油再回到点 $u$，所以我们如果设 $D_u$ 表示离点 $u$ 最近的加油站距离，那 $d_u$ 就变成了 $\min(D_u,d_u)$。\
你可能会说有可能在之前的时候到过加油站加油呢？那由于我们最短路的转移是按顺序的，所以在之前到达那个点时已经会把它到达加油站再回来的情况考虑了。\
那还有人会说如果经过加油站怎么办呢？那也好办，既然都经过了那肯定是选择顺便加个油更优了。\
然后我们要求最小值，看到最值就想二分，显然答案是具有单调性的，所以我们二分答案，至于 check 函数就跑一遍最短路，我们设目前二分的答案是 $x$ 注意如果 $d_u=x$ 时我们不能继续扩展了。\
那这个最短路怎么跑呢？首先我们肯定不需要 dij，因为边权都是 $1$，因此我们可以直接 bfs。但是有个问题，由于我们有可能会去一个加油站导致我们的 $d_u$ 减少，所以我们不能跑普通的 bfs，我们要跑可以重复入队的 bfs，也就是 spfa。\
诶？spfa 不是已经死了吗？\
是这样的，但是这个题有很好的性质，因为我们没到一个点都考虑了这个点到最近加油站再回来的情况，所以如果我们把扩展的点分层，那一定不存在回流的情况，唯一可能重复入栈的情况就是同一层之间会相互有扩展，但是那就代表又重新分层了，那复杂度上限就是每个点都被又扩展了一遍，也就是 $O(2m)$，再加上外层二分的复杂度，总复杂度 $O(m\log{n})$。
## 法2
我们对于每一个加油站考虑，如果最后的答案是 $x$，那么只要在同一个加油站直径 $x$ 之内的点都可以选择从该加油站中转到达彼此。\
那如果一个加油站的直径覆盖了另一个加油站怎么办呢？这就说明这两个加油站彼此可以互相到达，更进一步，这两个加油站的直径所能覆盖到的所有点都能互相到达。\
所以我们以终点 $T$ 与每个加油站为扩展起点，一层一层地进行扩展直到起点 $S$ 与 $T$ 处在同一个连通块。\
至于为什么要把 $T$ 也作为扩展起点，这是因为为了好扩展，因为我们如果直接扩展会存在两个被扩展的非加油站结点相互扩展导致错误的扩展，所以我们要先后扩展是否是加油站的点，对于两个非加油站结点之间进行扩展，我们的直径就要扩大一倍。\
其实为了不那么麻烦，由这个思路延伸，你可以直接二分答案并以 $T$ 作为起点向外扩展 $x$  步，若遇到加油站就另作起点进行扩展，这样每个点只需要扩展一次，复杂度 $O(m\log n)$。
## 法3
这是基于第一种做法和第二种做法的结合。\
我们同样对于每一个点求出距离最近的加油站的距离。然后我们按照距离升序排序。接着按照第二种扩展连通块的思路，只不过我们只考虑连接两个加油站的桥，假设 $d_u$ 表示距离最近加油站的距离，$p_u$ 表示距离最近加油站的编号，那么对于边 $(u,v)$，只要 $p_u\ne p_v$ 这就是一个桥，那它连接两个加油站的最小直径就是 $d_u+d_v+1$。后面的就和第二种方法类似，不断扩展合并联通块直到 $S,T$ 连通，复杂度在于排序的 $O(m\log m)$。
## code1
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
using namespace std;
const int N=1e5+666;
int n,m,k,S,T;
vector<int>G[N];
int d1[N];
bool iskey[N];
void dij1(){
    set<pair<int,int> >s;
    memset(d1,0x3f,sizeof(d1));
    for(int i=1;i<=n;++i){
        if(iskey[i]){
            s.insert({0,i});
            d1[i]=0;
        }
    }
    while(!s.empty()){
        int u=s.begin()->second;
        s.erase(s.begin());
        for(int v:G[u]){
            if(d1[v]>d1[u]+1){
                s.erase({d1[v],v});
                d1[v]=d1[u]+1;
                s.insert({d1[v],v});
            }
        }
    }
}
int d[N];
bool vis[N];
bool check(int x){
    queue<int>q;
    memset(d,0x3f,sizeof(d));
    memset(vis,0,sizeof(vis));
    d[S]=0;
    q.push(S);
    vis[S]=1;
    while(!q.empty()){
        int u=q.front();q.pop();vis[u]=0;
        if(d[u]+d1[u]<=x)d[u]=min(d[u],d1[u]);
        if(d[u]==x)continue;
        for(int v:G[u]){
            if(d[v]>d[u]+1){
                d[v]=d[u]+1;
                if(!vis[v]){
                    vis[v]=1;
                    q.push(v);
                }
            }
        }
    }
    return d[T]<=n;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>m>>k;
    for(int i=1;i<=k;++i){
        int x;cin>>x;
        iskey[x]=1;
    }
    for(int i=1;i<=m;++i){
        int u,v;cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    cin>>S>>T;
    dij1();
    int l=1,r=n+1;
    while(l<r){
        int mid=(l+r)>>1;
        if(check(mid))r=mid;
        else l=mid+1;
    }
    cout<<(l<=n?l:-1)<<'\n';
    return 0;
}
```
## code2 by `gzz`
```cpp
#include <cstdio>

const int N = 100000 + 5, M = 200000 + 5, BM = M * 2;

int n, m, k;
int hd[N], to[BM], nxt[BM];

inline void add_se(int idx, int a, int b) {
    nxt[idx] = hd[a]; hd[a] = idx;
    to[idx] = b;
}

int vis[N];
int fa[N];

inline int find(int a) {
    int s = a, t;
    while(fa[s] != s) s = fa[s];
    while(fa[a] != s) t = fa[a], fa[a] = s, a = t;
    return s;
}

inline void merge(int a, int b) {
    a = find(a), b = find(b);
    fa[a] = b;
}

int que[2][N], szque[2];

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= k; ++i) {
        int a; scanf("%d", &a);
        vis[a] = 1;
        que[0][++szque[0]] = a;
    }
    for(int i = 1; i <= m; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        add_se(i << 1, u, v);
        add_se(i << 1 | 1, v, u);
    }
    for(int i = 1; i <= n; ++i) fa[i] = i;
    int s, t; scanf("%d%d", &s, &t);
    if(!vis[t]){
        vis[t] = 1;
        que[0][++szque[0]] = t;
    }
    int nwq = 0, nwk = 0, vistag = 1;
    while(szque[nwq]) {
        ++nwk;
        ++vistag;
        for(int ii = 1; ii <= szque[nwq]; ++ii) {
            int u = que[nwq][ii];
            for(int e = hd[u]; e; e = nxt[e]) {
                int v = to[e];
                if(vis[v]) merge(u, v);
            }
        }
        if(find(s) == find(t)) break;
        ++nwk;
        for(int ii = 1; ii <= szque[nwq]; ++ii) {
            int u = que[nwq][ii];
            for(int e = hd[u]; e; e = nxt[e]) {
                int v = to[e];
                merge(u, v);
                if(!vis[v]) {
                    vis[v] = vistag;
                    que[nwq ^ 1][++szque[nwq ^ 1]] = v;
                }
            }
        }
        if(find(s) == find(t)) break;
        szque[nwq] = 0;
        nwq ^= 1;
    }
    if(find(s) != find(t)) puts("-1");
    else printf("%d\n", nwk);
    return 0;
}
```
## code3 by `Vercingetorix`
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctype.h>
#include <queue>
#include <cstring>
#include <set>
#include <bitset>
#include <map>
#include <chrono>
#include <random>
#include <unordered_map>
#include <stdio.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef std::vector<int> vi;
typedef std::vector<bool> vb;
typedef std::vector<string> vs;
typedef std::vector<double> vd;
typedef std::vector<long long> vll;
typedef std::vector<std::vector<int> > vvi;
typedef vector<vll> vvll;
typedef std::vector<std::pair<int, int> > vpi;
typedef vector<vpi> vvpi;
typedef std::pair<int, int> pi;
typedef std::pair<ll, ll> pll;
typedef std::vector<pll> vpll;

const long long mod = 1000000007;
ll gcd (ll a, ll b) {return b==0 ? a : gcd(b, a%b);}
const unsigned gen_seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937_64 gen(gen_seed);

#define all(c) (c).begin(),(c).end()
#define srt(c) sort(all(c))
#define srtrev(c) sort(all(c)); reverse(all(c))
#define forn(i, a, b) for(int i = a; i < b; i++)
#define read(x) scanf("%d", &x)
#define readv(x, n) vi x(n); forn(i,0,n) scanf("%d", &x[i])

#define pb push_back
#define mp make_pair

const int A = 100500;
int parent[A];
int rk[A];
void make_set (int v) {
    parent[v] = v;
    rk[v] = 0;
}

int find_set (int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set (parent[v]);
}

void union_sets (int a, int b) {
    a = find_set (a);
    b = find_set (b);
    if (a != b) {
        if (rk[a] < rk[b])
            swap (a, b);
        parent[b] = a;
        if (rk[a] == rk[b])
            ++rk[a];
    }
}

vi g[A];

int main()
{
#ifdef LOCAL
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    int n,m,k;
    scanf("%d %d %d", &n, &m, &k);
    readv(port, k);
    forn(i,0,k) port[i]--;
    vpi e;
    forn(i,0,m) {
        int u,v;
        scanf("%d %d", &u, &v);
        u--; v--;
        g[u].pb(v);
        g[v].pb(u);
        e.pb(mp(u, v));
    }
    int s,t;
    scanf("%d %d", &s, &t);
    int has = 0;
    s--; t--;
    for(auto x : port) if(x == t) has = 1;
    if(has == 0) port.pb(t);
    
    const int INF = 1e9;
    vi d (n, INF);
    vi p(n);
    priority_queue < pair<ll,int> > q;
    for(auto x : port) {
        d[x] = 0;
        p[x] = x;
        q.push (make_pair (0, x));
    }
    
    while (!q.empty()) {
        int v = q.top().second;
        ll cur_d = -q.top().first;
        q.pop();
        if (cur_d > d[v])  continue;
        for (size_t j=0; j<g[v].size(); ++j) {
            int to = g[v][j],
            len = 1;
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = p[v];
                q.push (make_pair (-d[to], to));
            }
        }
    }
    vector<pair<int, pi>> krus;
    for(auto x : e) {
        int u = x.first;
        int v = x.second;
        if(p[u] != p[v]) krus.pb(mp(d[u] + d[v] + 1, mp(p[u], p[v])));
    }
    srt(krus);
    forn(i,0,n) make_set(i);
    for(auto x : krus) {
        int u = x.second.first;
        int v = x.second.second;
        if(find_set(v) != find_set(u)) {
            union_sets(u, v);
        }
        if(find_set(s) == find_set(t)) {
            cout<<x.first;
            exit(0);
        }
    }
    cout<<-1;
    
    
}
```

---

## 作者：ConstantModerato (赞：0)

题意：给定一个包含 $n$ 个节点和 $m$ 条边的无向图，每走一条边都需要花费 $1$ 点能量。

有 $k$ 个特殊点，每经过一个特殊点都可以将当前能量值补充到能量上限。给定起点 $s$ 和终点 $t$，求可从点 $s$ 到达点 $t$ 的最小能量上限。（保证关键点位置不同且s点必为关键点）

方法 $1$: 考虑二分这个最小能量上限 $val$，然后从起点开始进行 $bfs$，如果当前点的距离大于 $val$ 就停止枚举，如果转移到关键点就将点的距离设置为 $0$，最后判断能不能到就可以。

观察到上面的方法，每一个点访问的次数没有保证，最坏的时间复杂度为 $O((n + m)k\log n)$，显然是不足以通过此题的。于是我们考虑优化上面的方案。~~（但是比赛的时候有很多人通过这个方法把这题创死了）~~

考虑一个点 $x$，如果这个点能在 $val$ 的范围内被特殊点集合 $V$ 内的达到。那么这特殊点集合 $V$ 中的特殊点点能到达的节点一定都相互可以达到。因为这些点都可以通过若干个特殊点达到对方。

观察到上面的结构有点类似于并查集，所以我们考虑通过并查集来维护这个可达的点集。

但是这样的复杂度还是 $O(\alpha(n)(n + m)k\log n )$ 级别的，有什么方法能让一个点的访问次数减少呢？

两个能互相可达的关键点集合，一定有一个距离最近的路径，我们考虑维护一个像那样的路径。

考虑维护一个点距离它最近的关键点，这样，如果这两个点的距离到关键点的距离 小于 $val - 1$ 的话，那这两个节点就相当于是连通的。这样我们就只需要遍历一遍节点了。复杂度 $O(\alpha(n)(n + m)\log n )$。

```
int n,m,k;
vector<int> E[N];
int vis[N],dis[N],f[N];
int s,t;
int find(int x){
    if (x == f[x]) return x;
    else return f[x] = find(f[x]);
}
void merge(int x,int y){
    f[find(x)] = find(y);
}
queue<int> q;
int check(int val){
    for (int i = 1;i <= n;i++) f[i] = i,dis[i] = 0;
    for (int i = 1;i <= n;i++) if (vis[i]) q.push(i);
    while (!q.empty()){
        int u = q.front();q.pop();
        for (auto v : E[u]){
            if (dis[u] >= val) continue;
            if (!dis[v] && !vis[v]){
                dis[v] = dis[u] + 1;
                merge(u,v);
                q.push(v);
            } else if (dis[v] + dis[u] + 1 <= val) merge(v,u);
        }
    } return find(s) == find(t);
}
int main(){
    n = read(),m = read(),k = read();
    for (int i = 1;i <= k;i++) vis[read()] = 1;
    for (int i = 1,u,v;i <= m;i++){
        u = read(),v = read();
        E[u].push_back(v);E[v].push_back(u);
    } s = read(),t = read(); vis[t] = 1;
    int l = 0,r = m + 1;
    while (l + 1 != r){
        int mid = l + r >> 1;
        if (check(mid)) r = mid;
        else l = mid;
    } 
    if (r == m + 1) puts("-1");
    else cout << r << endl;
    return 0;
}
```

其实你最后可以发现，这个二分其实没有什么必要，可以直接 $bfs$ 解决的。现场榜二 $gzz$ 的代码就是这样的。

```
int n, m, k;
int hd[N], to[BM], nxt[BM];
 
inline void add_se(int idx, int a, int b) {
    nxt[idx] = hd[a]; hd[a] = idx;
    to[idx] = b;
}
 
int vis[N];
int fa[N];
 
inline int find(int a) {
    int s = a, t;
    while(fa[s] != s) s = fa[s];
    while(fa[a] != s) t = fa[a], fa[a] = s, a = t;
    return s;
}
 
inline void merge(int a, int b) {
    a = find(a), b = find(b);
    fa[a] = b;
}
 
int que[2][N], szque[2];
 
int main() {
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= k; ++i) {
        int a; scanf("%d", &a);
        vis[a] = 1;
        que[0][++szque[0]] = a;
    }
    for(int i = 1; i <= m; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        add_se(i << 1, u, v);
        add_se(i << 1 | 1, v, u);
    }
    for(int i = 1; i <= n; ++i) fa[i] = i;
    int s, t; scanf("%d%d", &s, &t);
    if(!vis[t]){
        vis[t] = 1;
        que[0][++szque[0]] = t;
    }
    int nwq = 0, nwk = 0, vistag = 1;
    while(szque[nwq]) {
        ++nwk;
        ++vistag;
        for(int ii = 1; ii <= szque[nwq]; ++ii) {
            int u = que[nwq][ii];
            for(int e = hd[u]; e; e = nxt[e]) {
                int v = to[e];
                if(vis[v]) merge(u, v);
            }
        }
        if(find(s) == find(t)) break;
        ++nwk;
        for(int ii = 1; ii <= szque[nwq]; ++ii) {
            int u = que[nwq][ii];
            for(int e = hd[u]; e; e = nxt[e]) {
                int v = to[e];
                merge(u, v);
                if(!vis[v]) {
                    vis[v] = vistag;
                    que[nwq ^ 1][++szque[nwq ^ 1]] = v;
                }
            }
        }
        if(find(s) == find(t)) break;
        szque[nwq] = 0;
        nwq ^= 1;
    }
    if(find(s) != find(t)) puts("-1");
    else printf("%d\n", nwk);
    return 0;
}
```
通过一次广搜枚举一次距离，来维护最小值。

---

