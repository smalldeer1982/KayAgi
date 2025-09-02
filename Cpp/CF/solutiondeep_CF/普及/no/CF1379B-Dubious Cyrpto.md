# 题目信息

# Dubious Cyrpto

## 题目描述

Pasha loves to send strictly positive integers to his friends. Pasha cares about security, therefore when he wants to send an integer $ n $ , he encrypts it in the following way: he picks three integers $ a $ , $ b $ and $ c $ such that $ l \leq       a,b,c \leq r $ , and then he computes the encrypted value $ m = n       \cdot a + b - c $ .

Unfortunately, an adversary intercepted the values $ l $ , $ r $ and $ m $ . Is it possible to recover the original values of $ a $ , $ b $ and $ c $ from this information? More formally, you are asked to find any values of $ a $ , $ b $ and $ c $ such that

- $ a $ , $ b $ and $ c $ are integers,
- $ l \leq a, b, c \leq r $ ,
- there exists a strictly positive integer $ n $ , such that $ n \cdot a + b - c = m $ .

## 说明/提示

In the first example $ n = 3 $ is possible, then $ n \cdot 4 +       6 - 5 = 13 = m $ . Other possible solutions include: $ a = 4 $ , $ b = 5 $ , $ c = 4 $ (when $ n = 3 $ ); $ a = 5 $ , $ b =       4 $ , $ c = 6 $ (when $ n = 3 $ ); $ a = 6 $ , $ b = 6 $ , $ c = 5 $ (when $ n = 2 $ ); $ a = 6 $ , $ b = 5 $ , $ c =       4 $ (when $ n = 2 $ ).

In the second example the only possible case is $ n = 1 $ : in this case $ n \cdot 2 + 2 - 3 = 1 = m $ . Note that, $ n = 0 $ is not possible, since in that case $ n $ is not a strictly positive integer.

## 样例 #1

### 输入

```
2
4 6 13
2 3 1```

### 输出

```
4 6 5
2 2 3```

# AI分析结果

### 题目内容重写

#### 题目描述

Pasha 喜欢给他的朋友们发送严格的正整数。Pasha 关心安全性，因此当他想要发送一个整数 $n$ 时，他会以以下方式加密：他选择三个整数 $a$、$b$ 和 $c$，满足 $l \leq a, b, c \leq r$，然后计算加密值 $m = n \cdot a + b - c$。

不幸的是，一个对手截获了 $l$、$r$ 和 $m$ 的值。是否可以从这些信息中恢复出原始的 $a$、$b$ 和 $c$ 的值？更正式地说，你需要找到任何满足以下条件的 $a$、$b$ 和 $c$ 的值：

- $a$、$b$ 和 $c$ 是整数，
- $l \leq a, b, c \leq r$，
- 存在一个严格的正整数 $n$，使得 $n \cdot a + b - c = m$。

#### 说明/提示

在第一个示例中，$n = 3$ 是可能的，那么 $n \cdot 4 + 6 - 5 = 13 = m$。其他可能的解包括：$a = 4$，$b = 5$，$c = 4$（当 $n = 3$ 时）；$a = 5$，$b = 4$，$c = 6$（当 $n = 3$ 时）；$a = 6$，$b = 6$，$c = 5$（当 $n = 2$ 时）；$a = 6$，$b = 5$，$c = 4$（当 $n = 2$ 时）。

在第二个示例中，唯一可能的情况是 $n = 1$：在这种情况下，$n \cdot 2 + 2 - 3 = 1 = m$。注意，$n = 0$ 是不可能的，因为在这种情况下 $n$ 不是一个严格的正整数。

#### 样例 #1

##### 输入

```
2
4 6 13
2 3 1
```

##### 输出

```
4 6 5
2 2 3
```

### 算法分类

枚举、数学

### 题解分析与结论

所有题解的核心思路都是通过枚举 $a$ 的值，然后根据 $m$ 和 $a$ 的关系来确定 $b$ 和 $c$ 的值。不同的题解在确定 $b$ 和 $c$ 时采用了不同的策略，但整体思路相似。

#### 题解评分与亮点

1. **作者：wmy_goes_to_thu (赞：7)**  
   - **星级：4星**  
   - **关键亮点**：通过枚举 $a$ 并利用模运算快速确定 $b$ 和 $c$ 的值，代码简洁且高效。  
   - **代码核心**：
     ```cpp
     int p = i - m % i;
     if (l + p <= r) {
         cout << i << " " << l << " " << l + p << endl;
         break;
     }
     if (r - p >= l) {
         cout << i << " " << r - p << " " << r << endl;
         break;
     }
     ```

2. **作者：Create_Random (赞：1)**  
   - **星级：4星**  
   - **关键亮点**：将问题转化为一次函数的形式，通过二分查找确定 $n$ 的值，思路新颖且时间复杂度较低。  
   - **代码核心**：
     ```cpp
     long long left = 1, right = m;
     while (left <= right) {
         long long mid = (left + right) / 2;
         if (abs(mid * i - m) <= r - l) {
             if (mid * i - m >= 0) {
                 printf("%d %lld %lld\n", i, l, l + mid * i - m);
             } else {
                 printf("%d %lld %lld\n", i, r, r + mid * i - m);
             }
             flag = 1;
             break;
         }
     }
     ```

3. **作者：bigclever (赞：1)**  
   - **星级：4星**  
   - **关键亮点**：通过枚举 $a$ 并分别考虑 $n$ 的上下界，直接计算 $b$ 和 $c$ 的值，思路清晰且易于理解。  
   - **代码核心**：
     ```cpp
     int n1 = m / a, n2 = m / a + 1;
     if (n1 > 0 && (l + m - n1 * a) <= r) {
         printf("%lld %lld %lld\n", a, l + m - n1 * a, l);
         break;
     }
     if (n2 > 0 && (l + n2 * a - m) <= r) {
         printf("%lld %lld %lld\n", a, l, l + n2 * a - m);
         break;
     }
     ```

### 最优关键思路

通过枚举 $a$ 的值，利用模运算或二分查找快速确定 $b$ 和 $c$ 的值，确保 $b$ 和 $c$ 在给定范围内。这种方法既高效又易于实现。

### 拓展思路

类似的问题可以通过枚举和数学推导来解决，尤其是在涉及模运算和不等式约束的情况下。对于这类问题，枚举和数学推导是常用的解题思路。

### 推荐题目

1. [P1008 三连击](https://www.luogu.com.cn/problem/P1008)
2. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
3. [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)

---
处理用时：39.82秒