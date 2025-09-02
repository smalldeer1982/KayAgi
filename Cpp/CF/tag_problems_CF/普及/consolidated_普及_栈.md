---
title: "Vasya and Books"
layout: "post"
diff: 普及/提高-
pid: CF1073B
tag: ['栈']
---

# Vasya and Books

## 题目描述

Vasya 有 $n$ 本书，编号从 $1$ 到 $n$，放在一个栈中，最上面的书的编号为 $a_{1}$，下一本书为 $a_{2}$，以此类推，栈底部的书编号为 $a_{n}$，所有书的数字都是不同的。

Vasya 想在 $n$ 次操作下，把所有书都移动到他的背包里，在第 $i$ 次操作中他想移动编号为 $b_{i}$ 的书到他的包里，如果这本书还在栈中，他将取走 $b_{i}$ 和 $b_{i}$ 以上的所有书，并且将它们都放到包里，否则他什么都不需要做，并且开始取下一本书。

请你帮助 Vasya，告诉他每一步他要取走几本书。

翻译提供：@Maysoul

## 输入格式

第一行只有一个整数 $n$，代表栈中书的数量。

第二行有 $n$ 个整数 $a_{1}, a_{2}, \ldots, a_{n}$ 表示栈中书的编号。

第三行有 $n$ 个整数 $b_{1}, b_2, \ldots, b_{n}$ 表示 Vasya 将要取走的书。

保证 $a_{1\sim n}$ 互不相同，$b_{1\sim n}$ 互不相同。

## 输出格式

输出 $n$ 个整数，代表在第 $i$ 步 Vasya 需要移动的书的数目，如不需移动则输出 $0$。

## 说明/提示

$1\le n \le 2\times 10^{5}$。

$1\le a_{i}, b_i \le n $。

$1\le b_{i} \le n $。


在样例 $2$ 中，第一步 Vasya 取走了编号为 $4$ 及以上的三本书，在那之后，只有编号为 $2$ 和 $5$ 的书还在栈中，并且 $2$ 在 $5$ 上面，在下一步 Vasya 取走了编号为 $5$ 及以上的两本书，在之后的操作中，没有书可以再被移动了。

## 样例 #1

### 输入

```
3
1 2 3
2 1 3

```

### 输出

```
2 0 1 

```

## 样例 #2

### 输入

```
5
3 1 4 2 5
4 5 1 3 2

```

### 输出

```
3 2 0 0 0 

```

## 样例 #3

### 输入

```
6
6 5 4 3 2 1
6 5 3 4 2 1

```

### 输出

```
1 1 2 0 1 1 

```



---

---
title: "LR-remainders"
layout: "post"
diff: 普及/提高-
pid: CF1932C
tag: ['栈']
---

# LR-remainders

## 题目描述

给定一个长度为 $n$ 的数组 $a$，一个正整数 $m$，以及一个长度为 $n$ 的命令字符串。每个命令要么是字符 `L`，要么是字符 `R`。

按照字符串 $s$ 中写入的顺序处理所有 $n$ 个命令。处理命令的步骤如下：

首先，输出数组 $a$ 中所有元素的乘积除以 $m$ 的余数。
然后，如果命令是 `L`，则从数组 $a$ 中移除最左边的元素；如果命令是 `R`，则从数组 $a$ 中移除最右边的元素。
请注意，每次移动后，数组 $a$ 的长度减少 $1$，并且在处理所有命令后，数组将为空。

编写一个程序，按照字符串 $s$ 中写入的顺序从左到右处理所有命令。

## 输入格式

第一行包含一个整数 $t$（$1\le t\le10^4$），表示输入中的测试数据数量。然后是 $t$ 个测试数据的描述。

输入的每个测试数据分 $3$ 出。

第一行包含两个整数 $n$ 和 $m$（$1\le n\le2\cdot10^5,1\le m\le10^4$）——数组 $a$ 的初始长度和取余数的值。

第二行包含 $n$ 个整数 $a_1,a_2,\dots,a_n$（$1\le a_i\le10^4$），数组 $a$ 的元素。

第三行包含一个由 $ n $ 个字符 `L` 和 `R` 组成的字符串 $s$。

保证一个测试用例中所有 $n$ 值的总和不超过 $2\cdot10^5$。

## 输出格式

对于每个测试用例，输出 $n$ 个整数 $b_1,b_2,\dots,b_n$，其中 $b_i$ 是在执行第 $i$ 个命令时，当前数组 $a$ 的所有元素的乘积除以 $m$ 的余数。

### 样例解释
在示例的第一个测试用例中：

- $ 3 \cdot 1 \cdot 4 \cdot 2 \bmod 6 = 24 \bmod 6 = 0 $；
- $ s_1 = \text{L} $，因此我们移除第一个元素，得到数组 $ [1, 4, 2] $；
- $ 1 \cdot 4 \cdot 2 \bmod 6 = 8 \bmod 6 = 2 $；
- $ s_2 = \text{R} $，因此我们移除最后一个元素，得到数组 $ [1, 4] $；
- $ 1 \cdot 4 \bmod 6 = 4 \bmod 6 = 4 $；
- $ s_3 = \text{R} $，因此我们移除最后一个元素，得到数组 $ [1] $；
- $ 1 \bmod 6 = 1 $；
- $ s_4 = \text{L} $，因此我们移除第一个元素，得到一个空数组。

## 样例 #1

### 输入

```
4
4 6
3 1 4 2
LRRL
5 1
1 1 1 1 1
LLLLL
6 8
1 2 3 4 5 6
RLLLRR
1 10000
10000
R
```

### 输出

```
0 2 4 1 
0 0 0 0 0 
0 0 0 4 4 4 
0
```



---

---
title: "Regular Bracket Sequence"
layout: "post"
diff: 普及/提高-
pid: CF26B
tag: ['栈']
---

# Regular Bracket Sequence

## 题目描述

A bracket sequence is called regular if it is possible to obtain correct arithmetic expression by inserting characters «+» and «1» into this sequence. For example, sequences «(())()», «()» and «(()(()))» are regular, while «)(», «(()» and «(()))(» are not.

One day Johnny got bracket sequence. He decided to remove some of the brackets from it in order to obtain a regular bracket sequence. What is the maximum length of a regular bracket sequence which can be obtained?

## 输入格式

Input consists of a single line with non-empty string of «(» and «)» characters. Its length does not exceed $ 10^{6} $ .

## 输出格式

Output the maximum possible length of a regular bracket sequence.

## 样例 #1

### 输入

```
(()))(

```

### 输出

```
4

```

## 样例 #2

### 输入

```
((()())

```

### 输出

```
6

```



---

---
title: "Winner"
layout: "post"
diff: 普及/提高-
pid: CF2A
tag: ['模拟', '字符串', '概率论', '栈']
---

# Winner

## 题目描述

在 Berland 流行着纸牌游戏 `Berlogging`，这个游戏的赢家是根据以下规则确定的：

1. 在每一轮中，玩家获得或失去一定数量的分数，在游戏过程中，分数被记录在 `名称和得分` 行中，其中名字是玩家的名字，得分是在这一轮中获得的分数。得分是负值意味着玩家失去了相应的分数。
2. 如果在比赛结束时只有一名玩家分数最多，他就是获胜者。
3. 如果两名或两名以上的玩家在比赛结束时都有最大的分数 $m$ ，那么其中首先获得至少 $m$ 分的玩家胜利。开始时，每个玩家都是 $0$ 分。


保证在比赛结束时至少有一个玩家的分数为正。

## 输入格式

第一行包含整数 $n$，表示是游戏进行的的回合数。

第 $2 \sim n + 1$ 行，按照时间顺序输入 `名称和得分` 行的信息，其中名称是长度不大于 $32$ 的小写字母组成的字符串，分数的绝对值不大于 $1000$。

## 输出格式

输出获胜者的名称。

## 样例 #1

### 输入

```
3
mike 3
andrew 5
mike 2

```

### 输出

```
andrew

```

## 样例 #2

### 输入

```
3
andrew 3
andrew 2
mike 5

```

### 输出

```
andrew

```



---

---
title: "Maze"
layout: "post"
diff: 普及/提高-
pid: CF377A
tag: ['深度优先搜索 DFS', '栈']
---

# Maze

## 题目描述

Pavel loves grid mazes. A grid maze is an $ n×m $ rectangle maze where each cell is either empty, or is a wall. You can go from one cell to another only if both cells are empty and have a common side.

Pavel drew a grid maze with all empty cells forming a connected area. That is, you can go from any empty cell to any other one. Pavel doesn't like it when his maze has too little walls. He wants to turn exactly $ k $ empty cells into walls so that all the remaining cells still formed a connected area. Help him.

## 输入格式

The first line contains three integers $ n $ , $ m $ , $ k $ ( $ 1<=n,m<=500 $ , $ 0<=k&lt;s $ ), where $ n $ and $ m $ are the maze's height and width, correspondingly, $ k $ is the number of walls Pavel wants to add and letter $ s $ represents the number of empty cells in the original maze.

Each of the next $ n $ lines contains $ m $ characters. They describe the original maze. If a character on a line equals ".", then the corresponding cell is empty and if the character equals "\#", then the cell is a wall.

## 输出格式

Print $ n $ lines containing $ m $ characters each: the new maze that fits Pavel's requirements. Mark the empty cells that you transformed into walls as "X", the other cells must be left without changes (that is, "." and "\#").

It is guaranteed that a solution exists. If there are multiple solutions you can output any of them.

## 样例 #1

### 输入

```
3 4 2
#..#
..#.
#...

```

### 输出

```
#.X#
X.#.
#...

```

## 样例 #2

### 输入

```
5 4 5
#...
#.#.
.#..
...#
.#.#

```

### 输出

```
#XXX
#X#.
X#..
...#
.#.#

```



---

---
title: "Longest Regular Bracket Sequence"
layout: "post"
diff: 普及/提高-
pid: CF5C
tag: ['字符串', '动态规划 DP', '栈']
---

# Longest Regular Bracket Sequence

## 题目描述

This is yet another problem dealing with regular bracket sequences.

We should remind you that a bracket sequence is called regular, if by inserting «+» and «1» into it we can get a correct mathematical expression. For example, sequences «(())()», «()» and «(()(()))» are regular, while «)(», «(()» and «(()))(» are not.

You are given a string of «(» and «)» characters. You are to find its longest substring that is a regular bracket sequence. You are to find the number of such substrings as well.

## 输入格式

The first line of the input file contains a non-empty string, consisting of «(» and «)» characters. Its length does not exceed $ 10^{6} $ .

## 输出格式

Print the length of the longest substring that is a regular bracket sequence, and the number of such substrings. If there are no such substrings, write the only line containing "0 1".

## 样例 #1

### 输入

```
)((())))(()())

```

### 输出

```
6 2

```

## 样例 #2

### 输入

```
))(

```

### 输出

```
0 1

```



---

---
title: "Okabe and Boxes"
layout: "post"
diff: 普及/提高-
pid: CF821C
tag: ['栈']
---

# Okabe and Boxes

## 题目描述

Okabe and Super Hacker Daru are stacking and removing boxes. There are $ n $ boxes numbered from $ 1 $ to $ n $ . Initially there are no boxes on the stack.

Okabe, being a control freak, gives Daru $ 2n $ commands: $ n $ of which are to add a box to the top of the stack, and $ n $ of which are to remove a box from the top of the stack and throw it in the trash. Okabe wants Daru to throw away the boxes in the order from $ 1 $ to $ n $ . Of course, this means that it might be impossible for Daru to perform some of Okabe's remove commands, because the required box is not on the top of the stack.

That's why Daru can decide to wait until Okabe looks away and then reorder the boxes in the stack in any way he wants. He can do it at any point of time between Okabe's commands, but he can't add or remove boxes while he does it.

Tell Daru the minimum number of times he needs to reorder the boxes so that he can successfully complete all of Okabe's commands. It is guaranteed that every box is added before it is required to be removed.

## 输入格式

The first line of input contains the integer $ n $ ( $ 1<=n<=3·10^{5} $ ) — the number of boxes.

Each of the next $ 2n $ lines of input starts with a string "add" or "remove". If the line starts with the "add", an integer $ x $ ( $ 1<=x<=n $ ) follows, indicating that Daru should add the box with number $ x $ to the top of the stack.

It is guaranteed that exactly $ n $ lines contain "add" operations, all the boxes added are distinct, and $ n $ lines contain "remove" operations. It is also guaranteed that a box is always added before it is required to be removed.

## 输出格式

Print the minimum number of times Daru needs to reorder the boxes to successfully complete all of Okabe's commands.

## 说明/提示

In the first sample, Daru should reorder the boxes after adding box $ 3 $ to the stack.

In the second sample, Daru should reorder the boxes after adding box $ 4 $ and box $ 7 $ to the stack.

## 样例 #1

### 输入

```
3
add 1
remove
add 2
add 3
remove
remove

```

### 输出

```
1

```

## 样例 #2

### 输入

```
7
add 3
add 2
add 1
remove
add 4
remove
remove
remove
add 6
add 7
add 5
remove
remove
remove

```

### 输出

```
2

```



---

