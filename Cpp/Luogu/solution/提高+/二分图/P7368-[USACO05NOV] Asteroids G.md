# [USACO05NOV] Asteroids G

## 题目描述

贝茜想在 $N\times N$ 的网格中驾驶她的宇宙飞船。网格中有 $K$ 个小行星。要使驾驶过程愉快，就必须把这些小行星全部消除。

贝茜有一个武器，可以以一个单位代价消除一行或一列的全部小行星。贝茜想问你，要把所有小行星都消除的最小代价是多少。

## 说明/提示

#### 样例解释：

样例的图为（`X` 为小行星）：

```text
X.X
.X.
.X.
```

贝茜可以分别消除第一行和第二列的小行星。

---

#### 数据范围：

对于 $100\%$ 的数据，$1 \leq N \leq 500$，$1 \leq K \leq N \times N$。

## 样例 #1

### 输入

```
3 4
1 1
1 3
2 2
3 2

```

### 输出

```
2```

# 题解

## 作者：Silence_water (赞：30)

[题目传送门](https://www.luogu.com.cn/problem/P7368)

> 二分图最小覆盖的模型特点是：每条边有 $2$ 个端点，二者至少选择一个。我们不妨称之为 "$2$ 要素"。
> 
>  ——李煜东《算法竞赛进阶指南》

我们来寻找一下本题的 "$2$ 要素"：

每个小行星可以通过本行的武器或每列的武器被消除，二者至少选择一个。

我们将每个小行星的 $x$ 坐标与 $y$ 坐标看成一条边的两个端点。那么形成的这张图中的任意一条边都需要有至少一个端点有武器摆放。

换句话说，问题就是要求出一个最小的点集 $S$，使得图中任意一条边都有至少一个端点属于 $S$。这个问题被称为**二分图的最小点覆盖**。

故求消除所有小行星的最小代价就相当于求这张二分图的最小点覆盖数。

根据 König 定理，二分图最小点覆盖包含的点数等于二分图最大匹配包含的边数。

直接用匈牙利算法跑即可。

```cpp
bool dfs(int u)
{
	for(int i=1;i<=n;i++)
	{
		if(!e[u][i]||vis[i])continue;
		vis[i]=true;
		if(!match[i]||dfs(match[i]))
		{
			match[i]=u;
			return true;
		}
	}
	return false;
}
int solve()
{
	memset(match,0,sizeof(match));
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		memset(vis,false,sizeof(vis));
		if(dfs(i))cnt++;
	}
	return cnt;
}
```

upd 2023/1/3：根据评论区反馈修正了错误。

---

## 作者：RuSun (赞：21)

### 广告

[我的博客](https://rusun.blog.luogu.org/#)


### 好像没有 dinic ， 我来水一发！

这道题可以当做最小权覆盖集的模板题。

一开始对于建边没有搞清楚， 以为是把同一列同一行的所有点连起来， 但是又感觉模型没对， 于是看了题解。

这个问题的本质： 对于一个存在的点， 其本质就是要么在这一行上消灭， 要么就是在这一列上消灭， 即从中选择， 而费用都是 1 ， 就可以用最小权覆盖集解了。

看到题解中有人说邻接表要 MLE ， 这是在扯淡。

点的个数最大为 $n * 2 + 2$ 。

边的个数最大为 $n + n * n + n$ 。

随便开， 完全没问题。

### 建图

- 编号：将横坐标编号为 $1-n$ ， 将纵坐标编号为 $n + 1 - n + n$ ；

- 将所有的横坐标的点和源点连接， 容量为 1 （因为这个题每消灭一次费用为 1 ， 其实还可以再难一些， 将消灭不同的行或列的费用不一样， 那么就可以体现 dinic 算法的优势了）；

- 将所有的纵坐标的点和汇点连接， 容量为 1 （同理）；

- 对于每一个点， 将其横坐标与纵坐标的点连接， 容量为 INF （即不可割）。

### 完整代码

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <climits>
#define INF INT_MAX
using namespace std;
const int N = 1e3 + 10, M = 6e5 + 10;
int n, k, st, ed, d[N], cur[N];
int idx = -1, hd[N], nxt[M], edg[M], wt[M];
bool bfs()
{
    for (int i = st; i <= ed; i++)
        d[i] = -1;
    d[st] = 0;
    cur[st] = hd[st];
    queue <int> q;
    q.push(st);
    while (!q.empty())
    {
        int t = q.front();
        q.pop();
        for (int i = hd[t]; ~i; i = nxt[i])
            if (d[edg[i]] == -1 && wt[i])
            {
                cur[edg[i]] = hd[edg[i]];
                d[edg[i]] = d[t] + 1;
                if (edg[i] == ed)
                    return true;
                q.push(edg[i]);
            }
    }
    return false;
}
int find(int x, int limit)
{
    if (x == ed)
        return limit;
    int res = 0;
    for (int i = cur[x]; ~i && res < limit; i = nxt[i])
    {
        cur[x] = i;
        if (d[edg[i]] == d[x] + 1 && wt[i])
        {
            int t = find(edg[i], min(wt[i], limit - res));
            if (!t)
                d[edg[i]] = -1;
            wt[i] -= t;
            wt[i ^ 1] += t;
            res += t;
        }
    }
    return res;
}
int dinic()
{
    int res = 0, flow;
    while (bfs())
        while (flow = find(st, INF))
            res += flow;
    return res;
}
void add(int x, int y, int z)
{
    nxt[++idx] = hd[x];
    hd[x] = idx;
    edg[idx] = y;
    wt[idx] = z;
}
int main()
{
    cin >> n >> k;
    st = 0;
    ed = n << 1 | 1;
    for (int i = st; i <= ed; i++)
        hd[i] = -1;
    for (int i = 1; i <= n; i++)
    {
        add(st, i, 1);
        add(i, st, 0);
        add(i + n, ed, 1);
        add(ed, i + n, 0);
    }
    for (int i = 1, a, b; i <= k; i++)
    {
        cin >> a >> b;
        add(a, b + n, INF);
        add(b + n, a, 0);
    }
    cout << dinic();
    return 0;
}
```

### PS

距离上次提交题解已经有一年半的时间了， 记得那个暑假， 一个月过了 7 篇题解， 那时我才初一， 马上初二， 那时对 OI 的疯狂， 似乎确凿减少了， 还是希望我们共同不忘初心， 继续前进。

韶华不再， 求过

---

## 作者：xkcdjerry (赞：14)

这道题好像没有模拟退火题解，来水一个  
思路是对于每个陨石，一定会轰炸其所在的一行或一列。  
显而易见，如果行列都只存在这一个陨石，则同时轰炸行和列是不划算的。  

所以我们得出了模拟退火的对象：一个长为 $k$ 的01串，约定 $0$ 代表轰炸陨石所在的一行， $1$ 代表轰炸陨石所在的一列。  

估价函数我使用的就是需要轰炸的总数（要记住相同的行和列只需要轰炸一次，所以要查重以避免总数算大）。  
转移则是随机选择一个陨石并转换是轰炸所在的行还是轰炸所在的列。  

调参有亿点点难调 ~~我是不会告诉你我交了5页才调出来的~~

代码如下：
```cpp
#include <cstdio>
#include <ctime>
#include <cmath>
#include <cstdlib>
#define N 510
#define K (N*N)

int n,k;

int x[K],y[K];

struct solu
{
    //true:炸列
    //false:炸行
    bool vis[K];
}now,best,tmp;

//分别代表 best-cost now-cost temp-cost
int bc,nc,tc;

bool ver[N],hor[N];
int cost(solu &s)
{
    //暴力模拟，存储每一行每一列是否需要轰炸
    //最后统计所有需要炸的行列并求和
    for(int i=0;i<n;i++)
        ver[i]=hor[i]=false;
    for(int i=0;i<k;i++)
        if(s.vis[i]) ver[x[i]]=true;
        else hor[y[i]]=true;
    int ans=0;
    for(int i=0;i<n;i++)
    {
        if(ver[i]) ans++;
        if(hor[i]) ans++;
    }
    return ans;
}
solu turn(solu b)
{
    //这里是在Windows上调大数据必须的
    //因为RAND_MAX只有32767
    //但是k最大能到250000
    //所以不能直接取模，只能用这个Hack
    int i=rand()/(double)RAND_MAX*k;
    b.vis[i]=!b.vis[i];
    return b;
}

void read()
{
    scanf("%d%d",&n,&k);
    for(int i=0;i<k;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        //转化成以0为开始的索引
        x[i]=a-1;
        y[i]=b-1;
    }
}

//注下：由于线性同余法在一些计算机上的局限性
//使得最后一位始终为01交替
//所以此处使用rand()>(RAND_MAX/2)得到更高质量的随机数
void same(solu &a)
{
    //随机设置为同一个值，初始化best时使用
    bool val=rand()>(RAND_MAX/2);
    for(int i=0;i<k;i++)
        a.vis[i]=(val);
}
void rng(solu &a)
{
    //全部设置为随机值，初始化now时使用
    for(int i=0;i<k;i++)
        a.vis[i]=(rand()>(RAND_MAX/2));
}

//Boltzmann常数
#define kb 1.38e-23

inline bool accept(int diff,double T)
{
    return diff>=0||exp(diff/T/kb)>(rand()/(double)RAND_MAX);
}


void sa()
{
    //每次调用srand保证不一样的随机种子
    //玄学种子feel dead
    srand(0xfee1dead*rand());
    double T=1e7;
    const double eps=1e-10;
    const double cool=0.995;
    rng(now);
    nc=cost(now);
    while(T>eps)
    {
        tc=cost(tmp=turn(now));
        if(accept(nc-tc,T))
        {
            nc=tc;
            now=tmp;
        }
        if(nc<bc)
        {
            bc=nc;
            best=now;
        }
        T*=cool;
    }
}

//反复执行直到0.8秒
const int LIMIT=CLOCKS_PER_SEC*0.8;
int main()
{
    //srand(rand())保证高质量种子
    //dead beef有规律性可能被卡
    srand(0xdeadbeef);
    srand(rand());
    
    read();
    same(best);
    bc=cost(best);
    
    while(clock()<LIMIT)
        sa();
        
    printf("%d",bc);
}
```
注：因为 ~~玄学~~ 评测机波动，完全一样的代码会在 $100$ 和 $82$ 分之间反复横跳。  
[100分](https://www.luogu.com.cn/record/46915977)  [82分](https://www.luogu.com.cn/record/46915958)

---

## 作者：Mr_HY43205 (赞：11)

[P7368 [USACO05NOV]Asteroids G](https://www.luogu.com.cn/problem/P7368)
###### 题意
在 $N\times N$ 的网格图上有 $K$ 个小行星。现在要消除图上的所有小行星，每次操作可以消除同一行或同一列中的所有小行星，问最少需要几次操作？

$1 \leq N \leq 500$，$1 \leq K \leq N \times N$。

关键词：二分图最小点覆盖，könig定理，匈牙利算法

------------
###### 解题思路
我们的目标是将图中的所有小行星消除。如果把小行星看成一个节点，那本题应该可以转化成为图上的覆盖问题。

![](https://cdn.luogu.com.cn/upload/image_hosting/or0jxe8l.png)

简单地尝试一些建图会发现，如果我们只是在同一行或同一列的小行星之间连边，就无法体现“每次消除同行或同列中所有小行星”的性质。为了达到这样的效果，我们至少需要给每一行和每一列都建一个点，把每个代表小行星的点向它对应的行和列连边，通过选取行和列来进行覆盖。

![](https://cdn.luogu.com.cn/upload/image_hosting/cblwojka.png)

既然图中所有代表小行星的点都只连接了一行和一列，那我们可以直接把代表小行星的点省略，这样图中就只剩下了代表行和列的点，用行和列之间的连边来表示小行星。

![](https://cdn.luogu.com.cn/upload/image_hosting/gpdqn7kp.png)

显然，由于一个小行星只能连接唯一的行和列，这张图必定是一张二分图，而我们要解决的问题就变成了二分图上的最小点覆盖问题。

一般来说，在二分图上最小点覆盖的问题都会通过求解最大匹配来解决。根据 könig 定理，同一张图上最小点覆盖集的大小与最大匹配集的大小相同。

求解二分图上的最大匹配问题需要用到匈牙利算法。

匈牙利算法的基本流程是对于每一个点，从这个点出发，找一条路径，路径上经过的边依次为“匹配，未匹配，匹配，未匹配······”的状态（该路径也被称为一条增广路）。路径上第一条边和最后一条边应该是未匹配的。将路径上所有边的状态进行转换，即匹配的边变成未匹配，未匹配的边变成匹配。这样我们获得的匹配数就可以加一。

举个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/zzfnmdhb.png)

上图中，红色的边代表已匹配的边。在左图中，我们从左边的 $2$ 号点开始，找到了一条依次经过左 $2$ 、右 $1$ 、左 $1$、右 $2$ 的增广路。这条增广路上的边依次为黑、红、黑，代表它们依次为未匹配、匹配、未匹配。我们把路径上所有边的匹配情况改变，就得到了右图。可以看到，图上的匹配数增加了一。

我们对每一个左侧的点进行这一流程，最终就可以计算出图上的最大匹配数，也就得出了原问题的解。

匈牙利算法本质上是从每个点开始，dfs 遍历图上的边来寻找增广路，因此其时间复杂度为 $O(nm)$。

具体实现如下：

```cpp
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int maxN = 505;
int N, K;
vector <int> Nxt[maxN];
int bck[maxN * 2];	//记录与右侧点匹配的左侧点，没有匹配则为0
bool vis[maxN * 2];	//记录找到路径上经过的顶点
int ans = 0;

bool hungari(int u) {
    bool flag = false;
    for (int i = 0; i < Nxt[u].size() && !flag; i++) {
        int v = Nxt[u][i];
        if (vis[v] == true) continue;
        if (bck[v] != 0 && bck[v] != u) {	
            vis[v] = true;
            flag = hungari(bck[v]);	//递归寻找增广路
            if (flag) bck[v] = u;
        }
        else if (bck[v] == 0) {		//路径结尾的未匹配边
            bck[v] = u;
            flag = true;
        }
        else flag = false;
    }
    return flag;
}

int main() {
    cin >> N >> K;
    for (int i = 1; i <= K; i++) {
        int x, y;
        cin >> x >> y;
        Nxt[x].push_back(N + y);
    }
    for (int i = 1; i <= N; i++) {
        memset(vis, 0, sizeof(vis));	
        if (hungari(i)) ans++;		//对每一个左侧节点寻找增广路
    }
    cout << ans << endl;
    return 0;
}
```


---

## 作者：MY（一名蒟蒻） (赞：8)

[P7368 [USACO05NOV]Asteroids G](https://www.luogu.com.cn/problem/P7368)

## 分析

对于每一个小行星，只有两种方式消除。

如果把两种方式之间连边，显然构成二分图，我们需要让每一条边至少有一个点被选上。

于是转化为二分图最小点覆盖，等价于最大匹配问题。

即找到一条增广路，表示必须多放一个。

## 实现

[P3386 【模板】二分图最大匹配](https://www.luogu.com.cn/problem/P3386)

数据范围不明白为啥要用网络瘤，匈牙利挺香的。

将行作为左部点，列作为右部点建单向边跑匈牙利就行了，代码没必要了吧。

## $\text{Thank you for your reading !}$

---

## 作者：mydcwfy (赞：4)

~~没人写 Dinic ，我就来一篇吧~~

### 1.题意
对于每一个行星，要么选该行，要么选该列。

是不是有点熟悉？

### 2.分析

没错，他就是二分图最小点覆盖。

我的算法是将二分图转化为网络流，再跑一遍最小割。

即将左边的点与 $s$ 连接，右边的点与 $t$ 连接，权值均为1（代价为1）。
中间的边，权值 $+\infty$ （这样就不会成为割边了）。

#### 证明：割与点覆盖一一对应
对于每一个割，左边与源点如果满流，则选取；右边同理。

由于是割， $s$ 到 $t$ 不经过满流的点，就无法到达（否则又有了增广路）。

所以所有的边都被覆盖了，否则 $s$ 可以到 $t$，与割的定义矛盾。

对于每一个点覆盖，左边与源点连边满流；右边同理。

这时，由于中间的边都被覆盖了，$s$ 无法到 $t$。 

所以这就是一个割。

#### 证毕

又由最小割最大流定理可得：最小割=最大流。

那么，直接 Dinic 就可以了。

不懂网络流的同学，请移步
[我的博客](https://www.luogu.com.cn/blog/mydcwfy-342891/wang-lao-liu-chu-bu) 或百度 ~~逃~~

Code：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 1001
#define M 20000
#define INF 1e8
using namespace std;

int h[N],e[M],ne[M],w[M],idx,S,T;
int cur[N],q[N],d[N];
int n,m;

void add(int a,int b,int c)
{
	e[idx]=b,ne[idx]=h[a],w[idx]=c,h[a]=idx++;
	e[idx]=a,ne[idx]=h[b],w[idx]=0,h[b]=idx++;
}

inline void read(int &res)
{
	char c;
	while (!isdigit(c=getchar()));
	res=c-'0';
	while (isdigit(c=getchar())) res=(res<<1)+(res<<3)+c-'0';
	return;
}

bool bfs()
{
	memset(d,0,sizeof d);
	int hh=1,tt=1;
	q[1]=S;cur[S]=h[S];d[S]=1;
	while (hh<=tt)
	{
		int x=q[hh++];
		for (int i=h[x];~i;i=ne[i])
			if (!d[e[i]]&&w[i])
			{
				d[e[i]]=d[x]+1;
				cur[e[i]]=h[e[i]];
				if (e[i]==T) return true;
				q[++tt]=e[i];
			}
	}
	return false;
}

int findflow(int x,int limit)
{
	if (x==T) return limit;
	int flow=0;
	for (int i=cur[x];~i&&flow<limit;i=ne[i])
	{
		cur[x]=i;
		if (d[e[i]]==d[x]+1&&w[i])
		{
			int t=findflow(e[i],min(w[i],limit-flow));
			if (!t) d[e[i]]=-1;
			w[i]-=t,w[i^1]+=t,flow+=t;
		}
	}
	return flow;
}

int dinic()
{
	int r=0,flow;
	while (bfs()) while (flow=findflow(S,INF)) r+=flow;
	return r;
}

int main()
{
	memset(h,-1,sizeof h);
	read(n);read(m);
	int a,b;
	S=0,T=2*n+1;
	while (m--)
	{
		read(a);read(b);
		add(a,b+n,INF);
	}
	for (int i=1;i<=n;++i) add(S,i,1);
	for (int i=1;i<=n;++i) add(i+n,T,1);
	printf("%d\n",dinic());
	return 0;
}
```

---

## 作者：Elma_ (赞：3)

行列连边建二分图，消灭一行或一列的小行星相当于选择一个点覆盖所有和它相连的边。所以本题要求的其实就是二分图最小点覆盖，又因为二分图最小点覆盖等于其最大匹配，这个数据范围直接匈牙利就行了。

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
#define maxn 205
using namespace std;

inline int read() {
    int x = 0, w = 1;char ch = getchar();
    while (ch > '9' || ch < '0') { if (ch == '-')w = -1;ch = getchar(); }
    while (ch >= '0' && ch <= '9')x = x * 10 + ch - '0', ch = getchar();
    return x * w;
}


int t, n, ans, k;
bool vis[maxn], g[maxn][maxn];
int matched[maxn];

inline bool match(int pos) {
	for (int i = 1;i <= n;i++) {
        if (g[pos][i] && !vis[i]) {
			vis[i] = true;
			if (!matched[i] || match(matched[i])) { 
                matched[i] = pos;return true; 
            }
		}
    }
	return false;
}

int main(void) { 
	n = read(), k = read(), ans = 0;
    for (int i = 1, u, v;i <= k;i++) {
        u = read(), v = read();
        g[u][v] = true;
    }
	for (int i = 1;i <= n;i++) {
		memset(vis, false, sizeof(vis));
		if (match(i)) ans++;
 	}
    printf("%d\n", ans);
	return 0;
}
```


---

## 作者：miao5 (赞：1)

**题目大意：**

给一个01矩阵，每次操作可以把一行或一列全部的1变成0，求把整个矩阵变成0的最小操作数。

**思路：**

对于小行星 $i$ 在小行星的坐标 $x_i$ 与 $y_i$ 之间连边，然后求最小点覆盖即可。

最小点覆盖就等于最大匹配。

这题就做完了。

更多的细节在代码中。

**code：**

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1005;
int to[N*N],nxt[N*N],head[N],cnt=1;
int vis[N],cp[N];
int n,k,ans;
void add(int u,int v){
	to[cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt++;
} //加边 
bool dfs(int x){//匈牙利算法板子
	for(int i=head[x];i;i=nxt[i]){
		int v=to[i];
		if(vis[v]) continue;
		vis[v]=true;
		if(!cp[v]||dfs(cp[v])){
		    cp[v]=x;
		    return true;
		} 
	}
	return false;
} 
int main(){
	cin>>n>>k;
	for(int i=1;i<=k;i++){
		int u,v;
		cin>>u>>v;
		add(u,v+n);
	}//输入，建边 
	for(int i=1;i<=n;i++){
	    ans+=dfs(i);
	    memset(vis,0,sizeof(vis));
	}//求最大匹配 
	cout<<ans;//输出最小点覆盖=最大匹配 
	return 0;
}
```


---

## 作者：zmza (赞：1)

因为本题是二分图最小点覆盖（消灭一行或一列），我们又知道二分图最小点覆盖数就是二分图最大匹配数，所以这一道题就是二分图最大匹配。

只要将每个小行星的行和列建一条边，再跑匈牙利算法就可以算出二分图最大匹配，也就是二分图最小点覆盖了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int i = 0, f = 1;
	char ch;
	for(ch = getchar(); (ch < '0' || ch > '9') && ch != '-'; ch = getchar());
	if(ch == '-')
	{
		f = -1;
		ch = getchar();
	}
	for(; ch >= '0' && ch <= '9'; ch = getchar())
	{
		i = (i << 3) + (i << 1) + (ch ^ 48);
	}
	return i * f;
}
void write(int a,char b = ' ')
{
	if(a < 0)
	{
		putchar('-');
		a = -a;
	}
	if(a == 0)
	{
		putchar('0');
		putchar(b);
		return;
	}
	int sta[100] = {}, cnt = 0;
	while(a)
	{
		cnt++;
		sta[cnt] = a % 10;
		a /= 10;
	}
	while(cnt)
	{
		putchar(sta[cnt] + '0');
		cnt--;
	}
	putchar(b);
}
int a[505][505],match[505],n,m,e,p[505],ans;
bool dfs(int x)
{
	for(int i = 1; i <= n; i++)
	{
		if(a[x][i] && !p[i])
		{
			p[i] = 1;
			if(match[i] == 0 || dfs(match[i]))
			{
				match[i] = x;
				return 1;
			}
		}
	}
	return 0;
}
int main()
{
	n = read(),e = read();
	for(int i = 1; i <= e; i++)
	{
		int u = read(),v = read();
		a[u][v] = 1;
	}
	for(int i = 1; i <= n; i++)
	{
		memset(p,0,sizeof(p));
		if(dfs(i))ans++;
	}
	write(ans);
	return 0;
}
```


---

## 作者：dreamcast (赞：1)

先看题面 让你消灭一行或一列 那就是一个二分图的**最小点覆盖**

所以行列连边 然后正常匈牙利跑出**最大匹配**就可以了.

因为二分图最小点覆盖 等于 二分图最大匹配

$CODE:$
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<bitset>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N=505;
int n,k,a[N][N],vis[N],ans,qwq[N];
int find(int x){  //二分图最大匹配
	for(int i=1;i<=n;i++)
		if(!vis[i]&&a[x][i])
		{
			vis[i]=1;
			if(!qwq[i]||find(qwq[i]))
			{
				qwq[i]=x;
				return 1;
			}
		}
	return 0;
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=k;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		a[x][y]=1;  //行列连边
	}
	for(int i=1;i<=n;i++)
	{
		ans+=find(i);
		memset(vis,0,sizeof(vis));
	}
	printf("%d",ans);
  	
	return 0;
}
```


---

## 作者：FutureThx (赞：0)

一道较为简单的匈牙利算法练手题

### 题目大意

给出一个 $N \times N$ 的方阵，然后有 $K$ 个小行星在这个方阵之中，并给出它们的坐标。

每次可以选择花费一个代价消除一行或一列的所有小行星，问最小花费代价

### 解题思路

看到消除行列，并且代价最小，就很容易想到最小点集覆盖。

所以考虑对于每个小行星的行列，都进行连边，得出二分图

然后发现每一条边都必须有一个端点有武器摆放，否则就无法消除所有小行星，显然这个东西就是上面提到的最小点集覆盖。

又有二分图的最小点集覆盖点数等同于其最大匹配边数（[König定理](https://www.matrix67.com/blog/archives/116) 这个是Matrix67大神的博客，讲的非常详细），所以跑一遍匈牙利算法就行了

### 代码

```cpp
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
#define MAX_N 510
int n,k;
bool vis[MAX_N];
int match[MAX_N];
struct Graph{
    vector<int> next;
}node[MAX_N];
bool find(int u){
    for(int i = 0;i < node[u].next.size();i++){
        int v = node[u].next[i];
        if(vis[v] == true)continue;
        vis[v] = true;
        if(match[v] == 0 || find(match[v])){
            match[v] = u;
            return true;
        }
    }
    return false;
}
int main(){
    cin >> n >> k;
    for(int i = 1;i <= k;i++){
        int u,v;
        cin >> u >> v;
        node[u].next.push_back(v);
    }
    int ans = 0;
    for(int i = 1;i <= n;i++){
        memset(vis,false,sizeof(vis)); 
        ans += find(i);
    }
    cout << ans << endl;
    return 0;
}
```

### 后记

Updata 2021/6/1 : 完成题解

---

## 作者：Evitagen (赞：0)

比较基础的二分图最小点覆盖题目

首先要知道二分图的定义，匈牙利算法······

我们可以根据**konig**定理知道，
### 二分图最小点覆盖数=二分图最大匹配边数

所以这道题就变成了计算这个二分图的最大匹配边数。

#### 我们可以把每一行当做一个顶点，计算最多几个顶点可以把所有的小行星摧毁。

因此我们拿原图的行和列作匹配，如果某个位置有小行星，我们就把当前行和列连边，然后进行二分图匹配（匈牙利算法），这样就可以算出来最小点覆盖数。



接下来是代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=505;
int n,k,match[N],ans;
int a[N][N],vis[N];
bool dfs(int x){
	for(int i=1;i<=n;i++)
		if(a[x][i]&&!vis[i]){//如果当前需要摧毁小行星 
			vis[i]=1;
			if(match[i]==0||dfs(match[i])){//本身为非匹配点，而且又能找到另一个点和其匹配，那么就是增广路 
				match[i]=x;
				return true;
			}
		}
	return false;
}
int main()
{
	cin>>n>>k;
	for(int i=1;i<=k;i++){
		int x,y;scanf("%d%d",&x,&y);
		a[x][y]=1;//存图，将当前行和列连边
	}
	for(int i=1;i<=n;i++){//匈牙利算法模板 
		memset(vis,0,sizeof(vis));
		if(dfs(i))
			ans++;
	}
	cout<<ans<<endl;
	return 0;
} 
```


---

