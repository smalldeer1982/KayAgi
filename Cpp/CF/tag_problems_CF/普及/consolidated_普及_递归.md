---
title: "Three Parts of the Array"
layout: "post"
diff: 普及/提高-
pid: CF1006C
tag: ['递归', '深度优先搜索 DFS', '前缀和']
---

# Three Parts of the Array

## 题目描述

**问题描述**  
给定一个长度为n的整数序列$\{d_1,d_2,\dots,d_n\}$。  
你的任务是将序列分成3部分，每部分可以是空的，并保证每一个数都属于这三个部分的某一个，每一部分都必须是一些连续的整数。  
设三部分的和分别为$sum_1$,$sum_2$,$sum_3$。  那么你需要在所有划分方案中找到一个方案使得$sum_1=sum_3$且$sum_1$尽可能的大。  
确切的说，如果第一部分包含$a$个整数，第二部分包含$b$个整数而第三部分包含$c$个，那么应该有
$$sum_1 = \sum\limits_{1 \le i \le a}d_i,$$
$$sum_2 = \sum\limits_{a + 1 \le i \le a + b}d_i,$$
$$sum_3 = \sum\limits_{a + b + 1 \le i \le a + b + c}d_i.$$
并且对于空的那部分，它的和为0。  
你需要在所有划分方案中找到一个方案使得$sum_1=sum_3$且$sum_1$尽可能的大。

## 输入格式

第一行一个整数$n(1 \le n \le 2 \cdot 10^5)$  
第二行包含n个整数$d_1, d_2, \dots, d_n(1 \le d_i \le 10^9)$

## 输出格式

一行一个整数，表示$sum_1$的最大值  
显然，至少有一种划分方案是合法的$(a=c=0,b=n)$

## 样例 #1

### 输入

```
5
1 3 1 1 4

```

### 输出

```
5

```

## 样例 #2

### 输入

```
5
1 3 2 1 4

```

### 输出

```
4

```

## 样例 #3

### 输入

```
3
4 1 2

```

### 输出

```
0

```



---

---
title: "Catch Overflow!"
layout: "post"
diff: 普及/提高-
pid: CF1175B
tag: ['模拟', '递归']
---

# Catch Overflow!

## 题目描述

You are given a function $ f $ written in some basic language. The function accepts an integer value, which is immediately written into some variable $ x $ . $ x $ is an integer variable and can be assigned values from $ 0 $ to $ 2^{32}-1 $ . The function contains three types of commands:

- for $ n $ — for loop;
- end — every command between "for $ n $ " and corresponding "end" is executed $ n $ times;
- add — adds 1 to $ x $ .

After the execution of these commands, value of $ x $ is returned.

Every "for $ n $ " is matched with "end", thus the function is guaranteed to be valid. "for $ n $ " can be immediately followed by "end"."add" command can be outside of any for loops.

Notice that "add" commands might overflow the value of $ x $ ! It means that the value of $ x $ becomes greater than $ 2^{32}-1 $ after some "add" command.

Now you run $ f(0) $ and wonder if the resulting value of $ x $ is correct or some overflow made it incorrect.

If overflow happened then output "OVERFLOW!!!", otherwise print the resulting value of $ x $ .

## 输入格式

The first line contains a single integer $ l $ ( $ 1 \le l \le 10^5 $ ) — the number of lines in the function.

Each of the next $ l $ lines contains a single command of one of three types:

- for $ n $ ( $ 1 \le n \le 100 $ ) — for loop;
- end — every command between "for $ n $ " and corresponding "end" is executed $ n $ times;
- add — adds 1 to $ x $ .

## 输出格式

If overflow happened during execution of $ f(0) $ , then output "OVERFLOW!!!", otherwise print the resulting value of $ x $ .

## 说明/提示

In the first example the first "add" is executed 1 time, the second "add" is executed 150 times and the last "add" is executed 10 times. Note that "for $ n $ " can be immediately followed by "end" and that "add" can be outside of any for loops.

In the second example there are no commands "add", thus the returning value is 0.

In the third example "add" command is executed too many times, which causes $ x $ to go over $ 2^{32}-1 $ .

## 样例 #1

### 输入

```
9
add
for 43
end
for 10
for 15
add
end
add
end

```

### 输出

```
161

```

## 样例 #2

### 输入

```
2
for 62
end

```

### 输出

```
0

```

## 样例 #3

### 输入

```
11
for 100
for 100
for 100
for 100
for 100
add
end
end
end
end
end

```

### 输出

```
OVERFLOW!!!

```



---

---
title: "STL"
layout: "post"
diff: 普及/提高-
pid: CF190C
tag: ['字符串', '递归']
---

# STL

## 题目描述

Vasya used to be an accountant before the war began and he is one of the few who knows how to operate a computer, so he was assigned as the programmer.

We all know that programs often store sets of integers. For example, if we have a problem about a weighted directed graph, its edge can be represented by three integers: the number of the starting vertex, the number of the final vertex and the edge's weight. So, as Vasya was trying to represent characteristics of a recently invented robot in his program, he faced the following problem.

Vasya is not a programmer, so he asked his friend Gena, what the convenient way to store $ n $ integers is. Gena used to code in language X-- and so he can use only the types that occur in this language. Let's define, what a "type" is in language X--:

- First, a type is a string "int".
- Second, a type is a string that starts with "pair", then followed by angle brackets listing exactly two comma-separated other types of language X--. This record contains no spaces.
- No other strings can be regarded as types.

More formally: type := int | pair<type,type>. For example, Gena uses the following type for graph edges: pair<int,pair<int,int>>.

Gena was pleased to help Vasya, he dictated to Vasya a type of language X--, that stores $ n $ integers. Unfortunately, Gena was in a hurry, so he omitted the punctuation. Now Gena has already left and Vasya can't find the correct punctuation, resulting in a type of language X--, however hard he tries.

Help Vasya and add the punctuation marks so as to receive the valid type of language X--. Otherwise say that the task is impossible to perform.

## 输入格式

The first line contains a single integer $ n $ $ (1<=n<=10^{5}) $ , showing how many numbers the type dictated by Gena contains.

The second line contains space-separated words, said by Gena. Each of them is either "pair" or "int" (without the quotes).

It is guaranteed that the total number of words does not exceed $ 10^{5} $ and that among all the words that Gena said, there are exactly $ n $ words "int".

## 输出格式

If it is possible to add the punctuation marks so as to get a correct type of language X-- as a result, print a single line that represents the resulting type. Otherwise, print "Error occurred" (without the quotes). Inside the record of a type should not be any extra spaces and other characters.

It is guaranteed that if such type exists, then it is unique.

Note that you should print the type dictated by Gena (if such type exists) and not any type that can contain $ n $ values.

## 样例 #1

### 输入

```
3
pair pair int int int

```

### 输出

```
pair<pair<int,int>,int>
```

## 样例 #2

### 输入

```
1
pair int

```

### 输出

```
Error occurred
```



---

---
title: "Bewitching Stargazer"
layout: "post"
diff: 普及/提高-
pid: CF2053C
tag: ['递归', '分治']
---

# Bewitching Stargazer

## 题目描述

「我祈祷能拥有一颗透明的心，以及一双满含泪水的眼睛...」

—— 逃跑计划，《夜空中最亮的星》

Iris 仰望星空时，脑海中产生了一个有趣的问题。她希望你能帮忙解决这个问题，据说这样能引发一场流星雨。

夜空中有 $n$ 颗星星，排列成一行。Iris 拿着望远镜来观察这些星星。

最初，她观察整个区间 $[1, n]$，此时她的幸运值为 $0$。为了找到每个观察区间 $[l, r]$ 中的中间星星，Iris 开始了以下的递归过程：

- 首先，她计算中点位置 $m = \left\lfloor \frac{l+r}{2} \right\rfloor$。
- 如果区间长度（即 $r - l + 1$）是偶数，则她将该区间分成两个长度相等的子区间 $[l, m]$ 和 $[m+1, r]$，继续观察。
- 如果是奇数，则她会将望远镜对准第 $m$ 颗星星，幸运值增加 $m$；之后，如果 $l \neq r$，她会继续观察新产生的两个区间 $[l, m-1]$ 和 $[m+1, r]$。

Iris 有点懒，并以一个整数 $k$ 表示她的懒惰阈值：在观察过程中，任何长度严格小于 $k$ 的区间 $[l, r]$ 她都不会再继续观察。请你预测她最终的幸运值会是多少。

## 输入格式

输入包含多组测试用例。第一行是一个整数 $t$（$1 \leq t \leq 10^5$），代表测试用例的数量。接下来每组测试用例每行包括两个整数 $n$ 和 $k$（$1 \leq k \leq n \leq 2 \cdot 10^9$）。

## 输出格式

对每一个测试用例，输出一个整数，表示最终的幸运值。

## 说明/提示

在第一个测试用例中，初始观察区间是 $[1, 7]$。由于该区间长度为奇数，Iris 聚焦于第 $4$ 颗星星，幸运值增加 $4$。然后她将观察区间分成 $[1, 3]$ 和 $[5, 7]$。$[1, 3]$ 再次是奇数，于是她观察第 $2$ 颗星星，幸运值再增 $2$。此后其被分为 $[1, 1]$ 和 $[3, 3]$，因其长度都小于 $2$，所以不再观察。区间 $[5, 7]$ 的过程类似，最终幸运值增加 $6$。所以最终的幸运值为 $4 + 2 + 6 = 12$。

在最后一个测试用例中，Iris 最终观察到了所有星星，其最终幸运值为 $1 + 2 + \cdots + 8\,765\,432 = 38\,416\,403\,456\,028$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
6
7 2
11 3
55 13
5801 6
8919 64
8765432 1
```

### 输出

```
12
18
196
1975581
958900
38416403456028
```



---

---
title: "Skibidi Table"
layout: "post"
diff: 普及/提高-
pid: CF2093D
tag: ['递归']
---

# Skibidi Table

## 题目描述

Vadim 喜欢用整数填充正方形表格。但今天他想出了一个有趣的方法！以 $2 \times 2$ 的表格为例，行从上到下编号，列从左到右编号。我们在左上角单元格放置 $1$，右下角放置 $2$，左下角放置 $3$，右上角放置 $4$。这就是他需要的全部乐趣！

幸运的是，Vadim 有一个大小为 $2^n \times 2^n$ 的表格。他计划用 $1$ 到 $2^{2n}$ 的整数按升序填充它。为了填充这么大的表格，Vadim 会将其分成 $4$ 个相等的正方形子表格，先填充左上角的子表格，然后是右下角的子表格，接着是左下角的子表格，最后是右上角的子表格。每个较小的子表格会继续被分割成更小的子表格，直到分割成 $2 \times 2$ 的表格，并按照上述顺序填充。

现在 Vadim 迫不及待要开始填充表格了，但他有 $q$ 个两种类型的问题：

1. 位于第 $x$ 行第 $y$ 列的单元格中的数字是多少；
2. 数字 $d$ 位于哪个单元格坐标中。

请帮助回答 Vadim 的问题。

## 输入格式

每个测试包含多组输入数据。第一行包含一个整数 $t$（$1 \leq t \leq 10$）——输入数据的组数。接下来的行描述每组输入数据。

每组数据的第一行包含一个整数 $n$，描述表格的大小（$1 \le n \le 30$）。

每组数据的第二行包含一个整数 $q$——问题的数量（$1 \le q \le 20\,000$）。

接下来的 $q$ 行描述每个问题，格式如下：

- `-> x y` —— 询问位于第 $x$ 行第 $y$ 列的单元格中的数字（$1 \le x, y \le 2^n$）；
- `<- d` —— 询问数字 $d$（$1 \le d \le 2^{2n}$）所在的单元格坐标。

保证所有测试用例的 $q$ 之和不超过 $20\,000$。

## 输出格式

对每个问题，输出一行答案。

## 说明/提示

第一个样例的填充表格如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2093D/02d87014c7c132f45a9dd8ced0465346348b00e4.png)

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
2
5
-> 4 3
<- 15
<- 4
-> 3 1
-> 1 3
1
8
-> 1 1
-> 1 2
-> 2 1
-> 2 2
<- 1
<- 2
<- 3
<- 4
```

### 输出

```
7
2 3
1 2
9
13
1
4
3
2
1 1
2 2
2 1
1 2
```



---

---
title: "Mysterious Present"
layout: "post"
diff: 普及/提高-
pid: CF4D
tag: ['动态规划 DP', '搜索', '递归']
---

# Mysterious Present

## 题目描述

Peter decided to wish happy birthday to his friend from Australia and send him a card. To make his present more mysterious, he decided to make a chain. Chain here is such a sequence of envelopes $ A $ = { $ a_{1},a_{2},...,a_{n} $ }, where the width and the height of the $ i $ -th envelope is strictly higher than the width and the height of the $ (i-1) $ -th envelope respectively. Chain size is the number of envelopes in the chain.

Peter wants to make the chain of the maximum size from the envelopes he has, the chain should be such, that he'll be able to put a card into it. The card fits into the chain if its width and height is lower than the width and the height of the smallest envelope in the chain respectively. It's forbidden to turn the card and the envelopes.

Peter has very many envelopes and very little time, this hard task is entrusted to you.

## 输入格式

The first line contains integers $ n $ , $ w $ , $ h $ ( $ 1<=n<=5000 $ , $ 1<=w,h<=10^{6} $ ) — amount of envelopes Peter has, the card width and height respectively. Then there follow $ n $ lines, each of them contains two integer numbers $ w_{i} $ and $ h_{i} $ — width and height of the $ i $ -th envelope ( $ 1<=w_{i},h_{i}<=10^{6} $ ).

## 输出格式

In the first line print the maximum chain size. In the second line print the numbers of the envelopes (separated by space), forming the required chain, starting with the number of the smallest envelope. Remember, please, that the card should fit into the smallest envelope. If the chain of maximum size is not unique, print any of the answers.

If the card does not fit into any of the envelopes, print number $ 0 $ in the single line.

## 样例 #1

### 输入

```
2 1 1
2 2
2 2

```

### 输出

```
1
1 

```

## 样例 #2

### 输入

```
3 3 3
5 4
12 11
9 8

```

### 输出

```
3
1 3 2 

```



---

---
title: "New Reform"
layout: "post"
diff: 普及/提高-
pid: CF659E
tag: ['递归', '深度优先搜索 DFS']
---

# New Reform

## 题目描述

有 $n$ 个城市，$m$ 条双向道路，没有一个城市存在自己到自己的道路，两个不同的城市间，最多有一条道路，也不能保证能从一个城市到达任意一个其他城市。

现在需要对每一条道路定向，使之成为单向道路，当然需要尽可能少地产生孤立的城市。当其他所有城市都不能到达某个城市，则称这个城市为孤立城市。要求出最少的孤立城市的个数。

## 输入格式

第一行，两个整数，$n$ 和 $m$。

接下来 $m$ 行，每行两个整数 $x_i$ 和 $y_i$，表示一条道路连接城市 $x_i$ 和城市 $y_i$ 的双向道路。

## 输出格式

一行，一个整数，表示最少的孤立城市的个数。

### 数据规模与约定
$2\le n\le 100000$，$1\le m\le 100000$。

对于每一个合法的 $x_i$ 和 $y_i$，都有 $1\le x_i,y_i\le n$，且 $x_i \not\ =y_i$。

## 样例 #1

### 输入

```
4 3
2 1
1 3
4 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5 5
2 1
1 3
2 3
2 5
4 3

```

### 输出

```
0

```

## 样例 #3

### 输入

```
6 5
1 2
2 3
4 5
4 6
5 6

```

### 输出

```
1

```



---

---
title: "Andryusha and Colored Balloons"
layout: "post"
diff: 普及/提高-
pid: CF780C
tag: ['递归', '状态合并', '图论建模']
---

# Andryusha and Colored Balloons

## 题目描述

题意:

有一颗n个节点的树,进行有限制染色,问染色的最少颜色数,以及每个点的颜色(从1标号,标号不能超过颜色数).
限制:相邻三个点的颜色不能相同.

## 输入格式

第一行一个n,
接下来n-1行<x,y>,表示x与y之间有一条连边.

## 输出格式

第一行一个数,为最小颜色数.
接下来n个数,为[1,n]的点的颜色.

## 说明/提示

n:[3,2e5]

## 样例 #1

### 输入

```
3
2 3
1 3

```

### 输出

```
3
1 3 2 
```

## 样例 #2

### 输入

```
5
2 3
5 3
4 3
1 3

```

### 输出

```
5
1 3 2 5 4 
```

## 样例 #3

### 输入

```
5
2 1
3 2
4 3
5 4

```

### 输出

```
3
1 2 3 1 2 
```



---

---
title: "Maximal Binary Matrix"
layout: "post"
diff: 普及/提高-
pid: CF803A
tag: ['贪心', '递归']
---

# Maximal Binary Matrix

## 题目描述

You are given matrix with $ n $ rows and $ n $ columns filled with zeroes. You should put $ k $ ones in it in such a way that the resulting matrix is symmetrical with respect to the main diagonal (the diagonal that goes from the top left to the bottom right corner) and is lexicographically maximal.

One matrix is lexicographically greater than the other if the first different number in the first different row from the top in the first matrix is greater than the corresponding number in the second one.

If there exists no such matrix then output -1.

## 输入格式

The first line consists of two numbers $ n $ and $ k $ ( $ 1<=n<=100 $ , $ 0<=k<=10^{6} $ ).

## 输出格式

If the answer exists then output resulting matrix. Otherwise output -1.

## 样例 #1

### 输入

```
2 1

```

### 输出

```
1 0 
0 0 

```

## 样例 #2

### 输入

```
3 2

```

### 输出

```
1 0 0 
0 1 0 
0 0 0 

```

## 样例 #3

### 输入

```
2 5

```

### 输出

```
-1

```



---

---
title: "Party Lemonade"
layout: "post"
diff: 普及/提高-
pid: CF913C
tag: ['贪心', '递归', '进制']
---

# Party Lemonade

## 题目描述

题意

没有柠檬水的新年派对不是新年派对。像往常一样，你期待着客人，而柠檬水已经成为一种令人愉快的必需品。
你最喜欢的商店卖 n 种不同价格的装在不同瓶子里的柠檬水。一瓶第 i 种柠檬水，体积为2^{i-1}，价格为c_{i}卢布。商店里的每种柠檬水可以被认为有无限瓶。
你想要买至少 L 升的柠檬水，你需要花费多少卢布？

## 输入格式

第一行包含两个整数 n 和 L（1<=n<=30;1<=L<=10^{9}）。
第二行包含 n 个整数c_{1},c_{2},...,c_{n}（1<=c_{i}<=10^{9}）。

## 输出格式

输出一个正整数---买至少 L 升的柠檬水，你需要支付的最少卢布。



Translated by Fowany

## 样例 #1

### 输入

```
4 12
20 30 70 90

```

### 输出

```
150

```

## 样例 #2

### 输入

```
4 3
10000 1000 100 10

```

### 输出

```
10

```

## 样例 #3

### 输入

```
4 3
10 100 1000 10000

```

### 输出

```
30

```

## 样例 #4

### 输入

```
5 787787787
123456789 234567890 345678901 456789012 987654321

```

### 输出

```
44981600785557577

```



---

---
title: "Make a Square"
layout: "post"
diff: 普及/提高-
pid: CF962C
tag: ['递归', '枚举', '概率论']
---

# Make a Square

## 题目描述

You are given a positive integer $ n $ , written without leading zeroes (for example, the number 04 is incorrect).

In one operation you can delete any digit of the given integer so that the result remains a positive integer without leading zeros.

Determine the minimum number of operations that you need to consistently apply to the given integer $ n $ to make from it the square of some positive integer or report that it is impossible.

An integer $ x $ is the square of some positive integer if and only if $ x=y^2 $ for some positive integer $ y $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^{9} $ ). The number is given without leading zeroes.

## 输出格式

If it is impossible to make the square of some positive integer from $ n $ , print -1. In the other case, print the minimal number of operations required to do it.

## 说明/提示

In the first example we should delete from $ 8314 $ the digits $ 3 $ and $ 4 $ . After that $ 8314 $ become equals to $ 81 $ , which is the square of the integer $ 9 $ .

In the second example the given $ 625 $ is the square of the integer $ 25 $ , so you should not delete anything.

In the third example it is impossible to make the square from $ 333 $ , so the answer is -1.

## 样例 #1

### 输入

```
8314

```

### 输出

```
2

```

## 样例 #2

### 输入

```
625

```

### 输出

```
0

```

## 样例 #3

### 输入

```
333

```

### 输出

```
-1

```



---

