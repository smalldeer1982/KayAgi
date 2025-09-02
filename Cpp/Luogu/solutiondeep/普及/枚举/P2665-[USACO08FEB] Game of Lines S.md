# 题目信息

# [USACO08FEB] Game of Lines S

## 题目背景

Farmer John 最近发明了一个游戏，来考验自命不凡的贝茜。


## 题目描述

Farmer John has challenged Bessie to the following game: FJ has a board with dots marked at N (2 ≤ N ≤ 200) distinct lattice points. Dot i has the integer coordinates Xi and Yi (-1,000 ≤ Xi ≤ 1,000; -1,000 ≤ Yi ≤ 1,000).

Bessie can score a point in the game by picking two of the dots and drawing a straight line between them; however, she is not allowed to draw a line if she has already drawn another line that is parallel to that line. Bessie would like to know her chances of winning, so she has asked you to help find the maximum score she can obtain.

游戏开始的时 候，FJ 会给贝茜一块画着 $N (2 \le N \le 200)$ 个不重合的点的木板，其中第 $i$ 个点的横、纵坐标分别为 $X_i$ 和 $Y_i (-1000 \le X_i \le 1000, -1000 \le Y_i \le 1000)$。

贝茜可以选两个点画一条过它们的直线，当且仅当平面上不存在与画出直线 平行的直线。游戏结束时贝茜的得分，就是她画出的直线的总条数。为了在游戏中胜出，贝茜找到了你，希望你帮她计算一下最大可能得分。


## 说明/提示

贝茜能画出以下 $4$ 种斜率的直线：$-1$，$0$，$\dfrac{1}{3}$ 以及 $1$。

## 样例 #1

### 输入

```
4 
-1 1 
-2 0 
0 0 
1 1```

### 输出

```
4 ```

# AI分析结果

### 综合分析与结论
这些题解的核心思路都是通过计算给定的 \(N\) 个点中两两连线的斜率，然后统计不同斜率的数量来得到答案。主要区别在于判重和存储斜率的方式。
1. **算法要点**：
    - **计算斜率**：使用公式 \(k = \frac{y_i - y_j}{x_i - x_j}\) 计算斜率，同时要特判 \(x_i = x_j\) 的情况（此时直线与 \(y\) 轴平行）。
    - **判重**：通过排序后比较相邻元素（如大头题解）、使用 `map` （如hmh13951417981和YosemiteHe题解）、`set` （如planche、YuJieSong和嘟嘟cqy题解）、二维hash（如taoran题解）等方式进行判重。
2. **解决难点**：
    - **斜率计算的边界情况**：即 \(x\) 坐标相同导致除数为零的情况，大部分题解通过给这种特殊情况赋一个特殊值（如10000、999999、`inf` 等）来处理。
    - **判重**：选择合适的数据结构来高效地判重不同的斜率值。

### 通用建议与扩展思路
1. **关键思路或技巧**：
    - **数据结构选择**：在处理需要判重的情况时，`map` 和 `set` 是非常方便的C++ 数据结构，它们可以自动处理判重问题，提高代码效率和简洁性。
    - **边界条件处理**：对于可能出现的除数为零等边界条件，要进行合理的特判，避免程序出错。
2. **拓展**：
    - **同类型题**：此类题目通常围绕几何图形中的点、线关系，通过计算斜率、距离等几何属性，并结合判重、计数等操作来求解。类似算法套路还可应用于判断多边形是否为凸多边形（通过判断相邻边斜率变化）等问题。
3. **洛谷相似题目**：
    - **P1039 [NOIP2003 提高组] 侦探推理**：通过枚举和逻辑判断来解决问题，考察对复杂条件的处理和判重。
    - **P1131 奇数国**：涉及到对数据的处理和判重，与本题在数据处理思路上有相似之处。
    - **P1306 斐波那契公约数**：需要通过推导数学性质，结合数据处理和判重，与本题在思维方式上有一定相似性。
4. **个人心得摘录与总结**：
    - **Hiraeth**：强调了斜率不存在（除0）情况的特判以及整型计算浮点型要乘1.0的要点，避免因数据类型问题导致结果错误。 

---
处理用时：12.68秒