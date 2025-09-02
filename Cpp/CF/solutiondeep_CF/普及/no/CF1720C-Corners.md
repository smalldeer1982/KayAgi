# 题目信息

# Corners

## 题目描述

You are given a matrix consisting of $ n $ rows and $ m $ columns. Each cell of this matrix contains $ 0 $ or $ 1 $ .

Let's call a square of size $ 2 \times 2 $ without one corner cell an L-shape figure. In one operation you can take one L-shape figure, with at least one cell containing $ 1 $ and replace all numbers in it with zeroes.

Find the maximum number of operations that you can do with the given matrix.

## 说明/提示

In the first testcase one of the optimal sequences of operations is the following (bold font shows l-shape figure on which operation was performed):

- Matrix before any operation was performed:  101111011110
- Matrix after $ 1 $ operation was performed:  100101011110
- Matrix after $ 2 $ operations were performed:  100100011110
- Matrix after $ 3 $ operations were performed:  100100010110
- Matrix after $ 4 $ operations were performed:  100000010110
- Matrix after $ 5 $ operations were performed:  100000010100
- Matrix after $ 6 $ operations were performed:  100000000100
- Matrix after $ 7 $ operations were performed:  000000000100
- Matrix after $ 8 $ operations were performed:  000000000000

In the third testcase from the sample we can not perform any operation because the matrix doesn't contain any ones.

In the fourth testcase it does not matter which L-shape figure we pick in our first operation. We will always be left with single one. So we will perform $ 2 $ operations.

## 样例 #1

### 输入

```
4
4 3
101
111
011
110
3 4
1110
0111
0111
2 2
00
00
2 2
11
11```

### 输出

```
8
9
0
2```

# AI分析结果

### 题目内容
给定一个由 $n$ 行 $m$ 列组成的矩阵，矩阵中的每个单元格包含 $0$ 或 $1$。定义一个 $2 \times 2$ 的正方形，去掉其中一个角后的形状为 L 形。每次操作可以选择一个至少包含一个 $1$ 的 L 形，并将其中的所有数字替换为 $0$。求在给定的矩阵中，最多可以进行多少次这样的操作。

### 算法分类
贪心

### 题解分析与结论
本题的核心在于如何最大化操作次数，即每次操作尽可能少地消除 $1$。大多数题解都采用了贪心的策略，通过分析矩阵中 $1$ 的分布情况，找到最优的操作顺序。具体来说，题解们主要关注以下几点：

1. **初始状态分析**：如果矩阵中存在两个相邻的 $0$，则可以通过每次操作只消除一个 $1$，从而最大化操作次数。
2. **特殊情况处理**：如果矩阵中没有两个相邻的 $0$，则需要通过第一次操作构造出这样的状态，并根据矩阵中 $0$ 的数量调整操作次数。
3. **全 $1$ 矩阵的处理**：如果矩阵中全是 $1$，则第一次操作必须消除三个 $1$，之后每次操作可以消除一个 $1$。

### 高星题解推荐

#### 题解1：作者：liangbowen (赞：26)
- **星级**：★★★★★
- **关键亮点**：通过枚举每个 $2 \times 2$ 的矩阵，统计其中 $1$ 的数量，并根据 $1$ 的数量决定第一次操作消除的 $1$ 的数量。代码简洁，逻辑清晰。
- **核心代码**：
  ```cpp
  for (int i = 2; i <= n; i++)
      for (int j = 2; j <= m; j++) {
          int cnt = a[i-1][j-1] + a[i-1][j] + a[i][j-1] + a[i][j];
          if (cnt == 0) continue;
          if (cnt == 1) minn = min(minn, 1);
          if (cnt == 2) minn = min(minn, 1);
          if (cnt == 3) minn = min(minn, 2);
          if (cnt == 4) minn = min(minn, 3);
      }
  ```

#### 题解2：作者：E1_de5truct0r (赞：1)
- **星级**：★★★★
- **关键亮点**：通过判断是否存在只包含一个 $1$ 的 L 形，来决定操作次数。如果不存在，则通过第一次操作构造出这样的 L 形。思路清晰，代码简洁。
- **核心代码**：
  ```cpp
  inline bool check(const int &x,const int &y){
      if(x>1 && y>1 && s[x-1][y]+s[x][y]+s[x][y-1]-zer==1) return 1;
      if(x>1 && y<m && s[x-1][y]+s[x][y]+s[x][y+1]-zer==1) return 1;
      if(x<n && y>1 && s[x+1][y]+s[x][y]+s[x][y-1]-zer==1) return 1;
      if(x<n && y>1 && s[x+1][y]+s[x][y]+s[x][y+1]-zer==1) return 1;
      return 0;
  }
  ```

#### 题解3：作者：ztlh (赞：0)
- **星级**：★★★★
- **关键亮点**：通过判断矩阵中是否存在两个相邻的 $0$，来决定操作次数。如果不存在，则根据矩阵中 $0$ 的数量调整操作次数。思路清晰，代码简洁。
- **核心代码**：
  ```cpp
  for(int i=1;i<=n;i++)
      for(int j=1;j<=m;j++){
          if(s[i][j]=='1') continue;
          if(i+1<=n&&s[i+1][j]=='0') flag=1;
          if(j+1<=m&&s[i][j+1]=='0') flag=1;
          if(i+1<=n&&j+1<=m&&s[i+1][j+1]=='0') flag=1;
          if(i+1<=n&&j-1>=1&&s[i+1][j-1]=='0') flag=1;
      }
  ```

### 最优关键思路
1. **贪心策略**：每次操作尽可能少地消除 $1$，从而最大化操作次数。
2. **特殊情况处理**：根据矩阵中 $0$ 的分布情况，调整第一次操作消除的 $1$ 的数量。
3. **枚举与统计**：通过枚举每个 $2 \times 2$ 的矩阵，统计其中 $1$ 的数量，并根据统计结果决定操作次数。

### 可拓展之处
本题的贪心策略可以推广到类似的矩阵操作问题中，尤其是在需要最大化或最小化某种操作次数的场景下。类似的题目可以通过分析矩阵中元素的分布情况，找到最优的操作顺序。

### 推荐题目
1. [P1004 方格取数](https://www.luogu.com.cn/problem/P1004)
2. [P1006 传纸条](https://www.luogu.com.cn/problem/P1006)
3. [P1018 乘积最大](https://www.luogu.com.cn/problem/P1018)

---
处理用时：40.07秒