# 题目信息

# Candy Store

## 题目描述

The store sells $ n $ types of candies with numbers from $ 1 $ to $ n $ . One candy of type $ i $ costs $ b_i $ coins. In total, there are $ a_i $ candies of type $ i $ in the store.

You need to pack all available candies in packs, each pack should contain only one type of candies. Formally, for each type of candy $ i $ you need to choose the integer $ d_i $ , denoting the number of type $ i $ candies in one pack, so that $ a_i $ is divided without remainder by $ d_i $ .

Then the cost of one pack of candies of type $ i $ will be equal to $ b_i \cdot d_i $ . Let's denote this cost by $ c_i $ , that is, $ c_i = b_i \cdot d_i $ .

After packaging, packs will be placed on the shelf. Consider the cost of the packs placed on the shelf, in order $ c_1, c_2, \ldots, c_n $ . Price tags will be used to describe costs of the packs. One price tag can describe the cost of all packs from $ l $ to $ r $ inclusive if $ c_l = c_{l+1} = \ldots = c_r $ . Each of the packs from $ 1 $ to $ n $ must be described by at least one price tag. For example, if $ c_1, \ldots, c_n = [4, 4, 2, 4, 4] $ , to describe all the packs, a $ 3 $ price tags will be enough, the first price tag describes the packs $ 1, 2 $ , the second: $ 3 $ , the third: $ 4, 5 $ .

You are given the integers $ a_1, b_1, a_2, b_2, \ldots, a_n, b_n $ . Your task is to choose integers $ d_i $ so that $ a_i $ is divisible by $ d_i $ for all $ i $ , and the required number of price tags to describe the values of $ c_1, c_2, \ldots, c_n $ is the minimum possible.

For a better understanding of the statement, look at the illustration of the first test case of the first test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1798C/1160d0ae9da0a28139cfb8794bbbd0911d44c66f.png)Let's repeat the meaning of the notation used in the problem:

 $ a_i $ — the number of candies of type $ i $ available in the store.

 $ b_i $ — the cost of one candy of type $ i $ .

 $ d_i $ — the number of candies of type $ i $ in one pack.

 $ c_i $ — the cost of one pack of candies of type $ i $ is expressed by the formula $ c_i = b_i \cdot d_i $ .

## 说明/提示

In the first test case, you can choose $ d_1 = 4 $ , $ d_2 = 6 $ , $ d_3 = 7 $ , $ d_4 = 5 $ . Then the cost of packs will be equal to $ [12, 12, 35, 35] $ . $ 2 $ price tags are enough to describe them, the first price tag for $ c_1, c_2 $ and the second price tag for $ c_3, c_4 $ . It can be shown that with any correct choice of $ d_i $ , at least $ 2 $ of the price tag will be needed to describe all the packs. Also note that this example is illustrated by a picture in the statement.

In the second test case, with $ d_1 = 4 $ , $ d_2 = 2 $ , $ d_3 = 10 $ , the costs of all packs will be equal to $ 20 $ . Thus, $ 1 $ price tag is enough to describe all the packs. Note that $ a_i $ is divisible by $ d_i $ for all $ i $ , which is necessary condition.

In the third test case, it is not difficult to understand that one price tag can be used to describe $ 2 $ nd, $ 3 $ rd and $ 4 $ th packs. And additionally a price tag for pack $ 1 $ and pack $ 5 $ . Total: $ 3 $ price tags.

## 样例 #1

### 输入

```
5
4
20 3
6 2
14 5
20 7
3
444 5
2002 10
2020 2
5
7 7
6 5
15 2
10 3
7 7
5
10 1
11 5
5 1
2 2
8 2
6
7 12
12 3
5 3
9 12
9 3
1000000000 10000```

### 输出

```
2
1
3
2
5```

# AI分析结果

### 题目重写

#### 糖果商店

## 题目描述

商店出售 $ n $ 种糖果，编号从 $ 1 $ 到 $ n $。第 $ i $ 种糖果每颗价格为 $ b_i $ 元，商店中共有 $ a_i $ 颗第 $ i $ 种糖果。

你需要将所有糖果打包，每包只能包含同一种糖果。具体来说，对于每种糖果 $ i $，你需要选择一个整数 $ d_i $，表示每包中包含的糖果数量，且 $ a_i $ 必须能被 $ d_i $ 整除。

然后，第 $ i $ 种糖果每包的价格为 $ b_i \cdot d_i $，记为 $ c_i $，即 $ c_i = b_i \cdot d_i $。

打包后，糖果包将被摆放在货架上。考虑货架上糖果包的价格序列 $ c_1, c_2, \ldots, c_n $。一个价格标签可以描述从 $ l $ 到 $ r $ 的所有糖果包的价格，当且仅当 $ c_l = c_{l+1} = \ldots = c_r $。每个糖果包 $ 1 $ 到 $ n $ 必须至少被一个价格标签描述。例如，如果 $ c_1, \ldots, c_n = [4, 4, 2, 4, 4] $，那么需要 $ 3 $ 个价格标签，第一个标签描述第 $ 1 $ 和第 $ 2 $ 包，第二个标签描述第 $ 3 $ 包，第三个标签描述第 $ 4 $ 和第 $ 5 $ 包。

给定整数 $ a_1, b_1, a_2, b_2, \ldots, a_n, b_n $，你的任务是选择整数 $ d_i $，使得 $ a_i $ 能被 $ d_i $ 整除，并且描述 $ c_1, c_2, \ldots, c_n $ 所需的价格标签数量最小。

### 算法分类
贪心

### 题解分析与结论

本题的核心在于如何选择 $ d_i $ 使得 $ c_i $ 尽可能多地相等，从而减少价格标签的数量。通过分析，我们发现 $ c_i $ 必须满足 $ c_i = b_i \cdot d_i $，且 $ d_i $ 必须整除 $ a_i $。因此，$ c_i $ 必须同时满足 $ c_i $ 是 $ b_i $ 的倍数，且 $ c_i $ 整除 $ a_i \cdot b_i $。进一步推导，我们可以得出一个区间 $ [l, r] $ 可以共用一个价格标签的条件是 $\text{lcm}(b_l, \ldots, b_r)$ 整除 $\gcd(a_l \cdot b_l, \ldots, a_r \cdot b_r)$。

基于这个条件，我们可以采用贪心策略，从左到右尽可能多地合并糖果包，直到无法满足条件为止，然后开始一个新的价格标签。

### 高星题解

#### 题解作者：一扶苏一 (5星)

**关键亮点：**
1. 清晰地推导了 $ c_i $ 的条件，并给出了贪心策略的证明。
2. 代码实现简洁，使用了 `std::gcd` 和 `std::lcm` 函数，避免了复杂的数学计算。
3. 通过贪心策略，每次尽可能多地合并糖果包，减少了价格标签的数量。

**代码核心思想：**
```cpp
for (int i = 1; i <= n; ++i) {
    ++ans;
    long long x = b[i], y = 1ll * a[i] * b[i];
    for (int j = i + 1; j <= n; ++j) {
        x = std::lcm(1ll * b[j], x);
        y = std::gcd(y, 1ll * a[j] * b[j]);
        if (y % x != 0) {
            i = j - 1; break;
        }
        if (j == n) {
            i = j; break;
        }
    }
}
```

#### 题解作者：inc1ude_c (4星)

**关键亮点：**
1. 详细解释了 $ c_i $ 的条件，并给出了贪心策略的合理性。
2. 代码实现清晰，使用了 `gcd` 和 `lcm` 函数，逻辑简洁。

**代码核心思想：**
```cpp
for (int i = 1; i <= n; ++i) {
    ansg = gcd(ansg, a[i] * b[i]);
    ansl = lcm(ansl, b[i]);
    if ((ansg % ansl) != 0) {
        ansg = a[i] * b[i];
        ansl = b[i];
        cnt++;
    }
}
```

#### 题解作者：Hisaishi_Kanade (4星)

**关键亮点：**
1. 通过数学推导，清晰地解释了 $ c_i $ 的条件。
2. 代码实现简洁，使用了自定义的 `gcd` 和 `lcm` 函数，逻辑清晰。

**代码核心思想：**
```cpp
for (i = 1; i <= n;) {
    fx = b[i];
    fy = a[i] * b[i];
    for (j = i + 1; j <= n; ++j) {
        fx = lcm(fx, b[j]);
        fy = gcd(fy, a[j] * b[j]);
        if (fy % fx != 0) {
            i = j;
            break;
        }
    }
    ++cnt;
    if (j > n) break;
}
```

### 最优关键思路与技巧

1. **贪心策略**：从左到右尽可能多地合并糖果包，直到无法满足条件为止，然后开始一个新的价格标签。
2. **数学推导**：通过推导 $ c_i $ 的条件，确保每个区间 $ [l, r] $ 可以共用一个价格标签。
3. **代码优化**：使用 `gcd` 和 `lcm` 函数简化计算，避免复杂的数学操作。

### 拓展思路

类似的问题可以出现在需要将多个元素合并为尽可能少的组，且每组满足特定条件的场景中。例如，在资源分配、任务调度等问题中，贪心策略和数学推导同样适用。

### 推荐题目

1. [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P1090 [NOIP2004 提高组] 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1966 [NOIP2013 提高组] 火柴排队](https://www.luogu.com.cn/problem/P1966)

---
处理用时：54.25秒