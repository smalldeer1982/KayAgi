# 题目信息

# Sereja and Swaps

## 题目描述

As usual, Sereja has array $ a $ , its elements are integers: $ a[1],a[2],...,a[n] $ . Let's introduce notation:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF425A/32568eeb8040eb1aa136af55c788f7e656cb44a9.png)A swap operation is the following sequence of actions:

- choose two indexes $ i,j $ $ (i≠j) $ ;
- perform assignments $ tmp=a[i],a[i]=a[j],a[j]=tmp $ .

What maximum value of function $ m(a) $ can Sereja get if he is allowed to perform at most $ k $ swap operations?

## 样例 #1

### 输入

```
10 2
10 -1 2 2 2 2 2 2 -1 10
```

### 输出

```
32
```

## 样例 #2

### 输入

```
5 10
-1 -1 -1 -1 -1
```

### 输出

```
-1
```

# AI分析结果

### 题目内容重写
**Sereja and Swaps**

#### 题目描述
Sereja 有一个数组 $a$，其元素为整数：$a[1], a[2], ..., a[n]$。我们定义以下操作：

- 选择两个下标 $i, j$（$i \neq j$）；
- 执行赋值操作：$tmp = a[i], a[i] = a[j], a[j] = tmp$。

Sereja 最多可以进行 $k$ 次交换操作，求他能够得到的最大子段和 $m(a)$。

#### 样例 #1
**输入**
```
10 2
10 -1 2 2 2 2 2 2 -1 10
```
**输出**
```
32
```

#### 样例 #2
**输入**
```
5 10
-1 -1 -1 -1 -1
```
**输出**
```
-1
```

### 题解分析与结论
本题的核心在于如何通过最多 $k$ 次交换操作，使得某个子段的和最大化。大多数题解采用了暴力枚举子段并结合贪心策略的解法，即每次交换时尽可能将子段内的最小元素与子段外的最大元素交换，从而最大化子段和。

### 高星题解推荐
#### 题解1：柳易辰 (5星)
**关键亮点**：
- 提供了两种解法，第一种是暴力枚举，第二种通过 STL 优化，使用 `multiset` 和 `vector` 维护区间内外的元素，优化了时间复杂度。
- 详细解释了如何通过递推优化区间维护，减少了重复计算。
- 代码结构清晰，注释详细，易于理解。

**核心代码**：
```cpp
multiset<int> in; vector<int> out;
for (int i(l); i <= n; ++i) in.ins(a[i]);
for (int i(1); i < l; ++i) { out_ins(i); }
for (int r(n); r >= l; --r) {
    int p(0), d(b[r] - b[l - 1]);
    for (int i : in) {
        if (p == out.size()) break;
        if (out[p] <= i) break;
        d += out[p++] - i;
    }
    if (d > c) c = d;
    in.erase(in.lb(a[r]));
    out_ins(r);
}
```
**核心思想**：通过 `multiset` 维护区间内元素，`vector` 维护区间外元素，每次递推时更新区间内外的元素，减少重复计算。

#### 题解2：When (4星)
**关键亮点**：
- 使用优先队列维护区间内外的最大最小值，简化了交换操作的实现。
- 代码简洁，逻辑清晰，适合初学者理解。

**核心代码**：
```cpp
priority_queue<int, vector<int>, greater<int> > q1, kk;
priority_queue<int, vector<int>, less<int> > q2, kkk;
for (int i = 1; i <= n; ++i) {
    if (i >= l && i <= r) q1.push(a[i]);
    else q2.push(a[i]);
}
while (num -- && !q2.empty()) {
    int top = q2.top(); q2.pop();
    int ttop = q1.top();
    if (ttop >= top) break;
    q1.pop(); q1.push(top);
}
```
**核心思想**：使用优先队列维护区间内外的最大最小值，每次交换时取出区间内最小值和区间外最大值进行交换。

#### 题解3：ddmd (4星)
**关键亮点**：
- 直接模拟交换过程，通过遍历找到区间内最小值和区间外最大值进行交换。
- 代码实现简单，适合理解贪心策略。

**核心代码**：
```cpp
for (int i = 1; i <= k; i++) {
    int Min = 1e8, Max = -1e8, MIN, MAX;
    for (int i = 1; i <= n; i++) {
        if (i >= l && i <= r) { if (Min > b[i]) MIN = i, Min = b[i]; }
        else { if (Max < b[i]) MAX = i, Max = b[i]; }
    }
    if (Min < Max) swap(b[MIN], b[MAX]);
}
```
**核心思想**：通过遍历找到区间内最小值和区间外最大值进行交换，直接模拟交换过程。

### 最优关键思路
1. **贪心策略**：每次交换时，尽可能将区间内的最小元素与区间外的最大元素交换，从而最大化子段和。
2. **数据结构优化**：使用 `multiset` 和 `vector` 或优先队列来维护区间内外的元素，减少重复计算，优化时间复杂度。
3. **递推优化**：通过递推的方式更新区间内外的元素，减少重复计算，提高效率。

### 可拓展之处
- 类似问题可以通过贪心策略结合数据结构优化来解决，如使用堆、平衡树等数据结构维护区间内外的元素。
- 可以扩展到更多操作类型的问题，如旋转、翻转等操作。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)

### 个人心得摘录
- **柳易辰**：通过 STL 优化，减少了重复计算，代码实现较为复杂，但效率较高。
- **When**：优先队列的使用简化了代码实现，适合初学者理解贪心策略。
- **ddmd**：直接模拟交换过程，代码简单，适合理解贪心策略。

---
处理用时：42.48秒