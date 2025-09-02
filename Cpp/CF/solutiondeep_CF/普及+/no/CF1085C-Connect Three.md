# 题目信息

# Connect Three

## 题目描述

The Squareland national forest is divided into equal $ 1 \times 1 $ square plots aligned with north-south and east-west directions. Each plot can be uniquely described by integer Cartesian coordinates $ (x, y) $ of its south-west corner.

Three friends, Alice, Bob, and Charlie are going to buy three distinct plots of land $ A, B, C $ in the forest. Initially, all plots in the forest (including the plots $ A, B, C $ ) are covered by trees. The friends want to visit each other, so they want to clean some of the plots from trees. After cleaning, one should be able to reach any of the plots $ A, B, C $ from any other one of those by moving through adjacent cleared plots. Two plots are adjacent if they share a side.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1085C/cf5d536458708f86bac89ca28316f7ecb522f107.png)For example, $ A=(0,0) $ , $ B=(1,1) $ , $ C=(2,2) $ . The minimal number of plots to be cleared is $ 5 $ . One of the ways to do it is shown with the gray color.Of course, the friends don't want to strain too much. Help them find out the smallest number of plots they need to clean from trees.

## 说明/提示

The first example is shown on the picture in the legend.

The second example is illustrated with the following image:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1085C/bd6dd616034b12c36a0bd287e4e6a207ec125259.png)

## 样例 #1

### 输入

```
0 0
1 1
2 2
```

### 输出

```
5
0 0
1 0
1 1
1 2
2 2
```

## 样例 #2

### 输入

```
0 0
2 0
1 1
```

### 输出

```
4
0 0
1 0
1 1
2 0
```

# AI分析结果

### 题目内容
# 连接三点

## 题目描述
Squareland国家森林被划分为大小相等的$1×1$正方形地块，这些地块与南北和东西方向对齐。每个地块都可以通过其西南角的整数笛卡尔坐标$(x, y)$ 进行唯一描述。

三位朋友爱丽丝、鲍勃和查理打算在森林中购买三块不同的地块$A$、$B$、$C$。最初，森林中的所有地块（包括地块$A$、$B$、$C$）都被树木覆盖。朋友们希望能够互相拜访，所以他们想要清理一些地块上的树木。清理后，应该能够通过相邻的已清理地块从$A$、$B$、$C$中的任何一块到达另外任何一块。如果两块地共享一条边，则它们是相邻的。

例如，$A=(0,0)$ ，$B=(1,1)$ ，$C=(2,2)$ 。需要清理的地块的最小数量是$5$。其中一种清理方式用灰色表示。当然，朋友们不想太累。帮助他们找出需要清理树木的最小地块数量。

## 说明/提示
第一个示例如题目图例所示。
第二个示例如下图所示：

## 样例 #1
### 输入
```
0 0
1 1
2 2
```
### 输出
```
5
0 0
1 0
1 1
1 2
2 2
```
## 样例 #2
### 输入
```
0 0
2 0
1 1
```
### 输出
```
4
0 0
1 0
1 1
2 0
```

### 算法分类
构造

### 题解综合分析与结论
- **思路方面**：各题解都基于通过构造最短路径来连接三个点，从而确定最少需要清理的地块数量及路径上的点。
- **算法要点**：SuperBeetle题解通过以$y$轴排序，以排序后第二个点为标准遍历行来计算清理地块数；zym20249_提出以$x$或$y$轴排序，以另一个为标准遍历计算；shiroi将三个点按$x$排序，过中间点作竖线，其他两点向其作垂线构造路径；little_sun将$3$个点按$x$坐标排序，枚举$A$->$B$和$B$->$C$各两种曼哈顿距离路径取最小值。
- **解决难点**：难点在于如何找到一种通用且最优的路径构造方式，避免复杂的分类讨论。各题解通过不同的排序和构造策略来解决，其中shiroi的方法相对简洁直观，直接通过排序和作垂线避免了较多讨论。

### 所选的题解
- **作者：shiroi (5星)**
  - **关键亮点**：通过观察发现将三个点按$x$排序，过中间的点作一条竖线后其他两点向其做垂线即为最短路径，此方法最优且能避免复杂的路径分类讨论，代码实现简洁清晰。
  - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read()
{
    int x=0,f=1,c=getchar();
    while(c<48) c=='-'&&(f=-1),c=getchar();
    while(c>47) x=x*10+c-'0',c=getchar();
    return x*f;
}

const int MAXN = 15;
struct Point {int x,y;} p[MAXN];
std::set<pair<int,int> > s;

bool operator <(Point a,Point b)
{return a.x>b.x;}

int main(int argc, char const *argv[])
{
    for(int i=1; i<=3; ++i)
        p[i].x=read(),p[i].y=read();
    sort(p+1,p+4);
    int maxy=max(max(p[1].y,p[2].y),p[3].y);
    int miny=min(min(p[1].y,p[2].y),p[3].y);
    int maxx=max(max(p[1].x,p[2].x),p[3].x);
    int minx=min(min(p[1].x,p[2].x),p[3].x);
    for(int i=miny; i<=maxy; i++)
        s.insert(make_pair(p[2].x,i));
    for(int i=minx; i<=p[2].x; i++)
        s.insert(make_pair(i,p[3].y));
    for(int i=p[2].x; i<=maxx; i++)
        s.insert(make_pair(i,p[1].y));
    printf("%d\n", maxx+maxy-minx-miny+1);
    for(pair<int,int> x : s)
        printf("%d %d\n", x.first,x.second);
    return 0;
}
```
  - **核心实现思想**：先读入三个点坐标，按$x$坐标排序。通过遍历确定路径上的点并插入集合，最后输出集合中点的数量和具体坐标。

### 最优关键思路或技巧
通过对三个点按某一维度（如$x$轴）排序，利用中间点作为基准构造垂线来形成最短连通路径，这种方法简化了路径构造过程，避免了复杂的情况分析。

### 可拓展之处
此类题目属于在网格图上构造特定路径的问题，类似套路可应用于其他网格图上求点与点之间最小连通代价等问题。例如，给定多个点，要求用最短路径连接所有点，可考虑类似的排序和构造策略。

### 洛谷相似题目推荐
- [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：在棋盘上求从起点到终点的路径数，涉及网格图路径问题。
- [P1269 邮递员送信](https://www.luogu.com.cn/problem/P1269)：在有向图（类似网格图拓展）上求最短路径，可类比本题构造路径思路。
- [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)：在网格图上根据规则探索路径，与本题在网格图上进行路径相关操作类似。 

---
处理用时：41.29秒