# [ABC205F] Grid and Tokens

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc205/tasks/abc205_f

$ H $ 行 $ W $ 列のグリッドがあり、上から $ r $ 行目、左から $ c $ 列目のマスを $ (r,\ c) $ と表します。

$ N $ 個の駒があり、$ i\ \,\ (1\ \leq\ i\ \leq\ N) $ 個目の駒に対しては

- $ A_i\ \leq\ r\ \leq\ C_i $ かつ $ B_i\ \leq\ c\ \leq\ D_i $ を満たすいずれか一つのマス $ (r,\ c) $ に置く
- 置かない

のいずれかを選択することができます。ここで、二つの駒が同じ行や同じ列に存在するような置き方をすることはできません。

最大で何個の駒を置くことができるでしょうか？

## 说明/提示

### 制約

- $ 1\ \leq\ H,\ W,\ N\ \leq\ 100 $
- $ 1\ \leq\ A_i\ \leq\ C_i\ \leq\ H $
- $ 1\ \leq\ B_i\ \leq\ D_i\ \leq\ W $
- 入力は全て整数である。

### Sample Explanation 1

一つ目の駒をマス $ (1,\ 1) $ に、二つ目の駒をマス $ (2,\ 2) $ に置き、三つ目の駒は置かないようにすることで、$ 2 $ 個置くことができます。$ 3 $ 個置くことは不可能であるので、$ 2 $ を出力します。

## 样例 #1

### 输入

```
2 3 3
1 1 2 2
1 2 2 3
1 1 1 3```

### 输出

```
2```

## 样例 #2

### 输入

```
5 5 3
1 1 5 5
1 1 4 4
2 2 3 3```

### 输出

```
3```

# 题解

## 作者：songhongyi (赞：4)

本文同步发表于自建博客：<https://shyblog.rotriw.com/index.php/archives/68/>

题目的内容和范围非常暗示这是一道网络流题目，因而考虑建模。

对于网格的网络流建模，通常是考虑行列分开。我们可以认为每个行和列代表的点分别是点容量限制为 $1$ 的源点和汇点，因此这是一个 $h$ 个源点和 $w$ 个汇点的模型。接下来我们只需要考虑棋子如何在模型中体现。不难想到，棋子其实是一个点容量限制为 $1$ 的点，它允许范围内（$[A_i,C_i]$）的代表行的点流入，流出到范围内（$[B_i,D_i]$）的的代表列的点。

这是一个多源多汇带点容量的网络，我们采取以下的方法：

* 对于多源点，设置一个超级源点流向他们，每条弧的容量限制都是源点的点容量（这道题里是 $1$）；
* 多汇点同理添加超级汇点；
* 对带点权的点拆开，拆成入点和出点，所有入边连向入点，出边从出点连出，入点和出点中容量为这个点的点容量限制（这道题里是 $1$）。

对于第一个样例的情况，我们的模型如下（图片来自官方题解）：

![image](https://img.atcoder.jp/ghi/abc205_f_editorial.jpg)

接下来考虑分析复杂度。不难发现模型的点数是 $O(N+W+H)$ 的，而边数是 $O((W+H)\cdot n)$ 的。

这实际上是一个单位网络，可以证明，在单位网络上的 Dinic 算法的复杂度是 $O(\sqrt m\cdot n)$ 的，可以通过本题。

下面是示例代码：

```cpp
//
// Problem: [ABC205F] Grid and Tokens
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_abc205_f
// Memory Limit: 1 MB
// Time Limit: 2000 ms

#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define maxn 500
#define INF 0x3f3f3f3f

struct Edge
{
    int from, to, cap, flow;

    Edge( int u, int v, int c, int f ) : from( u ), to( v ), cap( c ), flow( f )
    {
    }
};

struct Dinic
{
    int n, m, s, t;
    vector< Edge > edges;
    vector< int > G[ maxn ];
    int d[ maxn ], cur[ maxn ];
    bool vis[ maxn ];

    void init( int n )
    {
        for ( int i = 0; i < n; i++ )
            G[ i ].clear();
        edges.clear();
    }

    void AddEdge( int from, int to, int cap )
    {
        // cerr << from << " " << to << " " << cap << endl;
        edges.push_back( Edge( from, to, cap, 0 ) );
        edges.push_back( Edge( to, from, 0, 0 ) );
        m = edges.size();
        G[ from ].push_back( m - 2 );
        G[ to ].push_back( m - 1 );
    }

    bool BFS()
    {
        memset( vis, 0, sizeof( vis ) );
        queue< int > Q;
        Q.push( s );
        d[ s ] = 0;
        vis[ s ] = 1;
        while ( !Q.empty() )
        {
            int x = Q.front();
            Q.pop();
            for ( int i = 0; i < G[ x ].size(); i++ )
            {
                Edge& e = edges[ G[ x ][ i ] ];
                if ( !vis[ e.to ] && e.cap > e.flow )
                {
                    vis[ e.to ] = 1;
                    d[ e.to ] = d[ x ] + 1;
                    Q.push( e.to );
                }
            }
        }
        return vis[ t ];
    }

    int DFS( int x, int a )
    {
        if ( x == t || a == 0 )
            return a;
        int flow = 0, f;
        for ( int& i = cur[ x ]; i < G[ x ].size(); i++ )
        {
            Edge& e = edges[ G[ x ][ i ] ];
            if ( d[ x ] + 1 == d[ e.to ]
                 && ( f = DFS( e.to, min( a, e.cap - e.flow ) ) ) > 0 )
            {
                e.flow += f;
                edges[ G[ x ][ i ] ^ 1 ].flow -= f;
                flow += f;
                a -= f;
                if ( a == 0 )
                    break;
            }
        }
        return flow;
    }

    int Maxflow( int s, int t )
    {
        this->s = s;
        this->t = t;
        int flow = 0;
        while ( BFS() )
        {
            memset( cur, 0, sizeof( cur ) );
            flow += DFS( s, INF );
        }
        return flow;
    }
} G;
int main()
{
    cin.tie( 0 );
    int n, w, h;
    cin >> h >> w >> n;
    int S = 0, T = 2 * n + w + h + 1;
    for ( int i = 1; i <= h; i++ )
    {
        G.AddEdge( S, i, 1 );
    }
    for ( int i = 1; i <= w; i++ )
    {
        G.AddEdge( h + 2 * n + i, T, 1 );
    }
    for ( int i = 1; i <= n; i++ )
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        for ( int j = a; j <= c; j++ )
        {
            G.AddEdge( j, h + i, 1 );
        }
        for ( int j = b; j <= d; j++ )
        {
            G.AddEdge( h + n + i, h + 2 * n + j, 1 );
        }
        G.AddEdge( h + i, h + n + i, 1 );
    }
    cout << G.Maxflow( S, T ) << endl;
}
```



---

## 作者：_Ponder_ (赞：4)

[Grid and Tokens](https://www.luogu.com.cn/problem/AT_abc205_f)

### 题目大意

给定 $n$ 个点和一个 $H\times W$ 的网格，每个点可以放置在 $(A_i,B_i)$ 到 $(C_i,D_i)$ 的矩形中或不放，每一行或一列只能放置一个点，求最多能放多少个点。

### 思路分析

首先看数据范围，再结合题目给的限制条件，容易发现这是一道网络流。

考虑建图，因为行和列存在限制条件而网格中的点不存在，所以可以考虑将每一行和每一列分别建成一个点。再建立一个超级源点和超级汇点，源点向行连边权为 $1$ 的边，列向汇点连边权为 $1$ 的边。 表示每一行和每一列只能放一个点的限制条件。

对于一个点的矩形放置范围，可以转换为行 $A_i\sim C_i$ 向该点连边权为 $1$ 的边，该点向列 $B_i\sim D_i$ 连边权为 $1$ 的边，表示每一行和每一列对于点的匹配。

同时，点存在容量的限制，所以要将点拆成入点和出点，再连边。

综上所述，建图过程如下：

- 建立源点，汇点。

- 对于每一行和每一列建立一个点，源点向行连边权为 $1$ 的边，列向汇点连边权为 $1$ 的边。

- 对于每一个点，建立入点和出点，入点向出点连边权为 $1$ 的边，行 $A_i\sim C_i$ 向入点连边权为 $1$ 的边，出点向列 $B_i\sim D_i$ 连边权为 $1$ 的边。

![](https://i.imgloc.com/2023/05/30/VtQDwL.png)

因为流网络是单位网络，所以时间复杂度为 $O(n^3)$。($n,H,W$ 同阶)

### 代码

```
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <queue>

using namespace std;
const int N=200100;
#define inf 0x3f3f3f3f

int n,m,k,idx=1,S,T,in1,in2,in3,in4,cnt;
int to[N],nxt[N],head[N],w[N];
int cur[N],d[N];

queue <int> q;

void add(int u,int v,int c){
    idx++;to[idx]=v;nxt[idx]=head[u];head[u]=idx;w[idx]=c;
    idx++;to[idx]=u;nxt[idx]=head[v];head[v]=idx;w[idx]=0;
}

bool bfs(){
    memset(d,-1,sizeof d);
    while(!q.empty()) q.pop();
    cur[S]=head[S];
    q.push(S);d[S]=0;
    while(!q.empty()){
        int now=q.front();q.pop();
        for(int i=head[now];i;i=nxt[i]){
            int v=to[i];
            if(~d[v]||!w[i]) continue;
            d[v]=d[now]+1;
            cur[v]=head[v];
            if(v==T) return 1;
            q.push(v);
        }
    }
    return 0;
}

int dfs(int s,int lim){
    if(s==T) return lim;
    int flow=0;
    for(int i=cur[s];i&&flow<lim;i=nxt[i]){
        int v=to[i];cur[s]=i;
        if(d[v]!=d[s]+1||!w[i]) continue;
        int t=dfs(v,min(w[i],lim-flow));
        if(!t) d[v]=-1;
        w[i]-=t;w[i^1]+=t;flow+=t;
    }
    return flow;
}

int dinic(){
    int ans=0,flow=0;
    while(bfs()) while(flow=dfs(S,inf)) ans+=flow;
    return ans;
}

int main(){
    scanf("%d%d%d",&n,&m,&k);
    S=N-5;T=N-6;cnt=n+m+1;
    for(int i=1;i<=n;i++) add(S,i,1);//源点->行
    for(int i=n+1;i<=n+m;i++) add(i,T,1);//列->汇点
    for(int i=1;i<=k;i++){
        scanf("%d%d%d%d",&in1,&in2,&in3,&in4);
        for(int i=in1;i<=in3;i++) add(i,cnt,1);//行->入点
        for(int i=n+in2;i<=n+in4;i++) add(cnt+1,i,1);//出点->列
        add(cnt,cnt+1,1);//入点->出点
        cnt+=2;
    }
    cout<<dinic()<<'\n';
    return 0;
}
```

---

## 作者：ケロシ (赞：1)

非常好网络流题目，使我建图水平提升。

首先这个每一行每一列最多只有一个棋子的限制，不难想到网络流维护限制。

对于每一行建出节点 $r_i$，然后对于源点建出 $S\to r_i$ 的边，容量为 $1$，即对应每一行最多只有一个棋子的限制。对于每一列同理，建容量为 $1$ 的边 $c_i\to T$。

然后考虑可放的 $n$ 枚棋子，考虑第 $i$ 个棋子，如果它放在 $[A_i,C_i]$ 的行和 $[B_i, D_i]$ 的列内，那么在 $[A_i,B_i]$ 中的一个 $r_p$ 就可以对应到 $[B_i, D_i]$ 中的 $c_q$。考虑建图，增加两个节点 $u$ 和 $v$，对于所有 $[A_i,B_i]$ 内的 $r_p$ 向 $u$ 连边，同样的，$v$ 向所有 $[C_i,D_i]$ 内的 $c_q$ 连边，最后 $u$ 向 $v$ 连边，边的容量都为 $1$，因为只能放一个棋子。这样符合范围内的 $r_p$ 都能对应到符合范围的 $c_q$，就能增加一种放棋子的方案。

例如下图就是 $A_i=1,C_i=2,B_i=2,D_i=3$ 的一个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/lrtybzel.png)

最后跑最大流即为答案。

```cpp
int n, m, k;
void solve() {
	cin >> n >> m >> k;
	Dinic :: init();
	int S = 0, T = n + m + 1;
	int tot = T;
	FOR(i, 1, n) Dinic :: add(S, i, 1);
	FOR(i, 1, m) Dinic :: add(i + n, T, 1);
	REP(_, k) {
		int l1, r1, l2, r2;
		cin >> l1 >> l2 >> r1 >> r2;
		int u = ++tot; int v = ++tot;
		FOR(i, l1, r1) Dinic :: add(i, u, 1);
		FOR(i, l2, r2) Dinic :: add(v, i + n, 1);
		Dinic :: add(u, v, 1);
	}
	cout << Dinic :: dinic(S, T) << endl;
}
```

---

## 作者：happybob (赞：0)

考虑每行一个点，每列一个点。源点 $S$ 向每行连边，每列向汇点 $T$ 连边，容量都是 $1$。

对于每个棋子，新开两个点，一个是行对应的点 $x$，另一个是列对应的 $y$。

发现其行可以在 $[A_i,C_i]$ 中任取，列可在 $[B_i,D_i]$ 中任取。对于 $j \in [A_i,C_i]$，连 $j \rightarrow x$，容量为 $1$。对于 $k \in [B_i,D_i]$，连 $y \rightarrow k$，容量为 $1$。

此外在连一个 $x \rightarrow y$，容量为 $1$。

对于每一条流满的从源点到行的边，意味着存在点占据了这一行，由于连了 $x \rightarrow y$，于是这条边必然会流向一个 $y$，从而流向一个列的点对答案产生最多 $1$ 的贡献。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;

int hs, w, n;
int S, T;

int e[N], h[N], c[N], ne[N], idx, d[N], cur[N];
inline void add(int u, int v, int w)
{
	e[idx] = v, ne[idx] = h[u], c[idx] = w, h[u] = idx++;
	e[idx] = u, ne[idx] = h[v], c[idx] = 0, h[v] = idx++;
}

inline bool bfs()
{
	for (int i = 0; i <= T; i++) d[i] = cur[i] = -1;
	queue<int> q;
	q.push(S);
	d[S] = 0, cur[S] = h[S];
	while (q.size())
	{
		int u = q.front();
		q.pop();
		for (int i = h[u]; ~i; i = ne[i])
		{
			int j = e[i];
			if (c[i] > 0 && d[j] == -1)
			{
				d[j] = d[u] + 1;
				cur[j] = h[j];
				if (j == T) return 1;
				q.push(j);
			}
		}
	}
	return 0;
}

inline int dfs(int u, int lim)
{
	if (u == T) return lim;
	int sum = 0;
	for (int i = cur[u]; ~i && sum < lim; i = ne[i])
	{
		cur[u] = i;
		int j = e[i];
		if (c[i] > 0 && d[j] == d[u] + 1)
		{
			int w = dfs(j, min(c[i], lim - sum));
			if (!w) d[j] = -1;
			sum += w;
			c[i] -= w;
			c[i ^ 1] += w;
		}
	}
	return sum;
}

inline int dinic()
{
	int res = 0;
	while (bfs())
	{
		int p;
		while (p = dfs(S, INT_MAX)) res += p;
	}
	return res;
}

int main()
{
	memset(h, -1, sizeof h);
	scanf("%d%d%d", &hs, &w, &n);
	T = hs + w + 2 * n + 1;
	for (int i = 1; i <= hs; i++) add(S, i, 1);
	for (int i = 1; i <= w; i++) add(i + hs, T, 1);
	for (int i = 1; i <= n; i++)
	{
		int u1 = hs + w + i, u2 = hs + w + i + n;
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		for (int j = a; j <= c; j++)
		{
			add(j, u1, 1);
		}
		add(u1, u2, 1);
		for (int j = b; j <= d; j++)
		{
			add(u2, j + hs, 1);
		}
	}
	printf("%d\n", dinic());
	return 0;
}
```



---

