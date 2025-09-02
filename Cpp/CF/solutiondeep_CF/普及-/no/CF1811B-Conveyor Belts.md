# 题目信息

# Conveyor Belts

## 题目描述

Conveyor matrix $ m_n $ is matrix of size $ n \times n $ , where $ n $ is an even number. The matrix consists of concentric ribbons moving clockwise.

In other words, the conveyor matrix for $ n = 2 $ is simply a matrix $ 2 \times 2 $ , whose cells form a cycle of length $ 4 $ clockwise. For any natural $ k \ge 2 $ , the matrix $ m_{2k} $ is obtained by adding to the matrix $ m_{2k - 2} $ an outer layer forming a clockwise cycle.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1811B/9983d2b36278ac1465bae7e881cd16110c58e71c.png) The conveyor matrix $ 8 \times 8 $ . You are standing in a cell with coordinates $ x_1, y_1 $ and you want to get into a cell with coordinates $ x_2, y_2 $ . A cell has coordinates $ x, y $ if it is located at the intersection of the $ x $ th row and the $ y $ th column.

Standing on some cell, every second you will move to the cell next in the direction of movement of the tape on which you are. You can also move to a neighboring cell by spending one unit of energy. Movements happen instantly and you can make an unlimited number of them at any time.

Your task is to find the minimum amount of energy that will have to be spent to get from the cell with coordinates $ x_1, y_1 $ to the cell with coordinates $ x_2, y_2 $ .

For example, $ n=8 $ initially you are in a cell with coordinates $ 1,3 $ and you want to get into a cell with coordinates $ 6, 4 $ . You can immediately make $ 2 $ movements, once you are in a cell with coordinates $ 3, 3 $ , and then after $ 8 $ seconds you will be in the right cell.

## 样例 #1

### 输入

```
5
2 1 1 2 2
4 1 4 3 3
8 1 3 4 6
100 10 20 50 100
1000000000 123456789 987654321 998244353 500000004```

### 输出

```
0
1
2
9
10590032```

# AI分析结果

### 题目内容
# 传送带

## 题目描述
传送带矩阵 $m_n$ 是一个 $n \times n$ 的矩阵，其中 $n$ 是偶数。该矩阵由同心带状区域组成，这些带状区域按顺时针方向移动。

换句话说，当 $n = 2$ 时，传送带矩阵就是一个 $2 \times 2$ 的矩阵，其单元格形成一个长度为 $4$ 的顺时针循环。对于任何自然数 $k \geq 2$，矩阵 $m_{2k}$ 是通过在矩阵 $m_{2k - 2}$ 的基础上添加一个外层，该外层形成一个顺时针循环得到的。

![8×8 的传送带矩阵](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1811B/9983d2b36278ac1465bae7e881cd16110c58e71c.png) 这是一个 $8 \times 8$ 的传送带矩阵。你站在坐标为 $x_1, y_1$ 的单元格中，想要到达坐标为 $x_2, y_2$ 的单元格。如果一个单元格位于第 $x$ 行和第 $y$ 列的交叉处，则它的坐标为 $x, y$。

站在某个单元格上，每秒你将沿着所在传送带的移动方向移动到下一个单元格。你也可以花费一个单位的能量移动到相邻单元格。移动是瞬间完成的，并且你可以在任何时候进行无限次移动。

你的任务是找到从坐标为 $x_1, y_1$ 的单元格到达坐标为 $x_2, y_2$ 的单元格所需花费的最小能量。

例如，当 $n = 8$ 时，最初你在坐标为 $1, 3$ 的单元格中，想要到达坐标为 $6, 4$ 的单元格。你可以立即进行 $2$ 次移动，当你到达坐标为 $3, 3$ 的单元格后，再过 $8$ 秒你将到达目标单元格。

## 样例 #1
### 输入
```
5
2 1 1 2 2
4 1 4 3 3
8 1 3 4 6
100 10 20 50 100
1000000000 123456789 987654321 998244353 500000004
```
### 输出
```
0
1
2
9
10590032
```

### 算法分类
数学

### 题解综合分析与结论
三道题解思路一致，都指出答案是两个点所在层数差的绝对值，关键在于求出点所在层数。难点在于理解传送带矩阵结构，明确相邻两层可通过一次移动到达。

### 所选的题解
 - **作者：abensyl (5星)**
    - **关键亮点**：思路清晰，不仅阐述核心思路，还给出完整简洁代码，代码中对输入坐标做了优化处理，减少计算量。
    - **个人心得**：无
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int TT;
  cin >> TT;
  while (TT--) {
    int n, a, c, b, d;
    cin >> n >> a >> c >> b >> d;
    n /= 2;
    if (a > n) a = n * 2 - a + 1;
    if (b > n) b = n * 2 - b + 1;
    if (c > n) c = n * 2 - c + 1;
    if (d > n) d = n * 2 - d + 1;
    int ca = min(a, c), cb = min(b, d);
    cout << abs(ca - cb) << '\n';
  }
  return 0;
}
```
核心实现思想：先读入数据，将 $n$ 减半，对超出 $n/2$ 的坐标进行转换，使其在 $[1, n/2]$ 范围内，然后分别取两点横纵坐标较小值，最后输出两点对应值差的绝对值。

 - **作者：sto_5k_orz (4星)**
    - **关键亮点**：简洁明了指出思路，给出计算层数的函数，逻辑清晰。
    - **个人心得**：无
    - **重点代码**：
```cpp
int dis(int n, int x, int y) {
	return min(min(x, y), min(n - x + 1, n - y + 1));
}
```
核心实现思想：通过取 $x$、$y$、$n - x + 1$、$n - y + 1$ 的最小值，得到点 $(x, y)$ 所在层数。

 - **作者：aimcf (4星)**
    - **关键亮点**：从传送带编号角度阐述思路，与其他题解本质相同但角度新颖。
    - **个人心得**：无
    - **重点代码**：无（未给出具体代码实现）

### 最优关键思路或技巧
通过观察矩阵结构，发现相邻两层可一次移动到达，将问题转化为求两点所在层数差。计算点所在层数时，利用点到四边距离的最小值这一特性。

### 可拓展思路
此类题目关键在于理解特殊矩阵结构与移动规则，类似题目通常围绕特殊矩阵中的移动、路径、距离等问题展开，可通过分析结构特点，找到关键属性（如本题的层数）来解决。

### 洛谷相似题目推荐
 - [P1046 陶陶摘苹果](https://www.luogu.com.cn/problem/P1046)
 - [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)
 - [P1116 车厢重组](https://www.luogu.com.cn/problem/P1116)

---
处理用时：38.40秒