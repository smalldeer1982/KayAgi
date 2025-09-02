---
title: "Forgery"
layout: "post"
diff: 普及-
pid: CF1059B
tag: ['枚举', '广度优先搜索 BFS']
---

# Forgery

## 题目描述

Student Andrey has been skipping physical education lessons for the whole term, and now he must somehow get a passing grade on this subject. Obviously, it is impossible to do this by legal means, but Andrey doesn't give up. Having obtained an empty certificate from a local hospital, he is going to use his knowledge of local doctor's handwriting to make a counterfeit certificate of illness. However, after writing most of the certificate, Andrey suddenly discovered that doctor's signature is impossible to forge. Or is it?

For simplicity, the signature is represented as an $ n\times m $ grid, where every cell is either filled with ink or empty. Andrey's pen can fill a $ 3\times3 $ square without its central cell if it is completely contained inside the grid, as shown below.

 `<br></br>xxx<br></br>x.x<br></br>xxx<br></br>`Determine whether is it possible to forge the signature on an empty $ n\times m $ grid.

## 输入格式

The first line of input contains two integers $ n $ and $ m $ ( $ 3 \le n, m \le 1000 $ ).

Then $ n $ lines follow, each contains $ m $ characters. Each of the characters is either '.', representing an empty cell, or '\#', representing an ink filled cell.

## 输出格式

If Andrey can forge the signature, output "YES". Otherwise output "NO".

You can print each letter in any case (upper or lower).

## 说明/提示

In the first sample Andrey can paint the border of the square with the center in $ (2, 2) $ .

In the second sample the signature is impossible to forge.

In the third sample Andrey can paint the borders of the squares with the centers in $ (2, 2) $ and $ (3, 2) $ :

1. we have a clear paper: `<br></br>...<br></br>...<br></br>...<br></br>...<br></br>`
2. use the pen with center at $ (2, 2) $ . `<br></br>###<br></br>#.#<br></br>###<br></br>...<br></br>`
3. use the pen with center at $ (3, 2) $ . `<br></br>###<br></br>###<br></br>###<br></br>###<br></br>`

In the fourth sample Andrey can paint the borders of the squares with the centers in $ (3, 3) $ and $ (3, 5) $ .

## 样例 #1

### 输入

```
3 3
###
#.#
###

```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3 3
###
###
###

```

### 输出

```
NO
```

## 样例 #3

### 输入

```
4 3
###
###
###
###

```

### 输出

```
YES
```

## 样例 #4

### 输入

```
5 7
.......
.#####.
.#.#.#.
.#####.
.......

```

### 输出

```
YES
```



---

---
title: "Obsession with Robots"
layout: "post"
diff: 普及-
pid: CF8B
tag: ['广度优先搜索 BFS', '最短路']
---

# Obsession with Robots

## 题目描述

The whole world got obsessed with robots,and to keep pace with the progress, great Berland's programmer Draude decided to build his own robot. He was working hard at the robot. He taught it to walk the shortest path from one point to another, to record all its movements, but like in many Draude's programs, there was a bug — the robot didn't always walk the shortest path. Fortunately, the robot recorded its own movements correctly. Now Draude wants to find out when his robot functions wrong. Heh, if Draude only remembered the map of the field, where he tested the robot, he would easily say if the robot walked in the right direction or not. But the field map was lost never to be found, that's why he asks you to find out if there exist at least one map, where the path recorded by the robot is the shortest.

The map is an infinite checkered field, where each square is either empty, or contains an obstruction. It is also known that the robot never tries to run into the obstruction. By the recorded robot's movements find out if there exist at least one such map, that it is possible to choose for the robot a starting square (the starting square should be empty) such that when the robot moves from this square its movements coincide with the recorded ones (the robot doesn't run into anything, moving along empty squares only), and the path from the starting square to the end one is the shortest.

In one movement the robot can move into the square (providing there are no obstrutions in this square) that has common sides with the square the robot is currently in.

## 输入格式

The first line of the input file contains the recording of the robot's movements. This recording is a non-empty string, consisting of uppercase Latin letters L, R, U and D, standing for movements left, right, up and down respectively. The length of the string does not exceed 100.

## 输出格式

In the first line output the only word OK (if the above described map exists), or BUG (if such a map does not exist).

## 样例 #1

### 输入

```
LLUUUR

```

### 输出

```
OK

```

## 样例 #2

### 输入

```
RRUULLDD

```

### 输出

```
BUG

```



---

---
title: "Water The Garden"
layout: "post"
diff: 普及-
pid: CF920A
tag: ['搜索', '枚举', '广度优先搜索 BFS']
---

# Water The Garden

## 题目描述

It is winter now, and Max decided it's about time he watered the garden.

The garden can be represented as $ n $ consecutive garden beds, numbered from $ 1 $ to $ n $ . $ k $ beds contain water taps ( $ i $ -th tap is located in the bed $ x_{i} $ ), which, if turned on, start delivering water to neighbouring beds. If the tap on the bed $ x_{i} $ is turned on, then after one second has passed, the bed $ x_{i} $ will be watered; after two seconds have passed, the beds from the segment $ [x_{i}-1,x_{i}+1] $ will be watered (if they exist); after $ j $ seconds have passed ( $ j $ is an integer number), the beds from the segment $ [x_{i}-(j-1),x_{i}+(j-1)] $ will be watered (if they exist). Nothing changes during the seconds, so, for example, we can't say that the segment $ [x_{i}-2.5,x_{i}+2.5] $ will be watered after $ 2.5 $ seconds have passed; only the segment $ [x_{i}-2,x_{i}+2] $ will be watered at that moment.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920A/13bc7cf6794d83f150515b3ef05c019c5a177edb.png) The garden from test $ 1 $ . White colour denotes a garden bed without a tap, red colour — a garden bed with a tap.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920A/7701b634db65a2b1523162fa68f6ca25374deecc.png) The garden from test $ 1 $ after $ 2 $ seconds have passed after turning on the tap. White colour denotes an unwatered garden bed, blue colour — a watered bed. Max wants to turn on all the water taps at the same moment, and now he wonders, what is the minimum number of seconds that have to pass after he turns on some taps until the whole garden is watered. Help him to find the answer!

## 输入格式

The first line contains one integer $ t $ — the number of test cases to solve ( $ 1<=t<=200 $ ).

Then $ t $ test cases follow. The first line of each test case contains two integers $ n $ and $ k $ ( $ 1<=n<=200 $ , $ 1<=k<=n $ ) — the number of garden beds and water taps, respectively.

Next line contains $ k $ integers $ x_{i} $ ( $ 1<=x_{i}<=n $ ) — the location of $ i $ -th water tap. It is guaranteed that for each ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920A/2023391807a0506d9aa6b2ab3f46eb89dee16074.png) condition $ x_{i-1}<x_{i} $ holds.

It is guaranteed that the sum of $ n $ over all test cases doesn't exceed $ 200 $ .

Note that in hacks you have to set $ t=1 $ .

## 输出格式

For each test case print one integer — the minimum number of seconds that have to pass after Max turns on some of the water taps, until the whole garden is watered.

## 说明/提示

The first example consists of $ 3 $ tests:

1. There are $ 5 $ garden beds, and a water tap in the bed $ 3 $ . If we turn it on, then after $ 1 $ second passes, only bed $ 3 $ will be watered; after $ 2 $ seconds pass, beds $ [1,3] $ will be watered, and after $ 3 $ seconds pass, everything will be watered.
2. There are $ 3 $ garden beds, and there is a water tap in each one. If we turn all of them on, then everything will be watered after $ 1 $ second passes.
3. There are $ 4 $ garden beds, and only one tap in the bed $ 1 $ . It will take $ 4 $ seconds to water, for example, bed $ 4 $ .

## 样例 #1

### 输入

```
3
5 1
3
3 3
1 2 3
4 1
1

```

### 输出

```
3
1
4

```



---

---
title: "Lucky Numbers (easy)"
layout: "post"
diff: 普及-
pid: CF96B
tag: ['广度优先搜索 BFS']
---

# Lucky Numbers (easy)

## 题目描述

Petya loves lucky numbers. Everybody knows that positive integers are lucky if their decimal representation doesn't contain digits other than $ 4 $ and $ 7 $ . For example, numbers $ 47 $ , $ 744 $ , $ 4 $ are lucky and $ 5 $ , $ 17 $ , $ 467 $ are not.

Lucky number is super lucky if it's decimal representation contains equal amount of digits $ 4 $ and $ 7 $ . For example, numbers $ 47 $ , $ 7744 $ , $ 474477 $ are super lucky and $ 4 $ , $ 744 $ , $ 467 $ are not.

One day Petya came across a positive integer $ n $ . Help him to find the least super lucky number which is not less than $ n $ .

## 输入格式

The only line contains a positive integer $ n $ ( $ 1<=n<=10^{9} $ ). This number doesn't have leading zeroes.

## 输出格式

Output the least super lucky number that is more than or equal to $ n $ .

Please, do not use the %lld specificator to read or write 64-bit integers in C++. It is preferred to use the cin, cout streams or the %I64d specificator.

## 样例 #1

### 输入

```
4500

```

### 输出

```
4747

```

## 样例 #2

### 输入

```
47

```

### 输出

```
47

```



---

