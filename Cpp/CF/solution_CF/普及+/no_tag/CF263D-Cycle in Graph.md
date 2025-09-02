# Cycle in Graph

## 题目描述

You've got a undirected graph $ G $ , consisting of $ n $ nodes. We will consider the nodes of the graph indexed by integers from 1 to $ n $ . We know that each node of graph $ G $ is connected by edges with at least $ k $ other nodes of this graph. Your task is to find in the given graph a simple cycle of length of at least $ k+1 $ .

A simple cycle of length $ d $ $ (d&gt;1) $ in graph $ G $ is a sequence of distinct graph nodes $ v_{1},v_{2},...,v_{d} $ such, that nodes $ v_{1} $ and $ v_{d} $ are connected by an edge of the graph, also for any integer $ i $ $ (1<=i&lt;d) $ nodes $ v_{i} $ and $ v_{i+1} $ are connected by an edge of the graph.

## 样例 #1

### 输入

```
3 3 2
1 2
2 3
3 1
```

### 输出

```
3
1 2 3 ```

## 样例 #2

### 输入

```
4 6 3
4 3
1 2
1 3
1 4
2 3
2 4
```

### 输出

```
4
3 4 1 2 ```

# 题解

## 作者：OIerZhao_1025 (赞：4)

## [题目传送门](https://www.luogu.com.cn/problem/CF263D)

## 题意
给定一个 $n$ 个节点的无向图 $G$，节点编号为 $1$ 到 $n$。已知图中每个节点至少与其他 $k$ 个节点相连。你的任务是在给定的图中找到一个长度至少为 $k+1$ 的简单环。
一个长度为 $d$（$d>1$）的简单环是图 $G$ 中的一系列不同的节点 $v_1,v_2,\dots,v_d$，满足节点 $v_1$ 与 $v_d$ 通过一条边连接。

## 思路
这道题是基环树，基环树是指一个树加了一条边以后构成的图。所以我们用 DFS 遍历一遍，总一个点开始递推，用一个数组标记一下有没有被访问过，如果被访问过说明他构成了一个环，这是再往回退，就可以找到环了。

## code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+10;
vector<int>e[N];
ll n,m,k,len,vis[N],pos;
void dfs(int u)//dfs枚举 
{
	vis[u]=++len;
	for(intv:e[u])
	{
		if(!vis[v])
		{
			dfs(v);
			break;
		}
		if(vis[u]-vis[v]>=k)
		{
			cout<<vis[u]-vis[v]+1<<'\n';
			cout<<u<<" ";
			pos=v;
			return;
		}
	}
	if(pos!=-1)cout<<u<<" ";
	if(pos==u)pos=-1;
}
int main()
{
	ios::sync_with_stdio(0);//减时间 
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++)
	{
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1);
	return 0;
}
```

---

## 作者：爱睡觉的Raki (赞：3)

在$DFS$过程中给每个点打上时间戳，若时间戳之差$>=k$，则说明找到了题目所要求的环，输出答案即可
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int maxn=2e5+5,inf=0x3f3f3f3f;
vector<int>e[maxn];
int n,m,k;
int vis[maxn],pos;
void dfs(int u,int tim){
	vis[u]=tim;
	for(auto v:e[u]){
		if(!vis[v]){
			dfs(v,tim+1);
			break;
		}
		if(vis[u]>=vis[v]+k){
			cout<<vis[u]-vis[v]+1<<endl;
			cout<<u<<" ";
			pos=v;
			return;
		}
	}
	if(pos!=-1)cout<<u<<" ";
	if(pos==u)pos=-1;
}
signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1,1);
}
```


---

## 作者：Milmon (赞：1)

[in Blog](//milk-lemon.blog.luogu.org/solution-CF263D) & [Problem](//www.luogu.com.cn/problem/CF263D)

## 题目大意

- 给定一个 $n$ 个点，$m$ 条边的无向图，每个点都至少连 $k$ 条边。求图中的任意一个长度至少为 $k+1$ 的简单环。

- $3\leq n,\ m\leq 10^5$，$2\leq k<n$

## 解题思路

容易想到计算每个点的时间戳 $dfn$。我们只需要找到一条边两个端点时间戳之差不小于 $k$，则这两点之间必有一条长度至少为 $k$ 的简单路径，再加上一条直接连接两点的边，形成的整个环至少有 $k+1$ 条边。

事实上任意一个符合每个点都至少连 $k$ 条边这个条件的图，必然存在这样的简单环，证明也不困难。

#### 【证明】

显然存在一条简单路径 $a_1\to a_2\to\cdots\to a_t$ 满足 $a_t$ 所有边的另一个顶点都在 $\{a_1,\ a_2,\ \cdots, a_t\}$ 中。设 $a_i$ 与 $a_t$ 有连边的最小的 $i$ 为 $p$，则由于 $a_t$ 这个点至少连 $k$ 条边，故 $t-p+1\geq k$。那么只需取 $a_p\to a_{p+1}\to\cdots\to a_t$ 就找到了一个简单环。

## AC 代码

```c++
#include<bits/stdc++.h>
using namespace std;

int n,m,k;

struct Edge{
    int to,nxt;
}edge[200001];
int head[100001],cntEdge;
inline void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
}

int dfn[100001],viscnt,vislist[100001];
bool vis[100001];

void dfs(int id){
    vis[id]=true,dfn[id]=++viscnt,
    vislist[viscnt]=id; // 记录 dfn 为 viscnt 的点为 id
    for(int i=head[id];i;i=edge[i].nxt)
        if(!vis[edge[i].to]){
            dfs(edge[i].to); break;
        }
        else if(dfn[edge[i].to]+k<=dfn[id]){
            // 找到环
            printf("%d\n",dfn[id]-dfn[edge[i].to]+1);
            for(int j=dfn[edge[i].to];j<=dfn[id];j++)
                printf("%d ",vislist[j]);
            printf("\n"); exit(0);
        }
}

int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    dfs(1);
    return 0;
}
```

---

## 作者：cwd2023 (赞：0)

## CF263D题解
#### by cwd2023


---

#### update 2024.10.27:
感谢管理员指正题解中的格式错误，已修改。

---


#### 题意简述：
有一个无向图，每个顶点至少连接其他的 $k$ 个顶点，求一个长度大于等于 $k+1$ 的简单环。

---
#### 解题思路：
不难发现，只要满足 **【每个顶点至少连接其他的 $k$  个顶点】** 这个条件，就会有符合要求的环，所以我们可以从任意节点开始 dfs，并给每个点打上**时间标记**。        
如果 dfs 到 $u$ 过程中遇到了一个走过的节点 $v$，并且两点之间路程大于等于 $k$，那么算上从 $u$ 到 $v$ 的路径，就有一个长度大于等于 $k+1$ 的环了。


---


至于怎么判断距离，用 $u$ 的时间标记减去 $v$ 的就好了。

---


##### 代码（详细注释）

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//开long long
ll n,m,k,cur;
//n,m,k的变量名对应题目，cur是找到的环的首个节点
ll dfn[100010];//时间标记
vector<ll>e[100010];//邻接矩阵存图
inline void dfs(ll u,ll d){//inline是加速的
	dfn[u]=d;//打标记
	for(auto v:e[u]){
		if(!dfn[v]){
			dfs(v,d+1);
			break;//避免重复的找环，有一个就退出
		}
		if(dfn[u]-dfn[v]>=k){
//注意此时dfn[v]是之前更改过的，比较小，所以用dfn[u]减dfn[v]
			cout<<dfn[u]-dfn[v]+1<<"\n";//输出环的长度
			cout<<u<<" ";
			cur=v;//标记环中的首节点
			return;
		}
	}
	if(cur!=-1)cout<<u<<" ";
	if(cur==u)cur=-1;
//如果这是环的起点，递归的上一级就不输出
}
int main(){
	ios::sync_with_stdio(0);
	cout.tie(0);
	cin.tie(0);//没用的优化
	cin>>n>>m>>k;
	for(ll i=1;i<=m;i++){
		ll u,v;
		cin>>u>>v;
		e[u].push_back(v);//无向图，两边都存
		e[v].push_back(u);
	}
	dfs(1,1);
	return 0;
}
```
##### 无注释版（自认为码风好看）

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,k,cur;
ll dfn[100010];
vector<ll>e[100010];
inline void dfs(ll u,ll d){
	dfn[u]=d;
	for(auto v:e[u]){
		if(!dfn[v]){
			dfs(v,d+1);
			break;
		}
		if(dfn[u]-dfn[v]>=k){
			cout<<dfn[u]-dfn[v]+1<<"\n";
			cout<<u<<" ";
			cur=v;
			return;
		}
	}
	if(cur!=-1)cout<<u<<" ";
	if(cur==u)cur=-1;
}
int main(){
	ios::sync_with_stdio(0);
	cout.tie(0);
	cin.tie(0);
	cin>>n>>m>>k;
	for(ll i=1;i<=m;i++){
		ll u,v;
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1,1);
	return 0;
}
```
最后，希望本文对大家有所帮助，感谢观看！
### 望管理员通过。

---

## 作者：minVan (赞：0)

**解题思路**

不难想到使用 Tarjan 算法来解决，算出时间戳之后，对于每条边 $(u,v)$，如果 $u,v$ 的时间戳之差大于等于 $k$，代表必有一条边数大于等于 $k$ 的简单路径连接着 $u,v$，从而这必然是一个边数大于等于 $k+1$ 的环。

Tarjan 部分代码：

```cpp
inline void dfs(int u) {
  vis[u] = ++tim;
  for (int v : e[u]) {
    if (!vis[v]) {
      dfs(v);
      break;
    } 
    if (vis[u] - vis[v] >= k) {
      cout << vis[u] - vis[v] + 1 << '\n';
      cout << u << " ";
      pos = v;
      return ;
    }
  }
  if (pos != -1) {
    cout << u << " ";
  }
  if (pos == u) {
    pos = -1;
  }
}
```

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
vector<int> e[N];
int n, m, k, tim;
int vis[N], pos;
inline void dfs(int u) {
  vis[u] = ++tim;
  for (int v : e[u]) {
    if (!vis[v]) {
      dfs(v);
      break;
    } 
    if (vis[u] - vis[v] >= k) {
      cout << vis[u] - vis[v] + 1 << '\n';
      cout << u << " ";
      pos = v;
      return ;
    }
  }
  if (pos != -1) {
    cout << u << " ";
  }
  if (pos == u) {
    pos = -1;
  }
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> m >> k;
  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    e[u].push_back(v);
    e[v].push_back(u);
  }
  dfs(1);
  return 0;
}
```

---

