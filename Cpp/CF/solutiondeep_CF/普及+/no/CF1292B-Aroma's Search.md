# 题目信息

# Aroma's Search

## 题目描述

获得了新身体后，我们的偶像 Aroma White（或者应该被称为 Kaori Minamiya？）开始在 OS 空间中寻找她尘封的过去。

这个空间可以看作是一个二维平面，在其内部有着无限多的数据点，从 $0$ 开始标号，它们的坐标定义如下：

- 第 $0$ 个点的坐标为 $(x_0, y_0)$。
- 对于 $i > 0$，第 $i$ 个点的坐标为 $(x_i, y_i) = (a_x \cdot x_{i-1} + b_x, a_y \cdot y_{i-1} + b_y)$。

初始时 Aroma 的位置为 $(x_s, y_s)$。她只能留在 OS 空间中最多 $t$ 秒，因为她还需要传送回真实世界。她不需要返回初始位置 $(x_s, y_s)$ 也能传送回家。

在 OS 空间中，Aroma 可以做如下操作：

- 在点 $(x, y)$ 上时，Aroma 可以移动到这四个点之一：$(x-1, y), (x+1, y), (x, y-1), (x, y+1)$。这个操作需要耗费 $1$ 秒。
- 如果 Aroma 当前的位置上有数据点，她可以收集它。我们可以假定这个操作耗费 $0$ 秒。当然，每个数据点只能被收集一次。

Aroma 想要在传送回去之前，收集尽可能多的数据点。你能帮助她计算在 $t$ 秒内最多能收集的数据点的个数吗？

## 样例 #1

### 输入

```
1 1 2 3 1 0
2 4 20```

### 输出

```
3```

## 样例 #2

### 输入

```
1 1 2 3 1 0
15 27 26```

### 输出

```
2```

## 样例 #3

### 输入

```
1 1 2 3 1 0
2 2 1```

### 输出

```
0```

# AI分析结果

【题目内容】
# Aroma的搜索

## 题目描述

获得了新身体后，我们的偶像Aroma White（或者应该被称为Kaori Minamiya？）开始在OS空间中寻找她尘封的过去。

这个空间可以看作是一个二维平面，在其内部有着无限多的数据点，从0开始标号，它们的坐标定义如下：

- 第0个点的坐标为 $(x_0, y_0)$。
- 对于 $i > 0$，第 $i$ 个点的坐标为 $(x_i, y_i) = (a_x \cdot x_{i - 1} + b_x, a_y \cdot y_{i - 1} + b_y)$。

初始时Aroma的位置为 $(x_s, y_s)$。她只能留在OS空间中最多 $t$ 秒，因为她还需要传送回真实世界。她不需要返回初始位置 $(x_s, y_s)$ 也能传送回家。

在OS空间中，Aroma可以做如下操作：

- 在点 $(x, y)$ 上时，Aroma可以移动到这四个点之一：$(x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1)$。这个操作需要耗费1秒。
- 如果Aroma当前的位置上有数据点，她可以收集它。我们可以假定这个操作耗费0秒。当然，每个数据点只能被收集一次。

Aroma想要在传送回去之前，收集尽可能多的数据点。你能帮助她计算在 $t$ 秒内最多能收集的数据点的个数吗？

## 样例 #1

### 输入

```
1 1 2 3 1 0
2 4 20
```

### 输出

```
3
```

## 样例 #2

### 输入

```
1 1 2 3 1 0
15 27 26
```

### 输出

```
2
```

## 样例 #3

### 输入

```
1 1 2 3 1 0
2 2 1
```

### 输出

```
0
```

【算法分类】
贪心

【综合分析与结论】
这些题解的核心思路都是基于点坐标的增长特性，利用贪心策略来解决问题。由于点坐标呈指数级增长，在有限时间 $t$ 内可到达的点数量有限，因此可以先计算出这些点的坐标。然后，通过枚举起始点，利用贪心原则（先往点更密集的方向收集，即往序号小的点方向，若时间有剩余再往序号大的点方向收集）来计算最多能收集的点的数量。

各题解的主要区别在于代码实现细节和对边界条件的处理方式，但整体思路一致。部分题解对贪心策略的原理进行了详细证明，有助于理解算法的正确性。

【所选题解】
- syksykCCC（5星）
  - 关键亮点：思路清晰，对贪心策略的原理进行了详细的数学证明，代码简洁明了，注释清晰。
  - 个人心得：无
- Tony102（4星）
  - 关键亮点：思路阐述清晰，代码结构良好，对问题的分析较为全面。
  - 个人心得：无
- lytqwq（4星）
  - 关键亮点：代码简洁，对贪心策略的解释通俗易懂。
  - 个人心得：无

【重点代码】
- syksykCCC的核心代码：
```cpp
#include <bits/stdc++.h>
#define max(a, b) a > b ? a : b
typedef long long LL;
const int N = 70;
LL ax, ay, bx, by, ans, n; 
LL x[N], y[N], xs, ys, t;
LL dist(LL x1, LL y1, LL x2, LL y2) { return llabs(x1 - x2) + llabs(y1 - y2); }
int main()
{
    scanf("%lld %lld %lld %lld %lld %lld", x, y, &ax, &ay, &bx, &by);
    scanf("%lld %lld %lld", &xs, &ys, &t);
    while(++n)
    {
        x[n] = ax * x[n - 1] + bx; y[n] = ay * y[n - 1] + by;
        if(x[n] > xs && y[n] > ys && dist(xs, ys, x[n], y[n]) > t) break;
    }
    for(int i = 0; i <= n; i++)
    {
        LL tans = 0, tt = t;
        if(dist(xs, ys, x[i], y[i]) <= tt) tt -= dist(xs, ys, x[i], y[i]), tans++; // S -> Pi 
        else { ans = max(ans, tans); continue; }
        for(int j = i; j; j--) // Pi -> P0
        {
            if(dist(x[j], y[j], x[j - 1], y[j - 1]) <= tt)
                tt -= dist(x[j], y[j], x[j - 1], y[j - 1]), tans++;
            else break;
        }
        for(int j = 1; j <= n; j++) // P0 -> Pi -> P∞
        {
            if(dist(x[j], y[j], x[j - 1], y[j - 1]) <= tt)
                tt -= dist(x[j], y[j], x[j - 1], y[j - 1]), tans += j > i; // 注意 j > i 的时候才能算入 
            else break;
        }
        ans = max(ans, tans);
    }
    printf("%lld\n", ans);
    return 0;
}
```
核心实现思想：先计算出所有可能到达的点的坐标，然后枚举起始点 $i$，从起始点出发，先往序号小的点方向收集，再往序号大的点方向收集，记录每次枚举的最大收集点数。

- Tony102的核心代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

int x0, Y0, ax, ay, bx, by, xs, ys, t;

std::vector < pair < int, int > > a;

inline int read()
{
    char ch = getchar();
    int f = 1, x = 0;
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + ch - '0'; ch = getchar(); }
    return x * f;
}

inline void init()
{
    int xi = x0, yi = Y0, nx = 0, ny = 0;
    a.push_back(make_pair(x0, Y0));
    while (1) {
        nx = ax * xi + bx, ny = ay * yi + by;
        if (abs(nx - x0) > (1e17) || abs(ny - Y0) > (1e17)) break;
        a.push_back(make_pair(nx, ny));
        xi = nx, yi = ny;
    }
}

signed main()
{
    x0 = read(), Y0 = read(), ax = read(), ay = read(), bx = read(), by = read();
    xs = read(), ys = read(), t = read();
    init();
    int ans = 0;
    for (register int i = 0; i < a.size(); ++ i) {
        int tim = llabs(xs - a[i].first) + llabs(ys - a[i].second), cnt = 0;
        if (tim > t) continue;
        ++ cnt;
        int xi = a[i].first, yi = a[i].second;
        if (i > 0) {
            for (register int j = i - 1; j >= 0; -- j) {
                int dis = (llabs(xi - a[j].first) + llabs(yi - a[j].second));
                tim += dis;
                if (tim > t) break;
                ++ cnt;
                xi = a[j].first, yi = a[j].second;
            }
        }
        if (tim >= t) { ans = std::max(ans, cnt); continue; }
        for (register int j = i + 1; j < a.size(); ++ j) {
            int dis = llabs(xi - a[j].first) + llabs(yi - a[j].second);
            tim += dis;
            if (tim > t) break;
            ++ cnt;
            xi = a[j].first, yi = a[j].second;
        }
        ans = std::max(ans, cnt);
    }
    printf("%lld\n", ans);
    return 0;
}
```
核心实现思想：先计算出所有可能到达的点的坐标并存储在向量中，然后枚举起始点，从起始点出发，先往序号小的点方向收集，再往序号大的点方向收集，记录最大收集点数。

- lytqwq的核心代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 101
long long int x[N],y[N],ax,ay,bx,by,xs,ys,T,n,sum,maxn;
int main()
{
    cin>>x[0]>>y[0]>>ax>>ay>>bx>>by>>xs>>ys>>T;
    for(int i=1;;i++)
    {
        x[i]=x[i-1]*ax+bx;
        y[i]=y[i-1]*ay+by;
        if(x[i]>2e16||y[i]>2e16)
        {
            n=i-1;
            break;
        }
    }
    for(int i=0;i<=n;i++)
    {
        long long int sT=T-(abs(xs-x[i])+abs(ys-y[i]));
        if(sT<0)
        {
            continue;
        }
        sum=1;
        maxn=max(maxn,sum);
        for(int o=i-1;o>=0;o--)
        {
            sT-=(abs(x[o+1]-x[o])+abs(y[o+1]-y[o]));
            if(sT<0)
            {
                break;
            }
            sum++;
        }
        sT-=(abs(x[0]-x[i])+abs(y[0]-y[i]));
        if(sT<0)
        {
            maxn=max(maxn,sum);
            continue;
        }
        for(int o=i+1;o<=n;o++)
        {
            sT-=(abs(x[o]-x[o-1])+abs(y[o]-y[o-1]));
            if(sT<0)
            {
                break;
            }
            sum++;
        }
        maxn=max(maxn,sum);
    }
    cout<<maxn<<endl;
}
```
核心实现思想：先计算出所有可能到达的点的坐标，然后枚举起始点，从起始点出发，先往序号小的点方向收集，再往序号大的点方向收集，记录最大收集点数。

【关键思路或技巧】
- **贪心策略**：根据点坐标的增长特性，先往点更密集的方向（序号小的点方向）收集，若时间有剩余再往序号大的点方向收集，能保证在有限时间内收集到最多的点。
- **枚举起始点**：通过枚举所有可能的起始点，找到最大的收集点数。
- **计算点坐标**：利用递推公式计算出所有可能到达的点的坐标，并根据点的范围和时间限制进行剪枝。

【拓展思路】
同类型题或类似算法套路：
- 涉及坐标移动和资源收集的问题，可考虑贪心策略，根据资源的分布特性选择最优的移动路径。
- 对于有递推关系的问题，可先计算出相关数据，再进行枚举和贪心选择。

【推荐题目】
- P1090 [NOIP2004 提高组] 合并果子
- P2240 【深基12.例1】部分背包问题
- P1223 排队接水

---
处理用时：80.37秒