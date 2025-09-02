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

本题的核心问题是通过最少的修改次数，将给定的序列变为单调递增或单调递减的序列。大多数题解采用了**最长不下降子序列（LIS）**和**最长不上升子序列（LDS）**的思路，通过计算这两个序列的长度，最终用总长度减去较长的序列长度得到最小修改次数。部分题解还针对序列中只有1、2、3的特点进行了优化，进一步提高了算法的效率。

### 所选高星题解

#### 1. **作者：奶酥奶酥QwQ (赞：14)**
- **星级：5星**
- **关键亮点：**
  - 使用了基于二分查找的LIS和LDS优化算法，时间复杂度为O(n log n)，适合大规模数据。
  - 通过`upper_bound`函数快速找到插入位置，避免了传统的O(n²)复杂度。
  - 代码简洁，逻辑清晰，易于理解。
- **核心代码：**
```cpp
int cnt = 1; f1[cnt] = A[1];
for(int i = 2; i <= n; i++){
    if(A[i] >= f1[cnt]){
        f1[++cnt] = A[i];
    } else
        *upper_bound(f1+1, f1+cnt+1, A[i]) = A[i];
}
```
- **个人心得：**
  - 通过二分查找优化LIS的求解过程，显著提升了算法效率。

#### 2. **作者：Priori_Incantatem (赞：9)**
- **星级：4星**
- **关键亮点：**
  - 使用了动态规划的思路，通过状态转移方程分别计算单调递增和单调递减的最小修改次数。
  - 代码结构清晰，状态转移方程明确，适合理解动态规划的基本思想。
- **核心代码：**
```cpp
if(a[i]==1){
    f[i][0]=f[i-1][0];
    f[i][1]=min(f[i-1][1],f[i-1][0])+1;
    f[i][2]=min(f[i-1][2],min(f[i-1][0],f[i-1][1]))+1;
}
```
- **个人心得：**
  - 通过状态转移方程逐步推导，最终得到最小修改次数。

#### 3. **作者：一只书虫仔 (赞：7)**
- **星级：4星**
- **关键亮点：**
  - 通过升维的方式，利用动态规划分别计算单调递增和单调递减的最小修改次数。
  - 代码结构清晰，状态转移方程明确，适合理解动态规划的基本思想。
- **核心代码：**
```cpp
dp1[i][1] = dp1[i - 1][1] + int(d[i] != 1);
dp1[i][2] = min(dp1[i - 1][1], dp1[i - 1][2]) + int(d[i] != 2);
dp1[i][3] = min(dp1[i - 1][1], min(dp1[i - 1][2], dp1[i - 1][3])) + int(d[i] != 3);
```
- **个人心得：**
  - 通过升维的方式，简化了状态转移方程的计算过程。

### 最优关键思路与技巧

1. **二分查找优化LIS/LDS**：通过二分查找将LIS/LDS的求解复杂度从O(n²)降低到O(n log n)，适合大规模数据处理。
2. **动态规划状态转移**：通过状态转移方程逐步推导最小修改次数，适合理解动态规划的基本思想。
3. **序列特性优化**：利用序列中只有1、2、3的特点，进一步优化算法，减少不必要的计算。

### 可拓展之处

1. **类似题目**：可以扩展到其他需要将序列变为单调递增或递减的问题，如最长上升子序列、最长下降子序列等。
2. **其他优化**：可以尝试使用其他数据结构（如线段树）进一步优化LIS/LDS的求解过程。

### 推荐题目

1. **P1020 导弹拦截**：考察最长不上升子序列和最长上升子序列的求解。
2. **P1091 合唱队形**：考察双向LIS的求解。
3. **P2782 友好城市**：考察LIS的应用。

### 个人心得总结

- **调试经历**：在优化LIS/LDS的过程中，二分查找的边界条件需要特别注意，避免出现错误。
- **踩坑教训**：在动态规划中，状态转移方程的推导需要仔细，避免遗漏某些情况。
- **顿悟感想**：通过二分查找优化LIS/LDS的求解过程，显著提升了算法效率，理解其原理后可以举一反三应用于其他类似问题。

---
处理用时：33.77秒