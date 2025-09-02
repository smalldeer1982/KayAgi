# [USACO19DEC] Milk Pumping G

## 题目描述

Farmer John 最近为了扩张他的牛奶产业帝国而收购了一个新的农场。这一新的农场通过一个管道网络与附近的小镇相连，FJ 想要找出其中最合适的一组管道，将其购买并用来将牛奶从农场输送到小镇。

这个管道网络可以用 $N$ 个接合点（管道的端点）来描述，将其编号为 $1 \ldots N$。接合点 $1$ 表示 FJ 的农场，接合点 $N$ 表示小镇。有 $M$ 条双向的管道，每条连接了两个接合点。使用第 $i$ 条管道需要 FJ 花费 $c_i$ 美元购入，可以支持每秒 $f_i$ 升牛奶的流量。

FJ 想要购买一条管道组成一条单一路径，路径的两端点分别为接合点 $1$ 和 $N$。这条路径的花费等于路径上所有管道的费用之和。路径上的流量等于路径上所有管道的最小流量（因为这是沿这条路径输送牛奶的瓶颈）。FJ 想要最大化路径流量与路径花费之比。保证存在从 $1$ 到 $N$之间的路径。


## 说明/提示

在这个例子中，仅由一条路径从 $1$ 到 $N$。 它的流量为 $\min(3,4)=3$，花费为 $2+5=7$。

### 数据范围

测试点 $2\sim 5$ 满足 $N,M\le 100$。

对于 $100\%$ 的数据，$2 \leq N \leq 1000$，$1 \leq M \leq 1000$。

供题：Brian Dean

## 样例 #1

### 输入

```
3 2
2 1 2 4
2 3 5 3```

### 输出

```
428571```

# 题解

## 作者：Hexarhy (赞：27)

一道略有变形的最短路模板题。

-----------

### 题意简述

给定一个**无向图**，每条边有其代价 $c$ 和限制 $f$。求出一条从 $1$ 到 $n$ 的路径，使得 $\dfrac{\min\{f_i\}}{\sum c_i}$ 最大。

### 解题思路

只要认真想真的不难。

有两个条件，考虑先枚举 $f$。既然要使分母 $\sum c_i$ 最小，那不相当于以 $c$ 为边权跑最短路？

于是我们可以跑 dijkstra 或 spfa。不过为了达到枚举 $f$ 起的限制作用，我们在**每次松弛操作之前**，要先判断这条边的限制是否**大于** $f$。否则不把这条边计算的最短路中，因为它不满足当前限制。

跑完最短路更新答案即可。

这里使用堆优化的 dijkstra，时间复杂度约为 $O(n^2\log n)$，可以通过本题。

当然也有二分等其他做法，不过已经没有必要了。不熟练的还容易出错。所以能简单算的就简单算。

### 实现细节

- 建图注意是无向图。

- 由于需要多次跑最短路，记得清空某些数组。

- 重载`priority_queue`的时候，符号不要写错。

### 参考代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

#define INF 0x7f7f7f7f
const int MAXN=3005;
int n,m,ans;
struct node
{
	int to,cost,limit;
	bool operator<(const node& a)const
	{
		return cost>a.cost;//方向别反了
	}
};
vector<node> edge[MAXN];
int dis[MAXN],limit[MAXN];
bool visit[MAXN];

void input(void)
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int a,b,x;
		cin>>a>>b>>x>>limit[i];
		edge[a].push_back(node{b,x,limit[i]});//无向图
		edge[b].push_back(node{a,x,limit[i]});
	}
}

int dijkstra(const int limit)
{
	priority_queue<node> q;//记得清空
	memset(visit,false,sizeof(visit));
	memset(dis,INF,sizeof(dis));
	dis[1]=0;
	q.push(node{1,0,limit});
	while(!q.empty())//模板
	{
		const int u=q.top().to;
		q.pop();
		if(visit[u])
		 continue;
		visit[u]=true;
		for(auto v:edge[u])
		 if(v.limit>=limit && dis[v.to]>dis[u]+v.cost)
		 {//注意限制
		 	dis[v.to]=dis[u]+v.cost;
		 	q.push(node{v.to,dis[v.to],limit});
		 }
	}
	return dis[n];
}

int main()
{
	input();
	for(int i=1;i<=m;i++)//枚举 m 次而非 n 次
	 ans=max(ans,limit[i]*int(1e6)/dijkstra(limit[i]));//更新答案
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：ForeverHYX (赞：10)

# 题解002 P5837
蒟蒻的第二篇题解，求管理员大大通过
## 01 链式前向星加边

虽然本题数据规模不大，但是介于本题解使用了枚举的做法，邻接矩阵可能会 $TLE$ ，因此采用链式前向星加边。

在链式前向星加边中，我们维护了数组 $head[i]$ ，用来表示起点为 $i$ 的最后一条边的编号。

同时引入了 $next$ 来表示与该边起点相同的最后一条边的编号，在具体程序中体现为这样：

```cpp
edge[cnt].next = head[u];//cnt表示该边编号
```

本题为有向图，但若为无向图的话，应当注意要将起点与终点颠倒后再建一条边,代码如下。

```cpp
void add(int u, int v, int c, int f)//链式前向星加边
{
    edge[++cnt].c = c;
    edge[cnt].to = v;
    edge[cnt].next = head[u];//cnt表示该边编号
    edge[cnt].f = f;
    head[u] = cnt;
}
```

## 02 链式前向星搜边

相应的,既然有了链式前向星加边,在实际应用中,为了遍历路径,我们还需要链式前向星搜边。

因为链式前向星加边实际上是建立了一张邻接表,因此我们也通过类似链表的方法来实现搜边。即在 $i=False$之前我们一直向前访问 $edge[i].next$ , 从而实现搜边的操作.
具体代码(可能是伪代码)如下

```cpp
for (int i = head[u]; i; i = edge[i].next){
	主体部分;//u代表当前所在边的起点         
}
```

## 03 本体算法
### Dijkstra+堆优化+枚举

[不知道Dijkstra的同学可以看这里的题解,太占篇幅,就不赘述了](https://www.luogu.com.cn/problem/solution/P4779)

因为我们发现流量是个 $0-1000$ 的数字,而堆优化后的dijkstra算法的复杂度是 $O(m\log_2n)$,因此枚举算法的复杂度完全在可接受范围内。

而此处的堆优化采用了 $C++$ 中的 $STL$ 中的优先队列，当然，一般队列显然也是可以实现的。

## 04 本题思路

### 以什么为关键字进行dijkstra和对什么进行列举

我们记某个管道的花费为 $C_i$ ,流量为 $F_i$ ,不难发现题目想让我们求得就是:

$$ \frac{min(F_1,F_2...F_i)}{C_1+C_2...+C_i}$$

那结果就呼之欲出了,我们不大可能对于分母这个多项式进行列举,因此很自然的对于流量进行列举,再在每次合法的列举中进行求最小路的操作。

## 05 代码实现

```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <iomanip>
const int inf = 1e6;
using namespace std;
int n, m, head[2000000], maxx, cnt,dis[2000000];
bool vis[2000000];
struct EDGE
{
    int next, to, c, f;
} edge[2000000];
struct node
{
    int dis;
    int pos;
    bool operator<(const node &x) const
    {
        return x.dis < dis;
    }
};
priority_queue<node> q;
void add(int u, int v, int c, int f)//链式前向星加边
{
    edge[++cnt].c = c;
    edge[cnt].to = v;
    edge[cnt].next = head[u];//cnt表示该边编号
    edge[cnt].f = f;
    head[u] = cnt;
}
void init()
{
    int a, b, c, f;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d%d", &a, &b, &c, &f);
        add(a, b, c, f);
        add(b, a, c, f);
    }
}
void dijkstra()
{
    for (int x = 1; x <= 1000; x++)
    {
        for(int j=1;j<=n;j++){
            dis[j]=inf;
            vis[j]=0;
        } 
        dis[1]=0;
        q.push((node){0, 1});
        while (!q.empty())
        {
            node tmp = q.top();
            q.pop();
            int u = tmp.pos;
            if (vis[u])
                continue;
            vis[u] = 1;
            for (int i = head[u]; i; i = edge[i].next)
            {
                if(edge[i].f<x) continue;
                int v = edge[i].to;
                if (dis[u] + edge[i].c < dis[v])
                {
                    dis[v] = dis[u] + edge[i].c;
                    if (!vis[v])
                    {
                        q.push((node){dis[v], v});
                    }
                }
            }
        }
        if(dis[n]!=inf){
            maxx=max(maxx,x*1000000/dis[n]);//题目中所说的向下取整我们可以通过先乘上1E6再除以最小路来实现
        }
    }
}
int main()
{
    init();
    dijkstra();
    cout <<maxx;
}
```


抄代码没意义，建议可以看完一遍再自己写。
## 06 一些小小的易错点

```cpp
if(edge[i].f<x) continue;
```

### 1
我们通过这行代码来过滤掉不合法的列举，即如果下一条流量比最小量还小就舍去。

### 2
```
maxx=max(maxx,x*1000000/dis[n]);
```

我们通过这行来实现题中所说的向下取整，同时乘除法顺序不能改，否则会因为 $int$ 的精度问题导致答案错误。

 _祝各位都能AC这道题，然后祝这篇题解可以过审核。_ 



---

## 作者：Purple_wzy (赞：10)

推荐一下我的博客，这里有12月月赛的全部12篇题解~~

https://www.cnblogs.com/Purple-wzy/

#### A Milk Pumping

题目：https://www.luogu.com.cn/problem/P5837

题解：从1到1000枚举这个最小流量，跑最短路就好。

复杂度：O(1000*(n+m)logn)

代码：

```
#include<bits/stdc++.h>
using namespace std;
#define re register int
#define F(x,y,z) for(re x=y;x<=z;x++)
#define FOR(x,y,z) for(re x=y;x>=z;x--)
#define I inline void
#define IN inline int
typedef long long ll;
I read(int &res){
    re g=1;register char ch=getchar();res=0;
    while(!isdigit(ch)){
        if(ch=='-')g=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        res=(res<<3)+(res<<1)+(ch^48);
        ch=getchar();
    }
    res*=g;
}
struct E{
	int to,nt,w,v;
}e[2020];
#define T e[k].to
const int INF=1e9+7;
int n,m,head[1010],X,Y,W,V,dis[1010],vis[1010],p,ans,tot;
queue<int>q;
int main(){
	freopen("pump.in","r",stdin);
	freopen("pump.out","w",stdout);
	read(n);read(m);
	memset(head,-1,sizeof(head));tot=-1;
	F(i,1,m){
		read(X);read(Y);read(W);read(V);
		e[++tot].to=Y;
		e[tot].nt=head[X];
		head[X]=tot;
		e[tot].w=W;
		e[tot].v=V;
		e[++tot].to=X;
		e[tot].nt=head[Y];
		head[Y]=tot;
		e[tot].w=W;
		e[tot].v=V;
	}
	ans=0;
	F(val,1,1000){
		F(i,1,n)dis[i]=INF,vis[i]=0;
		dis[1]=0,vis[1]=1;
		q.push(1);
		while(!q.empty()){
			p=q.front();q.pop();vis[p]=0;
			for(re k=head[p];k!=-1;k=e[k].nt){
				if(e[k].v<val)continue;
				if(dis[p]+e[k].w<dis[T]){
					dis[T]=dis[p]+e[k].w;
					if(!vis[T]){
						vis[T]=1;
						q.push(T);
					}
				}
			}
		}
		if(dis[n]!=INF)ans=max(ans,val*1000000/dis[n]);
	}
	cout<<ans;
    return 0;
}
```

---

## 作者：7KByte (赞：5)

抢第一篇题解


题意就是找出一条路径使得$\Large\frac{min\{f_i\}}{\sum c_i}$最大


看的像分数规划，果断二分


然后枚举最小流量$flow$，只保留流量大于等于$flow$的边，然后$Dij$跑单元最短路径，得到$Dist_{1-n}$，用$\frac{flow}{Dist}$更新答案即可

考场代码$O(N^2log^2N)$

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
int n,m,tot,h[1005],o[1005],T=0,b[1005];
struct node{
	int nxt,to,c,f;
}e[2005];
void add(int x,int y,int z,int val){
	e[++tot].nxt=h[x];h[x]=tot;e[tot].to=y;e[tot].c=z;e[tot].f=val;
}
int lim;
int v[100005],d[100005];
priority_queue<pair<int,int> >q;
void dij(int mid){
	memset(d,0x7f,sizeof(d));
	memset(v,0,sizeof(v));
	d[1]=0;q.push(make_pair(0,1));
	while(!q.empty()){
		int x=q.top().second;q.pop();
		v[x]=1;
		for(int i=h[x];i;i=e[i].nxt)if(e[i].f>=lim){
			if(d[x]+e[i].c*mid<d[e[i].to]){
				d[e[i].to]=d[x]+e[i].c*mid;
				q.push(make_pair(-d[e[i].to],e[i].to));
			}
		}
		while(!q.empty()&&v[q.top().second])q.pop();
	}
}
bool check(int mid){
	for(int i=1;i<=T;i++){
		lim=b[i];
		dij(mid);
		//cout<<i<<" "<<lim<<" "<<d[n]<<endl;
		if(d[n]<=lim*1000000)return true;
	}
	return false;
}
signed main(){
	//freopen("pump.in","r",stdin);
	//freopen("pump.out","w",stdout);
	scanf("%lld%lld",&n,&m);
	rep(i,1,m){
		int u,v,x,y;
		scanf("%lld%lld%lld%lld",&u,&v,&x,&y);
		add(u,v,x,y);add(v,u,x,y);
		o[i]=y;
	}
	sort(o+1,o+m+1);
	int l=0,r=1000000,ans=0;
	rep(i,1,m)if(i==1||o[i]!=o[i-1])b[++T]=o[i];
	while(l<=r){
		int mid=(l+r)>>1;
		//cout<<l<<" "<<mid<<" "<<r<<endl;
		if(check(mid))ans=mid,l=mid+1;
		else r=mid-1;
		//cout<<l<<" "<<mid<<" "<<r<<endl;
		//return 0;
	}
	printf("%lld\n",ans);
	return 0;
}
```

考完想了下发现不需要二分，复杂度$O(N^2logN)$

(抢进度，有问题右转评论区

---

## 作者：hensier (赞：4)

本题属于 **最短路** 题，但较模板题还是有很大区别的。

我们可以视一条管道为一条边，然后对于每一条边保存连接的端点 $u,v$ 以及管道的花费 $c$ 和管道的流量 $f$。

本文中将 $c$ 的含义视为一条边的权值或两点之间的距离。

若视 Farmer John 的整个管道网络为一个图，则样例所表示的图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/i4a4gywb.png?x-oss-process=image/resize,m_lfit,h_276,w_252)

题目让我们求出从 $1$ 到 $n$ 中，$\dfrac{\min\{f_i\}}{\sum c_i}$ 的最大值。

从上图来看，我们只能选择 $1 \to 2 \to 3$ 的路径。这样，最大值为 $\dfrac{\min(4,3)}{2+5}=\dfrac{3}{7}$。所以输出为 $\lfloor 10^6 \times \dfrac{3}{7} \rfloor=428571$。

我们不妨在样例的基础上增加一条边：

![](https://cdn.luogu.com.cn/upload/image_hosting/2h84iw19.png?x-oss-process=image/resize,m_lfit,h_278,w_249)

附加新输入：

```plain
3 3
2 1 2 4
2 3 5 3
1 3 3 6
```

则我们应当考虑路径 $1 \to 2 \to 3$ 和 $1 \to 3$。刚才已经分析了 $1 \to 2 \to 3$ 路径的答案，即 $\dfrac{3}{7}$。而 $1 \to 3$ 路径的答案为 $\dfrac{\min(6)}{3}=2$。由于 $2 \gt \dfrac{3}{7}$，所以 $2$ 比 $\dfrac{3}{7}$ 更优，输出 $\lfloor 10^6 \times 2 \rfloor=200000$。

### $\text{Solution 1: 枚举}$

由于每个端点的 $f$ 都有可能成为所有的 $f$ 值的最小值，因而我们可对哪一条边的 $f$ 满足 $f=\min\{f_i\}$ 进行枚举。

保证 $\min\{f_i\}$ 后，再找最小的 ${\sum c_i}$ 即可，这样需要跑 $m$ 次 $\text{Dijkstra}$。

时间复杂度：$\mathcal O(m(n+m) \log n)$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,cnt,head[1001],dis[1001],F[1001]; // 记录所有边的 f 值
double ans; // 保存最优解的值
bool vis[1001];
struct edge
{
    int nxt,to,w,f;
}e[2001];
struct node
{
    int pos,dis;
    bool operator<(const node &x)const // 从小到大为优先队列默认排序方式
    {
        return dis>x.dis;
    }
    // 重载运算符，把 dis 小的放在前面，但由于 priority_queue 的性质，需要颠倒过来
};
void add(int u,int v,int w,int f) // 链式前向星存边
{
    e[++cnt].nxt=head[u];
    e[cnt].to=v;
    e[cnt].w=w; // 这里用 w 代替 c，符合常规习惯
    e[cnt].f=f;
    head[u]=cnt;
}
int dijkstra(int s,int minf)
{
    memset(dis,0x3f,sizeof(dis)); // 重置所有点到 1 的总距离（即所有 c 值总和）为 0x3f3f3f3f
    memset(vis,false,sizeof(vis)); // 多次 dijkstra 要清空 vis 数组
    dis[s]=0; // 源点距离赋值为 0
    priority_queue<node>Q;
    Q.push((node){s,0}); // 将源点的数据压入队列中
    while(Q.size())
    {
        int x=Q.top().pos; // 取队列元素所表示的端点编号
        Q.pop(); // 将该元素弹出
        if(vis[x])continue;
        vis[x]=true;
        // 判断是否被访问 + 标记访问
        for(int i=head[x];i;i=e[i].nxt) // 运用链式前向星的性质遍历
        {
            int y=e[i].to;
            if(e[i].f<minf)continue; // 如果该边的 f 值小于本次 dijkstra 所枚举的 minf 值，则跳过该边
            if(dis[y]>dis[x]+e[i].w) // 按照模板找最小距离
            {
                dis[y]=dis[x]+e[i].w;
                if(!vis[y])Q.push((node){y,dis[y]});
            }
        }
    }
    return dis[n];
}
int read()
{
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')
    {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x;
}
int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++)
    {
        int u=read(),v=read(),c=read(),f=read();
        add(u,v,c,f);
        add(v,u,c,f);
        // 无向图，需存两次边
        F[i]=f;
    }
    for(int i=1;i<=m;i++)ans=max(ans,1e6*F[i]/dijkstra(1,F[i]));
    // 把 ans 值赋值为当前枚举到的 minf 和 dijkstra 后得到最小距离的商的 1e6 倍
    printf("%d",int(ans)); // 下取整输出答案
    return 0;
}
```

### $\text{Solution 2: 标记}$

实际上，我们在 $\text{Dijkstra}$ 的过程中，可以在边的结构体再加一些变量来保存 $f$ 和 $c$，并用浮点类型记录 $\dfrac{\min\{f_i\}}{\sum c_i}$ 的值。

时间复杂度：$\mathcal O((n+m) \log n)$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,cnt,head[1001];
double dis[1001];
bool vis[1001];
struct edge
{
    int nxt,to,w,f;
}e[2001];
struct node
{
    int pos,f,dis;
    // f 保存遍历过程中，经过的 f 值中最小的
    double d;
    // 比前一份代码中多了 d 和 f 两个变量，实际上 d = f / dis
    bool operator<(const node &x)const
    {
        return d<x.d;
    }
    // 实际上应该让 d 更大的在前面，但与前面同理，需要颠倒
};
void add(int u,int v,int w,int f)
{
    e[++cnt].nxt=head[u];
    e[cnt].to=v;
    e[cnt].w=w;
    e[cnt].f=f;
    head[u]=cnt;
}
double dijkstra(int s)
{
    memset(vis,false,sizeof(vis));
    priority_queue<node>Q;
    Q.push((node){s,0x3f3f3f3f,0,0});
    // 源点编号为 s，而 f 的最小值应当设为 0x3f3f3f3f
    while(Q.size())
    {
        int x=Q.top().pos,f=Q.top().f,d=Q.top().dis;
        Q.pop();
        if(vis[x])continue;
        vis[x]=true;
        for(int i=head[x];i;i=e[i].nxt)
        {
            int y=e[i].to,nd=d+e[i].w,nf=min(f,e[i].f);
            // nd 记录编号 1 和 y 两个点之间的距离
            // nf 取当前 f 值和之前所有 f 值中最小的
            if(1.0*nf/nd>dis[y]) // 我们要求的是最大的 nf/nd，所以按照这个值的大小进行松弛
            {
                dis[y]=1.0*nf/nd;
                if(!vis[y])Q.push((node){y,nf,nd,dis[y]});
            }
        }
    }
    return dis[n];
}
int read()
{
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')
    {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x;
}
int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++)
    {
        int u=read(),v=read(),c=read(),f=read();
        add(u,v,c,f);
        add(v,u,c,f);
    }
    printf("%d",int(1e6*dijkstra(1))); // 直接输出跑一次 dijkstra 得到的值即可
    return 0;
}
```

祝大家 $\text{NOIP2020 RP++}$！

---

## 作者：newbie666 (赞：2)

# 此题最短路!
第一眼看到这道题目以为是到提高组里的网络流问题，其实不然，直接用普及组里的无敌的Dijkstra(没有负权边)也可以，但是仔细考虑了一下，算了时间复杂度：


时间复杂度：普通的堆优化Dijkstra为O(mlogn),此题1~1000都要跑一遍，再在基础之上乘以1000，logn不超过10，1000×10×1000=10^7，并不大，实在不放心，就用scanf或快读吧！
#### 思路：先从1到1000跑一遍，然后Dijkstra里的函数一样，只是后面要加一句:
```cpp
maxx=max(maxx,x*1000000/dis[n]);
```
具体我们看代码吧，~~因该没有不懂的人吧？~~
# Code:
```cpp
#include<bits/stdc++.h>
#define inf 1e9
using namespace std;
int n,m,head[2000005],maxx=-1e9,cnt,dis[2000005];
bool vis[2000005];
struct E {
	int next;
	int to;
	int c;
	int f;
} edge[2000005];
struct node {
	int dis;
	int pos;
	bool operator<(const node &x) const {
		return x.dis < dis; //重载运算符 
	}
};
void addedge(int u, int v, int c, int f) { //链式前向星
	cnt++;
	edge[cnt].c=c;
	edge[cnt].to=v;
	edge[cnt].next=head[u];
	edge[cnt].f=f;
	head[u]=cnt;
	return ;
}
priority_queue<node> q;
void Dijkstra() {
	for(int x=1; x<=1000; x++) {
		for(int j=1; j<=n; j++) { //初始化
			dis[j]=inf;
			vis[j]=0;
		}
		dis[1]=0; //自己和自己所在的点距离为0
		q.push((node) {0,1});
		/*
		node a;
		a.dis=0;
		a.pos=1;
		q.push(a);
		*/
		while(!q.empty()) {
			node tmp=q.top(); //取队首(注意：不是front
			q.pop();
			int u=tmp.pos;
			if (vis[u]) continue; //蓝白点思想
			vis[u]=1; //标记为蓝点
			for (int i=head[u]; i!=0; i=edge[i].next) { //遍历相邻点
				if(edge[i].f<x) continue; //流量最小
				int v=edge[i].to; //方便，免得下面又要写edge[i].to了
				if (dis[u]+edge[i].c<dis[v]) {
					dis[v]=dis[u]+edge[i].c;
					if(!vis[v]) {
						q.push((node) {dis[v], v}); //直接放入优先队列
						/*
						node x;
						x.dis=dis[v];
						x.pos=v;
						q.push(x);
						*/
					}
				}
			}
		}
		if(dis[n]!=inf) {
			maxx=max(maxx,x*1000000/dis[n]); //根据题意得知(输出10的6次方乘以最优解的值，并向下取整).
		}
	}

	return ;
}
int main() {

	cin>>n>>m;
	for (int i=1; i<=m; i++) {
		int a,b,c,f;
		cin>>a>>b>>c>>f;
		addedge(a,b,c,f);
		addedge(b,a,c,f); //存图 
	}
	Dijkstra(); //开始算法 
	cout<<maxx<<endl; //输出最终答案
	return 0;
}
```
### 谢谢大家！

---

## 作者：StupidSeven (赞：2)

## Subject
[题目传送门](https://www.luogu.com.cn/problem/P5837)

## Analysis
题意比较显然，就是要一条能使$ \frac{min(f_i)}{\Sigma{c_i}} $最大的路径，考虑用Dijkstra算法

然后枚举流量，每次更新答案即可

## Code
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
#define M 500010
#define INF 0x3f3f3f3f
inline int Readint(void){
    int s=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){s=s*10+c-48;c=getchar();}
    return s*f;
}
struct HeapNode{//堆优化Dijkstra
    int u,dist;
    bool operator<(const HeapNode &x)const{
        return dist>x.dist;
    }
};
struct Node{
    int u,v,w,d;
}Edge[M];
int n,m,u,v,w,d,ans;
int head[M],cnt;
int dis[M];
void addEdge(int u,int v,int w,int d){
    Edge[++cnt]=(Node){head[u],v,w,d};
    head[u]=cnt;
    return;
}
void Dijkstra(int start){//每次跑最小花费
    priority_queue<HeapNode> Q;
    memset(dis,INF,sizeof dis);
    dis[1]=0;
    Q.push((HeapNode){1,0});
    while(!Q.empty()){
        HeapNode now=Q.top();Q.pop();
        int u=now.u,dist=now.dist;
        if(dis[u]!=dist) continue;//如果松弛过了，就不继续操作了
        for(int i=head[u];i;i=Edge[i].u){
            if(Edge[i].d<start) continue;//最小的流量
            int v=Edge[i].v;
            if(dis[v]>dis[u]+Edge[i].w){
                dis[v]=dis[u]+Edge[i].w;
                Q.push((HeapNode){v,dis[v]});
            }
        }
    }
    if(dis[n]!=INF)
        ans=max(ans,start*1000000/dis[n]);//按题目更新最大值
    return;
}
signed main(void){
    n=Readint();m=Readint();
    while(m--){
        u=Readint();v=Readint();
        w=Readint();d=Readint();
        addEdge(u,v,w,d);//注意是双向边
        addEdge(v,u,w,d);
    }
    for(int i=1;i<=1000;i++)//枚举流量
        Dijkstra(i);
    printf("%d\n",ans);
    return 0;
}
```

祝大家CSP J/S rp++

---

## 作者：tiger2005 (赞：2)

### 做题全过程

在AC了Gold T3后听别人说这道题很水，就开始尝试。

我首先想到的是固定边，求1到起点的最短路，终点到N的最短路，加上边权就是经过这条边最小的花费了吧。

但是最短路中间可能会有流量更小的啊，怎么办啊……

等等！如果从大到小加边……

我打开显示器，手指又一次在键盘上飞跃。

P.S. : 我打Gold的时候没有中文题面，就按照Google所说的四舍五入做了，之后WA了5次才发现自己有多蠢——蠢到不会看round down是什么意思……

---

### 题意简述

给定一个无向图，保证1和N联通。

每一条边有流量和花费，现在要找到一种从1到N的路径，使得$\dfrac{min(f_i)}{\Sigma c_i}$最大。

---

### 做法

我们可以考虑每一条边，如果这条边是从1到N的路径中流量最小的边，那么我们只用知道1到起点的最短路$C_1$，终点到N的最短路$C_2$(这两个最短路都不能经过流量比这条边小的边)，那么我们可以知道：

$ans=\dfrac{f_i}{C_1+C_2+c_i}$

我们可以交换起点和终点从而得到两种不一样的$C_1$和$C_2$。这样做可以防止某一种方案的最短路有重合(想一想，为什么)。

那么，我们只用在流量从大到小的顺序下依次向图加边，在加一条边时计算答案，并且更新最短路。详见代码。

复杂度：$O(M^2logN)$(常数一般，由于取决于经常远大于点数的边数而跑的很慢)

Code:
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
using namespace std;
int len[1010][1010];
int N,M;
vector<int> sn[1010];
struct Pipe{
	int st,ed,fl,ct;
	bool operator < (const Pipe & a)const{
		return fl<a.fl;
	}
}A[1010];
int dis[1010];
bool vis[1010];
priority_queue<pair<int,int> > pq;
long long ans;
void dij(int u,int p){
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	dis[u]=0;
	pq.push(make_pair(0,u));
	while(!pq.empty()){
		pair<int,int> r=pq.top();
		pq.pop();
		if(vis[r.second])	continue;
		vis[r.second]=1;
		for(int i=0,j=sn[r.second].size();i<j;i++){
			int tt = sn[r.second][i];
			if(tt<p)	continue;
			int v = A[tt].st+A[tt].ed-r.second;
			if(dis[v]>dis[r.second]+A[tt].ct){
				dis[v]=dis[r.second]+A[tt].ct;
				pq.push(make_pair(-dis[v],v));
			}
		}
	}
	for(int i=1;i<=N;i++)	len[u][i]=dis[i];
}
int main(){
	freopen("pump.in","r",stdin);
	freopen("pump.out","w",stdout);
	scanf("%d%d",&N,&M);
	for(int i=0;i<M;i++)
		scanf("%d%d%d%d",&A[i].st,&A[i].ed,&A[i].ct,&A[i].fl);
	sort(A,A+M);
	for(int i=0;i<M;i++){
		sn[A[i].st].push_back(i);
		sn[A[i].ed].push_back(i);
	}
	memset(len,0x3f,sizeof(len));
	len[1][1]=len[N][N]=0;
	for(int i=M-1;i+1;i--){
		if(len[1][A[i].st]!=0x3f3f3f3f && len[N][A[i].ed]!=0x3f3f3f3f)
			ans=max(ans,(long long)((1.0*A[i].fl/(len[1][A[i].st]+A[i].ct+len[N][A[i].ed]))*1000000));
		if(len[N][A[i].st]!=0x3f3f3f3f && len[1][A[i].ed]!=0x3f3f3f3f)
			ans=max(ans,(long long)((1.0*A[i].fl/(len[N][A[i].st]+A[i].ct+len[1][A[i].ed]))*1000000));
		dij(1,i);dij(N,i);
	}
	printf("%lld\n",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
```

---

## 作者：pocafup (赞：2)

这题其实想法挺简单的，因为他只需要简单的把每个点的花费和流量用dp记下来就好了

1.怎么记：

首先考虑dp的状态。由于所在的点和流量都要记，所以dp开二维，一维记所在的点，另一维记去哪

```cpp
//dp[i][j] ==> i 是现在所在的点，j是流量
```

2.从哪开始

~~看题~~

3.转移方法

```cpp
//dp[要去的点][现在的流量和要去的流量的最小值] = dp[现在的点][现在的流量]+去的花费
```

4.输出

在终点，对于每个能到达的流量，最大值就是花费/流量

spfa代码：

```cpp
#include <iostream>
#include <algorithm>
#include <math.h>
#include <cstring>
#include <queue>
#include <fstream>

using namespace std;
#define pp pair<long long,long long>
#define mp make_pair
long long maxi = 0, n,m, tot=0,head[100001];
struct Edge{
  long long to, next,cost,flow;
}edge[100001];
void add(long long x, long long y,long long co, long long fl){
  edge[++tot].to = y;
  edge[tot].cost = co;
  edge[tot].flow = fl;
  edge[tot].next = head[x];
  head[x] = tot;
}
long long dp[1001][1001];
void dij(long long a, long long b){ // dijkstra
  dp[a][b] = 0;
  queue<pp> q;
  q.push(mp(a,b));
  while(!q.empty()){
    long long qf = q.front().first;
    long long qs = q.front().second;
    q.pop();
    for(long long i=head[qf];i;i=edge[i].next){
      long long t = edge[i].to, flo = edge[i].flow;
      if (dp[t][min(qs,flo)]>dp[qf][qs]+edge[i].cost){
        dp[t][min(qs,flo)] = dp[qf][qs]+edge[i].cost; //上面讲的转移
        q.push(mp(t,min(qs,flo)));
      }
    }
  }
}
int main(){
  // setIO("pump");
  cin >> n >> m;
  for (long long i=0;i<m;i++){
    long long a,b,c,d; cin >> a >> b >> c >> d; add(a,b,c,d); add(b,a,c,d);
  }
  memset(dp,0x3f3f3f3f,sizeof(dp)); 
  dij(1,1000);
  for (long long i=1;i<1000;i++){
    if (dp[n][i]>1e9) continue; //越界不？
    long long num = floor((double)(i*1e6)/(double)dp[n][i]); // 不越界计算
    maxi = max(maxi,num);
  }
  cout << maxi;
}

```


---

## 作者：zjjws (赞：1)

这里的流量是路径上流量最小的一条边的流量，然后有边数 $m\le10^3$，所以流量最多就只有 $10^3$ 种可能。

很快就想到枚举一条边的流量 $f_i$ 作为路径流量，然后用所有能承受这个流量的水管，跑一遍 SPFA 最短路求当前流量下的最小费用 $s$。

$$ans=max(ans,\frac{f_i\times 10^6}{s})$$

复杂度为 $\operatorname O(m\times \min(m,f_{\max}))$。

就是说如果 $f_i\le 10^3$ 保持不变， $m,n$ 增大到 $10^6$，仍然是可以这么跑的。

```cpp
#include <bits/stdc++.h>
#define LL long long
#define max(a,b) a>b?a:b
#define min(a,b) a<b?a:b
using namespace std;
const int MAX=1e3+3;
const int MAA=1000000;
struct milk
{
    int to,next,z;
    int f;//流量
}a[MAX<<1];
int h[MAX];
int d[MAX];
int val[MAX];
int vit[MAX];
bool vis[MAX];
int n,m;
int nam;
int ans;
inline void cheak(int f)
{
    memset(vit,0x3f,sizeof(vit));
    vit[1]=0;
    vis[1]=true;
    int head=1,tail=0;
    d[++tail]=1;
    for(;head<=tail;)
    {
        int x=d[head++];
        vis[x]=false;
        for(int i=h[x];i>0;i=a[i].next)
        if(a[i].f>=f)
        {
            int y=a[i].to;
            if(vit[y]>vit[x]+a[i].z)
            {
                vit[y]=vit[x]+a[i].z;
                if(!vis[y])d[++tail]=y,vis[y]=true;
            }
        }
    }
    if(vit[n]==0x3f3f3f3f)return;
    // printf("%d/%d\n",f,vit[n]);
    ans=max(ans,(f*MAA)/vit[n]);
    return;
}
inline void add(int x,int y,int z,int f){a[++nam].to=y;a[nam].next=h[x];a[nam].z=z;a[nam].f=f;h[x]=nam;}
LL rin()
{
    LL s=0;
    char c=getchar();
    bool bj=0;
    for(;(c>'9'||c<'0')&&c!='-';c=getchar());
    if(c=='-')c=getchar(),bj=true;
    for(;c>='0'&&c<='9';c=getchar())s=(s<<1)+(s<<3)+(c^'0');
    if(bj)return -s;
    return s;
}
int main()
{
    n=rin();m=rin();
    int x,y,z,f;
    for(int i=1;i<=m;i++)
    {
        x=rin();y=rin();z=rin();f=rin();
        add(x,y,z,f);
        add(y,x,z,f);
        val[i]=f;
    }
    sort(val+1,val+m+1);
    ans=0;
    int j;
    for(int i=1;i<=m;i=j+1)
    {
        for(j=i;j<m&&val[j+1]==val[i];j++);
        cheak(val[i]);
    }
    printf("%d",ans);
    return 0;
}
```


---

## 作者：x_miracle (赞：1)

### 核心算法 Dijkstra


------------
这题乍一看，像一道Dijkstra的裸题。其实不然。

这道题的不同之处就在于，这道题要求维护两个量，一个是流量，一个是花费。而Dijkstra的模板题，维护的是一个量，就是花费（路程）。

这道题中，流量，与花费的联系并不是必然的。也就是说，**不可以想当然的认为，最短路上的流量与花费的比就是所求的答案。**（答主就丧命与此）

那么，如何解决呢？

### 枚举，控制变量

------------

我们要维护两个值，则我们可以枚举其中一个值，然后再在去寻找对应的另一个值。

在这道题中，明显是控制流量好一些。（因为花费不好控制）

不断枚举流量，跑出其对应的花费，然后与先前的比较。最后得出最大的。

### 代码如下（细节说明见注释）
```cpp
#include <bits/stdc++.h>
#define MAXN 2000005
#define INF 0x3f3f3f3f
struct EDGE{int to,nxt,val,cost;}	e[MAXN];
//存图 
struct node 
{
	int pos,dis;
	bool operator < (const node & x) const	{ return x.dis < dis; }
	//重定向 
};
int adj[MAXN],cnt=0,vis[MAXN],dis[MAXN];
int n,m,ans=0;
std::priority_queue < node > q;
//堆优化Dijkstra 
void addedge(int u,int v,int c,int f){e[++cnt].to=v; e[cnt].nxt=adj[u]; e[cnt].val=f;	e[cnt].cost=c; adj[u]=cnt;}
//链式前向星 
void Dijkstra(int minflow)
{
	//记得先清空 ，初始化 
	std::memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;++i)	dis[i]=INF;
	while(!q.empty())	q.pop(); 
	//Dijkstra
	dis[1]=0;	q.push((node) {1,0});
	while(!q.empty())
	{
		node temp=q.top();	q.pop();
		int u=temp.pos;
		if(vis[u])	continue;	vis[u]=1;
		for(int i=adj[u];i;i=e[i].nxt)
		{
			int v=e[i].to;
			if(minflow>e[i].val) continue;	//控制最小的流量
			//如果下一个边的流量比最小的还小，就舍掉。 
			if(dis[v]>dis[u]+e[i].cost)
			{
				dis[v]=dis[u]+e[i].cost;
				if(!vis[v])
					q.push((node) {v,dis[v]});
			}
		}
	}
}
int main()
{
	std::scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		int u,v,c,f;
		std::scanf("%d%d%d%d",&u,&v,&c,&f);
		addedge(u,v,c,f);	addedge(v,u,c,f);
		//无向图 
	}
	for(int minflow=1;minflow<=1000;++minflow)//枚举 
	{
		Dijkstra(minflow);
		if(dis[n]!=INF) ans=std::max(ans,minflow*1000000/dis[n]);
	}
	std::printf("%d",ans);
	return 0;
}
```


---

## 作者：Fairicle (赞：1)

讲一下我的做法吧

个人认为这道题只是dijkstra的变形

以1为原点跑单源最短路

我们维护两个数组：一个是dis数组，就是源点到当前点的cost；

一个是mf数组，指的是原点到当前点的最小流

每次取出**路径花费与路径流量之比最小**的即可，这个可以用priority_queue实现（将题目要求的路径流量与路径花费之比最大转换一下）

My code is below:
```cpp
#include"bits/stdc++.h"
using namespace std;
inline int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x;
}
int wl;
int head[2010];
struct node{
	int to,nxt,cost,flow;
}star[2010];
inline void add(int from,int to,int cost,int flow){
	wl++;
	star[wl].cost=cost;
	star[wl].flow=flow;
	star[wl].to=to;
	star[wl].nxt=head[from];
	head[from]=wl;
}
int n,m;
int mf[2010];
int vis[2010];
int dis[2010];
typedef pair<long double,int> p;//开double或者long double都行，别开int
priority_queue<p,vector<p>,greater<p> > q;
inline void dijkstra(){
	for(int i=1;i<=n;++i)
	dis[i]=100000000;
	dis[1]=0;
	q.push(make_pair(0,1));
	memset(mf,127,sizeof(mf));
	while(!q.empty())
	{
		int u=q.top().second;
		vis[u]=1;
		q.pop();
		for(int i=head[u];i;i=star[i].nxt)
		{
			int v=star[i].to;
			if(vis[v]) continue;
			int nowflow=star[i].flow,nowcost=star[i].cost;
			int mini=min(nowflow,mf[u]);
			if((dis[u]+nowcost)*mf[v]<dis[v]*mini||mf[v]==2139062143)//进行更新
			{
				mf[v]=mini;//这里不用把mf[u]置为mini，因为u还要更新别的点
				dis[v]=dis[u]+nowcost;
				q.push(make_pair(dis[v]/mf[v],v));
			}
		}
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=m;++i)
	{
		int a,b,c,d;
		a=read(),b=read(),c=read(),d=read();
		add(a,b,c,d),add(b,a,c,d);
	}
	dijkstra();
	//cout<<mf[n]<<" "<<dis[n]<<endl;
	cout<<mf[n]*1000000/dis[n];
	return 0;
}
```
这道题很练耐心有些地方写错了很难找，特别是Dijkstra部分

时间复杂度O（NlogN）

还跑得挺快，不吸氧rk2，吸氧目前并列rk1

---

## 作者：xixiup (赞：0)

## 思路分享

对于这道题，我们可以发现 $n$ 与 $m$ 的范围都很小，所以我们可以~~考虑枚举~~。

由于这道题的总流量 $Flow$ 是 $\min\limits_{i \in E} f_i$，所以我们可以枚举总流量 $flow$。

由于最后的答案是 $\dfrac{\sum\limits_{i \in E} c_i}{\min\limits_{i \in E} f_i}$，所以在 $flow$ 一定的情况下我们要使得 $\sum\limits_{i \in E} c_i$ 最小，所以我们可以在所有 $f_i \geqslant flow$ 的边上跑一遍最短路。

最后将所有的答案取一个 $\min$ 就可以了。

## 代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1010,maxm=2010;
int n,m,dis[maxn],vis[maxn],ansx,ansy;
int cnt,bg[maxn],ne[maxm],to[maxm],le[maxm],fl[maxm];
priority_queue<pair<int,int> >q;
void add(int x,int y,int z,int k){
	cnt++;
	ne[cnt]=bg[x];
	to[cnt]=y;
	le[cnt]=z;
	fl[cnt]=k;
	bg[x]=cnt;
}
void dijkstra(int flow){//最短路
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	dis[1]=0;
	q.push(make_pair(0,1));
	while(!q.empty()){
		int x=q.top().second;
		q.pop();
		if(vis[x]==1){
			continue;
		}
		vis[x]=1;
		for(int i=bg[x];i;i=ne[i]){
			int y=to[i];
			if(fl[i]<flow){
				continue;
			}
			if(dis[x]+le[i]<dis[y]){
				dis[y]=dis[x]+le[i];
				q.push(make_pair(-dis[y],y));
			}
		}
	}
	if(dis[n]==0x3f3f3f3f){
		return;
	}
	if(1.*ansx/ansy<1.*flow/dis[n]){
		ansx=flow;
		ansy=dis[n];
	}
}
int main(){
	freopen("milk.in","r",stdin);
	freopen("milk.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y,z,k;
		scanf("%d%d%d%d",&x,&y,&z,&k);
		add(x,y,z,k);
		add(y,x,z,k);
	}
	ansx=0;ansy=1;
	for(int i=1;i<=1000;i++){//枚举flow
		dijkstra(i);
	}
	printf("%.0lf",floor(1000000.*ansx/ansy));//输出答案
	return 0;
}

```


---

## 作者：过往梦魇之殇 (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/P5837)

**思路简述：**

先建一个无向图，

然后枚举$1\ldots1000$的流量，

每次跑一遍最短路，

最后取 流量$\times1000000/dis[n]$的最大值，输出即可。

**注意**每一遍最短路前都要清空一下数组。

------------

**代码展示：**

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
const int maxn=4e3+10;
const int INF=1e9+7;
queue<int>Q;
int n,m,head[maxn],dis[maxn],vis[maxn],cnt,ans;
struct node{
    int to,nxt,val,w;
}edge[maxn];
void add(int u,int v,int w,int val){
    edge[++cnt].to=v;
    edge[cnt].nxt=head[u];
    edge[cnt].val=val;
    edge[cnt].w=w;
    head[u]=cnt;
}
int main(){
    scanf("%d%d",&n,&m);
    for(re int i=1;i<=m;++i){
        int X,Y,W,F;
        scanf("%d%d%d%d",&X,&Y,&W,&F);
        add(X,Y,W,F);
        add(Y,X,W,F);
    }
    for(re int i=1;i<=1000;++i){
        for(re int j=1;j<=n;++j){
            dis[j]=INF;
            vis[j]=0;
        }
        dis[1]=0;
        vis[1]=1;
        Q.push(1);
        while(!Q.empty()){
            int now=Q.front();
            Q.pop();
            vis[now]=0;
            for(re int k=head[now];k;k=edge[k].nxt){
                if(edge[k].val<i){
                    continue;
                }
                if(dis[now]+edge[k].w<dis[edge[k].to]){
                    dis[edge[k].to]=dis[now]+edge[k].w;
                    if(!vis[edge[k].to]){
                        vis[edge[k].to]=1;
                        Q.push(edge[k].to);
                    }
                }
            }
        }
        if(dis[n]!=INF){
            ans=max(ans,i*1000000/dis[n]);
        }
    }
    printf("%d\n",ans);
    return 0;
}
```
>$Thanks$ $For$ $Watching!$

---

