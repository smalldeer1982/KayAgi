# 题目信息

# Big Vova

## 题目描述

Alexander is a well-known programmer. Today he decided to finally go out and play football, but with the first hit he left a dent on the new Rolls-Royce of the wealthy businessman Big Vova. Vladimir has recently opened a store on the popular online marketplace "Zmey-Gorynych", and offers Alex a job: if he shows his programming skills by solving a task, he'll work as a cybersecurity specialist. Otherwise, he'll be delivering some doubtful products for the next two years.

You're given $ n $ positive integers $ a_1, a_2, \dots, a_n $ . Using each of them exactly at once, you're to make such sequence $ b_1, b_2, \dots, b_n $ that sequence $ c_1, c_2, \dots, c_n $ is lexicographically maximal, where $ c_i=GCD(b_1,\dots,b_i) $ - the greatest common divisor of the first $ i $ elements of $ b $ .

Alexander is really afraid of the conditions of this simple task, so he asks you to solve it.

A sequence $ a $ is lexicographically smaller than a sequence $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ differ, the sequence $ a $ has a smaller element than the corresponding element in $ b $ .

## 说明/提示

In the first test case of the example, there are only two possible permutations $ b $ — $ [2, 5] $ and $ [5, 2] $ : for the first one $ c=[2, 1] $ , for the second one $ c=[5, 1] $ .

In the third test case of the example, number $ 9 $ should be the first in $ b $ , and $ GCD(9, 3)=3 $ , $ GCD(9, 8)=1 $ , so the second number of $ b $ should be $ 3 $ .

In the seventh test case of the example, first four numbers pairwise have a common divisor (a power of two), but none of them can be the first in the optimal permutation $ b $ .

## 样例 #1

### 输入

```
7
2
2 5
4
1 8 2 3
3
3 8 9
5
64 25 75 100 50
1
42
6
96 128 88 80 52 7
5
2 4 8 16 17```

### 输出

```
5 2 
8 2 1 3 
9 3 8 
100 50 25 75 64 
42 
128 96 80 88 52 7 
17 2 4 8 16```

# AI分析结果

### 题目内容重写

**Big Vova**

**题目描述**

Alexander 是一位著名的程序员。今天他决定出去踢足球，但第一次踢球时，他不小心在富商 Big Vova 的新 Rolls-Royce 上留下了一个凹痕。Vladimir 最近在流行的在线市场 "Zmey-Gorynych" 上开了一家商店，并给 Alex 提供了一份工作：如果他通过解决一个任务展示他的编程技能，他将成为网络安全专家。否则，他将在接下来的两年里运送一些可疑的产品。

给定 $n$ 个正整数 $a_1, a_2, \dots, a_n$，你需要将它们重新排列成一个序列 $b_1, b_2, \dots, b_n$，使得序列 $c_1, c_2, \dots, c_n$ 的字典序最大，其中 $c_i=GCD(b_1,\dots,b_i)$，即序列 $b$ 的前 $i$ 个元素的最大公约数。

Alexander 对这个简单的任务感到非常害怕，所以他请你来解决它。

一个序列 $a$ 字典序小于序列 $b$，当且仅当以下条件之一成立：

- $a$ 是 $b$ 的前缀，但 $a \ne b$；
- 在 $a$ 和 $b$ 第一个不同的位置，序列 $a$ 的元素小于序列 $b$ 的对应元素。

**说明/提示**

在第一个测试用例中，只有两种可能的排列 $b$ — $[2, 5]$ 和 $[5, 2]$：对于第一种排列，$c=[2, 1]$；对于第二种排列，$c=[5, 1]$。

在第三个测试用例中，数字 $9$ 应该是 $b$ 的第一个元素，且 $GCD(9, 3)=3$，$GCD(9, 8)=1$，所以 $b$ 的第二个元素应该是 $3$。

在第七个测试用例中，前四个数字两两之间有一个共同的除数（2 的幂），但它们中没有一个可以作为最优排列 $b$ 的第一个元素。

### 算法分类

贪心

### 题解分析与结论

题目要求重新排列一个整数序列，使得其前缀 GCD 序列的字典序最大。核心思路是贪心算法：每次选择当前能使前缀 GCD 最大的元素。

**题解对比：**

1. **wsyhb 的题解**（5星）
   - **亮点**：思路清晰，代码简洁，时间复杂度分析准确。
   - **核心思路**：每次选择当前能使前缀 GCD 最大的元素，使用标记数组避免重复选择。
   - **代码实现**：
     ```cpp
     for(int i=2;i<=n;++i) {
         int max_d=0,id=0;
         for(int j=1;j<=n;++j)
             if(a[j]) {
                 int v=gcd(a[j],d);
                 if(v>max_d) {
                     max_d=v;
                     id=j;
                 }
             }
         printf("%d%c",a[id],i<n?' ':'\n');
         a[id]=0;
         d=max_d;
     }
     ```

2. **lzy120406 的题解**（4星）
   - **亮点**：思路明确，代码可读性好，时间复杂度分析准确。
   - **核心思路**：每次选择当前能使前缀 GCD 最大的元素，使用标记数组避免重复选择。
   - **代码实现**：
     ```cpp
     for(int j = 0; j < n; ++j) {
         if(!used[j]) {
             int k = gcd(GCD, a[j]);
             if(k > maxx) {
                 maxx = k;
                 idx = j;
             }
         }
     }
     ```

3. **Nuclear_Fish_cyq 的题解**（4星）
   - **亮点**：思路清晰，代码实现详细，时间复杂度分析准确。
   - **核心思路**：每次选择当前能使前缀 GCD 最大的元素，使用标记数组避免重复选择。
   - **代码实现**：
     ```cpp
     for(int j = 0; j < n; j++) {
         if(!flag[j]) {
             if(gcd(a[j], now) > maxn) {
                 maxn = gcd(a[j], now);
                 maxi = j;
             }
         }
     }
     ```

### 最优关键思路

贪心算法是解决该问题的核心。每次选择当前能使前缀 GCD 最大的元素，确保前缀 GCD 序列的字典序最大。使用标记数组避免重复选择元素。

### 可拓展之处

类似的问题可以通过贪心算法解决，尤其是在需要最大化或最小化某种序列性质时。例如，最大化前缀和、最小化前缀积等问题。

### 推荐题目

1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)

### 个人心得摘录

- **wsyhb**：突然发现忘记贴代码了，却发现管理员光速审完了这篇题解，麻烦管理员再审一遍。
- **Nuclear_Fish_cyq**：翻译没有翻译全数据范围，是能过的。

这些心得反映了作者在解题过程中遇到的细节问题和对题解质量的关注。

---
处理用时：41.80秒