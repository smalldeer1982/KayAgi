# [GCJ 2019 #3] Napkin Folding

## 题目描述

Chalk 一直在和朋友们积极地环游世界，在最酷的地方拍照。最近，他来到了欧洲，研究了[餐巾折叠](https://en.wikipedia.org/wiki/Napkin_folding)的历史。从那以后，Chalk 就开始收集各种各样的餐巾来练习餐巾折叠艺术。

Chalk 的餐巾可以被定义为[简单多边形](https://en.wikipedia.org/wiki/Simple_polygon)。简单多边形是指没有边相交（除了相邻边在公共顶点处相交）的多边形。多边形的每个顶点都恰好属于两条边。

Chalk 折叠餐巾时，首先会在餐巾上画出*折叠图案*。折叠图案是一组 $\mathbf{K}-1$ 条线段，这些线段画在定义餐巾的多边形上。每条线段连接多边形边界上的两个有理数坐标点，并且完全位于多边形内部。折叠图案中的任意两条线段不能相交或重叠，除了可能在公共端点处。包含 $\mathbf{K}-1$ 条线段的折叠图案会将餐巾分成 $\mathbf{K}$ 个多边形区域。如果存在一条连续的路径（不一定是直线），连接两个点且不与多边形的任何边或折叠图案中的任何线段（即使是端点）相交，则这两个点属于同一区域。

Chalk 只对*整齐的折叠图案*感兴趣。折叠图案是*整齐*的，当且仅当与同一折叠线段 $F$ 相邻的任意两个区域关于 $F$ 对称。这意味着，如果沿着该线段折叠餐巾，这两个区域会完全重合。

下图展示了一个包含 $\mathbf{K}=8$ 个区域的整齐折叠图案。

![](https://cdn.luogu.com.cn/upload/image_hosting/ta6vzkcp.png)

Chalk 已经用整齐的折叠图案成功折叠了他的大部分餐巾。但他收藏中还有一些餐巾，始终找不到整齐的折叠图案。对于这些餐巾中的每一块，Chalk 需要你的帮助，找出一个包含 $\mathbf{K}$ 个区域的整齐折叠图案，或者判断不存在这样的整齐折叠图案。

## 说明/提示

**样例解释**

注意：样例 2 不适用于测试集 1。只有样例 1 会在运行测试集 1 前被测试（与通常的样例测试方式一致）。此外，样例 2 不会在运行测试集 2 前被测试。

对于样例 1，$\mathbf{K}=2$ 时，可以用任意一条虚线画出整齐的折叠图案：

![](https://cdn.luogu.com.cn/upload/image_hosting/bm3282e7.png)

对于样例 2，$\mathbf{K}=2$ 时，可以如下画出整齐的折叠图案：

![](https://cdn.luogu.com.cn/upload/image_hosting/hvx1riz3.png)

对于样例 3，没有整齐的折叠图案：

![](https://cdn.luogu.com.cn/upload/image_hosting/adkogxsq.png)

对于样例 4，存在两种可能的整齐折叠图案，$\mathbf{K}=2$：

![](https://cdn.luogu.com.cn/upload/image_hosting/j4v71qhu.png)

对于测试集 2 的样例，$\mathbf{K}=8$ 时，可以如下画出整齐的折叠图案：

![](https://cdn.luogu.com.cn/upload/image_hosting/vqrcukau.png)

**数据范围**

- $1 \leq \mathbf{T} \leq 100$。
- $3 \leq \mathbf{N} \leq 200$。
- $1 \leq \mathbf{X}_{\mathbf{i}} \leq 1000$，对所有 $\mathbf{i}$。
- $1 \leq \mathbf{Y}_{\mathbf{i}} \leq 1000$，对所有 $\mathbf{i}$。
- 所有 $\mathbf{N}$ 个点按顺时针顺序给出。
- 多边形任意两条相邻边不共线。
- 多边形为简单多边形，面积严格大于零。
- 除了相邻边在公共端点处外，多边形任意两条边不相交。

**测试集 1（4 分，公开）**

- $\mathbf{K}=2$。

**测试集 2（39 分，隐藏）**

- $2 \leq \mathbf{K} \leq 10$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
4 2
1 1
1 2
2 2
2 1
3 2
1 1
1 2
2 1
8 2
1 3
3 5
5 5
4 4
7 3
5 1
4 2
3 1
8 2
1 3
3 5
4 4
5 5
7 3
5 1
4 2
3 1```

### 输出

```
Case #1: POSSIBLE
1/1 2/1 2/1 1/1
Case #2: POSSIBLE
1/1 1/1 3/2 3/2
Case #3: IMPOSSIBLE
Case #4: POSSIBLE
1/1 3/1 7/1 3/1```

## 样例 #2

### 输入

```
1
10 8
4 1
3 1
2 2
2 3
1 3
1 4
2 4
3 3
3 2
4 2```

### 输出

```
Case #1: POSSIBLE
3/1 1/1 4/1 2/1
3/1 1/1 3/1 2/1
2/1 2/1 3/1 2/1
2/1 2/1 3/1 3/1
2/1 3/1 3/1 3/1
2/1 3/1 2/1 4/1
1/1 3/1 2/1 4/1```

