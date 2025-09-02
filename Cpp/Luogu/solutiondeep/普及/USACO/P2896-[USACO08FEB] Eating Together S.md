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
题目要求将序列变为非严格递增或递减，最少修改次数。核心思路是求最长不降/不升子序列，用总长度减去最大长度。解法主要分为两类：**二分优化法（O(n log n)）**和**线性状态转移DP（O(n)）**。前者适用于一般情况，后者利用元素范围有限（1-3）实现高效计算。

---

### 高星题解推荐

#### 1. 奶酥奶酥QwQ（★★★★★）
**关键亮点**：  
- 使用标准二分法求最长不降/不升子序列，时间复杂度O(n log n)。  
- 正确处理非严格序列，利用`upper_bound`和`greater<int>()`维护序列。  
**代码核心**：
```cpp
// 最长不降序列（递增）
int cnt = 1;
f1[cnt] = A[1];
for (int i = 2; i <= n; i++) {
    if (A[i] >= f1[cnt]) f1[++cnt] = A[i];
    else *upper_bound(f1+1, f1+cnt+1, A[i]) = A[i];
}
// 最长不升序列（递减）
cnt = 1;
f2[cnt] = A[1];
for (int i = 2; i <= n; i++) {
    if (A[i] <= f2[cnt]) f2[++cnt] = A[i];
    else *upper_bound(f2+1, f2+1+cnt, A[i], greater<int>()) = A[i];
}
```

#### 2. Priori_Incantatem（★★★★★）
**关键亮点**：  
- 线性DP，状态表示当前位的值，分升序和降序处理。  
- 时间复杂度O(n)，空间优化后更高效。  
**代码核心**：
```cpp
// 升序处理
if (a[i] == 1) {
    f[i][0] = f[i-1][0]; // 无需修改
    f[i][1] = min(f[i-1][0], f[i-1][1]) + 1; // 改为2，需修改
    f[i][2] = min({f[i-1][0], f[i-1][1], f[i-1][2]}) + 1; // 改为3
}
// 类似处理其他情况...
```

#### 3. 一只书虫仔（★★★★★）
**关键亮点**：  
- 分升序和降序独立处理，状态转移直观。  
- 代码简洁，直接计算最小修改次数。  
**代码核心**：
```cpp
for (int i = 1; i <= n; i++) {
    // 升序DP
    dp1[i][1] = dp1[i-1][1] + (d[i] != 1);
    dp1[i][2] = min(dp1[i-1][1], dp1[i-1][2]) + (d[i] != 2);
    dp1[i][3] = min({dp1[i-1][1], dp1[i-1][2], dp1[i-1][3]}) + (d[i] != 3);
    // 降序DP类似...
}
```

---

### 最优思路总结
1. **二分优化法**：维护最长不降/不升子序列，利用二分查找快速更新序列，时间复杂度O(n log n)。  
2. **线性状态转移DP**：针对元素范围有限（1-3），分状态记录当前位的可能值，动态规划求最小修改次数，时间复杂度O(n)。  

---

### 类似题目推荐
1. **P1091 合唱队形**（最长上升子序列变种）  
2. **P2782 友好城市**（二维排序后求LIS）  
3. **P1280 尼克的任务**（状态转移与时间规划）  

---

### 个人心得摘录
- **程雅馨**：优化内层循环倒序，遇到相同元素提前终止，减少重复比较。  
- **奶酥奶酥QwQ**：强调正确处理非严格序列时`upper_bound`与比较函数的配合。  
- **呆瓜yy**：调试中发现状态转移顺序对结果的影响，需严格保证递推顺序。

---
处理用时：119.89秒