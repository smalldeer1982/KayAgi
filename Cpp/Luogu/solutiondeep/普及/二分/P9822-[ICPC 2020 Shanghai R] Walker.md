# 题目信息

# [ICPC 2020 Shanghai R] Walker

## 题目描述

As a world-famous traveler, Prof. Pang's research interest is to travel as many places as possible in his life.

We have a segment $[0, n]$. There are two travelers on it. The first one is on position $p_1$ with velocity $v_1$ (which means s/he can walk $v_1$ unit on the segment per second). The second one is on position $p_2$ with velocity $v_2$.

From their respective beginning points, travelers can walk on the segment. They cannot walk outside the segment. Whenever they want to change their direction, they can turn around immediately.

Please help Prof. Pang to calculate the minimum  possible time by which every position of the segment is passed by at least one traveler.

## 样例 #1

### 输入

```
2
10000.0 1.0 0.001 9999.0 0.001
4306.063 4079.874 0.607 1033.423 0.847```

### 输出

```
5001000.0000000000
3827.8370013755```

# AI分析结果

### 综合分析与结论

本题的核心在于如何高效计算两名旅行者覆盖整个线段所需的最小时间。通过分析，可以将问题分为三种主要情况：
1. **单人走完全程**：选择速度较快或位置更优的旅行者独自完成任务。
2. **两人相向而行**：两人分别向相反方向行走，直到覆盖整个线段。
3. **两人各自负责一部分**：通过二分法确定一个中间点，两人分别覆盖线段的两部分。

大多数题解都采用了类似的分类讨论和二分法，但在细节处理和代码实现上有所不同。部分题解在精度控制、代码简洁性和优化程度上表现较好。

### 所选高分题解

#### 题解1：作者：wylnh (★★★★★)
**关键亮点**：
- 思路清晰，详细解释了三种情况的处理方式。
- 代码简洁且高效，使用了二分法精确计算中间点。
- 注意了精度控制，确保结果的准确性。

**核心代码**：
```cpp
double l = p1, r = p2;
while (r - l > eps) {
    double mid = (l + r) / 2;
    double t1 = (mid + min(mid - p1, p1)) / v1;
    double t2 = (n - mid + min(n - p2, p2 - mid)) / v2;
    ans = min(ans, max(t1, t2));
    if (t1 < t2) l = mid;
    else r = mid;
}
```
**实现思想**：通过二分法在 `[p1, p2]` 区间内寻找最优的中间点，使得两人覆盖各自部分的时间最小。

#### 题解2：作者：佬头 (★★★★☆)
**关键亮点**：
- 详细描述了二分法的应用场景和原理。
- 代码结构清晰，易于理解。
- 强调了二分法的单调性，帮助理解算法的正确性。

**核心代码**：
```cpp
double lft = p, rt = pp;
while (rt - lft >= 0.0000001) {
    mid = (lft + rt) / 2;
    if (check()) lft = mid + 0.0000001;
    else rt = mid - 0.0000001;
}
```
**实现思想**：通过二分法在 `[p1, p2]` 区间内寻找最优的中间点，确保两人覆盖各自部分的时间最小。

#### 题解3：作者：keepwatcher_kensap (★★★★☆)
**关键亮点**：
- 详细分析了四种情况，覆盖了所有可能的解决方案。
- 代码实现简洁，使用了二分法优化计算。
- 强调了精度控制的重要性。

**核心代码**：
```cpp
double left = p1, right = p2;
while (left + 0.0000001 < right) {
    double mid = left + (right - left) / 2;
    double s1 = (min(p1, mid - p1) + mid) / v1;
    double s2 = (min(n - p2, p2 - mid) + n - mid) / v2;
    result = min(result, max(s1, s2));
    if (s1 > s2) right = mid - 0.0000001;
    else left = mid + 0.0000001;
}
```
**实现思想**：通过二分法在 `[p1, p2]` 区间内寻找最优的中间点，确保两人覆盖各自部分的时间最小。

### 最优关键思路与技巧

1. **分类讨论**：将问题分为单人走完全程、两人相向而行、两人各自负责一部分三种情况，简化问题复杂度。
2. **二分法**：在 `[p1, p2]` 区间内通过二分法寻找最优的中间点，确保两人覆盖各自部分的时间最小。
3. **精度控制**：在二分法中，精确控制精度（如 `1e-7`），确保结果的准确性。

### 可拓展之处

- **类似问题**：可以扩展到多旅行者覆盖线段或区域的问题，通过类似的分治和二分法优化计算。
- **动态规划**：在某些情况下，可以使用动态规划优化计算过程，尤其是在旅行者数量较多时。

### 推荐题目

1. **P1004 方格取数**：考察路径规划和最优覆盖问题。
2. **P1020 导弹拦截**：涉及二分法和贪心算法的应用。
3. **P1040 加分二叉树**：考察二分法和动态规划的结合应用。

### 个人心得总结

- **调试经历**：部分题解提到在二分法中需要精确控制精度，否则可能导致结果不准确。
- **踩坑教训**：在分类讨论时，需确保所有情况都被覆盖，避免遗漏某些特殊情况。
- **顿悟感想**：通过二分法可以高效解决复杂的最优化问题，尤其是在需要精确计算的场景中。

---
处理用时：31.23秒