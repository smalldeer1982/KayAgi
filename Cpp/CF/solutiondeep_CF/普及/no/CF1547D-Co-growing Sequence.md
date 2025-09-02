# 题目信息

# Co-growing Sequence

## 题目描述

A sequence of non-negative integers $ a_1, a_2, \dots, a_n $ is called growing if for all $ i $ from $ 1 $ to $ n - 1 $ all ones (of binary representation) in $ a_i $ are in the places of ones (of binary representation) in $ a_{i + 1} $ (in other words, $ a_i \:\&\: a_{i + 1} = a_i $ , where $ \& $ denotes [bitwise AND](http://tiny.cc/xpy9uz)). If $ n = 1 $ then the sequence is considered growing as well.

For example, the following four sequences are growing:

- $ [2, 3, 15, 175] $ — in binary it's $ [10_2, 11_2, 1111_2, 10101111_2] $ ;
- $ [5] $ — in binary it's $ [101_2] $ ;
- $ [1, 3, 7, 15] $ — in binary it's $ [1_2, 11_2, 111_2, 1111_2] $ ;
- $ [0, 0, 0] $ — in binary it's $ [0_2, 0_2, 0_2] $ .

The following three sequences are non-growing:

- $ [3, 4, 5] $ — in binary it's $ [11_2, 100_2, 101_2] $ ;
- $ [5, 4, 3] $ — in binary it's $ [101_2, 100_2, 011_2] $ ;
- $ [1, 2, 4, 8] $ — in binary it's $ [0001_2, 0010_2, 0100_2, 1000_2] $ .

Consider two sequences of non-negative integers $ x_1, x_2, \dots, x_n $ and $ y_1, y_2, \dots, y_n $ . Let's call this pair of sequences co-growing if the sequence $ x_1 \oplus y_1, x_2 \oplus y_2, \dots, x_n \oplus y_n $ is growing where $ \oplus $ denotes [bitwise XOR](http://tiny.cc/bry9uz).

You are given a sequence of integers $ x_1, x_2, \dots, x_n $ . Find the lexicographically minimal sequence $ y_1, y_2, \dots, y_n $ such that sequences $ x_i $ and $ y_i $ are co-growing.

The sequence $ a_1, a_2, \dots, a_n $ is lexicographically smaller than the sequence $ b_1, b_2, \dots, b_n $ if there exists $ 1 \le k \le n $ such that $ a_i = b_i $ for any $ 1 \le i < k $ but $ a_k < b_k $ .

## 样例 #1

### 输入

```
5
4
1 3 7 15
4
1 2 4 8
5
1 2 3 4 5
4
11 13 15 1
1
0```

### 输出

```
0 0 0 0 
0 1 3 7 
0 1 0 3 2 
0 2 0 14 
0```

# AI分析结果

### 题目内容重写

**题目描述**

一个非负整数序列 $ a_1, a_2, \dots, a_n $ 被称为“增长的”，如果对于所有 $ i $ 从 $ 1 $ 到 $ n - 1 $，$ a_i $ 的二进制表示中的所有 $1$ 都在 $ a_{i + 1} $ 的二进制表示中的 $1$ 的位置上（换句话说，$ a_i \:\&\: a_{i + 1} = a_i $，其中 $ \& $ 表示按位与）。如果 $ n = 1 $，则该序列也被认为是增长的。

例如，以下四个序列是增长的：

- $ [2, 3, 15, 175] $ — 二进制表示为 $ [10_2, 11_2, 1111_2, 10101111_2] $；
- $ [5] $ — 二进制表示为 $ [101_2] $；
- $ [1, 3, 7, 15] $ — 二进制表示为 $ [1_2, 11_2, 111_2, 1111_2] $；
- $ [0, 0, 0] $ — 二进制表示为 $ [0_2, 0_2, 0_2] $。

以下三个序列不是增长的：

- $ [3, 4, 5] $ — 二进制表示为 $ [11_2, 100_2, 101_2] $；
- $ [5, 4, 3] $ — 二进制表示为 $ [101_2, 100_2, 011_2] $；
- $ [1, 2, 4, 8] $ — 二进制表示为 $ [0001_2, 0010_2, 0100_2, 1000_2] $。

考虑两个非负整数序列 $ x_1, x_2, \dots, x_n $ 和 $ y_1, y_2, \dots, y_n $。如果序列 $ x_1 \oplus y_1, x_2 \oplus y_2, \dots, x_n \oplus y_n $ 是增长的，其中 $ \oplus $ 表示按位异或，则称这对序列为“共同增长的”。

给定一个整数序列 $ x_1, x_2, \dots, x_n $，找到字典序最小的序列 $ y_1, y_2, \dots, y_n $，使得序列 $ x_i $ 和 $ y_i $ 是共同增长的。

序列 $ a_1, a_2, \dots, a_n $ 字典序小于序列 $ b_1, b_2, \dots, b_n $，如果存在 $ 1 \le k \le n $，使得对于任何 $ 1 \le i < k $，$ a_i = b_i $，但 $ a_k < b_k $。

### 算法分类
位运算、构造

### 题解分析与结论

各题解的核心思路基本一致，都是通过位运算来构造字典序最小的 $ y $ 序列。主要思路是从 $ y_1 = 0 $ 开始，逐步计算 $ y_i $，使得 $ x_i \oplus y_i $ 的二进制表示中的 $1$ 包含 $ x_{i-1} \oplus y_{i-1} $ 的二进制表示中的 $1$。

### 所选高星题解

#### 题解1：KSToki (5星)
**关键亮点**：
- 代码简洁，逻辑清晰。
- 通过位运算直接计算 $ y_i $，避免了复杂的二进制分解。

**核心代码**：
```cpp
int T,n,x,y;
int main()
{
    T=read();
    while(T--)
    {
        n=read();
        x=read();
        printf("0");
        while(--n)
        {
            y=read();
            printf(" %d",((y|x)^y));
            x|=y;
        }
        puts("");
    }
    return 0;
}
```
**核心思想**：
- $ y_i = (y | x) \oplus y $，确保 $ x_i \oplus y_i $ 的二进制表示中的 $1$ 包含 $ x_{i-1} \oplus y_{i-1} $ 的二进制表示中的 $1$。

#### 题解2：Forever1507 (4星)
**关键亮点**：
- 通过 $ a[i] | a[i-1] $ 计算 $ y_i $，思路清晰。
- 代码结构良好，易于理解。

**核心代码**：
```cpp
for(int i=2;i<=n;i++){
    int tmp=a[i];
    now=a[i]|a[i-1];
    ans[i]=now-tmp;
    a[i]=a[i]^ans[i];
}
```
**核心思想**：
- $ y_i = (a[i] | a[i-1]) - a[i] $，确保 $ x_i \oplus y_i $ 的二进制表示中的 $1$ 包含 $ x_{i-1} \oplus y_{i-1} $ 的二进制表示中的 $1$。

#### 题解3：Saber___ (4星)
**关键亮点**：
- 通过 $ a[i-1] | a[i] $ 计算 $ y_i $，思路清晰。
- 代码简洁，易于理解。

**核心代码**：
```cpp
for(int i=2;i<=n;i++){
    int x = (a[i] | a[i - 1]) - a[i];
    a[i] ^= x;
    cout << x << " ";
}
```
**核心思想**：
- $ y_i = (a[i] | a[i-1]) - a[i] $，确保 $ x_i \oplus y_i $ 的二进制表示中的 $1$ 包含 $ x_{i-1} \oplus y_{i-1} $ 的二进制表示中的 $1$。

### 最优关键思路
通过位运算直接计算 $ y_i $，确保 $ x_i \oplus y_i $ 的二进制表示中的 $1$ 包含 $ x_{i-1} \oplus y_{i-1} $ 的二进制表示中的 $1$。这种方法简洁高效，避免了复杂的二进制分解。

### 可拓展之处
类似的问题可以通过位运算来解决，特别是在需要构造满足特定二进制性质的序列时。位运算在处理二进制问题时非常高效，可以大大简化代码和逻辑。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
3. [P1966 火柴排队](https://www.luogu.com.cn/problem/P1966)

### 个人心得摘录
- **KSToki**：代码简洁，逻辑清晰，通过位运算直接计算 $ y_i $，避免了复杂的二进制分解。
- **Forever1507**：通过 $ a[i] | a[i-1] $ 计算 $ y_i $，思路清晰，代码结构良好。
- **Saber___**：通过 $ a[i-1] | a[i] $ 计算 $ y_i $，思路清晰，代码简洁。

---
处理用时：46.51秒