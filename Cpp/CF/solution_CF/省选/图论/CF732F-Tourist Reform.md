# Tourist Reform

## 题目描述

Berland is a tourist country! At least, it can become such — the government of Berland is confident about this.

There are $ n $ cities in Berland, some pairs of which are connected by two-ways roads. Each road connects two different cities. In Berland there are no roads which connect the same pair of cities. It is possible to get from any city to any other city using given two-ways roads.

According to the reform each road will become one-way. It will be oriented to one of two directions.

To maximize the tourist attraction of Berland, after the reform for each city $ i $ the value $ r_{i} $ will be calculated. It will equal to the number of cities $ x $ for which there is an oriented path from the city $ i $ to the city $ x $ . In other words, $ r_{i} $ will equal the number of cities which can be reached from the city $ i $ by roads.

The government is sure that tourist's attention will be focused on the minimum value of $ r_{i} $ .

Help the government of Berland make the reform to maximize the minimum of $ r_{i} $ .

## 样例 #1

### 输入

```
7 9
4 3
2 6
7 1
4 1
7 3
3 5
7 4
6 5
2 5
```

### 输出

```
4
4 3
6 2
7 1
1 4
3 7
5 3
7 4
5 6
2 5
```

# 题解

## 作者：DrBit (赞：7)

[题面](https://www.luogu.com.cn/problem/CF732F)

首先有一个结论，如果在一个连通块在无向图状态下是一个边双，那么一定有一种方法通过给边赋方向满足这个连通块在有向图状态下是强连通分量。

考虑把边双缩成一个点，那么这些点构成了一个树形结构。

因为要把这些树边（也就是割边）附上方向，所以肯定有一个边双不能走到其他边双。我们让那个边双为所含节点数最多的一个边双，可以发现这个边双的节点数就是题中要求的 $r_i$。

考虑一下怎么构造一个合法的方案。

其实很简单，在最大的边双中任取一点，从这个点开始 dfs，把树边的方向定为从上到下，非树边的方向定为从下到上。

这样原有的边双赋完方向之后都是强连通分量，且其他边双都能够走到最大的那个边双。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN = 4e5 + 50;
int bcc[MAXN], bcctot, siz[MAXN], dfn[MAXN], low[MAXN], timtot;
int s[MAXN], top, vis[MAXN];
struct edge
{
    int nxt, to, from, tag;
} e[MAXN * 2];
int head[MAXN], edgetot = 1;
int ans[MAXN];
int N, M;
void add(int x, int y)
{
    e[++edgetot].to = y;
    e[edgetot].from = x;
    e[edgetot].nxt = head[x];
    head[x] = edgetot;
}
void tarjan(int x, int fa)
{
    dfn[x] = low[x] = ++timtot;
    s[++top] = x;
    vis[x] = 1;
    for (int i = head[x]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (v == fa)
            continue;
        // cout << x << " " << v << ":" << dfn[v] << " " << low[v] << endl;
        if (!dfn[v])
        {
            tarjan(v, x);
            low[x] = min(low[x], low[v]);
        }
        else if (vis[v])
            low[x] = min(low[x], dfn[v]);
    }
    // cout << x << ":" << fa << " " << dfn[x] << " " << low[x] << endl;
    if (low[x] == dfn[x])
    {
        bcctot++;
        while (true)
        {
            int t = s[top];
            top--;
            siz[bcctot]++;
            bcc[t] = bcctot;
            vis[t] = 0;
            if (t == x)
                break;
        }
    }
}
void dfs(int x, int fa)
{
    vis[x] = 1;
    for (int i = head[x]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (v == fa)
            continue;
        // cout << x << "-->" << v << endl;
        if (vis[v])
        {
            if (!ans[i / 2])
                ans[i / 2] = i ^ 1;
        }
        else
        {
            if (!ans[i / 2])
                ans[i / 2] = i ^ 1;
            dfs(v, x);
        }
    }
}
int main()
{
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= M; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    for (int i = 1; i <= N; ++i)
        if (!dfn[i])
            tarjan(i, 0);
    int idx = 0;
    for (int i = 1; i <= N; ++i)
    {
        if (siz[bcc[i]] > siz[bcc[idx]])
            idx = i;
        // cout << i << ":" << bcc[i] << " " << siz[bcc[i]] << endl;
    }
    memset(vis, 0, sizeof(vis));
    // cout << idx << endl;
    dfs(idx, 0);
    printf("%d\n", siz[bcc[idx]]);
    for (int i = 1; i <= M; ++i)
        printf("%d %d\n", e[ans[i]].from, e[ans[i]].to);
    return 0;
}
```


---

## 作者：sgl654321 (赞：6)

一些闲话：暑假将尽，whk 全盘摆烂中。第一次那么快想出紫题。

## 题目大意
- 给定一个 $n$ 个点，$m$ 条边的无向连通图。
- 现在要求把每条边都定一个方向，该无向图将变为有向图。
- 定义一个点的权值 $R_i$ 是其能到达的点 $X$ 的个数（包括自身）。
- 求 $\min R_i$ 的最大值，并给出边的定向方案。

## 解题思路
我们知道，在一个边双连通分量中，任意两点 $x,y$ 之间都至少有两条路径，记录为 $P_1,P_2$。这启示我们，可以把 $P_1$ 定向为 $x$ 到 $y$，把 $P_2$ 定向为 $y$ 到 $x$。因此**边双缩点**的思想得以在本题中运用。

考虑一个无向连通图的 dfs 生成树。

![](https://cdn.luogu.com.cn/upload/image_hosting/yap8pges.png)

红色的边是树边，其他边都是返祖边。
### 1. 同一个边双内
我们先考虑同一个边双连通分量中边的定向情况。可以发现，我们把**树边**定为**从父到子**，把**返祖边**定为**从子到祖先**，这种定向方法一定可以使得一个边双变为一个有向图中的**强连通分量**。

证明如下：由于强连通分量的定义是任意两点可以互相到达，我们只需要证明这样的构造能够出现一个**简单环**即可。

单独取出一个边双，我们定义：不能通过树边到达同一个边双中其他点的结点，称为**边双叶子结点**。对于一个边双叶子节点 $x$，它必然能够通过返祖边到达边双中的根节点 $rt$。

为什么呢？因为假设不能到达根节点 $rt$，那么 $x$ 和 $rt$ 之间就**只存在一条**由树边构成的路径了。回到开头的定义：边双连通分量中，任意两点 $x,y$ 之间都**至少有两条路径**。这就与题设不相符合了。

那么我们把返祖边都设定为从子到祖先，就一定能让这个边双变成一个强连通分量。原命题得证。

### 2. 不同边双之间
接下来，我们把边双内的所有点缩成一个点，留下由桥组成的一个新图。学过 Tarjan 的同学们一定知道，留下的新图是一棵树：边双树。

由于我们在第一部分已经证明，同一个边双中的任意两点，可以通过某种构造方案互相到达。那么我们现在的问题就转化成了：

- 给定一棵树 $T$，有 $n$ 个点（$n$ 就是边双连通分量的个数）。每个点有一个点权 $a_i$（这就是第 $i$ 个边双连通分量的大小）。

- 对所有树边进行重定向，使之成为一个有向图。

- 定义一个点的属性 $R_i$ 为它能到达的点的点权和。形式化的，设 $\{x_k\}$ 是点 $i$ 能到达的点的集合（包括自身），那么 $R_i=\sum a_{x_k}$。

- 给出构造方案使得 $\min R_i$ 最小。

1. 下面我将证明：$\min R_i\le \max a_i$。

树有一个性质，那就是有 $n$ 个点，$(n-1)$ 条边。这意味着什么呢？意味着对边定向之后，一定总共有 $(n-1)$ 个入度和 $(n-1)$ 个出度分配到 $n$ 个点中。

那么注定有一个点，它不会有任何出度。这个点最好情况下也就是 $a_i$ 最大的那个了。

因此 $\min R_i\le \max a_i$。

2. 下面我将证明并给出构造方案：$\min R_i=\max a_i$。

很简单，我们直接令这个 $a_i$ 最大的点 $i$ 为根节点 $root$。然后我们从它开始对这棵树进行深度优先遍历，把这些树边的方向定为**从子到父**就行了。

显然这样是正确的，因为这样的构造方法可以保证对于一条边连接的父子 $(fa,son)$，有着 $R_{son}>R_{fa}$。而 $R_{root}=a_{root}=\max a_i$。这就保证了对于任意的 $R_i$，有 $R_i\ge \max a_i$。

### 3. 总结回顾
这道题的解题过程是：
1. 读入，求出边双连通分量。
2. 在同一个边双中，把**树边**定为**从父到子**，把**返祖边**定为**从子到祖先**。
3. 进行边双连通分量的缩点，构造出边双树。
4. 求出点数最多的一个边双，以它为根节点在边双树中 dfs。把所有边的方向定位**从子到父**。
5. $\min R_i$ 的值就是 $\max a_{i'}$，即最大的边双连通分量的大小。

## 参考代码
很多人说我的图论写的很抽象，因此代码不方便直接展示，间接展示在[这里](https://www.luogu.com.cn/paste/9ivgvrd5)。

---

## 作者：2huk (赞：5)

- 给定一张 $n$ 个点 $m$ 条边的简单无向图，你需要给每条边都确定一个方向，使原图变成一个有向图。设 $R_i$ 为从 $i$ 号点出发能到达的不同点的数量。最大化所有 $R_i$ 的最小值。
- 输出这个最小值以及每条边的定向方案。
- $n , m \le 4 \times 10^5$。

首先根据 [
CF118E](https://www.luogu.com.cn/problem/CF118E) 的思路，一定存在一种为一个 dcc（边双连通分量）中所有边定向的方案，使其成为一个 scc（强连通分量）。具体见[这里](https://www.cnblogs.com/2huk/p/18162417)。

所以将所有 dcc 缩点，那么原图将成为一颗树，每个点的点权为这个点所代表的 dcc 的点数。接下来最优的构造方案是将点权最大的点作为这棵树的根，然后让其余边都从儿子指向父亲。容易证明这样是正确的。

---

## 作者：Mistletoes (赞：3)

因为知道了算法tag，所以想到了正解：

先给出两个性质：
 1. 边双给边定向一定可以转为强连通图,此为最优解
 2. 树给边定向后R的最小值必为0

性质2证明如下：
```
设树有n个节点,
若R_min!=0,
则每点出度至少为1,各点出度之和至少为n,
则至少有n条边,但树只有n-1条边,矛盾
```
那么这道题只要在原图上把边双缩成点即可

问题是如何构造？

要解决树的构造很简单，因为树上必有一点无法到达其它节点，而我们又要令R_min最大，那么就令这个无法到达其它节点的点为 **包含点的个数最多的边双** 代表的点 ，把这个点当做 **根节点** dfs这棵树，把树上的边（原图上的桥）定向为 **son—>fa**，可以保证R_min=根节点代表的边双包含点的个数

然后就是我想不到的了，边双内部要如何构造呢？

虽然我自己想了一种构造方法，但是T得十分惨烈……

然后，第二天我去学习了dfs树，发现这个问题变得很简单

这是我最后用的构造方案：
```cpp
void dfs(int u){
	vis[u]=1;
	for(int i=head[u];i!=-1;i=edge_nxt[i]){
		int v=edge_v[i];
		if(edge_br[i]){
			add_e(edge_u[i],edge_v[i],edge_id[i]);
			continue;
		}
		if(!aa[edge_id[i]]) aa[edge_id[i]]=u,bb[edge_id[i]]=v;//加判断是为了防止将定好向的(fa[u],u)边再反向 
		if(!vis[v]) dfs(v);
	}
}
```
为什么可行？

用dfs树理解，这个构造方案就是**将所有树边定向向下并将所有回边定向向上**，由dfs树的性质知这一定可行

最后放上完整代码：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<stack>
using namespace std;
const int N=4e5+5;
int edge_u[N<<1],edge_v[N<<1],edge_id[N<<1],edge_nxt[N<<1],edge_br[N<<1];
int n,m,head[N],cnt,a[N],b[N],aa[N],bb[N];
int dfn[N],low[N],ind,bcc[N],Bcc,bcc_sz[N];
stack<int> s;
void add_edge(int u,int v,int id){
	edge_u[cnt]=u;
	edge_v[cnt]=v;
	edge_id[cnt]=id;
	edge_nxt[cnt]=head[u];
	head[u]=cnt++;
}
void tarjan(int u,int fa){
	dfn[u]=low[u]=++ind;
	s.push(u);
	for(int i=head[u];i!=-1;i=edge_nxt[i]){
		int v=edge_v[i];
		if(!dfn[v]){
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>dfn[u]){
				edge_br[i]=1;
				edge_br[i^1]=1;
				Bcc++;
				int k;
				do{
					k=s.top();
					s.pop();
					bcc[k]=Bcc;
					bcc_sz[Bcc]++;
				}while(k!=v);
			}
		}
		else{
			if(dfn[v]<dfn[u]&&v!=fa)
				low[u]=min(low[u],dfn[v]);
		}
	}
	//勿忘考虑u为根的情况: 
	if(!fa){
		Bcc++;
		while(!s.empty()){
			bcc[s.top()]=Bcc;
			bcc_sz[Bcc]++;
			s.pop();
		}
	}
}
int e_u[N<<1],e_v[N<<1],e_id[N<<1],e_nxt[N<<1];
int hd[N],ct;
void add_e(int u,int v,int id){
	e_u[ct]=u;
	e_v[ct]=v;
	e_id[ct]=id;
	e_nxt[ct]=hd[bcc[u]];//highlight
	hd[bcc[u]]=ct++;//highlight
}
int num,maxn=0;
bool vis_bcc[N],vis[N];
void dfs(int u){
	vis[u]=1;
	for(int i=head[u];i!=-1;i=edge_nxt[i]){
		int v=edge_v[i];
		if(edge_br[i]){
			add_e(edge_u[i],edge_v[i],edge_id[i]);
			continue;
		}
		if(!aa[edge_id[i]]) aa[edge_id[i]]=u,bb[edge_id[i]]=v;//加判断是为了防止将定好向的(fa[u],u)边再反向 
		if(!vis[v]) dfs(v);
	}
}
void dfs2(int u,int fa){
	for(int i=hd[u];i!=-1;i=e_nxt[i]){
		int v=bcc[e_v[i]];
		if(v==fa) continue;
		aa[e_id[i]]=e_v[i],bb[e_id[i]]=e_u[i];
		dfs2(v,u);
	}
}
int main(){
	memset(head,-1,sizeof(head));
	memset(hd,-1,sizeof(hd));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a[i],&b[i]);
		add_edge(a[i],b[i],i);
		add_edge(b[i],a[i],i);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i]) tarjan(i,0);
	for(int i=1;i<=n;i++){
		if(!vis_bcc[bcc[i]]){
			dfs(i);
			vis_bcc[bcc[i]]=1;
			if(bcc_sz[bcc[i]]>maxn){
				maxn=bcc_sz[bcc[i]];
				num=bcc[i];
			}
		}
	}
	dfs2(num,0);
	printf("%d\n",maxn);
	for(int i=1;i<=m;i++){
		if(aa[i]&&bb[i]) printf("%d %d\n",aa[i],bb[i]);
		else printf("%d %d\n",a[i],b[i]);
	}
	return 0;
}  
```


---

## 作者：i207M (赞：2)

![](https://cdn.luogu.com.cn/upload/pic/22702.png)

学习到了一发Tarjan缩边双；

数组开大点……

```
		if (vis[v[i]]) {
            au[i >> 1] = x;
            av[i >> 1] = v[i];
            continue;
        }
```

这句话很重要，因为DFS定向时，遇到了环，一定要让环接上；

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<stack>
#include<bitset>
#include<deque>
using namespace std;
#define ll long long
#define inf 0x3f3f3f3f
#define ri register int
#define il inline
#define fi first
#define se second
#define mp make_pair
#define pi pair<int,int>
#define mem0(x) memset((x),0,sizeof (x))
#define mem1(x) memset((x),0x3f,sizeof (x))
#define gc getchar
#define pb push_back
template<class T>void in(T &x)
{
    x = 0; bool f = 0; char c = gc();
    while (c < '0' || c > '9') {if (c == '-') f = 1; c = gc();}
    while ('0' <= c && c <= '9') {x = (x << 3) + (x << 1) + (c ^ 48); c = gc();}
    if (f) x = -x;
}
#undef gc
#define N 1000100
#define M N<<1
int n, m;
int v[M], u[M], nx[M];
int cnt = 1, head[N];
il void add(int uu, int vv) {
    u[++cnt] = uu, v[cnt] = vv, nx[cnt] = head[uu];
    head[uu] = cnt;
}
int cv[M], cu[M], cnx[M];
int cn = 1, ch[N];
il void cadd(int uu, int vv) {
    cu[++cn] = uu, cv[cn] = vv, cnx[cn] = ch[uu];
    ch[uu] = cn;
}
int low[N], dfn[N], dfc;
int mx, rt;
int st[N], top;
bool ins[N];
int au[M], av[M];
void tarjan(int x, int fe) {
    low[x] = dfn[x] = ++dfc;
    st[++top] = x;
    ins[x] = 1;
    //printf("V %d %d %d\n", x, dfn[x], dfc);
    for (ri i = head[x]; i; i = nx[i]) {
        if (i == fe) continue;
        if (!dfn[v[i]]) {
            tarjan(v[i], i ^ 1);
            low[x] = min(low[x], low[v[i]]);
        }
        else if (ins[v[i]]) {
            low[x] = min(low[x], dfn[v[i]]);
        }
    }
    if (low[x] == dfn[x]) {
        int sz = 0;
        //printf("LT ");
        while (st[top + 1] != x) {
            sz++;
            ins[st[top]] = 0;
            //printf("%d ", st[top]);
            top--;
        }
        //puts("");
        if (sz > mx) mx = sz, rt = x;
    }
}
/*int uni[N];
int nc;
il int getn(int x) {
    return lower_bound(uni + 1, uni + 1 + nc, x) - uni;
}*/
bool vis[N];
//vector<int> bs[N];
/*void dfs(int x, int k) {
    vis[x] = 1;
    bs[k].pb(x);
    for (ri i = head[x]; i; i = nx[i]) {
        if (vis[v[i]] || low[v[i]] != k) continue;
        else {
            au[i >> 1] = x;
            av[i >> 1] = v[i];
            dfs(v[i], k);
        }
    }
}*/
void dfs2(int x) {
    vis[x] = 1;
    for (ri i = head[x]; i; i = nx[i]) {
        if (vis[v[i]]) {
            au[i >> 1] = x;
            av[i >> 1] = v[i];
            continue;
        }
        if (low[v[i]] != low[x]) {
            au[i >> 1] = v[i];
            av[i >> 1] = x;
        }
        else {
            au[i >> 1] = x;
            av[i >> 1] = v[i];
        }
        dfs2(v[i]);
    }
}
signed main() {
    in(n), in(m);
    for (ri i = 1, a, b; i <= m; ++i) {
        in(a), in(b);
        //au[i] = a, av[i] = b;
        add(a, b);
        //kk[cnt] = i;
        add(b, a);
        //kk[cnt] = i;
    }
    tarjan(1, 0);
    /*memcpy(uni, low, sizeof uni);
    sort(uni + 1, uni + 1 + n);
    nc = unique(uni + 1, uni + 1 + n) - uni - 1;*/
    /*for (ri i = 1; i <= n; ++i) {
        printf("T %d %d %d\n", i, dfn[i], low[i]);
    }
    for (ri i = 1; i <= n; ++i) {
        if (!vis[i]) {
            dfs(i, low[i]);
        }
    }
    int mxn = 1;
    for (ri i = 2; i <= n; ++i) {
        if (bs[i].size() > bs[mxn].size()) mxn = i;
    }
    q.push(mxn);
    mem0(vis);
    //dfs2(mxn, low[mxn]);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        dfs2(x);
    }*/
    printf("%d\n", mx);
    dfs2(rt);//cout<<"A";
    for (ri i = 1; i <= m; ++i) {
        printf("%d %d\n", au[i], av[i]);
    }
    return 0;
}

```

---

## 作者：Richard_Whr (赞：1)

根据：[CF118E Bertown roads](https://www.luogu.com.cn/problem/CF118E) 的结论，知道了边双内部可以重定向为强连通，具体方案就是 dfs 的方向。

缩边双，得到一颗树。

看到最小值最大，考虑二分。

然后就直接贪心了，从叶子开始考虑问题，如果叶子能自治，那就把边指向父亲，这样父亲可以得到更多。

否则只能让父亲来支援自己。

对于非叶子，有些儿子节点可以提供点数，有些叶子需要点数，自己也需要点数。

注意到如果能满足自己的需求那么一定能满足需要点数的儿子的需求，因为他们已经将边指向了当前点，当前点能到的他们一定能到。

将可以提供点数的儿子提供的点数求和加上自己联通分量的大小，查看能否满足自己的需求即可。

最后查看根节点是不是仍然需要点数来判断。

感觉思路比直接想到选最大值更自然。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> PII;
const int N=4e5+10,M=N*2;
int h[N],e[M],ne[M],idx;
vector<PII> son[N]; 
bool st[M];
int dfn[N],low[N],ts;
int stk[N],top;
int id[N],sz[N],dcc;
int n,m;
int Lim;

inline void mark(int i)
{
	if(!st[i^1]) st[i]=true;
}

void tarjan(int u,int from)
{
	dfn[u]=low[u]=++ts,stk[++top]=u;
	for(int i=h[u];~i;i=ne[i])
	{
		int v=e[i];
		if(!dfn[v])
		{
			tarjan(v,i);
			mark(i);
			low[u]=min(low[u],low[v]);
		}
		else if(i!=(from^1)) low[u]=min(low[u],dfn[v]),mark(i);
	}
	if(low[u]==dfn[u])
	{
		int y;dcc++;
		do
		{
			y=stk[top--];
			id[y]=dcc;
			sz[dcc]++;
		}while(y!=u);
	}
}

int Dfs(int u,int fa)
{
	int siz=sz[u],minv=-Lim;
	for(auto it:son[u])
	{
		int v=it.first,w=it.second;
		if(v==fa) continue;
		int t=Dfs(v,u);
		if(t>=0) siz+=t,st[w]=true,st[w^1]=false;
		else st[w^1]=true,st[w]=false;
	}
	minv+=siz;
	if(minv<0) return minv;
	return siz;
}

bool check(int x)
{
	Lim=x;
	return Dfs(1,0)>=0;
}

void add(int a,int b)
{
	e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	
	memset(h,-1,sizeof h);
	cin>>n>>m;
	
	while(m--)
	{
		int a,b;
		cin>>a>>b;
		add(a,b),add(b,a); 
	}
	
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i,-1);
	
	for(int u=1;u<=n;u++)
	{
		for(int i=h[u];~i;i=ne[i])
		{
			int v=e[i];
			if(id[u]!=id[v])
			{
				st[i]=false;
				son[id[u]].push_back({id[v],i});
			}
		}
	}
	
	int l=1,r=n,ans=0;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(check(mid)) ans=mid,l=mid+1;
		else r=mid-1; 
	}
	
	check(ans);
	cout<<ans<<"\n";
	
	for(int i=0;i<idx;i++) if(st[i]) cout<<e[i^1]<<" "<<e[i]<<"\n";
	
	return 0;
}
```

---

## 作者：Priestess_SLG (赞：0)

可以证明每个边双都可以通过给边定向使得点对之间两两可达。因此对图跑边双缩点，那么剩下一个带点权的树。让树根为点数最大的结点，其余点全部指向父亲一定最优。因此做完了。

具体来说：对于新建的缩点后的树，直接从根节点往叶子结点连；对于每一个强连通分量直接在上面 dfs 出一棵树然后剩下的全部连返祖边即可。

代码，但是带一只 $\log$。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
// #define int long long
using namespace std;
const int N = 400010;
const int mod = 1e9 + 7;
vector<pair<int, int>> adj[N];
pair<int, int> id[N<<1];
int dfn[N], low[N], fa[N], bel[N];
int idx; set<pair<int, int>> bri;
void dfs(int u, int idd) {
    dfn[u] = low[u] = ++idx;
    for (auto &[v, w] : adj[u])
        if (!dfn[v]) {
            dfs(v, w);
            low[u] = min(low[u], low[v]);
            if (dfn[u] < low[v]) bri.emplace(id[w]), bri.emplace(id[w^1]);
        } else if (w != (idd^1)) low[u] = min(low[u], dfn[v]);
}
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}
void Merge(int x, int y) {
    x = find(x), y = find(y);
    if (x != y) fa[x] = y;
}
int siz[N];
vector<int> adj2[N], adj3[N];
vector<pair<int, int>> eres;
vector<int> scc[N];
int depth[N];
void dfs2(int u, int fa) {
    depth[u] = depth[fa] + 1;
    for (int &v : adj2[u])
        if (v != fa) dfs2(v, u);
}
set<pair<int, int>> use;
int vis[N], dep[N];
void dfs3(int u, int fa = 0) {
    vis[u] = 1;
    dep[u] = dep[fa] + 1;
    for (int &v : adj3[u])
        if (!vis[v]) {
            eres.emplace_back(u, v);
            use.emplace(u, v);
            use.emplace(v, u);
            dfs3(v, u);
        }
}
pair<int, int> rres[N];
map<pair<int, int>, int> back;
int tb[N];
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].emplace_back(b, i << 1);
        adj[b].emplace_back(a, i << 1 | 1);
        id[i << 1] = {a, b};
        id[i << 1 | 1] = {b, a};
        back[{a, b}] = back[{b, a}] = i;
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i]) dfs(i, 0);
    iota(fa, fa + n + 1, 0);
    for (int i = 2; i <= m + m + 1; ++i) {
        auto [x, y] = id[i];
        if (!bri.count({x, y})) Merge(x, y);
    }
    for (int i = 1; i <= n; ++i) bel[i] = find(i);
    for (int i = 1; i <= n; ++i) tb[i] = bel[i];
    sort(tb + 1, tb + n + 1);
    int index = unique(tb + 1, tb + n + 1) - tb - 1;
    for (int i = 1; i <= n; ++i) bel[i] = lower_bound(tb + 1, tb + index + 1, bel[i]) - tb;
    idx = index;
    for (int i = 1; i <= n; ++i) ++siz[bel[i]];
    int mx = -1, idd = -1;
    for (int i = 1; i <= idx; ++i)
        if (mx < siz[i]) mx = siz[i], idd = i;
    for (int i = 2; i <= m + m + 1; ++i) {
        auto [x, y] = id[i];
        if (bel[x] != bel[y]) adj2[bel[x]].emplace_back(bel[y]);
    }
    cout << siz[idd] << '\n';
    dfs2(idd, 0);
    for (int i = 1; i <= n; ++i) scc[bel[i]].emplace_back(i);
    for (int i = 1; i <= idx; ++i) {
        if (scc[i].empty()) continue;
        for (int &j : scc[i])
            for (auto &[k, o] : adj[j])
                if (bel[j] == bel[k]) adj3[j].emplace_back(k);
        use.clear();
        dfs3(scc[i][0]);
        for (int &j : scc[i])
            for (auto &[k, o] : adj[j])
                if (bel[j] == bel[k])
                    if (!use.count({j, k})) {
                        if (dep[j] <= dep[k]) eres.emplace_back(k, j);
                        else eres.emplace_back(j, k);
                    }
        for (int &j : scc[i]) adj3[j].clear(), vis[j] = 0;
    }
    for (int i = 1; i <= idx; ++i)
        for (int j : adj2[i]) {
            assert(i != j);
            int ti = i;
            if (depth[i] < depth[j]) swap(i, j);
            // i --> j
            for (int &k : scc[i])
                for (auto &[p, o] : adj[k])
                    if (bel[p] == j) {
                        eres.emplace_back(k, p);
                        goto label;
                    }
            label:;
            i = ti;
        }
    sort(eres.begin(), eres.end());
    eres.erase(unique(eres.begin(), eres.end()), eres.end());
    for (auto &[x, y] : eres) {
        int id = back[{x, y}];
        rres[id] = {x, y};
    }
    for (int i = 1; i <= m; ++i) cout << rres[i].first << ' ' << rres[i].second << '\n';
    return 0;
}


```

---

## 作者：songxr111 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF732F)

~~闲话：第一次这么快写出紫题~~

# 题目大意
- 给定一张 $n$ 个点 $m$ 条边的无向连通图，你需要对每一条边进行定向。
- 定向后，最大化所有点能到达的点数的最小值并输出方案。
- $n, m \le 4 \times 10$。

# 解题思路
由 [CF118E](https://www.luogu.com.cn/problem/CF118E) 得，为了让所有点尽量可以互相到达，可以使用 tarjan 算法，求出割边（桥）。对于不是割边的其他边来说，在 tarjan 中顺带求出的 dfs 树上，树边可以从祖先连向后代，非树边由后代连向祖先（dfs 树没有横叉边哈）。

于是乎这样就解决了非割边。

既然有了割边，就有了边双联通分量；有了边双联通分量，就可以缩点；缩了点，图就成了树。

对于一棵树，我们可以把所有边集中指向一个点（根），这样大家都可以到这个点。这样的话，所有点能到达的点数的最小值就是这个点（在原图中其实是边双）的大小。则所求变为最大边双的大小。

~~由于本人非常蒻不知道怎么统计边双大小于是使用了并查集维护 size~~

# 代码

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
#define ge getchar
#define pu putchar
using namespace std;
const int N = 4e5+5;
struct edge{//邻接表的边
    int to, id;
};
struct Edge{//用数组存的边
    int st, end, id;
    bool operator<(const Edge & other)const{
        return id < other.id;
    }
} ans[N], cut[N];
struct orded_edge{//被并查集替换过的树上割边
    int _st, to, _to, id;
};
vector<edge> g[N];
vector<orded_edge> tree[N];
int n, m, u, v, dfn[N], low[N], tim, anst, cutt, maxp, maxsz;
namespace bcj{//装*之并查集
    int fa[N], siz[N];
    void init(){
        for (int i=1;i<=n;i++) fa[i]=i, siz[i]=1;
    }
    int find(int x){
        return x==fa[x]?x:fa[x]=find(fa[x]);
    }
    void merge(int x, int y){
        int u = find(x);
        int v = find(y);
        if (u!=v){
            fa[u] = v;
            siz[v]+=siz[u];//维护size
        }
    }
}
using namespace bcj;
//快读快写请忽略
void read(int &x){
    x=0;char ch=ge();
    while ('0'>ch||ch>'9') ch=ge();
    while ('0'<=ch&&ch<='9'){
        x=x*10+ch-'0';
        ch=ge();
    }
}
void write(int x){
    if (x>9) write(x/10);
    pu(x%10+'0');
}
void tarjan(int now, int fa){
    dfn[now]=low[now]=++tim;
    for (auto i:g[now]){
        if (!dfn[i.to]){
            tarjan(i.to, now);
            if (low[i.to]>dfn[now]){//割边
                cut[++cutt] = Edge{now, i.to, i.id};//存进割边数组
            } 
            else {//正常边
                ans[++anst] = Edge{now, i.to, i.id};//存入答案
                merge(now, i.to);//加入并查集
            }
            low[now] = min(low[now], low[i.to]);
        }
        else if (i.to!=fa){//正常边
            merge(now, i.to);//加入并查集
            low[now] = min(low[now], dfn[i.to]);
            if (dfn[now]>dfn[i.to]) ans[++anst] = Edge{now, i.to, i.id};//返祖边存入答案
        }
    }
}
void dfs(int now, int fa){//树上dfs
    for (auto i:tree[now]){
        if (i.to!=fa){
            ans[++anst] = Edge{i._to, i._st, i.id};//从儿子到父亲的方向记录答案
            dfs(i.to, now);
        }
    }
}
int main(){
    read(n), read(m);
    init();//勿忘初始化并查集
    for (int i=1;i<=m;i++){
        read(u), read(v);
        //可恶的题目让我们按输入顺序输出
        //我们不得不记录一下输入时的id，最后排序
        g[u].push_back(edge{v, i});
        g[v].push_back(edge{u, i});
    }
    tarjan(1, -1);
    for (int i=1;i<=n;i++){//寻找最大size和它的边双的并查集
        if (fa[i]==i&&siz[i]>maxsz){
            maxsz = siz[i];
            maxp = i;
        }
    }
    write(maxsz), pu('\n');
    for (int i=1;i<=cutt;i++){//建树
        int fx = find(cut[i].st);
        int fy = find(cut[i].end);
        tree[fx].push_back(orded_edge{cut[i].st, fy, cut[i].end, cut[i].id});
        tree[fy].push_back(orded_edge{cut[i].end, fx, cut[i].st, cut[i].id});
    }
    dfs(maxp, -1);
    sort(ans+1, ans+1+anst);
    for (int i=1;i<=anst;i++){
        write(ans[i].st), pu(' ');
        write(ans[i].end), pu('\n');
    }
    return 0;
}
```

完结撒花！

---

## 作者：Loser_Syx (赞：0)

发现是边双内的点定向其中相连的边，可以做到互相到达，且对非此边双内的点无影响，那么可以考虑对原图缩完点之后的每个边双进行决策。

由于每两个边双之间是无法互相抵达的，那么缩完点后的图一定构成了一棵树。其中树根不会被其他边双到达。

考虑让 $size$ 最大的点当树根。那么树根上的答案会最大，且其他边双都最起码有它那么多个点。

[code](https://codeforces.com/contest/732/submission/288726382)。

---

## 作者：yangshengyu0719 (赞：0)

# 思路
首先这题可以看出与双连通分量有关，对于每个双连通分量内一定存在一种构造方式使得双连通分量内每个点都能互相到达，思路可以借鉴 [CF118E](https://www.luogu.com.cn/problem/CF118E)。

然后看到最小值最大化，考虑二分答案加贪心。我们知道无向图缩点后一定是一棵树，$size$ 大于当前二分值 $lim$ 的双连通分量一定尽量为叶节点，小于当前二分值 $lim$ 的双连通分量一定深度尽量尽量小。由此联想到哈夫曼树的构造方式，我们开一个大根堆维护 $r_i$，若堆顶小于 $lim$ 一定不存在构造方式，否则用堆顶的值更新相连的点的 $r_i$，同时记录连边。（有点像 dijkstra）。

# 代码
```cpp
#include <bits/stdc++.h>
#define PII pair<int,int>
using namespace std;
const int N=4e5+5;
int n,m,DFN[N],Low[N],sign;
int st[N],top,ins[N],tot,bl[N],sz[N],r[N];
int vis[N],vis2[N];
struct Edge{int to,id;};
struct Edges{int u,v;}e[N];
vector<Edge> E[N],E2[N];
void Tarjan(int x,int fa){
	DFN[x]=Low[x]=++sign;
	st[++top]=x,ins[x]=1;
	for(Edge v:E[x])
		if(v.to!=fa){
			if(!DFN[v.to]) Tarjan(v.to,x),Low[x]=min(Low[x],Low[v.to]);
			else if(ins[v.to]) Low[x]=min(Low[x],DFN[v.to]);
		}
	if(DFN[x]==Low[x]){
		int t;++tot;
		do{ t=st[top--];
			sz[bl[t]=tot]++;
		}while(top>0&&t!=x);
	}
}
bool check(int lim){
	priority_queue<PII> q;
	for(int i=1;i<=tot;i++) q.push({sz[i],i}),r[i]=sz[i];
	memset(vis2,0,sizeof vis2);
	memset(vis,0,sizeof vis);
	while(!q.empty()){
		int x=q.top().second;q.pop();
		if(vis[x]) continue;
		vis[x]=1;
		if(r[x]>=lim){
			for(Edge v:E2[x])
				if(!vis2[v.id]){
					r[v.to]+=r[x],q.push({r[v.to],v.to});
					if(v.to!=bl[e[v.id].u]) swap(e[v.id].u,e[v.id].v);
					vis2[v.id]=1;
				}
		}else return 0;
	}
	return 1;
}
void dfs(int x,int fa,int BL){
	vis[x]=1;
	for(Edge v:E[x]){
		if(bl[v.to]!=BL) continue;
		if(!vis2[v.id]) e[v.id]={x,v.to},vis2[v.id]=1;
		if(!vis[v.to]) dfs(v.to,x,BL);
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;cin>>u>>v;
		E[u].push_back({v,i});
		E[v].push_back({u,i});
		e[i]={u,v};
	}
	for(int i=1;i<=n;i++)
		if(!DFN[i]) Tarjan(i,0);
	for(int u=1;u<=n;u++)
		for(Edge v:E[u])
			if(bl[u]!=bl[v.to])
				E2[bl[u]].push_back({bl[v.to],v.id});
	for(int i=1;i<=n;i++)
		if(!vis[i]) dfs(i,0,bl[i]);
	int l=0,r=n+1;
	while(l<r){
		int mid=(l+r)>>1;
		if(check(mid)) l=mid+1;
		else r=mid;
	}
	cout<<l-1<<"\n";
	for(int i=1;i<=m;i++) cout<<e[i].u<<' '<<e[i].v<<'\n'; 
	return 0;
}
//一个双连通分量中的边改为单向后一定存在一种方式使得双连通分量中的点能互相到达 
```

---

## 作者：鱼跃于渊 (赞：0)

# 题意  
给定一个由 $n$ 个点、 $m$ 条边组成的无向图，要把每条边定向，求定向后每个点能到达的点的数量的最小值和定边方案。  
# 分析  
首先我们可以发现，属于同一个边双的两个点是可以互达的。考虑缩点，这样就得到了一棵树。然后我们又可以发现，在这棵树上，至少有一个点不能够到达其他点。考虑贪心，把最大的边双设成这个点，容易证明这是最优解。这样一来答案就是最大边双的大小。  
那么怎么定向呢？我们从最大边双中任取一点开始 dfs ,如果当前的边没被记录，就记录它的反边。为什么这是正确的呢？我们可以发现它的本质其实就是将所有树边定向向下，将所有非树边定向向上。  
# 代码  
```
#include <bits/stdc++.h>
using namespace std;
const int N=4e5+5,M=1e6+5;
struct edge{
	int u,v,nxt;
}e[M];
int cnt=1,head[N];
int n,m,ans[M];
int top,s[M];
int tot,low[N],dfn[N];
int dcnt,dcc[N],siz[N]; 
bool vis[N];
void add(int u,int v){
	e[++cnt]={u,v,head[u]};
	head[u]=cnt;
}
void tarjan(int u,int fa){
	low[u]=dfn[u]=++tot;
	s[++top]=u;vis[u]=1;
	for(int i=head[u],v;i;i=e[i].nxt){
		v=e[i].v;
		if(v==fa) continue;
		if(!dfn[v]){
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
		}else if(vis[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		dcnt++;
		do{
			dcc[s[top]]=dcnt;
			siz[dcnt]++;
			vis[s[top]]=0;
		}while(u!=s[top--]);
	}
}
void dfs(int u,int fa){
	vis[u]=1;
	for(int i=head[u],v;i;i=e[i].nxt){
		v=e[i].v;
		if(v==fa) continue;
		if(!ans[i/2]) ans[i/2]=i^1;
		if(!vis[v])	
			dfs(v,u);
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i]) tarjan(i,0);
	int tp=0;
	for(int i=1;i<=n;i++)
		if(siz[dcc[i]]>siz[dcc[tp]])
			tp=i;
	memset(vis,0,sizeof(vis));
	dfs(tp,0);
	cout<<siz[dcc[tp]]<<'\n';
	for(int i=1;i<=m;i++)
		cout<<e[ans[i]].u<<' '<<e[ans[i]].v<<'\n';
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

首先，一个边双的内部一定是可以联通相互到达的。

那么我们对边双缩点，就能得到一棵树，此时一定至少有一个点不能到达其它的点。贪心地，将这个点选作最大的边双。那么只需要让其它边双一直向上就能达到这个边双了。

构造方案：

以边双为根节点向下搜索，最后全部取反即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=4e5+5;
int n,m,tot,cnt[maxn],_[maxn],u[maxn],v[maxn],fa[maxn],dfn[maxn],low[maxn];
bool flg[maxn],vis[maxn];
struct node{
	int to,id;
};
vector<node> G[maxn];
void Tarjan(int u,int fa){
	dfn[u]=low[u]=++tot;
	for(auto N:G[u]){
		int v=N.to,id=N.id;
		if(!dfn[v]){
			Tarjan(v,u);
			if(low[v]>dfn[u])
				flg[id]=1;
			low[u]=min(low[u],low[v]);
		} else if(v!=fa)
			low[u]=min(low[u],dfn[v]);
	}
}
int Find(int x){
	return fa[x]=(fa[x]==x?x:Find(fa[x]));
}
void dfs(int U){
	vis[U]=1;
	for(auto N:G[U]){
		int V=N.to,id=N.id;
		if(~_[id])
			continue;
		if(U==u[id])
			_[id]=0;
		else
			_[id]=1;
		if(!vis[V])
			dfs(V);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i){
		scanf("%d%d",&u[i],&v[i]);
		G[u[i]].push_back(node({v[i],i}));
		G[v[i]].push_back(node({u[i],i}));
	}
	for(int i=1;i<=n;++i)
		if(!dfn[i])
			Tarjan(i,0);
	for(int i=1;i<=n;++i)
		fa[i]=i;
	for(int i=1;i<=m;++i)
		if(!flg[i])
			fa[Find(u[i])]=Find(v[i]);
	for(int i=1;i<=n;++i)
		++cnt[Find(i)];
	int res=0;
	for(int i=1;i<=n;++i)
		if(cnt[i]>cnt[res])
			res=i;
	memset(_,-1,sizeof(_));
	dfs(res);
	printf("%d\n",cnt[res]);
	for(int i=1;i<=m;++i)
		if(_[i])
			printf("%d %d\n",u[i],v[i]);
		else
			printf("%d %d\n",v[i],u[i]);
	return 0;
}
```

---

