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

本题的核心是求解两个旅行者在一条线段上覆盖所有位置的最小时间。题解主要集中在三种情况：单人走完全程、两人相向而行、两人分别负责线段的两部分并在中间相遇。大多数题解通过分类讨论和二分查找来优化第三种情况的求解。整体思路清晰，但部分题解在代码实现和优化上存在不足。

### 所选高星题解

#### 1. 作者：wylnh (5星)
- **关键亮点**：思路清晰，代码简洁，详细解释了三种情况的处理方式，特别是二分查找的优化。
- **个人心得**：强调了精度控制的重要性，建议精确到1e-7以避免误差。
- **核心代码**：
  ```cpp
  double l=p1,r=p2;
  while(r-l>eps){
      double mid=(l+r)/2;
      double t1=(mid+min(mid-p1,p1))/v1;
      double t2=(n-mid+min(n-p2,p2-mid))/v2;
      ans=min(ans,max(t1,t2));
      if(t1<t2) l=mid;
      else r=mid;
  }
  ```

#### 2. 作者：佬头 (4星)
- **关键亮点**：详细描述了二分查找的过程，特别是如何通过二分找到最优的相遇点。
- **核心代码**：
  ```cpp
  double lft = p, rt = pp;
  while(rt - lft >= 0.0000001){
      mid = (lft + rt) / 2;
      if(check()) lft = mid + 0.0000001;
      else rt = mid - 0.0000001;
  }
  ```

#### 3. 作者：0x282e202e2029 (4星)
- **关键亮点**：代码结构清晰，详细解释了二分查找的优化过程，特别是如何通过二分找到最优的相遇点。
- **核心代码**：
  ```cpp
  double l = p1, r = p2;
  while (r - l > eps) {
      double mid = (l + r) / 2;
      if (check(mid)) l = mid;
      else r = mid;
  }
  ```

### 最优关键思路与技巧

1. **分类讨论**：将问题分为单人走完全程、两人相向而行、两人分别负责线段的两部分并在中间相遇三种情况，分别计算时间。
2. **二分查找**：在第三种情况中，通过二分查找确定两人相遇的最优位置，使得两人覆盖线段的时间最小。
3. **精度控制**：在二分查找中，精确到1e-7以避免误差，确保结果的准确性。

### 可拓展之处

- **类似问题**：可以扩展到多旅行者覆盖线段的问题，或者旅行者在不同速度下的覆盖问题。
- **算法套路**：二分查找在优化问题中的应用，特别是在需要精确控制误差的情况下。

### 推荐题目

1. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020) - 考察二分查找和贪心算法的应用。
2. [P1044 栈](https://www.luogu.com.cn/problem/P1044) - 考察动态规划和栈的应用。
3. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059) - 考察排序和去重的应用。

### 个人心得总结

- **调试经历**：部分题解提到在二分查找中需要精确控制精度，否则会导致结果不准确。
- **踩坑教训**：在分类讨论时，需要确保所有情况都被覆盖，避免遗漏。
- **顿悟感想**：通过二分查找优化第三种情况的求解，可以显著提高算法的效率。

---
处理用时：20.51秒