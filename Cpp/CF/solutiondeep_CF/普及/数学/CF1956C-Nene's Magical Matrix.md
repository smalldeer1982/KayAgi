# 题目信息

# Nene's Magical Matrix

## 题目描述

The magical girl Nene has an $ n\times n $ matrix $ a $ filled with zeroes. The $ j $ -th element of the $ i $ -th row of matrix $ a $ is denoted as $ a_{i, j} $ .

She can perform operations of the following two types with this matrix:

- Type $ 1 $ operation: choose an integer $ i $ between $ 1 $ and $ n $ and a permutation $ p_1, p_2, \ldots, p_n $ of integers from $ 1 $ to $ n $ . Assign $ a_{i, j}:=p_j $ for all $ 1 \le j \le n $ simultaneously.
- Type $ 2 $ operation: choose an integer $ i $ between $ 1 $ and $ n $ and a permutation $ p_1, p_2, \ldots, p_n $ of integers from $ 1 $ to $ n $ . Assign $ a_{j, i}:=p_j $ for all $ 1 \le j \le n $ simultaneously.

Nene wants to maximize the sum of all the numbers in the matrix $ \sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}a_{i,j} $ . She asks you to find the way to perform the operations so that this sum is maximized. As she doesn't want to make too many operations, you should provide a solution with no more than $ 2n $ operations.

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, the maximum sum $ s=1 $ can be obtained in $ 1 $ operation by setting $ a_{1, 1}:=1 $ .

In the second test case, the maximum sum $ s=7 $ can be obtained in $ 3 $ operations as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1956C/3b20fbb55df6b6d6328669ffd917221602db721d.png)It can be shown that it is impossible to make the sum of the numbers in the matrix larger than $ 7 $ .

## 样例 #1

### 输入

```
2
1
2```

### 输出

```
1 1
1 1 1
7 3
1 1 1 2
1 2 1 2
2 1 1 2```

# AI分析结果

### 题目重写

**Nene的魔法矩阵**

**题目描述**

魔法少女Nene有一个大小为$n \times n$的矩阵$a$，初始时所有元素都为0。矩阵$a$的第$i$行第$j$列的元素记为$a_{i,j}$。

她可以对矩阵进行以下两种操作：

- **类型1操作**：选择一个整数$i$（$1 \le i \le n$）和一个$1$到$n$的排列$p_1, p_2, \ldots, p_n$，然后将矩阵的第$i$行的所有元素$a_{i,j}$赋值为$p_j$（$1 \le j \le n$）。
- **类型2操作**：选择一个整数$i$（$1 \le i \le n$）和一个$1$到$n$的排列$p_1, p_2, \ldots, p_n$，然后将矩阵的第$i$列的所有元素$a_{j,i}$赋值为$p_j$（$1 \le j \le n$）。

Nene希望通过不超过$2n$次操作，使得矩阵中所有元素的和$\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}a_{i,j}$最大化。请你帮助她找到一种操作方案，使得这个和最大。

**说明/提示**

在第一个测试用例中，最大和$s=1$可以通过1次操作得到，即将$a_{1,1}$赋值为1。

在第二个测试用例中，最大和$s=7$可以通过3次操作得到，如下所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1956C/3b20fbb55df6b6d6328669ffd917221602db721d.png)

可以证明，无法使矩阵中所有元素的和大于7。

**样例 #1**

**输入**

```
2
1
2
```

**输出**

```
1 1
1 1 1
7 3
1 1 1 2
1 2 1 2
2 1 1 2
```

### 题解分析与结论

#### 综合分析与结论

本题的核心是通过不超过$2n$次操作，使得矩阵中所有元素的和最大化。通过分析，最优的矩阵形式是每一行和每一列的元素从左上角开始逐渐增加，最终形成一个类似于“阶梯”的结构。具体来说，矩阵的第$i$行和第$i$列的元素最大值为$i$，且每个数$i$出现的次数为$2i-1$。

大多数题解都采用了类似的思路：从矩阵的右下角开始，依次对每一行和每一列进行操作，使用$1$到$n$的排列进行填充。这样，每次操作都会覆盖之前的操作，最终形成一个阶梯状的矩阵。

#### 评分较高的题解

**题解1：Day_Tao (4星)**

- **关键亮点**：通过逆向思维，从矩阵的右下角开始操作，逐步覆盖左上角的元素，最终形成一个阶梯状的矩阵。代码实现清晰，操作顺序合理。
- **代码核心**：
  ```cpp
  for (int i = n; i >= 1; i--) {
      printf("1 %lld ", i);
      for (int j = 1; j <= n; j++) printf("%lld ", j);
      printf("\n");
      printf("2 %lld ", i);
      for (int j = 1; j <= n; j++) printf("%lld ", j);
      printf("\n");
  }
  ```

**题解2：w9095 (4星)**

- **关键亮点**：通过从外圈到内圈交替进行行和列的操作，确保每次操作都能最大化当前圈的元素和。代码简洁，操作顺序合理。
- **代码核心**：
  ```cpp
  for(int i = n; i >= 1; i--) {
      op[++cnt] = 1, p[cnt] = i;
      op[++cnt] = 2, p[cnt] = i;
      for(int j = 1; j <= n; j++) s[i][j] = j, s[j][i] = j;
  }
  ```

**题解3：zxh923 (4星)**

- **关键亮点**：通过构造一个矩阵使得$a_{i,j} = \max(i,j)$，并证明这是最优的方案。代码实现简洁，操作顺序合理。
- **代码核心**：
  ```cpp
  for(int i = (n << 1); i; i--) {
      if(i & 1) cout << "1 ";
      else cout << "2 ";
      cout << ((i + 1) >> 1) << ' ';
      for(int j = 1; j <= n; j++) cout << j << ' ';
      cout << '\n';
  }
  ```

### 最优关键思路或技巧

1. **逆向思维**：从矩阵的右下角开始操作，逐步覆盖左上角的元素，确保每次操作都能最大化当前圈的元素和。
2. **交替操作**：交替进行行和列的操作，确保每次操作都能覆盖之前的操作，最终形成一个阶梯状的矩阵。
3. **贪心策略**：每次操作都选择当前最大的数进行填充，确保每个数$i$出现的次数为$2i-1$。

### 可拓展之处

- **类似问题**：类似的问题可以通过逆向思维和贪心策略来解决，例如在矩阵中填充不同的数，使得某些条件最大化或最小化。
- **其他应用**：这种逆向思维和贪心策略也可以应用于其他类型的矩阵操作问题，例如矩阵旋转、矩阵覆盖等。

### 推荐题目

1. [P1004 方格取数](https://www.luogu.com.cn/problem/P1004)
2. [P1005 矩阵取数游戏](https://www.luogu.com.cn/problem/P1005)
3. [P1006 传纸条](https://www.luogu.com.cn/problem/P1006)

---
处理用时：51.89秒