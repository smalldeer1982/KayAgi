---
title: "[ICPC 2024 Xi'an I] Chained Lights"
layout: "post"
diff: 普及-
pid: P10565
tag: ['2024', 'O2优化', 'ICPC']
---
# [ICPC 2024 Xi'an I] Chained Lights
## 题目描述


You have $n$ lights in a row. Initially, they are all off.
    
    
    
You are going to press these $n$ lights one by one. When you press light $i$, light $i$ will switch its state, which means it will turn on if it's off and turn off if it's on, and then for every $j$ satisfied $i|j,i< j\le n$, press light $j$ once.
    
    
    
For example, if $n=4$, when you press light $1$, light $1$ will turn on, and then you will press light $2,3,4$. Since you pressed light $2$, light $2$ will turn on and you will press light $4$, which will cause light 4 to turn on. After all the operations, lights $1,2,3$ will be turned on and light $4$ is still off.
    
    
    
You will press these $n$ lights and do the operations as mentioned above one by one. After all the operations, you want to know whether light $k$ is on or off.
    
    
    
You can also use the following code to understand the meaning of the problem:

```cpp
void press(int x)
{
    light[x]^=1;
    for (int y=x+x;y<=n;y+=x) press(y);
}
for (int i=1;i<=n;i++) press(i);
```
## 输入格式


There are multiple testcases.
    
    
    
The first line contains an integer $T(1\le T\le10^5)$, which represents the number of testcases.
    
    
    
Each of the testcases contains two integers $n,k(1\le k\le n\le10^6)$ in a single line.
## 输出格式

    
    
For each testcase, if light $k$ is turned on in the end, output $\text{YES}$, otherwise output $\text{NO}$.
## 样例

### 样例输入 #1
```
2
1 1
3 2
```
### 样例输出 #1
```
YES
NO
```


---

---
title: "[NWRRC2024] Another Brick in the Wall"
layout: "post"
diff: 普及-
pid: P12105
tag: ['2024', 'ICPC', '俄罗斯西北']
---
# [NWRRC2024] Another Brick in the Wall
## 样例

### 样例输入 #1
```
7 4
```
### 样例输出 #1
```
4
```


---

---
title: "[ICPC 2022 WF] Compression"
layout: "post"
diff: 普及-
pid: P12310
tag: ['字符串', '2022', 'Special Judge', 'ICPC']
---
# [ICPC 2022 WF] Compression
## 样例

### 样例输入 #1
```
1111

```
### 样例输出 #1
```
1

```
### 样例输入 #2
```
101

```
### 样例输出 #2
```
101

```
### 样例输入 #3
```
10110

```
### 样例输出 #3
```
10

```


---

---
title: "[ICPC 2024 Yokohama R] Ribbon on the Christmas Present"
layout: "post"
diff: 普及-
pid: P12778
tag: ['2024', 'ICPC']
---
# [ICPC 2024 Yokohama R] Ribbon on the Christmas Present
## 题目背景

译自 [ICPC 2024 Yokohama Regional Contest](https://icpc.jp/2024/)。
## 题目描述

你正在准备一条彩带，用于装饰圣诞礼物盒。你计划将这条最初为白色的彩带染色，以制作出不同红色深浅的条纹图案。彩带由若干节组成，每一节都应按计划染色。

你希望用最少的染色步骤来准备这条彩带。彩带上连续的几节可以用同一种红色深浅一步染色。已经染有某种红色深浅的彩带节可以用更深色调的染料进行套染；它会被染成那种更深的色调。然而，不允许用更浅的色调进行套染。由于彩带最初是白色的，所有节都必须至少染色一次。

$$
\fcolorbox{black}{CCCCCC}{\textcolor{black}{\textsf{\,50\,}}}
\fcolorbox{black}{111111}{\textcolor{white}{\textsf{100}}}
\fcolorbox{black}{CCCCCC}{\textcolor{black}{\textsf{\,50\,}}}
\fcolorbox{black}{CCCCCC}{\textcolor{black}{\textsf{\,50\,}}}
\fcolorbox{black}{111111}{\textcolor{white}{\textsf{100}}}
\fcolorbox{black}{CCCCCC}{\textcolor{black}{\textsf{\,50\,}}}
$$

上图展示了样例 $1$ 的图案。彩带有六节，节中的数字表示要染的颜色深浅级别。数字越大表示颜色越深。这可以通过三个染色步骤完成：
1. 用深浅级别为 $50$ 的红色染料染整条彩带；
2. 然后用深浅级别为 $100$ 的更深色染料染左起第二节；
3. 用深浅级别为 $100$ 的染料染第五节。

编写一个程序，计算制作计划条纹图案所需的最少染色步骤数。
## 输入格式


仅一组数据，格式如下所示：

> $n$\
> $d_1$ $d_2$ $\cdot \cdot \cdot$ $d_n$

每个测试点以一个整数 $n$ ($1 \le n \le 100$) 开始，表示彩带的节数。第二行包含 $n$ 个整数，$d_1,d_2,\ldots ,d_n$，描述了这 $n$ 节彩带计划的深浅级别。其中，$d_i$ 表示第 $i$ 节彩带计划的深浅级别，其值介于 $1$ 和 $100$ 之间（含两端），数值越大表示颜色越深。
## 输出格式

输出一行一个整数，表示制作计划条纹图案所需的最少染色步骤数。

## 样例

### 样例输入 #1
```
6
50 100 50 50 100 50
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
5
1 2 3 2 1
```
### 样例输出 #2
```
3
```
### 样例输入 #3
```
5
3 2 1 2 3
```
### 样例输出 #3
```
5
```
### 样例输入 #4
```
10
1 20 100 1 20 20 100 100 20 20
```
### 样例输出 #4
```
5
```
### 样例输入 #5
```
5
10 60 100 30 10
```
### 样例输出 #5
```
4
```


---

---
title: "[ICPC 2024 Yokohama R] The Sparsest Number in Between"
layout: "post"
diff: 普及-
pid: P12779
tag: ['2024', 'ICPC']
---
# [ICPC 2024 Yokohama R] The Sparsest Number in Between
## 题目背景

译自 [ICPC 2024 Yokohama Regional Contest](https://icpc.jp/2024/)。
## 题目描述


给定一对正整数 $a,b$（$a \le b$）。在 $a$ 和 $b$ 之间（包括 $a$ 和 $b$）的整数中，你的任务是找到最**稀疏**的一个，即其二进制表示中 $\texttt{1}$ 的数量最少的一个。如果存在两个或更多这样的整数，你应该找到其中最小的一个。

例如，假设 $a = 10$ 且 $b = 13$。 $a$ 和 $b$ 之间（包括 $a$ 和 $b$）的整数是 $10$、$11$、$12$ 和 $13$，它们的二进制表示分别为 $\texttt{1010},\texttt{1011},\texttt{1100}$ 和 $\texttt{1101}$。因此，在这种情况下，答案是 $10$，因为 $10$ 和 $12$ 的二进制表示中 $1$ 的数量最少，并且 $10$ 小于 $12$。

## 输入格式


仅一组数据，格式如下所示：


> $a$ $b$

其中，$a,b$ ($a \le b$) 是介于 $1$ 和 $10^{18}$ 之间（包括 $1$ 和 $10^{18}$）的整数。
## 输出格式


输出一行一个整数，表示 $a$ 和 $b$ 之间（包括 $a$ 和 $b$）最稀疏整数中最小的一个。

## 样例

### 样例输入 #1
```
10 13
```
### 样例输出 #1
```
10
```
### 样例输入 #2
```
11 15
```
### 样例输出 #2
```
12
```
### 样例输入 #3
```
11 20
```
### 样例输出 #3
```
16
```
### 样例输入 #4
```
1 1000000000000000000
```
### 样例输出 #4
```
1
```
### 样例输入 #5
```
9876543210 9876543210
```
### 样例输出 #5
```
9876543210
```


---

---
title: "[NERC 2022] Football"
layout: "post"
diff: 普及-
pid: P12795
tag: ['2022', 'Special Judge', 'ICPC', 'NERC/NEERC']
---
# [NERC 2022] Football
## 题目描述

Scientists are researching an impact of football match results on the mood of football fans. They have a hypothesis that there is a correlation between the number of draws and fans' desire to watch football matches in the future.

In football, two teams play a match. The teams score goals throughout a match. A score "$x$ $\tt{:}$ $y$" means that the team we observe scored $x$ goals and conceded $y$ goals. If $x = y$, then the match ends in a draw. If $x > y$, then the observed team wins, and if $x < y$, then it loses.

To find out if there is a correlation, the scientists gathered information about the results of teams in lower leagues. The information they found is the number of matches played by the team ($n$), the number of goals scored in these matches ($a$), and the number of goals conceded in these matches ($b$). 

You are given this information for a single team. You are asked to calculate the minimum number of draws that could have happened during the team's matches and provide a list of match scores with the minimum number of draws.
## 输入格式

The first line contains an integer $n$ --- the number of matches played by the team ($1 \le n \le 100$). The second line contains an integer $a$ --- the total number of goals scored by the team in all $n$ matches ($0 \le a \le 1000$). The third line contains an integer $b$ --- the total number of goals conceded by the team in all $n$ matches ($0 \le b \le 1000$).
## 输出格式

In the first line, print a single integer $d$ --- the minimum number of draws.

In the following $n$ lines, print a list of match scores, each line in the format "$x$ $\tt{:}$ $y$", where $x$ is the number of goals scored in the match, and $y$ -- the number of goals conceded, so that exactly $d$ of these matches have ended in a draw. In case multiple such lists of match scores exist, print any of them.
## 样例

### 样例输入 #1
```
3
2
4
```
### 样例输出 #1
```
0
1:0
1:2
0:2
```
### 样例输入 #2
```
1
2
2
```
### 样例输出 #2
```
1
2:2
```
### 样例输入 #3
```
4
0
7
```
### 样例输出 #3
```
0
0:1
0:2
0:1
0:3
```
### 样例输入 #4
```
6
3
1
```
### 样例输出 #4
```
2
0:0
1:0
0:0
0:1
1:0
1:0
```


---

---
title: "[NERC 2021] Deletive Editing"
layout: "post"
diff: 普及-
pid: P12817
tag: ['2021', 'ICPC', 'NERC/NEERC']
---
# [NERC 2021] Deletive Editing
## 题目描述

Daisy loves playing games with words. Recently, she has been playing the following Deletive Editing word game with Daniel. 

Daisy picks a word, for example, $\tt{DETERMINED}$. On each game turn, Daniel calls out a letter, for example, $\tt{E}$, and Daisy removes $\textbf{the first occurrence}$ of this letter from the word, getting $\tt{DTERMINED}$. On the next turn, Daniel calls out a letter again, for example, $\tt{D}$, and Daisy removes its first occurrence, getting $\tt{TERMINED}$. They continue with $\tt{I}$, getting $\tt{TERMNED}$, with $\tt{N}$, getting $\tt{TERMED}$, and with $\tt{D}$, getting $\tt{TERME}$. Now, if Daniel calls out the letter $\tt{E}$, Daisy gets $\tt{TRME}$, but there is no way she can get the word $\tt{TERM}$ if they start playing with the word $\tt{DETERMINED}$.

Daisy is curious if she can get the final word of her choice, starting from the given initial word, by playing this game for zero or more turns. Your task it help her to figure this out.
## 输入格式

The first line of the input contains an integer $n$ --- the number of test cases ($1 \le n \le 10\,000$). The following $n$ lines contain test cases. 

Each test case consists of two words $s$ and $t$ separated by a space. Each word consists of at least one and at most 30 uppercase English letters; $s$ is the Daisy's initial word for the game; $t$ is the final word that Daisy would like to get at the end of the game.
## 输出格式

Output $n$ lines to the output --- a single line for each test case. Output $\tt{YES}$ if it is possible for Daisy to get from the initial word $s$ to the final word $t$ by playing the Deletive Editing game. Output $\tt{NO}$ otherwise.
## 样例

### 样例输入 #1
```
6
DETERMINED TRME
DETERMINED TERM
PSEUDOPSEUDOHYPOPARATHYROIDISM PEPA
DEINSTITUTIONALIZATION DONATION
CONTEST CODE
SOLUTION SOLUTION
```
### 样例输出 #1
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
title: "[NWRRC 2023] Axis-Aligned Area"
layout: "post"
diff: 普及-
pid: P13581
tag: ['数学', '2023', '排序', 'ICPC', 'NWRRC']
---
# [NWRRC 2023] Axis-Aligned Area
## 题目描述

Alex 有四根长度为正整数的木棍，分别为 $a_1$、$a_2$、$a_3$ 和 $a_4$，且满足 $a_1 \le a_2 \le a_3 \le a_4$。

她想把这四根木棍放在平面上，使得每根木棍都平行于坐标轴中的某一条轴，并且被这些木棍围成的面积尽可能大。

请你求出能够围成的最大面积。
## 输入格式

输入包含四个正整数 $a_1$、$a_2$、$a_3$ 和 $a_4$，每个数占一行，表示木棍的长度，且满足非递减顺序（$1 \le a_1 \le a_2 \le a_3 \le a_4 \le 100$）。
## 输出格式

输出能够围成的最大面积。
## 样例

### 样例输入 #1
```
2
2
4
7
```
### 样例输出 #1
```
8
```
### 样例输入 #2
```
10
10
10
10
```
### 样例输出 #2
```
100
```
## 提示

以下是第一个样例的一种最优摆放方式：

![](https://cdn.luogu.com.cn/upload/image_hosting/u97ufdde.png)

灰色部分为被围成的面积。

由 ChatGPT 4.1 翻译


---

---
title: "[CERC 2020] Rescue Mission"
layout: "post"
diff: 普及-
pid: P13656
tag: ['2020', '前缀和', 'ICPC', 'CERC']
---
# [CERC 2020] Rescue Mission
## 题目描述

The plan of the Criminal Liberating Rough Squad (CLRS) is to attack the train carrying the prisoners to another jail through a desert and to free at least some of them.

CLRS got exactly 10 trucks which will carry the rescued criminals from the place of the assault to the makeshift airport where the planes are already being refueled before they fly abroad with the criminals on board.

At the assault scene, the CLRS will break into a train coach, neutralize coach guards, free all prisoners in the coach and move to the next coach. The squad will progress from the first attacked coach towards the end of the train, liberating the criminals in one coach after another. CLRS is proud to claim they are going to free and load into the trucks all criminals from any coach they will attack. CLRS moves in the train in only one direction, they never turn back.

Somewhat strangely, when the trucks will be leaving the scene, the number of freed criminals has to be exactly the same in all trucks. It is an old time safety superstition of CLRS and it cannot be broken at any cost at any action of this kind.

There are bad news too. The police will probably be patrolling relatively nearby, thus the scene has to be left as soon as possible after the initial assault. That is, immediately when the superstition rule allows it.

It may also happen, the mission will be impossible to accomplish. For example if CLRS starts the attack on a coach too close to the end of the train.

Now, everything has to be planned carefully. The number of transported criminals in each coach is known to CLRS beforehand. They want to know, for each coach in the train, how many coaches will they have to attack if the assault starts on that particular coach.

## 输入格式

The first input line contains integer $N$ ($1 \leq N \leq 10^5$), the number of coaches in the train. The second line contains $N$ values between 0 and 9 (inclusive), the number of transported criminals in each coach. The values are listed in the order from the first coach in the train to the last.

## 输出格式

The output consists of a sequence of $N$ numbers, $k$-th value in the sequence is the number of attacked coaches when the assault starts on $k$-th coach. If the mission cannot be accomplished starting on $k$-th coach, the corresponding value in the sequence is $-1$.
## 样例

### 样例输入 #1
```
5
0 2 4 6 8
```
### 样例输出 #1
```
1 4 2 -1 -1
```
### 样例输入 #2
```
5
5 5 5 0 5
```
### 样例输出 #2
```
2 2 3 1 -1
```


---

---
title: "[GCPC 2023] German Conference for Public Counting"
layout: "post"
diff: 普及-
pid: P13672
tag: ['2023', 'ICPC']
---
# [GCPC 2023] German Conference for Public Counting
## 题目描述

Greta loves counting.
She practises it every day of the year.
Depending on the season, she counts
falling leaves, raindrops, snowflakes, or even growing leaves.
However, there is one event in summer which tops everything else: the German
Conference for Public Counting (GCPC).

At this event, Greta meets counting enthusiasts from all over the country for
one week of counting and counting and counting... Together they participate in the 
Glamorous Competitive Public Counting and the Great Chaotic Public Counting.
At the end of the week they all try to win the Golden Cup of Public Counting.
Her favourite is the Gently Calming Public Counting where the crowd counts in silence, trying to harmoniously synchronise to reach the target number at precisely the same moment.

![](https://cdn.luogu.com.cn/upload/image_hosting/k9laqt9y.png)

:::align{center}
Figure G.1: People holding up signs for the countdown.
:::

To increase the tension and to prepare for the Gently Calming Public Counting,
the organizers of GCPC plan to start
with a silent countdown, where the people on the stage will at any time
display the current number by holding up signs with its digits.
On every sign, there is exactly one decimal digit.
Numbers greater than $9$ are displayed by holding up several signs next to each other.
Each number is shown using the least possible number of signs; there is no left padding with zeroes.
This way, the people on the stage display numbers $n, n-1, n-2, \dots$ until they
finally display $0$.
Since the GCPC will take place soon, the organizers want to finish their
preparations quickly.
How many signs do they need to prepare at least so that they can display
the entire countdown from $n$ to $0$?
## 输入格式

The input consists of:
- One line with an integer $n$ ($1 \le n \le 10^9$), the starting number of the countdown.

## 输出格式

Output the minimum number of signs required to display every number of the countdown.

## 样例

### 样例输入 #1
```
5
```
### 样例输出 #1
```
6
```
### 样例输入 #2
```
20
```
### 样例输出 #2
```
11
```
### 样例输入 #3
```
44
```
### 样例输出 #3
```
14
```
### 样例输入 #4
```
271828182
```
### 样例输出 #4
```
82
```
### 样例输入 #5
```
314159265
```
### 样例输出 #5
```
82
```
## 提示

In the first sample case, the organizers need one sign each with the digits $0$ to $5$, for a total of $6$ signs. In the second sample case, they need one sign with each digit other than $1$, and two signs with a $1$, for a total of $9+2=11$ signs.


---

---
title: "[GCPC 2023]  Investigating Frog Behaviour  on Lily Pad Patterns"
layout: "post"
diff: 普及-
pid: P13674
tag: ['2023', 'ICPC']
---
# [GCPC 2023]  Investigating Frog Behaviour  on Lily Pad Patterns
## 题目描述

Recently, the biologist Ina discovered a new frog species
on the lily pads of a pond.
She observed the frogs for a while and found them to be very conscious
about their personal space because they avoided sharing a lily pad with other frogs.
Also, they seemed quite lazy as they did not move often, and if they did,
they always jumped to the nearest empty lily pad.

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/6jt2rls1.png)

A frog in a pond.
:::

To confirm her hypotheses about the frogs' movement pattern, Ina set up
a large number of lily pads in a pool in her laboratory, arranged in a straight line.
Since the frogs were attracted to light, she was able to simplify the test setup
further by placing a bright light at one end of that line. This way, the frogs
would always jump in one direction (towards the light).

Of course, Ina could now place some frogs on the lily pads and
sit there all day watching the frogs jump around. But as the frogs
move so rarely, it would take ages to gather a sufficient amount of data.

She therefore attached to each frog a tiny device that could log all jumps of that frog.
This way, she could put the frogs on the lily pads, leave
them alone for a few hours and come back later to collect the data.
Unfortunately, the devices had to be so tiny that there was no space
for a position tracking system; instead, the devices could only record the times of the jumps.

But if the movement pattern of the frogs is as restricted as Ina thinks, surely the
individual movements of the frog can be reconstructed only from the initial positions and
the recorded jump time stamps?
## 输入格式

The input consists of:
- One line with an integer $n$ ($1\leq n \leq 2\cdot10^5$), the number of frogs.
- One line with $n$ integers $x_1,\dots, x_n$ ($1\leq x_i \leq 10^6$), the number of the lily pad on which the $i$th frog initially sits. The lily pads are numbered consecutively, starting at $1$. It is guaranteed that the initial positions are strictly increasing, i.e. $x_1 < x_2 < \dots < x_n$.
- One line with an integer $q$ ($1\leq q \leq 2\cdot10^5$), the number of jumps recorded.
- $q$ lines, each containing an integer $i$ ($1\leq i\leq n$), indicating that the $i$th frog jumped. The jumps are given in chronological order and you may assume that a jumping frog lands before the next jump begins. The frogs always jump to the nearest empty lily pad with a larger number, and you may assume that such a lily pad always exists.

## 输出格式

For each jump, output the number of the lily pad the frog lands on.
## 样例

### 样例输入 #1
```
5
1 2 3 5 7
3
1
2
4
```
### 样例输出 #1
```
4
6
8
```
### 样例输入 #2
```
5
1 2 3 5 7
4
1
1
1
1
```
### 样例输出 #2
```
4
6
8
9
```
## 提示

![](https://cdn.luogu.com.cn/upload/image_hosting/k07qih18.png)

:::align{center}
Figure I.1: Illustration of the first sample case. The lily pads are numbered from left to right, starting at 1.
:::


---

---
title: "[GCPC 2023] Loop Invariant"
layout: "post"
diff: 普及-
pid: P13677
tag: ['2023', 'ICPC']
---
# [GCPC 2023] Loop Invariant
## 题目描述

Luna, a historian, was exploring the archives of an
old monastery when she stumbled on a mysterious scroll of parchment.
On it were only two types of symbols: '$\texttt{(}$' and '$\texttt{)}$'.
Soon she noticed that the sequence of symbols satisfies an interesting property:
It can be constructed by repeatedly inserting '$\texttt{()}$' at some
position into an initially empty sequence.
Historians call such sequences *balanced*.
Figure L.1 gives an
example of a balanced sequence.

:::align{center}

![](https://cdn.luogu.com.cn/upload/image_hosting/16wf12pi.png)

Acircular piece of parchment.
:::

![](https://cdn.luogu.com.cn/upload/image_hosting/lm64um27.png)

:::align{center}
Figure L.1: Sample Input 2 derived by successively inserting '$\texttt{()}$' into an initially empty sequence.
:::

The chief librarian of the monastery recently told Luna
that some of the more elitist monks in the region had a habit of writing
on circular pieces of parchment.
In their minds, anyone
incapable of immediately telling where the text on such a scroll started was
also unworthy of knowing its content.
Consequently, Luna quickly inspected the edges of her
parchment strip. And sure enough, the edges at the left and right
end of the parchment strip fit together perfectly, indicating that the parchment
once actually was circular.
While holding the left and right edges together and looking at the now circular
parchment, she wonders whether the balanced sequence starting at the tear is the only
such sequence that could have resulted from tearing the parchment apart.
After all, it makes little sense trying to decrypt a text when you do not even
know where it starts.

## 输入格式

The input consists of:
- One line with a balanced sequence $s$ ($2\leq |s|\leq 10^6$), the sequence on Luna's strip of parchment.

## 输出格式

Output "$\texttt{no}$" if there is no way to obtain a different balanced sequence by cutting the circular sequence, otherwise give any such sequence.
## 样例

### 样例输入 #1
```
(()())(()())
```
### 样例输出 #1
```
no
```
### 样例输入 #2
```
()(())()
```
### 样例输出 #2
```
(())()()
```


---

---
title: "[GCPC 2023] Mischievous Math"
layout: "post"
diff: 普及-
pid: P13678
tag: ['数学', '2023', 'Special Judge', 'ICPC']
---
# [GCPC 2023] Mischievous Math
## 题目描述

Max enjoys playing number games, whether it involves finding
a combination that leads to a given
result or discovering all possible results for some given integers.
The problem is that Max is only 10 and has limited
mathematical knowledge, which restricts the possibilities for these games.
Luckily, in today's maths class, Max learned the concept of
parentheses and their effects on calculations. He realises that incorporating parentheses
into his number games could make them much more interesting.
After getting home from school, he asked his sister Nina to play a
variant of his favourite number game with him, using parentheses.

![](https://cdn.luogu.com.cn/upload/image_hosting/obfj7x59.png)


:::align{center}
Max trying to solve the third sample.
:::

In this new game, Max first tells her a number $d$.
Nina then tells him three numbers $a$, $b$ and $c$.
Now, Max needs to find an arithmetic expression
using addition, subtraction, multiplication and division, using each of these three
numbers ($a$, $b$ and $c$) at most once, such that the result is equal to $d$.
The numbers $a, b, c$ and $d$ all have to be distinct, and Max is allowed to
use parentheses as well.

For instance, for $a = 5$, $b = 8$, $c = 17$ and $d = 96$ a possible
solution would be $(17 - 5) \times 8 = 96$, and for $a = 3$, $b = 7$, $c = 84$
and $d = 12$ a possible solution would be $84 \div 7 = 12$, without using
the $3$.

Nina is quickly annoyed by this game. She would rather spend the
afternoon with her friends instead of playing games with her little
brother. Therefore, she wants to give him a task that occupies him for as long as possible.
Help her to find three numbers $a$, $b$ and $c$
such that it is impossible for Max to come up with a solution.
## 输入格式

The input consists of:
- One line with an integer $d$ ($1 \le d \le 100$), Max's chosen number.
## 输出格式

Output three numbers $a$, $b$ and $c$ ($1 \le a,b,c \le 100$) such that the numbers $a$, $b$, $c$ and $d$ are pairwise distinct and there is no solution to the number game.
## 样例

### 样例输入 #1
```
5
```
### 样例输出 #1
```
1 20 30
```
### 样例输入 #2
```
100
```
### 样例输出 #2
```
33 55 77
```
### 样例输入 #3
```
3
```
### 样例输出 #3
```
11 9 4
```


---

---
title: "[NWERC 2023] Klompendans"
layout: "post"
diff: 普及-
pid: P13710
tag: ['2023', 'ICPC']
---
# [NWERC 2023] Klompendans
## 题目描述

In traditional Dutch clog dancing, as the dancer, you need to follow a very specific sequence of movements. The dance takes place on a square grid of square tiles. At the start of the dance, you stand on the top - left corner tile of the grid. Then, you alternate between two types of dance moves, moving from tile to tile in the grid for as long as you want. Your first move can be either type, but after that, you must strictly alternate between the two types of moves.

Both moves are similar to knight moves in chess: In the first type of move, you move from your current square to a square that is $a$ tiles away along one axis of the grid and $b$ tiles away along the other axis. Similarly, in the second type of move, you need to move $c$ tiles and $d$ tiles along the respective axes. Since you can freely swap the two axes and choose the movement direction along each axis, there can be up to 8 ways to perform a given type of move. Figure K.1 shows an example dance routine with $(a, b)=(1, 2)$ and $(c, d)=(2, 3)$.

![](https://cdn.luogu.com.cn/upload/image_hosting/yu84dg31.png)

:::align{center}
Figure K.1: Illustration of Sample Input 3, showing a dance that begins in the top - left corner of a $4\times4$ grid and ends in the bottom - left corner, visiting the blue squares along the way. There are 13 reachable squares in total. The three squares highlighted in red cannot be part of any dance performance.
:::


Starting on the top - left corner tile, how many different tiles could you reach while doing a clog dance? It is not allowed to step outside the grid, and you do not count tiles that you simply step over while making a move. Note that you need to count all tiles that can be reached during some performance of the dance, not necessarily during the same one.
## 输入格式

The input consists of:
- One line with an integer $n$ ($3\leq n\leq500$), the side length of the square.
- One line with two integers $a$ and $b$ ($1\leq a, b\lt n$), describing the first dance move.
- One line with two integers $c$ and $d$ ($1\leq c, d\lt n$), describing the second dance move.
## 输出格式

Output the number of tiles you can reach using these dance moves. 
## 样例

### 样例输入 #1
```
3
2 1
2 2
```
### 样例输出 #1
```
6
```
### 样例输入 #2
```
8
1 2
1 2
```
### 样例输出 #2
```
64
```
### 样例输入 #3
```
4
1 2
2 3
```
### 样例输出 #3
```
13
```
### 样例输入 #4
```
5
1 2
2 3
```
### 样例输出 #4
```
25
```
### 样例输入 #5
```
10
3 3
4 4
```
### 样例输出 #5
```
50
```


---

---
title: "[NWERC 2023] Lateral Damage"
layout: "post"
diff: 普及-
pid: P13711
tag: ['2023', '交互题', 'Special Judge', '构造', 'ICPC']
---
# [NWERC 2023] Lateral Damage
## 题目描述

You are playing *Battleships* in a large ocean with large ships.
More precisely, there is a large square grid of size at most $100\times 100$
and inside it are up to $10$ of the largest type of ship in Battleships
-- the aircraft carrier -- which has a length of five tiles,
placed either horizontally or vertically.
The ships do not overlap, but they are allowed to be adjacent to each other.
See Figure L.1 for an example.

![](https://upload.wikimedia.org/wikipedia/commons/a/ac/Hra_n%C3%A1mo%C5%99n%C3%AD_bitva_%281%29.jpg)

:::align{center}
The original *Battleships* game, before the upgrade to a $100 \times 100$ grid. CC BY-NC 3.0 by Pavel Ševela on [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Hra_n%C3%A1mo%C5%99n%C3%AD_bitva_(1).jpg)
:::

Unfortunately, your opponent appears to bend the rules to their liking.
It looks like they do not always determine the placement of their ships before you start shooting.
You are not impressed by their attempt at cheating, and decide to try and win the game anyway.

![](https://cdn.luogu.com.cn/upload/image_hosting/0lfdcwfa.png)

:::align{center}
Figure L.1: Illustration of Sample Interaction 1 after the first four shots were fired.
:::

Your goal is to locate and sink all your opponent's aircraft carriers in at most $2500$ shots, that is, you must hit each of the five tiles of all their ships.
## 输入格式

This is an interactive problem.
Your submission will be run against an *interactor*, which reads from the standard output of your submission and writes to the standard input of your submission. This interaction needs to follow a specific protocol:

The interactor first sends one line with two integers $n$ and $k$ ($5 \le n \le 100$, $1 \le k \le 10$), the size of the grid and the number of ships. It is guaranteed that it is possible to place $k$ aircraft carriers in the grid without overlap.

Then, your program needs to start firing shots.
Each shot is fired by printing one line of the form "$\texttt{x y}$" ($1 \le x,y \le n$), indicating you shoot at position $(x, y)$. The interactor will respond with "$\texttt{hit}$" if the shot was a hit, "$\texttt{sunk}$" if the shot caused an aircraft carrier to sink, and "$\texttt{miss}$" otherwise. If you have shot the same location before, the response will be "$\texttt{miss}$".

Once you sink the last aircraft carrier, the interaction will stop and your program must exit.

The interactor is adaptive: the positions of the ships may be determined during the interaction, and may depend on where you decide to shoot.

Make sure you flush the buffer after each write.

A testing tool is provided to help you develop your solution.

Firing more than $2500$ shots will result in a wrong answer.
## 样例

### 样例输入 #1
```
7 2

miss

hit

miss

hit

hit

hit

hit

sunk

miss

miss

hit

miss

hit

hit

sunk
```
### 样例输出 #1
```

6 1

6 3

7 3

5 3

4 3

3 3

2 3

1 3

6 7

6 7

6 2

6 2

6 4

6 5

6 6
```


---

---
title: "[GCPC 2024] Bookshelf Bottleneck"
layout: "post"
diff: 普及-
pid: P13717
tag: ['贪心', '2024', 'ICPC']
---
# [GCPC 2024] Bookshelf Bottleneck
## 题目描述

Brianna is a bookworm. At home, she has a big bookshelf with all her favourite
books. She has a large collection ranging from detective novels and
science-fiction novels to biographies.

Recently, Brianna has expanded her collection with $n$ graphic novels. However,
the new books currently lie around everywhere and form huge stacks on the floor.
In the meantime, one of the shelf boards has collected dust and random household utensils that
do not belong there.
The new books just lying around have become too much to bear,
and Brianna finally decided to put them
on this shelf board. To do so, she first has to make room on it.


:::align{center}
![Figure B.1: Visualization of Sample Input 3.](https://cdn.luogu.com.cn/upload/image_hosting/atblbkye.png)
Figure B.1: Visualization of Sample Input 3.
:::

Brianna wants to arrange the books in a single horizontal line without
stacking multiple books on top of each other. While the shelf is wide
enough to hold all books without problems, it takes time to make room 
on the shelf. Therefore, Brianna wants to minimize the width of the part 
of the shelf that she needs to clear.

Each book can be described as a cuboid with three side lengths $l$, $w$, and $h$.
Since the room above the shelf board is limited by the next shelf board above it,
she can only fit a book vertically if its vertical side length is at most the distance $H$
between the two shelf boards. Brianna may rotate each book
in three-dimensional space as she wants. It is guaranteed that the shelf is deep enough
so that the books will not fall off, no matter the orientation. However, all books must
stand properly on the shelf board, meaning that every book touches the shelf board along an
entire face and not just by an edge.

What is the minimum width of shelf Brianna's books need?
## 输入格式

The input consists of:
- One line with two integers $n$ and $H$ ($1\leq n\leq 10^5$, $1\leq H \leq 10^9$), the number of books and the height of the shelf, respectively.
- $n$ lines, each containing three integers $l$, $w$, $h$ ($1\leq l,w,h \leq 10^9$), the dimensions of the books.
## 输出格式

Output the minimum width of shelf Brianna's books need, or "$\texttt{impossible}$" if it is impossible to place the books on the shelf.
## 样例

### 样例输入 #1
```
1 3
10 2 5
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
1 3
10 4 5
```
### 样例输出 #2
```
impossible
```
### 样例输入 #3
```
2 10
10 2 10
2 3 4
```
### 样例输出 #3
```
4
```
### 样例输入 #4
```
3 1000000000
1000000000 1000000000 1000000000
1000000000 1000000000 1000000000
1000000000 1000000000 1000000000
```
### 样例输出 #4
```
3000000000
```


---

---
title: "[GCPC 2024] Interference"
layout: "post"
diff: 普及-
pid: P13724
tag: ['模拟', '2024', 'ICPC']
---
# [GCPC 2024] Interference
## 题目描述

Physics can be so much fun!
Yesterday, your teacher explained how interference works: If you have two waves, their heights add up over the whole waves' length!
So if both waves have a peak, the resulting peak will be even higher.
Likewise, if both waves have a wave trough below the water surface, the resulting wave has a trough that will be even further below.
Technically, a wave's height is called amplitude and the distance between two wave peaks is called wavelength.

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/vaufr6oi.png)

Figure I.1: Interference of three waves in Sample Input 2. The black dots represent the resulting wave’s height.
:::

Today, your physics teacher describes the setup of an experiment she is about to perform.
She will create stationary waves in a one-dimensional container of water.
Due to her superior control over physical elements, all waves will have a precisely controlled amplitude and will only be created in an interval of given length.  
The wavelength of each wave is always $4$ and the first positive peak will always be at the first index of the interval.
We only measure the wave's amplitude at integer points.
For example, a wave with amplitude $2$ and length $9$ can be described as $\texttt{2 0 -2 0 2 0 -2 0 2}$.
If there is no wave at a point, the amplitude is $0$.
Your task is to predict how high the resulting wave will be at given points in the container taking into account all the waves that were created up to that point.
## 输入格式

The input consists of:
- One line with two integers $n$ and $w$ ($1 \le n \le 4\,000$, $1 \le w \le 10^{9}$), the number of lines and the width of the container.
- $n$ lines, each containing either a wave description or a prediction task:
  - "$\texttt{!}~p~\ell~a$", a wave description with starting position $p$, length $\ell$ $(1 \le p, \ell \le w)$, and amplitude $a$ $(1 \le a \le 10^9)$. It is guaranteed that $p+\ell - 1 \le w$.
  - "$\texttt{?}~p$", a prediction task for the resulting wave at position $p$ ($1 \le p \le w$).


See Figure I.1 for a partial visualization of Sample 2.
## 输出格式

For each prediction task, output a line with a single integer, the height of the wave resulting from all former described waves at the requested position.
## 样例

### 样例输入 #1
```
4 10
! 2 7 1
? 9
? 7
? 6
```
### 样例输出 #1
```
0
0
1
```
### 样例输入 #2
```
7 10
! 2 6 1
! 3 8 2
! 5 2 3
? 6
! 5 5 4
? 8
? 9
```
### 样例输出 #2
```
1
0
2
```
### 样例输入 #3
```
6 12
! 1 7 1
! 7 3 2
? 6
? 7
? 8
? 10
```
### 样例输出 #3
```
0
1
0
0
```
### 样例输入 #4
```
6 11
! 1 6 1
? 6
! 5 7 4
? 6
! 6 3 2
? 6
```
### 样例输出 #4
```
0
0
2
```


---

---
title: "[GCPC 2024] Kitten of Chaos"
layout: "post"
diff: 普及-
pid: P13726
tag: ['模拟', '字符串', '2024', 'ICPC']
---
# [GCPC 2024] Kitten of Chaos
## 题目描述

Karen has a beautiful precious glass object on the shelf in her living room.
Unfortunately, her cat Klaus does not like it when there is stuff on his favourite shelf.
Everything that is not bolted or glued in place, he will gradually push over the edge while looking Karen straight in the eyes.

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/oh6p314l.png)

Klaus, 10 seconds before an event that was luckily covered by Karen's insurance.

:::

Now, Klaus' paw slowly executes his diabolical deed. 
His cute fluffy face radiates inadvertent innocence.
Knowing that any intervention would only delay the inevitable, Karen wonders what will happen to the string her sister Kim wrote on the precious glass object.
After all, it took Kim a whole week to gather all the $\texttt{bdpq}$ letters that make up the string.

Can you describe to Karen what the string will look like from her point of view while it tumbles towards destruction?

While falling off the shelf, Karen's precious glass object is subject to the following transformations, described as seen when looking at the object from the front.

- $\texttt{h}$: horizontal flip, e.g. $\texttt{bbq}$ becomes $\texttt{pdd}$
- $\texttt{v}$: vertical flip, e.g. $\texttt{bbq}$ becomes $\texttt{ppd}$
- $\texttt{r}$: 180-degree rotation, e.g. $\texttt{bbq}$ becomes $\texttt{bqq}$


No flips along or rotations about any other axes are possible.
## 输入格式

The input consists of:
- One line with a string $s$ consisting of the letters $\texttt{bdpq}$ ($1 \le |s| \le 5\cdot 10^5$), the string printed on the glass object as seen at the start of the fall.
- One line with a string $t$ consisting of the letters $\texttt{hvr}$ ($1 \le |t| \le 5\cdot 10^5$) giving the sequence of transformations in the order that they occur during the fall.
## 输出格式

Output the string that can be seen at the moment the glass object touches the ground and just before it shatters into pieces.
## 样例

### 样例输入 #1
```
bbq
h
```
### 样例输出 #1
```
pdd
```
### 样例输入 #2
```
bbq
v
```
### 样例输出 #2
```
ppd
```
### 样例输入 #3
```
bbq
r
```
### 样例输出 #3
```
bqq
```
### 样例输入 #4
```
ppbddbq
hvrhv
```
### 样例输出 #4
```
bqppqdd
```


---

---
title: "[NWERC 2024] Alphabetical Aristocrats"
layout: "post"
diff: 普及-
pid: P13739
tag: ['字符串', '2024', 'ICPC']
---
# [NWERC 2024] Alphabetical Aristocrats
## 题目描述

It is the year 1830 of our Lord, 15 years after the Kingdom of the Netherlands gained independence from its French oppressors.
You are secretary of state and aide to his highness William I, Grand Duke of Luxembourg and King of the Netherlands --
an empire that is destined to prosper and stretch across centuries to come.
To the King's utter dismay, rogue scoundrels from the south recently dared to defy his benevolent rule.
They call themselves Belgians and declared their own kingdom --
a fact that his highness will surely deny for at least another seven to eleven years.
King William, in all his wisdom, decided to call upon the most trusted noblemen to scheme a campaign against the insubordinate elements that will last more than nine days.

:::align{center}

![](https://upload.wikimedia.org/wikipedia/commons/1/13/Kroegtafereel%2C_circa_1601_-_circa_1700%2C_Groeningemuseum%2C_0040612000.jpg?20201110013918)

Tavern Scene by Abraham van den Hecken the Younger. CC0 on [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Kroegtafereel,_circa_1601_-_circa_1700,_Groeningemuseum,_0040612000.jpg)

:::


You are to assemble a list of trustworthy royalty and sort them according to the Dutch rules.
The Dutch rules state that surnames are to be compared lexicographically, according to the values of the ASCII characters, and considering only the part starting from the first capital letter.
For example, King William compares the surname of his favourite painter Abraham $\texttt{van den Hecken the Younger}$ according to $\texttt{Hecken the Younger}$.
## 输入格式

The input consists of:
- One line with an integer $n$ ($1\leq n\leq 1000$), the number of surnames.
- $n$ lines, each with a string $s$ ($1\leq |s|\leq50$), one of the surnames. The surnames consist of English letters, spaces, and apostrophes
            ($\texttt{A-Z}, \texttt{a-z},$'$\ $', '$\verb|'|$').

    It is guaranteed that the part starting with the first capital letter is unique.
    Names have no leading, trailing, or consecutive spaces.
## 输出格式

Output the list of surnames, sorted according to the Dutch rules.
## 样例

### 样例输入 #1
```
7
van der Steen
fakederSteenOfficial
Groot Koerkamp
Bakker
van den Hecken the Younger
de Waal
van 't Hek

```
### 样例输出 #1
```
Bakker
Groot Koerkamp
van den Hecken the Younger
van 't Hek
van der Steen
fakederSteenOfficial
de Waal
```
### 样例输入 #2
```
5
var Emreis
an Gleanna
Terzieff Godefroy
aep Ceallach
of Rivia
```
### 样例输出 #2
```
aep Ceallach
var Emreis
an Gleanna
of Rivia
Terzieff Godefroy
```
### 样例输入 #3
```
7
van den Brand
den Brand Heek
Brand 'Heek
van Brand heek
DeN bRAnD hEeK
den brandHeek
der Brandheek
```
### 样例输出 #3
```
van den Brand
Brand 'Heek
den Brand Heek
van Brand heek
der Brandheek
DeN bRAnD hEeK
den brandHeek
```


---

---
title: "[SWERC 2023] Programming-trampoline-athlon!"
layout: "post"
diff: 普及-
pid: P13797
tag: ['模拟', '2023', '排序', 'ICPC']
---
# [SWERC 2023] Programming-trampoline-athlon!
## 题目描述

:::align{center}

![](https://espresso.codeforces.com/a75009f1d00a17654c89251bd019d39f1ee01d81.png)

![](https://espresso.codeforces.com/ed274bb41d6938a7fe78ee1e6b6f4ec73754aad8.png)

:::



Programming competitions are fun and exciting. Programming should be an Olympic sport! At least, this is what we believe. However, when we suggested this to some of our friends, they did not seem to share our excitement. So, we decided to suggest a combined sport that will be more interesting to watch. Programming-trampoline-athlon! (we are still working on the name.)


The idea is as follows. This is a team sport, where each team comprises of $3$ members. The team has at its disposal $1$ hour, $1$ computer, and $1$ trampoline. At all times, there must be at most one team member using the computer and at least one team member jumping the trampoline. At the beginning of the competition, the team is given $6$ programming problems, and $6$ trampoline elements (exercises). The team decides how to partition the trampoline elements between its members, such that each team member has to perform $2$ of the given elements on the trampoline. The programming tasks are solved cooperatively by the team members, but no one member can spend more than $25$ minutes on the computer in total. The scoring is comprised of two parts, which are added together:

- The programming score ranges between $0$ and $60$. The team receives $10$ points for every correctly solved problem.
- The trampoline score ranges between $0$ and $40$. Each of the $6$ trampoline elements receives a score from the judges that ranges between $0$ and $10$. The final trampoline execution score is determined by dropping the highest and lowest of the $6$ scores, and then adding up the remaining $4$ scores.

Before we pitch this new sport to the International Olympic Committee, we want everything to be ready in order to show them just how serious we are. Thus, each team should receive a medal when no more than two other teams obtained a strictly higher score. However, in order to cope with a recent shortage of medals, the jury was instructed to make sure that there would be no more than $1~000$ teams deserving a medal. We ask you to write a program that determines the medallists, given the performance of the different teams.
## 输入格式

The first line contains the number $N$ of competing teams. Then follow $N$ lines. Each of these lines describes a team and contains space-separated values $C, P, E_1, E_2, E_3, E_4, E_5, E_6$; $C$ is a five-letter code used to identify the team, $P$ is an integer specifying the number of problems the team solved, and $E_i$ is an integer specifying the execution score of trampoline element number $i$.
## 输出格式

The output should contain $M$ lines, where $M$ is the number of medallists. Each line should represent a medallist team, by containing two space-separated values $C$ and $S$, where $C$ is the team code and $S$ is the total score of the team. Medallist teams should be listed by decreasing total score and, in case of ties, by input order.
## 样例

### 样例输入 #1
```
5
EMAIL 3 5 6 7 8 9 10
CRASH 2 7 1 8 2 8 1
MOUSE 4 0 9 3 9 1 7
SWERC 6 3 1 4 1 5 9
PAINT 6 0 0 0 0 0 10
```
### 样例输出 #1
```
SWERC 73
EMAIL 60
MOUSE 60
PAINT 60
```
### 样例输入 #2
```
4
CRAZY 4 0 2 4 6 8 10
JAZZY 2 9 9 9 9 9 9
JUICY 3 2 9 10 9 10 1
FUZZY 5 0 1 1 2 3 5
```
### 样例输出 #2
```
CRAZY 60
JUICY 60
FUZZY 57
```


---

---
title: "[CERC 2023] Equal Schedules"
layout: "post"
diff: 普及-
pid: P13849
tag: ['模拟', '字符串', '2023', 'ICPC', 'CERC']
---
# [CERC 2023] Equal Schedules
## 题目描述

You are one of the people on-call for a high-availability service that offers users to solve programming tasks. As an organized team, you have an on-call schedule specifying who is responsible for the service at which time. A colleague sends you a new schedule, and you want to make sure that everyone has the same amount of on-call time as before, or print any differences.

The on-call schedule is specified with lines of form $s_i \ e_i \ t_i$, where $s_i$ and $e_i$ represent the start and end offsets of the on-call shift for a teammate $t_i$ from some start hour.

Given a sample schedule

```
0 7 jan
7 14 tomaz
14 20 jure
20 24 jan
24 25 tomaz
25 26 jure
```

we can see that jan is on-call for the first $7$ hours (hour $0, 1, 2, 3, 4, 5$, and $6$), tomaz for next $7$, … In total, jan is on-call for $11$ hours, tomaz for $8$ and jure for $7$.
## 输入格式

The input contains two schedules separated by a horizontal line `------`. Each schedule contains one or more lines of form $s_i \ e_i \ t_i$, where integers $s_i$ and $e_i$ specify that teammate $t_i$ is on-call for hours from $s_i$ up to and excluding $e_i$. A final line `======` is printed after the second schedule.
## 输出格式

Output the differences between two schedules, in form $t_i \ \pm d_i$, where $d_i$ is the difference between the second and the first schedule for the teammate $t_i$. The output should be sorted alphabetically by teammates' names and teammates with no differences should be omitted, otherwise the difference should be printed with a + or a - sign. If no differences are found, print `No differences found.` (without the quotes).
## 样例

### 样例输入 #1
```
0 7 jan
7 14 tomaz
14 20 jure
20 24 jan
24 25 tomaz
25 26 jure
------
0 9 tomaz
9 20 jan
20 26 jure
======
```
### 样例输出 #1
```
jure -1
tomaz +1
```
### 样例输入 #2
```
0 7 nino
7 14 bgs
14 21 ines
------
0 7 ines
7 14 nino
14 21 bgs
======
```
### 样例输出 #2
```
No differences found.

```
### 样例输入 #3
```
0 3 vid
3 6 maks
6 9 janez
------
0 1 vid
1 2 vid
2 3 vid
3 4 maks
4 5 maks
5 6 maks
6 7 janez
7 8 janez
======
```
### 样例输出 #3
```
janez -1
```
## 提示

### Input limits

For each schedule, the following holds:

- $s_1 = 0$
- $s_i < e_i$
- $s_{i+1} = e_i$
- $e_i \leq 1000$
- Name $t_i$ will consist of lowercase letters from the English alphabet.
- $3 \leq |t_i| \leq 20$


---

---
title: "[ICPC 2015 WF] Amalgamated Artichokes"
layout: "post"
diff: 普及-
pid: P6904
tag: ['2015', 'Special Judge', 'ICPC']
---
# [ICPC 2015 WF] Amalgamated Artichokes
## 题目描述

 ![](https://vj.z180.cn/751a8fdd9863b69e86176e87e1fd5b20?v=1600415919)  

Fatima Cynara is an analyst at Amalgamated Artichokes (AA). As with any company, AA has had some very good times as well as some bad ones. Fatima does trending analysis of the stock prices for AA, and she wants to determine the largest decline in stock prices over various time spans. For example, if over a span of time the stock prices were $19$, $12$, $13$, $11$, $20$ and $14$, then the largest decline would be $8$ between the first and fourth price. If the last price had been $10$ instead of $14$, then the largest decline would have been $10$ between the last two prices. 

Fatima has done some previous analyses and has found that the stock price over any period of time can be modelled reasonably accurately with the following equation:

$$ \operatorname {price}(k) = p \cdot (\sin (a \cdot k+b) + \cos (c \cdot k+d) + 2) $$

where $p$, $a$, $b$, $c$ and $d$ are constants. Fatima would like you to write a program to determine the largest price decline over a given sequence of prices. Figure 1 illustrates the price function for Sample Input 1. You have to consider the prices only for integer values of $k$.

  ![](https://vj.z180.cn/800605356b7337600d5163d2e5d7aab4?v=1600415919) 

   Figure 1: Sample Input 1. The largest decline occurs from the fourth to the seventh price. 
## 输入格式

The input consists of a single line containing $6$ integers $p$ ($1 \le p \le 1\, 000$), $a$, $b$, $c$, $d$ ($0 \le a, b, c, d \le 1\, 000$) and $n$ ($1 \le n \le 10^6$). The first $5$ integers are described above. The sequence of stock prices to consider is $\operatorname {price(1)}, \operatorname {price(2)}, \ldots , \operatorname {price}(n)$.
## 输出格式

Display the maximum decline in the stock prices. If there is no decline, display the number $0$. Your output should have an absolute or relative error of at most $10^{-6}$.
## 样例

### 样例输入 #1
```
42 1 23 4 8 10

```
### 样例输出 #1
```
104.855110477

```
### 样例输入 #2
```
100 7 615 998 801 3

```
### 样例输出 #2
```
0.00

```
### 样例输入 #3
```
100 432 406 867 60 1000

```
### 样例输出 #3
```
399.303813

```
## 提示

Time limit: 5000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2015
## 题目翻译

**题目背景**

法蒂玛是针对联合洋蓟果业公司 (Amalgamated Artichokes , AA) 的股票分析员。和其他的公司一样，联合洋蓟果业公司有的时候行情较好，有的时候不太行。法蒂玛对联合洋蓟果业公司的股票价格做了跟踪分析，她想确定不同时间段内股价最大跌幅是多少。比如如果一段时间内股价分别为19元，12元，13元，11元，20元，14元，则最大的跌幅为第一天和第四天之间的8。如果最后一天的价格不是14元而是10元，则最大跌幅为最后两天股价之间的10元。

法蒂玛做了些前期的分析，发现一段时间的股价可以建模精确合理地表示为以下方程式：
$$
price⁡(k)=p⋅(sin⁡(a⋅k+b)+cos⁡(c⋅k+d)+2)
$$
其中$p,a,b,c,d$均为常数。法蒂玛想要你写个程序确定给定价格序列上的最大股价跌幅。

图1说明了第一组样例的价格函数，你只能考虑时间为整数$k$时的价格。

对于第一组样例，最大股价跌幅出现在第四天和第七天之间。

**一句话题意**

对于给定序列，求差值最大的逆序对

**输入格式**

输入共一行，包含六个整数$p (1 \le p \le 1000), a, b, c, d ( 0 \le a, b, c, d \le 1\, 000)$ 和$ n (1 \le n \le 10^6).$

前五个整数意义如题目所述，给定序列长度为n。

**输出格式**

输出股价最大跌幅，如果没有股价下跌则输出0。

输出最多和标准答案有$10^{-6}$的相对或绝对误差。

**说明/提示**

时间限制: 5000 ms 

空间限制: 1048576 kB.

International Collegiate Programming Contest (ACM-ICPC) World Finals 2015


---

---
title: "[NEERC 2015] Adjustment Office"
layout: "post"
diff: 普及-
pid: P6974
tag: ['2015', 'ICPC']
---
# [NEERC 2015] Adjustment Office
## 题目描述

가리송과 안드레송은 정산소에서 일하고 있고, 미래를 예측하고자 한다. 둘에게는 큰 $n,x,n$ 정사각형이 주어진다。처음에 각 배열의 원소 $(x,y)$ 는 $x + y$ 로 채워져있다. $(1 \le x , y \le n)$.

미래 예측을 하는데에 두가지 타입의 쿼리가 들어온다.

- `R r` —$r$ 행의 모든 값들을 합한 결과를 출력하고, $r$ 행을 모두 $0$ 으로 바꾼다.
- `C c`—$c$ 열의 모든 값들을 합한 결과를 출력하고, $c$ 열을 모두 $0$ 으로 바꾼다.

쿼리 결과를 구하는 프로그램을 작성하시오.


## 输入格式

첫줄에는 배열의 크기 $n$ 과 쿼리의 개수 $q$ 가 입력된다. $(1 \le n \le 10^{6}, 1 \le q \le 10^{5})$.

그 다음 $q$ 개의 줄마다 `R r` (1 \le r \le n) 혹은 `C c` (1 \le c \le n)인 쿼리문이 입력된다.

## 输出格式

$q$ 개의 줄에 걸쳐서 $i$ 번째 쿼리의 결과를 출력한다. $(1 \le i \le q)$.
## 样例

### 样例输入 #1
```
3 7
R 2
C 3
R 2
R 1
C 2
C 1
R 3

```
### 样例输出 #1
```
12
10
0
5
5
4
0

```
## 提示

Time limit: 1 s, Memory limit: 256 MB. 


## 题目翻译

有一个大小为 $n\times n$ 的矩阵，每个位置的值为该位置的行数+列数。

接下来有 $q$ 次操作：

- $R\ m$：输出第 $m$ 行的总和并整行消去。
- $C\ m$：输出第 $m$ 列的总和并整列消去。

$1\leqslant n\leqslant 10^6$，$1\leqslant q\leqslant 10^5$，$1\leqslant m\leqslant n$。

Translated by Eason_AC  
2020.11.19


---

---
title: "[NEERC 2015] Easy Problemset"
layout: "post"
diff: 普及-
pid: P6977
tag: ['2015', 'ICPC']
---
# [NEERC 2015] Easy Problemset
## 题目描述



Perhaps one of the hardest problems of any ACM ICPC contest is to create a problemset with a reasonable number of easy problems. On Not Easy European Regional Contest this problem is solved as follows.

There are $n$ jury members (judges). They are numbered from $1$ to $n$ . Judge number $i$ had prepared $p_{i}$ easy problems before the jury meeting. Each of these problems has a hardness between $0$ and $49$ (the higher the harder). Each judge also knows a very large (say infinite) number of hard problems (their hardness is $50$) . Judges need to select $k$ problems to be used on the contest during this meeting.

They start to propose problems in the ascending order of judges numbers. The first judge takes the first problem from his list of remaining easy problems (or a hard problem, if he has already proposed all his easy problems) and proposes it. The proposed problem is selected for the contest if its hardness is greater than or equal to the total hardness of the problems selected so far, otherwise it is considered too easy. Then the second judge does the same etc. ; after the n-th judge, the first one proposes his next problem, and so on. This procedure is stopped immediately when $k$ problems are selected.

If all judges have proposed all their easy problems, but they still have selected less than $k$ problems, then they take some hard problems to complete the problemset regardless of the total hardness.

Your task is to calculate the total hardness of the problemset created by the judges.


## 输入格式



The first line of the input file contains the number of judges $n (2 \le n \le 10)$ and the number of problems $k (8 \le k \le 14)$ . The i-th of the following $n$ lines contains the description of the problems prepared by the i-th judge. It starts with $p_{i} (1 \le p_{i} \le 10)$ followed by $p_{i}$ non negative integers between $0$ and $49$ -- the hardnesses of the problems prepared by the i-th judge in the order they will be proposed.


## 输出格式



Output the only integer -- the total hardness of the selected problems.


## 样例

### 样例输入 #1
```
3 8
5 0 3 12 1 10
4 1 1 23 20
4 1 5 17 49

```
### 样例输出 #1
```
94

```
### 样例输入 #2
```
3 10
2 1 3
1 1
2 2 5

```
### 样例输出 #2
```
354

```
## 提示

Time limit: 1 s, Memory limit: 256 MB. 


## 题目翻译

有 $n$ 位出题人，他们要出 $k$ 道题。他们有一定数量的难度在 $0$ 到 $45$ 之间的简单题，和无限多道难度为 $50$ 的难题。出题人依次出题，每一位出题人都会选择他剩余的简单题目中的第一道，如果这道题目的难度大于等于之前选择的所有题目的难度之和，则会采用这道题目，否则就会丢弃这道题目。如果一位出题人的所有简单题目都用完了，他就会使用难题。直到选够了 $k$ 道题目，他们才会停止选题。


---

---
title: "[NEERC 2014] Knockout Racing"
layout: "post"
diff: 普及-
pid: P6995
tag: ['2014', 'ICPC']
---
# [NEERC 2014] Knockout Racing
## 题目描述



The races became more popular than ever at Pandora planet. But these races are quite unusual. There are $n$ cars participating in a race on the long straight track. Each car moves with a speed of $1$ meter per second. Track has coordinates in meters.

The car number $i$ moves between two points on the track with coordinates $a_{i}$ and $b_{i}$ starting at the second $0$ in the point $a_{i}.$ The car moves from $a_{i}$ to $b_{i},$ then from $b_{i}$ to $a_{i},$ then from $a_{i}$ to $b_{i}$ again, and so on.

Handsome Mike wants to knock some cars out of the race using dynamite. Thus he has $m$ questions. The question number $j$ is: what is the number of cars in the coordinates between $x_{j}$ and $y_{j}$ inclusive after $t_{j}$ seconds from the start?

Your task is to answer Mike's questions.


## 输入格式



The first line of the input file contains two integers $n$ and $m (1 \le n , m \le 1000)$ -- the number of cars in the race and the number of questions.

Each of the following $n$ lines contains a description of the car: two integers $a_{i}$ and $b_{i} (0 \le a_{i}, b_{i} \le 10^{9}, a_{i} ≠ b_{i})$ -- the coordinates of the two points between which the car $i$ moves.

Each of the following $m$ lines contains a description of the question: three integers $x_{j} , y_{j}$ , and $t_{j} (0 \le x_{j} \le y_{j} \le 10^{9}, 0 \le t_{j} \le 10^{9})$ -- the coordinate range and the time for the question $j$ .


## 输出格式



Write $m$ lines to the output file. Each line must contain one integer -- the answer to the corresponding question in order they are given in the input file.


## 样例

### 样例输入 #1
```
5 5
0 1
0 2
2 3
3 5
4 5
0 5 0
0 1 2
0 2 1
2 5 2
2 5 3

```
### 样例输出 #1
```
5
1
2
4
3

```
## 提示

Time limit: 1 s, Memory limit: 256 MB. 


## 题目翻译

# 题目简述
有$N$辆车在很长的直线赛道（可看作数轴）上行驶，每辆车在区间$[A_i,B_i]$间往返行驶，速度相同，有$M$个询问，每次询问一个区间$[X_i,Y_i]$在$T_i$时刻有多少辆车


---

---
title: "[CERC2013] What does the fox say?"
layout: "post"
diff: 普及-
pid: P7008
tag: ['模拟', '2013', 'ICPC']
---
# [CERC2013] What does the fox say?
## 题目描述

Determined to discover the ancient mystery—the sound that the fox makes—you went into the forest, armed with a very good digital audio recorder. The forest is, however, full of animals’ voices, and on your recording, many different sounds can be heard. But you are well prepared for your task: you know exactly all the sounds which other animals make. Therefore the rest of the recording—all the unidentified noises—must have been made by the fox.
## 输入格式

The first line of input contains the number of test cases $T$. The descriptions of the test cases follow:

The first line of each test case contains the recording—words over lower case English alphabet, separated by spaces. Each contains at most 100 letters and there are no more than 100 words. The next few lines are your pre-gathered information about other animals, in the format <animal> goes <sound>. There are no more than 100 animals, their names are not longer than 100 letters each and are actual names of animals in English. There is no fox goes ... among these lines.

The last line of the test case is exactly the question you are supposed to answer: what does the fox say?
## 输出格式

For each test case, output one line containing the sounds made by the fox, in the order from the recording. You may assume that the fox was not silent (contrary to popular belief, foxes do not communicate by Morse code).
## 样例

### 样例输入 #1
```
1
toot woof wa ow ow ow pa blub blub pa toot pa blub pa pa ow pow toot
dog goes woof
fish goes blub
elephant goes toot
seal goes ow
what does the fox say?

```
### 样例输出 #1
```
wa pa pa pa pa pa pow

```
## 提示

Time limit: 1000 ms, Memory limit: 1048576 kB. 

 Central Europe Regional Contest (CERC) 2013
## 题目翻译

### 题目大意

森林里面有很多声响，你想知道有哪些声响是由狐狸发出来的。

已知你搜集到了 $n$ 个声响，并且还知道某些其他动物能够发出的声响，已知如果没有哪一个声响是由其他任何一种动物发出来的话，那这个声响绝对是由狐狸发出来的。现在，给定你这 $n$ 个声响，以及某些其他动物能够发出的声响，请你求出狐狸发出的声响。

### 输入格式
**本题有多组询问。**

第一行包含一个整数 $T$，表示数据的组数。  
接下来若干组数据，每组数据由三部分组成：

- 第一行 $n$ 个仅由小写字母组成的字符串，代表搜集到的 $n$ 个声响。
- 接下来有若干行，代表某些其他动物能够发出的声响。格式为 ``<animal> goes <sound>``，其中 `<animal>` 代表动物的名称（仅由一个字符串组成），`<sound>` 代表这个动物发出的声响（仅由一个字符串组成）。保证不会在这些动物中出现狐狸。
- 最后一行，一个确定的字符串 ``what does the fox say?``。

### 输出格式
对于每组数据，输出仅一行，代表狐狸能够发出的声响。

### 数据范围
$n\leqslant 100$。  
保证每个字符串的长度不超过 $100$。

Translated by Eason_AC  
2020.10.30


---

---
title: "[CERC2013] Draughts"
layout: "post"
diff: 普及-
pid: P7012
tag: ['搜索', '2013', '广度优先搜索 BFS', 'ICPC']
---
# [CERC2013] Draughts
## 题目描述



Draughts (or checkers) is a game played by two opponents, on opposite sides of a $10 \times 10$ board. The board squares are painted black and white, as on a classic chessboard. One player controls the dark, and the other the light pieces. The pieces can only occupy the black squares. The players make their moves alternately, each moving one of his own pieces.

The most interesting type of move is capturing: if a diagonally adjacent square contains an opponent's piece, it may be captured (and removed from the game) by jumping over it to the unoccupied square immediately beyond it. It is allowed to make several consecutive captures in one move, if they are all made with a single piece. It is also legal to capture by either forward or backward jumps.

![](/upload/images2/dr.png)

The board before and after a single move with two captures.

You are given a draughts position. It is the light player's turn. Compute the maximal possible number of dark pieces he can capture in his next move.


## 输入格式



The first line of input contains the number of test cases $T$ . The descriptions of the test cases follow:

Each test case starts with an empty line. The following $10$ lines of $10$ characters each describe the board squares. The characters $#$ and . denote empty black and white squares, $W$ denotes a square with a light piece, $B -$ a square with a dark piece.


## 输出格式



For each test case print a single line containing the maximal possible number of captures. If there is no legal move (for example, there are no light pieces on the board), simply output $0$ .


## 样例

### 样例输入 #1
```
2

.#.#.#.#.#
#.#.#.#.#.
.#.#.B.#.#
#.#.#.#.#.
.#.#.B.#.#
#.#.W.#.#.
.#.#.#.#.#
#.#.#.B.#.
.#.#.#.#.#
#.#.#.#.#.

.#.#.#.#.#
#.#.#.#.#.
.#.#.B.#.#
#.B.#.B.#.
.#.#.B.#.#
#.B.W.#.#.
.#.B.B.#.#
#.#.#.#.#.
.#.B.B.#.#
#.#.#.#.#.

```
### 样例输出 #1
```
2
4

```
## 提示

Time limit: 2 s, Memory limit: 128 MB. 


## 题目翻译

国际跳棋（或称跳棋）是一种由两个对手在 $10 \times 10$ 的棋盘上进行的游戏。棋盘上的方块是黑色或白色的，就像经典的国际象棋棋盘一样。玩家一方控制黑棋，另一方控制白棋。棋子只能占据黑色的格子。棋手们交替走棋，各自移动自己的一个棋子。

最有趣的走法是吃掉：如果一个对角线相邻的格子里有对手的棋子，可以通过跳过它到紧挨着它的未被占领的格子来吃掉（并从游戏中删除被吃掉的这个棋子）。允许在一步棋中用一个棋子连续吃掉几个棋子。通过向前或向后的跳跃来吃子也是合法的。

你会得到一个棋子的位置。现在轮到白方了。计算他在下一步棋中能吃掉的最大可能的黑棋数量。

输入格式

输入的第一行包含测试用例 $T$ 的数量。接下来是测试用例的描述。

每个测试用例以空行开始。接下来的 10 行，每行都有 10 个字符，描述棋盘的方格。字符 # 和 . 表示空的黑色和白色方块，W 表示有浅色棋子的方块，B 表示有深色棋子的方块。

输出格式

对于每个测试案例，输出一行一个整数，代表最多可以吃黑子的个数。如果没有合法的棋步（例如，棋盘上没有白棋），只需输出 0。


---

---
title: "[NWRRC 2017] Auxiliary Project"
layout: "post"
diff: 普及-
pid: P7019
tag: ['2017', 'ICPC']
---
# [NWRRC 2017] Auxiliary Project
## 题目描述



Anna has just finished her course project. She has a lot of seven-segment LED displays as leftovers and a small power source. Each display consumes power proportionally to the number of lit segments, e.g . $‘9'$ consumes twice more power than $‘7'.$

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/15131/1.png)

Anna wonders what is the maximum possible sum of digits she is able to achieve, if her power source is able to light $n$ segments, and she wants to light exactly $n$ segments.


## 输入格式



The single line of the input contains one integer $n$ -- the number of segments that should be lit $(2 \le n \le 10^{6}).$


## 输出格式



Output a single integer -- the maximum possible sum of digits that can be displayed simultaneously.


## 样例

### 样例输入 #1
```
4

```
### 样例输出 #1
```
4

```
### 样例输入 #2
```
7

```
### 样例输出 #2
```
11

```
### 样例输入 #3
```
6

```
### 样例输出 #3
```
14

```
## 提示

Time limit: 3 s, Memory limit: 512 MB. 


## 题目翻译

用 LED 显示器来表示数字，表示方法如下：

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/15131/1.png)

你必须正好点亮 $n$ 段 LED 灯，使得这些灯能够组成一些数字。现在请你求出这些一位数和的最大值。

注：“一段”LED 灯指的是一条黑色的纵向短线或一条黑色的横向线段。如，`9` 由 $6$ 断组成。

$2\le n\le2\times 10^6$。

Translated by [cmll02](https://www.luogu.com.cn/user/171487)。


---

---
title: "[NWRRC 2017] Intelligence in Perpendicularia"
layout: "post"
diff: 普及-
pid: P7027
tag: ['2017', 'ICPC']
---
# [NWRRC 2017] Intelligence in Perpendicularia
## 题目描述



There are only two directions in Perpendicularia: vertical and horizontal. Perpendicularia government are going to build a new secret service facility. They have some proposed facility plans and want to calculate total secured perimeter for each of them.

The total secured perimeter is calculated as the total length of the facility walls invisible for the perpendicularly-looking outside observer. The figure below shows one of the proposed plans and corresponding secured perimeter.

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/15139/1.png)

Write a program that calculates the total secured perimeter for the given plan of the secret service facility.


## 输入格式



The plan of the secret service facility is specified as a polygon.

The first line of the input contains one integer $n$ -- the number of vertices of the polygon $(4 \le n \le 1000)$ . Each of the following $n$ lines contains two integers $x_{i}$ and $y_{i} -$ the coordinates of the i-th vertex $(−10^{6} \le x_{i}, y_{i} \le 10^{6}).$ Vertices are listed in the consecutive order.

All polygon vertices are distinct and none of them lie at the polygon's edge. All polygon edges are either vertical $(x_{i} = x_{i+1} or$ horizontal $(y_{i} = y_{i+1})$ and none of them intersect each other.


## 输出格式



Output a single integer -- the total secured perimeter of the secret service facility.


## 样例

### 样例输入 #1
```
10
1 1
6 1
6 4
3 4
3 3
5 3
5 2
2 2
2 3
1 3

```
### 样例输出 #1
```
6

```
## 提示

Time limit: 3 s, Memory limit: 512 MB. 


## 题目翻译

## 题目描述

给你一个数 $ n $ ，再给你 $ n $ 个点（$ x_i , y_i $），这 $ n $ 个点依次连成一个多边形。（保证多边形的每条边都与坐标轴平行或垂直，点不重合，点不在边上，边无相交）

求有多长的边是安全的？

（一个单位长度的边是安全的当且仅当它向外平移后能与其余边相遇，结合一下图看看）

## 输入格式

第一行一个数$ n $,表示有多少个定点。

接下来 $ n $ 行，行两个数 $ x_i \; y_i $ 表示每个点的坐标。

## 输出格式

一个数，表示安全的长度。


---

---
title: "[NWRRC 2016] Folding"
layout: "post"
diff: 普及-
pid: P7036
tag: ['2016', 'ICPC']
---
# [NWRRC 2016] Folding
## 题目描述



As you can remember, Alex is fond of origami. She switched from squares to rectangles, and rectangles are much more difficult to master. Her main interest is to determine what is the minimum possible number of folds required to transform $W \times H$ rectangle to $w \times h$ one. The result of each fold should also be rectangular, so it is only allowed to make folds that are parallel to the sides of the rectangle.

Help Alex and write a program that determines the minimum required number of folds.


## 输入格式



The first line of the input contains two integers $W$ and $H$ -- the initial rectangle dimensions. The second line contains two more integers $w$ and $h$ -- the target rectangle dimensions $(1 \le W , H , w , h \le 10^{9}).$


## 输出格式



Output a single integer -- the minimum required number of folds to transform the initial rectangle to the target one.

If the required transformation is not possible, output $−1$ .


## 样例

### 样例输入 #1
```
2 7
2 2

```
### 样例输出 #1
```
2

```
### 样例输入 #2
```
10 6
4 8

```
### 样例输出 #2
```
2

```
### 样例输入 #3
```
5 5
1 6

```
### 样例输出 #3
```
-1

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

### 题目大意：

求一个 $W\times H $ 的矩形通过折叠变为一个 $w\times h$ 的矩形的最少折叠次数，其中每次折叠的折痕必须平行于矩形的一边。

------------

### 输入格式：

第一行两个正整数 $W,H$，第二行两个正整数 $w,h$。

$1\le W,H,w,h\le10^9$

------------

### 输出格式：

输出最少折叠次数。若无法通过折叠变为目标矩形，输出 `-1`。



---

---
title: "[NWRRC 2016] King’s Heir"
layout: "post"
diff: 普及-
pid: P7041
tag: ['2016', 'ICPC']
---
# [NWRRC 2016] King’s Heir
## 题目描述



The king is dead, long live the king! After the sudden death of the king Fert XIII the people of the Flatland Kingdom are going to welcome the new king. Unfortunately, there is a problem, Fert has too many sons.

Actually, he has $n$ sons and he loved each new son more than all of his previous sons. Well, probably he just stopped loving his sons because of their bad behavior. Anyway, after the new son was born Fert made the new testament that declared that the newly born son would be the heir.

However, there is a problem. Only the king's son who is at least $18$ years old at the moment of the $king's death$ can become a new king. Now the ministers of the government are trying to find the correct $new king,$ but they seem to fail. Help them!


## 输入格式



The first line of the input contains three integers: $d , m$ and $y$ -- the day, the month and the year of the king's death, $d$ is from $1$ to $31$ , $m$ is from $1$ to $12 , y$ is from $1$ to $9999$ . It is guaranteed that there exists day $d$ in month $m$ , all months have the same number of days in Flatland as in our country, except that Flatland calendar doesn't have leap years, so February (month $2$) always has $28$ days.

The second line contains $n (1 \le n \le 100)$ -- the number of king's sons. The following $n$ lines contain three integers each $d_{i}, m_{i}$ and $ y_{i}$ and specify the birth dates of king's sons. All dates are correct and no son is born after or on the day of king's death. The king had no twins, so no two sons were born on the same date.


## 输出格式



Output one integer -- the number of the son that would become the king, or $−1$ if none of them is $at least 18$ years old. The sons are numbered from $1$ to $n$ in order they are described in the input. The youngest son who is at least $18$ years old at the moment of the king's death would become the king. $If the$ son has his 18th birthday exactly on the day of the king's death, he can become a king.


## 样例

### 样例输入 #1
```
22 10 2016
7
28 2 1999
22 7 1995
21 10 1998
23 10 1998
3 9 2000
1 4 2013
17 12 2004

```
### 样例输出 #1
```
3

```
### 样例输入 #2
```
22 10 2016
1
28 2 1999

```
### 样例输出 #2
```
-1

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

在国王去世的那一天，国王会让年龄最小但已满十八周岁的儿子继承国王，求哪一个儿子继承了国王，若没有儿子满足条件，则输出`-1`。保证国王不会有双胞胎。


---

---
title: "[NWRRC 2015] Alex Origami Squares"
layout: "post"
diff: 普及-
pid: P7048
tag: ['2015', 'Special Judge', 'ICPC']
---
# [NWRRC 2015] Alex Origami Squares
## 题目描述



Alex is fond of origami -- Japanese art of paper folding. Most origami designs start with a square sheet of paper. Alex is going to make a present for his mother. Present's design requires three equal square sheets of paper, but Alex has only one rectangular sheet. He is able to cut out squares of this sheet, but their sides should be parallel to the sides of the sheet. Help Alex to determine the maximum possible size of the paper squares he is able to cut out.


## 输入格式



The single line of the input file contains two integers $h$ and $w$ -- the height and the width of the sheet of paper $(1 \le h , w \le 1000)$ .


## 输出格式



Output a single real number -- the maximum possible length of the square side. It should be possible to cut out three such squares of $h \times w$ sheet of paper, so that their sides are parallel to the sides of the sheet.

Your answer should be precise up to three digits after the decimal point.


## 样例

### 样例输入 #1
```
210 297

```
### 样例输出 #1
```
105.0

```
### 样例输入 #2
```
250 100

```
### 样例输出 #2
```
83.333333

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 

spj provider:@[shenyouran](/user/137367).
## 题目翻译

## 题目描述

有一张矩形纸，要求将其裁成三个全等的正方形，且每一个正方形的侧面都与纸张的侧面平行，问裁成的小正方形边长最大是多少。

## 输入格式

一行两个整数 $h$ 和 $w$ $(1\le h,w\le 10^3)$ 表示矩形纸张的长和宽。

## 输出格式

输出一行一个实数，表示正方形边长的最大可能值。

你的答案与标准答案的相对及绝对误差不应超过 $10^{-3}$。


---

---
title: "[NWRRC 2015] Concatenation"
layout: "post"
diff: 普及-
pid: P7050
tag: ['2015', 'ICPC']
---
# [NWRRC 2015] Concatenation
## 题目描述



Famous programmer Gennady likes to create new words. One way to do it is to concatenate existing words. That means writing one word after another. For example, if he has words `cat` and `dog`, he would get a word `catdog`, that could mean something like the name of a creature with two heads: one cat head and one dog head.

Gennady is a bit bored of this way of creating new words, so he has invented another method. He takes a non-empty prefix of the first word, a non-empty suffix of the second word, and concatenates them. For example, if he has words `tree` and `heap`, he can get such words as `treap`, `tap`, or `theap`. Who knows what they could mean?

Gennady chooses two words and wants to know how many different words he can create using his new method. Of course, being a famous programmer, he has already calculated the answer. Can you do the same?


## 输入格式



Two lines of the input file contain words chosen by Gennady. They have lengths between $1$ and $100 000$ characters and consist of lowercase English letters only.


## 输出格式



Output one integer -- the number of different words Gennady can create out of words given in the input file.


## 样例

### 样例输入 #1
```
cat
dog

```
### 样例输出 #1
```
9

```
### 样例输入 #2
```
tree
heap

```
### 样例输出 #2
```
14

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

### 题目描述

著名的程序员 Gennady 喜欢创造新单词。其中一种方法是连接现有单词。

举个例子：如果 Gennady 有 `cat` 和 `dog` 两个词，那么他会得到一个新词： `catdog`，这可能意味着带有两个头的生物的名字：一个猫头和一个狗头。

Gennady 觉得这种创建新单词的方式有点无聊，因此他发明了另一种方法：使用第一个单词的非空前缀，第二个单词的非空后缀，并将它们连接起来。例如，如果他有单词 `tree` 和 `heap` ，则可以得到诸如 `treap`，`tap` 或 `theap` 之类的单词。

Gennady 选择了两个单词，并想知道他可以使用新方法创建多少个不同的单词。当然，作为著名的程序员，他已经计算出了答案。他突然想考考你，那么你能编写一个程序把答案计算出来吗？

### 输入格式

两行，每行有一个 Gennady 选择的单词 $s_i$ （$1\leq |s_i| \leq 100000$，$s_i$ 仅由小写英文字母组成）。

### 输出格式

输出一个整数，这个整数表示 Gennady 可以从这两个给定的单词中创建不同单词的数量。


---

---
title: "[NWRRC 2015] Easy Arithmetic"
layout: "post"
diff: 普及-
pid: P7052
tag: ['2015', 'Special Judge', 'ICPC']
---
# [NWRRC 2015] Easy Arithmetic
## 题目描述



Eva is a third-grade elementary school student. She has just learned how to perform addition and subtraction of arbitrary-precision integers. Her homework is to evaluate some expressions. It is boring, so she decided to add a little trick to the homework. Eva wants to add some plus and minus signs to the expression to make its value as large as possible.


## 输入格式



The single line of the input file contains the original arithmetic expression. It contains only digits, plus $(‘+')$ and minus $(‘-')$ signs.

The original expression is correct, that is:

numbers have no leading zeroes;

there are no two consecutive signs;

the last character of the expression is a digit.

The length of the original expression does not exceed $1000$ characters.


## 输出格式



Output a single line -- the original expression with some plus and minus signs added. Output expression must satisfy the same correctness constraints as the original one. Its value must be as large as possible.


## 样例

### 样例输入 #1
```
10+20-30

```
### 样例输出 #1
```
10+20-3+0

```
### 样例输入 #2
```
-3-4-1

```
### 样例输出 #2
```
-3-4-1

```
### 样例输入 #3
```
+10

```
### 样例输出 #3
```
+10

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

## 题目翻译 ##

现向一个仅含有加减号和数字的表达式中添加一些加号或减号， 使得操作后的**合法**表达式的值最大， 并输出操作后的表达式。

当一个表达式合法时满足以下条件：

1.每一个数字**不含前导零**。

2.表达式里没有两个**连续的符号**。

3.表达式的最后一个字符是数字。

保证原始表达式是合法的， 且长度不大于 $1000$。





---

---
title: "[NWRRC 2015] Hash Code Hacker"
layout: "post"
diff: 普及-
pid: P7055
tag: ['字符串', '2015', 'Special Judge', '哈希 hashing', '构造', 'ICPC']
---
# [NWRRC 2015] Hash Code Hacker
## 题目描述



According to Java standard library documentation, the hash code of String is computed as

$s[0] \times 31 ^ {n -1} + s[1] \times 31 ^ {n -2} + \cdots + s[n -1]$

Here $s[i]$ is the i-th character of the string, $n$ is the length of the string, and $^$ indicates exponentiation. Computation uses signed $32-bit$ integers in two's complement form.

Heather is going to hack the servers of Not Entirely Evil Recording Company $(NEERC).$ To perform an attack she needs $k$ distinct query strings that have equal hash codes. Unfortunately, NEERC servers accept query string containing lower- and uppercase English letters only.

Heather hired you to write a program that generates such query strings for her.


## 输入格式



The single line of the input file contains integer $k$ -- the number of required query strings to generate $(2 \le k \le 1000)$ .


## 输出格式



Output $k$ lines. Each line should contain a single query string. Each query string should be non-empty and its length should not exceed $1000$ characters. Query string should contain only lower- and uppercase English letters. All query strings should be distinct and should have equal hash codes.


## 样例

### 样例输入 #1
```
4

```
### 样例输出 #1
```
edHs
mENAGeS
fEHs
edIT

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

根据$Java$的标准库文件，字符串的哈希代码是这么计算的：

$$s[0]×31 ^{(n−1)}+s[1]×31^{(n−2)}+⋯+s[n−1]$$

在这里，s[i]指的是字符串中的第i位，n是字符串的长度。

这个计算过程用的是有符号的$32$位整数的二进制补码形式。

有一个人叫作 阖锕仄 $(Heather)$。他想要$hack$掉“不全是恶魔录音公司”$(NEERC)$。为了进行

一次攻击，阖锕仄需要$k$个有相同哈希代码的不同的询问字符串。不幸的是，$NEERC$的服务器

只接受只包含大小写字母的字符串。

阖锕仄请你帮忙写一个程序，以生成他需要的询问字符串。

-------

输入一个正整数$k$,代表需要的字符串的数量。

-------

输出有$k$行，每行的询问字符串都不应该为空，并且每行的字符串的长度应该小于等于1000个字符。

询问字符串的具体要求请看上文。

-------

时间限制：$2s$    

空间限制：$256MB$

翻译提供：@Trexmao


---

---
title: "[NWRRC 2015] Lucky Chances"
layout: "post"
diff: 普及-
pid: P7059
tag: ['2015', 'ICPC']
---
# [NWRRC 2015] Lucky Chances
## 题目描述



Lucky Chances is a lottery game. Each lottery ticket has a play field and a scratch area. The play field is a rectangular $r \times c$ field filled with numbers. The scratch area hides row and column numbers that specify the bet cell.

There are four possible winning directions: up, down, left and right. You win a direction if all numbers in this direction from the bet cell are strictly less than a number in the bet cell. And if the bet cell is on the edge of the grid, you win the corresponding direction automatically!

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/11477/1.png)

Unscratched ticket

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/11477/2.png)

Scratched ticket $1$

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/11477/3.png)

Scratched ticket $2$

Larry wants to choose the ticket that has maximum total number of winning directions for all possible bet cells. Write a program that determines this number for the given grid.


## 输入格式



The first line of the input file contains two integers $r$ and $c$ -- the number of rows and columns in the grid $(1 \le r , c \le 100)$ .

The following $r$ lines contain $c$ integers each -- the numbers printed on the grid. Each number is positive and does not exceed $1000$ .


## 输出格式



Output a single integer $w$ -- the total number of winning directions for the given grid.


## 样例

### 样例输入 #1
```
3 4
5 3 9 10
1 8 8 2
4 3 4 3

```
### 样例输出 #1
```
25

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

有一个名叫 Lucky chances 的游戏，游戏一开始给出一个 $r\times c$ 的矩阵，你可以选定矩阵中任意一个元素以及上、下、左、右四个方向中的任意一个方向进行游戏。如果这个方向上的任意一个元素都**严格小于**所选的元素，那么你就赢了。

试求出所有元素的能够使得你赢得游戏的方向的总和。

Translated by Eason_AC  
2020.11.15


---

---
title: "[NWRRC 2014] Alarm Clock"
layout: "post"
diff: 普及-
pid: P7060
tag: ['2014', 'Special Judge', 'ICPC']
---
# [NWRRC 2014] Alarm Clock
## 题目描述



Alice likes her digital alarm clock. She sets them up every evening. Last night Alice had a dream about her clock. Unfortunately, the only thing she is able to remember is the number of highlighted segments of the clock. Alice wonders what time was set on the clock in her dream.

Alice's clock have four digits: two for hours and two for minutes. For example, the clock below shows $9:30$ (note the leading zero).

![](https://cdn.luogu.com.cn/upload/image_hosting/6dl4fhwk.png)

The clock uses following digit representation.

![](https://cdn.luogu.com.cn/upload/image_hosting/igdzsez5.png)


## 输入格式



The only line of the input file contains single integer $n$ — the number of highlighted segments of the clock in Alice's dream $(0 \le n \le 30)$ .


## 输出格式



Output five characters in $\text{hh:mm}$ format — the time shown on the clock in Alice's dream. The time must be correct: $0 \le \text{hh} < 24$ and $0 \le \text{mm} < 60$ . If there are many possible correct times, output any of them. If there is none, output `Impossible`.


## 样例

### 样例输入 #1
```
23

```
### 样例输出 #1
```
09:30

```
### 样例输入 #2
```
28

```
### 样例输出 #2
```
Impossible

```
### 样例输入 #3
```
2

```
### 样例输出 #3
```
Impossible

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 

spj provider: @[rzh123](user/237530)
## 题目翻译

Alice梦见了一个时间，但她只记得了这个时间在电子钟上显现出来的**段数**，现在给出这个段数，让你反推Alice梦见的时间（若有多个答案，输出任意一个均可）  
**段数**：想必大家都听说过用火柴拼数字的游戏，比如1要用两个火柴，2要用5根火柴，8要用7根火柴等等（如题目图片所示），这里的**段数**指的就是一个时间的每一个数字，需要火柴数量的和（比如09：30，就要6+6+5+6=23个火柴）。  
**时间**：本题输出的时间仅有小时和分钟，其中小时在0到23之间，分钟在0到59之间  

输入一个整数n，n在0到30以内，代表Alice梦见的**段数**  
输出一个字符串，如果有合法的时间满足输入的段数，则输出这个时间（有多个输出任意一个均可），否则输出`Impossible`  

注意时间的前导零




---

---
title: "[NWRRC 2013] Arrangement of Contest"
layout: "post"
diff: 普及-
pid: P7079
tag: ['2013', 'ICPC']
---
# [NWRRC 2013] Arrangement of Contest
## 题目描述



Little Dmitry and little Petr want to arrange a contest. Their little friends submitted several task proposals and now Dmitry and Petr want to select some of them for the contest. As they are just little boys, they cannot estimate quality of tasks, but they know for sure that in good contest title of the first problem starts with A , the title of the second one -- with $B$ , and so on.

Given titles of the proposed tasks, help little brothers to determine the maximal number of problems in a good contest they can arrange.


## 输入格式



The first line contains single integer $n$ -- the number of problem proposals received by the little brothers $(1 \le n \le 100)$ .

Next $n$ lines contain titles of proposed problems, one per line. The length of each title does not exceed $30$ characters. Each title starts with an uppercase letter and contains only English letters, digits and underscores.


## 输出格式



Output a single number -- the maximal number of problems in a good contest. In case there is no good contest that may be arranged, output $0$ .


## 样例

### 样例输入 #1
```
12
Arrangement_of_Contest
Ballot_Analyzing_Device
Correcting_Curiosity
Dwarf_Tower
Energy_Tycoon
Flight_Boarding_Optimization
Garage
Heavy_Chain_Clusterization
Intellectual_Property
J
Kids_in_a_Friendly_Class
Lonely_Mountain

```
### 样例输出 #1
```
12

```
### 样例输入 #2
```
3
Snow_White_and_the_7_Dwarfs
A_Problem
Another_Problem

```
### 样例输出 #2
```
1

```
### 样例输入 #3
```
2
Good_Problem
Better_Problem

```
### 样例输出 #3
```
0

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

**题目描述**

小D和小P想要举行比赛。

他们收到了许多建议书，现在他们想要从这些报名书中挑选一些好的建议。

他们采纳的建议符合以下标准：第一个建议的开头为A，第二个建议的开头为B，以此类推。

请你帮助他们，确定他们所能采纳的建议的最大数量。

**输入格式**

第一行，一个正整数 $n$，表示建议数。

第 $2$ 至 $n+1$ 行，一行一个字符串，表示建议名称。

**输出格式**

一个整数，表示他们所能采纳的建议的最大数量。

**说明/提示**

对于 $100\%$ 的数据，$1\leq n \leq 100$


---

---
title: "[NWRRC 2013] Ballot Analyzing Device"
layout: "post"
diff: 普及-
pid: P7080
tag: ['2013', 'ICPC']
---
# [NWRRC 2013] Ballot Analyzing Device
## 题目描述



Election committee of Flatland is preparing for presidential elections. To minimize human factor in ballot counting they decided to develop an automated Ballot Analyzing Device $(BAD).$

There are $n$ candidates running for president. The ballot contains one square field for each candidate. The voter must mark exactly one of the fields. If no field is marked or there are two or more marked fields, the ballot is invalid. Each voter puts $his/her$ ballot to a special scanner in BAD. The scanner analyzes marks on the ballot and creates a special voting string of $n$ characters: $‘X'$ for marked field and $‘. '$ for unmarked one. Now voting strings must be analyzed to get the report. Your task is to develop a report generator for BAD.

Given voting strings for all ballots, your program must print the voting report. Candidates in the report must be arranged in order of decreasing number of votes. If two candidates have the same number of votes, they must have the same order as in a voting ballot. For each candidate calculate $his/her$ result in percent (if the candidate received $p$ votes, the result in percent is $100p/m)$ . The last line of the report must indicate the percentage of the invalid ballots.


## 输入格式



The first line contains two integers $n$ and $m$ -- the number of candidates and the number of ballots $(2 \le n \le 10$ ; $1 \le m \le 1000)$ . The following $n$ lines contain last names of candidates. Each name is a string of at most $100$ English letters. There is no candidate named `Invalid`.

Then $m$ lines follow, each of them contains one voting string.


## 输出格式



Print n+ $1$ lines. First print results for candidates in percent. For each candidate print $his/her$ last name followed by a space and then $his/her$ result in percent and a percent sign $‘\%'.$ The last line must specify the percentage of invalid ballots: a word `Invalid` followed by a space, the percentage of invalid ballots and a percent sign.

Round all numbers to exactly two digits after the decimal point. If the number is exactly in the middle of two representable numbers, output the greater one (e.g . output `12 . $35`$ for $12$ . $345$) .


## 样例

### 样例输入 #1
```
4 7
Loudy
Apples
Dogman
Miller
.X..
X...
....
..X.
..XX
..X.
..X.

```
### 样例输出 #1
```
Dogman 42.86%
Loudy 14.29%
Apples 14.29%
Miller 0.00%
Invalid 28.57%

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

有 $n$ 名选手参加一个比赛，有 $m$ 个人为他们投票。第 $i$ 个人的投票情况用一个长度为 $n$，并且仅包含 `.` 和 `X` 两个字符的字符串，其中，如果第 $j$ 位是 `X`，则第 $i$ 个人将票投给了第 $j$ 名选手，否则没有。规定每个投票者能且仅能将票投给一个人，否则都算无效票（即投的票数 $\geqslant 2$ 或者 $=0$）。请将每名选手按照他们所得到的票的比例排序（如果有两名选手得到的票的比例相同，在投票次序中先出现的那名选手排在前面），并输出他们的名字和得票比例，最后还要输出无效票所占的比例。

Translated by Eason_AC  
2020.11.12


---

---
title: "[NWRRC 2013] Energy Tycoon"
layout: "post"
diff: 普及-
pid: P7083
tag: ['2013', 'ICPC']
---
# [NWRRC 2013] Energy Tycoon
## 题目描述



Little Vasya is playing a new computer game -- turn-based strategy `Energy Tycoon`.

The rules of the game are quite simple:

The board contains $n$ slots arranged in a line.

There are power plants, one power plant occupies one or two consecutive slots, and produces one unit of energy.

Each turn the game allows you to build one new power plant, you can put it on the board if you wish. If there is no place for the new power plant, you can remove some older power plants.

After each turn, the computer counts the amount of energy produced by the power plants on the board and adds it to the total score.

![](/upload/images2/enegrgytycoon.png)

Vasya already knows the types of power plant he will be able to build each turn. Now he wants to know, what the maximum possible score he can get is. Can you help him?


## 输入格式



The first line of the input contains one integer $n (1 \le n \le 100 000)$ -- the number of slots on the board. The second line contains the string $s$ . The i-th character of the string is $1$ if you can build one-slot power plant at the i-th turn and the character is $2$ if you can build two-slot power plant at the i-th turn. The number of turns does not exceed $100 000$ .


## 输出格式



The output should contain a single integer -- the maximal score that can be achieved.


## 样例

### 样例输入 #1
```
3
21121

```
### 样例输出 #1
```
10

```
### 样例输入 #2
```
2
12

```
### 样例输出 #2
```
2

```
### 样例输入 #3
```
2
211

```
### 样例输出 #3
```
4

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

Vasya 正在玩一款新的电脑游戏 `Energy Tycoon`

游戏的规则非常简单：

有一行 $n$ 个空位。

有一些能源装置，每个能源装置会占用 $1$ 或 $2$ 个相邻的空位，并且每回合产生一个单位的能量。

在游戏里，每个回合可以建造一个新的能源装置（也可以不建造）。如果没有地方建新的能源装置，可以拆除一些旧的能源装置。

每一回合过后，电脑会统计这一回合内所有已经建造的能源装置产生的能量，并将其加到总分中。

Vasya 已经知道了每个回合他可以建造的能源装置的类型。现在他想知道，他能得到的最大分数是多少。你能帮他吗?


---

---
title: "[NWRRC 2013] Garage"
layout: "post"
diff: 普及-
pid: P7085
tag: ['2013', 'ICPC']
---
# [NWRRC 2013] Garage
## 题目描述



Wow! What a lucky day! Your company has just won a social contract for building a garage complex. Almost all formalities are done: contract payment is already transferred to your account.

So now it is the right time to read the contract. Okay, there is a sandlot in the form of $W \times H$ rectangle and you have to place some garages there. Garages are $w \times h$ rectangles and their edges must be parallel to the corresponding edges of the sandlot (you may not rotate garages, even by $90^{◦}).$ The coordinates of garages may be non-integer.

You know that the economy must be economical, so you decided to place as few garages as possible. Unfortunately, there is an opposite requirement in the contract: placing maximum possible number of garages.

Now let's see how these requirements are checked. . . The plan is accepted if it is impossible to add a new garage without moving the other garages (the new garage must also have edges parallel to corresponding sandlot edges).

![](https://www.acmicpc.net/upload/images2/garage.png)

Time is money, find the minimal number of garages that must be ordered, so that you can place them on the sandlot and there is no place for an extra garage.


## 输入格式



The only line contains four integers: $W , H , w , h$ -- dimensions of sandlot and garage in meters. You may assume that $1 \le w \le W \le 30 000$ and $1 \le h \le H \le 30 000$ .


## 输出格式



Output the optimal number of garages.


## 样例

### 样例输入 #1
```
11 4 3 2

```
### 样例输出 #1
```
2

```
### 样例输入 #2
```
10 8 3 4

```
### 样例输出 #2
```
2

```
### 样例输入 #3
```
15 7 4 2

```
### 样例输出 #3
```
4

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

你有一个 $W \times H$ 的大长方形。你又有无数个 $w \times h$ 的小长方形。请问，最少放入几个小长方形后，你无法再往这个大长方形里放入更多的小长方形。

所有小长方形不能重叠，也不能旋转。


---

---
title: "[ICPC 2022 Xi'an R] Clone Ranran"
layout: "post"
diff: 普及-
pid: P9360
tag: ['2022', 'O2优化', 'ICPC']
---
# [ICPC 2022 Xi'an R] Clone Ranran
## 题目描述

Ranran needs to prepare a contest! A contest is made of $c$ problems, and Ranran can do one of the following two things:

- Clone himself in $a$ minutes. That is, after $a$ minutes, there will be one more Ranran.
- Prepare a problem in $b$ minutes. That is, after $b$ minutes, there will be one more problem.

Note that a cloned Ranran can also do the two things above. A Ranran cannot do the two things at the same time.

Ranran wants to prepare the contest as fast as possible. But he is very lazy, so he asks you to find the minimum number of minutes to prepare the contest.

You need to answer $T$ queries independently.
## 输入格式

The first line contains an integer $T$ ($1\leq T\leq 10 ^ 5$).

Each of the next $T$ lines contains three integers $a$, $b$ and $c$ ($1\leq a, b, c\leq 10 ^ 9$), representing a query.
## 输出格式

For each test case, output a line with a single integer representing the answer.
## 样例

### 样例输入 #1
```
5
1 1 1
2 3 3
9 9 9
3 26 47
1064 822 1048576

```
### 样例输出 #1
```
1
7
45
44
21860

```
## 提示

**Source**: The 2022 ICPC Asia Xi'an Regional Contest Problem C.

**Author**: MagicSpark.
## 题目翻译

### 题目描述

然然需要准备一场有 $c$ 个问题的比赛！他可以进行两种操作：

- 在 $a$ 分钟内克隆一个自己；
- 在 $b$ 分钟内准备好一个问题。

克隆的然然也可以进行上述操作，但然然不能同时进行这两个操作。

然然希望尽快准备好比赛，但是他很懒，所以他让你求出准备比赛的最小分钟数。

共有 $T$ 组数据。

$1\leq T\leq 10 ^ 5$，$1\leq a, b, c\leq 10 ^ 9$。

### 输入格式

第一行一个整数 $T$。

接下来 $T$ 行，每行三个整数 $a, b, c$。

### 输出格式

对于每组数据，输出一行一个整数表示答案。




---

---
title: "[ICPC 2022 Xi'an R] Strange Sum"
layout: "post"
diff: 普及-
pid: P9367
tag: ['2022', 'O2优化', 'ICPC']
---
# [ICPC 2022 Xi'an R] Strange Sum
## 题目描述

Given a sequence $a_1, a_2, \ldots, a_n$.

You are going to select zero or more elements of $a$ so that: if you select $a_i$, then in any interval of length $i$ (formally, in $a[j, j + i - 1]$ for any $1 \le j \le n - i + 1$) you can select at most $2$ elements.

Calculate the maximal sum of the elements you select.
## 输入格式

The first line contains an integer $n$ ($2 \leq n \leq 10^5$).

The second line contains $n$ integers $a_1, a_2, \ldots, a_n$ ($-10^9 \leq a_i \leq 10^9$).
## 输出格式

Output a single integer denoting the answer.
## 样例

### 样例输入 #1
```
4
1 4 3 2

```
### 样例输出 #1
```
7

```
### 样例输入 #2
```
3
-10 -10 -10

```
### 样例输出 #2
```
0
```
## 提示

**Source**: The 2022 ICPC Asia Xi'an Regional Contest Problem J.

**Author**: JohnVictor.


---

---
title: "[CERC2019] Bob in Wonderland"
layout: "post"
diff: 普及-
pid: P9608
tag: ['模拟', '2019', 'ICPC']
---
# [CERC2019] Bob in Wonderland
## 题目背景

**题目译自 [CERC 2019](https://contest.felk.cvut.cz/19cerc/solved.html) 「[Bob in Wonderland](https://contest.felk.cvut.cz/19cerc/solved/bob.pdf)」**
## 题目描述

众所周知，链条是由相连的环组成的。通常，所有环都具有相同的形状和大小。Bob 是一名铁匠学徒，他正在制作自己的第一条铱链。他遵循传统的链条制作通则。上面写着：
- 如果没有链条，制作一个环，它将成为你链条的一部分。
- 如果有一条链，制作一个环，并将其连接到你已有的链中的另一个环上。

Bob 做了第一个环。然后，每次他制作另一个环时，他都会将其连接到链条上的其他环上，就像通则告诉他的那样。

当他完成时，他意识到他创造的物体根本不像一条普通的链。为了把链条拉直，他反复地拎起可能是链条两端的两个链环，并试图把它们尽可能地拉开。但在不同的地方，还有更多的“链条”从拉直的部分垂下来。

很明显，Bob 的工作还没有完成，他决定把他制作的物体称为未完成的链条。经过更多的思考，Bob 得出了一个结论，他必须更谨慎地断开一些环，并将它们重新连接到未完成的链条的其余部分，以获得他想要制作的直链。在直链中，每个环最多连接两个其他环，并且直链不能在不断开链环的情况下分离成更多的部分。

Bob 现在更加小心了，将用简单的步骤取得进展。在一个步骤中，他将选择一个环 A，连接到未完成链中的另一个环 B。然后，他会断开 A，将其与 B 分开，并将 A 重新连接到未完成的链条中的另一个环 C。如果最初连接到 A 的环不是 B，Bob 将在整个步骤中保持它们连接着 A。

Bob 获得直链所需执行的最小步骤数是多少？
## 输入格式

第一行包含一个整数 $N\ (1\le N\le 3\times 10^5)$，代表未完成的链条中的环数。所有环标号为 $1, 2, \dots, N$。

接下来 $N-1$ 行，每行包含两个整数，代表未完成链条中两个相连环的编号，按任意顺序给出。未完成的链条保证只有一个连体（即任意两个环之间都存在路径使他们相连）。
## 输出格式

输出一个整数，代表将 Bob 未完成的链条转化为直链的最少步骤数。
## 样例

### 样例输入 #1
```
5
4 3
1 2
4 5
3 2

```
### 样例输出 #1
```
0
```
### 样例输入 #2
```
6
1 3
3 2
3 4
4 5
4 6
```
### 样例输出 #2
```
2
```
### 样例输入 #3
```
7
1 2
2 3
3 4
4 5
3 6
6 7
```
### 样例输出 #3
```
1
```
## 提示

### 样例解释
![](https://cdn.luogu.com.cn/upload/image_hosting/541l6nqd.png)


---

---
title: "[ICPC 2020 Nanjing R] K Co-prime Permutation"
layout: "post"
diff: 普及-
pid: P9632
tag: ['2020', 'Special Judge', 'O2优化', 'ICPC', '南京']
---
# [ICPC 2020 Nanjing R] K Co-prime Permutation
## 题目描述

Kotori is very good at math (really?) and she loves playing with permutations and primes.

One day, she thinks of a special kind of permutation named $\textit{k co-prime permutation}$. A permutation $p_1,p_2,\cdots,p_n$ of $n$ is called a $k$ co-prime permutation of $n$ if there exists exactly $k$ integers $i$ such that $1 \le i \le n$ and $\text{gcd}(p_i,i)=1$, where $\text{gcd}(x,y)$ indicates the greatest common divisor of $x$ and $y$.

Given $n$ and $k$, please help Kotori construct a $k$ co-prime permutation of $n$ or just report that there is no such permutation.

Recall that a permutation of $n$ is a sequence of length $n$ containing all integers from $1$ to $n$.
## 输入格式

There is only one test case in each test file.

The first and only line contains two integers $n$ and $k$ ($1 \le n \le 10^6$, $0 \le k \le n$).
## 输出格式

Output one line containing $n$ integers $p_1, p_2, \cdots, p_n$ separated by one space, indicating the permutation satisfying the given constraints. If no such permutation exists output ``-1`` (without quotes) instead. If there are multiple valid answers you can print any of them.

Please, DO NOT output extra spaces at the end of each line, otherwise your answer may be considered incorrect!
## 样例

### 样例输入 #1
```
5 3
```
### 样例输出 #1
```
1 4 5 2 3
```
### 样例输入 #2
```
1 0
```
### 样例输出 #2
```
-1
```
## 题目翻译

### 题目描述

给定两个整数 $n$ 和 $k$，构造一个 $1 \sim n$ 的排列 $p_1,p_2,\cdots,p_n$，使得存在 $k$ 个整数 $i$ 满足 $1 \le i \le n$ 且 $\text{gcd}(p_i,i)=1$。

$\text{gcd}(x,y)$ 表示 $x$ 和 $y$ 的最大公约数。

### 输入格式

只有一组测试数据。

第一行输入两个整数 $n$ 和 $k$ $(1 \le n \le 10^6, 0 \le k \le n)$。

### 输出格式

输出一行 $n$ 个整数 $p_1, p_2, \cdots, p_n$，用空格分隔，表示一个满足给定的约束的排列。如果没有存在的排列则输出 ``-1``。如果有多个有效的答案，输出任意一个均可。

请不要在行末输出多余的空格，否则你的答案可能会被认为是错误的。

### 样例 #1

#### 样例输入 #1

```
5 3
```

#### 样例输出 #1

```
1 4 5 2 3
```

### 样例 #2

#### 样例输入 #2

```
1 0
```

#### 样例输出 #2

```
-1
```


---

---
title: "[ICPC 2021 Macao R] So I'll Max Out My Constructive Algorithm Skills"
layout: "post"
diff: 普及-
pid: P9656
tag: ['模拟', '2021', 'Special Judge', 'O2优化', 'ICPC', 'Ad-hoc', '澳门']
---
# [ICPC 2021 Macao R] So I'll Max Out My Constructive Algorithm Skills
## 题目描述

BaoBao the Witch is stuck in a maze with $n$ rows and $n$ columns, where the height of the cell in the $i$-th row and the $j$-th column is $h_{i,j}$. To get out of the maze, BaoBao has to find a path which passes through each cell exactly once. Each time she can only move into the neighboring cell sharing a same edge with the current one. But as we know, BaoBao is super lazy, so every time when she climbs up (that is to say, moving from a cell with a smaller height to another with a larger height) her happiness value will decrease. As her helping hand, your task is to find a valid path so that when moving along the path, the number of times BaoBao climbs up will not be more than the number of times she climbs down.

More formally, you need to find a sequence $(x_1, y_1), (x_2, y_2), \cdots, (x_{n^2}, y_{n^2})$ such that:
- For all $1 \le i \le n^2$, $ 1 \le x_i, y_i \le n$;
- For all $1 \le i, j \le n^2, i \neq j$, $ (x_i, y_i) \neq (x_j, y_j)$;
- For all $2 \le i \le n^2$, $|x_i - x_{i-1}| + |y_i - y_{i-1}| = 1$;
- $\sum\limits_{i=2}^{n^2}{[h_{x_{i-1}, y_{i-1}} < h_{x_i, y_i}]} \le \sum\limits_{i=2}^{n^2}{[h_{x_{i-1}, y_{i-1}} > h_{x_i, y_i}]}$, where $[P]$ equals $1$ when $P$ is true, and equals $0$ when it is false.

Additionally, you discover that the heights in all cells are a permutation of $n^2$, so you just need to output the height of each cell in a valid path.

## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ ($1 \le T \le 100$) indicating the number of test cases. For each test case:

The first line contains an integer $n$ ($2 \le n \le 64$) indicating the size of the maze.

For the following $n$ lines, the $i$-th line contains $n$ integers $h_{i, 1}, h_{i, 2}, \cdots, h_{i,n}$ ($1 \le h_{i, j} \le n^2$) where $h_{i,j}$ indicates the height of the cell in the $i$-th row and the $j$-th column. It's guaranteed that all integers in the input make up a permutation of $n^2$.
## 输出格式

For each test case output one line containing $n^2$ separated by a space indicating the heights of each cell in a valid path. If there are multiple valid answers you can output any of them. It's easy to prove that an answer always exists.

Please, DO NOT output extra spaces at the end of each line, or your answer may be considered incorrect!
## 样例

### 样例输入 #1
```
1
2
4 3
2 1
```
### 样例输出 #1
```
4 3 1 2
```
## 题目翻译

**【题目描述】**

宝宝女巫被困在一个 $n$ 行 $n$ 列的迷宫中，其中第 $i$ 行第 $j$ 列的单元格高度为 $h_{i,j}$。要走出迷宫，宝宝必须找到一条路径，该路径穿过每个单元格恰好一次。每次她只能移动到与当前单元格共享边的相邻单元格。但是众所周知，宝宝非常懒，所以每当她爬升（即从高度较低的单元格移动到高度较高的单元格）时，她的幸福值会减少。作为她的帮手，你的任务是找到一条有效的路径，使得沿着路径移动时，宝宝爬升的次数不多于她下降的次数。

更正式地说，你需要找到一个序列 $(x_1, y_1), (x_2, y_2), \cdots, (x_{n^2}, y_{n^2})$，使得：
- 对于所有的 $1 \le i \le n^2$，$ 1 \le x_i, y_i \le n$；
- 对于所有的 $1 \le i, j \le n^2, i \neq j$，$ (x_i, y_i) \neq (x_j, y_j)$；
- 对于所有的 $2 \le i \le n^2$，$|x_i - x_{i-1}| + |y_i - y_{i-1}| = 1$；
- $\sum\limits_{i=2}^{n^2}{[h_{x_{i-1}, y_{i-1}} < h_{x_i, y_i}]} \le \sum\limits_{i=2}^{n^2}{[h_{x_{i-1}, y_{i-1}} > h_{x_i, y_i}]}$，其中 $[P]$ 当 $P$ 为真时等于 $1$，当为假时等于 $0$。

此外，你发现所有单元格的高度都是 $n^2$ 的排列，所以你只需要输出有效路径中每个单元格的高度。

**【输入格式】**

有多个测试用例。输入的第一行包含一个整数 $T$（$1 \le T \le 100$），表示测试用例的数量。对于每个测试用例：

第一行包含一个整数 $n$（$2 \le n \le 64$），表示迷宫的大小。

接下来的 $n$ 行，第 $i$ 行包含 $n$ 个整数 $h_{i, 1}, h_{i, 2}, \cdots, h_{i,n}$（$1 \le h_{i, j} \le n^2$），其中 $h_{i,j}$ 表示第 $i$ 行第 $j$ 列单元格的高度。保证输入中的所有整数构成 $n^2$ 的排列。

**【输出格式】**

对于每个测试用例，输出一行，包含 $n^2$ 个由空格分隔的整数，表示有效路径中每个单元格的高度。如果有多个有效答案，你可以输出其中任何一个。很容易证明答案总是存在。

请不要在每行的末尾输出多余的空格，否则你的答案可能会被认为不正确！

翻译来自于：[ChatGPT](https://chatgpt.com/)。


---

---
title: "[ICPC 2022 Jinan R] Stack Sort"
layout: "post"
diff: 普及-
pid: P9677
tag: ['2022', 'O2优化', 'ICPC', '济南']
---
# [ICPC 2022 Jinan R] Stack Sort
## 题目描述

You are given a permutation with $n$ numbers, $a_1, a_2, \dots, a_n (1\leq a_i\leq n, a_i\neq a_j\textrm{ when }i\neq j)$. 

You want to sort these numbers using $m$ stacks. Specifically, you should complete the following task: 

Initially, all stacks are empty. You need to push each number $a_i$ to the top of one of the $m$ stacks one by one, in the order of $a_1,a_2,\ldots, a_n$. $\textbf{After pushing all numbers in the stacks}$, you pop all the elements from the stacks in a clever order so that the first number you pop is $1$, the second number you pop is $2$, and so on. **If you pop an element from a stack $S$, you cannot pop any element from the other stacks until $S$ becomes empty.**

What is the minimum possible $m$ to complete the task?
## 输入格式

The first line contains one integer $T~(1\le T \le 10^5)$, the number of test cases.

For each test case, the first line contains one positive integer $n~(1\le n \le 5 \times 10^5)$. The next line contains $n$ integers $a_1,\ldots, a_n~(1 \le a_i\le n)$ denoting the permutation. It is guaranteed that $a_1,\ldots, a_n$ form a permutation, i.e. $a_i\neq a_j$ for $i \neq j$. 

It is guaranteed that the sum of $n$ over all test cases is no more than $5\times 10^5$.

## 输出格式

For each test case, output the minimum possible $m$ in one line.
## 样例

### 样例输入 #1
```
3
3
1 2 3
3
3 2 1
5
1 4 2 5 3

```
### 样例输出 #1
```
3
1
4
```
## 题目翻译

你有一个 $n$ 项的数组 $a$ 和 $m$ 个栈，满足：
- $1\leq a_i\le n$，每一项各不相同。
- 对于 $i=1,2...n$，使 $a_i$ 成为任意一个栈的栈顶。
- 在每一项入栈后有一种方法使得 $1,2...,n$ 可以按照递增顺序依次出栈。

求 $m$ 的最小值。


---

---
title: "[NERC 2018]  Guest Student"
layout: "post"
diff: 普及-
pid: P9797
tag: ['2018', 'ICPC']
---
# [NERC 2018]  Guest Student
## 题目背景

翻译自 [NERC 2018](https://neerc.ifmo.ru/archive/2018/neerc-2018-statement.pdf) G 题。
## 题目描述

你作为某知名大学的客座学生，你想要在那里学习 $k$ 节课，但同时很遗憾，对于每周，你只有特定的时间才能有空去听课，如果 $a_i = 1$，说明周 $i$ 你有空，反之则没空。

你需要安排一个合理的日程，使得你去听第一节课到最后一节课中间经过的时间最短，当然第一节课听什么的顺序由你决定。
## 输入格式

第一行一个整数 $t (1 \leq t \leq 10000)$，表示数据组数。

接下来每组数据第一行一个整数 $k (1 \leq k \leq 10^8)$。

然后 $7$ 个整数 $a_1 \sim a_7$，$a_i = 1$ 表示有空，$a_i = 0$ 表示没空。
## 输出格式

对于每组数据，输出一个整数，表示最短的从第一节课到最后一节课所经过的时间。
## 样例

### 样例输入 #1
```
3
2
0 1 0 0 0 0 0
100000000
1 0 0 0 1 0 1
1
1 0 0 0 0 0 0
```
### 样例输出 #1
```
8
233333332
1
```
## 提示

对于所有数据，保证 $1 \leq t \leq 10000$，$1 \leq k \leq 10^8$ 且 $a_i \in \{0,1\}$。

对于样例一，从周二开始听课听到下周二，经过 $8$ 天。


---

---
title: "[ICPC 2020 Shanghai R] Fibonacci"
layout: "post"
diff: 普及-
pid: P9825
tag: ['数学', '2020', '数论', '上海', 'O2优化', 'ICPC']
---
# [ICPC 2020 Shanghai R] Fibonacci
## 题目描述

In mathematics, the Fibonacci numbers, commonly denoted as $f_n$, is a sequence such that each number is the sum of the two preceding numbers, starting with $1$ and $1$. That is, $f_1 = 1, f_2 = 1$ and $f_n = f_{n-2} + f_{n-1}~(n \ge 3)$.

Thus, the beginning of the sequence is $1, 1, 2, 3, 5, 8, 13, 21,\ldots$ .

Given $n$, please calculate $\sum_{i=1}^{n}{\sum_{j=i+1}^{n}{g(f_i,f_j)}}$, where $g(x,y) = 1$ when $x \cdot y$ is even, otherwise $g(x,y) = 0$.
## 输入格式

The only line contains one integer $n~(1\le n\le 10^9)$.
## 输出格式

Output one number -- $\sum_{i=1}^{n}{\sum_{j=i+1}^{n}{g(f_i,f_j)}}$.
## 样例

### 样例输入 #1
```
3
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
10
```
### 样例输出 #2
```
24
```
### 样例输入 #3
```
100
```
### 样例输出 #3
```
2739
```
## 题目翻译

在数学中，斐波拉契数列常被记为数列 $f_n$。该数列的首项 $f_1,f_2$ 均为 $1$，并满足递推公式 $f_n=f_{n-2}+f_{n-1}(n\ge 3)$。

因此，数列的前一些项为 $1,1,2,3,5,8,13,21,\cdots$。

若 $x\cdot y$ 为偶数，则函数 $g(x,y)=1$，否则 $g(x,y)=0$。求 $\sum\limits_{i=1}^n{\sum\limits_{j=i+1}^n{g(f_i,f_j)}}$ 的值。


---

---
title: "[ICPC 2021 Nanjing R] Oops, It's Yesterday Twice More"
layout: "post"
diff: 普及-
pid: P9840
tag: ['2021', 'Special Judge', 'O2优化', 'ICPC', '南京']
---
# [ICPC 2021 Nanjing R] Oops, It's Yesterday Twice More
## 题目描述

After the great success in 2018, 2019, and 2020, Nanjing University of Aeronautics and Astronautics (NUAA) will host the $\textit{International Collegiate Programming Contest}$ (ICPC) Nanjing regional for the fourth time.

Team $\textbf{\textit{Power of Two}}$ and team $\textbf{\textit{Three Hold Two}}$ won the champion for Tsinghua University in 2018 and 2019. In 2020, team $\textbf{\textit{Inverted Cross}}$ from Peking University won the champion. In 2021, there are around $700$ teams including $\textbf{the defending champion}$ participating in the contest. We are so excited to see who will win this year!

Although we can't gather in Nanjing this time due to the pandemic, we should still be grateful for the hard work done by all staff and volunteers for this contest. Thank you all for your great contribution to this contest!

In the 2018 contest, problem K, $\textbf{\textit{Kangaroo Puzzle}}$, requires the contestants to construct an operation sequence for the game:

> The puzzle is a grid with $n$ rows and $m$ columns ($1 \le n, m \le 20$) and there are some (at least $2$) kangaroos standing in the puzzle. The player's goal is to control them to get together. There are some walls in some cells and the kangaroos cannot enter the cells with walls. The other cells are empty. The kangaroos can move from an empty cell to an adjacent empty cell in four directions: up, down, left, and right.
>
> There is exactly one kangaroo in every empty cell in the beginning and the player can control the kangaroos by pressing the button U, D, L, R on the keyboard. The kangaroos will move simultaneously according to the button you press.
>
> The contestant needs to construct an operating sequence of at most $5 \times 10^4$ steps consisting of U, D, L, R only to achieve the goal.

In the 2020 contest, problem A, $\textbf{\textit{Ah, It's Yesterday Once More}}$, requires the contestants to construct an input map to hack the following code of the problem described before:

```cpp
#include <bits/stdc++.h>
using namespace std;
string s = "UDLR";
int main()
{
  srand(time(NULL));
  for (int i = 1; i <= 50000; i++) putchar(s[rand() % 4]);
  return 0;
}
```

Now in the 2021 contest, Paimon prepares another version of the problem for you. You are given a grid with $n$ rows and $n$ columns ($2 \leq n \leq 500$). All cells are empty and there is one kangaroo standing in each cell.

Similarly, you can control the kangaroos by pressing the button U, D, L, R on the keyboard. The kangaroos will move simultaneously according to the button you press. Specifically, for any kangaroo located in the cell on the $i$-th row and the $j$-th column, indicated by $(i,j)$:

- Button U: it will move to $(i-1,j)$ if $i>1$. Otherwise, it will stay in the same grid.
- Button D: it will move to $(i+1,j)$ if $i<n$. Otherwise, it will stay in the same grid.
- Button L: it will move to $(i,j-1)$ if $j>1$. Otherwise, it will stay in the same grid.
- Button R: it will move to $(i,j+1)$ if $j<n$. Otherwise, it will stay in the same grid.

You need to construct an operating sequence consisting only of characters `U`, `D`, `L`, and `R`. After applying it, you must make sure every kangaroo will gather at the specific cell $(a,b)$. The length of the operating sequence cannot exceed $3(n-1)$.
## 输入格式

There is only one test case in each test file.

The first and only line of the input contains three integers $n$, $a$, $b$ ($2 \leq n \leq 500$, $ 1 \leq a,b \leq n$) indicating the size of the grid and the target cell.
## 输出格式

Output a string consisting only of characters `U`, `D`, `L` and `R` in one line. And its length mustn't exceed $3(n-1)$. It can be proved that the answer always exists.
## 样例

### 样例输入 #1
```
3 3 3

```
### 样例输出 #1
```
RRDD
```
### 样例输入 #2
```
4 3 2

```
### 样例输出 #2
```
DLDLDLUR
```
## 题目翻译

有一张 $n\times n$ 的网格图，每个格子上都有一只袋鼠。对于一只在 $(i,j)$ 的袋鼠，有下面四个按钮：

- 按钮 `U`：如果 $i>1$，移动到 $(i-1,j)$，否则，原地不动；
- 按钮 `D`：如果 $i<n$，移动到 $(i+1,j)$，否则，原地不动；
- 按钮 `L`：如果 $j>1$，移动到 $(i,j-1)$，否则，原地不动；
- 按钮 `R`：如果 $j<n$，移动到 $(i,j+1)$，否则，原地不动。

每次按下按钮，都会对**所有的**袋鼠生效。请输出一种使得所有袋鼠最终都在 $(a,b)$ 的操作序列，并且序列的长度小于等于 $3\times(n-1)$。


---

---
title: "[EC Final 2021] DFS Order"
layout: "post"
diff: 普及-
pid: P9872
tag: ['2021', 'O2优化', '深度优先搜索 DFS', '树的遍历', 'ICPC']
---
# [EC Final 2021] DFS Order
## 题目描述

Prof. Pang has a rooted tree which is rooted at $1$ with $n$ nodes. These $n$ nodes are numbered from $1$ to $n$.

Now he wants to start the depth-first search at the root. He wonders for each node $v$, what is the minimum and the maximum position it can appear in the $\textbf{depth-first search order}$. The depth-first search order is the order of nodes visited during the depth-first search. A node appears in the $j$-th ($1\le j\le n$) position in this order means it is visited after $j-1$ other nodes. Because sons of a node can be iterated in arbitrary order, multiple possible depth-first orders exist. Prof. Pang wants to know for each node $v$, what are the minimum value and the maximum value of $j$ such that $v$ appears in the $j$-th position.

Following is a pseudo-code for the depth-first search on a rooted tree. After its execution, $\texttt{dfs\_order}$ is the depth-first search order.

```
let dfs_order be an empty list

def dfs(vertex x):
    append x to the end of dfs_order.
    for (each son y of x): // sons can be iterated in arbitrary order.
        dfs(y)

dfs(root)
```
## 输入格式

The first line contains a single integer $T~(1 \le T \le 10^6)$ denoting the number of test cases.

For each test case, the first line contains an integer $n~(1 \le n \le 10 ^ 5)$. Each of the next $n-1$ lines contains two integers $x$ and $y$, indicating node $x$ is node $y$'s parent ($1\le x, y\le n$). These edges form a tree rooted at $1$.

It is guaranteed that the sum of $n$ over all test cases is no more than $10^6$.
## 输出格式

For each test case, print $n$ lines. The $i$-th line contains two integers denoting the minimum and the maximum position node $i$ can appear in the depth-first search order.
## 样例

### 样例输入 #1
```
2
4
1 2
2 3
3 4
5
1 2
2 3
2 4
1 5
```
### 样例输出 #1
```
1 1
2 2
3 3
4 4
1 1
2 3
3 5
3 5
2 5
```
## 题目翻译

给定一棵以 $1$ 为根节点的树，若按**任意顺序**进行深度优先搜索，则第 $i$ 个点最小是第几个被搜到的以及最大是第几个？


---

---
title: "[EC Final 2021] Future Coder"
layout: "post"
diff: 普及-
pid: P9880
tag: ['2021', 'Special Judge', 'O2优化', 'ICPC']
---
# [EC Final 2021] Future Coder
## 题目描述

Prof. Pang builds his famous coding team recently. To pursue a gold medal in ICPC, hundreds of pupils join his team. Unfortunately, one of Prof. Pang's students believes that for any integers $a$ and $b$, $a\times b\ge a+b$. To disprove this proposition, Prof. Pang writes $n$ numbers $a_1,a_2,\ldots, a_n$ on a paper and wants you to count how many pairs of numbers $(a_i, a_j)$ ($1\le i < j\le n$) satisfies $a_i\times a_j<a_i+a_j$.
## 输入格式

The first line contains a single integer $T$ ($1\le T\le 10^6$) denoting the number of test cases.

For each test case, the first line contains a single integer $n$ ($1\le n\le 10^6$). The second line contains $n$ integers $a_1, a_2, \ldots, a_n$ ($-10^9\le a_i\le 10^9$).

It is guaranteed that the sum of $n$ over all test cases will not exceed $10^6$.
## 输出格式

For each test case, print one line containing the answer.
## 样例

### 样例输入 #1
```
2
8
3 -1 4 1 -5 9 2 -6
1
0

```
### 样例输出 #1
```
19
0

```
## 题目翻译

### 题目描述

共 $T$ 组数据，每组给出一个数 $n$ 和 $n$ 个数 $a_1,a_2,...,a_n$，求有多少个二元组 $(a_i,a_j)$ 满足 $a_ia_j<a_i+a_j$。

### 输入格式

第一行为一个数 $T$。

接下来 $T$ 组数据，每组数据第一行为一个数 $n$，第二行为 $n$ 个数 $a_1,a_2,...,a_n$。

### 输出格式

$T$ 行，为满足 $a_ia_j<a_i+a_j$ 的二元组 $(a_i,a_j)$ 的组数。

Translated from [FurippuWRY](https://www.luogu.com.cn/user/993779)。


---

---
title: "[ICPC 2018 Qingdao R] Function and Function"
layout: "post"
diff: 普及-
pid: P9897
tag: ['2018', 'O2优化', 'ICPC', '青岛']
---
# [ICPC 2018 Qingdao R] Function and Function
## 题目描述

If we define $f(0) = 1, f(1) = 0, f(4) = 1, f(8) = 2, f(16) = 1, \dots$, do you know what function $f$ means?

Actually, $f(x)$ calculates the total number of enclosed areas produced by each digit in $x$. The following table shows the number of enclosed areas produced by each digit:

![](https://cdn.luogu.com.cn/upload/image_hosting/sdv14tzu.png)

For example, $f(1234) = 0 + 0 + 0 + 1 = 1$, and $f(5678) = 0 + 1 + 0 + 2 = 3$.

We now define a recursive function $g$ by the following equations: 

$$\begin{cases} g^0(x) = x \\ g^k(x) = f(g^{k-1}(x)) & \text{if } k \ge 1 \end{cases}$$

For example, $g^2(1234) = f(f(1234)) = f(1) = 0$, and $g^2(5678) = f(f(5678)) = f(3) = 0$.

Given two integers $x$ and $k$, please calculate the value of $g^k(x)$.


## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ (about $10^5$), indicating the number of test cases. For each test case:

The first and only line contains two integers $x$ and $k$ ($0 \le x, k \le 10^9$). Positive integers are given without leading zeros, and zero is given with exactly one `0'.

## 输出格式

For each test case output one line containing one integer, indicating the value of $g^k(x)$.
## 样例

### 样例输入 #1
```
6
123456789 1
888888888 1
888888888 2
888888888 999999999
98640 12345
1000000000 0
```
### 样例输出 #1
```
5
18
2
0
0
1000000000
```
## 提示

![](https://cdn.luogu.com.cn/upload/image_hosting/fjjr5xin.png)
## 题目翻译

### 题目描述

如果我们定义 $f(0) = 1$，$f(1) = 0$，$f(4) = 1$，$f(8) = 2$，$f(16) = 1$ …… 你知道函数 $f$ 意味着什么吗？

其实，$f(x)$ 计算的是 $x$ 中每个数字所产生的封闭区域的总数。下表显示了每个数字产生的封闭区域数：

![](https://cdn.luogu.com.cn/upload/image_hosting/sdv14tzu.png)

例如，$f(1234) = 0 + 0 + 0 + 1 = 1$，$f(5678) = 0 + 1 + 0 + 2 = 3$。

现在，我们用以下等式定义递归函数 $g$： 

$$\begin{cases} g^0(x) = x \\ g^k(x) = f(g^{k-1}(x)) & \text{if } k \ge 1 \end{cases}$$

例如，$g^2(1234) = f(f(1234)) = f(1) = 0$，$g^2(5678) = f(f(5678)) = f(3) = 0$。

给定两个整数 $x$ 和 $k$，请计算 $g^k(x)$ 的值。

### 输入格式

有多个测试用例。输入的第一行包含一个整数 $T$（大约 $10 ^ 5$），表示测试用例的数量。
之后的每行包含两个整数 $x$ 和 $k$（$0 \le x, k \le 10^9$）。正整数不带前导零，零则正好是一个 "0"。

### 输出格式

对每个测试用例输出一行，其中包含一个整数，表示 $g^k(x)$ 的值。


---

