---
title: "Points"
layout: "post"
diff: 省选/NOI-
pid: CF19D
tag: ['线段树', '递归', '离散化']
---

# Points

## 题目描述

Pete and Bob invented a new interesting game. Bob takes a sheet of paper and locates a Cartesian coordinate system on it as follows: point $ (0,0) $ is located in the bottom-left corner, $ Ox $ axis is directed right, $ Oy $ axis is directed up. Pete gives Bob requests of three types:

- add x y — on the sheet of paper Bob marks a point with coordinates $ (x,y) $ . For each request of this type it's guaranteed that point $ (x,y) $ is not yet marked on Bob's sheet at the time of the request.
- remove x y — on the sheet of paper Bob erases the previously marked point with coordinates $ (x,y) $ . For each request of this type it's guaranteed that point $ (x,y) $ is already marked on Bob's sheet at the time of the request.
- find x y — on the sheet of paper Bob finds all the marked points, lying strictly above and strictly to the right of point $ (x,y) $ . Among these points Bob chooses the leftmost one, if it is not unique, he chooses the bottommost one, and gives its coordinates to Pete.

Bob managed to answer the requests, when they were 10, 100 or 1000, but when their amount grew up to $ 2·10^{5} $ , Bob failed to cope. Now he needs a program that will answer all Pete's requests. Help Bob, please!

## 输入格式

The first input line contains number $ n $ ( $ 1<=n<=2·10^{5} $ ) — amount of requests. Then there follow $ n $ lines — descriptions of the requests. add x y describes the request to add a point, remove x y — the request to erase a point, find x y — the request to find the bottom-left point. All the coordinates in the input file are non-negative and don't exceed $ 10^{9} $ .

## 输出格式

For each request of type find x y output in a separate line the answer to it — coordinates of the bottommost among the leftmost marked points, lying strictly above and to the right of point $ (x,y) $ . If there are no points strictly above and to the right of point $ (x,y) $ , output -1.

## 样例 #1

### 输入

```
7
add 1 1
add 3 4
find 0 0
remove 1 1
find 0 0
add 1 1
find 0 0

```

### 输出

```
1 1
3 4
1 1

```

## 样例 #2

### 输入

```
13
add 5 5
add 5 6
add 5 7
add 6 5
add 6 6
add 6 7
add 7 5
add 7 6
add 7 7
find 6 6
remove 7 7
find 6 6
find 4 4

```

### 输出

```
7 7
-1
5 5

```



---

---
title: "Colorado Potato Beetle"
layout: "post"
diff: 省选/NOI-
pid: CF243C
tag: ['搜索', '离散化', '广度优先搜索 BFS']
---

# Colorado Potato Beetle

## 题目描述

Old MacDonald has a farm and a large potato field, $ (10^{10}+1)×(10^{10}+1) $ square meters in size. The field is divided into square garden beds, each bed takes up one square meter.

Old McDonald knows that the Colorado potato beetle is about to invade his farm and can destroy the entire harvest. To fight the insects, Old McDonald wants to spray some beds with insecticides.

So Old McDonald went to the field, stood at the center of the central field bed and sprayed this bed with insecticides. Now he's going to make a series of movements and spray a few more beds. During each movement Old McDonald moves left, right, up or down the field some integer number of meters. As Old McDonald moves, he sprays all the beds he steps on. In other words, the beds that have any intersection at all with Old McDonald's trajectory, are sprayed with insecticides.

When Old McDonald finished spraying, he wrote out all his movements on a piece of paper. Now he wants to know how many beds won't be infected after the invasion of the Colorado beetles.

It is known that the invasion of the Colorado beetles goes as follows. First some bed on the field border gets infected. Than any bed that hasn't been infected, hasn't been sprayed with insecticides and has a common side with an infected bed, gets infected as well. Help Old McDonald and determine the number of beds that won't be infected by the Colorado potato beetle.

## 输入格式

The first line contains an integer $ n $ ( $ 1<=n<=1000 $ ) — the number of Old McDonald's movements.

Next $ n $ lines contain the description of Old McDonald's movements. The $ i $ -th of these lines describes the $ i $ -th movement. Each movement is given in the format " $ d_{i} $ $ x_{i} $ ", where $ d_{i} $ is the character that determines the direction of the movement ("L", "R", "U" or "D" for directions "left", "right", "up" and "down", correspondingly), and $ x_{i} $ ( $ 1<=x_{i}<=10^{6} $ ) is an integer that determines the number of meters in the movement.

## 输出格式

Print a single integer — the number of beds that won't be infected by the Colorado potato beetle.

Please do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 样例 #1

### 输入

```
5
R 8
U 9
L 9
D 8
L 2

```

### 输出

```
101
```

## 样例 #2

### 输入

```
7
R 10
D 2
L 7
U 9
D 2
R 3
D 10

```

### 输出

```
52
```



---

---
title: "Cow Tennis Tournament"
layout: "post"
diff: 省选/NOI-
pid: CF283E
tag: ['线段树', '离散化', '排序']
---

# Cow Tennis Tournament

## 题目描述

Farmer John is hosting a tennis tournament with his $ n $ cows. Each cow has a skill level $ s_{i} $ , and no two cows having the same skill level. Every cow plays every other cow exactly once in the tournament, and each cow beats every cow with skill level lower than its own.

However, Farmer John thinks the tournament will be demoralizing for the weakest cows who lose most or all of their matches, so he wants to flip some of the results. In particular, at $ k $ different instances, he will take two integers $ a_{i},b_{i} $ $ (a_{i}<b_{i}) $ and flip all the results between cows with skill level between $ a_{i} $ and $ b_{i} $ inclusive. That is, for any pair $ x,y $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF283E/7acc269d103239529ceb47c1b525554954b93d55.png) he will change the result of the match on the final scoreboard (so if $ x $ won the match, the scoreboard will now display that $ y $ won the match, and vice versa). It is possible that Farmer John will change the result of a match multiple times. It is not guaranteed that $ a_{i} $ and $ b_{i} $ are equal to some cow's skill level.

Farmer John wants to determine how balanced he made the tournament results look. In particular, he wants to count the number of triples of cows $ (p,q,r) $ for which the final leaderboard shows that cow $ p $ beats cow $ q $ , cow $ q $ beats cow $ r $ , and cow $ r $ beats cow $ p $ . Help him determine this number.

Note that two triples are considered different if they do not contain the same set of cows (i.e. if there is a cow in one triple that is not in the other).

## 输入格式

On the first line are two space-separated integers, $ n $ and $ k $ $ (3<=n<=10^{5}; 0<=k<=10^{5}) $ . On the next line are $ n $ space-separated distinct integers, $ s_{1},s_{2},...,s_{n} $ $ (1<=s_{i}<=10^{9}) $ , denoting the skill levels of the cows. On the next $ k $ lines are two space separated integers, $ a_{i} $ and $ b_{i} $ $ (1<=a_{i}<b_{i}<=10^{9}) $ representing the changes Farmer John made to the scoreboard in the order he makes it.

## 输出格式

A single integer, containing the number of triples of cows $ (p,q,r) $ for which the final leaderboard shows that cow $ p $ beats cow $ q $ , cow $ q $ beats cow $ r $ , and cow $ r $ beats cow $ p $ .

Please do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 说明/提示

In the first sample, cow 3 > cow 1, cow 3 > cow 2, and cow 2 > cow 1. However, the results between cows 1 and 2 and cows 2 and 3 are flipped, so now FJ's results show that cow 1 > cow 2, cow 2 > cow 3, and cow 3 > cow 1, so cows 1, 2, and 3 form a balanced triple.

## 样例 #1

### 输入

```
3 2
1 2 3
1 2
2 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
5 3
5 9 4 1 7
1 7
2 8
3 9

```

### 输出

```
3

```



---

---
title: "Coins Exhibition"
layout: "post"
diff: 省选/NOI-
pid: CF930E
tag: ['动态规划 DP', '离散化', '排序']
---

# Coins Exhibition

## 题目描述

Arkady and Kirill visited an exhibition of rare coins. The coins were located in a row and enumerated from left to right from $ 1 $ to $ k $ , each coin either was laid with its obverse (front) side up, or with its reverse (back) side up.

Arkady and Kirill made some photos of the coins, each photo contained a segment of neighboring coins. Akrady is interested in obverses, so on each photo made by him there is at least one coin with obverse side up. On the contrary, Kirill is interested in reverses, so on each photo made by him there is at least one coin with its reverse side up.

The photos are lost now, but Arkady and Kirill still remember the bounds of the segments of coins each photo contained. Given this information, compute the remainder of division by $ 10^{9}+7 $ of the number of ways to choose the upper side of each coin in such a way, that on each Arkady's photo there is at least one coin with obverse side up, and on each Kirill's photo there is at least one coin with reverse side up.

## 输入格式

The first line contains three integers $ k $ , $ n $ and $ m $ ( $ 1<=k<=10^{9} $ , $ 0<=n,m<=10^{5} $ ) — the total number of coins, the number of photos made by Arkady, and the number of photos made by Kirill, respectively.

The next $ n $ lines contain the descriptions of Arkady's photos, one per line. Each of these lines contains two integers $ l $ and $ r $ ( $ 1<=l<=r<=k $ ), meaning that among coins from the $ l $ -th to the $ r $ -th there should be at least one with obverse side up.

The next $ m $ lines contain the descriptions of Kirill's photos, one per line. Each of these lines contains two integers $ l $ and $ r $ ( $ 1<=l<=r<=k $ ), meaning that among coins from the $ l $ -th to the $ r $ -th there should be at least one with reverse side up.

## 输出格式

Print the only line — the number of ways to choose the side for each coin modulo $ 10^{9}+7=1000000007 $ .

## 说明/提示

In the first example the following ways are possible ('O' — obverse, 'R' — reverse side):

- OROOR,
- ORORO,
- ORORR,
- RROOR,
- RRORO,
- RRORR,
- ORROR,
- ORRRO.

In the second example the information is contradictory: the second coin should have obverse and reverse sides up at the same time, that is impossible. So, the answer is $ 0 $ .

## 样例 #1

### 输入

```
5 2 2
1 3
3 5
2 2
4 5

```

### 输出

```
8

```

## 样例 #2

### 输入

```
5 3 2
1 3
2 2
3 5
2 2
4 5

```

### 输出

```
0

```

## 样例 #3

### 输入

```
60 5 7
1 3
50 60
1 60
30 45
20 40
4 5
6 37
5 18
50 55
22 27
25 31
44 45

```

### 输出

```
732658600

```



---

