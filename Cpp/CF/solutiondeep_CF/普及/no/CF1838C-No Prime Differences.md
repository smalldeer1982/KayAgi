# 题目信息

# No Prime Differences

## 题目描述

You are given integers $ n $ and $ m $ . Fill an $ n $ by $ m $ grid with the integers $ 1 $ through $ n\cdot m $ , in such a way that for any two adjacent cells in the grid, the absolute difference of the values in those cells is not a prime number. Two cells in the grid are considered adjacent if they share a side.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1838C/8c9e5187d31f46fda0ceb06874a7a38c27ed3eed.png)It can be shown that under the given constraints, there is always a solution.

## 说明/提示

The first sample case corresponds to the picture above. The only absolute differences between adjacent elements in this grid are $ 1 $ , $ 4 $ , $ 6 $ , $ 8 $ , and $ 9 $ , none of which are prime.

## 样例 #1

### 输入

```
3
4 4
5 7
6 4```

### 输出

```
16  7  1  9
12  8  2  3
13  4 10 11
14  5  6 15

29 23 17  9  5  6  2
33 27 21 15 11  7  1
32 31 25 19 20 16 10
26 30 24 18 14  8  4
35 34 28 22 13 12  3

 2  3  7 11
 8  9  1 10
17 13  5  4
18 14  6 12
19 23 15 21
20 24 16 22```

# AI分析结果

### 题目内容重写
# No Prime Differences

## 题目描述

给定两个整数 $n$ 和 $m$，请填充一个 $n \times m$ 的网格，填入 $1$ 到 $n \cdot m$ 的整数，使得网格中任意两个相邻的单元格中的数值的绝对差不是质数。两个单元格相邻的定义是它们共享一条边。

可以证明，在给定的约束条件下，总是存在一个解。

## 说明/提示

第一个样例对应上图。该网格中相邻元素的绝对差仅为 $1$、$4$、$6$、$8$ 和 $9$，它们都不是质数。

## 样例 #1

### 输入

```
3
4 4
5 7
6 4
```

### 输出

```
16  7  1  9
12  8  2  3
13  4 10 11
14  5  6 15

29 23 17  9  5  6  2
33 27 21 15 11  7  1
32 31 25 19 20 16 10
26 30 24 18 14  8  4
35 34 28 22 13 12  3

 2  3  7 11
 8  9  1 10
17 13  5  4
18 14  6 12
19 23 15 21
20 24 16 22
```

### 算法分类
构造

### 题解分析与结论
本题的核心是通过构造一个矩阵，使得相邻单元格的差值不为质数。多个题解都采用了类似的思路，即通过调整矩阵的行或列的顺序，使得相邻单元格的差值变为非质数。以下是各题解的要点对比：

1. **lovely_codecat** 和 **copper_ingot** 的题解都提出了将矩阵的奇数行和偶数行分别输出，使得纵向差为 $2m$，从而避免质数差值。两者的思路基本相同，但 **copper_ingot** 的代码更为简洁，且考虑了 $n$ 为奇数时的特殊情况。
   
2. **analysis** 和 **c20231020** 的题解则进一步分类讨论了 $m$ 为偶数、$n$ 为偶数以及 $n$ 和 $m$ 均为奇数的情况，并给出了相应的构造方法。**c20231020** 的题解更为详细，且提供了循环移位的构造方法，适用于 $n$ 和 $m$ 均为奇数的情况。

3. **mouseboy** 的题解思路较为简单，直接通过调整行间距为 $2$ 来避免质数差值，但未考虑 $n$ 为奇数时的特殊情况，代码实现也较为简单。

### 评分较高的题解
1. **copper_ingot** (4星)
   - 关键亮点：代码简洁，考虑了 $n$ 为奇数时的特殊情况，思路清晰。
   - 核心代码：
     ```cpp
     for (int i = 1; i <= n / 2; i++){
         for (int j = 1; j <= m; j++) printf("%d ", (2 * i - 1) * m + j);
         puts("");
     }
     for (int i = 1; i <= (n + 1) / 2; i++){
         for (int j = 1; j <= m; j++) printf("%d ", (2 * i - 2) * m + j);
         puts("");
     }
     ```

2. **c20231020** (4星)
   - 关键亮点：详细分类讨论，提供了循环移位的构造方法，适用于 $n$ 和 $m$ 均为奇数的情况。
   - 核心代码：
     ```cpp
     int now = m;
     For(i, 1, n){
         for(int j = now % m + 1;; j = j % m + 1){
             a[i][j] = ++t;
             if(j == now) break;
         }
         now--;
     }
     ```

### 最优关键思路
通过调整矩阵的行或列的顺序，使得相邻单元格的差值变为非质数。具体来说，可以通过将奇数行和偶数行分别输出，或者通过循环移位的方式，确保差值不为质数。

### 拓展思路
类似的问题可以通过构造矩阵或调整顺序来满足特定条件。例如，构造一个矩阵使得相邻单元格的差值为特定范围内的数，或者满足其他数学性质。

### 推荐题目
1. [P1008 三连击](https://www.luogu.com.cn/problem/P1008)
2. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
3. [P1014 Cantor表](https://www.luogu.com.cn/problem/P1014)

这些题目都涉及到构造或排列问题，与本题的构造思路有相似之处。

---
处理用时：32.41秒