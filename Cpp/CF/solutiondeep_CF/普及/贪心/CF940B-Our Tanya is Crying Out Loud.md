# 题目信息

# Our Tanya is Crying Out Loud

## 题目描述

Right now she actually isn't. But she will be, if you don't solve this problem.

You are given integers $ n $ , $ k $ , $ A $ and $ B $ . There is a number $ x $ , which is initially equal to $ n $ . You are allowed to perform two types of operations:

1. Subtract 1 from $ x $ . This operation costs you $ A $ coins.
2. Divide $ x $ by $ k $ . Can be performed only if $ x $ is divisible by $ k $ . This operation costs you $ B $ coins.

 What is the minimum amount of coins you have to pay to make $ x $ equal to $ 1 $ ?

## 说明/提示

In the first testcase, the optimal strategy is as follows:

- Subtract 1 from $ x $ ( $ 9→8 $ ) paying 3 coins.
- Divide $ x $ by 2 ( $ 8→4 $ ) paying 1 coin.
- Divide $ x $ by 2 ( $ 4→2 $ ) paying 1 coin.
- Divide $ x $ by 2 ( $ 2→1 $ ) paying 1 coin.

The total cost is $ 6 $ coins.

In the second test case the optimal strategy is to subtract 1 from $ x $ $ 4 $ times paying $ 8 $ coins in total.

## 样例 #1

### 输入

```
9
2
3
1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5
5
2
20
```

### 输出

```
8
```

## 样例 #3

### 输入

```
19
3
4
2
```

### 输出

```
12
```

# AI分析结果

### 题目翻译

# Our Tanya is Crying Out Loud

## 题目描述

现在她其实并没有哭。但如果你不解决这个问题，她就会哭。

给你四个整数 $n$、$k$、$A$ 和 $B$。有一个数 $x$，初始时等于 $n$。你可以执行以下两种操作：

1. 将 $x$ 减 1。这个操作需要花费 $A$ 个硬币。
2. 将 $x$ 除以 $k$。只有当 $x$ 能被 $k$ 整除时才能执行这个操作。这个操作需要花费 $B$ 个硬币。

你需要将 $x$ 变为 $1$，问最少需要花费多少硬币？

## 说明/提示

在第一个测试用例中，最优策略如下：

- 将 $x$ 减 1（$9→8$），花费 3 个硬币。
- 将 $x$ 除以 2（$8→4$），花费 1 个硬币。
- 将 $x$ 除以 2（$4→2$），花费 1 个硬币。
- 将 $x$ 除以 2（$2→1$），花费 1 个硬币。

总花费为 6 个硬币。

在第二个测试用例中，最优策略是将 $x$ 减 1 四次，总共花费 8 个硬币。

## 样例 #1

### 输入

```
9
2
3
1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5
5
2
20
```

### 输出

```
8
```

## 样例 #3

### 输入

```
19
3
4
2
```

### 输出

```
12
```

### 题解分析与结论

#### 综合分析

这道题的核心在于贪心算法的应用。通过比较减法和除法的成本，选择最优的操作来减少 $x$ 的值。所有题解都基于这一思路，但在实现细节和优化程度上有所不同。

#### 最优关键思路

1. **贪心策略**：每次操作时，比较减法和除法的成本，选择成本较低的操作。
2. **优化**：当 $x$ 不能被 $k$ 整除时，先通过减法将 $x$ 减到能被 $k$ 整除，然后再进行除法操作。
3. **特判**：当 $k=1$ 时，只能通过减法将 $x$ 减到 1。

#### 评分较高的题解

1. **作者：_xbn (赞：5)**  
   - **星级**：5  
   - **关键亮点**：代码简洁，逻辑清晰，直接比较减法和除法的成本，选择最优操作。  
   - **核心代码**：
     ```cpp
     while(m > 1) {
         if(m % k > 0) {
             int t = m / k;
             t = t * k;
             if(t == 0) t = 1;
             ans = ans + (m - t) * p;
             m = t;
             continue;
         }
         int t = m / k;
         tot = m - t;
         if(tot * p < q) {
             ans += (m - 1) * p;
             m = 1;
         } else {
             m = t;
             ans += q;
         }
     }
     ```

2. **作者：miraculously (赞：4)**  
   - **星级**：4  
   - **关键亮点**：代码逻辑清晰，通过减法将 $x$ 减到能被 $k$ 整除，然后比较减法和除法的成本。  
   - **核心代码**：
     ```cpp
     while(n != 1) {
         ans += n % k * a;
         n -= n % k;
         if(b < (n - n / k) * a) {
             ans += b;
             n /= k;
         } else {
             ans += (n - 1) * a;
             return printf("%lld", ans), 0;
         }
     }
     ```

3. **作者：thomas_zjl (赞：2)**  
   - **星级**：4  
   - **关键亮点**：代码逻辑清晰，通过减法将 $x$ 减到能被 $k$ 整除，然后比较减法和除法的成本。  
   - **核心代码**：
     ```cpp
     while(n != 1) {
         ans += (n % k) * a;
         n = n - n % k;
         if(b > (n - n / k) * a) {
             ans += (n - 1) * a;
             break;
         } else {
             n = n / k;
             ans += b;
         }
     }
     ```

### 扩展思路与推荐题目

#### 扩展思路

1. **动态规划**：可以考虑使用动态规划来记录每一步的最优解，但在这道题中贪心算法已经足够高效。
2. **数学优化**：可以通过数学公式进一步优化，减少循环次数。

#### 推荐题目

1. **洛谷 P1048 [NOIP2005 普及组] 采药**  
   - **题号**：P1048  
   - **考察点**：贪心算法、动态规划

2. **洛谷 P1060 [NOIP2006 提高组] 开心的金明**  
   - **题号**：P1060  
   - **考察点**：贪心算法、动态规划

3. **洛谷 P1090 [NOIP2004 提高组] 合并果子**  
   - **题号**：P1090  
   - **考察点**：贪心算法、优先队列

---
处理用时：44.46秒