---
title: "Recovering BST"
layout: "post"
diff: 省选/NOI-
pid: CF1025D
tag: ['搜索', '构造']
---

# Recovering BST

## 题目描述

Dima the hamster enjoys nibbling different things: cages, sticks, bad problemsetters and even trees!

Recently he found a binary search tree and instinctively nibbled all of its edges, hence messing up the vertices. Dima knows that if Andrew, who has been thoroughly assembling the tree for a long time, comes home and sees his creation demolished, he'll get extremely upset.

To not let that happen, Dima has to recover the binary search tree. Luckily, he noticed that any two vertices connected by a direct edge had their greatest common divisor value exceed $ 1 $ .

Help Dima construct such a binary search tree or determine that it's impossible. The definition and properties of a binary search tree can be found [here.](https://en.wikipedia.org/wiki/Binary_search_tree)

## 输入格式

The first line contains the number of vertices $ n $ ( $ 2 \le n \le 700 $ ).

The second line features $ n $ distinct integers $ a_i $ ( $ 2 \le a_i \le 10^9 $ ) — the values of vertices in ascending order.

## 输出格式

If it is possible to reassemble the binary search tree, such that the greatest common divisor of any two vertices connected by the edge is greater than $ 1 $ , print "Yes" (quotes for clarity).

Otherwise, print "No" (quotes for clarity).

## 说明/提示

The picture below illustrates one of the possible trees for the first example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1025D/a6281ebfc3addc046e3a216e978640a7d00d938f.png)The picture below illustrates one of the possible trees for the third example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1025D/422d22e6560dde35033dafdd73125c60e4d294d8.png)

## 样例 #1

### 输入

```
6
3 6 9 18 36 108

```

### 输出

```
Yes

```

## 样例 #2

### 输入

```
2
7 17

```

### 输出

```
No

```

## 样例 #3

### 输入

```
9
4 8 10 12 15 18 33 44 81

```

### 输出

```
Yes

```



---

---
title: "Crime Management"
layout: "post"
diff: 省选/NOI-
pid: CF107D
tag: ['字符串', '深度优先搜索 DFS', '概率论']
---

# Crime Management

## 题目描述

Zeyad 想要在埃及犯下 $n$ 起罪行，并且不受惩罚。罪行有几种类型。例如，贿赂是一种罪行，但如果重复两次，它就不被视为犯罪。因此，贿赂在重复偶数次时不被视为犯罪。超速也是一种罪行，但如果其重复的次数是 5 的倍数，它也不被视为犯罪。

更具体地说，已知有 $c$ 条关于罪行重复的条件。每个条件描述了罪行的类型 $t_{i}$ 及其重复的次数限制 $m_{i}$ 。如果 Zeyad 犯下的罪行 $t_{i}$ 的次数是 $m_{i}$ 的倍数，则 Zeyad 不会因为该罪行而受到惩罚。如果某种罪行出现多次，满足其中任意一个条件即可不受惩罚。当然，如果某罪行的次数为零，Zeyad 对该罪行无罪。

现在，Zeyad 想知道有多少种方式可以精确犯下 $n$ 起罪行且不受惩罚。

罪行的顺序是重要的。更正式地说，犯下 $n$ 起罪行的两种方式（序列 $w1$ 和 $w2$ ）如果对所有 $1 \leq i \leq n$ ，$w1_{i} = w2_{i}$ ，那么它们是相同的方式。

## 输入格式

第一行包含两个整数 $n$ 和 $c$ ($0 \leq n \leq 10^{18}, 0 \leq c \leq 1000$) —— Zeyad 想要犯下的罪行数量和他知道的条件数量。

接下来是 $c$ 条条件的定义。有 $26$ 种类型的罪行。每个罪行的定义由罪行类型（一个大写拉丁字母）和其重复次数的限制组成。

每个罪行的重复次数限制是一个正整数，并且所有限制的乘积不超过 $123$ 。输入中可能有重复的条件。

若某罪行的重复次数限制为 $1$ ，无论犯多少次都不会受到惩罚。法律的严格性由其非强制性来弥补。

显然，如果某罪行未在条件集中列出，那么 Zeyad 不会考虑它，因为犯下它不可避免地会受到惩罚。

请不要在 C++ 中使用 %lld 格式符来读写 64 位整数，建议使用 cin 流（你也可以使用 %I64d 格式符）。

## 输出格式

输出精确犯下 $n$ 起罪行且不受惩罚的不同方式数量，结果对 $12345$ 取模。

## 说明/提示

在第一个测试用例中，16 种方式是：AAAAA，AAABB，AABAB，AABBA，ABAAB，ABABA，ABBAA，BAAAB，BAABA，BABAA，BBAAA，ABBBB，BABBB，BBABB，BBBAB，BBBBA。

## 样例 #1

### 输入

```
5 2
A 1
B 2

```

### 输出

```
16

```

## 样例 #2

### 输入

```
6 3
A 1
B 2
C 3

```

### 输出

```
113

```

## 样例 #3

### 输入

```
8 3
A 2
A 3
B 2

```

### 输出

```
128

```



---

---
title: "Unordered Swaps"
layout: "post"
diff: 省选/NOI-
pid: CF1682E
tag: ['深度优先搜索 DFS']
---

# Unordered Swaps

## 题目描述

Alice had a permutation $ p $ of numbers from $ 1 $ to $ n $ . Alice can swap a pair $ (x, y) $ which means swapping elements at positions $ x $ and $ y $ in $ p $ (i.e. swap $ p_x $ and $ p_y $ ). Alice recently learned her first sorting algorithm, so she decided to sort her permutation in the minimum number of swaps possible. She wrote down all the swaps in the order in which she performed them to sort the permutation on a piece of paper.

For example,

- $ [(2, 3), (1, 3)] $ is a valid swap sequence by Alice for permutation $ p = [3, 1, 2] $ whereas $ [(1, 3), (2, 3)] $ is not because it doesn't sort the permutation. Note that we cannot sort the permutation in less than $ 2 $ swaps.
- $ [(1, 2), (2, 3), (2, 4), (2, 3)] $ cannot be a sequence of swaps by Alice for $ p = [2, 1, 4, 3] $ even if it sorts the permutation because $ p $ can be sorted in $ 2 $ swaps, for example using the sequence $ [(4, 3), (1, 2)] $ .

Unfortunately, Bob shuffled the sequence of swaps written by Alice.

You are given Alice's permutation $ p $ and the swaps performed by Alice in arbitrary order. Can you restore the correct sequence of swaps that sorts the permutation $ p $ ? Since Alice wrote correct swaps before Bob shuffled them up, it is guaranteed that there exists some order of swaps that sorts the permutation.

## 输入格式

The first line contains $ 2 $ integers $ n $ and $ m $ $ (2 \le n \le 2 \cdot 10^5, 1 \le m \le n - 1) $ — the size of permutation and the minimum number of swaps required to sort the permutation.

The next line contains $ n $ integers $ p_1, p_2, ..., p_n $ ( $ 1 \le p_i \le n $ , all $ p_i $ are distinct) — the elements of $ p $ . It is guaranteed that $ p $ forms a permutation.

Then $ m $ lines follow. The $ i $ -th of the next $ m $ lines contains two integers $ x_i $ and $ y_i $ — the $ i $ -th swap $ (x_i, y_i) $ .

It is guaranteed that it is possible to sort $ p $ with these $ m $ swaps and that there is no way to sort $ p $ with less than $ m $ swaps.

## 输出格式

Print a permutation of $ m $ integers — a valid order of swaps written by Alice that sorts the permutation $ p $ . See sample explanation for better understanding.

In case of multiple possible answers, output any.

## 说明/提示

In the first example, $ p = [2, 3, 4, 1] $ , $ m = 3 $ and given swaps are $ [(1, 4), (2, 1), (1, 3)] $ .

There is only one correct order of swaps i.e $ [2, 3, 1] $ .

1. First we perform the swap $ 2 $ from the input i.e $ (2, 1) $ , $ p $ becomes $ [3, 2, 4, 1] $ .
2. Then we perform the swap $ 3 $ from the input i.e $ (1, 3) $ , $ p $ becomes $ [4, 2, 3, 1] $ .
3. Finally we perform the swap $ 1 $ from the input i.e $ (1, 4) $ and $ p $ becomes $ [1, 2, 3, 4] $ which is sorted.

In the second example, $ p = [6, 5, 1, 3, 2, 4] $ , $ m = 4 $ and the given swaps are $ [(3, 1), (2, 5), (6, 3), (6, 4)] $ .

One possible correct order of swaps is $ [4, 2, 1, 3] $ .

1. Perform the swap $ 4 $ from the input i.e $ (6, 4) $ , $ p $ becomes $ [6, 5, 1, 4, 2, 3] $ .
2. Perform the swap $ 2 $ from the input i.e $ (2, 5) $ , $ p $ becomes $ [6, 2, 1, 4, 5, 3] $ .
3. Perform the swap $ 1 $ from the input i.e $ (3, 1) $ , $ p $ becomes $ [1, 2, 6, 4, 5, 3] $ .
4. Perform the swap $ 3 $ from the input i.e $ (6, 3) $ and $ p $ becomes $ [1, 2, 3, 4, 5, 6] $ which is sorted.

There can be other possible answers such as $ [1, 2, 4, 3] $ .

## 样例 #1

### 输入

```
4 3
2 3 4 1
1 4
2 1
1 3
```

### 输出

```
2 3 1
```

## 样例 #2

### 输入

```
6 4
6 5 1 3 2 4
3 1
2 5
6 3
6 4
```

### 输出

```
4 1 3 2
```



---

---
title: "Sanae and Giant Robot"
layout: "post"
diff: 省选/NOI-
pid: CF1687C
tag: ['并查集', '广度优先搜索 BFS']
---

# Sanae and Giant Robot

## 题目描述

> 果然是那个吗！因为其实用性而无法被实现的！只能出现于憧憬中的，二足步行巨大机器人！——东风谷早苗，《东方非想天则》

早苗制造了一台巨大的机器人——非想天则，但是这个机器人出了一些故障。更糟糕的是，早苗不知道如何将其停止运行，因而早苗只能在机器人运行的时候对其修复。

非想天则的状态可以用一个正整数数列 $n$ 来表示。非想天则现在处于状态 $a_1,a_2,\dots a_n$，而早苗希望将其变为 $b_1,b_2,\dots,b_n$。

作为一位优秀的女子高中生，早苗非常了解复制粘贴的艺术。她有 $m$ 个可供选择的区间，在每一次操作中，早苗可以把序列 $b$ 中的一个可选择的区间对应位置地复制粘贴到序列 $a$ 中，前提是要求序列 $a$ 的每个数字的总和不变。形式化地来讲，早苗可以选择一个区间 $[l,r]$，执行操作 $a_i \leftarrow b_i (l \leq i \leq r)$，当且仅当 $\sum \limits_{i=1}^n a_i$ 不变。

请你判断早苗能否通过若干次这样的操作，将非想天则的状态由序列 $a$ 转化为序列 $b$。

## 输入格式

第一行输入一个正整数 $t(1 \leq t \leq 2 \times 10^4)$，表示输入数据组数。   
对于每组数据，首先输入两个正整数 $n,m(2 \leq n \leq 2 \times 10^5,1 \leq m \leq 10^5)$，分别表示数列 $a,b$ 的长度和可以操作的区间个数。        
第二行输入 $n$ 个正整数 $a_i(1 \leq a_i \leq 10^9)$，表示非想天则的状态。     
第三行输入 $n$ 个正整数 $b_i(1 \leq b_i \leq 10^9)$，表示早苗希望非想天则变成的状态。      
接下来输入 $m$ 行，每行两个正整数 $l,r(1 \leq l < r \leq n)$，表示早苗可以进行操作的区间。     
数据保证，$\sum n,\sum m \leq 2 \times 10^5$。

## 输出格式

如果早苗可以将数列 $a$ 转化为数列 $b$，则输出 `YES`，否则输出 `NO`，不区分大小写。

## 样例 #1

### 输入

```
2
5 2
1 5 4 2 3
3 2 5 4 1
1 3
2 5
5 2
1 5 4 2 3
3 2 4 5 1
1 2
2 4
```

### 输出

```
YES
NO
```



---

---
title: "Algebra Flash"
layout: "post"
diff: 省选/NOI-
pid: CF1767E
tag: ['状态合并', '图论建模', '快速沃尔什变换 FWT', '折半搜索 meet in the middle']
---

# Algebra Flash

## 题目描述

### 题目背景

Algebra Flash 2.2 刚刚发布！

更新日志：

- 全新游戏模式！

感谢您一直以来对游戏的支持！

就这？你略带失望地启动游戏，点进新的游戏模式，上面写着 "彩色平台"。


有 $n$ 个平台排成一列，编号从 $1$ 到 $n$。平台有 $m$ 种颜色，编号从 $1$ 到 $m$。第 $i$ 个平台的颜色是 $c_i$。

你从 $1$ 号平台开始，想要跳到 $n$ 号平台。在一次移动中，你可以从某个平台 $i$ 跳到平台 $i + 1$ 或 $i + 2$。

所有平台最初都未激活（包括平台 $1$ 和 $n$）。对于每种颜色 $j$，你可以支付 $x_j$ 枚金币来激活所有颜色为 $j$ 的平台。

你希望激活一些平台，然后从已激活的平台 $1$ 开始，跳过一些已激活的平台，到达已激活的平台 $n$。

要实现这个目标，你最少花费多少金币？

## 输入格式

第一行两个整数 $n$ 和 $m$（$2 \le n \le 3 \times 10^5$ ; $1 \le m \le 40$），分别表示平台数和颜色数。

第二行 $n$ 个整数 $c_1, c_2, \dots, c_n$（$1 \le c_i \le m$）表示平台的颜色。

第三行 $m$ 个整数 $x_1, x_2, \dots, x_m$（$1 \le x_i \le 10^7$）表示激活每种颜色的所有平台花费的金币数量。

## 输出格式

一行一个整数，表示从激活的平台 $1$ 开始，跳过一些激活的平台，到达激活的平台 $n$ 需要花费的最小金币数量。

Translated by UID 781046.

## 样例 #1

### 输入

```
5 3
1 3 2 3 1
1 10 100
```

### 输出

```
11
```

## 样例 #2

### 输入

```
5 3
1 3 2 3 1
1 200 20
```

### 输出

```
21
```

## 样例 #3

### 输入

```
4 2
2 2 1 1
5 5
```

### 输出

```
10
```

## 样例 #4

### 输入

```
10 10
3 8 6 2 10 5 2 3 7 3
9 7 4 2 1 8 2 6 2 2
```

### 输出

```
15
```



---

---
title: "Numbers"
layout: "post"
diff: 省选/NOI-
pid: CF241D
tag: ['搜索']
---

# Numbers

## 题目描述

You have a sequence of $ n $ distinct integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=n) $ . You want to remove some integers in such a way that the resulting sequence of integers satisfies the following three conditions:

1. the resulting sequence is not empty;
2. the exclusive or ( $ xor $ operation) of all the integers in the resulting sequence equals $ 0 $ ;
3. if you write all the integers of the resulting sequence (from beginning to the end) in a row in the decimal numeral system and without any spaces, the written number is divisible by $ p $ .

You are given the sequence of $ n $ integers $ a $ and a prime number $ p $ , find a way to satisfy the described conditions.

## 输入格式

The first line of the input contains two integers $ n $ and $ p $ $ (1<=n,p<=50000) $ . Next line contains $ n $ space-separated distinct integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=n) $ .

It is guaranteed that $ p $ is a prime number.

## 输出格式

If there is no solution for the given input, print "No" (without quotes) in the only line of the output.

Otherwise print "Yes" in the first line of output. The second line should contain an integer $ k $ $ (k&gt;0) $ specifying the number of remaining elements and the third line should contain $ k $ distinct integers $ x_{1},x_{2},...,x_{k} $ $ (1<=x_{i}<=n) $ . These integers mean that you should remove all integers from the sequence except integers $ a_{x1},a_{x2},...,a_{xk} $ to satisfy the described conditions.

If there are multiple solutions, any of them will be accepted.

## 样例 #1

### 输入

```
3 3
1 2 3

```

### 输出

```
Yes
3
1 2 3 

```

## 样例 #2

### 输入

```
3 5
1 2 3

```

### 输出

```
No

```



---

---
title: "Colorado Potato Beetle"
layout: "post"
diff: 省选/NOI-
pid: CF243C
tag: ['搜索', '离散化', '广度优先搜索 BFS']
---

# Colorado Potato Beetle

## 题目描述

Old MacDonald has a farm and a large potato field, $ (10^{10}+1)×(10^{10}+1) $ square meters in size. The field is divided into square garden beds, each bed takes up one square meter.

Old McDonald knows that the Colorado potato beetle is about to invade his farm and can destroy the entire harvest. To fight the insects, Old McDonald wants to spray some beds with insecticides.

So Old McDonald went to the field, stood at the center of the central field bed and sprayed this bed with insecticides. Now he's going to make a series of movements and spray a few more beds. During each movement Old McDonald moves left, right, up or down the field some integer number of meters. As Old McDonald moves, he sprays all the beds he steps on. In other words, the beds that have any intersection at all with Old McDonald's trajectory, are sprayed with insecticides.

When Old McDonald finished spraying, he wrote out all his movements on a piece of paper. Now he wants to know how many beds won't be infected after the invasion of the Colorado beetles.

It is known that the invasion of the Colorado beetles goes as follows. First some bed on the field border gets infected. Than any bed that hasn't been infected, hasn't been sprayed with insecticides and has a common side with an infected bed, gets infected as well. Help Old McDonald and determine the number of beds that won't be infected by the Colorado potato beetle.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=1000 $ ) — the number of Old McDonald's movements.

Next $ n $ lines contain the description of Old McDonald's movements. The $ i $ -th of these lines describes the $ i $ -th movement. Each movement is given in the format " $ d_{i} $ $ x_{i} $ ", where $ d_{i} $ is the character that determines the direction of the movement ("L", "R", "U" or "D" for directions "left", "right", "up" and "down", correspondingly), and $ x_{i} $ ( $ 1<=x_{i}<=10^{6} $ ) is an integer that determines the number of meters in the movement.

## 输出格式

Print a single integer — the number of beds that won't be infected by the Colorado potato beetle.

Please do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 样例 #1

### 输入

```
5
R 8
U 9
L 9
D 8
L 2

```

### 输出

```
101
```

## 样例 #2

### 输入

```
7
R 10
D 2
L 7
U 9
D 2
R 3
D 10

```

### 输出

```
52
```



---

---
title: "Distinct Paths"
layout: "post"
diff: 省选/NOI-
pid: CF293B
tag: ['搜索', '剪枝', '状态合并']
---

# Distinct Paths

## 题目描述

You have a rectangular $ n×m $ -cell board. Some cells are already painted some of $ k $ colors. You need to paint each uncolored cell one of the $ k $ colors so that any path from the upper left square to the lower right one doesn't contain any two cells of the same color. The path can go only along side-adjacent cells and can only go down or right.

Print the number of possible paintings modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 输入格式

The first line contains three integers $ n,m,k $ $ (1<=n,m<=1000,1<=k<=10) $ . The next $ n $ lines contain $ m $ integers each — the board. The first of them contains $ m $ uppermost cells of the board from the left to the right and the second one contains $ m $ cells from the second uppermost row and so on. If a number in a line equals 0, then the corresponding cell isn't painted. Otherwise, this number represents the initial color of the board cell — an integer from 1 to $ k $ .

Consider all colors numbered from 1 to $ k $ in some manner.

## 输出格式

Print the number of possible paintings modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 样例 #1

### 输入

```
2 2 4
0 0
0 0

```

### 输出

```
48

```

## 样例 #2

### 输入

```
2 2 4
1 2
2 1

```

### 输出

```
0

```

## 样例 #3

### 输入

```
5 6 10
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0

```

### 输出

```
3628800

```

## 样例 #4

### 输入

```
2 6 10
1 2 3 4 5 6
0 0 0 0 0 0

```

### 输出

```
4096

```



---

---
title: "Chess"
layout: "post"
diff: 省选/NOI-
pid: CF57E
tag: ['模拟', '搜索', '枚举']
---

# Chess

## 题目描述

Brian the Rabbit adores chess. Not long ago he argued with Stewie the Rabbit that a knight is better than a king. To prove his point he tries to show that the knight is very fast but Stewie doesn't accept statements without evidence. He constructed an infinite chessboard for Brian, where he deleted several squares to add some more interest to the game. Brian only needs to count how many different board squares a knight standing on a square with coordinates of $ (0,0) $ can reach in no more than $ k $ moves. Naturally, it is forbidden to move to the deleted squares.

Brian doesn't very much like exact sciences himself and is not acquainted with programming, that's why he will hardly be able to get ahead of Stewie who has already started solving the problem. Help Brian to solve the problem faster than Stewie.

## 输入格式

The first line contains two integers $ k $ and $ n $ ( $ 0<=k<=10^{18},0<=n<=440 $ ) which are correspondingly the maximal number of moves a knight can make and the number of deleted cells. Then follow $ n $ lines, each giving the coordinates of a deleted square in the form $ (x_{i},y_{i}) $ ( $ |x_{i}|<=10,|y_{i}|<=10 $ ). All the numbers are integer, the deleted squares are different and it is guaranteed that the square $ (0,0) $ is not deleted.

Please, do not use %lld specificator to read or write 64-bit integers in C++. It is preffered to use cin (also you may use %I64d).

## 输出格式

You must print the answer on a single line. As it can be rather long, you should print it modulo $ 1000000007 $ .

## 样例 #1

### 输入

```
1 0

```

### 输出

```
9

```

## 样例 #2

### 输入

```
2 7
-1 2
1 2
2 1
2 -1
1 -2
-1 -2
-2 -1

```

### 输出

```
9

```



---

---
title: "Expression"
layout: "post"
diff: 省选/NOI-
pid: CF58E
tag: ['搜索', '剪枝']
---

# Expression

## 题目描述

One day Vasya was solving arithmetical problems. He wrote down an expression $ a+b=c $ in his notebook. When the teacher checked Vasya's work it turned out that Vasya had solved the problem incorrectly. Now Vasya tries to find excuses. He says that he simply forgot to write down several digits in numbers $ a $ , $ b $ and $ c $ , but he can't remember what numbers they actually were. Help Vasya, find such numbers $ x $ , $ y $ and $ z $ , with which the following conditions are met:

- $ x+y=z $ ,
- from the expression $ x+y=z $ several digits can be erased in such a way that the result will be $ a+b=c $ ,
- the expression $ x+y=z $ should have the minimal length.

## 输入格式

The first and only input line contains the expression $ a+b=c $ ( $ 1<=a,b,c<=10^{6} $ , $ a $ , $ b $ and $ c $ don't contain leading zeroes) which is the expression Vasya wrote down.

## 输出格式

Print the correct expression $ x+y=z $ ( $ x $ , $ y $ and $ z $ are non-negative numbers without leading zeroes). The expression $ a+b=c $ must be met in $ x+y=z $ as a subsequence. The printed solution should have the minimal possible number of characters. If there are several such solutions, you can print any of them.

## 样例 #1

### 输入

```
2+4=5

```

### 输出

```
21+4=25

```

## 样例 #2

### 输入

```
1+1=3

```

### 输出

```
1+31=32

```

## 样例 #3

### 输入

```
1+1=2

```

### 输出

```
1+1=2

```



---

---
title: "Lomsat gelral"
layout: "post"
diff: 省选/NOI-
pid: CF600E
tag: ['搜索', '线段树', '树上启发式合并', '搜索']
---

# Lomsat gelral

## 题目描述

You are given a rooted tree with root in vertex $ 1 $ . Each vertex is coloured in some colour.

Let's call colour $ c $ dominating in the subtree of vertex $ v $ if there are no other colours that appear in the subtree of vertex $ v $ more times than colour $ c $ . So it's possible that two or more colours will be dominating in the subtree of some vertex.

The subtree of vertex $ v $ is the vertex $ v $ and all other vertices that contains vertex $ v $ in each path to the root.

For each vertex $ v $ find the sum of all dominating colours in the subtree of vertex $ v $ .

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of vertices in the tree.

The second line contains $ n $ integers $ c_{i} $ ( $ 1<=c_{i}<=n $ ), $ c_{i} $ — the colour of the $ i $ -th vertex.

Each of the next $ n-1 $ lines contains two integers $ x_{j},y_{j} $ ( $ 1<=x_{j},y_{j}<=n $ ) — the edge of the tree. The first vertex is the root of the tree.

## 输出格式

Print $ n $ integers — the sums of dominating colours for each vertex.

## 样例 #1

### 输入

```
4
1 2 3 4
1 2
2 3
2 4

```

### 输出

```
10 9 3 4

```

## 样例 #2

### 输入

```
15
1 2 3 1 2 3 3 1 1 3 2 2 1 2 3
1 2
1 3
1 4
1 14
1 15
2 5
2 6
2 7
3 8
3 9
3 10
4 11
4 12
4 13

```

### 输出

```
6 5 4 3 2 3 3 1 1 3 2 2 1 2 3

```



---

---
title: "Preorder Test"
layout: "post"
diff: 省选/NOI-
pid: CF627D
tag: ['二分', '深度优先搜索 DFS']
---

# Preorder Test

## 题目描述

For his computer science class, Jacob builds a model tree with sticks and balls containing $ n $ nodes in the shape of a tree. Jacob has spent $ a_{i} $ minutes building the $ i $ -th ball in the tree.

Jacob's teacher will evaluate his model and grade Jacob based on the effort he has put in. However, she does not have enough time to search his whole tree to determine this; Jacob knows that she will examine the first $ k $ nodes in a DFS-order traversal of the tree. She will then assign Jacob a grade equal to the minimum $ a_{i} $ she finds among those $ k $ nodes.

Though Jacob does not have enough time to rebuild his model, he can choose the root node that his teacher starts from. Furthermore, he can rearrange the list of neighbors of each node in any order he likes. Help Jacob find the best grade he can get on this assignment.

A DFS-order traversal is an ordering of the nodes of a rooted tree, built by a recursive DFS-procedure initially called on the root of the tree. When called on a given node $ v $ , the procedure does the following:

1. Print $ v $ .
2. Traverse the list of neighbors of the node $ v $ in order and iteratively call DFS-procedure on each one. Do not call DFS-procedure on node $ u $ if you came to node $ v $ directly from $ u $ .

## 输入格式

The first line of the input contains two positive integers, $ n $ and $ k $ ( $ 2<=n<=200000 $ , $ 1<=k<=n $ ) — the number of balls in Jacob's tree and the number of balls the teacher will inspect.

The second line contains $ n $ integers, $ a_{i} $ ( $ 1<=a_{i}<=1000000 $ ), the time Jacob used to build the $ i $ -th ball.

Each of the next $ n-1 $ lines contains two integers $ u_{i} $ , $ v_{i} $ ( $ 1<=u_{i},v_{i}<=n $ , $ u_{i}≠v_{i} $ ) representing a connection in Jacob's tree between balls $ u_{i} $ and $ v_{i} $ .

## 输出格式

Print a single integer — the maximum grade Jacob can get by picking the right root of the tree and rearranging the list of neighbors.

## 说明/提示

In the first sample, Jacob can root the tree at node $ 2 $ and order $ 2 $ 's neighbors in the order $ 4 $ , $ 1 $ , $ 5 $ (all other nodes have at most two neighbors). The resulting preorder traversal is $ 2 $ , $ 4 $ , $ 1 $ , $ 3 $ , $ 5 $ , and the minimum $ a_{i} $ of the first $ 3 $ nodes is $ 3 $ .

In the second sample, it is clear that any preorder traversal will contain node $ 1 $ as either its first or second node, so Jacob cannot do better than a grade of $ 1 $ .

## 样例 #1

### 输入

```
5 3
3 6 1 4 2
1 2
2 4
2 5
1 3

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4 2
1 5 5 5
1 2
1 3
1 4

```

### 输出

```
1

```



---

---
title: "The Chocolate Spree"
layout: "post"
diff: 省选/NOI-
pid: CF633F
tag: ['动态规划 DP', '枚举', '深度优先搜索 DFS']
---

# The Chocolate Spree

## 题目描述

Alice and Bob have a tree (undirected acyclic connected graph). There are $ a_{i} $ chocolates waiting to be picked up in the $ i $ -th vertex of the tree. First, they choose two different vertices as their starting positions (Alice chooses first) and take all the chocolates contained in them.

Then, they alternate their moves, selecting one vertex at a time and collecting all chocolates from this node. To make things more interesting, they decided that one can select a vertex only if he/she selected a vertex adjacent to that one at his/her previous turn and this vertex has not been already chosen by any of them during other move.

If at any moment one of them is not able to select the node that satisfy all the rules, he/she will skip his turns and let the other person pick chocolates as long as he/she can. This goes on until both of them cannot pick chocolates any further.

Due to their greed for chocolates, they want to collect as many chocolates as possible. However, as they are friends they only care about the total number of chocolates they obtain together. What is the maximum total number of chocolates they may pick?

## 输入格式

The first line of the input contains the single integer $ n $ ( $ 2<= $ n $ <=100000 $ ) — the number of vertices in the tree.

The second line contains $ n $ integers $ a_{i} $ ( $ 1<=a_{i}<=10^{9} $ ), $ i $ -th of these numbers stands for the number of chocolates stored at the node $ i $ .

Then follow $ n-1 $ lines that describe the tree. Each of them contains two integers $ u_{i} $ and $ v_{i} $ ( $ 1<=u_{i},v_{i}<=n $ ) — indices of vertices connected by the $ i $ -th edge.

## 输出格式

Print the number of chocolates Alice and Bob can collect together if they behave optimally.

## 说明/提示

In the first sample, Alice may start at the vertex $ 9 $ and Bob at vertex $ 8 $ . Alice will select vertex $ 1 $ and Bob has no options now. Alice selects the vertex $ 7 $ and they both stop.

In the second sample, both of them will pick either of the nodes alternately.

## 样例 #1

### 输入

```
9
1 2 3 4 5 6 7 8 9
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9

```

### 输出

```
25

```

## 样例 #2

### 输入

```
2
20 10
1 2

```

### 输出

```
30

```



---

---
title: "Bear and Square Grid"
layout: "post"
diff: 省选/NOI-
pid: CF679C
tag: ['字符串', '搜索', '连通块']
---

# Bear and Square Grid

## 题目描述

You have a grid with $ n $ rows and $ n $ columns. Each cell is either empty (denoted by '.') or blocked (denoted by 'X').

Two empty cells are directly connected if they share a side. Two cells $ (r_{1},c_{1}) $ (located in the row $ r_{1} $ and column $ c_{1} $ ) and $ (r_{2},c_{2}) $ are connected if there exists a sequence of empty cells that starts with $ (r_{1},c_{1}) $ , finishes with $ (r_{2},c_{2}) $ , and any two consecutive cells in this sequence are directly connected. A connected component is a set of empty cells such that any two cells in the component are connected, and there is no cell in this set that is connected to some cell not in this set.

Your friend Limak is a big grizzly bear. He is able to destroy any obstacles in some range. More precisely, you can choose a square of size $ k×k $ in the grid and Limak will transform all blocked cells there to empty ones. However, you can ask Limak to help only once.

The chosen square must be completely inside the grid. It's possible that Limak won't change anything because all cells are empty anyway.

You like big connected components. After Limak helps you, what is the maximum possible size of the biggest connected component in the grid?

## 输入格式

The first line of the input contains two integers $ n $ and $ k $ ( $ 1<=k<=n<=500 $ ) — the size of the grid and Limak's range, respectively.

Each of the next $ n $ lines contains a string with $ n $ characters, denoting the $ i $ -th row of the grid. Each character is '.' or 'X', denoting an empty cell or a blocked one, respectively.

## 输出格式

Print the maximum possible size (the number of cells) of the biggest connected component, after using Limak's help.

## 说明/提示

In the first sample, you can choose a square of size $ 2×2 $ . It's optimal to choose a square in the red frame on the left drawing below. Then, you will get a connected component with $ 10 $ cells, marked blue in the right drawing.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF679C/73f9f2e0fd56d2fb7f7f3062a32953f02d9af103.png)

## 样例 #1

### 输入

```
5 2
..XXX
XX.XX
X.XXX
X...X
XXXX.

```

### 输出

```
10

```

## 样例 #2

### 输入

```
5 3
.....
.XXX.
.XXX.
.XXX.
.....

```

### 输出

```
25

```



---

---
title: "Best Edge Weight"
layout: "post"
diff: 省选/NOI-
pid: CF827D
tag: ['深度优先搜索 DFS', '生成树', '动态树 LCT']
---

# Best Edge Weight

## 题目描述

You are given a connected weighted graph with $ n $ vertices and $ m $ edges. The graph doesn't contain loops nor multiple edges. Consider some edge with id $ i $ . Let's determine for this edge the maximum integer weight we can give to it so that it is contained in all minimum spanning trees of the graph if we don't change the other weights.

You are to determine this maximum weight described above for each edge. You should calculate the answer for each edge independently, it means there can't be two edges with changed weights at the same time.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2<=n<=2·10^{5} $ , $ n-1<=m<=2·10^{5} $ ), where $ n $ and $ m $ are the number of vertices and the number of edges in the graph, respectively.

Each of the next $ m $ lines contains three integers $ u $ , $ v $ and $ c $ ( $ 1<=v,u<=n $ , $ v≠u $ , $ 1<=c<=10^{9} $ ) meaning that there is an edge between vertices $ u $ and $ v $ with weight $ c $ .

## 输出格式

Print the answer for each edge in the order the edges are given in the input. If an edge is contained in every minimum spanning tree with any weight, print -1 as the answer.

## 样例 #1

### 输入

```
4 4
1 2 2
2 3 2
3 4 2
4 1 3

```

### 输出

```
2 2 2 1 
```

## 样例 #2

### 输入

```
4 3
1 2 2
2 3 2
3 4 2

```

### 输出

```
-1 -1 -1 
```



---

---
title: "Xor-MST"
layout: "post"
diff: 省选/NOI-
pid: CF888G
tag: ['深度优先搜索 DFS', '生成树', '进制']
---

# Xor-MST

## 题目描述

You are given a complete undirected graph with $ n $ vertices. A number $ a_{i} $ is assigned to each vertex, and the weight of an edge between vertices $ i $ and $ j $ is equal to $ a_{i}xora_{j} $ .

Calculate the weight of the minimum spanning tree in this graph.

## 输入格式

The first line contains $ n $ ( $ 1<=n<=200000 $ ) — the number of vertices in the graph.

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 0<=a_{i}<2^{30} $ ) — the numbers assigned to the vertices.

## 输出格式

Print one number — the weight of the minimum spanning tree in the graph.

## 样例 #1

### 输入

```
5
1 2 3 4 5

```

### 输出

```
8

```

## 样例 #2

### 输入

```
4
1 2 3 4

```

### 输出

```
8

```



---

---
title: "Prime Gift"
layout: "post"
diff: 省选/NOI-
pid: CF912E
tag: ['搜索', '二分', '素数判断,质数,筛法']
---

# Prime Gift

## 题目描述

Opposite to Grisha's nice behavior, Oleg, though he has an entire year at his disposal, didn't manage to learn how to solve number theory problems in the past year. That's why instead of Ded Moroz he was visited by his teammate Andrew, who solemnly presented him with a set of $ n $ distinct prime numbers alongside with a simple task: Oleg is to find the $ k $ -th smallest integer, such that all its prime divisors are in this set.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=16 $ ).

The next line lists $ n $ distinct prime numbers $ p_{1},p_{2},...,p_{n} $ ( $ 2<=p_{i}<=100 $ ) in ascending order.

The last line gives a single integer $ k $ ( $ 1<=k $ ). It is guaranteed that the $ k $ -th smallest integer such that all its prime divisors are in this set does not exceed $ 10^{18} $ .

## 输出格式

Print a single line featuring the $ k $ -th smallest integer. It's guaranteed that the answer doesn't exceed $ 10^{18} $ .

## 说明/提示

The list of numbers with all prime divisors inside $ {2,3,5} $ begins as follows:

 $ (1,2,3,4,5,6,8,...) $

The seventh number in this list ( $ 1 $ -indexed) is eight.

## 样例 #1

### 输入

```
3
2 3 5
7

```

### 输出

```
8

```

## 样例 #2

### 输入

```
5
3 7 11 13 31
17

```

### 输出

```
93

```



---

---
title: "Simple Cycles Edges"
layout: "post"
diff: 省选/NOI-
pid: CF962F
tag: ['搜索', '枚举', '差分']
---

# Simple Cycles Edges

## 题目描述

You are given an undirected graph, consisting of $ n $ vertices and $ m $ edges. The graph does not necessarily connected. Guaranteed, that the graph does not contain multiple edges (more than one edges between a pair of vertices) or loops (edges from a vertex to itself).

A cycle in a graph is called a simple, if it contains each own vertex exactly once. So simple cycle doesn't allow to visit a vertex more than once in a cycle.

Determine the edges, which belong to exactly on one simple cycle.

## 输入格式

The first line contain two integers $ n $ and $ m $ $ (1 \le n \le 100\,000 $ , $ 0 \le m \le \min(n \cdot (n - 1) / 2, 100\,000)) $ — the number of vertices and the number of edges.

Each of the following $ m $ lines contain two integers $ u $ and $ v $ ( $ 1 \le u, v \le n $ , $ u \neq v $ ) — the description of the edges.

## 输出格式

In the first line print the number of edges, which belong to exactly one simple cycle.

In the second line print the indices of edges, which belong to exactly one simple cycle, in increasing order. The edges are numbered from one in the same order as they are given in the input.

## 样例 #1

### 输入

```
3 3
1 2
2 3
3 1

```

### 输出

```
3
1 2 3 

```

## 样例 #2

### 输入

```
6 7
2 3
3 4
4 2
1 2
1 5
5 6
6 1

```

### 输出

```
6
1 2 3 5 6 7 

```

## 样例 #3

### 输入

```
5 6
1 2
2 3
2 4
4 3
2 5
5 3

```

### 输出

```
0


```



---

---
title: "NN country"
layout: "post"
diff: 省选/NOI-
pid: CF983E
tag: ['倍增', '深度优先搜索 DFS', '最近公共祖先 LCA']
---

# NN country

## 题目描述

In the NN country, there are $ n $ cities, numbered from $ 1 $ to $ n $ , and $ n - 1 $ roads, connecting them. There is a roads path between any two cities.

There are $ m $ bidirectional bus routes between cities. Buses drive between two cities taking the shortest path with stops in every city they drive through. Travelling by bus, you can travel from any stop on the route to any other. You can travel between cities only by bus.

You are interested in $ q $ questions: is it possible to get from one city to another and what is the minimum number of buses you need to use for it?

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of cities.

The second line contains $ n - 1 $ integers $ p_2, p_3, \ldots, p_n $ ( $ 1 \le p_i < i $ ), where $ p_i $ means that cities $ p_i $ and $ i $ are connected by road.

The third line contains a single integer $ m $ ( $ 1 \le m \le 2 \cdot 10^5 $ ) — the number of bus routes.

Each of the next $ m $ lines contains $ 2 $ integers $ a $ and $ b $ ( $ 1 \le a, b \le n $ , $ a \neq b $ ), meaning that there is a bus route between cities $ a $ and $ b $ . It is possible that there is more than one route between two cities.

The next line contains a single integer $ q $ ( $ 1 \le q \le 2 \cdot 10^5 $ ) — the number of questions you are interested in.

Each of the next $ q $ lines contains $ 2 $ integers $ v $ and $ u $ ( $ 1 \le v, u \le n $ , $ v \neq u $ ), meaning that you are interested if it is possible to get from city $ v $ to city $ u $ and what is the minimum number of buses you need to use for it.

## 输出格式

Print the answer for each question on a separate line. If there is no way to get from one city to another, print $ -1 $ . Otherwise print the minimum number of buses you have to use.

## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF983E/c42b59e68a69956240c890e5363c8c983d1d430c.png) Routes for first sample are marked on the picture.

## 样例 #1

### 输入

```
7
1 1 1 4 5 6
4
4 2
5 4
1 3
6 7
6
4 5
3 5
7 2
4 5
3 2
5 3

```

### 输出

```
1
3
-1
1
2
3

```

## 样例 #2

### 输入

```
7
1 1 2 3 4 1
4
4 7
3 5
7 6
7 6
6
4 6
3 1
3 2
2 7
6 3
5 3

```

### 输出

```
1
-1
-1
1
-1
1

```



---

---
title: "AND Graph"
layout: "post"
diff: 省选/NOI-
pid: CF986C
tag: ['广度优先搜索 BFS', '深度优先搜索 DFS', '位运算']
---

# AND Graph

## 题目描述

给定一个 $m$ 个整数的集合，每个整数在 $0$ 到 $2^n-1$ 之间，以每一个整数作为顶点建无向图，当两个点 $x$ 和 $y$ 做与运算值为 $0$ 时，则认为 $x$ 和 $y$ 是连通的，即 $x$ 和 $y$ 之间有一条无向边。请求出图中连通块的个数。

## 输入格式

第一行输入两个整数 $n$ 和 $m$（$0 \leq  n\leq22$，$1 \leq  m\leq2^n$）。  
第二行输入 $m$ 个整数，即集合里的元素。

## 输出格式

一个整数，表示图中连通块的个数。

## 样例 #1

### 输入

```
2 3
1 2 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5 5
5 19 10 20 12

```

### 输出

```
2

```



---

