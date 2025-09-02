# 题目信息

# Quality vs Quantity

## 题目描述

$  \def\myred#1{\color{red}{\underline{\bf{#1}}}} \def\myblue#1{\color{blue}{\overline{\bf{#1}}}}  $ $ \def\RED{\myred{Red}} \def\BLUE{\myblue{Blue}} $

You are given a sequence of $ n $ non-negative integers $ a_1, a_2, \ldots, a_n $ . Initially, all the elements of the sequence are unpainted. You can paint each number $ \RED $ or $ \BLUE $ (but not both), or leave it unpainted.

For a color $ c $ , $ \text{Count}(c) $ is the number of elements in the sequence painted with that color and $ \text{Sum}(c) $ is the sum of the elements in the sequence painted with that color.

For example, if the given sequence is $ [2, 8, 6, 3, 1] $ and it is painted this way: $ [\myblue{2}, 8, \myred{6}, \myblue{3}, 1] $ (where $ 6 $ is painted red, $ 2 $ and $ 3 $ are painted blue, $ 1 $ and $ 8 $ are unpainted) then $ \text{Sum}(\RED)=6 $ , $ \text{Sum}(\BLUE)=2+3=5 $ , $ \text{Count}(\RED)=1 $ , and $ \text{Count}(\BLUE)=2 $ .

Determine if it is possible to paint the sequence so that $ \text{Sum}(\RED) > \text{Sum}(\BLUE) $ and $ \text{Count}(\RED) < \text{Count}(\BLUE) $ .

## 说明/提示

In the first test case, there is no possible way to paint the sequence. For example, if you paint the sequence this way: $ [\myblue{1},\myblue{2},\myred{3}] $ (where $ 3 $ is painted red, $ 1 $ and $ 2 $ are painted blue) then $ \text{Count}(\RED)=1 < \text{Count}(\BLUE)=2 $ , but $ \text{Sum}(\RED)=3 \ngtr \text{Sum}(\BLUE)=3 $ . So, this is not a possible way to paint the sequence.

In the second test case, a possible way to paint the sequence is described in the statement. We can see that $ \text{Sum}(\RED)=6 > \text{Sum}(\BLUE)=5 $ and $ \text{Count}(\RED)=1 < \text{Count}(\BLUE)=2 $ .

In the third test case, there is no possible way to paint the sequence. For example, if you paint the sequence this way: $ [\myred{3},\myred{5},\myblue{4}, \myblue{2}] $ (where $ 3 $ and $ 5 $ are painted red, $ 4 $ and $ 2 $ are painted blue) then $ \text{Sum}(\RED) = 8 > \text{Sum}(\BLUE) = 6 $ but $ \text{Count}(\RED) = 2 \nless \text{Count}(\BLUE) = 2 $ . So, this is not a possible way to paint the sequence.

In the fourth test case, it can be proven that there is no possible way to paint the sequence satisfying sum and count constraints.

## 样例 #1

### 输入

```
4
3
1 2 3
5
2 8 6 3 1
4
3 5 4 2
5
1000000000 1000000000 1000000000 1000000000 1000000000```

### 输出

```
NO
YES
NO
NO```

# AI分析结果

### 题目内容
# 质量与数量

## 题目描述
给定一个由 \(n\) 个非负整数 \(a_1, a_2, \ldots, a_n\) 组成的序列。最初，序列中的所有元素均未涂色。你可以将每个数字涂成红色（用 \(\RED\) 表示）或蓝色（用 \(\BLUE\) 表示）（但不能同时涂两种颜色），也可以不涂色。

对于一种颜色 \(c\)，\(\text{Count}(c)\) 表示序列中涂有该颜色的元素数量，\(\text{Sum}(c)\) 表示序列中涂有该颜色的元素之和。

例如，如果给定的序列是 \([2, 8, 6, 3, 1]\)，并且涂成这样：\([\myblue{2}, 8, \myred{6}, \myblue{3}, 1]\)（其中 \(6\) 涂成红色，\(2\) 和 \(3\) 涂成蓝色，\(1\) 和 \(8\) 未涂色），那么 \(\text{Sum}(\RED)=6\)，\(\text{Sum}(\BLUE)=2 + 3 = 5\)，\(\text{Count}(\RED)=1\)，\(\text{Count}(\BLUE)=2\)。

判断是否有可能对序列进行涂色，使得 \(\text{Sum}(\RED) > \text{Sum}(\BLUE)\) 且 \(\text{Count}(\RED) < \text{Count}(\BLUE)\)。

## 说明/提示
在第一个测试用例中，不存在可能的涂色方式。例如，如果你将序列涂成这样：\([\myblue{1},\myblue{2},\myred{3}]\)（其中 \(3\) 涂成红色，\(1\) 和 \(2\) 涂成蓝色），那么 \(\text{Count}(\RED)=1 < \text{Count}(\BLUE)=2\)，但 \(\text{Sum}(\RED)=3 \ngtr \text{Sum}(\BLUE)=3\)。所以，这不是一种可能的涂色方式。

在第二个测试用例中，题目描述中给出了一种可能的涂色方式。我们可以看到 \(\text{Sum}(\RED)=6 > \text{Sum}(\BLUE)=5\) 且 \(\text{Count}(\RED)=1 < \text{Count}(\BLUE)=2\)。

在第三个测试用例中，不存在可能的涂色方式。例如，如果你将序列涂成这样：\([\myred{3},\myred{5},\myblue{4}, \myblue{2}]\)（其中 \(3\) 和 \(5\) 涂成红色，\(4\) 和 \(2\) 涂成蓝色），那么 \(\text{Sum}(\RED) = 8 > \text{Sum}(\BLUE) = 6\)，但 \(\text{Count}(\RED) = 2 \nless \text{Count}(\BLUE) = 2\)。所以，这不是一种可能的涂色方式。

在第四个测试用例中，可以证明不存在满足和与数量约束的涂色方式。

## 样例 #1
### 输入
```
4
3
1 2 3
5
2 8 6 3 1
4
3 5 4 2
5
1000000000 1000000000 1000000000 1000000000 1000000000
```
### 输出
```
NO
YES
NO
NO
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是基于贪心策略，即尽可能让较大的数涂成红色，较小的数涂成蓝色，同时满足红色数量小于蓝色数量。
 - **思路**：多数题解先对数组进行排序，再通过不同方式分配颜色并判断是否满足条件。有的从数组两端向中间靠拢，有的按特定规则选取固定数量的元素计算和。
 - **算法要点**：排序后，根据红色和蓝色数量关系及总和关系进行判断。如让红色数量比蓝色数量少1，分别计算红色和蓝色元素总和并比较。
 - **解决难点**：关键在于如何合理分配颜色，保证红色总和大于蓝色总和同时红色数量小于蓝色数量。部分题解考虑到可以不涂色这一情况，通过巧妙的下标处理来实现。

### 通用建议与扩展思路
对于这类贪心问题，关键在于找到合理的贪心策略。可以多思考如何从数据特征出发，确定元素分配方式。同类型题常围绕不同条件下的元素分配、选择等，类似套路是先分析数据特点，确定贪心方向，再通过模拟或计算验证。

### 洛谷题目推荐
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
 - [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
 - [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)

### 个人心得摘录与总结
 - Night_sea_64：强调了可以不涂色这个容易忽略的点，自己因没注意此点调试很久。总结出做此类题要仔细读题，关注所有可能情况。 

---
处理用时：38.84秒