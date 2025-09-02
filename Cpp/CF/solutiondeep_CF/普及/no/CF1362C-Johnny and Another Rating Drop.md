# 题目信息

# Johnny and Another Rating Drop

## 题目描述

The last contest held on Johnny's favorite competitive programming platform has been received rather positively. However, Johnny's rating has dropped again! He thinks that the presented tasks are lovely, but don't show the truth about competitors' skills.

The boy is now looking at the ratings of consecutive participants written in a binary system. He thinks that the more such ratings differ, the more unfair is that such people are next to each other. He defines the difference between two numbers as the number of bit positions, where one number has zero, and another has one (we suppose that numbers are padded with leading zeros to the same length). For example, the difference of $ 5 = 101_2 $ and $ 14 = 1110_2 $ equals to $ 3 $ , since $ 0101 $ and $ 1110 $ differ in $ 3 $ positions. Johnny defines the unfairness of the contest as the sum of such differences counted for neighboring participants.

Johnny has just sent you the rating sequence and wants you to find the unfairness of the competition. You have noticed that you've got a sequence of consecutive integers from $ 0 $ to $ n $ . That's strange, but the boy stubbornly says that everything is right. So help him and find the desired unfairness for received numbers.

## 说明/提示

For $ n = 5 $ we calculate unfairness of the following sequence (numbers from $ 0 $ to $ 5 $ written in binary with extra leading zeroes, so they all have the same length):

- $ 000 $
- $ 001 $
- $ 010 $
- $ 011 $
- $ 100 $
- $ 101 $

The differences are equal to $ 1 $ , $ 2 $ , $ 1 $ , $ 3 $ , $ 1 $ respectively, so unfairness is equal to $ 1 + 2 + 1 + 3 + 1 = 8 $ .

## 样例 #1

### 输入

```
5
5
7
11
1
2000000000000```

### 输出

```
8
11
19
1
3999999999987```

# AI分析结果

### 题目内容重写

# Johnny 和另一个评分下降

## 题目描述

Johnny 最喜欢的编程竞赛平台最近举办了一场竞赛，反响不错。然而，Johnny 的评分再次下降了！他认为这些题目虽然有趣，但并不能真实反映选手的能力。

Johnny 现在正在查看连续参赛者的评分，这些评分以二进制形式表示。他认为，如果两个相邻选手的评分差异越大，那么这种相邻关系就越不公平。他定义两个数字的差异为它们二进制表示中不同位的数量（假设数字用前导零填充到相同长度）。例如，$5 = 101_2$ 和 $14 = 1110_2$ 的差异为 $3$，因为 $0101$ 和 $1110$ 有 $3$ 个不同位。Johnny 将竞赛的不公平性定义为所有相邻选手评分的差异之和。

Johnny 给你发送了评分序列，希望你计算竞赛的不公平性。你注意到评分序列是从 $0$ 到 $n$ 的连续整数。虽然这很奇怪，但 Johnny 坚持认为这是正确的。请帮助他计算给定数字的不公平性。

## 说明/提示

对于 $n = 5$，我们计算以下序列的不公平性（数字从 $0$ 到 $5$ 以二进制表示，并用前导零填充到相同长度）：

- $000$
- $001$
- $010$
- $011$
- $100$
- $101$

相邻数字的差异分别为 $1$、$2$、$1$、$3$、$1$，因此不公平性为 $1 + 2 + 1 + 3 + 1 = 8$。

## 样例 #1

### 输入

```
5
5
7
11
1
2000000000000
```

### 输出

```
8
11
19
1
3999999999987
```

### 算法分类
数学、位运算

### 题解分析与结论

题解的核心思路是通过数学推导或位运算来高效计算不公平性。大多数题解都利用了二进制数的性质，通过逐位计算贡献来避免暴力枚举。

### 所选高分题解

#### 1. 作者：SpeedStar (赞：7)  
**星级：5星**  
**关键亮点：** 简洁高效的数学推导，代码实现清晰，时间复杂度为 $O(\log n)$。  
**核心代码：**
```cpp
while (n) {
    res += n;
    n /= 2;
}
```
**核心思想：** 通过不断将 $n$ 右移一位并累加，计算所有二进制位的贡献。

#### 2. 作者：LEle0309 (赞：1)  
**星级：4星**  
**关键亮点：** 详细解释了数学公式的推导过程，代码实现简洁。  
**核心代码：**
```cpp
while (n) {
    ans += n;
    n /= 2;
}
```
**核心思想：** 通过公式 $\sum_{i=0}^{\infty} \lfloor\frac{n}{2^i}\rfloor$ 计算不公平性，代码实现与 SpeedStar 类似。

#### 3. 作者：_Weslie_ (赞：1)  
**星级：4星**  
**关键亮点：** 通过二进制位的周期性变化推导出公式，代码实现清晰。  
**核心代码：**
```cpp
while (q) {
    q /= 2;
    ans += b / i;
    i *= 2;
}
```
**核心思想：** 通过逐位计算二进制位的贡献，时间复杂度为 $O(\log n)$。

### 最优关键思路与技巧
1. **数学推导：** 通过公式 $\sum_{i=0}^{\infty} \lfloor\frac{n}{2^i}\rfloor$ 计算不公平性，避免了暴力枚举。
2. **位运算优化：** 通过不断右移 $n$ 并累加，高效计算二进制位的贡献。

### 拓展思路
类似的问题可以通过分析二进制数的性质来解决，例如计算二进制数中 $1$ 的个数、二进制数的汉明距离等。

### 推荐题目
1. [P1226 【模板】快速幂](https://www.luogu.com.cn/problem/P1226)
2. [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)
3. [P1010 幂次方](https://www.luogu.com.cn/problem/P1010)

---
处理用时：29.07秒