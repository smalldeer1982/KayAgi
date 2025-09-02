# 题目信息

# Maximize the Intersections

## 题目描述

On a circle lie $ 2n $ distinct points, with the following property: however you choose $ 3 $ chords that connect $ 3 $ disjoint pairs of points, no point strictly inside the circle belongs to all $ 3 $ chords. The points are numbered $ 1, \, 2, \, \dots, \, 2n $ in clockwise order.

Initially, $ k $ chords connect $ k $ pairs of points, in such a way that all the $ 2k $ endpoints of these chords are distinct.

You want to draw $ n - k $ additional chords that connect the remaining $ 2(n - k) $ points (each point must be an endpoint of exactly one chord).

In the end, let $ x $ be the total number of intersections among all $ n $ chords. Compute the maximum value that $ x $ can attain if you choose the $ n - k $ chords optimally.

Note that the exact position of the $ 2n $ points is not relevant, as long as the property stated in the first paragraph holds.

## 说明/提示

In the first test case, there are three ways to draw the $ 2 $ additional chords, shown below (black chords are the ones initially drawn, while red chords are the new ones):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1552C/704c17cd22decf087937d97766096b41bea230a2.png)We see that the third way gives the maximum number of intersections, namely $ 4 $ .

In the second test case, there are no more chords to draw. Of course, with only one chord present there are no intersections.

In the third test case, we can make at most one intersection by drawing chords $ 1-3 $ and $ 2-4 $ , as shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1552C/abc82045666e4296b48f8b98db9ad5de10f98734.png)

## 样例 #1

### 输入

```
4
4 2
8 2
1 5
1 1
2 1
2 0
10 6
14 6
2 20
9 10
13 18
15 12
11 7```

### 输出

```
4
0
1
14```

# AI分析结果

### 题目翻译
# 最大化交点数量

## 题目描述
在一个圆上有 $2n$ 个不同的点，具有以下性质：无论你如何选择 $3$ 条连接 $3$ 对不相交点的弦，圆内没有一个点严格属于所有 $3$ 条弦。这些点按顺时针顺序编号为 $1, 2, \cdots, 2n$。

最初，有 $k$ 条弦连接了 $k$ 对点，使得这些弦的所有 $2k$ 个端点都不同。

你想要绘制 $n - k$ 条额外的弦，连接剩下的 $2(n - k)$ 个点（每个点必须恰好是一条弦的端点）。

最后，设 $x$ 为所有 $n$ 条弦的交点总数。如果你以最优方式选择 $n - k$ 条弦，计算 $x$ 能达到的最大值。

请注意，只要第一段中所述的性质成立，$2n$ 个点的确切位置并不重要。

## 说明/提示
在第一个测试用例中，有三种绘制 $2$ 条额外弦的方法，如下所示（黑色弦是最初绘制的，红色弦是新绘制的）：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1552C/704c17cd22decf087937d97766096b41bea230a2.png)
我们可以看到，第三种方法给出了最大的交点数，即 $4$。

在第二个测试用例中，没有更多的弦需要绘制。当然，只有一条弦时没有交点。

在第三个测试用例中，我们可以通过绘制弦 $1 - 3$ 和 $2 - 4$ 最多得到一个交点，如下所示：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1552C/abc82045666e4296b48f8b98db9ad5de10f98734.png)

## 样例 #1
### 输入
```
4
4 2
8 2
1 5
1 1
2 1
2 0
10 6
14 6
2 20
9 10
13 18
15 12
11 7
```

### 输出
```
4
0
1
14
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是先找出未连接的点，然后采用特定的连边方式（通常是将点 $i$ 与 $i + n - k$ 相连）来最大化弦之间的交点数，最后通过枚举所有弦对来统计交点总数。
- **思路对比**：大部分题解都从 $k = 0$ 的特殊情况入手，推导出一般情况的连边策略，即让新连的弦尽可能多地相交。
- **算法要点**：关键在于找到一种最优的连边方式，使得新连的弦之间以及新连弦与已有弦之间的交点数最大。通常采用的方法是将未连接的点依次编号，然后将 $i$ 与 $i + n - k$ 相连。
- **解决难点**：证明这种连边方式的最优性是关键难点。不同题解通过分类讨论、画图等方式进行了证明。

### 所选题解
- **zhongqijun（5星）**：
    - **关键亮点**：思路清晰，从特殊情况逐步推导到一般情况，对结论的证明较为详细，代码可读性高。
- **AmamiyaYuuko（4星）**：
    - **关键亮点**：对连边方式的最优性进行了分类讨论证明，代码实现简洁明了。
- **Cure_Wing（4星）**：
    - **关键亮点**：修正了数学公式，对思路的阐述较为清晰，代码规范。

### 重点代码
#### zhongqijun 的核心代码
```cpp
for(int i = 1;i <= (cnt/2);i ++)
{
    p[k+i][0] = a[i];
    p[k+i][1] = a[i+(cnt/2)];
}
for(int i = 1;i <= k;i ++)
    for(int j = i+1;j <= n;j ++)
        if((p[i][0] < p[j][0] && p[j][0] < p[i][1] && p[i][1] < p[j][1]) || (p[j][0] < p[i][0] && p[i][0] < p[j][1] && p[j][1] < p[i][1]))
            ans ++;
for(int i = 1;i < (cnt/2);i ++) ans += i;
```
**核心实现思想**：先将未连接的点按顺序两两配对，然后枚举所有弦对，判断是否相交并统计交点数，最后加上新连弦之间的交点数。

#### AmamiyaYuuko 的核心代码
```cpp
for (int i = 0; i < n - k; ++i)    g.push_back((Node){v[i], v[i + n - k]});
for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
        ans += check(g[i], g[j]);
    }
}
```
**核心实现思想**：将未连接的点按顺序两两配对加入弦的数组，然后枚举所有弦对，调用 `check` 函数判断是否相交并统计交点数。

#### Cure_Wing 的核心代码
```cpp
for(int i=1;i<=m/2;++i){p[++k][0]=r[i];p[k][1]=r[i+m/2];}
for(int i=1;i<=k;++i)
    for(int j=1;j<=k;++j)
        ans+=p[i][0]<p[j][0]&&p[j][0]<p[i][1]&&p[i][1]<p[j][1];
```
**核心实现思想**：将未连接的点按顺序两两配对，然后枚举所有弦对，判断是否相交并统计交点数。

### 拓展思路
同类型题或类似算法套路通常涉及几何图形中的构造问题，例如在多边形中连接顶点以最大化某些几何量（如面积、交点数等）。解题关键在于找到一种合理的构造方式，并证明其最优性。

### 推荐题目
1. [P1886 滑动窗口 /【模板】单调队列](https://www.luogu.com.cn/problem/P1886)
2. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

### 个人心得
题解中未包含个人心得。

---
处理用时：45.15秒