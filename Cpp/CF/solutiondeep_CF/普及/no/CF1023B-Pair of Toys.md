# 题目信息

# Pair of Toys

## 题目描述

Tanechka is shopping in the toy shop. There are exactly $ n $ toys in the shop for sale, the cost of the $ i $ -th toy is $ i $ burles. She wants to choose two toys in such a way that their total cost is $ k $ burles. How many ways to do that does she have?

Each toy appears in the shop exactly once. Pairs $ (a, b) $ and $ (b, a) $ are considered equal. Pairs $ (a, b) $ , where $ a=b $ , are not allowed.

## 说明/提示

In the first example Tanechka can choose the pair of toys ( $ 1, 4 $ ) or the pair of toys ( $ 2, 3 $ ).

In the second example Tanechka can choose only the pair of toys ( $ 7, 8 $ ).

In the third example choosing any pair of toys will lead to the total cost less than $ 20 $ . So the answer is 0.

In the fourth example she can choose the following pairs: $ (1, 1000000000000) $ , $ (2, 999999999999) $ , $ (3, 999999999998) $ , ..., $ (500000000000, 500000000001) $ . The number of such pairs is exactly $ 500000000000 $ .

## 样例 #1

### 输入

```
8 5
```

### 输出

```
2
```

## 样例 #2

### 输入

```
8 15
```

### 输出

```
1
```

## 样例 #3

### 输入

```
7 20
```

### 输出

```
0
```

## 样例 #4

### 输入

```
1000000000000 1000000000001
```

### 输出

```
500000000000
```

# AI分析结果

### 题目内容重写
# 玩具对

## 题目描述

Tanechka 在玩具店购物。店里有恰好 $n$ 个玩具在售，第 $i$ 个玩具的价格为 $i$ 个 burles。她想要选择两个玩具，使得它们的总价格为 $k$ 个 burles。她有多少种选择方式？

每个玩具在店里只出现一次。$(a, b)$ 和 $(b, a)$ 被视为相同的组合。$(a, b)$ 且 $a=b$ 的组合不被允许。

## 说明/提示

在第一个例子中，Tanechka 可以选择玩具对 $(1, 4)$ 或 $(2, 3)$。

在第二个例子中，Tanechka 只能选择玩具对 $(7, 8)$。

在第三个例子中，选择任何玩具对的总价格都小于 $20$，所以答案是 $0$。

在第四个例子中，她可以选择以下玩具对：$(1, 1000000000000)$，$(2, 999999999999)$，$(3, 999999999998)$，……，$(500000000000, 500000000001)$。这样的组合数恰好是 $500000000000$。

## 样例 #1

### 输入

```
8 5
```

### 输出

```
2
```

## 样例 #2

### 输入

```
8 15
```

### 输出

```
1
```

## 样例 #3

### 输入

```
7 20
```

### 输出

```
0
```

## 样例 #4

### 输入

```
1000000000000 1000000000001
```

### 输出

```
500000000000
```

### 算法分类
数学

### 题解分析与结论
本题的核心是通过数学方法计算满足条件的玩具对数量。所有题解都基于以下思路：
1. **无解情况**：当 $2n-1 < k$ 时，无解，输出 $0$。
2. **有解情况**：根据 $k$ 的奇偶性，计算满足条件的玩具对数量。具体来说，若 $k$ 为偶数，则答案为 $\min(k/2-1, n-k/2)$；若 $k$ 为奇数，则答案为 $\min(k/2, n-k/2)$。

### 评分较高的题解
1. **作者：naroto2022 (4星)**
   - **关键亮点**：清晰地解释了分类讨论的原因，代码简洁明了。
   - **代码核心**：
     ```cpp
     if(2*n-1<k) printf("0");
     else if(k%2==0) printf("%lld",min(k/2-1,n-k/2));
     else printf("%lld",min(k/2,n-k/2));
     ```

2. **作者：sto__Liyhzh__orz (4星)**
   - **关键亮点**：分类讨论清晰，代码简洁，使用了 `long long` 避免溢出。
   - **代码核心**：
     ```cpp
     if(n+n-1<k) cout<<0<<endl;
     else if(n>=k-1) cout<<k/2-(k%2?0:1)<<endl;
     else cout<<(2*n-k+1)/2<<endl;
     ```

3. **作者：Fraction (4星)**
   - **关键亮点**：通过解不等式组的方法，思路清晰，代码简洁。
   - **代码核心**：
     ```cpp
     if(2 * n - 1 < k) printf("0");
     else if(1 + n >= k) l = 1, r = k-1;
     else l = k - n, r = n;
     cout << (r-l+1)/2 ;
     ```

### 最优关键思路
1. **分类讨论**：根据 $k$ 的奇偶性和 $n$ 的大小关系，分别计算满足条件的玩具对数量。
2. **数学优化**：通过数学公式直接计算，避免暴力枚举，时间复杂度为 $O(1)$。

### 拓展思路
类似的问题可以通过数学方法优化，避免暴力枚举。例如，求解满足条件的数对、组合等问题时，可以先分析问题的数学性质，再通过公式计算。

### 推荐题目
1. [P1024 一元三次方程求解](https://www.luogu.com.cn/problem/P1024)
2. [P1036 选数](https://www.luogu.com.cn/problem/P1036)
3. [P1045 数的划分](https://www.luogu.com.cn/problem/P1045)

---
处理用时：31.54秒