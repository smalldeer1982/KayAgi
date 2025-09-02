# 题目信息

# [USACO11JAN] Dividing the Gold S

## 题目描述

Bessie and Canmuu found a sack of N (1 <= N <= 250) gold coins that they wish to divide as evenly as possible. Coin i has value v\_i (1 <= V\_i <= 2,000). The cows would like to split the pile as evenly as they can, but that is not always possible. What is the smallest difference between the values of the two piles?

In addition, the Bessie and Canmuu have found that there might be multiple ways to split the piles with that minimum difference. They would also like to know the number of ways to split the coins as fairly as possible. If it isn't possible to split the piles evenly, Bessie will get the higher-valued pile.

By way of example, consider a sack of five coins of values: 2, 1, 8, 4, and 16. Bessie and Canmuu split the coins into two piles, one pile with one coin worth 16, and the other pile with the remaining coins worth 1+2+4+8=15. Therefore the difference is 16-15 = 1.  This is the only way for them to split the coins this way, so the number of ways to split it evenly is just 1.

Note that same-valued coins can be switched among the piles to increase the number of ways to perform an optimal split. Thus, the set of coins {1, 1, 1, 1} has six different ways to split into two optimal partitions, each with two coins.

## 样例 #1

### 输入

```
5 
2 
1 
8 
4 
16 
```

### 输出

```
1 
1 
```

# AI分析结果



**算法分类**: 动态规划

---

### 综合分析与结论
本题要求将金币分为差值最小的两堆并统计方案数，核心解法为动态规划：
1. **最小差值**：转化为背包问题，求总和一半内的最大可组合值
2. **方案统计**：在背包过程中维护方案数，注意模数下的零值陷阱
3. **优化关键**：同时维护可达性数组避免模运算干扰，降维优化空间

---

### 高星题解推荐

#### 1. 作者：DengDuck（4星）
**关键亮点**：
- 使用双数组维护可达性（`vis[]`）和方案数（`dp[]`）
- 倒序查找确保最优解
- 代码简洁高效，时间复杂度 O(n·sum)

**核心代码**：
```cpp
for(int i=1;i<=n;i++) {
    for(int j=sum/2;j>=a[i];j--) {
        dp[j] = (dp[j] + dp[j-a[i]]) % Mod;
        vis[j] |= vis[j-a[i]];
    }
}
// 倒序查找第一个可达值
for(int i=sum/2;i>=0;i--) {
    if(vis[i]) {
        cout << sum-2*i << endl << dp[i];
        return 0;
    }
}
```

#### 2. 作者：妖怪i（4星）
**关键亮点**：
- 分步解决两个问题，逻辑清晰
- 共享物品循环结构，代码复用率高
- 使用滚动数组优化空间

**核心实现**：
```cpp
// 第一问：求最大可组合值
for(int i=1;i<=n;i++)
    for(int j=sum;j>=a[i];j--)
        f[j] = max(f[j], f[j-a[i]]+a[i]);

// 第二问：统计方案数
dp[0] = 1;
for(int i=1;i<=n;i++)
    for(int j=tot;j>=a[i];j--)
        dp[j] = (dp[j] + dp[j-a[i]])%mod;
```

#### 3. 作者：荣耀南冥（4星）
**关键亮点**：
- 处理特殊测试用例（如Hack数据）
- 引入中间变量`mid`优化搜索范围
- 显式处理转移条件提升正确性

**调试心得**：
> "当转移到`f[mid]`时，`num[mid - w[i]]`可能仍为0，需将`mid`与单个物品最大值取max"

---

### 关键思路总结
1. **双背包结构**：先求最优值再统计方案，共享物品遍历过程
2. **可达性验证**：使用`vis[]`数组避免模运算导致的假零值
3. **降维优化**：逆序更新保证状态独立性，空间复杂度 O(sum)
4. **边界处理**：总和奇偶性不影响解法，倒序查找首个可行解

---

### 拓展练习
1. [P1048 采药](https://www.luogu.com.cn/problem/P1048) - 基础01背包
2. [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164) - 求方案数的背包变种
3. [P4133 能量项链](https://www.luogu.com.cn/problem/P4133) - 多维背包+组合方案统计

---

### 个人心得摘录
"**方案数被模成0时需要额外处理可达性**" —— 当方案数取模后可能丢失有效解，通过独立维护可达性数组可避免此问题。  
"**中间值与最大值取max防止转移失效**" —— 处理单个大体积物品时需调整搜索范围，保证状态转移有效性。

---
处理用时：54.36秒