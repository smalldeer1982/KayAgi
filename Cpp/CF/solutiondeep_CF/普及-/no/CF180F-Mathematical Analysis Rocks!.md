# 题目信息

# Mathematical Analysis Rocks!

## 题目描述

Students of group 199 have written their lectures dismally. Now an exam on Mathematical Analysis is approaching and something has to be done asap (that is, quickly). Let's number the students of the group from 1 to $ n $ . Each student $ i $ ( $ 1<=i<=n $ ) has a best friend $ p[i] $ ( $ 1<=p[i]<=n $ ). In fact, each student is a best friend of exactly one student. In other words, all $ p[i] $ are different. It is possible that the group also has some really "special individuals" for who $ i=p[i] $ .

Each student wrote exactly one notebook of lecture notes. We know that the students agreed to act by the following algorithm:

- on the first day of revising each student studies his own Mathematical Analysis notes,
- in the morning of each following day each student gives the notebook to his best friend and takes a notebook from the student who calls him the best friend.

Thus, on the second day the student $ p[i] $ ( $ 1<=i<=n $ ) studies the $ i $ -th student's notes, on the third day the notes go to student $ p[p[i]] $ and so on. Due to some characteristics of the boys' friendship (see paragraph 1), each day each student has exactly one notebook to study.

You are given two sequences that describe the situation on the third and fourth days of revising:

- $ a_{1},a_{2},...,a_{n} $ , where $ a_{i} $ means the student who gets the $ i $ -th student's notebook on the third day of revising;
- $ b_{1},b_{2},...,b_{n} $ , where $ b_{i} $ means the student who gets the $ i $ -th student's notebook on the fourth day of revising.

You do not know array $ p $ , that is you do not know who is the best friend to who. Write a program that finds $ p $ by the given sequences $ a $ and $ b $ .

## 样例 #1

### 输入

```
4
2 1 4 3
3 4 2 1
```

### 输出

```
4 3 1 2 ```

## 样例 #2

### 输入

```
5
5 2 3 1 4
1 3 2 4 5
```

### 输出

```
4 3 2 5 1 ```

## 样例 #3

### 输入

```
2
1 2
2 1
```

### 输出

```
2 1 ```

# AI分析结果

### 题目内容
# Mathematical Analysis Rocks!
## 题目描述
199 组的学生们把他们的课程笔记写得很糟糕。现在数学分析考试即将来临，必须尽快采取措施（也就是要快）。让我们将该组的学生从 1 编号到 $n$。每个学生 $i$（$1\leq i\leq n$）都有一个最好的朋友 $p[i]$（$1\leq p[i]\leq n$）。实际上，每个学生都恰好是另一个学生的最好朋友。换句话说，所有的 $p[i]$ 都是不同的。该组中也可能有一些真正的 “特殊个体”，对于他们有 $i = p[i]$。

每个学生都只写了一本课程笔记。我们知道学生们同意按照以下算法行事：
- 在复习的第一天，每个学生都学习自己的数学分析笔记。
- 在接下来每天的早上，每个学生都会把笔记本交给他最好的朋友，并从称他为最好朋友的学生那里拿一本笔记本。

因此，在第二天，学生 $p[i]$（$1\leq i\leq n$）会学习第 $i$ 个学生的笔记，在第三天，笔记会到学生 $p[p[i]]$ 手中，依此类推。由于男孩们友谊的某些特点（见第一段），每天每个学生都恰好有一本笔记本可学习。

现在给你描述复习第三天和第四天情况的两个序列：
- $a_{1},a_{2},\cdots,a_{n}$，其中 $a_{i}$ 表示在复习第三天拿到第 $i$ 个学生笔记本的学生。
- $b_{1},b_{2},\cdots,b_{n}$，其中 $b_{i}$ 表示在复习第四天拿到第 $i$ 个学生笔记本的学生。

你不知道数组 $p$，也就是说你不知道谁是谁的最好朋友。编写一个程序，根据给定的序列 $a$ 和 $b$ 找到 $p$。
## 样例 #1
### 输入
```
4
2 1 4 3
3 4 2 1
```
### 输出
```
4 3 1 2 
```
## 样例 #2
### 输入
```
5
5 2 3 1 4
1 3 2 4 5
```
### 输出
```
4 3 2 5 1 
```
## 样例 #3
### 输入
```
2
1 2
2 1
```
### 输出
```
2 1 
```
### 算法分类
数学
### 题解综合分析与结论
所有题解的核心思路都是基于第三天和第四天笔记本持有者的关系来确定朋友关系。因为每天学生只会将笔记本交给自己最好的朋友，所以第三天持有第 $i$ 本笔记本的学生 $a_i$ 与第四天持有该笔记本的学生 $b_i$ 之间存在 $p_{a_i}=b_i$ 的关系，通过这个关系来构建数组 $p$ 从而得到每个学生的最好朋友。各题解在思路表述和代码实现风格上略有差异，但本质算法相同，整体质量不高，均未达到4星。
### 通用建议与扩展思路
对于此类题目，关键在于理解题目所描述的逻辑关系，并通过数学推导找到解题的核心等式。在代码实现上，要注意数组的正确使用和边界条件处理。类似的题目通常围绕人物关系、物品流转等场景，通过给定的不同状态信息反推隐藏的映射关系。可以通过多练习此类映射关系推导的题目，加深对这类问题的理解和解决能力。
### 推荐题目
1. [P1036 [NOIP2002 普及组] 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举组合并结合数学判断来解决问题，与本题类似在于需要找到数据间的特定关系进行处理。
2. [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：利用数学知识和枚举来找出满足条件的连续自然数序列，同样涉及到对数据关系的分析和推导。
3. [P1464 Function](https://www.luogu.com.cn/problem/P1464)：通过对函数规则的理解和数学分析来解决问题，和本题一样需要从给定规则中提炼出关键逻辑。 

---
处理用时：27.76秒