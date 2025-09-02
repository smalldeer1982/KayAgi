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
title: "Nearly Lucky Number"
layout: "post"
diff: 入门
pid: CF110A
tag: ['字符串', '概率论', '位运算']
---

# Nearly Lucky Number

## 题目描述

### 题目要求
如果一个数仅包含4和7，那么它就是一个"幸运数字"。
如果一个数**本身不是**幸运数，但是它所含有的数字4和7的个数之和为一个"幸运数字"，那么它就是一个"类幸运数字"。
给您一个数，请编程判断它是不是"类幸运数字"。

## 输入格式

一行一个整数N(N在64位整数(long long / int64)范围内)。

## 输出格式

一行一个字符串，如果N是"类幸运数字"则输出"YES"，否则输出"NO"。

感谢@PC_DOS 提供翻译

## 样例 #1

### 输入

```
40047

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
7747774

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
1000000000000000000

```

### 输出

```
NO

```



---

---
title: "Cookies"
layout: "post"
diff: 入门
pid: CF129A
tag: ['字符串', '数学', '概率论']
---

# Cookies

## 输出格式

感谢@面瘫者 提供的翻译

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
10
1 2 2 3 4 4 4 2 2 2

```

### 输出

```
8

```

## 样例 #3

### 输入

```
11
2 2 2 2 2 2 2 2 2 2 99

```

### 输出

```
1

```



---

---
title: "cAPS lOCK"
layout: "post"
diff: 入门
pid: CF131A
tag: ['字符串', '概率论']
---

# cAPS lOCK

## 题目描述

wHAT DO WE NEED cAPS LOCK FOR?

Caps lock is a computer keyboard key. Pressing it sets an input mode in which typed letters are capital by default. If it is pressed by accident, it leads to accidents like the one we had in the first passage.

Let's consider that a word has been typed with the Caps lock key accidentally switched on, if:

- either it only contains uppercase letters;
- or all letters except for the first one are uppercase.

In this case we should automatically change the case of all letters. For example, the case of the letters that form words "hELLO", "HTTP", "z" should be changed.

Write a program that applies the rule mentioned above. If the rule cannot be applied, the program should leave the word unchanged.

## 输入格式

The first line of the input data contains a word consisting of uppercase and lowercase Latin letters. The word's length is from 1 to 100 characters, inclusive.

## 输出格式

Print the result of the given word's processing.

## 样例 #1

### 输入

```
cAPS

```

### 输出

```
Caps
```

## 样例 #2

### 输入

```
Lock

```

### 输出

```
Lock

```



---

---
title: "Business trip"
layout: "post"
diff: 入门
pid: CF149A
tag: ['贪心', '排序', '概率论']
---

# Business trip

## 题目描述

多么令人开心啊！Petya的父母去了一个长达一年的商业旅行并且把这个爱玩的孩子独自留下了。Petya高兴到了极点。他跳上床并扔了一整天的枕头，直到...
（这和做题有什么关系，汗）

今天Petya打开橱柜发现了一个吓人的字条。他的父母给他留了家务：他应该给他们最喜爱的花浇一整年的水，每一天，无论早上，下午，还是晚上。“等一下”——Petya想。他明白一个事实，如果他在一年中的第$i$月（$1\leq i\leq12$）完成父母的任务，这个花就会生长$a_i$厘米，并且如果他在第$i$月不给花浇水，花在这个月就不会长。他的父母不会相信他给花浇过水了，如果这花生长的严格少于$k$厘米。

帮助Petya选择最少的月数浇花，使得这花能够长得不少于$k$厘米。

## 输入格式

第一行正好包含一个整数$k$（$0\leq k\leq100$）。下一行包含十二个整数：第$i$个数代表$a_i$（$0\leq a_i\leq100$）

## 输出格式

输出的仅仅一个整数，表示Petya给花浇水的最少月数，使得花生长不少于$k$厘米。如果花一年不能生长$k$厘米，输出$-1$。

## 说明/提示

让我们考虑第一个样例。在第七个月和第九个月给花浇水。然后花长五厘米。

第二样例Petya的父母会相信他，即使花不生长（$k=0$ ）。所以，Petya可能根本不浇花。

Translated by @Khassar

## 样例 #1

### 输入

```
5
1 1 1 1 2 2 3 2 2 1 1 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
0
0 0 0 0 0 0 0 1 1 2 3 0

```

### 输出

```
0

```

## 样例 #3

### 输入

```
11
1 1 4 1 1 5 1 1 4 1 1 1

```

### 输出

```
3

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
title: "Second Order Statistics"
layout: "post"
diff: 入门
pid: CF22A
tag: ['搜索', '排序', '概率论']
---

# Second Order Statistics

## 题目描述

### 题面描述

给定一个数组，输出其中第二小的整数（相等的整数只计算一次）。

## 输入格式

第一行，一个整数 $n$（$1 \leq n \leq 100$），表示数组长度。

第二行，$n$ 个绝对值小于 $100$ 的整数。

## 输出格式

一行。如果该数组存在第二小整数，则输出第二小整数。如果不存在，则输出`NO`。

## 样例 #1

### 输入

```
4
1 2 2 -4

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5
1 2 3 1 1

```

### 输出

```
2

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
title: "Helpful Maths"
layout: "post"
diff: 入门
pid: CF339A
tag: ['字符串', '排序', '概率论']
---

# Helpful Maths

## 题目描述

Xenia the beginner mathematician is a third year student at elementary school. She is now learning the addition operation.

The teacher has written down the sum of multiple numbers. Pupils should calculate the sum. To make the calculation easier, the sum only contains numbers 1, 2 and 3. Still, that isn't enough for Xenia. She is only beginning to count, so she can calculate a sum only if the summands follow in non-decreasing order. For example, she can't calculate sum 1+3+2+1 but she can calculate sums 1+1+2 and 3+3.

You've got the sum that was written on the board. Rearrange the summans and print the sum in such a way that Xenia can calculate the sum.

## 输入格式

The first line contains a non-empty string $ s $ — the sum Xenia needs to count. String $ s $ contains no spaces. It only contains digits and characters "+". Besides, string $ s $ is a correct sum of numbers 1, 2 and 3. String $ s $ is at most 100 characters long.

## 输出格式

Print the new sum that Xenia can count.

## 样例 #1

### 输入

```
3+2+1

```

### 输出

```
1+2+3

```

## 样例 #2

### 输入

```
1+1+3+1+3

```

### 输出

```
1+1+1+3+3

```

## 样例 #3

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
title: "123-sequence"
layout: "post"
diff: 入门
pid: CF52A
tag: ['数学', '贪心', '概率论']
---

# 123-sequence

## 题目描述

There is a given sequence of integers $ a_{1},a_{2},...,a_{n} $ , where every number is from 1 to 3 inclusively. You have to replace the minimum number of numbers in it so that all the numbers in the sequence are equal to each other.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=10^{6} $ ). The second line contains a sequence of integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=3 $ ).

## 输出格式

Print the minimum number of replacements needed to be performed to make all the numbers in the sequence equal.

## 说明/提示

In the example all the numbers equal to 1 and 3 should be replaced by 2.

## 样例 #1

### 输入

```
9
1 3 2 2 2 1 1 2 3

```

### 输出

```
5

```



---

---
title: "Soldier and Bananas"
layout: "post"
diff: 入门
pid: CF546A
tag: ['字符串', '数学', '概率论']
---

# Soldier and Bananas

## 题目描述

A soldier wants to buy $ w $ bananas in the shop. He has to pay $ k $ dollars for the first banana, $ 2k $ dollars for the second one and so on (in other words, he has to pay $ i·k $ dollars for the $ i $ -th banana).

He has $ n $ dollars. How many dollars does he have to borrow from his friend soldier to buy $ w $ bananas?

## 输入格式

The first line contains three positive integers $ k,n,w $ ( $ 1<=k,w<=1000 $ , $ 0<=n<=10^{9} $ ), the cost of the first banana, initial number of dollars the soldier has and number of bananas he wants.

## 输出格式

Output one integer — the amount of dollars that the soldier must borrow from his friend. If he doesn't have to borrow money, output $ 0 $ .

## 样例 #1

### 输入

```
3 17 4

```

### 输出

```
13
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
title: "Text Volume"
layout: "post"
diff: 入门
pid: CF837A
tag: ['字符串', '概率论']
---

# Text Volume

## 题目描述

You are given a text of single-space separated words, consisting of small and capital Latin letters.

Volume of the word is number of capital letters in the word. Volume of the text is maximum volume of all words in the text.

Calculate the volume of the given text.

## 输入格式

The first line contains one integer number $ n $ ( $ 1<=n<=200 $ ) — length of the text.

The second line contains text of single-space separated words $ s_{1},s_{2},...,s_{i} $ , consisting only of small and capital Latin letters.

## 输出格式

Print one integer number — volume of text.

## 说明/提示

In the first example there is only one word, there are 5 capital letters in it.

In the second example all of the words contain 0 capital letters.

## 样例 #1

### 输入

```
7
NonZERO

```

### 输出

```
5

```

## 样例 #2

### 输入

```
24
this is zero answer text

```

### 输出

```
0

```

## 样例 #3

### 输入

```
24
Harbour Space University

```

### 输出

```
1

```



---

---
title: "Generous Kefa"
layout: "post"
diff: 入门
pid: CF841A
tag: ['概率论']
---

# Generous Kefa

## 题目描述

读入一个字符串（都是小写字母），让你求出里边最多的一种字母的个数是否小于等于 $k$。，若大于输出"NO",否则输出"YES"。   
第二行为一个字符串。

## 样例 #1

### 输入

```
4 2
aabb

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
6 3
aacaab

```

### 输出

```
NO

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
title: "Find Extra One"
layout: "post"
diff: 入门
pid: CF900A
tag: ['概率论']
---

# Find Extra One

## 题目描述

# 题目简述
平面直角坐标系上有n个点，它们都不在y轴上。现在请你检查是否可以去掉一个点，使所有点都位于y轴的同一边。

## 输入格式

第一行为n。（2<=n<=100000）

接下来为n行Xi和Yi(Xi,Yi的绝对值<=1000000000,Xi!=0)，没有任意两点重合。

## 输出格式

如果可以去掉一个点使所有点位于y轴同一边，输出“Yes”，反之输出“No”。

大写小写都可以。

## 说明/提示

第一个样例中，删除第二个点。

第二个样例中，无法达到目标。

第三个样例中，随便删除一个点都可以。

## 样例 #1

### 输入

```
3
1 1
-1 -1
2 -1

```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
4
1 1
2 2
-1 1
-2 2

```

### 输出

```
No
```

## 样例 #3

### 输入

```
3
1 2
2 1
4 60

```

### 输出

```
Yes
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
title: "Olympiad"
layout: "post"
diff: 入门
pid: CF937A
tag: ['素数判断,质数,筛法', '概率论']
---

# Olympiad

## 题目描述

题意：

现在有n个人，每个人都有一些分数（0<=a[i]<=600）,你要做的是统计有多少种分数（0和重复的都不算）。

## 输入格式

第一行：一个n，接下来的一行里有n个数。

## 输出格式

输出分数的种类。

感谢 @（T_T）   提供的翻译。

## 样例 #1

### 输入

```
4
1 3 3 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3
1 1 1

```

### 输出

```
1

```

## 样例 #3

### 输入

```
4
42 0 0 42

```

### 输出

```
1

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
title: "Minimum Binary Number"
layout: "post"
diff: 入门
pid: CF976A
tag: ['字符串', '概率论']
---

# Minimum Binary Number

## 题目描述

给定一个二进制数（没有多余前导0），可以对这个二进制数执行两种操作：

1. 交换相邻数位的数字；
2. 用 1 代替 11（例如 110 变成 10）。

输出执行任意操作（或者不操作）后这些二进制数中最小的二进制数。

## 输入格式

第一行，一个数 n，表示这个二进制数的长度；

第二行，一个二进制数 s。

## 输出格式

执行任意操作后最小的二进制数；

## 样例解释

样例一解释：1001->1010->1100->100

样例二解释：不用操作

## 样例 #1

### 输入

```
4
1001

```

### 输出

```
100

```

## 样例 #2

### 输入

```
1
1

```

### 输出

```
1

```



---

---
title: "Infinity Gauntlet"
layout: "post"
diff: 入门
pid: CF987A
tag: ['字符串', '概率论']
---

# Infinity Gauntlet

## 题目描述

# 题目大意
你偷看了Thanos的无尽手套，手套上有6颗无限宝石：
- the **Power** Gem of **purple** color, 紫色的力量宝石
- the **Time** Gem of **green** color, 绿色的时间宝石
- the **Space** Gem of **blue** color, 蓝色的空间宝石
- the **Soul** Gem of **orange** color, 橙色的灵魂宝石
- the **Reality** Gem of **red** color, 红色的现实宝石
- the **Mind** Gem of **yellow** color. 黄色的心灵宝石

现在给出你偷看到的宝石的**颜色**，请你确定缺少了哪些宝石（**名称**）

## 输入格式

第一行一个整数 $n(0≤n≤6)$ ,表示你看到的宝石数量

下面 $n$ 行，每行一个字符串，表示你看到宝石的颜色，所有字符串都是小写的。

## 输出格式

第一行一个整数 $m(0≤m≤6)$ ，表示缺少的宝石的个数

下面 $m$ 行，每行一个宝石的**名字**，顺序随意，**名字首字母要记得大写，其他小写**。

感谢@二元长天笑 提供的翻译

## 样例 #1

### 输入

```
4
red
purple
yellow
orange

```

### 输出

```
2
Space
Time

```

## 样例 #2

### 输入

```
0

```

### 输出

```
6
Time
Space
Power
Reality
Mind
Soul

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

---
title: "A Blend of Springtime"
layout: "post"
diff: 入门
pid: CF989A
tag: ['概率论']
---

# A Blend of Springtime

## 题目描述

**题目大意：**

给定一个由'A','B','C','.'构成的字符串，'A''B''C'控制左中右三个位置，问是否存在一个位置'A''B''C'同时控制

## 输入格式

一个字符串

## 输出格式

如果满足条件，输出"Yes"，否则输出"No"

感谢@守望 提供翻译

## 样例 #1

### 输入

```
.BAC.

```

### 输出

```
Yes

```

## 样例 #2

### 输入

```
AA..CB

```

### 输出

```
No

```



---

