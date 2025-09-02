# 题目信息

# Yet Another Yet Another Task

## 题目描述

Alice and Bob are playing yet another card game. This time the rules are the following. There are $ n $ cards lying in a row in front of them. The $ i $ -th card has value $ a_i $ .

First, Alice chooses a non-empty consecutive segment of cards $ [l; r] $ ( $ l \le r $ ). After that Bob removes a single card $ j $ from that segment $ (l \le j \le r) $ . The score of the game is the total value of the remaining cards on the segment $ (a_l + a_{l + 1} + \dots + a_{j - 1} + a_{j + 1} + \dots + a_{r - 1} + a_r) $ . In particular, if Alice chooses a segment with just one element, then the score after Bob removes the only card is $ 0 $ .

Alice wants to make the score as big as possible. Bob takes such a card that the score is as small as possible.

What segment should Alice choose so that the score is maximum possible? Output the maximum score.

## 说明/提示

In the first example Alice chooses a segment $ [1;5] $ — the entire row of cards. Bob removes card $ 3 $ with the value $ 10 $ from the segment. Thus, the final score is $ 5 + (-2) + (-1) + 4 = 6 $ .

In the second example Alice chooses a segment $ [1;4] $ , so that Bob removes either card $ 1 $ or $ 3 $ with the value $ 5 $ , making the answer $ 5 + 2 + 3 = 10 $ .

In the third example Alice can choose any of the segments of length $ 1 $ : $ [1;1] $ , $ [2;2] $ or $ [3;3] $ . Bob removes the only card, so the score is $ 0 $ . If Alice chooses some other segment then the answer will be less than $ 0 $ .

## 样例 #1

### 输入

```
5
5 -2 10 -1 4```

### 输出

```
6```

## 样例 #2

### 输入

```
8
5 2 5 3 -30 -30 6 9```

### 输出

```
10```

## 样例 #3

### 输入

```
3
-10 6 -15```

### 输出

```
0```

# AI分析结果

【题目内容】
# 又一个又一个任务

## 题目描述

Alice和Bob正在玩又一个卡牌游戏。这次规则如下：有$n$张牌排成一列，第$i$张牌的值为$a_i$。

首先，Alice选择一个非空的连续区间$[l, r]$（$l \le r$）。之后，Bob从这个区间中移除一张牌$j$（$l \le j \le r$）。游戏的得分是剩余牌的总值$(a_l + a_{l + 1} + \dots + a_{j - 1} + a_{j + 1} + \dots + a_{r - 1} + a_r)$。特别地，如果Alice选择的区间只有一个元素，那么移除该牌后得分为$0$。

Alice希望得分尽可能大，而Bob则会移除一张牌使得得分尽可能小。

Alice应该选择哪个区间，使得得分最大？输出最大得分。

## 说明/提示

在第一个样例中，Alice选择区间$[1;5]$——整个牌列。Bob移除第$3$张牌，值为$10$。因此，最终得分为$5 + (-2) + (-1) + 4 = 6$。

在第二个样例中，Alice选择区间$[1;4]$，Bob移除第$1$张或第$3$张牌，值为$5$，得分为$5 + 2 + 3 = 10$。

在第三个样例中，Alice可以选择任何长度为$1$的区间：$[1;1]$、$[2;2]$或$[3;3]$。Bob移除唯一的牌，得分为$0$。如果Alice选择其他区间，得分将小于$0$。

## 样例 #1

### 输入

```
5
5 -2 10 -1 4```

### 输出

```
6```

## 样例 #2

### 输入

```
8
5 2 5 3 -30 -30 6 9```

### 输出

```
10```

## 样例 #3

### 输入

```
3
-10 6 -15```

### 输出

```
0```

【算法分类】  
动态规划

【题解分析与结论】  
该题的核心问题是如何选择一个区间，使得在移除该区间中的最大值后，剩余元素的和最大。由于Bob会移除区间中的最大值，因此Alice需要选择一个区间，使得区间和减去最大值后的值最大。

题解中，大多数解法都利用了$a_i$的值域较小的特点，通过枚举最大值来简化问题。常见的思路包括：
1. **枚举最大值**：通过枚举可能的最大值，计算在该最大值限制下的最大区间和。
2. **前缀和优化**：利用前缀和快速计算区间和，并结合单调栈或ST表来优化区间最大值的查找。
3. **动态规划**：通过动态规划维护区间和与最大值的关系，逐步求解最优解。

【评分较高的题解】  
1. **作者：45dinо (赞：12)**  
   - **星级：5星**  
   - **关键亮点**：通过枚举最大值，结合前缀和与简单的区间和优化，实现了高效的解法。代码简洁，思路清晰，充分利用了$a_i$的值域特点。  
   - **核心代码**：
     ```cpp
     for(int i=1;i<=31;i++) {
         res=0;
         for(int j=1;j<=n;j++) {
             res+=a[j];
             if(a[j]>i) res=0;
             res=max(res,0);
             ans=max(ans,res-i);
         }
     }
     ```
   - **个人心得**：作者提到通过枚举最大值来简化问题，避免了复杂的算法和数据结构，体现了“黄题用黄题方法做”的思路。

2. **作者：Lily_White (赞：6)**  
   - **星级：4星**  
   - **关键亮点**：通过枚举最大值，结合前缀和优化，减少了枚举的维度，提高了算法效率。思路清晰，代码可读性较好。  
   - **核心代码**：
     ```cpp
     for(int m=1;m<=31;m++) {
         res=0;
         for(int r=1;r<=n;r++) {
             sum+=a[r];
             if(a[r]>m || sum<0) sum=0;
             ans=max(ans,sum-m);
         }
     }
     ```
   - **个人心得**：作者通过证明枚举最大值的正确性，确保了算法的严谨性，避免了不必要的复杂操作。

3. **作者：fighter (赞：2)**  
   - **星级：4星**  
   - **关键亮点**：通过单调栈和ST表预处理，快速找到每个数作为最大值时的左右边界，并结合前缀和优化，实现了高效的解法。  
   - **核心代码**：
     ```cpp
     for(int i=1;i<=n;i++) {
         int p1 = i, p2 = n-p1+1;
         int t1 = s1.query(p1, s1.r[p1]-1)-s1.s[p1];
         int t2 = s2.query(p2, s2.r[p2]-1)-s2.s[p2];
         ans = max(ans, t1+t2);
     }
     ```
   - **个人心得**：作者通过单调栈和ST表的结合，优化了区间最大值的查找，体现了对数据结构的熟练运用。

【最优关键思路】  
通过枚举最大值，结合前缀和优化，可以高效地解决该问题。这种方法充分利用了$a_i$的值域特点，避免了复杂的算法和数据结构，同时保证了算法的正确性和高效性。

【拓展与举一反三】  
类似的问题可以通过枚举关键值（如最大值、最小值等）来简化问题，尤其是在值域较小的情况下。此外，前缀和与单调栈的结合也是处理区间问题的常用技巧。

【推荐题目】  
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)  
2. [P1440 求m区间内的最小值](https://www.luogu.com.cn/problem/P1440)  
3. [P2216 [HAOI2007]理想的正方形](https://www.luogu.com.cn/problem/P2216)

---
处理用时：42.03秒