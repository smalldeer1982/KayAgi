# 题目信息

# 「Wdcfr-1」Alice Wins!  (easy version)

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/zshuq5iq.png)


## 题目描述

**The difference between the versions is the limit of operations.**

Alice is a cute girl who has a lot of dolls.

There are $4\cdot n$ dolls playing *rock-paper-scissors*. They are divided into two teams: Team A and Team B. Each team contains $2\cdot n$ dolls.

A total of $2\cdot n$ rounds of the game will be played. In the $i$-th round, the $i$-th doll in Team A will play against the $i$-th doll in Team B. If the doll in Team A wins, Team A will get $1$ point. If it loses, Team A will lose $1$ point. If it ties, Team A will not get points.

Alice knows all the dolls' choices in this game. To be precise, she uses two arrays $a$ and $b$ to represent the choices of the dolls in the two teams. $a_i$ means the choice of the $i$-th doll in Team A, and $b_i$ means the choice of the $i$-th doll in Team B. In this question, we use $1$ for rock, $2$ for scissors, and $3$ for paper.

Now for **each team**, Alice wants to change the choices of **at most** $n$ dolls to make the score of Team A as high as possible.

Find the maximum score of Team A and its construction method. If there are multiple answers print any of them (you still have to maximize the score of Team A).

## 说明/提示

### Explanation

For the first test case, we can change $a_2$ to $1$ and $b_1$ to $2$. Then Team A can get $2$ points. It can be proved that this is the maximum score that Team A can get.

For the second test case, we can change $a_1$ to $3$ and $a_2$ to $1$.

### Constraints

$1\le T,n \le 10^5;\ 1\le a_i,b_i \le 3$. The sum of $n$ over all test cases  $\le 10^5$.

## 样例 #1

### 输入

```
2
1
1 2
1 2
2
2 3 1 3
1 2 2 1```

### 输出

```
2
1 1
2 2
4
3 1 1 3
1 2 2 1```

# AI分析结果

### 算法分类
贪心

### 综合分析与结论
题目要求通过改变A队和B队的出拳选择，使得A队的得分最大化。由于每队最多只能改变n次，因此可以通过贪心策略，分别在前n轮改变A队的出拳，使得A队赢得比赛；在后n轮改变B队的出拳，使得B队输给A队。这样A队可以确保在每一轮都得分，最终得分为2n。

### 所选高星题解
1. **作者：zct_sky (赞：3)**
   - **星级：4**
   - **关键亮点**：思路清晰，代码简洁，直接通过改变A队前n个和B队后n个的出拳来确保A队全胜。
   - **核心代码**：
     ```cpp
     for(int i=1;i<=n;i++) {
         if(b[i]==1) a[i]=3;
         if(b[i]==2) a[i]=1;
         if(b[i]==3) a[i]=2;
     }
     for(int i=n+1;i<=2*n;i++) {
         if(a[i]==1) b[i]=2;
         if(a[i]==2) b[i]=3;
         if(a[i]==3) b[i]=1;
     }
     ```
   - **个人心得**：通过直接改变A队和B队的出拳，确保A队全胜，思路简单直接。

2. **作者：ahawzlc (赞：1)**
   - **星级：4**
   - **关键亮点**：使用模运算简化判断条件，代码简洁高效。
   - **核心代码**：
     ```cpp
     for(int i=1;i<=n;i++) a[i]=(b[i]+2)%3;
     for(int i=n+1;i<=n<<1;i++) b[i]=(a[i]+1)%3;
     ```
   - **个人心得**：通过模运算简化了出拳的判断，代码更加简洁。

3. **作者：一只书虫仔 (赞：0)**
   - **星级：4**
   - **关键亮点**：思路清晰，代码简洁，直接通过改变A队前n个和B队后n个的出拳来确保A队全胜。
   - **核心代码**：
     ```cpp
     for(int i=1;i<=n;i++) {
         if(b[i]==1) a[i]=3;
         if(b[i]==2) a[i]=1;
         if(b[i]==3) a[i]=2;
     }
     for(int i=n+1;i<=2*n;i++) {
         if(a[i]==1) b[i]=2;
         if(a[i]==2) b[i]=3;
         if(a[i]==3) b[i]=1;
     }
     ```
   - **个人心得**：通过直接改变A队和B队的出拳，确保A队全胜，思路简单直接。

### 最优关键思路或技巧
通过贪心策略，分别在前n轮改变A队的出拳，使得A队赢得比赛；在后n轮改变B队的出拳，使得B队输给A队。这样A队可以确保在每一轮都得分，最终得分为2n。

### 可拓展之处
类似的问题可以通过贪心策略，分别对不同的部分进行优化，以达到全局最优解。例如，在资源分配问题中，可以通过贪心策略分别对不同的资源进行优化分配。

### 推荐题目
1. [P1007 独木桥](https://www.luogu.com.cn/problem/P1007)
2. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
3. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)

---
处理用时：25.48秒