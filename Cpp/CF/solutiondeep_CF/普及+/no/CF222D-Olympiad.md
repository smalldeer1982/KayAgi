# 题目信息

# Olympiad

## 题目描述

A boy named Vasya has taken part in an Olympiad. His teacher knows that in total Vasya got at least $ x $ points for both tours of the Olympiad. The teacher has the results of the first and the second tour of the Olympiad but the problem is, the results have only points, no names. The teacher has to know Vasya's chances.

Help Vasya's teacher, find two numbers — the best and the worst place Vasya could have won. Note that the total results' table sorts the participants by the sum of points for both tours (the first place has the participant who has got the most points). If two or more participants have got the same number of points, it's up to the jury to assign places to them according to their choice. It is guaranteed that each participant of the Olympiad participated in both tours of the Olympiad.

## 说明/提示

In the first text sample all 5 participants earn 2 points each in any case. Depending on the jury's decision, Vasya can get the first (the best) as well as the last (the worst) fifth place.

In the second test sample in the best case scenario Vasya wins again: he can win 12 points and become the absolute winner if the total results' table looks like that — {4:8, 6:4, 3:6, 4:4, 4:3, 5:0}.

In this table all participants are sorted by decreasing points and we can see how much a participant earned in the first and in the second tour.

In the worst case scenario Vasya can get the fifth place if the table looks like that — {4:8, 4:6, 6:4, 5:4, 4:3, 3:0}, and he earned 4 and 3 points in the first and second tours, correspondingly.

## 样例 #1

### 输入

```
5 2
1 1 1 1 1
1 1 1 1 1
```

### 输出

```
1 5
```

## 样例 #2

### 输入

```
6 7
4 3 5 6 4 4
8 6 0 4 3 4
```

### 输出

```
1 5
```

# AI分析结果

### 题目内容
# Olympiad

## 题目描述
有个叫 Vasya 的男孩参加了一场奥林匹克竞赛。他的老师知道，Vasya 两场竞赛的总得分至少为 \(x\) 分。老师有所有参赛者两场竞赛的成绩，但问题是，成绩表上只有分数，没有名字。老师想知道 Vasya 可能获得的名次范围。

请帮助 Vasya 的老师，找出两个数 —— Vasya 可能获得的最好名次和最差名次。注意，总成绩表是按照参赛者两场竞赛的总分进行排序的（总分最高的参赛者排第一名）。如果有两个或更多参赛者的总分相同，由评审团根据他们的选择来分配名次。保证每位参赛者都参加了两场竞赛。

## 说明/提示
在第一个示例中，所有 5 名参赛者在任何情况下的总分都是 2 分。根据评审团的决定，Vasya 既可以获得第一名（最好情况），也可以获得最后一名（最差情况），即第五名。

在第二个测试示例中，在最好的情况下 Vasya 再次获胜：如果总成绩表是这样的 —— {4:8, 6:4, 3:6, 4:4, 4:3, 5:0}，他可以得到 12 分并成为绝对冠军。

在这个表中，所有参赛者按得分降序排列，我们可以看到每个参赛者在第一场和第二场竞赛中分别获得了多少分。

在最坏的情况下，如果成绩表是这样的 —— {4:8, 4:6, 6:4, 5:4, 4:3, 3:0}，Vasya 可以获得第五名，他在第一场和第二场竞赛中分别获得了 4 分和 3 分。

## 样例 #1
### 输入
```
5 2
1 1 1 1 1
1 1 1 1 1
```
### 输出
```
1 5
```
## 样例 #2
### 输入
```
6 7
4 3 5 6 4 4
8 6 0 4 3 4
```
### 输出
```
1 5
```
### 算法分类
贪心
### 综合分析与结论
所有题解思路基本一致，都认为由于 Vasya 得分无上限，所以最好名次是第 1 名。而求最差名次时，大家都采用贪心策略，让第一场考试成绩较差的同学第二场考试成绩较好，通过对两场成绩数组排序后遍历，统计成绩大于等于 \(x\) 的人数，以此确定最差名次。不同题解在代码实现细节上略有差异，如排序方式、变量命名、输入输出方式等。
### 通用建议与扩展思路
通用建议：在解决此类问题时，要清晰理解题意，明确贪心策略的正确性，并注意代码实现中的细节，如数组下标、边界条件等。
扩展思路：类似题目可能会改变成绩的限制条件，或者改变排名的计算规则，例如按照单科成绩排名，或者总分相同情况下有更复杂的排名规则等。也可能将问题拓展到多维数组或更复杂的数据结构中，需要根据具体情况灵活运用贪心思想。
### 相似知识点洛谷题目
1. [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
2. [P2859 [USACO06DEC]Milk Patterns G](https://www.luogu.com.cn/problem/P2859)
3. [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)

---
处理用时：24.00秒