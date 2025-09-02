# 题目信息

# Phoenix and Beauty

## 题目描述

Phoenix loves beautiful arrays. An array is beautiful if all its subarrays of length $ k $ have the same sum. A subarray of an array is any sequence of consecutive elements.

Phoenix currently has an array $ a $ of length $ n $ . He wants to insert some number of integers, possibly zero, into his array such that it becomes beautiful. The inserted integers must be between $ 1 $ and $ n $ inclusive. Integers may be inserted anywhere (even before the first or after the last element), and he is not trying to minimize the number of inserted integers.

## 说明/提示

In the first test case, we can make array $ a $ beautiful by inserting the integer $ 1 $ at index $ 3 $ (in between the two existing $ 2 $ s). Now, all subarrays of length $ k=2 $ have the same sum $ 3 $ . There exists many other possible solutions, for example:

- $ 2, 1, 2, 1, 2, 1 $
- $ 1, 2, 1, 2, 1, 2 $

In the second test case, the array is already beautiful: all subarrays of length $ k=3 $ have the same sum $ 5 $ .

In the third test case, it can be shown that we cannot insert numbers to make array $ a $ beautiful.

In the fourth test case, the array $ b $ shown is beautiful and all subarrays of length $ k=4 $ have the same sum $ 10 $ . There exist other solutions also.

## 样例 #1

### 输入

```
4
4 2
1 2 2 1
4 3
1 2 2 1
3 2
1 2 3
4 4
4 3 4 2```

### 输出

```
5
1 2 1 2 1
4
1 2 2 1
-1
7
4 3 2 1 4 3 2```

# AI分析结果

### 题目翻译

Phoenix 喜欢美丽的数组。一个数组是美丽的，如果它的所有长度为 $k$ 的子数组的和都相同。子数组是数组中任意连续的元素序列。

Phoenix 目前有一个长度为 $n$ 的数组 $a$。他想要在其中插入一些整数（可能为零），使得数组变得美丽。插入的整数必须在 $1$ 到 $n$ 之间（包括 $1$ 和 $n$）。整数可以插入到任何位置（甚至在第一个元素之前或最后一个元素之后），并且他并不试图最小化插入的整数数量。

### 算法分类
构造

### 题解分析与结论

本题的核心在于构造一个数组，使得所有长度为 $k$ 的子数组的和相同。通过分析，我们发现这样的数组必须是一个循环节长度为 $k$ 的循环数组。因此，构造的关键在于确定这个循环节，并确保原数组中的所有元素都出现在构造后的数组中。

#### 关键思路
1. **循环节构造**：构造一个长度为 $k$ 的循环节，使得所有长度为 $k$ 的子数组的和相同。
2. **去重与填充**：如果原数组中不同元素的数量大于 $k$，则无解；否则，将原数组中的元素去重后，填充到循环节中，不足的部分可以随意填充 $1$ 到 $n$ 之间的数。
3. **复制循环节**：将循环节复制 $n$ 次，确保原数组中的每个元素都出现在构造后的数组中。

#### 最优题解

**题解作者：do_while_true (5星)**

**关键亮点**：
- 清晰地解释了循环节的构造思路，并通过去重与填充的方法确保了原数组中的元素都出现在构造后的数组中。
- 代码简洁明了，逻辑清晰，易于理解。

**核心代码**：
```cpp
void solve() {
    set<int> s;
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        s.insert(x);
    }
    if (s.size() > k) {
        puts("-1");
        return;
    }
    cout << n * k << endl;
    for (int i = 1; i <= n; i++) {
        for (int it : s) {
            cout << it << " ";
        }
        for (int j = 1; j <= k - s.size(); j++) {
            cout << n << " ";
        }
    }
    cout << endl;
}
```

**实现思想**：
- 使用 `set` 去重，判断不同元素的数量是否大于 $k$，若大于则无解。
- 否则，将去重后的元素填充到循环节中，不足的部分用 $n$ 填充，并将循环节复制 $n$ 次。

### 拓展思路
- **类似问题**：可以通过构造循环节来解决类似的问题，如要求所有长度为 $m$ 的子数组满足某种条件。
- **优化**：在实际应用中，可以通过优化循环节的构造来减少数组的长度，从而降低空间复杂度。

### 推荐题目
1. [P1325 CopyCopyCopyCopyCopy](https://www.luogu.com.cn/problem/P1325)
2. [P1348 Phoenix and Beauty](https://www.luogu.com.cn/problem/P1348)
3. [P1351 构造数组](https://www.luogu.com.cn/problem/P1351)

---
处理用时：22.56秒