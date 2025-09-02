---
title: "Counting Prefixes"
layout: "post"
diff: 省选/NOI-
pid: CF1919E
tag: ['动态规划 DP', '欧拉回路']
---

# Counting Prefixes

## 题目描述

There is a hidden array $ a $ of size $ n $ consisting of only $ 1 $ and $ -1 $ . Let $ p $ be the prefix sums of array $ a $ . More formally, $ p $ is an array of length $ n $ defined as $ p_i = a_1 + a_2 + \ldots + a_i $ . Afterwards, array $ p $ is sorted in non-decreasing order. For example, if $ a = [1, -1, -1, 1, 1] $ , then $ p = [1, 0, -1, 0, 1] $ before sorting and $ p = [-1, 0, 0, 1, 1] $ after sorting.

You are given the prefix sum array $ p $ after sorting, but you do not know what array $ a $ is. Your task is to count the number of initial arrays $ a $ such that the above process results in the given sorted prefix sum array $ p $ . As this number can be large, you are only required to find it modulo $ 998\,244\,353 $ .

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases. The description of the test cases follows.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 5000 $ ) — the size of the hidden array $ a $ .

The second line of each test case contains $ n $ integers $ p_1, p_2, \ldots, p_n $ ( $ |p_i| \le n $ ) — the $ n $ prefix sums of $ a $ sorted in non-decreasing order.

It is guaranteed that $ p_1 \le p_2 \le \ldots \le p_n $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 5000 $ .

## 输出格式

For each test case, output the answer modulo $ 998\,244\,353 $ .

## 说明/提示

In the first two test cases, the only possible arrays $ a $ for $ n = 1 $ are $ a = [1] $ and $ a = [-1] $ . Their respective sorted prefix sum arrays $ p $ are $ p = [1] $ and $ p = [-1] $ . Hence, there is no array $ a $ that can result in the sorted prefix sum array $ p = [0] $ and there is exactly $ 1 $ array $ a $ that can result in the sorted prefix sum array $ p = [1] $ .

In the third test case, it can be proven that there is no array $ a $ that could result in the sorted prefix sum array $ p = [-1, 1, 2] $ .

In the fourth test case, the $ 3 $ possible arrays $ a $ that could result in the sorted prefix sum array $ p = [-1, 0, 0, 1, 1] $ are:

- $ a = [1, -1, 1, -1, -1] $ . The prefix sum array before sorting is $ p = [1, 0, 1, 0, -1] $ , which after sorting gives $ p = [-1, 0, 0, 1, 1] $ .
- $ a = [1, -1, -1, 1, 1] $ . The prefix sum array before sorting is $ p = [1, 0, -1, 0, 1] $ , which after sorting gives $ p = [-1, 0, 0, 1, 1] $ .
- $ a = [-1, 1, 1, -1, 1] $ . The prefix sum array before sorting is $ p = [-1, 0, 1, 0, 1] $ , which after sorting gives $ p = [-1, 0, 0, 1, 1] $ .

For the fifth test case, the only possible array $ a $ that could result in the sorted prefix sum array $ p = [-4, -3, -3, -2, -1] $ is $ a = [-1, -1, -1, -1, 1] $ .

## 样例 #1

### 输入

```
5
1
0
1
1
3
-1 1 2
5
-1 0 0 1 1
5
-4 -3 -3 -2 -1
```

### 输出

```
0
1
0
3
1
```



---

---
title: "Two Paths"
layout: "post"
diff: 省选/NOI-
pid: CF36E
tag: ['图论', '连通块', '欧拉回路']
---

# Two Paths

## 题目背景

注意这题要加上这个：

```
freopen("input.txt","r",stdin);
freopen("output.txt","w",stdout);
```

## 题目描述

Once archaeologists found $ m $ mysterious papers, each of which had a pair of integers written on them. Ancient people were known to like writing down the indexes of the roads they walked along, as « $ a $ $ b $ » or « $ b $ $ a $ », where $ a,b $ are the indexes of two different cities joint by the road . It is also known that the mysterious papers are pages of two travel journals (those days a new journal was written for every new journey).

During one journey the traveler could walk along one and the same road several times in one or several directions but in that case he wrote a new entry for each time in his journal. Besides, the archaeologists think that the direction the traveler took on a road had no effect upon the entry: the entry that looks like « $ a $ $ b $ » could refer to the road from $ a $ to $ b $ as well as to the road from $ b $ to $ a $ .

The archaeologists want to put the pages in the right order and reconstruct the two travel paths but unfortunately, they are bad at programming. That’s where you come in. Go help them!

## 输入格式

The first input line contains integer $ m $ ( $ 1<=m<=10000 $ ). Each of the following $ m $ lines describes one paper. Each description consists of two integers $ a,b $ ( $ 1<=a,b<=10000 $ , $ a≠b $ ).

## 输出格式

In the first line output the number $ L_{1} $ . That is the length of the first path, i.e. the amount of papers in its description. In the following line output $ L_{1} $ space-separated numbers — the indexes of the papers that describe the first path. In the third and fourth lines output similarly the length of the second path $ L_{2} $ and the path itself. Both paths must contain at least one road, i.e. condition $ L_{1}&gt;0 $ and $ L_{2}&gt;0 $ must be met. The papers are numbered from $ 1 $ to $ m $ according to the order of their appearance in the input file. The numbers should be output in the order in which the traveler passed the corresponding roads. If the answer is not unique, output any.

If it’s impossible to find such two paths, output «-1».

Don’t forget that each paper should be used exactly once, i.e $ L_{1}+L_{2}=m $ .

## 样例 #1

### 输入

```
2
4 5
4 3

```

### 输出

```
1
2 
1
1

```

## 样例 #2

### 输入

```
1
1 2

```

### 输出

```
-1

```



---

---
title: "Mike and Fish"
layout: "post"
diff: 省选/NOI-
pid: CF547D
tag: ['图论', '欧拉回路', '二分图']
---

# Mike and Fish

## 题目描述

As everyone knows, bears love fish. But Mike is a strange bear; He hates fish! The even more strange thing about him is he has an infinite number of blue and red fish.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF547D/031dc6fdab66492c31079b30a48004c3918930a2.png)He has marked $ n $ distinct points in the plane. $ i $ -th point is point $ (x_{i},y_{i}) $ . He wants to put exactly one fish in each of these points such that the difference between the number of red fish and the blue fish on each horizontal or vertical line is at most 1.

He can't find a way to perform that! Please help him.

## 输入格式

The first line of input contains integer $ n $ ( $ 1<=n<=2×10^{5} $ ).

The next $ n $ lines contain the information about the points, $ i $ -th line contains two integers $ x_{i} $ and $ y_{i} $ ( $ 1<=x_{i},y_{i}<=2×10^{5} $ ), the $ i $ -th point coordinates.

It is guaranteed that there is at least one valid answer.

## 输出格式

Print the answer as a sequence of $ n $ characters 'r' (for red) or 'b' (for blue) where $ i $ -th character denotes the color of the fish in the $ i $ -th point.

## 样例 #1

### 输入

```
4
1 1
1 2
2 1
2 2

```

### 输出

```
brrb

```

## 样例 #2

### 输入

```
3
1 1
1 2
2 1

```

### 输出

```
brr

```



---

