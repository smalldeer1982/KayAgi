# [ABC315E] Prerequisites

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc315/tasks/abc315_e

$ 1 $ から $ N $ までの番号がついた $ N $ 冊の本があります。  
 本 $ i $ には $ C_i $ 冊の前提となる本があり、そのうち $ j $ 冊目は本 $ P_{i,j} $ で、本 $ i $ を読む前にこの $ C_i $ 冊をすべて読む必要があります。  
 ただし、適切な順序を選ぶことですべての本を読むことができます。

あなたは本 $ 1 $ を読むために必要な最小の数の本を読もうとしています。  
 本 $ 1 $ 以外に読まなければならない本の番号を読むべき順に出力してください。ただし、この条件下で読むべき本の集合は一意に定まります。  
 条件を満たす読む順番が複数考えられる場合は、そのいずれを出力しても構いません。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ C_i\ <\ N $
- $ \sum_{i=1}^{N}\ C_i\ \leq\ 2\ \times\ 10^5 $
- $ C_1\ \geq\ 1 $
- $ 1\ \leq\ P_{i,j}\ \leq\ N $
- $ 1\ \leq\ j\ <\ k\ \leq\ C_i $ のとき $ P_{i,j}\ \neq\ P_{i,k} $
- すべての本を読むことが可能である
 
### Sample Explanation 1

本 $ 1 $ を読むために本 $ 2,3,4 $、本 $ 2 $ を読むために本 $ 3,5 $、本 $ 4 $ を読むために本 $ 5 $ を読む必要があります。本 $ 3,5,6 $ を読むために他の本を読む必要はありません。 このとき、例えば本 $ 5,3,4,2 $ の順に読むことで本 $ 1 $ を読むことができます。$ 3 $ 冊以下の本を読んだ状態で本 $ 1 $ が読めるようになることはないため、これは答えの一つです。他にも本 $ 3,5,4,2 $ の順などで読むことでも $ 4 $ 冊の本を読んだ状態で本 $ 1 $ を読むことができるようになります。

## 样例 #1

### 输入

```
6
3 2 3 4
2 3 5
0
1 5
0
0```

### 输出

```
5 3 4 2```

## 样例 #2

### 输入

```
6
1 2
1 3
1 4
1 5
1 6
0```

### 输出

```
6 5 4 3 2```

## 样例 #3

### 输入

```
8
1 5
1 6
1 7
1 8
0
0
0
0```

### 输出

```
5```

# 题解

## 作者：codejiahui (赞：11)

这是第一篇只用拓扑排序，不用深搜的题解！

## 题意简述

- 有 $n$ 本书，每本书在读之前都必须读另外的几本书。

- 现在给定每本书阅读前的必读书，想读第一本书，问最少要先读多少书，要求输出**满足最少的前提下的**任意一种读书方案。

- $2 \le N \le 2\times 10^5$

## 题目分析

分析样例，在读第一本书前，先读第二、三、四本，读第二本要读第三、五本，读第四本要读第五本，可知答案符合要求。

根据上面的分析，按照读书的先后顺序，不难想到建图和拓扑排序。然而，本题中有一个关键问题，需要**满足最少的前提下的**读书方案，如果直接拓扑，会导致不需要读的书也被输出。

不过，上面的办法并非毫不可取，我们可以看出上面方法的根本问题在于无法在拓扑时确定当前的点与第一个点是否有关，反过来想，我们只需要保证在某个点后，所有点都和第一个点有关，不就行了？所以，只需**建反图，然后拓扑排序，从一号点开始都存储到数组，最后反过来输出**。

最后，有一个小问题需要解决：要保证在一号点之后都是必需的。其实只需要用从大到小的优先队列，在一号点被出队之前，其他能出队的点都会出队，那么一号点出队后，剩下的都是图中被一号约束的点，也就是必读书。

## 代码

**以下为重点代码：拓扑排序**

不会拓扑的请进入：[【模板】拓扑排序](https://www.luogu.com.cn/problem/B3644)

**注意：这题的拓扑增加了标记变量和优先队列。**

```cpp
int in[200010],n,m;
int flag = 0,a[200010],nn = 0;
vector<int> adj[200010];
priority_queue<int> q; 
void topo()
{
    for (int i = 1;i <= n;i++)
        if (in[i] == 0)
            q.push(i);
    while(!q.empty())
    {
        int u = q.top();
        q.pop();
        if (flag) a[++nn] = u;
        if (u == 1) flag = 1;
        for (int v:adj[u])
        {
            in[v]--;
            if (in[v] == 0)
                q.push(v);
        }
    }
}
```
详细代码如下，请自行做题，**勿抄袭**。

```cpp
//written by codejiahui
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int in[200010],n,m;
int flag = 0,a[200010],nn = 0;
vector<int> adj[200010];
priority_queue<int> q; 
void topo()
{
    for (int i = 1;i <= n;i++)
        if (in[i] == 0)
            q.push(i);
    while(!q.empty())
    {
        int u = q.top();
        q.pop();
        if (flag) a[++nn] = u;
        if (u == 1) flag = 1;
        for (int v:adj[u])
        {
            in[v]--;
            if (in[v] == 0)
                q.push(v);
        }
    }
}
int main()
{
    scanf("%d",&n);
    for (int i = 1;i <= n;i++)
    {
    	int x;
    	scanf("%d",&x);
    	for (int j = 1;j <= x;j++)
    	{
	        int u;
	        scanf("%d",&u);
	        in[u]++;
	        adj[i].push_back(u);
		}
    }
    topo();
    for (int i = nn;i >= 1;i--)
    	printf("%d ",a[i]);
    return 0;
}
```
~~求管理员通过~~

---

## 作者：FreedomKing (赞：3)

超级水的 E 题，但是有个笨蛋赛时想挂了我不说是谁。

### 思路

考虑简化问题，建一棵只有从父节点到子节点的单向边的树，父节点到子节点遍历就代表想要阅读一本书需要阅读哪些前置书籍，直接搜索就行了。由于需要先读前置书籍，倒序输出遍历时经过的元素即可。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int a[N],n,m,t,k;
vector<int>e[N];
bool vis[N];
void dfs(int x){
	vis[x]=true;
	for(int i=0;i<e[x].size();i++)
		if(!vis[e[x][i]])
			dfs(e[x][i]);
	if(x>1) cout<<x<<' ';
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>m;
		for(int j=1;j<=m;j++){
			int x;
			cin>>x;
			e[i].push_back(x);
		}
	}
	dfs(1);
	return 0;
}
```

---

## 作者：Elairin176 (赞：1)

[传送门](https://www.luogu.com.cn/problem/AT_abc315_e)    
淼题。   
## 题意
有 $n$ 本书。要阅读一本书必须将其所有的前置书籍都阅读完毕。现在要阅读第 $1$ 本书，输出一个合法的顺序，使按照这个顺序阅读可以阅读完所有第 $1$ 本书的前置书籍。    
## 解法
这些书的关系明显可以抽象成一个图来理解。    
因为阅读一本书需要阅读这本书全部的前置书籍，所以我们可以进行 dfs。这个 dfs 从 $1$ 开始即可。   
本题利用了 dfs 的性质：深的点先进行遍历。   
时间复杂度 $O(n)$，可以通过。   
[CODE](https://atcoder.jp/contests/abc315/submissions/44733998)

---

## 作者：so_find_skind (赞：1)

2023/8/24：有一点笔误，修改并重新提交审核

直接将这本书与每个点之前要读的书连条边然后 $\text{dfs}$ 求一遍即可。

不过这里就会有一个难点。

那就是边为何是以**这本书**为起点，**读这本书之前必须读的书为终点呢**呢？

因为，若是你想以**这本书**为终点的话，我就问你，你准备怎么求最短路径？

如果还有人不知趣的问无向图的话：

你建立无向图，这就没主次了啊，谁知道谁先谁后啊？！

无向图猝。

建立反边还有一个好处，就是若是一个点能到达另一个点，建反边后，原来的终点依然能到达原来的起点，类似于光路可逆，有向图的路径也是可逆的。

知道了这一点后，$\text{dfs}$ 就可以跑起来了！


code：

```
#include<bits/stdc++.h>
using namespace std;
int n;
bool vis[200005];
vector<int>g[200005];
void dfs(int u){
    vis[u]=true;
    for(int i=0;i<g[u].size();i++){
        if(!vis[g[u][i]])
            dfs(g[u][i]);
    }
    if(u!=1)
        cout<<u<<' ';
}
int main(){
    cin>>n;
    for(int i=1,c;i<=n;i++){
        cin>>c;
        for(int j=1,r;j<=c;j++){
            cin>>r;
            g[i].push_back(r);
        }
    }
    dfs(1);
    return 0;
}
```

---

## 作者：qwertim (赞：1)

~~见过的最水的 E 题。~~
# 题意
有 $n$ 本书，在读第 $i$ 本书前必须先读 $C_i$ 本书，分别为 $P_{i,1},P_{i,2},...,P_{i,C_i}$。现在你想读第一本书，问你在读第一本书之前至少需要读多少本书，按读的顺序输出。
# 思路
从 $1$ 开始 dfs 遍历在它之前要读的书，遍历完**之后**把这本书的编号加入到答案序列里（除了 $1$），最后按顺序输出即可。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,c[200005];
vector<int>v[200005],ans;
bool b[200005];
void dfs(int x){
	b[x]=1;//标记读没读过
	for(int i:v[x])
		if(!b[i])dfs(i);//如读过则不用再读一遍
	if(x!=1)ans.push_back(x);//不是1就加入答案序列
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d",&c[i]);
		int x;
		fo(j,1,c[i])scanf("%d",&x),v[i].push_back(x);
	}
	dfs(1);
	for(int i:ans)printf("%d ",i);//按读的顺序输出
	return 0;
}
```


---

## 作者：c1ampy (赞：1)

不难想到，根据书籍阅读的先后顺序，我们可以建立图论模型。而题目保证「存在一种阅读顺序可以将所有书籍都阅读一遍」，这表示建出来的图是 DAG。故题中的「阅读顺序」即可对应图的拓扑序。

不过，题目还要求最小化阅读的书籍本数。这就使得一般的拓扑排序算法不能直接解决本题，因为算法只能得到所有结点的拓扑序，而不能区分必需书籍和非必需书籍。

重新考虑必需书籍与非必需书籍的性质，可以发现，从必需书籍对应的结点出发，可以到达结点 $ 1 $，而从非必需书籍对应的结点出发则不能到达。

考虑建立反图，在反图中从结点 $ 1 $ 出发可到达的结点即为必需书籍，不能到达的即为非必需书籍。

因此，我们可以在反图中以结点 $ 1 $ 为源点进行搜索，将可以到达的结点标记为必需书籍对应的结点，再对原图中由必需书籍所对应结点组成的子图进行拓扑排序，即可得到答案。

不过，本题还有更简单的实现方式。

考虑在反图中以结点 $ 1 $ 为源点进行搜索的过程。如果我们采用的搜索方式是 DFS，那么我们得到的搜索树将会有如下性质：

- 对于搜索树上的非叶子结点 $ x $，设以结点 $ x $ 为根的子树为 $ \operatorname{subtree}(x) $，则对于 $ \operatorname{subtree}(x) $ 上除 $ x $ 以外的所有结点 $ y $，在答案序列中，$ y $ 总排在 $ x $ 之前。

依据这个性质，我们在反图中进行 DFS 时，在遍历完 $ \operatorname{subtree}(x) $ 之后（此时子树中除 $ x $ 以外的所有结点均以被加入答案序列中），再将 $ x $ 加入答案序列，即可得到符合条件的阅读顺序。

具体代码如下：

```cpp
void dfs(const int cur) {
	visited[cur] = true;
	for (int i = head[cur]; i; i = edge[i].next) {
		int to = edge[i].to;
		if (visited[to]) {
			continue;
		}
		dfs(to);
	}
	if (cur != 1) {
		printf("%d ", cur);
	}
}
```

所以，我们可以直接通过 DFS 得到答案，从而省去拓扑排序。

完整代码如下：

```cpp
#include <iostream>
#include <queue>

const int max_n = 2e5 + 10;

struct Edge {
	int next;
	int to;
};

int head[max_n];
Edge edge[max_n];
int edge_idx = 0;
bool visited[max_n];

void add_edge(const int from, const int to);
void dfs(const int cur);

int main() {

	int n;
	scanf("%d", &n);
	for (int from = 1; from <= n; ++from) {
		int out_degree;
		scanf("%d", &out_degree);
		for (int i = 1; i <= out_degree; ++i) {
			int to;
			scanf("%d", &to);
			add_edge(from, to);
		}
	}

	dfs(1);

	return 0;
}

void add_edge(const int from, const int to) {
	edge[++edge_idx].to = to;
	edge[edge_idx].next = head[from];
	head[from] = edge_idx;
}

void dfs(const int cur) {
	visited[cur] = true;
	for (int i = head[cur]; i; i = edge[i].next) {
		int to = edge[i].to;
		if (visited[to]) {
			continue;
		}
		dfs(to);
	}
	if (cur != 1) {
		printf("%d ", cur);
	}
}
```

---

## 作者：六楼溜刘 (赞：1)

~~最近的 ABC 真是越来越水了。~~

update 2023.8.24：修改笔误（DEG -> DAG）

## 题意

- 有 $N$ 本书，第 $i$ 本书有 $C_i$ 本前置读物 $P_{i,1},P_{i,2}\dots P_{i,c_i}$。
- 现在你想读第 $1$ 本书，问在读第 $1$ 本书之前至少还要读哪些书。
- 输出读它们的顺序，多解输出任意一个。
- 保证有解，$1 \le N,\sum C_i \le 2\times 10^5$，其他数据在合理范围内。

## 题解

这个题意乍一看挺复杂。其实形式化后就是给你一张所有 $P_{i,j}\to i$ 连边的有向图，然后要点给 $1$ 涂色，能给一个点涂色当且仅当入边对应的点全被涂色。

这样题意就明了了，由于保证有解所以整个图其实是个 DAG，那么其实按拓扑序涂色就行了。

另外，我们发现假如不存在一条 $i\to 1$ 的路径，其实点 $i$ 是不用涂色的。那么我们在反图上从点 $1$ 开始 DFS 给要涂色的点打个标记即可，最后输出时跳过没打标记的点。复杂度 $O(n)$。

## code（和文字题解有一定出入，大体思路一样）

```cpp
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
#define forup(i,s,e) for(int i=(s);i<=(e);i++)
#define fordown(i,s,e) for(int i=(s);i>=(e);i--)
using namespace std;
#define gc getchar()
inline int read(){
    int x=0,f=1;char c;
    while(!isdigit(c=gc)) if(c=='-') f=-1;
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=gc;}
    return x*f;
}
#undef gc
const int N=2e5+5,inf=0x3f3f3f3f;
int n;
vector<int> e[N],e1[N];//反图，正图
int vis[N],rd[N],v1[N];//标记，入度，是否已经删除（再跑拓扑序时）
void dfs(int x){//在反图上跑给能到 1 的点打标记
	vis[x]=1;
	for(auto i:e[x]){
		if(vis[i]) continue;
		dfs(i);
	}
}
vector<int> ans;
signed main(){
	n=read();
	forup(i,1,n){
		rd[i]=read();
		forup(j,1,rd[i]){
			int u=read();
			e[i].push_back(u);
			e1[u].push_back(i);
		}
	}
	dfs(1);
	vector<int> vec,vv;
	forup(i,1,n){
		if(!vis[i]) continue;
     //代码里是直接忽略没打标记的点，其实是一样的
		if(rd[i]==0) vec.push_back(i);
	}
	while(!v1[1]){//拓扑排序板子
		vv.clear();
		for(auto u:vec){
			ans.push_back(u);
			v1[u]=1;
			for(auto v:e1[u]){
				if(!vis[v]) continue;
				rd[v]--;
				if(rd[v]==0) vv.push_back(v);
			}
		}
		vec=vv;
	}
	for(auto i:ans){
		if(i==1) break;
		printf("%d ",i);
	}
}
```

---

## 作者：_zzzzzzy_ (赞：0)

# 思路

发现这个就是可以感性理解一下我们要学一个东西就要学另一个东西，可以用这个关系来进行建图。

发现我们是要学习 $1$ 的那么我们就要把连到 $1$ 的所有点都学一遍，然后递归定义就相当于后序遍历以 $1$ 为根的树。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int maxn = 1000000;
vector<int> e[maxn];
int a[maxn];
int tot;
int vis[maxn];
void dfs(int x) {
	vis[x] = 1;
	for (int v : e[x]) {
		if (!vis[v]) {
			dfs(v);
		}
	}
	a[++tot] = x;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.precision(6);

	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int k;
		cin >> k;
		for (int j = 1; j <= k; j++) {
			int x;
			cin >> x;
			e[i].push_back(x);
		}
	}
	dfs(1);
	for (int i = 1; i < tot; i++) {
		cout << a[i] << " ";
	}
	return 0;
}
```

---

## 作者：Failure_Terminator (赞：0)

## Solution

给一种麻烦（恶臭）做法。

先由 $C_i$ 相对应的 $P_{i,j}$ 建边，用一遍 `bfs` 跑出所有的书是否必须需要阅读。

然后对于每条边反向建边，进行一次拓扑排序，跑出阅读的顺序。

最后输出时选择必须需要阅读的输出即可。

## AC Code

[1.53KB 巨长代码](https://atcoder.jp/contests/abc315/submissions/44762095)

---

## 作者：umcalla (赞：0)

## 思路

如果读第 $i$ 本书前要读第 $j$ 本书，那么就建一条从 $i$ 到 $j$ 的有向边。

因为本题并不会出现无解的情况，所以用 DFS 从点 $1$ 开始扫一遍，每个点遍历完之后存入答案即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> g[200010];
vector<int> ans;
bool v[200010];
int n;
void dfs(int u)
{
	v[u]=1;
	for(auto i:g[u])
		if(!v[i])
			dfs(i);
	if(u!=1)
		ans.push_back(u);
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int k;
		cin>>k;
		while(k--)
		{
			int v;
			cin>>v;
			g[i].push_back(v);
		}
	}
	dfs(1);
	for(auto i:ans)
      	cout<<i<<" ";
	return 0;
}
```

---

## 作者：Crazyouth (赞：0)

**翻译**

你有 $n$ 本书，每本书都有 $c_i$ 个前置芝士（即你需要读完 $c_i$ 本指定的书才能读第 $i$ 本），求读完第 $1$ 本需要先读完哪些书（保证不会存在两本书相互为前置芝士）。

**分析**

对 abc315 的一些评价：你 C 题是橙题就算了，E 题一个拓扑排序板子，一个橙题这多少有点说不过去了吧。

拓扑板子。每一本书向它的前置芝士连边，一个 DAG 就建模完成了（题目中保证了无环）。跑个 DFS，把 DFS 到的节点输出，然后判一下是 $1$ 就不输出就行了。

**AC Code**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int vis[N],nxt[N],head[N],to[N],cnt=0;
void addedge(int u,int v)
{
	cnt++;
	nxt[cnt]=head[u];
	head[u]=cnt;
	to[cnt]=v;
}
int dfs(int u)
{
	vis[u]=1;
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(!vis[v]) dfs(v);
	}
	if(u!=1)//不是1才输出
	cout<<u<<' ';
}
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int c;
		cin>>c;
		for(int j=1;j<=c;j++)
		{
			int v;
			cin>>v;
			addedge(i,v);//向前置芝士连边
		}
	}
	dfs(1);//从1开始搜
	return 0;
}

---

## 作者：刘辰雨 (赞：0)

听说有更简做法，但我的做法总归没错。

# 0x00 译

给定 $n$ 个条件，第 $i$ 条形如 $c_1,c_2,\dots ,c_k$，表示要看第 $i$ 本书，必须先看完 $c_1,c_2,\dots ,c_k$。

问要看完 $1$ 号书，最少需要看多少本书？输出任意看书顺序，不包括第 $1$ 本。

注意：不必看完所有书，看到第 $1$ 本可止。

----

$\textit{Translate by Rain.}$

# 0x01 解

如果只考虑看多少本书，那么按照约束条件反向建边，从 $1$ 号点 $\text{DFS}$ 即可。但是考虑到顺序问题，赛时并不放心，于是再正向建边，拓扑排序，将 $\text{DFS}$ 出来的点按拓扑序再排一边即可。很开心。

# 0x02 码

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <bitset>
#include <algorithm>
using namespace std;

vector<int> vec[200005], G[200005];
int rd[200005];
int c[200005];
int n;
queue<int> q;
int res[200005], cnt;
bitset<200005> vist;

void find(int now) {
	for(int tmp : G[now]) {
		if(!vist[tmp]) res[++cnt] = tmp, vist[tmp] = true, find(tmp);
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1, l ; i<= n ; i++) {
		scanf("%d", &l);
		rd[i] = l;
		while(l--) {
			int v;
			scanf("%d", &v);
			vec[v].push_back(i);
			G[i].push_back(v);
		}
	}
	for(int i = 1 ; i<= n ; i++) {
		if(rd[i] == 0) q.push(i);
	}
	int tot = 0;
	while(!q.empty()) {
		int now = q.front();
		q.pop();
		for(int tmp : vec[now]) {
			if(rd[tmp]) {
				rd[tmp]--;
				if(!rd[tmp]) q.push(tmp), c[tmp] = c[now]+1;
			}
		}
	}
	find(1);
	sort(res+1, res+cnt+1, [](int x, int y) {
		return c[x] != c[y] ? c[x] < c[y] : x < y;
	});
	for(int i = 1 ; i<= cnt ; i++) {
		printf("%d ", res[i]);
		if(res[i] == 1) break;
	}
	return 0;
}
```

[Atcoder AC记录](https://atcoder.jp/contests/abc315/submissions/44746333)

---

## 作者：Imken (赞：0)

题意就是，有 $N$ 本书，每本书 $i$ 需要在阅读前先阅读一些依赖的书；要求以最少阅读量完成书 $1$ 的阅读，按照满足依赖关系的阅读顺序打印出必须阅读的除书 $1$ 以外的书的编号。

就是个拓扑排序板子，但是为了满足最小阅读量，所以跑一遍深搜把不会访问到的点排除出点集就行。

Code:

```cpp
void dfs(int u)
{
	vis[u] = 1;
	for (auto v : G[u]) {
		if (!vis[v])
			dfs(v);
	}
}

int main()
{
	io_init();
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> cnt;
		deg[i] = cnt;
		G[i].reserve(cnt);
		for (int j = 1; j <= cnt; j++) {
			cin >> v;
			G[i].push_back(v);
			rg[v].push_back(i);
		}
	}
	dfs(1);
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) deg[i] = -1;
	}
	for (int i = 1; i <= n; i++) {
		if (deg[i] == 0)
			q.push(i);
	}
	while (!q.empty()) {
		int u = q.front(); q.pop();
		rd.push_back(u);
		for (int v : rg[u]) {
			if (--deg[v] == 0)
				q.push(v);
		}
	}
	for (int x : rd) if (x != 1) cout << x << ' ';
	return 0;
}
```


---

## 作者：CJ_Fu (赞：0)

## 题目链接

[洛谷](https://www.luogu.com.cn/problem/AT_abc315_e)

[AtCoder](https://atcoder.jp/contests/abc315/tasks/abc315_e)

## 简要题意

给出 $N$ 本书，可以阅读第 $i$ 本书的前提是阅读第 $P_{i,1}\sim P_{i,C_i}$ 本书，求阅读第一本书的最少书的本数，题目保证有解使得阅读完所有书籍。

输出任一阅读顺序（$1$ 不需要输出）。

$2\le n\le 2\times 10^5$，对于所有 $1\le j<k\le C_i$ 满足 $P_{i,j}\not= P_{i,k}$。

## 思路

很容易可以想到按照 $P_{i,j}\to i(1\le j\le C_i)$ 建边，比如样例 $1$：

![](https://cdn.luogu.com.cn/upload/image_hosting/2araldx4.png)

因为保证有解，所以在这个有向图上不存在环。

然后你发现事情没有这么简单，直接拓扑排序会有问题。因为这个有向图不一定连通（比如样例 $3$）。

所以我们可以先建原图的反图，然后以 $1$ 为根 DFS，搜到的点标记一下，然后再在原图中对应被标记的点上跑拓扑排序即可。

时间复杂度 $O(n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,c;
vector<int>e1[200003],e2[200003];
bool vis[200003]; // 标记
int in[200003],pro[200003],top;
#define pb emplace_back
void dfs(int u){
	for(int v:e1[u]){
		in[u]++;
		e2[v].pb(u); // 原图
		if(!vis[v]){
			vis[v]=1;
			dfs(v);
		}
	}
}
void Dfs(int u){
	if(u!=1)cout<<u<<' ';
	for(int v:e2[u])
		if(!--in[v]) Dfs(v);
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>c;
		for(int j=1,p;j<=c;j++){
			cin>>p;
			e1[i].pb(p); // 反图
		}
	}
	vis[1]=1; dfs(1);
	for(int i=1;i<=n;i++)
		if(!in[i]&&vis[i]) pro[++top]=i;
	for(int i=1;i<=top;i++)	Dfs(pro[i]); // 拓扑
	return 0;
} 
```

可能是最近最水的 E 题？

---

## 作者：God_Max_Me (赞：0)

## 题意

给定你 $n$ 本书，在读第 $i$ 本书的时候，必须先读完若干本书（怎么看着像拓扑排序），现在要求想读第 $1$ 本书之前，要先按顺序读完哪些书？

## 思路

很显然，若读完第 $1$ 本书之前要先读完 $a_1,a_2\dots a_n$，那么又考虑子部分，即读 $a_1,a_2\dots a_n$ 又先需要读完哪些书。

显然可以用 dfs 搞定，深搜读当前书要先读哪些书，返回的时候加入 $ans$ 数组记录，并用 $vis$ 数组标记，最后输出 $ans$ 即可。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
template<typename P>
inline void read(P &x){
   	P res=0,f=1;
   	char ch=getchar();
   	while(ch<'0' || ch>'9'){
   		if(ch=='-') f=-1;
   		ch=getchar();
   	}
   	while(ch>='0' && ch<='9'){
   		res=res*10+ch-'0';
   		ch=getchar();
	}
	x=res*f;
}
int n;
const int Max=200010;
struct egde{
	int to,nxt;
}e[Max<<1];
int head[Max],cnt=0;
void add(int u,int v){
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
int c[Max];
vector<int> a[Max];
vector<int> ans;
bool vis[Max];
void dfs(int u,int fa){
	vis[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int to=e[i].to;
		if(!vis[to] && to!=fa){
			dfs(to,u);
		}
	}
	ans.push_back(u);
}
signed main(){
	read(n);
	for(int i=1;i<=n;++i){
		read(c[i]);
		int x;
		for(int j=1;j<=c[i];++j){
			read(x);
			a[i].push_back(x);
			add(i,x);
		}
	}
	for(int i=0;i<c[1];++i){
		int p=a[1][i];
		if(!vis[p]){
			dfs(p,0);
		}
	}
	for(int i=0;i<ans.size();++i){
		cout<<ans[i]<<' ';
	}
	cout<<endl;
	return 0;
}


```


---

