# 题目信息

# [PA 2015] Kieszonkowe

## 题目描述

给定 $n$ 个数，请从中选出若干个数，使得总和为偶数。

请最大化这个总和。

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 10^6$，$1\le a_i\le 10^3$。

## 样例 #1

### 输入

```
5
2 4 3 3 3```

### 输出

```
12```

# AI分析结果



### 综合分析与结论
本题的关键在于如何将总和调整为偶数并最大化。所有题解均基于贪心策略，核心思路为：
1. **总和为偶数**时直接输出。
2. **总和为奇数**时，减去最小奇数以得到最大偶数总和。
3. **特判**：当 `n=1` 且该数为奇数时无解。

优化点在于：无需排序所有数，只需在输入时记录最小奇数，将时间复杂度从 `O(n log n)` 优化为 `O(n)`。

### 高星题解推荐
#### 1. 作者：Yukinoshita_Yukino（4星）
**关键亮点**：
- **线性时间复杂度**：在输入时直接记录最小奇数，避免排序。
- **代码简洁**：逻辑清晰，无冗余操作。
```cpp
int main() {
    int n, sum = 0, min_odd = INT_MAX;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        sum += x;
        if (x % 2 == 1 && x < min_odd) min_odd = x;
    }
    if (n == 1 && sum % 2 == 1) printf("NIESTETY");
    else printf("%d", sum % 2 == 0 ? sum : sum - min_odd);
    return 0;
}
```

#### 2. 作者：Error_Eric（4星）
**关键亮点**：
- **空间优化**：不存储数组，边读入边处理。
- **完整处理边界条件**：包括 `n=1` 的特判。
```cpp
int main() {
    int n, x, sum = 0, min_odd = INT_MAX;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        sum += x;
        if (x % 2) min_odd = std::min(min_odd, x);
    }
    if (n == 1 && sum % 2) printf("NIESTETY");
    else printf("%d", sum % 2 ? sum - min_odd : sum);
    return 0;
}
```

#### 3. 作者：ShineEternal（4星）
**关键亮点**：
- **全面性检查**：额外处理总和减为0的极端情况（虽实际数据下不可能，但体现严谨性）。
```cpp
int main() {
    int n, sum = 0, min_odd = 1001;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        sum += x;
        if (x % 2 && x < min_odd) min_odd = x;
    }
    if (n == 1 && sum % 2) printf("NIESTETY");
    else printf("%d", sum % 2 ? sum - min_odd : sum);
    return 0;
}
```

### 核心思路总结
- **贪心策略**：总和奇偶性决定是否调整，优先考虑总和最大。
- **极值优化**：记录最小奇数避免排序，保证 `O(n)` 时间复杂度。
- **边界处理**：特判 `n=1` 的唯一奇数情况。

### 拓展与同类题目
1. **奇偶性调整**：如 [P1982 小朋友的数字](https://www.luogu.com.cn/problem/P1982)。
2. **极值贪心**：如 [P6196 [NOI Online 提高组] 冒泡排序](https://www.luogu.com.cn/problem/P6196)。
3. **贪心+数学**：如 [P2114 [NOI2014] 起床困难综合症](https://www.luogu.com.cn/problem/P2114)。

### 个人心得摘录
- **Error_Eric**：“代码优化思路：从动态规划到贪心的简化，启示我们在解决问题时需不断寻找更优方案。”
- **MZY666**：“每次想到贪心都要多问正确性，避免思维漏洞。”
- **james1BadCreeper**：“处理特殊情况（如无解）时，需仔细审题，明确‘若干’的定义。”

---
处理用时：133.08秒