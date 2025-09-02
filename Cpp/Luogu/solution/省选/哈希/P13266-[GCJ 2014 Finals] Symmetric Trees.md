# [GCJ 2014 Finals] Symmetric Trees

## 题目描述

给定一棵**顶点有颜色**的树，判断它能否在二维平面中绘制成具有**对称轴**的图形。

更正式地说，一棵树被称为“轴对称”的，当且仅当存在一种顶点在二维平面中的坐标分配方式，使得：

- 所有顶点的坐标都互不相同；
- 如果某个顶点 $\mathbf{v}_i$ 的颜色为 $\mathbf{C}$，坐标为 $(x_i, y_i)$，那么必须存在另一个顶点 $\mathbf{v}_i'$，其颜色也为 $\mathbf{C}$，坐标为 $(-x_i, y_i)$。特别注意：如果 $x_i = 0$，那么 $\mathbf{v}_i$ 自身就是它的对称点；
- 对于任意一条边 $(\mathbf{v}_i, \mathbf{v}_j)$，也必须存在一条边 $(\mathbf{v}_i', \mathbf{v}_j')$；
- 如果我们将边绘制为直线段，则任意两条边**只能在公共端点处重合**，不能在其他地方相交。

现在请你判断，给定的每棵树是否满足上述“轴对称”条件。


## 说明/提示

**样例解释**

第一个样例可以按照如下方式绘制，满足对称轴条件：

![](https://cdn.luogu.com.cn/upload/image_hosting/ithqougs.png)

第二个样例无法找到任何符合对称要求的排列方式：

![](https://cdn.luogu.com.cn/upload/image_hosting/0kmct7ap.png)

第三个样例中，有一种绘制方式满足关于一条垂直对称轴的对称关系：

![](https://cdn.luogu.com.cn/upload/image_hosting/9yzlvp9q.png)

## 限制条件

- $1 \leq T \leq 100$

### Small 数据集（7 分）

- 时间限制：~~60~~ 3 秒
- $2 \leq N \leq 12$

### Large 数据集（18 分）

- 时间限制：~~120~~ 5 秒
- $2 \leq N \leq 10000$

## 样例 #1

### 输入

```
3
4
R
G
B
B
1 2
2 3
2 4
4
R
G
B
Y
1 2
2 3
2 4
12
Y
B
Y
G
R
G
Y
Y
B
B
B
R
1 3
1 9
1 10
2 3
3 7
3 8
3 11
4 8
5 7
6 7
8 12```

### 输出

```
Case #1: SYMMETRIC
Case #2: NOT SYMMETRIC
Case #3: SYMMETRIC```

