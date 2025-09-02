# 题目信息

# Tender Carpenter

## 题目描述

I would use a firework to announce, a wave to bid farewell, and a bow to say thanks: bygones are bygones; not only on the following path will I be walking leisurely and joyfully, but also the footsteps won't halt as time never leaves out flowing; for in the next year, we will meet again.

— Cocoly1990, [Goodbye 2022](https://www.luogu.com.cn/problem/P8941)



In his dream, Cocoly would go on a long holiday with no worries around him. So he would try out for many new things, such as... being a carpenter. To learn it well, Cocoly decides to become an apprentice of Master, but in front of him lies a hard task waiting for him to solve.

Cocoly is given an array $ a_1, a_2,\ldots, a_n $ . Master calls a set of integers $ S $ stable if and only if, for any possible $ u $ , $ v $ , and $ w $ from the set $ S $ (note that $ u $ , $ v $ , and $ w $ do not necessarily have to be pairwise distinct), sticks of length $ u $ , $ v $ , and $ w $ can form a non-degenerate triangle $ ^{\text{∗}} $ .

Cocoly is asked to partition the array $ a $ into several (possibly, $ 1 $ or $ n $ ) non-empty continuous subsegments $ ^{\text{†}} $ , such that: for each of the subsegments, the set containing all the elements in it is stable.

Master wants Cocoly to partition $ a $ in at least two different $ ^{\text{‡}} $ ways. You have to help him determine whether it is possible.

 $ ^{\text{∗}} $ A triangle with side lengths $ x $ , $ y $ , and $ z $ is called non-degenerate if and only if:

- $ x + y > z $ ,
- $ y + z > x $ , and
- $ z + x > y $ .

 $ ^{\text{†}} $ A sequence $ b $ is a subsegment of a sequence $ c $ if $ b $ can be obtained from $ c $ by the deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

 $ ^{\text{‡}} $ Two partitions are considered different if and only if at least one of the following holds:

- the numbers of continuous subsegments split in two partitions are different;
- there is an integer $ k $ such that the lengths of the $ k $ -th subsegment in two partitions are different.

## 说明/提示

In the first test case, here are two possible partitions:

- $ [2, 3], [5, 7] $ , since 
  - $ [2, 3] $ is stable because sticks of lengths $ (2, 2, 2), (2, 2, 3), (2, 3, 3), (3, 3, 3) $ respectively can all form non-degenerate triangles.
  - $ [5, 7] $ is stable because sticks of lengths $ (5, 5, 5), (5, 5, 7), (5, 7, 7), (7, 7, 7) $ respectively can all form non-degenerate triangles.
- and $ [2], [3, 5], [7] $ , since 
  - $ [2] $ is stable because sticks of lengths $ (2, 2, 2) $ respectively can form a non-degenerate triangle.
  - $ [3, 5] $ is stable because sticks of lengths $ (3, 3, 3), (3, 3, 5), (3, 5, 5), (5, 5, 5) $ respectively can all form non-degenerate triangles.
  - $ [7] $ is stable because sticks of lengths $ (7, 7, 7) $ respectively can form a non-degenerate triangle.

Note that some other partitions also satisfy the constraints, such as $ [2], [3], [5], [7] $ and $ [2], [3], [5, 7] $ .

In the second test case, Cocoly can only partition each element as a single subsegment, resulting in $ [115], [9], [2], [28] $ . Since we only have one possible partition, the answer is $ \texttt{NO} $ .

In the third test case, please note that the partition $ [8, 4], [1], [6], [2] $ does not satisfy the constraints, because $ \{8, 4\} $ is not a stable set: sticks of lengths $ 4 $ , $ 4 $ , and $ 8 $ cannot form a non-degenerate triangle.

## 样例 #1

### 输入

```
5
4
2 3 5 7
4
115 9 2 28
5
8 4 1 6 2
6
1 5 4 1 4 7
2
100000 100000```

### 输出

```
YES
NO
NO
YES
YES```

# AI分析结果



---

## 算法分类
**几何**

---

## 综合分析与结论

### 核心思路
题目要求将数组分割为若干连续子段，每个子段对应的集合必须满足“稳定”条件（任意三元组可构成非退化三角形）。问题转化为判断是否存在至少两种不同的分割方式。

**关键推导**：
- **稳定集合的条件**：
  - **单元素集合**：自动满足。
  - **双元素集合**：较大元素严格小于较小元素的两倍（`max(u, v) < 2 * min(u, v)`）。
  - **多元素集合**：最大元素严格小于次大两元素之和（`s_k < s_{k-1} + s_{k-2}`）。

**核心观察**：
若存在至少一个相邻元素对可合并为稳定集合，则至少存在两种分割方式（全分割与合并后的分割）。否则，全分割是唯一方式。

### 解决难点
- **高效判断条件**：遍历所有相邻元素对，检查是否满足双元素稳定条件。
- **几何意义验证**：通过严格数学推导，将稳定条件转化为相邻元素对的数值关系。

---

## 题解评分与关键实现

### 最优题解 (5星)
**思路亮点**：
- 直接遍历相邻元素对，判断是否满足双元素稳定条件。
- 时间复杂度仅 O(n)，空间复杂度 O(1)。

**核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;

bool solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    for (int i = 0; i < n - 1; ++i) {
        int u = a[i], v = a[i+1];
        if (max(u, v) < 2 * min(u, v)) {
            return true; // 存在可合并的对
        }
    }
    return false; // 无任何相邻对可合并
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cout << (solve() ? "YES" : "NO") << endl;
    }
}
```

---

## 同类型题拓展
1. **洛谷 P1118**：组合数三角形，需构造满足三角形条件的排列。
2. **洛谷 P5717**：判断三条边能否构成三角形，基础几何条件判断。
3. **洛谷 P1053**：贪心选择与几何条件结合的最优分割。

---

## 可视化与算法演示
### 动画设计
1. **像素风格遍历**：
   - 用色块表示数组元素，相邻对高亮为红色或绿色。
   - **红色**：不满足合并条件；**绿色**：满足条件。
   - 遍历时动态显示当前检查的相邻对及其数值关系。

2. **关键运算步骤**：
   - 每一步比较相邻元素 `a[i]` 和 `a[i+1]`。
   - 显示 `max(a[i], a[i+1])` 与 `2 * min(a[i], a[i+1])` 的数值对比。

3. **音效与反馈**：
   - 发现可合并对时播放“成功”音效，背景变为绿色闪烁。
   - 无可行对时播放“失败”音效，背景变暗。

### 复古游戏化
- **8位音效**：使用芯片音乐风格提示成功/失败。
- **积分系统**：每找到一个可合并对得10分，总分影响最终评级。

---

## 个人心得
- **调试经验**：必须严格处理边界条件（如元素相等时的比较）。
- **思维突破**：发现双元素稳定条件的充要条件是解题关键，避免陷入复杂情况分析。

---
处理用时：204.13秒