---
title: "Porcelain"
layout: "post"
diff: 普及+/提高
pid: CF148E
tag: ['枚举', '背包 DP', '前缀和']
---

# Porcelain

## 题目描述

During her tantrums the princess usually smashes some collectable porcelain. Every furious shriek is accompanied with one item smashed.

The collection of porcelain is arranged neatly on $ n $ shelves. Within each shelf the items are placed in one row, so that one can access only the outermost items — the leftmost or the rightmost item, not the ones in the middle of the shelf. Once an item is taken, the next item on that side of the shelf can be accessed (see example). Once an item is taken, it can't be returned to the shelves.

You are given the values of all items. Your task is to find the maximal damage the princess' tantrum of $ m $ shrieks can inflict on the collection of porcelain.

## 输入格式

The first line of input data contains two integers $ n $ ( $ 1<=n<=100 $ ) and $ m $ ( $ 1<=m<=10000 $ ). The next $ n $ lines contain the values of the items on the shelves: the first number gives the number of items on this shelf (an integer between $ 1 $ and $ 100 $ , inclusive), followed by the values of the items (integers between $ 1 $ and $ 100 $ , inclusive), in the order in which they appear on the shelf (the first number corresponds to the leftmost item, the last one — to the rightmost one). The total number of items is guaranteed to be at least $ m $ .

## 输出格式

Output the maximal total value of a tantrum of $ m $ shrieks.

## 说明/提示

In the first case there are two shelves, each with three items. To maximize the total value of the items chosen, one can take two items from the left side of the first shelf and one item from the right side of the second shelf.

In the second case there is only one shelf, so all three items are taken from it — two from the left side and one from the right side.

## 样例 #1

### 输入

```
2 3
3 3 7 2
3 4 1 5

```

### 输出

```
15

```

## 样例 #2

### 输入

```
1 3
4 4 3 1 2

```

### 输出

```
9

```



---

---
title: "Yet Another Minimization Problem"
layout: "post"
diff: 普及+/提高
pid: CF1637D
tag: ['动态规划 DP', '背包 DP']
---

# Yet Another Minimization Problem

## 题目描述

You are given two arrays $ a $ and $ b $ , both of length $ n $ .

You can perform the following operation any number of times (possibly zero): select an index $ i $ ( $ 1 \leq i \leq n $ ) and swap $ a_i $ and $ b_i $ .

Let's define the cost of the array $ a $ as $ \sum_{i=1}^{n} \sum_{j=i + 1}^{n} (a_i + a_j)^2 $ . Similarly, the cost of the array $ b $ is $ \sum_{i=1}^{n} \sum_{j=i + 1}^{n} (b_i + b_j)^2 $ .

Your task is to minimize the total cost of two arrays.

## 输入格式

Each test case consists of several test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 40 $ ) — the number of test cases. The following is a description of the input data sets.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 100 $ ) — the length of both arrays.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 100 $ ) — elements of the first array.

The third line of each test case contains $ n $ integers $ b_1, b_2, \ldots, b_n $ ( $ 1 \leq b_i \leq 100 $ ) — elements of the second array.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 100 $ .

## 输出格式

For each test case, print the minimum possible total cost.

## 说明/提示

In the second test case, in one of the optimal answers after all operations $ a = [2, 6, 4, 6] $ , $ b = [3, 7, 6, 1] $ .

The cost of the array $ a $ equals to $ (2 + 6)^2 + (2 + 4)^2 + (2 + 6)^2 + (6 + 4)^2 + (6 + 6)^2 + (4 + 6)^2 = 508 $ .

The cost of the array $ b $ equals to $ (3 + 7)^2 + (3 + 6)^2 + (3 + 1)^2 + (7 + 6)^2 + (7 + 1)^2 + (6 + 1)^2 = 479 $ .

The total cost of two arrays equals to $ 508 + 479 = 987 $ .

## 样例 #1

### 输入

```
3
1
3
6
4
3 6 6 6
2 7 4 1
4
6 7 2 4
2 5 3 5
```

### 输出

```
0
987
914
```



---

---
title: "Rescheduling the Exam"
layout: "post"
diff: 普及+/提高
pid: CF1650E
tag: ['枚举', '背包 DP']
---

# Rescheduling the Exam

## 题目描述

Now Dmitry has a session, and he has to pass $ n $ exams. The session starts on day $ 1 $ and lasts $ d $ days. The $ i $ th exam will take place on the day of $ a_i $ ( $ 1 \le a_i \le d $ ), all $ a_i $ — are different.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/80b5043cb96246fb12fe0316b7ae224994f04da5.png)Sample, where $ n=3 $ , $ d=12 $ , $ a=[3,5,9] $ . Orange — exam days. Before the first exam Dmitry will rest $ 2 $ days, before the second he will rest $ 1 $ day and before the third he will rest $ 3 $ days.For the session schedule, Dmitry considers a special value $ \mu $ — the smallest of the rest times before the exam for all exams. For example, for the image above, $ \mu=1 $ . In other words, for the schedule, he counts exactly $ n $ numbers — how many days he rests between the exam $ i-1 $ and $ i $ (for $ i=0 $ between the start of the session and the exam $ i $ ). Then it finds $ \mu $ — the minimum among these $ n $ numbers.

Dmitry believes that he can improve the schedule of the session. He may ask to change the date of one exam (change one arbitrary value of $ a_i $ ). Help him change the date so that all $ a_i $ remain different, and the value of $ \mu $ is as large as possible.

For example, for the schedule above, it is most advantageous for Dmitry to move the second exam to the very end of the session. The new schedule will take the form:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/ea72ffbaa1a469cfa577e07f4a541e64f273ed21.png)Now the rest periods before exams are equal to $ [2,2,5] $ . So, $ \mu=2 $ .Dmitry can leave the proposed schedule unchanged (if there is no way to move one exam so that it will lead to an improvement in the situation).

## 输入格式

The first line of input data contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of input test cases. The descriptions of test cases follow.

An empty line is written in the test before each case.

The first line of each test case contains two integers $ n $ and $ d $ ( $ 2 \le n \le 2 \cdot 10^5, 1 \le d \le 10^9 $ ) — the number of exams and the length of the session, respectively.

The second line of each test case contains $ n $ integers $ a_i $ ( $ 1 \le a_i \le d, a_i < a_{i+1} $ ), where the $ i $ -th number means the date of the $ i $ -th exam.

It is guaranteed that the sum of $ n $ for all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the maximum possible value of $ \mu $ if Dmitry can move any one exam to an arbitrary day. All values of $ a_i $ should remain distinct.

## 说明/提示

The first sample is parsed in statement.

One of the optimal schedule changes for the second sample:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/a8127e465b7998df08b0c9dd6be925e73333852b.png)Initial schedule.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/c109ce56a74359821f30b8b4de03ca418349d132.png)New schedule.

In the third sample, we need to move the exam from day $ 1 $ to any day from $ 4 $ to $ 100 $ .

In the fourth sample, any change in the schedule will only reduce $ \mu $ , so the schedule should be left as it is.

In the fifth sample, we need to move the exam from day $ 1 $ to any day from $ 100000000 $ to $ 300000000 $ .

One of the optimal schedule changes for the sixth sample:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/c42982828b6b783bfe2b7287e37a4f2be5dfff0a.png)Initial schedule.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/40bee0dd841380562f7e8f2d4a71c924f5f6fe41.png)New schedule.

In the seventh sample, every day is exam day, and it is impossible to rearrange the schedule.

## 样例 #1

### 输入

```
9

3 12
3 5 9

2 5
1 5

2 100
1 2

5 15
3 6 9 12 15

3 1000000000
1 400000000 500000000

2 10
3 4

2 2
1 2

4 15
6 11 12 13

2 20
17 20
```

### 输出

```
2
1
1
2
99999999
3
0
1
9
```



---

---
title: "Vitaly and Advanced Useless Algorithms"
layout: "post"
diff: 普及+/提高
pid: CF1650F
tag: ['动态规划 DP', '背包 DP']
---

# Vitaly and Advanced Useless Algorithms

## 题目描述

Vitaly enrolled in the course Advanced Useless Algorithms. The course consists of $ n $ tasks. Vitaly calculated that he has $ a_i $ hours to do the task $ i $ from the day he enrolled in the course. That is, the deadline before the $ i $ -th task is $ a_i $ hours. The array $ a $ is sorted in ascending order, in other words, the job numbers correspond to the order in which the assignments are turned in.

Vitaly does everything conscientiously, so he wants to complete each task by $ 100 $ percent, or more. Initially, his completion rate for each task is $ 0 $ percent.

Vitaly has $ m $ training options, each option can be used not more than once. The $ i $ th option is characterized by three integers: $ e_i, t_i $ and $ p_i $ . If Vitaly uses the $ i $ th option, then after $ t_i $ hours (from the current moment) he will increase the progress of the task $ e_i $ by $ p_i $ percent.

For example, let Vitaly have $ 3 $ of tasks to complete. Let the array $ a $ have the form: $ a = [5, 7, 8] $ . Suppose Vitaly has $ 5 $ of options: $ [e_1=1, t_1=1, p_1=30] $ , $ [e_2=2, t_2=3, p_2=50] $ , $ [e_3=2, t_3=3, p_3=100] $ , $ [e_4=1, t_4=1, p_4=80] $ , $ [e_5=3, t_5=3, p_5=100] $ .

Then, if Vitaly prepares in the following way, he will be able to complete everything in time:

- Vitaly chooses the $ 4 $ -th option. Then in $ 1 $ hour, he will complete the $ 1 $ -st task at $ 80 $ percent. He still has $ 4 $ hours left before the deadline for the $ 1 $ -st task.
- Vitaly chooses the $ 3 $ -rd option. Then in $ 3 $ hours, he will complete the $ 2 $ -nd task in its entirety. He has another $ 1 $ hour left before the deadline for the $ 1 $ -st task and $ 4 $ hours left before the deadline for the $ 3 $ -rd task.
- Vitaly chooses the $ 1 $ -st option. Then after $ 1 $ hour, he will complete the $ 1 $ -st task for $ 110 $ percent, which means that he will complete the $ 1 $ -st task just in time for the deadline.
- Vitaly chooses the $ 5 $ -th option. He will complete the $ 3 $ -rd task for $ 2 $ hours, and after another $ 1 $ hour, Vitaly will complete the $ 3 $ -rd task in its entirety.

Thus, Vitaly has managed to complete the course completely and on time, using the $ 4 $ options.

Help Vitaly — print the options for Vitaly to complete the tasks in the correct order. Please note: each option can be used not more than once. If there are several possible answers, it is allowed to output any of them.

## 输入格式

The first line of input data contains an integer $ T $ ( $ 1 \le T \le 10^4 $ ) —the number of input test cases in the test.

The descriptions of the input test case follow.

The first line of each test case description contains two integers $ n $ and $ m $ ( $ 1 \le n,m \le 10^5 $ ) —the number of jobs and the number of training options, respectively.

The next line contains $ n $ numbers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the time before the deadline of job $ i $ . The array values — are non-decreasing, that is $ a_1 \le a_2 \le \dots \le a_n $ .

The following $ m $ lines contain triples of numbers $ e_i, t_i, p_i $ ( $ 1 \le e_i \le n $ , $ 1 \le t_i \le 10^9 $ , $ 1 \le p_i \le 100 $ ) — if Vitaly chooses this option, then after $ t_i $ hours he will increase the progress of the task $ e_i $ by $ p_i $ percent. The options are numbered from $ 1 $ to $ m $ in order in the input data.

It is guaranteed that the sum of $ n+m $ on all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print on the first line the number $ k $ , meaning that for $ k $ of options, Vitaly will be able to complete each task by $ 100 $ percent or more on time. The options should not be repeated. Or print -1 if Vitaly is unable to complete all tasks in time.

If there is an answer, on the next line print $ k $ of different integers from $ 1 $ to $ m $ — the numbers of the options in the order you want. If there is more than one answer, it is allowed to print any of them.

## 样例 #1

### 输入

```
5
3 5
5 7 8
1 1 30
2 3 50
2 3 100
1 1 80
3 3 100
1 5
51
1 36 91
1 8 40
1 42 83
1 3 45
1 13 40
2 9
9 20
2 8 64
2 7 64
1 20 56
2 8 76
2 20 48
1 2 89
1 3 38
2 18 66
1 7 51
3 2
7 18 33
1 5 80
3 4 37
2 5
569452312 703565975
1 928391659 66
1 915310 82
2 87017081 92
1 415310 54
2 567745964 82
```

### 输出

```
4
1 4 3 5 
3
2 4 5 
4
6 7 1 2 
-1
4
2 4 3 5
```

## 样例 #2

### 输入

```
3
3 9
20 31 40
1 9 64
3 17 100
3 9 59
3 18 57
3 20 49
2 20 82
2 14 95
1 8 75
2 16 67
2 6
20 36
2 2 66
2 20 93
1 3 46
1 10 64
2 8 49
2 18 40
1 1
1000000000
1 1000000000 100
```

### 输出

```
-1
4
3 4 1 5 
1
1
```



---

---
title: "World is Mine"
layout: "post"
diff: 普及+/提高
pid: CF1987D
tag: ['动态规划 DP', '背包 DP']
---

# World is Mine

## 题目描述

Alice and Bob are playing a game. Initially, there are $ n $ cakes, with the $ i $ -th cake having a tastiness value of $ a_i $ .

Alice and Bob take turns eating them, with Alice starting first:

- In her turn, Alice chooses and eats any remaining cake whose tastiness is strictly greater than the maximum tastiness of any of the cakes she's eaten before that. Note that on the first turn, she can choose any cake.
- In his turn, Bob chooses any remaining cake and eats it.

The game ends when the current player can't eat a suitable cake. Let $ x $ be the number of cakes that Alice ate. Then, Alice wants to maximize $ x $ , while Bob wants to minimize $ x $ .

Find out how many cakes Alice will eat if both players play optimally.

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \le t \le 500 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 5000 $ ) — the number of cakes.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) — the tastiness values of the cakes.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5000 $ .

## 输出格式

For each test case, output a single integer — the number of cakes Alice will eat if both players play optimally.

## 说明/提示

In the first test case, one possible sequence of turns is:

1. Alice eats a cake with a tastiness value of $ 1 $ . The remaining cakes are $ [4, 2, 3] $ .
2. Bob eats a cake with a tastiness value of $ 2 $ . The remaining cakes are $ [4, 3] $ .
3. Alice eats a cake with a tastiness of $ 3 $ . The remaining cakes are $ [4] $ .
4. Bob eats a cake with a tastiness value of $ 4 $ . The remaining cakes are $ [] $ .
5. Since there are no more cakes left, the game ends.

In the second test case, one possible sequence of turns is:

1. Alice eats a cake with a tastiness value of $ 1 $ . The remaining cakes are $ [1, 1] $ .
2. Bob eats a cake with a tastiness value of $ 1 $ . The remaining cakes are $ [1] $ .
3. Since Alice has already eaten a cake with a tastiness value of $ 1 $ , she cannot make a turn, so the game ends.

## 样例 #1

### 输入

```
9
4
1 4 2 3
3
1 1 1
5
1 4 2 3 4
4
3 4 1 4
1
1
8
4 3 2 5 6 8 3 4
7
6 1 1 3 5 3 1
11
6 11 6 8 7 5 3 11 2 3 5
17
2 6 5 3 9 1 6 2 5 6 3 2 3 9 6 1 6
```

### 输出

```
2
1
3
2
1
3
2
4
4
```



---

---
title: "Equalization"
layout: "post"
diff: 普及+/提高
pid: CF2075D
tag: ['动态规划 DP', '背包 DP']
---

# Equalization

## 题目描述

给定两个非负整数 $x$ 和 $y$。

你可以执行以下操作任意次数（包括零次）：选择一个正整数 $k$，并将 $x$ 或 $y$ 除以 $2^k$（向下取整）。此操作的代价为 $2^k$。但存在额外约束：每个 $k$ 值最多只能选择一次。

你的任务是计算使 $x$ 和 $y$ 相等所需的最小可能代价。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^5$）——测试用例的数量。

每个测试用例的唯一一行包含两个整数 $x$ 和 $y$（$0 \le x, y \le 10^{17}$）。

## 输出格式

对于每个测试用例，输出一个整数——使 $x$ 和 $y$ 相等所需的最小可能代价。

## 说明/提示

第一个示例中，可以按如下步骤操作：选择 $k=1$ 并将 $y$ 除以 $2$。之后，$x$ 和 $y$ 均等于 $0$。

第二个示例中，可以按如下步骤操作：选择 $k=2$ 并将 $x$ 除以 $4$；选择 $k=1$ 并将 $y$ 除以 $2$。之后，$x$ 和 $y$ 均等于 $1$。

第三个示例中，两数已经相等，无需操作。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
0 1
6 2
3 3
13 37
4238659325782394 12983091057341925
```

### 输出

```
2
6
0
26
32764
```



---

---
title: "Even String"
layout: "post"
diff: 普及+/提高
pid: CF2086D
tag: ['背包 DP', '组合数学']
---

# Even String

## 题目描述

你需要构造一个由小写拉丁字母组成的字符串 $s$，满足以下条件：
- 对于任意两个满足 $s_{i} = s_{j}$ 的下标 $i$ 和 $j$，这两个下标之差的绝对值为偶数，即 $|i - j| \bmod 2 = 0$。

构造任意字符串太简单了，因此你会被给定一个包含 $26$ 个数字的数组 $c$ —— 表示字符串 $s$ 中每个字母必须出现的次数。也就是说，对于每个 $i \in [1, 26]$，拉丁字母表中的第 $i$ 个字母必须恰好出现 $c_i$ 次。

你的任务是计算满足所有这些条件的不同字符串 $s$ 的数量。由于答案可能非常大，请输出其对 $998\,244\,353$ 取模后的结果。

## 输入格式

每个测试包含多个测试用例。第一行包含一个整数 $t$（$1 \le t \le 10^{4}$）—— 测试用例的数量。接下来是测试用例的描述。

每个测试用例包含 $26$ 个整数 $c_{i}$（$0 \le c_{i} \le 5 \cdot 10^{5}$）—— 数组 $c$ 的元素。

输入数据的额外限制：
- 每个测试用例的 $c_{i}$ 之和为正；
- 所有测试用例的 $c_{i}$ 之和不超过 $5 \cdot 10^{5}$。

## 输出格式

对于每个测试用例，输出一个整数 —— 满足条件的字符串 $s$ 的数量，对 $998\,244\,353$ 取模后的结果。


## 说明/提示

- 在第一个测试用例中，有 $4$ 个满足条件的字符串："abak"、"akab"、"baka" 和 "kaba"。


翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
2 1 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
3 1 1 0 0 0 0 0 0 0 0 0 0 0 0 1 0 1 0 0 0 0 0 0 1 0
0 0 0 0 0 0 0 0 0 0 0 0 1 0 3 0 0 0 0 0 0 0 0 0 0 0
1 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 233527 233827
```

### 输出

```
4
960
0
1
789493841
```



---

---
title: "Shaass and Bookshelf"
layout: "post"
diff: 普及+/提高
pid: CF294B
tag: ['背包 DP']
---

# Shaass and Bookshelf

## 题目描述

Shaass拥有n本书。他想为他的所有书制作一个书架，并想让书架的长宽尽量小。第i本书的厚度是t[i]，且这本书的纸张宽度是w[i]。书的厚度是1或2，所有书都有同样的高度（即书架的高是均匀的）。

Shaass以以下的方式摆放这些书籍。

1.他选择了一些书并竖直摆放它们。

2.他将剩余的书籍水平纺织于竖直的书上面。
水平放置的书的宽度和不能多于竖直放置的书的总厚度。图中描绘了书籍的样本排列。

帮助Shaass找到可以达到的书架长度最小值。

## 输入格式

输入的第一行包含一个int型的整数n（1<=n<=100）。
下面的n行分别为v[i]和w[i]，对应了书的长度和宽度（即书籍竖直放置与水平放置所占的空间）。
（1<=t[i]<=2,1<=w[i]<=100)

## 输出格式

一个整数，为可以达到的最小的长度。



------------

###### 翻译提供：masiyuan

## 样例 #1

### 输入

```
5
1 12
1 3
2 15
2 5
2 1

```

### 输出

```
5

```

## 样例 #2

### 输入

```
3
1 10
2 1
2 4

```

### 输出

```
3

```



---

---
title: "Lorry"
layout: "post"
diff: 普及+/提高
pid: CF3B
tag: ['贪心', '背包 DP', '队列']
---

# Lorry

## 题目描述

给定整数 $n,v$。  

有一辆载重量为 $v$ 的货车，准备运送两种物品。物品 A 的重量为 $1$，物体 B 的重量为 $2$，每个物品都有一个价值 $p_i$。求货车可以运送的物品的最大价值。

## 输入格式

第一个行包含两个整数 $n$ 和 $v$，分别表示有 $n$ 个物品，货车的载重量为 $v$。（$1\le n\le10^5$，$1\le v\le10^9$）

接下来 $n$ 行，每行两个整数，分别表示物品的重量 $t_i$ 和价值 $p_i$。（$t_i=1$ 或 $2$，$1\le p_i\le10^4$）

## 输出格式

第一行，一个整数，表示价值之和的最大值。

第二行，构成最大价值的物品的编号（如果答案不唯一，请输出其中任何一个）。

## 样例 #1

### 输入

```
3 2
1 2
2 7
1 3

```

### 输出

```
7
2

```



---

---
title: "Red-Green Towers"
layout: "post"
diff: 普及+/提高
pid: CF478D
tag: ['动态规划 DP', '背包 DP']
---

# Red-Green Towers

## 题目描述

你有 $r$ 块红色的积木和 $g$ 块绿色的积木，它们用于建造红绿塔。红绿塔按照下面的规则来建造：

- 红绿塔有若干层；
- 如果红绿塔有 $n$ 层，那么塔的第一层应该有 $n$ 块积木，第二层有 $n-1$ 块，第三层有 $n-2$ 块，以此类推，最后一层只有一块。换言之，每一层应该比前面一层少一块；
- 红绿塔的每一层必须使用相同颜色的积木。

令 $h$ 表示用 $r$ 个红积木和 $g$ 个绿积木所能搭建的满足上述规则的塔的最大层数。现在你的任务是确定可以建造出多少不同的有 $h$ 层的红绿塔。

如果两个红绿塔相同的一层使用的是不同的颜色，它们就被认为不同的。

你需要写一个程序来求出有多少种高度为 $h$ 的不同的红绿塔。由于答案很大，你只需要输出答案模 $10^9+7$（也就是$1000000007$）后的值。

## 输入格式

输入仅有一行，用空格隔开的两个数 $r$ 和 $g$，表示可用的红色、绿色积木的数量

## 输出格式

输出仅一行，高度为 $h$ 的不同红绿塔的个数模 $10^9+7$ 的值

**数据规模**

$0\le r,g\le 2\times 10^5$, $r+g\ge 1$

## 样例 #1

### 输入

```
4 6

```

### 输出

```
2

```

## 样例 #2

### 输入

```
9 7

```

### 输出

```
6

```

## 样例 #3

### 输入

```
1 1

```

### 输出

```
2

```



---

---
title: "Fox And Jumping"
layout: "post"
diff: 普及+/提高
pid: CF510D
tag: ['动态规划 DP', '枚举', '背包 DP', '最大公约数 gcd']
---

# Fox And Jumping

## 题目描述

Fox Ciel is playing a game. In this game there is an infinite long tape with cells indexed by integers (positive, negative and zero). At the beginning she is standing at the cell 0.

There are also $ n $ cards, each card has 2 attributes: length $ l_{i} $ and cost $ c_{i} $ . If she pays $ c_{i} $ dollars then she can apply $ i $ -th card. After applying $ i $ -th card she becomes able to make jumps of length $ l_{i} $ , i. e. from cell $ x $ to cell $ (x-l_{i}) $ or cell $ (x+l_{i}) $ .

She wants to be able to jump to any cell on the tape (possibly, visiting some intermediate cells). For achieving this goal, she wants to buy some cards, paying as little money as possible.

If this is possible, calculate the minimal cost.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=300 $ ), number of cards.

The second line contains $ n $ numbers $ l_{i} $ ( $ 1<=l_{i}<=10^{9} $ ), the jump lengths of cards.

The third line contains $ n $ numbers $ c_{i} $ ( $ 1<=c_{i}<=10^{5} $ ), the costs of cards.

## 输出格式

If it is impossible to buy some cards and become able to jump to any cell, output -1. Otherwise output the minimal cost of buying such set of cards.

## 说明/提示

In first sample test, buying one card is not enough: for example, if you buy a card with length 100, you can't jump to any cell whose index is not a multiple of 100. The best way is to buy first and second card, that will make you be able to jump to any cell.

In the second sample test, even if you buy all cards, you can't jump to any cell whose index is not a multiple of 10, so you should output -1.

## 样例 #1

### 输入

```
3
100 99 9900
1 1 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5
10 20 30 40 50
1 1 1 1 1

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
7
15015 10010 6006 4290 2730 2310 1
1 1 1 1 1 1 10

```

### 输出

```
6

```

## 样例 #4

### 输入

```
8
4264 4921 6321 6984 2316 8432 6120 1026
4264 4921 6321 6984 2316 8432 6120 1026

```

### 输出

```
7237

```



---

---
title: "Round Subset"
layout: "post"
diff: 普及+/提高
pid: CF837D
tag: ['动态规划 DP', '背包 DP']
---

# Round Subset

## 题目描述

我们把一个数的 roundness 值定义为它末尾 $0$ 的个数。

给你一个长度为 $n$ 的数列，要求你从中选出 $k$ 个数，使得这些选出的数的积的 roundness 值最大。

## 输入格式

第一行包括两个正整数 $n$ 和 $k$（$1 \leq n \leq 200$，$1 \leq k \leq n$）。

第二行包括 $n$ 个空白分隔的数 $a_1,a_2,\ldots,a_n$（$1 \leq a_i \leq 10^{18}$）。

## 输出格式

输出一个整数，是选择 $k$ 个数并作积的最大 roundness 值。

## 样例解释

在第一个例子中，有三种选法。$[50,4]$ 的积是 $200$，roundness 值是 $2$；$[4,20]$ 的积是 $80$，roundness 值是 $1$；$[50,20]$ 的积是 $1000$，roundness 值是 $3$。

第二个例子中选法 $[15,16,25]$ 的积是 $6000$，roundness 值是 $3$。

第三个例子中所有的选法的积的 roundness 值都是 $0$。

translated by @poorpool

## 样例 #1

### 输入

```
3 2
50 4 20

```

### 输出

```
3

```

## 样例 #2

### 输入

```
5 3
15 16 3 25 9

```

### 输出

```
3

```

## 样例 #3

### 输入

```
3 3
9 77 13

```

### 输出

```
0

```



---

---
title: "Fire"
layout: "post"
diff: 普及+/提高
pid: CF864E
tag: ['贪心', '排序', '背包 DP']
---

# Fire

## 题目描述

某人的房子着火了，他想从大火中带走价值总和尽量多的物品，每次他只能带走一个，分别给出挽救某物品需要的时间 $t$，该物品开始燃烧的时间 $d$（从 $d$ 时间开始就不能再挽救该物品了），该物品的价值 $p$。

## 输入格式

第一行为物品总数 $n$（$1\leqslant n\leqslant100$）；

接下来 $n$ 行，每行有三个整数 $t_i$（$1\leqslant t_i\leqslant20$），$di$（$1\leqslant d_i\leqslant2000$），$pi$（$1\leqslant p_i\leqslant20$）。

## 输出格式

第一行为能带走的最大的价值总和；

第二行为能带走的物品的数量；

第三行为能带走的物品的编号（按带走顺序排序）。

Translated by 凌幽

## 样例 #1

### 输入

```
3
3 7 4
2 6 5
3 7 6

```

### 输出

```
11
2
2 3 

```

## 样例 #2

### 输入

```
2
5 6 1
3 3 5

```

### 输出

```
1
1
1 

```



---

