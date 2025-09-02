# [USACO04OPEN] Cave Cows 1

## 题目描述

很少人知道其实奶牛非常喜欢到洞穴里面去探险。

洞窟里有 $ N $ ( $ 1 \leq N \leq 100 $ )个洞室，由 $ M $ ( $ 1 \leq M \leq 1000 $ )条双向通道连接着它们。每对洞室间至多只有一条双向通道，有 $ K $ ( $ 1 \leq K \leq 14 $ )个洞室，里面放有1捆干草．牛吃1捆干草，体重指数就会增加1。

贪吃的贝茜要到洞窟里面探险，她希望能吃尽量多的干草，但每条通道有一个宽度阈值，如果体重指数超过相应的阈值，贝茜就会被卡住。

她从洞窟1出发，体重指数为0。在洞里溜达一圈后，她要返回洞窟1。

那她最多能吃多少捆干草呢？注意，贝茜经过一个洞室，不一定非要吃掉里面的干草。

## 样例 #1

### 输入

```
6 7 5
1
2
3
4
5
1 2 3
3 6 2
6 2 10
2 4 1
5 1 1
4 5 1
1 6 1```

### 输出

```
4```

# 题解

## 作者：_蒟蒻__ (赞：16)

看到不少大佬都用状压DP过的，

但是，

凭良心估计一下自己的实力，发现本蒟蒻并不会啊……

重新思考一下，设dis[i][j]表示从i到j的最短边（限制收集）的长度。N<=100,可以用floyd处理。

最后贪心一下，把有干草的点i按照dis[1][i]排序，从最小的开始选。

蒟蒻水平低，还望各位大佬斧正。

```cpp
#include<cstdio>
#include<algorithm>
#define res register int
using namespace std;

const int inf=23333333;
int n,m,k;
int dis[110][110];
int a[110],b[110];

template<class T>
inline void read(T& v)
{
    char c=getchar();v=0;
    while(c<'0'||c>'9'){c=getchar();}
    while(c>='0'&&c<='9'){v=(v<<3)+(v<<1)+(c^'0');c=getchar();}
}

inline void floyd()
{	
	for(res i=1;i<=n;i++)dis[i][i]=inf;
	
	for(res t=1;t<=n;t++)
	 for(res i=1;i<=n;i++)
	  for(res j=1;j<=n;j++)
	  {
	  	  dis[i][j]=dis[j][i]=max(dis[i][j],min(dis[i][t],dis[t][j]));
			//考虑是否要从t点绕行（因为是无向图，且无次数限制，可以随便走） 
	  }
}

inline int solve()
{
	for(res i=1;i<=k;i++)b[i]=dis[1][a[i]];
	
	sort(b+1,b+k+1);
	
	int ans=0;
	
	for(res i=1;i<=k;i++)//贪心在这里 
	if(b[i]>ans)//当前已经拥有ans个，判断是否能够从这走。 
	{
		ans++;
	}
	
	return ans;
}

int main()
{	
	read(n),read(m),read(k);
	
	for(res i=1;i<=k;i++)
		read(a[i]);
	
	int x,y,w;
	for(res i=1;i<=m;i++)
	{
		read(x),read(y),read(w);
		dis[x][y]=dis[y][x]=max(dis[x][y],w);
	}
	
	floyd();
	
	printf("%d",solve());
	
	return 0;
}
```


---

## 作者：KaDa_Duck (赞：9)

题面意思大家应该都懂吧，我这里直接说思路吧。
首先连通图，双向通道这字眼首先就能一下想到是图论吧（~~其实是没学过状压~~）

根据题意跑一遍floyed，然后打个擂台就好啦。

dis[i][j]表示从i到j路径（能跑的）中宽度最大的。

**重点**说一下floyed里面的吧。

```cpp
dis[i][j]=max(dis[i][j],min(dis[i][k],dis[k][j]));
```
千万不要想成**dis[i][k]+dis[k][j]**。 它说每条路有一个宽度阈值，求最多吃的草。
所以我们只要求出每条路的最大阈值（~~你也可以理解成跑一遍最长路~~） 

至于min 因为初始化的原因想一下
1. 如果自己跑到自己显然对答案没有贡献所以我们赋一个极大值取min筛掉即可。
2. 如果没有这条路不存在，显然是没有阈值的，那么我们赋值为0就可以解决啦。
代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int dis[120][120];
int n,m,T,ans;//ans:当前吃了多少草
int f[120],a[120];
inline int read()//快读
{
	int Num=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9') {Num=Num*10+ch-'0'; ch=getchar();}
	return Num*f;
}
template <typename T>
inline void fprint(T x)//快输
{
    if(x < 0)
    {
        putchar(45);
        x=-x;
    }
    if(x>9)
    {
        fprint(x/10);
    }
    putchar(x%10+48);
}
inline bool cmp(int x,int y) {return x<y;}//sort从小到大排序
int main()
{
	n=read(),m=read(),T=read();
	for(int i=1;i<=T;i++) a[i]=read();
	for(int i=1;i<=n;i++) dis[i][i]=1002200;//自己到自己赋值极大值
	for(int i=1;i<=m;i++)
	{
		int x=read(),y=read(),z=read();
		dis[x][y]=z,dis[y][x]=z;
	}
	for(int k=1;k<=n;k++)//floyed
	for(int i=1;i<=n;i++)
	for(int j=i;j<=n;j++)
	dis[i][j]=max(dis[i][j],min(dis[i][k],dis[k][j]));
	for(int i=1;i<=T;i++) f[i]=dis[1][a[i]];//从起点到有草的最大阈值
	sort(f+1,f+1+T,cmp);
	for(int i=1;i<=T;i++) ans<f[i]?ans++:1;//如果ans<f[i] 吃的草加一
	fprint(ans);
	return 0;
}
```


------------
~~我的第一篇题解希望能过~~


---

## 作者：LJC00118 (赞：8)

简单 $ bfs $

发现 $ k \le 14 $，可以状压，所以我们用 $ vis[i][j] $ 表示当前在 $ i $ 这个点，已经吃掉的干草的状态为 $ j $ 可不可行，直接 $ bfs $ 即可


```cpp
#include <bits/stdc++.h>
#define Fast_cin ios::sync_with_stdio(false), cin.tie();
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> " << endl;
using namespace std;

typedef unsigned long long ull;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') fu = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

const int N = 105, M = 1005;

struct Edge { int u, v, next, val; } G[M << 1];
struct ele { int x, y; ele(int a = 0, int b = 0) : x(a), y(b) {} };

queue <ele> q;
bool vis[105][1 << 14];
int head[N], cnt[1 << 14], hav[N];
int T, n, m, k, tot;

inline void addedge(int u, int v, int val) {
    G[++tot] = (Edge) {u, v, head[u], val}, head[u] = tot;
    G[++tot] = (Edge) {v, u, head[v], val}, head[v] = tot;
}

inline int lowbit(int x) { return x & -x; }

int main() {
    for(register int i = 1; i < (1 << 14); i++) cnt[i] = cnt[i ^ lowbit(i)] + 1;
    read(n); read(m); read(k);
    for(register int i = 1; i <= k; i++) { int a; read(a); hav[a] = i; }
    for(register int i = 1; i <= m; i++) {
        int a, b, c;
        read(a); read(b); read(c);
        addedge(a, b, c);
    }
    vis[1][0] = 1; q.push(ele(1, 0));
    if(hav[1]) vis[1][1 << (hav[1] - 1)] = 1, q.push(ele(1, 1 << (hav[1] - 1)));
    while(!q.empty()) {
        ele t = q.front(); q.pop();
        int u = t.x, zt = t.y;
        for(register int i = head[u]; i; i = G[i].next) {
            int v = G[i].v;
//				fprintf(stderr, "zt = %d\n", zt);
            if(G[i].val < cnt[zt]) continue;
            if(!vis[v][zt]) vis[v][zt] = 1, q.push(ele(v, zt));
            if(hav[v] && !(zt & (1 << (hav[v] - 1))) && !vis[v][zt ^ (1 << (hav[v] - 1))]) {
                vis[v][zt ^ (1 << (hav[v] - 1))] = 1;
                q.push(ele(v, zt ^ (1 << (hav[v] - 1))));
            }
        }
    }
    int ans = 0;
    for(register int i = 0; i < (1 << 14); i++) if(vis[1][i]) ans = max(ans, cnt[i]);
    print(ans, '\n');
    return 0;
}
```

---

## 作者：COUPDETAT (赞：3)

# 贪心+floyd
## 这道题很显然 先求一遍多源最短路
### 1.记录有稻草的点
### 2.floyd（求当前路径最小限制的最大值）
### 3.把1到(有稻草的点)的限制进行排序
### 4.从小到大选择 如果比当前体重大就ans++
```cpp
#include<bits/stdc++.h>
using namespace std;
int d[101],dd[101],mp[101][101];
int main()
{
	int n,m,c;
	cin>>n>>m>>c;
	for(int i=1;i<=c;i++)
	{
		cin>>d[i];
	}
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		cin>>x>>y>>z;
		mp[x][y]=z;
		mp[y][x]=z;
	}
	for(int i=1;i<=n;i++)mp[i][i]=1433223;
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				mp[i][j]=max(mp[i][j],min(mp[i][k],mp[k][j]));
	int ans=0;
	for(int i=1;i<=c;i++)
		dd[i]=mp[1][d[i]];
	sort(dd+1,dd+1+c);
	for(int i=1;i<=c;i++)
	{
		if(dd[i]>ans)
		ans++;
	}
	cout<<ans;
}


```


---

## 作者：Gaode_Sean (赞：1)

首先可以用 floyd 预处理出 $i \sim j$ 所有路径中宽度限制的最大值，记为 $f_{i,j}$（这样显然会更优）。

将第 $i$ 堆干草的位置记为 $a_i$。

由此我们将 $f_{1,a_i}(1 \leq i \leq n)$ 从小到大排序，同时记录吃掉的干草数。记为 $s$。当 $s<f_{1,a_i}$ 时，选择吃下第 $i$ 堆干草。

## AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=101,T=15;
int f[N][N];
int n,m,t,a[T],mn=1e9,ans;
int main()
{
	scanf("%d%d%d",&n,&m,&t);
	for(int i=1;i<=t;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) f[i][i]=1e9;
	while(m--){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		f[x][y]=f[y][x]=z;
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++) if(i!=j) f[i][j]=max(f[i][j],min(f[i][k],f[k][j]));
		}
	}
	for(int i=1;i<=t;i++) a[i]=f[1][a[i]];
	sort(a+1,a+1+t);
	//reverse(a+1,a+1+t);
	for(int i=1;i<=t;i++) if(a[i]>=ans+1) ans++;
	printf("%d",ans);
	return 0;
}
```

---

## 作者：苹果蓝17 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P5096)

[更好的阅读体验](https://www.cnblogs.com/Appleblue17/p/14838018.html)

~~这题给的数据范围也太弱了吧，为啥 k 给得像状压一样……~~

#### 题意简述

+ $n$ 个点 $m$ 条边的无向图，边有边权，只有当体积小于边权时才能通过。
+ 有 $k$ 个特殊点上放有食物，吃掉可以使体积加一（经过该点时可以选择不吃）。

+ 初始时体积为 $0$ ，要求从 $1$ 号点出发，最后回到 $1$ 号点，可以重复经过一条边。求最多能吃掉多少食物。
+ $n \leq 100$，$m \leq 1000$，$k \leq 14$。

#### 题目分析

记 $w(x,y)$ 表示能从 $x$ 走到 $y$ 的最大体积。

由于边可以重复经过，事实上**每一个特殊点可以独立考虑**。

也就是说，贝茜的路线一定可以变为：从 $1$ 号点出发，到达某个特殊点并吃掉食物，再回到 $1$ 号点，并将这个过程重复 $ans$ 次。

理由很简单。假设贝茜走到了特殊点 $x$ 吃掉食物后体积为 $p$，又走到特殊点 $y$ 吃掉食物，那么有 $w(x,y) \geq p, w(y,1)\geq p+1$（否则就再也走不回 $1$ 号点了）。

因此 $w(x,1) \geq p$，将 $x \rightarrow y$ 变为 $x \rightarrow 1 \rightarrow y$  是合法的。

那么接下来的事情就是算出 $w(1,t)$，然后每一次贪心选取合法且 $w(1,t)$ 最小的特殊点吃掉。这一步的排序需要 $O(k\log k)$ 的时间复杂度。

考虑对每个点 $t$ 计算 $w(1,t)$，显然这样的路径一定在最大生成树上，建出树 dfs 一次即可。这一步最小生成树视实现需要 $O(m \log m)$ 或 $O(m \log n)$ 的时间复杂度。

总时间复杂度 $O(k \log k+m \log m)$ 或 $O(k \log k+m \log n)$，可以~~非常非常轻松地~~通过本题。

~~直接最优解……~~

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=110,M=1100;
struct nod{
	int to,nxt,w;
}e[N*2];
int head[N],cnt;
void add(int u,int v,int w){
	e[++cnt].to=v;
	e[cnt].w=w;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
int n,m,k;
int p[15],q[15];
int dis[110];

struct abc{
	int u,v,w;
}edg[M*2];
bool operator <(abc x,abc y){
	return x.w>y.w;
}

int fa[N];
int getf(int x){
	if(x==fa[x]) return x;
	return fa[x]=getf(fa[x]);
}
bool merge(int x,int y){
	int fx=getf(x),fy=getf(y);
	if(fx==fy) return 0;
	fa[fx]=fy;
	return 1;
}

void dfs(int u,int fa,int mn){
	dis[u]=mn;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa) continue;
		dfs(v,u,min(mn,e[i].w));
	}
}

int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++) scanf("%d",&p[i]);
	for(int i=1;i<=m;i++) scanf("%d%d%d",&edg[i].u,&edg[i].v,&edg[i].w);
	sort(edg+1,edg+m+1);
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=m;i++){
		int u=edg[i].u,v=edg[i].v;
		if(merge(u,v)) add(u,v,edg[i].w),add(v,u,edg[i].w);
	}
	//最大生成树 
	dfs(1,0,1e9);
	for(int i=1;i<=k;i++) q[i]=dis[p[i]]-1;
	sort(q+1,q+k+1);
	int nw=0,ans=0;//现在的体积 / 答案 
	for(int i=1;i<=k;i++)
		if(nw<=q[i]) nw++,ans++;//贪心 
	cout<<ans;
}
```

---

## 作者：cwfxlh (赞：0)

# [P5096](https://www.luogu.com.cn/problem/P5096)
## 题目分析
本题要求最多能吃多少捆干草，看上去就是在图上跑一个搜索，遍历所有可行的路径，最后得出最大答案，相信各位看了这道题都会有这个思路。   

为了实现这个搜索，我们可以使用状态压缩来压缩所有的干草状态（是否被吃掉），来维护当前的状态。搜索的内容如下：记录当前位置，当前干草状态，体重，然后遍历所有边，看能否过去，同时，如果这个洞穴有干草，那么就要考虑吃不吃这个洞穴的干草。     

但这样时间要爆，所以可以搞一个优化。记录的状态有位置与干草状态（体重与干草状态是相关的，所以可以忽略），所以我们可以写一个数组，记录每个状态（位置加干草）是否达到过。    

然后没了，写一个 BFS 即可。   
上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,vis[103][20003],fd[103],k1,k2,k3;
int tot,Q[6000003][3],head[10003],ans;
struct Edge
{
	int st;
	int ed;
	int val;
	int nxt;
}E[1000003];
int totE=1;
void addEdge(int st,int ed,int val)
{
	totE++;
	E[totE].st=st;
	E[totE].ed=ed;
	E[totE].val=val;
	E[totE].nxt=head[st];
	head[st]=totE;
	return;
}
void addQ(int now,int zt,int wt)
{
	if(vis[now][zt])return;
	vis[now][zt]=1;
	tot++;
	Q[tot][0]=now;
	Q[tot][1]=zt;
	Q[tot][2]=wt;
	return;
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k;i++)
	{
		scanf("%d",&k1);
		fd[k1]=i;
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&k1,&k2,&k3);
		addEdge(k1,k2,k3);
		addEdge(k2,k1,k3);
	}
	addQ(1,0,0);
	for(int i=1;i<=tot;i++)
	{
		k1=Q[i][0];
		k2=Q[i][1];
		k3=Q[i][2];
		if(k1==1)
		{
			if(fd[1]==0)
			{
				ans=max(ans,k3);
			}
			else
			{
				if((1<<(fd[1]-1))&k2)ans=max(ans,k3);
				else ans=max(ans,k3+1);
			}
		}
		for(int j=head[k1];j!=0;j=E[j].nxt)
		{
			if(k3>E[j].val)continue;
			addQ(E[j].ed,k2,k3);
		}
		if(fd[k1]==0)continue;
		if(((1<<(fd[k1]-1))&k2)!=0)continue;
		for(int j=head[k1];j!=0;j=E[j].nxt)
		{
			if(k3+1>E[j].val)continue;
			addQ(E[j].ed,(k2+(1<<(fd[k1]-1))),k3+1);
		}
	}
	printf("%d",ans);
	return 0;
}
```



---

## 作者：_edge_ (赞：0)

有很多神仙用状压过去了，可惜本蒟蒻不会状压。

题面几个信息要特别注意一下。

1. **里面放有 1 捆干草**，也就是每一个房间仅仅只有一捆干草。

2. **她从洞窟1出发，体重指数为0。在洞里溜达一圈后，她要返回洞窟1。** 一开始体重为 $0$，出发点在 $1$，结束点也只能在 $1$。

这些限制条件可以让我们比较容易地处理这道题目。

先不说用什么做法做，想一想怎么样可以找出合法的情况？

合法的情况也就是当前到达它这个节点的时候，**体重不能超过中间的最小边**，就比如说 $1 \rightarrow 2$ 权值为 $3$ ，在不考虑其它边的情况下，体重不能超过 $2$。

欸？是不是觉得很奇怪？为什么体重不能超过 $2$ 而不是 $3$ 呢？

原因显然，如果体重为 $3$ 的情况下，走过来吃完之后就不能走回来了，那如果不吃呢？~~你没事去走一趟还不吃东西是不是闲着没事干？~~，不走的话对答案没有产生任何的贡献，所以就不用走了。

那么如果说处理好了所有点到所有点的边不能超过某一个值了之后，该怎么办？

那么可以贪心地考虑一下，**每一个房间仅仅只有一捆干草**，如果当前可以走到一个边权最小的，那么选择第 $2$ 小和第 $3$ 小的肯定不是最优的。

为什么？

因为如果选择了第 $2$ 小，假设可以选择第 $3$ 小，那么必然选择了最小的也可以选第 $3$ 小的，(先不考虑重复的影响)，因为选择了最小的对体重的影响是 $+1$，那么如果最坏情况第 $2$ 小的边权刚好是体重 $+1$ ，那么第 $3$ 小也只能是体重 $+2$，于是就可以选择第 $3$ 小的了。

上面这种考虑的是最坏情况，最好情况是三个都选，所以可以从最小的开始贪心的选择。

那么回过头来考虑第一个问题，怎么处理合法情况，有神仙用了 floyd 然而本蒟蒻觉得 $O(n^3)$ 太慢了，所以就考虑使用单源求最短路径。

那么 …… 由于最后一次肯定是要回来的，所以从 $1$ 开始跑一遍最短路，然后求出到达某一个点路径的最小边并且让它最大化，求出来的数$-1$就是它所能承受的最大体重。

然后就可以愉快的进行一个贪心了！

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
const int INFN=105;
const int INFM=1005;
int n,m,k,head[INFN],tot,a[INFN];
struct _node_edge {int to_,next_,disv_;} edge[INFM<<1];
void add_edge(int x,int y,int z) {
        edge[++tot]=(_node_edge){y,head[x],z};
        head[x]=tot; return;
}
queue <int> q;
int dis_[INFN];
bool vis[INFN];
int fzx_min(int x,int y) {
        return x<y ? x : y;
}
void SPFA(int s) {
        memset(dis_,-63,sizeof dis_);
        memset(vis,false,sizeof vis);
        dis_[s]=1e9; vis[s]=true; q.push(s);//一开始要设成无穷大，因为不管怎么样都可以到达。
        while (q.size()) {
                int x=q.front(); q.pop(); vis[x]=false;
                for (int i=head[x]; i; i=edge[i].next_) {
                        if (dis_[edge[i].to_]<fzx_min(dis_[x],edge[i].disv_)) {
                                dis_[edge[i].to_]=fzx_min(dis_[x],edge[i].disv_);
                                if (!vis[edge[i].to_]) {
                                        vis[edge[i].to_]=true;
                                        q.push(edge[i].to_);
                                }
                        }
                }
        }
        return;
}
int ans[INFN],ans1;
signed main()
{
        scanf("%d %d %d",&n,&m,&k);
        for (int i=1; i<=k; i++) scanf("%d",&a[i]);
        for (int i=1; i<=m; i++) {
                int x=0,y=0,z=0; scanf("%d %d %d",&x,&y,&z);
                add_edge(x,y,z); add_edge(y,x,z);
        }
        SPFA(1);
        for (int i=1; i<=k; i++)
                ans[++ans1]=dis_[a[i]];
        sort(ans+1,ans+ans1+1);
        int sum=1;
        for (int i=1; i<=ans1; i++) {
                // cout<<ans[i]<<endl;
                if (ans[i]<=sum) continue; sum++;//这里没减一，直接用等于判掉。
        }
        cout<<sum<<"\n";
        return 0;
}
```

**谢谢观赏！**

---

