---
title: "Polycarp's Pockets"
layout: "post"
diff: 入门
pid: CF1003A
tag: ['枚举']
---

# Polycarp's Pockets

## 题目描述

题意   
输入$n$个数，输出其中最多有多少个数是相同的。

## 输入格式

第一行为一个整数$n$ ( 1 $\le$ $n$ $\le$ 100 ) , 第二行为$n$个整数。

## 输出格式

一个整数，表示其中最多相同的数的个数。

## 样例 #1

### 输入

```
6
1 2 4 3 3 2

```

### 输出

```
2

```

## 样例 #2

### 输入

```
1
100

```

### 输出

```
1

```



---

---
title: "The Rank"
layout: "post"
diff: 入门
pid: CF1017A
tag: ['枚举', '排序']
---

# The Rank

## 题目描述

John Smith knows that his son, Thomas Smith, is among the best students in his class and even in his school. After the students of the school took the exams in English, German, Math, and History, a table of results was formed.

There are $ n $ students, each of them has a unique id (from $ 1 $ to $ n $ ). Thomas's id is $ 1 $ . Every student has four scores correspond to his or her English, German, Math, and History scores. The students are given in order of increasing of their ids.

In the table, the students will be sorted by decreasing the sum of their scores. So, a student with the largest sum will get the first place. If two or more students have the same sum, these students will be sorted by increasing their ids.

Please help John find out the rank of his son.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 1000 $ ) — the number of students.

Each of the next $ n $ lines contains four integers $ a_i $ , $ b_i $ , $ c_i $ , and $ d_i $ ( $ 0\leq a_i, b_i, c_i, d_i\leq 100 $ ) — the grades of the $ i $ -th student on English, German, Math, and History. The id of the $ i $ -th student is equal to $ i $ .

## 输出格式

Print the rank of Thomas Smith. Thomas's id is $ 1 $ .

## 说明/提示

In the first sample, the students got total scores: $ 398 $ , $ 400 $ , $ 398 $ , $ 379 $ , and $ 357 $ . Among the $ 5 $ students, Thomas and the third student have the second highest score, but Thomas has a smaller id, so his rank is $ 2 $ .

In the second sample, the students got total scores: $ 369 $ , $ 240 $ , $ 310 $ , $ 300 $ , $ 300 $ , and $ 0 $ . Among the $ 6 $ students, Thomas got the highest score, so his rank is $ 1 $ .

## 样例 #1

### 输入

```
5
100 98 100 100
100 100 100 100
100 100 99 99
90 99 90 100
100 98 60 99

```

### 输出

```
2

```

## 样例 #2

### 输入

```
6
100 80 90 99
60 60 60 60
90 60 100 60
60 100 60 80
100 100 0 100
0 0 0 0

```

### 输出

```
1

```



---

---
title: "Cifera"
layout: "post"
diff: 入门
pid: CF114A
tag: ['模拟', '枚举', '进制']
---

# Cifera

## 题目描述

When Petya went to school, he got interested in large numbers and what they were called in ancient times. For instance, he learned that the Russian word "tma" (which now means "too much to be counted") used to stand for a thousand and "tma tmyschaya" (which literally means "the tma of tmas") used to stand for a million.

Petya wanted to modernize the words we use for numbers and invented a word petricium that represents number $ k $ . Moreover, petricium la petricium stands for number $ k^{2} $ , petricium la petricium la petricium stands for $ k^{3} $ and so on. All numbers of this form are called petriciumus cifera, and the number's importance is the number of articles la in its title.

Petya's invention brought on a challenge that needed to be solved quickly: does some number $ l $ belong to the set petriciumus cifera? As Petya is a very busy schoolboy he needs to automate the process, he asked you to solve it.

## 输入格式

The first input line contains integer number $ k $ , the second line contains integer number $ l $ ( $ 2<=k,l<=2^{31}-1 $ ).

## 输出格式

You should print in the first line of the output "YES", if the number belongs to the set petriciumus cifera and otherwise print "NO". If the number belongs to the set, then print on the seconds line the only number — the importance of number $ l $ .

## 样例 #1

### 输入

```
5
25

```

### 输出

```
YES
1

```

## 样例 #2

### 输入

```
3
8

```

### 输出

```
NO

```



---

---
title: "String Task"
layout: "post"
diff: 入门
pid: CF118A
tag: ['模拟', '字符串', '枚举']
---

# String Task

## 题目描述

Petya started to attend programming lessons. On the first lesson his task was to write a simple program. The program was supposed to do the following: in the given string, consisting if uppercase and lowercase Latin letters, it:

- deletes all the vowels,
- inserts a character "." before each consonant,
- replaces all uppercase consonants with corresponding lowercase ones.

Vowels are letters "A", "O", "Y", "E", "U", "I", and the rest are consonants. The program's input is exactly one string, it should return the output as a single string, resulting after the program's processing the initial string.

Help Petya cope with this easy task.

## 输入格式

The first line represents input string of Petya's program. This string only consists of uppercase and lowercase Latin letters and its length is from $ 1 $ to $ 100 $ , inclusive.

## 输出格式

Print the resulting string. It is guaranteed that this string is not empty.

## 样例 #1

### 输入

```
tour

```

### 输出

```
.t.r

```

## 样例 #2

### 输入

```
Codeforces

```

### 输出

```
.c.d.f.r.c.s

```

## 样例 #3

### 输入

```
aBAcAba

```

### 输出

```
.b.c.b

```



---

---
title: "The number of positions"
layout: "post"
diff: 入门
pid: CF124A
tag: ['模拟', '数学', '枚举']
---

# The number of positions

## 题目描述

Translated by @隐鬼在侧

## 样例 #1

### 输入

```
3 1 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5 2 3

```

### 输出

```
3

```



---

---
title: "Super Agent"
layout: "post"
diff: 入门
pid: CF12A
tag: ['模拟', '字符串', '枚举']
---

# Super Agent

## 题目描述

There is a very secret base in Potatoland where potato mash is made according to a special recipe. The neighbours from Porridgia decided to seize this recipe and to sell it to Pilauland. For this mission they have been preparing special agent Pearlo for many years. When, finally, Pearlo learned all secrets of espionage, he penetrated into the Potatoland territory and reached the secret base.

Now he is standing at the entrance, but to get inside he need to pass combination lock. Minute ago one of the workers entered the password on the terminal and opened the door. The terminal is a square digital keyboard $ 3×3 $ with digits from $ 1 $ to $ 9 $ .

Pearlo knows that the password consists from distinct digits and is probably symmetric with respect to the central button of the terminal. He has heat sensor which allowed him to detect the digits which the worker pressed. Now he wants to check whether the password entered by the worker is symmetric with respect to the central button of the terminal. This fact can Help Pearlo to reduce the number of different possible password combinations.

## 输入格式

Input contains the matrix of three rows of three symbols each. Symbol «X» means that the corresponding button was pressed, and «.» means that is was not pressed. The matrix may contain no «X», also it may contain no «.».

## 输出格式

Print YES if the password is symmetric with respect to the central button of the terminal and NO otherwise.

## 说明/提示

If you are not familiar with the term «central symmetry», you may look into http://en.wikipedia.org/wiki/Central\_symmetry

## 样例 #1

### 输入

```
XX.
...
.XX

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
X.X
X..
...

```

### 输出

```
NO

```



---

---
title: "HQ9+"
layout: "post"
diff: 入门
pid: CF133A
tag: ['字符串', '枚举']
---

# HQ9+

## 题目描述

HQ9+是一种搞笑的编程语言，只有4种指令，都是单个字符的：
"H"输出"Hello, World!"；
"Q"输出这个程序本身的源代码；
"9"输出歌曲"99 Bottles of Beer"的歌词（你可以自己上网搜这首歌）；
"+"增加内部储存中的数值

注意"H"和"Q"指令是区分大小写的，必须使用大写。程序中不属于这些指令的字符请忽略。

给你一个用HQ9+写的程序，问这个程序是否会有任何输出。

## 输入格式

输入有一行，p是这个HQ9+的程序。字符串p的长度在1和100之间，包括1和100。字符串p中每一个字符的ASCII码在33('!'感叹号)和126('~'波浪)之间，包括33和126。

## 输出格式

如果这个程序有输出，输出"YES"，否则输出"NO"。

## 说明/提示

第一个样例中只有一个指令"H"，输出了"Hello, World!"。

第二个样例中没有任何一个字符是这个程序的指令。
翻译贡献者UID：68708

## 样例 #1

### 输入

```
Hi!

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
Codeforces

```

### 输出

```
NO

```



---

---
title: "Flag"
layout: "post"
diff: 入门
pid: CF16A
tag: ['模拟', '字符串', '枚举']
---

# Flag

## 题目描述

根据一项新的 ISO 标准，每一个国家的国旗应该是一个 $n\times m$ 的格子场，其中每个格子最多有 $10$ 种不同的颜色。并且国旗应该有条纹：旗帜的每一行应包含相同颜色的方块，相邻的行的颜色应该是不同的。Berland 政府要求你找出他们的国旗是否符合新的 ISO 标准。

## 输入格式

输入的第一行包含数 $n$ 和 $m$，其中 $n$ 为行数，$m$ 为列数。

接下来是对旗的描述：以下 $n$ 行中的每一行包含 $m$ 个字符。每个字符是 $0$ 到 $9$ 之间的数字，代表相应正方形的颜色。

## 输出格式

如果国旗符合标准就输出 `YES`，否则输出 `NO`。

## 样例 #1

### 输入

```
3 3
000
111
222

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
3 3
000
000
111

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
3 3
000
111
002

```

### 输出

```
NO

```



---

---
title: "Maximum Substring"
layout: "post"
diff: 入门
pid: CF1750B
tag: ['枚举']
---

# Maximum Substring

## 题目描述

A binary string is a string consisting only of the characters 0 and 1. You are given a binary string $ s $ .

For some non-empty substring $ ^\dagger $ $ t $ of string $ s $ containing $ x $ characters 0 and $ y $ characters 1, define its cost as:

- $ x \cdot y $ , if $ x > 0 $ and $ y > 0 $ ;
- $ x^2 $ , if $ x > 0 $ and $ y = 0 $ ;
- $ y^2 $ , if $ x = 0 $ and $ y > 0 $ .

Given a binary string $ s $ of length $ n $ , find the maximum cost across all its non-empty substrings.

 $ ^\dagger $ A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^5 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the string $ s $ .

The second line of each test case contains a binary string $ s $ of length $ n $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print a single integer — the maximum cost across all substrings.

## 说明/提示

In the first test case, we can take a substring $ 111 $ . It contains $ 3 $ characters 1 and $ 0 $ characters 0. So $ a = 3 $ , $ b = 0 $ and its cost is $ 3^2 = 9 $ .

In the second test case, we can take the whole string. It contains $ 4 $ characters 1 and $ 3 $ characters 0. So $ a = 4 $ , $ b = 3 $ and its cost is $ 4 \cdot 3 = 12 $ .

In the third test case, we can can take a substring $ 1111 $ and its cost is $ 4^2 = 16 $ .

In the fourth test case, we can take the whole string and cost is $ 4 \cdot 3 = 12 $ .

In the fifth test case, we can take a substring $ 000 $ and its cost is $ 3 \cdot 3 = 9 $ .

In the sixth test case, we can only take the substring $ 0 $ and its cost is $ 1 \cdot 1 = 1 $ .

## 样例 #1

### 输入

```
6
5
11100
7
1100110
6
011110
7
1001010
4
1000
1
0
```

### 输出

```
9
12
16
12
9
1
```



---

---
title: "LOL Lovers"
layout: "post"
diff: 入门
pid: CF1912L
tag: ['枚举', '前缀和']
---

# LOL Lovers

## 题目描述

There are $ n $ food items lying in a row on a long table. Each of these items is either a loaf of bread (denoted as a capital Latin letter 'L' with ASCII code 76) or an onion (denoted as a capital Latin letter 'O' with ASCII code 79). There is at least one loaf of bread and at least one onion on the table.

You and your friend want to divide the food on the table: you will take a prefix of this row (several leftmost items), and the friend will take the rest. However, there are several restrictions:

1. Each person should have at least one item.
2. The number of your loaves should differ from the number of your friend's loaves.
3. The number of your onions should differ from the number of your friend's onions.

 Find any correct division and print the number of items you take or report that there is no answer.

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 200 $ ) — the number of food items on the table. The second line contains a string of length $ n $ consisting of letters 'L' and 'O'. $ i $ -th symbol represents the type of the $ i $ -th food item on the table: 'L' stands for a loaf of bread, and 'O' stands for an onion. It is guaranteed that this string contains at least one letter 'L' and at least one letter 'O'.

## 输出格式

Print one integer — a number $ k $ such that, if you take $ k $ leftmost items and your friend takes the remaining $ n - k $ items, each of you and your friend get at least one item, your number of loaves is different from your friend's, and your number of onions is different from your friend's. If there are several possible answers, print any of them. If there are no possible answers, print the number $ -1 $ .

## 说明/提示

In the first example, in any division the left and the right part contain one loaf of bread.

In the second example, the division is 'L' and 'O', and in these two strings the number of loaves is different (1 and 0) and the number of onions is different (0 and 1).

In the third example, any number 1, 2 or 3 is a correct answer.

## 样例 #1

### 输入

```
3
LOL
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
2
LO
```

### 输出

```
1
```

## 样例 #3

### 输入

```
4
LLLO
```

### 输出

```
1
```

## 样例 #4

### 输入

```
4
OLOL
```

### 输出

```
-1
```

## 样例 #5

### 输入

```
10
LLOOOOLLLO
```

### 输出

```
5
```



---

---
title: "Race"
layout: "post"
diff: 入门
pid: CF2112A
tag: ['数学', '枚举']
---

# Race

## 题目描述

Alice 和 Bob 正在参加一场电视节目的游戏。游戏开始的时候，奖品会被放在某个点上，第一个到达奖品所在位置的人将获得奖品。

Alice 决定她将从点 $a$ 起跑。Bob 还没有决定他的出发点。

Bob 知道奖品会落在点 $x$ 或点 $y$ 处，他可以在 Alice 之前到达奖品的位置当且仅当他的出发点和奖品的距离严格小于 Alice 的出发点和奖品的距离。点 $c$ 和点 $d$ 之间的距离是 $\vert c-d\vert$。

你的任务是回答 Bob 能不能选出一个整点，使得无论奖品是在点 $x$ 还是点 $y$ 处出现，都能保证他比 Alice 先到达奖品处。他可以选择除了 $a$ 以外的所有整点，包括 $x$ 和 $y$。

## 输入格式

多组数据。第一行一个整数 $t(1\le t\le 1000)$，表示数据组数。

对于每组数据，一行三个整数 $a,x,y(1\le a,x,y\le 100)$。三个数字两两不同。

## 输出格式

对于每组数据，如果答案为可以，那么输出一行一个字符串 `YES`；否则输出一行一个字符串 `NO`。

## 说明/提示

**样例解释**

对于第一组数据，Bob 可以选择点 $4$，如果奖品出现在点 $x$，Bob 和它之间的距离为 $\vert 4-3\vert=1$，Alice 和它之间的距离为 $\vert 1-3\vert=2$。如果奖品出现在点 $y$，Bob 和它之间的距离为 $\vert 4-4\vert=0$，Alice 和它之间的距离为 $\vert 1-4\vert=3$。

对于第二组数据，Bob 可以选择点 $2$，如果奖品出现在点 $x$，Bob 和它之间的距离为 $\vert 2-3\vert=1$，Alice 和它之间的距离为 $\vert 5-3\vert=2$。如果奖品出现在点 $y$，Bob 和它之间的距离为 $\vert 2-1\vert=1$，Alice 和它之间的距离为 $\vert 5-1\vert=4$。

对于第三组数据，Bob 无法选择一个点保证自己胜利。


## 样例 #1

### 输入

```
3
1 3 4
5 3 1
3 1 5
```

### 输出

```
YES
YES
NO
```



---

---
title: "System of Equations"
layout: "post"
diff: 入门
pid: CF214A
tag: ['枚举', '概率论']
---

# System of Equations

## 题目描述

Furik "非常喜欢" 数学课, 所以他从不去上课, 不像 Rubik. 但是现在Furik想要得到一个好一点的数学成绩. 为此, 他的数学老师Ms. Ivanova给了他一个新任务. Furik一瞬间就搞定了. 你行吗?



给你一个如下的等式方程组:



![](https://cdn.luogu.org/upload/vjudge_pic/CF214A/62e1cfae0726c97a669dda13cb6a561eafa52412.png)你的任务是计算, 有多少组整数(a,b)(0<=a,b)满足这个方程组.

## 输入格式

仅一行, 包含两个整数 n,m (1<=n,m<=1000) — 该方程组的参数. 由一个空格分隔.

## 输出格式

输出答案, 仅一行.

## 样例 #1

### 输入

```
9 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
14 28

```

### 输出

```
1

```

## 样例 #3

### 输入

```
4 20

```

### 输出

```
0

```



---

---
title: "You're Given a String..."
layout: "post"
diff: 入门
pid: CF23A
tag: ['字符串', '枚举']
---

# You're Given a String...

## 题目描述

You're given a string of lower-case Latin letters. Your task is to find the length of its longest substring that can be met in the string at least twice. These occurrences can overlap (see sample test 2).

## 输入格式

The first input line contains the string. It's guaranteed, that the string is non-empty, consists of lower-case Latin letters, and its length doesn't exceed 100.

## 输出格式

Output one number — length of the longest substring that can be met in the string at least twice.

## 样例 #1

### 输入

```
abcd

```

### 输出

```
0
```

## 样例 #2

### 输入

```
ababa

```

### 输出

```
3
```

## 样例 #3

### 输入

```
zzz

```

### 输出

```
2
```



---

---
title: "Almost Prime"
layout: "post"
diff: 入门
pid: CF26A
tag: ['枚举', '剪枝', '素数判断,质数,筛法']
---

# Almost Prime

## 题目描述

一个数如果恰好有两个不同质因子，那它被叫做几乎是质数的数。例如：`6,18,24`就是几乎是质数的数，而`4,8,9,42`不是，请你找出 $1$ 到 $n$ 中几乎是质数的数有多少个。

## 输入格式

输入仅包含一个整数 $n$（$1\leq n\leq3000$）。

## 输出格式

输出 $1$ 到 $n$ 中几乎是质数的数的数量。

Translated by Khassar

## 样例 #1

### 输入

```
10

```

### 输出

```
2

```

## 样例 #2

### 输入

```
21

```

### 输出

```
8

```



---

---
title: "Beautiful Year"
layout: "post"
diff: 入门
pid: CF271A
tag: ['模拟', '字符串', '枚举']
---

# Beautiful Year

## 题目描述

It seems like the year of 2013 came only yesterday. Do you know a curious fact? The year of 2013 is the first year after the old 1987 with only distinct digits.

Now you are suggested to solve the following problem: given a year number, find the minimum year number which is strictly larger than the given one and has only distinct digits.

## 输入格式

The single line contains integer $ y $ $ (1000<=y<=9000) $ — the year number.

## 输出格式

Print a single integer — the minimum year number that is strictly larger than $ y $ and all it's digits are distinct. It is guaranteed that the answer exists.

## 样例 #1

### 输入

```
1987

```

### 输出

```
2013

```

## 样例 #2

### 输入

```
2013

```

### 输出

```
2014

```



---

---
title: "Next Test"
layout: "post"
diff: 入门
pid: CF27A
tag: ['枚举', '概率论']
---

# Next Test

## 题目描述

### 题面描述

给出 $n$ 个互不相同的整数 $a_i$ ，从小到大找第一个没有出现过的整数。

## 输入格式

第一行一个正整数 $n$ ，之后是 $n$ 个整数 $a_i$ 。

## 输出格式

一个整数 $x$ ，即第一个没有出现过的整数。

## 说明/提示

$1\leq n\leq 3000$

 $1\leq a_i\leq 3000$

## 样例 #1

### 输入

```
3
1 7 2

```

### 输出

```
3

```



---

---
title: "Spit Problem"
layout: "post"
diff: 入门
pid: CF29A
tag: ['模拟', '枚举', '排序']
---

# Spit Problem

## 题目描述

In a Berland's zoo there is an enclosure with camels. It is known that camels like to spit. Bob watched these interesting animals for the whole day and registered in his notepad where each animal spitted. Now he wants to know if in the zoo there are two camels, which spitted at each other. Help him to solve this task.

The trajectory of a camel's spit is an arc, i.e. if the camel in position $ x $ spits $ d $ meters right, he can hit only the camel in position $ x+d $ , if such a camel exists.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=100 $ ) — the amount of camels in the zoo. Each of the following $ n $ lines contains two integers $ x_{i} $ and $ d_{i} $ ( $ -10^{4}<=x_{i}<=10^{4},1<=|d_{i}|<=2·10^{4} $ ) — records in Bob's notepad. $ x_{i} $ is a position of the $ i $ -th camel, and $ d_{i} $ is a distance at which the $ i $ -th camel spitted. Positive values of $ d_{i} $ correspond to the spits right, negative values correspond to the spits left. No two camels may stand in the same position.

## 输出格式

If there are two camels, which spitted at each other, output YES. Otherwise, output NO.

## 样例 #1

### 输入

```
2
0 1
1 -1

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
3
0 1
1 1
2 -2

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
5
2 -10
3 10
0 5
5 -5
10 1

```

### 输出

```
YES

```



---

---
title: "Laptops"
layout: "post"
diff: 入门
pid: CF456A
tag: ['贪心', '枚举', '排序']
---

# Laptops

## 题目描述

有一天Dima和Alex正在讨论关于 $n$ 台笔记本电脑的价格与质量。Dima认为价格高的笔记本质量也高，而Alex认为笔记本是物美价廉，价格低的笔记本质量反而高。

正当他们争（吵）论得不可开交之时，您过来了。现在您需要写出一个程序去确认谁是谁非。

## 输入格式

第一行输入笔记本个数 $n$ $(n \leqslant 10^5)$ 。

接下来的 $n$ 行输入两个数,分别是第 $n$ 个笔记本的价值 $a_i$ 与质量 $b_i$。

保证所有的 $a_i$ 与 $b_i$ 不同，且属于 $int$ 范围。

## 输出格式

如果存在符合Alex的要求的两台笔记本电脑（即一台的价格比另一台低且质量比另一台高），则输出"Happy Alex"，否则输出"Poor Alex"。

翻译提供者：Black_white_tony

## 样例 #1

### 输入

```
2
1 2
2 1

```

### 输出

```
Happy Alex

```



---

---
title: "Triangular numbers"
layout: "post"
diff: 入门
pid: CF47A
tag: ['搜索', '数学', '枚举']
---

# Triangular numbers

## 题目描述

A triangular number is the number of dots in an equilateral triangle uniformly filled with dots. For example, three dots can be arranged in a triangle; thus three is a triangular number. The $ n $ -th triangular number is the number of dots in a triangle with $ n $ dots on a side. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF47A/7344b4fd5acb7c973775cffc0c5a51a81c6ee4d9.png). You can learn more about these numbers from Wikipedia (http://en.wikipedia.org/wiki/Triangular\_number).

Your task is to find out if a given integer is a triangular number.

## 输入格式

The first line contains the single number $ n $ ( $ 1<=n<=500 $ ) — the given integer.

## 输出格式

If the given integer is a triangular number output YES, otherwise output NO.

## 样例 #1

### 输入

```
1

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
2

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
3

```

### 输出

```
YES

```



---

---
title: "Rock-paper-scissors"
layout: "post"
diff: 入门
pid: CF48A
tag: ['字符串', '枚举']
---

# Rock-paper-scissors

## 题目描述

### 题面描述

三个人玩石头剪刀布，问谁赢了。

## 输入格式

输入三行，每行一个字符串（`rock`(石头)，`scissors`(剪刀)，`paper`(布)），分别表示这三个人出的手势。

石头打破剪刀，剪刀剪纸，纸裹在石头上。

当有一个人同时赢过其他两人时，他获胜，否则胜负不分。

## 输出格式

如果第一个人赢了输出`F`，第二个人赢了输出`M`，第三个人赢了输出`S`，胜负不分输出`?`。
Translated by Khassar

## 样例 #1

### 输入

```
rock
rock
rock

```

### 输出

```
?

```

## 样例 #2

### 输入

```
paper
rock
rock

```

### 输出

```
F

```

## 样例 #3

### 输入

```
scissors
rock
rock

```

### 输出

```
?

```

## 样例 #4

### 输入

```
scissors
paper
rock

```

### 输出

```
?

```



---

---
title: "Vanya and Cubes"
layout: "post"
diff: 入门
pid: CF492A
tag: ['模拟', '数学', '枚举']
---

# Vanya and Cubes

## 题目描述

Vanya got $ n $ cubes. He decided to build a pyramid from them. Vanya wants to build the pyramid as follows: the top level of the pyramid must consist of $ 1 $ cube, the second level must consist of $ 1+2=3 $ cubes, the third level must have $ 1+2+3=6 $ cubes, and so on. Thus, the $ i $ -th level of the pyramid must have $ 1+2+...+(i-1)+i $ cubes.

Vanya wants to know what is the maximum height of the pyramid that he can make using the given cubes.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{4} $ ) — the number of cubes given to Vanya.

## 输出格式

Print the maximum possible height of the pyramid in the single line.

## 说明/提示

Illustration to the second sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF492A/95fc6e512a79cba53044cb07f98e0b0b07a634cb.png)

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
25

```

### 输出

```
4

```



---

---
title: "Watermelon"
layout: "post"
diff: 入门
pid: CF4A
tag: ['数学', '枚举']
---

# Watermelon

## 题目描述

一个炎热的夏天，Pete 和他的朋友 Billy 感到十分口渴，于是在西瓜摊上买了一个重 $w$ 公斤的西瓜。

他们回到家准备分西瓜。因为两个人都十分喜爱偶数，所以他们俩希望分出来的两块西瓜的重量都是偶数公斤。帮助他们判断是否可能做到这一点。

## 输入格式

一行一个整数 $w\,(0\le w\le100)$。

## 输出格式

如果可以按照他们的意愿分配西瓜，输出 `YES`；否则输出 `NO`。

### 样例 #1 解释

他们可以将西瓜分成 $2$ 公斤和 $6$ 公斤。

-----

翻译 By @[Eason_cyx](https://www.luogu.com.cn/user/741244)。

## 样例 #1

### 输入

```
8

```

### 输出

```
YES

```



---

---
title: "Pangram"
layout: "post"
diff: 入门
pid: CF520A
tag: ['模拟', '字符串', '二分', '枚举']
---

# Pangram

## 题目描述

A word or a sentence in some language is called a pangram if all the characters of the alphabet of this language appear in it at least once. Pangrams are often used to demonstrate fonts in printing or test the output devices.

You are given a string consisting of lowercase and uppercase Latin letters. Check whether this string is a pangram. We say that the string contains a letter of the Latin alphabet if this letter occurs in the string in uppercase or lowercase.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=100 $ ) — the number of characters in the string.

The second line contains the string. The string consists only of uppercase and lowercase Latin letters.

## 输出格式

Output "YES", if the string is a pangram and "NO" otherwise.

## 样例 #1

### 输入

```
12
toosmallword

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
35
TheQuickBrownFoxJumpsOverTheLazyDog

```

### 输出

```
YES

```



---

---
title: "Chat room"
layout: "post"
diff: 入门
pid: CF58A
tag: ['模拟', '字符串', '枚举', '队列']
---

# Chat room

## 题目描述

Vasya has recently learned to type and log on to the Internet. He immediately entered a chat room and decided to say hello to everybody. Vasya typed the word $ s $ . It is considered that Vasya managed to say hello if several letters can be deleted from the typed word so that it resulted in the word "hello". For example, if Vasya types the word "ahhellllloou", it will be considered that he said hello, and if he types "hlelo", it will be considered that Vasya got misunderstood and he didn't manage to say hello. Determine whether Vasya managed to say hello by the given word $ s $ .

## 输入格式

The first and only line contains the word $ s $ , which Vasya typed. This word consisits of small Latin letters, its length is no less that 1 and no more than 100 letters.

## 输出格式

If Vasya managed to say hello, print "YES", otherwise print "NO".

## 样例 #1

### 输入

```
ahhellllloou

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
hlelo

```

### 输出

```
NO

```



---

---
title: "Far Relative’s Birthday Cake"
layout: "post"
diff: 入门
pid: CF629A
tag: ['枚举', '深度优先搜索 DFS']
---

# Far Relative’s Birthday Cake

## 题目描述

多尔的家人正在庆祝多尔的生日派对。他们爱多尔，所以他们计划让他的生日蛋糕变得不可思议的！

蛋糕是一个由n×n的等边正方形组成的形状，长度为1。每个方块要么是空的，要么是由一个巧克力组成的。他们买了蛋糕，便开始把巧克力放在蛋糕上。“家庭之门”的幸福值等于蛋糕中同一行或同一列中装有巧克力的一对细胞的数量。多尔的家人想知道他们的幸福程度是多少？

## 输入格式

第一行输入一个整数n（1<=n<=100)，表示蛋糕边的长度。然后输入n行数，每行有n个字符。空的细胞用'.'表示，而含有巧克力的细胞用“C”表示。

## 输出格式

输出“家庭之门”幸福感的价值，即同一行或同一列的一对巧克力片的数量。

## 样例 #1

### 输入

```
3
.CC
C..
C.C

```

### 输出

```
4

```

## 样例 #2

### 输入

```
4
CC..
C..C
.CC.
.CC.

```

### 输出

```
9

```



---

---
title: "Ebony and Ivory"
layout: "post"
diff: 入门
pid: CF633A
tag: ['枚举']
---

# Ebony and Ivory

## 题目描述

Dante is engaged in a fight with "The Savior". Before he can fight it with his sword, he needs to break its shields. He has two guns, Ebony and Ivory, each of them is able to perform any non-negative number of shots.

For every bullet that hits the shield, Ebony deals $ a $ units of damage while Ivory deals $ b $ units of damage. In order to break the shield Dante has to deal exactly $ c $ units of damage. Find out if this is possible.

## 输入格式

The first line of the input contains three integers $ a $ , $ b $ , $ c $ ( $ 1<=a,b<=100,1<=c<=10000 $ ) — the number of units of damage dealt by Ebony gun and Ivory gun, and the total number of damage required to break the shield, respectively.

## 输出格式

Print "Yes" (without quotes) if Dante can deal exactly $ c $ damage to the shield and "No" (without quotes) otherwise.

## 说明/提示

In the second sample, Dante can fire $ 1 $ bullet from Ebony and $ 2 $ from Ivory to deal exactly $ 1·3+2·2=7 $ damage. In the third sample, Dante can fire $ 1 $ bullet from ebony and no bullets from ivory to do $ 1·6+0·11=6 $ damage.

## 样例 #1

### 输入

```
4 6 15

```

### 输出

```
No

```

## 样例 #2

### 输入

```
3 2 7

```

### 输出

```
Yes

```

## 样例 #3

### 输入

```
6 11 6

```

### 输出

```
Yes

```



---

---
title: "Summer Camp"
layout: "post"
diff: 入门
pid: CF672A
tag: ['字符串', '枚举']
---

# Summer Camp

## 题目描述

Every year, hundreds of people come to summer camps, they learn new algorithms and solve hard problems.

This is your first year at summer camp, and you are asked to solve the following problem. All integers starting with $ 1 $ are written in one line. The prefix of these line is "123456789101112131415...". Your task is to print the $ n $ -th digit of this string (digits are numbered starting with $ 1 $ .

## 输入格式

The only line of the input contains a single integer $ n $ ( $ 1<=n<=1000 $ ) — the position of the digit you need to print.

## 输出格式

Print the $ n $ -th digit of the line.

## 说明/提示

In the first sample the digit at position $ 3 $ is '3', as both integers $ 1 $ and $ 2 $ consist on one digit.

In the second sample, the digit at position $ 11 $ is '0', it belongs to the integer $ 10 $ .

## 样例 #1

### 输入

```
3

```

### 输出

```
3

```

## 样例 #2

### 输入

```
11

```

### 输出

```
0

```



---

---
title: "Irrational problem"
layout: "post"
diff: 入门
pid: CF68A
tag: ['字符串', '枚举']
---

# Irrational problem

## 题目描述

Little Petya was given this problem for homework:

You are given function ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF68A/8b7b3ed792043adfb79a0ac45ad9dbf53894718f.png) (here ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF68A/99fd5677ca5c02520be7595d9b1eaf3e9972e601.png) represents the operation of taking the remainder). His task is to count the number of integers $ x $ in range $ [a;b] $ with property $ f(x)=x $ .

It is a pity that Petya forgot the order in which the remainders should be taken and wrote down only 4 numbers. Each of 24 possible orders of taking the remainder has equal probability of being chosen. For example, if Petya has numbers 1, 2, 3, 4 then he can take remainders in that order or first take remainder modulo 4, then modulo 2, 3, 1. There also are 22 other permutations of these numbers that represent orders in which remainder can be taken. In this problem 4 numbers wrote down by Petya will be pairwise distinct.

Now it is impossible for Petya to complete the task given by teacher but just for fun he decided to find the number of integers ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF68A/5fea0bb6257453a51324f60c43779399607ff809.png) with property that probability that $ f(x)=x $ is not less than $ 31.4159265352718281828459045% $ . In other words, Petya will pick up the number $ x $ if there exist at least $ 7 $ permutations of numbers $ p_{1},p_{2},p_{3},p_{4} $ , for which $ f(x)=x $ .

## 输入格式

First line of the input will contain 6 integers, separated by spaces: $ p_{1},p_{2},p_{3},p_{4},a,b $ ( $ 1<=p_{1},p_{2},p_{3},p_{4}<=1000,0<=a<=b<=31415 $ ).

It is guaranteed that numbers $ p_{1},p_{2},p_{3},p_{4} $ will be pairwise distinct.

## 输出格式

Output the number of integers in the given range that have the given property.

## 样例 #1

### 输入

```
2 7 1 8 2 8

```

### 输出

```
0

```

## 样例 #2

### 输入

```
20 30 40 50 0 100

```

### 输出

```
20

```

## 样例 #3

### 输入

```
31 41 59 26 17 43

```

### 输出

```
9

```



---

---
title: "Triangle"
layout: "post"
diff: 入门
pid: CF6A
tag: ['枚举', '排序', '深度优先搜索 DFS', '排列组合']
---

# Triangle

## 题目描述

给定 $4$ 根木棍的长度，如果它们中存在 $3$ 根木棍可以组成三角形，输出 ```TRIANGLE``` ;如果它们无法组成三角形，但是它们中存在 $3$ 根木棍可以组成退化的三角形(任意两边之和大于等于第三边，但是不是三角形)，输出 ```SEGMENT``` ;否则，输出 ```IMPOSSIBLE``` 。

注意: 木棍不能折断，也不能只用一部分长度。

## 输入格式

一行 $4$ 个整数，$4$ 根木棍的长度。

## 输出格式

如果它们中存在 $3$ 根木棍可以组成三角形，输出 ```TRIANGLE``` ;如果它们无法组成三角形，但是它们中存在3根木棍可以组成退化的三角形，输出 ```SEGMENT``` ;否则，输出 ```IMPOSSIBLE```。

By @PC_DOS

## 样例 #1

### 输入

```
4 2 1 3

```

### 输出

```
TRIANGLE

```

## 样例 #2

### 输入

```
7 2 2 4

```

### 输出

```
SEGMENT

```

## 样例 #3

### 输入

```
3 5 9 1

```

### 输出

```
IMPOSSIBLE

```



---

---
title: "Display Size"
layout: "post"
diff: 入门
pid: CF747A
tag: ['数学', '枚举']
---

# Display Size

## 题目描述

A big company decided to launch a new series of rectangular displays, and decided that the display must have exactly $ n $ pixels.

Your task is to determine the size of the rectangular display — the number of lines (rows) of pixels $ a $ and the number of columns of pixels $ b $ , so that:

- there are exactly $ n $ pixels on the display;
- the number of rows does not exceed the number of columns, it means $ a<=b $ ;
- the difference $ b-a $ is as small as possible.

## 输入格式

The first line contains the positive integer $ n $ ( $ 1<=n<=10^{6} $ ) — the number of pixels display should have.

## 输出格式

Print two integers — the number of rows and columns on the display.

## 说明/提示

In the first example the minimum possible difference equals 2, so on the display should be 2 rows of 4 pixels.

In the second example the minimum possible difference equals 0, so on the display should be 8 rows of 8 pixels.

In the third example the minimum possible difference equals 4, so on the display should be 1 row of 5 pixels.

## 样例 #1

### 输入

```
8

```

### 输出

```
2 4

```

## 样例 #2

### 输入

```
64

```

### 输出

```
8 8

```

## 样例 #3

### 输入

```
5

```

### 输出

```
1 5

```

## 样例 #4

### 输入

```
999999

```

### 输出

```
999 1001

```



---

---
title: "Holiday Of Equality"
layout: "post"
diff: 入门
pid: CF758A
tag: ['模拟', '枚举', '排序']
---

# Holiday Of Equality

## 题目描述

## 题目大意
今天是Berland的平等节。为了庆祝节日，国王决定用国库里的钱来使Berland所有公民的福利均等。

在Berland，有$N$个公民，每个人的福利都被估计为一个整数$a_{i}$ burle（burle是Berland的货币）。

你是皇家财政管理员，你需要计算国王为此要付出的最低费用。国王只能给公民们钱，他没有权力夺走任何钱财。

## 输入格式

输入数据的第一行有一个整数$n$，表示Berland中公民的数量。

数据的第二行包括$n$个整数$a_{1},a_{2},...,a_{n}$，表示每个公民原有的福利。

## 输出格式

输出仅包括一个整数$S$，表示国王最少需要花费$S$ burle。

## 输入输出样例

略

## 说明/提示

第一个样例中，如果我们给第一个公民4 burles，第二个3 burles，第三个2 burles，第四个1 burle，那么所有公民的福利都等于4 burles。

第二个样例中，我们只需要给第三个公民1 burle就可以使得福利均等。

第三个样例中，我们需要分别给第一个和第三个公民2 burles，使得福利都等于3 burles。

第四个样例中，我们不需要给任何人钱因为所有人的福利都是12 burles。


对于100%的数据，$1 \leq n \leq 100$，$0 \leq a_{i} \leq 10^{6}$。

翻译提供者：Simpson561

## 样例 #1

### 输入

```
5
0 1 2 3 4

```

### 输出

```
10
```

## 样例 #2

### 输入

```
5
1 1 0 1 1

```

### 输出

```
1
```

## 样例 #3

### 输入

```
3
1 3 1

```

### 输出

```
4
```

## 样例 #4

### 输入

```
1
12

```

### 输出

```
0
```



---

---
title: "Bear and Big Brother"
layout: "post"
diff: 入门
pid: CF791A
tag: ['模拟', '枚举']
---

# Bear and Big Brother

## 题目描述

**题意翻译**

给定两个数 $a, b$，每个单位时间中，$a \leftarrow a \times 3,b\leftarrow b\times 2$，求在第多少个单位时间时，$a>b$。

## 输入格式

共一行，为两个正整数 $a,b$，详见题面。

## 输出格式

共一行，为在第多少个单位时间时，$a>b$。

## 说明/提示

对于 $100\%$ 的数据，$1\le a,b\le 10$。

**样例一解释**

第一个单位时间后，$a=4\times 3=12,b=7\times 2=14,a<b$；

第二个单位时间后，$a=12\times 3=36,b=14\times 2=28,a>b$，此时，已满足题目要求，输出 $2$。

**样例二解释**

第一个单位时间后，$a=4\times 3=12,b=9\times 2=18, a<b$；

第二个单位时间后，$a=12\times 3=36,b=18\times 2=36,a=b$；

第三个单位时间后，$a=36\times 3=108,b=36\times 2=72,a<b$，此时，已满足题目要求，输出 $3$。

**样例三解释**

第一个单位时间后，$a=1\times3=3,b=1\times2=2,a<b$，此时，已满足题目要求，输出 $1$。

Translate By @[159号程序员](https://www.luogu.com.cn/user/334586)

## 样例 #1

### 输入

```
4 7

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4 9

```

### 输出

```
3

```

## 样例 #3

### 输入

```
1 1

```

### 输出

```
1

```



---

---
title: "Fake News (easy)"
layout: "post"
diff: 入门
pid: CF802G
tag: ['模拟', '字符串', '枚举', '队列']
---

# Fake News (easy)

## 题目描述

As it's the first of April, Heidi is suspecting that the news she reads today are fake, and she does not want to look silly in front of all the contestants. She knows that a newspiece is fake if it contains heidi as a subsequence. Help Heidi assess whether the given piece is true, but please be discreet about it...

## 输入格式

The first and only line of input contains a single nonempty string $ s $ of length at most $ 1000 $ composed of lowercase letters (a-z).

## 输出格式

Output YES if the string $ s $ contains heidi as a subsequence and NO otherwise.

## 说明/提示

A string $ s $ contains another string $ p $ as a subsequence if it is possible to delete some characters from $ s $ and obtain $ p $ .

## 样例 #1

### 输入

```
abcheaibcdi

```

### 输出

```
YES
```

## 样例 #2

### 输入

```
hiedi

```

### 输出

```
NO
```



---

---
title: "Bark to Unlock"
layout: "post"
diff: 入门
pid: CF868A
tag: ['模拟', '字符串', '枚举']
---

# Bark to Unlock

## 题目描述

As technologies develop, manufacturers are making the process of unlocking a phone as user-friendly as possible. To unlock its new phone, Arkady's pet dog Mu-mu has to bark the password once. The phone represents a password as a string of two lowercase English letters.

Mu-mu's enemy Kashtanka wants to unlock Mu-mu's phone to steal some sensible information, but it can only bark $ n $ distinct words, each of which can be represented as a string of two lowercase English letters. Kashtanka wants to bark several words (not necessarily distinct) one after another to pronounce a string containing the password as a substring. Tell if it's possible to unlock the phone in this way, or not.

## 输入格式

The first line contains two lowercase English letters — the password on the phone.

The second line contains single integer $ n $ ( $ 1<=n<=100 $ ) — the number of words Kashtanka knows.

The next $ n $ lines contain two lowercase English letters each, representing the words Kashtanka knows. The words are guaranteed to be distinct.

## 输出格式

Print "YES" if Kashtanka can bark several words in a line forming a string containing the password, and "NO" otherwise.

You can print each letter in arbitrary case (upper or lower).

## 说明/提示

In the first example the password is "ya", and Kashtanka can bark "oy" and then "ah", and then "ha" to form the string "oyahha" which contains the password. So, the answer is "YES".

In the second example Kashtanka can't produce a string containing password as a substring. Note that it can bark "ht" and then "tp" producing "http", but it doesn't contain the password "hp" as a substring.

In the third example the string "hahahaha" contains "ah" as a substring.

## 样例 #1

### 输入

```
ya
4
ah
oy
to
ha

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
hp
2
ht
tp

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
ah
1
ha

```

### 输出

```
YES

```



---

---
title: "The Artful Expedient"
layout: "post"
diff: 入门
pid: CF869A
tag: ['模拟', '搜索', '枚举']
---

# The Artful Expedient

## 题目描述

首先定义一个整形变量n,Koyomi和Karen都会分别选择n个不同的正整数,分别表示为X1,X2,...Xn和Y1,Y2,...Yn。它们不断重复显示它们的序列,并一直重复直到所有2n个整数变得不同,此时,这是唯一被保留和考虑的最终状态。
他们需要计算满足有序数对(i,j)[1<=i,j<=n]中(Xi ^ Yi)的值等于2n个整数之中任意一个整数的值的有序数对的数量。这里'^'意味着对两个整数的按位异或操作,并且在大多数编程语言中用'^','/'或'xor'表示

如果这样的配对数量是偶数时,Karen就可以取得胜利,否则Koyomi胜利。你需要帮助他们决出最近一场比赛的获胜者。

## 输入格式

输入的第一行包含一个正整数n(1<=N<=2000)表示两个序列的长度。

第二行包含n个用空格分开的正整数X1,X2,...Xn(1<=Xi<=2*1e6)表示最后由Koyomi选择的正整数

第三行包含n个用空格分开的正整数Y1,Y2,...Yn(1<=Yi<=2*1e6)表示最后由Karen选择的正整数

输入数据保证给定的2n个正整数是两两不同的,也就是说,没有一对(i,j)[1<=i,j<=n]满足以下任意一项条件:
1.Xi=Yi
2.i≠j & Xi=Xj
3.i≠j & Yi=Yj

## 输出格式

输出一行表示获胜者的名字,即“Koyomi”或“Karen”(不含引号),注意大小写

样例解释
在样例1中,有6对满足条件的有序数对：(1,1),(1,2),(2,1),(2,3),(3,2),(3,3),因为6是偶数,所以Karen取得胜利
在样例2中,有16对满足条件的有序数对,所以Karen再次取得了比赛的胜利

Translated by @matthew

## 样例 #1

### 输入

```
3
1 2 3
4 5 6

```

### 输出

```
Karen

```

## 样例 #2

### 输入

```
5
2 4 6 8 10
9 7 5 3 1

```

### 输出

```
Karen

```



---

---
title: "QAQ"
layout: "post"
diff: 入门
pid: CF894A
tag: ['字符串', '递归', '枚举']
---

# QAQ

## 题目描述

"QAQ" is a word to denote an expression of crying. Imagine "Q" as eyes with tears and "A" as a mouth.

Now Diamond has given Bort a string consisting of only uppercase English letters of length $ n $ . There is a great number of "QAQ" in the string (Diamond is so cute!).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF894A/333c4dadce3b03c143ff500b3cc7457c4f2b76a3.png)illustration by 猫屋 https://twitter.com/nekoyaliuBort wants to know how many subsequences "QAQ" are in the string Diamond has given. Note that the letters "QAQ" don't have to be consecutive, but the order of letters should be exact.

## 输入格式

The only line contains a string of length $ n $ ( $ 1<=n<=100 $ ). It's guaranteed that the string only contains uppercase English letters.

## 输出格式

Print a single integer — the number of subsequences "QAQ" in the string.

## 说明/提示

In the first example there are $ 4 $ subsequences "QAQ": "QAQAQYSYIOIWIN", "QAQAQYSYIOIWIN", "QAQAQYSYIOIWIN", "QAQAQYSYIOIWIN".

## 样例 #1

### 输入

```
QAQAQYSYIOIWIN

```

### 输出

```
4

```

## 样例 #2

### 输入

```
QAQQQZZYNOIWIN

```

### 输出

```
3

```



---

---
title: "Rounding"
layout: "post"
diff: 入门
pid: CF898A
tag: ['模拟', '字符串', '枚举']
---

# Rounding

## 题目描述

Vasya has a non-negative integer $ n $ . He wants to round it to nearest integer, which ends up with $ 0 $ . If $ n $ already ends up with $ 0 $ , Vasya considers it already rounded.

For example, if $ n=4722 $ answer is $ 4720 $ . If $ n=5 $ Vasya can round it to $ 0 $ or to $ 10 $ . Both ways are correct.

For given $ n $ find out to which integer will Vasya round it.

## 输入格式

The first line contains single integer $ n $ ( $ 0<=n<=10^{9} $ ) — number that Vasya has.

## 输出格式

Print result of rounding $ n $ . Pay attention that in some cases answer isn't unique. In that case print any correct answer.

## 说明/提示

In the first example $ n=5 $ . Nearest integers, that ends up with zero are $ 0 $ and $ 10 $ . Any of these answers is correct, so you can print $ 0 $ or $ 10 $ .

## 样例 #1

### 输入

```
5

```

### 输出

```
0

```

## 样例 #2

### 输入

```
113

```

### 输出

```
110

```

## 样例 #3

### 输入

```
1000000000

```

### 输出

```
1000000000

```

## 样例 #4

### 输入

```
5432359

```

### 输出

```
5432360

```



---

---
title: "Proper Nutrition"
layout: "post"
diff: 入门
pid: CF898B
tag: ['枚举']
---

# Proper Nutrition

## 题目描述

Vasya has $ n $ burles. One bottle of Ber-Cola costs $ a $ burles and one Bars bar costs $ b $ burles. He can buy any non-negative integer number of bottles of Ber-Cola and any non-negative integer number of Bars bars.

Find out if it's possible to buy some amount of bottles of Ber-Cola and Bars bars and spend exactly $ n $ burles.

In other words, you should find two non-negative integers $ x $ and $ y $ such that Vasya can buy $ x $ bottles of Ber-Cola and $ y $ Bars bars and $ x·a+y·b=n $ or tell that it's impossible.

## 输入格式

First line contains single integer $ n $ ( $ 1<=n<=10000000 $ ) — amount of money, that Vasya has.

Second line contains single integer $ a $ ( $ 1<=a<=10000000 $ ) — cost of one bottle of Ber-Cola.

Third line contains single integer $ b $ ( $ 1<=b<=10000000 $ ) — cost of one Bars bar.

## 输出格式

If Vasya can't buy Bars and Ber-Cola in such a way to spend exactly $ n $ burles print «NO» (without quotes).

Otherwise in first line print «YES» (without quotes). In second line print two non-negative integers $ x $ and $ y $ — number of bottles of Ber-Cola and number of Bars bars Vasya should buy in order to spend exactly $ n $ burles, i.e. $ x·a+y·b=n $ . If there are multiple answers print any of them.

Any of numbers $ x $ and $ y $ can be equal $ 0 $ .

## 说明/提示

In first example Vasya can buy two bottles of Ber-Cola and one Bars bar. He will spend exactly $ 2·2+1·3=7 $ burles.

In second example Vasya can spend exactly $ n $ burles multiple ways:

- buy two bottles of Ber-Cola and five Bars bars;
- buy four bottles of Ber-Cola and don't buy Bars bars;
- don't buy Ber-Cola and buy $ 10 $ Bars bars.

In third example it's impossible to but Ber-Cola and Bars bars in order to spend exactly $ n $ burles.

## 样例 #1

### 输入

```
7
2
3

```

### 输出

```
YES
2 1

```

## 样例 #2

### 输入

```
100
25
10

```

### 输出

```
YES
0 10

```

## 样例 #3

### 输入

```
15
4
8

```

### 输出

```
NO

```

## 样例 #4

### 输入

```
9960594
2551
2557

```

### 输出

```
YES
1951 1949

```



---

---
title: "Hungry Student Problem"
layout: "post"
diff: 入门
pid: CF903A
tag: ['模拟', '枚举']
---

# Hungry Student Problem

## 题目描述

Ivan's classes at the university have just finished, and now he wants to go to the local CFK cafe and eat some fried chicken.

CFK sells chicken chunks in small and large portions. A small portion contains $ 3 $ chunks; a large one — $ 7 $ chunks. Ivan wants to eat exactly $ x $ chunks. Now he wonders whether he can buy exactly this amount of chicken.

Formally, Ivan wants to know if he can choose two non-negative integers $ a $ and $ b $ in such a way that $ a $ small portions and $ b $ large ones contain exactly $ x $ chunks.

Help Ivan to answer this question for several values of $ x $ !

## 输入格式

The first line contains one integer $ n $ ( $ 1<=n<=100 $ ) — the number of testcases.

The $ i $ -th of the following $ n $ lines contains one integer $ x_{i} $ ( $ 1<=x_{i}<=100 $ ) — the number of chicken chunks Ivan wants to eat.

## 输出格式

Print $ n $ lines, in $ i $ -th line output YES if Ivan can buy exactly $ x_{i} $ chunks. Otherwise, print NO.

## 说明/提示

In the first example Ivan can buy two small portions.

In the second example Ivan cannot buy exactly $ 5 $ chunks, since one small portion is not enough, but two small portions or one large is too much.

## 样例 #1

### 输入

```
2
6
5

```

### 输出

```
YES
NO

```



---

---
title: "Generate Login"
layout: "post"
diff: 入门
pid: CF909A
tag: ['字符串', '搜索', '贪心', '枚举']
---

# Generate Login

## 题目描述

The preferred way to generate user login in Polygon is to concatenate a prefix of the user's first name and a prefix of their last name, in that order. Each prefix must be non-empty, and any of the prefixes can be the full name. Typically there are multiple possible logins for each person.

You are given the first and the last name of a user. Return the alphabetically earliest login they can get (regardless of other potential Polygon users).

As a reminder, a prefix of a string $ s $ is its substring which occurs at the beginning of $ s $ : "a", "ab", "abc" etc. are prefixes of string "{abcdef}" but "b" and 'bc" are not. A string $ a $ is alphabetically earlier than a string $ b $ , if $ a $ is a prefix of $ b $ , or $ a $ and $ b $ coincide up to some position, and then $ a $ has a letter that is alphabetically earlier than the corresponding letter in $ b $ : "a" and "ab" are alphabetically earlier than "ac" but "b" and "ba" are alphabetically later than "ac".

## 输入格式

The input consists of a single line containing two space-separated strings: the first and the last names. Each character of each string is a lowercase English letter. The length of each string is between 1 and 10, inclusive.

## 输出格式

Output a single string — alphabetically earliest possible login formed from these names. The output should be given in lowercase as well.

## 样例 #1

### 输入

```
harry potter

```

### 输出

```
hap

```

## 样例 #2

### 输入

```
tom riddle

```

### 输出

```
tomr

```



---

---
title: "Perfect Squares"
layout: "post"
diff: 入门
pid: CF914A
tag: ['模拟', '枚举', '排序']
---

# Perfect Squares

## 题目描述

Given an array $ a_{1},a_{2},...,a_{n} $ of $ n $ integers, find the largest number in the array that is not a perfect square.

A number $ x $ is said to be a perfect square if there exists an integer $ y $ such that $ x=y^{2} $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=1000 $ ) — the number of elements in the array.

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ -10^{6}<=a_{i}<=10^{6} $ ) — the elements of the array.

It is guaranteed that at least one element of the array is not a perfect square.

## 输出格式

Print the largest number in the array which is not a perfect square. It is guaranteed that an answer always exists.

## 说明/提示

In the first sample case, $ 4 $ is a perfect square, so the largest number in the array that is not a perfect square is $ 2 $ .

## 样例 #1

### 输入

```
2
4 2

```

### 输出

```
2

```

## 样例 #2

### 输入

```
8
1 2 4 8 16 32 64 576

```

### 输出

```
32

```



---

---
title: "Garden"
layout: "post"
diff: 入门
pid: CF915A
tag: ['模拟', '枚举', '素数判断,质数,筛法']
---

# Garden

## 题目描述

Luba thinks about watering her garden. The garden can be represented as a segment of length $ k $ . Luba has got $ n $ buckets, the $ i $ -th bucket allows her to water some continuous subsegment of garden of length exactly $ a_{i} $ each hour. Luba can't water any parts of the garden that were already watered, also she can't water the ground outside the garden.

Luba has to choose one of the buckets in order to water the garden as fast as possible (as mentioned above, each hour she will water some continuous subsegment of length $ a_{i} $ if she chooses the $ i $ -th bucket). Help her to determine the minimum number of hours she has to spend watering the garden. It is guaranteed that Luba can always choose a bucket so it is possible water the garden.

See the examples for better understanding.

## 输入格式

The first line of input contains two integer numbers $ n $ and $ k $ ( $ 1<=n,k<=100 $ ) — the number of buckets and the length of the garden, respectively.

The second line of input contains $ n $ integer numbers $ a_{i} $ ( $ 1<=a_{i}<=100 $ ) — the length of the segment that can be watered by the $ i $ -th bucket in one hour.

It is guaranteed that there is at least one bucket such that it is possible to water the garden in integer number of hours using only this bucket.

## 输出格式

Print one integer number — the minimum number of hours required to water the garden.

## 说明/提示

In the first test the best option is to choose the bucket that allows to water the segment of length $ 3 $ . We can't choose the bucket that allows to water the segment of length $ 5 $ because then we can't water the whole garden.

In the second test we can choose only the bucket that allows us to water the segment of length $ 1 $ .

## 样例 #1

### 输入

```
3 6
2 3 5

```

### 输出

```
2

```

## 样例 #2

### 输入

```
6 7
1 2 3 4 5 6

```

### 输出

```
7

```



---

---
title: "Fafa and his Company"
layout: "post"
diff: 入门
pid: CF935A
tag: ['数学', '枚举', '概率论']
---

# Fafa and his Company

## 题目描述

Fafa owns a company that works on huge projects. There are $ n $ employees in Fafa's company. Whenever the company has a new project to start working on, Fafa has to divide the tasks of this project among all the employees.

Fafa finds doing this every time is very tiring for him. So, he decided to choose the best $ l $ employees in his company as team leaders. Whenever there is a new project, Fafa will divide the tasks among only the team leaders and each team leader will be responsible of some positive number of employees to give them the tasks. To make this process fair for the team leaders, each one of them should be responsible for the same number of employees. Moreover, every employee, who is not a team leader, has to be under the responsibility of exactly one team leader, and no team leader is responsible for another team leader.

Given the number of employees $ n $ , find in how many ways Fafa could choose the number of team leaders $ l $ in such a way that it is possible to divide employees between them evenly.

## 输入格式

The input consists of a single line containing a positive integer $ n $ ( $ 2<=n<=10^{5} $ ) — the number of employees in Fafa's company.

## 输出格式

Print a single integer representing the answer to the problem.

## 说明/提示

In the second sample Fafa has 3 ways:

- choose only $ 1 $ employee as a team leader with $ 9 $ employees under his responsibility.
- choose $ 2 $ employees as team leaders with $ 4 $ employees under the responsibility of each of them.
- choose $ 5 $ employees as team leaders with $ 1 $ employee under the responsibility of each of them.

## 样例 #1

### 输入

```
2

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
3

```



---

---
title: "Hamster Farm"
layout: "post"
diff: 入门
pid: CF939B
tag: ['模拟', '枚举']
---

# Hamster Farm

## 题目描述

Dima有$n$ 只仓鼠，有$k$ 种盒子，每种盒子编号为1~k，可以装$a_i$ 只仓鼠，所有盒子都要装满仓鼠，剩下的仓鼠不装，Dima想让剩下的仓鼠最少，求应选盒子和盒子总数，如果有多种情况，输出任意一种。

## 输出格式

感谢 @WDLGZH2017  提供的翻译。

## 样例 #1

### 输入

```
19 3
5 4 10

```

### 输出

```
2 4

```

## 样例 #2

### 输入

```
28 3
5 6 30

```

### 输出

```
1 5

```



---

---
title: "Mind the Gap"
layout: "post"
diff: 入门
pid: CF967A
tag: ['枚举', '概率论']
---

# Mind the Gap

## 题目描述

最近 Arkady 在一个大型机场当空中交通管理员.他管理着一条用于飞机降 落的跑道。因此，他的手中有一份当天的飞机降落时刻表。每架飞机需要一分钟 来降落。（即：从给定的时间持续一分钟）

现在有一架飞机要插队。这架飞机也需要一分钟来降落，但是为了安全，它 的降落前后应该有一段时间的空缺，前后各 s 分钟。

请你找到最早的可以安排插队的时间。

## 输入格式

第一行输入两个整数 n 和 s。（1<=n<=100,1<=s<=60)。    注：n架飞机；

	接下来的n行  即为每架飞机降落的时间，以h m形式给出（0<=h<=23,0<=m<=59)。(小时，分钟）

## 输出格式

最早的时间，同样以h m形式输出；
注：
如果在第一架飞机之前就可以加入，输出0 0；
如果只能在最后加入，h可以大于24；

感谢@shzr 提供的翻译

## 样例 #1

### 输入

```
6 60
0 0
1 20
3 21
5 0
19 30
23 40

```

### 输出

```
6 1

```

## 样例 #2

### 输入

```
16 50
0 30
1 20
3 0
4 30
6 10
7 50
9 30
11 10
12 50
14 30
16 10
17 50
19 30
21 10
22 50
23 59

```

### 输出

```
24 50

```

## 样例 #3

### 输入

```
3 17
0 30
1 0
12 0

```

### 输出

```
0 0

```



---

---
title: "Antipalindrome"
layout: "post"
diff: 入门
pid: CF981A
tag: ['字符串', '枚举']
---

# Antipalindrome

## 题目描述

A string is a palindrome if it reads the same from the left to the right and from the right to the left. For example, the strings "kek", "abacaba", "r" and "papicipap" are palindromes, while the strings "abb" and "iq" are not.

A substring $ s[l \ldots r] $ ( $ 1 \leq l \leq r \leq |s| $ ) of a string $ s = s_{1}s_{2} \ldots s_{|s|} $ is the string $ s_{l}s_{l + 1} \ldots s_{r} $ .

Anna does not like palindromes, so she makes her friends call her Ann. She also changes all the words she reads in a similar way. Namely, each word $ s $ is changed into its longest substring that is not a palindrome. If all the substrings of $ s $ are palindromes, she skips the word at all.

Some time ago Ann read the word $ s $ . What is the word she changed it into?

## 输入格式

The first line contains a non-empty string $ s $ with length at most $ 50 $ characters, containing lowercase English letters only.

## 输出格式

If there is such a substring in $ s $ that is not a palindrome, print the maximum length of such a substring. Otherwise print $ 0 $ .

Note that there can be multiple longest substrings that are not palindromes, but their length is unique.

## 说明/提示

"mew" is not a palindrome, so the longest substring of it that is not a palindrome, is the string "mew" itself. Thus, the answer for the first example is $ 3 $ .

The string "uffuw" is one of the longest non-palindrome substrings (of length $ 5 $ ) of the string "wuffuw", so the answer for the second example is $ 5 $ .

All substrings of the string "qqqqqqqq" consist of equal characters so they are palindromes. This way, there are no non-palindrome substrings. Thus, the answer for the third example is $ 0 $ .

## 样例 #1

### 输入

```
mew

```

### 输出

```
3

```

## 样例 #2

### 输入

```
wuffuw

```

### 输出

```
5

```

## 样例 #3

### 输入

```
qqqqqqqq

```

### 输出

```
0

```



---

