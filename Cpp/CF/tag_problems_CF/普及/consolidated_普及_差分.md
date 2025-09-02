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
title: "Two TVs"
layout: "post"
diff: 普及/提高-
pid: CF845C
tag: ['差分']
---

# Two TVs

## 题目描述

Polycarp 很喜欢看电视。

他写下了他今天所有感兴趣的共   $n\,(1 \le n \le 2 \times 10^5)$ 个电视节目。其中第   $i$ 个电视节目在   $l_i$ 时开始，  $r_i$ 时结束。  $\,(0 \le l_i, r_i \le 10^9)$

Polycarp 有两个电视。他可以同时在两台电视上看两种不同的节目，但他不能在一台电视上同时看两个不同的节目。如果一个节目结束时另一个节目刚好开始，则他不能在一台电视上看这两个节目。他想看完这   $n$ 个节目，请问两台电视足够吗？

## 输入格式

第一行一个正整数   $n$ 表示电视节目个数。

接下来   $n$ 行每行两个自然数   $l_i, r_i$，表示第   $i$ 个节目开始和结束的时间。

## 输出格式

一行一个字符串，如果 Polycarp 能用两台电视看完所有节目，输出 `YES`，否则输出 `NO`。```

## 样例 #1

### 输入

```
3
1 2
2 3
4 5

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
4
1 2
2 3
2 3
1 2

```

### 输出

```
NO

```



---

