# 题目信息

# Alternating Subsequence

## 题目描述

Recall that the sequence $ b $ is a a subsequence of the sequence $ a $ if $ b $ can be derived from $ a $ by removing zero or more elements without changing the order of the remaining elements. For example, if $ a=[1, 2, 1, 3, 1, 2, 1] $ , then possible subsequences are: $ [1, 1, 1, 1] $ , $ [3] $ and $ [1, 2, 1, 3, 1, 2, 1] $ , but not $ [3, 2, 3] $ and $ [1, 1,       1, 1, 2] $ .

You are given a sequence $ a $ consisting of $ n $ positive and negative elements (there is no zeros in the sequence).

Your task is to choose maximum by size (length) alternating subsequence of the given sequence (i.e. the sign of each next element is the opposite from the sign of the current element, like positive-negative-positive and so on or negative-positive-negative and so on). Among all such subsequences, you have to choose one which has the maximum sum of elements.

In other words, if the maximum length of alternating subsequence is $ k $ then your task is to find the maximum sum of elements of some alternating subsequence of length $ k $ .

You have to answer $ t $ independent test cases.

## 说明/提示

In the first test case of the example, one of the possible answers is $ [1, 2, \underline{3}, \underline{-1}, -2] $ .

In the second test case of the example, one of the possible answers is $ [-1, -2, \underline{-1}, -3] $ .

In the third test case of the example, one of the possible answers is $ [\underline{-2}, 8, 3, \underline{8},       \underline{-4}, -15, \underline{5}, \underline{-2}, -3, \underline{1}] $ .

In the fourth test case of the example, one of the possible answers is $ [\underline{1}, \underline{-1000000000},       \underline{1}, \underline{-1000000000}, \underline{1}, \underline{-1000000000}] $ .

## 样例 #1

### 输入

```
4
5
1 2 3 -1 -2
4
-1 -2 -1 -3
10
-2 8 3 8 -4 -15 5 -2 -3 1
6
1 -1000000000 1 -1000000000 1 -1000000000```

### 输出

```
2
-1
6
-2999999997```

# AI分析结果

### 题目内容重写

#### 交替子序列

**题目描述**

回忆一下，序列 $b$ 是序列 $a$ 的子序列，如果 $b$ 可以通过从 $a$ 中删除零个或多个元素而不改变剩余元素的顺序得到。例如，如果 $a=[1, 2, 1, 3, 1, 2, 1]$，那么可能的子序列有：$[1, 1, 1, 1]$、$[3]$ 和 $[1, 2, 1, 3, 1, 2, 1]$，但不是 $[3, 2, 3]$ 和 $[1, 1, 1, 1, 2]$。

给你一个由 $n$ 个正负元素组成的序列 $a$（序列中没有零）。

你的任务是选择一个长度最大且元素和最大的交替子序列（即每个下一个元素的符号与当前元素的符号相反，如正-负-正或负-正-负等）。在所有这样的子序列中，你需要选择一个元素和最大的子序列。

换句话说，如果交替子序列的最大长度为 $k$，那么你的任务是找到一个长度为 $k$ 的交替子序列，其元素和最大。

你需要回答 $t$ 个独立的测试用例。

**说明/提示**

在第一个测试用例中，一个可能的答案是 $[1, 2, \underline{3}, \underline{-1}, -2]$。

在第二个测试用例中，一个可能的答案是 $[-1, -2, \underline{-1}, -3]$。

在第三个测试用例中，一个可能的答案是 $[\underline{-2}, 8, 3, \underline{8}, \underline{-4}, -15, \underline{5}, \underline{-2}, -3, \underline{1}]$。

在第四个测试用例中，一个可能的答案是 $[\underline{1}, \underline{-1000000000}, \underline{1}, \underline{-1000000000}, \underline{1}, \underline{-1000000000}]$。

**样例 #1**

**输入**

```
4
5
1 2 3 -1 -2
4
-1 -2 -1 -3
10
-2 8 3 8 -4 -15 5 -2 -3 1
6
1 -1000000000 1 -1000000000 1 -1000000000
```

**输出**

```
2
-1
6
-2999999997
```

### 算法分类

贪心

### 题解分析与结论

该题的核心问题是在一个正负交替的序列中选择一个长度最大且元素和最大的子序列。通过分析，可以发现贪心算法是解决该问题的最佳选择。贪心算法的思路是：将序列分成若干段，每段中的元素符号相同，然后从每段中选择最大的元素，最终将这些元素相加得到结果。

### 所选题解

#### 1. 作者：PersistentLife (赞：4)

**星级**：★★★★★

**关键亮点**：
- 通过将序列分成若干段，每段符号相同，然后从每段中选择最大元素，确保了子序列的长度最大且和最大。
- 代码简洁，逻辑清晰，易于理解。

**核心代码**：
```cpp
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int a[n + 1];
        int maxx = 0;
        long long ans = 0;
        bool f = 0;
        for (int i = 1; i <= n; i++) cin >> a[i];
        if (a[1] < 0) f = 1;
        maxx = a[1];
        for (int i = 2; i <= n; i++) {
            if (a[i] > 0 && f) {
                f = 0;
                ans += maxx;
                maxx = a[i];
            } else if (a[i] < 0 && !f) {
                f = 1;
                ans += maxx;
                maxx = a[i];
            } else maxx = max(maxx, a[i]);
        }
        ans += maxx;
        cout << ans << endl;
    }
    return 0;
}
```

#### 2. 作者：sycqwq (赞：2)

**星级**：★★★★

**关键亮点**：
- 通过判断每个元素的正负性，选择每段中的最大元素，确保了子序列的长度最大且和最大。
- 代码实现简单，逻辑清晰。

**核心代码**：
```cpp
signed main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int n, a[200005], t = 1;
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        if (a[1] < 0) t = 0;
        int ma = a[1];
        int s = 0;
        for (int j = 1; j <= n; j++) {
            int tp = a[j] >= 0 ? 1 : 0;
            if (tp == t) {
                ma = max(ma, a[j]);
            } else {
                t = t == 0 ? 1 : 0;
                s += ma;
                ma = a[j];
            }
        }
        cout << s + ma << endl;
    }
    return 0;
}
```

#### 3. 作者：_Revenge_ (赞：0)

**星级**：★★★★

**关键亮点**：
- 通过将序列分成若干段，每段符号相同，然后从每段中选择最大元素，确保了子序列的长度最大且和最大。
- 代码实现简洁，逻辑清晰。

**核心代码**：
```cpp
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int a[n + 1];
        for (int i = 1; i <= n; i++) cin >> a[i];
        ll l = a[1] > 0 ? 1 : -1, ans = 0, maxn = a[1];
        for (int i = 2; i <= n; i++) {
            ll res = a[i] > 0 ? 1 : -1;
            if (res == l) {
                maxn = max(maxn, a[i]);
            } else {
                ans += maxn;
                maxn = a[i];
                l = res;
            }
        }
        ans += maxn;
        printf("%lld\n", ans);
    }
    return 0;
}
```

### 最优关键思路与技巧

1. **分段选择**：将序列分成若干段，每段中的元素符号相同，然后从每段中选择最大元素，确保子序列的长度最大且和最大。
2. **贪心策略**：通过贪心算法，每次选择当前段中的最大元素，确保子序列的和最大。

### 可拓展之处

该题的贪心策略可以应用于其他需要选择子序列且要求长度和和最大的问题。例如，选择最长上升子序列、最长下降子序列等。

### 推荐题目

1. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)
2. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)
3. [P1280 尼克的任务](https://www.luogu.com.cn/problem/P1280)

---
处理用时：51.68秒