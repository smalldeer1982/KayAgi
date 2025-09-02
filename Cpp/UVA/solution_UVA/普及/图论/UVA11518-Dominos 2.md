# Dominos 2

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=27&page=show_problem&problem=2513

[PDF](https://uva.onlinejudge.org/external/115/p11518.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11518/7f28ab761227ecc0796512e3a227ad6b7d28229e.png)

## 样例 #1

### 输入

```
1
3 2 1
1 2
2 3
2```

### 输出

```
2```

# 题解

## 作者：wwwidk1234 (赞：7)

[洛谷题目传送门](https://www.luogu.com.cn/problem/UVA11518)

[UVA 题目传送门](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=27&page=show_problem&problem=2513)

[(也许)更好的阅读体验？](https://wwwidk1234.github.io)

## 题目大意
一组多米诺骨牌，将用手推倒若干个，被推倒的多米诺骨牌可让后面的多米诺骨牌倒下，问有几个多米诺骨牌被推倒。

## 题目分析
可将多米诺骨牌视为一个有向图，要模拟推倒的过程，可用**深度优先遍历**方法。

考虑使用**邻接表**储存图，首先读入要存的边 $u,v$，随后将边存入 `vector` 里：

```cpp
adj[u].push_back(v);
```

随后读入起始点 $z$，以 $z$ 为起点，对图进行 DFS 操作。
```cpp
cin >> z;
dfs(z);
```

然后将 DFS 函数补充完整。
```cpp
void dfs(int u)
{
	vis[u] = true;
	int siz = adj[u].size();
	for(int i = 0; i < siz; ++i)
	{
		int now_point = adj[u][i];
		if(!vis[now_point]) dfs(now_point);
	}
}
```

最后，统计被访问过的点的个数，并输出。
```cpp
for(int i = 1; i <= n; i++) ans += vis[i];
cout << ans << endl;
```

**注意**：因为有多组数据，所以应在每组数据处理之前**清空邻接表以及标记数组**。

## 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const short MAXN = 10010;
vector<int> adj[MAXN];
bool vis[MAXN];
int n, m, l;
void dfs(int u)
{
	vis[u] = true;
	int siz = adj[u].size();
	for(int i = 0; i < siz; ++i)
	{
		int now_point = adj[u][i];
		if(!vis[now_point]) dfs(now_point);
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int u, v;
	int T;
	cin >> T;
	while(T--)
	{
		for(int i = 1; i <= n; i++) adj[i].clear();
		memset(vis, 0, sizeof vis);

		cin >> n >> m >> l;
		while(m--)
		{
			cin >> u >> v;
			adj[u].push_back(v);
		}
		int z;
		while(l--)
		{
			cin >> z;
			dfs(z);
		}
		int ans = 0;
		for(int i = 1; i <= n; i++) ans += vis[i];
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：xhhhh36 (赞：3)

[传送门](https://www.luogu.com.cn/problem/UVA11518)
# 题意
共有 $t$ 组数据，每组数据有 $n$ 个多米诺骨牌，$m$ 个关系。每个关系有两个多米诺骨牌 $x$ 和 $y$，代表 $x$ 被推倒后 $y$ 会倒下。有 $l$ 个多米诺骨牌是被手动推倒的，求最后有多少个多米诺骨牌被推倒。
# 思路
dfs 板子题。用链式前向星来存骨牌之间的关系，开一个 $v$ 数组来记录骨牌是否被推倒。从每个被手动推倒的骨牌开始 dfs，每到一个没有被推倒的骨牌处，就让 $ans$ 增加一。最后输出 $ans$ 即可。

记得多测要清空。
# AC code
```cpp
#include <bits/stdc++.h>

using namespace std;
bool v[10005];
int h[10005],cnt,t,n,m,l,ans;
struct Edge{
	int to,nxt;
}e[10005];
void add_edge(int u,int v){
	e[++cnt].to=v;
	e[cnt].nxt=h[u];
	h[u]=cnt;
}
void dfs(int x){
	if (!v[x]){
		v[x]=1;
		ans++;
	}
	for (int i=h[x];i!=-1;i=e[i].nxt){
		int u=e[i].to;
		if (!v[u]) dfs(u);
	}
}
void work(){
	memset(v,0,sizeof(v));
	memset(h,-1,sizeof(h));
	cnt=ans=0;
	cin>>n>>m>>l;
	int x,y;
	for (int i=1;i<=m;i++){
		cin>>x>>y;
		add_edge(x,y);
	}
	for (int i=1;i<=l;i++){
		cin>>x;
		dfs(x);
	}
	cout<<ans<<endl;
}
signed main(){
	cin>>t;
	while (t--) work();
	return 0;
}
```


---

## 作者：ljk8886 (赞：2)

## 题目大意
$n$ 个多米诺骨牌，有 $m$ 组关系，关系的形式为 $u$ 多米诺骨牌能推倒 $v$ 多米诺骨牌，然后推倒 $l$ 个多米诺骨牌，最后问有多少个多米诺骨牌被推到了。

## 题目分析
可以把 $u$ 多米诺骨牌能推倒 $v$ 多米诺骨牌的关系转化为 $u$ 和 $v$ 之间连了一条有向边。所以就可以直接 dfs。**注意：邻接表和标记数组一定要清空。**

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 5;
int T, u, v, n, m, l;
vector<int> e[N]; //邻接表 
bool vis[N]; //标记数组 
void dfs(int u)
{
	vis[u] = true; //标记为被推到了 
	for (int i = 0; i < e[u].size(); i++)
	{
		int v = e[u][i];
		if (vis[v]) continue;
		dfs(v);
	}
}
int main()
{
	scanf("%d", &T);
	while (T--)
	{
		memset(vis, false, sizeof(vis));
		for (int i = 1; i <= n; i++) e[i].clear(); //清空 
		scanf("%d%d%d", &n, &m, &l);
		while (m--)
		{
			scanf("%d%d", &u, &v);
			e[u].push_back(v); //建立有向边 
		}
		while (l--)
		{
			cin >> u;
			dfs(u);
		}
		int ans = 0;
		for (int i = 1; i <= n; i++) ans += (vis[i] == true); //统计有多少个被推到了 
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：da_ke (赞：1)

# 前言

蒟蒻刚学图论，比较入门的图论题目，题解重点讲想法，可以跳读，望支持。

upt 2023/8/10 : 修改笔误。

## 题目翻译

在一个多米诺骨牌上，它击倒了下一个，然后又击倒了那个，一直到最后。有时多米诺骨牌无法击倒下一个。那样的话我们必须用手把它击倒才能让多米诺骨牌再次倒下。给定一组用手击倒的多米诺骨牌，你的任务是确定倒下的多米诺骨子的总数。

（来自百度翻译）

## 题意理解

多米诺骨牌效应，即推倒一个骨牌，后面的骨牌会连锁反应。而本题中需注意：并不是所有的骨牌都推倒。

## 思考过程

### 建模（图）

多米诺骨牌（以下简称骨牌）各自推倒了固定的若干个骨牌。也就是说，一个骨牌连接一些骨牌。

理解题意，不难想到：骨牌都有编号，这个过程可以用图来表示。

不理解的看下面。

#### 什么是图？

图不像线性表一样有前驱后驱，并且连续；也不像树一样有祖先的关系（层次）。它只不过是“地图”或者说“网”。

这是 [OI-Wiki](https://oi-wiki.org) 中给的官方解释：

>图 (Graph) 是由若干给定的顶点及连接两顶点的边所构成的图形，这种图形通常用来描述某些事物之间的某种特定关系。顶点用于代表事物，连接两顶点的边则用于表示两个事物间具有这种关系。

有方向引导的图是有向图，反之为无向图。

本题中，骨牌推骨牌是有方向的，所以是有向图。

#### 如何存储图？

我们存储图的方式叫：**邻接表**。邻接表很像“超链接”。

比如一个网站需要 $5$ 个链接，那这 $5$ 个链接应分别指向 $5$ 个网址。即原网站需要添加 $5$ 个超链接。

懂了吧。

一般的，邻接表用 `vector` 实现。

以下代码中，`linker` 是“链接”信息，第 $x$ 个下标的 `vector` 是顶点 $x$ 连接的点。`maxn` 是顶点的数量。

```cpp

vector<int> linker[maxn];

void addEdge(int x,int y){ //建边,边是图的连接者.
    linker[x].push_back(y);
}

```

### 搜索/遍历

深度优先，就是使劲按链接给的信息向下**遍历**，这叫做“深度优先遍历（dfs）”。

一般的，深度优先用**递归**实现：

```cpp
void dfs(int d){ //d是深度(点的编号或其他)
    if(边界条件){
        return ;
    } //这个条件也可以在递归的时候处理.
    for(枚举状态(即能到达的点))
        dfs(这个能到达的状态(点)); //递归.
}
```

### 理清思路

对一个图给出的出发点遍历，算出已遍历的点的个数。

### 实现

代码（无注释）：

```cpp
#include <bits/stdc++.h>

using namespace std;

vector<int> linker[100024];
int vis[10024];

void dfs(int u){
    for(auto&it:linker[u])
        if(!vis[it]){
            vis[it]=1;
            dfs(it);
        }
}


int main(){
    ios::sync_with_stdio(false);
    int t;
    cin>>t;
    while(t--){
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=100024;++i)
            linker[i].clear();
        int n,m,k;
        cin>>n>>m>>k;
        for(int i=1;i<=m;++i){
            int x,y;
            cin>>x>>y;
            linker[x].push_back(y);
        }
        for(int i=1;i<=k;++i){
            int s;
            cin>>s;
            vis[s]=1;
            dfs(s);
        }
        int ans=0;
        for(int i=1;i<=n;++i)
            if(vis[i])
                ans++;
        cout<<ans<<endl;
    }
}
```

### 注意事项：

十年 OI 一场空，多组数据不清空。

这道题只有 $2\text s$ 可以用比较快的读入方式。

## 总结

今天收获蛮多的：图。

图是一种比较重要的数据结构，希望大家好好学习！

推荐题目：<https://www.luogu.com.cn/problem/P5318>

~~同学们，再见！~~

---

## 作者：zzhbpyy (赞：1)

### [原题传送门](https://www.luogu.com.cn/problem/UVA11518)

## 思路

将骨牌视为一个有向图的点，根据输入信息建图。将每个被推倒的点作为起始点进行 dfs。每访问到一个没访问过的点就将答案加一。

## 完整代码

```c++
#include<bits/stdc++.h>
using namespace std;
struct Edge{
	int u,v,nxt;
}a[10005];
int n,m,l,t,ct,vis[10005],head[10005],ans;
inline void add(int u,int v){
	a[++ct]={u,v,head[u]};
	head[u]=ct;
}
void dfs(int u){
	if(vis[u])return;
	vis[u]=true;ans++;
	for(int i=head[u];i;i=a[i].nxt){
		int v=a[i].v;
		if(vis[v])continue;
		dfs(v);
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(nullptr),cout.tie(nullptr);
	cin>>t;
	while(t--){
		ans=0,ct=0;
		memset(head,0,sizeof head);
		memset(vis,0,sizeof vis);
		cin>>n>>m>>l;
		for(int i=1,u,v;i<=m;i++){
			cin>>u>>v;
			add(u,v);
		}
		for(int i=1,j;i<=l;i++){
			cin>>j;
			dfs(j);
		}
		cout<<ans<<'\n';
	}
}
```

---

## 作者：封禁用户 (赞：1)

可以从每一个被人工推倒的骨牌为起点 $\text{dfs}$，先把起点打上标记，如果它的儿子节点没有被标记过，就用这个点继续 $\text{dfs}$。最后输出被标记过的点数即可。

```cpp
void dfs(int x){
	vis[x]=1;
	for(auto i:G[x]){
		if(!vis[i]){
			dfs(i);
		}
	}
	return ;
}
```

---

## 作者：jess1ca1o0g3 (赞：0)

[Portal(UVa)](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=27&page=show_problem&problem=2513)

[Portal(Luogu)](https://www.luogu.com.cn/problem/UVA11518)

## 思路

这是一道简单的图问题。

非常典型，用邻接表建图，从每一个被人工推倒的骨牌处 dfs。

由于被搜过的骨牌会被打上标记，最后统计标记的个数。

多测一定要清空。

## Code

```cpp
#include<cstring>
#include<iostream>
#include<vector>
using namespace std;
bool vis[10005];
vector <int> g[10005];
int t,n,m,k,u,v,r,ans;
void dfs(int u){
    vis[u]=1;
    for(auto i:g[u]) if(!vis[i]) dfs(i);
}
signed main(){
    cin>>t;
    while(t--){
        ans=0;
        memset(vis,0,sizeof vis);
        memset(g,0,sizeof g);
        cin>>n>>m>>k;
        for(int i=1;i<=m;i++){
            cin>>u>>v;
            g[u].push_back(v);
        }
        for(int i=1;i<=k;i++){
            cin>>r;
            dfs(r);
        }
        for(int i=1;i<=n;i++) if(vis[i]) ans++;
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：Katz (赞：0)

### 题意：

有 $n$ 个点，$m$ 条单向边，和 $l$ 个起始点。

问从所有的起始点出发总共能到达多少个不同的点。
***

### 题解：
dfs 模板题。

本题解使用了非常板子的链式前向星来存图，可以参考。

唯一要注意的就是多测清空。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,l,x,y,ans;
int head[10010],to[10010],nxt[10010],edgecnt;
void add(int u,int v)
{
	to[++edgecnt]=v;
	nxt[edgecnt]=head[u];
	head[u]=edgecnt;
}
bool vis[10010];
void dfs(int u)
{
	if(vis[u]==false) ans++;
	vis[u]=true;
	for(int i=head[u];i;i=nxt[i])
	{
		if(vis[to[i]]==true) continue;
		dfs(to[i]);
	}
}
void solve()
{
	edgecnt=ans=0;
	memset(head,0,sizeof(head));
	memset(vis,false,sizeof(vis));
	cin>>n>>m>>l;
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y;
		add(x,y);
	}
	while(l--) cin>>x,dfs(x);
	cout<<ans<<endl;
}
int main()
{
	int T;
	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：zhouzihang1 (赞：0)

# UVA11518 题解

[题目传送门](https://www.luogu.com.cn/problem/UVA11518)

[翻译](https://www.luogu.com.cn/paste/dt4jbrx5)

感谢 @[wwwidk1234](https://www.luogu.com.cn/user/728483) 提供翻译

upd 2023-11-09 修改了一些笔误。

## 思路

这道题是 dfs 的模版题，思路简单，代码简单易懂。

对于每一个节点 $w$，我们使用邻接表的形式存储它可以到达的点。

利用自定义函数的递归实现遍历所有其可以到达的节点。

一些小细节看代码就可以了。

## AC Code

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int N=10005;
int n,m,l;
int u,v;
int w;
bool vis[N];
vector<int> vc[N];
void dfs(int step)//step表示当前搜到了哪个节点 
{
	vis[step]=1;
	for(auto it:vc[step])//C++11的新特性，意思是定义一个变量it，it是vc[step]的每一个值，等同于下 
		if(!vis[it])
			dfs(it);
/*
	int it;
	for(int i=0;i<vc[step].size();i++)
	{
		it=vc[step][i];
		if(!vis[it])
			dfs(it);
	}
*/
}
int main()
{
	int T,ans;
	scanf("%d",&T);
	//cin>>T;
	while(T--)
	{
		ans=0;
		memset(vis,0,sizeof(vis));
		memset(vc,0,sizeof(vc));
		//初始化，防止出现答案错误的情况 
		scanf("%d%d%d",&n,&m,&l);
		//cin>>n>>m>>l;
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d",&u,&v);
			//cin>>u>>v;
			vc[u].push_back(v);
		}
		for(int i=1;i<=l;i++)
		{
			scanf("%d",&w);
			//cin>>w;
			dfs(w);
		}
		for(int i=1;i<=n;i++)
			if(vis[i])
				ans++;
		printf("%d\n",ans);
		//cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：vocaloid (赞：0)

题意：给出一张有向图和若干个出发点，从出发点一直走，问图中有多少个点被遍历

`SB`题，无脑$Dfs$或者$Bfs$即可

见代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt,fst[10005],nxt[100005],to[100005];
int n,m,K;
bool vis[10005];
void AddEdge(int u,int v)
{
    to[++cnt]=v;
    nxt[cnt]=fst[u];
    fst[u]=cnt;
}
void Dfs(int u)
{
    vis[u]=1;
    for(int i=fst[u];i;i=nxt[i])
    {
        int v=to[i];
        if(!vis[v]) Dfs(v);
    }
}
int main()
{
    int Times;
    scanf("%d",&Times);
    while(Times--)
    {
        cnt=0;
        memset(fst,0,sizeof(fst));
        memset(vis,0,sizeof(vis));
        scanf("%d %d %d",&n,&m,&K);
        for(int i=1;i<=m;i++)
        {
            int x,y;
            scanf("%d %d",&x,&y);
            AddEdge(x,y);
        }
        for(int i=1;i<=K;i++)
        {
            int x;
            scanf("%d",&x);
            Dfs(x);
        }
        int ans=0;
        for(int i=1;i<=n;i++) if(vis[i]) ans++;
        printf("%d\n",ans);
    }
    return 0;
}
```

---

