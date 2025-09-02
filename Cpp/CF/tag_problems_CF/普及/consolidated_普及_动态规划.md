---
title: "Ayoub and Lost Array"
layout: "post"
diff: 普及/提高-
pid: CF1105C
tag: ['动态规划 DP']
---

# Ayoub and Lost Array

## 题目描述

已知有一个长度为$n$($1\leq n\leq 2 \times 10^5$)的数列，每一个数的大小在$[l,r]$($1\leq l \leq r \leq 10^9$)之间。求出有多少种方案使得这个数列的和为$3$的倍数。答案对$10^9+7$取模。当然，如果无法组成任何一个合法的数列，答案即为$0$。

## 输入格式

一行三个正整数$n$,$l$,$r$

## 输出格式

一行，表示方案数模$10^9+7$的结果。

## 样例 #1

### 输入

```
2 1 3

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3 2 2

```

### 输出

```
1

```

## 样例 #3

### 输入

```
9 9 99

```

### 输出

```
711426616

```



---

---
title: "Required Length"
layout: "post"
diff: 普及/提高-
pid: CF1681D
tag: ['动态规划 DP', '枚举', '广度优先搜索 BFS']
---

# Required Length

## 题目描述

You are given two integer numbers, $ n $ and $ x $ . You may perform several operations with the integer $ x $ .

Each operation you perform is the following one: choose any digit $ y $ that occurs in the decimal representation of $ x $ at least once, and replace $ x $ by $ x \cdot y $ .

You want to make the length of decimal representation of $ x $ (without leading zeroes) equal to $ n $ . What is the minimum number of operations required to do that?

## 输入格式

The only line of the input contains two integers $ n $ and $ x $ ( $ 2 \le n \le 19 $ ; $ 1 \le x < 10^{n-1} $ ).

## 输出格式

Print one integer — the minimum number of operations required to make the length of decimal representation of $ x $ (without leading zeroes) equal to $ n $ , or $ -1 $ if it is impossible.

## 说明/提示

In the second example, the following sequence of operations achieves the goal:

1. multiply $ x $ by $ 2 $ , so $ x = 2 \cdot 2 = 4 $ ;
2. multiply $ x $ by $ 4 $ , so $ x = 4 \cdot 4 = 16 $ ;
3. multiply $ x $ by $ 6 $ , so $ x = 16 \cdot 6 = 96 $ ;
4. multiply $ x $ by $ 9 $ , so $ x = 96 \cdot 9 = 864 $ .

## 样例 #1

### 输入

```
2 1
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
3 2
```

### 输出

```
4
```

## 样例 #3

### 输入

```
13 42
```

### 输出

```
12
```



---

---
title: "Qpwoeirut And The City"
layout: "post"
diff: 普及/提高-
pid: CF1706C
tag: ['动态规划 DP', '贪心']
---

# Qpwoeirut And The City

## 题目描述

Qpwoeirut has taken up architecture and ambitiously decided to remodel his city.

Qpwoeirut's city can be described as a row of $ n $ buildings, the $ i $ -th ( $ 1 \le i \le n $ ) of which is $ h_i $ floors high. You can assume that the height of every floor in this problem is equal. Therefore, building $ i $ is taller than the building $ j $ if and only if the number of floors $ h_i $ in building $ i $ is larger than the number of floors $ h_j $ in building $ j $ .

Building $ i $ is cool if it is taller than both building $ i-1 $ and building $ i+1 $ (and both of them exist). Note that neither the $ 1 $ -st nor the $ n $ -th building can be cool.

To remodel the city, Qpwoeirut needs to maximize the number of cool buildings. To do this, Qpwoeirut can build additional floors on top of any of the buildings to make them taller. Note that he cannot remove already existing floors.

Since building new floors is expensive, Qpwoeirut wants to minimize the number of floors he builds. Find the minimum number of floors Qpwoeirut needs to build in order to maximize the number of cool buildings.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains the single integer $ n $ ( $ 3 \le n \le 10^5 $ ) — the number of buildings in Qpwoeirut's city.

The second line of each test case contains $ n $ integers $ h_1, h_2, \ldots, h_n $ ( $ 1 \le h_i \le 10^9 $ ) — the number of floors in each of the buildings of the city.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print a single integer — the minimum number of additional floors Qpwoeirut needs to build in order to maximize the number of cool buildings.

## 说明/提示

In the first test case, it is optimal for Qpwoeirut to make the second building cool by building $ 2 $ additional floors on top of it, making it taller than both of its adjacent buildings. The final heights of buildings will be $ [2, \underline{3}, 2] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/5b747d1e682e5f282bdd90fc1247bc9f2859b4d3.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/ca7bffe47191f356c4fd58ef8f125ae9f7e465e2.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/c25e1e8b92772ee4d6c001b5263ad32fc0bed1d3.png)In the second test case, the number of cool buildings is already maximized, so Qpwoeirut does not need to do anything.

In the third test case, it is optimal for Qpwoeirut to make the third and fifth buildings cool by building $ 2 $ additional floors onto the third building and $ 1 $ additional floor onto the fifth building. The final heights of buildings will be $ [3, 1, \underline{6}, 5, \underline{6}, 2] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/d8dd96553e5aa6fe2bbad7a9bf1dc528da32254c.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/ca7bffe47191f356c4fd58ef8f125ae9f7e465e2.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/6d7185baf1e5e2a187bb01c943d100104f7de6bc.png)It can be shown that it is impossible to make more than $ 2 $ of the buildings cool, or to make $ 2 $ buildings cool using fewer than $ 3 $ additional floors.

In the fourth test case, Qpwoeirut can either make the second building cool, or he can make the third building cool. Either way, he will be building $ 3 $ additional floors and maximizing the number of cool buildings. The final heights of buildings will be $ [4, 2, \underline{4}, 3, 5, 3, 6, 1] $ or $ [4, \underline{5}, 1, 3, 5, 3, 6, 1] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/27f107a434b26468932a928c7c16fd0abda918f0.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/ca7bffe47191f356c4fd58ef8f125ae9f7e465e2.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/4e2e7951e438027228057e8a21e8bea81f160a32.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706C/8e41aee337358c3f261ed9626c0e19808d3f7d2c.png)

## 样例 #1

### 输入

```
6
3
2 1 2
5
1 2 1 4 3
6
3 1 4 5 5 2
8
4 2 1 3 5 3 6 1
6
1 10 1 1 10 1
8
1 10 11 1 10 11 10 1
```

### 输出

```
2
0
3
3
0
4
```



---

---
title: "Подкрутка II"
layout: "post"
diff: 普及/提高-
pid: CF1769C2
tag: ['动态规划 DP', '贪心']
---

# Подкрутка II

## 题目描述

В этой версии задачи $ n \le 2 \cdot 10^5 $ и $ a_i \le 10^6 $ (а также есть ограничение на сумму $ n $ по наборам входных данных внутри одного теста).

Вика за время работы в компании VK уже сделала $ n $ коммитов в системе контроля версий. $ i $ -й коммит был сделан в $ a_i $ -й день работы Вики в компании. В некоторые дни Вика могла сделать несколько коммитов, а в другие — не сделать ни одного.

Вику интересуют такие отрезки подряд идущих дней, что в каждый из этих дней у неё есть хотя бы один коммит. Чем длиннее будет самый длинный такой отрезок, тем более продуктивным сотрудником она будет себя ощущать.

Недавно Вика нашла способ подкрутить время любого коммита вперёд, но не более чем на сутки. Таким образом, $ i $ -й коммит теперь может быть «сделан» либо в $ a_i $ -й, либо в $ (a_i + 1) $ -й день. Время каждого коммита можно подкрутить независимо от других — в частности, можно как оставить всем коммитам исходное время, так и перенести все коммиты ровно на день вперёд.

Найдите длину самого длинного возможного отрезка подряд идущих дней, в каждый из которых у Вики в профиле будет отображаться хотя бы один коммит, после возможной подкрутки времени некоторых коммитов.

## 输入格式

Каждый тест состоит из нескольких наборов входных данных. В первой строке находится одно целое число $ t $ ( $ 1 \le t \le 100 $ ) — количество наборов входных данных. Далее следует описание наборов входных данных.

Первая строка каждого набора входных данных содержит одно целое число $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — число коммитов.

Вторая строка содержит $ n $ целых чисел $ a_1, a_2, \ldots, a_n $ в неубывающем порядке ( $ 1 \le a_1 \le a_2 \le \ldots \le a_n \le 10^6 $ ) — номера дней, в которые были сделаны коммиты.

Гарантируется, что сумма $ n $ по всем наборам входных данных не превосходит $ 2 \cdot 10^5 $ .

## 输出格式

Для каждого набора входных данных выведите одно целое число — максимальную возможную длину отрезка дней, в каждый из которых у Вики в профиле будет отображаться хотя бы один коммит, после возможной подкрутки времени некоторых коммитов вперёд не более чем на сутки.

## 样例 #1

### 输入

```
3
9
1 1 3 4 6 6 6 8 10
6
1 2 3 4 5 6
5
10 10 10 10 10
```

### 输出

```
5
6
2
```



---

---
title: "Binary Path"
layout: "post"
diff: 普及/提高-
pid: CF1937B
tag: ['动态规划 DP', '贪心']
---

# Binary Path

## 题目描述

You are given a $ 2 \times n $ grid filled with zeros and ones. Let the number at the intersection of the $ i $ -th row and the $ j $ -th column be $ a_{ij} $ .

There is a grasshopper at the top-left cell $ (1, 1) $ that can only jump one cell right or downwards. It wants to reach the bottom-right cell $ (2, n) $ . Consider the binary string of length $ n+1 $ consisting of numbers written in cells of the path without changing their order.

Your goal is to:

1. Find the lexicographically smallest $ ^\dagger $ string you can attain by choosing any available path;
2. Find the number of paths that yield this lexicographically smallest string.

 $ ^\dagger $ If two strings $ s $ and $ t $ have the same length, then $ s $ is lexicographically smaller than $ t $ if and only if in the first position where $ s $ and $ t $ differ, the string $ s $ has a smaller element than the corresponding element in $ t $ .

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ).

The second line of each test case contains a binary string $ a_{11} a_{12} \ldots a_{1n} $ ( $ a_{1i} $ is either $ 0 $ or $ 1 $ ).

The third line of each test case contains a binary string $ a_{21} a_{22} \ldots a_{2n} $ ( $ a_{2i} $ is either $ 0 $ or $ 1 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output two lines:

1. The lexicographically smallest string you can attain by choosing any available path;
2. The number of paths that yield this string.

## 说明/提示

In the first test case, the lexicographically smallest string is $ \mathtt{000} $ . There are two paths that yield this string:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1937B/28bc26c21acb39dafc863512440b57a82f70d617.png)In the second test case, the lexicographically smallest string is $ \mathtt{11000} $ . There is only one path that yields this string:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1937B/f024d427300a33d2f71c9946e45249754a59348c.png)

## 样例 #1

### 输入

```
3
2
00
00
4
1101
1100
8
00100111
11101101
```

### 输出

```
000
2
11000
1
001001101
4
```



---

---
title: "Rudolf and the Ball Game"
layout: "post"
diff: 普及/提高-
pid: CF1941D
tag: ['动态规划 DP']
---

# Rudolf and the Ball Game

## 题目描述

$n$ 个人站成一个圈，按照顺时针编号依次是 $1$ 到 $n$。

现在这 $n$ 个人玩一个传球游戏，第 $i$ 次传球可以向顺时针方向传给与自己距离为 $d_i$ 的距离，或者向逆时针方向传给与自己距离为 $r_i$ 的距离。

游戏总共进行了 $m$ 轮传球，给你初始拿到球的人的编号 $x$ 和每次传球的方向和距离 $r_i$（有可能方向未知），求出最后可能是谁拿到了球，**按编号从小到大**输出。

------------

## 输入格式

**本题有多组数据**。

第一行一个整数 $t$，表示测试用例的数量。

对于每一组测试用例：

第一行三个整数 $n,m,x$。

接下来 $m$ 行包含每次的传球信息：传球的距离 $r_i$，以及传球的方向 $c_i$：

- $c_i=$ '0'，则这次传球为顺时针；

- $c_i=$ '1'，则这次传球为逆时针；

- $c_i=$ '?'，则这次传球方向未知，可以是顺时针也可以是逆时针。

------------

## 输出格式

对于每一组数据，共两行：

第一行一个整数 $k$，表示最后可能拿到球的人的数量。

第二行 $k$ 个整数，表示最后可能拿到球的人的编号

------------

## 说明/提示

#### 样例解释
下面是第一个测试用例的三次传球的示意图。箭头表示可能的传球方向。在传球后可能持有球的玩家被标记为灰色。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1941D/de43c3cc1c4b12f903e5224359bac3a10205e9a9.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1941D/1a47b05e6478f36a49179722556df26c9f84bbc8.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1941D/47036b3bd9ad777cfd4d3801abb62bd85bcbcc75.png)

------------

对于 $100\%$ 的数据，$1 \le t \le 1000,1 \le x  \le n \le 1000,1 \le m \le 1000,1 \le n\cdot m \le 2\cdot10^5,1 \le r_i \le n-1$。

## 样例 #1

### 输入

```
5
6 3 2
2 ?
2 ?
2 ?
12 1 2
3 1
10 7 4
2 ?
9 1
4 ?
7 0
2 0
8 1
5 ?
5 3 1
4 0
4 ?
1 ?
4 1 1
2 ?
```

### 输出

```
3
2 4 6 
1
11 
4
3 5 7 9 
3
2 3 5 
1
3
```



---

---
title: "Seraphim the Owl"
layout: "post"
diff: 普及/提高-
pid: CF1945D
tag: ['动态规划 DP']
---

# Seraphim the Owl

## 题目描述

The guys lined up in a queue of $ n $ people, starting with person number $ i = 1 $ , to ask Serafim the Owl about the meaning of life. Unfortunately, Kirill was very busy writing the legend for this problem, so he arrived a little later and stood at the end of the line after the $ n $ -th person. Kirill is completely dissatisfied with this situation, so he decided to bribe some people ahead of him.

For the $ i $ -th person in the queue, Kirill knows two values: $ a_i $ and $ b_i $ . If at the moment Kirill is standing at position $ i $ , then he can choose any position $ j $ such that $ j < i $ and exchange places with the person at position $ j $ . In this case, Kirill will have to pay him $ a_j $ coins. And for each $ k $ such that $ j < k < i $ , Kirill will have to pay $ b_k $ coins to the person at position $ k $ . Kirill can perform this action any number of times.

Kirill is thrifty, so he wants to spend as few coins as possible, but he doesn't want to wait too long, so Kirill believes he should be among the first $ m $ people in line.

Help Kirill determine the minimum number of coins he will have to spend in order to not wait too long.

## 输入格式

Each test consists of several sets of input data. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Then follows the description of the test case.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \le m \le n \le 200\,000 $ ) — the number of people in the queue besides Kirill and the maximum allowable final position of Kirill, respectively.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ separated by spaces ( $ 1 \le a_i \le 10^9 $ ).

The third line contains $ n $ integers $ b_1, b_2, \dots, b_n $ separated by spaces ( $ 1 \le b_i \le 10^9 $ ).

It is guaranteed that the sum of the values of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the minimum number of coins Kirill needs to spend.

## 样例 #1

### 输入

```
4
4 2
7 3 6 9
4 3 8 5
6 2
6 9 7 1 8 3
5 8 8 1 4 1
7 7
7 2 9 2 6 5 9
9 1 10 7 1 4 9
2 1
2 3
1 1
```

### 输出

```
14
22
9
3
```



---

---
title: "Maximum Sum"
layout: "post"
diff: 普及/提高-
pid: CF1946B
tag: ['动态规划 DP', '贪心']
---

# Maximum Sum

## 题目描述

You have an array $ a $ of $ n $ integers.

You perform exactly $ k $ operations on it. In one operation, you select any contiguous subarray of the array $ a $ (possibly empty) and insert the sum of this subarray anywhere in the array.

Your task is to find the maximum possible sum of the array after $ k $ such operations.

As this number can be very large, output the answer modulo $ 10^9 + 7 $ .

Reminder: the remainder of a number $ x $ modulo $ p $ is the smallest non-negative $ y $ such that there exists an integer $ q $ and $ x = p \cdot q + y $ .

## 输入格式

Each test consists of several test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Then follows the description of the test cases.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le n, k \le 2 \cdot 10^5 $ ) — the length of the array $ a $ and the number of operations, respectively.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ -10^9 \le a_i \le 10^9 $ ) — the array $ a $ itself.

It is guaranteed that the sum of the values of $ n $ and $ k $ for all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test, output a single integer — the maximum sum of the array that can be obtained after $ k $ operations modulo $ 10^9 + 7 $ .

## 说明/提示

In the first test case, it is advantageous to take an empty subarray of the array twice and insert the sum of the empty subarray (zero) anywhere, then the sum of the resulting array will be $ (-4) + (-7) + 0 + 0 = -11 $ , modulo $ 10^9 + 7 $ this is $ 999\,999\,996 $ .

In the second test case, it is advantageous to take the sum of the entire array three times and place it anywhere in the array, then one of the possible sequences of actions: \[ $ 2, 2, 8 $ \] $ \rightarrow $ \[ $ 2, 2, 8, 12 $ \] $ \rightarrow $ \[ $ 2, 2, 8, 12, 24 $ \] $ \rightarrow $ \[ $ 2, 2, 8, 12, 24, 48 $ \], the sum of the final array is $ 2 + 2 + 8 + 12 + 24 + 48 = 96 $ .

In the fourth test case, it is advantageous to take a subarray of the array consisting of the first three numbers (i.e. consisting of the numbers $ 4, -2 $ and $ 8 $ ) and insert its sum at the beginning of the array, thereby obtaining the array \[ $ 10, 4, -2, 8, -12, 9 $ \], the sum of this array is $ 17 $ .

In the seventh test case, it will always be advantageous for us to take an empty subarray of the array. In this case, the sum of the resulting array will not differ from the sum of the original. The answer will be the sum of the original array, taken modulo — $ 42 $ , because $ (-6 \cdot (10^9 + 7) + 42 = -6\,000\,000\,000) $ .

## 样例 #1

### 输入

```
12
2 2
-4 -7
3 3
2 2 8
1 7
7
5 1
4 -2 8 -12 9
7 4
8 14 -9 6 0 -1 3
7 100
5 3 -8 12 -5 -9 3
6 1000
-1000000000 -1000000000 -1000000000 -1000000000 -1000000000 -1000000000
2 1
1000000000 8
5 4
0 0 0 0 0
6 10
48973 757292 58277 -38574 27475 999984
7 1
-1000 1000 -1000 1000 -1000 1000 -1000
10 10050
408293874 -3498597 7374783 295774930 -48574034 26623784 498754833 -294875830 283045804 85938045
```

### 输出

```
999999996
96
896
17
351
716455332
42
2
0
897909241
0
416571966
```



---

---
title: "Trails (Easy)"
layout: "post"
diff: 普及/提高-
pid: CF1970E1
tag: ['动态规划 DP']
---

# Trails (Easy)

## 题目描述

Harry Potter is hiking in the Alps surrounding Lake Geneva. In this area there are $ m $ cabins, numbered 1 to $ m $ . Each cabin is connected, with one or more trails, to a central meeting point next to the lake. Each trail is either short or long. Cabin $ i $ is connected with $ s_i $ short trails and $ l_i $ long trails to the lake.

Each day, Harry walks a trail from the cabin where he currently is to Lake Geneva, and then from there he walks a trail to any of the $ m $ cabins (including the one he started in). However, as he has to finish the hike in a day, at least one of the two trails has to be short.

How many possible combinations of trails can Harry take if he starts in cabin 1 and walks for $ n $ days?

Give the answer modulo $ 10^9 + 7 $ .

## 输入格式

The first line contains the integers $ m $ and $ n $ .

The second line contains $ m $ integers, $ s_1, \dots, s_m $ , where $ s_i $ is the number of short trails between cabin $ i $ and Lake Geneva.

The third and last line contains $ m $ integers, $ l_1, \dots, l_m $ , where $ l_i $ is the number of long trails between cabin $ i $ and Lake Geneva.

We have the following constraints:

 $ 0 \le s_i, l_i \le 10^3 $ .

 $ 1 \le m \le 10^2 $ .

 $ 1 \le n \le 10^3 $ .

## 输出格式

The number of possible combinations of trails, modulo $ 10^9 + 7 $ .

## 样例 #1

### 输入

```
3 2
1 0 1
0 1 1
```

### 输出

```
18
```



---

---
title: "Money Buys Happiness"
layout: "post"
diff: 普及/提高-
pid: CF1974E
tag: ['动态规划 DP']
---

# Money Buys Happiness

## 题目描述

Being a physicist, Charlie likes to plan his life in simple and precise terms.

For the next $ m $ months, starting with no money, Charlie will work hard and earn $ x $ pounds per month. For the $ i $ -th month $ (1 \le i \le m) $ , there'll be a single opportunity of paying cost $ c_i $ pounds to obtain happiness $ h_i $ .

Borrowing is not allowed. Money earned in the $ i $ -th month can only be spent in a later $ j $ -th month ( $ j>i $ ).

Since physicists don't code, help Charlie find the maximum obtainable sum of happiness.

## 输入格式

The first line of input contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

The first line of each test case contains two integers, $ m $ and $ x $ ( $ 1 \le m \le 50 $ , $ 1 \le x \le 10^8 $ ) — the total number of months and the monthly salary.

The $ i $ -th of the following $ m $ lines contains two integers, $ c_i $ and $ h_i $ ( $ 0 \le c_i \le 10^8 $ , $ 1 \le h_i \le 10^3 $ ) — the cost and happiness on offer for the $ i $ -th month. Note that some happiness may be free ( $ c_i=0 $ for some $ i $ 's).

It is guaranteed that the sum of $ \sum_i h_i $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, print a single integer, the maximum sum of happiness Charlie could obtain.

## 说明/提示

In the first test case, Charlie only gets paid at the end of the month, so is unable to afford anything.

In the second test case, Charlie obtains the free happiness in the first month.

In the third test case, it's optimal for Charlie to buy happiness in the second month. Even with money left at the end, Charlie could not go back in time to obtain the happiness on offer in the first month.

## 样例 #1

### 输入

```
7
1 10
1 5
2 80
0 10
200 100
3 100
70 100
100 200
150 150
5 8
3 1
5 3
3 4
1 5
5 3
2 5
1 5
2 1
5 3
2 5
2 4
4 1
5 1
3 4
5 2
2 1
1 2
3 5
3 2
3 2
```

### 输出

```
0
10
200
15
1
9
9
```



---

---
title: "Mathematical Problem"
layout: "post"
diff: 普及/提高-
pid: CF1986D
tag: ['动态规划 DP', '贪心']
---

# Mathematical Problem

## 题目描述

你有一个长度 $n > 1$ 的字符串 $s$，由数字 $0$ 到 $9$ 组成，你要将 $n - 2$ 个运算符（$+$ 或 $\times$）插入至 $s$ 中，形成一个合法的表达式。

很明显，任何一个运算符都不应插入在 $s_0$ 前或 $s_{n - 1}$ 后，因为这样构不成一个合法的表达式。还有一点：字符串中数字的位置不能变。

假设 $s = \tt 987009$，可以获得以下几种表达式：

- $ 9 \times 8 + 70 \times 0 + 9 = 81 $ 
- $ 98 \times 7 \times 0 + 0 \times 9 = 0 $
- $ 9 + 8 + 7 + 0 + 09 = 33 $  
表达式里的数被允许含有前导零，例子中的 $09$ 可以被转换为 $9$。

从该字符串中，无法获得以下几种表达式：
- $+ 9 \times 8 \times 70 + 09$（符号只能放在数字之间）
- $98 \times 70 + 0 + 9$（因为有 $6$ 个数字，所以必须正好有 $4$ 个符号）

## 输入格式

每个测试由多个测试数据组成。第一行包含一个整数 $t$（$1 \leq t \leq 10^4$），表示测试数据的数量。

每个测试用例的第一行包含一个整数 $n(2 \leq n \leq 20)$，表示字符串 $s$ 的长度。

每个测试用例的第二行包含一个字符串 $s$，长度为 $n$，由 $0$ 到 $9$ 的数字组成。

## 输出格式

对于每个测试数据，输出每个合法表达式的最小结果。

## 样例 #1

### 输入

```
18
2
10
2
74
2
00
2
01
3
901
3
101
5
23311
6
987009
7
1111111
20
99999999999999999999
20
00000000000000000000
4
0212
18
057235283621345395
4
1112
20
19811678487321784121
4
1121
4
2221
3
011
```

### 输出

```
10
74
0
1
9
1
19
0
11
261
0
0
0
12
93
12
24
0
```



---

---
title: "Test of Love"
layout: "post"
diff: 普及/提高-
pid: CF1992D
tag: ['动态规划 DP']
---

# Test of Love

## 题目描述

ErnKor is ready to do anything for Julen, even to swim through crocodile-infested swamps. We decided to test this love. ErnKor will have to swim across a river with a width of $ 1 $ meter and a length of $ n $ meters.

The river is very cold. Therefore, in total (that is, throughout the entire swim from $ 0 $ to $ n+1 $ ) ErnKor can swim in the water for no more than $ k $ meters. For the sake of humanity, we have added not only crocodiles to the river, but also logs on which he can jump. Our test is as follows:

Initially, ErnKor is on the left bank and needs to reach the right bank. They are located at the $ 0 $ and $ n+1 $ meters respectively. The river can be represented as $ n $ segments, each with a length of $ 1 $ meter. Each segment contains either a log 'L', a crocodile 'C', or just water 'W'. ErnKor can move as follows:

- If he is on the surface (i.e., on the bank or on a log), he can jump forward for no more than $ m $ ( $ 1 \le m \le 10 $ ) meters (he can jump on the bank, on a log, or in the water).
- If he is in the water, he can only swim to the next river segment (or to the bank if he is at the $ n $ -th meter).
- ErnKor cannot land in a segment with a crocodile in any way.

Determine if ErnKor can reach the right bank.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains three numbers $ n, m, k $ ( $ 0 \le k \le 2 \cdot 10^5 $ , $ 1 \le n \le 2 \cdot 10^5 $ , $ 1 \le m \le 10 $ ) — the length of the river, the distance ErnKor can jump, and the number of meters ErnKor can swim without freezing.

The second line of each test case contains a string $ a $ of length $ n $ . $ a_i $ denotes the object located at the $ i $ -th meter. ( $ a_i \in \{ $ 'W','C','L' $ \} $ )

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output "YES" if ErnKor can pass the test, and output "NO" otherwise.

You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.

## 说明/提示

Let's consider examples:

- First example: We jump from the shore to the first log ( $ 0 \rightarrow 1 $ ), from the first log to the second ( $ 1 \rightarrow 3 $ ), from the second to the fourth ( $ 3 \rightarrow 5 $ ), and from the last log to the shore ( $ 5 \rightarrow 7 $ ). So, we have $ 0 \rightarrow 1 \rightarrow 3 \rightarrow 5 \rightarrow 7 $ . Since we did not encounter a crocodile and swam no more than k meters, the answer is «YES».
- Second example: $ 0 \rightarrow 1 $ , we jump into the water from the first log ( $ 1 \rightarrow 2 $ ), swim a cell to the log ( $ 2 \leadsto 3 $ ), $ 3 \rightarrow 4 \rightarrow 5 \rightarrow 6 \rightarrow 7 $ . Since we did not encounter a crocodile and swam no more than k meters, the answer is «YES».
- In the third example, ErnKor needs to swim two cells 'W', but can only swim one. Therefore, the answer is «NO».
- Sixth example: We jump from the shore into the water ( $ 0 \rightarrow 6 $ ) and swim one cell in the water ( $ 6 \leadsto 7 $ ). Since we did not encounter a crocodile and swam no more than k meters, the answer is «YES».

## 样例 #1

### 输入

```
6
6 2 0
LWLLLW
6 1 1
LWLLLL
6 1 1
LWLLWL
6 2 15
LWLLCC
6 10 0
CCCCCC
6 6 1
WCCCCW
```

### 输出

```
YES
YES
NO
NO
YES
YES
```



---

---
title: "Hungry Games"
layout: "post"
diff: 普及/提高-
pid: CF1994C
tag: ['动态规划 DP']
---

# Hungry Games

## 题目描述

### 题目大意

Yaroslav 正在玩一款电脑游戏，他的角色遇到了 $n$ 个蘑菇，第 $i$ 个蘑菇的毒性定义为 $a_i$。Yaroslav 可以选择两个整数 $1\le l\le r\le n$，并操控他的角色依次食用第 $l,l+1,\dots,r$ 个蘑菇。

Yaroslav 的角色有一个中毒属性 $g$，初始为 $0$。当他食用第 $i$ 个蘑菇时，$g$ 会增加 $a_i$，若此时 $g$ 超过了一个预设的最大中毒值 $x$，则 $g$ 会重置为 $0$。

Yaroslav 想知道有多少种选择 $l,r$ 的方案能使他的角色食用完蘑菇后，中毒属性 $g$ 不为 $0$。

## 输入格式

输入数据的第一行包括一个整数 $t\left(1\le t\le10^4\right)$，表示测试用例的组数。

对于每个测试用例：

- 第一行包括两个整数$n,x$ $\left(1\le n\le2\times10^5,1\le x\le10^9\right)$。
- 第二行包括 $n$ 个整数，依次表示 $a_1,a_2,\dots,a_n$ $\left(1\le a_i \le10^9\right)$。

## 输出格式

对于每个测试用例，输出一个整数，即符合题目条件的方案数。

## 样例 #1

### 输入

```
5
4 2
1 1 1 1
3 2
1 2 3
1 6
10
6 3
1 2 1 4 3 8
5 999999999
999999999 999999998 1000000000 1000000000 500000000
```

### 输出

```
8
2
0
10
7
```



---

---
title: "Add Zeros"
layout: "post"
diff: 普及/提高-
pid: CF2027C
tag: ['动态规划 DP', '数学', '记忆化搜索']
---

# Add Zeros

## 题目描述

You're given an array $ a $ initially containing $ n $ integers. In one operation, you must do the following:

- Choose a position $ i $ such that $ 1 < i \le |a| $ and $ a_i = |a| + 1 - i $ , where $ |a| $ is the current size of the array.
- Append $ i - 1 $ zeros onto the end of $ a $ .

After performing this operation as many times as you want, what is the maximum possible length of the array $ a $ ?

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 1000 $ ). The description of the test cases follows.

The first line of each test case contains $ n $ ( $ 1 \le n \le 3 \cdot 10^5 $ ) — the length of the array $ a $ .

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^{12} $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the maximum possible length of $ a $ after performing some sequence of operations.

## 说明/提示

In the first test case, we can first choose $ i = 4 $ , since $ a_4 = 5 + 1 - 4 = 2 $ . After this, the array becomes $ [2, 4, 6, 2, 5, 0, 0, 0] $ . We can then choose $ i = 3 $ since $ a_3 = 8 + 1 - 3 = 6 $ . After this, the array becomes $ [2, 4, 6, 2, 5, 0, 0, 0, 0, 0] $ , which has a length of $ 10 $ . It can be shown that no sequence of operations will make the final array longer.

In the second test case, we can choose $ i=2 $ , then $ i=3 $ , then $ i=4 $ . The final array will be $ [5, 4, 4, 5, 1, 0, 0, 0, 0, 0, 0] $ , with a length of $ 11 $ .

## 样例 #1

### 输入

```
4
5
2 4 6 2 5
5
5 4 4 5 1
4
6 8 2 3
1
1
```

### 输出

```
10
11
10
1
```



---

---
title: "New Rating"
layout: "post"
diff: 普及/提高-
pid: CF2029C
tag: ['动态规划 DP', '动态规划 DP']
---

# New Rating

## 题目描述

Hello, Codeforces Forcescode!





Kevin used to be a participant of Codeforces. Recently, the KDOI Team has developed a new Online Judge called Forcescode.

Kevin has participated in $ n $ contests on Forcescode. In the $ i $ -th contest, his performance rating is $ a_i $ .

Now he has hacked into the backend of Forcescode and will select an interval $ [l,r] $ ( $ 1\le l\le r\le n $ ), then skip all of the contests in this interval. After that, his rating will be recalculated in the following way:

- Initially, his rating is $ x=0 $ ;
- For each $ 1\le i\le n $ , after the $ i $ -th contest, 
  - If $ l\le i\le r $ , this contest will be skipped, and the rating will remain unchanged;
  - Otherwise, his rating will be updated according to the following rules: 
      - If $ a_i>x $ , his rating $ x $ will increase by $ 1 $ ;
      - If $ a_i=x $ , his rating $ x $ will remain unchanged;
      - If $ a_i<x $ , his rating $ x $ will decrease by $ 1 $ .

You have to help Kevin to find his maximum possible rating after the recalculation if he chooses the interval $ [l,r] $ optimally. Note that Kevin has to skip at least one contest.

## 输入格式

Each test contains multiple test cases. The first line of the input contains a single integer $ t $ ( $ 1\le t\le 5\cdot 10^4 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1\le n\le 3\cdot 10^5 $ ) — the number of contests.

The second line contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 1\le a_i\le n $ ) — the performance ratings in the contests.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the maximum possible rating after the recalculation if Kevin chooses the interval optimally.

## 说明/提示

In the first test case, Kevin must skip at least one contest. If he chooses any interval of length $ 1 $ , his rating after the recalculation will be equal to $ 5 $ .

In the second test case, Kevin's optimal choice is to select the interval $ [3,5] $ . During the recalculation, his rating changes as follows:

 $ $$$ 0 \xrightarrow{a_1=1} 1 \xrightarrow{a_2=2} 2 \xrightarrow{\mathtt{skip}} 2 \xrightarrow{\mathtt{skip}} 2 \xrightarrow{\mathtt{skip}} 2 \xrightarrow{a_6=3} 3 \xrightarrow{a_7=4} 4  $ $ </p><p>In the third test case, Kevin must skip the only contest, so his rating will remain at the initial value of  $ 0 $ .</p><p>In the fourth test case, Kevin's optimal choice is to select the interval  $ \[7,9\] $ . During the recalculation, his rating changes as follows:</p><p> $ $  0 \xrightarrow{a_1=9} 1 \xrightarrow{a_2=9} 2 \xrightarrow{a_3=8} 3 \xrightarrow{a_4=2} 2 \xrightarrow{a_5=4} 3 \xrightarrow{a_6=4} 4 \xrightarrow{\mathtt{skip}} 4 \xrightarrow{\mathtt{skip}} 4 \xrightarrow{\mathtt{skip}} 4  $ $ </p><p>In the fifth test case, Kevin's optimal choice is to select the interval  $ \[5,9\]$$$.

## 样例 #1

### 输入

```
5
6
1 2 3 4 5 6
7
1 2 1 1 1 3 4
1
1
9
9 9 8 2 4 4 3 5 3
10
1 2 3 4 1 3 2 1 1 10
```

### 输出

```
5
4
0
4
5
```



---

---
title: "Penchick and Desert Rabbit"
layout: "post"
diff: 普及/提高-
pid: CF2031D
tag: ['动态规划 DP']
---

# Penchick and Desert Rabbit

## 题目描述

Dedicated to pushing himself to his limits, Penchick challenged himself to survive the midday sun in the Arabian Desert!

While trekking along a linear oasis, Penchick spots a desert rabbit preparing to jump along a line of palm trees. There are $ n $ trees, each with a height denoted by $ a_i $ .

The rabbit can jump from the $ i $ -th tree to the $ j $ -th tree if exactly one of the following conditions is true:

- $ j < i $ and $ a_j > a_i $ : the rabbit can jump backward to a taller tree.
- $ j > i $ and $ a_j < a_i $ : the rabbit can jump forward to a shorter tree.

For each $ i $ from $ 1 $ to $ n $ , determine the maximum height among all trees that the rabbit can reach if it starts from the $ i $ -th tree.

## 输入格式

The first line contains the number of test cases $ t $ ( $ 1 \le t \le 5 \cdot 10^5 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 5 \cdot 10^5 $ ) — the number of trees.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) — the height of the trees.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5 \cdot 10^5 $ .

## 输出格式

For each test case, output $ n $ integers. The $ i $ -th integer should contain the maximum height among all trees that the rabbit can reach if it starts from the $ i $ -th tree.

## 说明/提示

In the first test case, the initial heights of trees are $ a = [2, 3, 1, 4] $ .

- If the rabbit starts from the first tree, it can jump to the third tree as $ 3 > 1 $ and $ 1 < 2 $ . Then, the rabbit can jump to the second tree as $ 2 < 3 $ and $ 3 > 1 $ . It can be proved that the rabbit cannot reach the fourth tree; hence, the maximum height of the tree that the rabbit can reach is $ a_2 = 3 $ .
- If the rabbit starts from the fourth tree, it does not need to jump anywhere as it is already at the highest tree.

In the second test case, the rabbit can jump to the first tree regardless of which tree it starts from.

In the fifth test case, if the rabbit starts from the fifth tree, it can jump to the fourth tree. Then the rabbit can jump to the seventh tree and finally reach the sixth tree. Therefore, the maximum height of the tree that the rabbit can reach is $ 8 $ .

## 样例 #1

### 输入

```
5
4
2 3 1 4
5
5 4 3 2 1
4
2 1 1 3
4
1 1 3 1
8
2 4 1 6 3 8 5 7
```

### 输出

```
3 3 3 4 
5 5 5 5 5 
2 2 2 3 
1 1 3 3 
8 8 8 8 8 8 8 8
```



---

---
title: "Sakurako's Field Trip"
layout: "post"
diff: 普及/提高-
pid: CF2033C
tag: ['动态规划 DP', '双指针 two-pointer', '分类讨论']
---

# Sakurako's Field Trip

## 题目描述

Even in university, students need to relax. That is why Sakurakos teacher decided to go on a field trip. It is known that all of the students will be walking in one line. The student with index $ i $ has some topic of interest which is described as $ a_i $ . As a teacher, you want to minimise the disturbance of the line of students.

The disturbance of the line is defined as the number of neighbouring people with the same topic of interest. In other words, disturbance is the number of indices $ j $ ( $ 1 \le j < n $ ) such that $ a_j = a_{j + 1} $ .

In order to do this, you can choose index $ i $ ( $ 1\le i\le n $ ) and swap students at positions $ i $ and $ n-i+1 $ . You can perform any number of swaps.

Your task is to determine the minimal amount of disturbance that you can achieve by doing the operation described above any number of times.

## 输入格式

The first line contains one integer $ t $ ( $ 1\le t\le 10^4 $ ) — the number of test cases.

Each test case is described by two lines.

- The first line contains one integer $ n $ ( $ 2 \le n \le 10^5 $ ) — the length of the line of students.
- The second line contains $ n $ integers $ a_i $ ( $ 1\le a_i\le n $ ) — the topics of interest of students in line.

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output the minimal possible disturbance of the line that you can achieve.

## 说明/提示

In the first example, it is necessary to apply the operation to $ i=2 $ , thus the array will become $ [1, \textbf{2}, 1, \textbf{1}, 3] $ , with the bold elements indicating those that have swapped places. The disturbance of this array is equal to $ 1 $ .

In the fourth example, it is sufficient to apply the operation to $ i=3 $ , thus the array will become $ [2, 1, \textbf{2}, \textbf{1}, 2, 4] $ . The disturbance of this array is equal to $ 0 $ .

In the eighth example, it is sufficient to apply the operation to $ i=3 $ , thus the array will become $ [1, 4, \textbf{1}, 5, \textbf{3}, 1, 3] $ . The disturbance of this array is equal to $ 0 $ .

## 样例 #1

### 输入

```
9
5
1 1 1 2 3
6
2 1 2 2 1 1
4
1 2 1 1
6
2 1 1 2 2 4
4
2 1 2 3
6
1 2 2 1 2 1
5
4 5 5 1 5
7
1 4 3 5 1 1 3
7
3 1 3 2 2 3 3
```

### 输出

```
1
2
1
0
0
1
1
0
2
```



---

---
title: "Kousuke's Assignment"
layout: "post"
diff: 普及/提高-
pid: CF2033D
tag: ['动态规划 DP', '前缀和']
---

# Kousuke's Assignment

## 题目描述

After a trip with Sakurako, Kousuke was very scared because he forgot about his programming assignment. In this assignment, the teacher gave him an array $ a $ of $ n $ integers and asked him to calculate the number of non-overlapping segments of the array $ a $ , such that each segment is considered beautiful.

A segment $ [l,r] $ is considered beautiful if $ a_l + a_{l+1} + \dots + a_{r-1} + a_r=0 $ .

For a fixed array $ a $ , your task is to compute the maximum number of non-overlapping beautiful segments.

## 输入格式

The first line of input contains the number $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases. Each test case consists of $ 2 $ lines.

- The first line contains one integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the length of the array.
- The second line contains $ n $ integers $ a_i $ ( $ -10^5 \le a_i \le 10^5 $ ) — the elements of the array $ a $ .

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 3\cdot 10^5 $ .

## 输出格式

For each test case, output a single integer: the maximum number of non-overlapping beautiful segments.

## 样例 #1

### 输入

```
3
5
2 1 -3 2 1
7
12 -4 4 43 -3 -5 8
6
0 -4 0 3 0 1
```

### 输出

```
1
2
3
```



---

---
title: "Three Strings"
layout: "post"
diff: 普及/提高-
pid: CF2050E
tag: ['动态规划 DP']
---

# Three Strings

## 题目描述

You are given three strings: $ a $ , $ b $ , and $ c $ , consisting of lowercase Latin letters. The string $ c $ was obtained in the following way:

1. At each step, either string $ a $ or string $ b $ was randomly chosen, and the first character of the chosen string was removed from it and appended to the end of string $ c $ , until one of the strings ran out. After that, the remaining characters of the non-empty string were added to the end of $ c $ .
2. Then, a certain number of characters in string $ c $ were randomly changed.

For example, from the strings $ a=\color{red}{\text{abra}} $ and $ b=\color{blue}{\text{cada}} $ , without character replacements, the strings $ \color{blue}{\text{ca}}\color{red}{\text{ab}}\color{blue}{\text{d}}\color{red}{\text{ra}}\color{blue}{\text{a}} $ , $ \color{red}{\text{abra}}\color{blue}{\text{cada}} $ , $ \color{red}{\text{a}}\color{blue}{\text{cada}}\color{red}{\text{bra}} $ could be obtained.

Find the minimum number of characters that could have been changed in string $ c $ .

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 10^3 $ ) — the number of test cases.

The first line of each test case contains one string of lowercase Latin letters $ a $ ( $ 1 \leq |a| \leq 10^3 $ ) — the first string, where $ |a| $ denotes the length of string $ a $ .

The second line of each test case contains one string of lowercase Latin letters $ b $ ( $ 1 \leq |b| \leq 10^3 $ ) — the second string, where $ |b| $ denotes the length of string $ b $ .

The third line of each test case contains one string of lowercase Latin letters $ c $ ( $ |c| = |a| + |b| $ ) — the third string.

It is guaranteed that the sum of $ |a| $ across all test cases does not exceed $ 2 \cdot 10^3 $ . Also, the sum of $ |b| $ across all test cases does not exceed $ 2 \cdot 10^3 $ .

## 输出格式

For each test case, output a single integer — the minimum number of characters that could have been changed in string $ c $ .

## 样例 #1

### 输入

```
7
a
b
cb
ab
cd
acbd
ab
ba
aabb
xxx
yyy
xyxyxy
a
bcd
decf
codes
horse
codeforces
egg
annie
egaegaeg
```

### 输出

```
1
0
2
0
3
2
3
```



---

---
title: "Unpleasant Strings"
layout: "post"
diff: 普及/提高-
pid: CF2104E
tag: ['动态规划 DP', '贪心']
---

# Unpleasant Strings

## 题目描述

我们称一个字母是允许的，当且仅当它是小写字母且属于拉丁字母表的前 $k$ 个字母。

给定一个长度为 $n$ 的字符串 $s$，它仅由允许的字母组成。

我们称一个字符串 $t$ 是愉快的，当且仅当 $t$ 是 $s$ 的子序列。

给定 $q$ 个字符串 $t_1, t_2, \dots, t_q$，它们都仅由允许的字母组成。对于每个字符串 $t_i$，计算最少需要在它的右侧追加多少个允许的字母，才能使其不再愉快。

序列 $t$ 是序列 $s$ 的子序列，当且仅当 $t$ 可以通过从 $s$ 中删除若干个（可以是零个或全部）任意位置的元素得到。

## 输入格式

第一行包含两个整数 $n$ 和 $k$（$1 \le n \le 10^6$；$1 \le k \le 26$）——字符串 $s$ 的长度和允许的字母数量。

第二行包含字符串 $s$，由 $n$ 个小写拉丁字母组成。字符串的每个字符都是拉丁字母表的前 $k$ 个字母之一。

第三行包含一个整数 $q$（$1 \le q \le 2 \cdot 10^5$）——查询的数量。

接下来的 $q$ 行包含查询：每行一个查询。第 $i$ 行包含字符串 $t_i$，仅由允许的字母组成。

输入数据的额外约束：所有 $t_i$ 的总长度不超过 $10^6$。


## 输出格式

对于每个查询，输出一个整数——最少需要在字符串右侧追加的允许字母数量，使其不再愉快。


## 说明/提示

在第一个样例中：

1. 字符串 cc 已经是不愉快的，因此不需要追加任何字母；
2. bcb 是愉快的，因此至少需要在右侧追加一个字母：bcba 仍然会保持愉快，但 bcbb 和 bcbc 是不愉快的；
3. 对于 b，至少需要追加两个字母，因为 ba、bb 和 bc 都是愉快的。例如，我们可以得到一个不愉快的字符串 bbb。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
7 3
abacaba
3
cc
bcb
b
```

### 输出

```
0
1
2
```

## 样例 #2

### 输入

```
5 1
aaaaa
6
a
aa
aaa
aaaa
aaaaa
aaaaaa
```

### 输出

```
5
4
3
2
1
0
```



---

---
title: "Kirei Attacks the Estate"
layout: "post"
diff: 普及/提高-
pid: CF2114E
tag: ['动态规划 DP', '贪心']
---

# Kirei Attacks the Estate

## 题目描述

Once, Kirei stealthily infiltrated the trap-filled estate of the Ainzbern family but was discovered by Kiritugu's familiar. Assessing his strength, Kirei decided to retreat. The estate is represented as a tree with $ n $ vertices, with the root at vertex $ 1 $ . Each vertex of the tree has a number $ a_i $ recorded, which represents the danger of vertex $ i $ . Recall that a tree is a connected undirected graph without cycles.

For a successful retreat, Kirei must compute the threat value for each vertex. The threat of a vertex is equal to the maximum alternating sum along the vertical path starting from that vertex. The alternating sum along the vertical path starting from vertex $ i $ is defined as $ a_i - a_{p_i} + a_{p_{p_i}} - \ldots $ , where $ p_i $ is the parent of vertex $ i $ on the path to the root (to vertex $ 1 $ ).

For example, in the tree below, vertex $ 4 $ has the following vertical paths:

- $ [4] $ with an alternating sum of $ a_4 = 6 $ ;
- $ [4, 3] $ with an alternating sum of $ a_4 - a_3 = 6 - 2 = 4 $ ;
- $ [4, 3, 2] $ with an alternating sum of $ a_4 - a_3 + a_2 = 6 - 2 + 5 = 9 $ ;
- $ [4, 3, 2, 1] $ with an alternating sum of $ a_4 - a_3 + a_2 - a_1 = 6 - 2 + 5 - 4 = 5 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2114E/041b3ada5bf12f77aa5a5a5b9431f1b90937ec72.png) The dangers of the vertices are indicated in red.Help Kirei compute the threat values for all vertices and escape the estate.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The following describes the test cases.

The first line contains an integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of vertices in the tree.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the dangers of the vertices.

The next $ n - 1 $ lines contain the numbers $ v, u $ ( $ 1 \le v, u \le n $ , $ v \neq u $ ) — the description of the edges of the tree.

It is guaranteed that the sum of $ n $ across all test cases does not exceed $ 2 \cdot 10^5 $ . It is also guaranteed that the given set of edges forms a tree.

## 输出格式

For each test case, output $ n $ integers — the threat of each vertex.

## 说明/提示

The tree from the first test case is depicted in the statement, and the maximum variable-sign sums are achieved as follows:

1. $ a_1 = 4 $ ;
2. $ a_2 = 5 $ ;
3. $ a_3 = 2 $ ;
4. $ a_4 - a_3 + a_2 = 6 - 2 + 5 = 9 $ ;
5. $ a_5 = 7 $ .

## 样例 #1

### 输入

```
2
5
4 5 2 6 7
1 2
3 2
4 3
5 1
6
1000000000 500500500 900900900 9 404 800800800
3 4
5 1
2 5
1 6
6 4
```

### 输出

```
4 5 2 9 7 
1000000000 1500500096 1701701691 199199209 404 800800800
```



---

---
title: "Gellyfish and Flaming Peony"
layout: "post"
diff: 普及/提高-
pid: CF2115A
tag: ['动态规划 DP', '广度优先搜索 BFS']
---

# Gellyfish and Flaming Peony

## 题目描述

Gellyfish hates math problems, but she has to finish her math homework:

Gellyfish is given an array of $ n $ positive integers $ a_1, a_2, \ldots, a_n $ .

She needs to do the following two-step operation until all elements of $ a $ are equal:

1. Select two indexes $ i $ , $ j $ satisfying $ 1 \leq i, j \leq n $ and $ i \neq j $ .
2. Replace $ a_i $ with $ \gcd(a_i, a_j) $ .

Now, Gellyfish asks you for the minimum number of operations to achieve her goal.

It can be proven that Gellyfish can always achieve her goal.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 5000 $ ). The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 5000 $ ) — the length of the array.

The second line of each test case contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 1 \leq a_i \leq 5000 $ ) — the elements of the array.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5000 $ .

## 输出格式

For each test case, output a single integer — the minimum number of operations to achieve her goal.

## 说明/提示

In the first test case, the following is a way that minimizes the number of operations:

1. Choose $ i = 3 $ and $ j=2 $ and replace $ a_3 $ with $ \gcd(a_3,a_2) = \gcd(30, 20) = 10 $ , then $ a $ becomes $ [12, 20, 10] $ .
2. Choose $ i=1 $ and $ j=3 $ and replace $ a_1 $ with $ \gcd(a_1,a_3) = \gcd(12, 10) = 2 $ , then $ a $ becomes $ [2, 20, 10] $ .
3. Choose $ i=2 $ and $ j=1 $ and replace $ a_2 $ with $ \gcd(a_2,a_1) = \gcd(20, 2) = 2 $ , then $ a $ becomes $ [2, 2, 10] $ .
4. Choose $ i=3 $ and $ j=1 $ and replace $ a_3 $ with $ \gcd(a_3,a_1) = \gcd(10, 2) = 2 $ , then $ a $ becomes $ [2, 2, 2] $ .

## 样例 #1

### 输入

```
3
3
12 20 30
6
1 9 1 9 8 1
3
6 14 15
```

### 输出

```
4
3
3
```



---

---
title: "Find Maximum"
layout: "post"
diff: 普及/提高-
pid: CF353C
tag: ['动态规划 DP', '贪心']
---

# Find Maximum

## 题目描述

Valera 有一个 $n$ 个数的 **非负整数** 数组 $a$ ，其元素分别为 $a_0,a_1,\cdots,a_{n-1}$。同时有一个函数 $f(x)=\sum_{i=0}^{n-1}a_i\cdot bit(i)$，$bit(i)$ 指的是数字 $x$ 在二进制中第 $i$ 位的值是否为 1。

举个例子，当 $n=4,x=11(11=2^0+2^1+2^3)$ 时，$f(x)=a_0+a_1+a_3$。

对于所有 $0\le x \le m$ 的整数 $x$ ，请求出 $f(x)$ 的最大值。

## 输入格式

第一行，输入 $n$ 。

接下来一行，输入数组 $a$ 。

最后一行输入一个由 $n$ 个数组成的数字序列 $s$ ，$s$ 即为 $m$ 的二进制翻转后的数字序列。（ 也就是 $m=\sum_{i=0}^{n-1}2^i\cdot s_i$ ）数字与数字之间没有空格。

## 输出格式

一行一个整数，表示 $f(x)$ 的最大值。

## 说明/提示

- $1 \le n \le 10^5$

- $0 \le a_i \le 10^4$

- $0\le s_i \le 1$

## 样例 #1

### 输入

```
2
3 8
10

```

### 输出

```
3

```

## 样例 #2

### 输入

```
5
17 0 10 2 1
11010

```

### 输出

```
27

```



---

---
title: "Little Pony and Expected Maximum"
layout: "post"
diff: 普及/提高-
pid: CF453A
tag: ['动态规划 DP', '期望']
---

# Little Pony and Expected Maximum

## 题目描述

暮暮刚刚在和她的朋友——AJ（苹果杰克）、FS（小蝶）、RD（云宝黛西）玩Ludo游戏。但是她马品没攒够总是输。回到城堡过后，她对游戏用的骰子产生了兴趣。


这个骰子有M面：骰子的第一面有一个点，第二面有两个点，以此类推，第m面含有M点。暮暮确信的是，当掷骰子时，每一面都有1/m的可能性出现，并且每次投掷的概率都是都是独立的。请你帮助她计算掷N次骰子后每次得到的点数中最大值的期望。

## 输入格式

一行两个整数 m 和 n (1 ≤ m, n ≤ 10^5).

## 输出格式

输出一行一个实数，与答案误差不大于10^-4

## 样例 #1

### 输入

```
6 1

```

### 输出

```
3.500000000000

```

## 样例 #2

### 输入

```
6 3

```

### 输出

```
4.958333333333

```

## 样例 #3

### 输入

```
2 2

```

### 输出

```
1.750000000000

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
title: "Woodcutters"
layout: "post"
diff: 普及/提高-
pid: CF545C
tag: ['动态规划 DP', '贪心']
---

# Woodcutters

## 题目描述

Little Susie listens to fairy tales before bed every day. Today's fairy tale was about wood cutters and the little girl immediately started imagining the choppers cutting wood. She imagined the situation that is described below.

There are $ n $ trees located along the road at points with coordinates $ x_{1},x_{2},...,x_{n} $ . Each tree has its height $ h_{i} $ . Woodcutters can cut down a tree and fell it to the left or to the right. After that it occupies one of the segments $ [x_{i}-h_{i},x_{i}] $ or $ [x_{i};x_{i}+h_{i}] $ . The tree that is not cut down occupies a single point with coordinate $ x_{i} $ . Woodcutters can fell a tree if the segment to be occupied by the fallen tree doesn't contain any occupied point. The woodcutters want to process as many trees as possible, so Susie wonders, what is the maximum number of trees to fell.

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of trees.

Next $ n $ lines contain pairs of integers $ x_{i},h_{i} $ ( $ 1<=x_{i},h_{i}<=10^{9} $ ) — the coordinate and the height of the $ і $ -th tree.

The pairs are given in the order of ascending $ x_{i} $ . No two trees are located at the point with the same coordinate.

## 输出格式

Print a single number — the maximum number of trees that you can cut down by the given rules.

## 说明/提示

In the first sample you can fell the trees like that:

- fell the $ 1 $ -st tree to the left — now it occupies segment $ [-1;1] $
- fell the $ 2 $ -nd tree to the right — now it occupies segment $ [2;3] $
- leave the $ 3 $ -rd tree — it occupies point $ 5 $
- leave the $ 4 $ -th tree — it occupies point $ 10 $
- fell the $ 5 $ -th tree to the right — now it occupies segment $ [19;20] $

In the second sample you can also fell $ 4 $ -th tree to the right, after that it will occupy segment $ [10;19] $ .

## 样例 #1

### 输入

```
5
1 2
2 1
5 10
10 9
19 1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
5
1 2
2 1
5 10
10 9
20 1

```

### 输出

```
4

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
title: "A Twisty Movement"
layout: "post"
diff: 普及/提高-
pid: CF933A
tag: ['动态规划 DP', '线段树', '枚举', '前缀和']
---

# A Twisty Movement

## 题目描述

A dragon symbolizes wisdom, power and wealth. On Lunar New Year's Day, people model a dragon with bamboo strips and clothes, raise them with rods, and hold the rods high and low to resemble a flying dragon.

A performer holding the rod low is represented by a $ 1 $ , while one holding it high is represented by a $ 2 $ . Thus, the line of performers can be represented by a sequence $ a_{1},a_{2},...,a_{n} $ .

Little Tommy is among them. He would like to choose an interval $ [l,r] $ ( $ 1<=l<=r<=n $ ), then reverse $ a_{l},a_{l+1},...,a_{r} $ so that the length of the longest non-decreasing subsequence of the new sequence is maximum.

A non-decreasing subsequence is a sequence of indices $ p_{1},p_{2},...,p_{k} $ , such that $ p_{1}<p_{2}<...<p_{k} $ and $ a_{p1}<=a_{p2}<=...<=a_{pk} $ . The length of the subsequence is $ k $ .

## 输入格式

The first line contains an integer $ n $ $ (1<=n<=2000) $ , denoting the length of the original sequence.

The second line contains $ n $ space-separated integers, describing the original sequence $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=2,i=1,2,...,n) $ .

## 输出格式

Print a single integer, which means the maximum possible length of the longest non-decreasing subsequence of the new sequence.

## 说明/提示

In the first example, after reversing $ [2,3] $ , the array will become $ [1,1,2,2] $ , where the length of the longest non-decreasing subsequence is $ 4 $ .

In the second example, after reversing $ [3,7] $ , the array will become $ [1,1,1,1,2,2,2,2,2,1] $ , where the length of the longest non-decreasing subsequence is $ 9 $ .

## 样例 #1

### 输入

```
4
1 2 1 2

```

### 输出

```
4

```

## 样例 #2

### 输入

```
10
1 1 2 2 2 1 1 2 2 1

```

### 输出

```
9

```



---

---
title: "Three displays"
layout: "post"
diff: 普及/提高-
pid: CF987C
tag: ['动态规划 DP', '线段树', '枚举']
---

# Three displays

## 题目描述

### 形式化题面

给定一个有两个性质 $s_i$ 和 $c_i$ 的数组，要求在其中选出三个数，满足：

 - $i<j<k$.
 - $s_i<s_j<s_k$.
 - $c_i+c_j+c_k$ 最小.

## 输入格式

第一行一个整数 $n$ 表示数组长度.

接下来一行 $n$ 个整数，表示 $s_i$.

接下来一行 $n$ 个整数，表示 $c_i$.

## 输出格式

一行一个整数，表示最小的 $c_i+c_j+c_k$

翻译 @[zymooll](/user/289296)

## 样例 #1

### 输入

```
5
2 4 5 4 10
40 30 20 10 40

```

### 输出

```
90

```

## 样例 #2

### 输入

```
3
100 101 100
2 4 5

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
10
1 2 3 4 5 6 7 8 9 10
10 13 11 14 15 12 13 13 18 13

```

### 输出

```
33

```



---

