# 题目信息

# [USACO10JAN] Buying Feed, II S

## 题目描述

Farmer John needs to travel to town to pick up K (1 <= K <= 100) pounds of feed. Driving D miles with K pounds of feed in his truck costs D\*K cents.

The county feed lot has N (1 <= N <= 100) stores (conveniently numbered 1..N) that sell feed. Each store is located on a segment of the X axis whose length is E (1 <= E <= 350). Store i is at location X\_i (0 < X\_i < E) on the number line and can sell FJ as much as F\_i (1 <= F\_i <= 100) pounds of feed at a cost of C\_i (1 <= C\_i <= 1,000,000) cents per pound. Amazingly, a given point on the X axis might have more than one store.

FJ starts at location 0 on this number line and can drive only in the positive direction, ultimately arriving at location E, with at least K pounds of feed. He can stop at any of the feed stores along the way and buy any amount of feed up to the the store's limit.

What is the minimum amount FJ has to pay to buy and transport the K pounds of feed? FJ knows there is a solution.

Consider a sample where FJ needs two pounds of feed from three stores (locations: 1, 3, and 4) on a number line whose range is 0..5:

```
0   1   2   3   4   5 
+---|---+---|---|---+ 
    1       1   1      Available pounds of feed 
    1       2   2      Cents per pound 
```
It is best for FJ to buy one pound of feed from both the second and third stores. He must pay two cents to buy each pound of feed for a total cost of 4. When FJ travels from 3 to 4 he is moving 1 unit of length and he has 1 pound of feed so he must pay 1\*1 = 1 cents.

When FJ travels from 4 to 5 he is moving one unit and he has 2 pounds of feed so he must pay 1\*2 = 2 cents.

The total cost is 4+1+2 = 7 cents. 

FJ 开车去买 $K$ 份食物，如果他的车上有 $X$ 份食物。每走一里就花费 $X$ 元。FJ 的城市是一条线，总共 $E$ 里路，有 $E+1$ 个地方，标号 $0\sim E$。 FJ 从 $0$ 开始走，到 $E$ 结束（不能往回走），要买 $K$ 份食物。 城里有 $N$ 个商店，每个商店的位置是 $X_i$（一个点上可能有多个商店），有 $F_i$ 份食物，每份 $C_i$ 元。 问到达 $E$ 并买 $K$ 份食物的最小花费。

## 说明/提示

![](https://cdn.luogu.com.cn/upload/pic/1720.png)


## 样例 #1

### 输入

```
2 5 3
3 1 2
4 1 2
1 1 1```

### 输出

```
7```

# AI分析结果



### 综合分析与结论

题目要求购买K磅饲料并运输到终点E，使总费用（购买价+运输费）最小。各题解主要采用贪心策略，将每个商店的饲料总成本计算为`c_i + (E - x_i)`，按此排序后优先购买最低成本的饲料。动态规划解法虽正确但复杂度较高，贪心策略更为高效。

### 高星题解推荐

#### 1. 幽界の冥神（5星）
**关键亮点**：
- 思路清晰，直接计算总成本并排序，贪心选择。
- 代码简洁，变量命名合理，注释明确。
- 正确性保证，时间复杂度O(n log n)。

**核心代码**：
```cpp
struct food{int val,num;}f[102]; // val为总成本
sort(f+1,f+1+n,cmp); // 按总成本排序
for(int i=1; i<=n && number>0; i++){
    ans += Min(number, f[i].num) * f[i].val; // 尽可能多买
    number -= f[i].num;
}
```

#### 2. tktp_AK（5星）
**关键亮点**：
- 结构体组织数据，逻辑清晰。
- 处理剩余需求时直接跳出循环，优化计算。
- 代码可读性强，变量命名规范。

**核心代码**：
```cpp
struct node {int x, f, c;};
sort(a+1, a+n+1, cmp); // 按总成本排序
for(int i=1; i<=n; i++){
    if(t + a[i].f > k) {
        ans += (k-t) * a[i].c; // 补足剩余需求
        break;
    }
    // 否则全买当前商店
}
```

#### 3. yezl（4星）
**关键亮点**：
- 推导公式清晰，强调总成本计算。
- 代码简洁，快速处理边界条件。
- 变量名稍简但逻辑明确。

**核心代码**：
```cpp
for(int i=1; i<=n; i++){
    ans += min(k, f[i].num) * f[i].val;
    k -= f[i].num;
    if(k <=0) break;
}
```

### 最优关键思路
**贪心策略**：将每个商店的饲料总成本计算为`c_i + (E - x_i)`（购买价+到终点的运输费），排序后优先购买总成本最低的，直至满足K磅需求。此方法正确性基于总运输费用与购买顺序无关，每个饲料的运输费用仅取决于自身位置。

### 类似题目推荐
1. **P1090 [NOIP2004 提高组] 合并果子**（贪心+优先队列）
2. **P2240 【深基12.例1】部分背包问题**（贪心选择单价高的物品）
3. **P4544 [USACO10NOV]Buying Feed G**（进阶版，需结合单调队列优化DP）

### 题解中的个人心得摘录
- **Sirius_X**提到动态规划转化为多重背包，但强调贪心更优。
- **rsdbk_husky**的DP解法虽复杂，但详细推导了状态转移，适合深入学习。
- **幽界の冥神**强调排序是贪心核心，避免未排序导致错误。

---
处理用时：211.13秒