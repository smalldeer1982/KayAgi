# [ABC142F] Pure

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc142/tasks/abc142_f

$ N $ 頂点 $ M $ 辺の有向グラフ $ G $ が与えられます。  
 このグラフの頂点には $ 1 $ から $ N $ までの番号が付けられており、$ i $ 番目の辺は頂点 $ A_i $ から頂点 $ B_i $ に向けて張られています。  
 このグラフは自己辺や多重辺を持たないことが保証されています。

すべての頂点の入次数が $ 1 $、出次数が $ 1 $ であるような $ G $ の誘導部分グラフ (注記を参照) が存在するか判定し、 存在するならその一例を示してください。  
 ただし、空グラフは含めないものとします。

## 说明/提示

### 注記

有向グラフ $ G\ =\ (V,\ E) $ に対し、次のような条件を満たす有向グラフ $ G'\ =\ (V',\ E') $ を $ G $ の誘導部分グラフと呼びます。

- $ V' $ は $ V $ の (空でない) 部分集合である。
- $ E' $ は、$ E $ の辺であって両端点がともに $ V' $ に含まれるものすべてを含む集合である。

### 制約

- $ 1\ \leq\ N\ \leq\ 1000 $
- $ 0\ \leq\ M\ \leq\ 2000 $
- $ 1\ \leq\ A_i,B_i\ \leq\ N $
- $ A_i\ \neq\ B_i $
- 組 $ (A_i,\ B_i) $ はすべて異なる。
- 入力はすべて整数である。

### Sample Explanation 1

頂点集合が $ \{1,\ 2,\ 4\} $ であるような $ G $ の誘導部分グラフの辺集合は $ \{(1,\ 2),\ (2,\ 4),\ (4,\ 1)\} $ であり、すべての頂点の入次数が $ 1 $、出次数が $ 1 $ となります。

### Sample Explanation 2

条件を満たす $ G $ の誘導部分グラフは存在しません。

## 样例 #1

### 输入

```
4 5
1 2
2 3
2 4
4 1
4 3```

### 输出

```
3
1
2
4```

## 样例 #2

### 输入

```
4 5
1 2
2 3
2 4
1 4
4 3```

### 输出

```
-1```

## 样例 #3

### 输入

```
6 9
1 2
2 3
3 4
4 5
5 6
5 1
5 2
6 1
6 2```

### 输出

```
4
2
3
4
5```

# 题解

## 作者：Lskkkno1 (赞：3)

- [AT5256 [ABC142F] Pure](https://www.luogu.com.cn/problem/AT5256)

### 题目描述

给定一个 $n$ 个点，$m$ 条边的有向图 $(n \le 1000, m \le 2000)$。

找到一个子图，使得子图里每个点的入度和出度都等于 1。

输出方案。

### 正解

题目要求即找到一个环，环内的点都只向外连一条边。

手玩发现可以先找到任意一个环，假如环内有连边，就把环缩小，一直缩到环内每个点出度都为 1。

模拟缩环的过程，发现只要找到一个环内的**最小环**即可。

那么就用 $bfs$ 搜出一颗有向树，**第一条返祖边**所连的两个点所在的那个最小环即为答案。

找方案的话可以记一下路径上的 preNode (前驱)。

现场用 $dfs$ 也过了，不过后面被 dqk hack 掉了。

$\color{DeepSkyBlue} Code :$

```cpp
/*
	bfs 找环
*/
#include <bits/stdc++.h>
#define N 1005
#define M 2005

using namespace std;

int n, m;
int dep[N];
int head[N], nex[M], to[M], e;
int stk[N], top;
bool instack[N], vis[N], G[N][N];
vector<int> res;

inline int Rd() {
	int x = 0; char ch = getchar();
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	return x;
}
inline void Ae(int u, int v) {
	nex[++e] = head[u], head[u] = e;
	to[e] = v;
}

void calc(int u, int v) {
	do {
		res.push_back(stk[top]);
	} while(stk[top--] != v);
	int ans = res.size();
	printf("%d\n", ans);
	for(int i = 0; i < ans; ++i) printf("%d\n", res[i]);
	exit(0);
}
void dfs(int u) {
	stk[++top] = u;
	instack[u] = vis[u] = true;
	for(int i = head[u]; i; i = nex[i]) {
		int v = to[i];
		if(vis[v]) {
			if(instack[v]) calc(u, v);
		} else {
			dfs(v);
		}
	}
	instack[u] = false, --top;
	return;
}

int main() {
	n = Rd(), m = Rd();
	for(int i = 1; i <= m; ++i) {
		int u = Rd(), v = Rd();
		G[u][v] = true;
		Ae(u, v);
	}
	
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			if(G[i][j] && G[j][i]) {
				puts("2");
				printf("%d\n%d\n", i, j);
				return 0;
			}	
		}
	}
	for(int i = 1; i <= n; ++i)
		if(!vis[i])
			dfs(i);
	puts("-1");
	return 0;	
}
```

---

## 作者：small_john (赞：2)

## 思路

其实挺简单的。

题目可以转换为求一个最小的环，那就直接 DFS。

用一个栈存前驱，如果找到换了就直接输出。

但是要注意特判，两个点之间的环在开始的时候，记得扫一遍，不然会 WA 两个点。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e3+5,M = 2e3+5;
int n,m,stk[N],top,cnt,head[N],nxt[M],to[M];
bool vis[N],vi[N],g[N][N];
vector<int> ans;
void add(int x,int y)
{
	nxt[++cnt] = head[x];
	head[x] = cnt;
	to[cnt] = y;
	g[x][y] = 1;
}
void print(int v)
{
	do ans.push_back(stk[top]);while(stk[top--]!=v);
	cout<<ans.size()<<'\n';
	for(auto i:ans)
		cout<<i<<'\n';
	exit(0);
}
void dfs(int u)
{
	stk[++top] = u;//进栈
	vis[u] = vi[u] = 1;
	for(int i = head[u];i;i = nxt[i])
	{
		int v = to[i];
		if(vis[v]&&vi[v])
			print(v);
		dfs(v);
	}
	vi[u] = 0;--top;//出栈
}
signed main()
{
	cin>>n>>m;
	for(int i = 1,x,y;i<=m;i++)
		cin>>x>>y,add(x,y);
	for(int i = 1;i<=n;i++)//特判
		for(int j = 1;j<=n;j++)
			if(g[i][j]&&g[j][i])
				return cout<<"2\n"<<i<<'\n'<<j,0;
	for(int i = 1;i<=n;i++)
		if(!vis[i])
			dfs(i);
	cout<<-1;
	return 0;
}
```

---

## 作者：ATION001 (赞：0)

看见各位大佬都用的是 DFS，本蒟蒻太菜了，就写了个 BFS + 最短路树的解法（Hack 过了哎）。
## 题目描述
给定 $n$ 个节点和 $m$ 条**有向边**，请输出这张图的**最小环**。如果没有环，输出 $-1$。
## 思路
首先我们可以跑 $n$ 遍 BFS 求任意两点之间的最短路（别想什么 Floyd，BFS 不香么）。

然后利用最短路径求出最小环的起点和终点（找不到最小环直接输出 $-1$）。

随后建立一个最短路树（需要输出路径）。

最后递归输出即可（不需要加别的大佬加的特判）。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct node{
	int id=-1,w=1e18,VR;
}ans;
int n,m,dis[1005][1005],fa[1005];
vector<int>v[1005],A;
bool vis[1005][1005];
void bfs(int Begin){
	queue<int>q;
	q.push(Begin);
	vis[Begin][Begin]=true;
	dis[Begin][Begin]=0;
	while(q.size()){
		int p=q.front();
		q.pop();
		for(int z:v[p]){
			if(!vis[Begin][z]){
				dis[Begin][z]=dis[Begin][p]+1;
				vis[Begin][z]=true;
				q.push(z);
			}
		}
	}
	return;
}
void print(int x){
    if(!x){
    	return;
	}
	print(fa[x]);
	A.push_back(x);
}
void LTREE(){
	for(int i=1;i<=n;i++){
		for(auto z:v[i]){
			if(dis[ans.id][z]==dis[ans.id][i]+1){
				fa[z]=i;
			}
		}
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	fill(dis[0],dis[n+1],1e18);
	for(int i=1,x,y;i<=m;i++){
		cin>>x>>y;
		v[x].push_back(y);
	}
	for(int i=1;i<=n;i++){
		bfs(i);
		for(int j=1;j<=n;j++){
			for(auto z:v[j]){
				if(z==i&&vis[i][j]){
					if(ans.w>dis[i][j]+1){
						ans.w=dis[i][j]+1;
						ans.id=i;
						ans.VR=j;
					}
				}
			}
		}
	}
	if(ans.id==-1){
		cout<<-1;
		return 0;
	}
	LTREE();
	print(ans.VR);
	cout<<A.size()<<'\n';
	for(int z:A){
		cout<<z<<'\n';
	}
	return 0;
}
```

---

## 作者：under_the_time (赞：0)

## 题意

> 给定一张 $n$ 个点 $m$ 条边的有向图 $G=(V,E)$，求一个**导出子图** $G'=(V',E')$（即先选定一个点集 $V'$，然后对于 $i,j\in V'$，若 $i\to j\in E$ 那么有 $i\to j\in E'$），使得对于 $u\in V'$，$u$ 在 $G'$ 中的入度和出度都恰好为一。输出一个方案或报告无解。
>
> $1\le n\le 1000$，$0\le m\le 2000$，保证图中无重边和自环。

## 解法

对于一个满足每个点入度出度均为 $1$ 的图，显然它就是一个**环**。不妨考虑这么构造：对于点 $u$，先满足它的出度为 $1$，那么 $u$ 有且仅有一条出边连向某一个点。这条边必须连向另外一个点 $v$，若 $v$ 还没有入边和出边，连边后继续考虑点 $v$；若 $v$ 已经有了入边，那么连接后无法满足入度为 $1$，不可取；若 $v$ 没有入边但有一条出边，即 $v$ 是第一个考虑的点，那么连接 $v$ 后就完成了构图。这样构造出的图就是一个环。

然后朴素的想法就是：在 $G$ 中选一个环出来输出就是答案。下面是一个反例：

![](https://cdn.luogu.com.cn/upload/image_hosting/bxzshtth.png)

对于这张图，$1\to 2\to 3\to 4\to 1$ 即为一个环。但如果我们选取 $V'=\{1,2,3,4\}$，那么导出子图就会包含 $3\to 1$ 这条边，不满足子图中每个点入度、出度均为 $1$；而正确答案即为**环长更小**的 $1\to 2\to 3\to 1$。$V'=\{1,2,3,4\}$ 不合法的原因就是出现了**环套环**。我们假设已经找到了原图中的所有环，那么对于**环长最小**的环显然不会出现环套环的情况，因为对于一个被套了的环**环长一定更短**。那么我们考虑找到**环长最短的环**即可。

## 实现

这里是一个找环的套路：考虑 dfs。我们维护一个栈，访问节点时将其入栈，回溯时将其出栈。对于点 $u$ 我们分别记录它**是否被访问过**和**是否在栈中**（前者当 $u$ 出栈时仍然保留）。对于点 $u$ 和边 $u\to v$，如果 $v$ 已经在栈中，意味着我们已经找到了一个长成 $v\to \cdots \to u\to v$ 的环，中间省略的点即为从 $v$ 走到 $u$ 路径上压入栈里的节点。然后在所有环中找到环长最小的即可。初始时我们枚举 $1\sim n$​ 中还没被访问过的点作为起点。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
const int maxm = 2005, maxn = 1005;
namespace Graph {
    struct Edge { int to, nxt; } e[maxm];
    int head[maxn], ecnt = 0;
    void addEdge(int u, int v) {
        e[++ ecnt] = Edge { v, head[u] };
        head[u] = ecnt;
    }
} using namespace Graph;
int siz; vector<int> ans;
int st[maxn], top; bool vis[maxn], used[maxn]; 
void dfs(int u) {
    if (used[u]) {
        if (!vis[u]) return ;
        int now_siz = 1, i; 
        for (i = top; st[i] != u; i --, now_siz ++);
        if (siz <= now_siz) return ;
        siz = now_siz, ans.clear();
        for (; i <= top; i ++) ans.push_back(st[i]);
        return ;
    } vis[st[++ top] = u] = used[u] = 1;
    for (int i = head[u]; i; i = e[i].nxt) dfs(e[i].to);
    vis[st[top --]] = 0;
}
int main() {
    scanf("%d %d", &n, &m), siz = n + 1;
    for (int i = 1, u, v; i <= m; i ++)
        scanf("%d %d", &u, &v), addEdge(u, v);
    for (int i = 1; i <= n; i ++)
        if (!used[i]) dfs(i);
    if (siz == n + 1) return puts("-1"), 0;
    printf("%d\n", siz);
    for (auto x : ans) printf("%d\n", x);
    return 0;
}
```

---

## 作者：lmy_2011 (赞：0)

我们先找到题目中的这句话“入度和出度都恰好是 $1$”，想要满足这样的条件，那么肯定有 $1$ 条边**指向他**，肯定又有一条边**被他指向**。
![](https://img1.baidu.com/it/u=2538111628,3419095790&fm=253&fmt=auto&app=138&f=PNG?w=500&h=500)

这样的话，你就会发现其实这题就是找环。

我用的是栈来找环，步骤如下：
1. 从图中任意 $1$ 个节点开始进行深度优先遍历，将该节点入栈。
2. 对于当前节点的每个兄弟节点，如果该兄弟节点已经在栈中，说明找到了 $1$ 个环，输出该环即可。
3. 如果该兄弟节点不在栈中，则将该兄弟节点入栈，并以该兄弟节点为起点继续进行深度优先遍历。
4. 如果当前节点的所有兄弟节点都已经被访问过，将该节点出栈，输出即可。


注意：**两个点之间在开始的时候本来就存在环**，记得遍历一边。

核心代码如下：
```cpp
void union(int x,int y)
{
	pos++;
	next[pos]=head[x];
	to[pos]=y;
	head[x]=pos;
	g[x][y]=true;
	return;
}
void dfs(int cur)
{
	stk.push(cur);
	vis1[cur]=true;
	vis2[cur]=true;
	for(int i=head[cur];i;i=next[i])
	{
		int nxt=to[i];
		if(vis1[nxt]==true&&vis2[nxt]==true)
		{
			print(nxt);
		}
		dfs(nxt);
	}
	vis2[cur]=false;
	stk.pop();
	return;
}

```


---

