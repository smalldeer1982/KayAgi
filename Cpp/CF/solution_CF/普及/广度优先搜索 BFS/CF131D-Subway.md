# Subway

## 题目描述

给出一个 $n$ 个点，$n$ 条边的无向无权图，图上每条边的长度为 $1$，保证图中有且仅由一个环。

你的任务是求出每一个点到环（环上任意一点）的最短路径长度。

## 样例 #1

### 输入

```
4
1 3
4 3
4 2
1 2
```

### 输出

```
0 0 0 0 ```

## 样例 #2

### 输入

```
6
1 2
3 4
6 4
2 3
1 3
3 5
```

### 输出

```
0 0 0 1 1 2 ```

# 题解

## 作者：ForLune_ (赞：7)

这里给出一种比较简单易懂的基环树找环方法。

[![voPydI.png](https://s1.ax1x.com/2022/09/03/voPydI.png)](https://imgse.com/i/voPydI)

观察该图。容易发现这棵基环树上的环为 $loop= \{ 3,4,5,6,7 \} $ 。考虑这棵基环树从节点 $1$ 开始的 $DFS$ 序： $1 \rightarrow 2 \rightarrow \color{Red} 3 \color{Black}  \rightarrow 4 \rightarrow 5 \rightarrow a \rightarrow b \rightarrow 6\rightarrow 7 \rightarrow  \color{Red} 3 \color{Black} \rightarrow ...$ ，容易发现这个环的搜索序中，从节点 $3$ 开始并从节点 $3$ 结束，那么显而易见的是我们在找环的时候第二次搜索到节点 $3$ 时，就要把 $3$ 标记上，说明我们已经找到了环上的一个节点 $3$ ，而且按照我们的搜索顺序节点 $3$ 是这个环的起点，也是这个环的终点。

显然，节点 $3$ 是这个环上的点，那么这个搜索顺序中节点 $3$ 的父节点节点 $7$ 也是这个环上的点，而节点 $7$ 的父节点 $6$ 也是这个环上的点......最后节点 $4$ 的父节点 $3$ 是环上的点，但节点 $3$ 的父节点 $2$ 不是这个环上的点（注意此时的“父节点”是对于搜索序而言）。

我们发现了一个性质：在基环树上，以某个节点为根开始搜索，第一次走到的重复搜索的节点（对于上图来说就是节点 $3$ ），我们称之为“合点”。而对于任意一个合点之外的节点，若这个节点在环上，那么它在这个搜索序中的父节点也在环上。

所以我们在找环的时候，可以从某个根节点开始搜索，若搜索到任意一个节点 $u$ 是重复搜索过的，就把这个节点标记为“合点”，并把它和它在搜索序上的父节点加入环（否则它的这个父节点就不会被加入到环里面）。在搜索完某个节点 $u$ 的子节点 $v$ 后，若节点 $v$ 在环上而且 $v$ 不是合点，那么就把节点 $u$ 也加入环。

这样一来我们就通过一次搜索找到了环。

```cpp
inline void find_loop(const int father,const int u)
{
	if(vis[u])																		//已经搜索过了 
	{
		if(!flag)																	//这是第一个被搜索到的合点 
		loop[++cnt]=u,loop[++cnt]=father,											//将合点和father加入环 
		mark[u]=mark[father]=true,													//把合点和father标记为环上的点 
		flag=u;																		//标记合点 
		return;
	}
	vis[u]=true;
	for(register int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(v==father) continue;
		find_loop(u,v);
		if(v!=flag&&mark[v])														//如果v不是合点而且v在环上 
		{
			if(!mark[u]) loop[++cnt]=u;												//若u还没加入环，把u加入环 
			mark[u]=true;															//把u标记为环上的点 
		}
	}
}
```

---

那么找到环之后，这道题该怎么做呢？显然我们可以从环上的每一个点 $u$ 出发，跳过环上的其他点，搜索以节点 $u$ 为根的子树，并依次更新每个节点到节点 $u$ 的距离，最后再输出即可。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int n,dis[3005];
int cnt,flag,total,head[3005],loop[3005];
bool vis[3005],mark[3005];
struct Edge{int to,next;} edge[6005];
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
inline void link(const int u,const int v) {edge[++total]=Edge{v,head[u]},head[u]=total;}
inline void find_loop(const int father,const int u)
{
	if(vis[u])
	{
		if(!flag) loop[++cnt]=u,loop[++cnt]=father,flag=u,mark[u]=mark[father]=true;
		return;
	}
	vis[u]=true;
	for(register int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(v==father) continue;
		find_loop(u,v);
		if(v!=flag&&mark[v])
		{
			if(!mark[u]) loop[++cnt]=u;
			mark[u]=true;
		}
	}
}
inline void dfs(const int father,const int u)
{
	for(register int i=head[u];i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(v==father||mark[v]) continue;
		dis[v]=dis[u]+1;
		dfs(u,v);
	}
}
int main()
{
	n=read();
	for(register int i=1,u,v;i<=n;++i) u=read(),v=read(),link(u,v),link(v,u);
	find_loop(0,1);
	for(register int i=1;i<=cnt;++i) dfs(0,loop[i]);
	for(register int i=1;i<=n;++i) printf("%d ",dis[i]);
	return 0;
}
```

---

## 作者：August_Light (赞：6)

# Subway 题解

[题目传送门](https://www.luogu.com.cn/problem/CF131D)

upd（2023/6/19）：解决了原来代码太丑的问题。

## 题意简述

给定一棵 $n$ 个节点的基环树，求每个节点到环的最短距离。

$n \le 10^3$。

## 解法

~~这是蓝题？~~

考虑基环树的 DFS 树，显然基环树上有且仅有一条边是非树边，且这条边是环的一部分。

任选一个节点为根做 DFS（`find_ring::dfs`），遇到儿子已经被 DFS 过的情况就说明找到了这条边（记为 $u\to v$）。

因为无向图的 DFS 树是没有横叉边的，记录一下每个节点的父亲（`find_ring::fa`），从 $u$ 沿着父亲一直往上跳到 $v$，这条路径上的所有点就组成了环。

找到环后以环上的每个节点为根对子树 DFS 一遍（`dfs`）即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

// 省略快读快写的实现

const int MAXN = 1e5 + 100;
const int MAXM = MAXN << 1;

struct Edge {
    int to, nxt;
} e[MAXM];
int head[MAXN], cnt = 1;
void addedge(int u, int v) {
    e[++cnt].to = v;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}

namespace find_ring {
    bool vis[MAXN], on_ring[MAXN];
    int fa[MAXN];
    vector<int> ring;
    void dfs(int u, int lst) {
        vis[u] = 1;
        for (int i = head[u]; i; i = e[i].nxt) {
            if (i == (lst ^ 1))
                continue;
            int v = e[i].to;
            if (!vis[v]) {
                fa[v] = u;
                dfs(v, i);
            } else if (!on_ring[v]) {
                on_ring[u] = 1; ring.push_back(u);
                int c = u; do {
                    c = fa[c];
                    on_ring[c] = 1; ring.push_back(c);
                } while (c != v);
            }
        }
    }
}
using find_ring::on_ring;
using find_ring::ring;

int ans[MAXN];
void dfs(int u, int lst, int dep) {
    ans[u] = dep;
    for (int i = head[u]; i; i = e[i].nxt) {
        if (i == (lst ^ 1))
            continue;
        int v = e[i].to;
        if (on_ring[v])
            continue;
        dfs(v, i, dep+1);
    }
}

int main() {
    int n = read();
    for (int i = 1; i <= n; i++) {
        int u = read(), v = read();
        addedge(u, v);
        addedge(v, u);
    }
    find_ring::dfs(1, 0);
    for (auto u : ring)
        dfs(u, 0, 0);
    for (int u = 1; u <= n; u++)
        write(ans[u], ' ');
    return 0;
}

```

---

## 作者：stntn (赞：4)

## 题意
求基环树每个点到环上的最少边数。

## 两遍 dfs

第一遍 dfs，找出环，并将环上的点打上标记。

```cpp
inline void dfs1(int u)
{
	vis[u]=1;
	for(re int i=head[u];~i;i=e[i].nxt)
	{
		int v=e[i].v;if(v==fa[u]||e[i].t) continue;//e[i].t 边 i是否为树边 否为true。 
		if(vis[v]){e[i].t=e[i^1].t=1;color(u,v);continue;}//如果v已经遍历过，说明该两点间形成环，打上标记。 
		fa[v]=u;dfs1(v);
	}
}
```


```cpp
inline void color(int u,int v) 
{
	while(u!=v) ont[u]=1,u=fa[u];//ont[i] 点 i是否在环上 是为true。 
	ont[v]=1;root=v;//将其中一个点改为根。 
}
```

第二遍 dfs，求每个点到环上的距离

由于第一次已经将环上一点置为根，所以不需要考虑某个点深度小于环的情况。

```cpp
inline void dfs2(int u,int fa)
{
	for(re int i=head[u];~i;i=e[i].nxt)
	{
		int v=e[i].v;if(v==fa||e[i].t) continue;//不要遍历到非树边，否则死循环。 
		dis[v]=dis[u]+(ont[v]^1);//v非环上点，说明已经脱离环进入树，开始统计路程。 
		dfs2(v,u);
	}
}
```
依次执行两次 dfs 即可

```cpp
signed main()
{
	srand(time(0));
	memset(head,-1,sizeof(head));
	read(n);root=rand()%n+1;//随机选根 
	for(re int i=1,u,v;i<=n;i++)
	{
		read(u);read(v);
		add_edge(u,v);
	}
	dfs1(root);
	dfs2(root/*此时根已在环上*/ ,0);
	for(re int i=1;i<=n;i++) printf("%d ",dis[i]);printf("\n");
	return 0;
}
```



---

## 作者：hater (赞：2)

你谷自古以来题解区多神仙 

这道题也不例外 

四篇全部缩点 ？？？？？ 

这难道不是基环树的环操作吗 ？ 

拓扑排序似乎木有毛病吧 ？ 

思路 ： 

topsort 条件是度为1的点进队 

解释一下 

度为一的点 只保留着一条达到另外一个节点的边 

那么显然 这个点并不是环上的点 于是入队 

最后 入度 >= 2 的节点就是环上的节点 

找出环上的点后 以那些点为起点 做 SPFA 

代码 ： 

```cpp
#include <bits/stdc++.h> 
#define MAX 3005 
#define R register 
using namespace std ; 
vector <int> v[MAX] ;  
int dep[MAX] , ins[MAX] , n ;  
bool In[MAX] ;  
queue <int> q ; 
signed main() 
{
	R int x , y ; 
	ios::sync_with_stdio(false) ;
	cin >> n ;
	for(R int i=1; i<=n; i++) 
	{
		cin >> x >> y ;
		v[x].push_back(y) ;
		v[y].push_back(x) ; 
		ins[x] ++ ; ins[y]++ ; 
	}
    for(R int i=1; i<=n; i++)
     if( ins[i] == 1 ) q.push(i) ; 
    while( !q.empty() ) 
    {
    	R int u = q.front() ; q.pop() ;
		for(R int i=0; i<v[u].size(); i++) 
		{
		   R int x = v[u][i] ; 
		   if( ins[x] <= 1 ) continue ;
		   ins[x] -- ; 
		   if( ins[x] == 1 ) 
		     q.push(x) ;	
		} 
	}
	memset( dep , 0x7f , sizeof(dep) ) ; 
	for(R int i=1; i<=n; i++)
	  if( ins[i] >= 2 ) dep[i] = 0 , q.push(i) ;
	while( !q.empty() ) 
	{
		R int u = q.front() ; q.pop() ; In[u] = 0 ; 
		for(R int i=0; i<v[u].size(); i++) 
		{
		   R int x = v[u][i] ;
		   if( ins[x] >= 2 ) continue ; 
		   if( dep[x] > dep[u]+1 ) 
		   {
		   	    dep[x] = dep[u]+1 ;
			    if( !In[x] ) 
				{
					In[x] = 1 ; 
					q.push(x) ;
				}  
		   } 	
		} 
	}
	for(R int i=1; i<=n; i++) 
	  cout << dep[i] << " " ; 
	cout << endl; 
	return 0 ; 
}
```


应该可以快的 但是人丑常数大 还懒

不卡 rk1 了

---

## 作者：米奇奇米 (赞：2)

## 题解-CF131D Subway

### 这道题目可以说不是很难吧，主要是代码比较长。

### $1.1$ 题目意思
题目意思很简单，就是让你求出每个点到唯一环的距离！题面是不是很小清新呀！

### $2.1$算法思想
我们可以先对那个环进行$tarjan$缩点，然后重新构图。

对于同一个强连通分量里的点，显然答案为$0$，其实说简单的就是求出每个强连通分量之间的距离。

这样求距离我们可以用$lca$求解：$dis=dep[a]+dep[b]-2*dep[lca(a,b)]$

这样我们就做出了一题$Div2 D$~~(逃~~

### $3.1$代码实现
主要是模板代码，细节也不是很多
```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=1e4+5,maxm=5e4+5;
struct nood {
    int nex,to;
} e[maxm<<1];
int head[maxn],low[maxn],dfn[maxn];
int stak[maxn],siz[maxn],col[maxn];
int pa[maxn][17],d[maxn],u[maxn],v[maxn];
int n,m,cnt,sum,now,s,rt,top,bit[35];
map<int,int>ma;

inline void add_edge(int u,int v) {
    e[++cnt].nex=head[u];
    head[u]=cnt;
    e[cnt].to=v;
}//前向星连边

inline void tarjan(int u,int fa) {
    stak[++top]=u;
    low[u]=dfn[u]=++now;
    for ( int i=head[u];i;i=e[i].nex ) {
        int v=e[i].to;
        if(v==fa) continue;
        if(!dfn[v]) {
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
        }
        else 
            if(!col[v]) 
                low[u]=min(low[u],dfn[v]);
    }
    if(low[u]==dfn[u]) {
        col[u]=++sum;
        siz[sum]++;
        while(stak[top]!=u) {
            col[stak[top]]=sum;
            siz[sum]++;
            top--;
        }
        top--;
    }
}//tarjan缩点

inline void dfs(int u,int fa) {
    d[u]=d[fa]+1;
    pa[u][0]=fa;
    for ( int i=1;i<=15;i++ ) 
        pa[u][i]=pa[pa[u][i-1]][i-1];
    for ( int i=head[u];i;i=e[i].nex ) {
        int v=e[i].to;
        if(v==fa) continue;
        dfs(v,u);
    }
}//lca预处理

inline int lca(int a,int b) {
    if(d[a]>d[b]) swap(a,b);
    for ( int i=15;i>=0;i-- ) 
        if(d[b]-(1<<i)>=d[a]) b=pa[b][i];
    if(a==b) return a;
    for ( int i=15;i>=0;i-- ) 
        if(pa[a][i]!=pa[b][i]) {
            a=pa[a][i];
            b=pa[b][i];
        }
    return pa[a][0];
}//求两点lca

inline int find(int a,int b) {
    return d[a]+d[b]-2*d[lca(a,b)]+1;
}//求两点之间的距离

inline int read() {
    int sum=0; char ch=getchar();
    while(!isdigit(ch)) ch=getchar();
    while(isdigit(ch)) 
        sum=sum*10+(ch-'0'),ch=getchar();
    return sum;
}

int main() {
    n=read(),m=n;
    for ( int i=1;i<=m;i++ ) {
        u[i]=read(),v[i]=read();
        add_edge(u[i],v[i]);
        add_edge(v[i],u[i]);
    }
    for ( int i=1;i<=n;i++ ) 
        if(!dfn[i]) tarjan(i,-1);
    cnt=0;
    memset(head,0,sizeof(head));
    memset(e,0,sizeof(e));
    for ( int i=1;i<=m;i++ ) 
        if(col[u[i]]!=col[v[i]]) {
            add_edge(col[u[i]],col[v[i]]);
            add_edge(col[v[i]],col[u[i]]);
        }
    //重新构图，对于不是同一个强联通分量里面的点连边
    dfs(1,0);   
    for ( int i=1;i<=n;i++ ) {
		ma[col[i]]++;
		if(ma[col[i]]>=2) rt=i;
	}
    //其实没有必要
	for ( int i=1;i<=n;i++ ) 
		if(col[i]==col[rt]) printf("0 ");
			else printf("%d ",find(col[i],col[rt])-1);
    return 0;
}
```





---

## 作者：Priori_Incantatem (赞：2)

做法应该很明显了，把环找出来求最短路就可以了，重点是怎么找环

这里讲的是一个 $O(n^2)$ 的神奇 dfs，非常容易写  
思路与 dfs/spfa 找环很相似，只不过不需要判断最短路

```cpp
void dfs(int x,int fa,int top) // fa,top 分别为上一个访问的节点和该次dfs的第一个节点
{
	flag[x]=1; // 打上标记
	
	for(int i=0;i<e[x].size();++i)
	{
		int y=e[x][i];
		if(y==fa)continue;
		if(flag[y]) //如果已经访问过了
		{
			if(y==top)opt2=1; // 这个判断的意义，是为了保证已经打上标记的所有点都在环上
			opt1=1; // 打上退出递归的标记
			return;
		}
		dfs(y,x,top);
		if(opt1)return;
	}
	
	flag[x]=0;
}
```

跑完 dfs 后，所有环上的点都被标记了，然后将它们塞进队列跑 dijkstra 就可以了  
其实 bfs 也行，因为是无权图

```cpp
#include<cstdio>
#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int Maxn=3020,inf=0x3f3f3f3f;
struct node{
	int pos,dis;
	node(int x,int y)
	{
		pos=x,dis=y;
	}
	bool operator <(const node &x)const
	{
		return x.dis<dis;
	}
};
int dis[Maxn];
bool vis[Maxn],flag[Maxn],opt1,opt2;
int n;
vector <int> e[Maxn];
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
void dfs(int x,int fa,int top)
{
	flag[x]=1;
	
	for(int i=0;i<e[x].size();++i)
	{
		int y=e[x][i];
		if(y==fa)continue;
		if(flag[y])
		{
			if(y==top)opt2=1;
			opt1=1;
			return;
		}
		dfs(y,x,top);
		if(opt1)return;
	}
	
	flag[x]=0;
}
void dij()
{
	priority_queue <node> q;
	fill(dis+1,dis+1+n,inf);
	for(int i=1;i<=n;++i)
	{
		if(!flag[i])continue;
		dis[i]=0,vis[i]=1;
		q.push(node(i,0));
	}
	while(q.size())
	{
		int x=q.top().pos;
		q.pop();
		for(int i=0;i<e[x].size();++i)
		{
			int y=e[x][i];
			if(dis[y]>dis[x]+1)
			{
				dis[y]=dis[x]+1;
				if(!vis[y])vis[y]=1,q.push(node(y,dis[y]));
			}
		}
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	n=read();
	
	for(int i=1;i<=n;++i)
	{
		int x=read(),y=read();
		e[x].push_back(y);
		e[y].push_back(x);
	}
	
	for(int i=1;i<=n;++i)
	{
		opt1=0;
		dfs(i,0,i);
		if(opt2)break; // opt2=1 说明已经找到了环，并且保证标记无误
		fill(flag+1,flag+1+n,0); // 记得将标记清零
	}
	dij();
	
	for(int i=1;i<=n;++i)
	printf("%d ",dis[i]);
	putchar('\n');
	
	return 0;
}
```

---

## 作者：Epoch_L (赞：1)

题目链接：

[洛谷](https://www.luogu.com.cn/problem/CF131D "洛谷")

[Codeforces](https://codeforces.com/problemset/problem/131/D "Codeforces")
## Solution
Tarjan 板题。

很明显可以用 Tarjan 找到这一个环。注意由于这是一个无向图，所以需要多记录一个当前节点的父亲，防止其反复横跳。然后缩完点以后，找到一个强连通分量的大小大于 $1$，也就是那一个环，以它为源点，跑 dijkstra，与此同时把那个环里的点打上标记。最后输出时如果有标记，就输出 $0$，否则输出其最短路径。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
void read(int &x)
{
	char ch=getchar();
	int r=0,w=1;
	while(!isdigit(ch))w=ch=='-'?-1:1,ch=getchar();
	while(isdigit(ch))r=(r<<3)+(r<<1)+(ch^48),ch=getchar();
	x=r*w;
}
const int N=1e5+7;
int low[N],dfn[N],stk[N],sz[N],scc[N];
int pre[N],now[N],son[N],dis[N],d[N];
int n,top,tot,sc,dfn_cnt;
bool in_stk[N],bb[N],cc[N];
vector<int>edge[N];
vector<int>in_h[N];
priority_queue<pair<int,int> >q;
void add(int x,int y,int z)
{
	pre[++tot]=now[x];
	son[tot]=y;
	dis[tot]=z;
	now[x]=tot;
}
void tarjan(int u,int fa)
{
	low[u]=dfn[u]=++dfn_cnt;stk[++top]=u;in_stk[u]=1;
	for(int v:edge[u])
	{
		if(v==fa)continue;
		if(!dfn[v])
		{
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
		}
		else if(in_stk[v])low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
	{
		sc++;
		do
		{
			scc[stk[top]]=sc;
			in_h[sc].push_back(stk[top]);
			sz[sc]++;
			in_stk[stk[top]]=0;
			top--;
		}while(stk[top+1]!=u);
	}
}
void dij(int s)
{
	memset(d,63,sizeof d);
	d[s]=0;q.push(make_pair(0,s));
	while(!q.empty())
	{
		int u=q.top().second;q.pop();
		if(bb[u])continue;
		bb[u]=1;
		for(int i=now[u];i;i=pre[i])
		{
			int v=son[i],w=dis[i];
			if(d[v]>d[u]+w)
			{
				d[v]=d[u]+w;
				q.push(make_pair(-d[v],v));
			}
		}
	}
}
void work()
{
	for(int u=1;u<=n;u++)
	for(int v:edge[u])
		if(scc[u]!=scc[v])add(scc[u],scc[v],1),add(scc[v],scc[u],1);
}
int main()
{
	read(n);
	for(int i=1,x,y;i<=n;i++)
	{
		read(x);read(y);
		edge[x].push_back(y);edge[y].push_back(x);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])tarjan(i,0);
	work();
	for(int i=1;i<=sc;i++)
	{
		if(sz[i]>1)
		{
			for(int j:in_h[i])cc[j]=1;
			dij(i);
			break;
		}
	}
	for(int i=1;i<=n;i++)
		printf("%d ",cc[i]==1?0:d[scc[i]]);
	return 0;
} 
```

---

## 作者：Zofia (赞：1)

### 前言

dfs和缩点的一般方法我就不再赘述了；
在此我就讲一点小技巧好了。

### 正文

本题需要求其他点到一组点的最短路，当然Tarjan找环是不可避免的，在此不多讲；

![image.png](https://i.loli.net/2019/10/06/sSbeUjF6ynXJ9fV.png)

对于类似的以一组点为源的最短路，我们可以构造一个虚点'0',到题中钦定的各点距离为0，这样以一组点为源的最短路就转化为了'0'的单源最短路。
然后直接跑最短路就完事了。

![image.png](https://i.loli.net/2019/10/06/PMH9ydr6I3FZJTK.png)

这种做法对于不在环上的一组点依然适用，对于有/无权，有/无向图均是使用的。

截至2019.10.06，最优解排名14，还是蛮快的。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m;
struct node{
	int to,dis,pnext;
}edge[100001];
int head[30001],ni=1,t;
int ins[30001],dfn[30001],low[30001];
stack<int>s;

inline void addedge(register int f,register int t,register int d){
	edge[++ni].to=t;
	edge[ni].dis=d;
	edge[ni].pnext=head[f];
	head[f]=ni;
}

inline int read(){
    register int x=0,f=1;
    register char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-'){f=-1;}ch=getchar();
    }while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);ch=getchar();
    }return x*f;
}

int inq[30001],dis[30001];
deque<int>q;

inline void SPFA(register int s){
	memset(dis,127,sizeof(dis));
	dis[s]=0;inq[s]=1;
	q.push_back(s);
	while(!q.empty()){
		register int u=q.front();
		q.pop_front();inq[u]=0;
		for(register int i=head[u];i;i=edge[i].pnext){
			register int v=edge[i].to;
			if(dis[v]>edge[i].dis+dis[u]){
				dis[v]=edge[i].dis+dis[u];
				if(!inq[v]){
					inq[v]=1;
					if(q.size()&&dis[v]<=dis[q.front()]){q.push_front(v);}
					else{q.push_back(v);}
				}
			}
		}
	}
}

int vec[30001],vi;

inline void Tarjan(register int p,register int e){
	dfn[p]=low[p]=++t;
	ins[p]=1;s.push(p);
	for(register int i=head[p];i;i=edge[i].pnext){
		if(i!=(e^1)){
			register int v=edge[i].to;
			if(!dfn[v]){
				Tarjan(v,i);
				low[p]=min(low[p],low[v]);
			}else if(ins[v]){
				low[p]=min(dfn[v],low[p]);
			}
		}
		
	}if(low[p]==dfn[p]){
		vi=0;
		while(s.top()!=p){
			ins[s.top()]=0;
			vec[++vi]=s.top();
			s.pop();
		}ins[s.top()]=0;
		vec[++vi]=s.top();
		s.pop();
		if(vi>1){
			for(register int i=1;i<=vi;i++){
				addedge(0,vec[i],0);
			}SPFA(0);
			for(register int i=1;i<=n;i++){
				printf("%d ",dis[i]);
			}exit(0);
		}
	}
}

int main(){
	m=n=read();
	for(register int i=1;i<=m;i++){
		register int x=read(),y=read();
		addedge(x,y,1);addedge(y,x,1);
	}for(register int i=1;i<=n;i++){
		if(!dfn[i]){Tarjan(i,0);}
	}return 0;
}
```


谢谢大家！

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF131D)

# 前置知识

[强连通分量](https://oi-wiki.org/graph/scc/) | [最短路](https://oi-wiki.org/graph/shortest-path/)

# 解法

考虑用 Tarjan 进行缩点，然后跑最短路。

  - 缩点：本题的缩点有些特殊，基于有向图缩点修改而得，因为是无向图，所以在 Tarjan 过程中要额外记录一下从何处转移过来，防止在同一处一直循环。
    - 基环树上找环还有其他方法，详见 [luogu P8655 [蓝桥杯 2017 国 B] 发现环](https://www.luogu.com.cn/problem/P8655)，这里仅讲解使用 Tarjan 求解。
  - 最短路：因为缩完点后就形成了一棵树，且因为是无向图，环外任意一点到环上最短距离等同于环上到环外任意一点最短距离，所以接着以环缩成的点为起点跑单源最短路或 DFS 或 LCA 求解即可。本篇题解使用 Dijkstra 算法求单源最短路。
    - 用 LCA 有些杀鸡用牛刀了。
	  - [luogu P2783 有机化学之神偶尔会做作弊](https://www.luogu.com.cn/problem/P2783) 需要用到 LCA 求解。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define sort stable_sort 
#define endl '\n'
struct node
{
	int nxt,to,w;
}e[10000];
int head[10000],u[10000],v[10000],dfn[10000],low[10000],ins[10000],c[10000],dis[10000],vis[10000],cnt=0,tot=0,ans=0,scc=0,rt=0;
stack<int>s;
void add(int u,int v)
{
	cnt++;
	e[cnt].nxt=head[u];
	e[cnt].to=v;
	e[cnt].w=1;
	head[u]=cnt;
}
void tarjan(int x,int fa)
{
	int i,k=0;
	tot++;
	dfn[x]=low[x]=tot;
	ins[x]=1;
	s.push(x);
	for(i=head[x];i!=0;i=e[i].nxt)
	{
		if(e[i].to!=fa)
		{
			if(dfn[e[i].to]==0)
			{
				tarjan(e[i].to,x);
				low[x]=min(low[x],low[e[i].to]);
			}
			else
			{
				if(ins[e[i].to]==1)
				{
					low[x]=min(low[x],dfn[e[i].to]);
				}
			}
		}
	}
	if(dfn[x]==low[x])
	{
		ans++;
		scc=0;
		while(x!=k)
		{
			k=s.top();
			ins[k]=0;
			c[k]=ans;
			scc++;
			s.pop();
		}
		if(scc>=2)
		{
			rt=ans;
		}
	}
}
void dijkstra(int s)
{
	int x,i;
	priority_queue<pair<int,int> >q;
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;
	q.push(make_pair(0,-s));
	while(q.empty()==0)
	{
		x=-q.top().second;
		q.pop();
		if(vis[x]==0)
		{
			vis[x]=1;
			for(i=head[x];i!=0;i=e[i].nxt)
			{
				if(dis[e[i].to]>dis[x]+e[i].w)
				{
					dis[e[i].to]=dis[x]+e[i].w;
					q.push(make_pair(-dis[e[i].to],-e[i].to));
				}
			}
		}
	}
}
int main()
{
	int n,i;
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>u[i]>>v[i];
		add(u[i],v[i]);
		add(v[i],u[i]);
	}
	for(i=1;i<=n;i++)
	{
		if(dfn[i]==0)
		{
			tarjan(i,0);
		}
	}
	cnt=0;
	memset(e,0,sizeof(e));
	memset(head,0,sizeof(head));
	for(i=1;i<=n;i++)
	{
		if(c[u[i]]!=c[v[i]])
		{
			add(c[u[i]],c[v[i]]);
			add(c[v[i]],c[u[i]]);
		}
	}
	dijkstra(rt);
	for(i=1;i<=n;i++)
	{
		cout<<dis[c[i]]<<" ";
	}
	return 0;
}	 
```

# 后记

推销一下自己的 [ Tarjan 学习笔记](https://www.cnblogs.com/The-Shadow-Dragon/p/17548536.html) 。

---

## 作者：osfly (赞：0)

注意到 $n$ 实在是小到不行，我们可以直接采用比较暴力的做法。

~~（嗯，可能算比较暴力吧~~

很简单，找环，然后把环里的所有点全部压进 `dijkstra` 的优先队列就行了。

找环最坏 $n$ 遍跑满的 `dfs`，最短路是 $O(n\log n)$ 的，最坏时间复杂度为 $O(n^2)$，稳过。

~~什么？怎么找环？都2202年了不会还有人不会找环吧qwq~~

对每一个点为起始点，都跑一边 `dfs`，一边跑一边标记，如果跑的时候碰到已经标记好的点，就说明碰到环了（注意不是标记完环了，现在还不能退出来因为我们标记的点中有多余的点，并不是单纯的环）。如果没有碰到就取消标记。

什么时候结束 `dfs` 呢？就是如果我们找到一个点是我们的起始点就可以结束了，此时易知我们现在标记的所有点就是环。

最后就快乐地上最短路啦~

```cpp
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
struct edge
{
	int v;
	int w;
	int nxt;
}e[6010];
int head[3010],tot;
void add(int u,int v,int w)
{
	e[++tot].v=v;
	e[tot].w=w;
	e[tot].nxt=head[u];
	head[u]=tot;
}
int n;
bool flag[3010];
bool ry,qwq;
void dfs(int u,int fa,int st)
{
	flag[u]=1;//标记
	for(int i=head[u];i&&!qwq;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa) continue;
		if(flag[v])//找到环了
		{
			if(v==st) ry=1;//现在标记的点是环，可以退出dfs了
			qwq=1;
			return ;
		}
		dfs(v,u,st);
	}
	if(!qwq) flag[u]=0;//从当前节点出发没有碰到环的话就取消标记
}
int dis[3010];
bool vis[3010];
void dij()//人尽皆知的东西
{
	priority_queue<pair<int,int> > q;
	memset(dis,0x7f,sizeof(dis));
	for(int i=1;i<=n;i++)
		if(flag[i])
		{
			dis[i]=0;
			q.push(make_pair(0,i));
		}
	int u;
	while(!q.empty())
	{
		u=q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt)
		{
			int v=e[i].v,w=e[i].w;
			if(dis[v]>dis[u]+w)
			{
				dis[v]=dis[u]+w;
				q.push(make_pair(-dis[v],v));
			}
		}
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1,u,v;i<=n;i++)
	{
		scanf("%d%d",&u,&v);
		add(u,v,1),add(v,u,1);
	}
	for(int i=1;i<=n&&!ry;i++)//对每个点都跑一遍dfs
	{
		qwq=0;
		memset(flag,0,sizeof(flag));//记得初始化
		dfs(i,0,i);
	}
	dij();
	for(int i=1;i<=n;i++) printf("%d ",dis[i]);
	return 0;
}
```

---

## 作者：若如初见 (赞：0)

20191104 upd：修正了一些小bug

** 本蒟蒻发一个不一样的做法：Kosaraju缩点。~~明明就是不会tarjan嘛~~ ** 

 首先说说 Kosaraju 在有向图上寻找强连通分量的做法：  

* 以任意点为起点，对图进行深度优先遍历，并记录每个节点的**退出顺序**；  

* 按照**退出顺序的逆序**，在**反向图**上进行深度优先遍历。每次深度优先遍历所经过的结点在同一个强连通分量上。  

以这张很著名的图为例：  

![](https://cdn.luogu.com.cn/upload/image_hosting/q4l3kanw.png)  

我们以 1 号结点为起点对图进行深度优先遍历：  

1 -> 3 -> 5 -> 6（退出） -> 5（退出） -> 4（退出） -> 3（退出）-> 2（退出） -> 1（退出）  

则退出顺序为：6 5 4 3 2 1  

按照退出顺序的逆序**在反图上**进行深度优先遍历：  

以 1 为起点：1 -> 4 -> 3 -> 2 -> 退出  

以 5 为起点：5 -> 退出

以 6 为起点：6 -> 退出

则原图中所有的强连通分量为：（1,4,3,2），（5）,（6）  

## 那么在基环树上呢？

基环树就是本题的情况。所谓基环树，可以理解为一棵树 + 一条边，即有 $n$ 个点和 $n$ 条边的、有唯一环的无向图。  

其实这种情况不难处理：首先进行依次深度优先遍历，标记经过的所有树边和返祖边（其实可以理解成标记第一次dfs时经过的所有边就可以了），这样我们就得到了一张“有向图”，再进行 Kosaraju 缩点即可。最后得到的所有强连通分量中，包含的点数多于 $1$ 的即为在环上的点。    

最后要求各点到环的距离也很简单，再进行一次 dfs 并记录深度即可。  

## 代码如下：  

```cpp
#include <cstdio>
#include <cstring>
#define MAXN 30005 //关于数据范围：题面上写了 n<=3000，但是第一次做的时候我 WA 了。。。把数组开到 30000 就过了
using namespace std;
int n,cnt,head[MAXN],mark[MAXN],s[MAXN],u[MAXN],v[MAXN],r,t,c[MAXN],circle,ans[MAXN];
bool vis[MAXN],flag[MAXN];
struct Edge{
	int next,to;
}edge[MAXN<<1];
inline void add(int u,int v){
	edge[++cnt].next=head[u];
	edge[cnt].to=v;
	head[u]=cnt;
}
void dfs1(int p){
	vis[p]=1;
	for(int i=head[p];i;i=edge[i].next){
		int v=edge[i].to;
		if(!vis[v]){
			flag[i]=1; //标记“有向边”
			dfs1(v);
		}
	}
	s[++r]=p; // 记录退出顺序
}
void dfs2(int p){
	vis[p]=1;
	mark[p]=t;
	c[t]++;
	for(int i=head[p];i;i=edge[i].next){
		if(flag[i]) continue; //因为此题给出的原图是无向图，所以dfs1时没有被标记的边相当于反图中的边
		int v=edge[i].to;
		if(!vis[v]) dfs2(v);
	}
}
void dfs3(int p,int depth){
	vis[p]=1;
	ans[p]=depth;
	for(int i=head[p];i;i=edge[i].next){
		int v=edge[i].to;
		if(!vis[v]) dfs3(v,depth+1);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d %d",&u[i],v[i]);
		add(u[i],v[i]);
		add(v[i],u[i]); //建一开始的无向图
	}
	dfs1(1); //第一次dfs：记录退出顺序经过的边
	memset(vis,0,sizeof(vis)); //清空 vis 数组，准备第二次深搜
	for(int i=n;i>=1;i--){
		t++;
		if(!mark[s[i]]) dfs2(s[i]); //找强连通分量
	}
	cnt=0;
	memset(head,0,sizeof(head)); //重新建图
	for(int i=1;i<=t;i++){
		add(mark[u[i]],mark[v[i]]);
		add(mark[v[i]],mark[u[i]]);
		if(c[i]>1) circle=i; //标记环
	}
	memset(vis,0,sizeof(vis));
	dfs3(circle,0); //第三次dfs，求距离
	for(int i=1;i<=n;i++)
		if(mark[i]!=circle) printf("%d ",ans[mark[i]]);
		else printf("0"); //原来在环上的点距离为0
	return 0;
}
```


---

