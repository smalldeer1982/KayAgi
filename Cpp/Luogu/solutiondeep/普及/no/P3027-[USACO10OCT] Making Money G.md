# 题目信息

# [USACO10OCT] Making Money G

## 题目背景

FJ又经营起了古董生意，买卖一些像奶牛圣诞树上的装饰之类的小玩意。他知道他会将他能存储的N(1<=N<=100)件不同的奶牛古董每件都卖出。


而且如果他的钱足够多他可以买他想要的任意数量的古董（即他可以购买的古董数量没有限制）。他只有M(1<=M<=100,000)元钱来买古董，但他想要在他经商的第一年年末最大化他的利润（这有点难以解释）。


第i种古董采购需要花费Ci(1<=Ci<=100,000)元钱，每卖掉一件可以获得Ri(1<=Ri<=100,000)元钱(每卖一件的利润为Ri-Ci)。FJ可以以任意顺序卖出他的货物。他并不需要花光他所有的钱来购买古董。


FJ在他经商的第一年年末能得到的最大总利润（利润=初始钱数-总花费+总收入）是多少呢？输入数据保证这个数字不会超过1,000,000,000.


假设FJ只有3种古董而且开始时有M=17元钱。下面是三种古董的花费和收入。


古董 花费 收入


1 2 4

2 5 6

3 3 7

在这种情况下，FJ应该花15元购买5个3号古董，再花2元购买1个1号古董，总共17元。他的利润是5\*(7-3)+1\*(4-2)=5\*4+1\*2=22元。他不能获得比这更多的利润了。


提示：第二个样例很有挑战性，但我们的答案是正确的。


输入格式：


第1行：两个以空格分开的整数：N和M


第2行到第N+1行：第i+1行包括两个以空格分开的整数：Ci和Ri


输出格式


第1行：FJ能获得的最大利润


## 题目描述

FJ has gone into the curio business, buying and selling knickknacks like cow Christmas tree ornaments. He knows he will sell every single curio he can stock from a catalog of N (1 <= N <= 100)

different cow curios, and he can buy as many of each kind of curio as his heart desires. He has only M (1 <= M <= 100,000) money to invest but wants to maximize his profit (which has a slightly unusual definition) at the end of his first year in business.

Curio type i costs C\_i (1 <= C\_i <= 100,000) money to purchase and yields R\_i (1 <= R\_i <= 100,000) revenue for each curio sold (a profit of R\_i-C\_i). FJ can mix and match the curios he sells in any way he wishes. He need not spend all his money when purchasing curios.

What is the greatest amount of total profit (profit = initial\_cash - all\_costs + all\_sales) FJ can have at the end of his first year? This number is guaranteed to be less than 1,000,000,000.

Consider the situation when FJ has just 3 kinds of curios and starts with M=17. Below are the cost and revenue numbers for each curio:

Curio     Cost     Revenue

#        C\_i       R\_i

1         2         4

2         5         6

3         3         7

In this case, FJ should purchase 5 curios of type 3 for 15 money and 1 more curio of type 1 for 2 money, a total of 17 money. His profit will be 5 \* (7-3) + 1 \* (4-2) = 5\*4 + 1\*2 = 22 money. He can do no better than this given the cost and revenue structure.

NOTE: The second test case is challenging -- but our answer is correct.


## 样例 #1

### 输入

```
3 17 
2 4 
5 6 
3 7 
```

### 输出

```
22 
```

# AI分析结果



### 算法分类
动态规划

### 综合分析与结论
本题核心为完全背包问题，每个古董可无限购买。利润计算式为 $总利润 = 初始资金 - 总花费 + 总收入$，需转化为动态规划模型。关键点在于正确计算物品价值（利润 $R_i-C_i$），最后遍历所有可能花费以找到最优解。

---

### 精选题解

#### 1. Yizhixiaoyun (4星)
**关键亮点**：  
- 明确点出完全背包模型，状态转移方程简洁。  
- 代码清晰，包含完整循环逻辑及答案处理。  
**代码核心**：
```cpp
for(int j=c[i];j<=m;j++)
    dp[j] = max(dp[j], dp[j-c[i]] + r[i]-c[i]);
// 最后遍历所有i求ans = max(dp[i] -i + m)
```

#### 2. 暮影灰狼 (4星)  
**关键亮点**：  
- 强调答案处理逻辑，解释为何需遍历而非直接取dp[m]。  
- 代码包含优化后的输入处理。  
**核心代码**：  
```cpp
for(int i=1;i<=n;++i)
    for(int j=w[i];j<=m;++j)
        dp[j] = max(dp[j], dp[j-w[i]]+val[i]);
```

#### 3. NATO (4星)  
**关键亮点**：  
- 使用更简洁的变量命名，代码风格易读。  
- 明确说明利润计算式与遍历逻辑。  
**核心实现**：  
```cpp
for(ll j=c[i];j<=m;++j)
    dp[j] = max(dp[j], dp[j-c[i]] + r[i]);
ans = max(ans, dp[i] + m -i);
```

---

### 最优思路总结
1. **模型转化**：将古董购买视为完全背包，物品价值为 $R_i - C_i$，花费为 $C_i$。  
2. **状态转移**：使用标准完全背包递推式更新dp数组。  
3. **答案处理**：遍历所有可能花费 $i$，计算 $dp[i] + (M - i)$ 的最大值，确保未用完资金的情况被考虑。

---

### 同类型拓展
- **类似题目**：  
  1. [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616)（完全背包模板）  
  2. [P1853 投资的最大利润](https://www.luogu.com.cn/problem/P1853)（本金再投资变种）  
  3. [P2946 Cow Frisbee Team S](https://www.luogu.com.cn/problem/P2946)（组合型完全背包）

---

### 个人心得摘录
- **kfhkx**：贪心排序利润可能导致错误，需验证策略正确性。  
  → 教训：动态规划问题中，贪心策略需谨慎验证，避免局部最优陷阱。  
- **Yizhixiaoyun**：完全背包模板直接应用，重点在问题转化。  
  → 关键：理解题目利润计算式与背包模型的对应关系。

---
处理用时：45.23秒