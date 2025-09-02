# 题目信息

# Money Buys Happiness

## 题目描述

Being a physicist, Charlie likes to plan his life in simple and precise terms.

For the next $ m $ months, starting with no money, Charlie will work hard and earn $ x $ pounds per month. For the $ i $ -th month $ (1 \le i \le m) $ , there'll be a single opportunity of paying cost $ c_i $ pounds to obtain happiness $ h_i $ .

Borrowing is not allowed. Money earned in the $ i $ -th month can only be spent in a later $ j $ -th month ( $ j>i $ ).

Since physicists don't code, help Charlie find the maximum obtainable sum of happiness.

## 说明/提示

In the first test case, Charlie only gets paid at the end of the month, so is unable to afford anything.

In the second test case, Charlie obtains the free happiness in the first month.

In the third test case, it's optimal for Charlie to buy happiness in the second month. Even with money left at the end, Charlie could not go back in time to obtain the happiness on offer in the first month.

## 样例 #1

### 输入

```
7
1 10
1 5
2 80
0 10
200 100
3 100
70 100
100 200
150 150
5 8
3 1
5 3
3 4
1 5
5 3
2 5
1 5
2 1
5 3
2 5
2 4
4 1
5 1
3 4
5 2
2 1
1 2
3 5
3 2
3 2```

### 输出

```
0
10
200
15
1
9
9```

# AI分析结果

### 题目内容重写
# 金钱买幸福

## 题目描述

作为一名物理学家，Charlie 喜欢用简单而精确的方式规划他的生活。

在接下来的 $m$ 个月里，Charlie 将从零开始努力工作，每个月赚取 $x$ 英镑。在第 $i$ 个月（$1 \le i \le m$），他将有一次机会支付 $c_i$ 英镑来获得 $h_i$ 的幸福。

不允许借钱。第 $i$ 个月赚的钱只能在之后的第 $j$ 个月（$j > i$）使用。

由于物理学家不擅长编程，请帮助 Charlie 找到他能获得的最大幸福总和。

## 说明/提示

在第一个测试用例中，Charlie 只在月底拿到工资，因此无法购买任何东西。

在第二个测试用例中，Charlie 在第一个月获得了免费的幸福。

在第三个测试用例中，Charlie 在第二个月购买幸福是最优的。即使最后还有剩余的钱，Charlie 也无法回到过去获得第一个月的幸福。

## 样例 #1

### 输入

```
7
1 10
1 5
2 80
0 10
200 100
3 100
70 100
100 200
150 150
5 8
3 1
5 3
3 4
1 5
5 3
2 5
1 5
2 1
5 3
2 5
2 4
4 1
5 1
3 4
5 2
2 1
1 2
3 5
3 2
3 2```

### 输出

```
0
10
200
15
1
9
9```

### 题解分析与结论

#### 综合分析
本题的核心是动态规划，但由于 $c_i$ 的值域较大，直接作为状态会导致内存不足。因此，大多数题解都采用了将幸福值作为状态，记录剩余的钱数。这种思路的关键在于利用幸福值的总和较小（$\sum h_i \leq 10^5$）的特点，避免了直接处理大值域的问题。

#### 最优思路与技巧
1. **状态定义**：将幸福值作为状态，$dp[j]$ 表示获得 $j$ 幸福值时剩余的最大钱数。
2. **状态转移**：对于每个月，更新 $dp[j]$，考虑是否购买当前的幸福值，并确保剩余的钱数不为负。
3. **工资处理**：在每个月底，给所有合法的 $dp[j]$ 加上当月的工资 $x$。
4. **空间优化**：由于每个月的状态只依赖于上个月的状态，因此可以省去第一维，使用一维数组进行滚动更新。

#### 推荐题解
1. **作者：Weekoder (5星)**
   - **关键亮点**：清晰的状态定义和转移方程，代码简洁且易于理解。
   - **核心代码**：
     ```cpp
     for (int i = 1; i <= m; i++) {
         for (int j = sum; j >= h[i]; j--)
            if (dp[j - h[i]] >= c[i])
                dp[j] = max(dp[j], dp[j - h[i]] - c[i]);
         for (int j = 0; j <= sum; j++)
            if (dp[j] >= 0)
                dp[j] += x;
     }
     ```

2. **作者：DrAlfred (4星)**
   - **关键亮点**：详细的状态转移分析，代码结构清晰，适合初学者理解。
   - **核心代码**：
     ```cpp
     for (int i = 1; i <= m; i++) {
         dp.resize(sum + 1, -1);
         for (int j = sum; j >= h; j--) {
             if (dp[j - h] >= c) {
                 dp[j] = max(dp[j], dp[j - h] - c);
             }
         }
         for (int j = 0; j <= sum; j++) {
             if (dp[j] >= 0) dp[j] += x;
         }
     }
     ```

3. **作者：Chenyichen0420 (4星)**
   - **关键亮点**：简洁的代码实现，优化了空间复杂度，适合竞赛场景。
   - **核心代码**：
     ```cpp
     for (int i = 1; i <= n; ++i) {
         cin >> l >> r; sm += r;
         for (int j = sm; j >= 0; --j) {
             if (j >= r && dp[j - r] >= l)
                 dp[j] = max(dp[j], dp[j - r] - l);
             if (dp[j] >= 0) dp[j] += m;
         }
     }
     ```

#### 推荐题目
1. **P1048 [NOIP2005 普及组] 采药**（题号：P1048）
2. **P1060 [NOIP2006 提高组] 开心的金明**（题号：P1060）
3. **P1616 疯狂的采药**（题号：P1616）

这些题目都涉及到动态规划中的背包问题，适合进一步练习类似的算法思路。

---
处理用时：34.87秒