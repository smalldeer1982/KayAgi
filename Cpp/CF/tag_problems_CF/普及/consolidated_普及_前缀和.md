---
title: "Covered Points Count"
layout: "post"
diff: 普及/提高-
pid: CF1000C
tag: ['枚举', '排序', '前缀和']
---

# Covered Points Count

## 题目描述

**题目大意：**

给你n个区间，求被这些区间覆盖层数为$k(k<=n)$的点的个数

## 输入格式

第一行一个整数，$n$，$n<=2*10^5$

以下$n$行，每行有两个整数，即这个区间的左右端点$l,r(0<=l<=r<=10^{18})$

## 输出格式

$n$个整数，即每个被覆盖层数对应的点的个数

感谢@守望 提供翻译

## 样例 #1

### 输入

```
3
0 3
1 3
3 8

```

### 输出

```
6 2 1 

```

## 样例 #2

### 输入

```
3
1 3
2 4
5 7

```

### 输出

```
5 2 0 

```



---

---
title: "Polycarp and Div 3"
layout: "post"
diff: 普及/提高-
pid: CF1005D
tag: ['字符串', '贪心', '前缀和']
---

# Polycarp and Div 3

## 题目描述

Polycarp likes numbers that are divisible by 3.

He has a huge number $ s $ . Polycarp wants to cut from it the maximum number of numbers that are divisible by $ 3 $ . To do this, he makes an arbitrary number of vertical cuts between pairs of adjacent digits. As a result, after $ m $ such cuts, there will be $ m+1 $ parts in total. Polycarp analyzes each of the obtained numbers and finds the number of those that are divisible by $ 3 $ .

For example, if the original number is $ s=3121 $ , then Polycarp can cut it into three parts with two cuts: $ 3|1|21 $ . As a result, he will get two numbers that are divisible by $ 3 $ .

Polycarp can make an arbitrary number of vertical cuts, where each cut is made between a pair of adjacent digits. The resulting numbers cannot contain extra leading zeroes (that is, the number can begin with 0 if and only if this number is exactly one character '0'). For example, 007, 01 and 00099 are not valid numbers, but 90, 0 and 10001 are valid.

What is the maximum number of numbers divisible by $ 3 $ that Polycarp can obtain?

## 输入格式

The first line of the input contains a positive integer $ s $ . The number of digits of the number $ s $ is between $ 1 $ and $ 2\cdot10^5 $ , inclusive. The first (leftmost) digit is not equal to 0.

## 输出格式

Print the maximum number of numbers divisible by $ 3 $ that Polycarp can get by making vertical cuts in the given number $ s $ .

## 说明/提示

In the first example, an example set of optimal cuts on the number is 3|1|21.

In the second example, you do not need to make any cuts. The specified number 6 forms one number that is divisible by $ 3 $ .

In the third example, cuts must be made between each pair of digits. As a result, Polycarp gets one digit 1 and $ 33 $ digits 0. Each of the $ 33 $ digits 0 forms a number that is divisible by $ 3 $ .

In the fourth example, an example set of optimal cuts is 2|0|1|9|201|81. The numbers $ 0 $ , $ 9 $ , $ 201 $ and $ 81 $ are divisible by $ 3 $ .

## 样例 #1

### 输入

```
3121

```

### 输出

```
2

```

## 样例 #2

### 输入

```
6

```

### 输出

```
1

```

## 样例 #3

### 输入

```
1000000000000000000000000000000000

```

### 输出

```
33

```

## 样例 #4

### 输入

```
201920181

```

### 输出

```
4

```



---

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
title: "Segment Occurrences"
layout: "post"
diff: 普及/提高-
pid: CF1016B
tag: ['前缀和']
---

# Segment Occurrences

## 题目描述

You are given two strings $ s $ and $ t $ , both consisting only of lowercase Latin letters.

The substring $ s[l..r] $ is the string which is obtained by taking characters $ s_l, s_{l + 1}, \dots, s_r $ without changing the order.

Each of the occurrences of string $ a $ in a string $ b $ is a position $ i $ ( $ 1 \le i \le |b| - |a| + 1 $ ) such that $ b[i..i + |a| - 1] = a $ ( $ |a| $ is the length of string $ a $ ).

You are asked $ q $ queries: for the $ i $ -th query you are required to calculate the number of occurrences of string $ t $ in a substring $ s[l_i..r_i] $ .

## 输入格式

The first line contains three integer numbers $ n $ , $ m $ and $ q $ ( $ 1 \le n, m \le 10^3 $ , $ 1 \le q \le 10^5 $ ) — the length of string $ s $ , the length of string $ t $ and the number of queries, respectively.

The second line is a string $ s $ ( $ |s| = n $ ), consisting only of lowercase Latin letters.

The third line is a string $ t $ ( $ |t| = m $ ), consisting only of lowercase Latin letters.

Each of the next $ q $ lines contains two integer numbers $ l_i $ and $ r_i $ ( $ 1 \le l_i \le r_i \le n $ ) — the arguments for the $ i $ -th query.

## 输出格式

Print $ q $ lines — the $ i $ -th line should contain the answer to the $ i $ -th query, that is the number of occurrences of string $ t $ in a substring $ s[l_i..r_i] $ .

## 说明/提示

In the first example the queries are substrings: "cod", "deforces", "fo" and "for", respectively.

## 样例 #1

### 输入

```
10 3 4
codeforces
for
1 3
3 10
5 6
5 7

```

### 输出

```
0
1
0
1

```

## 样例 #2

### 输入

```
15 2 3
abacabadabacaba
ba
1 15
3 4
2 14

```

### 输出

```
4
0
3

```

## 样例 #3

### 输入

```
3 5 2
aaa
baaab
1 3
1 1

```

### 输出

```
0
0

```



---

---
title: "Vasya and Golden Ticket"
layout: "post"
diff: 普及/提高-
pid: CF1030C
tag: ['搜索', '枚举', '前缀和']
---

# Vasya and Golden Ticket

## 题目描述

Recently Vasya found a golden ticket — a sequence which consists of $ n $ digits $ a_1a_2\dots a_n $ . Vasya considers a ticket to be lucky if it can be divided into two or more non-intersecting segments with equal sums. For example, ticket $ 350178 $ is lucky since it can be divided into three segments $ 350 $ , $ 17 $ and $ 8 $ : $ 3+5+0=1+7=8 $ . Note that each digit of sequence should belong to exactly one segment.

Help Vasya! Tell him if the golden ticket he found is lucky or not.

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 100 $ ) — the number of digits in the ticket.

The second line contains $ n $ digits $ a_1 a_2 \dots a_n $ ( $ 0 \le a_i \le 9 $ ) — the golden ticket. Digits are printed without spaces.

## 输出格式

If the golden ticket is lucky then print "YES", otherwise print "NO" (both case insensitive).

## 说明/提示

In the first example the ticket can be divided into $ 7 $ , $ 34 $ and $ 52 $ : $ 7=3+4=5+2 $ .

In the second example it is impossible to divide ticket into segments with equal sum.

## 样例 #1

### 输入

```
5
73452

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
4
1248

```

### 输出

```
NO

```



---

---
title: "Glider"
layout: "post"
diff: 普及/提高-
pid: CF1041D
tag: ['二分', '前缀和']
---

# Glider

## 题目描述

```
你在玩一个吃鸡游戏，你现在要跳伞。你的飞机现在在高度为$h$的空中飞行，你每飞一个单位长度的距离，你就会下落一个单位长度的高度，当然，有些地方是上升气流，你不会下落，你会往前直飞，由于你想在空中就被人打死，求你最远的飞行距离

## 输入格式

第一行两个正整数$n$，$h$，代表有$n$段上升气流，飞机的高度为$h$。

接下来$n$行，每行两个数$x_{i1}$，$x_{i2}$。代表$x_{i1}$至$x_{i2}$这段区间为上升气流。

## 输出格式

一个整数，代表你最远的飞行距离
```

## 样例 #1

### 输入

```
3 4
2 5
7 9
10 11

```

### 输出

```
10

```

## 样例 #2

### 输入

```
5 10
5 7
11 12
16 20
25 26
30 33

```

### 输出

```
18

```

## 样例 #3

### 输入

```
1 1000000000
1 1000000000

```

### 输出

```
1999999999

```



---

---
title: "Flamingoes of Mystery"
layout: "post"
diff: 普及/提高-
pid: CF1425F
tag: ['前缀和']
---

# Flamingoes of Mystery

## 题目描述

This is an interactive problem. You have to use a flush operation right after printing each line. For example, in C++ you should use the function fflush(stdout), in Java — System.out.flush(), in Pascal — flush(output) and in Python — sys.stdout.flush().

Mr. Chanek wants to buy a flamingo to accompany his chickens on his farm. Before going to the pet shop, Mr. Chanek stops at an animal festival to have fun. It turns out there is a carnival game with a flamingo as the prize.

There are $ N $ mysterious cages, which are numbered from $ 1 $ to $ N $ . Cage $ i $ has $ A_i $ $ (0 \le A_i \le 10^3) $ flamingoes inside $ (1 \le i \le N) $ . However, the game master keeps the number of flamingoes inside a secret. To win the flamingo, Mr. Chanek must guess the number of flamingoes in each cage.

Coincidentally, Mr. Chanek has $ N $ coins. Each coin can be used to ask once, what is the total number of flamingoes inside cages numbered $ L $ to $ R $ inclusive? With $ L < R $ .

## 输入格式

Use standard input to read the responses of your questions.

Initially, the judge will give an integer $ N $ $ (3 \le N \le 10^3) $ , the number of cages, and the number of coins Mr. Chanek has.

For each of your questions, the jury will give an integer that denotes the number of flamingoes from cage $ L $ to $ R $ inclusive.

If your program does not guess the flamingoes or ask other questions, you will get "Wrong Answer". Of course, if your program asks more questions than the allowed number, your program will get "Wrong Answer".

## 输出格式

To ask questions, your program must use standard output.

Then, you can ask at most $ N $ questions. Questions are asked in the format "? L R", ( $ 1 \le L < R \le N $ ).

To guess the flamingoes, print a line that starts with "!" followed by $ N $ integers where the $ i $ -th integer denotes the number of flamingo in cage $ i $ . After answering, your program must terminate or will receive the "idle limit exceeded" verdict. You can only guess the flamingoes once.

## 说明/提示

In the sample input, the correct flamingoes amount is $ [1, 4, 4, 6, 7, 8] $ .

## 样例 #1

### 输入

```
6
 
5
 
15
 
10
 
```

### 输出

```
 
? 1 2
 
? 5 6
 
? 3 4
 
! 1 4 4 6 7 8
```



---

---
title: "Counting Rectangles"
layout: "post"
diff: 普及/提高-
pid: CF1722E
tag: ['前缀和', '差分']
---

# Counting Rectangles

## 题目描述

You have $ n $ rectangles, the $ i $ -th rectangle has height $ h_i $ and width $ w_i $ .

You are asked $ q $ queries of the form $ h_s \ w_s \ h_b \ w_b $ .

For each query output, the total area of rectangles you own that can fit a rectangle of height $ h_s $ and width $ w_s $ while also fitting in a rectangle of height $ h_b $ and width $ w_b $ . In other words, print $ \sum h_i \cdot w_i $ for $ i $ such that $ h_s < h_i < h_b $ and $ w_s < w_i < w_b $ .

Please note, that if two rectangles have the same height or the same width, then they cannot fit inside each other. Also note that you cannot rotate rectangles.

Please note that the answer for some test cases won't fit into 32-bit integer type, so you should use at least 64-bit integer type in your programming language (like long long for C++).

## 输入格式

The first line of the input contains an integer $ t $ ( $ 1 \leq t \leq 100 $ ) — the number of test cases.

The first line of each test case two integers $ n, q $ ( $ 1 \leq n \leq 10^5 $ ; $ 1 \leq q \leq 10^5 $ ) — the number of rectangles you own and the number of queries.

Then $ n $ lines follow, each containing two integers $ h_i, w_i $ ( $ 1 \leq h_i, w_i \leq 1000 $ ) — the height and width of the $ i $ -th rectangle.

Then $ q $ lines follow, each containing four integers $ h_s, w_s, h_b, w_b $ ( $ 1 \leq h_s < h_b,\ w_s < w_b \leq 1000 $ ) — the description of each query.

The sum of $ q $ over all test cases does not exceed $ 10^5 $ , and the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output $ q $ lines, the $ i $ -th line containing the answer to the $ i $ -th query.

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1722E/eea41631a59a3be709b240003a8697e693220564.png)In the first test case, there is only one query. We need to find the sum of areas of all rectangles that can fit a $ 1 \times 1 $ rectangle inside of it and fit into a $ 3 \times 4 $ rectangle.

Only the $ 2 \times 3 $ rectangle works, because $ 1 < 2 $ (comparing heights) and $ 1 < 3 $ (comparing widths), so the $ 1 \times 1 $ rectangle fits inside, and $ 2 < 3 $ (comparing heights) and $ 3 < 4 $ (comparing widths), so it fits inside the $ 3 \times 4 $ rectangle. The $ 3 \times 2 $ rectangle is too tall to fit in a $ 3 \times 4 $ rectangle. The total area is $ 2 \cdot 3 = 6 $ .

## 样例 #1

### 输入

```
3
2 1
2 3
3 2
1 1 3 4
5 5
1 1
2 2
3 3
4 4
5 5
3 3 6 6
2 1 4 5
1 1 2 10
1 1 100 100
1 1 3 3
3 1
999 999
999 999
999 998
1 1 1000 1000
```

### 输出

```
6
41
9
0
54
4
2993004
```



---

---
title: "Stripe"
layout: "post"
diff: 普及/提高-
pid: CF18C
tag: ['模拟', '枚举', '前缀和']
---

# Stripe

## 题目描述

Once Bob took a paper stripe of $ n $ squares (the height of the stripe is 1 square). In each square he wrote an integer number, possibly negative. He became interested in how many ways exist to cut this stripe into two pieces so that the sum of numbers from one piece is equal to the sum of numbers from the other piece, and each piece contains positive integer amount of squares. Would you help Bob solve this problem?

## 输入格式

The first input line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — amount of squares in the stripe. The second line contains $ n $ space-separated numbers — they are the numbers written in the squares of the stripe. These numbers are integer and do not exceed 10000 in absolute value.

## 输出格式

Output the amount of ways to cut the stripe into two non-empty pieces so that the sum of numbers from one piece is equal to the sum of numbers from the other piece. Don't forget that it's allowed to cut the stripe along the squares' borders only.

## 样例 #1

### 输入

```
9
1 5 -6 7 9 -16 0 -2 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
3
1 1 1

```

### 输出

```
0

```

## 样例 #3

### 输入

```
2
0 0

```

### 输出

```
1

```



---

---
title: "Closest Cities"
layout: "post"
diff: 普及/提高-
pid: CF1922C
tag: ['贪心', '前缀和']
---

# Closest Cities

## 题目描述

There are $ n $ cities located on the number line, the $ i $ -th city is in the point $ a_i $ . The coordinates of the cities are given in ascending order, so $ a_1 < a_2 < \dots < a_n $ .

The distance between two cities $ x $ and $ y $ is equal to $ |a_x - a_y| $ .

For each city $ i $ , let's define the closest city $ j $ as the city such that the distance between $ i $ and $ j $ is not greater than the distance between $ i $ and each other city $ k $ . For example, if the cities are located in points $ [0, 8, 12, 15, 20] $ , then:

- the closest city to the city $ 1 $ is the city $ 2 $ ;
- the closest city to the city $ 2 $ is the city $ 3 $ ;
- the closest city to the city $ 3 $ is the city $ 4 $ ;
- the closest city to the city $ 4 $ is the city $ 3 $ ;
- the closest city to the city $ 5 $ is the city $ 4 $ .

The cities are located in such a way that for every city, the closest city is unique. For example, it is impossible for the cities to be situated in points $ [1, 2, 3] $ , since this would mean that the city $ 2 $ has two closest cities ( $ 1 $ and $ 3 $ , both having distance $ 1 $ ).

You can travel between cities. Suppose you are currently in the city $ x $ . Then you can perform one of the following actions:

- travel to any other city $ y $ , paying $ |a_x - a_y| $ coins;
- travel to the city which is the closest to $ x $ , paying $ 1 $ coin.

You are given $ m $ queries. In each query, you will be given two cities, and you have to calculate the minimum number of coins you have to spend to travel from one city to the other city.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Each test case is given in the following format:

- the first line contains one integer $ n $ ( $ 2 \le n \le 10^5 $ );
- the second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_1 < a_2 < \dots < a_n \le 10^9 $ );
- the third line contains one integer $ m $ ( $ 1 \le m \le 10^5 $ );
- then $ m $ lines follow; the $ i $ -th of them contains two integers $ x_i $ and $ y_i $ ( $ 1 \le x_i, y_i \le n $ ; $ x_i \ne y_i $ ), denoting that in the $ i $ -th query, you have to calculate the minimum number of coins you have to spend to travel from the city $ x_i $ to the city $ y_i $ .

Additional constraints on the input:

- in every test case, for each city, the closest city is determined uniquely;
- the sum of $ n $ over all test cases does not exceed $ 10^5 $ ;
- the sum of $ m $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each query, print one integer — the minimum number of coins you have to spend.

## 说明/提示

Let's consider the first two queries in the example from the statement:

- in the first query, you are initially in the city $ 1 $ . You can travel to the closest city (which is the city $ 2 $ ), paying $ 1 $ coin. Then you travel to the closest city (which is the city $ 3 $ ) again, paying $ 1 $ coin. Then you travel to the closest city (which is the city $ 4 $ ) again, paying $ 1 $ coin. In total, you spend $ 3 $ coins to get from the city $ 1 $ to the city $ 4 $ ;
- in the second query, you can use the same way to get from the city $ 1 $ to the city $ 4 $ , and then spend $ 5 $ coins to travel from the city $ 4 $ to the city $ 5 $ .

## 样例 #1

### 输入

```
1
5
0 8 12 15 20
5
1 4
1 5
3 4
3 2
5 1
```

### 输出

```
3
8
1
4
14
```



---

---
title: "Find B"
layout: "post"
diff: 普及/提高-
pid: CF1923C
tag: ['前缀和', '构造']
---

# Find B

## 题目描述

An array $ a $ of length $ m $ is considered good if there exists an integer array $ b $ of length $ m $ such that the following conditions hold:

1. $ \sum\limits_{i=1}^{m} a_i = \sum\limits_{i=1}^{m} b_i $ ;
2. $ a_i \neq b_i $ for every index $ i $ from $ 1 $ to $ m $ ;
3. $ b_i > 0 $ for every index $ i $ from $ 1 $ to $ m $ .

You are given an array $ c $ of length $ n $ . Each element of this array is greater than $ 0 $ .

You have to answer $ q $ queries. During the $ i $ -th query, you have to determine whether the subarray $ c_{l_{i}}, c_{l_{i}+1}, \dots, c_{r_{i}} $ is good.

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ q $ ( $ 1 \le n, q \le 3 \cdot 10^5 $ ) — the length of the array $ c $ and the number of queries.

The second line of each test case contains $ n $ integers $ c_1, c_2, \dots, c_n $ ( $ 1 \le c_i \le 10^9 $ ).

Then $ q $ lines follow. The $ i $ -th of them contains two integers $ l_i $ and $ r_i $ ( $ 1 \le l_i \le r_i \le n $ ) — the borders of the $ i $ -th subarray.

Additional constraints on the input: the sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ ; the sum of $ q $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each query, print YES if the subarray is good. Otherwise, print NO.

You can output each letter of the answer in any case (upper or lower). For example, the strings yEs, yes, Yes, and YES will all be recognized as positive responses.

## 样例 #1

### 输入

```
1
5 4
1 2 1 4 5
1 5
4 4
3 4
1 3
```

### 输出

```
YES
NO
YES
NO
```



---

---
title: "Elections"
layout: "post"
diff: 普及/提高-
pid: CF1978D
tag: ['贪心', '前缀和']
---

# Elections

## 题目描述

Elections are taking place in Berland. There are $ n $ candidates participating in the elections, numbered from $ 1 $ to $ n $ . The $ i $ -th candidate has $ a_i $ fans who will vote for him. Additionally, there are $ c $ people who are undecided about their favorite candidate, let's call them undecided. Undecided people will vote for the candidate with the lowest number.

The candidate who receives the maximum number of votes wins the elections, and if multiple candidates receive the same maximum number of votes, the candidate with the lowest number among them wins.

You found these elections too boring and predictable, so you decided to exclude some candidates from them. If you do not allow candidate number $ i $ to participate in the elections, all $ a_i $ of his fans will become undecided, and will vote for the candidate with the lowest number.

You are curious to find, for each $ i $ from $ 1 $ to $ n $ , the minimum number of candidates that need to be excluded from the elections for candidate number $ i $ to win the elections.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 2 \cdot 10^4 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ c $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 0 \le c \le 10^9 $ ) — the number of candidates in the elections and the number of undecided people.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \le a_i \le 10^9 $ ) — the number of fans for each candidate.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output $ n $ integers, the $ i $ -th of which should be equal to the minimum number of candidates that need to be excluded from the elections for candidate number $ i $ to win.

## 说明/提示

In the first test case:

- If all candidates are allowed, candidate number $ 1 $ will receive $ 3 $ votes ( $ 1 $ undecided person will vote for him), candidate number $ 2 $ will receive $ 0 $ votes, and candidate number $ 3 $ will receive $ 3 $ votes. Therefore, candidate number $ 1 $ wins (he received the same number of votes as candidate $ 3 $ , but his number is lower), so the answer for him is $ 0 $ .
- If candidate number $ 1 $ is not allowed, his $ 2 $ fans will become undecided. Then candidate number $ 2 $ will receive $ 3 $ votes ( $ 3 $ undecided people will vote for him) and candidate number $ 3 $ will receive $ 3 $ votes. Therefore, candidate number $ 2 $ wins (he received the same number of votes as candidate $ 3 $ , but his number is lower), so the answer for him is $ 1 $ .
- If candidates with numbers $ 1 $ and $ 2 $ are not allowed, candidate number $ 3 $ wins, so the answer for him is $ 2 $ .

In the second test case, candidate number $ 1 $ will win if candidate number $ 2 $ is not allowed to participate.

## 样例 #1

### 输入

```
5
3 1
2 0 3
2 3
0 10
5 3
5 4 3 2 1
4 5
3 10 7 1
6 0
2 2 2 3 3 3
```

### 输出

```
0 1 2
1 0
0 1 2 3 4
1 0 2 3
1 1 2 0 4 5
```



---

---
title: "Decode"
layout: "post"
diff: 普及/提高-
pid: CF1996E
tag: ['前缀和']
---

# Decode

## 题目描述

In a desperate attempt to obtain your waifu favorite character, you have hacked into the source code of the game. After days of struggling, you finally find the binary string that encodes the gacha system of the game. In order to decode it, you must first solve the following problem.

You are given a binary string $ s $ of length $ n $ . For each pair of integers $ (l, r) $ $ (1 \leq l \leq r \leq n) $ , count the number of pairs $ (x, y) $ $ (l \leq x \leq y \leq r) $ such that the amount of $ \mathtt{0} $ equals the amount of $ \mathtt{1} $ in the substring $ s_xs_{x+1}...s_y $ .

Output the sum of counts over all possible $ (l, r) $ modulo $ 10^9+7 $ .

## 输入格式

The first line contains $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

Each test case contains a binary string $ s $ ( $ 1 \leq |s| \leq 2 \cdot 10^5 $ ). It is guaranteed $ s $ only contains characters $ \mathtt{0} $ and $ \mathtt{1} $ .

It is guaranteed the sum of $ |s| $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output an integer, the answer modulo $ 10^9+7 $ .

## 样例 #1

### 输入

```
4
0000
01010101
1100111001
11000000111
```

### 输出

```
0
130
147
70
```



---

---
title: "Triple Operations"
layout: "post"
diff: 普及/提高-
pid: CF1999E
tag: ['数学', '前缀和']
---

# Triple Operations

## 题目描述

**题面描述**

Ivy 在黑板上写下了在 $l$ 到 $r$ 之间的所有整数。

在一次运算中，她做了以下操作：

- 在黑板上选出任意两个数字 $x$ 和 $y$ ，将它们擦掉，然后在它们的位置上写下数字 $3x$ 和 $\lfloor \frac{y}{3} \rfloor$ 。(这里的 $\lfloor x\rfloor$ 表示取整，即四舍五入到最接近的整数）。

要使黑板上的所有数字都等于 $0$ ，Ivy 最少需要进行多少次运算？可以证明一定有解。

## 输入格式

第一行包含一个正整数 $t$ ( $1 \leq t \leq 10^4$ )，表示测试用例的数量。

对于每个测试用例，仅一行包含两个正整数 $l$ 和 $r$ ( $1 \leq l <  r \leq 2 \cdot 10^5$ )。

## 输出格式

对于每个测试用例，输出一个整数，即使黑板上的所有数字等于 $0$ 所需的最少操作次数。

**样例解释**

在第一个测试用例中，我们可以执行 $5$ 次操作，如下：

$$
1,2,3 \xrightarrow[x=1,\\,y=2]{} 3,0,3 \xrightarrow[x=0,\\,y=3]{} 1,0,3 \xrightarrow[x=0,\\,y=3]{} 1,0,1 \xrightarrow[x=0,\\,y=1]{} 0,0,1 \xrightarrow[x=0,\\,y=1]{} 0,0,0 .
$$

## 样例 #1

### 输入

```
4
1 3
2 4
199999 200000
19 84
```

### 输出

```
5
6
36
263
```



---

---
title: "Photoshoot for Gorillas"
layout: "post"
diff: 普及/提高-
pid: CF2000E
tag: ['贪心', '前缀和']
---

# Photoshoot for Gorillas

## 题目描述

你非常喜欢大猩猩，于是你决定为它们组织一次拍摄活动。大猩猩生活在丛林中，丛林被表示为一个有 $n$ 行 $m$ 列的网格，有 $w$ 个大猩猩同意参与拍摄，第 $i$ 个大猩猩的身高为 $a_i$ .你希望将所有大猩猩放置在网格的单元格中，并且确保每个单元格中最多只有一只大猩猩。

每种方案的壮观程度等于网格中所有以 $k$ 为边长的子正方形的壮观程度的总和。

子正方形的壮观程度等于其中所有大猩猩的身高的总和。

从所有合适的方案中选出最壮观的方案。

## 输入格式

第一行包含一个整数 $t$ ，表示共有 $t$ 组测试样例。

测试用例的描述如下。

第一行包含三个整数 $n，m，k$，表示网格的尺寸和子正方形的边长。

第二行包含一个整数 $w$，表示大猩猩的数量。

第三行包含 $w$ 个整数 $a_1，a_2，...，a_w$，表示每个大猩猩的身高。

保证所有测试样例中 $n·m$ 的总和不超过 $2·10^5$，$w$ 的总和也不超过 $2·10^5$。

## 输出格式

对于每个测试用例，输出一个整数表示最壮观的方案的壮观程度。

## 样例 #1

### 输入

```
5
3 4 2
9
1 1 1 1 1 1 1 1 1
2 1 1
2
5 7
20 15 7
9
4 1 4 5 6 1 1000000000 898 777
1984 1 1
4
5 4 1499 2004
9 5 5
6
6 7 14 16 16 6
```

### 输出

```
21
12
49000083104
3512
319
```



---

---
title: "Alternating String"
layout: "post"
diff: 普及/提高-
pid: CF2008E
tag: ['贪心', '前缀和']
---

# Alternating String

## 题目描述

# 交替字符串


Sakurako 非常喜欢交替字符串。她把一个由小写拉丁字母组成的字符串 $s$ 称为"交替字符串"，如果字符串中偶数位置的字符都相同，奇数位置的字符都相同，且字符串的长度是偶数。

例如，字符串 `abab` 和 `gg` 是交替的，而字符串 `aba` 和 `ggwp` 则不是。

作为她的好朋友，你决定送她这样一个字符串，但你没能找到一个。幸运的是，你可以对字符串执行两种操作：

1. 选择一个索引 $i$ 并删除字符串中的第  $i$ 个字符，这将使字符串的长度减少 $1$ 。这种操作最多可以执行 $1$ 次；

2. 选择一个索引 $i$ 并将 $s_i$ 替换为任意其他字母。

由于你很着急，你需要确定将字符串变成交替字符串所需的最少操作次数。

## 输入格式

第一行包含一个整数 $t$ $(1 \le t \le 10^4)$。

每个测试用例的第一行包含一个整数$n$ $(1 \le n \le 2\cdot 10^5)$。

每个测试用例的第二行包含一个字符串$s$，由小写拉丁字母组成。

保证所有测试用例中$n$的总和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——将字符串 $s$ 变成交替字符串所需的最少操作次数。

## 说明/提示

对于字符串 `ababa`，你可以删除第一个字符得到 `baba`，这是一个交替字符串。

对于字符串 `acdada`，你可以将前两个字符改为 `d` 和 `a` 得到 `dadada`，这是一个交替字符串。

## 样例 #1

### 输入

```
10
1
a
2
ca
3
aab
5
ababa
6
acdada
9
ejibmyyju
6
bbccbc
6
abacba
5
bcbca
5
dcbdb
```

### 输出

```
1
0
1
1
2
6
2
3
1
1
```



---

---
title: "Firefly's Queries"
layout: "post"
diff: 普及/提高-
pid: CF2009F
tag: ['前缀和']
---

# Firefly's Queries

## 题目描述

Firefly is given an array $ a $ of length $ n $ . Let $ c_i $ denote the $ i $ 'th cyclic shift $ ^{\text{∗}} $ of $ a $ . She creates a new array $ b $ such that $ b = c_1 + c_2 + \dots + c_n $ where $ + $ represents concatenation $ ^{\text{†}} $ .

Then, she asks you $ q $ queries. For each query, output the sum of all elements in the subarray of $ b $ that starts from the $ l $ -th element and ends at the $ r $ -th element, inclusive of both ends.

 $ ^{\text{∗}} $ The $ x $ -th ( $ 1 \leq x \leq n $ ) cyclic shift of the array $ a $ is $ a_x, a_{x+1} \ldots a_n, a_1, a_2 \ldots a_{x - 1} $ . Note that the $ 1 $ -st shift is the initial $ a $ .

 $ ^{\text{†}} $ The concatenation of two arrays $ p $ and $ q $ of length $ n $ (in other words, $ p + q $ ) is $ p_1, p_2, ..., p_n, q_1, q_2, ..., q_n $ .

## 输入格式

The first line contains $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers $ n $ and $ q $ ( $ 1 \leq n, q \leq 2 \cdot 10^5 $ ) — the length of the array and the number of queries.

The following line contains $ n $ integers $ a_1, a_2, ..., a_n $ ( $ 1 \leq a_i \leq 10^6 $ ).

The following $ q $ lines contain two integers $ l $ and $ r $ ( $ 1 \leq l \leq r \leq n^2 $ ) — the left and right bounds of the query.

Note that the large inputs may require the use of 64-bit integers.

It is guaranteed that the sum of $ n $ does not exceed $ 2 \cdot 10^5 $ and the sum of $ q $ does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each query, output the answer on a new line.

## 说明/提示

For the first test case, $ b = [1, 2, 3, 2, 3, 1, 3, 1, 2] $ .

## 样例 #1

### 输入

```
5
3 3
1 2 3
1 9
3 5
8 8
5 5
4 8 3 2 4
1 14
3 7
7 10
2 11
1 25
1 1
6
1 1
5 7
3 1 6 10 4
3 21
6 17
2 2
1 5
1 14
9 15
12 13
5 3
4 9 10 10 1
20 25
3 11
20 22
```

### 输出

```
18
8
1
55
20
13
41
105
6
96
62
1
24
71
31
14
44
65
15
```



---

---
title: "Robert Hood and Mrs Hood"
layout: "post"
diff: 普及/提高-
pid: CF2014D
tag: ['前缀和', '差分']
---

# Robert Hood and Mrs Hood

## 题目描述

Impress thy brother, yet fret not thy mother.



Robin's brother and mother are visiting, and Robin gets to choose the start day for each visitor.

All days are numbered from $ 1 $ to $ n $ . Visitors stay for $ d $ continuous days, all of those $ d $ days must be between day $ 1 $ and $ n $ inclusive.

Robin has a total of $ k $ risky 'jobs' planned. The $ i $ -th job takes place between days $ l_i $ and $ r_i $ inclusive, for $ 1 \le i \le k $ . If a job takes place on any of the $ d $ days, the visit overlaps with this job (the length of overlap is unimportant).

Robin wants his brother's visit to overlap with the maximum number of distinct jobs, and his mother's the minimum.

Find suitable start days for the visits of Robin's brother and mother. If there are multiple suitable days, choose the earliest one.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1\leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case consists of three integers $ n $ , $ d $ , $ k $ ( $ 1 \le n \le 10^5, 1 \le d, k \le n $ ) — the number of total days, duration of the visits, and the number of jobs.

Then follow $ k $ lines of each test case, each with two integers $ l_i $ and $ r_i $ ( $ 1 \le l_i \le r_i \le n $ ) — the start and end day of each job.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output two integers, the best starting days of Robin's brother and mother respectively. Both visits must fit between day $ 1 $ and $ n $ inclusive.

## 说明/提示

In the first test case, the only job fills all $ 2 $ days, both should visit on day $ 1 $ .

In the second test case, day $ 2 $ overlaps with $ 2 $ jobs and day $ 1 $ overlaps with only $ 1 $ .

In the third test case, Robert visits for days $ [1,2] $ , Mrs. Hood visits for days $ [4,5] $ .

## 样例 #1

### 输入

```
6
2 1 1
1 2
4 1 2
1 2
2 4
7 2 3
1 2
1 3
6 7
5 1 2
1 2
3 5
9 2 1
2 8
9 2 4
7 9
4 8
1 3
2 3
```

### 输出

```
1 1
2 1
1 4
1 1
1 1
3 4
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
title: "Beautiful Sequence"
layout: "post"
diff: 普及/提高-
pid: CF2069C
tag: ['数学', '组合数学', '前缀和']
---

# Beautiful Sequence

## 题目描述

我们称一个整数序列为美丽的（beautiful），当且仅当满足以下条件：
- 序列长度至少为 $3$；
- 对于除第一个元素外的每个元素，其左侧存在一个比它小的元素；
- 对于除最后一个元素外的每个元素，其右侧存在一个比它大的元素；

例如，$[1, 4, 2, 4, 7]$ 和 $[1, 2, 4, 8]$ 是美丽的，但 $[1, 2]$、$[2, 2, 4]$ 和 $[1, 3, 5, 3]$ 不是。

注意：子序列是指通过删除原序列中某些元素（不改变剩余元素的顺序）得到的新序列。

给定一个大小为 $n$ 的整数数组 $a$，其中每个元素均为 $1$ 到 $3$ 之间的整数。你的任务是计算数组 $a$ 中美丽子序列的数量。由于答案可能很大，请将其对 $998244353$ 取模后输出。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例的第一行包含一个整数 $n$（$3 \le n \le 2 \cdot 10^5$）。

第二行包含 $n$ 个整数 $a_1, a_2, \dots, a_n$（$1 \le a_i \le 3$）。

输入额外约束：所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——数组 $a$ 中美丽子序列的数量对 $998244353$ 取模后的结果。

## 说明/提示

在示例的第一个测试用例中，以下子序列是美丽的：
- $[a_3, a_4, a_7]$；
- $[a_3, a_5, a_7]$；
- $[a_3, a_4, a_5, a_7]$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
7
3 2 1 2 2 1 3
4
3 1 2 2
3
1 2 3
9
1 2 3 2 1 3 2 2 3
```

### 输出

```
3
0
1
22
```



---

---
title: "Array and GCD"
layout: "post"
diff: 普及/提高-
pid: CF2104D
tag: ['贪心', '素数判断,质数,筛法', '前缀和']
---

# Array and GCD

## 题目描述

给定一个大小为 $n$ 的整数数组 $a$。

你可以执行以下操作任意次数（包括零次）：
- 支付 1 枚硬币并将数组中的任意一个元素增加 $1$（执行此操作时你至少需要有 1 枚硬币）；
- 获得 1 枚硬币并将数组中的任意一个元素减少 $1$。

我们称一个数组是理想的，当且仅当满足以下两个条件：
1. 数组中的每个元素都至少为 $2$；
2. 对于任意两个不同的下标 $i$ 和 $j$（$1 \le i, j \le n$；$i \ne j$），$a_i$ 和 $a_j$ 的最大公约数（GCD）等于 $1$。如果数组元素少于 2 个，则此条件自动满足。

我们称一个数组是美丽的，如果可以通过上述操作将其转换为理想数组，且初始时你没有硬币。如果数组已经是理想的，那么它也是美丽的。

给定的数组不一定是美丽或理想的。你可以从中删除任意数量的元素（包括删除整个数组或不删除任何元素）。你的任务是计算为了使数组变得美丽，最少需要删除多少个元素（可以是零个）。

## 输入格式

第一行包含一个整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 4 \cdot 10^5$）。

第二行包含 $n$ 个整数 $a_1, a_2, \dots, a_n$（$2 \le a_i \le 10^9$）。

输入数据的额外约束：所有测试用例的 $n$ 之和不超过 $4 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一个整数——为了使数组变得美丽，最少需要删除的元素数量（可以是零个）。


## 说明/提示

在第一个样例中，你不需要删除任何元素，因为数组已经是美丽的。可以通过以下操作将其转换为理想数组：$[5, 5, 5] \rightarrow [4, 5, 5] \rightarrow [4, 4, 5] \rightarrow [4, 3, 5]$（最终你会拥有 3 枚硬币）。

在第二个样例中，你需要删除 2 个元素才能使数组变得美丽。如果保留元素 $[2, 3]$ 并删除其他元素，那么给定的数组已经是理想的（因此也是美丽的）。

在第三个样例中，你不需要删除任何元素，因为数组已经是理想的（因此也是美丽的）。

在第四个样例中，数组是美丽的。可以通过以下操作将其转换为理想数组：$[2, 100, 2] \rightarrow [2, 99, 2] \rightarrow [2, 99, 3] \rightarrow [2, 98, 3] \rightarrow [2, 97, 3]$（最终你会拥有 2 枚硬币）。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
3
5 5 5
4
2 3 2 4
1
3
3
2 100 2
5
2 4 2 11 2
```

### 输出

```
0
2
0
0
1
```



---

---
title: "Smilo and Minecraft"
layout: "post"
diff: 普及/提高-
pid: CF2113C
tag: ['贪心', '枚举', '前缀和']
---

# Smilo and Minecraft

## 题目描述

Smilo 在玩 Minecraft！为了准备去打龙，他需要大量的金苹果，所以他需要大量的金子。因此，Smilo 准备下矿。

矿洞是一个 $n\times m$ 的矩形网格，每个格子可能是金矿、石头或空地。Smilo 可以在一个空地点燃炸药，这会将以此空地为中心的边长为 $2k+1$ 的正方形区域夷为平地。如果一个金矿在正方形的内部并且没有和边框相接触，那么它会直接消失；如果金矿在正方形的边框上（在内部并且和正方形的边相接触），Smilo 将会获得这个金子。

求出 Smilo 最多可以获得多少金子。

## 输入格式

多组数据。第一行一个整数 $t(1\le t\le 10^4)$ 表示数据组数。

对于每组数据，第一行三个整数 $n,m,k(1\le n,m,k\le 500)$。\
接下来 $n$ 行，每行一个由 `g`，`#` 和 `.` 构成的长度为 $m$ 的字符串，表示矿洞。`g` 表示金矿，`#` 表示石头，`.` 表示空格。

保证单个测试点中 $\sum nm\le 2.5\times 10^5$。

## 输出格式

对于每组数据，输出一行一个整数表示答案。

## 说明/提示

**样例解释**

对于第一组数据，Smilo 可以在任意空地中引爆炸药获得 $2$ 个金子：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2113C/31cdfd6d4d5bc2d30d1aa78bd3d2c6d2b0fc3eda.png)

对于第二组数据，Smilo 怎么做都不能获得任何金子：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2113C/a0691441b6e186314d109f809a1563824ebb170d.png)

对于第三组数据，Smilo 可以先在左下角的空地中引爆炸药获得 $2$ 个金子，再在左边一个格子引爆炸药获得 $2$ 个金子：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2113C/83af7f606c31f060510f0f11993f3494ca718e49.png)

By @[chenxi2009](/user/1020063)

## 样例 #1

### 输入

```
3
2 3 1
#.#
g.g
2 3 2
#.#
g.g
3 4 2
.gg.
g..#
g##.
```

### 输出

```
2
0
4
```



---

---
title: "Milking cows"
layout: "post"
diff: 普及/提高-
pid: CF383A
tag: ['贪心', '前缀和', '概率论']
---

# Milking cows

## 题目描述

Iahub在农场帮助他的祖父，今天他必须挤牛奶。农场里有$n$只牛左成一排，从左到右编号$1$到$n$。每只牛不是面向左边就是面向右边。当Iahub挤某一只牛的牛奶时，所有看得到这当前只牛的牛都会因为受到惊吓而损失一单位量的牛奶。面向左边的牛可以看到它左边的所有牛（不包括自己），面向右边的牛可以看到它右边的所有牛（不包括自己）。被惊吓过的牛可以再次被惊吓。被挤过奶的牛不会再被惊吓。我们假定每一头牛可以生产无限量的牛奶。

Iahub可以决定挤牛奶的顺序，但他必须每头牛都要挤。Iahub想损失尽可能少的牛奶。请输出最少的牛奶损失量。

## 输入格式

第一行包括一个整数$n(1<=n<=200000)$. 第二行包括n个整数$a_1,a_2...,a_n$。$a_i$是$0$表示牛面向左边，$1$则表示面向右边。

## 输出格式

输出一个整数，即最少的牛奶损失量

在C++中，请不要用%lld分类符来读入或输出64位整型。最好用输出输出流或者%I64D分类符

## 说明/提示

在第一个样例中,Iahub按照下面的顺序可以使得牛奶损失最少：$3,4,2,1$。当他挤牛$3$时，牛$4$会损失$1$单位牛奶。在此之后，没有牛奶损失。

Translated by @Imakf

## 样例 #1

### 输入

```
4
0 0 1 0

```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
1 0 1 0 1

```

### 输出

```
3
```



---

---
title: "Holidays"
layout: "post"
diff: 普及/提高-
pid: CF44C
tag: ['模拟', '前缀和', '差分']
---

# Holidays

## 题目描述

School holidays come in Berland. The holidays are going to continue for $ n $ days. The students of school № $ N $ are having the time of their lives and the IT teacher Marina Sergeyevna, who has spent all the summer busy checking the BSE (Berland State Examination) results, has finally taken a vacation break! Some people are in charge of the daily watering of flowers in shifts according to the schedule. However when Marina Sergeyevna was making the schedule, she was so tired from work and so lost in dreams of the oncoming vacation that she perhaps made several mistakes. In fact, it is possible that according to the schedule, on some days during the holidays the flowers will not be watered or will be watered multiple times. Help Marina Sergeyevna to find a mistake.

## 输入格式

The first input line contains two numbers $ n $ and $ m $ ( $ 1<=n,m<=100 $ ) — the number of days in Berland holidays and the number of people in charge of the watering respectively. The next $ m $ lines contain the description of the duty schedule. Each line contains two integers $ a_{i} $ and $ b_{i} $ ( $ 1<=a_{i}<=b_{i}<=n $ ), meaning that the $ i $ -th person in charge should water the flowers from the $ a_{i} $ -th to the $ b_{i} $ -th day inclusively, once a day. The duty shifts are described sequentially, i.e. $ b_{i}<=a_{i+1} $ for all $ i $ from $ 1 $ to $ n-1 $ inclusively.

## 输出格式

Print "OK" (without quotes), if the schedule does not contain mistakes. Otherwise you have to find the minimal number of a day when the flowers will not be watered or will be watered multiple times, and output two integers — the day number and the number of times the flowers will be watered that day.

## 说明/提示

Keep in mind that in the second sample the mistake occurs not only on the second day, but also on the sixth day, when nobody waters the flowers. However, you have to print the second day, i.e. the day with the minimal number.

## 样例 #1

### 输入

```
10 5
1 2
3 3
4 6
7 7
8 10

```

### 输出

```
OK

```

## 样例 #2

### 输入

```
10 5
1 2
2 3
4 5
7 8
9 10

```

### 输出

```
2 2

```

## 样例 #3

### 输入

```
10 5
1 2
3 3
5 7
7 7
7 10

```

### 输出

```
4 0

```



---

---
title: "Number of Ways"
layout: "post"
diff: 普及/提高-
pid: CF466C
tag: ['枚举', '前缀和']
---

# Number of Ways

## 题目描述

You've got array $ a[1],a[2],...,a[n] $ , consisting of $ n $ integers. Count the number of ways to split all the elements of the array into three contiguous parts so that the sum of elements in each part is the same.

More formally, you need to find the number of such pairs of indices $ i,j $ $ (2<=i<=j<=n-1) $ , that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF466C/6d268bd0e5773093a8b59275245964aa2b1c55f9.png).

## 输入格式

The first line contains integer $ n $ $ (1<=n<=5·10^{5}) $ , showing how many numbers are in the array. The second line contains $ n $ integers $ a[1] $ , $ a[2] $ , ..., $ a[n] $ $ (|a[i]|<=10^{9}) $ — the elements of array $ a $ .

## 输出格式

Print a single integer — the number of ways to split the array into three parts with the same sum.

## 样例 #1

### 输入

```
5
1 2 3 0 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4
0 1 -1 0

```

### 输出

```
1

```

## 样例 #3

### 输入

```
2
4 1

```

### 输出

```
0

```



---

---
title: "Hard Process"
layout: "post"
diff: 普及/提高-
pid: CF660C
tag: ['前缀和']
---

# Hard Process

## 题目描述

给你一个数组，其中有n个元素。每个元素不是0就是1。
现在可以进行k次操作，每次操作可以改变数组中的一个元素（只能改成0或1）。
请你求出操作后最长连续1的序列的长度，并输出操作后的序列。

## 输入格式

第一行输入两个整数n和k ( 1<=n<=3*10^5,0<=k<=n)
第二行包含n个整数。每个整数只存在1或0两种情况。

## 输出格式

第一行为一个整数z，表示最长连续1的序列长度。
第二行包含n个整数，表示操作后的序列。
如果有多个答案，任意输出其中的一种。

## 样例 #1

### 输入

```
7 1
1 0 0 1 1 0 1

```

### 输出

```
4
1 0 0 1 1 1 1

```

## 样例 #2

### 输入

```
10 2
1 0 0 1 0 1 0 1 0 1

```

### 输出

```
5
1 0 0 1 1 1 1 1 0 1

```



---

---
title: "An impassioned circulation of affection"
layout: "post"
diff: 普及/提高-
pid: CF814C
tag: ['二分', '枚举', '前缀和']
---

# An impassioned circulation of affection

## 题目描述

Nadeko's birthday is approaching! As she decorated the room for the party, a long garland of Dianthus-shaped paper pieces was placed on a prominent part of the wall. Brother Koyomi will like it!

Still unsatisfied with the garland, Nadeko decided to polish it again. The garland has $ n $ pieces numbered from $ 1 $ to $ n $ from left to right, and the $ i $ -th piece has a colour $ s_{i} $ , denoted by a lowercase English letter. Nadeko will repaint at most $ m $ of the pieces to give each of them an arbitrary new colour (still denoted by a lowercase English letter). After this work, she finds out all subsegments of the garland containing pieces of only colour $ c $ — Brother Koyomi's favourite one, and takes the length of the longest among them to be the Koyomity of the garland.

For instance, let's say the garland is represented by "kooomo", and Brother Koyomi's favourite colour is "o". Among all subsegments containing pieces of "o" only, "ooo" is the longest, with a length of $ 3 $ . Thus the Koyomity of this garland equals $ 3 $ .

But problem arises as Nadeko is unsure about Brother Koyomi's favourite colour, and has swaying ideas on the amount of work to do. She has $ q $ plans on this, each of which can be expressed as a pair of an integer $ m_{i} $ and a lowercase letter $ c_{i} $ , meanings of which are explained above. You are to find out the maximum Koyomity achievable after repainting the garland according to each plan.

## 输入格式

The first line of input contains a positive integer $ n $ ( $ 1<=n<=1500 $ ) — the length of the garland.

The second line contains $ n $ lowercase English letters $ s_{1}s_{2}...\ s_{n} $ as a string — the initial colours of paper pieces on the garland.

The third line contains a positive integer $ q $ ( $ 1<=q<=200000 $ ) — the number of plans Nadeko has.

The next $ q $ lines describe one plan each: the $ i $ -th among them contains an integer $ m_{i} $ ( $ 1<=m_{i}<=n $ ) — the maximum amount of pieces to repaint, followed by a space, then by a lowercase English letter $ c_{i} $ — Koyomi's possible favourite colour.

## 输出格式

Output $ q $ lines: for each work plan, output one line containing an integer — the largest Koyomity achievable after repainting the garland according to it.

## 说明/提示

In the first sample, there are three plans:

- In the first plan, at most $ 1 $ piece can be repainted. Repainting the "y" piece to become "o" results in "kooomi", whose Koyomity of $ 3 $ is the best achievable;
- In the second plan, at most $ 4 $ pieces can be repainted, and "oooooo" results in a Koyomity of $ 6 $ ;
- In the third plan, at most $ 4 $ pieces can be repainted, and "mmmmmi" and "kmmmmm" both result in a Koyomity of $ 5 $ .

## 样例 #1

### 输入

```
6
koyomi
3
1 o
4 o
4 m

```

### 输出

```
3
6
5

```

## 样例 #2

### 输入

```
15
yamatonadeshiko
10
1 a
2 a
3 a
4 a
5 a
1 b
2 b
3 b
4 b
5 b

```

### 输出

```
3
4
5
7
8
1
2
3
4
5

```

## 样例 #3

### 输入

```
10
aaaaaaaaaa
2
10 b
10 z

```

### 输出

```
10
10

```



---

---
title: "Karen and Coffee"
layout: "post"
diff: 普及/提高-
pid: CF816B
tag: ['前缀和']
---

# Karen and Coffee

## 题目描述

To stay woke and attentive during classes, Karen needs some coffee!

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF816B/84ca24fa194ecce1cb9c3e825b543dfb7809c444.png)Karen, a coffee aficionado, wants to know the optimal temperature for brewing the perfect cup of coffee. Indeed, she has spent some time reading several recipe books, including the universally acclaimed "The Art of the Covfefe".

She knows $ n $ coffee recipes. The $ i $ -th recipe suggests that coffee should be brewed between $ l_{i} $ and $ r_{i} $ degrees, inclusive, to achieve the optimal taste.

Karen thinks that a temperature is admissible if at least $ k $ recipes recommend it.

Karen has a rather fickle mind, and so she asks $ q $ questions. In each question, given that she only wants to prepare coffee with a temperature between $ a $ and $ b $ , inclusive, can you tell her how many admissible integer temperatures fall within the range?

## 输入格式

The first line of input contains three integers, $ n $ , $ k $ ( $ 1<=k<=n<=200000 $ ), and $ q $ ( $ 1<=q<=200000 $ ), the number of recipes, the minimum number of recipes a certain temperature must be recommended by to be admissible, and the number of questions Karen has, respectively.

The next $ n $ lines describe the recipes. Specifically, the $ i $ -th line among these contains two integers $ l_{i} $ and $ r_{i} $ ( $ 1<=l_{i}<=r_{i}<=200000 $ ), describing that the $ i $ -th recipe suggests that the coffee be brewed between $ l_{i} $ and $ r_{i} $ degrees, inclusive.

The next $ q $ lines describe the questions. Each of these lines contains $ a $ and $ b $ , ( $ 1<=a<=b<=200000 $ ), describing that she wants to know the number of admissible integer temperatures between $ a $ and $ b $ degrees, inclusive.

## 输出格式

For each question, output a single integer on a line by itself, the number of admissible integer temperatures between $ a $ and $ b $ degrees, inclusive.

## 说明/提示

In the first test case, Karen knows $ 3 $ recipes.

1. The first one recommends brewing the coffee between $ 91 $ and $ 94 $ degrees, inclusive.
2. The second one recommends brewing the coffee between $ 92 $ and $ 97 $ degrees, inclusive.
3. The third one recommends brewing the coffee between $ 97 $ and $ 99 $ degrees, inclusive.

A temperature is admissible if at least $ 2 $ recipes recommend it.

She asks $ 4 $ questions.

In her first question, she wants to know the number of admissible integer temperatures between $ 92 $ and $ 94 $ degrees, inclusive. There are $ 3 $ : $ 92 $ , $ 93 $ and $ 94 $ degrees are all admissible.

In her second question, she wants to know the number of admissible integer temperatures between $ 93 $ and $ 97 $ degrees, inclusive. There are $ 3 $ : $ 93 $ , $ 94 $ and $ 97 $ degrees are all admissible.

In her third question, she wants to know the number of admissible integer temperatures between $ 95 $ and $ 96 $ degrees, inclusive. There are none.

In her final question, she wants to know the number of admissible integer temperatures between $ 90 $ and $ 100 $ degrees, inclusive. There are $ 4 $ : $ 92 $ , $ 93 $ , $ 94 $ and $ 97 $ degrees are all admissible.

In the second test case, Karen knows $ 2 $ recipes.

1. The first one, "wikiHow to make Cold Brew Coffee", recommends brewing the coffee at exactly $ 1 $ degree.
2. The second one, "What good is coffee that isn't brewed at at least $ 36.3306 $ times the temperature of the surface of the sun?", recommends brewing the coffee at exactly $ 200000 $ degrees.

A temperature is admissible if at least $ 1 $ recipe recommends it.

In her first and only question, she wants to know the number of admissible integer temperatures that are actually reasonable. There are none.

## 样例 #1

### 输入

```
3 2 4
91 94
92 97
97 99
92 94
93 97
95 96
90 100

```

### 输出

```
3
3
0
4

```

## 样例 #2

### 输入

```
2 1 1
1 1
200000 200000
90 100

```

### 输出

```
0

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
title: "Convenient For Everybody"
layout: "post"
diff: 普及/提高-
pid: CF939C
tag: ['前缀和']
---

# Convenient For Everybody

## 题目描述

In distant future on Earth day lasts for $ n $ hours and that's why there are $ n $ timezones. Local times in adjacent timezones differ by one hour. For describing local time, hours numbers from $ 1 $ to $ n $ are used, i.e. there is no time "0 hours", instead of it " $ n $ hours" is used. When local time in the $ 1 $ -st timezone is $ 1 $ hour, local time in the $ i $ -th timezone is $ i $ hours.

Some online programming contests platform wants to conduct a contest that lasts for an hour in such a way that its beginning coincides with beginning of some hour (in all time zones). The platform knows, that there are $ a_{i} $ people from $ i $ -th timezone who want to participate in the contest. Each person will participate if and only if the contest starts no earlier than $ s $ hours 00 minutes local time and ends not later than $ f $ hours 00 minutes local time. Values $ s $ and $ f $ are equal for all time zones. If the contest starts at $ f $ hours 00 minutes local time, the person won't participate in it.

Help platform select such an hour, that the number of people who will participate in the contest is maximum.

## 输入格式

The first line contains a single integer $ n $ ( $ 2<=n<=100000 $ ) — the number of hours in day.

The second line contains $ n $ space-separated integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 1<=a_{i}<=10000 $ ), where $ a_{i} $ is the number of people in the $ i $ -th timezone who want to participate in the contest.

The third line contains two space-separated integers $ s $ and $ f $ ( $ 1<=s&lt;f<=n $ ).

## 输出格式

Output a single integer — the time of the beginning of the contest (in the first timezone local time), such that the number of participants will be maximum possible. If there are many answers, output the smallest among them.

## 说明/提示

In the first example, it's optimal to start competition at $ 3 $ hours (in first timezone). In this case, it will be $ 1 $ hour in the second timezone and $ 2 $ hours in the third timezone. Only one person from the first timezone won't participate.

In second example only people from the third and the fourth timezones will participate.

## 样例 #1

### 输入

```
3
1 2 3
1 3

```

### 输出

```
3

```

## 样例 #2

### 输入

```
5
1 2 3 4 1
1 3

```

### 输出

```
4

```



---

