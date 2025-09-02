# [USACO2.4] 牛的旅行 Cow Tours

## 题目描述

Farmer John 的农场里有很多 **牧区**。有的路径连接一些特定的牧区。**一片所有连通的牧区** 称为一个 **牧场**。但是就目前而言，你能看到至少有两个牧区通过任何路径都不连通。这样，Farmer John 就有 **多个** 牧场了。

John 想在牧场里添加 **恰好** 一条路径。对这条路径有以下限制：

一个牧场的 **直径** 就是牧场中 **最远** 的两个牧区的距离（本题中所提到的所有距离指的都是 **最短的距离**）。考虑如下的有 5 个牧区的牧场，牧区用 `*` 表示，路径用直线表示。每一个牧区都有自己的坐标：

```plain
                (15,15) (20,15)
                 D       E
                 *-------*
                 |     _/|
                 |   _/  |
                 | _/    |
                 |/      |
        *--------*-------*
        A        B       C
     (10,10)  (15,10) (20,10)
```
这个牧场的直径大约是 $12.07106$，最远的两个牧区是 A 和 E，它们之间的最短路径是 $A \to B \to E$。

这里是 John 的另一个牧场：

```plain
                         *F(30,15)
                        / 
                      _/  
                    _/    
                   /      
                  *------* 
                  G      H
                  (25,10)   (30,10)
```

在这个例子中，他刚好有这两个牧场。John 将会在这两个牧场中各选一个牧区（即从 $\{A,B,C,D,E\}$ 中选择一个牧区，从 $\{F,G,H\}$ 中选择一个牧区），然后用一条路径将它们连起来，使得连通后这个新的更大的牧场的直径尽可能小。

注意，如果两条路径中途相交，我们不认为它们是连通的。只有两条路径在同一个牧区相交，我们才认为它们是连通的。

输入文件包括牧区、它们各自的坐标，还有一个如下的对称邻接矩阵：

```plain
　 A  B  C  D  E  F  G  H 
A  0  1  0  0  0  0  0  0
B  1  0  1  1  1  0  0  0
C  0  1  0  0  1  0  0  0
D  0  1  0  0  1  0  0  0
E  0  1  1  1  0  0  0  0
F  0  0  0  0  0  0  1  0
G  0  0  0  0  0  1  0  1
H  0  0  0  0  0  0  1  0
```

其他邻接表中可能直接使用行列而不使用字母来表示每一个牧区。输入数据中不包括牧区的名字。

输入文件 **至少** 包括两个不连通的牧区。

请编程找出一条连接属于两个 **不同牧场** 的牧区的路径，使得连上这条路径后，这个更大的新牧场的直径尽可能小。输出在所有合法的连接方案中，新牧场直径的最小值。

## 说明/提示

样例对应题目描述中的情况。

最优解是连接 C 牧区和 G 牧区，连接后图上只有一个牧场。这个牧场的直径为 $A \to B \to C \to G \to F$，长度约为 $22.071068$。可以证明不存在更优的方案。

USACO 2.4


## 样例 #1

### 输入

```
8
10 10
15 10
20 10
15 15
20 15
30 15
25 10
30 10
01000000
10111000
01001000
01001000
01110000
00000010
00000101
00000010```

### 输出

```
22.071068
```

# 题解

## 作者：heidoudou (赞：189)

这一题非常之绕。首先需要弄清楚以下几个概念：

1. 牧区： 对应一个点。
2. 牧区之间的距离：实际上是两点之间的 **最短路**。 不要理解成欧几里得距离。只有 **直接连接** 的时候，才可以计算欧几里得距离。
3. 牧场： 一个连通块。
4. 牧场直径： 一个牧场的直径是这个牧场所有的牧区（点）之间 **距离** 的最大值。 说的绕一点就是 **最短路**的最大值。
5. 使用一条边连接两个牧场，使得合成的一个新的牧场的直径最小。意思是加入一条边之后，使得新的牧场的所有点对之间 **最短路** 的最大值 最小。

这道题的正解思路是：

1. 使用 DFS 对连通块染色标记：区分牧场。$O(V + E) = O(n^2)$
2. 使用 Floyd-Warshall 算法计算所有点对之间的 **最短路**。 $O(n^3)$
3. 计算每个牧场中，每个牧区点到其他点的 **最短路** 的最大值。（后面加边的时候要用）
4. 计算每个牧场中，所有最短路的最大值，即每个牧场的直径。 这个可以与 3 一起计算。 $O(n^2)$
5. 最后是找答案：对任意两个点，先判断是否同一个牧场。如果不是，考虑加入一条边，变成一个新的牧场。可以直接计算出通过这条边的最短路的最大值。 需要注意的是，通过这条边的最短路的最大值不一定是新牧场的所有最短路的最大值。这里需要比较三个值（牧场 A 的所有最短路的最大值； 牧场 B 的所有最短路的最大值， 加边后通过这条边的最短路的最大值），才能得到正确的新牧场的直径。 遍历所有点对（或者一半）， 找出 “新直径” 的最小值。 $O(n^2)$


最后的时间复杂度是 $O(n^3)$。 空间复杂度也只是 $O(n^2)$。


```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point
{
    int x, y;
    double distance(const Point &b)
    {
        return sqrt((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y));
    }
};

const int MAX_N = 150;
const double INF = 1e20;
int n;
int field[MAX_N] = {0};
double diameter[MAX_N + 1] = {0};
double dist[MAX_N][MAX_N];

void dfs(int i, int id)
{
    field[i] = id;
    for (int j = 0; j < n; ++j)
        if (!field[j] && dist[i][j] < INF)
            dfs(j, id);
}

int main()
{
    int i, j, k;
    Point a[MAX_N];
    scanf("%d\n", &n);
    for (i = 0; i < n; ++i)
        scanf("%d %d\n", &a[i].x, &a[i].y);
    
    char s[MAX_N + 1];
    for (i = 0; i < n; ++i)
    {
        scanf("%s", s);
        for (j = 0; j < n; ++j)
        if (s[j] == '1' || i == j)
            dist[i][j] = a[i].distance(a[j]);
        else
            dist[i][j] = INF;
    }

    // 1. DFS
    int id = 0;
    for (i = 0; i < n; ++i)
        if (!field[i])
            dfs(i, ++id);
    
    // 2. Floyd-Warshall
    for (k = 0; k < n; ++k)
        for (i = 0; i < n; ++i)
            for (j = 0; j < n; ++j)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    // 3.4. max_sp: find max shortest path and diameter;
    double max_sp[MAX_N];
    for (i = 0; i < n; ++i)
    {
        max_sp[i] = 0.0;
        for (j = 0; j < n; ++j)
            if (dist[i][j] < INF)
                max_sp[i] = max(max_sp[i], dist[i][j]);
        diameter[field[i]] = max(diameter[field[i]], max_sp[i]);
    }

    // 5. find answer
    double min_d = INF, max_d;
    for (i = 0; i < n; ++i)
        for (j = i + 1; j < n; ++j)
            if (field[i] != field[j])
            {
                max_d = max(max(diameter[field[i]], diameter[field[j]]),
                            max_sp[i] + a[i].distance(a[j]) + max_sp[j]);
                min_d = min(min_d, max_d);
            }

    printf("%.6f\n", min_d);

    return 0;
}
```


---

## 作者：StudyingFather (赞：66)

设将要合并的两个连通块为 $A,B$，新添加的边为 $(i,j)$（其中 $i \in A$，$j \in B$），新连通块为 $S$。

考虑连上 $(i,j)$ 边后，$S$ 连通块直径是怎样构成的。可以分为三种情况：

1. $A$ 连通块的直径；
2. $B$ 连通块的直径；
3. $A$ 连通块里从 $i$ 点出发的最远路径 + $(i,j)$ 这一条边 + $B$ 连通块里从 $j$ 点出发的最远路径。

实现的时候，因为 $n \leq 150$，可以用 Floyd 算法求出任意两点间最短路径和从任意一点出发的最远路径，然后用并查集维护连通块和每个连通块的直径。

随后枚举不在同一连通块内的两个点 $i,j$，取上面三种情况中的最大值作为新连通块的直径即可。

时间复杂度为 $O(n^3)$。

需要注意的是，有不少做法（包括《信息学竞赛一本通》（第三版）上介绍的做法，不知道这个问题在后面再版的时候有没有修正）只考虑了上面的情况 3，简单地用这条路径作为新连通块的直径，这样的做法显然是错误的。但原数据较弱，这种错解可以通过所有数据。

```cpp
// Problem: P1522 [USACO2.4]牛的旅行 Cow Tours
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P1522
// Memory Limit: 128 MB
// Time Limit: 1000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;
struct dsu {
  int fa[155], n;
  void init(int n) {
    this->n = n;
    for (int i = 1; i <= n; i++) fa[i] = i;
  }
  int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
  void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    fa[y] = x;
  }
  bool together(int x, int y) { return find(x) == find(y); }
} ds;
struct point {
  int x, y;
} p[155];
char str[155];
double d[155][155], maxd[155], ad[155];
double dist(double x1, double y1, double x2, double y2) {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
int main() {
  int n;
  scanf("%d", &n);
  ds.init(n);
  for (int i = 1; i <= n; i++) scanf("%d%d", &p[i].x, &p[i].y);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
      int c;
      scanf("%1d", &c);
      if (i == j)
        d[i][j] = 0;
      else if (c == 1) {
        d[i][j] = dist(p[i].x, p[i].y, p[j].x, p[j].y);
        ds.merge(i, j);
      } else
        d[i][j] = 1 << 30;
    }
  for (int k = 1; k <= n; k++)
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++)
      if (ds.together(i, j)) maxd[i] = max(maxd[i], d[i][j]);
    ad[ds.find(i)] = max(ad[ds.find(i)], maxd[i]);
  }
  double ans = 1 << 30;
  for (int i = 1; i <= n; i++)
    for (int j = i + 1; j <= n; j++)
      if (!ds.together(i, j))
        ans = min(ans,
                  max(maxd[i] + maxd[j] + dist(p[i].x, p[i].y, p[j].x, p[j].y),
                      max(ad[ds.find(i)], ad[ds.find(j)])));
  printf("%.6lf\n", ans);
  return 0;
}
```

---

## 作者：Imakf (赞：39)

# 题面分析

牧区就是一个点，牧场是多个（或一个）点构成的联通块，每个牧区的坐标将以$(x,y)$坐标的方式给出，两点之间的连通性将以对称的$01$矩阵给出，所以可以理解为无向边。

现在请将两个不连通的牧区相连，形成一个大牧场，使得这个大牧场的直径最小，一个牧场的直径就是牧场中**最远的两个牧区**的距离

# 算法分析

最短路好题，细节挺多的，因为$N\leq 150$很小，所以说各位都能想到要跑Floyd

跑完Floyd之后我们怎么做呢

我们容易想到枚举出每一个点能到的最远的点的距离，存到$Far[i]$里

然后暴力枚举不联通的两点$i,j$，求出答案$Far[i]+Far[j]+Distance(i,j)$

**然而这是错的**，可以被下面这个卡掉

```cpp
    @@@
    @1@
    @@@
     |   @@@
     |   @4@
 100 |   @@@
     |  
     |  
    @@@          @@@
    @2@----------@3@
    @@@   100    @@@
```

已知$4$到$2$距离$w$显然小于$100$

如果我们这个时候连$2,4$这样按照公式我们会得到错误答案

$Far[i]+Far[j]+Distance(i,j)=100+0+w<200$

显然连$2,4$的直径应该是$1->2->3=200$

我们少考虑了一点：新的大牧场的直径不一定比原来的两个牧场大

所以我们首先统计每个连通块的直径$Blockd[i]$，对于寻找连通块，直接dfs就行了

所以对于真正的答案应该是$max\{Far[i]+Far[j]+Distance(i,j) ,Blockd[i],Blockd[j]\}$，其中$i,j$不在同一连通块

# 善意的提醒

- 某些变量、函数记得用double型
- 极小值、极大值的设置
- Floyd中间转移点的循环必须放在最外层
- 对于读取一位数，用scanf("%1d" ,&x)就行了

# 代码

```cpp
#include<cstdio>
#include<cstdlib>
#include<cstdarg>
#include<iostream>
#include<cmath>

#define rg register
#define il inline
#define MX (150 + 5)
#define INF (123456789)

double min(double x ,double y){return x < y ? x : y;}
double max(double x ,double y){return x > y ? x : y;}
//记得double

int n;

struct farm{
	int x ,y;
	double distance(const farm &b){
		return sqrt((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y));
	}
}p[MX];

double dis[MX][MX] ,farthest[MX];
//dis是最短路
//farthest是上文的far，即每一个点能到的最远的点的距离
void Floyd(){
	for(rg int k = 1 ; k <= n ; ++k){
		for(rg int i = 1 ; i <= n ; ++i){
			for(rg int j = 1 ; j <= n ; ++j){
				dis[i][j] = min(dis[i][j] ,dis[i][k] + dis[k][j]);
			}
		}
	}
}

int linkcnt;	//连通块的个数
double Blockmax[MX];	//某个连通块中的farthest最大值
int refer[MX];	//表示某个点所在的连通块编号
void dfs(int x){
	if(refer[x])	return;
	refer[x] = linkcnt;
	for(rg int i = 1 ; i <= n ; ++i)
		if(dis[x][i] < INF)	dfs(i);
        //dis < INF即代表有边
}
int main(){
	scanf("%d" ,&n);
	for(rg int i = 1 ; i <= n ; ++i){
		scanf("%d%d" ,&p[i].x ,&p[i].y);
	}
	for(rg int i = 1 ,op ; i <= n ; ++i){
		for(rg int j = 1 ; j <= n ; ++j){
			dis[i][j] = INF;	//记得设初始值INF
			scanf("%1d" ,&op);
			if(op){
				dis[i][j] = p[i].distance(p[j]);
			}
			if(i == j)	dis[i][j] = 0;//自己到自己dis是0
		}
	}
	Floyd();
	for(rg int i = 1 ; i <= n ; ++i)	//寻找连通块
		if(!refer[i]){++linkcnt;dfs(i);}
	for(rg int i = 1 ; i <= n ; ++i){	//求出farthest
		for(rg int j = 1 ; j <= n ; ++j){
			if(dis[i][j] < INF){	//dis < INF即代表有边
				farthest[i] = max(farthest[i] ,dis[i][j]);
			}
		}
	}
	for(rg int i = 1; i <= linkcnt ; ++i){	//对于每一个连通块求出直径
		double kuaimax = -INF;	//记得设置-INF
		for(rg int j = 1 ; j <= n ; ++j){
			if(refer[j] == i)	kuaimax = max(kuaimax ,farthest[j]);
		}
		Blockmax[i] = kuaimax;
	}
	double ans = INF;	//记得设置INF
	for(rg int i = 1 ; i <= n ; ++i){
		for(rg int j = 1 ; j <= n ; ++j){
			if(refer[i] != refer[j]){	//两者不能在同一连通块
				ans = min(ans ,max(p[i].distance(p[j]) + farthest[i] + farthest[j] ,max(Blockmax[refer[i]] ,Blockmax[refer[j]])));
			}
		}
	}
	printf("%.6lf \n" ,ans);
	return 0;
}
```

---

## 作者：TsReaper (赞：16)

用Floyd求出每个点到其它点的距离（这里说的都是最短距离）。对于每个点x，找出可以到达它的，并且与它距离最远的点的距离，记为maxdis(x)。这样，我们枚举添加路径的两个端点a,b，那么答案就是min(maxdis(a)+maxdis(b)+dis(a,b))（dis(a,b)表示a,b间的距离）。注意，原来两个农场的直径也要参与答案的考虑。


---

## 作者：bztMinamoto (赞：12)

每一个牧场都是一个连通块，于是我们要求将两个图连通之后的最小直径是多少

当两牧场中的i，j连上一条边后，新牧场的直径为max（牧场1直径，牧场2直径，ij距离+牧场1中离i最远的距离+牧场2中离j最远的距离）

为了在规定时间内解决这道问题，我们应该先将一些数据预处理出来。先用floyd求出任意两点间距离，再通过枚举求出一个牧场中离每个点最长的距离，最后用dfs划分连通块，并记录每一个连通块的直径

记得INF开大一点

具体细节看注解，上代码
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cmath>
#include<string>
#define a(a,b,c) for(int a=b;a<=c;a++)
#define b(a,b,c) for(int a=b;a>=c;a--)
using namespace std;
typedef long long LL;
const int N=155,M=N*N,INF=1e10;
double d[N][N],f[N],t[N];
int a[N],ver[M],Next[M],head[N],x[N],y[N];
int n,tot,s;
double ans=INF;
void add(int x,int y)
{
    ver[++tot]=y,Next[tot]=head[x],head[x]=tot;
    return;
}
double num(int i,int j)
{
    return sqrt(((LL)x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
}
void dfs(int x)
{
    a[x]=s;
    t[s]=max(t[s],f[x]);
    //求出每一个连通块的直径
    for(int i=head[x];i;i=Next[i])
    if(!a[ver[i]])
    dfs(ver[i]);
    return;
}
bool cmp(double x,double y)
{
    return x>y;
}
double maxn(double a,double b,double c)
{
    double x[3];
    x[0]=a,x[1]=b,x[2]=c;
    sort(x,x+3,cmp);
    return x[0];
}
int main()
{
    scanf("%d",&n);
    a(i,1,n)
    a(j,1,n)
    d[i][j]=INF;
    a(i,1,n) d[i][i]=0;
    a(i,1,n)
    scanf("%d%d",&x[i],&y[i]);
    a(i,1,n)
    {
        string s;
        cin>>s;
        a(j,1,s.size())
        if(s[j-1]=='1') d[i][j]=num(i,j),add(i,j);
    }
    a(k,1,n)
    a(i,1,n)
    a(j,1,n)
    d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
    //用floyd算法求出任意两点间距离
    a(i,1,n)
    a(j,1,n)
    if(d[i][j]!=INF) f[i]=max(d[i][j],f[i]);
    //求出牧场中离每一个点最远的点的距离
    a(i,1,n)
    if(!a[i])
    s++,dfs(i);
    //划分连通块
    a(i,1,n)
    a(j,1,n)
    if(a[i]!=a[j])
    ans=min(ans,maxn(t[a[i]],t[a[j]],f[i]+f[j]+num(i,j)));
    printf("%.6lf",ans);
    //ps：不知道为什么，用printf四舍五入能A，不四舍五入反而会错……
    return 0;
}
```

---

## 作者：tribool4_in (赞：10)

惨遭数据 Hack 的菜鸡来写篇题解 /kk

题意就是有一个不联通的图，你需要在两个连通块之间连一条边，使得这个新形成的连通块直径尽可能小。

考虑到连一条边 $(i,j)$ 后新的连通块的直径可能有哪几种情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/76m4kul4.png)

1. 从 $i$ 点出发最远距离 + 从 $j$ 点出发最远距离 + $(i,j)$ 边的长度；
2. $i$ 所在连通块的直径；
3. $j$ 所在连通块的直径。

因此，由于数据较小，只需跑一遍 Floyd 并处理出从每一个点出发的最远距离，从而利用并查集计算出每一个联通块的直径；然后暴力枚举边 $(i,j)$（需保证不在同一连通块中）计算新的直径即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200;
inline int read() {
	int s = 0; char c = getchar();
	while (!isdigit(c)) c = getchar();
	while (isdigit(c)) s = s * 10 + c - '0', c = getchar();
	return s;
}
class dsu {
    private:
        int n;
        int *fa;
        void init(int n) {
            fa = new int[n + 10];
            for (int i = 0; i <= n; i++) fa[i] = i;
        }
    public:
        dsu(int n):n(n) { init(n); }
        int find(int x) {
            if (fa[x] == x) return x;
            return fa[x] = find(fa[x]);
        }
        bool together(int x, int y) { return find(x) == find(y); }
        void merge(int x, int y) {
            x = find(x), y = find(y);
            if (x != y) fa[x] = y;
        }
};
int n, x[N], y[N];
char s[N];
double f[N][N], d[N], dd[N];
double dis(int i, int j) {
	return sqrt((x[j] - x[i]) * (x[j] - x[i]) + (y[j] - y[i]) * (y[j] - y[i]));
}
int main() {
	n = read();
    dsu ds(n);
	for (int i = 1; i <= n; i++) {
		x[i] = read(), y[i] = read();
	}
	for (int i = 1; i <= n; i++) {
		scanf("%s", s + 1);
		for (int j = 1; j <= n; j++) {
			if (s[j] == '1') {
				f[i][j] = dis(i, j);
                ds.merge(i, j);
			} else if (i != j) {
				f[i][j] = 1e10;
			}
		}
	}
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
			}
		}
	}
	double d1 = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (ds.together(i, j)) {
				d[i] = max(d[i], f[i][j]);
				d1 = max(d1, d[i]); // 旧做法的痕迹（
			}
		}
        dd[ds.find(i)] = max(dd[ds.find(i)], d[i]);
	}
	double d2 = 1e10;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (!ds.together(i, j)) {
				d2 = min(d2,
                        max(d[i] + d[j] + dis(i, j), // 情况 1
                        max(dd[ds.find(i)], dd[ds.find(j)]))); // 情况 2 & 3
			}
		}
	}
	printf("%.6f\n", d2);
	return 0;
}
```

-----------

关于旧做法，这种做法只考虑了情况 1，然而无法通过 \#7 测试点。因此将得到的直径与原直径取最大值，然后由于数据问题通过。显然这两者理论上不可比较，因为新连通块的直径可能与原来的最大直径无关。在代码中可以找到旧做法的痕迹（）。

---

## 作者：luckydrawbox (赞：7)

## 题意

直径：一个牧场（连通块）中任意两点最短路的最大值。

给你一张无向带权图，图中有一些连通块，试连接图中两个不同的连通块中的一点，是新的连通块直径最小。

## 分析

- 我们需要把图存下来，于是用 $w_{i,j}=\sqrt{(x_i-x_j)^2+(y_i-y_j)^2}$ 代表边权。

- 我们需要找出图中的连通块，于是 $\text{dfs}$ 对每个块染色，把每个连通块的点放进对应的 $\text{vector}\ c2_{col}$ 里。

- 我们需要知道任意两点之间的最短路，于是跑了 ~~floyd~~ $n$ 次 $\text{Dijkstra}$ 求最短路 $d_{i,j}$。

- 我们需要知道每个连通块的直径 $cz_{col}$，于是我们需要知道每个点到块中其他点的最短路的最大值 $mxd_{c2_{col,i}}$，就可以知道 $cz_{col}=\max\{mxd_{c2_{col,i}}\}$。

- 我们需要找出答案，于是暴力枚举两个点 $i,j$，如果 $i,j$ 不在同一个连通块内，那么连接后的新直径可能在两个原来的连通块内，也可能是连接之后形成的，也就是 $\max(cz_{col_i},cz_{col_j},mxd_i+w_{i,j}+mxd_j)$。答案就是所有情况的最小值。

- 我们需要知道这样写会不会错，还没等你算出时间复杂度 $O(n^2\log n)$，你的程序已经在 $\text{100ms}$ 内 [$\text{AC}$](https://www.luogu.com.cn/record/56414131) 了。

## 代码

```cpp
#include<bits/stdc++.h>
#define qw first
#define er second
using namespace std;
const int N=200;
int n,c[N];//c[i]是i所在的连通块 
double x[N],y[N],w[N][N],d[N][N],mxd[N],cz[N],mx=1e9;
bool a[N][N],v[N];
vector<int>c2[N];
priority_queue<pair<double,int> >q;
pair<double,int>e;
void dfs(int x,int col){
	if(v[x]) return;
	v[x]=1;c[x]=col;
	c2[col].push_back(x);
	for(int i=1;i<=n;i++)
		if(a[x][i])
			dfs(i,col);
}
void Dijkstra(int s){
	memset(v,0,sizeof(v));
	d[s][s]=e.qw=0;e.er=s;
	q.push(e);
	while(q.size()){
		int x=q.top().er;
		q.pop();
		if(v[x])
			continue;
		v[x]=1;
		for(int i=1;i<=n;i++){
			if(!a[x][i])
				continue;
			if(d[s][i]>d[s][x]+w[x][i]){
				d[s][i]=d[s][x]+w[x][i];
				e.qw=-d[s][i];e.er=i;
				q.push(e);
			}
		}
	}
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=n;j++)
    		d[i][j]=1e7;
    for(int i=1;i<=n;i++)
    	cin>>x[i]>>y[i];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%1d",&a[i][j]);
			w[i][j]=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
		}
	}
	for(int i=1;i<=n;i++)
		Dijkstra(i);
	memset(v,0,sizeof(v));
	for(int i=1,col=1;i<=n;i++){
		if(v[i]) continue;
		dfs(i,col);
		for(int j=0;j<c2[col].size();j++){
			for(int k=0;k<c2[col].size();k++){
				if(j==k||d[c2[col][j]][c2[col][k]]==1e7) continue;
				mxd[c2[col][j]]=max(mxd[c2[col][j]],d[c2[col][j]][c2[col][k]]);
			}
			cz[col]=max(cz[col],mxd[c2[col][j]]);
		}
		col++;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(c[i]==c[j]) continue;
			mx=min(mx,max(cz[c[i]],max(cz[c[j]],mxd[i]+w[i][j]+mxd[j])));
		}
	printf("%.6lf",mx);
	return 0;
}
```


---

