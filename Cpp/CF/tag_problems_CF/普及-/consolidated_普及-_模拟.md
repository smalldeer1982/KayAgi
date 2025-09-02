---
title: "Binary String Constructing"
layout: "post"
diff: 普及-
pid: CF1003B
tag: ['模拟', '构造']
---

# Binary String Constructing

## 题目描述

给你 $3$ 个整数 $a$ ,$b$ ,$x$ ，让你求出一个包含了 $a$ 个 $0$，$b$ 个 $1$ 的二进制串 $s$。要求其中 $s_i\not =s_{i+1}$ 的对数正好等于 $x$。

## 输入格式

一行 $3$ 个整数 $a$ ,$b$ ,$x$。

## 输出格式

一行一个字符串 $s$ ,表示**任意**一符合要求的答案。

### 输入输出样例
无。

感谢 @win10 提供的翻译。

## 样例 #1

### 输入

```
2 2 1

```

### 输出

```
1100

```

## 样例 #2

### 输入

```
3 3 3

```

### 输出

```
101100

```

## 样例 #3

### 输入

```
5 3 6

```

### 输出

```
01010100

```



---

---
title: "Doggo Recoloring"
layout: "post"
diff: 普及-
pid: CF1025A
tag: ['模拟', '概率论']
---

# Doggo Recoloring

## 题目描述

Panic is rising in the committee for doggo standardization — the puppies of the new brood have been born multi-colored! In total there are 26 possible colors of puppies in the nature and they are denoted by letters from 'a' to 'z' inclusive.

The committee rules strictly prohibit even the smallest diversity between doggos and hence all the puppies should be of the same color. Thus Slava, the committee employee, has been assigned the task to recolor some puppies into other colors in order to eliminate the difference and make all the puppies have one common color.

Unfortunately, due to bureaucratic reasons and restricted budget, there's only one operation Slava can perform: he can choose a color $ x $ such that there are currently at least two puppies of color $ x $ and recolor all puppies of the color $ x $ into some arbitrary color $ y $ . Luckily, this operation can be applied multiple times (including zero).

For example, if the number of puppies is $ 7 $ and their colors are represented as the string "abababc", then in one operation Slava can get the results "zbzbzbc", "bbbbbbc", "aaaaaac", "acacacc" and others. However, if the current color sequence is "abababc", then he can't choose $ x $ ='c' right now, because currently only one puppy has the color 'c'.

Help Slava and the committee determine whether it is possible to standardize all the puppies, i.e. after Slava's operations all the puppies should have the same color.

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the number of puppies.

The second line contains a string $ s $ of length $ n $ consisting of lowercase Latin letters, where the $ i $ -th symbol denotes the $ i $ -th puppy's color.

## 输出格式

If it's possible to recolor all puppies into one color, print "Yes".

Otherwise print "No".

Output the answer without quotation signs.

## 说明/提示

In the first example Slava can perform the following steps:

1. take all puppies of color 'a' (a total of two) and recolor them into 'b';
2. take all puppies of color 'd' (a total of two) and recolor them into 'c';
3. take all puppies of color 'b' (three puppies for now) and recolor them into 'c'.

In the second example it's impossible to recolor any of the puppies.

In the third example all the puppies' colors are the same; thus there's no need to recolor anything.

## 样例 #1

### 输入

```
6
aabddc

```

### 输出

```
Yes

```

## 样例 #2

### 输入

```
3
abc

```

### 输出

```
No

```

## 样例 #3

### 输入

```
3
jjj

```

### 输出

```
Yes

```



---

---
title: "Odd Sum Segments"
layout: "post"
diff: 普及-
pid: CF1196B
tag: ['模拟', '贪心']
---

# Odd Sum Segments

## 题目描述

You are given an array $ a $ consisting of $ n $ integers $ a_1, a_2, \dots, a_n $ . You want to split it into exactly $ k $ non-empty non-intersecting subsegments such that each subsegment has odd sum (i. e. for each subsegment, the sum of all elements that belong to this subsegment is odd). It is impossible to rearrange (shuffle) the elements of a given array. Each of the $ n $ elements of the array $ a $ must belong to exactly one of the $ k $ subsegments.

Let's see some examples of dividing the array of length $ 5 $ into $ 3 $ subsegments (not necessarily with odd sums): $ [1, 2, 3, 4, 5] $ is the initial array, then all possible ways to divide it into $ 3 $ non-empty non-intersecting subsegments are described below:

- $ [1], [2], [3, 4, 5] $ ;
- $ [1], [2, 3], [4, 5] $ ;
- $ [1], [2, 3, 4], [5] $ ;
- $ [1, 2], [3], [4, 5] $ ;
- $ [1, 2], [3, 4], [5] $ ;
- $ [1, 2, 3], [4], [5] $ .

Of course, it can be impossible to divide the initial array into exactly $ k $ subsegments in such a way that each of them will have odd sum of elements. In this case print "NO". Otherwise, print "YES" and any possible division of the array. See the output format for the detailed explanation.

You have to answer $ q $ independent queries.

## 输入格式

The first line contains one integer $ q $ ( $ 1 \le q \le 2 \cdot 10^5 $ ) — the number of queries. Then $ q $ queries follow.

The first line of the query contains two integers $ n $ and $ k $ ( $ 1 \le k \le n \le 2 \cdot 10^5 $ ) — the number of elements in the array and the number of subsegments, respectively.

The second line of the query contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ), where $ a_i $ is the $ i $ -th element of $ a $ .

It is guaranteed that the sum of $ n $ over all queries does not exceed $ 2 \cdot 10^5 $ ( $ \sum n \le 2 \cdot 10^5 $ ).

## 输出格式

For each query, print the answer to it. If it is impossible to divide the initial array into exactly $ k $ subsegments in such a way that each of them will have odd sum of elements, print "NO" in the first line. Otherwise, print "YES" in the first line and any possible division of the array in the second line. The division can be represented as $ k $ integers $ r_1 $ , $ r_2 $ , ..., $ r_k $ such that $ 1 \le r_1 < r_2 < \dots < r_k = n $ , where $ r_j $ is the right border of the $ j $ -th segment (the index of the last element that belongs to the $ j $ -th segment), so the array is divided into subsegments $ [1; r_1], [r_1 + 1; r_2], [r_2 + 1, r_3], \dots, [r_{k - 1} + 1, n] $ . Note that $ r_k $ is always $ n $ but you should print it anyway.

## 样例 #1

### 输入

```
3
5 3
7 18 3 14 1
5 4
1 2 3 4 5
6 2
1 2 8 4 10 2

```

### 输出

```
YES
1 3 5
NO
NO

```



---

---
title: "Numbers"
layout: "post"
diff: 普及-
pid: CF13A
tag: ['模拟', '最大公约数 gcd', '进制']
---

# Numbers

## 题目描述

Little Petya likes numbers a lot. He found that number 123 in base 16 consists of two digits: the first is 7 and the second is 11. So the sum of digits of 123 in base 16 is equal to 18.

Now he wonders what is an average value of sum of digits of the number $ A $ written in all bases from $ 2 $ to $ A-1 $ .

Note that all computations should be done in base 10. You should find the result as an irreducible fraction, written in base 10.

## 输入格式

Input contains one integer number $ A $ ( $ 3<=A<=1000 $ ).

## 输出格式

Output should contain required average value in format «X/Y», where X is the numerator and Y is the denominator.

## 说明/提示

In the first sample number 5 written in all bases from 2 to 4 looks so: 101, 12, 11. Sums of digits are 2, 3 and 2, respectively.

## 样例 #1

### 输入

```
5

```

### 输出

```
7/3

```

## 样例 #2

### 输入

```
3

```

### 输出

```
2/1

```



---

---
title: "Permutation Minimization by Deque"
layout: "post"
diff: 普及-
pid: CF1579E1
tag: ['模拟', '队列']
---

# Permutation Minimization by Deque

## 题目描述

In fact, the problems E1 and E2 do not have much in common. You should probably think of them as two separate problems.

A permutation $ p $ of size $ n $ is given. A permutation of size $ n $ is an array of size $ n $ in which each integer from $ 1 $ to $ n $ occurs exactly once. For example, $ [1, 4, 3, 2] $ and $ [4, 2, 1, 3] $ are correct permutations while $ [1, 2, 4] $ and $ [1, 2, 2] $ are not.

Let us consider an empty [deque](https://tinyurl.com/pfeucbux) (double-ended queue). A deque is a data structure that supports adding elements to both the beginning and the end. So, if there are elements $ [1, 5, 2] $ currently in the deque, adding an element $ 4 $ to the beginning will produce the sequence $ [\color{red}{4}, 1, 5, 2] $ , and adding same element to the end will produce $ [1, 5, 2, \color{red}{4}] $ .

The elements of the permutation are sequentially added to the initially empty deque, starting with $ p_1 $ and finishing with $ p_n $ . Before adding each element to the deque, you may choose whether to add it to the beginning or the end.

For example, if we consider a permutation $ p = [3, 1, 2, 4] $ , one of the possible sequences of actions looks like this:

 $ \quad $ 1.add $ 3 $ to the end of the deque:deque has a sequence $ [\color{red}{3}] $ in it; $ \quad $ 2.add $ 1 $ to the beginning of the deque:deque has a sequence $ [\color{red}{1}, 3] $ in it; $ \quad $ 3.add $ 2 $ to the end of the deque:deque has a sequence $ [1, 3, \color{red}{2}] $ in it; $ \quad $ 4.add $ 4 $ to the end of the deque:deque has a sequence $ [1, 3, 2, \color{red}{4}] $ in it;Find the lexicographically smallest possible sequence of elements in the deque after the entire permutation has been processed.

A sequence $ [x_1, x_2, \ldots, x_n] $ is lexicographically smaller than the sequence $ [y_1, y_2, \ldots, y_n] $ if there exists such $ i \leq n $ that $ x_1 = y_1 $ , $ x_2 = y_2 $ , $ \ldots $ , $ x_{i - 1} = y_{i - 1} $ and $ x_i < y_i $ . In other words, if the sequences $ x $ and $ y $ have some (possibly empty) matching prefix, and the next element of the sequence $ x $ is strictly smaller than the corresponding element of the sequence $ y $ . For example, the sequence $ [1, 3, 2, 4] $ is smaller than the sequence $ [1, 3, 4, 2] $ because after the two matching elements $ [1, 3] $ in the start the first sequence has an element $ 2 $ which is smaller than the corresponding element $ 4 $ in the second sequence.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

The next $ 2t $ lines contain descriptions of the test cases.

The first line of each test case description contains an integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — permutation size. The second line of the description contains $ n $ space-separated integers $ p_i $ ( $ 1 \le p_i \le n $ ; all $ p_i $ are all unique) — elements of the permutation.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

Print $ t $ lines, each line containing the answer to the corresponding test case. The answer to a test case should contain $ n $ space-separated integer numbers — the elements of the lexicographically smallest permutation that is possible to find in the deque after executing the described algorithm.

## 说明/提示

One of the ways to get a lexicographically smallest permutation $ [1, 3, 2, 4] $ from the permutation $ [3, 1, 2, 4] $ (the first sample test case) is described in the problem statement.

## 样例 #1

### 输入

```
5
4
3 1 2 4
3
3 2 1
3
3 1 2
2
1 2
2
2 1
```

### 输出

```
1 3 2 4 
1 2 3 
1 3 2 
1 2 
1 2
```



---

---
title: "Next Round"
layout: "post"
diff: 普及-
pid: CF158A
tag: ['模拟']
---

# Next Round

## 题目描述

# CF158  Next Round 下一轮   
# 题意简述  
有$n$个人参加一场比赛，其中分数排名前$k$位的人将被选入下一轮（选入下一轮的人分数必须为正，见样例#2），特别的，如果几个人分数相同且刚好并列处于第$k$名（或是并列$k-i$名，但是全部算入后选入下一轮的人数超过$k$人），这几个人都将被选入下一轮（见样例#1），题目要求你输出进入下一轮的人数。输入保证已经按分数从大到小排序。

## 输入格式

输入一共$2$行：  
第$1$行是两个数$n,k$，分别代表参加比赛的人数和预计将会进入下一轮的人数；  
第$2$行有$n$个数，分别参加比赛的人的分数 $a_1,a_2,...,a_n$ 。（输入保证 $a_i \geq  a_{i+1}$）

## 输出格式

输出一个正整数，即实际进入下一轮的人数。

## 说明/提示

在样例#1中，第五位和第六位参赛者都获得了七分，所以有六人进入下一轮。  
在样例#2中，没有人得到大于0的评分。  

翻译提供者：n0000000000o

## 样例 #1

### 输入

```
8 5
10 9 8 7 7 7 5 5

```

### 输出

```
6

```

## 样例 #2

### 输入

```
4 2
0 0 0 0

```

### 输出

```
0

```



---

---
title: "Divine Array"
layout: "post"
diff: 普及-
pid: CF1602B
tag: ['模拟']
---

# Divine Array

## 题目描述

给定一个序列，一次转换是将一个数变成这个数在这个序列中出现的次数。

序列 $\{2,1,1,4,3,1,2\}$ 中，$2$ 出现 $2$ 次，$1$ 出现 $3$ 次，$3$ 和 $4$ 出现 $1$ 次，那么这个序列进行一次转换之后就变成了 $\{2,3,3,1,1,3,2\}$，同理，进行两次转换后是 $\{2,3,3,2,2,3,2\}$，进行三次转换后是 $\{4,3,3,4,4,3,4\}$。

有 $q$ 次询问，每次询问第 $x$ 个位置的元素经过 $k$ 次转换之后是什么。

## 输入格式

第一行输入一个正整数 $t$ 表示数据组数。

对于每一组数据：
- 第一行输入一个正整数 $n$ 表示序列长度。
- 第二行输入 $n$ 个正整数 $a_i$ 表示初始序列。
- 第三行输入一个正整数 $q$ 表示询问次数。

## 输出格式

对于每一个询问输出一行一个正整数表示答案。

## 说明/提示

$1\le t\le1000,1\le\sum n\le2000,1\le a_i,x\le n,1\le\sum q\le10^5，0\le k\le10^9$。

## 样例 #1

### 输入

```
2
7
2 1 1 4 3 1 2
4
3 0
1 1
2 2
6 1
2
1 1
2
1 0
2 1000000000
```

### 输出

```
1
2
3
3
1
2
```



---

---
title: "Wrong Addition"
layout: "post"
diff: 普及-
pid: CF1619C
tag: ['模拟']
---

# Wrong Addition

## 题目描述

Tanya is learning how to add numbers, but so far she is not doing it correctly. She is adding two numbers $ a $ and $ b $ using the following algorithm:

1. If one of the numbers is shorter than the other, Tanya adds leading zeros so that the numbers are the same length.
2. The numbers are processed from right to left (that is, from the least significant digits to the most significant).
3. In the first step, she adds the last digit of $ a $ to the last digit of $ b $ and writes their sum in the answer.
4. At each next step, she performs the same operation on each pair of digits in the same place and writes the result to the left side of the answer.

For example, the numbers $ a = 17236 $ and $ b = 3465 $ Tanya adds up as follows:

 $ $$$ \large{ \begin{array}{r} + \begin{array}{r} 17236\\ 03465\\ \end{array} \\ \hline \begin{array}{r} 1106911 \end{array} \end{array}}  $ $ </p><ul> <li> calculates the sum of  $ 6 + 5 = 11 $  and writes  $ 11 $  in the answer. </li><li> calculates the sum of  $ 3 + 6 = 9 $  and writes the result to the left side of the answer to get  $ 911 $ . </li><li> calculates the sum of  $ 2 + 4 = 6 $  and writes the result to the left side of the answer to get  $ 6911 $ . </li><li> calculates the sum of  $ 7 + 3 = 10 $ , and writes the result to the left side of the answer to get  $ 106911 $ . </li><li> calculates the sum of  $ 1 + 0 = 1 $  and writes the result to the left side of the answer and get  $ 1106911 $ . </li></ul><p>As a result, she gets  $ 1106911 $ .</p><p>You are given two positive integers  $ a $  and  $ s $ . Find the number  $ b $  such that by adding  $ a $  and  $ b $  as described above, Tanya will get  $ s $ . Or determine that no suitable  $ b$$$ exists.

## 输入格式

The first line of input data contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Each test case consists of a single line containing two positive integers $ a $ and $ s $ ( $ 1 \le a \lt s \le 10^{18} $ ) separated by a space.

## 输出格式

For each test case print the answer on a separate line.

If the solution exists, print a single positive integer $ b $ . The answer must be written without leading zeros. If multiple answers exist, print any of them.

If no suitable number $ b $ exists, output -1.

## 说明/提示

The first test case is explained in the main part of the statement.

In the third test case, we cannot choose $ b $ that satisfies the problem statement.

## 样例 #1

### 输入

```
6
17236 1106911
1 5
108 112
12345 1023412
1 11
1 20
```

### 输出

```
3465
4
-1
90007
10
-1
```



---

---
title: "Great Sequence"
layout: "post"
diff: 普及-
pid: CF1641A
tag: ['模拟', '贪心', '排序']
---

# Great Sequence

## 题目描述

A sequence of positive integers is called great for a positive integer $ x $ , if we can split it into pairs in such a way that in each pair the first number multiplied by $ x $ is equal to the second number. More formally, a sequence $ a $ of size $ n $ is great for a positive integer $ x $ , if $ n $ is even and there exists a permutation $ p $ of size $ n $ , such that for each $ i $ ( $ 1 \le i \le \frac{n}{2} $ ) $ a_{p_{2i-1}} \cdot x = a_{p_{2i}} $ .

Sam has a sequence $ a $ and a positive integer $ x $ . Help him to make the sequence great: find the minimum possible number of positive integers that should be added to the sequence $ a $ to make it great for the number $ x $ .

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 20\,000 $ ) — the number of test cases. Description of the test cases follows.

The first line of each test case contains two integers $ n $ , $ x $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 2 \le x \le 10^6 $ ).

The next line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case print a single integer — the minimum number of integers that can be added to the end of $ a $ to make it a great sequence for the number $ x $ .

## 说明/提示

In the first test case, Sam got lucky and the sequence is already great for the number $ 4 $ because you can divide it into such pairs: $ (1, 4) $ , $ (4, 16) $ . Thus we can add $ 0 $ numbers.

In the second test case, you can add numbers $ 1 $ and $ 14 $ to the sequence, then you can divide all $ 8 $ integers into such pairs: $ (1, 2) $ , $ (1, 2) $ , $ (2, 4) $ , $ (7, 14) $ . It is impossible to add less than $ 2 $ integers to fix the sequence.

## 样例 #1

### 输入

```
4
4 4
1 16 4 4
6 2
1 2 2 2 4 7
5 3
5 2 3 5 15
9 10
10 10 10 20 1 100 200 2000 3
```

### 输出

```
0
2
3
3
```



---

---
title: "Detective Task"
layout: "post"
diff: 普及-
pid: CF1675C
tag: ['模拟', '贪心']
---

# Detective Task

## 题目描述

Polycarp bought a new expensive painting and decided to show it to his $ n $ friends. He hung it in his room. $ n $ of his friends entered and exited there one by one. At one moment there was no more than one person in the room. In other words, the first friend entered and left first, then the second, and so on.

It is known that at the beginning (before visiting friends) a picture hung in the room. At the end (after the $ n $ -th friend) it turned out that it disappeared. At what exact moment it disappeared — there is no information.

Polycarp asked his friends one by one. He asked each one if there was a picture when he entered the room. Each friend answered one of three:

- no (response encoded with 0);
- yes (response encoded as 1);
- can't remember (response is encoded with ?).

Everyone except the thief either doesn't remember or told the truth. The thief can say anything (any of the three options).

Polycarp cannot understand who the thief is. He asks you to find out the number of those who can be considered a thief according to the answers.

## 输入格式

The first number $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases in the test.

The following is a description of test cases.

The first line of each test case contains one string $ s $ (length does not exceed $ 2 \cdot 10^5 $ ) — a description of the friends' answers, where $ s_i $ indicates the answer of the $ i $ -th friend. Each character in the string is either 0 or 1 or ?.

The given regularity is described in the actual situation. In particular, on the basis of answers, at least one friend can be suspected of stealing a painting.

It is guaranteed that the sum of string lengths over the entire input data set does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

Output one positive (strictly more zero) number – the number of people who could steal the picture based on the data shown.

## 说明/提示

In the first case, the answer is $ 1 $ since we had exactly $ 1 $ friend.

The second case is similar to the first.

In the third case, the suspects are the third and fourth friends (we count from one). It can be shown that no one else could be the thief.

In the fourth case, we know absolutely nothing, so we suspect everyone.

## 样例 #1

### 输入

```
8
0
1
1110000
?????
1?1??0?0
0?0???
??11
??0??
```

### 输出

```
1
1
2
5
4
1
1
3
```



---

---
title: "Most Similar Words"
layout: "post"
diff: 普及-
pid: CF1676C
tag: ['模拟']
---

# Most Similar Words

## 题目描述

You are given $ n $ words of equal length $ m $ , consisting of lowercase Latin alphabet letters. The $ i $ -th word is denoted $ s_i $ .

In one move you can choose any position in any single word and change the letter at that position to the previous or next letter in alphabetical order. For example:

- you can change 'e' to 'd' or to 'f';
- 'a' can only be changed to 'b';
- 'z' can only be changed to 'y'.

The difference between two words is the minimum number of moves required to make them equal. For example, the difference between "best" and "cost" is $ 1 + 10 + 0 + 0 = 11 $ .

Find the minimum difference of $ s_i $ and $ s_j $ such that $ (i < j) $ . In other words, find the minimum difference over all possible pairs of the $ n $ words.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains $ 2 $ integers $ n $ and $ m $ ( $ 2 \leq n \leq 50 $ , $ 1 \leq m \leq 8 $ ) — the number of strings and their length respectively.

Then follows $ n $ lines, the $ i $ -th of which containing a single string $ s_i $ of length $ m $ , consisting of lowercase Latin letters.

## 输出格式

For each test case, print a single integer — the minimum difference over all possible pairs of the given strings.

## 说明/提示

For the second test case, one can show that the best pair is ("abb","bef"), which has difference equal to $ 8 $ , which can be obtained in the following way: change the first character of the first string to 'b' in one move, change the second character of the second string to 'b' in $ 3 $ moves and change the third character of the second string to 'b' in $ 4 $ moves, thus making in total $ 1 + 3 + 4 = 8 $ moves.

For the third test case, there is only one possible pair and it can be shown that the minimum amount of moves necessary to make the strings equal is $ 35 $ .

For the fourth test case, there is a pair of strings which is already equal, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
6
2 4
best
cost
6 3
abb
zba
bef
cdu
ooo
zzz
2 7
aaabbbc
bbaezfe
3 2
ab
ab
ab
2 8
aaaaaaaa
zzzzzzzz
3 1
a
u
y
```

### 输出

```
11
8
35
0
200
4
```



---

---
title: "X-Sum"
layout: "post"
diff: 普及-
pid: CF1676D
tag: ['模拟']
---

# X-Sum

## 题目描述

Timur's grandfather gifted him a chessboard to practice his chess skills. This chessboard is a grid $ a $ with $ n $ rows and $ m $ columns with each cell having a non-negative integer written on it.

Timur's challenge is to place a bishop on the board such that the sum of all cells attacked by the bishop is maximal. The bishop attacks in all directions diagonally, and there is no limit to the distance which the bishop can attack. Note that the cell on which the bishop is placed is also considered attacked. Help him find the maximal sum he can get.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains the integers $ n $ and $ m $ ( $ 1 \le n \le 200 $ , $ 1 \leq m \leq 200 $ ).

The following $ n $ lines contain $ m $ integers each, the $ j $ -th element of the $ i $ -th line $ a_{ij} $ is the number written in the $ j $ -th cell of the $ i $ -th row $ (0\leq a_{ij} \leq 10^6) $

It is guaranteed that the sum of $ n\cdot m $ over all test cases does not exceed $ 4\cdot10^4 $ .

## 输出格式

For each test case output a single integer, the maximum sum over all possible placements of the bishop.

## 说明/提示

For the first test case here the best sum is achieved by the bishop being in this position:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1676D/ef38eda1ec7208a8243b8f6ac83d0d9df8a29fbb.png)

## 样例 #1

### 输入

```
4
4 4
1 2 2 1
2 4 2 4
2 2 3 1
2 4 2 4
2 1
1
0
3 3
1 1 1
1 1 1
1 1 1
3 3
0 1 1
1 0 1
1 1 0
```

### 输出

```
20
1
5
3
```



---

---
title: "Maximum Crossings (Easy Version)"
layout: "post"
diff: 普及-
pid: CF1676H1
tag: ['模拟']
---

# Maximum Crossings (Easy Version)

## 题目描述

The only difference between the two versions is that in this version $ n \leq 1000 $ and the sum of $ n $ over all test cases does not exceed $ 1000 $ .

A terminal is a row of $ n $ equal segments numbered $ 1 $ to $ n $ in order. There are two terminals, one above the other.

You are given an array $ a $ of length $ n $ . For all $ i = 1, 2, \dots, n $ , there should be a straight wire from some point on segment $ i $ of the top terminal to some point on segment $ a_i $ of the bottom terminal. For example, the following pictures show two possible wirings if $ n=7 $ and $ a=[4,1,4,6,7,7,5] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1676H1/71a1fe41f3cad0f3cbda88716457eefb4e46b4ca.png)A crossing occurs when two wires share a point in common. In the picture above, crossings are circled in red.

What is the maximum number of crossings there can be if you place the wires optimally?

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 1000 $ ) — the length of the array.

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \leq a_i \leq n $ ) — the elements of the array.

The sum of $ n $ across all test cases does not exceed $ 1000 $ .

## 输出格式

For each test case, output a single integer — the maximum number of crossings there can be if you place the wires optimally.

## 说明/提示

The first test case is shown in the second picture in the statement.

In the second test case, the only wiring possible has the two wires cross, so the answer is $ 1 $ .

In the third test case, the only wiring possible has one wire, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
4
7
4 1 4 6 7 7 5
2
2 1
1
1
3
2 2 2
```

### 输出

```
6
1
0
3
```



---

---
title: "Stone Age Problem"
layout: "post"
diff: 普及-
pid: CF1679B
tag: ['模拟', '线段树']
---

# Stone Age Problem

## 题目描述

数组 $a$ 有 $n$ 个元素，需要进行 $q$ 次操作。

操作1：将第 $i$ 号元素改为 $x$

操作2：将数组中所有元素改为 $x$

每次操作完成后，输出当前数组中所有元素的总和。

## 输入格式

第一行两个整数 $n,q(1\le n,q \le2\times 10^5)$

第二行 $n$ 个整数，表示 $a$ 中的元素 $(1\le a_i\le10^9)$

接下来有 $q$ 行，首先输入一个整数 $t(t\in {1,2})$

若 $t=1$，接着输入两个整数 $i,x(1\le i \le n, 1\le x \le 10^9)$

若 $t=2$，接着输入一个整数 $x(1\le x \le 10^9)$

## 输出格式

共 $q$ 行，每行一个整数，表示当前数组 $a$ 中所有元素的和

## 样例 #1

### 输入

```
5 5
1 2 3 4 5
1 1 5
2 10
1 5 11
1 4 1
2 1
```

### 输出

```
19
50
51
42
5
```



---

---
title: "Robots"
layout: "post"
diff: 普及-
pid: CF1680B
tag: ['模拟']
---

# Robots

## 题目描述

There is a field divided into $ n $ rows and $ m $ columns. Some cells are empty (denoted as E), other cells contain robots (denoted as R).

You can send a command to all robots at the same time. The command can be of one of the four types:

- move up;
- move right;
- move down;
- move left.

When you send a command, all robots at the same time attempt to take one step in the direction you picked. If a robot tries to move outside the field, it explodes; otherwise, every robot moves to an adjacent cell in the chosen direction.

You can send as many commands as you want (possibly, zero), in any order. Your goal is to make at least one robot reach the upper left corner of the field. Can you do this without forcing any of the robots to explode?

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 5000 $ ) — the number of test cases.

Each test case starts with a line containing two integers $ n $ and $ m $ ( $ 1 \le n, m \le 5 $ ) — the number of rows and the number of columns, respectively. Then $ n $ lines follow; each of them contains a string of $ m $ characters. Each character is either E (empty cell} or R (robot).

Additional constraint on the input: in each test case, there is at least one robot on the field.

## 输出格式

If it is possible to make at least one robot reach the upper left corner of the field so that no robot explodes, print YES. Otherwise, print NO.

## 说明/提示

Explanations for test cases of the example:

1. in the first test case, it is enough to send a command to move left.
2. in the second test case, if you try to send any command, at least one robot explodes.
3. in the third test case, it is enough to send a command to move left.
4. in the fourth test case, there is already a robot in the upper left corner.
5. in the fifth test case, the sequence "move up, move left, move up" leads one robot to the upper left corner;
6. in the sixth test case, if you try to move any robot to the upper left corner, at least one other robot explodes.

## 样例 #1

### 输入

```
6
1 3
ERR
2 2
ER
RE
2 2
ER
ER
1 1
R
4 3
EEE
EEE
ERR
EER
3 3
EEE
EER
REE
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
title: "Card Trick"
layout: "post"
diff: 普及-
pid: CF1681B
tag: ['模拟']
---

# Card Trick

## 题目描述

Monocarp has just learned a new card trick, and can't wait to present it to you. He shows you the entire deck of $ n $ cards. You see that the values of cards from the topmost to the bottommost are integers $ a_1, a_2, \dots, a_n $ , and all values are different.

Then he asks you to shuffle the deck $ m $ times. With the $ j $ -th shuffle, you should take $ b_j $ topmost cards and move them under the remaining $ (n - b_j) $ cards without changing the order.

And then, using some magic, Monocarp tells you the topmost card of the deck. However, you are not really buying that magic. You tell him that you know the topmost card yourself. Can you surprise Monocarp and tell him the topmost card before he shows it?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of testcases.

The first line of each testcase contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of cards in the deck.

The second line contains $ n $ pairwise distinct integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ) — the values of the cards.

The third line contains a single integer $ m $ ( $ 1 \le m \le 2 \cdot 10^5 $ ) — the number of shuffles.

The fourth line contains $ m $ integers $ b_1, b_2, \dots, b_m $ ( $ 1 \le b_j \le n - 1 $ ) — the amount of cards that are moved on the $ j $ -th shuffle.

The sum of $ n $ over all testcases doesn't exceed $ 2 \cdot 10^5 $ . The sum of $ m $ over all testcases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each testcase, print a single integer — the value of the card on the top of the deck after the deck is shuffled $ m $ times.

## 说明/提示

In the first testcase, each shuffle effectively swaps two cards. After three swaps, the deck will be $ [2, 1] $ .

In the second testcase, the second shuffle cancels what the first shuffle did. First, three topmost cards went underneath the last card, then that card went back below the remaining three cards. So the deck remained unchanged from the initial one — the topmost card has value $ 3 $ .

## 样例 #1

### 输入

```
3
2
1 2
3
1 1 1
4
3 1 4 2
2
3 1
5
2 1 5 4 3
5
3 2 1 2 1
```

### 输出

```
2
3
3
```



---

---
title: "Everyone Loves to Sleep"
layout: "post"
diff: 普及-
pid: CF1714A
tag: ['模拟']
---

# Everyone Loves to Sleep

## 题目描述

Vlad和其他人一样，非常喜欢睡觉。

Vlad每天都要做 $n$ 件事，每件事在特定时间。对于这些事情中的每一件，他都定了一个闹钟，其中第 $i$ 个在 $h_i$ 时 $m_i$ 分被触发（$0\le h_i<24,0\le m_i<60）$。

Vlad使用24小时时间格式，所以12:59之后是13:00,23:59后是00:00。

Vlad在H时M分睡觉（$0 \le H < 24， 0 \le M < 60$）。

他要你回答：在下一个闹钟响之前，他能睡多久。

如果在他上床睡觉的时候有任何闹钟响起，那么他将睡0小时0分钟。

## 输入格式

输入数据的第一行包含一个整数 $t$ ($1 \le t \le 100$） — 测试中测试用例的数量。

每组测试用例的第一行包含三个整数 $n$ , $H$ 和 $M$ ($ 1 \le n \le 10， 0 \le H < 24， 0 \le M < 60$） — 闹钟的数量和Vlad上床睡觉的时间。

以下 $n$ 行各包含两个数字 $h_i$ 和 $m_i$ ( $0 \le h_i < 24， 0 \le m_i < 60$） — 每个闹钟响的时间。两个或多个闹钟可以同时响起。描述时间的数字不包含前导零。

## 输出格式

输出 $t$ 行，每行都包含相应测试用例的答案。

作为答案，输出两个数字 - Vlad将分别睡觉的小时数和分钟数。如果在他上床睡觉的时候有任何闹钟响起，答案将是 $0\ 0$。

### 样例解释

对于第一个测试用例，Vlad上床后第一个响的闹钟是8:00的。

对于第二个测试用例，Vlad上床时有闹钟响起。

对于第三个测试用例，Vlad上床后第一个响的闹钟是第二天10:30的。

## 样例 #1

### 输入

```
3
1 6 13
8 0
3 6 0
12 30
14 45
6 0
2 23 35
20 15
10 30
```

### 输出

```
1 47
0 0
10 55
```



---

---
title: "Madoka and Underground Competitions"
layout: "post"
diff: 普及-
pid: CF1717B
tag: ['模拟', '构造']
---

# Madoka and Underground Competitions

## 题目描述

Madoka decided to participate in an underground sports programming competition. And there was exactly one task in it:

A square table of size $ n \times n $ , where  $ n $ is a multiple of $ k $ , is called good if only the characters '.' and 'X' are written in it, as well as in any subtable of size $ 1 \times k $ or $ k \times 1 $ , there is at least one character 'X'. In other words, among any $ k $ consecutive vertical or horizontal cells, there must be at least one containing the character 'X'.

Output any good table that has the minimum possible number of characters 'X', and also the symbol 'X' is written in the cell $ (r, c) $ . Rows are numbered from $ 1 $ to $ n $ from top to bottom, columns are numbered from $ 1 $ to $ n $ from left to right.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases. Description of the test cases follows.

The first and the only line of each test case contains four integers $ n $ , $ k $ , $ r $ , $ c $ ( $ 1 \le n \le 500, 1 \le k \le n, 1 \le r, c \le n $ ) — the size of the table, the integer $ k $ and the coordinates of the cell, which must contain the character 'X'. It is guaranteed that $ n $ is a multiple of $ k $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 500 $ .

## 输出格式

For each test case, output $ n $ lines, each consisting of $ n $ characters '.' and 'X', — the desired table. If there are several answers, then you can output anyone.

## 说明/提示

Let's analyze the first test case.

The following tables can be printed as the correct answer:

 X....X.X. or ..XX...X. It can be proved that there cannot be less than $ 3 $ characters 'X' in the answer.Note that the following table is invalid because cell $ (3, 2) $ does not contain the character 'X':

 X...X...XIn the second test case, the only correct table is:

 XXXX Each subtable of size $ 1 \times 1 $ must contain a 'X' character, so all characters in the table must be equal to 'X'.

## 样例 #1

### 输入

```
3
3 3 3 2
2 1 1 2
6 3 4 2
```

### 输出

```
X..
..X
.X.
XX
XX
.X..X.
X..X..
..X..X
.X..X.
X..X..
..X..X
```



---

---
title: "Word Game"
layout: "post"
diff: 普及-
pid: CF1722C
tag: ['模拟']
---

# Word Game

## 题目描述

Three guys play a game: first, each person writes down $ n $ distinct words of length $ 3 $ . Then, they total up the number of points as follows:

- if a word was written by one person — that person gets 3 points,
- if a word was written by two people — each of the two gets 1 point,
- if a word was written by all — nobody gets any points.

 In the end, how many points does each player have?

## 输入格式

The input consists of multiple test cases. The first line contains an integer $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains an integer $ n $ ( $ 1 \leq n \leq 1000 $ ) — the number of words written by each person.

The following three lines each contain $ n $ distinct strings — the words written by each person. Each string consists of $ 3 $ lowercase English characters.

## 输出格式

For each test case, output three space-separated integers — the number of points each of the three guys earned. You should output the answers in the same order as the input; the $ i $ -th integer should be the number of points earned by the $ i $ -th guy.

## 说明/提示

In the first test case:

- The word $ \texttt{abc} $ was written by the first and third guys — they each get $ 1 $ point.
- The word $ \texttt{def} $ was written by the second guy only — he gets $ 3 $ points.

## 样例 #1

### 输入

```
3
1
abc
def
abc
3
orz for qaq
qaq orz for
cod for ces
5
iat roc hem ica lly
bac ter iol ogi sts
bac roc lly iol iat
```

### 输出

```
1 3 1 
2 2 6 
9 11 5
```



---

---
title: "Even-Odd Increments"
layout: "post"
diff: 普及-
pid: CF1744B
tag: ['模拟', '数学']
---

# Even-Odd Increments

## 题目描述

You are given $ n $ of integers $ a_1, a_2, \ldots, a_n $ . Process $ q $ queries of two types:

- query of the form "0 $ x_j $ ": add the value $ x_j $ to all even elements of the array $ a $ ,
- query of the form "1 $ x_j $ ": add the value $ x_j $ to all odd elements of the array $ a $ .

Note that when processing the query, we look specifically at the odd/even value of $ a_i $ , not its index.

After processing each query, print the sum of the elements of the array $ a $ .

Please note that the answer for some test cases won't fit into 32-bit integer type, so you should use at least 64-bit integer type in your programming language (like long long for C++).

## 输入格式

The first line of the input contains an integer $ t $ $ (1 \leq t \leq 10^4 $ ) — the number of test cases.

The descriptions of the test cases follow.

The first line of each test case contains two integers $ n $ and $ q $ ( $ 1 \leq n $ , $ q \leq 10^5 $ ) — the length of array $ a $ and the number of queries.

The second line of each test case contains exactly $ n $ integers: $ a_1, a_2, \ldots, a_n $ ( $ 1 \leq a_i \leq 10^9 $ ) — elements of the array $ a $ .

The following $ q $ lines contain queries as two integers $ type_j $ and $ x_j $ $ (0 \leq type_j \leq 1 $ , $ 1 \leq x_j \leq 10^4 $ ).

It is guaranteed that the sum of values $ n $ over all test cases in a test does not exceed $ 10^5 $ . Similarly, the sum of values $ q $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, print $ q $ numbers: the sum of the elements of the array $ a $ after processing a query.

## 说明/提示

In the first test case, the array $ a = [2] $ after the first query.

In the third test case, the array $ a $ is modified as follows: $ [1, 3, 2, 4, 10, 48] $ $ \rightarrow $ $ [7, 9, 2, 4, 10, 48] $ $ \rightarrow $ $ [7, 9, 7, 9, 15, 53] $ $ \rightarrow $ $ [7, 9, 7, 9, 15, 53] $ $ \rightarrow $ $ [10, 12, 10, 12, 18, 56] $ $ \rightarrow $ $ [22, 24, 22, 24, 30, 68] $ $ \rightarrow $ $ [23, 25, 23, 25, 31, 69] $ .

## 样例 #1

### 输入

```
4
1 1
1
1 1
3 3
1 2 4
0 2
1 3
0 5
6 7
1 3 2 4 10 48
1 6
0 5
0 4
0 5
1 3
0 12
0 1
6 7
1000000000 1000000000 1000000000 11 15 17
0 17
1 10000
1 51
0 92
0 53
1 16
0 1
```

### 输出

```
2
11
14
29
80
100
100
100
118
190
196
3000000094
3000060094
3000060400
3000060952
3000061270
3000061366
3000061366
```



---

---
title: "Rudolf and the Ugly String"
layout: "post"
diff: 普及-
pid: CF1941C
tag: ['模拟', '贪心']
---

# Rudolf and the Ugly String

## 题目描述

Rudolf has a string $ s $ of length $ n $ . Rudolf considers the string $ s $ to be ugly if it contains the substring $ ^\dagger $ "pie" or the substring "map", otherwise the string $ s $ will be considered beautiful.

For example, "ppiee", "mmap", "dfpiefghmap" are ugly strings, while "mathp", "ppiiee" are beautiful strings.

Rudolf wants to shorten the string $ s $ by removing some characters to make it beautiful.

The main character doesn't like to strain, so he asks you to make the string beautiful by removing the minimum number of characters. He can remove characters from any positions in the string (not just from the beginning or end of the string).

 $ ^\dagger $ String $ a $ is a substring of $ b $ if there exists a consecutive segment of characters in string $ b $ equal to $ a $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The descriptions of the test cases follow.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 10^6 $ ) — the length of the string $ s $ .

The next line of each test case contains the string $ s $ of length $ n $ . The string $ s $ consists of lowercase Latin letters.

The sum of $ n $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

For each test case, output a single integer — the minimum number of characters that need to be deleted to make the string $ s $ beautiful. If the string is initially beautiful, then output $ 0 $ .

## 说明/提示

In the first test case, for example, you can delete the $ 4 $ th and $ 9 $ th characters to make the string beautiful.

In the second test case, the string is already beautiful.

## 样例 #1

### 输入

```
6
9
mmapnapie
9
azabazapi
8
mappppie
18
mapmapmapmapmapmap
1
p
11
pppiepieeee
```

### 输出

```
2
0
2
6
0
2
```



---

---
title: "Array Fix"
layout: "post"
diff: 普及-
pid: CF1948B
tag: ['模拟', '贪心']
---

# Array Fix

## 题目描述

给定一个长度为 $n$ 的非负整数序列 $a$，你可以进行如下操作任意次：

- 选择序列中第 $i$ 个数 $a_i$，将其从原序列中删除。然后将这个数字十进制上的每一位数，按原顺序放回序列。

比如，原来有序列 $[12, 3, 45, 67]$，如果选择其中第 $3$ 个数进行操作，那么序列就会变为 $[12, 3, 4, 5, 67]$。

再比如，原来有序列 $[2, 10]$，如果选择其中第 $2$ 个数进行操作，那么序列就会变为 $[2, 1, 0]$。

现在请你判断，是否存在一组操作方案，使得这个序列变得**单调不降**。

即，令最终序列长度为 $k$，那么有 $a_1 \leq a_2 \leq \cdots \leq a_k$。

## 输入格式

**本题目含多组数据。**

第一行，一个正整数 $t$，表示数据组数。

接下来每组数据包含两行：

- 第一行，一个正整数 $n$；
- 第二行，$n$ 个非负整数 $a_i$。

## 输出格式

对于每组数据，如果有解输出 `YES`，否则输出 `NO`。

## 说明/提示

对于 $100 \%$ 的数据，保证 $1 \leq t \leq 10^3, 2 \leq n \leq 50, 0 \leq a_i \leq 99$。

Translated by ShiRoZeTsu.

## 样例 #1

### 输入

```
3
4
12 3 45 67
3
12 28 5
2
0 0
```

### 输出

```
YES
NO
YES
```



---

---
title: "Product of Binary Decimals"
layout: "post"
diff: 普及-
pid: CF1950D
tag: ['模拟', '深度优先搜索 DFS']
---

# Product of Binary Decimals

## 题目描述

### 二进制小数的乘积
我们称一个数字为二进制小数，如果它是一个正整数，并且其十进制表示中的所有数字都是0或1。例如，$1010111$ 是一个二进制小数，而 $10201$ 和 $787788$ 不是。

给定一个数 $n$，你被要求判断是否可能将 $n$ 表示为一些（不一定是不同的）二进制小数的乘积。

## 输入格式

第一行包含一个整数 $t$（$1 \leq t \leq 5 \cdot 10^4$）— 测试用例的数量。

每个测试用例的唯一一行包含一个整数 $n$（$1 \leq n \leq 10^5$）。

## 输出格式

对于每个测试用例，如果 $n$ 可以表示为一些二进制小数的乘积，则输出 "YES"（不带引号），否则输出 "NO"（不带引号）。

你可以以任何形式输出 "YES" 和 "NO"（例如，字符串 "yES"、"yes" 和 "Yes" 都将被认为是肯定的响应）。

## 说明/提示

前五个测试用例可以表示为二进制小数的乘积如下：

$121 = 11 \times 11$
$1 = 1$ 已经是一个二进制小数。
$14641 = 11 \times 11 \times 11 \times 11$
$12221 = 11 \times 11 \times 101$
$10110 = 10110$ 已经是一个二进制小数。

## 样例 #1

### 输入

```
11
121
1
14641
12221
10110
100000
99
112
2024
12421
1001
```

### 输出

```
YES
YES
YES
YES
YES
YES
NO
NO
NO
NO
YES
```



---

---
title: "Progressive Square"
layout: "post"
diff: 普及-
pid: CF1955B
tag: ['模拟']
---

# Progressive Square

## 题目描述

大小为 $n$ 的累进正方形是一个 $n\times n$ 的矩阵。选择三个整数 $a_{1,1},c,d$
 ，并根据以下规则构造一个累进正方形：

$a _ {i+1,j} = a _ {i,j} + c$

$a _ {i,j+1} = a _ {i,j} + d$

例如，如果 $n=3,a_{1,1}=1,c=2,d=3$，那么累进正方形如下：
 
$\begin{pmatrix} 1 & 4 & 7 \\ 3 & 6 & 9 \\ 5 & 8 & 11 \end{pmatrix}$

给定 $n,c,d$，有 $n^2$ 个整数，判断这些数是否能组成一个符合规则的累进正方形。

## 输入格式

第一行一个整数 $t$，表示测试数据数。对于每组数据，第一行三个整数 $n,c,d$，第二行输入 $n \times n$ 个整数，表示需要构造累进正方形的数。

## 输出格式

对于每组数据，输出 `YES` 或 `NO` 表示结果。

## 样例 #1

### 输入

```
5
3 2 3
3 9 6 5 7 1 10 4 8
3 2 3
3 9 6 5 7 1 11 4 8
2 100 100
400 300 400 500
3 2 3
3 9 6 6 5 1 11 4 8
4 4 4
15 27 7 19 23 23 11 15 7 3 19 23 11 15 11 15
```

### 输出

```
NO
YES
YES
NO
NO
```



---

---
title: "Inhabitant of the Deep Sea"
layout: "post"
diff: 普及-
pid: CF1955C
tag: ['模拟']
---

# Inhabitant of the Deep Sea

## 题目描述

$n$ 艘船只开始探索海洋深处。这些船的编号从 $1$ 到 $n$ 并按升序相互跟随，第 $i$ 只船的耐久度是 $a[i]$ 。( $1 ≤ a[i] ≤ 10^9$ )

海妖按特定顺序袭击 $k$ 次船只：首先，它攻击船队的第一艘船只，然后攻击最后一艘，然后再攻击第一艘……依此类推。

海妖的每次攻击都会降低飞船的 $1$ 耐久度。当船舶的耐久性下降到 $0$ ，它就沉没了（而海妖只攻击尚未沉没的船只）。如果所有的船只都沉没了，海妖就没有什么可攻击的了，它就会游走。

给定 $n , k$ 和 $n$ 只船的耐久度，问海妖袭击后有多少艘船被击沉？

## 输入格式

**本题有多组数据**。
第一行一个整数 $t$，表示数据组数。

每个测试数据的第一行包含两个整数：船只的数量 $n$ 
以及海妖攻击船只的次数 $k$ 
 $(1≤N≤2⋅10^5
,1≤k≤10^{15}）$ 。

每个测试数据的第二行包含 $n$ 个整数，第 $i$ 个数表示第 $i$ 艘船的耐久度。

## 输出格式

对于每组测试数据，输出一行一个整数，为被海妖击沉的船只数量。

#### 输入样例
```
6
4 5
1 2 4 3
4 6
1 2 4 3
5 20
2 7 1 8 2
2 2
3 2
2 15
1 5
2 7
5 2

```

#### 输出样例

```
2
3
5
0
2
2

```

## 样例 #1

### 输入

```
6
4 5
1 2 4 3
4 6
1 2 4 3
5 20
2 7 1 8 2
2 2
3 2
2 15
1 5
2 7
5 2
```

### 输出

```
2
3
5
0
2
2
```



---

---
title: "Rectangle Filling"
layout: "post"
diff: 普及-
pid: CF1966B
tag: ['模拟', '贪心']
---

# Rectangle Filling

## 题目描述

There is an $ n \times m $ grid of white and black squares. In one operation, you can select any two squares of the same color, and color all squares in the subrectangle between them that color.

Formally, if you select positions $ (x_1, y_1) $ and $ (x_2, y_2) $ , both of which are currently the same color $ c $ , set the color of all $ (x, y) $ where $ \min(x_1, x_2) \le x \le \max(x_1, x_2) $ and $ \min(y_1, y_2) \le y \le \max(y_1, y_2) $ to $ c $ .

This diagram shows a sequence of two possible operations on a grid:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1966B/d8e91236088d989799638772d594a0a137d702f1.png)Is it possible for all squares in the grid to be the same color, after performing any number of operations (possibly zero)?

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le n, m \le 500 $ ) — the number of rows and columns in the grid, respectively.

Each of the next $ n $ lines contains $ m $ characters 'W' and 'B' — the initial colors of the squares of the grid.

It is guaranteed that the sum of $ n\cdot m $ over all test cases does not exceed $ 3\cdot 10^5 $ .

## 输出格式

For each test case, print "YES" if it is possible to make all squares in the grid the same color, and "NO" otherwise.

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 说明/提示

In the first example, it is impossible to ever change the color of any square with an operation, so we output NO.

The second example is the case pictured above. As shown in that diagram, it is possible for all squares to be white after two operations, so we output YES.

In the third and fourth examples, all squares are already the same color, so we output YES.

In the fifth example we can do everything in two operations. First, select positions $ (2, 1) $ and $ (1, 4) $ and color all squares with $ 1 \le x \le 2 $ and $ 1 \le y \le 4 $ to white. Then, select positions $ (2, 1) $ and $ (3, 4) $ and color all squares with $ 2 \le x \le 3 $ and $ 1 \le y \le 4 $ to white. After these two operations all squares are white.

## 样例 #1

### 输入

```
8
2 1
W
B
6 6
WWWWBW
WBWWWW
BBBWWW
BWWWBB
WWBWBB
BBBWBW
1 1
W
2 2
BB
BB
3 4
BWBW
WBWB
BWBW
4 2
BB
BB
WW
WW
4 4
WWBW
BBWB
WWBB
BBBB
1 5
WBBWB
```

### 输出

```
NO
YES
YES
YES
YES
NO
YES
NO
```



---

---
title: "Balanced Shuffle (Easy)"
layout: "post"
diff: 普及-
pid: CF1970A1
tag: ['模拟', '前缀和']
---

# Balanced Shuffle (Easy)

## 题目描述

A parentheses sequence is a string consisting of characters "(" and ")", for example "(()((".

A balanced parentheses sequence is a parentheses sequence which can become a valid mathematical expression after inserting numbers and operations into it, for example "(()(()))".

The balance of a parentheses sequence is defined as the number of opening parentheses "(" minus the number of closing parentheses ")". For example, the balance of the sequence "(()((" is 3.

A balanced parentheses sequence can also be defined as a parentheses sequence with balance 0 such that each of its prefixes has a non-negative balance.

We define the balanced shuffle operation that takes a parentheses sequence and returns a parentheses sequence as follows: first, for every character of the input sequence, we compute the balance of the prefix of the sequence before that character and write those down in a table together with the positions of the characters in the input sequence, for example:

Prefix balance01212321Position12345678Character(()(()))Then, we sort the columns of this table in increasing order of prefix balance, breaking ties in decreasing order of position. In the above example, we get:

Prefix balance01112223Position18427536Character()(()())The last row of this table forms another parentheses sequence, in this case "()(()())". This sequence is called the result of applying the balanced shuffle operation to the input sequence, or in short just the balanced shuffle of the input sequence.

You are given a balanced parentheses sequence. Print its balanced shuffle.

## 输入格式

The only line of input contains a string $ s $ consisting only of characters "(" and ")". This string is guaranteed to be a non-empty balanced parentheses sequence with its length not exceeding $ 500\,000 $ .

## 输出格式

Print the parentheses sequence $ t $ — the balanced shuffle of $ s $ .

## 样例 #1

### 输入

```
(()(()))
```

### 输出

```
()(()())
```



---

---
title: "Symmetric Encoding"
layout: "post"
diff: 普及-
pid: CF1974B
tag: ['模拟']
---

# Symmetric Encoding

## 题目描述

Polycarp has a string $ s $ , which consists of lowercase Latin letters. He encodes this string using the following algorithm:

- first, he constructs a new auxiliary string $ r $ , which consists of all distinct letters of the string $ s $ , written in alphabetical order;
- then the encoding happens as follows: each character in the string $ s $ is replaced by its symmetric character from the string $ r $ (the first character of the string $ r $ will be replaced by the last, the second by the second from the end, and so on).

For example, encoding the string $ s $ ="codeforces" happens as follows:

- the string $ r $ is obtained as "cdefors";
- the first character $ s_1 $ ='c' is replaced by 's';
- the second character $ s_2 $ ='o' is replaced by 'e';
- the third character $ s_3 $ ='d' is replaced by 'r';
- ...
- the last character $ s_{10} $ ='s' is replaced by 'c'.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1974B/bdd77e5f1b5637622489d2d075a49b021a94a8b9.png) The string $ r $ and replacements for $ s $ ="codeforces".Thus, the result of encoding the string $ s $ ="codeforces" is the string "serofedsoc".

Write a program that performs decoding — that is, restores the original string $ s $ from the encoding result.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the length of the string $ b $ .

The second line of each test case contains a string $ b $ of length $ n $ , consisting of lowercase Latin letters — the result of encoding the original string $ s $ .

It is guaranteed that the sum of the values of $ n $ over all test cases in the test does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output the string $ s $ from which the encoding result $ b $ was obtained.

## 样例 #1

### 输入

```
5
10
serofedsoc
3
ttf
9
tlrhgmaoi
1
w
15
hnndledmnhlttin
```

### 输出

```
codeforces
fft
algorithm
w
meetinthemiddle
```



---

---
title: "Good Prefixes"
layout: "post"
diff: 普及-
pid: CF1985C
tag: ['模拟']
---

# Good Prefixes

## 题目描述

Alex thinks some array is good if there exists some element that can be represented as the sum of all other elements (the sum of all other elements is $ 0 $ if there are no other elements). For example, the array $ [1,6,3,2] $ is good since $ 1+3+2=6 $ . Furthermore, the array $ [0] $ is also good. However, the arrays $ [1,2,3,4] $ and $ [1] $ are not good.

Alex has an array $ a_1,a_2,\ldots,a_n $ . Help him count the number of good non-empty prefixes of the array $ a $ . In other words, count the number of integers $ i $ ( $ 1 \le i \le n $ ) such that the length $ i $ prefix (i.e. $ a_1,a_2,\ldots,a_i $ ) is good.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of elements in the array.

The second line of each test case contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 0 \le a_i \le 10^9 $ ) — the elements of the array.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the number of good non-empty prefixes of the array $ a $ .

## 说明/提示

In the fourth test case, the array has five prefixes:

- prefix $ [0] $ is a good array, as mentioned in the statement;
- prefix $ [0, 1] $ is not a good array, since $ 0 \ne 1 $ ;
- prefix $ [0, 1, 2] $ is not a good array, since $ 0 \ne 1 + 2 $ , $ 1 \ne 0 + 2 $ and $ 2 \ne 0 + 1 $ ;
- prefix $ [0, 1, 2, 1] $ is a good array, since $ 2 = 0 + 1 + 1 $ ;
- prefix $ [0, 1, 2, 1, 4] $ is a good array, since $ 4 = 0 + 1 + 2 + 1 $ .

As you can see, three of them are good, so the answer is $ 3 $ .

## 样例 #1

### 输入

```
7
1
0
1
1
4
1 1 2 0
5
0 1 2 1 4
7
1 1 0 3 5 2 12
7
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 294967296
10
0 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 589934592
```

### 输出

```
1
0
3
3
4
1
2
```



---

---
title: "Manhattan Circle"
layout: "post"
diff: 普及-
pid: CF1985D
tag: ['模拟', '贪心']
---

# Manhattan Circle

## 题目描述

给定一个由“.”和“#”字符组成的n*m的网格，网格上存在一个完整的曼哈顿圆。网格的左上角坐标为(1,1)
，右下角坐标为(n,m) 。
如果|h-a| +|k-b|<r，则点（a,b）属于以（h,k）为中心的曼哈顿圆，其中r是正常数。
在网格上，作为曼哈顿圆一部分的点集被标记为“#”。找到圆心的坐标。

## 输入格式

第一行包含t（1<=t<=1000 ）——测试用例的数量。
每个测试用例的第一行分别包含n和m（1<=n·m<=2·100000 ）--网格的高度和宽度。
接下来的n行包含m个字符 '.' 或 '#'，如果字符是“#”，则该点是曼哈顿圆的一部分。
保证所有测试用例的n·m总和不超过2·100000 ，并且网格上有一个完整的曼哈顿圆圈。

## 输出格式

对于每个测试用例，输出两个整数，即圆心的坐标。

## 样例 #1

### 输入

```
6
5 5
.....
.....
..#..
.....
.....
5 5
..#..
.###.
#####
.###.
..#..
5 6
......
......
.#....
###...
.#....
1 1
#
5 6
...#..
..###.
.#####
..###.
...#..
2 10
..........
...#......
```

### 输出

```
3 3
3 3
4 2
1 1
3 4
2 4
```



---

---
title: "Matrix Stabilization"
layout: "post"
diff: 普及-
pid: CF1986B
tag: ['模拟']
---

# Matrix Stabilization

## 题目描述

给你一个大小为 $n \times m$ 的矩阵，矩阵的行从上到下编号为 $1$ 到 $n$，列从左到右编号为 $1$ 到 $m$。矩阵中第 $i$ 行与第 $j$ 列的交点处的元素记为 $a_{ij}$。

我们有一个用于稳定化矩阵 $a$ 的算法：

1. 找到一个单元格 $(i, j)$，该单元格的值严格大于其所有相邻单元格的值。如果没有这样的单元格，则终止算法。如果有多个这样的单元格，选择 $i$ 值最小的单元格；如果仍有多个单元格，选择 $j$ 值最小的单元格。
2. 将 $a_{ij}$ 的值减 1。
3. 回到步骤 1。

在这个问题中，如果两个单元格 $(a, b)$ 和 $(c, d)$ 共享一条边，即 $|a - c| + |b - d| = 1$，则它们被认为是相邻的。

你的任务是输出矩阵 $a$ 在稳定化算法执行后的结果。可以证明，此算法不能无限次运行。

## 输入格式

每个测试包含多组输入数据。第一行包含一个整数 $t$ ($1 \leq t \leq 10^4$) —— 输入数据的组数。接下来是这些输入数据的描述。

每组输入数据的第一行包含两个整数 $n$ 和 $m$ ($1 \leq n, m \leq 100, n \cdot m > 1$) —— 矩阵 $a$ 的行数和列数。

接下来的 $n$ 行描述了矩阵的相应行。第 $i$ 行包含 $m$ 个整数 $a_{i1}, a_{i2}, \ldots, a_{im}$ ($1 \leq a_{ij} \leq 10^9$)。

保证所有输入数据中 $n \cdot m$ 的总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每组输入数据，输出 $n$ 行，每行 $m$ 个数，表示矩阵 $a$ 在稳定化算法执行后的值。

## 样例 #1

### 样例输入 #1

## 样例 #1

### 输入

```
6
1 2
3 1
2 1
1
1
2 2
1 2
3 4
2 3
7 4 5
1 8 10
5 4
92 74 31 74
74 92 17 7
31 17 92 3
74 7 3 92
7 31 1 1
3 3
1000000000 1 1000000000
1 1000000000 1
1000000000 1 1000000000
```

### 输出

```
1 1 
1 
1 
1 2 
3 3 
4 4 5 
1 8 8 
74 74 31 31 
74 74 17 7 
31 17 17 3 
31 7 3 3 
7 7 1 1 
1 1 1 
1 1 1 
1 1 1
```



---

---
title: "Make Three Regions"
layout: "post"
diff: 普及-
pid: CF1997B
tag: ['模拟']
---

# Make Three Regions

## 题目描述

There is a grid, consisting of $ 2 $ rows and $ n $ columns. Each cell of the grid is either free or blocked.

A free cell $ y $ is reachable from a free cell $ x $ if at least one of these conditions holds:

- $ x $ and $ y $ share a side;
- there exists a free cell $ z $ such that $ z $ is reachable from $ x $ and $ y $ is reachable from $ z $ .

A connected region is a set of free cells of the grid such that all cells in it are reachable from one another, but adding any other free cell to the set violates this rule.

For example, consider the following layout, where white cells are free, and dark grey cells are blocked:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1997B/424d758ade46752deca8fcae4121a5c7f0d1a2fb.png) There are $ 3 $ regions in it, denoted with red, green and blue color respectively:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1997B/4fc8127700d32cdc5514e7db503c30c93554657e.png) The given grid contains at most $ 1 $ connected region. Your task is to calculate the number of free cells meeting the following constraint:

- if this cell is blocked, the number of connected regions becomes exactly $ 3 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of columns.

The $ i $ -th of the next two lines contains a description of the $ i $ -th row of the grid — the string $ s_i $ , consisting of $ n $ characters. Each character is either . (denoting a free cell) or x (denoting a blocked cell).

Additional constraint on the input:

- the given grid contains at most $ 1 $ connected region;
- the sum of $ n $ over all test cases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print a single integer — the number of cells such that the number of connected regions becomes $ 3 $ if this cell is blocked.

## 说明/提示

In the first test case, if the cell $ (1, 3) $ is blocked, the number of connected regions becomes $ 3 $ (as shown in the picture from the statement).

## 样例 #1

### 输入

```
4
8
.......x
.x.xx...
2
..
..
3
xxx
xxx
9
..x.x.x.x
x.......x
```

### 输出

```
1
0
0
2
```



---

---
title: "Showering"
layout: "post"
diff: 普及-
pid: CF1999C
tag: ['模拟']
---

# Showering

## 题目描述

作为一名中学生，jmsyang0808需要每天洗澡，但悲剧的是，因为Ta还要登~~臭名昭著的~~洛谷，AK CF赛，面基等等做一些琐碎的事导致Ta没有空。因为Ta太忙了，所以Ta请你写个程序来解决这个问题。

Ta有 $m$ 单位的时间，而Ta需要用 $s$ 单位的时间来洗澡。Ta有 $n$ 件事要做，第 $i$ 件事的开始与结束时间分别为 $l_i$ 和 $r_i$ ，期间Ta无法洗澡。没有两项任务重叠。

现在jmsyang0808问你，Ta有时间洗澡吗？如果能，输出 `YES` ，否则只能输出 `NO` 了QAQ~。

## 输入格式

_本题包含多组测试数据。_ 

第一行包含一个整数 $T(1\leq T\leq 10^4)$ 表示测试用例的数量。

每个测试用例的第一行包含三个整数 $n,s,m(1\leq n\leq 2\cdot 10^5,1\leq s,m\leq 10^9)$ 。

然后是 $n$ 行，其中第 $i$ 行包含两个整数 $l_i$ 和 $r_i$ $(0\leq l_i<r_i\leq m)$ 。

保证对于所有 $i>1$ ， $l_i>r_{i-1}$ 。

## 输出格式

对于每个输入用例，输出一行 `YES` 或 `NO` 。

## 说明/提示

下面是对于用例一的解释。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1999C/f37c16ccee56dc0e812638d809cb1411cb80cf1b.png)

Translated By @jmsyang0808.

## 样例 #1

### 输入

```
4
3 3 10
3 5
6 8
9 10
3 3 10
1 2
3 5
6 7
3 3 10
1 2
3 5
6 8
3 4 10
1 2
6 7
8 9
```

### 输出

```
YES
YES
NO
YES
```



---

---
title: "Spreadsheets"
layout: "post"
diff: 普及-
pid: CF1B
tag: ['模拟', '字符串', '进制']
---

# Spreadsheets

## 题目描述

In the popular spreadsheets systems (for example, in Excel) the following numeration of columns is used. The first column has number A, the second — number B, etc. till column 26 that is marked by Z. Then there are two-letter numbers: column 27 has number AA, 28 — AB, column 52 is marked by AZ. After ZZ there follow three-letter numbers, etc.

The rows are marked by integer numbers starting with 1. The cell name is the concatenation of the column and the row numbers. For example, BC23 is the name for the cell that is in column 55, row 23.

Sometimes another numeration system is used: RXCY, where X and Y are integer numbers, showing the column and the row numbers respectfully. For instance, R23C55 is the cell from the previous example.

Your task is to write a program that reads the given sequence of cell coordinates and produce each item written according to the rules of another numeration system.


## 输入格式

The first line of the input contains integer number $ n $ ( $ 1<=n<=10^{5} $ ), the number of coordinates in the test. Then there follow $ n $ lines, each of them contains coordinates. All the coordinates are correct, there are no cells with the column and/or the row numbers larger than $ 10^{6} $ .


## 输出格式

Write $ n $ lines, each line should contain a cell coordinates in the other numeration system.


## 样例 #1

### 输入

```
2
R23C55
BC23

```

### 输出

```
BC23
R23C55

```



---

---
title: "Numeric String Template"
layout: "post"
diff: 普及-
pid: CF2000C
tag: ['模拟']
---

# Numeric String Template

## 题目描述

Kristina 有一个名为 $a$ 的数组，称为模板，数组包含 $n$ 个整数。她还有 $m$ 个仅包含小写字母的字符串。这些字符串从 1 到 $m$ 编号。她想检查这些字符串是否符合模板。

一个字符串 $s$ 如果满足以下所有条件则被认为符合模板：

- 字符串 $s$ 的长度等于数组 $a$ 的元素个数。
- 数组 $a$ 中相同的数字对应到字符串 $s$ 中的相同字符。因此，如果 $a_i = a_j$，则 $s_i = s_j$（对于 $1 \le i,j \le n$）。
- 字符串 $s$ 中的相同字符对应到数组 $a$ 中的相同数字。因此，如果 $s_i = s_j$，则 $a_i = a_j$（对于 $1 \le i,j \le n$）。

换句话说，字符串中的字符和数组中的数字之间必须有一一对应的关系。例如，如果 $a = [3, 5, 2, 1, 3]$，则字符串 `abfda` 符合模板，而字符串 `afbfa` 不符合，因为字符 `f` 对应了数字 $1$ 和 $5$。

## 输入格式

- 第一行包含一个整数 $t$ ($1 \le t \le 10^4$) — 测试用例的数量。

接下来的描述是单个测试用例的内容。

- 每个测试用例的第一行包含一个整数 $n$ ($1 \le n \le 2 × 10^5$) — 数组 $a$ 的元素个数。

- 第二行包含正好 $n$ 个整数 $a_i$ ($-10^9 \le a_i \le 10^9$) — 数组 $a$ 的元素。

- 第三行包含一个整数 $m$ ($1 \le m \le 2 × 10^5$) — 要检查的字符串的数量。

- 接下来是 $m$ 个字符串，每个字符串包含非空的小写字母。

保证所有测试用例中 $n$ 的总和不超过 $2 × 10^5$，且所有字符串的总长度不超过 $2 × 10^5$。

## 输出格式

对于每个测试用例，输出 $m$ 行。

- 对于第 $i$ 个字符串，如果它符合模板，则输出 `YES`；
- 否则，输出 `NO`。

## 样例 #1

### 输入

```
3
5
3 5 2 1 3
2
abfda
afbfa
2
1 2
3
ab
abc
aa
4
5 -3 5 -3
4
aaaa
bcbc
aba
cbcb
```

### 输出

```
YES
NO
YES
NO
NO
NO
YES
NO
YES
```



---

---
title: "Index and Maximum Value"
layout: "post"
diff: 普及-
pid: CF2007B
tag: ['模拟', '贪心']
---

# Index and Maximum Value

## 题目描述

Index 在生日派对上收到了另一个整数数组 $a_1,a_2,\dots,a_n$。随后，她准备对这个数组进行一些操作。

形式化地，她决定对这个数组执行 $m$ 次操作。有两种操作类型：
- 第一种操作形如 $\texttt{+ l r}$。给定两个正整数 $l,r$，将所有满足 $1\le i\le n,l\le a_i\le r$ 的 $a_i$ 的值改为 $a_i+1$。
- 第二种操作形如 $\texttt{- l r}$。给定两个正整数 $l,r$，将所有满足 $1\le i\le n,l\le a_i\le r$ 的 $a_i$ 的值改为 $a_i-1$。

举个例子，如果给定的数组 $a$ 初始为 $[7,1,3,4,3]$，在执行操作 $\texttt{+ 2 4}$ 后，数组变为 $a=[7,1,4,5,4]$。然后，在执行操作 $\texttt{- 1 10}$ 后，数组变为 $a=[6,0,3,4,3]$。

Index 对 $a$ 数组的最大值很好奇。在每次操作之后，请告诉她 $a$ 数组中的最大值。

## 输入格式

**每个测试点有多组数据。**

第一行有一个正整数 $t$，表示数据的组数。

每组数据的第一行有两个整数 $n$ 和 $m(1\le n\le10^5,1\le m\le10^5)$，分别代表数组的长度和操作的次数。

每组数据的第二行有 $n$ 个整数 $a_1,a_2,\dots,a_n$，表示数组 $a$ 的初始值。

接下来 $m$ 行，每行描述一个操作，格式如下：
$\texttt{c l r}$ （$c\in\{\texttt{+,-}\}$，$l$ 和 $r$ 是整数，满足 $1\le l\le r\le10^9$）。

注意在若干次操作后，$a$ 数组中的某些元素可能不满足 $1\le a_i\le10^9$，就像样例中给出的那样。

保证 $\sum n\le10^5,\sum m\le 10^5$。

## 输出格式

对于每组数据，输出一行 $m$ 个整数，第 $i$ 个整数为第 $i$ 次操作后 $a$ 数组中的最大值。

### 样例解释翻译

在第一组数据中，操作过程如下：
- 在第一次操作后，数组变为 $[2,3,4,3,2]$。最大值为 $4$。
- 在第二次操作后，数组变为 $[1,2,4,2,1]$。最大值为 $4$。
- 在第三次操作后，数组变为 $[2,3,4,3,2]$。最大值为 $4$。
- 在第四次操作后，数组变为 $[3,4,5,4,3]$。最大值为 $5$。
- 在第五次操作后，数组变为 $[3,4,5,4,3]$。最大值为 $5$。
在第二组数据中，操作过程如下：
- 在第一次操作后，数组变为 $[2,4,4,5,5]$。最大值为 $5$。
- 在第二次操作后，数组变为 $[3,4,4,5,5]$。最大值为 $5$。
- 在第三次操作后，数组变为 $[3,3,3,4,4]$。最大值为 $4$。
- 在第四次操作后，数组变为 $[2,2,2,4,4]$。最大值为 $4$。
- 在第五次操作后，数组变为 $[1,1,1,3,3]$。最大值为 $3$。

## 样例 #1

### 输入

```
5
5 5
1 2 3 2 1
+ 1 3
- 2 3
+ 1 2
+ 2 4
- 6 8
5 5
1 3 3 4 5
+ 1 4
+ 2 3
- 4 5
- 3 3
- 2 6
5 5
1 1 1 1 1
+ 2 3
- 4 5
+ 1 6
- 2 5
+ 1 8
1 1
1
- 1 1
1 1
1000000000
+ 1000000000 1000000000
```

### 输出

```
4 4 4 5 5
5 5 4 4 3
1 1 2 1 2
0
1000000001
```



---

---
title: "Square or Not"
layout: "post"
diff: 普及-
pid: CF2008B
tag: ['模拟']
---

# Square or Not

## 题目描述

漂亮的二进制矩阵是指在四周边缘全为 1 而内部全为 0 的矩阵。

如下图所示为四个漂亮的二进制矩阵的示例。今天，Sakurako 玩了一种大小为 $r \times c$ 的漂亮二进制矩阵，并通过从第一行到第 $r$ 行依次记录每一行的内容，生成了一段二进制字符串 $s$。更具体地，第 $i$ 行第 $j$ 列的元素对应于字符串中的第 $((i-1) \cdot c + j)$ 个字符。

你需要检查，生成字符串 $s$ 的这个漂亮矩阵是否能成为一个方形矩阵。换句话说，你需要判断字符串 $s$ 是否可以由一个边长相等的漂亮二进制矩阵（即 $r = c$）形成。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$），表示测试用例的数量。

每个测试用例的第一行包含一个整数 $n$（$2 \le n \le 2 \cdot 10^5$），表示字符串的长度。

每个测试用例的第二行给出一个长度为 $n$ 的字符串 $s$。该字符串是由一个漂亮矩阵的行内容依次拼接而成。

保证所有测试用例中字符串长度 $n$ 的总和不超过 $2 \cdot 10^5$。

## 输出格式

对每个测试用例，如果原始矩阵可以是方形的，输出 "Yes"；否则输出 "No"。

## 示例与提示

在第二个测试用例中，字符串 `1111` 可以通过以下的矩阵得到：

$$
\begin{array}{cccc}
1 & 1 & 1 & 1 \\
\end{array}
$$

在第三个测试用例中，字符串 `111101111` 可以通过以下的矩阵得到：

$$
\begin{array}{ccc}
1 & 1 & 1 \\
1 & 0 & 1 \\
1 & 1 & 1 \\
\end{array}
$$

在第四个测试用例中，没有一个方形矩阵能够生成该字符串。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
2
11
4
1111
9
111101111
9
111111111
12
111110011111
```

### 输出

```
No
Yes
Yes
No
No
```



---

---
title: "Satyam and Counting"
layout: "post"
diff: 普及-
pid: CF2009D
tag: ['模拟']
---

# Satyam and Counting

## 题目描述

Satyam is given $ n $ distinct points on the 2D coordinate plane. It is guaranteed that $ 0 \leq y_i \leq 1 $ for all given points $ (x_i, y_i) $ . How many different nondegenerate right triangles $ ^{\text{∗}} $ can be formed from choosing three different points as its vertices?

Two triangles $ a $ and $ b $ are different if there is a point $ v $ such that $ v $ is a vertex of $ a $ but not a vertex of $ b $ .

 $ ^{\text{∗}} $ A nondegenerate right triangle has positive area and an interior $ 90^{\circ} $ angle.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains an integer $ n $ ( $ 3 \leq n \leq 2 \cdot 10^5 $ ) — the number of points.

The following $ n $ lines contain two integers $ x_i $ and $ y_i $ ( $ 0 \leq x_i \leq n $ , $ 0 \leq y_i \leq 1 $ ) — the $ i $ 'th point that Satyam can choose from. It is guaranteed that all $ (x_i, y_i) $ are pairwise distinct.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

Output an integer for each test case, the number of distinct nondegenerate right triangles that can be formed from choosing three points.

## 说明/提示

The four triangles in question for the first test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2009D/34af5d1e01dabd5b071d413da74fdbeb85cca657.png)

## 样例 #1

### 输入

```
3
5
1 0
1 1
3 0
5 0
2 1
3
0 0
1 0
3 0
9
1 0
2 0
3 0
4 0
5 0
2 1
7 1
8 1
9 1
```

### 输出

```
4
0
8
```



---

---
title: "Anya and 1100"
layout: "post"
diff: 普及-
pid: CF2036C
tag: ['模拟']
---

# Anya and 1100

## 题目描述

While rummaging through things in a distant drawer, Anya found a beautiful string $ s $ consisting only of zeros and ones.

Now she wants to make it even more beautiful by performing $ q $ operations on it.

Each operation is described by two integers $ i $ ( $ 1 \le i \le |s| $ ) and $ v $ ( $ v \in \{0, 1\} $ ) and means that the $ i $ -th character of the string is assigned the value $ v $ (that is, the assignment $ s_i = v $ is performed).

But Anya loves the number $ 1100 $ , so after each query, she asks you to tell her whether the substring "1100" is present in her string (i.e. there exist such $ 1 \le i \le |s| - 3 $ that $ s_{i}s_{i + 1}s_{i + 2}s_{i + 3} = \texttt{1100} $ ).

## 输入格式

The first line contains one integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of the test case contains the string $ s $ ( $ 1 \leq |s| \leq 2 \cdot 10^5 $ ), consisting only of the characters "0" and "1". Here $ |s| $ denotes the length of the string $ s $ .

The next line contains an integer $ q $ ( $ 1 \leq q \leq 2 \cdot 10^5 $ ) — the number of queries.

The following $ q $ lines contain two integers $ i $ ( $ 1 \leq i \leq |s| $ ) and $ v $ ( $ v \in \{0, 1\} $ ), describing the query.

It is guaranteed that the sum of $ |s| $ across all test cases does not exceed $ 2 \cdot 10^5 $ . It is also guaranteed that the sum of $ q $ across all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each query, output "YES", if "1100" is present in Anya's string; otherwise, output "NO".

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 样例 #1

### 输入

```
4
100
4
1 1
2 0
2 0
3 1
1100000
3
6 1
7 1
4 1
111010
4
1 1
5 0
4 1
5 0
0100
4
3 1
1 1
2 0
2 1
```

### 输出

```
NO
NO
NO
NO
YES
YES
NO
NO
YES
YES
YES
NO
NO
NO
NO
```



---

---
title: "Game on Paper"
layout: "post"
diff: 普及-
pid: CF203B
tag: ['模拟']
---

# Game on Paper

## 题目描述

One not particularly beautiful evening Valera got very bored. To amuse himself a little bit, he found the following game.

He took a checkered white square piece of paper, consisting of $ n×n $ cells. After that, he started to paint the white cells black one after the other. In total he painted $ m $ different cells on the piece of paper. Since Valera was keen on everything square, he wondered, how many moves (i.e. times the boy paints a square black) he should make till a black square with side $ 3 $ can be found on the piece of paper. But Valera does not know the answer to this question, so he asks you to help him.

Your task is to find the minimum number of moves, till the checkered piece of paper has at least one black square with side of $ 3 $ . Otherwise determine that such move does not exist.

## 输入格式

The first line contains two integers $ n $ and $ m $ $ (1<=n<=1000 $ , $ 1<=m<=min(n·n,10^{5})) $ — the size of the squared piece of paper and the number of moves, correspondingly.

Then, $ m $ lines contain the description of the moves. The $ i $ -th line contains two integers $ x_{i} $ , $ y_{i} $ ( $ 1<=x_{i},y_{i}<=n $ ) — the number of row and column of the square that gets painted on the $ i $ -th move.

All numbers on the lines are separated by single spaces. It is guaranteed that all moves are different. The moves are numbered starting from $ 1 $ in the order, in which they are given in the input. The columns of the squared piece of paper are numbered starting from $ 1 $ , from the left to the right. The rows of the squared piece of paper are numbered starting from $ 1 $ , from top to bottom.

## 输出格式

On a single line print the answer to the problem — the minimum number of the move after which the piece of paper has a black square with side $ 3 $ . If no such move exists, print -1.

## 样例 #1

### 输入

```
4 11
1 1
1 2
1 3
2 2
2 3
1 4
2 4
3 4
3 2
3 3
4 1

```

### 输出

```
10

```

## 样例 #2

### 输入

```
4 12
1 1
1 2
1 3
2 2
2 3
1 4
2 4
3 4
3 2
4 2
4 1
3 1

```

### 输出

```
-1

```



---

---
title: "MEX Destruction"
layout: "post"
diff: 普及-
pid: CF2049A
tag: ['模拟', '贪心']
---

# MEX Destruction

## 题目描述

Evirir 这条龙潜入了一个巫师的城堡，并发现了一个神秘的装置。由于它爱玩的天性，它开始摆弄（破坏）这个装置……

Evirir 这条龙发现了一个由 $ n $ 个非负整数组成的数组 $ a_1, a_2, \ldots, a_n $。

在一次操作中，它可以选择一个非空的子数组 $ ^{\text{∗}} $ $ b $ 并将其替换为整数 $ \operatorname{mex}(b) $ $ ^{\text{†}} $ 。它希望使用任意多次操作，使数组 $ a $ 只包含零。可以证明，在问题的约束条件下，这总是可能的。

需要找到使数组 $ a $ 只包含零所需的最小操作次数。

- $ ^{\text{∗}} $ 如果可以通过删除开头和结尾的若干（可能为零或全部）元素来获得数组 $ c $，则数组 $ c $ 是数组 $ d $ 的子数组。
- $ ^{\text{†}} $ 一个整数集合 $ f_1, f_2, \ldots, f_k $ 的最小排除值（mex）定义为集合 $ f $ 中不存在的最小的非负整数 $ x $。

## 输入格式

每个测试包含多个测试用例。第一行包含测试用例的数量 $ t $（$ 1 \le t \le 200 $）。测试用例的描述如下。

每个测试用例的第一行包含一个整数 $ n $（$ 1 \le n \le 50 $），即数组 $ a $ 的长度。

每个测试用例的第二行包含 $ n $ 个用空格分隔的整数 $ a_1, a_2, \ldots, a_n $（$ 0 \le a_i \le 100 $）。

保证所有测试用例中 $ n $ 的总和不超过 $ 500 $。

## 输出格式

对于每个测试用例，输出一行一个整数，即使数组 $ a $ 只包含零所需的最小操作次数。

## 说明/提示

在第一个测试用例中，Evirir 可以选择子数组 $ b = [1, 2, 3] $ 并将其替换为 $ \operatorname{mex}(1, 2, 3) = 0 $，将数组 $ a $ 从 $ [0, \underline{1, 2, 3}] $ 变为 $ [0, 0] $（其中选定的子数组已加下划线）。因此，答案是 $ 1 $。

在第二个测试用例中，数组 $ a $ 已经只包含 $ 0 $，所以不需要进行任何操作。

在第三个测试用例中，Evirir 可以按如下方式更改 $ a $：$ [1, \underline{0, 1, 0, 1}] \to [\underline{1, 2}] \to [0] $。这里，$ \operatorname{mex}(0, 1, 0, 1) = 2 $ 和 $ \operatorname{mex}(1, 2) = 0 $。

在第四个测试用例中，Evirir 可以选择整个数组 $ a $ 作为 $ b $，将数组 $ a $ 从 $ [\underline{3, 1, 4, 1, 5}] $ 变为 $ [0] $。

## 样例 #1

### 输入

```
10
4
0 1 2 3
6
0 0 0 0 0 0
5
1 0 1 0 1
5
3 1 4 1 5
4
3 2 1 0
7
9 100 0 89 12 2 3
4
0 3 9 0
7
0 7 0 2 0 7 0
1
0
2
0 1
```

### 输出

```
1
0
2
1
1
2
1
2
0
1
```



---

---
title: "Robot Program"
layout: "post"
diff: 普及-
pid: CF2070B
tag: ['模拟', '数学']
---

# Robot Program

## 题目描述

在坐标轴上有一个机器人。初始时，机器人位于点 $x$（$x \ne 0$）。机器人有一个长度为 $n$ 的命令序列，由字符组成，其中 L 表示向左移动一个单位（从点 $p$ 移动到点 $(p-1)$），R 表示向右移动一个单位（从点 $p$ 移动到点 $(p+1)$）。

机器人开始执行这个命令序列（每秒执行一个命令，按顺序执行）。然而，每当机器人到达点 0 时，已执行命令的计数器会被重置（即它会从头开始重新执行整个命令序列）。如果机器人完成了所有命令且未处于 0 点，它将停止运行。

你的任务是计算在接下来的 $k$ 秒内，机器人会进入点 0 多少次。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例的第一行包含三个整数 $n$、$x$ 和 $k$（$1 \le n \le 2 \cdot 10^5$；$-n \le x \le n$；$n \le k \le 10^{18}$）。

每个测试用例的第二行包含一个由 $n$ 个字符 L 和/或 R 组成的字符串 $s$。

输入额外约束：所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——在接下来的 $k$ 秒内机器人进入点 0 的次数。

## 说明/提示

第一个示例中，机器人移动路径为：$2 \rightarrow 1 \rightarrow \underline{0} \rightarrow -1 \rightarrow -2 \rightarrow -1$。机器人完成了序列中的所有指令且未处于 0 点，因此在 5 秒后停止，点 0 被进入 1 次。

第二个示例中，机器人移动路径为：$-1 \rightarrow \underline{0} \rightarrow 1 \rightarrow \underline{0} \rightarrow 1 \rightarrow \underline{0} \rightarrow 1 \rightarrow \underline{0} \rightarrow 1$。机器人运行了 8 秒，点 0 被进入 4 次。

第三个示例中，机器人移动路径为：$-2 \rightarrow -3 \rightarrow -2 \rightarrow -1 \rightarrow \underline{0} \rightarrow -1$。机器人运行了 5 秒，点 0 被进入 1 次。

第四个示例中，机器人移动路径为：$3 \rightarrow 2 \rightarrow 3 \rightarrow 4 \rightarrow 3 \rightarrow 2$。机器人完成了序列中的所有指令且未处于 0 点，因此在 5 秒后停止，未到达点 0。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
6
3 2 6
LLR
2 -1 8
RL
4 -2 5
LRRR
5 3 7
LRRLL
1 1 1
L
3 -1 4846549234412827
RLR
```

### 输出

```
1
4
1
0
1
2423274617206414
```



---

---
title: "Tung Tung Sahur"
layout: "post"
diff: 普及-
pid: CF2094D
tag: ['模拟', '字符串']
---

# Tung Tung Sahur

## 题目描述

你面前有两个鼓：一个左鼓和一个右鼓。敲击左鼓可以记录为 "L"，敲击右鼓可以记录为 "R"。

这个世界的奇怪力量变幻莫测：有时一次敲击会发出一声响，有时会发出两声响。因此，敲击左鼓可能会发出 "L" 或 "LL"，敲击右鼓可能会发出 "R" 或 "RR"。

敲击的序列记录在字符串 $p$ 中，而实际听到的声音记录在字符串 $s$ 中。给定 $p$ 和 $s$，判断字符串 $s$ 是否可能是由 $p$ 的敲击产生的结果。

例如，如果 $p=$ "LR"，那么敲击产生的结果可能是 "LR"、"LRR"、"LLR" 或 "LLRR"，但不可能是 "LLLR" 或 "LRL"。

## 输入格式

第一行包含一个整数 $t$（$1 \leq t \leq 10^4$）——独立测试用例的数量。

每个测试用例的第一行包含字符串 $p$（$1 \le |p| \le 2 \cdot 10^5$），仅由字符 "R" 和 "L" 组成，其中 $|p|$ 表示字符串 $p$ 的长度。

每个测试用例的第二行包含字符串 $s$（$1 \le |p| \le |s| \le 2 \cdot 10^5$），同样仅由字符 "R" 和 "L" 组成。

保证所有测试用例的 $|s|$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每组输入数据，如果 $s$ 可能是听到的声音，输出 "YES"，否则输出 "NO"。输出不区分大小写。


## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
R
RR
LRLR
LRLR
LR
LLLR
LLLLLRL
LLLLRRLL
LLRLRLRRL
LLLRLRRLLRRRL
```

### 输出

```
YES
YES
NO
NO
YES
```



---

---
title: "Come a Little Closer"
layout: "post"
diff: 普及-
pid: CF2114D
tag: ['模拟', '枚举']
---

# Come a Little Closer

## 题目描述

The game field is a matrix of size $ 10^9 \times 10^9 $ , with a cell at the intersection of the $ a $ -th row and the $ b $ -th column denoted as ( $ a, b $ ).

There are $ n $ monsters on the game field, with the $ i $ -th monster located in the cell ( $ x_i, y_i $ ), while the other cells are empty. No more than one monster can occupy a single cell.

You can move one monster to any cell on the field that is not occupied by another monster at most once .

After that, you must select one rectangle on the field; all monsters within the selected rectangle will be destroyed. You must pay $ 1 $ coin for each cell in the selected rectangle.

Your task is to find the minimum number of coins required to destroy all the monsters.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of monsters on the field.

The following $ n $ lines contain two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i, y_i \le 10^9 $ ) — the coordinates of the cell with the $ i $ -th monster. All pairs ( $ x_i, y_i $ ) are distinct.

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the minimum cost to destroy all $ n $ monsters.

## 说明/提示

Below are examples of optimal moves, with the cells of the rectangle to be selected highlighted in green.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2114D/925186708229ffea7667613d0cb72eebcaadb566.png) Required move for the first example.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2114D/213433b9bab32a2ca839daa9c0de4a82a4c12eb5.png) Required move for the fifth example.

## 样例 #1

### 输入

```
7
3
1 1
1 2
2 1
5
1 1
2 6
6 4
3 3
8 2
4
1 1
1 1000000000
1000000000 1
1000000000 1000000000
1
1 1
5
1 2
4 2
4 3
3 1
3 2
3
1 1
2 5
2 2
4
4 3
3 1
4 4
1 2
```

### 输出

```
3
32
1000000000000000000
1
6
4
8
```



---

---
title: "Jabber ID"
layout: "post"
diff: 普及-
pid: CF21A
tag: ['模拟', '字符串']
---

# Jabber ID

## 题目描述

一个地址由 `<username>@<hostname>[/resource]` 组成，其中 `[/resource]` 可以被省略。

- `<username>` 字段允许大写、小写字母，数字、下划线，其长度应在 $1$ 到 $16$ 之间。
- `<hostname>` 字段允许用 `.` 来分隔。每一段的要求同  `<username>` 字段，分隔出的每一部分长度在 $1$ 到 $16$，`<hostname>` 字段的总长度在 $1$ 到 $32$ 之间。
- `<resource>` 字段要求同 `<username>` 字段。


给出一个地址，询问是否合法。

## 输入格式

一行，一个字符串，表示一个地址（保证地址的字符的 ASCII 在 $33$ 到 $127$ 间），地址长度不超过 $100$ 字符。

## 输出格式

一行，如果合法输出 `YES`，否则输出 `NO`。

## 样例 #1

### 输入

```
mike@codeforces.com

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
john.smith@codeforces.ru/contest.icpc/12

```

### 输出

```
NO

```



---

---
title: "Little Elephant and Numbers"
layout: "post"
diff: 普及-
pid: CF221B
tag: ['模拟', '枚举']
---

# Little Elephant and Numbers

## 题目描述

The Little Elephant loves numbers.

He has a positive integer $ x $ . The Little Elephant wants to find the number of positive integers $ d $ , such that $ d $ is the divisor of $ x $ , and $ x $ and $ d $ have at least one common (the same) digit in their decimal representations.

Help the Little Elephant to find the described number.

## 输入格式

A single line contains a single integer $ x $ $ (1<=x<=10^{9}) $ .

## 输出格式

In a single line print an integer — the answer to the problem.

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
10

```

### 输出

```
2

```



---

---
title: "Xenia and Ringroad"
layout: "post"
diff: 普及-
pid: CF339B
tag: ['模拟']
---

# Xenia and Ringroad

## 题目描述

Xenia lives in a city that has $ n $ houses built along the main ringroad. The ringroad houses are numbered 1 through $ n $ in the clockwise order. The ringroad traffic is one way and also is clockwise.

Xenia has recently moved into the ringroad house number 1. As a result, she's got $ m $ things to do. In order to complete the $ i $ -th task, she needs to be in the house number $ a_{i} $ and complete all tasks with numbers less than $ i $ . Initially, Xenia is in the house number 1, find the minimum time she needs to complete all her tasks if moving from a house to a neighboring one along the ringroad takes one unit of time.

## 输入格式

The first line contains two integers $ n $ and $ m $ $ (2<=n<=10^{5},1<=m<=10^{5}) $ . The second line contains $ m $ integers $ a_{1},a_{2},...,a_{m} $ $ (1<=a_{i}<=n) $ . Note that Xenia can have multiple consecutive tasks in one house.

## 输出格式

Print a single integer — the time Xenia needs to complete all tasks.

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 说明/提示

In the first test example the sequence of Xenia's moves along the ringroad looks as follows: $ 1→2→3→4→1→2→3 $ . This is optimal sequence. So, she needs 6 time units.

## 样例 #1

### 输入

```
4 3
3 2 3

```

### 输出

```
6

```

## 样例 #2

### 输入

```
4 3
2 3 3

```

### 输出

```
2

```



---

---
title: "Shortest path of the king"
layout: "post"
diff: 普及-
pid: CF3A
tag: ['模拟', '贪心', '最短路']
---

# Shortest path of the king

## 题目描述

国王独自一人在国际象棋棋盘上。尽管他很孤独，但他并不会灰心，因为他有国家大事要做。例如，他必须对方格 $t$ 进行访问。因为国王没有浪费时间的习惯，所以他想从目前的位置（方格 $s$）上出发，走最少的步数。请你帮他做这件事。

在一次移动中，国王可以到达与他目前所在方格有共同的边或共同的顶点的方格里（通常情况下，他可以移动到 $8$ 个不同的方格里）。

## 输入格式

第一行包含方格 $s$ 的棋盘坐标，第二行包含方格 $t$ 的棋盘坐标。

棋盘坐标由两个字符组成，第一个是从 `a` 到 `h` 的小写拉丁字母，第二个是从 `1` 到 `8` 的数字。具体情况如上图所示。

## 输出格式

在第一行输出 $n$——国王移动的最小步数。然后接下来 $n$ 行输出移动的每一步。每次移动用 `L`、`R`、`U`、`D`、`LU`、`LD`、`RU` 或 `RD` 中的一个来描述。

`L`、`R`、`U`、`D` 分别指向左、向右、向上和向下移动，两个字母的组合代表沿着对角线移动（如 `RU` 代表向右上方移动）。如果答案不唯一，请输出任意一个答案。

## 样例 #1

### 输入

```
a8
h1

```

### 输出

```
7
RD
RD
RD
RD
RD
RD
RD

```



---

---
title: "DZY Loves Chessboard"
layout: "post"
diff: 普及-
pid: CF445A
tag: ['模拟', '字符串', '搜索', '深度优先搜索 DFS']
---

# DZY Loves Chessboard

## 题目描述

一个棋盘上有一些格子是坏的，另一些是正常的。对于每一个正常的格子，都要在上面放上棋子。
请找到一组解使没有两个相同颜色的棋子相邻(两个格子相邻为它们存在共同的边)

## 输入格式

第一行为两个数n,m。(1<=n,m<=100)
下面n行，每个格子上的字符为'-'或'.','-'表示坏掉的格子,'.'表示正常的格子。

## 输出格式

输出n行，每行m个字符。第i个字符串的第j个字符应为“W”，“B”或“ - ”。字符“W”是指在格子上放白色的棋子，“B”意味着放黑色的棋子，“ - ”表示坏掉的格子。
如果有多组答案，输出其中的一个

感谢@zhaotiensn 提供的翻译

## 样例 #1

### 输入

```
1 1
.

```

### 输出

```
B

```

## 样例 #2

### 输入

```
2 2
..
..

```

### 输出

```
BW
WB

```

## 样例 #3

### 输入

```
3 3
.-.
---
--.
```

### 输出

```
B-B
---
--B
```



---

---
title: "Game"
layout: "post"
diff: 普及-
pid: CF49D
tag: ['模拟', '构造']
---

# Game

## 题目描述

Vasya and Petya have invented a new game. Vasya takes a stripe consisting of $ 1×n $ square and paints the squares black and white. After that Petya can start moves — during a move he may choose any two neighboring squares of one color and repaint these two squares any way he wants, perhaps in different colors. Petya can only repaint the squares in white and black colors. Petya’s aim is to repaint the stripe so that no two neighboring squares were of one color. Help Petya, using the given initial coloring, find the minimum number of moves Petya needs to win.

## 输入格式

The first line contains number $ n $ ( $ 1<=n<=1000 $ ) which represents the stripe’s length. The second line contains exactly $ n $ symbols — the line’s initial coloring. 0 corresponds to a white square, 1 corresponds to a black one.

## 输出格式

If Petya cannot win with such an initial coloring, print -1. Otherwise print the minimum number of moves Petya needs to win.

## 说明/提示

In the first sample Petya can take squares 1 and 2. He repaints square 1 to black and square 2 to white.

In the second sample Petya can take squares 2 and 3. He repaints square 2 to white and square 3 to black.

## 样例 #1

### 输入

```
6
111010

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5
10001

```

### 输出

```
1

```

## 样例 #3

### 输入

```
7
1100010

```

### 输出

```
2

```

## 样例 #4

### 输入

```
5
00100

```

### 输出

```
2

```



---

---
title: "Infinite Sequence"
layout: "post"
diff: 普及-
pid: CF622A
tag: ['模拟', '数学']
---

# Infinite Sequence

## 题目描述

Consider the infinite sequence of integers: $ 1,1,2,1,2,3,1,2,3,4,1,2,3,4,5... $ . The sequence is built in the following way: at first the number $ 1 $ is written out, then the numbers from $ 1 $ to $ 2 $ , then the numbers from $ 1 $ to $ 3 $ , then the numbers from $ 1 $ to $ 4 $ and so on. Note that the sequence contains numbers, not digits. For example number $ 10 $ first appears in the sequence in position $ 55 $ (the elements are numerated from one).

Find the number on the $ n $ -th position of the sequence.

## 输入格式

The only line contains integer $ n $ ( $ 1<=n<=10^{14} $ ) — the position of the number to find.

Note that the given number is too large, so you should use $ 64 $ -bit integer type to store it. In C++ you can use the long long integer type and in Java you can use long integer type.

## 输出格式

Print the element in the $ n $ -th position of the sequence (the elements are numerated from one).

## 样例 #1

### 输入

```
3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5

```

### 输出

```
2

```

## 样例 #3

### 输入

```
10

```

### 输出

```
4

```

## 样例 #4

### 输入

```
55

```

### 输出

```
10

```

## 样例 #5

### 输入

```
56

```

### 输出

```
1

```



---

---
title: "Orchestra"
layout: "post"
diff: 普及-
pid: CF635A
tag: ['模拟', '枚举', '前缀和']
---

# Orchestra

## 题目描述

Paul is at the orchestra. The string section is arranged in an $ r×c $ rectangular grid and is filled with violinists with the exception of $ n $ violists. Paul really likes violas, so he would like to take a picture including at least $ k $ of them. Paul can take a picture of any axis-parallel rectangle in the orchestra. Count the number of possible pictures that Paul can take.

Two pictures are considered to be different if the coordinates of corresponding rectangles are different.

## 输入格式

The first line of input contains four space-separated integers $ r $ , $ c $ , $ n $ , $ k $ ( $ 1<=r,c,n<=10 $ , $ 1<=k<=n $ ) — the number of rows and columns of the string section, the total number of violas, and the minimum number of violas Paul would like in his photograph, respectively.

The next $ n $ lines each contain two integers $ x_{i} $ and $ y_{i} $ ( $ 1<=x_{i}<=r $ , $ 1<=y_{i}<=c $ ): the position of the $ i $ -th viola. It is guaranteed that no location appears more than once in the input.

## 输出格式

Print a single integer — the number of photographs Paul can take which include at least $ k $ violas.

## 说明/提示

We will use '\*' to denote violinists and '\#' to denote violists.

In the first sample, the orchestra looks as follows

`<br></br>*#<br></br>**<br></br>` Paul can take a photograph of just the viola, the $ 1×2 $ column containing the viola, the $ 2×1 $ row containing the viola, or the entire string section, for $ 4 $ pictures total.In the second sample, the orchestra looks as follows

`<br></br>#*<br></br>*#<br></br>#*<br></br>` Paul must take a photograph of the entire section.In the third sample, the orchestra looks the same as in the second sample.

## 样例 #1

### 输入

```
2 2 1 1
1 2

```

### 输出

```
4

```

## 样例 #2

### 输入

```
3 2 3 3
1 1
3 1
2 2

```

### 输出

```
1

```

## 样例 #3

### 输入

```
3 2 3 2
1 1
3 1
2 2

```

### 输出

```
4

```



---

---
title: "Petya and Java"
layout: "post"
diff: 普及-
pid: CF66A
tag: ['模拟', '字符串', '枚举']
---

# Petya and Java

## 题目描述

Little Petya has recently started attending a programming club. Naturally he is facing the problem of choosing a programming language. After long considerations he realized that Java is the best choice. The main argument in favor of choosing Java was that it has a very large integer data type, called BigInteger.

But having attended several classes of the club, Petya realized that not all tasks require using the BigInteger type. It turned out that in some tasks it is much easier to use small data types. That's why a question arises: "Which integer type to use if one wants to store a positive integer $ n $ ?"

Petya knows only 5 integer types:

1\) byte occupies 1 byte and allows you to store numbers from $ -128 $ to $ 127 $

2\) short occupies 2 bytes and allows you to store numbers from $ -32768 $ to $ 32767 $

3\) int occupies 4 bytes and allows you to store numbers from $ -2147483648 $ to $ 2147483647 $

4\) long occupies 8 bytes and allows you to store numbers from $ -9223372036854775808 $ to $ 9223372036854775807 $

5\) BigInteger can store any integer number, but at that it is not a primitive type, and operations with it are much slower.

For all the types given above the boundary values are included in the value range.

From this list, Petya wants to choose the smallest type that can store a positive integer $ n $ . Since BigInteger works much slower, Peter regards it last. Help him.

## 输入格式

The first line contains a positive number $ n $ . It consists of no more than $ 100 $ digits and doesn't contain any leading zeros. The number $ n $ can't be represented as an empty string.

Please, do not use %lld specificator to read or write 64-bit integers in C++. It is preffered to use cout (also you may use %I64d).

## 输出格式

Print the first type from the list "byte, short, int, long, BigInteger", that can store the natural number $ n $ , in accordance with the data given above.

## 样例 #1

### 输入

```
127

```

### 输出

```
byte

```

## 样例 #2

### 输入

```
130

```

### 输出

```
short

```

## 样例 #3

### 输入

```
123456789101112131415161718192021222324

```

### 输出

```
BigInteger

```



---

---
title: "Opponents"
layout: "post"
diff: 普及-
pid: CF688A
tag: ['模拟', '贪心', '概率论']
---

# Opponents

## 题目描述

# 问题描述

小白有 n 个对手，他每天都要和这些对手PK。对于每一天，如果 n 个对手全部到齐，那么小白就输了一场，否则小白就赢了一场。特别的，如果某天一个对手都没有到，也算小白赢。现在已知对手 d 天的出场情况，请计算小白最多能连胜多少场。

## 输入格式

第一行，两个整数 n , d ( 1 ≤ n,d ≤ 100 )。接下来 d 行，每行 n 个 0 或 1 的整数，依次表示这一天所有对手的到场情况， 1 表示到场， 0 表示缺席。

## 输出格式

一个整数，表示最多的连胜场次。

## 样例 #1

### 输入

```
2 2
10
00

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4 1
0100

```

### 输出

```
1

```

## 样例 #3

### 输入

```
4 5
1101
1111
0110
1011
1111

```

### 输出

```
2

```



---

---
title: "Exponential notation"
layout: "post"
diff: 普及-
pid: CF691C
tag: ['模拟', '数学']
---

# Exponential notation

## 题目描述

You are given a positive decimal number $ x $ .

Your task is to convert it to the "simple exponential notation".

Let $ x=a·10^{b} $ , where $ 1<=a&lt;10 $ , then in general case the "simple exponential notation" looks like "aEb". If $ b $ equals to zero, the part "Eb" should be skipped. If $ a $ is an integer, it should be written without decimal point. Also there should not be extra zeroes in $ a $ and $ b $ .

## 输入格式

The only line contains the positive decimal number $ x $ . The length of the line will not exceed $ 10^{6} $ . Note that you are given too large number, so you can't use standard built-in data types "float", "double" and other.

## 输出格式

Print the only line — the "simple exponential notation" of the given number $ x $ .

## 样例 #1

### 输入

```
16

```

### 输出

```
1.6E1

```

## 样例 #2

### 输入

```
01.23400

```

### 输出

```
1.234

```

## 样例 #3

### 输入

```
.100

```

### 输出

```
1E-1

```

## 样例 #4

### 输入

```
100.

```

### 输出

```
1E2

```



---

---
title: "Pineapple Incident"
layout: "post"
diff: 普及-
pid: CF697A
tag: ['模拟', '数学', '枚举']
---

# Pineapple Incident

## 题目描述

Ted有一个菠萝。这个菠萝可以像狗一样叫！在第 $t$ 秒它第一次叫。然后每隔 $s$ 秒之后它会叫一次，在叫这一次之后还会在后一秒再叫一次。意思就是说它会在 $t$ 秒，$t+s$ 秒，$t+s+1$ 秒，$t+2s$ 秒，$t+2s+1$ 秒分别叫一次，以此类推。 

Barney在早上醒来，他想吃个菠萝，但这只菠萝叫的时候Barney不能吃它。Barney打算在 $x$ 秒吃它，所以请你告诉Barney在x秒的时候，这个菠萝会不会叫。

## 输入格式

仅输入一行，输入 $t,s,x$($0\le t,x\le 10^9$，$2\leq s\leq 10^9$)分别为菠萝第一次叫的时间，叫的间隔以及Barney想吃的时间。

## 输出格式

如果菠萝要叫的话，输出YES，否则输出NO。

## 样例 #1

### 输入

```
3 10 4

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
3 10 3

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
3 8 51

```

### 输出

```
YES

```

## 样例 #4

### 输入

```
3 8 52

```

### 输出

```
YES

```



---

---
title: "Alice, Bob and Chocolate"
layout: "post"
diff: 普及-
pid: CF6C
tag: ['模拟']
---

# Alice, Bob and Chocolate

## 题目描述

Alice and Bob like games. And now they are ready to start a new game. They have placed $ n $ chocolate bars in a line. Alice starts to eat chocolate bars one by one from left to right, and Bob — from right to left. For each chocololate bar the time, needed for the player to consume it, is known (Alice and Bob eat them with equal speed). When the player consumes a chocolate bar, he immediately starts with another. It is not allowed to eat two chocolate bars at the same time, to leave the bar unfinished and to make pauses. If both players start to eat the same bar simultaneously, Bob leaves it to Alice as a true gentleman.

How many bars each of the players will consume?

## 输入格式

The first line contains one integer $ n $ ( $ 1<=n<=10^{5} $ ) — the amount of bars on the table. The second line contains a sequence $ t_{1},t_{2},...,t_{n} $ ( $ 1<=t_{i}<=1000 $ ), where $ t_{i} $ is the time (in seconds) needed to consume the $ i $ -th bar (in the order from left to right).

## 输出格式

Print two numbers $ a $ and $ b $ , where $ a $ is the amount of bars consumed by Alice, and $ b $ is the amount of bars consumed by Bob.

## 样例 #1

### 输入

```
5
2 9 8 2 7

```

### 输出

```
2 3

```



---

---
title: "Ilya and tic-tac-toe game"
layout: "post"
diff: 普及-
pid: CF754B
tag: ['模拟', '搜索', '枚举']
---

# Ilya and tic-tac-toe game

## 题目描述

题目大意：

伊莉雅是一个4x4井字棋的年迈棋手，他总是用x（英文小写）棋，今天，他跟他的朋友亚瑟玩了很多很多局游戏，亚瑟很累了，但是现在还剩下最后一场游戏，现在轮到伊莉雅下棋，请问伊莉雅下完这颗棋子后能否取得胜利？
井字棋规则：

 棋盘的规格为4*4，其中伊莉雅棋子为x，亚瑟的棋子为o（英文小写o），x先下，o后下，当某种棋子在棋盘上连成三个时取得胜利！（这三个棋子可以是水平、竖直或斜方向的连续三个）

## 输入格式

输入的数据为给定的棋盘，其中.为空格，x（英文小写）为伊莉雅的棋子， o（英文小写）为亚瑟的棋子，棋盘保证有空格子，现在轮到伊莉雅。 （有可能整个棋盘都没有棋子，意味着亚瑟还没有下）

## 输出格式

输出为单行：如果伊莉雅下完一颗棋子后能够取得胜利，输出YES，如果不能，则输出NO。


感谢@icebird  提供的翻译

## 样例 #1

### 输入

```
xx..
.oo.
x...
oox.

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
x.ox
ox..
x.o.
oo.x

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
x..x
..oo
o...
x.xo

```

### 输出

```
YES

```

## 样例 #4

### 输入

```
o.x.
o...
.x..
ooxx

```

### 输出

```
NO

```



---

---
title: "Shell Game"
layout: "post"
diff: 普及-
pid: CF777A
tag: ['模拟', '枚举']
---

# Shell Game

## 题目描述

Bomboslav likes to look out of the window in his room and watch lads outside playing famous shell game. The game is played by two persons: operator and player. Operator takes three similar opaque shells and places a ball beneath one of them. Then he shuffles the shells by swapping some pairs and the player has to guess the current position of the ball.

Bomboslav noticed that guys are not very inventive, so the operator always swaps the left shell with the middle one during odd moves (first, third, fifth, etc.) and always swaps the middle shell with the right one during even moves (second, fourth, etc.).

Let's number shells from $ 0 $ to $ 2 $ from left to right. Thus the left shell is assigned number $ 0 $ , the middle shell is $ 1 $ and the right shell is $ 2 $ . Bomboslav has missed the moment when the ball was placed beneath the shell, but he knows that exactly $ n $ movements were made by the operator and the ball was under shell $ x $ at the end. Now he wonders, what was the initial position of the ball?

## 输入格式

The first line of the input contains an integer $ n $ ( $ 1<=n<=2·10^{9} $ ) — the number of movements made by the operator.

The second line contains a single integer $ x $ ( $ 0<=x<=2 $ ) — the index of the shell where the ball was found after $ n $ movements.

## 输出格式

Print one integer from $ 0 $ to $ 2 $ — the index of the shell where the ball was initially placed.

## 说明/提示

In the first sample, the ball was initially placed beneath the middle shell and the operator completed four movements.

1. During the first move operator swapped the left shell and the middle shell. The ball is now under the left shell.
2. During the second move operator swapped the middle shell and the right one. The ball is still under the left shell.
3. During the third move operator swapped the left shell and the middle shell again. The ball is again in the middle.
4. Finally, the operators swapped the middle shell and the right shell. The ball is now beneath the right shell.

## 样例 #1

### 输入

```
4
2

```

### 输出

```
1

```

## 样例 #2

### 输入

```
1
1

```

### 输出

```
0

```



---

---
title: "Mike and palindrome"
layout: "post"
diff: 普及-
pid: CF798A
tag: ['模拟', '字符串', '概率论']
---

# Mike and palindrome

## 题目描述

麦克有一个只有小写英文字母的字符串 _s_ 。他想通过改变一个字符 的方式来让整个字符串成为回文字符串。

回文字符串是一个正着读和反着读都一样的字符串。比如说"z"， "aaa"，"aba"， "abccba"是回文字符串，而"codeforces"， "reality"和"ab"不是回文字符串。

## 输入格式

一行，包括一个字符串 _s_ (1<=|s|<=15)。

## 输出格式

如果麦克能通过只改变一个字符就使整个字符串成回文字符串的话就输出"YES"(不包括双引号)，不然的话就输出"NO"(同样不包括双引号)

感谢@deadpool123  提供的翻译

## 样例 #1

### 输入

```
abccaa

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
abbcca

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
abcda

```

### 输出

```
YES

```



---

---
title: "Kalevitch and Chess"
layout: "post"
diff: 普及-
pid: CF7A
tag: ['模拟', '贪心', '概率论']
---

# Kalevitch and Chess

## 题目描述

A famous Berland's painter Kalevitch likes to shock the public. One of his last obsessions is chess. For more than a thousand years people have been playing this old game on uninteresting, monotonous boards. Kalevitch decided to put an end to this tradition and to introduce a new attitude to chessboards.

As before, the chessboard is a square-checkered board with the squares arranged in a $ 8×8 $ grid, each square is painted black or white. Kalevitch suggests that chessboards should be painted in the following manner: there should be chosen a horizontal or a vertical line of 8 squares (i.e. a row or a column), and painted black. Initially the whole chessboard is white, and it can be painted in the above described way one or more times. It is allowed to paint a square many times, but after the first time it does not change its colour any more and remains black. Kalevitch paints chessboards neatly, and it is impossible to judge by an individual square if it was painted with a vertical or a horizontal stroke.

Kalevitch hopes that such chessboards will gain popularity, and he will be commissioned to paint chessboards, which will help him ensure a comfortable old age. The clients will inform him what chessboard they want to have, and the painter will paint a white chessboard meeting the client's requirements.

It goes without saying that in such business one should economize on everything — for each commission he wants to know the minimum amount of strokes that he has to paint to fulfill the client's needs. You are asked to help Kalevitch with this task.

## 输入格式

The input file contains 8 lines, each of the lines contains 8 characters. The given matrix describes the client's requirements, W character stands for a white square, and B character — for a square painted black.

It is guaranteed that client's requirments can be fulfilled with a sequence of allowed strokes (vertical/column or horizontal/row).

## 输出格式

Output the only number — the minimum amount of rows and columns that Kalevitch has to paint on the white chessboard to meet the client's requirements.

## 样例 #1

### 输入

```
WWWBWWBW
BBBBBBBB
WWWBWWBW
WWWBWWBW
WWWBWWBW
WWWBWWBW
WWWBWWBW
WWWBWWBW

```

### 输出

```
3

```

## 样例 #2

### 输入

```
WWWWWWWW
BBBBBBBB
WWWWWWWW
WWWWWWWW
WWWWWWWW
WWWWWWWW
WWWWWWWW
WWWWWWWW

```

### 输出

```
1

```



---

---
title: "Karen and Morning"
layout: "post"
diff: 普及-
pid: CF816A
tag: ['模拟', '字符串']
---

# Karen and Morning

## 题目描述

可怜已经准备好迎接在学校的新的一天。

现在是hh:mm，一个被以24小时制给与的时间。正如你所知道的，可怜喜欢回文，并且她相信如果在她醒来时的时间是回文的话会给她带来好运。

当她醒来时时间是回文的话，她最少应当睡多长时间？

记住，一个回文数是一个从前读和从后读相同的字符串。例如，05:39是不是回文数，因为05:39倒着读是93:50。另一方面，05:50是回文，因为05:50倒着读是05:50。

## 输入格式

仅有一行，包含一个格式为hh:mm的字符串（$00\leq hh\leq23,00\leq mm\leq59$ ）。

## 输出格式

仅输出一行一个整数，表示要使她醒来时的时间是回文，她所睡的最少时间。

## 说明/提示

在第一个样例中，可怜最少应睡的时间为$11$ ，这样她可以在05:50时醒来，这是一个回文时间。

在第二个样例中，可怜可以立刻起来，当前时间13:31就是一个回文。

在第三个样例中，可怜最少应睡的时间为$1$ 分钟。她可以在00:00醒来，这是一个回文时间。

感谢@Khassar 提供的翻译

## 样例 #1

### 输入

```
05:39

```

### 输出

```
11

```

## 样例 #2

### 输入

```
13:31

```

### 输出

```
0

```

## 样例 #3

### 输入

```
23:59

```

### 输出

```
1

```



---

---
title: "Chess Tourney"
layout: "post"
diff: 普及-
pid: CF845A
tag: ['模拟', '贪心', '排序']
---

# Chess Tourney

## 题目描述

Berland annual chess tournament is coming!

Organizers have gathered $ 2·n $ chess players who should be divided into two teams with $ n $ people each. The first team is sponsored by BerOil and the second team is sponsored by BerMobile. Obviously, organizers should guarantee the win for the team of BerOil.

Thus, organizers should divide all $ 2·n $ players into two teams with $ n $ people each in such a way that the first team always wins.

Every chess player has its rating $ r_{i} $ . It is known that chess player with the greater rating always wins the player with the lower rating. If their ratings are equal then any of the players can win.

After teams assignment there will come a drawing to form $ n $ pairs of opponents: in each pair there is a player from the first team and a player from the second team. Every chess player should be in exactly one pair. Every pair plays once. The drawing is totally random.

Is it possible to divide all $ 2·n $ players into two teams with $ n $ people each so that the player from the first team in every pair wins regardless of the results of the drawing?

## 输入格式

The first line contains one integer $ n $ ( $ 1<=n<=100 $ ).

The second line contains $ 2·n $ integers $ a_{1},a_{2},...\ a_{2n} $ ( $ 1<=a_{i}<=1000 $ ).

## 输出格式

If it's possible to divide all $ 2·n $ players into two teams with $ n $ people each so that the player from the first team in every pair wins regardless of the results of the drawing, then print "YES". Otherwise print "NO".

## 样例 #1

### 输入

```
2
1 3 2 4

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
1
3 3

```

### 输出

```
NO

```



---

---
title: "ACM ICPC"
layout: "post"
diff: 普及-
pid: CF886A
tag: ['模拟', '枚举']
---

# ACM ICPC

## 题目描述

In a small but very proud high school it was decided to win ACM ICPC. This goal requires to compose as many teams of three as possible, but since there were only $ 6 $ students who wished to participate, the decision was to build exactly two teams.

After practice competition, participant number $ i $ got a score of $ a_{i} $ . Team score is defined as sum of scores of its participants. High school management is interested if it's possible to build two teams with equal scores. Your task is to answer that question.

## 输入格式

The single line contains six integers $ a_{1},...,a_{6} $ ( $ 0<=a_{i}<=1000 $ ) — scores of the participants

## 输出格式

Print "YES" (quotes for clarity), if it is possible to build teams with equal score, and "NO" otherwise.

You can print each character either upper- or lowercase ("YeS" and "yes" are valid when the answer is "YES").

## 说明/提示

In the first sample, first team can be composed of $ 1 $ st, $ 2 $ nd and $ 6 $ th participant, second — of $ 3 $ rd, $ 4 $ th and $ 5 $ th: team scores are $ 1+3+1=2+1+2=5 $ .

In the second sample, score of participant number $ 6 $ is too high: his team score will be definitely greater.

## 样例 #1

### 输入

```
1 3 2 1 2 1

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
1 1 1 1 1 99

```

### 输出

```
NO

```



---

---
title: "Train and Peter"
layout: "post"
diff: 普及-
pid: CF8A
tag: ['模拟', '字符串']
---

# Train and Peter

## 题目描述

Peter 很喜欢坐火车去旅行。他实在是太喜欢坐火车了，以至于在火车上睡着了（雾）。

在一个夏天，Peter 正在一个从 A 城开往 B 城的列车上。像往常一样，他睡着了。突然，他醒了过来（?），开始看窗外的景物。他发现每一个火车站都有一面彩旗（旗上只有一种颜色）。

Peter 开始记忆他看到的彩旗的顺序。但是很快地，他又睡着了。不幸地，他没睡多久又醒来了，并且他开始继续记他看到的彩旗。一段时间以后，他又睡着了，这次直到旅途结束都没醒来。

到站以后，他告诉了他的父母他在旅途中看到的彩旗的顺序——在他中途睡着之前和中途睡着之后分别看到的两个颜色序列。

他的父母知道 Peter 特别喜欢幻想，所以他们把 Peter 说的序列给了你，并请你判断他的乘车方向。

他的父母用不同的小写字母表示不同的颜色。相同字母表示相同颜色，不同字母表示不同颜色。

## 输入格式

输入共有三行。第一行包括一个连续的，不为空且只有小写字母的字符串 $s_0$，表示从 A 到 B 依次每个站的彩旗的颜色（A 站和 B 站没有彩旗）。列车从 B 到 A 也会经过同样的车站——以相反的顺序而已。

第二行和第三行分别为 Peter 两次看到的序列 $s_1$ 和 $s_2$。两个序列都包括连续的小写字母且不为空。

## 输出格式

一行，输出以下四种单词之一（不包括引号）：

`forward`：Peter 只可能在从 A 到 B 的旅途中看到这样的序列。

`backward`：Peter 只可能在从 B 到 A 的旅途中看到这样的序列。

`both`：Peter 既可能在从 A 到 B 的旅途中看到，也可能在从 B 到 A 的旅途中看到这样的序列。

`fantasy`：Peter 不可能看到这样的序列。

## 说明/提示

列车一直都在移动，所以一面同样的旗子不可能被看到两次。

## 样例 #1

### 输入

```
atob
a
b

```

### 输出

```
forward

```

## 样例 #2

### 输入

```
aaacaaa
aca
aa

```

### 输出

```
both

```



---

---
title: "Tricky Alchemy"
layout: "post"
diff: 普及-
pid: CF912A
tag: ['模拟', '数学', '概率论']
---

# Tricky Alchemy

## 题目描述

During the winter holidays, the demand for Christmas balls is exceptionally high. Since it's already $ 2018 $ , the advances in alchemy allow easy and efficient ball creation by utilizing magic crystals.

Grisha needs to obtain some yellow, green and blue balls. It's known that to produce a yellow ball one needs two yellow crystals, green — one yellow and one blue, and for a blue ball, three blue crystals are enough.

Right now there are $ A $ yellow and $ B $ blue crystals in Grisha's disposal. Find out how many additional crystals he should acquire in order to produce the required number of balls.

## 输入格式

The first line features two integers $ A $ and $ B $ ( $ 0<=A,B<=10^{9} $ ), denoting the number of yellow and blue crystals respectively at Grisha's disposal.

The next line contains three integers $ x $ , $ y $ and $ z $ ( $ 0<=x,y,z<=10^{9} $ ) — the respective amounts of yellow, green and blue balls to be obtained.

## 输出格式

Print a single integer — the minimum number of crystals that Grisha should acquire in addition.

## 说明/提示

In the first sample case, Grisha needs five yellow and four blue crystals to create two yellow balls, one green ball, and one blue ball. To do that, Grisha needs to obtain two additional crystals: one yellow and one blue.

## 样例 #1

### 输入

```
4 3
2 1 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3 9
1 1 3

```

### 输出

```
1

```

## 样例 #3

### 输入

```
12345678 87654321
43043751 1000000000 53798715

```

### 输出

```
2147483648

```



---

---
title: "Tea Queue"
layout: "post"
diff: 普及-
pid: CF920B
tag: ['模拟', '枚举', '队列']
---

# Tea Queue

## 题目描述

Recently $ n $ students from city S moved to city P to attend a programming camp.

They moved there by train. In the evening, all students in the train decided that they want to drink some tea. Of course, no two people can use the same teapot simultaneously, so the students had to form a queue to get their tea.

 $ i $ -th student comes to the end of the queue at the beginning of $ l_{i} $ -th second. If there are multiple students coming to the queue in the same moment, then the student with greater index comes after the student with lesser index. Students in the queue behave as follows: if there is nobody in the queue before the student, then he uses the teapot for exactly one second and leaves the queue with his tea; otherwise the student waits for the people before him to get their tea. If at the beginning of $ r_{i} $ -th second student $ i $ still cannot get his tea (there is someone before him in the queue), then he leaves the queue without getting any tea.

For each student determine the second he will use the teapot and get his tea (if he actually gets it).

## 输入格式

The first line contains one integer $ t $ — the number of test cases to solve ( $ 1<=t<=1000 $ ).

Then $ t $ test cases follow. The first line of each test case contains one integer $ n $ ( $ 1<=n<=1000 $ ) — the number of students.

Then $ n $ lines follow. Each line contains two integer $ l_{i} $ , $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=5000 $ ) — the second $ i $ -th student comes to the end of the queue, and the second he leaves the queue if he still cannot get his tea.

It is guaranteed that for every ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920B/748ee9e1ae91d0e555bb85d14ee499f01d330017.png) condition $ l_{i-1}<=l_{i} $ holds.

The sum of $ n $ over all test cases doesn't exceed $ 1000 $ .

Note that in hacks you have to set $ t=1 $ .

## 输出格式

For each test case print $ n $ integers. $ i $ -th of them must be equal to the second when $ i $ -th student gets his tea, or $ 0 $ if he leaves without tea.

## 说明/提示

The example contains $ 2 $ tests:

1. During $ 1 $ -st second, students $ 1 $ and $ 2 $ come to the queue, and student $ 1 $ gets his tea. Student $ 2 $ gets his tea during $ 2 $ -nd second.
2. During $ 1 $ -st second, students $ 1 $ and $ 2 $ come to the queue, student $ 1 $ gets his tea, and student $ 2 $ leaves without tea. During $ 2 $ -nd second, student $ 3 $ comes and gets his tea.

## 样例 #1

### 输入

```
2
2
1 3
1 4
3
1 5
1 1
2 3

```

### 输出

```
1 2 
1 0 2 

```



---

---
title: "Lara Croft and the New Game"
layout: "post"
diff: 普及-
pid: CF976B
tag: ['模拟', '数学']
---

# Lara Croft and the New Game

## 题目描述

You might have heard about the next game in Lara Croft series coming out this year. You also might have watched its trailer. Though you definitely missed the main idea about its plot, so let me lift the veil of secrecy.

Lara is going to explore yet another dangerous dungeon. Game designers decided to use good old 2D environment. The dungeon can be represented as a rectangle matrix of $ n $ rows and $ m $ columns. Cell $ (x,y) $ is the cell in the $ x $ -th row in the $ y $ -th column. Lara can move between the neighbouring by side cells in all four directions.

Moreover, she has even chosen the path for herself to avoid all the traps. She enters the dungeon in cell $ (1,1) $ , that is top left corner of the matrix. Then she goes down all the way to cell $ (n,1) $ — the bottom left corner. Then she starts moving in the snake fashion — all the way to the right, one cell up, then to the left to the cell in $ 2 $ -nd column, one cell up. She moves until she runs out of non-visited cells. $ n $ and $ m $ given are such that she always end up in cell $ (1,2) $ .

Lara has already moved to a neighbouring cell $ k $ times. Can you determine her current position?

## 输入格式

The only line contains three integers $ n $ , $ m $ and $ k $ ( $ 2<=n,m<=10^{9} $ ,  $ n $ is always even, $ 0<=k<n·m $ ). Note that $ k $ doesn't fit into $ 32 $ -bit integer type!

## 输出格式

Print the cell (the row and the column where the cell is situated) where Lara ends up after she moves $ k $ times.

## 说明/提示

Here is her path on matrix $ 4 $ by $ 3 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF976B/1b2df8f31f927201c078b0cd1ef3dccbc8991311.png)

## 样例 #1

### 输入

```
4 3 0

```

### 输出

```
1 1

```

## 样例 #2

### 输入

```
4 3 11

```

### 输出

```
1 2

```

## 样例 #3

### 输入

```
4 3 7

```

### 输出

```
3 2

```



---

---
title: "A Tide of Riverscape"
layout: "post"
diff: 普及-
pid: CF989B
tag: ['模拟']
---

# A Tide of Riverscape

## 题目描述

**题目大意：**

给定一个由'0','1','.'构成的字符串，问可不可能无论'.'是什么，这个字符串都存在长度为$p$的周期

## 输入格式

一行两个数，$n,p$，$1<=p<=n<=2000$

以下一行，一个长度为$n$的字符串

## 输出格式

如果不满足条件，输出不满足条件的字符串（把'.'用'0'或'1'替换），否则输出"No"

感谢@守望 提供翻译

## 样例 #1

### 输入

```
10 7
1.0.1.0.1.

```

### 输出

```
1000100010

```

## 样例 #2

### 输入

```
10 6
1.0.1.1000

```

### 输出

```
1001101000

```

## 样例 #3

### 输入

```
10 9
1........1

```

### 输出

```
No

```



---

