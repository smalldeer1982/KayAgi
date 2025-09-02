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

1. **最长不下降子序列（LIS）与最长不上升子序列（LDS）**：通过计算序列的最长不下降子序列和最长不上升子序列，取最大值后用总长度减去该值，得到最小修改次数。
2. **动态规划（DP）**：通过状态转移方程，记录每个位置在不同状态下的最小修改次数，最终取最小值。
3. **二分查找优化**：在计算LIS和LDS时，使用二分查找来优化时间复杂度，从O(n^2)降低到O(nlogn)。
4. **滚动数组优化**：在DP过程中使用滚动数组来优化空间复杂度。

### 精选题解

#### 1. **作者：奶酥奶酥QwQ (5星)**
- **关键亮点**：使用了基于二分查找的LIS和LDS解法，时间复杂度为O(nlogn)，代码简洁且高效。
- **代码核心思想**：通过维护两个数组`f1`和`f2`，分别记录最长不下降和最长不上升子序列的最后一个数字，使用`upper_bound`进行二分查找优化。
```cpp
int cnt = 1; f1[cnt] = A[1];
for(int i = 2; i <= n; i++){
    if(A[i] >= f1[cnt]){
        f1[++cnt] = A[i];
    } else
        *upper_bound(f1+1, f1+cnt+1, A[i]) = A[i];
}
int ans = cnt;
cnt = 1; f2[cnt] = A[1];
for(int i = 2; i <= n; i++){
    if(A[i] <= f2[cnt]) f2[++cnt] = A[i];
    else *upper_bound(f2+1, f2+1+cnt, A[i], greater<int>()) = A[i];
}
printf("%d\n", n - max(ans, cnt));
```

#### 2. **作者：Priori_Incantatem (4星)**
- **关键亮点**：使用了动态规划的思路，通过状态转移方程计算每个位置在不同状态下的最小修改次数，思路清晰。
- **代码核心思想**：定义`f[i][j]`表示第i头牛的编号为j时，让1~i这个序列合法需要的最少操作次数，通过分类讨论进行状态转移。
```cpp
if(a[i]==1){
    f[i][0]=f[i-1][0];
    f[i][1]=min(f[i-1][1],f[i-1][0])+1;
    f[i][2]=min(f[i-1][2],min(f[i-1][0],f[i-1][1]))+1;
}
if(a[i]==2){
    f[i][0]=f[i-1][0]+1;
    f[i][1]=min(f[i-1][1],f[i-1][0]);
    f[i][2]=min(f[i-1][0],min(f[i-1][1],f[i-1][2]))+1;
}
if(a[i]==3){
    f[i][0]=f[i-1][0]+1;
    f[i][1]=min(f[i-1][0],f[i-1][1])+1;
    f[i][2]=min(f[i-1][0],min(f[i-1][1],f[i-1][2]));
}
```

#### 3. **作者：小柯 (4星)**
- **关键亮点**：使用了滚动数组优化，进一步减少了空间复杂度，代码实现简洁。
- **代码核心思想**：通过滚动数组`f1`和`f2`，分别记录递增和递减序列的最小修改次数，使用`Min`函数进行状态转移。
```cpp
for(int i=1;i<=n;i++){
    d=r();
    ii=i&1,iii=(i+1)&1;
    if(d==1){
        f1[ii][1]=f1[iii][1];
        f1[ii][2]=Min(f1[iii][1],f1[iii][2])+1;
        f1[ii][3]=Min(f1[iii][1],f1[iii][2],f1[iii][3])+1;
        f2[ii][1]=Min(f2[iii][1],f2[iiii][2],f2[iii][3]);
        f2[ii][2]=Min(f2[iii][2],f2[iii][3])+1;
        f2[ii][3]=f2[iii][3]+1;
    }
    // 其他情况类似
}
```

### 最优关键思路与技巧

1. **二分查找优化**：在计算LIS和LDS时，使用二分查找可以将时间复杂度从O(n^2)优化到O(nlogn)，适用于数据量较大的情况。
2. **动态规划状态转移**：通过定义状态转移方程，可以清晰地描述每个位置在不同状态下的最小修改次数，适用于需要分类讨论的问题。
3. **滚动数组优化**：在DP过程中使用滚动数组可以减少空间复杂度，适用于内存有限的情况。

### 可拓展之处

1. **类似题目**：可以扩展到其他需要将序列变为单调序列的问题，如将序列变为严格递增或递减序列。
2. **其他优化**：可以尝试使用其他数据结构（如线段树）来进一步优化时间复杂度。

### 推荐题目

1. **P2837 晚餐队列安排**：与本题类似，要求将序列变为单调序列。
2. **P1020 导弹拦截**：考察最长不上升子序列和最长不下降子序列。
3. **P1091 合唱队形**：考察序列的单调性变化。

### 个人心得摘录

- **调试经历**：在实现二分查找时，需要注意边界条件的处理，避免出现死循环或越界问题。
- **踩坑教训**：在动态规划中，状态转移方程的设计要清晰，避免遗漏某些情况。
- **顿悟感想**：通过二分查找优化LIS和LDS的计算，极大地提高了算法的效率，感受到了算法优化的魅力。

---
处理用时：28.34秒