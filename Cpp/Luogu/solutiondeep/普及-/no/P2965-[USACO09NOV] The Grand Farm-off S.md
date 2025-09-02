# 题目信息

# [USACO09NOV] The Grand Farm-off S

## 题目描述

Farmer John owns 3\*N (1 <= N <= 500,000) cows surprisingly numbered 0..3\*N-1, each of which has some associated integer weight W\_i (1 <= W\_i <= d). He is entering the Grand Farm-off, a farming competition where he shows off his cows to the greater agricultural community.

This competition allows him to enter a group of N cows. He has given each of his cows a utility rating U\_i (1 <= U\_i <= h), which

represents the usefulness he thinks that a particular cow will have in the competition, and he wants his selection of cows to have the maximal sum of utility.

There might be multiple sets of N cows that attain the maximum utility sum. FJ is afraid the competition may impose a total weight limit on the cows in the competition, so a secondary priority is to bring lighter weight competition cows.

Help FJ find a set of N cows with minimum possible total weight among the sets of N cows that maximize the utility, and print the remainder when this total weight is divided by M (10,000,000 <= M <= 1,000,000,000).

Note: to make the input phase faster, FJ has derived polynomials which will generate the weights and utility values for each cow. For each cow 0 <= i < 3\*N,

 $$W_i=(a\times i^5+b\times i^2+c)\mod d$$
 
 $$U_i=(e\times i^5+f\times i^3+g)\mod h$$
 
 $$(0\le a,b,c,d,e,f,g,h\le 10^9)$$

The formulae do sometimes generate duplicate numbers; your algorithm should handle this properly. 

农夫约翰有3N(1 < N < 500000)头牛，编号依次为1..#N，每头牛都有一个整数值的体 重。约翰准备参加农场技艺大赛，向广大的农业社区展示他的奶牛.
大赛规则允许约翰带N头牛参赛.约翰给每头牛赋予了一个“有用度”Ui，它表 示了某头牛在比赛中的有用程度.约翰希望他选出的奶牛的有用度之和最大.

有可能选出很多组的N头牛都能达到有用度最大和.约翰害怕选出的N头牛的总重量会给大赛 带来震撼，所以，要考虑优先选择体重轻的奶牛.

帮助约翰选出N头总重量最轻，并且有用度之和最大的奶牛.输出体重模M后的余数.

注意：为了使输入更快，约翰使用了一个多项式来生成每头牛的体重和有用度.对每头牛/， 体重和有用度的计算公式为：



 $$W_i=(a\times i^5+b\times i^2+c)\mod d$$
 
 $$U_i=(e\times i^5+f\times i^3+g)\mod h$$
 
 $$(0\le a,b,c,d,e,f,g,h\le 10^9)$$

## 说明/提示

The functions generate weights of 5, 6, 9, 14, 21, and 30 along with utilities of 0, 1, 8, 27, 64, and 125.


The two cows with the highest utility are cow 5 and 6, and their combined weight is 21+30=51.


## 样例 #1

### 输入

```
2 0 1 5 55555555 0 1 0 55555555 55555555 
```

### 输出

```
51 
```

# AI分析结果

### 算法分类
排序

### 综合分析与结论
题目要求在3N头牛中选择N头，使得它们的“有用度”之和最大，并且在有用度相同的情况下选择总重量最小的牛。核心思路是通过排序来解决，具体步骤如下：
1. **计算每头牛的体重和有用度**：根据给定的公式计算每头牛的体重 \( W_i \) 和有用度 \( U_i \)。
2. **排序**：按照有用度从大到小排序，如果有用度相同，则按照体重从小到大排序。
3. **选择前N头牛**：选择排序后的前N头牛，计算它们的总重量并输出模M的结果。

### 所选题解
#### 1. 作者：Qing_s (★★★★☆)
**关键亮点**：
- 详细解释了题目的核心逻辑和排序规则。
- 提供了代码实现，并指出了使用 `pow` 函数的潜在问题，建议手动计算幂次。
- 强调了数组大小和数据类型（`long long`）的重要性。

**个人心得**：
- 第一遍使用 `pow` 函数只得了10分，经过反思后改为手动计算幂次，最终通过。

**核心代码**：
```cpp
bool cmd(node x, node y) {
    if (x.u != y.u) return x.u > y.u;
    else return x.w < y.w;
}
```

#### 2. 作者：Suiseiseki (★★★★☆)
**关键亮点**：
- 简洁明了地解释了排序规则和实现方法。
- 强调了从0下标开始计算的重要性。

**核心代码**：
```cpp
struct P {
    int w, u;
    friend bool operator <(P p, P q) {
        if (p.u == q.u) return p.w < q.w;
        return p.u > q.u;
    }
} array[3*500000+5];
```

#### 3. 作者：FourteenObsidian (★★★★☆)
**关键亮点**：
- 提供了详细的代码实现，并强调了 `long long` 和数组大小的重要性。
- 手动计算幂次以避免 `pow` 函数的性能问题。

**核心代码**：
```cpp
inline long long cmp(COW x, COW y) {
    if (x.u == y.u) return x.w < y.w;
    else return x.u > y.u;
}
```

### 最优关键思路或技巧
1. **手动计算幂次**：避免使用 `pow` 函数，手动计算幂次以提高性能和精度。
2. **排序规则**：按照有用度从大到小排序，如果有用度相同则按照体重从小到大排序。
3. **数据类型和数组大小**：使用 `long long` 类型以避免溢出，确保数组大小足够大。

### 可拓展之处
- 类似的问题可以通过排序和贪心算法来解决，特别是在需要选择最优子集的情况下。
- 可以进一步优化计算幂次的方法，例如使用快速幂算法。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

---
处理用时：28.46秒