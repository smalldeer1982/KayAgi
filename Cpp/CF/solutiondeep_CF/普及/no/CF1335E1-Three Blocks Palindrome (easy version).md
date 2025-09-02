# 题目信息

# Three Blocks Palindrome (easy version)

## 题目描述

The only difference between easy and hard versions is constraints.

You are given a sequence $ a $ consisting of $ n $ positive integers.

Let's define a three blocks palindrome as the sequence, consisting of at most two distinct elements (let these elements are $ a $ and $ b $ , $ a $ can be equal $ b $ ) and is as follows: $ [\underbrace{a, a, \dots, a}_{x}, \underbrace{b, b, \dots, b}_{y}, \underbrace{a, a, \dots, a}_{x}] $ . There $ x, y $ are integers greater than or equal to $ 0 $ . For example, sequences $ [] $ , $ [2] $ , $ [1, 1] $ , $ [1, 2, 1] $ , $ [1, 2, 2, 1] $ and $ [1, 1, 2, 1, 1] $ are three block palindromes but $ [1, 2, 3, 2, 1] $ , $ [1, 2, 1, 2, 1] $ and $ [1, 2] $ are not.

Your task is to choose the maximum by length subsequence of $ a $ that is a three blocks palindrome.

You have to answer $ t $ independent test cases.

Recall that the sequence $ t $ is a a subsequence of the sequence $ s $ if $ t $ can be derived from $ s $ by removing zero or more elements without changing the order of the remaining elements. For example, if $ s=[1, 2, 1, 3, 1, 2, 1] $ , then possible subsequences are: $ [1, 1, 1, 1] $ , $ [3] $ and $ [1, 2, 1, 3, 1, 2, 1] $ , but not $ [3, 2, 3] $ and $ [1, 1, 1, 1, 2] $ .

## 样例 #1

### 输入

```
6
8
1 1 2 2 3 2 1 1
3
1 3 3
4
1 10 10 1
1
26
2
2 1
3
1 1 1```

### 输出

```
7
2
4
1
1
3```

# AI分析结果

### 题目内容重写
# 三块回文（简单版）

## 题目描述

简单版与困难版的唯一区别在于约束条件。

给定一个由 $n$ 个正整数组成的序列 $a$。

定义一个三块回文为：由最多两个不同元素（设这两个元素为 $a$ 和 $b$，$a$ 可以等于 $b$）组成的序列，形式如下：$[\underbrace{a, a, \dots, a}_{x}, \underbrace{b, b, \dots, b}_{y}, \underbrace{a, a, \dots, a}_{x}]$。其中 $x, y$ 是大于等于 $0$ 的整数。例如，序列 $[]$、$[2]$、$[1, 1]$、$[1, 2, 1]$、$[1, 2, 2, 1]$ 和 $[1, 1, 2, 1, 1]$ 是三块回文，但 $[1, 2, 3, 2, 1]$、$[1, 2, 1, 2, 1]$ 和 $[1, 2]$ 不是。

你的任务是选择 $a$ 的一个最长的子序列，使其为三块回文。

你需要回答 $t$ 个独立的测试用例。

回忆一下，序列 $t$ 是序列 $s$ 的子序列，如果 $t$ 可以通过从 $s$ 中移除零个或多个元素而不改变剩余元素的顺序得到。例如，如果 $s=[1, 2, 1, 3, 1, 2, 1]$，那么可能的子序列是：$[1, 1, 1, 1]$、$[3]$ 和 $[1, 2, 1, 3, 1, 2, 1]$，但不是 $[3, 2, 3]$ 和 $[1, 1, 1, 1, 2]$。

## 样例 #1

### 输入

```
6
8
1 1 2 2 3 2 1 1
3
1 3 3
4
1 10 10 1
1
26
2
2 1
3
1 1 1
```

### 输出

```
7
2
4
1
1
3
```

### 算法分类
枚举、前缀和

### 题解分析与结论
题目要求找到一个最长的子序列，使其为三块回文。由于三块回文的结构固定，可以通过枚举外层元素 $a$ 和中间元素 $b$ 来求解。难点在于如何高效地计算每个可能的 $a$ 和 $b$ 组合的最大长度。

各题解的主要思路如下：
1. **暴力枚举**：通过三重循环枚举分界点 $l$ 和 $r$，再枚举 $a$ 和 $b$，利用前缀和快速计算各区间的元素出现次数。时间复杂度较高，但思路清晰。
2. **贪心策略**：固定外层元素 $a$，从两端向中间取，尽可能多地保留中间元素 $b$ 的位置。通过预处理每个元素的位置，优化了时间复杂度。
3. **枚举外层元素**：枚举外层元素 $a$ 和 $x$，计算中间元素 $b$ 的最大出现次数。通过维护前缀和和每个元素的位置，优化了计算过程。

### 评分较高的题解
1. **作者：_JF_**  
   **星级：4星**  
   **关键亮点**：通过贪心策略，固定外层元素 $a$，从两端向中间取，优化了时间复杂度。代码实现清晰，利用了前缀和和位置记录，提高了效率。  
   **核心代码**：
   ```cpp
   int Slove(int l,int r,int dus,int op){
       int sum=0;
       for(int i=1;i<=200;i++){
           if(op==i)	continue;
           int now=s[i][r-1]-s[i][l];
           sum=max(sum,now);
       }
       return sum;
   }
   ```
   **个人心得**：通过贪心策略，从两端向中间取，能够最大化中间元素 $b$ 的位置，从而优化了计算过程。

2. **作者：One_JuRuo**  
   **星级：4星**  
   **关键亮点**：通过枚举外层元素 $a$ 和 $x$，计算中间元素 $b$ 的最大出现次数。利用前缀和和位置记录，优化了计算过程。代码实现清晰，逻辑严谨。  
   **核心代码**：
   ```cpp
   for(int i=1;i<=26;++i)
       if(v[i].size()>1)
       {
           res=0;
           for(int j=0;j<=(int)ceil(1.0*(v[i].size()-2)/2);++j)
           {
               int l=v[i][j],r=v[i][v[i].size()-j-1];
               if(l==r) ans=max(ans,res+1);
               else
               {
                   res+=2;
                   for(int k=1;k<=26;++k) if(k!=i) ans=max(ans,res+num[r-1][k]-num[l][k]);
               }
           }
       }
   ```
   **个人心得**：通过枚举外层元素 $a$ 和 $x$，能够有效地计算中间元素 $b$ 的最大出现次数，优化了计算过程。

### 最优关键思路或技巧
1. **贪心策略**：固定外层元素 $a$，从两端向中间取，能够最大化中间元素 $b$ 的位置，从而优化计算过程。
2. **前缀和**：利用前缀和快速计算各区间的元素出现次数，提高了计算效率。
3. **位置记录**：通过记录每个元素的位置，能够快速定位外层元素 $a$ 的位置，优化了枚举过程。

### 可拓展之处
1. **类似题目**：可以扩展到更多块的回文结构，如五块回文、七块回文等。
2. **优化策略**：可以通过动态规划或更高效的枚举策略进一步优化时间复杂度。

### 推荐题目
1. [P1439 【模板】最长公共子序列](https://www.luogu.com.cn/problem/P1439)
2. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)
3. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)

---
处理用时：43.39秒