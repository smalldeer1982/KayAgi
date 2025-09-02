# 题目信息

# Maximum width

## 题目描述

Your classmate, whom you do not like because he is boring, but whom you respect for his intellect, has two strings: $ s $ of length $ n $ and $ t $ of length $ m $ .

A sequence $ p_1, p_2, \ldots, p_m $ , where $ 1 \leq p_1 < p_2 < \ldots < p_m \leq n $ , is called beautiful, if $ s_{p_i} = t_i $ for all $ i $ from $ 1 $ to $ m $ . The width of a sequence is defined as $ \max\limits_{1 \le i < m} \left(p_{i + 1} - p_i\right) $ .

Please help your classmate to identify the beautiful sequence with the maximum width. Your classmate promised you that for the given strings $ s $ and $ t $ there is at least one beautiful sequence.

## 说明/提示

In the first example there are two beautiful sequences of width $ 3 $ : they are $ \{1, 2, 5\} $ and $ \{1, 4, 5\} $ .

In the second example the beautiful sequence with the maximum width is $ \{1, 5\} $ .

In the third example there is exactly one beautiful sequence — it is $ \{1, 2, 3, 4, 5\} $ .

In the fourth example there is exactly one beautiful sequence — it is $ \{1, 2\} $ .

## 样例 #1

### 输入

```
5 3
abbbc
abc```

### 输出

```
3```

## 样例 #2

### 输入

```
5 2
aaaaa
aa```

### 输出

```
4```

## 样例 #3

### 输入

```
5 5
abcdf
abcdf```

### 输出

```
1```

## 样例 #4

### 输入

```
2 2
ab
ab```

### 输出

```
1```

# AI分析结果

### 题目翻译
你的同学有两个字符串：$s$ 和 $t$，长度分别为 $n$ 和 $m$。一个序列 $p_1, p_2, \ldots, p_m$，其中 $1 \leq p_1 < p_2 < \ldots < p_m \leq n$，被称为“美丽序列”，如果对于所有 $i$ 从 $1$ 到 $m$，$s_{p_i} = t_i$。序列的宽度定义为 $\max\limits_{1 \le i < m} \left(p_{i + 1} - p_i\right)$。

请帮助你的同学找到宽度最大的美丽序列。你的同学保证给定的字符串 $s$ 和 $t$ 至少存在一个美丽序列。

### 算法分类
贪心

### 题解分析与结论
该题的核心思路是通过贪心策略，找到每个字符在 $s$ 中的最早和最晚出现位置，然后计算相邻字符的最大间隔。所有题解都采用了类似的思路，即通过两次遍历（一次从前向后，一次从后向前）来确定每个字符的最早和最晚位置，最后计算最大间隔。

### 所选高星题解
1. **作者：HC20050615 (4星)**
   - **关键亮点**：代码简洁，思路清晰，通过两次遍历分别记录每个字符的最早和最晚位置，最后计算最大间隔。
   - **代码核心思想**：
     ```cpp
     for(int i=1,j=0;i<=m;i++) {
         while(s[++j]!=t[i]);
         first[i]=j;
     }
     for(int i=m,j=n+1;i>=1;i--) {
         while(s[--j]!=t[i]);
         last[i]=j;
     }
     for(int i=1;i<=m-1;i++) {
         maxs=max(maxs,last[i+1]-first[i]);
     }
     ```

2. **作者：超级玛丽王子 (4星)**
   - **关键亮点**：代码结构清晰，变量命名合理，通过两次遍历分别记录每个字符的最早和最晚位置，最后计算最大间隔。
   - **代码核心思想**：
     ```cpp
     for(int i=0;i<n&&stp<m;++i) 
         if(s[i]==t[stp]) fst[stp++]=i;
     stp=m-1;
     for(int i=n-1;~i&&stp;--i) 
         if(s[i]==t[stp]) last[stp--]=i;
     for(int i=1;i<m;++i) {
         cur=last[i]-fst[i-1];
         if(cur>mx) mx=cur;
     }
     ```

3. **作者：白鲟 (4星)**
   - **关键亮点**：代码简洁优雅，通过两次遍历分别记录每个字符的最早和最晚位置，最后计算最大间隔。
   - **代码核心思想**：
     ```cpp
     for(int i=0,now=0;i<n&&now<m;++i)
         if(a[i]==b[now]) pos[0][now++]=i;
     for(int i=n-1,now=m-1;~i&&~now;--i)
         if(a[i]==b[now]) pos[1][now--]=i;
     for(int i=1;i<m;++i)
         ans=max(pos[1][i]-pos[0][i-1],ans);
     ```

### 最优关键思路
通过两次遍历（一次从前向后，一次从后向前）来确定每个字符的最早和最晚位置，最后计算相邻字符的最大间隔。这种贪心策略能够有效地解决问题，且时间复杂度为 $O(n)$。

### 可拓展之处
类似的问题可以通过贪心策略解决，尤其是涉及到最大化或最小化某些间隔或距离的问题。例如，最大化子序列中相邻元素的最小距离，或最小化子序列中相邻元素的最大距离。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
3. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)

---
处理用时：32.45秒