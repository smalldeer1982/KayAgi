# [USACO08OCT] Pasture Walking G

## 题目描述

The N cows (2 <= N <= 1,000) conveniently numbered 1..N are grazing among the N pastures also conveniently numbered 1..N. Most conveniently of all, cow i is grazing in pasture i.

Some pairs of pastures are connected by one of N-1 bidirectional walkways that the cows can traverse. Walkway i connects pastures A\_i and B\_i (1 <= A\_i <= N; 1 <= B\_i <= N) and has a length of L\_i (1 <= L\_i <= 10,000).

The walkways are set up in such a way that between any two distinct pastures, there is exactly one path of walkways that travels between them. Thus, the walkways form a tree.

The cows are very social and wish to visit each other often. Ever in a hurry, they want you to help them schedule their visits by computing the lengths of the paths between 1 <= L\_i <= 10,000 pairs of pastures (each pair given as a query p1,p2 (1 <= p1 <= N; 1 <= p2 <= N).

POINTS: 200

有N(2<=N<=1000)头奶牛，编号为1到N，它们正在同样编号为1到N的牧场上行走.为了方 便，我们假设编号为i的牛恰好在第i号牧场上.

有一些牧场间每两个牧场用一条双向道路相连，道路总共有N - 1条，奶牛可以在这些道路 上行走.第i条道路把第Ai个牧场和第Bi个牧场连了起来(1 <= A\_i <= N; 1 <= B\_i <= N)，而它的长度 是 1 <= L\_i <= 10,000.在任意两个牧场间，有且仅有一条由若干道路组成的路径相连.也就是说，所有的道路构成了一棵树.

奶牛们十分希望经常互相见面.它们十分着急，所以希望你帮助它们计划它们的行程，你只 需要计算出Q(1 < Q < 1000)对点之间的路径长度•每对点以一个询问p1,p2 (1 <= p1 <= N; 1 <= p2 <= N). 的形式给出.



## 说明/提示

Query 1: The walkway between pastures 1 and 2 has length 2.

Query 2: Travel through the walkway between pastures 3 and 4, then the one between 4 and 1, and finally the one between 1 and 2, for a total length of 7.


## 样例 #1

### 输入

```
4 2 
2 1 2 
4 3 2 
1 4 3 
1 2 
3 2 
```

### 输出

```
2 
7 
```

# 题解

## 作者：STLGirlfriend (赞：25)

这题不需要跑 LCA 之类的，只需要一个 Floyd + 剪枝就可以 AC 了。

Floyd 的复杂度大家都知道是 $O(n^3)$，但是我们可以剪枝。我们都知道 Floyd 初始需要把 $dist$ 数组初始化为 $\infty$，所以当我们进行第二层循环时，如果当前 $dist(i, k) = \infty$ 就可以直接跳过。

这个剪枝在此题的优化十分显著，可以直接 AC。

以下是代码（很久以前敲得，风格可能比较崩坏）：

```cpp
#include <cstdio>
#include <cstring>
#define min(a, b) ((a) < (b) ? (a) : (b))
const int MaxN = 1e3;
const int INF = 0x3f3f3f3f;
int d[MaxN + 1][MaxN + 1];
int main() {
	int N, Q;
	memset(d, 0x3f, sizeof(d));
	scanf("%d %d", &N, &Q);
	for (int i = 1, A, B, L; i < N; ++i) {
		scanf("%d %d %d", &A, &B, &L);
		d[A][B] = d[B][A] = L;
	}
	for (int k = 1; k <= N; ++k)
		for (int i = 1; i <= N; ++i) {
			if (d[i][k] == INF) continue;
			for (int j = 1; j <= N; ++j)
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
		}
	for (int P1, P2; Q--; ) {
		scanf("%d %d", &P1, &P2);
		printf("%d\n", d[P1][P2]);
	}
	return 0;
}
```

---

## 作者：雪颜 (赞：9)

    这题竟然是......树链剖分
    首先，我们知道，dis(u,v)=dis(u)+dis(v)-dis(lca(u,v))*2;(不知道算了。。。)
    然后，我们知道，lca可以用tarjan求，也可以用树剖求（不知道也算了。。。）
    那么树剖到底是什么呢？就是将树形结构“转化”成链式求解。
    对于点u，设u的子树结点个为s[u],若存在结点v,使得s[v]>=s[u]/2,那么edge(u,v)称为重边，其余边称为轻边，v是u的重孩子。
    由于s[u]>=s[v]*2+1,所以轻边的数量不会超过logN
    将重边组成的链称为重链，由于每个非叶子结点都有且仅有一条重边，所以重链和轻边交替出现。故重链的数量不会超过logN+1
    那么，我们只要沿着重链dfs，就可以记下每个结点所在的重链。若u,v在同一重链上，则lca(u,v)为u,v中深度小的；否则，跳到重链的顶端，并且沿着父节点一路向上找，直到u,v在同一重链上，此时lca(u,v)为u,v中深度小的。
    当然，还有一个很重要的储备知识：链式前向星（邻接表）
    那么，我们就可以写了。
    
    void add(int u,int v,int x){//链式前向星，加边，在u,v之间加上一条权值为x的边
		nxt[++t]=h[u];
		h[u]=t;
		adj[t]=v;
		w[t]=x;
	}
    void DFS(int u){//第一遍dfs，求出每个结点的父亲，深度，以及其子树的结点个数（包括自身）
		int i,j;
		s[u]=1;//子树结点数量目前只有一个，即u本身
        d[u]=d[f[u]]+1;//u的深度为其父亲深度+1
		for(i=h[u];i;i=nxt[i]){//遍历u的子树
			j=adj[i];
			if(j!=f[u]){//判断是否是其父亲，以免出现死循环
				f[j]=u;//标记，u的孩子的父亲是u
                ans[j]=w[i]+ans[u];//算出dis(j)
				DFS(j);
				s[u]+=s[j];//u子树中结点的个数加上其孩子所在子树结点的个数
			}
	    }
    }
    
    void dfs(int u){//第二遍dfs,记下每个结点所在的重链的编号，即重链中深度最小的结点的编号
		if(!top[u]) top[u]=u;//目前u是u所在重链的深度最小结点
		int i,j,k=0;
		for(i=h[u];i;i=nxt[i]){
			j=adj[i];
            if(j!=f[u]&&s[j]>s[k]) k=j;//k是u的重孩子
		}
		if(k>0){
			top[k]=top[u];//目前u是k所在重链的深度最小结点
			dfs(k);//沿着重链找下去
        }
       	for(i=h[u];i;i=nxt[i]){
			j=adj[i];
			if(j!=f[u]&&j!=k) dfs(j);//找轻边
		}
	}
    
    int LCA(int u,int v){//求u和v的lca
		while(top[u]!=top[v]){//若u,v不在同一重链上
			if(d[top[u]]<d[top[v]]) u=u+v,v=u-v,u=u-v;//若u所在重链的深度小，则交换u,v,这样可以确保最后找到的是深度最小的结点
			u=f[top[u]];//u跳到其重链上最小深度结点的父亲
        }
		return d[u]<d[v]?u:v;//返回深度最小的结点，即lca
	}

    int main(){
		int u,v,x,i;
		cin>>n>>m;//本来写了快读，懒得复制了
		for(i=1;i<n;i++){
			cin>>u>>v>>x;
			add(u,v,x);add(v,u,x);//树上的边是无向边，记得加边两次
		}
		DFS(1);
		dfs(1);
		while(m--){
			cin>>u;cin>>v;
			printf("%d\n",ans[u]+ans[v]-2*ans[LCA(u,v)]);//计算距离
		}
		return 0;
    }


---

## 作者：Watermatter (赞：8)

**最近刚学了树形结构和关于树的一些问题，恰好看到了这个题来练练手。**

这个题看到别的大佬用tarjan或树剖写的，我这个蒟蒻还没学（......），只好默默的掏出了自己的倍增求LCA，话不多说，上代码，萌新可以多看看注释。
```
#include<bits/stdc++.h>
#define N 1000100//数组可以开成10001，我开这么大是保险。
using namespace std;
int pre[N],now[N],son[N],tot,val[N];
int n,rt,q,f[N][20],dep[N],a[N],c[N],len[N];
bool b[N];
inline void dadson(int x,int y,int z)
{
    tot++;
    pre[tot]=now[x];
    now[x]=tot;
    son[tot]=y;
    len[tot]=z;
}//一个邻接表储存树
inline void dfs(int u,int d)
{
    dep[u]=d;
    b[u]=1;
    for(int i=now[u];i;i=pre[i])
    {
        int c=son[i];
        if(!b[c])
        {
            f[c][0]=u;
            val[c]=val[u]+len[i];
            dfs(c,d+1);
        }
    }
}//求每条边的权值
inline void dp()
{
    for(int i=1;i<=19;i++)
    for(int j=1;j<=n;j++)
    f[j][i]=f[f[j][i-1]][i-1];
}//这是两个点往上跳找公共祖先的预处理。
inline int lca(int x,int y)
{
    if(dep[x]<dep[y])swap(x,y);//如果x的深度比y的深度要小，则置换x，y。
    for(int i=19;i>=0;i--)
    {
        if(dep[f[x][i]]>=dep[y])
        x=f[x][i];
    }
    if(x==y)return x;//如果x==y时，说明找到了LCA，则返回x。
    for(int i=19;i>=0;i--)
    {
        if(f[x][i]!=f[y][i])
        x=f[x][i],y=f[y][i];
    }
    return f[x][0];//如果x!=y，则两个点同时往上跳，直到找到祖先为止。
}
inline void init()
{
    cin>>n>>q;
    rt=1;
    for(int i=1;i<n;i++)
    {
        int x,y,z;
        cin>>x>>y>>z;
        dadson(x,y,z);
        dadson(y,x,z);
    }
}//读入和储存树。
inline void work()
{
    dfs(rt,1);
    dp();
	int x,y;a[0]=1;
    for(int i=1;i<=q;i++)
    {
        cin>>x>>y;
        cout<<val[x]+val[y]-2*val[lca(x,y)]<<endl;//求树上的边权值
    }
 
}
int main()
{
    init();
    work();
    //so easy 的主程序，记得加return 0;
    return 0;
}
```

```
------------
一个提交记录，跑的还算是比较快的
https://www.luogu.org/record/show?rid=9819591

---

## 作者：顾z (赞：6)

# [顾](https://www.luogu.org/blog/RPdreamer/#)[z](https://www.cnblogs.com/-guz/)

~~你没有发现两个字里的blog都不一样嘛~~ qwq

题目描述-->[p2912 牧场散步](https://www.luogu.org/problemnew/show/P2912)

### 题意概括

给定一个**树**,给你Q个询问,每次询问输入一个二元组$(x,y)$,要求求出$(x,y)$的距离.

明显带权lca.

这里写一下递推式
$$f[u][i]=f[f[u][i-1]][i-1]$$

$$gw[u][i]=gw[f[u][i-1]][i-1]+gw[u][i-1]$$

#### 定义：

> $f[u][i]$代表$u$向上跳$2^i$步到达的节点.
>
> $gw[u][i]$代表$u$向上跳$2^i$步到达的节点的边权和.

为什么$f[u][i]=f[f[u][i-1]][i-1]$？

我们从$u$到达$f[u][i]$需要$2^i$步,而到达$f[u][i-1]$需要$2^{i-1}$步,再从这个位置跳$2^{i-1}$步,的话就到达了$f[u][i]$。

$$2^{i-1}+2^{i-1}=2*2^{i-1}=2^{i}$$

又因为我们处理$f[u][i-1]$一定比处理$f[u][i]$要早,所以这样转移即可.

#### 初始化

```c++
f[u][0]=fa;
gw[u][0]=edge[i].w;//即连向u的边权.
```

然后这样这个题就变成了裸的带权lca问题 qwq.

---------------------代码---------------------

```c++
#include<bits/stdc++.h>
#define R register
#define N 1008
using namespace std;
inline void in(int &x)
{
	int f=1;x=0;char s=getchar();
	while(!isdigit(s)){if(s=='-')f=-1;s=getchar();}
	while(isdigit(s)){x=x*10+s-'0';s=getchar();}
	x*=f;
}
int n,head[N],tot,m;
int depth[N],f[N][18],gw[N][18];
struct cod{int u,v,w;}edge[N<<1+8];
inline void add(int x,int y,int z)
{
	edge[++tot].u=head[x];
	edge[tot].v=y;
	edge[tot].w=z;
	head[x]=tot;
}
void dfs(int u,int fa,int dis)
{
	depth[u]=depth[fa]+1;
	f[u][0]=fa;gw[u][0]=dis;
	for(R int i=1;(1<<i)<=depth[u];i++)
		f[u][i]=f[f[u][i-1]][i-1],
		gw[u][i]=gw[f[u][i-1]][i-1]+gw[u][i-1];
	for(R int i=head[u];i;i=edge[i].u)
	{
		if(edge[i].v==fa)continue;
		dfs(edge[i].v,u,edge[i].w);
	}
}
inline int lca(int x,int y)
{
	if(depth[x]>depth[y])swap(x,y);
	int ans=0;
	for(R int i=17;i>=0;i--)
		if(depth[y]-(1<<i)>=depth[x])
			ans+=gw[y][i],y=f[y][i];
	if(x==y)return ans;
	for(R int i=17;i>=0;i--)
	{
		if(f[x][i]==f[y][i])continue;
		ans+=gw[x][i]+gw[y][i];
		y=f[y][i],x=f[x][i];
	}
	return (ans+gw[x][0]+gw[y][0]);
}
int main()
{
	in(n),in(m);
	for(R int i=1,x,y,z;i<n;i++)
	{
		in(x),in(y),in(z);
		add(x,y,z);add(y,x,z);
	}
	dfs(1,0,0);
	for(R int x,y;m;m--)
	{
		in(x),in(y);
		printf("%d\n",lca(x,y));
	}
}
```

---

## 作者：Tgotp (赞：5)

很经典的一道题，值得一刷，倍增维护区间和，bfs建树，预处理一遍就好了。最后直接lca就好了，最后lca的第二种情况别忘了同时再分别加两个的祖先。



```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
const int N = 100000 + 5;
int tot,head[N],n,q,f[N][30],p[N][30],deep[N];
bool vis[N];
struct node
{
    int next , to , val;
}edge[N];
int add(int a,int b,int c)
{
    edge[tot].next=head[a];
    edge[tot].to=b;
    edge[tot].val=c;
    head[a]=tot++;
}
int lca(int x,int y)
{
    int ans = 0;
    if(deep[x]<deep[y])swap(x,y);
    int i;
    for(i=0;(1<<i)<=deep[x];i++);
    for(int j=i-1;j>=0;j--)
        if(deep[x]-(1<<j)>=deep[y])
        {
            ans+=f[x][j];
            x=p[x][j];
        }
    if(x==y) return ans;
    for(int j=i-1;j>=0;j--)
    {
        if(p[x][j]!=p[y][j])
        {
            ans+=f[x][j]+f[y][j];
            x=p[x][j];
            y=p[y][j];
        }
    }
    return ans+f[x][0]+f[y][0];
}
void dfs(int x)
{
    vis[x]=true;
    for(int i=head[x];~i;i=edge[i].next)
        if(!vis[edge[i].to])
        {
            deep[edge[i].to]=deep[x]+1;
            p[edge[i].to][0]=x;
            f[edge[i].to][0]=edge[i].val;
            dfs(edge[i].to);
        }
}
void solve()
{
    memset(head,-1,sizeof(head));
    cin>>n>>q;
    for(int i = 1;i<n;i++)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        add(a,b,c);add(b,a,c);
    }
    dfs(1);
    for(int j=1;(1<<j)<=n;j++)
    {
        for(int i=1;i<=n;i++)
        if(p[i][j-1])
        {
            p[i][j]=p[p[i][j-1]][j-1];
            f[i][j]=f[i][j-1]+f[p[i][j-1]][j-1];
        }
    }
    for(int i=0;i<q;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        printf("%d\n",lca(a,b));
    }
}
int main()
{
    solve();
    return 0;
}
```

---

## 作者：Acc_Robin (赞：3)

这题要求LCA，很多人会想树剖或者倍增，但仔细一看数据范围——$10^4$，$O(n^2)$都能过，那直接写暴力跳LCA就行辣！

神魔？你不会暴力跳？

不断让深度大的向上跳一层，直到是同一个点为止.

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e4+10;
int n,m,d[N],fa[N],x,y,z,res;
struct Edge{
    int id,w;
};
int w[N];
basic_string<Edge>G[N];
void dfs(int u){for(int i=0,v;i<G[u].size();i++)if(!d[v=G[u][i].id])d[v]=d[u]+1,fa[v]=u,w[v]=G[u][i].w,dfs(v);}
int main(){
    cin>>n>>m,d[1]=1;
    for(int i=1;i<n;i++)cin>>x>>y>>z,G[x]+=(Edge){y,z},G[y]+=(Edge){x,z};
    dfs(1);
    for(int i=1;i<=m;i++){
        cin>>x>>y;res=0;
        while(x!=y){
            if(d[x]>d[y])res+=w[x],x=fa[x];
            else res+=w[y],y=fa[y];
        }
        cout<<res<<endl;
    }
    return 0;
}

```


---

## 作者：bztMinamoto (赞：3)

发个blog记录一下省的忘记

lca是一类大题，虽然有很多解法，但蒟蒻也知之不多，今天只挑两类解法，倍增和树剖



------------
倍增

这是一种在线解答lca问题的算法，具有高效性

先说思路：设f[x][i]表示节点x的第2^i辈祖先,特别的，若该节点不存在，责令f[x][i]=0，初始化f[x][0]为节点x的父节点，有以下递推关系式
```
f[x][i]=f[f[x][i-1]][i-1]
```
于是我们可以用bfs预处理出f数组。

计算lca(x,y)有以下步骤

1.设d[x]表示x的深度，且d[x]>=d[y]（否则交换x，y）

2.用二进制思想，将x向上调整到与y同一深度

具体来说，就是依次尝试让x向上走i=2^log n,……2^1,2^0,步，并检查到达的节点是否比y深，若是，则令x=f[x][i]

3.若此时x=y，则已找到，并返回值

4.否则，用二进制拆分思想，将x，y同时向上调整，并保证深度一致且二者不相会

具体来说，就是依次尝试让x，y向上走i=2^log n,……2^1,2^0,步，若f[x][i]!=f[y][i],则令x=f[x][i],y=f[y][i]

5.此时x，y必定只差一步就相会，他们的lca就是f[x][0]

预处理时间复杂度为O(n log n),之后每次询问的时间复杂度为O(log n)

上代码
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<bitset>
#include<cstring>
#include<cmath>
#define fu(a,b,c) for(int a=b;a<=c;a++)
#define fd(a,b,c) for(int a=b;a>=c;a--)
using namespace std;
const int INF=0x3f3f3f3f,N=1050;
int ver[N*2],Next[N*2],head[N],edge[N*2];
int fa[N][20],d[N],dist[N];
int n,m,tot,q,t,s;
inline void add(int x,int y,int z)
{
    ver[++tot]=y,edge[tot]=z,Next[tot]=head[x],head[x]=tot;
}
void bfs(int x)
{
    queue<int> q;
    q.push(x),d[x]=1;
    dist[x]=0;
    while(!q.empty())
    {
        int x=q.front();
        q.pop();
        for(int i=head[x];i;i=Next[i])
        {
            int y=ver[i],z=edge[i];
            if(d[y]) continue;
            d[y]=d[x]+1;
            dist[y]=dist[x]+z;
            fa[y][0]=x;
            fu(j,1,t)
            fa[y][j]=fa[fa[y][j-1]][j-1];
            q.push(y);
        }
    }
}
int lca(int x,int y)
{
    if(d[y]>d[x]) swap(x,y);
    fd(i,t,0)
    if(d[fa[x][i]]>=d[y]) x=fa[x][i];
    if(x==y) return x;
    fd(i,t,0)
    if(fa[x][i]!=fa[y][i])
    {
        x=fa[x][i],y=fa[y][i];
    }
    return fa[x][0];
}
int main()
{
    scanf("%d%d",&n,&q);
    t=(log(n)/log(2))+1;
    fu(i,1,n-1)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        add(x,y,z),add(y,x,z);
    }
    bfs(1);
    while(q--)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",dist[x]+dist[y]-2*dist[lca(x,y)]);
    }
    return 0;
}
```


------------
树剖

也是一种在线的解答，跑得比上面的还快~~（比香港记者还快）~~

此blog讲的很详细，我就借用（照抄）了
[](https://www.cnblogs.com/1227xq/p/6813288.html)https://www.cnblogs.com/1227xq/p/6813288.html

![](https://i.loli.net/2018/06/10/5b1d1f24e5c75.png)
![](https://i.loli.net/2018/06/10/5b1d1f24e5e0c.png)
![](https://i.loli.net/2018/06/10/5b1d1fd74fac3.jpg)
橙边为轻边

红边为重边

绿数为每个点的 top

橙数为每个点的编号

1　 先预处理 每个点的 deep深度  size子树大小  dad父节点　　

2　 再预处理 每个点的 top重链顶点

3　 就是跳了

 上代码
```
//minamoto
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<bitset>
#include<cstring>
#include<cmath>
#define fu(a,b,c) for(int a=b;a<=c;a++)
#define fd(a,b,c) for(int a=b;a>=c;a--)
using namespace std;
const int INF=0x3f3f3f3f,N=1050;
int ver[N*2],Next[N*2],head[N],edge[N*2];
int f[N],top[N],d[N],l[N],size[N];
int n,tot,t;
inline void add(int x,int y,int z)
{
    ver[++tot]=y,edge[tot]=z,Next[tot]=head[x],head[x]=tot;
}
void dfs(int x)
{
    size[x]=1,d[x]=d[f[x]]+1;
    for(int i=head[x];i;i=Next[i])
    {
        int y=ver[i],z=edge[i];
        if(y!=f[x])
        l[y]=l[x]+z,f[y]=x,dfs(y),size[x]+=size[y];
    }
}
void dfs_(int x)
{
    if(!top[x]) top[x]=x;
    int t=0;
    for(int i=head[x];i;i=Next[i])
    {
        int y=ver[i];
        if(y!=f[x]&&size[y]>size[t])
        t=y;
    }
    if(t) top[t]=top[x],dfs_(t);
    for(int i=head[x];i;i=Next[i])
    {
        int y=ver[i];
        if(y!=f[x]&&y!=t)
        dfs_(y);
    }
}
int lca(int x,int y)
{
    while(top[x]!=top[y])
    {
        if(d[top[x]]<d[top[y]]) swap(x,y);
        x=f[top[x]];
    }
    if(d[x]>d[y]) swap(x,y);
    return x;
}
int main()
{
    scanf("%d%d",&n,&t);
    fu(i,1,n-1)
    {
    	int x,y,z;
    	scanf("%d%d%d",&x,&y,&z);
    	add(x,y,z),add(y,x,z);
    }
    dfs(1);
    dfs_(1);
    while(t--)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",l[x]+l[y]-2*l[lca(x,y)]);
    }
    return 0;
}
```

---

## 作者：Dijkspfa (赞：3)

来一发Tarjan LCA，离线做法，思路还是维护前缀和。于是可以一遍dfs解决所有问题，求出lca后直接记录算出来的答案就行了,ans[lis] = len[u]+len[v]-2\*len[bcj(v)]。

感觉Tarjan是比较好写而且好懂的，N+Q的时间复杂度也非常优。




```cpp
#include <cstdio>
#define mxn 1007
#define gt(x) x = read()
using namespace std;
int n,q,cnte,cntq,pre[mxn],qpre[mxn],len[mxn],f[mxn],ans[mxn];
bool vis[mxn];
struct edge {int v,w,nxt; }e[mxn<<1];
struct qedge{int v,nxt,lis;}qe[mxn<<1];
inline int read()
{
    int out = 0;
    char c;
    while((c = getchar()) > '9' || c < '0');
    while(c >= '0' && c <= '9') 
        out = out * 10 + c - '0',c = getchar();
    return out;
}
inline void adde(int u,int v,int w)
{
    e[++cnte].v = v,e[cnte].w = w;
    e[cnte].nxt = pre[u],pre[u] = cnte;
    return;
}
inline void addq(int u,int v,int lis)
{
    qe[++cntq].v = v,qe[cntq].lis = lis;
    qe[cntq].nxt = qpre[u],qpre[u] = cntq;
    return;
}
int bcj(int x) {return f[x] == x ? x : f[x] = bcj(f[x]);}
void dfs(int p)
{
    vis[p] = 1,f[p] = p;
    for(int i = pre[p];i;i = e[i].nxt)
    {
        int s = e[i].v;    
        if(vis[s]) continue;
        len[s] = len[p] + e[i].w;
        dfs(s);
        f[s] = p;
    }
    for(int i = qpre[p];i;i = qe[i].nxt)
    {
        int v = qe[i].v;
        if(!vis[v]) continue;
        ans[qe[i].lis] = len[v] + len[p] - 2 * len[bcj(v)];
    }
    return;
}
int main()
{    int u,v,w;
    gt(n),gt(q);
    for(int i = 1;i < n;i++)
    {
        gt(u),gt(v),gt(w);
        adde(u,v,w),adde(v,u,w);
    }
    for(int i = 1;i <= q;i++)
    {
        gt(u),gt(v);
        addq(u,v,i),addq(v,u,i);
    }
    dfs(1);
    for(int i = 1;i <= q;i++) printf("%d\n",ans[i]);
    return 0;
}

```

---

## 作者：XHCuteDog (赞：1)

### 这个题是今天新学的知识:最近公共祖先的模板题QAQ
 由于前一天晚上补作业补到3点，，导致听课时睡昏了，，一觉醒来讲解已经到了尾声……
 不过作为蒟蒻，就要有蒟蒻的样子，经过默默地进行一些难以启齿的行为，我终究是快速A掉了这道题。
[题目传送门](https://www.luogu.org/problemnew/solution/P2912)
## 不得不说USACO的题还是很值得认真一做的，建议没有仔细读题并深入思考的盆友再去思考思考哦~~
 ok，注意题中这样一句话“在任意两个牧场间，有且仅有一条由若干道路组成的路径相连.也就是说，所有的道路构成了一棵树.”那么，存储就可以利用图的相关知识，最简洁明了易掌握的当然是链式前向星啦
```cpp
struct node{
       int y,w;
       };
node E[2*maxn];//用结构体实现前向星 
void add(int x,int y,int z)//基本插入 
{
     E[++id].y=y;
     E[id].w=z;
     next[id]=head[x];
     head[x]=id;
}
```
这段代码自然是一个基本操作了
### 下面思考一个问题，用什么来存储或是寻找某个点的第几个祖先呢？？？(由于本人不会插入图片)就用语言来描述吧，寻找X，Y的公共最近祖先的位置，这个必然是深度较浅的点的上方
为了方便进行寻找，我设置了anc[?][?？]数组，代表从？开始的第2^？？个祖先
```cpp
int lca(int x,int y)//返回X,Y的最近公共祖先的位置 
{
    if(dep[x]<dep[y])swap(x,y);
    for(int i=10;i>=0;i--)
      if(dep[anc[x][i]]>=dep[y])
        x=anc[x][i];
    if(x==y)return y;
    for(int i=10;i>=0;i--)
      if(anc[x][i]!=anc[y][i])
        x=anc[x][i],y=anc[y][i];
    return anc[x][0];
}
```
这段代码便用于寻找最近公共祖先的位置
## 至于更多的，，自我感觉没什么更多的，一部分解释留在代码的注释里，大家去寻找吧!
# 这就奉上AC
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,id=0;
const int maxn=500000;
int dep[maxn],anc[maxn][20];//dep[??]记录该点的深度,anc[x][i]记录X点的第2^i个祖先 
int head[maxn],next[2*maxn];//链式前向星基本东东 
int d[maxn];//记录从根节点到某点的距离. 
struct node{
       int y,w;
       };
node E[2*maxn];//用结构体实现前向星 
void add(int x,int y,int z)//基本插入 
{
     E[++id].y=y;
     E[id].w=z;
     next[id]=head[x];
     head[x]=id;
}
void dfs(int x,int fa)//查询到X点的距离d[x] 
{
     dep[x]=dep[fa]+1;
     for(int i=1;(1<<i)<=dep[x];i++)
       anc[x][i]=anc[anc[x][i-1]][i-1];
     for(int i=head[x];i;i=next[i])
     {
       int y=E[i].y;
       int w=E[i].w;
       if(y==fa)continue;
       anc[y][0]=x;
       d[y]=d[x]+w;
       dfs(y,x);
     }
}  
int lca(int x,int y)//返回X,Y的最近公共祖先的位置 
{
    if(dep[x]<dep[y])swap(x,y);
    for(int i=10;i>=0;i--)
      if(dep[anc[x][i]]>=dep[y])
        x=anc[x][i];
    if(x==y)return y;
    for(int i=10;i>=0;i--)
      if(anc[x][i]!=anc[y][i])
        x=anc[x][i],y=anc[y][i];
    return anc[x][0];
}
int main()
{
    scanf("%d%d",&n,&m); 
    for(int i=1;i<n;i++)//没得什么好说的 
    {
      int x,y,z;
      scanf("%d%d%d",&x,&y,&z);
      add(x,y,z);
      add(y,x,z);
    }
    dep[0]=0;//初始化,根节点的深度为0,到自身距离为0,第1个祖先是0, 
    d[1]=0;
    anc[1][0]=0;
    dfs(1,0);
    for(int i=1;i<=m;i++)
    {
      int x,y;
      scanf("%d%d",&x,&y);
      printf("%d\n",d[x]+d[y]-2*d[lca(x,y)]);//因为d[x],d[y]中含有重复的从根节点到公共最近祖先的距离 
    }
    return 0;
}

```
[蒟蒻的宝藏匣子](https://www.luogu.org/blog/sshilyzyx/)

---

## 作者：shadowice1984 (赞：1)

蒟蒻第一次写倍增。。。

这里简单说一下倍增的原理

任意一个正整数，都可以表示为几个2的n次幂之和。

根据这个原理，我们只需知道一个点上方的第2的n次方个祖先，就可以求出其所有祖先

（e。g。求第3个祖先可以表示为该点上方第二个祖先的第1个祖先）

同理，知道一个点上方的第2的n次方个祖先到该点的距离，即可求出该点到所有祖先的距离

那么，令father【i】【j】表示点i上方第2的j次方的祖先编号，d【i】【j】表示到father【i】【j】的距离

由2^n=2^(n-1)+2^(n-1）；

可得father【i】【j】=father【father【i】【j-1】】【j-1】；d【i】【j】=d【i】【j-1】+d【father【i】【j-1】】【j-1】；

上代码~

```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;
struct data//邻接表
{
    int next;int v;int val;
}edge[2010];int cnt;int alist[1010];
void add(int u,int v,int val)
{
    edge[++cnt].v=v;
    edge[cnt].val=val;
    edge[cnt].next=alist[u];
    alist[u]=cnt;return;
}
int d[1010][15];
int father[1010][15];
int depth[1010];//深度数组，作用一会说
int n;int q;
void dfs(int x)//深搜，完成祖先和祖先距离和深度关系
{
    for(int i=1;i<15;i++)
    {
        if(father[x][i-1]!=0)//递推f和d
        {
            father[x][i]=father[father[x][i-1]][i-1];
            d[x][i]=d[x][i-1]+d[father[x][i-1]][i-1];
        }
        else break;//0表示没有这个祖先，即距离太大了，那么更大的2^(n+1)也是0
    }
    int next=alist[x];
    while(next)//遍历出边
    {    
        int v=edge[next].v;int val=edge[next].val;
        if(v!=father[x][0])//显然不能爸爸是儿子的儿子，这就乱套了
        {
            father[v][0]=x;//初始化儿子
            d[v][0]=val;depth[v]=depth[x]+1;
                dfs(v);
        }
        next=edge[next].next;
    }
    return;
}
int lca(int u,int v)//标准的lca模板
{
    int res=0;//一定要赋值
    if(depth[u]<depth[v])swap(u,v);//钦定u更低
    int delta=depth[u]-depth[v];
    for(int i=0;i<15;i++)
    {
        if(delta&(1<<i))//把depth【u】和depth【v】的差拆成2的n次幂之和
        {
            res+=d[u][i];//更改u的同时更改d
            u=father[u][i];//更改u
        }
    }
    if(u==v)return res;//如果v是直系祖先，返回
    for(int i=14;i>=0;i--)//先选大的二进制位，有点贪心的意思
    {
        if(father[u][i]!=father[v][i])//移动
        {
            res+=d[u][i]+d[v][i];
            u=father[u][i];
            v=father[v][i];
        }
    }
    res+=d[u][0]+d[v][0];//最后father【u】【0】才是lca，因此加上u，v到lca距离
    return res;
}
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=0;i<n-1;i++)
    {
        int u;int v;int val;
        scanf("%d%d%d",&u,&v,&val);
        add(u,v,val);//双向边
        add(v,u,val);
    }
    dfs(1);//dfs
    for(int i=0;i<q;i++)
    {
        int u;int v;
        scanf("%d%d",&u,&v);
        printf("%d\n",lca(u,v));//处理询问
    }
    return 0;
}

```

---

## 作者：Awar3ness (赞：1)

没人写暴力题解啊，那我来一发

本题数据范围极小，1000\*1000

完全可以暴力来做，编程复杂度很小

代码：

```cpp
#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;
vector<pair<int,int> >e[1005];
int fa[1005],n,q,ans,deep[1005]={0,1},map[1005][1005],u,v,w;
void dfs(int now)
{
    for(int i=0;i<e[now].size();i++)
        if(e[now][i].first!=fa[now])//Èç¹ûÁ¬³öÈ¥µÄ±ß²»Ö¸ÏòËûµÄ¸¸Ç× 
        {
            fa[e[now][i].first]=now;//¸üÐÂ¸¸×Ó¹ØÏµ£¬Éî¶È¹ØÏµ 
            deep[e[now][i].first]=deep[now]+1;
            dfs(e[now][i].first);//¼ÌÐødfs 
        }
}
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<n;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        e[u].push_back(make_pair(v,w));
        e[v].push_back(make_pair(u,w));
        map[u][v]=map[v][u]=w;
    }
    dfs(1);
    for(int i=1;i<=q;i++)
    {
        scanf("%d%d",&u,&v);
        ans=0;
        while(u!=v)
        {
            if(deep[u]<deep[v]) swap(u,v);//Ã¿´Î¶¼ÈÃ±È½ÏÉîµÄµãÏÈ×ß 
            ans+=map[fa[u]][u];//ÀÛ¼ÓÈ¨Öµ 
            u=fa[u];//ÍùÉÏ×ß 
        }
        printf("%d\n",ans);
    }
}
```

---

## 作者：insprition (赞：1)

此题中用 len[i] 表示 i 到根距离

询问 x 和 y 的距离

答案可用 len[x] + len[y] - 2\*len[ lca(x,y) ]表示


而 lca 可以用树剖求出

len[] 在树剖求lca 的预处理中 可以顺带求出来


树剖求 lca 虽然不常用

但这并不代表 它的效率不高

我的 树剖代码 目前是本题 的 rank1

时间短 空间小

  
具体在我的

###**[博客](http://www.cnblogs.com/1227xq/p/6813288.html)**

里写了 树剖 lca

以及对于本题的 应用


---

## 作者：Link_Space (赞：0)

这道题的题面非常明了，就是给你一颗树，让你处理每一个询问，求两个点的距离，而本蒟蒻做这道题的时候脑袋一抽，并没有想到用LCA快速求解，写了一个极其暴力的Dijkstra，然而还很意外地直接过掉了，所以决定写一篇题解来纪念一下。


没什么大体思路，就是直接很粗暴的问一个就跑一遍DJ然后求距离就好了。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
typedef pair<int, int> PII;
int head[1000000];
int nxt[1000000];
int ver[1000000];
int link[1000000];
int cnt;
int dis[1000000];
void add(int x,int y,int z)
{
    nxt[++cnt] = head[x];
    head[x] = cnt;
    ver[cnt] = y;
    link[cnt] = z;
}
bool aim[1000000];
void djslm(int sta)
{
    priority_queue<PII, vector<PII>, greater<PII> > q;//注意此题需要堆优化，否则肯恩没法过
    memset(dis, 0x7f, sizeof dis);
    memset(aim, 0, sizeof aim);
    dis[sta] = 0;
    q.push({0, sta});
    while(!q.empty())
    {
        PII temp = q.top();
        q.pop();
        int lea = temp.first;
        int point = temp.second;
        if(aim[point])
            continue;
        aim[point] = 1;
        for (int i = head[point]; i;i=nxt[i])
        {
            int v0 = ver[i];
            if(dis[v0]>lea+link[i])
            {
                dis[v0] = lea + link[i];
                q.push({dis[v0], v0});
            }
        }
    }
}//DJ板子
int main()
{
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i < n;i++)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
        add(b, a, c);
    }
    for (int i = 1; i <= q;i++)
    {
        int sta;
        int las;
        scanf("%d%d", &sta, &las);
        djslm(sta);//每一次询问都跑一遍DJ
        printf("%d\n", dis[las]);
    }
}
```


---

## 作者：tcswuzb (赞：0)

## 题目描述
有N(2<=N<=1000)头奶牛，编号为1到W，它们正在同样编号为1到N的牧场上行走.为了方 便，我们假设编号为i的牛恰好在第i号牧场上.

有一些牧场间每两个牧场用一条双向道路相连，道路总共有N - 1条，奶牛可以在这些道路 上行走.第i条道路把第Ai个牧场和第Bi个牧场连了起来(1 <= A_i <= N; 1 <= B_i <= N)，而它的长度 是 1 <= L_i <= 10,000.在任意两个牧场间，有且仅有一条由若干道路组成的路径相连.也就是说，所有的道路构成了一棵树.

奶牛们十分希望经常互相见面.它们十分着急，所以希望你帮助它们计划它们的行程，你只 需要计算出Q(1 < Q < 1000)对点之间的路径长度•每对点以一个询问p1,p2 (1 <= p1 <= N; 1 <= p2 <= N). 的形式给出

```
Input
4 2 
2 1 2 
4 3 2 
1 4 3 
1 2 
3 2 
Output
2
7
```

## 题意分析

其实这道题就是 树剖 + LCA

至于[树剖](http://www.cnblogs.com/chinhhh/p/7965433.html)

首先 我们把边权下放到TA下面的点上

然后answer=路径上点权和-num[LCA(u,v)]*2

鉴于没有毒瘤的区间修改

本蒟蒻就写了比较简单的树状数组进行维护

# CODE:

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctime>
#include<queue>
#define IL inline
#define R register
#define int long long
#define N 10008
using namespace std;
template<typename T>IL void read(T &A)
{
    T x=0,f=1;char ch=getchar();
    while(!isdigit(ch))
    {
        if(ch=='-') f=0;ch=getchar();
    }
    while(isdigit(ch))
    {
        x=(x<<1)+(x<<3)+ch-'0';ch=getchar();
    }
    A=f ? x:-x;
}
int n,m,tot,cnt;
int num[N],id[N],wt[N];
struct Tree{
    int to,nex,w;
}e[N];
int fa[N][30];
int head[N];
int dep[N],siz[N],son[N],top[N];
int tre[N];
IL void add(int ai,int bi,int ci)
{
    e[++tot].to=bi;
    e[tot].w=ci;
    e[tot].nex=head[ai];
    head[ai]=tot;
}
IL void dfsa(int now,int fat)
{
    fa[now][0]=fat;dep[now]=dep[fat]+1;
    for(R int i=1;i<=25;++i)
     fa[now][i]=fa[fa[now][i-1]][i-1];
    for(R int i=head[now];i;i=e[i].nex)
    {
        int v=e[i].to;
        if(v==fa[now][0]) continue;
        dfsa(v,now);
    } 
}
IL void dfsb(int now,int fat)
{
    siz[now]=1;int maxson=-1;
    for(R int i=head[now];i;i=e[i].nex)
    {
        int v=e[i].to;
        if(v==fa[now][0]) continue;
        num[v]=e[i].w;
        dfsb(v,now);
        siz[now]+=siz[v];
        if(siz[v]>maxson) {son[now]=v;maxson=siz[v];}
    }
}
IL void dfsc(int now,int topf)
{
    id[now]=++cnt;
    wt[cnt]=num[now];
    top[now]=topf;
    if(!son[now]) return;
    dfsc(son[now],topf);
    for(R int i=head[now];i;i=e[i].nex)
    {
        int v=e[i].to;
        if(v==fa[now][0]||v==son[now]) continue;
        dfsc(v,v);
    }
}
IL void chande(int x,int y)
{
    while(x<=n)
    {
        tre[x]+=y;
        x+=(x&-x);
    }
}
IL int get(int x)
{
    int ans=0;
    while(x)
    {
        ans+=tre[x];
        x-=(x&-x);
    }
    return ans;
}
IL int qury(int nowx,int nowy)
{
    int ans=0;
    while(top[nowx]!=top[nowy])
    {
        if(dep[top[nowx]]<dep[top[nowy]]) swap(nowx,nowy);
        ans+=(get(id[nowx])-get(id[top[nowx]]-1));
        nowx=fa[top[nowx]][0];
    }
    if(dep[nowx]>dep[nowy]) swap(nowx,nowy);
    ans=ans-get(id[nowx]-1)+get(id[nowy]);
    return ans;
}
IL int LCA(int nowx,int nowy)
{
    if(dep[nowx]<dep[nowy]) swap(nowx,nowy);
    for(R int i=25;i>=0;--i) 
    if(dep[fa[nowx][i]]>=dep[nowy]) nowx=fa[nowx][i];
    if(nowy==nowx) return nowx;
    for(R int i=25;i>=0;--i)
    if(fa[nowx][i]!=fa[nowy][i]) 
    nowx=fa[nowx][i],nowy=fa[nowy][i];
    return fa[nowx][0];
}
signed main()
{
    read(n);read(m);
    for(R int i=1;i<n;++i)
    {
        int x,y,z;
        read(x);read(y);read(z);
        add(x,y,z);add(y,x,z);
    }
    dfsa(1,0);dfsb(1,0);dfsc(1,1);
//    for(R int i=1;i<=cnt;++i) printf("wt is %lld\n",wt[i]);
    for(R int i=1;i<=n;++i) chande(i,wt[i]);
    for(R int i=1;i<=m;++i)
    {
        int x,y;read(x);read(y);
        int lck=LCA(x,y);
//        cout<<" sdifh "<<lck<<endl;
        printf("%lld\n",qury(x,y)-num[lck]);
    }
    return 0;
}
```

# _NOIP 2018 RP++_

---

## 作者：Zechariah (赞：0)

这题为什么是普及+/提高啊...
直接构建一个无向图用spfa求距离就行了
上代码
```cpp
#include <bits/stdc++.h>
#define N 10000+100
using namespace std;
int p[N], dist[N], b[N], nt[N], q[N], w[N], sum;
bool flag[N];
void add(int x, int y, int z)
{
	b[++sum] = y;
	w[sum] = z;
	nt[sum] = p[x];
	p[x] = sum;
}
int spfa(int x, int y)
{
	memset(dist, 63, sizeof(dist));
	dist[x] = 0;
	q[1] = x;
	int head = 1, tail = 0;
	while (tail <= head)
	{
		int k = q[++tail];
		int e = p[k];
		flag[k] = false;
		while (e)
		{
			int kk = b[e];
			if (dist[kk] - w[e] > dist[k])
			{
				dist[kk] = dist[k] + w[e];
				if (!flag[kk])
				{
					flag[kk] = true;
					q[++head] = kk;
				}
			}
			e = nt[e];
		}
	}
	return dist[y];
}

int main(void)
{
	int m, n;
	scanf("%d%d", &n, &m);
	for (int i = 1; i != n; ++i)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		add(x, y, z);
		add(y, x, z);
	}
	while (m--)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		printf("%d\n", spfa(x, y));
	}
	return 0;
}
```

---

## 作者：Dream_It_Possible (赞：0)

~~不可思议，这题最短路径也能过~~

我们将ai到bi连一条权值为ci的路径，然后扫S到T的最短路径，要**用SPFA**或**用floyd先预处理，然后O(1)回答即可。**

SPFA(M*K*E) 注：K不定，平均值为2

floyd(N^3+M)

SPFA代码（floyd自己想）：

```
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
const int MAXN=2501;
typedef vector<int> Vec;//定义vector容器
Vec Map[MAXN],Val[MAXN];
int N,M,S,T;
 
void init()
{
	scanf("%d %d\n",&N,&M);
	int a,b,v;
	for(int i=1;i<=N-1;i++)
	{
		scanf("%d %d %d\n",&a,&b,&v);
		Map[a].push_back(b);//连边
		Val[a].push_back(v);//搭权值
		Map[b].push_back(a);//连边
		Val[b].push_back(v);//搭权值
	}
}
 
int dist[MAXN];
int flag[MAXN];
const int INF=1000000000;
queue<int>Q;//队列，对SPFA进行优化
void SPFA()
{
	for(int i=1;i<=N;i++)
		dist[i]=INF,flag[i]=0;//初始化
	dist[S]=0,flag[S]=1;
	Q.push(S);
	int t,tmp;
	while(!Q.empty())
	{
		t=Q.front();//取队首
		Q.pop();
		flag[t]=0;
		for(unsigned int i=0;i<Map[t].size();i++)//遍历与他相邻的节点
		{
			tmp=dist[t]+Val[t][i];
			if(tmp<dist[Map[t][i]])//松弛
			{
				dist[Map[t][i]]=tmp;
				if(!flag[Map[t][i]])
				{
					Q.push(Map[t][i]);
					flag[Map[t][i]]=1;//记录已访问
				}
			}
		}
	}
	printf("%d\n",dist[T]);//输出
	return;
}
 
int main()
{
	init();
	int i;
	for (i=1;i<=M;i++)
	{
		scanf("%d %d",&S,&T);
		memset(dist,0,sizeof(dist));//初始化
		memset(flag,0,sizeof(flag));//初始化
		SPFA();//扫从S到T最短路径
	}
	return 0;
}
```

---

## 作者：Kwork (赞：0)

求LCA，倍增维护向上的距离。

首先用倍增预处理出每个节点向上走2^n步的祖先以及距离，然后二分求出LCA，根据LCA再求出每个点到LCA的距离然后相加得出答案即可。然后就没了。数据还算小的。这里不详细解释LCA的求法。

-------------------------------------------------------------------------------------------------------------------------------------------------

```cpp
#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
//
using namespace std;
//
const int MAXN=1005,log_n=11;
//
struct edge{int to,w;};
vector<edge>G[MAXN];
int n,m,depth[MAXN],parent[log_n+1][MAXN],dis[log_n+1][MAXN];
// 
inline void read(int &n){
    n=0;
    char ch=getchar();
    while(ch<'0' || ch>'9') ch=getchar();
    do{
        n=n*10+ch-'0';
        ch=getchar();
    }while(ch>='0' && ch<='9');
    return;
}
inline void add_edge(int u,int v,int w){
    edge e;
    e.to=v,e.w=w;
    G[u].push_back(e);
    return;
}
void in_data(){
    int u,v,w;
    read(n);read(m);
    for(int i=1;i<n;i++){
        read(u);read(v);read(w);
        add_edge(u,v,w);
        add_edge(v,u,w);
    }
    return;
}
void dfs(int u,int fa,int dep,int w){
    parent[0][u]=fa;
    dis[0][u]=w;
    depth[u]=dep;
    int v,ww;
    for(int i=0;i<G[u].size();i++){
        v=G[u][i].to;
        if(v==fa) continue;
        ww=G[u][i].w;
        dfs(v,u,dep+1,ww);
    }
    return;
}
int lca(int u,int v){
    if(depth[u]>depth[v]) swap(u,v);
    int tmp=depth[v]-depth[u];
    for(int i=0;i<=log_n;i++){
        if((tmp>>i)&1)
            v=parent[i][v];
    }
    if(u==v) return u;
    for(int i=log_n;i>=0;i--){
        if(parent[i][u]!=parent[i][v]){
            v=parent[i][v];
            u=parent[i][u];
        }
    }
    return parent[0][u];
}
int get_dis(int u,int v,int ancestor){
    int ans=0;
    int tmp=depth[u]-depth[ancestor];
    for(int i=0;i<=log_n;i++){
        if((tmp>>i)&1){
            ans+=dis[i][u];
            u=parent[i][u];
        }
    }
    tmp=depth[v]-depth[ancestor];
    for(int i=0;i<=log_n;i++){
        if((tmp>>i)&1){
            ans+=dis[i][v];
            v=parent[i][v];
        }
    }
    return ans;
}
void solve_query(){
    dfs(1,0,0,0);
    for(int i=1;i<=log_n;i++){
        for(int u=1;u<=n;u++){
            parent[i][u]=parent[i-1][parent[i-1][u]];
            dis[i][u]=dis[i-1][u]+dis[i-1][parent[i-1][u]];
        }
    }
    int u,v;
    while(m--){
        read(u);read(v);
        int ancestor=lca(u,v);
        int ans=get_dis(u,v,ancestor);
        printf("%d\n",ans);
    }
    return;
}
int main(){
    in_data();
    solve_query();
    return 0;
}
```

---

