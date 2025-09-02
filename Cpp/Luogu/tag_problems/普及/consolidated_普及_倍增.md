---
title: "[GCJ 2010 #1C] Load Testing"
layout: "post"
diff: 普及/提高-
pid: P13397
tag: ['数学', '2010', '倍增', 'Google Code Jam']
---
# [GCJ 2010 #1C] Load Testing
## 题目描述

Now that you have won Code Jam and been hired by Google as a software engineer, you have been assigned to work on their wildly popular programming contest website.

Google is expecting a lot of participants ($P$) in Code Jam next year, and they want to make sure that the site can support that many people at the same time. During Code Jam 2010 you learned that the site could support at least $L$ people at a time without any errors, but you also know that the site can't yet support $P$ people.

To determine how many more machines you'll need, you want to know within a factor of $C$ how many people the site can support. This means that there is an integer $a$ such that you know the site can support $a$ people, but you know the site can't support $a \times C$ people.

You can run a series of *load tests*, each of which will determine whether the site can support at least $X$ people for some integer value of $X$ that you choose. If you pick an optimal strategy, choosing what tests to run based on the results of previous tests, how many load tests do you need in the worst case?

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ lines follow, each of which contains space-separated integers $L$, $P$ and $C$ in that order.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the case number (starting from 1) and $y$ is the number of load tests you need to run in the worst case before knowing within a factor of $C$ how many people the site can support.
## 样例

### 样例输入 #1
```
4
50 700 2
19 57 3
1 1000 2
24 97 2
```
### 样例输出 #1
```
Case #1: 2
Case #2: 0
Case #3: 4
Case #4: 2
```
## 提示

**Sample Explanation**

In Case #2, we already know that the site can support between $19$ and $57$ people. Since those are a factor of $3$ apart, we don't need to do any testing.

In Case #4, we can test $48$; but if the site can support $48$ people, we need more testing, because $48 \times 2 < 97$. We could test $49$; but if the site can't support $49$ people, we need more testing, because $24 \times 2 < 49$. So we need two tests.

**Limits**

- $1 \leqslant T \leqslant 1000.$
- $2 \leqslant C \leqslant 10.$
- $L$, $P$ and $C$ are all integers.

**Small dataset (14 Pts, Test set 1 - Visible)**

- $1 \leqslant L < P \leqslant 10^3.$

**Large dataset (22 Pts, Test set 2 - Hidden)**

- $1 \leqslant L < P \leqslant 10^9.$




---

---
title: "忠诚"
layout: "post"
diff: 普及/提高-
pid: P1816
tag: ['线段树', '倍增', 'ST 表']
---
# 忠诚
## 题目描述

老管家是一个聪明能干的人。他为财主工作了整整  $10$ 年。财主为了让自已账目更加清楚，要求管家每天记  $k$ 次账。由于管家聪明能干，因而管家总是让财主十分满意。但是由于一些人的挑拨，财主还是对管家产生了怀疑。于是他决定用一种特别的方法来判断管家的忠诚，他把每次的账目按  $1, 2, 3 \ldots$ 编号，然后不定时的问管家问题，问题是这样的：在   $a$ 到  $b$ 号账中最少的一笔是多少？为了让管家没时间作假，他总是一次问多个问题。
## 输入格式

输入中第一行有两个数  $m, n$，表示有  $m$ 笔账  $n$ 表示有  $n$ 个问题。

第二行为  $m$ 个数，分别是账目的钱数。

后面  $n$ 行分别是  $n$ 个问题，每行有   $2$ 个数字说明开始结束的账目编号。
## 输出格式

在一行中输出每个问题的答案，以一个空格分割。
## 样例

### 样例输入 #1
```
10 3
1 2 3 4 5 6 7 8 9 10
2 7
3 9
1 10
```
### 样例输出 #1
```
2 3 1
```
## 提示

对于 $100\%$ 的数据，$m \leq 10^5$，$n \leq 10^5$。


---

---
title: "[BJWC2008] 秦腾与教学评估"
layout: "post"
diff: 普及/提高-
pid: P4403
tag: ['2008', '倍增', '二分', '各省省选']
---
# [BJWC2008] 秦腾与教学评估
## 题目描述

在秦腾进入北京大学学习的第一个学期，就不幸遇到了前所未有的教学评估。

在教学评估期间，同学们被要求八点起床，十一点回宿舍睡觉，不 准旷课，上课不准迟到，上课不准睡觉……甚至连著名的北大三角地也在教学评估期间被以影响校容的理由被拆除。这些“变态”规定令习惯了自由自在随性生活学习的北大同学叫苦不迭。

这一天又到了星期五，一大早就是秦腾最不喜欢的高等代数课。可是因为是教学评估时期，不能迟到，于是他在八点五分的 时候挣扎着爬出了宿舍，希望能赶快混进在八点钟已经上课了的教室。

可是，刚一出宿舍楼门他就傻眼了: 从宿舍到教学楼的路上已经站满了教学评估团的成员。他们的目的就是抓住像他这样迟到的学生，扣除学校的分数。

秦腾当然不能让评估团得逞。他经过观察发现，整个评估团分成了N个小组，每个小组的成员都分布在从宿舍楼到教学楼的路上的某一段，并且同一小组的成员间的距离是相等的。于是，我们可以用三个整数S,
 E, D来描述评估团的小组: 既该小组的成员在从宿舍到教学楼的路上的:S, S + D, S + 2D, …, S + KD (K ∈ Z, S + KD ≤ E, S + (K + 1)D > E)位置。

观 察到了教学评估团的这一特点，又经过了认真的思考，秦腾想出了对策: 如果在路上的某一位置有奇数个教学评估团成员，他就可以运用调虎离山，声东击西，隔山打牛，暗度陈仓……等方法，以这一地点为突破口到达教学楼。

但是由于 教学评估团的成员的十分狡猾，成员位置安排的设计极其精妙，导致在整条路上几乎没有这样的位置出现。即使由于安排不慎重出现了这样的位置，最多也仅有一个。

现在秦腾观察出了所有小组的安排，但是由于整个教学评估团的人数太多，他实在看不出这样的位置是否存在。

现在，你的任务是写一个程序，帮助他做出判断。
## 输入格式

输入文件的第一行为一个整数T。

接下来输入T组相互独立的测试数据。

每组测试数据的第一行包含一个整数，代表N接下来的N行，每行三个整数Si, Ei, Di, 代表第i个小组对应的三个参数。
## 输出格式

对于每个测试数据，如果题目中所求的位置不存在，既任意位置都有偶数个教学评估团的成员存在，在输出文件的中打印一行:`Poor QIN Teng:(` (不包含引号)否则打印两个整数Posi, Count，代表在唯一的位置Posi，有Count个教学评估团的成员。

根据题意，Count应为奇数。
## 样例

### 样例输入 #1
```
3 
2 
1 10 1 
2 10 1 
2 
1 10 1 
1 10 1 
4 
1 10 1 
4 4 1 
1 5 1 
6 10 1 
```
### 样例输出 #1
```
1 1 
Poor QIN Teng:( 
4 3 
```
## 提示

教学评估团的总人数不大于10^8  

Si ≤ Ei  
1 ≤ T ≤ 5  
N ≤ 200000  
0 ≤ Si, Ei, Di ≤ 2^31 – 1  

输入文件的大小不大于2048KB 


---

