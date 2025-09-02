# 题目信息

# Fruits

## 题目描述

The spring is coming and it means that a lot of fruits appear on the counters. One sunny day little boy Valera decided to go shopping. He made a list of $ m $ fruits he wanted to buy. If Valera want to buy more than one fruit of some kind, he includes it into the list several times.

When he came to the fruit stall of Ashot, he saw that the seller hadn't distributed price tags to the goods, but put all price tags on the counter. Later Ashot will attach every price tag to some kind of fruits, and Valera will be able to count the total price of all fruits from his list. But Valera wants to know now what can be the smallest total price (in case of the most «lucky» for him distribution of price tags) and the largest total price (in case of the most «unlucky» for him distribution of price tags).

## 样例 #1

### 输入

```
5 3
4 2 1 10 5
apple
orange
mango
```

### 输出

```
7 19
```

## 样例 #2

### 输入

```
6 5
3 5 1 6 8 1
peach
grapefruit
banana
orange
orange
```

### 输出

```
11 30
```

# AI分析结果



### 题目内容中文重写

#### 题目名称：水果

**题目描述**  
春天来了，水果摊上出现了大量水果。一个晴朗的日子，小男孩 Valera 决定去购物。他列出了一个包含 $m$ 种水果的购买清单（同种水果出现多次表示要购买多个）。当他来到 Ashot 的水果摊时，发现价格标签还未分配到水果上，而是全部堆在柜台。Ashot 稍后会将每个价格标签分配到某种水果，而 Valera 希望提前知道在最优（总价最小）和最差（总价最大）标签分配情况下的总价格。

**样例 #1**  
输入：  
```
5 3
4 2 1 10 5
apple
orange
mango
```  
输出：  
```
7 19
```

**样例 #2**  
输入：  
```
6 5
3 5 1 6 8 1
peach
grapefruit
banana
orange
orange
```  
输出：  
```
11 30
```

---

### 题解综合分析与结论

#### 核心思路
所有题解均采用**贪心算法**，关键点如下：
1. **统计频率**：统计每种水果的出现次数。
2. **双排序策略**：
   - **价格排序**：将价格从小到大排序。
   - **频率排序**：将水果出现次数从大到小排序。
3. **分配规则**：
   - 最小总价：最高频率匹配最小价格，次高频率匹配次小价格，依此类推。
   - 最大总价：最高频率匹配最大价格，次高频率匹配次大价格，依此类推。

#### 算法优化点
- **贪心策略的数学证明**：通过排序后的交叉匹配确保极值的正确性。
- **数据结构选择**：`map` 或手动去重统计频率，均能高效处理数据规模（$n,m \leq 100$）。

---

### 精选题解与评分

#### 题解1：Fido_Puppy（⭐⭐⭐⭐⭐）
**关键亮点**  
- 使用 `map` 统计频率，代码简洁高效。
- 通过分离频率到数组并排序，清晰实现贪心匹配。
- 代码可读性强，逻辑紧凑。

**核心代码**  
```cpp
map<string, int> b;
for (int i = 1; i <= m; i++) {
    cin >> s[i];
    b[s[i]]++; // 统计频率
}
sort(a + 1, a + n + 1); // 价格排序
sort(c + 1, c + len + 1, greater<int>()); // 频率降序
// 计算最小和最大总价
for (int i = 1; i <= len; i++) {
    Min += c[i] * a[i];
    Max += c[i] * a[n - i + 1];
}
```

#### 题解3：fls233666（⭐⭐⭐⭐）
**关键亮点**  
- 手动去重统计频率，避免 `map` 依赖。
- 合并循环同时计算最小和最大总价，优化代码结构。
- 明确处理题目条件（不同水果种类 ≤ n），增强鲁棒性。

**核心代码**  
```cpp
sort(cnt, cnt + len); // 频率升序（后续倒序使用）
for (int j = 0, i = len - 1; i >= 0; i--, j++) {
    minans += cnt[i] * cost[j]; // 最小总价
    maxans += cnt[i] * cost[n - j - 1]; // 最大总价
}
```

---

### 关键技巧总结
1. **贪心策略的排序匹配**：通过双排序确保极值的正确性。
2. **频率统计优化**：根据数据规模选择 `map` 或数组去重。
3. **循环合并**：在一次循环中同时计算最小和最大值，提升代码效率。

---

### 拓展与相似题目
1. **同类型题目**  
   - [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：贪心+双指针。
   - [P1209 [USACO1.3] 修理牛棚](https://www.luogu.com.cn/problem/P1209)：极值分配问题。
   - [P5019 [NOIP2018 提高组] 铺设道路](https://www.luogu.com.cn/problem/P5019)：贪心策略应用。

2. **调试心得**  
   - **去重陷阱**：需确保频率统计后不再重复处理（题解1中 `b[s[i]] = 0` 避免重复存入数组）。
   - **边界处理**：如题解3中明确题目保证不同水果种类 ≤ n，避免数组越界。

---
处理用时：50.50秒