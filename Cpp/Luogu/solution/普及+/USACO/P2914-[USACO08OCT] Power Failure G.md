# [USACO08OCT] Power Failure G

## 题目描述

A vicious thunderstorm has destroyed some of the wires of the farm's electrical power grid! Farmer John has a map of all $N$ ($2\le N \le 1000$) of the powerpoles, which are conveniently numbered $1\ldots N$ and located on integer plane coordinates $(x_i,y_i)$ ($-100000 \le x_i \le 100000, -100000 \le y_i \le 100000$).

Some $W$ ($1 \le W \le 10000$) power wires connect pairs of power poles $P_i$ and $P_j$ ($1 \le Pi \le N, 1 \le Pj \le N$).

He needs to get power from pole $1$ to pole $N$ (which means that some series of wires can traverse from pole $1$ to pole $N$, probably through some intermediate set of poles).

Given the locations of the $N$ poles and the list of remaining power wires, determine the minimum length of power wire required to restore the electrical connection so that electricity can flow from pole $1$ to pole $N$.  No wire can be longer than some real number $M$ ($0.0 < M \le 200000.0$).

As an example, below on the left is a map of the $9$ poles and $3$ wires after the storm. For this task, $M = 2.0$. The best set of wires to add would connect poles $4$ and $6$ and also poles $6$ and $9$.

```cpp
   After the storm              Optimally reconnected
3  . . . 7 9 . . . . .          3  . . . 7 9 . . . . .
                                          /
2  . . 5 6 . . . . . .          2  . . 5 6 . . . . . .
                                        /
1  2-3-4 . 8 . . . . .          1  2-3-4 . 8 . . . . .
   |                               |
0  1 . . . . . . . . .          0  1 . . . . . . . . .

   0 1 2 3 4 5 6 7 8 9             0 1 2 3 4 5 6 7 8 9
```

The total length is then $1.414213562 + 1.414213562 = 2.828427124$.

POINTS: 350


## 说明/提示

Just as in the diagram above.


As above.


## 样例 #1

### 输入

```
9 3 
2.0 
0 0 
0 1 
1 1 
2 1 
2 2 
3 2 
3 3 
4 1 
4 3 
1 2 
2 3 
3 4 
```

### 输出

```
2828 
```

# 题解

## 作者：sxyugao (赞：5)

由题意可得这是一道单源最短路，从第一个点到第n个点的单源最短路，先在原来有电线的两点之间连一条边，代价为0，再建图，每两点之间先尝试建一条边，如果原来有边或代价大于m，则依然是无穷大，最后建图完成后跑一遍Dijkstra就好。
```cpp
const oo=maxlongint div 2;//常量，定义无穷大
var
n,w,i,j,k,p1,p2:longint;
m:double;
a:array[1..1000,1..1000]of double;
dist:array[1..1000]of double;
vis:array[1..1000]of boolean;
x,y:array[1..1000]of longint;
function calc(a,b,c,d:longint):double;//计算两点距离
  begin exit(sqrt(sqr(a-b)+sqr(c-d)));end;
function min(a,b:double):double;
  begin if a<b then exit(a);exit(b);end;
begin
read(n,w,m);
for i:=1 to n do read(x[i],y[i]);
for i:=1 to n do
  for j:=1 to n do
    a[i,j]:=oo;//初始化a数组，各点之间的距离为无穷大
for i:=1 to w do
  begin
    read(p1,p2);
    a[p1,p2]:=0;a[p2,p1]:=0;//原来如果有电线经过的代价为0
  end;
for i:=1 to n-1 do
  for j:=i+1 to n do
    begin
      a[i,j]:=min(a[i,j],calc(x[i],x[j],y[i],y[j]));
      //原来有电线的不架电线（代价为0）
      //没有电线的架电线（即两点之间的距离）
      if a[i,j]>m then a[i,j]:=oo;
      //如果新的电线大于了m，那么还是无穷大
      a[j,i]:=a[i,j];
    end;
//以下为最基本的最短路——Dijkstra，不解释
//若有疑问，请移步P3371【模板】单源最短路径
for i:=1 to n do dist[i]:=oo;
dist[1]:=0;
for i:=1 to n do
  begin
    k:=-1;
    for j:=1 to n do
      if((k=-1)or(dist[k]>dist[j]))and(not vis[j])then k:=j;
    if k=-1 then break;vis[k]:=true;
    for j:=1 to n do
      if(not vis[j])and(dist[k]+a[k,j]<dist[j])then
        dist[j]:=dist[k]+a[k,j];
  end;
if dist[n]<>oo then write(trunc(dist[n]*1000))else write(-1);
//输出答案的格式别忘了
end.
```

---

## 作者：Nanchtiy (赞：3)

安利个人blog：
https://www.cnblogs.com/BrokenString/
哇
这题目在暑假培训的时候考到
当时用Floyed会T掉
看楼下都是用Dijkstra
难道没有人用**优雅的SPFA**吗？
#### 思路
用前向星构建整个图
注意每一条边都不能超过len（也就是题目中的m）
所以存图的时候注意一下这一点就行了
其他就跟SPFA一样套板子
代码中还有详细注解
注意坑点：数组开大一点 没开大的我RE了2次
#### 代码
```
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int n,m,cnt;
double len;
int exist[500005];//判断是否在队中 
int team[2000020];//队列 
int head[500005];
double dis[500005];//从1到n的距离 
int t=0,w=1;
struct ele
{
	double x;
	double y;
}ele[100005];//电线杆的坐标 
struct edge
{
	int next;
	int to;
	double w;
}e[5000005]; 
void add(int u,int v,double w)
{
	e[++cnt].w=w;
	e[cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt;
}//前向星图 
double dist(int i,int j)
{
    double x1=ele[i].x;
    double y1=ele[i].y;
    double x2=ele[j].x;
    double y2=ele[j].y;
    double d=hypot(x1-x2,y1-y2);//判断电线杆之间的距离
	                            //据楼下的dalao说用sqrt会爆就没用
								//用了求直角三角形斜边长的函数<cmath> 
    return d;
}
int main()
{
	cin>>n>>m>>len;
	for(int i=1;i<=n;i++)
	cin>>ele[i].x>>ele[i].y;
	for(int i=1;i<=n;i++)
	dis[i]=99999999;//初始化 
	for(int i=1;i<=n;i++)
	for(int j=i+1;j<=n;j++)
	{
		if(dist(i,j)<=len)//如果没有超过len就可以加入边 
        {
			add(i,j,dist(i,j));
		    add(j,i,dist(i,j));
		}
	}
	for(int i=1;i<=m;i++)
    {
        int x,y;
        cin>>x>>y;
        add(x,y,0);
		add(y,x,0);//如果已经有电线就不用再花费距离 
    }
    dis[1]=0;//常规SPFA开始 
    team[1]=1;
    while(t<w)
    {
		t++;
		int u=team[t];
		exist[u]=0;
		for(int i=head[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if(dis[v]>dis[u]+e[i].w)
			{
				dis[v]=dis[u]+e[i].w;
				if(!exist[v])
				{
					w++;
					exist[v]=1;
					team[w]=v;
				}
			}
		}
	}
	if(dis[n]==99999999)//如果到不了 
	cout<<"-1";
	else
	cout<<int(dis[n]*1000);//强制转换int类型 
}
```

---

## 作者：柠檬布丁吖 (赞：3)

是一道很有意思的最短路题目哦！

## 题意

因为邪恶的暴风雨，可怜的 FJ 需要你帮忙修复电路。用电路使 编号 $1
\sim 9$ 的电站连通，恢复电路。

![邪恶的暴风雨！](https://cdn.luogu.com.cn/upload/image_hosting/oghzgy63.png)

（如图，图为题中高配版。配合样例食用更佳）

每个电站的坐标都在图中标出，并且标上了序号。红色的电线是完好无损的。需要你在两个电站中新连接的线不能超过一个限制 $M$，求在原来电线的基础上计算出需要修复电路的距离。

## 为什么使用最短路

若网络中的每条边都有一个数值（长度、成本、时间等），则找出两个结点之间总权和最小的路径就是最短路问题。

根据题意，需要我们选择最短的路程（电线的长度）将编号 $1\sim n$ 的点连通，所以使用最短路算法解决。

## 思路

把这一切抽象成图，跑最短路。已经有部分的边，因为这些是完好无损的边，所以在图中这些边没有耗费，边的权值为 $0$。剩下的边初始化为点与点在坐标中的距离。

Floyd 算法会超时。跑 Dijkstra，时间复杂度 $O((n+m)\log n)$。当边权值超过限制 $M$ 时，不更新答案。

当最终答案仍然为初始化的一个很大的数时，无解。

图中给出的蓝色的电线就是我们需要连上的。其它的会在代码里注释。也可以用用优先队列优化 Dijkstra 算法。

## ACcode

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>

using namespace std;

const int maxn=2e3+55;
const int oo=2e9+55;
int N,W;
double M;
struct zb{
	double x,y;
}z[maxn];
double g[maxn][maxn],dis[maxn];
bool vis[maxn];

//计算点与点在坐标中的距离 
double coordinate(zb x,zb y){
	return sqrt((x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y));
}

signed main(void){
	
	cin>>N>>W;
	cin>>M;
	
	for(int i=1;i<=N;i++){
		cin>>z[i].x>>z[i].y;
	}	
	
	//建图初始化 
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			g[i][j]=coordinate(z[i],z[j]);
		}
	}
	
	for(int i=1;i<=W;i++){
		int x,y;
		cin>>x>>y;
		g[x][y]=g[y][x]=0;
	}
	
	//答案数组初始化 
	for(int i=1;i<=maxn;i++){
		dis[i]=oo;
	}
	
	//Dijkstra 
	dis[1]=0;
	for(int i=1;i<=N;i++){
		int tmp=oo,id;
		for(int j=1;j<=N;j++){
			if(vis[j]==0 && dis[j]<tmp){
				tmp=dis[j];
				id=j;
			}
		}
		vis[id]=1;
		for(int j=1;j<=N;j++){
			if(dis[j]>dis[id]+g[id][j] && g[id][j]<M && j!=id){
				dis[j]=dis[id]+g[id][j];
			}
		}
	}
	
	if(dis[N]==oo){
		printf("-1\n");
	} else {
		cout<<(int)(dis[N]*1000)<<endl;
	}
	
	return 0;
}
```


---

## 作者：伟大的王夫子 (赞：3)

写了好久才不容易过的

首先，此题是个单源最短路问题，对于电线$(x, y)$,则令$x \to y$的边权为0

其余的边权则按照距离公式计算，若大于$m$,则赋值无穷大

最后跑一遍dijkstra。

刚开始以为只有$O(n^3)$,能用Floyd，然后T了

所以必须用dijkstra，复杂度$O((n+m)\log n)$

最后输出$\lfloor(d[n] \times 1000)\rfloor$（向下取整）

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, w;
double m, d[1001];
bool v[1001];
double a[1001][1001];
struct rec {
	double x, y;
} p[1001];
int main() {
//	freopen("data.in", "r", stdin);
//	freopen("data.out", "w", stdout);
	cin >> n >> w >> m;
//	for (register int i = 1; i <= n; ++i)
//		for (register int j = 1; j <= n; ++j)
//			a[i][j] = 1e18;
	for (register int i = 1; i <= n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
	for (register int i = 1; i <= n; ++i) 
		for (register int j = 1; j <= n; ++j) {
			a[i][j] = sqrt(pow(p[i].x - p[j].x, 2) + pow(p[i].y - p[j].y, 2));
			if (a[i][j] > m) a[i][j] = 1e18;
		}
	for (register int i = 1; i <= w; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		a[y][x] = a[x][y] = 0;
	}
	priority_queue<pair<double, int> > q;
	for (register int i = 1; i <= n; ++i) d[i] = 1e18;
	q.push(make_pair(0.0, 1));
	memset(v, 0, sizeof v);
	d[1] = 0;
	while (q.size()) {
		int x = q.top().second;
		q.pop();
		if (v[x]) continue;
		v[x] = 1;
		for (register int i = 1; i <= n; ++i) {
			double z = a[x][i];
			if (z == 1e18) continue;
			if (d[i] > d[x] + z) {
				d[i] = d[x] + z;
				q.push(make_pair(-d[i], i));
			}
		}
	}
	if (d[n] == 1e18) puts("-1");
	else printf("%.0lf", floor(d[n] * 1000));
} 
```
如果想要更好的体验，可以到[我的博客](https://www.luogu.org/blog/I-AK-IOI/)去看

---

## 作者：火车司机 (赞：2)

## 简要分析

如果读得懂这道题的话应该不难看出这是一道最短路（~~可以说是非常考验语文能力了~~

这道题的难点还是在于建图，图建好了以后跑一遍最短路就行了，这里我用的是 $dijkstra$

首先，对于幸存的电线，我们直接建一条边权为 $0$ 的边，表示不需要架设新的电线就可以通电

对于剩下的点，我们可以先根据勾股定理算出需要架设的电线长度，如果长度超过了 $m$ ，那我们就跳过，否则就建一条边

此外，还需要注意以下两点

- 此题是**无向图**，因此每次需要建边要建**两条边**

- 由于输出格式未翻译，大家需要根据样例推出我们需要输出的是 **$1000$ 倍的最短路长度保留整数**

## 完整代码

```cpp
#include <bits/stdc++.h>
#define ri register int
using namespace std;
int n, w, x, y, tot = 0, h[1005] = {0}, vis[1005] = {0};
double m, d, dis[1005] = {0};
struct node {
	double d;
	int p;
	bool operator < (const node &x) const {
		return x.d < d;
	}
} t;
struct crdnt {	//电线杆坐标
	double x, y;
} a[1005] = {0};
struct edge {
	int u, v;
	double w;
} e[1000005] = {0};
priority_queue <node> q;
inline void add(int u, int v, double w) {
	e[++tot].u = h[u], e[tot].v = v, e[tot].w = w, h[u] = tot;
}
int main() {
	scanf("%d%d%lf", &n, &w, &m);
	for (ri i = 1; i <= n; i++) scanf("%lf%lf", &a[i].x, &a[i].y), dis[i] = 1e9 + 7;
	for (ri i = 1; i <= w; i++) scanf("%d%d", &x, &y), add(x, y, 0), add(y, x, 0);
	for (ri i = 1; i <= n; i++)
		for (ri j = i + 1; j <= n; j++) {
			d = sqrt((a[i].x - a[j].x) * (a[i].x - a[j].x) + (a[i].y - a[j].y) * (a[i].y - a[j].y));
        		//不知道为什么我用了sqrt并没有炸
			if (d <= m) add(i, j, d), add(j, i, d);
		}
	dis[1] = 0, q.push((node) {0,1});	//用dijkstra跑一遍最短路
	while (!q.empty()) {
		t = q.top(), q.pop();
		if (vis[t.p]) continue;
		vis[t.p] = 1;
		for (ri i = h[t.p]; i; i = e[i].u)
			if (dis[t.p] + e[i].w < dis[e[i].v])
            	dis[e[i].v] = dis[t.p] + e[i].w, q.push((node) {dis[e[i].v],e[i].v});
	}
	if (dis[n] == 1e9 + 7) printf("%d", -1);
	else printf("%d", (int)(dis[n] * 1000));	//注意题意要求输出什么
	return 0;
}
```


---

## 作者：sto__Liyhzh__orz (赞：1)

[本题传送门](https://www.luogu.com.cn/problem/solution/P2914)

从题意中易得：本题是一道从第 $1$ 个点至第 $n$ 个点的单源最短路。

先将原有电线的两点连边，代价为 $0$。

接着再建图，两点之间~~直线距离最短~~，呸，背岔了。

两点之间先连上一条边，若这里原来本就有边，或代价大于 $m$，则为无穷大。

建图后跑一遍 `Dijkstra`（~~题解过审啦~~）即可。

---

## 作者：Loser_King (赞：1)

USACO的（几乎是）最短路模板题。

稍微加了一点计算几何和小技巧。

## 题意

>  平面中有 $n$ 个点，有 $m$ 条线段连接着它们。求至少要连接多少长度的线段，使得点 $1$ 和点 $n$ 连通。

## 做法

首先我们需要知道一个简单的知识：

对于平面中的两点 $A(x_1,y_1),\;B(x_2,y_2)$ ，有 $\overline{AB}=\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$。

知道了这个，就可以考虑两点间的距离了。

如果两点间已有线段，那么开始时考虑把它们之间的距离设为 $0$ ，

否则就是两点间的距离。如果大于 $m$ ，就是 INF（因为不可达）。

然后跑一遍单源最短路就好了。

（由于 $n\le 1000$ ，所以即使不加优化的 $\text{Dijkstra}$ 也是可以过的）

## 代码

```c++
//P2914 AC Code
//written by Loster_King(159686)
//124ms /  8.26MB /  976B C++ O2
#include<bits/stdc++.h>
#define inf 1000000000.0
using namespace std;
int const N=2333;
int n,w,x[N],y[N],vis[N],ans;
double m,f[N][N],d[N];
double dis(int i,int j){
    return sqrt(1.0*(x[i]-x[j])*(x[i]-x[j])+1.0*(y[i]-y[j])*(y[i]-y[j]));
    //注意要乘1.0，因为x和y这样相乘可能会爆int，所以需要先转成浮点型
}
int main(){
    scanf("%d%d%lf",&n,&w,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)f[i][j]=inf;//初始化
    for(int i=1;i<=n;i++)scanf("%d%d",&x[i],&y[i]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            double k=dis(i,j);
            if(k<m)f[i][j]=k;//判断大于还是小于m
        }
    for(int i=1;i<=w;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        f[a][b]=f[b][a]=0;//有线段，距离0
    }
    for(int i=2;i<=n;i++)d[i]=inf;
    for(int i=1;i<=n;i++){
        int k=0;
        for(int j=1;j<=n;j++)if(!vis[j]&&(!k||d[k]>d[j]))k=j;
        vis[k]=1;
        for(int j=1;j<=n;j++)if(!vis[j]&&d[j]>d[k]+f[k][j])d[j]=d[k]+f[k][j];
    }//dijkstra
    if(d[n]==inf)puts("-1");else printf("%d",int(d[n]*1000));//注意答案要乘1000取整
}
```



---

## 作者：lshhhhhh (赞：1)

这题其实就是最短路，把中间有连线的电线杆之间的距离设为零，开头先求一遍别的电线杆之间的距离，然后用Dijkstra就可以啦

附上伪代码：

```cpp
    for(int i=2;i<=n;i++)l[i]=-1;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            ch[i][j]=hypot(x[i]-x[j],y[i]-y[j]);//这是一个求直角三角形斜边长的函数，定义在头文件cmath中，一定得用这个，用sqrt求就会炸
        }
    }
    for(int i=1;i<=w;i++)scanf("%d%d",&pi,&pj),ch[pi][pj]=ch[pj][pi]=0;
    while(flag[n]==0)
    {
        int z=-1;
        for(int i=1;i<=n;i++)
        {
            if(flag[i]==0 && l[i]>=0 &&  (z<0 || l[i]<l[z]))z=i;
        }
        if(z==-1){printf("-1\n");return 0;}
        flag[z]=1;
        for(int i=1;i<=n;i++)
        {
            if(flag[i]==0 &&  ch[z][i]<=m && (l[i]<0 || l[z]+ch[z][i]<l[i]))l[i]=l[z]+ch[z][i];
        }
}
```

---

## 作者：rnf5114 (赞：1)

堆优化 dij 最短路板子题。

直接暴力建边即可，枚举每个点然后计算它们直接的距离，如果距离大于 $w$ 则不连边，对于还幸存的电线所对应两个电能中转点之间则连接一条边权为 $0$ 的边即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,w;
double m,dis[1010],y[1010],x[1010];
struct node{
	int y;
	double z;
};
vector<node>v[1010];
priority_queue<pair<double,int>>q;
double calc(int i,int j){
	return sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
}
void dij(){
	for(int i=1;i<=n;i++)
		dis[i]=1e15+10;
	dis[1]=0;
	q.push({0,1});
	while(!q.empty()){
		pair<int,int>tmp=q.top();
		q.pop();
		if(-tmp.first>dis[tmp.second])
			continue;
		for(int i=0;i<v[tmp.second].size();i++){
			int x=tmp.second,tmp1=v[tmp.second][i].y;
			if(dis[x]+v[x][i].z<dis[tmp1])
				dis[tmp1]=dis[x]+v[x][i].z,q.push({-dis[tmp1],tmp1});
		}
	}
}
signed main(){
	cin>>n>>w>>m;
	for(int i=1;i<=n;i++)
		cin>>x[i]>>y[i];
	for(int i=1;i<=w;i++){
		int x,y;
		cin>>x>>y;
		v[x].push_back({y,0});
		v[y].push_back({x,0});
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(j!=i&&calc(i,j)<=m)
				v[i].push_back({j,calc(i,j)});
	dij();
	if(dis[n]==1e15+10)
		cout<<-1;
	else
		cout<<long(dis[n]*1000);
	return 0;
}

/*
       ┏┓　　　┏┓
     ┏┛┻━━━┛┻┓
     ┃　　　　　　　┃
     ┃　　　━　　　┃
     ┃　┳┛　┗┳　┃
     ┃　　　　　　　┃
     ┃　　　┻　　　┃
     ┃　　　　　　　┃
     ┗━┓　　　┏━┛Codes are far away from bugs with the animal protecting
         ┃　　　┃    神兽保佑,代码无bug
         ┃　　　┃
         ┃　　　┗━━━┓
         ┃　　　　　 ┣┓
         ┃　　　　 ┏┛
         ┗┓┓┏━┳┓┏┛
           ┃┫┫　┃┫┫
           ┗┻┛　┗┻┛     ○|￣|_

*/

```

---

## 作者：yx666 (赞：0)

# P2914 Power Failure G 题解

## Part 1：题意

### Part 1.1：题干

在一个平面直角坐标系中，有 $n$ 个中转点，编号为 $1\dots n$（$n\in[2,1\times10^3]$），其中第 $i$ 个点的坐标为 $(x_i,y_i)$（$x_i,y_i\in[-1\times10^5,1\times10^5]$）。

有 $w$（$w\in[1,1\times10^4]$）条电线，每条电线连接两个点 $p_i$ 与 $p_j$（$p_i,p_j\in[1,n]$）。

现在，你可以任意连接这些中转点，使得从点 $1$ 到 $n$ 联通，且新添电线总长越短越好。但是，对于单条电线，其长度不能超过 $m$（$m\in[0,2\times10^5]$）。

请输出最短的新添电线总长乘 $1\times10^3$ 后的整数部分。如果无法使得点 $1$ 到 $n$ 联通，输出 `-1`。

### Part 1.2：输入

- 第一行：$n$，$w$。

- 第二行：$m$。

- 第 $3$ 到 $n+2$ 行：$x_i$，$y_i$。

- 第 $n+3$ 到 $n+2+w$ 行：$p_i$，$p_j$。

### Part 1.3：限制

- $n\in[2,1\times10^3],w\in[1,1\times10^4]$。

- $m\in[0,2\times10^5]$。

- $x_i,y_i\in[-1\times10^5,1\times10^5]$。

- $p_i,p_j\in[1,n]$。

- 除 $m$ 为小数外，其他皆为整数。

- 时间限制：$1$ s，内存限制：$125$ MB。

## Part 2：分析

最短路板子题（坑点有点多）。

### Part 2.1：建边

- 遍历所有顶点，依次尝试与其他顶点建边。

- 边的边权，为两个顶点的几何距离（勾股距离）。

- 限制：边权（距离）不大于 $m$。

- 给出的边（已有电线），边权为 $0$。

### Part 2.2：跑最短路

跑 `Dijkstra` 堆优化，理由：

1. 单源最短路。

2. 无负边权。

3. 上面建边时间复杂度 $O(n^2)$，跑其他的可能时间过不去（也不知道卡没卡 `SPFA`）。

### Part 2.3：坑点

1. 已有的电线，不能仅仅将边权改为 $0$，还是要老实加边。否则 $80$ pts（[WA](https://www.luogu.com.cn/record/154448081) on #5，#17，#18，#19）。

2. 求两点距离，开平方根里面的可能爆 `int`，导致 $90$ pts（[WA](https://www.luogu.com.cn/record/154384892) on #6，#20）。

## Part 3：代码实现

`vector` 边集数组与 `Dijkstra`。

``` cpp
#include<bits/stdc++.h>
using namespace std;

#define N 1024
#define M 10005
#define ll long long
#define pii pair<int,int>

const double inf=1e10;

inline double get_dis(const pii&a,const pii&b){
	return sqrt(
		(ll)(a.first-b.first)*(a.first-b.first)+(ll)(a.second-b.second)*(a.second-b.second)
		);
}	// 返回两点间距离

double dis[N];
inline void dij();

int n,w;
double m;
vector<pii> pos;			// 点的编号对应位置
vector<vector<int> >mp;		// 存图
vector<vector<double> >val;	// 边集数组存边权
signed main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	cin>>n>>w>>m;
	
	pos.resize(n+1);
	for(int i=1;i<=n;++i){
		cin>>pos[i].first>>pos[i].second;
	}
	
	mp.resize(n+1);
	val.resize(n+1,vector<double>(n+1));
	for(int i=2;i<=n;++i){
		for(int j=1;j<i;++j){
			double t=get_dis(pos[i],pos[j]);
			if(t<=m){
				val[i][j]=val[j][i]=t;
				mp[i].push_back(j);
				mp[j].push_back(i);
			}else{
				val[i][j]=val[j][i]=inf;
			}
		}
	}
	
	int a,b;
	for(int i=1;i<=w;++i){
		cin>>a>>b;
		mp[a].push_back(b);
		mp[b].push_back(a);
		val[a][b]=val[b][a]=0.0f;
	}
	
	dij();
	
	cout<<(dis[n]==inf?-1:(long long)(dis[n]*1000));
	return 0;
}

bitset<N>vis;
inline void dij(){
	fill(dis,dis+1+n,inf);
	dis[1]=0.0f;
	
	using T=pair<double,int>;
	priority_queue<T,vector<T>,greater<T> >q;
	q.push({dis[1],1});
	
	int now;
	while(q.size()){
		now=q.top().second;
		q.pop();
		
		if(vis[now]) continue;
		vis[now]=1;
		
		for(auto to:mp[now]){
			if(!vis[to]&&dis[to]>dis[now]+val[now][to]){
				dis[to]=dis[now]+val[now][to];
				q.push({dis[to],to});
			}
		}
	}
	return;
}
```

---

## 作者：keepwatcher_kensap (赞：0)

## Part 1 题意

有 $n$ 个电能中转点，$w$ 条电线分别连接着 $p_{1 \dots w},q_{1 \dots w}$，可以新添加电线连接两点但新电线的长度不能超过 $m$。求要让 $1$ 和 $n$ 联通至少要添加长度为多少的电线。

## Part 2 思路

要求新添加的最短长度，不难想到这是一个**最短路**题。

我们可以先将所有能连接起来的电能中转站连接起来，连接长度为两点的**欧几里得距离**。如果两点原本就有电线连接，则将这两点的距离设置为 $0$。

最后，用 Dijkstra 算法求出 $1$ 到 $n$ 的最短路即可。

## Part 3 代码

```
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int n,m,x[maxn],y[maxn],u[maxn],v[maxn];
double up,t[1005][1005],dis[maxn];
bool vis[maxn];
double distance(int i,int j)
{
    return sqrt((double)(x[i]-x[j])*(x[i]-x[j])+(double)(y[i]-y[j])*(y[i]-y[j]));
}
inline double dijkstra()
{
	for (int i=1;i<=n;i++) dis[i]=1000000000.0;
	dis[1]=0;
	for (int i=1;i<=n;i++)
	{
		int k=-1;
		for (int j=1;j<=n;j++)
		{
			if (!vis[j] && (k==-1 || dis[j]<dis[k])) k=j;
		}
		vis[k]=true;
		for (int j=1;j<=n;j++)
		{
			if (!vis[j] && dis[j]>dis[k]+t[k][j]) dis[j]=dis[k]+t[k][j];
		}
	}
	return dis[n];
}
int main()
{
	cin>>n>>m>>up;
	for (int i=1;i<=n;i++) cin>>x[i]>>y[i];
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++) t[i][j]=1000000000.0;
	}
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++)
	{
		if (i==j) continue;
		double distan=distance(i,j);
		if (distan<up) t[i][j]=t[j][i]=distan;
	}
	for (int i=1;i<=m;i++)
	{
		cin>>u[i]>>v[i];
		t[u[i]][v[i]]=t[v[i]][u[i]]=0;
	}
	double result=dijkstra();
	if (result==1000000000.0) cout<<"-1"<<endl;
	else cout<<int(result*1000)<<endl;
	return 0;
}
```

---

## 作者：rfsfreffr (赞：0)

很明显这是一道最短路得题目。

题目大意：给你一些点，其中有些点之间已经有了电线，求从点1到点n最少要建多少长度的电线。输出最优解答案*1000再向下取整。

对于那些已近有电线的点，可以直接将两点距离初始化为0,然后就可以直接跑最短路了，我用的算法是迪杰斯特拉，算法效率$O(n^2)$

具体看代码注释

# 代码:
```cpp
#include <bits/stdc++.h>
using namespace std;
struct oi{
	double x,y;
}a[100001];
int n,w;
double m;
double calc_dis(oi x,oi y){//计算两点之间的距离
	return sqrt((x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y));
}

double mp[1001][1001];//记录两点之间的距离的数组
double dis[1001];//用了跑最短路得数组
int vis[1001];
int main(){
	cin>>n>>w;
	cin>>m;	
	for(int i=1; i<=n; i++) {//读入点的坐标
		cin>>a[i].x>>a[i].y;
	}
	for(int i=1; i<=n; i++){//初始化点之间的距离
		for(int j=1; j<=n; j++){
			mp[i][j]=calc_dis(a[i],a[j]);
		}
	}
	for(int i=1; i<=w; i++){//两点之间有电线的店，将距离初始化为0
		int x,y;
		scanf("%d%d",&x,&y);
		mp[x][y]=mp[y][x]=0;
	}
	for(int i=1; i<=1000; i++) dis[i]=2e9;//迪杰斯特拉的初始化
	dis[1]=0;//因为求得是1~n得最短路径，所以将dis[1]设置为0
	for(int i=1; i<=n; i++){
		int v;
		double cnt=2e9;
		for(int j=1; j<=n; j++){//找到当前距离最小的点
			if(vis[j]==0) {
				if(dis[j]<cnt){
					cnt=dis[j];
					v=j;
				}
			}
		}
		vis[v]=1;
		for(int j=1; j<=n; j++){
			if(mp[v][j]<m&&j!=v){//如果电线建造的长度比m小才能进行松弛
				dis[j]=min(dis[j],dis[v]+mp[v][j]);
			}
		}
	}
	if(dis[n]==2e9) cout<<-1<<endl;//特殊情况，如果无论如何都无法从1走到n就按照题意输出-1
	else printf("%d\n",(int)(dis[n]*1000));//按题意输出答案
	return 0;
}
```

---

