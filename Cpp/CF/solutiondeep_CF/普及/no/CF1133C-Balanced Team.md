# 题目信息

# Balanced Team

## 题目描述

You are a coach at your local university. There are $ n $ students under your supervision, the programming skill of the $ i $ -th student is $ a_i $ .

You have to create a team for a new programming competition. As you know, the more students some team has the more probable its victory is! So you have to create a team with the maximum number of students. But you also know that a team should be balanced. It means that the programming skill of each pair of students in a created team should differ by no more than $ 5 $ .

Your task is to report the maximum possible number of students in a balanced team.

## 说明/提示

In the first example you can create a team with skills $ [12, 17, 15] $ .

In the second example you can take all students in a team because their programming skills are equal.

In the third example you can create a team consisting of a single student (and you cannot create a team consisting of at least two students).

## 样例 #1

### 输入

```
6
1 10 17 12 15 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
10
1337 1337 1337 1337 1337 1337 1337 1337 1337 1337
```

### 输出

```
10
```

## 样例 #3

### 输入

```
6
1 1000 10000 10 100 1000000000
```

### 输出

```
1
```

# AI分析结果

【题目内容重写】
# 平衡团队

## 题目描述

你是当地大学的一名教练。你手下有 $n$ 名学生，第 $i$ 名学生的编程能力为 $a_i$。

你需要为一场新的编程比赛组建一个团队。众所周知，团队中的学生越多，获胜的概率就越大！因此，你需要组建一个尽可能大的团队。但你也知道，团队应该是平衡的。这意味着，团队中每对学生之间的编程能力差异不应超过 $5$。

你的任务是报告一个平衡团队中可能的最大学生人数。

## 说明/提示

在第一个样例中，你可以组建一个能力为 $[12, 17, 15]$ 的团队。

在第二个样例中，你可以将所有学生都纳入团队，因为他们的编程能力相同。

在第三个样例中，你可以组建一个由单个学生组成的团队（你无法组建一个至少由两名学生组成的团队）。

## 样例 #1

### 输入

```
6
1 10 17 12 15 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
10
1337 1337 1337 1337 1337 1337 1337 1337 1337 1337
```

### 输出

```
10
```

## 样例 #3

### 输入

```
6
1 1000 10000 10 100 1000000000
```

### 输出

```
1
```

【算法分类】
排序、双指针

【题解分析与结论】
本题的核心思路是通过排序和双指针技巧来找到满足条件的最长连续子序列。排序后，使用双指针维护一个窗口，使得窗口内的最大值与最小值之差不超过5。通过滑动窗口的方式，可以高效地找到最长的满足条件的子序列。

【精选题解】
1. **作者：Rbu_nas (赞：3)**
   - **星级：4**
   - **关键亮点：使用双指针技巧，思路清晰，代码简洁。**
   - **核心代码：**
     ```cpp
     int j=1;    //指针起点，因为最少也能有1名学生参赛
     for(int i=1; i<=n; ++i)
         while(j <= n && a[j] <= a[i]+5)    //不断更新a[i]~a[j]区间长度
         {
             res=max(res, j-i+1);
             ++j;
         }
     ```
   - **个人心得：通过排序后，双指针可以高效地找到满足条件的最长子序列。**

2. **作者：微分几何 (赞：2)**
   - **星级：4**
   - **关键亮点：使用双指针，代码简洁，逻辑清晰。**
   - **核心代码：**
     ```cpp
     int ans=0,r=1;
     for(int i=1;i<=n;i++)
     {
         while(r+1<=n&&a[r+1]-a[i]<=5)
         {
             r++;
         }
         ans=max(ans,r-i+1);
     }
     ```
   - **个人心得：通过保留最大区间的右端点，可以高效地更新答案。**

3. **作者：LlLlCc (赞：1)**
   - **星级：4**
   - **关键亮点：使用双指针，代码简洁，思路清晰。**
   - **核心代码：**
     ```cpp
     for (int i=2;i<=n;i++){
         while (a[i]-a[hed]>5) hed++;
         ans=max(ans,i-hed+1);
     }
     ```
   - **个人心得：通过维护一个指针hed，可以高效地找到满足条件的最长子序列。**

【最优关键思路】
通过排序后，使用双指针维护一个窗口，使得窗口内的最大值与最小值之差不超过5。通过滑动窗口的方式，可以高效地找到最长的满足条件的子序列。

【拓展思路】
类似的问题可以扩展到其他条件，如差值不超过某个值，或者满足其他约束条件。双指针技巧在处理这类问题时非常有效。

【推荐题目】
1. P1102 A-B 数对（双指针）
2. P1638 逛画展（双指针）
3. P1712 [NOI2016] 区间（双指针+贪心）

---
处理用时：24.38秒