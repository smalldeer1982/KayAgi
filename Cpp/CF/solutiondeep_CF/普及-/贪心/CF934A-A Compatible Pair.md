# 题目信息

# A Compatible Pair

## 题目描述

Nian is a monster which lives deep in the oceans. Once a year, it shows up on the land, devouring livestock and even people. In order to keep the monster away, people fill their villages with red colour, light, and cracking noise, all of which frighten the monster out of coming.

Little Tommy has $ n $ lanterns and Big Banban has $ m $ lanterns. Tommy's lanterns have brightness $ a_{1},a_{2},...,a_{n} $ , and Banban's have brightness $ b_{1},b_{2},...,b_{m} $ respectively.

Tommy intends to hide one of his lanterns, then Banban picks one of Tommy's non-hidden lanterns and one of his own lanterns to form a pair. The pair's brightness will be the product of the brightness of two lanterns.

Tommy wants to make the product as small as possible, while Banban tries to make it as large as possible.

You are asked to find the brightness of the chosen pair if both of them choose optimally.

## 说明/提示

In the first example, Tommy will hide $ 20 $ and Banban will choose $ 18 $ from Tommy and $ 14 $ from himself.

In the second example, Tommy will hide $ 3 $ and Banban will choose $ 2 $ from Tommy and $ 1 $ from himself.

## 样例 #1

### 输入

```
2 2
20 18
2 14
```

### 输出

```
252
```

## 样例 #2

### 输入

```
5 3
-1 0 1 2 3
-1 0 1
```

### 输出

```
2
```

# AI分析结果



# A Compatible Pair

## 题目描述

Nian 是一种生活在深海的怪物，每年一次会出现在陆地吞食牲畜和人类。为了防止怪物靠近，人们用红色、灯光和鞭炮声驱赶它。

Tommy 有 $n$ 个灯笼，亮度为 $a_1,a_2,...,a_n$；Banban 有 $m$ 个灯笼，亮度为 $b_1,b_2,...,b_m$。Tommy 会藏起一个灯笼，Banban 从剩余灯笼中各选一个与自己的配对，亮度为二者乘积。Tommy 希望最终结果尽可能小，Banban 希望尽可能大。求双方最优策略下的最终亮度值。

---

## 题解综合分析

### 关键思路总结
1. **暴力枚举**：遍历所有可能的隐藏元素，计算剩余元素的最大乘积，时间复杂度 $O(n^2m)$，适用于小数据。
2. **贪心优化**：利用极值性质，预处理最大/次大、最小/次小值，仅需考虑隐藏最大或最小值的情况，时间复杂度 $O(n+m)$，适用于大数据。

### 高星题解推荐

#### 题解作者：Tweetuzki（★★★★★）
**亮点**：
- 基于极值性质，仅需处理隐藏最大值或最小值的情况
- 预处理次大/次小值，避免遍历所有可能
- $O(n+m)$ 时间复杂度，高效解决大数据场景

**核心代码**：
```cpp
// 预处理最大值、次大值、最小值、次小值
for (int i = 1; i <= n; ++i) {
    llt x;
    scanf("%lld", &x);
    if (x > Max1) {
        Maxer1 = Max1;
        Max1 = x;
    } else if (x > Maxer1)
        Maxer1 = x;

    if (x < Min1) {
        Miner1 = Min1;
        Min1 = x;
    } else if (x < Miner1)
        Miner1 = x;
}

// 计算隐藏最大/最小值后的四种组合
llt ans1 = max( max(Maxer1 * Max2, Maxer1 * Min2), max(Min1 * Max2, Min1 * Min2) );
llt ans2 = max( max(Max1 * Max2, Max1 * Min2), max(Miner1 * Max2, Miner1 * Min2) );
llt ans = min(ans1, ans2);
```

#### 题解作者：StudyingFather（★★★★）
**亮点**：
- 直观暴力枚举，代码简洁易实现
- 三重循环清晰体现问题逻辑，适合快速理解题意

**核心代码**：
```cpp
for(int i=1;i<=n;i++) { // 枚举隐藏的元素
    long long now=-INF;
    for(int j=1;j<=n;j++) 
        if(j!=i)
            for(int k=1;k<=m;k++)
                now=max(now,a[j]*b[k]); // 计算当前情况的最大值
    res=min(res,now); // 取所有情况的最小值
}
```

#### 题解作者：Eason_AC（★★★★）
**亮点**：
- 代码结构简洁，变量命名清晰
- 合理处理数据范围，明确使用 `long long`

**核心代码**：
```cpp
_for(k, 1, n) { // 枚举隐藏位置
    ll maxi = -INF;
    _for(i, 1, n) _for(j, 1, m)
        if(i != k) 
            maxi = max(maxi, a[i]*b[j]);
    ans = min(ans, maxi);
}
```

---

## 扩展与心得
**同类问题套路**：博弈策略下的极值选择问题，常通过逆向思维（如对手最优策略下的最坏情况）建模。极值预处理技巧可用于优化乘积类问题。

**推荐题目**：
1. [P1053 最大公约数](https://www.luogu.com.cn/problem/P1053)（极值性质）
2. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)（极值动态规划）
3. [P1888 三角函数](https://www.luogu.com.cn/problem/P1888)（极值选择与比值优化）

**调试心得**：
- 注意乘积可能导致的数值溢出，需使用 `long long`
- 处理负数时，负负得正可能成为最大乘积，需全组合遍历
- 贪心方法需严谨证明覆盖所有情况，避免次大/次小值更新逻辑错误

---
处理用时：141.60秒