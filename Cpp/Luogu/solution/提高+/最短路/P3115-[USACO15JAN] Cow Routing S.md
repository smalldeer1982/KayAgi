# [USACO15JAN] Cow Routing S

## 题目描述

Bessie 对她农场那寒冷的天气感到厌烦，于是她准备坐飞机到一个更温暖的地方度假。不幸的是，她发现只有一个航空公司：Air Bovinia，愿意卖票给牛，并且这些票的结构有些复杂。

Air Bovinia 拥有 $n$ 架飞机，每架飞机都有一个经过两个及以上的城市的特殊航线。举个例子：一架飞机可以从城市 $1$ 出发，然后飞往城市 $5$，再飞到城市 $2$，最后飞到城市 $8$。注意**航线是单向的**。任何城市都不会在同一条航线上出现多次。如果 Bessie 选择了一条航线，那么她可以从航线上的任意一个城市上飞机，然后在途中任意一个城市下飞机。他不必从航线的起点上飞机，再从航线的终点下飞机。每条航线都有一个确定的花费，只要它搭乘了这个航班，她就必须支付这个航班的全额花费，不论她途经了几个城市。如果 Bessie 多次搭乘了某个航班，那么每次搭乘 Bessie 都必须支付航班的花费。

Bessie 想要找到从她农场所在的城市（城市 $A$）到她目的地所在城市（城市 $B$）最便宜的路线。请你告诉她他最少要花多少钱，并告诉她在此基础上她最少要**经过几段航线**，也即经过的城市数量 $-1$（包括起点和终点）。

## 说明/提示

$1\le n\le 1000$，$1\le cost\le 10^9$，$1\le len\le 100$。城市的编号均不超过 $1000$。

可能需要开 `long long`。

## 样例 #1

### 输入

```
3 4 3 
3 5 
1 2 3 4 5 
2 3 
3 5 4 
1 2 
1 5 
```

### 输出

```
2 2 
```

# 题解

## 作者：bits (赞：10)

蒟蒻很菜，请见谅。

题目不是**特别、特别、特别**复杂。有一点要解释一下。

_"输出只有一行。 输出Bessie旅行最少要花的钱以及在此基础上最少的花费（中间用空格隔开）。如果Bessie不能从她的农场到达她的目的地，则直接输出-1"_ 
 
"在此基础上最少的花费"是指：**在花的钱最少时，经过的城市最少。**  ~~这是唯一比较绕的地方。~~
 
## 步入正题
 
分析：
 
1.建图: 此题中每个航线经过的城市数量<=100， 因此，枚举起点城市和终点城市，暴力建图即可。

PS: 若每个航线经过的城市数量经过的城市较多(如<=100000)，我们可以采用“中转点”的思想。即，对于航线中的所有城市$t [1],t[2],.....t[n],$新建一个点$x$，从$t[1],t[2]......t[n-1]$建立到$x$的边（权为题中给定的$cost$），在从$x$建立到$t[2],t[3]......t[n]$的边（权为$0$），即可使其中任意一点到另一点的距离和为$cost$,但相比而言节约了不少空间（**如果存边的话**）。

2.求最短路。**照着SPFA模板打即可，不需优化。**

详见以下代码。

```cpp
// luogu-judger-enable-o2
//吸个氧气(...)
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
//以下为fread(二进制读入)模板，实测相对于getchar应该快点
char ss[1<<17],*A=ss,*B=ss;
inline char gc(){
    return A==B&&(B=(A=ss)+fread(ss,1,1<<17,stdin),A==B)?EOF:*A++;
}
template<typename qRead>
inline void qr(qRead &s){
    char c=gc(); s=0;
    for(;c<'0'||c>'9';c=gc());
    for(;c>='0'&&c<='9';c=gc())
        s=(s<<1)+(s<<3)+(c^48);
}

typedef long long ll;
const int N=1005,M=105;
struct edge{
    int len,cnt;
}Edge[N][N];//邻接矩阵，本题边较多，不宜用邻接表
int City[N],t[M],n,m,i,j,u,v,a,b;
ll Dis[N];//最短距离
bool Inq[N];

void SPFA(int s){
//模板
    for(i=1;i<=n;++i){
        Dis[i]=1e18; City[i]=1e9;
    }
    queue<int> q;
    q.push(s); Inq[s]=1;
    Dis[s]=0; City[s]=0;
    ll x; int y;
    while(!q.empty()){
        u=q.front(); q.pop(); Inq[u]=0;
        for(v=1;v<=n;++v){//用邻接矩阵存储，那么就要枚举点
            if(Edge[u][v].len<1e9){//如果有边的话
                x=Dis[u]+Edge[u][v].len;
                y=City[u]+Edge[u][v].cnt;
                if(x<Dis[v]){
                    Dis[v]=x;
                    City[v]=y;
                    if(!Inq[v]){
                        q.push(v); Inq[v]=1;
                    }
                }
                else if(x==Dis[v] && y<City[v])//同时使城市数量最小
                    City[v]=y;
            }
        }
    }
}

int main(){
    qr(a); qr(b); qr(m);
    int x,y;
    for(i=1;i<N;++i){
        for(j=1;j<N;++j)
            Edge[i][j].len=Edge[i][j].cnt=1e9;
    }
    while(m--){
        qr(x); qr(y);
        for(i=1;i<=y;++i){
            qr(t[i]);
            n=t[i]>n?t[i]:n;
        }
        for(i=1;i<y;++i){
            for(j=i+1;j<=y;++j){
                if(x<Edge[t[i]][t[j]].len){//防止有重边
                    Edge[t[i]][t[j]].len=x;
                    Edge[t[i]][t[j]].cnt=j-i;
                }
                else if(x==Edge[t[i]][t[j]].len && j-i<Edge[t[i]][t[j]].cnt)
                    Edge[t[i]][t[j]].cnt=j-i;
            }
        }
    }
    SPFA(a);
    //输出
    if(Dis[b]<1e18)
        printf("%lld %d\n",Dis[b],City[b]);
    else
        puts("-1 -1");
    return 0;
}
```
//谢谢观看蒟蒻的代码。

//管理员dalao求通过

---

## 作者：qiutianqwq (赞：5)

### P3115 [USACO15JAN]Cow Routing S题解

[题目传送门](https://www.luogu.com.cn/problem/P3115)

#### 1. 题目大意

给你 $n$ 条路线，可以从这条路线上任意一点出发，任意一点结束。无论走过几个城市，花费都是 $w_i$，问从点 $A$ 到点 $B$ 花费最少以及花费最少前提上最少走**几个**城市，若不能到达，则输出 $-1$。

#### 2. 分析

其实就是一道 dijkstra 的变形，但是是双关键字的。建边时从一条路径从前至后两两建边。我们发现，最少走过城市的数量只与最少花费上有关系，我们只需要以最少花费为关键字来跑一遍 dijkstra 再更新最少走过城市的数量即可（不会 dijkstra 看[这里](https://www.luogu.com.cn/blog/zhujunyiyyds/zui-duan-lu-xue-xi-bi-ji)）。

#### 3. 注意事项

其实我当时做题的大致思路没有问题，只不过没看数据范围，不是数组开大（MLE）了就是小了（RE)。我在这里提醒大家，做题之前，先看数据范围，确定好了数组大小，再写代码。

有 $N$ 条航线，且 $1 \leq N \leq 1000$，每条航线最多包含 $100$ 个城市，每条路线中的城市从前至后两两建边，最多建 $N \times \sum_{i=1}^{k - 1} \ i$ 条路线，代入 $n$、$k$，最多建 $4950000$ 条边。还有一种情况记得特判，费用相等，路径长度要取最小值。最后记得开 ```long long```。


#### 4. Code

```c
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005, MAXM = 4950005; //最多点数，最多边数
const long long INF = 4557430888798830399; //初始化一个极大值，这里要用long long

int st, fi, n, idx; //起点，终点，点的数量，边的数量 
long long dis[MAXN][2], head[MAXN]; //dis[i][0]为起点到点i最少费用，dis[i][1]为最少费用下的最短路径 
struct Edge{int nxt, to, w, c;}edge[MAXM]; //下一条边，到达的点，费用，路径长度 
struct Node{long long x, w;}; //编号，最少花费 
bool operator < (const Node &a, const Node &b) {return a.w > b.w;} //从小到大排序 
bool vis[MAXN];
priority_queue <Node> q;

void add (int from, int to, int w, int c) //建边 
{
    edge[++idx].nxt = head[from];edge[idx].to = to;edge[idx].w = w;edge[idx].c = c;
    head[from] = idx;
}

void init ()
{
    memset (head, -1, sizeof (head));
    memset (dis, 0x3f, sizeof (dis));
    scanf ("%d%d%d", &st, &fi, &n);
    for (int i = 1; i <= n; i++)
    {
        int k, w;
        long long v[105];
        scanf ("%d%d", &w, &k);
        for (int j = 1; j <= k; j++)    scanf ("%lld", &v[j]);
        //从前至后建边 
        for (int x = 1; x <= k; x++)
        for (int y = x + 1; y <= k; y++)    add (v[x], v[y], w, y - x); //建一条连接v[x]、v[y]费用为w路径长为y - x的边 
    }
}

//堆优化dijkstra
void dijkstar (int s)
{
    dis[s][0] = dis[s][1] = 0;
    q.push (Node {s, 0});
    while (!q.empty ())
    {
        Node cur = q.top ();
        q.pop ();
        if (vis[cur.x]) continue;
        vis[cur.x] = 1;
        for (int i = head[cur.x]; i != -1; i = edge[i].nxt)
        {
            int to = edge[i].to;
            if (dis[to][0] > dis[cur.x][0] + edge[i].w) //若有更小的花费，则更新 
            {
                dis[to][0] = dis[cur.x][0] + edge[i].w;
                dis[to][1] = dis[cur.x][1] + edge[i].c;
                if (vis[to])    continue;
                q.push (Node {to, dis[to][0]}); //入队是入编号和花费 
            }
            if (dis[to][0] == dis[cur.x][0] + edge[i].w) //记得特判费用等于的情况 
            {
                dis[to][1] = min (dis[to][1], dis[cur.x][1] + edge[i].c);//费用等于取路径长度小的 
                if (vis[to])    continue;
                q.push (Node {to, dis[to][0]});
            }
        }
    }
}

void output ()
{
    if (dis[fi][0] == INF)  printf ("-1 -1"); //不能到达 
    else                    printf ("%lld %lld", dis[fi][0], dis[fi][1]);
}

int main ()
{
    init ();        //输入 
    dijkstar (st);  //最短路 
    output ();      //输出 
    return 0;
}
```


#### 5. 总结

1. 拿到一个题，先仔细读题目，特别是**输入输出**（有没有换行之类）和**数据范围**。
2. 分析出题目的**特殊情况**。

---

## 作者：Cerisier (赞：3)

### 题意

我认为有必要解释一下题意。

从 $A$ 城市开始，要走到 $B$ 城市。有 $n$ 架飞机，每架飞机都有一个固定的航线且是单向的。而且，你可以在一架飞机的航线途中任意一个城市下飞机，但无论你做了多久，你总是需要花费全程的价格。

航班信息记录方式如下：

第一行航班的花费 $\text{cost}$ 和航线经过的城市数量 $m$。

接下来 $m$ 个整数，表示经过的所有城市。

求出从 $A$ 到 $B$ 最少花费的路线。并且 **在此基础上** 最少经过多少城市。

### 思路

很简单的最短路的一道题。其实并没有那么复杂。

首先我们要搞定建图，这里我用一个储存结构体的 $\text{vector}$ 来存图。

如果结构体里面仅仅存边的另一点是不够的，我们还需要储存当前结点经过的城市数量 $\text{dis}$。

```cpp
struct edge {
    int v, c, dis;
};
vector<edge> g[maxn];
```

我来说一下存图方式，对于经过的每个城市 $a_1,a_2,\cdots,a_n$，我们都可以在 $a_i$ 和 $a_j$ 建一条边（$i<j$），其中将 $\text{dis}$ 修改为 $j-i$，表示经过了 $j-i$ 个城市。

这个很好模拟，随便写写就可以写出来了。

```cpp
for (int i = 1; i <= m; i++) {
    int c, n;
    cin >> c >> n;
    edge tmp;
    tmp.c = c;
    for (int j = 1; j <= n; j++) {
        cin >> a[j];
    }
    for (int j = 1; j < n; j++) {
        for (int k = j + 1; k <= n; k++) {
            tmp.v = a[k];
            tmp.dis = k - j;
            g[a[j]].push_back(tmp);
        }
    }
}
```

然后我们要跑 spfa。但是，如何维护最少经过的城市呢？当 spfa 每次搜索到一个新的点的时候，同时判断是否花费更少，或者是 **花费相同且经过城市最短**。如果只要其中有一个条件成立的话，我们就进行更新。

由于我们需要分开储存最少花费和最少经过城市，所以我用 $\text{cost}$ 数组储存最少花费，$\text{sum}$ 储存最少经过城市。其他的都与普通 spfa 无异。

```cpp
void spfa(int s) {
    memset(cost, 127, sizeof(cost));
    memset(sum, 127, sizeof(sum));
    inf = cost[0];
    cost[s] = sum[s] = 0;
    q.push(s);
    in_queue[s] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;
        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i].v;
            if (cost[v] > cost[u] + g[u][i].c ||
                (cost[v] == cost[u] + g[u][i].c &&
                 sum[u] + g[u][i].dis < sum[v])) {
                cost[v] = cost[u] + g[u][i].c;
                sum[v] = sum[u] + g[u][i].dis;
                if (!in_queue[v]) {
                    q.push(v);
                    in_queue[v] = true;
                }
            }
        }
    }
    return;
}
```

最后判断终点的 $\text{cost}$ 或者 $\text{sum}$ 是否是等于 $\text{inf}$ 的，如果是的，那么就输出 $\texttt{-1 -1}$，否则直接输出。

记得要开 long long，题目中说了。

### 代码

```cpp
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define int long long

const int maxn = 1010;

struct edge {
    int v, c, dis;
};
vector<edge> g[maxn];

queue<int> q;
int a[maxn];
int cost[maxn], sum[maxn];
bool in_queue[maxn];
int inf;

void spfa(int s) {
    memset(cost, 127, sizeof(cost));
    memset(sum, 127, sizeof(sum));
    inf = cost[0];
    cost[s] = sum[s] = 0;
    q.push(s);
    in_queue[s] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;
        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i].v;
            if (cost[v] > cost[u] + g[u][i].c ||
                (cost[v] == cost[u] + g[u][i].c &&
                 sum[u] + g[u][i].dis < sum[v])) {
                cost[v] = cost[u] + g[u][i].c;
                sum[v] = sum[u] + g[u][i].dis;
                if (!in_queue[v]) {
                    q.push(v);
                    in_queue[v] = true;
                }
            }
        }
    }
    return;
}

signed main() {
    int s, t, m;
    cin >> s >> t >> m;
    for (int i = 1; i <= m; i++) {
        int c, n;
        cin >> c >> n;
        edge tmp;
        tmp.c = c;
        for (int j = 1; j <= n; j++) {
            cin >> a[j];
        }
        for (int j = 1; j < n; j++) {
            for (int k = j + 1; k <= n; k++) {
                tmp.v = a[k];
                tmp.dis = k - j;
                g[a[j]].push_back(tmp);
            }
        }
    }
    spfa(s);
    if (cost[t] == inf || sum[t] == inf) {
        cout << -1 << ' ' << -1 << endl;
    } else {
        cout << cost[t] << ' ' << sum[t] << endl;
    }
    return 0;
}
```

---

## 作者：WKAHPM (赞：3)

#### -1.前置知识

最短路，图论

#### 0.大体思路

对每条航线进行**建边**处理，同时记录两个城市之间的城市数(这里题目中的经过多少城市指从$u$到$v$**不包括首/尾**的城市数)，然后跑$Dijkstra$即可

#### 1.建边

本题由于边数较多，采用邻接矩阵存图较为合适。

定义$cost[i][j]$表示从$i$到$j$的最少费用，$to[i][j]$表示**在费用最少的情况下**从$i$到$j$所经过的最少城市数

假设一条航线的费用是$money$,有$len$个城市，对应的编号分别为$x_{1},x_{2},···,x_{len}$

首先要明确一个常识性问题：在一条航线上，一个城市**不能飞到它之前的城市**

所以我们可以得到一个显然的建边方法，对于一条航线的$x_{i}$，向$x_{j}(i<j<=len)$建一条长度为$money$的边。需要注意的是，如果之前$cost[i][j]$已赋值，则

- 如果$money<cost[i][j]$，需要更新$cost[i][j],to[i][j]$

- 如果$money=cost[i][j]$，则如果$i$到$j$之间的城市数$<to[i][j]$，更新$to[i][j]$

这样就可以满足**在花费最少的情况下**经过的城市数最少


#### 2.Dijkstra

定义$c[i]$为起点到$i$的最少花费，$ans[i]$为起点到$i$之间经过的城市数

假设当前从城市$k$开始拓展。

如果$k$与某个城市$i$有连边$cost[k][i]$，我们可以类比之前建边的方法进行更新。


- 如果$c[k]+cost[k][i]<c[i]$，更新$c[i],ans[i]$

- 如果$c[k]+cost[k][i]=c[i]$，如果$ans[k]+to[k][i]<ans[i]$，更新$ans[i]$

其中$ans[i]$的更新是指$ans[i]=ans[k]+to[k][i]$

根据定义，$ans[i]$表示起点到$i$的城市数，$ans[k]$表示起点到$k$的城市数，$to[k][i]$表示$k$到$i$之间的城市数，所以很明显有$ans[i]=ans[k]+to[k][i]$


#### 3.Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int read()//快读
{
        int sum = 0, f = 1;
        char c = getchar();
        while(c < '0' or c > '9')
        {
                if(c == '-') f = -1;
                c = getchar();
        }
        while(c >= '0' and c <= '9')
        {
                sum = (sum << 1) + (sum << 3) + c - '0';
                c = getchar();
        }
        return sum * f;
}

int a, b, n, len, maxn;
int cost[1010][1010], x[10010], to[1010][1010], money, ans[1010];
unsigned long long c[1010];//别忘了开long long
priority_queue<pair <long long, int> > q;
bool vis[1010];

void Dijkstra()//堆优化Dij
{
        for(int i = 1; i <= maxn; i++) c[i] = LONG_LONG_MAX;
        c[a] = 0;
        q.push(make_pair(0, a));
        while(!q.empty())
        {
                int k = q.top().second;
                q.pop();
                if(vis[k]) continue;
                vis[k] = 1;
                for(int i = 1; i <= maxn; i++)
                        if(cost[k][i] != 1e9 + 10)//有连边
                        {
                                if(c[i] > c[k] + cost[k][i])
                                {
                                        c[i] = c[k] + cost[k][i];
                                        ans[i] = ans[k] + to[k][i];
                                        q.push(make_pair(-c[i], i));
                                }
                                else
                                {
                                        if(c[i] == c[k] + cost[k][i])
                                        {
                                                if(ans[i] > ans[k] + to[k][i]) ans[i] = ans[k] + to[k][i];
                                        }
                                }
                        }
        }
}

int main()
{
        for(int i = 1; i <= 1010; i++)
                for(int j = 1; j <= 1010; j++)
                        cost[i][j] = 1e9 + 10;//赋初值
        memset(to, 127, sizeof(to));//赋初值
        a = read(), b = read(), n = read();
        //建边
        for(int i = 1; i <= n; i++)
        {
                money = read(), len = read();
                for(int j = 1; j <= len; j++)
                        x[j] = read(), maxn = max(maxn, x[j]);
                for(int j = 1; j <= len; j++)
                {
                        for(int k = j + 1; k <= len; k++)
                        {
                                if(cost[x[j]][x[k]] > money)
                                        cost[x[j]][x[k]] = money, to[x[j]][x[k]] = k - j;//k-j就是j到k之间的城市数（不包含首尾）
                                else
                                if(cost[x[j]][x[k]] == money)
                                {
                                        if(k - j < to[x[j]][x[k]])
                                        {
                                                to[x[j]][x[k]] = k - j;
                                        }
                                }
                        }
                }
        }

        Dijkstra();

        if(c[b] != LONG_LONG_MAX)//判断是否能到达
        {
                printf("%lld %d", c[b], ans[b]);
        }
        else
        {
                printf("-1 -1");
        }
        return 0;
}

```


---

## 作者：yeshubo_qwq (赞：3)

[题面传送门](https://www.luogu.com.cn/problem/P3115)
## 思路
很明显的最短路，我们可以用 SPFA 来做。

1.建边：因为这题范围很小，只有 $100$，因此可以直接枚举起点和终点，然后用 struct 和 vector 存边。

2.用 SPFA 求最短路：与最普通的 SPFA 相比较，唯一的区别是这题需要我们多开一个数组用来存。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s1,s2,i,j,k,x,z,e[1010],f2[1010],d[1010],inf;
long long f[1010];
struct node{
	int x,y,z;
	//x存终点，y存费用，z存距离 
};
vector<node>a[1010];//下标即起点 
node t;
queue<int>q;
int main(){
    scanf("%d%d%d",&s1,&s2,&m);
    for(i=1;i<=m;i++){
        scanf("%d%d",&z,&n);t.y=z;
        for(j=1;j<=n;j++)scanf("%d",&d[j]);
        for(j=1;j<n;j++)
            for(k=j+1;k<=n;k++)
                t.x=d[k],t.z=k-j,a[d[j]].push_back(t);//存边 
    }
    memset(f,127,sizeof(f));//费用初始化最大值 
    memset(f2,127,sizeof(f2));//城市数量初始化最大值
    inf=f[0];
    f[s1]=0;f2[s1]=0;
    q.push(s1);e[s1]=1;
    while(!q.empty()){//SPFA模板 
        x=q.front();
        for(i=0;i<a[x].size();i++){
            z=a[x][i].x;
            if(f[x]+a[x][i].y<f[z]||(f[x]+a[x][i].y==f[z]&&f2[x]+a[x][i].z<f2[z])){
                f[z]=f[x]+a[x][i].y;f2[z]=f2[x]+a[x][i].z;
                if(!e[z])//队列中已有，不需要重复进入 
					q.push(z),e[z]=1;
            }
        }
        q.pop();e[x]=0;
    }
    if(f[s2]==inf||f2[s2]==inf)printf("-1 -1");//不能到达 
    else printf("%lld %d",f[s2],f2[s2]);
    return 0;
}
```

---

## 作者：蒟蒻Ivan (赞：2)

## 题目分析

题目可以划分为两个问题：

问题 1 到达终点最少钱数。

问题 2 在问题 1 基础上最少需要经过的城市数量。（题面似乎错了）

----

对于每一条航线上的结点 $i$，这条航线上在 $i$ 之前的结点，都有有向边指向结点 $i$。每一条有向边的边权是这条航线的 $cost$。

用 $dis$ 数组记录最少价格，$dis_i$ 表示到达结点 $i$ 最少需要的钱。

本题可以使用 **SPFA**（Shortest Path Faster Algorithm），用队列来维护哪些结点可能会引起更优的结果，就能只访问必要的边了。

```cpp
void spfa(int start)
{
	memset(dis, 999999, sizeof(dis));
	dis[start] = 0; // 初始结点设为0
	q.push(start); 
	while(!q.empty())
	{
		int x = q.front();
		q.pop();
		for(int i = 0;i < g[x].size();i++)
		{
			if(dis[g[x][i]] > dis[x] + w[x][i]) // 如果有可能的松弛操作，则将此结点入队
			{
				dis[g[x][i]] = dis[x] + w[x][i];
				q.push(g[x][i]);
			}
		}
	}
}
```
----

在问题 1 的基础上，我们要尽可能的让经过的城市数少。

很简单，建一个 vector，在建图的时候，给每一条边再加一个参数 $st$。对于结点 $i$ 和 同一条航线上、在 $i$ 之后的结点 $j$，由 $i$ 指向 $j$ 的有向边的 $st$ 为 $j - i$。

再加一个数组 $step$ 维护每一个结点在花费最少的时候最少需要经过的城市数量。

```cpp
if(dis[g[x][i]] > dis[x] + w[x][i])
{
	dis[g[x][i]] = dis[x] + w[x][i];
	q.push(g[x][i]);
}
else if(dis[g[x][i]] == dis[x] + w[x][i]) // 对于step的松弛操作
{
	if(step[g[x][i]] > step[x] + st[x][i])
	{
		step[g[x][i]] = step[x] + st[x][i];
		q.push(g[x][i]); vis[g[x][i]] = 1;
	}
}

```

在入队操作时，加上一个判断（如上），就可以解决这个问题。

注意输出`-1`的情况，此处我用的是布尔数组 $vis$ 记录。


------------

最终代码如下：

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
#include<vector>
using namespace std;

vector<int> g[1010];
vector<int> w[1010];
vector<int> st[1010];
long long dis[1010];
int step[1010];
int city[1010];
bool vis[1010];
queue<int> q;

void spfa(int start)
{
	memset(dis, 999999, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	dis[start] = 0;
	q.push(start);
	while(!q.empty())
	{
		int x = q.front();
		q.pop();
		for(int i = 0;i < g[x].size();i++)
		{
			if(dis[g[x][i]] > dis[x] + w[x][i])
			{
				dis[g[x][i]] = dis[x] + w[x][i];
				step[g[x][i]] = step[x] + st[x][i];
				q.push(g[x][i]);
				vis[g[x][i]] = 1;
			}
			else if(dis[g[x][i]] == dis[x] + w[x][i])
			{
				if(step[g[x][i]] > step[x] + st[x][i])
				{
					step[g[x][i]] = step[x] + st[x][i];
					q.push(g[x][i]); vis[g[x][i]] = 1;
				}
			}
		}
	}
}
int main()
{
	int s, t, n;
	cin >> s >> t >> n;
	for(int i = 1;i <= n;i++)
	{
		int cost, nn;
		scanf("%d%d", &cost, &nn);
		for(int j = 1;j <= nn;j++)
		{
			scanf("%d", &city[j]);
		}
		for(int j = 1;j <= nn;j++) // 建图
		{
			for(int k = j + 1;k <= nn;k++)
			{
				g[city[j]].push_back(city[k]);
				w[city[j]].push_back(cost);
				st[city[j]].push_back(k - j);
			}
		}
	}
	spfa(s);
	if(!vis[t])
    	cout << -1 << " " << -1;
	else
    	cout << dis[t] << " " << step[t];
	return 0;
}
```

---

## 作者：5ab_juruo (赞：2)

介绍一种比较优秀的邻接表做法。

首先，由于题目中使用双关键字最短路，我们可以使用如下方法将其变成单关键字：

- 将 $(a_i,b_i)$ 用 $a_ic+b_i$ 替换，其中 $c>\max b_i$。

这样就可以保证双关键字排序，又减少代码难度。在实际的测试中 $c$ 取到 $1000$ 即可。

我们来考虑具体构造。根据题意，每一班航班需要一定的花费（下文用 $w_i$ 表示）“上车”，每经过一个城市又需要 $1$ 的，我们容易想到构造分层图，每一条航班一条，具体方案为：

1. 对于第 $i$ 航班上的所有点，构造一个虚点（可以理解为在空中越过了这个城市）；
2. 每个点向其对应虚点连权值为 $w_ic$ 的边，虚点向其连权值为 $0$ 的边；
3. 相邻两个虚点连权值为 $1$ 的边。

根据上面的技巧和构造，这样的方法一定可以达成要求。要注意的是，每个点可能对应不同的虚点，因为航班间是独立的。

分析一下，可以得到边数与点数都是 $\mathcal{O}(\sum a_i)$（$a_i$ 为第 $i$ 班航班经过的城市数），即使在城市很多的时候也能跑得比较快。

Code：

```cpp
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

typedef long long ll;
constexpr int max_n = 1000, max_a = 100, max_m = max_n*max_a * 3, max_nd = max_n + max_a * max_n;
const ll INF = 0x3f3f3f3f3f3f3f3fll, max_c = 1000;

struct node
{
	int id;
	ll vl;
	node(int _i = 0, ll _v = 0) : id(_i), vl(_v) { }
	
	bool operator<(const node& n) const
	{
		return vl > n.vl;
	}
};
priority_queue<node> pq;

int hd[max_nd], des[max_m], nxt[max_m], e_cnt = 0, n_cnt = max_n;
ll val[max_m], dis[max_nd];
bool vis[max_nd] = {};

inline ll my_min(ll a, ll b) { return (a < b)? a:b; }
inline int my_max(int a, int b) { return (a > b)? a:b; }

void add_edge(int s, int t, ll v) // 邻接表存图加边
{
	des[e_cnt] = t, val[e_cnt] = v;
	nxt[e_cnt] = hd[s], hd[s] = e_cnt++;
}

int main()
{
	memset(hd, -1, sizeof hd);
	memset(dis, 0x3f, sizeof dis);
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int s, t, n;
	ll tc;
	node cur;
	
	cin >> s >> t >> n;
	s--, t--;
	for (int ii = 0, tn; ii < n; ii++) // 输入航班
	{
		cin >> tc >> tn;
		for (int i = 0, tp = -1, pt; i < tn; i++)
		{
			cin >> pt, pt--;
			add_edge(pt, n_cnt, tc * max_c); // 与虚点连边
			add_edge(n_cnt, pt, 0);
			
			if (tp != -1)
				add_edge(n_cnt - 1, n_cnt, 1); // 相邻虚点连边
			tp = pt, n_cnt++;
		}
	}

	dis[s] = 0;
	pq.emplace(s, 0);
	
	while (!pq.empty()) // 最短路，这里用 dijkstra
	{
		cur = pq.top();
		pq.pop();
		
		if (!vis[cur.id])
		{
			vis[cur.id] = true;
			for (int p = hd[cur.id]; p != -1; p = nxt[p])
				if (dis[des[p]] > dis[cur.id] + val[p])
				{
					dis[des[p]] = dis[cur.id] + val[p];
					pq.emplace(des[p], dis[des[p]]);
				}
		}
	}
	
	if (dis[t] == INF) // 特判无解
		cout << "-1 -1" << endl;
	else
		cout << dis[t] / max_c << " " << dis[t] % max_c << endl;
	
	return 0;
}
```

---

## 作者：a_grain (赞：2)



------------
[题面](https://www.luogu.com.cn/problem/P3115)

题目大意：
------------
给你起点和终点，并给出许多条**从前往后**互相能到达的边，求出起点到终点的最短路和乘坐飞机的次数（到达一个城市算一次~~本蒟蒻一开始没看清题目，求了航班数~~）。

------------
思路
------------
如果每一次读入进的航班包含城市数为 $n$。

则先把读入进来的航班都做 $n*(n-1)/2$ 次建边，
然后就是求最短路与乘坐飞机的次数了。

在此确定下邻接表应该开多大，因为 $n$ 最大为 $100$，所以一次最多能建 $4950$，而最多有 $1000$ 个航班，因此应该再 $4950$ 的基础上乘 $1000$，故应开到 $4950000$。

由于此题没有出现负环情况，因此立刻决定打 Dijkstra。

当然普通的 Dijkstra 显然只能处理最短路问题，无法解决乘坐飞机的次数的问题，因此我们应该多开一个数组 $tim[i]$ 存次数，并在邻接表中加一个变量存该边的次数的变量 $tim$。

假设正在做 $start$ 这个点，$to$ 为遍历的点，$dis[i]$ 存储最少花费，$e[i]$ 为邻接表。

- 如果 $dis[to]>dis[start]+e[i].dis$，把 $dis[to]$ 赋值为 $dis[start]+e[i].dis$，$tim[to]$ 也变为 $tim[start]+e[i].tim$
- 如果 $dis[to]==dis[start]+e[i].dis$，则 $tim[to]=min(tim[to],tim[start]+e[i].tim)$

------------

**AC code**
```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=4950001,NN=1001;
int cnt,n,i,j,k,h[NN],vis[NN],tim[NN],A,B,N,v,a[101];
long long dis[NN];
struct Node{int dis,to,nex,tim;}e[M];
void add(int x,int y,int v,int tim){//邻接表
	e[++cnt].dis=v;
	e[cnt].to=y;
	e[cnt].nex=h[x];
	e[cnt].tim=tim;
	h[x]=cnt;
}
priority_queue<pair<long long,int> ,vector<pair<long long,int> > ,greater<pair<long long,int> > > q;//pair按照第1个关键字排序
void Dijkstra(int x){//堆优化+Dijkstra
	int start,to,i;
	memset(dis,127,sizeof(dis));
	memset(vis,0,sizeof(vis));
	memset(tim,0,sizeof(tim));
	q.push(make_pair(0,x));dis[x]=0;
	while(!q.empty()){
		start=q.top().second;//取出开始节点
		q.pop();
		if(vis[start])continue;//如果已经做过了就换下一个
		vis[start]=1;//把开始节点赋值为做过
		for(i=h[start];i;i=e[i].nex){
			to=e[i].to;
			if(dis[to]>dis[start]+e[i].dis){
				dis[to]=dis[start]+e[i].dis;tim[to]=tim[start]+e[i].tim;
				if(!vis[to])q.push(make_pair(dis[to],to));
			}
			else if(dis[to]==dis[start]+e[i].dis)tim[to]=min(tim[to],tim[start]+e[i].tim);
		}
	}
}
void read(int &x){//快读
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
}
signed main(){
	read(A);read(B);read(N);
	for(i=1;i<=N;i++){
		read(v);read(n);
		for(j=1;j<=n;j++)read(a[j]);
		for(j=1;j<n;j++)//建边
			for(k=j+1;k<=n;k++)
				add(a[j],a[k],v,k-j);
	}
	Dijkstra(A);
	dis[B]==dis[0]?printf("-1 -1\n"):printf("%lld %lld\n",dis[B],tim[B]);//判断如果dis[B]没有更新过就输出2个-1
}
```
------------
在单源非负权最短路问题中，Dijkstra 算法时间复杂度 $O(n^2)$ 是较为稳定的，不像 SPFA，面对一些数据可能会被卡掉。

而当 Dijkstra 在经过堆优后，时间复杂度则会变为 $O((n+m)log_2n)$，相比与原来就显得非常可观了
。
因此本蒟蒻在此强烈推荐不会 Dijkstra 的人去学习一下 Dijkstra。

[入门模板题](https://www.luogu.com.cn/problem/P3371)

[堆优模板题](https://www.luogu.com.cn/problem/P4779)

其余题目可以搜索标签**最短路**或**Dijkstra**。

------------
# The End.

---

## 作者：Parat_rooper (赞：1)

# 解题思路：

这道题就是一道裸的最短路板子题啊！

不过就是换了一下建边的方式，我们可以发现，每一条航线中每一个城市和在航线中顺序在其后的每一个城市有一条边，边权已给，经过城市数量也很好算。

然后我们考虑使用哪种最短路算法，观察数据范围发现 $n\le1000$ ！ $\Theta(n^2)$ 的普通Dijkstra算法即可通过。

最后提供一个相对可能比其他题解短一些的代码：

```cpp
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
using LL = long long;
using pii = pair<pair<int, int>, int>;

const int kMaxN = 1001;

int n, A, B, p, m;
bool b[kMaxN];

struct node {
  LL d = 1LL << 60;//最短路长度
  bool b;
  int hd = 1 << 30;//最小经过城市数
  vector<pii>e;//这个地方我直接用了pair，分别存路径长度，经过城市数和路径终点
}a[kMaxN];

int main() {
  ios_base::sync_with_stdio(0), cin.tie(NULL), cout.tie(NULL);//懒人快读快写
  cin >> A >> B >> m;
  for (int i = 1, v, w, c[101]; i <= m; i++) {
    cin >> v >> w;
    for (int j = 1; j <= w; j++) {
      cin >> c[j];
      if (!b[c[j]]) {//这个地方算的是城市的数量
        n++, b[c[j]] = 1;
      }
    }
    for (int j = 1; j < w; j++) {//我并没有去重边，因为没有必要，不影响算法正确性
      for (int k = j + 1; k <= w; k++) {
        a[c[j]].e.push_back({{v, k - j}, c[k]});
      }//枚举每一对城市连边
    }
  }
  a[A].d = a[A].hd = 0;
  for (int i = 1; i <= n; i++) {//朴素dij
    p = 0;
    for (int j = 1; j <= n; j++) {
      if (!a[j].b && (!p || a[p].d > a[j].d || (a[p].d == a[j].d && a[p].hd > a[j].hd))) {
        p = j;
      }
    }
    if (!p) {
      break;
    }
    a[p].b = 1;
    for (pii j : a[p].e) {
      if ((a[p].d + j.first.first) < a[j.second].d || 
      ((a[p].d + j.first.first) == a[j.second].d && (a[p].hd + j.first.second) < a[j.second].hd)) {//注意是双关键字
        a[j.second].d = a[p].d + j.first.first, a[j.second].hd = a[p].hd + j.first.second;
      }
    }
  }
  cout << (a[B].d == (1LL << 60) ? -1 : a[B].d) << " " << (a[B].hd == (1 << 30) ? -1 : a[B].hd) << "\n";//判无解
  return 0;
}
```
完结撒花。

---

## 作者：小恐 (赞：1)

这道题是一个最短路问题。

注意是要求的是最短距离还有经过的城市数，不包括起点。

这里需要把每个飞机的路线转化为边，注意到这里可能有重边，但如果不处理重边的话，就有$10^7$条边，边数明显太大了。但如果处理重边的话就会少很多。既然要处理重边，我们干脆就拿邻接矩阵存，然后跑$O(n^2)$的dij（是不是有直接学堆优化的，朴素没学的？[看这](https://blog.csdn.net/Mr_Kingk/article/details/100175811)）。

由于要考虑城市数，所以每次找最小的时候如果$dis$一样就要比一下城市数，哪个少就取哪个。注意每次更新也要更新城市数。

最后要注意2点：
1. 十年OI一场空，不开ll见祖宗！
2. 注意不能到达输出-1

上代码：
```cpp
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int NR=1e3+5;
const int MR=1e5+5;
const int INF=0x3f3f3f3f;
typedef long long LL;
inline int read()
{
	int x=0;
	int bei=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			bei=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*=bei;
}
LL g[NR][NR];
int cnt[NR][NR];
int a[105];
LL dis[NR];
int city[NR];
bool book[NR];
int n=1000;
void dij(int s)
{
	memset(dis,0x3f3f,sizeof(dis));
	memset(city,0x3f,sizeof(city));
	dis[s]=0;
	city[s]=0;
	for(int i=1;i<=n;++i)
	{
		LL minn=0x3f3f3f3f3f3f3f3f;
		int ci=INF;
		int mini;
		for(int j=1;j<=n;++j)
		{
			if(book[j])
				continue;
			if(dis[j]<minn)
				minn=dis[j],ci=city[j],mini=j;
			else if(dis[j]==minn&&ci>city[j])
				ci=city[j],mini=j;
		}
		book[mini]=1;
		for(int j=1;j<=n;++j)
		{
			if(dis[j]>minn+g[mini][j])
				dis[j]=minn+g[mini][j],city[j]=ci+cnt[mini][j];
			else if(dis[j]==minn+g[mini][j]&&city[j]>ci+cnt[mini][j])
				city[j]=ci+cnt[mini][j];
		}
	}
}
int main()
{
	int s=read(),t=read(),N=read();
	memset(g,0x3f3f,sizeof(g));
	for(int i=1;i<=N;++i)
	{
		int co=read(),ci=read();
		for(int i=1;i<=ci;++i)
			a[i]=read();
		for(int i=1;i<=ci;++i)
			for(int j=i+1;j<=ci;++j)
			{
				if(g[a[i]][a[j]]>co)
					g[a[i]][a[j]]=co,cnt[a[i]][a[j]]=j-i;
				else if(g[i][j]==co)
					cnt[a[i]][a[j]]=min(cnt[a[i]][a[j]],j-i);
			}
	}
	dij(s);
	if(dis[t]==0x3f3f3f3f3f3f3f3f)
		dis[t]=city[t]=-1;
	printf("%lld %d",dis[t],city[t]);
	return 0;
}

```


---

## 作者：曹老师 (赞：1)

## Sol ##

[blog食用](http://www.caolaoshi.men/index.php/archives/usaco15jan-cowrout.html)

哇，第一次写邻接矩阵的$dij$！！！以前都是用邻接表存的，这次不太一样，**因为边比较多，邻接表的话要开的空间很大，不过可以注意到，虽然边很多，但是点很少，所以考虑用邻接矩阵来做。**

对于图的存储，每一个点都会到它路径上的所有点有一条长度为该航班花费的路径，**但是肯定会有重复的路径，所以我们取一下重复路径中最短的那条就好了**，因为题目中还说要经过的城市最少，所以呢，我这里建图其实还是不太严谨的，因为建图的时候可能会出现长度相等但是经过的城市比较少，我们也要更新一次。

然后，就是一个双关键值的$dij$，不知道为嘛题解中都用的$spfa$，$dij$很难写吗？？？与往常不太一样的是，在更新答案的时候，**分两种情况，就是上面说的：尽量选路径比较短的，如果路径相等，选经过点少的。**用优先队列加以维护，最后如果目的地的距离没有被更新，就说明到不了，就输出-1什么的就好了。

## Code ##

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;

struct Road {
	long long num , len , city;
	Road(long long nn , long long dd , long long ss) {
		num = nn , len = dd , city = ss;
	}
	bool operator < (const Road &a) const {
		return (len > a.len) || (len == a.len && city > a.city);
	}
};
long long dis[1005] , city[1005];
long long s , t , n , road[105] , maxx , map[1005][1005] , ci[1005][1005];

long long max(long long a , long long b) {
	return a>b?a:b;
}

void dij(long long s) {
	memset(dis , 0x3f , sizeof(dis));
	memset(city , 0x3f , sizeof(city));
	priority_queue<Road>q;
	dis[s] = city[s] = 0;
	q.push(Road(s,dis[s],city[s]));
	while(!q.empty()) {
		Road u = q.top();
		q.pop();
		if(u.len != dis[u.num] || u.city != city[u.num])
			continue;
		for(int i=1; i<=maxx; i++)
			if(dis[u.num]+map[u.num][i] < dis[i] || (dis[u.num]+map[u.num][i] == dis[i] && city[u.num]+ci[u.num][i] < city[i])) {
				dis[i] = dis[u.num] + map[u.num][i];
				city[i] = city[u.num] + ci[u.num][i];
				q.push(Road(i , dis[i] , city[i]));
			}
	}
}

int main() {
	memset(map , 0x3f , sizeof(map));
	memset(ci , 0x3f , sizeof(ci));
	scanf("%lld%lld%lld",&s,&t,&n);
	for(long long i=1; i<=n; i++) {
		long long x , y;
		scanf("%lld%lld",&x,&y);
		for(long long j=1; j<=y; j++) {
			scanf("%lld",&road[j]);
			maxx = max(maxx ,road[j]);
		}
		for(long long j=1; j<=y; j++)
			for(long long k=j+1; k<=y; k++)
				if(x < map[road[j]][road[k]]) {
					map[road[j]][road[k]] = x;
					ci[road[j]][road[k]] = k-j;
				}	
	}
	dij(s);
	if(dis[t] == dis[0])
		printf("-1 -1");
	else
		printf("%lld %lld",dis[t],city[t]);
	return 0;
}
```


  [1]: https://www.luogu.org/problemnew/show/P3115

---

## 作者：emo_male_god (赞：0)

### [USACO15JAN]Cow Routing S 题解

题意很简单，不用多说。

先来看如何建边：因为一条航线一次性可以经过多个城市，还可以反复上下飞机。所以我们枚举一条航线里的每两个城市进行连边，边权都相等。

因为题目还要求经过几条边，所以我们在建边的时候记录下这条边起点、终点、边权、途径的城市个数。然后跑一遍 Dijkstra 就行。

#### 其他注意事项：

除了最短路用的记录花费的数组，还需要开一个记录保证花费最小的情况下经过最小边数的数组。

因为建边比较多，前向星数组要开很大。

#### Code

```cpp
#include <iostream>
#include <cstring>
#include <bitset>
#include <queue>

using namespace std;

const int N = 1e3 + 5, M = 5e6 + 5;

struct node
{
	long long dis;
	int road, u;
	bool operator > (const node &x) const {return dis == x.dis ? road > x.road : dis > x.dis;}
};

priority_queue<node, vector<node>, greater<node>> p;
int head[N], to[M], we[M], ne[M], c[M], idx = 1;
int s, t, n, a[N], road[N];
long long dist[N];
bitset<N> st;

void add(int u, int v, int w, int cnt)
{
	c[idx] = cnt;
	to[idx] = v;
	we[idx] = w;
	ne[idx] = head[u];
	head[u] = idx ++ ;
}

void Dijkstra()
{
	memset(dist, 0x3f, sizeof dist);
	memset(road, 0x3f, sizeof road);
	road[s] = dist[s] = 0;
	p.push({0, 0, s});

	while (!p.empty())
	{
		int u = p.top().u;
		p.pop();

		if (st[u]) continue;
		st[u] = true;

		for (int i = head[u]; i; i = ne[i])
		{
			int v = to[i], w = we[i], cnt = c[i];
			if (dist[v] > dist[u] + w)
			{
				dist[v] = dist[u] + w;
				road[v] = road[u] + cnt;
				p.push({dist[v], road[v], v});
			}
			else if (dist[v] == dist[u] + w && road[v] > road[u] + cnt)
			{
				road[v] = road[u] + cnt;
				p.push({dist[v], road[v], v});
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> s >> t >> n;

	int w, cnt;
	for (int i = 1; i <= n; i = i ++ )
	{
		cin >> w >> cnt;
		for (int j = 1; j <= cnt; j = j ++ )
		{
			cin >> a[j];
			for (int k = 1; k < j; k = k ++ ) add(a[k], a[j], w, j - k); // 经过几个城市
		}
	}

	Dijkstra();

	if (dist[t] == 0x3f3f3f3f3f3f3f3f) printf("-1 -1\n");
	else printf("%lld %d\n", dist[t], road[t]);
	return 0;
}
```



[不懂可以私信我！](https://www.luogu.com.cn/user/798157)

---

## 作者：KK_lang (赞：0)

## 题意

给定若干条航线，每条航线上任两点之间的花费相等。求 $1$ 点到 $n$ 点的最短路（第一优先为花费，第二优先为乘坐飞机数）。

## 思路

建边后跑最短路，因为有优先度问题，所以可以重载一下小于号（我没有重载，用一个 ~~很长的~~ `if` 就有同样效果）。

有重边，继而邻接表不太能用，因为 `vector` 不太能判重编；所以这道题实际上是**邻接矩阵的最短路**。

有重边，那么邻接矩阵就要存最优的，就可以用上面说的长 `if` 解决，在最短路更新 `dis` 中也有类似的操作。

```cpp
// w[i][j] 表示 i 到 j 的花费，s[i][j] 表示 i 到 j 的乘坐飞机数
// 如果第一优先 w 更小，或者 w 一样并且 s 更小，就更新
if (w[t[x]][t[y]] > tw || (w[t[x]][t[y]] == tw && s[t[x]][t[y]] > y - x))  
	w[t[x]][t[y]] = tw, s[t[x]][t[y]] = y - x;
```

因为有一个取更小的操作，所以在建边和最短路之前要 `memset`。

$d1_{i}$ 表示 $1$ 号点到 $i$ 号点的最小花费，同理 $d2_{i}$ 表示 $1$ 号点到 $i$ 号点的最小乘坐飞机数。

## AC Code

这里姑且先用 SPFA 实现 ~~（不会被卡）~~。

```cpp
#include<bits/stdc++.h>
using namespace std;

int a, b, n, n2;
int t[1010];
long long d1[1010], d2[1010];
bool vis[1010];
int w[1010][1010], s[1010][1010];

void spfa()
{
	memset(d1, 0x3f, sizeof(d1));
	memset(d2, 0x3f, sizeof(d2));
	memset(vis, false, sizeof(vis));
	d1[a] = 0, d2[a] = 0;
	queue<int> q;
	q.push(a);
	vis[a] = true;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		vis[u] = false;
		for (int i = 1; i <= n; i++)
		{
			if (w[u][i] > 1e9) continue;
			if (d1[u] + w[u][i] < d1[i] || (d1[u] + w[u][i] == d1[i] && d2[u] + s[u][i] < d2[i]))
			{
				d1[i] = d1[u] + w[u][i];
				d2[i] = d2[u] + s[u][i];
				if (!vis[i])
				{
					q.push(i);
					vis[i] = true;
				}
			}
		}
	}
}

int main()
{
	cin >> a >> b >> n2;
	memset(w, 0x3f, sizeof(w));
	memset(s, 0x3f, sizeof(s));
	for (int i = 1; i <= n2; i++)
	{
		int tw, m;
		cin >> tw >> m;
		for (int j = 1; j <= m; j++) 
		{
			cin >> t[j];
			n = max(n, t[j]);
		}
		for (int x = 1; x < m; x++)
			for (int y = x + 1; y <= m; y++)
				if (w[t[x]][t[y]] > tw || (w[t[x]][t[y]] == tw && s[t[x]][t[y]] > y - x))  
				    w[t[x]][t[y]] = tw, s[t[x]][t[y]] = y - x;
	}
	spfa();
	if (d1[b] > 1e18) cout << "-1 -1\n";
	else cout << d1[b] << " " << d2[b] << endl;
	return 0;
}
```

---

## 作者：哈士奇憨憨 (赞：0)

## 题意
给定 $N$ 条路线及其费用，求从 $A$ 到 $B$ 的最小费用，以及在最小费用前提下，最少经过的边的数量。
## 思路
每条线路使得线路上的一些点对可以互达，并且代价为线路费用，边的数量为点对在线路中的距离。由此可以构造出一张图，要求的就是 $A$ 到 $B$ 的最短路径。

由于点数、线路数量都很小，所以可以直接枚举线路中的点对构图，然后用 Dijkstra 算法求最短路即可。
## 复杂度
令点数为 $O(M)$，本题中 $M = 1000$。

令线路长度为 $O(L)$，本题中 $L = 100$。
### 时间
线路数量 $O(N)$，枚举点对构图 $O(L^2)$，总共 $O(NL^2)$。求最短路 $O(M^2)$。总时间复杂度为 $O(NL^2+M^2)$。
### 空间
记录邻接矩阵 $O(M^2)$。记录线路 $O(M)$。总空间复杂度为 $O(M^2)$。
## CODE
```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using Pil = pair<LL, int>;  // 距离、边数
const int kMaxN = 1001;
const LL kInf = 1e18;
Pil l[kMaxN][kMaxN], d[kMaxN];
int q[kMaxN], a, b, c, n, m;
int main() {
  fill(l[0], l[kMaxN], (Pil){kInf, 0});  // 初始化邻接矩阵
  cin >> a >> b >> n;
  for (int i = 1; i <= n; i++) {
    cin >> c >> m;
    for (int j = 1; j <= m; j++) {
      cin >> q[j];
      for (int k = 1; k < j; k++) {                      // 枚举航线上靠前的点
        l[q[k]][q[j]] = min(l[q[k]][q[j]], {c, j - k});  // 更新航线上两点的最短距离
      }
    }
  }
  fill(q, q + kMaxN, 0), fill(d, d + kMaxN, (Pil){kInf, 0});  // 初始化标记数组和距离数组
  d[a] = {0, 0};                                              // 初始化起点距离
  for (int i = 1; i < kMaxN; i++) {
    int p = 0;
    for (int j = 1; j < kMaxN; j++) {  // 寻找距离最近的点
      if (!q[j] && (!p || d[j] < d[p])) {
        p = j;
      }
    }
    q[p] = 1;                          // 标记到达
    for (int j = 1; j < kMaxN; j++) {  // 更新其他点的距离
      d[j] = min(d[j], {d[p].first + l[p][j].first, d[p].second + l[p][j].second});
    }
  }
  if (d[b].first == kInf) {
    cout << "-1 -1";
  } else {
    cout << d[b].first << " " << d[b].second;
  }
  return 0;
}
```

---

## 作者：羚羊WANG (赞：0)

首先先跟大家说明一下，题目解释可能有一点不清晰，题目说的最小乘坐飞机的次数，就是相当于经过最少的城市

所以，题目就是让我们输出最小花费，以及在此基础上经过最少的城市

我们可以观察，$N \leq 1000$,所以显然不能采用$floyd$算法

题目中让我们求两个点之间的最小花费，我们可以抽象成一个一个最短路问题，两个点之间的距离是两个点之间的最小花费

题目中还有一个关键字，就是经过最小的城市，我们可以把这个作为第二关键字，把最小花费作为第一关键字，跑一遍最短路即可

跑最短路从起点开始跑，一直到终点

还有一个要注意到点：最短路的值要开$long long$，初值要赋一个极大值

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define inf 0x3f
using namespace std;
inline int read()
{
	int x=0;
	bool f=0;
	char c=getchar();
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
void write(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int n,m;
int s,t;
int g[1010][1010];
int dis[10010],ride[10010];
bool vis[10010];
int tot[1010][1010];
int e[10010];
priority_queue<pair<int,int> ,vector<pair<int,int> >,greater<pair<int,int> > >p;
inline void dij(){
	for(register int i=1;i<=n;++i)	
		dis[i]=1000000000000;
	dis[s]=0;
	p.push({0,s});
	while(!p.empty())
		{
			int tmp1,tmp2;
			tmp1=p.top().first;
			tmp2=p.top().second;
			p.pop();
			if(vis[tmp2])
				continue;
			vis[tmp2]=1;
			for(register int i=1;i<=n;++i)
				{
					if(g[tmp2][i]==inf)
						continue;
					if(dis[tmp2]+g[tmp2][i]<dis[i])
						{
							dis[i]=dis[tmp2]+g[tmp2][i];
							ride[i]=ride[tmp2]+tot[tmp2][i];
							p.push({dis[i],i});
						}
					if(dis[tmp2]+g[tmp2][i]==dis[i] && ride[tmp2]+tot[tmp2][i]<ride[i])
						ride[i]=ride[tmp2]+tot[tmp2][i];
				}
		}
}
signed main(){
	memset(g,inf,sizeof(g));
	memset(tot,inf,sizeof(tot));
	s=read();
	t=read();
	m=read();
	while(m--)
		{
			int cost;
			int pop;
			cost=read();
			pop=read();
			for(register int i=1;i<=pop;++i)
				{
					e[i]=read();
					n=max(n,e[i]);
				}
			for(register int i=1;i<=pop;++i)
				for(register int j=i+1;j<=pop;++j)
					{
						if(g[e[i]][e[j]]>cost)
							{
								g[e[i]][e[j]]=cost;
								tot[e[i]][e[j]]=j-i;
							}
						else if(g[e[i]][e[j]]==cost)
							tot[e[i]][e[j]]=max(tot[e[i]][e[j]],j-i);
					}
		}
	dij();
	if(dis[t]==1000000000000)
		{
			write(-1);
			putchar(' ');
			write(-1);
			return 0;
		}
	write(dis[t]);
	putchar(' ');
	write(ride[t]);
	return 0;
}

```


---

## 作者：winmt (赞：0)

这么简单的题怎么就这么点点人A？大家都不喜欢刷USACO月赛？

【思路】

一眼就应该看出是个无脑的双关键值最短路啊，直接裸的SPFA，一边跑一边记录并更新两个要求的关键值。最后输出就可以了。

相当于一个单源最短路的模板题，只不过加了一个判断到达此最短路径的经过最少节点数而已，但并无难度。

【代码】




```cpp
#include<iostream>
#include<fstream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<vector>
#include<queue>
#include<deque>
#include<utility>
#include<map>
#include<set>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<functional>
#include<sstream>
#include<cstring>
#include<bitset>
#include<stack>
using namespace std;
int s,e,n,m,mx=-1;
long long val;
int a[105];
long long dis[1005];
int cnt[1005];
long long v[1005][1005];
bool in_queue[1005];
queue<int>q;
int kkk[1005][1005];
void spfa()
{
    for(int i=1;i<=mx;i++)dis[i]=1e18;
    dis[s]=0;
    q.push(s);
    in_queue[s]=1;
    while(!q.empty())
    {
        int t=q.front();
        in_queue[t]=0;
        q.pop();
        for(int i=1;i<=mx;i++)
        {
            if(dis[i]>dis[t]+v[t][i])
            {
                dis[i]=dis[t]+v[t][i];
                cnt[i]=cnt[t]+kkk[t][i];
                if(!in_queue[i])
                {
                    in_queue[i]=1;
                    q.push(i);
                }
            }
            else if(dis[i]==dis[t]+v[t][i])if(cnt[t]+kkk[t][i]<cnt[i])cnt[i]=cnt[t]+kkk[t][i];
        }
    }
}
int main()
{
    scanf("%d%d%d",&s,&e,&n);
    memset(v,0x3f,sizeof(v));
    for(int i=1;i<=n;i++)
    {
        scanf("%lld%d",&val,&m);
        for(int j=1;j<=m;j++){scanf("%d",&a[j]);mx=max(mx,a[j]);}
        for(int j=1;j<=m;j++)
        {
            for(int k=j+1;k<=m;k++)
            {
                if(val<v[a[j]][a[k]])  
                {  
                    v[a[j]][a[k]]=val;
                    kkk[a[j]][a[k]]=k-j;  
                }
                else if(val==v[a[j]][a[k]] && k-j<kkk[a[j]][a[k]])
                {
                    kkk[a[j]][a[k]]=k-j;
                }
            }
        }
    }
    spfa();
    if(dis[e]==1e18)
    {
        printf("-1 -1\n");
        return 0;
    }
    else
    {
        printf("%lld %d\n",dis[e],cnt[e]);
        return 0;
    }
}
```

---

