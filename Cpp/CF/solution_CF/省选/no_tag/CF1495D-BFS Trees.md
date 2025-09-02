# BFS Trees

## 题目描述

We define a spanning tree of a graph to be a BFS tree rooted at vertex $ s $ if and only if for every node $ t $ the shortest distance between $ s $ and $ t $ in the graph is equal to the shortest distance between $ s $ and $ t $ in the spanning tree.

Given a graph, we define $ f(x,y) $ to be the number of spanning trees of that graph that are BFS trees rooted at vertices $ x $ and $ y $ at the same time.

You are given an undirected connected graph with $ n $ vertices and $ m $ edges. Calculate $ f(i,j) $ for all $ i $ , $ j $ by modulo $ 998\,244\,353 $ .

## 说明/提示

The following picture describes the first example.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1495D/486abdf550a50f53b4082318f3f6f5d586f1cd1e.png)

The tree with red edges is a BFS tree rooted at both $ 1 $ and $ 2 $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1495D/013a1802bccfe9c4bb22292e3e88d7aeac59bc95.png)

Similarly, the BFS tree for other adjacent pairs of vertices can be generated in this way.

## 样例 #1

### 输入

```
4 4
1 2
2 3
3 4
1 4```

### 输出

```
2 1 0 1
1 2 1 0
0 1 2 1
1 0 1 2```

## 样例 #2

### 输入

```
8 9
1 2
1 3
1 4
2 7
3 5
3 6
4 8
2 3
3 4```

### 输出

```
1 0 0 0 0 0 0 0
0 2 0 0 0 0 2 0
0 0 1 0 1 1 0 0
0 0 0 2 0 0 0 2
0 0 1 0 1 1 0 0
0 0 1 0 1 1 0 0
0 2 0 0 0 0 2 0
0 0 0 2 0 0 0 2```

# 题解

## 作者：feecle6418 (赞：13)

Fun fact：这题本来是 D1B。

数据范围很小，考虑对所有 $(i,j)$ 分别求解。

假如 $i\sim j$ 的最短路不止两条，则显然不存在合法解。这可以开始时用 BFS $O(nm)$ 判断。

否则，BFS 树中一定包含在 $i\to j$ 的最短路上的所有点。考虑其它每个点 $x$ 在 $(i,j)$ 的 BFS 树上面的父亲 $y$ 须满足的条件。显然是 $x,y$ 之间有边，$dis(y,i)+1=dis(x,i)$ 且 $dis(y,j)+1=dis(x,j)$。

对于所有 $x$ 把满足上式的 $y$ 的个数相乘就是答案。时间复杂度 $O(n^2m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=998244353;
int n,m,ans[405][405],cnt[405][405],dis[405][405],X[605],Y[605];
vector<int> g[405];
void bfs(int fr){
	queue<int> q;
	memset(dis[fr],0x3f,sizeof(dis[fr])),dis[fr][fr]=0,cnt[fr][fr]=1,q.push(fr);
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int y:g[x]){
			if(dis[fr][y]>dis[fr][x]+1)dis[fr][y]=dis[fr][x]+1,cnt[fr][y]=cnt[fr][x],q.push(y);
			else if(dis[fr][y]==dis[fr][x]+1)cnt[fr][y]=min(cnt[fr][y]+cnt[fr][x],2);
		}
	}
}
int Calc(int x,int y){
	int ans=1;
	for(int i=1;i<=n;i++){
		if(dis[x][i]+dis[y][i]==dis[x][y])continue;
		int cnt=0;
		for(int j:g[i])if(dis[x][j]+1==dis[x][i]&&dis[y][j]+1==dis[y][i])cnt++;
		ans=1ll*ans*cnt%mod;
	}
	return ans;
}
int main(){
	cin>>n>>m;
	for(int i=1,x,y;i<=m;i++)cin>>x>>y,g[x].push_back(y),g[y].push_back(x),X[i]=x,Y[i]=y;
	for(int i=1;i<=n;i++)bfs(i);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			//cout<<"C:"<<i<<' '<<j<<' '<<cnt[i][j]<<endl;
			if(cnt[i][j]==2){
				printf("0 ");
				continue;
			}
			printf("%d ",Calc(i,j));
		}
		puts("");
	}
    return 0;
}
```

---

## 作者：hater (赞：7)

~~写完直呼妙啊~~

这个数据范围不大 , 应该是枚举 $i$ 和 $j$ 之后求解 . 

显然如果 $i$ 到 $j$ 的最短路径方案数大于一 : 这种情况答案为零 . 

因为我们删去最短路上的环上任意一条边 , 都会使得一些端点不满足题目的要求 .~~自己画个图~~ 

我们考虑 把节点以到$i$的距离排序 从 $i$ 节点开始保留树边 , 

（ 换一种思维视角 也就是从$i$节点开始 **一层层** 地向外拓展 ）

那么对于原图的一条边 $(x,y)$ 他能保留的条件是 : 

$d_{i,y} = d_{i,x}+1$ 且 $d_{j,y} = d_{j,x}+1$ 

但是这并不完全 : 

如果一个节点不在从$i$到$j$的路径上 它一定会满足两个条件 ;

如果一个节点在从$i$到$j$的路径上 它不满足后面那个条件 .

但是我们已经知道了 $i$ 到 $j$ 的最短路径方案数一定等于一

换句话说 从$i$到$j$的树边一定是唯一的 那么我们只要忽略这些边就好了 . 

由于这里的最短路是确定的 , 边的保留与否无后效性 , 可以直接上乘法原理 . 

说点小细节 ： 

判最短路唯一可以用到$i$和$j$的距离和等于$i$到$j$的距离 

把节点以到$i$的距离排序可以在求最短路的时候顺便求出 ~~这个憨批懒得改了（虽然时间复杂度都变大了）~~ 

```cpp
#include<bits/stdc++.h> 
#define rg register 
#define fp( i , x , y ) for( rg int i=(x); i<=(y); ++i ) 
#define fq( i , x , y ) for( rg int i=(y); i>=(x); --i ) 
#define i60 long long 
#define dou double 
using namespace std ; 
const int N = 405 , skc = 998244353 ;  
vector <int> v[N] ; 
int n , m , d[2][N] , c[N] , s[2] , ans[N][N] , b[N] ;     
void add( int x , int y ) { v[x].push_back(y) ; }  
queue <int> q ; 
bool cmp( int x , int y ) { return d[0][x] < d[0][y] ; } 
void work( int w ) { 
  int x = s[w] ; 
  memset( d[w] , -1 , sizeof(d[w]) ) ; 
  q.push( x ) ; d[w][x] = 0 ; 
  while( q.size() ) { 
    x = q.front() ; q.pop() ;  
    int l = v[x].size() , y ; 
    fp( i , 0 , l-1 ) { 
      y = v[x][i] ; 
      if( d[w][y] != -1 ) continue ; 
	  d[w][y] = d[w][x] + 1 ; 
	  q.push( y ) ;  
	} 
  } 
} 
signed main() { 
  ios::sync_with_stdio(false) ; 
  cin.tie(0) ; 
  cin >> n >> m ; 
  int x , y ; 
  fp( i , 1 , n ) b[i] = i ; 
  fp( i , 1 , m ) cin >> x >> y , add( x , y ) , add( y , x ) ;  
  fp( i , 1 , n ) fp( j , i , n ) { 
    s[0] = i ; s[1] = j ; work( 0 ) ; work( 1 ) ; 
	int cnt = 0 , dis = d[0][j] ;  
	fp( k , 1 , n ) cnt += ( d[0][k] + d[1][k] == dis ) ; 
	if( cnt != dis+1 ) { ans[i][j] = 0 ; continue ; } 
	sort( b+1 , b+1+n , cmp ) ; 
	int nw = 1 ;  
	fp( k , 1 , n ) { 
	  x = b[k] ; 
	  if( d[0][x] + d[1][x] != dis ) nw = 1ll * nw * c[x] % skc ; 
	  fp( p , 1 , (int)v[x].size() ) { 
	    y = v[x][p-1] ; 
	    if( d[0][y] == d[0][x]+1 && d[1][y] == d[1][x] + 1 ) c[y] ++ ; 
	  } 
	} 
	ans[i][j] = nw ; 
	fp( k , 1 , n ) c[k] = 0 ;  
  } 
  fp( i , 1 , n ) {  
    fp( j , 1 , n ) cout << ans[min(i,j)][max(i,j)] << ' ' ; 
	cout << '\n' ; 
  } 
  return 0 ; 
} 

```



---

## 作者：Cherished (赞：4)

---
title: CF1495D BFS Trees
---

### 题目描述

定义一个图的生成树是以节点 ```s``` 为根的 ```BFS``` 树，当且仅当对任意节点 ```t```，图中 ```s``` 到 ```t``` 的最短路径长度等于树上 ```s``` 到 ```t``` 的最短路径长度。

对于一个图，定义 ```f(x, y)``` 为该图满足「同时是以节点 ```x``` 为根的 ```BFS``` 树和以节点 ```y``` 为根的 ```BFS``` 树」的生成树数量。

给出一个 ```n``` 个节点 ```m``` 条边的无向连通图，请对每对 ```i, j``` 计算 ```f(i, j)``` 对 ```998244353``` 取模的值。

### 题目解答

首先我们思考如果已经确定了这```s```树的，那么他有多少棵 ```BFS``` 生成树，我们考虑对这张图利用每一个点到 ```s``` 的距离进行分层，例如```dis(s,i)==3``` 那么我们就把 ```i``` 放在第三层，那我们假设 ```i``` 在第```k ```层，那么定义 ```c(i)``` 为 ```i``` 向第```k-1```层的点有多少条，直接相连的边。那么生成树的个树就是 $\prod_{i!=s}{c_i}$ 。

现在我们考虑什么时候点```x,y```可以有相同的生成树，首先这个生成树上的点可能会有两种，第一种是被夹在了```x,y```中也就是```dis(x,y)==dis(x,i)+dis(y,i)```，还有一种是这个点有一条连出去的边，使得这条边既可以成为```x```的```BFS```树中的边，又可以成为```y```的```BFS```树中的边。

我们现来考虑第一种点，如果第一类点和```x,y```连成的不是一条链，那么就会出现一些不好的情况，如下图，```1,3```是根，那么我们考虑```2```这个点，为了使```1,3```到```2```都是最短路，我们就必须同时连接 ```(3,2)(1,2)```这两条边，```4```也是同理，那么图中的边就不再是一棵树了。所以我们还得出了一条结论，就是第一种点都只有唯一的连接方式。

![](https://cdn.luogu.com.cn/upload/image_hosting/j8nymk43.png)

再来考虑第二种点，我们考虑分别以```x,y```进行分层那么只有可以同时出现在两棵```BFS```树的边才是合法的，那么再用相同的方式定义```c(i)```，答案就是  $\prod_{i!=x \land i!=y}{c_i}$。

这样我们就很顺畅的解决了这道题，代码还是很短的。QAQ

```cpp
int n, m, d[N][N];
vector <int> G[N];

modint Calc(int x, int y) {
	int cnt = 0;
	for (int i = 1; i <= n; i++)
		if (d[x][y] == d[x][i] + d[y][i])
			cnt++;
	if (cnt != d[x][y] + 1)
		return 0;
	modint Ans = 1;
	for (int i = 1; i <= n; i++) if (d[x][y] != d[x][i] + d[y][i]) {
		int c = 0;
		for (int j : G[i]) {
			if (d[x][i] != d[x][j] + 1) continue;
			if (d[y][i] != d[y][j] + 1) continue;
			c++;
		}
		Ans *= c;
	}
	return Ans;
}

int main() {
	Build_Mod(998244353), read(n), read(m), mset(d, 0x3f);
	for (int i = 1; i <= n; i++) d[i][i] = 0;
	for (int i = 1, a, b; i <= m; i++) {
		read(a), read(b);
		d[a][b] = d[b][a] = 1;
		G[a].pb(b), G[b].pb(a);
	}
	for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++)
		print(Calc(i, j), " \n"[j == n]);
	return 0;
}
```



---

## 作者：lsj2009 (赞：2)

### Solution

好题。

首先有个结论是：如果 $s\to t$ 的最短路不止一条，则必然无解。

这一点非常重要，但是我看大部分题解都没有说。所以简单写一下证明：

![](https://z1.ax1x.com/2023/11/07/pilr7yq.png)

如图，假设 $s\to t$ 有两条最短路，则构成了一个环，如果要得到一个 BFS Tree，则我们必然要断掉一条边，假设我们断的是图中的红边，也就是我们钦定了蓝色圆圈所画的地方在 $s$ 和 $t$ 的 BFS Tree 上。

但是显然并不是。因为 $t$ 到蓝色那一段的点显然走上方更优（因为上方和下方的最长度是相等的），这和 BFS Tree 的定义矛盾。

所以如果 $s\to t$ 有解，则必然只有一条最短路。

然后考虑接下来怎么计算答案。

我们考虑对于每个节点 $v$ 钦定他的父亲 $u$，那么要满足 $dis_{s,u}+1=dis_{s,v}$ 且 $dis_{t,u}+1=dis_{t,v}$。

但是考虑一种特殊情况：如果 $(u,v)$ 在 $s\to t$ 的最短路上，则不需要满足第二个条件，但是由于最短路有且仅有一条，所以这种贡献为 $1$，当 $v$ 在 $s\to t$ 的最短路上时 ``continue`` 掉即可。

然后对于每个 $v$，统计一下满足 $dis_{s,u}+1=dis_{s,v}$ 且 $dis_{t,u}+1=dis_{t,v}$ 的节点 $u$ 的个数，然后乘法原理即可。

初始化 $dis_{s,t}$ 花费 $\Theta(nm)$ 复杂度；枚举 $(s,t)$ 花费 $\Theta(n^2)$ 复杂度，统计答案花费 $\Theta(m)$ 复杂度，总复杂度为 $\Theta(n^2m)$。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=4e2+5,M=6e2+5,MOD=998244353;
int head[N],len;
struct node {
    int to,nxt;
}; node edge[M<<1];
void add_edge(int u,int v) {
    edge[++len]={v,head[u]}; head[u]=len;
}
int dis[N][N],cnt[N][N],n,m;
void bfs(int s) {
    queue<int> q;
    cl(dis[s],-1);
    q.push(s); 
	dis[s][s]=0; cnt[s][s]=1;
    while(!q.empty()) {
        int u=q.front(); q.pop();
        for(int i=head[u];i;i=edge[i].nxt) {
            int v=edge[i].to;
            if(dis[s][v]==-1) {
                dis[s][v]=dis[s][u]+1;
                cnt[s][v]=cnt[s][u];
                q.push(v);
            } else if(dis[s][v]==dis[s][u]+1)
                cnt[s][v]+=cnt[s][u];
        }
    }
}
int calc(int s,int t) {
    if(cnt[s][t]!=1)
        return 0;
    int res=1;
    rep(v,1,n) {
        if(dis[s][v]+dis[v][t]==dis[s][t])
            continue;
        int cnt=0;
        for(int i=head[v];i;i=edge[i].nxt) {
            int u=edge[i].to;
            if(dis[s][u]+1==dis[s][v]&&dis[t][u]+1==dis[t][v])
                ++cnt;
        }
        res=res*cnt%MOD;
    }
    return res;
}
signed main() {
    scanf("%lld%lld",&n,&m);
    while(m--) {
        int u,v;
        scanf("%lld%lld",&u,&v);
        add_edge(u,v);
        add_edge(v,u);
    }
    rep(i,1,n)
        bfs(i);
    rep(i,1,n) {
        rep(j,1,n)
            printf("%lld ",calc(i,j));
        puts("");
    }
    return 0;
}
```

---

## 作者：Alex_Eon (赞：1)

#### [$\color{red}\text{博客内食用效果更佳（点我）}$](https://www.luogu.com.cn/blog/Ksy/solution-cf1495d)

### 复杂度：$O(n^2m)$
### 完整思路

首先注意到 $n$ 范围不大，可以考虑 Floyd 求解全源最短路。

考虑对于 $x$ 和 $y$ 共同的生成树一定包含两者的最短路径。

先假设 $x, y$ 最短路径有且只有一条，考虑其上一点 $z$，$x, y$ 两者中一者到其最短路径依然有且只有一条，为了满足 $dis(x, z), dis(y, z)$ 不变，必须保留此最短路。

当 $x, y$ 最短路径不止一条时，对于这两条路径上的点依然需要满足上述 $z$ 的条件，因此多条最短路都需要保留，此时一定会成环，无法保持树的形态，也就一定无解。

现在对于 $x, y$ 两点已有一条唯一的链链接，考虑其他点如何挂在树上。对于一个点 $u$ 有边 $(u, v)$，若保留此边（使得 $v$ 为 $u$ 的父节点）必须满足 $dis(x, v) + 1 = dis(x, u) \land dis(y, v) + 1 = dis(y, u)$。所以我们对于一个点找出其合法父节点个数，对所有的点乘法原理计数即可。

### 代码实现需要注意的地方：

- 注意取模

### 参考代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef unsigned UN;
typedef double DB;
//--------------------//
const int N = 400 + 5, M = 600 + 5;
const int Mod = 998244353;

int n, m, dis[N][N];
vector<int> e[N];

int work(int u, int v) {
    int cnt = 0, res = 1;
    for (int i = 1; i <= n; i++)
        cnt += (dis[u][i] + dis[i][v] == dis[u][v]); // 检查最短路径数量
    if (cnt != dis[u][v] + 1)
        return 0;
    for (int i = 1; i <= n; i++)
        if (dis[u][i] + dis[i][v] != dis[u][v]) { // 对不在最短路径上的点进行计数
            cnt = 0;
            for (auto j : e[i])
                cnt += (dis[u][j] + 1 == dis[u][i] && dis[v][j] + 1 == dis[v][i]); // 对于 i 找到合法父节点 j 个数
            res = 1LL * res * cnt % Mod; 
        }
    return res;
}
//--------------------//
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dis[i][j] = 0x3f3f3f3f;
    for (int u, v, i = 1; i <= m; i++)
        scanf("%d%d", &u, &v), e[u].push_back(v), e[v].push_back(u), dis[u][v] = dis[v][u] = 1;
    for (int i = 1; i <= n; i++)
        dis[i][i] = 0;
    for (int k = 1; k <= n; k++) // Floyd
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[j][k]);
    for (int i = 1; i <= n; i++, printf("\n"))
        for (int j = 1; j <= n; j++)
            printf("%d ", work(i, j));
    return 0;
}
```

---

## 作者：RyexAwl (赞：1)

我们令 $\mathcal{T}_u$ 为以 $u$ 为根的 $BFS$ 树集合。

那么 $f(i,j) = |\mathcal{T}_i\bigcap \mathcal{T}_j|$ 。

定义 $fa(root,u)$ 为根为 $root$ 时 $u$ 的父亲。

特别地，规定 $fa(u,u)$ 有唯一的取值 $0$。

那么集合 $\mathcal{T}_u$ 的元素可以描述为满足特定条件的 $n$ 元组 $N=(fa(u,1),fa(u,2),fa(u,3)...fa(u,n))$。

令 $g(root,v)$ 为根节点为 $root$ 时，$v$ 的合法父亲数。

令 $d(i,j)$ 为点 $i,j$ 的最短距离。

$$
g(root,v)=\sum_{1\le q\le n}[d(u,q)+1=d(u,v)]
$$

特别地，规定 $g(u,u) = 1$ 。

那么 $\mathcal{T}_u=\prod_{1\le v\le n} g(u,v)$ 。

（因为每个点的深度是确定的因此是一定不会有后效性的）

我们发现我们用  “ $n$ 元组” 的定义很难去定义集合的交。

在这里我们定义一个映射 $\sigma: \mathcal{T}_i\to \mathcal{T}_j$ 表示一棵以 $i$ 为根的树的父亲列表映射到一棵以 $j$ 为根的树的父亲列表。

那么有：
$$
f(i,j) = |\mathcal{T}_i\bigcap \mathcal{T}_j|=\sum_{t\in\mathcal{T}_i} [\sigma(t)\in \mathcal{T}_j]
$$

我们发现我们要统计的本质上仍然是 $n$ 元组，因此也可以考虑每位分别考虑最后用乘法原理乘起来。

对于一棵树所对应的 $n$ 元组的每一个位置被映射的元素我们发现要么是其父亲，要么是其儿子。

并且我们发现如果一个位置 $u$ 的元素被映射成的元素是儿子当且仅当 $u$ 是 $j$ 的祖先并且其被映射成的元素一定是树上路径中 $j$ 到 $u$ 的倒数第二个点。

即只有树上点 $i$ 到 $j$ 路径上的点（不包括 $j$） 被映射成儿子。

并且我们发现其仍然也是没有后效性的，因此可以直接上乘法原理：

令 $S$ 为 $i$ 到 $j$ 所有最短路径构成的集合，那么：

$$
f(i,j)=\sum_{Q\in S}\prod_{1\le v\le n,v\not\in Q} \sum_{1\le q\le n}[d(i,q)+1=d(i,v)][d(j,q)+1=d(j,v)]
$$

但是我们发现如果 $|S|>1$，$f(i,j)$ 一定是为 $0$ 的。

（直接考虑艾弗森表达式）

因此我们可以直接 $O(n^3)$ 的去统计答案。







---

