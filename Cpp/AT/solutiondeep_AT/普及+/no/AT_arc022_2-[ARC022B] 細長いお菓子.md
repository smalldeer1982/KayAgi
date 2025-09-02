# 题目信息

# [ARC022B] 細長いお菓子

## 题目描述

### 题目简述



有一个长度为$N$的序列。



请从这个序列里面找出**满足全部的值都是不相同的**子序列。



请输出最长子序列的**这个长度**。

## 样例 #1

### 输入

```
7

1 2 1 3 1 4 4```

### 输出

```
3```

## 样例 #2

### 输入

```
1

100```

### 输出

```
1```

# AI分析结果

### 题目内容

#### 题目描述

有一个长度为$N$的序列。

请从这个序列里面找出**满足全部的值都是不相同的**子序列。

请输出最长子序列的**这个长度**。

#### 样例 #1

##### 输入

```
7

1 2 1 3 1 4 4
```

##### 输出

```
3
```

#### 样例 #2

##### 输入

```
1

100
```

##### 输出

```
1
```

### 算法分类

滑动窗口

### 综合分析与结论

本题要求找出序列中最长的子序列，且子序列中的所有元素都不重复。这是一个典型的滑动窗口问题，可以通过维护一个窗口来记录当前子序列的元素，并使用哈希表来快速判断元素是否重复。

### 通用建议与扩展思路

1. **滑动窗口**：滑动窗口是解决子序列问题的常用技巧，通过维护一个窗口来记录当前子序列的元素，并根据条件调整窗口的大小。
2. **哈希表**：哈希表可以快速判断元素是否重复，是滑动窗口问题中常用的数据结构。
3. **双指针**：滑动窗口通常使用双指针来维护窗口的边界，左指针和右指针分别表示窗口的起始和结束位置。

### 推荐题目

1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1638 连续子序列的最大和](https://www.luogu.com.cn/problem/P1638)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

### 关键思路与技巧

1. **滑动窗口**：通过维护一个窗口来记录当前子序列的元素，并根据条件调整窗口的大小。
2. **哈希表**：使用哈希表来快速判断元素是否重复，从而决定是否移动窗口的左指针。
3. **双指针**：使用双指针来维护窗口的边界，左指针和右指针分别表示窗口的起始和结束位置。

### 核心代码片段

```cpp
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

int longestUniqueSubsequence(const vector<int>& nums) {
    unordered_set<int> window;
    int left = 0, maxLen = 0;
    for (int right = 0; right < nums.size(); ++right) {
        while (window.count(nums[right])) {
            window.erase(nums[left]);
            ++left;
        }
        window.insert(nums[right]);
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}

int main() {
    int N;
    cin >> N;
    vector<int> nums(N);
    for (int i = 0; i < N; ++i) {
        cin >> nums[i];
    }
    cout << longestUniqueSubsequence(nums) << endl;
    return 0;
}
```

### 核心实现思想

1. **初始化**：使用一个哈希表`window`来记录当前窗口中的元素，使用双指针`left`和`right`来表示窗口的边界。
2. **滑动窗口**：遍历数组，对于每个元素`nums[right]`，如果它已经在`window`中，则移动左指针`left`，直到`nums[right]`不在`window`中。
3. **更新窗口**：将`nums[right]`插入`window`，并更新最大长度`maxLen`。
4. **输出结果**：遍历结束后，`maxLen`即为最长子序列的长度。

---
处理用时：20.59秒