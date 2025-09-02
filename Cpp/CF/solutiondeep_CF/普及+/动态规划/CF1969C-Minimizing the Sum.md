# 题目信息

# Minimizing the Sum

## 题目描述

You are given an integer array $ a $ of length $ n $ .

You can perform the following operation: choose an element of the array and replace it with any of its neighbor's value.

For example, if $ a=[3, 1, 2] $ , you can get one of the arrays $ [3, 3, 2] $ , $ [3, 2, 2] $ and $ [1, 1, 2] $ using one operation, but not $ [2, 1, 2 $ \] or $ [3, 4, 2] $ .

Your task is to calculate the minimum possible total sum of the array if you can perform the aforementioned operation at most $ k $ times.

## 说明/提示

In the first example, one of the possible sequences of operations is the following: $ [3, 1, 2] \rightarrow [1, 1, 2 $ \].

In the second example, you do not need to apply the operation.

In the third example, one of the possible sequences of operations is the following: $ [2, 2, 1, 3] \rightarrow [2, 1, 1, 3] \rightarrow [2, 1, 1, 1] $ .

In the fourth example, one of the possible sequences of operations is the following: $ [4, 1, 2, 2, 4, 3] \rightarrow [1, 1, 2, 2, 4, 3] \rightarrow [1, 1, 1, 2, 4, 3] \rightarrow [1, 1, 1, 2, 2, 3] $ .

## 样例 #1

### 输入

```
4
3 1
3 1 2
1 3
5
4 2
2 2 1 3
6 3
4 1 2 2 4 3```

### 输出

```
4
5
5
10```

# AI分析结果

### 题目重写
**最小化数组和**

#### 题目描述
给定一个长度为 $n$ 的整数数组 $a$。

你可以进行以下操作：选择数组中的一个元素，并将其替换为任意一个相邻元素的值。

例如，若 $a=[3, 1, 2]$，你可以通过一次操作得到数组 $[3, 3, 2]$、$[3, 2, 2]$ 或 $[1, 1, 2]$，但不能得到 $[2, 1, 2]$ 或 $[3, 4, 2]$。

你的任务是计算在最多进行 $k$ 次操作后，数组的最小可能总和。

#### 说明/提示
在第一个样例中，一种可能的操作序列是：$[3, 1, 2] \rightarrow [1, 1, 2]$。

在第二个样例中，你不需要进行操作。

在第三个样例中，一种可能的操作序列是：$[2, 2, 1, 3] \rightarrow [2, 1, 1, 3] \rightarrow [2, 1, 1, 1]$。

在第四个样例中，一种可能的操作序列是：$[4, 1, 2, 2, 4, 3] \rightarrow [1, 1, 2, 2, 4, 3] \rightarrow [1, 1, 1, 2, 4, 3] \rightarrow [1, 1, 1, 2, 2, 3]$。

#### 样例 #1
##### 输入
```
4
3 1
3 1 2
1 3
5
4 2
2 2 1 3
6 3
4 1 2 2 4 3
```

##### 输出
```
4
5
5
10
```

### 题解分析与结论
本题的核心是通过动态规划（DP）来解决，利用贪心思想优化状态转移。难点在于如何设计状态转移方程，以及如何高效地计算区间最小值。

#### 最优关键思路
1. **状态定义**：设 $f_{i,j}$ 表示前 $i$ 个元素进行 $j$ 次操作后的最小和。
2. **状态转移**：枚举操作次数 $t$，将区间 $[i-t, i]$ 内的元素替换为该区间的最小值，并更新 $f_{i,j}$。
3. **优化**：通过滚动数组或预处理区间最小值，将时间复杂度优化到 $O(nk^2)$。

#### 推荐题解
1. **作者：Herman526 (5星)**
   - **关键亮点**：清晰的状态定义与转移方程，优化了区间最小值的计算，代码简洁高效。
   - **代码核心**：
     ```cpp
     for(int i=0;i^n;++i){
         scanf("%d",a+i),g=a[i],m=f[i];
         for(int j=k;~j;m[j--]=1e15);
         for(int j=0;j<=k&&j<=i;g=std::min(g,(long long)a[i-++j])){
             if(w=g*(j+1),i==j)m[i]=w;
             for(int p=i^j?j:i+1;p<=k&&p<=i;++p)m[p]=std::min(m[p],f[i-j-1][p-j]+w);
         }
     }
     ```

2. **作者：破壁人罗辑 (4星)**
   - **关键亮点**：详细的状态转移方程解释，预处理区间最小值，代码结构清晰。
   - **代码核心**：
     ```cpp
     for(int j=1;j<=k;j++)for(int i=1;i+j<=n;i++)p[i][j]=min(p[i][j-1],(long long)a[i+j]);
     for(int j=1;j<=k;j++)for(int i=1;i+j<=n;i++)p[i][j]*=(j+1);
     ```

3. **作者：Jerrycyx (4星)**
   - **关键亮点**：通过计算可减去的最大值来间接求解最小和，思路独特，代码实现清晰。
   - **代码核心**：
     ```cpp
     for(int l=1;j-l>=1&&i-l>=0;l++){
         mina=min(mina,(long long)a[j-l]);
         f[j][i]=max(f[j][i],f[j-l-1][i-l]+getsum(j-l,j)-mina*(l+1));
     }
     ```

### 扩展思路
- **类似题目**：区间最小值问题、动态规划优化问题。
- **推荐题目**：
  1. [P1880 石子合并](https://www.luogu.com.cn/problem/P1880)
  2. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)
  3. [P1063 能量项链](https://www.luogu.com.cn/problem/P1063)

### 个人心得
- **调试经历**：在实现过程中，注意数组越界问题，特别是在处理边界条件时。
- **顿悟感想**：通过贪心思想优化状态转移，可以显著减少计算量，提高算法效率。

---
处理用时：40.58秒