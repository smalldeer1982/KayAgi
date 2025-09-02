---
title: "Cow and Vacation"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1307F
tag: ['倍增']
---

# Cow and Vacation

## 题目描述

Bessie 正在准备度假。

他所在的个洲有 n 个城市，n-1 条双向道路连接。保证可以从任意一个城市到任意一个城市。

Bessie 考虑了 v 种度假方案，每种方案包括从城市 ai 开始到城市 bi 结束。

已知一共有 r 个城市拥有休息点。Bessie 容易疲倦，并且他不能在不休息的情况下穿越超过 k 条连续道路。有时，他还会因为太想休息而多次穿过同一个城市。

对于每一种旅行方案，Bessie 是否有从出发城市到结束地城市的旅行方式？

## 输入格式

第一行包括三个整数，n，k，r（范围如原题所示）。分别表示城市的数量，Bessie 愿意在不休息的情况下连续通过的最大道路数，休息点的数量。

接下来 n-1 行，每行两个整数写 xi 和 yi（范围如原题所示），表示从 xi 到 yi 有一条双向道路连接。

接下来r行，每行一个数字，表示有休息点的城市，保证每个城市最多出现一遍。

接下来一行一个整数 v（范围如原题所示），表示度假方案数。

接下来v行，每行两个整数 ai 和 bi（范围如原题所示），表示该方案从 ai 开始到城市 bi 结束。

## 输出格式

一共 v 行，表示如果 Bessie 能够按要求到达，输出“YES”，反之输出“NO”。

## 说明/提示

第一个例子的图表如下所示。休息站用红色表示。

对于第一个查询，Bessie 可以按以下顺序访问这些城市：1->2->3。

对于第二个查询，Bessie 可以按以下顺序访问这些城市： 3->2-> 4-> 5。

对于第三个查询，Bessie 无法前往目的地。例如，如果她试图这样旅行：3->2->4->5->6，他在2条以上的道路上旅行而没有休息。

## 样例 #1

### 输入

```
6 2 1
1 2
2 3
2 4
4 5
5 6
2
3
1 3
3 5
3 6
```

### 输出

```
YES
YES
NO
```

## 样例 #2

### 输入

```
8 3 3
1 2
2 3
3 4
4 5
4 6
6 7
7 8
2 5 8
2
7 1
8 1
```

### 输出

```
YES
NO
```



---

---
title: "Hopping Around the Array"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1523H
tag: ['倍增']
---

# Hopping Around the Array

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1523H/e51ba52831aa2bdc46f5ded7e75759c71a41f8c8.png)William really wants to get a pet. Since his childhood he dreamt about getting a pet grasshopper. William is being very responsible about choosing his pet, so he wants to set up a trial for the grasshopper!

The trial takes place on an array $ a $ of length $ n $ , which defines lengths of hops for each of $ n $ cells. A grasshopper can hop around the sells according to the following rule: from a cell with index $ i $ it can jump to any cell with indices from $ i $ to $ i+a_i $ inclusive.

Let's call the  $ k $ -grasshopper value of some array the smallest number of hops it would take a grasshopper to hop from the first cell to the last, but before starting you can select no more than $ k $ cells and remove them from the array. When a cell is removed all other cells are renumbered but the values of $ a_i $ for each cell remains the same. During this the first and the last cells may not be removed.

It is required to process $ q $ queries of the following format: you are given three numbers $ l $ , $ r $ , $ k $ . You are required to find the $ k $ -grasshopper value for an array, which is a subarray of the array $ a $ with elements from $ l $ to $ r $ inclusive.

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 1 \le n, q \le 20000 $ ), the length of the array and the number of queries respectively.

The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le n $ ) – the elements of the array.

The following $ q $ lines contain queries: each line contains three integers $ l $ , $ r $ and $ k $ ( $ 1 \le l \le r \le n $ , $ 0 \le k \le min(30, r-l) $ ), which are the edges of the subarray and the number of the grasshopper value respectively.

## 输出格式

For each query print a single number in a new line — the response to a query.

## 说明/提示

For the second query the process occurs like this: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1523H/c1ccc3788dc1fede7feb02bdd9497a50772396e2.png)

For the third query the process occurs like this: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1523H/0e6c1b078b934e632312b366706afe7addccd69f.png)

## 样例 #1

### 输入

```
9 5
1 1 2 1 3 1 2 1 1
1 1 0
2 5 1
5 9 1
2 8 2
1 9 4
```

### 输出

```
0
2
1
2
2
```



---

---
title: "AmShZ Wins a Bet"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1610G
tag: ['倍增', '哈希 hashing']
---

# AmShZ Wins a Bet

## 题目描述

Right before the UEFA Euro 2020, AmShZ and Safar placed bets on who'd be the champion, AmShZ betting on Italy, and Safar betting on France.

Of course, AmShZ won. Hence, Safar gave him a bracket sequence $ S $ . Note that a bracket sequence is a string made of '(' and ')' characters.

AmShZ can perform the following operation any number of times:

- First, he cuts his string $ S $ into three (possibly empty) contiguous substrings $ A, B $ and $ C $ . Then, he glues them back by using a '(' and a ')' characters, resulting in a new string $ S $ = $ A $ + "(" + $ B $ + ")" + $ C $ .For example, if $ S $ = "))((" and AmShZ cuts it into $ A $ = "", $ B $ = "))", and $ C $ = "((", He will obtain $ S $ = "()))((" as a new string.

After performing some (possibly none) operations, AmShZ gives his string to Keshi and asks him to find the initial string. Of course, Keshi might be able to come up with more than one possible initial string. Keshi is interested in finding the lexicographically smallest possible initial string.

Your task is to help Keshi in achieving his goal.

A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 输入格式

The only line of input contains a single string $ S $ — the string after the operations $ (1\le |S|\le 3 \cdot 10^5) $ .

It is guaranteed that the first character of $ S $ is ')'.

## 输出格式

Print the lexicographically smallest possible initial string before operations.

## 说明/提示

In the first sample, you can transform ")((())))" into ")(()(())))" by splitting it into ")(", empty string, and "(())))". It can be shown that this is the lexicographically smallest possible initial string

## 样例 #1

### 输入

```
)(()(())))
```

### 输出

```
)((())))
```



---

---
title: "Replace"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1707E
tag: ['倍增']
---

# Replace

## 题目描述

给定一个长为 $n$ 的序列 $a_1,\ldots,a_n$，其中对于任意的 $i$ 满足 $1 \leq a_i \leq n$。

定义一个二元组函数如下：
$$f((l,r))=(\min\{a_l,\ldots,a_r\},\max\{a_l,\ldots,a_r\})(l \leq r)$$

你需要回答 $q$ 次询问，每次给定 $(l_i,r_i)$，问其最少经过多少次 $f$ 的调用（即 $(l,r) \rightarrow f((l,r))$）使得 $(l_i,r_i)$ 变成 $(1,n)$，若无解请输出 `-1`。

## 输入格式

第一行包含两个整数 $n,q(1 \leq n,q \leq 10^5)$，表示序列长度和询问次数。

第二行包含 $n$ 个整数 $a_i(1 \leq a_i \leq n)$，表示序列 $a$。

接下来 $q$ 行每行两个整数 $l_i,r_i(1 \leq l_i \leq r_i \leq n)$，表示每组询问。

## 输出格式

对每一个询问，输出其最小次数，或无解输出 `-1`。

### 样例解释

第一个样例中，$a=\{2,5,4,1,3\}$。

对于第一个询问，$(4,4) \rightarrow (1,1) \rightarrow (2,2) \rightarrow (5,5) \rightarrow (3,3) \rightarrow (4,4) \rightarrow \cdots$，故无解。

对于第二个询问，已经有 $(l_i,r_i)=(1,n)$，需要 $0$ 次。

对于第三个询问，$(1,4) \rightarrow (1,5)$，需要 $1$ 次。

对于第四个询问，$(3,5) \rightarrow (1,4) \rightarrow (1,5)$，需要 $2$ 次。

对于第五个询问，$(4,5) \rightarrow (1,3) \rightarrow (2,5) \rightarrow (1,5)$，需要 $3$ 次。

对于第六个询问，$(2,3) \rightarrow (4,5) \rightarrow (1,3) \rightarrow (2,5) \rightarrow (1,5)$，需要 $4$ 次。

## 样例 #1

### 输入

```
5 6
2 5 4 1 3
4 4
1 5
1 4
3 5
4 5
2 3
```

### 输出

```
-1
0
1
2
3
4
```

## 样例 #2

### 输入

```
6 3
2 3 4 6 1 2
5 6
2 5
2 3
```

### 输出

```
5
1
3
```

## 样例 #3

### 输入

```
5 3
3 2 2 4 1
2 5
1 3
1 5
```

### 输出

```
-1
-1
0
```



---

---
title: "Segment Covering"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1774G
tag: ['倍增', '最近公共祖先 LCA', '组合数学', '容斥原理']
---

# Segment Covering

## 题目描述

ChthollyNotaSeniorious gives DataStructures a number axis with $ m $ distinct segments on it. Let $ f(l,r) $ be the number of ways to choose an even number of segments such that the union of them is exactly $ [l,r] $ , and $ g(l,r) $ be the number of ways to choose an odd number of segments such that the union of them is exactly $ [l,r] $ .

ChthollyNotaSeniorious asked DataStructures $ q $ questions. In each query, ChthollyNotaSeniorious will give DataStructures two numbers $ l, r $ , and now he wishes that you can help him find the value $ f(l,r)-g(l,r) $ modulo $ 998\,244\,353 $ so that he wouldn't let her down.

## 输入格式

The first line of input contains two integers $ m $ ( $ 1 \leq m \leq 2 \cdot 10^5 $ ) and $ q $ ( $ 1 \leq q \leq 2 \cdot 10^5 $ ) — the number of segments and queries, correspondingly.

The $ i $ -th of the next $ m $ lines contains two integers $ x_i $ and $ y_i $ ( $ 1 \leq x_i < y_i \leq 10^9 $ ), denoting a segment $ [x_i, y_i] $ .

It is guaranteed that all segments are distinct. More formally, there do not exist two numbers $ i, j $ with $ 1 \le i < j \le m $ such that $ x_i = x_j $ and $ y_i = y_j $ .

The $ i $ -th of the next $ q $ lines contains two integers $ l_i $ and $ r_i $ ( $ 1 \leq l_i < r_i \leq 10^9 $ ), describing a query.

## 输出格式

For each query, output a single integer — $ f(l_i,r_i)-g(l_i,r_i) $ modulo $ 998\,244\,353 $ .

## 说明/提示

In the first query, we have to find $ f(1, 4) - g(1, 4) $ . The only subset of segments with union $ [1, 4] $ is $ \{[1, 3], [2, 4]\} $ , so $ f(1, 4) = 1, g(1, 4) = 0 $ .

In the second query, we have to find $ f(1, 5) - g(1, 5) $ . The only subsets of segments with union $ [1, 5] $ are $ \{[1, 3], [2, 4], [3, 5]\} $ and $ \{[1, 3], [3, 5]\} $ , so $ f(1, 5) = 1, g(1, 5) = 1 $ .

## 样例 #1

### 输入

```
4 2
1 3
4 6
2 4
3 5
1 4
1 5
```

### 输出

```
1
0
```



---

---
title: "Gasoline prices"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1801E
tag: ['倍增', '并查集']
---

# Gasoline prices

## 题目描述

Berland — is a huge country consisting of $ n $ cities. The road network of Berland can be represented as a root tree, that is, there is only $ n - 1 $ road in the country, and you can get from any city to any other exactly one way, if you do not visit any city twice. For the convenience of representing the country, for each city $ i $ , the city $ p_i $ is fixed, equal to the first city to which you need to go from the city $ i $ to get to the city $ 1 $ . In other words, the city $ p_i $ is equal to the ancestor of the city $ i $ if the tree is hung for the city $ 1 $ .There is one gas station in each city of Berland. Gas stations have special pricing, and for each gas station there is a fixed range of prices for which they are ready to sell gasoline. A gas station in the city with the number $ i $ is ready to sell gasoline at any price from $ l_i $ to $ r_i $ inclusive.

The King of Berland — is an exemplary family man, and for $ m $ years, two sons were born to him every year. The king's children have been involved in public affairs since early childhood, and at the end of each year they check the honesty of gasoline prices. From birth, the king's children, who are born in the year $ i $ , are responsible for checking gasoline prices on the ways from the city of $ a_i $ to the city of $ b_i $ and from the city of $ c_i $ to the city of $ d_i $ , respectively.

The check is as follows: both children simultaneously start their journey from the cities $ a_i $ and $ c_i $ , respectively. The first son of the king, born in the year $ i $ , moves along the path from the city $ a_i $ to the city $ b_i $ , and the second — from the city $ c_i $ to the city $ d_i $ . Children check that the price of gasoline in the city of $ a_i $ coincides with the price of gasoline in the city of $ c_i $ . Next, they check that the price of gasoline in the second city on the way from $ a_i $ to $ b_i $ coincides with the price in the second city on the way from $ c_i $ to $ d_i $ . Then they repeat the same thing for a couple of third cities on their paths and so on. At the end, they check that the price of gasoline in the city of $ b_i $ coincides with the price of gasoline in the city of $ d_i $ . It is guaranteed that the length of the path from the city $ a_i $ to the city $ b_i $ coincides with the length of the path from the city $ c_i $ to the city $ d_i $ .

Gas stations must strictly obey the laws, and therefore all checks of gasoline prices should not reveal violations. Help Berland gas stations find out how many ways they can set gasoline prices for $ m $ years. In other words, for each $ i $ from $ 1 $ to $ m $ , calculate how many ways you can set gasoline prices at all gas stations so that after the birth of the first $ i $ pairs of the king's children, all their checks did not reveal violations, and at any gas station the price was in the acceptable price range. Since the number of such methods can be large, calculate the answer modulo $ 10^9 + 7 $ .

## 输入格式

The first line contains a single integer $ n $ ( $ 1 \le n \le 200\,000 $ ) — the number of cities in Berland.

The second line contains $ (n - 1) $ numbers $ p_2,\ p_3,\ p_4,\ \ldots,\ p_n $ ( $ 1 \le p_i \le n $ ), where $ p_i $ denotes the number of the next city on the way from city $ i $ to city $ 1 $ .

In each of the following lines, two integers are given $ l_i $ and $ r_i $ ( $ 1 \le l_i \le r_i < 10^9+7 $ ), specifying the acceptable range of prices at the gas station number $ i $ .

The following line contains a single integer $ m $ ( $ 1 \le m \le 200\,000 $ ) — the number of years during which two sons were born to the king.

In each of the following $ m $ lines, four integers are given $ a_i $ , $ b_i $ , $ c_i $ and $ d_i $ ( $ 1 \le a_i, b_i, c_i, d_i \le n $ ), specifying two paths on which the king's children will check gasoline prices, born in the year $ i $ . It is guaranteed that the length of the path between the cities $ a_i $ and $ b_i $ is equal to the length of the path between the cities $ c_i $ and $ d_i $ .

## 输出格式

In $ m $ lines, print one number each. The number in the $ i $ line should be equal to the number of ways to set gasoline prices in all cities so that the king's children born in the years up to and including $ i $ do not reveal violations in inspections. Output the numbers modulo $ 10^9 + 7 $ .

## 说明/提示

Consider the first example.

After the birth of the first two sons, the prices in the cities of $ 1 $ and $ 2 $ should be equal. In total, there are 2 ways to choose the same gasoline price for the cities of $ 1 $ and $ 2 $ so that it falls within the acceptable price range for these cities. So, there are only ways to set gasoline prices: $ 2 \cdot 3 \cdot 3 \cdot 1 = 18 $ .

The second pair of sons will check the prices on the paths $ 1 - 2 $ and $ 2 - 1 $ . This means that gasoline prices in the cities of $ 1 $ and $ 2 $ must match, which is already being done. Therefore, after the birth of the second pair of sons, the answer did not change in any way.

The third pair of sons will check the prices on the tracks $ 3 - 1 - 2 - 4 $ and $ 4 - 2 - 1 - 3 $ . Then the price of non-gasoline in the city of $ 3 $ should be equal to the price in the city of $ 4 $ , and the price in the city of $ 1 $ should be equal to the price in the city of $ 2 $ . Prices in the cities of $ 1 $ and $ 2 $ are already the same. For the cities of $ 3 $ and $ 4 $ , there are 2 ways to choose the same price for gasoline so that it falls within the acceptable price range for these cities. So, there are only ways to set gasoline prices: $ 2 \cdot 2 \cdot 1 = 4 $ . The fourth pair of sons will check the prices on the tracks $ 3 - 1 - 2 - 4 $ and $ 3 - 1 - 2 - 5 $ . This means that the prices in the cities of $ 4 $ and $ 5 $ should be equal, and since the prices in the cities of $ 3 $ and $ 4 $ already coincide, then in the cities of $ 3 $ , $ 4 $ and $ 5 $ there should be the same price for gasoline. The price of gasoline in the city of $ 3 $ should be no more than 3, and the price of gasoline in the city of $ 5 $ should be no less than 4. So, after the birth of the fourth pair of sons, there are no ways to set gasoline prices so that all checks are carried out and prices are in the required ranges.

## 样例 #1

### 输入

```
5
1 1 2 2
2 4
1 3
1 3
2 4
4 4
4
1 1 2 2
1 2 2 1
3 4 4 3
3 4 3 5
```

### 输出

```
18
18
4
0
```

## 样例 #2

### 输入

```
8
1 2 3 4 5 8 6
3 7
2 6
3 8
5 10
5 8
2 9
3 8
6 8
4
1 3 7 6
4 1 5 7
1 7 7 1
1 8 2 7
```

### 输出

```
720
120
120
1
```



---

