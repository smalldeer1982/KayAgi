# SAC E#1 - 一道难题 Tree

## 题目背景

冴月麟和魏潇承是好朋友。

## 题目描述

冴月麟为了守护幻想乡，而制造了幻想乡的倒影，将真实的幻想乡封印了。任何人都无法进入真实的幻想乡了，但是她给前来救她的魏潇承留了一个线索。

她设置了一棵树（有根）。树的每一条边上具有割掉该边的代价。

魏潇承需要计算出割开这棵树的最小代价，这就是冴月麟和魏潇承约定的小秘密。

帮帮魏潇承吧。


注：所谓割开一棵有根树，就是删除若干条边，使得任何叶子节点和根节点不连通。

## 说明/提示

### 数据范围及约定

- 对于 $20\%$ 的数据，$n\le 10$；
- 对于 $50\%$ 的数据，$n \le 1000$；
- 对于 $100\%$ 的数据，$2\le n \le 100000$，且边权是不大于 $10^6$ 的非负整数。

## 样例 #1

### 输入

```
4 1
1 2 1 
1 3 1
1 4 1```

### 输出

```
3```

## 样例 #2

### 输入

```
4 1
1 2 3
2 3 1
3 4 2```

### 输出

```
1```

# 题解

## 作者：_louhc (赞：27)

# P3931 SAC E#1 - 一道难题 Tree   

------

# 写在前面

lovny(YKJ):用树形DP呀？

Venus(LYT):还在做网络流？

。。。

没必要！完全没必要！这道题DFS就够了！

# 思路

很明显，要使一个叶子节点到不了祖先，有两种选择：

> 他的某个祖先到不了根节点
>
> 它父亲->它 删了

然后我们可以遍历一遍树。

DFS( x, fa ) = $\Sigma$min(DFS( i, x ) ( 存在边x->i), val(x->i) )

fa是为了避免搜到父亲节点。

若x为叶子节点，直接返回INF

也就是说，要么断开x->i让i到不了根节点，下面就不用再删边了，要么让i到的了根节点，在下面某处再断开。

他没说c的范围，保险起见开long long

代码很短。。。真的很短。。。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define open(s) freopen( s".in", "r", stdin ), freopen( s".out", "w", stdout )
#define MAXN 100005
#define MAXM 200005
#define LL long long

int n, S;
int hd[MAXN], to[MAXM], nxt[MAXM], tot(1);
LL val[MAXM];

void Add( int x, int y, int z ){
	nxt[++tot] = hd[x]; hd[x] = tot; val[tot] = z; to[tot] = y;
	nxt[++tot] = hd[y]; hd[y] = tot; val[tot] = z; to[tot] = x;
}

LL DFS( int x, int fa ){
	LL ans(0); bool flg(0);
	for ( int i = hd[x]; i; i = nxt[i] )
		if ( to[i] != fa ) ans += min( DFS( to[i], x ), val[i] ), flg = 1;
	if ( !flg ) return LONG_LONG_MAX;
	return ans;
}

int main(){
	scanf( "%d%d", &n, &S );
	for ( int i = 1; i < n; ++i ){
		int x, y; LL z;
		scanf( "%d%d%lld", &x, &y, &z );
		Add( x, y, z );
	}
	printf( "%lld\n", DFS( S, S ) );
	return 0;
}
```



---

## 作者：皎月半洒花 (赞：15)

唔嗯，只是提供一个新的思路。

随机跳题跳到了这题，觉得有点意思就花了$3min$给$A$掉了，并且似乎是个没人写过的思路……？

题目意思就是让从根到每个叶子的路径上有至少一条边被割。那么不妨设计一个zz状态$f_i$，$f_i$表示前$i$个叶子被割完的最小代价。转移的时候考虑借助$dfs$序。如果$dfn_x=dfn_{fa_x}+sz_{fa_x}-1$，那么就说明是本子树内$dfs$序最靠后的一个节点，那么就有转移

$$f_i=f_{i-ctn_{fa_x}}+cost_{fa_x}$$

其中$cost_x$表示与$fa_x$间连边的$val$，$ctn_x$表示$x$子树内有多少叶子。

也就是说我们可以通过删掉$fa$来搞掉这整棵子树。同理我们可以不断找深度更小的祖先，方法也大体类似。

下面说一下聚合分析出来的复杂度。不妨令$end_x$表示以$x$为根的子树内$dfn$序最大的点，如果$end_x=end_{fa_x}$那么我们令$end_x=x$，同时令$ofa(end_x)=x$。

那么对于每个$x$都有唯一的$end_x$，也只会在遍历到$end_x$的时候会向上回溯到$x$，那么总的复杂度就是$O(n+\sum({dep_x-dep_{end_x}}))$。考虑后一部分的复杂度，在同一棵大子树内，最劣的情况显然是对于每个叶子都要向上跳，这样的情况只会发生在下一个叶子的$ofa$恰是上一个叶子的$ofa$的$fa$。也就是第一个跳$1$，第二个跳$2$……注意这样最多跳$\sqrt n$次，所以第二部分的复杂度就是$1+2+3\cdots+\sqrt n=O(n)$（类似卡长链剖分的那种树）。

于是最后的复杂度为$O(n)+O(n)$.

233就当顺便练练复杂度分析了。

```cpp
void dfs(int u, int fr){
	bool fg = 1 ;
	dfn[u] = ++ Id, sz[u] = 1, fa[u] = fr ;
	for (int k = head[u] ; k ; k = next(k)){
		if (to(k) == fr) continue ;
		fg = 0, cost[to(k)] = val(k) ;
		dfs(to(k), u), sz[u] += sz[to(k)], ctn[u] += ctn[to(k)] ; 
	}
	if (fg) Ls[++ tot] = u, ctn[u] = 1 ;
}
int main(){
	cin >> N >> rt ; int i, j, u, v ;
	for (i = 1 ; i < N ; ++ i) 
		u = qr(), v = qr(), j = qr(), add(u, v, j) ; 
	dfs(rt, 0) ; 
	for (i = 1 ; i <= tot ; ++ i){
		int n = Ls[i], nid = dfn[n] ; 
		f[i] = f[i - 1] + cost[Ls[i]] ; 
		while (fa[n]){
			if (fa[n] != rt && nid == dfn[fa[n]] + sz[fa[n]] - 1) 
				f[i] = min(f[i], f[i - ctn[fa[n]]] + cost[fa[n]]) ; 
			else break ;
			n = fa[n] ;
		}
	}
	cout << f[tot] << endl ; return 0 ;
}
```




---

## 作者：YoungLove (赞：15)

**网络流做法**

这是个最小割问题，那么就对应的用最大流做法。

每一条边都对应的一个权值，对其建立网络流模型，跑一遍Dinic就是答案。

[Youngsc](https://youngscc.github.io/)

## 代码这里

```cpp
# include <algorithm>
# include <iostream>
# include <cstring>
# include <cstdio>
# include <queue>
# include <cmath>
# define R register
# define LL long long
# define inf 2000101900

using namespace std;

int n,root,x,y,z,h[100010],v[100010],used[100010],e=-1,t,ans;
struct zx{int v,flow,pre;}ed[300010];
queue <int> q;

template <typename T> void in(R T& a){
    R T x=0,f=1; R char c = getchar();
    while(!isdigit(c)){if(c == '-') f=-1; c = getchar();}
    while(isdigit(c)) x = (x<<1)+(x<<3)+c-'0',c = getchar();
    a = x*f;
}

template <typename T> void maxx(R T &a,const T b){a>b? 0:a=b;}
template <typename T> void minn(R T &a,const T b){a<b? 0:a=b;}

inline void add(R int x,R int y,R int z){
    ed[++e] = (zx){y,z,h[x]};
    h[x] = e;
}

inline void dfs(R int x,R int fa){
    R bool flag = 0;
    for(R int i=h[x]; i!=-1; i=ed[i].pre)
        if(fa != ed[i].v) flag = 1,dfs(ed[i].v,x),ed[i^1].flow = 0;
    if(!flag) add(x,t,inf),add(t,x,0);
}

inline bool bfs(){
    memset(v,0,sizeof(v));
    v[root] = 1;
    q.push(root);
    while(!q.empty()){
        R int x = q.front();
        q.pop();
        for(R int i=h[x]; i!=-1; i=ed[i].pre)
        {
            R int p = ed[i].v;
            if(v[p]||!ed[i].flow) continue;
            v[p] = v[x]+1;
            q.push(p);
        }
    }
    return v[t];
}

inline int maxflow(R int x,R int want){
    if(!want||x == t) return want;
    R int flow = 0;
    for(R int i=used[x]; i!=-1; i=ed[i].pre,used[x]=i)
    {
        R int p = ed[i].v;
        if(v[p] == v[x]+1&&ed[i].flow)
        {
            R int f = maxflow(p,min(want,ed[i].flow));
            if(!f) continue;
            want -= f;
            flow += f;
            ed[i].flow -= f;
            ed[i^1].flow += f;
        }
    }
    return flow;
}

int main(){
    memset(h,-1,sizeof(h));
    in(n),in(root);
    t = n+1;
    for(R int i=1; i<n; ++i) in(x),in(y),in(z),add(x,y,z),add(y,x,z);
    dfs(root,-1);
    while(bfs()){
        memcpy(used,h,sizeof(h));
        ans += maxflow(root,inf);
    }
    printf("%d",ans);
}
```

---

## 作者：TLEphage (赞：10)

# 没有EK的话 ~~我来水一波qwq~~

**[题意](https://www.luogu.org/problemnew/show/P3931):给出一棵树，树上所有边都有值。如果取走边上的值就能使边消失，要求取最小的数使所有叶子结点与根分离。**

由于最近在学网络流，就不用dfs了。~~（我还咕了好久）~~**[$\color{red}\text{推荐blog}$](https://blog.csdn.net/qq_41357771/article/details/79416899) 结论：最小割问题用最大流解**

分析：如果再给一个n+1的点作为网络流的汇点，连接叶子结点就大致能构造出一个网络流，那就是裸的最小割问题了。



------------




### 那么存在几个问题：

1、树是无向图，而网络流是有向图，怎么判断方向呢？

2、怎么判断叶子结点呢？

------------


1、我们先不要给边赋值，先存在一个数组里，等判断后再给正向边赋值。

2、判断叶子结点只需在判断方向后用数组$value[]$存入**作为边的起始点的次数**

--那怎么判断方向呢？

--把图建出来你就会发现，树的方向就是从根到叶子结点，用一遍$dfs$确定$value$就行了

## 代码如下：

```cpp
bool qwq[N];
int pd[N],value[N];
void dfs(int x)//从根开始开始
{
    qwq[x]=1; //标记遍历过
    for(ri i=head[x];i;i=edge[i].nex)
    {
        if(qwq[edge[i].v]==1) continue; //防止反向遍历
        dfs(edge[i].v); //搜下一个点
        pd[x]++; //作为边的起始点的次数+=1
        edge[i].val=value[i|1]; //给正向边赋值（value的存入顺序见下方代码）
    }
}
```

### 然后连接叶子结点和n+1:

```cpp
for(ri i=1;i<=n;++i) if(pd[i]==0) add(i,t,inf),add(t,i,0);
```



------------

## 完整建图:

```cpp
int n,s,t;
bool qwq[N];
int head[N],value[N],tot=1;
struct Edge{int u,v,val,nex;}edge[N<<1];
int pd[N];
int gi()
{
    int s=0;char ch=getchar();
    while(!(ch>='0'&&ch<='9')) ch=getchar();
    while(ch>='0'&&ch<='9') {s=s*10+ch-'0';ch=getchar();}
    return s;
}
void add(int u,int v,int val)
{
    edge[++tot].u=u;
    edge[tot].v=v;
    edge[tot].val=val;
    edge[tot].nex=head[u];
    head[u]=tot;
}
void dfs(int x)
{
    qwq[x]=1;
    for(ri i=head[x];i;i=edge[i].nex)
    {
        if(qwq[edge[i].v]==1) continue;
        dfs(edge[i].v);
        pd[x]++;
        edge[i].val=value[i|1];//如果i=2，那么反向边是edge[3],正向边edge[2].val=value[3]
    }
}
int main()
{
    n=gi(),s=gi(),t=n+1;
    for(ri i=1;i<=n-1;++i)
    {
        int u=gi(),v=gi();
        add(u,v,0);
        add(v,u,0);
        value[tot]=gi();//tot=3,5,7
    }
    dfs(s);
    for(ri i=1;i<=n;++i) if(pd[i]==0) add(i,t,inf),add(t,i,0);
}
```

## 最后套EK模板就行了（是不是很容易）


```cpp
// luogu-judger-enable-o2
#include<cstdio>
#include<queue>
#define ri register int
using namespace std;
const int N = 2e5;
const int inf = 1<<30;
int n,s,t;
bool qwq[N];
inline int gi()
{
    int s=0;char ch=getchar();
    while(!(ch>='0'&&ch<='9')) ch=getchar();
    while(ch>='0'&&ch<='9') {s=s*10+ch-'0';ch=getchar();}
    return s;
}
inline int min(int a,int b){if(a<b) return a;return b;}
int head[N],value[N],tot=1;
struct Edge{int u,v,val,nex;}edge[N<<1];
int pd[N];
inline void add(int u,int v,int val)
{
    edge[++tot].u=u;
    edge[tot].v=v;
    edge[tot].val=val;
    edge[tot].nex=head[u];
    head[u]=tot;
}
bool vis[N];
struct Pre{int v/*前一个点*/,e/*相连的边*/;}pre[N];
inline bool BFS()//找增广路
{
    queue<int>q;
    for(ri i=1;i<=n;++i) pre[i].v=pre[i].e=-1;
    for(ri i=1;i<=n;++i) vis[i]=0;
    vis[s]=1;
    q.push(s);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(ri i=head[u];i;i=edge[i].nex)
        {
            int v=edge[i].v;
            if(vis[v]==0&&edge[i].val>0)
            {
                pre[v].v=u,pre[v].e=i;
                if(v==t) return 1;
                vis[v]=1;
                q.push(v);
            }
        }
    }
    return 0;
}
inline int EK()
{
    int ans=0;
    while(BFS())
    {
        int minn=inf;
        for(ri i=t;i!=s;i=pre[i].v) minn=min(minn,edge[pre[i].e].val);
        for(ri i=t;i!=s;i=pre[i].v)
        {
            edge[pre[i].e].val-=minn;
            edge[pre[i].e^1].val+=minn;
        }
        ans+=minn;
    }
    return ans;
}
inline void dfs(int x)
{
    qwq[x]=1;
    for(ri i=head[x];i;i=edge[i].nex)
    {
        if(qwq[edge[i].v]==1) continue;
        dfs(edge[i].v);
        pd[x]++;
        edge[i].val=value[i|1];
    }
}
int main()
{
    n=gi(),s=gi(),t=n+1;
    for(ri i=1;i<=n-1;++i)
    {
        int u=gi(),v=gi();
        add(u,v,0);
        add(v,u,0);
        value[tot]=gi();
    }
    dfs(s);
    for(ri i=1;i<=n;++i) if(pd[i]==0) add(i,t,inf),add(t,i,0);
    printf("%d",EK());
}
```








---

## 作者：mrsrz (赞：9)

树形dp。


对于一棵以i为根的子树，要么割掉i与它父亲的那一条边，要么就是在i的儿子中选择边割掉。于是问题又转化为i的儿子的最小价值。


设dp[i]表示根节点为i的子树割边的价值，则


dp[i]=min(e[i],dp[a]+dp[b]+dp[c]+....)(e[i]表示i与它父亲的连边的权值，a,b,c...表示i的儿子节点)。


答案为dp[c]（c为整棵树的根）。

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int n,rt,cnt,head[100010],dp[100010];
struct edge{
    int to,dis,nxt;
}e[100010<<1];
void dfs(int u,int en,int fa){
    int sum=0;
    for(int i=head[u];i;i=e[i].nxt)
    if(e[i].to!=fa){
        dfs(e[i].to,i,u);
        sum+=dp[e[i].to];
    }
    dp[u]=e[en].dis;
    if(sum&&sum<dp[u])dp[u]=sum;
}
int main(){
    cnt=0;
    memset(head,0,sizeof head);
    scanf("%d%d",&n,&rt);
    for(int i=1;i<n;++i){
        int u,v,t;
        scanf("%d%d%d",&u,&v,&t);
        e[++cnt]=(edge){v,t,head[u]};
        head[u]=cnt;
        e[++cnt]=(edge){u,t,head[v]};
        head[v]=cnt;
    }
    e[0].dis=0x3f3f3f3f;
    memset(dp,0x3f,sizeof dp);
    dfs(rt,0,0);
    printf("%d\n",dp[rt]);
    return 0;
}
```
[blog](http://www.cnblogs.com/Mrsrz/p/7665390.html)


---

## 作者：hovny (赞：5)

## [~~圆~~原题面](https://www.luogu.org/problemnew/show/P3931)

我环顾四周，发现大佬们的写法都好高端！

比较差劲的我，只能交上一份**DFS**的题解

## 思路：

### DFS（当然了，其他算法也行）

要想切断**叶子节点**到**根节点**的连接

就是在**叶子节点**和**根节点**之间砍掉一条边

这明显就很符合**DFS**的性质，一条路一直走下去，遇到分枝就分开走

于是我们DFS每一条路径，然后求答案

复杂度为`O(n)`

### 但是——还没完！

我们可以发现DFS有三种情况

1、该节点为叶子节点，此时只能删去连接它和父节点的边

2、该节点为枝节点，有父节点和子节点，需要选择性的删除

3、该节点为根节点，只有子节点，只能删去连接它和子节点的边

Code：

```cpp
#include<bits/stdc++.h>
#define INF 0x7f7f7f7f
using namespace std;
struct node{
	int to,cost;
	int nxt;
	node(int a,int b):to(a),cost(b){	}
	node(){	}
}b[200010];
int n,t,r;
int head[100010];
int read()
{
	int s=0;
	char c=getchar();
	while(!isdigit(c))
		c=getchar();
	while(isdigit(c))
	{
		s=(s<<1)+(s<<3)+c-'0';
		c=getchar();
	}
	return s;
}
void add(int x,int y,int cost)//建边
{
	b[++t]=node(y,cost);
	b[t].nxt=head[x];
	head[x]=t;
	b[++t]=node(x,cost);
	b[t].nxt=head[y];
	head[y]=t;
	return;
}
int Get(int k,int in)
{
	int i;
	int res=0;
	for(i=head[k];i;i=b[i].nxt)
		if(i!=(in^1))//成对变换原理，异或值相同但方向相反的边为一组，避免重复
			res+=Get(b[i].to,i);
	if(!b[head[k]].nxt&&k!=r)//确定是叶子节点
		res=b[in].cost;
	else
		res=min(res,b[in].cost);//否则两种方法选其一
	return res;
}
int main()
{
	int i;
	int x,y,cost;
	n=read();r=read();
	t=1;//初始赋1，利于成对变换
	for(i=1;i<n;i++)
	{
		x=read();y=read();cost=read();
		add(x,y,cost);
	}
	b[0].cost=INF;//对于根节点的双重保险，防止出什么岔子，比如结果为0
	printf("%d",Get(r,0));
	return 0;
}

```



---

## 作者：LlLlCc (赞：5)

一道非常值得练手的**网络流**~~水~~题（~~暴力也能过~~），题目大致为：对于给定的一颗带**边权有根树**，求出割去边的边权**最小值**，使任意叶子节点与根节点**不连通**。

首先明确一点，**在一颗树中，任意两点间有且只有一条简单路径**，即对于一个叶子节点，我们只需要删除改点到根节点的**任意一条边**，就可以使该节点与根节点不连通。当然，因为是任意删一条边，即我们选择最小的那条边删除。

再想想，其实这就是**网络流中求最小割**，我们将root作为**起点/源点**，再建一个虚拟的汇点，**将所有叶子节点与虚拟汇点建边**，建图完成后刷一趟Dinic即可AC

**不会网络流的看着**：[网络流详解](https://blog.csdn.net/qq_41357771/article/details/79416899)

最后，附上AC代码（仅供参考）：

```
#include<bits/stdc++.h>
#define maxn 100005
#define maxe 200005
using namespace std;
int Q[maxn],Dep[maxn],n,T,S,x,y,z,tot=1,lnk[maxn],nxt[maxe],son[maxe],w[maxe];
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
inline void add(int x,int y,int z){nxt[++tot]=lnk[x];lnk[x]=tot;w[tot]=z;son[tot]=y;}
inline bool Bfs(){
	memset(Dep,0,sizeof Dep);
	int hed=0,til=1;
    Q[1]=S;Dep[S]=1;
    while (hed!=til){
    	hed++;
    	for (int i=lnk[Q[hed]];i;i=nxt[i])
    	  if (!Dep[son[i]]&&w[i]>0){
    	  	Dep[son[i]]=Dep[Q[hed]]+1;
    	  	Q[++til]=son[i];
		  }
	}
	return Dep[T];
}
inline int Dfs(int x,int flow){
	if (x==T) return flow;
	int sum=0;
	for (int i=lnk[x];i&&sum<flow;i=nxt[i])
	  if (w[i]&&Dep[son[i]]==Dep[x]+1){
	  	int Now=Dfs(son[i],min(w[i],flow-sum));
	  	w[i]-=Now,w[i^1]+=Now;
	    sum+=Now;
	  }
	  return sum;
}
inline int Dinic(){
	int Ans=0;
	while (Bfs()) Ans+=Dfs(S,1<<30);
	return Ans;
}
inline void DFS(int x,int fa){
	bool flg=0;
	for (int i=lnk[x];i;i=nxt[i])
	  if (son[i]!=fa) flg=1,w[i^1]=0,DFS(son[i],x);
    if (!flg) add(x,T,1<<30),add(T,x,0);
}
int main(){
	n=read(),S=read();T=n+1;
	for (int i=1;i<n;i++) x=read(),y=read(),z=read(),add(x,y,z),add(y,x,z);
	DFS(S,0);
	printf("%d",Dinic());
	return 0;
}
```


---

## 作者：Priori_Incantatem (赞：4)

### 题目大意
给出一棵有根树，树上每条边都带权，求出一个割边集，使得给集合中边权之和最小

看完题发现就是个 最小割/最大流，设置一个超级汇点 $t$ ，并让所有叶子节点向 $t$ 连一条边，跑一边最大流

过了样例，提交 $0$ 分。。。

回来检查发现 树中的无向边被我处理成有向边了。  
正解应该是先存进双向边，将树用 $dfs$ 遍历成有根树结构后再加边，顺便再 $dfs$ 中寻找叶子节点


#### 代码：
```cpp
#include<cstdio>
#include<iostream>
#include<queue>
#include<cstring>
#include<vector>
using namespace std;
const int Maxn=100000+10,Maxm=400000+10,inf=0x3f3f3f3f;
struct edge{
	int v,len;
	edge(int x,int y)
	{
		v=x,len=y;
	}
};
vector <edge> e[Maxn];
int nxt[Maxm],to[Maxm],flow[Maxm];
int head[Maxn],d[Maxn];
int n,s,t,edgecnt=1,ans;
inline void add(int x,int y,int c)
{
	++edgecnt;
	nxt[edgecnt]=head[x];
	to[edgecnt]=y;
	flow[edgecnt]=c;
	head[x]=edgecnt;
}
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
void dfs(int x,int fa)
{
	bool flag=0;
	for(int i=0;i<e[x].size();++i)
	{
		int y=e[x][i].v;
		if(y==fa)continue;
		flag=1;
		add(x,y,e[x][i].len);
		add(y,x,0);
		dfs(y,x);
	}
	if(!flag) // 如果是叶子节点
	{
		add(x,t,inf);
		add(t,x,0);
	}
}
bool bfs()
{
	queue <int> q;
	memset(d,0,sizeof(d));
	d[s]=1,q.push(s);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=nxt[i])
		{
			int y=to[i];
			if(d[y] || !flow[i])continue;
			d[y]=d[x]+1;
			if(y==t)return 1;
			q.push(y);
		}
	}
	return 0;
}
int dinic(int x,int cur)
{
	if(x==t)return cur;
	int ret=cur;
	for(int i=head[x];i && ret;i=nxt[i])
	{
		int y=to[i];
		if(d[y]!=d[x]+1 || !flow[i])continue;
		int tmp=dinic(y,min(ret,flow[i]));
		if(!tmp)d[y]=0;
		flow[i]-=tmp,flow[i^1]+=tmp,ret-=tmp;
	}
	return cur-ret;
}
int main()
{
	//freopen("in.txt","r",stdin);
	n=read(),s=read();
	t=n+1;
	for(int i=1;i<n;++i)
	{
		int x=read(),y=read(),c=read();
		e[x].push_back(edge(y,c));
		e[y].push_back(edge(x,c));
	}
	dfs(s,0);
	
	int tmp=0;
	while(bfs())
	while(tmp=dinic(s,inf))ans+=tmp;
	printf("%d\n",ans);
	
	return 0;
}
```

---

## 作者：nosta (赞：3)

树形dp；另一种方程：设f[x]为**截断s与子树x的联系**的最小代价，mn[x]为**从s到x的路径上最小的边权**（特别地，mn[x]=inf），son[x]为x的儿子集合，则状态转移为

$$
f[x]=\min(mn[x], \sum_{y\in son[x]}f[y])
$$

当然了，若没有儿子直接令f[x]=mn[x]。

代码：

```
int dp(int x,int pa,int mn) {
	int c=-1;
	for(int i=head[x]; i; i=last[i]) {
		if(to[i]!=pa) c+=dp(to[i],x,min(mn,len[i]));
	}
	return (~c)?min(c+1,mn):mn;
}

int main() {
	scanf("%d%d",&n,&s);
	for(int x,y,w,i=n; --i; ) {
		scanf("%d%d%d",&x,&y,&w);
		add_edge(x,y,w);
		add_edge(y,x,w);
	}
	printf("%d\n",dp(s,0,2e9));
	return 0;
}

```

备注：利用这个方程可以小常数地解决 [P2495](https://www.luogu.org/problemnew/show/P2495)这题，试试看吧。

---

## 作者：wangxuye (赞：3)

题目要求割开树的最小代价，很容易想到最小割

而割开一棵树是要让所有的叶节点和根节点都不连通，源点很容易找（即为根节点），那么汇点不止一个，怎么办呢？

很简单，只要找一个“超级汇点”（所有的汇点都汇聚到这个点上，距离为inf）问题就转化成了标准的最小割（最大流）问题了

### 下面上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=200050,M=400050;
const int inf=0x7fffffff;

ll head[N],ver[M*2],edge[M*2],next[M*2],d[N];
ll n,s,t,tot=1,maxflow=0;
int leaf[N];                   //0为不存在，1为叶子节点，2为非叶子节点 

void add(int x,int y,ll z)
{
	ver[++tot]=y,edge[tot]=z,next[tot]=head[x],head[x]=tot;
	ver[++tot]=x,edge[tot]=z,next[tot]=head[y],head[y]=tot;
}

queue<ll> q;
bool bfs()                     //建层次图 
{
	for(;q.size();q.pop());
	memset(d,0,sizeof(d));
	d[s]=1;
	q.push(s);
	for(;q.size();)
	{
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=next[i])
			if(edge[i]&&!d[ver[i]])
			{
				d[ver[i]]=d[x]+1;
				q.push(ver[i]);
				if(ver[i]==t) return true;
			}
	}
	return false;
}

ll dinic(int x,ll flow)            //dinic算法 
{
	if(x==t) return flow;
	ll rest=flow,k;
	for(int i=head[x];i&&rest;i=next[i])
		if(edge[i]&&d[ver[i]]==d[x]+1)
		{
			k=dinic(ver[i],min(edge[i],rest));
			if(!k) d[ver[i]]=0;
			rest-=k;
			edge[i]-=k;
			edge[i^1]+=k;
		}
	return flow-rest;
}

int main()
{
	scanf("%d%d",&n,&s);
	memset(leaf,0,sizeof(leaf));
	for(int i=1;i<n;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		add(a,b,c);
		leaf[a]++;
		leaf[b]++;
	}
	for(int i=1;i<=n;i++)                   //n+1为超级汇点 
		if(leaf[i]==1&&i!=s) add(n+1,i,inf);
	t=n+1;
	ll flow=0;
	for(;bfs();)
		for(;flow=dinic(s,inf);maxflow+=flow);
	printf("%lld\n",maxflow);
	return 0;
}
```

---

## 作者：haooo (赞：2)

## 树形DP水题

设$dp[i]$为将根为i的子树处理掉的代价

每次有2个选择：

1. 割掉当前父亲节点与儿子节点连接的边，代价为边权

2. 不割掉这条边，选择在以儿子为根的子树下解决，代价为$dp[son]$

**因此**

$dp[x]=min(dp[y_1],e[y_1])+...+min(dp[y_i],e[y_i])$

其中$y_i$为x的儿子，$e[y_i]$为y到x的边权

#### 特判：

但当到**叶节点**的时候是没有子树的，所以直接让$dp[y]$为到他父亲的边权

附上代码，~~忠告：不要抄题解~~
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN=2e5+5;
int nex[MAXN],ver[MAXN],head[MAXN];
int tot;
ll edge[MAXN];
ll dp[MAXN];
ll f[MAXN];//其到父亲节点的边权，只在叶节点时有用
inline void add(int x,int y,ll z){//建图
    nex[++tot]=head[x];
    ver[tot]=y;
    head[x]=tot;
    edge[tot]=z;
    f[y]=z;
}
inline void dfs(int x,int fa){
    bool judge=true;//判断当前节点有没有子树
    for(int i=head[x];i;i=nex[i]){
        int y=ver[i];
        if(y==fa)  continue;
        dfs(y,x);
        dp[x]+=min(edge[i],dp[y]);
        judge=false;
    }
    if(judge)//当前节点为叶节点
        dp[x]=f[x];
}
int n;
int root;//根节点编号
int main(){
    freopen("tree.in","r",stdin);
    freopen("tree.out","w",stdout);
    scanf("%d%d",&n,&root);
    for(int i=1;i<n;i++){
        int x,y;ll z;
        scanf("%d%d%lld",&x,&y,&z);
        add(x,y,z);
        add(y,x,z);
    }
    dfs(root,-1);
    printf("%lld",dp[root]);
    return 0;
}

```


---

## 作者：chdy (赞：2)

写完dp 写最小割发现有点不对的地方。（认真思考发现很多网络流的做法是完全不必要的。）

遍观所有的网络流题解我发现很多都是不知道为什么自己网络流的复杂度可以过或者说建双向边都有权值也不会错的原因。

这里我给出解释 认真看题目你会发现求的是割断从叶子节点到S的路径的一条边使总价值最大，dp使很好写的。看起来像是最小割的模型考虑使用网络流。

1. 众所周知 最大流=最小割，证明的话想一下我们流向汇点的每条流的路径上必有一条路径是满流的，然后这些满流的加起来就是我们的最大流了，自然把这些满流的删掉就是最小割了，如果不是那说明还具有增广路，由我们求最大流的时候把边都增广了，所以不存在这种情况，得证。

2. 这道题 也很清晰明了其实对于每个叶子节点自己的增广路也只有唯一的一条路罢了，不可能有第二条增广路因为如果有两条增广路，由于这是从源点出发的两条路且都到达了同一个点所以有环说明不是树但是题目中保证这是一颗树故对于每个叶子节点增广路也只有一条。

3. 既然增广路只有一条这说明了反向流是不必要的，增广之后已经不可能再次增广了所以这道题其实只需要跑一遍dinic 连建分层图也不必要，时间复杂度为O(n)所以这也就解释了讨论中dinic能解决1e5的数据范围的原因。。

在题解诸多的环境中我们很容易被一些题解的思路给带偏所以要认真的思考出自己对题目的理解不要盲目的去看题解写一些不必要或者千篇一律的算法。(~~觉得有道理点个赞吧！~~

```cpp
//#include<bits/stdc++.h>
#include<iomanip>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<queue>
#include<deque>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<stack>
#include<algorithm>
#include<vector>
#include<cctype>
#include<utility>
#include<set>
#include<bitset>
#include<map>
#define INF 1000000000
#define ll long long
#define min(x,y) (x>y?y:x)
#define max(x,y) (x>y?x:y)
#define RI register ll
#define up(p,i,n) for(ll i=p;i<=n;++i)
#define db double
using namespace std;
char buf[1<<15],*fs,*ft;
inline char getc()
{
    return (fs==ft&&(ft=(fs=buf)+fread(buf,1,1<<15,stdin),fs==ft))?0:*fs++;
}
inline ll read()
{
    ll x=0,f=1;char ch=getc();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getc();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getc();}
    return x*f;
}
inline void put(ll x)
{
    x<0?x=-x,putchar('-'):0;
    int num=0;char ch[20];
    while(x)ch[++num]=x%10+'0',x/=10;
    num==0?putchar('0'):0;
    while(num)putchar(ch[num--]);
    putchar('\n');return;
}
const int MAXN=200010;
int n,s,len=1,t,h,flow,maxx;
int d[MAXN],vis[MAXN],ru[MAXN];
int lin[MAXN],ver[MAXN<<1],nex[MAXN<<1],e[MAXN<<1];
inline void add(int x,int y,int z)
{
	ver[++len]=y;
	nex[len]=lin[x];
	lin[x]=len;
	e[len]=z;
}
inline int dinic(int x,int flow)
{
	if(x==n+1)return flow;
	int rest=flow,k;vis[x]=1;
	for(int i=lin[x];i&&rest;i=nex[i])
	{
		int tn=ver[i];
		if(!e[i]||vis[tn])continue;
		k=dinic(tn,min(rest,e[i]));
		e[i]-=k;rest-=k;
	}
	return flow-rest;
}
int main()
{
	//freopen("1.in","r",stdin);
	n=read();s=read();
	for(int i=1;i<n;++i)
	{
		int x,y,z;
		x=read();y=read();z=read();
		add(x,y,z);add(y,x,z);
		++ru[x];++ru[y];
	}
	for(int i=1;i<=n;++i)if(i!=s&&ru[i]==1)add(i,n+1,INF);
	put(dinic(s,INF));
	return 0;
}

```


---

## 作者：NuoCarter (赞：1)

# P3931 题解

因为蒟蒻不会高端网络流，

所以选择了树形DP

定义 $f[u]$ 为 切断 u 这个结点的子树中的所有叶子结点的最小代价

**如果 u 为叶子结点，**

显然 f[u]=0(代码中有一点不一样，但整体的状态转移还是一样得）

**但是如果 u 不是叶子结点需要分两种情况：**

1.切断 u->v 这条边，代价为 $edge_{u->v}$

2.不切断 u->v 这条边，但是要保证 u 不能到达所有 v 中子树的叶子节点，这个的代价为 f[v]

所以在每次过程中取min就好了

推出方程就很简单了

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,M=2e5+5,INF=0x3f3f3f3f;
int head[N],edge[M],Next[M],to[M],tot,n,size[N],dep[N],root,f[N];

inline void add(int u,int v,int z){to[++tot]=v,edge[tot]=z,Next[tot]=head[u],head[u]=tot;}

inline void dfs(int x,int fa){
  size[x]=1,dep[x]=dep[fa]+1;
  for(int i=head[x];i;i=Next[i]){
    if(to[i]!=fa){
      dfs(to[i],x);
      size[x]+=size[to[i]];
    }
  }
  return;
}

inline int dp(int x,int fa){
  if(size[x]==1){f[x]=INF;return f[x];}
  for(int i=head[x];i;i=Next[i]){
    int y=to[i];
    if(y!=fa){f[x]+=min(dp(y,x),edge[i]);}
  }
  return f[x];
}

int main(){
  freopen("tree.in","r",stdin);
  //freopen("tree.out","w",stdout);
  scanf("%d%d",&n,&root);
  int u,v,w;
  for(int i=1;i<n;++i){
    scanf("%d%d%d",&u,&v,&w);
    add(u,v,w),add(v,u,w);
  }
  dfs(root,0);
  printf("%d\n",dp(root,0));
  return 0;
}

```


---

## 作者：Honeta (赞：1)

## LUOGU P3931 SOLUTION
### 思路点拨
根据题意，本题与最小割问题极为相似，根据最大流最小割定理，本题可转化为求网络最大流。  
  
还未学习该知识的，请[点我学习](https://www.luogu.org/blog/ONE-PIECE/wang-lao-liu-di-zong-jie)，然后建议先写模板题（[点我跳转](https://www.luogu.org/problem/P3376)）练习一下。  
  
**首先，提醒一个雷区！题目给的是一个无向图，故我们需要先从树根开始对这个无向图进行dfs预处理，把无向边转换成有向边。（WA 20分的绝大多数都忽略了这一点，包括我）**  
  
然后，一个网络流图不仅要有源点（即树的根节点），还要有汇点。我们假设n+1即为汇点，让所有的叶子节点都伸出一条指向n+1的有向边（这个可以在dfs预处理时顺便处理一下，而且要记得建反向边）。  
  
题目要求任何叶子节点都和根节点不连通，而这个条件恰恰和汇点和源点不连通是等价的（因为所有叶子节点都和汇点连通，故但凡有任何一个叶子节点和根节点连通，汇点和源点都是连通的）。  
  
至此，我们已经完成了构造，接下来问题就只剩下求网络流图的最大流了。这里有多种算法可以选择，我使用的是dinic算法，具体实现不再赘述。在存图时我采取的是vector存图，和大多数人的习惯不太一样（故网上的代码基本都是邻接表存图），大家可以参考下面的代码。
### AC代码
```cpp
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#define N 100005
#define I 0x3f3f3f3f//无穷大
using namespace std;
struct road{int to,w;};
struct edge{int to,w;}e[N<<2];//存储边的信息，考虑到双向建边（包括叶子节点与汇点）的问题，保险起见开四倍数组
vector<road> g[N];//存初始的无向图
vector<int> v[N];//存转化之后的有向图
int n,s,t,t1,t2,t3,cnt,ans,d[N];
void pre(int x,int fa)
{
  if(g[x].size()==1&&g[x][0].to==fa)//判叶子节点，和汇点建边
    {
      v[x].push_back(cnt);
      e[cnt].to=t;
      e[cnt++].w=I;
      v[t].push_back(cnt);//建反向边
      e[cnt].to=x;
      e[cnt++].w=0;
      return;
    }
  for(int i=0;i<g[x].size();i++)
    {
      int to=g[x][i].to,w=g[x][i].w;
      if(to==fa)continue;
      v[x].push_back(cnt);
      e[cnt].to=to;
      e[cnt++].w=w;
      v[to].push_back(cnt);//建反向边
      e[cnt].to=x;
      e[cnt++].w=0;
      pre(to,x);
    }
}
bool bfs()
{
  queue<int> q;
  memset(d,0,sizeof(d));
  d[s]=1;
  q.push(s);
  while(q.size())
    {
      int now=q.front();
      q.pop();
      for(int i=0;i<v[now].size();i++)
	{
	  int temp=v[now][i];
	  int to=e[temp].to,w=e[temp].w;
	  if(!d[to]&&w)
	    {
	      d[to]=d[now]+1;
	      q.push(to);
	    }
	}
    }
  return d[t];
}
int dfs(int now,int minn)
{
  if(now==t)return minn;
  for(int i=0;i<v[now].size();i++)
    {
      int temp=v[now][i];
      int to=e[temp].to,w=e[temp].w;
      if(d[to]==d[now]+1&&w)
	{
	  int res=dfs(to,min(minn,w));
	  if(res)
	    {
	      e[temp].w-=res;
	      e[temp^1].w+=res;
	      return res;
	    }
	}
    }
  return 0;
}
int main()
{
  scanf("%d%d",&n,&s);
  t=n+1;//设置汇点
  for(int i=1;i<n;i++)
    {
      scanf("%d%d%d",&t1,&t2,&t3);
      g[t1].push_back({t2,t3});//存无向图
      g[t2].push_back({t1,t3});
    }
  pre(s,s);//预处理，无向图转有向图
  while(bfs())//dinic算法求最大流
    ans+=dfs(s,I);
  printf("%d",ans);
  return 0;
}
```


---

## 作者：KillerXu (赞：0)

设 $f_x$ 为以 $x$ 为根结点的子树中所有的叶子结点都被割掉了的最小代价。考虑从儿子转移到父亲，两个选择，第一种儿子已经割完，第二种把父亲到儿子的边割去。取两个选择的最小代价，对每个儿子的结果再求和。即：

$$f_x = \sum _{v 
\in son(x)}\min\{f_v,\operatorname{dis}(x,v) \}$$

答案为 $f_s$

**代码**

```cpp
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <algorithm>

#define ll long long

const int N = 100005;

using namespace std;

ll f[N];
struct data{
	int to, next;
	ll val;
}edge[N << 1];
int head[N], tot = 0, size[N], leaf[N];
int n, s;

void dfs(int x, int fa){
	size[x] = 1;
	for(int i = head[x]; i; i = edge[i].next){
		int v = edge[i].to;
		if(v == fa) continue;
		dfs(v, x);
		size[x] += size[v];
	}
}

void solve(int x, int fa){
	if(leaf[x]) return;
	for(int i = head[x]; i; i = edge[i].next){
		int v = edge[i].to;
		if(v == fa) continue;
		solve(v, x);
		f[x] += min(f[v], edge[i].val);
	}
}

void add(int u, int v, int d){
	edge[++tot].to = v;
	edge[tot].val = d;
	edge[tot].next = head[u];
	head[u] = tot;
}

int main(){
	cin >> n >> s;
	for(int i = 1; i < n; i++){
		int u, v; ll d;
		cin >> u >> v >> d;
		add(u, v, d);
		add(v, u, d);
	}
	
	dfs(s, 0);
	for(int i = 1; i <= n; i++) if(size[i] == 1) { f[i] = 1e18; leaf[i] = 1; }
	solve(s, 0);
	
	cout << f[s];
	
	return 0;
}
```

---

## 作者：dzz1537568241 (赞：0)

# 树形dp


这真的百分百没有蓝题啊。。。

其他的树形dp题目比这个难很多

考虑这一个性质:

一个父节点是由其子树转移过来的

因此我们可以写一个状态转移方程式：

f[u] 表示对于节点u，确保他的子树和根节点没有一条路径，所需要的最小花费。

为什么我觉得这个铁定没有蓝题呢？

因为转移这个最小花费的只有两种情况

1. 直接删节点 u 和它父亲的 边
1. 它的子树的代价之和

这样就能写出代码了。。。
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 100050;
int rd(){
	int x = 0, f = 1; char c = getchar();
	while(c < '0' || c > '9'){if (c == '-'){ f = -1;} c = getchar();}
	while(c >= '0' && c <= '9'){x = x* 10 + c - '0'; c = getchar();} 
	return x*f;
}

struct Edge{
	int u, v, w, next;
}edge[maxn << 1];

int head[maxn], cnt, N, rt, t1, t2, t3, f[maxn];
int fa[maxn];

void addedge(int u, int v, int w){
	edge[++cnt].u = u;
	edge[cnt].v = v;
	edge[cnt].w = w;
	edge[cnt].next = head[u];
	head[u] = cnt;
}

int dfsfa(int u, int fat){
	for(int i = head[u]; i; i = edge[i].next){
		int v = edge[i].v, w = edge[i].w;
		if(v == fat)continue;
		//cout<<v<<" 1"<<endl;
		fa[v] = w;
		dfsfa(v, u);
	}
}

int dfs(int u, int fat){
	int ans = 0x3f3f3f;
	f[u] = fa[u]; 
	for(int i = head[u]; i; i = edge[i].next){
		int v = edge[i].v, w = edge[i].w;
		if(v == fat)continue;
		dfs(v, u);
		if(ans == 0x3f3f3f)ans = 0;
		ans += f[v];
	}
	f[u] = min(fa[u], ans);
}

int main(){
	N = rd(), rt = rd();
	for(int i = 1; i < N; i++){
		t1 = rd(), t2 = rd(), t3 = rd();
		addedge(t1,t2,t3), addedge(t2,t1,t3);
	}
	dfsfa(rt , -1);
	fa[rt] = 0x3f3f3f;//预处理 
	dfs(rt, -1);
	cout<<f[rt];
}
 
```
其实那个dfsfa完全没有必要写...
这道题目的名字蒙蔽了我的双眼，于是下意识的弄得复杂了。

建议把难度调成绿题，作为树形dp的入门题（~~虽然水，但是~~经典）

---

## 作者：TheShadow (赞：0)

# 闲扯

为了学习最小割到了这道题，但是看题解的时候发现做法还有树形 $DP$ ~~毕竟没怎么认真想过题~~，写完最小割之后，顺手来了发树形 $DP$ ，然后就过了，感觉真爽啊~~

# 题面

[题面](https://www.luogu.org/problem/P3931)

# Solution

## 解法一：最小割最大流

因为要求是所有的叶节点都不能到达根结点，而且可以删除边，要求删边的最小代价，看着就很像最小割。但是仔细一看，发现割完之后叶节点组成了很多个点集，怎么办？

我们只需要再虚拟一个超级汇点，将所有的根结点全部连向该节点，且边的流量均为 $INF$ 。（因为这些边是我们人为加的，肯定不能选这些边割去）

这时候我们可以看出，当所有的边割完之后，实际上是将这幅图变成了两个不相交的点集，且 $S$ 和 $T$ 分别处于一侧。这样就变成了最小割的模板了，直接跑最大流即可（最小割在数值上等于最大流，不清楚的自行百度）。



## 解法二：树形 $DP$

因为叶节点不能到根结点，我们考虑树形 $DP$ 从下向上统计。~~这是什么逻辑（雾~~

考虑 $dp_u$ 表示以 $u$ 为根节点时，所需要的最小代价，转移方程为： $dp_u=\sum \min(dp_i,dis_i)$ 。其中 $i$ 为 $u$ 的子节点， $dis$ 表示 $i$ 到 $u$ 的距离。

理解：对于包含于以 $i$ 为根结点的子树的叶节点，割去他们所需的最小代价为直接割去这颗子树和保持原来做法的最小值，而一个 $u$ 可能有多个子树，所以要求和（不同子树相互独立，互不影响）。

需要注意的时候，当 $u$ 的子节点 $i$ 就为叶节点时， $dp_i$ 要设为 $INF$ ，这样可以保证删去该点的值一定为 $dis_i$ 。

# Code

## 解法一：

```c++
#include<bits/stdc++.h>
#define del(a,i) memset(a,i,sizeof(a))
#define ll long long
#define inl inline
#define il inl void
#define it inl int
#define ill inl ll
#define re register
#define ri re int
#define rl re ll
#define mid ((l+r)>>1)
#define lowbit(x) (x&(-x))
#define INF 0x3f3f3f3f
using namespace std;
template<class T>il read(T &x){
	int f=1;char k=getchar();x=0;
	for(;k>'9'||k<'0';k=getchar()) if(k=='-') f=-1;
	for(;k>='0'&&k<='9';k=getchar()) x=(x<<3)+(x<<1)+k-'0';
	x*=f;
}
template<class T>il print(T x){
	if(x/10) print(x/10);
	putchar(x%10+'0');
}
ll mul(ll a,ll b,ll mod){long double c=1.;return (a*b-(ll)(c*a*b/mod)*mod)%mod;}
it qpow(int x,int m,int mod){
	int res=1,bas=x%mod;
	while(m){
		if(m&1) res=(res*bas)%mod;
		bas=(bas*bas)%mod,m>>=1;
	}
	return res%mod;
}
const int MAXN = 1e5+5;
int n,s,t,u,v,d,cur[MAXN],head[MAXN],num_edge=-1,dis[MAXN];
struct Edge{
	int next,to,w;
	Edge(){}
	Edge(int next,int to,int w):next(next),to(to),w(w){}
}edge[MAXN<<2];
il add_edge(int u,int v,int w){
	edge[++num_edge]=Edge(head[u],v,w),head[u]=num_edge;
	edge[++num_edge]=Edge(head[v],u,w),head[v]=num_edge;
}
il build(int u,int fa){
	bool fla=0;
	for(ri i=head[u];i!=-1;i=edge[i].next){
		if(edge[i].to==fa) continue;
		edge[i^1].w=0;
		build(edge[i].to,u),fla=1;
	}
	if(!fla) add_edge(u,t,INF);
}
inl bool BFS(int s,int t){
	del(dis,0),dis[s]=1;
	queue<int> q;q.push(s);
	while(!q.empty()){
		ri pos=q.front();q.pop();
		for(ri i=head[pos];i!=-1;i=edge[i].next)
			if(!dis[edge[i].to]&&edge[i].w>0){
				dis[edge[i].to]=dis[pos]+1;
				if(edge[i].to==t) return true;
				q.push(edge[i].to);
			}
	}
	return false;
}
it DFS(int now,int t,int flow){
	if(now==t) return flow;
	ri s=0,k;
	for(ri &i=cur[now];i!=-1;i=edge[i].next)
		if(dis[edge[i].to]==dis[now]+1&&edge[i].w>0){
			k=DFS(edge[i].to,t,min(flow-s,edge[i].w));
			s+=k,edge[i].w-=k,edge[i^1].w+=k;
			if(s==flow) break;
		}
	if(s==0) dis[now]=0;
	return s;
}
it Dinic(int s,int t){
	ri res=0;
	while(BFS(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=DFS(s,t,INF);
	}
	return res;
}
int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n),read(s),t=n+1,del(head,-1);
	for(ri i=1;i<n;++i) read(u),read(v),read(d),add_edge(u,v,d);
	build(s,0);
	printf("%d",Dinic(s,t));
	return 0;
}
```

## 解法二：

```c++
#include<bits/stdc++.h>
#define del(a,i) memset(a,i,sizeof(a))
#define ll long long
#define inl inline
#define il inl void
#define it inl int
#define ill inl ll
#define re register
#define ri re int
#define rl re ll
#define mid ((l+r)>>1)
#define lowbit(x) (x&(-x))
#define INF 0x3f3f3f3f
using namespace std;
template<class T>il read(T &x){
	int f=1;char k=getchar();x=0;
	for(;k>'9'||k<'0';k=getchar()) if(k=='-') f=-1;
	for(;k>='0'&&k<='9';k=getchar()) x=(x<<3)+(x<<1)+k-'0';
	x*=f;
}
template<class T>il print(T x){
	if(x/10) print(x/10);
	putchar(x%10+'0');
}
ll mul(ll a,ll b,ll mod){long double c=1.;return (a*b-(ll)(c*a*b/mod)*mod)%mod;}
it qpow(int x,int m,int mod){
	int res=1,bas=x%mod;
	while(m){
		if(m&1) res=(res*bas)%mod;
		bas=(bas*bas)%mod,m>>=1;
	}
	return res%mod;
}
const int MAXN = 1e5+5;
int n,s,dp[MAXN],u,v,d,head[MAXN],num_edge;
struct Edge{
	int next,to,dis;
	Edge(){}
	Edge(int next,int to,int dis):next(next),to(to),dis(dis){}
}edge[MAXN<<1];
il add_edge(int u,int v,int dis){
	edge[++num_edge]=Edge(head[u],v,dis),head[u]=num_edge;
	edge[++num_edge]=Edge(head[v],u,dis),head[v]=num_edge;
}
il DFS(int u,int fa){
	bool fla=0;
	for(ri i=head[u];i;i=edge[i].next){
		if(edge[i].to==fa) continue;fla=1;
		DFS(edge[i].to,u),dp[u]+=min(dp[edge[i].to],edge[i].dis);
	}
	if(!fla) dp[u]=INF;
}
int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n),read(s);
	for(ri i=1;i<n;++i) read(u),read(v),read(d),add_edge(u,v,d);
	DFS(s,0);
	printf("%d",dp[s]);
	return 0;
}
```

# 总结

最小割也是网络流的一个重要分支，也是一个建图游戏，多做题，找到感觉，学习不同的技巧，才能够自己熟练掌握。

---

## 作者：cold_cold (赞：0)

 [安利一波博客](https://www.cnblogs.com/cold-cold/p/10153495.html)

这题真的不是一道用网络流解决的好题，初学者应绕路

但我偏偏就用网络流写了

每个叶子节点连向超级汇点n+1，即可

但我当时把 所谓割开一棵有根树，就是删除若干条边，使得任何叶子节点和根节点不连通。

看成了所谓割开一棵有根树，就是删除若干条边，使得任何节点和根节点不连通。

这且不说，还有一个问题

这棵树是一个无向图，所以我们有两种选择

读入边以后，dfs建树

第二种就比较玄学

我们将反向边不设为0，而也设为原权值

因为它是无向图，而这种做法不会错的原因，可能是因为它是一棵树

实现如下：

```cpp
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
using namespace std;
typedef long long ll;
inline int read()
{
    register int p(1),a(0);register char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
    if(ch=='-') p=-1,ch=getchar();
    while(ch>='0'&&ch<='9') a=a*10+ch-48,ch=getchar();
    return a*p;
}
const int N=100100,M=200100,INF=0x3f3f3f3f;
queue<int> Q;
int n,m,src,st,u,v,w,cnt,ans=0,d[N],head[N],du[N];
struct EDGE{int nxt,val,to;}e[M<<1];
void add(int u,int v,int w){e[cnt]=(EDGE){head[u],w,v};head[u]=cnt++;}
int BFS()
{
    memset(d,-1,sizeof(d));
    while(!Q.empty()) Q.pop();;
    d[src]=0;Q.push(src);int u,v,w;
    while(!Q.empty())
    {
        u=Q.front();Q.pop();
        for(int i=head[u],v=e[i].to;i!=-1;i=e[i].nxt,v=e[i].to) if(e[i].val&&d[v]==-1)
        {
            d[v]=d[u]+1;
            if(v==st) return 1;
            Q.push(v);
        }
    }
    return 0;
}
int Dinic(int u,int flow)
{
    if(u==st||flow==0) return flow;
    int res=flow,tt;
    for(int i=head[u],v=e[i].to;i!=-1&&res;i=e[i].nxt,v=e[i].to)
    if(e[i].val&&d[v]==d[u]+1)
    {
        tt=Dinic(v,min(res,e[i].val));
        if(!tt) d[v]=-1;
        e[i].val-=tt;
        e[i^1].val+=tt;
        res-=tt;
    }
    return flow-res;
}
int main()
{
    // freopen("input","r",stdin);
    // freopen("output","w",stdout);
    memset(head,-1,sizeof(head));
    n=read(),m=n-1,src=read(),st=n+1;
    for(int i=1;i<=m;i++)
    {
        u=read(),v=read(),w=read(); du[u]++;du[v]++;
        add(u,v,w);add(v,u,w);
    }
    for(int i=1;i<=n;i++)if(i!=src&&du[i]==1) add(i,st,INF),add(st,i,0);
    while(BFS())
        ans+=Dinic(src,INF);
    printf("%d",ans);
    return 0;
}
/*
 
*/
```

---

## 作者：Drug__Lover (赞：0)

**树形DP**

**F[x]表示选取x节点以下的边能使叶子结点与x不连通的最小值**

**F[x]=min(与子节点的权值，与子树的权值）**

**边界条件F[子节点]=INF**


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 300000
using namespace std;
struct node
{
    int next,to,cost;
}e[maxn];
int deep[maxn];
int cnt;
int head[maxn];
int f[maxn];
int add(int u,int v,int w)
{
    e[++cnt].next=head[u];
    e[cnt].to=v;
    e[cnt].cost=w;
    head[u]=cnt;
}
int dfs(int x,int fa)
{
    if(deep[x]==1&&fa!=0)      //叶子结点 
    {
        f[x]=0x7fffffff;        //边界 处理  
        return 0;      
    }
    for(int i=head[x];i;i=e[i].next)     //枚举儿子结点 
    {
        int to=e[i].to;
        if(to!=fa)
        {
            dfs(to,x);                  
            f[x]+=min(f[to],e[i].cost); //转移 
        }
    }
}
int main()
{
    int n,s;
    cin>>n>>s;
    for(int i=1;i<n;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        deep[x]++,deep[y]++;       //用于找叶子结点 
        add(x,y,z);            //连边 
        add(y,x,z);
    }
    dfs(s,0);           //从根节点开始找 
    cout<<f[s]<<endl;       //最小值使得叶子结点与根节点不连通 
    return 0;
}
```

---

