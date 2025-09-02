# [ABC397G] Maximize Distance

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc397/tasks/abc397_g

给定一个包含 $N$ 个顶点和 $M$ 条边的有向图。顶点编号为 $1,2,\dots,N$，其中第 $j$ 条边（$j=1,2,\dots,M$）从顶点 $u_j$ 指向顶点 $v_j$。保证从顶点 $1$ 到顶点 $N$ 是可达的。

初始时，所有边的权重均为 $0$。当从 $M$ 条边中恰好选择 $K$ 条边并将其权重改为 $1$ 时，求修改后的图中顶点 $1$ 到顶点 $N$ 的最短距离的最大可能值。

## 说明/提示

### 约束条件

- $2 \leq N \leq 30$
- $1 \leq K \leq M \leq 100$
- $1 \leq u_j, v_j \leq N$
- $u_j \neq v_j$
- 给定图中，顶点 $1$ 到顶点 $N$ 是可达的
- 输入均为整数

### 样例解释 1

若选择边 $1$ 和 $3$，则顶点 $1$ 到顶点 $3$ 的最短距离为 $1$。由于不存在使最短距离达到 $2$ 或更大的选择方式，因此答案为 $1$。

### 样例解释 2

若选择边 $1$、$2$ 和 $4$，则顶点 $1$ 到顶点 $4$ 的最短距离为 $2$。由于不存在使最短距离达到 $3$ 或更大的选择方式，因此答案为 $2$。

### 样例解释 3

请注意图中可能存在多重边。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3 3 2
1 2
2 3
1 3```

### 输出

```
1```

## 样例 #2

### 输入

```
4 4 3
1 2
1 3
3 2
2 4```

### 输出

```
2```

## 样例 #3

### 输入

```
2 2 1
1 2
1 2```

### 输出

```
0```

# 题解

## 作者：forgive_ (赞：6)

发现一个题解区没有的做法！

求最短距离的最大值，考虑二分答案 $mid$，问题转化为使得最短距离 $\geq mid$ 最少修改几次。

看数据范围大胆猜测是网络流，但网络流貌似不太好刻画最短路这种东西。

那么考虑对偶，把限制写出来。

我们设 $x_i$ 表示第 $i$ 条边修改后的权值，那么首先要求：
$$x_i\leq 1$$
把限制看成“任意一条 $1$ 到 $n$ 的路径的边权和大于等于 $mid$”，那么：

$$x_{i_1}+x_{i_2}+...+x_{i_k}\geq mid$$

其中 $\left \{i_1,i_2,...i_k  \right \}$构成一条从 $1$ 到 $n$ 的路径。

我们需要求的是 $\sum x_i$ 的最小值。

对偶，设 $Q_i$ 为第一种限制，$P_i$ 为第二种限制，可以得到：

$$P_{j_1}+P_{j_2}+...+P_{j_k}\leq 1+Q_i$$

其中路径 $j_1,j_2,...j_k$ 都经过第 $i$ 条边。

求的是 $mid\sum\limits_j P_j-\sum\limits_i Q_i$ 的最大值。

接下来给这个式子编意义，看成是“每从 $1$ 号点走到 $n$ 号点一次就会获得 $mid$ 的收益，每条边初始只能经过一次，但可以花费 $1$ 的代价使得某条边可以经过的次数 $+1$”。

这个问题显然可以用费用流解决，具体来说：

- 设 $S$ 为 $1$ 号点，$T$ 为新建 $n+1$ 号点。

- 连边 $(n,T,\inf,mid)$，这是走到 $n$ 的收益。

- 对原图中每条边 $(x,y)$，连边 $(x,y,1,0)$,$(x,y,\inf,-1)$。

最后跑最大费用任意流即可，当费用为负时 `break` 出去。

**赛时代码：**

```cpp
#include<bits/stdc++.h>
using namespace std ;

typedef long long LL ;
const int N = 1010 , M = 1010 , inf = 0x3f3f3f3f ;
 
int n , m , S , T , K ;
struct nn
{
	int lst , to , val , c ;
}E[M<<1] ;
int head[N] , tot = 1 ;
inline void add( int x , int y , int v , int c )
{
	E[++tot] = (nn){head[x],y,v,c} ;
	head[x] = tot ;
}
queue<int> q ;
int f[N] , dis[N] , pre[N] ;
bool vis[N] ;
bool spfa( int S , int T )
{
	memset( dis , 0xcf , sizeof dis ) ;
	dis[S] = 0 , f[S] = 1e8 , vis[S] = 1 , pre[S] = 0 ;
	q.push(S) ;
	while( !q.empty() ) {
		int x = q.front() ; q.pop() ;
		vis[x] = 0 ;
		for(int i = head[x] ; i ; i = E[i].lst ) {
			int t = E[i].to ;
			if( E[i].val && dis[x]+E[i].c > dis[t] ) {
				f[t] = min( f[x] , E[i].val ) ;
				dis[t] = dis[x]+E[i].c ; pre[t] = i ;
				if( !vis[t] ) q.push(t) , vis[t] = 1 ;
			}
		}
	}
	return dis[T]>0 ;
}
int u[M] , v[M] ;
bool check( int V )
{
	memset( head , 0 , sizeof head ) ;
	tot = 1 ;
	S = 1 , T = n+1 ;
	for(int i = 1 ; i <= m ; i ++ ) {
		add(u[i],v[i],1,0) ; add(v[i],u[i],0,0) ;
		add(u[i],v[i],1e8,-1) ; add(v[i],u[i],0,1) ;
	}
	add(n,T,1e8,V) ;
	add(T,n,0,-V) ;
	int answ = 0 , ansc = 0 ;
	while( spfa(S,T) ) {
		if( dis[T]<=0 || ansc>K ) break ;
		answ += f[T] , ansc += f[T]*dis[T] ;
		for(int u = T ; u != S ; u = E[pre[u]^1].to ) {
			E[pre[u]].val -= f[T] , E[pre[u]^1].val += f[T] ;
		}
	}
	return ansc<=K ;
}

int main()
{
	scanf("%d%d%d" , &n , &m , &K ) ;
	for(int i = 1 ; i <= m ; i ++ ) {
		scanf("%d%d" , &u[i] , &v[i] ) ;
	}
	int l = 0 , r = n , mid ;
	while( l+1 < r ) {
		mid = (l+r)>>1 ;
		if( check(mid) ) l = mid ;
		else r = mid ;
	}
	if( check(r) ) printf("%d\n" , r ) ;
	else printf("%d" , l ) ;
	return 0 ;
}
```

---

## 作者：_zuoqingyuan (赞：5)

# 思路分析

数据范围很小，考虑网络流。

首先二分 $d$，转化为判定能否在进行不超过 $k$ 次操作的前提下，使 $1$ 到 $n$ 的最短距离**大于** $d$。

然后拆点，对于一个点 $x$，我们将其拆成 $(d+1)$ 个点 $(x,y)$，表示从 $1$ 到达 $x$，距离为 $y$。对于原图中的任意一条边 $u\to v$：

- 对于所有 $0\le D\le d$，连接一条容量为 $1$，从 $(u,D)\to (v,D)$ 的边。

- 对于所有 $0\le D<d$，连接一条容量为 $+\infty$，从 $(u,D)\to (v,D+1)$ 的边。

设原点为 $s$，汇点为 $t$。则：

- 连接一条容量为 $+\infty$，从 $s\to (1,0)$ 的边。

- 对于所有 $0\le D\le d$，连接一条容量为 $+\infty$，从 $(n,D)\to t$ 的边。

跑最大流，求出网络的最小割，最小割的值即是使 $1$ 到 $n$ 最短路径大于 $d$ 的最小操作数。

--------------------

解释一下原理。

要想让 $1$ 到 $n$ 的最短距离大于 $d$，等价于割掉网络中的一些边，使得 $s,t$ 不联通。

割掉一条边等价于让一条边的权重从 $0$ 变为 $1$。实际上，我们只有可能割掉容量为 $1$ 的边，即 $(u,D)\to (v,D)$ 的边，这样从 $u\to v$ 就必须走 $(u,D)\to (v,D+1)$ 这条边。此时一次操作的代价 $1$ 即和割掉边的容量相同。因为边的边权至多增加 $1$，所以 $(u,D)\to (u,D+1)$ 这中边的容量是 $+\infty$，防止被割断。

**这几天一直在想的一个问题**：$u\to v$ 这条边在网络中对应 $D+1$ 条边，理想情况下，最优的方案只会割去其中一条。但最小割中有没有可能割去超过 $1$ 条边？

答案是否定的，假设在原图中有两条不一样的路径都经过了 $u\to v$ 的边，且到达 $u$ 点时移动的距离不一样。在网络中我们割去了 $(u,D_1) \to (v,D_1),(u,D_2)\to (v,D_2)$ 这两条边（$D_1<D_2$）。我们先思考第一条边 $(u,D_1) \to (v,D_1)$，因为最小割使得 $s,t$ 不联通，对应在原图中，此时这条路径从 $v$ 到 $n$ 的最短距离必然大于 $d-D_1-1$。

此时，哪怕第二条边不割，$v$ 的 $n$ 的最短路仍然满足 $d-D_1-1\ge d-D_2$。也就是说，第二条边割掉和没割都不会有任何改变。所以放弃割掉这条边，可以得到一个更小的割，与条件中的最小割矛盾，故原结论成立。

所以我们安心大胆的跑网络流就对了。


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=3005,M=60005,inf=1e9+7;
int n,m,k,s,t;
vector<int>G[35];
int ver[N],to[M],nxt[M],val[M],idx=1,d[N],now[N];
queue<int>q;
void clear(){
    memset(ver,0,sizeof(ver));
    memset(to,0,sizeof(to));
    memset(nxt,0,sizeof(nxt));
    memset(val,0,sizeof(val));
    memset(d,0,sizeof(d));
    memset(now,0,sizeof(now));
    idx=1;
}
void add(int x,int y,int z){
    to[++idx]=y,nxt[idx]=ver[x],ver[x]=idx,val[idx]=z;
    to[++idx]=x,nxt[idx]=ver[y],ver[y]=idx,val[idx]=0;
}
int id(int x,int y,int z){
    return (x-1)*(z+1)+y;
}
bool bfs(){
    while(q.size())q.pop();
    for(int i=0;i<=t;i++)d[i]=0,now[i]=ver[i];
    q.push(s),d[s]=1;
    while(q.size()){
        int x=q.front();q.pop();
        for(int i=ver[x];i;i=nxt[i]){
            if(val[i]&&!d[to[i]]){
                int y=to[i];
                d[y]=d[x]+1,q.push(y);
                if(y==t)return 1;
            }
        }
    }
    return 0;
}
int dinic(int x,int flow){
    if(x==t||!flow)return flow;
    int used=0,f,y;
    for(int i=now[x];i;i=nxt[i]){
        now[x]=i,y=to[i];
        if(val[i]&&d[y]==d[x]+1){
            f=dinic(y,min(val[i],flow-used));
            if(!f)d[y]=0;
            else val[i]-=f,val[i^1]+=f,used+=f;
            if(used==flow)break;
        }
    }
    return used;
}
bool check(int d){
    clear();s=n*(d+1)+1,t=n*(d+1)+2;
    add(s,id(1,0,d),inf);
    for(int i=0;i<=d;i++)add(id(n,i,d),t,inf);
    for(int i=1;i<=n;i++){
        for(auto j:G[i]){
            for(int k=0;k<=d;k++){
                add(id(i,k,d),id(j,k,d),1);
                if(k!=d)add(id(i,k,d),id(j,k+1,d),inf);
            }
        }
    }
    int maxflow=0;
    while(bfs())maxflow+=dinic(s,inf);
    return (maxflow<=k);
}
int main(){
    scanf("%d %d %d",&n,&m,&k);
    for(int i=1,u,v;i<=m;i++){
        scanf("%d %d",&u,&v);
        G[u].push_back(v);
    }
    int l=0,r=m;
    while(l<r){
        int mid=(l+r)>>1;
        if(check(mid))l=mid+1;
        else r=mid;
    }
    printf("%d\n",l);
    return 0;
}
```

有的人认为二分的范围是 $[1,n]$？不过我写的是 $[1,m]$。

这样建图点数大概是 $nm$ 级别，边数则是 $m^2$ 级别。时间复杂度 $O(n^2m^4\log n)$，Dinic 轻松应对。

如有错误，请指出。

---

## 作者：fydj (赞：4)

首先先懂得一个基础的网络流建模。如果有 $n$ 个物品，把它们分成两个集合 $S,T$，每个物品不放在 $S$ 集合的代价是 $a_i$，不放在 $T$ 集合的代价是 $b_i$，同时还有 $m$ 条限制，形如如果 $u$ 在 $S$ 且 $v$ 在 $T$，那么会产生 $w$ 的代价。可以用最小割求解。

建模如下：对于每个物品连边 $(S,i,a_i),(i,T,b_i)$，对于每条限制连边 $(u,v,w)$，跑最小割即可。

建模的意义是，割掉一些边后，如果和 $S$ 连通，就认为在 $S$ 集合里，反之认为在 $T$ 集合里。割掉 $(S,i,a_i)$ 表示 $i$ 不在 $S$ 中，代价是 $a_i$；反之割掉 $(i,T,b_i)$ 表示 $i$ 不在 $T$ 中，代价是 $b_i$；如果 $u$ 在 $S$ 中，$v$ 在 $T$ 中，那么 $(u,v,w)$ 必须要割掉，代价是 $w$。

对于这道题，可以先二分答案 $d$，对于每个点拆成 $d$ 个点，点 $x_{i,j}$ 表示 $[dis_i\ge j]$。那么要求 $x_{1,1}=0,x_{n,d}=1$，同时还有一些额外约束：

+ $(x_{i,j},x_{i,j+1},\inf)$，因为不能同时满足 $dis_{i}<j$ 和 $dis_{i}>j$。
+ 对于边 $(u,v)$，$(x_{u,j},x_{v,j},1)$，表示把 $(u,v)$ 的边权设为 $1$。
+ 对于边 $(u,v)$，$(x_{u,j},x_{v,j+1},\inf)$，因为不能满足 $dis_{u}<j$ 和 $dis_{v}>j$，此时 $dis_v-dis_u>1$，不满足最短路。

于是直接利用上面的算法即可。

---

## 作者：Milthm (赞：4)

极其困难的题目，需要较高的网络流建模能力，这里参考了官方题解。

____

首先 $n\le 30$，再加上这是一个看上去很难做的最值问题，很像一个网络流题。那么我们首先需要做的就是二分答案，转化为判定问题：求是否可以在 $k$ 步内使得 $1$ 到 $n$ 的最短路不小于 $d$，接下来开始尝试网络流。

直接建模比较困难，可以先从简单情况考虑：

### $d=1$ 时

我们肯定是要让 $1$ 到 $n$ 的最短路不小于 $d$ 的操作步数最少，那么对于这个 $d=1$，我们发现必须让 $1$ 到 $n$ 的每条路径都至少有一个 $1$ 才能满足条件。也就是说，如果把每次操作的“改为 $1$”看作“删除”，那么问题就是求最小的步数使得 $1$ 和 $n$ 不连通。我们发现这就是一个最小割问题，可以直接解决。

### 一般情况

刚才 $d=1$ 的最小割转化给了我们很大的启发，我们考虑把一般情况也转化为最小割。

我们发现刚才的 $d=1$ 可以转化为一个赋值问题，即设 $a_i$ 表示 $1$ 到 $i$ 的最短路长度，那么对于每条边 $(u,v)$，只有当 $a_u=0$ 且 $a_v=1$ 时，这条边才是被选取的。设这种情况的代价为 $1$，其它为 $\inf$，再强制令 $a_1=0$，$a_n=1$。那么这个问题可以转化为最小割求解，也就是我们刚才说的。

那么现在一般情况仍然可以转化为赋值问题，还是设 $a_i$ 表示 $1$ 到 $i$ 的最短路长度，则对于每条边 $(u,v)$，若 $a_v=a_u+1$，则这条边的代价为 $1$。若 $a_v>a_u+1$，则代价为正无穷（因为这是不可能的），$a_v<a_u+1$ 则是不选，从而不需要考虑。然后钦定 $a_1=0$，$a_n=d$，即转化为求所有赋值方案里代价的最小值。

但问题是这个问题并不能使用最小割解决，因为 $a$ 的值并不是和 $d=1$ 时一样只有 $0$ 和 $1$，所以考虑拆点，将 $a_i$ 拆为 $b_{i,1},\cdots ,b_{i,d}$，$b_{i,j}=[j\le a_i]$。

那么现在就是要满足以下限制：

- 若赋值 $b_{i,j}=0$，$b_{i,j+1}=1$，则代价为正无穷，因为这是不可能的。

- 对于每条边 $(u,v)$，若赋值 $b_{u,j}=0$，$b_{v,j}=1$，则代价为 $1$，对应刚才 $a_v=a_u+1$ 的情况。

- 对于每条边 $(u,v)$，若赋值 $b_{u,j}=0$，$b_{v,j+1}=1$，则代价为正无穷，对应刚才 $a_v>a_u+1$ 的情况。

- $b_{1,1}=0$，$b_{n,d}=1$。

现在问题变成了一个值域为 $0,1$ 的赋值最小代价问题了。我们可以建一个 $nd$ 个点的图，把每种赋值条件连上对应代价的边，那么我们需要让 $b_{1,1}$ 和 $b_{n,d}$ 不在一个集合里，也就是我们常说的最小割问题了。

于是采用 Dinic 跑最大流，尽管理论时间复杂度高达 $O(n^5(n+m)\log n)$，但是实际上可以通过。

代码里第二维减了个一，问题不大。


```cpp
#include<bits/stdc++.h>
#define N 500005
using namespace std;
int n,s,t,inf=1e5,h[N],num=1,dis[N],cur[N],ans;
int nn,mm,u[N],v[N],k;
struct edge{
	int u,v,w,nxt;
}e[N];
void qwq(int u,int v,int w){
	e[++num]={u,v,w,h[u]};h[u]=num;
}
void add(int u,int v,int w){
	qwq(u,v,w);qwq(v,u,0);
}
int bfs(){
	for(int i=1;i<=n;++i)dis[i]=inf;
	queue<int>q;
	q.push(s);dis[s]=0;cur[s]=h[s];
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=h[u];i;i=e[i].nxt){
			int v=e[i].v;
			if(e[i].w>0&&dis[v]==inf){
				q.push(v);
				cur[v]=h[v];dis[v]=dis[u]+1;
				if(v==t)return 1;
			}
		}
	}
	return 0;
}
int dfs(int u,int sum){
	if(u==t)return sum;
	int ans=0;
	for(int i=cur[u];i&&sum;i=e[i].nxt){
		cur[u]=i;int v=e[i].v;
		if(e[i].w>0&&dis[v]==dis[u]+1){
			int minn=dfs(v,min(sum,e[i].w));
			if(!minn)dis[v]=inf;
			e[i].w-=minn;e[i^1].w+=minn;
			ans+=minn;sum-=minn;
		}
	}
	return ans;
}
int go(int x,int y){
	return x*nn+y;
}
bool check(int mid){
	num=1;memset(h,0,sizeof(h));memset(cur,0,sizeof(cur));
	s=nn*nn*2,t=s+1;n=t;
	for(int i=1;i<=nn;++i){
	//	add(s,go(i,mid),inf);
		for(int j=0;j<mid;++j)add(go(i,j),go(i,j+1),inf);
	}
	add(s,go(1,0),inf);add(go(nn,mid-1),t,inf);
	for(int i=1;i<=mm;++i){
		for(int j=0;j<mid;++j){
			add(go(u[i],j),go(v[i],j),1);add(go(u[i],j),go(v[i],j+1),inf);
		}
	}
	ans=0;
	while(bfs())ans+=dfs(s,inf);
	return ans<=k;
}
int main(){
	cin>>nn>>mm>>k;
	for(int i=1;i<=mm;++i)cin>>u[i]>>v[i];
	int l=0,r=nn-1,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))l=mid+1,ans=mid;
		else r=mid-1;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：SukiYuri (赞：2)

# ABC397G 题解

## 分析

好题，做过类似的，但赛时没有看出来挺可惜的。

考虑什么时候最短路不为 $0$，发现这等价于求原图的最小割，因此原问题不弱于最小割问题，让我们考虑网络流。

考虑把图分层，如果最短路为 $p$，则相当于以第 $1$ 层的 $1$ 为源点，第 $p$ 层的 $n$ 为汇点最小割，如果第 $i$ 层的第 $j$ 条边 $u_{i,j} \rightarrow v_{i,j}$ 被割了那么通过 $u_{i,j}$ 的流就流向 $v_{i,j+1}$。因为最短路长度小于 $n$，因此只需要建 $n-1$ 层就可以。

建图流程如下：

1. 假设原图有一条边 $u \rightarrow v$ 
2. 对 $i \in[1,n-1]$ 层，加边 $u_i\rightarrow v_i$，容量为 $1$
3. 对 $i\in[1,n-2]$ 层，加边 $u_i\rightarrow v_{i+1}$，容量为 $+\infty$

下图是对图 
```
Vertex=5 Edge=6
1 -> 2
1 -> 3
1 -> 4
2 -> 5
3 -> 5
4 -> 5
```
的建图示例（黄色边容量为 1，灰色边容量为无穷大）：
![](https://cdn.luogu.com.cn/upload/image_hosting/iz39lo35.png)
简单说明一下正确性，考虑这样的二元组 $u_i\rightarrow v_{i+1}$，其中 $u_i$ 在第 $i$ 层，$v_{i+1}$ 在第 $i+1$ 层。如果我们不割掉边 $u \rightarrow v$ 则原图有 $1 \rightarrow u \rightarrow v$ 使得 $1\rightarrow v$ 的路径权值为 $i$，因此 $1 \rightarrow n_{i}$ 的最小割即为使得路径权值为 $i$ 的最小花费。

于是可以二分解决问题。应当注意的是，二分的上界应为 $1\sim n$ 最短路的长度，如果取 $n$ 为上界，则可能会出现最小割为 $0$  的情况（示例如上图中 $1\sim 25$，$1\sim 20$）的最小割。

## 代码

```cpp
#include "iostream"
#include "cstdio"
#include "queue"
#include "cstring"
using namespace std;
int n,m,k;
const int maxn=1000,maxm=6005,inf=1e9+7;
struct Graph {
    int S,T,hd[maxn],t[maxm<<1],nx[maxm<<1],fl[maxm<<1],tt;
    int dep[maxn],cur[maxn];
    Graph() {tt=1;}
    inline void add(int u,int v,int f) {
        nx[++tt]=hd[u];t[tt]=v,fl[tt]=f,hd[u]=tt;
    }
    inline bool bfs() {
        memset(dep,0,sizeof dep);
        memcpy(cur,hd,sizeof hd);
        queue<int> q; dep[S]=1; q.push(S);
        while(!q.empty()) {
            int u=q.front(); q.pop();
            for(int i=hd[u];i;i=nx[i]) {
                if(dep[t[i]]||!fl[i]) continue;
                dep[t[i]]=dep[u]+1;
                if(t[i]==T) return 1;
                q.push(t[i]);
            }
        }
        return dep[T];
    }
    int dfs(int u,int f) {
        if(u==T||!f) return f;
        int x=0,y=f;
        for(int &i=cur[u];i;i=nx[i]) {
            if(dep[t[i]]!=dep[u]+1||!fl[i]) continue;
            int res=dfs(t[i],min(y,fl[i]));
            fl[i]-=res; fl[i^1]+=res;
            x+=res; y-=res;
            if(!y) break;
        }
        if(x==f) dep[u]=-1;
        return x;
    }
    inline int dinic() {
        int res=0;
        while(bfs()) res+=dfs(S,inf);
        return res;
    }
}G,_G;
inline bool chk(int b) {
    G=_G; G.T=b*n;
    if(!b||G.dinic()<=k) return 1;
    return 0;
}
int main() {
    ios::sync_with_stdio(0);
    cin>>n>>m>>k;
    for(int i=1;i<=m;++i) {
        int u,v; cin>>u>>v;
        for(int j=0;j<n;++j) {
            G.add(u+j*n,v+j*n,1);
            G.add(v+j*n,u+j*n,0);
            if(j!=n-1) {
                G.add(u+j*n,v+(j+1)*n,inf);
                G.add(v+(j+1)*n,u+j*n,0);
            }
        }
    }
    G.S=1; G.T=n; _G=G; G.bfs();
    int l=0,r=G.dep[n]-1,ans=0;
    while(l<=r) {
        int mid=l+r>>1;
        if(chk(mid)) {
            ans=mid,l=mid+1;
        } else r=mid-1;
    }
    cout<<ans;
    return 0;
}
```

附上 [AC 记录](https://atcoder.jp/contests/abc397/submissions/63872006)。

The end.

---

## 作者：emmoy (赞：1)

这里有一个不用二分的做法。

首先我们**枚举**答案 $d$，同其他题解，当 $d=1$ 时，答案就为原图的最小割。

我先抛出我的建图，正确性一会再讲。

- 对于一个 $d$，我们首先建出 $d$ 个题目中的图，所有边容量都为 $1$。

- 然后源点 $S$ 向每个图中的点 $1$ 都连一条容量为 $\inf$ 的边。

- 再将每个图中的点 $N$ 都向汇点 $T$ 连一条容量为 $\inf$ 的边。

- 最后对于原图的每一条边 $(u,v)$ 和 $1\leqslant i<d$ 的每个 $i$，将第 $i$ 个图的点 $u$ 向第 $i+1$ 个图的点 $v$ 连一条容量为 $inf$ 的边。

相信前三种边大家都很容易理解，并且也知道最后一种边是为了使每条边至多只割一次。

考虑连第四种边的正确性。

给一个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/7h5nmo9g.png)

其中 $u$ 和 $v$ 是一个图，剩下四个点是另一个图。

考虑如果 $(u,v)$ 在上一个图被割了，那么这个图再割 $(u_2,v_2)$ 也没用了，因为后面还有一个或多个 $(x,y)$ 割掉才能使 $S$ 与 $T$ 不连通，那么 $(u_2,v_2)$ 割了不如不割。

所以就可以使每条边至多只割一次。

最后，由于一个 $d$ 可以从 $d-1$ 的残量网络加一些边而来，而不用重新建图，所以就相当于跑了一次 $n^2$ 个点，$nm$ 条边的 dinic，但会多一些常数，所以时间复杂度为 $O(n^5m)$，但由于是边权只有 $1$ 或 $\inf$，于是常数很小，最慢的测试点跑了不到 5ms。

### code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf=1e7;
int n,m,k;
int h[100010],cnt=1;
struct node{
	int to,next,flow;
}edge[100010];
void add(int x,int y,int z){
	edge[++cnt]={y,h[x],z},h[x]=cnt;
	edge[++cnt]={x,h[y],0},h[y]=cnt;
}
int s,t;
int dis[100010],c[100010];
bool bfs(){
	for(int i=s;i<=t;i++) dis[i]=0,c[i]=h[i];
	queue<int> q;
	q.push(s),dis[s]=1;
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=h[x];i;i=edge[i].next){
			int v=edge[i].to;
			if(!dis[v]&&edge[i].flow){
				dis[v]=dis[x]+1;
				q.push(v);
			}
		}
	}
	return dis[t]!=0;
}
int dfs(int x,int limit){
	if(!limit||x==t) return limit;
	int res=0;
	for(int&i=c[x];i;i=edge[i].next){
		int v=edge[i].to;
		if(dis[v]==dis[x]+1&&edge[i].flow){
			int p=dfs(v,min(limit-res,edge[i].flow));
			res+=p,edge[i].flow-=p;
			edge[i^1].flow+=p;
		}
	}
	if(res==limit) dis[x]=0;
	return res;
}
int xx[120],yy[120];
int dinic(){
	int sum=0;
	while(bfs()){
		while(int l=dfs(s,inf)) sum+=l;
	}
	return sum;
}
signed main(){
	cin>>n>>m>>k;
	t=(n+2)*n+1;
	add(s,1,inf),add(n,t,inf);
	for(int i=1;i<=m;i++){
		cin>>xx[i]>>yy[i];
		add(xx[i],yy[i],1);
	}
	int sum=dinic();
	if(sum>k) return cout<<0,0;
	for(int i=2;i<=n+2;i++){
		for(int j=1;j<=m;j++){
			add(xx[j]+(i-2)*n,yy[j]+(i-1)*n,inf);
			add(xx[j]+(i-1)*n,yy[j]+(i-1)*n,1);
		}
		add(s,(i-1)*n+1,inf),add(i*n,t,inf);
		sum+=dinic();//注意是+=
		if(sum>k) return cout<<i-1,0;
	}
	return 0; 
}
```

---

## 作者：Dream_poetry (赞：1)

### 思路：

看到 $n$ 和 $m$ 的范围，大胆猜测网络流，但是先持保留意见。

在仔细看一眼题面，不难想到二分答案。

考虑若答案为 $1$，检验是否成立只需要在原图上跑一遍最小割。

推广到更加广泛的情况，我们进而联想到分层建图。

此时，我们对于当前进行 ```check()``` 的 $x$，考虑建 $x$ 层的分层图，每一层往下的流量设置为 $\inf$，每一层内部流量为 $1$。

这个时候如果起点和终点之间，存在一条长度小于 $x$ 的路径，所求的最小割必然很大，无法满足条件，符合我们的要求。

反之，我们考虑在此分层图上跑最小割，并将所得到的结果和 $k$ 进行比较。

最后将二分得到的答案输出即可。

**一定要注意每次建图前要清空旧图！**

### 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf=1e9;
int n,m;
struct node{
	int nex,to,val;
}e[1000005];
int tot;
int s,t;

int he[1000005];
int now[1000005];


inline void add(int x,int y,int w){
	e[++tot].nex=he[x];
	e[tot].to=y;
	e[tot].val=w;
	he[x]=tot;
}

int dis[1000005];

inline int bfs(){
	queue<int>q;
	for (int i=0;i<=1000000;i++){
		dis[i]=inf;
	}
	q.push(s);
	dis[s]=0;
	now[s]=he[s];
	while (q.size()){
		int x=q.front();
		q.pop();
		for (int i=he[x];i;i=e[i].nex){
			int v=e[i].to;
			int w=e[i].val;
			if (w>0 && dis[v]==inf){
				dis[v]=dis[x]+1;
				now[v]=he[v];
				q.push(v);
				if (v==t){
					return 1;
				}
			}
		}
	}	
	return 0;
}

inline int dfs(int x,int sum){
	if (x==t){
		return sum;
	}
	int res=0;
	for (int i=now[x];i && sum;i=e[i].nex){
		now[x]=i;
		int v=e[i].to;
		int w=e[i].val;
		if (dis[v]==dis[x]+1 && w>0){
			int k=dfs(v,min(sum,w));
			if (k==0){
				dis[v]=inf;
			}
			e[i].val-=k;
			e[i^1].val+=k;
			sum-=k;
			res+=k;
		}
	}
	return res;
}

inline int dinic(){
	int ans=0;
	while(bfs()){
		ans+=dfs(s,inf);
	}
	return ans;
}


int x[100005];
int y[100005];
int Maxk;

inline int check(int dep){
	for (int i=1;i<=1000000;i++){
		he[i]=0;
		now[i]=0;
	}
	tot=1;
	for (int k=1;k<=dep;k++){
		for (int i=1;i<=m;i++){
			add(x[i]+(k-1)*n,y[i]+(k-1)*n,1);
			add(y[i]+(k-1)*n,x[i]+(k-1)*n,0);
			if (k<dep){
				add(x[i]+(k-1)*n,y[i]+k*n,inf);
				add(y[i]+k*n,x[i]+(k-1)*n,0);
			}
		}
		if (k<dep){
			add(k*n,(k+1)*n,inf);
			add((k+1)*n,k*n,0);
		}
	}
	s=1;
	t=n*dep;
	return dinic()<=Maxk;
}

signed main(){
	cin>>n>>m>>Maxk;
	for (int i=1;i<=m;i++){
		cin>>x[i]>>y[i];
	}	
	int l=0;
	int r=n-1;
	while (l<r){
		int mid=(l+r+1)/2;
		if (check(mid)){
			l=mid;
		}
		else{
			r=mid-1;
		}
	}
	cout<<l;
	
	
	return 0;
}
```

---

## 作者：xiezheyuan (赞：1)

月考考完了（但是炸了），于是看了一下最近的 ABC G。

## 简要题意

给出一个 $n$ 个点 $m$ 条边的有向图，初始时这些边的边权均为 $0$。

你需要选定恰好 $k$ 条边将其边权改为 $1$，使得 $1$ 到 $n$ 的最短路长度最大（保证 $1\to n$ 连通）。

$2\leq n\leq 30,1\leq k\leq m\leq 100$。

## 思路

看到最小值最大，先二分，改为判定性问题：能否选定恰好 $k$ 条边，将其边权改为 $1$ 后，$1$ 到 $n$ 的最短路长度不小于 $x$。

首先可以发现这个“恰好”是假的，假如能够选定 $x$ 条边达成目标，则选定 $x+1$ 条边一定也可以。于是将限制改为至多 $k$ 条边。

然后发现最短路这个信息不好维护？不妨暴力一点，直接维护点 $i$ 的最短路 $d_i$。

那么我们相当于有 $n$ 个变量 $d$，需要满足一定的限制，使得 $d_1=0$ 且 $d_n\geq x$。

根据最短路的定义，应该只有这一条限制：对于边 ${(u,v)}$，${d_v\leq d_u+1}$。

另外如果 $d_v=d_u+1$，那么我们需要连一条边 $(u,v)$ 而需要 $1$ 的代价。我们需要最小化代价。

于是我们貌似需要解决一个 LP 问题？不过我不会单纯形，不过既然想到了 LP，那么就自然可以想到网络流。

根据图论建模的经典技巧（[AT_abc277_h \[ABC277Ex\] Constrained Sums](https://www.luogu.com.cn/problem/AT_abc277_h)），**我们可以将一个整数变量看成 $O(V)$ 个布尔变量。具体地，对于变量 $x$，可以改为记录若干个变量 $x_i=[x\geq i]$。**

对应到本题中，我们可以记录 $O(n^2)$ 个变量 $d_{ij}=[d_i\geq j]$。那么可以得到一个形如下面的问题：

> 有一个 $n$ 个点 $m$ 条边的有向图图，限制某两个点分别为 $0/1$，你需要给其他点附一个 $01$ 值，对于原图上的边，若起点是 $1$ 且汇点是 $0$，则需要等同于边权的代价。你需要求出最小代价。

可以发现这个问题和最小割问题相同，于是求最小割即可。时间复杂度 $O(\mathrm{maxflow}(n^2,n^2+nm）))$。

[Submission](https://atcoder.jp/contests/abc397/submissions/63972048)。

---

## 作者：WuMin4 (赞：1)

## [[ABC397G] Maximize Distance](https://atcoder.jp/contests/abc397/tasks/abc397_g)

## 题意 

给出一个有向图，你需要选择 $k$ 条边让它们的边权为 $1$，剩余边的边权为 $0$。问 $1$ 到 $n$ 的最短路长度的最大值为多少。

## 思路

最短路最大值显然二分答案，考虑给出最短路的长度如何计算最少需要的边数。

若最短路长度等于 $1$，则问题就变为了选择最少的边使得从 $1$ 到 $n$ 的每条路径都经过至少一条这些边。

设两点之间仅当边权为 $0$ 时有边，则若 $1$ 可以到达 $n$，最短路长度为 $0$，所以问题又变成了删去最少的边使得 $1$ 不能到达 $n$。

于是可以建图，边的流量为 $1$，求最小割即可。

现在将该问题扩展到最短路长度不为 $1$ 的情况。设最短路长度为 $x$，于是我们建立 $x$ 层图。若第 $i$ 层有一条 $(x_i,y_i)$ 的边，则从第 $i$ 层向第 $i+1$ 层连 $(x_i,y_{i+1})$ 的边，流量为无限大。再将每层的 $n$ 号点向第一层的 $n$ 号点连边，流量同样为无限大，求最小割即可得到答案。

考虑为什么可以这么做。设跨层的边表示将路径长度加 $1$。若节点 $1$ 可以到达第 $i$ 层的 $n$ 号节点，则经过了 $i-1$ 条跨层的边，于是该层的最短路长度便为 $i-1$，显然不满足条件。所以该图的一个割一定满足第 $i$ 层的最短路长度为 $i$，于是求出最小割便求出了答案。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=20005,INF=0x3f3f3f3f;
struct node{
	int x,w,rev,id;
};
vector<node> t[N];
int dep[N],gap[N],maxflow;
int n,m,k,S,T;
void add(int x,int y,int w){
	t[x].push_back({y,w,t[y].size()});
	t[y].push_back({x,0,t[x].size()-1});
}
void bfs(){
	memset(gap,0,sizeof(gap));
	memset(dep,-1,sizeof(dep));
	queue<int> q;
	q.push(T),dep[T]=0,gap[dep[T]]++;
	while(!q.empty()){
		int u=q.front();q.pop();
		for(node v:t[u]){
			if(dep[v.x]==-1){
				dep[v.x]=dep[u]+1;
				gap[dep[v.x]]++,q.push(v.x);
			}
		}
	}
}
int dfs(int x,int flow){
	if(x==T){
		maxflow+=flow;
		return flow;
	}
	int used=0;
	for(int i=0;i<t[x].size();i++){
		int v=t[x][i].x;
		if(t[x][i].w&&dep[v]+1==dep[x]){
			int mn=dfs(v,min(t[x][i].w,flow-used));
			if(mn) t[x][i].w-=mn,t[v][t[x][i].rev].w+=mn,used+=mn;
			if(flow==used) return used;
		}
	}
	gap[dep[x]]--;
	if(!gap[dep[x]]) dep[S]=n*k+1;
	dep[x]++,gap[dep[x]]++;
	return used;
}
int isap(){
	maxflow=0;
	bfs();
	while(dep[S]<n*k) dfs(S,INF);
	return maxflow;
}
struct IN{
	int x,y;
}in[105];
bool check(int mid){
	for(int i=1;i<=n*k;i++)
		t[i].clear();
	for(int d=0;d<mid;d++){
		for(int i=1;i<=m;i++){
			add(d*n+in[i].x,d*n+in[i].y,1);
			if(d!=mid-1) add(d*n+in[i].x,(d+1)*n+in[i].y,INF);
		}
		if(d) add(d*n+n,n,INF);
	}
	return isap()<=k;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m>>k;
	S=1,T=n;
	for(int i=1;i<=m;i++)
		cin>>in[i].x>>in[i].y;
	int l=1,r=k,mid,res=0;
	while(l<=r){
		mid=(l+r)/2;
		if(check(mid))
			l=mid+1,res=mid;
		else
			r=mid-1;
	}
	cout<<res;
	return 0;
}
```

---

## 作者：2012_Zhang_ (赞：1)

# 思路解析

## Part 1
首先赛时没来得及看这题，看完后才知道错过了一道最小割好题。  
做法显然是最小割，首先尝试直接求解。  
经过一番苦思冥想后，这个想法暂时被 Pass 掉了。  
一个宛如救世主的算法涌上心头 —— 二分。  
没错，就是二分，只需二分答案，求出所需次数。  
很明显它符合单调性，将次数与 $K$ 对比即可。

## Part 2
既然已经想到二分，那么思考如何实现。   
接下来考虑如何建边，  
首先发现正常的建边方式已经无法满足需求，  
那么我们需要用到一个网络流建边时的一个重要的做法 —— 拆点。   
将每个点拆成 $P$ 层，第 $i$ 层的容量是答案为  $i$ 时所需修改的边数。  
在最小割中割掉一条边等价于将一条边的权值改为一。  
显然我们可以连两种边，一种容量为 $inf$ 连向下一层，一种流量为 $1$ 连向同一层。  
我们可以发现只会割去容量为 $1$ 的边，正好符合修改数 $+1$ 的代价。  
对于点 $n$ 在每层连上汇点 $T$，而点 $S$ 处于点第一层的点 $1$。  
至此，边全部连完，可以放心跑二分。  
（本蒟蒻写的第一道 G 题）  

奉上代码：
# AC CODE
~~~cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int inf=1e9;
const int maxn=5e5+5;
int tot=1,head[maxn],to[maxn],val[maxn],nxt[maxn],dep[maxn],now[maxn];
int n,m,k,u[maxn],v[maxn],s,t;
queue<int>q;
void add(int a,int b,int w){
	nxt[++tot]=head[a];
	to[tot]=b;
	val[tot]=w;
	head[a]=tot;
	swap(a,b);
	nxt[++tot]=head[a];
	to[tot]=b;
	val[tot]=0;
	head[a]=tot;
}
bool bfs(){
	for(int i=1;i<maxn;i++) dep[i]=inf;
	while(!q.empty()) q.pop();
	now[s]=head[s];
	dep[s]=0;
	q.push(s);
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=nxt[i]){
			int y=to[i];
			if(val[i]>0&&dep[y]==inf){
				dep[y]=dep[x]+1;
				now[y]=head[y];
				q.push(y);
				if(y==t) return 1;
			}
		}
	}
	return 0;
} 
int dfs(int x,int sum){
	if(x==t) return sum;
	int cnt,ans=0;
	for(int i=now[x];i&&sum>0;i=nxt[i]){
		now[x]=i;
		int y=to[i];
		if(val[i]>0&&dep[y]-dep[x]==1){
			cnt=dfs(y,min(sum,val[i]));
			if(cnt==0) dep[y]=inf;
			val[i]-=cnt;
			val[i^1]+=cnt;
			sum-=cnt;
			ans+=cnt;
		}
	}
	return ans;
}
int id(int a,int b){return a*n+b;}
bool dinic(int p){
	s=1,t=n*n+1;
	tot=1;
	memset(head,0,sizeof head);
	memset(now,0,sizeof now);
	memset(dep,0,sizeof dep);
	for(int i=1;i<=m;i++){
		for(int j=0;j<p;j++){
			if(j<p-1) add(id(j,u[i]),id(j+1,v[i]),inf);
			add(id(j,u[i]),id(j,v[i]),1);
			add(id(j,n),t,inf);
		}
	}
	int ans=0;
	while(bfs()){
		ans+=dfs(s,inf);
		if(ans>=inf) break;
	}
	return ans<=k;
}
signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++) cin>>u[i]>>v[i];
	int l=0,r=n,ans=-1;
	while(l<=r){
		int mid=(l+r+1)/2;
		if(dinic(mid)) l=mid+1,ans=mid;
		else r=mid-1;
	}
    cout<<ans;
	return 0;
}
~~~
## update
2025.3.26 修改了部分内容，感谢 @[masterhuang](https://www.luogu.com.cn/user/365021) 提出的意见

---
到看到这里了，给个赞吧。

---

## 作者：wmrqwq (赞：0)

这是一篇视频题解。

![](bilibili:BV1nyXkYtE3i)

[参考代码](https://atcoder.jp/contests/abc397/submissions/63886649)

---

