# 题目信息

# [ICPC 2019 WF] Azulejos

## 题目背景

### Warning: If you submit a malicious program, you will be banned.
### 警告：恶意提交本题将被封号。


## 题目描述

Ceramic artists Maria and João are opening a small azulejo store in Porto. Azulejos are the beautiful ceramic tiles for which Portugal is famous. Maria and João want to create an attractive window display, but, due to limited space in their shop, they must arrange their tile samples in two rows on a single shelf. Each of João's tiles has exactly one of Maria's tiles in front of it and each of Maria's tiles has exactly one of João's tiles behind it. These hand-crafted tiles are of many different sizes, and it is important that each tile in the back row is taller than the tile in front of it so that both are visible to passers-by. For the convenience of shoppers, tiles in each row are arranged in non-decreasing order of price from left to right. Tiles of the same price may be arranged in any order subject to the visibility condition stated above.

Your task is to find an ordering of the tiles in each row that satisfies these constraints, or determine that no such ordering exists.

## 说明/提示

Source: ICPC 2019 World Finals.

## 样例 #1

### 输入

```
4
3 2 1 2
2 3 4 3
2 1 2 1
2 2 1 3```

### 输出

```
3 2 4 1
4 2 1 3```

## 样例 #2

### 输入

```
2
1 2
2 3
2 8
2 1```

### 输出

```
impossible```

# AI分析结果



**算法分类**: 贪心

---

### 综合分析与结论
题目要求将两排瓷砖排列为价格非递减且后排瓷砖严格高于前排对应位置。核心难点在于如何在价格相同的区间内贪心匹配高度，确保后续仍有可行解。所有题解均采用贪心策略，结合排序和数据结构（如 `multiset`、`multimap`）实现高效匹配。

关键思路总结：
1. **按价格排序**：分别对两排瓷砖按价格排序，保证价格非递减。
2. **分治价格区间**：在同一价格区间内，动态维护瓷砖高度集合，根据当前处理的瓷砖数量选择匹配方向。
3. **贪心匹配策略**：若前排瓷砖数较少，优先处理前排并尽量让后排剩余瓷砖更小；反之处理后排，让前排剩余瓷砖更大。
4. **高效查找**：使用 `lower_bound`、`upper_bound` 快速找到满足高度条件的瓷砖。

---

### 精选题解与亮点

#### 题解作者：pufanyi（⭐⭐⭐⭐）
**关键亮点**：
- **贪心策略清晰**：根据当前处理的瓷砖数量动态选择匹配方向，确保剩余瓷砖的最优性。
- **数据结构优化**：利用 `multiset` 维护高度集合，通过 `lower_bound` 快速匹配。
- **代码简洁性**：通过循环处理价格区间，避免复杂递归，提高可读性。

**核心代码思路**：
```cpp
multiset<pii> sta, stb; // 维护当前价格区间的瓷砖
while (处理完所有瓷砖) {
    if (前排瓷砖数 < 后排瓷砖数) {
        // 从前排选最高瓷砖，在后排找比它高的最小瓷砖
        auto it = stb.lower_bound(pii((sta.rbegin())->x, 0));
        if (it == stb.begin()) return impossible;
        ansb[i] = prev(it)->y;
    } else {
        // 从后排选最低瓷砖，在前排找比它高的最小瓷砖
        auto it = sta.upper_bound(pii((stb.begin())->x, 0));
        if (it == sta.end()) return impossible;
        ansa[i] = it->y;
    }
    // 删除已匹配瓷砖，更新集合
}
```

---

### 拓展与相似题目
1. **贪心+排序+匹配**：类似问题需在有序结构中找到最优匹配，如 [CF1132F](https://www.luogu.com.cn/problem/CF1132F)。
2. **双指针与集合维护**：涉及动态维护和高效查找的题目，如 [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)。
3. **区间分治策略**：将问题分解为独立区间处理，如 [P1880 石子合并](https://www.luogu.com.cn/problem/P1880)。

---
处理用时：58.44秒