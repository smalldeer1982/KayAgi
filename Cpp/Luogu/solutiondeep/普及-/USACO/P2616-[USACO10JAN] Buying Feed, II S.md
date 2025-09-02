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



### 题解分析与总结
本题核心在于将运输费用与购买费用合并计算，转化为贪心问题。正确解法是将每个商店的总成本视为（到终点的距离 + 单价），按总成本排序后优先购买最低价的饲料。动态规划解法虽可行但复杂度较高，贪心算法更优。

---

### 精选题解推荐

#### 1. 幽界の冥神（5星）
**关键亮点**：  
- 简洁的贪心思路，正确计算总成本 `s - x_i + c_i`。  
- 代码清晰，排序后线性贪心选取，时间复杂度 O(n log n)。  
**核心代码**：
```cpp
struct food{int val,num;};
bool cmp(food a,food b){return a.val<b.val;}
int main(){
    // 输入处理
    for(int i=1;i<=n;i++) f[i].val = s - a_i + c_i;
    sort(f+1,f+1+n,cmp);
    for(int i=1; i<=n && K>0; i++){
        ans += min(K, f[i].num) * f[i].val;
        K -= f[i].num;
    }
}
```

#### 2. tktp_AK（5星）
**关键亮点**：  
- 结构体排序逻辑相同，变量命名更易理解。  
- 处理剩余量时更直观，使用累计变量 `t` 跟踪已购数量。  
**核心代码**：
```cpp
struct node{int x,f,c;};
sort(a+1,a+n+1,cmp); // 按c+e-x排序
long long ans=0, t=0;
for(int i=1; i<=n; i++){
    if(t + a[i].f >k) ans += (k-t)*a[i].c;
    else ans += a[i].f*a[i].c;
    t += a[i].f;
}
```

#### 3. Sirius_X（4星）
**关键亮点**：  
- 提供动态规划视角，转化为多重背包问题。  
- 状态转移方程清晰，适合理解不同思路。  
**核心代码**：
```cpp
int dp[105] = {INF};
for(int i=1; i<=n; i++){
    for(int j=k; j>=1; j--){
        for(int l=1; l<=f; l++){
            dp[j] = min(dp[j], dp[j-l] + l*(c + e -x));
        }
    }
}
```

---

### 最优思路提炼
**核心技巧**：将运输费用提前计算到单价中，通过排序实现贪心选择。  
**正确性证明**：每个饲料的总成本 = 购买价 + 从商店到终点的运费，因此全局最优可通过局部最优（选最小总成本）实现。

---

### 同类题目推荐
1. **P1090 [NOIP2004 提高组] 合并果子** - 贪心+优先队列。  
2. **P4544 [USACO10NOV]Buying Feed G** - 进阶版，需单调队列优化DP。  
3. **P1208 [USACO1.3]混合牛奶 Mixing Milk** - 类似贪心策略，按单价排序。

---

### 题解心得摘录
- **幽界の冥神**：强调“贪心必配合排序”，提醒注意贪心的常见实现方式。  
- **rsdbk_husky**：指出动态规划中状态设计的难点，强调滚动数组优化空间。  
- **Sirius_X**：通过背包模型转化，展示不同算法的适用场景。

---
处理用时：72.85秒