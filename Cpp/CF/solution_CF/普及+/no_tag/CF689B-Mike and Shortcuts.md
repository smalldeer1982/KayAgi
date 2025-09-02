# Mike and Shortcuts

## 题目描述

Recently, Mike was very busy with studying for exams and contests. Now he is going to chill a bit by doing some sight seeing in the city.

City consists of $ n $ intersections numbered from $ 1 $ to $ n $ . Mike starts walking from his house located at the intersection number $ 1 $ and goes along some sequence of intersections. Walking from intersection number $ i $ to intersection $ j $ requires $ |i-j| $ units of energy. The total energy spent by Mike to visit a sequence of intersections $ p_{1}=1,p_{2},...,p_{k} $ is equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689B/cc97750fb7205e858b8008fe7ee7f7055a90a20f.png) units of energy.

Of course, walking would be boring if there were no shortcuts. A shortcut is a special path that allows Mike walking from one intersection to another requiring only $ 1 $ unit of energy. There are exactly $ n $ shortcuts in Mike's city, the $ i^{th} $ of them allows walking from intersection $ i $ to intersection $ a_{i} $ ( $ i<=a_{i}<=a_{i+1} $ ) (but not in the opposite direction), thus there is exactly one shortcut starting at each intersection. Formally, if Mike chooses a sequence $ p_{1}=1,p_{2},...,p_{k} $ then for each $ 1<=i&lt;k $ satisfying $ p_{i+1}=a_{pi} $ and $ a_{pi}≠p_{i} $ Mike will spend only $ 1 $ unit of energy instead of $ |p_{i}-p_{i+1}| $ walking from the intersection $ p_{i} $ to intersection $ p_{i+1} $ . For example, if Mike chooses a sequence $ p_{1}=1,p_{2}=a_{p1},p_{3}=a_{p2},...,p_{k}=a_{pk-1} $ , he spends exactly $ k-1 $ units of total energy walking around them.

Before going on his adventure, Mike asks you to find the minimum amount of energy required to reach each of the intersections from his home. Formally, for each $ 1<=i<=n $ Mike is interested in finding minimum possible total energy of some sequence $ p_{1}=1,p_{2},...,p_{k}=i $ .

## 说明/提示

In the first sample case desired sequences are:

 $ 1:1 $ ; $ m_{1}=0 $ ;

 $ 2:1,2 $ ; $ m_{2}=1 $ ;

 $ 3:1,3 $ ; $ m_{3}=|3-1|=2 $ .

In the second sample case the sequence for any intersection $ 1&lt;i $ is always $ 1,i $ and $ m_{i}=|1-i| $ .

In the third sample case — consider the following intersection sequences:

 $ 1:1 $ ; $ m_{1}=0 $ ;

 $ 2:1,2 $ ; $ m_{2}=|2-1|=1 $ ;

 $ 3:1,4,3 $ ; $ m_{3}=1+|4-3|=2 $ ;

 $ 4:1,4 $ ; $ m_{4}=1 $ ;

 $ 5:1,4,5 $ ; $ m_{5}=1+|4-5|=2 $ ;

 $ 6:1,4,6 $ ; $ m_{6}=1+|4-6|=3 $ ;

 $ 7:1,4,5,7 $ ; $ m_{7}=1+|4-5|+1=3 $ .

## 样例 #1

### 输入

```
3
2 2 3
```

### 输出

```
0 1 2 
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
```

### 输出

```
0 1 2 3 4 
```

## 样例 #3

### 输入

```
7
4 4 4 4 7 7 7
```

### 输出

```
0 1 2 1 2 3 3 
```

# 题解

## 作者：斜揽残箫 (赞：2)

#### 【题目大意】

给定 $n$ 个点和 $n$ 条小路，求从 $1$ 号点出发到这 $n$ 个点的最短路径。

#### 【解题思路】

从 $1$ 到 $n$ 每个点之间与连接一条主干路，再把每一条小路连接上，跑一遍 Dijkstra （堆优化）即可。

~~看到没有用Dijkstra的，来发一波~~。
#### 【代码实现】

+  可用邻接表存图，也可用 vector 存图，我用的邻接表，自己熟悉的是最好的。

+ 因为是单源最短路，所以可用 spfa ,也可用 Dijkstra 。

#### 【Code】

```cpp
#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
#define ull unsigned long long
#define ll long long
#define M 1000010
#define N 1010
#define qaq cout<<"可行QAQ"<<endl
#define INF 0x3f3f3f3f
using namespace std;
/*================================================*/
int n,num;
struct node{
	int dis;
	int x;
	inline bool operator<(const node &x)const//重载小根堆
	{
		return dis>x.dis;
	}
};
struct nod{
	int next;
	int to;
}e[M];
int head[M],dis[M];
bool vis[M];//判断是否到达
/*================================================*/
inline int read()
{
	int s = 0, f = 0;char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}

void add_edge(int from,int to)//链式前向星存边
{
	e[++num].to=to;
	e[num].next=head[from];
	head[from]=num;
}

void dijkstra()
{
	priority_queue <node> qp;
	memset(dis,INF,sizeof(dis));
	dis[1]=0;
	qp.push((node){0,1});
	while(!qp.empty()){
		node cun = qp.top();//每次取出来的一定是最小的。
		qp.pop();
		int k=cun.x;
		if(vis[k]) continue;
		vis[k]=true;
		for(int i=head[k];i;i=e[i].next){
			int y=e[i].to;
			if(dis[y] > dis[k] + 1){//更新最短路
				dis[y] = dis[k] + 1;
				qp.push((node){dis[y],y});
			} 
		} 
	}
}

/*=================================================*/

signed main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int x;
		scanf("%d",&x);
		add_edge(i,x);//连接小路。
		if(i!=n) {
			add_edge(i,i+1);//连接主干路
			add_edge(i+1,i);
		}
	}
	dijkstra();//跑一遍Dijkstra
	for(int i=1;i<=n;i++){
		printf("%d ",dis[i]);
	}
	return 0;//好习惯
}
```



---

## 作者：_Gabriel_ (赞：1)

### 大意

给定 $n$ 个点和一些路径，求起点 $1$ 到这 $n$ 个节点的最短路径。

### 思路

很明显用最短路径算法。

连边：有 $n-1$ 条双向边，即相邻节点之间连边，权值为 $1$。还有题目给出的 $n$ 条单向边，为 $i$ 和题目给定的 $a_i$ 相连，权值为 $1$。

由于没有负权边，可以用 dijkstra 解决此题。

### 代码

```c++
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;
typedef long long ll;
const int INF = 0x3f3f3f3f;
const ll mod = 998244353;
const int N = 5e5 + 10;
struct edge {
	int v, w;
};
struct node {
	int dis, u;
	bool operator > (const node& a) const {
		return dis > a.dis;
	}
};
vector<edge> G[N];
ll dis[N];
int vis[N];
priority_queue<node, vector<node>, greater<node> > q;
int n, m, s;

void dijkstra(int s) {
	for (int i = 1; i <= n; i++) dis[i] = 3e18;
	dis[s] = 0;
	q.push({0, s});
	while (!q.empty()) {
    	int u = q.top().u;
    	q.pop();
    	if (vis[u]) continue;
    	vis[u] = 1;
    	for (int i = 0; i < G[u].size(); i++) {
    		int v = G[u][i].v, w = G[u][i].w;
    		if (dis[v] > dis[u] + w) {
        		dis[v] = dis[u] + w;
        		q.push({dis[v], v});
    		}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		G[i].push_back({x, 1});
		if (i != n) {
			G[i].push_back({i + 1, 1});
			G[i + 1].push_back({i, 1});
		}
	}
	dijkstra(1);
	for (int i = 1; i <= n; i++) {
		cout << dis[i] << " ";
	}
    return 0;
}
```

[提交记录](https://codeforces.com/problemset/submission/689/287595257)

---

## 作者：RiceFruit (赞：1)

## 题目大意
[题目传送门](https://www.luogu.com.cn/problem/CF689B)

给你 $n$ 个点（从 $1 \sim n$ 编号）和 $n$（ $n\le2\times10^5$ ） 条有向边，其中每条有向边的长度为 $1$。且从 $i$点走到 $j$ 点的距离为 $|i-j|$（已给出的有向边除外）。求从第 $1$ 个点出发到达其余所有点的最短距离。

## 思路

一看到题面，首先想到的肯定是把所有边都存一下，然后跑一边 `dijkstra`，求最短路即可（~~蒟蒻~~我的想法）。但看到 $n\le2\times10^5$，肯定会挂。于是便考虑另一种做法。

我们不一定需要把所有的边都存进去，只需要存相邻两个点所连的边即可。因为任何一条长度大于 $1$ 的边都可以靠长度为 $1$ 的边所连起来。这个点是题目的关键，想到这一点，这道题就可以轻松 AC 了。

剩下的就是跑一遍 `dijkstra` 即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=6e5+7;
int n;
struct sa{
	int next;
	int to;
	int w;
}e[N];
struct node{
	int x;
	int dis;
	inline bool operator<(const node &x)const
	{
		return dis>x.dis;
	}
};
priority_queue<node>q;//优先队列 
int dis[N];//存距离 
bool vis[N];//标记 
int h[N],cnt;
void add(int u,int v,int w){//添边 
	e[++cnt]={h[u],v,w},h[u]=cnt;
}
void dijk(){//跑一遍dijkstra 
	memset(dis,0x3f,sizeof(dis));
	dis[1]=0;
	q.push({1,0});
	while(q.size()){
		int u=q.top().x;q.pop();
		if(vis[u])continue;vis[u]=1;
		for(int i=h[u];~i;i=e[i].next){
			int v=e[i].to,w=1;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				q.push({v,dis[v]});
			}
		}
	}
	return;
}
int main(){
	memset(h,-1,sizeof(h));
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;cin>>x;
		if(i!=x)add(i,x,1);
		if(i!=1)add(i-1,i,1),add(i,i-1,1);//建边 
	}
	dijk();
	for(int i=1;i<=n;i++)
	cout<<dis[i]<<' ';
	return 0;
}
```

---

## 作者：ATION001 (赞：0)

~~不得不承认这是 BFS 的经典题目啊。~~
### 吐槽
这题目翻译是机器翻译的吧……
## 题目描述
你想要到达你城市的每一个地方，从第 $i$ 个地方到达第 $j$ 个地方消耗的能量为 $|i-j|$。

当然，你可以走小路，注意小路是**单向的**，走小路从 $i$ 到 $j$ 只需要消耗单位为 $1$ 的能量。

你需要知道从 $1$ 号地点到达每一个地方需要消耗多少能量。
## 思路
~~大家应该都能看出来这是 BFS。~~

首先从 $1$ 地点开始跑 BFS，记录从 $1$ 开始到达每一个节点需要走几步。第 $i+1$ 的节点和小路能到达的节点，也就是 $a_i$ 的值都赋值为 $b_i+1$。$b$ 数组记录的是 $1$ 走到这个节点需要走几步。

最后统一输出结果，附上我的代码。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200010],b[200010];
queue<int>q;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	fill(b+2,b+200010,INT_MAX);
	q.push(1);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	while(q.size()){
		auto x=q.front();
		q.pop();
		if(b[x-1]==INT_MAX){
			b[x-1]=b[x]+1;
			q.push(x-1);
		}
		if(b[x+1]==INT_MAX){
			b[x+1]=b[x]+1;
			q.push(x+1);
		}
		if(b[a[x]]==INT_MAX){
			b[a[x]]=b[x]+1;
			q.push(a[x]);
		}
	}
	for(int i=1;i<=n;i++){
		cout<<b[i]<<' ';
	}
	return 0;
}
```

---

## 作者：orz_z (赞：0)

~~水题解的一天。~~

### 题目大意

给定 $n$ 个点 任意两点 $i,j$ 间有权值为 $|i-j|$ 的双向边，另有 $n$ 条权值为 $1$ 的单向边，求以 $1$ 为起点的单源最短路径。

$1\leqslant n\leqslant200000$



### 解题思路

由于 $n$ 太大了，$n^2$ 条边不能接受。

考虑简化， 发现 $i \to \ k$ 之间的边可以由 $\forall i \leq j<k,j \to j+1$ 这些权值为 $1$ 的边拼成。

然后跑 `dij` 最短路即可

总时间复杂度是 $\mathcal{O}(n\log n)$。



### CODE

```cpp
#include <bits/stdc++.h>

using namespace std;

const int _ = 200005;

int tot, head[_], to[_ * 3], nxt[_ * 3], w[_ * 3];

int vis[_], dis[_];

void add(int x, int y, int z)
{
    to[++tot] = y;
    w[tot] = z;
    nxt[tot] = head[x];
    head[x] = tot;
}

void dij()
{
    priority_queue<pair<int, int>> q;
    memset(dis, 0x3f, sizeof dis);
    q.push(make_pair(0, 1));
    dis[1] = 0;
    while (!q.empty())
    {
        int x = q.top().second;
        q.pop();
        if (vis[x])
            continue;
        vis[x] = 1;
        for (int i = head[x]; i; i = nxt[i])
        {
            int y = to[i], z = w[i];
            if (dis[y] > dis[x] + z)
            {
                dis[y] = dis[x] + z;
                q.push(make_pair(-dis[y], y));
            }
        }
    }
}

int n;

signed main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; i++)
    {
        add(i, i + 1, 1);
        add(i + 1, i, 1);
    }
    for (int i = 1; i <= n; i++)
    {
        int x;
        scanf("%d", &x);
        add(i, x, 1);
    }
    dij();
    for (int i = 1; i <= n; i++)
        printf("%d ", dis[i]);
    return 0;
}
```



---

## 作者：_Dreamer_ (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF689B)

### 题目简述

给定 $n$ 个点 任意两点 $i,j$ 间有权值为 $|i-j|$ 的双向边  另有 $n$ 条权值为 $1$ 的单向边  求以 $1$ 为起点的单源最短路径

$1\leqslant n\leqslant200000$

### solution

发现 $n$ 太大了 $n^2$ 条边不能接受  发现    $\ i \to  \ k\quad (\,i< j)$ 之间的边可以由  $i\to  j\ $之间的边和  $j\to k(\,i< j< k\,)$  之间的边 拼成

所以我们只需要从 $i$ 向  $i+1$ 连接权值为 $1$ 的边即可

题目中给定的单向边  按照题目要求即可

最后边的数量 $3n$ 左右

跑最短路即可

总时间复杂度是 $O(n+n\log n)$ 

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
const int M=N*3;
int head[N],ver[M],nxt[M],edge[M],cnt;
int v[N],d[N];
void add(int x,int y,int z)
{
	ver[++cnt]=y;
	edge[cnt]=z;
	nxt[cnt]=head[x];
	head[x]=cnt;
}
void dij()
{
	priority_queue<pair<int,int> > q;
	memset(d,0x3f,sizeof d);
	q.push(make_pair(0,1));d[1]=0;
	while(!q.empty())
	{
		int x=q.top().second;q.pop();
		if(v[x])continue;v[x]=1;
		for(int i=head[x];i;i=nxt[i])
		{
			int y=ver[i],z=edge[i];
			if(d[y]>d[x]+z)
			{
				d[y]=d[x]+z;
				q.push(make_pair(-d[y],y));
			}
		}
	} 
}
int n;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		add(i,i+1,1);
		add(i+1,i,1);
	}
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		add(i,x,1);
	}
	dij();
	for(int i=1;i<=n;i++)
	{
		printf("%d ",d[i]);
	}
	return 0;
}

```

---

## 作者：dalao_see_me (赞：0)

这一题，乍一看题目很长，实则很简单。

我们怎么做呢？

没有负权边，考虑一波dijkstra。

但是，这巨高的复杂度显然我们承受不了，所以我们可以采用堆优化以后的dijkstra。

不会堆优化请转[P4779](https://www.luogu.com.cn/problem/P4779)。

## 代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define mp(a,b) make_pair(a,b)
struct edge{
	int to,nxt;
	int w;
}e[1000086];
int dis[200086];
int last[200086],vis[200086];
int n,m,s=1,cnt;
priority_queue<pii,vector<pii>,greater<pii> >q;
//因为要找最短路，所以用小根堆
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
} 
inline void add(int u,int v,int w){
	e[++cnt].to=v;
	e[cnt].w=w;
	e[cnt].nxt=last[u];
	last[u]=cnt;
}
inline void djstr(){
	memset(dis,0x7f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	q.push(mp(0,s));
	dis[s]=0;
	while(!q.empty()){
		int p=q.top().second;
		q.pop();
		if(vis[p])continue;
		vis[p]=1;
		for(int i=last[p];i;i=e[i].nxt){
			int to=e[i].to;
			if(!vis[to]&&dis[to]>dis[p]+e[i].w){
				dis[to]=dis[p]+e[i].w;
				q.push(mp(dis[to],to));
			}
		}
	}
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++)
		if(i!=n){
			add(i,i+1,1);//大路
			add(i+1,i,1);
		}
	for(int i=1;i<=n;i++){
		int x=read();
		add(i,x,1);//小路，注意不能回头走
	}
	djstr();
	for(int i=1;i<=n;i++)printf("%lld ",dis[i]);
	return 0;
}
```


---

## 作者：pnpn111 (赞：0)

蒟蒻的第一篇题解

题目翻译：
```
最近，小贝忙于学习，考试和比赛。现在她想出去在城市里逛逛放松一下。

城市有n个路口，从1到n编号。小贝家在1号路口，她从1号路口出发，走过一系列的路口。从路口i到路口j需要消耗|i - j|单位的能量。她走过一系列路口p1 = 1, p2, ..., pk 消耗的总能量等于 。

当然，如果没有小路，一味步行是比较无聊的。小路是特别的路径，能让小贝从一个路口到另一个路口只消耗1单位的能量。小贝的城市总共恰好有n条小路，第i条小路允许小贝从路口i走到路口ai (i ≤ ai ≤ ai + 1) (但不能反方向走)，因此每个路口都有且只有一条小路。严格来说，如果小贝选择一系列路口p1 = 1, p2, ..., pk，那么对于每个1 ≤ i < k 满足pi + 1 = api，并且api ≠ pi，从路口pi到路口pi + 1，小贝只会消耗1单位能量，而不是|pi - pi + 1|。 例如，如果小贝选择路口序列p1 = 1, p2 = ap1, p3 = ap2, ..., pk = apk - 1，她总共消耗k - 1单位的能量。

在她开始闲逛之前，她请你帮她计算从她家到达每个路口最少消耗多少能量。

输入
第一行包含一个整数n (1 ≤ n ≤ 200 000) ，表示小贝城市的路口数量。

第二行包含n个整数a1, a2, ..., an (i ≤ ai ≤ n , ，给出小贝城市的小路，允许小贝只消耗1单位能量从路口i到路口ai。请注意小路不能走反方向(从ai到i)。

输出
输出n个整数m1, m2, ..., mn，其中mi表示从路口1到路口i的最小能量花费。
```


~~已提交题目翻译，也许不久后就能在题目界面上看到我的翻译了~~

这是一道最短路问题，直接用SPFA解决就好了

SPFA详细过程讲解：[最短路径问题---SPFA算法详解](https://blog.csdn.net/qq_35644234/article/details/61614581)

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int maxn=200005;
const long long inf=0x3f3f3f3f;

int n,dis[maxn];  //dis存的是最后的结果
bool inQue[maxn];
vector <int> a[maxn];
queue <int> que;

int main()
{
    cin>>n;    //输入，初始化部分
    for(int i=1;i<n;i++)
        dis[i]=inf;
    dis[0]=0;
    inQue[0]=true;
    for(int i=0;i<n;i++)
    {
        int ls;
        cin>>ls;
        a[i].push_back(ls-1);   //分别和两边的路口和捷径的目的地相连
        if(i>0)
            a[i].push_back(i-1);
        if(i<n-1)
            a[i].push_back(i+1);
    }
    que.push(0);    //从出发点开始
    while(!que.empty())
    {
        int w=que.front();
        inQue[w]=false;  
        que.pop();
        int len=a[w].size();
        for(int i=0;i<len;i++)
        {
            int ls=dis[a[w][i]];
            dis[a[w][i]]=min(dis[a[w][i]],dis[w]+1);    //选择原来的和新的走法中小的值
            if(ls!=dis[a[w][i]]&&!inQue[a[w][i]])    //如果值变动了，又没有在队列中，就把它加进去
            {
                que.push(a[w][i]);
                inQue[a[w][i]]=true;
            }
        }
    }
    for(int i=0;i<n;i++)
        cout<<dis[i]<<" ";
    return 0;
}

```


---

## 作者：durbin中将 (赞：0)

最短路-没什么好说的
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=200010;
const int inf=100000001;
int n,m;
bool vis[maxn];
int dist[maxn];
vector<int> G[maxn];
void addedge(int u,int v)//建边-函数
{
	G[u].push_back(v);
}
void spfa()
{
	for(register int i=1;i<=n;i++)
		dist[i]=inf;
	dist[1]=0;
	vis[1]=true;
	queue<int> q;
	q.push(1);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		vis[u]=false;
		for(register int i=0;i<G[u].size();i++)
		{
			int v=G[u][i];
			if(dist[v]>dist[u]+1)
			{
				dist[v]=dist[u]+1;
				if(!vis[v])
				{
					vis[v]=true;
					q.push(v);
				}
			}
		}
	}
}
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		addedge(i,x);
		if(i!=n) addedge(i,i+1),addedge(i+1,i);
	}//按照题意建边
	spfa();//调用spfa
	for(register int i=1;i<=n;i++)
		printf("%d ",dist[i]);//愉快输出
	return 0;
}
```

---

