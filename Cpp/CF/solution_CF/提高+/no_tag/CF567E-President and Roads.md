# President and Roads

## 题目描述

Berland has $ n $ cities, the capital is located in city $ s $ , and the historic home town of the President is in city $ t $ ( $ s≠t $ ). The cities are connected by one-way roads, the travel time for each of the road is a positive integer.

Once a year the President visited his historic home town $ t $ , for which his motorcade passes along some path from $ s $ to $ t $ (he always returns on a personal plane). Since the president is a very busy man, he always chooses the path from $ s $ to $ t $ , along which he will travel the fastest.

The ministry of Roads and Railways wants to learn for each of the road: whether the President will definitely pass through it during his travels, and if not, whether it is possible to repair it so that it would definitely be included in the shortest path from the capital to the historic home town of the President. Obviously, the road can not be repaired so that the travel time on it was less than one. The ministry of Berland, like any other, is interested in maintaining the budget, so it wants to know the minimum cost of repairing the road. Also, it is very fond of accuracy, so it repairs the roads so that the travel time on them is always a positive integer.

## 说明/提示

The cost of repairing the road is the difference between the time needed to ride along it before and after the repairing.

In the first sample president initially may choose one of the two following ways for a ride: $ 1→2→4→5→6 $ or $ 1→2→3→5→6 $ .

## 样例 #1

### 输入

```
6 7 1 6
1 2 2
1 3 10
2 3 7
2 4 8
3 5 3
4 5 2
5 6 1
```

### 输出

```
YES
CAN 2
CAN 1
CAN 1
CAN 1
CAN 1
YES
```

## 样例 #2

### 输入

```
3 3 1 3
1 2 10
2 3 10
1 3 100
```

### 输出

```
YES
YES
CAN 81
```

## 样例 #3

### 输入

```
2 2 1 2
1 2 1
1 2 2
```

### 输出

```
YES
NO
```

# 题解

## 作者：Imakf (赞：12)

~~你是否 Wrong answer on test 104？~~

问一条边是否一定会被经过，这非常简单：

只需要**正图反图统计两遍最短路数量**。

记 $s\rightarrow i$ 的最短路数量为 $d_i$

记 $i\rightarrow t$ 的最短路数量为 $d_i'$

如果有一条边 $u\rightarrow v$ 必须被经过，那么必然满足 $d_u\times d_v'=d_t$。

因为显然最短路数可以非常多，必须要取模。

显然 cf 数据非常毒瘤，必须要双模数。

然后注意边权不能减成负的，大力分类讨论即可。

~~好像模数稍微针对了一下 $1e9+7$~~

我用的是 

```cpp
#define mod (998244353)
#define mod2 (192608173)
```

### 代码
```cpp
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <queue>

#define rg register
#define il inline
#define MX (100000 + 33)
#define LL long long
#define mod (998244353)
#define mod2 (192608173)

int read(){
	char k = getchar(); int x = 0;
	while(k < '0' || k > '9') k = getchar();
	while(k >= '0' && k <= '9')
		x = x * 10 + k - '0' ,k = getchar();
	return x;
}

int pos[MX] ,neg[MX] ,tot;
struct edge{
	int fr ,node ,next ,w;
}h[MX << 1];
void addedge(int u ,int v ,int w ,int *head){
	h[++tot].next = head[u] ,head[u] = tot;
	h[tot].fr = u ,h[tot].node = v,h[tot].w = w;
}

struct node{
	int d; LL dis;
	bool operator <(const node& b)const{
		return dis > b.dis;
	}
};
LL distoT[MX] ,disfrS[MX] ,cnttoT[MX] ,cnt1[MX] ,cnt2[MX] ,cntfrS[MX];
int s ,t ,n ,m ,vis[MX];
void dijkstra(int ST ,int *head ,LL *dist ,LL *cnt ,LL *CNT){
	for(int i = 1 ; i <= n ; ++i) dist[i] = 1LL << 50;
	dist[ST] = 0 ,cnt[ST] = 1 ,memset(vis ,0 ,sizeof vis);
	std::priority_queue<node> q; q.push((node){ST ,0});
	while(!q.empty()){
		node tmp = q.top(); int x = tmp.d; q.pop();
		if(tmp.dis != dist[x] || vis[x]) continue;
		vis[x] = true;
		for(int i = head[x] ,d ; i ; i = h[i].next){
			d = h[i].node;
			if(dist[x] + h[i].w == dist[d]){
				(cnt[d] += cnt[x]) %= mod;
				(CNT[d] += CNT[x]) %= mod2;
			}
			if(dist[x] + h[i].w < dist[d]){
				dist[d] = dist[x] + h[i].w ,cnt[d] = cnt[x];
				CNT[d] = CNT[x];
				if(!vis[d]) q.push((node){d ,dist[d]});
			}
		}
	}
}

int main(){
	n = read() ,m = read() ,s = read() ,t = read();
	for(int i = 1 ,u ,v ,w ; i <= m ; ++i){
		u = read() ,v = read() ,w = read();
		addedge(u ,v ,w ,pos) ,addedge(v ,u ,w ,neg);
	}
	dijkstra(s ,pos ,disfrS ,cntfrS ,cnt1);
	dijkstra(t ,neg ,distoT ,cnttoT ,cnt2);
	for(int i = 1 ,u ,v ,w ; i <= m * 2 ; i += 2){
		u = h[i].fr ,v = h[i].node ,w = h[i].w;
		if(disfrS[u] + distoT[v] >= (1LL << 50))	puts("NO");
		else if(disfrS[u] + w + distoT[v] == disfrS[t]){
			if(cntfrS[t] == cntfrS[u] * cnttoT[v] % mod &&
			cnt1[t] == cnt1[u] * cnt2[v] % mod2)	puts("YES");
			else{
				if(w == 1) puts("NO");
				else puts("CAN 1");
			}
		}else{
			LL del = disfrS[u] + w + distoT[v] - disfrS[t] + 1;
			if(del >= w) puts("NO");
			else printf("CAN %lld\n" ,del);
		}
	}return 0;
}
```

---

## 作者：Rainybunny (赞：5)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[$luogu$](https://www.luogu.org/problem/CF567E).
# 题解
## 思路
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;明显, 我们可以从正向图上从$s$跑最短路, 在反向图上从$t$跑最短路, 这样就能考察每条边是否在最短路上.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;问题是, 如何判断某条边的唯一性?
## 边的唯一性
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;排开运用乘法原理取模计算的方法, 我们考虑一种$100\%AC$的算法.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;实际上, 由"唯一的边", 我们应该自然的联想到无向图中$Tarjan$求桥的方法. 本题, 我们把所有可能在最短路上的边转为无向边, 连同所有结点建出一个新的无向图, 这个图上的桥其实就是原图上"唯一的边".  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;于是, 我们可以轻易地区分出"Yes"与其它情况, 剩下的就交给你啦!
## 代码
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;( 原谅我无奈WA穿之余"define int long long". )
```cpp
#include <queue>
#include <cstdio>
#include <cstring>
#include <utility>

#define Int register int
#define int long long

using namespace std;

typedef long long LL;
typedef pair<LL, int> pli;

const int MAXN = 1e6, MAXM = 1e6;
int n, m, s, t, Cnte, ReCnte, SCnte = 1, Head[MAXN + 5] = {}, ReHead[MAXN + 5] = {}, SHead[MAXN + 5] = {};
int Indx, DFN[MAXN + 5] = {}, Low[MAXN + 5] = {}, Ans[MAXM + 5] = {};
LL Dist[MAXN + 5] = {}, ReDist[MAXN + 5] = {};
bool Vis[MAXN + 5] = {}, Unique[MAXN + 5] = {};
priority_queue<pli, vector<pli>, greater<pli> > Q;

struct Edge { int To, Cost, _nxt; } Graph[MAXM + 5] = {}, ReGraph[MAXM + 5] = {}, SGraph[MAXM * 2 + 5] = {};

inline void Link ( const int From, const int To, const int Cost ) {
	Graph[++ Cnte] = { To, Cost, Head[From] };
	Head[From] = Cnte;
}

inline void ReLink ( const int From, const int To, const int Cost ) {
	ReGraph[++ ReCnte] = { To, Cost, ReHead[From] };
	ReHead[From] = ReCnte;
}

inline void SLink ( const int From, const int To, const int edid ) {
	SGraph[++ SCnte] = { To, edid, SHead[From] };
	SHead[From] = SCnte;
}

inline int Min ( const int a, const int b ) { return a < b ? a : b; }

inline void Dijkstra ( int* Head, Edge* Graph, LL* Dist, const int s ) {
	memset ( Vis, false, sizeof Vis );
	for ( Int i = 1; i <= n; ++ i ) Dist[i] = 0x3f3f3f3f3f3f3f3f;
	Dist[s] = 0, Q.push ( { 0, s } );
	while ( ! Q.empty () ) {
		pli p = Q.top (); Q.pop ();
		if ( Vis[p.second] ) continue;
		Vis[p.second] = true;
		for ( Int i = Head[p.second], v, w; i; i = Graph[i]._nxt ) {
			if ( ! Vis[v = Graph[i].To] && Dist[v] > Dist[p.second] + ( w = Graph[i].Cost ) ) {
				Dist[v] = Dist[p.second] + w;
				Q.push ( { Dist[v], v } );
			}
		}
	}
}

inline void Tarjan ( const int u, const int fae ) {
	DFN[u] = Low[u] = ++ Indx;
	for ( Int i = SHead[u], v; i; i = SGraph[i]._nxt ) {
		if ( ! DFN[v = SGraph[i].To] ) {
			Tarjan ( v, i );
			if ( Low[v] > DFN[u] ) Unique[SGraph[i].Cost] = true;
			Low[u] = Min ( Low[u], Low[v] );
		} else if ( DFN[u] > DFN[v] && i ^ fae ^ 1 ) {
			Low[u] = Min ( Low[u], DFN[v] );
		}
	}
}

inline void Work () {
	scanf ( "%lld %lld %lld %lld", &n, &m, &s, &t );
	for ( Int i = 1, u, v, w; i <= m; ++ i ) {
		scanf ( "%lld %lld %lld", &u, &v, &w );
		Link ( u, v, w ), ReLink ( v, u, w );
	}
	Dijkstra ( Head, Graph, Dist, s ), Dijkstra ( ReHead, ReGraph, ReDist, t );
	LL MinDist = Dist[t];
//	printf ( "%d %d\n", MinDist, ReDist[s] );
	for ( Int i = 1; i <= n; ++ i ) {
		for ( Int j = Head[i], v; j; j = Graph[j]._nxt ) {
			v = Graph[j].To;
			if ( Dist[i] + Graph[j].Cost + ReDist[v] == MinDist ) {
				SLink ( i, v, j ), SLink ( v, i, j );
			}
		}
	}
	for ( Int i = 1; i <= n; ++ i ) {
		if ( ! DFN[i] ) {
			Tarjan ( i, 0 );
		}
	}
//	for ( Int i = 1; i <= m; ++ i ) printf ( "%d ", Unique[i] ); puts ( "" );
	for ( Int i = 1; i <= n; ++ i ) {
		for ( Int j = Head[i]; j; j = Graph[j]._nxt ) {
			int v = Graph[j].To; LL s = Dist[i] + ReDist[v];
			if ( Unique[j] ) Ans[j] = 0;
			else {
				Ans[j] = Graph[j].Cost - ( MinDist - s - 1 );
				if ( Graph[j].Cost <= Ans[j] ) Ans[j] = -1;
			}
		}
	}
	for ( Int i = 1; i <= m; ++ i ) {
		if ( Unique[i] || Ans[i] <= 0 ) {
			puts ( ~ Ans[i] || Unique[i] ? "YES" : "NO" );
		} else {
			printf ( "CAN %lld\n", Ans[i] );
		}
	}
}

signed main () {
	Work ();
	return 0;
}
```

---

## 作者：Wf_yjqd (赞：4)

模拟赛 T3，写的正解寄在最短路径数量求错。

喜提爆零。

------------

比较显然的是，肯定要跑 $s$ 的单源最短路。

然后其实只用求出最短路径图然后 Tarjan 求割桥就好了。

但我板子背不过。

考虑必经之路的特点，即走这条路的方案数等于总方案数。

那就再建一张反图，求 $t$ 的单源最短路。

过程中记录最短路径数量。

利用乘法原理可得，若有一条最短路边 $u$ 到 $v$，从 $s$ 到 $u$ 的方案数 $\times$ 反图上从 $t$ 到 $v$ 的方案数 $=$ 从 $s$ 到 $t$ 的方案数，则 $u$ 到 $v$ 这条边为必经之路。

输出 `CAN` 的情况直接贪心即可。

将这条边变成 $s$ 到 $t$ 的最短路长度 $-$ $s$ 到 $u$ 的最短路长度 $-$ 反图上 $t$ 到 $v$ 最短路长度 $-1$。

这样就会有至少一条经过 $u$ 到 $v$ 这条边，且比原最短路还短的路径。

如果边权到 $0$ 及以下就输出 `NO`。

其实此题还有个坑点，最短路方案数可能很大（算了算，高精都开不下），所以考虑取模。

没试过直接自然溢出或单模数行不行（我用了俩）。

------------

要大质数的可以看代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> p;
const ll maxn=2e5+84,mod1=564611849,mod2=80674637;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    return x*f;
}
inline void write(register ll x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return ;
}
struct Edge{
    ll from,to,ne,val;
}e[2][maxn];
ll n,m,s,t,tt,x,y,z,ecnt[2],head[2][maxn],dis[2][maxn],f[2][maxn][2];
inline void add(ll u,ll v,ll w,bool op){
    e[op][ecnt[op]]={u,v,head[op][u],w};
    head[op][u]=ecnt[op]++;
    return ;
}
priority_queue<p,vector<p>,greater<p> >pq;
bitset<maxn> vis;
void dijkstra(ll str,bool op){
    while(!pq.empty())
        pq.pop();
    memset(dis[op],0x3f,sizeof(dis[op]));
    dis[op][str]=0;
    f[op][str][0]=f[op][str][1]=1;
    pq.push({0,str});
    vis.reset();
    while(!pq.empty()){
        tt=pq.top().second;
        pq.pop();
        if(vis[tt])
            continue;
        vis[tt]=1;
        for(ll i=head[op][tt];i;i=e[op][i].ne){
            if(dis[op][e[op][i].to]>dis[op][tt]+e[op][i].val){
                dis[op][e[op][i].to]=dis[op][tt]+e[op][i].val;
                f[op][e[op][i].to][0]=f[op][tt][0]%mod1;
                f[op][e[op][i].to][1]=f[op][tt][1]%mod2;
                pq.push({dis[op][e[op][i].to],e[op][i].to});
            }
            else if(dis[op][e[op][i].to]==dis[op][tt]+e[op][i].val){
                f[op][e[op][i].to][0]=(f[op][e[op][i].to][0]+f[op][tt][0])%mod1;
                f[op][e[op][i].to][1]=(f[op][e[op][i].to][1]+f[op][tt][1])%mod2;
                考场寄在这，直接+1了。。
            }
        }
    }
    return ;
}
int main(){
    n=read();
    m=read();
    s=read()+1;
    t=read()+1;
    ecnt[0]=ecnt[1]=1;
    for(ll i=1;i<=m;i++){
        x=read()+1;
        y=read()+1;
        z=read();
        add(x,y,z,0);
        add(y,x,z,1);
    }
    dijkstra(s,0);
    dijkstra(t,1);
    for(ll i=1;i<ecnt[0];i++){
        printf("%d %d %d Sherry\n",f[0][t][0],f[1][e[0][i].to][0],f[0][e[0][i].from]);
        if(dis[0][e[0][i].from]+e[0][i].val+dis[1][e[0][i].to]==dis[0][t]&&f[0][t][0]%mod1==f[1][e[0][i].to][0]*f[0][e[0][i].from][0]%mod1&&f[0][t][1]%mod2==f[1][e[0][i].to][1]*f[0][e[0][i].from][1]%mod2){
            putchar('Y');
            putchar('E');
            putchar('S');
            putchar('\n');
        }
        else if(dis[0][t]-dis[0][e[0][i].from]-dis[1][e[0][i].to]>1){
            putchar('C');
            putchar('A');
            putchar('N');
            putchar(' ');
            write(e[0][i].val-(dis[0][t]-1-dis[0][e[0][i].from]-dis[1][e[0][i].to]));
            putchar('\n');
        }
        else{
            putchar('N');
            putchar('O');
            putchar('\n');
        }
    }
    return 0;
}
```

被大佬们虐了。

---

## 作者：nekko (赞：4)

首先可以把图正反存一遍，然后跑一下从s到所有点的最短路（正图），以及t到所有点的最短路（反图）

那么一条边 $(u,v,w)$ 在最短路上的条件就是：

$$dis_su+dis_tv=dis_st$$

如何判断一定要经过呢？其实可以直接把最短路图（正权边意义下是个 $DAG$）搞出来，然后当成无向图跑割边

~~由于我不会求割边，所以~~ 介绍另一种做法

设 $cnt_uv$ 表示从 $u$ 到 $v$ 的最短路条数

一条边是必经边，当且仅当：

$$cnt_su \times cnt_tv = cnt_st$$

然而最短路条数是指数级别的，可以想象一下一堆环串联在一块

不过这里只是需要判断是否相等，可以直接在模某个素数意义下判断相等就行了

如果觉得不保险，可以多来几个素数一块判断

``` cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int head[N], rest[N * 2], to[N * 2], w[N * 2];

void add(int u, int v, int w) {
    static int tot = 0;
    to[++ tot] = v, :: w[tot] = w, rest[tot] = head[u], head[u] = tot;
} 

int _head[N], _rest[N * 2], _to[N * 2], _w[N * 2];
void _add(int u, int v, int w) {
    static int tot = 0;
    _to[++ tot] = v, _w[tot] = w, _rest[tot] =  _head[u], _head[u] = tot;
}

struct E {
    int u, v, w;
} e[N];

int n, m, ans[N], s, t;

ll dis[2][N], cnt[2][2][N];
const ll mod[2] = { (ll) (1e9 + 7), 998244853 };

int vis[N];
struct T {
    int u; ll w;
};
bool operator < (T a, T b) {
    return a.w > b.w;
}
const ll inf = 0x3f3f3f3f3f3f3f3fll;
void dij(ll *dis, ll cnt[2][N], int s, int t, int *head, int *rest, int *to, int *w) {
    for(int i = 1 ; i <= n ; ++ i) vis[i] = 0, dis[i] = inf;
    priority_queue<T> pq;
    pq.push((T) { s, dis[s] = 0 });
    cnt[0][s] = 1;
    cnt[1][s] = 1;
    while(pq.size()) {
        int u = pq.top().u; pq.pop();
        if(vis[u]) continue; vis[u] = 1;
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i], wi = w[i];
            if(dis[v] > dis[u] + wi) {
                dis[v] = dis[u] + wi;
                cnt[0][v] = cnt[0][u];
                cnt[1][v] = cnt[1][u];
                pq.push((T) { v, dis[v] });
            } else if(dis[v] == dis[u] + wi) {
                cnt[0][v] = (cnt[0][v] + cnt[0][u]) % mod[0];
                cnt[1][v] = (cnt[1][v] + cnt[1][u]) % mod[1];
            }
        }
    }
}

int main() {
//    freopen("data.in", "r", stdin);
    
    ios :: sync_with_stdio(0);
    cin >> n >> m >> s >> t;
    for(int i = 1 ; i <= m ; ++ i) {
        int u, v, w; cin >> u >> v >> w;
        add(u, v, w);
        _add(v, u, w);
        e[i] = (E) { u, v, w };
    }
    dij(dis[0], cnt[0], s, t, head, rest, to, w);
    dij(dis[1], cnt[1], t, s, _head, _rest, _to, _w);
    
//    for(int i = 1 ; i <= n ; ++ i) cout << dis[0][i] << ' '; cout << endl;
//    for(int i = 1 ; i <= n ; ++ i) cout << dis[1][i] << ' '; cout << endl;
//    for(int i = 1 ; i <= n ; ++ i) cout << cnt[0][0][i] << ' '; cout << endl;
//    for(int i = 1 ; i <= n ; ++ i) cout << cnt[1][0][i] << ' '; cout << endl;
//    for(int i = 1 ; i <= n ; ++ i) cout << cnt[0][1][i] << ' '; cout << endl;
//    for(int i = 1 ; i <= n ; ++ i) cout << cnt[1][1][i] << ' '; cout << endl;
    
    for(int i = 1 ; i <= m ; ++ i) {
        int u = e[i].u, v = e[i].v, w = e[i].w;
//        cout << u << ' ' << v << ' ' << w << ' ' << (dis[0][u] + w + dis[1][v] == dis[0][t])
//        << ((cnt[0][0][u] * cnt[1][0][v]) % mod[0] == cnt[0][0][t])
//        << ((cnt[0][1][u] * cnt[1][1][v]) % mod[1] == cnt[0][1][t]) << endl; 
        if(dis[0][u] + w + dis[1][v] == dis[0][t]
        && (cnt[0][0][u] * cnt[1][0][v]) % mod[0] == cnt[0][0][t]
        && (cnt[0][1][u] * cnt[1][1][v]) % mod[1] == cnt[0][1][t]) {
           cout << "YES" << endl; 
        } else {
            ll del = dis[0][t] - dis[0][u] - dis[1][v];
            if(del <= 1) cout << "NO" << endl;
            else cout << "CAN " << w - del + 1 << endl; 
        }
    }
}
```

---

## 作者：xiaowang656 (赞：2)

# 最短路上的边判定

### 可能在最短路上的边

分别从起点到终点以及从终点到起点两边做dijkstra算法，通过判断这条边的松弛结果是否发生改变就可以判断是否在最短路上，因为对于边权值为w的有向边e=(u,v)，如果最后结果中dis[u]+w=dis[v]成立，说明不存在一条边（或者路径）对这两个端点的松弛具有更好的结果的，也即从u到v的最短路径可能经过这条边。但是仅仅这条结论离我们的要求还是不够的，我们还需要保证存在经过点u的最短以及点v的最短路，这能才能保证点u以及点v可能出现在最短路径上，在这个条件的基础上，结合上一条判断便可以得到我们的要求。

```cpp
if (dis[0][x] + w == dis[0][y] && dis[0][x] + dis[1][x] == dis[0][t] && dis[0][y] + dis[1][y] == dis[0][t])
```

其中dis[0]表示对从s到t做dij的结果，dis[1]表示从t到s做dij的结果。

```cpp
if (dis[0][x] + w + dis[1][y] == dis[0][t])
```

容易证明这两个判断是等价的。

另外注意这里写dij的时候，访问过的点一定要contiune，否则回出现同一个点被加多次的情况。


### 必定在最短路上的边

这个问题的解法我没有想出来，搜到了一道差不多的题目然后看题解才懂的做法。

参考题目[cf_567E](https://codeforces.com/problemset/problem/567/E)

- 利用乘法原理

    我们可以维护一个从起点s到u的路径数量$d_1$和从终点t到v的路径数量$d_2$，如果要满足是必要边的条件，那么必然有从起点s到终点t的路径数量$d_3=d_1\times d_2$。因为数据比较大，需要维护取模。

- 使用割边

    将可能在最短路上的边存起来并建立双向边，可以得到一个无向图，若某条边一定是最短路上的边，说明需要一定通过这条边到达终点，说明这是一条割边。不过注意因为加入的是双向边，所以最后结果可能存的必要边的反向边。

---

## 作者：KarmaticEnding (赞：1)

# 1.心路历程

### 1.分析题目

在什么情况下一条边 $u\rightarrow v$ 在最短路上？很显然，设 $s\rightarrow t$ 的最短路长度为 $l$，那么当且仅当 $d_{s\rightarrow u}+w_{u\rightarrow v}+d_{v\rightarrow t}=l$ 的时候这条边在最短路上。

### 2.错误的思路

__在不看后面的分析的情况下，读者可以尝试证明为什么这个思路是错的。__

我们对于每一条边，在另外一张图上建一个反向的边，然后跑两遍 $\text{Dijkstra}$，一遍在原图上正向跑，用 $dis$ 数组记录：对于每一个点 $u$，$s$ 到 $u$ 的最短路；一遍在另外一张“反图”上跑，用 $invdis$ 数组记录：对于每一个点 $v$，$v$ 到 $t$ 的最短路。

在输出答案的时候，对于每一条边的起点 $u$ 和终点 $v$ 以及权值 $w$：

- 如果 $dis_u+w+invdis_v=dis_t$，那么输出 `YES`。
- 如果 $dis_u+invdis_v\ge dis_t$，也就是说就算边权为最小值 $1$ 都无法使这条边在最短路上，那么输出 `NO`。
- 否则，输出 `CAN`，然后输出 $dis_u+invdis_v+w-dis_t-1$。

现在来分析为什么这个思路是错的。

首先，对于后两种情况，它一定是对的，这个值得肯定。

其次，如果 $dis_u+w+invdis_v=dis_t$，那么这条边就 __一定__ 在最短路上了吗？不一定吧。有可能最短路有很多条，这只是其中一条最短路的一条边而已。

### 3.正确的思路

如你所见，上一个思路虽然错误，但是也有可取之处。

那么，怎么改动上一个思路，使它成为一个真正正确的思路呢？

还是这样的情况：对于 $dis_u+w+invdis_v=dis_t$，它应该怎样处理？

可以把这个情况分为两种情况：

- 它一定在最短路上，输出 `YES`。
- 它不一定在最短路上，输出 `CAN 1`。

如何分析这两种情况？

设 $cnt_u$ 表示 $s$ 到 $u$ 的最短路条数，$invcnt_v$ 表示 $v$ 到 $t$ 的最短路条数。那么如果一条边 $u\rightarrow v$ 一定在最短路上，一定满足关系式：$cnt_u\times invcnt_v=cnt_t$。

说得轻松，怎么维护这个 $cnt$？

观察到一个点 $j$ 的 $cnt$ 仅能够从它的父节点转移过来，所以我们不妨跑完 $\text{Dijkstra}$ 之后，用 $\text{DFS}$ 暴力遍历每个结点，更新 $cnt$ 以及 $invcnt$，最后输出的时候简单处理一下。

两遍 $\text{Dijkstra}$，两遍 $\text{DFS}$，最后时间复杂度就约是 $O(kn)$。（$k$ 是一个不超过 $10$ 的常数）

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,int> PLI;
int n,m,s,t;
const int MAXN=100010;
struct EDGE{
	int beginpoint;
	int endpoint;
	long long weight;
}edge[MAXN];
vector<PLI> g[MAXN];
vector<PLI> inv_g[MAXN];//反向图,每条边都反着建
vector<int> last[MAXN];
ll dis[MAXN],invdis[MAXN],cnt[MAXN],invcnt[MAXN];
bool vis[MAXN],invvis[MAXN];
//跑两遍Dijkstra
priority_queue<PLI,vector<PLI>,greater<PLI> > q,invq;
void Dijkstra(){
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;
	q.push({0,s});
	while(q.size()){
		PLI t=q.top();
		q.pop();
		int u=t.second;
		if(vis[u]){
			continue;
		}
		vis[u]=true;
		for(PLI v:g[u]){
			if(dis[v.second]>dis[u]+v.first){
				dis[v.second]=dis[u]+v.first;//更新距离
				q.push({dis[v.second],v.second});
			}
		}
	}
}
void InverseDijkstra(){
	memset(invdis,0x3f,sizeof(invdis));
	invdis[t]=0;
	invq.push({0,t});
	while(invq.size()){
		PLI t=invq.top();
		invq.pop();
		int u=t.second;
		if(invvis[u]){
			continue;
		}
		invvis[u]=true;
		for(PLI v:inv_g[u]){
			if(invdis[v.second]>invdis[u]+v.first){
				invdis[v.second]=invdis[u]+v.first;//更新距离
				invq.push({invdis[v.second],v.second});
			}
		}
	}
}
ll DFS(int u){
	if(u==s){
		cnt[s]=1;
		return 1;
	}
	else{
		vis[u]=true;
		for(PLI v1:inv_g[u]){
			int v=v1.second;
			if(vis[v]){
				continue;
			}
			if(dis[u]==dis[v]+v1.first){
				cnt[u]+=DFS(v);
			}
		}
		vis[u]=false;
		return cnt[u];
	}
}
ll invDFS(int u){
	if(u==t){
		invcnt[t]=1;
		return 1;
	}
	else{
		invvis[u]=true;
		for(PLI v1:g[u]){
			int v=v1.second;
			if(invvis[v]){
				continue;
			}
			if(invdis[u]==invdis[v]+v1.first){
				invcnt[u]+=invDFS(v);
			}
		}
		invvis[u]=false;
		return invcnt[u];
	}
}
int main(){
	scanf("%d%d%d%d",&n,&m,&s,&t);
	int u,v;
	ll w;
	for(int i=1;i<=m;++i){
		scanf("%d%d%lld",&u,&v,&w);
		edge[i].beginpoint=u;
		edge[i].endpoint=v;
		edge[i].weight=w;
		g[u].emplace_back(w,v);
		inv_g[v].emplace_back(w,u);
	}
	Dijkstra();
	if(dis[t]>=0x3f3f3f3f){
		for(int i=1;i<=m;++i){
			putchar('N');
			putchar('O');
			putchar('\n');
		}
		return 0;
	}
	InverseDijkstra();
	memset(vis,0,sizeof(vis));
	memset(invvis,0,sizeof(invvis));
	DFS(t);
	invDFS(s);
	for(int i=1;i<=m;++i){
		if(dis[edge[i].beginpoint]+invdis[edge[i].endpoint]+edge[i].weight==dis[t]){
			if(cnt[edge[i].beginpoint]*invcnt[edge[i].endpoint]==cnt[t]){
				putchar('Y'),putchar('E'),putchar('S');
			}
			else{
				if(edge[i].weight==1){
					putchar('N');
					putchar('O');
				}
				else{
					putchar('C');
					putchar('A');
					putchar('N');
					putchar(' ');
					putchar('1');
				}
			}
			putchar('\n');
		}
		else{
			if(dis[edge[i].beginpoint]+invdis[edge[i].endpoint]+edge[i].weight+1-dis[t]>=edge[i].weight){
				putchar('N');
				putchar('O');
				putchar('\n');
			}
			else{
				putchar('C');
				putchar('A');
				putchar('N');
				putchar(' ');
				printf("%lld",dis[edge[i].beginpoint]+invdis[edge[i].endpoint]+edge[i].weight+1-dis[t]);
				putchar('\n');
			}
		}
	}
	return 0;
}

```

写得远远没有前面大佬写得短，但是个人认为思路至少是清晰的，点个赞吧QwQ

---

## 作者：ttq012 (赞：1)

有一个常见 trick：设 $s$ 为起点的最短路数量 $D_i$，$t$ 为起点的最短路数量$D'_i$，那么对于一条 $u\to v$ 的边，若有 $D_u\times D'_v=D_t$，那么 $s\to t$ 这条边一定可以出现在最短路上。

那么问题就变得简单了。设 $G'$ 为原图 $G$ 的反图，直接暴力跑出 $D$ 和 $D'$ 来，直接枚举每一条边判定即可。时间复杂度为 $O(m\log m)$。

---

## 作者：George_Je (赞：1)

建议先做这两道题：

[P1629 邮递员送信](https://www.luogu.com.cn/problem/P1629)

[P1608 路径统计](https://www.luogu.com.cn/problem/P1608)

------------

我们重点讨论输出 ```YES``` 的情况。

可以发现，如果走最短路时，某条边 $e$ 一定被经过，那么，这意味着所有的最短路径都会经过 $e$。更形式化地说，$e$ 属于所有从 $s$ 到 $t$ 的最短路径的交集。

我们考虑如何判断一条边 $e$ 是否满足上述条件，这里直接给出做法：

在原图中，以 $s$ 为起点跑一遍 $Dijkstra$，求出 $s$ 到每个点的最短路长度和最短路径数量，记为 $dis [0] [u]$ 和 $cnt [0] [u]$；在原图的反图中，以 $t$ 为起点跑一遍 $Dijkstra$，求出 $t$ 到每个点的最短路长度和最短路径数量（其实这等价于在原图中每个点到 $t$ 的最短路长度和最短路径数量），记为 $dis [1] [u]$ 和 $cnt [1] [u]$。

那么对于一条满足上述条件的边 $e$（从 $u$ 到 $v$ 且权值为 $w$)，其必然满足下列两个条件：

- $dis[0][u]+w+dis[1][v]=dis[0][t]$

- $cnt[0][u]\times cnt[1][v]=cnt[0][t]$

解释一下，第一个式子表示 $e$ 在一条最短路径上；第二个式子运用乘法原理，表示经过 $e$ 的最短路径数量等于所有从 $s$ 到 $t$ 的最短路径数量，那么也就表明所有从 $s$ 到 $t$ 的最短路径都会经过 $e$。遇到这种情况，我们输出 ```YES``` 即可。

至于剩下的情况，本质都一样，也比较简单，这里就略过了。

代码中需要注意的是，由于本题数据非常毒瘤，上述的 $dis$ 数组会爆 ```int```，而 $cnt$ 数组甚至会爆 ```long long```。应对前者开 ```long long``` 即可；至于后者，我们需要对 $cnt$ 数组取模，这里选取的模数是 $1145141$ ，如果实在不放心的话可以选择双模数。

```cpp
#include <bits/stdc++.h>
#define int long long
#define PII pair <int, int>
using namespace std;
constexpr int mod = 1145141;
constexpr int N = 1e5, MAX_N = N + 3;
constexpr int M = 1e5, MAX_M = M + 3;
int n, m;
vector <PII> E [2] [MAX_N];
int dis [2] [MAX_N], cnt [2] [MAX_N];
bool vis [MAX_N];
void Dijkstra (int s, bool d) {
	static priority_queue <PII, vector <PII>, greater <PII>> Q;
	memset (vis, 0, sizeof vis);
	memset (dis [d], 0x3f, sizeof dis [d]);
	cnt [d] [s] = 1;
	Q.push ({dis [d] [s] = 0, s});
	while (!Q.empty ()) {
		int u = Q.top ().second; Q.pop ();
		if (vis [u]) continue;
		vis [u] = 1;
		for (PII i : E [d] [u]) {
			int v = i.first;
			int w = i.second;
			if (dis [d] [u] + w < dis [d] [v]) {
				cnt [d] [v] = cnt [d] [u];
				Q.push ({dis [d] [v] = dis [d] [u] + w, v});
			}
			else if (dis [d] [u] + w == dis [d] [v])
				(cnt [d] [v] += cnt [d] [u]) %= mod;
		}
	}
}
int s, t;
struct edge {int u, v, w;} a [MAX_M];
signed main () {
	ios::sync_with_stdio (false);
	cin.tie (nullptr);
	cout.tie (nullptr);
	cin >> n >> m >> s >> t;
	for (int i = 1; i <= m; ++i) {
		static int u, v, w;
		cin >> u >> v >> w;
		a [i] = {u, v, w};
		E [0] [u].push_back ({v, w});
		E [1] [v].push_back ({u, w});
	}
	Dijkstra (s, 0);
	Dijkstra (t, 1);
	for (int i = 1; i <= m; ++i) {
		static int u, v, w, tmp, d;
		u = a [i].u; v = a [i].v; w = a [i].w;
		d = dis [0] [u] + w + dis [1] [v];
		if (d == dis [0] [t]) {
			if (cnt [0] [u] * cnt [1] [v] % mod == cnt [0] [t]) {
				cout << "YES\n";
				continue;
			}
		}
		tmp = d - dis [0] [t] + 1;
		if (w - tmp > 0) cout << "CAN " << tmp << '\n';
		else cout << "NO\n";
	}
}
```

---

## 作者：Mihari (赞：0)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF567E)

# 题解

对于 `NO` 和 `CAN` 的情况我们其实很好判断，只需要在正向、逆向跑一边 `dijkstra` 得到从 $s,t$ 到某边两点的距离，然后进行判断即可。

最难的情况其实是 `YES` 的情况，我们想一想这种情况出现的情景——在所有的最短路中，这条边没有可以替代的边，即没有其他相同长度的路径有和他同样的效果，称这种性质为“不可替代性”。

发现这种“不可替代性”和桥相似，即无论如何也要走过这条边，才能有最短路。

那么我们考虑把所有有可能是最短路的边建成一个新图，在图上跑 $tarjan$ 找桥，找到的桥即为必走边，输出 `YES`。

剩下两种情况过于简单，不作过多赘述。

话说 CF 数据是真的强，`dijkstra` 把 `<` 打成 `<=` 被卡，$SPFA$ 也被卡了 ~~关于SPFA，它已经死了~~

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13541598.html
```



---

