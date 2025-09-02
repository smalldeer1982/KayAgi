# Ants

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=447&page=show_problem&problem=4157

[PDF](https://uva.onlinejudge.org/external/14/p1411.pdf)

给定平面上的 $N$ 个黑点和 $N$ 个白点（共 $2N$ 个点），请找到一种方案，对于每一个黑点，找到一个白点，用线段把黑点和白点连接，保证最后**任意两条线段无公共点（不相交）**。

## 说明/提示

## 数据范围与提示

$1\leq N\leq 100, |x|, |y|\leq 10^4$。

保证无三点共线。数据保证有解。

$\small{\text{Statement fixed by @Starrykiller.}}$

## 样例 #1

### 输入

```
5
-42 58
44 86
7 28
99 34
-13 -59
-47 -44
86 74
68 -75
-68 60
99 -6```

### 输出

```
4
2
1
5
3```

# 题解

## 作者：VenusM1nT (赞：10)

本文**代码**前置芝士：[费用流](https://www.luogu.org/blog/Venus/zui-xiao-fei-yong-zui-tai-liu-ek-zkw-fei-yong-liu)

---
# 推出结论

题意已经讲的很清楚了，要使黑白点之间的连线不相交。

计算几何当然不是我们的强项，我们尝试把问题转换一下。

首先看不合法情况：

![](http://wx2.sinaimg.cn/mw690/0060lm7Tly1fxwqyn8hsjj30bb05i742.jpg)

并看不出什么端倪，此时我们再把合法情况连接起来：

![](http://wx4.sinaimg.cn/mw690/0060lm7Tly1fxwr0u1yvaj30al05igld.jpg)

此时依然看不出什么，我们再把原有的线段连上去：

![](http://wx4.sinaimg.cn/mw690/0060lm7Tly1fxwr27xvz2j30bs05e742.jpg)

此时我们会发现，不合法的线段和合法的线段组成了两个三角形，于是我们可以从三角形出发推结论。

三角形有哪些结论呢？~~抛去什么正弦定理余弦定理，~~三角形最基本的一个定理，就是**两边之和大于第三边，两边之差小于第三边**。

我们带着这个定理再去看上图，我们可以发现，合法情况的连线，**总长度明显比不合法情况的小**。

读者不妨自己再画多点的情况，然后自己研究一下。

至此，我们就得出了这道题最重要的结论：题意可以转化为求**让每条线段的长度和最小的方案**。

---
# 代码实现

于是这道题就可以和毒瘤计算几何脱开关系了，然后我们再来考虑怎么算长度和最小的方案。

首先，图是黑白染色的，这说明这张图必定可以分为一张**左右点数相同的二分图**，因为不用考虑交叉问题，所以我们可以直接建出一张二分图。

然后我们发现，这张二分图的边是**有权值**的，权值就是长度，既然看到权值，我们很自然就想到了**带权二分图匹配**，而这道题要让我们求长度最小，所以就是**二分图最小权匹配**。

至此，我们就求出了这道题的做法。

如果会$KM$的读者就可以去写代码了，我因为太菜了不会$KM$，在这里讲一讲**费用流**的做法。

这道题对于费用流来说是非常友好的，因为求的是**二分图最小权匹配**，所以只要套最小费用最大流的模板即可。

建模方法也很简单，如下：

> 1、建立超级源超级汇。

> 2、从超级源向左侧点连流量为$1$，费用为$0$的边。

> 3、从左侧点向右侧点连流量为$1$，费用为两点欧几里得距离的边。

> 4、从右侧点向超级汇连流量为$1$，费用为$0$的边。

> 5、跑最小费用最大流。

跑完之后，我们来考虑输出方案。我们知道，在跑完最小费用最大流之后，如果左侧点连向右侧点的边**满流**的话，就代表这两个点就是被配对的，所以我们在跑完之后，遍历左侧点，然后对于它**连出去**的边判断是否满流，即流量是否为$0$，如果满流就输出这条边的终点即可。

此时有人要问出最后一个问题：如果终点是超级源怎么办呢？

由于左右点数相同，所以每个左侧点绝对会有一个右侧点与之配对，所以从超级源连向左侧点的边**必定满流**，而在满流的情况下，左侧点连向超级源的边的流量必定为$1$，所以就不用担心这种情况了。

我写了两种费用流的代码，如下。

$EK$费用流（410ms）：

```cpp
#include<bits/stdc++.h>
#define eps 1e-5
#define inf 1010580540
using namespace std;
queue <int> q;
int cnt=1,fst[505],nxt[200005],to[200005],w[200005],cur[505];
int n,S,T,fr[505],f[505],ax[105],ay[105],bx[105],by[105];
bool inq[505],vis[505];
double cot[200005],dis[505];
void AddEdge(int u,int v,int c,double fl)
{
    to[++cnt]=v;
    nxt[cnt]=fst[u];
    fst[u]=cnt;
    w[cnt]=c;
    cot[cnt]=fl;
}
bool Spfa()
{
    for(int i=S;i<=T;i++) dis[i]=inf;
    memset(inq,0,sizeof(inq));
    q.push(S);
    dis[S]=0;
    inq[S]=1;
    f[S]=inf;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        inq[u]=0;
        for(int i=fst[u];i;i=nxt[i])
        {
            int v=to[i];
            if(dis[v]>dis[u]+cot[i] && w[i])
            {
                dis[v]=dis[u]+cot[i];
                f[v]=min(f[u],w[i]);
                fr[v]=i;
                if(!inq[v])
                {
                    q.push(v);
                    inq[v]=1;
                }
            }
        }
    }
    return dis[T]<inf-eps;
}
void ModifyFlow()
{
    int u=T;
    while(u!=S)
    {
        int i=fr[u];
        w[i]-=f[T];
        w[i^1]+=f[T];
        u=to[i^1];
    }
    maxflow+=f[T];
}
void MCMF()
{
    while(Spfa()) ModifyFlow();
}
double Calc(int x,int y)
{
    return sqrt((double)(ax[x]-bx[y])*(ax[x]-bx[y])+(double)(ay[x]-by[y])*(ay[x]-by[y]));
}
int main()
{
    while(cin>>n)
    {
        cnt=1;
        memset(fst,0,sizeof(fst));
        S=0;
        T=n*2+1;
        for(int i=1;i<=n;i++) scanf("%d %d",&ax[i],&ay[i]);
        for(int i=1;i<=n;i++) scanf("%d %d",&bx[i],&by[i]);
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                double d=Calc(i,j);
                AddEdge(i,j+n,1,d);
                AddEdge(j+n,i,0,-d);
            }
        }
        for(int i=1;i<=n;i++)
        {
            AddEdge(S,i,1,0);
            AddEdge(i,S,0,0);
        }
        for(int i=1;i<=n;i++)
        {
            AddEdge(i+n,T,1,0);
            AddEdge(T,i+n,0,0);
        }
        MCMF();
        for(int i=1;i<=n;i++)
        {
            for(int j=fst[i];j;j=nxt[j])
            {
                int v=to[j];
                if(!w[j])
                {
                    printf("%d\n",v-n);
                    break;
                }
            }
        }
    }
    return 0;
}
```

$zkw$费用流（240ms）：

```cpp
#include<bits/stdc++.h>
#define eps 1e-5
#define inf 1010580540
using namespace std;
deque <int> q;
int cnt=1,fst[505],nxt[200005],to[200005],w[200005],cur[505];
int n,S,T,ax[105],ay[105],bx[105],by[105];
bool inq[505],vis[505];
double cot[200005],dis[505];
void AddEdge(int u,int v,int c,double fl)
{
    to[++cnt]=v;
    nxt[cnt]=fst[u];
    fst[u]=cnt;
    w[cnt]=c;
    cot[cnt]=fl;
}
bool Spfa()
{
    for(int i=S;i<=T;i++) dis[i]=inf;
    memset(inq,0,sizeof(inq));
    q.push_front(T);
    dis[T]=0;
    inq[T]=1;
    while(!q.empty())
    {
        int u=q.front();
        q.pop_front();
        inq[u]=0;
        for(int i=fst[u];i;i=nxt[i])
        {
            int v=to[i];
            if(dis[v]-dis[u]+cot[i]>eps && w[i^1])
            {
                dis[v]=dis[u]-cot[i];
                if(!inq[v])
                {
                    if(!q.empty() && dis[v]<dis[q.front()]) q.push_front(v);
                    else q.push_back(v);
                    inq[v]=1;
                }
            }
        }
    }
    return dis[S]!=inf;
}
int Dfs(int u,int flow)
{
    vis[u]=1;
    if(u==T || !flow) return flow;
    int used=0;
    for(int i=cur[u];i;i=nxt[i])
    {
        cur[u]=i;
        int v=to[i];
        if(dis[v]-dis[u]+cot[i]<=eps && w[i] && !vis[v])
        {
            int fl=Dfs(v,min(flow,w[i]));
            if(fl)
            {
                used+=fl;
                flow-=fl;
                w[i]-=fl;
                w[i^1]+=fl;
                if(!flow) break;
            }
        }
    }
    return used;
}
void zkwMCMF()
{
    while(Spfa())
    {
        vis[T]=1;
        while(vis[T])
        {
            memcpy(cur,fst,sizeof(fst));
            memset(vis,0,sizeof(vis));
            int fl=Dfs(S,inf);
        }
    }
}
double Calc(int x,int y)
{
    return sqrt((double)(ax[x]-bx[y])*(ax[x]-bx[y])+(double)(ay[x]-by[y])*(ay[x]-by[y]));
}
int main()
{
    while(cin>>n)
    {
        cnt=1;
        memset(fst,0,sizeof(fst));
        S=0;
        T=n*2+1;
        for(int i=1;i<=n;i++) scanf("%d %d",&ax[i],&ay[i]);
        for(int i=1;i<=n;i++) scanf("%d %d",&bx[i],&by[i]);
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                double d=Calc(i,j);
                AddEdge(i,j+n,1,d);
                AddEdge(j+n,i,0,-d);
            }
        }
        for(int i=1;i<=n;i++)
        {
            AddEdge(S,i,1,0);
            AddEdge(i,S,0,0);
        }
        for(int i=1;i<=n;i++)
        {
            AddEdge(i+n,T,1,0);
            AddEdge(T,i+n,0,0);
        }
        zkwMCMF();
        for(int i=1;i<=n;i++)
        {
            for(int j=fst[i];j;j=nxt[j])
            {
                int v=to[j];
                if(!w[j])
                {
                    printf("%d\n",v-n);
                    break;
                }
            }
        }
    }
    return 0;
}
```

---

## 作者：G_X_J (赞：8)

题意：给定平面中 $n$ 个黑点，$n$ 个白点，且不存在任意三点共线。一个黑点一个白点凑成一对，得到 $n$ 对点。每对点连一条线，要求没有线段相交。

方法：分治。

将纵坐标最小的点挑出来，如果满足条件的有多个，任选一个即可，这样剩下的点没有在这个点下面的。不妨设这个点为黑点，命名为点 $A$。

按照与 $A$ 的极角的顺序一个一个遍历剩下的点，并尝试把它和 $A$ 连线。如果遍历到一个白点，且之前遍历过的黑白点个数相等，那么连线成功。

这时候，发现遍历过的点和没有遍历过的点被这条线段所确定的直线分为两半，且两侧都能保证黑点白点个数相同。那么，将这两组点分别配对连线，可以保证不会有线段穿过那条分界的直线。所以，直线两侧分成两个子问题继续求解。


```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
const int maxn=114;
int n;
struct pnt{
    int x,y,col,idx;//col==0: colony; col==1:apple trees; idx表示下标;
    bool operator <(const pnt &a)const{
        return y<a.y;
    }
};
pnt operator -(const pnt &a,const pnt &b){
    return pnt{a.x-b.x,a.y-b.y,a.col,a.idx};
}
void rd(pnt &a,int col,int idx){//read
    scanf("%d%d",&a.x,&a.y);
    a.col=col,a.idx=idx;
}
bool cmp(const pnt &a,const pnt &b){
    return atan2(a.x,a.y)>=atan2(b.x,b.y);
}
pnt cor[maxn<<1];//保存所有点
int ans[maxn];//保存连线方案
void solve(int l,int r)//区间左闭右开
{
    if(l>=r)return;
    sort(cor+l,cor+r);//按照y排序
    rep(i,l+1,r-1)cor[i]=cor[i]-cor[l];
    sort(cor+l+1,cor+r,cmp);//极角排序
    int cnt=0;//用来判断黑白点个数是否相等，每遇到一个点，根据颜色选择+1或者-1
    rep(i,l+1,r-1)
    {
        if(cnt==0&&(cor[l].col^cor[i].col))//连线成功
        {
            cor[l].col?ans[cor[i].idx]=cor[l].idx:ans[cor[l].idx]=cor[i].idx;
            solve(l+1,i),solve(i+1,r);
            return;
        }
        cnt+=(cor[i].col?-1:1);
    }
}
int main()
{
    while(scanf("%d",&n)==1)
    {
        rep(i,1,(n<<1))//读取n*2个点
            rd(cor[i],((i-1)/n)?1:0,(i-1)%n+1);
        solve(1,(n<<1)|1);
        rep(i,1,n)
            printf("%d\n",ans[i]);
        puts("");
    }
    return 0;
}
```


---

## 作者：fqEason (赞：4)

题解区都是 KM 算法，唯一的一篇费用流还是用的 EK，我来一发 dinic。 

[这个大佬](https://www.luogu.com.cn/blog/Venus/solution-uva1411)已经清晰地说明了费用流的思路，在此不赘述。

在稀疏图中，EK 算法与 dinic 算法的速度相差不大，但是在稠密图中，dinic 算法要较 EK 快得多，因此，dinic 算法有时有着更大的优势。

## code
```cpp
#include <bits/stdc++.h>
#define MAX 1000001
using namespace std;
int n,m,s,t,ans;
double cost;
struct node{
    int to,w,next;
    double c;
}edge[MAX];
struct point{
    double x,y;
}b[MAX],w[MAX];
int head[MAX],cnt=1;
double dis[MAX];
bool vis[MAX];
double distant(point a, point b) {
    return sqrt(1.0*(a.x-b.x)*(a.x-b.x)+1.0*(a.y-b.y)*(a.y-b.y));
}
//两点距离计算
void add(int u, int v, int w, double c) {
    edge[++cnt].to=v;
    edge[cnt].w=w;
    edge[cnt].c=c;
    edge[cnt].next=head[u];
    head[u]=cnt;
}
//链式前向星
bool bfs() {
    memset(vis,0,sizeof(vis));
    for (int i=0;i<=cnt;i++) dis[i]=1145141919;
    queue<int>q;
    q.push(s);
    vis[s]=true;
    dis[s]=0;
    while(q.size()) {
        int u=q.front();
        vis[u]=false;
        q.pop();
        for (int i=head[u];i;i=edge[i].next) {
            int v=edge[i].to;
            if (dis[v]>dis[u]+edge[i].c&&edge[i].w) {
                dis[v]=dis[u]+edge[i].c;
                if (!vis[v]) {
                    vis[v]=true;
                    q.push(v);
                }
            }
        }
    }
    return (dis[t]!=1145141919);
}
int dfs(int u, int flow) {
    if (u==t) {
        vis[t]=true;
        ans+=flow;
        return flow;
    }
    int used=0;
    double rlow;
    vis[u]=1;
    for (int i=head[u];i;i=edge[i].next) {
        int v=edge[i].to;
        if ((vis[v]==0||v==t)&&edge[i].w&&dis[v]==dis[u]+edge[i].c) {
            if (rlow=dfs(v,min(flow-used,edge[i].w))) {
                cost+=edge[i].c*rlow;
                edge[i].w-=rlow;
                edge[i^1].w+=rlow;
                used+=rlow;
                if (used==flow) break;
            }
        }
    }
    return used;
}
void dinic() {
    while(bfs()) {
        vis[t]=true;
        while(vis[t]) {
            memset(vis,0,sizeof(vis));
            dfs(s,INT_MAX);
        }
    }
}
//dinic最小费用最大流板子
int main() {
    cin >> n;
    s=0,t=2*n+1;
    for (int i=1;i<=n;i++) cin >> b[i].x >> b[i].y;
    for (int i=1;i<=n;i++) cin >> w[i].x >> w[i].y;
    for (int i=1;i<=n;i++) {
        for (int j=1;j<=n;j++) {
            double nowdis=distant(b[i],w[j]);
            add(i,j+n,1,nowdis);
            add(j+n,i,0,-nowdis);
        }
    }
    for (int i=1;i<=n;i++) {
        add(s,i,1,0);
        add(i,s,0,0);
    }
    for (int i=1;i<=n;i++) {
        add(i+n,t,1,0);
        add(t,i+n,0,0);
    }
    //分别从超级源点和超级汇点向黑白点连边
    dinic();
    for (int i=1;i<=n;i++) {
        for (int u=head[i];u;u=edge[u].next) {
            int v=edge[u].to;
            if (!edge[u].w) {
                cout << v-n << '\n';
                break; 
            }
        }
    }
    //寻找边是否残量为0，是的话输出终点
    return 0;
}
```
~~天知道为什么我这个 dinic 比 EK 还慢，大概是人傻常数大罢。~~

---

## 作者：JK_LOVER (赞：4)

## 题意
给你 $n$ 个白点和 $n$ 个黑点，求一种匹配方式，使匹配的白点与黑点的连边没有交点。[QAQ](https://www.luogu.com.cn/blog/xzc/solution-uva1411)
## 分析
这道题只要求求出一种方案数，所以我们可以只找一种一定满足这个条件的方案。


- 这里使用数学归纳法来证明，如果已经有 $n-1$ 个白点和 $n-1$ 个黑点已经匹配好了，那么现在再加入一对新点。如果直接链接，就会这样。
![](https://cdn.luogu.com.cn/upload/image_hosting/53mgu5wn.png)
- 但是现在就线段和线段就有规范相交了，是不合法的，所以要考虑调整，那么下图的紫色的边就是一种可行的方式，但是我们发现，我们走紫色的边，还不如直接链接这两个点。所以由此猜测构造方法。
![](https://cdn.luogu.com.cn/upload/image_hosting/10tugz8t.png)
- 匹配后距离和最小的一定是一种可行方案。

- 如果匹配后仍然有交点，那我们完全可以将靠近的连边，但这与距离和最小相违背。所以匹配后距离和最小一定是一组匹配方案。

那么现在这道题就转化为一道二分图完美匹配问题了，可以用 $KM$ 或者是 $MinCostMaxflow$ 求解，前者的时间复杂度更优为 $O(n^3)$ 。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 210;
const int M = N*N;
const int inf = 0x3f3f3f3f;
int read(){
	int x = 0,f = 0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}

struct Edge{int to,nxt,cap,flow;double cost;}e[M<<1];
struct Node{int x,y;}A[N];
int n,cnt=-1,head[N],lastn[N],laste[N],a[N],S,T;
double dist[N];
bool vis[N];
double dis(Node a,Node b)
{
	return sqrt((double)(a.x-b.x)*(a.x-b.x)+(double)(a.y-b.y)*(a.y-b.y));
}

void add(int x,int y,int cap,double cost)
{
	e[++cnt].cap = cap;e[cnt].flow = 0;
	e[cnt].to = y;e[cnt].cost = cost;
	e[cnt].nxt = head[x];head[x] = cnt; 
}

bool Bfs(int s,int t)
{
	for(int i = 1;i <= t;i++) 
	lastn[i] = laste[i] = a[i] = vis[i] = 0,dist[i] = 1e10;
	queue<int> Q;
	a[s] = inf; dist[s] = 0;
	Q.push(s);vis[s] = 1;
	while(Q.size())
	{
		int x = Q.front();Q.pop();vis[x] = 0;
		for(int i = head[x];~i;i = e[i].nxt)
		{
			int y = e[i].to;
			if(e[i].cap > e[i].flow)
			{
				if(dist[y] > dist[x] + e[i].cost)
				{
					dist[y] = dist[x] + e[i].cost;
					laste[y] = i;
					lastn[y] = x;
					a[y] = min(a[x],e[i].cap - e[i].flow);
					if(vis[y]) continue;
					Q.push(y);
					vis[y] = 1;
				}
			}
		}
	}
	return a[t] > 0;
}

void Ek(int s,int t)
{
	while(Bfs(s,t))
	{
		int k = t;
		while(k != s)
		{
			e[laste[k]].flow += a[t];
			e[laste[k]^1].flow -= a[t];
			k = lastn[k];
		}
	}
}

int main()
{
	while(scanf("%d",&n)!=EOF)
	{
		memset(head,-1,sizeof(head));
		cnt = -1;
		S = 2*n+1;T = S+1;
		for(int i = 1;i <= n;i++) scanf("%d %d",&A[i].x,&A[i].y);
		for(int i = 1+n;i <= n*2;i++) scanf("%d %d",&A[i].x,&A[i].y);
		for(int i = 1;i <= n;i++) add(S,i,1,0),add(i,S,0,0);
		for(int i = 1+n;i <= n*2;i++) add(i,T,1,0),add(T,i,0,0);
		for(int i = 1;i <= n;i++)
		{
			for(int j = 1+n;j <= n*2;j++)
			{
				add(i,j,1,dis(A[i],A[j]));
				add(j,i,0,-dis(A[i],A[j]));
			}
		}
		Ek(S,T);
		for(int i = 1;i <= n;i++)
		{
			for(int j = head[i];~j;j=e[j].nxt)
			{
				if(e[j].cap > 0 && e[j].flow == e[j].cap)
				{
					printf("%d\n",e[j].to-n);
					break;
				}
			}
		}
	}
	return 0;
} 
/*
5
-42 58
44 86
7 28
99 34
-13 -59
-47 -44
86 74
68 -75
-68 60
99 -60
*/
```


---

## 作者：逃离地球 (赞：3)

[题目链接](https://www.luogu.org/problem/UVA1411)

蒟蒻来写一篇**KM算法**的题解。

首先，如果所有线段不相交，那么线段长度之和一定最小。证明很简单，在这里不再赘述。（提示：三角形两边之和大于第三边）

那么这道题就转化为了一道带权二分图匹配问题，可以使用费用流求解。又由于黑白点数相同，所以带权最大匹配一定是完备匹配，故可以用KM算法求解。

若不会KM算法，请到[这里](https://blog.csdn.net/sixdaycoder/article/details/47720471)学习。

然后就把KM算法的板子改一下，在每个黑点与白点之间连一条权值为距离的边，就可以A了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

const double INF=1e9;

double Map[101][101],la[101],lb[101],va[101],vb[101],upd[101],delta;//一定要开double
int match[101],n;

bool dfs(int x){
	va[x]=1;
	for(int i=1;i<=n;i++){
		if(!vb[i]){
			if(fabs(la[x]+lb[i]-Map[x][i])<=0.0001){//注意精度
				vb[i]=1;
				if(!match[i]||dfs(match[i])){
					match[i]=x;
					return true;
				}
			}
			else{
				upd[i]=min(upd[i],la[x]+lb[i]-Map[x][i]);
			} 
		}
	}
	return false;
}

void KM(){//KM算法，不多解释
	for(int i=1;i<=n;i++){
		la[i]=-INF;
		lb[i]=0;
		for(int j=1;j<=n;j++){
			la[i]=max(la[i],Map[i][j]);
		}
	}
	
	for(int i=1;i<=n;i++){
		while(1){
			memset(va,0,sizeof(va));
			memset(vb,0,sizeof(vb));
			for(int i=1;i<=n;i++){
				upd[i]=INF;
			}
			if(dfs(i)){
				break;
			}
			delta=INF;
			for(int j=1;j<=n;j++){
				if(!vb[j]) delta=min(delta,upd[j]);
			}
			for(int j=1;j<=n;j++){
				if(va[j]) la[j]-=delta;
				if(vb[j]) lb[j]+=delta;
			}
		}
	}
}

void init(){
	memset(Map,0,sizeof(Map));
	memset(match,0,sizeof(match));
}

int main() {
	double x1[101],x2[101],y1[101],y2[101];
	while(scanf("%d",&n)!=EOF){
		init();
		
		for(int i=1;i<=n;i++){
			scanf("%lf %lf",&x2[i],&y2[i]);
		}
		for(int i=1;i<=n;i++){
			scanf("%lf %lf",&x1[i],&y1[i]);
		}
		
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				Map[i][j]=-double(sqrt((x1[i]-x2[j])*(x1[i]-x2[j])+(y1[i]-y2[j])*(y1[i]-y2[j])));
			}
		}//计算所有黑白点之间的距离，并连边
		KM();//KM求带权匹配
		for(int i=1;i<=n;i++){
			printf("%d\n",match[i]);
		}//输出结果
	}
    return 0;
}
```

[$ \LARGE\texttt{\color{red} My}\texttt{\color{blue} Blog}$](https://www.cnblogs.com/juruoyqr/)


---

## 作者：Ofnoname (赞：3)

KM算法的模板题。KM算法可以求解带权二分图的最大匹配，但是只能做出“一定有解且解是完全匹配的情况”。

由于本题求解的是最小值，所以计算两点距离时要取负数，才能计算“最大匹配”。简要说一下KM算法流程。

1. 给左部点，右部点设置“期望值”（这里设为`lx`,`ly`）。左部点初始化为它能连接的最大边权（每个点都希望连到最大边权），右部点初始化为0。但是这道题边权为负，所以可以省略初始化过程。

2. 跑匈牙利增广路，给第一个点找匹配点，限制条件为`lx[i]+ly[i]=d[i][j]`，即期望之和要等于边权。

3. 此时多半是找不到的，对于发生冲突的点（即跑匈牙利时use被标记过的点，要满足它们的其他选择所需要改变的值(让其满足`lx[i]+ly[i]=d[i][j]`)，记为d）。我们把跑匈牙利时搜到的所有点更新期望值，左部点减少d，让其满足其他匹配要求，右部点则增加d。

4. 再跑一次匈牙利增广路，如果还不行就继续更新期望再跑，早晚可以跑出来。

5. 回到2，给第2,3...N个点找匹配点。

复杂度为$O(N^3)$

```cpp
#include <bits/stdc++.h>
#define sqr(x) (x)*(x)
using namespace std;

const int MAX = 107;

int N,mat[MAX],use1[MAX],use2[MAX];
double X0[MAX],Y0[MAX],X1[MAX],Y1[MAX],lx[MAX],ly[MAX],d[MAX][MAX];

int DFS(int x)
{
	use1[x] = 1;
	for (int y = 1; y <= N; y++)
	{
		if (!use2[y] && fabs(lx[x]+ly[y]-d[x][y])<1e-9)
		{
			use2[y] = 1;
			if (!mat[y] || DFS(mat[y]))
				return mat[y] = x, 1;
		}
	}return 0;
}

int main()
{
	while (scanf("%d", &N) != EOF)
	{
		for (int i = 1; i <= N; i++)
			scanf("%lf %lf", X0 + i, Y0 + i);
		for (int i = 1; i <= N; i++)
			scanf("%lf %lf", X1 + i, Y1 + i);
		for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			d[j][i] = -sqrt(sqr(X0[i]-X1[j]) + sqr(Y0[i]-Y1[j]));
			
		memset(mat, 0, sizeof mat);
		memset(lx, 0, sizeof lx);
		memset(ly, 0, sizeof ly);
		for (int p = 1; p <= N; p++)
			while (1)
			{
				memset(use1, 0, sizeof use2);
				memset(use2, 0, sizeof use2);
				if (DFS(p)) break;
				
				double dd = 1e10;
				for (int i = 1; i <= N; i++) if (use1[i])
				for (int j = 1; j <= N; j++) if (!use2[j])
					dd = min(dd, lx[i]+ly[j]-d[i][j]);
				for (int i = 1; i <= N; i++)
				{
					if (use1[i]) lx[i] -= dd;
					if (use2[i]) ly[i] += dd;
				}
			}
		for (int i = 1; i <= N; i++)
			printf("%d\n", mat[i]);
	}
}
```

---

## 作者：DengDuck (赞：2)

不需要任何高级算法（心虚）。

考虑两个线段相交，我们交换一下端点，那么距离肯定会变小。

我们从而想到，如果我们保证了匹配之后两点之间距离最小，那么线段就应该是不相交的（否则两点距离之和可以更小）。

因此我们直接跑 $n$ 轮排序，每轮都找所有的 $i,j(i<j)$ 看看能不能更优就行了。

至于正确性可以考虑一个点换人最多换 $n$ 次。

时间复杂度为 $\mathcal O(n^3)$。

注意多测。多测不多测，亲人两行泪。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define X first
#define Y second
using namespace std;
const int N=30005;
int n,P[N];
pLL A[N],B[N];
inline LF Dis(pLL A,pLL B){return sqrtl((A.X-B.X)*(A.X-B.X)+(A.Y-B.Y)*(A.Y-B.Y));}
int main()
{
	while(~scanf("%d",&n))
	{
		for(int i=1;i<=n;i++)P[i]=i;
		for(int i=1;i<=n;i++)scanf("%lld%lld",&A[i].X,&A[i].Y);
		for(int i=1;i<=n;i++)scanf("%lld%lld",&B[i].X,&B[i].Y);
		for(int T=1;T<=n;T++)
		{
			int Flg=0;
			for(int i=1;i<=n;i++)
				for(int j=1;j<i;j++)
				{
					if(Dis(A[i],B[P[i]])+Dis(A[j],B[P[j]])>Dis(A[i],B[P[j]])+Dis(A[j],B[P[i]]))swap(P[i],P[j]),Flg=1;
				}
			if(!Flg)break;
		}
		for(int i=1;i<=n;i++)printf("%d\n",P[i]);		
		puts("");
	}
}
```

---

## 作者：Martian148 (赞：1)

# Link
[UVA1411 Ants](https://www.luogu.com.cn/problem/UVA1411)

# Solve

题目要求所有线段都不相交，等价于让每条线段的长度之和最小。

如果第$i_1$个白点连第$j_1$个黑点，第$i_2$个白点连接第$j_2$个黑点，并且线段$(i_1,j_1)$和$(i_2,j_2)$相交，那么交换一下，让$i_1$连$j_2$，让$j_1$连$i_2$，这样就不会交叉，并且有三角形两边和大于第三边可知，两条线段的长度和一定变小。

所以就可以把$N$个白点看作左部点，$N$个端点看作右部端点，让第$i$个白点和第$j$个黑点连边，边权$w(i,j)$就是他们在平面上的距离

用$KM$算法求二分图带权最小匹配时，我们把所有边权$w(i,j)$取为相反数，然后转化为求二分图带权最大匹配，最后把答案$-ans$作为答案即可。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=105,INF=1<<30;
int N,match[maxn];
bool va[maxn],vb[maxn];
double X_w[maxn],la[maxn],lb[maxn],Y_w[maxn],X_b[maxn],Y_b[maxn],w[maxn][maxn],delta,upd[maxn],ans;
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch<='9'&&ch>='0')ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
bool DFS(int x){
	va[x]=1;
	for(int y=1;y<=N;y++)
		if(!vb[y]){
			if(abs(la[x]+lb[y]-w[x][y])<1e-7){
				vb[y]=1;
				if(!match[y]||DFS(match[y])){
					match[y]=x;
					return true;
				}
			}
			else upd[y]=min(upd[y],la[x]+lb[y]-w[x][y]); 
		}
	return false;
}

void KM(){
	memset(match,0,sizeof match);
	for(int i=1;i<=N;i++){
		la[i]=-INF;
		lb[i]=0;
		for(int j=1;j<=N;j++)la[i]=max(la[i],w[i][j]);
	}
	for(int i=1;i<=N;i++)
		while(true){
			memset(va,0,sizeof va);
			memset(vb,0,sizeof vb);
			for(int j=1;j<=N;j++)upd[j]=INF;
			if(DFS(i))break;delta=INF;
			for(int j=1;j<=N;j++)
				if(!vb[j])delta=min(delta,upd[j]);
			for(int j=1;j<=N;j++){
				if(va[j]) la[j]-=delta;
				if(vb[j]) lb[j]+=delta;
			}
		}
}
int main(){
	freopen("UVA1411.in","r",stdin);
	freopen("UVA1411.out","w",stdout);
	while(scanf("%d",&N)!=EOF){
		for(int i=1;i<=N;i++)
			scanf("%lf%lf",&X_w[i],&Y_w[i]);
		for(int i=1;i<=N;i++)
			scanf("%lf%lf",&X_b[i],&Y_b[i]);
		for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
			w[j][i]=-sqrt((X_w[i]-X_b[j])*(X_w[i]-X_b[j])+(Y_w[i]-Y_b[j])*(Y_w[i]-Y_b[j]));
		KM();
		for(int i=1;i<=N;i++)printf("%d\n",match[i]);
	}
	return 0;
} 
```

---

## 作者：Mirasycle (赞：0)

本题来自刘汝佳紫书中的巨人与鬼。一道巧妙的几何相关构造题。


------------

看题解区有一种费用流的做法很巧妙，不过书上给的是分治法。

对所有点的纵坐标进行排序，取纵坐标最小的点作为原点，这样就可以保证其他点落在一二象限了。然后再进行极角排序算一下相对位置。

因为要求所有连线不相交，故可以考虑以两点为分界，使得分界线左边刚好两两匹配，右边两两匹配。这样就可以保证左右的线不会跨过分界线了。注意选取分界线的时候要保证分界线左右两边各自的黑白点数量相同。

暴力枚举分界线，然后两侧递归求解即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=210;
struct node{
    int x,y,col,id;
    bool operator < (const node &rhs) const { return y<rhs.y; }
	node operator - (const node &rhs) const { return (node){x-rhs.x,y-rhs.y,col,id}; }
}c[maxn];
int ans[maxn],n;
bool cmp(node a,node b){ return atan2(a.x,a.y)>=atan2(b.x,b.y); }
void solve(int l,int r){
    if(l>=r) return ;
    sort(c+l,c+r+1);
    for(int i=l+1;i<=r;i++) c[i]=c[i]-c[l];
    sort(c+l+1,c+r+1,cmp); int cnt=0;
    for(int i=l+1;i<=r;i++){
        if(cnt==0&&(c[l].col^c[i].col)){
            if(c[l].col) ans[c[i].id]=c[l].id;
			else ans[c[l].id]=c[i].id;
            solve(l+1,i-1); solve(i+1,r);
            return ;
        }
        cnt+=(c[i].col?-1:1);
    }
}
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    while(cin>>n){
        for(int i=1;i<=2*n;i++){
        	cin>>c[i].x>>c[i].y;
    		c[i].col=((i-1)/n)?1:0; c[i].id=(i-1)%n+1;
		}
        solve(1,2*n);
        for(int i=1;i<=n;i++) cout<<ans[i]<<"\n";
        cout<<endl;
	}
    return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

考虑若有 $A \to C,B \to D$，且两线段相交；那么改为 $A \to B,C \to D$ 之后就不交了，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/o4c0m2m2.png)

因为有三角形两边之和大于第三边，则将红边调整为蓝边之后距离总和会变小。

那么当距离总和最小时，肯定满足任意两条线段不交。

考虑直接建完全图，对于边 $i \to j$，其边权为 $\sqrt{(Ax_i-Ax_j)^2 + (By_i - By_j)^2}$；现在要求出二分图最小权完美匹配，将边权取负，跑 KM 即可。

时间复杂度为 $O(N^3)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
using namespace std;
typedef double db;
const int N=105,INF=1e9;
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(int x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Point{
	db x,y;
}a[N],b[N];
int n;
int fa[N],ans[N],A[N];
db lx[N],ly[N],s[N];
db W[N][N];
bool f[N];
db dis(int x,int y){
	return sqrt((a[x].x-b[y].x)*(a[x].x-b[y].x)+(a[x].y-b[y].y)*(a[x].y-b[y].y));
}
void bfs(int h){
	db t;
	int x=0,u=0,id=0;
	A[x]=h;
	while(A[x]){
		f[x]=1;
		u=A[x];
		t=INF;
		for(int v=1;v<=n;v++){
			if(f[v])
			  continue;
			if(s[v]>lx[u]+ly[v]-W[u][v]){
				s[v]=lx[u]+ly[v]-W[u][v];
				fa[v]=x;
			}
			if(s[v]<t){
				t=s[v];
				id=v;
			}
		}
		for(int i=0;i<=n;i++){
			if(f[i]){
				lx[A[i]]-=t;
				ly[i]+=t;
			}
			else
			  s[i]-=t;
		}
		x=id;
	}
	while(x){
		A[x]=A[fa[x]];
		x=fa[x];
	}
}
inline void KM(){
	full(lx+1,lx+n+1,0);
	full(ly+1,ly+n+1,0);
	full(A+1,A+n+1,0);
	for(int i=1;i<=n;i++){
		full(fa+1,fa+n+1,0);
		full(f+1,f+n+1,0);
		full(s+1,s+n+1,INF);
		bfs(i);
	}
	for(int i=1;i<=n;i++)
	  ans[A[i]]=i;
}
void solve(){
	for(int i=1;i<=n;i++){
		a[i].x=read();
		a[i].y=read();
	}
	for(int i=1;i<=n;i++){
		b[i].x=read();
		b[i].y=read();
	}
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=n;j++)
	    W[i][j]=-dis(i,j);
	KM();
	for(int i=1;i<=n;i++){
		write(ans[i]);
		putchar('\n');
	}
}
int main(){
	while(~scanf("%lld",&n))
	  solve();
	return 0;
}
```

---

## 作者：Yuki_Ever (赞：0)

 _部分内容参考自李煜东《算法竞赛进阶指南》_ 




#### 前置知识：匈牙利算法（增广路算法）



------------
#  KM 算法

首先我们先来看一个问题：

你有一张二分图，每条边都带有一个权值，需要求出该二分图的一组最大匹配，使得匹配边的权值总和最大。

其实这个问题可以用费用流解决，然而题解里似乎没什么详细讲 KM  算法的，这里就讲解一下 KM 算法。

#### 顶点标记值
在二分图中，给第 $i$ 个左部节点一个整数值 $x_i$，第 $j$ 个右部节点一个整数值 $y_j$。同时，满足对于任意 $i$，$j$ ，$x _ {i}+y_{j} \ge w_{i,j}$。（$w_{i,j}$ 为 $i,j$ 之间的边权）（若无边则设为负无穷）。则所有 $x_{i} ,y_{j}$ 称为节点的顶点标记值，简称顶标。

#### 交错树
在增广路算法中，如果从某个左部节点出发寻找匹配失败，那么在遍历过程中，所有访问过的节点构成一棵树。此树根为一个左部节点，树上奇数层边为非匹配边，偶数层边为匹配边。故称之为交错树。


------------

  首先我们找到一个性质：如果在相等的子图中存在完备匹配，那么它的边权值和等于所有顶点标记值之和，又因为顶点标记值的定义，任何一组匹配的边权都不可能大于所有顶标的和，故完备匹配就是此二分图的带权最大匹配。 

------------
于是，我们就可以得到 KM 算法的基本思想，即在满足定义的条件下，对每个节点的顶标进行随意赋值，然后不断扩大相等子图的规模，知道相等子图存在完备匹配。

对于一个相等子图，跑增广路算法求最大匹配。若匹配失败，则形成一棵交错树。

这里就会产生一个问题，不妨假设我们将这棵交错树中所有左部节点顶标减少一个整数值 $d$，访问顺序会有变化吗？

#### 情况 1：左部节点 $i$ 沿着非匹配边访问右部节点  $j$

若i和j均在交错树中，$x _ {i}+y _ {j}$ 不变，从前能访问到，现在 _仍可以_。

反之，$i$ 在树中，$j$ 不在，那么之前没遇到的，现在可能访问了。

#### 情况 2：右部节点 $j$ 沿着匹配边递归方位

则 $x _ {i}+y _ {j}$ 不变，匹配边还是一个相等子图。


------------

由上，我们就在所有 $i$ 在交错树中而 $j$ 不在的点集中，找出    $\min(x_i+y_j-w_{i,j})$，作为 $d$ 的值。然后不断重复以上过程，直到每一个左部点都匹配成功。时间复杂度 _$O(m \times n^2)$_。



------------
考虑 _优化_ ,记录数组 $upd[j]$ 表示每个右部点 $j$ 对应的最小 $d$，当一个点无法在当前的相等子图中找到匹配时，更新顶标，直接从 _最小边_ 开始跑 dfs，还需要一个 $last$ 数组表示每一个右部点 $j$ 在交错树中的一个右部点，沿着 $last$ 倒退找增广路。（基于每次更新顶标后，原来相等子图中的边并不会消失，故无需遍历已经遍历过的交错树。）

于是时间复杂度降到 _$O(n^3)$_ 了！



------------
#  _solve_  

 _题目要求最后所有线段都不相交，等价于让每条线段的长度之和最小_。试想，若第 $i_{1}$ 个白点连第 $j_{1}$ 个黑点，第 $i_{2}$ 个白点连第 $j_{2}$ 个黑点，并且 $(i_{1},j_{1})$ 与 $(i_{2},j_{2})$ 相交，那么就交换一下，让 $i_{1}$ 连 $j_{2}$，然后 $i_{2}$ 连 $j_{1}$，这样就不会交叉，并且由三角形性质可知，两条线段的长度之和变小。

接下来就简单了，

把 N 个白点看作 _左部点_，

把 N 个黑点看作 _右部点_，

让每个 $i$，$j$ 之间连边，$w_{i,j}$ 等于它们的距离。

是不是情况明朗的多了？_找二分图最小匹配即可_！

怎么找最 _小_ 呢？把所有 $w_{i,j}$ 先取相反数，找最大值就行了！


（代码很多 dalao 都写了，这里思路已经很清楚了，就不放了吧。）

~~其实就是不敢放。~~



------------
# 后记

切记： KM 算法只能在满足

 _带权最大匹配一定是完备匹配_ 

的情况使用！

所以还是推荐 _费用流_。

~~其实就是算法思路不难，但代码 bug 多。~~

 模板题：[P6577](https://www.luogu.com.cn/problem/P6577)。



------------

$2023.11.6$    

 _$Yuki.ever$_ 


---

## 作者：OldDriverTree (赞：0)

前置芝士：[二分图最大权完美匹配](https://www.luogu.com.cn/problem/P6577)。

___

# Solution

考虑一种情况：白点 $a$ 连接黑点 $x$，白点 $b$ 连接黑点 $y$，且这两条线段相交。

如果改成 $a$ 连接 $y$，$b$ 连接 $x$，这两条线段就不会相交，根据三角形的性质：两边之和大于第三边，还可以知道交换后长度和一定会变小。

那么长度和最小的连接方案一定满足要求。

注意要求长度和最小，把边权变相反数后跑 KM 即可。

# Code

```c++
#include<bits/stdc++.h>
#define sq(x) (x)*(x)
using namespace std;
typedef pair<int,int> P;
const int N=101;
const double inf=1e16;
double ex[N],ey[N],upd[N],g[N][N];
int n,m,last[N],match[N]; bool vis[N];
P a[N],b[N]; 

int read() {
    int x=0; bool f=true; char ch=0;
	while (!isdigit(ch) ) f&=(ch^'-'),ch=getchar();
    while (isdigit(ch) ) x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
    return f?x:-x;
}
void KM()
{
	memset(match,0,sizeof match);
	memset(ex,0,sizeof ex);
	memset(ey,0,sizeof ey);
	for (int u=1;u<=n;u++)
	{
		memset(vis,0,sizeof vis);
		memset(last,0,sizeof last);
		memset(upd,127,sizeof upd);
		int v=0,x,t; match[0]=u; 
		double val;
		
		while (match[v])
		{
			x=match[v],vis[v]=true,val=inf;
			for (int y=1;y<=n;y++) if (!vis[y])
			{
				if (upd[y]>ex[x]+ey[y]-g[x][y])
				upd[y]=ex[x]+ey[y]-g[x][y],last[y]=v;
				if (upd[y]<val) val=upd[y],t=y;
			}
			for (int y=0;y<=n;y++)
				if (vis[y]) ex[match[y] ]-=val,ey[y]+=val;
				else upd[y]-=val;
			v=t;
		}
		while (v) match[v]=match[last[v] ],v=last[v];
	}
}
int main()
{
	while (cin>>n)
	{
		for (int i=1;i<=n;i++) b[i]={read(),read()};
		for (int i=1;i<=n;i++) a[i]={read(),read()};
		
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				g[i][j]=-sqrt(sq(a[i].first-b[j].first)+sq(a[i].second-b[j].second) );
		KM();
		for (int i=1;i<=n;i++) printf("%d\n",match[i]);
	}
	return 0;
}
```

---

## 作者：Trimsteanima (赞：0)

# $\mathtt{UVA 1411}$ $\mathtt{Ants}$

## $\mathcal{Description}$

给定一些黑点白点，要求一个黑点连接一个白点，并且所有线段都不相交。

## $\mathcal{Solution}$

首先通过画图可以发现，要使所有线段都不相交可以使距离总和最小。所以题意就转化成为使距离总和最小的连接方式，自然联想到$KM$。我们可以先预处理出每一对白点和黑点之间的距离，因为要求的是最小连接方式，所以可以把距离取反来求最大值，限制条件为$g[i] + b[i] = a[i][j]$，$a[i][j]$是取反后的距离，$g[i]$是黑点的期望值，$b[i]$是白点的期望值，复杂度为$O(n^3)$。

## $\mathcal{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 110, INF = 1 << 30, Eps = 1e-9;
bool tfg[N], tfb[N];
int match[N], n,cnt ;
double a1[N], b1[N], a2[N], b2[N], a[N][N], b[N], g[N];
inline int read() {
	int x = 0, k = 1; char c = getchar();
	for (; c < 48 || c > 57; c = getchar()) k ^= (c == '-');
	for (; c >= 48 && c <= 57; c = getchar()) x = x * 10 + (c ^ 48);
	return k ? x : -x;
}
bool pd(int x) {
	tfg[x] = true;
	for (int i = 1; i <= n; i++)
		if (fabs(g[x] + b[i] - a[x][i]) <  Eps && !tfb[i]) {
			tfb[i] = true;
			if (match[i] == -1) {
				match[i] = x;
				return true;
			}
			if (pd(match[i])) {
				match[i] = x;
				return true;
			}
		}
	return false;
}
inline void KM() {
	memset(match, -1, sizeof(match));
	memset(b, 0.0, sizeof(b));
	for (int i = 1; i <= n; i++) {
		g[i] = std::max(0.0, a[i][1]);
		for (int j = 2; j <= n; j++)
			g[i] = std::max(g[i], a[i][j]);
	}
	for (int i = 1; i <= n; i++) {
		while (true) {
			//printf("%d KM\n",i);
			memset(tfb, false, sizeof(tfb));
			memset(tfg, false, sizeof(tfg));    
			if (pd(i))
				break;
			double d = INF;
			for (int j = 1; j <= n; j++)
				if (tfg[j])
					for (int k = 1; k <= n; k++)
						if (!tfb[k])
							d = std::min(d, g[j] + b[k] - a[j][k]);
			// if (cnt<=5) printf("%d %.2lf YES\n",i,d);
			for (int j = 1; j <= n; j++) {
				if (tfg[j])
					g[j] -= d;
				if (tfb[j])
					b[j] += d;
			}
			// if (i==1 && cnt<=5) for (int j=1; j<=n; j++) printf("%d %.2lf %.2lf\n",j,g[j],b[j]);
			// cnt++;
		}
	}
}
inline double dist(double x, double y, double xx, double yy) {
	return sqrt((x - xx) * (x - xx) + (y - yy) * (y - yy));
}
int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; i++)
			scanf("%lf%lf", &a1[i], &b1[i]);
		for (int i = 1; i <= n; i++) 
			scanf("%lf%lf", &a2[i], &b2[i]);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				a[j][i] = -dist(a1[i], b1[i], a2[j], b2[j]);
		KM();
		for (int i = 1; i <= n; i++)
			printf("%d\n", match[i]);
	}
	return 0;
}

```

---

## 作者：yzhang (赞：0)

### [更好的阅读](https://www.cnblogs.com/yzhang-rp-inf/p/10087461.html)

### [原题传送门](https://www.luogu.org/problemnew/show/UVA1411)

### 博客里对[二分图匹配](https://www.cnblogs.com/yzhang-rp-inf/p/10079578.html)的详细介绍


这道题是带权二分图匹配

用的是KM算法

我们要知道一个定理：要使线段没有相交，要使距离总和最小

我们先把任意一对白点、黑点的距离算一下

然后运用KM算法

因为要最小权值，所以需要把权值取反来求最大。

```cpp
#include <bits/stdc++.h>
#define N 105
using namespace std;
inline void write(register int x)
{
    if(!x)putchar('0');if(x<0)x=-x,putchar('-');
    static int sta[25];int tot=0;
    while(x)sta[tot++]=x%10,x/=10;
    while(tot)putchar(sta[--tot]+48);
}
inline double Max(register double x,register double y)
{
	return x>y?x:y;
}
inline double Min(register double x,register double y)
{
	return x<y?x:y;
}
int n;
double X1[N],Y1[N],X2[N],Y2[N];
double dis[N][N];
double lx[N],ly[N];
int link[N],s[N],t[N];
inline bool dfs(register int x)
{
	s[x]=1;
	for(register int i=1;i<=n;++i)
		if(fabs(lx[x]+ly[i]-dis[x][i])<1e-9&&!t[i])
		{
			t[i]=1;
			if(!link[i]||dfs(link[i]))
			{
				link[i]=x;
				return true;
			}
		}
	return false;
}
inline void update()
{
	double a=23333333;
	for(register int i=1;i<=n;++i)
		if(s[i])
			for(register int j=1;j<=n;++j)
				if(!t[j])
					a=Min(a,lx[i]+ly[j]-dis[i][j]);
	for(register int i=1;i<=n;++i)
	{
		if(s[i])
			lx[i]-=a;
		if(t[i])
			ly[i]+=a;
	}
}
inline void KM()
{
	for(register int i=1;i<=n;++i)
	{
		link[i]=lx[i]=ly[i]=0;
		for(register int j=1;j<=n;++j)
			lx[i]=Max(lx[i],dis[i][j]);
	}
	for(register int i=1;i<=n;++i)
		while(19260817)
		{
			for(register int j=1;j<=n;++j)
				s[j]=t[j]=0;
			if(dfs(i))
				break;
			else
				update();
		}
}
inline double getdis(register int x,register int y)
{
	return sqrt(pow(X1[x]-X2[y],2)+pow(Y1[x]-Y2[y],2));
}
int main()
{
	while(scanf("%d",&n)!=EOF)
	{
		for(register int i=1;i<=n;++i)
			scanf("%lf %lf",&X1[i],&Y1[i]);
		for(register int i=1;i<=n;++i)
			scanf("%lf %lf",&X2[i],&Y2[i]);
		for(register int i=1;i<=n;++i)
			for(register int j=1;j<=n;++j)
				dis[j][i]=-getdis(i,j);
		KM();
		for(register int i=1;i<=n;++i)
			write(link[i]),puts("");
	}
	return 0;
}
```

---

