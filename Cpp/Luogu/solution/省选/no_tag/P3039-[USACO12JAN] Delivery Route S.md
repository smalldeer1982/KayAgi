# [USACO12JAN] Delivery Route S

## 题目描述

FJ 有 $N\ (1 \le N \le 100)$ 个农场，每个农场具有独立的整数坐标 $(x_i, y_i)\ (1 \le x_i,y_i \le 10^6)$。他需要一个物资配送路线，从第 $1$ 个农场出发，依次经过农场 $1$，农场 $2$，农场 $3$……，最后从农场 $N$ 回到农场 $1$。

FJ 每次只能朝东南西北四个方向行走，每行走一个单位长度需要 $1$ 分钟，除了农场 $1$，其他农场能且仅能到达一次。

请计算 FJ 的最小时间花费。

## 说明/提示

样例中的最优方案是 $1 \to 2 \to 3 \to 4 \to 1$，需要 $12$ 分钟。

## 样例 #1

### 输入

```
4 
2 2 
2 4 
2 1 
1 3 
```

### 输出

```
12 
```

# 题解

## 作者：泥土笨笨 (赞：17)

Farmer John有n个农场，编号为1到n，每个农场在二维平面上，有一个坐标。现在他想按照编号的顺序一次访问每个农场，从1号到2号，再到3号……最后从n号回到1号。每次只能从当前位置走到当前位置的上下左右四个点，每走一步需要花1分钟，每个顶点只能访问一次，问走完一圈回到1点的最短时间是多少。

既然访问顺序是确定的，那么我们可以用单源最短路径算法，比如Dijkstra算法，分别计算从1到2的最短路径，2到3的最短路径……然后全部相加就是答案了。那么问题就转化成了如何求两点间的最短路径，比如我们先考虑按照题目中的样例，从2号到3号点的最短路径是多少。

把样例画成图看一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/nwurpmxt.png)

2号点到3号点，直接连下来是最快的，只要3分钟，就是红色的线。但是现在我们要从2号点直接走到3号点，中间不能经过无关的农场1，所以只能走绿色的线，所以从2到3的最短路径是5。

那么如何实现这种不经过农场的最短路径呢？这里有一个小技巧，加虚点。我们在每个点的上下左右，再加4个点。如下图，把虚点都加上：

![](https://cdn.luogu.com.cn/upload/image_hosting/6lwi1xk1.png)

好，那么我们现在有14个点。把每个农场和周围的四个点之间连一条长度为1的边，然后在虚点之间两两连边。比如2到9连一条边，9到6连一条边，6到12连一条边，12到3连一条边。我们要求走最短路径的时候，只能沿着我们连的边走，不能随便乱走。并且走的时候不能碰到别的农场。这样红色的路径2-5-1-3因为碰到了1号而不能走，而2-9-6-12-3这条路径是可以的。

我们这样连边以后跑最短路，一定是比较优秀的，因为如果路线经过了不存在的点，就会”绕远“。比如9号点和12号点的右边没有点了。如果你从9号点向右走，然后下来，然后到12号点的右边，再走回到12号点，你会发现这样绕路了，这样的路是不划算的。

那么是否任意两个虚点之间都连边呢？也不是。我们定义一个概念，”最多拐弯一次的路径“，就是两点之间的路径，要么是直线，要么最多只能有一个直角拐弯，不能有两个或者两个以上。比如图中2号点左边的10号点，和3号点下面的11号点，这两个点之间，就找不到一条路径可以最多拐一个直角弯就能相连。这样10号点和11号点我们就不连边，因为如果要拐超过一个弯，这个路线一定要绕路。事实上，10号到11号点，可以走10-14-7-12-11这条路径，这条路径是不绕路的，所以并不需要在他们之间多连一条绕路的边。

那么只要虚点之间的边都不绕路，那么虚点之间的路径的长度就是他们之间的曼哈顿距离，即两点之间横坐标的差的绝对值，加上纵坐标的差的绝对值。

下一个难点是如何判断两个点之间可以有一条”最多拐弯一次的路径“，而且要求这个路径不能经过农场呢？如果这两个点本来就在同一行或者同一列，问题就退化成了判断农场点在不在线段上，这个好解决。如果两个点不在同一行同一列，那么因为他们最多拐一次弯，所以只有两条路线可以走，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/w8ieduca.png)

从(x1,y1)点走到(x2，y2)点，要么走黑色路径，要么走红色路径。每条路径可以拆成两个线段，于是又退化为点在线段上的判断。

基本思路讲完了，其他就是代码了：

```cpp
#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int MAXN = 505;

struct Point {
    int x, y;

    Point(int x, int y) : x(x), y(y) {}

    bool operator<(const Point &a) const {
        if (x != a.x) return x < a.x;
        return y < a.y;
    }
};

struct Edge {
    int v, w;

    Edge(int v, int w) : v(v), w(w) {}
};

struct Node {
    int u, d;

    Node(int u, int d) : u(u), d(d) {}

    bool operator<(const Node &a) const {
        return d > a.d;
    }
};

int n, x[MAXN], y[MAXN], nn, ans, dis[MAXN], vis[MAXN];//nn表示点的总个数
map<Point, int> dict;//定义一个集合，用来判断某个点是否重复出现过
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
vector<Edge> adj[MAXN];

//判断p点在不在线段(x1,y1),(x2,y2)上
bool inSegment(int p, int x1, int y1, int x2, int y2) {
    if (x1 == x2 && x[p] == x1) {
        if (y1 > y2) swap(y1, y2);
        if (y[p] >= y1 && y[p] <= y2) return true;
    }
    if (y1 == y2 && y[p] == y1) {
        if (x1 > x2) swap(x1, x2);
        if (x1 <= x[p] && x[p] <= x2) return true;
    }
    return false;
}

//判断一条线段是否穿过任何一个农场
bool valid(int x1, int y1, int x2, int y2) {
    for (int i = 1; i <= n; ++i) {
        if (inSegment(i, x1, y1, x2, y2)) return false;
    }
    return true;
}

//判断p1和p2点能否连通，连通的条件是有至少一条最多一个直角的路径，不经过其他农场
bool connect(int p1, int p2) {
    if (x[p1] == x[p2] || y[p1] == y[p2]) {
        return valid(x[p1], y[p1], x[p2], y[p2]);
    }
    if (valid(x[p1], y[p1], x[p2], y[p1]) && valid(x[p2], y[p1], x[p2], y[p2])) return true;
    return valid(x[p1], y[p1], x[p1], y[p2]) && valid(x[p1], y[p2], x[p2], y[p2]);
}

int manhattan(int p, int q) {
    return abs(x[p] - x[q]) + abs(y[p] - y[q]);
}

void dijkstra(int start, int target) {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[start] = 0;
    priority_queue<Node> q;
    q.push(Node(start, 0));
    while (!q.empty()) {
        int u = q.top().u;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].v;
            if (v <= n && v != target) continue;
            int w = adj[u][i].w;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                q.push(Node(v, dis[v]));
            }
        }
    }
}

int main() {
    //先输入每个点的数据
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> x[i] >> y[i];
        dict[Point(x[i], y[i])] = i;
    }
    nn = n;
    //把每个点上下左右四个点也加进来，重复的就不要了
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 4; ++j) {
            int xx = x[i] + dx[j];
            int yy = y[i] + dy[j];
            Point p = Point(xx, yy);
            if (dict.count(p) == 0) {
                ++nn;
                x[nn] = xx;
                y[nn] = yy;
                dict[p] = nn;
            }
            int id = dict[p];
            adj[i].push_back(Edge(id, 1));
            adj[id].push_back(Edge(i, 1));
        }
    }
    //建边
    for (int i = n + 1; i <= nn; ++i) {
        for (int j = i + 1; j <= nn; ++j) {
            if (connect(i, j)) {
                int d = manhattan(i, j);
                adj[i].push_back(Edge(j, d));
                adj[j].push_back(Edge(i, d));
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        int target = i + 1;
        if (i == n) target = 1;
        dijkstra(i, target);
        if (dis[target] == 0x3f3f3f3f) {
            cout << -1 << endl;
            return 0;
        }
        ans += dis[target];
    }
    cout << ans << endl;
    return 0;
}
```


---

## 作者：nihanchu (赞：5)

usaco英文题解链接：<http://www.usaco.org/current/data/sol\_delivery.html>

表示看了题解和程序好久才看懂。。。。

思路大概是这样的，我们把原来的一个点拆分成五个点，分别在它的上下左右，也建立一个点，然后重新构图，在5n个点中一一判断是否能到达，如何判断呢？我们看看两个点间能不能构成一条直角路径，即这条路径只能转一次弯，如果可以就把这两个点连接起来，然后用图做dijkstra，得出我们要求的两点间的能到达的最短距离。

为什么可以这么做 ？？

 ![](https://cdn.luogu.com.cn/upload/pic/4528.png) 

（图中黑圈代表原本的点，红点代表扩展后的点，绿线代表原本没有红点前走的路线，黄线代表扩展点后的路线）

如图所示我们发现扩展红点后两点间之间连接的路径如果存在要么是直线，要么只存在一个直角，扩展点可以帮助我们减少路径的弯弯曲曲程度，更好做。且图画多了可以发现如果两个点包括他们的扩展点间都不存在直角路径，那么这两个点是不联通的。

所以我们就把原问题变成了重构图后，求一条由多条两点间（这两点互相可以到达，即直角路径上不存在原问题中的点）的直角路径构成的最短路径；

我知道讲的很模糊，所以具体的话还是程序里面写吧




```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
struct ding{
    int x,y;
}p[600];
struct bian{
    int to,next;
}edge[300000];
ding f2[600],f[600];
int n,h[5]={0,-1,1,0,0},l[5]={0,0,0,1,-1};
int indx[50000];
int num=0,cnt=0,head[10000],dis[10000];
bool vis[10000];
bool check3(int x1,int y1,int x2,int y2,int x3,int y3)
{
//为了方便我们就把直角路径拆成两条来看
  if (x2==x3) return ((x1==x2)&&(y1>min(y2,y3))&&(y1<max(y2,y3)));
  else return ((y1==y2)&&(x1>min(x2,x3))&&(x1<max(x2,x3)));
}
bool check2(ding tot,int a,int b)
{
  bool fg=true;
  for (int i=1;i<=n;i++) if ((tot.x==f[i].x)&&(tot.y==f[i].y)) {fg=false;break;}//我们要保证直角上没有点
  fg=fg||(f2[a].x==f2[b].x)||(f2[a].y==f2[b].y);
//当然如果两个点原本就在同一列或同一行的话，那就不存在直角了。。。 
  for (int i=1;i<=n;i++)
  if (check3(f[i].x,f[i].y,f2[a].x,f2[a].y,tot.x,tot.y)||check3(f[i].x,f[i].y,f2[b].x,f2[b].y,tot.x,tot.y))
//检查枚举的这条直角路径上有没有点，如果有，那么这条路径禁止通行
  {fg=false; break;} 
  if (fg) return true;
  return false;
}
bool check1(int a,int b)
{
//一般情况下两点间的的直角路径有两条，所以我们也分类讨论
  ding tot; tot.x=f2[a].x; tot.y=f2[b].y; 
  if (check2(tot,a,b)) return true;
   tot.x=f2[b].x; tot.y=f2[a].y; 
  if (check2(tot,a,b)) return true;
  return false;
}
void add(int u,int v)
{
  edge[++num].to=v;
  edge[num].next=head[u];
  head[u]=num;
}
int calc(int a,int b){return (abs(f2[a].x-f2[b].x)+abs(f2[a].y-f2[b].y));} 
//计算两点间的曼哈顿距离
int dijkstra(int a,int b)
{
  for (int i=1;i<=cnt;i++) {dis[i]=2100000000; vis[i]=false;}
//赋初值
  for (int i=1;i<=n;i++) if ((indx[i]!=b)&&(indx[i]!=a)) vis[indx[i]]=true;
//除了起点与终点外，其他原本就存在的点是不能用于更新最短路径的，因为它们只能被经过一次
  dis[a]=0;
  for (int i=1;i<=cnt;i++)
  {
      int now=1;
      for (int j=1;j<=cnt;j++) if (((dis[j]<dis[now])||(vis[now]))&&(!vis[j])) now=j;
//如果说已经没有没被更新过的点，或者点与点之间已经没路了，返回-1；
      if ((vis[now])||(dis[now]==2100000000)) return -1;
      if (now==b) return dis[b];
//如果终点成了目前离起点最近的未更新过其他点的点，那么说明剩下的点已经没办法再更新这条最短路了，直接返回答案
      vis[now]=true;
      for (int j=head[now];j;j=edge[j].next)
      {
        int y1=edge[j].to;
      if (!vis[y1]) dis[y1]=min(dis[y1],dis[now]+calc(now,y1));
    }
  }
  return -1;
}
int main()
{
  scanf("%d",&n);
  for (int i=1;i<=n;i++) 
  {
    scanf("%d%d",&p[i].x,&p[i].y);
    ding tot; tot.x=p[i].x; tot.y=p[i].y;
    f[i]=tot;
//定义一个结构体来储存只是为了方便。。。p[i]数组是没用的。。。
  }
  for (int i=1;i<=n;i++)
  {
    f2[++cnt]=f[i]; indx[i]=cnt;//储存扩展后的点，并记录原点在数组中的位置
    for (int j=1;j<=4;j++)
    {
     bool fg=true; 
     ding tot;tot.x=p[i].x+h[j]; tot.y=p[i].y+l[j];
//枚举扩展点
     for (int k=1;k<=n;k++) if ((tot.x==f[k].x)&&(tot.y==f[k].y)) {fg=false;break;}
//保证原本这个位置上是没有点的
     if (fg) f2[++cnt]=tot;
    }
  } 
  for (int i=1;i<=cnt;i++)
   for (int j=i+1;j<=cnt;j++)
   if (check1(i,j)) {add(i,j);add(j,i);}
//检查这两点间是否能到达，如果可以，那么就用链式前向星记录下来（好像可以不用，但是我当时以为。。）
   int ans=0;
  for (int i=1;i<=n;i++)
  {
      int sum=0;
      if (i!=n) sum=dijkstra(indx[i],indx[i+1]);
      else sum=dijkstra(indx[i],indx[1]); 
//计算它与它要到达的点间的最短距离
      if (sum==-1) {cout<<"-1"<<endl; return 0;}
//如果返回-1，说明两点间无法到达
      else ans+=sum;
//否则记录
  }
  printf("%d\n",ans);
  return 0;
}
```

---

## 作者：yr409892525 (赞：3)

## 题解：P3039 [USACO12JAN] Delivery Route S
如果没有每个点只能走一次的条件，则答案为曼哈顿距离。          

但是每个点只能走一次，也就是说，两个点的最短路上有可能障碍。             

所以就要绕道而行，最优情况就是贴着边走。            

所以可以对每个点的四周建立虚点。          

当两个点之间不能通过一次转折到达，则可以通过虚点连接。              

两个点是否可以通过一次转折到达，说明路径为两条线段，判断中间是否有障碍即可。

加上数据 $n \le 100$，让我们想到了全源最短路，所以不妨跑 Floyd。                
```cpp
#include <bits/stdc++.h>

using namespace std;
using Pii = pair<int,int>;

const int kMaxN = 501, kD[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int _n, n, f[kMaxN][kMaxN], ans;
Pii a[kMaxN];
set<Pii> s;

bool C(int i, int j) {
  bool b[2] = {0, 0};
  for (int k = 0; k < _n; k++) {
    if (k != i && k != j) {
      b[0] |= a[k].first == a[i].first && min(a[i].second, a[j].second) <= a[k].second && a[k].second <= max(a[i].second, a[j].second);
      b[1] |= a[k].first == a[j].first && min(a[i].second, a[j].second) <= a[k].second && a[k].second <= max(a[i].second, a[j].second);
      b[0] |= a[k].second == a[j].second && min(a[i].first, a[j].first) <= a[k].first && a[k].first <= max(a[i].first, a[j].first);
      b[1] |= a[k].second == a[i].second && min(a[i].first, a[j].first) <= a[k].first && a[k].first <= max(a[i].first, a[j].first);
    }
  }
  return !b[0] || !b[1];
}

int main() {
  cin.tie(0) -> sync_with_stdio(false);
  cin >> _n;
  for (int i = 0; i < _n; i++) {
    cin >> a[i].first >> a[i].second;
    s.insert(a[i]);
  }
  n = _n;
  for (int i = 0; i < _n; i++) {
    for (int j = 0; j < 4; j++) {
      Pii k = {a[i].first + kD[j][0], a[i].second + kD[j][1]};
      if (s.count(k) == 0) {
        s.insert(k);
        a[n++] = k;
      } 
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      f[i][j] = C(i, j) ? abs(a[i].first - a[j].first) + abs(a[i].second - a[j].second) : 1e9;
    }
  }
  for (int k = _n; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
      }
    }
  }
  for (int i = 0; i < _n; i++) {
    ans += f[i][(i + 1) % _n];
    if (ans > 1e9) {
      cout << -1;
      return 0;
    }
  }
  cout << ans;
  return 0;
}
```

---

## 作者：哈士奇憨憨 (赞：3)

## 题意
在平面上有 $N$ 个点，每次只能朝四个方向移动一格，求从 $1$ 号点出发按顺序经过每个点刚好一次，最后回到 $1$ 号点的最短距离。
## 思路
按照规则，从平面上一个点移动到另一个点的最短距离就是它们之间的曼哈顿距离。如果两个点在一条直线上，则最短路线只有一种走法；否则最短路线可以有多种走法，其中有两种走法只需要拐弯一次。

由于题目中要求每个点必须按顺序经过刚好一次，所以在路径中相邻两个点之间移动时，不能经过其他点，由此可能导致两点之间的最短距离变长。由于坐标的范围较大，无法用搜索的方式求出两点之间的最短距离，只能考虑对最短路径进行构造。

考虑最简单的情况，每次走到下一个点时最多拐弯一次，如果此时会经过其他点，则可以对路径进行微调，使得刚好从这个点旁边经过，并仍然保持是最短路径。因此，我们可以将每个点的四个位置相邻的格子当做衔接点，这样在最短路径中，可以保证每次最多拐弯一次就能到达下一个点。

我们可以暴力检查每一对点之间是否可以最多拐弯⼀次到达，然后求出通过衔接点，路径中每对相邻点之间的最短路径距离。考虑到点数很小，可以采用 Floyd 算法求解。

此外，原先的点中可能有的点位置本身就相邻，所以添加衔接点时需要注意，不能将已有的点添加为衔接点，可以采用 STL 中的 `set` 来判重。
## CODE
```cpp
#include <bits/stdc++.h>
using namespace std;
using Pii = pair<int, int>;
const int kMaxN = 501, kInf = 1e9, kD[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
set<Pii> s;
Pii p[kMaxN];
int f[kMaxN][kMaxN], n, m, ans;
bool C(int i, int j) {
  bool b0 = 0, b1 = 0;            // 初始化两条路线
  for (int k = 1; k <= n; k++) {  // 枚举中间点
    if (k != i && k != j) {       // 非起点或终点
      b0 |= p[k].first == p[i].first && p[k].second >= min(p[i].second, p[j].second) && p[k].second <= max(p[i].second, p[j].second);
      b0 |= p[k].second == p[j].second && p[k].first >= min(p[i].first, p[j].first) && p[k].first <= max(p[i].first, p[j].first);
      b1 |= p[k].second == p[i].second && p[k].first >= min(p[i].first, p[j].first) && p[k].first <= max(p[i].first, p[j].first);
      b1 |= p[k].first == p[j].first && p[k].second >= min(p[i].second, p[j].second) && p[k].second <= max(p[i].second, p[j].second);
    }
  }
  return !(b0 && b1);
}
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> p[i].first >> p[i].second;
    s.insert(p[i]);  // 加入集合
  }
  m = n;
  for (int i = 1; i <= n; i++) {                                   // 枚举点
    for (int j = 0; j < 4; j++) {                                  // 枚举方向
      p[m + 1] = {p[i].first + kD[j][0], p[i].second + kD[j][1]};  // 计算邻点
      if (!s.count(p[m + 1])) {                                    // 位置可用
        s.insert(p[++m]);                                          // 加入集合
      }
    }
  }
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= m; j++) {                                                               // 枚举点对
      f[i][j] = C(i, j) ? abs(p[i].first - p[j].first) + abs(p[i].second - p[j].second) : kInf;  // 计算拐一次弯是否可达
    }
  }
  for (int k = n + 1; k <= m; k++) {  // 枚举中间点
    for (int i = 1; i <= m; i++) {
      for (int j = 1; j <= m; j++) {                // 枚举点对
        f[i][j] = min(f[i][j], f[i][k] + f[k][j]);  // 更新距离
      }
    }
  }
  ans = f[n][1];                 // 初始化答案
  for (int i = 1; i < n; i++) {  // 累加答案
    ans = min(kInf, ans + f[i][i + 1]);
  }
  cout << (ans == kInf ? -1 : ans);
  return 0;
}
```

---

## 作者：a_small_penguin (赞：0)

### 思路

这道题如果忽略顺序，就只是一道黄，但是这题要求必须按照 $1 \to 2,2\to3,3\to4,\cdots,n - 1\to n,n \to 1$。那该如何操作呢？

此题可以和[P3632 \[APIO2011\] 寻路](https://www.luogu.com.cn/problem/P3632)一样运用类似的思
路，建图跑最短路。

先观察样例：![](https://cdn.luogu.com.cn/upload/image_hosting/kjlqumnz.png)

由于在 $i \to j$ 的过程中不能经过其他任何点，也就是说，最多只能在其他点的周围运动，所以可以想到，在每个点的上下左右四个方向各建一个虚点，如果虚点和原来的点重合就不建。

也就是这样的：![](https://cdn.luogu.com.cn/upload/image_hosting/jqojztgr.png)

再对虚点之间两两连边，但是要注意，如果连边必须是只有一个改变方向或没有改变方向，否则路径一定可以拆成数段路径拼接在一起。

建完图后就是这样的：![](https://cdn.luogu.com.cn/upload/image_hosting/2m3bshny.png)

再从每个虚点为起点跑最短路，或者直接跑一个 floyd，再枚举起点和终点相邻的虚点，再求出虚点之间的最短路径 $+2$，就是两点之间的最短路径了。当然，还要特判一下，如果两个点相邻就不用枚举，最短路就是 $1$。

时间复杂度为：$O(m \log n + n^2 \log m + n + n \log m + nm \log n)$。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
constexpr int fx[4] = {1, 0, -1, 0};
constexpr int fy[4] = {0, -1, 0, 1};


int n;
int x[109], y[109];
int cnt;
vector<int> g[509];
int a[509], b[509];
int d[509][509];
vector<pair<int, int> > e[509];
bitset<509> c[509];
map<pair<int, int>, int> p, q;
vector<int> l[2000009];
vector<int> r[2000009];

inline void input() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
        p[{x[i], y[i]}] = i;
        l[x[i]].push_back(y[i]);
        r[y[i]].push_back(x[i]);
    }
}

inline void addd() {
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 4; j++) {
            int cx = x[i] + fx[j];
            int cy = y[i] + fy[j];
            if(!p.count({cx, cy})) {
                if(!q.count({cx, cy})) {
                    q[{cx, cy}] = ++cnt;
                    a[cnt] = cx, b[cnt] = cy;
                    g[i].push_back(cnt);
                } else {
                    g[i].push_back(q[{cx, cy}]);
                }
            }
        }
    }
}

inline bool check(int _a, int _b, int _c, int _d) {
    if(p.count({_a, _b}) || p.count({_c, _d})) return 0;
    if(_a == _c) {
        if(!l[_a].size()) return 1;
        return upper_bound(l[_a].begin(), l[_a].end(), _b) == upper_bound(l[_a].begin(), l[_a].end(), _d);
    } else {
        if(!r[_b].size()) return 1;
        return upper_bound(r[_b].begin(), r[_b].end(), _a) == upper_bound(r[_b].begin(), r[_b].end(), _c);
    }
}

inline void add(int _a, int _b, int _u, int _c, int _d, int _v) {
    int cnt = abs(_b - _d) + abs(_a - _c);
    if(_a == _c || _b == _d) {
        if(check(_a, _b, _c, _d))e[_u].push_back({_v, cnt}), e[_v].push_back({_u, cnt});
        return;
    }
    if((check(_a, _b, _a, _d) && check(_a, _d, _c, _d)) || (check(_a, _b, _c, _b) && check(_c, _b, _c, _d))) e[_u].push_back({_v, cnt}), e[_v].push_back({_u, cnt});
}

inline void addedge() {
    for(int i = 1; i <= cnt; i++) {
        for(int j = i + 1; j <= cnt; j++) {
            add(a[i], b[i], i, a[j], b[j], j);
        }
    }
}

inline void dij(int s) {
    d[s][s] = 0;
    priority_queue<pair<int, int> > q;
    q.push({0, s});
    while(q.size()) {
        int u = q.top().second;
        q.pop();
        if(c[u][s]) continue;
        c[u][s] = 1;
        for(auto to: e[u]) {
            if(d[to.first][s] > d[u][s] + to.second) {
                d[to.first][s] = d[u][s] + to.second;
                q.push({-d[to.first][s], to.first});
            }
        }
    }
}

inline void zdl() {
    memset(d, 0x3f, sizeof(d));
    for(int i = 1; i <= cnt; i++) {
        dij(i);
    }
}

inline int num(int a, int b) {
    for(int i = 0; i < 4; i++) {
        int cx = x[a] + fx[i];
        int cy = y[a] + fy[i];
        if(cx == x[b] && cy == y[b]) return 1;
    }
    return 0;
}

inline int sum(int x, int y) {
    int z = num(x, y);
    if(z) return z;
    int minn = 0x3f3f3f3f3f3f3f3f;
    for(auto u: g[x]) {
        for(auto v:g[y]) {
            minn = min(minn, 2 + d[u][v]);
        }
    }
    if(minn == 0x3f3f3f3f3f3f3f3f) {
        cout << -1 << "\n";
        exit(0);
    }
    return minn;
} 

inline int ask() {
    int ans = sum(1, n);
    for(int i = 1; i < n; i++) {
        ans += sum(i, i + 1);
    }
    return ans;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    input();
    addd();
    for(int i = 0; i <= 1e6 + 1; i++) {
        if(l[i].size()) l[i].push_back(-1), l[i].push_back(1e6 + 9), sort(l[i].begin(), l[i].end());
        if(r[i].size()) r[i].push_back(-1), r[i].push_back(1e6 + 9), sort(r[i].begin(), r[i].end());
    }
    addedge();
    zdl();
    cout << ask();
    return 0;
}
```

---

## 作者：feizhu_QWQ (赞：0)

## 题意
一个二维平面上有 $n$ 个点，要求从点 $1$，出发，每次走到编号加一的点，到点 $n$ 时再走回点 $1$，的最短路径（曼哈顿距离），要求除了点 $1$ 不能重复经过其他点。  
## 思路
很明显这是哈密尔顿回路~~吗？~~，但找不到匹配的算法，我们就换个角度思考：  
![](https://cdn.luogu.com.cn/upload/image_hosting/mywv582z.png)  
学过小奥都知道，图中的绿色路径是可以通过平移变成红色路径的，也就是说；两条距离相等，所以为了方便，我们就直接处理红色路径。  
为了最短，我们要么直接走最短的曼哈顿距离，要么有点挡住了，我们就绕着他的边缘走。  
对于这个边缘就很好处理了，我们把每个点上下左右的点都拿出来，最多 $500$ 个，然后建边我们就可以判断有没有一个边缘点，使得我可以最多拐一次弯，先直走到这个边缘点，再拐弯直接到目标点，找到了，那么这两个点的最短路径就是他们的曼哈顿距离了，找不到，我们就先默认没有。  
接着，$500$ 个点的最短路算法，你想到了什么？Floyd！  
所以我们把这些点拿出来做一遍全源最短路，但我们的中转点只能是我们的边缘点哦！最后处理两个点的距离和就行了。  
注意：为了防止边缘点的重复，我们用集合来维护每个点是否出现过。  
别看我说的这么轻描淡写，这个思路想到还是很难的。  
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node
{
    int x,y;
    bool operator <(const node &f) const
    {
        if(x==f.x) return y>f.y;
        return x>f.x;//记得重载，我用的结构体
    }
};
set<node> s;
node pos[505];//空间要开大
int dp[505][505];
int n,top;
bool check(int i,int j)
{
    bool vis1=false,vis2=false;
    for(int k=1;k<=n;k++)
    {
        if(k==i||k==j) continue;
        if((pos[k].x==pos[i].x&&pos[k].y>=min(pos[i].y,pos[j].y)&&pos[k].y<=max(pos[i].y,pos[j].y))||(pos[k].y==pos[j].y&&pos[k].x>=min(pos[i].x,pos[j].x)&&pos[k].x<=max(pos[i].x,pos[j].x)))//判断有没有一个点可以使我只拐一次弯
        {
            vis1=true;
        }
        if((pos[k].y==pos[i].y&&pos[k].x>=min(pos[i].x,pos[j].x)&&pos[k].x<=max(pos[i].x,pos[j].x))||(pos[k].x==pos[j].x&&pos[k].y>=min(pos[i].y,pos[j].y)&&pos[k].y<=max(pos[i].y,pos[j].y)))//前面是先横后竖，这里是先竖后横
        {
            vis2=true;
        }
    }
    return vis1==false||vis2==false;
}
void floyd()
{
    for(int k=n+1;k<=top;k++)
    {
        for(int i=1;i<=top;i++)
        {
            for(int j=1;j<=top;j++) dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]);//Floyd板子
        }
    }
    return;
}
signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>pos[i].x>>pos[i].y,s.insert({pos[i].x,pos[i].y});
    top=n;
    for(int i=1;i<=n;i++)
    {
        pos[top+1]={pos[i].x-1,pos[i].y};
        if(s.count(pos[top+1])==0) s.insert(pos[top+1]),top++;//四个方向，代码很丑，不要介意
        pos[top+1]={pos[i].x+1,pos[i].y};
        if(s.count(pos[top+1])==0) s.insert(pos[top+1]),top++;
        pos[top+1]={pos[i].x,pos[i].y-1};
        if(s.count(pos[top+1])==0) s.insert(pos[top+1]),top++;
        pos[top+1]={pos[i].x,pos[i].y+1};
        if(s.count(pos[top+1])==0) s.insert(pos[top+1]),top++;
    }
    for(int i=1;i<=top;i++)
    {
        for(int j=1;j<=top;j++)
        {
            if(check(i,j))
            {
                dp[i][j]=abs(pos[i].x-pos[j].x)+abs(pos[i].y-pos[j].y);//曼哈顿距离
            }
            else dp[i][j]=1e18;
        }
    }
    floyd();
    int sum=dp[n][1];
    if(dp[n][1]>=1e17)
    {
        cout<<-1;//特判无解情况
        return 0;
    }
    for(int i=1;i<n;i++)
    {
        if(dp[i][i+1]>=1e17)
        {
            cout<<-1;
            return 0;
        }
        else
        {
            sum+=dp[i][i+1];
        }
    }
    cout<<sum;
    return 0;
}
```

---

