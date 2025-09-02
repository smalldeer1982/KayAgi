---
title: "Sonya and Hotels"
layout: "post"
diff: 普及-
pid: CF1004A
tag: ['枚举', '概率论']
---

# Sonya and Hotels

## 题目描述

Sonya decided that having her own hotel business is the best way of earning money because she can profit and rest wherever she wants.

The country where Sonya lives is an endless line. There is a city in each integer coordinate on this line. She has $ n $ hotels, where the $ i $ -th hotel is located in the city with coordinate $ x_i $ . Sonya is a smart girl, so she does not open two or more hotels in the same city.

Sonya understands that her business needs to be expanded by opening new hotels, so she decides to build one more. She wants to make the minimum distance from this hotel to all others to be equal to $ d $ . The girl understands that there are many possible locations to construct such a hotel. Thus she wants to know the number of possible coordinates of the cities where she can build a new hotel.

Because Sonya is lounging in a jacuzzi in one of her hotels, she is asking you to find the number of cities where she can build a new hotel so that the minimum distance from the original $ n $ hotels to the new one is equal to $ d $ .

## 输入格式

The first line contains two integers $ n $ and $ d $ ( $ 1\leq n\leq 100 $ , $ 1\leq d\leq 10^9 $ ) — the number of Sonya's hotels and the needed minimum distance from a new hotel to all others.

The second line contains $ n $ different integers in strictly increasing order $ x_1, x_2, \ldots, x_n $ ( $ -10^9\leq x_i\leq 10^9 $ ) — coordinates of Sonya's hotels.

## 输出格式

Print the number of cities where Sonya can build a new hotel so that the minimum distance from this hotel to all others is equal to $ d $ .

## 说明/提示

In the first example, there are $ 6 $ possible cities where Sonya can build a hotel. These cities have coordinates $ -6 $ , $ 5 $ , $ 6 $ , $ 12 $ , $ 13 $ , and $ 19 $ .

In the second example, there are $ 5 $ possible cities where Sonya can build a hotel. These cities have coordinates $ 2 $ , $ 6 $ , $ 13 $ , $ 16 $ , and $ 21 $ .

## 样例 #1

### 输入

```
4 3
-3 2 9 16

```

### 输出

```
6

```

## 样例 #2

### 输入

```
5 2
4 8 11 18 19

```

### 输出

```
5

```



---

---
title: "Packets"
layout: "post"
diff: 普及-
pid: CF1037A
tag: ['数学', '枚举', '进制']
---

# Packets

## 题目描述

你有$n$个硬币，每个硬币价值都为$1$。

你要把它们分成若干个小包裹，使得在$1$与$n$之间的所有面额都能用这其中某几个小包裹凑出。

每个小包裹只能作为一个整体使用。

请求出最少要分几个包裹。

## 输入格式

一个数$n$($1\le n\le 10^9$)。

## 输出格式

输出最少要分几个包裹。

### 样例解释1：

分成$3$个包裹：$[1,2,3]$，可以凑出$1$到$6$中所有的面额。

## 样例 #1

### 输入

```
6

```

### 输出

```
3
```

## 样例 #2

### 输入

```
2

```

### 输出

```
2
```



---

---
title: "Heist"
layout: "post"
diff: 普及-
pid: CF1041A
tag: ['枚举', '排序', '概率论']
---

# Heist

## 题目描述

昨晚有一家电子商店被抢劫了。

昨天在商店里的所有键盘都是从$x$开始按升序编号的。例如，如果$x=4$，并且商店中有$3$个键盘，那么编号就为$4,5,6$；如果$x=10$，并且有$7$个键盘，那么编号就为$10,11,12,13,14,15,16$。

在抢劫之后，只有$n$个键盘仍然存在，他们的编号分别为$a_1,a_2,\dots ,a_n$。计算被盗的键盘的最小可能数量。工作人员不记得$x$也不记得商店里原来有几个键盘。

## 输入格式

第一行输入一个整数$n(1\le n\le 1000)$，为商店里仍然存在的键盘的数量。

第二行输入$n$个整数$a_1,a_2\dots ,a_n(1\le a_i\le 10^9)$，表示所有商店里仍然存在的键盘的编号。

## 输出格式

输出被盗的键盘的最小可能数量。

感谢@dblark 提供的翻译

## 样例 #1

### 输入

```
4
10 13 12 8

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5
7 5 6 4 8

```

### 输出

```
0

```



---

---
title: "Vitamins"
layout: "post"
diff: 普及-
pid: CF1042B
tag: ['枚举', '背包 DP', '状态合并']
---

# Vitamins

## 题目描述

Berland shop sells $ n $ kinds of juices. Each juice has its price $ c_i $ . Each juice includes some set of vitamins in it. There are three types of vitamins: vitamin "A", vitamin "B" and vitamin "C". Each juice can contain one, two or all three types of vitamins in it.

Petya knows that he needs all three types of vitamins to stay healthy. What is the minimum total price of juices that Petya has to buy to obtain all three vitamins? Petya obtains some vitamin if he buys at least one juice containing it and drinks it.

## 输入格式

The first line contains a single integer $ n $ $ (1 \le n \le 1\,000) $ — the number of juices.

Each of the next $ n $ lines contains an integer $ c_i $ $ (1 \le c_i \le 100\,000) $ and a string $ s_i $ — the price of the $ i $ -th juice and the vitamins it contains. String $ s_i $ contains from $ 1 $ to $ 3 $ characters, and the only possible characters are "A", "B" and "C". It is guaranteed that each letter appears no more than once in each string $ s_i $ . The order of letters in strings $ s_i $ is arbitrary.

## 输出格式

Print -1 if there is no way to obtain all three vitamins. Otherwise print the minimum total price of juices that Petya has to buy to obtain all three vitamins.

## 说明/提示

In the first example Petya buys the first, the second and the fourth juice. He spends $ 5 + 6 + 4 = 15 $ and obtains all three vitamins. He can also buy just the third juice and obtain three vitamins, but its cost is $ 16 $ , which isn't optimal.

In the second example Petya can't obtain all three vitamins, as no juice contains vitamin "C".

## 样例 #1

### 输入

```
4
5 C
6 B
16 BAC
4 A

```

### 输出

```
15

```

## 样例 #2

### 输入

```
2
10 AB
15 BA

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
5
10 A
9 BC
11 CA
4 A
5 B

```

### 输出

```
13

```

## 样例 #4

### 输入

```
6
100 A
355 BCA
150 BC
160 AC
180 B
190 CA

```

### 输出

```
250

```

## 样例 #5

### 输入

```
2
5 BA
11 CB

```

### 输出

```
16

```



---

---
title: "Forgery"
layout: "post"
diff: 普及-
pid: CF1059B
tag: ['枚举', '广度优先搜索 BFS']
---

# Forgery

## 题目描述

Student Andrey has been skipping physical education lessons for the whole term, and now he must somehow get a passing grade on this subject. Obviously, it is impossible to do this by legal means, but Andrey doesn't give up. Having obtained an empty certificate from a local hospital, he is going to use his knowledge of local doctor's handwriting to make a counterfeit certificate of illness. However, after writing most of the certificate, Andrey suddenly discovered that doctor's signature is impossible to forge. Or is it?

For simplicity, the signature is represented as an $ n\times m $ grid, where every cell is either filled with ink or empty. Andrey's pen can fill a $ 3\times3 $ square without its central cell if it is completely contained inside the grid, as shown below.

 `<br></br>xxx<br></br>x.x<br></br>xxx<br></br>`Determine whether is it possible to forge the signature on an empty $ n\times m $ grid.

## 输入格式

The first line of input contains two integers $ n $ and $ m $ ( $ 3 \le n, m \le 1000 $ ).

Then $ n $ lines follow, each contains $ m $ characters. Each of the characters is either '.', representing an empty cell, or '\#', representing an ink filled cell.

## 输出格式

If Andrey can forge the signature, output "YES". Otherwise output "NO".

You can print each letter in any case (upper or lower).

## 说明/提示

In the first sample Andrey can paint the border of the square with the center in $ (2, 2) $ .

In the second sample the signature is impossible to forge.

In the third sample Andrey can paint the borders of the squares with the centers in $ (2, 2) $ and $ (3, 2) $ :

1. we have a clear paper: `<br></br>...<br></br>...<br></br>...<br></br>...<br></br>`
2. use the pen with center at $ (2, 2) $ . `<br></br>###<br></br>#.#<br></br>###<br></br>...<br></br>`
3. use the pen with center at $ (3, 2) $ . `<br></br>###<br></br>###<br></br>###<br></br>###<br></br>`

In the fourth sample Andrey can paint the borders of the squares with the centers in $ (3, 3) $ and $ (3, 5) $ .

## 样例 #1

### 输入

```
3 3
###
#.#
###

```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3 3
###
###
###

```

### 输出

```
NO
```

## 样例 #3

### 输入

```
4 3
###
###
###
###

```

### 输出

```
YES
```

## 样例 #4

### 输入

```
5 7
.......
.#####.
.#.#.#.
.#####.
.......

```

### 输出

```
YES
```



---

---
title: "Diverse Substring"
layout: "post"
diff: 普及-
pid: CF1073A
tag: ['字符串', '枚举', '概率论']
---

# Diverse Substring

## 题目描述

You are given a string $ s $ , consisting of $ n $ lowercase Latin letters.

A substring of string $ s $ is a continuous segment of letters from $ s $ . For example, "defor" is a substring of "codeforces" and "fors" is not.

The length of the substring is the number of letters in it.

Let's call some string of length $ n $ diverse if and only if there is no letter to appear strictly more than $ \frac n 2 $ times. For example, strings "abc" and "iltlml" are diverse and strings "aab" and "zz" are not.

Your task is to find any diverse substring of string $ s $ or report that there is none. Note that it is not required to maximize or minimize the length of the resulting substring.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 1000 $ ) — the length of string $ s $ .

The second line is the string $ s $ , consisting of exactly $ n $ lowercase Latin letters.

## 输出格式

Print "NO" if there is no diverse substring in the string $ s $ .

Otherwise the first line should contain "YES". The second line should contain any diverse substring of string $ s $ .

## 说明/提示

The first example has lots of correct answers.

Please, restrain yourself from asking if some specific answer is correct for some specific test or not, these questions always lead to "No comments" answer.

## 样例 #1

### 输入

```
10
codeforces

```

### 输出

```
YES
code

```

## 样例 #2

### 输入

```
5
aaaaa

```

### 输出

```
NO

```



---

---
title: "Lucky Sum of Digits"
layout: "post"
diff: 普及-
pid: CF109A
tag: ['字符串', '贪心', '枚举']
---

# Lucky Sum of Digits

## 题目描述

Petya喜欢幸运数字。我们都知道幸运数字是只含有$4$ 和$7$ 的正整数。例如数字$47$ ，$744$ ，$4$ 是幸运数字，而$5$ ，$17$ ，$467$ 不是。

Petya急切的想知道各个数位上数字的和为$n$ 的最小幸运数字是多少。帮助他完成这个任务。

## 输入格式

一行一个整数$n$ （$1\leq n\leq 10^6$ ） — 要求的幸运数字各个数位上数字的和。

## 输出格式

输出仅一行为这个结果 — 这个最小的各数位上和为$n$ 的幸运数。如果这个数不存在输出-1。

感谢@Khassar 提供的翻译

## 样例 #1

### 输入

```
11

```

### 输出

```
47

```

## 样例 #2

### 输入

```
10

```

### 输出

```
-1

```



---

---
title: "Roman and Browser"
layout: "post"
diff: 普及-
pid: CF1100A
tag: ['枚举']
---

# Roman and Browser

## 题目描述

### 题目大意

给定一个长度为 $n$ 的只有 $1$ 和 $-1$ 的序列，选择一个位置 $b$，然后删掉位置为 $b+i\times k$ 的数（$i$ 为整数），求操作后 $1$ 和 $-1$ 数量之差的绝对值的最大值。

## 输入格式

第一行两个整数 $n,k$。

第二行 $n$ 个整数，每个数是 $1$ 或 $-1$。

## 输出格式

一个整数，表示最大绝对差值。

## 样例 #1

### 输入

```
4 2
1 1 -1 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
14 3
-1 1 -1 -1 1 -1 -1 1 -1 -1 1 -1 -1 1

```

### 输出

```
9

```



---

---
title: "Buying Shovels"
layout: "post"
diff: 普及-
pid: CF1360D
tag: ['数学', '数论', '枚举']
---

# Buying Shovels

## 题目描述

Polycarp wants to buy exactly $ n $ shovels. The shop sells packages with shovels. The store has $ k $ types of packages: the package of the $ i $ -th type consists of exactly $ i $ shovels ( $ 1 \le i \le k $ ). The store has an infinite number of packages of each type.

Polycarp wants to choose one type of packages and then buy several (one or more) packages of this type. What is the smallest number of packages Polycarp will have to buy to get exactly $ n $ shovels?

For example, if $ n=8 $ and $ k=7 $ , then Polycarp will buy $ 2 $ packages of $ 4 $ shovels.

Help Polycarp find the minimum number of packages that he needs to buy, given that he:

- will buy exactly $ n $ shovels in total;
- the sizes of all packages he will buy are all the same and the number of shovels in each package is an integer from $ 1 $ to $ k $ , inclusive.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le       100 $ ) — the number of test cases in the input. Then, $ t $ test cases follow, one per line.

Each test case consists of two positive integers $ n $ ( $ 1       \le n \le 10^9 $ ) and $ k $ ( $ 1 \le k \le 10^9 $ ) — the number of shovels and the number of types of packages.

## 输出格式

Print $ t $ answers to the test cases. Each answer is a positive integer — the minimum number of packages.

## 说明/提示

The answer to the first test case was explained in the statement.

In the second test case, there is only one way to buy $ 8 $ shovels — $ 8 $ packages of one shovel.

In the third test case, you need to buy a $ 1 $ package of $ 6 $ shovels.

## 样例 #1

### 输入

```
5
8 7
8 1
6 10
999999733 999999732
999999733 999999733
```

### 输出

```
2
8
1
999999733
1
```



---

---
title: "Division by Two and Permutation"
layout: "post"
diff: 普及-
pid: CF1624C
tag: ['枚举']
---

# Division by Two and Permutation

## 题目描述

You are given an array $ a $ consisting of $ n $ positive integers. You can perform operations on it.

In one operation you can replace any element of the array $ a_i $ with $ \lfloor \frac{a_i}{2} \rfloor $ , that is, by an integer part of dividing $ a_i $ by $ 2 $ (rounding down).

See if you can apply the operation some number of times (possible $ 0 $ ) to make the array $ a $ become a permutation of numbers from $ 1 $ to $ n $ —that is, so that it contains all numbers from $ 1 $ to $ n $ , each exactly once.

For example, if $ a = [1, 8, 25, 2] $ , $ n = 4 $ , then the answer is yes. You could do the following:

1. Replace $ 8 $ with $ \lfloor \frac{8}{2} \rfloor = 4 $ , then $ a = [1, 4, 25, 2] $ .
2. Replace $ 25 $ with $ \lfloor \frac{25}{2} \rfloor = 12 $ , then $ a = [1, 4, 12, 2] $ .
3. Replace $ 12 $ with $ \lfloor \frac{12}{2} \rfloor = 6 $ , then $ a = [1, 4, 6, 2] $ .
4. Replace $ 6 $ with $ \lfloor \frac{6}{2} \rfloor = 3 $ , then $ a = [1, 4, 3, 2] $ .

## 输入格式

The first line of input data contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) —the number of test cases.

Each test case contains exactly two lines. The first one contains an integer $ n $ ( $ 1 \le n \le 50 $ ), the second one contains integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ).

## 输出格式

For each test case, output on a separate line:

- YES if you can make the array $ a $ become a permutation of numbers from $ 1 $ to $ n $ ,
- NO otherwise.

You can output YES and NO in any case (for example, strings yEs, yes, Yes and YES will be recognized as a positive response).

## 说明/提示

The first test case is explained in the text of the problem statement.

In the second test case, it is not possible to get a permutation.

## 样例 #1

### 输入

```
6
4
1 8 25 2
2
1 1
9
9 8 3 4 2 7 1 5 6
3
8 2 1
4
24 7 16 7
5
22 6 22 4 22
```

### 输出

```
YES
NO
YES
NO
NO
YES
```



---

---
title: "Double Sort"
layout: "post"
diff: 普及-
pid: CF1681C
tag: ['枚举']
---

# Double Sort

## 题目描述

你被给予了两个数组 $a$ 和 $b$，他们都有 $n$ 个数子。

在一步中，你可以选择两个数 $i$ 和 $j(1 \leq i,j \leq n; i \ne j)$ 并交换 $a_i$、$a_j$ 和 $b_i$、$b_j$。你必须交换这两个数组。

你最多可以执行 $10^4$ 次交换操作（可能为零次）。你能使两个数组都排序成非递减顺序么？如果可以，请打印所有使两个数组都成非递减顺序的移动序列。

## 输入格式

第一行包含一个整数 $t(1 \leq t \leq 100)$ — 测试用例的数量。

每个测试用例的第一行包含一个整数 $n(2 \leq n \leq 100)$ — 两个数组中的元素数。

第二行包括 $n$ 个整数 $a_1,a_2......a_n(1 \leq a_i \leq n)$ — 第一个数组。

第三行包括 $n$ 个整数 $b_1,b_2......b_n(1 \leq b_i \leq n)$ — 第二个数组。

## 输出格式

对于每个测试用例，输出答案。如果不可能使两个数组以最多 $10^4$ 的非递减顺序排序，则输出 $-1$。否则，首先，打印移动次数 $k(0 \leq k \leq 10^4)$。然后打印每一步的 $i$ 和 $j(1≤i,j≤n ; i \neq j)$。

如果有多个答案，则打印其中任何一个。你不必尽量减少移动的次数。

## 样例 #1

### 输入

```
3
2
1 2
1 2
2
2 1
1 2
4
2 3 1 2
2 3 2 3
```

### 输出

```
0
-1
3
3 1
3 2
4 3
```



---

---
title: "Easy As ABC"
layout: "post"
diff: 普及-
pid: CF1906A
tag: ['枚举']
---

# Easy As ABC

## 题目描述

You are playing a word puzzle. The puzzle starts with a $ 3 $ by $ 3 $ grid, where each cell contains either the letter A, B, or C.

The goal of this puzzle is to find the lexicographically smallest possible word of length $ 3 $ . The word can be formed by choosing three different cells where the cell containing the first letter is adjacent to the cell containing the second letter, and the cell containing the second letter is adjacent to the cell containing the third letter.

Two cells are adjacent to each other if they share a border or a corner, as shown in the following illustration. Formally, if $ (r, c) $ denotes the cell in the $ r $ -th row and $ c $ -th column, then cell $ (r, c) $ is adjacent to cell $ (r, c + 1) $ , $ (r - 1, c + 1) $ , $ (r - 1, c) $ , $ (r - 1, c - 1) $ , $ (r, c - 1) $ , $ (r + 1, c - 1) $ , $ (r + 1, c) $ , and $ (r + 1, c + 1) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906A/525e4da2ea69e21f85179b7ddc65c24b70ec2325.png)Determine the lexicographically smallest possible word of length $ 3 $ that you can find within the grid.

A string $ s $ of length $ n $ is lexicographically smaller than string $ t $ of the same length if there exists an integer $ 1 \leq i \leq n $ such that $ s_j = t_j $ for all $ 1 \leq j < i $ , and $ s_i < t_i $ in alphabetical order. The following illustration shows some examples on some grids and their the lexicographically smallest possible word of length $ 3 $ that you can find within the grids.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906A/2e823a64da2250303d9d2bed5748864eed6f5643.png)

## 输入格式

Input consists of three lines, each containing three letters, representing the puzzle grid. Each letter in the grid can only be either A, B, or C.

## 输出格式

Output the lexicographically smallest possible word of length $ 3 $ that you can find within the grid.

## 样例 #1

### 输入

```
BCB
CAC
BCB
```

### 输出

```
ABC
```

## 样例 #2

### 输入

```
BCB
CCC
CCA
```

### 输出

```
ACB
```

## 样例 #3

### 输入

```
ACA
CBC
ACA
```

### 输出

```
ABA
```

## 样例 #4

### 输入

```
ACA
CAC
ACA
```

### 输出

```
AAA
```

## 样例 #5

### 输入

```
CCC
CBC
CCC
```

### 输出

```
BCC
```



---

---
title: "Quests"
layout: "post"
diff: 普及-
pid: CF1914C
tag: ['贪心', '枚举']
---

# Quests

## 题目描述

Monocarp is playing a computer game. In order to level up his character, he can complete quests. There are $ n $ quests in the game, numbered from $ 1 $ to $ n $ .

Monocarp can complete quests according to the following rules:

- the $ 1 $ -st quest is always available for completion;
- the $ i $ -th quest is available for completion if all quests $ j < i $ have been completed at least once.

Note that Monocarp can complete the same quest multiple times.

For each completion, the character gets some amount of experience points:

- for the first completion of the $ i $ -th quest, he gets $ a_i $ experience points;
- for each subsequent completion of the $ i $ -th quest, he gets $ b_i $ experience points.

Monocarp is a very busy person, so he has free time to complete no more than $ k $ quests. Your task is to calculate the maximum possible total experience Monocarp can get if he can complete no more than $ k $ quests.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le n \le 2 \cdot 10^5 $ ; $ 1 \le k \le 2 \cdot 10^5 $ ) — the number of quests and the maximum number of quests Monocarp can complete, respectively.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^3 $ ).

The third line contains $ n $ integers $ b_1, b_2, \dots, b_n $ ( $ 1 \le b_i \le 10^3 $ ).

Additional constraint on the input: the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print a single integer — the maximum possible total experience Monocarp can get if he can complete no more than $ k $ quests.

## 说明/提示

In the first test case, one of the possible quest completion sequences is as follows: $ 1, 1, 2, 3, 2, 4, 4 $ ; its total experience is equal to $ \underline{4} + 1 + \underline{3} + \underline{1} + 1 + \underline{2} + 1 = 13 $ (the underlined numbers correspond to the instances when we complete a quest for the first time).

In the second test case, one of the possible quest completion sequences is as follows: $ 1, 1 $ ; its total experience is equal to $ \underline{1} + 3 = 4 $ .

In the third test case, one of the possible quest completion sequences is as follows: $ 1, 2, 2, 2, 3 $ ; its total experience is equal to $ \underline{3} + \underline{2} + 3 + 3 + \underline{4} = 15 $ .

## 样例 #1

### 输入

```
4
4 7
4 3 1 2
1 1 1 1
3 2
1 2 5
3 1 8
5 5
3 2 4 1 4
2 3 1 4 7
6 4
1 4 5 4 5 10
1 5 1 2 5 1
```

### 输出

```
13
4
15
15
```



---

---
title: "Erase First or Second Letter"
layout: "post"
diff: 普及-
pid: CF1917B
tag: ['枚举']
---

# Erase First or Second Letter

## 题目描述

You are given a string $ s $ of length $ n $ . Let's define two operations you can apply on the string:

- remove the first character of the string;
- remove the second character of the string.

Your task is to find the number of distinct non-empty strings that can be generated by applying the given operations on the initial string any number of times (possibly zero), in any order.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains $ n $ ( $ 1 \leq n \leq 10^5 $ ) — the length of the string.

The second line of each test case contains the string $ s $ . It is guaranteed that the string only contains lowercase letters of the English alphabet.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer: the number of distinct non-empty strings you can get.

## 说明/提示

In the first test case, we can get the following strings: $ a $ , $ aa $ , $ aaa $ , $ aaaa $ , $ aaaaa $ .

In the third test case, for example, the word $ ba $ can be reached in the following way:

- remove the first character of the current string $ ababa $ , getting $ baba $ ;
- remove the second character of the current string $ baba $ , getting $ bba $ ;
- remove the second character of the current string $ bba $ , getting $ ba $ .

## 样例 #1

### 输入

```
5
5
aaaaa
1
z
5
ababa
14
bcdaaaabcdaaaa
20
abcdefghijklmnopqrst
```

### 输出

```
5
1
9
50
210
```



---

---
title: "Forming Triangles"
layout: "post"
diff: 普及-
pid: CF1922B
tag: ['枚举']
---

# Forming Triangles

## 题目描述

You have $ n $ sticks, numbered from $ 1 $ to $ n $ . The length of the $ i $ -th stick is $ 2^{a_i} $ .

You want to choose exactly $ 3 $ sticks out of the given $ n $ sticks, and form a non-degenerate triangle out of them, using the sticks as the sides of the triangle. A triangle is called non-degenerate if its area is strictly greater than $ 0 $ .

You have to calculate the number of ways to choose exactly $ 3 $ sticks so that a triangle can be formed out of them. Note that the order of choosing sticks does not matter (for example, choosing the $ 1 $ -st, $ 2 $ -nd and $ 4 $ -th stick is the same as choosing the $ 2 $ -nd, $ 4 $ -th and $ 1 $ -st stick).

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Each test case consists of two lines:

- the first line contains one integer $ n $ ( $ 1 \le n \le 3 \cdot 10^5 $ );
- the second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le n $ ).

Additional constraint on the input: the sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, print one integer — the number of ways to choose exactly $ 3 $ sticks so that a triangle can be formed out of them.

## 说明/提示

In the first test case of the example, any three sticks out of the given $ 7 $ can be chosen.

In the second test case of the example, you can choose the $ 1 $ -st, $ 2 $ -nd and $ 4 $ -th stick, or the $ 1 $ -st, $ 3 $ -rd and $ 4 $ -th stick.

In the third test case of the example, you cannot form a triangle out of the given sticks with lengths $ 2 $ , $ 4 $ and $ 8 $ .

## 样例 #1

### 输入

```
4
7
1 1 1 1 1 1 1
4
3 2 1 3
3
1 2 3
1
1
```

### 输出

```
35
2
0
0
```



---

---
title: "Turtle Fingers: Count the Values of k"
layout: "post"
diff: 普及-
pid: CF1933C
tag: ['枚举']
---

# Turtle Fingers: Count the Values of k

## 题目描述

You are given three positive integers $ a $ , $ b $ and $ l $ ( $ a,b,l>0 $ ).

It can be shown that there always exists a way to choose non-negative (i.e. $ \ge 0 $ ) integers $ k $ , $ x $ , and $ y $ such that $ l = k \cdot a^x \cdot b^y $ .

Your task is to find the number of distinct possible values of $ k $ across all such ways.

## 输入格式

The first line contains the integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The following $ t $ lines contain three integers, $ a $ , $ b $ and $ l $ ( $ 2 \le a, b \le 100 $ , $ 1 \le l \le 10^6 $ ) — description of a test case.

## 输出格式

Output $ t $ lines, with the $ i $ -th ( $ 1 \le i \le t $ ) line containing an integer, the answer to the $ i $ -th test case.

## 说明/提示

In the first test case, $ a=2, b=5, l=20 $ . The possible values of $ k $ (and corresponding $ x,y $ ) are as follows:

- Choose $ k = 1, x = 2, y = 1 $ . Then $ k \cdot a^x \cdot b^y = 1 \cdot 2^2 \cdot 5^1 = 20 = l $ .
- Choose $ k = 2, x = 1, y = 1 $ . Then $ k \cdot a^x \cdot b^y = 2 \cdot 2^1 \cdot 5^1 = 20 = l $ .
- Choose $ k = 4, x = 0, y = 1 $ . Then $ k \cdot a^x \cdot b^y = 4 \cdot 2^0 \cdot 5^1 = 20 = l $ .
- Choose $ k = 5, x = 2, y = 0 $ . Then $ k \cdot a^x \cdot b^y = 5 \cdot 2^2 \cdot 5^0 = 20 = l $ .
- Choose $ k = 10, x = 1, y = 0 $ . Then $ k \cdot a^x \cdot b^y = 10 \cdot 2^1 \cdot 5^0 = 20 = l $ .
- Choose $ k = 20, x = 0, y = 0 $ . Then $ k \cdot a^x \cdot b^y = 20 \cdot 2^0 \cdot 5^0 = 20 = l $ .

In the second test case, $ a=2, b=5, l=21 $ . Note that $ l = 21 $ is not divisible by either $ a = 2 $ or $ b = 5 $ . Therefore, we can only set $ x = 0, y = 0 $ , which corresponds to $ k = 21 $ .

In the third test case, $ a=4, b=6, l=48 $ . The possible values of $ k $ (and corresponding $ x,y $ ) are as follows:

- Choose $ k = 2, x = 1, y = 1 $ . Then $ k \cdot a^x \cdot b^y = 2 \cdot 4^1 \cdot 6^1 = 48 = l $ .
- Choose $ k = 3, x = 2, y = 0 $ . Then $ k \cdot a^x \cdot b^y = 3 \cdot 4^2 \cdot 6^0 = 48 = l $ .
- Choose $ k = 8, x = 0, y = 1 $ . Then $ k \cdot a^x \cdot b^y = 8 \cdot 4^0 \cdot 6^1 = 48 = l $ .
- Choose $ k = 12, x = 1, y = 0 $ . Then $ k \cdot a^x \cdot b^y = 12 \cdot 4^1 \cdot 6^0 = 48 = l $ .
- Choose $ k = 48, x = 0, y = 0 $ . Then $ k \cdot a^x \cdot b^y = 48 \cdot 4^0 \cdot 6^0 = 48 = l $ .

## 样例 #1

### 输入

```
11
2 5 20
2 5 21
4 6 48
2 3 72
3 5 75
2 2 1024
3 7 83349
100 100 1000000
7 3 2
2 6 6
17 3 632043
```

### 输出

```
6
1
5
12
6
11
24
4
1
3
24
```



---

---
title: "Clock and Strings"
layout: "post"
diff: 普及-
pid: CF1971C
tag: ['枚举']
---

# Clock and Strings

## 题目描述

There is a clock labeled with the numbers $ 1 $ through $ 12 $ in clockwise order, as shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1971C/dc1b9b8cdcc08927ff93e17ee0e104c325e2c451.png)In this example, $ (a,b,c,d)=(2,9,10,6) $ , and the strings intersect.

Alice and Bob have four distinct integers $ a $ , $ b $ , $ c $ , $ d $ not more than $ 12 $ . Alice ties a red string connecting $ a $ and $ b $ , and Bob ties a blue string connecting $ c $ and $ d $ . Do the strings intersect? (The strings are straight line segments.)

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 5940 $ ) — the number of test cases.

The only line of each test case contains four distinct integers $ a $ , $ b $ , $ c $ , $ d $ ( $ 1 \leq a, b, c, d \leq 12 $ ).

## 输出格式

For each test case, output "YES" (without quotes) if the strings intersect, and "NO" (without quotes) otherwise.

You can output "YES" and "NO" in any case (for example, strings "yEs", "yes", and "Yes" will be recognized as a positive response).

## 说明/提示

The first test case is pictured in the statement.

In the second test case, the strings do not intersect, as shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1971C/23548bb954ac5431bdc4259b9b8d572eb5d94e6e.png)

## 样例 #1

### 输入

```
15
2 9 10 6
3 8 9 1
1 2 3 4
5 3 4 12
1 8 2 10
3 12 11 8
9 10 12 1
12 1 10 2
3 12 6 9
1 9 8 4
6 7 9 12
7 12 9 6
10 12 11 1
3 9 6 12
1 4 3 5
```

### 输出

```
YES
NO
NO
YES
YES
NO
NO
NO
NO
NO
NO
YES
YES
YES
YES
```



---

---
title: "Secret Box"
layout: "post"
diff: 普及-
pid: CF1985E
tag: ['数学', '枚举', '排列组合']
---

# Secret Box

## 题目描述

Ntarsis has a box $ B $ with side lengths $ x $ , $ y $ , and $ z $ . It lies in the 3D coordinate plane, extending from $ (0,0,0) $ to $ (x,y,z) $ .

Ntarsis has a secret box $ S $ . He wants to choose its dimensions such that all side lengths are positive integers, and the volume of $ S $ is $ k $ . He can place $ S $ somewhere within $ B $ such that:

- $ S $ is parallel to all axes.
- every corner of $ S $ lies on an integer coordinate.

 $ S $ is magical, so when placed at an integer location inside $ B $ , it will not fall to the ground.

Among all possible ways to choose the dimensions of $ S $ , determine the maximum number of distinct locations he can choose to place his secret box $ S $ inside $ B $ . Ntarsis does not rotate $ S $ once its side lengths are selected.

## 输入格式

The first line consists of an integer $ t $ , the number of test cases ( $ 1 \leq t \leq 2000 $ ). The description of the test cases follows.

The first and only line of each test case contains four integers $ x, y, z $ and $ k $ ( $ 1 \leq x, y, z \leq 2000 $ , $ 1 \leq k \leq x \cdot y \cdot z $ ).

It is guaranteed the sum of all $ x $ , sum of all $ y $ , and sum of all $ z $ do not exceed $ 2000 $ over all test cases.

Note that $ k $ may not fit in a standard 32-bit integer data type.

## 输出格式

For each test case, output the answer as an integer on a new line. If there is no way to select the dimensions of $ S $ so it fits in $ B $ , output $ 0 $ .

## 说明/提示

For the first test case, it is optimal to choose $ S $ with side lengths $ 2 $ , $ 2 $ , and $ 2 $ , which has a volume of $ 2 \cdot 2 \cdot 2 = 8 $ . It can be shown there are $ 8 $ ways to put $ S $ inside $ B $ .

The coordinate with the least $ x $ , $ y $ , and $ z $ values for each possible arrangement of $ S $ are:

1. $ (0, 0, 0) $
2. $ (1, 0, 0) $
3. $ (0, 1, 0) $
4. $ (0, 0, 1) $
5. $ (1, 0, 1) $
6. $ (1, 1, 0) $
7. $ (0, 1, 1) $
8. $ (1, 1, 1) $

The arrangement of $ S $ with a coordinate of $ (0, 0, 0) $ is depicted below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1985E/47efaaa7005bda1e805807f94ece6c58f2ba3050.png)For the second test case, $ S $ with side lengths $ 2 $ , $ 3 $ , and $ 3 $ are optimal.

## 样例 #1

### 输入

```
7
3 3 3 8
3 3 3 18
5 1 1 1
2 2 2 7
3 4 2 12
4 3 1 6
1800 1800 1800 4913000000
```

### 输出

```
8
2
5
0
4
4
1030301
```



---

---
title: "Shohag Loves XOR (Easy Version)"
layout: "post"
diff: 普及-
pid: CF2039C1
tag: ['数学', '枚举', '位运算']
---

# Shohag Loves XOR (Easy Version)

## 题目描述

This is the easy version of the problem. The differences between the two versions are highlighted in bold. You can only make hacks if both versions of the problem are solved.

Shohag has two integers $ x $ and $ m $ . Help him count the number of integers $ 1 \le y \le m $ such that $ \mathbf{x \neq y} $ and $ x \oplus y $ is a divisor $ ^{\text{∗}} $ of either $ x $ , $ y $ , or both. Here $ \oplus $ is the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) operator.

 $ ^{\text{∗}} $ The number $ b $ is a divisor of the number $ a $ if there exists an integer $ c $ such that $ a = b \cdot c $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first and only line of each test case contains two space-separated integers $ x $ and $ m $ ( $ 1 \le x \le 10^6 $ , $ 1 \le m \le 10^{18} $ ).

It is guaranteed that the sum of $ x $ over all test cases does not exceed $ 10^7 $ .

## 输出格式

For each test case, print a single integer — the number of suitable $ y $ .

## 说明/提示

In the first test case, for $ x = 6 $ , there are $ 3 $ valid values for $ y $ among the integers from $ 1 $ to $ m = 9 $ , and they are $ 4 $ , $ 5 $ , and $ 7 $ .

- $ y = 4 $ is valid because $ x \oplus y = 6 \oplus 4 = 2 $ and $ 2 $ is a divisor of both $ x = 6 $ and $ y = 4 $ .
- $ y = 5 $ is valid because $ x \oplus y = 6 \oplus 5 = 3 $ and $ 3 $ is a divisor of $ x = 6 $ .
- $ y = 7 $ is valid because $ x \oplus y = 6 \oplus 7 = 1 $ and $ 1 $ is a divisor of both $ x = 6 $ and $ y = 7 $ .

In the second test case, for $ x = 5 $ , there are $ 2 $ valid values for $ y $ among the integers from $ 1 $ to $ m = 7 $ , and they are $ 4 $ and $ 6 $ .

- $ y = 4 $ is valid because $ x \oplus y = 5 \oplus 4 = 1 $ and $ 1 $ is a divisor of both $ x = 5 $ and $ y = 4 $ .
- $ y = 6 $ is valid because $ x \oplus y = 5 \oplus 6 = 3 $ and $ 3 $ is a divisor of $ y = 6 $ .

## 样例 #1

### 输入

```
5
6 9
5 7
2 3
6 4
4 1
```

### 输出

```
3
2
1
1
0
```



---

---
title: "Pushing Balls"
layout: "post"
diff: 普及-
pid: CF2090B
tag: ['枚举']
---

# Pushing Balls

## 题目描述

Ecrade 有一个 $$$n \times m$$$ 的网格，初始为空。他通过多次（可能为零次）推球操作在其中放置了若干球。

每次操作时，他可以选择从某行的最左边缘或某列的最上边缘向网格内推入一个球。

当一个球朝某个方向移动时：
- 若目标位置原本没有球，则新推入的球会占据该位置并停止。
- 若目标位置已有球，则新推入的球会占据该位置，而原位置的球将继续沿相同方向移动到下一个位置。

注意：若某行或某列已满（即该行或列所有位置都有球），则不能从该行或列推入新球。

给定网格每个位置是否有球的最终状态，请判断是否存在一种推球操作序列使得最终状态可以被达成。

## 输入格式

第一行包含一个整数 $$$t$$$（$$$1 \le t \le 10\,000$$$）——测试用例数量。接下来是测试用例描述。

每个测试用例的第一行包含两个整数 $$$n$$$ 和 $$$m$$$（$$$1 \le n, m \le 50$$$）。

接下来是 $$$n$$$ 行，每行包含恰好 $$$m$$$ 个字符（仅由 0 和 1 构成），描述网格的最终状态。当且仅当输入中对应位置为 1 时，该位置存在一个球。

保证所有测试用例的 $$$n \cdot m$$$ 之和不超过 $$$10\,000$$$。

## 输出格式

对于每个测试用例，若存在合法操作序列达成最终状态则输出 "Yes"（不带引号），否则输出 "No"（不带引号）。

答案大小写不敏感（例如 "YES"、"yEs" 和 "yes" 均视为肯定回答）。


## 说明/提示

为简化描述：
- 若从第 $$$i$$$ 行的最左边缘推入球，称该操作为 $$$\text{ROW}\\ i$$$
- 若从第 $$$i$$$ 列的最上边缘推入球，称该操作为 $$$\text{COL}\\ i$$$

以下示例矩阵中的非零数字 $$$x$$$ 表示第 $$$x$$$ 次推入的球。

第一个测试用例的一个可能操作序列：
$$$\begin{pmatrix}0&0&0\\\\0&0&0\\\\0&0&0\end{pmatrix}\xrightarrow{\text{ROW}\\ 3}\xrightarrow{\text{ROW}\\ 3} \begin{pmatrix}0&0&0\\\\0&0&0\\\\2&1&0\end{pmatrix}\xrightarrow{\text{COL}\\ 3}\xrightarrow{\text{COL}\\ 3} \begin{pmatrix}0&0&4\\\\0&0&3\\\\2&1&0\end{pmatrix}$$$

第二个测试用例的一个可能操作序列：
$$$\begin{pmatrix}0&0&0\\\\0&0&0\\\\0&0&0\end{pmatrix}\xrightarrow{\text{ROW}\\ 2}\xrightarrow{\text{ROW}\\ 2}\xrightarrow{\text{ROW}\\ 2} \begin{pmatrix}0&0&0\\\\3&2&1\\\\0&0&0\end{pmatrix}\xrightarrow{\text{COL}\\ 2}\xrightarrow{\text{COL}\\ 2} \begin{pmatrix}0&5&0\\\\3&4&1\\\\0&2&0\end{pmatrix}$$$

第三个测试用例的一个可能操作序列：
$$$\begin{pmatrix}0&0&0\\\\0&0&0\\\\0&0&0\end{pmatrix}\xrightarrow{\text{ROW}\\ 1}\xrightarrow{\text{ROW}\\ 2}\xrightarrow{\text{ROW}\\ 3} \begin{pmatrix}1&0&0\\\\2&0&0\\\\3&0&0\end{pmatrix}\xrightarrow{\text{COL}\\ 3}\xrightarrow{\text{COL}\\ 3}\xrightarrow{\text{COL}\\ 3} \begin{pmatrix}1&0&6\\\\2&0&5\\\\3&0&4\end{pmatrix}\xrightarrow{\text{ROW}\\ 1}\xrightarrow{\text{ROW}\\ 2}\xrightarrow{\text{ROW}\\ 3} \begin{pmatrix}7&1&6\\\\8&2&5\\\\9&3&4\end{pmatrix}$$$

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
3 3
001
001
110
3 3
010
111
010
3 3
111
111
111
3 3
000
000
000
3 3
000
000
001
```

### 输出

```
YES
YES
YES
YES
NO
```



---

---
title: "Brr Brrr Patapim"
layout: "post"
diff: 普及-
pid: CF2094C
tag: ['枚举']
---

# Brr Brrr Patapim

## 题目描述

Brr Brrr Patapim 正在尝试破解 Tiramisù 的秘密密码，这个密码是一个由 $2 \cdot n$ 个元素组成的排列 $^{\text{∗}}$。为了帮助 Patapim 猜测，Tiramisù 给了他一个 $n \times n$ 的网格 $G$，其中 $G_{i,j}$（即网格第 $i$ 行第 $j$ 列的元素）包含 $p_{i+j}$，也就是排列中的第 $(i+j)$ 个元素。

给定这个网格，请帮助 Patapim 破解这个被遗忘的密码。题目保证这样的排列存在，并且可以证明该排列是唯一确定的。

$^{\text{∗}}$ 一个由 $m$ 个整数组成的排列是指一个包含 $1,2,\ldots,m$ 每个数恰好一次的序列。例如，$[1, 3, 2]$ 和 $[2, 1]$ 是排列，而 $[1, 2, 4]$ 和 $[1, 3, 2, 3]$ 不是。

## 输入格式

第一行包含一个整数 $t$ —— 测试用例的数量（$1 \leq t \leq 200$）。

每个测试用例的第一行包含一个整数 $n$（$1 \leq n \leq 800$）。

接下来的 $n$ 行每行包含 $n$ 个整数，描述网格 $G$。其中第一行包含 $G_{1,1}, G_{1,2}, \ldots, G_{1,n}$；第二行包含 $G_{2,1}, G_{2,2}, \ldots, G_{2,n}$，以此类推（$1 \leq G_{i,j} \leq 2 \cdot n$）。

题目保证网格对应一个有效的排列，并且所有测试用例的 $n$ 之和不超过 $800$。

## 输出格式

对于每个测试用例，请在新的一行输出 $2n$ 个数字：$p_1, p_2, \ldots, p_{2n}$。

## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
3
1 6 2
6 2 4
2 4 3
1
1
2
2 3
3 4
```

### 输出

```
5 1 6 2 4 3 
2 1 
1 2 3 4
```



---

---
title: "Shrinking Array"
layout: "post"
diff: 普及-
pid: CF2112B
tag: ['贪心', '枚举']
---

# Shrinking Array

## 题目描述

序列 $b$ 是美丽的，当且仅当 $b$ 的长度至少为 $2$ 且存在一个位置 $i$ 使得 $\vert b_i-b_{i+1}\vert\le 1$。 

给你一个序列 $a$，你可以执行以下操作直到其长度少于 $2$。
- 选择 $a$ 中两个相邻的位置 $i$ 和 $i+1$。
- 选择一个整数 $x$ 使得 $\min(a_i,a_{i+1})\le x\le \max(a_i,a_{i+1})$。
- 删除 $a_i$ 和 $a_{i+1}$，并在它们的位置插入一个 $x$。这会使得 $a$ 的长度减少 $1$。

计算最少需要多少次操作使得 $a$ 变得美丽，或报告这是不可能的。

## 输入格式

多组数据。第一行一个整数 $t(1\le t\le 200)$，表示数据组数。

对于每组数据，第一行一个整数 $n(2\le n\le 1000)$，表示 $a$ 的大小。\
第二行 $n$ 个整数 $a_1,a_2,\cdots,a_n(1\le a_i\le 10^6)$。

## 输出格式

对于每组数据，如果可以通过操作使得 $a$ 为美丽的，输出一行一个整数表示答案；否则输出一行 $-1$ 表示无解。

## 说明/提示

**样例解释**

对于第一组数据，$\vert a_2-a_3\vert=\vert 3-3\vert=0$，因此 $a$ 是美丽的。

对于第二组数据，执行操作会让 $a$ 的长度小于 $2$，所以不可能使得 $a$ 美丽。

对于第三组数据，选择 $a_1,a_2$ 和 $x=2$，操作后的序列 $[2,3,7]$ 是美丽的。

对于第四组数据，选择 $a_2,a_3$ 和 $x=3$，操作后的序列 $[1,3,2]$ 是美丽的。


## 样例 #1

### 输入

```
4
4
1 3 3 7
2
6 9
4
3 1 3 7
4
1 3 5 2
```

### 输出

```
0
-1
1
1
```



---

---
title: "Come a Little Closer"
layout: "post"
diff: 普及-
pid: CF2114D
tag: ['模拟', '枚举']
---

# Come a Little Closer

## 题目描述

The game field is a matrix of size $ 10^9 \times 10^9 $ , with a cell at the intersection of the $ a $ -th row and the $ b $ -th column denoted as ( $ a, b $ ).

There are $ n $ monsters on the game field, with the $ i $ -th monster located in the cell ( $ x_i, y_i $ ), while the other cells are empty. No more than one monster can occupy a single cell.

You can move one monster to any cell on the field that is not occupied by another monster at most once .

After that, you must select one rectangle on the field; all monsters within the selected rectangle will be destroyed. You must pay $ 1 $ coin for each cell in the selected rectangle.

Your task is to find the minimum number of coins required to destroy all the monsters.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of monsters on the field.

The following $ n $ lines contain two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i, y_i \le 10^9 $ ) — the coordinates of the cell with the $ i $ -th monster. All pairs ( $ x_i, y_i $ ) are distinct.

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the minimum cost to destroy all $ n $ monsters.

## 说明/提示

Below are examples of optimal moves, with the cells of the rectangle to be selected highlighted in green.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2114D/925186708229ffea7667613d0cb72eebcaadb566.png) Required move for the first example.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2114D/213433b9bab32a2ca839daa9c0de4a82a4c12eb5.png) Required move for the fifth example.

## 样例 #1

### 输入

```
7
3
1 1
1 2
2 1
5
1 1
2 6
6 4
3 3
8 2
4
1 1
1 1000000000
1000000000 1
1000000000 1000000000
1
1 1
5
1 2
4 2
4 3
3 1
3 2
3
1 1
2 5
2 2
4
4 3
3 1
4 4
1 2
```

### 输出

```
3
32
1000000000000000000
1
6
4
8
```



---

---
title: "Stripe 2"
layout: "post"
diff: 普及-
pid: CF21C
tag: ['动态规划 DP', '枚举']
---

# Stripe 2

## 题目描述

给出一个长度为 $n$ 的序列 $a$，问有多少种方案将序列 $a$ 划分为恰好连续的三段（每个元素都属于某一段），使得每一段的和都相等。

## 输入格式

第一行一个整数 $n$，表示序列长度。

第二行 $n$ 个整数用空格隔开，第 $i$ 个整数表示 $a_i$。

## 输出格式

一行一个整数表示方案数。

## 样例 #1

### 输入

```
4
1 2 3 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5
1 2 3 4 5

```

### 输出

```
0

```



---

---
title: "Little Elephant and Numbers"
layout: "post"
diff: 普及-
pid: CF221B
tag: ['模拟', '枚举']
---

# Little Elephant and Numbers

## 题目描述

The Little Elephant loves numbers.

He has a positive integer $ x $ . The Little Elephant wants to find the number of positive integers $ d $ , such that $ d $ is the divisor of $ x $ , and $ x $ and $ d $ have at least one common (the same) digit in their decimal representations.

Help the Little Elephant to find the described number.

## 输入格式

A single line contains a single integer $ x $ $ (1<=x<=10^{9}) $ .

## 输出格式

In a single line print an integer — the answer to the problem.

## 样例 #1

### 输入

```
1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
10

```

### 输出

```
2

```



---

---
title: "Little Xor"
layout: "post"
diff: 普及-
pid: CF252A
tag: ['博弈论', '枚举', '前缀和']
---

# Little Xor

## 题目描述

Little Petya likes arrays that consist of non-negative integers a lot. Recently his mom has presented him one such array consisting of $ n $ elements. Petya immediately decided to find there a segment of consecutive elements, such that the $ xor $ of all numbers from this segment was maximal possible. Help him with that.

The $ xor $ operation is the bitwise exclusive "OR", that is denoted as "xor" in Pascal and "^" in C/C++/Java.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=100 $ ) — the number of elements in the array. The second line contains the space-separated integers from the array. All numbers are non-negative integers strictly less than $ 2^{30} $ .

## 输出格式

Print a single integer — the required maximal $ xor $ of a segment of consecutive elements.

## 说明/提示

In the first sample one of the optimal segments is the segment that consists of the first and the second array elements, if we consider the array elements indexed starting from one.

The second sample contains only one optimal segment, which contains exactly one array element (element with index three).

## 样例 #1

### 输入

```
5
1 2 1 1 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3
1 2 7

```

### 输出

```
7

```

## 样例 #3

### 输入

```
4
4 2 4 8

```

### 输出

```
14

```



---

---
title: "Dima and Continuous Line"
layout: "post"
diff: 普及-
pid: CF358A
tag: ['枚举']
---

# Dima and Continuous Line

## 题目描述

在 $x$ 轴上存在 $n$ 个点 $(x_1,0),(x_2,0),(x_3,0),\dots ,(x_n,0)$，以相邻两点 $(x_i,0)$ 与 $(x_{i+1},0)$ 的连线作为直径向上作半圆，问是否有除 $x$ 轴上的交点。

## 输入格式

输入包含 $2$ 行：

第 $1$ 行一个整数 $n$，表示点的个数。

第 $2$ 行 $n$ 个整数，表示 $n$ 个点的坐标。

## 输出格式

若有，输出 `yes`，否则输出 `no`。

## 说明/提示

$1 \le n \le 10^3, -10^6 \le x_i \le 10^6$。

## 样例 #1

### 输入

```
4
0 10 5 15

```

### 输出

```
yes

```

## 样例 #2

### 输入

```
4
0 15 5 10

```

### 输出

```
no

```



---

---
title: "Shower Line"
layout: "post"
diff: 普及-
pid: CF431B
tag: ['枚举']
---

# Shower Line

## 题目描述

学生宿舍里只有一个淋浴，有很多个学生希望早上洗澡。这就是为什么每天早上宿舍门口有五个人排队的原因。淋浴一打开，第一个人就从队里进入淋浴。一段时间后，第一个人离开淋浴，下一个人进入淋浴。这个过程一直持续到每个人淋浴过。 洗澡需要一些时间，所以排队的学生在这时讲话。学生们成对交谈：第 $2\times i-1$ 个人与第 $2\times i$ 个人交谈。 更详细些，把人数从 $1$ 到 $5$ 编号，让我们假设队列最初看起来是 $23154$（编号 $2$ 的人位于队列的开头），然后，在淋浴开始前，$2$ 和 $3$ 谈话, $1$ 和 $5$ 谈话，$4$ 没有任何人交谈，$2$ 洗澡时，$3$ 和 $1$ 交谈，$5$ 和 $4$ 交谈，$3$ 洗澡时，$1$ 和 $5$ 聊天，$4$ 没有任何人交谈，$1$ 洗澡时，$5$ 和 $4$ 聊天，然后 $5$ 淋浴，$4$ 淋浴。 我们知道如果 $i$ 和 $j$ 交谈，$i$ 的幸福值增加 $g_{i,j}$，$j$ 的幸福值增加 $g_{j,i}$，你的任务是找到这样一排学生最初的顺序，使得所有学生的幸福感和最终达到最大。

## 输入格式

输入共五行，每行输入五个用空格分隔的整数。第 $i$ 行的第 $j$ 个整数代表 $g_{i,j}$。保证对于所有 $i$ 的 $g_{i,i}=0$。

## 输出格式

输出共 $1$ 行，输出学生最大的总幸福感.

## 说明/提示

对于 $100\%$ 的数据，满足 $0\le g_{i,j}\le10^5$。

## 样例 #1

### 输入

```
0 0 0 0 9
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
7 0 0 0 0

```

### 输出

```
32

```

## 样例 #2

### 输入

```
0 43 21 18 2
3 0 21 11 65
5 2 0 1 4
54 62 12 0 99
87 64 81 33 0

```

### 输出

```
620

```



---

---
title: "Dreamoon and Stairs"
layout: "post"
diff: 普及-
pid: CF476A
tag: ['枚举']
---

# Dreamoon and Stairs

## 题目描述

Dreamoon wants to climb up a stair of $ n $ steps. He can climb $ 1 $ or $ 2 $ steps at each move. Dreamoon wants the number of moves to be a multiple of an integer $ m $ .

What is the minimal number of moves making him climb to the top of the stairs that satisfies his condition?

## 输入格式

The single line contains two space separated integers $ n $ , $ m $ ( $ 0<n<=10000,1<m<=10 $ ).

## 输出格式

Print a single integer — the minimal number of moves being a multiple of $ m $ . If there is no way he can climb satisfying condition print $ -1 $ instead.

## 说明/提示

For the first sample, Dreamoon could climb in 6 moves with following sequence of steps: {2, 2, 2, 2, 1, 1}.

For the second sample, there are only three valid sequence of steps {2, 1}, {1, 2}, {1, 1, 1} with 2, 2, and 3 steps respectively. All these numbers are not multiples of 5.

## 样例 #1

### 输入

```
10 2

```

### 输出

```
6

```

## 样例 #2

### 输入

```
3 5

```

### 输出

```
-1

```



---

---
title: "Divisibility by Eight"
layout: "post"
diff: 普及-
pid: CF550C
tag: ['动态规划 DP', '枚举']
---

# Divisibility by Eight

## 题目描述

You are given a non-negative integer $ n $ , its decimal representation consists of at most $ 100 $ digits and doesn't contain leading zeroes.

Your task is to determine if it is possible in this case to remove some of the digits (possibly not remove any digit at all) so that the result contains at least one digit, forms a non-negative integer, doesn't have leading zeroes and is divisible by 8. After the removing, it is forbidden to rearrange the digits.

If a solution exists, you should print it.

## 输入格式

The single line of the input contains a non-negative integer $ n $ . The representation of number $ n $ doesn't contain any leading zeroes and its length doesn't exceed $ 100 $ digits.

## 输出格式

Print "NO" (without quotes), if there is no such way to remove some digits from number $ n $ .

Otherwise, print "YES" in the first line and the resulting number after removing digits from number $ n $ in the second line. The printed number must be divisible by $ 8 $ .

If there are multiple possible answers, you may print any of them.

## 样例 #1

### 输入

```
3454

```

### 输出

```
YES
344

```

## 样例 #2

### 输入

```
10

```

### 输出

```
YES
0

```

## 样例 #3

### 输入

```
111111

```

### 输出

```
NO

```



---

---
title: "Tricky Sum"
layout: "post"
diff: 普及-
pid: CF598A
tag: ['数学', '枚举']
---

# Tricky Sum

## 题目描述

In this problem you are to calculate the sum of all integers from $ 1 $ to $ n $ , but you should take all powers of two with minus in the sum.

For example, for $ n=4 $ the sum is equal to $ -1-2+3-4=-4 $ , because $ 1 $ , $ 2 $ and $ 4 $ are $ 2^{0} $ , $ 2^{1} $ and $ 2^{2} $ respectively.

Calculate the answer for $ t $ values of $ n $ .

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1<=t<=100 $ ) — the number of values of $ n $ to be processed.

Each of next $ t $ lines contains a single integer $ n $ ( $ 1<=n<=10^{9} $ ).

## 输出格式

Print the requested sum for each of $ t $ integers $ n $ given in the input.

## 说明/提示

The answer for the first sample is explained in the statement.

## 样例 #1

### 输入

```
2
4
1000000000

```

### 输出

```
-4
499999998352516354

```



---

---
title: "Block Towers"
layout: "post"
diff: 普及-
pid: CF626C
tag: ['枚举']
---

# Block Towers

## 题目描述

Students in a class are making towers of blocks. Each student makes a (non-zero) tower by stacking pieces lengthwise on top of each other. $ n $ of the students use pieces made of two blocks and $ m $ of the students use pieces made of three blocks.

The students don’t want to use too many blocks, but they also want to be unique, so no two students’ towers may contain the same number of blocks. Find the minimum height necessary for the tallest of the students' towers.

## 输入格式

The first line of the input contains two space-separated integers $ n $ and $ m $ ( $ 0<=n,m<=1000000 $ , $ n+m&gt;0 $ ) — the number of students using two-block pieces and the number of students using three-block pieces, respectively.

## 输出格式

Print a single integer, denoting the minimum possible height of the tallest tower.

## 说明/提示

In the first case, the student using two-block pieces can make a tower of height $ 4 $ , and the students using three-block pieces can make towers of height $ 3 $ , $ 6 $ , and $ 9 $ blocks. The tallest tower has a height of $ 9 $ blocks.

In the second case, the students can make towers of heights $ 2 $ , $ 4 $ , and $ 8 $ with two-block pieces and towers of heights $ 3 $ and $ 6 $ with three-block pieces, for a maximum height of $ 8 $ blocks.

## 样例 #1

### 输入

```
1 3

```

### 输出

```
9

```

## 样例 #2

### 输入

```
3 2

```

### 输出

```
8

```

## 样例 #3

### 输入

```
5 0

```

### 输出

```
10

```



---

---
title: "Orchestra"
layout: "post"
diff: 普及-
pid: CF635A
tag: ['模拟', '枚举', '前缀和']
---

# Orchestra

## 题目描述

Paul is at the orchestra. The string section is arranged in an $ r×c $ rectangular grid and is filled with violinists with the exception of $ n $ violists. Paul really likes violas, so he would like to take a picture including at least $ k $ of them. Paul can take a picture of any axis-parallel rectangle in the orchestra. Count the number of possible pictures that Paul can take.

Two pictures are considered to be different if the coordinates of corresponding rectangles are different.

## 输入格式

The first line of input contains four space-separated integers $ r $ , $ c $ , $ n $ , $ k $ ( $ 1<=r,c,n<=10 $ , $ 1<=k<=n $ ) — the number of rows and columns of the string section, the total number of violas, and the minimum number of violas Paul would like in his photograph, respectively.

The next $ n $ lines each contain two integers $ x_{i} $ and $ y_{i} $ ( $ 1<=x_{i}<=r $ , $ 1<=y_{i}<=c $ ): the position of the $ i $ -th viola. It is guaranteed that no location appears more than once in the input.

## 输出格式

Print a single integer — the number of photographs Paul can take which include at least $ k $ violas.

## 说明/提示

We will use '\*' to denote violinists and '\#' to denote violists.

In the first sample, the orchestra looks as follows

`<br></br>*#<br></br>**<br></br>` Paul can take a photograph of just the viola, the $ 1×2 $ column containing the viola, the $ 2×1 $ row containing the viola, or the entire string section, for $ 4 $ pictures total.In the second sample, the orchestra looks as follows

`<br></br>#*<br></br>*#<br></br>#*<br></br>` Paul must take a photograph of the entire section.In the third sample, the orchestra looks the same as in the second sample.

## 样例 #1

### 输入

```
2 2 1 1
1 2

```

### 输出

```
4

```

## 样例 #2

### 输入

```
3 2 3 3
1 1
3 1
2 2

```

### 输出

```
1

```

## 样例 #3

### 输入

```
3 2 3 2
1 1
3 1
2 2

```

### 输出

```
4

```



---

---
title: "Petya and Java"
layout: "post"
diff: 普及-
pid: CF66A
tag: ['模拟', '字符串', '枚举']
---

# Petya and Java

## 题目描述

Little Petya has recently started attending a programming club. Naturally he is facing the problem of choosing a programming language. After long considerations he realized that Java is the best choice. The main argument in favor of choosing Java was that it has a very large integer data type, called BigInteger.

But having attended several classes of the club, Petya realized that not all tasks require using the BigInteger type. It turned out that in some tasks it is much easier to use small data types. That's why a question arises: "Which integer type to use if one wants to store a positive integer $ n $ ?"

Petya knows only 5 integer types:

1\) byte occupies 1 byte and allows you to store numbers from $ -128 $ to $ 127 $

2\) short occupies 2 bytes and allows you to store numbers from $ -32768 $ to $ 32767 $

3\) int occupies 4 bytes and allows you to store numbers from $ -2147483648 $ to $ 2147483647 $

4\) long occupies 8 bytes and allows you to store numbers from $ -9223372036854775808 $ to $ 9223372036854775807 $

5\) BigInteger can store any integer number, but at that it is not a primitive type, and operations with it are much slower.

For all the types given above the boundary values are included in the value range.

From this list, Petya wants to choose the smallest type that can store a positive integer $ n $ . Since BigInteger works much slower, Peter regards it last. Help him.

## 输入格式

The first line contains a positive number $ n $ . It consists of no more than $ 100 $ digits and doesn't contain any leading zeros. The number $ n $ can't be represented as an empty string.

Please, do not use %lld specificator to read or write 64-bit integers in C++. It is preffered to use cout (also you may use %I64d).

## 输出格式

Print the first type from the list "byte, short, int, long, BigInteger", that can store the natural number $ n $ , in accordance with the data given above.

## 样例 #1

### 输入

```
127

```

### 输出

```
byte

```

## 样例 #2

### 输入

```
130

```

### 输出

```
short

```

## 样例 #3

### 输入

```
123456789101112131415161718192021222324

```

### 输出

```
BigInteger

```



---

---
title: "Pineapple Incident"
layout: "post"
diff: 普及-
pid: CF697A
tag: ['模拟', '数学', '枚举']
---

# Pineapple Incident

## 题目描述

Ted有一个菠萝。这个菠萝可以像狗一样叫！在第 $t$ 秒它第一次叫。然后每隔 $s$ 秒之后它会叫一次，在叫这一次之后还会在后一秒再叫一次。意思就是说它会在 $t$ 秒，$t+s$ 秒，$t+s+1$ 秒，$t+2s$ 秒，$t+2s+1$ 秒分别叫一次，以此类推。 

Barney在早上醒来，他想吃个菠萝，但这只菠萝叫的时候Barney不能吃它。Barney打算在 $x$ 秒吃它，所以请你告诉Barney在x秒的时候，这个菠萝会不会叫。

## 输入格式

仅输入一行，输入 $t,s,x$($0\le t,x\le 10^9$，$2\leq s\leq 10^9$)分别为菠萝第一次叫的时间，叫的间隔以及Barney想吃的时间。

## 输出格式

如果菠萝要叫的话，输出YES，否则输出NO。

## 样例 #1

### 输入

```
3 10 4

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
3 10 3

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
3 8 51

```

### 输出

```
YES

```

## 样例 #4

### 输入

```
3 8 52

```

### 输出

```
YES

```



---

---
title: "Ilya and tic-tac-toe game"
layout: "post"
diff: 普及-
pid: CF754B
tag: ['模拟', '搜索', '枚举']
---

# Ilya and tic-tac-toe game

## 题目描述

题目大意：

伊莉雅是一个4x4井字棋的年迈棋手，他总是用x（英文小写）棋，今天，他跟他的朋友亚瑟玩了很多很多局游戏，亚瑟很累了，但是现在还剩下最后一场游戏，现在轮到伊莉雅下棋，请问伊莉雅下完这颗棋子后能否取得胜利？
井字棋规则：

 棋盘的规格为4*4，其中伊莉雅棋子为x，亚瑟的棋子为o（英文小写o），x先下，o后下，当某种棋子在棋盘上连成三个时取得胜利！（这三个棋子可以是水平、竖直或斜方向的连续三个）

## 输入格式

输入的数据为给定的棋盘，其中.为空格，x（英文小写）为伊莉雅的棋子， o（英文小写）为亚瑟的棋子，棋盘保证有空格子，现在轮到伊莉雅。 （有可能整个棋盘都没有棋子，意味着亚瑟还没有下）

## 输出格式

输出为单行：如果伊莉雅下完一颗棋子后能够取得胜利，输出YES，如果不能，则输出NO。


感谢@icebird  提供的翻译

## 样例 #1

### 输入

```
xx..
.oo.
x...
oox.

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
x.ox
ox..
x.o.
oo.x

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
x..x
..oo
o...
x.xo

```

### 输出

```
YES

```

## 样例 #4

### 输入

```
o.x.
o...
.x..
ooxx

```

### 输出

```
NO

```



---

---
title: "Shell Game"
layout: "post"
diff: 普及-
pid: CF777A
tag: ['模拟', '枚举']
---

# Shell Game

## 题目描述

Bomboslav likes to look out of the window in his room and watch lads outside playing famous shell game. The game is played by two persons: operator and player. Operator takes three similar opaque shells and places a ball beneath one of them. Then he shuffles the shells by swapping some pairs and the player has to guess the current position of the ball.

Bomboslav noticed that guys are not very inventive, so the operator always swaps the left shell with the middle one during odd moves (first, third, fifth, etc.) and always swaps the middle shell with the right one during even moves (second, fourth, etc.).

Let's number shells from $ 0 $ to $ 2 $ from left to right. Thus the left shell is assigned number $ 0 $ , the middle shell is $ 1 $ and the right shell is $ 2 $ . Bomboslav has missed the moment when the ball was placed beneath the shell, but he knows that exactly $ n $ movements were made by the operator and the ball was under shell $ x $ at the end. Now he wonders, what was the initial position of the ball?

## 输入格式

The first line of the input contains an integer $ n $ ( $ 1<=n<=2·10^{9} $ ) — the number of movements made by the operator.

The second line contains a single integer $ x $ ( $ 0<=x<=2 $ ) — the index of the shell where the ball was found after $ n $ movements.

## 输出格式

Print one integer from $ 0 $ to $ 2 $ — the index of the shell where the ball was initially placed.

## 说明/提示

In the first sample, the ball was initially placed beneath the middle shell and the operator completed four movements.

1. During the first move operator swapped the left shell and the middle shell. The ball is now under the left shell.
2. During the second move operator swapped the middle shell and the right one. The ball is still under the left shell.
3. During the third move operator swapped the left shell and the middle shell again. The ball is again in the middle.
4. Finally, the operators swapped the middle shell and the right shell. The ball is now beneath the right shell.

## 样例 #1

### 输入

```
4
2

```

### 输出

```
1

```

## 样例 #2

### 输入

```
1
1

```

### 输出

```
0

```



---

---
title: "Vladik and Complicated Book"
layout: "post"
diff: 普及-
pid: CF811B
tag: ['枚举']
---

# Vladik and Complicated Book

## 题目描述

Vladik had started reading a complicated book about algorithms containing $ n $ pages. To improve understanding of what is written, his friends advised him to read pages in some order given by permutation $ P=[p_{1},p_{2},...,p_{n}] $ , where $ p_{i} $ denotes the number of page that should be read $ i $ -th in turn.

Sometimes Vladik’s mom sorted some subsegment of permutation $ P $ from position $ l $ to position $ r $ inclusive, because she loves the order. For every of such sorting Vladik knows number $ x $ — what index of page in permutation he should read. He is wondered if the page, which he will read after sorting, has changed. In other words, has $ p_{x} $ changed? After every sorting Vladik return permutation to initial state, so you can assume that each sorting is independent from each other.

## 输入格式

First line contains two space-separated integers $ n $ , $ m $ ( $ 1<=n,m<=10^{4} $ ) — length of permutation and number of times Vladik's mom sorted some subsegment of the book.

Second line contains $ n $ space-separated integers $ p_{1},p_{2},...,p_{n} $ ( $ 1<=p_{i}<=n $ ) — permutation $ P $ . Note that elements in permutation are distinct.

Each of the next $ m $ lines contains three space-separated integers $ l_{i} $ , $ r_{i} $ , $ x_{i} $ ( $ 1<=l_{i}<=x_{i}<=r_{i}<=n $ ) — left and right borders of sorted subsegment in $ i $ -th sorting and position that is interesting to Vladik.

## 输出格式

For each mom’s sorting on it’s own line print "Yes", if page which is interesting to Vladik hasn't changed, or "No" otherwise.

## 说明/提示

Explanation of first test case:

1. $ [1,2,3,4,5] $ — permutation after sorting, $ 3 $ -rd element hasn’t changed, so answer is "Yes".
2. $ [3,4,5,2,1] $ — permutation after sorting, $ 1 $ -st element has changed, so answer is "No".
3. $ [5,2,3,4,1] $ — permutation after sorting, $ 3 $ -rd element hasn’t changed, so answer is "Yes".
4. $ [5,4,3,2,1] $ — permutation after sorting, $ 4 $ -th element hasn’t changed, so answer is "Yes".
5. $ [5,1,2,3,4] $ — permutation after sorting, $ 3 $ -rd element has changed, so answer is "No".

## 样例 #1

### 输入

```
5 5
5 4 3 2 1
1 5 3
1 3 1
2 4 3
4 4 4
2 5 3

```

### 输出

```
Yes
No
Yes
Yes
No

```

## 样例 #2

### 输入

```
6 5
1 4 3 2 5 6
2 4 3
1 6 2
4 5 4
1 3 3
2 6 3

```

### 输出

```
Yes
No
Yes
No
Yes

```



---

---
title: "ACM ICPC"
layout: "post"
diff: 普及-
pid: CF886A
tag: ['模拟', '枚举']
---

# ACM ICPC

## 题目描述

In a small but very proud high school it was decided to win ACM ICPC. This goal requires to compose as many teams of three as possible, but since there were only $ 6 $ students who wished to participate, the decision was to build exactly two teams.

After practice competition, participant number $ i $ got a score of $ a_{i} $ . Team score is defined as sum of scores of its participants. High school management is interested if it's possible to build two teams with equal scores. Your task is to answer that question.

## 输入格式

The single line contains six integers $ a_{1},...,a_{6} $ ( $ 0<=a_{i}<=1000 $ ) — scores of the participants

## 输出格式

Print "YES" (quotes for clarity), if it is possible to build teams with equal score, and "NO" otherwise.

You can print each character either upper- or lowercase ("YeS" and "yes" are valid when the answer is "YES").

## 说明/提示

In the first sample, first team can be composed of $ 1 $ st, $ 2 $ nd and $ 6 $ th participant, second — of $ 3 $ rd, $ 4 $ th and $ 5 $ th: team scores are $ 1+3+1=2+1+2=5 $ .

In the second sample, score of participant number $ 6 $ is too high: his team score will be definitely greater.

## 样例 #1

### 输入

```
1 3 2 1 2 1

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
1 1 1 1 1 99

```

### 输出

```
NO

```



---

---
title: "Cubes for Masha"
layout: "post"
diff: 普及-
pid: CF887B
tag: ['枚举']
---

# Cubes for Masha

## 题目描述

Absent-minded Masha got set of $ n $ cubes for her birthday.

At each of 6 faces of each cube, there is exactly one digit from 0 to 9. Masha became interested what is the largest natural $ x $ such she can make using her new cubes all integers from 1 to $ x $ .

To make a number Masha can rotate her cubes and put them in a row. After that, she looks at upper faces of cubes from left to right and reads the number.

The number can't contain leading zeros. It's not required to use all cubes to build a number.

Pay attention: Masha can't make digit 6 from digit 9 and vice-versa using cube rotations.

## 输入格式

In first line integer $ n $ is given ( $ 1<=n<=3 $ ) — the number of cubes, Masha got for her birthday.

Each of next $ n $ lines contains 6 integers $ a_{i}_{j} $ ( $ 0<=a_{i}_{j}<=9 $ ) — number on $ j $ -th face of $ i $ -th cube.

## 输出格式

Print single integer — maximum number $ x $ such Masha can make any integers from 1 to $ x $ using her cubes or 0 if Masha can't make even 1.

## 说明/提示

In the first test case, Masha can build all numbers from 1 to 87, but she can't make 88 because there are no two cubes with digit 8.

## 样例 #1

### 输入

```
3
0 1 2 3 4 5
6 7 8 9 0 1
2 3 4 5 6 7

```

### 输出

```
87
```

## 样例 #2

### 输入

```
3
0 1 3 5 6 8
1 2 4 5 7 8
2 3 4 6 7 9

```

### 输出

```
98
```



---

---
title: "Nearest Minimums"
layout: "post"
diff: 普及-
pid: CF911A
tag: ['枚举', '排序', '位运算']
---

# Nearest Minimums

## 题目描述

You are given an array of $ n $ integer numbers $ a_{0},a_{1},...,a_{n-1} $ . Find the distance between two closest (nearest) minimums in it. It is guaranteed that in the array a minimum occurs at least two times.
找到一个长度为n的序列中，距离最短的最小值的距离。

## 输入格式

The first line contains positive integer $ n $ ( $ 2<=n<=10^{5} $ ) — size of the given array. The second line contains $ n $ integers $ a_{0},a_{1},...,a_{n-1} $ ( $ 1<=a_{i}<=10^{9} $ ) — elements of the array. It is guaranteed that in the array a minimum occurs at least two times.

## 输出格式

Print the only number — distance between two nearest minimums in the array.

## 样例 #1

### 输入

```
2
3 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3
5 6 5

```

### 输出

```
2

```

## 样例 #3

### 输入

```
9
2 1 3 5 4 1 2 3 1

```

### 输出

```
3

```



---

---
title: "Water The Garden"
layout: "post"
diff: 普及-
pid: CF920A
tag: ['搜索', '枚举', '广度优先搜索 BFS']
---

# Water The Garden

## 题目描述

It is winter now, and Max decided it's about time he watered the garden.

The garden can be represented as $ n $ consecutive garden beds, numbered from $ 1 $ to $ n $ . $ k $ beds contain water taps ( $ i $ -th tap is located in the bed $ x_{i} $ ), which, if turned on, start delivering water to neighbouring beds. If the tap on the bed $ x_{i} $ is turned on, then after one second has passed, the bed $ x_{i} $ will be watered; after two seconds have passed, the beds from the segment $ [x_{i}-1,x_{i}+1] $ will be watered (if they exist); after $ j $ seconds have passed ( $ j $ is an integer number), the beds from the segment $ [x_{i}-(j-1),x_{i}+(j-1)] $ will be watered (if they exist). Nothing changes during the seconds, so, for example, we can't say that the segment $ [x_{i}-2.5,x_{i}+2.5] $ will be watered after $ 2.5 $ seconds have passed; only the segment $ [x_{i}-2,x_{i}+2] $ will be watered at that moment.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920A/13bc7cf6794d83f150515b3ef05c019c5a177edb.png) The garden from test $ 1 $ . White colour denotes a garden bed without a tap, red colour — a garden bed with a tap.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920A/7701b634db65a2b1523162fa68f6ca25374deecc.png) The garden from test $ 1 $ after $ 2 $ seconds have passed after turning on the tap. White colour denotes an unwatered garden bed, blue colour — a watered bed. Max wants to turn on all the water taps at the same moment, and now he wonders, what is the minimum number of seconds that have to pass after he turns on some taps until the whole garden is watered. Help him to find the answer!

## 输入格式

The first line contains one integer $ t $ — the number of test cases to solve ( $ 1<=t<=200 $ ).

Then $ t $ test cases follow. The first line of each test case contains two integers $ n $ and $ k $ ( $ 1<=n<=200 $ , $ 1<=k<=n $ ) — the number of garden beds and water taps, respectively.

Next line contains $ k $ integers $ x_{i} $ ( $ 1<=x_{i}<=n $ ) — the location of $ i $ -th water tap. It is guaranteed that for each ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920A/2023391807a0506d9aa6b2ab3f46eb89dee16074.png) condition $ x_{i-1}<x_{i} $ holds.

It is guaranteed that the sum of $ n $ over all test cases doesn't exceed $ 200 $ .

Note that in hacks you have to set $ t=1 $ .

## 输出格式

For each test case print one integer — the minimum number of seconds that have to pass after Max turns on some of the water taps, until the whole garden is watered.

## 说明/提示

The first example consists of $ 3 $ tests:

1. There are $ 5 $ garden beds, and a water tap in the bed $ 3 $ . If we turn it on, then after $ 1 $ second passes, only bed $ 3 $ will be watered; after $ 2 $ seconds pass, beds $ [1,3] $ will be watered, and after $ 3 $ seconds pass, everything will be watered.
2. There are $ 3 $ garden beds, and there is a water tap in each one. If we turn all of them on, then everything will be watered after $ 1 $ second passes.
3. There are $ 4 $ garden beds, and only one tap in the bed $ 1 $ . It will take $ 4 $ seconds to water, for example, bed $ 4 $ .

## 样例 #1

### 输入

```
3
5 1
3
3 3
1 2 3
4 1
1

```

### 输出

```
3
1
4

```



---

---
title: "Tea Queue"
layout: "post"
diff: 普及-
pid: CF920B
tag: ['模拟', '枚举', '队列']
---

# Tea Queue

## 题目描述

Recently $ n $ students from city S moved to city P to attend a programming camp.

They moved there by train. In the evening, all students in the train decided that they want to drink some tea. Of course, no two people can use the same teapot simultaneously, so the students had to form a queue to get their tea.

 $ i $ -th student comes to the end of the queue at the beginning of $ l_{i} $ -th second. If there are multiple students coming to the queue in the same moment, then the student with greater index comes after the student with lesser index. Students in the queue behave as follows: if there is nobody in the queue before the student, then he uses the teapot for exactly one second and leaves the queue with his tea; otherwise the student waits for the people before him to get their tea. If at the beginning of $ r_{i} $ -th second student $ i $ still cannot get his tea (there is someone before him in the queue), then he leaves the queue without getting any tea.

For each student determine the second he will use the teapot and get his tea (if he actually gets it).

## 输入格式

The first line contains one integer $ t $ — the number of test cases to solve ( $ 1<=t<=1000 $ ).

Then $ t $ test cases follow. The first line of each test case contains one integer $ n $ ( $ 1<=n<=1000 $ ) — the number of students.

Then $ n $ lines follow. Each line contains two integer $ l_{i} $ , $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=5000 $ ) — the second $ i $ -th student comes to the end of the queue, and the second he leaves the queue if he still cannot get his tea.

It is guaranteed that for every ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920B/748ee9e1ae91d0e555bb85d14ee499f01d330017.png) condition $ l_{i-1}<=l_{i} $ holds.

The sum of $ n $ over all test cases doesn't exceed $ 1000 $ .

Note that in hacks you have to set $ t=1 $ .

## 输出格式

For each test case print $ n $ integers. $ i $ -th of them must be equal to the second when $ i $ -th student gets his tea, or $ 0 $ if he leaves without tea.

## 说明/提示

The example contains $ 2 $ tests:

1. During $ 1 $ -st second, students $ 1 $ and $ 2 $ come to the queue, and student $ 1 $ gets his tea. Student $ 2 $ gets his tea during $ 2 $ -nd second.
2. During $ 1 $ -st second, students $ 1 $ and $ 2 $ come to the queue, student $ 1 $ gets his tea, and student $ 2 $ leaves without tea. During $ 2 $ -nd second, student $ 3 $ comes and gets his tea.

## 样例 #1

### 输入

```
2
2
1 3
1 4
3
1 5
1 1
2 3

```

### 输出

```
1 2 
1 0 2 

```



---

---
title: "A Compatible Pair"
layout: "post"
diff: 普及-
pid: CF934A
tag: ['贪心', '枚举', '排序']
---

# A Compatible Pair

## 题目描述

Nian is a monster which lives deep in the oceans. Once a year, it shows up on the land, devouring livestock and even people. In order to keep the monster away, people fill their villages with red colour, light, and cracking noise, all of which frighten the monster out of coming.

Little Tommy has $ n $ lanterns and Big Banban has $ m $ lanterns. Tommy's lanterns have brightness $ a_{1},a_{2},...,a_{n} $ , and Banban's have brightness $ b_{1},b_{2},...,b_{m} $ respectively.

Tommy intends to hide one of his lanterns, then Banban picks one of Tommy's non-hidden lanterns and one of his own lanterns to form a pair. The pair's brightness will be the product of the brightness of two lanterns.

Tommy wants to make the product as small as possible, while Banban tries to make it as large as possible.

You are asked to find the brightness of the chosen pair if both of them choose optimally.

## 输入格式

The first line contains two space-separated integers $ n $ and $ m $ ( $ 2<=n,m<=50 $ ).

The second line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ .

The third line contains $ m $ space-separated integers $ b_{1},b_{2},...,b_{m} $ .

All the integers range from $ -10^{9} $ to $ 10^{9} $ .

## 输出格式

Print a single integer — the brightness of the chosen pair.

## 说明/提示

In the first example, Tommy will hide $ 20 $ and Banban will choose $ 18 $ from Tommy and $ 14 $ from himself.

In the second example, Tommy will hide $ 3 $ and Banban will choose $ 2 $ from Tommy and $ 1 $ from himself.

## 样例 #1

### 输入

```
2 2
20 18
2 14

```

### 输出

```
252

```

## 样例 #2

### 输入

```
5 3
-1 0 1 2 3
-1 0 1

```

### 输出

```
2

```



---

---
title: "Word Correction"
layout: "post"
diff: 普及-
pid: CF938A
tag: ['字符串', '枚举']
---

# Word Correction

## 题目背景

给一个长为n的字符串，当有两个元音字母相邻时，删除后一个元音，输出修改后的字符串。（注：a,e,i,o,u,y为元音字母）

## 题目描述

Victor tries to write his own text editor, with word correction included. However, the rules of word correction are really strange.

Victor thinks that if a word contains two consecutive vowels, then it's kinda weird and it needs to be replaced. So the word corrector works in such a way: as long as there are two consecutive vowels in the word, it deletes the first vowel in a word such that there is another vowel right before it. If there are no two consecutive vowels in the word, it is considered to be correct.

You are given a word $ s $ . Can you predict what will it become after correction?

In this problem letters a, e, i, o, u and y are considered to be vowels.

## 输入格式

The first line contains one integer $ n $ ( $ 1<=n<=100 $ ) — the number of letters in word $ s $ before the correction.

The second line contains a string $ s $ consisting of exactly $ n $ lowercase Latin letters — the word before the correction.

## 输出格式

Output the word $ s $ after the correction.

## 说明/提示

Explanations of the examples:

1. There is only one replace: weird ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938A/5a518872d8942914aef6c33d251688a64a8d6d74.png) werd;
2. No replace needed since there are no two consecutive vowels;
3. aaeaa ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938A/5a518872d8942914aef6c33d251688a64a8d6d74.png)aeaa ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938A/5a518872d8942914aef6c33d251688a64a8d6d74.png)aaa ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938A/5a518872d8942914aef6c33d251688a64a8d6d74.png)aa ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938A/5a518872d8942914aef6c33d251688a64a8d6d74.png) a.

## 样例 #1

### 输入

```
5
weird

```

### 输出

```
werd

```

## 样例 #2

### 输入

```
4
word

```

### 输出

```
word

```

## 样例 #3

### 输入

```
5
aaeaa

```

### 输出

```
a

```



---

---
title: "Points on the line"
layout: "post"
diff: 普及-
pid: CF940A
tag: ['枚举']
---

# Points on the line

## 题目描述

We've got no test cases. A big olympiad is coming up. But the problemsetters' number one priority should be adding another problem to the round.

The diameter of a multiset of points on the line is the largest distance between two points from this set. For example, the diameter of the multiset $ {1,3,2,1} $ is 2.

Diameter of multiset consisting of one point is 0.

You are given $ n $ points on the line. What is the minimum number of points you have to remove, so that the diameter of the multiset of the remaining points will not exceed $ d $ ?

## 输入格式

The first line contains two integers $ n $ and $ d $ ( $ 1<=n<=100,0<=d<=100 $ ) — the amount of points and the maximum allowed diameter respectively.

The second line contains $ n $ space separated integers ( $ 1<=x_{i}<=100 $ ) — the coordinates of the points.

## 输出格式

Output a single integer — the minimum number of points you have to remove.

## 说明/提示

In the first test case the optimal strategy is to remove the point with coordinate $ 4 $ . The remaining points will have coordinates $ 1 $ and $ 2 $ , so the diameter will be equal to $ 2-1=1 $ .

In the second test case the diameter is equal to $ 0 $ , so its is unnecessary to remove any points.

In the third test case the optimal strategy is to remove points with coordinates $ 1 $ , $ 9 $ and $ 10 $ . The remaining points will have coordinates $ 3 $ , $ 4 $ and $ 6 $ , so the diameter will be equal to $ 6-3=3 $ .

## 样例 #1

### 输入

```
3 1
2 1 4

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3 0
7 7 7

```

### 输出

```
0

```

## 样例 #3

### 输入

```
6 3
1 3 4 6 9 10

```

### 输出

```
3

```



---

---
title: "Encryption (easy)"
layout: "post"
diff: 普及-
pid: CF958C1
tag: ['枚举', '前缀和']
---

# Encryption (easy)

## 题目描述

Rebel spy Heidi has just obtained the plans for the Death Star from the Empire and, now on her way to safety, she is trying to break the encryption of the plans (of course they are encrypted – the Empire may be evil, but it is not stupid!). The encryption has several levels of security, and here is how the first one looks.

Heidi is presented with a screen that shows her a sequence of integers $ A $ and a positive integer $ p $ . She knows that the encryption code is a single number $ S $ , which is defined as follows:

Define the score of $ X $ to be the sum of the elements of $ X $ modulo $ p $ .

Heidi is given a sequence $ A $ that consists of $ N $ integers, and also given an integer $ p $ . She needs to split $ A $ into $ 2 $ parts such that:

- Each part contains at least $ 1 $ element of $ A $ , and each part consists of contiguous elements of $ A $ .
- The two parts do not overlap.
- The total sum $ S $ of the scores of those two parts is maximized. This is the encryption code.

Output the sum $ S $ , which is the encryption code.

## 输入格式

The first line of the input contains two space-separated integer $ N $ and $ p $ ( $ 2<=N<=100000 $ , $ 2<=p<=10000 $ ) – the number of elements in $ A $ , and the modulo for computing scores, respectively.

The second line contains $ N $ space-separated integers which are the elements of $ A $ . Each integer is from the interval $ [1,1000000] $ .

## 输出格式

Output the number $ S $ as described in the problem statement.

## 说明/提示

In the first example, the score is maximized if the input sequence is split into two parts as $ (3,4) $ , $ (7,2) $ . It gives the total score of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF958C1/39bbc2e047bed6ad62ef40401430a139534974d3.png).

In the second example, the score is maximized if the first part consists of the first three elements, and the second part consists of the rest. Then, the score is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF958C1/d991bcec92c9c10d8e1b00b096112e99ba9e2d35.png).

## 样例 #1

### 输入

```
4 10
3 4 7 2

```

### 输出

```
16

```

## 样例 #2

### 输入

```
10 12
16 3 24 13 9 8 7 5 12 12

```

### 输出

```
13

```



---

---
title: "Messages"
layout: "post"
diff: 普及-
pid: CF964B
tag: ['贪心', '枚举', '概率论']
---

# Messages

## 题目描述

------------

Vasya有n封信。第i封信将在ti秒之后接收。 每封信都开始都值a元，但收到消息后，消息的成本每分钟减少B元(B可能变为负数)。Vasya可以在任意时刻接收到任何消息，也可在任意时刻读取它。读完消息后，Vasya的银行账户会收到该消息的当前成本。最初，Vasya的银行账户为0。 同时,每分钟Vasya的银行账户会收到C·k元,k是收到了但未读信的数量。 Vasya非常贪婪（又一个葛朗台），正因为如此，他想让所有的信息在T分钟后被阅读，使其利益最大化。


------------

## 输入格式

------------

第一行输入5个数 n , A , B , C 与 T
( 1<=n,A,B,C,T<=1000 ).
第二个字符串包含n个整数
ti
​ ( 1<=ti<=T ）


------------

## 输出格式

------------



------------

输出一个整数，问题的答案。

## 样例 #1

### 输入

```
4 5 5 3 5
1 5 5 4

```

### 输出

```
20

```

## 样例 #2

### 输入

```
5 3 1 1 3
2 2 2 1 1

```

### 输出

```
15

```

## 样例 #3

### 输入

```
5 5 3 4 5
1 2 3 4 5

```

### 输出

```
35

```



---

---
title: "Two-gram"
layout: "post"
diff: 普及-
pid: CF977B
tag: ['字符串', '枚举']
---

# Two-gram

## 题目描述

Two-gram is an ordered pair (i.e. string of length two) of capital Latin letters. For example, "AZ", "AA", "ZA" — three distinct two-grams.

You are given a string $ s $ consisting of $ n $ capital Latin letters. Your task is to find any two-gram contained in the given string as a substring (i.e. two consecutive characters of the string) maximal number of times. For example, for string $ s $ = "BBAABBBA" the answer is two-gram "BB", which contained in $ s $ three times. In other words, find any most frequent two-gram.

Note that occurrences of the two-gram can overlap with each other.

## 输入格式

The first line of the input contains integer number $ n $ ( $ 2 \le n \le 100 $ ) — the length of string $ s $ . The second line of the input contains the string $ s $ consisting of $ n $ capital Latin letters.

## 输出格式

Print the only line containing exactly two capital Latin letters — any two-gram contained in the given string $ s $ as a substring (i.e. two consecutive characters of the string) maximal number of times.

## 说明/提示

In the first example "BA" is also valid answer.

In the second example the only two-gram "ZZ" can be printed because it contained in the string "ZZZAA" two times.

## 样例 #1

### 输入

```
7
ABACABA

```

### 输出

```
AB

```

## 样例 #2

### 输入

```
5
ZZZAA

```

### 输出

```
ZZ

```



---

---
title: "Switches and Lamps"
layout: "post"
diff: 普及-
pid: CF985B
tag: ['枚举', '概率论']
---

# Switches and Lamps

## 题目描述

You are given $ n $ switches and $ m $ lamps. The $ i $ -th switch turns on some subset of the lamps. This information is given as the matrix $ a $ consisting of $ n $ rows and $ m $ columns where $ a_{i,j}=1 $ if the $ i $ -th switch turns on the $ j $ -th lamp and $ a_{i,j}=0 $ if the $ i $ -th switch is not connected to the $ j $ -th lamp.

Initially all $ m $ lamps are turned off.

Switches change state only from "off" to "on". It means that if you press two or more switches connected to the same lamp then the lamp will be turned on after any of this switches is pressed and will remain its state even if any switch connected to this lamp is pressed afterwards.

It is guaranteed that if you push all $ n $ switches then all $ m $ lamps will be turned on.

Your think that you have too many switches and you would like to ignore one of them.

Your task is to say if there exists such a switch that if you will ignore (not use) it but press all the other $ n-1 $ switches then all the $ m $ lamps will be turned on.

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ ( $ 1<=n,m<=2000 $ ) — the number of the switches and the number of the lamps.

The following $ n $ lines contain $ m $ characters each. The character $ a_{i,j} $ is equal to '1' if the $ i $ -th switch turns on the $ j $ -th lamp and '0' otherwise.

It is guaranteed that if you press all $ n $ switches all $ m $ lamps will be turned on.

## 输出格式

Print "YES" if there is a switch that if you will ignore it and press all the other $ n-1 $ switches then all $ m $ lamps will be turned on. Print "NO" if there is no such switch.

## 样例 #1

### 输入

```
4 5
10101
01000
00111
10000

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
4 5
10100
01000
00110
00101

```

### 输出

```
NO

```



---

---
title: "Hexadecimal's Numbers"
layout: "post"
diff: 普及-
pid: CF9C
tag: ['递归', '枚举', '进制', '队列']
---

# Hexadecimal's Numbers

## 题目描述

One beautiful July morning a terrible thing happened in Mainframe: a mean virus Megabyte somehow got access to the memory of his not less mean sister Hexadecimal. He loaded there a huge amount of $ n $ different natural numbers from 1 to $ n $ to obtain total control over her energy.

But his plan failed. The reason for this was very simple: Hexadecimal didn't perceive any information, apart from numbers written in binary format. This means that if a number in a decimal representation contained characters apart from 0 and 1, it was not stored in the memory. Now Megabyte wants to know, how many numbers were loaded successfully.

## 输入格式

Input data contains the only number $ n $ ( $ 1<=n<=10^{9} $ ).

## 输出格式

Output the only number — answer to the problem.

## 说明/提示

For $ n $ = 10 the answer includes numbers 1 and 10.

## 样例 #1

### 输入

```
10

```

### 输出

```
2
```



---

