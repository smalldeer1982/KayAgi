# 题目信息

# Valera and Contest

## 题目描述

Valera loves to participate in competitions. Especially in programming contests. Today he has participated in the contest with his team, consisting of $ n $ students (including Valera). This contest was an individual competition, so each student in the team solved problems individually.

After the contest was over, Valera was interested in results. He found out that:

- each student in the team scored at least $ l $ points and at most $ r $ points;
- in total, all members of the team scored exactly $ s_{all} $ points;
- the total score of the $ k $ members of the team who scored the most points is equal to exactly $ s_{k} $ ; more formally, if $ a_{1},a_{2},...,a_{n} $ is the sequence of points earned by the team of students in the non-increasing order $ (a_{1}>=a_{2}>=...>=a_{n}) $ , then $ s_{k}=a_{1}+a_{2}+...+a_{k} $ .

However, Valera did not find out exactly how many points each of $ n $ students scored. Valera asked you to recover any distribution of scores between the students of the team, such that all the conditions above are met.

## 样例 #1

### 输入

```
5 3 1 3 13 9
```

### 输出

```
2 3 2 3 3 ```

## 样例 #2

### 输入

```
5 3 1 3 15 9
```

### 输出

```
3 3 3 3 3 ```

# AI分析结果

### 题目内容
# Valera和竞赛

## 题目描述
Valera喜欢参加竞赛，尤其是编程竞赛。今天他和他的团队一起参加了这场竞赛，团队由$n$个学生组成（包括Valera）。这场竞赛是个人赛，所以团队中的每个学生都是独立解题。

竞赛结束后，Valera对结果很感兴趣。他发现：
- 团队中的每个学生得分至少为$l$分，至多为$r$分；
- 团队所有成员的总得分恰好为$s_{all}$分；
- 团队中得分最高的$k$个成员的总得分恰好为$s_{k}$分；更正式地说，如果$a_{1},a_{2},...,a_{n}$是团队学生按非递增顺序（$a_{1} \geq a_{2} \geq... \geq a_{n}$）获得的分数序列，那么$s_{k}=a_{1}+a_{2}+...+a_{k}$。

然而，Valera没有确切知道$n$个学生中每个学生得了多少分。Valera请你恢复团队学生之间的任何一种分数分布，使得上述所有条件都得到满足。

## 样例 #1
### 输入
```
5 3 1 3 13 9
```
### 输出
```
2 3 2 3 3 
```

## 样例 #2
### 输入
```
5 3 1 3 15 9
```
### 输出
```
3 3 3 3 3 
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是将$n$个学生分为前$k$个和后$n - k$个分别处理分数分配。
 - **思路**：先考虑前$k$个学生的分数分配，再处理后$n - k$个学生的分数分配，以满足总分和前$k$名总分的条件。
 - **算法要点**：利用平均分和余数来分配分数。对于前$k$个学生，计算$s_k$除以$k$的商和余数，商作为大部分学生的分数，余数个学生再多得一分；后$n - k$个学生同理，用$s_{all}-s_k$除以$n - k$，按同样方式分配分数。
 - **解决难点**：主要难点在于合理分配分数以满足所有条件，部分题解考虑到$n = k$时的特殊情况避免程序出错。

所有题解整体质量相近，思路清晰程度、代码可读性和优化程度等方面差异不大，均未达到4星标准。

### 通用建议与扩展思路
通用建议：在代码实现时，注意边界条件的处理，如$n = k$的情况，避免出现除零错误。同时，可以适当增加注释提高代码可读性。
扩展思路：此类题目属于构造类型的模拟题，类似的题目可能会改变条件，如改变分数范围的限制方式，或者改变总分与部分学生总分之间的关系等。解题时关键在于根据给定条件，合理设计分配策略，通过模拟实际分配过程来构造出满足要求的结果。

### 相似知识点题目推荐
 - [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)
 - [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)
 - [P1425 小鱼的游泳时间](https://www.luogu.com.cn/problem/P1425) 

---
处理用时：26.62秒