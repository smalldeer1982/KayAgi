# 题目信息

# XOUR

## 题目描述

You are given an array $ a $ consisting of $ n $ nonnegative integers.

You can swap the elements at positions $ i $ and $ j $ if $ a_i~\mathsf{XOR}~a_j < 4 $ , where $ \mathsf{XOR} $ is the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Find the lexicographically smallest array that can be made with any number of swaps.

An array $ x $ is lexicographically smaller than an array $ y $ if in the first position where $ x $ and $ y $ differ, $ x_i < y_i $ .

## 说明/提示

For the first test case, you can swap any two elements, so we can produce the sorted array.

For the second test case, you can swap $ 2 $ and $ 1 $ (their $ \mathsf{XOR} $ is $ 3 $ ), $ 7 $ and $ 5 $ (their $ \mathsf{XOR} $ is $ 2 $ ), and $ 7 $ and $ 6 $ (their $ \mathsf{XOR} $ is $ 1 $ ) to get the lexicographically smallest array.

## 样例 #1

### 输入

```
4
4
1 0 3 2
5
2 7 1 5 6
8
1 2 1 2 1 2 1 2
4
16 4 1 64```

### 输出

```
0 1 2 3 
1 5 2 6 7 
1 1 1 1 2 2 2 2 
16 4 1 64```

# AI分析结果

### 题目内容重写

#### 题目描述

给定一个由 $n$ 个非负整数组成的数组 $a$。

如果 $a_i~\mathsf{XOR}~a_j < 4$，则可以交换位置 $i$ 和 $j$ 的元素，其中 $\mathsf{XOR}$ 是[按位异或操作](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

通过任意次数的交换，找到可以得到的字典序最小的数组。

数组 $x$ 的字典序小于数组 $y$，当且仅当在第一个不同的位置上，$x_i < y_i$。

#### 说明/提示

对于第一个测试用例，可以交换任意两个元素，因此可以得到排序后的数组。

对于第二个测试用例，可以交换 $2$ 和 $1$（它们的 $\mathsf{XOR}$ 为 $3$），$7$ 和 $5$（它们的 $\mathsf{XOR}$ 为 $2$），以及 $7$ 和 $6$（它们的 $\mathsf{XOR}$ 为 $1$），从而得到字典序最小的数组。

#### 样例 #1

##### 输入

```
4
4
1 0 3 2
5
2 7 1 5 6
8
1 2 1 2 1 2 1 2
4
16 4 1 64
```

##### 输出

```
0 1 2 3 
1 5 2 6 7 
1 1 1 1 2 2 2 2 
16 4 1 64
```

### 题解分析与结论

#### 综合分析与结论

本题的核心在于理解 $a_i \oplus a_j < 4$ 的条件，即两个数的二进制表示中，除了最后两位之外，其他位必须完全相同。因此，可以将数组中的元素按照 $a_i / 4$ 进行分组，每组内的元素可以任意交换。为了使整个数组的字典序最小，可以在每组内对元素进行排序，然后按照原数组的顺序依次输出每组的最小值。

#### 所选高分题解

##### 题解1：作者：Gapple (赞：3)

**星级：4星**

**关键亮点：**
- 通过将元素按 $a_i / 4$ 分组，明确哪些元素可以交换。
- 使用 `unordered_map` 和 `vector` 来存储和排序每组元素，代码简洁且高效。
- 通过遍历原数组，输出每组的最小值，保证了字典序最小。

**核心代码：**
```cpp
unordered_map<int, vector<int>, Hash> idx;

for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    idx[x >> 2].emplace_back(i);
    arr.emplace_back(x);
}

for (auto& [_, i] : idx)
    sort(i.begin(), i.end(), [&arr](int u, int v) { return arr[u] < arr[v]; });

for (int i = 0; i < n; ++i)
    cout << arr[idx[arr[i] >> 2][pos[arr[i] >> 2]++]] << ' ';
```

##### 题解2：作者：JXR_Kalcium (赞：3)

**星级：4星**

**关键亮点：**
- 使用 `map` 和 `priority_queue` 来维护每组的最小值，代码简洁且易于理解。
- 通过遍历原数组，输出每组的最小值，保证了字典序最小。

**核心代码：**
```cpp
map<int, priority_queue<int> > mp;

for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]), mp[a[i] / 4].push(-a[i]);

for (int i = 1; i <= n; ++i)
    printf("%d ", -mp[a[i] / 4].top()), mp[a[i] / 4].pop();
```

##### 题解3：作者：shenwentao (赞：0)

**星级：4星**

**关键亮点：**
- 通过将元素按 $a_i / 4$ 分组，明确哪些元素可以交换。
- 使用 `map` 和 `priority_queue` 来维护每组的最小值，代码简洁且高效。
- 通过遍历原数组，输出每组的最小值，保证了字典序最小。

**核心代码：**
```cpp
map<int, priority_queue<int> > mp;

for (int i = 1; i <= n; i++) {
    cin >> a[i];
    mp[a[i] >> 2].push(-a[i]);
}

for (int i = 1; i <= n; i++) {
    cout << -mp[a[i] >> 2].top() << " ";
    mp[a[i] >> 2].pop();
}
```

### 最优关键思路或技巧

1. **分组策略**：通过将元素按 $a_i / 4$ 分组，明确哪些元素可以交换，这是解决问题的关键。
2. **排序与输出**：在每组内对元素进行排序，然后按照原数组的顺序依次输出每组的最小值，保证了字典序最小。
3. **数据结构选择**：使用 `map` 和 `priority_queue` 来维护每组的最小值，代码简洁且高效。

### 可拓展之处

1. **类似题目**：可以拓展到其他基于位运算的分组问题，如按位与、按位或等。
2. **优化思路**：可以考虑使用更高效的数据结构来进一步优化时间复杂度，如使用 `unordered_map` 代替 `map`。

### 推荐题目

1. [P1971 按位异或](https://www.luogu.com.cn/problem/P1971)
2. [P1972 按位与](https://www.luogu.com.cn/problem/P1972)
3. [P1973 按位或](https://www.luogu.com.cn/problem/P1973)

### 个人心得

- **调试经历**：在实现过程中，需要注意分组时边界条件的处理，如 $a_i / 4$ 的结果可能为负数，需要确保分组正确。
- **顿悟感想**：通过将问题转化为分组和排序问题，可以大大简化问题的复杂度，提高解题效率。

---
处理用时：47.49秒