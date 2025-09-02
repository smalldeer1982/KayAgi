# 题目信息

# [ABC281E] Least Elements

## 题目描述

给定一个序列 $A$，对于每个 $1 \le i \le N - M + 1$，将 $A_i A_{i + 1} \cdots A_{i + M - 1}$ **从小到大**排序后（不影响原序列），求出 $\displaystyle ans_i = \sum\limits_{j=i}^{i+k-1} A_j$。

## 说明/提示

$1 \le K \le M \le N \le 2 \times 10^5$

$1 \le A_i \le 10^9$

## 样例 #1

### 输入

```
6 4 3

3 1 4 1 5 9```

### 输出

```
5 6 10```

## 样例 #2

### 输入

```
10 6 3

12 2 17 11 19 8 4 3 6 20```

### 输出

```
21 14 15 13 13```

# AI分析结果

### 题目内容重写

【题目描述】

给定一个序列 $A$，对于每个 $1 \le i \le N - M + 1$，将 $A_i A_{i + 1} \cdots A_{i + M - 1}$ **从小到大**排序后（不影响原序列），求出 $\displaystyle ans_i = \sum\limits_{j=i}^{i+k-1} A_j$。

【说明/提示】

$1 \le K \le M \le N \le 2 \times 10^5$

$1 \le A_i \le 10^9$

【样例 #1】

### 输入

```
6 4 3

3 1 4 1 5 9```

### 输出

```
5 6 10```

【样例 #2】

### 输入

```
10 6 3

12 2 17 11 19 8 4 3 6 20```

### 输出

```
21 14 15 13 13```

### 算法分类
排序、滑动窗口、数据结构（multiset/平衡树）

### 题解分析与结论

本题的核心问题是在一个滑动窗口中动态维护前 $K$ 小的元素，并计算它们的和。由于窗口大小固定，且需要频繁插入和删除元素，因此需要使用高效的数据结构来维护这些操作。常见的解法包括使用 `multiset`、平衡树、线段树等数据结构。

### 精选题解

#### 题解1：作者：hcywoi (赞：4)

**星级：★★★★★**

**关键亮点：**
- 使用两个 `multiset` 分别维护前 $K$ 小元素和剩余元素，通过滑动窗口的方式动态更新。
- 通过比较 `S1` 的最大值和 `S2` 的最小值来维护前 $K$ 小元素的有序性。
- 代码简洁，逻辑清晰，时间复杂度为 $O(n \log n)$。

**核心代码：**
```cpp
multiset<int> S1, S2;
LL res = 0;
for (int i = 1; i <= n; i++) {
    S2.insert(w[i]);
    while (S1.size() < k && S2.size()) {
        res += *S2.begin();
        S1.insert(*S2.begin());
        S2.erase(S2.begin());
    }
    while (S2.size() && (*S2.begin()) < (*S1.rbegin())) {
        res -= *S1.rbegin();
        res += *S2.begin();
        S2.insert(*S1.rbegin());
        S1.erase(S1.find(*S1.rbegin()));
        S1.insert(*S2.begin());
        S2.erase(S2.begin());
    }
    if (i >= m) {
        cout << res << ' ';
        int x = w[i - m + 1];
        if (S1.find(x) != S1.end()) {
            res -= x;
            S1.erase(S1.find(x));
        } else {
            S2.erase(S2.find(x));
        }
    }
}
```

#### 题解2：作者：FFTotoro (赞：3)

**星级：★★★★**

**关键亮点：**
- 使用 `vector` 和 `lower_bound` 来维护滑动窗口中的有序序列，通过二分查找快速插入和删除元素。
- 通过分类讨论删除和插入元素对前 $K$ 小元素和的影响，逻辑清晰。
- 时间复杂度为 $O(n \log n)$，代码实现较为简洁。

**核心代码：**
```cpp
vector<int> b;
int nowsum = 0;
for (int i = 1; i <= m; i++) b.emplace_back(a[i]);
sort(b.begin(), b.end());
for (int i = 0; i < k; i++) nowsum += b[i];
cout << nowsum << ' ';
for (int i = 1; i <= n - m; i++) {
    auto l = lower_bound(b.begin(), b.end(), a[i - 1]);
    if (l - b.begin() < k) nowsum += b[k] - *l;
    b.erase(l);
    b.insert(upper_bound(b.begin(), b.end(), a[i + m - 1]), a[i + m - 1]);
    auto r = lower_bound(b.begin(), b.end(), a[i + m - 1]);
    if (r - b.begin() < k) nowsum += a[i + m - 1] - b[k];
    cout << nowsum << ' ';
}
```

#### 题解3：作者：wizardMarshall (赞：0)

**星级：★★★★**

**关键亮点：**
- 使用两个 `set` 分别维护前 $K$ 小元素和剩余元素，通过滑动窗口的方式动态更新。
- 通过比较 `st` 的最大值和 `ss` 的最小值来维护前 $K$ 小元素的有序性。
- 代码简洁，逻辑清晰，时间复杂度为 $O(n \log n)$。

**核心代码：**
```cpp
set<int> st, ss;
int nowsum = 0;
for (int i = 1; i <= m; i++) {
    t[i] = a[i];
}
sort(t + 1, t + m + 1);
for (int i = 1; i <= k; i++) {
    nowsum += t[i];
    st.insert(t[i]);
}
for (int i = k + 1; i <= m; i++) {
    ss.insert(t[i]);
}
cout << nowsum << " ";
for (int i = 2; i <= n - m + 1; i++) {
    if (!st.empty() && a[i - 1] <= *(--st.end())) {
        st.erase(st.lower_bound(a[i - 1]));
        nowsum -= a[i - 1];
    } else if (!ss.empty()) {
        ss.erase(ss.lower_bound(a[i - 1]));
    }
    if (!st.empty() && a[i + m - 1] < *(--st.end())) {
        st.insert(a[i + m - 1]);
        nowsum += a[i + m - 1];
    } else {
        ss.insert(a[i + m - 1]);
    }
    if (st.size() > k) {
        nowsum -= *(--st.end());
        ss.insert(*(--st.end()));
        st.erase((--st.end()));
    } else if (!ss.empty() && st.size() < k) {
        nowsum += *ss.begin();
        st.insert(*ss.begin());
        ss.erase(ss.begin());
    }
    printf("%lld ", nowsum);
}
```

### 最优关键思路与技巧

1. **数据结构选择**：使用 `multiset` 或 `set` 来维护前 $K$ 小元素和剩余元素，能够高效地进行插入、删除和查找操作。
2. **滑动窗口**：通过滑动窗口的方式动态更新窗口内的元素，避免重复排序。
3. **有序性维护**：通过比较 `S1` 的最大值和 `S2` 的最小值，确保前 $K$ 小元素的有序性。

### 可拓展之处

类似的问题可以扩展到其他滑动窗口问题，如求滑动窗口的中位数、最大值等。可以使用类似的数据结构（如堆、平衡树）来维护窗口内的元素。

### 推荐题目

1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)

---
处理用时：49.05秒