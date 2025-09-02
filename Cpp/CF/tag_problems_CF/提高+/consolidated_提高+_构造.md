---
title: "Border"
layout: "post"
diff: 提高+/省选-
pid: CF1010C
tag: ['最大公约数 gcd', '进制', '构造']
---

# Border

## 题目描述

Astronaut Natasha arrived on Mars. She knows that the Martians are very poor aliens. To ensure a better life for the Mars citizens, their emperor decided to take tax from every tourist who visited the planet. Natasha is the inhabitant of Earth, therefore she had to pay the tax to enter the territory of Mars.

There are $ n $ banknote denominations on Mars: the value of $ i $ -th banknote is $ a_i $ . Natasha has an infinite number of banknotes of each denomination.

Martians have $ k $ fingers on their hands, so they use a number system with base $ k $ . In addition, the Martians consider the digit $ d $ (in the number system with base $ k $ ) divine. Thus, if the last digit in Natasha's tax amount written in the number system with the base $ k $ is $ d $ , the Martians will be happy. Unfortunately, Natasha does not know the Martians' divine digit yet.

Determine for which values $ d $ Natasha can make the Martians happy.

Natasha can use only her banknotes. Martians don't give her change.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1 \le n \le 100\,000 $ , $ 2 \le k \le 100\,000 $ ) — the number of denominations of banknotes and the base of the number system on Mars.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — denominations of banknotes on Mars.

All numbers are given in decimal notation.

## 输出格式

On the first line output the number of values $ d $ for which Natasha can make the Martians happy.

In the second line, output all these values in increasing order.

Print all numbers in decimal notation.

## 说明/提示

Consider the first test case. It uses the octal number system.

If you take one banknote with the value of $ 12 $ , you will get $ 14_8 $ in octal system. The last digit is $ 4_8 $ .

If you take one banknote with the value of $ 12 $ and one banknote with the value of $ 20 $ , the total value will be $ 32 $ . In the octal system, it is $ 40_8 $ . The last digit is $ 0_8 $ .

If you take two banknotes with the value of $ 20 $ , the total value will be $ 40 $ , this is $ 50_8 $ in the octal system. The last digit is $ 0_8 $ .

No other digits other than $ 0_8 $ and $ 4_8 $ can be obtained. Digits $ 0_8 $ and $ 4_8 $ could also be obtained in other ways.

The second test case uses the decimal number system. The nominals of all banknotes end with zero, so Natasha can give the Martians only the amount whose decimal notation also ends with zero.

## 样例 #1

### 输入

```
2 8
12 20

```

### 输出

```
2
0 4 
```

## 样例 #2

### 输入

```
3 10
10 20 30

```

### 输出

```
1
0 
```



---

---
title: "Chemical table"
layout: "post"
diff: 提高+/省选-
pid: CF1012B
tag: ['并查集', '概率论', '构造']
---

# Chemical table

## 题目描述

Innopolis University scientists continue to investigate the periodic table. There are $ n·m $ known elements and they form a periodic table: a rectangle with $ n $ rows and $ m $ columns. Each element can be described by its coordinates $ (r,c) $ ( $ 1<=r<=n $ , $ 1<=c<=m $ ) in the table.

Recently scientists discovered that for every four different elements in this table that form a rectangle with sides parallel to the sides of the table, if they have samples of three of the four elements, they can produce a sample of the fourth element using nuclear fusion. So if we have elements in positions $ (r_{1},c_{1}) $ , $ (r_{1},c_{2}) $ , $ (r_{2},c_{1}) $ , where $ r_{1}≠r_{2} $ and $ c_{1}≠c_{2} $ , then we can produce element $ (r_{2},c_{2}) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1012B/a1ec2b34980f17dea8ef9d5c32f5d591ae712bba.png)Samples used in fusion are not wasted and can be used again in future fusions. Newly crafted elements also can be used in future fusions.

Innopolis University scientists already have samples of $ q $ elements. They want to obtain samples of all $ n·m $ elements. To achieve that, they will purchase some samples from other laboratories and then produce all remaining elements using an arbitrary number of nuclear fusions in some order. Help them to find the minimal number of elements they need to purchase.

## 输入格式

The first line contains three integers $ n $ , $ m $ , $ q $ ( $ 1<=n,m<=200000 $ ; $ 0<=q<=min(n·m,200000) $ ), the chemical table dimensions and the number of elements scientists already have.

The following $ q $ lines contain two integers $ r_{i} $ , $ c_{i} $ ( $ 1<=r_{i}<=n $ , $ 1<=c_{i}<=m $ ), each describes an element that scientists already have. All elements in the input are different.

## 输出格式

Print the minimal number of elements to be purchased.

## 说明/提示

For each example you have a picture which illustrates it.

The first picture for each example describes the initial set of element samples available. Black crosses represent elements available in the lab initially.

The second picture describes how remaining samples can be obtained. Red dashed circles denote elements that should be purchased from other labs (the optimal solution should minimize the number of red circles). Blue dashed circles are elements that can be produced with nuclear fusion. They are numbered in order in which they can be produced.

Test 1

We can use nuclear fusion and get the element from three other samples, so we don't need to purchase anything.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1012B/d0188b7b484eed4ec50dd63bc64a04ce06b65611.png)Test 2

We cannot use any nuclear fusion at all as there is only one row, so we have to purchase all missing elements.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1012B/ba8b5c94cc17a4604dd0e58fb6a66f6e2487526e.png)Test 3

There are several possible solutions. One of them is illustrated below.

Note that after purchasing one element marked as red it's still not possible to immidiately produce the middle element in the bottom row (marked as 4). So we produce the element in the left-top corner first (marked as 1), and then use it in future fusions.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1012B/5273513fe4bf0485a76591391c8b08a7edf8e9af.png)

## 样例 #1

### 输入

```
2 2 3
1 2
2 2
2 1

```

### 输出

```
0

```

## 样例 #2

### 输入

```
1 5 3
1 3
1 1
1 5

```

### 输出

```
2

```

## 样例 #3

### 输入

```
4 3 6
1 2
1 3
2 2
2 3
3 1
3 3

```

### 输出

```
1

```



---

---
title: "Vasya And The Matrix"
layout: "post"
diff: 提高+/省选-
pid: CF1016D
tag: ['进制', '构造']
---

# Vasya And The Matrix

## 题目描述

Now Vasya is taking an exam in mathematics. In order to get a good mark, Vasya needs to guess the matrix that the teacher has constructed!

Vasya knows that the matrix consists of $ n $ rows and $ m $ columns. For each row, he knows the xor (bitwise excluding or) of the elements in this row. The sequence $ a_{1},a_{2},...,a_{n} $ denotes the xor of elements in rows with indices $ 1 $ , $ 2 $ , ..., $ n $ , respectively. Similarly, for each column, he knows the xor of the elements in this column. The sequence $ b_{1},b_{2},...,b_{m} $ denotes the xor of elements in columns with indices $ 1 $ , $ 2 $ , ..., $ m $ , respectively.

Help Vasya! Find a matrix satisfying the given constraints or tell him that there is no suitable matrix.

## 输入格式

The first line contains two numbers $ n $ and $ m (2<=n,m<=100) $ — the dimensions of the matrix.

The second line contains $ n $ numbers $ a_{1},a_{2},...,a_{n} (0<=a_{i}<=10^{9}) $ , where $ a_{i} $ is the xor of all elements in row $ i $ .

The third line contains $ m $ numbers $ b_{1},b_{2},...,b_{m} (0<=b_{i}<=10^{9}) $ , where $ b_{i} $ is the xor of all elements in column $ i $ .

## 输出格式

If there is no matrix satisfying the given constraints in the first line, output "NO".

Otherwise, on the first line output "YES", and then $ n $ rows of $ m $ numbers in each $ c_{i1},c_{i2},...\ ,c_{im} (0<=c_{ij}<=2·10^{9}) $ — the description of the matrix.

If there are several suitable matrices, it is allowed to print any of them.

## 样例 #1

### 输入

```
2 3
2 9
5 3 13

```

### 输出

```
YES
3 4 5
6 7 8

```

## 样例 #2

### 输入

```
3 3
1 7 6
2 15 12

```

### 输出

```
NO

```



---

---
title: "Tree Reconstruction"
layout: "post"
diff: 提高+/省选-
pid: CF1041E
tag: ['构造']
---

# Tree Reconstruction

## 题目描述

### 题目大意：
有一棵树，现在给你每条树边被去掉时，形成的两个联通块中点的最大的编号分别是多少，问满足条件的树存不存在

## 输入格式

第一行一个整数$n$

往下$n-1$行，每行两个整数，表示去掉这条边后两个联通块中点的最大的编号是多少

## 输出格式

如果不存在满足条件的树，输出"NO"

否则输出"YES"，下面$n-1$行每行描述一条树边（两端点的编号）

## 样例 #1

### 输入

```
4
3 4
1 4
3 4

```

### 输出

```
YES
1 3
3 2
2 4

```

## 样例 #2

### 输入

```
3
1 3
1 3

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
3
1 2
2 3

```

### 输出

```
NO

```



---

---
title: "Replace by MEX"
layout: "post"
diff: 提高+/省选-
pid: CF1375D
tag: ['构造']
---

# Replace by MEX

## 题目描述

You're given an array of $ n $ integers between $ 0 $ and $ n $ inclusive.

In one operation, you can choose any element of the array and replace it by the MEX of the elements of the array (which may change after the operation).

For example, if the current array is $ [0, 2, 2, 1, 4] $ , you can choose the second element and replace it by the MEX of the present elements — $ 3 $ . Array will become $ [0, 3, 2, 1, 4] $ .

You must make the array non-decreasing, using at most $ 2n $ operations.

It can be proven that it is always possible. Please note that you do not have to minimize the number of operations. If there are many solutions, you can print any of them.

 –

An array $ b[1 \ldots n] $ is non-decreasing if and only if $ b_1 \le b_2 \le \ldots \le b_n $ .

The MEX (minimum excluded) of an array is the smallest non-negative integer that does not belong to the array. For instance:

- The MEX of $ [2, 2, 1] $ is $ 0 $ , because $ 0 $ does not belong to the array.
- The MEX of $ [3, 1, 0, 1] $ is $ 2 $ , because $ 0 $ and $ 1 $ belong to the array, but $ 2 $ does not.
- The MEX of $ [0, 3, 1, 2] $ is $ 4 $ because $ 0 $ , $ 1 $ , $ 2 $ and $ 3 $ belong to the array, but $ 4 $ does not.

It's worth mentioning that the MEX of an array of length $ n $ is always between $ 0 $ and $ n $ inclusive.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le       200 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 3 \le n \le 1000 $ ) — length of the array.

The second line of each test case contains $ n $ integers $ a_1, \ldots, a_n $ ( $ 0 \le a_i \le n $ ) — elements of the array. Note that they don't have to be distinct.

It is guaranteed that the sum of $ n $ over all test cases doesn't exceed $ 1000 $ .

## 输出格式

For each test case, you must output two lines:

The first line must contain a single integer $ k $ ( $ 0 \le k       \le 2n $ ) — the number of operations you perform.

The second line must contain $ k $ integers $ x_1, \ldots,       x_k $ ( $ 1 \le x_i \le n $ ), where $ x_i $ is the index chosen for the $ i $ -th operation.

If there are many solutions, you can find any of them. Please remember that it is not required to minimize $ k $ .

## 说明/提示

In the first test case, the array is already non-decreasing ( $ 2       \le 2 \le 3 $ ).

Explanation of the second test case (the element modified by each operation is colored in red):

- $ a = [2, 1, 0] $ ; the initial MEX is $ 3 $ .
- $ a = [2, 1, {\color{red}{3}}] $ ; the new MEX is $ 0 $ .
- $ a = [ {\color{red}{0}} , 1, 3] $ ; the new MEX is $ 2 $ .
- The final array is non-decreasing: $ 0 \le 1 \le 3 $ .

Explanation of the third test case:

- $ a = [0, 7, 3, 1, 3, 7, 7] $ ; the initial MEX is $ 2 $ .
- $ a = [0, {\color{red}{2}}, 3, 1, 3, 7, 7] $ ; the new MEX is $ 4 $ .
- $ a = [0, 2, 3, 1, {\color{red}{4}}, 7, 7] $ ; the new MEX is $ 5 $ .
- $ a = [0, 2, 3, 1, {\color{red}{5}}, 7, 7] $ ; the new MEX is $ 4 $ .
- $ a = [0, 2, 3, {\color{red}{4}}, 5, 7, 7] $ ; the new MEX is $ 1 $ .
- The final array is non-decreasing: $ 0 \le 2 \le 3 \le 4 \le         5 \le 7 \le 7 $ .

## 样例 #1

### 输入

```
5
3
2 2 3
3
2 1 0
7
0 7 3 1 3 7 7
9
2 0 1 1 2 4 4 2 0
9
8 4 7 6 1 2 3 0 5
```

### 输出

```
0

2
3 1
4
2 5 5 4
11
3 8 9 7 8 5 9 6 4 1 2
10
1 8 1 9 5 2 4 6 3 7
```



---

---
title: "Towers"
layout: "post"
diff: 提高+/省选-
pid: CF1637F
tag: ['贪心', '构造']
---

# Towers

## 题目描述

You are given a tree with $ n $ vertices numbered from $ 1 $ to $ n $ . The height of the $ i $ -th vertex is $ h_i $ . You can place any number of towers into vertices, for each tower you can choose which vertex to put it in, as well as choose its efficiency. Setting up a tower with efficiency $ e $ costs $ e $ coins, where $ e > 0 $ .

It is considered that a vertex $ x $ gets a signal if for some pair of towers at the vertices $ u $ and $ v $ ( $ u \neq v $ , but it is allowed that $ x = u $ or $ x = v $ ) with efficiencies $ e_u $ and $ e_v $ , respectively, it is satisfied that $ \min(e_u, e_v) \geq h_x $ and $ x $ lies on the path between $ u $ and $ v $ .

Find the minimum number of coins required to set up towers so that you can get a signal at all vertices.

## 输入格式

The first line contains an integer $ n $ ( $ 2 \le n \le 200\,000 $ ) — the number of vertices in the tree.

The second line contains $ n $ integers $ h_i $ ( $ 1 \le h_i \le 10^9 $ ) — the heights of the vertices.

Each of the next $ n - 1 $ lines contain a pair of numbers $ v_i, u_i $ ( $ 1 \le v_i, u_i \le n $ ) — an edge of the tree. It is guaranteed that the given edges form a tree.

## 输出格式

Print one integer — the minimum required number of coins.

## 说明/提示

In the first test case it's optimal to install two towers with efficiencies $ 2 $ at vertices $ 1 $ and $ 3 $ .

In the second test case it's optimal to install a tower with efficiency $ 1 $ at vertex $ 1 $ and two towers with efficiencies $ 3 $ at vertices $ 2 $ and $ 5 $ .

In the third test case it's optimal to install two towers with efficiencies $ 6 $ at vertices $ 1 $ and $ 2 $ .

## 样例 #1

### 输入

```
3
1 2 1
1 2
2 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5
1 3 3 1 3
1 3
5 4
4 3
2 3
```

### 输出

```
7
```

## 样例 #3

### 输入

```
2
6 1
1 2
```

### 输出

```
12
```



---

---
title: "Equal Tree Sums"
layout: "post"
diff: 提高+/省选-
pid: CF1656E
tag: ['贪心', '构造']
---

# Equal Tree Sums

## 题目描述

You are given an undirected unrooted tree, i.e. a connected undirected graph without cycles.

You must assign a nonzero integer weight to each vertex so that the following is satisfied: if any vertex of the tree is removed, then each of the remaining connected components has the same sum of weights in its vertices.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. Description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 3 \leq n \leq 10^5 $ ) — the number of vertices of the tree.

The next $ n-1 $ lines of each case contain each two integers $ u, v $ ( $ 1 \leq u,v \leq n $ ) denoting that there is an edge between vertices $ u $ and $ v $ . It is guaranteed that the given edges form a tree.

The sum of $ n $ for all test cases is at most $ 10^5 $ .

## 输出格式

For each test case, you must output one line with $ n $ space separated integers $ a_1, a_2, \ldots, a_n $ , where $ a_i $ is the weight assigned to vertex $ i $ . The weights must satisfy $ -10^5 \leq a_i \leq 10^5 $ and $ a_i \neq 0 $ .

It can be shown that there always exists a solution satisfying these constraints. If there are multiple possible solutions, output any of them.

## 说明/提示

In the first case, when removing vertex $ 1 $ all remaining connected components have sum $ 5 $ and when removing vertex $ 3 $ all remaining connected components have sum $ 2 $ . When removing other vertices, there is only one remaining connected component so all remaining connected components have the same sum.

## 样例 #1

### 输入

```
2
5
1 2
1 3
3 4
3 5
3
1 2
1 3
```

### 输出

```
-3 5 1 2 2
1 1 1
```



---

---
title: "notepad.exe"
layout: "post"
diff: 提高+/省选-
pid: CF1672E
tag: ['构造']
---

# notepad.exe

## 题目描述

This is an interactive problem.

There are $ n $ words in a text editor. The $ i $ -th word has length $ l_i $ ( $ 1 \leq l_i \leq 2000 $ ). The array $ l $ is hidden and only known by the grader.

The text editor displays words in lines, splitting each two words in a line with at least one space. Note that a line does not have to end with a space. Let the height of the text editor refer to the number of lines used. For the given width, the text editor will display words in such a way that the height is minimized.

More formally, suppose that the text editor has width $ w $ . Let $ a $ be an array of length $ k+1 $ where $ 1=a_1 < a_2 < \ldots < a_{k+1}=n+1 $ . $ a $ is a valid array if for all $ 1 \leq i \leq k $ , $ l_{a_i}+1+l_{a_i+1}+1+\ldots+1+l_{a_{i+1}-1} \leq w $ . Then the height of the text editor is the minimum $ k $ over all valid arrays.

Note that if $ w < \max(l_i) $ , the text editor cannot display all the words properly and will crash, and the height of the text editor will be $ 0 $ instead.

You can ask $ n+30 $ queries. In one query, you provide a width $ w $ . Then, the grader will return the height $ h_w $ of the text editor when its width is $ w $ .

Find the minimum area of the text editor, which is the minimum value of $ w \cdot h_w $ over all $ w $ for which $ h_w \neq 0 $ .

The lengths are fixed in advance. In other words, the interactor is not adaptive.

## 输入格式

The first and only line of input contains a single integer $ n $ ( $ 1 \leq n \leq 2000 $ ) — the number of words on the text editor.

It is guaranteed that the hidden lengths $ l_i $ satisfy $ 1 \leq l_i \leq 2000 $ .

## 输出格式

Begin the interaction by reading $ n $ .

To make a query, print "? $ w $ " (without quotes, $ 1 \leq w \leq 10^9 $ ). Then you should read our response from standard input, that is, $ h_w $ .

If your program has made an invalid query or has run out of tries, the interactor will terminate immediately and your program will get a verdict Wrong answer.

To give the final answer, print "! $ area $ " (without the quotes). Note that giving this answer is not counted towards the limit of $ n+30 $ queries.

After printing a query do not forget to output end of line and flush the output. Otherwise, you will get Idleness limit exceeded. To do this, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- see documentation for other languages.

Hacks

The first line of input must contain a single integer $ n $ ( $ 1 \leq n \leq 2000 $ ) — the number of words in the text editor.

The second line of input must contain exactly $ n $ space-separated integers $ l_1,l_2,\ldots,l_n $ ( $ 1 \leq l_i \leq 2000 $ ).

## 说明/提示

In the first test case, the words are $ \{\texttt{glory},\texttt{to},\texttt{ukraine},\texttt{and},\texttt{anton},\texttt{trygub}\} $ , so $ l=\{5,2,7,3,5,6\} $ .

If $ w=1 $ , then the text editor is not able to display all words properly and will crash. The height of the text editor is $ h_1=0 $ , so the grader will return $ 0 $ .

If $ w=9 $ , then a possible way that the words will be displayed on the text editor is:

- $ \texttt{glory__to} $
- $ \texttt{ukraine__} $
- $ \texttt{and_anton} $
- $ \texttt{__trygub_} $

The height of the text editor is $ h_{9}=4 $ , so the grader will return $ 4 $ .

If $ w=16 $ , then a possible way that the words will be displayed on the text editor is:

- $ \texttt{glory_to_ukraine} $
- $ \texttt{and_anton_trygub} $

The height of the text editor is $ h_{16}=2 $ , so the grader will return $ 2 $ .

We have somehow figured out that the minimum area of the text editor is $ 32 $ , so we answer it.

## 样例 #1

### 输入

```
6

0

4

2
```

### 输出

```
? 1

? 9

? 16

! 32
```



---

---
title: "MEX vs DIFF"
layout: "post"
diff: 提高+/省选-
pid: CF1684E
tag: ['贪心', '构造']
---

# MEX vs DIFF

## 题目描述

给你一个大小为n的数组a，保证数组内元素非负，你可以执行以下操作k次：

在一次操作中将数组内任意一个数字改为任何一个非负整数。

现在定义这个数组的成本为DIFF(a)−MEX(a)，其中 DIFF(a) 为a数组内元素去重后的数量，  MEX(a) 为数组中未出现的元素中最小的元素，
举个例子，MEX( { 1 , 2 , 3 } )=0 , MEX( { 0 , 1 , 2 , 4 , 5 } ) = 3。

现在给你数组a，求能实现的最小成本。

## 输入格式

输入包含多个测试用例，第一行输入t表示数据组数，测试用例描述如下：

每个用例的第一行包含两个整数n和k，n表示数组长度，k表示最多的操作次数，第二行有n个整数，为数组n的元素。

## 输出格式

对于每个测试用例输出一行一个整数，表示该用例能实现的最小整数。

## 说明/提示

在第一个测试用例中，不需要任何操作来最小化 DIFF-MEX 的值。

在第二个测试用例中，可以将 5 替换为 1 。 数组 a 变为[ 0 , 2 , 4 , 1 ] , DIFF = 4，MEX=MEX( { 0 , 1 , 2 , 4 } )=3 ，所以答案是 1.

在第三个测试用例中，一个可能的数组 a 的变形是[ 4 , 13 , 0 , 0 , 13 , 1 , 2 ]，其中 DIFF = 5，MEX = 3。

在第四个测试用例中，一个可能的数组 a 的变形是 [ 1 , 2 , 3 , 0 , 0 , 0 ] 。

## 样例 #1

### 输入

```
4
4 1
3 0 1 2
4 1
0 2 4 5
7 2
4 13 0 0 13 1337 1000000000
6 2
1 2 8 0 0 0
```

### 输出

```
0
1
2
0
```



---

---
title: "Build a Tree and That Is It"
layout: "post"
diff: 提高+/省选-
pid: CF1714F
tag: ['构造']
---

# Build a Tree and That Is It

## 题目描述

# Build a Tree and That Is It


树是一个没有环的无向连通图，**注意**，在本题中，我们讨论的是无根树

现有四个整数 $ n, d_{12}, d_{23} $ 和 $ d_{31} $ . 构建一颗满足以下条件的树:

- 包含从 $ 1 $ 到 $ n $ 的 $n$ 个节点,
- 从节点 $ 1 $ 到节点 $ 2 $ 的距离（最短路的长度）为 $ d_{12} $ ,
- 从节点 $ 2 $ 到节点 $ 3 $ 的距离为 $ d_{23} $ ,
- 从节点 $ 3 $ 到节点 $ 1 $ 的距离为 $ d_{31} $ .

输出满足条件的任意一棵树；若不存在，请~~证明~~.

## 输入格式

第一行包含一个整数 $ t $ ( $ 1 \le t \le 10^4 $ ) 表示测试组数.

接下来 $ t $ 组, 每组一行数据包含 $4$ 个整数 $ n, d_{12}, d_{23} $ and $ d_{31} $ ( $ 3 \le n \le 2\cdot10^5; 1 \le d_{12}, d_{23}, d_{31} \le n-1 $ ).

输入数据保证所有 $ n $ 不超过 $ 2\cdot10^5 $ .

## 输出格式

对于每一组数据，若存在这种树，输出`YES`；若不存在，输出`NO`.

对于存在的情况，额外输出 $ n-1 $ 行来描述这棵树的边（一对正整数 $ x_i, y_i $ 表示第 $ i $ 条边连接第 $ x_i $ 号节点和第 $ y_i $ 号节点.

你可以按照任何顺序输出这些边及其顶点，若有多种解，输出其中一种即可.

## 样例 #1

### 样例输入 #1

```
9
5 1 2 1
5 2 2 2
5 2 2 3
5 2 2 4
5 3 2 3
4 2 1 1
4 3 1 1
4 1 2 3
7 1 4 1
```

### 样例输出 #1

```
YES
1 2
4 1
3 1
2 5
YES
4 3
2 5
1 5
5 3
NO
YES
2 4
4 1
2 5
5 3
YES
5 4
4 1
2 5
3 5
YES
2 3
3 4
1 3
NO
YES
4 3
1 2
2 4
NO
```

## 样例 #1

### 输入

```
9
5 1 2 1
5 2 2 2
5 2 2 3
5 2 2 4
5 3 2 3
4 2 1 1
4 3 1 1
4 1 2 3
7 1 4 1
```

### 输出

```
YES
1 2
4 1
3 1
2 5
YES
4 3
2 5
1 5
5 3
NO
YES
2 4
4 1
2 5
5 3
YES
5 4
4 1
2 5
3 5
YES
2 3
3 4
1 3
NO
YES
4 3
1 2
2 4
NO
```



---

---
title: "Permutation Addicts"
layout: "post"
diff: 提高+/省选-
pid: CF1738D
tag: ['构造']
---

# Permutation Addicts

## 题目描述

Given a permutation $ a_1, a_2, \dots, a_n $ of integers from $ 1 $ to $ n $ , and a threshold $ k $ with $ 0 \leq k \leq n $ , you compute a sequence $ b_1, b_2, \dots, b_n $ as follows.

For every $ 1 \leq i \leq n $ in increasing order, let $ x = a_i $ .

- If $ x \leq k $ , set $ b_{x} $ to the last element $ a_j $ ( $ 1 \leq j < i $ ) that $ a_j > k $ . If no such element $ a_j $ exists, set $ b_{x} = n+1 $ .
- If $ x > k $ , set $ b_{x} $ to the last element $ a_j $ ( $ 1 \leq j < i $ ) that $ a_j \leq k $ . If no such element $ a_j $ exists, set $ b_{x} = 0 $ .

Unfortunately, after the sequence $ b_1, b_2, \dots, b_n $ has been completely computed, the permutation $ a_1, a_2, \dots, a_n $ and the threshold $ k $ are discarded.

Now you only have the sequence $ b_1, b_2, \dots, b_n $ . Your task is to find any possible permutation $ a_1, a_2, \dots, a_n $ and threshold $ k $ that produce the sequence $ b_1, b_2, \dots, b_n $ . It is guaranteed that there exists at least one pair of permutation $ a_1, a_2, \dots, a_n $ and threshold $ k $ that produce the sequence $ b_1, b_2, \dots, b_n $ .

A permutation of integers from $ 1 $ to $ n $ is a sequence of length $ n $ which contains all integers from $ 1 $ to $ n $ exactly once.

## 输入格式

Each test contains multiple test cases. The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^5 $ ) — the number of test cases. The following lines contain the description of each test case.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 10^5 $ ), indicating the length of the permutation $ a $ .

The second line of each test case contains $ n $ integers $ b_1, b_2, \dots, b_n $ ( $ 0 \leq b_i \leq n+1 $ ), indicating the elements of the sequence $ b $ .

It is guaranteed that there exists at least one pair of permutation $ a_1, a_2, \dots, a_n $ and threshold $ k $ that produce the sequence $ b_1, b_2, \dots, b_n $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output the threshold $ k $ ( $ 0 \leq k \leq n $ ) in the first line, and then output the permutation $ a_1, a_2, \dots, a_n $ ( $ 1 \leq a_i \leq n $ ) in the second line such that the permutation $ a_1, a_2, \dots, a_n $ and threshold $ k $ produce the sequence $ b_1, b_2, \dots, b_n $ . If there are multiple solutions, you can output any of them.

## 说明/提示

For the first test case, permutation $ a = [1,3,2,4] $ and threshold $ k = 2 $ will produce sequence $ b $ as follows.

- When $ i = 1 $ , $ x = a_i = 1 \leq k $ , there is no $ a_j $ ( $ 1 \leq j < i $ ) that $ a_j > k $ . Therefore, $ b_1 = n + 1 = 5 $ .
- When $ i = 2 $ , $ x = a_i = 3 > k $ , the last element $ a_j $ that $ a_j \leq k $ is $ a_1 $ . Therefore, $ b_3 = a_1 = 1 $ .
- When $ i = 3 $ , $ x = a_i = 2 \leq k $ , the last element $ a_j $ that $ a_j > k $ is $ a_2 $ . Therefore, $ b_2 = a_2 = 3 $ .
- When $ i = 4 $ , $ x = a_i = 4 > k $ , the last element $ a_j $ that $ a_j \leq k $ is $ a_3 $ . Therefore, $ b_4 = a_3 = 2 $ .

 Finally, we obtain sequence $ b = [5,3,1,2] $ . For the second test case, permutation $ a = [1,2,3,4,5,6] $ and threshold $ k = 3 $ will produce sequence $ b $ as follows.

- When $ i = 1, 2, 3 $ , $ a_i \leq k $ , there is no $ a_j $ ( $ 1 \leq j < i $ ) that $ a_j > k $ . Therefore, $ b_1 = b_2 = b_3 = n + 1 = 7 $ .
- When $ i = 4, 5, 6 $ , $ a_i > k $ , the last element $ a_j $ that $ a_j \leq k $ is $ a_3 $ . Therefore, $ b_4 = b_5 = b_6 = a_3 = 3 $ .

 Finally, we obtain sequence $ b = [7,7,7,3,3,3] $ . For the third test case, permutation $ a = [6,5,4,3,2,1] $ and threshold $ k = 3 $ will produce sequence $ b $ as follows.

- When $ i = 1, 2, 3 $ , $ a_i > k $ , there is no $ a_j $ ( $ 1 \leq j < i $ ) that $ a_j \leq k $ . Therefore, $ b_4 = b_5 = b_6 = 0 $ .
- When $ i = 4, 5, 6 $ , $ a_i \leq k $ , the last element $ a_j $ that $ a_j > k $ is $ a_3 $ . Therefore, $ b_1 = b_2 = b_3 = a_3 = 4 $ .

 Finally, we obtain sequence $ b = [4,4,4,0,0,0] $ .

## 样例 #1

### 输入

```
3
4
5 3 1 2
6
7 7 7 3 3 3
6
4 4 4 0 0 0
```

### 输出

```
2
1 3 2 4
3
1 2 3 4 5 6
3
6 5 4 3 2 1
```



---

---
title: "ConstructOR"
layout: "post"
diff: 提高+/省选-
pid: CF1748D
tag: ['贪心', '中国剩余定理 CRT', '位运算', '构造']
---

# ConstructOR

## 题目描述

You are given three integers $ a $ , $ b $ , and $ d $ . Your task is to find any integer $ x $ which satisfies all of the following conditions, or determine that no such integers exist:

- $ 0 \le x \lt 2^{60} $ ;
- $ a|x $ is divisible by $ d $ ;
- $ b|x $ is divisible by $ d $ .

Here, $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

## 输入格式

Each test contains multiple test cases. The first line of input contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Each test case consists of one line, containing three integers $ a $ , $ b $ , and $ d $ ( $ 1 \le a,b,d \lt 2^{30} $ ).

## 输出格式

For each test case print one integer. If there exists an integer $ x $ which satisfies all of the conditions from the statement, print $ x $ . Otherwise, print $ -1 $ .

If there are multiple solutions, you may print any of them.

## 说明/提示

In the first test case, $ x=18 $ is one of the possible solutions, since $ 39|18=55 $ and $ 12|18=30 $ , both of which are multiples of $ d=5 $ .

In the second test case, $ x=14 $ is one of the possible solutions, since $ 8|14=6|14=14 $ , which is a multiple of $ d=14 $ .

In the third and fourth test cases, we can show that there are no solutions.

## 样例 #1

### 输入

```
8
12 39 5
6 8 14
100 200 200
3 4 6
2 2 2
18 27 3
420 666 69
987654321 123456789 999999999
```

### 输出

```
18
14
-1
-1
0
11
25599
184470016815529983
```



---

---
title: "Doremy's Experimental Tree"
layout: "post"
diff: 提高+/省选-
pid: CF1764F
tag: ['图论', '并查集', '构造']
---

# Doremy's Experimental Tree

## 题目描述

Doremy has an edge-weighted tree with $ n $ vertices whose weights are integers between $ 1 $ and $ 10^9 $ . She does $ \frac{n(n+1)}{2} $ experiments on it.

In each experiment, Doremy chooses vertices $ i $ and $ j $ such that $ j \leq i $ and connects them directly with an edge with weight $ 1 $ . Then, there is exactly one cycle (or self-loop when $ i=j $ ) in the graph. Doremy defines $ f(i,j) $ as the sum of lengths of shortest paths from every vertex to the cycle.

Formally, let $ \mathrm{dis}_{i,j}(x,y) $ be the length of the shortest path between vertex $ x $ and $ y $ when the edge $ (i,j) $ of weight $ 1 $ is added, and $ S_{i,j} $ be the set of vertices that are on the cycle when edge $ (i,j) $ is added. Then,
 $$ f(i,j)=\sum_{x=1}^{n}\left(\min_{y\in S_{i,j}}\mathrm{dis}_{i,j}(x,y)\right).  $$
 
 Doremy writes down all values of  $ f(i,j) $  such that  $ 1 \leq j \leq i \leq n $ , then goes to sleep. However, after waking up, she finds that the tree has gone missing. Fortunately, the values of  $ f(i,j) $  are still in her notebook, and she knows which  $ i $  and  $ j $  they belong to. Given the values of  $ f(i,j)$, can you help her restore the tree?

It is guaranteed that at least one suitable tree exists.

## 输入格式

The first line of input contains a single integer $ n $ ($ 2 \le n \le 2000 $) — the number of vertices in the tree.

The following $ n $ lines contain a lower-triangular matrix with $ i $ integers on the $ i $ -th line; the $ j $ -th integer on the $ i $ -th line is $ f(i,j) $ ( $ 0 \le f(i,j) \le 2\cdot 10^{15} $ ).

It is guaranteed that there exists a tree whose weights are integers between $ 1 $ and $ 10^9 $ such that the values of $ f(i,j) $ of the tree match those given in the input.

## 输出格式

Print $ n-1 $ lines describing the tree. In the $ i $ -th line of the output, output three integers $ u_i $ , $ v_i $ , $ w_i $ ( $ 1 \le u_i,v_i \le n $ , $ 1 \le w_i \le 10^9 $ ), representing an edge $ (u_i,v_i) $ whose weight is $ w_i $ .

If there are multiple answers, you may output any.

All edges must form a tree and all values of $ f(i,j) $ must match those given in the input.

## 说明/提示

In the first test case, the picture below, from left to right, from top to bottom, shows the graph when pairs $ (1,1) $ , $ (1,2) $ , $ (1,3) $ , $ (2,2) $ , $ (2,3) $ , $ (3,3) $ are connected with an edge, respectively. The nodes colored yellow are on the cycle.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764F/65b459471236cb3c4f73ac2ff04b74120b42f624.png)

## 样例 #1

### 输入

```
3
7
3 5
0 2 8
```

### 输出

```
2 3 3
1 2 2
```

## 样例 #2

### 输入

```
9
8081910646
8081902766 8081903751
8081902555 8081903540 8081905228
3090681001 3090681986 3090681775 7083659398
7083657913 7083658898 7083658687 2092437133 15069617722
1748216295 1748217280 1748217069 5741194692 749972427 10439821163
2377558289 2377559274 2377559063 6370536686 1379314421 5028071980 8866466178
1746983932 1746984917 1746984706 5739962329 748740064 10438588800 5026839617 10448447704
2341942133 2341943118 2341942907 6334920530 1343698265 4992455824 8830850022 4991223461 9115779270
```

### 输出

```
1 2 985
2 3 211
2 4 998244353
2 5 998244853
4 6 671232353
6 8 1232363
4 7 356561356
7 9 35616156
```



---

---
title: "Rectangle Shrinking"
layout: "post"
diff: 提高+/省选-
pid: CF1781E
tag: ['贪心', '构造']
---

# Rectangle Shrinking

## 题目描述

你有一个长为 $10^9$，宽为 $2$ 的矩形网格。

起初，网格上有 $n$ 个矩形，这些矩形的边沿着单元格的边。对于第 $i$ 个矩形，左上角为 $(u_i,l_i)$，右下角为 $(d_i,r_i)$。这些矩形两两之间可能相交、重合或包含。

对于每个矩形，你可以进行以下操作一种或者不操作：

- 删除这个矩形。

- 用一个非空的子矩形来替换它。

要求：在完成所有操作后，剩下的所有矩形中不允许任意两个矩形有交。

求剩余矩形覆盖的总面积最大为多少，以及达到最大的任意一种方案。

$1 \le u_i \le d_i \le 2$，$1 \le l_i \le r_i \le 10^9$，$\sum n \le 2 \times 10^5$。

## 输入格式

多测。

第一行一个正整数 $t$ ($1 \le t \le 10^4$) 表示测试用例的数量。

对于每个测试用例，
第一行一个正整数 $n$ ($1 \le n \le 2 \times 10^5$) 表示初始矩形的个数。

接下来一共 $n$ 行，第 $i$ 行包含四个整数 $u_i,l_i,d_i,r_i$ ($1 \le u_i \le d_i \le 2$，$1 \le l_i \le r_i \le 10^9$) 表示矩形左上角和右下角的坐标。

## 输出格式

对于每个测试用例，第一行一个整数 $s$ 表示剩余矩形覆盖的最大总面积。

在之后 $n$ 行中，第 $i$ 行输出四个整数表示方案：

如果第 $i$ 个矩形被删除，输出 `0 0 0 0`。

否则，输出第 $i$ 个矩形被替换后的左上角和右下角的新坐标，满足 $u_i \le u'_i \le d'_i \le d_i$，$l_i \le l'_i \le r'_i \le r_i$ 。

如果有多个解，输出任意一种。

### 样例解释
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1781E/2361ff07797a1f95e7735ebc4fd257e63a865b14.png)

上图为第一个测试用例的图片。上方为初始矩形，下方为剩余矩形。

翻译来自 [jianhe](https://www.luogu.com.cn/user/613794)。

## 样例 #1

### 输入

```
8
5
1 2 2 4
2 4 2 8
1 4 2 7
1 2 1 2
1 9 1 10
2
1 1 1 10
1 5 1 15
2
1 1 1 10
1 1 1 10
5
1 3 1 7
1 3 1 8
1 1 1 4
1 2 1 7
1 10 1 11
2
1 1 2 10
1 5 1 8
2
1 5 2 10
1 2 1 7
2
1 5 2 10
2 2 2 15
5
2 6 2 7
1 4 2 5
1 5 1 9
1 7 2 10
1 2 1 6
```

### 输出

```
15
1 2 2 4
2 5 2 8
1 5 1 7
0 0 0 0
1 9 1 10
15
1 1 1 10
1 11 1 15
10
1 1 1 10
0 0 0 0
10
0 0 0 0
1 8 1 8
1 1 1 4
1 5 1 7
1 10 1 11
20
1 1 2 10
0 0 0 0
15
1 5 2 10
1 2 1 4
20
1 5 1 10
2 2 2 15
16
2 6 2 6
2 4 2 5
0 0 0 0
1 7 2 10
1 2 1 6
```



---

---
title: "The Harmonization of XOR"
layout: "post"
diff: 提高+/省选-
pid: CF1787E
tag: ['位运算', '构造']
---

# The Harmonization of XOR

## 题目描述

给定 $n$ 个数 $[1,2,3,\ldots,n]$ 和两个正整数 $k$ 和 $x$。

将这些数分成恰好 $k$ 组使得每组的异或和都是 $x$。具体地，每个数都必须出现在恰好一组内。

例如，$n = 15,k = 6,x = 7$ 时，下列分法是合法的（$\oplus$ 表示按位异或运算）：

- $[6,10,11]$, $6 \oplus 10 \oplus 11 = 7$
- $[5,12,14]$, $5 \oplus 12 \oplus 14 = 7$
- $[3,9,13]$, $3 \oplus 9 \oplus 13 = 7$
- $[1,2,4]$, $1 \oplus 2 \oplus 4 = 7$
- $[8,15]$, $8 \oplus 15 = 7$
- $[7]$, $7 = 7$

下列分法是不合法的：

- $[6,10,11]$, $6 \oplus 10 \oplus 11 = 7$
- $[5,12,14]$, $5 \oplus 12 \oplus 14 = 7$
- $[3,9,13]$, $3 \oplus 9 \oplus 13 = 7$
- $[1,2,4]$, $1 \oplus 2 \oplus 4 = 7$
- $[7]$, $7 = 7$

因为 $8$ 和 $15$ 没有出现。

下列分法也不合法：

- $[6,10,11]$, $6 \oplus 10 \oplus 11 = 7$,
- $[5,12,14]$, $5 \oplus 12 \oplus 14 = 7$,
- $[3,9,13]$, $3 \oplus 9 \oplus 13 = 7$,
- $[3,4]$, $3 \oplus 4 = 7$,
- $[8,15]$, $8 \oplus 15 = 7$,
- $[7]$, $7 = 7$.

因为 $1$ 和 $2$ 未出现且 $3$ 出现两次。

~~这题本来是 C~~


保证所有测试数据的 $n$ 之和不超过 $2\cdot 10^5$。

## 输入格式

第一行一个正整数 $t$（$1\le t\le 10^4$）表示测试数据组数。

## 输出格式

对于每组测试数据，若不存在合法方案，输出 `NO`。若存在，先输出 `YES`，接下来 $k$ 行输出方案。具体地，每一行第一个数字输出这一组的长度 $s_i$，后接 $s_i$ 个数字表示这一组的数字。注意每一组中的数字可以按任意顺序给出。

### 样例解释

第一组测试数据中，给出的一组合法方案如下：

- $[6,10,11]$, $6 \oplus 10 \oplus 11 = 7$
- $[5,12,14]$, $5 \oplus 12 \oplus 14 = 7$
- $[3,9,13]$, $3 \oplus 9 \oplus 13 = 7$
- $[1,2,4]$, $1 \oplus 2 \oplus 4 = 7$
- $[8,15]$, $8 \oplus 15 = 7$
- $[7]$, $7 = 7$

第二组测试数据中，给出的一组合法方案如下：

- $[1,4]$, $1 \oplus 4 = 5$
- $[2,7]$, $2 \oplus 7 = 5$
- $[3,6]$, $3 \oplus 6 = 5$
- $[5,8,9,10,11]$, $5 \oplus 8 \oplus 9 \oplus 10 \oplus 11 = 5$

同时下面的方案也合法：

- $[1,4]$, $1 \oplus 4 = 5$
- $[2,7]$, $2 \oplus 7 = 5$
- $[5]$, $5 = 5$
- $[3,6,8,9,10,11]$, $3 \oplus 6 \oplus 8 \oplus 9 \oplus 10 \oplus 11 = 5$

## 样例 #1

### 输入

```
7
15 6 7
11 4 5
5 3 2
4 1 4
6 1 7
11 5 5
11 6 5
```

### 输出

```
YES
3 6 10 11
3 5 12 14
3 3 9 13
3 1 2 4
2 8 15
1 7
YES
2 1 4
2 2 7
2 3 6
5 5 8 9 10 11
NO
YES
4 1 2 3 4
YES
6 1 2 3 4 5 6
NO
NO
```



---

---
title: "Divisors and Table"
layout: "post"
diff: 提高+/省选-
pid: CF1792E
tag: ['数论', '素数判断,质数,筛法', '构造']
---

# Divisors and Table

## 题目描述

给定一张 $n \times n$ 的表格和一个正整数 $m = m_1 \times m_2$，表格第 $i$ 行第 $j$ 列的数 $a_{i, j} = i \times j$。

现在需要你求出 $m$ 的每个因子 $d$ 是否在表格中出现，若出现，则求出其出现在表格中的最小行号。

## 输入格式

第一行一个整数 $t$，表示测试用例的组数。

## 输出格式

对于每组测试用例，设 $d_1, d_2, \dots, d_k$ 为升序排序下 $m$ 的所有因子，$a_1, a_2, \dots, a_k$ 为这些因子在表格中出现的最小行号，特殊地，若 $d_i$ 不在表格中出现，则 $a_i = 0$。

输出一行两个整数 $s, X$。其中 $s$ 表示 $m$ 的因子在表格中出现的个数，$X$ 表示答案序列的异或和，形式化地，$X = a_1 \oplus a_2 \oplus \dots \oplus a_k$。

## 样例 #1

### 输入

```
3
3 72 1
10 10 15
6 1 210
```

### 输出

```
6 2
10 0
8 5
```



---

---
title: "City Union"
layout: "post"
diff: 提高+/省选-
pid: CF1799E
tag: ['贪心', '并查集', '构造']
---

# City Union

## 题目描述

You are given $ n \times m $ grid. Some cells are filled and some are empty.

A city is a maximal (by inclusion) set of filled cells such that it is possible to get from any cell in the set to any other cell in the set by moving to adjacent (by side) cells, without moving into any cells not in the set. In other words, a city is a connected component of filled cells with edges between adjacent (by side) cells.

Initially, there are two cities on the grid. You want to change some empty cells into filled cells so that both of the following are satisfied:

- There is one city on the resulting grid.
- The shortest path between any two filled cells, achievable only by moving onto filled cells, is equal to the Manhattan distance between them.

The Manhattan distance between two cells $ (a, b) $ and $ (c, d) $ is equal to $ |a - c| + |b - d| $ .

Find a way to add filled cells that satisfies these conditions and minimizes the total number of filled cells.

## 输入格式

Input consists of multiple test cases. The first line contains a single integer $ t $ , the number of test cases ( $ 1 \le t \le 5000 $ ).

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 50 $ , $ nm \geq 3 $ ).

The next $ n $ lines describe the grid. The $ i $ -th line contains a string $ s_i $ of length $ m $ . $ s_{i,j} $ is '\#' if the cell in position $ (i, j) $ is filled, and '.' if it is empty.

It is guaranteed that there are exactly two cities in the initial grid.

It is guaranteed that the sum of $ n\cdot m $ over all test cases does not exceed $ 25\,000 $ .

## 输出格式

For each test case, output $ n $ lines, each containing a string of length $ m $ , describing the grid you create in the same format as the input.

If there are multiple possible answers with the minimum number of filled cells print any.

## 说明/提示

In the first test case, we can add a single filled cell between the two cities to connect them. We can verify that the second condition is satisfied.

In the second test case, we can also connect the cities with a single filled cell, while satisfying the second condition.

In the third test case, note that if we filled the 3 cells in the top left, the cities would be connected, but the second condition would not be satisfied for cells $ (4, 2) $ and $ (2, 4) $ .

## 样例 #1

### 输入

```
11
1 3
#.#
2 2
.#
#.
4 4
..##
...#
#...
##..
6 6
.##...
##....
......
....##
.....#
...###
6 5
.#..#
.#..#
.#..#
.#.##
.#...
##...
5 5
#####
#...#
#.#.#
#...#
#####
4 4
.##.
##.#
#.##
.##.
5 5
..###
....#
.....
#....
#....
5 6
.##...
##....
#....#
....##
...##.
6 5
..##.
...##
....#
#....
##...
.##..
5 4
..##
..#.
..#.
#...
#...
```

### 输出

```
###

.#
##

..##
..##
###.
##..

.##...
###...
..#...
..####
...###
...###

.####
.####
.####
.####
.#...
##...

#####
#####
#####
#####
#####

.##.
####
####
.##.

..###
..###
..#..
###..
#....

.##...
###...
######
...###
...##.

..##.
..###
..###
###..
###..
.##..

..##
..#.
..#.
###.
#...
```



---

---
title: "Imbalanced Arrays"
layout: "post"
diff: 提高+/省选-
pid: CF1852B
tag: ['贪心', '拓扑排序', '构造']
---

# Imbalanced Arrays

## 题目描述

Ntarsis has come up with an array $ a $ of $ n $ non-negative integers.

Call an array $ b $ of $ n $ integers imbalanced if it satisfies the following:

- $ -n\le b_i\le n $ , $ b_i \ne 0 $ ,
- there are no two indices $ (i, j) $ ( $ 1 \le i, j \le n $ ) such that $ b_i + b_j = 0 $ ,
- for each $ 1 \leq i \leq n $ , there are exactly $ a_i $ indices $ j $ ( $ 1 \le j \le n $ ) such that $ b_i+b_j>0 $ , where $ i $ and $ j $ are not necessarily distinct.

Given the array $ a $ , Ntarsis wants you to construct some imbalanced array. Help him solve this task, or determine it is impossible.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^5 $ ). The description of the test cases follows.

The first line of each test case has a single integer $ n $ ( $ 1 \leq n \leq 10^5 $ ).

The next line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i \leq n $ ).

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output "NO" if there exists no imbalanced array.

Otherwise, output "YES". Then, on the next line, output $ n $ integers $ b_1, b_2, \ldots, b_n $ where $ b_i \neq 0 $ for all $ 1 \leq i \leq n $ — an imbalanced array.

## 说明/提示

For the first test case, $ b = [1] $ is an imbalanced array. This is because for $ i = 1 $ , there is exactly one $ j $ ( $ j = 1 $ ) where $ b_1 + b_j > 0 $ .

For the second test case, it can be shown that there exists no imbalanced array.

For the third test case, $ a = [0, 1, 0] $ . The array $ b = [-3, 1, -2] $ is an imbalanced array.

- For $ i = 1 $ and $ i = 3 $ , there exists no index $ j $ such that $ b_i + b_j > 0 $ .
- For $ i = 2 $ , there is only one index $ j = 2 $ such that $ b_i + b_j > 0 $ ( $ b_2 + b_2 = 1 + 1 = 2 $ ).

 Another possible output for the third test case could be $ b = [-2, 1, -3] $ .

## 样例 #1

### 输入

```
5
1
1
4
1 4 3 4
3
0 1 0
4
4 3 2 1
3
1 3 1
```

### 输出

```
YES
1 
NO
YES
-3 1 -2 
YES
4 2 -1 -3 
YES
-1 3 -1
```



---

---
title: "Permutation of Given"
layout: "post"
diff: 提高+/省选-
pid: CF1918G
tag: ['构造']
---

# Permutation of Given

## 题目描述

You were given only one number, $ n $ . It didn't seem interesting to you, so you wondered if it's possible to come up with an array of length $ n $ consisting of non-zero integers, such that if each element of the array is replaced by the sum of its neighbors (the elements on the ends are replaced by their only neighbors), you obtain a permutation of the numbers in the original array.

## 输入格式

Each test case contains only one number, $ n $ ( $ 2 \leq n \leq 10^6 $ ).

## 输出格式

If a solution exists, output "YES" (without quotes), followed by an array $ a $ ( $ -10^9 \leq a_i \leq 10^9, a_i \neq 0 $ ) that satisfies the condition of the problem. If there are multiple possible answers, output any of them.

If there is no suitable array, output "NO" (without quotes).

The words "YES" and "NO" can be output in any case, for example, "YES", "Yes", "yEs", and so on.

## 说明/提示

In the first test, the array \[ $ 1, 2, -2, -1 $ \] is suitable, because if each element is replaced by the sum of its neighbors, the resulting array is \[ $ 2, -1, 1, -2 $ \], which is a permutation of the original array.

In the second test, it can be shown that there is no solution.

## 样例 #1

### 输入

```
4
```

### 输出

```
YES
1 2 -2 -1
```

## 样例 #2

### 输入

```
5
```

### 输出

```
NO
```



---

---
title: "01 Tree"
layout: "post"
diff: 提高+/省选-
pid: CF1919D
tag: ['构造']
---

# 01 Tree

## 题目描述

There is an edge-weighted complete binary tree with $ n $ leaves. A complete binary tree is defined as a tree where every non-leaf vertex has exactly 2 children. For each non-leaf vertex, we label one of its children as the left child and the other as the right child.

The binary tree has a very strange property. For every non-leaf vertex, one of the edges to its children has weight $ 0 $ while the other edge has weight $ 1 $ . Note that the edge with weight $ 0 $ can be connected to either its left or right child.

You forgot what the tree looks like, but luckily, you still remember some information about the leaves in the form of an array $ a $ of size $ n $ . For each $ i $ from $ 1 $ to $ n $ , $ a_i $ represents the distance $ ^\dagger $ from the root to the $ i $ -th leaf in dfs order $ ^\ddagger $ . Determine whether there exists a complete binary tree which satisfies array $ a $ . Note that you do not need to reconstruct the tree.

 $ ^\dagger $ The distance from vertex $ u $ to vertex $ v $ is defined as the sum of weights of the edges on the path from vertex $ u $ to vertex $ v $ .

 $ ^\ddagger $ The dfs order of the leaves is found by calling the following $ \texttt{dfs} $ function on the root of the binary tree.

```
<pre class="verbatim"><br></br>dfs_order = []<br></br><br></br>function dfs(v):<br></br>    if v is leaf:<br></br>        append v to the back of dfs_order<br></br>    else:<br></br>        dfs(left child of v)<br></br>        dfs(right child of v)<br></br><br></br>dfs(root)<br></br>
```

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 2\cdot 10^5 $ ) — the size of array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le n - 1 $ ) — the distance from the root to the $ i $ -th leaf.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, print "YES" if there exists a complete binary tree which satisfies array $ a $ and "NO" otherwise.

You may print each letter in any case (for example, "YES", "Yes", "yes", "yEs" will all be recognized as a positive answer).

## 说明/提示

In the first test case, the following tree satisfies the array.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1919D/2af3796cd4a2a9733f8a3c061e8120f70b3cbf6a.png)

In the second test case, it can be proven that there is no complete binary tree that satisfies the array.

## 样例 #1

### 输入

```
2
5
2 1 0 1 1
5
1 0 2 1 3
```

### 输出

```
YES
NO
```



---

---
title: "XOR Break — Game Version"
layout: "post"
diff: 提高+/省选-
pid: CF1934D2
tag: ['构造']
---

# XOR Break — Game Version

## 题目描述

This is an interactive problem.

This is the game version of the problem. Note that the solution of this problem may or may not share ideas with the solution of the solo version. You can solve and get points for both versions independently.

Alice and Bob are playing a game. The game starts with a positive integer $ n $ , with players taking turns. On each turn of the game, the following sequence of events takes place:

- The player having the integer $ p $ breaks it into two integers $ p_{1} $ and $ p_{2} $ , where $ 0 \lt p_{1} \lt p $ , $ 0 \lt p_{2} \lt p $ and $ p_{1} \oplus p_{2} = p $ .
- If no such $ p_{1} $ , $ p_{2} $ exist, the player loses.
- Otherwise, the opponent does either select the integer $ p_{1} $ or $ p_{2} $ .
- The game continues with the selected integer. The opponent will try to break it.

As Alice, your goal is to win. You can execute a maximum of $ 63 $ break operations. You have the choice to play first or second. The system will act for Bob.

Here $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

## 输入格式

Each test contains multiple test cases. The first line of input contains a single integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

The only line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 10^{18} $ ) — the number the game starts with.

## 输出格式

For each test case, the interaction begins by reading the integer $ n $ .

After reading $ n $ , print a single line containing either "first" or "second", denoting what you want to play as (as first or second correspondingly).

On Alice's turn, you are required to print two positive integers, $ p_{1} $ and $ p_{2} $ such that $ 0 \lt p_{1} \lt p $ , $ 0 \lt p_{2} \lt p $ and $ p_{1} \oplus p_{2} = p $ . Here, $ p $ equals one of the two integers printed by Bob in the previous turn. If no turn has occurred previously, $ p $ is equal to $ n $ . If Alice cannot perform a break operation, print "0 0" to receive a Wrong answer verdict.

On Bob's turn, you should read two integers, $ p_{1} $ and $ p_{2} $ such that $ 0 \lt p_{1} \lt p $ , $ 0 \lt p_{2} \lt p $ and $ p_{1} \oplus p_{2} = p $ . Here, $ p $ equals one of the two integers printed by Alice in the previous turn. If no turn has occurred previously, $ p $ is equal to $ n $ . If Bob cannot perform a break operation $ p_{1} = 0 $ and $ p_2 = 0 $ in which case you should proceed to the next test case.

If any break operation performed by Alice is invalid, the interactor prints "-1 -1" and your code should promptly exit to receive a wrong answer verdict.

If Alice performs $ 63 $ turns and Bob can still execute a break operation on the current integers, the interactor prints "-1 -1", and your code should promptly exit to receive a wrong answer verdict.

After printing a query, do not forget to output the end of line and flush the output. Otherwise, you will get Idleness limit exceeded. To do this, use:

- fflush(stdout) or cout.flush() in C++;
- System.out.flush() in Java;
- flush(output) in Pascal;
- stdout.flush() in Python;
- see the documentation for other languages.

In this problem, hacks are disabled.

## 说明/提示

Explanation for the interaction.

Interactor / BobAliceExplanation4 $ t $ 1 $ n $ for the first test casesecondAlice chooses to go second0 0Bob says he cannot break $ p = 1 $ 3 $ n $ for the second test casefirstAlice chooses to go first1 2Alice breaks $ p = 3 $ into $ p_1 = 1 $ and $ p_2 = 2 $ 0 0Bob says he cannot break $ p = 1 $ or $ p = 2 $ 13 $ n $ for the third test casefirstAlice chooses to go first10 7Alice breaks $ p = 13 $ into $ p_1 = 10 $ and $ p_2 = 7 $ 3 4Bob breaks $ p = 7 $ into $ p_1 = 3 $ and $ p_2 = 4 $ 1 2Alice breaks $ p = 3 $ into $ p_1 = 1 $ and $ p_2 = 2 $ 0 0Bob says he cannot break $ p = 1 $ or $ p = 2 $ 777777770001 $ n $ for the fourth test casefirstAlice chooses to go first777777770000 1Alice breaks $ p = 777\,777\,770\,001 $ into $ p_1 = 777\,777\,770\,000 $ and $ p_2 = 1 $ 0 0Bob says he cannot perform break operation.This table is for explanation only and does not reflect the actual behavior of the interactor.

Note that in the last test case Bob could choose $ p_1 $ and perform a break operation but he gave up.

## 样例 #1

### 输入

```
4
1

0 0
3


0 0
13


3 4

0 0
777777770001


0 0
```

### 输出

```
second


first
2 1


first
10 7

1 2


first
777777770000 1
```



---

---
title: "Nene and the Mex Operator"
layout: "post"
diff: 提高+/省选-
pid: CF1956D
tag: ['动态规划 DP', '构造']
---

# Nene and the Mex Operator

## 题目描述

Nene gave you an array of integers $ a_1, a_2, \ldots, a_n $ of length $ n $ .

You can perform the following operation no more than $ 5\cdot 10^5 $ times (possibly zero):

- Choose two integers $ l $ and $ r $ such that $ 1 \le l \le r \le n $ , compute $ x $ as $ \operatorname{MEX}(\{a_l, a_{l+1}, \ldots, a_r\}) $ , and simultaneously set $ a_l:=x, a_{l+1}:=x, \ldots, a_r:=x $ .

Here, $ \operatorname{MEX} $ of a set of integers $ \{c_1, c_2, \ldots, c_k\} $ is defined as the smallest non-negative integer $ m $ which does not occur in the set $ c $ .

Your goal is to maximize the sum of the elements of the array $ a $ . Find the maximum sum and construct a sequence of operations that achieves this sum. Note that you don't need to minimize the number of operations in this sequence, you only should use no more than $ 5\cdot 10^5 $ operations in your solution.

## 输入格式

The first line contains an integer $ n $ ( $ 1 \le n \le 18 $ ) — the length of the array $ a $ .

The second line contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 0\leq a_i \leq 10^7 $ ) — the array $ a $ .

## 输出格式

In the first line, output two integers $ s $ and $ m $ ( $ 0\le m\le 5\cdot 10^5 $ ) — the maximum sum of elements of the array $ a $ and the number of operations in your solution.

In the $ i $ -th of the following $ m $ lines, output two integers $ l $ and $ r $ ( $ 1 \le l \le r \le n $ ), representing the parameters of the $ i $ -th operation.

It can be shown that the maximum sum of elements of the array $ a $ can always be obtained in no more than $ 5 \cdot 10^5 $ operations.

## 说明/提示

In the first example, after the operation with $ l=1 $ and $ r=2 $ the array $ a $ becomes equal to $ [2,2] $ . It can be shown that it is impossible to achieve a larger sum of the elements of $ a $ , so the answer is $ 4 $ .

In the second example, the initial sum of elements is $ 13 $ which can be shown to be the largest.

In the third example, the array $ a $ changes as follows:

- after the first operation ( $ l=3 $ , $ r=3 $ ), the array $ a $ becomes equal to $ [1,100,0,1] $ ;
- after the second operation ( $ l=3 $ , $ r=4 $ ), the array $ a $ becomes equal to $ [1,100,2,2] $ .

It can be shown that it is impossible to achieve a larger sum of the elements of $ a $ , so the answer is $ 105 $ .

## 样例 #1

### 输入

```
2
0 1
```

### 输出

```
4 1
1 2
```

## 样例 #2

### 输入

```
3
1 3 9
```

### 输出

```
13 0
```

## 样例 #3

### 输入

```
4
1 100 2 1
```

### 输出

```
105 2
3 3
3 4
```

## 样例 #4

### 输入

```
1
0
```

### 输出

```
1 1
1 1
```



---

---
title: "Exact Neighbours (Hard)"
layout: "post"
diff: 提高+/省选-
pid: CF1970B3
tag: ['构造']
---

# Exact Neighbours (Hard)

## 题目描述

在最近食死徒对霍格华兹城堡发动了一些袭击之后，凤凰社决定将 $n$ 个成员安置在霍格迈德村。这些房子将坐落在一片风景如画的正方形场地上。每个巫师都有自己的房子，每个房子都属于某个巫师。每栋房子将占据一个正方形的空间。

然而，正如你可能知道的，巫师是非常迷信的。在周末，每个巫师 $i$ 都想参观距离自己房子$a_i$（$0 \leq a_i \leq n$）的房子。

村里的道路是水平和垂直修建的，因此点（$x_i，y_i$）和（$x_j，y_j$）之间的距离在 $n \times n$ 域上是$   |x_{i} - x_{j}| + |y_{i} - y_{j}| $ 。巫师们相互了解和信任，所以当第二个巫师不在时，一个巫师可以去另一个巫师的家。建造的房子将会足够大，所有 $n$ 个巫师都可以同时参观任何房子。

除此之外，每个巫师都必须能看到北边的霍格沃茨城堡和南边的禁林，所以其他巫师的房子不应该挡住视线。就村庄而言，这意味着在 $n \times n$ 域的每一列中，最多可以有一个房子，所以如果第 $i$ 个房子有坐标$（x_i，y_i）$，那么对于所有 $i$ 不等于 $j$ ，都有 $x_i \neq x_j$。

凤凰社还不知道是否有可能以这样的方式放置 $n$ 栋房子，以满足所有 $n$ 位巫师的参观和景观要求，所以他们请求您帮助设计这样的计划。

如果可以有一个正确的位置，其中第 $i$ 个向导的房子离它有 $a_i$ 的距离，而第 $i$ 个巫师的房子是他们列中唯一的房子，输出 $YES$，每个巫师的房子的位置，以及每个巫师周末应该去哪个向导的房子。

如果无法正确放置，则输出 $NO$。

## 输入格式

第一行包含 $n$ （$2 \leq n \leq 2 \times 10^5$），即要建造的房屋数量。

第二行包含从 $a_1$ 到 $a_n$ 的n个整数。（$0 \leq a_i \leq n$）

## 输出格式

如果存在这样的放置，则在第一行输出 $YES$ ；否则，输出 $NO$ 。

如果答案是 $YES$，则输出 $n+1$ 行描述放置的内容。



接下来的 $n$ 行应该包含每个巫师的房屋 $1 \leq x_i，y_i \leq n$ 的位置。



最后一行的第 $i$ 个元素应该包含巫师的索引，其房屋与第 $i$ 个巫师的房屋正好相距 $a_i$。如果有多个这样的巫师，你可以输出任何一个。



如果有多个房屋放置方式，你可以输出任意一个。

## 样例 #1

### 输入

```
4
0 4 2 4
```

### 输出

```
YES
4 4
1 3
2 4
3 1
1 1 1 3
```

## 样例 #2

### 输入

```
4
1 3 0 1
```

### 输出

```
YES
2 1
4 1
1 1
3 1
3 3 3 1
```



---

---
title: "Choose Your Queries"
layout: "post"
diff: 提高+/省选-
pid: CF2025F
tag: ['图论', '构造']
---

# Choose Your Queries

## 题目描述

You are given an array $ a $ , consisting of $ n $ integers (numbered from $ 1 $ to $ n $ ). Initially, they are all zeroes.

You have to process $ q $ queries. The $ i $ -th query consists of two different integers $ x_i $ and $ y_i $ . During the $ i $ -th query, you have to choose an integer $ p $ (which is either $ x_i $ or $ y_i $ ) and an integer $ d $ (which is either $ 1 $ or $ -1 $ ), and assign $ a_p = a_p + d $ .

After each query, every element of $ a $ should be a non-negative integer.

Process all queries in such a way that the sum of all elements of $ a $ after the last query is the minimum possible.

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 2 \le n \le 3 \cdot 10^5 $ ; $ 1 \le q \le 3 \cdot 10^5 $ ) — the number of elements in $ a $ and the number of queries, respectively.

Then $ q $ lines follow. The $ i $ -th of these lines contains two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i, y_i \le n $ ; $ x_i \ne y_i $ ) — the description of the $ i $ -th query.

## 输出格式

For each query, print a line containing two characters:

- the first character should be x if you choose $ p=x_i $ , or y if you choose $ p=y_i $ ;
- the second character should be + if you choose $ d=1 $ , or - if you choose $ d=-1 $ .

If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
3 4
1 2
3 2
3 1
1 2
```

### 输出

```
y+
x+
x-
y-
```

## 样例 #2

### 输入

```
4 4
1 2
2 3
3 4
3 2
```

### 输出

```
y+
y+
x-
y-
```

## 样例 #3

### 输入

```
4 2
2 1
4 3
```

### 输出

```
y+
x+
```



---

---
title: "Roman and Numbers"
layout: "post"
diff: 提高+/省选-
pid: CF401D
tag: ['动态规划 DP', '枚举', '状态合并', '进制', '构造']
---

# Roman and Numbers

## 题目描述

Roman is a young mathematician, very famous in Uzhland. Unfortunately, Sereja doesn't think so. To make Sereja change his mind, Roman is ready to solve any mathematical problem. After some thought, Sereja asked Roma to find, how many numbers are close to number $ n $ , modulo $ m $ .

Number $ x $ is considered close to number $ n $ modulo $ m $ , if:

- it can be obtained by rearranging the digits of number $ n $ ,
- it doesn't have any leading zeroes,
- the remainder after dividing number $ x $ by $ m $ equals 0.

Roman is a good mathematician, but the number of such numbers is too huge for him. So he asks you to help him.

## 输入格式

The first line contains two integers: $ n $ $ (1<=n&lt;10^{18}) $ and $ m $ $ (1<=m<=100) $ .

## 输出格式

In a single line print a single integer — the number of numbers close to number $ n $ modulo $ m $ .

## 说明/提示

In the first sample the required numbers are: 104, 140, 410.

In the second sample the required number is 232.

## 样例 #1

### 输入

```
104 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
223 4

```

### 输出

```
1

```

## 样例 #3

### 输入

```
7067678 8

```

### 输出

```
47

```



---

---
title: "Prime Problem"
layout: "post"
diff: 提高+/省选-
pid: CF45G
tag: ['数学', '素数判断,质数,筛法', '构造']
---

# Prime Problem

## 题目描述

In Berland prime numbers are fashionable — the respectable citizens dwell only on the floors with numbers that are prime numbers. The numismatists value particularly high the coins with prime nominal values. All the prime days are announced holidays!

Yet even this is not enough to make the Berland people happy. On the main street of the capital stand $ n $ houses, numbered from 1 to $ n $ . The government decided to paint every house a color so that the sum of the numbers of the houses painted every color is a prime number.

However it turned out that not all the citizens approve of this decision — many of them protest because they don't want many colored houses on the capital's main street. That's why it is decided to use the minimal possible number of colors. The houses don't have to be painted consecutively, but every one of $ n $ houses should be painted some color. The one-colored houses should not stand consecutively, any way of painting is acceptable.

There are no more than 5 hours left before the start of painting, help the government find the way when the sum of house numbers for every color is a prime number and the number of used colors is minimal.

## 输入格式

The single input line contains an integer $ n $ ( $ 2<=n<=6000 $ ) — the number of houses on the main streets of the capital.

## 输出格式

Print the sequence of $ n $ numbers, where the $ i $ -th number stands for the number of color for house number $ i $ . Number the colors consecutively starting from 1. Any painting order is allowed. If there are several solutions to that problem, print any of them. If there's no such way of painting print the single number -1.

## 样例 #1

### 输入

```
8
```

### 输出

```
1 2 2 1 1 1 1 2
```



---

---
title: "Interesting Array"
layout: "post"
diff: 提高+/省选-
pid: CF482B
tag: ['线段树', '进制', '构造']
---

# Interesting Array

## 题目描述

We'll call an array of $ n $ non-negative integers $ a\[1\],a\[2\],...,a\[n\] $ interesting, if it meets $ m $ constraints. The $ i $ -th of the $ m $ constraints consists of three integers $ l_{i} $ , $ r_{i} $ , $ q_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ) meaning that value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF482B/c5cfeb39e6b942f975aeab6674c1941b58030e74.png) should be equal to $ q_{i} $ .

Your task is to find any interesting array of $ n $ elements or state that such array doesn't exist.

Expression $ x&y $ means the bitwise AND of numbers $ x $ and $ y $ . In programming languages C++, Java and Python this operation is represented as "&", in Pascal — as "and".

## 输入格式

We'll call an array of $ n $ non-negative integers $ a\[1\],a\[2\],...,a\[n\] $ interesting, if it meets $ m $ constraints. The $ i $ -th of the $ m $ constraints consists of three integers $ l_{i} $ , $ r_{i} $ , $ q_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ) meaning that value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF482B/c5cfeb39e6b942f975aeab6674c1941b58030e74.png) should be equal to $ q_{i} $ .

Your task is to find any interesting array of $ n $ elements or state that such array doesn't exist.

Expression $ x&y $ means the bitwise AND of numbers $ x $ and $ y $ . In programming languages C++, Java and Python this operation is represented as "&", in Pascal — as "and".

## 输出格式

We'll call an array of $ n $ non-negative integers $ a\[1\],a\[2\],...,a\[n\] $ interesting, if it meets $ m $ constraints. The $ i $ -th of the $ m $ constraints consists of three integers $ l_{i} $ , $ r_{i} $ , $ q_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ) meaning that value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF482B/c5cfeb39e6b942f975aeab6674c1941b58030e74.png) should be equal to $ q_{i} $ .

Your task is to find any interesting array of $ n $ elements or state that such array doesn't exist.

Expression $ x&y $ means the bitwise AND of numbers $ x $ and $ y $ . In programming languages C++, Java and Python this operation is represented as "&", in Pascal — as "and".

## 样例 #1

### 输入

```
3 1
1 3 3

```

### 输出

```
YES
3 3 3

```

## 样例 #2

### 输入

```
3 2
1 3 3
1 3 2

```

### 输出

```
NO

```



---

---
title: "Restoring Increasing Sequence"
layout: "post"
diff: 提高+/省选-
pid: CF490E
tag: ['字符串', '枚举', '构造']
---

# Restoring Increasing Sequence

## 题目描述

Peter wrote on the board a strictly increasing sequence of positive integers $ a_{1},a_{2},...,a_{n} $ . Then Vasil replaced some digits in the numbers of this sequence by question marks. Thus, each question mark corresponds to exactly one lost digit.

Restore the the original sequence knowing digits remaining on the board.

## 输入格式

The first line of the input contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the length of the sequence. Next $ n $ lines contain one element of the sequence each. Each element consists only of digits and question marks. No element starts from digit 0. Each element has length from 1 to 8 characters, inclusive.

## 输出格式

If the answer exists, print in the first line "YES" (without the quotes). Next $ n $ lines must contain the sequence of positive integers — a possible variant of Peter's sequence. The found sequence must be strictly increasing, it must be transformed from the given one by replacing each question mark by a single digit. All numbers on the resulting sequence must be written without leading zeroes. If there are multiple solutions, print any of them.

If there is no answer, print a single line "NO" (without the quotes).

## 样例 #1

### 输入

```
3
?
18
1?

```

### 输出

```
YES
1
18
19

```

## 样例 #2

### 输入

```
2
??
?

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
5
12224
12??5
12226
?0000
?00000

```

### 输出

```
YES
12224
12225
12226
20000
100000

```



---

---
title: "Wet Shark and Blocks"
layout: "post"
diff: 提高+/省选-
pid: CF621E
tag: ['动态规划 DP', '矩阵乘法', '构造']
---

# Wet Shark and Blocks

## 题目描述

有 $b$ 个格子，每个格子有 $n$ 个数字，各个格子里面的数字都是相同的. 求从 $b$ 个格子中各取一个数字, 构成一个 $b$ 位数, 使得这个 $b$ 位数模 $x$ 为 $k$ 的方案数（同一格子内相同的数字算不同方案）.答案对 $1\times 10^9+7$ 取模.

## 输入格式

第一行有4个整数 $n,b,k,x$ ,其中 $2\leq n\leq 50000,1\leq b\leq 10^{9},0\leq k< x\leq 100,x\ge2$ 
第二行有 $n$ 个数, 为每个格子里面的数字(每个格子里面的数字都是相同的.)

## 输出格式

即从每个块中选择一个数构成一个大数, 使得其模x为k的方案数对 $1\times 10^9+7$ 取模.
注意:

样例二中没有一种方案使得模2为1
样例三中11,13,21,23,31,33满足模2余1.

感谢@aiyougege 提供的翻译

## 样例 #1

### 输入

```
12 1 5 10
3 5 6 7 8 9 5 1 1 1 1 5

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3 2 1 2
6 2 2

```

### 输出

```
0

```

## 样例 #3

### 输入

```
3 2 1 2
3 1 2

```

### 输出

```
6

```



---

---
title: "Innokenty and a Football League"
layout: "post"
diff: 提高+/省选-
pid: CF780D
tag: ['字符串', '贪心', '构造']
---

# Innokenty and a Football League

## 题目描述

Innokenty is a president of a new football league in Byteland. The first task he should do is to assign short names to all clubs to be shown on TV next to the score. Of course, the short names should be distinct, and Innokenty wants that all short names consist of three letters.

Each club's full name consist of two words: the team's name and the hometown's name, for example, "DINAMO BYTECITY". Innokenty doesn't want to assign strange short names, so he wants to choose such short names for each club that:

1. the short name is the same as three first letters of the team's name, for example, for the mentioned club it is "DIN",
2. or, the first two letters of the short name should be the same as the first two letters of the team's name, while the third letter is the same as the first letter in the hometown's name. For the mentioned club it is "DIB".

Apart from this, there is a rule that if for some club $ x $ the second option of short name is chosen, then there should be no club, for which the first option is chosen which is the same as the first option for the club $ x $ . For example, if the above mentioned club has short name "DIB", then no club for which the first option is chosen can have short name equal to "DIN". However, it is possible that some club have short name "DIN", where "DI" are the first two letters of the team's name, and "N" is the first letter of hometown's name. Of course, no two teams can have the same short name.

Help Innokenty to choose a short name for each of the teams. If this is impossible, report that. If there are multiple answer, any of them will suit Innokenty. If for some team the two options of short name are equal, then Innokenty will formally think that only one of these options is chosen.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=1000 $ ) — the number of clubs in the league.

Each of the next $ n $ lines contains two words — the team's name and the hometown's name for some club. Both team's name and hometown's name consist of uppercase English letters and have length at least $ 3 $ and at most $ 20 $ .

## 输出格式

It it is not possible to choose short names and satisfy all constraints, print a single line "NO".

Otherwise, in the first line print "YES". Then print $ n $ lines, in each line print the chosen short name for the corresponding club. Print the clubs in the same order as they appeared in input.

If there are multiple answers, print any of them.

## 说明/提示

In the first sample Innokenty can choose first option for both clubs.

In the second example it is not possible to choose short names, because it is not possible that one club has first option, and the other has second option if the first options are equal for both clubs.

In the third example Innokenty can choose the second options for the first two clubs, and the first option for the third club.

In the fourth example note that it is possible that the chosen short name for some club $ x $ is the same as the first option of another club $ y $ if the first options of $ x $ and $ y $ are different.

## 样例 #1

### 输入

```
2
DINAMO BYTECITY
FOOTBALL MOSCOW

```

### 输出

```
YES
DIN
FOO

```

## 样例 #2

### 输入

```
2
DINAMO BYTECITY
DINAMO BITECITY

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
3
PLAYFOOTBALL MOSCOW
PLAYVOLLEYBALL SPB
GOGO TECHNOCUP

```

### 输出

```
YES
PLM
PLS
GOG

```

## 样例 #4

### 输入

```
3
ABC DEF
ABC EFG
ABD OOO

```

### 输出

```
YES
ABD
ABE
ABO

```



---

---
title: "Largest Beautiful Number"
layout: "post"
diff: 提高+/省选-
pid: CF946E
tag: ['字符串', '枚举', '构造']
---

# Largest Beautiful Number

## 题目描述

如果一个正整数在十进制表示法下，不含前导零，有偶数个数字，并且对于它的所有数字来说，有一种排列方式使得这些数字组成一个回文数，那么这个数就是“美丽数”。例如4242是一个美丽数，因为它含有4个数字，这4个数字可以组成一个回文数2442。

给定一个正整数s，求严格小于s的最大美丽数。

## 输入格式

第1行，1个整数t，表示数据组数。

下面t行，每行1个十进制数s。

## 输出格式

对于每个s，输出严格小于s的最大美丽数。

数据保证有解。

## 说明/提示

t <= 10^5 
 

s的长度<= 2*10^5 

感谢@刷题永动机 提供的翻译

## 样例 #1

### 输入

```
4
89
88
1000
28923845

```

### 输出

```
88
77
99
28923839

```



---

---
title: "A Mist of Florescence"
layout: "post"
diff: 提高+/省选-
pid: CF989C
tag: ['连通块', '构造']
---

# A Mist of Florescence

## 题目描述

**题目大意：**

让你构造一个$n*m$矩阵，这个矩阵由4种字符填充构成，给定4个整数，即矩阵中每种字符构成的四联通块个数，$n,m$需要你自己定，但是不能超过50

## 输入格式

一行，四个整数$a,b,c,d$，即每种字符构成的四联通块个数，$1<=a,b,c,d<=100$

## 输出格式

一个矩阵

感谢@守望 提供翻译

## 样例 #1

### 输入

```
5 3 2 1

```

### 输出

```
4 7
DDDDDDD
DABACAD
DBABACD
DDDDDDD
```

## 样例 #2

### 输入

```
50 50 1 1

```

### 输出

```
4 50
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
ABABABABABABABABABABABABABABABABABABABABABABABABAB
BABABABABABABABABABABABABABABABABABABABABABABABABA
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
```

## 样例 #3

### 输入

```
1 6 4 5

```

### 输出

```
7 7
DDDDDDD
DDDBDBD
DDCDCDD
DBDADBD
DDCDCDD
DBDBDDD
DDDDDDD
```



---

---
title: "Flow Control"
layout: "post"
diff: 提高+/省选-
pid: CF990F
tag: ['模拟', '构造']
---

# Flow Control

## 题目描述

You have to handle a very complex water distribution system. The system consists of $ n $ junctions and $ m $ pipes, $ i $ -th pipe connects junctions $ x_i $ and $ y_i $ .

The only thing you can do is adjusting the pipes. You have to choose $ m $ integer numbers $ f_1 $ , $ f_2 $ , ..., $ f_m $ and use them as pipe settings. $ i $ -th pipe will distribute $ f_i $ units of water per second from junction $ x_i $ to junction $ y_i $ (if $ f_i $ is negative, then the pipe will distribute $ |f_i| $ units of water per second from junction $ y_i $ to junction $ x_i $ ). It is allowed to set $ f_i $ to any integer from $ -2 \cdot 10^9 $ to $ 2 \cdot 10^9 $ .

In order for the system to work properly, there are some constraints: for every $ i \in [1, n] $ , $ i $ -th junction has a number $ s_i $ associated with it meaning that the difference between incoming and outcoming flow for $ i $ -th junction must be exactly $ s_i $ (if $ s_i $ is not negative, then $ i $ -th junction must receive $ s_i $ units of water per second; if it is negative, then $ i $ -th junction must transfer $ |s_i| $ units of water per second to other junctions).

Can you choose the integers $ f_1 $ , $ f_2 $ , ..., $ f_m $ in such a way that all requirements on incoming and outcoming flows are satisfied?

## 输入格式

The first line contains an integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of junctions.

The second line contains $ n $ integers $ s_1, s_2, \dots, s_n $ ( $ -10^4 \le s_i \le 10^4 $ ) — constraints for the junctions.

The third line contains an integer $ m $ ( $ 0 \le m \le 2 \cdot 10^5 $ ) — the number of pipes.

 $ i $ -th of the next $ m $ lines contains two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i, y_i \le n $ , $ x_i \ne y_i $ ) — the description of $ i $ -th pipe. It is guaranteed that each unordered pair $ (x, y) $ will appear no more than once in the input (it means that there won't be any pairs $ (x, y) $ or $ (y, x) $ after the first occurrence of $ (x, y) $ ). It is guaranteed that for each pair of junctions there exists a path along the pipes connecting them.

## 输出格式

If you can choose such integer numbers $ f_1, f_2, \dots, f_m $ in such a way that all requirements on incoming and outcoming flows are satisfied, then output "Possible" in the first line. Then output $ m $ lines, $ i $ -th line should contain $ f_i $ — the chosen setting numbers for the pipes. Pipes are numbered in order they appear in the input.

Otherwise output "Impossible" in the only line.

## 样例 #1

### 输入

```
4
3 -10 6 1
5
1 2
3 2
2 4
3 4
3 1

```

### 输出

```
Possible
4
-6
8
-7
7

```

## 样例 #2

### 输入

```
4
3 -10 6 4
5
1 2
3 2
2 4
3 4
3 1

```

### 输出

```
Impossible

```



---

