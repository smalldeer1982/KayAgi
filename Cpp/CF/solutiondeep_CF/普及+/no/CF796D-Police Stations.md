# 题目信息

# Police Stations

## 题目描述

Inzane finally found Zane with a lot of money to spare, so they together decided to establish a country of their own.

Ruling a country is not an easy job. Thieves and terrorists are always ready to ruin the country's peace. To fight back, Zane and Inzane have enacted a very effective law: from each city it must be possible to reach a police station by traveling at most $ d $ kilometers along the roads.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF796D/3d1a9e2d88191523d4bc40bc87e14f9eb6074cc0.png)There are $ n $ cities in the country, numbered from $ 1 $ to $ n $ , connected only by exactly $ n-1 $ roads. All roads are $ 1 $ kilometer long. It is initially possible to travel from a city to any other city using these roads. The country also has $ k $ police stations located in some cities. In particular, the city's structure satisfies the requirement enforced by the previously mentioned law. Also note that there can be multiple police stations in one city.

However, Zane feels like having as many as $ n-1 $ roads is unnecessary. The country is having financial issues, so it wants to minimize the road maintenance cost by shutting down as many roads as possible.

Help Zane find the maximum number of roads that can be shut down without breaking the law. Also, help him determine such roads.

## 说明/提示

In the first sample, if you shut down road $ 5 $ , all cities can still reach a police station within $ k=4 $ kilometers.

In the second sample, although this is the only largest valid set of roads that can be shut down, you can print either 4 5 or 5 4 in the second line.

## 样例 #1

### 输入

```
6 2 4
1 6
1 2
2 3
3 4
4 5
5 6
```

### 输出

```
1
5
```

## 样例 #2

### 输入

```
6 3 2
1 5 6
1 2
1 3
1 4
1 5
5 6
```

### 输出

```
2
4 5 ```

# AI分析结果

### 题目内容
# 警察局

## 题目描述
因扎内终于找到了有大量闲钱的赞恩，于是他们一起决定建立自己的国家。

治理国家并非易事。小偷和恐怖分子总是企图破坏国家的和平。为了反击，赞恩和因扎内制定了一项非常有效的法律：从每个城市出发，沿着道路行进最多 $d$ 公里，必须能够到达一个警察局。

该国共有 $n$ 个城市，编号从 $1$ 到 $n$，仅通过恰好 $n - 1$ 条道路相连。所有道路长度均为 $1$ 公里。最初，通过这些道路可以从一个城市前往任何其他城市。该国在某些城市还设有 $k$ 个警察局。特别地，城市结构满足上述法律要求。同时请注意，一个城市中可能设有多个警察局。

然而，赞恩觉得拥有多达 $n - 1$ 条道路并无必要。国家正面临财政问题，因此希望通过关闭尽可能多的道路来最小化道路维护成本。

帮助赞恩找出在不违反法律的前提下最多可以关闭的道路数量，并确定这些道路。

## 说明/提示
在第一个样例中，如果关闭道路 $5$，所有城市仍可在 $k = 4$ 公里内到达警察局。

在第二个样例中，尽管这是唯一最大的有效可关闭道路集合，但你可以在第二行打印 4 5 或 5 4。

## 样例 #1
### 输入
```
6 2 4
1 6
1 2
2 3
3 4
4 5
5 6
```
### 输出
```
1
5
```

## 样例 #2
### 输入
```
6 3 2
1 5 6
1 2
1 3
1 4
1 5
5 6
```
### 输出
```
2
4 5 ```

### 算法分类
贪心

### 题解综合分析与结论
所有题解思路核心均为利用贪心策略，基于广搜（BFS）对树进行处理。由于题目已保证初始状态下所有点到最近警察局距离不超过 $d$ ，所以在求解过程中可忽略 $d$ 。各题解要点在于将所有警察局（去重后）放入队列进行广搜，对每个点染色，染色依据为从哪个警察局搜索到达该点，这样染色后，两个染色不同节点间的边可被删除，因为删除后两端节点仍能通过各自对应警察局满足到警察局距离要求。各题解难点主要是如何清晰实现BFS染色及统计可删除边，不同题解在代码实现细节上略有差异，如数据结构定义、输入输出优化等。

### 所选的题解
 - **作者：lenlen (5星)**
    - **关键亮点**：思路阐述清晰，代码简洁明了，数据结构定义合理，直接利用广搜对节点染色并统计答案，无冗余操作。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+7232;
int n,m,d,dis[N],ans;
int x,y;
struct len{
    int u,v;
}t[N];
struct hl{
    int v,nxt;
}e[N<<1];
int cnt,h[N];
void add(int u,int v)
{
    e[++cnt].v=v,e[cnt].nxt=h[u],h[u]=cnt;
}
struct llt{
    int x,op;
}tmp;
queue<llt> q;
int main()
{
    scanf("%d%d%d",&n,&m,&d);
    for(int i=1;i<=m;++i) 
    {
        scanf("%d",&x);
        if(!dis[x]) dis[x]=x,q.push((llt){x,x});
    }
    for(int i=1;i<n;++i)
    {
        scanf("%d%d",&t[i].u,&t[i].v);
        add(t[i].u,t[i].v),add(t[i].v,t[i].u);
    }
    while(!q.empty())
    {
        tmp=q.front(),q.pop();
        for(int i=h[tmp.x],v;i;i=e[i].nxt)
        {
            if(dis[(v=e[i].v)]) continue;
            dis[v]=tmp.op;
            q.push((llt){v,tmp.op});
        }
    }
    for(int i=1;i<n;++i)
    if(dis[t[i].u]!=dis[t[i].v]) ++ans;
    printf("%d\n",ans);
    for(int i=1;i<n;++i)
    if(dis[t[i].u]!=dis[t[i].v]) printf("%d ",i);
}
```
    - **核心实现思想**：定义结构体存储边信息，利用邻接表存储图。先将警察局去重后加入队列，BFS过程中对未染色节点染色，最后遍历所有边，统计两端染色不同的边的数量并输出。
 - **作者：lukelin (4星)**
    - **关键亮点**：代码结构清晰，通过自定义函数实现输入优化，整体逻辑简单易懂。
    - **重点代码**：
```cpp
#include <cstdio>
#include <algorithm>
#include <queue>
#define max(a,b) ((a>b)?a:b)

using namespace std;

inline int read(){
    int x = 0; int zf = 1; char ch = ' ';
    while (ch!= '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}

struct Edge{
    int to, next;
} edges[600005];
int head[300005], edge_num = 0;

void addEdge(int from, int to){
    edges[++edge_num] = (Edge){to, head[from]};
    head[from] = edge_num;
}

struct Node{
    int id;
    int clr;
};

queue<Node> que;
int vis[300005];

int ans[300005], ans_num = 0;

void BFS(){
    Node u;
    while (!que.empty()){
        u = que.front(), que.pop();
        for (int c_e = head[u.id]; c_e; c_e = edges[c_e].next){
            int v = edges[c_e].to;
            if (!vis[v]){
                vis[v] = u.clr;
                que.push((Node){v, u.clr});
            }
        }
    }
}

int u[300005], v[300005];

int main(){
    int n = read(), k = read(), d = read();
    int clr = 0, kk = 0;
    for (int i = 1; i <= k; ++i){
        int pol = read();
        if (!vis[pol]){
            ++kk;
            que.push((Node){pol, ++clr});
            vis[pol] = clr;
        }
    }
    for (int i = 1; i < n; ++i){
        u[i] = read(), v[i] = read();
        addEdge(u[i], v[i]), addEdge(v[i], u[i]);
    }
    BFS();
    for (int i = 1; i < n; ++i)
        if (vis[u[i]]!= vis[v[i]])
            ans[++ans_num] = i;
    printf("%d\n", ans_num);
    for (int i = 1; i <= ans_num; ++i){
        if(i!= 1)
            printf(" ");
        printf("%d", ans[i]);
    }
    return 0;
}
```
    - **核心实现思想**：自定义 `read` 函数优化输入，通过邻接表存储图。BFS对节点染色，最后遍历边，将两端染色不同的边加入答案数组并输出。
 - **作者：mot1ve (4星)**
    - **关键亮点**：思路描述详细，代码简洁，利用 `pair` 存储节点和颜色信息，逻辑紧凑。
    - **重点代码**：
```cpp
//bfs染色 
#include<bits/stdc++.h>
using namespace std;
int n,k,d,idx,col;
int vis[1000010],head[1000010],u[1000010],v[1000010];
struct node{
	int nxt,to;
}edge[1000010];
vector<int> g;
void add(int u,int v)
{
	edge[++idx].nxt=head[u];
	edge[idx].to=v;
	head[u]=idx;
}
queue< pair<int,int> > q;
void bfs()
{
	while(q.size())
	{
		int x=q.front().first;
		int y=q.front().second;
		q.pop();
		for(int i=head[x];i;i=edge[i].nxt)
		{
			int v=edge[i].to;
			if(!vis[v])
			{
				vis[v]=y;
				q.push(make_pair(v,y));
			}
		}
	}
}
int main()
{
	cin>>n>>k>>d;
	for(int i=1;i<=k;i++)
	{
		int x;
		scanf("%d",&x);
		if(vis[x])
		continue;
		vis[x]=++col;
		q.push(make_pair(x,col));
	}
	for(int i=1;i<=n-1;i++)
	{
		scanf("%d%d",&u[i],&v[i]);
		add(u[i],v[i]);
		add(v[i],u[i]);
	}
	bfs();
	for(int i=1;i<=n-1;i++)
	{
		if(vis[u[i]]!=vis[v[i]])
		g.push_back(i);
	}
	cout<<g.size()<<endl;
	for(auto i : g)
	{
		printf("%d ",i);
	}
	return 0;
}
```
    - **核心实现思想**：利用邻接表存图，BFS时用 `pair` 存储节点和其染色信息，对未染色节点染色，最后遍历边，将两端染色不同的边加入向量并输出。

### 最优关键思路或技巧
利用BFS的性质，通过对从不同警察局出发搜索到的节点进行染色，从而快速判断哪些边可以删除。这种染色方法简单直接，有效利用了树结构和BFS的特点，避免了复杂的距离计算，直接从连通性和所属警察局角度解决问题。

### 可拓展之处
此类题目属于树上结构结合特定条件的优化问题，类似套路可应用于其他树上操作，如在满足一定节点连通性或距离限制条件下对树边进行增减操作。可拓展到更复杂的图结构，但需注意图的连通性维护及算法复杂度变化。

### 相似知识点洛谷题目
 - **P1352 没有上司的舞会**：同样基于树结构，通过树形DP解决问题，与本题类似在于都对树的节点进行操作，不过本题是贪心策略，该题是动态规划。
 - **P2015 二叉苹果树**：在二叉树上进行边的删除操作以满足特定条件，与本题类似在于都是对树边进行处理以达到某种最优，只是条件和处理方式不同。
 - **P1273 有线电视网**：在树上进行费用与收益相关计算，和本题一样都围绕树结构展开逻辑，不同在于本题是距离相关贪心，该题是费用收益相关计算。 

---
处理用时：112.40秒