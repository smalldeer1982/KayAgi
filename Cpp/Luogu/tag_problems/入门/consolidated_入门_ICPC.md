---
title: "[NERC 2020 Online] Kate' s 2021 Celebration"
layout: "post"
diff: 入门
pid: P12860
tag: ['模拟', '2020', 'Special Judge', 'O2优化', '排序', 'ICPC', 'NERC/NEERC', 'STL']
---
# [NERC 2020 Online] Kate' s 2021 Celebration
## 题目描述

Kate did not have a good year 2020 and she is glad that it is coming to an end. She is planning to celebrate New Year 2021 on a grand scale. 

Kate has decided to buy four balloons with digits $\texttt{2} \texttt{0} \texttt{2} \texttt{1}$ painted on them for her 2021 celebration. She went to a store's web site and has found that balloons with digits are sold in packs containing different assortments of balloons of various sizes, colors, and with different digits painted on them. Kate does not care about their size, color, or other attributes. She only cares about digits written on those balloons. Fortunately, the store has all the information about different packs of balloons that are available. Kate has managed to retrieve it through the store's REST API and extracted just the information she needs --- the price and the digits that are written on balloons in each pack. 

Please, help Kate with the final task of figuring out what is the cheapest pack of balloons she can buy that would get her the four digits she needs for her 2021 celebration.
## 输入格式

The first line of the input file contains an integer $n$ ($1 \le n \le 1000$) --- the number of packs of balloons available in the store.  

The next $n$ lines contain descriptions of packs, one line per pack. Each pack is described by an integer $p$ ($1 \le p \le 10^5$) --- the price of the pack in roubles, followed by a string of at least one and at most $100$ digits (each digit is from $\texttt{0}$to $\texttt{9}$) --- the digits on the balloons in the pack.
## 输出格式

Output a single integer --- the number of the cheapest pack that Kate can buy to get the digits for her $2021$ celebration. Packs of balloons are numbered starting from $1$ in the order they are given in the input. If there are multiple packs with the same price, output any one of them.

Output $0$ if there is no pack in the store that Kate can buy for her 2021 celebration.
## 样例

### 样例输入 #1
```
4
100 9876543210
200 00112233445566778899
160 012345678924568
150 000000123456789
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
5
100 0123456789
120 0022446688
200 00224466883456789
10 0
10 1
```
### 样例输出 #2
```
0
```
## 提示

In the first example, 2nd and 3rd packs of balloons contain digits $\texttt{2} \texttt{0} \texttt{2} \texttt{1}$ and the 3rd one is the cheapest.


---

---
title: "[NWRRC 2022] Absolutely Flat"
layout: "post"
diff: 入门
pid: P13598
tag: ['2022', 'ICPC', 'NWRRC']
---
# [NWRRC 2022] Absolutely Flat
## 题目描述

Alice is a proud owner of a four-legged table, and she wants her table to be flat. Alice considers the table to be flat if its four legs have equal lengths. 

Alice measured the table's current leg lengths and got $a_1, a_2, a_3$, and $a_4$. She also has a pad of length $b$. Alice can attach the pad to one of the legs, in which case the length of that leg will increase by $b$. She can also decide not to attach the pad, in which case the lengths of the legs will not change. Note that Alice has just a single pad, so she can neither apply it twice to the same leg nor apply it to two different legs.

Find out whether Alice can make her table flat.

## 输入格式

The input contains five positive integers $a_1, a_2, a_3, a_4$, and $b$, each on a separate line --- the lengths of the table's legs, and the length of the pad Alice has ($1 \le a_i, b \le 100$).
## 输出格式

Print $1$ if Alice can make her table flat, and $0$ otherwise.
## 样例

### 样例输入 #1
```
10
10
10
10
5
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
13
13
5
13
8
```
### 样例输出 #2
```
1
```
### 样例输入 #3
```
50
42
42
50
8
```
### 样例输出 #3
```
0
```
### 样例输入 #4
```
20
40
10
30
2
```
### 样例输出 #4
```
0
```
## 提示

In the first example test, the table is already flat, no pad is needed.

In the second example test, Alice can apply the pad to the third leg to make the table flat.

In the third and the fourth example tests, Alice can not make her table flat.


---

---
title: "[NWRRC 2021] Anno Domini 2022"
layout: "post"
diff: 入门
pid: P13628
tag: ['2021', 'ICPC', 'NWRRC']
---
# [NWRRC 2021] Anno Domini 2022
## 题目描述

Soon we will celebrate New Year 2022, but what does this number mean? As you possibly know, this dating system was invented in AD 525 by Dionysius Exiguus. He chose the birth of Jesus Christ as the starting point of the Years of Our Lord (Anno Domini in Latin, AD for short). All the years before that were counted backwards as years Before Christ (BC for short). 

An interesting detail of this dating system is that there is no year 0 --- year 1 BC is immediately followed by AD 1. Because of that, sometimes it is quite tricky to find time difference between two dates if these dates belong to two different eras.

To simplify this task, please write a program that computes how many years passed between January 1st of two years given in the input.
## 输入格式

Two years are specified on two sequential input lines. Each year is specified in one of two forms:
- as letters $\tt{AD}$, followed by a space and a positive integer without leading zeroes in range $1..9999$;
- as a positive integer without leading zeroes in range $1..9999$, followed by a space and letters $\tt{BC}$.

The years may be specified in arbitrary order --- the earlier year is not necessarily given first.
## 输出格式

The only line of the output must contain one integer: the number of years that passed between January 1st of the earlier year and January 1st of the later year.
## 样例

### 样例输入 #1
```
1 BC
AD 1
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
AD 1
AD 2001
```
### 样例输出 #2
```
2000
```
### 样例输入 #3
```
AD 2022
5508 BC
```
### 样例输出 #3
```
7529
```


---

---
title: "[GCPC 2023] Eszett"
layout: "post"
diff: 入门
pid: P13670
tag: ['模拟', '字符串', '2023', 'Special Judge', '枚举', 'ICPC']
---
# [GCPC 2023] Eszett
## 题目描述

For those trying to learn German, the letter 'ß', called *Eszett* or *sharp S*,
is usually a source of great confusion.
This letter is unique to the German language and it looks similar to a 'b' but is pronounced like an 's'.

![](https://cdn.luogu.com.cn/upload/image_hosting/u376ek1e.png)

:::align{center}
Ademonstration of the $\texttt{upper}$ function in Python
:::

Adding to the confusion is the fact that, until a few years ago, only a lowercase version of 'ß' existed in standard German orthography.
Wherever an uppercase 'ß' was needed, for example in legal documents and shop signs,
it was (and usually still is) replaced by capital double letters 'SS'.
In 2017, the capital 'ẞ' was officially introduced into the German language and may now be used in those scenarios, instead.

Other than being confusing for foreigners, the practice of replacing 'ß' with
'SS' also introduces some ambiguity because a given uppercase word
featuring one or more occurrences of 'SS' may correspond to multiple different
lowercase words, depending on whether each 'SS' is a capitalized 'ß' or 'ss'.

Given one uppercase word, find all the lowercase words that it could be derived from.
As the letter 'ß' is not part of the ASCII range,
please write an uppercase 'B', instead.

## 输入格式

The input consists of:
- One line with a string $s$ ($1 \le |s| \le 20$) consisting of uppercase letters.

It is guaranteed that the letter $\texttt{S}$ occurs at most three times in $s$. Note that $s$ need not be an actual German word.
## 输出格式

Output all the possible lowercase strings corresponding to $s$. Any order will be accepted, but each string must occur exactly once.
## 样例

### 样例输入 #1
```
AUFREISSEN
```
### 样例输出 #1
```
aufreissen
aufreiBen
```
### 样例输入 #2
```
MASSSTAB
```
### 样例输出 #2
```
massstab
maBstab
masBtab
```
### 样例输入 #3
```
EINDEUTIG
```
### 样例输出 #3
```
eindeutig
```
### 样例输入 #4
```
S
```
### 样例输出 #4
```
s
```
### 样例输入 #5
```
STRASSE
```
### 样例输出 #5
```
strasse
straBe
```


---

---
title: "[NEERC 2013] Fraud Busters"
layout: "post"
diff: 入门
pid: P7001
tag: ['2013', 'ICPC']
---
# [NEERC 2013] Fraud Busters
## 题目描述



The number of cars in Default City that travel to the city center daily vastly exceeds the number of available parking spots. The City Council had decided to introduce parking fees to combat the problem of overspill parking on the city streets. Parking fees are enforced using an automated vehicle registration plate scanners that take a picture of the vehicle registration plate, recognize the sequence of digits and letters in the code on the plate, and check the code against a vehicle registration database to ensure that parking fees are dutifully paid or to automatically issue a fine to the vehicle owner otherwise.

As soon as parking fees were introduced, a parking fee fraud had appeared. Some vehicle owners had started to close one or several digits or letters on their vehicle registration plate with pieces of paper while they park, thus making it impossible for the current version of the automated scanner to recognize their vehicle's registration code and to issue them a fine.

The Default City Council had instituted the Fraud Busters Initiative (FBI) to design a solution to prevent this kind of fraud. The overall approach that FBI had selected is to expand the number of vehicle features that scanners recognize (including features like vehicle type and color), as well as excluding from the list any vehicles that are detected to be elsewhere at this time. This information should help to identify the correct vehicle by narrowing down the search in the vehicle registration database.

You are working for FBI. Your colleagues had already written all the complex pieces of the recognition software that analyses various vehicle features and provides you with a list of registration codes that might potentially belong to a scanned car. Your task it to take this list and a recognized code from the license plate (which may be partially unrecognized) and find all the registration codes that match.


## 输入格式



The first line of the input file contains $9$ characters of the code as recognized by the scanner. Code that was recognized by the the scanner is represented as a sequence of $9$ digits, uppercase English letters, and characters $` \times ` (star).$ Star represents a digit or a letter that scanner could not recognize.

The second line of the input file contains a single integer number $n (1 \le n \le 1000)$ -- the number of vehicle registration codes from the vehicle registration database.

The following $n$ lines contain the corresponding registration codes, one code per line. Vehicle registration codes are represented as a sequence of $9$ digits and uppercase English letters. All codes on these $n$ lines of the input file are different.


## 输出格式



On the first line of the output file write a single integer $k (0 \le k \le n)$ -- the number of codes from the input file that match the code that was recognized by the scanner. The code from the scanner matches the code from the database if the characters on all the corresponding positions in the codes are equal or the character from the scanner code is $` \times `.$

On the following $k$ lines write the matching codes, one code per line, in the same order as they are given in the input file.


## 样例

### 样例输入 #1
```
A**1MP19*
4
A001MP199
E885EE098
A111MP199
KT7351TTB

```
### 样例输出 #1
```
2
A001MP199
A111MP199

```
## 提示

Time limit: 1 s, Memory limit: 128 MB. 


## 题目翻译

给定一个含未知字符的长度为9字符串，未知字符用'*'表示（不含引号）。下面给出n个长度为9字符串，如果下面输入的字符串与一开始输入的字符串除未知部分的其他部分完全相同，则该字符串符合要求。输出符合要求的字符串的数量和每个符合要求的字符串。

举例：假设一开始输入的字符串为A58**52*1,则字符串A58ZS52T1符合要求，而字符串A589992G1不符合要求


---

---
title: "[CERC2013] Bus"
layout: "post"
diff: 入门
pid: P7018
tag: ['2013', 'ICPC']
---
# [CERC2013] Bus
## 题目描述

A bus with $n$ passengers opens its door at the bus stop. Exactly half of its passengers and an additional half of a passenger get out. On the next stop, again, half of the passengers plus half of a passenger leave the bus. This goes on for $k$ stops in total. Knowing that the bus leaves the last stop empty, and that no one was hurt during the trip, determine the initial number $n$ of people in the bus.
## 输入格式

The first line of input contains the number of test cases $T$. The descriptions of the test cases follow:

The only line of each test case contains the number of stops $k$, $1 \leq k \leq 30$.
## 输出格式

For each test case, output a single line containing a single integer—the initial number of bus passengers.
## 样例

### 样例输入 #1
```
2
1
3

```
### 样例输出 #1
```
1
7

```
## 提示

Time limit: 1000 ms, Memory limit: 1048576 kB. 

 Central Europe Regional Contest (CERC) 2013
## 题目翻译

# [CERC2013] Bus

## 题面翻译

有一个数 $n$ ，定义一次操作为使 $n\rightarrow \frac{n-1}{2}$ 。已知经过了 $k$ 次操作后 $n$ 恰好为 $0$，求 $n$。
 
多测，有 $T$ 组数据，$T$ 在输入数据开头给出。 

保证 $1\leqslant k\leqslant 30$。

## 题目描述

A bus with $n$ passengers opens its door at the bus stop. Exactly half of its passengers and an additional half of a passenger get out. On the next stop, again, half of the passengers plus half of a passenger leave the bus. This goes on for $k$ stops in total. Knowing that the bus leaves the last stop empty, and that no one was hurt during the trip, determine the initial number $n$ of people in the bus.

## 输入格式

The first line of input contains the number of test cases $T$. The descriptions of the test cases follow:

The only line of each test case contains the number of stops $k$, $1 \leq k \leq 30$.

## 输出格式

For each test case, output a single line containing a single integer—the initial number of bus passengers.

## 样例 #1

### 样例输入 #1

```
2
1
3
```

### 样例输出 #1

```
1
7
```

## 提示

Time limit: 1000 ms, Memory limit: 1048576 kB. 

 Central Europe Regional Contest (CERC) 2013


---

---
title: "[NWRRC 2016] Anniversary Cake"
layout: "post"
diff: 入门
pid: P7031
tag: ['2016', 'Special Judge', 'ICPC']
---
# [NWRRC 2016] Anniversary Cake
## 题目描述



Two students, Adam and Anton, are celebrating two-year anniversary of not passing their Math $Logic exa_m.$ After very careful search in a local supermarket, they bought a rectangular cake with $integer dimensions$ and two candles.

Later in the campus Adam put the candles into different integer points of the cake and gave a knife $to Anto_n$ to cut the cake. The cut should start and end at integer points at the edges of the cake, and $it should$ not touch the candles. Also each piece should have exactly one candle at it. Please, help $Anto_n to$ find the starting and ending points of the cut.

![](https://onlinejudgeimages.s3.amazonaws.com/problem/13473/%EC%8A%A4%ED%81%AC%EB%A6%B0%EC%83%B7%202016-11-01%20%EC%98%A4%ED%9B%84%202.30.49.png)

A $7 \times 3$ cake and two candles at $(2 , 2)$ and $(3 , 2)$ .

Anton can cut this cake through $(0 , 0)$ and $(4 , 3)$ .


## 输入格式



The single line of the input contains six integers: $w , h$ -- cake dimensions; $a_{x}, a_{y}$ -- $x$ and $y coordinates$ of the first candle; $b_{x}, b_{y}$ -- the coordinates of the second candle $(3 \le w , h \le 10^{9}; 0 < a_{x}, b_{x} < w$ ; $0 < a_{y}, b_{y} < h$ ; $a_{x} ≠ b_{x}$ or $a_{y }≠ b_{y}).$


## 输出格式



Output four integers $s_{x}, s_{y}, e_{x},$ and $e_{y}$ -- the starting and ending coordinates of the cut. Both $starting and$ ending point of the cut should belong to the sides of the cake.

If there are several solutions, output any of them.


## 样例

### 样例输入 #1
```
7 3 2 2 3 2 

```
### 样例输出 #1
```
0 0 4 3

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 

spj provider:@[shenyouran](/user/137367)
## 题目翻译

有一个长方形蛋糕和两个蜡烛，蛋糕的尺寸是整数。

把两个蜡烛放在蛋糕的不同整数点上，并用一把刀来切蛋糕。切割应该在蛋糕边缘的整数点开始和结束，并且不应该接触蜡烛。此外，每件作品都应该有一支蜡烛。请找到切入的起点和终点。


---

---
title: "[NWRRC 2014] Grave"
layout: "post"
diff: 入门
pid: P7066
tag: ['2014', 'ICPC']
---
# [NWRRC 2014] Grave
## 题目描述



Gerard develops a Halloween computer game. The game is played on a rectangular graveyard with a rectangular chapel in it. During the game, the player places new rectangular graves on the graveyard. The grave should completely fit inside graveyard territory and should not overlap with the chapel. The grave may touch borders of the graveyard or the chapel.

![](https://cdn.luogu.com.cn/upload/image_hosting/qktc13ls.png)

Gerard asked you to write a program that determines whether it is possible to place a new grave of given size or there is no enough space for it.


## 输入格式



The first line of the input file contains two pairs of integers: $x_{1}, y_{1}, x_{2}, y_{2} (−10^{9} \le x_{1} < x_{2} \le 10^{9}; −10^{9} \le y_{1} < y_{2} \le 10^{9})$ — coordinates of bottom left and top right corners of the graveyard. The second line also contains two pairs of integers $x_{3}, y_{3}, x_{4}, y_{4} (x_{1} < x_{3} < x_{4} < x_{2}; y_{1} < y_{3} < y_{4} < y_{2})$ — coordinates of bottom left and top right corners of the chapel.

The third line contains two integers $w , h$ — width and height of the new grave $(1 \le w , h \le 10^{9}).$ Side with length $w$ should be placed along OX axis, side with length $h$ — along OY axis.


## 输出格式



The only line of the output file should contain single word: `Yes`, if it is possible to place the new grave, or `No`, if there is not enough space for it.


## 样例

### 样例输入 #1
```
1 1 11 8
2 3 8 6
3 2

```
### 样例输出 #1
```
Yes

```
### 样例输入 #2
```
1 1 11 8
2 3 8 6
4 3

```
### 样例输出 #2
```
No

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

在一块长方形的墓地上，有一个长方形的教堂，现在给出一个长宽已知的墓碑，墓碑不能与教堂重叠，询问这块墓地上能否放下这块墓碑。  

输入第一行两对坐标，代表墓地左下角和右上角的坐标（先 $x$ 轴再 $y$ 轴）；  
第二行也是两对坐标，代表教堂左下角和右上角的坐标（先 $x$ 轴再 $y$ 轴）（保证教堂完全在墓地内部且边缘不重叠）；  
第三行两个整数 $w$ 和 $h$，代表墓碑的长与宽，要求长度为 $w$ 的一侧必须对应 $x$ 轴，长度为 $h$ 的一侧必须对应 $y$ 轴。

输出一行一个字符串，如果放得下，输出 `Yes`，否则输出 `No`。


---

