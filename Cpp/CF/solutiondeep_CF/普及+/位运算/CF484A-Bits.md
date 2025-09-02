# 题目信息

# Bits

## 题目描述

Let's denote as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) the number of bits set ('1' bits) in the binary representation of the non-negative integer $ x $ .

You are given multiple queries consisting of pairs of integers $ l $ and $ r $ . For each query, find the $ x $ , such that $ l<=x<=r $ , and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) is maximum possible. If there are multiple such numbers find the smallest of them.

## 说明/提示

Let's denote as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) the number of bits set ('1' bits) in the binary representation of the non-negative integer $ x $ .

You are given multiple queries consisting of pairs of integers $ l $ and $ r $ . For each query, find the $ x $ , such that $ l<=x<=r $ , and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF484A/b30c9ebcde0f9929e0344fbd7e7dae947e957ee2.png) is maximum possible. If there are multiple such numbers find the smallest of them.

## 样例 #1

### 输入

```
3
1 2
2 4
1 10
```

### 输出

```
1
3
7
```

# AI分析结果

### 题目内容
# Bits

## 题目描述
设 \( \text{popcount}(x) \) 为非负整数 \( x \) 的二进制表示中置位（‘1’ 位）的数量。

给定多个由整数对 \( l \) 和 \( r \) 组成的查询。对于每个查询，找到满足 \( l \leq x \leq r \) 的 \( x \)，使得 \( \text{popcount}(x) \) 尽可能大。如果有多个这样的数，则找到其中最小的数。

## 说明/提示
设 \( \text{popcount}(x) \) 为非负整数 \( x \) 的二进制表示中置位（‘1’ 位）的数量。

给定多个由整数对 \( l \) 和 \( r \) 组成的查询。对于每个查询，找到满足 \( l \leq x \leq r \) 的 \( x \)，使得 \( \text{popcount}(x) \) 尽可能大。如果有多个这样的数，则找到其中最小的数。

## 样例 #1
### 输入
```
3
1 2
2 4
1 10
```
### 输出
```
1
3
7
```

### 综合分析与结论
这些题解的核心思路都是贪心算法。要点在于从 \( l \) 出发，通过位运算在不超过 \( r \) 的前提下，尽量在低位添加 \( 1 \) 来构造目标数。难点在于如何通过合适的位运算实现这一构造过程，并确保不超出范围。

多数题解采用从低位到高位遍历，尝试将 \( l \) 的当前位变为 \( 1 \) （通过 `|` 按位或运算），若结果不超过 \( r \) 则继续，否则停止。少数题解采用分情况讨论递归的方式。

最优关键思路是利用贪心策略，从低位开始按位或运算构造结果，这样既保证 \( 1 \) 的数量尽量多，又能使结果最小。

相似类型题通常围绕位运算和贪心策略，例如求特定区间内满足某种位状态条件的最值等。

### 所选的题解
- **作者：XiXi (赞：27) - 5星**
    - **关键亮点**：思路清晰，对贪心策略阐述详细，代码简洁明了。
    - **核心代码**：
```cpp
for (i=1;(l|i)<=r;i<<=1) l|=i;
```
**核心思想**：从 \( i = 1 \) 开始，每次将 \( i \) 左移一位，尝试将 \( l \) 与 \( i \) 按位或，若结果不超过 \( r \) ，则更新 \( l \) 。
- **作者：EuphoricStar (赞：3) - 5星**
    - **关键亮点**：简洁地阐述贪心策略，核心代码简短且注释清晰。
    - **核心代码**：
```cpp
ull t = 1;
while ((l | t) <= r) l |= t, t <<= 1;
```
**核心思想**：初始化 \( t = 1 \) ，在 \( l \) 与 \( t \) 按位或不超过 \( r \) 时，更新 \( l \) 并左移 \( t \) 。
- **作者：_cmh (赞：3) - 5星**
    - **关键亮点**：对思路和位运算解释详细，提醒数据类型和输入方式避免超时，代码简洁。
    - **核心代码**：
```cpp
for(unsigned long long i=1;(l|i)<=r;i<<=1) l|=i;
```
**核心思想**：同其他类似代码，从低位开始尝试按位或，构造满足条件的数。

### 洛谷相似题目
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：涉及贪心策略，通过对数据排序来得到最优解，与本题贪心思想有相似之处。
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：同样是贪心算法的应用，通过分析数据间关系找到最优排序。
- [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)：需要运用贪心策略来制定游戏策略，在一定规则下获取最优结果。 

---
处理用时：23.25秒