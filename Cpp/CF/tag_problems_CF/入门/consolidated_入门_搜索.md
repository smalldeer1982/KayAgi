---
title: "Second Order Statistics"
layout: "post"
diff: 入门
pid: CF22A
tag: ['搜索', '排序', '概率论']
---

# Second Order Statistics

## 题目描述

### 题面描述

给定一个数组，输出其中第二小的整数（相等的整数只计算一次）。

## 输入格式

第一行，一个整数 $n$（$1 \leq n \leq 100$），表示数组长度。

第二行，$n$ 个绝对值小于 $100$ 的整数。

## 输出格式

一行。如果该数组存在第二小整数，则输出第二小整数。如果不存在，则输出`NO`。

## 样例 #1

### 输入

```
4
1 2 2 -4

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5
1 2 3 1 1

```

### 输出

```
2

```



---

---
title: "Triangular numbers"
layout: "post"
diff: 入门
pid: CF47A
tag: ['搜索', '数学', '枚举']
---

# Triangular numbers

## 题目描述

A triangular number is the number of dots in an equilateral triangle uniformly filled with dots. For example, three dots can be arranged in a triangle; thus three is a triangular number. The $ n $ -th triangular number is the number of dots in a triangle with $ n $ dots on a side. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF47A/7344b4fd5acb7c973775cffc0c5a51a81c6ee4d9.png). You can learn more about these numbers from Wikipedia (http://en.wikipedia.org/wiki/Triangular\_number).

Your task is to find out if a given integer is a triangular number.

## 输入格式

The first line contains the single number $ n $ ( $ 1<=n<=500 $ ) — the given integer.

## 输出格式

If the given integer is a triangular number output YES, otherwise output NO.

## 样例 #1

### 输入

```
1

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
2

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
3

```

### 输出

```
YES

```



---

---
title: "Far Relative’s Birthday Cake"
layout: "post"
diff: 入门
pid: CF629A
tag: ['枚举', '深度优先搜索 DFS']
---

# Far Relative’s Birthday Cake

## 题目描述

多尔的家人正在庆祝多尔的生日派对。他们爱多尔，所以他们计划让他的生日蛋糕变得不可思议的！

蛋糕是一个由n×n的等边正方形组成的形状，长度为1。每个方块要么是空的，要么是由一个巧克力组成的。他们买了蛋糕，便开始把巧克力放在蛋糕上。“家庭之门”的幸福值等于蛋糕中同一行或同一列中装有巧克力的一对细胞的数量。多尔的家人想知道他们的幸福程度是多少？

## 输入格式

第一行输入一个整数n（1<=n<=100)，表示蛋糕边的长度。然后输入n行数，每行有n个字符。空的细胞用'.'表示，而含有巧克力的细胞用“C”表示。

## 输出格式

输出“家庭之门”幸福感的价值，即同一行或同一列的一对巧克力片的数量。

## 样例 #1

### 输入

```
3
.CC
C..
C.C

```

### 输出

```
4

```

## 样例 #2

### 输入

```
4
CC..
C..C
.CC.
.CC.

```

### 输出

```
9

```



---

---
title: "Triangle"
layout: "post"
diff: 入门
pid: CF6A
tag: ['枚举', '排序', '深度优先搜索 DFS', '排列组合']
---

# Triangle

## 题目描述

给定 $4$ 根木棍的长度，如果它们中存在 $3$ 根木棍可以组成三角形，输出 ```TRIANGLE``` ;如果它们无法组成三角形，但是它们中存在 $3$ 根木棍可以组成退化的三角形(任意两边之和大于等于第三边，但是不是三角形)，输出 ```SEGMENT``` ;否则，输出 ```IMPOSSIBLE``` 。

注意: 木棍不能折断，也不能只用一部分长度。

## 输入格式

一行 $4$ 个整数，$4$ 根木棍的长度。

## 输出格式

如果它们中存在 $3$ 根木棍可以组成三角形，输出 ```TRIANGLE``` ;如果它们无法组成三角形，但是它们中存在3根木棍可以组成退化的三角形，输出 ```SEGMENT``` ;否则，输出 ```IMPOSSIBLE```。

By @PC_DOS

## 样例 #1

### 输入

```
4 2 1 3

```

### 输出

```
TRIANGLE

```

## 样例 #2

### 输入

```
7 2 2 4

```

### 输出

```
SEGMENT

```

## 样例 #3

### 输入

```
3 5 9 1

```

### 输出

```
IMPOSSIBLE

```



---

---
title: "Buy a Shovel"
layout: "post"
diff: 入门
pid: CF732A
tag: ['模拟', '搜索', '数学']
---

# Buy a Shovel

## 题目描述

Polycarp urgently needs a shovel! He comes to the shop and chooses an appropriate one. The shovel that Policarp chooses is sold for $ k $ burles. Assume that there is an unlimited number of such shovels in the shop.

In his pocket Polycarp has an unlimited number of "10-burle coins" and exactly one coin of $ r $ burles ( $ 1<=r<=9 $ ).

What is the minimum number of shovels Polycarp has to buy so that he can pay for the purchase without any change? It is obvious that he can pay for 10 shovels without any change (by paying the requied amount of 10-burle coins and not using the coin of $ r $ burles). But perhaps he can buy fewer shovels and pay without any change. Note that Polycarp should buy at least one shovel.

## 输入格式

The single line of input contains two integers $ k $ and $ r $ ( $ 1<=k<=1000 $ , $ 1<=r<=9 $ ) — the price of one shovel and the denomination of the coin in Polycarp's pocket that is different from "10-burle coins".

Remember that he has an unlimited number of coins in the denomination of 10, that is, Polycarp has enough money to buy any number of shovels.

## 输出格式

Print the required minimum number of shovels Polycarp has to buy so that he can pay for them without any change.

## 说明/提示

In the first example Polycarp can buy 9 shovels and pay $ 9·117=1053 $ burles. Indeed, he can pay this sum by using 10-burle coins and one 3-burle coin. He can't buy fewer shovels without any change.

In the second example it is enough for Polycarp to buy one shovel.

In the third example Polycarp should buy two shovels and pay $ 2·15=30 $ burles. It is obvious that he can pay this sum without any change.

## 样例 #1

### 输入

```
117 3

```

### 输出

```
9

```

## 样例 #2

### 输入

```
237 7

```

### 输出

```
1

```

## 样例 #3

### 输入

```
15 2

```

### 输出

```
2

```



---

---
title: "Polycarp and Letters"
layout: "post"
diff: 入门
pid: CF864B
tag: ['模拟', '字符串', '搜索']
---

# Polycarp and Letters

## 题目描述

Polycarp loves lowercase letters and dislikes uppercase ones. Once he got a string $ s $ consisting only of lowercase and uppercase Latin letters.

Let $ A $ be a set of positions in the string. Let's call it pretty if following conditions are met:

- letters on positions from $ A $ in the string are all distinct and lowercase;
- there are no uppercase letters in the string which are situated between positions from $ A $ (i.e. there is no such $ j $ that $ s[j] $ is an uppercase letter, and $ a_{1}<j<a_{2} $ for some $ a_{1} $ and $ a_{2} $ from $ A $ ).

Write a program that will determine the maximum number of elements in a pretty set of positions.

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=200 $ ) — length of string $ s $ .

The second line contains a string $ s $ consisting of lowercase and uppercase Latin letters.

## 输出格式

Print maximum number of elements in pretty set of positions for string $ s $ .

## 说明/提示

In the first example the desired positions might be $ 6 $ and $ 8 $ or $ 7 $ and $ 8 $ . Positions $ 6 $ and $ 7 $ contain letters 'a', position $ 8 $ contains letter 'b'. The pair of positions $ 1 $ and $ 8 $ is not suitable because there is an uppercase letter 'B' between these position.

In the second example desired positions can be $ 7 $ , $ 8 $ and $ 11 $ . There are other ways to choose pretty set consisting of three elements.

In the third example the given string $ s $ does not contain any lowercase letters, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
11
aaaaBaabAbA

```

### 输出

```
2

```

## 样例 #2

### 输入

```
12
zACaAbbaazzC

```

### 输出

```
3

```

## 样例 #3

### 输入

```
3
ABC

```

### 输出

```
0

```



---

---
title: "The Artful Expedient"
layout: "post"
diff: 入门
pid: CF869A
tag: ['模拟', '搜索', '枚举']
---

# The Artful Expedient

## 题目描述

首先定义一个整形变量n,Koyomi和Karen都会分别选择n个不同的正整数,分别表示为X1,X2,...Xn和Y1,Y2,...Yn。它们不断重复显示它们的序列,并一直重复直到所有2n个整数变得不同,此时,这是唯一被保留和考虑的最终状态。
他们需要计算满足有序数对(i,j)[1<=i,j<=n]中(Xi ^ Yi)的值等于2n个整数之中任意一个整数的值的有序数对的数量。这里'^'意味着对两个整数的按位异或操作,并且在大多数编程语言中用'^','/'或'xor'表示

如果这样的配对数量是偶数时,Karen就可以取得胜利,否则Koyomi胜利。你需要帮助他们决出最近一场比赛的获胜者。

## 输入格式

输入的第一行包含一个正整数n(1<=N<=2000)表示两个序列的长度。

第二行包含n个用空格分开的正整数X1,X2,...Xn(1<=Xi<=2*1e6)表示最后由Koyomi选择的正整数

第三行包含n个用空格分开的正整数Y1,Y2,...Yn(1<=Yi<=2*1e6)表示最后由Karen选择的正整数

输入数据保证给定的2n个正整数是两两不同的,也就是说,没有一对(i,j)[1<=i,j<=n]满足以下任意一项条件:
1.Xi=Yi
2.i≠j & Xi=Xj
3.i≠j & Yi=Yj

## 输出格式

输出一行表示获胜者的名字,即“Koyomi”或“Karen”(不含引号),注意大小写

样例解释
在样例1中,有6对满足条件的有序数对：(1,1),(1,2),(2,1),(2,3),(3,2),(3,3),因为6是偶数,所以Karen取得胜利
在样例2中,有16对满足条件的有序数对,所以Karen再次取得了比赛的胜利

Translated by @matthew

## 样例 #1

### 输入

```
3
1 2 3
4 5 6

```

### 输出

```
Karen

```

## 样例 #2

### 输入

```
5
2 4 6 8 10
9 7 5 3 1

```

### 输出

```
Karen

```



---

---
title: "Generate Login"
layout: "post"
diff: 入门
pid: CF909A
tag: ['字符串', '搜索', '贪心', '枚举']
---

# Generate Login

## 题目描述

The preferred way to generate user login in Polygon is to concatenate a prefix of the user's first name and a prefix of their last name, in that order. Each prefix must be non-empty, and any of the prefixes can be the full name. Typically there are multiple possible logins for each person.

You are given the first and the last name of a user. Return the alphabetically earliest login they can get (regardless of other potential Polygon users).

As a reminder, a prefix of a string $ s $ is its substring which occurs at the beginning of $ s $ : "a", "ab", "abc" etc. are prefixes of string "{abcdef}" but "b" and 'bc" are not. A string $ a $ is alphabetically earlier than a string $ b $ , if $ a $ is a prefix of $ b $ , or $ a $ and $ b $ coincide up to some position, and then $ a $ has a letter that is alphabetically earlier than the corresponding letter in $ b $ : "a" and "ab" are alphabetically earlier than "ac" but "b" and "ba" are alphabetically later than "ac".

## 输入格式

The input consists of a single line containing two space-separated strings: the first and the last names. Each character of each string is a lowercase English letter. The length of each string is between 1 and 10, inclusive.

## 输出格式

Output a single string — alphabetically earliest possible login formed from these names. The output should be given in lowercase as well.

## 样例 #1

### 输入

```
harry potter

```

### 输出

```
hap

```

## 样例 #2

### 输入

```
tom riddle

```

### 输出

```
tomr

```



---

