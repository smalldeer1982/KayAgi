# 题目信息

# Mischievous Shooter

## 题目描述

Once the mischievous and wayward shooter named Shel found himself on a rectangular field of size $ n \times m $ , divided into unit squares. Each cell either contains a target or not.

Shel only had a lucky shotgun with him, with which he can shoot in one of the four directions: right-down, left-down, left-up, or right-up. When fired, the shotgun hits all targets in the chosen direction, the Manhattan distance to which does not exceed a fixed constant $ k $ . The Manhattan distance between two points $ (x_1, y_1) $ and $ (x_2, y_2) $ is equal to $ |x_1 - x_2| + |y_1 - y_2| $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1921G/07ae9ceed185244b94a445086f5cae84fbf84168.png) Possible hit areas for $ k = 3 $ .Shel's goal is to hit as many targets as possible. Please help him find this value.

## 说明/提示

Possible optimal shots for the examples in the statement:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1921G/027b9a5a762b96357d7642f8eac1d4cf8d7ae93a.png)

## 样例 #1

### 输入

```
4
3 3 1
.#.
###
.#.
2 5 3
###..
...##
4 4 2
..##
###.
#..#
####
2 1 3
#
#```

### 输出

```
3
4
5
2```

# AI分析结果



# Mischievous Shooter 中文题面

## 题目描述

顽皮的射手 Shel 发现他身处一个 $n \times m$ 的矩形场地，场地被划分为单位格子。每个格子可能包含目标也可能为空。

Shel 有一把幸运霰弹枪，可以向四个方向之一射击：右下、左下、左上或右上。当射击时，霰弹枪会命中选定方向上所有曼哈顿距离不超过固定常数 $k$ 的目标。两点 $(x_1, y_1)$ 和 $(x_2, y_2)$ 的曼哈顿距离为 $|x_1 - x_2| + |y_1 - y_2|$。

![可能的命中区域示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1921G/07ae9ceed185244b94a445086f5cae84fbf84168.png)（当 $k=3$ 时的命中范围示意图）

请帮助 Shel 计算他最多能击中多少个目标。

## 样例 #1

### 输入

```
4
3 3 1
.#.
###
.#.
2 5 3
###..
...##
4 4 2
..##
###.
#..#
####
2 1 3
#
#```

### 输出

```
3
4
5
2```

---

### 综合题解分析

#### 关键思路总结
1. **方向统一处理**：通过矩阵旋转将四个方向统一转换为同一方向处理，减少代码重复
2. **差分优化**：利用二维差分维护阶梯型区域，在 O(1) 时间完成区间加减操作
3. **滚动维护**：通过行间差分传递，避免重复计算重叠区域
4. **空间优化**：动态调整矩阵尺寸，避免静态数组空间浪费

#### 高分题解推荐

1. **sunkuangzheng（5星）**
   - **亮点**：矩阵旋转+差分优化，时间复杂度严格 O(nm)
   - **技巧**：
     ```cpp
     // 核心差分维护逻辑
     for i from 1 to n:
         for j from 1 to m:
             a[i][j] += a[i-1][j]
             b[i][j] += b[i-1][j+1]
     ```
   - **心得**："旋转后必须重新resize矩阵，否则会访问非法内存"（导致多次WA）

2. **Segment_Treap（4星）**
   - **亮点**：梯形前缀和+方向统一处理
   - **技巧**：
     ```cpp
     // 预处理梯形区域
     for i from 1 to n:
         for j from 1 to m:
             tx1[i][j] = tx1[i-1][min(m,j+1)] + xd1[i][j]
     ```

3. **MaxBlazeResFire（4星）**
   - **亮点**：矩阵转置优化空间，分治处理三角形区域
   - **代码片段**：
     ```cpp
     inline int S(int u,int d,int l,int r) { // 二维前缀和查询
         return a[d][r] - a[d][l-1] - a[u-1][r] + a[u-1][l-1];
     }
     ```

---

### 同类题目推荐
1. [P3406 海底高铁](https://www.luogu.com.cn/problem/P3406) - 差分数组经典应用
2. [P2004 领地选择](https://www.luogu.com.cn/problem/P2004) - 二维前缀和极值
3. [CF1864D Matrix Cascade](https://codeforces.com/problemset/problem/1864/D) - 差分处理三角形区域

---
处理用时：50.19秒