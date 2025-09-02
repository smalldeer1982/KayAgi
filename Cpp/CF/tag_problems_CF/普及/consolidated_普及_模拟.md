---
title: "Planning The Expedition"
layout: "post"
diff: 普及/提高-
pid: CF1011B
tag: ['模拟', '枚举', '概率论']
---

# Planning The Expedition

## 题目描述

Natasha is planning an expedition to Mars for $ n $ people. One of the important tasks is to provide food for each participant.

The warehouse has $ m $ daily food packages. Each package has some food type $ a_i $ .

Each participant must eat exactly one food package each day. Due to extreme loads, each participant must eat the same food type throughout the expedition. Different participants may eat different (or the same) types of food.

Formally, for each participant $ j $ Natasha should select his food type $ b_j $ and each day $ j $ -th participant will eat one food package of type $ b_j $ . The values $ b_j $ for different participants may be different.

What is the maximum possible number of days the expedition can last, following the requirements above?

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1 \le n \le 100 $ , $ 1 \le m \le 100 $ ) — the number of the expedition participants and the number of the daily food packages available.

The second line contains sequence of integers $ a_1, a_2, \dots, a_m $ ( $ 1 \le a_i \le 100 $ ), where $ a_i $ is the type of $ i $ -th food package.

## 输出格式

Print the single integer — the number of days the expedition can last. If it is not possible to plan the expedition for even one day, print 0.

## 说明/提示

In the first example, Natasha can assign type $ 1 $ food to the first participant, the same type $ 1 $ to the second, type $ 5 $ to the third and type $ 2 $ to the fourth. In this case, the expedition can last for $ 2 $ days, since each participant can get two food packages of his food type (there will be used $ 4 $ packages of type $ 1 $ , two packages of type $ 2 $ and two packages of type $ 5 $ ).

In the second example, there are $ 100 $ participants and only $ 1 $ food package. In this case, the expedition can't last even $ 1 $ day.

## 样例 #1

### 输入

```
4 10
1 5 2 1 1 1 2 5 7 2

```

### 输出

```
2

```

## 样例 #2

### 输入

```
100 1
1

```

### 输出

```
0

```

## 样例 #3

### 输入

```
2 5
5 4 3 2 1

```

### 输出

```
1

```

## 样例 #4

### 输入

```
3 9
42 42 42 42 42 42 42 42 42

```

### 输出

```
3

```



---

---
title: "The Phone Number"
layout: "post"
diff: 普及/提高-
pid: CF1017C
tag: ['模拟', '数学', '构造']
---

# The Phone Number

## 题目描述

Mrs. Smith is trying to contact her husband, John Smith, but she forgot the secret phone number!

The only thing Mrs. Smith remembered was that any permutation of $ n $ can be a secret phone number. Only those permutations that minimize secret value might be the phone of her husband.

The sequence of $ n $ integers is called a permutation if it contains all integers from $ 1 $ to $ n $ exactly once.

The secret value of a phone number is defined as the sum of the length of the longest increasing subsequence (LIS) and length of the longest decreasing subsequence (LDS).

A subsequence $ a_{i_1}, a_{i_2}, \ldots, a_{i_k} $ where $ 1\leq i_1 < i_2 < \ldots < i_k\leq n $ is called increasing if $ a_{i_1} < a_{i_2} < a_{i_3} < \ldots < a_{i_k} $ . If $ a_{i_1} > a_{i_2} > a_{i_3} > \ldots > a_{i_k} $ , a subsequence is called decreasing. An increasing/decreasing subsequence is called longest if it has maximum length among all increasing/decreasing subsequences.

For example, if there is a permutation $ [6, 4, 1, 7, 2, 3, 5] $ , LIS of this permutation will be $ [1, 2, 3, 5] $ , so the length of LIS is equal to $ 4 $ . LDS can be $ [6, 4, 1] $ , $ [6, 4, 2] $ , or $ [6, 4, 3] $ , so the length of LDS is $ 3 $ .

Note, the lengths of LIS and LDS can be different.

So please help Mrs. Smith to find a permutation that gives a minimum sum of lengths of LIS and LDS.

## 输入格式

The only line contains one integer $ n $ ( $ 1 \le n \le 10^5 $ ) — the length of permutation that you need to build.

## 输出格式

Print a permutation that gives a minimum sum of lengths of LIS and LDS.

If there are multiple answers, print any.

## 说明/提示

In the first sample, you can build a permutation $ [3, 4, 1, 2] $ . LIS is $ [3, 4] $ (or $ [1, 2] $ ), so the length of LIS is equal to $ 2 $ . LDS can be ony of $ [3, 1] $ , $ [4, 2] $ , $ [3, 2] $ , or $ [4, 1] $ . The length of LDS is also equal to $ 2 $ . The sum is equal to $ 4 $ . Note that $ [3, 4, 1, 2] $ is not the only permutation that is valid.

In the second sample, you can build a permutation $ [2, 1] $ . LIS is $ [1] $ (or $ [2] $ ), so the length of LIS is equal to $ 1 $ . LDS is $ [2, 1] $ , so the length of LDS is equal to $ 2 $ . The sum is equal to $ 3 $ . Note that permutation $ [1, 2] $ is also valid.

## 样例 #1

### 输入

```
4

```

### 输出

```
3 4 1 2

```

## 样例 #2

### 输入

```
2

```

### 输出

```
2 1

```



---

---
title: "Single Wildcard Pattern Matching"
layout: "post"
diff: 普及/提高-
pid: CF1023A
tag: ['模拟', '字符串']
---

# Single Wildcard Pattern Matching

## 题目描述

给定两个小写英文单词 $s,t$，其中 $s$ 包含还不多于一个的 `*`。$s$ 的长度为 $n$，而 $t$ 的长度为 $m$。

$s$ 中的 `*` 可以被替换为任意小写字母串（可以是空串），但其他字母不能被更改或者调换顺序。如果将 `*` 替换为一个任意小写字母串之后，$s=t$，那么我们称 $s,t$ 是匹配的。

例如，字符串 $s=$ `lu*gu` 与 `luogu` `lugu` `luooooogu`都是匹配的，但与字符串 `lougu` `log` `lu^_^gu` `lu114514gu` 都是不匹配的。

如果给定的 $s,t$ 是匹配的，输出 `YES`，否则输出 `NO`。

## 输入格式

第一行输入两个整数 $n,m$，分别表示 $s$ 和 $t$ 的长度。

第二行输入字符串 $s$，保证 $s$ 中只含有小写字母和不多于一个的 `*`。

第三行输入字符串 $t$，保证 $t$ 中只含有小写字母。

## 输出格式

如果 $s$ 与 $t$ 是匹配的，那么输出 `YES`，否则输出 `NO`。

## 说明/提示

对于 $100\%$ 的数据，$1\le n,m\le2\times10^5$。

$\mathrm{by\ @}$[$\mathrm{Fish\_Know\_Forever}$](/user/663215)

## 样例 #1

### 输入

```
6 10
code*s
codeforces

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
6 5
vk*cup
vkcup

```

### 输出

```
YES

```

## 样例 #3

### 输入

```
1 1
v
k

```

### 输出

```
NO

```

## 样例 #4

### 输入

```
9 6
gfgf*gfgf
gfgfgf

```

### 输出

```
NO

```



---

---
title: "Cthulhu"
layout: "post"
diff: 普及/提高-
pid: CF103B
tag: ['模拟', '并查集', '构造']
---

# Cthulhu

## 题目描述

...Once upon a time a man came to the sea. The sea was stormy and dark. The man started to call for the little mermaid to appear but alas, he only woke up Cthulhu...

Whereas on the other end of the world Pentagon is actively collecting information trying to predict the monster's behavior and preparing the secret super weapon. Due to high seismic activity and poor weather conditions the satellites haven't yet been able to make clear shots of the monster. The analysis of the first shot resulted in an undirected graph with $ n $ vertices and $ m $ edges. Now the world's best minds are about to determine whether this graph can be regarded as Cthulhu or not.

To add simplicity, let's suppose that Cthulhu looks from the space like some spherical body with tentacles attached to it. Formally, we shall regard as Cthulhu such an undirected graph that can be represented as a set of three or more rooted trees, whose roots are connected by a simple cycle.

It is guaranteed that the graph contains no multiple edges and self-loops.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF103B/33dc55a8762ea9a08fee5a98be66bd3670ec0fbb.png)

## 输入格式

The first line contains two integers — the number of vertices $ n $ and the number of edges $ m $ of the graph ($1 \le n \le 100$, $0 \le m \le \frac{n(n-1)}{2}$).

Each of the following $ m $ lines contains a pair of integers $ x $ and $ y $, that show that an edge exists between vertices $ x $ and $ y $ ($1 \le x, y \le n, x \ne y$). For each pair of vertices there will be at most one edge between them, no edge connects a vertex to itself.

## 输出格式

Print "NO", if the graph is not Cthulhu and "FHTAGN!" if it is.

## 说明/提示

Let us denote as a simple cycle a set of $ v $ vertices that can be numbered so that the edges will only exist between vertices number $ 1 $ and $ 2 $ , $ 2 $ and $ 3 $ , ..., $ v-1 $ and $ v $ , $ v $ and $ 1 $ .

A tree is a connected undirected graph consisting of $ n $ vertices and $ n-1 $ edges ( $ n&gt;0 $ ).

A rooted tree is a tree where one vertex is selected to be the root.

## 样例 #1

### 输入

```
6 6
6 3
6 4
5 1
2 5
1 4
5 4

```

### 输出

```
FHTAGN!
```

## 样例 #2

### 输入

```
6 5
5 6
4 6
3 1
5 1
1 2

```

### 输出

```
NO
```



---

---
title: "Smallest Word"
layout: "post"
diff: 普及/提高-
pid: CF1043C
tag: ['模拟', '字符串']
---

# Smallest Word

## 题目描述

IA has so many colorful magnets on her fridge! Exactly one letter is written on each magnet, 'a' or 'b'. She loves to play with them, placing all magnets in a row. However, the girl is quickly bored and usually thinks how to make her entertainment more interesting.

Today, when IA looked at the fridge, she noticed that the word formed by magnets is really messy. "It would look much better when I'll swap some of them!" — thought the girl — "but how to do it?". After a while, she got an idea. IA will look at all prefixes with lengths from $ 1 $ to the length of the word and for each prefix she will either reverse this prefix or leave it as it is. She will consider the prefixes in the fixed order: from the shortest to the largest. She wants to get the lexicographically smallest possible word after she considers all prefixes. Can you help her, telling which prefixes should be chosen for reversing?

A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 输入格式

The first and the only line contains a string $ s $ ( $ 1 \le |s| \le 1000 $ ), describing the initial string formed by magnets. The string $ s $ consists only of characters 'a' and 'b'.

## 输出格式

Output exactly $ |s| $ integers. If IA should reverse the $ i $ -th prefix (that is, the substring from $ 1 $ to $ i $ ), the $ i $ -th integer should be equal to $ 1 $ , and it should be equal to $ 0 $ otherwise.

If there are multiple possible sequences leading to the optimal answer, print any of them.

## 说明/提示

In the first example, IA can reverse the second and the third prefix and get a string "abbb". She cannot get better result, since it is also lexicographically smallest string obtainable by permuting characters of the initial string.

In the second example, she can reverse any subset of prefixes — all letters are 'a'.

## 样例 #1

### 输入

```
bbab

```

### 输出

```
0 1 1 0

```

## 样例 #2

### 输入

```
aaaaa

```

### 输出

```
1 0 0 0 1

```



---

---
title: "Boxes Packing"
layout: "post"
diff: 普及/提高-
pid: CF1066D
tag: ['模拟', '贪心', '二分']
---

# Boxes Packing

## 题目描述

有 $n$ 个物品，$m$ 个盒子。其中第 $i$ 个物品的大小为 $a_i$，所有盒子的大小均为 $k$。Makmis 先生想要将这些物品放入盒子中。对于每个物品，如果可以放入当前盒子中则放入当前盒子，否则换一个新的盒子放入。如果物品数量太多使得盒子装不下，可以**将先放入的物品丢弃**。求出最多能够放入多少物品。

## 输入格式

第一行三个整数 $n,m,k$，含义见上文。

第二行共 $n$ 个数，第 $i$ 个为 $a_i$，表示物品的大小。

## 输出格式

一行一个数，表示最多可以放入多少个物品。

## 说明/提示

#### 样例解释
- 在第一组样例中，可以将后 $4$ 个放入盒子。
- 在第二组样例中仅有一个盒子，故只能放入最后一个。
- 在第三组样例中有 $3$ 个大小为 $3$ 的盒子，每个盒子正好装满。
#### 数据规模与约定
保证 $1\le n,m\le2\times 10^5$，$1\le k\le10^9$，$1\le a_i\le k$。

## 样例 #1

### 输入

```
5 2 6
5 2 1 4 2

```

### 输出

```
4

```

## 样例 #2

### 输入

```
5 1 4
4 2 3 4 1

```

### 输出

```
1

```

## 样例 #3

### 输入

```
5 3 3
1 2 3 1 1

```

### 输出

```
5

```



---

---
title: "Berland Fair"
layout: "post"
diff: 普及/提高-
pid: CF1073D
tag: ['模拟', '枚举']
---

# Berland Fair

## 题目描述

XXI Berland Annual Fair is coming really soon! Traditionally fair consists of $ n $ booths, arranged in a circle. The booths are numbered $ 1 $ through $ n $ clockwise with $ n $ being adjacent to $ 1 $ . The $ i $ -th booths sells some candies for the price of $ a_i $ burles per item. Each booth has an unlimited supply of candies.

Polycarp has decided to spend at most $ T $ burles at the fair. However, he has some plan in mind for his path across the booths:

- at first, he visits booth number $ 1 $ ;
- if he has enough burles to buy exactly one candy from the current booth, then he buys it immediately;
- then he proceeds to the next booth in the clockwise order (regardless of if he bought a candy or not).

Polycarp's money is finite, thus the process will end once he can no longer buy candy at any booth.

Calculate the number of candies Polycarp will buy.

## 输入格式

The first line contains two integers $ n $ and $ T $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 1 \le T \le 10^{18} $ ) — the number of booths at the fair and the initial amount of burles Polycarp has.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — the price of the single candy at booth number $ i $ .

## 输出格式

Print a single integer — the total number of candies Polycarp will buy.

## 说明/提示

Let's consider the first example. Here are Polycarp's moves until he runs out of money:

1. Booth $ 1 $ , buys candy for $ 5 $ , $ T = 33 $ ;
2. Booth $ 2 $ , buys candy for $ 2 $ , $ T = 31 $ ;
3. Booth $ 3 $ , buys candy for $ 5 $ , $ T = 26 $ ;
4. Booth $ 1 $ , buys candy for $ 5 $ , $ T = 21 $ ;
5. Booth $ 2 $ , buys candy for $ 2 $ , $ T = 19 $ ;
6. Booth $ 3 $ , buys candy for $ 5 $ , $ T = 14 $ ;
7. Booth $ 1 $ , buys candy for $ 5 $ , $ T = 9 $ ;
8. Booth $ 2 $ , buys candy for $ 2 $ , $ T = 7 $ ;
9. Booth $ 3 $ , buys candy for $ 5 $ , $ T = 2 $ ;
10. Booth $ 1 $ , buys no candy, not enough money;
11. Booth $ 2 $ , buys candy for $ 2 $ , $ T = 0 $ .

No candy can be bought later. The total number of candies bought is $ 10 $ .

In the second example he has $ 1 $ burle left at the end of his path, no candy can be bought with this amount.

## 样例 #1

### 输入

```
3 38
5 2 5

```

### 输出

```
10

```

## 样例 #2

### 输入

```
5 21
2 4 100 2 6

```

### 输出

```
6

```



---

---
title: "Cinema Cashier"
layout: "post"
diff: 普及/提高-
pid: CF10B
tag: ['模拟', '树状数组', '队列']
---

# Cinema Cashier

## 题目描述

All cinema halls in Berland are rectangles with $ K $ rows of $ K $ seats each, and $ K $ is an odd number. Rows and seats are numbered from $ 1 $ to $ K $ . For safety reasons people, who come to the box office to buy tickets, are not allowed to choose seats themselves. Formerly the choice was made by a cashier, but now this is the responsibility of a special seating program. It was found out that the large majority of Berland's inhabitants go to the cinema in order to watch a movie, that's why they want to sit as close to the hall center as possible. Moreover, a company of $ M $ people, who come to watch a movie, want necessarily to occupy $ M $ successive seats in one row. Let's formulate the algorithm, according to which the program chooses seats and sells tickets. As the request for $ M $ seats comes, the program should determine the row number $ x $ and the segment $ [y_{l},y_{r}] $ of the seats numbers in this row, where $ y_{r}-y_{l}+1=M $ . From all such possible variants as a final result the program should choose the one with the minimum function value of total seats remoteness from the center. Say, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF10B/c9748a84837b67ee9aa2cbea2b55fdd9ec523940.png) — the row and the seat numbers of the most "central" seat. Then the function value of seats remoteness from the hall center is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF10B/9bc644baca5d1a575e01b85fce16d96f8e180ca4.png). If the amount of minimum function values is more than one, the program should choose the one that is closer to the screen (i.e. the row number $ x $ is lower). If the variants are still multiple, it should choose the one with the minimum $ y_{l} $ . If you did not get yet, your task is to simulate the work of this program.


## 输入格式

The first line contains two integers $ N $ and $ K $ ( $ 1<=N<=1000,1<=K<=99 $ ) — the amount of requests and the hall size respectively. The second line contains $ N $ space-separated integers $ M_{i} $ from the range $ [1,K] $ — requests to the program.

## 输出格式

Output $ N $ lines. In the $ i $ -th line output «-1» (without quotes), if it is impossible to find $ M_{i} $ successive seats in one row, otherwise output three numbers $ x,y_{l},y_{r} $ . Separate the numbers with a space.

## 样例 #1

### 输入

```
2 1
1 1

```

### 输出

```
1 1 1
-1

```

## 样例 #2

### 输入

```
4 3
1 2 3 1

```

### 输出

```
2 2 2
1 1 2
3 1 3
2 1 1

```



---

---
title: "Catch Overflow!"
layout: "post"
diff: 普及/提高-
pid: CF1175B
tag: ['模拟', '递归']
---

# Catch Overflow!

## 题目描述

You are given a function $ f $ written in some basic language. The function accepts an integer value, which is immediately written into some variable $ x $ . $ x $ is an integer variable and can be assigned values from $ 0 $ to $ 2^{32}-1 $ . The function contains three types of commands:

- for $ n $ — for loop;
- end — every command between "for $ n $ " and corresponding "end" is executed $ n $ times;
- add — adds 1 to $ x $ .

After the execution of these commands, value of $ x $ is returned.

Every "for $ n $ " is matched with "end", thus the function is guaranteed to be valid. "for $ n $ " can be immediately followed by "end"."add" command can be outside of any for loops.

Notice that "add" commands might overflow the value of $ x $ ! It means that the value of $ x $ becomes greater than $ 2^{32}-1 $ after some "add" command.

Now you run $ f(0) $ and wonder if the resulting value of $ x $ is correct or some overflow made it incorrect.

If overflow happened then output "OVERFLOW!!!", otherwise print the resulting value of $ x $ .

## 输入格式

The first line contains a single integer $ l $ ( $ 1 \le l \le 10^5 $ ) — the number of lines in the function.

Each of the next $ l $ lines contains a single command of one of three types:

- for $ n $ ( $ 1 \le n \le 100 $ ) — for loop;
- end — every command between "for $ n $ " and corresponding "end" is executed $ n $ times;
- add — adds 1 to $ x $ .

## 输出格式

If overflow happened during execution of $ f(0) $ , then output "OVERFLOW!!!", otherwise print the resulting value of $ x $ .

## 说明/提示

In the first example the first "add" is executed 1 time, the second "add" is executed 150 times and the last "add" is executed 10 times. Note that "for $ n $ " can be immediately followed by "end" and that "add" can be outside of any for loops.

In the second example there are no commands "add", thus the returning value is 0.

In the third example "add" command is executed too many times, which causes $ x $ to go over $ 2^{32}-1 $ .

## 样例 #1

### 输入

```
9
add
for 43
end
for 10
for 15
add
end
add
end

```

### 输出

```
161

```

## 样例 #2

### 输入

```
2
for 62
end

```

### 输出

```
0

```

## 样例 #3

### 输入

```
11
for 100
for 100
for 100
for 100
for 100
add
end
end
end
end
end

```

### 输出

```
OVERFLOW!!!

```



---

---
title: "Polygon"
layout: "post"
diff: 普及/提高-
pid: CF1360E
tag: ['模拟', '深度优先搜索 DFS']
---

# Polygon

## 题目描述

Polygon is not only the best platform for developing problems but also a square matrix with side $ n $ , initially filled with the character 0.

On the polygon, military training was held. The soldiers placed a cannon above each cell in the first row and a cannon to the left of each cell in the first column. Thus, exactly $ 2n $ cannons were placed.

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1360E/af538d3417e3bff02f7ca9d4302ffeb8985b4df9.png)Initial polygon for $ n=4 $ . Cannons shoot character 1. At any moment of time, no more than one cannon is shooting. When a 1 flies out of a cannon, it flies forward (in the direction of the shot) until it collides with a polygon border or another 1. After that, it takes the cell in which it was before the collision and remains there. Take a look at the examples for better understanding.

More formally:

- if a cannon stands in the row $ i $ , to the left of the first column, and shoots with a 1, then the 1 starts its flight from the cell ( $ i, 1 $ ) and ends in some cell ( $ i, j $ );
- if a cannon stands in the column $ j $ , above the first row, and shoots with a 1, then the 1 starts its flight from the cell ( $ 1, j $ ) and ends in some cell ( $ i,         j $ ).

For example, consider the following sequence of shots:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1360E/b0a2a2240d9a0a11c84c2c0dd9be686db3e431b3.png) 1. Shoot the cannon in the row $ 2 $ . 2. Shoot the cannon in the row $ 2 $ . 3. Shoot the cannon in column $ 3 $ .

You have a report from the military training on your desk. This report is a square matrix with side length $ n $ consisting of 0 and 1. You wonder if the training actually happened. In other words, is there a sequence of shots such that, after the training, you get the given matrix?

Each cannon can make an arbitrary number of shots. Before the training, each cell of the polygon contains 0.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le       1000 $ ) — the number of test cases. Then $ t $ test cases follow.

Each test case starts with a line containing an integer $ n $ ( $ 1 \le n \le 50 $ ) — the size of the polygon.

This is followed by $ n $ lines of length $ n $ , consisting of 0 and 1 — the polygon matrix after the training.

The total area of the matrices in all test cases in one test does not exceed $ 10^5 $ .

## 输出格式

For each test case print:

- YES if there is a sequence of shots leading to a given matrix;
- NO if such a sequence does not exist.

The letters in the words YES and NO can be printed in any case.

## 说明/提示

The first test case was explained in the statement.

The answer to the second test case is NO, since a 1 in a cell ( $ 1, 1 $ ) flying out of any cannon would continue its flight further.

## 样例 #1

### 输入

```
5
4
0010
0011
0000
0000
2
10
01
2
00
00
4
0101
1111
0101
0111
4
0100
1110
0101
0111
```

### 输出

```
YES
NO
YES
YES
NO
```



---

---
title: "String Manipulation 1.0"
layout: "post"
diff: 普及/提高-
pid: CF159C
tag: ['模拟']
---

# String Manipulation 1.0

## 题目描述

One popular website developed an unusual username editing procedure. One can change the username only by deleting some characters from it: to change the current name $ s $ , a user can pick number $ p $ and character $ c $ and delete the $ p $ -th occurrence of character $ c $ from the name. After the user changed his name, he can't undo the change.

For example, one can change name "arca" by removing the second occurrence of character "a" to get "arc".

Polycarpus learned that some user initially registered under nickname $ t $ , where $ t $ is a concatenation of $ k $ copies of string $ s $ . Also, Polycarpus knows the sequence of this user's name changes. Help Polycarpus figure out the user's final name.

## 输入格式

The first line contains an integer $ k $ ( $ 1<=k<=2000 $ ). The second line contains a non-empty string $ s $ , consisting of lowercase Latin letters, at most $ 100 $ characters long. The third line contains an integer $ n $ ( $ 0<=n<=20000 $ ) — the number of username changes. Each of the next $ n $ lines contains the actual changes, one per line. The changes are written as " $ p_{i} $ $ c_{i} $ " (without the quotes), where $ p_{i} $ ( $ 1<=p_{i}<=200000 $ ) is the number of occurrences of letter $ c_{i} $ , $ c_{i} $ is a lowercase Latin letter. It is guaranteed that the operations are correct, that is, the letter to be deleted always exists, and after all operations not all letters are deleted from the name. The letters' occurrences are numbered starting from 1.

## 输出格式

Print a single string — the user's final name after all changes are applied to it.

## 说明/提示

Let's consider the first sample. Initially we have name "bacbac"; the first operation transforms it into "bacbc", the second one — to "acbc", and finally, the third one transforms it into "acb".

## 样例 #1

### 输入

```
2
bac
3
2 a
1 b
2 c

```

### 输出

```
acb

```

## 样例 #2

### 输入

```
1
abacaba
4
1 a
1 a
1 c
2 b

```

### 输出

```
baa

```



---

---
title: "Column Swapping"
layout: "post"
diff: 普及/提高-
pid: CF1684C
tag: ['模拟']
---

# Column Swapping

## 题目描述

如果一个表格每行都单调不降，称它为好的。  
给你 $t$ 个 $n_i$ 行 $m_i$ 列的表格，对于每个表格，询问是否能通过调换某两列 **（不一定不同）** 使得这个表格是好的（这样的操作需要且仅能执行一次）。如果可以，输出两列的编号；不可以，输出 $-1$。

## 输入格式

第一行一个正整数 $t$，表示表格的个数。  
接下来输入 $t$ 个表格。  
对于每个表格，第一行两个正整数 $n,m$，分别表示表格的行数与列数。  
接下来 $n$ 行，每行 $m$ 个正整数，表示这个表格。

## 输出格式

对于每个表格，单独输出一行，如果能通过上面描述的方式将其变为好的，输出对调的两列的编号；如果不能，输出 $-1$。

## 说明/提示

$1\le t\le 100$  
$1\le n,m\le 2\times 10^5$  
$\sum n\times m\le 2\times 10^5$  
表格中的每一个数不超过 $10^9$  

**样例解释**  
**第一个**表格原本就是好的，因此可以将第一列和自己对调。  

**第二个**表格中，对调第 $1$ 和第 $2$ 列，会变成  
$$1,4$$  
$$3,2$$  
不是好的。如果对调任意一列和它自己，就是原本的表格，不是好的。因此输出`-1`。  

**第三个**表格中，对调第 $1$，$2$ 列，表格变为  
$$1,2$$
$$1,1$$
是好的。因此输出`1 2`。  

**第四个**表格中，调换第 $1$，$3$ 列，表格变为  
$$1,2,6$$  
$$3,4,5$$  
表格变为好的。输出 `1 3`  

**最后一个**表格中，每一行只有一个数，是单调不降的，但是只有一列，所以需要将这一列和自己对调。

## 样例 #1

### 输入

```
5
2 3
1 2 3
1 1 1
2 2
4 1
2 3
2 2
2 1
1 1
2 3
6 2 1
5 4 3
2 1
1
2
```

### 输出

```
1 1
-1
1 2
1 3
1 1
```



---

---
title: "Fishingprince Plays With Array"
layout: "post"
diff: 普及/提高-
pid: CF1696C
tag: ['模拟', '数学', '贪心', '构造']
---

# Fishingprince Plays With Array

## 题目描述

Fishingprince is playing with an array $ [a_1,a_2,\dots,a_n] $ . He also has a magic number $ m $ .

He can do the following two operations on it:

- Select $ 1\le i\le n $ such that $ a_i $ is divisible by $ m $ (that is, there exists an integer $ t $ such that $ m \cdot t = a_i $ ). Replace $ a_i $ with  $ m $ copies of $ \frac{a_i}{m} $ . The order of the other elements doesn't change. For example, when $ m=2 $ and $ a=[2,3] $ and $ i=1 $ , $ a $ changes into $ [1,1,3] $ .
- Select $ 1\le i\le n-m+1 $ such that $ a_i=a_{i+1}=\dots=a_{i+m-1} $ . Replace these $ m $ elements with a single $ m \cdot a_i $ . The order of the other elements doesn't change. For example, when $ m=2 $ and $ a=[3,2,2,3] $ and $ i=2 $ , $ a $ changes into $ [3,4,3] $ .

Note that the array length might change during the process. The value of $ n $ above is defined as the current length of the array (might differ from the $ n $ in the input).

Fishingprince has another array $ [b_1,b_2,\dots,b_k] $ . Please determine if he can turn $ a $ into $ b $ using any number (possibly zero) of operations.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \le t \le 10^4 $ ). Description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1\le n\le 5\cdot 10^4 $ , $ 2\le m\le 10^9 $ ).

The second line of each test case contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 1\le a_i\le 10^9 $ ).

The third line of each test case contains one integer $ k $ ( $ 1\le k\le 5\cdot 10^4 $ ).

The fourth line of each test case contains $ k $ integers $ b_1,b_2,\ldots,b_k $ ( $ 1\le b_i\le 10^9 $ ).

It is guaranteed that the sum of $ n+k $ over all test cases does not exceed $ 2\cdot 10^5 $ .

## 输出格式

For each testcase, print Yes if it is possible to turn $ a $ into $ b $ , and No otherwise. You can print each letter in any case (upper or lower).

## 说明/提示

In the first test case of the sample, we can do the second operation with $ i=2 $ : $ [1,\color{red}{2,2},4,2]\to [1,\color{red}{4},4,2] $ .

In the second testcase of the sample, we can:

- do the second operation with $ i=2 $ : $ [1,\color{red}{2,2},8,2,2]\to [1,\color{red}{4},8,2,2] $ .
- do the second operation with $ i=4 $ : $ [1,4,8,\color{red}{2,2}]\to [1,4,8,\color{red}{4}] $ .
- do the first operation with $ i=3 $ : $ [1,4,\color{red}{8},4]\to [1,4,\color{red}{4,4},4] $ .
- do the second operation with $ i=2 $ : $ [1,\color{red}{4,4},4,4]\to [1,\color{red}{8},4,4] $ .
- do the second operation with $ i=3 $ : $ [1,8,\color{red}{4,4}]\to [1,8,\color{red}{8}] $ .
- do the second operation with $ i=2 $ : $ [1,\color{red}{8,8}]\to [1,\color{red}{16}] $ .

## 样例 #1

### 输入

```
5
5 2
1 2 2 4 2
4
1 4 4 2
6 2
1 2 2 8 2 2
2
1 16
8 3
3 3 3 3 3 3 3 3
4
6 6 6 6
8 3
3 9 6 3 12 12 36 12
16
9 3 2 2 2 3 4 12 4 12 4 12 4 12 4 4
8 3
3 9 6 3 12 12 36 12
7
12 2 4 3 4 12 56
```

### 输出

```
Yes
Yes
No
Yes
No
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
title: "Card Game"
layout: "post"
diff: 普及/提高-
pid: CF1932D
tag: ['模拟', '贪心']
---

# Card Game

## 题目描述

两名玩家正在玩在线纸牌游戏。游戏使用一副  $32$ 张牌进行。每张牌都有花色和数字。有四种花色：梅花、方块、红心和黑桃。用字符 `C`、`D`、`H` 和 `S` 分别表示它们。共有 8 种数字，按递增顺序为 `2`、`3`、`4`、`5`、`6`、`7`、`8`、`9`。

每张牌由两个字母表示：其等级和花色。例如，红心 8 可以表示为 `8H`。

在游戏开始时，会选择一种花色作为王牌花色。

在每一轮中，玩家的操作如下：第一个玩家在桌子上放一张牌，第二个玩家必须用自己的一张牌打败这张牌。之后，两张牌都被移动到弃牌堆中。

一张牌可以打败另一张牌，如果两张牌都具有相同的花色，并且第一张牌的等级比第二张牌高。例如，方块 8 可以打败方块 4。此外，王牌可以打败任何非王牌牌，无论牌的等级如何，例如，如果王牌花色是梅花 (`C`)，那么梅花 3 可以打败方块 9。请注意，王牌只能被等级更高的王牌打败。

游戏中进行了 $n$ 轮，因此弃牌堆现在包含 $2n$ 张牌。你想要重建游戏中进行的轮次，但是弃牌堆中的牌已经洗牌。找到可能在游戏中玩过的 $n$ 轮的任何可能顺序。

## 输入格式

第一行包含整数 $t$（$1\le t\le100$），表示测试数据数量。接下来是 $t$ 个测试数据。

每个测试数据的第一行包含整数 $n$（$1\le n\le16$）。

每个测试数据的第二行包含一个字符，即王牌花色。它是 `CDHS` 中的一个。

每个测试数据的第三行包含 $2n$ 张牌的描述。每张牌由一个两个字符的字符串描述，第一个字符是牌的等级，是 `23456789` 中的一个，第二个字符是牌的花色，是 `CDHS` 中的一个。所有牌都是不同的。

## 输出格式

对于每个测试用例，输出答案：

打印 $n$ 行。在每一行中，以与输入相同的格式打印两张牌的描述：第一张牌是第一个玩家打出的牌，然后是第二个玩家用来打败它的牌。
如果没有解决方案，则打印一行 `IMPOSSIBLE`。
如果有多个解决方案，则打印其中任何一个。

## 样例 #1

### 输入

```
8
3
S
3C 9S 4C 6D 3S 7S
2
C
3S 5D 9S 6H
1
H
6C 5D
1
S
7S 3S
1
H
9S 9H
1
S
9S 9H
1
C
9D 8H
2
C
9C 9S 6H 8C
```

### 输出

```
3C 4C
6D 9S
3S 7S
IMPOSSIBLE
IMPOSSIBLE
3S 7S
9S 9H
9H 9S
IMPOSSIBLE
6H 9C
9S 8C
```



---

---
title: "Nearly Shortest Repeating Substring"
layout: "post"
diff: 普及/提高-
pid: CF1950E
tag: ['模拟', '数论']
---

# Nearly Shortest Repeating Substring

## 题目描述

You are given a string $ s $ of length $ n $ consisting of lowercase Latin characters. Find the length of the shortest string $ k $ such that several (possibly one) copies of $ k $ can be concatenated together to form a string with the same length as $ s $ and, at most, one different character.

More formally, find the length of the shortest string $ k $ such that $ c = \underbrace{k + \cdots + k}_{x\rm\ \text{times}} $ for some positive integer $ x $ , strings $ s $ and $ c $ has the same length and $ c_i \neq s_i $ for at most one $ i $ (i.e. there exist $ 0 $ or $ 1 $ such positions).

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^3 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \leq n \leq 2\cdot10^5 $ ) — the length of string $ s $ .

The second line of each test case contains the string $ s $ , consisting of lowercase Latin characters.

The sum of $ n $ over all test cases does not exceed $ 2\cdot10^5 $ .

## 输出格式

For each test case, print the length of the shortest string $ k $ satisfying the constraints in the statement.

## 说明/提示

In the first test case, you can select $ k = \texttt{a} $ and $ k+k+k+k = \texttt{aaaa} $ , which only differs from $ s $ in the second position.

In the second test case, you cannot select $ k $ of length one or two. We can have $ k = \texttt{abba} $ , which is equal to $ s $ .

## 样例 #1

### 输入

```
5
4
abaa
4
abba
13
slavicgslavic
8
hshahaha
20
stormflamestornflame
```

### 输出

```
1
4
13
2
10
```



---

---
title: "Playing Quidditch (Easy)"
layout: "post"
diff: 普及/提高-
pid: CF1970F1
tag: ['模拟']
---

# Playing Quidditch (Easy)

## 题目描述

今天下午，你打算出去散步，享受春天的第一缕阳光。在靠近魁地奇球场时，你听到了争吵声。原来是比赛比分又引起了争议，两队都坚信自己赢得了比赛！为了避免这种事情再次发生，你决定参与到比赛的裁判工作中。

现在，你将在体育场内观看比赛并计算得分。比赛结束后，你将宣布胜者。

今天参赛的有两支队伍：红色的格兰芬多队（R）和蓝色的拉文克劳队（B）。每支队伍由 $P$ 名球员组成（$1 \leq P \leq 10$）。

比赛的场地是一个由 $N$ 行 $M$ 列组成的矩形（$3 \leq N, M \leq 99$，且 $N$ 和 $M$ 是奇数）。场上所有位置均为整数，多名球员或多个物体可以占据同一个位置。比赛开始时，场地上有双方队伍的目标（每队可拥有1至5个目标），球员，以及一个鬼飞球。其他种类的球将在更复杂的问题中涉及。

比赛分为 $T$ 步（$0 \leq T \leq 10000$）。每一步中，场上的一个实体（球员或球）将执行一个动作。所有的实体都能移动。球员还可以接球或投掷他们携带的鬼飞球。要接球，球员需要和球在同一个位置。当球员携带鬼飞球时，球只会跟随他的移动，而不会执行其他动作。如果球员决定投掷鬼飞球，它就留在当前的位置。

得分的条件是，球员必须将鬼飞球放入对方队伍的目标中。成功时，该球员所在的队伍就会得一分，而鬼飞球会立刻返回到场地的正中央（即第 $(M+1)/2$ 列和第 $(N+1)/2$ 行的位置，从 1 开始计数）。场中心没有目标。如果球员不小心将球放进了自己的目标中，那么对方队伍会得一分。

## 输入格式

第一行给出两个整数 $N$ 和 $M$。

接下来是场地布局：共 $N$ 行，每行包含 $M$ 对字符，以空格分隔。每个字符对表示场上的一个位置，可能是以下情况之一：

- .. 代表一个空白位置
- R0, ..., R9, B0, ..., B9 代表一位球员。第一个字符表示队伍，第二个字符是该球员在队伍中的编号。每个字符对是唯一的，但不保证所有字符对都会出现在网格中。
- RG 或 BG 代表一个目标。蓝队需要将球投入红队的目标（RG），而红队需要将球投进蓝队的目标（BG）。
- .Q 代表鬼飞球，这是供球员用来得分的球。

接下来的一行是整数 $T$，表示比赛的步数。接下来的 $T$ 行，每行描述一个动作。每行包含几个用空格分隔的信息。第一个是执行动作的实体的字符对，接着是动作描述：

- U, D, L, R 分别表示向上、向下、向左、向右移动。每次只能移动一个格子。
- C 表示球员接球（只有球员可以接球）。随后是一个空格，接着是一对字符，表示被接住的球。因为在将来的版本中，可能会在同一个格子中有多个球。
- T 表示球员投掷他们携带的鬼飞球。

所有的动作都是有效的：球员不离开场地，不在不同位置接球，不在未携带鬼飞球时投掷它，等等。

## 输出格式

你需要描述比赛中的重要事件，每个事件占一行。具体来说：

- 每次得分后，你必须打印 t RED GOAL 或 t BLUE GOAL，其中 t 是行动在列表中的位置（从 0 开始）。如果得分是在球员自己的目标中（红队员向红目标得分或蓝队员向蓝目标得分），则打印得分的是另一队伍。

事��需按 t 的升序输出。

比赛结束后，你必须输出最终比分：`FINAL SCORE: r b`，其中 r 是红队的得分，b 是蓝队的得分。

## 说明/提示

在第一个示例中，一名蓝队球员走到网格中心收球，然后带球前往红色队的目标并成功得分！鬼飞球回到场地中心，随后一个红队球员也拿球成功得分。

在第二个示例中，红队球员拿到鬼飞球，移动并投掷，随后由蓝队球员接过，带球前往红队目标并得分。

在第三个例子中，红队球员将球投入自己的目标，因此蓝队得分。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5 5
.. R1 .. B1 ..
RG .. .. .. BG
RG R0 .Q B0 BG
RG .. .. .. BG
.. R2 .. B2 ..
13
B2 U
B2 U
B2 L
B2 C .Q
B2 L
B2 L
B2 T
R0 R
R0 C .Q
R0 D
R0 R
R0 R
R0 T
```

### 输出

```
6 BLUE GOAL
12 RED GOAL
FINAL SCORE: 1 1
```

## 样例 #2

### 输入

```
3 5
.. .. R0 .. ..
RG .. .Q .. BG
.. .. B0 .. ..
12
R0 D
R0 C .Q
R0 R
R0 T
R0 D
B0 R
B0 U
B0 C .Q
B0 L
B0 L
B0 L
B0 T
```

### 输出

```
11 BLUE GOAL
FINAL SCORE: 0 1
```

## 样例 #3

### 输入

```
3 5
.. .. R0 .. ..
RG .. .Q .. BG
.. .. B0 .. ..
5
R0 D
R0 C .Q
R0 L
R0 L
R0 T
```

### 输出

```
4 BLUE GOAL
FINAL SCORE: 0 1
```



---

---
title: "Ingenuity-2"
layout: "post"
diff: 普及/提高-
pid: CF1974D
tag: ['模拟', '贪心']
---

# Ingenuity-2

## 题目描述

Let's imagine the surface of Mars as an infinite coordinate plane. Initially, the rover Perseverance-2 and the helicopter Ingenuity-2 are located at the point with coordinates $ (0, 0) $ . A set of instructions $ s $ consisting of $ n $ instructions of the following types was specially developed for them:

- N: move one meter north (from point $ (x, y) $ to $ (x, y + 1) $ );
- S: move one meter south (from point $ (x, y) $ to $ (x, y - 1) $ );
- E: move one meter east (from point $ (x, y) $ to $ (x + 1, y) $ );
- W: move one meter west (from point $ (x, y) $ to $ (x - 1, y) $ ).

Each instruction must be executed either by the rover or by the helicopter. Moreover, each device must execute at least one instruction. Your task is to distribute the instructions in such a way that after executing all $ n $ instructions, the helicopter and the rover end up at the same point, or determine that this is impossible.

## 输入格式

The first line of input contains $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the number of instructions.

The second line of each test case contains a string $ s $ of length $ n $ consisting of the characters 'N', 'S', 'E', 'W' — the sequence of instructions.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10 ^ 5 $ .

## 输出格式

For each test case, if the required distribution of instructions exists, output a string $ p $ of length $ n $ consisting of the characters 'R', 'H'. If the $ i $ -th operation should be executed by the rover, then $ p_i=\text{R} $ , if the $ i $ -th operation should be executed by the helicopter, then $ p_i=\text{H} $ . If there are multiple solutions, output any of them.

Otherwise, output NO.

## 说明/提示

Let's consider the first example: the string $ S = \texttt{NENSNE} $ . One of the possible solutions, shown in the figure below, is $ p = \texttt{RRHRRH} $ , using which both the rover and the helicopter will end up one meter north and one meter east.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1974D/6e8d0f788b954d2ceff54878d55afda06efd52c8.png)For WWW, the solution is impossible.

## 样例 #1

### 输入

```
10
6
NENSNE
3
WWW
6
NESSWS
2
SN
2
WE
4
SSNN
4
WESN
2
SS
4
EWNN
4
WEWE
```

### 输出

```
RRHRRH
NO
HRRHRH
NO
NO
RHRH
RRHH
RH
RRRH
RRHH
```



---

---
title: "World Football Cup"
layout: "post"
diff: 普及/提高-
pid: CF19A
tag: ['模拟', '排序']
---

# World Football Cup

## 题目描述

## 题意
众所周知，2010 年 FIFA 世界杯在南非举行。BFA 决定下一届世界杯将在伯兰德举行。BFA 决定改变世界杯的一些规定：  

- 最后的比赛涉及 $n$ 支球队（$n$ 总是偶数）；
- 前 $\frac{n}{2}$ 队（根据排名）进入淘汰赛阶段。

积分榜是按照以下原则制作的：胜利一个队得 $3$ 分，平分 $1$ 分，失败 $0$ 分。首先，球队按积分顺序排在积分榜上，分数相等比较净胜球，净胜球相等比较进球数。

你被要求写一个程序，通过给定的比赛名单和所有比赛的结果，找到设法进入淘汰赛阶段的球队名单。

## 输入格式

第一个输入行包含唯一的整数 $n(1 \le n \le 50)$表示参加世界杯决赛的球队数量。 

以下 $n$ 行，包含这些团队的名称，名称是一个包含小写和大写拉丁字母的字符串，其长度不超过 $30$ 个字符。

以下的 $\frac{n\times(n-1)}{2}$ 行描述格式为 $\text{name1-name2  num1:num2}$，其中 $\text{name1,name2}$ 为团队名称；$\text{num1,num2} (0 \le \text{num1,num2} \le 100) $ 为相应的队伍得分。 数据保证没有两支球队名字相同，没有比赛一个球队与自己打球，任意两个球队只会比赛一次。

## 输出格式

按照字典顺序输出 $\frac{n}{2}$ 行进入淘汰赛阶段的球队的名字，在一个单独的行中输出每支球队名称。数据保证结果唯一。
Translated by @Youngsc、@艾因斯坦

## 样例 #1

### 输入

```
4
A
B
C
D
A-B 1:1
A-C 2:2
A-D 1:0
B-C 1:0
B-D 0:3
C-D 0:3

```

### 输出

```
A
D

```

## 样例 #2

### 输入

```
2
a
A
a-A 2:1

```

### 输出

```
a

```



---

---
title: "Colored Portals"
layout: "post"
diff: 普及/提高-
pid: CF2004D
tag: ['模拟', '图论', '贪心']
---

# Colored Portals

## 题目描述

一条直线上有 $n$ 个城市，这些城市的编号为 $1$ 到 $n$。

传送门被用于在城市间移动，传送门有四种颜色：蓝色，绿色，红色和黄色。每一个城市都有两种颜色的传送门。你可以从城市 $i$ 到城市 $j$，当且仅当这两个城市存在同色的传送门（例如，你可以从有红色和蓝色的传送门的城市到有蓝色和绿色传送门的城市），花费 $|i - j|$ 个硬币。

你的任务是回答 $q$ 个询问：计算城市 $x$ 到城市 $y$ 的最小花费。

## 输入格式

第一行输入 $t$（$1\le t \le 10^4$），代表测试数据的组数。

对于每个测试数据，第一行输入 $n,q$（$1\le n,q \le2 \times 10^5$），表示城市数和询问数。

第二行输入 $n$ 个只能为 `BG`，`BR`，`BY`，`GR`，`GY`，`RY` 之一的字符串，第 $i$ 个表示城市 $i$ 有的传送门颜色，`B` 表示蓝色，`G` 表示绿色，`R` 表示红色，`Y` 表示黄色。

接下来 $q$ 行第 $j$ 行输入 $x_j,y_j$（$1 \le x_j,y_j \le n$），表示第 $j$ 个询问的 $x,y$。

输入保证所有测试数据中 $n$ 的和不超过 $2 \times 10^5$，$q$ 的和不超过 $2 \times 10 ^ 5$。

## 输出格式

对每个询问，输出一个整数，即从城市 $x$ 到城市 $y$ 的最小花费（若无解输出 $-1$）。

## 样例 #1

### 输入

```
2
4 5
BR BR GY GR
1 2
3 1
4 4
1 4
4 2
2 1
BG RY
1 2
```

### 输出

```
1
4
0
3
2
-1
```



---

---
title: "Dubstep"
layout: "post"
diff: 普及/提高-
pid: CF208A
tag: ['模拟', '字符串', '枚举']
---

# Dubstep

## 题目描述

## 题目翻译
Vasya有一句歌词(可能含有空格)，他在第一个单词之前和最后一个单词之后加上若干(可以为0)个"WUB",再每个单词之间加上若干(至少为1)个"WUB"，转变成一个新的字符串(无空格)
如"I AM X" 可以变成 "WUBWUBIWUBAMWUBWUBX" 而不能变成 "WUBWUBIAMWUBX"
现在给出转变后的字符串，求出原来的字符串

## 输入格式

输入包括一个非空字符串SSS，其中SSS仅由大写字母组成并且的长度不超过200
保证原来的字符串不含有"WUB"并且至少有一个单词

## 输出格式

输出转变前的字符串，每个单词用空格分隔

## 样例 #1

### 输入

```
WUBWUBABCWUB

```

### 输出

```
ABC 
```

## 样例 #2

### 输入

```
WUBWEWUBAREWUBWUBTHEWUBCHAMPIONSWUBMYWUBFRIENDWUB

```

### 输出

```
WE ARE THE CHAMPIONS MY FRIEND 
```



---

---
title: "Flower Boy"
layout: "post"
diff: 普及/提高-
pid: CF2106D
tag: ['模拟', '贪心']
---

# Flower Boy

## 题目描述

花之少年有一个由 $n$ 朵花组成的花园，这些花可以表示为一个整数序列 $a_1, a_2, \dots, a_n$，其中 $a_i$ 表示从左数第 $i$ 朵花的美丽值。

伊戈尔想要收集恰好 $m$ 朵花。为此，他将从左到右遍历花园，并决定是否收集当前位置的花。他收集的第 $i$ 朵花的美丽值必须至少为 $b_i$。

伊戈尔发现，有时可能无法收集满足美丽值要求的 $m$ 朵花。因此，在开始收集之前，他可以选择任意一个整数 $k$，使用魔法棒培育一朵美丽值为 $k$ 的新花，并将其放置在花园中的任意位置（两朵花之间、第一朵花之前或最后一朵花之后）。由于魔法能力有限，他最多只能执行一次这个操作。

请输出伊戈尔执行上述操作时需要选择的最小整数 $k$，以确保他能收集到 $m$ 朵花。如果不需要操作就能收集 $m$ 朵花，则输出 $0$。如果即使执行操作也无法收集 $m$ 朵花，则输出 $-1$。

## 输入格式

输入的第一行包含一个整数 $t$（$1 \le t \le 10^4$）——测试用例的数量。

每个测试用例的第一行包含两个整数 $n$ 和 $m$（$1 \le m \le n \le 2 \cdot 10^5$）——分别表示花园中的花朵数量和伊戈尔想要收集的花朵数量。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, ..., a_n$（$1 \le a_i \le 10^9$）——表示从左数第 $i$ 朵花的美丽值。

每个测试用例的第三行包含 $m$ 个整数 $b_1, b_2, ..., b_m$（$1 \le b_i \le 10^9$）——表示伊戈尔收集的第 $i$ 朵花必须满足的最小美丽值。

保证所有测试用例的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式

对于每个测试用例，输出一行，表示伊戈尔执行操作时需要选择的最小整数 $k$。如果不需要操作，则输出 $0$；如果即使执行操作也无法满足条件，则输出 $-1$。


## 说明/提示

在第一个测试用例中，假设伊戈尔培育了一朵美丽值为 $6$ 的花，并将其放置在第三朵和第四朵花之间。此时花园变为 $[3, 5, 2, 6, 3, 3, 5, 8, 1, 2]$。然后，他可以选择第二、第四、第六、第七和第八朵花，其美丽值分别为 $[5, 6, 3, 5, 8]$。

在第三个测试用例中，他可以培育一朵美丽值为 $7$ 的花，并将其放在第一朵花之前。此时花园变为 $[7, 4, 3, 5, 4, 3]$。现在，他可以选择第一、第二和第四朵花。

在第四个测试用例中，伊戈尔不需要执行操作，因此答案为 $0$。

在第六个测试用例中，无论伊戈尔如何操作，都无法收集到 $3$ 朵满足美丽值要求的花，因此答案为 $-1$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
7
9 5
3 5 2 3 3 5 8 1 2
4 6 2 4 6
6 3
1 2 6 8 2 1
5 4 3
5 3
4 3 5 4 3
7 4 5
6 3
8 4 2 1 2 5
6 1 4
5 5
1 2 3 4 5
5 4 3 2 1
6 3
1 2 3 4 5 6
9 8 7
5 5
7 7 6 7 7
7 7 7 7 7
```

### 输出

```
6
3
7
0
-1
-1
7
```



---

---
title: "Red Light, Green Light (Easy version)"
layout: "post"
diff: 普及/提高-
pid: CF2118D1
tag: ['模拟', '数学', '图论']
---

# Red Light, Green Light (Easy version)

## 题目描述

**这是问题的简单版本。不同版本的区别在于对 $k$ 和单个测试点中的 $n,q$ 总和的限制不同。**

给你一个长度为 $10^{15}$ 的长条和一个常数 $k$。在长条上有 $n$ 个格子上有一个信号灯，第 $i$ 个信号灯在格子 $p_i$ 处，同时具有一个初相 $d_i<k$。第 $i$ 个信号灯将在时刻 $z\times k+d_i,z$ 为整数时亮红灯，其他时刻亮绿灯。

时刻 $0$ 时你在某个格子处，面向正方向。每个时刻你将执行如下操作：
- 如果你所在的格子上有一个红色的信号灯，转向；
- 向你所面向的方向走一格。

你要处理 $q$ 个询问，询问给出时刻 $0$ 时你在格子 $a_i$，问时刻 $10^{100}$ 你是否已经走出长条的范围。

## 输入格式

多组数据。第一行一个整数 $t(1\le t\le 500)$，表示数据组数。

对于每组数据：第一行两个整数 $n,k(1\le n,k\le 500)$。\
第二行 $n$ 个整数 $p_1,p_2,\cdots,p_n(1\le p_1<p_2\cdots<p_n\le 10^{15})$。\
第三行 $n$ 个整数 $d_1,d_2,\cdots,d_n(0\le d_i<k)$。\
第四行一个整数 $q(1\le q\le 500)$。\
第五行 $q$ 个整数 $a_1,a_2,\cdots,a_q(1\le a_i\le 10
^{15})$。

保证单个测试点中 $\sum n,\sum q\le 500$。

## 输出格式

对于每组数据，输出 $q$ 行，第 $i$ 个询问结果为是则在第 $i$ 行输出 `YES`，否则输出 `NO`。你可以以任意形式输出答案（大写或小写）。例如，`yEs`，`yes`，`Yes` 和 `YES` 均是符合条件的输出。

## 说明/提示

对于第一组数据，从 $1,2,3$ 出发的情况如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2118D2/ce9b61d8441ec2687644e4fcb1ecf9c698d0d9de.png)

对于第二组数据，从 $2$ 出发的情况如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2118D2/b6fc75687c6b2b664c445b1824b01121fde0aaa1.png)

## 样例 #1

### 输入

```
4
2 2
1 4
1 0
3
1 2 3
9 4
1 2 3 4 5 6 7 8 9
3 2 1 0 1 3 3 1 1
5
2 5 6 7 8
4 2
1 2 3 4
0 0 0 0
4
1 2 3 4
3 4
1 2 3
3 1 1
3
1 2 3
```

### 输出

```
YES
NO
YES
YES
YES
YES
NO
NO
YES
YES
NO
NO
YES
NO
YES
```



---

---
title: "Sponsor of Your Problems"
layout: "post"
diff: 普及/提高-
pid: CF2121E
tag: ['模拟', '随机化']
---

# Sponsor of Your Problems

## 题目描述

For two integers $ a $ and $ b $ , we define $ f(a, b) $ as the number of positions in the decimal representation of the numbers $ a $ and $ b $ where their digits are the same. For example, $ f(12, 21) = 0 $ , $ f(31, 37) = 1 $ , $ f(19891, 18981) = 2 $ , $ f(54321, 24361) = 3 $ .

You are given two integers $ l $ and $ r $ of the same length in decimal representation. Consider all integers $ l \leq x \leq r $ . Your task is to find the minimum value of $ f(l, x) + f(x, r) $ .

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The description of the test cases follows.

Each test case consists of a single line containing two integers $ l $ and $ r $ ( $ 1 \leq l \leq r < 10^9 $ ).

It is guaranteed that the numbers $ l $ and $ r $ have the same length in decimal representation and do not have leading zeros.

## 输出格式

For each test case, output the minimum value of $ f(l, x) + f(x, r) $ among all integer values $ l \leq x \leq r $ .

## 说明/提示

In the first test case, you can choose $ x = 1 $ . Then $ f(1, 1) + f(1, 1) = 1 + 1 = 2 $ .

In the second test case, you can choose $ x = 2 $ . Then $ f(2, 2) + f(2, 3) = 1 + 0 = 1 $ .

In the third test case, you can choose $ x = 5 $ . Then $ f(4, 5) + f(5, 6) = 0 + 0 = 0 $ .

In the fourth test case, you can choose $ x = 15 $ . Then $ f(15, 15) + f(15, 16) = 2 + 1 = 3 $ .

In the fifth test case, you can choose $ x = 18 $ . Then $ f(17, 18) + f(18, 19) = 1 + 1 = 2 $ .

In the sixth test case, you can choose $ x = 200 $ . Then $ f(199, 200) + f(200, 201) = 0 + 2 = 2 $ .

In the seventh test case, you can choose $ x = 900 $ . Then $ f(899, 900) + f(900, 999) = 0 + 1 = 1 $ .

In the eighth test case, you can choose $ x = 1992 $ . Then $ f(1990, 1992) + f(1992, 2001) = 3 + 0 = 3 $ .

## 样例 #1

### 输入

```
14
1 1
2 3
4 6
15 16
17 19
199 201
899 999
1990 2001
6309 6409
12345 12501
19987 20093
746814 747932
900990999 900991010
999999999 999999999
```

### 输出

```
2
1
0
3
2
2
1
3
3
4
3
5
12
18
```



---

---
title: "Champions' League"
layout: "post"
diff: 普及/提高-
pid: CF234E
tag: ['模拟', '排序']
---

# Champions' League

## 题目描述

In the autumn of this year, two Russian teams came into the group stage of the most prestigious football club competition in the world — the UEFA Champions League. Now, these teams have already started to play in the group stage and are fighting for advancing to the playoffs. In this problem we are interested in the draw stage, the process of sorting teams into groups.

The process of the draw goes as follows (the rules that are described in this problem, are somehow simplified compared to the real life). Suppose $ n $ teams will take part in the group stage ( $ n $ is divisible by four). The teams should be divided into groups of four. Let's denote the number of groups as $ m $ (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/65e4300bd0cdae46f7d260b1389d3b214f9ce521.png)). Each team has a rating — an integer characterizing the team's previous achievements. The teams are sorted by the rating's decreasing (no two teams have the same rating).

After that four "baskets" are formed, each of which will contain $ m $ teams: the first $ m $ teams with the highest rating go to the first basket, the following $ m $ teams go to the second one, and so on.

Then the following procedure repeats $ m-1 $ times. A team is randomly taken from each basket, first from the first basket, then from the second, then from the third, and at last, from the fourth. The taken teams form another group. After that, they are removed from their baskets.

The four teams remaining in the baskets after $ (m-1) $ such procedures are performed, form the last group.

In the real draw the random selection of teams from the basket is performed by people — as a rule, the well-known players of the past. As we have none, we will use a random number generator, which is constructed as follows. Its parameters are four positive integers $ x,a,b,c $ . Every time there is a call to the random number generator, it produces the following actions:

- calculates ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/2fe2894178b5b7478ae2269aae243e7c851b6173.png);
- replaces parameter $ x $ by value $ y $ (assigns ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/72e8070934423a6837039e7a1e2f312765ec26ab.png));
- returns $ x $ as another random number.

Operation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/99fd5677ca5c02520be7595d9b1eaf3e9972e601.png) means taking the remainder after division: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/c19545677f47a50d181dd7b00e822282597427db.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/770f8dc8f9b95dc42d2401b09019f707ad7418fc.png).

A random number generator will be used in the draw as follows: each time we need to randomly choose a team from the basket, it will generate a random number $ k $ . The teams that yet remain in the basket are considered numbered with consecutive integers from $ 0 $ to $ s-1 $ , in the order of decreasing rating, where $ s $ is the current size of the basket. Then a team number ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/65912cf5ed5c94787700c166a6eeb79e0114a14b.png) is taken from the basket.

Given a list of teams and the parameters of the random number generator, determine the result of the draw.

## 输入格式

The first input line contains integer $ n $ ( $ 4<=n<=64 $ , $ n $ is divisible by four) — the number of teams that take part in the sorting. The second line contains four space-separated integers $ x,a,b,c $ ( $ 1<=x,a,b,c<=1000 $ ) — the parameters of the random number generator. Each of the following $ n $ lines describes one team. The description consists of the name of the team and its rating, separated by a single space. The name of a team consists of uppercase and lowercase English letters and has length from 1 to 20 characters. A team's rating is an integer from 0 to 1000. All teams' names are distinct. All team's ratings are also distinct.

## 输出格式

Print the way the teams must be sorted into groups. Print the groups in the order, in which they are formed in the sorting. Number the groups by consecutive uppercase English letters, starting from letter 'A'. Inside each group print the teams' names one per line, in the order of decreasing of the teams' rating. See samples for a better understanding of the output format.

## 说明/提示

In the given sample the random number generator will be executed four times:

- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/fe99c797dbb307d601e0f59e424f6250c45a7d38.png),
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/baa288fe7b8d960b815b5367ff1126e08e6c706b.png),
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/81b191782fc61308d51cf88ac0aba6c561fc0212.png),
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF234E/549ef2ab2cbb05e99d689f6ca803b6fab657873d.png).

## 样例 #1

### 输入

```
8
1 3 1 7
Barcelona 158
Milan 90
Spartak 46
Anderlecht 48
Celtic 32
Benfica 87
Zenit 79
Malaga 16

```

### 输出

```
Group A:
Barcelona
Benfica
Spartak
Celtic
Group B:
Milan
Zenit
Anderlecht
Malaga

```



---

---
title: "F1 Champions"
layout: "post"
diff: 普及/提高-
pid: CF24B
tag: ['模拟']
---

# F1 Champions

## 题目描述

Formula One championship consists of series of races called Grand Prix. After every race drivers receive points according to their final position. Only the top 10 drivers receive points in the following order 25, 18, 15, 12, 10, 8, 6, 4, 2, 1. At the conclusion of the championship the driver with most points is the champion. If there is a tie, champion is the one with most wins (i.e. first places). If a tie still exists, it is chosen the one with most second places, and so on, until there are no more place to use for compare.

 Last year another scoring system was proposed but rejected. In it the champion is the one with most wins. If there is tie, champion is the one with most points. If a tie still exists it is proceeded the same way as in the original scoring system, that is comparing number of second, third, forth, and so on, places.

You are given the result of all races during the season and you are to determine the champion according to both scoring systems. It is guaranteed, that both systems will produce unique champion.

## 输入格式

The first line contain integer $ t $ ( $ 1<=t<=20 $ ), where $ t $ is the number of races. After that all races are described one by one. Every race description start with an integer $ n $ ( $ 1<=n<=50 $ ) on a line of itself, where $ n $ is the number of clasified drivers in the given race. After that $ n $ lines follow with the classification for the race, each containing the name of a driver. The names of drivers are given in order from the first to the last place. The name of the driver consists of lowercase and uppercase English letters and has length at most 50 characters. Comparing of names should be case-sensetive.

## 输出格式

Your output should contain exactly two line. On the first line is the name of the champion according to the original rule, and on the second line the name of the champion according to the alternative rule.

## 说明/提示

It is not guaranteed that the same drivers participate in all races. For the championship consider every driver that has participated in at least one race. The total number of drivers during the whole season is not more then $ 50 $ .

## 样例 #1

### 输入

```
3
3
Hamilton
Vettel
Webber
2
Webber
Vettel
2
Hamilton
Vettel

```

### 输出

```
Vettel
Hamilton

```

## 样例 #2

### 输入

```
2
7
Prost
Surtees
Nakajima
Schumacher
Button
DeLaRosa
Buemi
8
Alonso
Prost
NinoFarina
JimClark
DeLaRosa
Nakajima
Patrese
Surtees

```

### 输出

```
Prost
Prost

```



---

---
title: "Winner"
layout: "post"
diff: 普及/提高-
pid: CF2A
tag: ['模拟', '字符串', '概率论', '栈']
---

# Winner

## 题目描述

在 Berland 流行着纸牌游戏 `Berlogging`，这个游戏的赢家是根据以下规则确定的：

1. 在每一轮中，玩家获得或失去一定数量的分数，在游戏过程中，分数被记录在 `名称和得分` 行中，其中名字是玩家的名字，得分是在这一轮中获得的分数。得分是负值意味着玩家失去了相应的分数。
2. 如果在比赛结束时只有一名玩家分数最多，他就是获胜者。
3. 如果两名或两名以上的玩家在比赛结束时都有最大的分数 $m$ ，那么其中首先获得至少 $m$ 分的玩家胜利。开始时，每个玩家都是 $0$ 分。


保证在比赛结束时至少有一个玩家的分数为正。

## 输入格式

第一行包含整数 $n$，表示是游戏进行的的回合数。

第 $2 \sim n + 1$ 行，按照时间顺序输入 `名称和得分` 行的信息，其中名称是长度不大于 $32$ 的小写字母组成的字符串，分数的绝对值不大于 $1000$。

## 输出格式

输出获胜者的名称。

## 样例 #1

### 输入

```
3
mike 3
andrew 5
mike 2

```

### 输出

```
andrew

```

## 样例 #2

### 输入

```
3
andrew 3
andrew 2
mike 5

```

### 输出

```
andrew

```



---

---
title: "Sysadmin Bob"
layout: "post"
diff: 普及/提高-
pid: CF31B
tag: ['模拟', '字符串']
---

# Sysadmin Bob

## 题目描述

Email address in Berland is a string of the form $ A $ @ $ B $ , where $ A $ and $ B $ are arbitrary strings consisting of small Latin letters.

Bob is a system administrator in «Bersoft» company. He keeps a list of email addresses of the company's staff. This list is as a large string, where all addresses are written in arbitrary order, separated by commas. The same address can be written more than once.

Suddenly, because of unknown reasons, all commas in Bob's list disappeared. Now Bob has a string, where all addresses are written one after another without any separators, and there is impossible to determine, where the boundaries between addresses are. Unfortunately, on the same day his chief asked him to bring the initial list of addresses. Now Bob wants to disjoin addresses in some valid way. Help him to do that.

## 输入格式

The first line contains the list of addresses without separators. The length of this string is between $ 1 $ and $ 200 $ , inclusive. The string consists only from small Latin letters and characters «@».

## 输出格式

If there is no list of the valid (according to the Berland rules) email addresses such that after removing all commas it coincides with the given string, output No solution. In the other case, output the list. The same address can be written in this list more than once. If there are several solutions, output any of them.

## 样例 #1

### 输入

```
a@aa@a

```

### 输出

```
a@a,a@a

```

## 样例 #2

### 输入

```
a@a@a

```

### 输出

```
No solution

```

## 样例 #3

### 输入

```
@aa@a

```

### 输出

```
No solution

```



---

---
title: "Flipping Game"
layout: "post"
diff: 普及/提高-
pid: CF327A
tag: ['模拟', '枚举']
---

# Flipping Game

## 题目描述

Iahub got bored, so he invented a game to be played on paper.

He writes $ n $ integers $ a_{1},a_{2},...,a_{n} $ . Each of those integers can be either 0 or 1. He's allowed to do exactly one move: he chooses two indices $ i $ and $ j $ ( $ 1<=i<=j<=n $ ) and flips all values $ a_{k} $ for which their positions are in range $ [i,j] $ (that is $ i<=k<=j $ ). Flip the value of $ x $ means to apply operation $ x=1 $ - $ x $ .

The goal of the game is that after exactly one move to obtain the maximum number of ones. Write a program to solve the little game of Iahub.

## 输入格式

The first line of the input contains an integer $ n $ ( $ 1<=n<=100 $ ). In the second line of the input there are $ n $ integers: $ a_{1},a_{2},...,a_{n} $ . It is guaranteed that each of those $ n $ values is either 0 or 1.

## 输出格式

Print an integer — the maximal number of 1s that can be obtained after exactly one move.

## 说明/提示

In the first case, flip the segment from 2 to 5 $ (i=2,j=5) $ . That flip changes the sequence, it becomes: \[1 1 1 0 1\]. So, it contains four ones. There is no way to make the whole sequence equal to \[1 1 1 1 1\].

In the second case, flipping only the second and the third element $ (i=2,j=3) $ will turn all numbers into 1.

## 样例 #1

### 输入

```
5
1 0 0 1 0

```

### 输出

```
4

```

## 样例 #2

### 输入

```
4
1 0 0 1

```

### 输出

```
4

```



---

---
title: "Tic-tac-toe"
layout: "post"
diff: 普及/提高-
pid: CF3C
tag: ['模拟', '枚举', '概率论']
---

# Tic-tac-toe

## 题目描述

Certainly, everyone is familiar with tic-tac-toe game. The rules are very simple indeed. Two players take turns marking the cells in a $ 3×3 $ grid (one player always draws crosses, the other — noughts). The player who succeeds first in placing three of his marks in a horizontal, vertical or diagonal line wins, and the game is finished. The player who draws crosses goes first. If the grid is filled, but neither Xs, nor 0s form the required line, a draw is announced.

You are given a $ 3×3 $ grid, each grid cell is empty, or occupied by a cross or a nought. You have to find the player (first or second), whose turn is next, or print one of the verdicts below:

- illegal — if the given board layout can't appear during a valid game;
- the first player won — if in the given board layout the first player has just won;
- the second player won — if in the given board layout the second player has just won;
- draw — if the given board layout has just let to a draw.

## 输入格式

The input consists of three lines, each of the lines contains characters ".", "X" or "0" (a period, a capital letter X, or a digit zero).

## 输出格式

Print one of the six verdicts: first, second, illegal, the first player won, the second player won or draw.

## 样例 #1

### 输入

```
X0X
.0.
.X.

```

### 输出

```
second

```



---

---
title: "Multiplication Table"
layout: "post"
diff: 普及/提高-
pid: CF448D
tag: ['模拟', '二分', '枚举']
---

# Multiplication Table

## 题目描述

Bizon the Champion isn't just charming, he also is very smart.

While some of us were learning the multiplication table, Bizon the Champion had fun in his own manner. Bizon the Champion painted an $ n×m $ multiplication table, where the element on the intersection of the $ i $ -th row and $ j $ -th column equals $ i·j $ (the rows and columns of the table are numbered starting from 1). Then he was asked: what number in the table is the $ k $ -th largest number? Bizon the Champion always answered correctly and immediately. Can you repeat his success?

Consider the given multiplication table. If you write out all $ n·m $ numbers from the table in the non-decreasing order, then the $ k $ -th number you write out is called the $ k $ -th largest number.

## 输入格式

The single line contains integers $ n $ , $ m $ and $ k $ $ (1<=n,m<=5·10^{5}; 1<=k<=n·m) $ .

## 输出格式

Print the $ k $ -th largest number in a $ n×m $ multiplication table.

## 说明/提示

A $ 2×3 $ multiplication table looks like this:

`<br></br>1 2 3<br></br>2 4 6<br></br><br></br>`

## 样例 #1

### 输入

```
2 2 2

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2 3 4

```

### 输出

```
3

```

## 样例 #3

### 输入

```
1 10 5

```

### 输出

```
5

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
title: "Caisa and Sugar"
layout: "post"
diff: 普及/提高-
pid: CF463A
tag: ['模拟']
---

# Caisa and Sugar

## 题目描述

Caisa 要举办一个派对，他要购买巧克力蛋糕的原料。为此，他去了镇上最大的超市。

不巧，他只有 $s$ 美元买食糖。但这可不是悲伤的理由，因为超市里有 $n$ 种食糖，或许他可以买某一个。但这还没完。超市有着非常特别的找零政策：把糖果给买家作为找零，而不是美分。当然，给的糖果的数量始终不会超过 $99$，因为每个卖家都会最大化找零中美元的数量（$100$ 美分可以换成 $1$ 美元）。

Caisa 只想买一种食糖，同时他也希望找零中的糖果数量最多。他最多能得到多少糖果？请注意，Caisa 并不想降低买食糖的开销，他只想得到最多的糖果找零。

## 输入格式

第一行包含两个空格隔开的整数 $n$ 和 $s$ ($1$ $\leq$ $n$，$s$ $\leq$ $100$) 。

接下来 $n$ 行中的第 $i$ 行包含两个整数$x_i$ 和 $y_i$($1$ $\leq$ $x_i$ $\leq$ $100$；$0$ $\leq$ $y_i$ $\lt$ $100$)，分别代表购买第 $i$ 种糖需要多少美元、美分。

## 输出格式

输出一个整数，代表他最多能买到多少糖果。或者，如果他买不起任何一种食糖，则输出 $-1$。

## 说明/提示

在第一个样例中，Caisa 可以买第四种食糖，这种情况下他能得到 $50$ 个糖果找零。

## 样例 #1

### 输入

```
5 10
3 90
12 0
9 70
5 50
7 0

```

### 输出

```
50

```

## 样例 #2

### 输入

```
5 5
10 10
20 20
30 30
40 40
50 50

```

### 输出

```
-1

```



---

---
title: "New Year Book Reading"
layout: "post"
diff: 普及/提高-
pid: CF500C
tag: ['模拟', '贪心', '构造']
---

# New Year Book Reading

## 题目描述

小明非常喜欢读书。他一共有 $n$ 本书，编号为 $1\sim n$，第 $i$本书重 $w_i$。

小明计划在暑假的 $m$ 天里每天读一本书，第 $i$ 天读第 $d_i$ 本书，可能会重复读到同一本书。

因为所有的书都是堆成一摞的，所以每次读某本书之前小明都需要先将这本书上面所有的书搬开，拿出这本书，再将搬开的书按原顺序放回去，消耗体力为搬开书的重量之和，读完这本书后将其放在这摞书的最上面。

小明想知道这 $n$ 本书以怎样的初始顺序放置，所搬书消耗总体力最小。

## 输入格式

第一行两个正整数 $n,m$，表示小明一共有 $n$ 本书，要读 $m$ 天。

第二行 $n$ 个正整数，第 $i$ 个数表示表示第 $i$本书的重量为 $w_i$。

第三行 $m$ 个正整数，第 $i$ 个数表示第 $i$ 天要读第 $d_i$ 本书。

## 输出格式

一行一个数，表示读完 $m$ 次书所搬书消耗的最小体力值。

## 样例 #1

### 输入

```
3 5
1 2 3
1 3 2 3 1

```

### 输出

```
12

```



---

---
title: "Chewbaсca and Number"
layout: "post"
diff: 普及/提高-
pid: CF514A
tag: ['模拟', '字符串']
---

# Chewbaсca and Number

## 题目描述

Luke Skywalker gave Chewbacca an integer number $ x $ . Chewbacca isn't good at numbers but he loves inverting digits in them. Inverting digit $ t $ means replacing it with digit $ 9-t $ .

Help Chewbacca to transform the initial number $ x $ to the minimum possible positive number by inverting some (possibly, zero) digits. The decimal representation of the final number shouldn't start with a zero.

## 输入格式

The first line contains a single integer $ x $ $ (1<=x<=10^{18}) $ — the number that Luke Skywalker gave to Chewbacca.

## 输出格式

Print the minimum possible positive number that Chewbacca can obtain after inverting some digits. The number shouldn't contain leading zeroes.

## 样例 #1

### 输入

```
27

```

### 输出

```
22

```

## 样例 #2

### 输入

```
4545

```

### 输出

```
4444

```



---

---
title: "Rotate, Flip and Zoom"
layout: "post"
diff: 普及/提高-
pid: CF523A
tag: ['模拟', '字符串']
---

# Rotate, Flip and Zoom

## 题目描述

Polycarp is writing the prototype of a graphic editor. He has already made up his mind that the basic image transformations in his editor will be: rotate the image 90 degrees clockwise, flip the image horizontally (symmetry relative to the vertical line, that is, the right part of the image moves to the left, and vice versa) and zooming on the image. He is sure that that there is a large number of transformations that can be expressed through these three.

He has recently stopped implementing all three transformations for monochrome images. To test this feature, he asked you to write a code that will consecutively perform three actions with a monochrome image: first it will rotate the image 90 degrees clockwise, then it will flip the image horizontally and finally, it will zoom in twice on the image (that is, it will double all the linear sizes).

Implement this feature to help Polycarp test his editor.

## 输入格式

The first line contains two integers, $ w $ and $ h $ ( $ 1<=w,h<=100 $ ) — the width and height of an image in pixels. The picture is given in $ h $ lines, each line contains $ w $ characters — each character encodes the color of the corresponding pixel of the image. The line consists only of characters "." and "\*", as the image is monochrome.

## 输出格式

Print $ 2w $ lines, each containing $ 2h $ characters — the result of consecutive implementing of the three transformations, described above.

## 样例 #1

### 输入

```
3 2
.*.
.*.

```

### 输出

```
....
....
****
****
....
....

```

## 样例 #2

### 输入

```
9 20
**.......
****.....
******...
*******..
..******.
....****.
......***
*.....***
*********
*********
*********
*********
....**...
...****..
..******.
.********
****..***
***...***
**.....**
*.......*

```

### 输出

```
********......**********........********
********......**********........********
********........********......********..
********........********......********..
..********......********....********....
..********......********....********....
..********......********..********......
..********......********..********......
....********....****************........
....********....****************........
....********....****************........
....********....****************........
......******************..**********....
......******************..**********....
........****************....**********..
........****************....**********..
............************......**********
............************......**********

```



---

---
title: "Rebranding"
layout: "post"
diff: 普及/提高-
pid: CF591B
tag: ['模拟', '枚举']
---

# Rebranding

## 题目描述

The name of one small but proud corporation consists of $ n $ lowercase English letters. The Corporation has decided to try rebranding — an active marketing strategy, that includes a set of measures to change either the brand (both for the company and the goods it produces) or its components: the name, the logo, the slogan. They decided to start with the name.

For this purpose the corporation has consecutively hired $ m $ designers. Once a company hires the $ i $ -th designer, he immediately contributes to the creation of a new corporation name as follows: he takes the newest version of the name and replaces all the letters $ x_{i} $ by $ y_{i} $ , and all the letters $ y_{i} $ by $ x_{i} $ . This results in the new version. It is possible that some of these letters do no occur in the string. It may also happen that $ x_{i} $ coincides with $ y_{i} $ . The version of the name received after the work of the last designer becomes the new name of the corporation.

Manager Arkady has recently got a job in this company, but is already soaked in the spirit of teamwork and is very worried about the success of the rebranding. Naturally, he can't wait to find out what is the new name the Corporation will receive.

Satisfy Arkady's curiosity and tell him the final version of the name.

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ ( $ 1<=n,m<=200000 $ ) — the length of the initial name and the number of designers hired, respectively.

The second line consists of $ n $ lowercase English letters and represents the original name of the corporation.

Next $ m $ lines contain the descriptions of the designers' actions: the $ i $ -th of them contains two space-separated lowercase English letters $ x_{i} $ and $ y_{i} $ .

## 输出格式

Print the new name of the corporation.

## 说明/提示

In the second sample the name of the corporation consecutively changes as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/b0c9599f7e4282de011e545b3b2138ce054cf709.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/b503b89dff83c09912a9706615e9f382f03f5909.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/e277cc6136141b35244d23f5857e2b4088822639.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/cfe2461ca78ee24244102008b38c52289020e201.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/c06bdcdcec7417c4f543399c6c3d126f67ecf0a6.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/e46b37134536ad3b6c864840e66c2932fc25c838.png)

## 样例 #1

### 输入

```
6 1
police
p m

```

### 输出

```
molice

```

## 样例 #2

### 输入

```
11 6
abacabadaba
a b
b c
a d
e g
f a
b b

```

### 输出

```
cdcbcdcfcdc

```



---

---
title: "The Monster"
layout: "post"
diff: 普及/提高-
pid: CF787A
tag: ['模拟', '排序', '中国剩余定理 CRT']
---

# The Monster

## 题目描述

A monster is chasing after Rick and Morty on another planet. They're so frightened that sometimes they scream. More accurately, Rick screams at times $ b,b+a,b+2a,b+3a,... $ and Morty screams at times $ d,d+c,d+2c,d+3c,... $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF787A/23c11249630f1c4252ef0b9cda8ec1bf9b317b5a.png)The Monster will catch them if at any point they scream at the same time, so it wants to know when it will catch them (the first time they scream at the same time) or that they will never scream at the same time.

## 输入格式

The first line of input contains two integers $ a $ and $ b $ ( $ 1<=a,b<=100 $ ).

The second line contains two integers $ c $ and $ d $ ( $ 1<=c,d<=100 $ ).

## 输出格式

Print the first time Rick and Morty will scream at the same time, or $ -1 $ if they will never scream at the same time.

## 说明/提示

In the first sample testcase, Rick's $ 5 $ th scream and Morty's $ 8 $ th time are at time $ 82 $ .

In the second sample testcase, all Rick's screams will be at odd times and Morty's will be at even times, so they will never scream at the same time.

## 样例 #1

### 输入

```
20 2
9 19

```

### 输出

```
82

```

## 样例 #2

### 输入

```
2 1
16 12

```

### 输出

```
-1

```



---

---
title: "Mike and strings"
layout: "post"
diff: 普及/提高-
pid: CF798B
tag: ['模拟', '字符串']
---

# Mike and strings

## 题目描述

Mike有n个字符串s1,s2,……，sn，每个字符串均由小写字母构成。 每次移动你可以选择一个字符串si, 第1个字符移动最后，比如字符串 "coolmikecoolmike", 移动1次变成字符串 "oolmikecoolmikec"。

请计算至少需要移动多少次，可以使得n个字符串都变成相同。

## 输入格式

第一行，一个整数n(1≤n≤50)。 接下来n行，每行一个字符串，每个字符串的长度相当，且长度不超过50。

## 输出格式

输出最小移动次数，无解则输出-1.

## 样例 #1

### 输入

```
4
xzzwo
zwoxz
zzwox
xzzwo

```

### 输出

```
5

```

## 样例 #2

### 输入

```
2
molzv
lzvmo

```

### 输出

```
2

```

## 样例 #3

### 输入

```
3
kc
kc
kc

```

### 输出

```
0

```

## 样例 #4

### 输入

```
3
aa
aa
ab

```

### 输出

```
-1

```



---

---
title: "Position in Fraction"
layout: "post"
diff: 普及/提高-
pid: CF900B
tag: ['模拟', '字符串', '高精度']
---

# Position in Fraction

## 题目描述

给你三个整数 $a,b,c$，问 $\dfrac{a}{b}$ 的小数部分第几位是 $c$，如果无法找到，请输出 `-1`。

## 输入格式

共一行，三个整数 $a,b,c$。

## 输出格式

共一行，输出一个整数，表示 $c$ 的位置或 `-1`。

## 说明/提示

对于 $100\%$ 的数据：$1\le a<b\le 10^5,0\le c\le 9$。

## 样例 #1

### 输入

```
1 2 0

```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 3 7

```

### 输出

```
-1
```



---

---
title: "Our Tanya is Crying Out Loud"
layout: "post"
diff: 普及/提高-
pid: CF940B
tag: ['模拟', '贪心', '枚举']
---

# Our Tanya is Crying Out Loud

## 题目描述

Right now she actually isn't. But she will be, if you don't solve this problem.

You are given integers $ n $ , $ k $ , $ A $ and $ B $ . There is a number $ x $ , which is initially equal to $ n $ . You are allowed to perform two types of operations:

1. Subtract 1 from $ x $ . This operation costs you $ A $ coins.
2. Divide $ x $ by $ k $ . Can be performed only if $ x $ is divisible by $ k $ . This operation costs you $ B $ coins.

 What is the minimum amount of coins you have to pay to make $ x $ equal to $ 1 $ ?

## 输入格式

The first line contains a single integer $ n $ ( $ 1<=n<=2·10^{9} $ ).

The second line contains a single integer $ k $ ( $ 1<=k<=2·10^{9} $ ).

The third line contains a single integer $ A $ ( $ 1<=A<=2·10^{9} $ ).

The fourth line contains a single integer $ B $ ( $ 1<=B<=2·10^{9} $ ).

## 输出格式

Output a single integer — the minimum amount of coins you have to pay to make $ x $ equal to $ 1 $ .

## 说明/提示

In the first testcase, the optimal strategy is as follows:

- Subtract 1 from $ x $ ( $ 9→8 $ ) paying 3 coins.
- Divide $ x $ by 2 ( $ 8→4 $ ) paying 1 coin.
- Divide $ x $ by 2 ( $ 4→2 $ ) paying 1 coin.
- Divide $ x $ by 2 ( $ 2→1 $ ) paying 1 coin.

The total cost is $ 6 $ coins.

In the second test case the optimal strategy is to subtract 1 from $ x $ $ 4 $ times paying $ 8 $ coins in total.

## 样例 #1

### 输入

```
9
2
3
1

```

### 输出

```
6

```

## 样例 #2

### 输入

```
5
5
2
20

```

### 输出

```
8

```

## 样例 #3

### 输入

```
19
3
4
2

```

### 输出

```
12

```



---

---
title: "Minimize the error"
layout: "post"
diff: 普及/提高-
pid: CF960B
tag: ['模拟', '贪心']
---

# Minimize the error

## 题目描述

You are given two arrays $ A $ and $ B $ , each of size $ n $ . The error, $ E $ , between these two arrays is defined ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF960B/e950d33ee993b9f2e2ad61182c68b371192cc68e.png). You have to perform exactly $ k_{1} $ operations on array $ A $ and exactly $ k_{2} $ operations on array $ B $ . In one operation, you have to choose one element of the array and increase or decrease it by $ 1 $ .

Output the minimum possible value of error after $ k_{1} $ operations on array $ A $ and $ k_{2} $ operations on array $ B $ have been performed.

## 输入格式

The first line contains three space-separated integers $ n $ ( $ 1<=n<=10^{3} $ ), $ k_{1} $ and $ k_{2} $ ( $ 0<=k_{1}+k_{2}<=10^{3} $ , $ k_{1} $ and $ k_{2} $ are non-negative) — size of arrays and number of operations to perform on $ A $ and $ B $ respectively.

Second line contains $ n $ space separated integers $ a_{1},a_{2},...,a_{n} $ ( $ -10^{6}<=a_{i}<=10^{6} $ ) — array $ A $ .

Third line contains $ n $ space separated integers $ b_{1},b_{2},...,b_{n} $ ( $ -10^{6}<=b_{i}<=10^{6} $ )— array $ B $ .

## 输出格式

Output a single integer — the minimum possible value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF960B/52c5522faff1ae1553e7476d3c27b93932998da8.png) after doing exactly $ k_{1} $ operations on array $ A $ and exactly $ k_{2} $ operations on array $ B $ .

## 说明/提示

In the first sample case, we cannot perform any operations on $ A $ or $ B $ . Therefore the minimum possible error $ E=(1-2)^{2}+(2-3)^{2}=2 $ .

In the second sample case, we are required to perform exactly one operation on $ A $ . In order to minimize error, we increment the first element of $ A $ by $ 1 $ . Now, $ A=[2,2] $ . The error is now $ E=(2-2)^{2}+(2-2)^{2}=0 $ . This is the minimum possible error obtainable.

In the third sample case, we can increase the first element of $ A $ to $ 8 $ , using the all of the $ 5 $ moves available to us. Also, the first element of $ B $ can be reduced to $ 8 $ using the $ 6 $ of the $ 7 $ available moves. Now $ A=[8,4] $ and $ B=[8,4] $ . The error is now $ E=(8-8)^{2}+(4-4)^{2}=0 $ , but we are still left with $ 1 $ move for array $ B $ . Increasing the second element of $ B $ to $ 5 $ using the left move, we get $ B=[8,5] $ and $ E=(8-8)^{2}+(4-5)^{2}=1 $ .

## 样例 #1

### 输入

```
2 0 0
1 2
2 3

```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 1 0
1 2
2 2

```

### 输出

```
0
```

## 样例 #3

### 输入

```
2 5 7
3 4
14 4

```

### 输出

```
1
```



---

---
title: "Equator"
layout: "post"
diff: 普及/提高-
pid: CF962A
tag: ['模拟', '概率论']
---

# Equator

## 题目描述

已知 Polycarp 共有 $n$ 天准备编程竞赛，他每天预计做的题数为 $a_i$，请问直到第几天能做完所有题目的一半或更多。

## 输入格式

第一行，一个整数 $n$。

第二行，$n$ 个整数，表示 $a_i$。

## 输出格式

一个整数，表示答案。

## 样例 #1

### 输入

```
4
1 3 2 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
6
2 2 2 2 2 2

```

### 输出

```
3

```



---

---
title: "Petya's Exams"
layout: "post"
diff: 普及/提高-
pid: CF978G
tag: ['模拟', '贪心', '排序']
---

# Petya's Exams

## 题目描述

Petya studies at university. The current academic year finishes with $ n $ special days. Petya needs to pass $ m $ exams in those special days. The special days in this problem are numbered from $ 1 $ to $ n $ .

There are three values about each exam:

- $ s_i $ — the day, when questions for the $ i $ -th exam will be published,
- $ d_i $ — the day of the $ i $ -th exam ( $ s_i < d_i $ ),
- $ c_i $ — number of days Petya needs to prepare for the $ i $ -th exam. For the $ i $ -th exam Petya should prepare in days between $ s_i $ and $ d_i-1 $ , inclusive.

There are three types of activities for Petya in each day: to spend a day doing nothing (taking a rest), to spend a day passing exactly one exam or to spend a day preparing for exactly one exam. So he can't pass/prepare for multiple exams in a day. He can't mix his activities in a day. If he is preparing for the $ i $ -th exam in day $ j $ , then $ s_i \le j < d_i $ .

It is allowed to have breaks in a preparation to an exam and to alternate preparations for different exams in consecutive days. So preparation for an exam is not required to be done in consecutive days.

Find the schedule for Petya to prepare for all exams and pass them, or report that it is impossible.

## 输入格式

The first line contains two integers $ n $ and $ m $ $ (2 \le n \le 100, 1 \le m \le n) $ — the number of days and the number of exams.

Each of the following $ m $ lines contains three integers $ s_i $ , $ d_i $ , $ c_i $ $ (1 \le s_i < d_i \le n, 1 \le c_i \le n) $ — the day, when questions for the $ i $ -th exam will be given, the day of the $ i $ -th exam, number of days Petya needs to prepare for the $ i $ -th exam.

Guaranteed, that all the exams will be in different days. Questions for different exams can be given in the same day. It is possible that, in the day of some exam, the questions for other exams are given.

## 输出格式

If Petya can not prepare and pass all the exams, print -1. In case of positive answer, print $ n $ integers, where the $ j $ -th number is:

- $ (m + 1) $ , if the $ j $ -th day is a day of some exam (recall that in each day no more than one exam is conducted),
- zero, if in the $ j $ -th day Petya will have a rest,
- $ i $ ( $ 1 \le i \le m $ ), if Petya will prepare for the $ i $ -th exam in the day $ j $ (the total number of days Petya prepares for each exam should be strictly equal to the number of days needed to prepare for it).Assume that the exams are numbered in order of appearing in the input, starting from $ 1 $ .
  
  If there are multiple schedules, print any of them.

## 说明/提示

In the first example Petya can, for example, prepare for exam $ 1 $ in the first day, prepare for exam $ 2 $ in the second day, pass exam $ 1 $ in the third day, relax in the fourth day, and pass exam $ 2 $ in the fifth day. So, he can prepare and pass all exams.

In the second example, there are three days and two exams. So, Petya can prepare in only one day (because in two other days he should pass exams). Then Petya can not prepare and pass all exams.

## 样例 #1

### 输入

```
5 2
1 3 1
1 5 1

```

### 输出

```
1 2 3 0 3 

```

## 样例 #2

### 输入

```
3 2
1 3 1
1 2 1

```

### 输出

```
-1

```

## 样例 #3

### 输入

```
10 3
4 7 2
1 10 3
8 9 1

```

### 输出

```
2 2 2 1 1 0 4 3 4 4 

```



---

---
title: "Petr and Permutations"
layout: "post"
diff: 普及/提高-
pid: CF986B
tag: ['模拟', '贪心', '树状数组']
---

# Petr and Permutations

## 题目描述

Petr likes to come up with problems about randomly generated data. This time problem is about random permutation. He decided to generate a random permutation this way: he takes identity permutation of numbers from $ 1 $ to $ n $ and then $ 3n $ times takes a random pair of different elements and swaps them. Alex envies Petr and tries to imitate him in all kind of things. Alex has also come up with a problem about random permutation. He generates a random permutation just like Petr but swaps elements $ 7n+1 $ times instead of $ 3n $ times. Because it is more random, OK?!

You somehow get a test from one of these problems and now you want to know from which one.

## 输入格式

In the first line of input there is one integer $ n $ ( $ 10^{3} \le n \le 10^{6} $ ).

In the second line there are $ n $ distinct integers between $ 1 $ and $ n $ — the permutation of size $ n $ from the test.

It is guaranteed that all tests except for sample are generated this way: First we choose $ n $ — the size of the permutation. Then we randomly choose a method to generate a permutation — the one of Petr or the one of Alex. Then we generate a permutation using chosen method.

## 输出格式

If the test is generated via Petr's method print "Petr" (without quotes). If the test is generated via Alex's method print "Um\_nik" (without quotes).

## 说明/提示

Please note that the sample is not a valid test (because of limitations for $ n $ ) and is given only to illustrate input/output format. Your program still has to print correct answer to this test to get AC.

Due to randomness of input hacks in this problem are forbidden.

## 样例 #1

### 输入

```
5
2 4 5 1 3

```

### 输出

```
Petr

```



---

---
title: "Bishwock"
layout: "post"
diff: 普及/提高-
pid: CF991D
tag: ['模拟', '贪心']
---

# Bishwock

## 题目描述

Bishwock is a chess figure that consists of three squares resembling an "L-bar". This figure can be rotated by 90, 180 and 270 degrees so it can have four possible states:

```
XX   XX   .X   X.
X.   .X   XX   XX
```

Bishwocks don't attack any squares and can even occupy on the adjacent squares as long as they don't occupy the same square.

Vasya has a board with $ 2\times n $ squares onto which he wants to put some bishwocks. To his dismay, several squares on this board are already occupied by pawns and Vasya can't put bishwocks there. However, pawns also don't attack bishwocks and they can occupy adjacent squares peacefully.

Knowing the positions of pawns on the board, help Vasya to determine the maximum amount of bishwocks he can put onto the board so that they wouldn't occupy the same squares and wouldn't occupy squares with pawns.

## 输入格式

The input contains two nonempty strings that describe Vasya's board. Those strings contain only symbols "0" (zero) that denote the empty squares and symbols "X" (uppercase English letter) that denote the squares occupied by pawns. Strings are nonempty and are of the same length that does not exceed $ 100 $ .

## 输出格式

Output a single integer — the maximum amount of bishwocks that can be placed onto the given board.

## 样例 #1

### 输入

```
00
00

```

### 输出

```
1
```

## 样例 #2

### 输入

```
00X00X0XXX0
0XXX0X00X00

```

### 输出

```
4
```

## 样例 #3

### 输入

```
0X0X0
0X0X0

```

### 输出

```
0
```

## 样例 #4

### 输入

```
0XXX0
00000

```

### 输出

```
2
```



---

