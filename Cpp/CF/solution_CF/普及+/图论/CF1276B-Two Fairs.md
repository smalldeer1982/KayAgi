# Two Fairs

## 题目描述

There are $ n $ cities in Berland and some pairs of them are connected by two-way roads. It is guaranteed that you can pass from any city to any other, moving along the roads. Cities are numerated from $ 1 $ to $ n $ .

Two fairs are currently taking place in Berland — they are held in two different cities $ a $ and $ b $ ( $ 1 \le a, b \le n $ ; $ a \ne b $ ).

Find the number of pairs of cities $ x $ and $ y $ ( $ x \ne a, x \ne b, y \ne a, y \ne b $ ) such that if you go from $ x $ to $ y $ you will have to go through both fairs (the order of visits doesn't matter). Formally, you need to find the number of pairs of cities $ x,y $ such that any path from $ x $ to $ y $ goes through $ a $ and $ b $ (in any order).

Print the required number of pairs. The order of two cities in a pair does not matter, that is, the pairs $ (x,y) $ and $ (y,x) $ must be taken into account only once.

## 样例 #1

### 输入

```
3
7 7 3 5
1 2
2 3
3 4
4 5
5 6
6 7
7 5
4 5 2 3
1 2
2 3
3 4
4 1
4 2
4 3 2 1
1 2
2 3
4 1
```

### 输出

```
4
0
1
```

# 题解

## 作者：Orange_qwq (赞：16)

# 前言

[题目链接](https://www.luogu.com.cn/problem/CF1276B)


这里提供搜索（包括 dfs、bfs）做法。

此题解使用 邻接表 存图。

# 题意简述

给定 $n$ 个节点、$m$ 条边的**无向联通图**，以及两个点 $a,b$，求有多少对 $(u,v)$ 的路径**一定会经过** $a$ 和 $b$。

# 思路分析

## Step One

我们先给一个图。

![](https://cdn.luogu.com.cn/upload/image_hosting/eac7m6ud.png)

由图可知有 $(1,8),(1,9),(1,10),(2,8),(2,9),(2,10),(3,8),(3,9),(3,10)$ 这几对点满足题意要求。

仔细一看，可以发现 $a$ 与 $b$ **之间**的节点所通向的路径，无论是通向 $a$ 的左边，还是通向 $b$ 的右边，都不会包含 $a$ 或 $b$。

假设以节点序号较小为起点，较大为终点，我们可以得到：以 $a$ 左边的节点为起点，以 $b$ 右边的节点为终点，所构成的路径一定包含 $a$ 与 $b$。

![](https://cdn.luogu.com.cn/upload/image_hosting/n5oedz2b.png)

显然，一个节点把图分为两边，那么**图的左边除了经过该节点，没有可以不经过该节点而到达图的右边的路径。**

也就是，这个节点无可避免地经过 $a$ 和 $b$，无法绕路。

而最后 $(u,v)$ 的数量，就是 $a$ 左边的节点数量 $\times$ $b$ 右边的节点数量。（乘法原理）

------------

## Step Two

考虑搜索。

我们先假定起点为 $a$，终点为 $b$。

从 $a$ 出发开始搜，到 $b$ 为止，没有搜到的点就是 $b$ 右边的点。（参见下图）

![](https://cdn.luogu.com.cn/upload/image_hosting/b7f34kmt.png)

黄线为以 $a$ 为起点会搜到的路径。

只要给搜到的点打上标记，就可以知道 $b$ 右边点的数量。

同理，我们以 $b$ 为起点，也可以搜出 $a$ 左边的点。

两边的答案相乘，就可以得到题目的答案。

--------------

## Step Three

问题来到了如何实现。

+ 设一个记录访问的数组 $fl$。

+ 给终点（$a$ 或 $b$）先打上标记，搜到那里时就停。

+ 只要碰到没有搜过的，就继续搜下去。因为终点已经打上标记的，而且是联通图，所以没搜到的点就一定是 $a$ 左边或 $b$ 右边。

有了思路，我们就很容易写出 bfs、dfs 两种做法。

# $\texttt{AC CODE}$


为了同时给出 bfs、dfs 两种做法的程序，以下代码是以 bfs 搜 $b$ 右边的点，以 dfs 搜 $a$ 左边的点。

这里给出的做法，dfs 搜 $a$ 左边的答案，bfs 是搜 $b$ 右边的答案。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
const int M = 1e6 + 10;  // 因为 m 达到 5e5，而且是无向图，需要建两条边，所以应该开双倍
int h[M], cnt, n, m, ne[M], e[M], q[M], a, b;
bool fl[M];
long long s1, s2;

inline void add(int u, int v) { // 建边
	++cnt;
	e[cnt] = v;
	ne[cnt] = h[u];
	h[u] = cnt;
	++cnt;
	e[cnt] = u;
	ne[cnt] = h[v];
	h[v] = cnt;
}

void bfs(int s) {
	int l = 0, r = 1;
	q[r] = s;    // 起点入队
	fl[s] = fl[b] = 1; //起点和终点打标记
	while (l < r) { // 手写队列：如果队列不为空
		++l;
		int tmp = q[l];
		for (int k = h[tmp]; k; k = ne[k]) {
			int ch = e[k];
			if (!fl[ch]) fl[ch] = 1, q[++r] = ch; // 塞进队列并打上标记
		} 
	}
}

void dfs(int x) {
	for (int k = h[x]; k; k = ne[k]) {
		int ch = e[k];
		if (!fl[ch]) fl[ch] = 1, dfs(ch);
        // 只要没有访问到的，打上标记，继续 dfs
	}
}

void init(void) { // 初始化
	cnt = 0;
	for (int i = 1; i <= n; ++i) h[i] = 0;
	for (int i = 1; i <= n; ++i) fl[i] = 0;
	s1 = s2 = 0;
}

void run(void) {
	scanf("%d%d%d%d", &n, &m, &a, &b);
	init();
	for (int i = 1, u, v; i <= m; ++i) scanf("%d%d", &u, &v), add(u, v);
	bfs(a); 
	for (int i = 1; i <= n; ++i) if (!fl[i]) ++s1;  // 统计
	memset(fl, 0, sizeof fl); 
   // 这里只需要初始化 fl 数组
	fl[a] = 1; // 不要忘记给终点打标记
	dfs(b);
	for (int i = 1; i <= n; ++i) if (!fl[i]) ++s2;
	printf("%lld\n", s1 * s2);
}

int main() {
	int t;
	cin >> t;
	while (t--) run();
	return 0;
} 
```


---

## 作者：EdenSky (赞：6)

# [CF1276B Two Fairs](https://www.luogu.com.cn/problem/CF1276B)
- [或许更好的阅读体验](https://www.cnblogs.com/wanguan/p/17740806.html)

## 正文

这是样例 1 第 1 组数据的图。

![](https://cdn.luogu.com.cn/upload/image_hosting/qyyrtwlz.png)

让我们观察一下，路径 1->6、1->7、2->6、2->7 是可行的，所以答案为 4。

上述路径中好像点 4 没有贡献？

再看看样例 1 第 2 组数据的图。

![](https://cdn.luogu.com.cn/upload/image_hosting/mgqnzuls.png)

发现点 1 和点 4 相互之间存在其他路径，无需经过点 $a$ 和点 $b$。

综上，我们可以知道：在 $a$ 和 $b$ 之间的任意路径上的点是不作贡献的。

可以看作 $a$ 和 $b$ 之间的路径是一个桥梁，桥梁的两边的点才是做出贡献的，我们将第 1 组数据的图改变一下，可以很清楚地理解。

![](https://cdn.luogu.com.cn/upload/image_hosting/wmb5g6nr.png)

因此，我们只要找 $a$、$b$ 隔开的点的数量，再将两边数量相乘（乘法原理）即可。

接下来，只要找隔开的点的数量就可以。

考虑 DFS，对 $a$ 和 $b$ 分别 DFS。假设从 $a$ 开始搜，若有一分支搜到 $b$，则将该分支贡献清零，因为该分支上的点在 $a$、$b$ 之间，没有贡献（既与 $a$ 相连，也与 $b$ 相连）。$b$ 点同理。

那就可以写代码力。

```cpp
#define by_wanguan
#include<iostream>
#include<vector>
#include<cstring>
#define int long long
const int N=2e5+7;
using namespace std;
int T,n,m,a,b;
vector<int> g[N];
bool vis[N],vis_[N];
inline int dfsb(int x){
  vis[x]=1;
  int ret=1;
  if(x==a) {vis[x]=0; return 0;}
  for(int &i: g[x]){
    if(vis[i]) continue;
    int s=dfsb(i);
    if(s==0&&x!=b) {vis[x]=0; return 0;}
    ret+=s;
  }
  return ret;
}
inline int dfsa(int x){
  vis_[x]=1;
  int ret=1;
  if(x==b) {vis_[x]=0; return 0;}
  for(int &i: g[x]){
    if(vis_[i]) continue;
    int s=dfsa(i);
    if(s==0&&x!=a) {vis_[x]=0; return 0;}
    ret+=s;
  }
  return ret;
}
signed main(){
  ios::sync_with_stdio(false),cin.tie(0);
  cin>>T;
  while(T--){
    cin>>n>>m>>a>>b;
    memset(vis,0,sizeof vis);
    memset(vis_,0,sizeof vis_);
    for(int i=1;i<=n;i++) g[i].clear();
    for(int i=1,a,b;i<=m;i++)
      cin>>a>>b,
      g[a].emplace_back(b),
      g[b].emplace_back(a);
    int aa=dfsa(a)-1,bb=dfsb(b)-1;
    cout<<aa*bb<<'\n';
  }
}
```

[提交记录](https://www.luogu.com.cn/record/126802625)。

---

## 作者：formkiller (赞：4)


### Problem ：


给出 $N$ 个点 ， $M$ 条边 ， 以及两个点  $s , t$  

求 满足点对 $ (a,b) $ ，使得 $a$ 到 $b$ 的路径一定经过 $s$ 和 $t$ 的点对个数


------------

### Solution ：

我们把图放在水平位置上，把点 $s$ 放在左边，把 $t$ 放在右边

显然的，如果我们把  $s , t$  从图中去掉，那么原图会被分割成若干个子图，而原来的点对 $(a,b)$ 一定无法从 $a$ 走到 $b$ 

如果存在满足原条件的点对 $(a,b)$ ，那么原图一定会分为三个子图，分别为： $s$ 左边的点，$s$ 到 $t$ 中间的点， $t$ 右边的点

于是我们要求的满足点对 $(a,b)$ 的个数实质上就是从 $s$ 左边的点选一个出来，然后与 $t$ 右边的点进行配对

所以我们从 $s$ 开始进行搜索，碰到 $t$ 就停下，标记到达的每一个点，这样一来这些点就是 $s$ 左边的点和 $s$ 到 $t$ 中间的点

所以我们从 $t$ 开始进行搜索，碰到 $s$ 就停下，标记到达的每一个点，这样一来这些点就是 $t$ 右边的点和 $s$ 到 $t$ 中间的点

然后我们再把两次搜索都经过的点都去掉，他们就是 $s$ 到 $t$ 中间的点

于是我们就求出了 $s$ 左边的点和 $t$ 右边的点，把这两个子图的大小相乘就是答案


~~我Div 2上分就靠签了到然后开了它，所以来写一发题解~~

赛场代码略丑 ~~但我懒得改~~

### Code ：

```cpp
//good luck
# include <iostream>
# include <cstdio>
# include <cmath>
# include <cstdlib>
# include <cstring>
# include <string>
# include <algorithm>

#define is(a) (a>='0'&&a<='9')

using namespace std;

const int maxn=1e6+5;

int T,N,M,s,t,v1[maxn],v2[maxn];
int tot,hd[maxn],nt[maxn],ver[maxn];

inline void read(int &x)
{
  x=0;bool f=0;char ch=getchar();
  for (;!is(ch);ch=getchar()) f|=ch=='-';
  for (;is(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
  x=f?-x:x;
}

inline void addedge(int x,int y)
{
	++tot; ver[tot] = y; nt[tot] = hd[x]; hd[x] = tot;
}

inline void Dfs1(int x)
{
	v1[x] = 1;
	for (int i = hd[x]; i ; i = nt[i])
	{
		int y = ver[i];
		if (v1[y]||y==t) continue;
		Dfs1(y);
	}
}

inline void Dfs2(int x)
{
	v2[x] = 1;
	for (int i = hd[x]; i ; i = nt[i])
	{
		int y = ver[i];
		if (v2[y]||y==s) continue;
		Dfs2(y);
	}
}

int main()
{
//	freopen("a.in","r",stdin);
	read(T);
	while (T--)
	{
		read(N); read(M); read(s); read(t);
		for (int i = 1; i <= M; ++i)
		{
			int x,y;
			read(x); read(y);
			addedge(x,y);
			addedge(y,x);
		}
		Dfs1(s);
		Dfs2(t);
		long long A=0,B=0;
		for (int i = 1; i <= N; ++i)
		{
			if (v1[i]&&!v2[i]&&i!=s) ++A;
			if (!v1[i]&&v2[i]&&i!=t) ++B;
			v1[i]=v2[i]=0;
		}
		printf("%lld\n",A*B);
		for (int i = 1; i <= tot; ++i) hd[i]=nt[i]=ver[i]=0;
		tot=0;
	}
    return 0;
}

```


---

## 作者：yangmuguang (赞：1)

### 题意

一个 $n$ 个节点，$m$ 条边的连通无向图，请问有多少对节点 $(u,v)$ 满足 $u$ 到 $v$ 的路径必定经过 $a$ 和 $b$ 节点。

$4\le n\le 2\times 10^5$，$n-1\le m\le 5\times 10^5$，$a$，$b$，$u$，$v$ 互不相同。

### 思路

先来个样例。

![](https://cdn.luogu.com.cn/upload/image_hosting/eyl63pfs.png)

显而易见，答案为 $16$：从任何一个黄色节点到任意一个蓝色节点都是一个符合条件的路径。

可以发现，答案为所有 A“左边”的点（所有去 B 必须经过 A 的点）乘上所有 B“右边”的点（所有去 A 必须经过 B 的点）。

所以，我们可以 DFS 求出从 A 不经过 B 可以达到的点（B 左边的点）和 B 不经过 A 可以到达的点（A 右边的点），从而求出答案。

时间复杂度：$O(n)$。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define faster ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(0)
ll t,n,m,a,b;
bool ia[200005],ib[200005];
vector<ll>con[200005];
void dfsa(ll x,ll fa)
{
	ia[x]=1;
	if (x==a)return;
	for (ll i=0;i<con[x].size();i++)
	{
		if (con[x][i]!=fa&&!ia[con[x][i]])
		{
			dfsa(con[x][i],x);
		}
	}
}
void dfsb(ll x,ll fa)
{
	ib[x]=1;
	if (x==b)return;
	for (ll i=0;i<con[x].size();i++)
	{
		if (con[x][i]!=fa&&!ib[con[x][i]])
		{
			dfsb(con[x][i],x);
		}
	}
}
int main()
{
	faster;
	cin>>t;
	while (t--)
	{
		cin>>n>>m>>a>>b;
		for (ll i=1;i<=n;i++)
		{
			con[i].clear();
		}
		for (ll i=1;i<=m;i++)
		{
			ll u,v;
			cin>>u>>v;
			con[u].pb(v);
			con[v].pb(u);
		}
		memset(ia,0,sizeof ia);
		memset(ib,0,sizeof ib);
		dfsa(b,-1);
		dfsb(a,-1);
		ll ac=0,bc=0;
		for (ll i=1;i<=n;i++)
		{
			if (ia[i]&&!ib[i])ac++;
			if (ib[i]&&!ia[i])bc++;
		}
		cout<<ac*bc<<"\n";
	}
	return 0;
}
```

---

## 作者：gaomingyang101011 (赞：1)

## 思路：

这道题我们需要我们找到必须经过 $a$ 点和 $b$ 点才能到达的点的对数，那我们就可以将 $a$ 点能到的点和 $b$ 点能到的点分别标记，同时 $a$ 点搜到 $b$ 点就停止，$b$ 点同样如此，然后我们就知道被 $a$ 点 $b$ 点同时标记的点不可能出现在我们要求的对数中，之被 $a$ 点标记的点都必须经过 $a$ 点和 $b$ 点才能到达只被 $b$ 点标记的点，那我们就将只被 $a$ 点标记的点数与只被 $b$ 点标记的点数相乘就是最终的组数了。

## 代码：


```cpp
#include<iostream>
#include<cstring>
#include<vector>
#define ll long long
using namespace std;
const int N=2*1e5+5;
ll t;
ll n,m,a,b; 
vector<ll> k[N];
ll u,v; 
bool visa[N],visb[N];
void dfsa(int x){
	if(x==b) return;
	for(int i=0;i<k[x].size();i++){
		if(visa[k[x][i]]==0){
			visa[k[x][i]]=1;
			dfsa(k[x][i]);
		}
	}
}
void dfsb(int x){
	if(x==a) return;
	for(int i=0;i<k[x].size();i++){
		if(visb[k[x][i]]==0){
			visb[k[x][i]]=1;
			dfsb(k[x][i]);
		}
	}
}
int main(){
    cin>>t;
    while(t--){
    	cin>>n>>m>>a>>b;
		memset(visa,0,sizeof(visa));
		memset(visb,0,sizeof(visb));
		for(int i=1;i<=n;i++) k[i].clear();
		for(int i=1;i<=m;i++){
			cin>>u>>v;
			k[u].push_back(v);
			k[v].push_back(u);
		}
		dfsa(a);
		dfsb(b);
		ll ansa=0,ansb=0;
		for(int i=1;i<=n;i++){
			if(visa[i]==1&&visb[i]==0) ansa++;
			if(visb[i]==1&&visa[i]==0) ansb++;
		}
		cout<<ansa*ansb<<endl;
	}
    return 0;
}
```

---

## 作者：q_hacker_p (赞：1)

# 题目解析
先随便举个例子![](https://cdn.luogu.com.cn/upload/image_hosting/8bxu45wk.png)
由此发现，只能从一个方框的一个点走到另一个方框的一个的点。根据乘法原理，路径数等于两个方框的点的个数相乘。

## 问题 1：求出靠近 $a$ 的方框中点的个数
观察图片过后可以发现，方框中的点只能经过 $a$ 到达。所以就可以从 $b$ 开始做 DFS（以 DFS 举例）只要到 $a$ 标记 $a$ 后就返回。最后没有走到的就是方框中的个数。

函数：
```cpp

void dfs_Stop_At_Point_A(ll x)
{
	vis_Stop_At_Point_A[x] = 1;
	if(x == a)//到a停止
	{
		return ;
	}
	for(int i = 0; i < Adjacency_List[x].size(); i++)//遍历
	{
		if(!vis_Whether_To_Walk_Through[Adjacency_List[x][i]])//判断是否走过
		{
			vis_Whether_To_Walk_Through[Adjacency_List[x][i]] = 1;//标记为1即走过
			dfs_Stop_At_Point_A(Adjacency_List[x][i]);//继续深搜
		}
	}
}
```

## 问题 2：求出靠近 $b$ 的方框中点的个数
同问题一，只是从 $a$ 开始 DFS，到 $b$ 结束。
函数：
```cpp

void dfs_Stop_At_Point_B(ll x)
{
	vis_Stop_At_Point_B[x] = 1;
	if(x == b)//到b停止
	{
		return ;
	}
	for(int i = 0; i < Adjacency_List[x].size(); i++)//遍历
	{
		if(!vis_Whether_To_Walk_Through[Adjacency_List[x][i]])//判断是否走过
		{
			vis_Whether_To_Walk_Through[Adjacency_List[x][i]] = 1;//标记为1即走过
			dfs_Stop_At_Point_B(Adjacency_List[x][i]);//继续深搜
		}
	}
}
```

## 问题 3：统计
把标记数组遍历一遍，数 $0$ 的个数。
代码：
```cpp

	ll cnt1 = 0, cnt2 = 0;
	for(int i = 1; i <= n; i++)
	{
		if(!vis_Stop_At_Point_B[i])//数0的个数
			cnt1++;
	}
	for(int i = 1; i <= n; i++)
	{
		if(!vis_Stop_At_Point_A[i])//数0的个数
			cnt2++;
	}
```

## 问题 4：计算答案
直接相乘。
```cpp
cout << cnt1 * cnt2;//用乘法原理算结果
```
## 完整 AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, m, a, b;
ll u, v;
ll T;
vector <ll> Adjacency_List[200002];//邻接表
bool vis_Stop_At_Point_B[200002];//标记数组
bool vis_Stop_At_Point_A[200002];
bool vis_Whether_To_Walk_Through[200002];
void dfs_Stop_At_Point_B(ll x)
{
	vis_Stop_At_Point_B[x] = 1;
	if(x == b)//到b停止
	{
		return ;
	}
	for(int i = 0; i < Adjacency_List[x].size(); i++)//遍历
	{
		if(!vis_Whether_To_Walk_Through[Adjacency_List[x][i]])//判断是否走过
		{
			vis_Whether_To_Walk_Through[Adjacency_List[x][i]] = 1;//标记为1即走过
			dfs_Stop_At_Point_B(Adjacency_List[x][i]);//继续深搜
		}
	}
}
void dfs_Stop_At_Point_A(ll x)
{
	vis_Stop_At_Point_A[x] = 1;
	if(x == a)//到a停止
	{
		return ;
	}
	for(int i = 0; i < Adjacency_List[x].size(); i++)//遍历
	{
		if(!vis_Whether_To_Walk_Through[Adjacency_List[x][i]])//判断是否走过
		{
			vis_Whether_To_Walk_Through[Adjacency_List[x][i]] = 1;//标记为1即走过
			dfs_Stop_At_Point_A(Adjacency_List[x][i]);//继续深搜
		}
	}
}
void Run()
{
	cin >> n >> m >> a >> b;
	for(int i = 1; i <= m; i++)
	{
		cin >> u >> v;
		Adjacency_List[u].push_back(v);//放入邻接表
		Adjacency_List[v].push_back(u);
	}
	for(int i = 1; i <= n; i++)
		sort(Adjacency_List[i].begin(), Adjacency_List[i].end());//排序
	vis_Whether_To_Walk_Through[a] = a;//标记
	dfs_Stop_At_Point_B(a);
	memset(vis_Whether_To_Walk_Through, 0, sizeof(vis_Whether_To_Walk_Through));//还原
	vis_Whether_To_Walk_Through[b] = b;//标记
	dfs_Stop_At_Point_A(b);
	ll cnt1 = 0, cnt2 = 0;
	for(int i = 1; i <= n; i++)
	{
		if(!vis_Stop_At_Point_B[i])//数0的个数
			cnt1++;
	}
	for(int i = 1; i <= n; i++)
	{
		if(!vis_Stop_At_Point_A[i])//数0的个数
			cnt2++;
	}
	cout << cnt1 * cnt2 << "\n";//用乘法原理算结果
}
int main()
{
	cin >> T;
	while(T--)
	{
		Run();
		memset(vis_Whether_To_Walk_Through, 0, sizeof(vis_Whether_To_Walk_Through));//初始化
		memset(vis_Stop_At_Point_A, 0, sizeof(vis_Stop_At_Point_A));
		memset(vis_Stop_At_Point_B, 0, sizeof(vis_Stop_At_Point_B));
		for(int i = 1; i <= n; i++)
			Adjacency_List[i].clear();
		
	}
	return 0;
}
```

---

## 作者：OIer_ACMer (赞：1)

~~小牛牛要回家~~。

------------
注：本题思路较为简单，所以作者不会过多赘述证明以及原理，望周知！

------------
## 大致思路：
这道题思路比较简单，我大致说一下：

这个题目真的想过来就只是一个 dfs 遍历的问题。**两个点必须都是割点才可以有这样的数对**。我们先将一个点 $a$ 设置为割点，从另一个点 $b$ 出发，计算不能到达的点数 $cnt1$。然后将 $b$ 设置为割点，从 $a$ 出发，计算不能到达的点数 $cnt2$。相乘后就是答案了。两次 dfs 计算的是分别与 $a$，$b$ 两点相连的点数。

那么至于为什么答案是 $cnt1$ 和 $cnt2$ 的结果相乘呢？根据乘法原理我们可以知道，想要求出满足题目条件的点数，就必须**要满足这几个点要将 $a$ 和 $b$ 看做是两个割点，根据割点的性质我们可以知道，如果割点没了，那么路径就不联通，所以我们需要统计，在不经过 $a$ 的情况下能到达 $b$ 的点和不经过 $b$ 的情况下能到达 $a$ 的点的数量 $cnt1$ 和 $cnt2$**。同时根据乘法原理我们可以知道，最终的方案数就是两者乘积（这个我就不多解释了，实在不知道的可以上网搜搜啥是乘法原理）。

算了，我也说一下代码实现原理吧。首先，题目说路径是无向图，所以我们在用 vector 存边时要两个方向都存（这句话我在之前已经重复 $n$ 次了）。

接着，我们先跑一遍 $a$ 点和 $b$ 点之间的 dfs 路径，每次在满足**第一次遍历**且**路径不是往回走**的情况下将 $g_{u,i}$ 和 $x$ 节点再次放入函数 $\operatorname{dfs}$ 中继续递归搜索。因为如果你找重复了就会陷入死循环（这我就不多说了）。通过这一次遍历，我们可以找出不能与 $a$ 点互相连通的点的个数有多少。

同理，我们再用 dfs 计算与 $b$ 点相连的点数，用 $cnt2$ 储存不能和 $b$ 相连的点的个数。

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const int maxx = 2e5 + 100;
vector<int> g[maxx];
int vis[maxx];
int n, m, a, b;
inline void pre()
{
    for (int i = 1; i <= n; i++)
    {
        g[i].clear(), vis[i] = 0;
    }
}
inline void dfs(int u, int x)
{
    vis[u] = 1;
    for (int i = 0; i < g[u].size(); i++)
    {
        if (vis[g[u][i]] || g[u][i] == x)
        {
            continue;
        }
        dfs(g[u][i], x);
    }
}
int main()
{
    int t;
    t = read();
    while (t--)
    {
        int x, y;
        pre();
        n = read();
        m = read();
        a = read();
        b = read();
        for (int i = 1; i <= m; i++)
        {
            x = read();
            y = read();
            g[x].push_back(y);
            g[y].push_back(x);
        }
        dfs(a, b);
        int cnt1 = 0, cnt2 = 0;
        for (int i = 1; i <= n; i++)
        {
            if (vis[i] == 0)
            {
                cnt1++;
            }
        }
        for (int i = 1; i <= n; i++)
        {
            vis[i] = 0;
        }
        dfs(b, a);
        cnt1 -= 1;
        cnt2 -= 1;
        for (int i = 1; i <= n; i++)
        {
            if (vis[i] == 0)
            {
                cnt2++;
            }
        }
        printf("%lld\n", (ll)cnt1 * (ll)cnt2);
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/123022109)

---

## 作者：wusixuan (赞：0)

只有 $a$ 左边的点到 $b$ 右边的点才可行，因为 $a$ 左边的点一定要经过 $a$ 和 $b$ 才可以到 $b$ 右边的点，$b$ 右边的点也同样。所以根据乘法原理得知答案为 $a$ 左边的点的数量 $\times$ $b$ 右边的点的数量。

我们可以从 $b$ 一直搜到 $a$，一旦搜到 $a$ 就不搜了，一定会而且只会搜到除 $a$ 左边的点外其他所有的点。于是可以做一遍搜索，然后再算出来 $a$ 左边的点的个数。$b$ 右边的点的个数就是从 $a$ 到 $b$ 搜，一样方法算出来。

两种结果算出来一乘就是答案。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10;
vector<int> v[N];
int n, m, a, b;
bool vis[N];
int cnt = 0;

void dfs(int u, int to) {
	vis[u] = 1;
	cnt++;
	if (u == to)
		return ;
	for (auto i : v[u]) {
		if (vis[i])
			continue;
		dfs(i, to);
	}
}

signed main() {
	ios::sync_with_stdio(0);
	int t;
	cin >> t;
	while (t--) {
		cin >> n >> m >> a >> b;
		for (int i = 1; i <= n; i++)
			v[i].clear();//注意要初始化
		for (int i = 1; i <= m; i++) {
			int x, y;
			cin >> x >> y;
			v[x].push_back(y);
			v[y].push_back(x);
		}
		for (int i = 1; i <= n; i++)
			vis[i] = 0;
		cnt = 0, dfs(a, b);
		int ans = n - cnt;//算b右边的点
		for (int i = 1; i <= n; i++)
			vis[i] = 0;
		cnt = 0, dfs(b, a);
		ans *= (n - cnt);//乘上a左边的点
		cout << ans << endl;
	}
	return 0;
}
//码风丑陋，不喜勿喷
//复杂度是线性的，可以通过
```

---

## 作者：_Flame_ (赞：0)

## 思路

很巧妙的一道题。

如何使两点之间的路径一定经过给出的两个特殊点是解题的关键。

首先把题目给出的两个特殊点都从图中去掉，可以发现给出的图会被分成三个不同的点集，即 $a$ 与 $b$ 中间的点，$a$ 左边的点，$b$ 右边的点。

用样例的第一组数据为例，$3$ 号点与 $5$ 号点为特殊点，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ouptxer2.png)

其中 $4$ 号点属于 $a$ 与 $b$ 中间的点，$1$ 号点和 $2$ 号点属于 $a$ 左边的点，$6$ 号点与 $7$ 号点为 $b$ 右边的点。

然后我们可以发现当一个点对满足其中一个点属于 $a$ 左边，另外一个点属于 $b$ 右边时，这两点之间的路径一定经过 $a$ 与 $b$。

如图中 $1$ 号点到 $6$ 号点，$2$ 号点到 $7$ 号点：

![](https://cdn.luogu.com.cn/upload/image_hosting/ifj7dbwk.png)

接下来就是三个点集的求法问题，我们可以发现从 $a$ 开始进行 $\text{dfs}$，到 $b$ 停止，可以遍历到的点如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/16i5naxi.png)

可以发现正好是 $a$ 左边的点的点集加上 $a$ 与 $b$ 中间的点的点集。

所以我们只用从 $a$ 开始进行 $\text{dfs}$，到 $b$ 停止，把每个经过的点打上标记，再从 $b$ 开始进行 $\text{dfs}$，到 $a$ 停止，把每个经过的点打上标记，两种标记重合的地方为 $a$ 与 $b$ 中间的点的点集，其他分别为为另外两种，统计两种点的数量，乘法原理求出答案即可。

## Code

```cpp

#include<bits/stdc++.h>
#define int long long
#define _int __int128
#define y1 _
using namespace std;

static char buf[1000000],*p1=buf,*p2=buf;

inline int read(){
	char c=getchar();
	int res=0,f=1;
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res*f;
}

inline void write(int x){
	static char buf[20];
	static int len=-1;
	if(x<0){
		putchar('-');
		x=-x;
	}
	do{
		buf[++len]=x%10;
		x/=10;
	}
	while(x);
	while(len>=0){
		putchar(buf[len--]+48);
	}
}

const int maxn=501000;
const int maxm=110;
const int mod=50;
const int inf=420444186480114514;

int n,m;
int a,b;
int cnta,cntb;

int visa[maxn],visb[maxn];

int head[maxn],tot;
struct egde{
	int to,nxt;
}e[maxn<<1];

void add(int u,int v){
	e[++tot].to=v;
	e[tot].nxt=head[u];
	head[u]=tot;
}

void dfs1(int u,int ed){
	visa[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!visa[v]&&v!=ed){
			dfs1(v,ed);
		} 
	}
}

void dfs2(int u,int ed){
	visb[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!visb[v]&&v!=ed){
			dfs2(v,ed);
		} 
	}
}

void init(){
	for(int i=1;i<=n;i++){
		visa[i]=0;
		visb[i]=0;
	}
	for(int i=1;i<=tot;i++){
		e[i].nxt=0;
		e[i].to=0;
		head[i]=0;
	}
	tot=0;
	cnta=0;
	cntb=0;
}

void solve(){
	init();
	n=read(),m=read(),a=read(),b=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(u,v);
		add(v,u);
	}
	dfs1(a,b);
	dfs2(b,a);
	for(int i=1;i<=n;i++){
		if(i!=a){
			if(visa[i]&&!visb[i]){
				cnta++;
			}
		}
		if(i!=b){
			if(!visa[i]&&visb[i]){
				cntb++;
			}
		}
	}
	write(cnta*cntb);
	puts("");
	return ;
}

signed main(){
	int T=read();
	while(T--){
		solve();
	}
	return 0;
}



```

---

