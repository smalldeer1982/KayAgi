# 最短経路

## 题目描述

有一张 $n$ 点 $n-1$ 边的无向图，第 $i$ 条边连接点 $a_i$ 和点 $b_i$，长度为 $c_i$。请求出是否有至少一对整数 $(i,j)$ 满足：从点 $i$ 到点 $j$ 的最短路径长度恰好为 $x$？如果是，请输出`Yes`，否则请输出`No`。

## 说明/提示

#### 数据规模与约定

- $2 \le n \le 3000$
- $1 \le a_i \lt b_i \le n$
- $1 \le c_i \le 10^5$
- $1 \le x \le 10^9$
- 保证图联通

## 样例 #1

### 输入

```
3 5
1 2 3
1 3 2```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3 4
1 2 3
1 3 2```

### 输出

```
No```

## 样例 #3

### 输入

```
10 15
3 8 3
5 9 3
6 7 1
7 8 1
2 8 5
2 4 5
4 9 3
1 4 5
1 10 2```

### 输出

```
Yes```

# 题解

## 作者：chenzhiyv (赞：2)

#### 前置知识：Dijkstra

## 思路

首先，我们看到在题目描述里有最短路径的字样，那么我们就可以想到三个最短路径算法（Dijkstra，Spfa，Floyd），再一看，就会发现要求任意两点的最短距离恰好为 $x$，我们就会想到 Floyd，但 $n\le3000$，Floyd 的 $O(n^3)$ 的复杂度不能通过此题，所以考虑换算法。

考虑对每一个点做一次 Dijkstra，将所有点距这个点的最短距离存在 $dis$ 数组里,看是否有点距离恰好为 $x$，复杂度 $O(n^2\log_{2}{n} )$，极限数据需要约 $10^7$ 次基本操作，可以通过此题。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3000+10,M=6000+10;
int h[N],to[M],ne[M],w[M],idx;
int dis[N];
bool vst[N];
void add(int u,int v,int c)
{
	to[++idx]=v;
	w[idx]=c;
	ne[idx]=h[u];
	h[u]=idx;
}
int n,x;
int aaaa,ffff;
char ch;
inline int read()
{
	aaaa=0;
	ffff=1;
	ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-')
			ffff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		aaaa=(aaaa<<1)+(aaaa<<3)+(ch^48);
		ch=getchar();
	}	
	return ffff*aaaa;
}
void write(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9)
		write(x/10);
	putchar(x%10+'0');
}
void dijkstra(int s)
{
	memset(dis,63,sizeof(dis));
	memset(vst,0,sizeof(vst));
	priority_queue<pair<int,int>,vector<pair<int,int > > ,greater<pair<int,int > > >q;
	dis[s]=0;
	q.push(make_pair(0,s));
	while(!q.empty())
	{
		int u=q.top().second;
		q.pop();
		if(vst[u])
			continue;
		vst[u]=1;
		for(int i=h[u];i;i=ne[i])
		{
			int v=to[i];	
			if(dis[v]>dis[u]+w[i])
			{
				dis[v]=dis[u]+w[i];
				q.push(make_pair(dis[v],v));
			}
		}
	}
}
signed main()
{
	n=read();x=read();
	int u,v,c;
	for(int i=1;i<n;i++)
	{
		u=read();v=read();c=read();
		add(u,v,c);
		add(v,u,c);
	}
	for(int i=1;i<=n;i++)
	{
		dijkstra(i);
		for(int j=1;j<=n;j++)
		{
			if(dis[j]==x)
			{
				cout<<"Yes"<<endl;
				return 0;
			}
		}
	}
	cout<<"No"<<endl;
	return 0;
}
```

---

## 作者：easy42 (赞：0)

### 思路

最短路板子题。

显然叫我们求出全源最短路径。

这里有 $O(n^3)$ 的 Floyd，$O(n\log n)$ 的堆优化 Dijkstra，以及 $O(n^2)$ 的 Spfa。

这里直接使用堆优化 Dijkstra 就可以了。

具体来说，求出每个点与所有点的最短路，判一下是否与 $x$ 相等就好了。

### 实现
这里使用的是堆优化 Dijkstra，总时间复杂度 $O(n^2\log n)$，可以通过此题。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int X = 10001, INF = 0x3f3f3f3f;
int nex[X], p, head[X], to[X], val[X], dis[X], vis[X];
int n, x, s;

// 定义结构体 node 用于优先队列
struct node {
    int num, dis;
};

// 重载小于运算符，用于优先队列的比较
bool operator <(node a, node b) {
    return a.dis > b.dis;
}

priority_queue<node> q;

// 快读函数
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

// 快写函数
inline void write(int x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

// 添加边的函数
void addedge(int u, int v, int w) {
    nex[++p] = head[u];
    head[u] = p;
    to[p] = v;
    val[p] = w;
}

// Dijkstra 算法
void dijkstra() {
    for (int i = 1; i <= n; i++) dis[i] = INT_MAX;
    memset(vis, 0, sizeof(vis));
    node t;
    t.dis = dis[s] = 0;
    t.num = s;
    q.push(t);
    while (!q.empty()) {
        int a = q.top().num;
        q.pop();
        if (vis[a]) continue;
        vis[a] = 1;
        for (int i = head[a]; i; i = nex[i]) {
            if (!vis[to[i]] && dis[a] + val[i] < dis[to[i]]) {
                dis[to[i]] = dis[a] + val[i];
                t.num = to[i];
                t.dis = dis[to[i]];
                q.push(t);
            }
        }
    }
}

int main() {
    bool flag = false;
    int a, b, c;
    // 使用快读读取 n 和 x
    n = read();
    x = read();
    for (int i = 1; i < n; i++) {
        // 使用快读读取 a, b, c
        a = read();
        b = read();
        c = read();
        addedge(a, b, c);
        addedge(b, a, c);
    }
    for (int k = 1; k <= n; k++) {
        s = k;
        dijkstra();
        for (int j = 1; j <= n; j++) {
            if (dis[j] == x) flag = true;
        }
    }
    if (flag) {
        const char* yes = "Yes";
        for (int i = 0; yes[i]; i++) {
            putchar(yes[i]);
        }
    } else {
        const char* no = "No";
        for (int i = 0; no[i]; i++) {
            putchar(no[i]);
        }
    }
    return 0;
}
```

---

## 作者：DemonPlayer (赞：0)

### 题意：     
求出任意 $(i,j)$ 之间最短路，当最短路为 $x$ 时，输出 $\texttt {Yes}$，没有输出 $\texttt {No}$。     
### 思路：      
要求出任意节点到任意节点距离，可以使用 Floyd，但注意到 $1\le n\le 3000$ 显然会超时，所以需使用 Dijkstra 求最短路。
### Code：     
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,x,u,v,w;
vector<int> vi[3005],wi[3005];
int dist[3005];
bool vis[3005];

struct pts{
	int idx;
	int dist;
	bool operator <(const pts& x)const{
		return x.dist<dist;
	}
};

void dijk(int x){
	memset(dist,0x3f,sizeof(dist));
	dist[x]=0;
	memset(vis,0,sizeof(vis));
	priority_queue<pts> q;
	q.push({x,0});
	while(q.size()){
		u=q.top().idx;
		q.pop();
		if(vis[u]){
			continue;
		}
		vis[u]=0;
		for(int i=0;i<vi[u].size();i++){
			v=vi[u][i];
			if(dist[v]>dist[u]+wi[u][i]){
				dist[v]=dist[u]+wi[u][i];
				q.push({v,dist[v]});
			}
		}
	}
	return;
}

int main(){
	scanf("%d%d",&n,&x);
	for(int i=1;i<n;i++){
		scanf("%d%d%d",&u,&v,&w);
		vi[u].push_back(v);
		vi[v].push_back(u);
		wi[u].push_back(w);
		wi[v].push_back(w);
	}
	for(int i=2;i<=n;i++){
		dijk(i);
		for(int j=1;j<i;j++){
			if(dist[j]==x){
				cout<<"Yes";
				return 0;
			}
		}
	}
	cout<<"No";
	return 0;
}
```

---

## 作者：angiing1222 (赞：0)

题意很明确，第一眼看上去可以使用 `floyd` 解决这道题。

但是再仔细看看数据范围：

> $2\le n\le 3000$

时间复杂度为 $O(n^3)$ 的 `floyd` 明显无法解决。

接着简要分析一下题目：

> 给出一个 $n$ 点 $n-1$ 条边的无向连通图，问是否有两个点的最短路长度为 $x$。

因为这张图边数比点数少 $1$，所以这张图一定是一棵树。

考虑使用 `dijkstra` 与 `lca` ，先预处理一遍各个点到 $1$ 号点的最短路径，再枚举两个点 $i,j$，这两个点的最短距离为 $1$ 到 $i$ 的距离加上 $1$ 到 $j$ 的距离减去二倍的 $1$ 到 $i$ 和 $j$ 的最近公共祖先的距离，接着判断一下就解决问题了。

直接上 `AC` 代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
vector<pair<int,int>>G[10005];//使用vector邻接表存图
int dep[10005],f[10005][21],len[10005];
bitset<10005>vis; 
void init(int x,int fa){//倍增求lca的初始化
	dep[x]=dep[fa]+1;
	for(int i=0;i<20;++i)f[x][i+1]=f[f[x][i]][i];
	for(int i=0;i<G[x].size();++i){
		int nx=G[x][i].first;
		if(nx==fa)continue;
		f[nx][0]=x;
		init(nx,x);
	}
}
int lca(int x,int y){//倍增求lca
	if(dep[x]<dep[y])swap(x,y);
	for(int i=20;i>=0;--i){
		int nx=f[x][i];
		if(dep[nx]>=dep[y])x=nx;
		if(x==y)return x;
	}
	for(int i=20;i>=0;--i){
		if(f[x][i]!=f[y][i]){
			x=f[x][i];
			y=f[y][i];
		}
	}
	return f[x][0];
}
priority_queue<pair<int,int>>q;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
	int n,m,g=1,x;
	cin>>n>>x;
	m=n-1;
	for(int i=0;i<n-1;++i){
		int x,y,z;
		cin>>x>>y>>z;
		G[x].push_back({y,z});
		G[y].push_back({x,z});
	}
	vis.reset();
	memset(len,0x3f,sizeof(len)); 
	len[1]=0;
	q.push(make_pair(0,1));
	while(!q.empty()){//dijkstra板子
		int x=q.top().second;
		q.pop();
		if(vis[x])continue;
		vis[x]=1;
		for(int i=0;i<G[x].size();++i){
			int nx=G[x][i].first,c=G[x][i].second;
			if(len[nx]>len[x]+c){
				len[nx]=len[x]+c;
				q.push(make_pair(-len[nx],nx));
			}
		}
	}
	init(g,0);
	for(int i=2;i<=n;++i){
		for(int j=i+1;j<=n;++j){
			if(len[i]+len[j]-2*len[lca(i,j)]==x){//判断是否长度为x
				cout<<"Yes";
				return 0;
			}
		}
	}
	cout<<"No";
	return 0;
}
```

---

