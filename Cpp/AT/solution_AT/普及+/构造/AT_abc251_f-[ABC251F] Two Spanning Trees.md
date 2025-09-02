# [ABC251F] Two Spanning Trees

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc251/tasks/abc251_f

$ N $ 頂点 $ M $ 辺の無向グラフ $ G $ が与えられます。 $ G $ は**単純**（自己ループおよび多重辺を持たない）かつ**連結**です。

$ i\ =\ 1,\ 2,\ \ldots,\ M $ について、$ i $ 番目の辺は頂点 $ u_i $ と頂点 $ v_i $ を結ぶ無向辺 $ \lbrace\ u_i,\ v_i\ \rbrace $ です。

下記の $ 2 $ つの条件をともに満たすような $ G $ の $ 2 $ つの全域木 $ T_1,T_2 $ を $ 1 $ 組構成してください。（ $ T_1 $ と $ T_2 $ は異なる全域木である必要はありません。）

- $ T_1 $ は下記を満たす。
  
  > $ T_1 $ を頂点 $ 1 $ を根とする根付き木とみなしたとき、$ G $ の辺のうち $ T_1 $ に含まれないすべての辺 $ \lbrace\ u,\ v\ \rbrace $ について、$ u $ と $ v $ は $ T_1 $ において祖先と子孫の関係にある。
- $ T_2 $ は下記を満たす。
  
  > $ T_2 $ を頂点 $ 1 $ を根とする根付き木とみなしたとき、$ G $ の辺のうち $ T_2 $ に含まれない辺 $ \lbrace\ u,\ v\ \rbrace $ であって、$ u $ と $ v $ が $ T_2 $ において祖先と子孫の関係にあるようなものは存在しない。

ここで、「根付き木 $ T $ において頂点 $ u $ と頂点 $ v $ が祖先と子孫の関係にある」とは、「 $ T $ において $ u $ が $ v $ の祖先である」と「 $ T $ において $ v $ が $ u $ の祖先である」のうちどちらかが成り立つことをいいます。

本問題の制約下において上記の条件を満たす $ T_1 $ と $ T_2 $ は必ず存在することが示せます。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ N-1\ \leq\ M\ \leq\ \min\lbrace\ 2\ \times\ 10^5,\ N(N-1)/2\ \rbrace $
- $ 1\ \leq\ u_i,\ v_i\ \leq\ N $
- 入力はすべて整数
- 与えられるグラフは単純かつ連結

### Sample Explanation 1

上記の出力例において、$ T_1 $ は $ 5 $ 本の辺 $ \lbrace\ 1,\ 4\ \rbrace,\ \lbrace\ 4,\ 3\ \rbrace,\ \lbrace\ 5,\ 3\ \rbrace,\ \lbrace\ 4,\ 2\ \rbrace,\ \lbrace\ 6,\ 2\ \rbrace $ を持つ $ G $ の全域木です。この $ T_1 $ は問題文中の条件を満たします。実際、$ G $ の辺のうち $ T_1 $ に含まれない各辺に関して、 - 辺 $ \lbrace\ 5,\ 1\ \rbrace $ について、頂点 $ 1 $ は頂点 $ 5 $ の祖先であり、 - 辺 $ \lbrace\ 1,\ 2\ \rbrace $ について、頂点 $ 1 $ は頂点 $ 2 $ の祖先であり、 - 辺 $ \lbrace\ 1,\ 6\ \rbrace $ について、頂点 $ 1 $ は頂点 $ 6 $ の祖先です。 また、$ T_2 $ は $ 5 $ 本の辺 $ \lbrace\ 1,\ 5\ \rbrace,\ \lbrace\ 5,\ 3\ \rbrace,\ \lbrace\ 1,\ 4\ \rbrace,\ \lbrace\ 2,\ 1\ \rbrace,\ \lbrace\ 1,\ 6\ \rbrace $ を持つ $ G $ の全域木です。この $ T_2 $ は問題文中の条件を満たします。実際、$ G $ の辺のうち $ T_2 $ に含まれない各辺に関して、 - 辺 $ \lbrace\ 4,\ 3\ \rbrace $ について、頂点 $ 4 $ と頂点 $ 3 $ は祖先と子孫の関係になく、 - 辺 $ \lbrace\ 2,\ 6\ \rbrace $ について、頂点 $ 2 $ と頂点 $ 6 $ は祖先と子孫の関係になく、 - 辺 $ \lbrace\ 4,\ 2\ \rbrace $ について、頂点 $ 4 $ と頂点 $ 2 $ は祖先と子孫の関係にありません。

### Sample Explanation 2

$ 3 $ 本の辺 $ \lbrace\ 1,\ 2\rbrace,\ \lbrace\ 1,\ 3\ \rbrace,\ \lbrace\ 1,\ 4\ \rbrace $ を持つ木 $ T $ が $ G $ の唯一の全域木です。 $ G $ の辺のうちこの木 $ T $ に含まれない辺は存在しないので、明らかに、$ T $ は $ T_1 $ の条件と $ T_2 $ の条件をともに満たします。

## 样例 #1

### 输入

```
6 8
5 1
4 3
1 4
3 5
1 2
2 6
1 6
4 2```

### 输出

```
1 4
4 3
5 3
4 2
6 2
1 5
5 3
1 4
2 1
1 6```

## 样例 #2

### 输入

```
4 3
3 1
1 2
1 4```

### 输出

```
1 2
1 3
1 4
1 4
1 3
1 2```

# 题解

## 作者：Nahida_Buer (赞：4)

# 题目大意
在原图中构造两棵以 $1$ 为根的符合要求（第一问为任意非树边连接的两节点都存在祖先关系；第二问为任意非树边连接的两节点不存在祖先关系）的生成树，并分别输出它们的边，任输出一种正确答案即可。注：非树边的意思是在原图中排除掉指定的生成树中的边所有后剩余的边。
# 解题过程
遇到没思路的题不要慌，先研究样例，画出图。
## 第二问
可以先考虑第二问的生成树：观察画出的图之后，我们发现：要想让非树边连接的节点都不存在祖先关系，浅显一点想，就要让任两个非树边连接的节点尽量处于不同的两棵子树，也可以说，就是让任两个非树边连接的节点的最近公共先祖是这两点之外的其他点。那么也就是让生成树中每个节点尽量有多一些子节点。对广搜比较熟悉的同学立刻可以想到用广搜遍历一张图所搜到的边组成的集合组成的一棵树刚好满足这个条件。
#### 证明
根据广搜的性质，深度小的节点优先被搜到，如果任意两点之间有边连接，则要么该边是树边；如果是非树边，则其中一个节点一定被深度小于等于另一个节点的其他节点所搜到。所以非树边连接的节点都不存在祖先关系。
## 第一问
既然第二问是广搜，那么第一问自然能够猜测到是深搜，通过类似的思路我们可以证明它：
#### 证明
根据深搜的性质，如果任意两节点之间有非树边连接，则该边一定是返祖边，所以非树边连接的节点都存在祖先关系。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int read(){//快读
	int x=0;char ch=getchar();
	while (ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48;ch=getchar();}
	return x;
}
int n,m;
bitset<400005>pd;//2*i和2*i-1分别代表i节点在广搜和深搜中是否遍历过了
vector<int>h[200005];
void dfs(int u){
	for(int v:h[u]){
		if(pd[(v<<1)-1])continue;
		pd[(v<<1)-1]=1;
		printf("%d %d\n",u,v);
		dfs(v);
	}
}
void bfs(){
	queue<int>q;
	q.push(1);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int v:h[u]){
			if(pd[v<<1])continue;
			pd[v<<1]=1;
			printf("%d %d\n",u,v);
			q.push(v);
		}
	}
}
int main(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		h[u].push_back(v);
		h[v].push_back(u);
	}
	pd[1]=pd[2]=1;
	dfs(1);
	bfs();
}
```

---

## 作者：Pengzt (赞：4)

[ABC251F](https://www.luogu.com.cn/problem/AT_abc251_f)

题意：给一个图，求出两棵这个图的生成树，分别满足没有横叉边和返祖边，并输出这两棵树的形态。

首先是没有横叉边，如果学过 Tarjan 的话，肯定可以直接 DFS 一遍就可以了。因为只要遇到横叉边，在之前的点的搜索中优先走这条边，一定可以变为所有边都是树边或返祖边。

同理，因为要求不出现返祖边，即满足 $|dep_u-dep_v|=1$。如果有点满足 $(x,y),(y,z),(z,x)$ 的话，可以先遍历掉返祖边，即 $(x,y),(x,z),(y,z)$，这样就不会有返祖边了。BFS 一边就可以了。

所以直接输出 DFS 生成树和 BFS 生成树即可。

[评测记录](https://atcoder.jp/contests/abc251/submissions/46653891)

---

## 作者：MMXIandCCXXII (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc251_f)


2025.2.6 应读者要求，补充一下证明。

## 题目大意
给定一个无向图 $G$，其中有 $n$ 个点，$m$ 条边，构造两棵生成树 $T_1$ 和 $T_2$ 满足：
+ $T_1$ 使得图中不在树上的边连接的两点都是祖宗关系
+ $T_2$ 使得图中不在树上的边连接的两点都不是祖宗关系

## 思路
最开始没思路，于是把样例的图画下来，不难发现 $T_1$ 就是深搜的路径，而 $T_2$ 就是广搜的路径。

考虑反证，先看 $T_1$，如果一条非树边连接的两个点树上不是祖宗关系，则从 dfn 序小的一点出发，必然需要回溯才能到达另一点，但是实际上可以直接从这条边到达，所以矛盾。

$T_2$ 同理，若一条非树边连接的两个点是祖宗关系，那么广搜时肯定会直接从离根近的一点走到另一点，那么这也是矛盾的。

所以我们可以直接通过广搜和深搜解决这个问题。

## code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

vector <int> v[N];
bool vis[N];

void dfs(int u)
{
	vis[u] = true;
	for (int i = 0; i < v[u].size(); i++)
	{
		int j = v[u][i];
		if (vis[j]) continue;
		cout << u << " " << j << endl;
		dfs (j);
	}
}

queue <int> q;

void bfs()
{
	q.push (1);
	vis[1] = true;
	while (q.size())
	{
		int x = q.front();
		q.pop();
		for (int i = 0; i < v[x].size(); i++)
		{
			int j = v[x][i];
			if (vis[j]) continue;
			vis[j] = true;
			cout << x << " " << j << endl;
			q.push (j);
		}
	}
}

int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		int x, y;
		cin >> x >> y;
		v[x].push_back (y);
		v[y].push_back (x);
	}
	dfs (1);
	memset (vis, false, sizeof vis);
	bfs ();
	return 0;
}
```

---

## 作者：LionBlaze (赞：1)

前言：感谢 Graph Editor，给本题解提供了图片。

这道题非常的魔法（至少对我来说）。

# 前置知识

如果把一个无向图转化为一棵树，那么会有三种边：

- 树边：正常的书上的边。
- 后向边：从子节点指向祖先的边。
- 横叉边：从一棵子树连到另一棵子树。

那么，$T_1$ 的要求就是没有横叉边，$T_2$ 就是没有后向边。

# 做题

## 没有横叉边

这样一个图是有横叉边的，这条边就是 $A$：

![](https://s21.ax1x.com/2025/01/12/pEP6YKU.png)

容易发现，如果把点 $3$ 拉下去，那么就没有横叉边 $A$ 了，只有一条后向边 $B$：

![](https://s21.ax1x.com/2025/01/12/pEP6trF.png)

是不是所有图都可以这样呢？答案是肯定的。

### 所有 DFS 树都没有横叉边

证明：

首先考虑横叉边是如何产生的。

显然，就是搜索到一个节点 $u$，有一条边 $u\leftrightarrow v$，$v$ 已经搜索过并且不是 $u$ 的祖先。

那么，我们考虑 $u$ 是谁扩展出来的？

既然 $v$ 不是 $u$ 的祖先，那么肯定不是 $v$ 搜索到某一个节点，再搜索到另一个节点，再这样下去，一直到 $u$ 的。

我们定义 $G_\text{old}$（Gold?） 为原图，$G_\text{new}$ 为在 $G_\text{old}$ 中去除所有在搜索 $v$ 之前搜索到的节点的图（当然也去除和这些节点连的边）。

那么，搜索 $v$ 的一个必然的后果是，搜索到了 $G_\text{old}$ 中所有 $v$ 可以到达的节点。

需要说明的是，$G_\text{old}$ 不一定连通，比如最简单的图 $G=\{V=\{1,2,3\},E=\{(1,2),(1,3)\}\}$，那么如果从 $1$ 开始搜索且 $v=2$，则新图为 $G=\{V=\{2,3\},E=\empty\}$，显然不连通。

但是既然 $u$ 在 $v$ 之后搜到（所以 $u \in G_\text{new}$），并且 $u$ 和 $v$ 有直接连边，那么显然搜索 $v$ 的副作用之一就是搜索到了 $u$。

这样，$u$ 就是 $v$ 的子孙节点，所以 $u \leftrightarrow v$ 是后向边而非横叉边，故横叉边不存在。

证毕 Q.E.D。

## 没有后向边

DFS 序是没有横叉边的，所以是不是 BFS 序就是没有后向边的呢？

神奇的脑回路，但是人类智慧，但是正确的。前提是没有重边，但是题目中已经保证了图是简单图。

### BFS 树没有后向边

设有一条边 $u \leftrightarrow v$，其中 $u$ 是刚刚搜索到的一个节点，$v$ 是以前搜索到的一个节点，并且满足 $v$ 是 $u$ 的祖先。

设 $v$ 是 $u$ 的 $k$ 级祖先，其中 $k$ 必须严格大于 $1$，否则就有两条 $u \leftrightarrow v$ 的边了。并且设 $u$ 的 $k-1$ 级祖先是 $w$。

但是，这是广度优先搜索啊，每个节点都会直接扩展到自己的所有未扩展的相邻节点。

其中，$u$ 和 $v$ 相邻，$w$ 也和 $v$ 相邻，则它们分别负责了 $v$ 的两棵子树。两棵子树之间的边必然是横叉边，不存在后向边，证毕。

## Summary

第一问 DFS 即可。第二问 BFS 即可。

---

## 作者：_shine_ (赞：0)

一眼遍历题。

要使每一条非树边为子先关系，显然要让这个形成一条类似于链（多条）的东西，这样再看非树边显然也是祖先关系了。

思考些许显然想到爆搜，即深搜，这样每次就都能让其变成一条或多条类似于链的东西了。

要使得整棵树添加非树边为非祖先关系，显然层层搜索，所以使用广搜，这样就能使得添加的为非祖先关系。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define pii pair<int,int>
#define int long long
const int maxn=4e5+10;
int n,m;
int e[maxn],h[maxn],ne[maxn],idx;
bool vis[maxn];
void add(int a,int b){
	e[idx]=b;
	ne[idx]=h[a];
	h[a]=idx++;
}
void dfs(int u){
//	if(vis[u]==true)return ;
//	vis[u]=true;
	for(int i=h[u];i!=-1;i=ne[i]){
		int j=e[i];
		if(vis[j]==true)continue;
		vis[j]=true;
		cout << u << " " << j << endl;
		dfs(j);
	}
}
void bfs(){
	queue<int>q;
	q.push(1);
	while(q.size()!=0){
		int num=q.front();
		q.pop();
		for(int i=h[num];i!=-1;i=ne[i]){
			int j=e[i];
			if(vis[j]==true)continue;
			vis[j]=true;
			cout << num << " " << j << endl;
			q.push(j);
		}
	}
}
signed main(){
	memset(h,-1,sizeof(h));
	cin >> n >> m;
	for(int i=1;i<=m;++i){
		int a,b;
		cin >> a >> b;
		add(a,b);
		add(b,a);
	}
	vis[1]=true;
	dfs(1);
//	puts("md");
	memset(vis,false,sizeof(vis));
	vis[1]=true;
	bfs();
	return 0;
}
```

---

## 作者：Union_Find (赞：0)

首先第一问，学过 Tarjan 的都知道，直接 dfs 一边的生成树就是一颗没有横叉边的树，所以第一问就解决了

```cpp
void dfs(ll u){
	for (int i = 0; i < e[u].size(); i++){
		ll v = e[u][i];
		if (vis[v]) continue;
		cout << u << " " << v << "\n";
		vis[v] = 1;
		dfs(v);
	}
}

vis[1] = 1, dfs(1);
```

然后是第二问，没有返祖边。发现了一件有趣的事，就是如果有一条返祖边，我们可以构造出一种方法使它没有返祖边。

如下图，让 竖着的那些边作为树边，$1$ 到 $5$ 是一条返祖边，但是如果让 $1$ 到 $5$ 是树边，那么 $4$ 到 $5$ 就是横叉边了。我们发现，这其实就是优先连到 $1$ 近的边。这就是在 bfs 时经过的边。

![](https://cdn.luogu.com.cn/upload/image_hosting/9x45tr8r.png)

所以就有了第二问的代码。

```cpp
il void bfs(ll s){
	q.push(s);vis[s] = 1;
	while (q.size()){
		ll u = q.front();q.pop();
		for (int i = 0; i < e[u].size(); i++){
			ll v = e[u][i];
			if (vis[v]) continue;
			cout << u << " " << v << "\n";
			vis[v] = 1;
			q.push(v);
		}
	}
}

memset (vis, 0, sizeof vis);//vis 重复使用了，要清空。
	bfs(1);
```

然后我们就可以 A 掉这题了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 200005
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
ll n = rd(), m = rd(), u, v, vis[N];
vector <ll> e[N];
queue <ll> q;
void dfs(ll u){
	for (int i = 0; i < e[u].size(); i++){
		ll v = e[u][i];
		if (vis[v]) continue;
		cout << u << " " << v << "\n";
		vis[v] = 1;
		dfs(v);
	}
}
il void bfs(ll s){
	q.push(s);vis[s] = 1;
	while (q.size()){
		ll u = q.front();q.pop();
		for (int i = 0; i < e[u].size(); i++){
			ll v = e[u][i];
			if (vis[v]) continue;
			cout << u << " " << v << "\n";
			vis[v] = 1;
			q.push(v);
		}
	}
}
int main(){
	for (int i = 1; i <= m; i++){
		u = rd(), v = rd();
		e[u].push_back(v);
		e[v].push_back(u);
	}
	vis[1] = 1, dfs(1);
	memset (vis, 0, sizeof vis);
	bfs(1);
	return 0;
}

```

---

## 作者：ZBH_123 (赞：0)

### 思路：DFS 和 BFS
对一个图进行 BFS，得到的一棵生成树必定是题目中的 $T_2$，而用 DFS 得到的生成树必定是题目中的 $T_1$。为什么？我们先来分析 BFS 生成树。BFS 的基本思想就是一层一层地遍历，这就导致了 BFS 生成树后所有的非树边连接的两个节点均不存在祖孙关系。而 BFS 生成出来的树正是题目中的 $T_2$。

接着再来分析 DFS 生成树。DFS 的思想就是不到叶节点不回头，这会导致什么呢？因为 DFS 是一直往下搜的，当搜到的这条边连接着已经搜过的点时，这条边连接着的两个节点必定存在祖孙关系。所以 DFS 生成出来的树一定是题目中的 $T_1$。

最后，题目要求我们输出选中的边，可以选择把树边存下来，也可以选择直接输出。我这里用的是把树边存下来。

AC code:
```cpp
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
const int maxn=2e5;
int n,m,x,y,head[maxn+5],tot=1;
bool vis[maxn+5];
vector<pair<int,int> >t1,t2;
struct Edge{
	int next,to;
}edge[2*maxn+5];
void add(int a,int b){
	edge[++tot].to=b;
	edge[tot].next=head[a];
	head[a]=tot;
}
void dfs(int x,int e){
	vis[x]=true;
	for(int i=head[x];i;i=edge[i].next){
		if(i!=(e^1)||e==0){
			if(!vis[edge[i].to]){
				t1.push_back(make_pair(x,edge[i].to));
				dfs(edge[i].to,i);
			}
		}
	}
}
void bfs(){
	queue<int>q;
	q.push(1);
	vis[1]=true;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=edge[i].next){
			int v=edge[i].to;	
			if(!vis[v]){
				t2.push_back(make_pair(u,v));
				q.push(v);
				vis[v]=true;
			}
		}
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>x>>y;
		add(x,y);
		add(y,x);
	}
	dfs(1,0);
	memset(vis,0,sizeof vis);
	bfs();
	for(int i=0;i<t1.size();i++){
		cout<<t1[i].first<<' '<<t1[i].second<<endl;
	}
	for(int i=0;i<t2.size();i++){
		cout<<t2[i].first<<' '<<t2[i].second<<endl;
	}
	return 0;
}
```

---

## 作者：Ak_hjc_using (赞：0)

### 题目大意
给定一张有 $n$ 个点，$m$ 条边的无向图 $G$，要求我们构造两颗生成树，其中满足：

$T1$ 使得图中不在树上的边连接的两点都是祖宗关系。

$T2$ 使得图中不在树上的边连接的两点都不是祖宗关系。

### 题目思路
这道题的思路并不是很明显，所以我们可以靠样例来分析这道题目的意思。

画出这道题的样例：

![](https://cdn.luogu.com.cn/upload/image_hosting/1sw4nzsl.png)

然后我们发现，这两个东西不就是求这张图的深度和广度优先搜索的遍历过程吗？

所以只需要求出深度优先搜索和广度优先搜索的过程就可以了。

不放代码。

---

## 作者：xiaoPanda (赞：0)

## ABC251F Two Spanning Trees(*1703) 
### Title
给出一个图 $G$，请你构造两个生成树 $T_1,T_2$，使得：

+ $T_1$ 使得任何不在树上的边 $(i,j)$ ，节点 $i$ 和 $j$ 一定存在一个节点是另一个的祖先。

+ $T_2$ 使得任何不在树上的边 $(i,j)$ ，节点 $i$ 和 $j$ 不存在一个节点是另一个的祖先。

（$1$ 号节点为根节点）

### Solution
先~~打表~~给出结论 : $T_1$ 将图 DFS，$T_2$ 将图 BFS。

证明如下：

$T_1$ ：

+ 对于不在同一层的节点之间就像一条链，所以一定满足要求。

+ 对于在同一层的节点之间如果有边 $(i,j)$，那么 DFS 时一定会先扫到点 $j$ （因为这个点是 $i$ 的祖先），但事实上并没有，所以同一层的节点之间没有边，满足要求。

$T_2$ ：

+ 对于在同一层的节点之间就像菊花图，所以不可能有一个节点是另一个的祖先。
+ 对于不在同一层的节点之间如果有边 $(i,j)$，那么如果 $i$ 是 $j$ 的祖先，那么 $i$ 一定是 $j$ 与 $i$ 同层的 $k$ 的祖先过孩子，但事实上并没有，所以不同一层的节点之间没有边。

---

## 作者：sieve (赞：0)

# 题解：[[ABC251F] Two Spanning Trees](https://www.luogu.com.cn/problem/AT_abc251_f)

## 思路

题目要求我们在一个 $n$ 个点，$m$ 条边的图中构建两个生成树。一个要求剩下的边连接的两点是祖宗关系，另一个要求不是。

不难发现，这个其实就是这张图的 DFS 和 BFS 遍历过程。

代码就不贴了。

---

