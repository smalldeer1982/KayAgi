# 题目信息

# [入门赛 #10] Coin Selection G（hard version）

## 题目描述

Farmer John 和 Bessie 正在一起玩硬币选择游戏。

初始时桌面上有 $n$ 枚硬币，每枚硬币有一个面额，我们使用 $a _ 1, a _ 2, \cdots, a _ n$ 分别代表第 $1, 2, \cdots, n$ 枚硬币的面额。

他们还各有一个属于自己的钱包，初始时，钱包都是空的。

从 **Bessie** 开始，双方轮流操作。每次操作中，当前的操作者会从桌面上剩余的硬币中选择**面值不超过当前自己钱包中硬币的总面额**的硬币中**面额最大的**一枚硬币，把它从桌子上拿走，放到自己的钱包里。如果桌面上剩余的**所有**硬币面值都**超过了自己钱包里已有硬币的总面额**，那么选择剩余的所有硬币中面额**最小**的一个。

当桌面上没有硬币时，游戏结束。

请你分别求出，	游戏结束后，Farmer John 和 Bessie 钱包里硬币的总面额。

## 说明/提示

### 数据规模与约定

- 对 $100\%$ 的数据，保证 $1 \leq n \leq 10^5$，$1 \leq a_i \leq 10^{9}$。

Provider：一扶苏一

## 样例 #1

### 输入

```
2
3 2```

### 输出

```
2 3```

## 样例 #2

### 输入

```
5
1 2 3 4 5```

### 输出

```
9 6```

# AI分析结果



### 算法分类
二分

### 题解分析与结论
题目核心在于动态维护有序硬币集合，并快速找到每次操作对应的硬币。所有题解均采用排序 + 二分查找的思路，但数据结构选择不同：
- **主流解法**（如 GeorgeAAAADHD、Huangjy88）使用 `vector` 存储排序后的硬币，通过二分查找目标位置后直接删除。尽管 `vector.erase()` 的时间复杂度理论上是 O(n)，但实际可能因数据分布或优化（如优先删除尾部元素）通过测试。
- **高阶解法**（如 Wangjunhao2011）采用 `set` + `map` 组合，利用平衡树特性实现 O(log n) 的查找和删除，严格满足时间要求，但代码复杂度较高。

### 高分题解推荐
1. **GeorgeAAAADHD（4 星）**
   - **亮点**：代码简洁，二分逻辑清晰，利用迭代器直接定位删除位置。
   - **代码核心**：
     ```cpp
     void add(long long &sum) {
         int l = 0, r = a.size() - 1, ans = 0, x = 0;
         while (l <= r) {  // 二分查找最大可取的硬币
             int mid = (l + r) / 2;
             if (a[mid] <= sum) { x = mid; ans = a[mid]; l = mid + 1; }
             else r = mid - 1;
         }
         if (!ans) {  // 无符合则取最小
             sum += a[0];
             a.erase(a.begin());
         } else {     // 删除目标硬币
             sum += a[x];
             a.erase(a.begin() + x);
         }
     }
     ```

2. **Huangjy88（4 星）**
   - **亮点**：使用 `upper_bound` 简化二分流程，代码更简短。
   - **核心实现**：
     ```cpp
     if (res[k] < a[0]) {  // 取最小的情况
         res[k] += a[0];
         a.erase(a.begin());
     } else {
         int m = upper_bound(a.begin(), a.end(), res[k]) - a.begin();
         res[k] += a[m - 1];  // upper_bound 前一个即为最大值
         a.erase(a.begin() + m - 1);
     }
     ```

3. **Wangjunhao2011（5 星）**
   - **亮点**：采用 `set` + `map` 实现严格 O(n log n)，避免 vector 的线性删除。
   - **关键代码**：
     ```cpp
     set<int>::iterator it = s.lower_bound(x);
     if (*it != x) it--;  // 调整迭代器到合法位置
     mp[*it]--;           // 维护计数
     if (mp[*it] == 0) s.erase(it);  // 动态删除空值
     ```

### 关键思路总结
1. **排序预处理**：所有硬币按升序排列，便于后续二分操作。
2. **二分查找优化**：利用 `upper_bound` 或手写二分快速定位目标硬币。
3. **动态维护策略**：优先选择时间复杂度更优的数据结构（如 `set`），若允许近似解则用 `vector` 的快速首尾删除。

### 拓展与举一反三
- **类似问题**：动态集合最值查询（如 [CF702F](https://codeforces.com/problemset/problem/702/F)）。
- **推荐练习**：
  1. [P1177 快速排序](https://www.luogu.com.cn/problem/P1177)（排序基础）
  2. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)（二分优化 DP）
  3. [P3380 二逼平衡树](https://www.luogu.com.cn/problem/P3380)（平衡树综合应用）

### 调试心得摘录
- **HDZmessi**：原代码因在循环中重复查找元素导致 TLE，优化为记录迭代器后 AC。
- **Wangjunhao2011**：强调 `multiset` 无法处理重复元素删除，需用 `map` 辅助计数。

---
处理用时：171.01秒