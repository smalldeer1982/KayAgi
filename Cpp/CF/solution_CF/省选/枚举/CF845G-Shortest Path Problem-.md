# Shortest Path Problem?

## 题目描述

You are given an undirected graph with weighted edges. The length of some path between two vertices is the bitwise xor of weights of all edges belonging to this path (if some edge is traversed more than once, then it is included in bitwise xor the same number of times). You have to find the minimum length of path between vertex $ 1 $ and vertex $ n $ .

Note that graph can contain multiple edges and loops. It is guaranteed that the graph is connected.

## 样例 #1

### 输入

```
3 3
1 2 3
1 3 2
3 2 0
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 2
1 1 3
1 2 3
```

### 输出

```
0
```

# 题解

## 作者：zac2010 (赞：5)

不妨先了解几个前置知识/引理：

异或的抵消性质：

* $a\oplus a=0$
* $\forall b[b\not= a],a\oplus b\not=0$
* $(a\oplus b)\oplus (a\oplus c)=b\oplus c$

> 引理 $1$：$\forall u,v\in\text{Tree}$，$u\to v$ 所有路径的边权异或和都等于 $dis_u\oplus dis_v$（$dis_i$ 为节点 $i$ 到根路径上边权的异或和）

上述引理根据异或的抵消性可得。

> 引理 $2$：对于一般图 $G$，我们任取一颗 $\text{DFS}$ 树。那么图上所有的环都可以用只包含了一条非树边的简单环异或出来。

> 引理 $3$：对于图上两点间的任意路径（我们只关心边权的异或和），必定可以由 $\text{DFS}$ 树上的树边路径以及图中一些环异或出来。

依旧是利用异或的抵消性质得到。

我们回到题目中。假设输入的图是一棵树，那么直接 $dis_1\oplus dis_n$ 就做完了。

但输入的可能是一般图——我们任取一颗 $\text{DFS}$ 树，按照上述方法求出 $dis_1$ 到 $dis_n$。之后考虑那些非树边，每条非树边都必定会与一些树边形成恰好一个简单环。根据引理 $2,3$，我们只需要维护一个支持插入的数据结构，它能选出一个子集，使得子集中的元素异或上 $dis_1\oplus dis_n$ 最大。发现线性基可以轻松的维护。

```cpp
#include <bits/stdc++.h>
#define FL(i, a, b) for(int i = (a); i <= (b); i++)
#define FR(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
struct E{int v; ll w;}; vector<E> e[N];
int n, m, vis[N]; ll dis[N];
struct LinearBasis{
	ll a[65];
	int insert(ll x){
		FR(i, 62, 0) if((x >> i) & 1){
			if(!a[i]){a[i] = x; return 1;}
			else x ^= a[i];
		}
		return 0;
	}
	ll qmin(ll ret = 0){
		FR(i, 62, 0) ret = min(ret, ret ^ a[i]);
		return ret;
	}
} b;
void dfs(int u, int fa){
	vis[u] = 1;
	for(const auto &p: e[u]) if(p.v != fa){
		if(!vis[p.v])
			dis[p.v] = dis[u] ^ p.w, dfs(p.v, u);
		else b.insert(dis[u] ^ dis[p.v] ^ p.w);
	}
}
int main(){
    scanf("%d%d", &n, &m);
    FL(i, 1, m){
        int u, v; ll w;
		scanf("%d%d%lld", &u, &v, &w);
        e[u].emplace_back((E){v, w});
		e[v].emplace_back((E){u, w});
    }
	dfs(1, 0);
	printf("%lld\n", b.qmin(dis[1] ^ dis[n]));
    return 0;
}
```

---

## 作者：顾z (赞：3)

> ### Description
>
> 给定一张 $n$ 个点 $m$ 条边的无向图，一开始你在点 $1$，且价值为 $0$
>
> 每次你可以选择一个相邻的点，然后走过去，并将价值异或上该边权
>
> 如果在点 $n$，你可以选择结束游戏
>
> 求一种方案，使得结束游戏后价值最小
>
> $n,m \le 10^5$
>
> ### Input
>
> 第一行为两个整数$n,m$代表有$n$个点$m$条边。
>
> 接下来$m$行,描述一条从$x$到$y$长度为$z$的无向边。
>
> ### Output
>
> 一个整数,代表最小价值。

首先,很明确的一点,题目要求我们求出很多条边的最小异或和。

由此,我们可以想到**线性基**

由于我们可以重复经过一些边,那么根据异或性质,当这条边被重复走过两次,那它对答案的贡献就是$0$。但是即使这样,它还可能连向其他的点。

虽然我们没办法枚举边,但是可以考虑将这些边所在分为两种。

1. 环上的边
2. 链上的边

但是我们**通向一个环的时候会经过一条连向这个环的边两次**。(一进一出)。

因此,我们考虑**维护每个环的异或和,塞入线性基中**。

再找一条链,去和其异或起来最小。即可。

**这条链可以随便选择**。

简单证明一下;

> 假设存在两条链$A,B$，我们现在选择了不优的$A$链,但是在求解答案的时候(利用线性基)
>
> 我们会异或到一个环($A,B$链围成的环),这时,就好比我们原路返回,又选择了较优的$B$链。

因此,这个题就解决了.

``代码``

```c++
#include<cstdio>
#include<algorithm>
#include<iostream>
#define R register
#define lo long long 

using namespace std;

const int gz=1e5+8;

inline void in(R int &x)
{
    int f=1;x=0;char s=getchar();
    while(!isdigit(s)){if(s=='-')f=-1;s=getchar();}
    while(isdigit(s)){x=x*10+s-'0';s=getchar();}
    x*=f;
}

int head[gz<<1],tot;

struct cod{int u,v;lo w;}edge[gz<<2];

lo p[64],dis[gz];

inline void add(R int x,R int y,R lo z)
{
    edge[++tot].u=head[x];
    edge[tot].v=y;
    edge[tot].w=z;
    head[x]=tot;
}

int n,m;

bool vis[gz];

inline void ins(R lo x)
{
    for(R int i=63;i>=0;i--)
    {
        if((x>>i)&1LL)
        {
            if(p[i])
                x^=p[i];
            else 
            {
                p[i]=x;
                break;
            }
        }
    }
}

inline lo query(R lo o)
{
    R lo res=o;
    for(R int i=63;i>=0;i--)
        if((res^p[i])<res)res^=p[i];
    return res;
}

void dfs(R int u,R lo now)
{
    vis[u]=true;dis[u]=now;
    for(R int i=head[u];i;i=edge[i].u)
    {
        if(!vis[edge[i].v])
            dfs(edge[i].v,now^edge[i].w);
        else ins(now^edge[i].w^dis[edge[i].v]);
    }
}

int main()
{
    in(n);in(m);
    for(R int i=1,x,y;i<=m;i++)
    {
        R lo z;
        in(x),in(y);
        scanf("%lld",&z);
        add(x,y,z),add(y,x,z);
    }
    
    dfs(1,0);
    
    printf("%lld\n",query(dis[n]));
}
```



---

## 作者：splendore (赞：2)

### 题意
给定一个无向图（可能有环），求 $1$ 到 $n$ 异或和最小的一条路径。

### 思路
看到求一条路径的异或值，想到线性基。

因为求的是异或和，所以往外走再原路返回的答案不变，所以我们只需要考虑环的情况即可。

事实上，可以直接把环当成一个点，将其异或和插入线性基，最后再找出线性基中可表出的最小的值就是答案。

代码如下：
```
#include<cstdio>
using namespace std;
typedef long long LL;
const int N=100005,M=200005,B=60;
struct edge{int y;LL c;int pre;}a[M];int alen,last[N];
inline void ins(int x,int y,LL c){a[++alen]={y,c,last[x]};last[x]=alen;}
int n,m,cnt;
LL p[B+1],d[N];
bool zero,v[N];
void ins(LL x){
	for(int i=B;~i;--i)
		if(x>>i&1){
			if(!p[i])return p[i]=x,void();
			else x^=p[i];
		}
	zero=1;
}
LL findmin(){
	LL res=d[n];
	for(int i=B;~i;--i)if(res>(res^p[i]))res^=p[i];
	return res;
}
void dfs(int x){
	v[x]=1;
	for(int k=last[x],y;k;k=a[k].pre){
		if(!v[y=a[k].y])d[y]=d[x]^a[k].c,dfs(y);
		else ins(d[y]^d[x]^a[k].c);
	}
}
int main(){
	LL c;scanf("%d%d",&n,&m);
	for(int i=1,x,y;i<=m;++i){
		scanf("%d%d%lld",&x,&y,&c);
		ins(x,y,c);ins(y,x,c);
	}
	dfs(1);
	printf("%lld",findmin());
	return 0;
}
```

---

## 作者：Forever1507 (赞：1)

前置知识：
- $a⊕b=c$ 则 $a⊕c=b$
- 线性基

显然我们要求一堆边的边权异或最小值，马上联想到线性基。

但是我们显然是不能直接上线性基的，不然你保证不了连通性。

首先我们想到环，对于一个环，一旦进入，就 **必须把环里的边全部走完** 。

所以我们可以直接把环往线性基里塞。

然后题目就可以简化为一条链加上若干环的异或和的最小值。

提出结论：边可以任选。

证明：

对于两个不同的从 $1$ 到 $n$ 的边的集合 $A,B$，因为是无向图，所以 $A$ 和 $B$ 一定构成环，然后这个环一定在线性基里，所以任意选就可以了。


代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{
	int v,w;
};
vector<node>nbr[100005];
int n,p[64],dis[100005],m;
bool wypafo(int x){
	for(register int j=63;j>=0;j--){
		if(1ll*x>>j){
			if(!p[j]){ 
				p[j]=x;
				break;
			}
			else x^=p[j];
		}
	}
}
bool vis[100005];
void dfs(int cur,int sum){
	vis[cur]=1;
	dis[cur]=sum;
	for(register int i=0;i<nbr[cur].size();++i){
		int nxt=nbr[cur][i].v;
		if(!vis[nxt])dfs(nxt,sum^nbr[cur][i].w);//如果重复到达两次就是环
		else wypafo(sum^nbr[cur][i].w^dis[nxt]);
	}
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;++i){
		int u,v,w;
		cin>>u>>v>>w;
		nbr[u].push_back((node){v,w});
		nbr[v].push_back((node){u,w});
	}
	dfs(1,0);
	int ans=dis[n];
	for(int i=63;i>=0;i--)ans=min(ans,ans^p[i]);
	cout<<ans;
	return 0;
}
```


---

## 作者：JK_LOVER (赞：1)

## 题意
从一号节点出发，使得到达 $n$ 号节点后总价值最小。总价值是把路径价值异或起来得到的值。[$QWQ$](https://www.luogu.com.cn/blog/xzc/solution-cf845g)
## 分析
就像最大XOR和路径 [一样](https://www.luogu.com.cn/problem/P4151) 
。这道题也要分析异或的特殊性质 
$$
a \oplus b \oplus b = a
$$ 
有了这个性质，那么我们就可以考虑一个环的贡献，就像下图。如果进入这个环，那么它就可以考虑异或这个环可以贡献的值，因为来回两次，进入环的那条边的贡献就被抵消掉了。
![](https://cdn.luogu.com.cn/upload/image_hosting/lh7jbiq3.png)

- 那现在就是求问到底异或哪些环可以使异或和最小。

- 线性基可以处理子集异或和，那么就可以把每个环的值插入线性基。

- 然后随意找一条 $1$ 号节点到 $n$ 号节点的路径，查询就可以了。为什么可以是随意？因为任意不同的两条 $1$ 到 $n$ 的路径一定构成了一个环，这样两条路径其实就等价了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+100;
int read(){
	int x = 0,f = 0;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)) {x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
struct Edge{int to,nxt,w;}e[N<<1];
int head[N],vis[N],dis[N],p[70],cnt = 1,n,m;
void addedge(int x,int y,int z){
	e[++cnt].to = y;e[cnt].nxt = head[x];e[cnt].w = z;head[x] = cnt;
	e[++cnt].to = x;e[cnt].nxt = head[y];e[cnt].w = z;head[y] = cnt;
}
void insert(int x){
	for(int i = 30;i >= 0;i--) {
		if((x>>i)&1){
			if(!p[i]){
				p[i] = x;return;
			}
			x ^= p[i];
		}
	}
}
void dfs(int x,int val)
{
	dis[x] = val;
	for(int i = head[x];i;i = e[i].nxt){
		int y = e[i].to;
		if(!vis[y]){
			vis[y] = 1;
			dfs(y,val ^ e[i].w);
		}
		else insert(val ^ e[i].w ^ dis[e[i].to]);
	}
}
int main()
{
	n = read();m = read();
	for(int i = 1;i <= m;i++) {
		int a = read(),b = read(),c = read();
		addedge(a,b,c);
	}
	vis[1] = 1;
	dfs(1,0);
	for(int i = 30;i >= 0;i--){
		if((dis[n]^p[i]) < dis[n]){
			dis[n] ^= p[i];
		}
	}
	printf("%d\n",dis[n]);
	return 0;
}
```



---

## 作者：L_zaa_L (赞：0)

## 题意
求图上从 $1$ 到 $n$ 的所有路径的最小异或和。

## 分析
一眼看出可以用线性基。

由题目可以看出答案是由随便一条 $1$ 到 $n$ 的路径异或上图中若干个环。

所以可以将用 DFS 处理环，将环的异或和扔进线性基。

然后从 $1$ 到 $n$ 路径的选择随便选一个，因为如果有另一条更优的路径的话，这两条路径就会构成一个环，最优解用这个环异或掉原来选择的路径，就会自动变为更优的路径。

然后直接用线性基算出最小值即可。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch;
	ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-f;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+(ch-'0');
		ch=getchar();
	}
	return x*f;
}
int n,m;
vector<pair<int,int> > q[200005];
bool flag[200005];
int gg[200005];
int p[200005];
void insert(int x){//插入线性基
	for(int i=63;i>=0;i--)
		if(x&(1ll<<i)){
			if(!p[i]){p[i]=x;break;}
			x^=p[i];
		}
}
void dfs(int now,int uu){
	flag[now]=1;
	gg[now]=uu;
	for(int i=0;i<q[now].size();i++){
		int v=q[now][i].first;
		int d=q[now][i].second;
		if(!flag[v]) dfs(v,uu^d);
		else insert(d^gg[v]^uu);
	}
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int s=read(),t=read(),d=read();
		q[s].push_back(make_pair(t,d));
		q[t].push_back(make_pair(s,d));
	}
	dfs(1,0);
	int ans=gg[n];
	for(int i=60;i>=0;i--) ans=min(ans^p[i],ans);//线性基算出最小值
	cout<<ans;
	return 0;
}
```



---

## 作者：Yansuan_HCl (赞：0)

如果是树则答案唯一——**往外走任意路径再走回简单路径答案不变**。考虑图比树多什么：往树上加边则形成一个环。根据上方结论，可以**任意走到一个环**，走完这个环再走简单路径。

于是就显而易见：把每个环的权值加入线性基查询即可。

```cpp
struct LB {
	ll p[63];
	void insert(ll v) {
		D (i, 62, 0) if ((v >> i) & 1) {
			if (!p[i]) { p[i] = v; break; }
			v ^= p[i];
		}
	}
	ll ask(ll v) {
		D (i, 62, 0) if ((v ^ p[i]) < v)
			v ^= p[i];
		return v;
	}
} lb;

const int N = 100004;
int n, m; vector<pair<int, ll>> g[N];
int vis[N]; ll sum[N];
void dfs(int u) {
	vis[u] = 1;
	for (auto [v, w] : g[u])
		if (vis[v])
			lb.insert(sum[v] ^ sum[u] ^ w);
		else {
			sum[v] = sum[u] ^ w;
			dfs(v);
		}
}

int main() {
	rd(n, m);
	U (i, 1, m) {
		int u, v; ll w; rd(u, v, w);
		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}
	dfs(1);
	printf("%lld", lb.ask(sum[n]));
}
```

---

## 作者：Plozia (赞：0)

宣传博客 $\to$ [link](https://blog.csdn.net/BWzhuzehao/article/details/118765815)

首先看到题目的时候，看见异或最小值，就需要想到可能是线性基，而这题正需要线性基。

这里推几个线性基的写的好的文章：

- [线性基 - OI Wiki](https://oi-wiki.org/math/basis/)
- ~~[数学/数论专题-学习笔记：线性基 - By Plozia](https://blog.csdn.net/BWzhuzehao/article/details/118388282)~~

好，现在我认为你已经掌握了线性基。

对于 $1 \to n$ 的路径而言，我们可以将这条路径拆成 2 部分：一条链 + 一些环。

相当于我们要求链的路径长度异或上所有环长度的最小值。

先看所有环长度的异或最小值，我们可以先用一遍 DFS 预处理出所有的环，将这些环的长度丢到线性基里面，那么这样线性基能异或出来的最小值就是所有环长度的最小值。

但是还有一条链啊？

实际上这条链可以随便选！

证明如下：

假设我们不能随便选链，也就是说我们必须选择长度为 $A$ 的链才能得到正确答案。

设所有环能异或出的最小值为 $x$，我们选出的路径长度为 $B$，实际上的最优长度为 $A$，那么按照假设我们有 $B \oplus x > A \oplus x$。

但是注意到这是一张无向图，因此路径 $A$ 和路径 $B$ 共同组成了一个环。

由于我们需要求的是最小值，因此当我们遍历线性基求最小值的时候由于 $A \oplus x$ 更优，将会导致 $B \gets B \oplus A$。

因此实际上 $A,B$ 两条路径是同等优秀的，不存在哪条更加优秀的链。

证毕。

Code：[GitHub CodeBase-of-Plozia CF845G Shortest Path Problem.cpp](https://github.com/Plozia/CodeBase-of-Plozia/blob/main/Codeforces%20%E5%88%B7%E9%A2%98%E5%90%88%E9%9B%86/CF845G%20Shortest%20Path%20Problem.cpp)

```cpp
/*
========= Plozia =========
    Author:Plozia
    Problem:CF845G Shortest Path Problem?
    Date:2021/7/15
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 100000 + 5, MAXM = 100000 + 5;
int n, m, Head[MAXN], cnt_Edge = 1;
LL ans, dis[MAXN], d[70];
bool book[MAXN];
struct node { int to; LL val; int Next; } Edge[MAXM << 1];

LL Read()
{
    LL sum = 0, fh = 1; char ch = getchar();
    for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
    return sum * fh;
}
LL Max(LL fir, LL sec) { return (fir > sec) ? fir : sec; }
LL Min(LL fir, LL sec) { return (fir < sec) ? fir : sec; }
void add_Edge(int x, int y, LL z) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, z, Head[x]}; Head[x] = cnt_Edge; }

void Add(LL x)
{
    for (int i = 63; i >= 0; --i)
    {
        if (x & (1ll << i))
        {
            if (d[i] & x) x ^= d[i];
            else { d[i] = x; return ; }
        }
    }
}

void dfs(int now, LL sum)
{
    book[now] = 1; dis[now] = sum;
    for (int i = Head[now]; i; i = Edge[i].Next)
    {
        int u = Edge[i].to;
        if (!book[u]) dfs(u, sum ^ Edge[i].val);
        else Add(sum ^ Edge[i].val ^ dis[u]);
    }
}

int main()
{
    n = Read(), m = Read();
    for (int i = 1; i <= m; ++i)
    {
        int x = Read(), y = Read(); LL z = Read();
        add_Edge(x, y, z); add_Edge(y, x, z);
    }
    dfs(1, 0); ans = dis[n];
    for (int i = 63; i >= 0; --i) ans = Min(ans, ans ^ d[i]);
    printf("%lld\n", ans); return 0;
}
```

---

## 作者：huayucaiji (赞：0)

裸的线性基，只不过需要一些变化。

我们首先需要对图构建一颗随意的生成树。只要是颗树即可。比如说我们构造出了如下的一张图（其中边权为 `....` 的代表这之间可能省略了一些边）：

![1](http://image.qingtengbc.com/2021/03/07/5349fa2d65311.png)

我们可以通过一次 DFS 求出每个点到根节点，即 $2$ 号点，的距离 $dis_i$。**注意根节点不一定是 $2$，最好不要是 $1$ 或 $n$，没试过是否可以。**

显然我们还有一些不在生成树里的边，对于这些边，有一个废话一样的性质，就是他们加进图去后，至少会产生一个新的环。比如说我们加入一条边 $(k_2,k_3)$，得到图：

![2](http://image.qingtengbc.com/2021/03/07/c490d61115da2.png)

我们得到了一个环 $k_1,k_2,k_3,\cdots,k_n$，环的权值是 $val_c=val_1 \operatorname{xor} val_2\operatorname{xor} val_3\cdots\operatorname{xor} val_n$。我们的 $1->n$ 的路径上如果要经过这个环怎么办呢？我们可以这样想，其实我们遍历一下这个环得到的权值是 $dis_1 \operatorname{xor} dis_{k_1} \operatorname{xor} val_c \operatorname{xor} dis_{k_1} \operatorname{xor} dis_1=val_c$。因此只是把这个环的权值加了进去。

由于任意一个环都可以用几个环异或出来，我们只需要把每条新加入的边形成的环加到线性基里，求出**最小**值后，再异或上必须要有的 $dis_1$ 和 $dis_n$，就是答案。

时间复杂度 $O(n)$。

```cpp
//Don't act like a loser.
//This code is written by huayucaiji
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int MAXN=2e5+10;

int n,m,cnt;
int p[100],h[MAXN],father[MAXN],dis[MAXN];

int find(int x) {
	if(x!=father[x]) {
		return father[x]=find(father[x]);
	}
	return father[x];
}

void insert(int x) {
	for(int i=63;i>=0;i--) {
		if(!(x&(1ll<<i))) {
			continue;
		}
		if(!p[i]) {
			p[i]=x;
			break;
		}
		x=p[i]^x;
	}
}

struct edge {
	int u,v,w,next;
	bool tree;
}e[MAXN<<2];

void addedge(int u,int v,int w) {
	e[++cnt].u=u;
	e[cnt].v=v;
	e[cnt].w=w;
	e[cnt].next=h[u];
	h[u]=cnt;
}

void generate_tree() {
	for(int i=1;i<=m;i++) {
		if(find(e[i].u)!=find(e[i].v)) {
			father[find(e[i].u)]=find(e[i].v);
			e[i].tree=1;
			e[i+1].tree=1;
		}
	}
}
void dfs(int u,int fa) {
	for(int i=h[u];i;i=e[i].next) {
		if(!e[i].tree) {
			continue;
		}
		int v=e[i].v;
		
		if(v!=fa) {
			dis[v]=dis[u]^e[i].w;
			dfs(v,u);
		}
	}
}

signed main() {
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		father[i]=i;
	}
	for(int i=1;i<=m;i++) {
		int u,v,w;
		u=read();
		v=read();
		w=read();
		addedge(u,v,w);
		addedge(v,u,w);
	}
	m<<=1;
	
	generate_tree();
	dfs(2,0);
	
	for(int i=1;i<=m;i++) {
		if(!e[i].tree) {
			insert(dis[e[i].u]^dis[e[i].v]^e[i].w);
		}
	}
	
	int ans=dis[1]^dis[n];
	for(int i=63;i>=0;i--) {
		ans=min(ans,ans^p[i]);
	}
	
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：Hagasei (赞：0)

双倍经验：[[WC2011]最大XOR和路径](https://www.luogu.com.cn/problem/P4151)

看到“异或”，“最”等字眼我们就知道它是道线性基。

我们发现一种做法是找到一条路径之后用任意环将其增广，因为 $p\operatorname{xor}p=0$，所以正确性是保证的（跑到某个环再跑回来无影响。

但是有几个问题

- 找哪条路径？其实哪条都可以。因为 $p_1:1\rightarrow n$ 与 $p_2:1\rightarrow n$ 必会组成一条环。

- 环有很多怎么办？求出任意生成树，则所有非树边均会拉出一个环，而它们可以凑出所有的环。

- 怎么统计答案？把环的异或和都加入线性基里，然后以那条路径的边权为起始值，跑最小异或即可。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int p[64],d[64],zero;
inline void insert(int x){
	while(x&&p[__lg(x)]) x^=p[__lg(x)];
	if(x) p[__lg(x)]=x;
	else ++zero;
}
inline int qmin(int x){
	int r=LLONG_MAX;
	for(int i=63;i>=0;--i){
		x=min(x,p[i]^x);
	}
	if(zero) r=min(r,x);
	return x;
}
int a[100005],n;
int hd[200005],nxt[200005],ww[200005],to[200005],cnt,val[100005],tot;
bool tag[200005],vis[100005];
bool dfs(int x){
	vis[x]=1;
	bool flag=0,f;
	for(int i=hd[x];~i;i=nxt[i]){
		const int y=to[i],w=ww[i];
		if(!vis[y]){
			tag[i]=tag[i^1]=1;
			val[y]=val[x]^w;
			if(f=dfs(y)) tot^=w;
			flag|=f;
		}
	}
	if(x==n||flag) return 1;
	return 0;
}
signed main(){
	memset(hd,-1,sizeof hd);
	int m;
	cin>>n>>m;
	for(int i=1;i<=m;++i){
		int x,y,w;
		cin>>x>>y>>w;
		nxt[cnt]=hd[x];
		hd[x]=cnt;
		to[cnt]=y;
		ww[cnt]=w;
		++cnt;
		nxt[cnt]=hd[y];
		hd[y]=cnt;
		to[cnt]=x;
		ww[cnt]=w;
		++cnt;
	}
	dfs(1);
	for(int x=1;x<=n;++x){
		for(int i=hd[x];~i;i=nxt[i]){
			const int y=to[i],w=ww[i];
			if(!tag[i]&&(i&1)){
				insert(w^val[x]^val[y]);
			}
		}
	}
	cout<<qmin(tot);
}
```

---

