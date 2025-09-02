# 题目信息

# Pair of Topics

## 题目描述

The next lecture in a high school requires two topics to be discussed. The $ i $ -th topic is interesting by $ a_i $ units for the teacher and by $ b_i $ units for the students.

The pair of topics $ i $ and $ j $ ( $ i < j $ ) is called good if $ a_i + a_j > b_i + b_j $ (i.e. it is more interesting for the teacher).

Your task is to find the number of good pairs of topics.

## 样例 #1

### 输入

```
5
4 8 2 6 2
4 5 4 1 3```

### 输出

```
7```

## 样例 #2

### 输入

```
4
1 3 2 4
1 3 2 4```

### 输出

```
0```

# AI分析结果

### 题目内容重写
#### 题目描述
高中下一节课需要讨论两个话题。第 $i$ 个话题对老师的兴趣度为 $a_i$，对学生的兴趣度为 $b_i$。

话题对 $(i, j)$（$i < j$）被称为“好对”，如果 $a_i + a_j > b_i + b_j$（即对老师来说更有趣）。

你的任务是找出“好对”的数量。

#### 样例 #1
##### 输入
```
5
4 8 2 6 2
4 5 4 1 3
```
##### 输出
```
7
```

#### 样例 #2
##### 输入
```
4
1 3 2 4
1 3 2 4
```
##### 输出
```
0
```

### 算法分类
排序、二分

### 题解分析与结论
本题的核心思路是将问题转化为求满足 $c_i + c_j > 0$ 的数对 $(i, j)$，其中 $c_i = a_i - b_i$。通过排序和二分查找，可以高效地统计满足条件的数对数量。

### 评分较高的题解
#### 题解1：CCA（5星）
**关键亮点**：
- 使用双指针法，时间复杂度为 $O(N \log N)$。
- 代码简洁，思路清晰，通过排序和单调性优化了查找过程。

**核心代码**：
```cpp
for(int i = 1; i <= n; i++){
    while(c1[i] > c2[pos + 1] && pos < n) pos++;
    ans += pos;
}
printf("%lld" , ans / 2);
```
**实现思想**：通过排序后，利用双指针的单调性，快速找到满足条件的数对。

#### 题解2：Rainy7（4星）
**关键亮点**：
- 使用二分查找，时间复杂度为 $O(N \log N)$。
- 代码结构清晰，易于理解。

**核心代码**：
```cpp
for(ll i = 1; i <= n; i++){
    l = i + 1; r = n; j = 0;
    while(l <= r){
        mid = (l + r) >> 1;
        if(c[i] + c[mid] >= 1){
            j = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    if(j) ans += (n - j + 1);
}
```
**实现思想**：通过二分查找，快速找到满足条件的 $j$，并统计满足条件的数对数量。

#### 题解3：do_while_false（4星）
**关键亮点**：
- 使用滑动窗口优化，时间复杂度为 $O(N \log N)$。
- 代码简洁，思路清晰。

**核心代码**：
```cpp
while(now > i && c[now - 1] > -c[i]) --now;
if(now == i) {
    ans += (n - i + 1) * (n - i) / 2;
    break;
}
ans += n - now + 1;
```
**实现思想**：通过滑动窗口优化，减少不必要的查找操作，提高效率。

### 最优关键思路
通过将问题转化为 $c_i + c_j > 0$，并利用排序和二分查找（或双指针）来高效统计满足条件的数对数量。排序后的数组具有单调性，可以利用这一性质优化查找过程。

### 可拓展之处
类似的问题可以通过转化为单调性问题，利用排序和二分查找或双指针来优化。例如，求满足某些条件的数对、区间等问题。

### 推荐题目
1. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)
2. [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)
3. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)

### 个人心得总结
- **调试经历**：在处理二分查找时，注意边界条件的处理，避免死循环或遗漏某些情况。
- **踩坑教训**：在统计数对时，注意避免重复计数，尤其是当 $i = j$ 时。
- **顿悟感想**：通过将问题转化为单调性问题，可以大大简化查找过程，提高算法效率。

---
处理用时：30.92秒