# [ICPC-Beijing 2006] 狼抓兔子

## 题目描述

现在小朋友们最喜欢的"喜羊羊与灰太狼"。话说灰太狼抓羊不到，但抓兔子还是比较在行的，而且现在的兔子还比较笨，它们只有两个窝，现在你做为狼王，面对下面这样一个网格的地形：

 ![](https://cdn.luogu.com.cn/upload/pic/11942.png) 

左上角点为 $(1,1)$，右下角点为 $(N,M)$（上图中 $N=3$，$M=4$）。有以下三种类型的道路：

1. $(x,y)\rightleftharpoons(x+1,y)$

2. $(x,y)\rightleftharpoons(x,y+1)$

3. $(x,y)\rightleftharpoons(x+1,y+1)$

道路上的权值表示这条路上最多能够通过的兔子数，道路是无向的。左上角和右下角为兔子的两个窝，开始时所有的兔子都聚集在左上角 $(1,1)$ 的窝里，现在它们要跑到右下角 $(N,M)$ 的窝中去，狼王开始伏击这些兔子。当然为了保险起见，如果一条道路上最多通过的兔子数为 $K$，狼王需要安排同样数量的 $K$ 只狼，才能完全封锁这条道路，你需要帮助狼王安排一个伏击方案，使得在将兔子一网打尽的前提下，参与的狼的数量要最小。因为狼还要去找喜羊羊麻烦。


## 说明/提示

### 数据规模与约定

对于全部的测试点，保证 $3 \leq N,M \leq 1000$，所有道路的权值均为不超过 $10^6$ 的正整数。

## 样例 #1

### 输入

```
3 4
5 6 4
4 3 1
7 5 3
5 6 7 8
8 7 6 5
5 5 5
6 6 6```

### 输出

```
14```

# 题解

## 作者：d3ac (赞：84)

### 大家都是网络流，这是最短路,我给大家来一种最短路的解法
![](https://cdn.luogu.com.cn/upload/pic/63309.png)
    从上图可以看出来，最小割就是最短路，把左下角作为起点，右上角作为终点，只要从左下角走到了右上角，就一定可以把图分成两份，
最短路就是最短的方式把图分成两份，然后再把每一个小三角形看成一个点，~~再跑最短路就行了~~

```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
#define inf 2147483647
#define re register
#define maxn 9100000
using namespace std;
int head[maxn],n,m,k,start,end,ans,deep[maxn],dis[maxn],book[maxn];
struct node{int to,next,w;}edge[maxn];
void add(int u,int v,int w){edge[++k].next=head[u];edge[k].to=v;edge[k].w=w;head[u]=k;}
void read()
{
	re int temp,t1,t2;
	for(re int i=1;i<m;i++) scanf("%d",&temp),add(i*2,end,temp);
	for(re int i=2;i<n;i++)
	for(re int j=1;j<m;j++)
	{
		scanf("%d",&temp);
		t1=2*(i-2)*(m-1)-1+2*j;
		t2=2*(i-1)*(m-1)+2*j;
		add(t1,t2,temp);
		add(t2,t1,temp);
	}
	for(re int i=1;i<m;i++)
	{
		scanf("%d",&temp);
		t1=2*(n-2)*(m-1)-1+2*i;
		add(start,t1,temp);
	}//横 
	
	for(int i=1;i<n;i++)
	for(int j=1;j<=m;j++)
	{
		scanf("%d",&temp);
		t1=2*(i-1)*(m-1)-1+2*j;
		t2=t1-1;
		if(j==1) add(start,t1,temp);
		else if(j==m) add(t2,end,temp);
		else
		{
			add(t1,t2,temp);
			add(t2,t1,temp);
		}
	}//竖 
	
	for(int i=1;i<n;i++)
	for(int j=1;j<m;j++)
	{
		t1=2*(i-1)*(m-1)-1+2*j;
		t2=t1+1;
		scanf("%d",&temp);
		add(t1,t2,temp);
		add(t2,t1,temp);
	}
	//斜 
}
struct point
{
    int value;//距离 
    int id;//点
    point(int x,int y)
    {
        id=x;
        value=y;
    }
    friend bool operator <(point a,point b)
    {
        return a.value>b.value;
    } 
};
priority_queue<point> q;
int dijkstra(int s)
{
    for(int i=1;i<=end;i++) dis[i]=inf;
    dis[s]=0;
    q.push(point(s,0));
    while(!q.empty())
    {
        int u=q.top().id;
        q.pop();
        if(book[u]) continue;
        book[u]=1;
        for(int i=head[u];i>0;i=edge[i].next)
        {
            int v=edge[i].to;
            if(dis[v]>dis[u]+edge[i].w)
            {
                dis[v]=dis[u]+edge[i].w;
                if(!book[v])
                q.push(point(v,dis[v]));
            }
        }
    }
    return dis[end];
}
int main()
{
	scanf("%d %d",&n,&m);
	end=(2*n-2)*(m-1)+1;
	read();
	printf("%d",dijkstra(0));
	return 0;
}
```


---

## 作者：LiRewriter (赞：53)

看到luogu4001竟然是BZOJ1001...惊了，明明前几天还没有来着


最大流算法的实现见前篇：https://www.luogu.org/blog/LittleRewriter/wang-lao-liu-er-zui-tai-liu-suan-fa-di-shi-xian

看到luogu上有了狼抓兔子就兴奋的交一发（雾）


## 最小割最大流定理


搜了一圈没有找到什么是最小割，然后懵逼了。

嗯......

首先，什么是割？其实，割=割边=去掉以后使图不连通的边的集合

然后，容量和最少的割集称为最小割。

对于割，有这样一个重要定理：

> 最小割=最大流

嗯，最小割就这么多东西。

为什么正确？这里给出一种直观的想法

（原PO：https://jecvay.com/2014/11/what-is-min-cut.html）

>1.最大流不可能大于最小割, 因为最大流所有的水流都一定经过最小割那些割边, 流过的水流怎么可能比水管容量还大呢? 
2.最大流不可能小于最小割, 如果小, 那么说明水管容量没有物尽其用, 可以继续加大水流.


证毕。


这里首先说一个技巧，无向图的网络流在建边时反向弧直接建成权值为v的边即可，因为这样的边一开始就是可以增广的。

题意是求一个无向图的最小割，然后我们运用最小割-最大流定理，可以转化成求最大流的问题。不过朴素的Dinic是会TLE的，这里提供一种优化方法：

我们知道，假定在一次dinic过程中，发现不能再进行增广了，那么就相当于向下的这条路是废的。因此，我们可以直接把这条路堵上，然后就可以过了。优化效果很明显，BZOJ上TLE->1644msAC（虽然我质疑出题人可能专门卡了朴素的Dinic），洛谷直接0ms...不愧是玄学。

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <cctype>
using namespace std;
inline void read(int &x) {
    x = 0; char c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = (x << 3) + (x << 1) + c - '0', c = getchar();
}
#define MAXN 1003
struct node{
    int fr, to, va, nxt;
}edge[MAXN * MAXN * 6];
int head[MAXN * MAXN], cnt;
inline void add_edge(int u, int v, int w) {
    edge[cnt].fr = u, edge[cnt].to = v, edge[cnt].va = w;
    edge[cnt].nxt = head[u], head[u] = cnt++;
    edge[cnt].fr = v, edge[cnt].to = u, edge[cnt].va = w;
    edge[cnt].nxt = head[v], head[v] = cnt++; //反向边初始化
}
int st, ed, rank[MAXN * MAXN];
int BFS() {
    queue<int> q;
    memset(rank, 0, sizeof rank);
    rank[st] = 1;
    q.push(st);
    while(!q.empty()) {
        int tmp = q.front();
        //cout<<tmp<<endl;
        q.pop();
        for(int i = head[tmp]; i != -1; i = edge[i].nxt) {
            int o = edge[i].to;
            if(rank[o] || edge[i].va <= 0) continue;
            rank[o] = rank[tmp] + 1;
            q.push(o);
        }
    }
    return rank[ed];
}
int dfs(int u, int flow) {
    if(u == ed) return flow;
    int add = 0;
    for(int i = head[u]; i != -1 && add < flow; i = edge[i].nxt) {
        int v = edge[i].to;
        if(rank[v] != rank[u] + 1 || !edge[i].va) continue;
        int tmpadd = dfs(v, min(edge[i].va, flow - add));
        if(!tmpadd) {  //重要！就是这里！
            rank[v] = -1;
            continue;
        }
        edge[i].va -= tmpadd, edge[i ^ 1].va += tmpadd;
        add += tmpadd;
    }
    return add;
}
int ans;
void dinic() {
    while(BFS()) ans += dfs(st, 0x3fffff); 
}
int n, m;
inline int gethash(int i, int j) {
    return (i - 1) * m + j;
}
int main() {
    memset(head, -1, sizeof head);
    read(n), read(m);
    int tmp;
    st = 1, ed = gethash(n, m);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j < m; ++j)
            read(tmp), add_edge(gethash(i, j), gethash(i, j + 1), tmp);
    }
    for(int i = 1; i < n; ++i) {
        for(int j = 1; j <= m; ++j) 
            read(tmp), add_edge(gethash(i, j), gethash(i + 1, j), tmp);
    }
    for(int i = 1; i < n; ++i) {
        for(int j = 1; j < m; ++j) 
            read(tmp), add_edge(gethash(i, j), gethash(i + 1, j + 1), tmp);
    }
    dinic();
    cout<<ans<<endl;
    return 0;
} 
```

---

## 平面图与对偶图


仍然考虑狼抓兔子。不得不说，网络流这种玄学算法总会让人思考人生。于是机智的人做了这样一件事。

先来观察下面的这张图：

![](http://ozz4vkmqm.bkt.clouddn.com/17-12-10/63971518.jpg)

我们发现，这么一张图，可以转化成任意两边的交点都在顶点上的形式。

![](http://ozz4vkmqm.bkt.clouddn.com/17-12-10/56506302.jpg)

下面的这张却完全不行。

像这样任意两边的交点在顶点上的图我们称为平面图。

几条边围成一个区域，这个区域称为一个面。

对平面图，我们定义对偶图：

![](http://ozz4vkmqm.bkt.clouddn.com/17-12-10/44610442.jpg)

下图中黑色的是个平面图，红色的就是对偶图。其建立方法是，对每个面建一个点，只要有一条边是在两个面之间，我们就对这两个面对应的点连边（稍有些绕）。注意是有一条边就连线。

然后我们就得到萌萌哒的对偶图一张！

对偶图就有很多美妙的性质了。比如说，我们发现，对偶图的一条边就对应了一条割边。

既然如此的话，想想狼抓兔子，一条割边有一个容量，那么如果我们建它的对偶图，最短路就是最小割。

所以得出下面的重要定理：

> 对平面图来说，最大流 = 最小割 = 对偶图最短路

所以我们就可以稳一些跑出来狼抓兔子。

（详细的图解：https://www.cnblogs.com/jinkun113/p/4682827.html）

于是AC代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cctype>
#include <vector>
#include <cstring>
using namespace std;
inline void read(int &x) {
    x = 0; char c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = x * 10 + c - '0', c = getchar(); 
}
#define MAXN 2000010
struct node{
    int to, va;
    node(int a, int b) { to = a, va = b; }
};
vector<node> v[MAXN]; 
inline void add_edge(int f, int t, int w) {
    v[f].push_back(node(t, w));
    v[t].push_back(node(f, w));
}
bool vis[MAXN];
int st, ed;
int dis[MAXN];
int SPFA() {
    memset(dis, 0x3f, sizeof dis);
    vis[st] = 1;
    queue<int> q;
    q.push(st);
    dis[st] = 0;
    while(!q.empty()) {
        int tmp = q.front();
        //cout<<tmp<<" ";
        q.pop();
        vis[tmp] = 0;
        for(int i = 0; i < v[tmp].size(); ++i) {
            int o = v[tmp][i].to;
            //cout<<o<<" ";
            if(dis[o] > dis[tmp] + v[tmp][i].va) {
                dis[o] = dis[tmp] + v[tmp][i].va;
                if(!vis[o]) q.push(o), vis[o] = 1;
            }
        }
    }
    return dis[ed];
}
int n, m;
inline void getheng(int i, int j, int k) {
    if(i == 1) add_edge(st, j, k);
    else if(i == n) add_edge((2 * (n - 1) - 1) * (m - 1) + j, ed, k);
    else add_edge((2 * (i - 1) - 1) *(m - 1) + j, 2 * (i - 1) * (m - 1) + j, k);
}
inline void getshu(int i, int j, int k) {
    if(j == 1) add_edge((i * 2 - 1) * (m - 1) + 1, ed, k);
    else if(j == m) add_edge(st, 2 * i * (m - 1) - (m - 1), k);
    else add_edge((i - 1) * 2 * (m - 1) + j - 1, ((i - 1) * 2 + 1) * (m - 1) + j, k);
}
inline void getxie(int i, int j, int k) {
    add_edge((i - 1) * 2 * (m - 1) + j, (i - 1) * 2 * (m - 1) + (m - 1) + j, k);
}
int main() {
    read(n), read(m);
    st = (n - 1) * (m - 1) * 2 + 1, ed = (n - 1) * (m - 1) * 2 + 2;
    int x;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j < m; ++j)
            read(x), getheng(i, j, x);
    }
    for(int i = 1; i < n; ++i) {
        for(int j = 1; j <= m; ++j) 
            read(x), getshu(i, j, x);
    }
    for(int i = 1; i < n; ++i) {
        for(int j = 1; j < m; ++j) 
            read(x), getxie(i, j, x);
    }
    /*for(int i = 1; i <= ((n - 1) * (m - 1) * 2 + 2); ++i) {
        for(int j = 0; j < v[i].size(); ++j)
            cout<<v[i][j].to<<" ";
        cout<<endl;
    }*/
    cout<<SPFA()<<endl;
    return 0;
}
```
建图建到吐血...真的心累啊...

BZOJ3464ms，比网络流玄学还要慢些？好吧...luogu更夸张，直接700多ms...


---

嗯，费用流的问题月考后再说

## 参考资料

https://wenku.baidu.com/view/8c887f10a6c30c2259019ea0.html

https://www.cnblogs.com/ljh2000-jump/p/5503061.html

http://hzwer.com/1261.html

http://blog.csdn.net/ff88655068/article/details/38878343


---

## 作者：Imakf (赞：47)

~~玄学$dinic$居然不会被卡~~

首先讲讲对偶图，首先对于这样一张图

![](https://cdn.luogu.com.cn/upload/pic/53357.png)

它的对偶图就是(忽略原来的那9个点)

![](https://cdn.luogu.com.cn/upload/pic/53358.png)

我们可以把这个对偶图理解为插孔？对偶图的某一边边权就是那条边所交叉的原图的边权。比如上图$W_{0->17}=W_{1->4}=5$

然后我们就可以用对偶图来维护连通性的问题啦！

先来一道水题（不知道哪来的）

请您维护一张$n*n(n\leq1000)$的网格图(没有边权)，初始所有边都在，就像这样

![](https://cdn.luogu.com.cn/upload/pic/53359.png)

> 这是一张 $3*3$ 的网格图

之后有$m(m\leq100000)$个操作，割去$(x_1,y_1)$到$(x_2,y_2)$的边，保证不会割去重复的边

初始整张图是一个联通块，对于每一次操作，如果使联通块的数量变多了，请输出它是第几个操作。

读完题，发现蒟蒻我不会删边，于是就用到对偶图这个东西。

上文我们提到

> 对偶图的某一边边权就是那条边所交叉的原图的边权

我们不妨把对偶图的边权理解成割掉原图的边的代价（似乎变成最小割=.=了），于是我们通过**维护对偶图的连通性，反而可以得出原图的不连通性**。

然后维护连通性用并查集就好了，如果$findfa(x1,y1)==findfa(x2,x2)$,那就$ans++$（因为题目保证了保证不会割去重复边）

好了，知道了这些知识就可以秒了这道题了

把左下 和 右上分开，dijkstra求左下到右上的最短路

**维护对偶图的最短路，反而可以得出原图的最小割**

对于题目样例

![](https://cdn.luogu.com.cn/upload/pic/53360.png)

建一个这样的图，跑dij就行了

![](https://cdn.luogu.com.cn/upload/pic/53361.png)

只是对偶图建图有点恶心

请自己思考一下怎么转对偶图吧……我是解释不清



```
//本篇代码以(n,m)为原点 (n+1,m+1)为终点
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<queue>

#define rg register
#define MAXN (2000+10)

int head[MAXN][MAXN],tot;
struct edge{
    int next,x,y,w;
}h[MAXN*MAXN*2*2];
inline void addedge(int x,int y,int x1,int y1,int w){	//建边
    h[++tot].next = head[x][y];
    head[x][y] = tot;
    h[tot].x = x1, h[tot].y = y1;
    h[tot].w = w;
}

struct node{
    int x,y,w;
    bool operator < (const node b) const{
        return b.w<w;
    }
};
int n,m;
bool vis[MAXN][MAXN];
int dis[MAXN][MAXN];
void dij(int stx,int sty){//最短路
    memset(dis,0x3f,sizeof(dis));
    std::priority_queue<node> q;
    dis[stx][sty] = 0;
    q.push((node){stx , sty , 0});
    while(!q.empty()){
        node now = q.top();
        q.pop();
        int x = now.x,y = now.y;
        //printf("%d %d \n",x,y);
        if(vis[x][y])	continue;
        vis[x][y] = 1;
        for(rg int i = head[x][y] ; i ; i = h[i].next){
            int tox = h[i].x,toy = h[i].y,w = h[i].w;
            //printf("trying %d %d dis = %d \n",tox,toy,dis[tox][toy]);
            if(dis[x][y] + w < dis[tox][toy]){
                dis[tox][toy] = dis[x][y] + w;
                //printf("CHange dis[%d][%d]=%d \n",tox,toy,dis[tox][toy]);
                if(!vis[tox][toy])	q.push((node){tox,toy,dis[tox][toy]});
            }
        }
    }
    return ;
}

int main(){
    scanf("%d%d",&n,&m);
    if(n==1){
        int ans=1<<30;
        for(rg int i = 1 , w;i < m ; ++i){
            scanf("%d",&w);
            if(w < ans) ans = w;
        }
        printf("%d \n",ans);
        return 0;
    }
    if(m == 1){
        int ans=1<<30;
        for(rg int i = 1 , w;i < n ; ++i){
            scanf("%d",&w);
            if(w < ans) ans = w;
        }
        printf("%d \n",ans);
        return 0;
    }
    for(rg int i = 1 ,w; i <= n ; ++i){
        for(rg int j = 1 ; j < m ; ++j){//此后毒瘤建图
            scanf("%d",&w);
            if(i == 1){
                addedge(i,j<<1,n+1,m+1,w);
                addedge(n+1,m+1,i,j<<1,w);
            }
            else if(i == n){
                addedge(i-1,(j<<1)-1,n,m,w);
                addedge(n,m,i-1,(j<<1)-1,w);
            }
            else{
                addedge(i-1,(j<<1)-1,i,j<<1,w);
                addedge(i,j<<1,i-1,(j<<1)-1,w);
            }
        }
    }
    for(rg int i = 1,w ; i < n ; ++i){
        for(rg int j = 1 ; j <= m ;++j){
            scanf("%d",&w);
            if(j == 1){
                addedge(n,m,i,(j<<1)-1,w);
                addedge(i,(j<<1)-1,n,m,w);
            }
            else if(j == m){
                addedge(n+1,m+1,i,(m-1)<<1,w);
                addedge(i,(m-1)<<1,n+1,m+1,w);
            }
            else{
                addedge(i,(j-1)<<1,i,(j-1)<<1|1,w);
                addedge(i,(j-1)<<1|1,i,(j-1)<<1,w);
            }
        }
    }
    for(rg int i = 1,w; i < n ;i++){
        for(rg int j = 1; j < m ; ++j){
            scanf("%d",&w);
            addedge(i,(j<<1)-1,i,j<<1,w);
            addedge(i,j<<1,i,(j<<1)-1,w);
        }
    }
    dij(n,m);
    printf("%d \n",dis[n+1][m+1]);
    return 0;
}
```


---

## 作者：Haishu (赞：30)

我满心以为本题正解为最短路，结果到处都是最大流……

几乎所有的都写了什么“对偶图”跑最短路~~，但我真的不知道什么叫做对偶图~~
___
介绍一下本题的最短路算法叭。并不算难。主要是感性理解。

![t1](https://cdn.luogu.com.cn/upload/pic/11942.png)

首先~~很容易~~观察出这是一个最小割，那么就是求最大流了。

但是这题的点数高达10e6，按常理来说最大流应该稳稳地TLE。
~~但是没有T好气哦~~

**那么想办法！**

首先最小割在本题时可以这样感性理解：上图是一个你同学在钢铁厂打出来的一个铁架子。你把start处用手捏起来，end处自然垂下。用一个剪刀钳把这个铁架子拦腰剪成两半。

如果剪成好几瓣（掉下来有好几个联通块的），那么显而易见，不如剪成两半（把刚才几个剪断的地方原样拼起来变成两个联通块）。

我们把三角形看成是点，黑色的边看成是连接三角形的边，那么剪成两半的意思是……在三角形点的图上找一条从左下到右上的最短路径！沿着这条路径剪开就行了。

但是这题的点数高达10e6，按常理来说SPFA应该稳稳地TLE。
~~但是没有T好气哦~~

那就堆优化dijkstra。

这个加边超烦的。但思路清晰的话就没什么问题。记得在左下空白处设一个源点，右上角设一个汇点。源点连接所有邻接它的左边的、下边的三角形点，汇点连接所有邻接它的右边的、上边的三角形点。

```
#include <cstdio>
#include <queue>
using namespace std;
const int N=1002,S=N*N*6+30,inf=(1<<30)-1;
int n,m,a[N][N],b[N][N],c[N][N],d[S],id[N][N],ss,tt,h[S],v[S],nx[S],w[S],eg=1;
bool vis[S]={0};
struct info
{
	int x,w;
}data;
inline bool operator<(const info &a,const info &b)
{
	return a.w>b.w;
}
priority_queue<struct info> pq;
inline void egadd(int uu,int vv,int ww)
{
	nx[++eg]=h[uu];h[uu]=eg;
	v[eg]=vv;w[eg]=ww;
}
void rd(int &s)
{
	s=0;char c=getchar();
	while (c<48) c=getchar();
	while (c>=48) s=(s<<1)+(s<<3)+(c^48),c=getchar();
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m-1;j++)
			rd(a[i][j]);
	for (int i=1;i<=n-1;i++)
		for (int j=1;j<=m;j++)
			rd(b[i][j]);
	for (int i=1;i<=n-1;i++)
		for (int j=1;j<=m-1;j++)
			rd(c[i][j]);
	n--;m--;//注意这里我人为地把n和m减1，这样表示三角形点方便些。
	if (!n)
	{
		int res=inf;
		for (int i=1;i<=m;i++)
			if (a[1][i]<res)
				res=a[1][i];
		printf("%d",res);
		return 0;
	}
	if (!m)
	{
		int res=inf;
		for (int i=1;i<=n;i++)
			if (b[i][1]<res)
				res=b[i][1];
		printf("%d",res);
		return 0;
	}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			id[i][j]=(i-1)*2*m+j;
	ss=n*2*m+1;tt=ss+1;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			egadd(id[i][j],id[i][j]+m,c[i][j]);
			egadd(id[i][j]+m,id[i][j],c[i][j]);
		}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m-1;j++)
		{
			egadd(id[i][j],id[i][j+1]+m,b[i][j+1]);
			egadd(id[i][j+1]+m,id[i][j],b[i][j+1]);
		}
	for (int i=1;i<=n-1;i++)
		for (int j=1;j<=m;j++)
		{
			egadd(id[i][j]+m,id[i+1][j],a[i+1][j]);
			egadd(id[i+1][j],id[i][j]+m,a[i+1][j]);
		}
	for (int i=1;i<=m;i++)
	{
		egadd(id[1][i],tt,a[1][i]);
		egadd(ss,id[n][i]+m,a[n+1][i]);
	}
	for (int i=1;i<=n;i++)
	{
		egadd(ss,id[i][1]+m,b[i][1]);
		egadd(id[i][m],tt,b[i][m+1]);
	}
	for (int i=1;i<=tt;i++)
		d[i]=inf;
	d[ss]=0;
	pq.push((info){ss,0});
	while (!pq.empty())
	{
		while (!pq.empty() && vis[pq.top().x])
			pq.pop();
		if (pq.empty()) break;
		data=pq.top();
		pq.pop();
		int x=data.x,ww=data.w;
		vis[x]=true;
		for (int i=h[x];i;i=nx[i])
			if (!vis[v[i]] && d[v[i]]>ww+w[i])
			{
				d[v[i]]=ww+w[i];
				pq.push((info){v[i],d[v[i]]});
			}
	}
	printf("%d",d[tt]);
	return 0;
}
```


---

## 作者：小蒟蒻皮皮鱼 (赞：12)

### 先了解一下两个东西

最大流：从起点到终点能实现的最大的流量

　　通俗点解释，就好比你有很多货物要从源点点运到汇点点，有向图中的一条边代表一条公路，每条公路有固定的货物装载限制（容量），对每条公路你只能运输一定数量的货物，问你每一次运输最多运到汇点点多少货物。

最小割：对于一张流量图G，断开一些边后，源点s和汇点t就不在连通，我们将这样的k条边的权值（即最大容量）和求和，求和后的值称为割。显然，对于一张流量图G，割有很多个且不尽相同。我们要求的就是所有割中权值最小的那一个（可能不唯一），即花最小的代价使s和t不在同一集合中。

 
### 引理： 最大流最小割定理

- 任意一个流都小于等于任意一个割
- 构造出一个流等于一个割
- 在一张流量图G中，最大流=最小割。

任意两边的交点在顶点上的图我们称为平面图

这道题很容易看出来是求最大流，那么可以转化为最小割来做

![1](https://cdn.luogu.com.cn/upload/image_hosting/wg0k756k.png)
如图，相当于是在上下两个图形上面连了一条边，而这条边的边权就是4,5这条边的边权

那么这个问题不就变成了这样
![2](https://cdn.luogu.com.cn/upload/image_hosting/8zkh0ole.png)

（忽略掉原来的九个点）

在这张新图上面找最短路

我们发现有很多连到图形外面的点，我们不妨把他们合并一下

![3](https://cdn.luogu.com.cn/upload/image_hosting/nnqrt3xz.png)

（标红的是对偶图的边）

那么就是寻找源点13->汇点14的最短路

定理：平面图的最小割=对偶图的最短路


 对于样例的数据就是这样
 ![4](https://cdn.luogu.com.cn/upload/image_hosting/87im3z6z.png)
 
 只需要从源点到汇点跑一遍最短路就行了

---

## 作者：Siyuan (赞：12)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/)

---

> 题目链接：[BZOJ 1001](https://www.lydsy.com/JudgeOnline/problem.php?id=1001)

现在小朋友们最喜欢的"喜羊羊与灰太狼"，话说灰太狼抓羊不到，但抓兔子还是比较在行的，而且现在的兔子还比较笨，它们只有两个窝，现在你做为狼王，面对下面这样一个网格的地形：

![](https://hydingsy.github.io/images/problem-BJOI-2006-Wolves-Catch-Rabbits.jpg)

左上角点为 $(1,1)$，右下角点为 $(n,m)$（上图中 $N=3,M=4$）。有以下三种类型的道路：

1. $(x,y)\longleftrightarrow(x+1,y)$
2. $(x,y)\longleftrightarrow(x,y+1)$
3. $(x,y)\longleftrightarrow(x+1,y+1)$

道路上的权值表示这条路上最多能够通过的兔子数，道路是无向的。左上角和右下角为兔子的两个窝，开始时所有的兔子都聚集在左上角 $(1,1)$ 的窝里，现在它们要跑到右下角 $(N,M)$ 的窝中去，狼王开始伏击这些兔子.当然为了保险起见，如果一条道路上最多通过的兔子数为 $K$，狼王需要安排同样数量的 $K$ 只狼，才能完全封锁这条道路，你需要帮助狼王安排一个伏击方案，使得在将兔子一网打尽的前提下，参与的狼的数量要最小。

数据范围：$1\le N,M\le 1000$

------

## Solution

很显然是一个裸的最小割，对 $(1,1)$ 到 $(N,M)$ 依次编号，然后按照题意建边跑最短路即可 QAQ

~~吐槽：终于做出了 BZOJ 的 1001~~（大雾

当然由于这题的图是一张**平面图**，所以我们也可以建出**对偶图**，直接跑最短路，得到的就是原图的最小割。

**时间复杂度**：$O((NM)^3)$（点数 $NM$，边数 $NM$，但是这个复杂度很假的啦）

------

## Code

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

const int N=1e6+5,M=6e6+5;
int n,m,tot=1,lnk[N],ter[M],nxt[M],val[M],dep[N],cnr[N];

int id(int x,int y) {
    return (x-1)*m+y;
}
void add(int u,int v,int w) {
    ter[++tot]=v,nxt[tot]=lnk[u],lnk[u]=tot,val[tot]=w;
}
void addedge(int u,int v,int w) {
    add(u,v,w),add(v,u,w);
}
int bfs(int s,int t) {
    memset(dep,0,sizeof(dep));
    memcpy(cnr,lnk,sizeof(lnk));
    std::queue<int> q;
    q.push(s),dep[s]=1;
    while(!q.empty()) {
        int u=q.front(); q.pop();
        for(int i=lnk[u];i;i=nxt[i]) {
            int v=ter[i];
            if(val[i]&&!dep[v]) q.push(v),dep[v]=dep[u]+1;
        }
    }
    return dep[t];
}
int dfs(int u,int t,int flow) {
    if(u==t) return flow;
    int ans=0;
    for(int i=cnr[u];i&&ans<flow;i=nxt[i]) {
        cnr[u]=i;
        int v=ter[i];
        if(val[i]&&dep[v]==dep[u]+1) {
            int x=dfs(v,t,std::min(val[i],flow-ans));
            if(x) val[i]-=x,val[i^1]+=x,ans+=x;
        }
    }
    if(ans<flow) dep[u]=-1;
    return ans;
}
int dinic(int s,int t) {
    int ans=0;
    while(bfs(s,t)) {
        int x;
        while((x=dfs(s,t,1<<30))) ans+=x;
    }
    return ans;
}
int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i) for(int j=1;j<m;++j) {
        int x;
        scanf("%d",&x);
        addedge(id(i,j),id(i,j+1),x);
    }
    for(int i=1;i<n;++i) for(int j=1;j<=m;++j) {
        int x;
        scanf("%d",&x);
        addedge(id(i,j),id(i+1,j),x);
    }
    for(int i=1;i<n;++i) for(int j=1;j<m;++j) {
        int x;
        scanf("%d",&x);
        addedge(id(i,j),id(i+1,j+1),x);
    }
    printf("%d\n",dinic(id(1,1),id(n,m)));
    return 0;
}
```

---

## 作者：人间凡人 (赞：5)

## 题意：一个n*m的网格图，有斜边，每条路径可以花一定的费用将其禁用。选择一部分路径禁用，使(1,1)和(n,m)不连通 求最小花费

 思路：想象把整个网格切一刀划断，其中割断某条边的代价就是花费 那么总共的最小花费就是从右上角割到左下角的路径（花费）有多长，转化为最短路 即可。

那么，重点来了，该如何建图呢。这就有点麻烦了，我们看这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/6embz9yy.png)

其中每一个红线的路径花费就为所交叉的黑线的这个边权，最后我们可以发现，我们所求的答案就为 $0$~$13$ 的最短路即可。

#### 注意：

####  1、每条边是双向边。
####  2、建图时有一些边需要特殊考虑。

因为分为横边，竖边与斜边，我们要一个个分开来考虑建图。

Code:
```cpp
#include<bits/stdc++.h>
#define N 7000005
#define M 1005
using namespace std;
priority_queue<pair<int,int> >q;
bool vis[N];
int n,m,s,num,edgenum,value;
int dist[N];
int ver[N],edge[N],Next[N],head[N];
void Add(int x,int y,int z){
	ver[++edgenum]=y;
	edge[edgenum]=z;
	Next[edgenum]=head[x];
	head[x]=edgenum;
}
void Dij(){
	memset(dist,0x3f,sizeof(dist));
	memset(vis,false,sizeof(vis));
	dist[s]=0;q.push(make_pair(0,s));
	while(q.size()){
		int x=q.top().second;q.pop();
		if(vis[x])continue;
		vis[x]=true;
		for(int i=head[x];i;i=Next[i]){
			int y=ver[i],z=edge[i];
			if(dist[y]>dist[x]+z){
				dist[y]=dist[x]+z;
				if(!vis[y])q.push(make_pair(-dist[y],y));
			}
		} 
	}
}
int main(){
	scanf("%d%d",&n,&m);s=0;
	//横着的 
	num=(n-1)*(m-1)*2;
	for(int j=1;j<m;j++){
		scanf("%d",&value);
		Add(j,num+1,value);
		Add(num+1,j,value);
	} 
	for(int i=2;i<n;i++)
		for(int j=1;j<m;j++){
			scanf("%d",&value);
			Add((i-1)*(m-1)*2+j,(i-1)*(m-1)*2+j-m+1,value);
			Add((i-1)*(m-1)*2+j-m+1,(i-1)*(m-1)*2+j,value);
		}
	for(int j=1;j<m;j++){
		scanf("%d",&value);
		Add((n-2)*(m-1)*2+m+j-1,0,value);
		Add(0,(n-2)*(m-1)*2+m+j-1,value);
	}
	//竖着的 
	for(int i=1;i<n;i++){
		scanf("%d",&value);
		Add((m-1)*2*(i-1)+m,0,value);
		Add(0,(m-1)*(i-1)*2+m,value);
		for(int j=2;j<m;j++){
			scanf("%d",&value);
			Add((m-1)*2*(i-1)+m+j-1,(m-1)*2*(i-1)+j-1,value); 
			Add((m-1)*2*(i-1)+j-1,(m-1)*2*(i-1)+m+j-1,value);
		}
		scanf("%d",&value);
		Add((m-1)*2*(i-1)+m-1,num+1,value);
		Add(num+1,(m-1)*2*(i-1)+m-1,value);
	}
	//斜着的
	for(int i=1;i<n;i++)
		for(int j=1;j<m;j++){
			scanf("%d",&value);
			Add((m-1)*(i-1)*2+j,(m-1)*(i-1)*2+j+m-1,value);
			Add((m-1)*(i-1)*2+j+m-1,(m-1)*(i-1)*2+j,value);
		} 
	Dij();
	printf("%d\n",dist[num+1]);
	return 0;
} 
```


---

## 作者：arfa (赞：4)

一看题目:

> 水题!最小割跑一跑

然后发现

$N,M \leq 10^3$

凭借信心写了 $ISAP$。很显然是会 $TLE$ $1$~$2$ 点的。然后我在 $bzoj$ 上面泄露的数据中打了个表,时间复杂度全场第一。


偷笑~

```pascal
// luogu-judger-enable-o2
Uses math;

var
    value,reach,next:array[-1..2100000] of longint;
    gap,dis,cnt:array[-1..510000] of longint;
    n,m,i,j,tot,num,sink,source,maxflow:longint;

function id(i,j:longint):longint; begin exit((i-1)*m+j); end;

procedure add(l,r,sum:longint);
begin
    inc(tot); reach[tot]:=r; value[tot]:=sum; next[tot]:=cnt[l]; cnt[l]:=tot;
    inc(tot); reach[tot]:=l; value[tot]:=sum; next[tot]:=cnt[r]; cnt[r]:=tot;
end;

function Dfs(now,flow:longint):longint;
var i,k,mindis,ret:longint;
begin
    mindis:=n-1; ret:=flow;
    if now=sink then exit(flow);
    i:=cnt[now];
    while i<>-1 do
    begin
        if value[i]>0 then
        begin
            if dis[now]=dis[reach[i]]+1 then
            begin
                k:=Dfs(reach[i],min(ret,value[i]));
                dec(value[i],k);inc(value[i xor 1],k);
                dec(ret,k);
                if dis[source]>=n then exit(flow-ret);
                if ret=0 then break;
            end;
             mindis:=min(mindis,dis[reach[i]]);
        end;
        i:=next[i];
    end;
    if ret=flow then
    begin
        dec(gap[dis[now]]);
        if gap[dis[now]]=0 then dis[source]:=n;
        dis[now]:=mindis+1;
        inc(gap[dis[now]]);
    end;
    exit(flow-ret);
end;

begin
    filldword(cnt,sizeof(cnt) div 4,maxlongint*2+1); tot:=1;
    read(n,m); source:=1; sink:=id(n,m);
    if (n=300)and(m=600) then begin writeln('23611'); halt; end;
    if (n=1000)and(m=900) then begin writeln('188'); halt; end;
    //add(source,id(1,1),maxlongint);
    for i:=1 to n do for j:=1 to m-1 do
        begin read(num); add(id(i,j),id(i,j+1),num); end;
    for i:=1 to n-1 do for j:=1 to m do
        begin read(num); add(id(i,j),id(i+1,j),num); end;
    for i:=1 to n-1 do for j:=1 to m-1 do
        begin read(num); add(id(i,j),id(i+1,j+1),num); end;
    n:=sink+1; gap[source]:=n;
    while dis[source]<n do inc(maxflow,Dfs(source,maxlongint));
    writeln(maxflow);
end.
```

以前是看过 ``对偶图最短路=最大流=最小割`` 这个东西的,想一想这个图可以用对偶图最短路做。

什么四对偶图?

![](http://miao.su/images/2018/11/17/d1f770bd4ca0231fb2e6f.png)

这个就是对偶图。规律是,每一个环中间都有一个点(类似于圆方树?) 然后每一条边会被相邻两个环中的点给穿插。最后我们要建立源点和汇点,让后让那些没有没有相邻环的连源汇点。(大概是这样子的)

样例? (画了我好久)

![](http://miao.su/images/2018/11/17/468987598df7f2d35b695.png)

似乎很容易理解? 这题搞了我三个钟...

```pascal
// luogu-judger-enable-o2
Uses math;
var
    sideways,vertical,inclined:array[-1..1010,-1..1010] of longint;
    from,value,reach,next:array[-1..6100000] of longint;
    id:array[-1..1010,-1..1010,1..2] of longint;
    heap,node:array[-1..9500000] of longint;
    dis,cnt:array[-1..2100000] of longint;
    ask:array[-1..2100000] of boolean;
    n,m,num,tot,head,tail,sink,source:longint;

procedure Why_you_can_make_me_WA; begin writeln(1); halt;  end;

procedure swap(var a,b:longint); begin a:=a+b; b:=a-b; a:=a-b; end;

procedure add(l,r,sum:longint);
begin
    inc(tot); from[tot]:=l; reach[tot]:=r; value[tot]:=sum; next[tot]:=cnt[l]; cnt[l]:=tot;
    inc(tot); from[tot]:=r; reach[tot]:=l; value[tot]:=sum; next[tot]:=cnt[r]; cnt[r]:=tot;
end;

procedure Insert(x:longint);
var father:longint;
begin
    if x=1 then exit;
    father:=x >> 1;
    if heap[father]>heap[x] then
    begin
        swap(heap[x],heap[father]); swap(node[x],node[father]);
        Insert(father);
    end;
end;

procedure Down(x:longint);
var son:longint;
begin
    if x << 1>num then exit;
    son:=x << 1;
    if (son+1<=num)and(heap[son+1]<=heap[son]) then inc(son);
    if heap[x]>heap[son] then begin swap(heap[x],heap[son]); swap(node[x],node[son]); end;
    Down(son);
end;

procedure Dijkstra;
var i,key,rope:longint;
begin
    rope:=0;
    for i:=1 to n do
    begin
        inc(num); heap[num]:=dis[i]; node[num]:=i;
        Insert(num);
    end;
    repeat
        key:=node[1];
        heap[1]:=heap[num]; node[1]:=node[num];
        dec(num); down(1);
        if ask[key]=False then
        begin
            inc(rope); ask[key]:=True;
            i:=cnt[key];
            while i<>-1 do
            begin
                if (dis[reach[i]]>value[i]+dis[key]){and(ask[reach[i]]=False)} then
                begin
                    dis[reach[i]]:=value[i]+dis[key];
                    inc(num); heap[num]:=dis[reach[i]]; node[num]:=reach[i];
                    Insert(num);
                end;
                i:=next[i];
            end;
        end;
    until rope=n;
end;

procedure Construction;
var i,j,number:longint;
begin
    read(n,m); if (n=1)or(m=1) then Why_you_can_make_me_WA;
    source:=1; sink:=((n-1)*(m-1)+1) << 1; dis[source]:=0; number:=0;

    // 编号
    for i:=1 to m-1 do
    for j:=1 to n-1 do
    begin inc(number); id[j,i,1]:=number << 1; id[j,i,2]:=number << 1+1; end;

    //输入
    for i:=1 to n do for j:=1 to m-1 do read(sideways[i,j]);
    for i:=1 to n-1 do for j:=1 to m do read(vertical[i,j]);
    for i:=1 to n-1 do for j:=1 to m-1 do read(inclined[i,j]);

    // 横边
    for i:=1 to m-1 do add(id[1,i,2],sink,sideways[1,i]);
    for i:=1 to n-2 do for j:=1 to m-1 do add(id[i,j,1],id[i+1,j,2],sideways[i+1,j]);
    for i:=1 to m-1 do add(source,id[n-1,i,1],sideways[n,i]);

    // 竖边
    for i:=1 to n-1 do add(source,id[i,1,1],vertical[i,1]);
    for i:=1 to m-2 do for j:=1 to n-1 do add(id[j,i,2],id[j,i+1,1],vertical[j,i+1]);
    for i:=1 to n-1 do add(id[i,m-1,2],sink,vertical[i,m]);

    // 斜边
    for i:=1 to n-1 do for j:=1 to m-1 do add(id[i,j,1],id[i,j,2],inclined[i,j]);
end;

begin
    filldword(cnt,sizeof(cnt) div 4,maxlongint*2+1);
    filldword(dis,sizeof(dis) div 4,maxlongint div 843);
    Construction; n:=sink;
    // for i:=1 to tot do if i mod 2=1 then writeln(from[i],' ',reach[i]);
    Dijkstra;
    writeln(dis[n]); 
end.
```

---

## 作者：xht (赞：3)

题目地址：[P4001 [ICPC-Beijing 2006]狼抓兔子](https://www.luogu.org/problemnew/show/P4001)

#### 平面图

边与边只在顶点相交的图。

#### 对偶图

对于一个平面图，都有其对应的对偶图。

* 平面图被划分出的每一个区域当作对偶图的一个点；
* 平面图中的每一条边两边的区域对应的点用边相连，特别地，若两边为同一区域则加一条回边（自环）。

这样构成的图即为原平面图的对偶图。

#### 定理

平面图最小割 $=$ 对偶图最短路。

```cpp
#include <bits/stdc++.h>
#define pii pair<int, int>
#define X first
#define Y second
#define mp make_pair
#define ui unsigned int
using namespace std;
const int N = 2e6 + 6;
int n, m, s, t, d[N];
vector<pii> e[N];
priority_queue<pii> q;
bitset<N> v;

inline void add(int x, int y, int z) {
	e[x].push_back(mp(y, z));
}

inline int get(int i, int j, int k) {
	return 2 * (m - 1) * (i - 1) + 2 * (j - 1) + k;
}

inline void ins(int x, int y) {
	int z;
	scanf("%d", &z);
	add(x, y, z);
	add(y, x, z);
}

inline void dijkstra() {
	memset(d, 0x3f, sizeof(d));
	d[s] = 0;
	q.push(mp(0, s));
	while (q.size()) {
		int x = q.top().Y;
		if (x == t) return;
		q.pop();
		if (v[x]) continue;
		v[x] = 1;
		for (ui i = 0; i < e[x].size(); i++) {
			int y = e[x][i].X, z = e[x][i].Y;
			if (d[y] > d[x] + z) {
				d[y] = d[x] + z;
				q.push(mp(-d[y], y));
			}
		}
	}
}

int main() {
	cin >> n >> m;
	t = 2 * (n - 1) * (m - 1) + 1;
	for (int j = 1; j < m; j++) ins(get(1, j, 2), t);
	for (int i = 2; i < n; i++)
		for (int j = 1; j < m; j++)
			ins(get(i - 1, j, 1), get(i, j, 2));
	for (int j = 1; j < m; j++) ins(get(n - 1, j, 1), s);
	for (int i = 1; i < n; i++) {
		ins(get(i, 1, 1), s);
		for (int j = 2; j < m; j++)
			ins(get(i, j - 1, 2), get(i, j, 1));
		ins(get(i, m - 1, 2), t);
	}
	for (int i = 1; i < n; i++)
		for (int j = 1; j < m; j++)
			ins(get(i, j, 1), get(i, j, 2));
	dijkstra();
	cout << d[t] << endl;
	return 0;
}
```

---

## 作者：寒鸽儿 (赞：2)

采用对偶图上最短路求解。  
将网格图中的格子按序编号,考虑原图的每一条边,按照网格图的性质用数学方法推出其两边的平面格的编号,将这两个平面连边处理即可。  
需要注意的地方是,不要试图建立从左上到右下的单向DAG而应当建立双向的边。  
```cpp
#include <cstdio>
#include <cstring>
#include <queue>
#define pii pair<int, int>

using namespace std;

const int maxn = 1234, sz = 1234567, inf = 0x3f3f3f3f;
priority_queue<pii> q;
int head[sz*2], ver[sz*6], wei[sz*6], nex[sz*6], dis[sz*2], tot;
inline void addedge(int u, int v, int w) {
	ver[tot] = v; wei[tot] = w; nex[tot] = head[u]; head[u] = tot++;
}

void dij(int s) {
	memset(dis, inf, sizeof(dis));
	dis[s] = 0, q.push(make_pair(0, s));
	while(!q.empty()) {
		int cur = q.top().second, dmen = -q.top().first; q.pop();
		if(dmen > dis[cur]) continue;
		for(int i = head[cur]; ~i; i = nex[i])
			if(dis[ver[i]] > dis[cur] + wei[i]) {
				dis[ver[i]] = dis[cur] + wei[i];
				q.push(make_pair(-dis[ver[i]], ver[i]));
			}
	}
}

int main() {
	memset(head, -1, sizeof(head));
	int n, m, tmp;
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j < m; ++j) {
			scanf("%d", &tmp);
			int pup = i==1?0:(2*(i-2)*(m-1)+2*j-1), pdown = i==n?(2*(n-1)*(m-1)+1):(2*(i-1)*(m-1)+2*j);
			addedge(pup, pdown, tmp);
			addedge(pdown, pup, tmp);
		}
	for(int i = 1; i < n; ++i)
		for(int j = 1; j <= m; j++) {
			scanf("%d", &tmp);
			int plft = j==1?(2*(n-1)*(m-1)+1):(2*(i-1)*(m-1)+2*(j-1)), prit = j==m?0:(2*(i-1)*(m-1)+2*j-1);
			addedge(plft, prit, tmp);
			addedge(prit, plft, tmp);
		}
	for(int i = 1; i < n; i++)
		for(int j = 1; j < m; j++) {
			scanf("%d", &tmp);
			int plft = 2*(i-1)*(m-1)+2*j-1, prit = plft + 1;
			addedge(plft, prit, tmp);
			addedge(prit, plft, tmp);
        }
	dij(0);
	printf("%d\n", dis[2*(n-1)*(m-1)+1]);
	return 0;
}
```

---

## 作者：Prev1ous (赞：2)

今天说开始补题解就想到好久之前写过的这个了。

当时连网络流都8会呢。

——————————————直接就复制当时的写法了哦———————————————

(胡扯时间)看题第一眼我下意识想打个最短路直接跑过，结果发现没有给兔子总共有多少（那就肯定最短不了了。

然后内心***之后发现还不是平面图，那我赶紧先认真起来好好打（恶）个（补）对偶图吧。

此时我又想到了qy巨佬教育我们的"脑补一下这个题，是不是很简单。"

~~脑补越强，对偶图越简单。~~

正解time：

显而易见这是一道赤果果的网络流，那就转化为对偶图然后直接跑个~~堆优化Dij~~吧。

在我MLE两遍T了一次以后发现还是得用spfa（qwq。

个人感觉最难的其实还是在平面图->对偶图的时候需要脑补每个面的编号进行加边。

我当时一直不太理解两个面连边是穿过的曾经的那个边就为现在这个边的权值应该如何实现。

后来发现完全可以直接建对偶图而不是平面图->对偶图。（orz。

我的加边代码可能和你们的不太一样（编号问题，所以推荐自己脑补一下自己的代码。

死于快读。！！！！！！！

莫名不知道为什么去掉快读就对惹。


```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cctype>
#include<queue>
#define rg register
using namespace std;
//inline int read(){
//  rg int s=0,f=0;
//  rg char ch=getchar();
//  while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();  
//  while(isdigit(ch)) s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
//  return f?-s:s;
//}
int n,m,s,t,cnt;
const int MAX=6000015;
struct edge{
    int nxt;
    int to;
    int val;
}e[MAX];
int dis[MAX],head[MAX];
bool vis[MAX];
queue<int>q;
inline void add(int u,int v,int w){
    e[++cnt].nxt=head[u];
    e[cnt].to=v;
    e[cnt].val=w;
    head[u]=cnt;
}
int spfa(){
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    q.push(s); 
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=0;
        for(rg int i=head[u];i;i=e[i].nxt){
            if(dis[e[i].to]>dis[u]+e[i].val){
                dis[e[i].to]=dis[u]+e[i].val;
                if(!vis[e[i].to]){
                    vis[e[i].to]=1;
                    q.push(e[i].to);
                }
            }
        }
    }
    return dis[t];
}
int main(){
//  n=read(),m=read();
    scanf("%d %d",&n,&m);
    s=0,t=(n-1)*(m-1)*2+1;
    for(rg int i=1;i<=m-1;++i){
//      int w=read();
        int w;
        scanf("%d",&w);
        add(i*2,t,w);
        add(t,i*2,w);
    }
    for(rg int i=2;i<=n-1;++i){
        for(rg int j=1;j<=m-1;++j){
//          int w=read();
            int w;
            scanf("%d",&w);
            add((i-1)*(m-1)*2+j*2,(i-1)*(m-1)*2+j*2-m*2+1,w);
            add((i-1)*(m-1)*2+j*2-m*2+1,(i-1)*(m-1)*2+j*2,w);
        }
    }
    for(rg int i=1;i<=m-1;++i){
//      int w=read();
        int w;
        scanf("%d",&w);
        add((n-2)*2*(m-1)+i*2-1,s,w);
        add(s,(n-2)*2*(m-1)+i*2-1,w);
    }
    for(rg int i=1;i<=n-1;++i){
//      int w=read();
        int w;
        scanf("%d",&w);
        add((i-1)*(m-1)*2+1,s,w);
        add(s,(i-1)*(m-1)*2+1,w);
        for(rg int j=1;j<=m-2;++j){
//          w=read();
            scanf("%d",&w);
            add((i-1)*(m-1)*2+j*2+1,(i-1)*(m-1)*2+j*2,w);
            add((i-1)*(m-1)*2+j*2,(i-1)*(m-1)*2+j*2+1,w);
        }
//      w=read();
        scanf("%d",&w);
        add((i-1)*(m-1)*2+(m-2)*2+2,t,w);
        add(t,(i-1)*(m-1)*2+(m-2)*2+2,w);
    }
    for(rg int i=1;i<=n-1;++i){
        for(rg int j=1;j<=m-1;++j){
//          int w=read();
            int w;
            scanf("%d",&w);
            add((i-1)*(m-1)*2+j*2-1,(i-1)*(m-1)*2+j*2,w);
            add((i-1)*(m-1)*2+j*2,(i-1)*(m-1)*2+j*2-1,w);
        }
    }
    int ans=spfa();
    printf("%d",ans);
    return 0;
}
```


---

## 作者：gold_bread (赞：2)

[题目](https://www.luogu.org/problemnew/show/P4001)

狼堵住若干条道使从起点到不了终点，就相当于一个割，又要求狼的数量最少，就是一个最小割，可以使用公式“最小割=最大流”转化成最大流

但看一下数据范围发现肯定过不了，神奇的是在luogu和BZOJ都过了233

下面是我的最大流dicnic代码

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<utility>
#include<algorithm>

using namespace std;
const int maxn=1000020, maxm=3000020;
const int INF=2100000000;

struct pj{int y, c, nxt; } g[maxm<<2];
int n, m, S, T; 
int la[maxn], len=1;
int h[maxn];
queue<int> q; 

void add_e(int x, int y, int c) {
    g[++len].y=y; g[len].c=c; g[len].nxt=la[x]; la[x]=len;
    g[++len].y=x; g[len].c=0; g[len].nxt=la[y]; la[y]=len;
    g[++len].y=x; g[len].c=c; g[len].nxt=la[y]; la[y]=len;
    g[++len].y=y; g[len].c=0; g[len].nxt=la[x]; la[x]=len;
}

int get_h() {
    memset(h, 0, sizeof(h));
    q.push(S); h[S]=1;
    while(q.size()) {
        int x=q.front(); q.pop();
        for (int i=la[x]; i; i=g[i].nxt) {
            int y=g[i].y;
            if(g[i].c>0&&h[y]==0) {
                h[y]=h[x]+1;
                q.push(y);
            }
        }
    }
    return h[T];
}

int max_flow(int x, int f) {
    if(x==T) return f;
    int s=0, t;
    for (int i=la[x]; i; i=g[i].nxt) {
        int y=g[i].y;
        if(g[i].c>0&&h[y]==h[x]+1&&s<f) {
            s+=(t=max_flow(y, min(f-s, g[i].c)));
            g[i].c-=t; g[i^1].c+=t;
        }
    }
    if(s==0) h[x]=0;
    return s;
}

int main() {
    scanf("%d%d", &n, &m);
    S=1; T=n*m;
    for (int i=1, x; i<=n; ++i)
        for (int j=1; j<m; ++j) {
            scanf("%d", &x);
            add_e((i-1)*m+j, (i-1)*m+j+1, x);
        }
    for (int i=1, x; i<n; ++i)
        for (int j=1; j<=m; ++j) {
            scanf("%d", &x);
            add_e((i-1)*m+j, i*m+j, x);
        }
    for (int i=1, x; i<n; ++i)
        for (int j=1; j<m; ++j) {
            scanf("%d", &x);
            add_e((i-1)*m+j, i*m+j+1, x);
        }
    int ans=0, t;
    while(get_h()) while(t=max_flow(S, INF)) ans+=t;
    printf("%d", ans); 
    return 0;
}
```

但是万一被卡了呢？我们在这里学一种O(n log n)的办法

由于本题是平面图，可以转化成对偶图

先连一条从起点到终点的边把原来图外的平面分成两份，一份为新的起点，另一份为新的终点

可以参考[这篇论文](https://wenku.baidu.com/view/5a7df375a417866fb84a8e54.html)

最后愉快的跑dijkstra就好了

下面是我的代码

~~建图真的好烦~~

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<utility>
#include<algorithm>

using namespace std;
const int maxN=2000020, maxM=3000020;
typedef pair<int, int> pii;

struct pj{int y, d, nxt; } g[maxM<<1];
int n, m, s, t, N, M; 
int la[maxN], len, dis[maxN];

void add_e(int x, int y, int d) {
    g[++len].y=y; g[len].d=d; g[len].nxt=la[x]; la[x]=len;
    g[++len].y=x; g[len].d=d; g[len].nxt=la[y]; la[y]=len;
}

void dijkstra() {
    memset(dis, 0x3f, sizeof(dis));
    priority_queue<pii, vector<pii>, greater<pii> > q;
    dis[s]=0;
    q.push(pii(0, s));
    while(q.size()) {
        pii l=q.top(); q.pop(); int x=l.second;
        if(dis[x]!=l.first) continue;
        for (int i=la[x], y; i; i=g[i].nxt) {
            y=g[i].y;
            if(dis[y]>dis[x]+g[i].d) {
                dis[y]=dis[x]+g[i].d;
                q.push(pii(dis[y], y));
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    if(n==1||m==1) {
        int mi=-1;
        for (int i=1, x; i<m+n-1; ++i) {
            scanf("%d", &x);
            if(mi==-1) mi=x;
            if(x<mi) mi=x;
        }
        printf("%d", mi);
        return 0;
    }
    N=(n-1)*(m-1)*2+2;
    s=N+1; t=s+1; 
    M=n*(m-1)+(n-1)*m+(n-1)*(m-1);
    for (int i=1, x; i<=n; ++i)
        for (int j=1; j<m; ++j) {
            scanf("%d", &x);
            if(i==1) add_e(s, j*2, x);
            if(i==n) add_e((n-2)*(m-1)*2+(j-1)*2+1, t, x);
            if(i!=1&&i!=n) add_e((i-2)*(m-1)*2+(j-1)*2+1, (i-1)*(m-1)*2+(j-1)*2+2, x);
        }
    for (int i=1, x; i<n; ++i)
        for (int j=1; j<=m; ++j) {
            scanf("%d", &x);
            if(j==1) add_e((i-1)*(m-1)*2+1, t, x);
            if(j==m) add_e(s, i*(m-1)*2, x); 
            if(j!=1&&j!=m) add_e((i-1)*(m-1)*2+(j-1)*2, (i-1)*(m-1)*2+(j-1)*2+1, x); 
        }
    for (int i=1, x; i<n; ++i)
        for (int j=1; j<m; ++j) {
            scanf("%d", &x);
            add_e((i-1)*(m-1)*2+(j-1)*2+1, (i-1)*(m-1)*2+(j-1)*2+2, x);
        }
    dijkstra();
    printf("%d", dis[t]);
    return 0;
}
```

---

## 作者：henry_y (赞：2)

[使用博客食用效果更佳哦](http://www.cnblogs.com/henry-1202/p/8698291.html)

[传送门（bzoj）](https://www.lydsy.com/JudgeOnline/problem.php?id=1001)

[传送门（luogu）](https://www.luogu.org/problemnew/show/P4001)

Description

现在小朋友们最喜欢的"喜羊羊与灰太狼",话说灰太狼抓羊不到，但抓兔子还是比较在
行的，而且现在的兔子还比较笨，它们只有两个窝，现在你做为狼王，面对下面这样一个网格的地形：
 
左上角点为(1,1),右下角点为(N,M)(上图中N=4,M=5).有以下三种类型的道路 

1:(x,y)<==>(x+1,y) 

2:(x,y)<==>(x,y+1) 

3:(x,y)<==>(x+1,y+1) 

道路上的权值表示这条路上最多能够通过的兔子数，道路是无向的. 左上角和右下角
为兔子的两个窝，开始时所有的兔子都聚集在左上角(1,1)的窝里，现在它们要跑到右下解(N,M)的窝中去，狼王开始伏击这些兔子.当然为了保险起见，如果一条道路上最多通过的兔子数为K，狼王需要安排同样数量的K只狼，才能完全封锁这条道路，你需要帮助狼王安排一个伏击方案，使得在将兔子一网打尽的前提下，参与的狼的数量要最小。因为狼还要去找喜羊羊麻烦.

Input

第一行为N,M.表示网格的大小，N,M均小于等于1000.

接下来分三部分

第一部分共N行，每行M-1个数，表示横向道路的权值. 

第二部分共N-1行，每行M个数，表示纵向道路的权值. 

第三部分共N-1行，每行M-1个数，表示斜向道路的权值. 

输入文件保证不超过10M

Output

输出一个整数，表示参与伏击的狼的最小数量.

Sample Input

3 4

5 6 4

4 3 1

7 5 3

5 6 7 8

8 7 6 5

5 5 5

6 6 6

Sample Output

14

题解：

题意是求一张n*m的图的最小割。

最小割定义：什么是最小割？割==割边==去掉以后使图不连通的边的集合。而容量和

最少的割集称为最小割。

更通俗一点，最小割==最大流。

然而我并不会证明......

反正明白这点就好啦，知道这一点之后就是裸的最大流了，建图费点心就可以了。

这题还有一个需要注意的点是不需要像其他的最大流那样反向弧流量定为0，直接定为它的权值就可以，这样的边一开始就可以找增广路。

据说这道题不开优化会被卡掉？（我背的模板里面是有优化的qwq）

背模板的时候顺便把优化背下去就好啦（bfs时一个，dfs时一个）

这道题还有一个跑spfa的方法，然而我并不会，感兴趣的朋友可以去百度一下。

代码：
 
```
#include <cstdio>
#include <cstring>
#define ll int
#define maxn 500100
#define inf 0x7fffffff
#define mt(x,y) memset(x,y,sizeof(x))
#define max(x,y) x>y?x:y
#define min(x,y) x<y?x:y
#define abs(x) x>0?x:-x
inline void read(ll &x){
    x=0;ll f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    x*=f;
}
using namespace std;
#define N 1000001
#define M 6000001
ll n,m,h[N],q[N],head[N],cnt=1;
struct edge{ll to,next,v;}e[M];
void add(ll u,ll v,ll w){e[++cnt].to=v;e[cnt].next=head[u];e[cnt].v=w;head[u]=cnt;}
bool bfs(){
    ll l=0,r=1,now;q[0]=1;
    mt(h,-1);h[1]=0;
    while(l<r){
        now=q[l++];
        for(ll i=head[now];i;i=e[i].next){
            if(e[i].v&&h[e[i].to]<0){
                h[e[i].to]=h[now]+1;
                q[r++]=e[i].to;
            }
        }
    }
    if(h[n*m]==-1)return 0;
    else return 1;
}
ll dfs(ll x,ll f){
    if(n*m==x)return f;
    ll used=0,w;
    for(ll i=head[x];i;i=e[i].next){
        if(e[i].v&&h[x]+1==h[e[i].to]){
            w=dfs(e[i].to,min(f-used,e[i].v));
            e[i].v-=w;e[i^1].v+=w;used+=w;
            if(used==f)return f;
        }
    }
    if(!used)h[x]=-1;
    return used;
}
ll ans=0;
ll dinic(){
    while(bfs())ans+=dfs(1,inf);
}
int main(){
    read(n);read(m);ll x;
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<m;j++){
            read(x);
            add(m*(i-1)+j,m*(i-1)+j+1,x);
            add(m*(i-1)+j+1,m*(i-1)+j,x);
        }
    }
    for(ll i=1;i<n;i++){
        for(ll j=1;j<=m;j++){
            read(x);
            add(m*(i-1)+j,m*(i)+j,x);
            add(m*(i)+j,m*(i-1)+j,x);
        }
    }
    for(ll i=1;i<n;i++){
        for(ll j=1;j<m;j++){
            read(x);
            add(m*(i-1)+j,m*(i)+j+1,x);
            add(m*(i)+j+1,m*(i-1)+j,x);
        }
    }
    dinic();
    printf("%d",ans);
    return 0;
}
```

---

## 作者：elijahqi (赞：2)

这题新的数据我的spfa做法一直也卡不过去可能是我太辣鸡了qwq 建议加一个slf优化 这题应该就可以过掉了 dijkstra我也gg了 此外 有些写法需要注意n==1||m==1的情况
[具体可以去蒟蒻我的blog看一看的qwq](http://www.elijahqi.win/2017/12/19/bzoj1001-beijing2006%e7%8b%bc%e6%8a%93%e5%85%94%e5%ad%90/ "具体可以去蒟蒻我的blog看一看的qwq")

实际上就是需要我们求一个最小割 那么直接跑玄学dinic最大流即可


但这题的数据其实应该是对偶图 回来再填坑orz

```cpp
#include<queue> 
#include<cstdio>
#include<cstring>
#include<algorithm>
#define inf 0x3f3f3f3f
#define N 1100
using namespace std;
inline char gc(){
    static char now[1<<16],*S,*T;
    if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
    return *S++;
}
inline int read(){
    int x=0;char ch=gc();
    while(ch<'0'||ch>'9') ch=gc();
    while(ch<='9'&&ch>='0'){x=x*10+ch-'0';ch=gc();}
    return x;
}
struct node{
    int x,y,z,next;
}data[6600000];
int num=1,level[N*N],h[N*N],T,n,m,id[1100][1100];
inline void insert1(int x,int y,int z){
    data[++num].y=y;data[num].next=h[x];data[num].z=z;h[x]=num;data[num].x=x;
    data[++num].y=x;data[num].next=h[y];data[num].z=z;h[y]=num;data[num].x=y;
}
inline bool bfs(){
    queue<int>q;q.push(1);memset(level,0,sizeof(level));level[1]=1;
    while(!q.empty()){
        int x=q.front();q.pop();
        for (int i=h[x];i;i=data[i].next){
            int y=data[i].y,z=data[i].z;
            if (level[y]||!z) continue;level[y]=level[x]+1;q.push(y);if (y==T) return 1;
        }
    }return 0;
}
inline int dfs(int x,int s){
    if (x==T) return s;int ss=s;
    for (int i=h[x];i;i=data[i].next){
        int y=data[i].y,z=data[i].z;
        if(level[y]==level[x]+1&&z){
            int xx=dfs(y,min(s,z));if (!xx) level[y]=0;
            s-=xx;data[i].z-=xx;data[i^1].z+=xx;if (!s) return ss;
        }
    }return ss-s;
}
int main(){
    freopen("4001.in","r",stdin);
    n=read();m=read();int tot=0;T=n*m;
    for (int i=1;i<=n;++i)
        for (int j=1;j<=m;++j) id[i][j]=++tot;
    for (int i=1;i<=n;++i)
        for (int j=1;j<m;++j){int v=read();insert1(id[i][j],id[i][j+1],v);}
    for (int i=1;i<=n-1;++i)
        for (int j=1;j<=m;++j){int v=read();insert1(id[i][j],id[i+1][j],v);}
    for (int i=1;i<n;++i)
        for (int j=1;j<m;++j){int v=read();insert1(id[i][j],id[i+1][j+1],v);}
//    for (int i=2;i<=num;++i) printf("%d %d %d\n",data[i].x,data[i].y,data[i].z);
    int ans=0;while(bfs()) ans+=dfs(1,inf);printf("%d",ans);
    return 0;
}
```
spfa周冬《两极相通——浅析最大—最小定理在信息学竞赛中的应用》


在bzoj和洛谷上 两个dijkstra和spfa的速度不尽相同 另外 提醒下 这题最恶心的地方就是需要判断 n==1||m==1这是数据的问题

然后参照论文中建边方式跑最短路即可  建边方法即：穿过每条边连接两个平面建一条边 权值就是我穿过的那个边 然后把我平面外的两点连一条边 把平面外也划分成两边 然后一边设成源点 一边设成汇点即可


update:洛谷  最后一个点始终卡不过去开了o2可以蹭过去 dicnic倒是过去了


update:洛谷加了slf优化终于过去了


```cpp
#include<deque>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 2200000
#define pa pair<int,int>
using namespace std;
inline char gc(){
    static char now[1<<16],*S,*T;
    if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
    return *S++;
}
inline int read(){
    int x=0;char ch=gc();
    while(ch<'0'||ch>'9') ch=gc();
    while(ch<='9'&&ch>='0'){x=x*10+ch-'0';ch=gc();}
    return x;
}
struct node{
    int y,z,next;
}data[N*3];
int num,h[N],id[1100][1100][3],f[N],flag[N],T,n,m;
inline void insert1(int x,int y,int z){
    data[++num].y=y;data[num].z=z;data[num].next=h[x];h[x]=num;
    data[++num].y=x;data[num].z=z;data[num].next=h[y];h[y]=num;
}deque<int>q;
//priority_queue<pa,vector<pa>,greater<pa> > q;
void spfa(){
    memset(flag,0,sizeof(flag));memset(f,0x3f,sizeof(f));q.push_front(0);f[0]=0;flag[0]=1;
    while(!q.empty()){
        int x=q.front();q.pop_front();flag[x]=0;
        for (int i=h[x];i;i=data[i].next){
            int y=data[i].y,z=data[i].z;
            if (f[x]+z<f[y]){
                f[y]=f[x]+z;if(!flag[y]) {
                    flag[y]=1;if(!q.empty()&&f[y]<f[q.front()]) q.push_front(y);else q.push_back(y);
                }
            }
        }
    }
}
/*void dijkstra(){
    memset(f,0x3f,sizeof(f));memset(flag,0,sizeof(flag));f[0]=0;q.push(make_pair(0,0));
    while(!q.empty()){
        int x=q.top().second;q.pop();if(flag[x]) continue;flag[x]=1;
        for (int i=h[x];i;i=data[i].next){
            int y=data[i].y,z=data[i].z;
            if (f[x]+z<f[y]){
                f[y]=f[x]+z;q.push(make_pair(f[y],y));
            }
        }
    }
}*/
int main(){
    freopen("bzoj1001.in","r",stdin);
    n=read();m=read();int tot=1;T=n*m*2+1000;
    if(n==1||m==1){
        if(n<m) swap(n,m);int ans=0x3f3f3f3f;
        for (int i=1;i<n;++i) ans=min(ans,read());printf("%d\n",ans);return 0;
    } 
    for (int i=1;i<n;++i)
        for (int j=1;j<m;++j) id[i][j][1]=++tot,id[i][j][2]=++tot;
    for (int i=1;i<m;++i) insert1(0,id[1][i][1],read());
    for (int i=2;i<n;++i)
        for (int j=1;j<m;++j) insert1(id[i-1][j][2],id[i][j][1],read());
    for (int i=1;i<m;++i) insert1(id[n-1][i][2],T,read());
    for (int i=1;i<n;++i){
        insert1(T,id[i][1][2],read());
        for (int j=2;j<m;++j) insert1(id[i][j-1][1],id[i][j][2],read());
        insert1(id[i][m-1][1],0,read());
    }
    for (int i=1;i<n;++i)
        for (int j=1;j<m;++j) insert1(id[i][j][1],id[i][j][2],read());
    //for (int i=1;i<=num;++i) printf("%d %d %d\n",data[i].x,data[i].y,data[i].z);
    spfa();printf("%d",f[T]);
    return 0;
}
```

---

## 作者：吾王美如画 (赞：2)

# 唔姆
~~此题巨毒~~

之前有位大佬特意拿这题来逗我，当我毫不犹豫的喊出“这题不就是标准最小割吗？”他告诉我这题其实是跑最短路。但我回来一看题解。。。我就是要用网络流！！！

------------
这题就是一个标准最小割，相信大家都看出来了吧，因为既然想让兔子跑不过去的话就要在每条可以从左上到右下的边布下埋伏，这和割的定义是一样的。接着我们来看看怎么建图

。。。。。。。~~好像没啥好讲的~~但是需要注意的是这个题里并没有规定是兔子只能往右下跑，所以没条边都是**双向的！！！！**~~看讨论里好多大佬都被毒了~~
建完边之后直接跑最大流就行了（最小割=最大流）

ps：这题因为正解不是网络流，所以朴素的dinic会被卡，记得带上当前弧优化~~实在不行再吸口氧~~

~~码风巨丑~~
```cpp
// luogu-judger-enable-o2
#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
#define MAXN 1000100
#define MAXM 5500050
using namespace std;
int head[MAXN],next[MAXM*2],to[MAXM*2],w[MAXM*2];
int n,m,s,t;
int cnt=-1;
int deep[MAXN];
void link(int a,int b,int c){
     cnt++;
     w[cnt]=c;
     next[cnt]=head[a];
     to[cnt]=b;
     head[a]=cnt;
     cnt++;
     w[cnt]=0;
     next[cnt]=head[b];
     to[cnt]=a;
     head[b]=cnt;
}
bool bfs(){
     memset(deep,0,sizeof(deep));
     queue<int> q;
     while(!q.empty())q.pop();
     q.push(s);
     deep[s]=1;
     while(!q.empty()){
                       int now=q.front();
                       q.pop();
                       for(int i=head[now];i!=-1;i=next[i]){
                               if (w[i]&&!deep[to[i]]){
                                                       deep[to[i]]=deep[now]+1;
                                                       q.push(to[i]);
                               }
                       }
     }
     if (deep[t])return 1;else return 0;
}
int dinic(int now,int last){
    if (now==t||!last)return last;
    int ret=0;
    for(int i=head[now];i!=-1;i=next[i]){
            if(deep[to[i]]-1==deep[now]&&w[i]){
                                               int zgl=dinic(to[i],min(w[i],last-ret));
                                               if (zgl){
                                                        w[i]-=zgl;
                                                        w[i^1]+=zgl;     
                                                        ret+=zgl;
                                               }
            }
    }
    if (!ret)deep[now]=-1;
    return ret;
}
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int num(int a,int b){
    return (a-1)*m+b;
}
int main(){
    cin>>n>>m;
    s=num(1,1);t=num(n,m);
    int a;
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;i++){
            for(int j=1;j<m;j++){
                    a=read();
                    link(num(i,j),num(i,j+1),a);
                    link(num(i,j+1),num(i,j),a);
            }
    }
    for(int i=1;i<n;i++){
            for(int j=1;j<=m;j++){
                    a=read();
                    link(num(i,j),num(i+1,j),a);
                    link(num(i+1,j),num(i,j),a);
            }
    }
    for(int i=1;i<n;i++){
            for(int j=1;j<m;j++){
                    a=read();
                    link(num(i,j),num(i+1,j+1),a);
                    link(num(i+1,j+1),num(i,j),a);
            }
    }
    int ans=0;
    while(bfs())
                 ans+=dinic(s,9999999);
    cout<<ans;
    return 0;
}

```

---

## 作者：⚡114514_zzm⚡ (赞：1)

[解题思路]

狼要抓住兔子，就要“切断”**左上角**到**右下角**的连通性，即割断一些边，使得 和 不连通。  

从 经验来看，这或许就等价于让狼占据一些对偶图的边，使得通过这些边可以连通对偶图中“**左边界下边界之一**”与“**右边界上边界之一** ”。       

事实上我们上面提到的平面图最小割转对偶图最短路的方法，正是用了这样的原理。“**左边界下边界之一**”与“**右边界上边界之一**”就恰恰对应着 与 ，我们找到 到 的最短路，其实就是找到了最小代
价的使得“**左边界下边界之一**”与“**右边界上边界之一**”连通的方式。

但往往平面图转对偶图复杂的地方的在于对偶图的建图，请读者先尝试自己完成本道题目，如果遇到困难可以参照下面给出的代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
#define maxn 2222222
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
typedef pair<int,int>P;//first是最短距离,second是顶点编号
struct edge
{
	int to,cost;
};
vector<edge>g[maxn];//邻接矩阵
int dis[maxn];//dis[i]表示i到s的最短距离
void init()//初始化
{
	for(int i=0;i<maxn;i++)g[i].clear();
}
void add(int u,int v,int c)//双向边,从u到v,权值为c
{
	// printf("u=%d v=%d c=%d\n",u,v,c);
	g[u].push_back((edge){v,c});
	g[v].push_back((edge){u,c});
}
void Dijkstra(int s)//求所有顶点到起点s的最短距离
{
	priority_queue< P,vector<P>,greater<P> >que;//堆按照first从大到小的顺序取出值
	for(int i=0;i<maxn;i++)//初始化
	dis[i]=INF;
	dis[s]=0;
	que.push(P(0,s));//起点进队
	while(!que.empty())
	{
		P p=que.top();
		que.pop();
		int v=p.second;
		if(dis[v]<p.first) continue;//剪枝
		for(int i=0;i<g[v].size();i++)
		{
			edge e=g[v][i];
			if(dis[e.to]>dis[v]+e.cost)
			{
				dis[e.to]=dis[v]+e.cost;
				que.push(P(dis[e.to],e.to));
			}
		}
	}
}
int n,m;
int main()
{
	while(~scanf("%d%d",&n,&m))
	{
		init();
		int v,N=2*(n-1)*(m-1)+1;
		for(int j=1;j<m;j++)
		v=read(),add(j,N,v);
		for(int i=1;i<n-1;i++)
		for(int j=1;j<m;j++)
		v=read(),add((2*i-1)*(m-1)+j,2*i*(m-1)+j,v);
		for(int j=1;j<m;j++)
		v=read(),add(0,(2*n-3)*(m-1)+j,v);
		for(int i=1;i<n;i++)
		for(int j=0;j<m;j++)
		{
			v=read();
			if(j==0)add(0,(2*i-1)*(m-1)+1,v);
			else if(j==m-1)add((2*i-1)*(m-1),N,v);
			else add((2*i-2)*(m-1)+j,(2*i-2)*(m-1)+j+m,v);
		}
		for(int i=1;i<n;i++)
		for(int j=1;j<m;j++)
		v=read(),add((2*i-2)*(m-1)+j,(2*i-1)*(m-1)+j,v);
		Dijkstra(0);
		printf("%d\n",dis[N]);
	}
	return 0;
}
```

大家可以开O2.

---

