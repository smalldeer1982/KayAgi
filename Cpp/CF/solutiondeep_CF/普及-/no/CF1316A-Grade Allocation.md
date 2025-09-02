# 题目信息

# Grade Allocation

## 题目描述

$ n $ students are taking an exam. The highest possible score at this exam is $ m $ . Let $ a_{i} $ be the score of the $ i $ -th student. You have access to the school database which stores the results of all students.

You can change each student's score as long as the following conditions are satisfied:

- All scores are integers
- $ 0 \leq a_{i} \leq m $
- The average score of the class doesn't change.

You are student $ 1 $ and you would like to maximize your own score.

Find the highest possible score you can assign to yourself such that all conditions are satisfied.

## 说明/提示

In the first case, $ a = [1,2,3,4]  $ , with average of $ 2.5 $ . You can change array $ a $ to $ [10,0,0,0] $ . Average remains $ 2.5 $ , and all conditions are satisfied.

In the second case, $ 0 \leq a_{i} \leq 5 $ . You can change $ a $ to $ [5,1,1,3] $ . You cannot increase $ a_{1} $ further as it will violate condition $ 0\le a_i\le m $ .

## 样例 #1

### 输入

```
2
4 10
1 2 3 4
4 5
1 2 3 4```

### 输出

```
10
5```

# AI分析结果

### 题目内容
# 成绩分配

## 题目描述
有\(n\)名学生参加一场考试，这场考试的最高可能分数是\(m\)。设\(a_{i}\)为第\(i\)名学生的分数。你可以访问存储所有学生成绩的学校数据库。

只要满足以下条件，你就可以更改每个学生的分数：
- 所有分数均为整数。
- \(0 \leq a_{i} \leq m\)。
- 班级的平均分数不变。

你是学生1，你想最大化自己的分数。

在满足所有条件的情况下，找出你能给自己分配的最高分数。

## 说明/提示
在第一种情况下，\(a = [1,2,3,4]\)，平均分为\(2.5\)。你可以将数组\(a\)更改为\([10,0,0,0]\)。平均分仍为\(2.5\)，且所有条件均满足。

在第二种情况下，\(0 \leq a_{i} \leq 5\)。你可以将\(a\)更改为\([5,1,1,3]\)。你不能再进一步提高\(a_{1}\)，因为这将违反\(0\le a_i\le m\)这个条件。

## 样例 #1
### 输入
```
2
4 10
1 2 3 4
4 5
1 2 3 4
```
### 输出
```
10
5
```

### 算法分类
贪心

### 综合分析与结论
所有题解的核心思路均为贪心策略，即要使1号学生分数最大，在保证总分不变（因为平均分数不变意味着总分不变）且每个学生分数在\(0\)到\(m\)之间的条件下，让其他学生分数尽可能为\(0\)，将其他学生的分数都给1号学生。但1号学生分数不能超过\(m\)，所以最终1号学生的最高分数为所有学生分数总和与\(m\)中的较小值。各题解思路清晰，代码实现也较为简单直接，区别主要在于代码风格和细节处理上。

### 通用建议与扩展思路
对于此类贪心问题，关键在于找到合理的贪心策略。在思考过程中，可以从极端情况出发，如本题中让其他学生分数为\(0\)这种极端情况来使目标学生分数最大化。同类型题通常围绕在满足一定条件下对某些量进行最值求解，类似算法套路是分析条件，找到能使目标量最优的分配方式。例如在资源分配问题中，在资源总量和分配限制条件下，如何分配资源使某个目标收益最大等。

### 洛谷相似题目推荐
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
- [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)
- [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)

### 个人心得摘录与总结
部分作者提到要注意初始化（如`sum = 0`等），这是编程中的一个重要细节，若未初始化可能导致结果错误。还有作者表示看到大佬们用`while`循环处理多组数据，自己以后也会使用，这体现了学习优秀代码风格对提升编程能力的帮助。 

---
处理用时：33.00秒