# [JSOI2008] Blue Mary的旅行

## 题目描述

在一段时间之后，网络公司终于有了一定的知名度，也开始收到一些订单，其中最大的一宗来自 B 市。

Blue Mary 决定亲自去签下这份订单。为了节省旅行经费，他的某个金融顾问建议只购买 U 航空公司的机票。 U 航空公司的所有航班每天都只有一班，并且都是上午出发当天下午到达的，所以他们每人每天只能坐一班飞机。

经过调查，他们得到了 U 航空公司经营的所有航班的详细信息，这包括每一航班的出发地，目的地以及最多能买到的某一天出发的票数。(注意: 对于一个确定的航班，无论是哪一天，他们最多能买到的那一天出发的票数都是相同的）。

Blue Mary 注意到他们一定可以只乘坐 U 航空公司的航班就从 A 市到达 B 市，但是，由于每一航班能买到的票的数量的限制，他们所有人可能不能在同一天到达 B 市。

所以现在 Blue Mary 需要你的帮助，设计一个旅行方案使得最后到达B市的人的到达时间最早。

## 说明/提示

对于 $100\%$ 的数据，$2\le N\le 50,1\le M\le 2450,1\le T,z\le 50,1\le x,y\le N,x\neq y$。

## 样例 #1

### 输入

```
3 3 5
1 2 1
2 3 5
3 1 4
```

### 输出

```
6
```

# 题解

## 作者：chihik (赞：4)

这道题貌似很多人用的是网络流+分层图。这里介绍一种费用流解法。

可以证明，最后一个人到达的时间是小于第100天的。

那么对于每一趟航班，如果他的起点是$u$，终点为$v$，可搭乘的人的数量为$w$。那我们就对$(u,v)$连100条流量为$w$,费用为$i$的边（$i$表示第几天），分别表示第$i$天的航班。

我们跑费用流时，也不是计算最短距离，而是找到起点到终点的一条路径上的一条费用最大的边的最小值。

比如

![1.PNG](https://i.loli.net/2019/10/22/CDAfuEbINWJkQTw.png)

我们要的路径是$A \to C \to D$,因为$max(AC,CD)<max(AB,BD)$

跑一个流量为$t$的费用流即可。

```cpp
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
#define INF 0x3f3f3f3f

const int MAXN = 5005;
int flow , cost;
int n , m , u , v , w , f;
struct node{
	int v , w , f , rev;
};
vector< node > Graph[ MAXN + 5 ];

int dis[ MAXN + 5 ] , vis[ MAXN + 5 ];
int prevv[ MAXN + 5 ] , preve[ MAXN + 5 ];
void spfa( int s , int t ) {
	queue< int > Que;
	memset( dis , 0x3f , sizeof( dis ) );
	memset( vis , 0 , sizeof( vis ) );

	dis[ s ] = 0 , vis[ s ] = 1 , Que.push( s );
	while( !Que.empty( ) ) {
		int u = Que.front( );
		Que.pop( ) , vis[ u ] = 0;

		for( int i = 0 ; i < Graph[ u ].size( ) ; i ++ ) {
			int v = Graph[ u ][ i ].v , w = Graph[ u ][ i ].w;
			if( w <= dis[ u ] ) continue;	//保证一天只坐一班飞机
			if( Graph[ u ][ i ].f && dis[ v ] > max( dis[ u ] , w ) ) {
				dis[ v ] = max( dis[ u ] , w );
				prevv[ v ] = u , preve[ v ] = i;
				if( !vis[ v ] )
					Que.push( v ) , vis[ v ] = 1;
			}
		}
	}
}
void Costflow( int S , int T ) {
	while( 1 ) {
		spfa( S , T );
		if( !flow || dis[ T ] == INF ) return;
		
		int d = INF;
		for( int v = T ; v != S ; v = prevv[ v ] )
			d = min( d , Graph[ prevv[ v ] ][ preve[ v ] ].f );
		flow -= d , cost = max( cost , dis[ T ] );
		for( int v = T ; v != S ; v = prevv[ v ] ) {
			Graph[ prevv[ v ] ][ preve[ v ] ].f -=d;
			Graph[ v ][ Graph[ prevv[ v ] ][ preve[ v ] ].rev ].f += d;
		}
	}
}

int main( ) {
	scanf("%d %d %d",&n,&m,&flow);
	for( int i = 1 ; i <= m ; i ++ ) {
		scanf("%d %d %d",&u,&v,&f);
		for( int j = 1 ; j <= 105 ; j ++ ) {
			w = j;
			Graph[ u ].push_back( { v , w , f , Graph[ v ].size( ) } );
			Graph[ v ].push_back( { u , -w , 0 , Graph[ u ].size( ) - 1 } );
		}
	}
	Costflow( 1 , n );
	printf("%d\n",cost);
	return 0;
}
```

Update: 2021.1.5

深深的体会到 1 年前的自己太菜了。

考虑这道题的加强版：[BZOJ4669 抢夺](https://darkbzoj.tk/problem/4669)

唯一不同的是，这道题的人数很大，所以不能建分层图。

有两个显然的结论：

- 每天可以新到达的人数一定不降

- 后面的人可以跟着前面的人走，时间相差 1 天

但是可能过程中存在一条新的最短路，让这些跟别人走的人，通过新的最短路到达终点，这样就不会有 1 天的时差了。

所以每次增广后通过时间差值判断通过人数，无增广路之后用最大流计算。

为了保证尽量少的时间通过的人数多，用费用流增广。

这样做就不需要二分了。

~~如果你没有发现它是多测，就会像我一样爆零。~~

```cpp
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define Inf 0x3f3f3f3f

const int MAXN = 1000 , MAXM = 5000;
int head[ MAXN + 5 ] , Enum = 1;
struct Edge {
	int v , nxt , flw , w;
	Edge(){}
	Edge( int V , int Nxt , int Flw , int W ) { v = V , nxt = Nxt , flw = Flw , w = W; }
} Graph[ 2 * MAXM + 5 ];
void Add_Edge( int u , int v , int flw , int c ) {
	Graph[ ++ Enum ] = Edge( v , head[ u ] , flw ,  c ); head[ u ] = Enum;
	Graph[ ++ Enum ] = Edge( u , head[ v ] , 0   , -c ); head[ v ] = Enum;
}

int dis[ MAXN + 5 ]; bool inq[ MAXN + 5 ];
int cur[ MAXN + 5 ]; bool vis[ MAXN + 5 ];
bool Spfa( int s , int t ) {
	queue< int > Que;
	memset( dis , 0x3f , sizeof( dis ) );
	memset( inq , 0 , sizeof( inq ) );
	memset( vis , 0 , sizeof( vis ) );
	memcpy( cur , head , sizeof( head ) );
	dis[ s ] = 0; Que.push( s ) , inq[ s ] = 1;
	while( !Que.empty() ) {
		int u = Que.front();  Que.pop() , inq[ u ] = 0;
		for( int i = head[ u ] ; i ; i = Graph[ i ].nxt ) {
			int v = Graph[ i ].v , flw = Graph[ i ].flw , w = Graph[ i ].w;
			if( flw && dis[ v ] > dis[ u ] + w ) {
				dis[ v ] = dis[ u ] + w;
				if( !inq[ v ] ) Que.push( v ) , inq[ v ] = 1;
			}
		}
	}
	return dis[ t ] != Inf;
}
int dfs( int u , int t , int f ) {
	if( u == t ) return f; vis[ u ] = 1;
	for( int &i = cur[ u ] ; i ; i = Graph[ i ].nxt ) {
		int v = Graph[ i ].v , flw = Graph[ i ].flw , w = Graph[ i ].w;
		if( flw && dis[ v ] == dis[ u ] + w && !vis[ v ] ) {
			int mf = dfs( v , t , min( f , flw ) );
			if( mf ) {
				Graph[ i ].flw -= mf , Graph[ i ^ 1 ].flw += mf;
				return mf;
			}
		}
	} dis[ u ] = Inf;
	return 0;
}

int n , m , k , s , t;
int main( ) {
    // freopen("snatch.in","r",stdin);
    // freopen("snatch.out","w",stdout);

    while( ~scanf("%d %d %d",&n,&m,&k) ) {
        memset( head , 0 , sizeof( head ) ); Enum = 1;

        s = 1 , t = n;
        for( int i = 1 , u , v , c ; i <= m ; i ++ ) {
            scanf("%d %d %d",&u,&v,&c);
            Add_Edge( u , v , c , 1 );
        }

        if( k == 0 ) { printf("0\n"); }
        else {
            int Maxf = 0 , last = 0;
            for( ; Spfa( s , t ) ; last = dis[ t ] ) {
                int nowf = 0; for( int fl = 0 ; ( fl = dfs( s , t , Inf ) ) != 0 ; nowf += fl );

                if( k <= ( dis[ t ] - last ) * Maxf ) { 
                    printf("%d\n", last - 1 + (int)ceil( k * 1.0 / Maxf ) ) & 0;
                    goto there;
                }

                k -= ( dis[ t ] - last ) * Maxf;
                Maxf += nowf;
            }
            if( last == 0 ) { puts( "No solution" ); goto there; }
            printf("%d\n", last - 1 + (int)ceil( k * 1.0 / Maxf ) ) & 0;
        }
        there:;
    }
    return 0;
}
```

---

## 作者：Newuser (赞：2)

对于原题，我们很容易想到是一个网络流模型，看到这个最大值最小，我们能够想到二分。然后呢，我们还要考虑到这个限制条件－－每天只能走一步。那么其实我们对于每一天分层就可以了，上一天的点向下一条边的点连边，分成若干天层，如果在分层图下最大流能跑出ｔ个人，也就满足了题意。

再一深思,我们发现，其实二分很麻烦，每次边都要重构一下，原来跑出来的信息都不能保留。那么我们迭代加深的每次新建图，再跑最大流就可以了。

[欢迎来Newuser小站van!](http://www.newuser.top/2018/12/26/%E3%80%90jsoi2008blue-mary%E7%9A%84%E6%97%85%E8%A1%8C%E3%80%91%E5%88%86%E5%B1%82%E5%9B%BE%E6%9C%80%E5%A4%A7%E6%B5%81/)

isap code:
```cpp
#include<stdio.h>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<iostream>
#include<queue>

using namespace std;
const int maxm = 500005;
int en[maxm],nt[maxm],la[maxm],owo=1,v[maxm];
void adg(int x,int y,int z) {
	en[++owo]=y; nt[owo]=la[x]; la[x]=owo; v[owo]=z;
	en[++owo]=x; nt[owo]=la[y]; la[y]=owo; v[owo]=0;
}
int tot;
int n,m,t,S,T;
int X[2555],Y[2555],Z[2555];
int dis[maxm],cnt[maxm];
int sap(int x,int flow) {
	if(x==T) return flow;
	int dlt = 0;
	for(int it=la[x];it;it=nt[it]) {
		int y = en[it];
		if(v[it]&&dis[y]+1==dis[x]) {
			int tmp = sap(y,min(flow-dlt,v[it]));
			v[it]-=tmp; v[it^1]+=tmp;
			dlt +=tmp;
			if(dlt==flow||dis[S]>=tot) return dlt;
		}
	}
	cnt[dis[x]]--;
	if(cnt[dis[x]]==0) dis[S] = tot;
	dis[x]++;
	cnt[dis[x]]++;
	return dlt;
}
int getmaxflow() {
	for(int i=0;i<=tot;i++) cnt[i]=dis[i]=0;
	int sm = 0;
	while(dis[S]<tot) sm+=sap(S,0x3f3f3f3f);
	return sm;
}
int DY[205][105];
int main() {
	scanf("%d%d%d",&n,&m,&t);
	S = ++tot; T = ++tot;
	for(int i=1;i<=m;i++) {
		scanf("%d%d%d",&X[i],&Y[i],&Z[i]);	
	}
	for(int i=1;i<=n;i++) DY[0][i] = ++tot;
	adg(S,DY[0][1],t);
	adg(DY[0][n],T,t);
	int flow = 0;
	for(int tim=1;;tim++) {
		for(int i=1;i<=n;i++) DY[tim][i] = ++tot,adg(DY[tim-1][i],tot,0x3f3f3f3f);
		for(int i=1;i<=m;i++) {
			adg(DY[tim-1][X[i]],DY[tim][Y[i]],Z[i]);
		}
		adg(DY[tim][n],T,t);
		flow += getmaxflow();
		if(flow==t) {
			printf("%d",tim);
			exit(0);
		}
	}
}
```

---

## 作者：Reanap (赞：1)

[洛谷链接](https://www.luogu.com.cn/problem/P4400)

这是一道很有意思的题目。

经过一番化简，我们可以把题目理解为求得最少使所有人都到达的最少时间为 $day$ ，同时对于这个时间我们找到了若干条不冲突的方案 $dis_i$ 和 $p_i$ 表示路径的长度和一批有多少人到达，使得其满足：

$$
k \le \sum (k - dis_i + 1) \times p_i
$$

化简可得：

$$
k + \sum dis_i \times p_i \le k \times \sum p_i
$$

因此我们只要求得了 $\sum p_i$ 和 $\sum dis_i \times p_i$ 就可以快速求得答案。

我们发现他的单位时间内的限制与网络流的流量限制很像，同时 $\sum dis_i \times p_i$ 又和费用流的费用计算很像，因此我们考虑使用费用流辅助。但是由于总流量不确定，我们考虑枚举总流量。容易发现，在前期费用增长比较缓慢，而后期变化量较大，因此这是一个单峰函数，可以三分。

注意，在三分时，我们要把天数以浮点数形式比较，以防止在向上去整后平台的出现对正确性的影响。（~~虽然没有任何一个数据卡了这一点~~）

得到如下代码：

```cpp
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;

template <typename T>
void read(T &x) {
	T f=1;x=0;char s=getchar();
	while(s<'0'||s>'9') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=(x<<3)+(x<<1)+(s^'0');s=getchar();}
	x *= f;
}

const int MAXN = 1e5 + 5;
const int MAXM = 1e5 + 5;
const LL inf = 1e15;

int head[MAXN] , to[MAXM << 1] , nxt[MAXM << 1] , cnt = 1;
LL edge[MAXM << 1] , val[MAXM << 1];
void add(int u , int v , LL c , LL w) {
	nxt[++cnt] = head[u];head[u] = cnt;to[cnt] = v;edge[cnt] = c;val[cnt] = w;
	nxt[++cnt] = head[v];head[v] = cnt;to[cnt] = u;edge[cnt] = 0;val[cnt] = -w;
}

int las[MAXN] , pre[MAXN] , num , s , t , vis[MAXN];
LL dis[MAXN] , flow[MAXN];

struct MinCostMaxFlow {
	LL MaxFlow , MinCost;
	bool bfs() {
		for (int i = 1; i <= num; ++i) las[i] = 0 , dis[i] = inf , pre[i] = 0 , flow[i] = 0 , vis[i] = 0;
		flow[s] = inf , dis[s] = 0;
		queue <int> q;q.push(s);
		int flag = 0;
		while(!q.empty()) {
			int x = q.front();
			q.pop();
			vis[x] = 0;
			for (int i = head[x]; i; i = nxt[i]) {
				if(!edge[i]) continue;
				int v = to[i];
				if(dis[v] > dis[x] + val[i]) {
					dis[v] = dis[x] + val[i];
					flow[v] = min(flow[x] , edge[i]);
					pre[v] = x;
					las[v] = i;
					if(v == t) {
						flag = 1;
						continue;
					}
					if(!vis[v]) vis[v] = 1 , q.push(v);
				}
			}
		} 
		return flag;
	}
	void MVMC() {
		MaxFlow = 0 , MinCost = 0;
		while(bfs()) {
			int now = t;
			MaxFlow += flow[t];
			MinCost += dis[t] * flow[t];
			while(now != s) {
				edge[las[now]] -= flow[t];
				edge[las[now] ^ 1] += flow[t];
				now = pre[now];
			}
		}
	} 
}MIN;

int n , m , k;

double cal(int x) {
	for (int i = 2; i <= cnt; i += 2) edge[i] += edge[i ^ 1] , edge[i ^ 1] = 0;
	edge[cnt - 1] = x;
	MIN.MVMC();
	return (k + MIN.MinCost) * 1.0 / MIN.MaxFlow;
}

int main() {
//	freopen("snatch.in" , "r" , stdin);
//	freopen("snatch.out" , "w" , stdout)
	while(scanf("%d %d %d" , &n , &m , &k) != EOF) {
		num = n + 2;
		s = n + 2 , t = n;
		for (int i = 1; i <= m; ++i) {
			int u , v , c;
			read(u),read(v),read(c);
//			u ++ , v ++;
			add(u , v , c , 1);
		}
		if(!k) {
			puts("0");
			cnt = 1;
			for (int i = 1; i <= num; ++i) head[i] = 0; 
			continue;
		}
		add(s , 1 , inf , 0);
		MIN.MVMC();
		if(MIN.MaxFlow == 0) {
			puts("No solution");
			cnt = 1;
			for (int i = 1; i <= num; ++i) head[i] = 0; 
			continue;
		}
		int l = 1 , r = MIN.MaxFlow;
		LL ans = (k + MIN.MinCost + MIN.MaxFlow - 1) / MIN.MaxFlow - 1;
		while(l <= r) {
			int mid = (l + r) >> 1;
			double ans1 = cal(mid) , ans2 = cal(mid + 1);
			if(ans1 > ans2) l = mid + 1 , ans = min(ans , (LL)ceil(ans2));
			else r = mid - 1 , ans = min(ans , (LL)ceil(ans1));
		}
		printf("%lld\n" , ans);
		cnt = 1;
		for (int i = 1; i <= num; ++i) head[i] = 0; 
	}
	
	return 0;
}
```

---

