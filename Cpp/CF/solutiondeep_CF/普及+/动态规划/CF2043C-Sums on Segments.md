# 题目信息

# Sums on Segments

## 题目描述

### 题目内容
给定一个长度为 $n$ 的数组 $a$，其中除了至多一个 $i \in [0,n)$ 满足 $|a_i| \neq 1$ 以外，其余全部项均满足 $|a_i|=1$。

求该数组中全部可能的子数组和，以升序输出。子数组是原数组中一段连续的数组。

## 样例 #1

### 输入

```
5
5
1 -1 10 1 1
5
-1 -1 -1 -1 -1
2
-1 2
2
7 1
3
1 4 -1```

### 输出

```
8
-1 0 1 2 9 10 11 12 
6
-5 -4 -3 -2 -1 0 
4
-1 0 1 2 
4
0 1 7 8 
6
-1 0 1 3 4 5```

# AI分析结果

### 题目内容重写

#### 题目描述
给定一个长度为 $n$ 的数组 $a$，其中除了至多一个 $i \in [0,n)$ 满足 $|a_i| \neq 1$ 以外，其余全部项均满足 $|a_i|=1$。

求该数组中全部可能的子数组和，以升序输出。子数组是原数组中一段连续的数组。

### 题解分析与结论

#### 综合分析
本题的核心在于如何处理数组中至多一个特殊值（$|a_i| \neq 1$）对子数组和的影响。大多数题解采用了分治的思想，将问题分为处理不包含特殊值的区间和包含特殊值的区间。对于不包含特殊值的区间，子数组和的范围可以通过最大子段和和最小子段和来确定；对于包含特殊值的区间，则需要结合特殊值左右的前缀和后缀和来计算。

#### 最优关键思路
1. **分治思想**：将数组分为不包含特殊值的区间和包含特殊值的区间，分别处理。
2. **最大最小子段和**：通过计算区间的最大子段和和最小子段和，确定子数组和的范围。
3. **前缀和后缀和**：对于包含特殊值的区间，利用前缀和后缀和来计算可能的子数组和。

#### 可拓展之处
类似的问题可以通过分治思想来解决，特别是当数组中存在少量特殊值时。此外，最大最小子段和的计算方法在解决连续子数组和的问题中也非常常见。

### 推荐题目
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
2. [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)
3. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)

### 所选高星题解

#### 题解1：作者：Eous (5星)
**关键亮点**：
- 清晰的分治思路，将问题分为不包含特殊值的区间和包含特殊值的区间。
- 详细证明了在只包含 $\pm1$ 的区间中，子数组和的范围是连续的。
- 代码结构清晰，逻辑严谨。

**核心代码**：
```cpp
void solve() {
    cin >> n;
    pos = val = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] != 1 && a[i] != -1) {
            val = a[i];
            pos = i;
        }
    }
    max1 = min1 = 0;
    fill(dp1 + 1, dp1 + n + 1, 0);
    fill(dp2 + 1, dp2 + n + 1, 0);
    for (int i = 1; i <= pos - 1; i++) {
        dp1[i] = max(dp1[i - 1] + a[i], 0ll);
        max1 = max(max1, dp1[i]);
        dp2[i] = min(dp2[i - 1] + a[i], 0ll);
        min1 = min(min1, dp2[i]);
    }
    max2 = min2 = 0;
    fill(dp1 + 1, dp1 + n + 1, 0);
    fill(dp2 + 1, dp2 + n + 1, 0);
    for (int i = pos + 1; i <= n; i++) {
        dp1[i] = max(dp1[i - 1] + a[i], 0ll);
        max2 = max(max2, dp1[i]);
        dp2[i] = min(dp2[i - 1] + a[i], 0ll);
        min2 = min(min2, dp2[i]);
    }
    set<int> ans;
    for (int i = min(min1, min2); i <= max(max1, max2); i++)
        ans.insert(i);
    max1 = min1 = sum = 0;
    for (int i = pos - 1; i >= 1; i--) {
        sum += a[i];
        max1 = max(max1, sum);
        min1 = min(min1, sum);
    }
    max2 = min2 = sum = 0;
    for (int i = pos + 1; i <= n; i++) {
        sum += a[i];
        max2 = max(max2, sum);
        min2 = min(min2, sum);
    }
    for (int i = (min1 + min2); i <= (max1 + max2); i++)
        ans.insert(val + i);
    cout << ans.size() << endl;
    for (auto i : ans)
        cout << i << " ";
    cout << endl;
}
```

#### 题解2：作者：HetmesAskalana (4星)
**关键亮点**：
- 使用STL集合自动去重和排序，简化了代码实现。
- 通过维护当前值域的上下界来处理子数组和的范围。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
void solve() {
    int n, k = -1;
    cin >> n;
    vector<int> a(n);
    set<int> R = {0};
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        R.insert(a[i]);
        if (abs(a[i]) != 1) k = i;
    }
    if (k != -1) {
        merge(R, mm(a, 0, k - 1));
        merge(R, mm(a, k + 1, n - 1));
        merge(R, mx(a, k));
    } else merge(R, mm(a, 0, n - 1));
    cout << R.size() << endl;
    for (auto i : R)
        cout << i << " ";
    cout << endl;
}
```

#### 题解3：作者：wfc284 (4星)
**关键亮点**：
- 通过扩展和收缩的思想，证明了子数组和的连续性。
- 代码实现简洁，逻辑清晰。

**核心代码**：
```cpp
void work(int *a, int n) {
    int x = 0, y = 0;
    int mx = 0, mn = 0;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += a[i];
        mx = max(mx, sum - y);
        mn = min(mn, sum - x);
        x = max(x, sum);
        y = min(y, sum);
    }
    for (int i = mn; i <= mx; i++) ans.push_back(i);
}
```

### 个人心得总结
在处理包含特殊值的问题时，分治思想非常有效。通过将问题分解为多个子问题，可以简化复杂度的计算和代码的实现。此外，维护当前值域的上下界是解决连续子数组和问题的常用技巧。

---
处理用时：57.05秒