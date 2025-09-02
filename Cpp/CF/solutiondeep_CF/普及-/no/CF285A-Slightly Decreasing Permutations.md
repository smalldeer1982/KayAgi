# 题目信息

# Slightly Decreasing Permutations

## 题目描述

Permutation $ p $ is an ordered set of integers $ p_{1},p_{2},...,p_{n} $ , consisting of $ n $ distinct positive integers, each of them doesn't exceed $ n $ . We'll denote the $ i $ -th element of permutation $ p $ as $ p_{i} $ . We'll call number $ n $ the size or the length of permutation $ p_{1},p_{2},...,p_{n} $ .

The decreasing coefficient of permutation $ p_{1},p_{2},...,p_{n} $ is the number of such $ i\ (1<=i&lt;n) $ , that $ p_{i}&gt;p_{i+1} $ .

You have numbers $ n $ and $ k $ . Your task is to print the permutation of length $ n $ with decreasing coefficient $ k $ .

## 样例 #1

### 输入

```
5 2
```

### 输出

```
1 5 2 4 3
```

## 样例 #2

### 输入

```
3 0
```

### 输出

```
1 2 3
```

## 样例 #3

### 输入

```
3 2
```

### 输出

```
3 2 1
```

# AI分析结果

### 题目内容
# 略递减排列

## 题目描述
排列 $p$ 是一个有序的整数集合 $p_1, p_2, \ldots, p_n$，由 $n$ 个不同的正整数组成，每个数都不超过 $n$。我们将排列 $p$ 的第 $i$ 个元素记为 $p_i$。我们称数字 $n$ 为排列 $p_1, p_2, \ldots, p_n$ 的大小或长度。

排列 $p_1, p_2, \ldots, p_n$ 的递减系数是满足 $p_i > p_{i + 1}$ 的 $i$（$1 \leq i < n$）的数量。

给定数字 $n$ 和 $k$。你的任务是输出长度为 $n$ 且递减系数为 $k$ 的排列。

## 样例 #1
### 输入
```
5 2
```
### 输出
```
1 5 2 4 3
```

## 样例 #2
### 输入
```
3 0
```
### 输出
```
1 2 3
```

## 样例 #3
### 输入
```
3 2
```
### 输出
```
3 2 1
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是通过特定方式构造出满足递减系数为 $k$ 的排列。主要区别在于构造的具体方式。有的是先输出部分递增数再输出部分递减数；有的通过双指针交换数组元素来构造；还有的先考虑非排列情况再离散化。

### 所选的题解
- **作者：yanxingyu0910 (赞：1)，星级：4 星**
    - **关键亮点**：思路清晰，先明确题意为使前一个比后一个大的个数等于 $K$，通过正序输出 $k + 2$ 到 $n$ 的数，再逆序输出 $k + 1$ 到 $1$ 的数来构造排列。代码使用快读优化输入。
    - **重点代码**：
```cpp
for(i = k + 2; i <= n; i++){//正序输出 
    printf("%lld ", i);
}
for(i = k + 1; i >= 1; i--){//逆序输出 
    printf("%lld ", i);
}
```
    - **核心实现思想**：分两段循环，第一段正序输出较大部分数，第二段逆序输出较小部分数，从而构造出满足条件的排列。
- **作者：hanyuchen2019 (赞：1)，星级：4 星**
    - **关键亮点**：表述简洁，先阐述题意为构造含 $k$ 个逆序对的序列，提出先输出 $n - k$ 个递增数，再输出 $k$ 个递减数的思路，并通过例子说明，同时指出循环边界的易错点。
    - **重点代码**：
```cpp
for(int i = k + 1; i <= n; i++)//递增
    cout << i << " ";
for(int i = k; i >= 1; i--)//递减
    cout << i << " ";
```
    - **核心实现思想**：与上一题解类似，通过控制两段循环分别输出递增和递减部分的数来构造排列。
- **作者：Misaka_Mik0t0 (赞：0)，星级：4 星**
    - **关键亮点**：直接给出构造方法，让前 $k + 1$ 个数下降，之后全部上升，思路直接明了。
    - **重点代码**：
```cpp
for(int i = k + 1; i >= 1; --i)printf("%d ", i);
for(int i = k + 2; i <= n; ++i)printf("%d ", i);
```
    - **核心实现思想**：同样是分两段循环构造，先逆序输出前 $k + 1$ 个数，再正序输出剩余数。

### 最优关键思路或技巧
这些较优题解的关键思路都是通过分段构造的方式，利用递增和递减序列的组合来满足递减系数的要求。在代码实现上，合理控制循环边界是关键技巧。

### 拓展
此类题目属于构造类问题，常见的类似套路是根据给定的条件，通过数学分析找到一种合理的构造方式。比如构造满足特定条件的矩阵、序列等。

### 推荐题目
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)
- [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)
- [P1433 吃奶酪](https://www.luogu.com.cn/problem/P1433)

---
处理用时：39.66秒