# 题目信息

# Colorful Bricks

## 题目描述

On his free time, Chouti likes doing some housework. He has got one new task, paint some bricks in the yard.

There are $ n $ bricks lined in a row on the ground. Chouti has got $ m $ paint buckets of different colors at hand, so he painted each brick in one of those $ m $ colors.

Having finished painting all bricks, Chouti was satisfied. He stood back and decided to find something fun with these bricks. After some counting, he found there are $ k $ bricks with a color different from the color of the brick on its left (the first brick is not counted, for sure).

So as usual, he needs your help in counting how many ways could he paint the bricks. Two ways of painting bricks are different if there is at least one brick painted in different colors in these two ways. Because the answer might be quite big, you only need to output the number of ways modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, since $ k=0 $ , the color of every brick should be the same, so there will be exactly $ m=3 $ ways to color the bricks.

In the second example, suppose the two colors in the buckets are yellow and lime, the following image shows all $ 4 $ possible colorings.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1081C/4fa7a2f23ff4f46a8191eb0b20c44295510018b7.png)

## 样例 #1

### 输入

```
3 3 0
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 2 1
```

### 输出

```
4
```

# AI分析结果

### 题目重写
**题目描述**

在空闲时间，Chouti喜欢做一些家务。他有一个新任务，给院子里的一些砖块涂色。

地上有一排$n$块砖。Chouti手头有$m$种不同颜色的油漆桶，因此他将每块砖涂成这$m$种颜色之一。

涂完所有砖块后，Chouti感到满意。他退后一步，决定找点乐子。经过一番计数，他发现其中有$k$块砖的颜色与左边砖块的颜色不同（第一块砖不计入，因为它没有左边的砖块）。

因此，他需要你的帮助来计算他有多少种涂砖的方式。两种涂砖方式不同，当且仅当至少有一块砖在这两种方式中被涂成不同的颜色。由于答案可能很大，你只需要输出结果对$998\,244\,353$取模的值。

**说明/提示**

在第一个样例中，由于$k=0$，每块砖的颜色应该相同，因此有恰好$m=3$种涂砖方式。

在第二个样例中，假设油漆桶中的两种颜色是黄色和绿色，下图展示了所有$4$种可能的涂色方式。

**样例 #1**

### 输入
```
3 3 0
```

### 输出
```
3
```

**样例 #2**

### 输入
```
3 2 1
```

### 输出
```
4
```

### 算法分类
组合数学

### 题解分析与结论
该题的核心是计算在$n$块砖中，恰好有$k$块砖的颜色与左边砖块不同的涂色方案数。大多数题解都采用了组合数学的思路，通过隔板法和乘法原理来计算方案数。

### 精选题解
1. **作者：houzhiyuan (赞：8)**
   - **星级：5**
   - **关键亮点**：题解思路清晰，详细解释了如何通过隔板法和乘法原理计算方案数，并提供了完整的代码实现，包括组合数和快速幂的计算。
   - **代码核心**：
     ```cpp
     long long C1(long long a,long long b){//计算组合数
         return cheng(jie[a],cheng(ni[b],ni[a-b]));
     }
     ```
     - **实现思想**：通过预处理阶乘和逆元，快速计算组合数。

2. **作者：YB_is_short (赞：6)**
   - **星级：4**
   - **关键亮点**：简洁明了地解释了隔板法和颜色选择的思路，虽然没有提供完整代码，但思路清晰，易于理解。
   - **代码核心**：无
     - **实现思想**：通过组合数和颜色选择的乘法原理计算方案数。

3. **作者：Ousmane_Dembele (赞：5)**
   - **星级：4**
   - **关键亮点**：提供了动态规划的解法，虽然复杂度较高，但思路新颖，适合理解动态规划的应用。
   - **代码核心**：
     ```cpp
     dp[i][j]=dp[i-1][j-1]*(m-1)+dp[i-1][j];
     ```
     - **实现思想**：通过状态转移方程计算前$i$块砖中有$j$块与左边颜色不同的方案数。

### 最优关键思路
最优的思路是通过组合数学中的隔板法和乘法原理来计算方案数。具体来说，首先在$n-1$个空隙中选择$k$个位置插入隔板，将砖块分成$k+1$段，每段颜色相同。然后，第一段有$m$种颜色选择，后面的每段有$m-1$种颜色选择，因此总方案数为$C_{n-1}^{k} \times m \times (m-1)^k$。

### 可拓展之处
该题的思路可以拓展到其他组合数学问题，如计算在特定条件下排列或组合的方案数。类似的题目可以考察如何通过隔板法和乘法原理解决复杂的组合问题。

### 推荐题目
1. [P1357 花园](https://www.luogu.com.cn/problem/P1357)
2. [P3197 [HNOI2008]越狱](https://www.luogu.com.cn/problem/P3197)
3. [P3807 【模板】卢卡斯定理](https://www.luogu.com.cn/problem/P3807)

---
处理用时：29.93秒