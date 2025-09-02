# Egor in the Republic of Dagestan

## 题目描述

Egor is a famous Russian singer, rapper, actor and blogger, and finally he decided to give a concert in the sunny Republic of Dagestan.

There are $ n $ cities in the republic, some of them are connected by $ m $ directed roads without any additional conditions. In other words, road system of Dagestan represents an arbitrary directed graph. Egor will arrive to the city $ 1 $ , travel to the city $ n $ by roads along some path, give a concert and fly away.

As any famous artist, Egor has lots of haters and too annoying fans, so he can travel only by safe roads. There are two types of the roads in Dagestan, black and white: black roads are safe at night only, and white roads — in the morning. Before the trip Egor's manager's going to make a schedule: for each city he'll specify it's color, black or white, and then if during the trip they visit some city, the only time they can leave it is determined by the city's color: night, if it's black, and morning, if it's white. After creating the schedule Egor chooses an available path from $ 1 $ to $ n $ , and for security reasons it has to be the shortest possible.

Egor's manager likes Dagestan very much and wants to stay here as long as possible, so he asks you to make such schedule that there would be no path from $ 1 $ to $ n $ or the shortest path's length would be greatest possible.

A path is one city or a sequence of roads such that for every road (excluding the first one) the city this road goes from is equal to the city previous road goes into. Egor can move only along paths consisting of safe roads only.

The path length is equal to the number of roads in it. The shortest path in a graph is a path with smallest length.

## 说明/提示

For the first sample, if we paint city $ 1 $ white, the shortest path is $ 1 \rightarrow 3 $ . Otherwise, it's $ 1 \rightarrow 2 \rightarrow 3 $ regardless of other cities' colors.

For the second sample, we should paint city $ 3 $ black, and there are both black and white roads going from $ 2 $ to $ 4 $ . Note that there can be a road connecting a city with itself.

## 样例 #1

### 输入

```
3 4
1 2 0
1 3 1
2 3 0
2 3 1```

### 输出

```
2
011```

## 样例 #2

### 输入

```
4 8
1 1 0
1 3 0
1 3 1
3 2 0
2 1 0
3 4 1
2 4 0
2 4 1```

### 输出

```
3
1101```

## 样例 #3

### 输入

```
5 10
1 2 0
1 3 1
1 4 0
2 3 0
2 3 1
2 5 0
3 4 0
3 4 1
4 2 1
4 5 0```

### 输出

```
-1
11111```

# 题解

## 作者：Tarsal (赞：9)

## CF1407E 题解

### 题目大意

有一张图，每条边都有一个权值 $0/1$ 。

你现在需要给点染色 $0/1$ ，一条边可以经过有且仅当它的起始点的颜色和边的颜色一样。

问你可不可以使得从 $1 \to n$ 不存在连通的路径，如果不可以，求最短路径，路径长度定义为这条路径上边的数量。

### 题解

这题作为 $2E$ 来说还是挺简单的，算是白给吧。

你考虑一条边什么时候才可以连通，这是取决于它的前一个点。

但是如果你正序的去遍历的话，你肯定会先遍历到它的起始点，但是这个点可能和多个边对应，那怎么处理？

那我们就反着来！！

从 $n$ 号点开始遍历，如果当前的 $2$ 点之间只有一种颜色的边，表示你可以把这条路堵死，那就把它堵死。

如果有 $2$ 种颜色，那么他的节点也就不是什么很重要的问题了。

你会说一个节点会连接多条边，为什么对其他的边没有影响呢？

因为我们做的是 $BFS$ 每个节点只要统计最短的路径，而且每次先被遍历到的一定比下一次遍历到的路径要短，所以直接 $BFS$ 就可以了。

```
#include <iostream>
#include <queue>
#include <string.h>
#include <stdio.h>
using namespace std;
const int maxn = 5e5 + 10;

int n, m, x, y, w, cnt, col[maxn], dis[maxn], vis[maxn], d[maxn], head[maxn];
struct node {
    int nxt, to, val;
} e[maxn << 1];
void add(int x, int y, int w) {
	e[++ cnt].to = y; e[cnt].nxt = head[x]; head[x] = cnt; e[cnt].val = w;
}
queue<int>q;
int main() {
    // cin >> n >> m;
    scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++ i) {
		// cin >> x >> y >> w;
        scanf("%d%d%d", &x, &y, &w);
        add(y, x, w);
	}
	if(n == 1) {
        cout << "0" << endl << "0";
		return 0;
	}
	memset(col, -1, sizeof(col));
	q.push(n);
    vis[n] = 0;
	while(q.size()) {
		int x = q.front(); q.pop();
		if(x == 1) {
            break;
        }
        for(int i = head[x]; i; i = e[i].nxt) {
            int v = e[i].to;
            if(vis[v]) continue;
			if(col[v] == -1 || col[v] == 1 - e[i].val) {
				col[v] = 1 - e[i].val;
			}
            else {
				q.push(v);
				d[v] = d[x] + 1;
				vis[v] = 1;
		    }
        }
	}
    if(d[1]) {
        cout << d[1] << endl;
    }
    else {
        cout << "-1" << endl;
    }
	for(int i = 1; i <= n; ++ i) {
		if(col[i] == -1) {
            cout << "0";
        }
		else {
            cout << col[i];
        }
	}
	return 0;
}
```

---

## 作者：_sh1kong_ (赞：6)

[In Luogu](https://www.luogu.com.cn/problem/CF1407E)

从 $1$ 出发染色不好处理，考虑从 $n$ 出发进行染色，尽可能让每一条路不可经过，这样也是最大化其他点到 $n$ 的最短路。

如果当前为 $u$，点 $v$ 和 $u$ 有边，如果只有一种颜色的边，那么这条路是可以禁止经过的，将 $v$ 设置成与边不同的颜色。如果有不同颜色的边，那么 $v$ 的颜色无论怎么染色都以到达 $u$。

从 $n$ 开始进行反向 BFS 。

当第一遍历到未染色的点 $x$，将点 $x$ 设为与边不同的颜色。如果遍历到染色的点，并且染色的点与边颜色相同，说明此点无法避开，加入到队列中，更新到 $n$ 的最短路，直到 $1$ 入队。

时间复杂度为 $\mathcal{O}(n + m)$。

代码不放。

---

## 作者：AlicX (赞：3)

### 题意  

给定一个由 $n$ 个点，$m$ 条边组成的有向图，每条边的边权分别为 $0$ 或 $1$，让你给每个点染色，同颜色的点与同颜色的边才能连接起来，请你使得点 $1$ 和点 $n$ 不连通，如果不行，最大化他们之间的最短路距离。最后输出染色方案。

## Solution 

发现正着搞很困难，所以正难则反，考虑倒着做。

首先建立反向边，设 $f_{u,w}$ 表示当前在点 $u$，并将点 $u$ 染成 $w$ 这种颜色后离终点的最大的最小距离，并设 $to$ 为 $u$ 可以到达的点。还需要明白一个性质：假设两点之间只有一条线路可达，那么无论边的颜色是什么，只需要将点的颜色染成与边不同的就可以了。接下来直接跑最短路就可以了，注意在松弛时要将放入队列的值取两种颜色状态下的最大值。

注意判断 $n=1$ 的情况。 

```cpp
// Celestial Cyan 
// Luogu uid : 706523 
// Luogu : https://www.luogu.com.cn/problem/CF1407E
// CF : https://codeforces.com/problemset/problem/1407/E
// AT : 
// FTOJ : 
// Contest : Codeforces Round 669 (Div. 2)
// Cnblogs : 
// Memory Limit: 256 MB
// Time Limit: 2000 ms 
// 2023/7/23  

#include<bits/stdc++.h>
//#define int long long
#define x first
#define y second
#define il inline 
#define db double
#define low(x) x&-x
#define ls(x) x<<1
#define rs(x) x<<1|1 
#define pb(x) push_back(x)
#define gcd(x,y) __gcd(x,y) 
#define lcm(x,y) x*y/gcd(x,y) 
#define debug() puts("-------")  
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> PII; 
const int N=5e5+10,K=2,INF=1e9+7; 
int n,m; 
bool st[N];
int dis[N][K]; 
int h[N],idx=0; 
struct Node{
	int w; 
	int to,ne; 
}tr[N]; 
struct Mind{ 
	il bool operator<(Mind &Cyan)const{ } 
}; 
il int read(){  
	int x=0,f=1; char c=getchar();
	while(c<'0'||c>'9'){ if(c=='-') f=-1; c=getchar(); }
	while(c>='0'&&c<='9'){ x=(x<<3)+(x<<1)+c-48; c=getchar(); }
	return x*f; 
} 
il void add(int u,int v,int w){
	tr[idx].w=w,tr[idx].to=v,tr[idx].ne=h[u],h[u]=idx++; 
} 
il void dij(){
	priority_queue<pii> q; 
	memset(st,false,sizeof st); q.push({0,n}); 
	for(int i=1;i<=n;i++) dis[i][0]=dis[i][1]=INF; dis[n][0]=dis[n][1]=0; 
	while(!q.empty()){ 
		int u=q.top().y; q.pop(); 
		if(st[u]) continue; st[u]=true; 
		int Max=max(dis[u][0],dis[u][1]); 
		for(int i=h[u];i!=-1;i=tr[i].ne){
			int to=tr[i].to,w=tr[i].w; 
			if(dis[to][w]>Max+1){ 
				dis[to][w]=Max+1; 
				int Max=max(dis[to][0],dis[to][1]); 
				if(Max<INF) q.push({-Max,to}); 	  
			} 
		} 
	} 
} 
signed main(){   
	memset(h,-1,sizeof h); 
	n=read(),m=read(); 
	while(m--){
		int u=read(),v=read(); 
		int w=read(); add(v,u,w); 
	} dij(); int Max=max(dis[1][0],dis[1][1]); 
	if(n==1){
		puts("0\n0"); 
		return 0; 
	} if(Max<INF) printf("%d\n",Max); else puts("-1"); 
	for(int i=1;i<=n;i++) printf("%d",(dis[i][0]>dis[i][1])?0:1); puts(""); 
	return 0;
} /* */
```

---

## 作者：onglu (赞：2)

## E. Egor in the Republic of Dagestan  
### 题目大意  

一张有向图，可以有重边和自环，每条边有$0,1$标记。  
现在要求给图染色，一个点如果被染成$0$，那么它的$1$出边都要被删去，反之亦然。 
现在要求这张图从$1$到$n$的最短路最长，或者干脆不连通，求出染色方案。  

### 思路  
~~蛮简单的一道图论题~~  

一开始有个直观的想法就是如果能把能到第$n$个点的边全部封上，岂不美哉？  

注意到图中会有重边，并且边的颜色不同，这样就会导致一些边不能被封上。  

再去考虑这些不能被封上的边（一个点到某个后继节点有两个颜色不同的出边），发现这个点的染什么颜色已经不重要了，因为如果能到这个节点，就直接可以往终点走去，再走别的路是浪费时间。   

所以我们就可以从终点出发$bfs$反图，贪心地染色每一条边指向的点，如果该点已经被染色过，说明这条边无法被封上，就把那个点入队，直到必须把$1$号点入队，此时就得到了$1$号点到$n$号点的最短路最大值，至于剩下没被染色的点，任意染色即可。  

### 代码  
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 1009;

int read(){
	char c; int num, f = 1;
	while(c = getchar(),!isdigit(c)) if(c == '-')f = -1; num = c - '0';
	while(c = getchar(), isdigit(c)) num = num * 10 + c - '0';
	return num * f;
}

int n, m, col[N], dis[N], vis[N], d[N];
int head[N], nxt[N], ver[N], edge[N], tot;
void add(int x, int y, int w){
	ver[++tot] = y; nxt[tot] = head[x]; head[x] = tot; edge[tot] = w;
}
queue<int>q;

int main()
{
	n = read(); m = read();
	for(int i = 1; i <= m; i++){
		int x = read(), y = read(), w = read();
		add(y, x, w);
	}
	if(n == 1){
		printf("0\n0\n");
		return 0;
	}
	memset(col, -1, sizeof(col));
	q.push(n); vis[n] = 0;
	while(q.size()){
		int x = q.front(); q.pop();
		if(x == 1)break;
		for(int i = head[x]; i; i = nxt[i])if(!vis[ver[i]]){
			if(col[ver[i]] == -1 || col[ver[i]] == 1 - edge[i]){
				col[ver[i]] = 1 - edge[i];
			}else {
				q.push(ver[i]);
				d[ver[i]] = d[x] + 1;
				vis[ver[i]] = 1;
			}
		}
	}
	printf("%d\n", d[1] ? d[1] : -1);
	for(int i = 1; i <= n; i++){
		if(col[i] == -1)printf("0");
		else printf("%d",col[i]);
	}
	printf("\n");
	return 0;
}
```


---

## 作者：lfxxx (赞：1)

假设一个点的黑色出边点集是 $B_u$ 白色出边点集是 $W_u$。

令 $dis_u$ 表示 $u$ 到 $n$ 的最短路。

那么假若 $\min_{v \in B_u} dis_v \geq \min_{v \in W_u} dis_v$，肯定要把这个点染成黑色，反之染成白色。

也就是假若知道一个点出边的点到 $n$ 的最短路，就可以给这个点染色从而求解这个点的最短路。

于是考虑建立反图，倒着跑最短路，那么假若点 $u$ 在反图上第一次更新了点 $v$，由于边权全部是 $1$，那么点 $v$ 就应该染成和边 $(u,v)$ 不同的颜色，因为点 $u$ 贡献到的颜色集合的最短路一定是最小值。那么就像这样一边跑最短路一边染色即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5+114;
int use[maxn],col[maxn];
int n,m;
int vis[maxn],dis[maxn];
vector<int> E[maxn][2];
priority_queue< pair<int,int> > q;
void solve(){
    memset(dis,0x3f3f3f3f,sizeof(dis));
    dis[n]=0;
    use[n]=1;
    col[n]=0;
    q.push(make_pair(-dis[n],n));
    while(q.size()>0){
        int u=q.top().second;
        q.pop();
        if(vis[u]==1) continue;
        vis[u]=1;
        for(int v:E[u][0]){
            if(use[v]==0){
                use[v]=1;
                col[v]=1;
            }else if(col[v]==0){
                if(dis[v]>dis[u]+1){
                    dis[v]=dis[u]+1;
                    q.push(make_pair(-dis[v],v));
                }
            }
        }
        for(int v:E[u][1]){
            if(use[v]==0){
                use[v]=1;
                col[v]=0;
            }else if(col[v]==1){
                if(dis[v]>dis[u]+1){
                    dis[v]=dis[u]+1;
                    q.push(make_pair(-dis[v],v));
                }
            }
        } 
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,t;
        cin>>u>>v>>t;
        E[v][t].push_back(u);
    }
    solve();
    cout<<(dis[1]<0x3f3f3f3f?dis[1]:-1)<<'\n';
    for(int i=1;i<=n;i++) cout<<col[i];
    return 0;
}
```

---

## 作者：activeO (赞：1)

## 题目大意

 $ n $ 个点 $ m $ 条边的有向图，边有黑白两种颜色。现在要给点染色,白点只能走它连出去的白边，黑点只能走它连出去的黑边。问是否存在一种染色方案，使得不存在一条 $ 1 \rightarrow n $ 的路径。如果存在这样的染色方案，在第一行输出 $ -1 $，否则输出 $ 1 \rightarrow n $ 最长的最短路径长度并输出对应第一行答案的染色方案。

## 思路

首先正序跑的话是不好处理的，因为先遍历到一个点的起始点会对应很多条边。所以我们要倒着推。

然后就可以考虑一个 $ dp_{u,0/1} $ 表示到第 $ u $ 个点选择黑还是白。然后就可以得到 $ dp_{u,0/1} \leftarrow \max{dp_{v,0},dp_{v,1}}+1 $，这里  $ v $ 是对应这颜色的边可以到的点。然后合格就可以放到 dij 里面跑了。

## 代码

**注：变量名略有不同。**

```cpp
#include <bits/stdc++.h>//祝大家学习愉快！

using namespace std;

const int maxn=5e5+5;
const int inf=0x3f3f3f3f;
struct edge{
	int to,nxt,c;
}e[maxn<<1];
int head[maxn],len;
struct node{
	int dis,x;
	node(){}
	node(int dd,int xx){
		dis=dd;
		x=xx;
	}
	bool operator < (const node &b) const {
		return dis>b.dis;
	}
};
priority_queue<node> que;
int dis[maxn][3];
bool vis[maxn];

inline void init(){
	memset(head,-1,sizeof(head));
	memset(dis,0x3f,sizeof(dis));
	len=0;
}
void add(int u,int v,int c){
	e[++len].to=v;
	e[len].c=c;
	e[len].nxt=head[u];
	head[u]=len;
}

void dij(int s){
	dis[s][0]=dis[s][1]=0;
	que.push(node(0,s));
	while(!que.empty()){
		int u=que.top().x;
		que.pop();
		if(vis[u]) continue;
		vis[u]=1;
		int d=max(dis[u][0],dis[u][1]);
		for(int i=head[u];i!=-1;i=e[i].nxt){
			int v=e[i].to,c=e[i].c;
			if(vis[v]) continue;
			if(dis[v][c]>d+1){
				dis[v][c]=d+1;
				int maxx=max(dis[v][0],dis[v][1]);
				if(maxx<inf) que.push(node(maxx,v));
			}
		}
	}
}

int main(){
	
	init();
	
	int n,m;
	
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v,c;
		scanf("%d %d %d",&u,&v,&c);
		add(v,u,c);
	}
	
	dij(n);
	
	int maxx=max(dis[1][0],dis[1][1]);
	
	if(maxx<inf) printf("%d\n",maxx);
	else puts("-1");
	for(int i=1;i<=n;i++){
		if(dis[i][0]>dis[i][1]) putchar('0');
		else putchar('1');
	}
	
	return 0;
}
```


---

## 作者：big_news (赞：1)

[菜鸡的Div2题解](https://big-news.cn/2020/09/09/%E3%80%8C%E8%A7%A3%E9%A2%98%E6%8A%A5%E5%91%8A%E3%80%8DCodeforces%20Round%20669%20(Div.%202)/)

算是我见过的比较裸的一道 E 题了...

设 $f[u,0/1]$ 表示在 $u$ 点，选 0 边还是选 1 边的答案。

转移的话，枚举一条边 $u\gets v$，应当有 $f[u,c]\gets \max(f[v,0],f[v,1])+1$，其中 $c$ 代表边 $u\gets v$ 的颜色。

注意到一个点不会被松弛超过一次，直接跑 Dijkstra 转移即可，时间复杂度 $O((n+m)\log n)$。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
using namespace std;

const int CN = 1e6 + 6;
const int INF = 0x3f3f3f3f;

class fs {public: int to,nxt,tp; void init(int t,int n,int p) {to = t, nxt = n, tp = p;} } E[CN << 1];
int hd[CN], ecnt = 0; void add(int x,int y,int z) {E[++ecnt].init(y, hd[x], z); hd[x] = ecnt;}

int n, m;

class DJ {public: int v, id; bool operator < (const DJ &a) const {return v > a.v;}} ;
DJ mk(int a, int b) {DJ d; d.v = a, d.id = b; return d;}
int d[CN][2]; bool vis[CN]; priority_queue<DJ> Q;
void SP(int u){
    memset(d, 0x3f, sizeof(d)), Q.push( mk(d[u][0] = d[u][1] = 0, u) );
    while(!Q.empty()){
        u = Q.top().id, Q.pop();
        if(vis[u]) continue; vis[u] = true; 
        int dis = max(d[u][0], d[u][1]);
        for(int k = hd[u]; k; k = E[k].nxt){
            int v = E[k].to, c = E[k].tp, cur; if(vis[v]) continue;
            if(d[v][c] > dis + 1){
                d[v][c] = dis + 1, cur = max(d[v][0], d[v][1]);
                if(cur < INF) Q.push( mk(cur, v) );
            }
        }
    }
}

int main()
{
    n = read(), m = read();
    for(int i = 1; i <= m; i++) {int u = read(), v = read(), t = read(); add(v, u, t);}
    SP(n);
    
    if(max(d[1][0], d[1][1]) < INF) printf("%d", max(d[1][0], d[1][1])), puts("");
    else puts("-1");
    for(int i = 1; i <= n; i++) putchar(d[i][0] > d[i][1] ? '0' : '1');
}
```

---

## 作者：laol (赞：0)

## CF1407E 题解

### 思路

考虑建反图，从 $n$ 点出发跑 SPFA 进行染色。

#### solution

不妨设 $u$ 为边的起始点，$v$ 为边的终点，$c$ 为边的颜色。

1. $u$ 未染色，则将其染为与 $c$ 相反的颜色，阻碍该边通行。

1. $u$ 染了 $c$ 颜色，意味着由 $u$ 必然能够通向 $v$，直接将 $u$ 加入队列。

2. $u$ 染了 $c$ 相反的颜色，走不了不管它。

如果 $1$ 号点必须加入队列，那么此时就得到了 $1$ 号点到 $n$ 号点的最短路最大值。

如果还有未染色的点，随意染色即可。

### 参考代码
``` cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch<='9'&&ch>='0')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();return x*f;}

int head[N],tot;
struct edge{int to,nxt,w;}e[N];
void add(int u,int v,int w){e[++tot]={v,head[u],w};head[u]=tot;}

int dis[N],vis[N],col[N];
void bfs(int x){
	memset(dis,0x3f,sizeof dis);
	memset(col,-1,sizeof col);
	memset(vis,0,sizeof vis);
	queue<int>q;
	q.push(x);
	vis[x]=1;dis[x]=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		vis[u]=0;
		for(int v,i=head[u];i;i=e[i].nxt){
			v=e[i].to;
			if(col[v]==-1)col[v]=e[i].w^1;
			else if(col[v]==e[i].w&&dis[v]>dis[u]+1){
					dis[v]=dis[u]+1;
					if(!vis[v])q.push(v),vis[v]=1;
				}
		}
	}
}
int n,m;
int main(){
	cin>>n>>m;
	for(int i=1,u,v,w;i<=m;i++){
		u=read();v=read();w=read();
		add(v,u,w);
	}
	bfs(n);
	for(int i=1;i<=n;i++)if(col[i]==-1)col[i]=1;
	printf("%d\n",(dis[1]==0x3f3f3f3f)?-1:dis[1]);
	for(int i=1;i<=n;i++)printf("%d",col[i]);
	return 0;
}

```

---

## 作者：wangyibo201026 (赞：0)

## solution

首先考虑一个这样的事情：假如目前决策到 $x$ 点，$x$ 的 $0$ 出边的所有点的最短路最小值比 $1$ 出边的所有点的最小值要大，那么根据贪心，我们应该是要染成 $0$ 点的。

因此我们从 $n$ 到 $1$ 进行最短路转移，首先我们建反图，注意到当一个点 $x$ 第一次更新到 $v$ 时，$x$ 一定是 $v$ 的最优转移点，那么 $v$ 的颜色应该与这条边的颜色不同（因为最短一定不优），否则则是一定转移过的点，选择与边同色的点进行转移即可。

---

## 作者：_Flame_ (赞：0)

### $\text{solution}$

正着从 $1$ 开始染色会遇到一个点的起始点对应多条边的情况，不好处理，所以考虑建反图从 $n$ 开始考虑。

设状态 $dp_{i,0/1}$ 表示到点 $i$ 时下一步选 $0$ 边还是 $1$ 边，对于一条从点 $u$ 到点 $v$ 的颜色为 $col$ 边可以得到转移 $dp_{u,col}=\max (dp_{v,0},dp_{v,1})+1$。

注意到每一个点被松弛的次数不会超过一次，直接扔到 Dijkstra 中跑一遍即可。


### $\text{code}$

```cpp
int n,m;

int head[maxn],tot;

struct edge{
	int to,nxt,w;
}e[maxn<<2];

void add(int u,int v,int w){
	e[++tot].nxt=head[u];
	e[tot].to=v;
	e[tot].w=w;
	head[u]=tot;
}

struct Dis{
	int id,dis;
};

bool operator<(Dis x,Dis y){
	return x.dis>y.dis;
}priority_queue<Dis> q;

int dis[maxn][2];
bool vis[maxn];

void dij(int x){
	memset(dis,0x3f,sizeof(dis));
	while(!q.empty()){
		q.pop();
	}
	dis[x][0]=0;
	dis[x][1]=0;
	q.push({x,0});
	while(!q.empty()){
		int u=q.top().id;
		q.pop();
		if(vis[u]){
			continue ;
		}
		vis[u]=1;
		int cnt=max(dis[u][0],dis[u][1]);
//		cout<<cnt<<endl;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(vis[v]){	
				continue ;
			}
			if(dis[v][e[i].w]>cnt+1){
				dis[v][e[i].w]=cnt+1;
				if(max(dis[v][0],dis[v][1])<inf){
					q.push({v,max(dis[v][0],dis[v][1])});
				}
			}
		}
	}
}

void solve(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		add(v,u,w);
	}
	dij(n);
	if(max(dis[1][1],dis[1][0])<inf){
		write(max(dis[1][1],dis[1][0]));
		puts("");
	}
	else{
		puts("-1");
	}
	for(int i=1;i<=n;i++){
		if(dis[i][0]>dis[i][1]){
			write(0);
		}
		else{
			write(1);
		}
	}
	return ;
}

```



---

## 作者：Glassy_Sky (赞：0)

# [[CF1407E]Egor in the Republic of Dagestan](https://www.luogu.com.cn/problem/CF1407E)

## 题目：

$n$ 个点 $m$ 条边的有向图，边有黑白两种颜色。

现在要给点染色，每个点染成黑或白色。

白点只能走它连出去的白边，黑点只能走它连出去的黑边。

问是否存在一种染色方案，使得不存在一条 $1\rightarrow n$ 的路径。如果存在这样的染色方案，在第一行输出 `-1`，否则输出 $1\rightarrow n$ 最长的最短路径长度。在第二行，输出对应第一行答案的染色方案。

## 分析：

如果按正常思路：从节点 1 出发，寻找有没有无法到达节点 n 的染色方案会非常麻烦。

考虑反向搜索，从节点 n 开始扩张一个点集：一定能来到节点 n 的点的集合。

先考虑解决第一个问题，采用贪心策略，尽量不让新节点加入点集。

即尽量给新节点染上 **不同于** **它连接当前点集的边颜色** 的颜色。

如果新节点连接当前点集的边 两种颜色都有，那就没办法了，染什么色都没用，只能让它加入点集。

该策略正确性显然。

最后在该点集扩张完之后，看一看节点 1 在不在点集里面，即可解决第一个问题。

那第二个问题怎么解决？

先明确一点，对于第一个问题处理，我们使用宽搜来扩张点集。

在本题边权为 1 的情况下，宽搜的过程本身就是求最短路的过程。

可以发现，当新节点加入点集时，已经表明不管你给它染上什么色，它都一定连接上了点集中的某点，所以它离节点 n 的最短距离已经确定了，而且这个最短距离 **不受该点颜色的影响** 。

而如果某节点始终都无法加入点集，那它是什么颜色显然对方案没影响。

所以你在解决第一个问题时采用的贪心染色策略，本身就是在 **使最短路最大化** ，而该染色策略没确定颜色的边，自然无所谓你染什么色，随便你输出。

所以问题也就很好解决了。

还有个小坑，节点数为 1 时要特判。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=5e5+5,maxm=5e5+5;

int n,m,col[maxn],dis[maxn];
bool vis[maxn];
struct node {
	int v,col;
};
vector<node>edge[maxn];
queue<int>q;

int main() {
	memset(col,-1,sizeof col);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) {
		int u,v,c;
		scanf("%d%d%d",&u,&v,&c);
		edge[v].push_back({u,c});
	}
	if(n==1) {
		printf("0\n0");
		return 0;
	}
	q.push(n);
	vis[n]=true;
	while(!q.empty()) {
		int now=q.front();
		q.pop();
		for(int i=0;i<edge[now].size();i++) {
			int v=edge[now][i].v,c=edge[now][i].col;
			if(vis[v]) continue;
			if(col[v]==-1) col[v]=1-c;
			else if(col[v]==c) {
				q.push(v);
				dis[v]=dis[now]+1;
				vis[v]=true;
			}
		}
	}
	if(!dis[1]) printf("-1\n");
	else printf("%d\n",dis[1]);
	for(int i=1;i<=n;i++)
		if(col[i]==-1) printf("1");
		else printf("%d",col[i]);
	return 0;
}
```


---

## 作者：GFyyx (赞：0)

## 解题思路
从 $1$ 出发染色不好处理，考虑从 $n$ 出发进行染色，尽可能让每一条路不可经过，这样也是最大化其他点到 $n$ 的最短路，反向建图。

如果当前为 $u$，点 $v$ 和 $u$ 有边，如果只有一种颜色的边，那么这条路是可以禁止经过的。

将 $v$ 设置成与边不同的颜色。如果有不同颜色的边，那么 $v$ 的颜色无论怎么染色都可以到达 $u$。

因此，一个点不会被松弛超过一次，直接跑 Dijkstra 就做完了。

## AC 代码（附有注释）
本人码风较丑，码量不长，不建议抄。

```cpp
#include <iostream>
#include <string.h>
#include <queue>
using namespace std;
struct edge{int to,nxt,w;}e[114514<<4];
int head[114514<<3],tot;
int n,m,dis[2][114514<<3];//颜色为i时的距离
bool vis[114514<<3];
void add(int u,int v,int w){
	e[++tot]={v,head[u],w};
	head[u]=tot;
}//链式前向星
void Dijkstra(){
	memset(dis,0x3f,sizeof(dis));
	dis[0][n]=dis[1][n]=0;
	priority_queue<pair<int,int>> pq;
	pq.push({0,n});
	while(!pq.empty()){
		int u=pq.top().second;
		pq.pop();
		if(vis[u]) continue;
		vis[u]=1;
		int k=max(dis[0][u],dis[1][u]);
		for(register int i=head[u]; i; i=e[i].nxt){
			int v=e[i].to;
			if(dis[e[i].w][v]>k+1&&!vis[v]){
				dis[e[i].w][v]=k+1;
				int maxn=max(dis[0][v],dis[1][v]);
				if(maxn<1919810) pq.push({-maxn,v});
			}//没有重载运算符
		}
	}
}//最短路 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin >> n >> m;
	int u,v,w;
	for(register int i=1; i<=m; i++)
		cin >> u >> v >> w,add(v,u,w);//反向建图
	Dijkstra();
	int maxn=max(dis[0][1],dis[1][1]);
	if(maxn>1919810) maxn=-1;//没更新过maxn,找不到路径
	cout << maxn << endl;
	for(register int i=1; i<=n; i++)//输出染色
		cout << (dis[0][i]<=dis[1][i]);
	return 0;
}

```

---

## 作者：王鲲鹏 (赞：0)

#### 题意：
给出一个有向图，每条边有一个颜色0/1，要求为每个点指定一个颜色，当点的颜色和这条出边的颜色相同时才能走这条边。求最大化从点 $1$ 到 $n$ 的最短路的长度。

#### Solution

如果我们考虑最短路上的一个点 $x$，因为边权都是 $1$，整个图有一种层次感。可以发现点 $x$ 的颜色不影响 $dis[x]$，而会影响从 $x$ 到 $n$ 的最小路。

贪心地，我们可以考虑最大化 $x$ 到 $n$ 的最小距离。

在反图上，从 $n$ 开始 `bfs`，当第一次碰到某个无色点 $x$ 时，将 $x$ 的颜色设置为与这条边的颜色相反。之后再访问到时，且边的颜色与点的颜色相同时，就更新它（并入队列）。显然每个点最多被更新一次。

这样就最大化了每个点到 $n$ 的距离。也就是最大化了 $1$ 到 $n$ 的距离。

#### Codes

```cpp
#include <cstdio>
#include <queue>
int const maxn = 500005;
int n = 0, m = 0;
int head[maxn], nxt[maxn << 1], to[maxn << 1], val[maxn << 1], cnt = 0;
inline void insert(int u, int e, int v) { nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = e; val[cnt] = v; }
int color[maxn], dis[maxn];
int main() {
	scanf("%d %d", &n, &m);
	int x = 0, y = 0, z = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d %d", &x, &y, &z);
		insert(y, x, z);  // 反图
	}
	for (int i = 1; i <= n; ++i)
		color[i] = -1, dis[i] = n * 2;
	color[n] = 0;
	dis[n] = 0;
	std::queue<int> q;
	q.push(n);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = head[x]; i; i = nxt[i]) {
			if (color[to[i]] == -1)
				color[to[i]] = (val[i] ^ 1);
			else {
				if (color[to[i]] == val[i] && dis[to[i]] > dis[x] + 1) {
					dis[to[i]] = dis[x] + 1;
					q.push(to[i]);
				}
			}
		}
	}
	printf("%d\n", dis[1] == 2 * n ? -1 : dis[1]);
	for (int i = 1; i <= n; ++i)
		putchar('0' + (color[i] == -1 ? 0 : color[i]));
	printf("\n");
	return 0;
}
```


---

