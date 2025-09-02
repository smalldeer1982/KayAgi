# 题目信息

# Hacker, pack your bags!

## 题目描述

It's well known that the best way to distract from something is to do one's favourite thing. Job is such a thing for Leha.

So the hacker began to work hard in order to get rid of boredom. It means that Leha began to hack computers all over the world. For such zeal boss gave the hacker a vacation of exactly $ x $ days. You know the majority of people prefer to go somewhere for a vacation, so Leha immediately went to the travel agency. There he found out that $ n $ vouchers left. $ i $ -th voucher is characterized by three integers $ l_{i} $ , $ r_{i} $ , $ cost_{i} $ — day of departure from Vičkopolis, day of arriving back in Vičkopolis and cost of the voucher correspondingly. The duration of the $ i $ -th voucher is a value $ r_{i}-l_{i}+1 $ .

At the same time Leha wants to split his own vocation into two parts. Besides he wants to spend as little money as possible. Formally Leha wants to choose exactly two vouchers $ i $ and $ j $ $ (i≠j) $ so that they don't intersect, sum of their durations is exactly $ x $ and their total cost is as minimal as possible. Two vouchers $ i $ and $ j $ don't intersect if only at least one of the following conditions is fulfilled: $ r_{i}&lt;l_{j} $ or $ r_{j}&lt;l_{i} $ .

Help Leha to choose the necessary vouchers!

## 说明/提示

In the first sample Leha should choose first and third vouchers. Hereupon the total duration will be equal to $ (3-1+1)+(6-5+1)=5 $ and the total cost will be $ 4+1=5 $ .

In the second sample the duration of each voucher is $ 3 $ therefore it's impossible to choose two vouchers with the total duration equal to $ 2 $ .

## 样例 #1

### 输入

```
4 5
1 3 4
1 2 5
5 6 1
1 2 4
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 2
4 6 3
2 4 1
3 5 4
```

### 输出

```
-1
```

# AI分析结果



### 中文题目重写

#### 题目名称：黑客，打包你的行李！

#### 题目描述

众所周知，分散注意力的最好方法就是做自己喜欢的事。对于Leha来说，工作就是这样的事。

于是这位黑客开始努力工作以摆脱无聊。这意味着Leha开始攻击全世界的计算机。由于这种热情，老板给了Leha恰好 $x$ 天的假期。你知道大多数人喜欢去某个地方度假，所以Leha立即去了旅行社。在那里他发现还剩 $n$ 张优惠券。第 $i$ 张优惠券由三个整数 $l_i$、$r_i$、$cost_i$ 描述——离开Vičkopolis的日期、返回Vičkopolis的日期以及对应优惠券的费用。第 $i$ 张优惠券的持续时间为 $r_i - l_i + 1$。

同时Leha希望将自己的假期分成两部分。此外，他希望尽可能少花钱。正式地说，Leha希望选择恰好两张优惠券 $i$ 和 $j$（$i \neq j$），使得它们不相交，它们的持续时间之和恰好为 $x$，且总费用尽可能小。如果满足以下至少一个条件，则称两张优惠券 $i$ 和 $j$ 不相交：$r_i < l_j$ 或 $r_j < l_i$。

帮助Leha选择所需的优惠券！

#### 输入输出格式

（输入输出格式与样例保持原样，此处略）

---

**算法分类**：排序 + 二分

---

### 题解综合分析

#### 关键思路总结
1. **排序预处理**：将所有区间按左端点排序，便于后续查找不重叠区间
2. **长度分桶优化**：维护一个最小值数组`Min[len]`，记录各长度区间的最小费用
3. **离线查询处理**：将每个区间的查询需求预处理后按右端点倒序处理，保证不重叠条件
4. **二分加速查找**：使用二分/倍增法快速定位第一个满足条件的区间位置

#### 优质题解推荐

**1. MuYC 题解（⭐⭐⭐⭐⭐）**
- **核心亮点**：
  - 巧妙的离线处理：将查询按右端点倒序处理，与扫描过程完美配合
  - 倍增法优化二分：使用`log2(n)`次跳跃代替传统二分
  - 空间换时间策略：通过维护`Min`数组实现O(1)查询
- **关键代码**：
```cpp
// 预处理查询区间
for(int i = 1 ; i <= n ; i ++) {
    int lena = T[i].r - T[i].l + 1;
    if(lena >= m) continue;
    // 使用倍增法查找第一个l > r_i的区间
    int K = n + 1;
    for(int j = log2(n - i + 1) ; j >= 0 ; j --)
        if(T[K - (1 << j)].l > T[i].r) K -= (1 << j);
    // 记录该区间的查询需求
    C[i] = {K, T[i].cost, m - lena};
}

// 离线处理查询
sort(C + 1, C + 1 + n, cmp1);
int now = 1;
for(int i = n ; i >= 1 ; i --) {
    // 维护Min数组
    int len = T[i].r - T[i].l + 1;
    Min[len] = min(Min[len], T[i].cost);
    // 处理所有当前右端点的查询
    while(C[now].L == i) {
        Ans = min(Ans, C[now].D + Min[C[now].F]);
        now++;
    }
}
```

**2. AC_love 题解（⭐⭐⭐⭐）**
- **核心亮点**：
  - 动态数组维护：按长度分桶存储区间，每个桶内按右端点排序
  - 前缀最小值优化：通过维护前缀最小值数组实现快速查询
  - 二分定位边界：在对应长度桶中二分查找满足条件的区间
- **关键代码**：
```cpp
// 按左端点排序
sort(s + 1, s + 1 + n, cmp);

for(int i = 1; i <= n; i++) {
    // 处理当前区间
    int len = s[i].r - s[i].l + 1;
    int target = m - len;
    // 二分查找满足条件的区间
    int l = 0, r = v[target].size() - 1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(v[target][mid].r < s[i].l) l = mid + 1;
        else r = mid - 1;
    }
    // 更新答案
    if(r >= 0) ans = min(ans, s[i].cost + minn[target][r]);
    // 更新当前长度的桶
    v[len].push_back(s[i]);
    minn[len].push_back(min(minn[len].back(), s[i].cost));
}
```

---

### 思维拓展
1. **同类问题**：处理区间不重叠问题时，可以考虑按端点排序后离线处理
2. **优化套路**：维护分桶最小值数组是处理多条件查询的常用技巧
3. **算法迁移**：此方法可应用于需要"前后时序关系+属性匹配"的问题，如任务调度、区间覆盖等

### 推荐练习
1. [P1712 [NOI2016]区间](https://www.luogu.com.cn/problem/P1712) —— 区间覆盖与选择问题
2. [P2161 [SHOI2009]会场预约](https://www.luogu.com.cn/problem/P2161) —— 区间冲突管理
3. [P2894 [USACO08FEB]Hotel G](https://www.luogu.com.cn/problem/P2894) —— 区间分配与维护

---
处理用时：96.46秒