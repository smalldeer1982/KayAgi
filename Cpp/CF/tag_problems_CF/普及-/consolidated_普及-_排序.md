---
title: "Homework"
layout: "post"
diff: 普及-
pid: CF101A
tag: ['贪心', '排序', '概率论']
---

# Homework

## 题目描述

Gerald在上学的一天，他的老师在班上布置了一项作业：她给每个同学一个有n个小写拉丁字母（即英文字母）的字符串，要求学生学习这个字符串中的字母的写法。但是，由于Gerald太懒了，他不想学习这些字母。这就是为什么他决定丢掉这个字符串的部分（不需要是连续的一部分）。他所丢失的部分可以由若干个任意长度在任意位置的连续的子字符串组成。但是，Gerald知道，如果他丢掉了超过k个字母，他就会显得非常可疑。

请求出在不超过k个字母被删除之后，字符串中最少剩下多少个不同的字母。你还需要求出一种删除这些字母的方式。

## 输入格式

输入的第一行是一个长度为n的字符串( $1<=n<=10^{5}$ )。这个字符串由小写拉丁字母组成。输入的第二行是数k( $0<=k<=10^{5}$ )。

## 输出格式

请在第一行只输出数m——从这个字符串中删除k个字符之后最少剩下的最少的不同字母的个数。

在第二行输出在删除一些字母之后Gerald所能得到的字符串。这个字符串应该刚好有m个不同的字母。这个最终的字符串应该是原字符串的一个子串。如果Gerald能够得到多个都刚好有m个不同字母的不同的字符串，输出其中任意一个。

## 说明/提示

在第一个样例中这个字符串含有5个字母但是你只允许删去其中4个，所以会剩下至少一个字母。所以，正确答案就是1和任意一个长度在1到5的、只含有字母a的字符串。

在第二个杨立忠你可以删去4个字母。你不能删去所有的字母，因为这个字符串的长度是7。 但是，你可以删去所以除了a以外的字母（这样的字母不多于4个），所以得到的答案是"aaaa"。

在第三个样例中字符串的长度是8，且k=10，所以可以将所有的字母都删去。正确答案是0和空字符串。

Translated by @oolliivveerr

## 样例 #1

### 输入

```
aaaaa
4

```

### 输出

```
1
aaaaa

```

## 样例 #2

### 输入

```
abacaba
4

```

### 输出

```
1
aaaa

```

## 样例 #3

### 输入

```
abcdefgh
10

```

### 输出

```
0


```



---

---
title: "Heist"
layout: "post"
diff: 普及-
pid: CF1041A
tag: ['枚举', '排序', '概率论']
---

# Heist

## 题目描述

昨晚有一家电子商店被抢劫了。

昨天在商店里的所有键盘都是从$x$开始按升序编号的。例如，如果$x=4$，并且商店中有$3$个键盘，那么编号就为$4,5,6$；如果$x=10$，并且有$7$个键盘，那么编号就为$10,11,12,13,14,15,16$。

在抢劫之后，只有$n$个键盘仍然存在，他们的编号分别为$a_1,a_2,\dots ,a_n$。计算被盗的键盘的最小可能数量。工作人员不记得$x$也不记得商店里原来有几个键盘。

## 输入格式

第一行输入一个整数$n(1\le n\le 1000)$，为商店里仍然存在的键盘的数量。

第二行输入$n$个整数$a_1,a_2\dots ,a_n(1\le a_i\le 10^9)$，表示所有商店里仍然存在的键盘的编号。

## 输出格式

输出被盗的键盘的最小可能数量。

感谢@dblark 提供的翻译

## 样例 #1

### 输入

```
4
10 13 12 8

```

### 输出

```
2

```

## 样例 #2

### 输入

```
5
7 5 6 4 8

```

### 输出

```
0

```



---

---
title: "Correct Solution?"
layout: "post"
diff: 普及-
pid: CF12B
tag: ['字符串', '排序']
---

# Correct Solution?

## 题目描述

在一个寒冷的冬夜，Alice 和她的哥哥 Bob 正坐在家中的壁炉旁，玩一个有趣的游戏。

Alice 给出了一个数 $n$，并让 Bob 找到满足以下条件的数：

- 通过将这个数的数位打乱，得到一个没有前导零的最小的新数。

“没问题！“ Bob 立刻给出了答案。因为 Alice 并不知道哥哥的答案是否正确，所以她将 $n$ 和哥哥给出的答案给了你，希望你能帮她判断这个答案是否正确。

## 输入格式

第一行，一个正整数 $n\,(0 \le n \le 10^9)$，保证没有前导零。

第二行，一个正整数 $m\,(0 \le m \le 10^9)$，表示 Bob 给出的答案，可能有前导零。

## 输出格式

如果 Bob 的答案正确，输出 `OK`，否则输出 `WRONG_ANSWER`。

-----

翻译 By @[Eason_cyx](https://luogu.com.cn/user/741244)。

## 样例 #1

### 输入

```
3310
1033

```

### 输出

```
OK

```

## 样例 #2

### 输入

```
4
5

```

### 输出

```
WRONG_ANSWER

```



---

---
title: "Fruits"
layout: "post"
diff: 普及-
pid: CF12C
tag: ['贪心', '排序']
---

# Fruits

## 题目描述

The spring is coming and it means that a lot of fruits appear on the counters. One sunny day little boy Valera decided to go shopping. He made a list of $ m $ fruits he wanted to buy. If Valera want to buy more than one fruit of some kind, he includes it into the list several times.

When he came to the fruit stall of Ashot, he saw that the seller hadn't distributed price tags to the goods, but put all price tags on the counter. Later Ashot will attach every price tag to some kind of fruits, and Valera will be able to count the total price of all fruits from his list. But Valera wants to know now what can be the smallest total price (in case of the most «lucky» for him distribution of price tags) and the largest total price (in case of the most «unlucky» for him distribution of price tags).

## 输入格式

The first line of the input contains two integer number $ n $ and $ m $ ( $ 1<=n,m<=100 $ ) — the number of price tags (which is equal to the number of different kinds of fruits that Ashot sells) and the number of items in Valera's list. The second line contains $ n $ space-separated positive integer numbers. Each of them doesn't exceed $ 100 $ and stands for the price of one fruit of some kind. The following $ m $ lines contain names of the fruits from the list. Each name is a non-empty string of small Latin letters which length doesn't exceed 32. It is guaranteed that the number of distinct fruits from the list is less of equal to $ n $ . Also it is known that the seller has in stock all fruits that Valera wants to buy.

## 输出格式

Print two numbers $ a $ and $ b $ ( $ a<=b $ ) — the minimum and the maximum possible sum which Valera may need to buy all fruits from his list.

## 样例 #1

### 输入

```
5 3
4 2 1 10 5
apple
orange
mango

```

### 输出

```
7 19

```

## 样例 #2

### 输入

```
6 5
3 5 1 6 8 1
peach
grapefruit
banana
orange
orange

```

### 输出

```
11 30

```



---

---
title: "Reverse Sort"
layout: "post"
diff: 普及-
pid: CF1605B
tag: ['贪心', '排序']
---

# Reverse Sort

## 题目描述

题目共给出 $t(1 \le t \le 1000)$ 组数据，每组数据包含一个正整数 $n(1 \le n \le 1000)$ 和一个长度为 $n$ 的 $01$ 串 $s$， 现在你需要在 $s$ 中选出一个子序列，将这个子序列中的字符翻转（如字符串 $10100$， 选出子序列 $1100$， 翻转得到 $0011$， 放回原串中得到 $00011$），使得翻转后的字符串字典序最小。

## 输入格式

第一行一个 $t$， 表示样例组数。

每组一个正整数 $t$ 和一个字符串 $s$， 表示字符串的长度和你将要进行操作的字符串。

## 输出格式

对于每组数据，第一行输出需要操作的次数（一次提取和一次翻转总称为一次操作，若不需修改则输出 $0$，详见样例），若操作次数不为零，则在第二行输出：

第一个数字 $k$，表示需要提取出来的数字个数，后 $k$ 个数字，表示提取出来的数字在原串中的位置（下标 + 1）

样例解释：

对于第一组样例，不需要进行任何操作，本身字典序最小，输出 $0$

对于第二组样例，需要进行一次操作，即将 $10100$ 中的 $1100$ 提取出来翻转，原串变为 $00011$

对于第三组样例，需要进行一次操作，即将 $001000$ 中的 $100$ 提取出来翻转，原串变为 $000001$

## 样例 #1

### 输入

```
3
7
0011111
5
10100
6
001000
```

### 输出

```
0
1
4 1 3 4 5 
1
3 3 5 6
```



---

---
title: "Great Sequence"
layout: "post"
diff: 普及-
pid: CF1641A
tag: ['模拟', '贪心', '排序']
---

# Great Sequence

## 题目描述

A sequence of positive integers is called great for a positive integer $ x $ , if we can split it into pairs in such a way that in each pair the first number multiplied by $ x $ is equal to the second number. More formally, a sequence $ a $ of size $ n $ is great for a positive integer $ x $ , if $ n $ is even and there exists a permutation $ p $ of size $ n $ , such that for each $ i $ ( $ 1 \le i \le \frac{n}{2} $ ) $ a_{p_{2i-1}} \cdot x = a_{p_{2i}} $ .

Sam has a sequence $ a $ and a positive integer $ x $ . Help him to make the sequence great: find the minimum possible number of positive integers that should be added to the sequence $ a $ to make it great for the number $ x $ .

## 输入格式

Each test contains multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 20\,000 $ ) — the number of test cases. Description of the test cases follows.

The first line of each test case contains two integers $ n $ , $ x $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 2 \le x \le 10^6 $ ).

The next line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case print a single integer — the minimum number of integers that can be added to the end of $ a $ to make it a great sequence for the number $ x $ .

## 说明/提示

In the first test case, Sam got lucky and the sequence is already great for the number $ 4 $ because you can divide it into such pairs: $ (1, 4) $ , $ (4, 16) $ . Thus we can add $ 0 $ numbers.

In the second test case, you can add numbers $ 1 $ and $ 14 $ to the sequence, then you can divide all $ 8 $ integers into such pairs: $ (1, 2) $ , $ (1, 2) $ , $ (2, 4) $ , $ (7, 14) $ . It is impossible to add less than $ 2 $ integers to fix the sequence.

## 样例 #1

### 输入

```
4
4 4
1 16 4 4
6 2
1 2 2 2 4 7
5 3
5 2 3 5 15
9 10
10 10 10 20 1 100 200 2000 3
```

### 输出

```
0
2
3
3
```



---

---
title: "Monsters Attack!"
layout: "post"
diff: 普及-
pid: CF1923B
tag: ['贪心', '排序']
---

# Monsters Attack!

## 题目描述

You are playing a computer game. The current level of this game can be modeled as a straight line. Your character is in point $ 0 $ of this line. There are $ n $ monsters trying to kill your character; the $ i $ -th monster has health equal to $ a_i $ and is initially in the point $ x_i $ .

Every second, the following happens:

- first, you fire up to $ k $ bullets at monsters. Each bullet targets exactly one monster and decreases its health by $ 1 $ . For each bullet, you choose its target arbitrary (for example, you can fire all bullets at one monster, fire all bullets at different monsters, or choose any other combination). Any monster can be targeted by a bullet, regardless of its position and any other factors;
- then, all alive monsters with health $ 0 $ or less die;
- then, all alive monsters move $ 1 $ point closer to you (monsters to the left of you increase their coordinates by $ 1 $ , monsters to the right of you decrease their coordinates by $ 1 $ ). If any monster reaches your character (moves to the point $ 0 $ ), you lose.

Can you survive and kill all $ n $ monsters without letting any of them reach your character?

## 输入格式

The first line of the input contains one integer $ t $ ( $ 1 \le t \le 3 \cdot 10^4 $ ) — the number of test cases.

Each test case consists of three lines:

- the first line contains two integers $ n $ and $ k $ ( $ 1 \le n \le 3 \cdot 10^5 $ ; $ 1 \le k \le 2 \cdot 10^9 $ );
- the second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ );
- the third line contains $ n $ integers $ x_1, x_2, \dots, x_n $ ( $ -n \le x_1 < x_2 < x_3 < \dots < x_n \le n $ ; $ x_i \ne 0 $ ).

Additional constraint on the input: the sum of $ n $ over all test cases does not exceed $ 3 \cdot 10^5 $ .

## 输出格式

For each test case, print YES if you can kill all $ n $ monsters before they reach your character, or NO otherwise.

You can output each letter of the answer in any case (upper or lower). For example, the strings yEs, yes, Yes, and YES will all be recognized as positive responses.

## 说明/提示

In the first example, you can act as follows:

- during the $ 1 $ -st second, fire $ 1 $ bullet at the $ 1 $ -st monster and $ 1 $ bullet at the $ 3 $ -rd monster. Then the $ 1 $ -st monster dies, the $ 2 $ -nd and the $ 3 $ -rd monster move closer;
- during the $ 2 $ -nd second, fire $ 2 $ bullets at the $ 2 $ -nd monster. Then the $ 2 $ -nd monster dies, the $ 3 $ -rd monster moves closer;
- during the $ 3 $ -rd second, fire $ 2 $ bullets at the $ 3 $ -rd monster. Then the $ 3 $ -rd monster dies.

In the second example, you can fire only $ 1 $ bullet, so you can kill only one of the two monsters during the $ 1 $ -st second. Then, the remaining monster moves closer and kills your character.

## 样例 #1

### 输入

```
5
3 2
1 2 3
-1 2 3
2 1
1 1
-1 1
4 10
3 4 2 5
-3 -2 1 3
5 3
2 1 3 2 5
-3 -2 3 4 5
2 1
1 2
1 2
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
title: "Splitting Items"
layout: "post"
diff: 普及-
pid: CF2004C
tag: ['贪心', '排序']
---

# Splitting Items

## 题目描述

Alice 和 Bob 有 $n$ 个数，第 $i$ 个数为 $a_i$，他们决定玩一个游戏取走这些数。

游戏由 Alice 开始取数。

每一次玩家都可以拿走一个剩下的数，直到没有数字可拿走。

定义 $A$ 是 Alice 获取的数字和，$B$ 是 Bob 获取的数字和，游戏总分 $p = A - B$。

Alice 希望最大化 $p$，Bob 希望最小化 $p$，他们都绝顶聪明。

现在 Bob 拥有了修改数的权限，可以把一些数字（可以没有，也可以没有全部）**增加**一个整数值（可以增加不同的值），但是这样 Alice 可能会起疑心，所以总增加的数值必须小于等于 $k$。

请求出 Bob 能达到的 $p$ 的最小值。

## 输入格式

**本题有多组数据。**

首先输入一个整数 $t (1 \le t \le 5000)$，表示数据组数。

对于每一组数据，第一行输入两个整数 $n, k (2 \le n \le 2 \times 10 ^ 5, 0 \le k \le 10 ^ 9)$，含义如题意描述。

注意到所有数据的 $n$ 总和不大于 $2 \times 10 ^ 5$。

下一行输入 $n$ 个整数 $a_1, a_2, \cdots, a_n (1 \le a_i \le 10 ^ 9)$，表示每个数的值。

## 输出格式

对于每组数据输出一个整数表示答案。

## 样例 #1

### 输入

```
4
2 5
1 10
3 0
10 15 12
4 6
3 1 2 4
2 4
6 9
```

### 输出

```
4
13
0
0
```



---

---
title: "Photographer"
layout: "post"
diff: 普及-
pid: CF203C
tag: ['贪心', '排序']
---

# Photographer

## 题目描述

Valera's lifelong ambition was to be a photographer, so he bought a new camera. Every day he got more and more clients asking for photos, and one day Valera needed a program that would determine the maximum number of people he can serve.

The camera's memory is $ d $ megabytes. Valera's camera can take photos of high and low quality. One low quality photo takes $ a $ megabytes of memory, one high quality photo take $ b $ megabytes of memory. For unknown reasons, each client asks him to make several low quality photos and several high quality photos. More formally, the $ i $ -th client asks to make $ x_{i} $ low quality photos and $ y_{i} $ high quality photos.

Valera wants to serve as many clients per day as possible, provided that they will be pleased with his work. To please the $ i $ -th client, Valera needs to give him everything he wants, that is, to make $ x_{i} $ low quality photos and $ y_{i} $ high quality photos. To make one low quality photo, the camera must have at least $ a $ megabytes of free memory space. Similarly, to make one high quality photo, the camera must have at least $ b $ megabytes of free memory space. Initially the camera's memory is empty. Valera also does not delete photos from the camera so that the camera's memory gradually fills up.

Calculate the maximum number of clients Valera can successfully serve and print the numbers of these clients.

## 输入格式

The first line contains two integers $ n $ and $ d $ $ (1<=n<=10^{5},1<=d<=10^{9}) $ — the number of clients and the camera memory size, correspondingly. The second line contains two integers $ a $ and $ b $ ( $ 1<=a<=b<=10^{4} $ ) — the size of one low quality photo and of one high quality photo, correspondingly.

Next $ n $ lines describe the clients. The $ i $ -th line contains two integers $ x_{i} $ and $ y_{i} $ ( $ 0<=x_{i},y_{i}<=10^{5} $ ) — the number of low quality photos and high quality photos the $ i $ -th client wants, correspondingly.

All numbers on all lines are separated by single spaces.

## 输出格式

On the first line print the answer to the problem — the maximum number of clients that Valera can successfully serve. Print on the second line the numbers of the client in any order. All numbers must be distinct. If there are multiple answers, print any of them. The clients are numbered starting with $ 1 $ in the order in which they are defined in the input data.

## 样例 #1

### 输入

```
3 10
2 3
1 4
2 1
1 0

```

### 输出

```
2
3 2 
```

## 样例 #2

### 输入

```
3 6
6 6
1 1
1 0
1 0

```

### 输出

```
1
2 
```



---

---
title: "Swap Columns and Find a Path"
layout: "post"
diff: 普及-
pid: CF2046A
tag: ['贪心', '排序']
---

# Swap Columns and Find a Path

## 题目描述

有一个包含 $2$ 行 $n$ 列的矩阵。从上至下标号 $1,2$，从左到右标号 $1$ 到 $n$。记第 $i$ 横行第 $j$ 竖列的位置为 $(i,j)$，每个单元位置有一个整数。

你可以进行如下操作任意次（包括 $0$ 次）：

- 交换两列数字（找到整数 $x,y$ 满足 $1\le x\lt y\le n$，交换 $a_{1,x}$ 与 $a_{1,y}$，同时交换 $a_{2,x}$ 与 $a_{2,y}$）。

以上操作全部完成后，你需要找到一条从 $(1,1)$ 到 $(2,n)$ 的路径，每一次只能从 $(i,j)$ 移动到 $(i+1,j)$ 或 $(i,j+1)$。显然，路径无法走出这个矩形。

这条路径的分数为路径上所有 $(n+1)$ 个整数之和。你要进行上述的操作，并且找到最大可能的分数。

## 输入格式

本题包含多组数据。第一行，一个整数 $t$ ($1\le t\le 5000$) 表示数据组数。

对于每组数据，输入三行：

- 第一行，一个整数 $n$ ($1\le n\le 5000$)，表示矩阵的列数。

- 第二行，$n$ 个整数 $a_{1,1},a_{1,2},\cdots,a_{1,n}$，表示矩阵的第一行。

- 第三行，$n$ 个整数 $a_{2,1},a_{2,2},\cdots,a_{2,n}$，表示矩阵的第二行。

保证所有 $n$ 之和不超过 $5000$。

## 输出格式

对于每组数据，输出一个整数，表示你可以获得的最大分数。

翻译：[HYdroKomide](https://www.luogu.com.cn/user/299883)

## 样例 #1

### 输入

```
3
1
-10
5
3
1 2 3
10 -5 -3
4
2 8 5 3
1 10 3 4
```

### 输出

```
-5
16
29
```



---

---
title: "Kamilka and the Sheep"
layout: "post"
diff: 普及-
pid: CF2092A
tag: ['数学', '排序']
---

# Kamilka and the Sheep

## 题目描述

Kamilka 有一群由 $n$ 只绵羊组成的羊群，第 $i$ 只绵羊的美丽值为 $a_i$。所有 $a_i$ 均互不相同。清晨已至，需要给绵羊喂食。Kamilka 可以选择一个非负整数 $d$ 并给每只绵羊喂食 $d$ 捆草。此后，每只绵羊的美丽值将增加 $d$。

傍晚时，Kamilka 必须选择恰好两只绵羊带往山区。若这两只绵羊的美丽值（在喂食后）分别为 $x$ 和 $y$，则 Kamilka 此次散步的乐趣等于 $\gcd(x, y)$，其中 $\gcd(x, y)$ 表示整数 $x$ 和 $y$ 的[最大公约数 (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor)。

任务是通过合理选择 $d$，求出 Kamilka 能获得的最大可能乐趣。

## 输入格式

每个测试包含多个测试用例。第一行包含一个整数 $t$ ($1 \leq t \leq 500$)，表示测试用例数量。接下来是测试用例描述。

每个测试用例的第一行包含一个整数 $n$ ($2 \leq n \leq 100$)，表示 Kamilka 拥有的绵羊数量。

每个测试用例的第二行包含 $n$ 个互不相同的整数 $a_1, a_2, \ldots, a_n$ ($1 \leq a_i \leq 10^9$)，表示绵羊的美丽值。

保证所有 $a_i$ 均互不相同。

## 输出格式

对于每个测试用例，输出一个整数：Kamilka 能获得的最大可能乐趣。


## 说明/提示

第一个测试用例中，选择 $d=1$ 可行。此时乐趣为 $\gcd(1+1, 3+1)=\gcd(2, 4)=2$。可以证明无法获得更大的答案。

第二个测试用例中，选择 $d=3$。此时乐趣为 $\gcd(5+3, 1+3)=\gcd(8, 4)=4$。因此该测试用例的答案为 $4$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
2
1 3
5
5 4 3 2 1
3
5 6 7
3
1 11 10
```

### 输出

```
2
4
2
10
```



---

---
title: "The Picky Cat"
layout: "post"
diff: 普及-
pid: CF2102B
tag: ['排序']
---

# The Picky Cat

## 题目描述

给定一个整数数组 $a_1, a_2, \ldots, a_n$。你可以执行以下操作任意次数（包括零次）：

- 选择一个下标 $i$（$1 \le i \le n$）。将 $a_i$ 乘以 $-1$（即更新 $a_i := -a_i$）。

你的任务是判断是否可以通过上述操作使得下标为 $1$ 的元素成为数组的中位数。注意操作也可以应用于下标 $1$，这意味着中位数可以是 $a_1$ 的原值或其相反数。

数组 $b_1, b_2, \ldots, b_m$ 的中位数定义为数组中第 $\left\lceil \frac{m}{2} \right\rceil$ 小的元素 $^{\text{∗}}$。例如，数组 $[3, 1, 2]$ 的中位数是 $2$，而数组 $[10, 1, 8, 3]$ 的中位数是 $3$。

保证数组 $a$ 中元素的绝对值互不相同。形式化地说，不存在下标对 $1 \le i < j \le n$ 满足 $|a_i| = |a_j|$。

$^{\text{∗}}$ $\lceil x \rceil$ 是向上取整函数，返回大于等于 $x$ 的最小整数。

## 输入格式

每个测试包含多个测试用例。第一行输入测试用例数量 $t$（$1 \le t \le 10^4$）。接下来是各测试用例的描述。

每个测试用例的第一行包含一个整数 $n$（$1 \le n \le 10^5$）——数组 $a$ 的长度。

每个测试用例的第二行包含 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$|a_i| \le 10^6$，$|a_i| \neq |a_j|$）——数组 $a$ 的元素。

保证所有测试用例的 $n$ 之和不超过 $10^5$。

## 输出格式

对于每个测试用例，如果可以使下标为 $1$ 的元素成为数组的中位数，输出"YES"，否则输出"NO"。

你可以以任意大小写形式输出答案（例如字符串"yEs"、"yes"、"Yes"和"YES"都会被识别为肯定回答）。


## 说明/提示

在第一个测试用例中，$a_1 = 2$ 已经是数组 $a = [2, 3, 1]$ 的中位数，因此不需要任何操作。

在第二个测试用例中，我们可以执行两次操作：一次在下标 $2$，一次在下标 $5$。数组变为 $[1, -2, 3, 4, -5]$，其中中位数为 $1$。

在第三个测试用例中，如果对下标 $1$ 执行操作，数组将变为 $[-4, 2, 0, -5]$，其中中位数为 $-4$。

在第四个测试用例中，可以证明不存在任何操作序列能使数组的中位数变为 $5$ 或 $-5$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
7
3
2 3 1
5
1 2 3 4 5
4
4 2 0 -5
4
-5 0 4 3
4
-10 8 3 2
1
1
10
9 1000 -999 -13 456 -223 23 24 10 0
```

### 输出

```
YES
YES
YES
NO
NO
YES
YES
```



---

---
title: "Sale"
layout: "post"
diff: 普及-
pid: CF34B
tag: ['贪心', '排序']
---

# Sale

## 题目描述

Once Bob got to a sale of old TV sets. There were $ n $ TV sets at that sale. TV set with index $ i $ costs $ a_{i} $ bellars. Some TV sets have a negative price — their owners are ready to pay Bob if he buys their useless apparatus. Bob can «buy» any TV sets he wants. Though he's very strong, Bob can carry at most $ m $ TV sets, and he has no desire to go to the sale for the second time. Please, help Bob find out the maximum sum of money that he can earn.

## 输入格式

The first line contains two space-separated integers $ n $ and $ m $ ( $ 1<=m<=n<=100 $ ) — amount of TV sets at the sale, and amount of TV sets that Bob can carry. The following line contains $ n $ space-separated integers $ a_{i} $ ( $ -1000<=a_{i}<=1000 $ ) — prices of the TV sets.

## 输出格式

Output the only number — the maximum sum of money that Bob can earn, given that he can carry at most $ m $ TV sets.

## 样例 #1

### 输入

```
5 3
-6 0 35 -2 4

```

### 输出

```
8

```

## 样例 #2

### 输入

```
4 2
7 0 0 -7

```

### 输出

```
7

```



---

---
title: "The number on the board"
layout: "post"
diff: 普及-
pid: CF835B
tag: ['字符串', '贪心', '排序']
---

# The number on the board

## 题目描述

Some natural number was written on the board. Its sum of digits was not less than $ k $ . But you were distracted a bit, and someone changed this number to $ n $ , replacing some digits with others. It's known that the length of the number didn't change.

You have to find the minimum number of digits in which these two numbers can differ.

## 输入格式

The first line contains integer $ k $ ( $ 1<=k<=10^{9} $ ).

The second line contains integer $ n $ ( $ 1<=n&lt;10^{100000} $ ).

There are no leading zeros in $ n $ . It's guaranteed that this situation is possible.

## 输出格式

Print the minimum number of digits in which the initial number and $ n $ can differ.

## 说明/提示

In the first example, the initial number could be $ 12 $ .

In the second example the sum of the digits of $ n $ is not less than $ k $ . The initial number could be equal to $ n $ .

## 样例 #1

### 输入

```
3
11

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3
99

```

### 输出

```
0

```



---

---
title: "Chess Tourney"
layout: "post"
diff: 普及-
pid: CF845A
tag: ['模拟', '贪心', '排序']
---

# Chess Tourney

## 题目描述

Berland annual chess tournament is coming!

Organizers have gathered $ 2·n $ chess players who should be divided into two teams with $ n $ people each. The first team is sponsored by BerOil and the second team is sponsored by BerMobile. Obviously, organizers should guarantee the win for the team of BerOil.

Thus, organizers should divide all $ 2·n $ players into two teams with $ n $ people each in such a way that the first team always wins.

Every chess player has its rating $ r_{i} $ . It is known that chess player with the greater rating always wins the player with the lower rating. If their ratings are equal then any of the players can win.

After teams assignment there will come a drawing to form $ n $ pairs of opponents: in each pair there is a player from the first team and a player from the second team. Every chess player should be in exactly one pair. Every pair plays once. The drawing is totally random.

Is it possible to divide all $ 2·n $ players into two teams with $ n $ people each so that the player from the first team in every pair wins regardless of the results of the drawing?

## 输入格式

The first line contains one integer $ n $ ( $ 1<=n<=100 $ ).

The second line contains $ 2·n $ integers $ a_{1},a_{2},...\ a_{2n} $ ( $ 1<=a_{i}<=1000 $ ).

## 输出格式

If it's possible to divide all $ 2·n $ players into two teams with $ n $ people each so that the player from the first team in every pair wins regardless of the results of the drawing, then print "YES". Otherwise print "NO".

## 样例 #1

### 输入

```
2
1 3 2 4

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
1
3 3

```

### 输出

```
NO

```



---

---
title: "Boxes Packing"
layout: "post"
diff: 普及-
pid: CF903C
tag: ['贪心', '排序']
---

# Boxes Packing

## 题目描述

Mishka有$n$个空盒子，对于每一个$i(1 \le i \le n)$，第$i$个盒子是一个边长为$a_i$的正方体。

如果满足以下条件，Mishka可以将盒子$i$放入另一个盒子$j$中：

- 第$i$个盒子没有放进另一个盒子里；
- 第$j$个盒子不包含任何其他盒子；
- 第$i$个盒子比第$j$个盒子小$(a_i<a_j )$。

Mishka可以将盒子互相放置任意次数。 他希望尽可能减少可以看见的盒子的数量。 如果一个盒子没有被放入另一个盒子中，则该盒子为可见的。

现请你帮助Mishka确定可见的盒子的最小可能数量。

## 输入格式

第一行包含一个整数$n(1 \le n \le 5000)$，表示Mishka有的空盒子数量。

第二行包含$n$个整数$a_1$，$a_2$，$...$，$a_n(1 \le a_i \le 10^9)$，$a_i$表示第$i$个盒子的边长。

## 输出格式

输出可见的盒子的最小可能数量。

## 样例 #1

### 输入

```
3
1 2 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
4
4 2 4 3

```

### 输出

```
2

```



---

---
title: "Nearest Minimums"
layout: "post"
diff: 普及-
pid: CF911A
tag: ['枚举', '排序', '位运算']
---

# Nearest Minimums

## 题目描述

You are given an array of $ n $ integer numbers $ a_{0},a_{1},...,a_{n-1} $ . Find the distance between two closest (nearest) minimums in it. It is guaranteed that in the array a minimum occurs at least two times.
找到一个长度为n的序列中，距离最短的最小值的距离。

## 输入格式

The first line contains positive integer $ n $ ( $ 2<=n<=10^{5} $ ) — size of the given array. The second line contains $ n $ integers $ a_{0},a_{1},...,a_{n-1} $ ( $ 1<=a_{i}<=10^{9} $ ) — elements of the array. It is guaranteed that in the array a minimum occurs at least two times.

## 输出格式

Print the only number — distance between two nearest minimums in the array.

## 样例 #1

### 输入

```
2
3 3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
3
5 6 5

```

### 输出

```
2

```

## 样例 #3

### 输入

```
9
2 1 3 5 4 1 2 3 1

```

### 输出

```
3

```



---

---
title: "A Compatible Pair"
layout: "post"
diff: 普及-
pid: CF934A
tag: ['贪心', '枚举', '排序']
---

# A Compatible Pair

## 题目描述

Nian is a monster which lives deep in the oceans. Once a year, it shows up on the land, devouring livestock and even people. In order to keep the monster away, people fill their villages with red colour, light, and cracking noise, all of which frighten the monster out of coming.

Little Tommy has $ n $ lanterns and Big Banban has $ m $ lanterns. Tommy's lanterns have brightness $ a_{1},a_{2},...,a_{n} $ , and Banban's have brightness $ b_{1},b_{2},...,b_{m} $ respectively.

Tommy intends to hide one of his lanterns, then Banban picks one of Tommy's non-hidden lanterns and one of his own lanterns to form a pair. The pair's brightness will be the product of the brightness of two lanterns.

Tommy wants to make the product as small as possible, while Banban tries to make it as large as possible.

You are asked to find the brightness of the chosen pair if both of them choose optimally.

## 输入格式

The first line contains two space-separated integers $ n $ and $ m $ ( $ 2<=n,m<=50 $ ).

The second line contains $ n $ space-separated integers $ a_{1},a_{2},...,a_{n} $ .

The third line contains $ m $ space-separated integers $ b_{1},b_{2},...,b_{m} $ .

All the integers range from $ -10^{9} $ to $ 10^{9} $ .

## 输出格式

Print a single integer — the brightness of the chosen pair.

## 说明/提示

In the first example, Tommy will hide $ 20 $ and Banban will choose $ 18 $ from Tommy and $ 14 $ from himself.

In the second example, Tommy will hide $ 3 $ and Banban will choose $ 2 $ from Tommy and $ 1 $ from himself.

## 样例 #1

### 输入

```
2 2
20 18
2 14

```

### 输出

```
252

```

## 样例 #2

### 输入

```
5 3
-1 0 1 2 3
-1 0 1

```

### 输出

```
2

```



---

---
title: "Chess Placing"
layout: "post"
diff: 普及-
pid: CF985A
tag: ['排序', '费用流', '概率论']
---

# Chess Placing

## 题目描述

You are given a chessboard of size $ 1×n $ . It is guaranteed that  $ n $ is even. The chessboard is painted like this: "BWBW $ ... $ BW".

Some cells of the board are occupied by the chess pieces. Each cell contains no more than one chess piece. It is known that the total number of pieces equals to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/e98ace5c1ad627053f6404505602ba90672a171b.png).

In one step you can move one of the pieces one cell to the left or to the right. You cannot move pieces beyond the borders of the board. You also cannot move pieces to the cells that are already occupied.

Your task is to place all the pieces in the cells of the same color using the minimum number of moves (all the pieces must occupy only the black cells or only the white cells after all the moves are made).

## 输入格式

The first line of the input contains one integer $ n $ ( $ 2<=n<=100 $ ,  $ n $ is even) — the size of the chessboard.

The second line of the input contains ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/e98ace5c1ad627053f6404505602ba90672a171b.png) integer numbers ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/f69846f45d2fb290f17c0996035d8272d32fce7d.png) ( $ 1<=p_{i}<=n $ ) — initial positions of the pieces. It is guaranteed that all the positions are distinct.

## 输出格式

Print one integer — the minimum number of moves you have to make to place all the pieces in the cells of the same color.

## 说明/提示

In the first example the only possible strategy is to move the piece at the position $ 6 $ to the position $ 5 $ and move the piece at the position $ 2 $ to the position $ 3 $ . Notice that if you decide to place the pieces in the white cells the minimum number of moves will be $ 3 $ .

In the second example the possible strategy is to move ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/4f3653422b6429c3f89311497c438fd20547c4f8.png) in 4 moves, then ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/6c4181624e2b8f95750df668d534111d8ee2005d.png) in 3 moves, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/74a8630d5d683f941562dca49b5d40bcde2fe1ef.png) in 2 moves and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/b97ec32af1cd5347877d0d15bd3de6cc845fde76.png) in 1 move.

## 样例 #1

### 输入

```
6
1 2 6

```

### 输出

```
2

```

## 样例 #2

### 输入

```
10
1 2 3 4 5

```

### 输出

```
10

```



---

---
title: "Micro-World"
layout: "post"
diff: 普及-
pid: CF990B
tag: ['排序']
---

# Micro-World

## 题目描述

You have a Petri dish with bacteria and you are preparing to dive into the harsh micro-world. But, unfortunately, you don't have any microscope nearby, so you can't watch them.

You know that you have $ n $ bacteria in the Petri dish and size of the $ i $ -th bacteria is $ a_i $ . Also you know intergalactic positive integer constant $ K $ .

The $ i $ -th bacteria can swallow the $ j $ -th bacteria if and only if $ a_i > a_j $ and $ a_i \le a_j + K $ . The $ j $ -th bacteria disappear, but the $ i $ -th bacteria doesn't change its size. The bacteria can perform multiple swallows. On each swallow operation any bacteria $ i $ can swallow any bacteria $ j $ if $ a_i > a_j $ and $ a_i \le a_j + K $ . The swallow operations go one after another.

For example, the sequence of bacteria sizes $ a=[101, 53, 42, 102, 101, 55, 54] $ and $ K=1 $ . The one of possible sequences of swallows is: $ [101, 53, 42, 102, \underline{101}, 55, 54] $ $ \to $ $ [101, \underline{53}, 42, 102, 55, 54] $ $ \to $ $ [\underline{101}, 42, 102, 55, 54] $ $ \to $ $ [42, 102, 55, \underline{54}] $ $ \to $ $ [42, 102, 55] $ . In total there are $ 3 $ bacteria remained in the Petri dish.

Since you don't have a microscope, you can only guess, what the minimal possible number of bacteria can remain in your Petri dish when you finally will find any microscope.

## 输入格式

The first line contains two space separated positive integers $ n $ and $ K $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 1 \le K \le 10^6 $ ) — number of bacteria and intergalactic constant $ K $ .

The second line contains $ n $ space separated integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^6 $ ) — sizes of bacteria you have.

## 输出格式

Print the only integer — minimal possible number of bacteria can remain.

## 说明/提示

The first example is clarified in the problem statement.

In the second example an optimal possible sequence of swallows is: $ [20, 15, 10, 15, \underline{20}, 25] $ $ \to $ $ [20, 15, 10, \underline{15}, 25] $ $ \to $ $ [20, 15, \underline{10}, 25] $ $ \to $ $ [20, \underline{15}, 25] $ $ \to $ $ [\underline{20}, 25] $ $ \to $ $ [25] $ .

In the third example no bacteria can swallow any other bacteria.

## 样例 #1

### 输入

```
7 1
101 53 42 102 101 55 54

```

### 输出

```
3

```

## 样例 #2

### 输入

```
6 5
20 15 10 15 20 25

```

### 输出

```
1

```

## 样例 #3

### 输入

```
7 1000000
1 1 1 1 1 1 1

```

### 输出

```
7

```



---

