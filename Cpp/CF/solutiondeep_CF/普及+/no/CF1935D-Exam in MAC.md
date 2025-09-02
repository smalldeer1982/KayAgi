# 题目信息

# Exam in MAC

## 题目描述

The Master's Assistance Center has announced an entrance exam, which consists of the following.

The candidate is given a set $ s $ of size $ n $ and some strange integer $ c $ . For this set, it is needed to calculate the number of pairs of integers $ (x, y) $ such that $ 0 \leq x \leq y \leq c $ , $ x + y $ is not contained in the set $ s $ , and also $ y - x $ is not contained in the set $ s $ .

Your friend wants to enter the Center. Help him pass the exam!

## 说明/提示

In the first test case, the following pairs are suitable: $ (0, 0) $ , $ (2, 2) $ , $ (3, 3) $ .

In the third test case, the following pairs are suitable: $ (0, 1) $ , $ (0, 2) $ , $ (0, 4) $ , $ (1, 3) $ , $ (2, 6) $ , $ (3, 4) $ , $ (3, 5) $ , $ (4, 5) $ , $ (4, 6) $ , $ (5, 6) $ .

## 样例 #1

### 输入

```
8
3 3
1 2 3
1 179
57
4 6
0 3 5 6
1 1
1
5 10
0 2 4 8 10
5 10
1 3 5 7 9
4 10
2 4 6 7
3 1000000000
228 1337 998244353```

### 输出

```
3
16139
10
2
33
36
35
499999998999122959```

# AI分析结果

### 题目内容重写

**题目描述**

Master's Assistance Center 宣布了一项入学考试，考试内容如下：

考生会得到一个大小为 $n$ 的集合 $s$ 和一个奇怪的整数 $c$。对于这个集合，需要计算满足以下条件的整数对 $(x, y)$ 的数量：$0 \leq x \leq y \leq c$，且 $x + y$ 不在集合 $s$ 中，同时 $y - x$ 也不在集合 $s$ 中。

你的朋友想进入这个中心。帮助他通过考试！

**说明/提示**

在第一个测试用例中，以下数对是符合条件的：$(0, 0)$，$(2, 2)$，$(3, 3)$。

在第三个测试用例中，以下数对是符合条件的：$(0, 1)$，$(0, 2)$，$(0, 4)$，$(1, 3)$，$(2, 6)$，$(3, 4)$，$(3, 5)$，$(4, 5)$，$(4, 6)$，$(5, 6)$。

### 算法分类
数学、容斥原理

### 题解分析与结论

该题的核心是通过容斥原理计算符合条件的数对数量。所有题解都采用了容斥原理的思路，即先计算所有可能的数对数量，然后减去不满足条件的数对数量，最后加上被重复减去的数对数量。

### 所选高分题解

#### 题解1：作者：66xyyd (赞：7)
**星级：5星**
**关键亮点：**
- 详细解释了容斥原理的四个条件，分别计算了满足不同条件的数对数量。
- 代码结构清晰，函数命名合理，易于理解。
- 通过数学公式推导，优化了计算过程，减少了时间复杂度。

**核心代码：**
```cpp
long long _f1(long long x){
    return (x+1)*(x+1)-(x+1)*x/2;
}
long long _f2(long long x){
    return x-(x+x%2)/2+1;
}
long long _f3(long long x){
    return (c-x+1);
}
long long _f4(long long x){
    return (x*(x+1)/2+(n-x)*(n-x+1)/2);
}
```
**实现思想：**
- `_f1` 计算所有可能的数对数量。
- `_f2` 计算满足 $x + y \in s$ 的数对数量。
- `_f3` 计算满足 $y - x \in s$ 的数对数量。
- `_f4` 计算同时满足 $x + y \in s$ 和 $y - x \in s$ 的数对数量。

#### 题解2：作者：sunkuangzheng (赞：5)
**星级：4星**
**关键亮点：**
- 使用了前缀和优化，进一步减少了时间复杂度。
- 通过奇偶性分类，简化了同时满足两个条件的数对数量的计算。

**核心代码：**
```cpp
int ct0 = 0,ct1 = 0;
for(int i = 1;i <= n;i ++) cin >> a[i],sum += c - a[i] + 1 + a[i] / 2 + 1;
for(int i = 1;i <= n;i ++){
    ct1 += (a[i] & 1),ct0 += !(a[i] & 1),
    sum -= (a[i] & 1) ? ct1 : ct0;
}
```
**实现思想：**
- 通过遍历集合 $s$，分别计算满足 $x + y \in s$ 和 $y - x \in s$ 的数对数量。
- 利用奇偶性分类，计算同时满足两个条件的数对数量。

#### 题解3：作者：Alex_Wei (赞：4)
**星级：4星**
**关键亮点：**
- 简洁明了地解释了容斥原理的应用。
- 通过组合数学公式，直接计算了同时满足两个条件的数对数量。

**核心代码：**
```cpp
int A_0 = sum_{s\in S} (1 + \lfloor \frac s 2 \rfloor);
int A_1 = sum_{s\in S} (c - s + 1);
int A_2 = \binom {\mathrm{odd} + 1} 2 + \binom {\mathrm{even} + 1} 2;
```
**实现思想：**
- `A_0` 计算满足 $x + y \in s$ 的数对数量。
- `A_1` 计算满足 $y - x \in s$ 的数对数量。
- `A_2` 计算同时满足 $x + y \in s$ 和 $y - x \in s$ 的数对数量。

### 最优关键思路或技巧
1. **容斥原理**：通过容斥原理计算符合条件的数对数量，先计算总数，再减去不满足条件的数对数量，最后加上被重复减去的数对数量。
2. **奇偶性分类**：通过奇偶性分类，简化了同时满足两个条件的数对数量的计算。
3. **前缀和优化**：利用前缀和优化，减少了时间复杂度，提高了计算效率。

### 可拓展之处
该题的思路可以拓展到其他类似的容斥原理问题，例如计算满足多个条件的组合数或排列数。类似的问题可以通过分类讨论和数学公式推导来优化计算过程。

### 推荐题目
1. [P1494 [国家集训队]小Z的袜子](https://www.luogu.com.cn/problem/P1494)
2. [P1972 [SDOI2009]HH的项链](https://www.luogu.com.cn/problem/P1972)
3. [P2709 小B的询问](https://www.luogu.com.cn/problem/P2709)

---
处理用时：45.12秒