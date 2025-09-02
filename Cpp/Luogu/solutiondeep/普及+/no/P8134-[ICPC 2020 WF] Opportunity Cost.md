# 题目信息

# [ICPC 2020 WF] Opportunity Cost

## 题目背景

ICPC2020 WF G

## 题目描述

As with most types of products, buying a new phone can be difficult.
One of the main challenges is that there are a lot of different
aspects of the phone that you might care about, such as its price, its
performance, and how user-friendly the phone is.
Typically, there will be no single phone that is simultaneously the
best at all of these things: the cheapest phone, the most powerful
phone, and the most user-friendly phone will likely be different phones.

Thus when buying a phone, you are forced to make some sacrifices by
balancing the different aspects you care about against each other and
choosing the phone that achieves the best compromise (where "best"
of course depends on what your priorities happen to be).  One way of
measuring this sacrifice is known as the *opportunity cost*,
which (for the purposes of this problem) we define as follows.

Suppose that you have bought a phone with price $x$, performance $y$,
and user-friendliness $z$. For simplicity, we assume that these three
values are measured on a comparable numeric scale where higher is
better. If there are $n$ available phones, and the values
$(x_i,y_i,z_i)$ represent the (price, performance, user-friendliness)
of the $i^{\text{th}}$ phone, then the opportunity cost of your phone
is defined as

$$\max _{1 \leq i \leq n}\left(\max \left(x_{i}-x, 0\right)+\max \left(y_{i}-y, 0\right)+\max \left(z_{i}-z, 0\right)\right)$$


Write a program that, given the list of available phones, finds a
phone with the minimum opportunity cost.

## 样例 #1

### 输入

```
4
20 5 5
5 20 5
5 5 20
10 10 10```

### 输出

```
10 4
```

## 样例 #2

### 输入

```
4
15 15 5
5 15 15
15 5 15
10 10 10```

### 输出

```
10 1```

# AI分析结果

### 算法分类
枚举

### 综合分析与结论
题目要求找到机会成本最小的手机，机会成本的计算涉及多个维度的比较。由于无法通过简单的排序或二分法解决，题解普遍采用了枚举的思路，通过预处理和位运算来优化计算过程。

### 所选题解
1. **柳易辰 (5星)**
   - **关键亮点**：通过位运算枚举所有可能的情况，预处理每种情况的最大值，再计算每个手机的机会成本。思路清晰，代码简洁，优化到位。
   - **个人心得**：通过将复杂的问题转化为位运算和预处理，大大简化了计算过程，避免了重复计算。

   ```cpp
   for (int i(1); i <= n; ++i)
       for (int k(0); k < 8; ++k) {
           ui sum(0);
           for (int j(0); j < 3; ++j) if ((k >> j) & 1) sum += a[i][j];
           if (sum > w[k]) w[k] = sum; 
       }
   ```

2. **KDL_ANIPLEX (5星)**
   - **关键亮点**：通过枚举所有可能的情况，预处理每种情况的最大值，再计算每个手机的机会成本。代码可读性强，思路清晰。
   - **个人心得**：通过将问题转化为枚举和预处理，避免了复杂的计算，提高了代码的效率。

   ```cpp
   for (int i = 1; i <= n; i++) {
       for (int k = 0; k < 8; k++) {
           int s = 0;
           if (k % 2) s += a[i].z;
           if (k / 2 % 2) s += a[i].y;
           if (k / 4 % 2) s += a[i].x;
           sun[k] = max(sun[k], s);
       }
   }
   ```

3. **XiaoQuQu (4星)**
   - **关键亮点**：通过位运算枚举所有可能的情况，预处理每种情况的最大值，再计算每个手机的机会成本。代码简洁，思路清晰。
   - **个人心得**：通过将问题转化为位运算和预处理，简化了计算过程，提高了代码的效率。

   ```cpp
   for (int S = 0; S < (1ll << 3); ++S) {
       for (int i = 1; i <= n; ++i) {
           int tmp = 0;
           for (int k = 0; k < 3; ++k) {
               if (S >> k & 1) tmp += a[i][k];
           }
           mx[S] = max(mx[S], tmp);
       }
   }
   ```

### 最优关键思路或技巧
- **位运算枚举**：通过位运算枚举所有可能的情况，简化了复杂问题的处理。
- **预处理**：通过预处理每种情况的最大值，避免了重复计算，提高了效率。

### 可拓展之处
- 类似的多维比较问题，可以通过枚举和预处理的方法来解决。
- 位运算在处理复杂问题时，可以大大简化代码和提高效率。

### 推荐题目
1. [P1880 [NOI1995]石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P1048 [NOIP2005 普及组] 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1060 [NOIP2006 普及组] 开心的金明](https://www.luogu.com.cn/problem/P1060)

---
处理用时：21.04秒