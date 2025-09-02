---
title: "Buns"
layout: "post"
diff: 普及/提高-
pid: CF106C
tag: ['背包 DP']
---

# Buns

## 题目描述

Lavrenty, a baker, is going to make several buns with stuffings and sell them.

Lavrenty has $ n $ grams of dough as well as $ m $ different stuffing types. The stuffing types are numerated from 1 to $ m $ . Lavrenty knows that he has $ a_{i} $ grams left of the $ i $ -th stuffing. It takes exactly $ b_{i} $ grams of stuffing $ i $ and $ c_{i} $ grams of dough to cook a bun with the $ i $ -th stuffing. Such bun can be sold for $ d_{i} $ tugriks.

Also he can make buns without stuffings. Each of such buns requires $ c_{0} $ grams of dough and it can be sold for $ d_{0} $ tugriks. So Lavrenty can cook any number of buns with different stuffings or without it unless he runs out of dough and the stuffings. Lavrenty throws away all excess material left after baking.

Find the maximum number of tugriks Lavrenty can earn.

## 输入格式

The first line contains $ 4 $ integers $ n $ , $ m $ , $ c_{0} $ and $ d_{0} $ ( $ 1<=n<=1000 $ , $ 1<=m<=10 $ , $ 1<=c_{0},d_{0}<=100 $ ). Each of the following $ m $ lines contains $ 4 $ integers. The $ i $ -th line contains numbers $ a_{i} $ , $ b_{i} $ , $ c_{i} $ and $ d_{i} $ ( $ 1<=a_{i},b_{i},c_{i},d_{i}<=100 $ ).

## 输出格式

Print the only number — the maximum number of tugriks Lavrenty can earn.

## 说明/提示

To get the maximum number of tugriks in the first sample, you need to cook 2 buns with stuffing 1, 4 buns with stuffing 2 and a bun without any stuffing.

In the second sample Lavrenty should cook 4 buns without stuffings.

## 样例 #1

### 输入

```
10 2 2 1
7 3 2 100
12 3 1 10

```

### 输出

```
241
```

## 样例 #2

### 输入

```
100 1 25 50
15 5 20 10

```

### 输出

```
200
```



---

---
title: "Cut Ribbon"
layout: "post"
diff: 普及/提高-
pid: CF189A
tag: ['背包 DP']
---

# Cut Ribbon

## 题目描述

给一长度为n的缎带，要求将其剪成若干长度为a,b,c的缎带，且缎带数量尽可能多。

## 输入格式

输入仅一行，四个正整数n,a,b,c(n,a,b,c≤4000)。

## 输出格式

输出仅一行，即缎带数量的最大值。

## 样例 #1

### 输入

```
5 5 3 2

```

### 输出

```
2

```

## 样例 #2

### 输入

```
7 5 5 2

```

### 输出

```
2

```



---

---
title: "Elimination"
layout: "post"
diff: 普及/提高-
pid: CF417A
tag: ['枚举', '背包 DP']
---

# Elimination

## 题目描述

The finalists of the "Russian Code Cup" competition in 2214 will be the participants who win in one of the elimination rounds.

The elimination rounds are divided into main and additional. Each of the main elimination rounds consists of $ c $ problems, the winners of the round are the first $ n $ people in the rating list. Each of the additional elimination rounds consists of $ d $ problems. The winner of the additional round is one person. Besides, $ k $ winners of the past finals are invited to the finals without elimination.

As a result of all elimination rounds at least $ n·m $ people should go to the finals. You need to organize elimination rounds in such a way, that at least $ n·m $ people go to the finals, and the total amount of used problems in all rounds is as small as possible.

## 输入格式

The first line contains two integers $ c $ and $ d $ ( $ 1<=c,d<=100 $ ) — the number of problems in the main and additional rounds, correspondingly. The second line contains two integers $ n $ and $ m $ ( $ 1<=n,m<=100 $ ). Finally, the third line contains an integer $ k $ ( $ 1<=k<=100 $ ) — the number of the pre-chosen winners.

## 输出格式

In the first line, print a single integer — the minimum number of problems the jury needs to prepare.

## 样例 #1

### 输入

```
1 10
7 2
1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2 2
2 1
2

```

### 输出

```
0

```



---

---
title: "Arpa's weak amphitheater and Mehrdad's valuable"
layout: "post"
diff: 普及/提高-
pid: CF741B
tag: ['并查集', '背包 DP']
---

# Arpa's weak amphitheater and Mehrdad's valuable

## 题目描述

有 $n$ 个人 $(1\le n\le1000)$。每个人有一个重量 $w_i(1\le w_i\le 1000)$ 和一个魅力值 $b_i(1\le b_i\le 10^6)$。 $n$ 个人之间有 $m(1\le m\le\min(\frac{n\times(n-1)}{2}, 10^5))$ 个关系。第 $i$ 个关系由两个数字 $x_i$ 和 $y_i$ 组成，表示第 $x_i$ 个人和第 $y_i$ 个人是朋友，朋友关系是双向的。

已知若 $a$ 和 $b$ 是朋友，$b$ 和 $c$ 是朋友，则 $a$ 和 $c$ 是朋友。 现在 Mehrdad 要邀请一些人来到派对，使这些人的重量总和不超过 $w\ (1\le w\le1000)$，且魅力值总和尽量大。同一个朋友圈里的人，只能邀请其中的一个人，或者全部人，或者一个人也不邀请。

## 输入格式

第一行，三个整数 $n,m,w$

第二行，$n$ 个整数 $w_1,w_2,\cdots,w_n$

第三行，$n$ 个整数 $b_1,b_2,\cdots,b_n$

接下来 $m$ 行，每行表示一个关系，第 $i$ 行有两个整数 $x_i$ 和 $y_i$。每一组朋友关系都是不同的。

## 输出格式

一行，表示最大的魅力值总和。

## 样例 #1

### 输入

```
3 1 5
3 2 5
2 4 2
1 2

```

### 输出

```
6

```

## 样例 #2

### 输入

```
4 2 11
2 4 6 6
6 4 2 1
1 2
2 3

```

### 输出

```
7

```



---

