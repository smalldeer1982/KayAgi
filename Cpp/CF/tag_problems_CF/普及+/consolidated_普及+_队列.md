---
title: "Maximize the Remaining String"
layout: "post"
diff: 普及+/提高
pid: CF1506G
tag: ['贪心', '单调队列']
---

# Maximize the Remaining String

## 题目描述

给你一个由小写英文字母组成的字符串 $s$，你需要去掉一部分字符，使得操作后得到的字符串 $t$ 满足在 $s$ 中出现的字母每种只保留一个并且最大化 $t$ 的字典序。

## 输入格式

多测
第一行一个正整数 $T$（$1\le T\le 10^4$）表示数据组数。  
接下来 $T$ 行，每行一个由小写字母组成的字符串 $s$（$\sum|s|\le 2\times 10^5$）。

## 输出格式

输出 $T$ 行  
对于每组输入的 $s$，输出一行一个字符串表示满足要求且字典序最大的 $t$。

## 样例 #1

### 输入

```
6
codeforces
aezakmi
abacaba
convexhull
swflldjgpaxs
myneeocktxpqjpz
```

### 输出

```
odfrces
ezakmi
cba
convexhul
wfldjgpaxs
myneocktxqjpz
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
title: "Rudolf and k Bridges"
layout: "post"
diff: 普及+/提高
pid: CF1941E
tag: ['动态规划 DP', '单调队列']
---

# Rudolf and k Bridges

## 题目描述

Bernard loves visiting Rudolf, but he is always running late. The problem is that Bernard has to cross the river on a ferry. Rudolf decided to help his friend solve this problem.

The river is a grid of $ n $ rows and $ m $ columns. The intersection of the $ i $ -th row and the $ j $ -th column contains the number $ a_{i,j} $ — the depth in the corresponding cell. All cells in the first and last columns correspond to the river banks, so the depth for them is $ 0 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1941E/2420e4ab48e7eae57737cc3a1dbfde24de284901.png) The river may look like this.Rudolf can choose the row $ (i,1), (i,2), \ldots, (i,m) $ and build a bridge over it. In each cell of the row, he can install a support for the bridge. The cost of installing a support in the cell $ (i,j) $ is $ a_{i,j}+1 $ . Supports must be installed so that the following conditions are met:

1. A support must be installed in cell $ (i,1) $ ;
2. A support must be installed in cell $ (i,m) $ ;
3. The distance between any pair of adjacent supports must be no more than $ d $ . The distance between supports $ (i, j_1) $ and $ (i, j_2) $ is $ |j_1 - j_2| - 1 $ .

Building just one bridge is boring. Therefore, Rudolf decided to build $ k $ bridges on consecutive rows of the river, that is, to choose some $ i $ ( $ 1 \le i \le n - k + 1 $ ) and independently build a bridge on each of the rows $ i, i + 1, \ldots, i + k - 1 $ . Help Rudolf minimize the total cost of installing supports.

## 输入格式

The first line contains a single integer $ t $ $ (1 \le t \le 10^3) $ — the number of test cases. The descriptions of the test cases follow.

The first line of each test case contains four integers $ n $ , $ m $ , $ k $ , and $ d $ ( $ 1 \le k \le n \le 100 $ , $ 3 \le m \le 2 \cdot 10^5 $ , $ 1 \le d \le m $ ) — the number of rows and columns of the field, the number of bridges, and the maximum distance between supports.

Then follow $ n $ lines, $ i $ -th line contains $ m $ positive integers $ a_{i, j} $ ( $ 0 \le a_{i, j} \le 10^6 $ , $ a_{i, 1} = a_{i, m} = 0 $ ) — the depths of the river cells.

It is guaranteed that the sum of $ n \cdot m $ for all sets of input data does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single number — the minimum total cost of supports installation.

## 说明/提示

In the first test case, it is most profitable to build a bridge on the second row.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1941E/7ad474029f5a4a6573b004238d770f23ae9fe42a.png) It is not a top view, but side view: gray cells — bridge itself, white cells are empty, black cells — supports, blue cells — water, brown cells — river bottom.In the second test case, it is most profitable to build bridges on the second and third rows. The supports will be placed in cells $ (2, 3) $ , $ (3, 2) $ , and on the river banks.

In the third test case the supports can be placed along the river banks.

## 样例 #1

### 输入

```
5
3 11 1 4
0 1 2 3 4 5 4 3 2 1 0
0 1 2 3 2 1 2 3 3 2 0
0 1 2 3 5 5 5 5 5 2 0
4 4 2 1
0 3 3 0
0 2 1 0
0 1 2 0
0 3 3 0
4 5 2 5
0 1 1 1 0
0 2 2 2 0
0 2 1 1 0
0 3 2 1 0
1 8 1 1
0 10 4 8 4 4 2 0
4 5 3 2
0 8 4 4 0
0 3 4 8 0
0 8 1 10 0
0 10 1 5 0
```

### 输出

```
4
8
4
15
14
```



---

---
title: "Selection Sort"
layout: "post"
diff: 普及+/提高
pid: CF2041M
tag: ['贪心', '优先队列']
---

# Selection Sort

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2041M/d5dc69f2c95d765850bbfc6e16bfc04c742abf70.png)Every student enrolled in the algorithms course is required to submit an assignment this week. The task is to implement an $ O(n^2) $ -time algorithm to sort $ n $ given integers in non-decreasing order. Alice has already completed her assignment, and her implementation is shown below.

```
<pre class="lstlisting">```
int alice_sort(int *s, int n){<br></br>  for(int i = 0; i < n; ++i){<br></br>    for(int j = i + 1; j < n; ++j){<br></br>      if(s[i] > s[j]){<br></br>        int swap = s[i];<br></br>        s[i] = s[j];<br></br>        s[j] = swap;<br></br>      }<br></br>    }<br></br>  }<br></br>  return 0;<br></br>}<br></br>
```
```

While you have access to Alice's code, you prefer not to simply copy it. Instead, you want to use Alice's sorting function as a building block for your own solution. There are two ways as listed below you can utilize her function, but each of them can be applied at most once. The order in which these two operations are invoked can be arbitrary.

- Prefix sort: choose a length $ i \in \{1, 2, \ldots, n\} $ and call $ \texttt{alicesort(}s, i\texttt{)} $ . This sorts the first $ i $ elements in the array $ s $ .
- Suffix sort: choose a length $ i \in \{1, 2, \ldots, n\} $ and call $ \texttt{alicesort(}s+n-i, i\texttt{)} $ . This sorts the last $ i $ elements in the array $ s $ .

Due to the time complexity of the sorting algorithm, the cost of performing either a prefix or suffix sort is $ i^2 $ , where $ i $ is the length of the chosen subarray. Your goal is to determine the minimum cost to sort the input array $ s $ of $ n $ integers in non-decreasing order using Alice's function, following the rules mentioned above.

For example, Let $ s=[3,2,5,5,4,1] $ . We can first perform a suffix sort of length $ 4 $ , and the array becomes $ [3,2,1,4,5,5] $ . Then, we perform a prefix sort of length $ 3 $ , and the array becomes $ [1,2,3,4,5,5] $ , which is a sorted array. The cost is $ 4^2+3^2=25 $ . Here is another example, let $ s=[4,3,2,1] $ . We can complete the sorting by performing only a prefix sort of length $ 4 $ , and the cost is $ 4^2=16 $ .

## 输入格式

The first line contains exactly one integer $ n $ which indicates the number of integers in the array $ s $ . The second line contains the $ n $ integers in $ s=[s_0, s_1, \ldots, s_{n-1}] $ .

- $ 1 \le n \le 10^6 $
- For all $ i $ ( $ 0\le i < n $ ), $ 0\le s_i < 2^{31}-1 $ .

## 输出格式

Output an integer on a line, indicating the minimum cost to sort the input array $ s $ of $ n $ integers in non-decreasing order using Alice's function, following the rules mentioned above.

## 样例 #1

### 输入

```
6
3 2 5 5 4 1
```

### 输出

```
25
```

## 样例 #2

### 输入

```
4
4 3 2 1
```

### 输出

```
16
```



---

---
title: "Canteen (Easy Version)"
layout: "post"
diff: 普及+/提高
pid: CF2089B1
tag: ['贪心', '单调队列']
---

# Canteen (Easy Version)

## 题目描述

这是该问题的简单版本。两个版本的区别在于此版本中，$$k=0$$。只有当你解决了该问题的所有版本时才能进行 hack。

Ecrade 有两个由整数构成的序列 $$$a_0, a_1, \ldots, a_{n - 1}$$$ 和 $$$b_0, b_1, \ldots, b_{n - 1}$$$。保证 $$$a$$$ 中所有元素的总和不超过 $$$b$$$ 中所有元素的总和。

初始时，Ecrade 可以对序列 $$$a$$$ 进行恰好 $$$k$$$ 次修改。保证 $$$k$$$ 不超过 $$$a$$$ 的总和。每次修改操作如下：
- 选择一个整数 $$$i$$$（$$0 \le i < n$$）满足 $$$a\_i > 0$$$，并执行 $$$a_i := a_i - 1$$$。

然后，Ecrade 将对 $$$a$$$ 和 $$$b$$$ 依次执行以下三个操作，这三个操作构成一轮操作：
1. 对每个 $$$0 \le i < n$$$：$$t := \min(a_i, b_i)$$，$$a_i := a_i - t$$，$$b_i := b_i - t$$；
2. 对每个 $$$0 \le i < n$$$：$$c_i := a_{(i - 1) \bmod n}$$；
3. 对每个 $$$0 \le i < n$$$：$$a_i := c_i$$。

Ecrade 想知道，在对 $$$a$$$ 进行恰好 $$$k$$$ 次修改后，使得 $$$a$$$ 中所有元素变为 $$$0$$$ 所需的最小轮数。

然而，这似乎有些复杂，因此请帮助他！

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $$$t$$$（$$1 \le t \le 2 \cdot 10^4$$）。接下来是各测试用例的描述。

每个测试用例的第一行包含两个整数 $$$n$$$、$$k$$（$$1 \le n \le 2 \cdot 10^5$$，$$k = 0$$）。

每个测试用例的第二行包含 $$$n$$$ 个整数 $$$a\_0, a\_1, \ldots, a\_{n - 1}$$$（$$1 \le a_i \le 10^9$$）。

每个测试用例的第三行包含 $$$n$$$ 个整数 $$$b\_0, b\_1, \ldots, b\_{n - 1}$$$（$$1 \le b_i \le 10^9$$）。

保证所有测试用例的 $$$n$$$ 之和不超过 $$$2 \cdot 10^5$$$。同时保证每个测试用例中 $$$a$$$ 的总和不超过 $$$b$$$ 的总和，且 $$$k$$$ 不超过 $$$a$$$ 的总和。

## 输出格式

对于每个测试用例，输出在对 $$$a$$$ 进行恰好 $$$k$$$ 次修改后，使得 $$$a$$$ 中所有元素变为 $$0$$ 所需的最小轮数。


## 说明/提示

在此版本中，Ecrade 不能对 $$$a$$$ 进行修改。

在第一个测试用例中：
- 第一轮操作后，$$a=[0,0,0]$$，$$b=[4,0,0]$$。

在第二个测试用例中：
- 第一轮操作后，$$a=[3,0,0,1]$$，$$b=[3,1,0,0]$$；
- 第二轮操作后，$$a=[1,0,0,0]$$，$$b=[0,1,0,0]$$；
- 第三轮操作后，$$a=[0,1,0,0]$$，$$b=[0,1,0,0]$$；
- 第四轮操作后，$$a=[0,0,0,0]$$，$$b=[0,0,0,0]$$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
3 0
1 1 4
5 1 4
4 0
1 2 3 4
4 3 2 1
4 0
2 1 1 2
1 2 2 1
8 0
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
```

### 输出

```
1
4
4
8
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
title: "Washer, Dryer, Folder"
layout: "post"
diff: 普及+/提高
pid: CF452D
tag: ['队列']
---

# Washer, Dryer, Folder

## 题目描述

You have $ k $ pieces of laundry, each of which you want to wash, dry and fold. You are at a laundromat that has $ n_{1} $ washing machines, $ n_{2} $ drying machines and $ n_{3} $ folding machines. Each machine can process only one piece of laundry at a time. You can't dry a piece of laundry before it is washed, and you can't fold it before it is dried. Moreover, after a piece of laundry is washed, it needs to be immediately moved into a drying machine, and after it is dried, it needs to be immediately moved into a folding machine.

It takes $ t_{1} $ minutes to wash one piece of laundry in a washing machine, $ t_{2} $ minutes to dry it in a drying machine, and $ t_{3} $ minutes to fold it in a folding machine. Find the smallest number of minutes that is enough to wash, dry and fold all the laundry you have.

## 输入格式

The only line of the input contains seven integers: $ k,n_{1},n_{2},n_{3},t_{1},t_{2},t_{3} $ $ (1<=k<=10^{4}; 1<=n_{1},n_{2},n_{3},t_{1},t_{2},t_{3}<=1000) $ .

## 输出格式

Print one integer — smallest number of minutes to do all your laundry.

## 说明/提示

In the first example there's one instance of each machine, each taking 5 minutes to complete. You have only one piece of laundry, so it takes 15 minutes to process it.

In the second example you start washing first two pieces at moment $ 0 $ . If you start the third piece of laundry immediately, then by the time it is dried, there will be no folding machine available, so you have to wait, and start washing third piece at moment $ 2 $ . Similarly, you can't start washing next piece until moment $ 5 $ , since otherwise there will be no dryer available, when it is washed. Start time for each of the eight pieces of laundry is $ 0,0,2,5,10,10,12 $ and $ 15 $ minutes respectively. The last piece of laundry will be ready after $ 15+10+5+2=32 $ minutes.

## 样例 #1

### 输入

```
1 1 1 1 5 5 5

```

### 输出

```
15

```

## 样例 #2

### 输入

```
8 4 3 2 10 5 2

```

### 输出

```
32

```



---

---
title: "George and Job"
layout: "post"
diff: 普及+/提高
pid: CF467C
tag: ['动态规划 DP', '优先队列', '前缀和']
---

# George and Job

## 题目描述

新款手机 iTone6 近期上市，George 很想买一只。不幸地，George 没有足够的钱，所以 George 打算当一名程序猿去打工。现在George遇到了一个问题。
给出一组有 $n$ 个整数的数列 $p_1,p_2,...,p_n$ ,你需要挑出 $k$ 组长度为 $m$ 的数，要求这些数互不重叠
即$ [l_{1},r_{1}],[l_{2},r_{2}],...,[l_{k},r_{k}] (1<=l_{1}<=r_{1}<l_{2}<=r_{2}<...<l_{k}<=r_{k}<=n; r_{i}-l_{i}+1=m)$
使选出的数的和值最大，请你帮助George码出这份代码

## 输入格式

第1行读入3个整数 $n , m , k(1\leq(m×k)\leq n\leq5000) (1\leq(m×k)\leq n\leq5000)$,
第2行读入 $n$ 个数 $p_1,p_2,...,p_n$

## 输出格式

输出1个整数，代表可以取到的最大值
# 输入输出样例
如原版
translated by @Venus

## 样例 #1

### 输入

```
5 2 1
1 2 3 4 5

```

### 输出

```
9

```

## 样例 #2

### 输入

```
7 1 3
2 10 7 18 5 33 0

```

### 输出

```
61

```



---

---
title: "Closing ceremony"
layout: "post"
diff: 普及+/提高
pid: CF720A
tag: ['排序', '队列']
---

# Closing ceremony

## 题目描述

The closing ceremony of Squanch Code Cup is held in the big hall with $ n×m $ seats, arranged in $ n $ rows, $ m $ seats in a row. Each seat has two coordinates $ (x,y) $ ( $ 1<=x<=n $ , $ 1<=y<=m $ ).

There are two queues of people waiting to enter the hall: $ k $ people are standing at $ (0,0) $ and $ n·m-k $ people are standing at $ (0,m+1) $ . Each person should have a ticket for a specific seat. If person $ p $ at $ (x,y) $ has ticket for seat $ (x_{p},y_{p}) $ then he should walk $ |x-x_{p}|+|y-y_{p}| $ to get to his seat.

Each person has a stamina — the maximum distance, that the person agrees to walk. You should find out if this is possible to distribute all $ n·m $ tickets in such a way that each person has enough stamina to get to their seat.

## 输入格式

The first line of input contains two integers $ n $ and $ m $ ( $ 1<=n·m<=10^{4} $ ) — the size of the hall.

The second line contains several integers. The first integer $ k $ ( $ 0<=k<=n·m $ ) — the number of people at $ (0,0) $ . The following $ k $ integers indicate stamina of each person there.

The third line also contains several integers. The first integer $ l $ ( $ l=n·m-k $ ) — the number of people at $ (0,m+1) $ . The following $ l $ integers indicate stamina of each person there.

The stamina of the person is a positive integer less that or equal to $ n+m $ .

## 输出格式

If it is possible to distribute tickets between people in the described manner print "YES", otherwise print "NO".

## 样例 #1

### 输入

```
2 2
3 3 3 2
1 3

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
2 2
3 2 3 3
1 2

```

### 输出

```
NO

```



---

---
title: "Crunching Numbers Just for You"
layout: "post"
diff: 普及+/提高
pid: CF784F
tag: ['排序', '优先队列', '队列']
---

# Crunching Numbers Just for You

## 题目描述

你正在为销售机票的网站开发一项新功能：按能够对价格进行票分类照片你已经提取了票价，所以只有最后一步要做...

## 输出格式

记住，这是一个非常重要的功能，你必须确保顾客欣赏它！

Translated by @zhrzhrzhr

## 样例 #1

### 输入

```
3 3 1 2

```

### 输出

```
1 2 3 

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
title: "Coprocessor"
layout: "post"
diff: 普及+/提高
pid: CF909E
tag: ['排序', '拓扑排序', '队列']
---

# Coprocessor

## 题目描述

给你 $N$ 个任务，任务从 $0$ 开始标号，有些只能用主处理器处理，另外的任务只能用副处理器处理。其中存在 $M$ 个依赖关系，如果任务 $i$ 依赖于任务 $j$，那么称 $j$ 是 $i$ 的前继任务。

主处理器和副处理器都可以一次处理很多个任务。一个任务能被处理的条件为其所有的前继任务已经被执行过了，或者前继任务和自己同时被放进同一个处理器处理。


现在给出这些依赖关系和每个任务处理要用的处理器，求副处理器最少运行了几次。保证依赖关系是一张有向无环图。

## 输入格式

第一行输入两个非负整数 $N, M\ (1 \le N \le 10 ^ 5,\ 0 \le M \le 10 ^ 5)$。

接下来输入一行 $N$ 个整数 $E _ i\ (E _ i \in \{0, 1\})$，若 $E _ i = 0$ 则表示任务 $i$ 只能在主处理器上运行，否则其只能在副处理器上运行。

接下来 $M$ 行，每行两个非负整数 $T _ 1, T _ 2\ (0 \le T _ i < n,\ T _ 1 \ne T _ 2)$，表示任务 $T _ 1$ 依赖于任务 $T _ 2$。

## 输出格式

一行一个整数表示答案。

感谢 @Styx  提供的翻译。

## 样例 #1

### 输入

```
4 3
0 1 0 1
0 1
1 2
2 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4 3
1 1 1 0
0 1
0 2
3 0

```

### 输出

```
1

```



---

