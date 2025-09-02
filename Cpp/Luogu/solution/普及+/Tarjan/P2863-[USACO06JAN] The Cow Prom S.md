# [USACO06JAN] The Cow Prom S

## 题目描述

有一个 $n$ 个点，$m$ 条边的有向图，请求出这个图点数大于 $1$ 的强连通分量个数。

## 说明/提示

#### 数据规模与约定

对于全部的测试点，保证 $2\le n \le 10^4$，$2\le m\le 5\times 10^4$，$1 \leq a, b \leq n$。

## 样例 #1

### 输入

```
5 4
2 4
3 5
1 2
4 1```

### 输出

```
1```

# 题解

## 作者：冈崎梦美 (赞：111)

## 1.1 简述强联通分量与Tarjan
在有向图G中，如果两个顶点间至少存在一条路径，称两个顶点强连通。如果有向图G的每两个顶点都强连通，称G是一个强连通图。非强连通图有向图的极大强连通子图，称为强连通分量。

~~说白了就是如果一个有向图的子图里每个点可以两两互达，那么这个子图是一个强联通分量~~

Tarjan算法就是基于DFS求强联通分量的算法。


## 2.1 Tarjan思想

#### 2.1.1 Tarjan维护的变量
在Tarjan算法中我们维护如下的变量：
```
vector<int> G[maxn];//图本身（邻接表）
stack<int>s;//栈，存放答案
int vis[maxn];//标记点是否在栈中
int dfn[maxn];//节点i的时间戳
int low[maxn];//节点i能够回溯到的最早位于栈中的节点。（子树的根，可以理解为并查集的“祖先”一类的东西）
int color[maxn];//每个点属于第几个强联通分量
int colornum;//强连通分量的个数
int cnt;//当前时间
```

#### 2.2.2 Tarjan算法运行过程

1. 按照深度优先遍历的方式遍历这张图。
2. 遍历当前节点所出的所有边。在遍历过程中：

    ( 1 ) 如果当前边的终点还没有访问过，访问。

	回溯回来之后比较当前节点的low值和终点的low值。将较小的变为当前节点的low值。（因为遍历到终点时有可能触发了2）

	( 2 )  如果已经访问过，那我们一定走到了一个之前已经走过的点（终点的时间戳一定比当前的小）

	则比较当前节点的low值和终点的dfn值。将较小的变为当前节点的low值
3. 在回溯过程中，对于任意节点u用其出边的终点v的low值来更新节点u的low值。因为节点v能够回溯到的已经在栈中的节点，节点u也一定能够回溯到。因为存在从u到v的直接路径，所以v能够到的节点u也一定能够到。

4. 当一个节点的dfn值和low值相等时，这个节点是一个强联通分量的“根”。压栈，输出。

~~我知道这让你听得很迷糊，~~先来一段伪代码看看吧。
```
void tarjan(int u)//当前节点
{
	dfn[u]=low[u]=++cnt;//该节点本身是一个强联通分量
    节点入栈;
    vis[u]=true;//当前节点已入栈
    for(遍历该节点所有出边)
    {
    	int v=当前边的终点;
        if (!dfn[v])
        {
        	tarjan(v);//深度优先遍历
            low[u]=min(low[u],low[v]);
        }
        else low[u]=min(dfn[v],low[u]);
    }
    if (low[u]==dfn[u])
    {
    	while(栈顶!=v)
        {
            染色;
        	出栈;
        }
    }
    染色;
    出栈;
}
```
手模一组数据就不模啦，网上到处都是。

## 3.1 完整code
这里以洛谷P2863 `[USACO06JAN]牛的舞会The Cow Prom`为例。题意为：给定一个图，要求图中节点数大于一的强联通分量个数。
对于这道~~模板~~题，我们应当做到一遍A掉。
```
#include<bits/stdc++.h>
#define maxn 10001
using namespace std;
vector<int>G[maxn];
stack<int>s;
int n,m;
int dfn[maxn],used[maxn],vis[maxn],low[maxn],color[maxn],num[maxn],colornum=0,cnt=0,ans=0;
void paint(int x)
{
    s.pop();
    color[x]=colornum;
    num[colornum]++;
    vis[x]=false;
}
void tarjan(int x)
{
    dfn[x]=low[x]=++cnt;
    s.push(x);
    vis[x]=used[x]=true;
    for(int i=0;i<G[x].size();i++)
    {
        int q=G[x][i];
        if (!dfn[q])
        {
            tarjan(q);
            low[x]=min(low[x],low[q]);
        }
        else if (vis[q]) low[x]=min(low[x],dfn[q]);
    }
    if (low[x]==dfn[x])
    {
        colornum++;
        while(s.top()!=x)
        {
            int t=s.top();
            paint(t);
        }
        paint(x);
    }
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
    }
    for(int i=1;i<=n;i++)
    {
        if (!used[i]) tarjan(i);
    }
    for(int i=1;i<=colornum;i++)
    {
        if (num[i]>1) ans++;
    }
    cout<<ans;
    return 0;
}
```

### 3.2 我接下来学习什么算法？
缩点。[ P2341 [HAOI2006]受欢迎的牛](https://www.luogu.org/problemnew/show/P2341)可以作为一道模板题。

敬请期待。

---

## 作者：Frozen_Heart (赞：22)

//这道题思路还是很简单的   一个裸的tarjan强连通分量    在这里还是着重解释一下tarjan的代码












```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m;
int cnt;//记录强联通分量的个数
int visitnum;//遍历的步数
int dfn[100010];//记录元素第一次被访问的步数
int low[100010];//包含i的强联通分量最早被访问的步数
int num[100010];//记录强联通分量里的点的个数
int belong[100010];//i从属的强联通分量的序号
int top;//栈中元素的个数
int stack[100010];//手打栈
int instack[100010];//判断元素是否在栈中
int head[100010];
struct node{
int to,next;
}edge[100010];//链式前向星存边
int read()//读入优化
{
    int x=0,w=1;char ch=getchar();
    while(ch>'9'||ch<'0') {if(ch=='-')w=-1;ch=getchar();}
    while(ch<='9'&&ch>='0') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    return x*w;
}
void tarjan(int);
int main()
{
    int ans=0;
    int p,q;
    n=read();m=read();
    for(int i=1;i<=m;i++)
    {
        p=read();q=read();
        edge[i].to=q;
        edge[i].next=head[p];
        head[p]=i;
    }
    for(int i=1;i<=n;i++)
    {
        if(!dfn[i])//i没被访问过了
        {
            tarjan(i);
        }
    }
    for(int i=1;i<=cnt;i++)
    {
        if(num[i]>1)
        ans++;
    }
    printf("%d",ans);
}
void tarjan(int u)
{
    int v;
    visitnum++;
    dfn[u]=low[u]=visitnum;
    stack[++top]=u;//入栈
    instack[u]=1;//入栈
    for(int i=head[u];i;i=edge[i].next)
    {
        v=edge[i].to;
        if(!dfn[v])//还没被访问过
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);//判断u是否为v的子节点
        }
        else if(instack[v])
        {
            low[u]=min(low[u],dfn[v]);
                       //其实这里的dfn[v]也能换成low[v] 但最好写dfn
        }
    }
    if(dfn[u]==low[u])//u为强联通分量的根
    {
        cnt++;
        do//退栈
        {
            num[cnt]++;
            v=stack[top--];
            belong[v]=cnt;
            instack[v]=0;
        }while(u!=v);
    }
}
```

---

## 作者：Jeblqr (赞：14)


# 广告

## [我的blog & 更好的阅读体验](https://www.jeb.website/)



------------



### Have you 听过 Tarjan？

> 此算法以一个有向图作为输入，并按照所在的强连通分量给出其顶点集的一个划分。图中的每个节点只在一个强连通分量中出现，即使是在有些节点单独构成一个强连通分量的情况下（比如图中出现了树形结构或孤立节点）。
算法的基本思想如下：任选一节点开始进行深度优先搜索（若深度优先搜索结束后仍有未访问的节点，则再从中任选一点再次进行）。搜索进程中已访问的节点不再访问。搜索树的若干子树构成了图的强连通分量。
节点按照被访问的顺序存入堆栈中。从搜索树的子树返回至一个节点时，检查该节点是否是某一强连通分量的根节点（见下）并将其从堆栈中删除。如果某节点是强连通分量的根，则在它之前出堆栈且还不属于其他强连通分量的节点构成了该节点所在的强连通分量。
(来自[Wikipedia](https://zh.wikipedia.org/wiki/Tarjan%E7%AE%97%E6%B3%9))


~~看不懂对不对？~~

~~我也是~~

那我们一个一个来解决。

## 什么是强连通分量？

> 强连通分量（英语：Strongly connected component）是图论中的概念。图论中，强连通图指每一个顶点皆可以经由该图上的边抵达其他的每一个点的有向图。意即对于此图上每一个点对$(Va,Vb)$ ，皆存在路径 $Va→Vb$ 以及 $Vb→Va$ 。强连通分量则是指一张有向图$G$的极大强连通子图$G'$。如果将每一个强连通分量缩成一个点，则原图$G$将会变成一张有向无环图。一张图被称为有向无环图当且仅当此图不具有点集合数量大于一的强连通分量，因为有向环即是一个强连通分量，而且任何的强连通分量皆具有至少一个有向环。
(依然来自[Wikipedia](https://zh.wikipedia.org/wiki/%E5%BC%BA%E8%BF%9E%E9%80%9A%E5%88%86%E9%87%8F))

~~依旧看不懂对不对？~~

那我们给个简明的定义：

>  $$G'=\{V|V \in G,\forall V_a→V_b\}$$ , $G'$ 即为强连通分量

~~还是看不懂？~~

上图

![](https://www.jeb.website/img/tarjan1.png)

在下面der子图中，每一个点都可以经过某条或某几条边到达其他任意的一个点，所以这个子图是一个强连通分量。而在下面那个图中，不是所有的点都可以去到其他所有的点（实际上，一个都不能）。所以，这个子图就不是一个强连通分量。

~~又㕛叒叕看不懂？？？~~

###### ~~我说了，还解释了，还看不懂，我还有什么好说的？~~


## 实现

### 思路

我们随便找个点向下dfs，如果若干次后又可以回到它，那显而易见的，从该点回到该点的所有的点所构成的图，即为一个强连通分量。

可是我们dfs的时候，只能找到路径，那我们怎么标记它们是一个强连通分量呢？

我们引入**追溯值**。

**追溯值**表示在dfs中，它能访问的所有点中，**dfs序**最小的那个编号。容易得出，在一个强连通分量中，追溯值都是一样的，所以我们要把追溯值一样的点都标记一下。那我们怎么做到标记呢？我们就要用一个栈。在进入dfs的时候把它压入栈里，当每个可到达的点的追溯值都大于它时，说明它就是一个强连通分量（它自己本身也是一个强连通分量）中的dfs序最小的那个点（也可以理解为最浅的那个点），于是把压在它上面的栈的点都打上标记就好了。

### 伪代码

```
algorithm tarjan is
input: 圖 G = (V, E)
output: 以所在的強連通分量劃分的頂點集

index := 0
S := empty // 置堆疊為空
for each v in V do
 if (v.index is undefined)
   strongconnect(v)
 end if

function strongconnect(v)
 // 將未使用的最小index值作為節點v的index
 v.index := index
 v.lowlink := index
 index := index + 1
 S.push(v)

 // 考慮v的後繼節點
 for each (v, w) in E do
   if (w.index is undefined) then
     // 後繼節點w未訪問，呼叫遞迴
     strongconnect(w)
     v.lowlink := min(v.lowlink, w.lowlink)
   else if (w is in S) then
     // w已在堆疊S中，亦即在當前強連通分量中
     v.lowlink := min(v.lowlink, w.index)
   end if

 // 若v是根則出堆疊，並求得一個強連通分量
 if (v.lowlink = v.index) then
   start a new strongly connected component
   repeat
     w := S.pop()
     add w to current strongly connected component
   until (w = v)
   output the current strongly connected component
 end if
end function

//Wikipedia大法好
```

### C++实现

#### 定义一些东西

```cpp
struct Node
{
	int y,next;
};
Node node[M];//邻接数组
//dfn dfs序，cntcolor 标记总数的统计，low 追溯值，color 标记，colortot 不同标记
int last[N],cntcolor[N],dfn[N],low[N],color[N],tot,colortot,dtot;
bool vis[N];
stack<int> st;
void paint();
void tarjan(int x);
public:
	Tarjan();
	void insert(int x,int y);
	int calcAmount(int n);
```

#### Tarjan代码

```cpp
void Tarjan::tarjan(int x)
{
	dfn[x]=low[x]=++dtot;//记录dfs序；每个点都可视为一个强连通分量，所以low初始化为dfn
	st.push(x);//压入栈中
	vis[x]=true;//标记访问过
	for (int i=last[x];i;i=node[i].next)//遍历每个相连的点
	{
		int y=node[i].y;
		if (!dfn[y])//没有搜索过
		{
			tarjan(y);//向下更新
			low[x]=min(low[x],low[y]);//更新low
		}
		else if (vis[y])//搜索过
		{
			low[x]=min(low[x],low[y]);//直接用
		}
	}
	if (dfn[x]==low[x])//搜索完了
	{
		colortot++;//新加标记
		while (st.top()!=x)
			paint();//对于所有在它上面的点标记
		paint();//标记它自己
	}
}
```

**要注意的是，可能会有几个孤立的子图，因此要遍历所有的点，把前面没有搜过的点都丢进去dfs搜一下**

那放完整代码吧。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<stack>
#define N 1000001
#define M 1000001
using namespace std;

//--------------------------------------------
class Tarjan
{
	struct Node
	{
		int y,next;
	};
	Node node[M];
	int last[N],cntcolor[N],dfn[N],low[N],color[N],tot,colortot,dtot;
	bool vis[N];
	stack<int> st;
	void paint();
	void tarjan(int x);
	public:
		Tarjan();
		void insert(int x,int y);
		int calcAmount(int n);
		
};

void Tarjan::paint()
{
	int x=st.top();
	st.pop();
	vis[x]=false;
	color[x]=colortot;
	cntcolor[colortot]++;
}

void Tarjan::tarjan(int x)
{
	dfn[x]=low[x]=++dtot;
	st.push(x);
	vis[x]=true;
	for (int i=last[x];i;i=node[i].next)
	{
		int y=node[i].y;
		if (!dfn[y])
		{
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if (vis[y])
		{
			low[x]=min(low[x],low[y]);
		}
	}
	if (dfn[x]==low[x])
	{
		colortot++;
		while (st.top()!=x)
			paint();
		paint();
	}
}

Tarjan::Tarjan():tot(0),colortot(0),dtot(0)
{
	memset(node,0,sizeof node);
	memset(last,0,sizeof last);
	memset(cntcolor,0,sizeof cntcolor);
	memset(dfn,0,sizeof dfn);
	memset(low,0,sizeof low);
	memset(color,0,sizeof color);
} 

void Tarjan::insert(int x,int y)
{
	node[++tot]={y,last[x]};
	last[x]=tot;
}

int Tarjan::calcAmount(int n)
{
	for (int i=1;i<=n;i++)
	{
		if (!dfn[i])//dfn为0，说明没有访问过
			tarjan(i);
	}
	int ans=0;
	for (int i=1;i<=colortot;i++)
		if (cntcolor[i]>1)
			ans++;
	return ans;
}
//--------------------------------------------

Tarjan tj;
int main()
{
	int n,m;
	cin>>n>>m;
	for (int i=1,x,y;i<=m;i++)
		cin>>x>>y,tj.insert(x,y);
	cout<<tj.calcAmount(n); 
	return 0;
}
```


## 板子

[洛谷P2863](https://www.luogu.org/fe/problem/P2863)


---

## 作者：Marginalin (赞：10)

裸的强连通图，用Tarjan就好
解释都在源程序里面啦
```cpp
//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cstdio>
#include <stack>
using namespace std;

const int MAXN = 100000 + 10;

stack<int> S;
vector<int> G[MAXN]; // 存图 

//n：点数 m：边数 deep：深度 sum：强连通块个数  Ans：答案个数 
int n, m, deep, sum, Ans;  
// dfn low 都知道，， col：第 x个点染的什么颜色 
int dfn[MAXN], low[MAXN], col[MAXN]; 
int cnt[MAXN]; // 颜色为 x的个数 
bool vis[MAXN]; // 判断有没有访问过 

void Tarjan(int now) {
	vis[now] = true; // 标记为访问过
	S.push(now); // 将该点压入栈中 
	dfn[now] = low[now] = ++deep; //记录时间戳
	for(int i=0; i<G[now].size(); i++) { // 搜索与该点联通的点 
		int To = G[now][i]; // 下一个将要访问的点 
		if(!dfn[To]) { // 如果没有被搜过 
			Tarjan(To); //开始搜索 
			low[now] = min(low[now], low[To]); // 回溯更新 low值 
		}
		else if(vis[To]) low[now] = min(low[now], low[To]); // 搜过了 直接更新 low 
	}
	if(dfn[now] == low[now]) { // 找到一个强连通块的根 
		col[now] = ++sum;  // 染色 
		vis[now] = false;  
		while(true) { //将搜索栈中该点以上的点弹出  他们都是在这个强联通块中 
			int x = S.top(); S.pop();
			col[x] = sum; // 该强联通块染成第 sum种颜色 
			vis[x] = false;
			if(now == x) break; // 将根弹出后 结束循环 
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i=1; i<=m; i++) { // 读入有向图 
		int x, y;
		scanf("%d%d", &x, &y);
		G[x].push_back(y);
	}
	for(int i=1; i<=n; i++) // 遍历 n个点 
		if(!dfn[i]) // 如果这个点没有被搜过 开始Tarjan 
			Tarjan(i);
	for(int i=1; i<=n; i++) // 记录第 i种颜色的点有几个 
		cnt[col[i]] ++;
	for(int i=1; i<=sum; i++) // 如果是第 i种颜色的点大于1 则就是一个强联通块
		if(cnt[i] > 1)
			Ans ++;
	printf("%d\n", Ans); // 输出答案 
	return 0;
}
```

---

## 作者：Misaka19280 (赞：9)

题解里满地都是tarjan啊

为了表示对写tarjan的各位选手的敬佩，我在此介绍一下kosaraju算法吧

以下内容来自《信息学奥赛一本通》：

基于两次DFS的有向图强连通子图算法。

第一步，对原有向图G进行DFS，记录结点访问完的顺序d[i],d[i]表示第i个访问完的结点是d[i];

第二步，选择具有最晚访问完的顶点，对反向图GT进行DFS，删除能够遍历到的顶点，这些顶点构成一个强连通分量

第三步，如果还有顶点没有删除，继续第二步，否则算法结束

所以每次在做第二次dfs的时候，统计删除点的个数，超过1了就ans++

上代码

```
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn=10001;
const int maxm=50001;

struct edge
{
    int v,next;
}G[maxm*2],G_f[maxm*2];
int head[maxn],head_f[maxn],vis[maxn],d[maxn];
int n,m,top=0,top_f=0,cnt=0,ans=0;

int add(int x,int y)
{
    G[++top].next=head[x];
    head[x]=top;
    G[top].v=y;
}

void add_f(int x,int y)
{
    G_f[++top_f].next=head_f[x];
    head_f[x]=top_f;
    G_f[top_f].v=y;
}

void dfs1(int x)
{
    vis[x]=false;
    for (int i=head[x];i;i=G[i].next)
    {
        int v=G[i].v;
        if (vis[v]) dfs1(v);
    }
    d[++cnt]=x; //统计d数组
}

void dfs2(int x)
{
    vis[x]=false;
	cnt++;
    for (int i=head_f[x];i!=0;i=G_f[i].next)
    {
        int v=G_f[i].v;
        if (vis[v]) dfs2(v);
    }
    return;
}

void kosaraju()
{
    memset(vis,true,sizeof(vis));
    cnt=0;
    for (int i=1;i<=n;i++)
        if (vis[i]) dfs1(i);
    memset(vis,true,sizeof(vis));
    for (int i=n;i>=1;i--)
    {
        int now=d[i];
        if (vis[now])
        {
            cnt=0;
            dfs2(now);
            if (cnt!=1) ans++;
        }
    }
    printf("%d ",ans);
}

int main()
{
    scanf("%d %d",&n,&m);
    memset(head,0,sizeof(head));
    memset(head_f,0,sizeof(head_f));
    for (int i=1;i<=m;i++)
    {
        int a,b;
        scanf("%d %d",&a,&b);
		add(a,b);
		add_f(b,a); //图和反图
    }
    kosaraju();
    return 0;
}
```

---

## 作者：zhaimingshuzms (赞：8)

#突然发现以前自己挺傻的

此题只要维护强连通分量大小就可以了，所以不需要栈。

首先，一次dfs会且只会找出一个强连通分量，而它的大小就是这次dfs最大的pre[x]-low[x]+1，此题判断大于1，即为pre[x]不等于low[x]

于是此题就简单了

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10001,M=50001;
int pre[N],low[N],fi[N],nscc[N],isc[N],ne[M],b[M],clk,n,m,x,y,ans;
bool ri;
void dfs(int x){
    pre[x]=low[x]=++clk;
    for (int j=fi[x],y=b[j]; j; j=ne[j],y=b[j])
    {
        if (!pre[y]) dfs(y);
           if (!isc[y]) low[x]=min(low[x],low[y]);
    }
    if (pre[x]!=low[x]) ri=1;
}
int main(){
    scanf("%d%d",&n,&m);
    while (m){
        scanf("%d%d",&x,&y);
        b[m]=y; ne[m]=fi[x]; fi[x]=m--;
    }
    for (int i=1; i<=n; i++) 
       if (!pre[i]){
             ri=0;
             dfs(i);
             if (ri) ++ans;
        }        
    printf("%d",ans);
}
```

---

## 作者：陈新月 (赞：6)

思路：

其实没有什么思路的啦，只是Tarjan算法的裸题，只要判断强连通分量是否大1就行了，如果大于就答案++，最后输出就行了。

下面为贴代码过程







    


```cpp
#include<cstdio>
#include<algorithm>
#include<stack>
#define N 10009
#define M 50009
using namespace std;
int en,ans,n,m;
int t,cnt,low[N],dfn[N];
bool instack[N];
stack<int> sta;
struct edge{
    int e;
    edge *next;
}*v[N],ed[M];
void add_edge(int s,int e){
    en++;
    ed[en].next = v[s],v[s] = ed+en,v[s]->e = e;
}
void dfs(int now){
    t++;
    low[now] = dfn[now] = t;
    instack[now] = true;
    sta.push(now);
    for(edge *e = v[now];e;e = e->next)
      if(!dfn[e->e]){
              dfs(e->e);
              low[now] = min(low[now],low[e->e]);
      }
      else if(instack[e->e])low[now] = min(low[now],dfn[e->e]);
    if(dfn[now] == low[now]){
        cnt++;
        int siz = 0;
        while(sta.top() != now){
            instack[sta.top()] = false;
            siz++;
            sta.pop();
        }
        instack[now] = false;
        sta.pop();
        siz++;
        if(siz > 1)ans++;
    }
}
void tarjan(){
    for(int a = 1; a<= n; a++)
      if(!dfn[a])dfs(a);
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i = 1; i <= m; i++){
        int x,y;
        scanf("%d%d",&x,&y);
        add_edge(x,y);     //有向图 
    }
    tarjan();
    printf("%d\n",ans);
    return 0;
}

```

---

## 作者：Ervin (赞：6)

### 刚刚才发现用$vector$做$Tarjan$很好用、、
其实这个题目就是一个$Tarjan$求强连通分量的裸题，本~~神犇~~在很早以前就已经写过强连通分量，但是发现这道题目的时候~~早就已经忘得一干二净了~~我靠( ‵o′)凸,$I$服了$U!!$
1. 好了，不开玩笑了，其实用$vector$写$Tarjan$还是比较简单的，不用像各种图论题目一样写个$add$()建图，直接标记一下就可以用，~~像我这种懒得多一句都很难受的人，~~还是很适合我的么。。
2. 其实这个题目跑完$Tarjan$之后判断一下$cnt>1$，成立的话就$ans$++，最后输出$ans$就可以了。
#### 粘一下代码：
```cpp
#include<cstdio>
#include<vector>
#define N 10010
using namespace std;
vector<int>g[N];
int color[N],dfn[N<<1],low[N<<1],stack[N<<1],vis[N],cnt[N],deep,top,n,m,sum,ans;
inline void tarjan(int u)
{
	
	vis[u]=1;				//判断有没有访问过
	stack[++top]=u;          //手动建立一个栈
    dfn[u]=++deep;           //其实这两个才是最重要的，~~楼下大佬已经讲的够清楚了，本神犇就不多讲了~~
	low[u]=deep;
	int sz=g[u].size();
	for(int i=0;i<sz;i++)
	{
		int v=g[u][i];
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else
			if(vis[v])
				low[u]=min(low[u],low[v]);
	}
	if(dfn[u]==low[u])
	{
		color[u]=++sum;
		vis[u]=0;
		while(stack[top]!=u)
		{
			color[stack[top]]=sum;
			vis[stack[top--]]=0;
		}
		top--;
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		g[a].push_back(b);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			tarjan(i);
	for(int i=1;i<=n;i++)
		cnt[color[i]]++;
	for(int i=1;i<=sum;i++)
		if(cnt[i]>1)
			ans++;
	printf("%d",ans);
    return 0;                //~~程序完美的结束，~~AC啦！！
}
```

---

## 作者：ViXpop (赞：5)

### 此题作为一道tarjan模板题，思路还是比较好想

别看原题一大堆英文，翻译过来之后各种乱七八糟的描述

题意却很清晰，就是给我们一个有向图，让我们求节点数大于1的强联通分量的个数

至于什么是强联通分量我就不赘述了，相信各位神仙都懂

既然我们能清晰的了解题意，那么代码的思路也就很明了了

直接就是常规tarjan思路，只不过多了个统计缩点后每个强联通分量的里点的个数

#### 下面就是代码了，看不懂有注释呢

```
#include <bits/stdc++.h>
using namespace std;
inline int read(){
    int res=0,f=1;char ch=' ';
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){res=res*10+ch-'0';ch=getchar();}
    return res*f;
}
const int N=3e5+5;    //其实可以不开这么大，5e4+5即可
int n,m,cnt,cut,to[N],nxt[N],head[N],dfn[N],ins[N],top,low[N],st[N],id,belong[N],ans,vis[N],num[N];
int _min(int a,int b){return a<b?a:b;}
void qxx(int x,int y){
	to[++cnt]=y;
	nxt[cnt]=head[x];
	head[x]=cnt;
}
void tarjan(int x){   //常规tarjan操作
	dfn[x]=low[x]=++id;
	st[++top]=x;
	ins[x]=1;
	for(register int i=head[x];i;i=nxt[i]){
		int k=to[i];
		if(!dfn[k]){  //如果这个点没有遍历过，就继续跑
			tarjan(k);
			low[x]=_min(low[x],low[k]);
		}
		else if(ins[k])low[x]=_min(low[x],dfn[k]);
	}
	if(low[x]==dfn[x]){
		++cut;
		do{
			belong[st[top]]=cut;
			ins[st[top]]=0;
			num[belong[st[top]]]++; 
                        //统计缩点后每个强联通分量的点数
		}while(st[top--]!=x);
	}
}
int main() {
	n=read(),m=read();
	for(register int i=1;i<=m;i++){
		int l=read(),r=read();
		qxx(l,r);
	}
	for(register int i=1;i<=n;i++)if(!dfn[i])tarjan(i);
    			//所有点全部跑一遍
	for(register int i=1;i<=n;i++)
		if(!vis[belong[i]]&&num[belong[i]]>1){
			ans++;
			vis[belong[i]]=1;//统计答案
		}
	printf("%d\n",ans);
    return 0;
}
```
#### 就是这么简单


---

## 作者：w_x_c_q (赞：3)

**Tarjan缩点简单题**

如果不会Tarjan缩点的话，请看一下教程吧；

有几个需要注意的点：

1.数组一定要开得够大，尽量要比给出的数据范围大上一些；

2.题目中给出的绳索（即边）是单向的；存图时要注意

主要思路就是走一遍Tarjan，再去统计一下缩点后的点的size值大于1的个数，即为答案；

代码在这里
```cpp
#include<iostream>
#include<cstdio>
#define cq(i,s,n) for(int i=s;i<=n;i++)
using namespace std;
struct edge{
	int nxt,to;
}edge[400005];

int head[400005],vis[400005];
int n,m,x,y,a,b,num,ans;
int tot,col;
int dfn[400005],low[400005],st[400005],belong[400005];
int size[400005];
int top;

void add(int from,int to){
	edge[++num].nxt=head[from];
	edge[num].to=to;
	head[from]=num;
}

void Tarjan(int u){
	dfn[u]=low[u]=++tot;
	st[++top]=u;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to;
		if(!dfn[v]){
			Tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(!belong[v]){
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(low[u]==dfn[u]){
		belong[u]=++col;
		size[belong[u]]++;
		while(st[top]!=u){
			belong[st[top]]=col;
			size[belong[u]]++;
			top--;
		}
		top--;
	}
}
int main(){
	scanf("%d%d",&n,&m);
	cq(i,1,m){
		scanf("%d%d",&x,&y);
		add(x,y);
//		add(y,x);   注意存单向边
	}
	cq(i,1,n){
		if(!dfn[i])Tarjan(i);
	}
	cq(i,1,col){
		if(size[i]>1)ans++;
	}
	printf("%d",ans);
	return 0;
} 
```

---

## 作者：大头冲锋车丶 (赞：2)


**这题是tarjan求强连通分量的模板题。**
tarjan算法是用来求有向图强连通分量的算法，作用是进行缩点操作，因为有些算法是需要DAG图（有向无环图）才能进行操作的，所以很多图论算法之前都需要进行缩点。

tarjan算法核心需要两个数组：
dfn[i] ：用来存储整张图遍历到 i 节点的时间顺序，从 1 开始计数。
low[i] ：节点 i 能够回溯到的最早位于栈中的节点。

此外还需要一个数组用来模拟栈。
	[详细推荐文章~]

对tarjan算法的理解：
1、对于栈中元素u，那么u上面的节点（对于栈）就是以 **“u为根的强连通”** 的节点，**u节点一定会通过有向图达到这些节点。**

2、对于遍历到新节点（即未被访问过的）时，再次以DFS形式，进行向内深搜，而递归返回时，应该**low[u]=min（low[u],low[v]）**。意义就是，取 u 能够回溯的最早位于栈中的节点，而由于 v 是新节点，所以递归到这时 v 一定已经在栈中。

3、对于遍历到老节点（即已经被访问过的）时，且 v 节点已经在栈中。则应该**low[u]=min(low[u],dfn[v])** 。由于 v 被遍历过，且 v 在栈中，说明图中**还可能会有一个 以 v 节点为强连通分量的根节点**。

 v 在栈中，还说明它肯定比 u 更先遍历到，而此时有 u -> v 这条边，则**说明 u 与 v 是双向可达的**，即说明 **v 回溯时一定可以到 u**，而为了满足 low[]数组的条件，所以直接取**low[u]=min(low[u],dfn[v])** 即可。
 
 4、若 u 点退出了for循环，说明以 u 为起点的边已经遍历完了，若此时仍然有 **low[u]==dfn[u]**，则说明**有一个以 u 为根节点的树**，这个树上的节点的low[]数组值都为low[u]值，则说明这树上的点都相互可达。故这里就有**一个以 u 为根节点的强连通分量的树**。
 
 此题是模板题，只需要排除 节点数为 1 的强连通分量树就可以了。
 代码如下:
 ```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#define MAXN 10008
#define MAXM 50008
using namespace std;
int dfn[MAXN], vis[MAXN], head[MAXN], s[MAXN], low[MAXN];
int N, M, cnt, top, tot, sum;
struct Edge
{
	int to;
	int next;
}edge[MAXM];
inline void add(int u, int v)
{
	edge[++cnt].to = v;
	edge[cnt].next = head[u];
	head[u] = cnt;
	return;
}
inline void init()
{
	sum = cnt = top = tot = 0;
	memset(head, 0, sizeof(head));
	memset(low, 0, sizeof(low));
	memset(vis, 0, sizeof(vis));
	memset(dfn, 0, sizeof(dfn));
	memset(s, 0, sizeof(s));
	return;
}
inline void tarjan(int u)
{
	dfn[u] = low[u] = ++tot;
	vis[u] = 1;
	s[++top] = u;
	for (int i = head[u]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if (vis[v])
			low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		int ans = 0;
		while (s[top] != u) {
			vis[s[top--]] = 0;
			ans++;
		}
		top--, ans++;
		if (ans > 1) sum++;
	}
	return;
}
int main()
{
	while (~scanf("%d%d", &N, &M))
	{
		int A, B;
		for (int i = 1; i <= M; i++) {
			scanf("%d%d", &A, &B);
			add(A, B);
		}
		for (int i = 1; i <= N; i++) {
			if (!dfn[i]) tarjan(i);
		}
		printf("%d\n", sum);
	}
}

```


---

## 作者：Arcturus1350 (赞：2)

赤裸裸的板子，就加一个特判就行。直接上代码

```cpp
#include<stdio.h>
#include<algorithm>
#include<iostream>
using namespace std;
bool ins[10000000];//记录入没入栈。
bool typ[10000000];//特判*1，是强连通分量就直接过了。
int top;int ans[10000000];
int stack[10000000];//手写栈。
void push(int x)//手写栈ing.
{
    ins[x]=true;
    stack[++top]=x;
    return ;
}
void pop()
{
    ins[stack[top]]=false;
    top--;
    return ;
}
struct data{
    int v;int next;
}edge[10000000];
int cnt;int alist[10000000];
void add(int u,int v)//继续手写结构体。
{
    edge[++cnt].v=v;
    edge[cnt].next=alist[u];
    alist[u]=cnt;
}
int dfn[100000];int dfu;//dfn作为x的入栈序号。
int low[1000000];int res=0;
void dfs(int x)//dfs
{
    dfn[x]=++dfu;//记录搜索序号
    push (x);
    low[x]=dfn[x];
    int next=alist[x];
    while(next)
    {
        int v=edge[next].v;
        if(ins[v]==true)//被搜过就不用再搜了
        {
            low[x]=min(low[x],low[v]);
        }
        else if(ins[v]==false)
        {
            dfs(v);
            low[x]=min(low[x],low[v]);
        }
        next=edge[next].next;
    }
    if(dfn[x]==low[x])//如果搜回来了。
    {
        while(low[stack[top]]==low[x])
        {
            typ[stack[top]]=true;
            pop();
            ans[x]++;
        }
        if(ans[x]>1) res++;//想要转圈的话必须要两个人及以上。
    }
    return;
}
int n,m;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int n1,m1;
        scanf("%d%d",&n1,&m1);//不解释。
        add(n1,m1);
    }
    for(int i=1;i<=n;i++)
    {
        if(typ[i]==1) continue;//要是在扫过的强连通分量里面直接过。
        else dfs(i);
    }
    printf("%d",res);
    return 0;//程序拜拜
}
```

---

## 作者：wohohohoho (赞：1)

~~蒟蒻发题解啦~~

一道十分简单的tarjan模版题，没学过tarjan的可以[看看](https://blog.csdn.net/qq_34374664/article/details/77488976)

（网上找的，没有帮人宣传的意思）

剩下的就直接套模版啦~只要判断一下强联通分量点的个数就行辣

~~贴代码~~
```cpp
#include<iostream>
using namespace std;
int head[100010],n,m;
int dfn[100010]={0},low[100010],sta[100010],dn=0；
int ans=0,top=0,cnt=0;
int num[100010]={0};
bool vis[100010]={0};

struct Edge //前向星存图，邻接表会爆
{
	int to,next;
}edge[100010];

void add(int u,int v,int c)//连边
{
	edge[c].to=v;
	edge[c].next=head[u];
	head[u]=c;
}

void tarjan(int x)//tarjan本体~~
{
	dfn[x]=++dn;
	low[x]=dn;
	vis[x]=true;
	sta[++top]=x;
	for(int i=head[x];i;i=edge[i].next)
	{
		int k=edge[i].to;
		if(!dfn[k])
		{
			tarjan(k);
			low[x]=min(low[x],low[k]);
		}
		else if(vis[k]) low[x]=min(low[x],low[k]);
	}
	if(dfn[x]==low[x])
	{
		++cnt;
		do
		{
			num[cnt]++;
			vis[sta[top--]]=false;
		}while(sta[top+1]!=x);
	}
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)//输入连边
	{
		int u,v;
		cin>>u>>v;
		add(u,v,i);
	}
	for(int i=1;i<=n;i++)//防止漏点
		if(!dfn[i])
			tarjan(i);
	for(int i=1;i<=cnt;i++)//检验这个强联通分量的点个数是否大于一
		if(num[i]>1)
			ans++；
	cout<<ans;
	return 0;
}
```


---

## 作者：Coding的二营长 (赞：1)

tarjan求强连通分量的基础题

主要利用了dfs回溯时的“连锁反应”判断强连通分量


由于dfs回溯的自身性质；会把大强连通分量中包含的小分量成员先出栈，但这道题只考虑分量数量，所以我们只用记录强连通分量中深度最低的点（即初点）有多少个就能求出分量数量

但tarjan中的出栈操作同样会把不属于强连通分量的 叶节点 当做初点脱出，由于只有回溯到初点这层时才会有出栈操作，我们用sum数组判断以u为初点的强连通分量中有几个成员，成员大于1才是合法强连通分量

```cpp
#include<iostream>
using namespace std;
int n,m;
int nxt[50001],to[50001],x[10001];

int dfn[10001],low[10001],vis[10001];//dfn:dfs序(越深越大，分量初点在整个分量中最小)  low[]:该点及其子孙中能连到的dfn中的最小值  vis[]:该点是否在栈中（不是是否搜过！）
																																						//初始时是自己能连到的最小值
int sta[10001],q=0;
int sum[10001];

void dfs(int u,int deep)
{
	dfn[u]=deep;
	low[u]=deep;
	vis[u]=1;
	sta[++q]=u;
	for(int j=x[u];j!=0;j=nxt[j])
	{	int v=to[j];
	if(!dfn[v])//下一个点没搜过，继续搜下去
		{
			dfs(v,deep+1);
			low[u]=std::min(low[u],low[v]);//放在dfs后更新很关键
															//自己的子孙找到回到“回到过去（分量初点）”的路径后
															//由下一个else if更新low[],然后在回溯时连锁更新（不超过初点的）祖先的low[]
		}
		else if(vis[v])//下个点已经进栈（是祖先）
		{
			low[u]=std::min(low[u],low[v]);//祖先的low[]肯定小，这里就是把当前节点的low[]指向分量初点
															//这里更新后，自己的父节点会和自己比较，因为自己的low[]中带分量初点的值(low[]在分量中最小)
															//只要自己的父节点在分量内部，与自己取min值必会也更新为分量初点的值
			
		}
	}
	if(dfn[u]==low[u])//该点没有出边 /该点是分量初点  就会进去if()
	{
		while(sta[q]!=u)
		{
			vis[sta[q]]=0;//出栈
			q--;
			sum[u]++;//一般需要求分量的数量、组合等就在出栈时用数组存储记录
		}
		vis[sta[q]]=0;
		q--;//强连通分量初点单独出栈
		sum[u]++;
	}
	
}


int main()
{

std::ios::sync_with_stdio(0);
cin>>n>>m;
int cnt=0;
int a,b;
for(int i=1;i<=m;i++)
{
	cin>>a>>b;
	cnt++;
	to[cnt]=b;
	nxt[cnt]=x[a];
	x[a]=cnt;
}

for(int i=1;i<=n;i++)
{							//dfn有赋值代表搜过，不然0
if(!dfn[i])dfs(i,1);//用dfn表示该点有没有搜过（搜过不为0）
						//注意vis[]表示是否在栈中，与是否搜过无关
}
int ans=0;
for(int i=1;i<=n;i++)
{
	if(sum[i]>1)ans++;//sum==1的点是没有下一条出边而出栈的点，去掉
	
}

cout<<ans;


return 0;
}

```

---

## 作者：QwQ_operator (赞：1)

思路：裸地板子题，裸到一定境界了。。。（求强连通分量的个数。。。。。）


只需要在板子里面加一个统计一个强连通分量个数的ans，由于我们求的是组合，一个人肯定不是一个组合对吧？！


这样我们在判断一下ans是否等于1，如果是的话强联通分量的个数-1.


代码：

```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 100001
using namespace std;
bool vis[N];
int n,m,x,y,tim,tot,top,sum;
int head[N],dfn[N],low[N],stack[N],belong[N];
inline int read()
{
    int x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0'; ch=getchar();}
    return x*f;
}
struct Edge
{
    int from,next,to;
}edge[N];
int add(int x,int y)
{
    tot++;
    edge[tot].to=y;
    edge[tot].next=head[x];
    head[x]=tot;
}
int tarjan(int now)
{
    dfn[now]=low[now]=++tim;
    stack[++top]=now;vis[now]=true;
    for(int i=head[now];i;i=edge[i].next)
    {
        int t=edge[i].to;
        if(vis[t]) low[now]=min(low[now],dfn[t]);
        else if(!dfn[t]) tarjan(t),low[now]=min(low[now],low[t]);
    }
    if(low[now]==dfn[now])
    {
        sum++;belong[now]=sum;
        int ans=1;
        for(;stack[top]!=now;top--)
        {
            vis[stack[top]]=false;
            belong[stack[top]]=sum;
            ans++;
        }
        vis[now]=false;top--;
        if(ans==1) sum--;
    }
}
int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++)
     x=read(),y=read(),add(x,y);
    for(int i=1;i<=n;i++)
      if(!dfn[i]) tarjan(i);
    printf("%d",sum);
    return 0;
}

```

---

## 作者：Del_Your_Heart (赞：1)

[可在博客内阅读](https://www.luogu.org/blog/62246/solution-p2863)


------------

# 写在前面

**$tarjan$算法前置小芝士：$dfs$序，强连通分量**

**$1^o$强连通分量**：在一个**有向图**的任意一非空子图中，**任意**两点都能互相到达，则称这个子图为该无向图的一个**强连通分量**。举个栗子：环就是一种强连通分量。

**重要性质1**：在一个**边权为正**的**有向图**中，若有一条经过点的权值和最大的路径通过一个强连通分量中的一点，则这条路径通过其**所有点**。（缩点的理论基础）

**重要性质2**：一个无向图的所有强连通分量都是**相互独立**的，没有相同的点或边。（这也是其被称为“分量”的原因）

**以上两条性质都是显而易见的，但却非常重要。**

**$2^odfs$序**：顾名思义，就是在$dfs$一个图时遍历各个点的**先后顺序**。

**优点**：将树或图用**线性**的结构存储，便于**查询**和**修改**。



------------

# 算法内容
$tarjan$算法是一种基于$dfs$的求强连通分量算法。

具体实现如下：维护一个$dfs$序——数组$dfn[]$，和由$i$节点能达到的$dfn$值最小的节点的$dfn$值——$low[]$，并维护一个栈，在最开始时将节点压入栈中。显然，**在一个强连通分量中，所有点的$low$值都为该强连通分量中$dfn$值最小的节点的$dfn$值**。利用这条性质，我们可以求出所有的强连通分量。

在每遍历完一个节点以及它之后的节点后，判断其$dfn$值是否和$low$值相等。如果是，那么**该节点即为其所在强连通分量中的$dfn$值最小的点**，将栈中该节点及其以上的所有节点全部取出，即为该强连通分量的所有点。

#### 给出伪代码：

```
void tarjan(int u){
	dfn[u]=low[u]=++时间编号;
	将u压入栈中;
	遍历所有u能到达的点v{
		if v没有被访问过{
        tarjan(v);
           low[u]=min(low[u],low[v]);
		}
		else if v仍在栈中{
			low[u]=min(low[u],dfn[v]);
		}
   }
	if low[u]==dfn[u]{
		++强连通分量编号;
		while 栈顶!=u{
			将栈顶编号;
			弹出栈顶;
		}
	}
}
```

### 对于本题而言，只要一个强连通分量包含超过$1$头奶牛，那么他们就珂以愉快的跳圆舞，只须统计出$size$大于$1$的强连通分量个数即可。


------------

# 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x=0,f=0;char ch=getchar();
    while(!isdigit(ch)){f|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return f?-x:x;
}
int n,m,ans=0;
int dfn[10005],low[10005],ins[10005],timing;
int colcnt,col[10005],colnum[10005];
vector<int> e[10005];
stack<int> q;
inline void tarjan(int u){
    dfn[u]=low[u]=++timing;q.push(u);ins[u]=1;
    for(int v:e[u])
        if(!dfn[v])
            tarjan(v),low[u]=min(low[u],low[v]);
        else if(ins[v])
            low[u]=min(low[u],dfn[v]);
    if(dfn[u]==low[u]){
        ++colcnt;
        int tmp;
        do{
            tmp=q.top();q.pop();ins[tmp]=0;
            col[tmp]=colcnt;
            colnum[colcnt]++;//统计size大小
        }while(tmp!=u);
    }
}
int main(){
    n=read();m=read();
    for(register int i=1,a,b;i<=m;++i)
        a=read(),b=read(),e[a].push_back(b);
    for(register int i=1;i<=n;++i)
        if(!dfn[i])
            tarjan(i);
    for(register int i=1;i<=colcnt;++i)
        if(colnum[i]>1)
            ans++;//计数
    cout<<ans;
    return 0;
}
```

---

## 作者：lytqwq (赞：0)

##### 昨天学的tarjan算法，现在来看一下标签为tarjan的唯一一道绿题

~~这道题是tarjan裸题~~

关于tarjan算法，我是看这篇算法入门的：
[http://www.cnblogs.com/shadowland/p/5872257.html](http://www.cnblogs.com/shadowland/p/5872257.html)

~~我才不会告诉你前向星我也是才学的~~：

[https://blog.csdn.net/acdreamers/article/details/16902023](https://blog.csdn.net/acdreamers/article/details/16902023)

##### 那么！这道题就可以：

1. 前向星输入后

1. 先求出强联通分量，

1. 然后统计每个强连通分量的成员个数。如果成员个数大于1，那么s++

1. 输出s



##### 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 10001
struct edge{
	int to,next;
}e[50001];
int head[N],gjc[N],s;
void add(int u,int v,int cnt)
{
	e[cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt;
}
int dfn[N],low[N],vis[N],Stack[N],dfs_num,color[N],top,col_num,n,m;
void tarjan(int x)
{
	dfn[x]=++dfs_num;
	low[x]=dfs_num;
	vis[x]=1;
	Stack[++top]=x;
	
	for(int i=head[x];i!=0;i=e[i].next)
	{
		int temp=e[i].to;
		if(dfn[temp]==0)
		{
			tarjan(temp);
			low[x]=min(low[x],low[temp]);
		}
		else if(vis[temp]==1)
		{
			low[x]=min(low[x],dfn[temp]);
		}
	}
	if(dfn[x]==low[x])
	{
		vis[x]=1;
		color[x]=++col_num;
		gjc[col_num]++;
		while(Stack[top]!=x)
		{
			color[Stack[top]]==col_num;
			vis[Stack[top--]]=0;
			gjc[col_num]++;
		}
		top--;
	}
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		add(x,y,i);
	}
	for(int i=1;i<=n;i++)
	{
		if(dfn[i]==0)
		{
			tarjan(i);
		}
	}
	for(int i=1;i<=col_num;i++)
	{
		if(gjc[i]>1)
		{
			s++;
		}
	}
	cout<<s;
}
```


---

## 作者：Tiffany_Tendering (赞：0)

    缩点的模板题
    
    首先注意审题 
    我们要根据顺时针建图 这就决定了这道试题是一道有向图 而不是无向图
    缩点的时候我们要用的是tarjan而不是并查集
    
    其实接下来就是缩点的常规思路了
    这道题比3387还要简单一下
    因为这道题不需要建新图 只要记录一下每个强连通分量里的点有几个就好了
    如果强连通分量里的点大于等于2个 那么ans++即可
    



```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<stack>
using namespace std;
const int maxn = 10005;
const int maxm = 50005;
int n,m,head[maxn],top,dfn[maxn],low[maxn],countt[maxn],indexx,ans,cnt;
bool instack[maxn] ;
struct edge {
	int to,next ;
}e[maxm];
stack< int > s;
void add_edge(int u,int v) {
	e[++top].to = v;
	e[top].next = head[u] ;
	head[u] = top ;
}

void tarjan(int u) {
	dfn[u] = low[u] = ++indexx ;
	s.push(u) ;
	instack[u] = 1;
	for(int i = head[u]; i ;i = e[i].next) {
		if(!dfn[e[i].to]) {
			tarjan(e[i].to) ;
			low[u] = min(low[u] , low[e[i].to]) ;
		}
		else
		  if(instack[e[i].to])
		    low[u] = min(low[u] , low[e[i].to]) ;
	}
	if(dfn[u] == low[u]) {
		cnt++;
		while(s.top() != u) {
			int k = s.top() ;  s.pop() ;
			instack[k] = 0;
			countt[cnt]++ ;   //记录一下这个强连通分量里有几个点 
		}
		s.pop() ;
		countt[cnt]++;
		instack[u] = 0;
	}
}

int main() {
	scanf("%d%d",&n,&m) ;
	for(int i = 1;i <= m ;++i) {
		int x,y; scanf("%d%d",&x,&y) ;
		add_edge(x , y) ;
	}
	for(int i = 1;i <= n ;++i)
	  if(!dfn[i]) tarjan( i ) ;
	for(int i = 1;i <= cnt ;++i) 
		if(countt[i] > 1) ans++;
	printf("%d",ans) ;
	return 0;
}
```

---

## 作者：BFSBFSBFSBFS (赞：0)

~~(这题真奇怪..).~~

题目做法.3页题解给的不能再清楚了..

所以我们讨论些别的事..

写完之后发现.所有题解连的全是有向边..

看题目描述..翻译上来看...~~蜜汁牵引~~...

然而原文上好像说的是..正拉反拉都是可以的...

~~(英语差请吐槽.).~~

所以似乎翻译的检验方式略有差错.?

~~反正只能单向用力的绳子很高级.~~.

有dalao能去找官方题解吗..~~暂时不能翻墙.~~.

反正有向能过就对了..

那么无向怎么弄.?

**换种判断同边的方法:每条边只能用1次.**,

~~(代码太丑.拒发.).~~.

(ಡωಡ).


---

## 作者：yqkkkkk (赞：0)

#### tarjan裸题，不知道为什么是普及+提高
要注意的是奶牛自己不算一个强连通图
##  **如果used和way数组不用bool类型会炸（MLE）**
### **主要思想：**~~代码里都说了直接看代码吧~~ 
如果没看懂的话可以看[这个网址](http://blog.csdn.net/jeryjeryjery/article/details/52829142?locationNum=4&fps=1)**他的代码有些问题**但思路是正确的（和我一样），再融合他的思想理解我的代码就可以了
废话不多说先附上代码：
```cpp
#include<stdio.h>
#include<stack>
#define N 10010
using namespace std;
struct cow{int dfn,low;bool used;}f[N];
//dfn为该点入栈编号，low为其最早入栈的祖先，used记录其是否被使用 
stack<int> s;//栈，一个后进先出的结构，可以理解为“倒队列”ps：如果队列（queue）你都不会那你八成废了
int n,m,i,j,cnt,ans;
bool way[N][N];
//used和way一定要定成bool类型，否则会MLE 
inline int read()//快速读入 
{
	int sign=1,num=0;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')sign=-1;ch=getchar();}
	while(isdigit(ch)){num=num*10+(ch-'0');ch=getchar();}
	return sign*num;
}
void init()//输入 
{
	n=read();
	m=read();
	while(m--)
	{
		i=read();
		j=read();
		way[i][j]=1;//i奶牛牵引j奶牛
					//由于边是又向的所以只存一次 
	}
}
void tarjan(int i) 
{
	f[i].dfn=f[i].low=++cnt;
	f[i].used=1;
	s.push(i);
	//初始化 
	for(int j=1;j<=n;++j)
	{
		//判断i奶牛是否牵引j奶牛 
		if(way[i][j])
			if(!f[j].dfn)
			{
				tarjan(j);
				f[i].low=min(f[i].low,f[j].low);//更新祖先 
			}
			//used在此处不加会影响已连接的连通图 
			else if(f[j].used) 
				f[i].low=min(f[i].low,f[j].low);
	}
	//构成连通图 ，并清栈准备下一点查找 
	if(f[i].dfn==f[i].low) 
	{
		int t,c(0);
		do
		{
			f[t=s.top()].used=0;
			s.pop();
			++c;
		}while(t!=i);
		if(c>1)++ans;//c至关重要，因为题目中一只奶牛自己不算一个连通图 
	}
}
int main()
{
	init();
	for(int i=1;i<=n;++i)if(!f[i].dfn)tarjan(i);
	printf("%d",ans);
	return 0;
}
```
不懂的在讨论栏里问我

~~然而我并不会去理你~~


---

## 作者：LPA20020220 (赞：0)

tarjan的裸题啦，直接一遍涂色，再搜索不同颜色的个数，如果有两头牛及以上同色就将ans+1.

注意牛可能“离群”，所以每头牛都要搜一遍（如果未搜到）

上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10005;
struct sd
{
    int node;
    vector <int> next;
};
sd data[N];
int low[N];//栈中最早的与自己在同一环中的位置 
int dfn[N];//时间戳，表示dfs时的顺序 
bool vis[N];
int color[N];//染色结果 
bool gone[N]; 
int dye[N];
int dfnnum=0,col=0;//col表示染色的种类 
stack <int> mystack;
inline void tarjan(int p)
{
    gone[p]=true;
    dfnnum++;
    dfn[p]=dfnnum;
    low[p]=dfn[p];
    vis[p]=true;
    mystack.push(p);
    for(register int i=data[p].next.size()-1;i>=0;i--)
    {
        int tar=data[p].next[i];
        if(dfn[tar]==0)//未访问过的节点 
        {
            tarjan(tar);
            low[p]=min(low[tar],low[p]);
        }
        else if(vis[tar])//已访问 
        {
            low[p]=min(low[p],dfn[tar]);
        }
    }
    if(dfn[p]==low[p])//回溯涂色，将整个强连通分量涂成一种颜色 
    {
        vis[p]=false;
        col++;
        color[p]=col;
        while(mystack.top()!=p)
        {
            color[mystack.top()]=col;
            vis[mystack.top()]=false;
            mystack.pop();
        } 
        mystack.pop();
    }
}
int main()
{
    int cow, rope,a,b;
    memset(gone,false,sizeof(gone));
    memset(dye,false,sizeof(dye));
    memset(vis,false,sizeof(vis));
    memset(dfn,false,sizeof(dfn));
    scanf("%d%d",&cow,&rope);
    for(int i=1;i<=rope;i++)
    {
        scanf("%d%d",&a,&b);
        data[a].next.push_back(b);
    }
    for(int i=1;i<=cow;i++)//为了确保没有“离群的牛”每头牛都尝试搜一遍 
    {
        if(!gone[i])
        {
            tarjan(i);
        }
    }
    int ans=0;
    for(int i=1;i<=cow;i++)//确定颜色数量 
    {
        if(dye[color[i]]==0)
        {
            dye[color[i]]++;
            continue;
        }
        if(dye[color[i]]==1)
        {
            dye[color[i]]++;
            ans++;
        }
        else dye[color[i]]++;
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：winmt (赞：0)

裸的tarjan求一个强连通分量，就是答案。模板题差不多。。。



    
    

    
    
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<stack>
#include<vector>
using namespace std;
struct node
{
    int num,par;
}p[10005];
int n,m,index=1,x,y,cnt;
vector<int>v[10005];
bool vis[10005];
int ind[10005];
stack<int>s;
bool in_stack[10005];
void tarjan(int x)
{
    p[x].num=index;
    p[x].par=p[x].num;
    index++;
    vis[x]=1;
    in_stack[x]=1;
    s.push(x);
    for(int i=0;i<v[x].size();i++)
    {
        if(!vis[v[x][i]])
        {
            tarjan(v[x][i]);
            p[x].par=min(p[x].par,p[v[x][i]].par);
        }
        else if(in_stack[v[x][i]])
        {
            p[x].par=min(p[x].par,p[v[x][i]].num);
        }
    }
    if(p[x].num==p[x].par)
    {
        ++cnt;
        int gutc=0;
        int k;
        do
        {
            k=s.top();
            s.pop();
            in_stack[k]=0;
            gutc++;
        }while(k!=x);
        if(gutc==1)cnt--;
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        v[x].push_back(y);
    }
    for(int i=1;i<=n;i++)
    {
        if(!vis[i])tarjan(i);
    }
    printf("%d\n",cnt);
    return 0;
} 

```

---

## 作者：Hyxss (赞：0)

这这着这这道题只要把板子稍微改一下下就好啦

**感谢[Rothen](https://www.luogu.org/space/show?uid=99827)  大佬 帮我改了一下细节**

至于算法在这里就不过多阐述罗~~我才不会告诉你其实我也不怎么懂（那逆还发题解）~~

实在看不懂的话  就去找2018luogu博客 [传送门](https://www.luogu.org/blog/styx-ferryman/chu-tan-tarjan-suan-fa-qiu-qiang-lian-tong-fen-liang-post)

不废话罗直接贴代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
vector<ll> g[10000+500];
ll dfn[10000+500],sta[10000+500],/*栈*/low[10000+500],color[10000+500],num[10000+500];
bool vis[10000+500];
ll deep,top,sum;
inline ll read(){//快读
    bool f=1;ll x=0;char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=!f;c=getchar();}
    while(c>='0'&&c<='9') {x=x*10+c-'0';c=getchar();}
    return f?x:-x;
}
void tarjan(ll u){
    dfn[u]=++deep;
    low[u]=deep;
    vis[u]=1;
    sta[++top]=u;
    for(ll i=0;i<g[u].size();i++){
        if(!dfn[g[u][i]]) {
             tarjan(g[u][i]);
            low[u]=min(low[u],low[g[u][i]]);
        }
       else if(vis[g[u][i]])
            low[u]=min(low[u],low[g[u][i]]);
    }
    if(dfn[u]==low[u]){
        vis[u]=0;
        color[u]=++sum;
         num[summ]++;
        while(sta[top]!=u){
            vis[sta[top--]]=0;
            num[sum]++;
            color[sta[top]]=sum;
        }
        top--;
    }
}
int main()
{
    ll i,j;
    ll n,m;
    ll a,b;
    ll ans=0;
    n=read();m=read();
    for(i=1;i<=m;i++){
        a=read();b=read();
        g[a].push_back(b);
    }
    for(i=1;i<=n;i++)
        if(!dfn[i])
            tarjan(i);
    for(i=1;i<=sum;i++)
        if(num[i]>1) ans++;       
    cout<<ans;
    return 0;
}
```

**温馨提示：千万不要ctrl+c  ctrl+v**
![](https://cdn.luogu.com.cn/upload/pic/64567.png)

---

