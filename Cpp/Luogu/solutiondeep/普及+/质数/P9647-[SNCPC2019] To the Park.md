# 题目信息

# [SNCPC2019] To the Park

## 题目描述

宝宝和他的 $(n-1)$ 个同学要去公园。为了方便，他们的老师梦想格子将学生从 1 到 $n$ 编号，并决定将学生分成一些小组，每组恰好由两个学生组成。

由于某种原因，梦想格子要求同组的两个学生的编号必须有一个大于 1 的公约数。注意，每个学生最多只能属于一个小组，并且不需要每个学生都属于一个小组。

请帮助梦想格子组成尽可能多的小组。

## 样例 #1

### 输入

```
3
1
4
6
```

### 输出

```
0
1 2 4
2 2 4 3 6
```

# AI分析结果

### 综合分析与结论

本题的核心问题是将学生分成尽可能多的小组，要求同组学生的编号有大于1的公约数。题解的关键在于如何高效地构造符合条件的小组，并确保每个学生最多只属于一个小组。

通过对题解的分析，发现以下关键思路：
1. **素数处理**：素数的倍数可以作为配对的基础，尤其是奇素数的倍数。
2. **偶数优先配对**：偶数之间可以直接配对，因为它们都有公约数2。
3. **贪心策略**：从大到小处理素数，确保每个学生尽可能被配对。

### 所选题解

#### 题解1：SDLTF_凌亭风 (4星)
**关键亮点**：
- **素数筛法**：使用线性筛法预处理素数，确保效率。
- **贪心构造**：从大到小处理素数，优先配对奇素数的倍数，再处理偶数。
- **代码清晰**：逻辑清晰，代码结构合理，易于理解。

**个人心得**：
- 提到线性筛不能只筛到$10^5$，否则会出问题，提醒了在处理边界条件时的注意事项。

**核心代码**：
```cpp
inline void solve() {
    n = read();
    if (n <= 3) return (void)puts("0");
    v.clear(), v2.clear(), c[1] = 1;
    for (register int i = 2; i <= n; i++) c[i] = 0;
    for (register int i = 1; prime[i] <= n; i++) prime[i] > (n >> 1) ? (c[prime[i]] = 1) : 1;
    for (register int i = (n >> 1); i >= 3; i--) {
        if (np[i]) continue;
        v2.push_back(i);
        for (register int j = 3; j * i <= n; j++) !c[j * i] ? (void)v2.push_back(j * i) : (void)1;
        v2.size() & 1 ? (void)v2.push_back(i << 1) : (void)1;
        for (register int j = 0; j < v2.size() - 1; j += 2) {
            x = v2[j], y = v2[j + 1], v.push_back(make_pair(x, y)), c[x] = c[y] = 1;
        }
        v2.clear();
    }
    for (register int i = 1; i <= n; i++) !c[i] ? (void)v2.push_back(i) : (void)1;
    for (register int i = 0; i < v2.size() - 1; i += 2) {
        x = v2[i], y = v2[i + 1], v.push_back(make_pair(x, y)), c[x] = c[y] = 1;
    }
    printf("%d ", res = v.size());
    for (register int i = 0; i < res; i++) {
        printf("%d %d", v[i].first, v[i].second);
        i != res - 1 ? putchar(' ') : 1;
    }
    puts("");
}
```

### 最优关键思路与技巧
1. **素数筛法**：预处理素数，确保后续配对的高效性。
2. **贪心策略**：从大到小处理素数，优先配对奇素数的倍数，再处理偶数。
3. **边界处理**：注意线性筛的范围，避免边界条件导致的错误。

### 可拓展之处
- **类似问题**：可以扩展到其他需要分组且组内元素有特定关系的题目，如分组求和、分组求积等。
- **算法套路**：贪心策略和素数筛法在多种组合优化问题中都有广泛应用。

### 推荐题目
1. [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)
2. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
3. [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)

---
处理用时：31.22秒