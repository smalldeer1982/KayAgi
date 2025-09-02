# [ABC299E] Nearest Black Vertex

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc299/tasks/abc299_e

$ N $ 個の頂点と $ M $ 本の辺からなる、単純（自己ループおよび多重辺を含まない）かつ連結な無向グラフが与えられます。  
$ i\ =\ 1,\ 2,\ \ldots,\ M $ について、$ i $ 番目の辺は頂点 $ u_i $ と頂点 $ v_i $ を結ぶ無向辺です。

各頂点を白または黒で塗る方法であって、下記の $ 2 $ つの条件をともに満たすものが存在するかを判定し、存在する場合はその一例を示してください。

- $ 1 $ 個以上の頂点が黒で塗られている。
- すべての $ i\ =\ 1,\ 2,\ \ldots,\ K $ について、下記の条件が成り立つ。
  - 頂点 $ p_i $ と「黒で塗られた頂点のうち頂点 $ p_i $ からの距離が最小であるもの」の距離がちょうど $ d_i $ である。

ここで、頂点 $ u $ と頂点 $ v $ の距離は、$ u $ と $ v $ を結ぶパスの辺の本数としてあり得る最小値として定義されます。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2000 $
- $ N-1\ \leq\ M\ \leq\ \min\lbrace\ N(N-1)/2,\ 2000\ \rbrace $
- $ 1\ \leq\ u_i,\ v_i\ \leq\ N $
- $ 0\ \leq\ K\ \leq\ N $
- $ 1\ \leq\ p_1\ \lt\ p_2\ \lt\ \cdots\ \lt\ p_K\ \leq\ N $
- $ 0\ \leq\ d_i\ \leq\ N $
- 与えられるグラフは単純かつ連結
- 入力はすべて整数

### Sample Explanation 1

例えば、頂点 $ 1,\ 3 $ を黒に、頂点 $ 2,\ 4,\ 5 $ を白に塗るという方法が、問題文中の条件を満たします。 実際、$ i\ =\ 1,\ 2,\ 3,\ 4,\ 5 $ について、頂点 $ i $ と「黒で塗られた頂点のうち頂点 $ i $ からの距離が最小であるもの」の距離を $ A_i $ で表すと、 $ (A_1,\ A_2,\ A_3,\ A_4,\ A_5)\ =\ (0,\ 1,\ 0,\ 1,\ 2) $ であり、特に、$ A_1\ =\ 0,\ A_5\ =\ 2 $ が成り立ちます。

### Sample Explanation 2

問題文中の条件を満たすように各頂点を白または黒で塗る方法が存在しないため、`No` を出力します。

## 样例 #1

### 输入

```
5 5
1 2
2 3
3 1
3 4
4 5
2
1 0
5 2```

### 输出

```
Yes
10100```

## 样例 #2

### 输入

```
5 5
1 2
2 3
3 1
3 4
4 5
5
1 1
2 1
3 1
4 1
5 1```

### 输出

```
No```

## 样例 #3

### 输入

```
1 0
0```

### 输出

```
Yes
1```

# 题解

## 作者：STARSczy (赞：4)

# 题意：
输入一个图中有 $n$ 个节点和 $m$ 条边，输入每条边所连接的两个节点。图中有黑白节点，输入 $k$ 次，每次给出节点 $x$ 以及节点到最短距离最小的黑色节点的最短距离（可以为 $0$）。求出节点哪些是黑，哪些是白（输出任意一种即可）。黑色节点输出 `1`，白色节点输出 `0`，无解直接输出 `-1`。

# 做法：
因为节点 $x$ 到最近黑色节点的最短距离已经是最小值，所以我们把最短距离小于给定距离的节点全部排除。然后判断对于一个节点，是否所有的距离等于给定距离的节点都被排除了。如果是，说明无解，输出 `-1`，结束程序。若不存在无解，则说明一定有解。把排除成为黑色节点的全部输出为白色节点，否则输出位黑色节点。

# 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int maxn=2e3+10;
int n,m,k,mp[maxn][maxn],len[maxn],p[maxn]/*排除黑色节点的标记数组*/,fi[maxn],sc[maxn];

signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;++i){
		int a,b;
		scanf("%lld%lld",&a,&b);
		mp[a][++len[a]]=b,mp[b][++len[b]]=a;
	}
	scanf("%lld",&k);
	for(int i=1;i<=k;++i){
		queue<int> num/*节点编号*/,cnt/*节点深度*/;
		int a,b,t[maxn]={}/*用来广搜时去重*/;
		scanf("%lld%lld",fi+i,sc+i);
		a=fi[i],b=sc[i];
		num.push(a),cnt.push(0);
		while(!num.empty()){//广搜，排除不可能为黑色的节点。
			int x=num.front(),y=cnt.front();
			num.pop(),cnt.pop();
			if(t[x]||y==b) continue;
			t[x]=1,p[x]=1;
			for(int i=1;i<=len[x];++i) num.push(mp[x][i]),cnt.push(y+1);
		}
	}
	for(int i=1;i<=k;++i){
		queue<int> num,cnt;
		int a,b,t[maxn]={}/*广搜去重*/,o=0/*是否还有距离符合要求的没被排除黑色的节点*/;
		a=fi[i],b=sc[i];
		num.push(a),cnt.push(0);
		while(!num.empty()){//第二次广搜，判断对于一个节点，是否所有的距离等于给定距离的节点都被排除。
			int x=num.front(),y=cnt.front();
			num.pop(),cnt.pop();
			if(t[x]) continue;
			if(y==b){
				if(!p[x]){
					o=1;
					break;
				}
				continue;
			}
			t[x]=1;
			for(int i=1;i<=len[x];++i) num.push(mp[x][i]),cnt.push(y+1);
		}
		if(!o){
			cout<<"No";
			return 0;
		}
	}
	cout<<"Yes\n";
	for(int i=1;i<=n;++i) printf("%lld",!p[i]);
	return 0;
}
```

---

## 作者：Accelessar (赞：3)

[AT 题面](https://atcoder.jp/contests/abc299/tasks/abc299_e) [洛谷题面](/problem/AT_abc299_e)

### 简要题意

给定一张无向图，问是否存在一种将部分节点染黑的方案，满足：

- 至少有 $1$ 个节点被染黑。

- $K$ 条形如 $p_i,d_i$ 的限制，表示节点 $p_i$ 到与它最近的黑点的最短距离等于 $d_i$。

若存在给出一种可行方案，若不存在报告无解。

### 思路

逆向思维，考虑哪些点不能被染黑。

对于每一个 $p_i$，以它为源点跑一遍最短路，如果一个点 $x$ 到 $p_i$ 的最短路 $dis_x\lt d_i$，那么它不能被染黑，标记它为白色。

特别地，如果发现所有到 $p_i$ 最短路径等于 $d_i$ 的节点都已经被标记为白色了，这就意味着这一条限制不可能满足，直接无解。

最后检查所有节点，如果所有节点都已经被标记为白色，那么无解，否则将各点的标记取反后输出即可。

这很合理对不对？[WA*1](https://atcoder.jp/contests/abc299/submissions/40902890)。

来一组 hack：

```
3 2
2 3
3 1
2
3 0
1 2
```

问题出在哪里呢？当处理到 `3 0` 时，没有节点被标记为白色；处理到 `1 2` 时，$1,3$ 节点被标记为白色。所以程序认为将 $2$ 号节点染黑可以满足要求，但显然它不满足第一条限制。

所以问题出在我们使用了在线处理的方式，在处理当前条件时并不知道后面的条件会不会把我们已得出的结论推翻。我们发现只要把 hack 数据中的两个条件交换一下位置就可以得出正确答案。下面介绍 2 种解决方法。

1. 记录所有限制条件，按顺序处理两次。以上面的 hack 数据为例，当我们第二次处理到 `3 0` 这个条件时，因为第一轮处理时 $3$ 号节点已经标记为白色了，所以程序就知道出现了矛盾，需要报告无解。参考实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define fr(i,l,r) for(int i=(l);i<=(r);i++)
#define eb emplace_back
#define ep emplace
template<typename T>inline T rd(T&a){
    #define gc getchar
    #define dg(x) (x>='0'&&x<='9')
    char c=gc();T x=0,f=1;
    for(;!dg(c);c=gc())if(c=='-')f=-1;
    for(;dg(c);c=gc())x=(x<<1)+(x<<3)+c-48;
    return a=f*x;
}template<typename T,typename...Val>void rd(T&x,Val&...val){rd(x),rd(val...);}
const int N=2010;
int n,m,k,u,v,dis[N];
bool bk[N],fl=1;
vector<int>e[N];

void dijkstra(int s){
    priority_queue<pii>pq;
    memset(dis,0x3f,sizeof dis),pq.ep(dis[s]=0,s);
    while(!pq.empty()){
        auto[d,u]=pq.top();pq.pop();
        if(dis[u]==-d)for(int v:e[u])if(dis[v]>dis[u]+1)pq.ep(-(dis[v]=dis[u]+1),v);
    }
}

int main(){
    for(rd(n,m);m--;)rd(u,v),e[u].eb(v),e[v].eb(u);
    rd(k);vector<pii>p(k);
    for(auto&[u,v]:p)cin>>u>>v;
    for(auto[u,v]:p){
        dijkstra(u);
        bool fl1=1;
        fr(i,1,n)bk[i]|=dis[i]<v,fl1&=dis[i]!=v||bk[i];
        if(fl1)return puts("No"),0;
    }for(auto[u,v]:p){
        dijkstra(u);
        bool fl1=1;
        fr(i,1,n)bk[i]|=dis[i]<v,fl1&=dis[i]!=v||bk[i];
        if(fl1)return puts("No"),0;
    }fr(i,1,n)fl&=bk[i];
    if(fl)return puts("No"),0;
    puts("Yes");fr(i,1,n)cout<<!bk[i];
    return 0;
}
```

2. 无脑随机化。依然要存一下所有条件，然后打乱条件的顺序一直跑即可。亲测可过。参考实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
mt19937 rng(random_device{}());
typedef pair<int,int> pii;
#define fr(i,l,r) for(int i=(l);i<=(r);i++)
#define eb emplace_back
#define ep emplace
template<typename T>inline T rd(T&a){
    #define gc getchar
    #define dg(x) (x>='0'&&x<='9')
    char c=gc();T x=0,f=1;
    for(;!dg(c);c=gc())if(c=='-')f=-1;
    for(;dg(c);c=gc())x=(x<<1)+(x<<3)+c-48;
    return a=f*x;
}template<typename T,typename...Val>void rd(T&x,Val&...val){rd(x),rd(val...);}
const int N=2010;
int n,m,k,u,v,dis[N];
bool bk[N],fl=1;
vector<int>e[N];

void dijkstra(int s){
    priority_queue<pii>pq;
    memset(dis,0x3f,sizeof dis),pq.ep(dis[s]=0,s);
    while(!pq.empty()){
        auto[d,u]=pq.top();pq.pop();
        if(dis[u]==-d)for(int v:e[u])if(dis[v]>dis[u]+1)pq.ep(-(dis[v]=dis[u]+1),v);
    }
}

int main(){
    for(rd(n,m);m--;)rd(u,v),e[u].eb(v),e[v].eb(u);
    rd(k);vector<pii>p(k);
    for(auto&[v,u]:p)cin>>u>>v;
    while((double)clock()<0.9*CLOCKS_PER_SEC){
        shuffle(p.begin(),p.end(),rng);
        for(auto[v,u]:p){
            dijkstra(u);
            bool fl1=1;
            fr(i,1,n)bk[i]|=dis[i]<v,fl1&=dis[i]!=v||bk[i];
            if(fl1)return puts("No"),0;
        }fr(i,1,n)fl&=bk[i];
        if(fl)return puts("No"),0;
    }puts("Yes");fr(i,1,n)cout<<!bk[i];
    return 0;
}
```

---

## 作者：2huk (赞：1)

## 题目描述

有一个 $N$ 个点 $M$ 条边的无重边，无自环的无向连通图，每个点可能是黑色的或者是白色的。

请你设计一种染色方案，使得 $p_i$ 点距离最近的黑点的距离恰好为 $d_i$。

## 数据范围

$1 \le N \le 2000,\ N - 1\le M\le\min\left(\dfrac{N(N-1)}2,2000\right),\ 0 \le K \le N$

## 总体思路

首先将所有的点染成黑色，然后将所有距离 $p_i$ 点的最短距离小于 $d_i$ 的点全部染成白色。染色完成后，判断是否满足输入的 $p_i$ 和 $d_i$ 的限制即可。

定义 $dis_{i, j}$ 表示 $i$ 点到 $j$ 点的最短距离，$col_i$ 表示第 $i$ 个点是否是黑色。

## 求出任意两点的最短距离

求出任意两点的最短距离也就是求出所有的 $dis_{i, j}$ 的值。

枚举每一个点 $i$，然后 `BFS` 更新点 $i$ 到其它点 $j$ 的最短距离即可。

主函数部分：

```cpp
for (int i = 1; i <= n; i ++ ) bfs(i);
```

`BFS` 部分：

```cpp
typedef pair<int, int> PII;

#define v first
#define dist second

int n, m, x, y, k, p[N], d[N];
int h[N], e[N], ne[N], idx;
bool st[N], col[N];		// col[i] 表示第 i 个点是否是黑色 
int dis[N][N];		// dis[i][j] 表示 i 到 j 的最短距离	

void bfs(int s)
{
	memset(st, 0, sizeof st);
	queue<PII> q;
	q.push({s, 0});
	st[s] = 1;
	
	while (!q.empty())
	{
		auto t = q.front();		// 取出队头元素并出队 
		
		q.pop();
		
		dis[s][t.v] = t.dist;	// 更新距离 
		
		for (int i = h[t.v]; i != -1; i = ne[i])		// 枚举所有与 t.v 相邻的点 i 
		{
			int j = e[i];
			if (st[j]) continue;		// 如果这个点的距离更新过，不做处理（BFS 先搜到的一定是距离最近的） 
			st[j] = 1;
			q.push({j, t.dist + 1});	// 入队 
		}
	}
}
```

## 染色

读入所有的 $p_i$ 和 $d_i$，并把与 $p_i$ 的最短距离小于 $d_i$ 的点全部染成白色。可以枚举所有的点 $j$，并判断 $dis_{p_i, j}$ 是否 $<d_i$。若是，重新染为白色。

```cpp
cin >> k;

for (int i = 1; i <= k; i ++ )
{
	cin >> p[i] >> d[i];		// 读入 
	for (int j = 1; j <= n; j ++ )
		if (dis[p[i]][j] < d[i]) col[j] = 0; 		// 如果最短距离小于 d[i]，重新染成白色 
}
```

## 判断合法

判断是否合法，只需要找到黑色的且与 $p_i$ 距离最近的点的距离是否等于 $d_i$。若不等于，输出 `No` 并结束程序。反之，输出所有的 $col_i$ 即可。

```cpp
for (int i = 1; i <= k; i ++ )
{
	int tmp = 0x3f3f3f3f;		// tmp 表示当前距离 i 点最近点的距离 
	
	for (int j = 1; j <= n; j ++ )
		if (col[j]) tmp = min(tmp, dis[p[i]][j]);		// 更新最小值 
	
	if (tmp != d[i])		// 判断是否等于 d[i] 
	{
		puts("No");
		return 0;
	}
}
```

## 代码

[Code](https://www.luogu.com.cn/paste/1xlc7ik8)


---

## 作者：LHQing (赞：1)

### 题意概要：

给定一张有 $n$ 个点，$m$ 条边的图。将这张图黑白染色。对其中 $k$ 个点要满足以下条件：对于点 $x$，离它最近的**黑点**与它相距为 $d$。求这种图是否存在染色方案，若有，并构造方案。

### 题目分析：

首先，预处理出两两间的距离。使用合适的最短路径算法即可。

首先，对于 $\operatorname{dis}(i,x)<d$ 的所有 $i$ 点显然不能满足条件，我们在这些点上打个标记即可。

由于距离是恰好为 $d$，那么在所有 $\operatorname{dis}(i,x)=d$ 的点上开一个 `vector`，将这个**特殊点的编号**加进去。（注意，这不是点的编号，而是特殊点的编号。）

最后判断是否存在解的时候，我们只需要统计一下，对于**所有**没有打标记的点，将其 `vector` 中所有的特殊点的编号放在一起，去重后是否是 $k$ 个。如果是 $k$ 个，说明对于每个特殊点，至少存在一个点可以染成黑色与其相对应。（可以用桶排序去重。）若是，答案为 `Yes`，否则为 `No`。

对于构造方案，我们只用在没打标记的点染黑色，打了标记的染白色即可。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pd(x) push_back(x)
#define all(x) x.begin(),x.end()
//==============================================================================
ll QP(ll x,ll y,ll mod){ll ans=1;for(;y;y>>=1,x=x*x%mod)if(y&1)ans=ans*x%mod;return ans;}
//==============================================================================
namespace IO{
	int readInt(){
		int x=0,y=0;char c=0;
		while(!isdigit(c))y|=c=='-',c=getchar();
		while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
		return !y?x:-x;
	}
	void write(int x){if(!x)return;write(x/10);putchar(x%10);}
	void Output(int x){if(x<0)putchar('-'),x=-x;if(!x)putchar('0');else write(x);}
	void WL(int x){Output(x);putchar('\n');}
	void WS(int x){Output(x);putchar(' ');}
}
namespace Debug{
	void DeVec(vector<int> c){for(auto y:c)printf("%d ",y);puts("");}
	void DeNum(int x){printf("%d\n",x);}
}
//==============================================================================
const int N=2e3+10;
int n,m,q;
vector<int> a[N];
struct node{int x,dis;};
bool vis[N];
int P[N];
priority_queue<node> Q;
bool operator <(const node &x,const node &y){return x.dis>y.dis;}
int S,dis[N][N];
void Dijkstra(int S){
	memset(vis,false,sizeof(vis));dis[S][S]=0;
	Q.push({S,dis[S][S]});
	while(!Q.empty()){
		int x=Q.top().x;Q.pop();
		if(vis[x])continue;vis[x]=true;
		for(auto y:a[x])
			if(dis[S][x]+1<dis[S][y])
				dis[S][y]=dis[S][x]+1,
				Q.push({y,dis[S][y]});
	}
}
vector<int> ak[N];
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int x,y;scanf("%d%d",&x,&y);
		a[x].pd(y),a[y].pd(x);
	}memset(dis,0x3f,sizeof(dis));
	for(int i=1;i<=n;i++)Dijkstra(i);
	scanf("%d",&q);
	if(!q){
		puts("Yes");
		for(int i=1;i<=n;i++)
			printf("%d",1);
		return 0;
	}
	for(int r=1;r<=q;r++){
		int p,x;scanf("%d%d",&p,&x);
		for(int i=1;i<=n;i++){
			if(dis[p][i]<x)P[i]=1;
			if(dis[p][i]==x)ak[i].pd(r);
		}
	}
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)
		if(!P[i])
			for(auto y:ak[i])
				vis[y]=true;
	for(int i=1;i<=q;i++)
		if(!vis[i]){
			puts("No");
			return 0;
		}
	puts("Yes");
	for(int i=1;i<=n;i++)
		printf("%d",P[i]==1?0:1);
	return 0;
}
```

---

## 作者：incra (赞：1)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc299_e)
### 题解
首先，用 BFS 求出每一个点到其他所有点的距离。

然后，对于每一个查询的点 $p_i$，求出所有与其距离大于等于 $d_i$ 的点，并将所有与其距离小于 $d_i$ 的点删除。

接着，再在每一个查询中的点 $p_i$ 求出是否有未删除的点的距离到 $p_i$ 的距离为 $d_i$，若有，将这个点标为黑色。如果没有距离 $p_i$ 为 $d_i$ 的点，则这题无解。

注意，题目中不允许所有点都是白色的，所以 $k=0$ 时要特判。
### 代码
```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;
const int N = 2010;
int n,m,k;
bool vis[N];
vector <int> g[N];
int p[N],d[N];
int dist[N][N];
int ans[N];
bool boom[N];
void bfs (int dis[],int p) {
	queue <int> q;
	q.push (p);
	memset (vis,false,sizeof (vis));
	vis[p] = true;
	while (q.size ()) {
		int x = q.front ();
		q.pop ();
		for (int y : g[x]) {
			if (vis[y]) continue;
			vis[y] = true;
			dis[y] = dis[x] + 1;
			q.push (y);
		}
	}
}
int main () {
	cin >> n >> m;
	while (m--) {
		int a,b;
		cin >> a >> b;
		g[a].push_back (b),g[b].push_back (a);
	}
	for (int i = 1;i <= n;i++) bfs (dist[i],i);
	cin >> k;
	if (!k) {
		puts ("Yes");
		for (int i = 1;i <= n;i++) cout << 1;
		cout << endl;
		return 0;
	}
	for (int i = 1;i <= k;i++) {
		cin >> p[i] >> d[i];
		for (int j = 1;j <= n;j++) {
			if (dist[p[i]][j] < d[i]) boom[j] = true;
		}
	}
	for (int i = 1;i <= k;i++) {
		bool flag = true;
		for (int j = 1;j <= n;j++) {
			if (dist[p[i]][j] == d[i] && !boom[j]) ans[j] = true,flag = false;
		}
		if (flag) {
			puts ("No");
			return 0;
		}
	}
	printf ("Yes\n");
	for (int i = 1;i <= n;i++) cout << ans[i];
	cout << endl;
	return 0;
}
```

---

## 作者：Neil_Qian (赞：1)

# [ABC299E] Nearest Black Vertex 题解

给定一张无向无权图，每个点要么是黑色，要么是白色。有一些限制，从一个点出发，离它最近的黑点距离恰为一个值。求涂色方案或输出无解。所有数据在 $2000$ 以内。

一看到无向无权图，而且 $n\le2000$，先从每个点出发广搜求出任意两点的距离，$O(n^2)$ 可以接受。

考虑每个限制，对于点 $p_i$，最近的黑点距离为 $d_i$，所有距离刚好是 $d_i$ 的可以选，并且必须选其中一个，距离 $>d_i$ 的也可以选，集合 $S_i=\{j(dist_{p_i,j}\ge d_i)\}_{j=1}^{n}$。

最后的答案集合 $ANS$ 一定满足 $ANS\subseteq ALL=\bigcap_{i=1}^{k}S_i$，但还要满足每一个最近的黑点的距离，显然点尽可能多越有可能满足条件，因此检查集合 $ALL$ 即可。最后问题得解，时间复杂度 $O(n^2+nk)$。

```cpp
#include<bits/stdc++.h>
using namespace std;const int N=2e3+2;
int n,m,k,x,y,a[N],b[N],ans[N][N];
vector<int> v[N];queue<int> q;bool c[N][N],p[N],flag;
inline void bfs(int st){//广搜
	q.push(st),fill(ans[st]+1,ans[st]+n+1,1e9),ans[st][st]=0;
	while(!q.empty()){
		x=q.front(),q.pop();
		for(int t:v[x])if(ans[st][t]==1e9)
			ans[st][t]=ans[st][x]+1,q.push(t);
	}
}
int main(){
	scanf("%d%d",&n,&m),fill(p+1,p+n+1,1);//读入&初始化
	while(m--)scanf("%d%d",&x,&y),
		v[x].push_back(y),v[y].push_back(x);
	for(int i=1;i<=n;i++)bfs(i);
	scanf("%d",&k);
	for(int i=1;i<=k;i++){
		scanf("%d%d",&a[i],&b[i]);
		for(int j=1;j<=n;j++)//集合求并集
			c[i][j]=(ans[a[i]][j]>=b[i]),p[j]&=c[i][j];
	}
	for(int i=1;i<=k;i++){
		flag=0;
		for(int j=1;j<=n;j++)if(ans[a[i]][j]==b[i]&&p[j])
		{flag=1;break;}//检查答案
		if(!flag)return printf("No\n"),0;
	}
	printf("Yes\n");
	for(int i=1;i<=n;i++)printf("%d",p[i]);
	return printf("\n"),0;
}
```

---

## 作者：yujinning (赞：0)

## 题意

- 给定一张具有 $N$ 个顶点的无向无权图和 $K$ 个目标点，每个目标点 $p_i$ 都具有距离参数 $d_i$。

- 要求标记出若干点，使得每个目标点 $p_i$ 离最近的标记点的距离均为 $d_i$。

- $N\leq 2000$。

## 解法

可在 $O(N^2)$ 的时间复杂度内解决问题。

对于每个点预处理与其他点的距离，可用 bfs 实现，记点 $i$ 与点 $j$ 的距离为 $dis_{i,j}$，对于每个点的计算距离只会遍历到每个点一次，因此时间复杂度为 $O(N^2)$。

```cpp
void bfs(int num){
	queue<node> q;
	q.push((node){num,0}); vst[num]=1;
	while(!q.empty()){
		node now=q.front(); q.pop();
		for(int i=0;i<son[now.id].size();i++){
			int v=son[now.id][i];
			if(vst[v]==1) continue; vst[v]=1;
			dis[num][v]=dis[v][num]=now.len+1;
			q.push((node){v,now.len+1});
		}
	}
}
```

不妨依次考虑是否选定每个点。对于点 $x(x\in[1,N])$，若这个点离某一个点 $p_i$ 距离小于 $d_i(i\in[1,K])$，则选定这个点后的方案必然不合法，舍弃这个点，否则此点必然对于方案有意，选定这个点。时间复杂度 $O(NK)$。

最终判断每个目标点是否存在一个选定点满足 $dis_{x,p_i}=d_i(x$ 为目标点，$i\in[1,K]$）。若对于每个目标点都满足要求，则表明当前方案符合要求；否则不存在此方案。时间复杂度 $O(NK)$。

而 $K<N$，则总计时间复杂度为 $O(N^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2009;
inline int read(){ int x=0,f=1; char ch=getchar(); while(!isdigit(ch)){ if(ch=='-') f=-1; ch=getchar();} while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48); ch=getchar();} return x*f;}
inline void write(int x){ if(x<0) putchar('-'),x=-x; if(x>9) write(x/10); putchar(x%10+'0');}
int n,m,k,dis[N][N],p[N],d[N],okk[N],yes[N];
bool vst[N];
vector<int> son[N];
struct node{
	int id,len;
};
void bfs(int num){
	queue<node> q;
	q.push((node){num,0}); vst[num]=1;
	while(!q.empty()){
		node now=q.front(); q.pop();
		for(int i=0;i<son[now.id].size();i++){
			int v=son[now.id][i];
			if(vst[v]==1) continue; vst[v]=1;
			dis[num][v]=dis[v][num]=now.len+1;
			q.push((node){v,now.len+1});
		}
	}
}
int main(){
    n=read(); m=read();
    for(int i=1;i<=m;i++){
    	int u=read(),v=read();
    	son[u].push_back(v),son[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		fill(vst,vst+1+n,0);
		bfs(i);
	}
	k=read();
	for(int i=1;i<=k;i++) p[i]=read(),d[i]=read();
	for(int i=1;i<=n;i++){
		bool flag=true;
	    for(int j=1;j<=k;j++)
	    	if(dis[i][p[j]]<d[j]){flag=false; break;}
		if(flag==true){
			okk[i]=1;
			for(int j=1;j<=k;j++)
			    if(dis[i][p[j]]==d[j]) yes[j]=1; 
		}
	}
	bool flag=true;
	for(int i=1;i<=k;i++) if(yes[i]==0){flag=false; break;}
	if(flag==false) cout<<"No";
	else{
		cout<<"Yes"<<endl;
		for(int i=1;i<=n;i++) write(okk[i]);
	}
	return 0;
}
```

---

