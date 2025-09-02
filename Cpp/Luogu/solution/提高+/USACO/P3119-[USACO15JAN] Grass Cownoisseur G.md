# [USACO15JAN] Grass Cownoisseur G

## 题目描述

为了更好地管理牛群的放牧路线，Farmer John 在他的农场中安装了若干单向牛道。农场由 $N$ 块草场组成，编号为 $1$ 到 $N$，每条单向牛道连接一对草场。例如，若存在一条从草场 $X$ 到 $Y$ 的路径，则牛可以从 $X$ 前往 $Y$，但不能从 $Y$ 返回 $X$。

众所周知，Bessie 喜欢尽可能多地品尝不同草场的牧草。她每天从草场 $1$ 出发，访问一系列草场后返回草场 $1$。她试图最大化沿途经过的不同草场数量（重复访问的草场只算一次）。

由于单向路径的限制，Bessie 担心这会减少她每日路线中可以访问的草场数量。她想知道如果她违反规则，在路线中最多逆向通过某条道路一次，最多能品尝多少草场的牧草。请计算她从草场 $1$ 出发并返回的情况下，最多能访问的不同草场数量。注意 Bessie 在整个旅程中最多只能逆向通过一条道路，且同一条路径不能逆向两次。

## 说明/提示

**样例解析：**

以下是样例输入的 ASCII 图示：

```
v---3-->6
7   | \ |
^\  v  \|
| \ 1   |
|   |   v
|   v   5
4<--2---^
```

Bessie 可以通过逆向路径 $5\to 3$ 访问草场 $1, 2, 4, 7, 2, 5, 3, 1$。到达草场 $3$ 后，若不再次逆向其他路径则无法前往 $6$。

## 样例 #1

### 输入

```
7 10 
1 2 
3 1 
2 5 
2 4 
3 7 
3 5 
3 6 
6 5 
7 2 
4 7 

```

### 输出

```
6 
```

# 题解

## 作者：block_joker (赞：175)

首先很容易想到缩点，记c[i]为i所在强连通分量名，p[c[i]]为i点所在强联通分量能相互通达的点数

然后用是spfa跑一次以1为起点的最长路，记为dis1[i]

以及以1为终点的最长路（可以用建反图实现），记做dis2[i]

最后枚举i,答案就为max{dis1[c[i]]+dis2[v]-p[c[1]]} （v->i连通且dis1[c[i]]
,dis2[v]都不为0）

还有注意ans初始化为p[c[1]],因为有可能出不去（就是反转边没有用的情况）

为什么dis1[c[i]]和dis2[v]不会有重点呢，因为如果有重点的话就会在缩点的时候被缩掉了

想不明白可以自己画一画


代码：
```cpp
#include<vector>
#include<map>
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<queue>
using namespace std;
const int N=1e5+5,M=1e5+5;
int h[N],nxt[M],r[M],sum=1;
int h1[N],nxt1[M],r1[M],sum1=1;
int h2[N],nxt2[M],r2[M],sum2=1;
int t,c[N],dfn[N],low[N],s[N],top,color,num,start,gass[N];
int p,q,n,m;
int dis1[N],dis2[N];
bool use[N];
void add(int a,int b){sum++;nxt[sum]=h[a],r[sum]=b;h[a]=sum;}
void add1(int a,int b){sum1++;nxt1[sum1]=h1[a],r1[sum1]=b;h1[a]=sum1;}
void add2(int a,int b){sum2++;nxt2[sum2]=h2[a],r2[sum2]=b;h2[a]=sum2;}
void found(int k)
{
dfn[k]=low[k]=++num,s[++top]=k,use[k]=1;
for(int i=h[k];i;i=nxt[i])
{
	int v=r[i];
	if(!dfn[v])found(v),low[k]=min(low[k],low[v]);
	else if(use[v])low[k]=min(low[k],low[v]);
}	
if(low[k]==dfn[k])
{
	c[k]=++color,use[k]=0;
	gass[color]=1;
	while(s[top]!=k){gass[color]++,use[s[top]]=0;c[s[top--]]=c[k];}
		top--;
}
}
void spfa1(int k)
{
	dis1[k]=gass[k];
	queue<int> Q;
	Q.push(k);
	while(!Q.empty()){
		int now=Q.front();Q.pop();
		for(int i=h1[now];i;i=nxt1[i]){
			int v=r1[i];
			if(dis1[v]<dis1[now]+gass[v]){
				dis1[v]=dis1[now]+gass[v];
				if(!use[v])Q.push(v),use[v]=1;
			}
		}
				use[now]=0;
	}
}
void spfa2(int k)
{ 
    dis2[k]=gass[k];
	queue<int> Q;
	Q.push(k);
	while(!Q.empty()){
		int now=Q.front();Q.pop();
		for(int i=h2[now];i;i=nxt2[i]){
			int v=r2[i];
			if(dis2[v]<dis2[now]+gass[v]){
				dis2[v]=dis2[now]+gass[v];
				if(!use[v])Q.push(v),use[v]=1;
			}
		}
		use[now]=0;
	}
}
int main()
{
scanf("%d%d",&n,&m);
while(m--)
{
scanf("%d%d",&q,&p);
add(q,p);
}
for(int i=1;i<=n;i++)if(!dfn[i])found(i);
start=c[1];
for(int i=1;i<=n;i++)
for(int u=h[i];u;u=nxt[u])
if(c[i]!=c[r[u]])add1(c[i],c[r[u]]),add2(c[r[u]],c[i]);
spfa1(start),spfa2(start);
int ans=gass[start];
for(int i=1;i<=n;i++)
	if(!use[c[i]]&&dis1[c[i]]){
	int now=c[i];
	use[now]=1;
	for(int u=h2[now];u;u=nxt2[u]){
		int v=r2[u];
		if(!dis2[v])continue;
		ans=max(ans,dis1[now]+dis2[v]-gass[start]);
	}
		
	}
	cout<<ans;
return 0;
}


```

---

## 作者：hsfzLZH1 (赞：106)

**此题难在建模。**

看到这道题，首先想到的是$Tarjan$缩点，将图上的强连通分量（强连通分量中的任意两点相互可达）缩成点，形成一个新图，可以保证新图上无环（因为如果有环则环一定在一个强连通分量中），然后再考虑接下来的步骤。

简单概述一下$Tarjan$求强连通分量的过程。我们用$DFS$解决这个问题。在$DFS$的过程中，对节点有一个访问序号，记为$dfn_i$。然后，对于节点$i$，我们定义其在$DFS$树上，中间节点在节点$i$的子树中且不经过节点$i$到其$DFS$树上的父亲节点$fa$的边$(i,fa)$（如果有重边则可以经过）所能到达的最小的时间戳，即$low_i=min~dfn_a$。对于一个节点$i$，如果$low_i=dfn_i$，那么肯定有一个包含节点$i$的新强联通分量。如何计算这个强连通分量内的节点呢？我们用一个数据结构栈（$STL~stack$）解决这个问题。我们每访问一个新的节点，将该节点加入栈；对一个节点的$DFS$过程结束时，如果找到一个新的强连通分量时，依次将栈中的元素弹出，直到弹出的元素是当前节点为止。

由于这个$DFS$过程需要访问一个节点所有的出边，我们可以用邻接链表存边（$vector$或链式前向星）。时间复杂度$O(N+M)$。

然后便是在$DAG$上进行操作的问题了。看了下其他大佬的题解，都是分类，枚举。这里介绍一个分层图的方法。

考虑一张图，将这个图复制一份，点的编号从$1$~$N$到$(N+1)$~$(N+N)$。然后在两层图中连边。对于原图上的每一条边，**从原图的指向点到新图的起始点连一条边，边权与原边相同，代表逆向走一条边**。逆向走了一条边，就不能再逆向走了，所以从上面的一层（新图）无法回到下面的一层。最后跑一遍$SPFA$，节点$1$所在的强连通分量编号，到节点$1$所在的强连通分量编号+$N$上的最长路，就是最后的答案。

代码：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
const int maxn=100010;
const int inf=2e9;
vector<int>G[maxn];
vector<int>G1[maxn*2];
int n,m,u,v,op,index_,dfn[maxn],low[maxn],bcc[maxn],siz[maxn*2],cnt,dist[maxn*2];
bool tf[maxn*2];
stack<int>st;
queue<int>q;
void dfs(int cur)
{
    dfn[cur]=low[cur]=++index_;
    tf[cur]=true;
    st.push(cur);
    for(int i=0;i<G[cur].size();i++)
    {
        if(!dfn[G[cur][i]])
        {
            dfs(G[cur][i]);
            low[cur]=min(low[cur],low[G[cur][i]]);
        }
        else if(tf[G[cur][i]])low[cur]=min(low[cur],dfn[G[cur][i]]);
    }
    if(dfn[cur]==low[cur])
    {
        cnt++;
        while(st.top()!=cur)
        {
            bcc[st.top()]=cnt;
            tf[st.top()]=false;
            siz[cnt]++;
            st.pop();
        }
        bcc[st.top()]=cnt;
        tf[st.top()]=false;
        siz[cnt]++;
        st.pop();
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    while(m--)
    {
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
    }
    for(int i=1;i<=n;i++)if(!dfn[i])dfs(i);
    for(int i=1;i<=cnt;i++)siz[cnt+i]=siz[i];
    for(int i=1;i<=n;i++)for(int j=0;j<G[i].size();j++)if(bcc[i]!=bcc[G[i][j]])
    {
        G1[bcc[i]].push_back(bcc[G[i][j]]);
        G1[bcc[G[i][j]]].push_back(bcc[i]+cnt);
        G1[bcc[i]+cnt].push_back(bcc[G[i][j]]+cnt);
    }
    tf[bcc[1]]=true;q.push(bcc[1]);
    while(!q.empty())
    {
        int x=q.front();
        for(int i=0;i<G1[x].size();i++)if(dist[G1[x][i]]<dist[x]+siz[x])
        {
            dist[G1[x][i]]=dist[x]+siz[x];
            if(!tf[G1[x][i]])tf[G1[x][i]]=true,q.push(G1[x][i]);
        }
        q.pop();tf[x]=false;
    }
    printf("%d\n",dist[bcc[1]+cnt]);
    return 0;
}
```
用这样的思想，还可以解决一道这样的问题：给定一个有向图$G$，有$m$张优惠券，可以把一条边的边权改成一个固定值$k$，求节点$s$到节点$t$之间最短路的长度和方案数。方法是建立一个$m+1$层的多层图，层与层之间的边的权值都为$k$，然后跑最短路。由于用了优惠券不一定能达到优化的目的，所以答案为$min(t,t+n,t+n+n,...)$。方案数也可如此做。

----------------------------------

感谢[实哥](https://www.luogu.org/space/show?uid=54153)大佬提供的$hack$数据，本篇题解其实有一个瑕疵，但由于数据水没有测出来。

如果整个图是一个强连通分量，转换成新图的时候就不会加边，所以最后节点的最长路是错误的。

解决方法也显而易见，就是建新图的时候从起点直接往终点连一条边权为起点代表的强连通分量的大小的边。

~~不贴代码了（其实只用改一行）~~

---

## 作者：nihanchu (赞：23)

这道题我看了一个上午所有需要的相关知识点的视频，然后花了好久才打出来，果然是水平不够啊。。。。


为了以后还能看懂并记住这些知识点，特意写篇博客来记录一下。


优秀题解博客：<http://blog.csdn.net/popoqqq/article/details/44081279>

上面这篇博客写了好多我没见过的语法，看上去好厉害。。。。


首先，写这道题时，先要学会以下知识点：


1.了解如何寻找强连通分量并进行缩点


2.如何在DAG（有向无环图）中用拓扑找最短路


3.如何使用链式前向星（会用vector的话可以自动忽略这一点）


题目链接：<http://www.lydsy.com/JudgeOnline/problem.php?id=3887>

这道题我们可以发现如果我们走到一个强连通分量中，为了有尽可能多的点，我们会把它全都走一遍再决定从分量中的哪个点走出。


所以我们可以先进行缩点 ，缩点后的点权为点所代表的原强连通分量中点的个数，这样我们就把它变成了更好处理的DAG。处理后的所有点总共能分成三类：


1.能到达点1的


2.从点1出发能到达的


3.和点1没有任何关系的


很显然我们可以删除第三类点，因为就算怎么翻转路径，第三类的点都和答案没有任何关系。而我们最终要反转的边在一开始一定是一条从第二类点到第一类点的边，我们把这样的边全部反转，把能达到点1的路径统统改成到达点n+1，这样问题就简化成了在DAG中找一条从点1到点n+1的点权和最大的路径，很明显，我们可以用拓扑+dp解决了；


可能有人会和我刚开始一样觉得万一我们最后找到的路径中有两条边被反转过，怎么办？其实可以发现这是不可能的，因为如果有，那么那两条被反转的边的中间的路径一定符合它们未反转之前就既能到达点1，也能被点1，可是这是DAG，绝不会存在环。


唔，这是大概思路，下面的程序实现与这个思路存在一点小小的差异，具体程序注释中讲吧。

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<stack>
using namespace std;
struct point{
    int to,next;
}edge[200000],edge1[200000][3];
int cnt,n,m,ans,t,tot;
int head[200000],head1[200000][3],d[200000][3],dfn[200000],low[200000],v[200000];
int node[200000],f[200000][3],size[200000],q[200000];
stack<int>s;
void add(int u,int v)
{
  edge[++cnt].to=v;
  edge[cnt].next=head[u];
  head[u]=cnt;
}
void add1(int u,int v,int ch)
//ch为1的时候表示原本的缩点后的图，2的时候表示所有边都已反向过的图
{
   if (ch==1) cnt++;
   d[v][ch]++; 
   edge1[cnt][ch].to=v;
   edge1[cnt][ch].next=head1[u][ch];
   head1[u][ch]=cnt;
}
void tarjan(int u)
{
  dfn[u]=low[u]=++t;//赋初值
  s.push(u);//放入栈中
  for (int i=head[u];i;i=edge[i].next)
      if (dfn[edge[i].to]==0)
//如果说这个点的dfn为0的话就表示这个点还未被搜索到过
      {
        tarjan(edge[i].to);
        low[u]=min(low[u],low[edge[i].to]);
    }
    else if (!v[edge[i].to])
//这个点没有出栈的话
     low[u]=min(low[u],dfn[edge[i].to]);
   if (dfn[u]==low[u])//如果这是一个强连通分量的根的话
   {
        tot++;//强连通分量数量加1，及缩点后的点数加1
        int now=0;
        while (now!=u)
        {
          now=s.top();//弹出栈
          s.pop();
       v[now]=true;//这个点已经出栈了
       node[now]=tot;//这个点属于哪一块强连通分量
       size[tot]++;    //这个强连通分量的大小加1
     }
   }
}
void find(int ch)
{
  f[node[1]][ch]=size[node[1]];
//ch依旧表示路是否被反向
//f[i][ch]数组则表示在当前的图，1到达[i]的路径上点权和最大为多少
  int ta=0; 
//当前队列的尾巴
  for (int i=1;i<=tot;i++) 
  if (d[i][ch]==0) q[++ta]=i;//如果说入度为0，加入队列
  while  (ta>0)//拓扑+dp就不详细解释了
  {
      int p=q[ta--];
      for (int i=head1[p][ch];i;i=edge1[i][ch].next)
      {
        f[edge1[i][ch].to][ch]=max(f[edge1[i][ch].to][ch],f[p][ch]+size[edge1[i][ch].to]);
      if (--d[edge1[i][ch].to][ch]==0) q[++ta]=edge1[i][ch].to;
    }
  }
}
int main()
{
  int x,y;
  scanf("%d%d",&n,&m);
  for (int i=1;i<=m;i++)    
  {
      scanf("%d%d",&x,&y);
      add(x,y);//连接未缩点之前的边
  }
  t=0;
  for (int i=1;i<=n;i++) if (!v[i]) tarjan(i);
//用tarjan求强连通分量并进行缩点
//v[i]表示这个点有无出栈，如果为false的话，说明这个点还未被访问或者说还在栈中
 cnt=0; 
  for (int i=1;i<=n;i++)
   for (int j=head[i];j;j=edge[j].next)
    if (node[i]!=node[edge[j].to])//此语句避免自环
    {
      add1(node[i],node[edge[j].to],1);//连边，之后搜索出的是1能到达的点
      add1(node[edge[j].to],node[i],2);//我们反向所有的边，这样搜索出来1能到达的点，其实是能到达1的点，这样就避免了构造n+1这个点
    }
  memset(f,0xef,sizeof f);//清空为一个很大的负数
  find(1);find(2);//搜索
  ans=size[node[1]];//开始答案的大小为1所在的强连通分量的大小
  for (int i=1;i<=n;i++)
   for (int j=head[i];j;j=edge[j].next)
//这里我们枚举所有未缩点前的边（当然这个取决于你自己）
//边的方向本来是node[i]——>node[edge[j].to]
//我们把它们反向，f[node[edge[j].to]][1]表示从点1到node[edge[j].to]，最大点权和为多少
//f[node[i]][2]表示从node[i]到点1最大点权和为多少
//这样边反向后，我们就可以成功的构建一条
//不过因为f[node[edge[j].to]][1]和f[node[i]][2]都包含了1所在的强连通分量的点权，所以我们需要减去一个size[node[1]]。
//1——>node[edge[j].to]——>node[i]——>1的路径了
    if (node[i]!=node[edge[j].to])
    ans=max(ans,f[node[edge[j].to]][1]+f[node[i]][2]-size[node[1]]);
   printf("%d\n",ans);
   return 0;   
} 
```
看完这道题好像收获了不少。。。

---

## 作者：namelessgugugu (赞：22)

第一次切紫题稍微有些激动，然后看到题解清一色的~~已经死了的~~SPFA，决定自己写一篇用缩点+拓扑的题解。
#### 思路
看到题面中的“只吃一次”和“有向图”，自然不难想到缩点。

假设我们已经跑完一遍tarjan了，设草坪 $1$ 所在的强连通分量为 $s$。至多逆行一次的可能情况仅有两种：

* 1.不逆行，这样就只能在 $s$ 里面走，不然就回不来了。
* 2.从 $s$ 往下走，走到分量 $u$，同时有一个 能到达 $s$ 的分量 $v$有一条指向 $u$ 的边，从 $u$ 逆行到 $v$，再走到 $s$。

第一点过于简单，我们主要扯扯第二点。

关于第二点，我们可以选择在原DAG图和其反图上以 $s$ 为起点各跑一遍最长路，设点 $i$ 在两个图上的最长路分别是 $f[1][i],f[1][i]$。答案就是 $max(f[1][u]+f[0][v]-w[s])$，其中 $u,v$ 是任意一条边的起点和终点，$w[i]$ 是分量 $i$ 的节点数。

关于如何跑最长路，大多数题解选择的是SPFA，但是这玩意时间复杂度过于不稳定（可能会被卡成 $O(NM)$，虽然我不知道DAG图做不做得到），而且在DAG图中，用 __拓扑__ 求最长路显然更加方便，而且时间复杂度稳定在 $O(N)$，所以我们选择通过跑两次拓扑来找最长路。

#### 代码
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
const int N = 100005;
int n, m, ans;

int x[N], y[N];
int edge[N], next[N], head[N], tot;

int dfn[N], low[N], tt, st[N], top;
bool ins[N];

int col[N], cnt, w[N];
// col表示节点所属的分量编号，cnt表示分量数量，w表示分量大小 
int f[2][N], d[N];
// f的含义见上文，d表示每个分量的入度 
bool vis[2][N];
// vis[0/1][i] 表示i节点在正/反DAG图上是否能从s走到 
inline void add(int f, int t)//链式前向星 
{
	edge[++tot] = t, next[tot] = head[f], head[f] = tot;
	return;
}
void tarjan(int x)//用tarjan缩点 
{
	dfn[x] = low[x] = ++tt;
	ins[x] = 1, st[++top] = x;
	for(int i = head[x];i;i = next[i])
	{
		int y = edge[i];
		if(!dfn[y])
			tarjan(y), low[x] = std::min(low[x], low[y]);
		else if(ins[y])
			low[x] = std::min(low[x], dfn[y]);
	}
	if(dfn[x] == low[x])
	{
		++cnt;
		int tmp = -1;
		while(tmp != x)
		{
			tmp = st[top--];
			++w[cnt], col[tmp] = cnt, ins[tmp] = 0;
		}
	}
	return;
}
void topo(const int typ)//拓扑排序，参数typ的值0/1表示现在是正/反图 
{
	std::queue<int> que;
	for(int i = 1;i <= cnt;++i)
		if(!d[i])//如果入度为0，压入队列 
			que.push(i);
	while(!que.empty())
	{
		int x = que.front();
		f[typ][x] += w[x]; 
		que.pop();
		for(int i = head[x];i;i = next[i])
		{
			int y = edge[i];
			--d[y];
			if(vis[typ][x])
				vis[typ][y] = 1, f[typ][y] = std::max(f[typ][x], f[typ][y]);
			//如果s能走到x，那么也能走到y，更新vis和f的值 
			if(!d[y])//如果入读为0，压入队列 
				que.push(y);
		}
	}
	return;
}
int main(void)
{
	scanf("%d%d", &n, &m);
	for(int i = 1;i <= m;++i)
		scanf("%d%d", x+i, y+i), add(x[i], y[i]);
	//缩点 
	for(int i = 1;i <= n;++i)
		if(!dfn[i])
			tarjan(i); 
	for(int i = 1;i <= m;++i)
		x[i] = col[x[i]], y[i] = col[y[i]];
	int s = col[1];
	vis[0][s] = vis[1][s] = 1;//节点s无论在正反图上都能走到自己 
	memset(head, 0, sizeof(head)), tot = 0;
	memset(d, 0, sizeof(d));
	//跑拓扑之前记得memest 
	for(int i = 1;i <= m;++i)
		if(x[i] != y[i])
			add(x[i], y[i]), ++d[y[i]];
	topo(0);
	memset(head, 0, sizeof(head)), tot = 0;
	memset(d, 0, sizeof(d));
	//第二次也不要忘记 
	for(int i = 1;i <= m;++i)
		if(x[i] != y[i])
			add(y[i], x[i]), ++d[x[i]];//这次是反图 
	topo(1);
	ans = w[s];//对应上文第一种情况 
	for(int i = 1;i <= m;++i)
		if(vis[1][x[i]] && vis[0][y[i]])//对应上文第二种情况 
			ans = std::max(ans, f[1][x[i]]+f[0][y[i]]-w[s]);
	printf("%d", ans);//输出答案 
	return 0;
}
```

---

## 作者：DarthVictor (赞：8)

# 题目
[原题链接](https://www.luogu.com.cn/problem/P3119)
# 解说
刷$Tarjan$题的时候看到的题目，第一次见到把分层图和$Tarjan$结合的题目，觉得这样的思路很有趣，写博客以记之。

**总思路：建双层图->Tarjan缩点->最长路**

首先看到题目中“只能走一次的逆向边”这样的条件，我们会很自然地想到建一个分层图。每一个点$i$在第二层有一个对应的编号为$i+n$的对应点。第二层建边基本是第一层的还原，同时对于每一条边$x$到$y$还要建一条$y$到$x+n$连接一二层，由于是单向边我们就可以保证上了二层就没办法再下来，即保证了逆向边只走一次。

图建好之后很自然地跑$Tarjan$强联通分量的板子再缩点。这时候新建的边的权值应该为目的地强联通分量的大小，这样我们只要走过这条边就可以获得去点的答案，同时因为缩点之后的图是有向无环图，可以保证一个边跑最长路时只走一次，即保证了一个点的权值只取了一次。

最后输出答案时记得应该取$max(dis[belong[1]],dis[belong[1+n]])$，因为答案可能在第一层的终点取得也可能在第二层的终点取得。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100000+3,maxe=100000+3;
int head[2*maxn],tot,dfn[2*maxn],low[2*maxn],dfn_clock,scc_cnt,size[2*maxn],n,m,stk[2*maxn],top,belong[2*maxn],cnt,h[2*maxn],dis[2*maxn];
//记得开二倍
//话说用到的数组真多……
bool vis[2*maxn];
struct edge{//原边
	int to,next;
}e[3*maxe];//记得开三倍
struct edge2{//缩点之后的边
	int to,next,w;
}ed[3*maxe];//记得开三倍
void add(int a,int b){
	e[++tot].to=b;
	e[tot].next=head[a];
	head[a]=tot;
}
void insert(int a,int b,int w){
	ed[++cnt].to=b;
	ed[cnt].w=w;
	ed[cnt].next=h[a];
	h[a]=cnt;
}
void tarjan(int u){//求强联通分量的板子
	dfn[u]=low[u]=++dfn_clock;
	stk[++top]=u;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}else if(!belong[v]) low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		scc_cnt++;
		while(1){
			int tmp=stk[top--];
			belong[tmp]=scc_cnt;
			size[scc_cnt]++;
			if(tmp==u) break;
		}
	}
}
void spfa(int s){//跑最短路
	deque<int> q;
	q.push_back(s);
	while(!q.empty()){
		int u=q.front();
		q.pop_front();
		vis[u]=0;
		for(int i=h[u];i;i=ed[i].next){
			int v=ed[i].to,w=ed[i].w;
			if(dis[u]+w>dis[v]){
				dis[v]=dis[u]+w;
				if(!vis[v]){
					vis[v]=1;
					if(!q.empty()&&dis[v]>dis[q.front()]) q.push_front(v);
					else q.push_back(v);
				}
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(x+n,y+n);
		add(y,x+n);//分层图核心加边
	}
	for(int i=1;i<=2*n;i++) if(!dfn[i]) tarjan(i);
	for(int i=1;i<=2*n;i++){//缩点
		for(int j=head[i];j;j=e[j].next){
			int x=belong[i],y=belong[e[j].to];
			if(x!=y) insert(x,y,size[y]);
		}
	}
	spfa(belong[1]);
	printf("%d\n",max(dis[belong[1]],dis[belong[1+n]]));
	return 0;
}
```

幸甚至哉，歌以咏志。

---

## 作者：木木！ (赞：7)

各位`dalao`都是用`SPFA`做出来的。虽然这题`SPFA`跑`DAG`的时间复杂度并没有更劣，但是却有一种方法可以不用`SPFA`来做。因为缩点后图变成了一张`DAG`，所以可以直接用`DAG DP`求最长路。

具体流程是，建图的同时建反图。由于强连通分量在反图中不变，所以只需要求一次强连通分量。

然后，`c[x]`表示`x`所在的强连通分量，从`c[1]`开始，反向跑一遍`dp`，求出从`i`走到`c[1]`的最长路径，然后再从`c[1]`开始正向跑一遍`dp`，求出另一个方向的最长路径的同时求出答案。

答案是，在求另一个方向的最长路径的同时，枚举一下入边。如果存在一条边`<r,l>`，`r`是反向的，`l`是正向的，则更新答案`ans`为`max(ans,dp[r]+dp[l])`。

时间复杂度稳定$\Theta(n+m)$。

附AC代码：

```cpp
#include <queue>
#include <cstdio>
using namespace std;

inline void chkmax(int& a,int b)
{
	if(a<b)
	{
		a = b;
	}
}

inline void chkmin(int& a,int b)
{
	if(b<a)
	{
		a = b;
	}
}

int beg[100005];
int rbeg[100005];
int cbeg[100005];
int rcbeg[100005];
int ed[400005];
int nxt[400005];
int top;

void addedge(int* beg,int a,int b)
{
	++top;
	ed[top] = b;
	nxt[top] = beg[a];
	beg[a] = top;
}

int lvis[100005];
int rvis[100005];

void lvvs(int x)
{
	lvis[x] = 1;
	for(int p=beg[x]; p; p=nxt[p])
	{
		if(!lvis[ed[p]])
		{
			lvvs(ed[p]);
		}
	}
}

void rvvs(int x)
{
	rvis[x] = 1;
	for(int p=rbeg[x]; p; p=nxt[p])
	{
		if(!rvis[ed[p]])
		{
			rvvs(ed[p]);
		}
	}
}

int ci[100005];
int dfn[100005];
int low[100005];
int stk[100005];
int ins[100005];
int stktop;
int dfntop;
int ctop;

void tarjan(int x)
{
	++stktop;
	++dfntop;
	low[x] = dfn[x] = dfntop;
	stk[stktop] = x;
	ins[x] = 1;
	
	for(int p=beg[x]; p; p=nxt[p])
	{
		if(!dfn[ed[p]])
		{
			tarjan(ed[p]);
			chkmin(low[x],low[ed[p]]);
		}
		else
		{
			if(ins[ed[p]])
			{
				chkmin(low[x],low[ed[p]]);
			}
		}
	}
	
	if(low[x]==dfn[x])
	{
		++ctop;
		while(stk[stktop]!=x)
		{
			ci[stk[stktop]] = ctop;
			ins[stk[stktop]] = 0;
			--stktop;
		}
		ci[x] = ctop;
		ins[x] = 0;
		--stktop;
	}
}

int mi[100005];
int ind[100005];
int rind[100005];
int dp[100005];

int clvis[100005];
int crvis[100005];

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; ++i)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		addedge(beg,a,b);
		addedge(rbeg,b,a); 
	}
	
	lvvs(1);
	rvvs(1);
	
	for(int i=1; i<=n; ++i)
	{
		if(!dfn[i])
		{
			tarjan(i);
		}
	}
	
	for(int i=1; i<=n; ++i)
	{
		++mi[ci[i]];
		clvis[ci[i]] = clvis[ci[i]]||lvis[i];
		crvis[ci[i]] = crvis[ci[i]]||rvis[i];
	}
	
	for(int i=1; i<=n; ++i)
	{
		for(int p=rbeg[i]; p; p=nxt[p])
		{
			if(ci[ed[p]]!=ci[i])
			{
				addedge(rcbeg,ci[i],ci[ed[p]]);
				
				if(rvis[i])
				{
					++rind[ci[ed[p]]];
				}
			}
		}
		for(int p=beg[i]; p; p=nxt[p])
		{
			if(ci[ed[p]]!=ci[i])
			{
				addedge(cbeg,ci[i],ci[ed[p]]);
				
				if(lvis[i])
				{
					++ind[ci[ed[p]]];
				}
			}
		}
	}
	
	queue<int> q;
	q.push(ci[1]);
	
	while(!q.empty())
	{
		int th = q.front();
		q.pop();
		
		dp[th] += mi[th];
		
		for(int p=rcbeg[th]; p; p=nxt[p])
		{
			if(crvis[ed[p]])
			{
				--rind[ed[p]];
				chkmax(dp[ed[p]],dp[th]);
			
				if(!rind[ed[p]])
				{
					q.push(ed[p]);
				}
			}
		}
	}
	
	q.push(ci[1]);
	dp[ci[1]] -= mi[ci[1]]; //防止起点被重复算
	
	int ans = mi[ci[1]]<<1;
	while(!q.empty())
	{
		int th = q.front();
		q.pop();
		
		dp[th] += mi[th];
		
		for(int p=rcbeg[th]; p; p=nxt[p])
		{
			if(crvis[ed[p]] && dp[ed[p]])
			{
				chkmax(ans,dp[ed[p]]+dp[th]);
			}
		}
		for(int p=cbeg[th]; p; p=nxt[p])
		{
			if(clvis[ed[p]])
			{
				--ind[ed[p]];
				chkmax(dp[ed[p]],dp[th]);
			
				if(!ind[ed[p]])
				{
					q.push(ed[p]);
				}
			}
		}
	}
	
	printf("%d\n",ans-mi[ci[1]]); //起点被重复算了所以要减去
}
```

---

## 作者：GoldenPotato137 (赞：5)

蒟蒻博客传送门：[QAQ](https://www.cnblogs.com/GoldenPotato/p/9168356.html)



------------


### Solution


这题显然要先把缩点做了。

然后我们就可以考虑如何处理走反向边的问题。

像我这样的蒟蒻，当然是使用搜索，带记忆化的那种（滑稽）。

 .
 
 .
 

**考虑设f(i,j)表示到达第i个点，还能走j次反向边，所能到达的最多的点的数量。**

转移可以表示为：

![QAQ](https://cdn.luogu.com.cn/upload/pic/20957.png)

**如果x能到达1所在的强连通分量或max出来的值不为0，说明当前状态可行，否则不可行。**

.

.

 

然后用记忆化搜索表达出来就OK了


------------
### Solution
```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<stack>
#include<cstring>
using namespace std;
long long read()
{
    long long x=0,f=1; char c=getchar();
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)){x=x*10+c-'0';c=getchar();}
    return x*f;
}
const int N=100000+100;
struct road
{
    int to,IsBack;
    road (int A,int B)
    {
        to=A,IsBack=B;
    }
};
vector <int> e[N];
vector <road> e2[N];
int belong[N],nd_tot,nd_to,low[N],dfn[N],InStack[N],cnt[N];
stack <int> st;
void Tarjan(int now)
{
    low[now]=dfn[now]=++nd_to;
    InStack[now]=true;
    st.push(now);
    for(int i=0;i<int(e[now].size());i++)
        if(dfn[e[now][i]]==0)
        {
            Tarjan(e[now][i]);
            low[now]=min(low[now],low[e[now][i]]);
        }
        else if(InStack[e[now][i]]==true)
            low[now]=min(low[now],low[e[now][i]]);
    if(low[now]==dfn[now])
    {
        nd_tot++;
        while(st.empty()==false)
        {
            int temp=st.top();
            st.pop();
            belong[temp]=nd_tot;
            InStack[temp]=false;
            cnt[nd_tot]++;
            if(temp==now)
                break;
        }
    }
}
int n,m,S,f[N][2];
int dfs(int now,int back)
{
    if(f[now][back]>=0) return f[now][back];
    int t_ans=0;
    bool OK=false;
    for(int i=0;i<int(e2[now].size());i++)
        if(e2[now][i].to!=S and back-e2[now][i].IsBack>=0)
            t_ans=max(t_ans,dfs(e2[now][i].to,back-e2[now][i].IsBack));
        else if(back>=e2[now][i].IsBack)
            OK=true;
    if(t_ans!=0 or OK==true)
        return f[now][back]=t_ans+cnt[now];
    else
        return f[now][back]=0;
}
int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++)
        e[i].reserve(4),
        e2[i].reserve(4);
    for(int i=1;i<=m;i++)
    {
        int s=read(),t=read();
        e[s].push_back(t);
    }
    
    for(int i=1;i<=n;i++)
        if(dfn[i]==0)
            Tarjan(i);
    S=belong[1];
    for(int i=1;i<=n;i++)
        for(int j=0;j<int(e[i].size());j++)
            if(belong[i]!=belong[e[i][j]])
            {
                e2[belong[i]].push_back(road(belong[e[i][j]],0));
                e2[belong[e[i][j]]].push_back(road(belong[i],1));
            }
    
    memset(f,0x80,sizeof f);
    int ans=0;
    for(int i=0;i<int(e2[S].size());i++)
        ans=max(ans,dfs(e2[S][i].to,1-e2[S][i].IsBack));
    
    printf("%d",ans+cnt[S]);
    return 0;
}

```

---

## 作者：George1123 (赞：3)

[${\color{orange}\text{欢迎拜访我这个蒟蒻的博客}}$](https://www.luogu.org/blog/wzc-wwwwd/)

[P3119 【\[USACO15JAN\]草鉴定Grass Cownoisseur】](https://www.luogu.org/problem/P3119)

### 此题算法:tarjan缩点+图论(?)

大致思路:

>1.$ $输入有向边并存图。tarjan缩点。

```cpp
struct graph{
	edge e[N];
	int g[N],top,dis[N];
	void add(int x,int y){
		e[++top]=(edge){
			y,g[x]
		}; g[x]=top;
	} 
} ori,tos,opp;
```
    上代码中三个图分别表示原图(ori)，缩图(tos)，缩图的反图(opp)

>2.$ $建缩图及缩图的反图。分别spfa就可以得出以节点$1$所在的强连通分量为起点和终点的最长路。


(样例 by mspaint)
![](https://s2.ax1x.com/2019/10/06/u6dYmF.jpg)

>3.$ $ 将答案$ans$的初始值置为节点$1$所在的强连通分量的点数。

>4.$ $让$ans$等于所有的强连通分量$i$和与它连着的强连通分量$to$的${tos.dis[i]+opp.dis[to]}$的最大值$-$节点$1$所在的强连通分量的点数($i$和$to$之间的那条边就是反边)。

>5.$ $最后$ans$就是题目的答案。

## 以下是代码+注释

```cpp
//Libra
#include <bits/stdc++.h>
using namespace std;
const int N=1e5;
int n,m,ans;
struct edge{
	int adj,nex;
};
struct graph{
	edge e[N];
	int g[N],top,dis[N];
	void add(int x,int y){
		e[++top]=(edge){
			y,g[x]
		}; g[x]=top;
	} //复杂但清晰的建图
} ori,tos,opp;
int ind,dfn[N],low[N];
int cnt,col[N],sum[N];
bool in[N],use[N];
stack<int> st;
void tarjan(int x){ //缩点的代码
	dfn[x]=low[x]=++ind;
	st.push(x); in[x]=1;
	for(int i=ori.g[x];i;i=ori.e[i].nex){ //如果tarjan死循环了，这里的e[i].nex很可能写成e[x].nex了
		int to=ori.e[i].adj;
		if(!dfn[to]){
			tarjan(to);
			low[x]=min(low[x],low[to]);
		} else if(in[to])
			low[x]=min(low[x],dfn[to]);
	} if(dfn[x]==low[x]){
		int tmp=0; cnt++;
		while(tmp!=x){
			tmp=st.top(); st.pop();
			col[tmp]=cnt;
			in[tmp]=0;
			sum[cnt]++;
		}
	}
} void spfa(int set,graph &gr){ //spfa，别忘了把gr的地址带进去
	gr.dis[set]=sum[set];
	queue<int> q; q.push(set);
	while(!q.empty()){
		int now=q.front(); q.pop();
		for(int i=gr.g[now];
		i;i=gr.e[i].nex){
			int to=gr.e[i].adj;
			if(gr.dis[to]<gr.
			dis[now]+sum[to]){
				gr.dis[to]=gr.
				dis[now]+sum[to];
				if(!use[to]){
					q.push(to);
					use[to]=1;
				}
			}
		} use[now]=0;
	}
} int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		ori.add(a,b);
	} for(int i=1;i<=n;i++)
		if(!dfn[i])
			tarjan(i);
	for(int i=1;i<=n;i++)
		for(int j=ori.g[i];
		j;j=ori.e[j].nex){
			int to=ori.e[j].adj;
			if(col[i]!=col[to]){
				tos.add(col[i],col[to]); //缩图
				opp.add(col[to],col[i]); //↑的反图
			}
		}
	spfa(col[1],tos); spfa(col[1],opp); //一个spfa解决俩
	ans=sum[col[1]]; //ans的初始值
	for(int i=1;i<=cnt;i++){
		if(!use[i]&&tos.dis[i]){
			use[i]=1;
			for(int j=opp.g[i];
			j;j=opp.e[j].nex){
				int to=opp.e[j].adj;
				if(!opp.dis[to])
					continue;
				ans=max(ans,tos.dis[i]
				+opp.dis[to]-sum[col[1]]); //求最大ans
			}
		}
	} printf("%d\n",ans);
	return 0;
}
```

不看spfa和tarjan代码还挺短。

谢谢大家! !




---

## 作者：SuperGoodGame (赞：3)

全当纪念下 ，

------------

考虑当不能反转一条边时 ， 奶牛最多能到达的点就是它所在的强联通分量大小 ， 那么反转一条边后 ， 我们就有**一次机会走出它本身的强联通分量然后通过反转某条边回来** ， 

然后做法比较显然 ，缩点后枚举每条边 ， 如果这条边连接的两个强联通分量一个是**可以到达 1号点**（所在的强联通分量） 的 ， 一个是可以**被 1 号点（所在的强联通分量）到达的** ， 那么我们就可以通过反转这条边让奶牛从 1 号点然后走回到 1 号点

------------
预处理出哪些点 可以到达1 ， 和哪些点可以被1 到达 ， 和到达的最远距离

预处理的复杂度应该是 $O(m)$ 

统计答案 $O(m)$ 枚举边即可

预处理的时候细节还是要注意下，比如说要取个max

统计答案时注意能到达和不能到达的强联通分量的标记方法 ， 恩调了很长时间发现自己这个地方出现了漏洞QAQ

```
// luogu-judger-enable-o2
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>

using namespace std;

#define re register
#define Rep(i,l,r) for(re int i=l;i<=r;++i)
#define N 100005

struct node{
    int v,nxt;
}e[N] , E[N][2];
int n,m,ans=-1;
int head[N] , tot;
inline void add(int u,int v){
    e[++tot]=(node){v,head[u]};
    head[u]=tot;
}
int Head[N][2] , Tot[2];
inline void Add(int u,int v,int i){
    E[++Tot[i]][i]=(node){v,Head[u][i]};
    Head[u][i]=Tot[i];
}

int dfn[N] , low[N] , col[N] , val[N] , vis[N];
int ColNum , DfsNum;
stack <int> s;
inline void paint (int u){
    vis[u]=0 , s.pop();
    col[u]=ColNum;
    val[ColNum]++;
}
void Tarjan(int u){
    low[u]=dfn[u]=++DfsNum;
    vis[u]=1 , s.push(u);
    for(re int i=head[u];i;i=e[i].nxt){
        int v=e[i].v;
        if(!dfn[v]) Tarjan(v) , low[u]=min(low[v] , low[u]);
        else if(vis[v]) low[u]=min(low[u] , dfn[v]);
    }
    if(low[u]==dfn[u]) {
        ColNum++;
        while(s.top()!=u)
            paint(s.top());
        paint(u);
    }
}
int mark[N] , f[N][2];
void dfs(int u,int x){
    for(re int i=Head[u][x];i;i=E[i][x].nxt){
        int v=E[i][x].v;
        f[v][x]=max(f[v][x] , f[u][x]+val[v]);
        dfs(v,x);
        mark[v]=x+1;
    }
}
int main() {
    //freopen("read.in","r",stdin);
    //freopen("WA.out","w",stdout);
    scanf("%d%d",&n,&m);
    Rep(i,1,m){
        re int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);
    }
    Rep(i,1,n) if(!dfn[i]) Tarjan(i);
    Rep(u,1,n)
        for(re int i=head[u];i;i=e[i].nxt)
            if(col[u]!=col[e[i].v])
                Add(col[u] , col[e[i].v],0) , Add(col[e[i].v] , col[u] , 1);
    f[col[1]][0]=f[col[1]][1]=val[col[1]] , dfs(col[1],0) , dfs(col[1],1) , ans=val[col[1]];
    Rep(u,1,ColNum)
        for(re int i=Head[u][1];i;i=E[i][1].nxt)
        	if( f[u][0] && f[E[i][1].v][1] )
       			ans=max(ans,f[u][0]+f[E[i][1].v][1]-val[col[1]]);
    cout<<ans;
    return 0;
}
```
$mark$ 数组并不好用QAQ

---

## 作者：1saunoya (赞：3)

$\texttt{强连通分量 + 最短路的裸题}$

对于这一题 简化一下模型:从 1 处出发 然后去吃草 最后回到1 问你最多能吃多少草

~~对于逆行啥玩意先不管 放这儿~~

显而易见这是个缩点就可以做到的东西 

缩点之后重构一个图 对于最短路出发再回来的方法是建反向边



这题其实求的是最长路 我们可以像树剖一样把点转成边 然后再搞掉一个点的贡献

~~~
inline void Tarjan(int u) {
	dfn[u] = low[u] = ++ tot ;//时间戳
	s[++ top] = u , used[u] = 1 ;
	for(register int i = _head[u] ; i ; i = _e[i].nxt) {
		int v = _e[i].v ;
		if(! dfn[v]) {
			Tarjan(v) ;
			low[u] = min(low[u] , low[v]) ;
		}
		else if(used[v]) low[u] = min(low[u] , dfn[v]) ;
	}
	if(low[u] == dfn[u]) {
		t[co[u] = ++ num] ++ ;//num表示的是第几个强连通分量
		used[u] = 0 ;
		while(s[top] ^ u) {// ^ 相当于 !=
			used[s[top]] = 0 ;//打消标记
			t[co[s[top --]] = num] ++ ;//t是当前的强连通分量里有几个点
		}
		top -- ;// 对于 u 这个节点也需要放进去 因为 u 也是强连通分量的一部分
	}
}
~~~


~~~
for(register int i = 1 ; i <= n ; i ++) 
		for(register int j = _head[i] ; j ; j = _e[j].nxt) {
			int v = _e[j].v ;
			if(co[i] ^ co[v]) {
				From.Add(co[i] , co[v]) ;
				Back.Add(co[v] , co[i]) ;
			}
		}
~~~

建图的办法 由于我太懒了懒得写两个Add两个Spfa ~~其实是我懒得复制粘贴而且还可能出锅~~

然后跑$Spfa$就可以了


对于逆行。。 你只需要选倒着的边 也就是反向边 这样就可以做到逆行~~恶意逆行罚款200~~

~~~
for(register int i = 1 ; i <= n ; i ++) 
		if(! used[co[i]] && From.dis[co[i]]) {
			int u = co[i] ;
			used[u] = 1 ;
			for(register int j = Back.head[u] ; j ; j = Back.e[j].nxt) {
				int v = Back.e[j].v ;
				if(! Back.dis[v]) continue ;
				ans = max(ans , From.dis[u] + Back.dis[v] - t[start]) ;
//				cout << From.dis[u] + Back.dis[v] - t[start] << endl ;
			}
		}
~~~


$\mathcal Code$


```cpp
//Isaunoya
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std ;
inline int read() {
	register int x = 0 ;
	register int f = 1 ;
	register char c = getchar() ;
	for( ; ! isdigit(c) ; c = getchar()) if(c == '-') f = -1 ;
	for( ; isdigit(c) ; c = getchar()) x = (x << 1) + (x << 3) + (c & 15) ;
	return x * f ;
}
int st[105] ;
template < typename T > inline void write(T x , char c = '\n') {
	int tp = 0 ;
	if(x == 0) return (void) puts("0") ;
	if(x < 0) putchar('-') , x = -x ;
	for( ; x ; x /= 10) st[++ tp] = x % 10 ;
	for( ; tp ; tp --) putchar(st[tp] + '0') ;
	putchar(c) ;
}
//#define Online_Judge

int n , m ;
const int N = 1e5 + 5 ;
struct Edge {
	int v , nxt ;
};
Edge _e[N << 1] ;
int _head[N] ;
int _cnt = 0 ;
inline void Add(int u , int v) {
	_e[ ++ _cnt ].v = v ;
	_e[ _cnt ].nxt = _head[u] ;
	_head[u] = _cnt ;
	return ;
}
int dfn[N] , low[N] , tot = 0 , num = 0 , s[N] ;
int top = 0 ; int co[N] ;
int t[N] ; int used[N] ;
inline void Tarjan(int u) {
	dfn[u] = low[u] = ++ tot ;
	s[++ top] = u , used[u] = 1 ;
	for(register int i = _head[u] ; i ; i = _e[i].nxt) {
		int v = _e[i].v ;
		if(! dfn[v]) {
			Tarjan(v) ;
			low[u] = min(low[u] , low[v]) ;
		}
		else if(used[v]) low[u] = min(low[u] , dfn[v]) ;
	}
	if(low[u] == dfn[u]) {
		t[co[u] = ++ num] ++ ;
		used[u] = 0 ;
		while(s[top] ^ u) {
			used[s[top]] = 0 ;
			t[co[s[top --]] = num] ++ ;
		}
		top -- ;
	}
}
class T {
	public :
		struct node {
			int v , nxt ;
		};
		int cnt = 0 ;
		node e[N << 1] ;
		int head[N] ;
		inline void Add(int u , int v) {
			e[ ++ cnt ].v = v ;
			e[ cnt ].nxt = head[u] ;
			head[u] = cnt ;
			return ;
		}
		int dis[N] ;
		bool vis[N] ;
		inline void Spfa(int s) {
			queue < int > q ;
			dis[s] = t[s] ;
			q.push(s) ;
			while(q.size()) {
				int u = q.front() ;
				vis[u] = 0 , q.pop() ;
				for(register int i = head[u] ; i ; i = e[i].nxt) {
					int v = e[i].v ;
					if(dis[u] + t[v] > dis[v]) {
						dis[v] = dis[u] + t[v] ;
						if(! vis[v]) {
							vis[v] = 1 ;
							q.push(v) ;
						}
					}
				}
			}
		}
} From , Back ;
signed main() {
#ifdef Online_Judge
	freopen("testdata.in" , "r" , stdin) ;
	freopen("testdata2.out" , "w" , stdout) ;
#endif
	n = read() ;
	m = read() ;
	for(register int  i = 1 ; i <= m  ; i ++) {
		int u = read() , v = read() ;
		Add(u , v) ;
	}
	for(register int i = 1 ; i <= n ; i ++) 
		if(! dfn[i]) Tarjan(i) ;
	for(register int i = 1 ; i <= n ; i ++) 
		for(register int j = _head[i] ; j ; j = _e[j].nxt) {
			int v = _e[j].v ;
			if(co[i] ^ co[v]) {
				From.Add(co[i] , co[v]) ;
				Back.Add(co[v] , co[i]) ;
			}
		}
	int start = co[1] ;
	From.Spfa(start) , Back.Spfa(start) ;
	int ans = t[start] ;
	for(register int i = 1 ; i <= n ; i ++) 
		if(! used[co[i]] && From.dis[co[i]]) {
			int u = co[i] ;
			used[u] = 1 ;
			for(register int j = Back.head[u] ; j ; j = Back.e[j].nxt) {
				int v = Back.e[j].v ;
				if(! Back.dis[v]) continue ;
				ans = max(ans , From.dis[u] + Back.dis[v] - t[start]) ;
//				cout << From.dis[u] + Back.dis[v] - t[start] << endl ;
			}
		}
	write(ans) ;
	return 0 ;
}
```

---

## 作者：walk_alone (赞：3)

这个题先tarjan加缩点不解释  
（先放上缩点模板P3387的代码）  
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
struct line
{
    int from;
    int to;
    int next;
};
line que[100001];
int headers[100001],cnt,dfn[100001],st[100001],low[100001],siz[100001],color[100001],tot,book[100001],value[100001],f[100001],num,index;
void add(int from,int to)
{
    cnt++;
    que[cnt].from=from;
    que[cnt].to=to;
    que[cnt].next=headers[from];
    headers[from]=cnt;
}
void tarjan(int u)
{
    dfn[u]=low[u]=++index;
    st[++tot]=u;
	book[u]=1;
    for(int i=headers[u];i;i=que[i].next)
        if(!dfn[que[i].to])
        {
            tarjan(que[i].to);
            low[u]=min(low[u],low[que[i].to]);
        }
        else
            if(book[que[i].to])
                low[u]=min(dfn[que[i].to],low[u]);
    if(low[u]==dfn[u])
    {
        num++;
        while(st[tot+1]!=u)
        {
            color[st[tot]]=num;
            siz[num]+=value[st[tot]];
            book[st[tot]]=0;
            tot--;
        }
    }
}
void search(int x)
{
    if(f[x])
		return;
    f[x]=siz[x];
    int maxsum=0;
    for(int i=headers[x];i;i=que[i].next)
	{
        if(!f[que[i].to])
			search(que[i].to);
        maxsum=max(maxsum,f[que[i].to]);
    }
    f[x]+=maxsum;
}
int main()
{
    int n,m,a,b;
    scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&value[i]);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&a,&b);
        add(a,b);
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            tarjan(i);
    for(int i=1;i<=cnt;i++)
        que[i].next=0;
    for(int i=1;i<=n;i++)
        headers[i]=0;
    int used=cnt;
    cnt=1;
    for(int i=1;i<=used;i++)
        if(color[que[i].from]!=color[que[i].to])
        {
            que[cnt].from=color[que[i].from];
            que[cnt].to=color[que[i].to];
            que[cnt].next=headers[color[que[i].from]];
            headers[color[que[i].from]]=cnt;
            cnt++;
        }
        else
            que[i].from=que[i].to=0;
	cnt--;
	int ans=0;
	for(int i=1;i<=num;i++)
        if(!f[i])
		{
            search(i);
            ans=max(ans,f[i]);
        }
	printf("%d",ans);
    return 0;
}

```  
缩点之后，我们可以先用缩点后原图跑一遍bfs然后再建反图再跑一遍bfs，来找出1所在联通块能到达的所有联通块，和能到达1所在的联通块的所有联通块。  
现在来证明一下：  
&emsp;&emsp;我们考虑一下DAG中的一个基本单元，有三条边，1->u,1->v,u->v  
&emsp;&emsp;因为只能走一次反边，所以我们可以将边u->v反走，这个时候我们就可以沿着1->v->u->1回到1（当然其实每一条边反走都行，但是为了方便我们就这样走）  
所以我们使用bfs我们就可以找到我们可不走反边就经过的点集合$u$和其最长路，建反图找到不走反边经过最多点回到1的点集合$v$和其最长路。而答案就是$max(dis[u][1],dis[v][2])$(令$dis[i][1]$是1到$i$的最长路，$dis[i][2]$是$i$到1的最长路)  
代码入下  
```cpp
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
struct line
{
    int from;
    int to;
    int next;
};
line que[100001];//就是你们习惯的edge，当年习惯没养好
int headers[100001],cnt,dfn[100001],st[100001],low[100001],siz[100001],color[100001],tot,book[100001],num,index;//color：记录每个点所在联通块。siz：记录每个联通块的大小。num:记录联通块的编号
int reach[100001][3];
void add(int from,int to)
{
    cnt++;
    que[cnt].from=from;
    que[cnt].to=to;
    que[cnt].next=headers[from];
    headers[from]=cnt;
}
void tarjan(int u)
{
    dfn[u]=low[u]=++index;
    st[++tot]=u;
    book[u]=1;
    for(int i=headers[u];i;i=que[i].next)
        if(!dfn[que[i].to])
        {
            tarjan(que[i].to);
            low[u]=min(low[u],low[que[i].to]);
        }
        else
            if(book[que[i].to])
                low[u]=min(dfn[que[i].to],low[u]);
    if(low[u]==dfn[u])
    {
        num++;
        while(st[tot+1]!=u)
        {
            color[st[tot]]=num;
            siz[num]++;
            book[st[tot]]=0;
            tot--;
        }
    }
}
void bfs(int s,int times)//times就是判定正向还是反向
{
    queue<int>q;
    q.push(s);
    reach[s][times]=0;
    while(!q.empty())
    {
        int t=q.front();
        q.pop();
        for(int i=headers[t];i;i=que[i].next)
            if(reach[que[i].to][times]<reach[t][times]+siz[que[i].to])//从100分变成7分的原因。同时附上一组hack数据：6 8 1 2 2 5 5 6 6 2 1 3 2 4 3 4 1 4 答案：5
            {
                reach[que[i].to][times]=reach[t][times]+siz[que[i].to];//reach[i][1]就是dis[i][1],reach[i][2]同理
                q.push(que[i].to);
            }
    }
}
int main()
{
    int n,m,a,b;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&a,&b);
        add(a,b);
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            tarjan(i);
    for(int i=1;i<=cnt;i++)
        que[i].next=0;
    for(int i=1;i<=n;i++)
        headers[i]=0;
    int used=cnt;
    cnt=0;
    for(int i=1;i<=used;i++)
        if(color[que[i].from]!=color[que[i].to])
        {
            cnt++;
            que[cnt].from=color[que[i].from];
            que[cnt].to=color[que[i].to];
            que[cnt].next=headers[que[cnt].from];
            headers[que[cnt].from]=cnt;
        }
        else
            que[i].from=que[i].to=0;//以上都是tarjan加缩点
    bfs(color[1],1);//第一次bfs，找到u集合
	//建反图，即把每条边反过来
    for(int i=1;i<=cnt;i++)
        que[i].next=0;
    for(int i=1;i<=n;i++)
        headers[i]=0;
    for(int i=1;i<=cnt;i++)
    {
        swap(que[i].from,que[i].to);
        que[i].next=headers[que[i].from];
        headers[que[i].from]=i;
    }
    bfs(color[1],2);	//第二次bfs，找到v集合
    int ans=0;
    for(int i=1;i<=cnt;i++)
        if((reach[que[i].from][1] || que[i].from==color[1]) && (reach[que[i].to][2] || que[i].to==color[1]))//这个地方反过来的原因：现有的图是反图，所以边的入和出也要反过来
            ans=max(ans,reach[que[i].from][1]+reach[que[i].to][2]);
    printf("%d",ans+siz[color[1]]);
    return 0;
}

```

---

## 作者：Katoumegumi (赞：1)

之前做的一道题,今天想起来好像没在洛谷交,于是跑回来交顺便写篇题解.

~~主要是看到已有的题解好像有一定错误~~

------------
这道题说实话,越看题解越会感觉鬼畜,觉得各种"建图鬼畜","思维鬼畜",诸如此类.实际上,这道题的思路还是很清晰的,下面分享一波解题过程(＾0＾)┛;


拿到题目一看到单向边,很自然就会想到是否会用$Tarjan$缩点,如果用的话能否真正在本题中起到作用;分析一下之后,容易得出,缩点之后的一团的权值就是之前到这几个点得到的点权之和(强连通分量中任意两点互相可达),所以要用$,,,$然后图就建好了$......$


然后我们~~这时候~~开始思考题目要我们解决的问题,显然这个逆行一次是略有点恶心的.先不考虑这个恶心的选择的话,我们只考虑从起点如果**不逆行**可以得到的最大$Ans$.显然这个答案可以在我们新图上正一边最长路即可.


但接下来我们仍需处理这一次逆行的问题.我们考虑,我们现在正站在举例起点最远的点,我们可以逆行一条路回到起点,这可咋整?

选择与当前点相连的并且可以一路回到起点的那条边就行啦!

$ans=max(ans,(ll)(dis[i][1]+dis[p][0]))$


画个图这种思路还是很显然的啦!

顺便说一句,$ans$的初值一定要赋值为起点所在强连通分量的权值,否则当这个图整个就是个环,你的答案就是一个莫名其妙的值啦!

~~自己试试去卡其他题解吧~~

$code:$
```c++
#include<stdio.h>
#include<string.h>
#include<stack>
#include<algorithm>
#include<ctype.h>
#include<vector>
#include<queue>
#define ll long long
#define inf 1e9+9
using namespace std;

char buf[1<<20],*p1,*p2;
inline char gc() {
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin))==p1?0:*p1++;
}

template<typename T>
inline void read(T &x) {
    char tt;
    bool flag=0;
    while(!isdigit(tt=gc())&&tt!='-');
    tt=='-'?(flag=1,x=0):(x=tt-'0');
    while(isdigit(tt=gc())) x=x*10+tt-'0';
    flag?x=-x:x=x;
}

struct node {
    int x,len;
    inline node(int a=0,int b=0) {
        x=a;
        len=b;
    }
    bool operator<(node a)const {
        return len<a.len;
    }
};

int n,m,tot,scc,belong[100005],sz[100005];
ll dis[100005][2];
bool instack[100005];
vector<int>G[100005];
vector<node>g[100005][2];
stack<int>s;
int low[100005],dfn[100005];
priority_queue<node>q;

void djs(int start,int t) {
    for(int i=1; i<=scc; i++) dis[i][t]=-inf;
    dis[start][t]=(t==1)?sz[start]:0;
    q.push(node(start,dis[start][t]));
    while(!q.empty()) {
        int x=q.top().x;
        int len=q.top().len;
        q.pop();

        if(len!=dis[x][t]) continue;
        for(int i=g[x][t].size()-1; i>=0; i--) {
            int p=g[x][t][i].x;
            len=g[x][t][i].len;
            if(dis[p][t]>=dis[x][t]+len) continue;
            dis[p][t]=(ll)dis[x][t]+len;
            q.push(node(p,dis[p][t]));
        }
    }
}

void dfs(int x) {
    low[x]=dfn[x]=++tot;
    s.push(x),instack[x]=1;
    int p;
    for(int i=G[x].size()-1; i>=0; i--) {
        int p=G[x][i];
        if(!dfn[p]) {
            dfs(p);
            low[x]=min(low[x],low[p]);
        } else if(dfn[p]&&instack[p]) {
            low[x]=min(low[x],low[p]);
        }
    }
    if(low[x]==dfn[x]) {
        scc++;
        do {
            p=s.top();
            s.pop();
            instack[p]=0;
            belong[p]=scc;
            sz[scc]++;
        } while(x!=p);
    }
}

ll ans;
int main() {
    read(n),read(m);
    for(int i=1; i<=m; i++) {
        int x,y;
        read(x),read(y);
        G[x].push_back(y);
    }
    for(int i=1; i<=n; i++) if(!dfn[i]) dfs(i);
    for(int i=1; i<=n; i++)
        for(int j=G[i].size()-1; j>=0; j--) {
            int p=G[i][j];
            if(belong[i]==belong[p]) continue;
            g[belong[i]][1].push_back(node(belong[p],sz[belong[p]]));
            g[belong[p]][0].push_back(node(belong[i],sz[belong[i]]));
        }

    djs(belong[1],0);
    djs(belong[1],1);
    
    ans=sz[belong[1]];
    int start=belong[1];
    for(int i=1; i<=scc; i++) {
        for(int j=g[i][0].size()-1; j>=0; j--) {
            int p=g[i][0][j].x;
            ans=max(ans,(ll)(dis[i][1]+dis[p][0]));
        }
    }
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：asuldb (赞：1)

这大概是我写过的除了树剖以外最长的代码了吧

首先看到有向图和重复经过等敏感词应该能想到先tarjan后缩点了吧

首先有一个naive的想法，既然我们要求只能走一次返回原点，那我们就正着反着建两遍图，分别处理出1到其他点的所能经过的最多点数和其他点到1经过的最大点数，之后找到那些和1有正边或反边相连的点，之后逆行这一条边，取一个max就好了

于是洋洋洒洒写了100多行发现连样例都过不了

本着交一交试试看的心态交了上去，发现还能过四个点

于是就去手画了一遍样例，发现自己真的是非常naive

样例是这个样子的

![样例](https://cdn.luogu.com.cn/upload/pic/21842.png)

尽管很丑，但就勉强看看吧

我们发现按照刚才那个思路我们显然是要挂的

因为按照那样跑出来的结果是4，但这里的最佳方案应该是从1到那个缩好的点再到5，之后逆行一次走到3，之后走回1

这样我们如果只考虑能到到1的或只考虑能被1到达的，显然是不行的

这样不行怎么办，我们放到一起考虑就好了

如果一个能被1到达的点（比如说样例里的5）有一条边（当然这是一条反边）能到达一个能到达1的点，我们就可以把这两种情况一起考虑

同理一个能到达1的点有一条边（自然这是一条正边）和一个能被1到达的点相连，这两种情况也可以一起考虑

所以就是代码了
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<bitset>
#define re register
#define maxn 100001
using namespace std;
struct node
{
	int v,nxt;
}e[maxn],e1[maxn],e2[maxn];
int head[maxn],head1[maxn],head2[maxn];
int dfn[maxn],low[maxn],st[maxn],belong[maxn],dp1[maxn],d[maxn],dp2[maxn];
int f1[maxn],f2[maxn];
int q[maxn],r[maxn],c[maxn];
bitset<maxn> f;//闲的没事干开了bitset
int n,m,top,k,p,num,num1,num2,mid;
inline void add_edge(int x,int y)
{
	e[++num].v=y;
	e[num].nxt=head[x];
	head[x]=num;
}//原图
inline void add_edge_1(int x,int y)
{
	e1[++num1].v=y;
	e1[num1].nxt=head1[x];
	head1[x]=num1;
}//缩点后新图建正边
inline void add_edge_2(int x,int y)
{
	e2[++num2].v=y;
	e2[num2].nxt=head2[x];
	head2[x]=num2;
}//缩点后新图建反边
inline int read()
{
	char c=getchar();
	int x=0;
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9')
	  x=(x<<3)+(x<<1)+c-48,c=getchar();
	return x;
}
void tarjan(int x)
{
	dfn[x]=low[x]=++k;
	f[x]=1;
	st[++top]=x;
	for(re int i=head[x];i;i=e[i].nxt)
	if(!dfn[e[i].v]) tarjan(e[i].v),low[x]=min(low[x],low[e[i].v]);
	else if(f[e[i].v]) low[x]=min(low[x],dfn[e[i].v]);
	if(dfn[x]==low[x])
	{
		p++;
		do
		{
			mid=st[top--];
			f[mid]=0;
			d[p]++;//记录新点点权
			belong[mid]=p;//记录好每一个点属于哪一个缩完点后的新点
		}while(x!=mid);
	}
}
int main()
{
	n=read();
	m=read();
	int x,y;
	for(re int i=1;i<=m;i++)
	{
		x=read();
		y=read();
		add_edge(x,y);
	}
	for(re int i=1;i<=n;i++)
	if(!dfn[i]) tarjan(i);//缩点！
	for(re int i=1;i<=n;i++)
	for(re int j=head[i];j;j=e[j].nxt)
	if(belong[i]!=belong[e[j].v]) 
	{
		r[belong[e[j].v]]++,add_edge_1(belong[i],belong[e[j].v]);//建正图
		c[belong[i]]++,add_edge_2(belong[e[j].v],belong[i]);//建反图
	}
	f[belong[1]]=1;//我们开一个标记数组,标记那些点可以被1到达,拓扑排序的时候只有这些点才进行动规,其余的点只做删边操作
	dp1[belong[1]]=d[belong[1]];
	int tot=0;
	for(re int i=1;i<=p;i++)
	if(!r[i]) q[++tot]=i;
	for(re int i=1;i<=tot;i++)
	{
		for(re int j=head1[q[i]];j;j=e1[j].nxt)
		{
			r[e1[j].v]--;
			if(f[q[i]])
			{
				f[e1[j].v]=1;
				dp1[e1[j].v]=max(dp1[e1[j].v],dp1[q[i]]+d[e1[j].v]);
                //dp1[i]表示从1到i形成的最大点权
			}
			if(!r[e1[j].v]) q[++tot]=e1[j].v;
		}
	}
	int ans=0;
	for(re int i=head1[belong[1]];i;i=e1[i].nxt)
		ans=max(ans,dp1[e1[i].v]);
	for(re int i=1;i<=p;i++)
		f1[i]=f[i];//记录那些点可以被1到达
	tot=0;
	memset(q,0,sizeof(q));
	f.reset();//bitset清零
	f[belong[1]]=1;//标记同理，表示这个点可以到达1
	dp2[belong[1]]=d[belong[1]];
	for(re int i=1;i<=p;i++)
	if(!c[i]) q[++tot]=i;
	for(re int i=1;i<=tot;i++)
	{
		for(re int j=head2[q[i]];j;j=e2[j].nxt)
		{
			c[e2[j].v]--;
			if(f[q[i]])
			{
				f[e2[j].v]=1;
				dp2[e2[j].v]=max(dp2[e2[j].v],dp2[q[i]]+d[e2[j].v]);
                //dp2[i]表示i这个点到1形成的最大点权
			}
			if(!c[e2[j].v]) q[++tot]=e2[j].v;
		}
	}
	for(re int i=head2[belong[1]];i;i=e2[i].nxt)
		ans=max(ans,dp2[e2[i].v]);
	for(re int i=1;i<=p;i++)
		f2[i]=f[i];//记录那些点可以到达1
	for(re int i=1;i<=p;i++)
	if(f1[i])//这个点可以被1到达
	{
		for(re int j=head2[i];j;j=e2[j].nxt)//逆行一次
		if(f2[e2[j].v]) ans=max(ans,dp1[i]+dp2[e2[j].v]-d[belong[1]]);//由于两次dp都把1所在的强联通分量的点权算了进去，所以要减去一个1所在的强联通分量的点权
	}
	for(re int i=1;i<=p;i++)
	if(f2[i])
	{
		for(re int j=head1[i];j;j=e1[j].nxt)
		if(f1[e1[j].v]) ans=max(ans,dp2[i]+dp1[e1[j].v]-d[belong[1]]);
	}//同理
	ans=max(d[belong[1]],ans);//如果一谁都到达不了，谁也到不了，那么答案就是1的点权了
	printf("%d",ans);
	return 0;
}
```

---

## 作者：chihik (赞：0)

我们应该用$Tarjan$缩点，将原图变为$GAD$图，同时记录每个强连通分量的节点个数，记为$num[i]$。

因为起点终点都是1，所以路径一定是一个环。我们可以处理出1到所有点的距离，存在$dis1$中（跑正图）和所有点到1的距离存在$dis2$中（跑反图）。注意，如果走不到就设为极小值。最短路跑的是点权，其实和边权差不多。

题目说可以逆向走一条有向边，我们设该边起点为$u$，终点为$v$，那么，答案就应为$num[belong[1]]+max(dis1[v]+dis2[u])$。


```cpp
#include <cstdio>
#include <queue>
#include <stack>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 100000;
int n,m,x,y;
vector< int > Graph[ MAXN + 5 ];
stack< int > s;

int dfn[ MAXN + 5 ] , low[ MAXN + 5 ] , depth , cnt;
int belong[ MAXN + 5 ] , num[ MAXN + 5 ];
bool is[ MAXN + 5 ];

void Tarjan( int u ) {
    dfn[ u ] = low[ u ] = ++ depth;
    is[ u ] = 1 , s.push( u );
    
    int v;
    for( int i = 0 ; i < Graph[ u ].size( ) ; i ++ ) {
        v = Graph[ u ][ i ];
        if( !dfn[ v ] ) {
            Tarjan( v );
            low[ u ] = min( low[ u ] , low[ v ] );
        }
        else if( is[ v ] )
            low[ u ] = min( low[ u ] , dfn[ v ] );
    }
    if( dfn[ u ] == low[ u ] ) {
        cnt ++;
        do{
            v = s.top();
            is[ v ] = 0 , s.pop();
            belong[ v ] = cnt;
            num[ cnt ] ++;
        }while( u != v );
    }
}

struct node{
    int v,w;
    node(){}
    node( int V , int W ) {
        v = V;
        w = W;
    }
    bool operator < ( const node &x ) const {
        return w < x.w;
    }
};
vector< int > lit_Graph1[ MAXN + 5 ];
vector< int > lit_Graph2[ MAXN + 5 ]; 
int dis1[ MAXN + 5 ],dis2[ MAXN + 5 ];
bool vis[ MAXN + 5 ];
void Spfa1( int s ) {
    queue< int > Q;
    while( !Q.empty() ) Q.pop();
    for( int i = 1 ; i <= n ; i ++ ) dis1[ i ] = -0x3f3f3f3f;
    memset( vis , 0 , sizeof( vis ) );
    dis1[ s ] = 0 , vis[ s ] = 1;
    
    Q.push( s );
    while ( !Q.empty() ) {
        int u = Q.front();
        Q.pop() , vis[ u ] = 0;

        for ( int i = 0 ; i < lit_Graph1[ u ].size() ; i ++ ) {
            int v = lit_Graph1[ u ][ i ];
            if ( dis1[ v ] < dis1[ u ] + num[ v ] ) {
                dis1[ v ] = dis1[ u ] + num[ v ];
                if ( !vis[ v ] ) {
                    vis[ v ] = 1;
                    Q.push( v );
                }
            }
        }
    }
}

void Spfa2( int s ) {
    queue< int > Q;
    while( !Q.empty() ) Q.pop();
    for( int i = 1 ; i <= n ; i ++ ) dis2[ i ] = -0x3f3f3f3f;
    memset( vis , 0 , sizeof( vis ) );
    dis2[ s ] = 0 , vis[ s ] = 1;
    
    Q.push( s );
    while ( !Q.empty() ) {
        int u = Q.front();
        Q.pop() , vis[ u ] = 0;

        for ( int i = 0 ; i < lit_Graph2[ u ].size() ; i ++ ) {
            int v = lit_Graph2[ u ][ i ];
            if ( dis2[ v ] < dis2[ u ] + num[ v ] ) {
                dis2[ v ] = dis2[ u ] + num[ v ];
                if ( !vis[ v ] ) {
                    vis[ v ] = 1;
                    Q.push( v );
                }
            }
        }
    }
}


int main( ) {
    scanf("%d %d",&n,&m);
    for( int i = 1 ; i <= m ; i ++ ) {
        scanf("%d %d",&x,&y);
        Graph[ x ].push_back( y );
    }
    for( int i = 1 ; i <= n ; i ++ )
        if( !dfn[ i ] ) Tarjan( i );
    for( int i = 1 ; i <= n ; i ++ )
    {
        for( int j = 0 ; j < Graph[ i ].size( ) ; j ++ ) {
            int u = belong[ i ] , v = belong[ Graph[ i ][ j ] ];
            if( u != v ) {
                lit_Graph1[ u ].push_back( v );
                lit_Graph2[ v ].push_back( u );
            }
        }
    }
    
    
    Spfa1( belong[ 1 ] );
    Spfa2( belong[ 1 ] );
    
    int Ans = num[ belong[ 1 ] ];
    for( int i = 1 ; i <= cnt ; i ++ ) {
        for( int j = 0 ; j < lit_Graph1[ i ].size( ) ; j ++ ) {
            int u = i , v = lit_Graph1[ i ][ j ];
            Ans = max( Ans , dis1[ v ] + dis2[ u ] + num[ belong[ 1 ] ] );
        }
    }
    printf("%d\n",Ans);
    return 0;
}
```


---

## 作者：luoxin (赞：0)

本文主要是对**为什么**枚举反向边后的路径**不会有重复点**进行一个说明

首先考虑不能走反向边的答案，显示就是1号点所在强连通分量的大小，如果可以走一次反向边呢？考虑缩点，显然我们的最终答案一定是通过原有的边走到一个强连通分量$x$，然后开始枚举与$x$相连的反向边的端点$y$，并且能保证从$y$出发能够只经过原有的边可以到达1号点所在的强联通分量。![](https://cdn.luogu.com.cn/upload/pic/59338.png)
那么为什么不会有跑到重点呢？ 如上图 如果$y$到$1$的路径与$1$到$x$的路径有重点，假设这个重点为$s$，也就是说从$s$出发能到达到$1$，**也就是$1$与$s$处于同一来连通分量，与假设矛盾**。

于是$Tarjan$缩点连边，跑原边和反向边分别跑一次最长路，再枚举答案即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5, MAXM = 3e5 + 5, BOUND = 2e5, MOD = 1e9 + 7, INF = 0x3f3f3f3f;
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
struct Edge {
	int v, next;
}e[MAXM];
int n, m, u, v, cnt, head[MAXN], head2[MAXN], head3[MAXN];
int dfn[MAXN], d[2][MAXN], st[MAXN], top, tot, low[MAXN], sz[MAXN], col[MAXN], color, out[MAXN], root, in[MAXN];
bool vis[MAXN];
inline void addEdge(int *head, int u, int v) {
	e[++cnt].v = v; e[cnt].next = head[u]; head[u] = cnt;
}
void tarjan(int u) {
	dfn[u] = low[u] = ++tot;
	vis[u] = 1; st[++top] = u;
	for (int i = head[u]; i; i = e[i].next) {
		int v = e[i].v;
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if (vis[v]) low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		color++; int v;
		do {
			v = st[top--]; vis[v] = 0;
			col[v] = color, sz[color]++;
		} while (u != v);
	}
}
void spfa(int *head, int f) {
	memset(vis, 0, sizeof(vis));
	queue<int> q;
	q.push(col[1]);
	d[f][col[1]] = sz[col[1]]; vis[col[1]] = 1;
	while (q.size()) {
		int u = q.front(); q.pop();
		vis[u] = 0;
		for (int i = head[u]; i; i = e[i].next) {
			int v = e[i].v;
			if (d[f][v] < d[f][u] + sz[v]) {
				d[f][v] = d[f][u] + sz[v];
				if (!vis[v]) {
					vis[v] = 1;
					q.push(v);
				}
			}
		}
	}

}
int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> n >> m;
	rep(i, 1, m) {
		cin >> u >> v;
		addEdge(head, u, v);
	}
	rep(i, 1, n) {
		if (!dfn[i])tarjan(i);
	}
	rep(u, 1, n) {
		int v;
		for (int i = head[u]; i; i = e[i].next) {
			v = e[i].v;
			if (col[v] != col[u])addEdge(head2, col[v], col[u]), addEdge(head3, col[u], col[v]);
		}
	}
	spfa(head2, 0); spfa(head3, 1);
	int ans = sz[col[1]], v;
	rep(u, 1, color) {
		if (!d[1][u])continue;
		for (int i = head2[u]; i; i = e[i].next) {
			v = e[i].v;
			if (d[0][v]) {
				ans = max(ans, d[1][u] + d[0][v] - sz[col[1]]);
			}
		}
	}
	cout << ans << '\n';
	return 0;
}
```


---

## 作者：xukuan (赞：0)

tarjan+spfa

首先题目中说“Bessie在通一个草场只吃一次草，所以一个草场可以经过多次”，那么如果Bessie进入了一个环，肯定是吃完了环里的草再走

这样我们就可以用tarjan缩点

然后以1为起点和终点各跑一遍spfa（终点那组用建反图实现）

再枚举Bessie最后到的点，直接统计

注意两条线路只会在起点和终点有交点

证明（重点）：

反证法，假设起点为S，终点为T，交点为O。

那么S-O-T就形成了一个环

众所周知，tarjan缩点之后得到的图是一个DAG（有向无环图），所以不可能存在环，矛盾

故两条线路只会在起点和终点有交点

注意这里要减掉起点所在环的值，这里重复了

代码：

```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

bool v[100010];
ll n,m,color,deep,ans;
ll dfn[100010],low[100010],colour[100010],sum[100010];
//colour[i]表示i属于哪一个环，sum[i]表示环i中有几个点
ll _d[100010],_d_[100010];
ll ver[200010],Next[200010],head[100010],tot;//原图
ll _ver[200010],_Next[200010],_head[100010],_tot;//缩点后的正向图
ll _ver_[200010],_Next_[200010],_head_[100010],_tot_;//缩点后的反向图
stack<ll> st;
queue<ll> q;

inline ll read(){
	ll x=0,tmp=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') tmp=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+ch-48;
		ch=getchar();
	}
	return tmp*x;
}

inline void addEdge(ll x,ll y){//原图加边
	ver[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
}

inline void _addEdge(ll x,ll y){//缩点后的正向图加边
	_ver[++_tot]=y;
	_Next[_tot]=_head[x];
	_head[x]=_tot;
}

inline void _addEdge_(ll x,ll y){//缩点后的反向图加边
	_ver_[++_tot_]=y;
	_Next_[_tot_]=_head_[x];
	_head_[x]=_tot_;
}

inline void _spfa(ll s){//缩点后的正向图跑spfa，就是以1为起点的spfa
	memset(_d,0,sizeof(_d));
	memset(v,0,sizeof(v));
	_d[s]=sum[s]; v[s]=1;
	q.push(s);
	while(!q.empty()){
		ll x=q.front(); q.pop();
		for(ll i=_head[x]; i; i=_Next[i]){
			ll y=_ver[i];
			if(_d[y]<_d[x]+sum[y]){
				_d[y]=_d[x]+sum[y];
				if(!v[y]){
					q.push(y);
					v[y]=1;
				}
			}
		}
		v[x]=0;
	}
}

inline void _spfa_(ll s){//缩点后的反向图跑spfa，就是以1为终点的spfa
	memset(_d_,0,sizeof(_d_));
	memset(v,0,sizeof(v));
	_d_[s]=sum[s]; v[s]=1;
	q.push(s);
	while(!q.empty()){
		ll x=q.front(); q.pop();
		for(ll i=_head_[x]; i; i=_Next_[i]){
			ll y=_ver_[i];
			if(_d_[y]<_d_[x]+sum[y]){
				_d_[y]=_d_[x]+sum[y];
				if(!v[y]){
					q.push(y);
					v[y]=1;
				}
			}
		}
		v[x]=0;
	}
}

void tarjan(ll x){//缩点
	dfn[x]=low[x]=++deep;
	v[x]=1; st.push(x);
	for(ll i=head[x]; i; i=Next[i]){
		ll y=ver[i];
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else{
			if(v[y]) low[x]=min(low[x],low[y]);
		}
	}
	
	if(dfn[x]==low[x]){
		colour[x]=++color;
		v[x]=0;
		sum[color]=1;
		while(st.top()!=x){
			sum[color]++;
			colour[st.top()]=color;
			v[st.top()]=0;
			st.pop();
		}
		st.pop();
	}
}

int main(){
	n=read(); m=read();
	while(m--) addEdge(read(),read());
	for(ll i=1; i<=n; i++){
		if(!dfn[i]) tarjan(i);
	}
	for(ll x=1; x<=n; x++){
		for(ll i=head[x]; i; i=Next[i]){
			ll y=ver[i];
			if(colour[x]!=colour[y]){//不连出自环
				_addEdge(colour[x],colour[y]);
				_addEdge_(colour[y],colour[x]);
			}
		}
	}
	_spfa(colour[1]); _spfa_(colour[1]);
	ans=sum[colour[1]];
	for(ll i=1; i<=n; i++){
		if(!v[colour[i]]&&_d[colour[i]]){//这个环没有被访问且能从1号点走到
			ll x=colour[i]; v[x]=1;
			for(ll i=_head_[x]; i; i=_Next_[i]){
				ll y=_ver_[i];
				if(!_d_[y]) continue;
				ans=max(ans,_d[x]+_d_[y]-sum[colour[1]]);//逆向边的使用
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：大菜鸡fks (赞：0)

这题一开始一直以为缩点以后是树，就想了一些奇怪的贪心。所以看题想题还是要把细节都想全。

solution：这题的缩点还是挺显然的。考虑缩点以后的dag。你可以发现：最终的一条路径一定是由。 1号点所在联通块->k号点所在联通块->经过一条反向边->1号点所在联通块。

所以我们预处理出来原图和反图的最长路（每个联通块的大小作为点权）。最后枚举反向的边，计算出贡献。

tip:算贡献的时候注意去掉重复的。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=100005;
struct edge{
	int link,next;
}e[maxn],E[maxn];
int n,m,head[maxn],H[maxn],tot;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void add_edge(int u,int v){
	e[++tot]=(edge){v,head[u]}; head[u]=tot;
}
inline void init(){
	n=read(); m=read();
	for (int i=1;i<=m;i++){
		int u,v;
		u=read(); v=read();
		add_edge(u,v);
	}
}
bool instack[maxn];
int size[maxn],belong[maxn],dfn[maxn],tim,scc,low[maxn],top,stack[maxn];
inline void pop(){
	size[scc]++; belong[stack[top]]=scc; instack[stack[top--]]=0;
}
void tarjan(int u){
	dfn[u]=low[u]=++tim; stack[++top]=u; instack[u]=1;
	for (int i=head[u];i;i=e[i].next){
		int v=e[i].link;
		if (!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}else{
			if (instack[v]) low[u]=min(low[u],dfn[v]);
		}
	}
	if (low[u]==dfn[u]){
		scc++;
		while (stack[top]!=u) pop();
		pop();
	}
}
inline void Add(int u,int v){
	E[++tot]=(edge){v,H[u]}; H[u]=tot;
}
inline void build(){
	tot=0;
	for (int u=1;u<=n;u++){
		for (int i=head[u];i;i=e[i].next){
			int v=e[i].link;
			if (belong[u]!=belong[v]){
				Add(belong[u],belong[v]);
			}
		}
	}
}
int q[maxn],h,t,dis1[maxn],dis2[maxn],vis[maxn];
inline void spfa(int *dis){
	memset(dis,0,sizeof(dis)); 
	memset(vis,0,sizeof(vis));
	dis[belong[1]]=size[belong[1]];
	vis[belong[1]]=1; q[1]=belong[1]; h=0; t=1;
	while (h<t){
		int u=q[++h];
		for (int i=H[u];i;i=E[i].next){
			int v=E[i].link;
			if (dis[v]<dis[u]+size[v]){
				dis[v]=dis[u]+size[v];
				if (!vis[v]){
					q[++t]=v;
					vis[v]=1;
				}
			}
		}
		vis[u]=0;
	}
}
inline void rebuild(){
	tot=0;
	memset(H,0,sizeof(H));
	for (int u=1;u<=n;u++){
		for (int i=head[u];i;i=e[i].next){
			int v=e[i].link;
			if (belong[u]!=belong[v]){
				Add(belong[v],belong[u]);
			} 
		}
	}
}
int ans;
inline void solve(){
	for (int i=1;i<=n;i++){
		if (!dfn[i]){
			tarjan(i);
		}
	}
	build();
	spfa(dis1);
	rebuild();
	spfa(dis2);
	for (int u=1;u<=n;u++){
		for (int i=head[u];i;i=e[i].next){
			int v=e[i].link;
			if (dis2[belong[u]]&&dis1[belong[v]]){
				ans=max(ans,dis2[belong[u]]+dis1[belong[v]]-size[belong[1]]);
			}
		}
	}
	printf("%d\n",ans);
}
int main(){
	init();
	solve();
	return 0;
}
```


---

## 作者：沉辰 (赞：0)

第一反应，先tarjan缩点。之后我们得到一个没有环的新图。
 
如果不走逆向边，那么从1出发回到1，新图没有环，走过的点数就是原图1所在的环点的数目
 
但是我们又一次走逆向边的机会，所以在没有环的情况下，我们可以主动制造一个环
 
 
 
考虑如何制造一个环？
 
因为我们可以走反向边，假设对于边j反向得到了一个环。
 
那么就相当于在这里由环断为两条链 
 
链中存在两种点 ：一个是1可以到达的点 ， 另一种是可以到达1的点
 
对于这个可以用拓扑排序处理出来（预处理时要注意细节，详见代码）
 
 
 
考虑怎样得到答案：
 
我们可以枚举某一条边，把它反向，
 
ans=从1到此边一点的数目+另一点到1的点的数目-1所在强连通分量点的数目(因为这个环被加了两次)
代码见博客
[安然流香](http://www.cnblogs.com/adelalove/p/8490391.html)


---

