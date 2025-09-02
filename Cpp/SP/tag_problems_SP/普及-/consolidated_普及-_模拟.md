---
title: "JAVAC - Java vs C &#43&#43"
layout: "post"
diff: 普及-
pid: SP1163
tag: ['模拟']
---

# JAVAC - Java vs C &#43&#43

## 题目描述

Apologists of Java and C++ can argue for hours proving each other that their programming language is the best one. Java people will tell that their programs are clearer and less prone to errors, while C++ people will laugh at their inability to instantiate an array of generics or tell them that their programs are slow and have long source code.

  
 Another issue that Java and C++ people could never agree on is identifier naming. In Java a multiword identifier is constructed in the following manner: the first word is written starting from the small letter, and the following ones are written starting from the capital letter, no separators are used. All other letters are small. Examples of a Java identifier are javaIdentifier, longAndMnemonicIdentifier, name, nEERC.

  
 Unlike them, C++ people use only small letters in their identifiers. To separate words they use underscore character ‘\_’. Examples of C++ identifiers are c\_identifier, long\_and\_mnemonic\_identifier, name (you see that when there is just one word Java and C++ people agree), n\_e\_e\_r\_c.

  
 You are writing a translator that is intended to translate C++ programs to Java and vice versa. Of course, identifiers in the translated program must be formatted due to its language rules — otherwise people will never like your translator.

  
 The first thing you would like to write is an identifier translation routine. Given an identifier, it would detect whether it is Java identifier or C++ identifier and translate it to another dialect. If it is neither, then your routine should report an error. Translation must preserve the order of words and must only change the case of letters and/or add/remove underscores.

## 输入格式

The input file consists of several lines that contains an identifier. It consists of letters of the English alphabet and underscores. Its length does not exceed 100.

## 输出格式

If the input identifier is Java identifier, output its C++ version. If it is C++ identifier, output its Java version. If it is none, output 'Error!' instead.

## 样例 #1

### 输入

```
long_and_mnemonic_identifier

anotherExample

i

bad_Style
```

### 输出

```
longAndMnemonicIdentifier

another_example

i

Error!
```



---

---
title: "ULM02 - The Sierpinski Fractal"
layout: "post"
diff: 普及-
pid: SP15728
tag: ['模拟', '递归']
---

# ULM02 - The Sierpinski Fractal

## 题目描述

Consider a regular triangular area, divide it into four equal triangles of half height and remove the one in the middle. Apply the same operation recursively to each of the three remaining triangles. If we repeated this procedure infinite times, we'd obtain something with an area of zero. The fractal that evolves this way is called the Sierpinski Triangle. Although its topological dimension is _2_, its Hausdorff-Besicovitch dimension is_log(3)/log(2)~1.58_, a fractional value (that's why it is called a fractal). By the way, the Hausdorff-Besicovitch dimension of the Norwegian coast is approximately _1.52_, its topological dimension being _1_.

For this problem, you are to outline the Sierpinski Triangle up to a certain recursion depth, using just ASCII characters. Since the drawing resolution is thus fixed, you'll need to grow the picture appropriately. Draw the smallest triangle (that is not divided any further) with two slashes, to backslashes and two underscores like this:

 /\\



---

---
title: "PRIME1 - Prime Generator"
layout: "post"
diff: 普及-
pid: SP2
tag: ['模拟', '枚举', '素数判断,质数,筛法']
---

# PRIME1 - Prime Generator

## 题目描述

 Peter wants to generate some prime numbers for his cryptosystem. Help him! Your task is to generate all prime numbers between two given numbers!

## 输入格式

 The input begins with the number t of test cases in a single line (t<=10). In each of the next t lines there are two numbers m and n (1 <= m <= n <= 1000000000, n-m<=100000) separated by a space.

## 输出格式

For every test case print all prime numbers p such that m <= p <= n, one number per line, test cases separated by an empty line.

## 说明/提示

**Warning: large Input/Output data, be careful with certain languages (though most should be OK if the algorithm is well designed)**   
Information
-----------

 After cluster change, please consider [PRINT](http://www.spoj.com/problems/PRINT/) as a more challenging problem.

## 样例 #1

### 输入

```
2
1 10
3 5
```

### 输出

```
2
3
5
7

3
5
```



---

---
title: "SBANK - Sorting Bank Accounts"
layout: "post"
diff: 普及-
pid: SP27
tag: ['模拟', '字符串', '排序']
---

# SBANK - Sorting Bank Accounts

## 题目描述

 In one of the internet banks thousands of operations are being performed every day. Since certain customers do business more actively than others, some of the bank accounts occur many times in the list of operations. Your task is to sort the bank account numbers in ascending order. If an account appears twice or more in the list, write the number of repetitions just after the account number. The format of accounts is as follows: **2** control digits, an **8**-digit code of the bank, **16** digits identifying the owner (written in groups of four digits), for example (at the end of each line there is exactly one space):

**30 10103538 2222 1233 6160 0142**  **Banks are real-time institutions and they need FAST solutions. If you feel you can meet the challenge within a very stringent time limit, go ahead!** A well designed sorting algorithm in a fast language is likely to succeed.

## 输入格式

   
_t_ \[the number of tests <= **5**\]   
_n_ \[the number of accounts<= **100 000**\]   
\[list of accounts\]   
\[empty line\]   
\[next test cases\]

## 输出格式

   
\[sorted list of accounts with the number of repeated accounts\]   
\[empty line\]   
\[other results\]

## 样例 #1

### 输入

```
2
6
03 10103538 2222 1233 6160 0142 
03 10103538 2222 1233 6160 0141 
30 10103538 2222 1233 6160 0141 
30 10103538 2222 1233 6160 0142 
30 10103538 2222 1233 6160 0141 
30 10103538 2222 1233 6160 0142 

5
30 10103538 2222 1233 6160 0144 
30 10103538 2222 1233 6160 0142 
30 10103538 2222 1233 6160 0145 
30 10103538 2222 1233 6160 0146 
30 10103538 2222 1233 6160 0143
```

### 输出

```
03 10103538 2222 1233 6160 0141 1
03 10103538 2222 1233 6160 0142 1
30 10103538 2222 1233 6160 0141 2
30 10103538 2222 1233 6160 0142 2

30 10103538 2222 1233 6160 0142 1
30 10103538 2222 1233 6160 0143 1
30 10103538 2222 1233 6160 0144 1
30 10103538 2222 1233 6160 0145 1
30 10103538 2222 1233 6160 0146 1
```



---

---
title: "ARMY - Army Strength"
layout: "post"
diff: 普及-
pid: SP2727
tag: ['模拟']
---

# ARMY - Army Strength

## 题目描述

The next MechaGodzilla invasion is on its way to Earth. And once again, Earth will be the battleground for an epic war.

MechaGodzilla's army consists of many nasty alien monsters, such as Space Godzilla, King Gidorah, and MechaGodzilla herself.

To stop them and defend Earth, Godzilla and her friends are preparing for the battle.

## 样例 #1

### 输入

```
2

1 1
1
1

3 2
1 3 2
5 5
```

### 输出

```
Godzilla
MechaGodzilla
```



---

---
title: "CNTDO - Count Doubles"
layout: "post"
diff: 普及-
pid: SP27303
tag: ['模拟']
---

# CNTDO - Count Doubles

## 题目描述

给你一个整数数组，您的任务是确定数组中的某个整数是同一数组中其他整数的两倍的数的个数。例如，考虑一个数组 $a=\{1,3,4,7,9,2,18\}$，答案是 $3$，因为 $2$ 是 $1$ 的两倍，$4$ 是 $2$ 的两倍， $18$ 是 $9$ 的两倍。

## 输入格式

第一行一个整数 $T$（$T\leq1000$），表示数据组数。  
每组数据包含两行：  
第一行一个整数 $N$（$1\leq N\leq 1000$），表示给定数组中不同整数的数量。  
第二行包含 $N$ 个整数，每个整数的绝对值不大于 $10000$。

## 输出格式

共一行，输出是其他整数的两倍的整数的个数。  

翻译 By [wangzl](https://www.luogu.com.cn/user/222039)



---

---
title: "ONP - Transform the Expression"
layout: "post"
diff: 普及-
pid: SP4
tag: ['模拟', '递归', '栈']
---

# ONP - Transform the Expression

## 题目描述

请你将 $n$ 个中缀表达式转换为后缀表达式。

## 输入格式

第一行一个整数 $n$ 代表中缀表达式个数。

接下来 $n$ 行代表 $n$ 个中缀表达式。

## 输出格式

$n$ 行代表每个中缀表达式转换过来的后缀表达式。

## 说明/提示

对于 $100\%$ 的数据，$n \le 100$ , 表达式长度 $\le 400$ 。

Translated by @[稀神探女](/user/85216)

## 样例 #1

### 输入

```
3

(a+(b*c))

((a+b)*(z+x))

((a+t)*((b+(a+c))^(c+d)))
```

### 输出

```
abc*+

ab+zx+*

at+bac++cd+^*
```



---

---
title: "ANARC07C - Rotating Rings"
layout: "post"
diff: 普及-
pid: SP4568
tag: ['模拟']
---

# ANARC07C - Rotating Rings

## 题目描述

任何方形网格都可以看作一个或多个环，一个套在一个里面。例如，如图 (a) 所示，一个 5 x 5 的网格由三个环组成，编号为 1、2 和 3（从外到内）。一个大小为 $N$ 的方形网格被称为有序的，如果它包含从 1 到 $N^2$ 的值，并且按行优先顺序排列，如图 (b) 所示，其中 $N = 4$。我们希望确定给定的方形网格是否可以通过仅旋转其环来排序。例如，图 (c) 中的网格可以通过将第一个环逆时针旋转两个位置，并将第二个环顺时针旋转一个位置来排序。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/SP4568/de2efad7acfbae02d1e24e4c5bae5c3fbd72210c.png)

## 输入格式

你的程序将被测试在一个或多个测试用例上。每个测试用例的第一行是一个整数 $N$，表示网格的大小。接下来有 $N$ 行，每行包含 $N$ 个整数值，按行优先顺序指定网格中的值。注意 $0 < N \leq 1000$。

测试用例以一个虚拟测试用例结束，该测试用例的 $N = 0$。

## 输出格式

对于每个测试用例，在单独的一行上输出结果，使用以下格式：

`k. 结果`

其中 $k$ 是测试用例编号（从 1 开始），结果是 "YES" 或 "NO"（不带双引号），并且在 "." 和 "结果" 之间有一个空格。

## 样例

```
输入
4
9 5 1 2
13 7 11 3
14 6 10 4
15 16 12 8
3
1 2 3
5 6 7
8 9 4
0

输出
1. YES
2. NO
```



---

---
title: "GLJIVE - GLJIVE"
layout: "post"
diff: 普及-
pid: SP8319
tag: ['模拟', '前缀和']
---

# GLJIVE - GLJIVE

## 题目描述

 In front of Super Mario there are **10 mushrooms**, arranged in a row. A certain amount of points is awarded for picking each of the mushrooms. Super Mario must pick mushrooms **in order** they appear, but is not required to pick them all – his goal is to score a number of points **as close as possible to 100**.

In case there exist two such numbers which are equally close to 100 (e.g. 98 and 102), Mario will pick the **greater** one (in this case 102).

Help Super Mario and tell him how many points he will score.

## 输入格式

Input consists of 10 lines, each of which contains one positive integer less than or equal to 100, denoting the scores awarded for picking each mushroom, in the order that Mario can pick them in.

## 输出格式

The first and only line of output must contain the required number of points.

## 样例 #1

### 输入

```
10

20

30

40

50

60

70

80

90

100
```

### 输出

```
100
```



---

---
title: "NY10A - Penney Game"
layout: "post"
diff: 普及-
pid: SP8612
tag: ['模拟', '字符串']
---

# NY10A - Penney Game

## 题目描述

Penney’s game is a simple game typically played by two players. One version of the game calls for each player to choose a unique three-coin sequence such as **HEADS TAILS HEADS (HTH)**. A fair coin is tossed sequentially some number of times until one of the two sequences appears. The player who chose the first sequence to appear wins the game.

For this problem, you will write a program that implements a variation on the Penney Game. You willread a sequence of 40 coin tosses and determine how many times each three-coin sequence appears. Obviously there are eight such three-coin sequences: **TTT**, **TTH**, **THT**, **THH**, **HTT**, **HTH**, **HHT** and **HHH**. Sequences may overlap. For example, if all 40 coin tosses are heads, then the sequence HHH appears 38 times.

## 输入格式

The first line of input contains a single integer P, (1

## 输出格式

For each data set there is one line of output. It contains the data set number followed by a single space, followed by the number of occurrences of each three-coin sequence, in the order shown above, with a space between each one. There should be a total of 9 space separated decimal integers on each output line.

## 样例 #1

### 输入

```
\n4\n1\nHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n2\nTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT\n3\nHHTTTHHTTTHTHHTHHTTHTTTHHHTHTTHTTHTTTHTH\n4\nHTHTHHHTHHHTHTHHHHTTTHTTTTTHHTTTTHTHHHHT\n\n
```

### 输出

```
\n1 0 0 0 0 0 0 0 38\n2 38 0 0 0 0 0 0 0\n3 4 7 6 4 7 4 5 1\n4 6 3 4 5 3 6 5 6
```



---

