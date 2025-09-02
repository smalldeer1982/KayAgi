# Kefa and Park

## 题目描述

Kefa decided to celebrate his first big salary by going to the restaurant.

He lives by an unusual park. The park is a rooted tree consisting of $ n $ vertices with the root at vertex $ 1 $ . Vertex $ 1 $ also contains Kefa's house. Unfortunaely for our hero, the park also contains cats. Kefa has already found out what are the vertices with cats in them.

The leaf vertices of the park contain restaurants. Kefa wants to choose a restaurant where he will go, but unfortunately he is very afraid of cats, so there is no way he will go to the restaurant if the path from the restaurant to his house contains more than $ m $ consecutive vertices with cats.

Your task is to help Kefa count the number of restaurants where he can go.

## 说明/提示

Let us remind you that a tree is a connected graph on $ n $ vertices and $ n-1 $ edge. A rooted tree is a tree with a special vertex called root. In a rooted tree among any two vertices connected by an edge, one vertex is a parent (the one closer to the root), and the other one is a child. A vertex is called a leaf, if it has no children.

Note to the first sample test: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF580C/3cc68e912c69745e5c96ffcfeb5680e415b9867a.png) The vertices containing cats are marked red. The restaurants are at vertices 2, 3, 4. Kefa can't go only to the restaurant located at vertex $ 2 $ .

Note to the second sample test: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF580C/3d11dcb54f6b1deed424e5699c584e06f67a1d2b.png) The restaurants are located at vertices 4, 5, 6, 7. Kefa can't go to restaurants 6, 7.

## 样例 #1

### 输入

```
4 1
1 1 0 0
1 2
1 3
1 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
7 1
1 0 1 1 0 0 0
1 2
1 3
2 4
2 5
3 6
3 7
```

### 输出

```
2
```

# 题解

## 作者：sukimo (赞：7)

一道搜索题，思路就是从根节点开始dfs找路径的时候统计。之前被卡过几次，后来找到了错误。对于每个dfs到的节点，维护$3$个参数：

$1$.当前节点编号

$2$.以当前节点结尾的连续点权为$1$的节点个数

$3$.从根节点走到当前节点的路径，最大连续点权为$1$的节点个数 

三个信息都比较好维护，其中参数$2$和$3$需要互相更新（见代码，只要理解了上面三个参数的意义，代码非常好理解）。如果在半路参数$3$就大于$m$了，可以直接剪掉。我采用的判断叶节点方法是记下每个点的连边数量，如果只连了一条边且不是根节点（第二个条件很重要！！，因为可以造出两点一边的特殊数据，这时根节点也只连了一条边），就是叶节点。

上代码：

```
#include<bits/stdc++.h>
using namespace std;
const int MX=100005;int m,tot,in[MX],vis[MX],fir[MX],val[MX];struct STR{int next,to;}edge[MX<<1];
void add(int u,int v,int cnt){edge[cnt].to=v;edge[cnt].next=fir[u];fir[u]=cnt;}
void dfs(int x,int now_cnt,int _max){
	if(_max>m)return;if(!(in[x]-1)&&x-1){tot++;return;}
	vis[x]=1;
	for(int i=fir[x];i;i=edge[i].next)
		if(!vis[edge[i].to]){
			int q=val[edge[i].to]?now_cnt+1:0;dfs(edge[i].to,q,max(_max,q));
		}
}
int main(){
	int n;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&val[i]);
	for(int i=1;i<=n-1;i++){int u,v;scanf("%d%d",&u,&v);add(u,v,i);add(v,u,i+n-1);in[u]++;in[v]++;}
	dfs(1,val[1],val[1]);printf("%d",tot);
	return 0;
}
```


---

## 作者：0xFF (赞：4)

#### 题目大意


------------
给定一个有 $n$ 个节点的有根树，每个节点的点权为 $0$ 或 $1$，求出从根节点出发到叶子节点的路径中有多少条路径满足路径上连续的点权为 $1$ 的节点个数不超过 $m$。

#### 思路分析


------------
从根节点开始 ```dfs``` 即可。

```dfs``` 记录当前搜到的节点，当前节点的父亲节点以及这条路径到当前节点的连续点权为 $1$ 的数量。

如果当前节点点权为 $0$ 搜索下一层，同时更新连续点权为 $1$ 的值更新为 $0$。

如果当前节点点权为 $1$ 则判断其连续点权为 $1$ 的节点个数是否 $\le m$，若满足条件继续搜索，否则返回即可。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define int long long
using namespace std;
const int N = 100050;
inline int read(){
	int x=0,f=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
	for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
	return x*f;
}
int n,m,a[N],ans;
int tot , head[N] , index[N];
struct node{
	int to,next;
}edge[N<<1];
void addedge(int u,int v){
	edge[++tot].to = v;
	edge[tot].next = head[u];
	head[u] = tot;
}
void dfs(int now,int fa,int cnt){
	if(index[now] == 1 && now != 1){
		if(cnt <= m) ans++;
		return;
	}
	for(int i=head[now];i;i=edge[i].next){
		int v = edge[i].to;
		if(v == fa) continue;
		if(!a[v]) dfs(v,now,0);
		else if(cnt < m) dfs(v,now,cnt+1);
	}
}
signed main(){
	n = read() , m = read();
	for(int i=1;i<=n;i++){
		a[i] = read(); 
	}
	for(int i=1;i<=n-1;i++){
		int u = read() , v = read();
		addedge(u,v); addedge(v,u);
		++index[v] , ++index[u];
	}
	dfs(1,0,a[1]);
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Z1qqurat (赞：3)

这是一道有意思的树形dp。

### 思路

老规矩，先来看看这道题的思路。

Part 1：如果没有 $m$ 的限制，怎么做？

如果我们把 $m$ 的限制去掉，就很简单了：

1.用数组 $dp[x]$ 表示以 $x$ 为根节点的子树有多少条连续点权为 $1$ 的路径。//```状态。```

2.那么状态转移：如果 $a[x]=1$ ，则继续往下面dp，否则清零。

Part 2：如何解决 $m$ 的限制？

那么我们用一个 $sum$ 记录目前路径上有多少个连续点权为 $1$ 的点，当 $sum>m$ 时，结束dp。

于是我们可以拿一个数 $dp$ 记录答案，如果 $x$ 不是根结点 $1$ 且 $x$ 为叶子结点，答案就多了一种。

### 代码

一些有关于实现的解释写在代码注释里面了。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#define ll long long
#define ri register int
using namespace std;
const int MAXN=100010;
int n,m,a[MAXN],u,v,dp;
vector <int> T[MAXN];

void dfs(int x,int fa,int sum){//由于是无根树，我们用fa记录父节点。
    if(sum>m)return ;//m的限制。
    if(x!=1&&T[x].size()==1)dp++;//记录答案。
    for(ri i=0;i<T[x].size();i++){
        int y=T[x][i];
        if(y==fa)continue;
        if(a[y]==1)dfs(y,x,sum+1);
        else dfs(y,x,0);//重点：式子部分。
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for(ri i=1;i<=n;i++)cin>>a[i];
    for(ri i=1;i<n;i++){
        cin>>u>>v;
        T[u].push_back(v);
        T[v].push_back(u);
    }
    dfs(1,0,a[1]);//sum由根结点是否点权为1决定。
    cout<<dp;
    return 0;
}
```

$End.$

---

## 作者：Utilokasteinn (赞：2)

## [Link](https://www.luogu.com.cn/problem/CF580C)

本题翻译似乎不太清楚，我做题的时候被误导了。翻译：

对于一棵 $n$ 个节点且以 $1$ 号节点为根的树，每个节点都有一个权值，是 $0$ 或 $1$。问从根节点到其叶子节点的路径中，有多少条**子路径**满足路径上最大连续点权为 $1$ 的节点个数不超过 $m$。（**必须经过叶子节点**）

只要读懂题，就容易发现可以直接 ```dfs```，不断更新最大连续点权为 $1$ 的个数，若满足答案就加 $1$，否则就清零。若当前路径上的最大连续点权为 $1$ 的节点个数超过 $m$ 便直接返回。

其余也没有什么需要注意的地方，代码实现也很简单。

时间复杂度：$O(n)$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int s=0;char c=getchar();
	for(;!isdigit(c);c=getchar());
	for(;isdigit(c);c=getchar())
		s=s*10+c-'0';
	return s;
}
int n,m,a[100005],ans;
int tot,head[100005],in[100005];
struct edge{
	int to,nxt;
}e[200005];
void add(int u,int v)
{
	e[++tot].to=v;
	e[tot].nxt=head[u];
	head[u]=tot;
	in[v]++;
}
void dfs(int u,int fa,int cnt)
{
	if(in[u]==1&&u!=1)
	{
		ans+=cnt<=m;
		return;
	}
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa)continue;
		if(!a[v])dfs(v,u,0);
		else if(cnt<m)dfs(v,u,cnt+1);
	}
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<n;i++)
	{
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	dfs(1,0,a[1]);
	printf("%d",ans);
	return 0;
}
```
谢谢观赏。

---

## 作者：Mine_King (赞：2)

这题我们可以根据题意直接把树分成几条链，明显这几条链是互不干扰的。那么接下来的问题就是如何求一条链上最长的连续的 $1$ 的数量。  
我们可以尝试用 dp 来做，设 $dp_i$ 表示前 $i$ 个数最大的连续的 $1$ 的数量，我们发现要转移的话还要记录一个 $v_i$ 表示以 $i$ 结尾的连续的 $1$ 的个数。然后就可以得出状态转移方程：$dp_i=max(dp_{i-1},v_i)$。而 $v_i$ 的转移方程就是 $v_i=(a_i==0?0:v_{i-1}+1)$（这里 $a_i$ 表示第 $i$ 个点的权值）。  

接着把他扩展到树上，其实就是用 $dp_i$ 表示从根节点到 $i$ 这一条路径上最大的连续的 $1$ 的个数，状态转移方程不变，最后统计一下叶子结点的答案即可。

code：
```cpp
#include<cstdio>
using namespace std;
int n,m,ans,clr[100005];
int mid[100005],lst[100005];
struct graph
{
	int tot;
	int hd[100005];
	int nxt[200005],to[200005];
	void add(int u,int v)
	{
		tot++;
		nxt[tot]=hd[u];
		hd[u]=tot;
		to[tot]=v;
		return ;
	}
}g;
void dfs(int now,int fa)
{
	if(clr[now]) lst[now]=lst[fa]+1;
	else lst[now]=0;
	if(lst[now]>mid[fa]) mid[now]=lst[now];
	else mid[now]=mid[fa];
	bool flag=true;
	for(int i=g.hd[now];i;i=g.nxt[i])
		if(g.to[i]!=fa) dfs(g.to[i],now),flag=false;
	if(flag&&mid[now]<=m) ans++;
	return ;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&clr[i]);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		g.add(u,v);
		g.add(v,u);
	}
	dfs(1,0);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Harry_Hedwig (赞：1)

# 0x00 思路
先看题。
>给定一棵 $N$ 个节点的有根树（其中根节点始终为 $1$ 号节点），点有点权，点权只有 $1$ 和 $0$ 两种，求从根节点到叶子节点的路径中，有多少条路径满足：路径上最大连续点权为 $1$ 的节点个数不超过 $M$。

那么既然这是一颗有根树， 于是不难想到用存储树的方式来存储它。但是很不幸地是，题面并**没有**规定 $x_i$ 是 $y_i$ 的父节点，所以存在 $x_i$ 是 $y_i$ 的子节点的情况。

那么为了避免这样的情况，我们该怎么做呢？

# 0x01 过程
很明显，建**双向边**即可完成。那么如何去找叶子节点呢？

请大家看这 2 个图：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF580C/3d11dcb54f6b1deed424e5699c584e06f67a1d2b.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF580C/3cc68e912c69745e5c96ffcfeb5680e415b9867a.png)

发现了吗？叶子节点只有**一条边**连接，所以我们可以利用这个特性去寻找叶节点,接着只需要一个很普通的深搜即可。

# code
```c
#include<bits/stdc++.h>
using namespace std;
#pragma 2
const int N=100005;
int n,m,cango[N],ans;
bool have_child[N];
int cats[N];
vector<int>to[N];
void can_go(int now_jie,int cats_num)//现在所在节点、连续有多少节点含有猫（不算此节点）
{
	int cats_now=cats_num*cats[now_jie]+cats[now_jie]/*此节点为1则加1，为0则清零*/,i;
	if(cats_now>m)
		return;
	if(to[now_jie].size()==1&&!cango[now_jie])//判断是否能到
	{
		ans++;
		return;
	}
	cango[now_jie]=1;
	for(i=0;i<to[now_jie].size();i++)//能走到的
	{
		if(!cango[to[now_jie][i]])//没走过
			can_go(to[now_jie][i],cats_now);
	}
	return;
}
int main()
{
	int i,x,y;
	scanf("%d %d",&n,&m);
	for(i=1;i<=n;i++)
		scanf("%d",&cats[i]);
	for(i=1;i<n;i++)
	{
		scanf("%d %d",&x,&y);
		to[x].push_back(y);
		to[y].push_back(x);
	}
	cango[1]=1;//只走一次
	can_go(1,0);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：QQH08 (赞：1)

话说这题不是无脑dfs嘛？

在dfs的时候，除了常规遍历树的参数，再加一个 $sum$。
$sum$ 表示以当前点为结尾的连续 $1$ 的数量，过程中如果大于 $m$ 直接停止遍历即可，否则根据 $a_u$ 分 $2$ 类更新即可。

- 如果 $a_u=0$，$sum$ 直接清零，遍历。
- 如果 $a_u=1$，当 $sum+1 \leq m$，就把 $sum+1$，然后继续遍历；否则直接跳出。

再用一个入度来判断叶子节点，如果一个点入度为 $1$ 且不是根节点，那就是叶子节点了，根据 $sum$ 的大小更新答案。

最后dfs从 $1$ 号点开始，若 $a_1=0$，那么 $sum$ 一开始赋为 $0$；否则为 $1$。

然后代码实现非常简单啦：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int n,m,ans,edgenum,head[N],Next[N*2],vet[N*2],d[N],a[N];
void add(int u,int v){
	edgenum++;
	Next[edgenum]=head[u];
	vet[edgenum]=v;
	head[u]=edgenum;
	d[v]++;
}
void dfs(int u,int fa,int sum){
	if(d[u]==1&&u!=1){
		if(sum<=m)ans++;
		return;
	}
	for(int e=head[u];e;e=Next[e]){
		int v=vet[e];
		if(v==fa)continue;
		if(a[v]==0)dfs(v,u,0);
		else if(sum+1<=m)dfs(v,u,sum+1);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}
	dfs(1,0,a[1]);
	printf("%d",ans);
	return 0;
}
```


---

## 作者：D2T1 (赞：1)

[$\color{blue}{\text {pwp }~{\to\textbf{My blog}\gets}}~\text{qwq}$](https://www.luogu.com.cn/blog/390770/blogcenter)

## 题解

DFS 简单题。

使用 DFS 遍历这棵树，遍历到每个点记录**以这个节点为结尾的连续点权为 $1$ 的节点个数**，当这个数 $> m$ 时直接回溯，遍历到叶子节点时更新答案即可。

## 代码

```cpp
//CF580C
#include <bits/stdc++.h>
using namespace std;

const int N=1e5+10;
int n,m,val[N],ans,vis[N];
vector<int> Edge[N];

inline void dfs(int x,int cnt){
	vis[x]=true;
	if(cnt>m) return;
	if(cnt<=m && x!=1 && Edge[x].size()==1) ++ans;
	for(int i=0; i<Edge[x].size(); ++i){
		int y=Edge[x][i];
		if(!vis[y]){
			if(val[y]) dfs(y,cnt+1);
			else dfs(y,0);
		}
	}
	return;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i) scanf("%d",&val[i]);
	for(int i=1; i<=n-1; ++i){
		int u,v; scanf("%d%d",&u,&v);
		Edge[u].push_back(v);
		Edge[v].push_back(u);
	}
	dfs(1,val[1]);
	printf("%d\n",ans);
	return 0;
} 
```

---

## 作者：123hh2 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF580C)

---

### 前言

这道题很水，打暴力就能过，建议降黄

---

### 题目大意

给你一棵树，节点数为 $n(2 \le n \le 10^5)$，每个节点都有一个权值 $x \in \{0,1\}$

求从根节点 1 出发到所有叶子节点中的所有路径中，最大连续点权为 1 节点个数不超过 $m(1 \le m \le n)$ 的路径个数

---

### 思路

由于 $n(2 \le n \le 10^5)$，我们考虑 $O(n)$ 从节点 1 遍历这棵树，在向下遍历的时候维护一下当前路径的最大连续点权为 1 的个数，如果当前最大连续点权为 1 的个数已经超过 $m$ 的了，就直接 return 就行了，否则继续向下遍历

考虑到一个完整的路径是从 1 号节点到叶子结点的，所以我们用一个 $vis$ 数组来存一下当前遍历到的节点都有哪些。如果当前节点是叶子节点，那么他的父亲一定被遍历到了，所以可以用一个变量来存当前节点的扩展状态，不能扩展的必定是叶子结点

---

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define in inline
#define ri register
#define _123hh2 0
using namespace std;
in int read()
{
    int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}return x*f;
}
in void write(int x) {if(x<0) {x=-x;putchar('-');}if(x>9) write(x/10);putchar(x%10+'0');}
const int maxn=1e5+1;
struct A {int to,nxt;}edge[maxn<<1];
int awa[maxn],head[maxn],cnt,sum,n,m;bool vis[maxn];
in void add(int u,int v) {edge[++cnt].to=v,edge[cnt].nxt=head[u],head[u]=cnt;}
void dfs(int u,int k)//当前遍历到节点 u，最大连续权值为 1 的个数为 k
{
    if(k>m) return;//不合法，直接 return
    vis[u]=1;int tot=0;//这里我脑抽了一下，可以用 bool 变量表示的，用来表示当前节点能否继续扩展
    for(ri int i=head[u];i;i=edge[i].nxt)
    {
        int v=edge[i].to;
        if(vis[v]) continue;//不能遍历已经遍历过的节点
        tot++;
        //如果下一个节点权值为1，那么 k+=1
        //否则 k 置为 0
        //因为要求的是连续的 1 的个数
        if(awa[v]) dfs(v,k+1);
        else dfs(v,0);
    }
    if(!tot) sum++;//合法方案，数量++
}
signed main()
{
    n=read(),m=read();
    for(ri int i=1;i<=n;i++) awa[i]=read();
    for(ri int i=1;i<n;i++) {int u=read(),v=read();add(u,v),add(v,u);}
    dfs(1,awa[1]);write(sum);
    return _123hh2;
}
```
---

~~应该非常简单~~

如果有哪里不懂可以私信我 qwq

---

## 作者：MuYC (赞：0)

#### 前言

本人很菜，只会写无脑暴力。

看到本题，没有想什么DP，DFS，感觉可以树剖维护一个树上最大子段和，于是就写了。

树链剖分练手好题

#### 做法
“路径上最大连续点权为 1 的节点个数”,这不就是最大子段和吗？

因为要求是连续的 1 ，那么我们直接把等于 0 的节点直接在子段上设置权值为负无限就可以了。这样选择最大子段和，肯定不会选择中间负无限的数。所以就可以用树上最大子段和的板子来维护路径上最大连续点权为 1 的节点个数了。

然后枚举一下叶子节点，对于根节点到叶子节点进行路径查询即可。

也不用判断哪一个重链深度深，肯定是叶子节点那边的，这样子就是一个删减版的树上最大子段和了，写完后稍微改改还有双倍经验：[树上最大子段和模板](https://www.luogu.com.cn/problem/SP6779)。

~~很好写啊，也就150行......(doge)，写了一个多小时~~

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 101005,INF = MAXN * 3;

int n,M;
int data[MAXN];
int start[MAXN],cnt = 0;
int dfn[MAXN],dfn_id[MAXN],siz[MAXN],son[MAXN];
int deep[MAXN],fa[MAXN],tp[MAXN],now = 0,root = 1;
int leaves[MAXN],res = 0;

struct Edge {
    int next,to;
} edge[MAXN * 2];

struct Segment {
    int l,r,lmax,rmax,dat,sum;
    void clean()
    {
        l = r = lmax = rmax = dat = sum = 0;
        return ;
    }
} T[MAXN * 4];

void add(int from,int to)
{
    cnt ++;
    edge[cnt].to = to;
    edge[cnt].next = start[from];
    start[from] = cnt;
}

inline int read()
{
    int x = 0 , flag = 1;
    char ch = getchar();
    for ( ; ch > '9' || ch < '0' ; ch = getchar())if(ch == '-')flag = -1;
    for ( ; ch >= '0' && ch <= '9' ; ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
    return x * flag;
}

int DFS(int x,int from)//树链剖分DFS1
{
    siz[x] = 1;fa[x] = from;
    son[x] = 0,deep[x] = deep[from] + 1;
    int flag = 1;
    for(int i = start[x] ; i ; i = edge[i].next)
    {
        int to = edge[i].to;
        if(to == from) continue;
        flag = 0;
        int v = DFS(to,x);
        siz[x] += v;
        if(v > siz[son[x]])son[x] = to;
    }
    leaves[x] = flag;//如果没有出边就是叶子节点，用flag进行判断
    return siz[x];
}

void DFS2(int x,int top)//树链剖分DFS2
{
    tp[x] = top;
    dfn[x] = ++ now ; 
    dfn_id[now] = x;
    if(son[x])DFS2(son[x],top);
    for(int i = start[x] ; i ; i = edge[i].next)
    {
        int to = edge[i].to;
        if(to != son[x] && to != fa[x])DFS2(to,to);
    }
    return ;
}

Segment update(Segment A,Segment B)//最大子段和的合并
{
    Segment Res;
    Res.lmax = max(A.lmax , A.sum + B.lmax);
    Res.rmax = max(B.rmax , B.sum + A.rmax);
    Res.sum = A.sum + B.sum;
    Res.dat = max(max(A.dat,B.dat),A.rmax + B.lmax);
    return Res;
}

void build(int x,int l,int r)//常规线段树建树
{
    T[x].l = l , T[x].r = r;
    if(l == r)
    {
        if(data[dfn_id[l]])T[x].lmax = T[x].rmax = T[x].dat = T[x].sum = 1;
        else T[x].lmax = T[x].rmax = T[x].dat = T[x].sum = -INF;//赋值为负无限 
        return ;
    }
    int mid = (l + r) >> 1;
    build(x << 1 , l , mid);
    build(x << 1 | 1 , mid + 1 , r);
    T[x] = update(T[x << 1] , T[x << 1 | 1]);
    T[x].l = l , T[x].r = r;
    return ;
}

Segment GetMax(int x,int l,int r)
{
    if(T[x].l >= l && T[x].r <= r)return T[x];
    int mid = (T[x].l + T[x].r) >> 1;
    if(l > mid)return GetMax(x << 1 | 1 , l , r);
    if(r <= mid)return GetMax(x << 1 , l , r);
    Segment Res,A = GetMax(x << 1 , l , mid),B = GetMax(x << 1 | 1 , mid + 1 , r);
    Res = update(A,B);
    return Res;
}

void GetS(int to,int x)
{
    Segment Ans;
    Ans.lmax = -100000, Ans.rmax = -100000 , Ans.dat = -1000000,Ans.sum =0 ;
    while(x)//目标一直是根节点，所以直接判断x不为零即可。
    {
        Segment Now;
        Now = GetMax(1 , dfn[tp[x]] , dfn[x]);
        Ans = update(Now,Ans);//Ans一定要放在后面，不然会Wa！
        x = fa[tp[x]];
    }
    if(Ans.dat <= M)res ++;
    return ;
}

signed main()
{
    n = read();M = read();
    for(int i = 1 ; i <= n ; i ++)
    {
        int x = read();
        data[i] = (bool)(x);
    }
    for(int i = 1 ; i <= n - 1 ; i ++)
    {
        int u = read(),v = read();
        add(u,v);add(v,u);
    }
    DFS(1,0);
    DFS2(1,1);
    build(1, 1 , n);
    for(int i = 1 ; i <= n ; i ++)if(leaves[i] == 1)GetS(root,i);
    cout << res;
    return 0;
}
```

#### 后话
虽说，最坏时间复杂度为O($n log^2n$)，但是貌似跑得还算快？

![](https://s3.ax1x.com/2020/11/26/D00YqK.png)

---

## 作者：AuCloud (赞：0)

很裸的树上dp

考虑记录每个节点到根节点路径上的最长1串长度和后缀1串长度

每个点若为1则后缀++，跟最长串取max

若为0则后缀清空

最后判断若为叶子节点则判断是否合法，更新ans

```cpp
#include <bits/stdc++.h>
using namespace std;
int k, ans;
int a[100001], mx[100001], hz[100001], head[100001], nxt[200001], to[200001], tot;
void add(int x, int y)
{
    nxt[++tot] = head[x];
    head[x] = tot;
    to[tot] = y;
}
void dfs(int x, int from)
{
    if(a[x] == 1)
    {
        hz[x] = hz[from] + 1;
        mx[x] = max(mx[from], hz[x]);
    }
    else
    {
        hz[x] = 0;
        mx[x] = mx[from];
    }
    bool fl = 0;
    for(int i = head[x]; i; i = nxt[i])
    {
        int y = to[i];
        if(y != from)
        {
            fl = 1;
            dfs(y, x);
        }
    }
    if(!fl && mx[x] <= k) ans++;
}
int main()
{
    int n;
    cin >> n >> k;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for(int i = 1; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        add(x, y);
        add(y, x);
    }
    dfs(1, 0);
    cout << ans;
    return 0;
}

```

~~这题绝对不值蓝题~~

---

## 作者：cyy233 (赞：0)

# 看没人写赶紧水一发




给定一棵$ N $个节点且以1号节点为根的树，点有点权，点权

只有 $1$ 和 $0$ 两种，求从**根节点到叶子节点**的路径中，

有多少条路径满足：路径上最大**连续**点权不超过$ M$。



首先，这道题必须$dfs$或$bfs$(不然怎么做）

对于每个节点$x$，我们必须统计搜到这的点权值，

如果这个节点权值为$0$，

就把$dfs$过程中往下传的连续点权值改为$0$，

因为只有当点权值为1是才能增加连续点权，

如果是$1$，那么我们就在从父节点传下来的连续点权值的基础上$+1$，当连续点权超过$m$时，这个儿子在就不用做了。




代码如下






```
#include<bits/stdc++.h>
#define LL long long
#define inf LONG_LONG_MAX
#define re register
#define he(x) for(register int i=head[x];i;i=e[i].nxt)
using namespace std;
LL n,m,ans,tot,head[200010],val[100010];
struct CCF{
	LL nxt,to;
}e[200010];
template <class frd> inline void read(frd &a)
{
    bool f=0;a=0;char ch=getchar();
    while(ch<48||ch>57){if(ch=='-')f=1;ch=getchar();}
    while(ch>=48&&ch<=57)a=(a<<1)+(a<<3)+(ch^48),ch=getchar();
    if(f)a=-a;
}
template<typename T>inline void readc(T &x){
    while(x=getchar(),!islower(x)&&!isupper(x));
}
template<typename T>inline void print(T x,char c='\n'){
    static int buf[40];
    if(x==0){
        putchar('0');
        putchar(c);
        return;
    }
    if(x<0)putchar('-'),x=-x;
    for(buf[0]=0;x;x/=10)buf[++buf[0]]=x%10+48;
    while(buf[0])putchar((char)buf[buf[0]--]);
    putchar(c);
}
inline void add(LL x,LL y){
	e[++tot].to=y;
	e[tot].nxt=head[x];
	head[x]=tot;
}
inline void dfs(LL x,LL fa,LL w){
	bool flag=false;
	he(x){
		LL y=e[i].to;
		if(y==fa)continue;
		flag=true;
        //如果它有儿子，就不是叶子节点
		if(val[y]+w>m)continue;
  		//超过m，不做了
		if(val[y])dfs(y,x,val[y]+w);
		else dfs(y,x,0);
  		//点权为0，连续点权清零
	}
	if(!flag)ans++;
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	read(n);read(m);
	for(int i=1;i<=n;i++)read(val[i]);
	for(int i=1;i<n;i++){
		LL u,v;
		read(u);read(v);
		add(u,v);add(v,u);
	}
	dfs(1,0,val[1]);
  //必须有根节点的点权
	print(ans);
	fclose(stdin);fclose(stdout);
    return 0;
}

```










---

