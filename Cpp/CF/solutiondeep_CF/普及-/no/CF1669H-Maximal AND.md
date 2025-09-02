# 题目信息

# Maximal AND

## 题目描述

Let $ \mathsf{AND} $ denote the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND), and $ \mathsf{OR} $ denote the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

You are given an array $ a $ of length $ n $ and a non-negative integer $ k $ . You can perform at most $ k $ operations on the array of the following type:

- Select an index $ i $ ( $ 1 \leq i \leq n $ ) and replace $ a_i $ with $ a_i $ $ \mathsf{OR} $ $ 2^j $ where $ j $ is any integer between $ 0 $ and $ 30 $ inclusive. In other words, in an operation you can choose an index $ i $ ( $ 1 \leq i \leq n $ ) and set the $ j $ -th bit of $ a_i $ to $ 1 $ ( $ 0 \leq j \leq 30 $ ).

Output the maximum possible value of $ a_1 $ $ \mathsf{AND} $ $ a_2 $ $ \mathsf{AND} $ $ \dots $ $ \mathsf{AND} $ $ a_n $ after performing at most $ k $ operations.

## 说明/提示

For the first test case, we can set the bit $ 1 $ ( $ 2^1 $ ) of the last $ 2 $ elements using the $ 2 $ operations, thus obtaining the array \[ $ 2 $ , $ 3 $ , $ 3 $ \], which has $ \mathsf{AND} $ value equal to $ 2 $ .

For the second test case, we can't perform any operations so the answer is just the $ \mathsf{AND} $ of the whole array which is $ 4 $ .

## 样例 #1

### 输入

```
4
3 2
2 1 1
7 0
4 6 6 28 6 6 12
1 30
0
4 4
3 1 3 1```

### 输出

```
2
4
2147483646
1073741825```

# AI分析结果

### 题目内容
# 最大按位与

## 题目描述
设 $\mathsf{AND}$ 表示[按位与操作](https://en.wikipedia.org/wiki/Bitwise_operation#AND)，$\mathsf{OR}$ 表示[按位或操作](https://en.wikipedia.org/wiki/Bitwise_operation#OR)。

给定一个长度为 $n$ 的数组 $a$ 和一个非负整数 $k$。你可以对该数组执行最多 $k$ 次以下类型的操作：
- 选择一个索引 $i$（$1 \leq i \leq n$），并将 $a_i$ 替换为 $a_i$ $\mathsf{OR}$ $2^j$，其中 $j$ 是介于 $0$ 到 $30$（含）之间的任意整数。换句话说，在一次操作中，你可以选择一个索引 $i$（$1 \leq i \leq n$）并将 $a_i$ 的第 $j$ 位设置为 $1$（$0 \leq j \leq 30$）。

输出在执行最多 $k$ 次操作后，$a_1$ $\mathsf{AND}$ $a_2$ $\mathsf{AND}$ $\cdots$ $\mathsf{AND}$ $a_n$ 的最大可能值。

## 说明/提示
对于第一个测试用例，我们可以使用 $2$ 次操作将最后 $2$ 个元素的第 $1$ 位（$2^1$）设置为 $1$，从而得到数组 \[ $2$, $3$, $3$\]，其按位与值等于 $2$。

对于第二个测试用例，我们不能执行任何操作，所以答案就是整个数组的按位与，即 $4$。

## 样例 #1
### 输入
```
4
3 2
2 1 1
7 0
4 6 6 28 6 6 12
1 30
0
4 4
3 1 3 1```

### 输出
```
2
4
2147483646
1073741825```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路均为贪心算法，从高位到低位枚举答案的二进制位，尝试将所有数的当前位都变为1以最大化按位与结果。具体要点为统计数组中每个数二进制表示中每一位为0的个数，若操作次数足够将当前位的0全部变为1，则进行操作并更新答案和剩余操作次数，否则跳过该位。解决的难点在于理解按位与运算的性质，即所有数的对应位都为1时结果才为1，以及如何通过贪心策略优先处理高位来保证最终结果最大。

### 所选的题解
- **作者：Nt_Tsumiki (5星)**
    - **关键亮点**：思路清晰，代码简洁明了，直接从高位枚举，通过统计每一位为0的个数来判断是否能将该位变为1，核心代码逻辑紧凑。
    - **重点代码**：
```cpp
for (int i = 30,tmp = 0;i >= 0;i--) {
    for (int j = 1;j <= n;j++) tmp+=(a[j]>>i&1^1);
    if (k >= tmp) {
        k -= tmp;
        ans|=1<<i;
    }
}   
```
    - **核心实现思想**：从30位到0位枚举，统计当前位为0的个数`tmp`，若`k`大于等于`tmp`，则用`k`减去`tmp`，并将答案`ans`的当前位置1。
- **作者：2huk (4星)**
    - **关键亮点**：提出维护桶的方式统计每一位为1的个数，使代码逻辑更清晰，对贪心策略的阐述详细。
    - **重点代码**：
```cpp
int res = 0;
for (int i = 30; i >= 0; -- i )
    if (k >= n - t[i])
        res |= 1 << i,
        k -= n - t[i];
```
    - **核心实现思想**：从30位到0位枚举，若`k`大于等于需要将当前位变为1的操作次数（`n - t[i]`），则更新结果`res`并减去操作次数。
- **作者：JS_TZ_ZHR (4星)**
    - **关键亮点**：代码简洁，通过两次循环分别统计每一位为0的个数和根据操作次数更新答案，对贪心依据的说明简洁到位。
    - **重点代码**：
```cpp
for(int i=0;i<=30;i++){
    cnt[i]=0;
    for(int j=1;j<=n;j++){
        if(!(a[j]&(1<<i)))cnt[i]++;
    }
}
for(int i=30;i>=0;i--)if(k>=cnt[i])k-=cnt[i],ans+=(1<<i);
```
    - **核心实现思想**：先统计每一位为0的个数到`cnt`数组，再从30位到0位枚举，若`k`大于等于`cnt[i]`，则更新答案`ans`并减去操作次数。

### 最优关键思路或技巧
利用贪心策略，基于按位与运算性质，从高位到低位枚举二进制位，通过统计每一位为0的个数来决定是否使用操作次数将所有数的该位变为1，以最大化按位与结果。

### 可拓展之处
同类型题通常围绕位运算和贪心策略，比如改变操作类型或者数组的约束条件。类似算法套路是在涉及位运算的最值问题中，常考虑按位贪心，根据运算性质从高位或低位依次处理。

### 推荐题目
- [P1247 取火柴游戏](https://www.luogu.com.cn/problem/P1247)：涉及位运算和博弈论，需通过按位分析来确定策略。
- [P1879 [USACO06NOV]玉米田Corn Fields](https://www.luogu.com.cn/problem/P1879)：状态压缩动态规划结合位运算，通过位运算来表示和处理状态。
- [P5657 【模板】AC自动机（二次加强版）](https://www.luogu.com.cn/problem/P5657)：字符串处理结合位运算，利用位运算优化匹配过程。 

---
处理用时：62.83秒