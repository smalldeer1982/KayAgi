# Simple Cycles Edges

## 题目描述

You are given an undirected graph, consisting of $ n $ vertices and $ m $ edges. The graph does not necessarily connected. Guaranteed, that the graph does not contain multiple edges (more than one edges between a pair of vertices) or loops (edges from a vertex to itself).

A cycle in a graph is called a simple, if it contains each own vertex exactly once. So simple cycle doesn't allow to visit a vertex more than once in a cycle.

Determine the edges, which belong to exactly on one simple cycle.

## 样例 #1

### 输入

```
3 3
1 2
2 3
3 1
```

### 输出

```
3
1 2 3 
```

## 样例 #2

### 输入

```
6 7
2 3
3 4
4 2
1 2
1 5
5 6
6 1
```

### 输出

```
6
1 2 3 5 6 7 
```

## 样例 #3

### 输入

```
5 6
1 2
2 3
2 4
4 3
2 5
5 3
```

### 输出

```
0

```

# 题解

## 作者：泥土笨笨 (赞：20)

提供一个不用 `set` 也不用差分的 `tarjan` 的做法吧，应该是比较好理解的。

题意是在一个无向图上，找到所有只在一个简单环上的边。因为简单环是不能经过同一个点两次的，所以我们可以看出来，环是不能穿过割点的。那么我们可以跑一遍 `tarjan` ，把割点和点双连通分量求出来，每个点双连通分量是可以单独考虑的。不同的点双连通分量之间互不影响。比如对于下面的图， `1` 是割点， `1 2 3` 是一个点双连通分量，这里面只有一个简单环。 `1 4 5 6` 是一个点双连通分量，它里面不只有一个环。它们相互独立，可以单独考虑。

![](https://cdn.luogu.com.cn/upload/image_hosting/nuel78eb.png)

那么对于一个点双连通分量，怎么知道里面哪些边是只在一个环里的呢？其实只要一个点双连通分量里面不止有一个环，那么每条边都可以在不止一个环里面。所以其实问题变成，求出每个点双，判断这个点双里面是不是只有一个环。只有一个环等价于这个点双里面点的个数等于边的条数。

那么如何求点双内部点的个数和边的条数呢？我们在跑 `tarjan` 的时候，定义两个栈，一个叫 `sv` ，把沿途经过的点都存下来。一个叫 `se` ，把沿途经过的边都存下来。每当发现一个点双的时候，就把这两个栈里面的点和边都 `pop` 出来，数一数个数是不是相等就行了。

具体的实现方式中，我看到有题解是用 `set` 来判边是不是重复，因为无向图是正反双向插入边，那么有可能一条边被放到 `se` 里面两次了，所以需要去重。其实这个是没有必要的，我们在 `tarjan` 的时候，加一个判断，只有走到一个没访问过的点，或者是从一个点走回祖先的时候，才插入到 `se` 里。如果是一个点往一个已经访问过的儿子方向走的边，我们就不插入了。这样可以保证每条边只插入栈一次，也就不用 `set` 了，节约了一个 `log` 的复杂度。

具体实现细节可以参考代码里面的注释

```cpp
#include <iostream>
#include <stack>

using namespace std;
const int MAXN = 1e5 + 5;
struct Node {
    int v, id, next;
} pool[MAXN << 1];
int n, m, head[MAXN], pre[MAXN], low[MAXN], nn, dt;
int fa[MAXN];//每个点往父亲方向走的边

void addEdge(int u, int v, int id) {
    pool[++nn].v = v;
    pool[nn].id = id;
    pool[nn].next = head[u];
    head[u] = nn;
}

stack<int> sv;//tarjan经过的每个点
stack<int> se;//tarjan经过的边的编号
int vis[MAXN];//当前点双连通分量里面经过的边
int ans[MAXN];//每个是答案的边，标记一下

void tarjan(int u) {
    sv.push(u);
    low[u] = pre[u] = ++dt;
    for (int i = head[u]; i; i = pool[i].next) {
        int v = pool[i].v;
        int id = pool[i].id;
        if (pre[v] == 0) {
            fa[v] = id;
            se.push(id);
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if (low[v] >= pre[u]) {
                //找到一个点双，统计这个点双里面点的个数和边的条数，如果点和边相等，说明只有一个环
                int cntV = 1;//点的个数，肯定包含割点自己
                int cntE = 0;//边的个数
                while (true) {
                    int t = sv.top();
                    sv.pop();
                    cntV++;
                    if (t == v) break;
                }
                while (true) {
                    int t = se.top();
                    se.pop();
                    vis[cntE++] = t;
                    if (t == fa[v]) break;
                }
                if (cntV == cntE) {
                    //只有一个环，标记一下
                    for (int j = 0; j < cntE; j++) {
                        ans[vis[j]] = 1;
                    }
                }
            }
        } else if (id != fa[u]) {
            low[u] = min(low[u], pre[v]);
            if (pre[v] < pre[u]) {
                //反向边进栈，其他边不进，保证不重复
                se.push(id);
            }
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        addEdge(u, v, i);
        addEdge(v, u, i);
    }
    for (int i = 1; i <= n; ++i) {
        if (pre[i] == 0) {
            tarjan(i);
        }
    }
    int cnt = 0;
    for (int i = 1; i <= m; ++i) {
        if (ans[i] == 1) cnt++;
    }
    cout << cnt << endl;
    for (int i = 1; i <= m; ++i) {
        if (ans[i] == 1) {
            cout << i << " ";
        }
    }
    cout << endl;
    return 0;
}
```


---

## 作者：_stellar (赞：9)

### 前置芝士：

我们如下定义：

$\large\texttt{DFS树}$：对于无向连通图G，在dfs过程中与原点集构成的生成树即为DFS树。

$\large\texttt{返祖边}$：在一个由树边和非树边组成的集合$E$中，对于任意$u,v∈E$，都满足$u,v$为父子或子父的关系的边，称为返祖边。

$\large\texttt{简单环}$：不经过重复边的环。

那么可有性质：在$E$中，非树边均为返祖边。所以在问题处理时，**所有的边都在一个子树内**。



------------
### 简单环的研究：

如图：有两个简单环相交于链$4-5$上

![](https://cdn.luogu.com.cn/upload/pic/71111.png )

对于$1-4-5$，$0-4-5$都自成一个简单环。

但是显然，对于大环$0-1-4-5$也成为一个简单环。

换句话说，**对于两个相交的简单环，总是可以拓展成新的简单环。**

根据题意说明，我们发现，**要使一个边恰好在一个简单环内，那么对应的两个简单环不能相交，否则所在简单环数$++$**。

而根据返祖边的性质，**两个简单环的相交处一定在树上**，那么问题就转换成了边的覆盖。

也就是说，我们将统计**两个简单环是否相交**转换为**两个简单环中的某一部分是否相交**。在这里我们为了方便，默认为判断返祖边是否相交，其中返祖边集为简单环拆去非树边的一条链（环=链+边）。

那么思路就出来了，**对于每一个简单环，我们将它的返祖边覆盖在原图上**，最后总计没有被覆盖到的区域一定符合题意。

对于树上染色，使用树上差分进行染色。对于一条返祖边$u-v$进行差分，最后差分数组元素为$1$的即为未覆盖区域。

时间复杂度$O$($n+m$)。

代码就不给了，看[caoyang1123](https://cdn.luogu.com.cn/upload/pic/71111.png )的吧。


---

## 作者：Juanzhang (赞：6)

[$\verb|CF962F Simple Cycles Edges|$](https://www.luogu.org/problemnew/show/CF962F)

> 给定一个无向图，求有多少条边仅被包含在一个简单环内并输出
>
> $n,\ m\leq10^5$

tarjan

------

首先，一个连通块是一个环，当且仅当该连通块的 点数=边数

可以发现，如果两个环仅由一个公共点连接，那么这两个环互不影响，即点双两两互不影响。

所以我们可以考虑处理出点双和每个点双内的边数

但是求出点双后暴力dfs会被如下数据卡掉：

```
66667 99999
1 2
1 3
2 3
1 4
1 5
4 5
1 6
1 7
6 7
...
```

因为 $1$ 节点每次枚举所有边的效率太低

于是可以在tarjan时将所有边压入栈中，再用set统计点双中的边数以及答案并去重

代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define nc getchar()
const int maxn = 1e5 + 10;
int n, m, tot, top, h[maxn], dfn[maxn], low[maxn], st[maxn * 3];
struct edges {
  int nxt, to;
} e[maxn << 1];
set <int> ans, edge[maxn], node[maxn];

inline int read() {
  int x = 0; char c = nc;
  while (c < 48) c = nc;
  while (c > 47) x = x * 10 + c - 48, c = nc;
  return x;
}

void addline(int u, int v) {
  static int cnt = 1;
  e[++cnt] = edges{h[u], v}, h[u] = cnt;
}

void tarjan(int u, int f) {
  static int now;
  dfn[u] = low[u] = ++now;
  for (int i = h[u]; i; i = e[i].nxt) {
    int v = e[i].to;
    if (!dfn[v]) {
      st[++top] = i >> 1, st[++top] = u, st[++top] = v;
      tarjan(v, u);
      low[u] = min(low[u], low[v]);
      if (dfn[u] <= low[v]) {
        tot++;
        while (1) {
          int t1, t2;
          node[tot].insert(t1 = st[top--]);
          node[tot].insert(t2 = st[top--]);
          edge[tot].insert(st[top--]);
          if (t1 == v && t2 == u) break;
        }
      }
    } else if (dfn[v] < dfn[u] && v != f) {
      st[++top] = i >> 1, st[++top] = u, st[++top] = v;
      low[u] = min(low[u], dfn[v]);
    }
  }
}

int main() {
  n = read(), m = read();
  for (int i = 1; i <= m; i++) {
    int u = read(), v = read();
    addline(u, v), addline(v, u);
  }
  for (int i = 1; i <= n; i++) {
    if (!dfn[i]) tarjan(i, 0);
  }
  for (int i = 1; i <= tot; i++) {
    if (edge[i].size() == node[i].size()) {
      ans.insert(edge[i].begin(), edge[i].end());
    }
  }
  printf("%d\n", (int)ans.size());
  for (int u : ans) printf("%d ", u);
  return 0;
}
```

---

## 作者：Imakf (赞：3)

这是一篇不需要用 set 的 tarjan 题解。

首先题意可以转化为找出边数等于点数的点双连通分量，不禁让人想起 tarjan。

只需要在 tarjan 的时候对当前点双边的数量进行差分就可以判断出当前点双有多少边了。

仔细想想，由于每一个点双都是在最先被 dfs 到的点计算的，所以差分是正确的。

代码应该比较清晰了。

复杂度就是 $O(n+m)$ 的啦。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int MX = 1e5 + 23;

int n ,m;

int head[MX] ,tot = 1;
struct edge{
	int node ,next ,w;
}h[MX << 1];
void addedge(int u ,int v ,int flg = 1){
	h[++tot] = (edge){v ,head[u] ,1} ,head[u] = tot;
	if(flg) addedge(v ,u ,false);
}

int DFN[MX] ,low[MX] ,cnt ,stk[MX] ,dep;
int estk[MX] ,ans[MX];
int M;
void tarjan(int x){
	DFN[x] = low[x] = ++cnt;
	stk[++dep] = x;
	for(int i = head[x] ,d ; i ; i = h[i].next){
		int curm = M;
        // 保存一下当前的边数
		if(h[i].w){ // 这条边是第一次经过（两个方向都是）
			estk[++M] = i / 2;
			h[i].w = h[i ^ 1].w = 0;
            // 反向边也要更新
		}
		if(!DFN[d = h[i].node]){
			tarjan(d);
			low[x] = min(low[x] ,low[d]);
			if(DFN[x] == low[d]){ 
				int vcnt = 0;
				for(int tmp = 0 ; tmp != d ; --dep){
					tmp = stk[dep];
					++vcnt;
				}
				++vcnt;
                // 以上是正常缩点双
				int ok = (M - curm == vcnt);
                // 差分判断当前点双的边数是否和点数一致
				while(curm < M){
					ans[estk[M]] = ok;
					--M;
				}
			}
		}else if(DFN[d] < low[x]) low[x] = DFN[d];
	}
}

int main(){
	cin >> n >> m;
	for(int i = 1 ,u ,v ; i <= m ; ++i){
		cin >> u >> v;
		addedge(u ,v);
	}
	for(int i = 1 ; i <= n ; ++i)
		if(!DFN[i]) tarjan(i);
	int cnt = 0;
	for(int i = 1 ; i <= m ; ++i){
		cnt += ans[i];
	}
	cout << cnt << endl;
	for(int i = 1 ; i <= m ; ++i){
		if(ans[i]){
			cout << i << " ";
		}
	}
	cout << endl;
	return 0;
}
```



---

## 作者：sigland (赞：3)

很显然,对于求有关图.环之类的题目我们可以想到建搜索树来做.而建完之后我们发现所求的边可以分为两种情况:
1.被且仅被1条返祖边覆盖的树边
2.所在起点到终点都是成立的树边的返祖边.
那么我们只要建好搜索树(因为不一定连通所以可能不止一棵),之后对于返祖边的起点终点进行树状差分,然后在枚举每条返祖边起点到终点在树上的路径,如果这条路径上差分值都是1即可行.统计答案.(枚举路径这一步我写的有些暴力,直接暴力从一个点往祖先跳,有可能被卡,所以最好可以写树剖,但我实在太蒟蒻就没写...)
具体实现见代码吧...
```cpp
#pragma GCC optimize(3,"inline","Ofast")
#include<bits/stdc++.h>
using namespace std;
vector<int>ans;
int tmp,tp,a,b,u,v,n,m,to[500010],deep[500010],nxt[500010],hd[500010],fa[100010],tofa[500010],num=-1,cf[500010];
bool tree[500010],vis[100010],flag;
void add(int u,int v)      //加边 (双向) 
{
    nxt[++num]=hd[u],to[num]=v,hd[u]=num;
    nxt[++num]=hd[v],to[num]=u,hd[v]=num;
}
void dfs1(int pos,int f,int dp)//建搜索树 
{
    fa[pos]=f;vis[pos]=1;deep[pos]=dp;
    for(int i=hd[pos];i!=-1;i=nxt[i])
    {
        if(!vis[to[i]])
        {
            tofa[to[i]]=i,tree[i]=1;dfs1(to[i],pos,dp+1);//记录是否为树边,以及到连接父亲节点边编号 
        }
    }
}
void dfs(int pos)
{
    vis[pos]=1;
    for(int i=hd[pos];i!=-1;i=nxt[i])
    {
        if(tree[i])dfs(to[i]),cf[pos]+=cf[to[i]];//跑出差分 
    }
}
int main()
{
    memset(hd,-1,sizeof hd);
    memset(nxt,-1,sizeof nxt);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&a,&b);
        add(a,b);
    }
    for(int i=1;i<=n;i++)
        if(!vis[i])dfs1(i,0,1);
    for(int i=0;i<=num;i+=2)
    {
        if(tree[i]||tree[i+1])continue;
        else u=to[i],v=to[i+1];
        if(deep[u]<deep[v])swap(u,v);
        cf[u]++;cf[v]--;//进行差分,注意在一个点上的差分值代表这个点到父亲的边的差分,因此在u,v上做,具体可画图理解 
    }
    memset(vis,0,sizeof vis);
    for(int i=1;i<=n;i++)
        if(!vis[i])dfs(i);
    for(int i=0;i<=num;i+=2)
    {
        if(tree[i]||tree[i+1])continue;
        else u=to[i],v=to[i+1];
        if(deep[u]<deep[v])swap(u,v);
        flag=0;tmp=u;
        for(;fa[tmp]!=v;tmp=fa[tmp])//暴力跑路径 
        {
            if(cf[tmp]!=1)
            {
                flag=1;break;
            }
        }
        if(!flag&&cf[tmp]==1)
        {
            ans.push_back((i+2)/2);//因为存的是双向边,故编号为+2再/2 
            while(u!=v)
            {
                ans.push_back((tofa[u]+2)/2);
                u=fa[u];
            }
        }
    }
    sort(ans.begin(),ans.end());cout<<ans.size()<<endl;
    for(int i=0;i<ans.size();i++)cout<<ans[i]<<" ";//输出 
}
```

---

## 作者：dbxxx (赞：3)

[可以在我的博客中查看，谢谢支持。](https://www.cnblogs.com/crab-in-the-northeast/p/cf962f.html)

在一个无向图中，某个简单环等价于这个图中某个点数等于边数的**点双**连通分量。

> 为什么不是边双连通分量？
>
> 想象一个 8 字结构。这个 8 字整体并不是一个简单环（边数比点数多1），而是上下两个简单环中间共用一个点形成的。
>
> 从点双的角度来看，是上下两个点数等于边数的点双，这是正确的。
>
> 而从边双的角度来看，整个 8 字是一个边双，而上下两个环为这个 8 字边双的子图，并不是边双联通分量，等价性就破坏了。
>
> 可以这样理解：**两个简单环可以共用一个点，而不能共用一条边**。而**边双是不能处理共用一个点的**，所以边双不行。

在 tarjan 求解点双连通分量的过程中，同时用两个栈，分别存点和边。

然后判断到一个点双连通分量的时候，如果发现点数等于边数，那么存点的栈直接弹出，存边的栈边弹边把弹出的边记录在答案中，否则两个栈都直接弹就可以了。

但实际实现代码的时候发现，点数和边数似乎本来就需要弹栈同时统计？不会还用到一个数组来存弹出来的边，然后再回去给数组标记吧。这样就麻烦了。

我们发现存点的栈无论如何都是直接弹，那么点数直接边弹边统计即可。

而边数，其实就是栈中 $(u, v)$ 这条边，一直往上到栈顶的这些边的数量。那么一开始弹入 $(u, v)$ 之前我们记录一下存边栈的大小 $erz$，之后检测到点双，弹栈之前栈的大小 $s$ 减去 $erz$ 就是边的数量。具体看代码。

```cpp
/*
 * @Author: crab-in-the-northeast 
 * @Date: 2022-10-07 22:53:38 
 * @Last Modified by: crab-in-the-northeast
 * @Last Modified time: 2022-10-08 00:45:49
 */
#include <bits/stdc++.h>
inline int read() {
    int x = 0;
    bool flag = true;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-')
            flag = false;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = (x << 1) + (x << 3) + ch - '0';
        ch = getchar();
    }
    if(flag)
        return x;
    return ~(x - 1);
}

const int maxn = (int)1e5 + 5;
const int maxm = (int)1e5 + 5;
typedef std :: pair <int, int> pii;

std :: vector <pii> G[maxn];
std :: vector <int> ans;
std :: stack <int> vst, est;

int dfn[maxn], low[maxn], times;

inline bool gmi(int &a, int b) {
    return b < a ? a = b, true : false;
}

void tarjan(int u, int lst) {
    dfn[u] = low[u] = ++times;
    vst.push(u);

    for (pii e : G[u]) {
        int v = e.first, id = e.second;
        if (!dfn[v]) {
            int erz = est.size();
            est.push(id);
            tarjan(v, id);
            gmi(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                int ent = est.size() - erz, vnt = 1;
                while (!vst.empty()) {
                    int x = vst.top();
                    vst.pop();
                    ++vnt;
                    if (x == v)
                        break;
                }

                // printf("%d %d %d\n", low[u], low[v], ent);
                while (!est.empty()) {
                    int x = est.top();
                    est.pop();
                    if (ent == vnt)
                        ans.push_back(x);
                    if (x == id)
                        break;
                }
            }
        } else if (id != lst) {
            // 我们刚刚是从哪条边来的，不能从这条边上返回去
            // 事实上还有一种写法是 tarjan 在传参 u 的同时也传参 u 的父亲 fa，然后检测 v != fa 防止回去
            // 这种写法在无重边，或者求点双/割点的时候都没有问题（你把一个点删了重边一起没，不影响）
            // 但是在有重边环境下，求边双/桥的时候就会出问题了，比如 1 - 2 之间两条边，删除一条可以走另一条。这种情况下只能像我这么写
            // 具体可以看洛谷中边双的板题 P8436
            gmi(low[u], dfn[v]);
            est.push(id);
        }
    }
}

int main() {
    int n = read(), m = read();
    for (int i = 1; i <= m; ++i) {
        int u = read(), v = read();
        G[u].emplace_back(v, i);
        G[v].emplace_back(u, i);
    }

    for (int u = 1; u <= n; ++u)
        if (!dfn[u])
            tarjan(u, 0);
    
    printf("%d\n", (int)ans.size());
    std :: sort(ans.begin(), ans.end());
    
    for (auto x : ans)
        printf("%d ", x);
    puts("");
    return 0;
}
```



---

## 作者：TUIFEI_oier (赞：2)

一个奇怪的做法，貌似没有看见相同做法的题解。

首先对于不同的连通块，我们分别处理即可。  
发现如果一条边符合条件，当且仅当它所在的点双恰为一个简单环。  
于是，我们可以把题意转化为：**求所有点数等于边数的点双连通分量**。  
因为一条边只会在一个点双中出现，于是我们考虑**在每条边上新增**一个点。  
即把这样一张图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/71tjy7ki.png)  
变成这样：  
![](https://cdn.luogu.com.cn/upload/image_hosting/twq3qh4c.png)  
此时，如果我们把原来的 $n$ 个点权值设为 $1$，新增点的权值设为 $-1$，相当于要求**有多少个点双的点权和为 $0$**。  
这是在 Tarjan 过程中可以方便地统计的。  
同时，因为每条边只会属于一个点双，所以每个新增点也只会被一个点双包含，记录下来每个新增点对应的点双编号即可。

此时还有一个问题：对于一条不存在于任意一个简单环中的边，我们这样处理会导致误判。  
有一个比较笨的解决方法，在新增点之前跑一下原图的 Tarjan，则所有只有两个点的点双就对应一条这样的边，记录下来这些边后新建点时忽略这些边即可。  
于是总时间复杂度为 $O(n+m)$。

代码如下：  
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ch getchar
template<typename T> void read(T &x){
    x = 0; int f(1); char c = ch();
    for(;!isdigit(c);c = ch()) if(c == '-') f = -1;
    for(;isdigit(c);c = ch()) x = x*10+c-'0';
    x *= f;
}
template<typename T,typename... Args>
inline void read(T &x,Args&... args){
    read(x); read(args...);
}
#define pb emplace_back
const int maxn = 100005;
int n,m,ANS[maxn],cnt;
int hd[maxn],tt = 1; // 注意前向星的开始下标。
struct edge{int ed,nxt;}e[2*maxn];
int dfn[2*maxn],low[2*maxn];
int sta[2*maxn],top,tot;
int val[2*maxn],V[2*maxn];
int eu[maxn],ev[maxn];
vector<int> Frm[2*maxn];
vector<int> G[2*maxn];
void star(int u,int v){
    e[++tt] = (edge){v,hd[u]}; hd[u] = tt;
    e[++tt] = (edge){u,hd[v]}; hd[v] = tt;	
}
void Tarjan(int x){
    dfn[x] = low[x] = ++tot;
    sta[++top] = x;
    for(auto y:G[x]){
        if(!dfn[y]){
            Tarjan(y);
            low[x] = min(low[x],low[y]);
            if(low[y] == dfn[x]){
                ++cnt;
                while(sta[top+1] != y){
                V[cnt] += val[sta[top]];
                    if(val[sta[top]] == -1)
                        Frm[cnt].pb(sta[top]);
                    --top;
                }
                V[cnt] += val[x];
                if(val[x] == -1)	Frm[cnt].pb(x);
                // 统计点权和，并记录每个点双中的新增点。
            }
        }
        else	low[x] = min(low[x],dfn[y]);
    }
}
void tarjan(int x){
    dfn[x] = low[x] = ++tot;
    sta[++top] = x;
    for(int i = hd[x];i;i = e[i].nxt){
        int y = e[i].ed;
        if(!dfn[y]){
            tarjan(y);
            low[x] = min(low[x],low[y]);
            if(low[y] == dfn[x]){
                cnt = 0;
                while(sta[top+1] != y)
                    ++cnt,--top;
                ++cnt;
                if(cnt == 2)	ANS[i/2] = 1;
                // 对于所有大小为 2 的点双，给边打上标记。
            }
        }
        else	low[x] = min(low[x],dfn[y]);
    }
}
int main(){
    read(n,m);
    for(int i(1);i <= m;++i){
        read(eu[i],ev[i]);
        star(eu[i],ev[i]);
    }
    for(int i(1);i <= n;++i)
        if(!dfn[i]) tarjan(i),--top;
//第一次 tarjan，求出不存在于任意一个简单环中的边，并打上标记。
    memset(dfn,0,sizeof dfn);
    tot = top = cnt = 0;
    for(int i(1);i <= n;++i)	val[i] = 1;
    for(int i(1);i <= m;++i){
        if(ANS[i] == 1){ANS[i] = 0;continue;}
        G[eu[i]].pb(n+i); G[ev[i]].pb(n+i);
        G[n+i].pb(eu[i]); G[n+i].pb(ev[i]); val[n+i] = -1;
    }
//新建边上的点。
    n += m;
    for(int i(1);i <= n;++i)
        if(!dfn[i]) Tarjan(i),--top;
//第二次 tarjan，求出所有新图点双的权值和。
    for(int i(1);i <= cnt;++i)
        if(V[i] == 0)
        for(int j(0);j < Frm[i].size();++j)
            ANS[Frm[i][j]-n+m] = 1;
//统计答案、输出。
    cnt = 0;
    for(int i(1);i <= m;++i)	cnt += ANS[i];
    cout << cnt << endl;
    for(int i(1);i <= m;++i)
        if(ANS[i])	printf("%d ",i);
    return 0;
}
```

---

## 作者：翼德天尊 (赞：1)

环类统计问题不妨先考虑下我们的 dfs 生成树。

显然一条边只被一个环包含的必要条件是，在 dfs 生成树上只被一条返祖边覆盖。除此之外，如果两条返祖边存在相交部分，则代表这两个环上的所有边一定都被至少两个环覆盖。

所以不妨先对所有返祖边包含的链作链覆盖，再依次考虑每一条返祖边覆盖的区域，如果存在一条边权值 $>1$ 则说明该环还与其它环相交，此时不妨再作一次链覆盖。最终只被一个环包含的树边一定是那些权值为 $1$ 的边。

非树边的处理显然。链覆盖可以通过树链剖分+线段树维护，时间复杂度  $O(m\log ^2n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5;
int n,m,bf[N],ptot,dep[N],fa[N],tp[N],siz[N],zson[N],dfn[N],tim,jl[N],jtot,f[N];
struct Edge{
    int to[N<<1],next[N<<1],head[N],tot,id[N<<1];
    void adde(int u,int v,int i){
        to[++tot]=v,next[tot]=head[u],head[u]=tot,id[tot]=i;
    }
}S;
struct SegTree{
    int maxn[N<<2],lz[N<<2];
    void pushdown(int i){
        if (lz[i]){
            maxn[i<<1]+=lz[i],maxn[i<<1|1]+=lz[i];
            lz[i<<1]+=lz[i],lz[i<<1|1]+=lz[i];
            lz[i]=0;
        }
    }
    void pushup(int i){
        maxn[i]=max(maxn[i<<1],maxn[i<<1|1]);
    }
    void add(int i,int l,int r,int ql,int qr,int k){
        if (ql<=l&&r<=qr){
            maxn[i]+=k;
            lz[i]+=k;
            return;
        }
        int mid=l+r>>1;
        pushdown(i);
        if (ql<=mid) add(i<<1,l,mid,ql,qr,k);
        if (mid<qr) add(i<<1|1,mid+1,r,ql,qr,k);
        pushup(i);
    }
    int query(int i,int l,int r,int ql,int qr){
        if (ql<=l&&r<=qr) return maxn[i];
        int mid=l+r>>1;
        pushdown(i);
        if (qr<=mid) return query(i<<1,l,mid,ql,qr);
        if (mid<ql) return query(i<<1|1,mid+1,r,ql,qr);
        return max(query(i<<1,l,mid,ql,qr),query(i<<1|1,mid+1,r,ql,qr));
    }
}T;
struct node{
    int u,v,id;
    node (int u=0,int v=0,int id=0)
        :u(u),v(v),id(id){}
}p[N];
ll read(){
    ll w=0,f=1;
    char ch=getchar();
    while (ch>'9'||ch<'0') {
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9') {
        w=(w<<3)+(w<<1)+(ch^48);
        ch=getchar();
    }
    return w*f;
}
int find(int x){
    if (bf[x]==x) return x;
    return bf[x]=find(bf[x]);
}
void dfs1(int u){
    siz[u]=1,dep[u]=dep[fa[u]]+1;
    for (int i=S.head[u];i;i=S.next[i]){
        int v=S.to[i];
        if (v==fa[u]) continue;
        fa[v]=u,dfs1(v),f[v]=S.id[i];
        siz[u]+=siz[v];
        if (siz[v]>siz[zson[u]]) zson[u]=v;
    }
}
void dfs2(int u,int t){
    tp[u]=t,dfn[u]=++tim;
    if (zson[u]) dfs2(zson[u],t);
    for (int i=S.head[u];i;i=S.next[i]){
        int v=S.to[i];
        if (v==fa[u]||v==zson[u]) continue;
        dfs2(v,v);
    }
}
bool cmp(node x,node y){
    return x.v<y.v;
}
void modify(int x,int y){
    while (tp[x]!=tp[y]){
        if (dep[tp[x]]<dep[tp[y]]) swap(x,y);
        T.add(1,1,n,dfn[tp[x]],dfn[x],1);
        x=fa[tp[x]];
    }
    if (dfn[x]==dfn[y]) return;
    if (dfn[x]>dfn[y]) swap(x,y);
    T.add(1,1,n,dfn[x]+1,dfn[y],1);
}
int query(int x,int y){
    int maxn=0;
    while (tp[x]!=tp[y]){
        if (dep[tp[x]]<dep[tp[y]]) swap(x,y);
        maxn=max(maxn,T.query(1,1,n,dfn[tp[x]],dfn[x]));
        x=fa[tp[x]];
    }
    if (dfn[x]==dfn[y]) return maxn;
    if (dfn[x]>dfn[y]) swap(x,y);
    maxn=max(maxn,T.query(1,1,n,dfn[x]+1,dfn[y]));
    return maxn;
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
	n=read(),m=read();
    for (int i=1;i<=n;i++) bf[i]=i;
    for (int i=1;i<=m;i++){
        int u=read(),v=read(),x=find(u),y=find(v);
        if (x==y) p[++ptot]=node(u,v,i);//,cout<<i<<" left"<<"\n";
        else S.adde(u,v,i),S.adde(v,u,i),bf[x]=y;//,cout<<i<<" right"<<"\n";
    }
    for (int i=1;i<=n;i++)
        if (!dep[i]) dfs1(i),dfs2(i,i);
    for (int i=1;i<=ptot;i++)
        modify(p[i].u,p[i].v);
    for (int i=1;i<=ptot;i++)
        if (query(p[i].u,p[i].v)>1) modify(p[i].u,p[i].v);
        else jl[++jtot]=p[i].id;
    for (int i=1;i<=n;i++)
        if (T.query(1,1,n,dfn[i],dfn[i])==1) jl[++jtot]=f[i];
    cout<<jtot<<"\n";
    sort(jl+1,jl+1+jtot);
    for (int i=1;i<=jtot;i++) cout<<jl[i]<<" ";
    puts("");
    return 0;
}
```

---

## 作者：_lqs_ (赞：1)

首先一个显然的性质：一个环内，当点数等于边数时是个简单环。

这里写边双是错误的，例如对于以下数据：

```cpp
7 7
1 2
2 3
1 3
3 6
3 4
4 5
5 6
```
这里包含了两个简单环，但是边双会把它们缩成一个点，因此我们要考虑点双。由于一个简单环本来就是联通块，因此点双一定会把一个联通块内最大的环缩在一起。

一个点双内的点是容易统计的，直接在 Tarjan 过程中开栈处理即可。处理边的话，如果是遍历每一个点双，再把每一个点的所有边遍历一次会在最后一个点超时，因为同一个点及其边会被遍历多次。所以最好的办法就是在把点丢进栈的同时把边也丢进去，用 ```set``` 处理重点。时间复杂度 $O((n+m) \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 100005
int n,m,i,j,ans,sum,a,b,c,k,num,ff[N*2],st[N*100],s,LG[N*2],P[N],pr[N*2],flag[N*2],cnt[N],vis[N],del[N],h[N],dis[N],low[N],dfn[N];
struct AB{
	int a,b,n,p;
}d[N<<1];
void cun(int a,int b,int x){
	d[++k].a=a,d[k].b=b,d[k].p=x;
	d[k].n=h[a],h[a]=k;
}
set<int>G[N],F[N];
void Tarjan(int a,int lst){
	low[a]=dfn[a]=++num;
	int cld=0;
	for(int i=h[a];i;i=d[i].n){
		int b=d[i].b;
		if(!ff[d[i].p]) st[++s]=d[i].p,st[++s]=a,st[++s]=b,ff[d[i].p]=1;
		if(!dfn[b]){		
			Tarjan(b,a),cld++;
			low[a]=min(low[a],low[b]);
			if(low[b]>=dfn[a]){
				flag[a]=1;
				++ans;
				while(st[s]!=b || st[s-1]!=a) F[ans].insert(st[s--]),F[ans].insert(st[s--]),pr[st[s]]=ans,G[ans].insert(st[s--]);
				F[ans].insert(st[s--]),F[ans].insert(st[s--]),pr[st[s]]=ans,G[ans].insert(st[s--]);
			}
		}
		else low[a]=min(low[a],dfn[b]);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;++i){
		scanf("%d%d",&a,&b,&c);
		cun(a,b,i),cun(b,a,i);
	}
	for(i=1;i<=n;++i){
		if(!dfn[i]) Tarjan(i,i);
	}
	for(i=1;i<=k;++i,++i){
		if(F[pr[d[i].p]].size()==G[pr[d[i].p]].size()) sum++;
	}
	printf("%d\n",sum);
	for(i=1;i<=k;++i,++i){
		if(F[pr[d[i].p]].size()==G[pr[d[i].p]].size()) printf("%d ",d[i].p);
	}
	return 0;
}
```



---

## 作者：ybw051114 (赞：1)

## 思路:
考虑对于两个简单环的交对称差，可以得到新的简单环
所以一个简单环要么全满足，要么全不满足。
对于一条非树边看一下中间是否只有 1 个覆盖
用树上差分 + dfs 实现
dfs 时记录它的祖先保证全为 1 的最大深度
## 实现:

```cpp
#include <bits/stdc++.h>

#ifndef use_ios11
#define use_ios11
using namespace std;
struct ins
{
    int ans;
    ins()
    {
        ans = 1;
    }
#define endl '\n'
    void read()
    {
    }
    void read1(char &s)
    {
        char c = getchar();
        for (; !isprint(c) || c == ' ' || c == '\n' || c == '\t'; c = getchar())
            ;
        s = c;
        if (c == EOF)
            ans = 0;
    }
    void read1(string &s)
    {
        s = "";
        char c = getchar();
        for (; !isprint(c) || c == ' ' || c == '\n' || c == '\t'; c = getchar())
            ;
        for (; isprint(c) && c != ' ' && c != '\n' && c != '\t'; c = getchar())
            s += c;
        if (c == EOF)
            ans = 0;
    }
    template <typename T>
    void read1(T &n)
    {
        T x = 0;
        int f = 1;
        char c = getchar();
        for (; !isdigit(c); c = getchar())
        {
            if (c == '-')
                f = -1;
            if (c == EOF)
            {
                ans = 0;
                return;
            }
        }
        for (; isdigit(c); c = getchar())
            x = x * 10 + c - 48;
        n = x * f;
        if (c == EOF)
            ans = 0;
        if (c != '.')
            return;
        T l = 0.1;
        while ((c = getchar()) <= '9' && c >= '0')
            x = x + (c & 15) * l, l *= 0.1;
        n = x * f;
        if (c == EOF)
            ans = 0;
    }
    void write() {}
    void write1(string s)
    {
        int n = s.size();
        for (int i = 0; i < n; i++)
            putchar(s[i]);
    }
    void write1(const char *s)
    {
        int n = strlen(s);
        for (int i = 0; i < n; i++)
            putchar(s[i]);
    }
    void write1(char s)
    {
        putchar(s);
    }
    void write1(float s, int x = 6)
    {
        char y[10001];
        sprintf(y, "%%.%df", x);
        printf(y, s);
    }
    void write1(double s, int x = 6)
    {
        char y[10001];
        sprintf(y, "%%.%dlf", x);
        printf(y, s);
    }
    void write1(long double s, int x = 6)
    {
        char y[10001];
        sprintf(y, "%%.%dLf", x);
        printf(y, s);
    }
    template <typename T>
    void write1(T n)
    {
        if (n < 0)
            n = -n, putchar('-');
        if (n > 9)
            write1(n / 10);
        putchar('0' + n % 10);
    }
    template <typename T>
    friend ins operator>>(ins x, T &n);
    template <typename T>
    friend ins operator<<(ins x, T n);
    operator bool()
    {
        return ans;
    }
};
template <typename T>
ins operator>>(ins x, T &n)
{
    if (!x.ans)
        return x;
    x.read1(n);
    return x;
}
template <typename T>
ins operator<<(ins x, T n)
{
    x.write1(n);
    return x;
}
ins yin;
ins yout;
#endif
int n, m;
const int maxn = 1e5 + 10;
int tot = 1, head[maxn];
struct edge
{
    int v, nxt, tr;
} e[maxn << 1];
void __ADD(int u, int v)
{
    e[++tot].v = v;
    e[tot].nxt = head[u];
    head[u] = tot;
}
void add(int a, int b)
{
    __ADD(a, b);
    __ADD(b, a);
}
int ans;
int vis[maxn];
int a[maxn];
int dep[maxn];
int tof[maxn];
int f[maxn];
int sum[maxn];
void dfs(int u, int fa)
{
    vis[u] = 1;
    dep[u] = dep[fa] + 1;
    f[u] = fa;
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].v;
        if (v == fa)
            continue;
        // cout << u << ' ' << v << endl;
        if (vis[v])
        {
            if (dep[u] > dep[v])
                sum[v]--, sum[u]++;
        }
        else
            dfs(v, u), e[i].tr = e[i ^ 1].tr = 1, tof[v] = i;
    }
}
vector<int> ans1;
void dfs1(int u, int fa, int deep)
{
    // cout << u << vis[5] << endl;
    vis[u] = 1;
    // cout << u << " " << deep << " " << sum[u] << endl;
    deep = sum[u] == 1 ? deep : dep[u] + 1;
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].v;
        if (v == fa)
            continue;
        if (!vis[v])
            dfs1(v, u, deep);
        else
        {
            if (dep[v] + 1 >= deep && dep[u] > dep[v])
            {
                int uu = u, vv = v;
                ans1.push_back(i / 2);
                while (uu != vv)
                {
                    ans1.push_back(tof[uu] / 2);
                    // cout << uu << ' ' << v << endl;
                    uu = f[uu];
                }
            }
        }
    }
}
void dfs2(int u, int fa)
{
    vis[u] = 1;
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].v;
        if (v == fa)
            continue;
        if (!vis[v])
        {
            dfs2(v, u);
            sum[u] += sum[v];
        }
    }
    // cout << u << " " << sum[u] << endl;
}
int main()
{
    yin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int a, b;
        yin >> a >> b;
        add(a, b);
    }
    for (int i = 1; i <= n; i++)
        if (!vis[i])
            dfs(i, 0);
    memset(vis, 0, sizeof(vis));
    // cout << vis[5] << endl;
    for (int i = 1; i <= n; i++)
        if (!vis[i])
            dfs2(i, 0);
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; i++)
        if (!vis[i])
            dfs1(i, 0, 1);
    sort(ans1.begin(), ans1.end());
    yout << ans1.size() << endl;
    for (int i = 0; i < ans1.size(); i++)
        yout << ans1[i] << " ";
    return 0;
}

```

---

## 作者：Mihari (赞：1)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF962F)

# 题解

首先应分析在什么情况下，一条边才只会包含在一个简单环里面。

如果两个环有公共边，对于这两个环的边分情况讨论：

- 对于公共边，这条边被左、右俩环同时包含，显然不符题意；
- 对于非公共边，首先他们分别属于自己的环，其次，他们又在一个最外围的大环上；

也就是说，如果两个环有公共边，那么这俩环上没有边是符合题意的。

那么我们的目的就很明确了——寻找独立的简单环的边数并输出其编号。

此处“独立”是指与其他环没有公共边。

那么，问题变成如何“寻找”独立环，分析独立环的特性——显然，点数等于边数，这是再显然不过的条件。

那么，我们可以将图中的点双全部找出来，对于每一个点双再分别判断点数是否等于边数即可。

为什么不找边双？显然两个简单环是可以存在公共点的（区分公共边），所以我们寻找的其实是割点而非桥，最简单的一个模型就是 $8$ 字结构，在这种模型下边双就会出问题（CF 的数据应该是 test#8）。

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13540154.html
```



---

## 作者：foryou_ (赞：0)

对于有关环的无向图问题，自然往双连通方面思考。

容易发现一个点双连通分量（下文简称 V-DCC）中至多有一个简单环。

这是因为，若有多个简单环，则必定存在割点。

于是我们直接在每个 V-DCC 里边统计即可。

进一步可以发现，若一个 V-DCC 满足边数与点数相等，则它里面的所有边都是答案。

统计点数是简单的。如何统计边数？

类似于存储点的栈，我们也可以设置一个存储边的栈。

每次点与边分别弹出并统计各自数量即可。

[代码实现](https://codeforces.com/contest/962/submission/292900101)，注意标注出来的细节点。

---

## 作者：GJX_Algorithm (赞：0)

# CF962F 题解
## 题目描述
- 给定一个 $n$ 个点，$m$ 条边的无向图。

- 输出恰好被包含在**一个**简单环中的边。

## 解题思路
- 第一眼看题，无向图，简单环，双连通分量跑不了。

- 可是问题来了，用边双还是用点双？

### 边双与点双的选择
- 首先考虑边双，根据边双的性质，很快就能确定一个做法：

  1. 先找出图中所有边双。
 
  2. 对于一个简单环，其**点数一定等于边数**，所以可以判断边双是否为简单环。
 
- 但是，边双做法是否可能被 hack？如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/uhiwjjn9.png)

- 既然边双被 hack 了，那么接着考虑点双，可是这题跟点双有什么关系呢？

  1. 首先我们可以得出一条结论：**一条边只能在一个点双里**。如果在经过两个点双，就必定有环套环现象。
 
  2. 根据上述结论，我们可以得知，每个点双都是独立的，我们只需要对点双进行单个讨论即可。
 
  3. 对于每个点双，判定其是否为简单环的方法同边双一样。
 
### 判定简单环
- 通过以上推论，我们已经知道这题的解决方法，可是我们又多了一个问题，**如何统计点数与边数**？

- 点数很好统计，只需要在维护边双的时候统计即可。

- 边数需要我们**再开一个栈存边**，在维护边双弹出点的同时弹出边，统计即可。
## AC Code
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize(2)
using namespace std;
const int N = 3e5 + 5;
int n, m;
int u, v;
int cnt = 1, tot, root;
int to[N], head[N], Next[N];
int dfn[N], low[N], cut[N];
bool vis[N];
vector<int> edge;
stack<int> stkp, stke;
set<int> ans;
void add(int u, int v)
{
    to[++cnt] = v;
    Next[cnt] = head[u];
    head[u] = cnt;
    return ;
}
void tarjan(int cur, int in_edge)
{
	dfn[cur] = low[cur] = ++tot;
	stkp.push(cur);
	for (int i = head[cur]; i; i = Next[i])
	{
		int nxt = to[i];
		if (dfn[nxt] == 0)
		{
            stke.push(i);
			tarjan(nxt, i);
			low[cur] = min(low[cur], low[nxt]);
			if (dfn[cur] <= low[nxt]) //可能是割点
			{
				int tmp = 0, psum = 0, esum = 0;
                edge.clear();
				while (stkp.empty() == 0 && tmp != nxt) //从栈顶一直弹到cur之上
				{
					tmp = stkp.top();
					stkp.pop();
                    psum++;
				}
                psum++;

                tmp = 0;
                while (stke.empty() == 0 && tmp != i) //弹边
                {
                    //cout << tmp << "\n";
                    tmp = stke.top();
                    edge.push_back(tmp);
                    stke.pop();
                    esum++;
                }
                edge.push_back(i);
                //cout << cur << " " << nxt << " " << psum << " " << esum << "\n";
                if (esum == psum) //点数 = 边数，简单环
                    for (auto i : edge)
                        ans.insert(i / 2); //set去重 + 排序
			}
		}
		else if (i != (in_edge ^ 1))
        {
			low[cur] = min(low[cur], dfn[nxt]);
            if (dfn[cur] > dfn[nxt]) stke.push(i);
        }
	}
    return ;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        add(u, v), add(v, u);
    }
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
            tarjan(i, 0);
    int len = ans.size();
    printf("%d\n", len);
    for (auto i : ans) 
        printf("%d ", i);
    return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

应该算是不一样的做法吧。

结论是显而易见的：当一个点双内边数等于点数时，这个点双内部的边就是可选的。

考虑如何统计这些边。

注意到一个点对应的点双上界 $O(n)$，不能直接暴枚。

而一个边对应的点双就是两个端点对应的点双的并集，容易发现它是唯一的。

针对点双入手，考虑建出圆方树。

原图的路径上，放到圆方树上就是一个圆点经过一个方点再到达另一个圆点的路径。

因为一个圆点的邻接点就是它对应的点双，那么我们直接对中间那个方点进行贡献即可。

具体做法是找到两个端点间深度较大的点 $v$，它的父亲就是这条边对应的方点。

这个做法是 $O(n)$ 的。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
const int N=1e6+5;
int n,m,cnt,dfn[N],low[N],tot,u[N],v[N],siz[N<<1],dep[N<<1],fa[N<<1];
vector<int> G1[N],G2[N<<1],ans;
stack<int> s;
inline void Tarjan(int u){
	low[u]=dfn[u]=++tot;
	s.push(u);
	for(auto v:G1[u])
		if(!dfn[v]){
			Tarjan(v);
			low[u]=min(low[u],low[v]);
			if(dfn[u]==low[v]){
				int tmp;
				++cnt;
				do{
					tmp=s.top();
					s.pop();
					G2[tmp].push_back(cnt);
					G2[cnt].push_back(tmp);
				} while(tmp!=v);
				G2[u].push_back(cnt);
				G2[cnt].push_back(u);
			}
		} else low[u]=min(low[u],dfn[v]);
}
inline void Dfs(int u){
	for(auto v:G2[u]){
		if(v==fa[u]) continue;
		dep[v]=dep[u]+1,fa[v]=u;
		Dfs(v);
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m,cnt=n;
	for(int i=1;i<=m;++i){
		cin>>u[i]>>v[i];
		G1[u[i]].push_back(v[i]);
		G1[v[i]].push_back(u[i]);
	}
	for(int i=1;i<=n;++i) if(!dfn[i]) Tarjan(i),Dfs(i);
	for(int i=1;i<=m;++i){
		if(dep[u[i]]>dep[v[i]]) swap(u[i],v[i]);
		++siz[fa[v[i]]];
	}
	for(int i=1;i<=m;++i) if(siz[fa[v[i]]]==G2[fa[v[i]]].size()) ans.push_back(i);
	cout<<ans.size()<<endl;
	for(auto x:ans) cout<<x<<' ';
	cout<<endl;
	return 0;
}
```

---

## 作者：Otue (赞：0)

$\text{Trick 1:}$ **题目要求的简单环(被包含在恰好一个简单环的点形成的环)** 必定经过割点但绝对不穿过割点。

$\text{Trick 2:}$ 如何判定简单环？直接判点数是否等于边数即可。

所以跑一遍点双连通分量，过程中记录所有经过点和经过边。但无向图的边可能经过多次，所以需要加判断：走到一个没访问过的点，或者从一个点走回祖先。只有这种边才能被加入经过边中。

所以 $\rm \text{Trick 3}$ 是：点双统计经过边时，需要注意去重。走到一个没访问过的点，或者从一个点走回祖先的边才符合要求。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)
#define int long long
const int N = 3e5 + 5;

int n, m, dfn[N], low[N], idx, b[N], tot, ans[N];
stack<int> se, sv;

int en = 1, first[N];
struct edge {
	int e, next; 
}ed[N];
void add_edge(int s, int e) {
	en++;
	ed[en].e = e;
	ed[en].next = first[s];
	first[s] = en;
}

void tarjan(int u, int from) {
	dfn[u] = low[u] = ++idx; sv.push(u);
	for (int p = first[u]; p; p = ed[p].next) {
		int v = ed[p].e;
		if (!dfn[v]) {
			se.push(p); 
			tarjan(v, p);
			low[u] = min(low[u], low[v]);
			if (dfn[u] <= low[v]) {
				int cntv = 1, cnte = 0;
				tot = 0;
				int y;
				do {
					y = sv.top(); sv.pop();
					cntv++; 
				} while (y != v);
				do {
					y = se.top(); se.pop();
					cnte++;
					b[++tot] = y;
				} while (y != p);
				if (cntv == cnte) { // 简单环
					_for(i, 1, tot) ans[b[i] / 2] = 1; 
				} 
			}
		}
		else if (p != (from ^ 1)) {	
			low[u] = min(low[u], dfn[v]);
			if (dfn[v] < dfn[u]) { // 从一个点走回祖先
				se.push(p);
			}
		}
	}
}

signed main() {
	cin >> n >> m;
	_for(i, 1, m) {
		int u, v;
		cin >> u >> v;
		add_edge(u, v), add_edge(v, u);
	} 
	_for(i, 1, n) if (!dfn[i]) tarjan(i, 0);
	int cnt = 0;
	_for(i, 1, m) if (ans[i] == 1) cnt++;
	cout << cnt << endl;
	_for(i, 1, m) if (ans[i] == 1) cout << i << ' ';
}
```

---

## 作者：Lily_White (赞：0)

首先跑一遍 ```Tarjan``` 求出点双，接着，对于每个点双，注意到当点数恰好等于边数的时候是一个简单环。故使用 ```std::set``` 维护并计数即可。

Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define pb push_back
#define mp make_pair
#define y1 y114514
#define elif else if
#define VPII vector <PII>
#define y2 y1919810
typedef pair <int, int> PII;
typedef vector <int> VI;
//#define int long long
#define all(x) x.begin(),  x.end()
#define lsh(i) (1 << (i))
#define lshll(i) (1LL << (i))
#define repn(i, n) for (int i = 1; i <= (int)n; i++)
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define range(i, s, t)  for (int i = s; i <= (int)t; i++)
const int INF = 0x3f3f3f3f;
const long double EPS = 1e-6;
long long qread() {
    char c = getchar();
    int neg = 1;
    long long val = 0;
    while (c != '-' && !isdigit(c)) 
        c = getchar();
    if (c == '-') {
        c = getchar(); 
        neg = -1;
    }
    while (isdigit(c)) {
        val = (val << 3) + (val << 1) + c - '0';
        c = getchar();
    }
    return neg * val;
}
const int N = 100010;
int bcccnt, bccID[N], bccSize[N];
int n, m;
VPII G[N]; VI T[N];
vector <VPII> bcc;
map <PII, int> me;
VI E[N];
namespace tarjan {
    int dfn[N], tot, low[N];
    stack <PII> s;
    void tarjan(int u, int f = -1) {
        dfn[u] = low[u] = ++tot;
        int sz = 0;
        for (auto e: G[u]) {
            int v = e.first;
            ++sz;
            if (v == f) continue;
            if (!dfn[v]) {
                s.push(mp(u, v));
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
                if ((dfn[u] == 1 && sz > 1) || (dfn[u] > 1 && dfn[u] <= low[v])) {
                    VPII mirai;
                    PII t;
                    while ((t = s.top()) != mp(u, v)) {
                        mirai.pb(t);
                        s.pop();
                    }
                    mirai.pb(s.top());
                    s.pop();
                    bcc.pb(mirai);
                }
            } else if (dfn[u] > dfn[v]) {
                low[u] = min(low[u], dfn[v]);
                s.push(mp(u, v));
            }
        }
    }
}
void solve() {
    n = qread();
    m = qread();
    repn(i, m) {
        int u = qread(), v = qread();
        G[u].pb(mp(v, i));
        G[v].pb(mp(u, i));
        me[mp(u, v)] = me[mp(v, u)] = i;
    }
    repn(i, n)
        if (!tarjan::dfn[i]) {
            tarjan::tarjan(i);
            VPII eleanor;
            while (!tarjan::s.empty()) {
                eleanor.pb(tarjan::s.top());
                tarjan::s.pop();
            }
            bcc.pb(eleanor);
        }
    repn(u, n)
        for (auto e: G[u]) {
            int v = e.first;
            if (bccID[u] != bccID[v]) {
                T[bccID[u]].pb(bccID[v]);
            }
        }
    n = bcccnt;
    set <int> ans;
    for (auto component: bcc) {
        set <int> distinct;
        for (auto i:component) {
            distinct.insert(i.first);
            distinct.insert(i.second);
        }
        if (distinct.size() == component.size()) {
            for (auto i: component)
                ans.insert(me[i]);
        }
    }
    printf("%d\n", (int)ans.size());
    for (auto e: ans)
        printf("%d ", e);
    puts("");
}
int main() {
    int T = 1;
    //T = qread();
    while (T--) 
        solve();
    return 0;
}
```

---

