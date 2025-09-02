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



### 综合分析与结论
该问题本质是**利润最大化的完全背包问题**，核心思路是将每个古董的利润（R_i-C_i）视为价值，成本C_i视为体积，通过完全背包DP求解。所有正确解法均采用此思路，最终需遍历所有可能的花费情况，计算 `dp[i] + (M - i)` 的最大值。

---

### 精选题解（评分≥4星）

#### 1. 作者：Yizhixiaoyun ⭐⭐⭐⭐⭐  
**关键亮点**  
- 代码简洁清晰，直接套用完全背包模板  
- 明确注释状态转移方程 `dp[j] = max(dp[j], dp[j-c_i] + profit)`  
- 正确处理最终答案的遍历逻辑  
```cpp
// 核心代码片段
for(int i=1;i<=n;++i){
    for(int j=c[i];j<=m;++j){
        dp[j] = max(dp[j], dp[j-c[i]] + r[i]-c[i]);
    }
}
for(int i=1;i<=m;++i) 
    ans = max(ans, dp[i]-i + m);
```

#### 2. 作者：暮影灰狼 ⭐⭐⭐⭐  
**关键亮点**  
- 通过 `val[i] = tmp-w[i]` 预计算利润提升可读性  
- 使用更规范的变量命名（w表示成本，val表示利润）  
- 包含输入优化代码（快速读入函数）

#### 3. 作者：Halberd_Cease ⭐⭐⭐⭐  
**关键亮点**  
- 使用 `ans[j] = j` 初始化巧妙处理剩余金额  
- 最终直接输出 `ans[m]`（需确认正确性，但代码通过测试）  
```cpp
// 独特初始化方式
for(int i=1;i<=m;i++) ans[i] = i;  // 初始剩余金额
for(...) ans[j] = max(ans[j], ans[j-x]+k);
```

---

### 关键思路与技巧总结
1. **问题转化**：将利润计算式 `总利润 = (初始金额 - 总成本) + 总收益` 简化为 `(R_i - C_i)` 的累加，转化为完全背包问题  
2. **状态设计**：`dp[j]` 表示花费j元时的最大利润  
3. **逆向思维**：最终答案需遍历所有可能花费 `i`，计算 `dp[i] + (M - i)`，而非直接取 `dp[M]`  
4. **空间优化**：通过滚动数组将空间复杂度优化至O(M)

---

### 同类题目推荐
1. [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616) - 完全背包模板题  
2. [P1853 投资的最大效益](https://www.luogu.com.cn/problem/P1853) - 复合背包与利润最大化  
3. [P2918 [USACO08NOV] Buying Hay S](https://www.luogu.com.cn/problem/P2918) - 带特殊限制的完全背包

---

### 题解心得摘录
**kfhkx的调试教训**  
> "刚开始尝试贪心按单位利润排序，但发现反例：当单个利润低但数量多时更优。意识到必须用动态规划处理组合问题"

**启示**：贪心在背包问题中往往不适用，需通过动态规划穷举状态。当物品间存在组合效应时，DP是更可靠的方法。

---
处理用时：50.70秒