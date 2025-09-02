# Yaroslav and Algorithm

## 题目描述

Yaroslav likes algorithms. We'll describe one of his favorite algorithms.

1. The algorithm receives a string as the input. We denote this input string as $ a $ .
2. The algorithm consists of some number of command. Сommand number $ i $ looks either as $ s_{i} $ >> $ w_{i} $ , or as $ s_{i} $ <> $ w_{i} $ , where $ s_{i} $ and $ w_{i} $ are some possibly empty strings of length at most $ 7 $ , consisting of digits and characters "?".
3. At each iteration, the algorithm looks for a command with the minimum index $ i $ , such that $ s_{i} $ occurs in $ a $ as a substring. If this command is not found the algorithm terminates.
4. Let's denote the number of the found command as $ k $ . In string $ a $ the first occurrence of the string $ s_{k} $ is replaced by string $ w_{k} $ . If the found command at that had form $ s_{k} $ >> $ w_{k} $ , then the algorithm continues its execution and proceeds to the next iteration. Otherwise, the algorithm terminates.
5. The value of string $ a $ after algorithm termination is considered to be the output of the algorithm.

Yaroslav has a set of $ n $ positive integers, he needs to come up with his favorite algorithm that will increase each of the given numbers by one. More formally, if we consider each number as a string representing the decimal representation of the number, then being run on each of these strings separately, the algorithm should receive the output string that is a recording of the corresponding number increased by one.

Help Yaroslav.

## 样例 #1

### 输入

```
2
10
79
```

### 输出

```
10<>11
79<>80
```

# 题解

## 作者：s4CRIF1CbUbbL3AtIAly (赞：1)

你要写一种很新的代码，使得这个代码每次从头到尾执行第一个有效替换（可能同时中止程序）后新的数变为原本的数 $+1$。

注意到问号是一个可以使用的符号，我们要用它来表示进位。

那么要做的第一步就是把问号移到最后面。

首先我们在整个代码的最后加一个 `>>?`，这样它就会在开头出现一个问号。

接下来就是直接移动：

```
?0>>0?
?1>>1?
?2>>2?
?3>>3?
?4>>4?
?5>>5?
?6>>6?
?7>>7?
?8>>8?
?9>>9?
```

这样它就出现在了最后，我们就可以直接进行加法了。因为问号表示的是它前面一位存在进位，所以只要前一位不是 9 就可以停止。

```
0?<>1
1?<>2
2?<>3
3?<>4
4?<>5
5?<>6
6?<>7
7?<>8
8?<>9
9?>>?0
```

写到这好像就结束了，结果突然发现这个程序好像爆炸了？？？

思考一下，发现如果这个问号被移到了前面并且没有消失，它就会又被后面的操作移回去。

为了避免这个问题，我们把上面这段改成两个问号：

```
0??<>1
1??<>2
2??<>3
3??<>4
4??<>5
5??<>6
6??<>7
7??<>8
8??<>9
9??>>??0
```

当一个问号添加到最后时，因为前面并没有任何其它合法操作，因此会又在开头出现一个问号并到最后。这样我们只要带着两个问号操作即可。

但是这个时候还是会在 $9999\dots9$ 的情况炸掉，因此我们再前面这一段之后加上一句：

```
??<>1
```

于是就解决了。

```
0??<>1
1??<>2
2??<>3
3??<>4
4??<>5
5??<>6
6??<>7
7??<>8
8??<>9
9??>>??0
??<>1
?0>>0?
?1>>1?
?2>>2?
?3>>3?
?4>>4?
?5>>5?
?6>>6?
?7>>7?
?8>>8?
?9>>9?
>>?
```

---

## 作者：Aiopr_2378 (赞：1)

Solution of CF301C Yaroslav and Algorithm

## 解题思路

很好的构造题。

因为我们需要让每个数都加一，必可避免地需要定位到**每个数的末尾位置**。所以我们可以把 $\texttt{?}$ 当做位置标记符，经过如下构造：

### P1.

我们需要插入位置标记符号，可以找到一个位置，进行如下构造：

```
0>>0?
1>>1?
2>>2?
3>>3?
4>>4?
5>>5?
6>>6?
7>>7?
8>>8?
9>>9?
```

因为我们只能加入一个 $\texttt{?}$，所以上述代码必须放到最后位置，使得程序运行时只能经过一次。

### P2.

我们需要讲 $\texttt{?}$ 符号移动到序列末尾位置，进行如下构造：

```
?0>>0?
?1>>1?
?2>>2?
?3>>3?
?4>>4?
?5>>5?
?6>>6?
?7>>7?
?8>>8?
?9>>9?
```

### P3.

我们需要对序列末尾的数字 $+1$，进行如下构造：

```
0?<>1
1?<>2
2?<>3
3?<>4
4?<>5
5?<>6
6?<>7
7?<>8
8?<>9
```

注意加数后就要结束程序。

特别地，对于末尾是 $9$ 的数，需要向上进位，即需要让 $\texttt{?}$ 向前移动，但是移动到前面后会和 P2 中的代码冲突，进而都移动回来。所以考虑将 $\texttt{?}$ 变为 $\texttt{??}$ 并提高优先级，即

```
9?>>??0
```

### P4.

对于进位的，向前移动标记符并进位，如下：

```
0??<>1
1??<>2
2??<>3
3??<>4
4??<>5
5??<>6
6??<>7
7??<>8
8??<>9
```

注意优先级需要比 P2 高，进行后结束程序。

特殊地，对于还需要进位的 $9$，继续前移：

```
9??>>??0
```

注意如果都运行后若到数列开头则变为 $1$，例如 $9999999\to 10000000$。

```
??<>1
```

## 参考构造

如下：

```
0??<>1
1??<>2
2??<>3
3??<>4
4??<>5
5??<>6
6??<>7
7??<>8
8??<>9
9??>>??0
??<>1
?0>>0?
?1>>1?
?2>>2?
?3>>3?
?4>>4?
?5>>5?
?6>>6?
?7>>7?
?8>>8?
?9>>9?
9?>>??0
0?<>1
1?<>2
2?<>3
3?<>4
4?<>5
5?<>6
6?<>7
7?<>8
8?<>9
0>>0?
1>>1?
2>>2?
3>>3?
4>>4?
5>>5?
6>>6?
7>>7?
8>>8?
9>>9?

```

---

## 作者：Leap_Frog (赞：0)

### P.S.
[恭喜你找到了原题！](https://mao.snuke.org/tasks/10)  

### Description.
略

### Solution.
首先考虑 `?` 的作用。  
相当于就是一个标志符。  
我们考虑一个很 `Naive` 的做法，用 `?` 作为一个标记。  
先把 `?` 移到最后一位，然后再把 `?` 前的一个数字加一。  
如果那个数字是 $9$，我们就把 `?` 前移，否则 `?` 就清空。  
这样看上去很对，但是 WA 了。  

经手模，我们发现 `?` 前移后会被移到后面的操作冲突  
所以我们加两个 `?` 即可。  

然后就 WA on test 2 了。  
考虑如果有 `999..999`，这样搞完后会变成 `??00000000`  
我们再把最开头的 `??` 去掉即可。  

然后就做完了。   

### Coding.
```php
0??<>1
1??<>2
2??<>3
3??<>4
4??<>5
5??<>6
6??<>7
7??<>8
8??<>9
9??>>??0
??<>1
?0>>0?
?1>>1?
?2>>2?
?3>>3?
?4>>4?
?5>>5?
?6>>6?
?7>>7?
?8>>8?
?9>>9?
>>?
```

---

## 作者：xyf007 (赞：0)

> 有一种程序，以一个字符串 $a$ 为输入，包括一些操作。
> 1. 每一次操作有两种，形如 $s_i>>w_i$ 或 $s_i<>w_i$，其中 $s_i,w_i$ 是长度不超过 $7$ 的只包含数字和 `?` 的字符串。
> 2. 运行这个程序会多次按顺序遍历所有的操作。每次遍历会找到第一个操作 $i$ 满足 $s_i$ 是 $a$ 的子串并将 $a$ 中的第一个 $s_i$ 替换成 $w_i$。如果找不到这样的操作，则程序停止。否则如果操作 $i$ 是形如 $s_i>>w_i$ 的，那么开始新一轮遍历，否则程序停止。
> 3. 程序的输出就是程序停止时的 $a$。
>
> 现在给出 $n$ 个数 $a_1,a_2,\ldots,a_n$，请你构造一个程序，要求对于每一个输入的 $a_i$，输出 $a_i+1$。

~~这个读入是拿来诈骗的，实际上根本不需要读入。~~  
注意到这个 `?` 很奇怪，实际上是人工模拟加法的时候要用他来指示我们做到哪里。用 `??` 来指示我们当前需要加一的位置。则对于 `0??`、`1??`……`8??`，实际上我们已经做完了，直接 `0??<>1`、`1??<>2`，以此类推。而 `9??` 需要进位，变成 `??0` 即可。如果最后进到了首位，还需要 `??<>1`。  
而一开始我们要先放两个问号，因此要有 `>>?` 来放问号，`0?>>?0` 等来向后移动。  
注意各个操作的先后顺序。另外在 CF 的评测机上 `??<` 会自动转义成 `{`，而且结尾不能有多余的换行，注意自己的输出。~~也可以使用 Python。~~
```python
print("0??<>1\n1??<>2\n2??<>3\n3??<>4\n4??<>5\n5??<>6\n6??<>7\n7??<>8\n8??<>9\n9??>>??0\n??<>1\n?0>>0?\n?1>>1?\n?2>>2?\n?3>>3?\n?4>>4?\n?5>>5?\n?6>>6?\n?7>>7?\n?8>>8?\n?9>>9?\n>>?\n", end='')
```

---

