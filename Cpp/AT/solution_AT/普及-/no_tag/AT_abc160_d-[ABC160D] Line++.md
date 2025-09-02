# [ABC160D] Line++

## 题目描述

## 题意

有一张 $N$ 个点、$N$ 条边的图。

- 对于第 $i$ 个点（$1 \leq i < N$），连一条 $i$ 和 $i+1$ 之间的无向边。

- 再给你两个点 $x, y$ 满足 $y > x + 1$，连一条 $x$ 和 $y$ 之间的无向边。

对于 $k=1, 2, \cdots, n-1$，求图上最短路径为 $k$ 的点对数。

## 说明/提示

$3 \leq N \leq 2 \times 10^3$.

$1 \leq x, y \leq N$.

$x + 1 < y$.

所有输入均为整数.

## 样例 #1

### 输入

```
5 2 4```

### 输出

```
5
4
1
0```

## 样例 #2

### 输入

```
3 1 3```

### 输出

```
3
0```

## 样例 #3

### 输入

```
7 3 7```

### 输出

```
7
8
4
2
0
0```

## 样例 #4

### 输入

```
10 4 8```

### 输出

```
10
12
10
8
4
1
0
0
0```

# 题解

## 作者：Jairon314 (赞：6)

$$ \textbf{\huge AT4811 [ABC160D]} $$
$$ \textbf{\LARGE Line++} $$
$$ \text{\large ————Jair} $$

$$ \text{\small Warning: This problem's solving belongs to} $$
$$ \textbf {\huge $ \mathbb{TOP\;SECRET} $} $$
$$ \text {\small Unauthorized personnel are prohibited from visiting} $$
$$ \text {\small Perpetrators will be monitored, located, and dealt with} $$

$$ PAY\;ATTENTION: $$
$$ \text {\small cspJ踩线1$=$的蒟蒻没有想出十分优秀的低复杂度解法} $$
$$ \text {\small 橙名蒟蒻刷橙题} $$

$$ \large· $$
$$ \large· $$
$$ \large· $$

$$ \large \frak Forward $$
--------
今天来水题解（AT橙题），由于黄色绿色蓝色紫色黑色的题解我都写过了，于是来写一下橙题的题解。

当我看到这道题的时候，脑中立马浮现：氵题！于是5分钟码完AC了（不愧是橙题）。一看题解，发现题解区全都是找的规律，基本没有正规的最短路解法。为了让最短路更加广为人知，我准备发一篇最短路的题解

$$ \text {本文将用标准的{\small dijkstra+堆优化}进行讲解} $$

$$ \large \frak CodeTime $$
--------

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define maxn 1000010

struct Edge{
	int to;
	int val;
	int nexty;
}edge[maxn];//标准结构体存图 

int path[maxn],link[maxn],cnt;
bool vis[maxn];

void build(int u,int v,int w){
	edge[++cnt].to=v;
	edge[cnt].val=w;
	edge[cnt].nexty=link[u];
	link[u]=cnt;
}//前向星 

void dijkstra(int s){
	memset(path,0x3f3f,sizeof path);
	memset(vis,false,sizeof vis);
	path[s]=0;
	priority_queue< pair< int,int > > q;
	q.push(make_pair(0,s));
	while(!q.empty()){
		int x=q.top().second;
		q.pop();
		if(vis[x])continue;
		vis[x]=1;
		for(int i=link[x];i;i=edge[i].nexty){
			if(path[edge[i].to]>edge[i].val+path[x]){
				path[edge[i].to]=edge[i].val+path[x];
				q.push(make_pair(-path[edge[i].to],edge[i].to));
			}
		}
	}
}//dijkstra+堆优化 

int n,x,y,sum[maxn];

int main(){
	scanf("%d%d%d",&n,&x,&y);
	for(int i=1;i<n;i++){
		build(i,i+1,1);
		build(i+1,i,1);
	}
	build(x,y,1);
	build(y,x,1);
	for(int i=1;i<=n;i++){
		dijkstra(i);
		for(int j=1;j<=n&&j!=i;j++){
			sum[path[j]]++;//桶排 
		}
	}
	for(int i=1;i<n;i++){
		printf("%d\n",sum[i]);
	}
	//暴力求解 
	return 0;
}
```

好了，笔者的意图就是让大家了解dijkstra算法，如果你想要更加深入的学习dijkstra，请继续参考[单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)和[单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)，谢谢大家！

$$ \large \frak {in\;the\;end}$$
--------
祝大家元旦快乐，万事如意，在2021年绽放光彩！~~我相信我一定会的~~


---

## 作者：caoxuran (赞：2)

### 这道题只需要以一个点到另一个点的直线距离和以 $ xy $ 作为跳板修正后的距离比小就行了。
例如：$ a $ 到 $ b $ ($ a $ < $ b $)的直线距离为 $ b $ - $ a $，以 $ xy $ 为跳板的距离为 | $ x $ - $ a $ | + | $ y $ - $ b $ | + $ 1 $ 。

因此，$ a $ 到 $ b $ 的最短距离就是：
```cpp
min(b-a,abs(x-a)+abs(y-b)+1);
```

#### 上代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int ans[3001];

int main()
{
	int n,x,y;
	cin>>n>>x>>y;
	int temp;
	
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
		{
			temp=min(j-i,abs(i-x)+abs(j-y)+1);		//选择最短距离
			ans[temp]++;
		}
	
	for(int i=1;i<n;i++)
		cout<<ans[i]<<endl;
	return 0;
}
```
网上应该有很多人和我的思路一样吧。

---

## 作者：Aehnuwx (赞：2)

题意：给出 $N,X,Y$。有 $N$ 条无向边：
- 对于 $i=1,2,\cdots,N-1$，连一条从点 $i$ 到点 $i+1$ 的无向边。
- 连一条从点 $X$ 到点 $Y$ 的无向边。

对于 $k=1,2,\cdots,N-1$，要求解决以下问题：
- 找到能使无向边 $(i,j)(1\le i<j\le N)$ 的距离为 $k$ 的方案数。

数据范围：
- $3\le N\le 2\times 10^3$
- $1\le X,Y\le N$
- $X+1<Y$



------------


Sol:
显然，使用 $O(N^3)$ 的 Floyd 算法是不可行的，会直接 TLE。

我们分析一下题目后，会发现：题目中的这个无向图，假如去掉 $(X,Y)$ 这条无向边之后，便会成为**一条链**！

事实上，$O(N^3)$ 的 Floyd 算法是一种解决**图**的多源最短路径的**预处理**方法。在本题这种情况下，显然有些大材小用了。

我们是否可以找到一种时间复杂度为 $O(N^2)$ 的预处理方法呢？答案是肯定的。

设 $s(i,j)$ 为点 $i$ 到点 $j$ 的最短距离。那么枚举 $i,j(1\le i<N,i<j\le N)$，则 $s(i,j)=\min\{j-i,|X-i|+|Y-j|\}$。

其中，$j-i$ 为不可以经过 $(X,Y)$ 的 $i$ 到 $j$ 的最短距离，$|X-i|+|Y-j|$ 为必须经过 $(X,Y)$ 的 $i$ 到 $j$ 的最短距离。

再使用一个桶 $T()$。枚举 $i,j(1\le i<N,i<j\le N)$，每次枚举到一组 $i$ 和 $j$ 后，$T(s(i,j))\gets T(s(i,j))+1$。

最终，枚举 $k=1,2,\cdots,N-1$，每次输出 $T(k)$ 即为最终答案。



------------


Code:
```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define iterator IT
#define SIZ(V) V.size()
#define FS(a) fixed<<setprecision(a)
using namespace std;
namespace STARTER {
	int MAX(int a,int b) {return a>b?a:b;}
	int MIN(int a,int b) {return a<b?a:b;}
	int ABS(int a) {return a<0?-a:a;}
	int GCD(int a,int b) {return !b?a:GCD(b,a%b);}
	int LCM(int a,int b) {return a/GCD(a,b)*b;}
	int QSM(int a,int b,int p) {int ret=1;while (b) (b&1)&&(ret=ret*a%p),a=a*a%p,b>>=1;return ret;}
	int ROUND(double a) {return a+0.5;}
}
using STARTER::MAX;
using STARTER::MIN;
using STARTER::ABS;
using STARTER::GCD;
using STARTER::LCM;
using STARTER::QSM;
using STARTER::ROUND;
const int maxN=2005;int n,x,y,/*dis[maxN][maxN],*/s[maxN][maxN],ans[maxN],t[maxN*maxN];
int main() {
	cin>>n>>x>>y/*,dis[x][y]=1*/;
	//for (int i=1;i<n;i++) dis[i][i+1]=1; 
	//for (int i=1;i<n;i++)
	//	for (int j=i+1;j<=n;j++) dis[i][j]=1;
	for (int i=1;i<n;i++)
		for (int j=i+1;j<=n;j++) //{
			//if (i<=x&&j>=y) s[i][j]=x-i+1+j-y;
			//else s[i][j]=j-i;
			s[i][j]=min(j-i,ABS(x-i)+1+ABS(y-j));
		//}
	//for (int i=1;i<n;i++) {
	//	for (int j=i+1;j<=n;j++) printf("s[%d][%d]=%d ",i,j,s[i][j]);
	//	puts("");
	//}
	for (int i=1;i<n;i++)
		for (int j=i+1;j<=n;j++) t[s[i][j]]++;
	for (int k=1;k<n;k++) cout<<t[k]<<'\n';
}
```

---

## 作者：cyrxdzj (赞：1)

### 一、思路

一看数据范围，$n\le2000$。

思路已经大体出来了：剪枝完，暴力搜！

可以先建图，再对每个点都进行一次迪杰斯特拉最短路算法（带桶优化），每次都将结果以桶的形式存储。

注意，不能重复计数。

### 二、完整代码

```cpp
#include<cstdio>
#include<queue>
using namespace std;
struct edge_object
{
	int to,next;
}edge[4005];
struct node
{
	int u,dis;
	bool operator<(const node &b)const
	{
		return dis>b.dis;
	}
};
int n,edge_cnt;
int x,y;
int head[2005];
int dis[2005];
int ans[2005];
void add_edge(int u,int v)
{
	edge[++edge_cnt].to=v;
	edge[edge_cnt].next=head[u];
	head[u]=edge_cnt;
}
void dijskra(int u)//最短路算法。
{
	priority_queue<node>q;
	dis[u]=0;
	q.push((node){u,0});
	while(!q.empty())
	{
		node u=q.top();
		q.pop();
		for(int i=head[u.u];i;i=edge[i].next)
		{
			int v=edge[i].to;
			if(dis[v]>dis[u.u]+1)
			{
				dis[v]=dis[u.u]+1;
				q.push((node){v,dis[v]});
			}
		}
	}
}
int main()
{
	scanf("%d",&n);//输入&建图。
	for(int i=1;i<n;i++)
	{
		add_edge(i,i+1);
		add_edge(i+1,i);
	}
	scanf("%d%d",&x,&y);
	add_edge(x,y);
	add_edge(y,x);
	for(int i=1;i<=n;i++)//跑最短路算法。
	{
		for(int j=1;j<=n;j++)
		{
			dis[j]=0x3fffffff;
		}
		dijskra(i);
		for(int j=i+1;j<=n;j++)//注意要写j=i+1而不是j=1，防止重复计数。
		{
			ans[dis[j]]++;
		}
	}
	for(int i=1;i<n;i++)//输出。
	{
		printf("%d\n",ans[i]);
	}
	return 0;
}
```

By [dengzijun](https://www.luogu.com.cn/user/387836)

---

## 作者：Eason_AC (赞：1)

## Content
给定一个 $n$ 个点、$n$ 条边的无向图。对于所有的 $1\leqslant i<n$，在点 $i,i+1$ 之间连一条无向边。另外在给定两个点 $x,y$，在点 $x,y$ 之间连一条无向边。现请对于所有的 $1\leqslant k<n$，求出图中最短距离为 $k$ 的点对数。

**数据范围：$3\leqslant n\leqslant2\times 10^3$，$1\leqslant x,y\leqslant n$，$x+1<y$。**
## Solution
相信各位一开始想到的就是最短路算法了吧。但是 $\mathcal O(n^3)$ 的 Floyd 算法并不能跑得过去，那么自然就去想别的最短路算法了，比如 Dijkstra。这时我们发现，$\mathcal O(n\log n)$ 的堆优化 Dijkstra 貌似可以较轻松地通过此题，那我们不妨来继续往下想一下！

首先我们对于每个点用堆优化 Dijkstra 求出其到每个点的距离，然后再将每个距离存储到桶中。枚举每个点是 $\mathcal O(n)$ 的，每次跑堆优化 Dijkstra 是 $\mathcal O(n\log n)$ 的，因此总的时间复杂度是 $\mathcal O(n^2\log n)$ 的，足以通过此题。

注意，这么样来的话，我们距离为 $k$ 的点对 $(x,y)$ 就会重复算 $2$ 次（一次在从点 $x$ 跑 Dijkstra 的时候，另一次在从点 $y$ 跑 Dijkstra 的时候）。因此我们最后要将每个得出来的距离为 $k$ 的点对数除以 $2$，才能得到正确结果。
## Code
```cpp
const int N = 2e3 + 7;
int n, cnt, num[N], h[N << 1], dis[N], vis[N];
struct edge {int to, nxt;}e[N << 1];

iv a_e(int u, int v) {e[++cnt] = (edge){v, h[u]}; h[u] = cnt;}
iv dj(int s) {
    pq<pii> q;
    dis[s] = 0, q.push(pii(0, s));
    while(!q.empty()) {
        int x = q.top().se; q.pop();
        if(vis[x]) continue;
        vis[x] = 1;
        for(int i = h[x]; i; i = e[i].nxt) {
            int y = e[i].to;
            if(dis[y] > dis[x] + 1) dis[y] = dis[x] + 1, q.push(pii(-dis[y], y));
        }
    }
}

int main() {
    n = Rint;
    F(int, i, 1, n - 1) a_e(i, i + 1), a_e(i + 1, i);
    int x = Rint, y = Rint; a_e(x, y), a_e(y, x);
    F(int, i, 1, n) {
        memset(dis, 0x3f, sizeof(dis)), memset(vis, 0, sizeof(vis));
        dj(i);
        F(int, j, 1, n) num[dis[j]]++;
    }
    F(int, i, 1, n - 1) num[i] /= 2, println(num[i]);
    return 0;
}
```

---

## 作者：绿绵羊 (赞：1)

这道题其实并不是一道$\color{white}\small\colorbox{orange}{普及-}$的题目，  
因为它实际上应该是$\color{white}\small\colorbox{red}{入门}$题。

------------
（上面是开玩笑的QwQ，但这题确实没有你们想象中的难）  
这道题，很多人都说用**Floyd**，但一看数据范围就惊呆了：**2000³**……肯定会**超时**的好吗！！！  
那难道就要和Floyd相互886了吗？当然不是，这道题不能用Floyd，但可以用上Floyd的**主体思想**。

------------
### 什么是Floyd
Floyd，~~顾名思义~~就是先**枚举**一个点，再看这个点能不能**优化**另外两点间的距离。  
比如这个：![](https://cdn.luogu.com.cn/upload/image_hosting/f59jw2gz.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
不难发现，①和②之间虽有一条边，但太长了，如果经过③的话则会短很多，那么就在**邻接矩阵**里把①到②的距离从原来的99改成6。  
Floyd就是通过多次**枚举**像③这样的点，再**枚举**另外两个可**被优化**的点，最终得出一张图中**任意两点**间的最短距离。

------------
再说回这道题，这边我们可以**不用全部枚举**。  
其实，整个图最初没有新加边时的最短距离是很好求的，就是两点之**差的绝对值**，那么，新加的边就是用来优化的。  
是的，这里是**用边来优化**，因为题目已经把用来优化的边告诉你了。  
这样就**少了一重枚举**，复杂度从O（n³）降到了O（n²），轻松$\color{white}\small\colorbox{green}{AC}$。

------------
相信大家都已经听懂了，那么就是最后一步：~~Copy~~写代码。  
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n, x, y;
	cin >> n >> x >> y;
	int a[n+1][n+1], s[n];
	for (int i=1; i<=n; i++)
		for (int j=1; j<=n; j++) a[i][j]=fabs(i-j);//求出加边前的最短距离
	for (int i=1; i<=n; i++)
		for (int j=1; j<=n; j++)
			a[i][j]=min(a[i][j], min(a[i][x]+a[y][j]+1, a[i][y]+a[x][j]+1));//开始优化~
	for (int i=1; i<n; i++) s[i]=0;
	for (int i=1; i<=n; i++)
		for (int j=1; j<=n; j++) s[a[i][j]]++;//统计
	for (int i=1; i<n; i++) cout << s[i]/2 << endl;
	return 0;//愉快地结束
}
```


---

## 作者：智子·起源 (赞：0)

## 同样的方法，最简单明了的讲法

从一个点到另一个点的最短路有两种走法：

- 直接走（不依靠x、y连接的边），这种走法需要的步数就是它俩之间的距离。

- 依靠x、y之间的无向边，则较小的那个起点就要到x点，然后移到y点，再移到较大的那个终点，即三部分分别是abs（i-x）和abs（j-y）还有1。（x到y之间还要走一步）

把两种走法求最小值，即两点间的最短路。

最后，把所有两点之间的最短路下标计数，然后输出即可。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,f[100000+5];
int main()
{
  cin>>n>>x>>y;
  for(int i=1;i<n;i++)
    for(int j=i+1;j<=n;j++)
      f[min(j-i,abs(i-x)+abs(j-y)+1)]++;//计算最短路
  for(int i=1;i<n;i++)cout<<f[i]<<endl;//输出，从1到n-1，因为没有任意两个点间的距离超过n-1                            
  return 0;
}
```


---

## 作者：do_while_true (赞：0)

## 题目分析

设 $f_{i,j}$ 为 $i$ 到 $j$ 的最短路，预处理加边之前的最短路，再更新加边后的各个点的最短路。

观察发现，若 $i$ 在 $x$ 及其左侧，$j$ 在 $y$ 及其右侧，则 $f_{i,j}$ 减去连的边的跳过的节点个数，也就是```f[i][j]-=y-x-1;```

若 $i$ 点在 $x,y$ 中间，则 $i$ 到 $j$ 有两条路可以走: 一个一个走原先的路，为 $f_{i,j}$ ；走到 $x$ 点，跳到 $y$ 点，再从 $y$ 走到 $j$，长度为 $f[i][x]+f[y][j]+1$ ，里面的 $1$ 是走 $x$ 到 $y$ 的长度。

若 $j$ 点在 $x,y$ 中间同理。

最后开个桶，遍历$f$数组即可。

## Code:

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,x,y;
int f[2001][2001];
int vis[20001];
int main()
{
	scanf("%d%d%d",&n,&x,&y);
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
			f[i][j]=f[j][i]=j-i;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(i<=x&&j>=y)
				f[i][j]-=y-x-1;
			if(i>x&&i<y)
				f[i][j]=min(f[i][j],f[i][x]+f[y][j]+1);
			if(j>x&&j<y)
				f[i][j]=min(f[i][j],f[j][y]+f[x][i]+1);
			f[j][i]=f[i][j];
		}
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			vis[f[i][j]]++;
	for(int i=1;i<=n-1;i++)
		printf("%d\n",vis[i]);
	return 0;
}
```


---

