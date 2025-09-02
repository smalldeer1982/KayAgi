# 题目信息

# Kostya the Sculptor

## 题目描述

Kostya is a genial sculptor, he has an idea: to carve a marble sculpture in the shape of a sphere. Kostya has a friend Zahar who works at a career. Zahar knows about Kostya's idea and wants to present him a rectangular parallelepiped of marble from which he can carve the sphere.

Zahar has $ n $ stones which are rectangular parallelepipeds. The edges sizes of the $ i $ -th of them are $ a_{i} $ , $ b_{i} $ and $ c_{i} $ . He can take no more than two stones and present them to Kostya.

If Zahar takes two stones, he should glue them together on one of the faces in order to get a new piece of rectangular parallelepiped of marble. Thus, it is possible to glue a pair of stones together if and only if two faces on which they are glued together match as rectangles. In such gluing it is allowed to rotate and flip the stones in any way.

Help Zahar choose such a present so that Kostya can carve a sphere of the maximum possible volume and present it to Zahar.

## 说明/提示

In the first example we can connect the pairs of stones:

- $ 2 $ and $ 4 $ , the size of the parallelepiped: $ 3×2×5 $ , the radius of the inscribed sphere $ 1 $
- $ 2 $ and $ 5 $ , the size of the parallelepiped: $ 3×2×8 $ or $ 6×2×4 $ or $ 3×4×4 $ , the radius of the inscribed sphere $ 1 $ , or $ 1 $ , or $ 1.5 $ respectively.
- $ 2 $ and $ 6 $ , the size of the parallelepiped: $ 3×5×4 $ , the radius of the inscribed sphere $ 1.5 $
- $ 4 $ and $ 5 $ , the size of the parallelepiped: $ 3×2×5 $ , the radius of the inscribed sphere $ 1 $
- $ 5 $ and $ 6 $ , the size of the parallelepiped: $ 3×4×5 $ , the radius of the inscribed sphere $ 1.5 $

Or take only one stone:

- $ 1 $ the size of the parallelepiped: $ 5×5×5 $ , the radius of the inscribed sphere $ 2.5 $
- $ 2 $ the size of the parallelepiped: $ 3×2×4 $ , the radius of the inscribed sphere $ 1 $
- $ 3 $ the size of the parallelepiped: $ 1×4×1 $ , the radius of the inscribed sphere $ 0.5 $
- $ 4 $ the size of the parallelepiped: $ 2×1×3 $ , the radius of the inscribed sphere $ 0.5 $
- $ 5 $ the size of the parallelepiped: $ 3×2×4 $ , the radius of the inscribed sphere $ 1 $
- $ 6 $ the size of the parallelepiped: $ 3×3×4 $ , the radius of the inscribed sphere $ 1.5 $

It is most profitable to take only the first stone.

## 样例 #1

### 输入

```
6
5 5 5
3 2 4
1 4 1
2 1 3
3 2 4
3 3 4
```

### 输出

```
1
1
```

## 样例 #2

### 输入

```
7
10 7 8
5 10 3
4 2 6
5 5 5
10 2 8
4 2 1
7 7 7
```

### 输出

```
2
1 5
```

# AI分析结果



# Kostya the Sculptor

## 题目描述

Kostya 是一位天才雕塑家，他有一个想法：雕刻一个球形的大理石雕塑。Kostya 的朋友 Zahar 在采石场工作，知道他的想法后，想送他一个由大理石制成的长方体，让他可以雕刻出最大的球体。

Zahar 有 $n$ 块长方体石块，第 $i$ 块的边长分别为 $a_i$、$b_i$、$c_i$。他最多可以选择两块石块，将它们粘合在一起形成一个新长方体（必须满足粘合面尺寸相同）。

求能雕刻出的球体的最大半径（即新长方体最短边的一半），并输出所选石块的编号。

## 说明/提示

当选择两个石块时，需通过旋转或翻转使粘合面完全匹配。样例说明展示了不同组合的拼接效果，最终最优解可能来自单个石块或两个石块的组合。

---

**算法分类**：贪心

---

## 题解分析与结论

### 核心思路
1. **单个石块**：球体半径由三边的最小值决定。
2. **两个石块**：需找到可拼接的相同面，合并后的最短边为 `min(合并维度, 原两维度)`。
3. **高效处理**：用 `map` 维护每个面（排序后的长宽）对应的最大第三边及编号，实现 O(1) 查询和更新。

### 最优题解亮点

#### 题解作者：sto__Liyhzh__orz（⭐⭐⭐⭐⭐）
- **关键技巧**：预处理每个石块的三边排序，生成三种可能的面存入 `map`，查询时直接计算合并效果。
- **代码亮点**：
  ```cpp
  map<pair<int,int>, pair<int,int>> m;  // 存储面（a,b）对应的最大c和编号
  for (每个石块) {
    sort(a, a+3);
    // 检查三种面组合（a0×a1, a0×a2, a1×a2）
    for (每种面组合) {
      计算合并后的最短边，更新答案
      更新map中的最大c值
    }
  }
  ```

#### 题解作者：CaiXY06（⭐⭐⭐⭐）
- **实现优化**：显式处理三个面组合，代码结构更易读。
- **核心代码**：
  ```cpp
  // 检查三个面组合并更新答案
  f = mp[make_pair(a[0],a[1])];
  temp = min(min(a[0],a[1]), f.first + a[2]);
  ```

#### 题解作者：Yingluosanqian（⭐⭐⭐⭐）
- **循环模式**：通过三次交换维度生成所有面组合，覆盖全部可能。
- **代码片段**：
  ```cpp
  for (int mode=1; mode<=3; mode++) {
    swap(e[0], e[1]); swap(e[1], e[2]);
    // 处理当前面组合
  }
  ```

---

## 关键思路总结
1. **预处理排序**：将每个长方体的三边排序，保证 `a≤b≤c`。
2. **面组合哈希**：使用 `map` 存储每个面（排序后的长宽）对应的最大第三边和编号。
3. **动态更新**：遍历每个长方体的三个可能面，查询并更新最优解。

---

## 相似题目推荐
1. [CF455A Boredom](https://codeforces.com/problemset/problem/455/A)（动态规划+频率统计）
2. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)（贪心+维护序列）
3. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)（分治/树状数组）

---
处理用时：85.41秒