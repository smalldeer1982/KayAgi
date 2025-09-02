---
title: "Border"
layout: "post"
diff: 提高+/省选-
pid: CF1010C
tag: ['最大公约数 gcd', '进制', '构造']
---

# Border

## 题目描述

Astronaut Natasha arrived on Mars. She knows that the Martians are very poor aliens. To ensure a better life for the Mars citizens, their emperor decided to take tax from every tourist who visited the planet. Natasha is the inhabitant of Earth, therefore she had to pay the tax to enter the territory of Mars.

There are $ n $ banknote denominations on Mars: the value of $ i $ -th banknote is $ a_i $ . Natasha has an infinite number of banknotes of each denomination.

Martians have $ k $ fingers on their hands, so they use a number system with base $ k $ . In addition, the Martians consider the digit $ d $ (in the number system with base $ k $ ) divine. Thus, if the last digit in Natasha's tax amount written in the number system with the base $ k $ is $ d $ , the Martians will be happy. Unfortunately, Natasha does not know the Martians' divine digit yet.

Determine for which values $ d $ Natasha can make the Martians happy.

Natasha can use only her banknotes. Martians don't give her change.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1 \le n \le 100\,000 $ , $ 2 \le k \le 100\,000 $ ) — the number of denominations of banknotes and the base of the number system on Mars.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — denominations of banknotes on Mars.

All numbers are given in decimal notation.

## 输出格式

On the first line output the number of values $ d $ for which Natasha can make the Martians happy.

In the second line, output all these values in increasing order.

Print all numbers in decimal notation.

## 说明/提示

Consider the first test case. It uses the octal number system.

If you take one banknote with the value of $ 12 $ , you will get $ 14_8 $ in octal system. The last digit is $ 4_8 $ .

If you take one banknote with the value of $ 12 $ and one banknote with the value of $ 20 $ , the total value will be $ 32 $ . In the octal system, it is $ 40_8 $ . The last digit is $ 0_8 $ .

If you take two banknotes with the value of $ 20 $ , the total value will be $ 40 $ , this is $ 50_8 $ in the octal system. The last digit is $ 0_8 $ .

No other digits other than $ 0_8 $ and $ 4_8 $ can be obtained. Digits $ 0_8 $ and $ 4_8 $ could also be obtained in other ways.

The second test case uses the decimal number system. The nominals of all banknotes end with zero, so Natasha can give the Martians only the amount whose decimal notation also ends with zero.

## 样例 #1

### 输入

```
2 8
12 20

```

### 输出

```
2
0 4 
```

## 样例 #2

### 输入

```
3 10
10 20 30

```

### 输出

```
1
0 
```



---

---
title: "Vasya And The Matrix"
layout: "post"
diff: 提高+/省选-
pid: CF1016D
tag: ['进制', '构造']
---

# Vasya And The Matrix

## 题目描述

Now Vasya is taking an exam in mathematics. In order to get a good mark, Vasya needs to guess the matrix that the teacher has constructed!

Vasya knows that the matrix consists of $ n $ rows and $ m $ columns. For each row, he knows the xor (bitwise excluding or) of the elements in this row. The sequence $ a_{1},a_{2},...,a_{n} $ denotes the xor of elements in rows with indices $ 1 $ , $ 2 $ , ..., $ n $ , respectively. Similarly, for each column, he knows the xor of the elements in this column. The sequence $ b_{1},b_{2},...,b_{m} $ denotes the xor of elements in columns with indices $ 1 $ , $ 2 $ , ..., $ m $ , respectively.

Help Vasya! Find a matrix satisfying the given constraints or tell him that there is no suitable matrix.

## 输入格式

The first line contains two numbers $ n $ and $ m (2<=n,m<=100) $ — the dimensions of the matrix.

The second line contains $ n $ numbers $ a_{1},a_{2},...,a_{n} (0<=a_{i}<=10^{9}) $ , where $ a_{i} $ is the xor of all elements in row $ i $ .

The third line contains $ m $ numbers $ b_{1},b_{2},...,b_{m} (0<=b_{i}<=10^{9}) $ , where $ b_{i} $ is the xor of all elements in column $ i $ .

## 输出格式

If there is no matrix satisfying the given constraints in the first line, output "NO".

Otherwise, on the first line output "YES", and then $ n $ rows of $ m $ numbers in each $ c_{i1},c_{i2},...\ ,c_{im} (0<=c_{ij}<=2·10^{9}) $ — the description of the matrix.

If there are several suitable matrices, it is allowed to print any of them.

## 样例 #1

### 输入

```
2 3
2 9
5 3 13

```

### 输出

```
YES
3 4 5
6 7 8

```

## 样例 #2

### 输入

```
3 3
1 7 6
2 15 12

```

### 输出

```
NO

```



---

---
title: "Binary Numbers AND Sum"
layout: "post"
diff: 提高+/省选-
pid: CF1066E
tag: ['模拟', '进制', '前缀和']
---

# Binary Numbers AND Sum

## 题目描述

## 题目大意



现在，给你两个位数为 $n$ 和 $m$ 的两个二进制数$a$,$b$，现在，我们要进行如下操作：



* 计算$a$&$b$

* 答案累加上一个操作的值

* $b$右移一位，最后一位直接舍弃



现在,请你算出最终的答案，并输出，答案对998244353取模

## 输入格式

第一行，两个整数$n$,$m$,$(1≤n,m≤2 \times 10^5)$



第一行，一个长度为$n$的二进制数$a$



第一行，一个长度为$m$的二进制数$b$

## 输出格式

一行，一个数，表示答案

## 样例 #1

### 输入

```
4 4
1010
1101

```

### 输出

```
12

```

## 样例 #2

### 输入

```
4 5
1001
10101

```

### 输出

```
11

```



---

---
title: "Compatible Numbers"
layout: "post"
diff: 提高+/省选-
pid: CF165E
tag: ['动态规划 DP', '枚举', '进制']
---

# Compatible Numbers

## 题目描述

Two integers $ x $ and $ y $ are compatible, if the result of their bitwise "AND" equals zero, that is, $ a $ $ & $ $ b=0 $ . For example, numbers $ 90 $ $ (1011010_{2}) $ and $ 36 $ $ (100100_{2}) $ are compatible, as $ 1011010_{2} $ $ & $ $ 100100_{2}=0_{2} $ , and numbers $ 3 $ $ (11_{2}) $ and $ 6 $ $ (110_{2}) $ are not compatible, as $ 11_{2} $ $ & $ $ 110_{2}=10_{2} $ .

You are given an array of integers $ a_{1},a_{2},...,a_{n} $ . Your task is to find the following for each array element: is this element compatible with some other element from the given array? If the answer to this question is positive, then you also should find any suitable element.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=10^{6} $ ) — the number of elements in the given array. The second line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ ( $ 1<=a_{i}<=4·10^{6} $ ) — the elements of the given array. The numbers in the array can coincide.

## 输出格式

Print $ n $ integers $ ans_{i} $ . If $ a_{i} $ isn't compatible with any other element of the given array $ a_{1},a_{2},...,a_{n} $ , then $ ans_{i} $ should be equal to -1. Otherwise $ ans_{i} $ is any such number, that $ a_{i} $ $ & $ $ ans_{i}=0 $ , and also $ ans_{i} $ occurs in the array $ a_{1},a_{2},...,a_{n} $ .

## 样例 #1

### 输入

```
2
90 36

```

### 输出

```
36 90
```

## 样例 #2

### 输入

```
4
3 6 3 6

```

### 输出

```
-1 -1 -1 -1
```

## 样例 #3

### 输入

```
5
10 6 9 8 2

```

### 输出

```
-1 8 2 2 8
```



---

---
title: "Roman and Numbers"
layout: "post"
diff: 提高+/省选-
pid: CF401D
tag: ['动态规划 DP', '枚举', '状态合并', '进制', '构造']
---

# Roman and Numbers

## 题目描述

Roman is a young mathematician, very famous in Uzhland. Unfortunately, Sereja doesn't think so. To make Sereja change his mind, Roman is ready to solve any mathematical problem. After some thought, Sereja asked Roma to find, how many numbers are close to number $ n $ , modulo $ m $ .

Number $ x $ is considered close to number $ n $ modulo $ m $ , if:

- it can be obtained by rearranging the digits of number $ n $ ,
- it doesn't have any leading zeroes,
- the remainder after dividing number $ x $ by $ m $ equals 0.

Roman is a good mathematician, but the number of such numbers is too huge for him. So he asks you to help him.

## 输入格式

The first line contains two integers: $ n $ $ (1<=n&lt;10^{18}) $ and $ m $ $ (1<=m<=100) $ .

## 输出格式

In a single line print a single integer — the number of numbers close to number $ n $ modulo $ m $ .

## 说明/提示

In the first sample the required numbers are: 104, 140, 410.

In the second sample the required number is 232.

## 样例 #1

### 输入

```
104 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
223 4

```

### 输出

```
1

```

## 样例 #3

### 输入

```
7067678 8

```

### 输出

```
47

```



---

---
title: "Interesting Array"
layout: "post"
diff: 提高+/省选-
pid: CF482B
tag: ['线段树', '进制', '构造']
---

# Interesting Array

## 题目描述

We'll call an array of $ n $ non-negative integers $ a\[1\],a\[2\],...,a\[n\] $ interesting, if it meets $ m $ constraints. The $ i $ -th of the $ m $ constraints consists of three integers $ l_{i} $ , $ r_{i} $ , $ q_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ) meaning that value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF482B/c5cfeb39e6b942f975aeab6674c1941b58030e74.png) should be equal to $ q_{i} $ .

Your task is to find any interesting array of $ n $ elements or state that such array doesn't exist.

Expression $ x&y $ means the bitwise AND of numbers $ x $ and $ y $ . In programming languages C++, Java and Python this operation is represented as "&", in Pascal — as "and".

## 输入格式

We'll call an array of $ n $ non-negative integers $ a\[1\],a\[2\],...,a\[n\] $ interesting, if it meets $ m $ constraints. The $ i $ -th of the $ m $ constraints consists of three integers $ l_{i} $ , $ r_{i} $ , $ q_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ) meaning that value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF482B/c5cfeb39e6b942f975aeab6674c1941b58030e74.png) should be equal to $ q_{i} $ .

Your task is to find any interesting array of $ n $ elements or state that such array doesn't exist.

Expression $ x&y $ means the bitwise AND of numbers $ x $ and $ y $ . In programming languages C++, Java and Python this operation is represented as "&", in Pascal — as "and".

## 输出格式

We'll call an array of $ n $ non-negative integers $ a\[1\],a\[2\],...,a\[n\] $ interesting, if it meets $ m $ constraints. The $ i $ -th of the $ m $ constraints consists of three integers $ l_{i} $ , $ r_{i} $ , $ q_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ) meaning that value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF482B/c5cfeb39e6b942f975aeab6674c1941b58030e74.png) should be equal to $ q_{i} $ .

Your task is to find any interesting array of $ n $ elements or state that such array doesn't exist.

Expression $ x&y $ means the bitwise AND of numbers $ x $ and $ y $ . In programming languages C++, Java and Python this operation is represented as "&", in Pascal — as "and".

## 样例 #1

### 输入

```
3 1
1 3 3

```

### 输出

```
YES
3 3 3

```

## 样例 #2

### 输入

```
3 2
1 3 3
1 3 2

```

### 输出

```
NO

```



---

---
title: "New Year Tree"
layout: "post"
diff: 提高+/省选-
pid: CF620E
tag: ['线段树', '状态合并', '进制']
---

# New Year Tree

## 题目描述

The New Year holidays are over, but Resha doesn't want to throw away the New Year tree. He invited his best friends Kerim and Gural to help him to redecorate the New Year tree.

The New Year tree is an undirected tree with $ n $ vertices and root in the vertex $ 1 $ .

You should process the queries of the two types:

1. Change the colours of all vertices in the subtree of the vertex $ v $ to the colour $ c $ .
2. Find the number of different colours in the subtree of the vertex $ v $ .

## 输入格式

The first line contains two integers $ n,m $ ( $ 1<=n,m<=4·10^{5} $ ) — the number of vertices in the tree and the number of the queries.

The second line contains $ n $ integers $ c_{i} $ ( $ 1<=c_{i}<=60 $ ) — the colour of the $ i $ -th vertex.

Each of the next $ n-1 $ lines contains two integers $ x_{j},y_{j} $ ( $ 1<=x_{j},y_{j}<=n $ ) — the vertices of the $ j $ -th edge. It is guaranteed that you are given correct undirected tree.

The last $ m $ lines contains the description of the queries. Each description starts with the integer $ t_{k} $ ( $ 1<=t_{k}<=2 $ ) — the type of the $ k $ -th query. For the queries of the first type then follows two integers $ v_{k},c_{k} $ ( $ 1<=v_{k}<=n,1<=c_{k}<=60 $ ) — the number of the vertex whose subtree will be recoloured with the colour $ c_{k} $ . For the queries of the second type then follows integer $ v_{k} $ ( $ 1<=v_{k}<=n $ ) — the number of the vertex for which subtree you should find the number of different colours.

## 输出格式

For each query of the second type print the integer $ a $ — the number of different colours in the subtree of the vertex given in the query.

Each of the numbers should be printed on a separate line in order of query appearing in the input.

## 样例 #1

### 输入

```
7 10
1 1 1 1 1 1 1
1 2
1 3
1 4
3 5
3 6
3 7
1 3 2
2 1
1 4 3
2 1
1 2 5
2 1
1 6 4
2 1
2 2
2 3

```

### 输出

```
2
3
4
5
1
2

```

## 样例 #2

### 输入

```
23 30
1 2 2 6 5 3 2 1 1 1 2 4 5 3 4 4 3 3 3 3 3 4 6
1 2
1 3
1 4
2 5
2 6
3 7
3 8
4 9
4 10
4 11
6 12
6 13
7 14
7 15
7 16
8 17
8 18
10 19
10 20
10 21
11 22
11 23
2 1
2 5
2 6
2 7
2 8
2 9
2 10
2 11
2 4
1 12 1
1 13 1
1 14 1
1 15 1
1 16 1
1 17 1
1 18 1
1 19 1
1 20 1
1 21 1
1 22 1
1 23 1
2 1
2 5
2 6
2 7
2 8
2 9
2 10
2 11
2 4

```

### 输出

```
6
1
3
3
2
1
2
3
5
5
1
2
2
1
1
1
2
3

```



---

---
title: "Xor-sequences"
layout: "post"
diff: 提高+/省选-
pid: CF691E
tag: ['模拟', '进制', '位运算']
---

# Xor-sequences

## 题目描述

You are given $ n $ integers $ a_{1},a_{2},...,a_{n} $ .

A sequence of integers $ x_{1},x_{2},...,x_{k} $ is called a "xor-sequence" if for every $ 1<=i<=k-1 $ the number of ones in the binary representation of the number $ x_{i} $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF691E/081f686069870b762728923799c454e27369af9a.png) $ x_{i+1} $ 's is a multiple of $ 3 $ and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF691E/187abd20483c4318d7cd71518f323b9990bcdd61.png) for all $ 1<=i<=k $ . The symbol ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF691E/081f686069870b762728923799c454e27369af9a.png) is used for the binary exclusive or operation.

How many "xor-sequences" of length $ k $ exist? Output the answer modulo $ 10^{9}+7 $ .

Note if $ a=[1,1] $ and $ k=1 $ then the answer is $ 2 $ , because you should consider the ones from $ a $ as different.

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n<=100 $ , $ 1<=k<=10^{18} $ ) — the number of given integers and the length of the "xor-sequences".

The second line contains $ n $ integers $ a_{i} $ ( $ 0<=a_{i}<=10^{18} $ ).

## 输出格式

Print the only integer $ c $ — the number of "xor-sequences" of length $ k $ modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
5 2
15 1 2 4 8

```

### 输出

```
13

```

## 样例 #2

### 输入

```
5 1
15 1 2 4 8

```

### 输出

```
5

```



---

---
title: "Vasiliy's Multiset"
layout: "post"
diff: 提高+/省选-
pid: CF706D
tag: ['素数判断,质数,筛法', '进制', '字典树 Trie']
---

# Vasiliy's Multiset

## 题目描述

Author has gone out of the stories about Vasiliy, so here is just a formal task description.

You are given $ q $ queries and a multiset $ A $ , initially containing only integer $ 0 $ . There are three types of queries:

1. "+ x" — add integer $ x $ to multiset $ A $ .
2. "- x" — erase one occurrence of integer $ x $ from multiset $ A $ . It's guaranteed that at least one $ x $ is present in the multiset $ A $ before this query.
3. "? x" — you are given integer $ x $ and need to compute the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/728a3690d3a76b81fb1ccb07b4c04b8d10b1870d.png), i.e. the maximum value of bitwise exclusive OR (also know as XOR) of integer $ x $ and some integer $ y $ from the multiset $ A $ .

Multiset is a set, where equal elements are allowed.

## 输入格式

The first line of the input contains a single integer $ q $ ( $ 1<=q<=200000 $ ) — the number of queries Vasiliy has to perform.

Each of the following $ q $ lines of the input contains one of three characters '+', '-' or '?' and an integer $ x_{i} $ ( $ 1<=x_{i}<=10^{9} $ ). It's guaranteed that there is at least one query of the third type.

Note, that the integer $ 0 $ will always be present in the set $ A $ .

## 输出格式

For each query of the type '?' print one integer — the maximum value of bitwise exclusive OR (XOR) of integer $ x_{i} $ and some integer from the multiset $ A $ .

## 说明/提示

After first five operations multiset $ A $ contains integers $ 0 $ , $ 8 $ , $ 9 $ , $ 11 $ , $ 6 $ and $ 1 $ .

The answer for the sixth query is integer ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/4b442d72cf0f109da9eae35430cf9dc9dfa35fdf.png) — maximum among integers ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/c712973b7cb6a6b393c3b423fc78dda636ebb034.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/e9b3f94b7acd1861f4b82fb60d691b2bd163374e.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/1bf5d0b4ff98720973629f7915ae529e790539ba.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/9023c8bab139f08429005ae47d2d497f5795be9b.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/e21b15be88af70287d01c0b8f13ae0d351197a9c.png).

## 样例 #1

### 输入

```
10
+ 8
+ 9
+ 11
+ 6
+ 1
? 3
- 8
? 3
? 8
? 11

```

### 输出

```
11
10
14
13

```



---

---
title: "Salazar Slytherin's Locket"
layout: "post"
diff: 提高+/省选-
pid: CF855E
tag: ['数位 DP', '状态合并', '进制']
---

# Salazar Slytherin's Locket

## 题目描述

Harry came to know from Dumbledore that Salazar Slytherin's locket is a horcrux. This locket was present earlier at 12 Grimmauld Place, the home of Sirius Black's mother. It was stolen from there and is now present in the Ministry of Magic in the office of Dolorous Umbridge, Harry's former Defense Against the Dark Arts teacher.

Harry, Ron and Hermione are infiltrating the Ministry. Upon reaching Umbridge's office, they observed a code lock with a puzzle asking them to calculate count of magic numbers between two integers $ l $ and $ r $ (both inclusive).

Harry remembered from his detention time with Umbridge that she defined a magic number as a number which when converted to a given base $ b $ , all the digits from $ 0 $ to $ b-1 $ appear even number of times in its representation without any leading zeros.

You have to answer $ q $ queries to unlock the office. Each query has three integers $ b_{i} $ , $ l_{i} $ and $ r_{i} $ , the base and the range for which you have to find the count of magic numbers.

## 输入格式

First line of input contains $ q $ ( $ 1<=q<=10^{5} $ ) — number of queries.

Each of the next $ q $ lines contain three space separated integers $ b_{i} $ , $ l_{i} $ , $ r_{i} $ ( $ 2<=b_{i}<=10 $ , $ 1<=l_{i}<=r_{i}<=10^{18} $ ).

## 输出格式

You have to output $ q $ lines, each containing a single integer, the answer to the corresponding query.

## 说明/提示

In sample test case $ 1 $ , for first query, when we convert numbers $ 4 $ to $ 9 $ into base $ 2 $ , we get:

- $ 4=100_{2} $ ,
- $ 5=101_{2} $ ,
- $ 6=110_{2} $ ,
- $ 7=111_{2} $ ,
- $ 8=1000_{2} $ ,
- $ 9=1001_{2} $ .

Out of these, only base $ 2 $ representation of $ 9 $ has even number of $ 1 $ and $ 0 $ . Thus, the answer is $ 1 $ .

## 样例 #1

### 输入

```
2
2 4 9
3 1 10

```

### 输出

```
1
2

```

## 样例 #2

### 输入

```
2
2 1 100
5 1 100

```

### 输出

```
21
4

```



---

---
title: "The Untended Antiquity"
layout: "post"
diff: 提高+/省选-
pid: CF869E
tag: ['树状数组', '进制', '差分']
---

# The Untended Antiquity

## 题目描述

Adieu l'ami.

Koyomi is helping Oshino, an acquaintance of his, to take care of an open space around the abandoned Eikou Cram School building, Oshino's makeshift residence.

The space is represented by a rectangular grid of $ n×m $ cells, arranged into $ n $ rows and $ m $ columns. The $ c $ -th cell in the $ r $ -th row is denoted by $ (r,c) $ .

Oshino places and removes barriers around rectangular areas of cells. Specifically, an action denoted by " $ 1\ r_{1}\ c_{1}\ r_{2}\ c_{2} $ " means Oshino's placing barriers around a rectangle with two corners being $ (r_{1},c_{1}) $ and $ (r_{2},c_{2}) $ and sides parallel to squares sides. Similarly, " $ 2\ r_{1}\ c_{1}\ r_{2}\ c_{2} $ " means Oshino's removing barriers around the rectangle. Oshino ensures that no barriers staying on the ground share any common points, nor do they intersect with boundaries of the $ n×m $ area.

Sometimes Koyomi tries to walk from one cell to another carefully without striding over barriers, in order to avoid damaging various items on the ground. " $ 3\ r_{1}\ c_{1}\ r_{2}\ c_{2} $ " means that Koyomi tries to walk from $ (r_{1},c_{1}) $ to $ (r_{2},c_{2}) $ without crossing barriers.

And you're here to tell Koyomi the feasibility of each of his attempts.

## 输入格式

The first line of input contains three space-separated integers $ n $ , $ m $ and $ q $ ( $ 1<=n,m<=2500 $ , $ 1<=q<=100000 $ ) — the number of rows and columns in the grid, and the total number of Oshino and Koyomi's actions, respectively.

The following $ q $ lines each describes an action, containing five space-separated integers $ t $ , $ r_{1} $ , $ c_{1} $ , $ r_{2} $ , $ c_{2} $ ( $ 1<=t<=3 $ , $ 1<=r_{1},r_{2}<=n $ , $ 1<=c_{1},c_{2}<=m $ ) — the type and two coordinates of an action. Additionally, the following holds depending on the value of $ t $ :

- If $ t=1 $ : $ 2<=r_{1}<=r_{2}<=n-1 $ , $ 2<=c_{1}<=c_{2}<=m-1 $ ;
- If $ t=2 $ : $ 2<=r_{1}<=r_{2}<=n-1 $ , $ 2<=c_{1}<=c_{2}<=m-1 $ , the specified group of barriers exist on the ground before the removal.
- If $ t=3 $ : no extra restrictions.

## 输出格式

For each of Koyomi's attempts (actions with $ t=3 $ ), output one line — containing "Yes" (without quotes) if it's feasible, and "No" (without quotes) otherwise.

## 说明/提示

For the first example, the situations of Koyomi's actions are illustrated below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF869E/5930e5689d91726564d05581955bbc9acf5a8c98.png)

## 样例 #1

### 输入

```
5 6 5
1 2 2 4 5
1 3 3 3 3
3 4 4 1 1
2 2 2 4 5
3 1 1 4 4

```

### 输出

```
No
Yes

```

## 样例 #2

### 输入

```
2500 2500 8
1 549 1279 1263 2189
1 303 795 1888 2432
1 2227 622 2418 1161
3 771 2492 1335 1433
1 2017 2100 2408 2160
3 48 60 798 729
1 347 708 1868 792
3 1940 2080 377 1546

```

### 输出

```
No
Yes
No

```



---

---
title: "Beads"
layout: "post"
diff: 提高+/省选-
pid: CF8E
tag: ['枚举', '进制', '概率论']
---

# Beads

## 题目描述

One Martian boy called Zorg wants to present a string of beads to his friend from the Earth — Masha. He knows that Masha likes two colours: blue and red, — and right in the shop where he has come, there is a variety of adornments with beads of these two colours. All the strings of beads have a small fastener, and if one unfastens it, one might notice that all the strings of beads in the shop are of the same length. Because of the peculiarities of the Martian eyesight, if Zorg sees one blue-and-red string of beads first, and then the other with red beads instead of blue ones, and blue — instead of red, he regards these two strings of beads as identical. In other words, Zorg regards as identical not only those strings of beads that can be derived from each other by the string turnover, but as well those that can be derived from each other by a mutual replacement of colours and/or by the string turnover.

It is known that all Martians are very orderly, and if a Martian sees some amount of objects, he tries to put them in good order. Zorg thinks that a red bead is smaller than a blue one. Let's put 0 for a red bead, and 1 — for a blue one. From two strings the Martian puts earlier the string with a red bead in the $ i $ -th position, providing that the second string has a blue bead in the $ i $ -th position, and the first two beads $ i-1 $ are identical.

At first Zorg unfastens all the strings of beads, and puts them into small heaps so, that in each heap strings are identical, in his opinion. Then he sorts out the heaps and chooses the minimum string in each heap, in his opinion. He gives the unnecassary strings back to the shop assistant and says he doesn't need them any more. Then Zorg sorts out the remaining strings of beads and buys the string with index $ k $ .

All these manupulations will take Zorg a lot of time, that's why he asks you to help and find the string of beads for Masha.

## 输入格式

The input file contains two integers $ n $ and $ k $ ( $ 2<=n<=50;1<=k<=10^{16} $ ) —the length of a string of beads, and the index of the string, chosen by Zorg.

## 输出格式

Output the $ k $ -th string of beads, putting 0 for a red bead, and 1 — for a blue one. If it s impossible to find the required string, output the only number -1.

## 说明/提示

Let's consider the example of strings of length 4 — 0001, 0010, 0011, 0100, 0101, 0110, 0111, 1000, 1001, 1010, 1011, 1100, 1101, 1110. Zorg will divide them into heaps: {0001, 0111, 1000, 1110}, {0010, 0100, 1011, 1101}, {0011, 1100}, {0101, 1010}, {0110, 1001}. Then he will choose the minimum strings of beads in each heap: 0001, 0010, 0011, 0101, 0110. The forth string — 0101.

## 样例 #1

### 输入

```
4 4

```

### 输出

```
0101

```



---

---
title: "Jamie and Binary Sequence (changed after round)"
layout: "post"
diff: 提高+/省选-
pid: CF916B
tag: ['进制']
---

# Jamie and Binary Sequence (changed after round)

## 题目描述

Jamie is preparing a Codeforces round. He has got an idea for a problem, but does not know how to solve it. Help him write a solution to the following problem:

Find $ k $ integers such that the sum of two to the power of each number equals to the number $ n $ and the largest integer in the answer is as small as possible. As there may be multiple answers, you are asked to output the lexicographically largest one.

To be more clear, consider all integer sequence with length $ k $ $ (a_{1},a_{2},...,a_{k}) $ with ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916B/804a330680fa0a689680c55396d7d651c977b163.png). Give a value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916B/3a6d52e5a86468620a5b59c3452f1e46ca1a5ee4.png) to each sequence. Among all sequence(s) that have the minimum $ y $ value, output the one that is the lexicographically largest.

For definitions of powers and lexicographical order see notes.


## 输入格式

The first line consists of two integers $ n $ and $ k $ ( $ 1<=n<=10^{18},1<=k<=10^{5}) $ — the required sum and the length of the sequence.

## 输出格式

Output "No" (without quotes) in a single line if there does not exist such sequence. Otherwise, output "Yes" (without quotes) in the first line, and $ k $ numbers separated by space in the second line — the required sequence.

It is guaranteed that the integers in the answer sequence fit the range $ [-10^{18},10^{18}] $ .

## 说明/提示

Sample 1:

 $ 2^{3}+2^{3}+2^{2}+2^{1}+2^{0}=8+8+4+2+1=23 $

Answers like $ (3,3,2,0,1) $ or $ (0,1,2,3,3) $ are not lexicographically largest.

Answers like $ (4,1,1,1,0) $ do not have the minimum $ y $ value.

Sample 2:

It can be shown there does not exist a sequence with length 2.

Sample 3:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916B/32c976228a27c0f708bbb18d0f890775f96c4e59.png)

Powers of 2:

If $ x>0 $ , then $ 2^{x}=2·2·2·...·2 $ ( $ x $ times).

If $ x=0 $ , then $ 2^{x}=1 $ .

If $ x<0 $ , then ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916B/6fdb1f744a78ad201a27505654584044743d34f7.png).

Lexicographical order:

Given two different sequences of the same length, $ (a_{1},a_{2},...\ ,a_{k}) $ and $ (b_{1},b_{2},...\ ,b_{k}) $ , the first one is smaller than the second one for the lexicographical order, if and only if $ a_{i}<b_{i} $ , for the first $ i $ where $ a_{i} $ and $ b_{i} $ differ.

## 样例 #1

### 输入

```
23 5

```

### 输出

```
Yes
3 3 2 1 0 

```

## 样例 #2

### 输入

```
13 2

```

### 输出

```
No

```

## 样例 #3

### 输入

```
1 2

```

### 输出

```
Yes
-1 -1 

```



---

---
title: "Mahmoud and Ehab and the xor-MST"
layout: "post"
diff: 提高+/省选-
pid: CF959E
tag: ['生成树', '进制', '前缀和']
---

# Mahmoud and Ehab and the xor-MST

## 题目描述

Ehab is interested in the bitwise-xor operation and the special graphs. Mahmoud gave him a problem that combines both. He has a complete graph consisting of $ n $ vertices numbered from $ 0 $ to $ n-1 $ . For all $ 0<=u<v<n $ , vertex $ u $ and vertex $ v $ are connected with an undirected edge that has weight ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF959E/31294aedffbec70e119efb89ca1f6d2afecc694a.png) (where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF959E/bc47da33894a98df53134f30108d8405a90ea418.png) is the [bitwise-xor operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)). Can you find the weight of the minimum spanning tree of that graph?

You can read about complete graphs in [https://en.wikipedia.org/wiki/Complete\_graph](https://en.wikipedia.org/wiki/Complete_graph)

You can read about the minimum spanning tree in [https://en.wikipedia.org/wiki/Minimum\_spanning\_tree](https://en.wikipedia.org/wiki/Minimum_spanning_tree)

The weight of the minimum spanning tree is the sum of the weights on the edges included in it.

## 输入格式

The only line contains an integer $ n $ $ (2<=n<=10^{12}) $ , the number of vertices in the graph.

## 输出格式

The only line contains an integer $ x $ , the weight of the graph's minimum spanning tree.

## 说明/提示

In the first sample: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF959E/da1dd366c44de9a7fa58c6a7748f6a57cd6a4b83.png) The weight of the minimum spanning tree is 1+2+1=4.

## 样例 #1

### 输入

```
4

```

### 输出

```
4
```



---

---
title: "Lucky Country"
layout: "post"
diff: 提高+/省选-
pid: CF95E
tag: ['背包 DP', '连通块', '进制']
---

# Lucky Country

## 题目描述

Petya loves lucky numbers. Everybody knows that positive integers are lucky if their decimal representation doesn't contain digits other than $ 4 $ and $ 7 $ . For example, numbers $ 47 $ , $ 744 $ , $ 4 $ are lucky and $ 5 $ , $ 17 $ , $ 467 $ are not.

One night Petya was sleeping. He was dreaming of being the president of some island country. The country is represented by islands connected by two-way roads. Between some islands there is no road way, even through other islands, that's why the country is divided into several regions. More formally, each island belongs to exactly one region, there is a path between any two islands located in the same region; there is no path between any two islands from different regions. A region is lucky if the amount of islands in it is a lucky number.

As a real president, Petya first decided to build a presidential palace. Being a lucky numbers' fan, Petya wants to position his palace in one of the lucky regions. However, it is possible that initially the country has no such regions. In this case Petya can build additional roads between different regions, thus joining them. Find the minimum number of roads needed to build to create a lucky region.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n,m<=10^{5} $ ). They are the number of islands and the number of roads correspondingly. Next $ m $ lines contain road descriptions. Each road is defined by the numbers of islands that it connects: that is, by two integers $ u $ and $ v $ ( $ 1<=u,v<=n $ ). Some roads can connect an island with itself; there can be more than one road between a pair of islands. Numbers in each line are separated by exactly one space character.

## 输出格式

If there's no solution, output the only number "-1" (without the quotes). Otherwise, output the minimum number of roads $ r $ that need to be built to get a lucky region.

## 样例 #1

### 输入

```
4 3
1 2
2 3
1 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5 4
1 2
3 4
4 5
3 5

```

### 输出

```
-1

```



---

