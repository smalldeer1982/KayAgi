# 题目信息

# Special Grid

## 题目描述

You are given an $ n×m $ grid, some of its nodes are black, the others are white. Moreover, it's not an ordinary grid — each unit square of the grid has painted diagonals.

The figure below is an example of such grid of size $ 3×5 $ . Four nodes of this grid are black, the other $ 11 $ nodes are white.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF435D/2a129804a620070f064ad9f06e8026399abd5ad7.png)Your task is to count the number of such triangles on the given grid that:

- the corners match the white nodes, and the area is positive;
- all sides go along the grid lines (horizontal, vertical or diagonal);
- no side contains black nodes.

## 说明/提示

The figure below shows red and blue triangles. They are the examples of the required triangles in the first sample. One of the invalid triangles is painted green. It is invalid because not all sides go along the grid lines.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF435D/f9604961f586e4f0664ffd8ad99709dfacd15973.png)

## 样例 #1

### 输入

```
3 5
10000
10010
00001
```

### 输出

```
20
```

## 样例 #2

### 输入

```
2 2
00
00
```

### 输出

```
4
```

## 样例 #3

### 输入

```
2 2
11
11
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# 特殊网格

## 题目描述
给定一个 $n×m$ 的网格，其中一些节点为黑色，其余为白色。此外，这不是一个普通的网格，网格的每个单位正方形都绘制了对角线。

下图是一个大小为 $3×5$ 的此类网格示例。该网格中有四个节点为黑色，其他 $11$ 个节点为白色。

![示例网格](https://cdn.luogu.com.cn/upload/vjudge_pic/CF435D/2a129804a620070f064ad9f06e8026399abd5ad7.png)

你的任务是计算满足以下条件的三角形数量：
- 三角形的顶点为白色节点，且面积为正；
- 所有边都沿着网格线（水平、垂直或对角线）；
- 任何一条边都不包含黑色节点。

## 说明/提示
下图展示了红色和蓝色三角形。它们是第一个示例中所需三角形的示例。其中一个无效三角形被涂成绿色。它无效是因为并非所有边都沿着网格线。

![示例三角形](https://cdn.luogu.com.cn/upload/vjudge_pic/CF435D/f9604961f586e4f0664ffd8ad99709dfacd15973.png)

## 样例 #1
### 输入
```
3 5
10000
10010
00001
```
### 输出
```
20
```

## 样例 #2
### 输入
```
2 2
00
00
```
### 输出
```
4
```

## 样例 #3
### 输入
```
2 2
11
11
```
### 输出
```
0
```

### 算法分类
动态规划

### 综合分析与结论
该题解利用动态规划思想解决问题。通过定义三维数组 `f[i][j][k]` 记录点 `(i, j)` 向方向 `k` 符合要求的最长延伸长度，先在 $O(n^3)$ 时间内求出该数组。然后枚举直角顶点，利用已求出的 `f` 数组判断斜边上是否有黑点，从而累加符合要求的三角形数量。整体思路清晰，利用动态规划减少重复计算，是解决本题的有效方法。

### 所选的题解
 - **星级**：4星
 - **关键亮点**：巧妙利用动态规划定义状态，通过预处理最长延伸长度，简化后续三角形判断过程。
 - **重点代码核心实现思想**：首先通过三重循环初始化 `f` 数组，记录每个点向不同方向的最长延伸长度。然后通过四重循环枚举直角顶点和不同方向，判断斜边上是否有黑点以及另一条直角边是否满足延伸要求，满足则累加答案。
```cpp
// 计算 f 数组
for(int i=1;i<=n;++i)
    for(int j=1;j<=m;++j)
        for(int k=0;k<4;++k)
        {
            int x=i,y=j;
            while(x>0&&x<=n&&y>0&&y<=m&&a[x][y]==0)x+=dx[k],y+=dy[k];
            f[i][j][k]=(i-x!=0?i-x:j-y);
        }
// 枚举直角顶点计算答案
for(int i=1;i<=n;++i)
    for(int j=1;j<=m;++j)if(a[i][j]==0)
        for(int k=0;k<8;++k)
        {
            int l=(k+2)%8,w=(k+3)%4;
            for(int t=1;t<min(n,m);++t)
            {
                int xp=i+t*dx[k],yp=j+t*dy[k],xq=i+t*dx[l],yq=j+t*dy[l];
                if(xp<=0||xp>n||yp<=0||yp>m||xq<=0||xq>n||yq<=0||yq>m)break;
                if(a[xp][yp]==1||a[xq][yq]==1)break;
                if(k>=1&&k<=4)
                {
                    if((dx[w]==0||f[xq][yq][w]>(xp-xq)/dx[w])&&(dy[w]==0||f[xq][yq][w]>(yp-yq)/dy[w]))
                        ans++;
                }else
                {
                    if((dx[w]==0||f[xp][yp][w]>(xq-xp)/dx[w])&&(dy[w]==0||f[xp][yp][w]>(yq-yp)/dy[w]))
                        ans++;
                }
            }
        }
```

### 最优关键思路或技巧
利用动态规划的思想，通过预处理每个点向不同方向的最长延伸长度，将复杂的三角形判断问题转化为对数组的简单查询和比较，有效降低了时间复杂度。

### 可拓展之处
同类型题目通常围绕网格上的图形计数或路径问题，结合网格的特性（如节点颜色限制、边的方向限制等），运用动态规划思想来解决。类似的算法套路是通过合理定义状态数组，记录网格中每个点的某些属性，然后通过状态转移方程来更新数组，最后利用数组信息解决问题。

### 推荐洛谷题目
 - [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：也是在网格上的路径计数问题，可通过动态规划解决。
 - [P1216 数字三角形](https://www.luogu.com.cn/problem/P1216)：经典的动态规划题目，在三角形网格上进行数值计算。
 - [P1048 采药](https://www.luogu.com.cn/problem/P1048)：虽然不是网格问题，但动态规划的思想类似，通过状态转移来解决资源分配问题。 

---
处理用时：56.29秒