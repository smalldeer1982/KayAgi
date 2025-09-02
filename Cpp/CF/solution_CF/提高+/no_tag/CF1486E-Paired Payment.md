# Paired Payment

## 题目描述

There are $ n $ cities and $ m $ bidirectional roads in the country. The roads in the country form an undirected weighted graph. The graph is not guaranteed to be connected. Each road has it's own parameter $ w $ . You can travel through the roads, but the government made a new law: you can only go through two roads at a time (go from city $ a $ to city $ b $ and then from city $ b $ to city $ c $ ) and you will have to pay $ (w_{ab} + w_{bc})^2 $ money to go through those roads. Find out whether it is possible to travel from city $ 1 $ to every other city $ t $ and what's the minimum amount of money you need to get from $ 1 $ to $ t $ .

## 说明/提示

The graph in the first example looks like this.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1486E/d05a9b1774a0eade44485bb99ef938693d1a95f9.png)

In the second example the path from $ 1 $ to $ 3 $ goes through $ 2 $ , so the resulting payment is $ (1 + 2)^2 = 9 $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1486E/9c27ff1803f812784d9dc5ba8f09e905e17b3714.png)

## 样例 #1

### 输入

```
5 6
1 2 3
2 3 4
3 4 5
4 5 6
1 5 1
2 4 2```

### 输出

```
0 98 49 25 114```

## 样例 #2

### 输入

```
3 2
1 2 1
2 3 2```

### 输出

```
0 -1 9```

# 题解

## 作者：nytyq (赞：3)

## Part 0.前言

模拟赛的题，是一道好题。

听完讲解，我发现这道题的代码和[旅游巴士](https://www.luogu.com.cn/problem/P9751)颇为相似。


## Part 1.思路

显然易知，此题用 **Dijkstra 求最短路算法**。

为了简化问题，我们只考虑如下这种简单的情况：

+ 由 $a$ 指向 $b$ 的一条有向边，边权为 $w_1$。
+ 有 $b$ 指向 $c$ 的一条有向边，边权为 $w_2$。
+ 则 $a$ 至 $c$ 的整体花费为 $(w_1+w_2)^2$。

考虑对上述的式子做一个等价变形。

则有 $a$ 到 $b$ 的权重为 $0$，有 $b$ 到 $c$ 的权重为 $(w_1+w_2)^2$ **或者** $a$ 到 $b$ 的权重为 $(w_1+w_2)^2$，有 $b$ 到 $c$ 的权重为 $0$。

为了在下文中好简述，我们令起始点为 $a$，中转点代表 $b$，结束点为 $c$。

由于我们不知道一个点是处于中转点还是结束点状态。我们就想着多加一维表是点的状态。但显然我们在结束点求花费的时候不好求出，于是考虑到对于我们用上一条边的边权作为第二维。

则 **Dijkstra 求最短路算法** 的普通状态 $dist_{i}$ 扩展为了 $dist_{i,w}$，其中的 $w$ 为起始点到中转点的边权。

那么对于一个点的状态只可能是为中转点或者终点（因为起始点可以看作是上一次花费的终点），所以说我们对于一个点就有两种情况讨论。

+ 前面为起始点，则 $dist_{i,w}$ 中的 $w$ 是 $0$。
+ 前面为中转点，则 $dist_{i,w}$ 中的 $w$ 是 $(w_1^2+w_2^2)$。
  
于是对于每个点的状态都有了明确的枚举状态，进行 **Dijkstra求最短路算法** 就能求得答案。

## AC Code

```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
using namespace std;
#define p pair<ll,pair<int,int> > 
const int N=1e5+5;
typedef long long ll;
vector<pair<int,int> > g[N];
int n,m;
ll dist[N][51];
void dj(){
	memset(dist,0x3f,sizeof(dist));
	dist[1][0]=0;
	priority_queue<p,vector<p>,greater<p> > q;
	q.push({0,{1,0}});
	while(q.size()){
		auto x=q.top();q.pop();
		int ver=x.second.first,distance=x.second.second;
		for(int i=0;i<g[ver].size();i++){
			int v=g[ver][i].first,w=g[ver][i].second;
			if(distance>0){
				if(dist[v][0]>dist[ver][distance]+(distance+w)*(distance+w)){
					dist[v][0]=dist[ver][distance]+(distance+w)*(distance+w);
					q.push({dist[v][0],{v,0}});
				}
			}
			else{
				if(dist[v][w]>dist[ver][distance]){
					dist[v][w]=dist[ver][distance];
					q.push({dist[v][w],{v,w}});
				}
			}
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	while(m--){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		g[a].push_back({b,c});
		g[b].push_back({a,c});
	}
	dj();
	for(int i=1;i<=n;i++){
		ll res=0;
		if(dist[i][0]>=0x3f3f3f3f3f3f3f3f) res=-1;
		else res=dist[i][0];
		printf("%lld ",res);
	}
	return 0;
}
```

---

## 作者：FiraCode (赞：3)

我们来看一个图：
![](https://cdn.luogu.com.cn/upload/image_hosting/prtnv6gz.png)
从最上边的点，到最后一个点，边权是： $(w_1 + w_2)^2$

#### 那么从一个点到另一个点，需要两步：
>*	第一步，移到中间点。
>*	第二步，移到目标点。

#### 我们把点分为两类：
>- 1. 到达点：到达点就是到达一个点的最短路是多少
>- 2. 中转点：中转点就是要到达一个地方经过的点

#### 如果我们把路径分为两种：
>一： 中转点 $\impliedby$ 到达点，花费0边权

>二： 到达点 $\impliedby$ 中转点，花费 $(w_1 + w_2) ^ 2$ 

>但如果这样做的话，复杂度会很高，中转点的状态数是 $n^2$

>但当前我们只关注 $w_1$ 是谁，而不关注中转点是谁。

>所以我们可以把中转点改一下，中转点的状态数只有 $[50]$ 个就够了，因为 $w_i$ 最多只有 50。

>$u_0$ 代表到达点 ， $u_1$ 代表u是中转点，他是由1走过来的。

>这就维护了他的最短路 $dis_{[u][0]} ,dis_{[u][1]} ……. dis_{[u][50]}$ 。

他的时间复杂度为 $\mathcal{O(n·mlongm)}$
### 看代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;//根据题目范围
#define ll long long
#define itn int //个人习惯，防手残
vector< pair<int , int> > e[maxn];//定义变量
int n , m;
ll dis[maxn][55];
inline void dij() {
	memset (dis , 0x3f , sizeof (dis));//每次用的时候，要初始化
	dis[1][0] = 0;
	priority_queue< pair <ll , pair<int , int> > > pq;
	pq.push({0 , {1 , 0}});
	while (!pq.empty()) {
		auto now = pq.top(); pq.pop();
		int u = now.second.first , u2 = now.second.second;
		for (auto &x : e[u]) {
			int v = x.first , w = x.second;
			if (u2 > 0) {
				if (dis[v][0] > dis[u][u2] + (u2 + w) * (u2 + w)) {
					dis[v][0] = dis[u][u2] + (u2 + w) * (u2 + w);
					pq.push({-dis[v][0] , {v , 0}});
				}
			}else {
				if (dis[v][w] > dis[u][u2]) {
					dis[v][w] = dis[u][u2];
					pq.push({-dis[v][w] , {v , w}});
				}
			}
		}
	}
}
int main() {
	cin >> n >> m;//读入
	for (int i = 0; i < m; ++ i) {//读入边
		int u , v , w;
		cin >> u >> v >> w;
		e[u].push_back({v , w});
		e[v].push_back({u , w});
	}
	dij();//调用函数
	for (itn i = 1; i <= n; ++ i)//输出
		if (dis[i][0] > int(1e18))cout << "-1 ";
		else cout << dis[i][0] << ' ';
	return 0;
}
```

---

## 作者：appear_hope (赞：2)

先读懂题。

首先看到平方和，直接用公式，那么 $(w_{ab} + w_{bc})^2 = w_{ab}^2 + w_{bc}^2 + 2 \times w_{ab} \times w_{bc}$，那么观察到该题的转移方式显然不能暴力转移，我们可以将路径长度加入状态，但由于平方和还有一个两倍乘积，又观察到 $w_i$ 的取值范围只有 $50$，所以索性将上一次经过的边的长度加入状态。

代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;
using pir = pair<int, int>;

const int N = 1e5 + 2;
const int M = 52;
const long long INF = 5e17;

struct Node{
  int x;
  int op1, op2;
  long long cnt;
  bool operator < (const Node &b) const{
    return cnt > b.cnt;
  }
};

int n, m;
vector<pir> g[N];
bool vis[N][2][M];
long long dist[N][2][M];
priority_queue<Node> heap;

void Record(int x, int op1, int op2, long long cnt){
  if(vis[x][op1][op2] || cnt >= dist[x][op1][op2]) return ;
  dist[x][op1][op2] = cnt, heap.push({x, op1, op2, cnt});
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for(int i = 1, u, v, w; i <= m; i++){
    cin >> u >> v >> w;
    g[u].push_back({v, w}), g[v].push_back({u, w});
  }
  for(int i = 1; i <= n; i++){
    for(int j = 0; j <= M - 2; j++) dist[i][0][j] = dist[i][1][j] = INF;
  }
  Record(1, 0, 0, 0);
  while(!heap.empty()){
    Node q = heap.top();
    heap.pop();
    //cout << q.x << ' ' << q.op1 << ' ' << q.op2 << ' ' << q.cnt << '\n';
    if(vis[q.x][q.op1][q.op2]) continue;
    vis[q.x][q.op1][q.op2] = 1;
    for(pir e : g[q.x]){
      int v = e.first, w = e.second;
      if(q.op1) Record(v, 0, 0, q.cnt + w * w + 2 * q.op2 * w);
      else Record(v, 1, w, q.cnt + w * w);
    }
  }
  for(int i = 1; i <= n; i++){
    long long ans = INF;
    bool flag = 0;
    for(int j = 0; j <= M - 2; j++){
      if(vis[i][0][j]){
        ans = min(ans, dist[i][0][j]);
        flag = 1;
      }
    }
    if(!flag){
      cout << -1 << ' ';
      continue;
    }
    cout << ans << ' ';
  }
  return 0;
}

```

---

## 作者：7KByte (赞：2)

分层图

第 $0$ 层表示原图的节点。

第 $i$ 层的节点 $v$ 记作$V_{i,v}$表示经过一条大小为 $i$ 边到达节点 $v$ 。

那么对于原图一条有向边 $u\to v$。拆成 $V_{0,u}\to V_{w_{i,j},v}$，边权为$w_{i,j}^2$ 和 $V_{k,u} \to V_{0,v},k\in [1,50]$，边权为$w_{i,j}^2+2\times w_{i,j}\times k$。

无向边拆成两条边，然后跑 $\texttt{Dijkstra}$ 最短路即可。

观察一下一下边数和点数分别是 $\rm{50M}$ 和 $\rm {50N}$，似乎会 $\texttt{TLE}$ ，但原图上的一条边对应新图上两条新边和一个拆出的点，所以时间复杂度仍然是 $\rm O(N \log N)$，假定$N,M$同规模。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 5200005
using namespace std;
int n,m,s,h[N],tot;
struct edge{
int to,nxt,val;
}e[30000005];
void add(int x,int y,int z){
	e[++tot].nxt=h[x];h[x]=tot;e[tot].to=y;e[tot].val=z;
}
priority_queue<pair<int,int> >q;
int d[N],v[N];
void dij(){
	memset(d,0x3f,sizeof(d));
	memset(v,0,sizeof(v));
	d[s]=0;q.push(make_pair(0,s));
	while(!q.empty()){
		int x=q.top().second;q.pop();
		v[x]=1;
		for(int i=h[x];i;i=e[i].nxt)if(d[x]+e[i].val<d[e[i].to]){
			d[e[i].to]=d[x]+e[i].val;q.push(make_pair(-d[e[i].to],e[i].to));
		}
		while(!q.empty()&&v[q.top().second])q.pop();
	}
}
int f(int x,int y){return x*n+y;}
int main(){
	scanf("%d%d",&n,&m);s=1;
	rep(op,1,m){
		int x,y,z;scanf("%d%d%d",&x,&y,&z);
		add(x,f(z,y),z*z);
		add(y,f(z,x),z*z);
		rep(i,1,50)add(f(i,x),y,z*z+z*i*2);
		rep(i,1,50)add(f(i,y),x,z*z+z*i*2);
	}
	dij();rep(i,1,n)printf("%d ",d[i]>=0x3f3f3f3f?-1:d[i]);
	return 0;
}
```

---

## 作者：CommonDigger (赞：1)

## 题目大意
[CF1486E Paired Payment](https://www.luogu.com.cn/problem/CF1486E)

单源最短路，但是距离计算的规则是每两条边权值之和的平方,两两一组。例如：分别走过 $5,3,11,6$ 四条边，权值有两组，距离计算是 $(5+3)^2+(11+6)^2=353$。

## 做法
考虑类似分层图的思想。题目有一个很友善的数据范围：边权 $w\le50$。所以可以设数组 $\texttt{dis[200005][51]}$，其中 $\texttt{dis[i][j]}$ 表示走到 $i$ 号点，上一条边的边权是 $j$ 的最短路程。特别地，$j=0$ 时，表示接下来是一组新的边。

$j\neq0$ 时，当前组合里有一条边，再选一条边，就形成了一个新的边权组合，算出权值。

$j=0$ 时，此时上一条边已经在前面的组合里了，随便选一条边作为新的组合，先不更新权值。

其他的和最短路差别不大，具体见代码。

## 代码
```cpp
/*
Luogu CF1486E Paired Payment
https://www.luogu.com.cn/problem/CF1486E
*/
#include "iostream"
#include "queue"
#include "cstring"
using namespace std;
const int N=200005;
int n, m, head[N], idx, temp1, temp2, temp3;
int dis[N][51];
bool ins[N][51];
struct edge{
    int to, nxt, w;
}e[2*N];
struct node{
    int id, pre;
    node(int id=1, int pre=0){
        this->id=id;
        this->pre=pre;
    }
};
void add_edge(int u, int v, int w){
    e[++idx].to=v;
    e[idx].w=w;
    e[idx].nxt=head[u];
    head[u]=idx;
}
int square(int i){
    return i*i;
}
void spfa(){
    queue<node>q;
    q.push(node(1, 0));
    memset(dis, 0x3f, sizeof(dis));
    dis[1][0]=0;
    while(!q.empty()){
        int id=q.front().id, pre=q.front().pre;
        ins[id][pre]=false;
        q.pop();
        if(pre==0){
            for(int i=head[id];i;i=e[i].nxt){
                int to=e[i].to, w=e[i].w;
                if(dis[id][0] < dis[to][w]){
                    dis[to][w] = dis[id][0];
                    if(!ins[to][w]){
                        ins[to][w]=true;
                        q.push(node(to, w));
                    }
                }
            }
        }else{
            for(int i=head[id];i;i=e[i].nxt){
                int to=e[i].to, w=e[i].w;
                if(dis[id][pre]+square(pre+w)<dis[to][0]){
                    dis[to][0]=dis[id][pre]+square(pre+w);
                    if(!ins[to][0]){
                        ins[to][0]=true;
                        q.push(node(to, 0));
                    }
                }
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for(int i=1;i<=m;i++){
        cin >> temp1 >> temp2 >> temp3;
        add_edge(temp1, temp2, temp3);
        add_edge(temp2, temp1, temp3);
    }
    spfa();
    for(int i=1;i<=n;i++) cout << (dis[i][0]==0x3f3f3f3f ? -1 : dis[i][0]) << " ";
}
```

---

## 作者：rainbow_cat (赞：1)

首先我们可以考虑对于任意连续两点进行连边，但很明显，这会被菊花图卡掉。   
思考如果我们将状态从 $dis_i$ 改为 $dis_{i,j}$ 代表以 $j$ 为中间点到 $i$ 的最短路。然而这也会超时，不过我们注意到了 $w\le50$。  
所以我们定义状态 $dis_{i,j}$ 代表从长度为 $j$ 的边到达 $i$ 的最短距离，若此时走了偶数次，$j=0$。  
对于一条从 $x$ 到 $y$ 的，长度为 $z$ 的边，若已走偶数步： 
$$
dis_{y,z}=\min(dis_{y,z},dis_{x,0}+z^2)
$$
若已走奇数步：
$$
dis_{y,0}=\min(dis_{y,0},dis_{x,las}+2\times x \times las+z^2)
$$
其中 $las$ 为上一条边的长度。   
最后，到点 $i$ 的答案为 $dis_{i,0}$。   
**注：**  
由于路径可能有重复经过的点，所以去掉判重复经过的部分。此时 dijkstra 在使用大根堆时的答案也是正确的，只不过会超时。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,x,y,z,dis[100010][60];
bool vis[100010][60];
vector<pair<int,int>>e[100010];
struct node{int u,fr,dis;};
bool operator < (node x,node y){return x.dis>y.dis;}
priority_queue<node>q;
void dijkstra()
{
	memset(dis,0x3f,sizeof dis);
	q.push({1,0,0});
	dis[1][0]=0;
	while(q.size())
	{
		int u=q.top().u,fr=q.top().fr;
		q.pop();
//		if(vis[u][fr])continue;
//		vis[u][fr]=1;
		for(auto i:e[u])
		{
			if(fr)
			{
				if(dis[i.first][0]>dis[u][fr]+(i.second*fr*2)+(i.second*i.second))
				{
					dis[i.first][0]=dis[u][fr]+(i.second*fr*2)+(i.second*i.second);
					q.push({i.first,0,dis[i.first][0]});
				}
			}
			else
			{
				if(dis[i.first][i.second]>dis[u][0]+i.second*i.second)
				{
					dis[i.first][i.second]=dis[u][0]+i.second*i.second;
					q.push({i.first,i.second,dis[i.first][i.second]});
				}
			}
		}
	}
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)cin>>x>>y>>z,e[x].push_back({y,z}),e[y].push_back({x,z});
	dijkstra();
	for(int i=1;i<=n;i++)cout<<(dis[i][0]!=0x3f3f3f3f3f3f3f3f?dis[i][0]:-1)<<' ';
	return 0;
}

---

## 作者：ny_jerry2 (赞：0)

算多维最短路的模板了吧。

类似于 dp，维护三个状态：

- $u$：遍历到了那个点。
- $sc$：对于第奇数条边（奇数特指已选了奇数条边），该边权值。
- $now$：当前是第奇/偶次选择。

以下设 $dist$ 为最短路数组，$w_{a,b}$ 指 $a \to b$ 的边权。

转移：  
$$
dist_{j,w_{u,j},1}=\min_{u \to j}{dist_{u,0,0}}
$$

$$
dist_{j,0,0}=\min_{u \to j} dist_{u,sc,1} + (sc+w_{u,j})^2
$$

最后输出即可。

## 代码
```
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
int n,m;
const int N=1e5+10;
int h[N<<2],w[N<<2],e[N<<2],ne[N<<2],idx;
inline void add(int a,int b,int c){
	e[idx]=b,w[idx]=c,ne[idx]=h[a],h[a]=idx++;
}
long long dist[N][110][2];
bool st[N][110][2];
struct node{
	int u;
	long long sc,dis;
	bool now;
	bool operator<(const node &t)const{
		return dis>t.dis;
	}
};
void dj(){
	priority_queue<node> q;
	q.push({1,0,0,0});
	memset(dist,0x3f,sizeof dist);
	memset(st,0,sizeof st);
	dist[1][0][0]=0;
	while(q.size()){
		node t=q.top();
		q.pop();
		int u=t.u;
		long long sc=t.sc;
		bool now=t.now;
		if(st[u][sc][now]){
			continue;
		}
		st[u][sc][now]=1;
//		cout<<u<<' '<<sc<<' '<<now<<' '<<dist[u][sc][now]<<endl;
		for(int i=h[u];~i;i=ne[i]){
			int j=e[i];
			if(now==0){
				if(dist[j][w[i]][1]>dist[u][0][0]){
					dist[j][w[i]][1]=dist[u][0][0];
					q.push({j,w[i],dist[j][w[i]][1],1});
				}
			}else{
				if(dist[j][0][0]>dist[u][sc][1]+(sc+w[i])*(sc+w[i])){
					dist[j][0][0]=dist[u][sc][1]+(sc+w[i])*(sc+w[i]);
					q.push({j,0,dist[j][0][0],0});
				}
			}
		}
	}
}
long long ans[N];
int main(){
	memset(h,-1,sizeof h);
	cin>>n>>m;
	while(m--){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		add(a,b,c);
		add(b,a,c);
	}
	dj();
	for(int i=1;i<=n;i++){
		if(dist[i][0][0]>=1e18){
			dist[i][0][0]=-1;
		}
		printf("%lld ",dist[i][0][0]);
	}
	return 0;
}
```

---

## 作者：AK_heaven (赞：0)

### [CF1486E](https://www.luogu.com.cn/problem/CF1486E)

首先第一时间想到 $F_{i, j}$ 表示从 $1$ 号节点到 $i$ 号节点上一条边为 $j$ 权值的最短距离。约定 $j = 0$ 时，表示经过边数为偶数。所以答案就是 $F_{i, 0}$。

如果直接 DP 转移会直接懵逼，因为这张无向图上根本就没有拓扑序，也就不存在子结构，所以 DP 是不能做的。于是转换思路，用图论算法最短路来做，时间复杂度为 $O(n w \log m)$，$4s$ 时间随便通过。

**The code**


```cpp
#include<bits/stdc++.h>

#define L(i, a, b) for(int i = (a); i <= (b); i++)
#define R(i, a, b) for(int i = (a); i >= (b); i--)
#define ll long long

using namespace std;

const int N = 2e5 + 10;

int dis[N][51], n, m, h[N], tot, vis[N][51];

struct Edge {
	int v, w, lst;
}e[N<<2];

void add(int u, int v, int w) {
	e[++tot] = {v, w, h[u]};
	h[u] = tot;
}

void dij(int s) {
	priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> q;
	dis[s][0] = 0;
	q.push({0, {s, 0}});
	bool f = 1;
	while(!q.empty()) {
			int u = q.top().second.first;
			int j = q.top().second.second;
			q.pop();
			if(vis[u][j]) continue;
			vis[u][j] = 1;
			for(int i = h[u]; i; i = e[i].lst) {
				int v = e[i].v, w = e[i].w;
				if(j == 0) {
					if(dis[v][w] > dis[u][0] + w*w)
					  dis[v][w] = dis[u][0] + w*w, q.push({dis[v][w], {v, w}});
				}
				else {
					if(dis[v][0] > dis[u][j] + 2 * j * w + w * w)
					  dis[v][0] = dis[u][j] + 2 * j * w + w * w, q.push({dis[v][0], {v, 0}});
				}
			}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);  cout.tie(0);
	cin >> n >> m;
	memset(dis, 0x3f, sizeof(dis));
	L(i, 1, m) {
		int u, v, w; cin >> u >> v >> w;
		add(u, v, w); add(v, u, w);
	}
	dij(1);
	L(i, 1, n)
	  cout << (dis[i][0] == dis[0][0] ? -1 : dis[i][0]) << ' ';
	return 0;
}

```

---

## 作者：Genius_Star (赞：0)

### 思路：

本题和 CSP-2023 普及组 T4 难度差不多，故建议降绿吧。

首先有一个朴素的思路 $dis_{i, j}$ 表示上一个点为 $j$ 走到 $i$ 的最短距离，转移是 $O(N^2 \log N^2)$ 的。

注意观察数据范围，容易发现 $w \le 50$ 是很小的；且我们只需要知道上次走过来的那条边的值，则考虑令 $dp_{i, w}$ 表示上一次走过来的边的值是 $w$（$w=0$ 表示还没有经过中转）。

此时就可以 dijkstra 转移了，时间复杂度为 $O((nw) \log (nw))$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it = l; it != r; ++it) (*it)=x
#define Full(a) memset(a, 0, sizeof(a))
#define open(s1,s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define For(i,l,r) for(register int i = l; i <= r; ++i)
#define _For(i,l,r) for(register int i = r; i >= l; --i)
using namespace std;
using namespace __gnu_pbds;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 1e5 + 10, M = 55, INF = 2e9;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
int n, m, u, v, w;
int dis[N][M];
bool f[N][M];
vector<pair<int, int>> E[N];
priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> Q;
inline void add(int u, int v, int w){
	E[u].push_back({v, w});
	E[v].push_back({u, w});
}
inline void dijkstra(int s){
	for(int i = 1; i <= n; ++i)
	  for(int j = 0; j < M; ++j)
	    dis[i][j] = INF;
	dis[s][0] = 0;
	Q.push({0, {s, 0}});
	while(!Q.empty()){
		int u = Q.top().se.fi, x = Q.top().se.se;
		Q.pop();
		if(f[u][x])
		  continue;
		f[u][x] = 1;
		for(auto t : E[u]){
			int v = t.fi, y = t.se;
			if(!x){
				if(dis[v][y] > dis[u][x] + y * y){
					dis[v][y] = dis[u][x] + y * y;
					Q.push({dis[v][y], {v, y}});
				}
			}
			else{
				if(dis[v][0] > dis[u][x] + 2 * x * y + y * y){
					dis[v][0] = dis[u][x] + 2 * x * y + y * y;
					Q.push({dis[v][0], {v, 0}});
				}
			}
		}
	}
}
bool End;
int main(){
	n = read(), m = read();
	while(m--){
		u = read(), v = read(), w = read();
		add(u, v, w);
	}
	dijkstra(1);
	for(int i = 1; i <= n; ++i){
		if(dis[i][0] == INF)
		  write(-1);
		else
		  write(dis[i][0]);
		putchar(' ');
	}
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：xiongyuhan (赞：0)

# 题意简述

给你一个无向带权图，一次只能走两条边，费用为 $(w_1 + w_2) ^ 2$ 让你求 $1$ 号点到每个点的最短路。

# 主要思路

分层图，原因是 $w$ 很小，只有 $50$ 于是可以拆点。

令 $x_i$ 为从任意点到 $x$ 点，边权为 $i$，$x_0$ 就是点 $x$。

所以建边就有两种情况：

1.如果此边作为第一段，则建边$(u_0,v_w,0)$；

2.如果此边作为第二段，则建边$(u_i,v_0,(i+w)^2)$ 其中 $i$ 表示上一条边的权值。

最后从 $1_0$ 开始跑一遍最短路就行了。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, m, k, dis[5100005];
bool vis[5100005];
struct node{
	int v, w;
	bool operator  < (const node &a) const{
		return a.w < w;
	}
};
vector<node> g[5100005];
void Dijkstra(){
	memset(dis, 0x3f, sizeof(dis));
	priority_queue<node> q;
	q.push({1, 0});
	dis[1] = 0;
	while(!q.empty()){
		int tmp = q.top().v;
		q.pop();
		if(vis[tmp]) continue;
		vis[tmp] = 1;
		for(auto i : g[tmp]){
			if(dis[tmp] + i.w < dis[i.v]){
				dis[i.v] = dis[tmp] + i.w;
				q.push({i.v, dis[i.v]});
			}
		}
	}
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	cin >> n >> m;
	for(int i = 1 ; i <= m ; i++){
		int u, v, w;
		cin >> u >> v >> w;
		g[u].push_back({v + w * n, 0});
		for(int j = 1 ; j <= 50 ; j++){
			g[u + j * n].push_back({v, (j + w) * (j + w)});
		}
		g[v].push_back({u + w * n, 0});
		for(int j = 1 ; j <= 50 ; j++){
			g[v + j * n].push_back({u, (j + w) * (j + w)});
		}
	}
	Dijkstra();
	for(int i = 1 ; i <= n ; i++){
		if(dis[i] == 4557430888798830399) cout <<"-1 ";
		else cout << dis[i] <<" ";
	}
	return 0;
}

---

## 作者：CQWDX (赞：0)

[题目传送门](https://codeforces.com/problemset/problem/1486/E)

### 题意简述

在一带权无向图上，每次只能连续经过两条边，且代价为两条边边权之和的平方。求单源最短路。

数据范围 $1\leq n\leq10^5,\ 1\leq m \leq 2\times10^5,\ 1\leq w\leq50$。

### 分析

暴力建图的话总边数为 $m^2$，会爆炸。

考虑一个路径 $u\to x\to v$，$w_1=w_{u,x},\ w_2=w_{x,v}$。

由于一次移动至少要经过两条边，所以上述代价和等价于将边权全部移到 $x\to v$ 上。

如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/z7yc53o9.png)

这样的话 $u\to x$ 就没那么重要了。在 $w_2$ 一定的情况下共有 $w=50$ 种可能的权值。

可以考虑以 $w_1$ 的值构造分层图。

令 $(w,u)$ 为入边边权为 $w$ 且入点为 $u$ 的**点集**。但是由于其并不影响结果，可以将其作为一个点。

则对于点对 $(u,x,v)$，可以将 $u$ 向 $(w_1,u)$ 连一条边权为 $0$ 的边；将 $(w_1,u)$ 向 $v$ 连一条边权为 $(w_1+w_2)^2$ 的边。

显然 $u\to v$ 的代价等价于原图。

举个例子。

分层前：

![](https://cdn.luogu.com.cn/upload/image_hosting/1t8iy6lq.png)

分层后：~~边权什么的可以自己脑补~~

![](https://cdn.luogu.com.cn/upload/image_hosting/nmcmz4ih.png)

显然，对于一个点 $u$（假定其为路径的起始点），分层后其最大出度为 $w=50$。

总边数从 $m^2$ 骤降到了 $mw$。

时间复杂度还没想出来。反正降了很多就是了。

应该是 $O(m\log m)$ 这个级别。

```cpp
#include <bits/stdc++.h>
#define layer(x, y) (x * n + y)
typedef long long ll;
const int maxn = 5.5e6 + 20;
const int maxm = 2.5e7 + 20;
struct edge {
	int u, v, w, nxt;
};
struct point {
	int u;
	ll dis;
	friend bool operator < (point a, point b) {
		return a.dis > b.dis;
	}
	point(int a, ll b) {
		u = a, dis = b;
	}
};
int head[maxn], idx;
edge e[maxm];
void add(int x, int y, int z) {
	idx++;
	e[idx].u = x, e[idx].v = y, e[idx].w = z;
	e[idx].nxt = head[x], head[x] = idx;
}
ll dis[maxn];
bool mk[maxn];
void dijkstra(int st) {
	memset(dis, 0x3f, sizeof dis);
	std::priority_queue<point> q;
	dis[st] = 0;
	q.push(point(st, 0));
	while(!q.empty()) {
		int u = q.top().u;
		q.pop();
		if(mk[u]) continue;
		mk[u] = 1;
		for(int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].v, w = e[i].w;
			if(dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				q.push(point(v, dis[v]));
			}
		}
	}
}
int n, m, st, des;
int main() {
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= m; i++) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		add(x, layer(z, y), 0);
		add(y, layer(z, x), 0);
		for(int w = 1; w <= 50; w++) {
			add(layer(w, x), y, (w + z) * (w + z));
			add(layer(w, y), x, (w + z) * (w + z));
		}
	}
	dijkstra(1);
	for(int i = 1; i <= n; i++)
		printf("%lld ", dis[i] > 4e18 ? -1 : dis[i]);
	return 0;
}
```

---

## 作者：Cure_Wing (赞：0)

[CF1486E Paired Payment](https://www.luogu.com.cn/problem/CF1486E)

### 思路

我们发现连续走两条边的权值是 $(w_1+w_2)^2$，无法分成两段表示。这样子的话我们让这两条边全部走完后再处理。而走完后我们一定知道第二条边，但第一条边我们不知道。所以我们跑最短路时多记录一维表示第一条边的权值。

对于一个点，它如果是途径点，我们的第二维记录上一条边的权值；它如果是终点，我们让它的第二维为 $0$，表示到这个点已经走完两条边，并且此时将这一条边权与上一条转移的边权合并计算总权值。

最短路跑 Dijkstra，完全没有问题。

时间复杂度为 $O(m\log m)$，带 $2$ 倍常数，因为每条边存在第一条和第二条两种状态。这样做跑得飞快，而且边权无论开到多少也完全没有问题。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>
using std::cin;using std::cout;
constexpr int N=100005,K=51,inf=1e9;
int n,m,u,v,w,dis[N][K];
bool vis[N][K];
struct A{int v,w;};
struct B{
	int u,val,dis;
	inline bool operator<(const B &a)const{return dis>a.dis;}
};
std::vector<A>edge[N];
std::priority_queue<B>q;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n>>m;memset(dis,0x3f,sizeof(dis));dis[1][0]=0;
	for(int i=1;i<=m;++i){
		cin>>u>>v>>w;
		edge[u].push_back(A{v,w});
		edge[v].push_back(A{u,w});
	}
	q.push(B{1,0,0});
	while(!q.empty()){
		B k=q.top();q.pop();
		if(vis[k.u][k.val]) continue;
		vis[k.u][k.val]=1;
		for(A i:edge[k.u]){
			if(k.val){
				if(dis[k.u][k.val]+(k.val+i.w)*(k.val+i.w)<dis[i.v][0]){
					dis[i.v][0]=dis[k.u][k.val]+(k.val+i.w)*(k.val+i.w);
					q.push(B{i.v,0,dis[i.v][0]});
				}
			}else{
				if(dis[k.u][0]<dis[i.v][i.w]){
					dis[i.v][i.w]=dis[k.u][0];
					q.push(B{i.v,i.w,dis[i.v][i.w]});
				}
			}
		}
	}
	for(int i=1;i<=n;++i) cout<<(dis[i][0]>inf?-1:dis[i][0])<<' ';
	return 0;
}
```

### 说明

题解区中普遍存在一种错误做法，在一开始就建出边权小于或等于 $w_i$ 的所有的边，这样子会导致许多不存在的点被访问。尽管这样会使这条路径成为死胡同，并不会导致答案错误，但是这些边依旧会被经过。于是这种算法的时间复杂度尽管也是 $O(m\log m)$，但是却带了 $w_i+1=51$ 倍的常数，很容易超时，要经过精细的卡常或者评测机波动以极小的空隙通过。

---

## 作者：liuyi0905 (赞：0)

### 题目大意：
有一张 $n$ 个点、$m$ 条带权边的无向图，一次可以走两条边，费用为 $(w_1+w_2)^2$，求从点 $1$ 到每一个点的最少费用。
### 思路：
本题的 $w$ 较小，可以把 $w$ 当作层数，做分层图。

建边时，把点 $u$ 的第 $0$ 层连向点 $v$ 的第 $w$ 层，边权为 $0$，然后反着建一次；把点 $u$ 所有层连向点 $v$ 的第 $0$ 层，边权为 $(q+w)^2$，$q$ 为层数。

接下来跑一遍最短路即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e6+1e5+5;
long long n,m,dis[N];
bool vis[N];
struct edge{
    int to,val;
    bool operator<(const edge&a)const{return val>a.val;}
};
vector<edge>nbr[N];
int cmp(edge x,edge y){return x.val>y.val;}
void dijkstra(){
    priority_queue<edge>pq;
    fill(dis+2,dis+51*n+1,1e18);
    pq.push({1,0});
    for(;!pq.empty();){
        int cur=pq.top().to;
        pq.pop();
        if(vis[cur])continue;
        vis[cur]=1;
        for(auto nxt:nbr[cur])
            if(dis[nxt.to]>dis[cur]+nxt.val){
                dis[nxt.to]=dis[cur]+nxt.val;
                pq.push({nxt.to,dis[nxt.to]});
            }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    for(cin>>n>>m;m;m--){
        int u,v,w;
        cin>>u>>v>>w;
        nbr[u].push_back({v+w*n,0});
        nbr[v].push_back({u+w*n,0});
        for(int j=1;j<=50;j++){
            nbr[u+j*n].push_back({v,pow(w+j,2)});
            nbr[v+j*n].push_back({u,pow(w+j,2)});
        }
    }
    dijkstra();
    for(int i=1;i<=n;i++)cout<<(dis[i]!=1e18?dis[i]:-1)<<" ";
    return 0;
}
```

---

## 作者：GenesisCrystal (赞：0)

~~为什么这题我第一眼不是分层图啊。~~

## 思路

### 暴力
提供一种暴力思路：先正常建边（使用邻接表），然后枚举每一个点，向外拓展两次（不能是自己)，将边权设成 $(w_1+w_2)^2$ 就行了。

具体来说，就是把一条 $x\overset{w_1}\rightarrow u\overset{w_2}\rightarrow y$ 的边变成一条 $x\overset{(w_1+w_2)^2}\rightarrow y$ 的边。

此方法能打 $87$，被 $\text C \text F$ 第 $8$ 个点卡住了。

### 正解
~~众所不周知：看一道题目先看题面，再看范围。~~

看到数据范围： $w \le 50$，此时就可以拆点了。

将一个点 $u$ 拆成 $51$ 个点 $u_0, u_1, u_2, u_3, \cdots, u_n$，对于图中所有点，$u_i$ 的编号是，其中如果下标 $0 < i \le 50$，则 $u_i$ 的意义是“上一条边的边长为 $i$，到达 $u$ 点”。

所以对于一条边 $u \overset{w} \rightarrow v$，建 $u_0 \overset{0} \rightarrow v_w, u_i \overset{(w + i) ^ 2} \rightarrow v_0(1 \le i \le 50)$。

~~不知道为什么会 MLE。~~

注意事项：

1. 只能用 Dijkstra，某死去的玩意儿已经死去了，别管了。

1. 数组大小要开 $5 \times 10^6 + 10^5$ 的大小（其实就是 $51\times10^5$）。

1. 不用开 $\text{long long}$。

1. 要关闭同步流

## Code
```cpp
#include <iostream>
#include <queue>
#include <cstring>

using namespace std;
using pii = pair<int, int>;

const int kMaxN = 5e6 + 1e5 + 1;

bool f[kMaxN];
int n, m;
vector<pii> g[kMaxN];
struct Node {
	int u, w;
	Node(int u, int w) : u(u), w(w) {}
	bool operator<(Node a) const {
		return w > a.w;
	}
};

void add(int u, int v, int w) {
	for (int i = 1; i <= 50; i++) {
		g[u + i * n].push_back({v, (i + w) * (i + w)});
	}
	g[u].push_back({v + w * n, 0});
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1, u, v, w; i <= m; i++) {
		cin >> u >> v >> w;
		add(u, v, w), add(v, u, w);
	}
	priority_queue<Node> q;
	q.push(Node(1, 0));
	int dis[kMaxN];
	memset(dis, 0x3f, sizeof(dis));
	dis[1] = 0;
	while (!q.empty()) {
		Node t = q.top();
		q.pop();
		if (f[t.u]) {
			continue;
		}
		f[t.u] = 1;
		for (int j = 0; j < g[t.u].size(); j++) {
			pii i = g[t.u][j];
			if (dis[i.first] > dis[t.u] + i.second) {
				dis[i.first] = dis[t.u] + i.second;
				q.push(Node(i.first, dis[i.first]));
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		cout << (dis[i] > 1e9 ? -1 : dis[i]) << ' ';
	}
	return 0;
}
```

---

