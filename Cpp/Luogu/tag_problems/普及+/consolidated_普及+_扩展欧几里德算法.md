---
title: "[NOIP 2012 提高组] 同余方程"
layout: "post"
diff: 普及+/提高
pid: P1082
tag: ['数学', '2012', 'NOIP 提高组', '扩展欧几里德算法']
---
# [NOIP 2012 提高组] 同余方程
## 题目描述

求关于 $ x$ 的同余方程 $ a x \equiv 1 \pmod {b}$ 的最小正整数解。

## 输入格式

一行，包含两个整数 $a,b$，用一个空格隔开。

## 输出格式

一个整数 $x_0$，即最小正整数解。输入数据保证一定有解。

## 样例

### 样例输入 #1
```
3 10
```
### 样例输出 #1
```
7
```
## 提示

### 数据规模与约定

- 对于 $40\%$ 的数据，$2 ≤b≤ 1,000$；
- 对于 $60\%$ 的数据，$2 ≤b≤ 50,000,000$；
- 对于 $100\%$ 的数据，$2 ≤a, b≤ 2,000,000,000$。




---

---
title: "[GCJ Farewell Round #2] Intruder Outsmarting"
layout: "post"
diff: 普及+/提高
pid: P12952
tag: ['数学', '2023', '扩展欧几里德算法', 'Google Code Jam']
---
# [GCJ Farewell Round #2] Intruder Outsmarting
## 题目描述

Amiria is a cautious internet user, and as such, she is setting up two-factor authentication for her accounts. She is using a special type of security key as an extra precaution to outsmart any intruders that may want to take it. Amiria's security key requires a code to activate. To enter the code, one must place it on wheels with numbers, similar to code padlocks.

Amiria's security key has a sequence of $\mathbf{W}$ wheels. Each wheel has the numbers 1 through $\mathbf{N}$ printed in order. By one wheel rotation, the user can move the currently shown integer either to the next or the previous integer. Numbers on the wheel wrap around. This means the number after $\mathbf{N}$ is 1 and the number before 1 is $\mathbf{N}$.

There is no hidden password. To activate Amiria's security key, a person needs to move the wheels such that the sequence of numbers shown is palindromic. That is, the sequence of numbers is the same when read from left to right and from right to left. To slow down intruders, Amiria rigged the security key such that the wheels only rotate in increments of $\mathbf{D}$. That is, on a move, a wheel that is currently showing $x$ can be made to show $x - \mathbf{D}$ or $x + \mathbf{D}$, applying the proper wraparound. That is, if $x - \mathbf{D} < 1$ the actual number shown after the operation is $x - \mathbf{D} + \mathbf{N}$, and if $x + \mathbf{D} > \mathbf{N}$ the actual number shown is $x + \mathbf{D} - \mathbf{N}$.

Amiria wants to check how much this system would slow down an intruder trying to use her security key. Given the number of wheels and the number currently shown on each wheel, find the minimum number of operations needed to make the sequence of shown numbers palindromic, or report that it is impossible to do so.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case consists of two lines. The first line of a test case contains 3 integers $\mathbf{W}$, $\mathbf{N}$, and $\mathbf{D}$: the number of wheels in Amiria's security key, the number of integers shown in each of those wheels, and the fixed increment that Amiria rigged for every wheel. The second line of a test case contains $\mathbf{W}$ integers $\mathbf{X}_{1}, \mathbf{X}_{2}, \ldots, \mathbf{X}_{\mathbf{W}}$, where $\mathbf{X}_{i}$ is the number currently shown in the $i$-th wheel from left to right.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the minimum number of operations needed to make the sequence of shown numbers palindromic. If there is no way to make the sequence of shown numbers palindromic through the allowed operations, $y$ must be IMPOSSIBLE instead.
## 样例

### 样例输入 #1
```
3
5 5 4
1 4 5 5 4
3 4 2
3 4 3
2 4 2
1 4
```
### 样例输出 #1
```
Case #1: 3
Case #2: 0
Case #3: IMPOSSIBLE
```
## 提示

**Sample Explanation**

In Sample Case #1, the sequence can be made $5 \ 4 \ 5 \ 4 \ 5$, which is palindromic, with 3 operations by using one addition operation on the first and fourth wheels, and one subtraction operation on the fifth wheel. There is no way to make the sequence palindromic with fewer moves.

In Sample Case #2 the sequence is already palindromic, so we do not need any operations.

In Sample Case #3, both numbers would need to be equal for the sequence to be palindromic. Since wheel values can only move by 2 and both current numbers have different parity, that cannot be done.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $1 \leq \mathbf{D} \leq \mathbf{N}-1$.
- $1 \leq \mathbf{X}_{\mathbf{i}} \leq \mathbf{N}$, for all $i$.

**Test Set 1 (4 Pts, Visible Verdict)**

- $2 \leq \mathbf{W} \leq 5$.
- $2 \leq \mathbf{N} \leq 5$.

**Test Set 2 (10 Pts, Visible Verdict)**

- $2 \leq \mathbf{W} \leq 1000$.
- $2 \leq \mathbf{N} \leq 10^{9}$.



---

---
title: "[GCJ 2010 #3] De-RNG-ed"
layout: "post"
diff: 普及+/提高
pid: P13403
tag: ['2010', '数论', '扩展欧几里德算法', '分类讨论', 'Google Code Jam']
---
# [GCJ 2010 #3] De-RNG-ed
## 题目描述

I want to make an online poker website. A very important component of such a system is the random number generator. It needs to be fast and random enough. Here is a compromise I came up with. I need a way to generate random numbers of length at most $D$. My plan is to select a prime number $P \leq 10^D$. I am also going to pick non-negative integers $A$ and $B$. Finally, I'm going to pick an integer seed $S$ between $0$ and $P-1$, inclusive.

To output my sequence of pseudo-random numbers, I'm going to first output $S$ and then compute the new value of $S$ like this:

$$S := (A\times S + B) \bmod P$$

Then I will output the new value of $S$ as the next number in the sequence and update $S$ again by using the same formula. I can repeat this as many times as I want.

Do you think that this is a good random number generator? Can you write a program that takes $K$ consecutive elements of a sequence that was generated by my random number generator, and prints the next element of the sequence?

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each one starts with a line containing $D$ and $K$. The next line contains $K$ consecutive elements generated by a random number generator of the kind described above.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the case number (starting from 1) and $y$ is either the next number in the sequence, or the string "I don't know." if the answer is ambiguous.
## 样例

### 样例输入 #1
```
3
2 10
0 1 2 3 4 5 6 7 8 9
3 1
13
1 5
6 6 6 6 6
```
### 样例输出 #1
```
Case #1: 10
Case #2: I don't know.
Case #3: 6
```
## 提示

**Limits**

- $1 \leq T \leq 100$.
- $1 \leq K \leq 10$.
- The $K$ integers will be consecutive elements of a sequence generated by a random number generator of the type described above.

**Small dataset (4 Pts, Test set 1 - Visible)**

- $1 \leq D \leq 4$.

**Large dataset (10 Pts, Test set 2 - Hidden)**

- $1 \leq D \leq 6$.



---

---
title: "青蛙的约会"
layout: "post"
diff: 普及+/提高
pid: P1516
tag: ['数学', '扩展欧几里德算法', '中国剩余定理 CRT']
---
# 青蛙的约会
## 题目描述

两只青蛙在网上相识了，它们聊得很开心，于是觉得很有必要见一面。它们很高兴地发现它们住在同一条纬度线上，于是它们约定各自朝西跳，直到碰面为止。可是它们出发之前忘记了一件很重要的事情，既没有问清楚对方的特征，也没有约定见面的具体位置。不过青蛙们都是很乐观的，它们觉得只要一直朝着某个方向跳下去，总能碰到对方的。但是除非这两只青蛙在同一时间跳到同一点上，不然是永远都不可能碰面的。为了帮助这两只乐观的青蛙，你被要求写一个程序来判断这两只青蛙是否能够碰面，会在什么时候碰面。

我们把这两只青蛙分别叫做青蛙 A 和青蛙 B，并且规定纬度线上东经 $0$ 度处为原点，由东往西为正方向，单位长度 $1$ 米，这样我们就得到了一条首尾相接的数轴。设青蛙 A 的出发点坐标是 $x$，青蛙 B 的出发点坐标是 $y$。青蛙 A 一次能跳 $m$ 米，青蛙 B 一次能跳 $n$ 米，两只青蛙跳一次所花费的时间相同。纬度线总长 $L$ 米。现在要你求出它们跳了几次以后才会碰面。

## 输入格式

输入只包括一行五个整数 $x,y,m,n,L$。

## 输出格式

输出碰面所需要的次数，如果永远不可能碰面则输出一行一个字符串 `Impossible`。

## 样例

### 样例输入 #1
```
1 2 3 4 5

```
### 样例输出 #1
```
4

```
## 提示

对于 $100\%$ 的数据，$1 \le x \ne y \le 2 \times 10^{9}$，$1 \le m, n \le 2 \times 10^{9}$，$1 \le L \le 2.1 \times 10^{9}$。



---

---
title: "【模板】有理数取余"
layout: "post"
diff: 普及+/提高
pid: P2613
tag: ['数学', '高精度', '扩展欧几里德算法']
---
# 【模板】有理数取余
## 题目描述

给出一个有理数 $c=\frac{a}{b}$，求 $c \bmod 19260817$ 的值。

这个值被定义为 $bx\equiv a\pmod{19260817}$ 的解。
## 输入格式

一共两行。

第一行，一个整数 $a$。  
第二行，一个整数 $b$。  
## 输出格式

一个整数，代表求余后的结果。如果无解，输出 `Angry!`。
## 样例

### 样例输入 #1
```
233
666

```
### 样例输出 #1
```
18595654

```
## 提示

对于所有数据，保证 $0\leq a \leq 10^{10001}$，$1 \leq b \leq 10^{10001}$，且 $a, b$ 不同时是 $19260817$ 的倍数。


---

