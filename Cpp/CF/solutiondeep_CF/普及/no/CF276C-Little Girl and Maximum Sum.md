# 题目信息

# Little Girl and Maximum Sum

## 题目描述

The little girl loves the problems on array queries very much.

One day she came across a rather well-known problem: you've got an array of $ n $ elements (the elements of the array are indexed starting from 1); also, there are $ q $ queries, each one is defined by a pair of integers $ l_{i} $ , $ r_{i} $ $ (1<=l_{i}<=r_{i}<=n) $ . You need to find for each query the sum of elements of the array with indexes from $ l_{i} $ to $ r_{i} $ , inclusive.

The little girl found the problem rather boring. She decided to reorder the array elements before replying to the queries in a way that makes the sum of query replies maximum possible. Your task is to find the value of this maximum sum.

## 样例 #1

### 输入

```
3 3
5 3 2
1 2
2 3
1 3
```

### 输出

```
25
```

## 样例 #2

### 输入

```
5 3
5 2 4 1 3
1 5
2 3
2 3
```

### 输出

```
33
```

# AI分析结果



# 中文题目重写

## 题目描述

小女孩非常喜欢关于数组查询的问题。有一天她遇到了一个经典问题：给定一个包含 $n$ 个元素的数组（元素索引从 1 开始），以及 $q$ 个查询，每个查询由一对整数 $l_i, r_i$ 定义（$1 \leq l_i \leq r_i \leq n$）。对于每个查询，需要计算数组中索引从 $l_i$ 到 $r_i$ 的元素之和。

小女孩觉得这个问题太简单了。她决定在回答查询前对数组元素重新排列，使得所有查询结果的总和最大化。你的任务是求出这个最大总和。

## 样例 #1

### 输入
```
3 3
5 3 2
1 2
2 3
1 3
```

### 输出
```
25
```

---

# 算法分类
**贪心 + 差分**

---

# 题解分析与结论

## 核心逻辑
- **贪心策略**：将出现频率最高的数组位置分配给最大元素，以最大化总和。
- **差分技巧**：通过差分数组高效统计每个位置被查询的频次。

## 解决难点
1. **频次统计优化**：直接暴力统计每个位置的查询次数会超时（$O(nq)$），使用差分可将时间复杂度优化至 $O(n+q)$。
2. **排序对应**：对原数组和频次数组分别排序后一一对应相乘，确保大数乘高频。

---

# 高分题解推荐（评分≥4星）

## 题解1：AKPC（★★★★★）
**关键亮点**：
- 代码简洁高效，完美结合差分与贪心
- 时间复杂度 $O(n \log n)$，空间优化到位
- 完整包含输入处理、差分计算、排序逻辑

**核心代码**：
```cpp
// 差分处理区间标记
for (int i=1;i<=m;i++) cin>>l>>r,tip[l]++,tip[r+1]--;
// 前缀和计算频次
for (int i=1;i<=n;i++) tip[i]+=tip[i-1];
// 双排序对应相乘
sort(a+1,a+n+1);
sort(tip+1,tip+n+1);
for (int i=1;i<=n;i++) ans+=tip[i]*a[i];
```

---

## 题解2：Little09（★★★★☆）
**关键亮点**：
- 逻辑清晰，变量命名规范
- 独立完成差分计算与结果统计
- 包含完整输入输出处理

**核心代码**：
```cpp
// 差分标记处理
for (int i=1;i<=m;i++) {
    int x,y;
    cin >> x >> y;
    b[x]++,b[y+1]--;
}
// 频次计算与排序
for (int i=1;i<=n;i++) b[i]+=b[i-1];
sort(b+1,b+n+1);
sort(a+1,a+n+1);
// 结果计算
for (int i=1;i<=n;i++) ans+=b[i]*a[i];
```

---

# 最优实现技巧总结
1. **差分数组应用**：
   - 使用 `tip[l]++` 和 `tip[r+1]--` 标记区间
   - 通过前缀和 `tip[i] += tip[i-1]` 计算最终频次
2. **双排序策略**：
   - 将原数组和频次数组**同向排序**（均升序或均降序）
   - 时间复杂度由排序主导 $O(n \log n)$
3. **数据类型控制**：
   - 使用 `long long` 防止结果溢出
   - 输入输出流优化（如 `ios::sync_with_stdio(false)`）

---

# 拓展与相似题目
1. **区间频次统计**：[P3406 海底高铁](https://www.luogu.com.cn/problem/P3406)
2. **贪心排序策略**：[P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. **差分进阶应用**：[P1083 借教室](https://www.luogu.com.cn/problem/P1083)

---
处理用时：53.90秒