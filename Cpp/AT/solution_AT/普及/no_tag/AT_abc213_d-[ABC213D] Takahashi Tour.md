# [ABC213D] Takahashi Tour

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc213/tasks/abc213_d

AtCoder 国には $ 1 $ から $ N $ の番号がついた $ N $ 個の都市と、$ 1 $ から $ N-1 $ の番号がついた $ N-1 $ 個の道路があります。  
 道路 $ i $ を通ると都市 $ A_i $ と都市 $ B_i $ の間を相互に移動することができます。全ての都市は道路を使って互いに行き来できることが保証されます。

高橋くんは都市 $ 1 $ を出発し、次のルールで旅をします。

- いまいる都市と道路で直接つながっている都市のうち、まだ訪れたことがない都市が存在するとき、そのような都市のうち番号が最も小さい都市へ移動する
- そのような都市が存在しないとき
  - いまいる都市が都市 $ 1 $ なら旅を終了する
  - そうでないなら、いまいる都市を初めて訪れたときに直前にいた都市へ移動する

高橋くんが旅の過程で訪れる都市を順に答えてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i,B_i\ \leq\ N $
- 全ての都市は道路を使って互いに行き来できる

### Sample Explanation 1

高橋くんの旅は次のようになります。 - 最初都市 $ 1 $ にいます。 - 都市 $ 1 $ から道路で直接つながっている都市のうち未訪問なのは都市 $ 2,3 $ です。番号が小さい都市 $ 2 $ へ移動します。 - 都市 $ 2 $ から道路で直接つながっている都市のうち未訪問なのは都市 $ 4 $ です。都市 $ 4 $ へ移動します。 - 都市 $ 4 $ から道路で直接つながっている都市のうち未訪問の都市はありません。直前にいた都市 $ 2 $ へ移動します。 - 都市 $ 2 $ から道路で直接つながっている都市のうち未訪問の都市はありません。初めて都市 $ 2 $ に来る直前にいた都市 $ 1 $ へ移動します。 - 都市 $ 1 $ から道路で直接つながっている都市のうち未訪問なのは都市 $ 3 $ です。都市 $ 3 $ へ移動します。 - 都市 $ 3 $ から道路で直接つながっている都市のうち未訪問の都市はありません。直前にいた都市 $ 1 $ へ移動します。 - 都市 $ 1 $ から道路で直接つながっている都市のうち未訪問の都市はありません。旅を終了します。

## 样例 #1

### 输入

```
4
1 2
4 2
3 1```

### 输出

```
1 2 4 2 1 3 1```

## 样例 #2

### 输入

```
5
1 2
1 3
1 4
1 5```

### 输出

```
1 2 1 3 1 4 1 5 1```

# 题解

## 作者：L_zaa_L (赞：5)

## 题意
给定一个 $n$ 个点，$n-1$ 条边的图，最初在点 $1$，按如下规则行走:

如果与这个点直接连接的点中有没去过的，就去其中编号最小的那一个。

否则：

- 如果当前在点 $1$ 就退出。

- 否则回到上一个点。

输出遍历过程。
## 分析
假如这个图长这样：

![](https://pic1.zhimg.com/80/v2-82146333a2190854e5da6989a5483d73_720w.png)

那么按照题意，他应该每次往左边走（因为左边小），每次到达叶节点就一直返回上一层，直到这个节点有另一个子节点就继续搜。那么这张图的答案就应该是 $1-2-4-2-5-2-1-3-6-3-1$。

那么总所周知，边可以用边表和 vector 用来优化，但由于边表需要多个变量，所以这里建议用 vector，因为排好序就可以按照从小到大的顺序遍历子节点。

### 边表
```
void add(int a,int b){to[++tot]=b;nxt[tot]=head[a];head[a]=tot;}
```

### vector
```
a[v].push_back(u);
a[u].push_back(v);

```

但是父节点遍历怎么办呢，需要每次记录父节点吗？其实不用，因为尽人皆知，搜索是先进行前一句话，在后面的一句话只有等上一句执行完后才能执行，所以即使这句话前面有搜索，他也会先搜索，再执行。所以可以先执行搜索子节点的搜索，再在后面加上输出这个节点即可。

## Code
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){//快读
    int s=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch == '-') f=-1;ch=getchar();}
    while(isdigit(ch)){s=s*10+ch-'0';ch=getchar();}
    return s*f;
}
void write(int x){//快写
    if(x<0){putchar('-');x=-x;}
    if(x>9) write(x/10);
    putchar(x%10+'0');
    return;
}
int n;
bool book[200005];//标记每个点有没有被走过
vector<int>a[200005];
void dfs(int city){
	cout<<city<<" ";
	for(int i=0;i<a[city].size();i++)
		if(!book[a[city][i]]){//如果子节点没有被遍历过
			book[a[city][i]]=1;//记录
			dfs(a[city][i]);//循环
			cout<<city<<" ";//子节点遍历完后就会输出
		}
}
signed main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		a[v].push_back(u);
		a[u].push_back(v);
	}
	book[1]=1;
	for(int i=1;i<=n;i++)
		sort(a[i].begin(),a[i].end());//将每条边排序，所以可以从小到大遍历；
	dfs(1);//从1开始搜索
	return 0;
}


```

---

## 作者：Little_x_starTYJ (赞：4)

### 题目大意
给定一个 $n$ 个点的无向图，从根节点 $1$ 开始，按照以下遍历规则遍历:


1. 如果这个点所能到达的点中有没有遍历过的，那么就按照编号的从小到大的顺序遍历。

2. 否则，那么：
	- 如果此点为 $1$，结束遍历。
   - 否则回溯到上一点。

请你按照遍历顺序输出到达过的点的编号。
### 解题思路
我们先用 `vector` 容器存储这个无向图，再进行一次从小到大的排序，然后从根节点开始搜索，标记每个点的到达情况即可。

CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> a[200010];
bool vis[200010];
void dfs(int now) {
	cout << now << ' ';
	vis[now] = true;
	for (int i = 0; i < a[now].size(); i++) 
    	if (!vis[a[now][i]])
        	dfs(a[now][i]), cout << now << ' ';
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i < n; i++)	{
		int u, v;
		cin >> u >> v;
	    a[u].push_back(v);
		a[v].push_back(u);
	}
	for (int i = 1; i <= n; i++)
		sort(a[i].begin(), a[i].end());
	dfs(1);
	return 0;
}
```

---

## 作者：filletoto (赞：1)

[传送门](https://www.luogu.com.cn/problem/AT_abc213_d)
# 题意
有一个 $n$ 个点的无向图。从根节点 $1$ 开始，按如下规则遍历整个图：

1. 如果有连接这个点的其他点没有走过，则到这个点。如果有多个点，那么按从小到大的顺序走。

1. 如果有这个点没有其他点或者连接这个点的其他点都走过了，那么：

	- 如果这个点是根节点 $1$，结束。
   - 否则回到上一个点。


# 思路
先用 `vector` 存储这张图（注意是无向图）。由于要按从小到大的顺序，所以还需要进行排序。

再从根节点 $1$ 开始深搜。用 $vis$ 数组标记这个点有没有走过。

#### 注意:题目要求的是遍历的过程所以返回的上一个节点编号也要输出。

# 代码
[AC 记录](https://www.luogu.com.cn/record/148287297)
```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> e[200005];
int vis[200005];
int n;
inline void dfs(int x)
{
	vis[x]=1;//标记
	cout << x << " ";
	for(int i=0;i<e[x].size();i++)
	{
		if(!vis[e[x][i]])
		{
			dfs(e[x][i]);
			cout << x << " ";//注意要输出他的上一个节点
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<n;i++)
	{
		int x,y;
		cin>>x>>y;
		e[x].push_back(y);
		e[y].push_back(x);//注意是无向图
	}
	for(int i=1;i<=n;i++)
	{
		sort(e[i].begin(),e[i].end());//从小到大排序
	}
	dfs(1);



	return 0;
}
```

---

## 作者：Symbolize (赞：1)

# $\tt{Solution}$
就是求个欧拉序，每次要走编号小的，那实际上就是排序，这题如果使用邻接表会很简单，但是我并不是那样喜欢邻接表，所以我想讲一讲用链式前向星如何做。

思考一下一下链式前向星的工作原理，你会发现，最先放入里面的边会最后遍历（对于起点一致的边而言）。所以说这里的排序是从大到小而不是从小到大。然后就是深搜的时候记得是在刚进入的时候输出一遍，递归完过后再输出一遍。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(register int i=l;i<=r;++i)
#define rep2(i,l,r) for(register int i=l;i>=r;--i)
#define rep3(i,h,x,ne) for(register int i=h[x];~i;i=ne[i])
#define debug() puts("----------")
const int N=4e5+10;
using namespace std;
int n,h[N],e[N],ne[N],idx;
vector<int> G[N];
int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
void add(int x,int y)
{
	e[idx]=y;
	ne[idx]=h[x];
	h[x]=idx++;
	return;
}
void dfs(int x,int fa)
{
	cout<<x<<' ';
	rep3(i,h,x,ne)
	{
		int to=e[i];
		if(to==fa) continue;
		dfs(to,x);
		cout<<x<<' ';
	}
	return;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	memset(h,-1,sizeof h);
	n=read();
	rep1(i,1,n-1)
	{
		int u=read();
		int v=read();
		G[u].push_back(v);
		G[v].push_back(u);
	}
	rep1(i,1,n)
	{
		sort(G[i].begin(),G[i].end());
		reverse(G[i].begin(),G[i].end());
		for(auto x:G[i]) add(i,x);
	}
	dfs(1,0);
	putchar('\n');
	return 0;
}

```

---

## 作者：冷却心 (赞：1)

## 题意

给定一个 $n$ 个点（按 $1,2,3\dots,n-1,n$ 编号）， $n - 1$ 条边的图，高桥最初在点 $1$，他会按如下规则行走:

- 如果与这个点直接连接的点中有没去过的，就去其中编号最小的那一个。

- 如果没有：

	- 如果当前在点 $1$ 就退出。
    
   - 否则回到上一个点。

输出高桥依次经过的点的编号。

## 解法

一看题，这不就是求遍历这张图的 DFS 序吗，每遍历到一个节点就输出。

但还要注意，它回到上一个点也要输出，看如下代码段（$x$ 代表当前点）：

```cpp
cout << x << " ";
for (LL to : g[x]){
	if (!vis[to]){
		vis[to] = 1;
		DFS(to);
		cout << x << " ";
	}
}
```

`DFS(to)` 的下一行 `cout << x << " "` 就是 DFS 过 $x$ 的某一棵子树后，还要输出一下它本身，就代表从子结点回到上一个点。

## Code

```cpp
#include<bits/stdc++.h>
#define LL long long
#define Fcin\
	ios :: sync_with_stdio(0);\
	cin.tie(0); cout.tie(0)
using namespace std;
const LL N = 2e5 + 10;
LL n, vis[N];
vector<LL> g[N];

void DFS(LL x){
	cout << x << " ";
	for (LL to : g[x]){
		if (!vis[to]){
			vis[to] = 1;
			DFS(to);
			cout << x << " ";
		}
	}
	return ;
}
int main(){
	memset(vis, 0, sizeof(vis));
	Fcin;
	cin >> n;
	LL u, v;
	for (LL i = 1; i <= n - 1; i ++){
		cin >> u >> v;
		g[u].emplace_back(v);
		g[v].emplace_back(u);
	}
	
	for (LL i = 1; i <= n; i ++)
		sort(g[i].begin(), g[i].end());
	
	LL now = 1;
	vis[now] = 1;
	DFS(1);
	
	return 0;
}
```



---

## 作者：niuzh (赞：0)

### 思路

可以直接 ```dfs```，用一个 $vis$ 记录当前节点是否到过，搜索到一个点时输出当前节点。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
vector<int> g[N];
bitset<N> vis;
void dfs(int u)
{
	vis[u]=1;//记录
	cout<<u<<" ";//输出
	for (int i=0;i<g[u].size(); i++)
	{
		if (!vis[g[u][i]])
		{
			dfs(g[u][i]);
			cout<<u<<" ";//回溯时也要输出
		}
	}
}
int main()
{
	int n;
	cin>>n;
	for (int i=1,u,v; i<n; i++)
	{
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i=1; i<=n; i++)
	{
		sort(g[i].begin(),g[i].end());//搜索子节点时权值小的靠前
	}
	dfs(1);
	return 0;
}
```

---

## 作者：Li_Yichen (赞：0)

把树看为无向图，如果这个点能走，就走编号最小的。如果不能的话，如果这一点为一，直接返回，否则回溯到上一个点。我们使用邻接表来存，因为要走到编号最小的，所以直接把每一个点能到达的点从小到大排序即可，注意无向图要建双向边。

```
#include<bits/stdc++.h>
using namespace std;
int n; 
vector<int> g[200005];
int vis[200005];
void dfs(int u){
	cout << u << " ";
	vis[u] = 1;
	for(int i=0;i<g[u].size();i++){
		int v = g[u][i];//走到编号最小的 
		if(vis[v]) continue;
		vis[v] = 1;
		dfs(v);//接着遍历 
		cout << u << " ";//回溯 
	}
}
int main(){
	cin >> n;
	for(int i=1;i<n;i++){
		int u,v;
		cin >> u >> v;
		//无向图建双向边 
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		sort(g[i].begin(),g[i].end());//给每一个点排序 
	}
	dfs(1);
	return 0;
}


```

---

## 作者：seika27 (赞：0)

### 题意
给定一个图，起始点为点 $1$。

要求按照规则遍历。

如果与当前节点连接得点中有没遍历过的，去其中最小的一个。

如果与当前点连接得点中全部被遍历过，且当前点是点 $1$，退出。

如果与当前点连接得点中全部被遍历过，且当前点不是点 $1$，那就返回上一个点。

### 思路
由于需要排序，推荐使用 ```vector``` 

对于第一条规则，我们只需将每个点所连得点排序即可。

需要注意的是，由于第三条规则的存在，每当我们遍历完与节点 $x$ 相连的一个节点后，需要输出 $x$。

然后就从 $1$ 号节点开始深搜，记得用一个数组记录这个点是否遍历过。

### code
```cpp
#include <bits/stdc++.h>
#define int long long 
#define cin std::cin
#define cout std::cout
const int N=2e5+5;
int n;
std::vector<int>g[N];
int vis[N]; 
void dfs(int x)
{
	vis[x]=1;
	cout<<x<<' ';
	for(int i=0;i<g[x].size();i++)
	{
		int v=g[x][i];
		if(vis[v])continue;
		dfs(v);
		cout<<x<<' ';	//第三条规则
	}
}
signed main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<n;i++)
	{
		int u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for(int i=1;i<=n;i++)std::sort(g[i].begin(),g[i].end());	//第一条规则
	dfs(1);
	return 0;
}
```

---

## 作者：jess1ca1o0g3 (赞：0)

[Portal(AT)](https://atcoder.jp/contests/abc213/tasks/abc213_d)

[Portal(Luogu)](https://www.luogu.com.cn/problem/AT_abc213_d)

## 题意

给你一张 $n$ 个点，$n-1$ 条边的无向图，从 $1$ 开始：

- 如果这个点相连的点还没走过，到最小的。

- 否则回溯，如果点为 $1$ 则退出。

  打印整个过程，不考虑重复。

## 思路

把树建成图，由于要从小到大遍历，对每个点的连接点进行排序。

正常深搜，打印每个点就好了。

## Code

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
vector<vector<int>> g;
vector<bool> vis;
int n,u,v;
void dfs(int u){
    vis[u]=1;
    printf("%d ",u);
    for(int i=0;i<g[u].size();i++){
        if(!vis[g[u][i]]){
            dfs(g[u][i]);
            printf("%d ",u);
        }
    }
}
void add(int u,int v){
    g[u].push_back(v);
    g[v].push_back(u);
}
signed main(){
    scanf("%d",&n);
    vis.resize(n+1,0);
    g.resize(n+1);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&u,&v);
        add(u,v);
    }
    for(int i=1;i<=n;i++) sort(g[i].begin(),g[i].end());
    dfs(1);
    return 0;
}
```



---

## 作者：2021zjhs005 (赞：0)

Part $0$. 前置知识
------------

遍历**树**的**深搜**方法

Part $1$. 题目大意
------------

有一棵树（其实原题中是都市，现在就用树来说），它有 $n$ 个结点，编号为 $1$，$2$，$3$，$\ldots$，$n$。

它的**根结点**是 $1$。

现在给定 $n-1$ 个 $a$ 和 $b$，其中 $a$ 和 $b$ 是这棵树上的一个结点，表示结点 $a$ 和结点 $b$ 连通。

现在从根结点 $1$ 开始遍历每一个结点，需要满足如下条件：

- 如果当前结点有可到达的结点，且有**多个可到达**的结点，则先访问**编号小**的结点。

- 否则返回上一个结点，直到整棵树遍历完毕。

要求：输出这一棵树的**遍历的状态**（就是输出遍历的过程中所到达的结点，**不管会不会重复**）。


Part $2$. 题目分析
------------

通过题目大意，我们可以得到：这就是一道 **dfs** 基础题。

没有碰到过此类 dfs 题目的人，建议先做[查找文献](https://www.luogu.com.cn/problem/P5318)~~（顺便学一下 bfs 宽搜）。~~

首先，我们需要**建图**（树是一种特殊的图）。

分两步骤：

1. 选择邻接矩阵还是邻接表存储图。

1. 用什么数据结构存。

如果不知道什么是邻接矩阵还是邻接表，[看这篇](https://blog.csdn.net/cristianoxm/article/details/106802886)。

### 分析问题

1. 因为图的结点数量 $n\le 2\times 10^5$，所以**不能用邻接矩阵**存，要用**邻接表**。

1. 用 `vector` 存储更好，数组要用**二维**，队列**不能保证结点的从小到大**（为了使字典序最小，所以要排序），优先队列**不能直接访问第 $i$ 个元素**。



------------

所以可以打出如下代码：


```cpp
void add(int x,int y){
//树是无向图，两个结点互相连通，谁都可以到谁。
    edge[x].push_back(y);
    edge[y].push_back(x);//存储。
}
```



------------
其次，需要将存放元素进行**从小到大排序**：

```cpp
for(int i=1;i<=n;i++)
    sort(edge[i].begin(),edge[i].end());
    //将容器内的元素排序。
```



------------
最后，就是解决 dfs 深搜了！

我们用一个 `f` 数组来表示**结点是否遍历过**，是就 $1$，否则就是 $0$。

然后用一个循环访问当前结点**可以达到的所有结点**。如果还**没有遍历过**，就从这个**子结点继续深搜**。

接着输出每一个结点即可。

```cpp
void dfs(int x){
    f[x]=1;//标记。
    cout<<x<<" ";//输出。
    for(int i=0;i<edge[x].size();i++)//可遍历的所有结点。
        if(!f[edge[x][i]]){//没有遍历过。
            dfs(edge[x][i]);//深搜。
            cout<<x<<" ";//注意，上面的输出是输出子结点，等回来了还要输出父亲结点！
        }
    //return;
/*加不加无所谓，如果没有回溯完该函数会继续回溯。*/
}
```


Part $3$. AC 代码
------------

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int n,m,f[N];
vector <int> edge[N];
queue <int> q;
void add(int x,int y){
    edge[x].push_back(y);
    edge[y].push_back(x);
}
void dfs(int x){
    f[x]=1;
    cout<<x<<" ";
    for(int i=0;i<edge[x].size();i++)
        if(!f[edge[x][i]]){
            dfs(edge[x][i]);
            cout<<x<<" ";		
    }
}
int main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int a,b;
        cin>>a>>b;
        add(a,b);//建图。
    }
    for(int i=1;i<=n;i++)
        sort(edge[i].begin(),edge[i].end());//排序。
    dfs(1);//深搜。
    return 0;
}
```

---

## 作者：ruanwentao666 (赞：0)

# AT_abc213_d 题解
[题目传送门](https://www.luogu.com.cn/problem/AT_abc213_d)

## 题意分析
题意简化：按照如下方式遍历树。

步骤：

1. 寻找当前节点的子节点中，未遍历过的编号最小的一个。

2. 重复操作 $1$，直到当前节点为叶子节点为止，回退到上一个节点。

最后只需输出每一步所到达的节点的编号即可。

注：要求是字典序最小的哦。

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
priority_queue<int,vector<int>,greater<int> >g[200005];
bool vis[200005];
void dfs(int u){
	cout<<u<<" ";
	while(!g[u].empty()){
		int t=g[u].top();
		g[u].pop();
		if(!vis[t]){
			vis[t]=1;
			dfs(t);
			cout<<u<<" ";
		}
	}
}
int main(){
	cin>>n;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		g[u].push(v);
		g[v].push(u);
	}
	vis[1]=1;
	dfs(1);
	return 0;
}

```


---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc213_d)

一道 `dfs` 序题。

题目中高桥每次只会去最小的那个点，所以要先对整张图进行排序。

```cpp
for (int i = 1; i <= n; i++) sort(g[i].begin(), g[i].end());
```
然后考虑 `dfs`。高桥不会走重复的点，所以我们可以开一个 `vis` 数组进行标记。然后我们需要处理高桥君如果无路可走会返回上一个点的情况。在 `dfs` 回溯后输出当前节点即可。

```cpp
void dfs(int cur) {
    vis[cur] = 1;
    cout << cur << " ";
    for (auto v : g[cur]) {
        if (vis[v]) continue;
        dfs(v);
        cout << cur << " ";
    }
}
```
### Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 1e9
using namespace std;
vector <int> g[200005];
bool vis[200005]; // 标记高桥走过的点
int n;
void dfs(int cur) {
    vis[cur] = 1; // 每走过一个点就标记一下
    cout << cur << " "; 
    for (auto v : g[cur]) {
        if (vis[v]) continue; // 如果已经走过了就不走了
        dfs(v); // 注意这里要先 dfs
        cout << cur << " ";
    }
}
signed main() {
    ios :: sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) sort(g[i].begin(), g[i].end()); // 排序
    dfs(1);
    return 0;
}
```


---

## 作者：StevenLiTheOIer (赞：0)

## 前言：
我太蒻了，第一篇题解。
## 题意简述：
给定 $n$ 个点（编号为 $1$, $2$, $\cdots$, $n-1$, $n$），$n-1$ 条边的图（其实就是树罢），从点 $1$ 开始按如下规则遍历：

- 如果与当前结点相连的点中有没去过的，那么去编号最小的一个点。
- 否则：
	- 如果回到了编号为 $1$ 的点就结束。
    - 否则返回上一个点（父结点）。

输出经过的点的编号。
## 思路：
容易想到 DFS 序，每到一个新的结点即输出它的编号，注意遍历完一棵子树后还要 **再一次** 输出子树的根。
## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
vector <int> e[200006];
void dfs(int now, int fa)
{
	cout << now << " "; //第一次遍历到时输出 
	if (e[now].size() == 1 && now != 1) return;
	for (int i = 0; i < e[now].size(); i++)
		if (e[now][i] != fa)
			dfs(e[now][i], now), cout << now << " "; //遍历完子树后再次输出 
}
int main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n - 1; i++)
	{
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for (int i = 1; i <= n; i++)
		sort(e[i].begin(), e[i].end());
	dfs(1, 0);
	return 0;
}
```

---

