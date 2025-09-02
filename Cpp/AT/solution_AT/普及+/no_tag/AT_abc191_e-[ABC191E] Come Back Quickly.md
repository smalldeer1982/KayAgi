# [ABC191E] Come Back Quickly

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc191/tasks/abc191_e

AtCoder 国には、町 $ 1 $ から町 $ N $ までの $ N $ 個の町と、道路 $ 1 $ から道路 $ M $ までの $ M $ 本の道路があります。  
 道路 $ i $ は町 $ A_i $ から町 $ B_i $ への一方通行で、通るのに $ C_i $ 分かかります。$ A_i\ =\ B_i $ かもしれませんし、同じ町の組を結ぶ道路が複数あるかもしれません。  
 高橋君はこの国で散歩をしようと考えました。ある町から出発し、$ 1 $ 本以上の道路を通り、出発した町に帰ってくるような経路を**正しい散歩経路**と呼ぶことにします。  
 各町について、その町から出発する正しい散歩経路が存在するかを判定してください。また、存在するなら、そのような経路を通るのにかかる時間の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 2000 $
- $ 1\ \le\ M\ \le\ 2000 $
- $ 1\ \le\ A_i\ \le\ N $
- $ 1\ \le\ B_i\ \le\ N $
- $ 1\ \le\ C_i\ \le\ 10^5 $
- 入力は全て整数

### Sample Explanation 1

道路 $ 1,\ 2,\ 3 $ によって、町 $ 1,\ 2,\ 3 $ は一周に $ 30 $ 分かかる一つの輪のように繋がっています。 町 $ 4 $ から町 $ 1,\ 2,\ 3 $ に行くことはできますが、町 $ 4 $ に帰ってくることはできません。

### Sample Explanation 2

$ A_i\ =\ B_i $ であるような道路が存在するかもしれません。 この場合、町 $ 1 $ からは、道路 $ 6 $ だけを使って $ 10 $ 分で町 $ 1 $ に帰ってくることができます。

### Sample Explanation 3

同じ町の組を結ぶ道路が複数あるかもしれないことに注意してください。

## 样例 #1

### 输入

```
4 4
1 2 5
2 3 10
3 1 15
4 3 20```

### 输出

```
30
30
30
-1```

## 样例 #2

### 输入

```
4 6
1 2 5
1 3 10
2 4 5
3 4 10
4 1 10
1 1 10```

### 输出

```
10
20
30
20```

## 样例 #3

### 输入

```
4 7
1 2 10
2 3 30
1 4 15
3 4 25
3 4 20
4 3 20
4 3 30```

### 输出

```
-1
-1
40
40```

# 题解

## 作者：fengenrong (赞：2)

我们其实可以使用最短路，用 Dijkstra 的优化去求。

#### Dijkstra 的优化
首先，定义数组 $dis$ 存储源点到其他各点的最短距离，初始时 $dis_{start}$ 为 $0$， 其余各元素均为无穷大，并且使用一个 $vis$ 数组存储当前这个数是否已经确定最短路。并且不断遍历所有顶点，先取当前 $dis$ 的最小值，标记一下，然后松弛它的邻接点。

再回到这题，这题我们不能直接标记，我们可以先将 $start$ 的邻接点放入优先队列当中，然后不断松弛。最后看一下 $dis_{start}$ 与 $dis_0$ 是否相等，如相等，输出 `-1`，否则输出 $dis_{start}$。

### 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAX=2*1e3+5; 
struct op{//链式前项星
	int from,to,sum;
}a[MAX];
int head[MAX];
int cnt;
int n,m;
void hb(int x,int y,int z)//合并
{
	a[cnt].from=head[x];
	a[cnt].to=y;
	a[cnt].sum=z;
	head[x]=cnt++;
}
struct node{
	int sum,num;//分别存值与编号
	node() {}
    node(int a,int b) : sum(a), num(b) {}
	bool operator<(const node &x)const//重载运算符
	{
		return sum<x.sum;
	}
	bool operator>(const node &x)const//重载运算符
	{
		return sum>x.sum;
	}
};
priority_queue<node, vector<node>, greater<node> > q;//优先队列
int DIS(int x)
{
	int dis[MAX];
	memset(dis,63,sizeof(dis));//初始化
	bool vis[MAX];
	memset(vis,0,sizeof(vis));//初始化
	while(!q.empty())//初始化
	{
		q.pop();
	}
	for(register int i=head[x];i!=-1;i=a[i].from)
	{
		dis[a[i].to]=min(dis[a[i].to],a[i].sum);
	}
	for(register int i=1;i<=n;i++)
	{
		if(dis[i]!=dis[0])
		{
			q.push(node(dis[i],i));//放入优先队列
		}
	}
	while(!q.empty())//Dijkstra的优化
	{
		int NUM=q.top().num;
		q.pop();
		if(vis[NUM]==1)//标记过的跳过
		{
			continue;
		}
		for(register int i=head[NUM];i!=-1;i=a[i].from)//遍历邻接点
		{
			int jkl=a[i].to;
			if(dis[jkl]>dis[NUM]+a[i].sum)//松弛
			{
				dis[jkl]=dis[NUM]+a[i].sum;
				q.push(node(dis[jkl],jkl));//放入优先队列
			}
		}
	}
	return dis[x]==dis[0]?-1:dis[x];//返回答案
}
signed main()
{
	memset(head,-1,sizeof(head));//初始化
	cin>>n>>m;
	for(register int i=1;i<=m;i++)
	{
		int x,y,z;
		cin>>x>>y>>z;//输入
		hb(x,y,z);
	}
	for(register int i=1;i<=n;i++)
	{
		cout<<DIS(i)<<endl;
	}
	return 0;
}
```

---

## 作者：Rannio (赞：1)

### 题面：

给你一个 $n$ 个点 $m$ 条边的有向图，第 $i$ 条边 $a_i$，$b_i$，$c_i$，表示一条单向边从 $a_i$ 到 $ b_i$，长度为 $c_i$，可能会有重边和自环。问能否从第 $i$ 号点出发然后回到该点形成一个环？可以则输出最短时间，否则输出 $-1$。

### 思路：

不难发现本题考查的是最短路。  
观察题面，发现边数与点数都较大，考虑堆优化 Dijkstra，对于每个点 $i$ 都跑一次堆优化 Dijkstra，在确定最初进行松弛的点时将点 $i$ 的邻接点放入堆即可。如连通，最后的答案即为 $dis_i$，否则为 $-1$。

```
#include<bits/stdc++.h>
using namespace std;
int a,s,d[100005],f;
int ans;
int head[100005],cnt=1;
int dis[100005];
int vis[100005];
struct jntm{
    int to,next,val;
}edge[100005];
struct node{
    int qz,bh;
    bool operator>(const node& x)const{
        return qz>x.qz;
    }
};
priority_queue<node,vector<node>,greater<node> > q;
void add(int x,int y,int z){
    edge[cnt].to=y;
    edge[cnt].next=head[x];
    edge[cnt].val=z;
    head[x]=cnt++;
}
int dij(int x){
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    while(q.size()){
        q.pop();
    }
    for(int i=head[x];i;i=edge[i].next){
        int y=edge[i].to;
        dis[y]=min(dis[y],edge[i].val);
        q.push(node{dis[y],y});
    }
    while(q.size()){
        int u=q.top().bh;
        q.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=1;
        for(int i=head[u];i;i=edge[i].next){
            int y=edge[i].to;
            if(dis[y]>dis[u]+edge[i].val){
                dis[y]=dis[u]+edge[i].val;
            }
            q.push(node{dis[y],y});
        }
    }
    return dis[x]==dis[0]?-1:dis[x];
}
int main(){
    scanf("%d%d",&a,&s);
    for(int i=1;i<=s;i++){
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        add(x,y,z);
    }
    for(int i=1;i<=a;i++){
        printf("%d\n",dij(i));
    }
    return 0;
}
```

---

## 作者：Tang_poetry_syndrome (赞：1)

## [ABC191E] Come Back Quickly 
[洛谷题面](https://www.luogu.com.cn/problem/AT_abc191_e) [Atcoder 题面](https://atcoder.jp/contests/abc191/tasks/abc191_e)
### 题目大意
$n$ 个城市 $m$ 条道路，每条路 $a_i,b_i,c_i$，表示 $a_i$ 到 $b_i$ 的单向路，需要花费 $c_i$ 单位时间走到，可能会有重边和自环。问能否从第 $i$ 个城市出发然后回到该城市形成一个环？可以则输出最短时间，否则输出 $-1$。
### 思路
优化 Dijkstra 求最小环的板子。  
先来介绍一下堆优化 Dijkstra：  
首先定义 $dis_i$ 为原点到点 $i$ 的最短距离。然后按 Dijkstra 跑最短路，不同之处在于用一个大根堆维护邻接最小距离，并以最小距离进行松弛。  
这题可以将原点的最小距离也设置成无穷大，在松弛时更新最小值，如果原点的最小距离为无穷大，则输出 `-1`，否则输出原点的最小距离。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,j,k) for(register int i=j;i<=k;i++)
#define pb push_back
int n,m,a,b,c; 
const ll INF=LONG_LONG_MAX; 
int main() {
	cin>>n>>m;
	vector<vector<pair<ll,int> > >g(n);
	f(i,1,m)cin>>a>>b>>c,g[a-1].push_back(make_pair(c,b-1));
	f(i,0,n-1){
		vector<ll>d(n,INF);
		priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > >q;
		q.push(make_pair(0LL,i));
		while(!q.empty()){
			ll c;
			int b;
			tie(c,b)=q.top();
			q.pop();
			if(c>d[b])continue;
			ll e=d[b];
			if(b==i)e=0;
			for(pair<ll,int> p:g[b]) {
				ll w=p.first;
				int u=p.second;
				if(e+w<d[u]) {
					d[u]=e+w;
					q.push(make_pair(d[u],u));
				}
			}
		}
		ll ans=d[i];
		if(ans==INF)ans=-1;
		cout<<ans<<endl;
	}
}
```
[提交记录](https://atcoder.jp/contests/abc191/submissions/46752212)

---

## 作者：lyt_awa (赞：1)

## 题目大意
$n$ 个城市 $m$ 条道路，每条路 $a_i$，$b_i$，$c_i$，表示 $a_i$ 到 $b_i$ 的单向路，需要花费 c_i 分钟走到，可能会有重边和自环。问能否从第 $i$ 个城市出发然后回到该城市形成一个环？可以输出最短时间，否则 $-1$。
## 思路
很容易想到本题考察的是最短路。

**对于一个点 $i$ 我们可以先求出其到其他所有点的最短路 $dis(i,j)$。**  
然后对于每一个点 $j$ 看一下有没有到点 $i$ 的边，若有就用 $dis(i,j)+v(j,i)$ 更新点 $i$ 的答案。

由于**说明/提示**中有：
> $1\le C_i\le 10^{5} $

则可以直接用 Dijkstra 去求最短路。

时间复杂度 $nm\log m$。

---

## 作者：CQ_Bob (赞：0)

## 分析

注意到 $1\le n,m \le 2000$，考虑打暴力。

对于一个起点 $i$，从 $i$ 出发再回到 $i$ 的情况有 $2$ 种，其代价为：

1. $i \to i$，代价为 $i$ 的自环的最小代价。

2. $i \to j \to i$，代价为 $\mathit{dis}_{i,j}+\mathit{dis}_{j,i}$。

$\mathit{dis}$ 可以暴力跑 $n$ 遍最短路来预处理。而对于第 $1$ 种情况，在读入的时候判断一下是否存在即可。答案就是两者代价最小值。

## 代码

[Link](https://atcoder.jp/contests/abc191/submissions/47174496).

---

## 作者：PineappleSummer (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc191_e)

较为简单的最短路题。

考虑**能否从第 $i$ 个城市出发然后回到该城市形成一个环**，如果可以，就说明对于点对 $(i,j)$，从点 $i$ 到 点 $j$ 有路径，从点 $j$ 到点 $i$ 有路径。

对于每个点 $i$，以 $i$ 为起点跑最短路，从点 $i$ 到 点 $j$ 的最短路径长度记为 $d_j$。然后找到 $i$ 的所有入边，设另一端点为 $j$，则 $ans=\min\{d_j+a_{i,j}\}$。如果 $ans$ 没有被更新，输出 $-1$ 即可。
```cpp
for(int i=1;i<=n;i++)
{
	dijkstra(i);
	ll ans=inf;
	for(auto j:G[i])//这里是建反边，方便找到i的所有入边
		ans=min(ans,d[j.first]+j.second);
	cout<<(ans==inf?-1:ans)<<'\n';//判断是否无解
}
```

[完整代码](https://atcoder.jp/contests/abc191/submissions/44910113)，时间复杂度 $O(nm\log n)$。

---

## 作者：comcopy (赞：0)


# 题目大意
$n$ 个城市 $m$ 条道路，每条路 $a_i,b_i,c_i$，表示 $a_i$ 到 $b_i$ 的单向路，需要花费 $c_i$ 分钟走到，可能会有重边和自环。

问能否从第 $i$ 个城市出发然后回到该城市形成一个环？可以输出最短时间，否则 -1。

---

# 题目分析

不看环的话，显然是个很明显的最短路问题。

那么我们如何将环的问题解决？这里考虑到一种拆点的做法。

我们将一个点拆分为入点和出点分别存入边和出边，然后将出边往入边连一条单向边来保证图是连通的。举个例子：

```
4 4
1 2
1 3
4 1
3 1
```

首先把点 1 拆分成点 1 和 点 3，点 2 拆分成点 2 和点 4。

这样我们的连边就是这样了：
![](https://cdn.luogu.com.cn/upload/image_hosting/7rzmuolv.png)

很显然发现是不连通的，但由于我们跑最短路的时候要从存出边的点开始，所以只能将存入边的点与存出边的点连一条边，就变成了这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/b8dyzju8.png)




就变成了我们想要的形状，这时候再对每个存出边的点跑一次最短路判断它能否到达存入边的点就行了。

```cpp
#include<bits/stdc++.h>
#define mi(...) <% __VA_ARGS__ %>
using namespace std;
const int N=4010;
inline int read(){
	int x;
	scanf("%d",&x);
	return x;
}

map<int,bool>mp;

int in[N];
int n,m;

struct edge {
	int v, w;
};

struct nde {
	int dis,u;
	bool operator>(const nde& a) const {
		return dis > a.dis;
	}
};
vector<edge>e[N<<1];
int dis[N][N<<1];
bool vis[N<<1];
inline void dijkstra() {
    for(int i=1;i<=n+n;++i){
    	for(int j=1;j<=n+n;++j) dis[i][j]=1e9+7;
	}
	
    priority_queue<nde,vector<nde>,greater<nde> > q;
    for(int i=1;i<=n;++i){
    	q.push(mi(0,i));
		dis[i][i]=dis[i+n][i]=0;
		for(int i=1;i<=n+n;++i)vis[i]=0; 
	    while(!q.empty()) {
	        int u = q.top().u;
	        q.pop();
	        if(vis[u])continue;
	        vis[u]=1;
	        for (auto ed:e[u]) {
	            int v = ed.v, w = ed.w;
	            if (dis[i][v] > dis[i][u] + w) {
	                dis[i][v] = dis[i][u] + w;
	                q.push({ dis[i][v], v });
	            }
	        }
	    }
	}
   
    return;
}

signed main(){
	n=read(),m=read();
	for(int i=1;i<=m;++i){
		int x(read()),y(read()),z(read());
		++in[y];
		e[x].push_back(mi(y+n,z));
	}
	for(int i=1;i<=n;++i)
		e[i+n].push_back(mi(i,0));;
	dijkstra();
	for(int i=1;i<=n;++i)cout<<(dis[i][i+n]>=1e9+7?-1:dis[i][i+n])<<endl;
	
	return(0-0);
}
```

---

