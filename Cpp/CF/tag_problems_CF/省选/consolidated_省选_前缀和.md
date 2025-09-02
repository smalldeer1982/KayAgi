---
title: "AB-Strings"
layout: "post"
diff: 省选/NOI-
pid: CF1012D
tag: ['字符串', '前缀和']
---

# AB-Strings

## 题目描述

## 题面描述
给定两个只包含 $\texttt{a}$ 和 $\texttt{b}$ 的字符串，每次操作可以把两个字符串的任意前缀进行交换（前缀长度可以为 $0$），问最少多少次操作可以使的一个串只有 $\texttt{a}$，另一个串只有 $\texttt{b}$。

## 输入格式

两行，一行一个字符串，保证串长 $\leq 200000$。

保证两个串中有 $\texttt{a}$ 和 $\texttt{b}$。

## 输出格式

第一行一个整数 $n(0\leq n\leq 500000)$，表示答案。

后面 $n$ 行，一行两个整数，表示每次操作时被交换的两个串的前缀长度。

## 样例 #1

### 输入

```
bab
bb

```

### 输出

```
2
1 0
1 3

```

## 样例 #2

### 输入

```
bbbb
aaa

```

### 输出

```
0

```



---

---
title: "Graph And Numbers"
layout: "post"
diff: 省选/NOI-
pid: CF1221G
tag: ['前缀和']
---

# Graph And Numbers

## 题目描述

You are given an undirected graph with $ n $ vertices and $ m $ edges. You have to write a number on each vertex of this graph, each number should be either $ 0 $ or $ 1 $ . After that, you write a number on each edge equal to the sum of numbers on vertices incident to that edge.

You have to choose the numbers you will write on the vertices so that there is at least one edge with $ 0 $ written on it, at least one edge with $ 1 $ and at least one edge with $ 2 $ . How many ways are there to do it? Two ways to choose numbers are different if there exists at least one vertex which has different numbers written on it in these two ways.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n \le 40 $ , $ 0 \le m \le \frac{n(n - 1)}{2} $ ) — the number of vertices and the number of edges, respectively.

Then $ m $ lines follow, each line contains two numbers $ x_i $ and $ y_i $ ( $ 1 \le x_i, y_i \le n $ , $ x_i \ne y_i $ ) — the endpoints of the $ i $ -th edge. It is guaranteed that each pair of vertices is connected by at most one edge.

## 输出格式

Print one integer — the number of ways to write numbers on all vertices so that there exists at least one edge with $ 0 $ written on it, at least one edge with $ 1 $ and at least one edge with $ 2 $ .

## 样例 #1

### 输入

```
6 5
1 2
2 3
3 4
4 5
5 1

```

### 输出

```
20

```

## 样例 #2

### 输入

```
4 4
1 2
2 3
3 4
4 1

```

### 输出

```
4

```

## 样例 #3

### 输入

```
35 29
1 2
2 3
3 1
4 1
4 2
3 4
7 8
8 9
9 10
10 7
11 12
12 13
13 14
14 15
15 16
16 17
17 18
18 19
19 20
20 21
21 22
22 23
23 24
24 25
25 26
26 27
27 28
28 29
29 30

```

### 输出

```
34201047040

```



---

---
title: "Bracket Insertion"
layout: "post"
diff: 省选/NOI-
pid: CF1781F
tag: ['动态规划 DP', '组合数学', '前缀和', '概率论']
---

# Bracket Insertion

## 题目描述

Vika likes playing with bracket sequences. Today she wants to create a new bracket sequence using the following algorithm. Initially, Vika's sequence is an empty string, and then she will repeat the following actions $ n $ times:

- Choose a place in the current bracket sequence to insert new brackets uniformly at random. If the length of the current sequence is $ k $ , then there are $ k+1 $ such places: before the first bracket, between the first and the second brackets, $ \ldots $ , after the $ k $ -th bracket. In particular, there is one such place in an empty bracket sequence.
- Choose string "()" with probability $ p $ or string ")(" with probability $ 1 - p $ and insert it into the chosen place. The length of the bracket sequence will increase by $ 2 $ .

A bracket sequence is called regular if it is possible to obtain a correct arithmetic expression by inserting characters '+' and '1' into it. For example, sequences "(())()", "()", and "(()(()))" are regular, while ")(", "(()", and "(()))(" are not.

Vika wants to know the probability that her bracket sequence will be a regular one at the end. Help her and find this probability modulo $ 998\,244\,353 $ (see Output section).

## 输入格式

The only line contains two integers $ n $ and $ q $ ( $ 1 \le n \le 500 $ ; $ 0 \le q \le 10^4 $ ). Here $ n $ is equal to the number of bracket insertion operations, and the probability that Vika chooses string "()" on every step of the algorithm is equal to $ p = q \cdot 10^{-4} $ .

## 输出格式

Print the probability that Vika's final bracket sequence will be regular, modulo $ 998\,244\,353 $ .

Formally, let $ M = 998\,244\,353 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 说明/提示

In the first example, Vika will get a regular bracket sequence () with probability $ p = \frac{3}{4} $ , and she will get an irregular bracket sequence )( with probability $ 1 - p = \frac{1}{4} $ . The sought probability is $ \frac{3}{4} $ , and $ 249\,561\,089 \cdot 4 \equiv 3 \pmod{998\,244\,353} $ .

In the second example, the sought probability is $ \frac{11}{25} $ .

## 样例 #1

### 输入

```
1 7500
```

### 输出

```
249561089
```

## 样例 #2

### 输入

```
2 6000
```

### 输出

```
519087064
```

## 样例 #3

### 输入

```
5 4000
```

### 输出

```
119387743
```



---

---
title: "Palisection"
layout: "post"
diff: 省选/NOI-
pid: CF17E
tag: ['字符串', '前缀和', '差分']
---

# Palisection

## 题目描述

给定一个长度为n的小写字母串。问你有多少对相交的回文子 串（包含也算相交） 。

## 输入格式

第一行是字符串长度n(1<=n<=2*10^6)，第二行字符串

## 输出格式

相交的回文子串个数%51123987

Translated by liyifeng

## 样例 #1

### 输入

```
4
babb

```

### 输出

```
6

```

## 样例 #2

### 输入

```
2
aa

```

### 输出

```
2

```



---

---
title: "Button Pressing"
layout: "post"
diff: 省选/NOI-
pid: CF1906B
tag: ['前缀和']
---

# Button Pressing

## 题目描述

You are given $ N $ buttons (numbered from $ 1 $ to $ N $ ) and $ N $ lamps (numbered from $ 1 $ to $ N $ ). Each lamp can either be on or off. Initially, lamp $ i $ is on if $ A_i = 1 $ , and off if $ A_i = 0 $ .

Button $ i $ is connected to lamp $ i - 1 $ (if $ i > 1 $ ) and lamp $ i + 1 $ (if $ i < N $ ). In one move, you can press a button $ i $ only if lamp $ i $ is on. When a button is pressed, the state of the lamps connected to this button is toggled. Formally, the lamps will be on if it was off previously, and the lamps will be off if it was on previously. Note that lamp $ i $ is not connected to button $ i $ , thus, the state of lamp $ i $ does not change if button $ i $ is pressed.

After zero or more moves, you want lamp $ i $ to be on if $ B_i = 1 $ , and off if $ B_i = 0 $ . Determine if it is possible to achieve this task.

## 输入格式

This problem has multiple test cases. The first line consists of an integer $ T $ ( $ 1 \leq T \leq 1000 $ ), which represents the number of test cases. Each test case consists of three lines.

The first line of each test case consists of an integer $ N $ ( $ 3 \le N \le 200\,000 $ ). The sum of $ N $ over all test cases does not exceed $ 200\,000 $ .

The second line of each test case consists of a string $ A $ of length $ N $ . Each character of $ A $ can either be 0 or 1. The $ i $ -th character represents the initial state of lamp $ i $ .

The third line of each test case consists of a string $ A $ of length $ N $ . Each character of $ B $ can either be 0 or 1. The $ i $ -th character represents the desired final state of lamp $ i $ .

## 输出格式

For each test case, output YES in a single line if the final state of all lamps can be reached after zero or more moves, or NO otherwise.

## 说明/提示

Explanation for the sample input/output #1

For the first test case, by pressing the buttons $ 4, 2, 4, 3, 1, 2 $ in sequence, the condition of the buttons changes as: $ 0101 \rightarrow 0111 \rightarrow 1101 \rightarrow 1111 \rightarrow 1010 \rightarrow 1110 \rightarrow 0100 $ .

For the second test case, you are unable to press any button, hence it is impossible to reach the final state.

## 样例 #1

### 输入

```
2
4
0101
0100
3
000
010
```

### 输出

```
YES
NO
```

## 样例 #2

### 输入

```
5
7
0101011
1111010
5
11111
00000
4
1101
1101
6
101010
100100
3
000
000
```

### 输出

```
NO
NO
YES
YES
YES
```



---

---
title: "The Destruction of the Universe (Hard Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2030G2
tag: ['组合数学', '排列组合', '前缀和']
---

# The Destruction of the Universe (Hard Version)

## 题目描述

This is the hard version of the problem. In this version, $ n \leq 10^6 $ . You can only make hacks if both versions of the problem are solved.

Orangutans are powerful beings—so powerful that they only need $ 1 $ unit of time to destroy every vulnerable planet in the universe!

There are $ n $ planets in the universe. Each planet has an interval of vulnerability $ [l, r] $ , during which it will be exposed to destruction by orangutans. Orangutans can also expand the interval of vulnerability of any planet by $ 1 $ unit.

Specifically, suppose the expansion is performed on planet $ p $ with interval of vulnerability $ [l_p, r_p] $ . Then, the resulting interval of vulnerability may be either $ [l_p - 1, r_p] $ or $ [l_p, r_p + 1] $ .

Given a set of planets, orangutans can destroy all planets if the intervals of vulnerability of all planets in the set intersect at least one common point. Let the score of such a set denote the minimum number of expansions that must be performed.

Orangutans are interested in the sum of scores of all non-empty subsets of the planets in the universe. As the answer can be large, output it modulo $ 998\,244\,353 $ .

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 10^6 $ ) — the number of planets in the universe.

The following $ n $ lines contain two integers $ l_i $ and $ r_i $ ( $ 1 \leq l_i \leq r_i \leq n $ ) — the initial interval of vulnerability of the $ i $ -th planet.

It is guaranteed that the sum of $ n $ does not exceed $ 10^6 $ over all test cases.

## 输出格式

For each test case, output an integer — the sum of scores to destroy all non-empty subsets of the planets in the universe, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first testcase, there are seven non-empty subsets of planets we must consider:

- For each of the subsets $ \{[1,1]\}, \{[2,3]\}, \{[3,3]\} $ , the score is $ 0 $ .
- For the subset $ \{[2,3], [3,3]\} $ , the score is $ 0 $ , because the point $ 3 $ is already contained in both planets' interval of vulnerability.
- For the subset $ \{[1,1], [2,3]\} $ , the score is $ 1 $ . By using one operation on changing the interval of vulnerability of the second planet to be $ [1,3] $ , the two planets now both have the point $ 1 $ in their interval.
- For the subset $ \{[1,1], [3,3]\} $ , the score is $ 2 $ . By using two operations on changing the interval of vulnerability of the first planet to be $ [1,3] $ , the two planets now both have the point $ 3 $ in their interval.
- For the subset $ \{[1,1], [2,3], [3,3]\} $ , the score is $ 2 $ . By using one operation on changing the interval of vulnerability of the first planet to be $ [1,2] $ and one operation on changing the interval of vulnerability of the third planet to $ [2,3] $ , all three planets will have the point $ 2 $ in their interval.

The sum of scores of all non-empty subsets of the first testcase is $ 0 \cdot 4 + 1 \cdot 1 + 2\cdot2 = 5 $ .

## 样例 #1

### 输入

```
3
3
1 1
2 3
3 3
4
1 4
2 3
2 4
1 1
5
1 2
2 3
3 4
4 5
1 5
```

### 输出

```
5
6
24
```



---

---
title: "Affectionate Arrays (Easy Version)"
layout: "post"
diff: 省选/NOI-
pid: CF2053I1
tag: ['动态规划 DP', '前缀和']
---

# Affectionate Arrays (Easy Version)

## 题目描述

你是信的开头，诗的内容，童话的结尾。

—— ilem，[《勾指起誓》](https://www.bilibili.com/video/BV1Jb411U7u2/)



本题是简单版问题。两个版本的区别在于，此版本中你需要计算数组的最小长度。只有当你解决了所有版本的问题时才能进行 hack 操作。

Iris 珍视一个整数数组 $a_1, a_2, \ldots, a_n$。她知道这个数组有一个有趣的性质：所有元素的最大绝对值不超过所有元素的和，即 $\max(\lvert a_i\rvert) \leq \sum a_i$。

Iris 定义数组的**无聊值**为其最大子数组$^{\text{∗}}$和。

Iris 的生日即将到来，Victor 打算送她另一个数组 $b_1, b_2, \ldots, b_m$ 作为礼物。出于某些看似明显的原因，他决定数组 $b_1, b_2, \ldots, b_m$ 应满足以下条件：

- $a_1, a_2, \ldots, a_n$ 必须是 $b_1, b_2, \ldots, b_m$ 的子序列$^{\text{†}}$。
- 两个数组的和相同，即 $\sum\limits_{i=1}^n a_i = \sum\limits_{i=1}^m b_i$。
- 数组 $b$ 的无聊值尽可能小。
- 在所有具有最小无聊值的数组中，数组 $b$ 的长度（即 $m$）尽可能小。此时，Iris 将立刻理解他的心意！

即使有上述约束，可能的礼物仍然太多。因此 Victor 请你计算满足所有条件的数组 $b_1, b_2, \ldots, b_m$ 的长度 $\boldsymbol{m}$。他承诺：如果你成功帮助他，他会与你分享 Iris 的生日蛋糕。

注意：由于输入规模较大，你可能需要针对此问题进行优化。

例如，在 C++ 中，只需在 main() 函数开头添加以下代码：

```cpp
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}
```

$^{\text{∗}}$ 若数组 $c$ 可通过删除数组 $d$ 开头和末尾的若干（可能为零或全部）元素得到，则称 $c$ 是 $d$ 的子数组。

$^{\text{†}}$ 若序列 $c$ 可通过删除序列 $d$ 中任意位置的若干（可能为零或全部）元素得到，则称 $c$ 是 $d$ 的子序列。

## 输入格式

每个测试包含多个测试用例。第一行输入一个整数 $t$（$1 \leq t \leq 10^5$）—— 测试用例的数量。接下来是各测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \leq n \leq 3\cdot 10^6$）—— 数组 $a_1, a_2, \ldots, a_n$ 的长度。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$-10^9 \leq a_i \leq 10^9$）—— 初始数组。保证 $\max(\lvert a_i\rvert) \leq \sum a_i$。

保证所有测试用例的 $n$ 之和不超过 $3\cdot 10^6$。

## 输出格式

对每个测试用例，输出一行一个整数：满足条件的数组 $b$ 的长度 $m$。

## 说明/提示

第一个测试用例中，$a=[1, 2, 3, 4]$。唯一满足所有条件的数组 $b$ 是 $[1, 2, 3, 4]$，因此输出 4。

第二个测试用例中，$a=[2, -3, 2, 2]$。可能的数组 $b$ 包括 $[1, 2, -3, 2, -1, 2]$ 和 $[2, 1, -3, 2, -1, 2]$，因此输出 6。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
4
1 2 3 4
4
2 -3 2 2
10
2 -7 6 3 -1 4 2 -5 8 -4
20
4 -2 4 3 -2 1 5 2 3 6 -5 -1 -4 -2 -3 5 -3 1 -4 1
```

### 输出

```
4
6
14
25
```



---

---
title: "Tape Programming"
layout: "post"
diff: 省选/NOI-
pid: CF238D
tag: ['模拟', '前缀和']
---

# Tape Programming

## 题目描述

There is a programming language in which every program is a non-empty sequence of "<" and ">" signs and digits. Let's explain how the interpreter of this programming language works. A program is interpreted using movement of instruction pointer (IP) which consists of two parts.

- Current character pointer (CP);
- Direction pointer (DP) which can point left or right;

Initially CP points to the leftmost character of the sequence and DP points to the right.

We repeat the following steps until the first moment that CP points to somewhere outside the sequence.

- If CP is pointing to a digit the interpreter prints that digit then CP moves one step according to the direction of DP. After that the value of the printed digit in the sequence decreases by one. If the printed digit was $ 0 $ then it cannot be decreased therefore it's erased from the sequence and the length of the sequence decreases by one.
- If CP is pointing to "<" or ">" then the direction of DP changes to "left" or "right" correspondingly. Then CP moves one step according to DP. If the new character that CP is pointing to is "<" or ">" then the previous character will be erased from the sequence.

If at any moment the CP goes outside of the sequence the execution is terminated.

It's obvious the every program in this language terminates after some steps.

We have a sequence $ s_{1},s_{2},...,s_{n} $ of "<", ">" and digits. You should answer $ q $ queries. Each query gives you $ l $ and $ r $ and asks how many of each digit will be printed if we run the sequence $ s_{l},s_{l+1},...,s_{r} $ as an independent program in this language.

## 输入格式

The first line of input contains two integers $ n $ and $ q $ $ (1<=n,q<=10^{5}) $ — represents the length of the sequence $ s $ and the number of queries.

The second line contains $ s $ , a sequence of "<", ">" and digits (0..9) written from left to right. Note, that the characters of $ s $ are not separated with spaces.

The next $ q $ lines each contains two integers $ l_{i} $ and $ r_{i} $ $ (1<=l_{i}<=r_{i}<=n) $ — the $ i $ -th query.

## 输出格式

For each query print $ 10 $ space separated integers: $ x_{0},x_{1},...,x_{9} $ where $ x_{i} $ equals the number of times the interpreter prints $ i $ while running the corresponding program. Print answers to the queries in the order they are given in input.

## 样例 #1

### 输入

```
7 4
1>3>22<
1 3
4 7
7 7
1 7
```

### 输出

```
0 1 0 1 0 0 0 0 0 0
2 2 2 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
2 3 2 1 0 0 0 0 0 0

```



---

---
title: "Colorful Stones"
layout: "post"
diff: 省选/NOI-
pid: CF264D
tag: ['字符串', '前缀和']
---

# Colorful Stones

## 题目描述

There are two sequences of colorful stones. The color of each stone is one of red, green, or blue. You are given two strings $ s $ and $ t $ . The $ i $ -th (1-based) character of $ s $ represents the color of the $ i $ -th stone of the first sequence. Similarly, the $ i $ -th (1-based) character of $ t $ represents the color of the $ i $ -th stone of the second sequence. If the character is "R", "G", or "B", the color of the corresponding stone is red, green, or blue, respectively.

Initially Squirrel Liss is standing on the first stone of the first sequence and Cat Vasya is standing on the first stone of the second sequence. You can perform the following instructions zero or more times.

Each instruction is one of the three types: "RED", "GREEN", or "BLUE". After an instruction $ c $ , the animals standing on stones whose colors are $ c $ will move one stone forward. For example, if you perform an instruction «RED», the animals standing on red stones will move one stone forward. You are not allowed to perform instructions that lead some animals out of the sequences. In other words, if some animals are standing on the last stones, you can't perform the instructions of the colors of those stones.

A pair of positions (position of Liss, position of Vasya) is called a state. A state is called reachable if the state is reachable by performing instructions zero or more times from the initial state (1, 1). Calculate the number of distinct reachable states.

## 输入格式

The input contains two lines. The first line contains the string $ s $ ( $ 1<=|s|<=10^{6} $ ). The second line contains the string $ t $ ( $ 1<=|t|<=10^{6} $ ). The characters of each string will be one of "R", "G", or "B".

## 输出格式

Print the number of distinct reachable states in a single line.

Please, do not write the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 说明/提示

In the first example, there are five reachable states: (1, 1), (2, 2), (2, 3), (3, 2), and (3, 3). For example, the state (3, 3) is reachable because if you perform instructions "RED", "GREEN", and "BLUE" in this order from the initial state, the state will be (3, 3). The following picture shows how the instructions work in this case.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF264D/ff8e8d184349ca742f85291d5c556a28aebdf7a7.png)

## 样例 #1

### 输入

```
RBR
RGG

```

### 输出

```
5

```

## 样例 #2

### 输入

```
RGBB
BRRBRR

```

### 输出

```
19

```

## 样例 #3

### 输入

```
RRRRRRRRRR
RRRRRRRR

```

### 输出

```
8

```



---

---
title: "Greg and Caves"
layout: "post"
diff: 省选/NOI-
pid: CF295D
tag: ['动态规划 DP', '枚举', '前缀和']
---

# Greg and Caves

## 题目描述

Greg有一个8868，其屏幕为一$n \times m$的矩形，每个像素可以是黑色或白色。我们考虑将8868的行从上到下编号为1到$n$。类似地，8868的列从左到右编号为1到$m$



Greg认为8868显示一个洞时，当且仅当以下情况：



- $\exist$区间$[l,r](1 \leq l \leq r \leq n)$，使得每一行恰有两个黑色像素，而所有其他行只有白色像素

- $\exist$行$t(l \leq t \leq r)$，使得对于$\forall(i,j)(l \leq i \leq j \leq t)$，第$i$行中黑色单元格之间列的集合$S_1$，与第$j$行中黑色单元格之间列的集合$S_2$，满足$S_1 \subseteq S_2$，同样对于$\forall (i,j)(t \leq i \leq j \leq r)$，第$i$行中黑色单元格之间列的集合$S_1$，与第$j$行中黑色单元格之间列的集合$S_2$，满足$S_2 \subseteq S_1$，



Greg想知道，有多少种方案能让他的8868显示一个洞。当且仅当两个屏幕存在一个位置像素颜色不同，两种方案不同



帮帮Greg吧

## 输入格式

第一行两个整数$n$，$m$表示8868的分辨率$(1 \leq n,m \leq 2000)$

## 输出格式

一行，答案在模$1e9+7$意义下的数值

## 样例 #1

### 输入

```
1 1

```

### 输出

```
0

```

## 样例 #2

### 输入

```
4 4

```

### 输出

```
485

```

## 样例 #3

### 输入

```
3 5

```

### 输出

```
451

```



---

---
title: "Cats Transport"
layout: "post"
diff: 省选/NOI-
pid: CF311B
tag: ['枚举', '斜率优化', '前缀和']
---

# Cats Transport

## 题目描述

Zxr960115 is owner of a large farm. He feeds $ m $ cute cats and employs $ p $ feeders. There's a straight road across the farm and $ n $ hills along the road, numbered from 1 to $ n $ from left to right. The distance between hill $ i $ and $ (i-1) $ is $ d_{i} $ meters. The feeders live in hill 1.

One day, the cats went out to play. Cat $ i $ went on a trip to hill $ h_{i} $ , finished its trip at time $ t_{i} $ , and then waited at hill $ h_{i} $ for a feeder. The feeders must take all the cats. Each feeder goes straightly from hill 1 to $ n $ without waiting at a hill and takes all the waiting cats at each hill away. Feeders walk at a speed of 1 meter per unit time and are strong enough to take as many cats as they want.

For example, suppose we have two hills $ (d_{2}=1) $ and one cat that finished its trip at time 3 at hill 2 $ (h_{1}=2) $ . Then if the feeder leaves hill 1 at time 2 or at time 3, he can take this cat, but if he leaves hill 1 at time 1 he can't take it. If the feeder leaves hill 1 at time 2, the cat waits him for 0 time units, if the feeder leaves hill 1 at time 3, the cat waits him for 1 time units.

Your task is to schedule the time leaving from hill 1 for each feeder so that the sum of the waiting time of all cats is minimized.

## 输入格式

The first line of the input contains three integers $n,m,p$ $(2 \le n\le 10^5,1 \le m \le 10^5, 1\le p \le 100)$.

The second line contains $n-1$ positive integers $d_{2},d_{3},...,d_{n}$  $(1 \le d_{i} < 10^{4}) .$

Each of the next $m$ lines contains two integers $h_i$ and $t_i$ $(1 \le h_i \le n,0 \le t_i \le 10^9)$.

## 输出格式

Output an integer, the minimum sum of waiting time of all cats.

Please, do not write the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 样例 #1

### 输入

```
4 6 2
1 3 5
1 0
2 1
4 9
1 10
2 10
3 12

```

### 输出

```
3

```



---

---
title: "Axis Walking"
layout: "post"
diff: 省选/NOI-
pid: CF327E
tag: ['状态合并', '进制', '前缀和']
---

# Axis Walking

## 题目描述

Iahub wants to meet his girlfriend Iahubina. They both live in $ Ox $ axis (the horizontal axis). Iahub lives at point 0 and Iahubina at point $ d $ .

Iahub has $ n $ positive integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ . The sum of those numbers is $ d $ . Suppose $ p_{1} $ , $ p_{2} $ , ..., $ p_{n} $ is a permutation of $ {1,2,...,n} $ . Then, let $ b_{1}=a_{p1} $ , $ b_{2}=a_{p2} $ and so on. The array b is called a "route". There are $ n! $ different routes, one for each permutation $ p $ .

Iahub's travel schedule is: he walks $ b_{1} $ steps on $ Ox $ axis, then he makes a break in point $ b_{1} $ . Then, he walks $ b_{2} $ more steps on $ Ox $ axis and makes a break in point $ b_{1}+b_{2} $ . Similarly, at $ j $ -th $ (1<=j<=n) $ time he walks $ b_{j} $ more steps on $ Ox $ axis and makes a break in point $ b_{1}+b_{2}+...+b_{j} $ .

Iahub is very superstitious and has $ k $ integers which give him bad luck. He calls a route "good" if he never makes a break in a point corresponding to one of those $ k $ numbers. For his own curiosity, answer how many good routes he can make, modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=24 $ ). The following line contains $ n $ integers: $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ).

The third line contains integer $ k $ ( $ 0<=k<=2 $ ). The fourth line contains $ k $ positive integers, representing the numbers that give Iahub bad luck. Each of these numbers does not exceed $ 10^{9} $ .

## 输出格式

Output a single integer — the answer of Iahub's dilemma modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

In the first case consider six possible orderings:

- \[2, 3, 5\]. Iahub will stop at position 2, 5 and 10. Among them, 5 is bad luck for him.
- \[2, 5, 3\]. Iahub will stop at position 2, 7 and 10. Among them, 7 is bad luck for him.
- \[3, 2, 5\]. He will stop at the unlucky 5.
- \[3, 5, 2\]. This is a valid ordering.
- \[5, 2, 3\]. He got unlucky twice (5 and 7).
- \[5, 3, 2\]. Iahub would reject, as it sends him to position 5.

In the second case, note that it is possible that two different ways have the identical set of stopping. In fact, all six possible ways have the same stops: \[2, 4, 6\], so there's no bad luck for Iahub.

## 样例 #1

### 输入

```
3
2 3 5
2
5 7

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3
2 2 2
2
1 3

```

### 输出

```
6

```



---

---
title: "On Changing Tree"
layout: "post"
diff: 省选/NOI-
pid: CF396C
tag: ['树状数组', '前缀和', '栈']
---

# On Changing Tree

## 题目描述

You are given a rooted tree consisting of $ n $ vertices numbered from $ 1 $ to $ n $ . The root of the tree is a vertex number $ 1 $ .

Initially all vertices contain number $ 0 $ . Then come $ q $ queries, each query has one of the two types:

- The format of the query: $ 1 $ $ v $ $ x $ $ k $ . In response to the query, you need to add to the number at vertex $ v $ number $ x $ ; to the numbers at the descendants of vertex $ v $ at distance $ 1 $ , add $ x-k $ ; and so on, to the numbers written in the descendants of vertex $ v $ at distance $ i $ , you need to add $ x-(i·k) $ . The distance between two vertices is the number of edges in the shortest path between these vertices.
- The format of the query: $ 2 $ $ v $ . In reply to the query you should print the number written in vertex $ v $ modulo $ 1000000007 $ $ (10^{9}+7) $ .

Process the queries given in the input.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=3·10^{5} $ ) — the number of vertices in the tree. The second line contains $ n-1 $ integers $ p_{2},p_{3},...\ p_{n} $ ( $ 1<=p_{i}&lt;i $ ), where $ p_{i} $ is the number of the vertex that is the parent of vertex $ i $ in the tree.

The third line contains integer $ q $ ( $ 1<=q<=3·10^{5} $ ) — the number of queries. Next $ q $ lines contain the queries, one per line. The first number in the line is $ type $ . It represents the type of the query. If $ type=1 $ , then next follow space-separated integers $ v,x,k $ ( $ 1<=v<=n $ ; $ 0<=x&lt;10^{9}+7 $ ; $ 0<=k&lt;10^{9}+7 $ ). If $ type=2 $ , then next follows integer $ v $ ( $ 1<=v<=n $ ) — the vertex where you need to find the value of the number.

## 输出格式

For each query of the second type print on a single line the number written in the vertex from the query. Print the number modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

You can read about a rooted tree here: http://en.wikipedia.org/wiki/Tree\_(graph\_theory).

## 样例 #1

### 输入

```
3
1 1
3
1 1 2 1
2 1
2 2

```

### 输出

```
2
1

```



---

---
title: "Levels and Regions"
layout: "post"
diff: 省选/NOI-
pid: CF643C
tag: ['斜率优化', '前缀和', '期望']
---

# Levels and Regions

## 题目描述

Radewoosh is playing a computer game. There are $ n $ levels, numbered $ 1 $ through $ n $ . Levels are divided into $ k $ regions (groups). Each region contains some positive number of consecutive levels.

The game repeats the the following process:

1. If all regions are beaten then the game ends immediately. Otherwise, the system finds the first region with at least one non-beaten level. Let $ X $ denote this region.
2. The system creates an empty bag for tokens. Each token will represent one level and there may be many tokens representing the same level.
  - For each already beaten level $ i $ in the region $ X $ , the system adds $ t_{i} $ tokens to the bag (tokens representing the $ i $ -th level).
  - Let $ j $ denote the first non-beaten level in the region $ X $ . The system adds $ t_{j} $ tokens to the bag.
3. Finally, the system takes a uniformly random token from the bag and a player starts the level represented by the token. A player spends one hour and beats the level, even if he has already beaten it in the past.

Given $ n $ , $ k $ and values $ t_{1},t_{2},...,t_{n} $ , your task is to split levels into regions. Each level must belong to exactly one region, and each region must contain non-empty consecutive set of levels. What is the minimum possible expected number of hours required to finish the game?

## 输入格式

The first line of the input contains two integers $ n $ and $ k $ ( $ 1<=n<=200000 $ , $ 1<=k<=min(50,n) $ ) — the number of levels and the number of regions, respectively.

The second line contains $ n $ integers $ t_{1},t_{2},...,t_{n} $ ( $ 1<=t_{i}<=100000 $ ).

## 输出格式

Print one real number — the minimum possible expected value of the number of hours spent to finish the game if levels are distributed between regions in the optimal way. Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-4} $ .

Namely: let's assume that your answer is $ a $ , and the answer of the jury is $ b $ . The checker program will consider your answer correct if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF643C/73b7e412a182af1e0d063e02722d13792ecaced8.png).

## 说明/提示

In the first sample, we are supposed to split $ 4 $ levels into $ 2 $ regions. It's optimal to create the first region with only one level (it must be the first level). Then, the second region must contain other three levels.

In the second sample, it's optimal to split levels into two regions with $ 3 $ levels each.

## 样例 #1

### 输入

```
4 2
100 3 5 7

```

### 输出

```
5.7428571429

```

## 样例 #2

### 输入

```
6 2
1 2 4 8 16 32

```

### 输出

```
8.5000000000

```



---

---
title: "Expected diameter of a tree"
layout: "post"
diff: 省选/NOI-
pid: CF804D
tag: ['树的直径', '前缀和', '期望']
---

# Expected diameter of a tree

## 题目描述

Pasha is a good student and one of MoJaK's best friends. He always have a problem to think about. Today they had a talk about the following problem.

We have a forest (acyclic undirected graph) with $ n $ vertices and $ m $ edges. There are $ q $ queries we should answer. In each query two vertices $ v $ and $ u $ are given. Let $ V $ be the set of vertices in the connected component of the graph that contains $ v $ , and $ U $ be the set of vertices in the connected component of the graph that contains $ u $ . Let's add an edge between some vertex ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF804D/8ef01bdc02f37e886781700f62479c92154da008.png) and some vertex in ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF804D/0479fe8afb5e9211cdac4c2d711ca0b8e2ad6e82.png) and compute the value $ d $ of the resulting component. If the resulting component is a tree, the value $ d $ is the diameter of the component, and it is equal to -1 otherwise. What is the expected value of $ d $ , if we choose vertices $ a $ and $ b $ from the sets uniformly at random?

Can you help Pasha to solve this problem?

The diameter of the component is the maximum distance among some pair of vertices in the component. The distance between two vertices is the minimum number of edges on some path between the two vertices.

Note that queries don't add edges to the initial forest.

## 输入格式

The first line contains three integers $ n $ , $ m $ and $ q $ ( $ 1<=n,m,q<=10^{5} $ ) — the number of vertices, the number of edges in the graph and the number of queries.

Each of the next $ m $ lines contains two integers $ u_{i} $ and $ v_{i} $ ( $ 1<=u_{i},v_{i}<=n $ ), that means there is an edge between vertices $ u_{i} $ and $ v_{i} $ .

It is guaranteed that the given graph is a forest.

Each of the next $ q $ lines contains two integers $ u_{i} $ and $ v_{i} $ ( $ 1<=u_{i},v_{i}<=n $ ) — the vertices given in the $ i $ -th query.

## 输出格式

For each query print the expected value of $ d $ as described in the problem statement.

Your answer will be considered correct if its absolute or relative error does not exceed $ 10^{-6} $ . Let's assume that your answer is $ a $ , and the jury's answer is $ b $ . The checker program will consider your answer correct, if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF804D/259203790d90e969d73ec841bd0673c1e8e7d69a.png).

## 说明/提示

In the first example the vertices $ 1 $ and $ 3 $ are in the same component, so the answer for the first query is -1. For the second query there are two options to add the edge: one option is to add the edge $ 1-2 $ , the other one is $ 2-3 $ . In both ways the resulting diameter is $ 2 $ , so the answer is $ 2 $ .

In the second example the answer for the first query is obviously -1. The answer for the second query is the average of three cases: for added edges $ 1-2 $ or $ 1-3 $ the diameter is $ 3 $ , and for added edge $ 1-4 $ the diameter is $ 2 $ . Thus, the answer is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF804D/80f05d9f9a5abbad800eeb11e2f309500aaccabe.png).

## 样例 #1

### 输入

```
3 1 2
1 3
3 1
2 3

```

### 输出

```
-1
2.0000000000

```

## 样例 #2

### 输入

```
5 2 3
2 4
4 3
4 2
4 1
2 5

```

### 输出

```
-1
2.6666666667
2.6666666667

```



---

---
title: "Karen and Cards"
layout: "post"
diff: 省选/NOI-
pid: CF815D
tag: ['枚举', '前缀和', '概率论']
---

# Karen and Cards

## 题目描述

Karen just got home from the supermarket, and is getting ready to go to sleep.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF815D/d6b07c74db93ed793c45ff910937379fe578d8dc.png)After taking a shower and changing into her pajamas, she looked at her shelf and saw an album. Curious, she opened it and saw a trading card collection.

She recalled that she used to play with those cards as a child, and, although she is now grown-up, she still wonders a few things about it.

Each card has three characteristics: strength, defense and speed. The values of all characteristics of all cards are positive integers. The maximum possible strength any card can have is $ p $ , the maximum possible defense is $ q $ and the maximum possible speed is $ r $ .

There are $ n $ cards in her collection. The $ i $ -th card has a strength $ a_{i} $ , defense $ b_{i} $ and speed $ c_{i} $ , respectively.

A card beats another card if at least two of its characteristics are strictly greater than the corresponding characteristics of the other card.

She now wonders how many different cards can beat all the cards in her collection. Two cards are considered different if at least one of their characteristics have different values.

## 输入格式

The first line of input contains four integers, $ n $ , $ p $ , $ q $ and $ r $ ( $ 1<=n,p,q,r<=500000 $ ), the number of cards in the collection, the maximum possible strength, the maximum possible defense, and the maximum possible speed, respectively.

The next $ n $ lines each contain three integers. In particular, the $ i $ -th line contains $ a_{i} $ , $ b_{i} $ and $ c_{i} $ ( $ 1<=a_{i}<=p $ , $ 1<=b_{i}<=q $ , $ 1<=c_{i}<=r $ ), the strength, defense and speed of the $ i $ -th collection card, respectively.

## 输出格式

Output a single integer on a line by itself, the number of different cards that can beat all the cards in her collection.

## 说明/提示

In the first test case, the maximum possible strength is $ 4 $ , the maximum possible defense is $ 4 $ and the maximum possible speed is $ 5 $ . Karen has three cards:

- The first card has strength $ 2 $ , defense $ 2 $ and speed $ 5 $ .
- The second card has strength $ 1 $ , defense $ 3 $ and speed $ 4 $ .
- The third card has strength $ 4 $ , defense $ 1 $ and speed $ 1 $ .

There are $ 10 $ cards that beat all the cards here:

1. The card with strength $ 3 $ , defense $ 3 $ and speed $ 5 $ .
2. The card with strength $ 3 $ , defense $ 4 $ and speed $ 2 $ .
3. The card with strength $ 3 $ , defense $ 4 $ and speed $ 3 $ .
4. The card with strength $ 3 $ , defense $ 4 $ and speed $ 4 $ .
5. The card with strength $ 3 $ , defense $ 4 $ and speed $ 5 $ .
6. The card with strength $ 4 $ , defense $ 3 $ and speed $ 5 $ .
7. The card with strength $ 4 $ , defense $ 4 $ and speed $ 2 $ .
8. The card with strength $ 4 $ , defense $ 4 $ and speed $ 3 $ .
9. The card with strength $ 4 $ , defense $ 4 $ and speed $ 4 $ .
10. The card with strength $ 4 $ , defense $ 4 $ and speed $ 5 $ .

In the second test case, the maximum possible strength is $ 10 $ , the maximum possible defense is $ 10 $ and the maximum possible speed is $ 10 $ . Karen has five cards, all with strength $ 1 $ , defense $ 1 $ and speed $ 1 $ .

Any of the $ 972 $ cards which have at least two characteristics greater than $ 1 $ can beat all of the cards in her collection.

## 样例 #1

### 输入

```
3 4 4 5
2 2 5
1 3 4
4 1 1

```

### 输出

```
10

```

## 样例 #2

### 输入

```
5 10 10 10
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1

```

### 输出

```
972

```



---

---
title: "Coprime Arrays"
layout: "post"
diff: 省选/NOI-
pid: CF915G
tag: ['数学', '前缀和', '差分']
---

# Coprime Arrays

## 题目描述

#### 题意：

我们称一个大小为 $n$ 的数组 $a$ 互质，当且仅当 $gcd(a_1,a_2,\cdots,a_n)=1$，$gcd$ 是最大公约数的意思。

给定 $n,k$，对于每个 $i$ $(1\le i\le k)$，你都需要确定这样的数组的个数——长度为 $n$ 的互质数组 $a$ ，满足对每个 $j$ $(1\le j\le n)$，都有 $1\le a_j\le i$。

答案可能非常大，请对 $10^9+7$ 取模。

## 输入格式

只有一行，两个数 $n,k$ $(1\le n,k\le 2\cdot10^6)$，分别表示数组的大小和数组元素大小的上限。

## 输出格式

为了降低输出的时间，你需要对输出进行如下处理：

把 $i$ 的答案（对 $10^9+7$ 取模后）记作 $b_i$。你需要输出 $\sum_{i=1}^{k} (b_i\oplus i)$，再对 $10^9+7$ 取模。

这里 $\oplus$ 表示按位异或，在 c++ 和 Java 中写作 ```^```，在 Pascal 中写作 ```xor```。

## 说明/提示

因为互质数组的数量比较多，我们只列出不互质的：

当 $i=1$ 时，唯一的数组就是互质的，$b_1=1$。

当 $i=2$ 时，数组 $[2,2,2]$ 不是互质的，$b_2=7$。

当 $i=3$ 时，数组 $[2,2,2],[3,3,3]$ 不是互质的，$b_3=25$。

当 $i=4$ 时，数组 $[2,2,2],[3,3,3],[2,2,4],[2,4,2],[2,4,4],[4,2,2],[4,2,4],[4,4,2],[4,4,4]$ 不是互质的，$b_4=55$。

Translated by 小粉兔

## 样例 #1

### 输入

```
3 4

```

### 输出

```
82

```

## 样例 #2

### 输入

```
2000000 8

```

### 输出

```
339310063

```



---

