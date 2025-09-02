# [NEERC 2016] Cactus Construction

## 题目描述

让我们考虑以下构建图的方法。选择颜色数 $\hat{c}$。设 $n$ 为图中的顶点数。为了构建一个图，我们使用一个包含多个图的工作空间。每个图的每个顶点都有一个颜色。颜色由从 $1$ 到 $\hat{c}$ 的整数表示。最初，我们在工作空间中有 $n$ 个图，每个图中有一个顶点，所有顶点都被涂成颜色 $1$，且没有边。第 $i$ 个图的唯一顶点编号为 $i$。

允许以下操作：

join a $b$：将包含顶点 $a$ 和 $b$ 的图合并为一个图。不添加边。顶点 $a$ 和 $b$ 必须在不同的图中。

recolor a $c_{1}c_{2}$：在包含顶点 $a$ 的图中，将所有颜色为 $c_{1}$ 的顶点重新着色为颜色 $c_{2}$。

connect a $c_{1}c_{2}$：在包含顶点 $a$ 的图中，创建所有颜色为 $c_{1}$ 的顶点与颜色为 $c_{2}$ 的顶点之间的边。如果 $c_{1} = c_{2}$，则不创建自环。如果这样的边已经存在，则创建第二条平行边。在这个问题中不允许多重边，所以这种情况不应发生。

最后，我们应该有一个单一的图，并且其顶点的颜色无关紧要。

可以用来构建图的最小颜色数 $\hat{c}$ 称为图的团宽。团宽是图复杂度的特征之一。许多 NP 难问题可以在团宽有界的图上通过动态规划在这个构建图的过程中以多项式时间解决。对于一般图，计算团宽的确切值已知是 NP 难的。然而，对于某些图类，已知团宽的界限。

仙人掌图是一个连通的无向图，其中每条边最多位于一个简单环上。直观上，仙人掌图是树的推广，其中允许一些环。仙人掌图中不允许多重边（在一对顶点之间的多条边）和自环（连接顶点自身的边）。已知仙人掌图的团宽不超过 $4$。

给定一个仙人掌图。找出如何用最多 $\hat{c} = 4$ 种颜色以描述的方式构建它。

![](https://onlinejudgeimages.s3.amazonaws.com/problem/13991/%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202016-12-22%20%EC%98%A4%ED%9B%84%207.31.10.png)

![](https://onlinejudgeimages.s3.amazonaws.com/problem/13991/%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202016-12-22%20%EC%98%A4%ED%9B%84%207.31.21.png)

## 说明/提示

时间限制：2 秒，内存限制：512 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
8 2
5 1 2 3 4 7
5 4 5 6 1 8
```

### 输出

```
17
r 2 1 2
j 2 3
c 2 1 2
r 6 1 2
j 5 6
c 6 1 2
r 4 1 3
j 4 3
j 4 6
j 4 7
c 4 3 1
r 4 3 1
r 8 1 2
r 1 1 3
j 1 8
j 1 4
c 1 3 2
```

## 样例 #2

### 输入

```
15 3
9 1 2 3 4 5 6 7 8 3
7 2 9 10 11 12 13 10
5 2 14 9 15 10
```

### 输出

```
39
r 7 1 2
r 5 1 2
j 7 8
c 7 1 2
j 5 4
c 5 1 2
r 6 1 3
j 6 7
j 6 5
c 6 3 2
r 3 1 4
j 6 3
c 6 4 1
r 11 1 2
r 13 1 2
j 12 11
j 12 13
c 11 1 2
r 10 1 3
j 12 10
c 10 2 3
r 10 1 2
r 10 4 2
r 15 1 3
j 15 10
c 15 3 3
j 9 10
c 9 1 3
r 9 3 2
r 9 1 4
r 14 1 4
j 9 14
c 9 4 4
r 1 1 4
r 3 1 2
j 2 1
j 2 14
j 2 3
c 2 1 4
```

# 题解

## 作者：zhylj (赞：3)

先考虑树的情况如何构造：

我们考虑从叶子开始由深至浅合并子树，我们让三种颜色分别代表三个意义：

- 颜色 $1$：与这个点相邻的边均已建好。
- 颜色 $2$：以这个点为根的整个子树都已建好，但它和它的父亲还未连边。
- 颜色 $3$：以这个点为根的整个子树还没建好。

显然，一开始所有点的颜色都要设为 $3$，然后我们按深度从大到小考虑每个点 $u$，将其和其所有孩子 $v$ 连边，完成这棵子树的构造，由于我们考虑的顺序，所以此时其所有孩子的颜色均为 $2$。故可以依次进行以下的步骤：

- 将 $u,v$ 合并。
- 连接所有颜色 $3$ 和颜色 $2$ 的点。
- 将颜色 $2$ 改为颜色 $1$。

在考虑完所有孩子后，我们就可以将 $u$ 的颜色 $3$ 改为颜色 $2$ 了。

接下来我们考虑仙人掌的构造：找出一棵 DFS 树，那么就有：每条边只被至多一个非树边覆盖、每条非树边均为返祖边。于是考虑利用颜色 $4$ 表示还未连返祖边的点。

那么在考虑点 $u$ 时，其所有孩子 $v$ 一共有三种情况（注意在每次拼接开始时，$u,v$ 分别都为连通块中唯一的颜色为 $3,2$ 的点）：

- $v$ 不在环中或 $v$ 所在的环的顶端深度大于 $u$：该情况子树中必然不存在颜色 $4$ 的点，可以和树的情况一样做。
- $v$ 在环中，且 $v$ 所在环的顶端深度等于 $u$：在做完树的情况后，把 $u$ 连向所有颜色为 $4$ 的点，再把所有颜色为 $4$ 的点变为 $1$。
- $v$ 在环中，且 $v$ 所在环的顶端深度小于 $u$：此情况 $v$ 的颜色应该被设为 $4$，但为了防止干扰前一种情况，我们应该把这种情况留到最后去处理（显然此时不存在任何颜色为 $4$ 的点）。

然后就做完了，操作数是 $\mathcal O(n)$ 的，较为宽裕。

```cpp
const int N = 1e6 + 5;
 
int n, o_cnt;
char opt[N][20];
 
std::vector <int> E[N];
void Add(int u, int v) {
	E[u].push_back(v);
	E[v].push_back(u);
}
 
int dep[N], fa[N], low[N];
bool is_bg[N];
std::vector <int> ch[N], dfa;
void Dfs(int u) {
	dep[u] = dep[fa[u]] + 1;
	low[u] = dep[u];
	for(int v : E[u])
		if(v != fa[u]) {
			if(!dep[v]) {
				ch[u].push_back(v);
				fa[v] = u; Dfs(v);
				low[u] = std::min(low[u], low[v]);
			} else if(dep[v] < dep[u]) {
				low[u] = std::min(low[u], dep[v]);
				is_bg[u] = true;
			}
		}
	dfa.push_back(u);
}
void Solve() {
	for(int u : dfa) {
		sprintf(opt[++o_cnt], "r %d 1 3", u);
		std::sort(ch[u].begin(), ch[u].end(), [&](const int &x, const int &y) {
			return low[x] > low[y];
		});
		for(int v : ch[u]) {
			sprintf(opt[++o_cnt], "j %d %d", u, v);
			sprintf(opt[++o_cnt], "c %d 2 3", u);
			if(low[v] < dep[u] && is_bg[v]) {
				sprintf(opt[++o_cnt], "r %d 2 4", v);
			} else {
				if(low[v] == dep[u]) {
					sprintf(opt[++o_cnt], "c %d 3 4", u);
					sprintf(opt[++o_cnt], "r %d 4 1", u);
				}
				sprintf(opt[++o_cnt], "r %d 2 1", v);
			}
		}
		sprintf(opt[++o_cnt], "r %d 3 2", u);
	}
}
 
int main() {
	int m; scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i) {
		int k; scanf("%d", &k);
		std::vector <int> p;
		while(k--) { int x; scanf("%d", &x); p.push_back(x); }
		for(int j = 0; j < (int)p.size() - 1; ++j)
			Add(p[j], p[j + 1]);
	}
	Dfs(1);
	Solve();
	printf("%d\n", o_cnt);
	for(int i = 1; i <= o_cnt; ++i)
		printf("%s\n", opt[i]);
	return 0;
}
```

---

## 作者：oisdoaiu (赞：2)

*tag:构造，仙人掌*

*一道很有意思的构造题*

---
首先考虑树怎么做：

- 叶子节点把颜色改为 $2$。
- 非叶子节点把颜色改为 $3$。然后先处理完所有儿子，再将所有儿子集合与当前点合起来。然后连 $2,3$，即把所有儿子和当前点连起来。再改 $2$ 为 $1$，改 $3$ 为 $2$。

可以发现每个节点处理完后，都满足：

- 当前点颜色为 $2$
- 子树内所有其他点颜色为 $1$
- 子树内所有边都已经连好了

所以如果是树的话，只需要 $3$ 种颜色就够了

---
推广到仙人掌上，建出圆方树，对于圆点的操作和树一样，考虑方点(环)怎么处理。

设当前方点 $x$，父亲为 $y$。那么找到 $x$ 对应的环，顺次处理这个环。沿用之前的思路，我们保证每一个点处理完后颜色都为 $2$，且集合内其他点颜色都为 $1$。于是我们依次合并两个相邻的儿子，设为 $a,b$。

- $r\ a\ 2\ 3$
- $j\ a\ b$
- $c\ a\ 2\ 3$
- $r\ a\ 3\ 1$

这样操作后，就连了一条 $(a,b)$ 的边，而且让 $a$ 的颜色改为了 $1$。

但是问题来了，到了最后一步我们需要把这条链的头尾连起来，怎么办呢？

这个时候就用上第 $4$ 种颜色了，对于第一个处理的节点，合并后我们不把它的颜色改为 $1$，而是改为 $4$。这样的话是不会影响连这条链的过程的，而且最后做一次连 $2,4$ 操作就可以把头尾连起来，然后再做一次改 $4$ 为 $1$ 保证性质。

---
关于操作次数，此题 $10^6=20n$，也就是说一个点能够进行 $20$ 次操作，显然我们的操作数远达不到这个上限。

---
上述就是大体思路，不过这题细节**十分多**。
### 细节1
在连链的时候，要**分三类**：

- 第一个点
	- $r\ x\ 2\ 4$
- 第二个点
	- $j\ x\ prv$
    - $c\ x\ 2\ 4$
- 其他点
	- $r\ prv\ 2\ 3$
    - $j\ x\ prv$
    - $c\ x\ 2\ 3$
    - $r\ x\ 3\ 1$

### 细节2
在具体实现方点的时候，假设方点 $x$，父亲 $y$。那么可以把这个环**除了 $y$** 之外的点先连成一条链。根据构建过程，这根链满足头为 $4$，尾为 $2$，其余点为 $1$。所以可以做：

- $r\ \text{链}\ 2\ 4$
- $j\ \text{链}\ y$
- $c\ y\ 2\ 4$
- $r\ y\ 4\ 1$

这样就一下连了两条边。(如果当前 $y$ 的颜色为 $1$，则还需要一次操作把 $y$ 的颜色改为 $2$)

### 细节3
由于在实现方点的时候，我们会修改 $y$ 的颜色。所以在处理圆点 $x$ 的时候，**如果有至少一个儿子是方点，就不执行改颜色的操作！** 因为这样会把 $y$ 集合中其他 $1$ 改为 $2$(`WA on 34`)。当然也要特判没有方儿子的时候，做一次改颜色 $1$ 为 $2$ 的操作。

[代码](https://www.luogu.com.cn/paste/wus3nfxy)

---

## 作者：Graphcity (赞：1)

一道比较巧妙且有意思的构造题。

首先操作次数的限制非常宽松，所以我们主要考虑只有四种颜色的限制。

每种颜色都应该有一个用途：

- 颜色 1：当前连通块的 LCA，与其它结点连边
- 颜色 2,3：连边过程中的中间结点
- 颜色 4：垃圾桶，所有没用的点都扔进去

仙人掌图必然要先建出来圆方树。用 Tarjan 建出来的圆方树有一个好性质：原图中相邻的点在遍历顺序中也是相邻的。

对圆方树进行 dfs，每次遍历一个方点时，都合并对应的环，然后让父亲结点颜色变为 1，其它结点颜色变为 4。

对于割边，我们只要 $\{1\},\{1\}\to \{1\},\{2\}\to\{1,2\}\to \{1,4\}$ 即可。

对于非割边，我们将父亲结点取出来，其它结点排成一个序列。我们希望，这个序列最后应该是 $3\to 4\to 4\to\cdots\to 2$ 这样的，这样只要连接父亲结点与首尾结点，再将首尾扔掉即可。

构造方法如下：

- 第一步：首结点颜色变为 2
- 第二步：依次向右枚举结点，通过跟割边类似的方法将 $\{2\},\{1\}$ 转变成 $\{4,2\}$。注意首结点和次结点较为特殊，应变成 $\{3,2\}$。

这样操作总次数为 $O(n+m)$ 级别，远小于限制。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

struct Node{int to,nxt;} Edge[Maxn*2+5];
int tot,Head[Maxn+5];
inline void Addedge(int x,int y)
{
    Edge[++tot]=(Node){y,Head[x]};
    Head[x]=tot;
}

int n,m,cnt,dfn[Maxn+5],low[Maxn+5];
int st[Maxn+5],top,cur;
vector<int> v[Maxn+5];

inline void Tarjan(int x)
{
    dfn[x]=low[x]=++cur,st[++top]=x;
    for(int i=Head[x];i;i=Edge[i].nxt)
    {
        int y=Edge[i].to;
        if(!dfn[y])
        {
            Tarjan(y),low[x]=min(low[x],low[y]);
            if(low[y]==dfn[x])
            {
                v[++cnt].push_back(x),v[x].push_back(cnt);
                while(1)
                {
                    int k=st[top--]; v[cnt].push_back(k),v[k].push_back(cnt);
                    if(y==k) break;
                }
            }
        }
        else low[x]=min(low[x],dfn[y]);
    }
}
vector<int> w; int id;
vector<array<int,4>> ans;
inline void Merge(int a,int b) {ans.push_back({0,a,b,0});}
inline void Change(int a,int c1,int c2) {ans.push_back({1,a,c1,c2});}
inline void Link(int a,int c1,int c2) {ans.push_back({2,a,c1,c2});}
inline void Solve()
{
    if(w.size()==1) Change(w[0],1,2),Merge(id,w[0]),Link(id,1,2),Change(id,2,4);
    else
    {
        Change(w[0],1,2);
        for(int i=1;i<w.size();++i)
        {
            Merge(w[i-1],w[i]),Link(w[i],1,2);
            if(i==1) Change(w[i],2,3); else Change(w[i],2,4);
            Change(w[i],1,2);
        }
        Merge(id,w[0]),Link(id,1,2),Link(id,1,3),Change(id,2,4),Change(id,3,4);
    }
    
}
inline void dfs(int x,int fa)
{
    for(auto y:v[x]) if(y!=fa) dfs(y,x);
    if(x>n)
    {
        w.clear();
        for(auto y:v[x]) if(y!=fa) w.push_back(y);
        id=fa,Solve();
    }
}

int main()
{
    n=read(),m=read(),cnt=n;
    For(i,1,m)
    {
        int a=read()-1,b=read(),c;
        while(a--) c=read(),Addedge(b,c),Addedge(c,b),b=c;
    }
    For(i,1,n) if(!dfn[i]) Tarjan(i);
    dfs(1,0);
    cout<<ans.size()<<endl;
    for(auto i:ans)
    {
        int op=i[0],a=i[1],b=i[2],c=i[3];
        if(op==0) printf("j %d %d\n",a,b);
        if(op==1) printf("r %d %d %d\n",a,b,c);
        if(op==2) printf("c %d %d %d\n",a,b,c);
    }
    return 0;
}
```

---

## 作者：_Clown_ (赞：1)

我们先来考虑树的情况怎么做：
- 在树上 dfs，不断**合并子树**。

我们只需要把深度**最浅**的点染成颜色染成颜色 $2$，其他染成颜色 $1$，然后在一个点合并子树时，它的颜色是 $3$，合并完之后可以把它的颜色改成 $2$。也就是在树上我们**只需要** $3$ 种颜色。

$\color{red}\text{在仙人掌上，需要特殊考虑的也只有环末了。}$

因为断环为链后，环末是链上深度最大的，但是我们又需要它连边，所以只要给它染颜色 $4$，然后在各种情况下特判即可。

在一个环深度**最浅**的地方，把颜色 $4$ 的边也连上去，同时把它染成 $1$。

在环的链传递时，判断一下后继是否是环末。其余的就是**类似树的**方法了。

剩下就只需要注意细节即可。细节比较繁琐，需要细心处理。代码鬼畜，细节繁多，无法突出重点，就~~不放~~了。

---

