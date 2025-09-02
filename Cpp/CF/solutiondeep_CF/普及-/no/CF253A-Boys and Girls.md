# 题目信息

# Boys and Girls

## 题目描述

There are $ n $ boys and $ m $ girls studying in the class. They should stand in a line so that boys and girls alternated there as much as possible. Let's assume that positions in the line are indexed from left to right by numbers from 1 to $ n+m $ . Then the number of integers $ i $ ( $ 1<=i&lt;n+m $ ) such that positions with indexes $ i $ and $ i+1 $ contain children of different genders (position $ i $ has a girl and position $ i+1 $ has a boy or vice versa) must be as large as possible.

Help the children and tell them how to form the line.

## 说明/提示

In the first sample another possible answer is BGBGBG.

In the second sample answer BBGBGB is also optimal.

## 样例 #1

### 输入

```
3 3
```

### 输出

```
GBGBGB
```

## 样例 #2

### 输入

```
4 2
```

### 输出

```
BGBGBB
```

# AI分析结果

### 题目内容
# 男孩和女孩

## 题目描述
班上有 $n$ 名男生和 $m$ 名女生在学习。他们要站成一列，以便男孩和女孩尽可能交替出现。假设队列中同学的位置从左到右由数字 $1$ 到 $n + m$ 索引。那么，满足索引为 $i$ 和 $i + 1$ 的位置上是不同性别的孩子（位置 $i$ 是女孩，位置 $i + 1$ 是男孩，反之亦然）的整数 $i$（$1 \leq i \lt n + m$）的数量必须尽可能大。

帮助孩子们，告诉他们如何站成一列。

## 说明/提示
在第一个样例中，另一个可能的答案是 BGBGBG。

在第二个样例中，答案 BBGBGB 也是最优的。

## 样例 #1
### 输入
```
3 3
```
### 输出
```
GBGBGB
```

## 样例 #2
### 输入
```
4 2
```
### 输出
```
BGBGBB
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路均为贪心策略，要点在于先让男女生交替排列，再将多余的人排在末尾。不同题解在实现细节上略有差异，但本质相同。难点在于处理男女生人数不同时，如何保证交替次数最多，所有题解都通过比较男女生人数，先输出数量少的一方与另一方交替的组合，再输出多余一方的剩余部分来解决。

### 通用建议与扩展思路
通用建议：此类贪心问题关键在于理解如何通过局部最优选择达到全局最优，实现时注意边界条件和特殊情况处理。
扩展思路：类似的贪心题目通常涉及资源分配、任务调度等场景，解决时需明确最优目标，确定贪心策略。例如在资源分配中，每次选择能带来最大收益的分配方式。

### 洛谷题目推荐
- P1094 [纪念品分组](https://www.luogu.com.cn/problem/P1094)：通过贪心策略对纪念品分组，使组数最少。
- P1199 [三国游戏](https://www.luogu.com.cn/problem/P1199)：利用贪心思想在游戏中选择最优策略。
- P1080 [国王游戏](https://www.luogu.com.cn/problem/P1080)：需通过合理的贪心排序解决问题。

### 个人心得摘录与总结
- “话说明天阶段检测我咋还在写题解~~这题真心神奇。。。竟然真要文件输入输出，我第一次不信邪结果TLE了~~我还以为RemoteJudge万能呢~~”：强调了本题文件输入输出的特殊要求，不按要求做可能导致超时。 

---
处理用时：16.76秒