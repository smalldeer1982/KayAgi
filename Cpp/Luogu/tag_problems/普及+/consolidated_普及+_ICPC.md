---
title: "[ICPC 2024 Xi'an I] Make Them Straight"
layout: "post"
diff: 普及+/提高
pid: P10556
tag: ['2024', 'O2优化', 'ICPC']
---
# [ICPC 2024 Xi'an I] Make Them Straight
## 题目描述

There is a sequence $a$ of non-negative integers of length $n$, the $i$-th element of it is $a_i(1\leq i\leq n)$.

A sequence is defined as 'good' if and only if there exists a non negative integer $k(0\leq k\leq 10^6)$ that satisfies the following condition:

$a_{i}=a_{1}+(i-1)k$ for all $1\leq i\leq n$.

To make this sequence 'good', for each $i(1\leq i\leq n)$, you can do nothing, or pay $b_i$ coin to replace $a_i$ with any non-negative integer.

The question is, what is the minimum cost to make this sequence 'good'.
## 输入格式

The first line contains an integer $n(1\leq n\leq 2\times 10^5)$, described in the statement.

The second line contains $n$ integers $a_1,...,a_n(0\leq a_i\leq 10^6)$.

The third line contains $n$ integers $b_1,...,b_n(0\leq b_i\leq 10^6)$.
## 输出格式

One integer, the answer.
## 样例

### 样例输入 #1
```
5
1 4 3 2 5
1 1 1 1 1
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
5
1 4 3 2 5
1 9 1 1 1
```
### 样例输出 #2
```
3
```


---

---
title: "[ICPC 2024 Xi'an I] XOR Game"
layout: "post"
diff: 普及+/提高
pid: P10558
tag: ['2024', 'O2优化', 'ICPC']
---
# [ICPC 2024 Xi'an I] XOR Game
## 题目背景

# statement updated:
$z$ is the number of numbers whose values are $0$.
## 题目描述

Alice and Bob are playing a game against each other.

In front of them are a multiset $\{a_i\}$ of non-negative integers and a single integer $x$. Each number in $a$ is $0$ or $2^i(0\le i<k)$ before the game.

This game will be a turn-based game, and Alice will go first. In one person's turn, he or she will choose an integer from $a$. Let this number be $p$. Then this person will choose whether or not to make $x\gets x\oplus p$, then remove $p$ from $a$. Here, operation $\oplus$ means bitwise xor.

Alice wants to make $x$ as big as possible, and Bob wants to make $x$ as small as possible.

You are a bystander who wants to know the final value of $x$. However, the size of $a$ is a huge number. Formally, there are $b_i$ numbers whose values are $2^i$ in $a$ for all $0\le i<k$, and $z$ numbers whose values are $0$. But you still want to challenge this impossible problem.

If Alice and Bob are smart enough, please output the final value of $x$.
## 输入格式

The first line contains two integers $k,z(1\le k\le10^5,0\le z\le 10^9)$.

The next line contains $k$ integers, the $i$ -th integer is $b_{i-1}(0\le b_{i-1}\le10^9)$.
## 输出格式

Output the answer in binary format. Note that you should output exactly $k$ digit from high to low even though this number has leading $0$s.
## 样例

### 样例输入 #1
```
1 0
3
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
2 0
2 1
```
### 样例输出 #2
```
11
```
### 样例输入 #3
```
2 0
2 2
```
### 样例输出 #3
```
00
```


---

---
title: "[ICPC 2024 Xi'an I] Smart Quality Inspector"
layout: "post"
diff: 普及+/提高
pid: P10561
tag: ['2024', 'O2优化', 'ICPC']
---
# [ICPC 2024 Xi'an I] Smart Quality Inspector
## 题目描述

    
Ella has a factory. One day, her factory is facing a product quality inspection.
    
    
    
Her factory has $N$ production lines. Among the $N$ production lines, $N-K$ of them are qualified, and the other $K$ lines are unqualified. The fine of the $i$ -th$(1\leq i\leq K)$ unqualified line is $i$ Yuan.
    
    
    
There are $M$ quality inspectors here. For the $j$ -th$(1\leq j\leq M)$ quality inspector, he will inspect from the $l_i$ -th line to the $r_i$ -th line and find the unqualified production line with the largest fine among them, then impose this fine on Ella.
    
    
    
Ella does not want to receive so many fines, so she decides to renumber the $N$ production lines to receive the least amount of fines. Please help her.
    
    
    
In simple terms:
    
    
    
You have a sequence $A$ of length $N$, $A=[1,2,3,...,K,0,0,0,...,0]$. Here $N,K$ are given.
    
    
    
There are $M$ pairs of integers, each pair consists of two numbers $l_i,r_i$.
    
    
    
You need to rearrange sequence $A$ to minimize the following:
    
    
    
$$\sum_{i=1}^M \max_{j=l_i}^{r_i} (A_{j})$$
## 输入格式


    
The first line contains three integers $N,K,M(1\leq K\leq N\leq 20,1\leq M\leq 10^5)$, described in the statement.
    
    
    
Then $M$ lines, the $i$ -th line of them contains two integers $l_i,r_i(1\leq l_i\leq r_i\leq N)$.
    
## 输出格式


    
An integer indicates the answer.
## 样例

### 样例输入 #1
```
4 4 3
1 2
3 4
1 4
```
### 样例输出 #1
```
10
```


---

---
title: "[ICPC 2024 Xi'an I] Rubbish Sorting"
layout: "post"
diff: 普及+/提高
pid: P10564
tag: ['2024', 'O2优化', 'ICPC']
---
# [ICPC 2024 Xi'an I] Rubbish Sorting
## 题目描述


Bob has many pieces of rubbish. One day, he wants to sort them.
    
    
    
For every piece of rubbish, its type is expressed as a positive integer.
    
    
    
He has $q$ operations. For each operation, it is one of the following two operations.

- `1 s x` He tells you that the piece of rubbish named $s$ has a type of $x$.
- `2 s` He wants to ask you the type of rubbish $s$.


    
But his memories are not always accurate.
    
    
    
For each operation $2$, $s$ may not have appeared in the previous operation $1$s.
    
    
    
We define the similarity of two strings $s_1$ and $s_2$ as $\sum_{i=1}^{\min\{|s_1|,|s_2|\}} [s_{1,i}=s_{2,i}]$.
    
    
    
Here all the strings' indexes start at $1$.
    
    
    
For a string $s$, its type is the type of string which has the maximum similarity to $s$ among all the strings that have appeared in the previous operations $1$s. Note that if there are multiple strings that all have the maximum similarity to $s$, the type of $s$ is the minimum type of these strings' type.
    
    
    
Now, he wants you to solve this problem.
    
## 输入格式


The first line contains an integer $q(1\le q\le 3\times 10^5)$, which is the number of operations.
    
    
    
Next $q$ lines contain operations, one per line. They correspond to the description given in the statement.
    
    
    
It is guaranteed that for every operation $2$ there is at least one operation $1$ before it.
    
    
    
But some pieces of rubbish will have more than one type, you can consider it as the minimum type you have read.
    
    
    
The rubbish's names only consist of lowercase Latin letters.
    
    
    
$1 \le |s| \le 5, 1 \le x \le 10^9$
## 输出格式


    
For every operation $2$, you should print an integer in a single line that is the rubbish $s$'s type.
    
## 样例

### 样例输入 #1
```
4
1 aaa 1
2 aa
1 ab 2
2 bb
```
### 样例输出 #1
```
1
2
```
### 样例输入 #2
```

```
### 样例输出 #2
```

```


---

---
title: "[SEERC 2020] Reverse Game"
layout: "post"
diff: 普及+/提高
pid: P10737
tag: ['2020', 'ICPC']
---
# [SEERC 2020] Reverse Game
## 题目描述

Alice 和 Bob 在玩一个游戏，规则如下：

- 游戏开始前给定一个字符串 $s$。

- 每次行动，选择 $s$ 的一个子串 $t$，$t$ 只能是 `10`、`100`、`110`、`1010` 中的一个，反转 $t$ 的每个字符，例如 `100` 翻转为 `001`。

- 不能操作者输掉游戏。

Alice 先手，问双方同时采取最优策略的情况下，谁能赢。
## 输入格式

一个仅包含 $01$ 的字符串 $s\ (1 \leq |s| \leq 10^6)$。
## 输出格式

如果 Alice 胜利输出 `Alice`，Bob 胜利输出 `Bob`。
## 样例

### 样例输入 #1
```
010
```
### 样例输出 #1
```
Alice
```
### 样例输入 #2
```
1111
```
### 样例输出 #2
```
Bob
```
### 样例输入 #3
```
1010
```
### 样例输出 #3
```
Bob
```
### 样例输入 #4
```
1010001011001
```
### 样例输出 #4
```
Alice
```
## 提示

对于样例 $1$，选择子串 `10` 进行反转后 Bob 无法操作。


---

---
title: "[EC Final 2020] Namomo Subsequence"
layout: "post"
diff: 普及+/提高
pid: P10816
tag: ['2020', 'O2优化', 'ICPC']
---
# [EC Final 2020] Namomo Subsequence
## 题目描述

``gshfd1jkhaRaadfglkjerVcvuy0gf`` said Prof. Pang. 

To understand Prof. Pang's word, we would like to calculate the number of $\textit{namomo subsequence}$s of it. The word by Prof. Pang is a string $s$ with $n$ characters where each character is either an English letter (lower or upper case) or a digit. The $i$-th character of $s$ is denoted by $s[i]$ ($1\le i\le n$). A subsequence $t$ of $s$ is defined by a list of indices $t_1, \ldots, t_6$ such that $1\le t_1 < t_2 < \ldots < t_6\le n$. Let $compare(c_1, c_2)$ be a function on two characters such that $compare(c_1, c_2)=1$ when $c_1=c_2$ and $compare(c_1, c_2)=0$ otherwise. $t$ is a namomo subsequence of $s$ if and only if for any $1\le i<j\le 6$, $compare(s[t_i], s[t_j]) = compare(namomo[i], namomo[j])$, where $namomo[x]$ represents the $x$-th character of the string ``namomo`` ($1\le x\le 6$). 

Output the number of namomo subsequences of a given string $s$ modulo $998244353$.
## 输入格式

The first line contains a string $s$ with $n$ characters ($6\le n\le 1000000$). $s$ contains only lower case English letters (`a` -- `z`), upper case English letters (`A` -- `Z`) and digits (`0` -- `9`).
## 输出格式

Output one integer -- the answer modulo $998244353$.
## 样例

### 样例输入 #1
```
wohaha
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
momomo
```
### 样例输出 #2
```
0
```
### 样例输入 #3
```
gshfd1jkhaRaadfglkjerVcvuy0gf
```
### 样例输出 #3
```
73
```
### 样例输入 #4
```
retiredMiFaFa0v0
```
### 样例输出 #4
```
33
```
## 题目翻译

给你一个串 $s$，问你有多少个长度为 $6$ 且形如 $A B C D C D$ 的子序列。 

$6\le |s|\le 10^6$，字符集大小 $62$。


---

---
title: "[EC Final 2020] Rectangle Flip 2"
layout: "post"
diff: 普及+/提高
pid: P10817
tag: ['2020', 'O2优化', 'ICPC']
---
# [EC Final 2020] Rectangle Flip 2
## 题目描述

Prof. Pang enters a trap room in a dungeon. The room can be represented by an $n$ by $m$ chessboard. We use $(i, j)$ ($1\le i\le n$, $1\le j\le m$) to denote the cell at the $i$-th row and $j$-th column. Every second, the floor of one cell breaks apart (so that Prof. Pang can no longer stand on that cell.) After $nm$ seconds, there will be no cell to stand on and Prof. Pang will fall through to the next (deeper and more dangerous) level.

But Prof. Pang knows that calm is the key to overcome any challenge. So instead of being panic, he calculates the number of rectangles such that every cell in it is intact (i.e., not broken) after every second. (A rectangle represented by four integers $a, b, c$ and $d$ ($1\le a\le b\le n, 1\le c\le d\le m$) includes all cells $(i, j)$ such that $a\le i\le b, c\le j\le d$. There are $
\frac{n(n+1)}{2} \times \frac{m(m+1)}{2}$ rectangles in total.)
## 输入格式

The first line contains two integers $n$, $m$ ($1\le n, m\le 500$) separated by a single space. 

The $(i+1)$-th line contains two integers $a$, $b$ separated by a single space representing that the cell $(a, b)$ breaks apart at the $i$-th second. It is guaranteed that each cell appears exactly once in the input. 
## 输出格式

Output $nm$ lines. The $i$-th line should contain the number of rectangles such that every cell in it is intact after the first $i$ cells break apart.
## 样例

### 样例输入 #1
```
2 2
1 1
2 1
1 2
2 2
```
### 样例输出 #1
```
5
3
1
0
```
## 提示

In the example, after the first second, there are $3$ rectangles of area $1$ and $2$ rectangles of area $2$ that satisfy the constraint. So the first line should contain a $5$. After the second second, only cells in the second column remains intact. The answer should be $3$. After the third second, only one cell remains intact. The answer should be $1$. After the fourth second, all cells broke apart so the answer should be $0$. 
## 题目翻译

### 题目描述

庞教授进入了一个地下城的陷阱房间。这个房间可以用一个 $n$ 行 $m$ 列的棋盘来表示。我们用 $(i, j)$ ($1\le i\le n$, $1\le j\le m$) 来表示第 $i$ 行第 $j$ 列的单元格。每秒钟，有一个单元格的地板会破裂（这样庞教授就不能再站在这个单元格上了）。经过 $nm$ 秒后，将没有单元格可供站立，庞教授将跌落到下一个（更深且更危险的）层级。

但庞教授知道冷静是克服任何挑战的关键。因此，他没有惊慌，而是计算了在每秒钟后，所有单元格都完好的矩形的数量（即，每个单元格在矩形中都没有破裂）。一个矩形由四个整数 $a, b, c$ 和 $d$ ($1\le a\le b\le n, 1\le c\le d\le m$) 表示，包含所有 $(i, j)$ 使得 $a\le i\le b, c\le j\le d$。总共有 $
\frac{n(n+1)}{2} \times \frac{m(m+1)}{2}$ 个矩形。

### 输入格式

第一行包含两个整数 $n$, $m$ ($1\le n, m\le 500$)，用空格分隔。

第 $(i+1)$ 行包含两个整数 $a$, $b$，表示在第 $i$ 秒钟单元格 $(a, b)$ 破裂。保证每个单元格在输入中出现恰好一次。

### 输出格式

输出 $nm$ 行。第 $i$ 行应包含在前 $i$ 个单元格破裂之后，每个单元格都完好的矩形的数量。

### 提示

在示例中：在第一秒后，有 $3$ 个面积为 $1$ 的矩形和 $2$ 个面积为 $2$ 的矩形满足条件。因此第一行应该输出 $5$。在第二秒后，仅第二列中的单元格保持完好。答案应该是 $3$。在第三秒后，仅一个单元格保持完好。答案应该是 $1$。在第四秒后，所有单元格都破裂，所以答案应该是 $0$。

翻译者：[Immunoglobules](https://www.luogu.com.cn/user/1066251)


---

---
title: "[EC Final 2020] Square"
layout: "post"
diff: 普及+/提高
pid: P10827
tag: ['2020', 'O2优化', '素数判断,质数,筛法', 'ICPC']
---
# [EC Final 2020] Square
## 题目描述

Father Study loves math very much.

Given a sequence of integers $a_1,a_2,...,a_n$, Father Study wants to calculate another sequence of integers $t_1,t_2,...,t_n$ satisifing 
- For each $i~(1 \le i \le n)$, $t_i > 0$.
- For each $i~(1\le i < n)$, $a_i \times t_i \times a_{i+1} \times t_{i+1}$ is a square number. (In mathematics, a square number or perfect square is an integer that is the square of an integer, in other words, it is the product of some integer with itself.)
- $\prod_{i=1}^{n}{t_i}$ is minimized.


Please help Father Study to calculate the answer --- the minimum value of $\prod_{i=1}^{n}{t_i}$. Because the answer is too large, please output the answer modulo $1000000007$.

## 输入格式

The first line contains a single integer $n$ ($1\le n \le 100000$).

The second line contains $n$ integers $a_1, a_2, ..., a_n$ ($1 \le a_i \le 1000000$) separated by single spaces.
## 输出格式

Output one integer -- the answer modulo $1000000007$. 
## 样例

### 样例输入 #1
```
3
2 3 6
```
### 样例输出 #1
```
6
```


---

---
title: "[NERC2024] DAG Serialization"
layout: "post"
diff: 普及+/提高
pid: P12095
tag: ['2024', 'Special Judge', 'ICPC', '北欧亚大陆']
---
# [NERC2024] DAG Serialization
## 样例

### 样例输入 #1
```
5
set true
unset true
set false
unset false
unset false
2
1 4
5 2
```
### 样例输出 #1
```
5 1 3 2 4
```
### 样例输入 #2
```
3
unset true
unset false
set true
0
```
### 样例输出 #2
```
2 3 1
```
### 样例输入 #3
```
2
unset false
set true
1
2 1
```
### 样例输出 #3
```
-1
```
### 样例输入 #4
```
2
unset false
set false
0
```
### 样例输出 #4
```
-1
```


---

---
title: "[NERC2024] Expression Correction"
layout: "post"
diff: 普及+/提高
pid: P12096
tag: ['2024', 'Special Judge', 'ICPC', '北欧亚大陆']
---
# [NERC2024] Expression Correction
## 样例

### 样例输入 #1
```
2+2=4
```
### 样例输出 #1
```
Correct
```
### 样例输入 #2
```
123456789+9876543210=111111110+11-1
```
### 样例输出 #2
```
123456789+987654321=1111111100+11-1
```
### 样例输入 #3
```
10+9=10
```
### 样例输出 #3
```
Impossible
```
### 样例输入 #4
```
24=55-13
```
### 样例输出 #4
```
42=55-13
```
### 样例输入 #5
```
1000000000-10=9999999999
```
### 样例输出 #5
```
Impossible

```


---

---
title: "[NERC2024] Fix Flooded Floor"
layout: "post"
diff: 普及+/提高
pid: P12097
tag: ['2024', 'ICPC', '北欧亚大陆']
---
# [NERC2024] Fix Flooded Floor
## 题目描述

Archimedes conducted his famous experiments on buoyancy. But not everyone knows that while he was taking a bath, he was too focused and didn't notice the moment when the water overflowed over the edge of the bath and flooded the floor near the wall. His expensive parquet was irreversibly damaged!

Archimedes noticed that not all was lost, and there were still several undamaged parquet pieces. The parquet near the wall had the shape of a long narrow stripe of $2\times n$ cells. Archimedes had an unlimited supply of $1\times 2$ parquet pieces that could be placed parallel or perpendicular to the wall. Archimedes didn't want to cut the parquet pieces. As a great scientist, he figured out that there was exactly one way to restore the parquet by filling the damaged area of the parquet with the non-overlapping $1\times 2$ cell shaped pieces.

Help historians to check Archimedes' calculations. For the given configuration of the $2\times n$ parquet floor, determine whether there is exactly one way to fill the damaged parquet cells with the $1\times 2$ cell parquet pieces. If Archimedes was wrong, find out whether there are multiple ways to restore the parquet, or there are no ways at all.
## 输入格式

The first line contains a single integer $T$ ($1 \le T \le 10^4$)~--- the number of test cases to solve.

Then the description of test cases follows.

The first line of each test case contains a single integer $n$ ($1 \le n \le 2\cdot 10^5$) --- the length of the parquet floor.

The following two lines contain exactly $n$ characters each and describe the parquet, where $\texttt{.}$ denotes a damaged cell and $\texttt{\#}$ denotes an undamaged cell.

The total sum of $n$ in all $T$ test cases doesn't exceed $2\cdot 10^5$.
## 输出格式

For each test case, print $\tt{Unique}$ if there is exactly one way to restore the parquet, $\tt{Multiple}$ if there are multiple ways to do so, or $\tt{None}$ if it is impossible to restore the parquet.
## 样例

### 样例输入 #1
```
4
10
#.......##
##..#.##..
6
...#..
..#...
8
........
........
3
###
###
```
### 样例输出 #1
```
Unique
None
Multiple
Unique
```


---

---
title: "[NERC2024] Judicious Watching"
layout: "post"
diff: 普及+/提高
pid: P12101
tag: ['2024', 'ICPC', '北欧亚大陆']
---
# [NERC2024] Judicious Watching
## 题目描述

Jill loves having good grades in university, so she never misses deadlines for her homework assignments. But even more, she loves watching the series and discussing it with her best friend Johnny. And unfortunately, today she needs to choose between these two activities!

Jill needs to complete $n$ homework tasks. The $i$-th task would require $a_i$ minutes to complete and needs to be submitted to the teacher at most $d_i$ minutes from now. Also, there are $m$ new episodes of the series that Johnny and Jill want to discuss. The $j$-th episode lasts $l_j$ minutes. Jill can complete tasks in any order, but she needs to watch the episodes in the order they come. Neither completing a homework task nor watching an episode can be interrupted after starting. 

Johnny and Jill need to agree on a time $t_k$ when they would have a call to discuss the series. They are not sure yet which time to choose. For each possible time, compute the maximum number of episodes Jill could watch before that time while still being able to complete all $n$ homework tasks in time.

Note that for the purpose of this problem we assume that discussing the series with Johnny at time $t_k$ does not consume significant time from Jill and **can happen even if she is in the middle of completing any of her homework tasks**.
## 输入格式

There are several test cases in the input. The input begins with the number of test cases $T$ ($1 \le T \le 1\,000$). 

Each test case starts with a line with three integers $n$ ($1 \le n \le 200\,000$) --- the number of homework tasks, $m$ ($1 \le m \le 200\,000$) --- the number of episodes, and $q$ ($1 \le q \le 200\,000$) --- the number of possible times for the call with Jill.

The second line contains $n$ integers $a_i$ ($1 \le a_i \le 10^9$) --- the number of minutes it takes to complete the task. 
The next line contains $n$ integers $d_i$ ($1 \le d_i \le 10^{15}$) --- the deadline before which this task must be completed.
The next line contains $m$ integers $l_j$ ($1 \le l_j \le 10^9$) --- the length of episodes in the order they need to be watched.
The next line contains $q$ integers $t_k$ ($1 \le t_k \le 10^{15}$) --- the possible times of call with Jill. 

It is possible to complete all tasks within their respective deadlines.

The sum of each of $n$, $m$, $q$ over all test cases in input doesn't exceed $200\,000$.
## 输出格式

For each test case output a single line with $q$ integers --- for each possible time $t_k$ the maximum number of episodes Jill can watch.
## 样例

### 样例输入 #1
```
2
1 2 3
10
15
5 5
5 15 20
3 4 5
8 100 8
10 150 20
2 32 1 1
9 200 51 50 10
```
### 样例输出 #1
```
1 1 2
1 4 2 2 1
```


---

---
title: "[ICPC 2022/2023 WF] Turning Red"
layout: "post"
diff: 普及+/提高
pid: P12301
tag: ['图论', '2022', '2023', 'ICPC']
---
# [ICPC 2022/2023 WF] Turning Red
## 样例

### 样例输入 #1
```
8 6
GBRBRRRG
2 1 4
1 2
4 4 5 6 7
3 5 6 7
1 8
1 8

```
### 样例输出 #1
```
8

```
### 样例输入 #2
```
4 3
RGBR
2 1 2
2 2 3
2 3 4

```
### 样例输出 #2
```
impossible

```
### 样例输入 #3
```
4 4
GBRG
2 1 2
2 2 3
2 3 4
1 4

```
### 样例输出 #3
```
6

```
### 样例输入 #4
```
3 3
RGB
1 1
1 2
1 3

```
### 样例输出 #4
```
3

```


---

---
title: "[ICPC 2023 WF] Jet Lag"
layout: "post"
diff: 普及+/提高
pid: P12302
tag: ['贪心', '2023', 'Special Judge', 'ICPC', '线性 DP']
---
# [ICPC 2023 WF] Jet Lag
## 样例

### 样例输入 #1
```
3
30 45
60 90
120 180

```
### 样例输出 #1
```
2
0 30
90 120

```
### 样例输入 #2
```
1
0 60

```
### 样例输出 #2
```
impossible

```
### 样例输入 #3
```
7
31 32
35 41
48 55
69 91
1000 2022
2022 2023
2994 4096

```
### 样例输出 #3
```
5
0 5
10 28
56 68
92 900
2025 2900

```


---

---
title: "[NAC 2025] SLA Tomography"
layout: "post"
diff: 普及+/提高
pid: P12630
tag: ['2025', 'ICPC', 'NAC']
---
# [NAC 2025] SLA Tomography
## 题目描述

Stereolithography (SLA) is a 3D printing technique for hardening liquid material into a solid object one layer at a time using a laser. In this problem, we will consider a 2D simplification of SLA where the design of the object being printed can be represented as a rectangular grid of $\texttt{\#}$ and $\texttt{.}$ characters, where $\texttt{\#}$ represents a grid cell occupied by the object and $\texttt{.}$ is empty space. For example, here is a $4\times 8$ design:

```
..#.....
..#..#..
#.#.##..
#.#####.
```

A design does not have to consist of a single connected piece, but except for $\texttt{\#}$ cells on the bottom row of the design, **each $\texttt{\#}$ cell must be supported by another $\texttt{\#}$ cell directly below it**.

Printing an object using SLA proceeds layer-by-layer, starting from the bottom row. First, all cells in the row are flooded with a liquid photosensitive resin. Then a laser sweeps over the row, hardening the resin in all $\texttt{\#}$ cells into a solid and skipping all $\texttt{.}$ cells. Then, leftover liquid to the left of the leftmost $\texttt{\#}$ and to the right of the rightmost $\texttt{\#}$ drains away. Other liquid remains trapped. (If there are no $\texttt{\#}$ cells in the row---which can only happen for rows near the top of the design, after the object has been fully printed---all liquid drains away from the row.) This process then repeats for each subsequent row. For the design above, after printing is complete, resin remains trapped in all of the cells marked with a $\sim$ character below:

```
..#.....
..#~~#..
#~#~##..
#~#####.
```

While manually suctioning the leftover resin from the object, you start to wonder: how much of the original design can be recovered from knowing only how much liquid resin is left over in each row of the design after printing? For the above design, the amount of leftover resin in each row (starting from the top of the design) is $0$, $2$, $2$, $1$. Other designs also have the same leftover-resin fingerprint; for example:

```
....
#..#
#..#
#.##
```

Given a list of how many cells of liquid resin are left over in each row (starting from the top row), print the width of the narrowest object design whose rows would contain those amounts of liquid resin after printing. If no such design exists, print $\texttt{impossible}$.
## 输入格式

The first line of input contains a single integer $N (1 \leq N \leq 10^5)$, the number of rows in the object design.
$N$ lines follow, each containing a single integer $x$ ($0 \leq x \leq 10^9$), the number of cells of leftover liquid resin in each row of the desired object design (in order from top to bottom).

At least one row will have at least one leftover cell of liquid resin.
## 输出格式

Print the width (number of columns) in the narrowest object design whose number of leftover liquid resin cells in each row matches the input. ("Narrowest" means having the smallest possible number of columns). If no such design exists, print $\texttt{impossible}$ instead.
## 样例

### 样例输入 #1
```
4
0
2
2
1
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
3
4
0
4
```
### 样例输出 #2
```
11
```
## 提示

Sample Input 1 corresponds to the example above. One narrowest-possible design for Sample Input 2 is:

```
#....#.....
######.....
######....#
```


---

---
title: "[NERC 2022] King' s Puzzle"
layout: "post"
diff: 普及+/提高
pid: P12800
tag: ['2022', 'Special Judge', '构造', 'ICPC', 'Ad-hoc', 'NERC/NEERC']
---
# [NERC 2022] King' s Puzzle
## 题目描述

King Kendrick is a sovereign ruler of Kotlin Kingdom. He is getting ready for the next session of the government. Kotlin Kingdom consists of $n$ cities. These cities need to be connected by several bidirectional roads. Since ministries are responsible for aspects of safety and comfort of the kingdom's residents, some of them have made the following requirements:

- "All the cities should be connected by new roads, i.e. there should be a path from any city to any other city via the roads" --- Ministry of Transport and Digital Infrastructure.
- "There may not be a loop road --- a road that connects a city with itself" --- Ministry of Environment.
- "There should be at most one road between a pair of cities" --- Treasury Department.
- "If $a_i$ is the number of roads connected to $i$-th city, then the set $\{a_1, \ldots, a_n\}$ should consist of exactly $k$ distinct numbers" --- Ministry of ICPC.

King Kendrick has issues with the requirements from the Ministry of ICPC. He asks you to help him. Find any set of roads that suits all the requirements above or say that it is impossible.
## 输入格式

The only line of the input consists of two integers $n$ and $k$ ($1 \le k \le n \le 500$).
## 输出格式

If it is impossible to satisfy all the requirements, output $\texttt{NO}$ in the only line.

Otherwise, output $\texttt{YES}$ in the first line.

Output $m$ --- the number of roads ($0 \le m \le \frac{n \cdot (n - 1)}{2}$) in the second line.

Next $m$ lines should contain pairs of integers $a$ and $b$ --- the cities to connect by a road ($1 \le a, b \le n$).
## 样例

### 样例输入 #1
```
5 2
```
### 样例输出 #1
```
YES
4
1 2
1 3
1 4
1 5
```
### 样例输入 #2
```
4 1
```
### 样例输出 #2
```
YES
4
1 2
2 3
3 4
4 1
```
## 提示

### Sample 1 Explanation

![](https://cdn.luogu.com.cn/upload/image_hosting/cuv06x7v.png)

City 1 has four roads connected to it while other cities have exactly one.

### Sample 2 Explanation

![](https://cdn.luogu.com.cn/upload/image_hosting/xbm5xgu8.png)

Every city has exactly two roads connected to it.


---

---
title: "[NERC 2021] Interactive Treasure Hunt"
layout: "post"
diff: 普及+/提高
pid: P12822
tag: ['2021', '交互题', 'Special Judge', '构造', 'ICPC', 'Ad-hoc', 'NERC/NEERC']
---
# [NERC 2021] Interactive Treasure Hunt
## 题目描述

$\textit{This is an interactive problem.}$

There is a grid of $n\times m$ cells. Two treasure chests are buried in two different cells of the grid. Your task is to find both of them. You can make two types of operations:

- $\tt{DIG}$ $r$ $c$: try to find the treasure in the cell $(r, c)$. The interactor will tell you if you found the treasure or not.
- $\tt{SCAN}$ $r$ $c$: scan from the cell $(r, c)$. The result of this operation is the sum of Manhattan distances from the cell $(r, c)$ to the cells where the treasures are hidden. Manhattan distance from a cell $(r_1, c_1)$ to a cell $(r_2, c_2)$ is calculated as $|r_1 - r_2| + |c_1 - c_2|$.
You need to find the treasures in at most 7 operations. This includes both $\tt{DIG}$ and $\tt{SCAN}$ operations in total. To solve the test you need to call $\tt{DIG}$ operation at least once in both of the cells where the treasures are hidden.

### Interactive Protocol

Your program has to process multiple test cases in a single run. First, the testing system writes $t$ --- the number of test cases ($1\le t \le 100$). Then, $t$ test cases should be processed one by one.

In each test case, your program should start by reading the integers $n$ and $m$ ($2 \le n, m \le 16$).

Then, your program can make queries of two types:

- $\tt{DIG}$ $r$ $c$ ($1\le r\le n$; $1\le c\le m$). The interactor responds with integer $1$, if you found the treasure, and $0$ if not. If you try to find the treasure in the same cell multiple times, the result will be $0$ since the treasure is already found. 

- $\tt{SCAN}$ $r$ $c$ ($1\le r\le n$; $1\le c\le m$). The interactor responds with an integer that is the sum of Manhattan distances from the cell $(r, c)$ to the cells where the treasures were hidden. The sum is calculated for both cells with treasures, even if you already found one of them.

After you found both treasures, i.e. you received $1$ for two $\tt{DIG}$ operations, your program should continue to the next test case or exit if that test case was the last one. 
## 输入格式

See Interactive Protocol.
## 输出格式

See Interactive Protocol.
## 样例

### 样例输入 #1
```
1
2 3

1

1

3

0

1
```
### 样例输出 #1
```


SCAN 1 2

DIG 1 2

SCAN 2 2

DIG 1 1

DIG 1 3
```


---

---
title: "[NERC 2019] Elections"
layout: "post"
diff: 普及+/提高
pid: P12938
tag: ['2019', 'Special Judge', 'ICPC', 'NERC/NEERC']
---
# [NERC 2019] Elections
## 题目描述

Byteburg Senate elections are coming. Usually "United Byteland", the ruling Byteland party, takes all the seats in the Senate to ensure stability and sustainable development. But this year there is one opposition candidate in one of the constituencies. Even one opposition member can disturb the stability in the Senate, so the head of the Party asks you to ensure that the opposition candidate will not be elected.

There are $n$ candidates, numbered from 1 to $n$. Candidate $n$ is the opposition candidate. There are $m$ polling stations in the constituency, numbered from 1 to $m$. You know the number of votes cast for each candidate at each polling station. The only thing you can do to prevent the election of the opposition candidate is to cancel the election results at some polling stations. The opposition candidate will be elected if the sum of the votes cast in their favor at all non-canceled stations will be **strictly greater** than the analogous sum for every other candidate. 

Your task is to prevent the election of the opposition candidate by canceling the election results at the minimal possible number of polling stations. Notice that solution always exists, because if you cancel the elections at all polling stations, the number of votes for each candidate will be 0, and the opposition candidate will not be elected.
## 输入格式

The first line of the input contains two integers $n$ and $m$ ($2\le n\le 100$; $1\le m \le 100$) --- the number of candidates and the number of polling stations. The next $m$ lines contain the election results at each polling station with $n$ numbers on each line. In the $i$-th line the $j$-th number is $a_{i,j}$ --- the number of votes cast for the candidate $j$ at the station $i$ ($0\le a_{i,j} \le 1\,000$).
## 输出格式

In the first line output integer $k$ --- the minimal number of the polling stations in which you need to cancel the election results. In the second line output $k$ integers --- the indices of canceled polling stations, in any order. If there are multiple ways to cancel results at $k$ stations, output any one of them.
## 样例

### 样例输入 #1
```
5 3
6 3 4 2 8
3 7 5 6 7
5 2 4 7 9
```
### 样例输出 #1
```
2
3 1
```
### 样例输入 #2
```
2 1
1 1
```
### 样例输出 #2
```
0
```
### 样例输入 #3
```
3 3
2 3 8
4 2 9
3 1 7
```
### 样例输出 #3
```
3
1 2 3
```
## 提示

In the first example, the candidates from 1 to 5 received 14, 12, 13, 15, and 24 votes correspondingly. The opposition candidate has the most votes. However, if you cancel the election results at the first and the third polling stations, then only the result from the second polling station remains and the vote sums become 3, 7, 5, 6, and 7, without the opposition candidate being in the lead anymore. 


---

---
title: "[NERC 2019] Lexicography"
layout: "post"
diff: 普及+/提高
pid: P12945
tag: ['2019', 'Special Judge', 'ICPC', 'NERC/NEERC']
---
# [NERC 2019] Lexicography
## 题目描述

Lucy likes letters. She studied the definition of the lexicographical order at school and plays with it.

At first, she tried to construct the lexicographically smallest word out of given letters. It was so easy! Then she tried to build multiple words and minimize one of them. This was much harder!

Formally, Lucy wants to make $n$ words of length $l$ each out of the given $n \cdot l$ letters, so that the $k$-th of them in the lexicographic order is lexicographically as small as possible.
## 输入格式

The first line contains three integers $n$, $l$, and $k$ ($1\le k \le n \le 1\,000$; $1 \le l \le 1\,000$) --- the total number of words, the length of each word, and the index of the word Lucy wants to minimize.

The next line contains a string of $n \cdot l$ lowercase letters of the English alphabet.
## 输出格式

Output $n$ words of $l$ letters each, one per line, using the letters from the input. Words must be sorted in the lexicographic order, and the $k$-th of them must be lexicographically as small as possible. If there are multiple answers with the smallest $k$-th word, output any of them.
## 样例

### 样例输入 #1
```
3 2 2
abcdef
```
### 样例输出 #1
```
af
bc
ed
```
### 样例输入 #2
```
2 3 1
abcabc
```
### 样例输出 #2
```
aab
bcc
```


---

---
title: "[NWRRC 2023] Game of Nim"
layout: "post"
diff: 普及+/提高
pid: P13587
tag: ['动态规划 DP', '2023', '前缀和', 'ICPC', 'NWRRC']
---
# [NWRRC 2023] Game of Nim
## 题目描述

Georgiy and Gennady are playing a new game they have just invented after learning about the classical game of Nim. This game is played with $n$ stones and consists of two stages.

In the setup stage, Georgiy chooses a positive integer $p < n$ and puts a pile of $p$ stones on a game field.
After that, Gennady forms an arbitrary number of piles, each containing an arbitrary number of stones, using all $(n - p)$ stones not used by Georgiy.

For example, if $n = 10$ and $p = 2$, Gennady can form:

- $8$ piles of $1$ stone each,
- or one pile of $5$ stones and one pile of $3$ stones,
- or $2$ piles of $2$ stones and $4$ piles of $1$ stone,
- or one pile of $8$ stones,
- etc.

After the setup stage, the Nim stage comes. At this stage, the game of Nim is played. Players take turns, starting from Georgiy. On each turn, the player must remove at least one stone and may remove any number of stones, provided they all come from the same pile. The player who takes the last stone wins at Nim and, consequently, wins the entire game.

Georgiy and Gennady have just started the game, and now it is the middle of the setup stage: Georgiy has already made his pile of $p$ stones, but Gennady has not divided the remaining $(n - p)$ stones into piles yet. Now Gennady wants to know what his chances are to win the game.

You are to calculate the number of ways Gennady can divide $(n - p)$ stones into piles so that he will win the game, assuming that both players will play Nim optimally.

As you may know, according to the Sprague-Grundy theory, Gennady will win if and only if the bitwise exclusive or (XOR) of all pile sizes (the pile of $p$ stones and all piles made from the remaining $(n-p)$ stones) is equal to zero.

Since the answer can be large, please calculate it modulo $m$. Two ways are considered to be different
if the corresponding multisets of pile sizes are different--- that is, the order of piles does not matter.
## 输入格式

The only line contains three integers $n$, $p$, and $m$, denoting the total number of stones in the game, the size of the pile chosen by Georgiy, and the value of the modulus ($1 \le p < n \le 500$; $2 \le m \le 10^9$).
## 输出格式

Print the number of ways Gennady can divide the remaining $(n - p)$ stones into piles so that he will win the game, modulo $m$.
## 样例

### 样例输入 #1
```
8 3 1000
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
5 2 1000
```
### 样例输出 #2
```
0
```
## 提示

In the first example, the only two winning ways for Gennady to divide the remaining $5$ stones are:

- one pile of $3$ stones and $2$ piles of $1$ stone,
- or one pile of $2$ stones and $3$ piles of $1$ stone.

In the second example, no matter how Gennady divides the remaining $3$ stones, he is bound to lose.


---

---
title: "[ICPC 2025 APC] Pho Restaurant"
layout: "post"
diff: 普及+/提高
pid: P13622
tag: ['2024', 'ICPC']
---
# [ICPC 2025 APC] Pho Restaurant
## 题目描述

您可能知道，越南河粉（pho）是河内最常见的菜肴之一。它包含一种特殊的米粉、肉（通常是牛肉或鸡肉）和葱，浸在美味的汤中。越南人早餐、午餐、晚餐甚至便餐都喜欢吃河粉。对于游客来说，尤其是在河内寒冷的天气里，品尝河粉是必做之事。

你在越南经营一家有 $n$ 张餐桌（编号为 $1$ 到 $n$）的 *phở bò*（牛肉河粉）餐厅。2024 年 ICPC 亚洲及太平洋锦标赛的参赛者们正在您的餐厅里。每位参赛者最初都坐在某张餐桌旁，且每张餐桌最初都至少有一位参赛者。每位参赛者想点两种最著名的河粉之一：*phở tái*（半熟牛肉河粉）或 *phở chín*（全熟牛肉河粉）。餐桌 $i$ 的初始状态由二进制字符串 $S_i$ 表示。$S_i$ 的长度是最初坐在该桌的参赛者人数。如果最初坐在该桌的第 $j$ 位参赛者想点 *phở tái*，则 $S_i$ 的第 $j$ 个字符为 $0$；如果想点 *phở chín*，则为 $1$。

为了便于记录订单，餐厅希望坐在同一桌的参赛者点同样的菜。也就是说，对于每张餐桌，以下至少有一条必须成立：
* 所有坐在该桌的参赛者都想点 *phở tái*。
* 所有坐在该桌的参赛者都想点 *phở chín*。

为了满足此要求以及参赛者的订单，您需要将零名或多名参赛者移动到其他餐桌。目标餐桌必须是这 $n$ 张餐桌之一。换句话说，您不能增加新的餐桌。每张餐桌可容纳的参赛者数量没有限制。移动参赛者后，每张餐桌都应满足以下条件：要么该餐桌没有参赛者，要么所有坐在该餐桌的参赛者都点同样的菜。

由于移动参赛者需要时间，您希望计算出需要移动的参赛者的最少人数。
## 输入格式

输入的第一行包含一个整数 $n$ ($2 \le n \le 100,000$)。

接下来的 $n$ 行，每行包含一个二进制字符串。第 $i$ 行包含 $S_i$ ($1 \le |S_i| \le 200,000$)。

所有 $i$ 的 $|S_i|$ 的总和不超过 $500,000$。
## 输出格式

输出一个整数，代表您需要移动的参赛者的最少人数。
## 样例

### 样例输入 #1
```
4
11101101
00
10001
10
```
### 样例输出 #1
```
5
```
### 样例输入 #2
```
2
101010
010101

```
### 样例输出 #2
```
6
```
### 样例输入 #3
```
5
0000
11
0
00000000
1
```
### 样例输出 #3
```
0
```
## 提示

**样例解释 #1**

你可以移动
* 最初坐在 1 号桌的第七位参赛者到 3 号桌，
* 最初坐在 1 号桌的第四位参赛者到 4 号桌，
* 最初坐在 3 号桌的第一和第五位参赛者到 1 号桌，以及
* 最初坐在 4 号桌的第一位参赛者到 1 号桌。

这样一来，所有坐在 1 号桌的参赛者点的都是 *phở chín*，而坐在其他桌的参赛者点的都是 *phở tái*。可以证明，无法在移动少于 5 名参赛者的情况下满足要求。


---

---
title: "[NWRRC 2021] Clean Up!"
layout: "post"
diff: 普及+/提高
pid: P13630
tag: ['贪心', '2021', '字典树 Trie', 'ICPC', 'NWRRC']
---
# [NWRRC 2021] Clean Up!
## 题目描述

Once Charlie decided to start a new life by deleting all files in his Downloads directory. It's easy to do that using $\texttt{bash}$ shell! It has two useful features: the $\texttt{rm}$ command, which removes all files given as arguments, and patterns, which are replaced with the list of files matching them before executing the command.

Charlie ran $\texttt{rm *}$, but received an $\texttt{Argument list too long}$ response. Unfortunately, after $\texttt{bash}$ replaced $\texttt{*}$ with the names of all files in the Downloads directory, it failed to run the command because it had too many arguments.

After some experiments, Charlie realized he can execute $\texttt{rm abc*}$ to delete all files with names starting with $\texttt{abc}$ if there are at most $k$ such files. If more than $k$ files match this pattern, none of them will be deleted. Of course, he can replace $\texttt{abc}$ with any string.

Help Charlie to find the smallest number of $\texttt{rm}$ commands needed to delete all files. Assume that he can only use the $\texttt{rm}$ command as $\texttt{rm <prefix>*}$, where $\texttt{<prefix>}$ consists of lowercase English letters (and can be empty). 
## 输入格式

The first line contains two integers $n$ and $k$ --- the number of files to delete, and the maximum number of files that can be deleted by one $\texttt{rm}$ command ($1 \le n, k \le 3 \cdot 10^5$).

Each of the next $n$ lines contains a single string, denoting a file name. All file names are distinct, non-empty, and consist of lowercase English letters. The total length of all file names doesn't exceed $3 \cdot 10^5$.
## 输出格式

Print a single integer --- the smallest number of $\texttt{rm}$ commands needed to delete all files.
## 样例

### 样例输入 #1
```
4 2
a
abc
abd
b
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
4 2
d
c
ab
a
```
### 样例输出 #2
```
2
```
### 样例输入 #3
```
5 3
please
remove
all
these
files
```
### 样例输出 #3
```
3
```
## 提示

In the first example test, Charlie can execute $\texttt{rm ab*}$ to delete files $\texttt{abc}$ and $\texttt{abd}$, and then execute $\texttt{rm~*}$ to delete files $\texttt{a}$ and $\texttt{b}$. Note that he can't just run $\texttt{rm *}$ immediately, because initially all four files match an empty prefix. 


---

---
title: "[NWRRC 2021] Kaleidoscopic Route"
layout: "post"
diff: 普及+/提高
pid: P13638
tag: ['图论', '2021', 'Special Judge', '广度优先搜索 BFS', 'ICPC', 'NWRRC']
---
# [NWRRC 2021] Kaleidoscopic Route
## 题目描述

There are $n$ cities in Kaleidostan connected with $m$ bidirectional roads. The cities are numbered from $1$ to $n$. Each road has an integer called $\textit{colorfulness}$. 

Keanu wants to travel from city $1$ to city $n$. He wants to take the $\textit{shortest}$ route --- that is, the route with the smallest number of roads. Among all the shortest routes, he wants to take the $\textit{kaleidoscopic}$ one --- that is, the route with the largest possible difference between the maximum and the minimum colorfulnesses of its roads. Help Keanu find such a route.
## 输入格式

The first line contains two integers $n$ and $m$ --- the number of cities and the number of roads ($2 \le n \le 10^5$; $1 \le m \le 2 \cdot 10^5$).

The $i$-th of the following $m$ lines contains three integers $v_i$, $u_i$, and $c_i$ --- the indices of the cities connected by the $i$-th road, and the colorfulness of the $i$-th road ($1 \le v_i, u_i \le n$; $v_i \neq u_i$; $0\le c_i \le 10^9$).

Each pair of cities is connected by at most one road. It is guaranteed that you can travel from any city to any other city using the roads.
## 输出格式

In the first line, print a single integer $k$ --- the number of roads in the required route. 

In the second line, print $k+1$ integers $c_0, c_1, \ldots, c_k$ --- the sequence of cities on the route ($1 \le c_i \le n$; $c_0 = 1$; $c_k = n$).
## 样例

### 样例输入 #1
```
6 8
1 5 2
5 2 5
3 5 4
1 3 10
3 4 6
4 5 7
4 6 8
2 6 1
```
### 样例输出 #1
```
3
1 5 4 6
```
## 提示

![](https://cdn.luogu.com.cn/upload/image_hosting/bun5oktu.png)

In the example test, the required route consists of $3$ roads, and the difference between the maximum and the minimum colorfulnesses of its roads is $8-2=6$.


---

---
title: "[NWRRC 2021] Letters Q and F"
layout: "post"
diff: 普及+/提高
pid: P13639
tag: ['2021', 'ICPC', 'NWRRC']
---
# [NWRRC 2021] Letters Q and F
## 题目描述

Little Lev is learning how to draw letters $\tt{Q}$ and $\tt{F}$. Initially, he has a white grid of size $n \times m$. Then he will draw several letters of one of the following two shapes:

![](https://cdn.luogu.com.cn/upload/image_hosting/nmufwv6b.png)

Lev will not rotate or mirror these two shapes. Every time he draws a new letter, he will choose a position for the letter inside the grid and paint all cells of the shape black. Lev will only draw letters in such a way that before drawing all black cells of the letter are white --- that is, he will never paint a cell twice.

You are given the final coloring of the grid. Count the number of letters $\tt{Q}$ and letters $\tt{F}$ drawn by Lev.
## 输入格式

The first line contains two integers $n$ and $m$ --- the height and the width of the grid ($5 \le n \le 300$; $3 \le m \le 300$).

The next $n$ lines contain $m$ characters each, denoting the final state of the grid. A white cell is denoted by $\tt{.}$, a black cell is denoted by $\tt{\#}$.

It is guaranteed that the grid is a valid result of Lev's drawing.
## 输出格式

Print two integers --- the number of letters $\tt{Q}$ and the number of letters $\tt{F}$ drawn by Lev, respectively.
## 样例

### 样例输入 #1
```
5 3
###
#.#
###
..#
..#
```
### 样例输出 #1
```
1 0
```
### 样例输入 #2
```
5 3
###
#..
##.
#..
#..
```
### 样例输出 #2
```
0 1
```
### 样例输入 #3
```
5 8
###..###
#.#..#..
###..##.
..#..#..
..#..#..
```
### 样例输出 #3
```
1 1
```
### 样例输入 #4
```
8 8
.....###
###..#.#
#.######
###.####
#.###.##
#.#.###.
..#...#.
......#.
```
### 样例输出 #4
```
2 2
```
## 提示

Illustration for the fourth example test:

![](https://cdn.luogu.com.cn/upload/image_hosting/xurousuy.png)


---

---
title: "[CERC 2020] Excavation"
layout: "post"
diff: 普及+/提高
pid: P13654
tag: ['2020', '并查集', 'Special Judge', 'ICPC', 'CERC']
---
# [CERC 2020] Excavation
## 题目描述

The police investigation revealed the gangsters deployed several radioactive stones under the city to poison underground waters. The exact positions of radioactive stones were found, but due to nature of radioactivity, it is a difficult task to remove the stones safely. The government of the city thus decided to use shielded excavators to retrieve stones from the ground.

The city shape is a square grid. City services have several excavator types available – Reepadlo, Qrtech, Bugger, Namakatschenko, and Kopatsch. Each of them has different specifications and movement pattern. Excavators may move either as a Rook, a Queen, a Bishop, a kNight, or as a King in the game of chess, respectively (see images for movement illustration). Due to compatibility issues only a single type of excavators can be deployed.

![](https://cdn.luogu.com.cn/upload/image_hosting/s7uvuutt.png)

There is at most one radioactive stone on each tile of the grid. At the beginning of the excavation, there is one excavator at the position of each radioactive stone and it immediately retrieves the stone from the ground. The next steps of the operation are executed to follow strict radiation handling safety protocol. At each step only one excavator can execute a single move and it can execute it only if the move brings the excavator to a position of another excavator. Excavators of types Reepadlo, Qrtech, Bugger may skip over other excavators during a move over multiple grid tiles, i.e. they do not have to end the move on the position of the first encountered excavator. After excavator $A$ arrives to the position of excavator $B$, $B$ takes its load and $A$ is removed from the operation to be cleaned of radiation.

The operation finishes successfully if in the end there is a single excavator remaining. It is possible the operation can not be successfully finished.

Your task is to determine whether the operation can be finished successfully. If it can, print also the excavators' moves leading to the solution.

## 输入格式

The first line of input contains an integer $N$ ($1 \leq N \leq 100$), determining the size of the city, and a single character determining the excavator type to be deployed (“R” – Reepadlo, “Q” – Qrtech, “B” – Bugger, “N” – Namakatschenko, “K” – Kopatsch).

After that follow $N$ lines describing the initial positions of the excavators in the city. Each line contains $N$ characters, where each character is either the excavator type or “.” for empty field. There is always at least one excavator deployed in the city.

## 输出格式

On the first line print either “YES”, if the operation for the given configuration can be finished successfully, and “NO” otherwise. If the operation can be finished successfully, print also lines describing moves of excavators in the same order they were executed during the excavation, if there were any. $i$-th such line describes a single step and contains four space separated integers $X, Y, W, Z$ ($1 \leq X, Y, W, Z \leq N$), indicating an excavator moves from position $(X, Y)$ to position $(W, Z)$ in step $i$. A position $(X, Y)$ describes the position on row $X$ (numbered from top to bottom) and in column $Y$ (numbered from left to right).
## 样例

### 样例输入 #1
```
2 K
K.
KK
```
### 样例输出 #1
```
YES
2 2 2 1
2 1 1 1
```
### 样例输入 #2
```
3 B
B..
B..
..B
```
### 样例输出 #2
```
NO
```


---

---
title: "[CERC 2020] Tobacco Growing"
layout: "post"
diff: 普及+/提高
pid: P13655
tag: ['2020', 'Special Judge', 'ICPC', 'CERC']
---
# [CERC 2020] Tobacco Growing
## 题目描述

In the city, there is a beautiful park full of blossoming flowers. This park is very popular among citizens and especially families with children are common visitors. The gangsters want to extend their criminal activities to this area, mainly in the tobacco production. They decided to secretly plant tobacco seeds in the park and let it grow right under policemen noses. When the time is right, they plan to harvest as much tobacco as possible in a single operation and smuggle it over borders.

The park consists of flower tiles with coordinates ranging from $-10^6$ to $10^6$ in either direction. A tile on coordinates $(X, Y)$ neighbors with tiles on coordinates $(X + 1, Y)$, $(X - 1, Y)$, $(X, Y + 1)$ and $(X, Y - 1)$ (within coordinates range). On the first day, the gangsters may cut the flowers on any of the tiles. Also only on the first day, if a tile is cut, the gangsters may either plant a tobacco on it, or let the tile contain only grass. In the beginning, the tobacco quantity on a tile with tobacco is $1$ and the tobacco quantity on a tile with grass or on a tile with flowers is $0$. Local tobacco spreads rather aggressively, and so on each consecutive day, the tobacco quantity on park tiles grows as follows:

- Tobacco quantity on tiles with tobacco and grass is increased by the sum of tobacco quantity on the neighboring tiles on the previous day.
- Tobacco quantity on tiles with flowers always remains $0$.

After some days of growing, the harvest operation will take place on a particular day. The gangsters will choose some of the tiles (of any type) to be harvested and obtain the total tobacco quantity on such tiles on that day. Each tile may be harvested at most once and all tobacco quantity on a chosen tile must be harvested. The gangsters can’t harvest everything, because there is a limit on the tobacco quantity that can be somewhat safely smuggled. At the same time, the gangsters do not want to take any unnecessary losses and so they want to harvest exactly the limit amount.

The task is to help the gangsters to plan the operation to the very detail. That is in particular:

1. For the first day, choose flower tiles to be cut, and from these choose tiles to plant tobacco on. At most $2 \cdot 10^5$ flower tiles may be cut, to not raise suspicion among policemen.
2. Choose the number of days to keep tobacco growing. The number of days must be at most 100 to not make this tobacco business blatantly obvious.
3. Choose tiles to be harvested after the given number of days pass. At most $10^4$ tiles may be harvested, as any more would take the gangsters too much time.

Will you manage to help the gangsters? Good luck!

## 输入格式

The input contains a single line with an integer $N$ ($0 \leq N \leq 10^{18}$), the exact tobacco quantity to be harvested.

## 输出格式

On the first line, print the number $C$ ($0 \leq C \leq 2 \cdot 10^5$) of cut flower tiles. For each such tile, output a line in the form of either $X$ $Y$ $1$ for a cut tile with integer coordinates $(X, Y)$ and with a planted tobacco, or $X$ $Y$ $0$ for a cut tile left as a grass area ($-10^6 \leq X, Y \leq 10^6$).

Afterwards print a line with two space-separated numbers $H$ and $D$ ($0 \leq H \leq 10^4$, $0 \leq D \leq 100$), the number of harvested fields and the number of days for tobacco to grow, respectively. Then print $H$ lines with two space-separated integers $X$ and $Y$ ($-10^6 \leq X, Y \leq 10^6$), the coordinates of tiles to be harvested after $D$ days.
## 样例

### 样例输入 #1
```
1
```
### 样例输出 #1
```
1
0 0 1
1 0
0 0
```
### 样例输入 #2
```
13
```
### 样例输出 #2
```
8
1 0 1
0 1 0
1 1 0
3 1 0
1 2 1
2 2 1
1 3 1
3 3 1
3 2
3 3
1 2
1 0
```
## 提示

![](https://cdn.luogu.com.cn/upload/image_hosting/np0x8jis.png)


---

---
title: "[CERC 2020] Storage Problems"
layout: "post"
diff: 普及+/提高
pid: P13659
tag: ['动态规划 DP', '2020', 'ICPC', 'CERC']
---
# [CERC 2020] Storage Problems
## 题目描述

The gangsters did a very successful robbery of the city's most famous auction house. Now they are safely at their hideout, where they store the stolen items. Luckily, you managed to place a listening device into their hideout. You also have a personal file on each ganger, which contains a recording of their voice. You will listen carefully to what happens next with hope it will help you with the investigation of the robbery.

Each gangster stole exactly one item, the $i$-th gangster stole the $i$-th item. Now each gangster is trying to put his item into the common storage, which can hold a total weight of $K$. The storage is a small room and the gangsters store their items one by one.

When a gangster tries to put an item into the storage but it does not fit, that is the total weight of the items in the storage would exceed $K$, he gets angry and throws all the items in the storage out. While doing this, he tells the others that "$j$ items are going to trash!", where $j$ is the number of items in the storage at the point he tried to store his item. At this point a fight ensues and no more storing will happen.

As you have a listening device in the gangsters' storage, you will hear how much items the gangster throws out. Also, using your personal files, you can tell apart each of the gangster's voices.

Therefore, it would help your investigation greatly if you could know in advance, for all possible values of $j$ and $i$, how many different subsets of items could be in the storage at the moment when the $i$-th gangster throws all the $j$ items out. As the number of subsets can be large, output it modulo $167772161$.
## 输入格式

The input consists of two lines. The first line contains two integers $N$ and $K$ ($2 \leq N \leq 400$, $1 \leq K \leq 400$), the number of gangsters and the maximum weight that the storage can hold. The second line contains $N$ integers $w_1, w_2, \cdots, w_N$, such that ($1 \leq w_i \leq K$) for each $1 \leq i \leq N$. Here $w_i$ is the weight of item that the $i$-th gangster stole.

## 输出格式

The output consists of $N$ lines, each line containing exactly $N-1$ integers. The $j$-th value on the $i$-th line contains the number of subsets of items containing exactly $j$ items, such that they fit into the storage but the $i$-th gangster's item can not be added. Each number is modulo $167772161$.
## 样例

### 样例输入 #1
```
3 3
2 2 1
```
### 样例输出 #1
```
1 1
1 1
0 0
```
### 样例输入 #2
```
5 5
1 2 3 4 5
```
### 样例输出 #2
```
1 1 0 0
2 2 0 0
2 2 0 0
3 3 0 0
4 4 0 0
```


---

---
title: "[GCPC 2023] Balloon Darts"
layout: "post"
diff: 普及+/提高
pid: P13667
tag: ['2023', '鸽笼原理', '随机化', '构造', 'ICPC']
---
# [GCPC 2023] Balloon Darts
## 题目描述

As you may know, you get a colourful balloon for each problem you solve in an ICPC contest.
You were quite successful in your last contest
and now you own a remarkable collection of $n$ balloons.
The obvious thing to do with these balloons is to pop them all using darts.
However, you only have three darts.

![](https://cdn.luogu.com.cn/upload/image_hosting/3lkiybcb.png)

:::align{center}
Popping balloons as an amusement park attraction. Photo by blende12, [Pixabay](https://pixabay.com/photos/balloon-leisure-time-4525887/)
:::

The balloons are modelled as points in the plane with fixed locations.
For each dart you choose from where and in which direction to throw it.
The dart travels in a straight line, popping all balloons in its way.

As you practised a lot during the last years,
you can throw a dart precisely in any direction and it will fly infinitely far.
Thus, if anyone can pop all the balloons, it is you. 
However, before the fun begins, you first need to determine
if you can pop all balloons using at most three darts.
## 输入格式

The input consists of:
- One line containing an integer $n$ ($1 \leq n \leq 10^4$), the number of balloons.
- $n$ lines, each containing two integers $x$ and $y$ ($|x|, |y| \leq 10^9$), the coordinates of a balloon.

It is guaranteed that no two balloons are at the same location.
## 输出格式

Output "$\texttt{possible}$" if three darts are sufficient to pop all balloons and "$\texttt{impossible}$" otherwise.
## 样例

### 样例输入 #1
```
6
0 0
1 1
2 4
3 9
4 16
5 25
```
### 样例输出 #1
```
possible
```
### 样例输入 #2
```
7
0 0
1 1
2 4
3 9
4 16
5 25
6 36
```
### 样例输出 #2
```
impossible
```
### 样例输入 #3
```
7
-1 -1
0 0
1 1
2 4
3 9
4 16
5 25
```
### 样例输出 #3
```
possible
```


---

---
title: "[NWERC 2023] Fixing Fractions"
layout: "post"
diff: 普及+/提高
pid: P13705
tag: ['2023', 'Special Judge', 'ICPC']
---
# [NWERC 2023] Fixing Fractions
## 题目描述

Maths is hard.$^{\text{[citation needed]}}$
But it could be easier!
And the internet™ has found some excellent ways to make it easier.

![](https://cdn.luogu.com.cn/upload/image_hosting/zaysoilw.png)

:::align{center}
Source: The Internet™.
:::

Take a look at the following true equations:

$$
\begin{aligned}
\displaystyle\log(1)+\log(2)+\log(3)&=\displaystyle\log(1+2+3)\\
\displaystyle\frac{1\cancel{63}}{\cancel{3}2\cancel{6}}&=\displaystyle\frac{1}{2}~.

\end{aligned}
$$

Following the patterns, we come to the conclusion that the following equation should also be true:

$$
\displaystyle\frac{12\cancel{3}}{2\cancel{3}4}=\frac{1}{2}~.
$$

However, this is actually wrong in boring old standard maths.
Therefore, we define a new kind of funky maths where it is allowed to cancel out digits on the left side of the equality sign.
This surely will make everyone's life easier.
Except yours, since you have to evaluate if two given fractions are equal in our new funky maths.



## 输入格式

The input consists of:
- One line with four integers $a$, $b$, $c$, and $d$ ($1\leq a,b,c,d<10^{18}$), describing the two fractions $\frac{a}{b}$ and $\frac{c}{d}$.

## 输出格式

If there exist integers $a'$ and $b'$ obtained from $a$ and $b$ by cancelling
out the same digits and with $\frac{a'}{b'} = \frac{c}{d}$ in standard mathematics, output
"$\texttt{possible}$", followed by $a'$ and $b'$.
Otherwise, output "$\texttt{impossible}$".

If there are multiple valid solutions, you may output any one of them.

Note that neither $a'$ nor $b'$ is allowed to contain leading zeroes after
cancelling digits.
## 样例

### 样例输入 #1
```
163 326 1 2
```
### 样例输出 #1
```
possible
1 2
```
### 样例输入 #2
```
871 1261 13 39
```
### 样例输出 #2
```
possible
87 261
```
### 样例输入 #3
```
123 267 12339 23679
```
### 样例输出 #3
```
impossible
```


---

---
title: "[NWERC 2023] Higher Arithmetic"
layout: "post"
diff: 普及+/提高
pid: P13707
tag: ['2023', 'Special Judge', 'ICPC']
---
# [NWERC 2023] Higher Arithmetic
## 题目描述

Captchas are getting more and more elaborate.
It started with doing simple calculations like $7 + 2$, and now, it has evolved into having to distinguish chihuahuas from double chocolate chip muffins.

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/uvk9ao3u.png)
:::

To combat the rise of smarter bots, the Internet Captcha Production Company (ICPC) has outdone itself this time:
given a distorted image containing many integers, find the maximum value that can be expressed using each of the given integers exactly once, using addition, multiplication, and arbitrary parentheses.

After unsuccessfully trying to solve such a captcha for an hour straight, Katrijn is terribly frustrated.
She decides to write a program that outputs a valid arithmetic expression with maximal value.
## 输入格式

The input consists of:
- One line with an integer $n$ ($1 \le n \le 10^5$), the number of integers in the captcha.
- One line with $n$ integers $a$ ($1 \le a \le 10^6$), the integers in the captcha.
## 输出格式

Output a valid arithmetic expression with maximal value, where each integer from the input list is used exactly once.
The usual order of operations applies.
The output expression may use at most $10^6$ characters and must not contain any spaces.
Such an expression exists for any possible input.

If there are multiple valid solutions, you may output any one of them.
## 样例

### 样例输入 #1
```
4
1 2 3 4
```
### 样例输出 #1
```
3*((1+2)*4)
```
### 样例输入 #2
```
3
13 37 1
```
### 样例输出 #2
```
(1+13)*37
```
### 样例输入 #3
```
4
1 1 1 1
```
### 样例输出 #3
```
((1+1)*(1+1))
```


---

---
title: "[GCPC 2024] Copycat Catcher"
layout: "post"
diff: 普及+/提高
pid: P13718
tag: ['2024', 'ICPC', '哈希表']
---
# [GCPC 2024] Copycat Catcher
## 题目描述

Your university recently established the Graduate Code Plagiarism Control (GCPC) initiative to get hold of the ever-increasing load on the graders for the computer science assignments.
Currently, the graders need to check the code of assignments manually for plagiarism.
The GCPC aims to simplify this part of the graders' jobs by performing the plagiarism checks automatically.

![](https://cdn.luogu.com.cn/upload/image_hosting/dmrh1qay.png)

:::align{center}
A Plagiarism Keyboard
:::

Code consists of tokens separated by spaces. Tokens are strings of alphabetical letters, numerals, and brackets. If a token consists of only a single alphabetical letter (upper or lowercase), it is a variable in the code.

The GCPC wants the plagiarism checker to compare query pieces of code to a reference code.
Specifically, it should check whether each query could have been obtained by selecting a contiguous
string of tokens from the reference and consistently renaming variables.

Variables are consistently renamed if no two occurrences of the same variable are renamed to different variables,
and if no two different variables are renamed to the same variable.

The GCPC has asked you to develop the plagiarism checker.
## 输入格式

The input consists of:
- A description of the reference, consisting of:
  - One line containing an integer $n$ ($1\leq n \leq 2\,000$), the number of tokens in the reference.
  - One line containing $n$ tokens, each consisting only of the characters '$\texttt{a}$'-'$\texttt{z}$', '$\texttt{A}$'-'$\texttt{Z}$', '$\texttt{0}$'-'$\texttt{9}$', '$\texttt{(}$' and '$\texttt{)}$'.
- An integer $q$ ($1 \leq q \leq 2\,000$), the number of queries.
- $2\cdot q$ lines, each two lines in the same format as the reference.

It is guaranteed that each query as well as the reference consist of at most $2\,000$ characters (excluding spaces). Tokens are separated by single spaces.
## 输出格式

For each query, output "$\texttt{yes}$" if the query could have been obtained from the reference, and "$\texttt{no}$" otherwise.
## 样例

### 样例输入 #1
```
9
for i in range(10) do print i j end
4
3
print j i
2
do print
6
k in range(10) do print k
6
k in range(10) do print j
```
### 样例输出 #1
```
yes
yes
yes
no

```
### 样例输入 #2
```
5
i is i times j
7
5
i is i times j
5
a is a times b
5
j is j times c
5
a is i times j
5
j is i times j
5
0 is 0 times j
5
i is i times i

```
### 样例输出 #2
```
yes
yes
yes
no
no
no
no

```
### 样例输入 #3
```
5
A 1 ( ) b
4
2
b 2
2
b 1
3
1 ) (
5
a 1 ( ) F

```
### 样例输出 #3
```
no
yes
no
yes

```


---

---
title: "[NWERC 2024] Mouse Trap"
layout: "post"
diff: 普及+/提高
pid: P13751
tag: ['计算几何', '2024', 'Special Judge', '前缀和', '凸包', 'ICPC']
---
# [NWERC 2024] Mouse Trap
## 题目描述

Medea the cat is a real troublemaker.
Even though she is loving and caring with humans, sometimes she likes to crash on mouse parties in the field nearby her house, uninvited, just for the fun of it!


:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/zxffm682.png)

Medea with a mouse.

:::

A mouse party is a bunch of mice standing on the vertices of a convex polygon in the two-dimensional plane.
When Medea crashes a mouse party, she jumps, out of nowhere, to some point inside the party's polygon.
All the mice and Medea can be considered as points in the two-dimensional plane, meaning that they have no shape or dimensions.

Medea is still careful, however.
She considers how the mice might encircle her, so that she runs away before they get a chance to do so.
Medea defines an \textit{encirclement} as a subset of exactly three mice such that she lies strictly inside the triangle constructed with the mice as vertices.
An example can be seen in Figure M.1.

:::align{center}

![](https://cdn.luogu.com.cn/upload/image_hosting/4rm403dp.png)

Figure M.1: Illustration of Sample Input 2, showing one of the three encirclements in the case where Medea jumps to $(1.4,1.4)$.

:::


One day, Medea decided to crash on a party of mice.
She does not jump accurately, so she does not know exactly which point inside the mouse party she is going to jump to -- all she knows is that she will jump to a uniformly random point with real coordinates inside the mouse party.

Medea wants to know the expected number of distinct encirclements after she lands inside the party.
This turned out to be too difficult to calculate, even for Medea's 200 IQ points, so she asked for your help!

## 输入格式

The input consists of:
- One line with an integer $n$ ($3 \leq n \leq 2\cdot 10^5$), the number of mice.
- $n$ lines, each with two integers $x$ and $y$ ($|x|, |y| \leq 10^7$), the coordinates of a mouse.

The coordinates of the mice are given in counterclockwise order and form a strictly convex polygon with non-zero area. A strictly convex polygon is a convex polygon such that no three consecutive vertices are on a straight line.
## 输出格式

Output the expected number of encirclements after Medea lands inside the polygon.

Your answer should have an absolute or relative error of at most $10^{-4}$.
## 样例

### 样例输入 #1
```
4
0 0
1 0
1 1
0 1
```
### 样例输出 #1
```
2.0
```
### 样例输入 #2
```
5
0 0
1 0
2 1
1 2
0 2
```
### 样例输出 #2
```
3.66666667
```
### 样例输入 #3
```
3
-3141592 -2718281
-3141593 -2718281
-3141592 -2718282
```
### 样例输出 #3
```
1.0
```


---

---
title: "[CERC 2021] Radar"
layout: "post"
diff: 普及+/提高
pid: P13770
tag: ['计算几何', '二分', '2021', 'Special Judge', 'ICPC', 'CERC']
---
# [CERC 2021] Radar
## 题目描述

We are using a special radar to scan an area. The radar accepts a list of distances, e.g. 2, 4, 1, and a list of angles, e.g. $100^\circ$, $270^\circ$, $180^\circ$, $10^\circ$, $300^\circ$, and scans the points across all the given distances and angles. How close to some other points of interest will we be able to scan?
## 输入格式

The first line of the input gives three space-separated integers: $R$, $F$, $N$, representing the number of radii, the number of angles, and the number of points of interest, respectively. Then $R$ lines follow, $i$-th of which contains an integer $r_i$, representing the distance from the radar that will be scanned. Then, $F$ lines follow, each containing two space-separated integers $(f_x)_i$, $(f_y)_i$, that represent Cartesian coordinates of a point, defining the $i$-th angle. Then, $N$ lines follow, each containing two space-separated integers $x_i$, $y_i$, that represent the Cartesian coordinates of the $i$-th point.

The angle, defined by the point $(f_x)_i$, $(f_y)_i$ is the angle from the $x$-axis to the ray from the origin through $(f_x)_i$, $(f_y)_i$.
## 输出格式

Output $N$ lines, $i$-th of which should contain the distance from the point $(x_i, y_i)$ to the closest scanned point. The result will be considered correct if it is within the $10^{-6}$ of absolute or relative precision.
## 样例

### 样例输入 #1
```
3 7 5
2
4
7
8 4
2 8
-1 5
-7 2
-4 -4
1 -8
6 -3
3 -1
8 1
2 6
-5 2
-1 -1
```
### 样例输出 #1
```
0.977772290466
2.750120773895
0.846777708005
1.464071052924
0.585786437627
```
## 提示

### Comment

Illustration of sample case:

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/6rmdx4uq.png)
:::

### Input limits

* $1 \leq R, F, N \leq 10^5$
* $|x_i|, |y_i|, |(f_x)_i|, |(f_y)_i|, r_i < 10^6$
* $(f_x)_i^2 + (f_y)_i^2, r_i > 0$
* All $r_i$ are pairwise distinct.
* Rays, defined by $(f_x)_i, (f_y)_i$, are pairwise distinct.


---

---
title: "[CERC 2021] Single-track railway"
layout: "post"
diff: 普及+/提高
pid: P13773
tag: ['线段树', '二分', '树状数组', '2021', 'ICPC', 'CERC']
---
# [CERC 2021] Single-track railway
## 题目描述

Trains running on a single-track railway can only meet at the stations. Suppose that a pair of trains simultaneously leave in the opposite directions, one from the initial and the other from the final station, i.e. the initial station in the opposite direction. It is likely that one of the trains will have to wait for the other one at one of the stations along the railway. To minimize the delays, the trains meet at the station such that the waiting time is minimized.

We know the travel time between each two adjacent stations, equal in both directions. Unfortunately, the travel times constantly change because of the works along the railway. You are given the initial travel times and an updated travel time for the affected section after each change. Write a program that computes the shortest possible waiting time for a pair of trains leaving from the opposite ends of the railway after each of the changes.
## 输入格式

The first line specifies the number of stations, $n$. In the second line, $n-1$ numbers are given, corresponding to the initial travel times between the adjacent stations (the $i$-th number is the travel time between stations $i$ and $i+1$). The third line specifies the number of changes, $k$. This is followed by $k$ lines, each containing two numbers: the first one, $j \in [1, n-1]$, specifies the station, and the second gives the updated travel time between stations $j$ and $j+1$. Keep in mind that the first station is numbered 1 rather than 0.
## 输出格式

Output $n+1$ lines, where the $i$-th line will contain the shortest possible waiting time after $i-1$ changes (the first one should correspond to the situation before any changes).
## 样例

### 样例输入 #1
```
6
20 70 40 10 50
2
4 80
2 30
```
### 样例输出 #1
```
10
0
40
```
## 提示

### Comment

At the beginning, the trains leaving in the opposite directions should meet at station 3. The first train will reach that station in 90 minutes, and the second will arrive there in 100 minutes; the waiting time will thus be 10 minutes. Following the first change, the optimal meeting point becomes station 4. Both trains will take 130 minutes to get there, so neither will have to wait. After the second change, they will also meet at station 4. This time, however, the train that arrives first will have to wait for 40 minutes.

### Input limits

* $2 \leq n \leq 200\,000$
* $0 \leq k \leq 200\,000$
* All travel times (both the initial and the updated ones) are integers from the interval $[1, 10^6]$.


---

---
title: "[SWERC 2023] Olympic goodies"
layout: "post"
diff: 普及+/提高
pid: P13801
tag: ['2023', 'ICPC']
---
# [SWERC 2023] Olympic goodies
## 题目描述

:::align{center}

![](https://espresso.codeforces.com/5b58e27029703e37247b24c6c8ebbc352e62449b.png)

:::


Freshly arrived on the market, retailer YAOGS (Yet Another Olympic Goodies Seller) sells very expensive Olympics-themed items. To make themselves better known to the public, they half-heartedly decide to give away some of these items via a contest: the first person to answer correctly the question "How many circles are there in the Olympic Games logo?" can thus gain up to $P$ very expensive but equally valued items.


To spice things up (and spend less), YAOGS however opts for an additional challenge, as follows. The $P$ available items are positioned along some, but possibly not all of the alleys of YAOGS's headquarters; each alley can thus contain 0, 1, or more items. For reasons unknown, these alleys form a connected, undirected, acyclic graph (i.e., a tree) with $N$ nodes, numbered from 0 to $N-1$.


The winner knows $N$ but has no idea about either the tree structure or the items' placement. Once goodies are placed, her task is to choose a start node $m$ and an end node $n$. She can then collect all the items on the (unique) path from $m$ to $n$ in the tree.


YAOGS decides to cleverly place the goodies so that they minimise the maximum number of items that can possibly be collected. Assuming they properly carry out this task, what is the maximum number of items the winner can collect?
## 输入格式

Each line contains two space-separated integers. The fist line contains the numbers $N$ and $P$. Then follow $N-1$ lines; the $k\text{th}$ such line contains two integers $a_k$ and $b_k$, meaning that there is an edge between the nodes $a_k$ and $b_k$ of the tree.

**Limits**
	
- $1 \leq M \leq 100000$;
- $1 \leq P \leq 100000$;
- $0 \leq a_k \leq N-1$ and $0 \leq b_k \leq N-1$ for all $k \leq N-1$;
- the set of edges in the input file describes a valid tree structure.
## 输出格式

The output should contain a single line, consisting of a single integer: the maximum number of items
that can be collected by the winner.
## 样例

### 样例输入 #1
```
5 5
0 1
0 2
2 3
2 4
```
### 样例输出 #1
```
4
```
## 提示

**Sample Explanation**

For the tree in the sample input, depicted below, an optimal item placement by YAOGS guarantees
that the winner cannot collect more than four items.


The figures below show two possible item placements to achieve this optimality. In the first one, the
four items may be collected by choosing, for instance, nodes $1$ and $3$. In the second one, the four items
may be collected by choosing, for instance, nodes $0$ and $4$.

![](https://espresso.codeforces.com/8ebb2ecdb22b673ba1f401eeeee819480e846618.png)




---

---
title: "[CERC 2022] Constellations"
layout: "post"
diff: 普及+/提高
pid: P13807
tag: ['2022', 'ICPC', 'CERC']
---
# [CERC 2022] Constellations
## 题目描述

Astrologists took a hard scientific look at their zodiac horoscope predictions and realised that their methodology doesn't provide future insight better than chance. Instead of looking inwards they blame the stars and historical construction of constellations for their inability to predict the future. They're testing out a new way of constructing constellations that will renew their powers of future-sight.

They need your help to implement their iterative constellation creation system. Initially every star represents its own constellation. In every step you should merge two constellations into one, by picking the constellations that are closest to each other. The distance between two constellations $A$ and $B$ is defined as the average squared Euclidean distance of pairs of stars from each constellation:

$$d(A, B) = \frac{1}{|A||B|} \sum_{a \in A} \sum_{b \in B} ||a - b||^2$$

If multiple pairs have the same distance you should merge older constellations first. When comparing two pairs of constellations that could be merged, first compare the distances between constellations. If both pairs are at exactly the same distance, compare them by the age of the older constellation in a pair. If there is still a tie, compare them by the age of the newer constellation in a pair. A constellation's age is defined by the time when it was formed with the last merge, or in case of single-star constellations by the age of the star. The stars in the input are listed from oldest to youngest.
## 输入格式

The first line contains $N$, the number of stars. The next $N$ lines contain coordinates of stars with two space-separated integers $X_i$ and $Y_i$.
## 输出格式

After every step of the described constellation creation system, print out the size of the newly created constellation. You should output $N - 1$ lines.
## 样例

### 样例输入 #1
```
3
0 0
-1 0
10 10
```
### 样例输出 #1
```
2
3
```
### 样例输入 #2
```
4
0 0
0 -1
0 1
0 2
```
### 样例输出 #2
```
2
2
4
```
### 样例输入 #3
```
4
0 0
0 1
0 -1
0 2
```
### 样例输出 #3
```
2
3
4
```
## 提示

### Input limits

* $2 \leq N \leq 2000$
* $-1000 \leq X_i, Y_i \leq 1000$ for all $1 \leq i \leq N$
* All pairs $X_i, Y_i$ are unique since it’s physically impossible for two stars to lie on the same point.


---

---
title: "[CERC 2022] Differences"
layout: "post"
diff: 普及+/提高
pid: P13810
tag: ['2022', '随机化', 'ICPC', 'CERC']
---
# [CERC 2022] Differences
## 题目描述

We have a list of $N$ strings $S_i$. All strings have length $M$ and consist only of characters A, B, C and D. Let us define the distance between two strings $X$ and $Y$ as the number of indices $j$, where the strings have different characters ($X_j \neq Y_j$). We know that the list of strings $S_i$ contains precisely one special string that has distance $K$ to all other strings. Note that there might be other pairs of strings with a distance of $K$. We are experiencing problems finding this special string, so please write a program to help us out.
## 输入格式

The first line contains space-separated integers $N$, $M$ and $K$. Strings $S_i$ are given in the following $N$ lines.

## 输出格式

Output the index $i$ of the special string. Strings are numbered from 1 to $N$ as given in the input.
## 样例

### 样例输入 #1
```
5 10 2
DCDDDCCADA
ACADDCCADA
DBADDCCBDC
DBADDCCADA
ABADDCCADC
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
4 6 5
AABAAA
BAABBB
ABAAAA
ABBAAB
```
### 样例输出 #2
```
2
```
## 提示

### Input limits

* $2 \leq N, M \leq 10^5$
* $1 \leq K \leq M$
* $NM \leq 2 \cdot 10^7$


---

---
title: "[CERC 2022] Greedy Drawers"
layout: "post"
diff: 普及+/提高
pid: P13811
tag: ['2022', 'Special Judge', 'ICPC', 'CERC']
---
# [CERC 2022] Greedy Drawers
## 题目描述

Janko has $N$ rectangular notebooks on the table. The $i$-th notebook has sides of length $A_i$ and $B_i$. Next to the table is a chest of drawers that consists of $N$ drawers, which have a rectangular shape but can be of different sizes. The $j$-th drawer has width $X_j$ and depth $Y_j$. Janko wants to store each notebook in its own drawer. He can rotate the notebooks but will place them in a drawer so that the sides of the notebook are aligned with the sides of the drawer. A notebook fits into the drawer if the length of each side does not exceed the length of the corresponding aligned side of the drawer.

Janko has decided on a procedure to assign notebooks to drawers. For every notebook he will determine the number of drawers that he can fit the notebook into. Similarly, he will determine for every drawer the number of notebooks that would fit into this drawer. Then he will select the object (notebook or drawer) with the smallest number of options. If this object has no options, the procedure stops with a failure. If there are several objects with the same smallest number of options, he will select one uniformly at random. He will assign one of the options to the selected object uniformly at random. If the selected object was a notebook, he will assign it to a random drawer that can fit the notebook. If the selected object was a drawer, he will assign it to a random notebook that fits into the drawer. He will remove the assigned pair (notebook and drawer) and repeat the procedure until all notebooks are assigned to drawers.

Metka has overheard Janko's idea about placing notebooks into drawers. She is convinced that his procedure is flawed and might not succeed. Help her by writing a program that will read the number of notebooks and drawers $N$ and output a list of notebooks and a list of drawers where Janko's random greedy method doesn't necessarily find an assignment of all notebooks to drawers although such an assignment exists.

## 输入格式

The first and only line contains integer the number of notebooks and drawers $N$.
## 输出格式

First, output $N$ lines with space-separated notebook side lengths $A_i$ and $B_i$. Next, output an empty line followed by another $N$ lines with space-separated drawer dimensions $X_j$ and $Y_j$. All dimensions should be integers between 1 and 1000, inclusive.

## 样例

### 样例输入 #1
```
1
```
### 样例输出 #1
```
4 3

2 6
```
### 样例输入 #2
```
3
```
### 样例输出 #2
```
4 4
3 5
6 1

2 7
5 4
5 5
```
## 提示

### Comment

Note that the provided sample inputs and outputs are incorrect. The inputs don't respect the constraint $150 \leq N$.

In the first sample, there is a single notebook which doesn't fit into the single drawer, therefore a valid assignment doesn't exist.

In the second sample, Janko's method would successfully assign all notebooks to drawers. First, it would select the last notebook ($6 \times 1$) or the first drawer ($2 \times 7$) and assign it to the other one because both have a single option. Now both remaining notebooks fit into both remaining drawers, therefore any assignment will do.

### Evaluation

To evaluate the output of your program, we will run Janko's random greedy method on your data (notebook and drawer dimensions). Note that there must exist an assignment of all notebooks to drawers, otherwise your output will be considered as incorrect. Your solution will be evaluated on 20 test cases and Janko's method has to fail on all of them. For every test case we will run Janko's method once with a fixed random seed.

### Input limits

- $150 \leq N \leq 250$


---

---
title: "[CERC 2022] Skills in Pills"
layout: "post"
diff: 普及+/提高
pid: P13815
tag: ['数学', '2022', 'ICPC', 'CERC']
---
# [CERC 2022] Skills in Pills
## 题目描述

An unnamed protagonist of this task received amazing e-mail offers for wondrous pills that will enhance their cognitive and all other sorts of abilities. After carefully analysing all offers and side effects, he has decided that he will order 2 types of pills, let's call them $A$ and $B$. He needs to take pill $A$ every $k$ days and pill $B$ every $j$ days. He will follow this meticulously over the next $n$ days.

More formally, in the next $n$ days, there should be no $k$ consecutive days where he does not take pill $A$ and no $j$ consecutive days where pill $B$ is not taken. However, there is a twist – the two pills are highly potent and must not be taken on the same day, lest horrible side effects should happen. Given this constraint, what is the smallest number of pills that he needs to take to meet these requirements?
## 输入格式

You are given three space-separated integers, $k$, $j$, and $n$.
## 输出格式

Print one number – the minimum number of pills that need to be taken. It is easy to prove that a solution always exists for the given constraints.
## 样例

### 样例输入 #1
```
2 3 8
```
### 样例输出 #1
```
6
```
### 样例输入 #2
```
2 3 11
```
### 样例输出 #2
```
9
```
### 样例输入 #3
```
3 7 100
```
### 样例输出 #3
```
48
```
## 提示

### Comment

In the first case, we can take pill $A$ on days $2$, $4$, $5$, and $7$, and pill $B$ on days $3$ and $6$, giving the sequence $\text{.ABAABA}$. In the second case, the best approach is to take pills in sequence $\text{.ABAABAABA}$, which requires taking $9$ pills.

### Input limits

- $2 \leq n \leq 10^6$
- $2 \leq k, j \leq n$


---

---
title: "[CERC 2022] The Game"
layout: "post"
diff: 普及+/提高
pid: P13816
tag: ['模拟', '2022', 'ICPC', 'CERC']
---
# [CERC 2022] The Game
## 题目描述

Vladimir is the loneliest child in the neighbourhood. No other kid likes to play with him. His parents decided to cheer him up so they bought him a card game called _The Game_. This card game is for up to 5 players, but it can also be played in the _solo_ (i.e. single-player) mode.

The package contains 98 _regular_ playing cards that are labeled by integers $2, 3, \ldots, 99$. In addition to these, there are 4 special _direction_ cards. Two of them are labeled with the number $1$ (followed by an up arrow) and the other two are labeled with $100$ (followed by a down arrow).

In the initial phase of the game, the pile of regular cards is shuffled and placed face down on the table – this will be the _draw pile_. The four direction cards are placed in a column; the two cards labeled $1$ have to be at the top. There should also be enough space on the right-hand side of each direction card – this is where regular cards will be laid during the play. The card labeled $1$ initiates an _ascending row_, while a card labeled $100$ initiates a _descending row_. In the solo mode, the player draws the top 8 cards from the draw pile, one by one, and puts them in his hand.

After the initial phase the game starts. On each turn the player has to play two cards from his hand according to the following rules:

- A card may be placed at the end of an ascending row if it is larger than the last (i.e. right-most) card in the row.
- A card may be placed at the end of a descending row if it is smaller than the last card in the row.
- A card with a smaller label may be placed at the end of an ascending row, or a card with a larger label may be placed at the end of a descending row, if the absolute difference between its value and the value of the last card in the row is exactly $10$. This move is called the _backwards trick_. Note that because of this extra rule, the values of the cards in an ascending row are not necessarily ascending (and similarly, the values of the cards in a descending row are not necessarily descending).

After playing two cards from the hand, the player should draw two new cards from the draw pile, one by one. This concludes his turn. If the draw pile is empty, he continues playing in the same way without drawing new cards. The game ends when the player has no cards left in his hand (in that case the player _beats the game_) or if he cannot play any of the remaining cards in his hand (in that case the player has _lost the game_).

**Example:** Suppose that the player's initial hand (i.e. the first 8 cards which he has drawn) is:

69, 17, 59, 32, 31, 77, 87, 89

He may decide to play the card 89 (putting it in the first descending row) and the card 17 (putting it in the second ascending row). The state of all four rows after the move is:

```
1 -> 17  
1 ->  
100 <- 89  
100 <-
``` 

Then he has to pick up two more cards from the draw pile – suppose these two cards are $84$ and $3$ – and his hand becomes:

$69, 59, 32, 31, 77, 87, 84, 3$

In the second turn he might want to play the card $3$ (in the first ascending row) and card $87$ (in the first descending row, after card $89$). The state of all four rows after the move:

```
1 -> 3  
1 -> 17
100 <- 89, 87 
100 <-
```

Vladimir played the game for a few times and he could not always beat the game. Since he hates losing the game, you should write a computer program that will inspect the draw pile and predict the outcome of the game. This will help Vladimir to decide whether he wants to play it or not.

You should also know that Vladimir is a very logical and predictable person. He plays according to the following rules.

- When he draws a card, he places it in his hand on the far-right side.
- He will always play a card from his hand according to his list of priorities:

  1. If one or more cards allow him to do the backward trick, he will use the leftmost such card. If that card can be used for the backward trick in different rows, he will use the top-most amongst these rows.
  2. Otherwise, he plays a card in the regular way. He will select the card to play, and the row in which to put it, in such a way as to minimize the absolute value of the difference between the value of the card that is being played and the last card in the row. If several cards attain the minimum, he will use the left-most amongst these cards. Finally, if there are several choices of where to play this card, he will choose the top-most row.

Your program should find the final state of the game.

## 输入格式

The first (and only) line of the input contains 98 space-separated integers, i.e. some permutation of the set $\{2, 3, \ldots, 99\}$ that represents the initial draw pile. The cards are listed in order from top to bottom of the draw pile.
## 输出格式

The output contains six lines. The first four lines describe the four rows of cards on the table. The fifth line lists the cards that remained in the player's hand (if any) while the last line lists the cards that remained in the draw pile (if any). Print an empty line in case of an empty list. Cards in the four rows and in the hand should be ordered from left to right, while the cards in the last line, which represents the remainder of the draw pile, should be ordered from top to bottom as in the input data. See also the sample outputs.
## 样例

### 样例输入 #1
```
96 69 40 94 35 7 53 88 10 89 47 37 16 61 24 46 90 6 33 25 63 73 26 81 2 45 77 75 48 57 66 34 59 92 44 11 31 18 9 52 91 50 8 98 5 64 86 62 83 4 19 3 27 97 28 36 23 76 58 30 38 12 39 78 41 56 80 67 70 99 13 42 17 49 84 22 32 29 54 71 51 74 79 95 72 15 87 21 65 68 60 85 55 43 93 20 82 14
```
### 样例输出 #1
```
1 7 10 16 6 9 11 18 31 62 64 83 86 91 92 97 98 99
1 2 5 8 19 23 27 28 30 36 38 39 41 56 58 67 70 76 78 80 84 74 79 95
100 96 94 89 88 69 61 53 47 46 40 37 35 33 26 25 24 34 44 42 22 32 29 17 13 12 4 3
100 90 81 77 75 73 66 63 59 57 52 50 48 45 21 15
49 54 71 51 72 87 65 68
60 85 55 43 93 20 82 14
```
### 样例输入 #2
```
87 31 58 56 82 93 9 68 65 41 26 64 3 11 5 84 24 46 16 30 14 85 52 12 91 75 96 17 47 37 76 69 78 49 25 28 48 81 95 63 34 43 27 74 80 62 53 83 40 71 72 35 23 21 51 66 55 61 67 32 38 29 60 39 4 18 20 77 7 94 59 42 79 10 92 97 57 2 86 33 89 90 88 19 22 99 45 44 73 70 50 6 15 98 54 13 36 8
```
### 样例输出 #2
```
1 9 11 16 24 14 17 26 28 30 31 34 62 74 78 80 81 71 72 83 95 96 97 99
1 3 5 12 25 27 29 38 39 42 59 60 66 67 57 77 79 86 89 90 92 94 98 88
100 93 87 82 68 65 64 58 56 46 41 37 47 43 53 51 61 55 45 44 33 22 20 19 15 13 10 8 6
100 91 85 84 76 75 69 63 52 49 48 40 35 32 23 21 18 7 4 2
73 70 50 54 36
```


---

---
title: "[CERC 2023] Going to the Moon"
layout: "post"
diff: 普及+/提高
pid: P13851
tag: ['数学', '2023', '三分', 'Special Judge', 'ICPC', 'CERC']
---
# [CERC 2023] Going to the Moon
## 题目描述

Alice and Bob are playing a game in the sand outside their mansion. A circle representing the Moon is drawn somewhere, and they each also pick a place to stand (inside, on the edge, or outside the Moon). The goal of the game is that one of the players runs to the other as fast as possible, while also touching the Moon during the run.

Given the positions of the Moon, Alice, and Bob, find the length of the shortest path that starts at one of the players, touches (or crosses) the edge or the interior of the Moon, and ends at the position of the other player.

## 输入格式

The first line contains an integer $T$, the number of test cases. It’s followed by $T$ lines, each containing 7 space-separated integers $x_A$, $y_A$, $x_B$, $y_B$, $x_C$, $y_C$, $r$, representing coordinates of Alice, $A = (x_A, y_A)$, Bob, $B = (x_B, y_B)$, the center of the circle, $C = (x_C, y_C)$, and its radius $r$.

## 输出格式

For each test case output a single decimal number representing the length of the shortest path from $A$ to $B$ that also touches at least one point inside or on the edge of a circle with the center $C$ and radius $r$. The solution will be considered correct if the relative or absolute error compared to the official solution is within $10^{-6}$.

## 样例

### 样例输入 #1
```
2
0 0 2 0 -1 2 1
5 0 3 0 2 0 2
```
### 样例输出 #1
```
3.9451754612261913
2
```
## 提示

### Comment

The solution for the first test case is shown in the picture.

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/rnv9of0l.png)
:::align

### Input limits

- $1 \leq T \leq 10^3$
- $-10^3 \leq x_A, y_A, x_B, y_B, x_C, y_C \leq 10^3$
- $0 \leq r \leq 10^3$


---

---
title: "[SEERC 2019] Projection"
layout: "post"
diff: 普及+/提高
pid: P5802
tag: ['2019', 'ICPC']
---
# [SEERC 2019] Projection
## 题目描述

![TensorFlow](https://cdn.luogu.com.cn/upload/image_hosting/gdl3vztm.png)

你是一个 TensorFlow 的死忠粉，因此，你想要从两个投影图形来还原出 TensorFlow 的图标。

假定你有一个 3D 空间，尺寸为 $n \times m \times h$，以及两个投影图形（一个 $n \times m$ 的矩阵和一个 $n \times h$ 的矩阵，矩阵里的元素都为 $0$ 或 $1$）。你需要计算出一些 $1 \times 1 \times 1$ 的小正方体的集合，使得这些正方体放入 3D 空间后构成的立体的正投影（光照立体正面在立体后侧形成的投影）和右投影（光照立体左面在立体右侧形成的投影）与题目给定的投影图形一致。如果无解，输出 $-1$。如果有解，你需要计算出两个满足条件的集合，一个包含的小正方体数量最少，另一个最多。假定正方体的摆放不受重力影响（即小正方体在 3D 空间中可以随意放置，悬空也不需要支撑）。规定矩阵中的 $1$ 代表有阴影遮住，$0$ 代表无阴影遮住。

如果有多解，你需要输出字典序最小的解。一个解 $a$ 字典序比解 $b$ 小，当且仅当对于两个解中第一对不相同的数字，$a$ 中的数字小于 $b$ 中的。

例如，解 $[(0, 0, 0), (1, 1, 1)]$ 比解 $[(1, 1, 1), (0, 0, 0)]$ 字典序更小。
## 输入格式

第一行包含三个整数 $n, m, h \ (1 \leq n,m,h \leq 100)$，代表 3D 空间的尺寸。

接下来的 $n$ 行中，每一行包含 $m$ 个字符 $0$ 或 $1$，其中 $1$ 代表有阴影遮住，$0$ 代表无阴影遮住。这 $n \times m$ 个字符描述了一个正投影。

接下来的 $n$ 行中，每一行包含 $h$ 个字符，格式同上。这 $n \times h$ 个字符描述了一个右投影。
## 输出格式

如果无解，仅在第一行输出 $-1$ 即可。

如果有解，第一行输出一个整数 $k_{max}$，代表满足题目要求的解中小正方体个数的最大值。

接下来 $k_{max}$ 行中每行输出三个整数 $x, y, z \ (0 \leq x < n, 0 \leq y < m, 0 \leq z < h)$，代表小正方体最多的解中字典序最小的解的 $k_{max}$ 个小正方体的放置位置。

接下来一行输出一个整数 $k_{min}$，代表满足题目要求的解中小正方体个数的最小值。

接下来 $k_{min}$ 行中每行输出三个整数 $x, y, z \ (0 \leq x < n, 0 \leq y < m, 0 \leq z < h)$，代表小正方体最少的解中字典序最小的解的 $k_{min}$ 个小正方体的放置位置。
## 样例

### 样例输入 #1
```
5 3 3
111
010
010
010
010
111
100
110
100
100
```
### 样例输出 #1
```
14
0 0 0
0 0 1
0 0 2
0 1 0
0 1 1
0 1 2
0 2 0
0 2 1
0 2 2
1 1 0
2 1 0
2 1 1
3 1 0
4 1 0
8
0 0 0
0 1 1
0 2 2
1 1 0
2 1 0
2 1 1
3 1 0
4 1 0
```
### 样例输入 #2
```
2 2 2
00
00
11
11
```
### 样例输出 #2
```
-1
```
### 样例输入 #3
```
2 3 2
101
011
10
11
```
### 样例输出 #3
```
6
0 0 0
0 2 0
1 1 0
1 1 1
1 2 0
1 2 1
4
0 0 0
0 2 0
1 1 0
1 2 1
```
## 提示

一个放置在 $(x, y, z)$ 的小正方体会在正投影的 $(x, y)$ 位置产生一个有阴影遮住的区域，并在右投影的 $(x, z)$ 位置产生一个有阴影遮住的区域。

坐标从 $0$ 开始编号。


---

---
title: "[ICPC 2019 WF] Azulejos"
layout: "post"
diff: 普及+/提高
pid: P6251
tag: ['2019', 'Special Judge', 'O2优化', 'ICPC']
---
# [ICPC 2019 WF] Azulejos
## 题目背景

### Warning: If you submit a malicious program, you will be banned.
### 警告：恶意提交本题将被封号。

## 题目描述

Ceramic artists Maria and João are opening a small azulejo store in Porto. Azulejos are the beautiful ceramic tiles for which Portugal is famous. Maria and João want to create an attractive window display, but, due to limited space in their shop, they must arrange their tile samples in two rows on a single shelf. Each of João's tiles has exactly one of Maria's tiles in front of it and each of Maria's tiles has exactly one of João's tiles behind it. These hand-crafted tiles are of many different sizes, and it is important that each tile in the back row is taller than the tile in front of it so that both are visible to passers-by. For the convenience of shoppers, tiles in each row are arranged in non-decreasing order of price from left to right. Tiles of the same price may be arranged in any order subject to the visibility condition stated above.

Your task is to find an ordering of the tiles in each row that satisfies these constraints, or determine that no such ordering exists.
## 输入格式

The first line of input contains an integer $n$ ($1 \leq n \leq 5 \times 10^5$), the number of tiles in each row. The next four lines contain $n$ integers each; the first pair of lines represents the back row of tiles and the second pair of lines represents the front row. Tiles in each row are numbered from $1$ to $n$ according to their ordering in the input. The first line in each pair contains $n$ integers $p_1, \dots , p_n$ ($1 \leq p_i \leq 10^9$ for each $i$), where $p_i$ is the price of tile number $i$ in that row. The second line in each pair contains $n$ integers $h_1, \dots , h_n$ ($1 \leq h_i \leq 10^9$ for each $i$), where $h_i$ is the height of tile number $i$ in that row.
## 输出格式

If there is a valid ordering, output it as two lines of $n$ integers, each consisting of a permutation of the tile numbers from $1$ to $n$. The first line represents the ordering of the tiles in the back row and the second
represents the ordering of the tiles in the front row. If more than one pair of permutations satisfies the constraints, any such pair will be accepted. If no ordering exists, output `impossible`.
## 样例

### 样例输入 #1
```
4
3 2 1 2
2 3 4 3
2 1 2 1
2 2 1 3
```
### 样例输出 #1
```
3 2 4 1
4 2 1 3
```
### 样例输入 #2
```
2
1 2
2 3
2 8
2 1
```
### 样例输出 #2
```
impossible
```
## 提示

Source: ICPC 2019 World Finals.
## 题目翻译

给你两种瓷砖 $a,b$，每种瓷砖有 $n$ 块，每块瓷砖有两个属性：高度 $h$ 和价值 $p$。

现在要求你把这些瓷砖重新排成两行（$2\times n$）。前一行放瓷砖 $b$，后一行放瓷砖 $a$。

要求从左到右 $p$ 递增（单调不减），对于任意一个位置 $i$，后面的瓷砖要比前面的瓷砖高。

求一种方案或输出无解。

$n\le 5\times 10^5$


---

---
title: "[ICPC 2019 WF] Circular DNA"
layout: "post"
diff: 普及+/提高
pid: P6254
tag: ['模拟', '2019', 'O2优化', 'ICPC']
---
# [ICPC 2019 WF] Circular DNA
## 题目描述

You have an internship with a bioinformatics research group studying DNA. A single strand of DNA consists of many genes, which fall into different categories called gene types. Gene types are delimited by specific nucleotide sequences known as gene markers. Each gene type i has a unique start marker $\texttt s_i$ and a unique end marker $\texttt e_i$ . After many dirty jobs (growing bacteria, cell extraction, protein engineering,and so on), your research group can convert DNA into a form consisting of only the gene markers, removing all the genetic material lying between the markers.

Your research group came up with the interesting hypothesis that gene interpretation depends on whether the markers of some gene types form properly nested structures. To decide whether markers of gene type $i$ form a proper nesting in a given sequence of markers $w$, one needs to consider the subsequence of $w$ containing only the markers of gene type $i$ ($\texttt s_i$ and $\texttt e_i$), leaving none of them out. The following (and only the following) are considered to be properly nested structures:

- $\texttt s_i \texttt e_i$
- $\texttt s_i N \texttt e_i$, where $N$ is a properly nested structure
- $AB$, where $A$ and $B$ are properly nested structures

Given your computing background, you were assigned to investigate this property, but there is one further complication. Your group is studying a specific type of DNA called circular DNA, which is DNA that forms a closed loop. To study nesting in circular DNA, it is necessary to cut the loop at some location, which results in a unique sequence of markers (the direction of reading is fixed by molecular properties). Whether a gene type $i$ forms a proper nesting now also depends on where the circular DNA is cut. Your task is to find the cutting location that maximizes the number of gene types that form a properly nested structure. Figure D.1 shows an example corresponding to Sample Input 1. The indicated cut results in the markers for gene type 1 being properly nested.

![](https://cdn.luogu.com.cn/upload/image_hosting/l856fbko.png)
## 输入格式

The first line of input contains an integer $n$ ($1 \leq n \leq 10^6$), the length of the DNA. The next line contains the DNA sequence, that is, $n$ markers. Each marker is a character $c$ followed by an integer $i$, where $c \in \{\texttt s, \texttt e\}$ specifies whether it is a start or an end marker and $i$ ($1 \leq i \leq 10^6$) is the gene type of the marker. The given DNA sequence has been obtained from the circular DNA by cutting at an arbitrary location.
## 输出格式

Output one line with two integers $p$ and $m$, where $p$ is the cutting position that maximizes the number of different gene types that form a proper nesting, and $m$ is this maximum number of gene types. The DNA is cut just before the $p^{\text{th}}$ input marker (for instance, the cut shown in Figure D.1 has $p = 3$). If more than one cutting position yields the same maximum value of $m$, output the smallest $p$ that does so.
## 样例

### 样例输入 #1
```
9
e1 e1 s1 e2 s1 s2 e42 e1 s1
```
### 样例输出 #1
```
3 1
```
### 样例输入 #2
```
8
s1 s1 e3 e1 s3 e1 e3 s3
```
### 样例输出 #2
```
8 2
```
## 提示

Source: ICPC 2019 World Finals.
## 题目翻译

一个长度为 $n$ 的环形 DNA 序列，以顺时针顺序给出，其中每个基因有类型和编号两个属性，类型是 $s$（头）或 $e$（尾）中的一种，而编号是 $1$ 到 $10^6$ 中的整数。
你需要在某个地方切断，按照顺时针顺序拉成链后，最大化能够完美匹配的基因编号个数。

一个基因编号 $i$ 是能够完美匹配的，当且仅当它在链中对应的所有基因，将 $s$ 看作左括号，$e$ 看作右括号，可以匹配成非空的合法括号序列。

如果有多个位置满足最大化的条件，输出最小的位置。

输入第一行一个整数 $n(1\leq n\leq 10^6)$，表示 DNA 序列的长度，第二行是 DNA 序列，包含 $n$ 个元素，每个元素有一个字符 $c∈\{s,e\}$（$s$ 表示切割时以这个元素为开始还是结束，$s$ 表示开始，$e$ 表示结束）和一个整数 $i (1 \le i \le 10^6)$ 表示基因类型。可以通过在任意位置切割，从环状 DNA 获得给定的 DNA 序列。

输出一行包含两个整数 $p$ 和 $m$，$p$ 是切割位置，可最大化能够完美匹配的基因编号个数，$m$ 是能够完美匹配基因类型的最大数量如果多个切割位置产生相同的最大值 $m$，输出最小的 $p$。


---

---
title: "[ICPC 2019 WF] Dead-End Detector"
layout: "post"
diff: 普及+/提高
pid: P6255
tag: ['2019', 'O2优化', 'ICPC']
---
# [ICPC 2019 WF] Dead-End Detector
## 题目背景

### Warning: If you submit a malicious program, you will be banned.
### 警告：恶意提交本题将被封号。

## 题目描述

The council of your home town has decided to improve road sign placement,especially for dead ends. They have given you a road map, and you must determine where to put up signs to mark the dead ends. They want you to use as few signs as possible.

The road map is a collection of locations connected by two-way streets. The following rule describes how to obtain a complete placement of dead-end signs. Consider a street $S$ connecting a location $x$ with another location. The $x$-entrance of $S$ gets a dead-end sign if, after entering $S$ from $x$, it is not possible to come back to $x$ without making a U-turn. A U-turn is a 180-degree turn immediately reversing the direction.

To save costs, you have decided not to install redundant dead-end signs, as specified by the following rule. Consider a street $S$ with a dead-end sign at its $x$-entrance and another street $T$ with a dead-end sign at its $y$-entrance. If, after entering $S$ from $x$, it is possible to go to $y$ and enter $T$ without making a U-turn, the dead-end sign at the $y$-entrance of $T$ is redundant. See Figure E.1 for examples.

![](https://cdn.luogu.com.cn/upload/image_hosting/33rn5okp.png)

Figure E.1: Illustration of sample inputs, indicating where non-redundant dead-end signs are placed.

## 输入格式

The first line of input contains two integers $n$ and $m$, where $n$ $(1 \leq n \leq 5\times10^5)$ is the number of locations and $m$ $(0 \leq m \leq 5 \times 10^5)$ is the number of streets. Each of the following $m$ lines contains two integers $v$ and $w$ $(1 \leq v \lt w \leq n)$ indicating that there is a two-way street connecting locations $v$ and $w$. All location pairs in the input are distinct.
## 输出格式

On the first line, output $k$, the number of dead-end signs installed. On each of the next $k$ lines, output two integers $v$ and $w$ marking that a dead-end sign should be installed at the $v$-entrance of a street connecting locations $v$ and $w$. The lines describing dead-end signs must be sorted in ascending order of $v$-locations,breaking ties in ascending order of $w$-locations.
## 样例

### 样例输入 #1
```
6 5
1 2
1 3
2 3
4 5
5 6

```
### 样例输出 #1
```
2
4 5
6 5
```
### 样例输入 #2
```
8 8
1 2
1 3
2 3
3 4
1 5
1 6
6 7
6 8

```
### 样例输出 #2
```
3
1 5
1 6
3 4

```
## 提示

Source: ICPC World Finals 2019 Problem E.
## 题目翻译

有一张 $n$ 个点 $m$ 条边的简单无向图。

如果走过一条边 $u→v$ 后，不掉头无法返回到 u，这条边就是对 $u$ 来说的“死路”。

你需要对每个死路标记路标，但是有的路标是多余的。

如果从一个死路 $u→v$ 开始可以不掉头地走到另一个死路 $u' → v'$，那么后者 $u' → v'$ 就是多余的。

最后问要标记多少路标，输出每对 $u→v$，按照 $u$ 为第一关键字，$v$ 为第二关键字排序。

第一行输入 $n$ , $m$ ，后 $m$ 行每行两个整数 $u$ , $v$ 。

输出的第一行是要标记的路标数 $k$ ，然后 $k$ 行每行一对题目所说的死路 ： $u→v$ （不要输出“$→$”）。


---

---
title: "[ICPC 2015 WF] Keyboarding"
layout: "post"
diff: 普及+/提高
pid: P6909
tag: ['2015', 'ICPC']
---
# [ICPC 2015 WF] Keyboarding
## 题目描述

How many keystrokes are necessary to type a text message? You may think that it is equal to the number of characters in the text, but this is correct only if one keystroke generates one character. With pocket-size devices, the possibilities for typing text are often limited. Some devices provide only a few buttons, significantly fewer than the number of letters in the alphabet. For such devices, several strokes may be needed to type a single character. One mechanism to deal with these limitations is a virtual keyboard displayed on a screen, with a cursor that can be moved from key to key to select characters. Four arrow buttons control the movement of the cursor, and when the cursor is positioned over an appropriate key, pressing the fifth button selects the corresponding character and appends it to the end of the text. To terminate the text, the user must navigate to and select the Enter key. This provides users with an arbitrary set of characters and enables them to type text of any length with only five hardware buttons.

In this problem, you are given a virtual keyboard layout and your task is to determine the minimal number of strokes needed to type a given text, where pressing any of the five hardware buttons constitutes a stroke. The keys are arranged in a rectangular grid, such that each virtual key occupies one or more connected unit squares of the grid. The cursor starts in the upper left corner of the keyboard and moves in the four cardinal directions, in such a way that it always skips to the next unit square in that direction that belongs to a different key. If there is no such unit square, the cursor does not move.

![](https://cdn.luogu.com.cn/upload/image_hosting/3cxjl2y4.png)

   Figure 1: Sample Input 1. An example virtual keyboard and hardware buttons. 

Figure 1, illustrating Sample Input 1, shows a possible way to type CONTEST using 30 strokes on an example virtual keyboard. The red dots represent the virtual keys where the select button was pressed.
## 输入格式

The first line of the input contains two integers $r$ and $c$ ($1 \leq r, c \leq 50$), giving the number of rows and columns of the virtual keyboard grid. The virtual keyboard is specified in the next $r$ lines, each of which contains $c$ characters. The possible values of these characters are uppercase letters, digits, a dash, and an asterisk (representing Enter). There is only one key corresponding to any given character. Each key is made up of one or more grid squares, which will always form a connected region. The last line of the input contains the text to be typed. This text is a non-empty string of at most $10\, 000$ of the available characters other than the asterisk.
## 输出格式

Display the minimal number of strokes necessary to type the whole text, including the Enter key at the end. It is guaranteed that the text can be typed.
## 样例

### 样例输入 #1
```
4 7
ABCDEFG
HIJKLMN
OPQRSTU
VWXYZ**
CONTEST

```
### 样例输出 #1
```
30

```
### 样例输入 #2
```
5 20
12233445566778899000
QQWWEERRTTYYUUIIOOPP
-AASSDDFFGGHHJJKKLL*
--ZZXXCCVVBBNNMM--**
--------------------
ACM-ICPC-WORLD-FINALS-2015

```
### 样例输出 #2
```
160

```
### 样例输入 #3
```
2 19
ABCDEFGHIJKLMNOPQZY
X*****************Y
AZAZ

```
### 样例输出 #3
```
19

```
### 样例输入 #4
```
6 4
AXYB
BBBB
KLMB
OPQB
DEFB
GHI*
AB

```
### 样例输出 #4
```
7

```
## 提示

Time limit: 3000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2015
## 题目翻译

给定一个 $r$ 行 $c$ 列的在电视上的「虚拟键盘」，通过「上，下，左，右，选择」共 $5$ 个控制键，你可以移动电视屏幕上的光标来打印文本。一开始，光标在键盘的左上角，每次按方向键，光标总是跳到下一个在该方向上与当前位置的字符不同的字符，若不存在则不移动。每次按选择键，则将光标所在位置的字符打印出来。  
现在求打印给定文本（要在结尾打印换行符）的最少按键次数。


---

---
title: "[ICPC 2016 WF] Ceiling Function"
layout: "post"
diff: 普及+/提高
pid: P6919
tag: ['2016', 'ICPC']
---
# [ICPC 2016 WF] Ceiling Function
## 题目描述

Advanced Ceiling Manufacturers (ACM) is analyzing the properties of its new series of Incredibly Collapse-Proof Ceilings (ICPCs). An ICPC consists of $n$ layers of material, each with a different value of collapse resistance (measured as a positive integer). The analysis ACM wants to run will take the collapse-resistance values of the layers, store them in a binary search tree, and check whether the shape of this tree in any way correlates with the quality of the whole construction. Because, well, why should it not?

To be precise, ACM takes the collapse-resistance values for the layers, ordered from the top layer to the bottom layer, and inserts them one-by-one into a tree. The rules for inserting a value $v$ are:

If the tree is empty, make $v$ the root of the tree.

If the tree is not empty, compare $v$ with the root of the tree. If $v$ is smaller, insert $v$ into the left subtree of the root, otherwise insert $v$ into the right subtree.

ACM has a set of ceiling prototypes it wants to analyze by trying to collapse them. It wants to take each group of ceiling prototypes that have trees of the same shape and analyze them together.

For example, assume ACM is considering five ceiling prototypes with three layers each, as described by Sample Input 1 and shown in Figure 1. Notice that the first prototype’s top layer has collapse-resistance value 2, the middle layer has value 7, and the bottom layer has value 1. The second prototype has layers with collapse-resistance values of 3, 1, and 4 – and yet these two prototypes induce the same tree shape, so ACM will analyze them together.

Given a set of prototypes, your task is to determine how many different tree shapes they induce.

![](https://cdn.luogu.com.cn/upload/image_hosting/xvdteesl.png)

   Figure 1: The four tree shapes induced by the ceiling prototypes in Sample Input 1. 
## 输入格式

The first line of the input contains two integers $n$ ($1 \le n \le 50$), which is the number of ceiling prototypes to analyze, and $k$ ($1 \le k \le 20$), which is the number of layers in each of the prototypes.

The next $n$ lines describe the ceiling prototypes. Each of these lines contains $k$ distinct integers (between $1$ and $10^6$, inclusive), which are the collapse-resistance values of the layers in a ceiling prototype, ordered from top to bottom.
## 输出格式

Display the number of different tree shapes.
## 样例

### 样例输入 #1
```
5 3
2 7 1
3 1 4
1 5 9
2 6 5
9 7 3

```
### 样例输出 #1
```
4

```
### 样例输入 #2
```
3 4
3 1 2 40000
3 4 2 1
33 42 17 23

```
### 样例输出 #2
```
2

```
## 提示

Time limit: 5000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2016
## 题目翻译

给出 $n$ 组数，每组 $k$ 个，求这些数每组分别按顺序插入构成的不同二叉搜索树的数量。


---

---
title: "[ICPC 2017 WF] Posterize"
layout: "post"
diff: 普及+/提高
pid: P6934
tag: ['2017', 'ICPC']
---
# [ICPC 2017 WF] Posterize
## 题目描述



![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/14638/1.png)

Pixels in a digital picture can be represented with three integers in the range $0$ to $255$ that indicate the intensity of the red, green, and blue colors. To compress an image or to create an artistic effect, many photo-editing tools include a `posterize` operation which works as follows. Each color channel is examined separately; this problem focuses only on the red channel. Rather than allow all integers from $0$ to $255$ for the red channel, a posterized image allows at most $k$ integers from this range. Each pixel's original red intensity is replaced with the nearest of the allowed integers. The photo-editing tool selects a set of $k$ integers that minimizes the sum of the squared errors introduced across all pixels in the original image. If there are $n$ pixels that have original red values $r_{1},$ . . . , $r_{n},$ and $k$ allowed integers $v_{1},$ . . . , $v_{k},$ the sum of squared errors is defined as

$$\sum\limits_{i=1}^n \min\limits_{1 \le j \le k}(r_i-v_j)^2$$

Your task is to compute the minimum achievable sum of squared errors, given parameter $k$ and a description of the red intensities of an image's pixels.


## 输入格式



The first line of the input contains two integers $d (1 \le d \le 256)$ , the number of distinct red values that occur in the original image, and $k (1 \le k \le d)$ , the number of distinct red values allowed in the posterized image. The remaining $d$ lines indicate the number of pixels of the image having various red values. Each such line contains two integers $r (0 \le r \le 255)$ and $p (1 \le p \le 2^{26}),$ where $r$ is a red intensity value and $p$ is the number of pixels having red intensity $r$ . Those $d$ lines are given in increasing order of red value.


## 输出格式



Display the sum of the squared errors for an optimally chosen set of $k$ allowed integer values.


## 样例

### 样例输入 #1
```
2 1
50 20000
150 10000

```
### 样例输出 #1
```
66670000

```
### 样例输入 #2
```
2 2
50 20000
150 10000

```
### 样例输出 #2
```
0

```
### 样例输入 #3
```
4 2
0 30000
25 30000
50 30000
255 30000

```
### 样例输出 #3
```
37500000

```
## 提示

Time limit: 2 s, Memory limit: 512 MB. 


## 题目翻译

给定 $d$ 类元素，第 $i$ 类元素的取值为 $r_i$，且有 $p_i$ 个，按照这些信息可以将这些元素排列在一个长度为 $n=\sum p_i$ 的序列里，现在你要做的是规划一个长度为 $k$ 的序列 $v_i$，使得按照如下定义的序列误差最小：

$$\sum\limits_{i=1}^n \min\limits_{1 \le j \le k}(r_i-v_j)^2$$

求最小序列误差。

$1 \le k \le d \le 256$，$0 \le r \le 255$，$1 \le p \le 2^{26}$。

翻译者：一只书虫仔


---

---
title: "[ICPC 2018 WF] Go with the Flow"
layout: "post"
diff: 普及+/提高
pid: P6946
tag: ['2018', 'ICPC']
---
# [ICPC 2018 WF] Go with the Flow
## 题目描述



In typesetting, a `river` is a string of spaces formed by gaps between words that extends down several lines of text. For instance, Figure F.1 shows several examples of rivers highlighted in red (text is intentionally blurred to make the rivers more visible).

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/15694/1.png)

Figure F.1 : Examples of rivers in typeset text.

Celebrated river authority Flo Ng wants her new book on rivers of the world to include the longest typographic rivers possible. She plans to set the text in a mono-spaced font (all letters and spaces have equal width) in a left-aligned column of some fixed width, with exactly one space separating words on each line (the text is not aligned on the right). For Flo, a `river` is defined as a sequence of spaces lying in consecutive lines in which the position of each space in the sequence (except the first) differs by at most $1$ from the position of the space in the line above it. Trailing white space cannot appear in a river. Words must be packed as tightly as possible on lines; no words may be split across lines. The line width used must be at least as long as the longest word in the text. For instance, Figure F.2 shows the same text set with two different line widths.

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/15694/2.png)

Figure F.2 : Longest rivers $( \times )$ for two different line widths.

Given a text, you have been tasked with determining the line width that produces the longest river of spaces for that text.


## 输入格式



The first line of input contains an integer $n (2 \le n \le 2 500)$ specifying the number of words in the text. The following lines of input contain the words of text. Each word consists only of lowercase and uppercase letters, and words on the same line are separated by a single space. No word exceeds $80$ characters.


## 输出格式



Display the line width for which the input text contains the longest possible river, followed by the length of the longest river. If more than one line width yields this maximum, display the shortest such line width.


## 样例

### 样例输入 #1
```
21
The Yangtze is the third longest
river in Asia and the longest in
the world to flow
entirely in one country

```
### 样例输出 #1
```
15 5

```
### 样例输入 #2
```
25
When two or more rivers meet at
a confluence other than the sea
the resulting merged river takes
the name of one of those rivers

```
### 样例输出 #2
```
21 6

```
## 提示

Time limit: 12 s, Memory limit: 1024 MB. 


## 题目翻译

#### 题目描述
在字体排印学中，“川流”是由单词之间的间隙组成的连续几列的空格。如图所示为几个用红色高亮标出的“川流”（文本被有意模糊处理来凸显川流）：

![img](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/15694/1.png)

知名川流机构 Flo Ng 希望他在新的关于世界河流的书上出现尽可能长的川流。他会使用一种单一字宽的字体（每个字母和空格都具有相同的宽度）且左对齐，单词之间恰用一个空格分隔。对 Flo 来说，一条“川流”指的是连续几行里的空格，且相邻空格在行里出现的位置的距离不超过 $1$。川流不能包含末尾的空格。每行的单词都必须尽可能地紧凑，但不能有单词被拆到两行里。行宽至少不能短于文本中最长的一个单词。下图是同一个文本使用不同行宽的一个例子。

![img](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/15694/2.png)

给定文本，你需要求出一个行宽使得该文本最长的川流尽可能长。

#### 输入格式
第一行有一个整数 $n(2≤n≤2500)$ 表示文本的单词个数。接下来几行为该文本的单词。每个单词都只包含大写和小写字母，且长度不超过 $80$ 个字符。

#### 输出格式
输出两个整数，分别表示使得文本出现最长的川流的行宽以及川流的长度。如果有多个行款达到川流长度的最大值，输出最小的行宽。


---

---
title: "[ICPC 2018 WF] Wireless is the New Fiber"
layout: "post"
diff: 普及+/提高
pid: P6951
tag: ['2018', 'Special Judge', 'ICPC']
---
# [ICPC 2018 WF] Wireless is the New Fiber
## 题目描述



A new type of unbounded-bandwidth wireless communication has just been tested and proved to be a suitable replacement for the existing, fiber-based communications network, which is struggling to keep up with traffic growth. You have been charged with deciding the layout of the new communications network. The current communications network consists of a set of nodes (which route messages), and links of fiber, each of which connects two different nodes. For each pair of nodes, there exists at least one way (but possibly more, for bandwidth purposes) to travel along the fiber between the two.

The new communications network will not have any fiber. Instead, it will have wireless links, each connecting two nodes. These links have unbounded bandwidth but are expensive, so it has been decided that as few of these links will be built as possible to provide connectivity; for each pair of nodes there should be exactly one way to travel between them along the wireless links. Moreover, you discovered that the nodes have each been built with a particular number of connections in mind. For each node, if it will be connected to a different number of links than it is today, it will have to be reorganized, and that is costly.

Your task is to design the new network so that it has precisely one path between each pair of nodes while minimizing the number of nodes that do not have the same number of connections as in the original network. Figure K.1 shows the original network and a solution for Sample Input $1$ .

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/15699/1.png)

Figure K.1 : Illustration of Sample Input $1$ .


## 输入格式



The input begins with a line containing two integers $n (2 \le n \le 10^{4})$ and $m (1 \le m \le 10^{5}),$ denoting the number of nodes and the number of fiber links in the existing network. The nodes are numbered from $0$ to $n − 1$ . Each of the next $m$ lines contains two distinct integers $a_{i}$ and $b_{i},$ denoting the fact that the $i^{th}$ fiber link connects nodes numbered $a_{i}$ and $b_{i}.$ It is guaranteed that for each pair of nodes there exists at least one path connecting the two nodes. Any pair of nodes may have more than one fiber link connecting them.


## 输出格式



Display the smallest number of nodes for which the number of connected links needs to change. Starting on the next line, display a system of connections in the same format as the input. That is, display a line containing the number of nodes (this will be the same as in the input) and the number of wireless links, and then on subsequent lines descriptions of the links. If more than one layout is possible, any valid layout will be accepted.


## 样例

### 样例输入 #1
```
7 11
0 1
0 2
0 5
0 6
1 3
2 4
1 2
1 2
1 5
2 6
5 6

```
### 样例输出 #1
```
3
7 6
0 1
0 2
0 5
0 6
3 6
4 6

```
### 样例输入 #2
```
4 3
0 1
2 1
2 3

```
### 样例输出 #2
```
0
4 3
2 1
1 3
0 2

```
## 提示

Time limit: 2 s, Memory limit: 1024 MB. 

SPJ provider: @[shenyouran](/user/137367).
## 题目翻译

给你一张 $n$ 个点 $m$ 条边的无向连通图，用这 $n$ 个点重新构建一棵树使得有尽可能少的节点度数发生改变，求一种方案。


---

---
title: "[NEERC 2017] Box"
layout: "post"
diff: 普及+/提高
pid: P6953
tag: ['2017', 'ICPC']
---
# [NEERC 2017] Box
## 题目描述



Bella is working in a factory that produces boxes. All boxes are in a shape of rectangular parallelepipeds. A net of the corresponding parallelepiped is cut out of a flat rectangular piece of cardboard of size $w$ *h . This net is a polygon with sides parallel to the sides of the rectangle of the cardboard. The net is bent along several lines and is connected along the edges of the resulting parallelepiped to form a box. The net is bent only along the edges of the resulting box.

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/15284/1.png)

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/15284/2.png)

The first example

The third example

Bella is a software developer and her task is to check whether it is possible to make a box of size $a \times b \times c$ out of a cardboard of size $w \times h$ . Bella did write a program and boxes are being produced. Can you do the same?


## 输入格式



The first line contains three integers a , $b$ , and $c$ -- the dimensions of the box.

The second line contains two integers $w$ and $h$ -- the width and the height of the cardboard.

All integers are positive and do not exceed $10^{8}.$


## 输出格式



Print `Yes` if it is possible to cut a box a $ \times b \times c$ out of a cardboard of size $w \times h$ . Print `No` otherwise.


## 样例

### 样例输入 #1
```
1 2 3
6 5

```
### 样例输出 #1
```
Yes

```
### 样例输入 #2
```
1 2 3
5 5

```
### 样例输出 #2
```
No

```
### 样例输入 #3
```
1 1 1
10 2

```
### 样例输出 #3
```
Yes

```
## 提示

Time limit: 3 s, Memory limit: 512 MB. 


## 题目翻译

给出一个长方体的长、宽、高（分别是 $a, b, c$），问：能否在一张长为 $w$，宽为 $h$ 的纸上裁出这个长方体的某一个侧面展开图。

如果可以，请输出 `Yes`，否则输出 `No`。


---

---
title: "[NEERC 2017] Designing the Toy"
layout: "post"
diff: 普及+/提高
pid: P6955
tag: ['2017', 'Special Judge', 'ICPC']
---
# [NEERC 2017] Designing the Toy
## 题目描述



You are the main toy producer in the city. Recently you bought a $3D-printer$ that provides you with an unprecedented opportunity for designing new fancy toys for children.

In a package with the $3D-printer$ there is a booklet containing several examples of what can be created with it. One of the examples is a figure that looks like a triangle, like a circle, or like a square depending on which of its sides you are looking at.

Unfortunately, it turned out that the booklet describes the most recent version of your printer. Your printer is only able to create figures that consist of voxels (three-dimensional pixels), i.e . figures that look like a union of a unit-length cubes that are the cells of a three-dimensional grid. Thus, you are not able to print any `smooth` figures (like a sphere, for example) with it. On the other hand, important feature of your model is its ability to create figures whose parts are not even connected with each other by putting wires of a negligible thickness between them.

You like the idea of the figure in the booklet, so you decided to improve upon this idea. Instead of specifying shapes of figure projections from different perspectives, you would specify their areas. In this problem, a voxel is defined by a triple of integers $(x , y , z)$ , which corresponds to a unit cube [x , $x + 1] \times $ [y , $y + 1] \times $ [z , $z + 1].$

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/15286/1.png)

You are given three positive integers a , $b$ and $c$ . Your task is to find a description of a figure $F$ consisting of one or more voxels, for which the area of its orthogonal projection onto the plane Oxy is a , the area of its orthogonal projection onto the plane Oxz is $b$ , and the area of its orthogonal projection onto the plane Oyz is $c$ , or to determine that it is impossible.


## 输入格式



The only line of the input contains three integers a , $b$ , and $c (1 \le $ a , $b , c \le 100)$ -- the desired area of orthogonal projections onto the planes Oxy, Oxz, and Oyz correspondingly.


## 输出格式



If it is impossible to find the desired figure, print only the integer $−1$ .

Otherwise, in the first line print the integer $n$ , defining the number of voxels in the figure. Then print $n$ triples $x , y , z (−100 \le x , y , z \le 100)$ defining the voxels of the figure. Voxels may be printed in any order, but no voxel may be repeated twice.

The number of voxels $n$ should not exceed $10^{6}.$

Any figure with the requested projection areas is accepted.


## 样例

### 样例输入 #1
```
4 3 5

```
### 样例输出 #1
```
6
0 0 0
0 1 0
0 2 0
0 2 2
1 2 2
0 0 2

```
### 样例输入 #2
```
100 1 1

```
### 样例输出 #2
```
-1

```
## 提示

Time limit: 3 s, Memory limit: 512 MB. 


## 题目翻译

## 题目描述

你是这里的玩具生产大佬。最近你买了一台 3D 打印机，它给你提供了一个~~大赚一笔~~创造新玩具的机会。

你的打印机只能打印由一个个单位方块（棱长为 $1$ 的正方体）构成的几何体。因此，你不能打印出任何“光滑”的几何体（比如球体）。另外，这台打印机打印的几何体可以有完全不相连甚至浮空的部分。

建立空间直角坐标系。一个 $[x , x + 1] $ $\times $ $[y , y + 1]$ $\times $ $[z , z + 1]$ 的方块用整数三元组 $(x , y , z)$ 表示。

现在你想指定打印出的几何体在平面 $Oxy$，平面 $Oxz$ 和平面 $Oyz$ 上的投影面积。

![](https://cdn.luogu.com.cn/upload/image_hosting/udemly1h.png)

给出三个正整数 $a,b,c$，依次表示几何体在平面 $Oxy$，平面 $Oxz$ 和平面 $Oyz$ 上的投影面积。判断该集合体是否存在，若存在，找到满足条件的几何体。

## 输入格式

一行，包含 $3$ 个正整数 $a,b,c$ $(1 \le a , b , c \le 100)$。

## 输出格式

如果所求几何体不存在，输出 `-1` 。

否则，输出的第一行包含一个整数 $n$，表示图中方块的数量。

接下来 $n$ 行，每行 $3$ 个整数 $x,y,z$ 表示每个方块的位置。方块可以按任意顺序输出，但不能重复。

$n$ 的值不应超过 $10^{6}$。

任何满足条件的几何体都算作正确。

## 提示

时间限制：3s，内存限制：512MB。

Translated by Georiky


---

---
title: "[NEERC 2016] Abbreviation"
layout: "post"
diff: 普及+/提高
pid: P6964
tag: ['2016', 'ICPC']
---
# [NEERC 2016] Abbreviation
## 题目描述



An abbreviation (from Latin brevis, meaning short) is a shortened form of a word or phrase. In this problem you must write an automated tool that replaces a sequence of capitalized words with the corresponding abbreviation that consists of the first upper case letters only, followed by a full definition in parenthesis. See sample input and output.

Let us make some formal definitions. A word in a text is a maximally long sequence of lower and upper case English letters. A capitalized word is a word that consists of an upper case letter followed by one or more lower case letters. For example, `Ab`, `Abc`, `Abcd`, and `Abcde` are all capitalized words, while `ab`, `A`, `AB`, `ABc` and `AbC` are not.

An abbreviatable sequence of words is a sequence of two or more capitalized words that are separated by exactly one space, no line breaks or punctuation are allowed inside it.

An abbreviation of an abbreviatable sequence of words is a sequence of the first (upper case) letters of each word, followed by a single space, an opening parenthesis, the original abbreviatable sequence, and a closing parenthesis.


## 输入格式



The input file consists of up to $1 000$ lines of text with up to $120$ characters on each line. Each line consists of spaces, upper and lower case letters, commas or dots. There are no leading or trailing spaces on lines and there are no empty lines. There is at least one line in the input file.


## 输出格式



Write to the output file the original text with every abbreviatable sequence of words replaced with the corresponding abbreviation.


## 样例

### 样例输入 #1
```
This is ACM North Eastern European Regional Contest,
sponsored by International Business Machines.
The. Best. Contest. Ever.
A Great Opportunity for all contestants.

```
### 样例输出 #1
```
This is ACM NEERC (North Eastern European Regional Contest),
sponsored by IBM (International Business Machines).
The. Best. Contest. Ever.
A GO (Great Opportunity) for all contestants.

```
### 样例输入 #2
```
ab Ab A Abc AB Abcd ABc Abcde AbC

```
### 样例输出 #2
```
ab Ab A Abc AB Abcd ABc Abcde AbC

```
### 样例输入 #3
```
Oh  No  Extra Spaces.And,Punctuation Ruin Everything

```
### 样例输出 #3
```
Oh  No  ES (Extra Spaces).And,PRE (Punctuation Ruin Everything)

```
## 提示

Time limit: 1 s, Memory limit: 512 MB. 


## 题目翻译

### 题目描述
定义 word 为一个首字母大写、长度大于 1 、 其他位为小写字母的单词，如 `Ab`、 `Abc`、 `Abcd`、 和 `Abcde`，但 `ab`、`A`、 `AB`、 `ABc` 和 `AbC`。

定义一个 word 串为一个有大于 1 个 word 、每两个 word 中有且只有一个空格的串，如 `International Business Machines`。

现给你若干行，如遇到 word 串则让他变为缩写，缩写方式为：先提取首字母（大写），再加空格和 `(` ，再把全称写出来，最后加上 `)` ，如: `International Business Machines` 可缩写为 `IBM (International Business Machines)` 。

### 输入格式
若干行（不超过 1000 行）由大小写字母、标点和空格组成的的字符串（每行不超过 120 个字符）。

### 输出格式
缩写后的若干行字符串（无法缩写的不用缩写）。

#### translate by:`ddgtang`


---

---
title: "[NEERC 2013] Bonus Cards"
layout: "post"
diff: 普及+/提高
pid: P6997
tag: ['2013', 'Special Judge', 'ICPC']
---
# [NEERC 2013] Bonus Cards
## 题目描述



Dmitry loves programming competitions very much. The Finals of the famed Champions League are taking place in Dmitry's home city, so he wants to visit the competition. The competition is very popular, but most tickets to the competition are reserved for VIPs and for sponsors.

For the general public tickets to the Champions League Finals are distributed in the following way. Spectators, that want to see the competition, submit their request that states the payment method they want to use to pay for their ticket. Suppose there are $n$ seats available. Several draw round are conducted. In each round every request that is not yet fulfilled receives some number of slots depending on the payment method. Then one of those slots is selected uniformly at random. The request to which this slot belongs is considered fulfilled and does not take part in subsequent drawing rounds. Draw ends after $n$ rounds or when there are no more unfulfilled requests, whichever occurs first. An International Card Processing Corporation (ICPC) is a sponsor of the Champions League. Those who chose ICPC card as a payment method receive two slots in each draw round, while users of other payment methods receive only one.

Dmitry has a card from ICPC, but he also has a card from Advanced Credit Merchandise $(ACM),$ which offers him a bonus on all his spendings. His brother Petr works in a company that conducts draw to distribute tickets, so he told Dmitry in advance how many people had already decided to use ICPC card and how many had decided to use other methods. Now Dmitry want to know the probabilities he would get a ticket if he would use his ICPC card or if he would use his ACM card, so that he can make an informed choice. His request is going to be in addition to the number of requests Petr had told him about.

Can you help?


## 输入格式



The first and the only line of the input contains $3$ integer numbers -- the number of seats available for a draw $n (1 \le n \le 3000)$ , the number of requests with ICPC card as a payment method a , and the number of requests with other payment methods $b (0 \le $ a , $b \le 10^{9}).$


## 输出格式



On the first line output the probability of getting a ticket using ICPC card. On the second line output the probability of getting a ticket using ACM card. Answers should have an absolute error of no more than $10^{-9}.$


## 样例

### 样例输入 #1
```
1 1 2

```
### 样例输出 #1
```
0.3333333333333333
0.2

```
### 样例输入 #2
```
10 10 10

```
### 样例输出 #2
```
0.5870875690480144
0.3640355515319861

```
## 提示

Time limit: 1 s, Memory limit: 128 MB. 


## 题目翻译

一个比赛有 $n$ 张比赛门票，门票用随机抽选的方式决定。有 $a$ 个人参与一类抽选，$b$ 个人参与二类抽选，其中一类抽选选中的概率是二类抽选的两倍。共进行 $n$ 次抽选，第 $i$ 次随机抽选在前 $i-1$ 次没有选出的名额中选出一个人。也就是说，这个人获得了比赛门票，接下来第 $i+1$ 到 $n$ 次的抽选集合不包括他。

Dmitry 现在如果要参加门票抽选，请你求出他分别参与一类抽选名额和二类抽选名额时，能够获得比赛门票的概率。（$a,b$ 个人不包括 Dmitry）


---

---
title: "[NEERC 2013] Kabaleo Lite"
layout: "post"
diff: 普及+/提高
pid: P7006
tag: ['2013', 'Special Judge', 'ICPC']
---
# [NEERC 2013] Kabaleo Lite
## 题目描述



Kabaleo Lite is a board game. The board consists of several stacks of conical chips of various colors. Only the color of the top chip of the stack is visible.

Each player has a unique target color and a set of colored chips. The target color is hidden from other players, while the set of chips is visible to them. On his turn, player selects one of his chips and puts it on one of the board stacks, thus recoloring it to the color of the chosen chip.

After the last turn, the number of visible board chips of each color is calculated. The winning color is the color that occurs the maximum times. The player (if any) that has this color as his target color, wins the game. If there is no such player or if there are two or more colors that occur the maximum times, the game ends in a draw.

You are playing your last chip in the Kabaleo Lite game. Other players also have one chip left. You want to determine all possible moves that lead you to winning the game. You do not know the target colors of other players and you cannot predict their moves, so your move must guarantee your victory regardless of moves of your opponents.


## 输入格式



The first line contains four integers $n , p , c$ and $h$ -- the number of stacks on the board $(1 \le n \le 10^{6}),$ the number of players $(1 \le p \le 10^{6}),$ the number of chips' colors $(p \le c \le 10^{6}),$ and your hidden color $(1 \le h \le c)$ .

The second line contains $n$ integers $b_{i}$ -- the color of the visible board chip for each stack on the board $(1 \le b_{i} \le c)$ .

The third line contains $p$ integers $l_{i}$ -- the color of the last chip for each player $(1 \le l_{i} \le c)$ . The players are numbered from one (you) to $n$ in the order of their turns.


## 输出格式



The first line must contain $w$ -- the number of winning moves.

The second line must contain $w$ distinct numbers $m_{i}$ -- the numbers of the stacks on which your chip should be put to win. Stacks are numbered starting from $1$ in the order that their visible colors are given in the input file. You can output their numbers in any order on this line.

Remember, that your move should be winning regardless of the moves of all other players.


## 样例

### 样例输入 #1
```
6 3 4 2
2 1 2 3 2 2
2 1 1

```
### 样例输出 #1
```
1
2

```
## 提示

Time limit: 1 s, Memory limit: 128 MB. 


## 题目翻译

有一种棋盘游戏：棋盘上有 $n$ 个格子，每个格子上可以堆叠若干个有颜色的筹码，只有每个格子中最上方的筹码的颜色是可见的。

参加游戏的每个玩家都有各自不同的一个目标颜色，以及一些彩色筹码。每个人只知道自己的目标颜色，但各自拥有的筹码颜色和数量都是公开的。每个回合中，所有玩家轮流在棋盘上选一个格子放置筹码，同时覆盖下方的筹码。游戏结束后，数出棋盘上可见筹码数最多的颜色，以该颜色为目标颜色的玩家即获胜。若该颜色不是任何玩家的目标颜色，或者棋盘上出现最多的颜色不唯一，则游戏平局。

现在，一局游戏进行到了最后，你和其他所有玩家都只剩最后一个筹码。现在恰好轮到你操作，在不知道其他人的目标颜色的前提下，你想知道你一共有哪些操作可以保证必胜。

### 输入格式

第一行 $4$ 个整数 $n,p,c,h$，分别表示棋盘格数、玩家数、筹码颜色总数和你的目标颜色；

第二行 $n$ 个整数 $b_i$，表示棋盘上现有的筹码颜色，棋盘格编号从 $1$ 开始；

第三行 $p$ 个整数 $l_i$，表示每个玩家的最后一枚筹码的颜色，玩家编号从你开始。

### 输出格式

第一行 $1$ 个整数 $w$，表示你有多少种必胜操作。

第二行 $w$ 个整数 $m_i$，表示你应该把筹码放在哪个格子上。顺序不限。

数据范围见原题。


---

---
title: "[CERC2013] Crane"
layout: "post"
diff: 普及+/提高
pid: P7015
tag: ['2013', 'Special Judge', 'ICPC']
---
# [CERC2013] Crane
## 题目描述



There are $n$ crates waiting to be loaded onto a ship. The crates are numbered $1 , 2 , \cdots , n$ , the numbers determining the order of loading. Unfortunately, someone messed up the transit and the crates are standing in a row in an arbitrary order. As there is only limited space in the dock area, you must sort the crates by swapping some of them.

You are given a crane that works in the following way: you select a connected interval of crates of even length. The crane then exchanges the first half of the interval with the second half. The order inside both halves remains unchanged. Determine the sequence of crane moves that reorders the crates properly.

The crane's software has a bug: the move counter is a $9-based$ (not $10-based,$ as you might think) integer with at most $6$ digits. Therefore, the crane stops working (and has to be serviced) after $9^{6} = 531441$ moves. Your solution must fit within this limit.


## 输入格式



The first line of input contains the number of test cases $T$ . The descriptions of the test cases follow:

Each test case starts with an integer $n , 1 \le n \le 10 000$ , denoting the number of crates. In the next line a permutation of numbers ${1 , 2 , \cdots $ , n} follows.


## 输出格式



For each test case print a single line containing $m -$ the number of swaps $-$ followed by $m$ lines describing the swaps in the order in which they should be performed. A single swap is described by two numbers $-$ the indices of the first and the last element in the interval to be exchanged. Do not follow the crane's strange software design $-$ use standard decimal numeral system.


## 样例

### 样例输入 #1
```
2
6
5 4 6 3 2 1
5
1 2 3 4 5

```
### 样例输出 #1
```
5
1 2
4 5
5 6
4 5
1 6
0

```
## 提示

Time limit: 4 s, Memory limit: 128 MB. 


## 题目翻译

有 $n$ 个箱子等着装上船。箱子的编号是 $a_1,a_2,\cdots,a_n$。你的工作是通过若干次交换，将它们从小到大排列。你每次可以选择一个区间，将它的前半部分与后半部分交换，两半内部的顺序保持不变。你最多可以交换 $531441$ 次。 

### 输入格式

第一行输入包含数据组数 $T$。

接下来 $2\times T$ 行，表示 $T$ 组数据。每组数据的第一行为 $n\ (1 \leq n \leq 10000)$，表示箱子的数量。第二行为 $n$ 个正整数$a_1,a_2,\cdots,a_n $ ，表示箱子的编号。

### 输出格式

对于每组数据，首先输出一个数 $m$ ，表示交换的次数。 然后输出 $m$ 行，按照顺序描述每一次交换。对于每次交换，输出要交换的区间中第一个元素和最后一个元素的下标。


---

---
title: "[CERC2013] Digraphs"
layout: "post"
diff: 普及+/提高
pid: P7017
tag: ['2013', 'Special Judge', 'ICPC']
---
# [CERC2013] Digraphs
## 题目描述

A digraph is a graph with orientation... oh, sorry, not this time. Let's stop being nerds for a minute and talk about languages (human languages, not PHP).

Digraphs are pairs of characters that represent one phoneme (sound). For example, "ch" in English (as in "church") is a single consonant sound. The languages of Central Europe are fond of digraphs: Hungarian "sz", Czech "ch" and Polish "rz" are fine examples of them.

Digraphs are very annoying for people who do not use them natively. We will make up a letter-puzzle specifically for those people. Given a list of digraphs, construct a biggest possible square of lower case English letters such that its rows and columns do not contain any of these digraphs. This means that no two consecutive letters (read from top to bottom or from left to right) can form a digraph.

## 输入格式


The first line of input contains the number of test cases $T$ . The descriptions of the test cases follow:

Each test case starts with an integer $n , 0 \le n \le 676$ , denoting the number of forbidden digraphs. The $n$ following lines contain the digraphs.

## 输出格式

For each test case print a square of the largest possible size which does not contain any of the digraphs. If it is possible to construct a square of size $20 \times 20$ or bigger, print only a $20 \times 20$ square.

Warning: Part of the example test data below was omitted for clarity. You can access full sample tests at your workstation. 
## 样例

### 样例输入 #1
```
2
628
aa
az
ba
bb
bc
bd
be
bf
bg
bh
bi
bj
bk
bl
bm
bn
bo
bp
bq
br
bs
bt
bu
bv
bw
bx
by
ca
cb
cc
cd
ce
cf
cg
ch
ci
cj
ck
cl
cm
cn
co
cp
cq
cr
cs
ct
cu
cv
cw
cx
cy
da
db
dc
dd
de
df
dg
dh
di
dj
dk
dl
dm
dn
do
dp
dq
dr
ds
dt
du
dv
dw
dx
dy
ea
eb
ec
ed
ee
ef
eg
eh
ei
ej
ek
el
em
en
eo
ep
eq
er
es
et
eu
ev
ew
ex
ey
fa
fb
fc
fd
fe
ff
fg
fh
fi
fj
fk
fl
fm
fn
fo
fp
fq
fr
fs
ft
fu
fv
fw
fx
fy
ga
gb
gc
gd
ge
gf
gg
gh
gi
gj
gk
gl
gm
gn
go
gp
gq
gr
gs
gt
gu
gv
gw
gx
gy
ha
hb
hc
hd
he
hf
hg
hh
hi
hj
hk
hl
hm
hn
ho
hp
hq
hr
hs
ht
hu
hv
hw
hx
hy
ia
ib
ic
id
ie
if
ig
ih
ii
ij
ik
il
im
in
io
ip
iq
ir
is
it
iu
iv
iw
ix
iy
ja
jb
jc
jd
je
jf
jg
jh
ji
jj
jk
jl
jm
jn
jo
jp
jq
jr
js
jt
ju
jv
jw
jx
jy
ka
kb
kc
kd
ke
kf
kg
kh
ki
kj
kk
kl
km
kn
ko
kp
kq
kr
ks
kt
ku
kv
kw
kx
ky
la
lb
lc
ld
le
lf
lg
lh
li
lj
lk
ll
lm
ln
lo
lp
lq
lr
ls
lt
lu
lv
lw
lx
ly
ma
mb
mc
md
me
mf
mg
mh
mi
mj
mk
ml
mm
mn
mo
mp
mq
mr
ms
mt
mu
mv
mw
mx
my
na
nb
nc
nd
ne
nf
ng
nh
ni
nj
nk
nl
nm
nn
no
np
nq
nr
ns
nt
nu
nv
nw
nx
ny
oa
ob
oc
od
oe
of
og
oh
oi
oj
ok
ol
om
on
oo
op
oq
or
os
ot
ou
ov
ow
ox
oy
pa
pb
pc
pd
pe
pf
pg
ph
pi
pj
pk
pl
pm
pn
po
pp
pq
pr
ps
pt
pu
pv
pw
px
py
qa
qb
qc
qd
qe
qf
qg
qh
qi
qj
qk
ql
qm
qn
qo
qp
qq
qr
qs
qt
qu
qv
qw
qx
qy
ra
rb
rc
rd
re
rf
rg
rh
ri
rj
rk
rl
rm
rn
ro
rp
rq
rr
rs
rt
ru
rv
rw
rx
ry
sa
sb
sc
sd
se
sf
sg
sh
si
sj
sk
sl
sm
sn
so
sp
sq
sr
ss
st
su
sv
sw
sx
sy
ta
tb
tc
td
te
tf
tg
th
ti
tj
tk
tl
tm
tn
to
tp
tq
tr
ts
tt
tu
tv
tw
tx
ty
ua
ub
uc
ud
ue
uf
ug
uh
ui
uj
uk
ul
um
un
uo
up
uq
ur
us
ut
uu
uv
uw
ux
uy
va
vb
vc
vd
ve
vf
vg
vh
vi
vj
vk
vl
vm
vn
vo
vp
vq
vr
vs
vt
vu
vv
vw
vx
vy
wa
wb
wc
wd
we
wf
wg
wh
wi
wj
wk
wl
wm
wn
wo
wp
wq
wr
ws
wt
wu
wv
ww
wx
wy
xa
xb
xc
xd
xe
xf
xg
xh
xi
xj
xk
xl
xm
xn
xo
xp
xq
xr
xs
xt
xu
xv
xw
xx
xy
ya
yb
yc
yd
ye
yf
yg
yh
yi
yj
yk
yl
ym
yn
yo
yp
yq
yr
ys
yt
yu
yv
yw
yx
yy
za
zb
zc
zd
ze
zf
zg
zh
zi
zj
zk
zl
zm
zn
zo
zp
zq
zr
zs
zt
zu
zv
zw
zx
zy
zz
2
aa
bb

```
### 样例输出 #1
```
aw
wz
abababababababababab
babababababababababa
abababababababababab
babababababababababa
abababababababababab
babababababababababa
abababababababababab
babababababababababa
abababababababababab
babababababababababa
abababababababababab
babababababababababa
abababababababababab
babababababababababa
abababababababababab
babababababababababa
abababababababababab
babababababababababa
abababababababababab
babababababababababa

```
## 提示

Time limit: 2 s, Memory limit: 128 MB. 


## 题目翻译

## 题目描述

有一些有向字母对，构造一个尽量大（最大$20\times20$）的方阵，使得这个方阵中任意两个相邻字母对（从左到右或从上到下）都不是这些有向字母对中的一个。

## 输入格式

第一行一个整数$T$，表示数据组数。

每组数据第一行一个整数$n$($0 \le n \le 676$)，表示有向字母对数。

接下来$n$行，每行$2$个小写字母，表示一组有向字母对。

## 输出格式

对于每组数据，输出一个尽量大的方阵，不包含任何一个有向字母对（如果可以构造比$20\times20$规模更大的方阵，只需要$20\times20$规模就够了）。

如果有多组解，输出任意一组即可。


---

---
title: "[NWRRC 2017] Consonant Fencity"
layout: "post"
diff: 普及+/提高
pid: P7021
tag: ['2017', 'Special Judge', 'ICPC']
---
# [NWRRC 2017] Consonant Fencity
## 题目描述



There are two kinds of sounds in spoken languages: vowels and consonants. Vowel is a sound, produced with an open vocal tract; and consonant is pronounced in such a way that the breath is at least partly obstructed. For example, letters a and $o$ are used to express vowel sounds, while letters $b$ and $p$ are the consonants (e.g . bad, pot).

a vowel (e.g . silly) or as a consonant (e.g . yellow). The letter $w$ , usually used as a consonant (e.g . wet) could produce a vowel after another vowel (e.g . growth) in English, and in some languages (e.g . Welsh) it could be even the only vowel in a word.

In this task, we consider $y$ and $w$ as vowels, so there are seven vowels in English alphabet: a , $e , i , o , u , w$ and $y$ , all other letters are consonants.

Let's define the consonant fencity of a string as the number of pairs of consecutive letters in the string which both are consonants and have different cases (lowercase letter followed by uppercase or vice versa). For example, the consonant fencity of a string CoNsoNaNts is $2$ , the consonant fencity of a string dEsTrUcTiOn is $3$ and the consonant fencity of string StRenGtH is $5$ .

You will be given a string consisting of lowercase English letters. Your task is to change the case of some letters in such a way that all equal letters will be of the same case (that means, no letter can occur in resulting string as both lowercase and uppercase), and the consonant fencity of resulting string is maximal.


## 输入格式



The only line of the input contains non-empty original string consisting of no more than $10^{6}$ lowercase English letters.


## 输出格式



Output the only line: the input string changed to have maximum consonant fencity.


## 样例

### 样例输入 #1
```
consonants

```
### 样例输出 #1
```
CoNsoNaNts

```
### 样例输入 #2
```
destruction

```
### 样例输出 #2
```
dEsTrUcTiOn

```
### 样例输入 #3
```
strength

```
### 样例输出 #3
```
StRenGtH

```
## 提示

Time limit: 3 s, Memory limit: 512 MB. 


## 题目翻译

定义**非**辅音字母为 ``a`` ``e`` ``i`` ``o`` ``u`` ``w`` ``y``。

定义一个字符串的价值是连续两个大小写不同的辅音的个数。

给定一个小写字符串，试图改变若干个字母的大小写使得这个字符串的价值最大。

输出更改后的字符串。多解任意输出。



---

---
title: "[NWRRC 2017] Equal Numbers"
layout: "post"
diff: 普及+/提高
pid: P7023
tag: ['2017', 'ICPC']
---
# [NWRRC 2017] Equal Numbers
## 题目描述



You are given a list of $n$ integers $a_{1},$ . . . , $a_{n}.$ You can perform the following operation: choose some $a_{i}$ and multiply it by any positive integer.

Your task is to compute the minimum number of different integers that could be on the list after $k$ operations for all $0 \le k \le n$ .


## 输入格式



The first line of the input contains single integer $n (1 \le n \le 3·10^{5}).$ The second line of the input contains $n$ integers $a_{i} (1 \le a_{i} \le 10^{6}).$


## 输出格式



Output a single line that contains $n + 1$ integers. The i-th integer should be the minimum possible number of different integers in the list after $i − 1$ operations.


## 样例

### 样例输入 #1
```
6
3 4 1 2 1 2

```
### 样例输出 #1
```
4 4 3 3 2 2 1

```
## 提示

Time limit: 3 s, Memory limit: 512 MB. 


## 题目翻译

给定一个长度为 $n$ 的数列 $a_1,a_2,a_3,...,a_n$，每次操作，你可以让某个被选定的数乘上任意一个正整数。

现在。对于所有的 $k\in[0,n]$，求出经过 $k$ 次操作后数列里面不同的数的数量能够达到的最小值。

Translated by Eason_AC  
2020.11.15


---

---
title: "[NWRRC 2016] CodeCoder vs TopForces"
layout: "post"
diff: 普及+/提高
pid: P7033
tag: ['2016', 'ICPC']
---
# [NWRRC 2016] CodeCoder vs TopForces
## 题目描述



Competitive programming is very popular in Byteland. In fact, every Bytelandian citizen is registered at two programming sites -- CodeCoder and TopForces. Each site maintains its own proprietary rating system. Each citizen has a unique integer rating at each site that approximates their skill. Greater rating corresponds to better skill.

People of Byteland are naturally optimistic. Citizen A thinks that he has a chance to beat citizen B in a programming competition if there exists a sequence of Bytelandian citizens $A = P_{0}, P_{1},...,P_{k} = B$ for some $k \ge 1$ such that for each $i (0 \le i < k) , P_{i}$ has higher rating than $P_{i+1}$ at one or both sites.

Each Bytelandian citizen wants to know how many other citizens they can possibly beat in a programming competition.


## 输入格式



The first line of the input contains an integer $n$ -- the number of citizens $(1 \le n \le 100 000)$ . $The following n$ lines contain information about ratings. The i-th of them contains two integers $CC_{i} and TF_{i}$ -- ratings of the i-th citizen at CodeCoder and TopForces $(1 \le CC_{i}, TF_{i} \le 10^{6}).$ All the ratings at each site are distinct.


## 输出格式



For each citizen $i$ output an integer $b_{i}$ -- how many other citizens they can possibly beat in a programming competition. Each $b_{i}$ should be printed in a separate line, in the order the citizens are given in the input.


## 样例

### 样例输入 #1
```
4
2 3
3 2
1 1
4 5

```
### 样例输出 #1
```
2
2
0
3

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

- 有 $n$ 个人，每个人有两个能力值 $CC_i$ 和 $TF_i$。第 $i$ 个人能打败第 $j$ 个人当且仅当 $CC_i >CC_j$ 或 $TF_i>TF_j$。

- 强的关系具有传递性，也就是说 $i$ 比 $j$ 强，$j$ 比 $k$ 强，那么 $i$ 比 $k$ 强。 求出每个人最多可以打败的人的个数。

- $n \leq10^5$，$CC_i,TF_i \leq10^6$，数据保证 $CC_i$ 两两不同、$TT_i$ 两两不同。


---

---
title: "[NWRRC 2016] Java2016"
layout: "post"
diff: 普及+/提高
pid: P7040
tag: ['2016', 'Special Judge', 'ICPC']
---
# [NWRRC 2016] Java2016
## 题目描述



John likes to learn esoteric programming languages. Recently he discovered the probabilistic $\textit{programming language}$ Java2K. Built-in functions of Java2K have only a certain probability to do whatever you $\textit{intend them}$ to do.

The Java2K programming is very hard, so John designed a much simpler language for training: Java2016. $\textit{Built-in}$ operators of Java2016 are deterministic, while their operands are random. Each value in $\textit{Java2016 is}$ a positive integer in the range $0 \cdots 255$ , inclusive.

Java2016 supports six operators of three precedencies:

$$\begin{aligned}{\langle \mathrm{expression}\rangle}&\quad::=\quad{\langle \mathrm{expression}\rangle}\operatorname{`\texttt{min}\text'}{\langle \mathrm{sum}\rangle}\mid{\langle \mathrm{expression}\rangle}\operatorname{`\texttt{max}\text'}{\langle \mathrm{sum}\rangle}\mid {\langle \mathrm{sum}\rangle}\\{\langle \mathrm{sum}\rangle}&\quad::=\quad{\langle \mathrm{sum}\rangle}\operatorname{`\texttt{+}\text'}{\langle \mathrm{term}\rangle}\mid{\langle \mathrm{sum}\rangle}\operatorname{`\texttt{-}\text'}{\langle \mathrm{term}\rangle}\mid{\langle \mathrm{term}\rangle}\\{\langle \mathrm{term}\rangle}&\quad::=\quad{\langle \mathrm{term}\rangle}\operatorname{`\texttt{*}\text'}{\langle \mathrm{factor}\rangle}\mid {\langle \mathrm{term}\rangle}\operatorname{`\texttt{/}\text'}{\langle \mathrm{factor}\rangle}\mid {\langle \mathrm{factor}\rangle}\\{\langle \mathrm{factor}\rangle}&\quad::=\quad\operatorname{`\texttt{(}\text'}{\langle \mathrm{expression}\rangle}\operatorname{`\texttt{)}\text'}\mid `\texttt{?}\text'\mid {\langle \mathrm{macro}\rangle}\end{aligned}$$

Minimum $(\textit{`min'})$ and maximum $((\textit{`max'}))$ operators are defined as usual. Addition $(\text{`+'}),$ subtraction $(\text{`--'}) and$ multiplication $(\text{`}\times\text{'})$ are defined modulo $256$ . The result of the division $(\text{`}/\text{'})$ is rounded towards zero. $\textit{If}$ the divider is zero, the program crashes. The argument of the operator is a result of another $\textit{operator, evenly}$ distributed random value $(\text{`}?\text{'})$, or macro substitution.

For instance, the probability that $\text{`?/?/?'}$ is evaluated to zero is $98.2\%$, while the probability of $the crash$ is $0.8\%$.

The Java2016 program consists of zero or more macro definitions, followed by the resulting expression. $ Each$ macro definition has a form of

$$\begin{aligned}{\langle \mathrm{macrodef}\rangle}&\quad::=\quad{\langle \mathrm{macro}\rangle}\operatorname{`\texttt{=}\text'}{\langle \mathrm{expression}\rangle}\\{\langle \mathrm{macro}\rangle}&\quad::=\quad\operatorname{`\texttt{a}\text'}\ldots\operatorname{`\texttt{z}\text'}\end{aligned}$$


The macro should be defined before the first use. It may not be redefined. The macro is expanded to $its definitio_n$ on each use. For instance,

```plain
a = ? max ?
(a max $a) / a
```

is expanded to `((? max ?) max (? max ?)) / (? max ?)`.

John is going to add probabilistic constants to Java2016, so for each possible constant value he needs $a progra_m$ that successfully evaluates to this value with at least one-half probability. Crashes are $\textit{counted toward}$ failures.


## 输入格式



The input contains a single integer $c$ -- the target constant $(0 \le c \le 255)$ .


## 输出格式



Output a Java2016 program that successfully evaluates to constant $c$ with probability no less than $1/2$ . $ The$ total length of the program should not exceed $256$ characters (excluding spaces).


## 样例

### 样例输入 #1
```
0

```
### 样例输出 #1
```
? /?/ ?

```
### 样例输入 #2
```
1

```
### 样例输出 #2
```
a = ? max ?
(a max a) / a

```
## 提示

Time limit: 2 s, Memory limit: 512 MB. 


## 题目翻译

John 喜欢学习深奥的编程语言。最近，他发现了概率编程语言 Java2K。Java2K 的内置函数只有一定的概率去执行你想让它们做的事情。

Java2K 编程非常困难，因此 John 设计了一种简单得多的语言用于训练：Java2016。Java2016 的内置运算符是确定性的，而它们的操作数是随机的。Java2016 中的每个值都是 $0$ 到 $255$ (包含 $0$ 和 $255$) 中的整数。

Java2016 支持分为三个优先级的六种运算符：

$$\begin{aligned}{\langle \mathrm{expression}\rangle}&\quad::=\quad{\langle \mathrm{expression}\rangle}\operatorname{`\texttt{min}\text'}{\langle \mathrm{sum}\rangle}\mid{\langle \mathrm{expression}\rangle}\operatorname{`\texttt{max}\text'}{\langle \mathrm{sum}\rangle}\mid {\langle \mathrm{sum}\rangle}\\{\langle \mathrm{sum}\rangle}&\quad::=\quad{\langle \mathrm{sum}\rangle}\operatorname{`\texttt{+}\text'}{\langle \mathrm{term}\rangle}\mid{\langle \mathrm{sum}\rangle}\operatorname{`\texttt{-}\text'}{\langle \mathrm{term}\rangle}\mid{\langle \mathrm{term}\rangle}\\{\langle \mathrm{term}\rangle}&\quad::=\quad{\langle \mathrm{term}\rangle}\operatorname{`\texttt{*}\text'}{\langle \mathrm{factor}\rangle}\mid {\langle \mathrm{term}\rangle}\operatorname{`\texttt{/}\text'}{\langle \mathrm{factor}\rangle}\mid {\langle \mathrm{factor}\rangle}\\{\langle \mathrm{factor}\rangle}&\quad::=\quad\operatorname{`\texttt{(}\text'}{\langle \mathrm{expression}\rangle}\operatorname{`\texttt{)}\text'}\mid `\texttt{?}\text'\mid {\langle \mathrm{macro}\rangle}\end{aligned}$$

最小 ($\operatorname{`\texttt{min}\text'}$) 和最大 ($\operatorname{`\texttt{max}\text'}$) 运算符的定义和通常一样。加法 ($\operatorname{`\texttt{+}\text'}$)、减法 ($\operatorname{`\texttt{-}\text'}$) 和乘法 ($\operatorname{`\texttt{*}\text'}$) 是在模 $256$ 的意义下定义的。除法 ($`\operatorname{\texttt{/}\text'}$) 的结果向 $0$ 取整。如果除数是 $0$，程序就会崩溃。运算符的参数是另一个运算符的结果、均匀分布的随机数 ($\operatorname{`\texttt{?}\text'}$) 或宏代换的结果。

例如，$``\texttt{?/?/?}\text{''}$ 有 $98.2\%$ 的概率计算得到 $0$，而崩溃的概率为 $0.8\%$。

Java2016 程序由零个或多个宏定义以及随后的结果表达式组成。每条宏定义都形如

$$\begin{aligned}{\langle \mathrm{macrodef}\rangle}&\quad::=\quad{\langle \mathrm{macro}\rangle}\operatorname{`\texttt{=}\text'}{\langle \mathrm{expression}\rangle}\\{\langle \mathrm{macro}\rangle}&\quad::=\quad\operatorname{`\texttt{a}\text'}\ldots\operatorname{`\texttt{z}\text'}\end{aligned}$$

宏必须在第一次使用前被定义。宏不能被重复定义。宏在每次使用时都会被展开成它的定义。例如，

$$\texttt{a = ?  max ?}\\\texttt{(a max a) / a}$$

会被展开成 $``\texttt{((? max ?) max (? max ?)) / (? max ?)}\text{''}$。

John 将要把概率常量加入 Java2016，因此对每个可能的常量，他需要一个程序能以至少一半的概率成功计算出这个值。崩溃被算作失败。

#### 输入

输入包含一个整数 $c$ ($0\le c\le 255$)，表示目标常量。

#### 输出

输出一个 Java2016 程序，它需要能够以至少 $1/2$ 的概率成功计算出常量 $c$。程序的总长度不应超过 $256$ 个字符 (空格不计算在内)。


---

---
title: "[NWRRC 2015] Black and White"
layout: "post"
diff: 普及+/提高
pid: P7049
tag: ['2015', 'Special Judge', 'ICPC']
---
# [NWRRC 2015] Black and White
## 题目描述



The jury has a great artistic idea -- to create a rectangular panel out of a huge pile of black and white squares of the same size. The panel should have exactly $b 4-connected$ areas made of black tiles, and $w 4-connected$ areas made of white tiles.

Remember, a $4-connected$ area of some color is a maximal set of the panel tiles such that:

any two tiles of the area share the same color;

for any two tiles of the area there is a tile sequence connecting them, such that any two consecutive tiles of the sequence share a common side.

In addition to the artistic idea, the jury has already developed a program that produces design of the panel. But since this problem is about art, any new solution is extremely important for the jury.


## 输入格式



The only line of the input file contains two integers $b$ and $w$ -- number of black and white areas $(1 \le b , w \le 1000)$ .


## 输出格式



The first line of the output file should contain the picture sizes $r$ and $c$ -- the number of rows and columns $(1 \le r , c \le 100 000)$ . This line should be followed by $r$ lines of $c$ symbols each. Each symbol should be either $‘@'$ (for black tile) or $‘. '$ (for white one). There should be no more than $100 000$ tiles in the panel.


## 样例

### 样例输入 #1
```
2 3

```
### 样例输出 #1
```
6 7
@@@@@@@
@.@@@@@
@@...@@
@@@@@@@
.......
@@@@@@@

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

给定正整数 $b,w$，请你构造出一个黑白矩阵，使得矩阵内恰有 $b$ 个黑色连通块和 $w$ 个白色连通块。

输出的第一行包含两个整数 $r,c$，表示你构造出的矩阵的行数和列数。接下来是一个 $r\times c$ 的矩阵，表示你构造出的黑白矩阵。其中 ```@``` 代表黑色，```.``` 代表白色。

数据范围：$1\le b,w\le 1000$

你的矩阵应满足：$1\le r,c\le 100000$ 且 $r\times c\le100000$


---

---
title: "[NWRRC 2015] Journey to the “The World’s Start”"
layout: "post"
diff: 普及+/提高
pid: P7057
tag: ['2015', 'ICPC']
---
# [NWRRC 2015] Journey to the “The World’s Start”
## 题目描述



Jerry Prince is the fourth grade student and he goes to New-Lodnon to visit the most popular amusement park `The World's Start`.

An airport he arrives at is next to the first stop of the metro line. This line has $n$ stops and `The World's Start` is on the last of them. The metro of New-Lodnon is pretty fast so you may assume that you can get from a stop to the next one in just one minute.

Jerry needs a travel card to use the metro. Each travel card has a range $r$ and a price $p$ . With a travel card of range $r$ Jerry may travel no more than $r$ stops at once. Therefore, if Jerry enters metro at the stop $i$ he should exit on one of the stops from $i − r$ to $i + r$ inclusive. It takes $d_{i}$ minutes to exit and reenter metro at i-th stop. There is no time required to enter the first stop or exit the last one.

Jerry is not very rich but he has some spare time, so he decided to buy the cheapest travel card that will allow him to travel from the first metro stop to the last one in no more than $t$ minutes.


## 输入格式



The first line of the input file contains two integers $n$ and $t$ -- the number of stops and the maximum possible time $(2 \le n \le 50 000$ ; $n - 1 \le t \le 10^{9}).$

The second line contains $n - 1$ integers $p_{r}$ -- the prices of travel cards with range $r = 1$ . . . $n − 1 (1 \le p_{r} \le 100 000)$

The third line contains $n - 2$ integers $d_{i}$ -- the number of minutes required to reenter metro at stop $i = 2$ . . . $n - 1 (1 \le d_{i} \le 10^{5}).$


## 输出格式



Output a single integer $p$ -- the lowest possible price of one travel card that allows Jerry to travel from the first to the last stop in no more than $t$ minutes.


## 样例

### 样例输入 #1
```
4 4
1 2 3
1 4

```
### 样例输出 #1
```
2

```
## 提示

Time limit: 2 s, Memory limit: 256 MB. 


## 题目翻译

杰瑞在一条地铁线路上，这条线有$n$个站，世界的起点在最后一个，地铁很快，你可以在一分钟内从一个站点到达下一个站点。

杰瑞需要一张旅行卡才能乘地铁。每张旅行卡都有一个范围$r$和价格$p$。使用范围为$r$的旅行卡，他一次就只能最多旅行$r$站。因此，如果他在第二站进入地铁，他应该在$i−r$到$i+r$的其中一站下车。它需要$d[i]$在第一站下车或者重新进入地铁，不需要时间进入第一站或离开最后一站。

杰瑞不是很富有，但他有一些空闲时间，所以他决定买一张最便宜的旅行卡，这样他就可以在不超过$t$分钟的时间内从地铁的第一站坐到到最后一站。


---

---
title: "[NWRRC 2014] Joy of Flight"
layout: "post"
diff: 普及+/提高
pid: P7069
tag: ['2014', 'Special Judge', 'ICPC']
---
# [NWRRC 2014] Joy of Flight
## 题目描述

Jacob likes to play with his radio-controlled aircraft. The weather today is pretty windy and Jacob has to plan flight carefully. He has a weather forecast — the speed and direction of the wind for every second of the planned flight.

The plane may have airspeed up to $v_{\max}$ units per second in any direction. The wind blows away plane in the following way: if airspeed speed of the plane is $(v_x, v_y)$ and the wind speed is $(w_x, w_y)$, the plane moves by $(v_x+w_x, v_y+w_y)$ each second.

![](https://cdn.luogu.com.cn/upload/image_hosting/2uyb1zpd.png)

Jacob has a fuel for exactly $k$ seconds, and he wants to learn, whether the plane is able to fly from start to finish in this time. If it is possible he needs to know the flight plan: the position of the plane after every second of flight.
## 输入格式

The first line of the input file contains four integers $S_x, S_y, F_x, F_y$ — coordinates of start and finish ($−10 000 ≤ S_x, S_y, F_x, F_y ≤ 10 000$).

The second line contains three integers $n, k$ and $v_{\max}$ — the number of wind condition changes, duration of Jacob’s flight in seconds and maximum aircraft speed ($1 ≤ n, k, v_{\max} ≤ 10 000$).

The following $n$ lines contain the wind conditions description. The $i$-th of these lines contains integers $t_i, w_{x_i}$ and $w_{y_i}$ — starting at time $t_i$ the wind will blow by vector $(w_{x_i}, w_{y_i})$ each second ($0 = t_1 < ··· < t_i < t_{i+1} < ··· < k; \sqrt{w_{x_i}^2 + w_{y_i}^2} ≤ v_{\max}$).
## 输出格式

The first line must contain `Yes` if Jacob’s plane is able to fly from start to finish in k seconds, and `No` otherwise.

If it can to do that, the following $k$ lines must contain the flight plan. The $i$-th of these lines must contain two floating point numbers $x$ and $y$ — the coordinates of the position ($P_i$) of the plane after $i$-th second of the flight.

The plan is correct if for every $1 ≤ i ≤ k$ it is possible to fly in one second from $P_{i−1}$ to some point $Q_i$, such that distance between $Q_i$ and $P_i$ doesn’t exceed $10^{−5}$, where $P_0 = S$. Moreover the distance between $P_k$ and $F$ should not exceed $10^{-5}$ as well.
## 样例

### 样例输入 #1
```
1 1 7 4
2 3 10
0 1 2
2 2 0
```
### 样例输出 #1
```
Yes
3 2.5
5 2.5
7 4
```
## 提示

Time limit: 2 s, Memory limit: 256 MB.
## 题目翻译

## 简述

大意就是一架飞机要从起点飞到终点，飞机有最大空速，飞行最大时间，给出风速的变化和风如何影响飞机飞行，求出飞机是否能到达终点，如果能就输出飞机的位置变化。

## 题目描述

雅各布（Jacob）喜欢玩他的无线电摇制飞机。今天的风很大，雅各布必须小心地计划飞行。他有一个天气预报——飞行计划中每秒钟的风速和风向。

飞机每秒在任何方向的空速最大都可以达到 $v_{max}$ 。风吹动飞机的方式如下：如果飞机的空速是 $(v_x,v_y)$ 并且风速是 $(w_x,w_y)$ ，那么飞机每秒将移动 $(v_x+w_x,v_y+w_y)$ 。

![P7069-1](https://cdn.luogu.com.cn/upload/image_hosting/2uyb1zpd.png)

雅各布（Jacob）有一种刚好能使用$k$秒的燃料，他想知道，飞机是否能在这段时间内从起点飞到终点。如果可能的话，他需要知道飞行计划：每飞行一秒后飞机的位置。

## 输入格式

输入文件的第一行有四个整数 $S_x,S_y,F_x,F_y$ ，代表起始位置 $(-10000 \le S_x,S_y,F_x,F_y \le 10000)$ 。

第二行有三个整数 $n,k 和 v_{max}$ ——风况变化的次数，雅各布（Jacob）飞行持续的时间（以秒为单位）和飞机最大空速。

剩下的 $n$ 行是对风向的描述，第 $i$ 行有三个整数 $t_i,w_{xi} 和 w_{yi}$ ——从时间 $t_i$ 开始，风速为每秒 $(w_{xi},w_{yi})$ （一个向量） $(0=t_1< \cdots <t_i<t_{i+1}< \cdots <k; \sqrt{{w^2_{xi}}+{w^2_{yi}}} \le v_{max})$ 。

## 输出格式

如果 $k$ 秒内雅各布（Jacob）的飞机能从起点飞到终点则应输出 `Yes` ，否则输出 `No` 。

如果它能飞到，接下来的 $k$ 行必须包括飞行计划。第 $i$ 行必须包括两个浮点数 $x$ 和 $y$ （保留几位貌似没说）——飞行了第 $i$ 秒的平面位置 $(P_i)$ 。

如果对于每个 $1 \le i \le k$ 都能在一秒内从点 $P_{i-1}$ 飞到某个点 $Q_i$ ，使得 $Q_i$ 和 $P_i$ 间距离不超过 $10^{-5}$ ，其中 $P_0=S$ ，那么这个计划就是正确的。此外 $P_k$ 和 $F$ 间的距离也应不超过 $10^{-5}$ 。

## 说明/提示

时间限制： $2s$ ；内存限制： $256MB$ 

by XYY1411

2020/12/08


---

---
title: "[ICPC 2020 WF] Opportunity Cost"
layout: "post"
diff: 普及+/提高
pid: P8134
tag: ['2020', 'O2优化', 'ICPC']
---
# [ICPC 2020 WF] Opportunity Cost
## 题目背景

ICPC2020 WF G
## 题目描述

As with most types of products, buying a new phone can be difficult.
One of the main challenges is that there are a lot of different
aspects of the phone that you might care about, such as its price, its
performance, and how user-friendly the phone is.
Typically, there will be no single phone that is simultaneously the
best at all of these things: the cheapest phone, the most powerful
phone, and the most user-friendly phone will likely be different phones.

Thus when buying a phone, you are forced to make some sacrifices by
balancing the different aspects you care about against each other and
choosing the phone that achieves the best compromise (where "best"
of course depends on what your priorities happen to be).  One way of
measuring this sacrifice is known as the *opportunity cost*,
which (for the purposes of this problem) we define as follows.

Suppose that you have bought a phone with price $x$, performance $y$,
and user-friendliness $z$. For simplicity, we assume that these three
values are measured on a comparable numeric scale where higher is
better. If there are $n$ available phones, and the values
$(x_i,y_i,z_i)$ represent the (price, performance, user-friendliness)
of the $i^{\text{th}}$ phone, then the opportunity cost of your phone
is defined as

$$\max _{1 \leq i \leq n}\left(\max \left(x_{i}-x, 0\right)+\max \left(y_{i}-y, 0\right)+\max \left(z_{i}-z, 0\right)\right)$$


Write a program that, given the list of available phones, finds a
phone with the minimum opportunity cost.
## 输入格式

The first line of input contains an integer $n$ ($2 \leq n \leq
200\,000$), the number of phones considered. Following that are $n$ lines.
The $i^{\text{th}}$ of these lines contains three integers $x_i$, $y_i$, and $z_i$,
where $x_i$ is the price, $y_i$ is the performance, and $z_i$ is the
user-friendliness of the $i^{\text{th}}$ phone ($1 \leq x_i, y_i, z_i \leq
10^9$).
## 输出格式

Output a single line containing two integers: the smallest possible
opportunity cost and an integer between $1$ and $n$ indicating the
phone achieving that opportunity cost. If there are multiple such
phones, output the one with the smallest index.

## 样例

### 样例输入 #1
```
4
20 5 5
5 20 5
5 5 20
10 10 10
```
### 样例输出 #1
```
10 4

```
### 样例输入 #2
```
4
15 15 5
5 15 15
15 5 15
10 10 10
```
### 样例输出 #2
```
10 1
```
## 题目翻译

与大多数类型的产品一样，购买一部新手机可能很困难。其中一个主要困难是，你可能会关心手机的许多不同方面，比如价格、性能以及手机的用户友好程度（**本题中仅考虑这三种因素**）。通常情况下，不会有一款手机同时在所有这些方面都是最好的，也就是说，最便宜的手机、功能最强大的手机和用户最友好的手机可能是不同的手机。因此，在购买手机时，你不得不做出一些牺牲，平衡彼此关心的不同方面，并选择实现最佳折衷的手机（当然，“最佳”取决于你的优先级）。衡量这种牺牲的一种方法称为**机会成本**（为了解决这个问题），我们将其定义如下：

某商店里一共有 $n$ 部手机，其中第 $i$ 部手机的价格为 $x_i$，性能为 $y_i$，用户友好程度为 $z_i$。假设你购买了一个价格为 $x$，性能为 $y$，用户友好程度为 $z$ 的一台手机，那么购买这台手机的机会成本用如下公式表示：

$$\max\limits_{1\leqslant i\leqslant n}(\max(x_i-x,0)+\max(y_i-y,0)+\max(z_i-z,0))$$

现在，请求出所有 $n$ 部手机的机会成本的最小值，并找到机会成本最小的**编号最小**的手机的编号。

数据范围：

- $2\leqslant n\leqslant 2\times 10^5$。
- $1\leqslant x_i,y_i,z_i\leqslant 10^9$。

Translated by Eason_AC


---

---
title: "[ICPC 2022 Xi'an R] Find Maximum"
layout: "post"
diff: 普及+/提高
pid: P9362
tag: ['2022', 'O2优化', 'ICPC']
---
# [ICPC 2022 Xi'an R] Find Maximum
## 题目描述

We define a function $f(x)$ over all non-negative integer $x$ as follows:
$$
f(x) =
\begin{cases}
1 & (x = 0) \\
f(\frac{x}{3}) + 1 & (x > 0\land x\bmod3 = 0) \\
f(x - 1) + 1  & (x > 0\land x\bmod 3\neq 0)
\end{cases}
$$
Calculate $\max_{x = l} ^ r f(x)$.

You need to answer $T$ queries independently.
## 输入格式

The first line contains a single integer $T$ ($1\leq T\leq 10 ^ 4$).

Each of the next $T$ lines contains two integers $l$ and $r$ ($1\leq l\leq r\leq 10 ^ {18}$), representing a query.
## 输出格式

Output $T$ lines. The $i$-th line contains a single integer, representing the answer to the $i$-th query.
## 样例

### 样例输入 #1
```
10
1 2
1 3
1 4
1 5
2 3
2 4
2 5
3 4
3 5
4 5

```
### 样例输出 #1
```
3
3
4
5
3
4
5
4
5
5

```
## 提示

**Source**: The 2022 ICPC Asia Xi'an Regional Contest Problem E.

**Author**: MagicSpark.
## 题目翻译

### 题目描述

定义在所有非负整数 $x$ 上的函数 $f(x)$ 如下：

$$
f(x) =
\begin{cases}
1 & (x = 0) \\
f(\frac{x}{3}) + 1 & (x > 0\land x\bmod3 = 0) \\
f(x - 1) + 1  & (x > 0\land x\bmod 3\neq 0)
\end{cases}
$$

计算 $\max_{x = l} ^ r f(x)$。

共有 $T$ 组数据。

$1\leq T\leq 10 ^ 4$，$1\leq l\leq r\leq 10 ^ {18}$。

### 输入格式

第一行一个整数 $T$。

接下来 $T$ 行，每行两个整数 $l, r$ 表示一组询问。

### 输出格式

对于每组询问，输出一行一个整数表示答案。




---

---
title: "[ICPC 2022 Xi'an R] Perfect Word"
layout: "post"
diff: 普及+/提高
pid: P9364
tag: ['2022', 'O2优化', 'ICPC']
---
# [ICPC 2022 Xi'an R] Perfect Word
## 题目描述

You are given $n$ strings and required to find the length of the longest *perfect word*.

A string $t$ is called a *perfect word*, if and only if every non-empty substring of $t$ appears in the given strings.

A string $s$ is called a substring of $t$ if and only if it can be obtained by removing several (possibly zero) characters from the beginning or end of $t$.

## 输入格式

The first line contains a single integer $n$ ($1 \leq n \leq 10 ^ 5$).

Each of the next $n$ lines contains a string consisting of lowercase English letters.

It is guaranteed that the total length of the given strings is no more than $10 ^ 5$.

## 输出格式

Output an integer, representing the length of the longest perfect word.

## 样例

### 样例输入 #1
```
4
a
t
b
ab

```
### 样例输出 #1
```
2

```
## 提示

**Source**: The 2022 ICPC Asia Xi'an Regional Contest Problem G.

**Author**: MonkeyKing.
## 题目翻译

### 题目描述

给定 $n$ 个字符串，你需要找到最长的「完美单词」。

字符串 $t$ 称为「完美单词」，当且仅当它的所有非空子串都出现在给定的字符串中。

字符串 $s$ 称为 $t$ 的子串，当且仅当 $s$ 可由 $t$ 在开头和结尾分别删去零个或若干个字符得到。

$1\leq n\leq 10 ^ 5$，字符串仅由小写字母组成，且总长不超过 $10 ^ 5$。

### 输入格式

第一行一个整数 $n$。

接下来 $n$ 行，每行一个字符串。

### 输出格式

输出一行一个整数表示最长的「完美单词」的长度。




---

---
title: "[ICPC 2022 Xi'an R] Tree"
layout: "post"
diff: 普及+/提高
pid: P9369
tag: ['2022', 'O2优化', 'ICPC']
---
# [ICPC 2022 Xi'an R] Tree
## 题目描述

You are given a tree $T$ with $n$ nodes. The tree is rooted at $1$. Define $\mathrm{subtree}(u)$ as the set of nodes in the subtree of $u$.

Call a subset of nodes $S$ good if and only if $S$ satisfies at least one of the following contidions:

- For all $u, v\in S$ where $u\neq v$, either $u\in \mathrm{subtree}(v)$ or $v\in \mathrm{subtree}(u)$.
- For all $u, v\in S$ where $u\neq v$, both $u\notin \mathrm{subtree}(v)$ and $v\notin \mathrm{subtree}(u)$.

You need to partition all nodes of $T$ into several good subsets. Calculate the minimum number of subsets.

## 输入格式

The first line contains a single integer $Q$ ($1\leq Q\leq 10 ^ 5$), denoting the number of test cases.

For each test case, the first line contains an integer $n$ ($1\leq n\leq 10 ^ 6$). The next line contains $n - 1$ integers $p_2, p_3, \ldots, p_n$ ($1\leq p_i < i$), indicating that there is an edge between $p_i$ and $i$ for each $i=2,3,\ldots,n$.

It is guaranteed that the sum of $n$ over all test cases is no more than $10 ^ 6$.
## 输出格式

For each test case, output a single integer representing the answer.
## 样例

### 样例输入 #1
```
2
7
1 1 2 2 2 3
5
1 2 3 4

```
### 样例输出 #1
```
3
1

```
## 提示

**Source**: The 2022 ICPC Asia Xi'an Regional Contest Problem L.

**Author**: Alex_Wei.
## 题目翻译

### 题目描述

给定大小为 $n$ 的有根树 $T$，根节点为 $1$。定义 $\mathrm{subtree}(u)$ 表示结点 $u$ 的子树。

称集合 $S$ 是好的，当且仅当 $S$ 至少满足下列条件之一：

- 对于 $u, v\in S$ 且 $u\neq v$，$u\in \mathrm{subtree}(v)$ 或 $v\in \mathrm{subtree}(u)$。
- 对于 $u, v\in S$ 且 $u\neq v$，$u\notin \mathrm{subtree}(v)$ 且 $v\notin \mathrm{subtree}(u)$。

将 $T$ 划分为若干好的集合，求集合数量的最小值。

共有 $Q$ 组数据。

$1\leq Q\leq 10 ^ 5$，$1\leq n, \sum n\leq 10 ^ 6$，每个点的父亲编号 $1\leq p_i < i$。

### 输入格式

第一行一个整数 $Q$。

对于每组测试数据，第一行一个整数 $n$，第二行 $n - 1$ 个由空格隔开的整数 $p_2, p_3, \cdots, p_n$，表示每个点的父亲编号。

### 输出格式

对于每组测试数据，输出一行一个整数表示答案。


---

---
title: "[ICPC 2021 WF] Splitstream"
layout: "post"
diff: 普及+/提高
pid: P9448
tag: ['2021', 'ICPC']
---
# [ICPC 2021 WF] Splitstream
## 题目描述

A splitstream system is an acyclic network of nodes that processes finite sequences of numbers. There are two types of nodes (illustrated in Figure J.1):

- A *split* node takes a sequence of numbers as input and distributes them alternatingly to its two outputs. The first number goes to output $1$, the second to output $2$, the third to output $1$, the fourth to output $2$, and so on, in this order.</li>
- A *merge** node takes two sequences of numbers as input and merges them alternatingly to form its single output. The output contains the first number from input $1$, then the first from input $2$, then the second from input $1$, then the second from input $2$, and so on. If one of the input sequences is shorter than the other, then the remaining numbers from the longer sequence are simply transmitted without being merged after the shorter sequence has been exhausted.</li>

 ![](https://cdn.luogu.com.cn/upload/image_hosting/e0gr6wa3.png)
  
  Figure J.1: Illustration of how split and merge nodes work.
  
The overall network has one input, which is the sequence of positive integers $1, 2, 3, \ldots, m$. Any output of any node can be queried. A query will seek to identify the $k^{th}$ number in the sequence of numbers for a given output and a given $k$. Your task is to implement such queries efficiently.
## 输入格式

The first line of input contains three integers $m$, $n$, and $q$, where $m$ ($1 \leq m \leq 10^9$) is the length of the input sequence, $n$ ($1 \leq n \leq 10^4$) is the number of nodes, and $q$ ($1 \leq q \leq 10^3$) is the number of queries.

The next $n$ lines describe the network, one node per line. A split node has the format $\texttt{S} \ x \ y \ z$, where $x$, $y$ and $z$ identify its input, first output and second output, respectively. A merge node has the format $\texttt{M} \ x \ y \ z$, where $x$, $y$ and $z$ identify its first input, second input and output, respectively. Identifiers $x$, $y$ and $z$ are distinct positive integers. The overall input is identified by $1$, and the remaining input/output identifiers form a consecutive sequence beginning at $2$. Every input identifier except $1$ appears as exactly one output. Every output identifier appears as the input of at most one node.

Each of the next $q$ lines describes a query. Each query consists of two integers $x$ and $k$, where $x$ ($2 \leq x \leq 10^5$) is a valid output identifier and $k$ ($1 \leq k \leq 10^9$) is the index of the desired number in that sequence. Indexing in a sequence starts with $1$.
## 输出格式

For each query $x$ and $k$ output one line with the $k^{th}$ number in the output sequence identified by $x$, or $\texttt{none}$ if there is no element with that index number.
## 样例

### 样例输入 #1
```
200 2 2
S 1 2 3
M 3 2 4
4 99
4 100

```
### 样例输出 #1
```
100
99

```
### 样例输入 #2
```
100 3 6
S 1 4 2
S 2 3 5
M 3 4 6
6 48
6 49
6 50
6 51
6 52
5 25

```
### 样例输出 #2
```
47
98
49
51
53
100

```
### 样例输入 #3
```
2 3 3
S 1 2 3
S 3 4 5
M 5 2 6
3 1
5 1
6 2

```
### 样例输出 #3
```
2
none
none

```
## 题目翻译

### 题意
有一个有 $n$ 个节点的传输数字序列的网络，其中有两种节点：拆分节点和合并节点。拆分节点会将输入序列中的数字交替插入两个输出序列中，合并节点会交替将两个输入序列中的数字插入输出序列中。例如：

$\{1,2,3,4,5\}$ 拆分得 $\{1,3,5\}$ 和 $\{2,4\}$。

$\{2,4\}$ 和 $\{1,3,5\}$ 合并得 $\{2,1,4,3,5\}$。

在网络中，除 $1$ 号外每一个结点的每一个输入端都连接着另一个节点的输出端,$1$ 号节点的输入端为总输入端，每一个输出端不一定连接着另一个节点的输入端。每一个输出端都有着从 $2$ 开始的正整数编号。

将一个数字序列 $\{1,2,\cdots,m\}$ 从 $1$ 号节点的输入端输入网络，你需要求出编号为  $x$ 的输出端输出的序列中的第 $k$ 个数字。

### 输入格式
第一行三个整数 $n,m,q$。分别表示结点的个数、输入序列为 $\{1,2,\cdots,m\}$、查询的次数。

接下来 $n$ 行，每行一个字母开头，接着是三个整数 $x,y,z$。若字母为 $S$，则表示这是一个拆分节点，$x$ 是它的输入端所连接的输出端编号，$y,z$ 是它的两个输出端的编号；若字母为 $M$，则表示这是一个合并节点，$x,y$ 是它的两个输入端所连接的输出端的编号，$z$ 是它的输出端编号。

再接下来 $q$ 行，每行两个整数 $x,k$，意义如题意中所述。

### 输出格式
对于每一次询问，输出其对应的回答。若答案不存在，输出 `none`。


---

---
title: "[CERC2019] ABB"
layout: "post"
diff: 普及+/提高
pid: P9606
tag: ['字符串', '2019', '哈希 hashing', 'KMP 算法', 'Manacher 算法', 'ICPC']
---
# [CERC2019] ABB
## 题目背景

**题目译自 [CERC 2019](https://contest.felk.cvut.cz/19cerc/solved.html) 「[ABB](https://contest.felk.cvut.cz/19cerc/solved/abb.pdf)」**
## 题目描述

Fernando 受雇于滑铁卢大学，负责完成该大学不久前开始的一个开发项目。在校园外，该大学希望为重要的外国游客和合作者建造具有代表性的平房街。

目前，这条街只建了一部分，它从湖岸开始，一直延伸到森林尽头。Fernando 的任务是通过在森林尽头建造更多的平房来完成这条街。所有现有的平房都坐落在街道的一侧，新的平房应该建在同一侧。这些平房有各种各样的类型，漆成各种各样的颜色。

在 Fernando 看来，整条街的布局有点混乱。他担心增加新平房后，它会看起来更加混乱。所以他想通过为新平房选择合适的颜色来增加一些排列顺序。当项目完成时，平房的整个颜色序列将是对称的，也就是说，从街道的两端观察时，颜色序列是相同的。

在其他问题中，Fernando 想知道，在满足平房颜色限制的情况下，他最少需要用来建造和适当染色才能完成项目的新平房数量。

### 简要题意

求使给定小写字母字符串成为回文串需在字符串末尾加入字母的最少数量。
## 输入格式

第一行包含一个整数 $N\ (1\le N\le 4\times 10^5)$，代表街道上现有平房的数量。

第二行包含一个由 $N$ 个小写字母（从 `a` 到 `z`）组成的字符串，代表从湖岸开始的街道现有的平房颜色顺序，其中不同的字母表示不同的颜色。
## 输出格式

输出一个整数，代表满足 Fernando 要求的新平房的最少数量。
## 样例

### 样例输入 #1
```
3
abb

```
### 样例输出 #1
```
1

```
### 样例输入 #2
```
12
recakjenecep

```
### 样例输出 #2
```
11

```
### 样例输入 #3
```
15
murderforajarof

```
### 样例输出 #3
```
6

```


---

---
title: "[ICPC 2020 Nanjing R] Fireworks"
layout: "post"
diff: 普及+/提高
pid: P9627
tag: ['2020', 'Special Judge', 'O2优化', 'ICPC', '南京']
---
# [ICPC 2020 Nanjing R] Fireworks
## 题目描述

Kotori is practicing making fireworks for the upcoming hanabi taikai$^1$. It takes her $n$ minutes to make a single firework, and as she is not really proficient in making fireworks, each firework only has a probability of $p \times 10^{-4}$ to be perfect.

After she finishes making a firework, she can just start making the next firework, or take $m$ minutes to light all the remaining fireworks finished before. If there is at least one perfect firework among the lit ones, she will be happy and go to rest. Otherwise, she will continue practicing. Can you tell her the minimum expected practicing time before she goes to rest if she takes the optimal strategy?

Notice that no matter how many fireworks remain, it always takes $m$ minutes to light them all.

$^1$ Hanabi taikai: Romaji of the Japanese word ``花火大會``, which means the firework... err... party?
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ ($1 \le T \le 10^4$) indicating the number of test cases. For each test case:

The first and only line contains three integers $n$, $m$ and $p$ ($1 \le n, m \le 10^9$, $1 \le p \le 10^4$).
## 输出格式

For each test case, output one line containing one number indicating the minimum expected practicing time.

Your answer will be considered correct if and only if the absolute or relative error does not exceed $10^{-4}$.
## 样例

### 样例输入 #1
```
3
1 1 5000
1 1 1
1 2 10000
```
### 样例输出 #1
```
4.0000000000
10141.5852891136
3.0000000000
```
## 题目翻译

Kotori 正在制作烟花。她制作一支烟花需要 $n$ 分钟，每支烟花有 $p\times 10 ^ {-4}$ 的概率是完美的。

当 Kotori 制作好一支烟花时，她可以选择继续制作，也可以选择用 $m$ 分钟点燃所有烟花。如果其中有完美的烟花，那么她会很开心，并停下来休息，否则她会继续制作烟花。你能告诉她在最优策略下，最少期望多长时间才能停下来休息吗？

注意，无论已经制作好了多少支烟花，Kotori 都需要 $m$ 分钟将它们点燃。

多组数据，$1\leq T, p\leq 10 ^ 4$，$1\leq n, m\leq 10 ^ 9$。要求相对误差或绝对误差不超过 $10 ^ {-4}$。


---

---
title: "[ICPC 2021 Macao R] Sandpile on Clique"
layout: "post"
diff: 普及+/提高
pid: P9661
tag: ['2021', 'O2优化', 'ICPC', 'Ad-hoc', '澳门']
---
# [ICPC 2021 Macao R] Sandpile on Clique
## 题目描述

The $\textit{Abelian Sandpile Model}$ is a famous dynamical system displaying self-organized criticality. It has been studied for decades since it was introduced by Per Bak, Chao Tang and Kurt Wiesenfeld in a 1987 paper. The sandpile prediction is of wide interest in physics,
computer science, and mathematics, both for its beautiful algebraic structure and for its relevance to applications like load balancing and derandomization of models like internal diffusion-limited aggregation. The sandpile model is related to many other models and physical phenomena, like the rotor-routing model, avalanche models.

In the sandpile model, we are given an undirected graph $G$ whose vertices are indexed from $1$ to $n$. We're also given $n$ integers $a_1, a_2, \cdots, a_n$ where $a_i$ indicates that there are $a_i$ chips placed on vertex $i$ initially. Each turn we will pick an arbitrary vertex $v$ such that the number of chips on $v$ is not smaller than the number of edges connecting $v$, denoted as $d_v$. For each neighbor of $v$, it will receive one chip from $v$. Therefore, $v$ will lost $d_v$ chips. This process is called firing or toppling. Firing will keep happening until no vertex $v$ has at least $d_v$ chips.

It can be proven that the order of firing doesn't affect the result. Meanwhile, it is also possible that the firing will never terminate. This instance is described as ``recurrent``. Now you are given a clique and the initial number of chips. Determine whether this instance is a recurrent one. If not, please output the final number of chips for each node respectively.

A clique (also called a complete graph) is a graph where every two vertices are connected with an edge.
## 输入格式

There is only one test case in each test file.

The first line of the input contains an integer $n$ ($2 \leq n \leq 5 \times 10^5$) indicating the size of the clique. 

The second line contains $n$ integers $a_1, a_2, \cdots, a_n$ ($0 \leq a_i \leq 10^9$) where $a_i$ indicates the initial number of chips placed on vertex $i$.

## 输出格式

Output one line. If the given sandpile instance will terminate, output $n$ integers separated by a space where the $i$-th integer indicates the final number of chips on the $i$-th vertex. Otherwise output ``Recurrent`` (without quotes) instead.

Please, DO NOT output extra spaces at the end of each line or your solution may be considered incorrect!
## 样例

### 样例输入 #1
```
5
5 0 3 0 3
```
### 样例输出 #1
```
3 3 1 3 1
```
### 样例输入 #2
```
2
1 0
```
### 样例输出 #2
```
Recurrent
```
## 提示

For the first sample test case:

- We can only select vertex $1$ at the beginning. The number of chips becomes $\{1, 1, 4, 1, 4\}$.
- We can now select vertex $3$ or $5$ because both of them have at least $4$ chips. We select vertex $3$ and the number of chips becomes $\{2, 2, 0, 2, 5\}$. Selecting vertex $5$ will lead to the same result.
- We now select vertex $5$. The number of chips becomes $\{3, 3, 1, 3, 1\}$. There is no vertex with at least $4$ chips so the firing terminates.

For the second sample test case, we can select vertex $1$ and $2$ repeatedly. The firing never terminates.
## 题目翻译

**【题目描述】**

阿贝尔沙堆模型（Abelian Sandpile Model）是一个著名的显示自组织临界性的动力学系统。自从它由 Per Bak、Chao Tang 和 Kurt Wiesenfeld 在 1987 年的一篇论文中引入以来，它已经被研究了数十年。沙堆模型的预测引起了物理学、计算机科学和数学的广泛关注，这不仅是因为它美丽的代数结构，还因为它与负载平衡和内部扩散有关的模型的应用，如去随机化。沙堆模型与许多其他模型和物理现象相关，如转子路由模型、雪崩模型。

在沙堆模型中，给定一个顶点编号从 $1$ 到 $n$ 的无向图 $G$。我们还给出了 $n$ 个整数 $a_1, a_2, \cdots, a_n$，其中 $a_i$ 表示初始时放置在顶点 $i$ 上的筹码数量。每个回合，我们将选择一个任意的顶点 $v$，使得 $v$ 上的筹码数量不小于与 $v$ 相连的边数，记为 $d_v$。对于 $v$ 的每个邻居，它将从 $v$ 接收一枚筹码。因此，$v$ 将失去 $d_v$ 枚筹码。这个过程被称为 ``firing`` 或 ``toppling``。直到没有顶点 $v$ 至少有 $d_v$ 枚筹码时，firing 才会停止。

可以证明，firing 的顺序不会影响结果。同时，也可能 firing 永远不会终止。这种情况被描述为“recurrent”。现在给定一个团和初始筹码数量，请确定这个实例是否是一个 recurrent 实例。如果不是，请分别输出每个节点的最终筹码数量。

团（也称为完全图）是一个图，其中任意两个顶点都有边相连。

**【输入格式】**

每个测试文件中只有一个测试用例。

输入的第一行包含一个整数 $n$（$2 \leq n \leq 5 \times 10^5$），表示团的大小。

第二行包含 $n$ 个整数 $a_1, a_2, \cdots, a_n$（$0 \leq a_i \leq 10^9$），其中 $a_i$ 表示放置在顶点 $i$ 上的初始筹码数量。

**【输出格式】**

输出一行。如果给定的沙堆实例将终止，则输出由空格分隔的 $n$ 个整数，其中第 $i$ 个整数表示第 $i$ 个顶点上的最终筹码数量。否则输出 ``Recurrent``（不包括引号）。

请不要在每行末尾输出额外的空格，否则您的解决方案可能被认为是错误的！

**【样例解释】**

对于第一个样例测试用例：

- 我们只能在开始时选择顶点 $1$。筹码数量变为 $\{1, 1, 4, 1, 4\}$。
- 现在我们可以选择顶点 $3$ 或 $5$，因为它们都至少有 $4$ 枚筹码。我们选择顶点 $3$，筹码数量变为 $\{2, 2, 0, 2, 5\}$。选择顶点 $5$ 会得到相同的结果。
- 现在我们选择顶点 $5$。筹码数量变为 $\{3, 3, 1, 3, 1\}$。没有顶点至少有 $4$ 枚筹码，因此 firing 终止。

对于第二个样例测试用例，我们可以重复选择顶点 $1$ 和 $2$。firing 永远不会终止。

翻译来自于：[ChatGPT](https://chatgpt.com/)


---

---
title: "[ICPC 2022 Jinan R] Tower"
layout: "post"
diff: 普及+/提高
pid: P9667
tag: ['2022', 'O2优化', '枚举', 'ICPC', '济南']
---
# [ICPC 2022 Jinan R] Tower
## 题目描述

Prof. Pang built $n$ block towers with different heights. The $i$-th tower has height $a_i$.

Prof. Shou doesn't like these towers because of their arbitrary heights. He decides to $\textbf{first remove exactly \textit{m} of them}$, and then perform some (or none) of the following operations: 

- Choose a tower and increase its height $a_i$ by $1$. 
- Choose a tower and decrease its height $a_i$ by $1$.
- Choose a tower and divide its height $a_i$ by $2$. If the new height is not an integer, it is rounded down. 

Prof. Shou can never choose a removed tower. If after an operation, the height of a tower will become $0$, that operation is not allowed. Under these constraints, Prof. Shou can perform an arbitrary number of operations in arbitrary order. 

Prof. Shou would like all the towers that are not removed to have the same heights. Please calculate the minimum number of operations to achieve this.
## 输入格式

The first line contains one integer $T~(1\le T \le 10)$, the number of test cases.

For each test case, the first line contains two integers $n, m~(1\le n\le 500, 0\le m <n)$, the number of towers, and the number of towers Prof. Shou should delete before performing the operations.

The next line contains $n$ integers $a_1,\ldots, a_n~(1\le a_i\le 10^9)$, the initial heights of the towers.
## 输出格式

For each test case, output the minimum number of operations in one line.
## 样例

### 样例输入 #1
```
3
2 0
2 6
5 0
1 2 3 4 5
5 3
1 2 3 4 5
```
### 样例输出 #1
```
2
4
1
```
## 题目翻译

### 题目描述
庞教授搭了 $n$ 座不同高度的塔。第 $i$ 座塔的高度是 $a _ {i}$。

寿教授不喜欢这些参差不齐的塔。他决定**先去掉它们中的 $m$ 座**，然后执行以下操作中的一些（或不执行）：
- 选择一座塔并增加它 $1$ 个单位高度。
- 选择一座塔并减少它 $1$ 个单位高度。
- 选择一座塔并把它的高度 $a _ {i}$ 除以 $2$，如果它不是整数的话，向下取整。

寿教授永远不会选择被拆除的塔。如果操作后，塔的高度变为 $0$，则不允许操作。在这些约束条件下，寿教授可以按任意顺序执行任意数量的运算。

寿教授希望所有没有被拆除的塔都有相同的高度 $a _ {i}$。请计算实现此目标的最小操作次数。
### 输入格式
第一行是一个整数 $T(1\leqslant$ $T$ $\leqslant$ $10)$,表示有 $T$ 组数据。

对于每组测试数据，第一行包括两个整数 $n,m (1\leqslant$ $n$ $\leqslant$ $500$$,$$0$ $\leqslant$ $m$ $\leqslant$ $n$$)$，表示塔的数量以及寿教授在执行操作之前应该删除的塔的数量。

下一行包括 $n$ 个整数 $a _ {1},\dots,a _ {n} (1\leqslant$ $a _ {i}$ $\leqslant$ $10^9)$，表示塔的最初高度。
### 输出格式
对于每组测试数据，在一行中输出最小操作数。


---

---
title: "[ICPC 2022 Jinan R] Frozen Scoreboard"
layout: "post"
diff: 普及+/提高
pid: P9670
tag: ['2022', 'Special Judge', 'O2优化', 'ICPC', '济南']
---
# [ICPC 2022 Jinan R] Frozen Scoreboard
## 题目描述

There was an ICPC contest two thousand years ago in the Qin dynasty. There were $m$ problems and $n$ teams in the contest. We only know how many problems each team solved and how much total time they used from the historical records. These are called the $\textbf{final result}$s of the teams. We don't know which problems they solved or their submission times.

Recently, we seem to had a discovery. We found the $\textbf{frozen scoreboard}$ of the teams. From the frozen scoreboard of a team, we know their submissions during the whole contest, but we don't know the verdicts of the submissions in the last hour. And some people found that for some teams, their frozen scoreboards may contradict their final results in the historical records.

Given the final results and the frozen scoreboards of the teams, please construct a $\textbf{final scoreboard}$ for each team that is consistent with both its final result and its frozen scoreboard.

From the submissions during the contest, we can calculate the final scoreboard and the final result as follows:

For a fixed team $i$, its $\textbf{final scoreboard}$ is an array of $m$ elements where the $j$-th element shows some information about team $i$'s submissions on problem $j$. 

- If team $i$ didn't submit to problem $j$, the cell should be a single character ``.`` (without quotes). 

- If team $i$ submitted $x$ times to problem $j$ and none of the submissions was accepted, the cell should contain $-\ x$. 

- Otherwise, consider all submissions from team $i$ to problem $j$. Each submission has a submission time. Suppose the earliest accepted submission is the $x$-th one. Then the cell should contain $+\ x/y$ where $y~(0\le y\le 299)$ is the submission time of the $x$-th submission. $y$ is an integer representing the submission time in minutes.

Note that in the final scoreboard, we don't care about submissions after the first accepted one. It is possible that two or more submissions happened in the same minute.

The $\textbf{final result}$ of a team is computed from its $\textbf{final scoreboard}$. For each team, we can calculate the number of problems it solved. This number is equal to the number of ``+`` in the team's final scoreboard.

We can also calculate its total time. If team $i$ solved problem $j$ in the $y$-th minute after $x-1$ unaccepted submissions (in other words, the $j$-th cell of its final scoreboard is $+\ x/y$), problem $j$ contributes $20(x-1)+y$ time to team $i$. If team $i$ didn't solve problem $j$, problem $j$ contributes $0$ time to team $i$, no matter team $i$ submitted to problem $j$ or not. The total time of team $i$ is the sum of contributions of each problem.

The rules for the $\textbf{frozen scoreboard}$ will be introduced in the input section. We will distinguish submissions in the final hour and other submissions. A submission was in the final hour if its submission time is between $240$ and $299$.
## 输入格式

The first line contains two integers $n, m~(1\le n\le 1000, 1\le m\le 13)$, the number of teams in the contest, and the number of problems in the contest.

Then there are $n$ blocks describing the $\textbf{final result}$ and the $\textbf{frozen scoreboard}$ of each team.

The $i$-th block represents team $i$. In the $i$-th block, the first line contains two integers $a_i, b_i~(0\le a_i\le m, 0\le b_i\le 10^5)$, the number of problems team $i$ solved $\textbf{during the whole contest}$ and the total time of team $i$ for solving the $a_i$ problems. These two numbers represent the final result of the contest. The next $m$ lines describe the status of team $i$ in the frozen scoreboard. For each $1\le j\le m$, 

- If the $j$-th line is $+\ x/y$ $(1\le x\le 100, 0\le y\le 239)$, team $i$ solved problem $j$ at time $y$ and the accepted solution is their $x$-th submission on problem $j$.
- If the $j$-th line is $?\ x\ y$ $(1\leq x \leq y \leq 100)$, team $i$ didn't solve the problem $j$ in the first four hours. Team $i$ submitted problem $j$ for $y$ times in which $x$ submissions are in the last hour. Note that submissions made in the last hour after the accepted one will count in the $\textbf{frozen scoreboard}$, but not in the $\textbf{final scoreboard}$.
- If the $j$-th line is $-\ x$, team $i$ didn't solve the problem $j$ in the first four hours. Team $i$ submitted problem $j$ for $x~(1\le x\le 100)$ times before the last hour and did not submit problem $j$ in the last hour.
- If the $j$-th line is a single character ``.`` (without quotes), team $i$ didn't submit problem $j$ at all.
## 输出格式

For each team $i$, if its final result contradicts its frozen scoreboard, output $\texttt{No}$ in one line. Otherwise, output $\texttt{Yes}$ in the first line and then output $m$ lines, describing a final scoreboard that is consistent with both the final result and the frozen scoreboard of team $i$. The $j$-th line should contain 

- $+\ x/y$ $(1\le x \le 100, 0\le y \le 299)$, if the $x$-th submission from team $i$ to problem $j$ is accepted and is in the $y$-th minute of the contest. All submissions from team $i$ to team $j$ before the $x$-th one was not accepted. Please don't output extra spaces before and after slash ``/``. 
- $-\ x$ $(1\le x\le 100)$, if team $i$ submitted to problem $j$ for $x$ times and none of the submissions was accepted.
- $.$ if team $i$ didn't submit to problem $j$ at all. 

If there are multiple solutions, output any.

$\textbf{Please note that in the input and the output, there is always a space following each ?, +, and -.}$
## 样例

### 样例输入 #1
```
1 13
7 951
+ 1/6
? 3 4
+ 4/183
- 2
+ 3/217
.
.
.
+ 2/29
+ 1/91
.
+ 1/22
.
```
### 样例输出 #1
```
Yes
+ 1/6
+ 2/263
+ 4/183
- 2
+ 3/217
.
.
.
+ 2/29
+ 1/91
.
+ 1/22
.
```
### 样例输入 #2
```
6 2
1 100
.
? 3 4
2 100
+ 1/1
+ 1/2
0 0
- 5
- 6
2 480
? 100 100
? 100 100
2 480
? 99 100
? 100 100
1 2000
? 100 100
? 100 100
```
### 样例输出 #2
```
No
No
Yes
- 5
- 6
Yes
+ 1/240
+ 1/240
No
Yes
+ 87/280
- 100
```
## 提示

Here is an example of the frozen scoreboard in the first sample.

![](https://cdn.luogu.com.cn/upload/image_hosting/jw4c3965.png)
## 题目翻译

### 题目描述

2000 年以前的秦朝，曾举办过一次 ICPC 比赛。比赛中有 $m$ 道题，$n$ 个团队。我们知道每个队完成了多少道题以及其历史记录的总用时。这些称作该团队的结果，但是我们不知道他们每道题是否完成、用时多久。

最近，我们发现了每个队**冻结的计分板**。从该计分板上，我们可以看到每个队在比赛中的提交情况，但是不知道在最后一小时内提交的判分。一些人发现，对于一些队来说，他们冻结的计分板可能与他们在历史记录中的最终成绩相矛盾。

请根据最终得分和冻结的计分板，为各队创建一个与其最终结果和冻结的计分板一致的最终计分板。

按照以下规则来计算计分板和总分：

对于给定的队伍 $i$，它**最终的计分板**是一个 $m$ 元数组，其中第 $j$ 个元素给出队伍 $i$ 在第 $j$ 题上的提交信息。

- 如果队伍 $i$ 没有提交问题 $j$，输出 ```.```。

- 如果队伍 $i$ 对问题 $j$ 提交了 $x$ 次但均未通过，输出 $-x$。

- 否则，考虑队伍 $i$ 在问题 $j$ 的所有评测结果。每次提交都有一个提交时间，设第一个通过的评测是第 $x$ 次评测，在第 $y$ 分钟时提交。输出 $+x/y$，其中 $0\leq y\leq299$。

在最终计分板上，只考虑第一次通过的提交。同一分钟内可能有多次提交。

一个队伍的最终得分是该队伍完成了多少道题，即该队最终计分板上 ```+``` 的个数。

一个队伍总用时按如下方式计算。如果队伍 $i$ 在第 $y$ 分钟完成了第 $j$ 道题，在完成前有 $x-1$ 次失败的提交（即最终计分板上第 $j$ 个问题的数为 $+x/y$），该问题的用时记为 $20(x-1)+y$。 如果队伍 $i$ 没有完成第 $j$ 道题，该问题的用时记为 $0$，无论是否提交过。队伍 $i$ 的总时间是每道题用时的总和。

### 输入格式

第一行包括两个整数 $n,m\;(1\leq n\leq1000,1\leq m\leq13)$，为队伍个数和题目个数。

接下来 $n$ 组，描述每个队伍的最终得分和冻结的计分板。

第 $i$ 组表示队伍 $i$。每一组中，第一行包括两个整数 $a_i,b_i\;(0\leq a_i\leq m,0\leq b_i\leq10^5)$，为队伍 $i$ 在**整场比赛中**完成的题目个数和每道题的用时。这两个数字是比赛的最终结果。

接下来 $m$ 行，描述队伍 $i$ 在计分板上的内容。对于任意 $1\leq j\leq m$，

- 如果第 $j$ 行是 $+\,x/y\;(1\leq x\leq100,0\leq y\leq239)$，表示队伍 $i$ 在第 $y$ 分钟，第 $x$ 次提交时通过了题 $j$。

- 如果第 $j$ 行是 $?\,x\,y\;(1\leq x\leq y\leq100)$，表示队伍 $i$ 没有在前四个小时中作出题 $j$。这个队伍提交了 $y$ 次，其中 $x$ 次在最后一小时内。最后一小时内且通过该题的提交记录会在**冻结的计分板**上显示，但不会在**最终计分板**上显示。

- 如果第 $j$ 行是 $-x$，表示队伍 $i$ 没有在前四小时内作出题 $j$。这个队伍在最后一个小时前提交了 $x\,(1\leq x\leq100)$ 次，且没有在最后一小时内做出题 $j$。

- 如果第 $j$ 行是一个单一的字符 ```.```，表示队伍 $i$ 没有提交过题 $j$。

### 输出格式

对于每个队伍 $i$，如果最终结果和冻结的计分板相矛盾，输出一行 $\texttt{No}$。否则，第一行输出 $\texttt{Yes}$，接下来 $m$ 行，描述一种队伍 $i$ 可能的计分板，满足最终结果和冻结的计分板。其中，第 $j$ 行应该包括：

- $+\,x/y\,(1\leq x\leq100,0\leq y\leq299)$，如果队伍 $i$ 在第 $x$ 次提交，第 $y$ 分钟完成了题 $j$，在这之前没有队伍通过这道题。不要在字符 ```/``` 前后输出多余的空格。

- $-x\,(1\leq x\leq100)$，如果队伍 $i$ 提交了 $x$ 次题 $j$，且均未通过。

- ```.```，如果队伍 $i$ 没有提交题 $j$。

如果有多种可能的答案，任意输出一种即可。

**请注意，在输入和输出中，```?,+,-``` 后总有一个空格。**


---

---
title: "[EC Final 2022] Chase Game 2"
layout: "post"
diff: 普及+/提高
pid: P9725
tag: ['图论', '2022', 'O2优化', 'ICPC']
---
# [EC Final 2022] Chase Game 2
## 题目描述

Prof. Pang and Prof. Shou like playing a chase game.

The game map consists of $n$ rooms and $n-1$ bi-directional channels. The game map is connected. That means, the map forms a tree.

At first, Prof. Pang is in room $u$, while Prof. Shou is in room $v$ ($u\neq v$). Prof. Pang and Prof. Shou take turns to play, and Prof. Shou goes first. In one's turn, the player knows his own position and the other player's position and can decide either to stay in the current room or to move to another room which is connected with the current room directly by a channel. When Prof. Pang and Prof. Shou are in the same room, Prof. Shou is caught by Prof. Pang. 

Prof. Pang and Prof. Shou are smart enough. Prof. Pang wants to catch Prof. Shou in a finite number of turns. Prof. Shou does not want to be caught by Prof. Pang in any finite number of turns. 

Prof. Shou gets tired of being caught every time and finds Prof. Fei for help. Prof. Shou asks Prof. Fei to add some channels so that Prof. Pang cannot catch him in finite number of turns for any pair of initial rooms $(u,v)$. Prof. Fei is lazy, so he hopes to add as few channels as possible. If no matter how to add the channels there is always a pair of rooms $(u,v)$ such that Prof. Pang can catch Prof. Shou, output $-1$.
## 输入格式

The first line contains a single integer $T$ ($1\le T\le 10^4$) denoting the number of test cases. 

For each test case, the first line contains a single integer $n$ ($2\le n\le 10^5$) denoting the number of rooms.

For the next $n-1$ lines, each line contains two integers $u$ and $v$ ($1\le u, v\le n$) denoting a channel connecting room $u$ and room $v$.

It is guaranteed that the sum of $n$ over all test cases does not exceed $2\times 10^5$, and the rooms and channels always form a tree.
## 输出格式

For each test case, print a number denoting the smallest number of added channels, or just print $-1$.
## 样例

### 样例输入 #1
```
4
2
1 2
4
1 2
2 3
3 4
4
1 2
2 3
2 4
5
1 2
2 3
3 4
3 5

```
### 样例输出 #1
```
-1
1
-1
2

```
## 题目翻译

**【题目描述】**

庞教授和寿教授喜欢玩追逐游戏。

游戏地图由 $n$ 个房间和 $n-1$ 条双向通道组成。游戏地图是连通的。这意味着地图形成一棵树。

一开始，庞教授在房间 $u$，而寿教授在房间 $v$（$u\neq v$）。庞教授和寿教授轮流玩游戏，寿教授先开始。在自己的回合中，玩家知道自己所在的位置和另一个玩家的位置，可以决定留在当前房间或者移动到与当前房间直接通过通道相连的另一个房间。当庞教授和寿教授在同一个房间时，寿教授被庞教授抓住。

庞教授和寿教授足够聪明。庞教授希望在有限的回合内抓住寿教授。寿教授不希望在任何有限的回合内被庞教授抓住。

寿教授厌倦了每次都被抓住，找到了费教授寻求帮助。寿教授请求费教授添加一些通道，使得无论初始房间对 $(u,v)$ 如何，庞教授都无法在有限的回合内抓住他。费教授很懒，所以他希望尽可能少地添加通道。如果无论如何添加通道，总是存在一对房间 $(u,v)$，使得庞教授能够抓住寿教授，输出 $-1$。

**【输入格式】**

第一行包含一个整数 $T$ ($1\le T\le 10^4$)，表示测试用例的数量。

对于每个测试用例，第一行包含一个整数 $n$ ($2\le n\le 10^5$)，表示房间的数量。

接下来的 $n-1$ 行，每行包含两个整数 $u$ 和 $v$ ($1\le u, v\le n$)，表示连接房间 $u$ 和房间 $v$ 的通道。

保证所有测试用例中 $n$ 的总和不超过 $2\times 10^5$，并且房间和通道始终构成一棵树。

对于每个测试用例，输出一个数字表示添加的通道的最小数量，或者只输出 $-1$。

**【输出格式】**

输出一行整数，表示答案。

翻译来自于：[ChatGPT](https://chatgpt.com/)


---

---
title: "[NERC 2018] Easy Chess"
layout: "post"
diff: 普及+/提高
pid: P9795
tag: ['2018', 'Special Judge', 'ICPC']
---
# [NERC 2018] Easy Chess
## 题目背景

翻译自 [NERC 2018](https://neerc.ifmo.ru/archive/2018/neerc-2018-statement.pdf) E 题。
## 题目描述

Elma 正在学习象棋。

Elma 是个新手，她还不特别了解象棋是如何下的，所以，为了更好地让她了解象棋，她的奶奶让她从一个棋盘（如下图）中进行 $n$ 次移动，每次移动只能是水平或垂直地移动若干个格子的，且每个点只能到达一次，使得从 a1 到 h8 处。

![](https://cdn.luogu.com.cn/upload/image_hosting/zlooykdb.png)
## 输入格式

输入一个数 $n(2 \leq n \leq 63)$，表示你一共需要走的步数。
## 输出格式

给出一种可行方案且保证停留过的点不重复。
## 样例

### 样例输入 #1
```
4
```
### 样例输出 #1
```
a1 f1 c1 c8 h8
```
## 提示

对于所有数据保证 $2 \leq n \leq 63$ 且保证存在至少一种合法方案。


---

---
title: "[ICPC 2020 Shanghai R] Mine Sweeper II"
layout: "post"
diff: 普及+/提高
pid: P9820
tag: ['模拟', '数学', '2020', '上海', 'Special Judge', 'O2优化', 'ICPC']
---
# [ICPC 2020 Shanghai R] Mine Sweeper II
## 题目描述

A mine-sweeper map $X$ can be expressed as an $n\times m$ grid. Each cell of the grid is either a mine cell or a non-mine cell. A mine cell has no number on it. Each non-mine cell has a number representing the number of mine cells around it. (A cell is around another cell if they share at least one common point. Thus, every cell that is not on the boundary has $8$ cells around it.) The following is a $16\times 30$ mine-sweeper map where a flagged cell denotes a mine cell and a blank cell denotes a non-mine cell with number 0.

![](https://cdn.luogu.com.cn/upload/image_hosting/5bykwzuy.png)

Given two mine-sweeper maps $A, B$ of size $n\times m$, you should modify at most $\left\lfloor\frac{nm}{2}\right\rfloor$ (i.e. the largest nonnegative integer that is less than or equal to $\frac{nm}{2}$) cells in $B$ (from a non-mine cell to a mine cell or vice versa) such that the sum of numbers in the non-mine cells in $A$ and the sum of numbers in the non-mine cells in $B$ are the same. (If a map has no non-mine cell, the sum is considered as $0$.)

If multiple solutions exist, print any of them. If no solution exists, print ``-1`` in one line.
## 输入格式

The first line contains two integers $n, m\,(1\le n,m \le 1000)$, denoting the size of given mine-sweeper maps.

The $i$-th line of the following $n$ lines contains a length-$m$ string consisting of  ``.`` and ``X`` denoting the $i$-th row of the mine-sweeper map $A$. A ``.`` denotes for a non-mine cell and an ``X`` denotes for a mine cell.

The $i$-th line of the following $n$ lines contains a length-$m$ string consisting of  ``.`` and ``X`` denoting the $i$-th row of the mine-sweeper map $B$. A ``.`` denotes for a non-mine cell and an ``X`` denotes for a mine cell.
## 输出格式

If no solution exists, print ``-1`` in one line.

Otherwise, print $n$ lines denoting the modified mine-sweeper map $B$. The $i$-th line should contain a length-$m$ string consisting of  ``.`` and ``X`` denoting the $i$-th row of the modified map $B$. A ``.`` denotes for a non-mine cell and an ``X`` denotes for a mine cell.

Please notice that you need not print the numbers on non-mine cells since these numbers can be determined by the output mine-sweeper map.
## 样例

### 样例输入 #1
```
2 4
X..X
X.X.
X.X.
.X..
```
### 样例输出 #1
```
X.XX
.X..
```
## 提示

We modify one cell in $B$. Then the sums of the numbers on non-mine cells in $A$ and $B$ both equal $10$.
## 题目翻译

一张扫雷地图 $X$ 可以被视为一个 $n \times m$ 的网格，每个格子要么是地雷格，要么不是地雷格。地雷格上没有数字，而每个非地雷格上都有一个数字，代表周围相邻 $8$ 个格子中地雷格的数目。下图是一个 $16\times 30$ 的扫雷地图，地雷格由小红旗表示，一个空白的格子代表一个数字为 $0$ 的非地雷格。

![](https://cdn.luogu.com.cn/upload/image_hosting/5bykwzuy.png)


给出两张尺寸均为 $n\times m$ 的扫雷地图 $A,B$。每次修改可以将一个地雷格改为非地雷格，或者将一个非地雷格改为地雷格。你可以修改最多 $\lfloor \dfrac{nm}{2} \rfloor$ 个地图 $B$ 中的格子，请给出一种方案，使得 $A,B$ 中非地雷格上数字之和相同。若无解，输出 $-1$。


---

---
title: "[ICPC 2020 Shanghai R] Sky Garden"
layout: "post"
diff: 普及+/提高
pid: P9827
tag: ['动态规划 DP', '数学', '2020', '上海', 'Special Judge', 'O2优化', 'ICPC']
---
# [ICPC 2020 Shanghai R] Sky Garden
## 题目描述

Prof. Du and Prof. Pang plan to build a sky garden near the city of Allin. In the garden, there will be a plant maze consisting of straight and circular roads.

On the blueprint of the plant maze, Prof. Du draws $n$ circles indicating the circular roads. All of them have center $(0, 0)$. The radius of the $i$-th circle is $i$.

Meanwhile, Prof. Pang draws $m$ lines on the blueprint indicating the straight roads. All of the lines pass through $(0, 0)$. Each circle is divided into $2m$ parts with equal lengths by these lines.

Let $Q$ be the set of the $n+m$ roads. Let $P$ be the set of all intersections of two different roads in $Q$. Note that each circular road and each straight road have two intersections.

For two different points $a\in P$ and $b\in P$, we define $dis(\{a, b\})$ to be the shortest distance one needs to walk from $a$ to $b$ along the roads. Please calculate the sum of $dis(\{a, b\})$ for all $\{a, b\}\subseteq P$. 
## 输入格式

The only line contains two integers $n,m~(1\le n,m\le 500)$.
## 输出格式

Output one number -- the sum of the distances between every pair of points in $P$.

Your answer is considered correct if its absolute or relative error does not exceed $10^{-6}$.
## 样例

### 样例输入 #1
```
1 2
```
### 样例输出 #1
```
14.2831853072
```
### 样例输入 #2
```
2 3
```
### 样例输出 #2
```
175.4159265359
```
## 提示

![](https://cdn.luogu.com.cn/upload/image_hosting/81sxvtcp.png)

$dis(p_1, p_2)=dis(p_2, p_3)=dis(p_3, p_4)=dis(p_1, p_4)=\frac{\pi}{2}$

$dis(p_1, p_5)=dis(p_2, p_5)=dis(p_3, p_5)=dis(p_4, p_5)=1$

$dis(p_1, p_3)=dis(p_2, p_4)=2$
## 题目翻译

Prof. Du 和 Prof. Pang 计划在 Allin 城周围建立一个天空花园。在花园中，将有一个由直路和圆弧路组成的植物迷宫。

在植物迷宫的蓝图上，Prof. Du 画了 $n$ 个圆来表示所有的圆弧路，所有的 $n$ 个圆的圆心均为 $(0,0)$，第 $i$ 个圆的半径为 $i$。

同时，Prof. Pang 在蓝图上画了 $m$ 条直线，表示所有的直路。这 $m$ 条直线将所有的圆均分为 $2m$ 份。

假定集合 $Q$ 是所有 $n+m$ 条路的集合，集合 $P$ 是 $Q$ 中任意两条不相同的路的交点的集合。请注意，每条直线和每个圆有两个交点。

对于任意两个不同的点 $a\in P$，$b\in P$，定义 $\operatorname{dis}(\{a,b\})$ 为从点 $a$ 走到点 $b$ 的最短距离。对于所有 $\{a,b\} \subseteq P$，计算 $\operatorname{dis}(\{a,b\})$ 的和。


---

---
title: "[ICPC 2021 Nanjing R] Paimon Sorting"
layout: "post"
diff: 普及+/提高
pid: P9843
tag: ['2021', 'Special Judge', 'O2优化', 'ICPC', '南京']
---
# [ICPC 2021 Nanjing R] Paimon Sorting
## 题目描述

Paimon just invents a new sorting algorithm which looks much like $\textit{bubble sort}$, with a few differences. It accepts a $1$-indexed sequence $A$ of length $n$ and sorts it. Its pseudo-code is shown below.

```cpp
// The Sorting Algorithm
SORT(A)
  for i from 1 to n // n is the number of elements if A
    for j from 1 to n
      if a[i] < a[j] // a[i] is the i-th element in A
        Swap a[i] and a[j]
```


If you don't believe this piece of algorithm can sort a sequence it will also be your task to prove it. Anyway here comes the question:

Given an integer sequence $A = a_1, a_2, \cdots, a_n$ of length $n$, for each of its prefix $A_k$ of length $k$ (that is, for each $1 \le k \le n$, consider the subsequence $A_k = a_1, a_2, \cdots, a_k$), count the number of swaps performed if we call $\text{SORT}(A_k)$.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line contains an integer $n$ ($1 \le n \le 10^5$) indicating the length of the sequence.

The second line contains $n$ integers $a_1, a_2, \cdots, a_n$ ($1 \le a_i \le n$) indicating the given sequence.

It's guaranteed that the sum of $n$ of all test cases will not exceed $10^6$.
## 输出格式

For each test case output one line containing $n$ integers $s_1, s_2, \cdots, s_n$ separated by a space, where $s_i$ is the number of swaps performed if we call $\text{SORT}(A_i)$.

Please, DO NOT output extra spaces at the end of each line or your solution may be considered incorrect!
## 样例

### 样例输入 #1
```
3
5
2 3 2 1 5
3
1 2 3
1
1

```
### 样例输出 #1
```
0 2 3 5 7
0 2 4
0

```
## 题目翻译

给出一个排序算法（用伪代码表示）：

```cpp
// 排序算法
SORT(A)
  for i from 1 to n // n 是序列 A 的元素个数
    for j from 1 to n
      if a[i] < a[j] // a[i] 是序列 A 的第 i 个元素
        Swap a[i] and a[j]

```

请你算出对于一个序列 $A=a_1,a_2,\cdots,a_n$ 的所有前缀 $A_k=a_1,a_2,\cdots,a_k$（$1\le k\le n$），$\operatorname{SORT}(A_k)$ 中的交换（Swap）操作将会被执行几次。


---

---
title: "[EC Final 2021] Fenwick Tree"
layout: "post"
diff: 普及+/提高
pid: P9883
tag: ['2021', 'Special Judge', 'O2优化', 'ICPC']
---
# [EC Final 2021] Fenwick Tree
## 题目描述

Prof. Pang is giving a lecture on the Fenwick tree (also called binary indexed tree). 

In a Fenwick tree, we have an array $c[1\ldots n]$ of length $n$ which is initially all-zero ($c[i]=0$ for any $1\le i\le n$). Each time, Prof. Pang can call the following procedure for some position $pos$ ($1\leq pos \leq n$) and value $val$:

```cpp
def update(pos, val):
    while (pos <= n):
        c[pos] += val
        pos += pos & (-pos)
```

Note that `pos & (-pos)` equals to the maximum power of $2$ that divides `pos` for any positive integer `pos`. 

In the procedure, $val$ can be **any real** number. After calling it some (zero or more) times, Prof. Pang forgets the exact values in the array $c$. He only remembers whether $c[i]$ is zero or not for each $i$ from $1$ to $n$. Prof. Pang wants to know what is the minimum possible number of times he called the procedure assuming his memory is accurate.
## 输入格式

The first line contains a single integer $T~(1 \le T \le 10^5)$ denoting the number of test cases.

For each test case, the first line contains an integer $n~(1 \le n \le 10 ^ 5)$. The next line contains a string of length $n$. The $i$-th character of the string is `1` if $c[i]$ is nonzero and `0` otherwise. 

It is guaranteed that the sum of $n$ over all test cases is no more than $10^6$.
## 输出格式

For each test case, output the minimum possible number of times Prof. Pang called the procedure. It can be proven that the answer always exists.
## 样例

### 样例输入 #1
```
3
5
10110
5
00000
5
11111

```
### 样例输出 #1
```
3
0
3

```
## 提示

For the first example, Prof. Pang can call `update(1,1)`, `update(2,-1)`, `update(3,1)` in order.

For the third example, Prof. Pang can call `update(1,1)`, `update(3,1)`, `update(5,1)` in order.
## 题目翻译

定义一次「操作」为选定任意一个 $pos$ 和 $val$ 后对 $c$ 序列进行以下操作（显然就是树状数组的单点加操作）：

```python
def update(pos, val):
    while (pos <= n):
        c[pos] += val
        pos += pos & (-pos)
```

给定序列长度 $n$ 和一个长度为 $n$ 的 $\texttt{01}$ 串 $s$，以及一个初始全为 $0$ 的序列 $c$。 求最少的操作数使得最终的 $c$ 序列满足 $\forall 1\le i\le n: s_i=\texttt0 \Leftrightarrow c_i=0,s_i=1\Leftrightarrow c_i\not=0$。 

你只需要输出最少的操作数。


---

---
title: "[ICPC 2018 Qingdao R] Magic Multiplication"
layout: "post"
diff: 普及+/提高
pid: P9888
tag: ['模拟', '2018', 'O2优化', '枚举', 'ICPC', '青岛']
---
# [ICPC 2018 Qingdao R] Magic Multiplication
## 题目描述

BaoBao is now learning a new binary operation between two positive integers, represented by $\otimes$, in his magic book. The book tells him that the result of such operation is calculated by concatenating all multiple results of each digit in the two integers.

Formally speaking, let the first integer be $A = a_1a_2 \dots a_n$, where $a_i$ indicates the $i$-th digit in $A$, and the second integer be $B = b_1b_2 \dots b_m$, where $b_i$ indicates the $i$-th digit in $B$. We have 

$$A \otimes B = \sum\limits_{i=1}^n\sum\limits_{j=1}^m a_ib_j = a_1b_1 + a_1b_2 + \dots + a_1b_m + a_2b_1 + \dots + a_nb_m$$ 

Note that the result of $a_ib_j$ is considered to be a $\textbf{string}$ (without leading zeros if $a_ib_j > 0$, or contains exactly one `0` if $a_ib_j = 0$), NOT a normal integer. Also, the sum here means $\textbf{string concatenation}$, NOT the normal addition operation.

For example, $23 \otimes 45 = 8101215$. Because $8=2 \times 4$, $10=2 \times 5$, $12=3 \times 4$ and $15=3 \times 5$.

BaoBao is very smart and soon knows how to do the inverse operation of $\otimes$. Now he gives you the result of a $\otimes$ operation and the numbers of digits in the two original integers. Please help him to restore the two original integers $A$ and $B$.

## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$, indicating the number of test cases. For each test case:

The first line contains two positive integers $n$ and $m$ ($1 \le n, m \le 2 \times 10^5$), where $n$ indicates the length of $A$ and $m$ indicates the length of $B$. Here length of an integer means the length of the string when writing the number in decimal notation without leading zeros.

The second line contains only one positive integer $C$ without leading zeros, indicating the result of $A \otimes B$. The length of $C$ is no more than $2 \times 10^5$.

It's guaranteed that the sum of lengths of $C$ over all test cases will not exceed $2 \times 10^6$.
## 输出格式

For each test case output one line.

If there exist such $A$ and $B$ that $A \otimes B = C$, output one line containing two integers $A$ and $B$ separated by one space. Note that $A$ and $B$ should be positive integers without leading zeros, the length of $A$ should be exactly $n$, and the length of $B$ should be exactly $m$.

If there are multiple valid answers, output the answer with the smallest $A$; If there are still more than one answer, output one of them with the smallest $B$.

If such $A$ and $B$ do not exist, print ``Impossible`` (without quotes) on a single line.
## 样例

### 样例输入 #1
```
4
2 2
8101215
3 4
100000001000
2 2
80101215
3 4
1000000010000
```
### 样例输出 #1
```
23 45
101 1000
Impossible
Impossible
```
## 题目翻译

BaoBao 现在正在他的魔法书中学习两个正整数之间的一种新的二进制运算，用 $\otimes$ 表示。这本书告诉他，这种运算的结果是通过将两个整数中每个数字的所有多个结果串联起来计算的。

形式上讲，让第一个整数为 $A=A_1a_2\dots A_n$，其中 $A_i$ 表示 $A$ 中的第 $i$ 位，第二个整数为 $B=B_1b_2\dots B_m$，其中 $B_i$ 表示 $B$ 中的第一位。我们有

$$A \otimes B = \sum\limits_{i=1}^n\sum\limits_{j=1}^m a_ib_j = a_1b_1 + a_1b_2 + \dots + a_1b_m + a_2b_1 + \dots + a_nb_m$$

请注意，$a_ib_j$ 的结果被认为是 $\textbf{string}$（如果 $a_ib_j>0$，则不带前导零，或者如果 $a_ib_j > 0$，则仅包含一个 $0$），而不是正常整数。此外，这里的 sum 表示 $\textbf{string concatenation}$，而不是正常的加法运算。

例如，$23\otimes 45=8101215$。因为 $8=2\times 4$，$10=2\times 5$，$12=3\times 4$ 和 $15=3\times 5$。

BaoBao 很聪明，很快就知道如何做 $\otimes$ 的逆运算。现在，他给出了 $\otimes$ 运算的结果以及两个原始整数中的位数。请帮助他恢复两个原始整数 $A$ 和 $B$。

## 输入格式

有多个测试用例。输入的第一行包含一个整数 $T$，表示测试用例的数量。对于每个测试用例：

第一行包含两个正整数 $n$ 和 $m$（$1\le n,m\le 2\times 10^5$），其中 $n$ 表示 $A$ 的长度，$m$ 表示 $B$ 的长度。这里，整数的长度是指在不带前导零的十进制记数法中写入数字时字符串的长度。

第二行只包含一个不带前导零的正整数 $C$，表示 $A\otimes B$ 的结果。$C$ 的长度不超过 $2\times 10^5$。

保证所有测试用例的 $C$ 长度总和不会超过 $2\times 10^6$。

## 输出格式

对于每个测试用例输出一行。

如果存在这样的 $A$ 和 $B$，$A\otimes B=C$，则输出一行，其中包含由一个空格分隔的两个整数 $A$ 与 $B$。请注意，$A$ 和 $B$ 应该是不带前导零的正整数，$A$ 的长度应该正好是 $n$，$B$ 的长度应正好是 $m$。

如果存在多个有效答案，则输出具有最小 $A$ 的答案；如果仍然有一个以上的答案，请输出其中一个最小的 $B$。

如果不存在这样的 $A$ 和 $B$，请在单行上打印 ``Impossible``（不带引号）。


---

---
title: "[ICPC 2018 Qingdao R] Plants vs. Zombies"
layout: "post"
diff: 普及+/提高
pid: P9889
tag: ['贪心', '2018', '二分', 'O2优化', 'ICPC', '青岛']
---
# [ICPC 2018 Qingdao R] Plants vs. Zombies
## 题目描述

BaoBao and DreamGrid are playing the game $\textit{Plants vs. Zombies}$. In the game, DreamGrid grows plants to defend his garden against BaoBao's zombies.

![](https://cdn.luogu.com.cn/upload/image_hosting/9tyl9ix3.png)

$\textit{Plants vs. Zombies(?)} \\
\textit{(Image from pixiv. ID: 21790160; Artist: socha)}$

There are $n$ plants in DreamGrid's garden arranged in a line. From west to east, the plants are numbered from 1 to $n$ and the $i$-th plant lies $i$ meters to the east of DreamGrid's house. The $i$-th plant has a defense value of $d_i$ and a growth speed of $a_i$. Initially, $d_i = 0$ for all $1 \le i \le n$. 

DreamGrid uses a robot to water the plants. The robot is in his house initially. In one step of watering, DreamGrid will choose a direction (east or west) and the robot moves exactly 1 meter along the direction. After moving, if the $i$-th plant is at the robot's position, the robot will water the plant and $a_i$ will be added to $d_i$. Because the water in the robot is limited, at most $m$ steps can be done.

The defense value of the garden is defined as $\min\{d_i | 1 \le i \le n\}$. DreamGrid needs your help to maximize the garden's defense value and win the game.

- Each time the robot MUST move before watering a plant;
- It's OK for the robot to move more than $n$ meters to the east away from the house, or move back into the house, or even move to the west of the house.
## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$, indicating the number of test cases. For each test case:

The first line contains two integers $n$ and $m$ ($2 \le n \le 10^5$, $0 \le m \le 10^{12}$), indicating the number of plants and the maximum number of steps the robot can take.

The second line contains $n$ integers $a_1, a_2, ... , a_n$ ($1 \le a_i \le 10^5$), where $a_i$ indicates the growth speed of the $i$-th plant.

It's guaranteed that the sum of $n$ in all test cases will not exceed $10^6$.
## 输出格式

For each test case output one line containing one integer, indicating the maximum defense value of the garden DreamGrid can get.
## 样例

### 样例输入 #1
```
2
4 8
3 2 6 6
3 9
10 10 1
```
### 样例输出 #1
```
6
4
```
## 提示

In the explanation below, `E` indicates that the robot moves exactly 1 meter to the east from his current position, and `W` indicates that the robot moves exactly 1 meter to the west from his current position.

For the first test case, a candidate direction sequence is $\{E, E, W, E, E, W, E, E\}$, so that we have $d = \{6,6,12,6\}$ after the watering.

For the second test case, a candidate direction sequence is $\{E, E, E, E, W, E, W, E, W\}$, so that we have $d = \{10, 10, 4\}$ after the watering.
## 题目翻译

给定 $n$ 个植物和 $m$ 的步数限制，每个植物在位置 $1\dots n$ 上。你初始时在位置 $0$，每次可以移动到相邻的位置上。

每次设你走完一步后到达的位置是 $i$，则会使得这个位置的植物的高度增加 $a_i$。设 $d_i$ 为走完 $m$ 步后位置 $i$ 的植物高度，求出一个最优的走法使得 $\min\limits_{1 \le i \le n} d_i$ 最大。

$2\leq n\leq 10 ^ 5$，$0\leq m\leq 10 ^ {12}$，$1\leq a_i\leq 10 ^ 5$，$\sum n\leq 10 ^ 6$。


---

