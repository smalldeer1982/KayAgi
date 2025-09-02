# 题目信息

# [USACO08FEB] Eating Together S

## 题目描述

The cows are so very silly about their dinner partners. They have organized themselves into three groups (conveniently numbered 1, 2, and 3) that insist upon dining together. The trouble starts when they line up at the barn to enter the feeding area.

Each cow i carries with her a small card upon which is engraved Di (1 ≤ Di ≤ 3) indicating her dining group membership. The entire set of N (1 ≤ N ≤ 30,000) cows has lined up for dinner but it's easy for anyone to see that they are not grouped by their dinner-partner cards.

FJ's job is not so difficult. He just walks down the line of cows changing their dinner partner assignment by marking out the old number and writing in a new one. By doing so, he creates groups of cows like 111222333 or 333222111 where the cows' dining groups are sorted in either ascending or descending order by their dinner cards.

FJ is just as lazy as the next fellow. He's curious: what is the absolute mminimum number of cards he must change to create a proper grouping of dining partners? He must only change card numbers and must not rearrange the cows standing in line.

FJ的奶牛们在吃晚饭时很傻。他们把自己组织成三组（方便编号为1, 2和3），坚持一起用餐。当他们在谷仓排队进入喂食区时，麻烦就开始了。


每头奶牛都随身带着一张小卡片，小卡片上刻的是Di（1≤Di≤3）表示她属于哪一组。所有的N（1≤N≤30000）头奶牛排队吃饭，但他们并不能按卡片上的分组站好。


FJ的工作并不是那么难。他只是沿着牛的路线走下去，把旧的号码标出来，换上一个新的。通过这样做，他创造了一群奶牛，比如111222333或333222111，奶牛的就餐组按他们的晚餐卡片按升序或降序排列。


FJ就像任何人一样懒惰。他很好奇：怎样他才能进行适当的分组，使得他只要修改最少次数的数字？由于奶牛们已经很长时间没有吃到饭了，所以“哞哞”的声音到处都是，FJ只好更换卡号，而不能重新排列已经排好队的奶牛。


## 说明/提示

感谢@一思千年 提供翻译


## 样例 #1

### 输入

```
5
1
3
2
1
1
```

### 输出

```
1
```

# AI分析结果

### 综合分析与结论

本题的核心问题是通过最少的修改次数，将给定的序列变为单调递增或单调递减的序列。题解中主要采用了以下几种思路：

1. **最长不下降子序列（LIS）与最长不上升子序列（LDS）**：通过计算序列的最长不下降子序列和最长不上升子序列，取其中较长的长度，然后用总长度减去该长度，得到最小修改次数。这种方法的时间复杂度为O(n^2)，但在优化后可以达到O(n log n)。

2. **动态规划（DP）**：通过状态转移方程，记录每个位置在单调递增或递减情况下的最小修改次数。这种方法的时间复杂度为O(n)，且适用于序列中元素种类较少的情况（如本题中只有1、2、3）。

3. **二分查找优化**：在计算LIS和LDS时，使用二分查找来优化时间复杂度，将O(n^2)优化为O(n log n)。

### 所选高星题解

#### 1. 作者：奶酥奶酥QwQ (★★★★★)
- **关键亮点**：使用二分查找优化LIS和LDS的计算，时间复杂度为O(n log n)，代码简洁且高效。
- **核心思想**：通过维护一个数组记录各个长度LIS的最后一个数字，利用二分查找快速更新LIS和LDS的长度。
- **代码片段**：
  ```cpp
  int cnt = 1; f1[cnt] = A[1];
  for(int i = 2; i <= n; i++){
      if(A[i] >= f1[cnt]){
          f1[++cnt] = A[i];
      } else
          *upper_bound(f1+1, f1+cnt+1, A[i]) = A[i];
  }
  ```

#### 2. 作者：Priori_Incantatem (★★★★☆)
- **关键亮点**：使用动态规划，记录每个位置在单调递增或递减情况下的最小修改次数，时间复杂度为O(n)。
- **核心思想**：通过状态转移方程，分别计算单调递增和单调递减情况下的最小修改次数，最后取最小值。
- **代码片段**：
  ```cpp
  if(a[i] == 1){
      f[i][0] = f[i-1][0];
      f[i][1] = min(f[i-1][1], f[i-1][0]) + 1;
      f[i][2] = min(f[i-1][2], min(f[i-1][0], f[i-1][1])) + 1;
  }
  ```

#### 3. 作者：zht467 (★★★★☆)
- **关键亮点**：使用动态规划，记录每个位置在单调递增或递减情况下的最小修改次数，时间复杂度为O(n)。
- **核心思想**：通过状态转移方程，分别计算单调递增和单调递减情况下的最小修改次数，最后取最小值。
- **代码片段**：
  ```cpp
  f[i][1][0] = f[i-1][1][0] + (a[i] != 1);
  f[i][2][0] = min(f[i-1][1][0], f[i-1][2][0]) + (a[i] != 2);
  f[i][3][0] = min(f[i-1][1][0], min(f[i-1][2][0], f[i-1][3][0])) + (a[i] != 3);
  ```

### 最优关键思路与技巧

1. **二分查找优化LIS/LDS**：在计算最长不下降子序列或最长不上升子序列时，使用二分查找可以将时间复杂度从O(n^2)优化到O(n log n)，适用于大规模数据。

2. **动态规划状态转移**：通过状态转移方程，记录每个位置在单调递增或递减情况下的最小修改次数，适用于序列中元素种类较少的情况。

3. **滚动数组优化空间**：在动态规划中，使用滚动数组可以减少空间复杂度，适用于大规模数据。

### 可拓展之处

1. **类似题目**：可以扩展到序列中元素种类较多的情况，或者要求序列满足其他条件（如严格递增或递减）。

2. **算法套路**：动态规划和二分查找是解决序列问题的常用套路，可以应用到其他类似问题中。

### 推荐题目

1. **P1020 导弹拦截**：考察最长不上升子序列和最长不下降子序列的应用。
2. **P1091 合唱队形**：考察序列的双向单调性。
3. **P2782 友好城市**：考察序列的匹配与单调性。

### 个人心得摘录

- **奶酥奶酥QwQ**：通过二分查找优化LIS和LDS的计算，显著提高了代码的效率。
- **Priori_Incantatem**：使用动态规划记录每个位置的最小修改次数，思路清晰且易于理解。
- **zht467**：通过状态转移方程分别计算单调递增和递减情况下的最小修改次数，代码简洁且高效。

---
处理用时：32.91秒