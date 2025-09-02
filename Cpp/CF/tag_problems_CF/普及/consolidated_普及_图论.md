---
title: "Party"
layout: "post"
diff: 普及/提高-
pid: CF1711B
tag: ['图论']
---

# Party

## 题目描述

A club plans to hold a party and will invite some of its $ n $ members. The $ n $ members are identified by the numbers $ 1, 2, \dots, n $ . If member $ i $ is not invited, the party will gain an unhappiness value of $ a_i $ .

There are $ m $ pairs of friends among the $ n $ members. As per tradition, if both people from a friend pair are invited, they will share a cake at the party. The total number of cakes eaten will be equal to the number of pairs of friends such that both members have been invited.

However, the club's oven can only cook two cakes at a time. So, the club demands that the total number of cakes eaten is an even number.

What is the minimum possible total unhappiness value of the party, respecting the constraint that the total number of cakes eaten is even?

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $ t $ ( $ 1 \leq t \leq 10^4 $ ). The description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 1 \leq n \leq 10^5 $ , $ 0 \leq m \leq \min(10^5,\frac{n(n-1)}{2}) $ ) — the number of club members and pairs of friends.

The second line of each test case contains $ n $ integers $ a_1,a_2, \dots,a_n $ ( $ 0 \leq a_i \leq 10^4 $ ) — the unhappiness value array.

Each of the next $ m $ lines contains two integers $ x $ and $ y $ ( $ 1 \leq x,y \leq n $ , $ x \neq y $ ) indicating that $ x $ and $ y $ are friends. Each unordered pair $ (x,y) $ appears at most once in each test case.

It is guaranteed that both the sum of $ n $ and the sum of $ m $ over all test cases do not exceed $ 10^5 $ .

## 输出格式

For each test case, print a line containing a single integer – the minimum possible unhappiness value of a valid party.

## 说明/提示

In the first test case, all members can be invited. So the unhappiness value is $ 0 $ .

In the second test case, the following options are possible:

- invite $ 1 $ and $ 2 $ ( $ 0 $ cakes eaten, unhappiness value equal to $ 3 $ );
- invite $ 2 $ and $ 3 $ ( $ 0 $ cakes eaten, unhappiness value equal to $ 2 $ );
- invite only $ 1 $ ( $ 0 $ cakes eaten, unhappiness value equal to $ 4 $ );
- invite only $ 2 $ ( $ 0 $ cakes eaten, unhappiness value equal to $ 5 $ );
- invite only $ 3 $ ( $ 0 $ cakes eaten, unhappiness value equal to $ 3 $ );
- invite nobody ( $ 0 $ cakes eaten, unhappiness value equal to $ 6 $ ).

 The minimum unhappiness value is achieved by inviting $ 2 $ and $ 3 $ .In the third test case, inviting members $ 3,4,5 $ generates a valid party with the minimum possible unhappiness value.

## 样例 #1

### 输入

```
4
1 0
1
3 1
2 1 3
1 3
5 5
1 2 3 4 5
1 2
1 3
1 4
1 5
2 3
5 5
1 1 1 1 1
1 2
2 3
3 4
4 5
5 1
```

### 输出

```
0
2
3
2
```



---

---
title: "Tree Cutting"
layout: "post"
diff: 普及/提高-
pid: CF1946C
tag: ['图论', '二分']
---

# Tree Cutting

## 题目描述

You are given a tree with $ n $ vertices.

Your task is to find the maximum number $ x $ such that it is possible to remove exactly $ k $ edges from this tree in such a way that the size of each remaining connected component $ ^{\dagger} $ is at least $ x $ .

 $ ^{\dagger} $ Two vertices $ v $ and $ u $ are in the same connected component if there exists a sequence of numbers $ t_1, t_2, \ldots, t_k $ of arbitrary length $ k $ , such that $ t_1 = v $ , $ t_k = u $ , and for each $ i $ from $ 1 $ to $ k - 1 $ , vertices $ t_i $ and $ t_{i+1} $ are connected by an edge.

## 输入格式

Each test consists of several sets of input data. The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of sets of input data. This is followed by a description of the sets of input data.

The first line of each set of input data contains two integers $ n $ and $ k $ ( $ 1 \le k < n \le 10^5 $ ) — the number of vertices in the tree and the number of edges to be removed.

Each of the next $ n - 1 $ lines of each set of input data contains two integers $ v $ and $ u $ ( $ 1 \le v, u \le n $ ) — the next edge of the tree.

It is guaranteed that the sum of the values of $ n $ for all sets of input data does not exceed $ 10^5 $ .

## 输出格式

For each set of input data, output a single line containing the maximum number $ x $ such that it is possible to remove exactly $ k $ edges from the tree in such a way that the size of each remaining connected component is at least $ x $ .

## 说明/提示

The tree in the first set of input data:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1946C/832ffb4f88c37ab14f5b7a9eaac2d6382d506053.png)After removing the edge $ 1 $ — $ 3 $ , the tree will look as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1946C/fbcdbb17592694a687d8cacf2d552a9f2e19b5fc.png)The tree has split into two connected components. The first component consists of two vertices: $ 1 $ and $ 2 $ . The second connected component consists of three vertices: $ 3, 4 $ and $ 5 $ . In both connected components, there are at least two vertices. It can be shown that the answer $ 3 $ is not achievable, so the answer is $ 2 $ .

## 样例 #1

### 输入

```
6
5 1
1 2
1 3
3 4
3 5
2 1
1 2
6 1
1 2
2 3
3 4
4 5
5 6
3 1
1 2
1 3
8 2
1 2
1 3
2 4
2 5
3 6
3 7
3 8
6 2
1 2
2 3
1 4
4 5
5 6
```

### 输出

```
2
1
3
1
1
2
```



---

---
title: "0, 1, 2, Tree!"
layout: "post"
diff: 普及/提高-
pid: CF1950F
tag: ['图论']
---

# 0, 1, 2, Tree!

## 题目描述

查找满足条件的有根树 $^{\dagger}$ 的最小高度。

其中 $a+b+c$ 个顶点满足以下条件：

- $a$ 个顶点恰好有 $2$ 个子顶点，

- $b$ 个顶点恰好有 $1$ 个子顶点，

- $c$ 个顶点没有子顶点。

如果没有这样的树，输出 $-1$。

如：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1950F/0c6b0806a993f448977c57ce3c99533fc6610921.png)

上面的树植根于顶部顶点，每个顶点都标有它的子节点数。

这里 $a=2,b=1,c=3$，高度为 $2$。

 $^{\dagger}$：有根树是指一个没有循环的连通图，有一个特殊的顶点称为根。在有根树中，在由边连接的任意两个顶点，一个顶点是父顶点（离根更近的顶点），另一个是子顶点。

树中两个顶点之间的距离是它们之间最短路径中的边数。有根树的高度是从顶点到根部的最大距离。

## 输入格式

第一行包含一个整数 $t$（$1\leq t\leq 10^4$）表示测试用例的数量。
每个测试用例的唯一一行包含三个整数 $a$，$b$ 和 $c$（$0\leq a、b、c\leq 10^5$；$1\leq a+b+c$）。

所有测试用例的 $a+b+c$ 之和不超过 $3 \cdot 10^5$。

## 输出格式

对于每个测试用例，如果不存在这样的树，输出 $-1$。

否则输出一个整数——满足条件的树的最小高度。

## 样例 #1

### 样例输入 #1

```
10
2 1 3
0 0 1
0 1 1
1 0 2
1 1 3
3 1 4
8 17 9
24 36 48
1 0 0
0 3 1
```

### 样例输出 #1

```
2
0
1
1
-1
3
6
-1
-1
3
```

## 说明/提示

第一个测试用例如图所示。树的高度不能低于 $2$。

在第二个测试用例中，您可以形成一个只有一个顶点且没有边的树。它的高度为 $0$，这显然是最佳的。

在第三个测试用例中，您可以形成一个由单个边连接的两个顶点的树。它的高度为 $1$，这显然是最佳的。

## 样例 #1

### 输入

```
10
2 1 3
0 0 1
0 1 1
1 0 2
1 1 3
3 1 4
8 17 9
24 36 48
1 0 0
0 3 1
```

### 输出

```
2
0
1
1
-1
3
6
-1
-1
3
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
title: "pSort"
layout: "post"
diff: 普及/提高-
pid: CF28B
tag: ['图论', '并查集']
---

# pSort

## 题目描述

给定一个长度为 $n$ 的数列 $\{a_n\}$，初始时 $\{a_n\} = \{1, 2, \dots, n\}$。位置 $i$ 上的数可以和位置 $i \pm d_i$ 上的数交换。给定一个 $1 \sim n$ 的全排列，问初始的数列可否交换成给定的形式。

## 输入格式

第一行一个整数 $n$。

第二行 $n$ 个互不相同的整数表示目标数列。

第三行 $n$ 个整数表示 $d_1, d_2, \dots, d_n$。

## 输出格式

如果能交换到给定样式，输出 `YES`，否则输出 `NO`。

## 说明/提示

$1 \le n \le 100$

## 样例 #1

### 输入

```
5
5 4 3 2 1
1 1 1 1 1

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
7
4 3 5 1 2 7 6
4 6 6 1 6 6 1

```

### 输出

```
NO

```

## 样例 #3

### 输入

```
7
4 2 5 1 3 7 6
4 6 6 1 6 6 1

```

### 输出

```
YES

```



---

---
title: "Andryusha and Colored Balloons"
layout: "post"
diff: 普及/提高-
pid: CF780C
tag: ['递归', '状态合并', '图论建模']
---

# Andryusha and Colored Balloons

## 题目描述

题意:

有一颗n个节点的树,进行有限制染色,问染色的最少颜色数,以及每个点的颜色(从1标号,标号不能超过颜色数).
限制:相邻三个点的颜色不能相同.

## 输入格式

第一行一个n,
接下来n-1行<x,y>,表示x与y之间有一条连边.

## 输出格式

第一行一个数,为最小颜色数.
接下来n个数,为[1,n]的点的颜色.

## 说明/提示

n:[3,2e5]

## 样例 #1

### 输入

```
3
2 3
1 3

```

### 输出

```
3
1 3 2 
```

## 样例 #2

### 输入

```
5
2 3
5 3
4 3
1 3

```

### 输出

```
5
1 3 2 5 4 
```

## 样例 #3

### 输入

```
5
2 1
3 2
4 3
5 4

```

### 输出

```
3
1 2 3 1 2 
```



---

---
title: "Friends"
layout: "post"
diff: 普及/提高-
pid: CF94B
tag: ['图论', '枚举']
---

# Friends

## 题目描述

有一天，一个叫做伊戈尔-凯的人放弃编程，转攻数学题。一个深秋的夜晚，他坐在桌旁读书，想着数学问题。
书上有着一段话吸引了他的注意：“在任六人中有三个人互相认识或互相不认识。”
伊戈尔完全无法理解为什么至少有六个人。“那对不起，我觉得五个人也一样，”他脑子里开始胡思乱想“让我试试...马克思，利亚，瓦娃--他们互相认识，额..再加一个迪玛和欧莱格，对瓦娃来说他们三个互不认识！哈哈哈哈哈，这个定理就是一个渣渣。”
伊戈尔带着他的5个朋友，让他们记下来，他们中谁互为朋友。现在他想看看这五个人是否真的认识三对或三对不认识的人。

## 输入格式

第一行包括了一个整数m(0<=m<=10)这是伊戈尔的五个朋友之间的互相认识的关系的个数。
接下来m行每行有两个数aibi（1<=ai,bi<=5;ai!=bi）,表示ai与bi是互相认识。每个关系是准确的也是对称的，即若x认识y，y也认识x。

## 输出格式

如果这五个人中既没有三个不认识的也没有三个互相认识的，输出：“FAIL”。其他情况输出“WIN“

## 样例 #1

### 输入

```
4
1 3
2 3
1 4
5 3

```

### 输出

```
WIN

```

## 样例 #2

### 输入

```
5
1 2
2 3
3 4
4 5
5 1

```

### 输出

```
FAIL

```



---

