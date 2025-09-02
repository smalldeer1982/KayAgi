---
title: "Tanya and Stairways"
layout: "post"
diff: 入门
pid: CF1005A
tag: ['模拟', '概率论']
---

# Tanya and Stairways

## 题目描述

给你N个数（1≤N≤1000），这N个数是由M个从1开始的连续自然序列组成的

## 输入格式

第一行，一个数：N

第二行N个数，分别是组成M个序列的元素

## 输出格式

第一行，一个数：M

第二行，M个数，分别是这M个序列的长度

## 样例 #1

### 输入

```
7
1 2 3 1 2 3 4

```

### 输出

```
2
3 4 
```

## 样例 #2

### 输入

```
4
1 1 1 1

```

### 输出

```
4
1 1 1 1 
```

## 样例 #3

### 输入

```
5
1 2 3 4 5

```

### 输出

```
1
5 
```

## 样例 #4

### 输入

```
5
1 2 1 2 1

```

### 输出

```
3
2 2 1 
```



---

---
title: "Game Shopping"
layout: "post"
diff: 入门
pid: CF1009A
tag: ['模拟']
---

# Game Shopping

## 题目描述

Maxim wants to buy some games at the local game shop. There are $ n $ games in the shop, the $ i $ -th game costs $ c_i $ .

Maxim has a wallet which can be represented as an array of integers. His wallet contains $ m $ bills, the $ j $ -th bill has value $ a_j $ .

Games in the shop are ordered from left to right, Maxim tries to buy every game in that order.

When Maxim stands at the position $ i $ in the shop, he takes the first bill from his wallet (if his wallet is empty then he proceeds to the next position immediately) and tries to buy the $ i $ -th game using this bill. After Maxim tried to buy the $ n $ -th game, he leaves the shop.

Maxim buys the $ i $ -th game if and only if the value of the first bill (which he takes) from his wallet is greater or equal to the cost of the $ i $ -th game. If he successfully buys the $ i $ -th game, the first bill from his wallet disappears and the next bill becomes first. Otherwise Maxim leaves the first bill in his wallet (this bill still remains the first one) and proceeds to the next game.

For example, for array $ c = [2, 4, 5, 2, 4] $ and array $ a = [5, 3, 4, 6] $ the following process takes place: Maxim buys the first game using the first bill (its value is $ 5 $ ), the bill disappears, after that the second bill (with value $ 3 $ ) becomes the first one in Maxim's wallet, then Maxim doesn't buy the second game because $ c_2 > a_2 $ , the same with the third game, then he buys the fourth game using the bill of value $ a_2 $ (the third bill becomes the first one in Maxim's wallet) and buys the fifth game using the bill of value $ a_3 $ .

Your task is to get the number of games Maxim will buy.

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 1000 $ ) — the number of games and the number of bills in Maxim's wallet.

The second line of the input contains $ n $ integers $ c_1, c_2, \dots, c_n $ ( $ 1 \le c_i \le 1000 $ ), where $ c_i $ is the cost of the $ i $ -th game.

The third line of the input contains $ m $ integers $ a_1, a_2, \dots, a_m $ ( $ 1 \le a_j \le 1000 $ ), where $ a_j $ is the value of the $ j $ -th bill from the Maxim's wallet.

## 输出格式

Print a single integer — the number of games Maxim will buy.

## 说明/提示

The first example is described in the problem statement.

In the second example Maxim cannot buy any game because the value of the first bill in his wallet is smaller than the cost of any game in the shop.

In the third example the values of the bills in Maxim's wallet are large enough to buy any game he encounter until he runs out of bills in his wallet.

## 样例 #1

### 输入

```
5 4
2 4 5 2 4
5 3 4 6

```

### 输出

```
3

```

## 样例 #2

### 输入

```
5 2
20 40 50 20 40
19 20

```

### 输出

```
0

```

## 样例 #3

### 输入

```
6 4
4 8 15 16 23 42
1000 1000 1000 1000

```

### 输出

```
4

```



---

---
title: "Testing Pants for Sadness"
layout: "post"
diff: 入门
pid: CF103A
tag: ['模拟', '递推', '线性递推']
---

# Testing Pants for Sadness

## 题目描述

The average miner Vaganych took refresher courses. As soon as a miner completes the courses, he should take exams. The hardest one is a computer test called "Testing Pants for Sadness".

The test consists of $ n $ questions; the questions are to be answered strictly in the order in which they are given, from question $ 1 $ to question $ n $ . Question $ i $ contains $ a_{i} $ answer variants, exactly one of them is correct.

A click is regarded as selecting any answer in any question. The goal is to select the correct answer for each of the $ n $ questions. If Vaganych selects a wrong answer for some question, then all selected answers become unselected and the test starts from the very beginning, from question $ 1 $ again. But Vaganych remembers everything. The order of answers for each question and the order of questions remain unchanged, as well as the question and answers themselves.

Vaganych is very smart and his memory is superb, yet he is unbelievably unlucky and knows nothing whatsoever about the test's theme. How many clicks will he have to perform in the worst case?

## 输入格式

The first line contains a positive integer $ n $ ( $ 1<=n<=100 $ ). It is the number of questions in the test. The second line contains space-separated $ n $ positive integers $ a_{i} $ ( $ 1<=a_{i}<=10^{9} $ ), the number of answer variants to question $ i $ .

## 输出格式

Print a single number — the minimal number of clicks needed to pass the test it the worst-case scenario.

Please do not use the %lld specificator to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specificator.

## 说明/提示

Note to the second sample. In the worst-case scenario you will need five clicks:

- the first click selects the first variant to the first question, this answer turns out to be wrong.
- the second click selects the second variant to the first question, it proves correct and we move on to the second question;
- the third click selects the first variant to the second question, it is wrong and we go back to question 1;
- the fourth click selects the second variant to the first question, it proves as correct as it was and we move on to the second question;
- the fifth click selects the second variant to the second question, it proves correct, the test is finished.

## 样例 #1

### 输入

```
2
1 1

```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
2 2

```

### 输出

```
5
```

## 样例 #3

### 输入

```
1
10

```

### 输出

```
10
```



---

---
title: "The King's Race"
layout: "post"
diff: 入门
pid: CF1075A
tag: ['模拟']
---

# The King's Race

## 题目描述

On a chessboard with a width of $ n $ and a height of $ n $ , rows are numbered from bottom to top from $ 1 $ to $ n $ , columns are numbered from left to right from $ 1 $ to $ n $ . Therefore, for each cell of the chessboard, you can assign the coordinates $ (r,c) $ , where $ r $ is the number of the row, and $ c $ is the number of the column.

The white king has been sitting in a cell with $ (1,1) $ coordinates for a thousand years, while the black king has been sitting in a cell with $ (n,n) $ coordinates. They would have sat like that further, but suddenly a beautiful coin fell on the cell with coordinates $ (x,y) $ ...

Each of the monarchs wanted to get it, so they decided to arrange a race according to slightly changed chess rules:

As in chess, the white king makes the first move, the black king makes the second one, the white king makes the third one, and so on. However, in this problem, kings can stand in adjacent cells or even in the same cell at the same time.

The player who reaches the coin first will win, that is to say, the player who reaches the cell with the coordinates $ (x,y) $ first will win.

Let's recall that the king is such a chess piece that can move one cell in all directions, that is, if the king is in the $ (a,b) $ cell, then in one move he can move from $ (a,b) $ to the cells $ (a + 1,b) $ , $ (a - 1,b) $ , $ (a,b + 1) $ , $ (a,b - 1) $ , $ (a + 1,b - 1) $ , $ (a + 1,b + 1) $ , $ (a - 1,b - 1) $ , or $ (a - 1,b + 1) $ . Going outside of the field is prohibited.

Determine the color of the king, who will reach the cell with the coordinates $ (x,y) $ first, if the white king moves first.

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 10^{18} $ ) — the length of the side of the chess field.

The second line contains two integers $ x $ and $ y $ ( $ 1 \le x,y \le n $ ) — coordinates of the cell, where the coin fell.

## 输出格式

In a single line print the answer "White" (without quotes), if the white king will win, or "Black" (without quotes), if the black king will win.

You can print each letter in any case (upper or lower).

## 说明/提示

An example of the race from the first sample where both the white king and the black king move optimally:

1. The white king moves from the cell $ (1,1) $ into the cell $ (2,2) $ .
2. The black king moves form the cell $ (4,4) $ into the cell $ (3,3) $ .
3. The white king moves from the cell $ (2,2) $ into the cell $ (2,3) $ . This is cell containing the coin, so the white king wins.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1075A/f254caab5d6689c7762373bad40ea730253add20.png)An example of the race from the second sample where both the white king and the black king move optimally:

1. The white king moves from the cell $ (1,1) $ into the cell $ (2,2) $ .
2. The black king moves form the cell $ (5,5) $ into the cell $ (4,4) $ .
3. The white king moves from the cell $ (2,2) $ into the cell $ (3,3) $ .
4. The black king moves from the cell $ (4,4) $ into the cell $ (3,5) $ . This is the cell, where the coin fell, so the black king wins.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1075A/8da824ef69161fea610dd68f5d79c6e1d4915d1c.png)In the third example, the coin fell in the starting cell of the black king, so the black king immediately wins.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1075A/ef64633e6cdf332ba74f49b9036ceea6af7c9df5.png)

## 样例 #1

### 输入

```
4
2 3

```

### 输出

```
White
```

## 样例 #2

### 输入

```
5
3 5

```

### 输出

```
Black
```

## 样例 #3

### 输入

```
2
2 2

```

### 输出

```
Black
```



---

---
title: "Power Consumption Calculation"
layout: "post"
diff: 入门
pid: CF10A
tag: ['模拟', '排序', '概率论']
---

# Power Consumption Calculation

## 题目描述

Tom is interested in power consumption of his favourite laptop. His laptop has three modes. In normal mode laptop consumes $ P_{1} $ watt per minute. $ T_{1} $ minutes after Tom moved the mouse or touched the keyboard for the last time, a screensaver starts and power consumption changes to $ P_{2} $ watt per minute. Finally, after $ T_{2} $ minutes from the start of the screensaver, laptop switches to the "sleep" mode and consumes $ P_{3} $ watt per minute. If Tom moves the mouse or touches the keyboard when the laptop is in the second or in the third mode, it switches to the first (normal) mode. Tom's work with the laptop can be divided into $ n $ time periods $ [l_{1},r_{1}],[l_{2},r_{2}],...,[l_{n},r_{n}] $ . During each interval Tom continuously moves the mouse and presses buttons on the keyboard. Between the periods Tom stays away from the laptop. Find out the total amount of power consumed by the laptop during the period $ [l_{1},r_{n}] $ .

## 输入格式

The first line contains 6 integer numbers $ n $ , $ P_{1} $ , $ P_{2} $ , $ P_{3} $ , $ T_{1} $ , $ T_{2} $ ( $ 1<=n<=100,0<=P_{1},P_{2},P_{3}<=100,1<=T_{1},T_{2}<=60 $ ). The following $ n $ lines contain description of Tom's work. Each $ i $ -th of these lines contains two space-separated integers $ l_{i} $ and $ r_{i} $ ( $ 0<=l_{i}<r_{i}<=1440 $ , $ r_{i}<l_{i+1} $ for $ i<n $ ), which stand for the start and the end of the $ i $ -th period of work.

## 输出格式

Output the answer to the problem.

## 样例 #1

### 输入

```
1 3 2 1 5 10
0 10

```

### 输出

```
30
```

## 样例 #2

### 输入

```
2 8 4 2 5 10
20 30
50 100

```

### 输出

```
570
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
title: "Epic Game"
layout: "post"
diff: 入门
pid: CF119A
tag: ['模拟', '最大公约数 gcd']
---

# Epic Game

## 题目描述

Simon和Antisimon在玩石子游戏。

共有n颗石子，Simon先拿。

Simon能拿当前n和a的最大公约数，Antisimon能拿当前n和b的最大公约数。

当有一个人不能拿时（n=0）那个人就输了。

求谁赢了。

## 输入格式

一行，a，b，n（1<=a,b,n<=100）

## 输出格式

一行，如果Simon赢了，输出0；Antisimon赢了，输出1.

## 说明/提示

gcd(0,x)=gcd(x,0)=x;

对于样例1：

Simon拿gcd(3,9)=3颗

Antisimon拿gcd(5,6)=1颗

Simon拿gcd(3,5)=1颗

Antisimon拿gcd(5,4)=1颗

Simon拿gcd(3,3)=3颗

Antisimon输了

感谢@引领天下 提供的翻译

## 样例 #1

### 输入

```
3 5 9

```

### 输出

```
0
```

## 样例 #2

### 输入

```
1 1 100

```

### 输出

```
1
```



---

---
title: "Increasing Sequence"
layout: "post"
diff: 入门
pid: CF11A
tag: ['模拟']
---

# Increasing Sequence

## 题目描述

### 题面描述

把数列中一个数加上 $d$ 算作一次操作，求最少几次操作能把这个数列变为递增数列。

## 输入格式

输入共 $2$ 行。

第一行 $2$ 个整数 $n$ 和 $d$，$n$ 表示数列中数的数量，$d$ 含义如题目所示。

第二行 $n$ 个整数，表示原始数列。

## 输出格式

一行一个整数 $m$，表示最少 $m$ 次操作能把这个数列变为递增数列。

## 样例 #1

### 输入

```
4 2
1 3 3 2

```

### 输出

```
3

```



---

---
title: "Maximum Square"
layout: "post"
diff: 入门
pid: CF1243A
tag: ['模拟']
---

# Maximum Square

## 题目描述

### 题意简述

给定 $n$ 个正整数 $a_1,a_2,···,a_n$。请你从中选取 $x$ 个正整数 $b_1,b_2,···,b_x$，使得其满足：

$$b_i\geq x(1\leq i \leq x)$$

您需要最大化 $x$。

## 输入格式

第一行一个正整数 $k(1\leq k \leq 10)$，表示数据的组数。

对于每组数据，第一行一个正整数 $n(1\leq n \leq 1000)$。

接下来一行 $n$ 个正整数 $a_1,a_2,···,a_n$。

## 输出格式

对于每组数据，输出 $x$。您需要最大化 $x$。

## 样例 #1

### 输入

```
4
5
4 3 1 4 5
4
4 4 4 4
3
1 1 1
5
5 5 1 1 5

```

### 输出

```
3
4
1
3

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
title: "Presents"
layout: "post"
diff: 入门
pid: CF136A
tag: ['模拟']
---

# Presents

## 题目描述

Little Petya very much likes gifts. Recently he has received a new laptop as a New Year gift from his mother. He immediately decided to give it to somebody else as what can be more pleasant than giving somebody gifts. And on this occasion he organized a New Year party at his place and invited $ n $ his friends there.

If there's one thing Petya likes more that receiving gifts, that's watching others giving gifts to somebody else. Thus, he safely hid the laptop until the next New Year and made up his mind to watch his friends exchanging gifts while he does not participate in the process. He numbered all his friends with integers from $ 1 $ to $ n $ . Petya remembered that a friend number $ i $ gave a gift to a friend number $ p_{i} $ . He also remembered that each of his friends received exactly one gift.

Now Petya wants to know for each friend $ i $ the number of a friend who has given him a gift.

## 输入格式

The first line contains one integer $ n $ ( $ 1<=n<=100 $ ) — the quantity of friends Petya invited to the party. The second line contains $ n $ space-separated integers: the $ i $ -th number is $ p_{i} $ — the number of a friend who gave a gift to friend number $ i $ . It is guaranteed that each friend received exactly one gift. It is possible that some friends do not share Petya's ideas of giving gifts to somebody else. Those friends gave the gifts to themselves.

## 输出格式

Print $ n $ space-separated integers: the $ i $ -th number should equal the number of the friend who gave a gift to friend number $ i $ .

## 样例 #1

### 输入

```
4
2 3 4 1

```

### 输出

```
4 1 2 3

```

## 样例 #2

### 输入

```
3
1 3 2

```

### 输出

```
1 3 2

```

## 样例 #3

### 输入

```
2
1 2

```

### 输出

```
1 2

```



---

---
title: "Letter"
layout: "post"
diff: 入门
pid: CF14A
tag: ['模拟', '字符串']
---

# Letter

## 题目描述

给定一 $N \times M$ 规模的矩阵，输出最小的包含所有 `*` 的矩阵。

## 输入格式

一行两个整数， $N$ 和 $M$ 。

然后一个 $N \times M$ 大小的矩阵。

## 输出格式

输出最小的包含所有 `*` 的矩阵。

## 说明/提示

$1 \leq N,M \leq 50$。

## 样例 #1

### 输入

```
6 7
.......
..***..
..*....
..***..
..*....
..***..

```

### 输出

```
***
*..
***
*..
***

```

## 样例 #2

### 输入

```
3 3
***
*.*
***

```

### 输出

```
***
*.*
***

```



---

---
title: "I_love_%username%"
layout: "post"
diff: 入门
pid: CF155A
tag: ['模拟', '排序', '概率论']
---

# I_love_%username%

## 题目描述

Vasya很喜欢一个coder，他喜欢看那个coder的节目，那个coder每次编程可以得到一个非负分数（不超过10000），而有两种情况能使Vasya惊讶：
·coder得到的分数完全大于过去的分数；
·coder得到的分数完全小于过去的分数。
注意：第一次得到的分数不会使人惊讶。
给定coder编程次数n，给定每次编程得到的分数，请你求出Vasya的惊讶次数。

~~看着题面上好像没有介绍输入输出和数据范围就来多嘴一句~~

## 输入格式

第一行包括一个整数n（1<=n<=1000），代表coder参加比赛时的编码数量；

第二行包括了n个用空格分开的整数，即coder每一个编码在比赛中的得分（得分均不超过10000）；

## 输出格式

输出一行，包括一个整数，代表整场比赛中Vasya被coder惊讶到的总次数；


由 @strike 提供翻译

## 样例 #1

### 输入

```
5
100 50 200 150 200

```

### 输出

```
2

```

## 样例 #2

### 输入

```
10
4664 6496 5814 7010 5762 5736 6944 4850 3698 7242

```

### 输出

```
4

```



---

---
title: "Dislike of Threes"
layout: "post"
diff: 入门
pid: CF1560A
tag: ['模拟']
---

# Dislike of Threes

## 题目描述

Polycarp doesn't like integers that are divisible by $ 3 $ or end with the digit $ 3 $ in their decimal representation. Integers that meet both conditions are disliked by Polycarp, too.

Polycarp starts to write out the positive (greater than $ 0 $ ) integers which he likes: $ 1, 2, 4, 5, 7, 8, 10, 11, 14, 16, \dots $ . Output the $ k $ -th element of this sequence (the elements are numbered from $ 1 $ ).

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases. Then $ t $ test cases follow.

Each test case consists of one line containing one integer $ k $ ( $ 1 \le k \le 1000 $ ).

## 输出格式

For each test case, output in a separate line one integer $ x $ — the $ k $ -th element of the sequence that was written out by Polycarp.

## 样例 #1

### 输入

```
10
1
2
3
4
5
6
7
8
9
1000
```

### 输出

```
1
2
4
5
7
8
10
11
14
1666
```



---

---
title: "Doors and Keys"
layout: "post"
diff: 入门
pid: CF1644A
tag: ['模拟', '字符串', '栈']
---

# Doors and Keys

## 题目描述

The knight is standing in front of a long and narrow hallway. A princess is waiting at the end of it.

In a hallway there are three doors: a red door, a green door and a blue door. The doors are placed one after another, however, possibly in a different order. To proceed to the next door, the knight must first open the door before.

Each door can be only opened with a key of the corresponding color. So three keys: a red key, a green key and a blue key — are also placed somewhere in the hallway. To open the door, the knight should first pick up the key of its color.

The knight has a map of the hallway. It can be transcribed as a string, consisting of six characters:

- R, G, B — denoting red, green and blue doors, respectively;
- r, g, b — denoting red, green and blue keys, respectively.

Each of these six characters appears in the string exactly once.

The knight is standing at the beginning of the hallway — on the left on the map.

Given a map of the hallway, determine if the knight can open all doors and meet the princess at the end of the hallway.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 720 $ ) — the number of testcases.

Each testcase consists of a single string. Each character is one of R, G, B (for the doors), r, g, b (for the keys), and each of them appears exactly once.

## 输出格式

For each testcase, print YES if the knight can open all doors. Otherwise, print NO.

## 说明/提示

In the first testcase, the knight first collects all keys, then opens all doors with them.

In the second testcase, there is a red door right in front of the knight, but he doesn't have a key for it.

In the third testcase, the key to each door is in front of each respective door, so the knight collects the key and uses it immediately three times.

In the fourth testcase, the knight can't open the blue door.

## 样例 #1

### 输入

```
4
rgbBRG
RgbrBG
bBrRgG
rgRGBb
```

### 输出

```
YES
NO
YES
NO
```



---

---
title: "Lucky?"
layout: "post"
diff: 入门
pid: CF1676A
tag: ['模拟']
---

# Lucky?

## 题目描述

A ticket is a string consisting of six digits. A ticket is considered lucky if the sum of the first three digits is equal to the sum of the last three digits. Given a ticket, output if it is lucky or not. Note that a ticket can have leading zeroes.

## 输入格式

The first line of the input contains an integer $ t $ ( $ 1 \leq t \leq 10^3 $ ) — the number of testcases.

The description of each test consists of one line containing one string consisting of six digits.

## 输出格式

Output $ t $ lines, each of which contains the answer to the corresponding test case. Output "YES" if the given ticket is lucky, and "NO" otherwise.

You can output the answer in any case (for example, the strings "yEs", "yes", "Yes" and "YES" will be recognized as a positive answer).

## 说明/提示

In the first test case, the sum of the first three digits is $ 2 + 1 + 3 = 6 $ and the sum of the last three digits is $ 1 + 3 + 2 = 6 $ , they are equal so the answer is "YES".

In the second test case, the sum of the first three digits is $ 9 + 7 + 3 = 19 $ and the sum of the last three digits is $ 8 + 9 + 4 = 21 $ , they are not equal so the answer is "NO".

In the third test case, the sum of the first three digits is $ 0 + 4 + 5 = 9 $ and the sum of the last three digits is $ 2 + 0 + 7 = 9 $ , they are equal so the answer is "YES".

## 样例 #1

### 输入

```
5
213132
973894
045207
000000
055776
```

### 输出

```
YES
NO
YES
YES
NO
```



---

---
title: "Equal Candies"
layout: "post"
diff: 入门
pid: CF1676B
tag: ['模拟', '数学']
---

# Equal Candies

## 题目描述

There are $ n $ boxes with different quantities of candies in each of them. The $ i $ -th box has $ a_i $ candies inside.

You also have $ n $ friends that you want to give the candies to, so you decided to give each friend a box of candies. But, you don't want any friends to get upset so you decided to eat some (possibly none) candies from each box so that all boxes have the same quantity of candies in them. Note that you may eat a different number of candies from different boxes and you cannot add candies to any of the boxes.

What's the minimum total number of candies you have to eat to satisfy the requirements?

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 50 $ ) — the number of boxes you have.

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \leq a_i \leq 10^7 $ ) — the quantity of candies in each box.

## 输出格式

For each test case, print a single integer denoting the minimum number of candies you have to eat to satisfy the requirements.

## 说明/提示

For the first test case, you can eat $ 1 $ candy from the second box, $ 2 $ candies from the third box, $ 3 $ candies from the fourth box and $ 4 $ candies from the fifth box. Now the boxes have $ [1, 1, 1, 1, 1] $ candies in them and you ate $ 0 + 1 + 2 + 3 + 4 = 10 $ candies in total so the answer is $ 10 $ .

For the second test case, the best answer is obtained by making all boxes contain $ 5 $ candies in them, thus eating $ 995 + 995 + 0 + 995 + 995 + 995 = 4975 $ candies in total.

## 样例 #1

### 输入

```
5
5
1 2 3 4 5
6
1000 1000 5 1000 1000 1000
10
1 2 3 5 1 2 7 9 13 5
3
8 8 8
1
10000000
```

### 输出

```
10
4975
38
0
0
```



---

---
title: "Digit Minimization"
layout: "post"
diff: 入门
pid: CF1684A
tag: ['模拟']
---

# Digit Minimization

## 题目描述

有一个用十进制表示的没有前导零的正整数 $n$ 。Alice 和 Bob 正在用这个数玩一个游戏。Alice 先手，他们轮流进行游戏。

在她的这一轮中，Alice 应该交换这个数中的任何不同位置的两位。轮到 Bob 时，他每次都会删除这个数的末一位。当这个数只剩一位时，游戏结束。

你需要找出 Alice 用最佳方法在最后找出的最小数。

## 输入格式

本题有多组数据。

输入数据第一行包含一个正整数 $t$（$1 \le t \le 10^4$），表示数据组数。

接下来 $t$ 行，每行包含一个正整数 $n$（$10 \le n \le 10^9$），表示游戏中用到的这个正整数，$n$ 在十进制表示中不含前导零。

## 输出格式

输出 $t$ 行，每行输出一个正整数，表示游戏结束时 Alice 能得到的最小数。

### 输入输出样例解释

在第一个测试数据中，Alice 将 $1$ 和 $2$ 交换，然后 Bob 又将最后一位 $1$ 删除。最后得到结果 $2$。

在第二个测试数据中，Alice 将 $3$ 和 $1$ 交换，变成 $312$。然后 Bob 将最后一位 $2$ 删除，变成 $31$。接着 Alice 将 $3$ 和 $1$ 交换，变成 $13$。最后 Bob 将最后一位删除，得到最终的结果 $1$。

## 样例 #1

### 输入

```
3
12
132
487456398
```

### 输出

```
2
1
3
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
title: "Spell Check"
layout: "post"
diff: 入门
pid: CF1722A
tag: ['模拟']
---

# Spell Check

## 题目描述

输入一个字符串，请判断这个字符串是不是字符串 `Timur` 的一种排列。

例如：`Timur` ，`miurT` ，`Trumi` ，`mriTu` 都是正确的排列。

**注意：正确的排列必须包含大写的T和小写的其他字母。**

---

## 输入格式

输入的第一行一个整数 $t$ ，表示有 $t$ 组数据。

对于每组数据，第一行一个整数 $n$，表示输入的名字排列的长度。

第二行一个字符串，表示需要判断的排列。

---

## 输出格式

对于每组数据，如果当前排列事是正确的，则输出 `YES`，否则输出 `NO`。

---

## 说明/提示

$ 1 \le t \le 10^3 $ , $1 \le n \le 10$。

Translate By @Andy_L

## 样例 #1

### 输入

```
10
5
Timur
5
miurT
5
Trumi
5
mriTu
5
timur
4
Timr
6
Timuur
10
codeforces
10
TimurTimur
5
TIMUR
```

### 输出

```
YES
YES
YES
YES
NO
NO
NO
NO
NO
NO
```



---

---
title: "Colourblindness"
layout: "post"
diff: 入门
pid: CF1722B
tag: ['模拟']
---

# Colourblindness

## 题目描述

Vasya has a grid with $ 2 $ rows and $ n $ columns. He colours each cell red, green, or blue.

Vasya is colourblind and can't distinguish green from blue. Determine if Vasya will consider the two rows of the grid to be coloured the same.

## 输入格式

The input consists of multiple test cases. The first line contains an integer $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 100 $ ) — the number of columns of the grid.

The following two lines each contain a string consisting of $ n $ characters, each of which is either R, G, or B, representing a red, green, or blue cell, respectively — the description of the grid.

## 输出格式

For each test case, output "YES" if Vasya considers the grid's two rows to be identical, and "NO" otherwise.

You can output the answer in any case (for example, the strings "yEs", "yes", "Yes" and "YES" will be recognized as a positive answer).

## 说明/提示

In the first test case, Vasya sees the second cell of each row as the same because the second cell of the first row is green and the second cell of the second row is blue, so he can't distinguish these two cells. The rest of the rows are equal in colour. Therefore, Vasya will say that the two rows are coloured the same, even though they aren't.

In the second test case, Vasya can see that the two rows are different.

In the third test case, every cell is green or blue, so Vasya will think they are the same.

## 样例 #1

### 输入

```
6
2
RG
RB
4
GRBG
GBGB
5
GGGGG
BBBBB
7
BBBBBBB
RRRRRRR
8
RGBRRGBR
RGGRRBGR
1
G
G
```

### 输出

```
YES
NO
YES
NO
YES
YES
```



---

---
title: "Two Vessels"
layout: "post"
diff: 入门
pid: CF1872A
tag: ['模拟']
---

# Two Vessels

## 题目描述

You have two vessels with water. The first vessel contains $ a $ grams of water, and the second vessel contains $ b $ grams of water. Both vessels are very large and can hold any amount of water.

You also have an empty cup that can hold up to $ c $ grams of water.

In one move, you can scoop up to $ c $ grams of water from any vessel and pour it into the other vessel. Note that the mass of water poured in one move does not have to be an integer.

What is the minimum number of moves required to make the masses of water in the vessels equal? Note that you cannot perform any actions other than the described moves.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 1000 $ ). The description of the test cases follows.

Each test case consists of a single line containing three integers $ a $ , $ b $ , and $ c $ ( $ 1 \le a, b, c \le 100 $ ) — the mass of water in the vessels and the capacity of the cup, respectively.

## 输出格式

For each test case, output a single number — the minimum number of moves required to make the masses of water in the vessels equal. It can be shown, that it is always possible.

## 说明/提示

In the first test case, only one move is enough: if we pour $ 2 $ grams of water from the second vessel into the first one, both vessels will contain $ 5 $ grams of water.

In the second example test case, three moves are enough:

- Pour $ 3 $ grams of water from the first vessel into the second one. After this move, the first vessel will contain $ 17 - 3 = 14 $ grams of water, and the second vessel will contain $ 4 + 3 = 7 $ grams.
- Pour $ 2 $ grams of water from the first vessel into the second one. After this move, the first vessel will contain $ 14 - 2 = 12 $ grams of water, and the second vessel will contain $ 7 + 2 = 9 $ grams.
- Finally, pour $ 1.5 $ grams of water from the first vessel into the second one. After this move, the first vessel will contain $ 12 - 1.5 = 10.5 $ grams of water, and the second vessel will contain $ 9 + 1.5 = 10.5 $ grams.

Note that this is not the only way to equalize the vessels in $ 3 $ moves, but there is no way to do it in $ 2 $ moves.

In the third example test case, the vessels initially contain the same amount of water, so no moves are needed. The answer is $ 0 $ .

## 样例 #1

### 输入

```
6
3 7 2
17 4 3
17 17 1
17 21 100
1 100 1
97 4 3
```

### 输出

```
1
3
0
1
50
16
```



---

---
title: "YetnotherrokenKeoard"
layout: "post"
diff: 入门
pid: CF1907B
tag: ['模拟']
---

# YetnotherrokenKeoard

## 题目描述

Polycarp has a problem — his laptop keyboard is broken.

Now, when he presses the 'b' key, it acts like an unusual backspace: it deletes the last (rightmost) lowercase letter in the typed string. If there are no lowercase letters in the typed string, then the press is completely ignored.

Similarly, when he presses the 'B' key, it deletes the last (rightmost) uppercase letter in the typed string. If there are no uppercase letters in the typed string, then the press is completely ignored.

In both cases, the letters 'b' and 'B' are not added to the typed string when these keys are pressed.

Consider an example where the sequence of key presses was "ARaBbbitBaby". In this case, the typed string will change as follows: "" $ \xrightarrow{\texttt{A}} $ "A" $ \xrightarrow{\texttt{R}} $ "AR" $ \xrightarrow{\texttt{a}} $ "ARa" $ \xrightarrow{\texttt{B}} $ "Aa" $ \xrightarrow{\texttt{b}} $ "A" $ \xrightarrow{\texttt{b}} $ "A" $ \xrightarrow{\texttt{i}} $ "Ai" $ \xrightarrow{\texttt{t}} $ "Ait" $ \xrightarrow{\texttt{B}} $ "it" $ \xrightarrow{\texttt{a}} $ "ita" $ \xrightarrow{\texttt{b}} $ "it" $ \xrightarrow{\texttt{y}} $ "ity".

Given a sequence of pressed keys, output the typed string after processing all key presses.

## 输入格式

The first line of the input data contains an integer $ t $ ( $ 1 \le t \le 1000 $ ), the number of test cases in the test.

The following contains $ t $ non-empty lines, which consist of lowercase and uppercase letters of the Latin alphabet.

It is guaranteed that each line contains at least one letter and the sum of the lengths of the lines does not exceed $ 10^6 $ .

## 输出格式

For each test case, output the result of processing the key presses on a separate line. If the typed string is empty, then output an empty line.

## 样例 #1

### 输入

```
12
ARaBbbitBaby
YetAnotherBrokenKeyboard
Bubble
Improbable
abbreviable
BbBB
BusyasaBeeinaBedofBloomingBlossoms
CoDEBARbIES
codeforces
bobebobbes
b
TheBBlackbboard
```

### 输出

```
ity
YetnotherrokenKeoard
le
Imprle
revile

usyasaeeinaedofloominglossoms
CDARIES
codeforces
es

helaoard
```



---

---
title: "Odd One Out"
layout: "post"
diff: 入门
pid: CF1915A
tag: ['模拟']
---

# Odd One Out

## 题目描述

You are given three digits $ a $ , $ b $ , $ c $ . Two of them are equal, but the third one is different from the other two.

Find the value that occurs exactly once.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 270 $ ) — the number of test cases.

The only line of each test case contains three digits $ a $ , $ b $ , $ c $ ( $ 0 \leq a $ , $ b $ , $ c \leq 9 $ ). Two of the digits are equal, but the third one is different from the other two.

## 输出格式

For each test case, output the value that occurs exactly once.

## 样例 #1

### 输入

```
10
1 2 2
4 3 4
5 5 6
7 8 8
9 0 9
3 6 3
2 8 2
5 7 7
7 7 5
5 7 5
```

### 输出

```
1
3
6
7
0
6
8
5
5
7
```



---

---
title: "Not Quite Latin Square"
layout: "post"
diff: 入门
pid: CF1915B
tag: ['模拟']
---

# Not Quite Latin Square

## 题目描述

A Latin square is a $ 3 \times 3 $ grid made up of the letters $ \texttt{A} $ , $ \texttt{B} $ , and $ \texttt{C} $ such that:

- in each row, the letters $ \texttt{A} $ , $ \texttt{B} $ , and $ \texttt{C} $ each appear once, and
- in each column, the letters $ \texttt{A} $ , $ \texttt{B} $ , and $ \texttt{C} $ each appear once.

 For example, one possible Latin square is shown below. $ $$$\begin{bmatrix} \texttt{A} & \texttt{B} & \texttt{C} \\ \texttt{C} & \texttt{A} & \texttt{B} \\ \texttt{B} & \texttt{C} & \texttt{A} \\ \end{bmatrix} $ $ <p>You are given a Latin square, but one of the letters was replaced with a question mark  $ \texttt{?}$$$. Find the letter that was replaced.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \leq t \leq 108 $ ) — the number of testcases.

Each test case contains three lines, each consisting of three characters, representing the Latin square. Each character is one of $ \texttt{A} $ , $ \texttt{B} $ , $ \texttt{C} $ , or $ \texttt{?} $ .

Each test case is a Latin square with exactly one of the letters replaced with a question mark $ \texttt{?} $ .

## 输出格式

For each test case, output the letter that was replaced.

## 说明/提示

The correct Latin squares for the three test cases are shown below:

 $ $$$\begin{bmatrix} \texttt{A} & \texttt{B} & \texttt{C} \\ \texttt{C} & \color{red}{\texttt{A}} & \texttt{B} \\ \texttt{B} & \texttt{C} & \texttt{A} \\ \end{bmatrix} \quad \begin{bmatrix} \texttt{B} & \texttt{C} & \texttt{A} \\ \texttt{C} & \texttt{A} & \color{red}{\texttt{B}} \\ \texttt{A} & \texttt{B} & \texttt{C} \\ \end{bmatrix} \quad \begin{bmatrix} \color{red}{\texttt{C}} & \texttt{A} & \texttt{B} \\ \texttt{B} & \texttt{C} & \texttt{A} \\ \texttt{A} & \texttt{B} & \texttt{C} \\ \end{bmatrix} $ $$$

## 样例 #1

### 输入

```
3
ABC
C?B
BCA
BCA
CA?
ABC
?AB
BCA
ABC
```

### 输出

```
A
B
C
```



---

---
title: "Can I Square?"
layout: "post"
diff: 入门
pid: CF1915C
tag: ['模拟']
---

# Can I Square?

## 题目描述

Calin has $ n $ buckets, the $ i $ -th of which contains $ a_i $ wooden squares of side length $ 1 $ .

Can Calin build a square using all the given squares?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ) — the number of buckets.

The second line of each test case contains $ n $ integers $ a_1, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — the number of squares in each bucket.

The sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output "YES" if Calin can build a square using all of the given $ 1 \times 1 $ squares, and "NO" otherwise.

You can output the answer in any case (for example, the strings "yEs", "yes", "Yes" and "YES" will be recognized as a positive answer).

## 说明/提示

In the first test case, Calin can build a $ 3 \times 3 $ square.

In the second test case, Calin can build a $ 4 \times 4 $ square.

In the third test case, Calin cannot build a square using all the given squares.

## 样例 #1

### 输入

```
5
1
9
2
14 2
7
1 2 3 4 5 6 7
6
1 3 5 7 9 11
4
2 2 2 2
```

### 输出

```
YES
YES
NO
YES
NO
```



---

---
title: "Unnatural Language Processing"
layout: "post"
diff: 入门
pid: CF1915D
tag: ['模拟']
---

# Unnatural Language Processing

## 题目描述

Lura was bored and decided to make a simple language using the five letters $ \texttt{a} $ , $ \texttt{b} $ , $ \texttt{c} $ , $ \texttt{d} $ , $ \texttt{e} $ . There are two types of letters:

- vowels — the letters $ \texttt{a} $ and $ \texttt{e} $ . They are represented by $ \textsf{V} $ .
- consonants — the letters $ \texttt{b} $ , $ \texttt{c} $ , and $ \texttt{d} $ . They are represented by $ \textsf{C} $ .

 There are two types of syllables in the language: $ \textsf{CV} $ (consonant followed by vowel) or $ \textsf{CVC} $ (vowel with consonant before and after). For example, $ \texttt{ba} $ , $ \texttt{ced} $ , $ \texttt{bab} $ are syllables, but $ \texttt{aa} $ , $ \texttt{eda} $ , $ \texttt{baba} $ are not.A word in the language is a sequence of syllables. Lura has written a word in the language, but she doesn't know how to split it into syllables. Help her break the word into syllables.

For example, given the word $ \texttt{bacedbab} $ , it would be split into syllables as $ \texttt{ba.ced.bab} $ (the dot $ \texttt{.} $ represents a syllable boundary).

## 输入格式

The input consists of multiple test cases. The first line contains an integer $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ) — the length of the word.

The second line of each test case contains a string consisting of $ n $ lowercase Latin characters — the word.

All words given are valid words in the language; that is, they only use the letters $ \texttt{a} $ , $ \texttt{b} $ , $ \texttt{c} $ , $ \texttt{d} $ , $ \texttt{e} $ , and each word is made up of several syllables.

The sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For test case, output a string denoting the word split into syllables by inserting a dot $ \texttt{.} $ between every pair of adjacent syllables.

If there are multiple possible splittings, output any of them. The input is given in such a way that at least one possible splitting exists.

## 样例 #1

### 输入

```
6
8
bacedbab
4
baba
13
daddecabeddad
3
dac
6
dacdac
22
dababbabababbabbababba
```

### 输出

```
ba.ced.bab
ba.ba
dad.de.ca.bed.dad
dac
dac.dac
da.bab.ba.ba.bab.bab.ba.bab.ba
```



---

---
title: "Rudolf and the Ticket"
layout: "post"
diff: 入门
pid: CF1941A
tag: ['模拟']
---

# Rudolf and the Ticket

## 题目描述

Rudolf is going to visit Bernard, and he decided to take the metro to get to him. The ticket can be purchased at a machine that accepts exactly two coins, the sum of which does not exceed $ k $ .

Rudolf has two pockets with coins. In the left pocket, there are $ n $ coins with denominations $ b_1, b_2, \dots, b_n $ . In the right pocket, there are $ m $ coins with denominations $ c_1, c_2, \dots, c_m $ . He wants to choose exactly one coin from the left pocket and exactly one coin from the right pocket (two coins in total).

Help Rudolf determine how many ways there are to select indices $ f $ and $ s $ such that $ b_f + c_s \le k $ .

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases. Then follows the description of each test case.

The first line of each test case contains three natural numbers $ n $ , $ m $ , and $ k $ ( $ 1 \le n, m \le 100, 1 \le k \le 2000 $ ) — the number of coins in the left and right pockets, and the maximum sum of two coins for the ticket payment at the counter, respectively.

The second line of each test case contains $ n $ integers $ b_i $ ( $ 1 \le b_i \le 1000 $ ) — the denominations of coins in the left pocket.

The third line of each test case contains $ m $ integers $ c_i $ ( $ 1 \le c_i \le 1000 $ ) — the denominations of coins in the right pocket.

## 输出格式

For each testcase, output a single integer — the number of ways Rudolf can select two coins, taking one from each pocket, so that the sum of the coins does not exceed $ k $ .

## 说明/提示

Note that the pairs indicate the indices of the coins in the array, not their denominations.

In the first test case, Rudolf can choose the following pairs of coins: $ [1, 1], [1, 2], [1, 4], [2, 1], [2, 2], [2, 4] $ .

In the second test case, Rudolf cannot choose one coin from each pocket in any way, as the sum of any two elements from the first and second arrays will exceed the value of $ k=4 $ .

In the third test case, Rudolf can choose: $ [1, 1], [2, 1], [3, 1], [4, 1] $ .

In the fourth test case, Rudolf can choose any coin from the left pocket and any coin from the right pocket.

## 样例 #1

### 输入

```
4
4 4 8
1 5 10 14
2 1 8 1
2 3 4
4 8
1 2 3
4 2 7
1 1 1 1
2 7
3 4 2000
1 1 1
1 1 1 1
```

### 输出

```
6
0
4
12
```



---

---
title: "Setting up Camp"
layout: "post"
diff: 入门
pid: CF1945A
tag: ['模拟']
---

# Setting up Camp

## 题目描述

## 题目
组委会计划在游览结束后带领奥林匹克运动会的参赛选手进行徒步旅行。目前，正在计算需要搭乘的帐篷数量。据了解，每个帐篷最多可容纳 $3$ 人。

在参赛选手中，有 $a$ 名内向型选手， $b$ 名外向型选手和 $c$ 名没有要求的选手：

- 每个内向选手都想独自住在帐篷里。因此，内向选手的帐篷里必须只有一个人--就是他自己。
- 每个外向者都希望和两个人住在一个帐篷里。因此，一个外向者的帐篷里必须正好有三个人。
- 每个人都可以选择任何一种方式(独居或者与他人同住)。

请问至少需要多少顶帐篷，才能让所有参加者都能根据自己的喜好找到住处。如果无法满足所有参赛者的愿望，则输出 $-1$ 。

## 输入格式

每个测试由多个测试用例组成。第一行包含一个整数 $t$ ( $1 \le t \le 10^4$ ) - 测试用例的数量。随后是测试用例的说明。

每个测试用例由一行描述，其中包含三个整数 $a$ 、 $b$ 、 $c$ ( $0 \le a, b, c \le 10^9$ )--分别是内向型、外向型和通用型的数量。

## 输出格式

对于每个测试用例，输出一个整数，即**最小帐篷数**，如果无法容纳参赛者，则输出 $-1$ 。

## 样例 #1

### 输入

```
10
1 2 3
1 4 1
1 4 2
1 1 1
1 3 2
19 7 18
0 0 0
7 0 0
0 24 0
1000000000 1000000000 1000000000
```

### 输出

```
3
-1
3
-1
3
28
0
7
8
1666666667
```



---

---
title: "Stair, Peak, or Neither?"
layout: "post"
diff: 入门
pid: CF1950A
tag: ['模拟']
---

# Stair, Peak, or Neither?

## 题目描述

You are given three digits $ a $ , $ b $ , and $ c $ . Determine whether they form a stair, a peak, or neither.

- A stair satisfies the condition $ a<b<c $ .
- A peak satisfies the condition $ a<b>c $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

The only line of each test case contains three digits $ a $ , $ b $ , $ c $ ( $ 0 \leq a $ , $ b $ , $ c \leq 9 $ ).

## 输出格式

For each test case, output "STAIR" if the digits form a stair, "PEAK" if the digits form a peak, and "NONE" otherwise (output the strings without quotes).

## 样例 #1

### 输入

```
7
1 2 3
3 2 1
1 5 3
3 4 1
0 0 0
4 1 7
4 5 7
```

### 输出

```
STAIR
NONE
PEAK
PEAK
NONE
NONE
STAIR
```



---

---
title: "Upscaling"
layout: "post"
diff: 入门
pid: CF1950B
tag: ['模拟']
---

# Upscaling

## 题目描述

给你一个整数 $n$，输出一个 $2n \times 2n$ 的棋盘，由 $2 \times 2$ 的 `#` 与 $2 \times 2$ 的 `.` 构成，最左上角的单元格为 $2 \times 2$ 的 `#` 构成。

## 输入格式

第 $1$ 行为一个整数 $t$，表示询问的次数。

接下来 $t$ 行，每行一个整数 $n$。

## 输出格式

对于每个测试用例，输出 $2n$ 行，每行包含 $2n$ 个没有空格的字符——如语句中所述的棋盘。不要在每个测试用例之间输出空行。

###### translate by [sqrt404](https://www.luogu.com.cn/user/637410)

## 样例 #1

### 输入

```
4
1
2
3
4
```

### 输出

```
##
##
##..
##..
..##
..##
##..##
##..##
..##..
..##..
##..##
##..##
##..##..
##..##..
..##..##
..##..##
##..##..
##..##..
..##..##
..##..##
```



---

---
title: "Clock Conversion"
layout: "post"
diff: 入门
pid: CF1950C
tag: ['模拟']
---

# Clock Conversion

## 题目描述

Given the time in 24-hour format, output the equivalent time in 12-hour format.

- [24-hour format](https://en.wikipedia.org/wiki/24-hour_clock#Description) divides the day into 24 hours from $ 00 $ to $ 23 $ , each of which has 60 minutes from $ 00 $ to $ 59 $ .
- [12-hour format](https://en.wikipedia.org/wiki/12-hour_clock#Description) divides the day into two halves: the first half is $ \mathrm{AM} $ , and the second half is $ \mathrm{PM} $ . In each half, the hours are numbered in the order $ 12, 01, 02, 03, \dots, 11 $ . Each hour has 60 minutes numbered from $ 00 $ to $ 59 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 1440 $ ) — the number of test cases.

The only line of each test case contains a string $ s $ of length $ 5 $ with format hh:mm representing a valid time in the 24-hour format. hh represents the hour from $ 00 $ to $ 23 $ , and mm represents the minute from $ 00 $ to $ 59 $ .

The input will always be a valid time in 24-hour format.

## 输出格式

For each test case, output two strings separated by a space ("hh:mm AM" or "hh:mm PM"), which are the 12-hour equivalent to the time provided in the test case (without quotes).

You should output the time exactly as indicated; in particular, you should not remove leading zeroes.

## 样例 #1

### 输入

```
11
09:41
18:06
12:14
00:59
00:00
14:34
01:01
19:07
11:59
12:00
21:37
```

### 输出

```
09:41 AM
06:06 PM
12:14 PM
12:59 AM
12:00 AM
02:34 PM
01:01 AM
07:07 PM
11:59 AM
12:00 PM
09:37 PM
```



---

---
title: "Yogurt Sale"
layout: "post"
diff: 入门
pid: CF1955A
tag: ['模拟']
---

# Yogurt Sale

## 题目描述

The price of one yogurt at the "Vosmiorochka" store is $ a $ burles, but there is a promotion where you can buy two yogurts for $ b $ burles.

Maxim needs to buy exactly $ n $ yogurts. When buying two yogurts, he can choose to buy them at the regular price or at the promotion price.

What is the minimum amount of burles Maxim should spend to buy $ n $ yogurts?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le {10}^{4} $ ) — the number of test cases.

The first and only line of each test case contains three integers $ n $ , $ a $ , and $ b $ ( $ 1 \le n \le 100 $ , $ 1 \le a, b \le 30 $ ) — the number of yogurts Maxim wants to buy, the price for one yogurt, and the price for two yogurts on promotion.

## 输出格式

For each test case, print in a separate line the minimum cost of buying $ n $ yogurts at "Vosmiorochka".

## 说明/提示

In the third test case of the example, it is more advantageous to buy three yogurts for $ 15 $ burles than two for $ 11 $ and one for $ 5 $ .

In the fourth test case of the example, you need to buy four yogurts, each for $ 5 $ burles.

## 样例 #1

### 输入

```
4
2 5 9
3 5 9
3 5 11
4 5 11
```

### 输出

```
9
14
15
20
```



---

---
title: "Two Friends"
layout: "post"
diff: 入门
pid: CF1969A
tag: ['模拟']
---

# Two Friends

## 题目描述

Monocarp 想要举办一个聚会。他有 $n$ 个朋友，并且他想要让他们之中的至少 $2$ 人来参加聚会。

第 $i$ 个朋友的最好的朋友是 $p_i$。每一个 $p_i$ 都是不一样的，并且对于所有的 $i \in [1, n]$，$p_i \neq i$。

Monocarp 可以给朋友们发送邀请。如果第 $i$ 个朋友和第 $p_i$ 个朋友都收到了邀请（注意第 $p_i$ 个朋友不一定真的要去参加聚会），那么第 $i$ 个朋友会去参加聚会。每份邀请都会发送给其中一位朋友。

举个例子，如果 $p = [3,1,2,5,4]$，并且 Monocarp 给朋友 $[1, 2, 4, 5]$ 发邀请，那么朋友 $[2, 4,5]$ 会去参加聚会。朋友 $1$ 不会去参加聚会因为他最好的朋友没有收到邀请；朋友 $3$ 不会去参加聚会因为他没有受到邀请。

求 Monocarp 最少需要发出的邀请数以让至少 $2$ 个朋友来参加聚会。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 5000$），表示数据组数。

每一组数据包含两行：

- 第一行包含一个整数 $n$（$2\le n \le 50$），表示朋友数；
- 第二行包含 $n$ 个整数 $p_1, p_2, \dotsc, p_n$（$1 \le p_i \le n$；$p_i \neq i$；所有的 $p_i$ 都不一样）。

## 输出格式

输出一个整数，为 Monocarp 最少需要发出的邀请数。

### 样例解释

在第一组数据中，Monocarp 可以给朋友 $4$ 和 $5$ 发邀请。他们两人都会来参加聚会因为他们是对方最好的朋友，并且他们都收到了邀请。

在第二组数据中，例如，Monocarp 可以给朋友 $1,2$ 和 $3$ 发邀请。然后朋友 $1$ 和 $2$ 会出席：朋友 $1$ 和他最好的朋友 $2$ 都收到了邀请，朋友 $2$ 和他最好的朋友 $3$ 都收到了邀请。朋友 $3$ 不会出席因为他最好的朋友 $4$ 没有收到邀请。只给少于 $3$ 个朋友发邀请函还至少有 $2$ 个朋友来参加聚会是不可能的。

在第三组数据中，Monocarp 可以给朋友 $1$ 和 $2$ 都发邀请，然后他们两个都会出席。

## 样例 #1

### 输入

```
3
5
3 1 2 5 4
4
2 3 4 1
2
2 1
```

### 输出

```
2
3
2
```



---

---
title: "My First Sorting Problem"
layout: "post"
diff: 入门
pid: CF1971A
tag: ['模拟']
---

# My First Sorting Problem

## 题目描述

You are given two integers $ x $ and $ y $ .

Output two integers: the minimum of $ x $ and $ y $ , followed by the maximum of $ x $ and $ y $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases.

The only line of each test case contains two space-separated integers $ x $ and $ y $ ( $ 0 \leq x, y \leq 9 $ ).

## 输出格式

For each test case, output two integers: the minimum of $ x $ and $ y $ , followed by the maximum of $ x $ and $ y $ .

## 样例 #1

### 输入

```
10
1 9
8 4
1 4
3 4
2 0
2 4
6 9
3 3
0 0
9 9
```

### 输出

```
1 9
4 8
1 4
3 4
0 2
2 4
6 9
3 3
0 0
9 9
```



---

---
title: "Different String"
layout: "post"
diff: 入门
pid: CF1971B
tag: ['模拟']
---

# Different String

## 题目描述

给定一个以小写字母构成的字符串 $s$。

现在你的任务是，重新排列 $s$ 的字符以形成一个不等于 $s$ 的新字符串 $r$。

## 输入格式

**本题单个测试点内包含多组测试数据。**

第一行包含一个整数 $t$（$1\leq t\leq 1000$），表示测试数据组数。

每个测试用例的唯一一行包含一个字符串 $s$，长度最多为 $10$，由小写英文字母组成。

## 输出格式

对于每个测试用例，如果不存在语句中描述的字符串 $r$，则输出`NO`。

否则，输出`YES`。然后，输出一行一个字符串 $r$，由字符串 $s$ 的字母组成。

你可以以任何大小写形式输出`YES`和`NO`。

如果可以有多个答案，则可以输出其中任何一个。

## 样例 #1

### 输入

```
8
codeforces
aaaaa
xxxxy
co
d
nutdealer
mwistht
hhhhhhhhhh
```

### 输出

```
YES
forcodesec
NO
YES
xxyxx
YES
oc
NO
YES
undertale
YES
thtsiwm
NO
```



---

---
title: "Verify Password"
layout: "post"
diff: 入门
pid: CF1976A
tag: ['模拟']
---

# Verify Password

## 题目描述

Monocarp 正在制作他的新网站，目前的挑战是如何让用户选择强密码。

Monocarp 决定强密码应满足以下条件：

- 密码只能由小写拉丁字母和数字组成；
- 字母后面不能有数字（因此，每个字母后面要么有另一个字母，要么这个密码字符串结束）；
- 所有数字应按非递减顺序排序；
- 所有字母应按非递减顺序排序。

请注意，密码可以只有字母或数字。

Monocarp 成功地实现了识别第一个条件，但他在其余条件上很吃力。你能帮他验证密码吗？

## 输入格式

**本题目为多测。**

第一行包含一个整数 $ t $ ( $ 1 \le t \le 1000 $ ) ，为子测试点的数量。

每个子测试点的第一行包含一个整数 $ n $ ( $ 1 \le n \le 20 $ ) ，为密码的长度。

每个子测试点的第二行包含一个字符串，正好由 $ n $ 个字符组成。每个字符都是小写拉丁字母或数字。

## 输出格式

对于每个子测试点，如果给出的密码很强，则打印 `YES` ，否则打印 `NO` 。

### 样例 #1

#### 样例输入 #1

```
5
4
12ac
5
123wa
9
allllmost
5
ac123
6
011679
```

#### 样例输出 #1

```
YES
NO
YES
NO
YES
```

## 说明/提示

在第二个子测试点中，字母没有按照不递减的顺序排列。

在第四个子测试点中，字母后面有一个数字--数字 `1` 在字母 `A` 后面。

## 样例 #1

### 输入

```
5
4
12ac
5
123wa
9
allllmost
5
ac123
6
011679
```

### 输出

```
YES
NO
YES
NO
YES
```



---

---
title: "Problem Generator"
layout: "post"
diff: 入门
pid: CF1980A
tag: ['模拟']
---

# Problem Generator

## 题目描述

Vlad 计划在下个月举行 $m$ 轮比赛。每轮比赛应包含一个难度等级为 "A"、"B"、"C"、"D"、"E"、"F "和 "G "的问题。

Vlad 已经有了一个有 $n$ 个问题的题库，其中第 $i$ 个问题的难度等级为 $a_i$ 。这些问题可能不够多，所以他可能需要再想出一些问题。

Vlad 想要尽可能少地提出问题，所以他要求你找出他需要提出的问题的最少数量，以便举行 $m$ 轮比赛。

例如，如果 $m=1$ 、 $n = 10$ 、 $a=$ "BGECDCBDED"，那么他需要提出两道难题：一道难度为 "A"，一道难度为 "F"。

## 输入格式

第一行包含一个整数 $t$ ( $1 \le t \le 1000$ ) ，表示测试用例数。

每个测试用例的第一行包含两个整数 $n$ 和 $m$ ( $1 \le n \le 50$ , $1 \le m \le 5$ )，分别是题库中的问题数和即将进行的比赛数。

每个测试用例的第二行包含一个由 $n$ 个字符（从 "A "到 "G"）组成的字符串 $a$，表示题库中问题的难度。

## 输出格式

对于每个测试用例，输出一个整数，即最少需要再出多少个问题才能举行 $m$ 轮比赛。

## 样例 #1

### 输入

```
3
10 1
BGECDCBDED
10 2
BGECDCBDED
9 1
BBCDEFFGG
```

### 输出

```
2
5
1
```



---

---
title: "Creating Words"
layout: "post"
diff: 入门
pid: CF1985A
tag: ['模拟', '字符串']
---

# Creating Words

## 题目描述

Matthew is given two strings $ a $ and $ b $ , both of length $ 3 $ . He thinks it's particularly funny to create two new words by swapping the first character of $ a $ with the first character of $ b $ . He wants you to output $ a $ and $ b $ after the swap.

Note that the new words may not necessarily be different.

## 输入格式

The first line contains $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases.

The first and only line of each test case contains two space-separated strings, $ a $ and $ b $ , both of length $ 3 $ . The strings only contain lowercase Latin letters.

## 输出格式

For each test case, after the swap, output $ a $ and $ b $ , separated by a space.

## 样例 #1

### 输入

```
6
bit set
cat dog
hot dog
uwu owo
cat cat
zzz zzz
```

### 输出

```
sit bet
dat cog
dot hog
owu uwo
cat cat
zzz zzz
```



---

---
title: "Maximum Multiple Sum"
layout: "post"
diff: 入门
pid: CF1985B
tag: ['模拟', '数学']
---

# Maximum Multiple Sum

## 题目描述

给定一个整数$ n $，找到一个整数$ x $，这样:

- $ 2 \leq x \leq n $。
- 将 $ x $ 中小于等于 $ n $ 的倍数之和取最大值。形式上是 $ x + 2x + 3x + \dots + kx $，其中 $ kx \leq n $ 比 $ x $ 的所有可能值都大。

## 输入格式

第一行包含$ t $ ($ 1 \leq t \leq 100 $)——测试用例的数量。

每个测试用例包含一个整数 $ n $ ($ 2 \leq n \leq 100 $)。

## 输出格式

对于每个测试用例，输出一个整数，即$ x $的最优值。可以看出只有一个唯一的答案。

## 说明/提示

对于“$ n = 3 $”，“$ x $”可能取值为“$ 2 $”和“$ 3 $”。所有小于等于$ n $的$ 2 $的倍数之和为$ 2 $，所有小于等于$ n $的$ 3 $的倍数之和为$ 3 $。因此，$ 3 $是$ x $的最优值。

对于$ n = 15 $, $ x $的最优值为$ 2 $。小于或等于$ n $的所有$ 2 $的倍数之和为$ 2 + 4 + 6 + 8 + 10 + 12 + 14 = 56 $，可以证明它是$ x $的所有其他可能值的最大值。

## 样例 #1

### 输入

```
2
3
15
```

### 输出

```
3
2
```



---

---
title: "Scale"
layout: "post"
diff: 入门
pid: CF1996B
tag: ['模拟']
---

# Scale

## 题目描述

Tina has a square grid with $ n $ rows and $ n $ columns. Each cell in the grid is either $ 0 $ or $ 1 $ .

Tina wants to reduce the grid by a factor of $ k $ ( $ k $ is a divisor of $ n $ ). To do this, Tina splits the grid into $ k \times k $ nonoverlapping blocks of cells such that every cell belongs to exactly one block.

Tina then replaces each block of cells with a single cell equal to the value of the cells in the block. It is guaranteed that every cell in the same block has the same value.

For example, the following demonstration shows a grid being reduced by factor of $ 3 $ .

 Original grid  $ 0 $  $ 0 $  $ 0 $  $ 1 $  $ 1 $  $ 1 $  $ 0 $  $ 0 $  $ 0 $  $ 1 $  $ 1 $  $ 1 $  $ 0 $  $ 0 $  $ 0 $  $ 1 $  $ 1 $  $ 1 $  $ 1 $  $ 1 $  $ 1 $  $ 0 $  $ 0 $  $ 0 $  $ 1 $  $ 1 $  $ 1 $  $ 0 $  $ 0 $  $ 0 $  $ 1 $  $ 1 $  $ 1 $  $ 0 $  $ 0 $  $ 0 $   Reduced grid  $ 0 $  $ 1 $  $ 1 $  $ 0 $ Help Tina reduce the grid by a factor of $ k $ .

## 输入格式

The first line contains $ t $ ( $ 1 \leq t \leq 100 $ ) – the number of test cases.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1 \leq n \leq 1000 $ , $ 1 \le k \le n $ ,  $ k $ is a divisor of $ n $ ) — the number of rows and columns of the grid, and the factor that Tina wants to reduce the grid by.

Each of the following $ n $ lines contain $ n $ characters describing the cells of the grid. Each character is either $ 0 $ or $ 1 $ . It is guaranteed every $ k $ by $ k $ block has the same value.

It is guaranteed the sum of $ n $ over all test cases does not exceed $ 1000 $ .

## 输出格式

For each test case, output the grid reduced by a factor of $ k $ on a new line.

## 样例 #1

### 输入

```
4
4 4
0000
0000
0000
0000
6 3
000111
000111
000111
111000
111000
111000
6 2
001100
001100
111111
111111
110000
110000
8 1
11111111
11111111
11111111
11111111
11111111
11111111
11111111
11111111
```

### 输出

```
0
01
10
010
111
100
11111111
11111111
11111111
11111111
11111111
11111111
11111111
11111111
```



---

---
title: "A+B Again?"
layout: "post"
diff: 入门
pid: CF1999A
tag: ['模拟']
---

# A+B Again?

## 题目描述

Given a two-digit positive integer $ n $ , find the sum of its digits.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 90 $ ) — the number of test cases.

The only line of each test case contains a single two-digit positive integer $ n $ ( $ 10 \leq n \leq 99 $ ).

## 输出格式

For each test case, output a single integer — the sum of the digits of $ n $ .

## 样例 #1

### 输入

```
8
77
21
40
34
19
84
10
99
```

### 输出

```
14
3
4
7
10
12
1
18
```



---

---
title: "Card Game"
layout: "post"
diff: 入门
pid: CF1999B
tag: ['模拟']
---

# Card Game

## 题目描述

Suneet and Slavic play a card game. The rules of the game are as follows:

- Each card has an integer value between $ 1 $ and $ 10 $ .
- Each player receives $ 2 $ cards which are face-down (so a player doesn't know their cards).
- The game is turn-based and consists exactly of two turns. In a round, both players pick a random unflipped card and flip it. The player who flipped a card with a strictly greater number wins the round. In case of equality, no one wins the round.
- A player wins a game if he wins the most number of rounds (i.e. strictly greater than the other player). In case of equality, no one wins the game.

Since Suneet and Slavic aren't best friends, you need to calculate the number of ways the game could happen that Suneet would end up as the winner.

For a better understanding, please check the notes section.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first and only line of each test case contains $ 4 $ integers $ a_1 $ , $ a_2 $ , $ b_1 $ , $ b_2 $ ( $ 1 \leq a_1, a_2, b_1, b_2 \leq 10 $ ) where $ a_1 $ and $ a_2 $ represent the cards Suneet has, and $ b_1 $ and $ b_2 $ represent the cards Slavic has, respectively.

## 输出格式

For each test case, output a single integer — the number of games Suneet would win considering all possible games.

## 说明/提示

Consider the first test case when Slavic starts with the cards that have the values $ 2 $ and $ 6 $ , and Suneet starts with cards that have the values $ 3 $ and $ 8 $ . The game could happen in $ 4 $ different ways:

- Suneet flips $ 3 $ and Slavic flips $ 2 $ . Suneet wins the first round. Then, Suneet flips $ 8 $ and Slavic flips $ 6 $ . Suneet wins the second round as well. Since Suneet won $ 2 $ rounds, he wins the game.
- Suneet flips $ 3 $ and Slavic flips $ 6 $ . Slavic wins the first round. Then, Suneet flips $ 8 $ and Slavic flips $ 2 $ . Suneet wins the second round. Nobody wins since both players won an equal amount of rounds.
- Suneet flips $ 8 $ and Slavic flips $ 6 $ . Suneet wins the first round. Then, Suneet flips $ 3 $ and Slavic flips $ 2 $ . Suneet wins the second round as well. Since Suneet won $ 2 $ rounds, he wins the game.
- Suneet flips $ 8 $ and Slavic flips $ 2 $ . Suneet wins the first round. Then, Suneet flips $ 3 $ and Slavic flips $ 6 $ . Slavic wins the round. Nobody wins since both players won an equal amount of rounds.

## 样例 #1

### 输入

```
5
3 8 2 6
1 1 1 1
10 10 2 2
1 1 10 10
3 8 7 2
```

### 输出

```
2
0
4
0
2
```



---

---
title: "Primary Task"
layout: "post"
diff: 入门
pid: CF2000A
tag: ['模拟']
---

# Primary Task

## 题目描述

有 $t$ 个整数，要求这 $t$ 个整数写成 $\test{10^x}$ ($x\ge2$) 的形式，但由于 '$\test{^}$' 出现问题，所以将 '$\test{^}$' 省略。例如 $10^5$ 会变成 $105$，$10^{19}$ 会变成 $1019$，现在要求每个整数是否满足要求。

## 输入格式

第一行一个整数 $t$ ($1 \le t \le 10^4$)，表示有 $t$ 个整数。

接下来的 $t$ 行每行一个整数 $a$ ($1 \le a \le 10000$)，表示每一个整数。

## 输出格式

对于每个整数，输出 `YES` 或 `NO`，表示是否满足要求。

注意：答案不要求严格按照大小写输出。例如  `yEs`，`yes`，`Yes` 都将视作 `Yes`。

## 样例 #1

### 输入

```
7
100
1010
101
105
2033
1019
1002
```

### 输出

```
NO
YES
NO
YES
NO
YES
NO
```



---

---
title: "Seating in a Bus"
layout: "post"
diff: 入门
pid: CF2000B
tag: ['模拟']
---

# Seating in a Bus

## 题目描述

有 $n$ 个数，编号分别为 $1$ 到 $n$。必须按以下规则来标记这些数：

- 若没有数被标记，则被标记的数可以是任何从 $1$ 到 $n$ 的数。
- 否则，被标记的数至少有一个与它相邻的数被标记。具体的，如果要标记编号 $i$，则编号 $i-1$ 和 $i+1$ 至少有一个被标记。

现在，这 $n$ 个数都要被标记，用数组 $a$ 来表示依次要标记那些数。具体的，$a_1$ 表示第一个要标记的数，$a_2$ 表示第二个要标记的数，依次类推。

你已经知道了 $a$ 数组的内容，要求是否满足规则。

例如 $n=5$，且 $a$ = [$5，4，2，1，3$]，则不满足要求，因为 $a_3$ 中被标记的数是 $2$，而编号 $1$ 和 $3$ 却都没有被标记。

## 输入格式

第一行一个整数 $t$（$1 \le t \le 10^4$），表示有 $t$ 组数据。

每一组第一行一个整数 $n$（$1 \le n \le 2 \cdot 10^5$），表示有 $n$ 个数。

每一组第二行有 $n$ 个不同的整数表示 $a_i$，表示第 $i$ 个被标记的数。

保证所有 $n$ 的总和不超过 $2 \cdot 10^5$，并且没有数再次标记已经标记过的数。

## 输出格式

对于每组数据输出 `YES` 或 `NO`，表示是否符合规则。

注意：答案不要求严格按照大小写输出。例如  `yEs`，`yes`，`Yes` 都将视作 `Yes`。

本题为 [@hanciyang](https://www.luogu.com.cn/user/927003) 翻译。

## 样例 #1

### 输入

```
4
5
5 4 2 1 3
3
2 3 1
4
2 3 1 4
5
1 2 3 5 4
```

### 输出

```
NO
YES
YES
NO
```



---

---
title: "Minimize!"
layout: "post"
diff: 入门
pid: CF2009A
tag: ['模拟']
---

# Minimize!

## 题目描述

给你两个整数 $a$ 和 $b$ ($a≤b$) 。
在 $c$ ($a≤c≤b$) 的所有可能整数值中，求 $(c−a)+(b−c)$ 的最小值。

## 输入格式

第一行包含 $t$ ($1≤t≤55$) -测试用例数。
每个测试用例包含两个整数 $a$ 和 $b$ ($1≤a≤b≤10$) 。

## 输出格式

对于每个测试用例，另起一行输出 $(c−a)+(b−c)$ 的最小可能值。

## 样例 #1

### 输入

```
3
1 2
3 10
5 5
```

### 输出

```
1
7
0
```



---

---
title: "osu!mania"
layout: "post"
diff: 入门
pid: CF2009B
tag: ['模拟']
---

# osu!mania

## 题目描述

You are playing your favorite rhythm game, osu!mania. The layout of your beatmap consists of $ n $ rows and $ 4 $ columns. Because notes at the bottom are closer, you will process the bottommost row first and the topmost row last. Each row will contain exactly one note, represented as a '#'.

For each note $ 1, 2, \dots, n $ , in the order of processing, output the column in which the note appears.

## 输入格式

The first line contains $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases.

For each test case, the first line contains $ n $ ( $ 1 \leq n \leq 500 $ ) — the number of rows of the beatmap.

The following $ n $ lines contain $ 4 $ characters. The $ i $ -th line represents the $ i $ -th row of the beatmap from the top. It is guaranteed that the characters are either '.' or '#', and exactly one of the characters is '#'.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 500 $ .

## 输出格式

For each test case, output $ n $ integers on a new line, the column that the $ i $ -th note appears in for all $ i $ from $ 1 $ to $ n $ .

## 样例 #1

### 输入

```
3
4
#...
.#..
..#.
...#
2
.#..
.#..
1
...#
```

### 输出

```
4 3 2 1 
2 2 
4
```



---

---
title: "Alternating Sum of Numbers"
layout: "post"
diff: 入门
pid: CF2010A
tag: ['模拟']
---

# Alternating Sum of Numbers

## 输出格式

**数据范围：** $1 \le t \le 1000$，$1 \le n \le 50$，$1 \le a_i \le 100$。

## 样例 #1

### 输入

```
4
4
1 2 3 17
1
100
2
100 100
5
3 1 4 1 5
```

### 输出

```
-15
100
0
10
```



---

---
title: "Three Brothers"
layout: "post"
diff: 入门
pid: CF2010B
tag: ['模拟']
---

# Three Brothers

## 题目描述

### 题目翻译：

三兄弟相约见面。我们按以下顺序给他们编号：老大是 $1$ 号，老二是 $2$ 号，老三是 $3$ 号。

到了约定的时间，有一个兄弟迟到了。现在给出准时到达的两个兄弟的编号，你需要确定那个迟到的兄弟的编号。

## 输入格式

输入一行包含两个不同的整数 $a$ 和 $b$ （$1 \leq a, b \leq 3$，且 $a \neq b$），代表准时到达的两个兄弟的编号。编号顺序是任意的。

## 输出格式

输出一个整数，代表迟到的兄弟的编号。
```

## 样例 #1

### 输入

```
3 1
```

### 输出

```
2
```



---

---
title: "Message Transmission Error (easy version)"
layout: "post"
diff: 入门
pid: CF2010C1
tag: ['模拟', '字符串']
---

# Message Transmission Error (easy version)

## 题目描述

This is a simplified version of the problem. It differs from the difficult one only in its constraints.

At the Berland State University, the local network between servers does not always operate without errors. When transmitting two identical messages consecutively, an error may occur, resulting in the two messages merging into one. In this merging, the end of the first message coincides with the beginning of the second. Of course, the merging can only occur at identical characters. The length of the merging must be a positive number less than the length of the message text.

For example, when transmitting two messages "abrakadabra" consecutively, it is possible that it will be transmitted with the described type of error, resulting in a message like "abrakadabrabrakadabra" or "abrakadabrakadabra' (in the first case, the merging occurred at one character, and in the second case, at four).

Given the received message $ t $ , determine if it is possible that this is the result of an error of the described type in the operation of the local network, and if so, determine a possible value of $ s $ .

A situation where two messages completely overlap each other should not be considered an error. For example, if the received message is "abcd", it should be considered that there is no error in it. Similarly, simply appending one message after another is not a sign of an error. For instance, if the received message is "abcabc", it should also be considered that there is no error in it.

## 输入格式

The input consists of a single non-empty string $ t $ , consisting of lowercase letters of the Latin alphabet. The length of the string $ t $ does not exceed $ 100 $ characters.

## 输出格式

If the message $ t $ cannot contain an error, output "NO" (without quotes) in a single line of output.

Otherwise, in the first line, output "YES" (without quotes), and in the next line, output the string $ s $ — a possible message that could have led to the error. If there are multiple possible answers, any of them is acceptable.

## 说明/提示

In the second example, a suitable answer could also be the string "acacaca".

## 样例 #1

### 输入

```
abrakadabrabrakadabra
```

### 输出

```
YES
abrakadabra
```

## 样例 #2

### 输入

```
acacacaca
```

### 输出

```
YES
acaca
```

## 样例 #3

### 输入

```
abcabc
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
abababab
```

### 输出

```
YES
ababab
```

## 样例 #5

### 输入

```
tatbt
```

### 输出

```
NO
```



---

---
title: "Robin Helps"
layout: "post"
diff: 入门
pid: CF2014A
tag: ['模拟']
---

# Robin Helps

## 题目描述

There is a little bit of the outlaw in everyone, and a little bit of the hero too.



The heroic outlaw Robin Hood is famous for taking from the rich and giving to the poor.

Robin encounters $ n $ people starting from the $ 1 $ -st and ending with the $ n $ -th. The $ i $ -th person has $ a_i $ gold. If $ a_i \ge k $ , Robin will take all $ a_i $ gold, and if $ a_i=0 $ , Robin will give $ 1 $ gold if he has any. Robin starts with $ 0 $ gold.

Find out how many people Robin gives gold to.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1\leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ , $ k $ ( $ 1 \le n \le 50, 1 \le k \le 100 $ ) — the number of people and the threshold at which Robin Hood takes the gold.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 100 $ ) — the gold of each person.

## 输出格式

For each test case, output a single integer, the number of people that will get gold from Robin Hood.

## 说明/提示

In the first test case, Robin takes $ 2 $ gold from the first person and gives a gold to the second person.

In the second test case, Robin takes $ 3 $ gold and gives $ 1 $ gold to each of the next $ 2 $ people.

In the third test case, Robin takes $ 3 $ gold and so only gives gold to $ 3 $ other people.

## 样例 #1

### 输入

```
4
2 2
2 0
3 2
3 0 0
6 2
0 3 0 0 0 0
2 5
5 4
```

### 输出

```
1
2
3
0
```



---

---
title: "Alice's Adventures in "Chess""
layout: "post"
diff: 入门
pid: CF2028A
tag: ['模拟']
---

# Alice's Adventures in "Chess"

## 题目描述

爱丽丝正在乡下试图与红心皇后见面！此时，爱丽丝位于位置 $(0,0)$，而红心皇后位于位置 $(a,b)$。爱丽丝只能朝四个基本方向移动（北、东、南、西）。

更正式地说，如果爱丽丝在点 $(x,y)$，她将执行以下操作之一：

- 向北移动（用 $N$ 表示），移动到 $(x,y+1)$；
- 向东移动（用 $E$ 表示），移动到 $(x+1,y)$；
- 向南移动（用 S 表示），移动到 $(x,y-1)$；
- 向西移动（用 W 表示），移动到 $(x-1,y)$。

爱丽丝的移动是预先确定的。她有一个字符串 $s$，表示她从左到右执行的移动序列。一旦她到达序列的末尾，她将永远重复相同的移动模式。

你能帮助爱丽丝弄清楚她是否会与红心皇后相遇吗？

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$ $(1 \le t \le 500)$。测试用例的描述随后给出。

每个测试用例的第一行包含三个整数 $n,a,b$ $(1 \le n,a,b \le 10)$ — 字符串的长度和红心皇后的初始坐标。

第二行包含一个长度为 $n$ 的字符串 $s$，仅由字符 N、E、S 或 W 组成。

## 输出格式

对于每个测试用例，输出一个字符串 "YES" 或 "NO"（不带引号），表示爱丽丝是否最终会与红心皇后相遇。

你可以以任何大小写输出答案（大写或小写）。例如，字符串 "yEs"、"yes"、"Yes" 和 "YES" 都会被识别为肯定的回应。

## 说明/提示

在第一个测试用例中，爱丽丝沿着路径 $(0,0) \xrightarrow[\texttt{N}]{} (0,1) \xrightarrow[\texttt{E}]{} (1,1) \xrightarrow[\texttt{N}]{} (1,2) \xrightarrow[\texttt{E}]{} (2,2)$ 移动。

在第二个测试用例中，爱丽丝永远无法到达红心皇后。

## 样例 #1

### 输入

```
6
2 2 2
NE
3 2 2
NNE
6 2 1
NNEESW
6 10 10
NNEESW
3 4 2
NEE
4 5 5
NEWS
```

### 输出

```
YES
NO
YES
YES
YES
NO
```



---

---
title: "Sakurako and Kosuke"
layout: "post"
diff: 入门
pid: CF2033A
tag: ['模拟']
---

# Sakurako and Kosuke

## 题目描述

Sakurako 和 Kosuke 在数轴上用一个点玩游戏。这个点初始在数轴原点。二人轮流操作，Sakurako 先。

在第 $i$ 次移动，玩家将这个点向某个方向移动 $2 \times i - 1$ 个单位长度。Sakurako 向负方向移动点，而 Kosuke 向正方向。

设该点坐标为 $x$。

所以游戏开始后就会发生：
1. Sakurako 将点沿负方向移动 $1$ 个单位长度，此时 $x = -1$；
2. Kosuke 将点沿正方向移动 $3$ 个单位长度，此时 $x = 2$；
3. Sakurako 将点沿负方向移动 $5$ 个单位长度，此时 $x = -3$；
4. $\cdot \cdot \cdot$

直到 $|x| > n$ 时，他们才会停下。可以证明游戏一定会结束的。

定义赢家是在游戏结束前最后一个移动点的人。

你的任务是找到赢家。

## 输入格式

第一行一个正整数 $t$（$1 \le t \le 100$），表示 Sakurako 和 Kosuke 玩游戏的次数。

接下来的 $t$ 行，每行一个正整数 $n$（$1 \le n \le 100$），含义见上。

## 输出格式

总共 $t$ 行，每行输出每次游戏的赢家。

翻译人 [Rich1](https://www.luogu.com.cn/user/1069671)

## 样例 #1

### 输入

```
4
1
6
3
98
```

### 输出

```
Kosuke
Sakurako
Kosuke
Sakurako
```



---

---
title: "Quintomania"
layout: "post"
diff: 入门
pid: CF2036A
tag: ['模拟']
---

# Quintomania

## 题目描述

Boris Notkin composes melodies. He represents them as a sequence of notes, where each note is encoded as an integer from $ 0 $ to $ 127 $ inclusive. The interval between two notes $ a $ and $ b $ is equal to $ |a - b| $ semitones.

Boris considers a melody perfect if the interval between each two adjacent notes is either $ 5 $ semitones or $ 7 $ semitones.

After composing his latest melodies, he enthusiastically shows you his collection of works. Help Boris Notkin understand whether his melodies are perfect.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of melodies.

Each melody is described by two lines.

The first line contains an integer $ n $ ( $ 2 \leq n \leq 50 $ ) — the number of notes in the melody.

The second line contains $ n $ integers $ a_{1}, a_{2}, \dots, a_{n} $ ( $ 0 \leq a_{i} \leq 127 $ ) — the notes of the melody.

## 输出格式

For each melody, output "YES", if it is perfect; otherwise, output "NO".

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 样例 #1

### 输入

```
8
2
114 109
2
17 10
3
76 83 88
8
38 45 38 80 85 92 99 106
5
63 58 65 58 65
8
117 124 48 53 48 43 54 49
5
95 102 107 114 121
10
72 77 82 75 70 75 68 75 68 75
```

### 输出

```
YES
YES
YES
NO
YES
NO
YES
YES
```



---

---
title: "Twice"
layout: "post"
diff: 入门
pid: CF2037A
tag: ['模拟']
---

# Twice

## 题目描述

Kinich wakes up to the start of a new day. He turns on his phone, checks his mailbox, and finds a mysterious present. He decides to unbox the present.

Kinich unboxes an array $ a $ with $ n $ integers. Initially, Kinich's score is $ 0 $ . He will perform the following operation any number of times:

- Select two indices $ i $ and $ j $ $ (1 \leq i < j \leq n) $ such that neither $ i $ nor $ j $ has been chosen in any previous operation and $ a_i = a_j $ . Then, add $ 1 $ to his score.

Output the maximum score Kinich can achieve after performing the aforementioned operation any number of times.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 500 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 20 $ ) — the length of $ a $ .

The following line of each test case contains $ n $ space-separated integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq n $ ).

## 输出格式

For each test case, output the maximum score achievable on a new line.

## 说明/提示

In the first and third testcases, Kinich cannot perform any operations.

In the second testcase, Kinich can perform one operation with $ i=1 $ and $ j=2 $ .

In the fourth testcase, Kinich can perform one operation with $ i=1 $ and $ j=4 $ .

## 样例 #1

### 输入

```
5
1
1
2
2 2
2
1 2
4
1 2 3 1
6
1 2 3 1 2 3
```

### 输出

```
0
1
0
1
3
```



---

---
title: "Waiting for..."
layout: "post"
diff: 入门
pid: CF2038J
tag: ['模拟']
---

# Waiting for...

## 题目描述

Monocarp 正在车站等公共汽车。不幸的是，也有很多人想乘坐公共汽车。

你会得到两类事件的列表：

- B $b_i$  ：有 $b_i$ 个免费座位的巴士到达车站；
- P $p_i$  ： $p_i$ 人到站。

这些事件是按时间顺序列出的。

当公共汽车到达时，会发生以下情况。公车站的所有人（除了 Monocarp ）都试图上车。如果所有人都有足够的空位，他们就都上车。否则，有些人会留在公交车站（上车的人数等于免费座位的数量）。

如果在所有人（除了 Monocarp ）进入公共汽车后仍然至少有一个空闲座位，那么 Monocarp 可以决定也进入这辆公共汽车（但他可能选择等待另一辆公共汽车）。对于每一辆公共汽车，您必须确定 Monocarp 是否有可能乘坐该公共汽车。

## 输入格式

第一行包含一个整数 $n (1 \le n \le 10^3)$ —事件的数量。

然后是 $n$ 行。其中第 $i$ 行为以下两种格式之一：

- B $b_i ( 1 \le b_i \le 10^6 )$ -一辆有 $b_i$ 免费座位的巴士到达车站；
- P $p_i ( 1 \le p_i \le 10^6 )$ - $p_i$ 人到站。

输入的附加约束：至少有一个B类型的事件。

## 输出格式

对于类型B的每个事件，如果 Monocarp 可以乘坐该辆车，则输出 `YES`，否则输出 `NO` （不区分大小写）。

## 样例 #1

### 输入

```
10
P 2
P 5
B 8
P 14
B 5
B 9
B 3
P 2
B 1
B 2
```

### 输出

```
YES
NO
NO
YES
NO
YES
```



---

---
title: "Fixing the Expression"
layout: "post"
diff: 入门
pid: CF2038N
tag: ['模拟']
---

# Fixing the Expression

## 题目描述

一个表达式是由三个字符组成的字符串，其中第一个和最后一个字符是数字（从 $0$ 到 $9$ ），中间的字符是一个比较符号（$<$ 、$=$ 或 $>$ ）。

如果比较符号与数字相匹配，那么这个表达式就是成立的（例如，如果第一个数字严格小于最后一个数字，那么比较符号就应该是 $<$ ）。

例如，表达式 $1<3$ 、$4>2$ 、$0=0$ 是成立的，而 $5>5$ 、$7<3$ 则不成立。

给定一个字符串，它是一个表达式。尽可能少地改变字符，使变成一个成立的表达式。注意，如果已经是成立的，就应该保持原样。

## 输入格式

第一行包含一个整数 $t$（ $1\le t \le 300$ ）—— 测试用例的数量。

每个测试用例占一行，包含字符串 $s$（ $\vert s \vert = 3$ ，的第一个和最后一个字符是数字，第二个字符是比较符号）。

## 输出格式

对于每个测试用例，输出一个由 $3$ 个字符组成的字符串 —— 通过尽可能少地改变中的字符而得到的一个成立的表达式。如果有多个答案，输出其中任意一个即可。

translated by @[jgysb](https://www.luogu.com.cn/user/543559)

## 样例 #1

### 输入

```
5
3&lt;7
3&gt;7
8=9
0=0
5&lt;3
```

### 输出

```
5
3<7
3>7
8=9
0=0
5<3
```



---

---
title: "The Bento Box Adventure"
layout: "post"
diff: 入门
pid: CF2041A
tag: ['模拟']
---

# The Bento Box Adventure

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2041A/6724e41fa1b725d06db3c22a7057ae0e507a6d98.png) Image generated by ChatGPT 4o.Boxed meals in Taiwan are very common, offering convenient and affordable nutrition-balanced choices for students and office workers. These meals typically include a variety of vegetables, protein, and rice, providing a well-rounded diet. With numerous options available at local self-service restaurants, they are a popular choice for those looking for a quick, healthy lunch.

There are five Taiwanese self-service restaurants numbered from 1 to 5. You plan to visit a different restaurant each day from Monday to Friday to pack a boxed meal for lunch. You've already visited one restaurant from Monday to Thursday, each time visiting a different one. Now, it's Friday, and you want to visit the last remaining restaurant that you haven't been to yet this week.

Write a program that takes as input the four restaurants you've already visited (one for each day from Monday to Thursday) and outputs the restaurant you should visit on Friday.

## 输入格式

A single line of input containing four integers $ a, b, c, d $ , each between 1 and 5 (inclusive), representing the restaurant numbers you visited from Monday to Thursday, in order.

- $ 1\le a, b, c, d\le 5 $
- All four numbers will be different.

## 输出格式

Output the restaurant number you should visit on Friday.

## 样例 #1

### 输入

```
1 3 2 5
```

### 输出

```
4
```

## 样例 #2

### 输入

```
2 5 4 3
```

### 输出

```
1
```



---

---
title: "Easy Problem"
layout: "post"
diff: 入门
pid: CF2044A
tag: ['模拟']
---

# Easy Problem

## 题目描述

给定一个整数 $n$ 求有多少对二元组 $(a,b)$ 满足 $ a = n - b$

## 输入格式

第一行输入一个整数 $t$ $(1 \le t \le 99)$，表示数据组数  
接下来第二行到第 $(t+1)$ 行，每行一个整数 $n$ $(1 \le n \le 100)$。

## 输出格式

共 $t$ 行，每行一个整数表示有多少个符合条件的二元组

## 样例 #1

### 输入

```
3
2
4
6
```

### 输出

```
1
3
5
```



---

---
title: "Normal Problem"
layout: "post"
diff: 入门
pid: CF2044B
tag: ['模拟']
---

# Normal Problem

## 题目描述

玻璃上写着一串仅包含小写字母 $p$，$q$，$w$ 的字符串 $a$。求该玻璃水平翻转之后，从左到右看到的新字符串 $b$。

## 输入格式

第一行输入一个整数 $t$ $(1≤t≤100)$ ——测试数据的组数。

对于每一组测试数据，输入一行字符串 $a$ ——玻璃正面所看到的字符串。保证 $a$ 只包含小写字母 $p$，$q$，$w$。

## 输出格式

对于每一组测试数据，输出一行字符串$b$ ——该玻璃水平翻转之后所看到的字。

Translated by [zhoujy1209](https://www.luogu.com.cn/user/946085)

## 样例 #1

### 输入

```
5
qwq
ppppp
pppwwwqqq
wqpqwpqwwqp
pqpqpqpq
```

### 输出

```
pwp
qqqqq
pppwwwqqq
qpwwpqwpqpw
pqpqpqpq
```



---

---
title: "Line Breaks"
layout: "post"
diff: 入门
pid: CF2050A
tag: ['模拟']
---

# Line Breaks

## 题目描述

Kostya has a text $ s $ consisting of $ n $ words made up of Latin alphabet letters. He also has two strips on which he must write the text. The first strip can hold $ m $ characters, while the second can hold as many as needed.

Kostya must choose a number $ x $ and write the first $ x $ words from $ s $ on the first strip, while all the remaining words are written on the second strip. To save space, the words are written without gaps, but each word must be entirely on one strip.

Since space on the second strip is very valuable, Kostya asks you to choose the maximum possible number $ x $ such that all words $ s_1, s_2, \dots, s_x $ fit on the first strip of length $ m $ .

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n \le 50 $ ; $ 1 \le m \le 500 $ ) — the number of words in the list and the maximum number of characters that can be on the first strip.

The next $ n $ lines contain one word $ s_i $ of lowercase Latin letters, where the length of $ s_i $ does not exceed $ 10 $ .

## 输出格式

For each test case, output the maximum number of words $ x $ such that the first $ x $ words have a total length of no more than $ m $ .

## 样例 #1

### 输入

```
5
3 1
a
b
c
2 9
alpha
beta
4 12
hello
world
and
codeforces
3 2
ab
c
d
3 2
abc
ab
a
```

### 输出

```
1
2
2
1
0
```



---

---
title: "Olympiad Date"
layout: "post"
diff: 入门
pid: CF2091A
tag: ['模拟', '字符串']
---

# Olympiad Date

## 题目描述

第一届 IT Campus "NEIMARK" 奥林匹克的决赛定于 2025 年 3 月 1 日举行。一位无名实习生被要求用数字组成奥林匹克的日期——01.03.2025。

为了完成这个任务，实习生拿了一大袋数字并开始逐个抽取。他一共抽取了 $n$ 个数字——在第 $i$ 次抽取时抽到了数字 $a_i$。

你怀疑实习生做了多余的工作。请确定实习生在第几步时首次能够用已抽取的数字组成奥林匹克的日期（分隔的点可以忽略），或者报告无法用这些数字组成该日期。注意前导零必须显示。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $t$ ($1 \leq t \leq 10^4$)。接下来是每个测试用例的描述。

每个测试用例的第一行包含一个整数 $n$ ($1 \le n \le 20$)。

每个测试用例的第二行包含 $n$ 个整数 $a_i$ ($0 \leq a_i \leq 9$)——实习生按时间顺序抽取的数字。

## 输出格式

对于每个测试用例，输出实习生可能抽取的最小数字数量（即最早满足条件的步数）。如果所有数字都无法组成日期，则输出数字 $0$。

## 说明/提示

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
10
2 0 1 2 3 2 5 0 0 1
8
2 0 1 2 3 2 5 0
8
2 0 1 0 3 2 5 0
16
2 3 1 2 3 0 1 9 2 1 0 3 5 4 0 3
```

### 输出

```
9
0
8
15
```



---

---
title: "BerOS file system"
layout: "post"
diff: 入门
pid: CF20A
tag: ['模拟', '字符串']
---

# BerOS file system

## 题目描述

新的操作系统BerOS有一个很好的特性。可以在路径中使用任意数量的字符“/”作为分隔符，而不是使用一个传统的“/”。例如，字符串`//usr///local//nginx/sbin//`和`/usr/local/nginx///sbin//`是等效的。只有根目录的路径可以表示为单个字符“/”，才需要路径末尾的字符“/”（或此类字符的某些序列）。
如果路径包含尽可能少的字符数“/”，则称为normalized的路径。

您的任务是将给定路径转换为规范化形式。

## 输入格式

一行，仅包含小写字母和`/`的字符串，保证路径至少含有一个`/`，不超过 $100$ 个字符。

## 输出格式

一行，一个字符串，表示简化后的路径。

## 样例 #1

### 输入

```
//usr///local//nginx/sbin

```

### 输出

```
/usr/local/nginx/sbin

```



---

---
title: "Team"
layout: "post"
diff: 入门
pid: CF231A
tag: ['模拟', '概率论']
---

# Team

## 题目描述

## 题目要求
三位选手要去参加编程竞赛，比赛共有N道题目，他们商定: 对于每一道题目，只有两位及以上的选手确认找到解法时才做。
试问，他们一共能做多少题?

## 输入格式

第一行一个整数N，表示题目的数量。
第二行到第N+1行，每行三个整数(0或者1)，其中0表示这位选手无法解出此题，1表示这位选手想到了解法。

## 输出格式

一行，一个整数，表示他们所能做的题目的数量。

感谢@PC_DOS 提供翻译

## 样例 #1

### 输入

```
3
1 1 0
1 1 1
1 0 0

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2
1 0 0
0 1 1

```

### 输出

```
1

```



---

---
title: "Boy or Girl"
layout: "post"
diff: 入门
pid: CF236A
tag: ['模拟', '字符串']
---

# Boy or Girl

## 题目描述

Those days, many boys use beautiful girls' photos as avatars in forums. So it is pretty hard to tell the gender of a user at the first glance. Last year, our hero went to a forum and had a nice chat with a beauty (he thought so). After that they talked very often and eventually they became a couple in the network.

But yesterday, he came to see "her" in the real world and found out "she" is actually a very strong man! Our hero is very sad and he is too tired to love again now. So he came up with a way to recognize users' genders by their user names.

This is his method: if the number of distinct characters in one's user name is odd, then he is a male, otherwise she is a female. You are given the string that denotes the user name, please help our hero to determine the gender of this user by his method.

## 输入格式

The first line contains a non-empty string, that contains only lowercase English letters — the user name. This string contains at most 100 letters.

## 输出格式

If it is a female by our hero's method, print "CHAT WITH HER!" (without the quotes), otherwise, print "IGNORE HIM!" (without the quotes).

## 说明/提示

For the first example. There are 6 distinct characters in "wjmzbmr". These characters are: "w", "j", "m", "z", "b", "r". So wjmzbmr is a female and you should print "CHAT WITH HER!".

## 样例 #1

### 输入

```
wjmzbmr

```

### 输出

```
CHAT WITH HER!

```

## 样例 #2

### 输入

```
xiaodao

```

### 输出

```
IGNORE HIM!

```

## 样例 #3

### 输入

```
sevenkplus

```

### 输出

```
CHAT WITH HER!

```



---

---
title: "System Administrator"
layout: "post"
diff: 入门
pid: CF245A
tag: ['模拟']
---

# System Administrator

## 题目描述

Polycarpus是系统管理员。在他的严格指导下有两台服务器——a和b。为了了解服务器的性能，Polycarpus执行命令“ping a”和“ping b”。每个ping命令都会向命令参数中指定的服务器发送10个数据包。执行程序会产生两个整数x$ 和 y（x+y=10；x，y>=0）。这些数字意味着 x 包通过网络成功地到达了相应的服务器，y 包丢失了，今天 Polycarpus 在工作日执行了n个ping命令。现在，对于每个服务器，Polycarpus都想知道服务器是否“活动”。Polycarpus认为服务器是“活动的”，如果我们发送到该服务器的数据包中至少有一半是通过网络成功到达的。帮助Polycarpus，根据给定的命令及其结果来确定每个服务器是否“活动”。

## 输入格式

第一行输入一个正整数 n ，表示命令总数。

接下来 n 行输入3个正整数 ti,xi,yi, 分别表示发送到哪个服务器（ti=1表示发送至a服务器，ti=2表示发送至b服务器），发送成功的数量和发送失败的数量。

## 输出格式

输出共n行，每行输出一个字符串，表示服务器是否活动，LIVE表示活动，DEAD表示没有活动

## 样例 #1

### 输入

```
2
1 5 5
2 6 4

```

### 输出

```
LIVE
LIVE

```

## 样例 #2

### 输入

```
3
1 0 10
2 0 10
1 10 0

```

### 输出

```
LIVE
DEAD

```



---

---
title: "Phone numbers"
layout: "post"
diff: 入门
pid: CF25B
tag: ['模拟', '字符串']
---

# Phone numbers

## 题目描述

Phone number in Berland is a sequence of $ n $ digits. Often, to make it easier to memorize the number, it is divided into groups of two or three digits. For example, the phone number 1198733 is easier to remember as 11-987-33. Your task is to find for a given phone number any of its divisions into groups of two or three digits.

## 输入格式

The first line contains integer $ n $ ( $ 2<=n<=100 $ ) — amount of digits in the phone number. The second line contains $ n $ digits — the phone number to divide into groups.

## 输出格式

Output any of divisions of the given phone number into groups of two or three digits. Separate groups by single character -. If the answer is not unique, output any.

## 样例 #1

### 输入

```
6
549871

```

### 输出

```
54-98-71
```

## 样例 #2

### 输入

```
7
1198733

```

### 输出

```
11-987-33

```



---

---
title: "Colorful Stones (Simplified Edition)"
layout: "post"
diff: 入门
pid: CF265A
tag: ['模拟', '字符串']
---

# Colorful Stones (Simplified Edition)

## 题目描述

There is a sequence of colorful stones. The color of each stone is one of red, green, or blue. You are given a string $ s $ . The $ i $ -th (1-based) character of $ s $ represents the color of the $ i $ -th stone. If the character is "R", "G", or "B", the color of the corresponding stone is red, green, or blue, respectively.

Initially Squirrel Liss is standing on the first stone. You perform instructions one or more times.

Each instruction is one of the three types: "RED", "GREEN", or "BLUE". After an instruction $ c $ , if Liss is standing on a stone whose colors is $ c $ , Liss will move one stone forward, else she will not move.

You are given a string $ t $ . The number of instructions is equal to the length of $ t $ , and the $ i $ -th character of $ t $ represents the $ i $ -th instruction.

Calculate the final position of Liss (the number of the stone she is going to stand on in the end) after performing all the instructions, and print its 1-based position. It is guaranteed that Liss don't move out of the sequence.

## 输入格式

The input contains two lines. The first line contains the string $ s $ ( $ 1<=|s|<=50 $ ). The second line contains the string $ t $ ( $ 1<=|t|<=50 $ ). The characters of each string will be one of "R", "G", or "B". It is guaranteed that Liss don't move out of the sequence.

## 输出格式

Print the final 1-based position of Liss in a single line.

## 样例 #1

### 输入

```
RGB
RRR

```

### 输出

```
2

```

## 样例 #2

### 输入

```
RRRBGBRBBB
BBBRR

```

### 输出

```
3

```

## 样例 #3

### 输入

```
BRRBGBRGRBGRGRRGGBGBGBRGBRGRGGGRBRRRBRBBBGRRRGGBBB
BBRBGGRGRGBBBRBGRBRBBBBRBRRRBGBBGBBRRBBGGRBRRBRGRB

```

### 输出

```
15

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
title: "Bit++"
layout: "post"
diff: 入门
pid: CF282A
tag: ['模拟', '字符串']
---

# Bit++

## 题目描述

The classic programming language of Bitland is Bit++. This language is so peculiar and complicated.

The language is that peculiar as it has exactly one variable, called $ x $ . Also, there are two operations:

- Operation ++ increases the value of variable $ x $ by 1.
- Operation -- decreases the value of variable $ x $ by 1.

A statement in language Bit++ is a sequence, consisting of exactly one operation and one variable $ x $ . The statement is written without spaces, that is, it can only contain characters "+", "-", "X". Executing a statement means applying the operation it contains.

A programme in Bit++ is a sequence of statements, each of them needs to be executed. Executing a programme means executing all the statements it contains.

You're given a programme in language Bit++. The initial value of $ x $ is $ 0 $ . Execute the programme and find its final value (the value of the variable when this programme is executed).

## 输入格式

The first line contains a single integer $ n $ $ (1<=n<=150) $ — the number of statements in the programme.

Next $ n $ lines contain a statement each. Each statement contains exactly one operation (++ or --) and exactly one variable $ x $ (denoted as letter «X»). Thus, there are no empty statements. The operation and the variable can be written in any order.

## 输出格式

Print a single integer — the final value of $ x $ .

## 样例 #1

### 输入

```
1
++X

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2
X++
--X

```

### 输出

```
0

```



---

---
title: "Shaass and Oskols"
layout: "post"
diff: 入门
pid: CF294A
tag: ['模拟']
---

# Shaass and Oskols

## 题目描述

Shaass要打一些鸟。

有 $n$ 根水平电线彼此平行排列，电线从顶到底编号为 $1$ 到 $n$ ，每根电线上都有一些鸟彼此相邻，第 $i$ 根电线上有 $a_i$ 只鸟。

如果Shaass击中其中的一只鸟（假设这只鸟在第 $i$ 条电线上），在它左侧的鸟会跳向电线 $i$-1，在它右侧的鸟会跳向电线 $i$+1 ,如果没有这样的电线，它们就会飞走。

Shaass打了 $m$ 只鸟，告诉你每条电线上初始时鸟的个数，你的任务是计算出 $m$ 次射击后每根电线上有多少只鸟。

## 输入格式

第一行一个整数 $n$, (1<=$n$<=100)，接下来一行 $n$ 个整数$a_1,a_2,a_3...a_n$ (0<=$a_i$<=100）.

第三行一个整数 $m$（0<=$m$<=100)，接下来 $m$ 行每行包含两个整数 $x_i$ 和 $y_i$ ，意味着Shaass射击在电线 $x_i$ 的第 $y_i$ 只（左起）鸟，（1<=$x_i$<=$n$, 1<=$y_i$）。保证在那一时刻电线 $x_i$ 上至少会有 $y_i$ 只鸟。

## 输出格式

在第 $i$ 行打印第 $i$ 根电线上鸟的数量。

## 样例 #1

### 输入

```
5
10 10 10 10 10
5
2 5
3 13
2 12
1 13
4 6

```

### 输出

```
0
12
5
0
16

```

## 样例 #2

### 输入

```
3
2 4 1
1
2 2

```

### 输出

```
3
0
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
title: "Even Odds"
layout: "post"
diff: 入门
pid: CF318A
tag: ['模拟', '进制', '位运算']
---

# Even Odds

## 题目描述

## 题目大意

作为一个不顺从的人， $Volodya$  不喜欢当前的事物状态，特别是自然数的顺序（自然数是正整数）。他决心重新安排他们。但是自然数太多，所以 $Volodya$ 决定从 $n$ 开始。他写出下面的数列：首先是从1到 $n$ 的所有奇数整数（以升序排列），然后从1到 $n$ 的所有偶数整数（也按升序排列）。帮助我们的英雄找出：第 $k$ 个数字是多少

## 输入格式

输入一行包含整数n和k（1 <＝k<＝n<＝10^12）

请不要使用%lld说明符来读取或写入C++中的64位整数。最好使用cin、cut流或%I64d说明符。

翻译提供者：蒟蒻烟雨平生

## 样例 #1

### 输入

```
10 3

```

### 输出

```
5
```

## 样例 #2

### 输入

```
7 7

```

### 输出

```
6
```



---

---
title: "Borze"
layout: "post"
diff: 入门
pid: CF32B
tag: ['模拟', '字符串']
---

# Borze

## 题目描述

### 题面描述

三进制数字符号在Berland很受欢迎。如果用borze编码表示电报的三进制数。数字 $0,1,2$ 分别被作为`.`，`-.`和`--`。你需要为borze编码解码。（把borze编码转换为三进制数）。

## 输入格式

第一行包含在Borze编码。字符串的长度介于 $1$ 到 $200$ 个字符之间。这是保证给定的字符串是一个有效的一些三元数borze编码（这个数可能有前导零）。

## 输出格式

一个三进制数（如果有前导零要输出）。

## 样例 #1

### 输入

```
.-.--

```

### 输出

```
012
```

## 样例 #2

### 输入

```
--.

```

### 输出

```
20
```

## 样例 #3

### 输入

```
-..-.--

```

### 输出

```
1012
```



---

---
title: "Magnets"
layout: "post"
diff: 入门
pid: CF344A
tag: ['模拟', '概率论']
---

# Magnets

## 题目描述

Mad scientist Mike entertains himself by arranging rows of dominoes. He doesn't need dominoes, though: he uses rectangular magnets instead. Each magnet has two poles, positive (a "plus") and negative (a "minus"). If two magnets are put together at a close distance, then the like poles will repel each other and the opposite poles will attract each other.

Mike starts by laying one magnet horizontally on the table. During each following step Mike adds one more magnet horizontally to the right end of the row. Depending on how Mike puts the magnet on the table, it is either attracted to the previous one (forming a group of multiple magnets linked together) or repelled by it (then Mike lays this magnet at some distance to the right from the previous one). We assume that a sole magnet not linked to others forms a group of its own.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF344A/5ad7b55de90b4c95ae686ce6e02cbb9c5dff4d4e.png)Mike arranged multiple magnets in a row. Determine the number of groups that the magnets formed.

## 输入格式

The first line of the input contains an integer $ n $ ( $ 1<=n<=100000 $ ) — the number of magnets. Then $ n $ lines follow. The $ i $ -th line ( $ 1<=i<=n $ ) contains either characters "01", if Mike put the $ i $ -th magnet in the "plus-minus" position, or characters "10", if Mike put the magnet in the "minus-plus" position.

## 输出格式

On the single line of the output print the number of groups of magnets.

## 说明/提示

The first testcase corresponds to the figure. The testcase has three groups consisting of three, one and two magnets.

The second testcase has two groups, each consisting of two magnets.

## 样例 #1

### 输入

```
6
10
10
10
01
10
10

```

### 输出

```
3

```

## 样例 #2

### 输入

```
4
01
01
10
10

```

### 输出

```
2

```



---

---
title: "Extra-terrestrial Intelligence"
layout: "post"
diff: 入门
pid: CF36A
tag: ['模拟', '字符串']
---

# Extra-terrestrial Intelligence

## 题目背景

注意这题要加上这个：

```
freopen("input.txt","r",stdin);
freopen("output.txt","w",stdout);
```

## 题目描述

Recently Vasya got interested in finding extra-terrestrial intelligence. He made a simple extra-terrestrial signals’ receiver and was keeping a record of the signals for $ n $ days in a row. Each of those $ n $ days Vasya wrote a 1 in his notebook if he had received a signal that day and a 0 if he hadn’t. Vasya thinks that he has found extra-terrestrial intelligence if there is a system in the way the signals has been received, i.e. if all the intervals between successive signals are equal. Otherwise, Vasya thinks that the signals were sent by some stupid aliens no one cares about. Help Vasya to deduce from the information given by the receiver if he has found extra-terrestrial intelligence or not.

## 输入格式

The first line contains integer $ n $ ( $ 3<=n<=100 $ ) — amount of days during which Vasya checked if there were any signals. The second line contains $ n $ characters 1 or 0 — the record Vasya kept each of those $ n $ days. It’s guaranteed that the given record sequence contains at least three 1s.

## 输出格式

If Vasya has found extra-terrestrial intelligence, output YES, otherwise output NO.

## 样例 #1

### 输入

```
8
00111000

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
7
1001011

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
7
1010100

```

### 输出

```
YES

```



---

---
title: "Translation"
layout: "post"
diff: 入门
pid: CF41A
tag: ['模拟', '字符串']
---

# Translation

## 题目描述

### 题面描述

Berland 和 Birland 两地均有各自的语言，Berlandish 和 Birlandish。V 是一个翻译员，负责将 Berlandish 翻译成 Birlandish。将 Berlandish 翻译成 Birlandish 其实非常简单，只需把这个单词倒过来。比如单词`code`翻译过来就是`edoc`。但是粗心的 V 还是会犯一些错误。现在请你帮她判断一下他翻译的是否正确。

## 输入格式

两行，分别是一个 Berlandish 单词和 V 翻译的 Birlandish 单词。单词中所有字母均为小写拉丁字母（其实就是英文字母）;单词长度均不超过 $100$ 字符，单词中不包含任何多余空格。

## 输出格式

一行，如果 V 的翻译是正确的，输出`YES`。否则输出`NO`。

## 样例 #1

### 输入

```
code
edoc

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
abb
aba

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
code
code

```

### 输出

```
NO

```



---

---
title: "Football"
layout: "post"
diff: 入门
pid: CF43A
tag: ['模拟', '字符串']
---

# Football

## 题目描述

One day Vasya decided to have a look at the results of Berland 1910 Football Championship’s finals. Unfortunately he didn't find the overall score of the match; however, he got hold of a profound description of the match's process. On the whole there are $ n $ lines in that description each of which described one goal. Every goal was marked with the name of the team that had scored it. Help Vasya, learn the name of the team that won the finals. It is guaranteed that the match did not end in a tie.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=100 $ ) — the number of lines in the description. Then follow $ n $ lines — for each goal the names of the teams that scored it. The names are non-empty lines consisting of uppercase Latin letters whose lengths do not exceed 10 symbols. It is guaranteed that the match did not end in a tie and the description contains no more than two different teams.

## 输出格式

Print the name of the winning team. We remind you that in football the team that scores more goals is considered the winner.

## 样例 #1

### 输入

```
1
ABC

```

### 输出

```
ABC

```

## 样例 #2

### 输入

```
5
A
ABA
ABA
A
A

```

### 输出

```
A

```



---

---
title: "Letter"
layout: "post"
diff: 入门
pid: CF43B
tag: ['模拟', '字符串', '概率论']
---

# Letter

## 题目描述

### 题面描述

Vasya 决定利用报纸上的一段文字写一封匿名信。他可以从报纸上剪下一段文字（或字母），把他们粘贴到匿名信上去。已经剪下的文字不可重复使用。当然，匿名信中的空格不需要剪——他只要在空格处作出标记即可。现在，他知道报纸上的文字 $s1$ 和他即将写下的匿名信的内容 $s2$，请你帮他看看，他能否完成匿名信的书写。

## 输入格式

两行，分别是 $s1$ 和 $s2$（无空行），长度不超过 $200$，英文字母区分大小写，信中空格不作处理。

## 输出格式

写的出来就输出`YES`，否则输出`NO`。

## 样例 #1

### 输入

```
Instead of dogging Your footsteps it disappears but you dont notice anything
where is your dog

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
Instead of dogging Your footsteps it disappears but you dont notice anything
Your dog is upstears

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
Instead of dogging your footsteps it disappears but you dont notice anything
Your dog is upstears

```

### 输出

```
NO

```

## 样例 #4

### 输入

```
abcdefg hijk
k j i h g f e d c b a

```

### 输出

```
YES

```



---

---
title: "Little Pony and Crystal Mine"
layout: "post"
diff: 入门
pid: CF454A
tag: ['模拟', '字符串']
---

# Little Pony and Crystal Mine

## 题目描述

Twilight Sparkle once got a crystal from the Crystal Mine. A crystal of size $ n $ ( $ n $ is odd; $ n>1 $ ) is an $ n×n $ matrix with a diamond inscribed into it.

You are given an odd integer $ n $ . You need to draw a crystal of size $ n $ . The diamond cells of the matrix should be represented by character "D". All other cells of the matrix should be represented by character "\*". Look at the examples to understand what you need to draw.

## 输入格式

The only line contains an integer $ n $ ( $ 3<=n<=101 $ ; $ n $ is odd).

## 输出格式

Output a crystal of size $ n $ .

## 样例 #1

### 输入

```
3

```

### 输出

```
*D*
DDD
*D*

```

## 样例 #2

### 输入

```
5

```

### 输出

```
**D**
*DDD*
DDDDD
*DDD*
**D**

```

## 样例 #3

### 输入

```
7

```

### 输出

```
***D***
**DDD**
*DDDDD*
DDDDDDD
*DDDDD*
**DDD**
***D***

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
title: "Sleuth"
layout: "post"
diff: 入门
pid: CF49A
tag: ['模拟', '字符串']
---

# Sleuth

## 题目描述

Vasya plays the sleuth with his friends. The rules of the game are as follows: those who play for the first time, that is Vasya is the sleuth, he should investigate a "crime" and find out what is happening. He can ask any questions whatsoever that can be answered with "Yes" or "No". All the rest agree beforehand to answer the questions like that: if the question’s last letter is a vowel, they answer "Yes" and if the last letter is a consonant, they answer "No". Of course, the sleuth knows nothing about it and his task is to understand that.

Unfortunately, Vasya is not very smart. After 5 hours of endless stupid questions everybody except Vasya got bored. That’s why Vasya’s friends ask you to write a program that would give answers instead of them.

The English alphabet vowels are: A, E, I, O, U, Y

The English alphabet consonants are: B, C, D, F, G, H, J, K, L, M, N, P, Q, R, S, T, V, W, X, Z



## 输入格式

The single line contains a question represented by a non-empty line consisting of large and small Latin letters, spaces and a question mark. The line length does not exceed 100. It is guaranteed that the question mark occurs exactly once in the line — as the last symbol and that the line contains at least one letter.

## 输出格式

Print answer for the question in a single line: YES if the answer is "Yes", NO if the answer is "No".

Remember that in the reply to the question the last letter, not the last character counts. I. e. the spaces and the question mark do not count as letters.

## 样例 #1

### 输入

```
Is it a melon?

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
Is it an apple?

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
  Is     it a banana ?

```

### 输出

```
YES

```

## 样例 #4

### 输入

```
Is   it an apple  and a  banana   simultaneouSLY?

```

### 输出

```
YES

```



---

---
title: "A and B and Chess"
layout: "post"
diff: 入门
pid: CF519A
tag: ['模拟', '字符串', '概率论']
---

# A and B and Chess

## 题目描述

A和B正在准备参加编程比赛。

为了锻炼他们的逻辑思维能力从而更好地解决问题，A和B决定来下棋。在游戏期间，A突然想要知道哪位玩家占得了优势。

对于每个棋子我们知道它们的权势值：

皇后的值是9；
车的值是5；
象（相）的值是3；
骑士的值也是3；
卒（兵）的值是1；
国王的值不考虑在优势评估中.
一个玩家的优势值是他在棋盘上所有棋子权势值的总和。

因为A不喜欢算数，所以他请求你告诉他哪位玩家的占有优势？（即优势值更大）

## 输入格式

输入一共八行，八列，描述这个棋盘。

白方的棋子如要表示均用大写字母，黑方则用的是小写字母。

白方棋子规定如下：皇后用Q表示，车用R表示，象用B表示，骑士用N表示，卒用P表示，国王用K表示。

黑方棋子则相反，用小写字母：q,r,b,n,p,k。

一个空的棋盘格子用"."（一个点）表示

无需考虑棋盘上的情况能否在真实的游戏中实现，只需计算出优势总值再比较即可。

## 输出格式

如果白方的优势总值更大，则输出"White",如果黑方的优势总值更大，则输出"Black"。如果总值相等，那么请输出"Draw"。

## 说明/提示

对于样例一，白方总值为9，黑方总值为5，所以输出"White"。

对于样例二，两方总值均为39，输出"Draw"。

对于样例三，白方总值为9，黑方总值为16，输出"Black"。

Translated by @lonelysir

## 样例 #1

### 输入

```
...QK...
........
........
........
........
........
........
...rk...

```

### 输出

```
White

```

## 样例 #2

### 输入

```
rnbqkbnr
pppppppp
........
........
........
........
PPPPPPPP
RNBQKBNR

```

### 输出

```
Draw

```

## 样例 #3

### 输入

```
rppppppr
...k....
........
........
........
........
K...Q...
........

```

### 输出

```
Black

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
title: "Autocomplete"
layout: "post"
diff: 入门
pid: CF53A
tag: ['模拟', '字符串']
---

# Autocomplete

## 题目描述

Autocomplete is a program function that enables inputting the text (in editors, command line shells, browsers etc.) completing the text by its inputted part. Vasya is busy working on a new browser called 'BERowser'. He happens to be working on the autocomplete function in the address line at this very moment. A list consisting of $ n $ last visited by the user pages and the inputted part $ s $ are known. Your task is to complete $ s $ to make it an address of one of the pages from the list. You have to find the lexicographically smallest address having a prefix $ s $ .

## 输入格式

The first line contains the $ s $ line which is the inputted part. The second line contains an integer $ n $ ( $ 1<=n<=100 $ ) which is the number of visited pages. Then follow $ n $ lines which are the visited pages, one on each line. All the lines have lengths of from $ 1 $ to $ 100 $ symbols inclusively and consist of lowercase Latin letters only.

## 输出格式

If $ s $ is not the beginning of any of $ n $ addresses of the visited pages, print $ s $ . Otherwise, print the lexicographically minimal address of one of the visited pages starting from $ s $ .

The lexicographical order is the order of words in a dictionary. The lexicographical comparison of lines is realized by the '<' operator in the modern programming languages.

## 样例 #1

### 输入

```
next
2
nextpermutation
nextelement

```

### 输出

```
nextelement

```

## 样例 #2

### 输入

```
find
4
find
findfirstof
findit
fand

```

### 输出

```
find

```

## 样例 #3

### 输入

```
find
4
fondfind
fondfirstof
fondit
fand

```

### 输出

```
find

```



---

---
title: "Flea travel"
layout: "post"
diff: 入门
pid: CF55A
tag: ['模拟']
---

# Flea travel

## 题目描述

一个虫子位于绕城一圈的$n$片树叶中的一片上，在第$k$分钟，虫子会跳过$k-1$片树叶并在脚下的树叶上做一个记号。在这里，我们假设虫子的$life=+∞$。你的任务是判断该虫子是否将$n$片树叶都做了记号。

## 输入格式

只有一行，一个数字$n$，为树叶总数量。

## 输出格式

若将$n$片树叶都做了记号，输出$YES$。否则，输出$NO$。

Translated by @da32s1da

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
3

```

### 输出

```
NO

```



---

---
title: "Elections"
layout: "post"
diff: 入门
pid: CF570A
tag: ['模拟', '离散化']
---

# Elections

## 题目描述

有 $n$ 个候选人，$m$ 个城市，每一个城市给出每一个候选人的票数，票数最多的就被这个城市选了。当票数一样是，号码最小的被这个城市选。获得票数最多的候选人候选人当选，当有多个候选人获得的票数一样时，号码最小的候选人当选。

## 输入格式

第一行有两个整数 $n,m$（$1 \le n,m \le 100$），表示候选人的个数和城市的个数。

以下 $m$ 行每行都有 $n$ 个非负整数，第 $i$ 行第 $j$ 个的整数 $a_{i, j}$（$1 \le j \le n$，$1 \le i \le m$，$0 \le a_{i, j} \le {10}^9$）表示第 $i$ 个城市给出的第 $j$ 个候选人的选票数。

## 输出格式

一个整数，表示当选的人的编号。

## 样例 #1

### 输入

```
3 3
1 2 3
2 3 1
1 2 1

```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 4
10 10 3
5 1 6
2 2 2
1 5 7

```

### 输出

```
1
```



---

---
title: "Kefa and First Steps"
layout: "post"
diff: 入门
pid: CF580A
tag: ['模拟']
---

# Kefa and First Steps

## 题目描述

Kefa decided to make some money doing business on the Internet for exactly $ n $ days. He knows that on the $ i $ -th day ( $ 1<=i<=n $ ) he makes $ a_{i} $ money. Kefa loves progress, that's why he wants to know the length of the maximum non-decreasing subsegment in sequence $ a_{i} $ . Let us remind you that the subsegment of the sequence is its continuous fragment. A subsegment of numbers is called non-decreasing if all numbers in it follow in the non-decreasing order.

Help Kefa cope with this task!

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ).

The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ).

## 输出格式

Print a single integer — the length of the maximum non-decreasing subsegment of sequence $ a $ .

## 说明/提示

In the first test the maximum non-decreasing subsegment is the numbers from the third to the fifth one.

In the second test the maximum non-decreasing subsegment is the numbers from the first to the third one.

## 样例 #1

### 输入

```
6
2 2 1 3 4 1

```

### 输出

```
3
```

## 样例 #2

### 输入

```
3
2 2 9

```

### 输出

```
3
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
title: "Word"
layout: "post"
diff: 入门
pid: CF59A
tag: ['模拟', '字符串', '概率论']
---

# Word

## 题目描述

Vasya is very upset that many people on the Net mix uppercase and lowercase letters in one word. That's why he decided to invent an extension for his favorite browser that would change the letters' register in every word so that it either only consisted of lowercase letters or, vice versa, only of uppercase ones. At that as little as possible letters should be changed in the word. For example, the word HoUse must be replaced with house, and the word ViP — with VIP. If a word contains an equal number of uppercase and lowercase letters, you should replace all the letters with lowercase ones. For example, maTRIx should be replaced by matrix. Your task is to use the given method on one given word.

## 输入格式

The first line contains a word $ s $ — it consists of uppercase and lowercase Latin letters and possesses the length from $ 1 $ to $ 100 $ .

## 输出格式

Print the corrected word $ s $ . If the given word $ s $ has strictly more uppercase letters, make the word written in the uppercase register, otherwise - in the lowercase one.

## 样例 #1

### 输入

```
HoUse

```

### 输出

```
house

```

## 样例 #2

### 输入

```
ViP

```

### 输出

```
VIP

```

## 样例 #3

### 输入

```
maTRIx

```

### 输出

```
matrix

```



---

---
title: "Fortune Telling"
layout: "post"
diff: 入门
pid: CF59B
tag: ['模拟', '排序', '概率论']
---

# Fortune Telling

## 题目描述

玛丽娜喜欢萨沙。但她一直在想萨沙是否爱她。当然，知道的最好方法就是去占卜。占卜的方法有很多，但是玛丽娜选择了最简单的一个方法。她拿起一只或几只甘菊，一个接一个地掰下花瓣。在每个花瓣之后，她说出“爱”或“不爱”，第一个掰的花瓣后先说“爱”。有 $n$ 朵甘菊在田间生长，它们的花瓣数等于$a_1$，$a_2$，$\ldots$ $a_n$。玛丽娜想挑一束可能有最大花瓣总数的花束，且结果仍然是“爱”。帮她做到这一点：找到花瓣的最大数量可能在哪一个花束中。

## 输入格式

第一行包含一个整数 $n$（$1\leq n\leq 10 0$），这是在田间种植的甘菊数量。第二行包含$n$个整数 $a_i$（$ 1 \leq a_i\leq100$），表示第 $i$ 朵甘菊的花瓣数量。

## 输出格式

输出一个数字，代表花束中最大的花瓣数量，这就会导致“爱”。如果没有这样的花束，请输出$0$。花束可能只由一朵花组成。
感谢@MarshalKen 提供的翻译

## 样例 #1

### 输入

```
1
1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
1
2

```

### 输出

```
0

```

## 样例 #3

### 输入

```
3
5 6 7

```

### 输出

```
13

```



---

---
title: "Chat Server's Outgoing Traffic"
layout: "post"
diff: 入门
pid: CF5A
tag: ['模拟', '字符串']
---

# Chat Server's Outgoing Traffic

## 题目描述

Polycarp正在开发一个名为“Polychat”的新项目。按照IT的现代倾向，他决定，这个项目也应该包含聊天。为了实现这一目标，Polycarp在笔记本电脑前花费了几个小时，实现了一个可以处理三种命令的聊天服务器：

将一个人加入聊天（“添加”命令）。

从聊天中删除一个人（“删除”命令）。

向所有正在聊天的人发送消息，包括发送消息的人（“发送”命令）。

现在，Polycarp希望了解处理特定命令集时服务器将产生的传出流量。

Polycarp知道聊天服务器不会为“添加”和“删除”命令发送流量。当处理“发送”命令时，服务器向聊天的每个参与者(当前在线的人)发送l个字节，其中l是消息的长度。

由于Polycarp没有时间，他在寻求帮助来解决这个问题。

## 输入格式

输入文件将包含不超过100个命令，每个命令都在自己的行中。每行不超过100个字符。命令的格式如下：

+<名称>为“添加”命令。
-<名称>为“删除”命令。
<SENDER_NAME>：<MESSAGE_TEXT>为'发送'命令。

<name>(名字)和<sender_name>是拉丁字母和数字的非空序列。<message_text>可以包含字母，数字和空格，但不能以空格开始或结束<message_text>是一个空行。

保证输入数据是正确的，即不会有“添加”命令，如果人用这样的名字已经在聊天，不会有“删除”命令，如果没有人跟在这样的名字聊天等

所有的名字都是区分大小写的。

## 输出格式

输出流量

Translated by @liyifeng

## 样例 #1

### 输入

```
+Mike
Mike:hello
+Kate
+Dmitry
-Dmitry
Kate:hi
-Kate

```

### 输出

```
9

```

## 样例 #2

### 输入

```
+Mike
-Mike
+Mike
Mike:Hi   I am here
-Mike
+Kate
-Kate

```

### 输出

```
14

```



---

---
title: "USB Flash Drives"
layout: "post"
diff: 入门
pid: CF609A
tag: ['模拟', '贪心', '排序']
---

# USB Flash Drives

## 题目描述

Sean正在把一个大文件考到n个U盘里。这个文件足有m MB那么大。第i个U盘的容量是a[i]。
假设Sean能把文件分装到多个U盘中，请求出他最少需要用多少个U盘来考这个文件。

## 输入格式

第一行包括一个整数n(1<=n<=100)-U盘的个数。

第二行包含一个整数m(1<=m<=10^5)-文件的大小。

以下n行每一行包括一个整数a[i] (1<=a[i]<=1000)-第i个U盘的大小。

确定答案出现-也就是说所有a[i]的总和不小于m。

## 输出格式

输出至少要多少U盘。

翻译提供者：sunhaina061031

## 样例 #1

### 输入

```
3
5
2
1
3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3
6
2
3
2

```

### 输出

```
3

```

## 样例 #3

### 输入

```
2
5
5
10

```

### 输出

```
1

```



---

---
title: "Ultra-Fast Mathematician"
layout: "post"
diff: 入门
pid: CF61A
tag: ['模拟', '字符串']
---

# Ultra-Fast Mathematician

## 题目描述

Shapur was an extremely gifted student. He was great at everything including Combinatorics, Algebra, Number Theory, Geometry, Calculus, etc. He was not only smart but extraordinarily fast! He could manage to sum $ 10^{18} $ numbers in a single second.

One day in 230 AD Shapur was trying to find out if any one can possibly do calculations faster than him. As a result he made a very great contest and asked every one to come and take part.

In his contest he gave the contestants many different pairs of numbers. Each number is made from digits $ 0 $ or $ 1 $ . The contestants should write a new number corresponding to the given pair of numbers. The rule is simple: The $ i $ -th digit of the answer is $ 1 $ if and only if the $ i $ -th digit of the two given numbers differ. In the other case the $ i $ -th digit of the answer is $ 0 $ .

Shapur made many numbers and first tried his own speed. He saw that he can perform these operations on numbers of length $ ∞ $ (length of a number is number of digits in it) in a glance! He always gives correct answers so he expects the contestants to give correct answers, too. He is a good fellow so he won't give anyone very big numbers and he always gives one person numbers of same length.

Now you are going to take part in Shapur's contest. See if you are faster and more accurate.

## 输入格式

There are two lines in each input. Each of them contains a single number. It is guaranteed that the numbers are made from $ 0 $ and $ 1 $ only and that their length is same. The numbers may start with $ 0 $ . The length of each number doesn't exceed 100.

## 输出格式

Write one line — the corresponding answer. Do not omit the leading $ 0 $ s.

## 样例 #1

### 输入

```
1010100
0100101

```

### 输出

```
1110001

```

## 样例 #2

### 输入

```
000
111

```

### 输出

```
111

```

## 样例 #3

### 输入

```
1110
1010

```

### 输出

```
0100

```

## 样例 #4

### 输入

```
01110
01100

```

### 输出

```
00010

```



---

---
title: "Joysticks"
layout: "post"
diff: 入门
pid: CF651A
tag: ['模拟', '贪心', '递归']
---

# Joysticks

## 题目描述

朋友们正要去玩游戏机。他们有两个游戏机，却只有一个充电器。最开始第一个游戏机有a1%的电，第二个游戏机有a2%的电。你只能在每分钟的最开始将一个游戏机接上充电器。每一分钟每个游戏机会消耗2%的电（如果没有接上充电器）或者充上1%的电（如果接上了充电器）。

当两个游戏机都有电时游戏才能继续。因此，如果在某一分钟的开始某个游戏机只有1%的电，它必须接上充电器，否则游戏会停止。如果某个游戏机完全没电（它的电量变为0），游戏也会停下。

试确定该游戏能够持续的最长时间。禁止暂停游戏，即在每一分钟两个游戏机都应该在使用。允许将游戏机充电到超过100%的电量。

## 输入格式

输入的第一行包括两个正整数a1、a2（1 <= a1、a2 <= 100），分别表示第一个游戏机和第二个游戏机的初始电量。

## 输出格式

输出一个整数，游戏能够持续的最长时间。在某一个游戏机没电之前游戏继续。

感谢@蒟蒻的PSJ 提供的翻译

## 样例 #1

### 输入

```
3 5

```

### 输出

```
6

```

## 样例 #2

### 输入

```
4 4

```

### 输出

```
5

```



---

---
title: "Vanya and Fence"
layout: "post"
diff: 入门
pid: CF677A
tag: ['模拟', '概率论']
---

# Vanya and Fence

## 题目描述

有n个人，如果这个人的高度大于k，那么马路宽度+2，否则+1，输出最终的宽度值。

## 输入格式

第一行是n和k
第二行是n个数（这个人的高度）

## 输出格式

输出最终的宽度值。

感谢@666yuchen  提供的翻译和@王轶凡lg2018 提供的建议

## 样例 #1

### 输入

```
3 7
4 5 14

```

### 输出

```
4

```

## 样例 #2

### 输入

```
6 1
1 1 1 1 1 1

```

### 输出

```
6

```

## 样例 #3

### 输入

```
6 5
7 6 8 9 10 5

```

### 输出

```
11

```



---

---
title: "Mishka and Game"
layout: "post"
diff: 入门
pid: CF703A
tag: ['模拟', '概率论']
---

# Mishka and Game

## 题目描述

Mishka是一只小北极熊。正如所知的，小熊喜欢在他们的空闲时间为了巧克力玩骰子。在一个美妙的早上，她正走在冰块上时，Mishka遇见了她的朋友Chris，她们就开始玩这个游戏了。

这个游戏的规则十分简单：首先定义一个回合数$n$ 。
在每一回合，每个玩家扔一个在它的表面写着$1$ 到$6$ 的立方体骰子。扔出较大的数的那个玩家获得这一回合的胜利。如果两名玩家扔出的数一样，则没有胜者。

一般来说，赢得较多回合的玩家将获得这个游戏的胜利。如果两个玩家赢得的回合数相同，这场游戏的结果是平局。

Mishka仍然非常的小以至于不能算胜负场，所以她要求你观看这场比赛并确定结果。请帮帮她吧！

## 输入格式

第一行输入一个整数$n$ （$1\leq n\leq 100$ ） — 游戏的回合数。

下$n$ 行描述了这些回合。其中的第$i$ 行包含一对数 $m_i$ 和$c_i$ （$1\leq m_i,c_i \leq 6$ ） — 在第$i$ 回合Mishka扔出的数和Chris扔出的数。

## 输出格式

如果Mishka是这场游戏的胜利者，仅输出一行"Mishka"（不含引号）。

如果Chris是这场游戏的胜利者，仅输出一行"Chris"（不含引号）。

如果这场游戏是平局，仅输出一行"Friendship is magic!^^"（不含引号）。

## 说明/提示

在第一个样例中，Mishka在第一回合输了，但在第二回合和第三回合赢了，因此她是游戏的获胜者。

在第二个样例中，Mishka在第一回合赢了，Chris在第二回合赢了，游戏结束时以比分1:1战平。

在第三个样例中，Chris在第一回合赢了，但是后面两个回合没有胜利者。游戏的获胜者是Chris。

by @Khassar

## 样例 #1

### 输入

```
3
3 5
2 1
4 2

```

### 输出

```
Mishka
```

## 样例 #2

### 输入

```
2
6 1
1 6

```

### 输出

```
Friendship is magic!^^
```

## 样例 #3

### 输入

```
3
1 5
3 3
2 2

```

### 输出

```
Chris
```



---

---
title: "King Moves"
layout: "post"
diff: 入门
pid: CF710A
tag: ['模拟', '字符串']
---

# King Moves

## 题目描述

The only king stands on the standard chess board. You are given his position in format "cd", where $ c $ is the column from 'a' to 'h' and $ d $ is the row from '1' to '8'. Find the number of moves permitted for the king.

Check the king's moves here <a>https://en.wikipedia.org/wiki/King\_(chess)</a>.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF710A/c293477e407dd29c222477fd35652e45e6890a3c.png)King moves from the position e4

## 输入格式

The only line contains the king's position in the format "cd", where 'c' is the column from 'a' to 'h' and 'd' is the row from '1' to '8'.

## 输出格式

Print the only integer $ x $ — the number of moves permitted for the king.

## 样例 #1

### 输入

```
e4

```

### 输出

```
8

```



---

---
title: "Way Too Long Words"
layout: "post"
diff: 入门
pid: CF71A
tag: ['模拟', '字符串']
---

# Way Too Long Words

## 题目描述

有时候，像“localization”或“internationalization”这样的词汇如此之长，以至于在一篇文章中多次写下这些词语令人厌烦。

让我们考虑一个词太长，如果它的长度严格超过 10个字符。太长的单词应该用一个特殊的缩写代替。

这个缩写是这样写的：我们写下一个单词的第一个和最后一个字母，并在它们之间写出第一个和最后一个字母之间的字母数。该数字是十进制系统，不包含任何前导零。

因此，“localization”将拼写为“l10n”，而“internationalization”将拼写为”i18n”。

建议您使用缩写来自动更改单词的过程。因为所有太长的单词应该用缩写代替，不太长的单词不应该经历任何改变。

## 输入格式

第一行包含一个整数 n（ 1 <= N <= 100 1 < = n < = 1 0 0）。以下各项 n 行包含一个词。所有的单词由小写拉丁字母组成， 并且拥有从1到100个字符的长度。 _ _

## 输出格式

输出n行。第i行应包含来自输入数据的第 i个字替换的结果。

## 样例 #1

### 输入

```
4
word
localization
internationalization
pneumonoultramicroscopicsilicovolcanoconiosis

```

### 输出

```
word
l10n
i18n
p43s

```



---

---
title: "One-dimensional Japanese Crossword"
layout: "post"
diff: 入门
pid: CF721A
tag: ['模拟', '字符串']
---

# One-dimensional Japanese Crossword

## 题目描述

最近，阿德蒂克发现了日语填字游戏。日语填字游戏是一幅图片，表示为一张桌子大小的a×b正方形，每个方格都是白色或黑色的。
行的左边和列的顶部都有整数，对相应的行或列进行加密。整数的数量表示对应的行或列中有多少组黑色方块，整数本身表示相应组中连续的黑色方块的数量(您可以在维基百科[https://en.wikipedia.org/wiki/Japanese_crossword](https://en.wikipedia.org/wiki/Japanese_crossword)）_纵横字谜中找到更详细的解释)。

阿德蒂克认为日语填字的一般情况太复杂，画了n个正方形(例如1×n1×n)的一行，他想用和日语填字一样的方式加密。

对一行日文横线进行加密的例子。帮助阿德蒂克找到对他画的行进行加密的数字。

## 输入格式

输入的第一行包含单个整数n n(1<=n<=100 1<=n<=100)-行的长度。输入的第二行包含一个由n个字符‘B’或‘W’组成的字符串(‘B’对应于黑色方格，‘W’-与Adtemk绘制的行中的白色方格对应)。

## 输出格式

第一行应该包含一个整数k-加密行的整数，例如行中的黑方格组数。第二行应该包含k个整数，对行进行加密，例如，按照从左到右的顺序对应连续黑色方块的大小。

## 样例 #1

### 输入

```
3
BBW

```

### 输出

```
1
2 
```

## 样例 #2

### 输入

```
5
BWBWB

```

### 输出

```
3
1 1 1 
```

## 样例 #3

### 输入

```
4
WWWW

```

### 输出

```
0

```

## 样例 #4

### 输入

```
4
BBBB

```

### 输出

```
1
4 
```

## 样例 #5

### 输入

```
13
WBBBBWWBWBBBW

```

### 输出

```
3
4 1 3 
```



---

---
title: "The New Year: Meeting Friends"
layout: "post"
diff: 入门
pid: CF723A
tag: ['模拟', '数学']
---

# The New Year: Meeting Friends

## 题目描述

有三个朋友在一条笔直的岛上生活着，我们将其看做一条直线（数轴）。第一个人的家在点$x_1$​ 处，第二个人的家在点$x_2$处，第三个人的家在点$x_3$处。他们计划一起庆祝新年，所以他们需要在直线上的任一某点见面。请你帮他们找出一个点，使得他们走的总距离最短，并求出这个总距离。

## 输入格式

第一行有三个数，$x_1$，$x_2$​ ，$x_3$ ，(1<=$x_1$​ ，$x_2$​ ，$x_3$<=100)。分别对应第一、第二和第三个人的房子的位置。

## 输出格式

输出一个整数：最小的总距离以满足他们能在一起庆祝新年。

## 说明/提示

在第一个样例中，朋友们应在点4见面。因此，第一个朋友必须走3个单位距离（从点7到点4），第二个朋友也要走3个单位距离（从点1到点4），而第三位朋友不用去任何地方，因为他住在点4。

感谢@cplus 提供的翻译

## 样例 #1

### 输入

```
7 1 4

```

### 输出

```
6

```

## 样例 #2

### 输入

```
30 20 10

```

### 输出

```
20

```



---

---
title: "Buy a Shovel"
layout: "post"
diff: 入门
pid: CF732A
tag: ['模拟', '搜索', '数学']
---

# Buy a Shovel

## 题目描述

Polycarp urgently needs a shovel! He comes to the shop and chooses an appropriate one. The shovel that Policarp chooses is sold for $ k $ burles. Assume that there is an unlimited number of such shovels in the shop.

In his pocket Polycarp has an unlimited number of "10-burle coins" and exactly one coin of $ r $ burles ( $ 1<=r<=9 $ ).

What is the minimum number of shovels Polycarp has to buy so that he can pay for the purchase without any change? It is obvious that he can pay for 10 shovels without any change (by paying the requied amount of 10-burle coins and not using the coin of $ r $ burles). But perhaps he can buy fewer shovels and pay without any change. Note that Polycarp should buy at least one shovel.

## 输入格式

The single line of input contains two integers $ k $ and $ r $ ( $ 1<=k<=1000 $ , $ 1<=r<=9 $ ) — the price of one shovel and the denomination of the coin in Polycarp's pocket that is different from "10-burle coins".

Remember that he has an unlimited number of coins in the denomination of 10, that is, Polycarp has enough money to buy any number of shovels.

## 输出格式

Print the required minimum number of shovels Polycarp has to buy so that he can pay for them without any change.

## 说明/提示

In the first example Polycarp can buy 9 shovels and pay $ 9·117=1053 $ burles. Indeed, he can pay this sum by using 10-burle coins and one 3-burle coin. He can't buy fewer shovels without any change.

In the second example it is enough for Polycarp to buy one shovel.

In the third example Polycarp should buy two shovels and pay $ 2·15=30 $ burles. It is obvious that he can pay this sum without any change.

## 样例 #1

### 输入

```
117 3

```

### 输出

```
9

```

## 样例 #2

### 输入

```
237 7

```

### 输出

```
1

```

## 样例 #3

### 输入

```
15 2

```

### 输出

```
2

```



---

---
title: "Grasshopper And the String"
layout: "post"
diff: 入门
pid: CF733A
tag: ['模拟', '字符串']
---

# Grasshopper And the String

## 题目描述

## 题意描述

一天，有一只蚱蜢正在草地上跳跃，它发现了一张纸，上面有一个字符串。蚱蜢感兴趣的是，它所需要的最小的跳跃能力是多少，才能跳到纸的另一端，它只会跳到元音字母上(为'A','E','I','O','U','Y')。

形式上，蚱蜢从字符串的最左边一个字符的左侧开始跳，目标是跳到最右边一个字符的右侧。蚱蜢的跳跃能力的值就是它跳跃的距离。跳跃能力最小为 $1$ 。

![](https://cdn.luogu.org/upload/vjudge_pic/CF733A/3d6ef82d52bf3bf3e745680bd25bf47489d98417.png)

如图，样例1中蚱蜢所需的最小跳跃能力为4。

## 输入格式

输入的第一行是由大写字母组成的一个字符串，保证该字符串不为空，字符串的长度不超过100。

## 输出格式

输出一个整数 $a$ ，为蚱蜢在这张纸条上所需的最小跳跃能力。

Translated by @dblark

## 样例 #1

### 输入

```
ABABBBACFEYUKOTT

```

### 输出

```
4
```

## 样例 #2

### 输入

```
AAA

```

### 输出

```
1
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
title: "A Serial Killer"
layout: "post"
diff: 入门
pid: CF776A
tag: ['模拟', '字符串']
---

# A Serial Killer

## 题目描述

我们所深爱的侦探夏洛克，目前正试图抓住一个每天都要杀死一个人的强迫症杀手。通过运用其自身高超的推理能力，夏洛克目前对于凶手挑选下一位受害者的策略了然于心。
当第一天降临，杀手首先从两位潜在的受害者中随机挑选一位脸黑人士进行暗杀，并且每当一位潜在的受害者倒下，都会有另一人取代该受害者之位置，成为新的潜在受害者（幸免于难的那位仍然留在潜在受害者名单上）。可以确定这位杀手每天都会重复这一过程，这样一来，杀手每天都有两个潜在的受害者可供选择进行暗杀。好在夏洛克知道最初的两个潜在受害者是谁，并且，夏洛克知道发生杀人事件的当天的死者是谁以及新的潜在受害者是谁。
显然，好心的你需要每天帮助夏洛克列出每天的的潜在受害者名单，这样一来夏洛克就能从中观察到一些奇妙的规律。

## 输入格式

输入的第一行包含两个名字(每个名字的长度不超过10)，这是最初的两个潜在受害者。下一行包含整数天数n (1<=n<=1000)。
接下来的n行每行包含两个名字(每个名字的长度不超过10)，第一个是当天被谋杀的人（死者），第二个是取代死者成为新的潜在受害者的人。

## 输出格式

输出n+1行，每行输出当天的两位潜在受害者的名字（这两个名字的输出顺序可以随意）

## 说明/提示

如样例1所示，杀手从ross和rachel开始杀起。
第一天结束后，ross不幸被杀而joey接替。
第二天结束后，rachel不幸被杀而phoebe接替。
第三天结束后，phoebe不幸被杀而monica接替。
第四天结束后，monica不幸被杀而chandler接替。

## 样例 #1

### 输入

```
ross rachel
4
ross joey
rachel phoebe
phoebe monica
monica chandler

```

### 输出

```
ross rachel
joey rachel
joey phoebe
joey monica
joey chandler

```

## 样例 #2

### 输入

```
icm codeforces
1
codeforces technex

```

### 输出

```
icm codeforces
icm technex

```



---

---
title: "Haiku"
layout: "post"
diff: 入门
pid: CF78A
tag: ['模拟', '概率论']
---

# Haiku

## 题目描述

Haiku is a genre of Japanese traditional poetry.

A haiku poem consists of 17 syllables split into three phrases, containing 5, 7 and 5 syllables correspondingly (the first phrase should contain exactly 5 syllables, the second phrase should contain exactly 7 syllables, and the third phrase should contain exactly 5 syllables). A haiku masterpiece contains a description of a moment in those three phrases. Every word is important in a small poem, which is why haiku are rich with symbols. Each word has a special meaning, a special role. The main principle of haiku is to say much using a few words.

To simplify the matter, in the given problem we will consider that the number of syllable in the phrase is equal to the number of vowel letters there. Only the following letters are regarded as vowel letters: "a", "e", "i", "o" and "u".

Three phases from a certain poem are given. Determine whether it is haiku or not.

## 输入格式

The input data consists of three lines. The length of each line is between $ 1 $ and $ 100 $ , inclusive. The $ i $ -th line contains the $ i $ -th phrase of the poem. Each phrase consists of one or more words, which are separated by one or more spaces. A word is a non-empty sequence of lowercase Latin letters. Leading and/or trailing spaces in phrases are allowed. Every phrase has at least one non-space character. See the example for clarification.

## 输出格式

Print "YES" (without the quotes) if the poem is a haiku. Otherwise, print "NO" (also without the quotes).

## 样例 #1

### 输入

```
on  codeforces 
beta round is running
   a rustling of keys 

```

### 输出

```
YES
```

## 样例 #2

### 输入

```
how many gallons
of edo s rain did you drink
                                cuckoo

```

### 输出

```
NO
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
title: "An abandoned sentiment from past"
layout: "post"
diff: 入门
pid: CF814A
tag: ['模拟', '贪心']
---

# An abandoned sentiment from past

## 题目描述

A few years ago, Hitagi encountered a giant crab, who stole the whole of her body weight. Ever since, she tried to avoid contact with others, for fear that this secret might be noticed.

To get rid of the oddity and recover her weight, a special integer sequence is needed. Hitagi's sequence has been broken for a long time, but now Kaiki provides an opportunity.

Hitagi's sequence $ a $ has a length of $ n $ . Lost elements in it are denoted by zeros. Kaiki provides another sequence $ b $ , whose length $ k $ equals the number of lost elements in $ a $ (i.e. the number of zeros). Hitagi is to replace each zero in $ a $ with an element from $ b $ so that each element in $ b $ should be used exactly once. Hitagi knows, however, that, apart from $ 0 $ , no integer occurs in $ a $ and $ b $ more than once in total.

If the resulting sequence is not an increasing sequence, then it has the power to recover Hitagi from the oddity. You are to determine whether this is possible, or Kaiki's sequence is just another fake. In other words, you should detect whether it is possible to replace each zero in $ a $ with an integer from $ b $ so that each integer from $ b $ is used exactly once, and the resulting sequence is not increasing.

## 输入格式

The first line of input contains two space-separated positive integers $ n $ ( $ 2<=n<=100 $ ) and $ k $ ( $ 1<=k<=n $ ) — the lengths of sequence $ a $ and $ b $ respectively.

The second line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ ( $ 0<=a_{i}<=200 $ ) — Hitagi's broken sequence with exactly $ k $ zero elements.

The third line contains $ k $ space-separated integers $ b_{1},b_{2},...,b_{k} $ ( $ 1<=b_{i}<=200 $ ) — the elements to fill into Hitagi's sequence.

Input guarantees that apart from $ 0 $ , no integer occurs in $ a $ and $ b $ more than once in total.

## 输出格式

Output "Yes" if it's possible to replace zeros in $ a $ with elements in $ b $ and make the resulting sequence not increasing, and "No" otherwise.

## 说明/提示

In the first sample:

- Sequence $ a $ is $ 11,0,0,14 $ .
- Two of the elements are lost, and the candidates in $ b $ are $ 5 $ and $ 4 $ .
- There are two possible resulting sequences: $ 11,5,4,14 $ and $ 11,4,5,14 $ , both of which fulfill the requirements. Thus the answer is "Yes".

In the second sample, the only possible resulting sequence is $ 2,3,5,8,9,10 $ , which is an increasing sequence and therefore invalid.

## 样例 #1

### 输入

```
4 2
11 0 0 14
5 4

```

### 输出

```
Yes

```

## 样例 #2

### 输入

```
6 1
2 3 0 8 9 10
5

```

### 输出

```
No

```

## 样例 #3

### 输入

```
4 1
8 94 0 4
89

```

### 输出

```
Yes

```

## 样例 #4

### 输入

```
7 7
0 0 0 0 0 0 0
1 2 3 4 5 6 7

```

### 输出

```
Yes

```



---

---
title: "The Useless Toy"
layout: "post"
diff: 入门
pid: CF834A
tag: ['模拟']
---

# The Useless Toy

## 题目描述

走在马什马洛市的街道上，斯拉斯蒂诺纳看到一些商人在卖一种现在很流行的无用玩具——焦糖纺纱机！她想加入热潮，于是便买了一个。

斯威特兰的纺纱工有V形焦糖的形状。每个纺纱机都可以绕着一条看不见的魔法轴旋转。在特定的时间点，旋转器可以采取如下所示的4个位置（每个位置相对于前一个旋转90度，第四个位置后面跟着第一个位置）：
![](https://cdn.luogu.org/upload/vjudge_pic/CF834A/978c2c171211f16d263ee860d565ee38c2afcc26.png)
在纺纱机被纺纱后，它开始旋转，这通过以下算法描述：纺纱机维持其位置一秒钟，然后以顺时针或逆时针的顺序庄严地切换到下一个位置，这取决于纺纱机的纺纱方向。

斯拉斯蒂诺纳设法使旋转器旋转了n秒。被过程的优雅所吸引，她完全忘记了纺纱机旋转的方向！幸运的是，她成功地回忆起了开始的位置，并想根据她所知道的信息推断出方向。请你帮助她完成这件事。

## 输入格式

第一个字符串中有两个字符——旋转器的起始位置和结束位置。该位置用下列字符之一编码：v（ASCII代码118，小写字母v）、<（ASCII代码60）、^（ASCII代码94）或>（ASCII代码6262）（参见上面的图片以供参考）。字符由一个单独的空间分隔。

在第二个字符串中，输入单个数n( 0<=n<=10^9)——旋转的持续时间。

在假定给定起始位置的情况下，保证旋转器的结束位置是任意方向上n次旋转两次的结果。

## 输出格式

如果方向是顺时针，输出cw。如果逆时针，否则未定义。

## 样例 #1

### 输入

```
^ >
1

```

### 输出

```
cw

```

## 样例 #2

### 输入

```
< ^
3

```

### 输出

```
ccw

```

## 样例 #3

### 输入

```
^ v
6

```

### 输出

```
undefined

```



---

---
title: "Arya and Bran"
layout: "post"
diff: 入门
pid: CF839A
tag: ['模拟']
---

# Arya and Bran

## 题目描述

布兰和他的姐姐艾莉亚来自同一所房子。布兰喜欢糖果，所以艾莉亚会给他一些糖果。

一开始，艾莉亚和布兰有0个糖果。一共有n天，在第i天，艾莉亚会在盒子里找到上帝赐予的ai颗糖果。她每天最多能给布兰8块糖。没有给完的糖果可以在以后给他。

你的任务是找出在第n天结束前，布兰最早在第几天可以得到k颗糖果。最后你只要将输出最早天数。如果布兰在第n天也不能得到k颗糖果则输出-1。

## 输入格式

第一行包含两个整数 $n$（$1\le n\le 100$）和 $k$（$1\le k\le 10000$）
第二行包含 $n$ 个整数 $a_1,a_2,a_3,\ldots,a_n$（$1\leq a_i\leq100$）

## 输出格式

输出应包含一个整数。如果布兰在 $n$ 天里可以得到 $k$ 颗糖果则输出最早天数，否则输出 `-1`。

## 说明/提示

样例1中，艾莉亚在第二天时可以给布兰3颗糖果。 样例2中，艾莉亚可以在第三天时给布兰总共17颗糖果，因为她每天最多可以给他8颗糖果。
样例3中，艾莉亚不能给布兰9颗糖果，因为她每天最多可以给他8颗糖果，然而只有1天。

## 样例 #1

### 输入

```
2 3
1 2

```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 17
10 10 10

```

### 输出

```
3
```

## 样例 #3

### 输入

```
1 9
10

```

### 输出

```
-1
```



---

---
title: "Quasi-palindrome"
layout: "post"
diff: 入门
pid: CF863A
tag: ['模拟', '字符串', '概率论']
---

# Quasi-palindrome

## 题目描述

Let quasi-palindromic number be such number that adding some leading zeros (possible none) to it produces a palindromic string.

String $ t $ is called a palindrome, if it reads the same from left to right and from right to left.

For example, numbers $ 131 $ and $ 2010200 $ are quasi-palindromic, they can be transformed to strings " $ 131 $ " and " $ 002010200 $ ", respectively, which are palindromes.

You are given some integer number $ x $ . Check if it's a quasi-palindromic number.

## 输入格式

The first line contains one integer number $ x $ ( $ 1<=x<=10^{9} $ ). This number is given without any leading zeroes.

## 输出格式

Print "YES" if number $ x $ is quasi-palindromic. Otherwise, print "NO" (without quotes).

## 样例 #1

### 输入

```
131

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
320

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
2010200

```

### 输出

```
YES

```



---

---
title: "Fair Game"
layout: "post"
diff: 入门
pid: CF864A
tag: ['模拟', '排序']
---

# Fair Game

## 题目描述

Petya and Vasya decided to play a game. They have $ n $ cards ( $ n $ is an even number). A single integer is written on each card.

Before the game Petya will choose an integer and after that Vasya will choose another integer (different from the number that Petya chose). During the game each player takes all the cards with number he chose. For example, if Petya chose number $ 5 $ before the game he will take all cards on which $ 5 $ is written and if Vasya chose number $ 10 $ before the game he will take all cards on which $ 10 $ is written.

The game is considered fair if Petya and Vasya can take all $ n $ cards, and the number of cards each player gets is the same.

Determine whether Petya and Vasya can choose integer numbers before the game so that the game is fair.

## 输入格式

The first line contains a single integer $ n $ ( $ 2<=n<=100 $ ) — number of cards. It is guaranteed that $ n $ is an even number.

The following $ n $ lines contain a sequence of integers $ a_{1},a_{2},...,a_{n} $ (one integer per line, $ 1<=a_{i}<=100 $ ) — numbers written on the $ n $ cards.

## 输出格式

If it is impossible for Petya and Vasya to choose numbers in such a way that the game will be fair, print "NO" (without quotes) in the first line. In this case you should not print anything more.

In the other case print "YES" (without quotes) in the first line. In the second line print two distinct integers — number that Petya should choose and the number that Vasya should choose to make the game fair. If there are several solutions, print any of them.

## 说明/提示

In the first example the game will be fair if, for example, Petya chooses number $ 11 $ , and Vasya chooses number $ 27 $ . Then the will take all cards — Petya will take cards $ 1 $ and $ 4 $ , and Vasya will take cards $ 2 $ and $ 3 $ . Thus, each of them will take exactly two cards.

In the second example fair game is impossible because the numbers written on the cards are equal, but the numbers that Petya and Vasya should choose should be distinct.

In the third example it is impossible to take all cards. Petya and Vasya can take at most five cards — for example, Petya can choose number $ 10 $ and Vasya can choose number $ 20 $ . But for the game to be fair it is necessary to take $ 6 $ cards.

## 样例 #1

### 输入

```
4
11
27
27
11

```

### 输出

```
YES
11 27

```

## 样例 #2

### 输入

```
2
6
6

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
6
10
20
30
20
10
20

```

### 输出

```
NO

```

## 样例 #4

### 输入

```
6
1
1
2
2
3
3

```

### 输出

```
NO

```



---

---
title: "Polycarp and Letters"
layout: "post"
diff: 入门
pid: CF864B
tag: ['模拟', '字符串', '搜索']
---

# Polycarp and Letters

## 题目描述

Polycarp loves lowercase letters and dislikes uppercase ones. Once he got a string $ s $ consisting only of lowercase and uppercase Latin letters.

Let $ A $ be a set of positions in the string. Let's call it pretty if following conditions are met:

- letters on positions from $ A $ in the string are all distinct and lowercase;
- there are no uppercase letters in the string which are situated between positions from $ A $ (i.e. there is no such $ j $ that $ s[j] $ is an uppercase letter, and $ a_{1}<j<a_{2} $ for some $ a_{1} $ and $ a_{2} $ from $ A $ ).

Write a program that will determine the maximum number of elements in a pretty set of positions.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=200 $ ) — length of string $ s $ .

The second line contains a string $ s $ consisting of lowercase and uppercase Latin letters.

## 输出格式

Print maximum number of elements in pretty set of positions for string $ s $ .

## 说明/提示

In the first example the desired positions might be $ 6 $ and $ 8 $ or $ 7 $ and $ 8 $ . Positions $ 6 $ and $ 7 $ contain letters 'a', position $ 8 $ contains letter 'b'. The pair of positions $ 1 $ and $ 8 $ is not suitable because there is an uppercase letter 'B' between these position.

In the second example desired positions can be $ 7 $ , $ 8 $ and $ 11 $ . There are other ways to choose pretty set consisting of three elements.

In the third example the given string $ s $ does not contain any lowercase letters, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
11
aaaaBaabAbA

```

### 输出

```
2

```

## 样例 #2

### 输入

```
12
zACaAbbaazzC

```

### 输出

```
3

```

## 样例 #3

### 输入

```
3
ABC

```

### 输出

```
0

```



---

---
title: "Between the Offices"
layout: "post"
diff: 入门
pid: CF867A
tag: ['模拟', '字符串']
---

# Between the Offices

## 题目描述

As you may know, MemSQL has American offices in both San Francisco and Seattle. Being a manager in the company, you travel a lot between the two cities, always by plane.

You prefer flying from Seattle to San Francisco than in the other direction, because it's warmer in San Francisco. You are so busy that you don't remember the number of flights you have made in either direction. However, for each of the last $ n $ days you know whether you were in San Francisco office or in Seattle office. You always fly at nights, so you never were at both offices on the same day. Given this information, determine if you flew more times from Seattle to San Francisco during the last $ n $ days, or not.

## 输入格式

The first line of input contains single integer $ n $ ( $ 2<=n<=100 $ ) — the number of days.

The second line contains a string of length $ n $ consisting of only capital 'S' and 'F' letters. If the $ i $ -th letter is 'S', then you were in Seattle office on that day. Otherwise you were in San Francisco. The days are given in chronological order, i.e. today is the last day in this sequence.

## 输出格式

Print "YES" if you flew more times from Seattle to San Francisco, and "NO" otherwise.

You can print each letter in any case (upper or lower).

## 说明/提示

In the first example you were initially at San Francisco, then flew to Seattle, were there for two days and returned to San Francisco. You made one flight in each direction, so the answer is "NO".

In the second example you just flew from Seattle to San Francisco, so the answer is "YES".

In the third example you stayed the whole period in San Francisco, so the answer is "NO".

In the fourth example if you replace 'S' with ones, and 'F' with zeros, you'll get the first few digits of $ π $ in binary representation. Not very useful information though.

## 样例 #1

### 输入

```
4
FSSF

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
2
SF

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
10
FFFFFFFFFF

```

### 输出

```
NO

```

## 样例 #4

### 输入

```
10
SSFFSFFSFF

```

### 输出

```
YES

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
title: "Search for Pretty Integers"
layout: "post"
diff: 入门
pid: CF870A
tag: ['模拟', '排序', '剪枝']
---

# Search for Pretty Integers

## 题目描述

You are given two lists of non-zero digits.

Let's call an integer pretty if its (base $ 10 $ ) representation has at least one digit from the first list and at least one digit from the second list. What is the smallest positive pretty integer?

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n,m<=9 $ ) — the lengths of the first and the second lists, respectively.

The second line contains $ n $ distinct digits $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=9 $ ) — the elements of the first list.

The third line contains $ m $ distinct digits $ b_{1},b_{2},...,b_{m} $ ( $ 1<=b_{i}<=9 $ ) — the elements of the second list.

## 输出格式

Print the smallest pretty integer.

## 说明/提示

In the first example $ 25 $ , $ 46 $ , $ 24567 $ are pretty, as well as many other integers. The smallest among them is $ 25 $ . $ 42 $ and $ 24 $ are not pretty because they don't have digits from the second list.

In the second example all integers that have at least one digit different from $ 9 $ are pretty. It's obvious that the smallest among them is $ 1 $ , because it's the smallest positive integer.

## 样例 #1

### 输入

```
2 3
4 2
5 7 6

```

### 输出

```
25

```

## 样例 #2

### 输入

```
8 8
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1

```

### 输出

```
1

```



---

---
title: "Book Reading"
layout: "post"
diff: 入门
pid: CF884A
tag: ['模拟']
---

# Book Reading

## 题目描述

【题目大意】 最近Luba买了一本书，他希望在接下来的$n$  天里抽出$t$  秒看完这本书。（总计$t$  秒） 但是Luba每天会有一些工作，对于第$i$天，他需要花费$a_i$ 秒时间来工作。 问Luba最早在什么时候能看完这本书。（注意一天有$86400$ 秒）

## 输出格式

Translated by @Durant_Lee

## 样例 #1

### 输入

```
2 2
86400 86398

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2 86400
0 86400

```

### 输出

```
1

```



---

---
title: "Local Extrema"
layout: "post"
diff: 入门
pid: CF888A
tag: ['模拟']
---

# Local Extrema

## 题目描述

You are given an array $ a $ . Some element of this array $ a_{i} $ is a local minimum iff it is strictly less than both of its neighbours (that is, $ a_{i}<a_{i-1} $ and $ a_{i}<a_{i+1} $ ). Also the element can be called local maximum iff it is strictly greater than its neighbours (that is, $ a_{i}>a_{i-1} $ and $ a_{i}>a_{i+1} $ ). Since $ a_{1} $ and $ a_{n} $ have only one neighbour each, they are neither local minima nor local maxima.

An element is called a local extremum iff it is either local maximum or local minimum. Your task is to calculate the number of local extrema in the given array.

## 输入格式

The first line contains one integer $ n $ ( $ 1<=n<=1000 $ ) — the number of elements in array $ a $ .

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 1<=a_{i}<=1000 $ ) — the elements of array $ a $ .

## 输出格式

Print the number of local extrema in the given array.

## 样例 #1

### 输入

```
3
1 2 3

```

### 输出

```
0

```

## 样例 #2

### 输入

```
4
1 5 2 5

```

### 输出

```
2

```



---

---
title: "Scarborough Fair"
layout: "post"
diff: 入门
pid: CF897A
tag: ['模拟', '字符串']
---

# Scarborough Fair

## 题目描述

Are you going to Scarborough Fair?Parsley, sage, rosemary and thyme.

Remember me to one who lives there.

He once was the true love of mine.





Willem is taking the girl to the highest building in island No.28, however, neither of them knows how to get there.

Willem asks his friend, Grick for directions, Grick helped them, and gave them a task.

Although the girl wants to help, Willem insists on doing it by himself.

Grick gave Willem a string of length $ n $ .

Willem needs to do $ m $ operations, each operation has four parameters $ l,r,c_{1},c_{2} $ , which means that all symbols $ c_{1} $ in range $ [l,r] $ (from $ l $ -th to $ r $ -th, including $ l $ and $ r $ ) are changed into $ c_{2} $ . String is 1-indexed.

Grick wants to know the final string after all the $ m $ operations.

## 输入格式

The first line contains two integers $ n $ and $ m $ $ (1<=n,m<=100) $ .

The second line contains a string $ s $ of length $ n $ , consisting of lowercase English letters.

Each of the next $ m $ lines contains four parameters $ l,r,c_{1},c_{2} $ ( $ 1<=l<=r<=n $ , $ c_{1},c_{2} $ are lowercase English letters), separated by space.

## 输出格式

Output string $ s $ after performing $ m $ operations described above.

## 说明/提示

For the second example:

After the first operation, the string is wxxak.

After the second operation, the string is waaak.

After the third operation, the string is gaaak.

## 样例 #1

### 输入

```
3 1
ioi
1 1 i n

```

### 输出

```
noi
```

## 样例 #2

### 输入

```
5 3
wxhak
3 3 h x
1 5 x a
1 3 w g

```

### 输出

```
gaaak
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
title: "Splitting in Teams"
layout: "post"
diff: 入门
pid: CF899A
tag: ['模拟', '概率论', '栈']
---

# Splitting in Teams

## 题目描述

There were $ n $ groups of students which came to write a training contest. A group is either one person who can write the contest with anyone else, or two people who want to write the contest in the same team.

The coach decided to form teams of exactly three people for this training. Determine the maximum number of teams of three people he can form. It is possible that he can't use all groups to form teams. For groups of two, either both students should write the contest, or both should not. If two students from a group of two will write the contest, they should be in the same team.

## 输入格式

The first line contains single integer $ n $ ( $ 2<=n<=2·10^{5} $ ) — the number of groups.

The second line contains a sequence of integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=2 $ ), where $ a_{i} $ is the number of people in group $ i $ .

## 输出格式

Print the maximum number of teams of three people the coach can form.

## 说明/提示

In the first example the coach can form one team. For example, he can take students from the first, second and fourth groups.

In the second example he can't make a single team.

In the third example the coach can form three teams. For example, he can do this in the following way:

- The first group (of two people) and the seventh group (of one person),
- The second group (of two people) and the sixth group (of one person),
- The third group (of two people) and the fourth group (of one person).

## 样例 #1

### 输入

```
4
1 1 2 1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2
2 2

```

### 输出

```
0

```

## 样例 #3

### 输入

```
7
2 2 2 1 1 1 1

```

### 输出

```
3

```

## 样例 #4

### 输入

```
3
1 1 1

```

### 输出

```
1

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
title: "Modular Exponentiation"
layout: "post"
diff: 入门
pid: CF913A
tag: ['模拟']
---

# Modular Exponentiation

## 题目描述

The following problem is well-known: given integers $ n $ and $ m $ , calculate

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF913A/73fb55a49ff8c4211b34696969c8aef5090c1d6d.png), where $ 2^{n}=2·2·...·2 $ ( $ n $ factors), and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF913A/b0d2851c9c5ab36f8f15a3eac416cac07be09dd3.png) denotes the remainder of division of $ x $ by $ y $ .

You are asked to solve the "reverse" problem. Given integers $ n $ and $ m $ , calculate

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF913A/d4dceae314a5c8428af0d75bf92415449f36c7d5.png).

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=10^{8} $ ).

The second line contains a single integer $ m $ ( $ 1<=m<=10^{8} $ ).

## 输出格式

Output a single integer — the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF913A/d4dceae314a5c8428af0d75bf92415449f36c7d5.png).

## 说明/提示

In the first example, the remainder of division of 42 by $ 2^{4}=16 $ is equal to 10.

In the second example, 58 is divisible by $ 2^{1}=2 $ without remainder, and the answer is 0.

## 样例 #1

### 输入

```
4
42

```

### 输出

```
10

```

## 样例 #2

### 输入

```
1
58

```

### 输出

```
0

```

## 样例 #3

### 输入

```
98765432
23456789

```

### 输出

```
23456789

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
title: "Chips"
layout: "post"
diff: 入门
pid: CF92A
tag: ['模拟', '数学', '概率论']
---

# Chips

## 题目描述

现在有n个海狮坐成一个圆圈玩♂游♂戏。所有海狮都被顺时针的被编上号码了：2号海狮在1号海狮的左边坐着，3号海狮在2号海狮的左边坐着，……，1号海狮在n号海狮的左边坐着。


我们还有一位慷慨的来自某薯片公司的员工。他为了宣传他的薯片有多好吃，带来了m片薯片来到海狮群做宣传。他站在海狮圈的中间并顺时针转动。第i号海狮可以分到i个薯片。如果这位员工没有足够的薯片，这个黑心的员工就带着剩下的薯片跑了。现在给你n和m，让你求这个员工最后会拿多少薯片。

## 输入格式

一行，包含两个整数n和m。（1<=n<=50，1<=m<=10^4）

## 输出格式

输出这个员工带着多少薯片跑了

感谢@deadpool123 提供翻译

## 样例 #1

### 输入

```
4 11

```

### 输出

```
0

```

## 样例 #2

### 输入

```
17 107

```

### 输出

```
2

```

## 样例 #3

### 输入

```
3 8

```

### 输出

```
1

```



---

---
title: "Friends Meeting"
layout: "post"
diff: 入门
pid: CF931A
tag: ['模拟']
---

# Friends Meeting

## 题目描述

在x-坐标轴（可以视为数轴）上有两个人，分别从$a$ 位置和$b$ 位置出发。

对于每个人，他可以往任意方向无限次地移动。当他第$i$ 次移动时，疲乏度增加$i$ 。例如，一个人第$1$ 次移动疲乏度增加$1$ ，第$2$ 次移动疲乏度增加$2$ （累计疲乏度为$3$ ），第$3$ 次移动增加$3$ （累计疲乏度为$6$ ），以此类推。

试求出这两个人在同一点相遇时疲乏度的和的最小值。

## 输入格式

分两行输入两个整数$a$ 和$b$ 。

$1 \le a,b \le 1000$  且 $ a\neq b$ 。

## 输出格式

一个整数，即两人疲乏度的和的最小值。

### 样例解释
- 样例1：显然，其中一个人移动一个步即可，则答案为$1$ 。
- 样例2：显然，两人各移动一步，到达位置$100$ 。答案为$1+1=2$ 。
- 样例3：为到达位置$8$ ，左边的人向右移动$3$ 步，疲乏度为$1+2+3=6$ ；右边的人向左移动$2$ 步，疲乏度为$1+2=3$ 。答案为$6+3=9$ 。

感谢@hiuseues 提供的翻译

## 样例 #1

### 输入

```
3
4

```

### 输出

```
1

```

## 样例 #2

### 输入

```
101
99

```

### 输出

```
2

```

## 样例 #3

### 输入

```
5
10

```

### 输出

```
9

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
title: "Tetris"
layout: "post"
diff: 入门
pid: CF961A
tag: ['模拟', '概率论']
---

# Tetris

## 题目描述

You are given a following process.

There is a platform with $ n $ columns. $ 1 \times 1 $ squares are appearing one after another in some columns on this platform. If there are no squares in the column, a square will occupy the bottom row. Otherwise a square will appear at the top of the highest square of this column.

When all of the $ n $ columns have at least one square in them, the bottom row is being removed. You will receive $ 1 $ point for this, and all the squares left will fall down one row.

You task is to calculate the amount of points you will receive.

## 输入格式

The first line of input contain 2 integer numbers $ n $ and $ m $ ( $ 1 \le n, m \le 1000 $ ) — the length of the platform and the number of the squares.

The next line contain $ m $ integer numbers $ c_1, c_2, \dots, c_m $ ( $ 1 \le c_i \le n $ ) — column in which $ i $ -th square will appear.

## 输出格式

Print one integer — the amount of points you will receive.

## 说明/提示

In the sample case the answer will be equal to $ 2 $ because after the appearing of $ 6 $ -th square will be removed one row (counts of the squares on the platform will look like $ [2~ 3~ 1] $ , and after removing one row will be $ [1~ 2~ 0] $ ).

After the appearing of $ 9 $ -th square counts will be $ [2~ 3~ 1] $ , and after removing one row it will look like $ [1~ 2~ 0] $ .

So the answer will be equal to $ 2 $ .

## 样例 #1

### 输入

```
3 9
1 1 2 2 2 3 1 2 3

```

### 输出

```
2

```



---

---
title: "Football"
layout: "post"
diff: 入门
pid: CF96A
tag: ['模拟', '字符串']
---

# Football

## 题目描述

Petya loves football very much. One day, as he was watching a football match, he was writing the players' current positions on a piece of paper. To simplify the situation he depicted it as a string consisting of zeroes and ones. A zero corresponds to players of one team; a one corresponds to players of another team. If there are at least $ 7 $ players of some team standing one after another, then the situation is considered dangerous. For example, the situation $ 00100110111111101 $ is dangerous and $ 11110111011101 $ is not. You are given the current situation. Determine whether it is dangerous or not.

## 输入格式

The first input line contains a non-empty string consisting of characters "0" and "1", which represents players. The length of the string does not exceed $ 100 $ characters. There's at least one player from each team present on the field.

## 输出格式

Print "YES" if the situation is dangerous. Otherwise, print "NO".

## 样例 #1

### 输入

```
001001

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
1000000001

```

### 输出

```
YES

```



---

---
title: "Wrong Subtraction"
layout: "post"
diff: 入门
pid: CF977A
tag: ['模拟', '字符串', '栈']
---

# Wrong Subtraction

## 题目描述

Little girl Tanya is learning how to decrease a number by one, but she does it wrong with a number consisting of two or more digits. Tanya subtracts one from a number by the following algorithm:

- if the last digit of the number is non-zero, she decreases the number by one;
- if the last digit of the number is zero, she divides the number by 10 (i.e. removes the last digit).

You are given an integer number $ n $ . Tanya will subtract one from it $ k $ times. Your task is to print the result after all $ k $ subtractions.

It is guaranteed that the result will be positive integer number.

## 输入格式

The first line of the input contains two integer numbers $ n $ and $ k $ ( $ 2 \le n \le 10^9 $ , $ 1 \le k \le 50 $ ) — the number from which Tanya will subtract and the number of subtractions correspondingly.

## 输出格式

Print one integer number — the result of the decreasing $ n $ by one $ k $ times.

It is guaranteed that the result will be positive integer number.

## 说明/提示

The first example corresponds to the following sequence: $ 512 \rightarrow 511 \rightarrow 510 \rightarrow 51 \rightarrow 50 $ .

## 样例 #1

### 输入

```
512 4

```

### 输出

```
50

```

## 样例 #2

### 输入

```
1000000000 9

```

### 输出

```
1

```



---

---
title: "Game"
layout: "post"
diff: 入门
pid: CF984A
tag: ['模拟', '排序']
---

# Game

## 题目描述

Two players play a game.

Initially there are $ n $ integers $ a_1, a_2, \ldots, a_n $ written on the board. Each turn a player selects one number and erases it from the board. This continues until there is only one number left on the board, i. e. $ n - 1 $ turns are made. The first player makes the first move, then players alternate turns.

The first player wants to minimize the last number that would be left on the board, while the second player wants to maximize it.

You want to know what number will be left on the board after $ n - 1 $ turns if both players make optimal moves.

## 输入格式

The first line contains one integer $ n $ ( $ 1 \le n \le 1000 $ ) — the number of numbers on the board.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^6 $ ).

## 输出格式

Print one number that will be left on the board.

## 说明/提示

In the first sample, the first player erases $ 3 $ and the second erases $ 1 $ . $ 2 $ is left on the board.

In the second sample, $ 2 $ is left on the board regardless of the actions of the players.

## 样例 #1

### 输入

```
3
2 1 3

```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
2 2 2

```

### 输出

```
2
```



---

---
title: "Diverse Team"
layout: "post"
diff: 入门
pid: CF988A
tag: ['模拟', '贪心', '概率论']
---

# Diverse Team

## 题目描述

给定n和k和n个元素的数列，请在这个数列中找k个不同的元素。
如果可行，则输出“YES”和其中一个答案（可能有多个答案）的元素编号。
否则输出“NO”。


感谢@南方不败 提供翻译

## 输入格式

第一行n和k，第二行n个数。

## 样例 #1

### 输入

```
5 3
15 13 15 15 12

```

### 输出

```
YES
1 2 5 

```

## 样例 #2

### 输入

```
5 4
15 13 15 15 12

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
4 4
20 10 40 30

```

### 输出

```
YES
1 2 3 4 

```



---

