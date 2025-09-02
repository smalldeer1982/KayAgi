# [USACO06JAN] Redundant Paths G

## 题目描述

为了从 F (1 <= F <= 5,000) 个牧场（编号为 1 到 F）中的一个到达另一个牧场，贝西和其他牛群被迫经过腐烂苹果树附近。奶牛们厌倦了经常被迫走特定的路径，想要修建一些新路径，以便在任意一对牧场之间总是有至少两条独立的路线可供选择。目前在每对牧场之间至少有一条路径，他们希望至少有两条。当然，他们只能在官方路径上从一个牧场移动到另一个牧场。

给定当前 R (F-1 <= R <= 10,000) 条路径的描述，每条路径恰好连接两个不同的牧场，确定必须修建的最少新路径数量（每条新路径也恰好连接两个牧场），以便在任意一对牧场之间至少有两条独立的路线。若两条路线不使用相同的路径，即使它们沿途访问相同的中间牧场，也被视为独立的。

在同一对牧场之间可能已经有多条路径，你也可以修建一条新路径连接与某条现有路径相同的牧场。


## 说明/提示

样例解释：

路径的一个可视化图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/cubnel5k.png)

从 1 到 6 和从 4 到 7 修建新路径满足条件。

![](https://cdn.luogu.com.cn/upload/image_hosting/rgguiytp.png)

检查一些路线：

- 1 – 2：1 -> 2 和 1 -> 6 -> 5 -> 2
- 1 – 4：1 -> 2 -> 3 -> 4 和 1 -> 6 -> 5 -> 4
- 3 – 7：3 -> 4 -> 7 和 3 -> 2 -> 5 -> 7

事实上，每对牧场之间都由两条路线连接。

添加其他路径也可能解决问题（例如从 6 到 7 的路径）。然而，添加两条路径是最少的。
（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
7 7
1 2
2 3
3 4
2 5
4 5
5 6
5 7```

### 输出

```
2```

# 题解

## 作者：说好不哭 (赞：104)

题解 P2860 【冗余路径】

注意：因为已有题解讲明白了题意和思路，所以我就不在此重复了，我只是想说明一下最简单清晰的一个方法——这就是一个求双联通分量的模板（当然，你也可以理解为无向图缩点）

所以，打一遍模板即可。当然，对于这个模板，我想要讲的清楚一些。

对于无向图的缩点，由于是无向图，所以要从u到v建一条边，又要从v到u建一条边，但是，在tarjan时会有两条边重复，这是一个麻烦，而且，还不得不建两条边，这该怎么办呢？

解决的方法就是，当同一条无向边的两条有向边的其中一条走过时，把另一条同时赋值为走过，这就要用到一个神奇的公式，^1。 举例来说，0^1=1,1^1=0; 2^1=3,3^1=2; 4^1=3,3^1=4......相信大家已经都发现了规律。而建边的时候，一条无向边的两条有向边刚好相差1，这不很OK嘛？问题解决了。

不过要注意，我的cnt，就是边的初始值，赋值为1，这是用来凑数字的。所以边，是从第2，3条；第4,5条......这样下去的（对于0,1条，因为自己代码习惯，我就直接从2开始了，0,1条加进去应该也可以，你想试的话也可以试试）

其余地方，就和有向图的缩点完全一样了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=5e3+5,M=1e4+5;
int n,m,vis[M<<1],du[N],ans;
int cnt=1,head[N],u[M],v[M];
int now,top,col,dfn[N],low[N],sta[N],color[N];
struct edge{int next,to;}e[M<<1];

inline void add(int u,int v)
{
	cnt++;
	e[cnt].next=head[u];
	e[cnt].to=v;
	head[u]=cnt;
	cnt++;
	e[cnt].next=head[v];
	e[cnt].to=u;
	head[v]=cnt;
}

inline void tarjan(int u)
{
	dfn[u]=low[u]=++now;	
	sta[++top]=u;
	for (register int i=head[u]; i; i=e[i].next)
	if (!vis[i])
	{
	vis[i]=vis[i^1]=1;
		if (!dfn[e[i].to])
		{
			tarjan(e[i].to);	
			low[u]=min(low[u],low[e[i].to]);
		}
		else low[u]=min(low[u],dfn[e[i].to]);
	}
	if (low[u]==dfn[u])
	{
		color[u]=++col;	
		while (sta[top]!=u) color[sta[top]]=col,top--;
		top--;
	}
}

int main(){
memset(head,0,sizeof(head));
memset(dfn,0,sizeof(head));
//下面过程如果不懂，看前面的几篇题解吧
	scanf("%d%d",&n,&m);
	for (register int i=1; i<=m; ++i) scanf("%d%d",&u[i],&v[i]),add(u[i],v[i]);
	for (register int i=1; i<=n; ++i) if (!dfn[i]) tarjan(i);
	for (register int i=1; i<=m; ++i) if (color[u[i]]!=color[v[i]]) du[color[u[i]]]++,du[color[v[i]]]++;
	for (register int i=1; i<=col; ++i) if (du[i]==1) ans++;
printf("%d\n",ans+1>>1);
return 0;	
}
```
# 代码可以当作模板收藏。


---

## 作者：BinDir0 (赞：64)

（写题解不容易，来[我的博客](https://www.cnblogs.com/lost-in-tianyi/)玩玩咯qwq~）

## 该题考察的知识点是边双连通分量

	边双连通分量即一个无向图中，去掉一条边后仍互相连通的极大子图。（单独的一个点也可能是一个边双连通分量）

	换言之，一个边双连通分量中不包含桥。

例如下图（样例）中的边双连通分量有$(1)$，$(2,3,5,6)$，$(4)$，$(7)$

![](https://i.loli.net/2019/04/07/5ca94d5387496.png)

不难发现，在一个边双连通分量中，任意两点都存在至少两条互相分离的路径；（如$1->2$与$1->3->2$）

如若不在一个边双连通分量中，则可能经过桥（甚至不联通）如：$2->4$。

由于桥是必须通过的，所以不存在两条互相分离的路径（或没有路径）。我们要做的，就是连边将整张图变成一张边双连通图。

## ~~（正文好像才开始）~~

首先是找出所有边双连通分量。不难发现，边双连通分量不包含桥，因此我们只需将桥无视掉，每一个连通的子图就是一个边双连通分量。（桥的公式大家都知道吧）代码如下：
```cpp
void tarjan(int u,int edge)
{	
    dfn[u]=low[u]=++num;
    for(int i=fst[u];i!=0;i=nex[i])
    {
        int v=to[i];
        if(!dfn[v])
        {
            tarjan(v,i);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v])	//桥的公式qwq
            {
                bridg[i]=bridg[i^1]=1;
            }
        }
        else if(i!=(edge^1))
            low[u]=min(low[u],dfn[v]);
    }
}
```


因为在一个边双连通分量中，任意两点都存在至少两条互相分离的路径，所以我们可以将其缩为一个点。缩完点之后，我们可以把它转换成一棵搜索树。

![](https://i.loli.net/2019/04/07/5ca94eb3be6d9.png)

我们会发现，去掉一条边后可能会与原树不连通的，是只连有一条边的边，即叶结点（设其数量为leaf）。为令原图 _边双连通_（我不知道这么说对不对），我们把两个叶结点为一组用新边将其连接起来。这么看，答案似乎是$leaf\div2$了。

且慢！！让我们看看上图。上图$leaf=3$，而$leaf\div2=1$。事实上，我们需要2条边。所以最终公式为$(leaf+1)\div2$。（终于完了qwq）

最后捋一捋思路：

- 找边双连通分量

- 缩点

- 建树，找$leaf$

- $ans=(leaf+1)\div2$

### 完结撒花qwqwqwqwqwq

code：

```cpp
//Author:夏目贵志
#include<bits/stdc++.h>
using namespace std;
int qwwq,fst[10100],nex[10100],to[10100],a,b,cnt,num,cutn,bridg[10100],br,u[10100]; 
int dfn[10100],low[10100],ans,f[10100],root,pl,n,m,size,t,dcc,c[10100],du[10100];
void add(int a,int b)
{
    nex[++t]=fst[a];
    u[t]=a;
    to[t]=b;
    fst[a]=t;
    return ;
}
void tarjan(int u,int edge)
{	
    dfn[u]=low[u]=++num;
    for(int i=fst[u];i!=0;i=nex[i])
    {
        int v=to[i];
        if(!dfn[v])
        {
            tarjan(v,i);
            low[u]=min(low[u],low[v]);
            if(dfn[u]<low[v])
            {
                bridg[i]=bridg[i^1]=1;
            }
        }
        else if(i!=(edge^1))
            low[u]=min(low[u],dfn[v]);
    }
}
void dfs(int u)
{
    c[u]=dcc;
    for(int i=fst[u];i!=0;i=nex[i])
    {
        int v=to[i];
        if(c[v]!=0||bridg[i]==1)
        continue;
        dfs(v); 
    } 
}
int main()
{
    scanf("%d%d",&n,&m);
    t=1;
    for(int i=1;i<=m;i++)
    {
     	scanf("%d%d",&a,&b);
     	add(a,b);add(b,a);
    }
    tarjan(1,0);
    for(int i=1;i<=n;i++)
    {
        if(!c[i])
        {
            dcc++;
            dfs(i);
        } 
    }
    for(int i=1;i<=m;i++)
    {
     	if(c[u[i*2]]!=c[to[i*2]])
     	{
     		du[c[u[i*2]]]++;
     		du[c[to[i*2]]]++;
     	}
    }
    for(int i=1;i<=dcc;i++)
    {
    	if(du[i]==1)
    	br++;
    }
    cout<<(br+1)/2;

    
    
    
    return 0;
}

```


---

## 作者：hsfzLZH1 (赞：40)

此题就是在图上加上最少的边，使得所有的节点都在环上（可能是不同的环）。

我们考虑$Tarjan$算法。首先将所有边-双连通分量缩成点，将整个图转变为一个树，然后在这个规模更小的图上加最小的边，使得所有缩成的点都在环上。

描述一下$Tarjan$算法的过程。对于一个无向的连通分量，制定一个根节点，从这个节点开始进行$DFS$遍历，能形成一个$DFS$树。在$DFS$的过程中有一个访问顺序，定义为$dfn_i$，即该节点的时间戳。定义一个$low_i$，定义为**该节点不经过其到$DFS$树上父亲节点的边，中间只能经过其在$DFS$树上的子孙节点，最后能够到达的最小时间戳**（是不是很长）。

有了$Tarjan$算法，我们就可以在遍历一棵树的时间复杂度$O(N)$中，处理每个节点的信息。如果一个节点$i$的$dfn_i=low_i$，那么它的$DFS$树上的孩子都“很不争气”，到不了比当前节点时间戳更早的节点，所以节点$i$属于一个新的双连通分量。

我们可以利用一个简单的数据结构——栈，去判断每个节点归属的双联通分量。在$DFS$开始的过程中，将该节点的编号压入一个栈，在$DFS$向其他节点的遍历结束时，如果满足新的边-双连通分量的条件，不停地将栈顶的元素弹出，知道弹出的元素是当前元素，终止操作。这样所有弹出的点都归属于一个边-双联通分量。

将每个节点所归属的边-双连通分量后，我们可以将归属于一个边-双连通分量缩成新图上的一个节点，这样所形成的每个连通分量就是一棵树。然后我们需要证明一个定理：**这个连通分量上的广义叶子节点（度数为$1$）除以$2$向上取整即为所需要加的边数**。

前面相信有很多大佬给出了证明，这里概述如下：题目要求的是所有点至少度数为$2$，度数为$1$的点应该至少连一条边，最好的方法当然是一次性连两个度数为$1$的点，如果最后没有匹配（个数为奇数），仍然要连边，所以得出结论。

上代码：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<stack>
using namespace std;
const int maxn=5010;
const int maxm=20010;
int n,m,u[maxn],v[maxn],x,y,cur,h[maxn],nxt[maxm],p[maxm],index_,dfn[maxn],low[maxn],bcc[maxn],deg[maxn],ans,ltt;
bool tf[maxm];
stack<int>st;
inline void add_edge(int x,int y)
{
    cur++;
    nxt[cur]=h[x];
    h[x]=cur;
    p[cur]=y;
}
void dfs(int cur)
{
    dfn[cur]=low[cur]=++index_;
    for(int j=h[cur];j!=-1;j=nxt[j])if(tf[j])
    {
        int i=p[j];
        if(dfn[i])low[cur]=min(low[cur],dfn[i]);
        else
        {
            st.push(i);
            tf[j]=tf[(j&1)?j+1:j-1]=false;
            dfs(i);
            tf[j]=tf[(j&1)?j+1:j-1]=true;
            low[cur]=min(low[cur],low[i]);
        }
    }
    if(dfn[cur]==low[cur])
    {
        ans++;
        while(!st.empty())
        {
            bcc[st.top()]=ans;
            if(st.top()==cur){st.pop();break;} 
            st.pop();
        }
    } 
}
int main()
{
    memset(h,-1,sizeof h);
    memset(tf,true,sizeof tf);
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)scanf("%d%d",u+i,v+i),add_edge(u[i],v[i]),add_edge(v[i],u[i]);
    for(int i=1;i<=n;i++)if(!dfn[i])ans=0,st.push(i),dfs(i);
    for(int i=0;i<m;i++)if(bcc[u[i]]!=bcc[v[i]])deg[bcc[u[i]]]++,deg[bcc[v[i]]]++;
    for(int i=1;i<=n;i++)if(deg[i]==1)ltt++;
    printf("%d\n",(ltt+1)/2);
    return 0;
}
```

---

## 作者：Belarus (赞：37)

Update 2020/11/22：修复了一个小错误。   

Update 2021/09/30：修复了一个大错误，更新了更严谨的证明。



**注意：本题解主要详细讲解为什么答案是 $\lfloor\dfrac{s+1}{2}\rfloor$($s$ 为叶子节点数)** 


首先我们要明白：  **进行 e-DCC 缩点之后，最终形成的图是一棵树。**

因为：  假设缩点之后的图不是树，那么一定存在一个环，因此这个环还可以缩成一个点，这产生了矛盾。

接下来讲解为什么是 $\lfloor\dfrac{s+1}{2}\rfloor$：  

这个公式实际上是**对 $s$ 奇偶性的讨论得出来的通式**。  

先看 $s$ 为偶数的情况。  

不妨从基环树下手，考虑先连两个叶子节点。



## Step 1

那么让我们先证明一个结论：**存在叶子节点 $x,y$，连接 $(x,y)$ 后构成的基环树有偶数个支链**。

所谓支链，就是基环树环上的点向外连边的个数。

**证明过程（反证法）**：

假设所有连边方案中，基环树都有奇数个支链。那么对于画出这样的图：  

![图片.png](https://i.loli.net/2021/09/30/el6kqmYdtJNbFpi.png)

（那些歪歪曲曲的代表其他支链）

那么我们现在断开 $(x,y)$，将 $y$（$x$ 也行，这里取一个来证明）与一个支链的末端叶节点相连。

![图片.png](https://i.loli.net/2021/09/30/H6xgadcykj32bzQ.png)

那么可以发现 $y$ 处于一个新的环中（下图青色）。

![图片.png](https://i.loli.net/2021/09/30/W6mkgOZRISHPcfj.png)

根据假设，这个环应该拥有奇数个支链。

$x$（或者说 $lca$）所在的这条链上为环贡献一个支链，那么根据假设，这个环上的其他地方，也就是原图中的那一条支链上，必须拥有偶数个支链。

但实际上我们开始假设时，是对任意图的，所以不一定在这条链上有偶数个支链，产生矛盾，假设不成立。

所以，**存在叶子节点 $x,y$，连接 $(x,y)$ 后构成的基环树有偶数个支链**。



## Step 2

我们将对这个拥有偶数条支链的基环树做一些处理。

以下面这个图为例：

![图片.png](https://i.loli.net/2021/09/30/K8hX67baQJORgB5.png)

我们将不同支链上的叶子节点两两配对，直到无法配对为止。

![图片.png](https://i.loli.net/2021/09/30/adntC32XqIxY5yf.png)

可以看到，这上面每两个点都有至少两条分离路径。

但是这是运气好的情况，假如运气不好，出现这样的情况呢：

![图片.png](https://i.loli.net/2021/09/30/a9tuny3gTrjOB1X.png)

$(9,10)$ 和 $(12,14)$ 连了之后，是无法满足条件的。

症结就在于它们的 $lca$ 不在环上，所以这种情况**是绝对不可以出现的**！

但是运气很差，这种情况就是出现了。那么接下来我们要证明的就是，**这种情况是可以改变成一个合法的解的**。

以下图为例：

![图片.png](https://i.loli.net/2021/09/30/MXfV6qkw9APOiev.png)

方便起见，我省去了所有已经配对的链，简化为一个环。

可以证明，这些遗留下来的叶子节点一共有偶数个（因为本来有偶数个，两两配对，不能配对到最后肯定剩偶数个）。

并且这个环上面一定有两个叶子节点（毕竟环就是这样构造出来的），我们姑且设为 $3,4$。

断开 $(3,4)$，连接 $(3,8),(4,9)$，得到：

![图片.png](https://i.loli.net/2021/09/30/qw8fWVSlvHUR35O.png)

这时候连接 $(6,7)$，就满足条件了：

![图片.png](https://i.loli.net/2021/09/30/JvtTn4e68uBKOLU.png)

可以见得，遇到这种情况，我们**断开环上的叶子节点，将其与两个未配对的叶子节点相连，构成一个新的大环**。

此时剩余的叶子节点的 $lca$ 就在环上了。

当然这是一种情况，还有其他情况，比如：

![图片.png](https://i.loli.net/2021/09/30/eN8QrDjGCo3vmZU.png)

证明方法类似，不再赘述。

这样，每个叶子节点都只与一个叶子节点相连，所以总共 $\dfrac{s}{2}$ 个新增的边。



那么接下来，奇数就好办了，只要新增的这个节点与已经成体系的“大环”上一点相连，就满足条件。

因此奇数时答案为 $\dfrac{s+1}{2}$。  



综合两者，得出答案为 $\lfloor\dfrac{s+1}{2}\rfloor$。完结撒花！



~~这估计是这个题第一篇完整证明了这个结论的题解吧~~



---

## 作者：KSkun (赞：13)

## 解题思路

分析题目这一句：两条路径相互分离，是指两条路径没有一条重合的道路。联想到无向图中桥的概念，可以得到结论：只要这个图中不存在桥，那么就一定存在两条相互分离的路径。因此这个题目可以理解为求把给定无向图转换成不含桥的无向图所需连边的最少数量。


这里的最少数量如何求解？实际上等到我们把原图中所有的桥找出来以后，对不含桥的连通块缩点，会发现最后剩下的图是一个树。添加最少的边使这棵树上所有的链都变成环，则是本题的答案。这个答案可以由这棵树叶子节点数/2向上取整得出。（贪心，比较显然）


以题目样例为例：


（1）把这个图中的桥找出来，下图中，绿色框中的即为不含桥的连通块，共4个，框与框之间的边就是桥。



 ![](https://cdn.luogu.com.cn/upload/pic/8546.png) 

（2）缩点。



 ![](https://cdn.luogu.com.cn/upload/pic/8547.png) 

（3）缩完点原图变成树，如图是一组最优解。解不唯一，但是建边的数量固定。



 ![](https://cdn.luogu.com.cn/upload/pic/8548.png) 

实现上，Tarjan找一下桥，把桥断掉后找连通块并且缩点，整理出新的图，对图中结点统计度数，度数为1的就是叶子节点。计数叶子节点就可以得到答案了。



## 程序


```cpp
// Code by KSkun, 2017/10 
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

struct Edge {
    int to, nxt;
    bool vis;
    
    Edge() {}
    Edge(int t, int n):to(t), nxt(n) {}
} gra[20005];
int ecnt = 0, head[5005];

bool gra1[5005][5005];

void conn(int u, int v) {
    gra[ecnt] = Edge(v, head[u]);
    head[u] = ecnt;
    gra[ecnt + 1] = Edge(u, head[v]);
    head[v] = ecnt + 1;
    gra[ecnt].vis = gra[ecnt + 1].vis = false;
    ecnt += 2;
}

int f, r;

int dfn[5005], low[5005], par[5005], step = 1;

// Tarjan找桥 
void dfs(int u) {
    dfn[u] = low[u] = step++;
    int e = head[u];
    while(e != -1) {
        if(gra[e].vis) {
            e = gra[e].nxt;
            continue;
        }
        gra[e].vis = gra[e ^ 1].vis = true;
        if(dfn[gra[e].to] == 0) {
            par[gra[e].to] = e;
            dfs(gra[e].to);
            low[u] = min(low[gra[e].to], low[u]);
        } else {
            low[u] = min(dfn[gra[e].to], low[u]);
        }
        e = gra[e].nxt;
    }
}

int lable[5005];

void sd(int u, int num) {
    lable[u] = num;
    int e = head[u];
    while(e != -1) {
        if(gra[e].vis && lable[gra[e].to] == 0) {
            sd(gra[e].to, num);
        }
        e = gra[e].nxt;
    }
}

int du[5005];

int main() {
    memset(head, -1, sizeof head);
    scanf("%d%d", &f, &r);
    int a, b;
    // 链式前向星，建图 
    for(int i = 0; i < r; i++) {
        scanf("%d%d", &a, &b);
        conn(a, b);
    }
    dfs(1);
    // 这里把桥断掉 
    for(int i = 1; i <= f; i++) {
        int opp = par[i] ^ 1;
        int oppp = gra[opp].to;
        // 这里是核心，桥的一个性质就是桥的两个端点中，一个端点的low大于另一个端点的dfn
        // 这是因为桥的两端分别是两个连通块（环），前面一个桥上的点DFS序肯定要比桥另一端的所有点DFS序大 
        if(low[i] > dfn[oppp]) {
            gra[par[i]].vis = false;
            gra[opp].vis = false;
        }
    }
    // 缩点 
    int num = 1;
    for(int i = 1; i <= f; i++) {
        if(lable[i] == 0) {
            sd(i, num++);
        }
    }
    // 把缩完点的图整理出来，用矩阵存了一下 
    for(int i = 1; i <= f; i++) {
        int e = head[i];
        while(e != -1) {
            gra1[lable[gra[e].to]][lable[i]] = gra1[lable[i]][lable[gra[e].to]] = true;
            e = gra[e].nxt;
        }
    } 
    // 统计结点度数 
    for(int i = 1; i < num; i++) {
        for(int j = 1; j < num; j++) {
            if(i != j && gra1[i][j]) du[i]++;
        }
    }
    // 统计叶子节点数量 
    int ans = 0;
    for(int i = 1; i < num; i++) {
        if(du[i] == 1) ans++;
    } 
    printf("%d", (int) ceil(ans / double(2)));
    return 0;
}
```

---

## 作者：violinwang (赞：11)

<font face="微软雅黑">
  本题目的： 
  使每两个点之间至少有两条相互分离（即不同的）的路径。


<font face="微软雅黑">
### 思路：可以发现，在一个环中，从A到B都至少有2条路径，因此先解决环
	
<font face="微软雅黑">
	栗子如下：
    
![](http://a2.qpic.cn/psb?/V141COev2OWXS3/oFBdk8AqgVC2gNGOpNtJyvf02uAqulLHK4BjswZwm.s!/c/dGEBAAAAAAAA&ek=1&kp=1&pt=0&bo=0QGKAdEBigEBACc!&vuin=2602723959&tm=1519668000&sce=60-2-2&rf=0-0)


#### 因此，先无向图找到各个边双连通分量或者说是桥（不严谨地说，找环）

### 思考如何连剩下的边使得全图成为一个环，边数最少

#### 方法：找到后数数有多少个点只连有一条边

#### 手动模拟一下发现，任意一张图都可以转换->叶子结点相互连边

#### （因有题解贴上图，这里就不贴了，有问题可以发私信给我）

#### 发现最少连边为（只连有一条边的点数+1）÷2

------------


#### 整体代码来一波


```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iostream>
#define N 100600
#define M 500000
using namespace std;
struct node{int u,v,nxt;}e[M];

int n,m,K,hed[N],dfn[N],lows[N],Cnt,E[N],dcc;
//	n->点数	m->边数	K->加边操作中边号	hed[i]->前向星
//	Cnt:55行	
//	E[i]:点i所在的边双联通分量的编号	dcc:计边双连通分量号

bool bri[M];
void ad (int u,int v){
    e[++K].u=u;e[K].v=v;e[K].nxt=hed[u];hed[u]=K;
}	//加边操作


void dfs (int x,int fa){
    dfn[x]=lows[x]=++Cnt;
    for (int i=hed[x];i;i=e[i].nxt){
        int v=e[i].v;
        if (!dfn[v]){
            dfs (v,x);
            lows[x]=min(lows[x],lows[v]);
            if (lows[v]>dfn[x])	{
                bri[i]=true;i%2==0?bri[i-1]=true:bri[i+1]=true;	//双向边，很重要
           //当然可以不这样存，不过习惯了
            }
        }
        else if (v!=fa)	lows[x]=min(dfn[v],lows[x]);//v!=fa
    }
}

void dfs2 (int x){
    E[x]=dcc;//将x装入边双联通 dcc中 
    for (int i=hed[x];i;i=e[i].nxt){
        if (bri[i]==true)	continue;//跳过桥
        int v=e[i].v;
        if (!E[v])	dfs2(v);//没有更新过便更新
    }
}

int chudu[N];//记录出度

void dfs3(){
    for (int i=1;i<=K;++i){//遍历每条边，K不能改成m哦，双向，改成m*2可以
        int u=e[i].u,v=e[i].v;
            if (E[u]!=E[v]){
            chudu[E[u]]++;
            chudu[E[v]]++;
			//也可以注销掉一行，那么下面的ans++的判断条件改为chudu[i]==1	[原因是因为原图双向]
        }
    }
    int ans=0;
    for (int i=1;i<=dcc;++i){
        if(chudu[i]==2)	ans++;
    }
    printf("%d\n",ans+1>>1);// >>1等价于÷1，根据运算符先后级，实现功能为先加后除
} 

int main (){
    scanf ("%d%d",&n,&m);
    int u,v; 
    for (int i=1;i<=m;++i){
         scanf ("%d%d",&u,&v);
         ad(u,v);ad(v,u);//双向
    }
    
    for (int i=1;i<=n;++i)
        if(!dfn[i])	dfs (i,-1);//点i没有更新过dfn值便更新
        
    for (int i=1;i<=n;++i){
        if (!E[i])
            dcc++,dfs2(i);//点i没有更新过E[i]值便更新
    }
    
    dfs3();
    return 0;
} 
```


这道题写法有很多种，希望大家不要局限于一种方法，思想到位即可，代码应自己写，形成自己的代码风格。

想说一点的是：大部分写法最后是遍历判断，存图操作不一定需要，能省就省啦！



---

## 作者：Alex_Wei (赞：10)

> [P2860 [USACO06JAN]Redundant Paths G](https://www.luogu.com.cn/problem/P2860)
>
> [初级图论](https://www.cnblogs.com/alex-wei/p/basic_graph_theory.html)。

题目相当于添加最少的边使得整张图变成一个边双。

考虑边双缩点得到缩点树 $T$，其上所有边都是原图割边。显然，如果在 $u, v$ 之间加一条边，设 $U$ 为 $u$ 所在边双对应的缩点树上的结点，$V$ 同理，则相当于将 $U, V$ 简单路径上的所有边变成非割边。

我们希望用最少的路径覆盖 $T$ 的每一条边。对此有经典结论：最小路径数为 $T$ 的叶子个数除以 $2$ 上取整。

证明这是答案下界非常容易，因为每条链至多覆盖两个叶子到它唯一相邻的点的边。当只有两个点的时候特殊讨论。接下来给出一个达到该下界的构造方法。

称两个叶子匹配表示在最终方案中，存在一条连接它们的链。

首先，当叶子个数为奇数时，考虑任意一个叶子 $u$，从它出发找到第一个度数 $\geq 3$ 的结点 $v$，令 $u, v$ 匹配，转化为叶子个数为偶数的情况。如果不存在度数 $\geq 3$ 的结点，则 $T$ 为一条链，与叶子个数为奇数矛盾。

先将所有叶子任意两两匹配，再调整。设在当前方案中，存在一条边 $(u, v)$ 没有被覆盖，设断开 $(u, v)$ 后 $u, v$ 分别属于连通块 $U, V$。

$U$ 或 $V$ 不可能只有一个原树的叶子，否则该叶子和另外某个叶子匹配时必然经过 $(u, v)$，与 $(u, v)$ 没有被覆盖矛盾。同理可证 $U$ 或 $V$ 不可能有奇数个叶子。

因此，当前方案必然是 $U$ 的所有偶数个叶子两两匹配，$V$ 的所有偶数个叶子两两匹配。设 $U$ 的某两个匹配的叶子为 $u_1, u_2$，它们在以 $u$ 为根时的 LCA 为 $u_d$。对于 $V$，类似定义 $v_1, v_2$ 和 $v_d$。

当前方案覆盖了 $u_1\to u_d \to u_2$ 和 $v_1 \to v_d \to v_2$ 的所有边，但令 $u_1$ 和 $v_1$，$u_2$ 和 $v_2$ 匹配，$u_i\to u_d \to u\to v \to v_d \to v_i$ 的所有边被覆盖。原来被覆盖的边仍被覆盖，同时 $(u, v)$ 也被覆盖了。

因此，对于当前方案，若某条边没有覆盖，通过上述调整一定能不改变链的条数使得原来被覆盖的边仍被覆盖，且该边也被覆盖。答案上界得证。

时间复杂度 $\mathcal{O}(n + m)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 5e3 + 5;
int n, m, dn, deg[N], dfn[N], low[N];
int cn, col[N], stc[N], top;
vector<pair<int, int>> e[N];
void form(int id) {
  cn++;
  for(int x = 0; x != id; ) col[x = stc[top--]] = cn;
}
void tarjan(int id, int eid) {
  stc[++top] = id, dfn[id] = low[id] = ++dn;
  for(auto _ : e[id]) {
    if(_.second == eid) continue;
    int it = _.first;
    if(!dfn[it]) {
      tarjan(it, _.second);
      low[id] = min(low[id], low[it]);
      if(low[it] > dfn[id]) form(it);
    }
    else low[id] = min(low[id], dfn[it]);
  }
  if(!eid) form(id);
}
int main() {
  cin >> n >> m;
  for(int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    e[u].push_back(make_pair(v, i));
    e[v].push_back(make_pair(u, i));
  }
  tarjan(1, 0);
  for(int i = 1; i <= n; i++)
    for(auto _ : e[i]) {
      int it = _.first;
      if(i < it && col[i] != col[it]) deg[col[i]]++, deg[col[it]]++;
    }
  int leaf = 0;
  for(int i = 1; i <= cn; i++) leaf += deg[i] == 1;
  cout << (leaf + 1 >> 1) << endl;
  return cerr << "Time: " << clock() << endl, 0;
}
```

---

## 作者：quest_2 (赞：8)

_捞一下蒟蒻[Blog](https://www.luogu.com.cn/blog/quest233/#)_

_这篇文章重在讲解在切这道题时是如何想到正解的。_

记得有一位巨佬说过，每一道题都是板子套板子套板子套$\cdots \cdots$ ，也就是 $({\color{black}\colorbox{white}{板子}})^K$。

有了这一基础理论，我们就想想什么板子是可以套上这题的。

先来看题意，稍加简化便是这样：

```
有一无向图。
要求加一些边，使得每两个点之间至少有两条边相连。
求最少加边数。
```
`至少有两条边相连`？容易看出这是一道图论题，甚至可以看出是一道**图的连通性专题的图论题**。

说到图的连通性，就必然会想到一个令人膜拜的人物，$\mathbf{Tarjan}$ 。几乎所有的图的连通性题目都和他发明的算法，借助于时间戳的跑强连通分量/桥/割点等等的神仙操作有关。那我们如何运用这些神仙操作完成任务呢？

至少有两条边相连，也就是说，**删去任意两点之间的一条路径后，这两点依然联通**。

删去任意两点之间的一条路径后，这两点依然联通？

我们想起桥的定义：删去两点之间的一条路径后，这两点不再联通。

实在很难不把他们俩想到一块去。

如果把原图中的所有桥都删掉，会留下一些联通块。这些联通块就满足题中说的：两点间至少有两条边相连。

而这种联通块，学名称作**边双联通分量**，可以发现一个规律：边双联通分量中两点之间**不会因为加边而减少整幅图中原有的桥**。

毕竟他们可是在拆桥运动后仍然存活的 ${\color{red}\colorbox{white}{牢不可破的联盟}}$ ，已经没有再加固联盟的必要了。

所以我们要加固的，实则是那些在拆桥运动后，支离破碎的结点。

这一步骤，一样可以用Tarjan算法完成，用类似**Tarjan求强连通分量**的染色法。在同一个边双联通分量中的点会被染上同一个颜色。同一种颜色的结点，又可以用**Tarjan缩点**的思想。把一个边双联通分量缩成一个结点。

 _（注：这里说一下，我们做这道题时只需要用到桥的概念和强连通分量的一种操作思想，这两个东西是不用敲的，所以不用慌\fad。）_ 

又因为删完桥后，桥的两端点会分到两个不同的联通块里。所以一个桥的两端**必然是不同的颜色**，也就不能被缩到一起。

所以缩点后的图会必然成为一棵树的形状，如图～

![](https://cdn.luogu.com.cn/upload/image_hosting/nlek31o2.png)

可以看到将边双联通分量缩成一点后，图变成了树。

这时候我们就会参悟到，我们的加边实则是要把这整棵树边变成一个边双连通分量。

我们要找的是支离破碎的点，支离破碎是删完桥之后的事情了。拆桥之前，这种点仅仅依靠一座可怜的桥与其他部分保持联系。

这样可怜的情况体现在缩点后的树上，就是**从一个点开始遍历，一个支离破碎的点被跑到的次数只有一次**。

那我们就在跑树上遍历的时候记录这个点的入度 $in$ 。**入度为1**的点就是支离破碎点。

现在要加边连接这些支离破碎点了。这里我们打算 $O(1)$ 得出。可以想出，每次我们的加边行为都得连接两个破碎点。

 如果有两个破碎点，加一条边连接他们，这两个点就不再仅有一座桥与外界联通了。

那如果有三个呢，最最简单的图就是一个根下面仨儿子，这种情况下，我们只需连两条边即可加固所有的破碎点。（不妨YY一波）

以三个点**呈三角形互相连边**（~~稳定的三角关系~~ $\bigtriangleup$ ）应该是最最简单的边双联通分量单位。

而每两个破碎点在树上与他们的公共祖先的关系一定是呈大小不定的 $\bigwedge$ 字形状，要形成三角关系只需要**再加一笔**。即**一笔至多加固两个破碎点**。

- 所以破碎点为偶数个时，加边数为 $\dfrac{N}{2}$ 。

- 而奇数个时，总是会剩一个不能组成三角关系，那就需要多加一条边，让剩下的这个点随便和一个三角关系连接，加边数为 $\dfrac{N}{2}+1$ 。

这两个式子我们又可以合二为一，即加边数 $\left\lfloor\dfrac{(N+1)}{2}\right\rfloor$ 。

至此我们有了正解。

~~无非无向图缩点板子~~。（首尾呼应）

实现如下：

```cpp
#include <iostream>
#include <stack>
using namespace std;
const int MAX = 2e4 + 7;
int N, M;

/*前向星组件*/
struct edge
{
     int to;
     int next;
} e[MAX << 2];
int head[MAX], eid = 0;
void adde(int x, int y)
{
     e[++eid].to = y;
     e[eid].next = head[x];
     head[x] = eid;
}

/*Tarjan缩点组件（贺板子就完事）*/
int low[MAX], dfn[MAX], t = 0, cnt = 0, id[MAX], in[MAX];
stack<int> st;
void tarjan(int u, int lst_e)
{
	
     low[u] = dfn[u] = ++t;
     st.push(u);
     //tarjan特色
     for (int i = head[u]; i; i = e[i].next)
     {
          int v = e[i].to;
          if (!dfn[v])
          {
               tarjan(v, i);
               low[u] = min(low[u], low[v]);//更新
          }
          else if (i != (lst_e ^ 1))
          //这里因为是无向图，输入一条无向边我们会存入两条有向边
          //但这样会在tarjan时导致二人转（雾
          //故还要判这是不是上一条边的反边
          //用异或表示反边的骚操作属实秀
          //但注意边的id要从1开始计数
          //否则就用不了骚操作
          {
               low[u] = min(low[u], dfn[v]);//更新
          }
     }
     if (low[u] == dfn[u])//若这一联通块结束了
     {
          int k;
          ++cnt;
          while (k != u)
          {
               k = st.top();
               st.pop();
               id[k] = cnt;//染色
          }
     }
}
int main()
{
     cin >> N >> M;
     eid = 1;
     //谨记！！！！！
     for (int i = 1; i <= M; i++)
     {
          int fr, to;
          cin >> fr >> to;
          adde(fr, to);
          adde(to, fr);
     }
     for (int i = 1; i <= N; i++)
     {
          if (!dfn[i])
          {
               tarjan(i, -1);//Tarjan基操
          }
     }
     for (int u = 1; u <= N; u++)
     {
          for (int i = head[u]; i; i = e[i].next)
          {
               int v = e[i].to;//前向星遍历
               
               if (id[u] == id[v])
                    continue;
                    //这里就看出缩点的意味了
                    //同一联通块的在这里默认缩成一点
                    //不会遍历过去
                    
               in[id[v]]++;//记录入度
          }
     }
     int res = 0;
     for (int i = 1; i <= cnt; i++)
     {
          if (in[i] == 1)
          {
               res++;//统计破碎点
          }
     }
     cout << (res + 1) / 2 << endl;//出解
}
```

那位大佬说的没错，无非一道板子题（~~再 放 送~~）。

---

## 作者：Caicz (赞：5)

### 初看题目，有点懵

#### 再一看：
**什么？两条路？图？连通？**

这些关键字一来，自然就想到了**我们 ~~可爱又迷人~~的tarjan桑**，即可以像[P2746](https://www.luogu.com.cn/problem/P2746)一样缩点，统计每个强连通分量的入度，出度，取最大值。


------------

**等等，无向图？**

**ヽ ( # ` Д ´ ) ﾉ**似乎不能~~双倍经验~~**同类迁移**了啊

但是， 没有问题，我们可以将无向边转换为**最优**有向边，转而求出强连通分量，并缩点，由于数据保证图一定连通，即不存在度数为0的点，那么我们就可以只统计入度为 1 的点的个数**num**，并将他们两两相连。
**那么答案 num/2 并向上取整**

- 那么，如何将无向边转化为**最优有向边**呢？

那就要安利一个~~大宝贝~~ **“^” 二进制异或运算符**

它可以将二进制下的的数 同为 1或0 变为 0，不同则为 1；

那么我们具体应该如何使用呢？

已知我们存图所用为**前向星存图**（什么？你不会前向星，那么请先学好，学扎实图基础，再来学tarjan）由于是无向图，我们会将每条边存两遍，而其中能走过去的边即为以当前为起点的最优有向边

**而我们走了该条边之后，因为我们是当有向图处理，自然回来的那条边也不能走**，所以我们用 **vis[i]=true**表示这条边已走过，但如何表示反向的边呢？

我们首先应明白 **x^1==(x==偶数 ? x+1：x-1)**
也就是说只要我们将每一条无向边的正向边的边号储存为偶数，反向边的边号储存为奇数，只要经过了该条边既可以进行标记**vis[i]=vis[i^1]=true**



------------


代码核心：
```cpp

void tarjan(int u,int fa)
{
	dfn[u]=low[u]=++cnt;
	s[++top]=u,ins[u]=true;
	for(int i=head[u];i;i=e[i].last)
	{
		if(vis[i])continue;
		vis[i]=vis[i^1]=true;
		int v=e[i].v;
		if(!dfn[v])
		{
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
		}
		else if(ins[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u])
	{
		so[u]=++bcnt;
		ins[u]=false;
		while(u!=s[top])
		{
			so[s[top]]=bcnt;
			ins[s[top]]=false;
			top--;
		}
		top--;
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a[i],&b[i]);
		add(a[i],b[i]);
		add(b[i],a[i]);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])tarjan(i,i);
	for(int i=1;i<=m;i++)
	{
		if(so[a[i]]!=so[b[i]])
			++r[so[a[i]]],++r[so[b[i]]];
	}
	for(int i=1;i<=bcnt;i++)
	{
		if(r[i]==1)
			ans1++;
	}
	printf("%d\n",(ans1+1)/2);
	return 0;
}
```

## 注意：

在毒瘤出题人的毒瘤数据中，存在**重边！**





---

## 作者：水库中的水库 (赞：3)

这道题可以转换为一句话题意：给定一个图，求需要添加几条边使其成为边双连通图

可以证明在一个边双连通图里的点之间的连边是不会减少桥的数目的

所以我们可以把每个双联通子图缩为一个点

双联通子图的求法为：先求出每个桥，删除这些桥剩下的每个联通块都是一个双联通子图

再将所有桥添加，可以得到一个树

答案就是这棵树的(叶子节点个数+1)/2

```cpp
/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年05月21日 星期二 09时35分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1000010;

int Begin[maxn], Next[maxn], To[maxn], e, be[maxn], cnt;
int low[maxn], dfn[maxn], n, m, p[maxn], ans, tot, degree[maxn];
bool vis[maxn];
stack<int> Stack;

inline void add(int u, int v)
{
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; be[e] = e + 1;
	To[++ e] = u; Next[e] = Begin[v]; Begin[v] = e; be[e] = e - 1;
}

inline void Tarjan(int u)
{
	low[u] = dfn[u] = ++ cnt; Stack.push(u);
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		vis[i] = true;
		if ( !vis[be[i]] ) 
		{
			int v = To[i];
			if ( !dfn[v] ) { Tarjan(v); low[u] = min(low[u], low[v]); }
			else low[u] = min(low[u], dfn[v]);
		}
	}
	if ( low[u] == dfn[u] ) 
	{
		p[u] = ++ tot;
		while ( Stack.top() != u ) 
		{
			p[Stack.top()] = tot; Stack.pop();
		}
		Stack.pop();
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); }
	Tarjan(1);
	REP(u, 1, n)
		for ( int i = Begin[u]; i; i = Next[i] ) 
		{
			vis[i] = false;
			if ( vis[be[i]] ) 
			{
				int v = To[i];
				if ( p[u] != p[v] ) { ++ degree[p[u]]; ++ degree[p[v]]; }
			}
		}
	REP(i, 1, tot) if ( degree[i] == 1 ) ++ ans;
	printf("%d\n", (ans + 1) / 2);
    return 0;
}
```

---

## 作者：风随逐影 (赞：3)

## 边双联通分量模版

先用tarjan找桥，再找到e-dcc。

我们可以将每个边-双连通分量缩成新图上的一个节点，这样所形成的每个连通分量就是一棵树。然后我们需要证明一个定理：**这个连通分量上的广义叶子节点（度数为1）除以2向上取整即为所需要加的边数。**

统计出叶子数量即可。

```c
#include<bits/stdc++.h>
using namespace std;
#define go(i,a,b) for(int i=(a);i<=(b);++(i))
#define com(i,a,b) for(int i=(a);i>=(b);--(i))
#define mem(a,b) memset((a),(b),sizeof(a))
#define inf 0x3f3f3f3f
#define fin freopen("input.txt","r",stdin)
#define fout freopen("output.txt","w",stdout)
#define w first
#define t second
typedef long long ll;
const int maxn=5010,maxm=20010;
int n,m;
int head[maxn],dfn[maxn],low[maxn],c[maxn],cnt=0,dcc=0,du[maxn];
bool bridge[maxm];
struct node{
    int nxt,u,v;
}e[maxm];
void add(int u,int v){
    e[cnt]=(node){head[u],u,v};
    head[u]=cnt++;
}

void tarjan(int u,int fedge){
    dfn[u]=low[u]=++dcc;
    for(int i=head[u];i+1;i=e[i].nxt){
        int v=e[i].v;
        if(!dfn[v]){
            tarjan(v,i);
            low[u]=min(low[u],low[v]);
            if(low[v]>dfn[u]){
                bridge[i]=bridge[i^1]=1;
            }
        }
        else{
            if((i^1)!=fedge) low[u]=min(low[u],dfn[v]);//易错,要注意优先级问题
			//当fa与u之间有多条边时，（x，fa）一定不是桥
			//所以如果处理重边时，需要标记边，否则只需标记父节点 
        }
    }
}

void getdcc(int u){
    c[u]=dcc;
    for(int i=head[u];i+1;i=e[i].nxt){
        int v=e[i].v;
        if(c[v]||bridge[i]) continue;
        getdcc(v);
    }
}

void getans(){
    for(int i=0;i<cnt;i++){
        int u=e[i].u,v=e[i].v;
        if(c[u]==c[v]) continue;
        du[c[u]]++;
    }
    int ans=0;
    go(i,1,dcc){
        if(du[i]==1) ans++;
    }
    printf("%d",(ans+1)>>1);
}

int main()
{
    //fin;
    mem(head,-1);
    scanf("%d%d",&n,&m);
    int x,y;
    go(i,1,m){
        scanf("%d%d",&x,&y);
        add(x,y),add(y,x);
    }
    go(i,1,n){
        if(!dfn[i]) tarjan(i,-1);
    }
    dcc=0;
    go(i,1,n){
        if(!c[i]) ++dcc,getdcc(i);
    }
    getans();
    return 0;
}
```


---

## 作者：Long·J·William (赞：3)

## 思路：

Tarjan缩点，然后ans=（新图中度为1的节点数+1）/2；

新图中通向度为1的节点的边即为桥，切断则图不连通；

所以要使每个点的度都大于1；

连接两个度为1的节点可以同时解决它们；

如果有剩余的点就特供给它一条边；


## 代码实现：

```cpp
#include<cstdio>
const int maxn=5e3+10;
const int maxm=2e4+10;
inline int min_(int x,int y){return x<y?x:y;}
int f,r,ans;
int a,b;
int e[maxm][2];
int h[maxn],hs=1,et[maxm],en[maxm];
void add(int u,int v){
    ++hs,et[hs]=v,en[hs]=h[u],h[u]=hs;
    ++hs,et[hs]=u,en[hs]=h[v],h[v]=hs;
}
int q[maxn],top;
int dfn[maxn],dfs,low[maxn];
int d[maxn],t[maxn],ts;
bool v[maxm];
void tarjan(int k){
    dfn[k]=low[k]=++dfs;
    q[++top]=k;
    for(int i=h[k];i;i=en[i])
    if(!v[i]){
        v[i]=v[i^1]=1;
        if(dfn[et[i]]) low[k]=min_(low[k],dfn[et[i]]);
        else tarjan(et[i]),low[k]=min_(low[k],low[et[i]]);
    }
    if(!t[k]){
        ++ts;
        while(low[k]<=dfn[q[top]]) t[q[top--]]=ts;
    }
}
int main(){
    freopen("rpaths.in","r",stdin);
    freopen("rpaths.out","w",stdout);
    scanf("%d%d",&f,&r);
    for(int i=1;i<=r;i++){
        scanf("%d%d",&a,&b);
        e[i][0]=a,e[i][1]=b;
        add(a,b);
    }
    for(int i=1;i<=f;i++) if(!dfn[i]) tarjan(i);
    for(int i=1;i<=r;i++) if(t[e[i][0]]!=t[e[i][1]]) ++d[t[e[i][0]]],++d[t[e[i][1]]];
    for(int i=1;i<=ts;i++) if(d[i]==1) ans++;
    printf("%d\n",ans+1>>1);
    return 0;
}
```

---

## 作者：GoldenPotato137 (赞：2)

[戳我获得更好的阅读体验qwq](https://www.goldenpotato.cn/%E5%9B%BE%E8%AE%BA/usaco06jan%E5%86%97%E4%BD%99%E8%B7%AF%E5%BE%84redundant-paths/)

---
# Solution
首先，我们可以发现题目要求每一个点到其他所有点的路径不只有一条，**这本质上就是要我们把这个图所有的桥都消除掉。**  

要消除掉桥，首先必须要把边双先缩起来。缩边双很简单：**和求强连通分量一模一样，唯一要注意的是我们要多记录一个$fa$，防止我们求$low$的时候直接把$fa$算进来。**  
求完边双之后，我们会发现原图变成一个树的形式。想象一下：我们要把这个树上所有的单边去掉，我们只需要把叶子节点两两连起来即可。**（注意，这里的叶子节点是广义的（即根也有可能是叶子节点））**  
还有一个小细节：对于直接就是一个环的情况，我们要特判一下，直接输出0即可。

时间复杂度$O(n)$  
就酱，这题就被我们切掉啦︿(￣︶￣)︿

---
# Code
```cpp
//Luogu P2860 [USACO06JAN]冗余路径Redundant Paths
//Apr,8th,2019
//边双
#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
long long read()
{
	long long x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-'0';c=getchar();}
	return x*f;
}
const int N=5000+100;
vector <int> e[N],e2[N];
int n,m;
int dfn[N],low[N],dfn_to,InStack[N],mstack[N],top,belong[N],cnt;
bool vis[N];
void Tarjan(int now,int father)
{
	vis[now]=InStack[now]=true;
	dfn[now]=low[now]=++dfn_to;
	mstack[++top]=now;
	for(int i=0;i<int(e[now].size());i++)
		if(vis[e[now][i]]==false)
		{
			Tarjan(e[now][i],now);
			low[now]=min(low[now],low[e[now][i]]);
		}
		else if(e[now][i]!=father and InStack[e[now][i]]==true)
			low[now]=min(low[now],dfn[e[now][i]]);
	if(low[now]==dfn[now])
	{
		cnt++;
		while(mstack[top+1]!=now)
			InStack[mstack[top]]=false,
			belong[mstack[top--]]=cnt;
	}
}
int GetAns(int now,int father)
{
	int ans=0;
	for(int i=0;i<int(e2[now].size());i++)
		if(e2[now][i]!=father)
			ans+=GetAns(e2[now][i],now);
	return max(1,ans);
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		e[i].reserve(4);
	for(int i=1;i<=m;i++)
	{
		int s=read(),t=read();
		e[s].push_back(t);
		e[t].push_back(s);
	}
	
	Tarjan(1,0);
	
	for(int i=1;i<=n;i++)
		for(int j=0;j<int(e[i].size());j++)
			if(belong[i]!=belong[e[i][j]])
				e2[belong[i]].push_back(belong[e[i][j]]);
	int ans=GetAns(belong[1],belong[1])+(e2[belong[1]].size()==1);
	if(cnt==1)//特判只有一个环
		ans=0;
	printf("%d",ans/2+ans%2);
	return 0;
}

```






---

## 作者：珈乐唯毒 (赞：2)

# P2860题解
题目理解：每个点都有两条不重合的路径可以到达，也就是说我们需要把原图通过加边变成一个边双连通分量。

### 那么怎么做呢？

1. 以样例为例子，我们先求出原图的双连通分量，然后缩点。
1. 为了使缩点后的图边双连通，我们需要把度数为1的点，通过加边增加度数。
1. 将每两个缩了之后的度数为一的点配对，也就是输出度数为一的点的个数加一除以二

### 那么如何求边双联通分量？

直接用tarjan把图中所有的桥删掉就可以了
#### 利用tarjan删桥的代码
```

void tarjan(int u,int last){
	low[u]=dfn[u]=++tot;
	for(int i=head[u];i;i=edge[i].next){
		if(!dfn[edge[i].to]){
			tarjan(edge[i].to,i);
			if(low[edge[i].to]>dfn[u]){
				bridge[i]=bridge[i^1]=1;//标记桥
			}
			else low[u]=min(low[u],low[edge[i].to]);
		}
		else
			if(i!=last&&(i^1)!=last)low[u]=min(low[u],dfn[edge[i].to]);
	}
}
```
友情提示，因为要使用异或符号判断是否重边，所以在用前向星存边时应从2号开始存

### 那么如何缩点？
1. 从一号节点开始，如果当前节点没有被使用过，就用它进行广搜。扩展点的条件为用于扩展的边不为桥且点没有到过。
1. 如果搜到的点被到过，且边为桥，说明此点与正在扩展的点不在一个边双联通分量里面，两个分量的度都要++

#### 缩点代码
```
	for(int i=1;i<=n;i++){
		if(vis[i])continue;
		vis[i]=1;
		sc++;
		q.push(i);
		while(!q.empty()){
			int u=q.front();
			co[u]=sc;
			q.pop();
			for(int j=head[u];j;j=edge[j].next){
				int v=edge[j].to;
				if(!vis[v]&&!bridge[j]){
					q.push(v);
					vis[v]=1;
				}
				if(vis[v]&&bridge[j]){
					du[co[u]]++;
					du[co[v]]++;
				}
			}
		}
	}
```

然后就可以AC了
#### 完整代码
```
#include<bits/stdc++.h>
using namespace std;
const int N=1000005;
int en=1,n,m,low[N],dfn[N],x,y,tot,ans,co[N];
bool bridge[N],vis[N];
struct Edge{
	int next,to;
}edge[N];
int head[N],sc,du[N];
void add(int a,int b){
	edge[en+1].next=head[a];
	head[a]=++en;
	edge[en].to=b;
	return;
}
void tarjan(int u,int last){
	low[u]=dfn[u]=++tot;
	for(int i=head[u];i;i=edge[i].next){
		if(!dfn[edge[i].to]){
			tarjan(edge[i].to,i);
			if(low[edge[i].to]>dfn[u]){
				bridge[i]=bridge[i^1]=1;
			}
			else low[u]=min(low[u],low[edge[i].to]);
		}
		else
			if(i!=last&&(i^1)!=last)low[u]=min(low[u],dfn[edge[i].to]);
	}
}
queue<int> q;
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>x>>y;
		add(x,y);
		add(y,x);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]){
			tarjan(i,0);
		}
	}
	for(int i=1;i<=n;i++){
		if(vis[i])continue;
		vis[i]=1;
		sc++;
		q.push(i);
		while(!q.empty()){
			int u=q.front();
			co[u]=sc;
			q.pop();
			for(int j=head[u];j;j=edge[j].next){
				int v=edge[j].to;
				if(!vis[v]&&!bridge[j]){
					q.push(v);
					vis[v]=1;
				}
				if(vis[v]&&bridge[j]){
					du[co[u]]++;
					du[co[v]]++;
				}
			}
		}
	}
	for(int i=1;i<=sc;i++)
		if(du[i]==1)ans++;
	cout<<(ans+1)/2;
	return 0;
}
```


---

## 作者：abandentsky (赞：1)

题意：题目的意思应该很清楚边不重复的路径。这不就是边-双联通分量嘛。
先来复习（预习）几个概念：
强连通：对于有向图G中两个点a和b，如果存在一条路径a->b，那么我们成a和b强连通。

------------

强连通分量：对于一个有向图的极大子图G',对于G'中的任意两个点a,b。如果a和b强连通，b和a强连通。那么这个极大子图就是原图的一个强连通分量。这里面要简单说就是：任意两个点要相互到达，不能说从a能到b，但是从b到不了a。
这就不是强连通分量了。

------------

双联通（点双联通）：一般没有特别注释的双联通都是点双联通。在一个图中对于任意的a和b如果a到b有至少两条路径，并且路径上的点没有一个重复（相同），我们称为点双联通，或者说对于一个图，如果这个图没有割点，那么这个图就是双联通（点双联通）。

------------

边双联通：边双联通指在一个图中，如果a到b存在至少两条路径，并且这两条路径上没有一条是重合的（一样的）。那么就是边双联通分量，或者说这个图没有割边，他就是边双联通分量。

------------
思路：先找出桥，去掉桥以后，各个连通块就是一个边双联通分量。所以我们使用dfs先找到桥，标记出来。再进行第二遍dfs，这一边dfs我们找连通块。最后问需要多少条边才能使得所有点边双联通，我们将度为1的点都改成2，就好了。所以统计度为1的点，然后加上1.最后除以2就是结果了。
（这部分下面有好几个大佬画图解释了，我就是明确一下几个概念，同时给出一下刘汝佳版的边双联通求法。代码写的优点垃圾，不过应该能看懂）。

------------

下面给出刘汝佳版的AC代码：（给出的测试样例第9个有重边，所以在使用前需要判重，去掉重边）


------------
给出一组有重边的测试数据，希望大家不要调到重边的坑里去。
```c
16 22
1 3
7 1
5 1
12 7
6 3
4 7
8 3
10 7
14 6
11 5
9 7
15 4
2 6
13 12
8 2
2 11
6 1
4 11
1 14
3 10
13 16
13 16
输出结果：2
不判重结果：1
```


```c
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#define MAXN 100100
#define maxnode 2000005
#define sigma_size 26
#define md 12345678
using namespace std;
typedef long long LL;

struct Edge
{
    int from,to;
    Edge(int from=0,int to=0):from(from),to(to){};
};
bool mp[5005][5005];
vector<Edge> edges;
int iscut[MAXN],bccno[MAXN],pre[MAXN];
int dfs_clock,bcc_cnt;
vector<int> bccn[MAXN],G[MAXN];
stack<int> S;
bool vis[MAXN];
int n,m;

int dfs(int u,int fa)                                                              //第一遍找到桥
{
    int lowu=pre[u]=++dfs_clock;
    for(int i=0;i<G[u].size();i++)
    {
        Edge &e=edges[G[u][i]];
        int v=e.to;
        if(!pre[v])                                                                  //用自己的后驱来跟新自己
        {
            int lowv=dfs(v,u);
            lowu=min(lowu,lowv);
            if(lowv>pre[u])
            {
                int pp=G[u][i];
                vis[pp]=true;                                                      //标记出这一条边就是桥
                vis[pp^1]=true;                                                  //由于是无向图，所以就是连续的两个都标记
            }
        }
        else if(pre[v]<pre[u]&&v!=fa)                                //用反向边更新自己
        {
            lowu=min(lowu,pre[v]);
        }
    }
    return lowu;
}

int DFS(int u,int fa)                                                          //现在没有了桥，所以我们直接遍历每一个连通块来找到边双联通
{
    int lowu=pre[u]=++dfs_clock;
    for(int i=0;i<G[u].size();i++)
    {
        if(vis[G[u][i]]||vis[G[u][i]^1])                                                                 //不允许走桥，去掉桥以后剩下的都是连通块
            continue;
        Edge &e=edges[G[u][i]];
        int v=e.to;
        if(!pre[v])                                                                                                   //没访问这个节点用哪个自己的后驱节点更新
        {
            S.push(G[u][i]);
            int lowv=DFS(v,u);
            lowu=min(lowu,lowv);
        }
        else if(pre[v]<pre[u]&&v!=fa)                                 //用反向边跟新自己
        {
            S.push(G[u][i]);
            lowu=min(lowu,pre[v]);
        }
    }
    return lowu;
}

void AddEdge(int from,int to)
{
    edges.push_back({from,to});
    edges.push_back({to,from});
    int mm=edges.size();
    G[from].push_back(mm-2);
    G[to].push_back(mm-1);
}

void Find_Bcc(int n)
{
    dfs_clock=bcc_cnt=0;
    memset(pre,0,sizeof(pre));
    memset(vis,0,sizeof(vis));
    memset(bccno,0,sizeof(bccno));
    for(int i=1;i<=n;i++)
    {
        if(!pre[i])
            dfs(i,-1);
    }
    memset(pre,0,sizeof(pre));
    memset(bccno,0,sizeof(bccno));
    dfs_clock=0;
    bcc_cnt=n+1;
    for(int i=1;i<=n;i++)
    {
        if(!pre[i])
        {
            bcc_cnt++;
            DFS(i,-1);
        }
        while(!S.empty())
        {
            int x=S.top();
            S.pop();
            Edge &e=edges[x];
            if(bccno[e.from]!=bcc_cnt)
                bccno[e.from]=bcc_cnt,bccn[bcc_cnt].push_back(e.from);
            if(bccno[e.to]!=bcc_cnt)
                bccno[e.to]=bcc_cnt,bccn[bcc_cnt].push_back(e.to);
        }
    }
    int len=edges.size();
    int num[MAXN];
    int ans=0;
    for(int i=0;i<len;i++)
    {
        Edge &e=edges[i];
        if(vis[i])
        {
            int xx=bccno[e.from];
            int yy=bccno[e.to];
            if(xx)
                num[xx]++;
            else
                num[e.from]++;
            if(yy)
                num[yy]++;
            else
                num[e.to]++;
        }
    }
    ans/=2;
    for(int i=1;i<=bcc_cnt+n;i++)
    {
        if(num[i]==2)
            ans++;
    }
    printf("%d\n",(ans+1)/2);
}

int main()
{
    scanf("%d %d",&n,&m);
    int u,v;
    for(int i=1;i<=m;i++)
    {
        scanf("%d %d",&u,&v);
        if(mp[u][v])
            continue;
        mp[u][v]=mp[v][u]=true;
        AddEdge(u,v);
    }
    Find_Bcc(n);
    return 0;
}

```





---

## 作者：小菜鸟 (赞：1)

一句话题意：给定一个无向连通图，求至少加几条边能使其变为一个边双连通分量。

思路：找边双，缩点，求叶节点个数，加一，除以二。

然而找边双可能会萎。

求边双通常有两种方法：记住前驱节点，或是记住前驱边。

然而由于此题有重边，记点会WA on #9...

但我们还是有办法。

~~本着老死不重构代码的思想，~~ 我们设法使记点和记边变得等效。

于是我们可以开一个$vis$数组，判断此条边是否被加过。

如果没有就直接加。如果加过了...

新开一个节点，把这个节点接到边的起点与终点之间。

于是对于每一条边，都有了一个唯一的前驱节点...

于是重边什么的就不用在意了。

代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>

const int N=300005,M=600005;

int n,m,head[N],dis[N],from[N];
int cnt,cir_cnt,dfn[N],low[N],cir[N];
int _head[N],_dis[N];

struct Edge
{
    int from,next,to;
};
Edge E[M],_E[M];

int new_node=300005;//为了防止影响其他节点，新节点从后往前依次申请

bool vis[5005][5005];

void add(int u,int v)
{
    static int tot=0;
    E[++tot].next=head[u];
    E[tot].to=v;
    head[u]=tot;
}
void _add(int u,int v)
{
    static int tot=0;
    _E[++tot].next=_head[u];
    _E[tot].from=u;
    _E[tot].to=v;
    _head[u]=tot;
}

void tarjan(int u,int fa)
{
    static std::stack<int> s;
    low[u]=dfn[u]=++cnt;
    s.push(u);
    for(int i=head[u];i;i=E[i].next)
    {
    	int v=E[i].to;
        if(v==fa)continue;
        if(!dfn[v])
        {
            tarjan(v,u);
            low[u]=std::min(low[u],low[v]);
        }
        else
        {
            if(cir[v]==0)low[u]=std::min(low[u],dfn[v]);
        }
    }
    if(low[u]!=dfn[u])return;
    cir_cnt++;
    while(1)
    {
        int x=s.top();
        s.pop();
        cir[x]=cir_cnt;
        if (x==u)break;
    }
}

int deg[N];

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;++i)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        if(vis[u][v])
        {
            --new_node;//关键操作
            add(u,new_node);
            add(new_node,u);
            add(v,new_node);
            add(new_node,v);
        }
        else
        {
            vis[u][v]=1;
            add(u,v);
            add(v,u);
        }
    }
    tarjan(1,0);
    if(cir_cnt==1)
    {
        puts("0");
        return 0;
    }
    for(int u=1;u<=n;++u)
    {
        for(int i=head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(cir[u]!=cir[v])
            {
                _add(cir[u],cir[v]);
                ++deg[cir[u]];
                ++deg[cir[v]];
            }
        }
    }
    int res=0;
    for(int i=1;i<=n;++i)if(deg[i]==2)++res;
    printf("%d",(res+1)/2);
}
```





---

