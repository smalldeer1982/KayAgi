# 题目信息

# Debate

## 题目描述

Elections in Berland are coming. There are only two candidates — Alice and Bob.

The main Berland TV channel plans to show political debates. There are $ n $ people who want to take part in the debate as a spectator. Each person is described by their influence and political views. There are four kinds of political views:

- supporting none of candidates (this kind is denoted as "00"),
- supporting Alice but not Bob (this kind is denoted as "10"),
- supporting Bob but not Alice (this kind is denoted as "01"),
- supporting both candidates (this kind is denoted as "11").

The direction of the TV channel wants to invite some of these people to the debate. The set of invited spectators should satisfy three conditions:

- at least half of spectators support Alice (i.e. $ 2 \cdot a \ge m $ , where $ a $ is number of spectators supporting Alice and $ m $ is the total number of spectators),
- at least half of spectators support Bob (i.e. $ 2 \cdot b \ge m $ , where $ b $ is number of spectators supporting Bob and $ m $ is the total number of spectators),
- the total influence of spectators is maximal possible.

Help the TV channel direction to select such non-empty set of spectators, or tell that this is impossible.

## 说明/提示

In the first example $ 4 $ spectators can be invited to maximize total influence: $ 1 $ , $ 2 $ , $ 3 $ and $ 6 $ . Their political views are: "11", "10", "01" and "00". So in total $ 2 $ out of $ 4 $ spectators support Alice and $ 2 $ out of $ 4 $ spectators support Bob. The total influence is $ 6+4+3+9=22 $ .

In the second example the direction can select all the people except the $ 5 $ -th person.

In the third example the direction can select people with indices: $ 1 $ , $ 4 $ , $ 5 $ and $ 6 $ .

In the fourth example it is impossible to select any non-empty set of spectators.

## 样例 #1

### 输入

```
6
11 6
10 4
01 3
00 3
00 7
00 9
```

### 输出

```
22
```

## 样例 #2

### 输入

```
5
11 1
01 1
00 100
10 1
01 1
```

### 输出

```
103
```

## 样例 #3

### 输入

```
6
11 19
10 22
00 18
00 29
11 29
10 28
```

### 输出

```
105
```

## 样例 #4

### 输入

```
3
00 5000
00 5000
00 5000
```

### 输出

```
0
```

# AI分析结果

【题目内容】
# 辩论

## 题目描述

Berland的选举即将到来。只有两位候选人——Alice和Bob。

Berland的主要电视频道计划展示政治辩论。有$n$个人想作为观众参与辩论。每个人都有自己的影响力和政治观点。政治观点有四种：

- 不支持任何候选人（用“00”表示），
- 支持Alice但不支持Bob（用“10”表示），
- 支持Bob但不支持Alice（用“01”表示），
- 同时支持两位候选人（用“11”表示）。

电视台希望邀请一些人参加辩论。邀请的观众集合需要满足以下三个条件：

- 至少有一半的观众支持Alice（即$2 \cdot a \ge m$，其中$a$是支持Alice的观众人数，$m$是观众总人数），
- 至少有一半的观众支持Bob（即$2 \cdot b \ge m$，其中$b$是支持Bob的观众人数，$m$是观众总人数），
- 观众的总影响力尽可能大。

帮助电视台选择这样一个非空的观众集合，或者说明这是不可能的。

## 说明/提示

在第一个例子中，可以邀请4位观众以最大化总影响力：$1$、$2$、$3$和$6$。他们的政治观点分别是：“11”、“10”、“01”和“00”。因此，总共有$2$位观众支持Alice，$2$位观众支持Bob。总影响力为$6+4+3+9=22$。

在第二个例子中，电视台可以选择除第$5$位之外的所有人。

在第三个例子中，电视台可以选择索引为$1$、$4$、$5$和$6$的人。

在第四个例子中，不可能选择任何非空的观众集合。

## 样例 #1

### 输入

```
6
11 6
10 4
01 3
00 3
00 7
00 9
```

### 输出

```
22
```

## 样例 #2

### 输入

```
5
11 1
01 1
00 100
10 1
01 1
```

### 输出

```
103
```

## 样例 #3

### 输入

```
6
11 19
10 22
00 18
00 29
11 29
10 28
```

### 输出

```
105
```

## 样例 #4

### 输入

```
3
00 5000
00 5000
00 5000
```

### 输出

```
0
```

【算法分类】
贪心

【题解分析与结论】
本题的核心是通过贪心策略选择观众，使得在满足支持Alice和Bob的条件的同时，最大化总影响力。各题解的思路基本一致，主要分为以下几个步骤：
1. 优先选择支持Alice和Bob的观众（“11”），因为他们的加入不会影响条件，且能直接增加影响力。
2. 将只支持Alice（“10”）和只支持Bob（“01”）的观众进行配对，因为每对“10”和“01”的加入也不会影响条件。
3. 最后处理不支持任何候选人（“00”）和剩余的“10”或“01”观众，按照影响力从大到小选择，直到无法满足条件为止。

【评分较高的题解】
1. **作者：bzzltl (4星)**
   - **关键亮点**：详细证明了“10”和“01”配对的合理性，代码结构清晰，逻辑严谨。
   - **代码核心**：
     ```cpp
     sort(t10+1,t10+jl1+1,cmp);
     sort(t01+1,t01+jl2+1,cmp);
     int mn=min(jl1,jl2);
     for(int i=1;i<=mn;i++) ans+=t01[i]+t10[i];
     ```

2. **作者：是个汉子 (4星)**
   - **关键亮点**：提出了“01”和“10”全部选出的结论，并通过枚举优化了选择过程，代码简洁高效。
   - **代码核心**：
     ```cpp
     for(int i=0;i<=num[1];i++){
         if(num[3]+i<num[2]||num[3]+num[2]<i) continue;
         ans=max(ans,a[1][i]+a[2][num[2]]+a[0][min(num[0],min(num[3]+i-num[2],num[3]+num[2]-i))]);
     }
     ```

3. **作者：Tjaweiof (4星)**
   - **关键亮点**：将“11”观众直接加入答案，并通过排序和配对处理“10”和“01”，代码实现简单明了。
   - **代码核心**：
     ```cpp
     for(int i=1;i<=tot4;i++) ans+=d[i];
     for(int i=1;i<=min(tot2,tot3);i++) ans+=b[i]+c[i];
     ```

【最优关键思路】
1. 优先选择“11”观众，因为他们的加入不会影响条件，且能直接增加影响力。
2. 将“10”和“01”观众配对，因为每对“10”和“01”的加入也不会影响条件。
3. 最后处理“00”和剩余的“10”或“01”观众，按照影响力从大到小选择，直到无法满足条件为止。

【拓展思路】
类似的问题可以通过贪心策略解决，尤其是当问题涉及在满足某些条件下最大化或最小化某个值时。例如，资源分配、任务调度等问题。

【推荐题目】
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)

---
处理用时：42.44秒