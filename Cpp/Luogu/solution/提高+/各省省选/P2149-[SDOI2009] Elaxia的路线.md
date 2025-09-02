# [SDOI2009] Elaxia的路线

## 题目描述

最近，Elaxia 和 w** 的关系特别好，他们很想整天在一起，但是大学的学习太紧张了，他们必须合理地安排两个人在一起的时间。

Elaxia 和 w** 每天都要奔波于宿舍和实验室之间，他们 希望在节约时间的前提下，一起走的时间尽可能的长。

现在已知的是 Elaxia 和 w** 所在的宿舍和实验室的编号以及学校的地图：  
地图上有 $n$ 个路口，$m$ 条路，经过每条路都需要一定的时间。 具体地说，就是要求无向图中，两对点间最短路的最长公共路径。


## 说明/提示

【数据范围】    
对于 $30\%$ 的数据，$1\le n \le 100$；   
对于 $60\%$ 的数据，$1\le n \le 1000$；   
对于 $100\%$ 的数据，$1\le n \le 1500$，$1 \leq m \leq 3 \times 10^5$，$1\le w \le 10^4$，输入数据保证没有重边和自环。


## 样例 #1

### 输入

```
9 10
1 6 7 8
1 2 1
2 5 2
2 3 3
3 4 2
3 9 5
4 5 3
4 6 4
4 7 2
5 8 1
7 9 1```

### 输出

```
3```

# 题解

## 作者：caeious (赞：95)

// 感谢 djq 完善本算法

需要一定思维的一道初等图论题。。。

可以证明，所求最长公共路径是一条链，不然由于最短路的一部分还是最短路，而无向图中 $S$ 到 $T$ 与 $T$ 到 $S$ 的最短路相等，可以像下图一样优化：  
![](https://cdn.luogu.com.cn/upload/image_hosting/jpfy966o.png)

那么我们可以找出 Elaxia 去实验室的最短路经过的**有向边**组成的 DAG，所求路径一定是该 DAG 上的一条链。样例建成的如下图所示：  
![](https://cdn.luogu.com.cn/upload/image_hosting/wbpb0hzk.png)

同时，所求链也应在 W-- 的最短路 DAG（姑且称为 DAGw）上。如下图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/pi75104w.png)

题目说是并行和相遇都算公共，但所求链显然不会又包括并行，又包含相遇，否则因为 DAGw 不可能同时有 $u \to v$ 和 $v \to u$ 边，它在 DAGw 上不是链了。（**讨论里的第一组hack数据卡了这一点。**）我们可以求一下**只保留**在两 DAG 中同向出现的边时的最长链，和**只保留**在两 DAG 中反向出现的边时的最长链。（**第二组hack卡了“只保留”三个字**）。

---

参考实现

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<utility>
#include<iostream>
#include<queue>
#include<string>
#define inf 0x3f3f3f3f
#define mp make_pair
#define maxn 1505
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
struct edge{
    int to,cst;
}el[maxn*maxn],el2[maxn*maxn];
int E,n,m,head[maxn],nxt[maxn*maxn],x1,y1,x2,y2,d[5][maxn];
int E2,head2[maxn],nxt2[maxn*maxn],len[maxn],deg[maxn],que[maxn],he,ta;
//变量名带2的都是新建的图的信息。
bool vis[maxn];
inline int getint(){
    char c;
    for(c=getchar();c<'0' || c>'9';c=getchar());
    int res = c - '0';
    for(c=getchar();c>='0'&&c<='9';c=getchar()) res = res * 10 + (c - '0');
    return res;
}
inline void addedge2(int u,int v,int w){
    E2++;
    el2[E2] = (edge){v,w};
    nxt2[E2] = head2[u];
    head2[u] = E2;
    deg[v]++;
}
inline void addedge(int u,int v,int w){
    E++;
    el[E] = (edge){v,w};
    nxt[E] = head[u];
    head[u] = E;
}
inline void dijkstra(int id,int S){
    memset(d[id],0x3f,sizeof(d[id]));
    memset(vis,0,sizeof(vis));
    d[id][S] = 0;
    for(int i=1;i<=n;i++){
        int md = inf,u = -1;
        for(int j=1;j<=n;j++){
            if(!vis[j] && md > d[id][j]){
                md = d[id][j];
                u = j;
            }
        }
        if(u == -1) break;
        vis[u] = true;
        for(int j=head[u];j!=-1;j=nxt[j]){
            d[id][el[j].to] = min(d[id][el[j].to],d[id][u] + el[j].cst);
        }
    }
}
inline void quepush(int x){
    que[ta] = x;
    ta++;
}
inline int quepop(){
    int ret = que[he];
    he++;
    return ret;
}
inline void topo(){
        memset(vis,0,sizeof(vis));
    he = ta = 1;
    for(int i=1;i<=n;i++) if(!deg[i]) quepush(i);
    while(he != ta){
        int u = quepop();
        for(int i=head2[u];i!=-1;i=nxt2[i]){
            deg[el2[i].to]--;
            len[el2[i].to] = max(len[el2[i].to],len[u] + el2[i].cst);
            if(deg[el2[i].to] == 0) quepush(el2[i].to);
        }
    }
}
int main(){
    memset(head,-1,sizeof(head));
    memset(head2,-1,sizeof(head2));
    n = getint();
    m = getint();
    x1=getint(),y1=getint(),x2=getint(),y2=getint();
    for(int i=1;i<=m;i++){
        int u,v,w;
        u=getint(),v=getint(),w=getint();
        addedge(u,v,w);
        addedge(v,u,w);
    }
    dijkstra(1,x1);
    dijkstra(2,y1);
    dijkstra(3,x2);
    dijkstra(4,y2);
    for(int i=1;i<=n;i++){
        for(int j=head[i];j!=-1;j=nxt[j]){
            if(d[1][i] + el[j].cst + d[2][el[j].to] == d[1][y1]){
                if(d[3][i] + el[j].cst + d[4][el[j].to] == d[3][y2])
                addedge2(i,el[j].to,el[j].cst);
            }
        }
    }
    topo();
    int ans = 0;
    for(int i=1;i<=n;i++) ans = max(ans,len[i]);
    memset(head2,-1,sizeof(head2));
    E2 = 0;
    memset(deg,0,sizeof(deg));
    memset(len,0,sizeof(len));
    for(int i=1;i<=n;i++){
        for(int j=head[i];j!=-1;j=nxt[j]){
            if(d[1][i] + el[j].cst + d[2][el[j].to] == d[1][y1]){
                if(d[4][i] + el[j].cst + d[3][el[j].to] == d[3][y2])
                addedge2(i,el[j].to,el[j].cst);
            }
        }
    }
    topo();
    for(int i=1;i<=n;i++) ans = max(ans,len[i]);
    printf("%d\n",ans);
  return 0;
}
```

附上一组蒟蒻的简单数据：

input：

```
4 4
1 4 2 3
1 2 10
1 3 1
4 2 9
4 3 2
```

Output：

```
2
```

---

## 作者：BJpers2 (赞：56)

做了一下午，好不容易AC了这道紫题。

实际上下面大佬讲的思路已经很清晰了，发这篇题解主要是提供一些更简洁的写法。

其一，没有必要建两张图，只要在原图的基础上标记就行了。

其二，拓扑没必要跑两遍，用两个数组分别记录顺走和反走所能得到的最长公共部分即可。

其三，队列用数组写反而更舒服（个人喜好）

主要思路就是4个最短路筛出有用边，然后起点1向终点1拓扑

代码有些压行，非喜勿喷。
```cpp
#include<iostream>
#include<cstdio>
#include<set>
#define N 5000
#define M 2500250
#define INF 1000010000
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define REP(u) for(int i=hd[u],v=e[i].v,w=e[i].w;i;i=e[i].n,v=e[i].v,w=e[i].w)
using namespace std;
struct edge{int n,v,w;}e[M];
int n,m,u,v,w,hd[N],fl,dis[4][N],s1,t1,s2,t2,ans,f[N],g[N],ok[M],in[N],l,r,q[N];
set< pair<int,int> >h;
void add(int u,int v,int w){e[++fl].v=v,e[fl].w=w,e[fl].n=hd[u],hd[u]=fl;}
void dijkstra(int s,int k){
	FOR(i,1,n) dis[k][i]=INF;
	dis[k][s]=0,h.insert(make_pair(0,s));
	while(!h.empty()){
		u=h.begin()->second,h.erase(*h.begin());
		REP(u)if(dis[k][u]+w<dis[k][v]){
			if(dis[k][v]<=INF)  h.erase(make_pair(dis[k][v],v));
			dis[k][v]=dis[k][u]+w,h.insert(make_pair(dis[k][v],v));
		}
	}
}
int main(){
	scanf("%d%d%d%d%d%d",&n,&m,&s1,&t1,&s2,&t2);
	FOR(i,1,m) scanf("%d%d%d",&u,&v,&w),add(u,v,w),add(v,u,w);
	dijkstra(s1,0),dijkstra(t1,1);
	dijkstra(s2,2),dijkstra(t2,3);
	FOR(u,1,n)REP(u)
		if(dis[0][u]+w+dis[1][v]==dis[0][t1]) ok[i]=1,in[v]++;
	l=r=1,q[r++]=s1;
	while(l<r){
		int u=q[l++];ans=max(ans,max(f[u],g[u]));
		REP(u)if(ok[i]){
			in[v]--;
			if(dis[2][u]+w+dis[3][v]==dis[2][t2]) f[v]=max(f[v],f[u]+w);//并行走 
			if(dis[3][u]+w+dis[2][v]==dis[2][t2]) g[v]=max(g[v],g[u]+w);//反向走 
			if(!in[v]) q[r++]=v;
		}
	}printf("%d",ans);
}
```

---

## 作者：天泽龟 (赞：41)

#### 看着大佬纠结于题目实现的各种细节，本蒟蒻还在想这题应该怎么实现...

有些知识没有做过类似的题目，你就是真的不知道，顶着头皮硬磕真不一定能在一定时间弄出来。我会将整个题目的思路详细地分析一波，把一些关键的操作举出来。_(:з」∠)_

---

整个题描述巨短，说白了就是**要求无向图中，两对点间最短路的最长公共路径。**

首先连初学图论的萌新都知道，一个图中的最短路径不止一条。

- ### 所以，“要想找出所有在最短路径上的边”便成为首要的问题。

这个其实想一想还是可以搞出来的，假设两个节点分别为$u,v$且u靠近s，则一条边在最短路径上，一定满足起始$s,t$点分别到$u,v$的距离加上这条边权，等于最小路径长度。即$$ds[u]+w+dt[v]=ds[t]$
其中$ds[i]$数组和$dt[i]$数组分别为$s,t$到各个点的路径，这个不难理解~~（但就是想不到）~~。

于是乎我们可以先用4个$SPFA$（当然8012年了还是打$dij$更好）算出4个顶点到各个点的最短路，枚举每一条边即可。

- ### 但是求出来所有边又要怎么处理呢？？

既然我们要求最短路的最长公共路径，那这条路径由以上求出的边组成的，跟其他边半毛钱关系没有。

为了方便处理，我们可以把这些边重新建个图，或者通过打标记的方法将这些边独立出来，这样在接下来的操作里就会方便许多。

有些细节放在代码里讲：
```
    for (int i=1;i<=n;i++)
    for (int j=fir[i];j;j=e[j].next) //枚举每条边
    {
        int v=e[j].v,w=e[j].w;
        if (d1[i]+w+d3[v]==d1[y1])  //判断第一对
        {
       //判断第二对的时候由于枚举的是单向边，所以作双向处理。 
        	if (d2[i]+w+d4[v]==d2[y2]) add2(i,v,w);
        	if (d2[v]+w+d4[i]==d2[y2]) add2(v,i,w);
		}
	}
```

- ## 建完图了，怎么求最长路径呢？

既然我们建了一个是一个有向图，不具有后效性，所以可以跑有向图DP了！

设$dp[i]$是第i节点的最长路径，易得到式子$$dp[i]=dp[u]+w$其中u是i的前驱节点，对于入度为0的点答案为0，为了方便理解我采用**记忆化**的方法求解。

由于所有边可能不会全连通，所以枚举每一个没有标记的点均跑一边，最后求出最大的$dp[i]$即是答案。

```
int dfs(int u)
{
    if (dp[u]) return dp[u];
    for (int i=fir2[u];i;i=e2[i].next) 
    {
        
        int v=e2[i].v,w=e2[i].w;
        dp[u]=max(dp[u],dfs(v)+w);  //核心，深搜算u前驱的答案。
    }
    return dp[u];
}
```

---

于是三个重要操作就没了，其余的细节其他题解也有就不多赘述，具体可看丑陋的代码：
```
// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include <iostream>
#include <cstring>
#include <queue>
#include <climits>
using namespace std;
struct ed{
    int v,next,w;
}e[5000000],e2[5000000];
int st,d1[50000],d2[5000],d3[5000],d4[5000];
int fir[10000],fir1[10000],fir2[20000],dp[10000],maxx;
int n,m,u,v,l,x1,x2,y1,y2,rd[10000];
bool vis[40000]; queue<int> q;

void add(int u,int v,int l)
{
    e[++st].v=v; e[st].next=fir[u]; e[st].w=l; fir[u]=st;
}

void add2(int u,int v,int l)
{
    e2[++st].v=v; e2[st].next=fir2[u];  e2[st].w=l; fir2[u]=st; rd[u]=rd[v]=1;
}

void spfa(int b,int *d)
{
    for (int i=1;i<=n;i++) d[i]=INT_MAX/2; d[b]=0;
    while (!q.empty()) q.pop(); q.push(b);
    memset(vis,0,sizeof(vis)); vis[b]=1;
    while (!q.empty())
    {
        int k=q.front(); q.pop(); vis[k]=0;
        for (int i=fir[k];i;i=e[i].next)
        {
            int v=e[i].v,w=e[i].w; 
            if (d[v]>d[k]+w) {
                d[v]=d[k]+w; if (!vis[v]) vis[v]=1,q.push(v);
            }
        }
    }
}

int dfs(int u)
{
    if (dp[u]) return dp[u];
    for (int i=fir2[u];i;i=e2[i].next) 
    {
        
        int v=e2[i].v,w=e2[i].w;
        dp[u]=max(dp[u],dfs(v)+w);	
    }
    return dp[u];
}

int main()
{
    cin>>n>>m;
    cin>>x1>>y1>>x2>>y2;
    for (int i=1;i<=m;i++) cin>>u>>v>>l,add(u,v,l),add(v,u,l);
    spfa(x1,d1); spfa(x2,d2); spfa(y1,d3); spfa(y2,d4); st=0;//求4个顶点到各个点的最短路 
//~~~~~~~~ 
    for (int i=1;i<=n;i++)
    for (int j=fir[i];j;j=e[j].next)
    {
        int v=e[j].v,w=e[j].w;
        if (d1[i]+w+d3[v]==d1[y1])
        {
        	if (d2[i]+w+d4[v]==d2[y2]) add2(i,v,w);
        	if (d2[v]+w+d4[i]==d2[y2]) add2(v,i,w);
		}
		
        //有向图会漏判 
    }
    memset(dp,0,sizeof(dp)); 
    for (int i=1;i<=n;i++) if (rd[i]&&!dp[i]) dfs(i);//枚举每一个边进行记忆化 
    for (int i=1;i<=n;i++) maxx=max(maxx,dp[i]); 
    cout<<maxx<<endl;
}
```

几个hack数据都能过，要是有错请指出_(:з」∠)_

---

## 作者：da_AA (赞：38)

先不要脸的宣传一波[我的博客](https://www.cnblogs.com/wyxwyx/p/sdoi2009ela.html)

# Solution

不知道为啥泥萌要跑4遍最短路，我好像只跑了两遍。

要求最短路径的最长公共部分，我是先跑了一遍从$x_1$到$y_1$的最短路，然后把$x_1$到$y_1$最短路上的边打个标记。再跑一遍$x_2$到$y_2$的最短路，只不过这次的"边权"改为一对数：边的长度和边在第一次最短路中的长度。然后迪杰斯特拉跑的时候堆里先比较最短路长度，短的先出，如果最短路长度一样，在比较和之前重叠的长度，长的先出。

暂时通过了所有讨论中的hack数据。（应该是吧

代码也很好写啊，就是把普通的dij的`dis`换成一个自己写的结构体就行了啊。

# Code 

```C++
#include <cstdio>
#include <cstring>
#include <queue>

typedef long long ll;

const int N = 1510;
const int M = N * (N - 1);

struct state {
    int x, y;
    state(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator>(const state& a) const {
        return x == a.x ? y < a.y : x > a.x;
    }
    state operator+(const state& a) const { return state(x + a.x, y + a.y); }
    bool operator==(const state& a) const { return x == a.x && y == a.y; }
    bool operator<(const state& a) const { return !(*this == a || *this > a); }
} dis[N], w[M];
int vis[N], hd[N], to[M], nxt[M], cnt = 1, n, m, fl[M];

inline void adde(int x, int y, int z) {
    to[++cnt] = y;
    nxt[cnt] = hd[x];
    w[cnt].x = z;
    hd[x] = cnt;
}

struct node {
    int p;
    state d;
    node(int p = 0, state d = state(0, 0)) : p(p), d(d) {}
    bool operator<(const node& x) const { return d > x.d; }
};
std::priority_queue<node> q;
void dij(int s) {
    for (int i = 1; i <= n; ++i) dis[i] = state(0x3f3f3f3f, 0), vis[i] = 0;
    q.push(node(s, dis[s] = state(0, 0)));
    while (!q.empty()) {
        node x = q.top();
        q.pop();
        if (vis[x.p]) continue;
        vis[x.p] = 1;
        for (int i = hd[x.p]; i; i = nxt[i])
            if (!vis[to[i]]) {
                if (dis[to[i]] > x.d + w[i])
                    q.push(node(to[i], dis[to[i]] = x.d + w[i]));
            }
    }
}

void dfs(int x) {
    // printf("%d\n", x);
    for (int i = hd[x]; i; i = nxt[i]) {
        if (dis[to[i]] + w[i] == dis[x]) {
            w[i].y += w[i].x;
            w[i ^ 1].y += w[i].x;
            dfs(to[i]);
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    for (int i = 1, x, y, z; i <= m; ++i) {
        scanf("%d%d%d", &x, &y, &z);
        adde(x, y, z);
        adde(y, x, z);
    }
    dij(x1);
    // printf("%d %d\n", dis[y1].x, dis[y1].y);
    dfs(y1);
    dij(x2);
    printf("%d\n", dis[y2].y);
    return 0;
}
```

---

## 作者：saipubw (赞：26)


先附一张样例：

![样例](https://cdn.luogu.com.cn/upload/pic/59536.png)

思路：$dijkstra$+有向无环图上的动态规划

首先，我们要明确一个问题：

最短路算法的路径形成的图必然是有向无环图，这是因为如果最短路存在，则必然没有负环。因此路径中不可能出现环。

如下图，即为从$1$号点开始跑$dijkstra$算法形成的有向无环图：

![dijkstra最短路的结果](https://cdn.luogu.com.cn/upload/pic/59537.png)

那么，该如何保存这张图呢？我们可以在dijkstra的松弛操作中这么做：
```cpp
if (dis[e.to] >= e.w + dis[now.to])
    {
        if (dis[e.to] > e.w + dis[now.to])
        {
            pre[e.to].clear();
            dis[e.to] = e.w + dis[now.to];
            que.push({e.to, dis[e.to]});
        }
        pre[e.to].push_back({now.to, e.w});
    }
```

每当我们成功松弛一个点，我们就清除这个点之前存在的边。把刚才松弛它的边反向，并将其加入一个新的图pre中。如果不能松弛，但是刚好相等的时候，我们只将这个点加入新的图pre中。这样我们就得到了所有边刚好与上图相反，从多个点汇聚到起点的有向无环图。

但是我们只要从$1$号点到$6$号点上的最短路径。因此这张图上仍然有许多没用的点，如$9$号点，$8$号点，$7$号点。

接下来，我们在这张图上，从终点开始$dfs$，标记遍历到的所有点，没被标记的点把它去掉。这样，图中的所有点和边都位于最短路径上了。

![新的pre图](https://cdn.luogu.com.cn/upload/pic/59538.png)

现在我们成功的把最短路径转换成了一个有向无环图。

拓扑排序可用dfs实现，因此在之前的dfs过程中可顺便进行拓扑排序。

这样，我们只要按拓扑序，从终点开始往起点进行dag上的动态规划即可。

那么问题就只剩下列出状态转移方程了。

![样例的解释](https://cdn.luogu.com.cn/upload/pic/59539.png)

先解释一下样例，如图所示，选择$1-2-3-4-6$，则无公共路径，选择$1-2-5-4-6$，则公共路径长度为$3$，也就是说，$4$和$5$之间的边成为了公共路径。

我们先说明一个显然的结论，最长公共路径一定是一条最短路路径上连续的一段。

还是拿一张图来举例子。

![](https://cdn.luogu.com.cn/upload/pic/59540.png)

假设公共部分可以是不连续的.

图中，$2$号点到$8$号点的最短路径为$2-3-6-8$

而1号点到7号点的最短路径为$1-2-3-4-5-6-8-7$

他们的公共路径为$2-3$和$6-8$

显然的，我们会发现，这种情况不可能成立，因为三号点到六号点的最短路径长度一定是唯一的。所以$3-6$的路径和$3-4-5-6$的路径长度应该相同。这样，1号点到7号点必然存在另外一条最短路径：$1-2-3-6-8-7$，其公共路径为$2-3-6-8$。

因此，由归纳法可证明，所有间断的公共路径一定能被连成连续的一段。

需要说明的是，某一条最短路上，可能有多段公共路径，每段公共路径都是另外一对点的最短路方案中的一种。（而同一种方案的公共路径一定是连续的）

这样，问题转化为：求出最短路径上最长的公共路径连续段。


我们在其中一对点的最短路径图上进行动态规划。设有$n$个点$bi$连向点$a$。每条边的长度为$wi$。最短路径图的起点为$s$，终点为$t$

$dp[a][0]$表示当前点a所在的连续公共路径的长度

$dp[a][1]$表示从t到a的最长公共路径

状态转移方程如下：

如果bi到a这条边在另外一张最短路径图上也存在，则这是一条公共边

$ dp[a][0] = max(dp[b_{i}][0]+wi),i∈[1,n]$

$ dp[a][1] = max(dp[b_{i}][1],dp[a][0]),i∈[1,n]$

否则：


$ dp[a][1] = max(dp[b_{i}][1]),i∈[1,n]$

$ dp[a][0] = 0$   //这条边不是公共边，当前不存在连续段，所以长度为0


最后$dp[s][1]$即为我们需要求的，从$t$到$s$的最短路上的最长公共路径。

最后，总结一下我们的算法：

1.跑两次$djikstra$，建出两张最短路径图

2.从终点开始跑两次基于$dfs$的拓扑排序，并标记上能被遍历到的点。

3.任选一张图，按照拓扑顺序，根据遍历的边在另外一张图上是否存在跑动态规划。
注意，需要把另外一张图正的方向和倒过来的方向各判断一次取最大值（在$2$中未被标记的点不应考虑）

可以看出，$2$和$3$的时间复杂度基本是线性的，因此算法的渐进时间复杂度和$djikstra$相同。

最后，附代码：

```cpp
#include <bits/stdc++.h>
#define maxn 1505
#define INF 0x3f
#define max(a, b) (((a) > (b)) ? (a) : (b))
using std::priority_queue;
using std::vector;
struct Edge
{
    int to, w;
    friend bool operator<(Edge a, Edge b)
    {
        return a.w > b.w;
    }
};
vector<Edge> head[maxn], pre1[maxn], pre2[maxn];
vector<int> poi1, poi2;
priority_queue<Edge> que;
int dis1[maxn], dis2[maxn], dp[maxn][2];
bool ispass1[maxn], ispass2[maxn], tab[maxn][maxn];
void dfs(int pos, bool *ispass, vector<Edge> *pre, vector<int> &poi);
void dijk(int beg, int *dis, vector<Edge> *pre);
int main(void)
{
    int n, m, x1, y1, x2, y2, u, v, l,ans=0;
    scanf("%d%d%d%d%d%d", &n, &m, &x1, &y1, &x2, &y2);
    for (int i = 0; i < m; ++i)
    {
        scanf("%d%d%d", &u, &v, &l);
        head[u].push_back({v, l});
        head[v].push_back({u, l});
    }
    dijk(x1, dis1, pre1),dijk(x2, dis2, pre2);
    dfs(y1, ispass1, pre1, poi1),dfs(y2, ispass2, pre2, poi2);
    for (int i = 1; i <= n; ++i)
        for (auto &e : pre2[i])
            tab[i][e.to]= 1;
    for (int i = poi1.size() - 1; i >= 0; --i)
        for (auto &e : pre1[poi1[i]])
            if (ispass2[poi1[i]] && ispass2[e.to] && tab[poi1[i]][e.to])//这两点需在另外一张图中存在且被标记
            {
                dp[e.to][0] = max(dp[poi1[i]][0] + e.w, dp[e.to][0]);
                dp[e.to][1] = max(max(dp[poi1[i]][1], dp[e.to][0]), dp[e.to][1]);
            }
            else
                dp[e.to][1] = max(dp[poi1[i]][1], dp[e.to][1]);
    ans=max(ans,dp[x1][1]),memset(dp,0,sizeof(dp));
    for (int i = poi1.size() - 1; i >= 0; --i)
        for (auto &e : pre1[poi1[i]])
            if (ispass2[poi1[i]] && ispass2[e.to] && tab[e.to][poi1[i]])//再跑一次，另外一张图的边需要反过来看。
            {
                dp[e.to][0] = max(dp[poi1[i]][0] + e.w, dp[e.to][0]);
                dp[e.to][1] = max(max(dp[poi1[i]][1], dp[e.to][0]), dp[e.to][1]);
            }
            else
                dp[e.to][1] = max(dp[poi1[i]][1], dp[e.to][1]);
    ans=max(ans,dp[x1][1]);
    printf("%d", ans);
    return 0;
}
void dijk(int beg, int *dis, vector<Edge> *pre)
{
    memset(dis, INF, sizeof(dis1));
    dis[beg] = 0;
    que.push({beg, 0});
    Edge now;
    while (!que.empty())
    {
        now = que.top();
        if (now.w == dis[now.to])
            for (auto &e : head[now.to])
                if (dis[e.to] >= e.w + dis[now.to])
                {
                    if (dis[e.to] > e.w + dis[now.to])
                    {
                        pre[e.to].clear();
                        dis[e.to] = e.w + dis[now.to];
                        que.push({e.to, dis[e.to]});
                    }
                    pre[e.to].push_back({now.to, e.w});
                }
        que.pop();
    }
    return;
}
void dfs(int pos, bool *ispass, vector<Edge> *pre, vector<int> &poi)
{
    ispass[pos] = 1;
    for (auto &e : pre[pos])
        if (ispass[e.to] == 0)
            dfs(e.to, ispass, pre, poi);
    poi.push_back(pos);
    return;
}

```







---

## 作者：TsReaper (赞：16)

调得让人心生怨念的好题！

一个比较容易想到的思路是：看看哪些点处于公共最短路上。显然，如果dis(x1,i) + dis(i,y1) == dis(x1,y1) 且 dis(x2,i) + dis(i,y2) == dis(x2,y2)（dis表示两点间最短路），那么点i在公共最短路上。为了求出所需要的dis值，我们需要分别以x1,y1,x2,y2为起点，各跑一遍最短路。接下来枚举一对位于公共最短路上的点i,j，最大的abs( dis(x1,i) - dis(x1,j) )（abs为绝对值）就是答案。

这个思路看起来非常合理，实际得分也很划算。但是，这个思路存在着漏洞，比如对于下面这张图：

 ![](https://cdn.luogu.com.cn/upload/pic/1545.png) 

（目标是从1走到5，2走到6，绿色为点编号，红色为边权）

如果用上面的思路可以得到，点3,4在公共最短路上，然而abs( dis(1,3) - dis(1,4) ) = 1，可是很显然这张图的答案为0.为什么会出错呢？

因为虽然点3,4处于公共最短路上，但是点3,4之间的边并没有处于公共最短路上。

所以，考虑点是否处于公共最短路上的思路是不正确的，应该要考虑某条边是不是处于公共最短路上。

这样我们又有了另外一种思路：如果一条边所连接的两个点都在公共最短路上，那么这条边是不是也在公共最短路上呢？听起来很合理，但是我们再来看下面这张图：

 ![](https://cdn.luogu.com.cn/upload/pic/1546.png) 

（目标是从1走到2，3走到4，绿色为点编号，红色为边权）

可以发现点1,2在公共最短路上，但是边1-2却不在公共最短路上...又失败了- -

不过没有关系，我们还可以这样想：设一条边连接的两个点为i,j，如果dis(x1,i)+len+dis(j,y1) == dis(x1,y1) 且 dis(x2,i)+len+dis(j,y2) == dis(x2,y2)（len为边权），那么边i-j就在公共最短路上。

这样，找出了所有位于公共最短路上的边，我们只需要在这些边中求一条最长链就可以了。求最长链的方法就相对比较多了，我使用的是拓扑排序：设一条边连接的两个点为i,j，如果dis(x1,i)<dis(x1,j)，那么将这条边的方向指定为i-->j。由于最短路上不会出现环，所以构造出来的图是有向无环图。在这张有向无环图上利用拓扑排序进行dp，求出最长链就好了。

以上是我写这道题时的思路历程，从开始想到写出正解调了一上午，这酸爽...


---

## 作者：cn_lemon (赞：13)

首先我们可以证明一个结论，两对点最短路的最长公共路径一定是一条连续的链：

因为两个点最短路上的每两个点之间的路径都是它们两个点的最短路，如果二号最短路与一号最短路在某个点交叉，又在某个点分开，那么两条路就不可能在别的点再交叉了，不然的话还不如在一号最短路继续走来的近。

OK,我的代码很宏（rong）伟（chang），算法是这样的，先对第一对点进行spfa，然后从终点开始把所有最短路经过的边都标记一下，标记的方法是这样的：如果当前点u离起点的距离是disu,对于u连出去的一条边，如果边的权值为w，而这条边对应的那个点v的disv=disu-w,那么从v到u的这条路径是形成最短路的合法路径，于是我们用类似BFS的操作，把这些边都标记了。

然后再对第二对点的起点终点各自做一次spfa，像对于第一对点一样，把它们存在于最短路中的合法的边标记一下，然后如果有边被重复标记，就加入一个新的图，最后dp求出最长的链就可以了。

这是我第一次做这种最短路找路径的题，没有看过任何一篇题解，于是YY出了这个神（shi）一样的方法，后来看到题解里面四遍spfa的方法感觉比我的好写多了，但实际上进行的都是差不多的操作，只是我找最短路合法路径的方法非常优（ma）雅（fan），而且我的时间复杂度也很优（dan）秀（teng），但是别开生面的方法才能锻炼自己的脑洞，希望大家多多加油。

下附~~优雅的~~代码
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int maxn=1500+10;
int x1,x2,y1,y2;
int a[maxn][maxn];
int n,m;
int dis[maxn],b[maxn][maxn];
int dp[maxn];
bool vis[maxn];
int e,nex[maxn*maxn],beg[maxn],to[maxn*maxn],w[maxn*maxn];
int E,Nex[maxn*maxn],Beg[maxn],To[maxn*maxn],W[maxn*maxn];
inline void add(int u,int v,int ww)
{
    to[++e]=v;
    nex[e]=beg[u];
    beg[u]=e;
    w[e]=ww;
}
inline void Add(int u,int v,int ww)
{
    To[++E]=v;
    Nex[E]=Beg[u];
    Beg[u]=E;
    W[E]=ww;
}
inline void spfa(int sta)
{
    queue<int>q;
    q.push(sta);
    memset(vis,0,sizeof(vis));
    memset(dis,127,sizeof(dis));
    dis[sta]=0;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        vis[u]=0;
        for(register int i=beg[u];i;i=nex[i])
        {
            int v=to[i];
            if(dis[v]>dis[u]+w[i])
            {
                dis[v]=dis[u]+a[u][v];
                if(!vis[v])
                {
                    vis[v]=1;
                    q.push(v);
                }
            }
        }
    }
}
void create()
{
    queue<int>q;
    q.push(y1);
    memset(vis,0,sizeof(vis));
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(register int i=beg[u];i;i=nex[i])
        {
            int v=to[i];
        if(dis[u]-w[i]==dis[v])
        {
            b[u][v]=-1;
            if(!vis[v])
            {
                vis[v]=1;
                q.push(v);
            }
        }
        }
    }
}
void mark(int sta)
{
    queue<int>q;
    q.push(sta);
    memset(vis,0,sizeof(vis));
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(register int i=beg[u];i;i=nex[i])
        {
            int v=to[i];
        if(dis[u]-w[i]==dis[v])
        {
            if(b[u][v]==-1)
            {
                b[u][v]=a[u][v];
                Add(u,v,b[u][v]);
            }
            if(!vis[v])
            {
                vis[v]=1;
                q.push(v);
            }
        }
        }
    }
}
void dfs(int u)
{
    for(register int i=Beg[u];i;i=Nex[i])
    {
        int v=To[i];
        if(dp[v])
        {
            if(b[u][v]>0)dp[u]=max(dp[u],dp[v]+W[i]);
        }
        else
        {
            dfs(v);
            if(b[u][v]>0)dp[u]=max(dp[u],dp[v]+W[i]);
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
    for(register int i=1;i<=m;++i)
    {
        int u,v,ww;
        scanf("%d%d%d",&u,&v,&ww);
        add(u,v,ww);
        add(v,u,ww);
        a[u][v]=a[v][u]=ww;
    }
    spfa(x1);
    create();
    spfa(x2);	
    mark(y2);
    spfa(y2);
    mark(x2);
    for(register int i=1;i<=n;++i)
        if(!dp[i])
            dfs(i);
    int ans=0;
    for(register int i=1;i<=n;++i)
        ans=max(ans,dp[i]);
    printf("%d\n",ans);

    return 0;
}


```

---

## 作者：Foreverxxx (赞：7)

前言：如果没有说 $m$ 的范围，那是真的有点难想……

### 思路

首先我们来思考，两条最短路的公共路径会是什么样子。我们先来画个图。

![](https://cdn.luogu.com.cn/upload/image_hosting/h2ze765d.png)

现在假设 $x_1=1,y_1=10,x_2=5,y_2=10$，那么 $x_1$ 到 $y_1$ 的最短路便是：

![](https://cdn.luogu.com.cn/upload/image_hosting/4lxfvkla.png)

而 $x_2$ 和 $y_2$ 的最短路是：

![](https://cdn.luogu.com.cn/upload/image_hosting/vnjclqpk.png)

所以我们发现，这两条最短路的公共路径，必形成一个联通块。

现在来证明一下（貌似并不需要这么麻烦）：

假设现在这两条最短路的公共路径形成了两个（或多个）联通块，则说明两条路径都可以从一个联通块到达另一个联通块。

不过由于最短路的性质，两个联通块必定会以最短路的方式连接，最终形成一个联通块，不可能形成两个及以上个联通块。

所以我们已经知道，两条最短路径的公共路径会形成一个联通块。

那么问题就比较简单了，只需要求出这个联通块的最长路就行了，于是我们选择跑一次拓扑。

不过现在还有一个问题：这张图是一个无向图，所以说我们需要跑正反两次拓扑，才能得到最终的答案。

### 一些细节

1. 形成的联通块是一张无向图，所以需要跑正反两次拓扑求最长路。

2. 题目没有说 $m$ 的范围，所以说数组得开大一些。

Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int sss=0;
	char chh=getchar();
	while(chh<'0'||chh>'9') chh=getchar();
	while(chh>='0'&&chh<='9'){
		sss=sss*10+chh-'0';
		chh=getchar();
	}
	return sss;
}
int n,m;
int s1,t1,s2,t2;
bool vis[1505];
int in[1505],dis[1505];
int head[1505],to[1000005],val[1000005],nxt[1000005],tot=0;
void add(int u,int v,int w){
	to[++tot]=v;
	val[tot]=w;
	nxt[tot]=head[u];
	head[u]=tot;
}
int head2[1505],to2[1000005],val2[1000005],nxt2[1000005],tot2=0;
void add2(int u,int v,int w){
	to2[++tot2]=v;
	val2[tot2]=w;
	nxt2[tot2]=head2[u];
	head2[u]=tot2;
}
int dist[1505][6];
struct node{
	int dis,pos;
	bool operator<(const node& x)const{
		return x.dis<dis;
	}
};
void Dijkstra(int sta,int num){
	memset(vis,false,sizeof vis);
	priority_queue<node> q;
	q.push((node){0,sta}); dist[sta][num]=0;
	while(!q.empty()){
		int x=q.top().pos; q.pop();
		if(vis[x]) continue;
		vis[x]=true;
		for(register int i=head[x];i;i=nxt[i]){
			int u=to[i],v=val[i];
			if(dist[u][num]>dist[x][num]+v){
				dist[u][num]=dist[x][num]+v;
				if(!vis[u]) q.push((node){dist[u][num],u});
			}
		}
	}
}
void top_sort(){
	memset(dis,0,sizeof dis);
	stack<int> q;
	for(register int i=1;i<=n;i++){
		if(!in[i]) q.push(i);
	}
	while(!q.empty()){
		int x=q.top(); q.pop();
		for(register int i=head2[x];i;i=nxt2[i]){
			int u=to2[i],v=val2[i];
			dis[u]=max(dis[u],dis[x]+v);
			in[u]--; if(!in[u]) q.push(u);
		}
	}
}
signed main(){
	n=read(),m=read(); int u,v,w;
	s1=read(),t1=read(),s2=read(),t2=read();
	for(register int i=1;i<=m;i++){
		u=read(),v=read(),w=read();
		add(u,v,w); add(v,u,w);
	}
	memset(dist,0x3f,sizeof dist);
	Dijkstra(s1,1);
	Dijkstra(t1,2);
	Dijkstra(s2,3);
	Dijkstra(t2,4);
	for(register int x=1;x<=n;x++){
		for(register int i=head[x];i;i=nxt[i]){
			int u=to[i],v=val[i];
			if(dist[x][1]+v+dist[u][2]==dist[t1][1]&&dist[x][3]+v+dist[u][4]==dist[t2][3]){
				add2(x,u,v); in[u]++;
			}
		}
	}
	top_sort();
	int ans=0;
	for(register int i=1;i<=n;i++){
		ans=max(ans,dis[i]);
	}
	memset(dis,0,sizeof dis); memset(in,0,sizeof in);
	memset(head2,-1,sizeof head2); tot2=1;
	for(register int x=1;x<=n;x++){
		for(register int i=head[x];i;i=nxt[i]){
			int u=to[i],v=val[i];
			if(dist[x][1]+v+dist[u][2]==dist[t1][1]&&dist[x][4]+v+dist[u][3]==dist[t2][3]){
				add2(x,u,v); in[u]++;
			}
		}
	}
	top_sort();
	for(register int i=1;i<=n;i++){
		ans=max(ans,dis[i]);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：javalyc (赞：5)

~~现在看看自己早期的题解真是惨不忍睹...~~(upd in 2019.8.11)

这是我第一个自己写的紫题，所以想写一篇题解纪念一下

#~~过了的时候自己都不信~~

[博客传送门qwq](https://www.cnblogs.com/LLTYYC/p/9506297.html )



### 算法 最短路+DAG上的dp~~+建图~~

## 思路

首先是求最短路，但是题目没给出边的范围，所以我选用 $Dijkstra$ 求最短路，~~SPFA可能会爆炸~~

先分别求出以两个人为起点的单源最短路径，然后判断一条边 $(a,b)$ 是否在最短路径上只要判断 $dis[a]+map[a][b]$ 是否等于 $dis[b]$

其中 $map[a][b]$ 表示从点a到点b的 直接 距离 

貌似不用走四遍最短路..

找出最短路径（注意是路径不是路程）后用其中一个人的路径建一个图

如果这个人的最短路径有一种方案使得路径经过 $(a,b)$ 就从 $a$ 连一条边到 $b$，显然这个图是 $DAG$，然后就可以考虑在 $DAG$ 上跑 $dp$ 了

具体就是对于新图的一边连接的两点 $a,b$，如果边 $(a,b)$ 同时在另一个人的最短路径上，那么 $f[b]=max(f[b],f[a]+map[a][b])$

顺便付上自己搞的的样例图（luogu的图片有点大...）
![](https://cdn.luogu.com.cn/upload/pic/26486.png)
具体操作代码里注释还是挺细的吧，因为只要两遍最短路所以常数比较优秀 ?
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
inline int read() //顺手打一个快读 
{
    int res=0;
    char ch=getchar();
    while(ch>'9'||ch<'0')
        ch=getchar();
    while(ch>='0'&&ch<='9')
    {
        res=res*10+ch-'0';
        ch=getchar();
    }
    return res;
}
struct node//为Dijkstra的优先队列开的结构体 
{
	int u,v;//v存储节点编号，u存储到当时点v的最短路径 
	bool operator < (const node &b) const{
		return u>b.u;
	}//重载运算符 
};
priority_queue <node> q;//Dijkstra的优先队列
struct edge
{
	int from,to;
}e[5000005];
int fir[1505],cnt;//存边（边数可能较大，用链式前向星存边会比vector快一些） 
int map[1505][1505];//map[i][j]存从点i到点j的直接距离 
inline void add(int a,int b,int c)
{
	e[++cnt].from=fir[a];
	fir[a]=cnt;
	e[cnt].to=b;
	map[a][b]=c;
}//链式前向星加边 
int xa,ya,xb,yb,n,m;
int dis[1505][2];
//dis[i][0]存 Elaxia从xa到各点的距离，dis[i][1]存w**从xb到各点的距离
inline void dijk(int sta,int k)//Dijkstra求最短路 
{
	dis[sta][k]=0;
	node p;
	p.u=0; p.v=sta;
	q.push(p);
	while(q.empty()==0)
	{
		int u=q.top().u,v=q.top().v;
		q.pop();//出队 
		if(u!=dis[v][k]) continue;//优化 
		for(int i=fir[v];i;i=e[i].from)
		{
			int to=e[i].to;
			if(dis[to][k]>dis[v][k]+map[v][to])//松弛操作 
			{
				dis[to][k]=dis[v][k]+map[v][to];
				p.u=dis[to][k]; p.v=to;
				q.push(p);//入队 
			}
		}
	}
}
vector <int> v[1505];//懒得用链式前向星了，直接用vector存Elaxia的最短路线就好了 
int f[1505],du[1505],ans;
//f[i]表示以i为终点的最长连续 公共最短路长度，du[i]存入度 
queue <int> qa;
bool vis[1505],pd[1505][1505],p[1505];
//vis存Elaxia最短路线上的点
//pd[i][j]=1表示w**的最短路线中有经过从i到j的边,p是用来判断节点是否在队列qa中 
inline void slove()
{
	memset(dis,0x7f,sizeof(dis));
	dijk(xa,0);
	dijk(xb,1);
	qa.push(ya);
	//反向找出最短路径上的点，保证先出队的节点在Elaxia的最短路径上处于更后的位置
	//从终点开始找，保证找到的满足条件的点一定在Elaxia的最短路上
	vis[ya]=1;
	while(qa.empty()==0)
	{
		int x=qa.front(); qa.pop();
		for(int i=fir[x];i;i=e[i].from)
		{
			int u=e[i].to;
			if(dis[u][0]+map[u][x]==dis[x][0])
			//如果一个节点u满足条件，说明u在Elaxia的最短路上
			{
				v[u].push_back(x);//从u到点x连一条有向边 
				du[x]++;//点x的入度加一 
				if(vis[u]==0)//如果没有加入过 
				{
					qa.push(u);//把u加入队列，从而找到更"前面"的点 
					vis[u]=1;//现在加入过了 
				}
			}
		}
	}
	//此时qa已经空了，可以重复利用 
	qa.push(yb); //开始找w**的最短路径 
	p[yb]=1;//vis数组要留着，重新开一个数组p 
	while(qa.empty()==0)//同上
	{
		int x=qa.front(); qa.pop();
		for(int i=fir[x];i;i=e[i].from)
		{
			int u=e[i].to;
			if(dis[u][1]+map[u][x]==dis[x][1])//同上 
			{
				pd[x][u]=pd[u][x]=1;//这次不用连边了，方便后面的判断 
				//正反都要判断，可能是反着走 
				if(p[u]==0)
				{
					p[u]=1;
					qa.push(u);
				}
			}
		}
	}
	//以下为DAG上的dp 
	for(int i=1;i<=n;i++)
		if(du[i]==0&&vis[i])//如果i点入度为零且 Elaxia的最短路经过i
			qa.push(i);//把i加入qa
	while(qa.empty()==0)
	{
		int x=qa.front(); qa.pop();
		int len=v[x].size();
		for(int i=0;i<len;i++)
		{
			int u=v[x][i];//首先能够保证 Elaxia的最短路经过边x->i 
			du[u]--;//入度减一 
			if(pd[x][u]) //如果边x->i也被w**的最短路经过 
				f[u]=max(f[u],f[x]+map[x][u]);//更新长度 
			if(du[u]==0)
				qa.push(u);//dp要按照拓扑序来保证这个点前面的所有点都访问过了 
		}
	}
	//以上为DAG上的dp 
	for(int i=1;i<=n;i++)
		ans=max(ans,f[i]);//找出答案 
}
int main()
{
	memset(map,0x7f,sizeof(map));
	cin>>n>>m;
	cin>>xa>>ya>>xb>>yb;
	int a,b,c;
	for(int i=1;i<=m;i++)
	{
		a=read(); b=read(); c=read(); 
		add(a,b,c);
		add(b,a,c);
	}
	slove();
	cout<<ans;
	return 0;//简单易懂的主程序 
}
```
然而洛谷的数据真的水..就过了

#### 其实这是有问题的（感谢[Brave_Cattle](https://www.luogu.org/space/show?uid=45661) 巨佬指出错误）

有一种可能数据：

4 4

1 4 2 3

1 2 10

1 3 1

4 2 9

4 3 2

![](https://cdn.luogu.com.cn/upload/pic/31762.png)

显然答案是 $2$，但是我的程序输出是$3$...

因为我没有考虑到最短路径只能选一种走...

那要怎么解决呢

也不难，虽然要考虑正反方向，但是显然不会一下正着走，一下反着走

所以分开讨论一下就好了..然后代码就变得更长了...

懒得重新写代码了...
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
inline int read() //顺手打一个快读 
{
    int res=0;
    char ch=getchar();
    while(ch>'9'||ch<'0')
        ch=getchar();
    while(ch>='0'&&ch<='9')
    {
        res=res*10+ch-'0';
        ch=getchar();
    }
    return res;
}
struct node//为Dijkstra的优先队列开的结构体 
{
    int u,v;//v存储节点编号，u存储到当时点v的最短路径 
    bool operator < (const node &b) const{
        return u>b.u;
    }//重载运算符 
};
priority_queue <node> q;//Dijkstra的优先队列
struct edge
{
    int from,to;
}e[5000005];
int fir[1505],cnt;//存边（边数可能较大，用链式前向星存边会比vector快一些） 
int map[1505][1505];//map[i][j]存从点i到点j的直接距离 
inline void add(int a,int b,int c)
{
    e[++cnt].from=fir[a];
    fir[a]=cnt;
    e[cnt].to=b;
    map[a][b]=c;
}//链式前向星加边 
int xa,ya,xb,yb,n,m;
int dis[1505][2];
//dis[i][0]存 Elaxia从xa到各点的距离，dis[i][1]存w**从xb到各点的距离
inline void dijk(int sta,int k)//Dijkstra求最短路 
{
    dis[sta][k]=0;
    node p;
    p.u=0; p.v=sta;
    q.push(p);
    while(q.empty()==0)
    {
        int u=q.top().u,v=q.top().v;
        q.pop();//出队 
        if(u!=dis[v][k]) continue;//优化 
        for(int i=fir[v];i;i=e[i].from)
        {
            int to=e[i].to;
            if(dis[to][k]>dis[v][k]+map[v][to])//松弛操作 
            {
                dis[to][k]=dis[v][k]+map[v][to];
                p.u=dis[to][k]; p.v=to;
                q.push(p);//入队 
            }
        }
    }
}
vector <int> v[1505];//懒得用链式前向星了，直接用vector存Elaxia的最短路线就好了 
int f[1505],du[1505],ans;
//f[i]表示以i为终点的最长连续 公共最短路长度，du[i]存入度 
queue <int> qa;
bool vis[1505],pd[1505][1505],p[1505];
//vis存Elaxia最短路线上的点
//pd[i][j]=1表示w**的最短路线中有经过从i到j的边,p是用来判断节点是否在队列qa中 
int duu[1505];//du数组的拷贝
int t[2265025][2],tot;
inline void slove()
{
    memset(dis,0x7f,sizeof(dis));
    dijk(xa,0);
    dijk(xb,1);
    qa.push(ya);
    //反向找出最短路径上的点，保证先出队的节点在Elaxia的最短路径上处于更后的位置
    //从终点开始找，保证找到的满足条件的点一定在Elaxia的最短路上
    vis[ya]=1;
    while(qa.empty()==0)
    {
        int x=qa.front(); qa.pop();
        for(int i=fir[x];i;i=e[i].from)
        {
            int u=e[i].to;
            if(dis[u][0]+map[u][x]==dis[x][0])
            //如果一个节点u满足条件，说明u在Elaxia的最短路上
            {
                v[u].push_back(x);//从u到点x连一条有向边 
                du[x]++;//点x的入度加一 
                if(vis[u]==0)//如果没有加入过 
                {
                    qa.push(u);//把u加入队列，从而找到更"前面"的点 
                    vis[u]=1;//现在加入过了 
                }
            }
        }
    }
    //此时qa已经空了，可以重复利用 
    qa.push(yb); //开始找w**的最短路径 
    p[yb]=1;//vis数组要留着，重新开一个数组p 
    while(qa.empty()==0)//同上
    {
        int x=qa.front(); qa.pop();
        for(int i=fir[x];i;i=e[i].from)
        {
            int u=e[i].to;
            if(dis[u][1]+map[u][x]==dis[x][1])//同上 
            {
                pd[u][x]=1;//这次不用连边了，方便后面的判断 
                t[++tot][0]=u; t[tot][1]=x; //可能路径方向相反，先用一个数组存着
                if(p[u]==0)
                {
                    p[u]=1;
                    qa.push(u);
                }
            }
        }
    }

    //以下为DAG上的dp 
    //第一遍先找方向相同的路径
    for(int i=1;i<=n;i++)
    {
        if(du[i]==0&&vis[i])//如果i点入度为零且 Elaxia的最短路经过i
            qa.push(i);//把i加入qa
        duu[i]=du[i];//拷贝一下du,因为要用两次
    }
    while(qa.empty()==0)
    {
        int x=qa.front(); qa.pop();
        int len=v[x].size();
        for(int i=0;i<len;i++)
        {
            int u=v[x][i];//首先能够保证 Elaxia的最短路经过边x->v[x][i] 
            duu[u]--;//入度减一
            if(pd[x][u]) //如果边x->i也被w**的最短路经过 
                f[u]=max(f[u],f[x]+map[x][u]);//更新长度 
            if(duu[u]==0)
                qa.push(u);//dp要按照拓扑序来保证这个点前面的所有点都访问过了 
        }
    }
    for(int i=1;i<=n;i++)
        ans=max(ans,f[i]);//更新答案
    
    //第二遍找方向相反的路径，同上
    memset(f,0,sizeof(f));
    for(int i=1;i<=tot;i++)
    {
        pd[t[i][0]][t[i][1]]=0;
        pd[t[i][1]][t[i][0]]=1; //把路径换个方向
    }
    for(int i=1;i<=n;i++)
        if(du[i]==0&&vis[i])
            qa.push(i);//同上
    while(qa.empty()==0)
    {
        int x=qa.front(); qa.pop();
        int len=v[x].size();
        for(int i=0;i<len;i++)
        {
            int u=v[x][i];
            du[u]--;
            if(pd[x][u])
                f[u]=max(f[u],f[x]+map[x][u]);
            if(du[u]==0)
                qa.push(u);
        }
    }//同上

    //以上为DAG上的dp 
    for(int i=1;i<=n;i++)
        ans=max(ans,f[i]);
}
int main()
{
    memset(map,0x7f,sizeof(map));
    cin>>n>>m;
    cin>>xa>>ya>>xb>>yb;
    int a,b,c;
    for(int i=1;i<=m;i++)
    {
        a=read(); b=read(); c=read(); 
        add(a,b,c);
        add(b,a,c);
    }
    slove();
    cout<<ans;
    return 0;//简单易懂的主程序 
}
```
#### P.S 我的上一篇题解好像是在几年前了，这是我的第二篇题解，希望写得好一点，所以注释比较细

---

## 作者：Kevin_F (赞：3)

## **分析：**

我最开始想的是跑两遍最短路，然后记录一下最短路走了哪些边（如果有两条最短路就选经过边多的），打上标记。两边之后找两次都标记的边有多少就行了。

但。。。我并没有实现出来。

最后让我们看一下正解：

## _**四边spfa+拓扑排序求最长边**_   

先让我们考虑如何求两对点最短路的最长公共路径？

1.先明白：如果有一条边，它的起点到最短路的起点 + 终点到最短路的终点 + 边权 == 最短路起点到终点的距离，那么这条边一定在最短路上。

也就是说如果有一条边$i:from -> to$权值是w在最短路$x -> y$上，那么有$dis_{x->from} + dis_{to->y} + edge[i]._w == dis_{x->y}$


2.所以就可以把两条最短路径都经过的边重新建图

3.最后就是求最长路即可（显然图是DAG  拓扑排序可以求）。

**注意！！注意！！注意！！**

1.最开始我们建的是无向图，也就是说：$dis_{from->to} + w$ 和  $dis_{to->from} + w$是一样的。

2.重新建图的时候我们建的是有向图。

最短路和普通的$spfa$没什么区别，稍微改了一下dis数组，那样就不用开4个dis了。

拓扑序也差不多，$ind[i]$表示第$i$点的入度。


**总体来说**，这个题主要还是想法，还有对基础算法的应用。挺好一个题。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn = 1505;

inline int read(){
	char ch = getchar(); int f = 1 , x = 0;
	while(ch > '9' || ch < '0'){if(ch == '-') f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
	return x * f;
}

int n,m,x,y,xx,yy,u,v,w;
struct Edge{
	int from,to,next,val;
	int tag;
}edge[maxn * maxn] , e[maxn * maxn];
int head1[maxn],tot1,head2[maxn],tot2;
int dis[5][maxn],ind[maxn];
bool vis[maxn];
int f[maxn];

void add(int u,int v,int w){
	edge[++tot1].to = v;
	edge[tot1].from = u;
	edge[tot1].next = head1[u];
	edge[tot1].val = w;
	head1[u] = tot1;
}

void addedge(int u,int v,int w){
	e[++tot2].from = u;
	e[tot2].to =	 v;
	e[tot2].val = w;
	e[tot2].next = head2[u];
	head2[u] = tot2;
}

void spfa(int s,int flag){
	queue<int> q;
	for(int i=1;i<=n;i++)  dis[flag][i] = 1e9;
	memset(vis,false,sizeof(vis));
	q.push(s);
	dis[flag][s] = 0;  vis[s] = true;
	while(!q.empty()){
		int cur = q.front();
		q.pop(); vis[cur] = false;
		for(int i=head1[cur];i;i=edge[i].next){
			int v = edge[i].to;
			if(dis[flag][v] > dis[flag][cur] + edge[i].val){
				dis[flag][v] = dis[flag][cur] + edge[i].val;
				if(vis[v] == 0){
					q.push(v);
					vis[v] = true;
				}
			}
		}
	}
}

inline void topo(){
	queue<int> que;
	que.push(x);
	while(!que.empty()){
		int cur = que.front();
		que.pop();
		for(int i=head2[cur];i;i=e[i].next){
			int v = e[i].to , w = e[i].val;
			--ind[v];
			if(!ind[v]) {
				que.push(v);
				f[v] = max(f[v] , f[cur] + e[i].tag * w);
			}
		}
	}
}

void rebuild(){
	for(int i=1;i<=tot1;i++){
		int v = edge[i].to , u = edge[i].from , w = edge[i].val;
		if(dis[1][u] + w + dis[2][v] == dis[1][y]){
			addedge(u , v , w);
			if(dis[3][u] + w + dis[4][v] == dis[3][yy] || dis[3][v] + w + dis[4][u] == dis[3][yy])
			//为了处理无向图的问题 
			e[tot2].tag = 1;
			ind[v]++;
		}
	}
}

int main(){
	n = read(); m = read();
	x = read(); y = read(); xx = read(); yy = read();
	for(int i=1;i<=m;i++){
		u = read(); v = read(); w = read();
		add(u , v , w);
		add(v , u , w);
	}
	spfa(x , 1);
	spfa(y , 2);
	spfa(xx , 3);
	spfa(yy , 4);
	rebuild();
	topo();
	printf("%d\n",f[y]);
	return 0;
}
```

---

## 作者：Avocadooo (赞：2)

（注：本题解的 std 通过了题目讨论区中由 @[lemir3](https://www.luogu.com.cn/user/54986) 给出的 [HACK 数据](https://www.luogu.com.cn/discuss/261934)）

### 1.题目类型判断

浏览题目，简化题意：

>求一无向图中，两对点间最短路的最长公共路径。（最短路可能有多条）

显然是最短路相关的图论题。




### 2.基本思路

考虑建立一个“最短路公共路径图”，里面只包含两点对的最短路的公共路径，再求出其中最长的路径即可。

### 首先扫波雷！
> $ 1. $ 对于一个点对，考虑起讫点各搜一次最短路，记录对于每一个点的距离数组 $ dist[start][i],dist[end][i] $ 。而当 $ dist[start][i]+dist[end][i] $ 等于起讫点之间的最短路，那么这个点一定在起讫点的某一条最短路上，用得出的这些点重新建图。

这个想法是错误的！我们要求的不是最短路包含公共点数的最大值，而求的是最长公共路径。我们要枚举的是最短路包含边，而不是最短路包含点。两个在**不同最短路**上的点可能连接有新的一条边，而这条边是不可以加上去的！

虽然上面想法错误，但是我们仍可从中获得一些思路。那就是枚举每条边的端点 $ x,y $ ，若 $ dist[start][x]+dist[end][y]+d(x,y)=dist[start][end] $ ，说明**这条边**存在于起讫点的最短路上。


### 二次扫雷!

> $ 2. $ 由起点到终点搜得的边建立新的一个的 DAG ，跑一边拓扑排序求得答案。

我们肯定需要这么干，**但不仅仅是这么干。** 我们仍然需要由终点到起点再建立一个 DAG ，再跑一边拓扑排序，才能求得最终答案。

因为题目准确提到了是在 **"无向图"** 中的最短路最长公共路径。也就是不考虑两点对的最短路的公共路径上状态是**相同方向**或是**相反方向**。所以建 DAG 要建两次！

### 3.std代码 ~~（你们最喜欢的）~~

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#define N 1000005
#define INF 0x7fffffff/2
using namespace std;
int MAX(int c,int d)
{
	return c>d?c:d;
}
int n,m;
int s1,t1,s2,t2;
struct Edge
{
	int next,to,v;
};
Edge e[N];
int h[N],cnt;
void AddEdge(int c,int d,int v)
{
	e[++cnt]=(Edge){h[c],d,v};
	h[c]=cnt;
}
Edge e2[N];
int h2[N],cnt2;
void AddEdge2(int c,int d,int v)
{
	e2[++cnt2]=(Edge){h2[c],d,v};
	h2[c]=cnt2;
}
queue<int> q;
int rd[N],dp[N];
void tpsort()
{
	for(int i=1;i<=n;i++) if(!rd[i]) q.push(i);
	while(!q.empty())
	{
		int u=q.front(); q.pop();
		for(int i=h2[u];i;i=e2[i].next)
		{
			int y=e2[i].to,C=e2[i].v;
			dp[y]=max(dp[y],dp[u]+C);
			if(!--rd[y]) q.push(y);
		}
	}
}
int d[5][N];
bool vst[5][N];
void SPFA(int num,int r)
{
	for(int i=1;i<=n;i++) d[num][i]=INF;
	d[num][r]=0;
	q.push(r);
	while(!q.empty())
	{
		int u=q.front(); q.pop();
		vst[num][u]=false;
		for(int i=h[u];i;i=e[i].next)
		{
			int y=e[i].to,C=e[i].v;
			if(d[num][y]>d[num][u]+C)
			{
				d[num][y]=d[num][u]+C;
				if(!vst[num][y])
				{
					vst[num][y]=true;
					q.push(y);
				}
			}
		}
	}
}
int main()
{
	scanf("%d %d",&n,&m);
	scanf("%d %d %d %d",&s1,&t1,&s2,&t2);
	for(int i=1,x,y,z;i<=m;i++)
	{
		scanf("%d %d %d",&x,&y,&z);
		AddEdge(x,y,z);
		AddEdge(y,x,z);
	}
	SPFA(1,s1); SPFA(2,t1); SPFA(3,s2); SPFA(4,t2);
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=h[i];j;j=e[j].next)
		{
			int y=e[j].to,C=e[j].v;
			if(d[3][i]+d[4][y]+C==d[3][t2])
			{
				if(d[1][i]+d[2][y]+C==d[1][t1])
				{
					AddEdge2(i,y,C);
					rd[y]++;
				}
			}
		}
	}
	tpsort();
	for(int i=1;i<=n;i++) ans=max(ans,dp[i]);
	memset(dp,0,sizeof(dp));
	memset(rd,0,sizeof(rd));
	memset(e2,0,sizeof(e2));
	memset(h2,0,sizeof(h2));
	cnt2=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=h[i];j;j=e[j].next)
		{
			int y=e[j].to,C=e[j].v;
			if(d[3][i]+d[4][y]+C==d[3][t2])
			{
				if(d[1][y]+d[2][i]+C==d[1][t1])
				{
					AddEdge2(y,i,C);
					rd[i]++;
				}
			}
		}
	}
	tpsort();
	for(int i=1;i<=n;i++) ans=max(ans,dp[i]);
	printf("%d",ans);
}
```

---

## 作者：檀黎斗·神 (赞：2)

先以给出的四个点为起点的SPFA遍历一遍

以Elaxia的最短路和Elaxia、w的公共最短路建立一个新图

怎么判断某边是否为最短路呢？

其实可以通过判断dis(u,i)+len(i,j)+dis(j,v) == /！= dis(u,v)

接下来用拓扑排序递推：f[b[i].v]=max(f[b[i].v],f[temp]+b[i].w\*b[i].f)

```cpp
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
struct node{
    int u,v,w,nxt,f;
}a[4000005],b[4000005];
queue<int>q;
int n,m,cnt,ct2;
int h[2005],p[5],d[5][2005],h2[2005],r[2005],f[2005];
void add(int u,int v,int w)
{
    a[++cnt].u=u;
    a[cnt].v=v;
    a[cnt].w=w;
    a[cnt].nxt=h[u]; 
    h[u]=cnt;
}
void SPFA(int x)
{    
    bool v[1505]={0};
    for(int i=1;i<=n;++i) 
    if(i!=p[x]) d[x][i]=0x3f3f3f3f;
    q.push(p[x]);
    v[p[x]]=1;
    while( !q.empty() )
    {
        int now=q.front();
        q.pop(),v[now]=0;
        for(int i=h[now];i;i=a[i].nxt)
        {
            int to=a[i].v;
            if(d[x][to]>d[x][now]+a[i].w)
            {
                d[x][to]=d[x][now]+a[i].w;
                if(!v[to]) v[to]=1,q.push(to);
            } 
        }            
    }
}
int main()
{
    int x,y,z;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=4;++i) scanf("%d",&p[i]);
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d%d",&x,&y,&z);
        add(x,y,z),add(y,x,z);
    }
    for(int i=1;i<=4;++i) SPFA(i);
    

    for(int i=1;i<=cnt;++i) //以Elaxia为主重建图 
     if(d[1][a[i].u]+a[i].w+d[2][a[i].v]==d[1][p[2]])
     {
         b[++ct2].u==a[i].u; 
         b[ct2].v=a[i].v; 
         b[ct2].w=a[i].w; 
         b[ct2].nxt=h2[a[i].u]; 
         h2[a[i].u]=ct2;
         if(d[3][a[i].u]+a[i].w+d[4][a[i].v]==d[3][p[4]]||d[4][a[i].u]+a[i].w+d[3][a[i].v]==d[3][p[4]]) b[ct2].f=1;
         r[a[i].v]++;
     }
    
    q.push(p[1]);
    int now;
    while(!q.empty())//拓扑排序找关键路径 
    {
        now=q.front(); q.pop();
        for(int i=h2[now];i;i=b[i].nxt)
        {
            --r[b[i].v];
            if(!r[b[i].v])
            {
                q.push(b[i].v);
                f[b[i].v]=max(f[b[i].v],f[now]+b[i].w*b[i].f);
            }
        }
    }
    printf("%d",f[p[2]]);
    return 0;
}
```

---

## 作者：vani_prcups (赞：2)

人生中A的第二道省选/NOI-……

这题好像是~~用某F姓大佬裸的增广路算法做的~~最长公共最短路模板。

其实理解算法并不难，先把以四个点为起点的SPFA跑一遍，然后建新图，只保留Elaxia的最短路（边权为0）和Elaxia、w的公共最短路。这里怎么判断某边是否是最短路呢？答案是用这个：

```cpp
dis(s,i)+len(i,j)+dis(j,t)=dis(s,t)
```
下一步可以用拓扑排序递推：

```cpp
f[b[i].t]=max(f[b[i].t],f[temp]+b[i].v*b[i].ok)
```
最后输出Elaxia终点的f值。

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
queue <int> q;
struct node
{
    int f,t,nt,v,ok;
}a[2000005],b[2000005];
int n,m,head[1505],len,lt,s[6],ht[1505],visited[1505],dis[5][1505],f[1505],to[1505];
void spfa(int p)
{
    visited[s[p]]=1;
    q.push(s[p]);
    for (int i=1;i<=n;i++)
    if (i!=s[p])dis[p][i]=0x7fffffff/3;
    int temp;
    while (!q.empty())
    {
        temp=q.front();
        q.pop();
        visited[temp]=0;
        for (int i=head[temp];i;i=a[i].nt)
        {
            if (dis[p][a[i].t]>dis[p][temp]+a[i].v)
            {
                dis[p][a[i].t]=dis[p][temp]+a[i].v;
                if (visited[a[i].t]==0)visited[a[i].t]=1,q.push(a[i].t);
            }
        }
    }
}
int main()
{
    scanf("%d %d",&n,&m);
    for (int i=1;i<=4;i++)
    scanf("%d",&s[i]);
    int u,v,w;
    for (int i=1;i<=m;i++)//输入，双向建图
    {
        scanf("%d %d %d",&u,&v,&w);
        a[++len].t=v;
        a[len].f=u;
        a[len].v=w;
        a[len].nt=head[u];
        head[u]=len;
        a[++len].t=u;
        a[len].f=v;
        a[len].v=w;
        a[len].nt=head[v];
        head[v]=len;
    }
    for (int i=1;i<=4;i++)//四次SPFA
    spfa(i);
    for (int i=1;i<=len;i++)
    if (dis[1][a[i].f]+a[i].v+dis[2][a[i].t]==dis[1][s[2]])//重建图，以Elaxia为主
    {
        b[++lt].t=a[i].t;
        if (dis[3][a[i].f]+a[i].v+dis[4][a[i].t]==dis[3][s[4]]||dis[4][a[i].f]+a[i].v+dis[3][a[i].t]==dis[3][s[4]])
        b[lt].ok=1;
        b[lt].f=a[i].f;
        b[lt].v=a[i].v;
        b[lt].nt=ht[a[i].f];
        ht[a[i].f]=lt;
        to[a[i].t]++;
    }
    q.push(s[1]);//拓扑排序
    int temp;
    while (!q.empty())
    {
        temp=q.front();
        q.pop();
        for (int i=ht[temp];i;i=b[i].nt)
        {
            --to[b[i].t];
            if (to[b[i].t]==0)
            {
                q.push(b[i].t);
                f[b[i].t]=max(f[b[i].t],f[temp]+b[i].v*b[i].ok);
            }
        }
    }
    printf("%d",f[s[2]]);
}
```

---

## 作者：木木！ (赞：1)

蒟蒻的第一道紫题题解……最慢的做法（300+ms）

思路：首先跑四遍Dijkstra，选出所有满足`dists1[a]+distt1[a]==dists1[t1] && dists2[a]+distt2[a]==dists2[t2]`的点，即在双方最短路上都有的点。

可以看到，这些点构成了一些子图，这些子图的直径就是所求的长度。证明不会证。

求直径的方法就是随便选一个点，跑一遍Dijkstra，找到最远的那个点，再跑一遍Dijkstra，找到最远的距离，就是直径。（不会证）

时间复杂度：$\Theta((n+m)logm + n^2)$，循环里的Dijkstra可以被均摊掉，总花费不会大于一次整图的Dijkstra。

优化一下（在Dijkstra里面直接用队列记录访问过的点）可以做到$\Theta((n+m)logm)$，但是我懒……再说常数那么大，就算优化了也优化不了几ms。

用了一点函数指针知识以简化代码。

```cpp
#include <queue>
#include <cstdio>
using namespace std;

void chkmax(int& a,int b)
{
	if(b>a)
	{
		a = b;
	}
}

int beg[1505];
int ed[450005];
int nxt[450005];
int len[450005];
int top;

void addedge(int a,int b,int l)
{
	++top;
	len[top] = l;
	nxt[top] = beg[a];
	beg[a] = top;
	ed[top] = b;
}

int n;
int vis[1505];

void fillter_dijkstra(int* dist,int s,bool (*fillter)(int)) //fillter是个函数指针
{
	for(int i=1; i<=n; ++i)
	{
		dist[i] = 0x7f7f7f7f;
		vis[i] = 0;
	}
	dist[s] = 0;
	priority_queue<pair<int,int> > pq;
	pq.push(make_pair(0,s));

	while(!pq.empty())
	{
		int th = pq.top().second;
		pq.pop();
		while(vis[th])
		{
			if(pq.empty()) break;
			th = pq.top().second;
			pq.pop();
		}

		vis[th] = 1;

		for(int p=beg[th]; p; p=nxt[p])
		{
			if(fillter(ed[p]) && dist[th]+len[p] < dist[ed[p]])
			{
				dist[ed[p]] = dist[th]+len[p];
				pq.push(make_pair(-dist[ed[p]],ed[p]));
			}
		}
	}
}

bool always(int x)
{
	return true;
}

void dijkstra(int* dist,int s)
{
	fillter_dijkstra(dist,s,always);
}

int s1,t1,s2,t2;
int dists1[1505];
int dists2[1505];
int distt1[1505];
int distt2[1505];

bool can(int a)
{
	return dists1[a]+distt1[a]==dists1[t1] && dists2[a]+distt2[a]==dists2[t2];
}

int caned[1505];
int disttmp[1505];

int main()
{
	int m;
	scanf("%d%d%d%d%d%d",&n,&m,&s1,&t1,&s2,&t2);
	for(int i=1; i<=m; ++i)
	{
		int a,b,l;
		scanf("%d%d%d",&a,&b,&l);
		addedge(a,b,l);
		addedge(b,a,l);
	}

	dijkstra(dists1,s1);
	dijkstra(dists2,s2);
	dijkstra(distt1,t1);
	dijkstra(distt2,t2);

	int ans = 0;

	for(int i=1; i<=n; ++i)
	{
		if(!caned[i] && can(i))
		{
			fillter_dijkstra(disttmp,i,can);

			int maxpos = i;
			for(int j=1; j<=n; ++j)
			{
				if(vis[j])
				{
					caned[j] = 1;
					if(disttmp[j] > disttmp[maxpos])
					{
						maxpos = j;
					}
				}
			}

			fillter_dijkstra(disttmp,maxpos,can);

			for(int j=1; j<=n; ++j)
			{
				if(vis[j])
				{
					chkmax(ans,disttmp[j]);
				}
			}
		}
	}

	printf("%d\n",ans);
}
```

---

## 作者：wumingshi (赞：1)

这道题其实明白后思路很简单：四遍SPFA，然后判断每一条边是否可以在最短路中，是的话就新开一个图，在同一位置加入一条单向边，然后进行拓扑排序，维护答案最大值就好了。由于原题中两人面对面经过也同样算作可行方案，所以我们需要选择出允许两人面对面经过的可行最短路方案，再重新开一个图跑一遍拓扑排序，维护出答案就好了。

另外注意：这道题虽然有很多人AC了，但是在bzoj的讨论中有两组数据，大部分人的代码是无法通过这两个测试数据的，包括楼上两位的题解。经测试，PoPoQQQ大神的代码是真正正确的，于是本蒟蒻就参考了Po姐的代码^\_^

不过Po姐的代码中最后两遍SPFA是冗余的，只要改一下判断中的数组名称就可以达到同样的效果

[Po姐传送门](http://blog.csdn.net/popoqqq/article/details/44513281)

附上bzoj讨论中的两组数据：

8 8
1 3 2 4

1 6 1
3 8 1
2 5 1
4 7 1
5 6 1
6 7 1
7 8 1
8 5 1
正确答案：1，错误答案：2

8 9
1 6 7 8

1 2 1
2 3 1
3 4 1
4 5 1
5 6 1
7 3 5
7 5 5
2 8 4
4 8 4
正确答案：1，错误答案：3

蒟蒻丑陋的代码：

```c++
#include<queue>
#include<cstdio>
#include<cstring>
using namespace std;
struct edge
{
    int nxt,to,dis;
}a[3000010];
int head[10000];
int Head[10000];
int lv[10000];
bool b[10000];
int s1[10000],t1[10000],s2[10000],t2[10000];
int n,m,x1,y1,x2,y2,x,y,z,num,ans;
queue<int>q;
inline int max(int a,int b){return a>b?a:b;}
inline void add(int head[],int x,int y,int z){a[++num].nxt=head[x],a[num].to=y,a[num].dis=z,head[x]=num;}
inline void Add(int head[],int x,int y,int z){add(head,x,y,z);add(head,y,x,z);}
inline void SPFA(int S,int dis[])
{
    memset(dis,0x3f,sizeof (int)*1510);
    dis[S]=0;q.push(S);
    while(!q.empty())
    {
        int tmp=q.front();q.pop();
        b[tmp]=0;
        for(int i=head[tmp];i;i=a[i].nxt)
          if(dis[a[i].to]>dis[tmp]+a[i].dis)
          {
              dis[a[i].to]=dis[tmp]+a[i].dis;
              if(!b[a[i].to]) b[a[i].to]=1,q.push(a[i].to);
          }
    }
}
inline void topologysort()
{
    int dis[10000];
    memset(dis,0,sizeof(dis));
    for(int i=1;i<=n;i++)
      if(!lv[i]) q.push(i);
    while(!q.empty())
    {
        int tmp=q.front();q.pop();
        ans=max(ans,dis[tmp]);
        for(int i=Head[tmp];i;i=a[i].nxt)
        {
            dis[a[i].to]=max(dis[a[i].to],dis[tmp]+a[i].dis);
            if(!--lv[a[i].to]) q.push(a[i].to);
        }
    }
}
int main()
{
    scanf("%d%d%d%d%d%d",&n,&m,&x1,&y1,&x2,&y2);
    for(int i=1;i<=m;i++)
      scanf("%d%d%d",&x,&y,&z),Add(head,x,y,z);
    SPFA(x1,s1);SPFA(y1,t1);
    SPFA(x2,s2);SPFA(y2,t2);
    for(int tmp=1;tmp<=n;tmp++)
      for(int i=head[tmp];i;i=a[i].nxt)
        if(s1[tmp]+a[i].dis+t1[a[i].to]==s1[y1]&&s2[tmp]+a[i].dis+t2[a[i].to]==s2[y2])
          add(Head,tmp,a[i].to,a[i].dis),lv[a[i].to]++;
    topologysort();
    memset(Head,0,sizeof(Head));
    for(int tmp=1;tmp<=n;tmp++)
      for(int i=head[tmp];i;i=a[i].nxt)
        if(s1[tmp]+a[i].dis+t1[a[i].to]==s1[y1]&&s2[a[i].to]+a[i].dis+t2[tmp]==s2[y2])
          add(Head,tmp,a[i].to,a[i].dis),lv[a[i].to]++;
    topologysort();
    printf("%d",ans);
    return 0;
}
```c++
```cpp
#include<queue>
#include<cstdio>
#include<cstring>
using namespace std;
struct edge
{
    int nxt,to,dis;
}a[3000010];
int head[10000];
int Head[10000];
int lv[10000];
bool b[10000];
int s1[10000],t1[10000],s2[10000],t2[10000];
int n,m,x1,y1,x2,y2,x,y,z,num,ans;
queue<int>q;
inline int max(int a,int b){return a>b?a:b;}
inline void add(int head[],int x,int y,int z){a[++num].nxt=head[x],a[num].to=y,a[num].dis=z,head[x]=num;}
inline void Add(int head[],int x,int y,int z){add(head,x,y,z);add(head,y,x,z);}
inline void SPFA(int S,int dis[])
{
    memset(dis,0x3f,sizeof (int)*1510);
    dis[S]=0;q.push(S);
    while(!q.empty())
    {
        int tmp=q.front();q.pop();
        b[tmp]=0;
        for(int i=head[tmp];i;i=a[i].nxt)
          if(dis[a[i].to]>dis[tmp]+a[i].dis)
          {
              dis[a[i].to]=dis[tmp]+a[i].dis;
              if(!b[a[i].to]) b[a[i].to]=1,q.push(a[i].to);
          }
    }
}
inline void topologysort()
{
    int dis[10000];
    memset(dis,0,sizeof(dis));
    for(int i=1;i<=n;i++)
      if(!lv[i]) q.push(i);
    while(!q.empty())
    {
        int tmp=q.front();q.pop();
        ans=max(ans,dis[tmp]);
        for(int i=Head[tmp];i;i=a[i].nxt)
        {
            dis[a[i].to]=max(dis[a[i].to],dis[tmp]+a[i].dis);
            if(!--lv[a[i].to]) q.push(a[i].to);
        }
    }
}
int main()
{
    scanf("%d%d%d%d%d%d",&n,&m,&x1,&y1,&x2,&y2);
    for(int i=1;i<=m;i++)
      scanf("%d%d%d",&x,&y,&z),Add(head,x,y,z);
    SPFA(x1,s1);SPFA(y1,t1);
    SPFA(x2,s2);SPFA(y2,t2);
    for(int tmp=1;tmp<=n;tmp++)
      for(int i=head[tmp];i;i=a[i].nxt)
        if(s1[tmp]+a[i].dis+t1[a[i].to]==s1[y1]&&s2[tmp]+a[i].dis+t2[a[i].to]==s2[y2])
          add(Head,tmp,a[i].to,a[i].dis),lv[a[i].to]++;
    topologysort();
    memset(Head,0,sizeof(Head));
    for(int tmp=1;tmp<=n;tmp++)
      for(int i=head[tmp];i;i=a[i].nxt)
        if(s1[tmp]+a[i].dis+t1[a[i].to]==s1[y1]&&s2[a[i].to]+a[i].dis+t2[tmp]==s2[y2])
          add(Head,tmp,a[i].to,a[i].dis),lv[a[i].to]++;
    topologysort();
    printf("%d",ans);
    return 0;
}
```
```cpp

---

## 作者：__stdcall (赞：1)

其实楼下几位给的判定“某一条边在不在最短路中的方法”确实不错

即根据最短路的性质，若dis(s,i)+len(i,j)+dis(j,t)=dis(s,t)，则边(i,j)在s->t的最短路上

但是我常用的是另外一种方法，效率也不错

这种方法类似于dp中，计算出所有状态，最后要打印解的时候的“顺着最终状态找决策”

这种方法只用spfa两遍，不过仍然要倒序寻找两遍

即从x1点spfa一遍之后，从y1点倒序寻找，对于所有的y1的相邻节点v，若dist[v] + len(v,y1) = dist[y1]，则边(v,y1)在最短路上，点v在最短路上

然后把v点推入队列，用bfs的方式对于所有的“在最短路上的点”都进行这样的操作，这样就求出了所有在x1->y1的最短路上的边，可以用邻接矩阵保存，方便查找

然后从x2点spfa之后，用相同的方式找x2->y2的最短路径上的所有边，如果有边(u,v)同时在x1->y1和x2->y2的最短路上出现了

那么在新的“最短路图”中构造一条弧<u,v>，其中dist[u] < dist[v]，这里的dist可以取“从x1开始spfa的dist”或者是“从x2开始spfa的dist”中的任意一个，但是肯定不能两个混着用啦。。。

说的不是很清楚，详见代码，重复代码比较多，所以看起来比较长，实际上还是很好理解的。








```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;
const int MAXN = 1502, MAXM = 1125000;
const int INF = 0x3f3f3f3f;
int n,m,x1,my_y1,x2,y2;
struct Myque {
    int arr[MAXN], head, tail;
    Myque() { clear(); }
    void clear() { head = tail = 0; }
    void push_back( int num ) { arr[tail] = num; if( ++tail == MAXN ) tail = 0; }
    void push_front( int num ) { if( --head == -1 ) head = MAXN-1; arr[head] = num; }
    void pop() { if( ++head == MAXN ) head = 0; }
    int front() { return arr[head]; }
    bool empty() { return head == tail; }
};
struct Graph {
    int head[MAXN], to[MAXM<<1], nxt[MAXM<<1], w[MAXM<<1], idx;
    Graph() { idx = 0; memset( head, -1, sizeof(head) ); }
    void addedge( int u, int v, int l ) {
        to[idx] = v; w[idx] = l; nxt[idx] = head[u]; head[u] = idx; ++idx;
    }
    bool inq[MAXN]; Myque q; int dist[MAXN];
    void spfa( int s ) {
        memset( dist, 0x3f, sizeof(dist) ); dist[s] = 0;
        memset( inq, false, sizeof(inq) ); inq[s] = true; q.push_back(s);
        while( !q.empty() ) {
            int u = q.front(); q.pop(); inq[u] = false;
            for( int e = head[u]; ~e; e = nxt[e] ) {
                int v = to[e];
                if( dist[v] > dist[u] + w[e] ) {
                    dist[v] = dist[u] + w[e];
                    if( !inq[v] ) { inq[v] = true;
                        if( dist[v] <= q.front() ) q.push_front(v);
                        else q.push_back(v);
                    }
                }
            }
        }
    }
}origin,sp;
namespace Toposort {
    int in[MAXN]; Myque q; Myque rstq;
    void init() { memset( in, 0, sizeof(in) ); }
    void topo( const Graph &g ) {
        for( int i = 1; i <= n; ++i ) if( !in[i] ) q.push_back(i);
        while( !q.empty() ) {
            int u = q.front(); q.pop(); rstq.push_back(u);
            for( int e = g.head[u]; ~e; e = g.nxt[e] ) {
                int v = g.to[e];
                if( --in[v] == 0 ) q.push_back(v);
            }
        }
    }
    int dist[MAXN];
    int dpf( const Graph &g ) {
        memset( dist, 0, sizeof(dist) ); int ans = 0;
        while( !rstq.empty() ) {
            int u = rstq.front(); rstq.pop(); ans = max( ans, dist[u] );
            for( int e = g.head[u]; ~e; e = g.nxt[e] ) {
                int v = g.to[e], w = g.w[e];
                dist[v] = max( dist[v], dist[u] + w );
            }
        }
        return ans;
    }
}
using Toposort::in;
using Toposort::topo;
using Toposort::dpf;
namespace MarkPath {
    int adj[MAXN][MAXN]; Myque q; bool vis[MAXN];
    void mark_path( const Graph &g, int t ) {
        memset( adj, 0, sizeof(adj) ); q.push_back(t);
        memset( vis, false, sizeof(vis) ); vis[t] = true;
        while( !q.empty() ) {
            int u = q.front(); q.pop();
            for( int e = g.head[u]; ~e; e = g.nxt[e] ) {
                int v = g.to[e], w = g.w[e];
                if( g.dist[v] == g.dist[u] - w ) {
                    adj[u][v] = adj[v][u] = w;
                    if( !vis[v] ) {
                        vis[v] = true; q.push_back(v);
                    }
                }
            }
        }
    }
    void mark_path_2( const Graph &g, int t, Graph &obj ) {
        memset( vis, false, sizeof(vis) ); vis[t] = true;
        q.push_back(t); Toposort::init();
        while( !q.empty() ) {
            int u = q.front(); q.pop();
            for( int e = g.head[u]; ~e; e = g.nxt[e] ) {
                int v = g.to[e], w = g.w[e];
                if( g.dist[v] == g.dist[u] - w ) {
                    if( !vis[v] ) {
                        vis[v] = true; q.push_back(v);
                    }
                    if( adj[v][u] ) {
                        obj.addedge(v,u,w); in[u]++;
                    }
                }
            }
        }
    }
}
using MarkPath::mark_path;
using MarkPath::adj;
using MarkPath::mark_path_2;
int main() {
    scanf( "%d%d%d%d%d%d", &n, &m, &x1, &my_y1, &x2, &y2 );
    for( int i = 0; i < m; ++i ) {
        int u,v,l; scanf( "%d%d%d", &u, &v, &l );
        origin.addedge(u,v,l); origin.addedge(v,u,l);
    }
    origin.spfa(x1); mark_path(origin,my_y1);
    origin.spfa(x2); mark_path_2(origin,y2,sp);
    topo(sp); printf( "%d\n", dpf(sp) );
    return 0;
}

```

---

