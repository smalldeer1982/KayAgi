# [ICPC 2017 WF] Son of Pipe Stream

## 题目描述

两年以前，你帮助你的家乡安装了国内的第一个 Flubber 管道网络，获得了巨大成功。投票表明每个人都喜欢在自己家的厨房里装上 Flubber 分配器，而现在一些有进取心的市民发现了一种新的用途——Flubber 和水混合后似乎可以帮助灭火！这是一个很及时的发现，因为最近无法控制的大火出奇地常见。

你家乡的市议会想在一个位于中央的地方制造 Flubber 和水的混合物以利用 Flubber 的这个属性。这个被称为 Flubber 部门的地方拥有专门训练的员工去往着火的地点并且利用经过处理的 Flubber 来控制火势。

管道已经在城市中铺设好。你会得到管道布局，而你需要决定如何将 Flubber 从 Flubber 工厂、将水从一个本地水源通过管道运送至 Flubber 部门。

注意 Flubber 和水会在同一管道网络中，甚至可能在同一条管道中流动。所有管道是双向的，但是 Flubber 和水不能在同一条管道中异向流动。此外，如果两种液体同向流过一条管道，它们会不可避免地混合，因此网络中的所有节点配备了特殊的膜和筛，如你所见，可以分离和重新组织所有流入的混合物。管道网络是个封闭系统，因此在每个节点处每种液体的总流入速率必须等于总流出速率，除了每种液体各自的源头和目的地（Flubber 部门）。

每条管道有某个容量，有些粘稠的 Flubber 有一个粘度值 $v$，所以能运输 $v$ 升每秒的水的管道只能运输 $1$ 升每秒的 Flubber。管道对于混合物的容量是线性变化的。更精确地，假设 $c$ 表示管道对于水的容量，$f$ 和 $w$ 分别表示 Flubber 和水流过管道的速率（单位均为升每秒），则容量的限制用不等式 $v⋅f+w\le c$ 表示。

你主要关心的是平衡流到 Flubber 部门的混合物。你想要尽可能多的混合液体，但是也需要足够的水——因为未经稀释的 Flubber 是高度易燃的——也需要足够的 Flubber——因为 Flubber 部门可不能没了 Flubber！你想出了一个公式来衡量最终混合物的价值：$F^a⋅W^{1-a}$，其中 $F$ 是以升每秒为单位的 Flubber 的流入速率，$W$ 是以升每秒为单位的水的流入速率，$a$ 是一个给定的介于 0 和 1 之间的常数。

求出 $F^a⋅W^{1−a}$ 能达到的最大值以及如何安排 Flubber 和水的路径来达到它。

## 样例 #1

### 输入

```
6 6 3.0 0.66
2 4 8
4 6 1
3 6 1
4 5 5
1 5 7
3 5 3
```

### 输出

```
0.000000000 1.360000000
0.000000000 1.000000000
0.000000000 -1.000000000
0.000000000 0.360000000
0.880000000 0.000000000
-0.880000000 -0.360000000
1.02037965897
```

## 样例 #2

### 输入

```
5 5 1.0 0.5
1 2 10
2 3 10
3 4 10
4 5 10
3 5 10
```

### 输出

```
5 0
5 5
4.2 3.14159
4.2 3.14159
-4.2 -3.14159
5
```

# 题解

## 作者：岸芷汀兰 (赞：7)

# 一、题目：

[洛谷原题](https://www.luogu.com.cn/problem/P6938)

[codeforces原题](https://codeforces.com/gym/101471)

# 二、思路：

这道题整整让我调了一个下午！一直被精度卡，后来把所有的精度全部取消就 A 了！

现在让我们来系统梳理一下这道题的思路。

首先可以看出，题目中的参数 $v$ 纯粹是迷惑人的。我们完全可以将 $v\times f$ 看成一个新流。最终求出来答案再除以 $v^a$ 即可。

我们试想这样一种情况：新建一个超级源点 $\mathfrak{s}$，从 $\mathfrak{s}$ 分别向 1、2 号点连容量是无穷大的边，设从 $\mathfrak{s}$ 向 3 号点跑最大流得到的答案是 $Z$。那么一定有 $F+W=Z$。

最终的答案设成一个函数 $f(F)=F^a(Z-F)^{1-a}$，对该函数求导，得
$$
\begin{aligned}
f'(F)&=aF^{a-1}(Z-F)^{1-a}-F^a(1-a)(Z-F)^{-a}\\
&=F^a(Z-F)^{-a}\left(\dfrac{a(Z-F)}{F}-1+a\right)\\
&=F^a(Z-F)^{-a}\dfrac{aZ-F}{F}
\end{aligned}
$$
则当 $F<aZ$ 时，$f'(F)>0$；当 $F>aZ$ 时，$f'(F)<0$。所以当 $F=aZ$ 时，$f(F)$ 有极大值。

但是接下来有两个问题亟待我们去解决。

第一个问题是我们可能无法让 $F$ 达到 $aZ$。设从 1 号点向 3 号点跑最大流的答案是 $F_{\max}$，从 2 号点向 3 号点跑最大流的答案是 $W_{\max}$。那么，$F$ 的范围（或者可以理解为定义域）为 $[Z-W_{\max},F_{\max}]$。所以我们只需要在 $F$ 的定义域找见距离 $aZ$ 最近的值即可。设该值为 $F^*$，$W^*=Z-F^*$。

第二个问题是，有可能 $F^*$ 所对应的流和 $W^*$ 所对应的流叠加在一起时，会造成同一根水管会有不同方向的两条流。但是，我们可以构造出一种满足题意的流。

1. 从 $\mathfrak{s}$ 向 1 号点连容量为 $F^*$ 的边，向 2 号点连容量是 $W^*$ 的边。再从 $\mathfrak{s}$ 向 3 号点跑最大流。
2. 新建一张图 $G$，新图边的方向为旧图中最大流的流向，容量为旧图中最大流的流量。
3. 从新图的超级源点 $\mathfrak{s}$ 向 1 号点连容量为 $F^*$ 的边，再从 $\mathfrak{s}$ 向 3 号点跑最大流。此时每条边的流量就是 Flubber 的最终答案，每条边的容量减流量就是 water 的最终答案。

显然，由于新图的每条边的流量守恒，**容量也守恒**，所以 water 的流量也是守恒的。而且 Flubber 的流量一定是 $F^*$，water 的流量一定是 $W^*$。

# 三、代码：

```cpp
#include <iostream> // 不要设任何的eps！
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;
#define FILEIN(s) freopen(s, "r", stdin)
#define FILEOUT(s) freopen(s, "w", stdout)
#define mem(s, v) memset(s, v, sizeof s)

inline int read(void) {
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
    return f * x;
}

const int MAXN = 205, MAXM = MAXN * MAXN;
const double INF = 1e9;

int n, m, head[MAXN], tot = 1, S, T;
int q[MAXN], cur[MAXN], d[MAXN];
int dir[MAXM];
double Fmax, Wmax, Z, F$, W$, ans, v, a;

struct Edge {
    int y, next;
    double w;
    Edge() {}
    Edge(int _y, int _next, double _w) : y(_y), next(_next), w(_w) {}
}e[MAXM];

inline void add(int x, int y, double w) {
    e[++ tot] = Edge(y, head[x], w);
    head[x] = tot;
}

inline void connect(int x, int y, double w) {
    add(x, y, w); add(y, x, w);
}

bool bfs(void) {
    int hh = 0, tt = -1;
    q[++ tt] = S; cur[S] = head[S];
    mem(d, -1); d[S] = 0;
    while (hh <= tt) {
        int x = q[hh ++];
        for (int i = head[x]; i; i = e[i].next) {
            int y = e[i].y;
            if (e[i].w > 0 && d[y] == -1) {
                d[y] = d[x] + 1;
                cur[y] = head[y];
                if (y == T) return true;
                q[++ tt] = y;
            }
        }
    }
    return false;
}

double find(int x, double limit) {
    if (x == T) return limit;
    double flow = 0;
    for (int i = cur[x]; i && flow < limit; i = e[i].next) {
        cur[x] = i;
        int y = e[i].y;
        if (e[i].w > 0 && d[y] == d[x] + 1) {
            double t = find(y, min(e[i].w, limit - flow));
            if (t == 0) d[y] = -1;
            e[i].w -= t; e[i ^ 1].w += t; flow += t;
        }
    }
    return flow;
}

double dinic(void) {
    double r = 0, flow;
    while (bfs()) {
        if ((flow = find(S, INF)) > 0) r += flow;
    }
    return r;
}

inline void restore(void) {
    for (int i = 2; i <= tot; i += 2) {
        double mid = (e[i].w + e[i ^ 1].w) / 2.0;
        e[i].w = e[i ^ 1].w = mid;
    }
}

int main() {
    n = read(); m = read(); scanf("%lf%lf", &v, &a);
    for (int i = 1; i <= m; ++ i) {
        int x = read(), y = read();
        double w; scanf("%lf", &w);
        connect(x, y, w);
    }
    S = 1; T = 3;
    Fmax = dinic(); restore();

    S = 2;
    Wmax = dinic(); restore();

    S = n + 1; connect(S, 1, INF); connect(S, 2, INF);
    Z = dinic(); restore();

    if (Z - Wmax > a * Z) F$ = Z - Wmax;
    else if (Fmax < a * Z) F$ = Fmax;
    else F$ = a * Z;
    W$ = Z - F$;

    ans = pow(F$, a) * pow(W$, 1 - a);
    ans /= pow(v, a);

    for (int i = head[n + 1]; i; i = e[i].next) {
        int y = e[i].y;
        if (y == 1) e[i].w = F$, e[i ^ 1].w = 0;
        else e[i].w = W$, e[i ^ 1].w = 0;
    }
    dinic();

    for (int i = 2; i <= tot; i += 2) {
        double mid = (e[i].w + e[i ^ 1].w) / 2;
        if (e[i ^ 1].w > mid) { dir[i] = 1; e[i].w = e[i ^ 1].w - mid; e[i ^ 1].w = 0; }
        else { dir[i] = -1; e[i ^ 1].w = e[i].w - mid; e[i].w = 0; }
    }
    for (int i = head[n + 1]; i; i = e[i].next) {
        int y = e[i].y;
        if (y == 1) { e[i].w = F$; e[i ^ 1].w = 0; }
        else e[i].w = e[i ^ 1].w = 0;
    }

    S = n + 1;
    dinic();
    tot -= 4;
    for (int i = 2; i <= tot; i += 2) {
        if (dir[i] == 1)
            printf("%.8lf %.8lf\n", e[i ^ 1].w / v, e[i].w);
        else
            printf("-%.8lf -%.8lf\n", e[i].w / v, e[i ^ 1].w);

    }
    printf("%.8lf\n", ans);
    return 0;
}
```



---

## 作者：FutaRimeWoawaSete (赞：1)

精通人性的谜语人男讲师只讲了一下求最大流的正确性还有什么乱七八糟的东西就讲完了，反正就是讲不完一道题了属于是，毕竟题目很简单是吧，流汗。           

我们首先去掉 $v$ 系数，丢进表达式中化一下简就可以发现是常数，所以直接设为 $1$ 最后算答案时除掉就好了。

这样就具有一个网络流模型的雏形了。

首先最大流的正确性其实还是挺关键的，可以通过反证法后分类讨论证明：显然想让原式表达式的值越大那么肯定两个正数越大越好是吧，那么不是最大流就是说残留网络上还存在至少一条增广路。         

对任意一条增广路进行讨论：           

- 没有反向边的增广路，此时直接流过去显然会让原表达式值更大；

- 有反向边的增广路但全是水的反向边，这个显然也直接流；

- 有反向边并且该增广路上有 Flubber 的反向边，这时我们注意到，如果要继续往下增广得到的路径可能会有 Flubber 和水对冲的情况，但是事实上在扔掉系数 $v$ 之后这两者的路径是可以互换的，进而这条增广路可以实现，个人印象中网络流的基础证明里面是有运用这个套路的。               

那么只要残留网络上存在一条增广路原式的值就不可能是最大的。         

通过建立超级源点 $S$，对 $1$ 和 $2$ 连容量无穷的边，容易求得原图最大流 $Z$。

接着我们考虑找到了最大流 $Z$ 后可以怎样求解原问题。           

由于 $F + W = Z$。对于原式，~~手动三分~~发现当 $F = aZ$ 时原式可以取得最大值，而且函数应该长成一个单峰的样子。                

我们不妨对于全图找到光是 Flubber 跑或水跑可以得到的最大流，记其为 $Fmax,Wmax$，那么显然 $F \in [Wmax - Fmax,Fmax]$ 并且由于流的值是实数，对于这个区间中的任何一个数 $F$ 都能取到，之后分类讨论一下该区间在单峰函数上的位置情况后可以得到实际的 $F'$ 的取值，~~经典高一数学题~~。                   

再之后为了构造出来一组不对冲的方案，我们重新对网络流建模来构造方案：       
- 重新建原图，然后把 $(S,1)$ 的容量改为单向的 $F'$，把 $(S,2)$ 的容量改为单向的 $W'$；

- 跑一遍最大流，标记残留网络上每条边在一组最大流上的方向，原图中每条边的容量重新设定为在跑完最大流时该边的流量，这么做是为了分配这个流量给水和 Flubber。（若没读懂请反复理解）

- 最后将 $(S , 1)$ 的容量改为单向的 $F'$，将 $(S,2)$ 的容量改为 $0$，重新跑一遍最大流后每条边的流量即是 Flubber 的流量，而容量减去流量就是水的流量，毕竟两者的流量相加总的容量。            

最后输出的时候可能会有一些 $-0.0$ 之类的情况可能要手判一下，不清楚spj 可不可以判这个。

---

