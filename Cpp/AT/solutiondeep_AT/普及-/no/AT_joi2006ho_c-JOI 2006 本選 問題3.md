# 题目信息

# JOI 2006 本選 問題3

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2006ho/tasks/joi2006ho_c

# AI分析结果

### 题目内容重写
【题目描述】
将一个自然数 $n$ 拆分成若干个 $\le n$ 的正整数之和，序列中的数字**从大到小**排序，输出顺序也按照**字典序从大到小**输出。

### 算法分类
深度优先搜索 DFS

### 题解综合分析与结论
本题的核心是通过深度优先搜索（DFS）来枚举所有可能的拆分方案，并按照字典序从大到小输出。所有题解都采用了DFS的基本框架，但在实现细节和优化上有所不同。

### 所选高星题解
#### 1. 作者：AlicX (4星)
**关键亮点**：
- 使用了三个状态变量 `s`、`k`、`last` 来分别表示当前和、当前选择的数字个数、以及上一次选择的数字，使得代码逻辑清晰且易于理解。
- 通过 `min(n-s, last)` 来限制当前选择的数字范围，减少了不必要的搜索，提高了效率。
- 注意了行末不能有多余空格的输出细节。

**核心代码**：
```cpp
void dfs(int s, int k, int last) {
    if (s > n) return;
    if (s == n) {
        for (int i = 1; i < k - 1; i++) cout << a[i] << " ";
        cout << a[k - 1] << endl;
        return;
    }
    for (int i = min(n - s, last); i >= 1; i--) {
        a[k] = i;
        dfs(s + i, k + 1, i);
    }
}
```

#### 2. 作者：AirQwQ (4星)
**关键亮点**：
- 使用了 `plan` 数组来存储当前的选择，并通过 `min(n-sum, plan[cnt-1])` 来优化搜索范围。
- 通过 `dfs(sum+i, cnt+1)` 简化了回溯操作，减少了代码量。
- 初始化 `plan[0] = n` 来避免越界问题。

**核心代码**：
```cpp
void dfs(int sum, int cnt) {
    if (sum == n) {
        for (int i = 1; i < cnt - 1; i++) cout << plan[i] << ' ';
        cout << plan[cnt - 1] << endl;
        return;
    }
    for (int i = min(n - sum, plan[cnt - 1]); i >= 1; i--) {
        plan[cnt] = i;
        dfs(sum + i, cnt + 1);
    }
}
```

#### 3. 作者：tbdsh (3.5星)
**关键亮点**：
- 使用了 `cnt` 数组来存储当前的选择，并通过三目运算符 `cnt[x - 1] == 0 ? n : cnt[x - 1]` 来初始化搜索范围。
- 代码结构简单，易于理解，但在优化和细节处理上稍显不足。

**核心代码**：
```cpp
void dfs(int x, int sum) {
    if (sum == n) {
        for (int i = 1; i < x - 1; i++) cout << cnt[i] << " ";
        cout << cnt[x - 1] << "\n";
        return;
    } else if (sum > n) {
        return;
    }
    for (int i = (cnt[x - 1] == 0 ? n : cnt[x - 1]); i >= 1; i--) {
        cnt[x] = i;
        dfs(x + 1, sum + i);
    }
}
```

### 最优关键思路或技巧
- **状态变量设计**：使用 `s`、`k`、`last` 等状态变量来清晰表示当前搜索状态，便于理解和维护。
- **搜索范围优化**：通过 `min(n-s, last)` 或 `min(n-sum, plan[cnt-1])` 来限制当前选择的数字范围，减少不必要的搜索。
- **回溯简化**：通过 `dfs(sum+i, cnt+1)` 等简化回溯操作，减少代码量。

### 可拓展之处
- **同类型题**：类似的问题包括枚举所有可能的组合或排列，如子集生成、全排列等。
- **算法套路**：DFS在组合数学、图论等领域有广泛应用，掌握DFS的基本框架和优化技巧对解决复杂问题非常有帮助。

### 推荐洛谷题目
1. P2404 自然数的拆分
2. P1036 选数
3. P1706 全排列问题

---
处理用时：25.85秒