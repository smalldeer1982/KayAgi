# 题目信息

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

# AI分析结果

### 算法分类
图论

### 综合分析与结论
题目要求计算地铁乘客的客流量，核心在于计算乘客从起点到终点的最少换乘次数。由于地铁线路和车站之间的关系可以抽象为图论问题，因此最相关的算法分类是图论。题解中主要使用了广度优先搜索（BFS）和Floyd算法来解决这个问题。

### 所选题解

#### 题解1：zhuweiqi
- **星级**：5星
- **关键亮点**：通过将车站的线路关系转化为图的邻接矩阵，使用BFS预处理线路之间的最少换乘次数，最后通过枚举起点和终点的线路来计算客流量。思路清晰，代码优化程度高。
- **个人心得**：作者在最初的BFS实现中发现时间复杂度较高，通过将车站的扩展改为线路的扩展，成功优化了算法。

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

#### 题解2：Somebody_lmm
- **星级**：4星
- **关键亮点**：通过将边作为点进行建图，使用Floyd算法计算线路之间的最少换乘次数，最后通过枚举起点和终点的线路来计算客流量。思路新颖，代码实现简洁。
- **个人心得**：作者在最初的Dijkstra实现中发现时间复杂度较高，通过将边作为点进行建图，成功优化了算法。

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
			for(int j=0;j<=y;j++)
				ans=min(dist[A[a][i]][A[b][j]]+1,ans);
		if(ans!=0x3f3f3f3f) sum+=ans;		
	}
	cout<<sum;
	return 0;
}
```

### 最优关键思路或技巧
1. **图的转化**：将车站的线路关系转化为图的邻接矩阵，使用BFS或Floyd算法计算线路之间的最少换乘次数。
2. **枚举优化**：通过枚举起点和终点的线路，计算客流量，避免了直接对车站进行搜索的高时间复杂度。

### 可拓展之处
1. **多源最短路径**：可以进一步优化为多源最短路径问题，使用更高效的算法如Dijkstra或A*算法。
2. **动态更新**：如果地铁线路动态变化，可以考虑使用动态图算法来实时更新最少换乘次数。

### 推荐题目
1. [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
2. [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)
3. [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)

---
处理用时：36.83秒