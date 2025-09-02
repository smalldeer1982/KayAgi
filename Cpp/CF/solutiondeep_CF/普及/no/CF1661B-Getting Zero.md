# 题目信息

# Getting Zero

## 题目描述

Suppose you have an integer $ v $ . In one operation, you can:

- either set $ v = (v + 1) \bmod 32768 $
- or set $ v = (2 \cdot v) \bmod 32768 $ .

You are given $ n $ integers $ a_1, a_2, \dots, a_n $ . What is the minimum number of operations you need to make each $ a_i $ equal to $ 0 $ ?

## 说明/提示

Let's consider each $ a_i $ :

- $ a_1 = 19 $ . You can, firstly, increase it by one to get $ 20 $ and then multiply it by two $ 13 $ times. You'll get $ 0 $ in $ 1 + 13 = 14 $ steps.
- $ a_2 = 32764 $ . You can increase it by one $ 4 $ times: $ 32764 \rightarrow 32765 \rightarrow 32766 \rightarrow 32767 \rightarrow 0 $ .
- $ a_3 = 10240 $ . You can multiply it by two $ 4 $ times: $ 10240 \rightarrow 20480 \rightarrow 8192 \rightarrow 16384 \rightarrow 0 $ .
- $ a_4 = 49 $ . You can multiply it by two $ 15 $ times.

## 样例 #1

### 输入

```
4
19 32764 10240 49```

### 输出

```
14 4 4 15```

# AI分析结果

### 题目重写
#### 题目描述
假设你有一个整数 $v$。在每次操作中，你可以选择以下两种操作之一：
- 将 $v$ 设置为 $(v + 1) \bmod 32768$
- 将 $v$ 设置为 $(2 \cdot v) \bmod 32768$

给定 $n$ 个整数 $a_1, a_2, \dots, a_n$，你需要将每个 $a_i$ 变为 $0$。求每个 $a_i$ 变为 $0$ 所需的最少操作次数。

#### 说明/提示
考虑每个 $a_i$：
- $a_1 = 19$。你可以先将其加 1 得到 20，然后将其乘以 2 共 13 次，最终得到 0。总共需要 $1 + 13 = 14$ 步。
- $a_2 = 32764$。你可以将其加 1 共 4 次：$32764 \rightarrow 32765 \rightarrow 32766 \rightarrow 32767 \rightarrow 0$。
- $a_3 = 10240$。你可以将其乘以 2 共 4 次：$10240 \rightarrow 20480 \rightarrow 8192 \rightarrow 16384 \rightarrow 0$。
- $a_4 = 49$。你可以将其乘以 2 共 15 次。

#### 样例输入
```
4
19 32764 10240 49
```

#### 样例输出
```
14 4 4 15
```

### 算法分类
**广度优先搜索 BFS**

### 题解分析与结论
本题的核心是通过两种操作将给定的整数 $v$ 变为 $0$，且操作次数最少。由于 $32768 = 2^{15}$，问题的本质是通过加法和乘法操作使得 $v$ 的二进制表示中后 15 位都为 0。

#### 题解对比
1. **Exber 的题解**：采用贪心策略，通过枚举加法次数和计算左移次数来求解最小操作数。思路清晰，代码简洁，时间复杂度较低。
2. **Pig_py 的题解**：通过枚举加法和乘法的次数，结合预处理的幂次表来求解。思路较为直接，但代码复杂度较高。
3. **Cappuccino_mjj 的题解**：使用 BFS 进行状态搜索，直接求解最小操作数。思路简单，但时间复杂度较高。

#### 最优题解
**Exber 的题解**（评分：5星）
- **关键亮点**：通过贪心策略，先枚举加法次数，再计算左移次数，时间复杂度为 $O(n \times 15)$，效率较高。
- **代码核心**：
  ```cpp
  inline int calc(int x) {
      int pos = 15;
      for (int i = 0; i <= 15; i++) {
          if (x & (1 << i)) {
              pos = i;
              break;
          }
      }
      return 15 - pos;
  }

  inline void slove() {
      scanf("%d", &n);
      for (int i = 1; i <= n; i++) {
          int x;
          scanf("%d", &x);
          int ans = 1e8;
          for (int j = 0; j <= 15; j++) {
              ans = min(ans, j + calc((x + j) % 32768));
          }
          printf("%d ", ans);
      }
  }
  ```

### 关键思路与技巧
- **贪心策略**：先枚举加法次数，再计算左移次数，确保每次操作都能最大限度地减少 $v$ 的值。
- **位运算优化**：通过位运算快速找到 $v$ 的二进制表示中最右边的 1，从而确定左移次数。

### 拓展与举一反三
- **类似题目**：
  1. [P1008 三连击](https://www.luogu.com.cn/problem/P1008)
  2. [P1010 幂次方](https://www.luogu.com.cn/problem/P1010)
  3. [P1011 进制转换](https://www.luogu.com.cn/problem/P1011)

### 个人心得
- **调试经历**：在枚举加法次数时，需要注意 $v$ 的取值范围，避免溢出或无效操作。
- **顿悟感想**：通过位运算可以快速确定 $v$ 的二进制表示中最右边的 1，从而简化计算过程。

---
处理用时：29.93秒