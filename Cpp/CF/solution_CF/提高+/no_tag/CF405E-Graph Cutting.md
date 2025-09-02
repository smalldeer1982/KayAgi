# Graph Cutting

## 题目描述

Little Chris is participating in a graph cutting contest. He's a pro. The time has come to test his skills to the fullest.

Chris is given a simple undirected connected graph with $ n $ vertices (numbered from 1 to $ n $ ) and $ m $ edges. The problem is to cut it into edge-distinct paths of length 2. Formally, Chris has to partition all edges of the graph into pairs in such a way that the edges in a single pair are adjacent and each edge must be contained in exactly one pair.

For example, the figure shows a way Chris can cut a graph. The first sample test contains the description of this graph.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF405E/aa33f90804f9db5d4060a2ddb4da922a7c1a5340.png)You are given a chance to compete with Chris. Find a way to cut the given graph or determine that it is impossible!

## 样例 #1

### 输入

```
8 12
1 2
2 3
3 4
4 1
1 3
2 4
3 5
3 6
5 6
6 7
6 8
7 8
```

### 输出

```
1 2 4
1 3 2
1 4 3
5 3 6
5 6 8
6 7 8```

## 样例 #2

### 输入

```
3 3
1 2
2 3
3 1
```

### 输出

```
No solution
```

## 样例 #3

### 输入

```
3 2
1 2
2 3
```

### 输出

```
1 2 3
```

# 题解

## 作者：CYZZ (赞：3)

# [Graph Cutting](https://www.luogu.com.cn/problem/CF405E)
图论练手题，建议评蓝？
## 思路
可以先考虑数据是一棵树的情况，可以递归处理每一颗子树。设当前递归到了点 $u$，$v_i$ 是 $u$ 在 dfs 树上的儿子，已经递归处理完了 $v_i$。此时有两种情况：

- $v_i$ 的儿子中有还未被处理的点 $c$，则 $(c,v_i,u)$ 是一组边，直接输出。
- $v_i$ 的子树已经被处理完了，此时可以把 $v_i$ 丢进 $vec_u$ 中。处理完所有 $v$ 后，把 $vec_u$ 中的点两两配对，输出。如果最后 $vec_u$ 中还剩下了一个点，可以变为第一种情况，在回溯时和父亲连边。

再考虑数据是图的情况，相比起树，dfs 树中会出现一些返祖边。对于返祖边 $(v,k)$，也可以把 $v$ 丢进 $vec_k$ 中，这样在回溯到 $k$ 时也会把 $v$ 考虑进去的。

不难发现，无解当且仅当 $m$ 是奇数。
## 代码
[codeforces 提交](https://codeforces.com/contest/405/submission/219565658)

---

## 作者：YFF1 (赞：2)

## 题目大意：
给定一个无向连通图，请把图切割为若干条长度为二的链，使得每一条边都被包含在一条链中。
输出其中一种剖分方式。若无解，按题目要求输出。
## 思路：
采用递归求解，每次递归一个点的子结点，放入队列中进行处理。处理每个点时，按照以下规则操作。为了通俗易懂，定义三个，命名为父亲，自己和儿子：

- 自己无法处理的，交给父亲处理。
- 儿子处理了它的兄弟节点，但是自己仍然要处理儿子的兄弟节点。即在遍历时，用一个数组统计边是否被遍历而不是点。

举个例子：  
假设自己有三个子节点，分别是儿子和两个兄弟，那么先将子节点里面可以两两配对的先配上，必定会剩下一个节点无法配对或者没有剩下节点。如果剩下的是儿子，将儿子返回给自己的父亲进行处理。那么最后就会将父亲和自己和儿子三个配成一对。
## 代码：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef pair<int,int> pii;
int n,m,x,y;
vector<pii>g[200005];
bool vis[200005];
int dfs(int x){
	queue<int>q;
	for(pii i:g[x]){
		if(vis[i.second])continue;
		vis[i.second]=1;// 标记边是否被访问 
		int r=dfs(i.first);
		if(r)printf("%lld %lld %lld\n",x,i.first,r);//由父亲处理自己无法配对的儿子 
		else q.push(i.first);
	}
	while(q.size()>=2){//先把能配对的两两配对 
		printf("%lld ",q.front());
		q.pop();
		printf("%lld ",x);
		printf("%lld\n",q.front());
		q.pop();
	}
	if(!q.empty())return q.front();//将落单的那个与自己的父亲配对 
	return 0;
}
signed main () {
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%lld%lld",&x,&y);
		g[x].push_back({y,i});
		g[y].push_back({x,i});
	}
	if(m%2!=0)cout<<"No solution";//直接输出无解 
	else dfs(1);
	return 0;
}
```

---

## 作者：DE_aemmprty (赞：2)

### $1$ 题目链接
[$\color{blue}\texttt{protal}$](https://www.luogu.com.cn/problem/CF405E)

### $2$ 题目大意

给你一个 $n$ 个点 $m$ 条边的简单无向图，问你能否将这个图分割成 $\frac{m}{2}$ 个长度恰好为 $2$ 的路径，使得每条边都恰好出现一次。如果能，请输出其中一种构造，否则输出 "No solution"。

### $3$ 解法分析

我们先考虑一棵树的情况。

如果题目给的是一棵树的话，若我们现在已经来到了结点 $\text{root}$，那么我们先把他的儿子顶点先递归一遍，然后再来判断他的儿子节点。假设现在我们正在判 $u_i$ 是否能构造完毕：

* 如果对于 $v_i$ 这个儿子节点构造完后，$v_i$ 还有一个 $c$ 点没有用到，那么我们就将 $(\text{root}, v_i, c)$ 构造成一组。

* 否则，把这个儿子节点扔进数组 $d$ 里，稍后进行处理。

那么，对于所有能构造成功的点来说：

* 将所有这样能完整构造的子节点按以下方式构造： $(d_1, \text{root}, d_2),(d_3, \text{root}, d_4),\cdots$

这里可以发现，只要 $m$ 是偶数，就一定能构造出来；反之，就一定无法构造成功。

那对于图来说，我们可以通过 dfs，把这个图转化成一颗树。

这样，这道题就完成了。

### $4$ AC代码

```cpp
// 凑合着看吧，码风被邪教感染了（
// Fron yh2021shx
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define lf double
#define RI register int
#define GO(i,a,b) for(int i = a; i <= b; i ++)
#define RO(i,b,a) for(int i = b; i >= a; i --)
#define FO(i,u,head,e) for(RI i = head[u]; i; i = e[i].next)
#define mem(a,x) memset(a, x, sizeof a)
#define F first
#define S second
#define pii pair<int,int>
#define MP(a,b) make_pair(a,b)
#define PB(a) push_back(a)
#define CI const int

CI maxn = 1e5 + 7;
CI maxm = 2e5 + 7;

struct Edge{
	int u, v, next;
}e[maxm];

int head[maxn], cnt;

void add(int u, int v){
	cnt ++;
	e[cnt].u = u;
	e[cnt].v = v;
	e[cnt].next = head[u];
	head[u] = cnt;
}

int get(int x){
	if (x & 1) return x + 1;
	return x - 1;
}

int n, m;

int visE[maxm], vis[maxn];

// 寻找构造方案
int check(int cur){
	int x = 0;
	vis[cur] = 1;
	FO (i, cur, head, e){
		int v = e[i].v;
		if (visE[i]) continue;
		visE[i] = visE[get(i)] = 1;
		int res;
		if (vis[v]) res = 0;
		else res = check(v);
		if (res > 0)
			printf("%d %d %d\n", cur, v, res);
		else{
			if (!x) x = v;
			else{
				printf("%d %d %d\n", x, cur, v);
				x = 0;
			}
		}
	}
	return x;
} 

int main(){
	cin >> n >> m;
	if (m & 1){
		printf("No solution\n");
		return 0;
	}
	GO (i, 1, m){
		int u, v;
		scanf("%d %d", &u, &v);
		add(u, v); add(v, u);
	} 
	
	// 寻找构造方案
	check(1);
	return 0;
}
```

---

## 作者：IkunTeddy (赞：0)

# 题目分析

在图上直接做显然不好做，所以考虑在一棵生成树上求解。

最后我们会发现在 DFS 树上最好求，如过连向儿子的边内部能两两配对就内部完成，否则就跟一条返祖边配对。这样子树内就没有剩余，一定能配对成功。

在最开始判一下奇数无解即可。

时间复杂度 $O(n)$。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
//
const int maxn=1e5+10;
int n,m;
unordered_map<int,int>cut[maxn];
int deg[maxn],p[maxn];
vector<int> g[maxn];
int cnt;
struct Ans{
	int x,y,z;
}ans[maxn];
int dep[maxn];
void dfs(int u,int fa){
	int p1=0,p2=0;
	dep[u]=dep[fa]+1;
	for(int v:g[u]){
		if(!dep[v]){
			dfs(v,u);
		}
		if(dep[v]<dep[u])continue ;
		if(!cut[u][v]){
			if(!p1)p1=v;
			else{
				p2=v;
				ans[++cnt]={p1,u,p2};
				p1=p2=0;
			}
		}
	}
	if(p1){
		for(int v:g[u]){
			if(dep[v]<dep[u]){
				p2=v;
				cut[u][v]=cut[v][u]=1;
				ans[++cnt]={p1,u,p2};
				break ;
			}
		}
	}
}
int main(){
	cin>>n>>m;
	for(int i=1,x,y;i<=m;i++){
		cin>>x>>y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	if(m&1){
		cout<<"No solution\n";
		return 0;
	}
	dfs(1,0);
	for(int i=1;i<=cnt;i++)cout<<ans[i].x<<' '<<ans[i].y<<' '<<ans[i].z<<'\n';
	
	return 0;
}
```

---

