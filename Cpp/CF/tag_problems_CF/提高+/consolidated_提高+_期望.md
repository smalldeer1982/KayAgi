---
title: "Vasya and Magic Matrix"
layout: "post"
diff: 提高+/省选-
pid: CF1042E
tag: ['前缀和', '期望', '逆元']
---

# Vasya and Magic Matrix

## 题目描述

Vasya has got a magic matrix $ a $ of size $ n \times m $ . The rows of the matrix are numbered from $ 1 $ to $ n $ from top to bottom, the columns are numbered from $ 1 $ to $ m $ from left to right. Let $ a_{ij} $ be the element in the intersection of the $ i $ -th row and the $ j $ -th column.

Vasya has also got a chip. Initially, the chip is in the intersection of the $ r $ -th row and the $ c $ -th column (that is, in the element $ a_{rc} $ ). Vasya performs the following process as long as possible: among all elements of the matrix having their value less than the value of the element with the chip in it, Vasya randomly and equiprobably chooses one element and moves his chip to this element.

After moving the chip, he adds to his score the square of the Euclidean distance between these elements (that is, between the element in which the chip is now and the element the chip was moved from). The process ends when there are no elements having their values less than the value of the element with the chip in it.

Euclidean distance between matrix elements with coordinates $ (i_1, j_1) $ and $ (i_2, j_2) $ is equal to $ \sqrt{(i_1-i_2)^2 + (j_1-j_2)^2} $ .

Calculate the expected value of the Vasya's final score.

It can be shown that the answer can be represented as $ \frac{P}{Q} $ , where $ P $ and $ Q $ are coprime integer numbers, and $ Q \not\equiv 0~(mod ~ 998244353) $ . Print the value $ P \cdot Q^{-1} $ modulo $ 998244353 $ .

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ $ (1 \le n, m \le 1\,000) $ — the number of rows and the number of columns in the matrix $ a $ .

The following $ n $ lines contain description of the matrix $ a $ . The $ i $ -th line contains $ m $ integers $ a_{i1}, a_{i2}, \dots, a_{im} ~ (0 \le a_{ij} \le 10^9) $ .

The following line contains two integers $ r $ and $ c $ $ (1 \le r \le n, 1 \le c \le m) $ — the index of row and the index of column where the chip is now.

## 输出格式

Print the expected value of Vasya's final score in the format described in the problem statement.

## 说明/提示

In the first example, Vasya will move his chip exactly once. The expected value of the final score is equal to $ \frac{1^2 + 2^2+ 1^2}{3} = 2 $ .

## 样例 #1

### 输入

```
1 4
1 1 2 1
1 3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2 3
1 5 7
2 3 1
1 2

```

### 输出

```
665496238

```



---

---
title: "Beautiful Mirrors"
layout: "post"
diff: 提高+/省选-
pid: CF1265E
tag: ['动态规划 DP', '期望']
---

# Beautiful Mirrors

## 题目描述

Creatnx has $ n $ mirrors, numbered from $ 1 $ to $ n $ . Every day, Creatnx asks exactly one mirror "Am I beautiful?". The $ i $ -th mirror will tell Creatnx that he is beautiful with probability $ \frac{p_i}{100} $ for all $ 1 \le i \le n $ .

Creatnx asks the mirrors one by one, starting from the $ 1 $ -st mirror. Every day, if he asks $ i $ -th mirror, there are two possibilities:

- The $ i $ -th mirror tells Creatnx that he is beautiful. In this case, if $ i = n $ Creatnx will stop and become happy, otherwise he will continue asking the $ i+1 $ -th mirror next day;
- In the other case, Creatnx will feel upset. The next day, Creatnx will start asking from the $ 1 $ -st mirror again.

You need to calculate [the expected number](https://en.wikipedia.org/wiki/Expected_value) of days until Creatnx becomes happy.

This number should be found by modulo $ 998244353 $ . Formally, let $ M = 998244353 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 输入格式

The first line contains one integer $ n $ ( $ 1\le n\le 2\cdot 10^5 $ ) — the number of mirrors.

The second line contains $ n $ integers $ p_1, p_2, \ldots, p_n $ ( $ 1 \leq p_i \leq 100 $ ).

## 输出格式

Print the answer modulo $ 998244353 $ in a single line.

## 说明/提示

In the first test, there is only one mirror and it tells, that Creatnx is beautiful with probability $ \frac{1}{2} $ . So, the expected number of days until Creatnx becomes happy is $ 2 $ .

## 样例 #1

### 输入

```
1
50

```

### 输出

```
2

```

## 样例 #2

### 输入

```
3
10 20 50

```

### 输出

```
112

```



---

---
title: "Let's Play Osu!"
layout: "post"
diff: 提高+/省选-
pid: CF235B
tag: ['期望']
---

# Let's Play Osu!

## 题目描述

你在玩一个叫做 Osu 的游戏（某音游）！我们来简化一下游戏规则。一局游戏中需要点击 $n$ 次。每一次点击有两种结果：正确或失误。我们定义正确为符号 `O`，失误为 `X`，那么整局游戏可以被写成一个长度为 $n$ 的由字符 `X` 或 `O` 组成的字符串。

用这个字符串你可以用以下的方法计算游戏的得分：对于一个极大的连续的 `O` 连击，将连击的次数的平方加入到总得分中（即连续的 `O` 的个数的平方）。举例说明，如果你的游戏序列为 `OOXOOOXXOO`，那么极大连续的 `O` 连击共有三个：`OO`，`OOO`，`OO`，所以你的总得分为 $2^2 + 3^2 + 2^2= 17$ 。如果整局游戏里没有一次成功的点击那么总得分就为 $0$。

你现在知道了第 $i$ 次 ($1\leq i\leq n$)点击成功的概率为 $p_i$，换句话说，字符串中第 $i$ 个字符有 $p_i$ 的概率成为 `O`，有 $1-p_i$ 的概率成为 `X`，你的任务是算出你游戏总得分的期望值。

## 输入格式

第一行包含一个整数表示点击的次数 $n$ $( 1\leq n\leq 10^5 )$ 第二行包含 $n$ 个由空格间隔开的实数 $p_1,p_2,...,p_n ( 0\leq p_i\leq 1 )$ 输入的 $p_i$ 最多为六位小数。

## 输出格式

输出一个实数——你游戏的期望得分。你的答案必须与标准答案的误差不超过 $10^{-6}$。

## 说明/提示

$3$ 位字符串一共有 $8$ 种不同的情况。每一种出现的概率为 $0.125$ 所以期望得分是 $\dfrac{(9+4+2+1+4+1+1)}{8}=2.75$。

感谢@[凄魉](/user/45876) 提供的翻译。

## 样例 #1

### 输入

```
3
0.5 0.5 0.5

```

### 输出

```
2.750000000000000

```

## 样例 #2

### 输入

```
4
0.7 0.2 0.1 0.9

```

### 输出

```
2.489200000000000

```

## 样例 #3

### 输入

```
5
1 1 1 1 1

```

### 输出

```
25.000000000000000

```



---

---
title: "Game on Tree"
layout: "post"
diff: 提高+/省选-
pid: CF280C
tag: ['数学', '期望']
---

# Game on Tree

## 题目描述

给定一棵有根树，结点编号从 $1$ 到 $n$。根结点为 $1$ 号结点。

对于每一次操作，等概率的选择一个**尚未被删去**的结点并将它及其子树全部删去。当所有结点被删除之后，游戏结束；也就是说，删除 $1$ 号结点后游戏即结束。

要求求出删除所有结点的期望操作次数。

## 输入格式

第一行，一个正整数 $n$ 表示结点数量。

接下来 $n-1$ 行每行两个数，表示树上的一条连接 $a_i$ 与 $b_i$ 的边 $(a_i,b_i)$

保证给定的数据是一棵树。

## 输出格式

输出一个实数，表示期望操作次数。答案误差在 $10^{-6}$ 之内则认为正确。

**样例解释**

在第一个样例中，有两种情况：

一种是直接删除根（即 $1$ 号结点），另一种是先删去 $2$ 号结点，再删除 $1$ 号结点。

操作次数的期望是 $1\times \dfrac12+2\times\dfrac12=1.5$。

在第二个样例中，情况更为复杂。其中有两种情况会将问题转化成第一个样例，而剩下的一种情况会一次全部删除。

操作次数的期望是 $1\times\dfrac13+(1+1.5)\times\dfrac23=\dfrac13+\dfrac53=2$。

## 样例 #1

### 输入

```
2
1 2

```

### 输出

```
1.50000000000000000000

```

## 样例 #2

### 输入

```
3
1 2
1 3

```

### 输出

```
2.00000000000000000000

```



---

---
title: "Exposition"
layout: "post"
diff: 提高+/省选-
pid: CF6E
tag: ['单调队列', '枚举', '期望', '队列']
---

# Exposition

## 题目描述

There are several days left before the fiftieth birthday of a famous Berland's writer Berlbury. In this connection the local library decided to make an exposition of the works of this famous science-fiction writer. It was decided as well that it is necessary to include into the exposition only those books that were published during a particular time period. It is obvious that if the books differ much in size, the visitors will not like it. That was why the organizers came to the opinion, that the difference between the highest and the lowest books in the exposition should be not more than $ k $ millimeters.

The library has $ n $ volumes of books by Berlbury, arranged in chronological order of their appearance. The height of each book in millimeters is know, it is $ h_{i} $ . As Berlbury is highly respected in the city, the organizers want to include into the exposition as many books as possible, and to find out what periods of his creative work they will manage to cover. You are asked to help the organizers cope with this hard task.

## 输入格式

The first line of the input data contains two integer numbers separated by a space $ n $ ( $ 1<=n<=10^{5} $ ) and $ k $ ( $ 0<=k<=10^{6} $ ) — the amount of books by Berlbury in the library, and the maximum allowed height difference between the lowest and the highest books. The second line contains $ n $ integer numbers separated by a space. Each number $ h_{i} $ ( $ 1<=h_{i}<=10^{6} $ ) is the height of the $ i $ -th book in millimeters.

## 输出格式

In the first line of the output data print two numbers $ a $ and $ b $ (separate them by a space), where $ a $ is the maximum amount of books the organizers can include into the exposition, and $ b $ — the amount of the time periods, during which Berlbury published $ a $ books, and the height difference between the lowest and the highest among these books is not more than $ k $ milllimeters.

In each of the following $ b $ lines print two integer numbers separated by a space — indexes of the first and the last volumes from each of the required time periods of Berlbury's creative work.

## 样例 #1

### 输入

```
3 3
14 12 10

```

### 输出

```
2 2
1 2
2 3

```

## 样例 #2

### 输入

```
2 0
10 10

```

### 输出

```
2 1
1 2

```

## 样例 #3

### 输入

```
4 5
8 19 10 13

```

### 输出

```
2 1
3 4

```



---

