# 题目信息

# [USACO06DEC] River Hopscotch S

## 题目描述

Every year the cows hold an event featuring a peculiar version of hopscotch that involves carefully jumping from rock to rock in a river. The excitement takes place on a long, straight river with a rock at the start and another rock at the end, L units away from the start (1 ≤ L ≤ 1,000,000,000). Along the river between the starting and ending rocks, N (0 ≤ N ≤ 50,000) more rocks appear, each at an integral distance Di from the start (0 < Di < L).

To play the game, each cow in turn starts at the starting rock and tries to reach the finish at the ending rock, jumping only from rock to rock. Of course, less agile cows never make it to the final rock, ending up instead in the river.

Farmer John is proud of his cows and watches this event each year. But as time goes by, he tires of watching the timid cows of the other farmers limp across the short distances between rocks placed too closely together. He plans to remove several rocks in order to increase the shortest distance a cow will have to jump to reach the end. He knows he cannot remove the starting and ending rocks, but he calculates that he has enough resources to remove up to M rocks (0 ≤ M ≤ N).

FJ wants to know exactly how much he can increase the shortest distance \*before\* he starts removing the rocks. Help Farmer John determine the greatest possible shortest distance a cow has to jump after removing the optimal set of M rocks.

奶牛跳房子：从N块石头中移除M块，使得间距最小值最大。


## 说明/提示

Before removing any rocks, the shortest jump was a jump of 2 from 0 (the start) to 2. After removing the rocks at 2 and 14, the shortest required jump is a jump of 4 (from 17 to 21 or from 21 to 25).


## 样例 #1

### 输入

```
25 5 2
2
14
11
21
17```

### 输出

```
4```

# AI分析结果

### 综合分析与结论

该题目是一个典型的二分答案问题，核心思想是通过二分查找来确定最大化的最小跳跃距离。所有题解都采用了二分查找的思路，但在实现细节、代码可读性和优化程度上有所不同。大多数题解都提到了以下几点：

1. **二分查找**：通过二分查找来枚举可能的跳跃距离，判断是否满足移除石头的数量限制。
2. **贪心策略**：在判断函数中，使用贪心策略来计算需要移除的石头数量。
3. **排序**：由于石头的初始位置是无序的，所有题解都强调了排序的重要性。

### 所选高质量题解

#### 1. 作者：seek_my_calling (★★★★★)
- **关键亮点**：代码简洁明了，二分查找和贪心策略的实现非常清晰，适合初学者理解。
- **核心代码**：
  ```cpp
  int count(int mid) {
      int j = 0, x = 0;
      for (int i = 1; i <= n + 1; i++) {
          if (a[i] - a[j] < mid) x++;
          else j = i;
      }
      return x;
  }
  ```
  **核心思想**：通过遍历石头数组，计算在当前跳跃距离 `mid` 下需要移除的石头数量。

#### 2. 作者：_maze (★★★★☆)
- **关键亮点**：详细解释了二分查找的原理，并提供了清晰的判断函数实现。
- **核心代码**：
  ```cpp
  int pd(int x) {
      int w = 0, j = 0;
      for (int i = 1; i <= n + 1; i++) {
          if (a[i] - a[j] < x) w++;
          else j = i;
      }
      return w <= m;
  }
  ```
  **核心思想**：通过判断函数 `pd` 来计算在当前跳跃距离 `x` 下是否满足移除石头的数量限制。

#### 3. 作者：yuyer (★★★★☆)
- **关键亮点**：提供了两种判断函数的实现，分别通过统计移除的石头数量和保留的石头数量来判断。
- **核心代码**：
  ```cpp
  int check(int s) {
      int j = 0, c = 0;
      for (int i = 1; i <= n; i++) {
          if (a[i] - a[j] < s) c++;
          else j = i;
      }
      return c;
  }
  ```
  **核心思想**：通过判断函数 `check` 来计算在当前跳跃距离 `s` 下需要移除的石头数量。

### 最优关键思路与技巧

1. **二分查找**：通过二分查找来枚举可能的跳跃距离，逐步缩小范围，直到找到最大化的最小跳跃距离。
2. **贪心策略**：在判断函数中，使用贪心策略来计算需要移除的石头数量，确保每次移除的石头都是当前最优的选择。
3. **排序**：由于石头的初始位置是无序的，排序是确保二分查找和贪心策略正确性的前提。

### 可拓展之处

- **同类型题**：类似的二分答案问题还有 [P1824](https://www.luogu.org/problem/P1824)、[P1316](https://www.luogu.org/problem/P1316)、[P2678](https://www.luogu.org/problem/P2678)。
- **算法套路**：二分答案 + 贪心策略是解决最大化最小值问题的常见套路，适用于多种场景。

### 推荐题目

1. [P1824 进击的奶牛](https://www.luogu.org/problem/P1824)
2. [P1316 丢瓶盖](https://www.luogu.org/problem/P1316)
3. [P2678 跳石头](https://www.luogu.org/problem/P2678)

### 个人心得摘录

- **seek_my_calling**：强调了排序的重要性，并提醒读者不要忘记将终点石头加入数组。
- **_maze**：详细解释了二分查找的原理，并强调了判断函数的实现细节。
- **yuyer**：提供了两种判断函数的实现，帮助读者更好地理解贪心策略的应用。

这些心得对于理解二分答案问题的实现细节和优化思路非常有帮助。

---
处理用时：28.56秒