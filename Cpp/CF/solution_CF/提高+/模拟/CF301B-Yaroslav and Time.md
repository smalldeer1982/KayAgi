# Yaroslav and Time

## 题目描述

Yaroslav is playing a game called "Time". The game has a timer showing the lifespan he's got left. As soon as the timer shows 0, Yaroslav's character dies and the game ends. Also, the game has $ n $ clock stations, station number $ i $ is at point $ (x_{i},y_{i}) $ of the plane. As the player visits station number $ i $ , he increases the current time on his timer by $ a_{i} $ . The stations are for one-time use only, so if the player visits some station another time, the time on his timer won't grow.

A player spends $ d·dist $ time units to move between stations, where $ dist $ is the distance the player has covered and $ d $ is some constant. The distance between stations $ i $ and $ j $ is determined as $ |x_{i}-x_{j}|+|y_{i}-y_{j}| $ .

Initially, the player is at station number $ 1 $ , and the player has strictly more than zero and strictly less than one units of time. At station number $ 1 $ one unit of money can increase the time on the timer by one time unit (you can buy only integer number of time units).

Now Yaroslav is wondering, how much money he needs to get to station $ n $ . Help Yaroslav. Consider the time to buy and to increase the timer value negligibly small.

## 样例 #1

### 输入

```
3 1000
1000
0 0
0 1
0 3
```

### 输出

```
2000
```

## 样例 #2

### 输入

```
3 1000
1000
1 0
1 1
1 2
```

### 输出

```
1000
```

# 题解

## 作者：xcxc82 (赞：3)

# CF301B

## 题意

给定 $n$ 个点的坐标和一个常数 $d$，从 $i$ 点走到 $j$ 点需要耗费 $d\times(\left|x_i-x_j\right|+\left|y_i-y_j\right|)$ 的路费，第一次经过点 $i$ 时能增加 $a_i$ 的路费（$2\le i\le n-1$），现在从 $1$ 号节点出发，问需要准备多少路费才能走到 $n$ 号节点。

$n\le100$，$10^3\le d\le10^5$，$1\le a_i\le10^3$

## 题解

考虑使用最短路算法。对 $i\rightarrow j$ 的路径建立一条长度为 $d\times(\left|x_i-x_j\right|+\left|y_i-y_j\right|)-a_i$ 的边，观察数据范围，$d$ 的最小值要比 $a_i$ 的最大值大，因此**不会出现负权边**，且每个节点必定只经过一次，$1$ 到 $n$ 的最短路即为所求值。有些题解里说 Dijstra 会错第 $10$ 个点估计是自己的建边建错了。

使用 SPFA，Dijstra，Floyed 中的任意一种即可。

## 代码


```cpp
#include<bits/stdc++.h>
#define raed read
using namespace std;
const int MAXN = 200010,INF = 0x3f3f3f3f;
const double eps = 0.0001;
inline int read(){
	int X=0; bool flag=1; char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') flag=0; ch=getchar();}
	while(ch>='0'&&ch<='9') {X=(X<<1)+(X<<3)+ch-'0'; ch=getchar();}
	if(flag) return X;return ~(X-1);
}
int head[MAXN],tot = 1,f[MAXN],vis[MAXN],n,a[MAXN];
int T,d,x[MAXN],y[MAXN];
struct E{
	int next,v,w;
}edge[MAXN<<1];
void add(int u,int v,int w){
	edge[tot].v = v;
	edge[tot].w = w;
	edge[tot].next = head[u];
	head[u] = tot++;
}
struct Node{
	int node,ans;
	bool operator <(const Node x) const{
		return x.ans<ans;
	}
};
void Dijstra(){
	priority_queue<Node> q;
	for(int i=0;i<=n;i++) f[i] = (1ll<<31)-1;
	f[1] = 0;
	q.push(Node{1,0});
	while(!q.empty()){
		Node now = q.top();
		int u = now.node;
		q.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		for(int i=head[u];i;i = edge[i].next){
			int v = edge[i].v,w = edge[i].w;
			if(f[u]+w<f[v]){
				f[v] = f[u]+w;
				q.push(Node{v,f[v]});
			}
		}
	}
}
int main(){
	n = raed(),d = raed();
	for(int i=2;i<=n-1;i++) a[i] = raed();
	for(int i=1;i<=n;i++){
		x[i] = raed(),y[i] = raed();
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			add(i,j,d*(abs(x[i]-x[j])+abs(y[i]-y[j]))-a[j]);
			add(j,i,d*(abs(x[i]-x[j])+abs(y[i]-y[j]))-a[i]);
		}
	}
	Dijstra();
	cout<<f[n]<<endl;
}
```







---

## 作者：Underage_potato (赞：2)

## Solution

~~最短路板题！~~

我们用 $a_k$ 代表走到第 $k$ 个点时的可恢复单位时间的值。

那么两个点之间的距离则为：$ \left ( \left | x_1 -x_2 \right | + \left | y_1-y_2 \right |  \right ) \times d -a_k $。

然后直接跑一遍最短路即可！dij、SPFA 和 Floyd 都行，我写的 Floyd，~~因为太懒了~~。

## AC Code:

```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define INF 1919810
using namespace std;

ll n,d;
ll a[1001],x[1001],y[1001],dis[1001][1001];

inline void init(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			dis[i][j]=INF;
		}
	}
}

inline void work(){
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			dis[i][j]=(abs(x[i]-x[j])+abs(y[i]-y[j]))*d-a[j];
			dis[j][i]=(abs(x[i]-x[j])+abs(y[i]-y[j]))*d-a[i];
		}
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(i!=k && j!=k && i!=j){
					dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
				}
			}
		}
	}
}
int main(){
	cin>>n>>d;
	for(int i=2;i<n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
	}
	init();
	work();
	cout<<dis[1][n];
	return 0;
}
```


---

## 作者：封禁用户 (赞：1)

# CF301B

这不最短路的板子题吗？

## 思路
用 $ak$ 代表走到第 $k$ 点时的可恢复单位时间的值。

$i$ 到 $j$ 的距离是 $\left ( \left | xi-xj \right | + \left | yi-yj \right |  \right ) \times d-ak$。

再打一下最短路代码，建议 Floyd，~~因为短~~。

## AC Code

```
#include <bits/stdc++.h>
using namespace std;
int n,d,a[105],x[105],y[105],dis[105][105];
void floyd() {
	for(int k=1; k<=n; k++)
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)
				if(dis[i][j]>dis[i][k]+dis[k][j]&&j!=k&&i!=k)
					dis[i][j]=dis[i][k]+dis[k][j];
}
int main() {
	cin>>n>>d;
	for(int i=2; i<n; i++) cin>>a[i];
	for(int i=1; i<=n; i++) cin>>x[i]>>y[i];
	for(int i=1; i<=n; dis[i][i]=0,i++)
		for(int j=i+1; j<=n; j++)
			dis[i][j]=(abs(x[j]-x[i])+abs(y[j]-y[i]))*d-a[j],dis[j][i]=(abs(x[j]-x[i])+abs(y[j]-y[i]))*d-a[i];
	floyd();
	cout<<dis[1][n];
	return 0;
}
```

---

## 作者：XL4453 (赞：1)

### 解题思路：

考虑建图跑最短路。

由于每一个点之间都可以相互到达，所以需要建一个完全图，每一个点 $i$ 到另一个点 $j$ 的边权为 $(|x_i-x_j|+|y_i-y_j|)\times d-a_i$ 表示从 $i$ 到  $j$ 需要在原来的基础上再消耗这么多的时间。这个值也有可能是负的，表示会减少一定的时间。

由于每一个点最多只能提供一次代价，所以不需要判断负权环，直接写一个普通的 Floyd 就可以了。而如果写 SPFA 或者 堆优化之后的 Dijkstra 可能会陷入死循环。~~100 的数据谁去写那些东西。~~

-------
### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int link[105][105],n,d,a[105],x[105],y[105];
int main(){
	scanf("%d%d",&n,&d);
	for(int i=2;i<n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)scanf("%d%d",&x[i],&y[i]);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	if(i!=j)
	link[i][j]=d*(abs(x[i]-x[j])+abs(y[i]-y[j]))-a[i];
	for(int k=1;k<=n;k++)
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	link[i][j]=min(link[i][j],link[i][k]+link[k][j]);
	printf("%d",link[1][n]);
	return 0;
}
```

---

## 作者：MiRaciss (赞：1)

思路：最短路

每两个点的距离为$(|x_1-x_2|+|y_1-y_2|)*d-a[j]$,其中j为走到第j个点的可恢复的单位时间的大小
然后跑一遍dijkstra即可

```cpp
#include<bits/stdc++.h>
#include<queue>
#include<vector>
using namespace std;

struct zz{
	int v;
	int w;
	bool operator < (const zz x) const
      { return x.w<w; }
};

vector<zz> v[2505];
int n,d,INF;
int dp[2505];
int a[100005];
int x[100005];
int y[100005];
bool f[2505];

void Dijkstra(int s,int t){
	dp[s]=0;
	priority_queue<zz> q;
	zz Now;
	Now.v=s;
	Now.w=dp[s];
	q.push(Now); 
	while(q.size()){
		zz now=q.top();
		q.pop();
		if(f[now.v]){
			continue;
		}
		f[now.v]=1;
		int k=now.v;
		for(int j=0;j<v[k].size();j++){
			if(dp[k]+v[k][j].w<dp[v[k][j].v]){
				dp[v[k][j].v]=dp[k]+v[k][j].w;
				zz NOW;
				NOW.w=dp[v[k][j].v];
				NOW.v=v[k][j].v;
				q.push(NOW); 
			}
		}
	}
	printf("%d\n",dp[t]);
}

int main(){
	memset(dp,0x3f,sizeof dp);
	scanf("%d%d",&n,&d);
	for(int i=2;i<n;i++) scanf("%d",&a[i]); 
	for(int i=1;i<=n;i++) scanf("%d%d",&x[i],&y[i]);
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			int dist=(abs(x[j]-x[i])+abs(y[j]-y[i]))*d;
			v[i].push_back(zz{j,dist-a[j]});
			v[j].push_back(zz{i,dist-a[i]});
		}
	}
		
	//cin>>s>>t;
	Dijkstra(1,n); 
	return 0;
}
```

---

## 作者：2022_37_yzyUUU (赞：1)

# CF301B
## 题意

两点之间的距离为 $ | x_i - x_j | \times d + | y_i - y_j | \times d - a $。

已知 $ n $ 个坐标和 $ n-2 $ 个 $ a $，求第一个点到第 $ n $ 个点的最短路。

## 最短路

因为本题 $ n≤100 $ 所以可以用 Floyd，三重循环也不会超时。

floyd 板子

```cpp
for(int k=1;k<=n;k++)
   for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
           f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
```

## AC Code

```
#include<bits/stdc++.h>
using namespace std;
int n,d,a[101],x[101],y[101],f[101][101];
int main() {
	cin>>n>>d;
	for(int i=2; i<n; i++) {
		cin>>a[i];
	}
	memset(f,0x7ffffff,sizeof(f)); //初始化成极大值
	for(int i=1; i<=n; i++)cin>>x[i]>>y[i];
	for(int i=1; i<=n; i++) {
		for(int j=i+1; j<=n; j++) {
			f[i][j]=d*(abs(x[i]-x[j])+abs(y[i]-y[j]))-a[j];
			f[j][i]=d*(abs(x[i]-x[j])+abs(y[i]-y[j]))-a[i];//注意a不同
		}
	}
	for(int k=1; k<=n; k++)
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)
				if(f[i][j]>f[i][k]+f[k][j]&&j!=k&&i!=k)
					f[i][j]=f[i][k]+f[k][j];
	cout<<f[1][n];
}

```

---

## 作者：yzh_Error404 (赞：0)

可以一眼看出是最短路。

不难发现，从 $i$ 点走向 $j$ 点的代价是 $d$ 乘 $i$ 到 $j$ 的距离再减去 $a_j$ 。

这里的 $a_j$ 可以不用考虑第二次经过的可能，因为若一个点走过了第二次，则路径一定有环，一定不是最优的。

所以在每一对 $i$ 与 $j$ 之间连上权值为 $d\times \operatorname{getdist}(x_i,y_i,x_j,y_j)-a_i$ 的双向边，跑最短路即可。

这里的 $\operatorname{getdist}$ 是求 $i$ 与 $j$ 之间的曼哈顿距离。

因为数据范围是 $n\le100$ ，所以直接用了 Floyd。

代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=105;
int dis[MAXN][MAXN];
int n,d;
int a[MAXN],x[MAXN],y[MAXN];
inline getdist(int x1,int y1,int x2,int y2)
{
    return abs(x1-x2)+abs(y1-y2);
}
int main()
{
	scanf("%d%d",&n,&d);
	for(register int i=2;i<n;i++)
	    scanf("%d",&a[i]);
	for(register int i=1;i<=n;i++)
	    scanf("%d%d",&x[i],&y[i]);
	for(register int i=1;i<=n;i++)
	    for(register int j=1;j<=n;j++)
	        if(i!=j)dis[i][j]=d*getdist(x[i],y[i],x[j],y[j])-a[i];
	for(register int k=1;k<=n;k++)
	    for(register int i=1;i<=n;i++)
	        for(register int j=1;j<=n;j++)
	            dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	printf("%d",dis[1][n]);
	return 0;
}
```

---

## 作者：JackMerryYoung (赞：0)

# 前言

这道题是个图论，别看他是个蓝题，~~其实非常简单~~。

这题目坑点有点多，先说明一下，以便同学们写代码的时候不要被坑。

坑点一：不能使用 Dijkstra

至于为什么这么说，请看下面的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/muw99aaa.png)

（WA 的全是用 Dijkstra 的，AC 是用了 Floyd，CE 请忽略）

坑点二：读入 $a_i$

只读入 $N - 2$ 个点的恢复时间 $a_i$ ！这点一定要注意！

坑点三：读入坐标

读入的是坐标！不是距离！

解决了以上坑点，那么就正式开始讲题了！

# 正文

设 $i$, $j$ 两点间距离为 $dis_{i,j}$，那么根据曼哈顿距离公式，我们有：

$$
dis_{i,j} = |x_i - x_j| + |y_i - y_j|
$$

根据题目意思，Yaroslav 从点 $i$ 到点 $j$ 需要花 $d \times dis_{i,j}$ 的时间，而又可以恢复 $a_j$ 的时间。

那么联系到 Yaroslav 不能使他的时间为负数，那么我们就得思考一下最短路。

考虑以 Yaroslav 的时间为关键字，以对时间做出改变的点建图，我们发现从 $i$ 到 $j$ 可以对时间做出改变。

则以 $d \times dis_{i,j} - a_j$ （据题目意思）为边权建图，跑个最短路，即可 AC。

~~那么现在，一切都将真相大白。~~

具体考虑使用什么算法，建议 Floyd（不会被负边权卡掉的都可以）。（~~我才不会告诉你我用 Dijkstra 被负边权卡了第十个点呢~~）

# 代码

~~你们最想要的..~~ 

Talk is$\color{white}\text{n't}$ cheap, $\color{white}\text{Don't}$ show me the code..

``` cpp
#include <bits/stdc++.h>
using namespace std;

int N, D;
long long a[105];
long long x[105], y[105];
long long dis[105][105];

void add(int u, int v, int w);

int main()
{
	cin >> N >> D;
	for(int i = 2; i < N; i ++)
	{
		cin >> a[i];
	}

	for(int i = 1; i <= N; i ++)
	{
		cin >> x[i] >> y[i];
	}

    for(int i = 1; i <= N; i ++)
	{
        for(int j = 1; j <= N; j ++)
        {
            if(i != j)
                dis[i][j] = INT_MAX;
        }
    }

	for(int i = 1; i <= N; i ++)
	{
		for(int j = i + 1; j <= N; j ++)
		{
			dis[i][j] = (abs(x[i] - x[j]) + abs(y[i] - y[j])) * D - a[j];
			dis[j][i] = (abs(x[i] - x[j]) + abs(y[i] - y[j])) * D - a[i];
		}
	}
	
	for(int k = 1; k <= N; k ++)
	{
		for(int i = 1; i <= N; i ++)
		{
            for(int j = 1; j <= N; j ++)
            {
                if(i != k && j != k && i != j)
                {
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
                }
            }
        }
    }

	cout << dis[1][N] << endl;
	return 0;
}
```

---

## 作者：ztxtjz (赞：0)

## 【题意】
从第$1$个点经过$k$个点到第$n$个点，除起点和终点的点都有不同大小的时间供给，求最少需要多少时间。
## 【思路】
本题是最短路模板题。$i$到$j$的距离是$(abs(x[j]-x[i])+abs(y[j]-y[i]))*d-a[j]$，$a[j]$为到达$j$点可获得的供给大小。

由于数据范围$3≤n≤100$，可以用$floyd$来做，代码较为简单。
## 【代码】
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,d,a[105],x[105],y[105],dis[105][105];
void floyd()
{
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(dis[i][j]>dis[i][k]+dis[k][j]&&j!=k&&i!=k)
					dis[i][j]=dis[i][k]+dis[k][j];
}
int main()
{
	scanf("%d%d",&n,&d);
	for(int i=2;i<n;i++) scanf("%d",&a[i]); 
	for(int i=1;i<=n;i++) scanf("%d%d",&x[i],&y[i]);
	for(int i=1;i<=n;dis[i][i]=0,i++)
		for(int j=i+1;j<=n;j++)
            dis[i][j]=(abs(x[j]-x[i])+abs(y[j]-y[i]))*d-a[j],dis[j][i]=(abs(x[j]-x[i])+abs(y[j]-y[i]))*d-a[i];
	floyd();
	printf("%d",dis[1][n]);
	return 0;
}
```

---

## 作者：OIer_Hhy (赞：0)

这道题，一看就知道，肯定是一道最短路。

不会写 dijkstra、bellman-ford、SPFA 的我刚想退出，突然看到数据范围：$(3 \le n \le 100)$！

哈哈，这不是一道 Floyd 题吗？


先计算两点之间的曼哈顿距离，用一个数组 $a$ 存各点的权值（能恢复的点数），再开一个结构体 $b$ 表示点的坐标。先初始化每一条直达路的边权 $d \times dis(a_i.x,a_i.y,b_i.x,b_i.y)$（$i$ 点直接到 $j$ 点要花的时间），再 Floyd（可能经过其他点比直接去还快）。

`Floyd[1][n]` 就是我们要求的答案。

AC code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100;
int n,d,a[maxn+20],floyd[maxn+20][maxn+20];
struct node{
	int x,y;
}b[maxn+20];
int dis(int x1,int y1,int x2,int y2){
	return abs(x1-x2)+abs(y1-y2);
}
signed main(){
	cin>>n>>d;
	for(int i=2;i<=n-1;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i].y>>b[i].x;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			int x=dis(b[i].x,b[i].y,b[j].x,b[j].y);
			floyd[i][j]=x*d-a[j];
		}
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(i!=k&&j!=k&&i!=j)
					floyd[i][j]=min(floyd[i][j],floyd[i][k]+floyd[k][j]);
			}
		}
	}
	cout<<floyd[1][n]<<endl;
	return 0;
}

```

---

