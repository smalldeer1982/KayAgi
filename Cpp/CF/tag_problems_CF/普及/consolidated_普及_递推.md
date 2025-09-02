---
title: "Intense Heat"
layout: "post"
diff: 普及/提高-
pid: CF1003C
tag: ['递推']
---

# Intense Heat

## 题目描述

给定一个含有 $n$ 个数的数组，以及 $k$，求所有长度大于等于 $k$ 的子串的平均数最大值。

## 输入格式

第一行两个整数，表示 $n$ 和 $k$。

第二行 $n$ 个整数，表示给定的数组 $a_1,a_2,...,a_n$。

## 输出格式

一行一个小数（保留到小数点后至少 6 位），表示答案。

## 样例 #1

### 输入

```
4 3
3 4 1 2

```

### 输出

```
2.666666666666667

```



---

---
title: "New Year Ratings Change"
layout: "post"
diff: 普及/提高-
pid: CF379C
tag: ['递推', '排序', '期望']
---

# New Year Ratings Change

## 题目描述

One very well-known internet resource site (let's call it X) has come up with a New Year adventure. Specifically, they decided to give ratings to all visitors.

There are $ n $ users on the site, for each user we know the rating value he wants to get as a New Year Present. We know that user $ i $ wants to get at least $ a_{i} $ rating units as a present.

The X site is administered by very creative and thrifty people. On the one hand, they want to give distinct ratings and on the other hand, the total sum of the ratings in the present must be as small as possible.

Help site X cope with the challenging task of rating distribution. Find the optimal distribution.

## 输入格式

The first line contains integer $ n $ $ (1<=n<=3·10^{5}) $ — the number of users on the site. The next line contains integer sequence $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=10^{9}) $ .

## 输出格式

Print a sequence of integers $ b_{1},b_{2},...,b_{n} $ . Number $ b_{i} $ means that user $ i $ gets $ b_{i} $ of rating as a present. The printed sequence must meet the problem conditions.

If there are multiple optimal solutions, print any of them.

## 样例 #1

### 输入

```
3
5 1 1

```

### 输出

```
5 1 2

```

## 样例 #2

### 输入

```
1
1000000000

```

### 输出

```
1000000000

```



---

---
title: "Bear and Blocks"
layout: "post"
diff: 普及/提高-
pid: CF573B
tag: ['递推', '线段树', '线性递推']
---

# Bear and Blocks

## 题目描述

Limak is a little bear who loves to play. Today he is playing by destroying block towers. He built $ n $ towers in a row. The $ i $ -th tower is made of $ h_{i} $ identical blocks. For clarification see picture for the first sample.

Limak will repeat the following operation till everything is destroyed.

Block is called internal if it has all four neighbors, i.e. it has each side (top, left, down and right) adjacent to other block or to the floor. Otherwise, block is boundary. In one operation Limak destroys all boundary blocks. His paws are very fast and he destroys all those blocks at the same time.

Limak is ready to start. You task is to count how many operations will it take him to destroy all towers.

## 输入格式

The first line contains single integer $ n $ ( $ 1<=n<=10^{5} $ ).

The second line contains $ n $ space-separated integers $ h_{1},h_{2},...,h_{n} $ ( $ 1<=h_{i}<=10^{9}) $ — sizes of towers.

## 输出格式

Print the number of operations needed to destroy all towers.

## 说明/提示

The picture below shows all three operations for the first sample test. Each time boundary blocks are marked with red color.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF573B/256df13c1ef1192f2e98a72ff5ba9bb98f4ceade.png) After first operation there are four blocks left and only one remains after second operation. This last block is destroyed in third operation.

## 样例 #1

### 输入

```
6
2 1 4 6 2 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
7
3 3 3 1 3 3 3

```

### 输出

```
2

```



---

---
title: "Tennis Championship"
layout: "post"
diff: 普及/提高-
pid: CF735C
tag: ['贪心', '递推']
---

# Tennis Championship

## 题目描述

Famous Brazil city Rio de Janeiro holds a tennis tournament and Ostap Bender doesn't want to miss this event. There will be $ n $ players participating, and the tournament will follow knockout rules from the very first game. That means, that if someone loses a game he leaves the tournament immediately.

Organizers are still arranging tournament grid (i.e. the order games will happen and who is going to play with whom) but they have already fixed one rule: two players can play against each other only if the number of games one of them has already played differs by no more than one from the number of games the other one has already played. Of course, both players had to win all their games in order to continue participating in the tournament.

Tournament hasn't started yet so the audience is a bit bored. Ostap decided to find out what is the maximum number of games the winner of the tournament can take part in (assuming the rule above is used). However, it is unlikely he can deal with this problem without your help.

## 输入格式

The only line of the input contains a single integer $ n $ ( $ 2<=n<=10^{18} $ ) — the number of players to participate in the tournament.

## 输出格式

Print the maximum number of games in which the winner of the tournament can take part.

## 说明/提示

In all samples we consider that player number $ 1 $ is the winner.

In the first sample, there would be only one game so the answer is $ 1 $ .

In the second sample, player $ 1 $ can consequently beat players $ 2 $ and $ 3 $ .

In the third sample, player $ 1 $ can't play with each other player as after he plays with players $ 2 $ and $ 3 $ he can't play against player $ 4 $ , as he has $ 0 $ games played, while player $ 1 $ already played $ 2 $ . Thus, the answer is $ 2 $ and to achieve we make pairs $ (1,2) $ and $ (3,4) $ and then clash the winners.

## 样例 #1

### 输入

```
2

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3

```

### 输出

```
2

```

## 样例 #3

### 输入

```
4

```

### 输出

```
2

```

## 样例 #4

### 输入

```
10

```

### 输出

```
4

```



---

