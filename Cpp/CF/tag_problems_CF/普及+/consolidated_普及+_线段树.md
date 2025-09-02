---
title: "Array Restoration"
layout: "post"
diff: 普及+/提高
pid: CF1023D
tag: ['线段树']
---

# Array Restoration

## 题目描述

Initially there was an array $ a $ consisting of $ n $ integers. Positions in it are numbered from $ 1 $ to $ n $ .

Exactly $ q $ queries were performed on the array. During the $ i $ -th query some segment $ (l_i, r_i) $ $ (1 \le l_i \le r_i \le n) $ was selected and values of elements on positions from $ l_i $ to $ r_i $ inclusive got changed to $ i $ . The order of the queries couldn't be changed and all $ q $ queries were applied. It is also known that every position from $ 1 $ to $ n $ got covered by at least one segment.

We could have offered you the problem about checking if some given array (consisting of $ n $ integers with values from $ 1 $ to $ q $ ) can be obtained by the aforementioned queries. However, we decided that it will come too easy for you.

So the enhancement we introduced to it is the following. Some set of positions (possibly empty) in this array is selected and values of elements on these positions are set to $ 0 $ .

Your task is to check if this array can be obtained by the aforementioned queries. Also if it can be obtained then restore this array.

If there are multiple possible arrays then print any of them.

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 1 \le n, q \le 2 \cdot 10^5 $ ) — the number of elements of the array and the number of queries perfomed on it.

The second line contains $ n $ integer numbers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le q $ ) — the resulting array. If element at some position $ j $ is equal to $ 0 $ then the value of element at this position can be any integer from $ 1 $ to $ q $ .

## 输出格式

Print "YES" if the array $ a $ can be obtained by performing $ q $ queries. Segments $ (l_i, r_i) $ $ (1 \le l_i \le r_i \le n) $ are chosen separately for each query. Every position from $ 1 $ to $ n $ should be covered by at least one segment.

Otherwise print "NO".

If some array can be obtained then print $ n $ integers on the second line — the $ i $ -th number should be equal to the $ i $ -th element of the resulting array and should have value from $ 1 $ to $ q $ . This array should be obtainable by performing exactly $ q $ queries.

If there are multiple possible arrays then print any of them.

## 说明/提示

In the first example you can also replace $ 0 $ with $ 1 $ but not with $ 3 $ .

In the second example it doesn't really matter what segments to choose until query $ 10 $ when the segment is $ (1, 3) $ .

The third example showcases the fact that the order of queries can't be changed, you can't firstly set $ (1, 3) $ to $ 6 $ and after that change $ (2, 2) $ to $ 5 $ . The segment of $ 5 $ should be applied before segment of $ 6 $ .

There is a lot of correct resulting arrays for the fourth example.

## 样例 #1

### 输入

```
4 3
1 0 2 3

```

### 输出

```
YES
1 2 2 3

```

## 样例 #2

### 输入

```
3 10
10 10 10

```

### 输出

```
YES
10 10 10 

```

## 样例 #3

### 输入

```
5 6
6 5 6 2 2

```

### 输出

```
NO

```

## 样例 #4

### 输入

```
3 5
0 0 0

```

### 输出

```
YES
5 4 2

```



---

---
title: "Petya and Array"
layout: "post"
diff: 普及+/提高
pid: CF1042D
tag: ['线段树', '树状数组', '前缀和']
---

# Petya and Array

## 题目描述

Petya has an array $ a $ consisting of $ n $ integers. He has learned partial sums recently, and now he can calculate the sum of elements on any segment of the array really fast. The segment is a non-empty sequence of elements standing one next to another in the array.

Now he wonders what is the number of segments in his array with the sum less than $ t $ . Help Petya to calculate this number.

More formally, you are required to calculate the number of pairs $ l, r $ ( $ l \le r $ ) such that $ a_l + a_{l+1} + \dots + a_{r-1} + a_r < t $ .

## 输入格式

The first line contains two integers $ n $ and $ t $ ( $ 1 \le n \le 200\,000, |t| \le 2\cdot10^{14} $ ).

The second line contains a sequence of integers $ a_1, a_2, \dots, a_n $ ( $ |a_{i}| \le 10^{9} $ ) — the description of Petya's array. Note that there might be negative, zero and positive elements.

## 输出格式

Print the number of segments in Petya's array with the sum of elements less than $ t $ .

## 说明/提示

In the first example the following segments have sum less than $ 4 $ :

- $ [2, 2] $ , sum of elements is $ -1 $
- $ [2, 3] $ , sum of elements is $ 2 $
- $ [3, 3] $ , sum of elements is $ 3 $
- $ [4, 5] $ , sum of elements is $ 3 $
- $ [5, 5] $ , sum of elements is $ -1 $

## 样例 #1

### 输入

```
5 4
5 -1 3 4 -1

```

### 输出

```
5

```

## 样例 #2

### 输入

```
3 0
-1 2 -3

```

### 输出

```
4

```

## 样例 #3

### 输入

```
4 -1
-2 1 -2 3

```

### 输出

```
3

```



---

---
title: "Rooks Defenders"
layout: "post"
diff: 普及+/提高
pid: CF1679C
tag: ['线段树', '树状数组']
---

# Rooks Defenders

## 题目描述

You have a square chessboard of size $ n \times n $ . Rows are numbered from top to bottom with numbers from $ 1 $ to $ n $ , and columns — from left to right with numbers from $ 1 $ to $ n $ . So, each cell is denoted with pair of integers $ (x, y) $ ( $ 1 \le x, y \le n $ ), where $ x $ is a row number and $ y $ is a column number.

You have to perform $ q $ queries of three types:

- Put a new rook in cell $ (x, y) $ .
- Remove a rook from cell $ (x, y) $ . It's guaranteed that the rook was put in this cell before.
- Check if each cell of subrectangle $ (x_1, y_1) - (x_2, y_2) $ of the board is attacked by at least one rook.

Subrectangle is a set of cells $ (x, y) $ such that for each cell two conditions are satisfied: $ x_1 \le x \le x_2 $ and $ y_1 \le y \le y_2 $ .

Recall that cell $ (a, b) $ is attacked by a rook placed in cell $ (c, d) $ if either $ a = c $ or $ b = d $ . In particular, the cell containing a rook is attacked by this rook.

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 1 \le n \le 10^5 $ , $ 1 \le q \le 2 \cdot 10^5 $ ) — the size of the chessboard and the number of queries, respectively.

Each of the following $ q $ lines contains description of a query. Description begins with integer $ t $ ( $ t \in \{1, 2, 3\} $ ) which denotes type of a query:

- If $ t = 1 $ , two integers $ x $ and $ y $ follows ( $ 1 \le x, y \le n $ ) — coordinated of the cell where the new rook should be put in. It's guaranteed that there is no rook in the cell $ (x, y) $ at the moment of the given query.
- If $ t = 2 $ , two integers $ x $ and $ y $ follows ( $ 1 \le x, y \le n $ ) — coordinates of the cell to remove a rook from. It's guaranteed that there is a rook in the cell $ (x, y) $ at the moment of the given query.
- If $ t = 3 $ , four integers $ x_1, y_1, x_2 $ and $ y_2 $ follows ( $ 1 \le x_1 \le x_2 \le n $ , $ 1 \le y_1 \le y_2 \le n $ ) — subrectangle to check if each cell of it is attacked by at least one rook.

It's guaranteed that among $ q $ queries there is at least one query of the third type.

## 输出格式

Print the answer for each query of the third type in a separate line. Print "Yes" (without quotes) if each cell of the subrectangle is attacked by at least one rook.

Otherwise print "No" (without quotes).

## 说明/提示

Consider example. After the first two queries the board will look like the following picture (the letter $ R $ denotes cells in which rooks are located, the subrectangle of the query of the third type is highlighted in green):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/ed156665629e711ee2ed4626477b94d3794c1b66.png)Chessboard after performing the third and the fourth queries:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/287c91194903b3f438014966a1c3ab50aa3053b1.png)Chessboard after performing the fifth and the sixth queries:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/2450d8ada954d98a57be494097290cacc9d47393.png)Chessboard after performing the seventh and the eighth queries:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/860ee139e8d85a9e953e6218af254f9a2b04a395.png)Chessboard after performing the last two queries:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/fa48f4457088559fa8b50c796cacdd0ae0609075.png)

## 样例 #1

### 输入

```
8 10
1 2 4
3 6 2 7 2
1 3 2
3 6 2 7 2
1 4 3
3 2 6 4 8
2 4 3
3 2 6 4 8
1 4 8
3 2 6 4 8
```

### 输出

```
No
Yes
Yes
No
Yes
```



---

---
title: "Max GEQ Sum"
layout: "post"
diff: 普及+/提高
pid: CF1691D
tag: ['线段树', '单调队列']
---

# Max GEQ Sum

## 题目描述

现在你有一个由 $n$ 个整数组成的数组 $a$，$(i,j)$ 满足条件当且仅当 $\max (a_i,a_{i+1},\cdots,a_j)\ge a_i+a_{i+1}+\cdots+a_j$，其中 $1\le i\le j\le n$。问是否所有 $(i,j)$ 都满足要求。

## 输入格式

第一行包括一个整数 $t$，表示数据的组数。

每组数据的第一行包括一个整数 $n$，表示数组的长度。

每组数据的第二行为 $n$ 个整数，即为所给出的数组。

保证所有数据的 $n$ 之和不超过 $2\times 10^5$。

## 输出格式

对于每组数据，所有 $(i,j)$ 都符合条件则输出 `YES`，否则输出 `NO`。

## 样例 #1

### 输入

```
3
4
-1 1 -1 2
5
-1 2 -3 2 -1
3
2 3 -1
```

### 输出

```
YES
YES
NO
```



---

---
title: "Rorororobot"
layout: "post"
diff: 普及+/提高
pid: CF1709D
tag: ['线段树', 'ST 表']
---

# Rorororobot

## 题目描述

There is a grid, consisting of $ n $ rows and $ m $ columns. The rows are numbered from $ 1 $ to $ n $ from bottom to top. The columns are numbered from $ 1 $ to $ m $ from left to right. The $ i $ -th column has the bottom $ a_i $ cells blocked (the cells in rows $ 1, 2, \dots, a_i $ ), the remaining $ n - a_i $ cells are unblocked.

A robot is travelling across this grid. You can send it commands — move up, right, down or left. If a robot attempts to move into a blocked cell or outside the grid, it explodes.

However, the robot is broken — it executes each received command $ k $ times. So if you tell it to move up, for example, it will move up $ k $ times ( $ k $ cells). You can't send it commands while the robot executes the current one.

You are asked $ q $ queries about the robot. Each query has a start cell, a finish cell and a value $ k $ . Can you send the robot an arbitrary number of commands (possibly, zero) so that it reaches the finish cell from the start cell, given that it executes each command $ k $ times?

The robot must stop in the finish cell. If it visits the finish cell while still executing commands, it doesn't count.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n \le 10^9 $ ; $ 1 \le m \le 2 \cdot 10^5 $ ) — the number of rows and columns of the grid.

The second line contains $ m $ integers $ a_1, a_2, \dots, a_m $ ( $ 0 \le a_i \le n $ ) — the number of blocked cells on the bottom of the $ i $ -th column.

The third line contains a single integer $ q $ ( $ 1 \le q \le 2 \cdot 10^5 $ ) — the number of queries.

Each of the next $ q $ lines contain five integers $ x_s, y_s, x_f, y_f $ and $ k $ ( $ a[y_s] < x_s \le n $ ; $ 1 \le y_s \le m $ ; $ a[y_f] < x_f \le n $ ; $ 1 \le y_f \le m $ ; $ 1 \le k \le 10^9 $ ) — the row and the column of the start cell, the row and the column of the finish cell and the number of times each your command is executed. The start and the finish cell of each query are unblocked.

## 输出格式

For each query, print "YES" if you can send the robot an arbitrary number of commands (possibly, zero) so that it reaches the finish cell from the start cell, given that it executes each command $ k $ times. Otherwise, print "NO".

## 样例 #1

### 输入

```
11 10
9 0 0 10 3 4 8 11 10 8
6
1 2 1 3 1
1 2 1 3 2
4 3 4 5 2
5 3 11 5 3
5 3 11 5 2
11 9 9 10 1
```

### 输出

```
YES
NO
NO
NO
YES
YES
```



---

---
title: "Kirill and Mushrooms"
layout: "post"
diff: 普及+/提高
pid: CF1945F
tag: ['线段树', '堆']
---

# Kirill and Mushrooms

## 题目描述

当营地里的每个人都进入梦乡后，基里尔便偷偷溜出帐篷，到智慧的橡树下采蘑菇。

众所周知，橡树下生长着 $n$ 朵蘑菇，每朵蘑菇都有 $v_i$ 的魔力。 基里尔非常想用这些蘑菇制作一种魔力最大的灵药。

灵药的强度等于其中蘑菇的数量与这些蘑菇中最小魔力的乘积。要配制灵药，基里尔要依次采摘生长在橡树下的蘑菇。基里尔可以按照任何顺序采集蘑菇。

然而，事情并非如此简单。智慧的橡树给出了一个排列 $p_1,p_2,...,p_n$，如果基里尔只采摘 $k$ 朵蘑菇，那么 $v_{p_1},v_{p_2},...,v_{p_{k-1}}$ 都将变为 $0$。 基里尔不会使用魔力为零的蘑菇来配制灵药。

你的任务是帮助基里尔采集蘑菇，使他能够酿造出最大魔力的灵药。然而，基里尔有点害怕在橡树旁待太久，所以在所有适合采集蘑菇的方案中，他要求你找到蘑菇数量最少的那个。

## 输入格式

每个数据包含多个测试用例。

第一行包含一个整数 $t$ ( $1 \le t \le 10^4$ ) ，表示测试用例的数量。

每个测试用例的第一行都包含一个整数 $n$（$1 \le n \le 2\cdot 10^5$），表示蘑菇的数量。

第二行包含一个大小为 $n$ 的数组 $v$（$1\le v_i \le 10^9$），表示蘑菇的魔力。

第三行包含一个长度为 $n$ 的排列 $p$。

保证所有测试用例中的 $n$ 的值之和不超过 $2\cdot 10^5$。

## 输出格式

对于每个测试用例，输出两个用空格隔开的整数，分别为可以酿造的灵药的最大浓度和基里尔为此需要使用的最少蘑菇数量。

## 说明/提示

在样例的第一个测试用例中，你需要采摘前两朵蘑菇，因此灵药的魔力等于 $2 \cdot \min(a_1, a_2) = 2 \cdot \min(9, 8) = 2 \cdot 8 = 16$。 请注意，采摘两朵蘑菇后，第三朵蘑菇的魔力将变为 $0$。

## 样例 #1

### 输入

```
6
3
9 8 14
3 2 1
5
1 2 3 4 5
1 2 3 4 5
6
1 2 3 4 5 6
6 5 4 3 2 1
5
1 4 6 10 10
2 1 4 5 3
4
2 2 5 5
4 2 3 1
5
1 2 9 10 10
1 4 2 3 5
```

### 输出

```
16 2
9 3
8 2
20 2
5 1
20 2
```



---

---
title: "Long Inversions"
layout: "post"
diff: 普及+/提高
pid: CF1955E
tag: ['线段树']
---

# Long Inversions

## 题目描述

给定一个长度为$ n $的01字符串$ s $。01字符串是指只包含字符'1' 和'0'的字符串

可以选定一个整数$ k $ ( $ 1 \le k \le n $ )，将字符串中的连续k个字符进行替换，将0替换成1，1替换成0。

当 $ n=5 $ , $ s=00100 $时 , 你可以指定$ k=3 $ ，做如下操作：

- 翻转1-3的子串：$ s=\color{blue}{110}00 $ ;
- 反转3-5的子串：$ s=11\color{blue}{111} $ ;

经过不限次操作后，寻找能将01字符串中的所有字符转换成1的最大$ k $值。

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 1 \le n \le 5000 $ ) — the length of the string $ s $ .

The second line of each test case contains a string $ s $ of length $ n $ , consisting of the characters '1' and '0'.

It is guaranteed that the sum of the values $ n^2 $ over all test cases in the test does not exceed $ 25 \cdot 10^6 $ .

## 输出格式

For each test case, output the maximum integer $ k $ ( $ 1 \le k \le n $ ) for which it is possible to obtain a string $ s $ consisting only of the characters '1' using the described operations.

## 样例 #1

### 输入

```
5
5
00100
5
01000
7
1011101
3
000
2
10
```

### 输出

```
3
2
4
3
1
```



---

---
title: "Longest Max Min Subsequence"
layout: "post"
diff: 普及+/提高
pid: CF2001D
tag: ['线段树', '栈']
---

# Longest Max Min Subsequence

## 题目描述

You are given an integer sequence $ a_1, a_2, \ldots, a_n $ . Let $ S $ be the set of all possible non-empty subsequences of $ a $ without duplicate elements. Your goal is to find the longest sequence in $ S $ . If there are multiple of them, find the one that minimizes lexicographical order after multiplying terms at odd positions by $ -1 $ .

For example, given $ a = [3, 2, 3, 1] $ , $ S = \{[1], [2], [3], [2, 1], [2, 3], [3, 1], [3, 2], [2, 3, 1], [3, 2, 1]\} $ . Then $ [2, 3, 1] $ and $ [3, 2, 1] $ would be the longest, and $ [3, 2, 1] $ would be the answer since $ [-3, 2, -1] $ is lexicographically smaller than $ [-2, 3, -1] $ .

A sequence $ c $ is a subsequence of a sequence $ d $ if $ c $ can be obtained from $ d $ by the deletion of several (possibly, zero or all) elements.

A sequence $ c $ is lexicographically smaller than a sequence $ d $ if and only if one of the following holds:

- $ c $ is a prefix of $ d $ , but $ c \ne d $ ;
- in the first position where $ c $ and $ d $ differ, the sequence $ c $ has a smaller element than the corresponding element in $ d $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 5 \cdot 10^4 $ ). The description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 1 \le n \le 3 \cdot 10^5 $ ) — the length of $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) — the sequence $ a $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, output the answer in the following format:

Output an integer $ m $ in the first line — the length of $ b $ .

Then output $ m $ integers $ b_1, b_2, \ldots, b_m $ in the second line — the sequence $ b $ .

## 说明/提示

In the first example, $ S = \{[1], [2], [3], [1, 3], [2, 1], [2, 3], [3, 1], [3, 2], [2, 1, 3], [3, 2, 1]\} $ . Among them, $ [2, 1, 3] $ and $ [3, 2, 1] $ are the longest and $ [-3, 2, -1] $ is lexicographical smaller than $ [-2, 1, -3] $ , so $ [3, 2, 1] $ is the answer.

In the second example, $ S = \{[1]\} $ , so $ [1] $ is the answer.

## 样例 #1

### 输入

```
4
4
3 2 1 3
4
1 1 1 1
9
3 2 1 3 2 1 3 2 1
1
1
```

### 输出

```
3
3 2 1
1
1
3
3 1 2
1
1
```

## 样例 #2

### 输入

```
10
2
1 2
10
5 2 1 7 9 7 2 5 5 2
2
1 2
10
2 2 8 7 7 9 8 1 9 6
9
9 1 7 5 8 5 6 4 1
3
3 3 3
6
1 6 4 4 6 5
6
3 4 4 5 3 3
10
4 1 4 5 4 5 10 1 5 1
7
1 2 1 3 2 4 6
```

### 输出

```
2
1 2
5
5 1 9 7 2
2
1 2
6
2 7 9 8 1 6
7
9 1 7 5 8 6 4
1
3
4
1 4 6 5
3
4 5 3
4
5 4 10 1
5
2 1 3 4 6
```



---

---
title: "Adjust The Presentation (Hard Version)"
layout: "post"
diff: 普及+/提高
pid: CF2021C2
tag: ['贪心', '线段树']
---

# Adjust The Presentation (Hard Version)

## 题目描述

This is the hard version of the problem. In the two versions, the constraints on $ q $ and the time limit are different. In this version, $ 0 \leq q \leq 2 \cdot 10^5 $ . You can make hacks only if all the versions of the problem are solved.

A team consisting of $ n $ members, numbered from $ 1 $ to $ n $ , is set to present a slide show at a large meeting. The slide show contains $ m $ slides.

There is an array $ a $ of length $ n $ . Initially, the members are standing in a line in the order of $ a_1, a_2, \ldots, a_n $ from front to back. The slide show will be presented in order from slide $ 1 $ to slide $ m $ . Each section will be presented by the member at the front of the line. After each slide is presented, you can move the member at the front of the line to any position in the lineup (without changing the order of the rest of the members). For example, suppose the line of members is $ [\color{red}{3},1,2,4] $ . After member $ 3 $ presents the current slide, you can change the line of members into either $ [\color{red}{3},1,2,4] $ , $ [1,\color{red}{3},2,4] $ , $ [1,2,\color{red}{3},4] $ or $ [1,2,4,\color{red}{3}] $ .

There is also an array $ b $ of length $ m $ . The slide show is considered good if it is possible to make member $ b_i $ present slide $ i $ for all $ i $ from $ 1 $ to $ m $ under these constraints.

However, your annoying boss wants to make $ q $ updates to the array $ b $ . In the $ i $ -th update, he will choose a slide $ s_i $ and a member $ t_i $ and set $ b_{s_i} := t_i $ . Note that these updates are persistent, that is changes made to the array $ b $ will apply when processing future updates.

For each of the $ q+1 $ states of array $ b $ , the initial state and after each of the $ q $ updates, determine if the slideshow is good.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains three integers $ n $ , $ m $ and $ q $ ( $ 1 \le n, m \le 2 \cdot 10^5 $ ; $ 0 \leq q \leq 2 \cdot 10^5 $ ) — the number of members and the number of sections.

The second line of each test case contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 1 \le a_i \le n $ ) — the initial order of the members from front to back. It is guaranteed that each integer from $ 1 $ to $ n $ appears exactly once in $ a $ .

The third line of each test case contains $ m $ integers $ b_1, b_2, \ldots, b_m $ ( $ 1 \le b_i \le n $ ) — the members who should present each section.

Each of the next $ q $ lines contains two integers $ s_i $ and $ t_i $ ( $ 1 \le s_i \le m $ , $ 1 \le t_i \le n $ ) — parameters of an update.

It is guaranteed that the sum of $ n $ , the sum of $ m $ and the sum of $ q $ over all test cases do not exceed $ 2 \cdot 10^5 $ respectively.

## 输出格式

For each test case, output $ q+1 $ lines corresponding to the $ q+1 $ states of the array $ b $ . Output "YA" if the slide show is good, and "TIDAK" otherwise.

You can output the answer in any case (upper or lower). For example, the strings "yA", "Ya", "ya", and "YA" will be recognized as positive responses.

## 说明/提示

For the first test case, you do not need to move the members as both slides are presented by member $ 1 $ , who is already at the front of the line. After that, set $ b_1 := 2 $ , now slide $ 1 $ must be presented by member $ 2 $ which is impossible as member $ 1 $ will present slide $ 1 $ first. Then, set $ b_1 = 1 $ , the $ b $ is the same as the initial $ b $ , making a good presentation possible.

## 样例 #1

### 输入

```
3
4 2 2
1 2 3 4
1 1
1 2
1 1
3 6 2
1 2 3
1 1 2 3 3 2
3 3
2 2
4 6 2
3 1 4 2
3 1 1 2 3 4
3 4
4 2
```

### 输出

```
YA
TIDAK
YA
YA
TIDAK
YA
TIDAK
YA
YA
```



---

---
title: "Skipping"
layout: "post"
diff: 普及+/提高
pid: CF2023B
tag: ['动态规划 DP', '图论', '线段树', '最短路']
---

# Skipping

## 题目描述

现在已经是3024年了，出题的想法早就枯竭。现今的OI以一种修改后的个人参赛形式进行。比赛有$n$道题，编号从$1$到$n$，一道题有一个分数$a_i$和一个参数$b_i$。最开始，评测系统会把第$1$道题丢给选手。当一个选手拿到第$i$道题，他有两个选择：

- 提交，获得$a_i$分
- 跳过，但他再不能去交这道题了。

接下来，评测系统会把编号最大的符合下述条件的题目$j$丢给选手：

- 如果选手提交了$i$题，那么$j<i$
- 如果选手选择跳过，那么$j\leq b_i$

系统不能给选手一道之前给过的题目。如果系统找不到这样的题，那么比赛结束。特别的，如果选手提交第一题，比赛结束。

请你帮助小p拿到最高的可能得分。

## 输入格式

此题**多测**，第一行一个整数$t(1\leq t\leq 10^5$，为测试数据组数。每组数据如下：

第一行一个整数$n(1\leq n\leq 4\cdot10^5)$，表示题目数量

第二行一行$n$个整数$a_1,a_2……a_n(1\leq a_i\leq 10^9)$表示题目分数。

第三行一行$n$个整数$b_1,b_2……b_n(1\leq b_i\leq n)$表示题目参数。

保证所有测试数据的$\sum n$不超过$4\cdot 10^5$。

## 输出格式

每行输出一个整数，为小p最大的可能得分。

## 样例 #1

### 输入

```
4
2
15 16
2 1
5
10 10 100 100 1000
3 4 1 1 1
3
100 49 50
3 2 2
4
100 200 300 1000
2 3 4 1
```

### 输出

```
16
200
100
1000
```



---

---
title: "QED's Favorite Permutation"
layout: "post"
diff: 普及+/提高
pid: CF2030D
tag: ['线段树', '差分']
---

# QED's Favorite Permutation

## 题目描述

你有一个长度为 $n$ 的排列 $p$，也就是说，$1$ 到 $n$ 中的每个正整数都在 $p$ 中出现恰好一次。同时你还有一个长度也为 $n$ 的字符串 $s$，其中仅含 `L` 和 `R` 两种字符。（排列和字符串的下标均从 $1$ 开始编号）

定义一次操作为：任意选择一个编号 $i$（$1 \le i \le n$），在这之后：

* 如果 $s_i$ 为 `L`，则交换 $p_i$ 和 $p_{i-1}$。（保证 $s_1$ 不为 `L`）

* 如果 $s_i$ 为 `R`，则交换 $p_i$ 和 $p_{i+1}$。（保证 $s_n$ 不为 `R`）

接下来给出 $q$ 次询问，在第 $i$ 次询问中（$1 \le i \le q$），你将会得到一个编号 $x_i$（$1 \le x_i \le n$），表示如果 $s_{x_i}$ 为 `L`，则你需要将其改为 `R`；反之如果 $s_{x_i}$ 为 `R`，则你需要将其改为 `L`。在修改完成之后，你还需要判断能否通过上述操作使得排列 $p$ 单调递增（操作次数不限），即对任意的 $1 \le i \le n-1$，都有 $p_i < p_{i+1}$。

**询问中对字符串 $\bm{s}$ 的修改均为永久性的，会在询问结束后保留。在回答询问的过程中，你不应对排列 $\bm{p}$ 进行任何真实的操作。**

## 输入格式

第一行一个正整数 $t$（$1 \le t \le 10^4$），表示测试数据的组数。对于每组测试数据而言：

第一行包含两个正整数 $n,q$（$1\le n,q \le 2 \times 10^5$，$n \ge 3$），分别表示排列的长度和询问的次数。

第二行包含 $n$ 个正整数 $p_1,p_2,...,p_n$（$1 \le p_i \le n$），表示排列 $p$。

第三行包含一个长度为 $n$ 的字符串 $s$，保证 $s_i \in \{ \texttt{L}, \texttt{R} \}，s_1 = \texttt{R}，s_n = \texttt{L}$。

接下来 $q$ 行，其中第 $i$ 行包含一个正整数 $x_i$（$1 \le x_i \le n$），表示要修改的字符的编号。

保证所有测试数据中 $n$ 和 $q$ 的总和都不超过 $2 \times 10^5$。

## 输出格式

对于每个询问，在单独一行输出一个字符串表示答案。如果在修改完成之后能通过上述操作使得排列 $p$ 单调递增（操作次数不限），则输出 `YES`；否则输出 `NO`。评测时不区分大小写，例如 `Yes`，`yES` 等均被认为与 `YES` 等价。

### 【样例解释】

对于第一组测试数据，在第一次询问之后，$s = \texttt{RRRLL}$。我们可以通过如下操作序列使得排列 $p$ 单调递增：

* 初始时，$p=[1,4,2,5,3]$。

* 选择 $i=2$ 进行一次操作，由于 $s_2 = \texttt{R}$，所以我们交换 $p_2$ 和 $p_3$，得到 $p=[1,2,4,5,3]$。

* 选择 $i=5$ 进行一次操作，由于 $s_5 = \texttt{L}$，所以我们交换 $p_5$ 和 $p_4$，得到 $p=[1,2,4,3,5]$。

* 选择 $i=4$ 进行一次操作，由于 $s_4 = \texttt{L}$，所以我们交换 $p_4$ 和 $p_3$，得到 $p=[1,2,3,4,5]$。此时，排列 $p$ 已经单调递增。

因此，对于第一次询问你应当输出 `YES`。

对于第一组测试数据可以证明，在三次询问对字符串 $s$ 的修改完成之后，不可能再通过上述操作使得排列 $p$ 单调递增。因此，对于第三次询问你应当输出 `NO`。




Translated by FruitWasTaken

## 样例 #1

### 输入

```
3
5 3
1 4 2 5 3
RLRLL
2
4
3
8 5
1 5 2 4 8 3 6 7
RRLLRRRL
4
3
5
3
4
6 2
1 2 3 4 5 6
RLRLRL
4
5
```

### 输出

```
YES
YES
NO
NO
YES
NO
NO
NO
YES
YES
```



---

---
title: "Gifts Order"
layout: "post"
diff: 普及+/提高
pid: CF2057D
tag: ['线段树']
---

# Gifts Order

## 题目描述

“T-Generation” 队计划采购一些毛衣以满足多种需求，他们拥有 $n$ 件毛衣编号从 $1$ 至 $n$。第 $i$ 件毛衣的尺寸为 $a_i$。现在，他们需要选出某段连续的毛衣送去参加奥林匹克竞赛。这些毛衣必须尽可能适合更多的人，同时又不能选择得太多。

他们需要选择两个下标 $l$ 和 $r$（$1 \le l \le r \le n$），使便利性最大化。便利性定义为 $\operatorname{max}(a_l, a_{l + 1}, \ldots, a_r) - \operatorname{min}(a_l, a_{l + 1}, \ldots, a_r) - (r - l)$，也就是尺寸的范围减去所选毛衣数量。

考虑到毛衣的尺寸可能会发生变化，总共有 $q$ 次这样的变动。每次变化中，第 $p$ 件毛衣的尺寸变为 $x$。

请帮助 “T-Generation” 团队计算出在所有可能的 $(l, r)$ 对中，初次和每次尺寸调整后的最大便利性。

## 输入格式

输入包含多个测试用例。第一行是一个整数 $t$（$1 \le t \le 10^4$）表示测试用例的数量。随后是每个测试用例的描述。

每个测试用例的第一行包含两个整数 $n$ 和 $q$（$1 \le n, q \le 2 \cdot 10^5$），分别表示毛衣总数和尺寸变化的次数。

接下来的第二行包括 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \le a_i \le 10^9$），表示每件毛衣的尺寸。

此后 $q$ 行，每行包含两个整数 $p$ 和 $x$（$1 \le p \le n$, $1 \le x \le 10^9$），表示一次尺寸变化，第 $p$ 件毛衣的尺寸变为 $x$。

保证所有测试用例中所有 $n$ 的总和以及所有 $q$ 的总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出在操作前以及每次尺寸变化后，所有可能的 $(l, r)$ 对中最大便利性。

## 说明/提示

来看第一个测试用例的情况：

- 在没有变化之前，可以选取所有毛衣，此时便利性等于 $\operatorname{max}(a_1, a_2) - \operatorname{min}(a_1, a_2) - (2 - 1) = 10 - 1 - 1 = 8$。
- 第一次查询后，两件毛衣的尺寸都变为 $10$，只能选取第一件毛衣，此时便利性等于 $10 - 10 - 0 = 0$。
- 第二次查询后，第一件毛衣的尺寸为 $10$，第二件为 $2$，可以选取所有毛衣，便利性为 $\operatorname{max}(a_1, a_2) - \operatorname{min}(a_1, a_2) - (2 - 1) = 10 - 2 - 1 = 7$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
2 2
1 10
1 10
2 2
5 3
1 2 3 4 5
3 7
1 4
5 2
8 5
7 4 2 4 8 2 1 4
5 4
1 10
3 2
8 11
7 7
```

### 输出

```
8
0
7
0
4
4
4
5
3
6
6
9
7
```



---

---
title: "XOR on Segment"
layout: "post"
diff: 普及+/提高
pid: CF242E
tag: ['线段树', '进制', '位运算']
---

# XOR on Segment

## 题目描述

You've got an array $ a $ , consisting of $ n $ integers $ a_{1},a_{2},...,a_{n} $ . You are allowed to perform two operations on this array:

1. Calculate the sum of current array elements on the segment $ [l,r] $ , that is, count value $ a_{l}+a_{l+1}+...+a_{r} $ .
2. Apply the xor operation with a given number $ x $ to each array element on the segment $ [l,r] $ , that is, execute ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF242E/a6ed6800239445c652bf1618450a09b2fce8b86d.png). This operation changes exactly $ r-l+1 $ array elements.

Expression ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF242E/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) means applying bitwise xor operation to numbers $ x $ and $ y $ . The given operation exists in all modern programming languages, for example in language C++ and Java it is marked as "^", in Pascal — as "xor".

You've got a list of $ m $ operations of the indicated type. Your task is to perform all given operations, for each sum query you should print the result you get.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the size of the array. The second line contains space-separated integers $ a_{1},a_{2},...,a_{n} $ ( $ 0<=a_{i}<=10^{6} $ ) — the original array.

The third line contains integer $ m $ ( $ 1<=m<=5·10^{4} $ ) — the number of operations with the array. The $ i $ -th of the following $ m $ lines first contains an integer $ t_{i} $ ( $ 1<=t_{i}<=2 $ ) — the type of the $ i $ -th query. If $ t_{i}=1 $ , then this is the query of the sum, if $ t_{i}=2 $ , then this is the query to change array elements. If the $ i $ -th operation is of type $ 1 $ , then next follow two integers $ l_{i},r_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ). If the $ i $ -th operation is of type $ 2 $ , then next follow three integers $ l_{i},r_{i},x_{i} $ ( $ 1<=l_{i}<=r_{i}<=n,1<=x_{i}<=10^{6} $ ). The numbers on the lines are separated by single spaces.

## 输出格式

For each query of type $ 1 $ print in a single line the sum of numbers on the given segment. Print the answers to the queries in the order in which the queries go in the input.

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams, or the %I64d specifier.

## 样例 #1

### 输入

```
5
4 10 3 13 7
8
1 2 4
2 1 3 3
1 2 4
1 3 3
2 2 5 5
1 1 5
2 1 2 10
1 2 3

```

### 输出

```
26
22
0
34
11

```

## 样例 #2

### 输入

```
6
4 7 4 0 7 3
5
2 2 3 8
1 1 5
2 3 5 1
2 4 5 6
1 2 3

```

### 输出

```
38
28

```



---

---
title: "Inna and Sequence"
layout: "post"
diff: 普及+/提高
pid: CF374D
tag: ['线段树']
---

# Inna and Sequence

## 题目描述

Dima's spent much time thinking what present to give to Inna and gave her an empty sequence $ w $ . Now they want to fill sequence $ w $ with numbers zero and one. For that, they decided to play an amusing game.

Before the game begins, Dima chooses $ m $ integers $ a_{1},a_{2},...,a_{m} $ $ (1<=a_{1}<a_{2}<...<a_{m}) $ . Then Inna and Dima start playing, that is, adding numbers to sequence $ w $ . Each new number they choose is added to the end of the sequence. At some moments of time Dima feels that the game is going to end too soon (and he wants to play with Inna as long as possible), so he hits a table hard with his fist. At that the $ a_{1} $ -th, $ a_{2} $ -th, $ a_{3} $ -th, $ ... $ , $ a_{k} $ -th numbers from the beginning simultaneously fall out of the sequence (the sequence gets $ k $ numbers less). Here $ k $ is such maximum number that value $ a_{k} $ doesn't exceed the current length of the sequence. If number $ a_{1} $ is larger than the current length of $ w $ , then nothing falls out of the sequence.

You are given the chronological sequence of events in the game. Each event is either adding a number to the end of sequence $ w $ or Dima's hit on the table. Calculate the sequence $ w $ after all these events happen.

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ $ (1<=n,m<=10^{6}) $ showing how many events took place and how many numbers Dima chose.

The next line contains $ m $ distinct integers $ a_{i} $ $ (1<=a_{i}<=10^{6}) $ sorted in the increasing order.

Next $ n $ lines describe the events in the chronological order. Each line contains a single integer: -1, 0 or 1. Number -1 means that Dima hits the table. Number 0 means that Inna and Dima add number 0 to the end of the sequence. Number 1 means that Inna and Dima add number 1 to the end of the sequence.

## 输出格式

In a single line print a sequence of numbers 0 and 1 — the elements of the sequence after all events happen. Print the elements of the sequence in the order from the beginning to the end of the sequence.

If after all events the sequence ends up empty, print "Poor stack!".

## 样例 #1

### 输入

```
10 3
1 3 6
-1
1
1
0
0
-1
0
1
-1
1

```

### 输出

```
011

```

## 样例 #2

### 输入

```
2 1
1
1
-1

```

### 输出

```
Poor stack!

```



---

---
title: "Present"
layout: "post"
diff: 普及+/提高
pid: CF460C
tag: ['模拟', '线段树', '差分']
---

# Present

## 题目描述

Little beaver is a beginner programmer, so informatics is his favorite subject. Soon his informatics teacher is going to have a birthday and the beaver has decided to prepare a present for her. He planted $ n $ flowers in a row on his windowsill and started waiting for them to grow. However, after some time the beaver noticed that the flowers stopped growing. The beaver thinks it is bad manners to present little flowers. So he decided to come up with some solutions.

There are $ m $ days left to the birthday. The height of the $ i $ -th flower (assume that the flowers in the row are numbered from $ 1 $ to $ n $ from left to right) is equal to $ a_{i} $ at the moment. At each of the remaining $ m $ days the beaver can take a special watering and water $ w $ contiguous flowers (he can do that only once at a day). At that each watered flower grows by one height unit on that day. The beaver wants the height of the smallest flower be as large as possible in the end. What maximum height of the smallest flower can he get?

## 输入格式

The first line contains space-separated integers $ n $ , $ m $ and $ w $ $ (1<=w<=n<=10^{5}; 1<=m<=10^{5}) $ . The second line contains space-separated integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=10^{9}) $ .

## 输出格式

Print a single integer — the maximum final height of the smallest flower.

## 说明/提示

In the first sample beaver can water the last 3 flowers at the first day. On the next day he may not to water flowers at all. In the end he will get the following heights: \[2, 2, 2, 3, 2, 2\]. The smallest flower has height equal to 2. It's impossible to get height 3 in this test.

## 样例 #1

### 输入

```
6 2 3
2 2 2 2 1 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2 5 1
5 8

```

### 输出

```
9

```



---

---
title: "Glass Carving"
layout: "post"
diff: 普及+/提高
pid: CF527C
tag: ['线段树', '排序']
---

# Glass Carving

## 题目描述

Leonid wants to become a glass carver (the person who creates beautiful artworks by cutting the glass). He already has a rectangular $ w $ mm $ × $ $ h $ mm sheet of glass, a diamond glass cutter and lots of enthusiasm. What he lacks is understanding of what to carve and how.

In order not to waste time, he decided to practice the technique of carving. To do this, he makes vertical and horizontal cuts through the entire sheet. This process results in making smaller rectangular fragments of glass. Leonid does not move the newly made glass fragments. In particular, a cut divides each fragment of glass that it goes through into smaller fragments.

After each cut Leonid tries to determine what area the largest of the currently available glass fragments has. Since there appear more and more fragments, this question takes him more and more time and distracts him from the fascinating process.

Leonid offers to divide the labor — he will cut glass, and you will calculate the area of the maximum fragment after each cut. Do you agree?

## 输入格式

The first line contains three integers $ w,h,n $ ( $ 2<=w,h<=200000 $ , $ 1<=n<=200000 $ ).

Next $ n $ lines contain the descriptions of the cuts. Each description has the form $ H y $ or $ V x $ . In the first case Leonid makes the horizontal cut at the distance $ y $ millimeters ( $ 1<=y<=h-1 $ ) from the lower edge of the original sheet of glass. In the second case Leonid makes a vertical cut at distance $ x $ ( $ 1<=x<=w-1 $ ) millimeters from the left edge of the original sheet of glass. It is guaranteed that Leonid won't make two identical cuts.

## 输出格式

After each cut print on a single line the area of the maximum available glass fragment in mm $ ^{2} $ .

## 说明/提示

Picture for the first sample test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF527C/6468d2fd0321178fa316ccb774411f002769e9ee.png) Picture for the second sample test:  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF527C/40ba2772b27431a21bc874ab308dc348ec8365fd.png)

## 样例 #1

### 输入

```
4 3 4
H 2
V 2
V 3
V 1

```

### 输出

```
8
4
4
2

```

## 样例 #2

### 输入

```
7 6 5
H 4
V 3
V 5
H 2
V 1

```

### 输出

```
28
16
12
6
4

```



---

---
title: "Factory Repairs"
layout: "post"
diff: 普及+/提高
pid: CF627B
tag: ['线段树', '树状数组']
---

# Factory Repairs

## 题目描述

A factory produces thimbles in bulk. Typically, it can produce up to $ a $ thimbles a day. However, some of the machinery is defective, so it can currently only produce $ b $ thimbles each day. The factory intends to choose a $ k $ -day period to do maintenance and construction; it cannot produce any thimbles during this time, but will be restored to its full production of $ a $ thimbles per day after the $ k $ days are complete.

Initially, no orders are pending. The factory receives updates of the form $ d_{i} $ , $ a_{i} $ , indicating that $ a_{i} $ new orders have been placed for the $ d_{i} $ -th day. Each order requires a single thimble to be produced on precisely the specified day. The factory may opt to fill as many or as few of the orders in a single batch as it likes.

As orders come in, the factory owner would like to know the maximum number of orders he will be able to fill if he starts repairs on a given day $ p_{i} $ . Help the owner answer his questions.

## 输入格式

The first line contains five integers $ n $ , $ k $ , $ a $ , $ b $ , and $ q $ ( $ 1<=k<=n<=200000 $ , $ 1<=b&lt;a<=10\ 000 $ , $ 1<=q<=200000 $ ) — the number of days, the length of the repair time, the production rates of the factory, and the number of updates, respectively.

The next $ q $ lines contain the descriptions of the queries. Each query is of one of the following two forms:

- $ 1\ d_{i}\ a_{i} $ ( $ 1<=d_{i}<=n $ , $ 1<=a_{i}<=10\ 000 $ ), representing an update of $ a_{i} $ orders on day $ d_{i} $ , or
- $ 2\ p_{i} $ ( $ 1<=p_{i}<=n-k+1 $ ), representing a question: at the moment, how many orders could be filled if the factory decided to commence repairs on day $ p_{i} $ ?

It's guaranteed that the input will contain at least one query of the second type.

## 输出格式

For each query of the second type, print a line containing a single integer — the maximum number of orders that the factory can fill over all $ n $ days.

## 说明/提示

Consider the first sample.

We produce up to $ 1 $ thimble a day currently and will produce up to $ 2 $ thimbles a day after repairs. Repairs take $ 2 $ days.

For the first question, we are able to fill $ 1 $ order on day $ 1 $ , no orders on days $ 2 $ and $ 3 $ since we are repairing, no orders on day $ 4 $ since no thimbles have been ordered for that day, and $ 2 $ orders for day $ 5 $ since we are limited to our production capacity, for a total of $ 3 $ orders filled.

For the third question, we are able to fill $ 1 $ order on day $ 1 $ , $ 1 $ order on day $ 2 $ , and $ 2 $ orders on day $ 5 $ , for a total of $ 4 $ orders.

## 样例 #1

### 输入

```
5 2 2 1 8
1 1 2
1 5 3
1 2 1
2 2
1 4 2
1 3 2
2 1
2 3

```

### 输出

```
3
6
4

```

## 样例 #2

### 输入

```
5 4 10 1 6
1 1 5
1 5 5
1 3 2
1 5 2
2 1
2 2

```

### 输出

```
7
1

```



---

---
title: "Petya and Post"
layout: "post"
diff: 普及+/提高
pid: CF66E
tag: ['动态规划 DP', '线段树', '枚举']
---

# Petya and Post

## 题目描述

### 题意翻译

有 $n$ 个邮局，在每个邮局都有一个加油站。（邮局编号从 $1$ 开始）

对于第 $i$ 个邮局，$a_i$ 表示位于这个邮局加油站最多能加多少油，$b_i$ 表示它到第 $i+1$ 个邮局会耗费多少油。特殊的，对于第 $n$ 个邮局，$b_n$ 表示它到第 $1$ 个邮局会耗费多少油。

现在可以任意选择一个邮局出发，开始的油量为 $0$。可以选择顺时针或者逆时针走动，一旦决定方向就不可以回头。 要求路途上任一时刻油量$\ge 0$。

## 输入格式

第一行一个正整数 $n$。

第二行 $n$ 个正整数表示 $a$。

第三行 $n$ 个正整数表示 $b$。

## 输出格式

第一行一个正整数 $res$，表示有多少个邮局出发可以回到自己。

第二行 $res$ 个正整数，从小到大的输出这些可以回到自己的邮局的编号。

### 数据规模

$1 \le n \le 10^5$。

$\sum\limits_{i=1}^n a_i$ 不超过 $10^9$。

$\sum\limits_{i=1}^n b_i$ 不超过 $10^9$。

## 样例 #1

### 输入

```
4
1 7 2 3
8 1 1 3

```

### 输出

```
2
2 4

```

## 样例 #2

### 输入

```
8
1 2 1 2 1 2 1 2
2 1 2 1 2 1 2 1

```

### 输出

```
8
1 2 3 4 5 6 7 8

```



---

---
title: "Segments Removal"
layout: "post"
diff: 普及+/提高
pid: CF899E
tag: ['线段树', '优先队列', '队列']
---

# Segments Removal

## 题目描述

Vasya has an array of integers of length $ n $ .

Vasya performs the following operations on the array: on each step he finds the longest segment of consecutive equal integers (the leftmost, if there are several such segments) and removes it. For example, if Vasya's array is $ [13,13,7,7,7,2,2,2] $ , then after one operation it becomes $ [13,13,2,2,2] $ .

Compute the number of operations Vasya should make until the array becomes empty, i.e. Vasya removes all elements from it.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=200000 $ ) — the length of the array.

The second line contains a sequence $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) — Vasya's array.

## 输出格式

Print the number of operations Vasya should make to remove all elements from the array.

## 说明/提示

In the first example, at first Vasya removes two fives at the second and third positions. The array becomes $ [2,2] $ . In the second operation Vasya removes two twos at the first and second positions. After that the array becomes empty.

In the second example Vasya has to perform five operations to make the array empty. In each of them he removes the first element from the array.

In the third example Vasya needs three operations. In the first operation he removes all integers $ 4 $ , in the second — all integers $ 100 $ , in the third — all integers $ 2 $ .

In the fourth example in the first operation Vasya removes the first two integers $ 10 $ . After that the array becomes $ [50,10,50,50] $ . Then in the second operation Vasya removes the two rightmost integers $ 50 $ , so that the array becomes $ [50,10] $ . In the third operation he removes the remaining $ 50 $ , and the array becomes $ [10] $ after that. In the last, fourth operation he removes the only remaining $ 10 $ . The array is empty after that.

## 样例 #1

### 输入

```
4
2 5 5 2

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5
6 3 4 1 5

```

### 输出

```
5

```

## 样例 #3

### 输入

```
8
4 4 4 2 2 100 100 100

```

### 输出

```
3

```

## 样例 #4

### 输入

```
6
10 10 50 10 50 50

```

### 输出

```
4

```



---

---
title: "Bash and a Tough Math Puzzle"
layout: "post"
diff: 普及+/提高
pid: CF914D
tag: ['线段树']
---

# Bash and a Tough Math Puzzle

## 题目描述

Bash likes playing with arrays. He has an array $ a_{1},a_{2},...\ a_{n} $ of $ n $ integers. He likes to guess the greatest common divisor (gcd) of different segments of the array. Of course, sometimes the guess is not correct. However, Bash will be satisfied if his guess is almost correct.

Suppose he guesses that the gcd of the elements in the range $ [l,r] $ of $ a $ is $ x $ . He considers the guess to be almost correct if he can change at most one element in the segment such that the gcd of the segment is $ x $ after making the change. Note that when he guesses, he doesn't actually change the array — he just wonders if the gcd of the segment can be made $ x $ . Apart from this, he also sometimes makes changes to the array itself.

Since he can't figure it out himself, Bash wants you to tell him which of his guesses are almost correct. Formally, you have to process $ q $ queries of one of the following forms:

- $ 1lrx $ — Bash guesses that the gcd of the range $ [l,r] $ is $ x $ . Report if this guess is almost correct.
- $ 2iy $ — Bash sets $ a_{i} $ to $ y $ .

Note: The array is $ 1 $ -indexed.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=5·10^{5} $ ) — the size of the array.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) — the elements of the array.

The third line contains an integer $ q $ ( $ 1<=q<=4·10^{5} $ ) — the number of queries.

The next $ q $ lines describe the queries and may have one of the following forms:

- $ 1lrx $ ( $ 1<=l<=r<=n,1<=x<=10^{9} $ ).
- $ 2iy $ $ (1<=i<=n,1<=y<=10^{9}) $ .

Guaranteed, that there is at least one query of first type.

## 输出格式

For each query of first type, output "YES" (without quotes) if Bash's guess is almost correct and "NO" (without quotes) otherwise.

## 说明/提示

In the first sample, the array initially is $ {2,6,3} $ .

For query $ 1 $ , the first two numbers already have their gcd as $ 2 $ .

For query $ 2 $ , we can achieve a gcd of $ 3 $ by changing the first element of the array to $ 3 $ . Note that the changes made during queries of type $ 1 $ are temporary and do not get reflected in the array.

After query $ 3 $ , the array is now $ {9,6,3} $ .

 For query $ 4 $ , no matter which element you change, you cannot get the gcd of the range to be $ 2 $ .

## 样例 #1

### 输入

```
3
2 6 3
4
1 1 2 2
1 1 3 3
2 1 9
1 1 3 2

```

### 输出

```
YES
YES
NO

```

## 样例 #2

### 输入

```
5
1 2 3 4 5
6
1 1 4 2
2 3 6
1 1 4 2
1 1 5 2
2 5 10
1 1 5 2

```

### 输出

```
NO
YES
NO
YES

```



---

---
title: "Queue"
layout: "post"
diff: 普及+/提高
pid: CF91B
tag: ['线段树']
---

# Queue

## 题目描述

There are $ n $ walruses standing in a queue in an airport. They are numbered starting from the queue's tail: the $ 1 $ -st walrus stands at the end of the queue and the $ n $ -th walrus stands at the beginning of the queue. The $ i $ -th walrus has the age equal to $ a_{i} $ .

The $ i $ -th walrus becomes displeased if there's a younger walrus standing in front of him, that is, if exists such $ j $ ( $ i<j $ ), that $ a_{i}>a_{j} $ . The displeasure of the $ i $ -th walrus is equal to the number of walruses between him and the furthest walrus ahead of him, which is younger than the $ i $ -th one. That is, the further that young walrus stands from him, the stronger the displeasure is.

The airport manager asked you to count for each of $ n $ walruses in the queue his displeasure.

## 输入格式

The first line contains an integer $ n $ ( $ 2<=n<=10^{5} $ ) — the number of walruses in the queue. The second line contains integers $ a_{i} $ ( $ 1<=a_{i}<=10^{9} $ ).

Note that some walruses can have the same age but for the displeasure to emerge the walrus that is closer to the head of the queue needs to be strictly younger than the other one.

## 输出格式

Print $ n $ numbers: if the $ i $ -th walrus is pleased with everything, print "-1" (without the quotes). Otherwise, print the $ i $ -th walrus's displeasure: the number of other walruses that stand between him and the furthest from him younger walrus.

## 样例 #1

### 输入

```
6
10 8 5 3 50 45

```

### 输出

```
2 1 0 -1 0 -1 
```

## 样例 #2

### 输入

```
7
10 4 6 3 2 8 15

```

### 输出

```
4 2 1 0 -1 -1 -1 
```

## 样例 #3

### 输入

```
5
10 3 1 10 11

```

### 输出

```
1 0 -1 -1 -1 
```



---

---
title: "Tufurama"
layout: "post"
diff: 普及+/提高
pid: CF961E
tag: ['数学', '可持久化线段树', '级数']
---

# Tufurama

## 题目描述

One day Polycarp decided to rewatch his absolute favourite episode of well-known TV series "Tufurama". He was pretty surprised when he got results only for season 7 episode 3 with his search query of "Watch Tufurama season 3 episode 7 online full hd free". This got Polycarp confused — what if he decides to rewatch the entire series someday and won't be able to find the right episodes to watch? Polycarp now wants to count the number of times he will be forced to search for an episode using some different method.

TV series have $ n $ seasons (numbered $ 1 $ through $ n $ ), the $ i $ -th season has $ a_{i} $ episodes (numbered $ 1 $ through $ a_{i} $ ). Polycarp thinks that if for some pair of integers $ x $ and $ y $ ( $ x<y $ ) exist both season $ x $ episode $ y $ and season $ y $ episode $ x $ then one of these search queries will include the wrong results. Help Polycarp to calculate the number of such pairs!

## 输入格式

The first line contains one integer $ n $ $ (1<=n<=2·10^{5}) $ — the number of seasons.

The second line contains $ n $ integers separated by space $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=10^{9}) $ — number of episodes in each season.

## 输出格式

Print one integer — the number of pairs $ x $ and $ y $ ( $ x<y $ ) such that there exist both season $ x $ episode $ y $ and season $ y $ episode $ x $ .

## 说明/提示

Possible pairs in the second example:

1. $ x=1 $ , $ y=2 $ (season 1 episode 2 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF961E/6ef98cfc3df1e68639bb147759e3ed8244b80174.png) season 2 episode 1);
2. $ x=2 $ , $ y=3 $ (season 2 episode 3 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF961E/6ef98cfc3df1e68639bb147759e3ed8244b80174.png) season 3 episode 2);
3. $ x=1 $ , $ y=3 $ (season 1 episode 3 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF961E/6ef98cfc3df1e68639bb147759e3ed8244b80174.png) season 3 episode 1).

In the third example:

1. $ x=1 $ , $ y=2 $ (season 1 episode 2 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF961E/6ef98cfc3df1e68639bb147759e3ed8244b80174.png) season 2 episode 1);
2. $ x=1 $ , $ y=3 $ (season 1 episode 3 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF961E/6ef98cfc3df1e68639bb147759e3ed8244b80174.png) season 3 episode 1).

## 样例 #1

### 输入

```
5
1 2 3 4 5

```

### 输出

```
0

```

## 样例 #2

### 输入

```
3
8 12 7

```

### 输出

```
3

```

## 样例 #3

### 输入

```
3
3 2 1

```

### 输出

```
2

```



---

