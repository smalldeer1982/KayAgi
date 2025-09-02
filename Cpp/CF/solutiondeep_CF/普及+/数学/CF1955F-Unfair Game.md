# 题目信息

# Unfair Game

## 题目描述

Alice and Bob gathered in the evening to play an exciting game on a sequence of $ n $ integers, each integer of the sequence doesn't exceed $ 4 $ . The rules of the game are too complex to describe, so let's just describe the winning condition — Alice wins if the [bitwise XOR](http://tiny.cc/xor_wiki_eng) of all the numbers in the sequence is non-zero; otherwise, Bob wins.

The guys invited Eve to act as a judge. Initially, Alice and Bob play with $ n $ numbers. After one game, Eve removes one of the numbers from the sequence, then Alice and Bob play with $ n-1 $ numbers. Eve removes one number again, after which Alice and Bob play with $ n - 2 $ numbers. This continues until the sequence of numbers is empty.

Eve seems to think that in such a game, Alice almost always wins, so she wants Bob to win as many times as possible. Determine the maximum number of times Bob can win against Alice if Eve removes the numbers optimally.

## 说明/提示

In the first example, Bob wins when Eve has not removed any numbers yet.

In the second example, Bob wins if Eve removes one one and one three.

## 样例 #1

### 输入

```
5
1 1 1 0
1 0 1 2
2 2 2 0
3 3 2 0
0 9 9 9```

### 输出

```
1
1
3
3
12```

# AI分析结果



# Unfair Game

## 题目描述

Alice 和 Bob 在晚上聚在一起玩一个基于 $n$ 个整数序列的刺激游戏，序列中的每个整数不超过 $4$。游戏的获胜条件是：若序列中所有数字的[按位异或](http://tiny.cc/xor_wiki_eng)结果非零则 Alice 胜，否则 Bob 胜。

他们邀请 Eve 担任裁判。初始时，Alice 和 Bob 使用 $n$ 个数字进行游戏。每轮游戏后，Eve 会从序列中移除一个数字，接着用剩余数字进行下一轮游戏，直到序列为空。

Eve 认为 Alice 几乎总能获胜，因此她希望让 Bob 尽可能多地获胜。请确定在 Eve 最优移除策略下，Bob 能获胜的最大次数。

## 样例 #1

### 输入

```
5
1 1 1 0
1 0 1 2
2 2 2 0
3 3 2 0
0 9 9 9
```

### 输出

```
1
1
3
3
12
```

---

### 综合题解分析

#### 关键思路
1. **数字4的特殊性**：由于4的二进制最高位（100）与其他数字不同，只有当4的数量为偶数时，其异或结果才可能为0。贡献次数为 $\lfloor a_4/2 \rfloor$。
2. **1、2、3的奇偶性**：当三个数的奇偶性相同时，异或结果可能为0。特别地，若三者均为奇数，可以额外贡献1次（因为 $1 \oplus 2 \oplus 3 = 0$）。
3. **公式整合**：总次数为各数字数量除以2的整数部分之和，加上三个数全为奇数时的额外1次。

#### 最优解法
```cpp
int ans = a/2 + b/2 + c/2 + d/2 + (a%2 && b%2 && c%2);
```

#### 高分题解推荐

1. **菲斯斯夫斯基（5星）**  
   **亮点**：通过奇偶性分类讨论，最终整合为简洁公式。  
   **代码**：
   ```cpp
   printf("%d\n", a/2 + b/2 + c/2 + d/2 + (a%2 && b%2 && c%2));
   ```

2. **yangduan_（4星）**  
   **亮点**：直接点明1、2、3异或为0的特性，代码简洁。  
   **代码**：
   ```cpp
   ans = a/2 + b/2 + c/2 + d/2 + ((a%2==1) && (b%2==1) && (c%2==1));
   ```

3. **yshpdyt（4星）**  
   **亮点**：详细推导奇偶性要求，明确数学逻辑。  
   **代码**：
   ```cpp
   res = a1/2 + a2/2 + a3/2 + a4/2 + (a1%2 && a2%2 && a3%2);
   ```

#### 扩展与总结
- **同类问题**：涉及位运算性质与奇偶性分析的题目，如异或和为0的子数组计数。
- **举一反三**：对于需要最大化特定条件的删除策略，优先考虑数学性质而非暴力枚举。

#### 推荐练习题
1. [P1469 找筷子](https://www.luogu.com.cn/problem/P1469)（异或性质应用）
2. [P1100 高低位交换](https://www.luogu.com.cn/problem/P1100)（位运算操作）
3. [P2114 起床困难综合症](https://www.luogu.com.cn/problem/P2114)（位运算与贪心策略）

---
处理用时：112.00秒