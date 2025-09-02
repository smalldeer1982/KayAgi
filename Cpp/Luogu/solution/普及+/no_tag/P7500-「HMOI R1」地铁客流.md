# 「HMOI R1」地铁客流

## 题目背景

一座城市的地铁客流量是非常重要的指标，它体现了这座城市正在不断流动着的人口数量。无论通勤还是旅游，都会给这座城市的经济带来活力。

疫情期间各地地铁客流惨淡，甚至有部分城市地铁停运。现在疫情态势好转，各地陆续复工复产，地铁客流量大小也是判断城市复工复产、经济恢复率的重要参考。

## 题目描述

天穹市的地铁系统由 $M$ 条线路组成，共有 $N$ 座车站，**每座车站都会有线路停靠**。每条线路的相邻两站之间可视为由无向边连接。其中地铁 $i$ 号线上有 $k_i$ 座车站，**这些车站互不相同**。

这些线路会在一些车站相交，也就是说，一座车站可能有很多线路停靠。

现在，有 $P$ 位乘客分别想从 $s_j$ 号车站出发，去 $t_j$ 号车站，**保证这两座车站不同**。当这两座车站不在一条线路上时，他就会进行若干次换乘。作为天穹地铁的技术工作人员，你需要计算这些乘客贡献的客流量。

-------------

请注意，在这里使用的客流量计算方法和实际应用中的有所不同。

客流量 $=$ 进站客流 $+$ 换乘客流。进站客流即为乘客数；换乘客流为乘客的换乘次数。起终点之间可能会有多条路径可以选择，此时，地铁客流量与 **乘客选择的** 路径无关；计算时，我们只考虑 **换乘次数最少** 的路径。

---------

注意：

- 设从 $s$ 到 $t$ 最少进行 $\rm trans$ 次换乘，则此时要乘坐 $\rm trans + 1$ 条线路，贡献 $\rm trans + 1$ 的客流量。  
- 当乘客不能从起点到达终点时，即 $s, t$ 之间没有通路，他就会去坐公交，此时客流量计为 $0$。

## 说明/提示

样例解释：

- 默认乘客会选择换乘次数最少的路径。
- 边上的数字表示所在地铁线路的编号。

样例 1 如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/t97d5qmr.png)

乘客 $1$ 会乘坐 $1$ 号线从 $1$ 到 $3$，再乘坐 $2$ 号线从 $3$ 到 $6$；  
乘客 $2$ 会乘坐 $3$ 号线从 $4$ 到 $2$，再乘坐 $1$ 号线从 $2$ 到 $3$；  
乘客 $3$ 会乘坐 $4$ 号线从 $4$ 到 $8$；  
乘客 $4$ 会乘坐 $2$ 号线从 $6$ 到 $3$，乘坐 $1$ 号线从 $3$ 到 $2$，再乘坐 $3$ 号线从 $2$ 到 $4$，最后乘坐 $4$ 号线从 $4$ 到 $7$。

如上，四个人分别贡献了 $2, 2, 1, 4$ 的客流量，答案为 $9$。

样例 2 如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/i0lm9un9.png)

相比样例 1，  
乘客 $2$ 可以选择另外一条路线，即乘坐 $4$ 号线从 $4$ 到 $8$，再乘坐 $2$ 号线从 $8$ 到 $3$，也是换乘一次的；  
乘客 $4$ 可以选择另外一条换乘次数更少的的路线：乘坐 $4$ 号线从 $7$ 到 $8$，再乘坐 $2$ 号线从 $8$ 到 $6$，只换乘了一次。

总客流量为 $2 + 2 + 1 + 2 = 7$。

样例 3 如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/a2afk5k5.png)

相比样例 1，乘客 $2$ 和 $4$ 的出行路径不是通路，不会计入客流量。

总客流量为 $2 + 0 + 1 + 0 = 3$。

------------

设车站 $i$ 停靠的线路数为 $\mathrm{siz}_i$。  
对于所有数据：

- $2 \le N \le 10^5$；
- $1 \le M \le 1000$；
- $1 \le P \le 100$；
- $1 \le \mathrm{siz}_i \le 50$。

--------

**本题采用捆绑测试。**

| No.  | Constraints              | Score |
| ---- | ------------------------ | ----- |
| $1$  | $N, P \le 5;\ M \le 3$   | $10$  |
| $2$  | $k_i = 2$                | $20$  |
| $3$  | $N, M \le 50;\ P \le 10$ | $20$  |
| $4$  | $M \le 500;\ P \le 10$   | $20$  |
| $5$  | No further constraints   | $30$  |

------------

由于读入量较大，请勿不关流同步使用 `cin`。

你可以通过 `std::ios::sync_with_stdio(false)` 来关闭 `cin` 的流同步。

你也可以使用以下快速读入模板，支持读入 `int` 范围内的非负整数。

```cpp
int readInt() {
	int ret = 0; char o;
	while (!isdigit(o = getchar()));
	do ret = ret * 10 + (o ^ 48);
	while (isdigit(o = getchar()));
	return ret;
}
```
----------

- Idea: 南桥汽车站
- Solution: 南桥汽车站
- Code: 南桥汽车站
- Data: 南桥汽车站

## 样例 #1

### 输入

```
8 4 4
4 1 2 3 5
2 3 6
2 2 4
3 7 4 8
1 6
4 3
4 8
6 7```

### 输出

```
9```

## 样例 #2

### 输入

```
8 4 4
4 1 2 3 5
3 6 3 8
2 2 4
3 7 4 8
1 6
4 3
4 8
6 7```

### 输出

```
7```

## 样例 #3

### 输入

```
8 3 4
4 1 2 3 5
2 3 6
3 7 4 8
1 6
4 3
4 8
6 7```

### 输出

```
3```

# 题解

## 作者：zhuweiqi (赞：3)

本题的思路非常巧妙，是一道不可多得的带思维的广搜好题，下面我将循序渐进地教大家如何解决本题（特别地，在本篇题解中，所有变量均会统一用小写字母表示）。

一开始，我粗略地看完题目之后，脑海中冒出来的第一个想法是跑 $p$ 遍单源最短路，由于路径权值只有 $0$ 和 $1$，因此可以简化成一个关于 bfs 的问题，每次扩展的范围就是所有经过当前车站的线路停靠的所有站点，对于每个询问，如果车站 $s$ 能扩展到车站 $t$，就让 $ans$ 加上对应的贡献值， 最后输出 $ans$。我花了 $20$ 分钟时间将我这个想法成功地实现了出来：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0' && c<='9'){
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	return x;
}
const int N=100002,M=1002;
vector<int> line[M];
vector<int> station[N];
int f[N];
queue<int> q;
void bfs(){
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(auto l:station[x]){
			for(auto s:line[l]){
				if(f[s]==-1){
					f[s]=f[x]+1;
					q.push(s);
				}
			}
		}
	}
	return;
}
int main(){
	int n=read(),m=read(),p=read(),k,x,s,t,ans=0;
	for(int i=1;i<=m;i++){
		k=read();
		while(k--){
			x=read();
			line[i].push_back(x);
			station[x].push_back(i);
		}
	}
	while(p--){
		s=read(),t=read();
		memset(f,-1,sizeof(f));
		q.push(s);
		f[s]=0;
		bfs();
		if(f[t]!=-1) ans+=f[t];
	}
	printf("%d",ans);
	return 0;
}
```

[Unfortunately](https://www.luogu.com.cn/record/123202892)，T 飞了。

仔细地分析了一下这个代码的时间复杂度，发现最坏情况下~~竟然~~是 $O(pn^2)$ 的。很显然，这个时间复杂度级别的代码无论怎么优化都不可能卡过去。

此时，我们就需要改变解决本题的思路。我们在数据范围内发现到一个很奇怪的东西，每个车站停靠的线路数量不超过 $50$，然后再结合着 $m\leq 1000$ 一起看，我们是否能将主要的时间复杂度转移到 $m$ 上去呢？继续深入地思考一下，我们发现刚才的那个 bfs 貌似是按照地铁线路，一个一个车站地去扩展的，诶？那我们为什么不把车站放一边，直接按照地铁线路去扩展呢？

至此，正解大致的思路已经出来了，首先我们用一个邻接矩阵存储两条线路之间是否有共同停靠的站点，接着把邻接矩阵用邻接表存储节约之后 bfs 的时间，然后预处理 $dis$ 数组（$dis_{i,j}$ 表示从第 $i$ 条线路到第 $j$ 条线路至少需要换乘几次，注意，需要初始化整个数组为一个小于 $0$ 的值，并且要把 $dis_{i,i}$ 的值初始化为 $0$），这个过程可以通过 $n$ 遍 bfs 来实现，最后，对于每个询问，枚举第一条线路和最后一条线路（即枚举停靠车站 $s$ 和车站 $t$ 的线路），输出贡献值的总和即可，设 $a$ 为 $siz_i$ 中的最大值，则时间复杂度最坏情况下为 $O(m^2+a^2n)$，可以通过本题（[link](https://www.luogu.com.cn/record/123206403)）！参考代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0' && c<='9'){
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	return x;
}
const int N=100002,M=1002,inf=1e9;
vector<int> station[N];
bool con[M][M];
vector<int> c[M];
int dis[M][M];
queue<int> q;
void bfs(int st){
	dis[st][st]=0;
	q.push(st);
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(auto y:c[x]){
			if(dis[st][y]==-1){
				dis[st][y]=dis[st][x]+1;
				q.push(y);
			}
		}
	}
	return;
}
int main(){
	int n=read(),m=read(),p=read(),k,x,s,t,ans=0;
	for(int i=1;i<=m;i++){
		k=read();
		while(k--){
			x=read();
			station[x].push_back(i);
		}
	}
	for(int i=1;i<=n;i++){
		for(auto u:station[i]){
			for(auto v:station[i]){
				con[u][v]=con[v][u]=1;
			}
		}
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			if(con[i][j]){
				c[i].push_back(j);
			}
		}
	}
	memset(dis,-1,sizeof(dis));
	for(int i=1;i<=m;i++) bfs(i);
	while(p--){
		s=read(),t=read();
		int mins=inf;
		for(auto u:station[s]){
			for(auto v:station[t]){
				if(dis[u][v]!=-1){
					mins=min(mins,dis[u][v]+1);
				}
			}
		}
		if(mins!=inf) ans+=mins;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Somebody_lmm (赞：2)

# P7500 地铁客流

[题目传送门](https://www.luogu.com.cn/problem/P7500)

感谢 @[ruojiyz](https://www.luogu.com.cn/user/557781) 提供的思路。

---

看完题目，我的第一想法是：

先按照题意建图，并且用并查集将在同一连通块中的点合并起来。

面对每一个乘客出行的起点和终点 $(a,b)$，先用并查集判断是否在同一个连通块中。

若不在，则跳过；否则，对点 $a$ 跑 Dijkstra。

时间复杂度 $O(P\times M\times  siz\times\log n)$。

拿到了 $50$ 分的好成绩。

### 50pts Code: 

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std; 
const int N=1e5+10;
const int M=1e6+10;
int n,m,p;
int fa[N],dist[N];
bool f[N];

// 链式前向星
struct ss{
	int nxt,to,id; //nxt上一条边，to到达的点，id这条边的编号
}edge[M];
int first[M],cnt=0;
// 加边函数
void add(int a,int b,int id){
	edge[++cnt].to=b;
	edge[cnt].id=id;
	edge[cnt].nxt=first[a];
	first[a]=cnt;
}

// 并查集
int find(int x){
	if(fa[x]==x) return x;
	fa[x]=find(fa[x]);
	return fa[x];
}

void dijkstra(int s){
	for(int i=1;i<=n;i++) dist[i]=2e18,f[i]=0;
	priority_queue<pair<int,pair<int,int> >,vector<pair<int,pair<int,int> > >,greater<pair<int,pair<int,int> > > > Q;  //堆优化，三个值分别表示(到当前点的距离，点，上一条经过的边的编号)
	Q.push(make_pair(0,make_pair(s,0)));
	dist[s]=0;
	while(!Q.empty()){
		int t=(Q.top().second).first,bef=(Q.top().second).second;Q.pop();
		if(f[t]) continue;
		f[t]=1;
		for(int i=first[t];i;i=edge[i].nxt){
			int y=edge[i].to,id=edge[i].id;
			if(dist[y]>dist[t]+(id!=bef)){ // 边的编号不同才+1
				dist[y]=dist[t]+(id!=bef); 
				Q.push(make_pair(dist[y],make_pair(y,id)));
			}
		}
	}
}

int sum=0;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>p;
	for(int i=1;i<=n;i++) fa[i]=i;  //并查集的预处理
	for(int i=1;i<=m;i++){
		int x,have,bef;cin>>x>>have;
		bef=have;
		for(int j=2;j<=x;j++){
			cin>>have;
			add(bef,have,i),add(have,bef,i); //加边
			int u=find(bef),v=find(have);  //并查集合并
			fa[u]=v; 
		}
	}
	while(p--){
		int a,b;
		cin>>a>>b;
		if(find(a)!=find(b)) continue; //判断是否在同一连通块中
		else{
			dijkstra(a);
			sum+=dist[b];
		}
	}
	cout<<sum;
	return 0;
}
```

面对上面这个又臭又长的 TLE 代码，在对他进行 $144$ 小时的不断优化下，在听取 @[ruojiyz](https://www.luogu.com.cn/user/557781) 的建议后，于是考虑选择变换思路。

我们将**边**作为**点**，再进行建图。

具体地，若两点再同一条线上，则其贡献为 $0$，只有换线，才会增加 $1$ 贡献。

若可以换线，那一定至少有一个点同时在这两条线上。

![样例](https://cdn.luogu.com.cn/upload/image_hosting/t97d5qmr.png)

例如样例图中，$1\to 3$ 的贡献为 $0$，$2\to 6$ 的贡献为 $1$。

可以发现：$3$ 同时在线 $1$ 和线 $2$ 上，我们就可以对线 $1$ 和线 $2$ 建一条边。

考虑用 `std::vector` 储存，设 $A_i$ 表示与点 $i$ 相连的边的 `vector`。

以下是上述过程的代码：

```cpp
// 对每个点相邻的边的储存
for(int i=1;i<=m;i++){
	int num,x;
	cin>>num;
	for(int j=1;j<=num;j++){
		cin>>x;
		A[x].push_back(i);
	}
}
//建图(这里用的是邻接矩阵)
	for(int i=1;i<=n;i++){ // 枚举点
		int x=A[i].size();// x: 与 i 相连的边数
		if(x<=1) continue; // 不可能有存在两条线
		for(int j=0;j<x;j++) // 枚举
			for(int k=j+1;k<x;k++)
				dist[A[i][j]][A[i][k]]=dist[A[i][k]][A[i][j]]=1; //建边
	}
```

建图之后，就很简单了。

本题限时 $2.5s$，所以 floyd 跑 $O(n^3)$ 可以过。

以下是 floyd 代码：

```cpp
for(int i=1;i<=m;i++) dist[i][i]=0;
for(int k=1;k<=m;k++)
	for(int i=1;i<=m;i++)
		for(int j=1;j<=m;j++)
			dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
```

面对每一个乘客的起点和终点 $(a,b)$，可以分别枚举与起点和终点的相连边，取其最小值。

```cpp
for(int k=1;k<=p;k++){
	int a,b,x,y,ans=0x3f3f3f3f;
	cin>>a>>b;
	x=A[a].size(),y=A[b].size();
	for(int i=0;i<x;i++)
		for(int j=0;j<y;j++)
			ans=min(dist[A[a][i]][A[b][j]]+1,ans); //dist[][]+1 加1因为进站也会产生一个贡献
	if(ans!=0x3f3f3f3f) sum+=ans;  //若 ans=0x3f3f3f3f 则说明两点不连通		
}
```

可能上面说的不大清楚，以下是完整代码:

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e5+10,M=1e3+10;
int n,m,p;
int dist[M][M],sum=0;
vector<int> A[N];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	memset(dist,0x3f,sizeof dist);
	cin>>n>>m>>p;
	for(int i=1;i<=m;i++){
		int num,x;
		cin>>num;
		for(int j=1;j<=num;j++){
			cin>>x;
			A[x].push_back(i);
		}
	}
	for(int i=1;i<=n;i++){
		int x=A[i].size();
		if(x<=1) continue;
		for(int j=0;j<x;j++)
			for(int k=j+1;k<x;k++)
				dist[A[i][j]][A[i][k]]=dist[A[i][k]][A[i][j]]=1;
	}
	for(int i=1;i<=m;i++) dist[i][i]=0;
	for(int k=1;k<=m;k++)
		for(int i=1;i<=m;i++)
			for(int j=1;j<=m;j++)
				dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
	for(int k=1;k<=p;k++){
		int a,b,x,y,ans=0x3f3f3f3f;
		cin>>a>>b;
		x=A[a].size(),y=A[b].size();
		for(int i=0;i<x;i++)
			for(int j=0;j<y;j++)
				ans=min(dist[A[a][i]][A[b][j]]+1,ans);
		if(ans!=0x3f3f3f3f) sum+=ans;		
	}
	cout<<sum;
	return 0;
}
```

---

