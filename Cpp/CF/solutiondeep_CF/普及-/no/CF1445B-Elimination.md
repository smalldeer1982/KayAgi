# 题目信息

# Elimination

## 题目描述

There is a famous olympiad, which has more than a hundred participants. The Olympiad consists of two stages: the elimination stage, and the final stage. At least a hundred participants will advance to the final stage. The elimination stage in turn consists of two contests.

A result of the elimination stage is the total score in two contests, but, unfortunately, the jury lost the final standings and has only standings for the first and for the second contest separately.

In each contest, the participants are ranked by their point score in non-increasing order. When two participants have a tie (earned the same score), they are ranked by their passport number (in accordance with local regulations, all passport numbers are distinct).

In the first contest, the participant on the 100-th place scored $ a $ points. Also, the jury checked all participants from the 1-st to the 100-th place (inclusive) in the first contest and found out that all of them have at least $ b $ points in the second contest.

Similarly, for the second contest, the participant on the 100-th place has $ c $ points. And the jury checked that all the participants from the 1-st to the 100-th place (inclusive) have at least $ d $ points in the first contest.

After two contests, all participants are ranked by their total score in two contests in non-increasing order. When participants have the same total score, tie-breaking with passport numbers is used. The cutoff score to qualify to the final stage is the total score of the participant on the 100-th place.

Given integers $ a $ , $ b $ , $ c $ , $ d $ , please help the jury determine the smallest possible value of the cutoff score.

## 说明/提示

For the first test case, consider the following olympiad scenario: there are $ 101 $ participants in the elimination stage, each having $ 1 $ point for the first contest and $ 2 $ points for the second contest. Hence the total score of the participant on the 100-th place is $ 3 $ .

For the second test case, consider the following olympiad scenario:

- there are $ 50 $ participants with points $ 5 $ and $ 9 $ for the first and second contest respectively;
- $ 50 $ participants with points $ 4 $ and $ 8 $ for the first and second contest respectively;
- and $ 50 $ participants with points $ 2 $ and $ 9 $ for the first and second contest respectively.

 Hence the total point score of the participant on the 100-th place is $ 12 $ .

## 样例 #1

### 输入

```
2
1 2 2 1
4 8 9 2```

### 输出

```
3
12```

# AI分析结果

### 题目内容
# 淘汰赛

## 题目描述
有一场著名的奥林匹克竞赛，有一百多名参赛者。该竞赛由两个阶段组成：淘汰赛阶段和决赛阶段。至少有一百名参赛者将晋级决赛阶段。淘汰赛阶段又由两场比赛组成。

淘汰赛阶段的结果是两场比赛的总分数，但不幸的是，评委们丢失了最终排名，只分别有第一场和第二场比赛的排名。

在每场比赛中，参赛者根据他们的得分按非递增顺序排名。当两名参赛者得分相同时（得分相同），他们根据护照号码排名（根据当地规定，所有护照号码都是不同的）。

在第一场比赛中，第100名的参赛者得了$a$分。此外，评委检查了第一场比赛中第1名到第100名（包括）的所有参赛者，发现他们在第二场比赛中都至少得了$b$分。

同样，对于第二场比赛，第100名的参赛者得了$c$分。评委检查了第二场比赛中第1名到第100名（包括）的所有参赛者，发现他们在第一场比赛中都至少得了$d$分。

两场比赛结束后，所有参赛者根据他们在两场比赛中的总分数按非递增顺序排名。当参赛者总分数相同时，使用护照号码进行排名。晋级决赛阶段的分数线是第100名参赛者的总分数。

给定整数$a$、$b$、$c$、$d$，请帮助评委确定分数线的最小可能值。

## 说明/提示
对于第一个测试用例，考虑以下竞赛场景：淘汰赛阶段有101名参赛者，每个人在第一场比赛中得1分，在第二场比赛中得2分。因此，第100名参赛者的总分数是3分。

对于第二个测试用例，考虑以下竞赛场景：
 - 有50名参赛者在第一场和第二场比赛中的分数分别为5分和9分；
 - 50名参赛者在第一场和第二场比赛中的分数分别为4分和8分；
 - 还有50名参赛者在第一场和第二场比赛中的分数分别为2分和9分。

因此，第100名参赛者的总分数是12分。

## 样例 #1
### 输入
```
2
1 2 2 1
4 8 9 2
```
### 输出
```
3
12
```

• **算法分类**：数学
• **综合分析与结论**：这些题解思路基本一致，均基于对比赛得分情况的数学分析。要点在于明确第一场前100名总分最小值为$a + b$，第二场前100名总分最小值为$c + d$，而题目要求总分第100名分数的最小值，由于只能有100人晋级，所以要取$max(a + b, c + d)$。难点在于理解为什么要取两者最大值，若取较小值会导致有超过100人总分大于等于该值，不符合题目要求。
• **通用建议与扩展思路**：此类题目关键在于理解各数据间的逻辑关系，通过分析极端情况来确定答案。对于类似的比赛排名、分数计算问题，都可以从分析各部分得分的最值情况入手。同类型题可考虑一些涉及多场比赛综合排名，通过局部信息推导整体排名分数线的问题。
• **推荐题目**：
  - [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)
  - [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)
  - [P1255 数楼梯](https://www.luogu.com.cn/problem/P1255)
• **个人心得摘录与总结**：部分作者提到在证明$max(a + b, c + d)$为正确答案时花费了较多时间讨论，说明对于看似简单的结论，严谨的证明很重要，不能仅凭直觉。同时，部分作者通过观察样例来辅助理解题意，这也是解决复杂题目时的有效方法。 

---
处理用时：33.92秒