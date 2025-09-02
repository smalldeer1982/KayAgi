# 题目信息

# [USACO08DEC] Patting Heads S

## 题目描述

It's Bessie's birthday and time for party games! Bessie has instructed the N (1 <= N <= 100,000) cows conveniently numbered 1..N to sit in a circle (so that cow i [except at the ends] sits next to cows i-1 and i+1; cow N sits next to cow 1). Meanwhile, Farmer John fills a barrel with one billion slips of paper, each containing some integer in the range 1..1,000,000.

Each cow i then draws a number A\_i (1 <= A\_i <= 1,000,000) (which is not necessarily unique, of course) from the giant barrel.  Taking turns, each cow i then takes a walk around the circle and pats the heads of all other cows j such that her number A\_i is exactly

divisible by cow j's number A\_j; she then sits again back in her original position.

The cows would like you to help them determine, for each cow, the number of other cows she should pat.



## 说明/提示

The 5 cows are given the numbers 2, 1, 2, 3, and 4, respectively.


The first cow pats the second and third cows; the second cows pats no cows; etc.


## 样例 #1

### 输入

```
5 
2 
1 
2 
3 
4 
```

### 输出

```
2 
0 
2 
1 
3 
```

# AI分析结果



### 综合分析与结论
本题核心在于高效统计每个数的倍数出现次数。暴力枚举不可行，最优解法采用 **倍数枚举法**：预处理每个数的出现次数，遍历每个数的倍数累积答案。时间复杂度为 O(M log M)，其中 M 为最大数值。该方法利用调和级数特性，显著优于因数枚举法（O(N√A)）。

---

### 精选题解与评分

#### 题解1：AMSDE（★★★★★）
**亮点**：思路清晰，代码简洁，时间复杂度最优。通过预处理+倍数遍历高效统计答案。  
**核心思路**：
```cpp
for (int i=1; i<=Max; i++) {
    if (num[i]==0) continue;
    for (int j=i; j<=Max; j+=i)
        ans[j] += num[i]; // 累加倍数
}
printf("%d\n", ans[a[i]]-1); // 减去自身
```

#### 题解2：Aragron_II（★★★★★）
**亮点**：代码精简，直接处理最大数值范围，逻辑明确。  
**关键代码**：
```cpp
for(int i=1; i<=Bignumber; i++) 
    for(int j=i; j<=Bignumber; j+=i)
        w[j] += c[i]; // 倍数贡献统计
```

#### 题解3：Garrison（★★★★☆）
**亮点**：优化重复数字处理，强调桶计数的重要性。  
**心得**：提到“重复数字一次性处理”优化，避免逐次累加。

---

### 关键思路总结
1. **桶计数预处理**：统计每个数的出现次数。
2. **倍数遍历代替因数枚举**：对每个数 i，遍历其倍数 j，累加贡献至 ans[j]。
3. **去重与减一处理**：最终答案需减去自身的一次计数。

---

### 拓展与举一反三
- **同类问题**：统计因数出现次数、区间内倍数数量等问题均可采用类似方法。
- **优化思维**：当需要处理大量数的因数/倍数关系时，优先考虑调和级数遍历法。

---

### 推荐练习题
1. [P1403 约数研究](https://www.luogu.com.cn/problem/P1403)（倍数统计应用）
2. [P2424 约数和](https://www.luogu.com.cn/problem/P2424)（因数贡献累积）
3. [P3383 线性筛素数](https://www.luogu.com.cn/problem/P3383)（倍数遍历思想）

---

### 题解中的调试心得
- **减一处理**：多篇题解强调 `ans[a[i]]-1`，避免统计自身。
- **完全平方数特判**：因数枚举法中需避免重复累加平方根。
- **数据范围优化**：如 AMSDE 动态计算 Max 提升效率，避免无效循环。

---
处理用时：65.22秒