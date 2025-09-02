---
title: "Traps"
layout: "post"
diff: 普及+/提高
pid: CF1684D
tag: ['贪心', '差分']
---

# Traps

## 题目描述

There are $ n $ traps numbered from $ 1 $ to $ n $ . You will go through them one by one in order. The $ i $ -th trap deals $ a_i $ base damage to you.

Instead of going through a trap, you can jump it over. You can jump over no more than $ k $ traps. If you jump over a trap, it does not deal any damage to you. But there is an additional rule: if you jump over a trap, all next traps damages increase by $ 1 $ (this is a bonus damage).

Note that if you jump over a trap, you don't get any damage (neither base damage nor bonus damage). Also, the bonus damage stacks so, for example, if you go through a trap $ i $ with base damage $ a_i $ , and you have already jumped over $ 3 $ traps, you get $ (a_i + 3) $ damage.

You have to find the minimal damage that it is possible to get if you are allowed to jump over no more than $ k $ traps.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases. Description of the test cases follows.

The first line of each test case contains two integers $ n $ and $ k $ ( $ 1 \le n \le 2 \cdot 10^5 $ , $ 1 \le k \le n $ ) — the number of traps and the number of jump overs that you are allowed to make.

The second line of each test case contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) — base damage values of all traps.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case output a single integer — the minimal total damage that it is possible to get if you are allowed to jump over no more than $ k $ traps.

## 说明/提示

In the first test case it is allowed to jump over all traps and take $ 0 $ damage.

In the second test case there are $ 5 $ ways to jump over some traps:

1. Do not jump over any trap.Total damage: $ 5 + 10 + 11 + 5 = 31 $ .
2. Jump over the $ 1 $ -st trap.Total damage: $ \underline{0} + (10 + 1) + (11 + 1) + (5 + 1) = 29 $ .
3. Jump over the $ 2 $ -nd trap.Total damage: $ 5 + \underline{0} + (11 + 1) + (5 + 1) = 23 $ .
4. Jump over the $ 3 $ -rd trap.Total damage: $ 5 + 10 + \underline{0} + (5 + 1) = 21 $ .
5. Jump over the $ 4 $ -th trap.Total damage: $ 5 + 10 + 11 + \underline{0} = 26 $ .

To get minimal damage it is needed to jump over the $ 3 $ -rd trap, so the answer is $ 21 $ .

In the third test case it is optimal to jump over the traps $ 1 $ , $ 3 $ , $ 4 $ , $ 5 $ , $ 7 $ :

Total damage: $ 0 + (2 + 1) + 0 + 0 + 0 + (2 + 4) + 0 = 9 $ .

## 样例 #1

### 输入

```
5
4 4
8 7 1 4
4 1
5 10 11 5
7 5
8 2 5 15 11 2 8
6 3
1 2 3 4 5 6
1 1
7
```

### 输出

```
0
21
9
6
0
```



---

---
title: "Difference Array"
layout: "post"
diff: 普及+/提高
pid: CF1707B
tag: ['差分']
---

# Difference Array

## 题目描述

你有一个初始长度为 $n$ 的有序数组 $a$（从小到大）。设 $a$ 当前长度为 $l$，你要对 $a$ 作差分，即令 $b_i = a_{i+1} - a_i(1\le i < l)$，然后将 $b$ 数组从小到大排序，接着让 $a_i = b_i(1 \le i < l)$，并继续执行上述操作。

显然，每一次操作后 $a$ 数组的长度都会减少 $1$；执行 $n - 1$ 次操作之后，$a$ 中只会剩下一个元素，请你输出这个剩下的元素。

## 输入格式

输入包含多组数据，第一行一个正整数 $t(0 < t \le 10^4)$，表示数据组数。

对于每一组数据：

- 第一行一个正整数 $n(1 < n \le 10^5)$，表示 $a$ 数组的初始长度

- 第二行 $n$ 个整数 $a_i(0 \le a_i \le 5\times10^5)$，表示 $a$ 数组。

## 输出格式

$t$ 行，每行一个正整数，表示每一组数据中 $a$ 数组最终剩下的那个元素。

### 样例解释

令 $\operatorname{sort}(a)$ 表示将 $a$ 数组从小到大排序。

- 对于第一组数据，初始的 $a = \{1,10,100\}$；在第一次操作后，$a=\operatorname{sort}(\{10-1,100-10\})=\{9,90\}$；在第二次操作后，$a = \operatorname{sort}(\{90-9\})=\{81\}$。故答案为 $81$。

- 对于第二组数据，初始的 $a=\{4,8,9,13\}$；在第一次操作后，$a=\operatorname{sort}(\{8-4,9-8,13-9\})=\{1,4,4\}$；在第二次操作后，$a=\operatorname{sort}(\{4-1,4-4\})=\{0,3\}$；在第三次操作后，$a=\operatorname{sort}(\{3-0\})=\{3\}$。故答案为 $3$。

## 样例 #1

### 输入

```
5
3
1 10 100
4
4 8 9 13
5
0 0 0 8 13
6
2 4 8 16 32 64
7
0 0 0 0 0 0 0
```

### 输出

```
81
3
1
2
0
```



---

---
title: "Fools and Roads"
layout: "post"
diff: 普及+/提高
pid: CF191C
tag: ['深度优先搜索 DFS', '最近公共祖先 LCA', '差分']
---

# Fools and Roads

## 题目描述

有一颗 $n$  个节点的树，$k$  次旅行，问每一条边被走过的次数。

## 输入格式

第一行一个整数 $n$  （$2\leq n\leq 10^5$ ）。

接下来 $n-1$  行，每行两个正整数 $x,y$  （$1\leq x,y\leq n,x\neq y$ ），表示 $x$  与 $y$  之间有一条连边。

接下来一个整数 $k$  （$0\leq k\leq 10^5$ ）。

接下来 $k$  行，每行两个正整数 $x,y$  （$1\leq x,y\leq n$ ），表示有一个从 $x$  到 $y$  的旅行。

## 输出格式

一行空格分隔的 $n - 1$ 个整数，按输入顺序输出每一条边被走过的次数。

Translated by @larryzhong

## 样例 #1

### 输入

```
5
1 2
1 3
2 4
2 5
2
1 4
3 5

```

### 输出

```
2 1 1 1 

```

## 样例 #2

### 输入

```
5
3 4
4 5
1 4
2 4
3
2 3
1 3
3 5

```

### 输出

```
3 1 1 1 

```



---

---
title: "Mischievous Shooter"
layout: "post"
diff: 普及+/提高
pid: CF1921G
tag: ['枚举', '前缀和', '差分']
---

# Mischievous Shooter

## 题目描述

Once the mischievous and wayward shooter named Shel found himself on a rectangular field of size $ n \times m $ , divided into unit squares. Each cell either contains a target or not.

Shel only had a lucky shotgun with him, with which he can shoot in one of the four directions: right-down, left-down, left-up, or right-up. When fired, the shotgun hits all targets in the chosen direction, the Manhattan distance to which does not exceed a fixed constant $ k $ . The Manhattan distance between two points $ (x_1, y_1) $ and $ (x_2, y_2) $ is equal to $ |x_1 - x_2| + |y_1 - y_2| $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1921G/07ae9ceed185244b94a445086f5cae84fbf84168.png) Possible hit areas for $ k = 3 $ .Shel's goal is to hit as many targets as possible. Please help him find this value.

## 输入格式

Each test consists of several test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. Then follows the description of the test cases.

The first line of each test case contains field dimensions $ n $ , $ m $ , and the constant for the shotgun's power $ k $ ( $ 1 \le n, m, k \le 10^5, 1 \le n \cdot m \le 10^5 $ ).

Each of the next $ n $ lines contains $ m $ characters — the description of the next field row, where the character '.' means the cell is empty, and the character '\#' indicates the presence of a target.

It is guaranteed that the sum of $ n \cdot m $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output a single integer on a separate line, which is equal to the maximum possible number of hit targets with one shot.

## 说明/提示

Possible optimal shots for the examples in the statement:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1921G/027b9a5a762b96357d7642f8eac1d4cf8d7ae93a.png)

## 样例 #1

### 输入

```
4
3 3 1
.#.
###
.#.
2 5 3
###..
...##
4 4 2
..##
###.
#..#
####
2 1 3
#
#
```

### 输出

```
3
4
5
2
```



---

---
title: "QED's Favorite Permutation"
layout: "post"
diff: 普及+/提高
pid: CF2030D
tag: ['线段树', '差分']
---

# QED's Favorite Permutation

## 题目描述

你有一个长度为 $n$ 的排列 $p$，也就是说，$1$ 到 $n$ 中的每个正整数都在 $p$ 中出现恰好一次。同时你还有一个长度也为 $n$ 的字符串 $s$，其中仅含 `L` 和 `R` 两种字符。（排列和字符串的下标均从 $1$ 开始编号）

定义一次操作为：任意选择一个编号 $i$（$1 \le i \le n$），在这之后：

* 如果 $s_i$ 为 `L`，则交换 $p_i$ 和 $p_{i-1}$。（保证 $s_1$ 不为 `L`）

* 如果 $s_i$ 为 `R`，则交换 $p_i$ 和 $p_{i+1}$。（保证 $s_n$ 不为 `R`）

接下来给出 $q$ 次询问，在第 $i$ 次询问中（$1 \le i \le q$），你将会得到一个编号 $x_i$（$1 \le x_i \le n$），表示如果 $s_{x_i}$ 为 `L`，则你需要将其改为 `R`；反之如果 $s_{x_i}$ 为 `R`，则你需要将其改为 `L`。在修改完成之后，你还需要判断能否通过上述操作使得排列 $p$ 单调递增（操作次数不限），即对任意的 $1 \le i \le n-1$，都有 $p_i < p_{i+1}$。

**询问中对字符串 $\bm{s}$ 的修改均为永久性的，会在询问结束后保留。在回答询问的过程中，你不应对排列 $\bm{p}$ 进行任何真实的操作。**

## 输入格式

第一行一个正整数 $t$（$1 \le t \le 10^4$），表示测试数据的组数。对于每组测试数据而言：

第一行包含两个正整数 $n,q$（$1\le n,q \le 2 \times 10^5$，$n \ge 3$），分别表示排列的长度和询问的次数。

第二行包含 $n$ 个正整数 $p_1,p_2,...,p_n$（$1 \le p_i \le n$），表示排列 $p$。

第三行包含一个长度为 $n$ 的字符串 $s$，保证 $s_i \in \{ \texttt{L}, \texttt{R} \}，s_1 = \texttt{R}，s_n = \texttt{L}$。

接下来 $q$ 行，其中第 $i$ 行包含一个正整数 $x_i$（$1 \le x_i \le n$），表示要修改的字符的编号。

保证所有测试数据中 $n$ 和 $q$ 的总和都不超过 $2 \times 10^5$。

## 输出格式

对于每个询问，在单独一行输出一个字符串表示答案。如果在修改完成之后能通过上述操作使得排列 $p$ 单调递增（操作次数不限），则输出 `YES`；否则输出 `NO`。评测时不区分大小写，例如 `Yes`，`yES` 等均被认为与 `YES` 等价。

### 【样例解释】

对于第一组测试数据，在第一次询问之后，$s = \texttt{RRRLL}$。我们可以通过如下操作序列使得排列 $p$ 单调递增：

* 初始时，$p=[1,4,2,5,3]$。

* 选择 $i=2$ 进行一次操作，由于 $s_2 = \texttt{R}$，所以我们交换 $p_2$ 和 $p_3$，得到 $p=[1,2,4,5,3]$。

* 选择 $i=5$ 进行一次操作，由于 $s_5 = \texttt{L}$，所以我们交换 $p_5$ 和 $p_4$，得到 $p=[1,2,4,3,5]$。

* 选择 $i=4$ 进行一次操作，由于 $s_4 = \texttt{L}$，所以我们交换 $p_4$ 和 $p_3$，得到 $p=[1,2,3,4,5]$。此时，排列 $p$ 已经单调递增。

因此，对于第一次询问你应当输出 `YES`。

对于第一组测试数据可以证明，在三次询问对字符串 $s$ 的修改完成之后，不可能再通过上述操作使得排列 $p$ 单调递增。因此，对于第三次询问你应当输出 `NO`。




Translated by FruitWasTaken

## 样例 #1

### 输入

```
3
5 3
1 4 2 5 3
RLRLL
2
4
3
8 5
1 5 2 4 8 3 6 7
RRLLRRRL
4
3
5
3
4
6 2
1 2 3 4 5 6
RLRLRL
4
5
```

### 输出

```
YES
YES
NO
NO
YES
NO
NO
NO
YES
YES
```



---

---
title: "Ardent Flames"
layout: "post"
diff: 普及+/提高
pid: CF2037F
tag: ['二分', '离散化', '差分']
---

# Ardent Flames

## 题目描述

You have obtained the new limited event character Xilonen. You decide to use her in combat.

There are $ n $ enemies in a line. The $ i $ 'th enemy from the left has health $ h_i $ and is currently at position $ x_i $ . Xilonen has an attack damage of $ m $ , and you are ready to defeat the enemies with her.

Xilonen has a powerful "ground stomp" attack. Before you perform any attacks, you select an integer $ p $ and position Xilonen there ( $ p $ can be any integer position, including a position with an enemy currently). Afterwards, for each attack, she deals $ m $ damage to an enemy at position $ p $ (if there are any), $ m-1 $ damage to enemies at positions $ p-1 $ and $ p+1 $ , $ m-2 $ damage to enemies at positions $ p-2 $ and $ p+2 $ , and so on. Enemies that are at least a distance of $ m $ away from Xilonen take no damage from attacks.

Formally, if there is an enemy at position $ x $ , she will deal $ \max(0,m - |p - x|) $ damage to that enemy each hit. Note that you may not choose a different $ p $ for different attacks.

Over all possible $ p $ , output the minimum number of attacks Xilonen must perform to defeat at least $ k $ enemies. If it is impossible to find a $ p $ such that eventually at least $ k $ enemies will be defeated, output $ -1 $ instead. Note that an enemy is considered to be defeated if its health reaches $ 0 $ or below.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) – the number of test cases.

The first line of each test case contains three integers $ n $ , $ m $ , and $ k $ ( $ 1 \leq k \leq n \leq 10^5 $ , $ 1 \leq m \leq 10^9 $ ).

The following line contains $ n $ integers $ h_1, h_2, ..., h_n $ ( $ 1 \leq h_i \leq 10^9 $ ).

The last line of each testcase contains $ n $ integers $ x_1, x_2, ..., x_n $ ( $ 1\leq x_i \leq 10^9 $ , $ x_i < x_{i+1} $ for all $ 1 \leq i < n $ )

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^5 $ .

## 输出格式

For each test case, output an integer on a new line, the minimum number of attacks that must be performed to defeat at least $ k $ enemies. If it is impossible to find a $ p $ such that eventually at least $ k $ enemies will be defeated, output $ -1 $ instead.

## 说明/提示

In the first testcase, it is optimal to select $ p=2 $ . Each attack, the first enemy takes $ 5-|2-1|=4 $ damage, the second enemy takes $ 5 $ damage, the third enemy takes $ 4 $ damage, the fourth enemy takes $ 3 $ damage, and the fifth enemy takes $ 2 $ damage. After $ 2 $ attacks, the first three enemies will be defeated. It can be shown that it is impossible to defeat $ 3 $ enemies in less than $ 2 $ attacks, no matter which $ p $ is selected.

In the second testcase, we must kill all $ 9 $ enemies. By selecting $ p=5 $ , all nine enemies will be defeated in $ 2 $ attacks.

In the third testcase, we must kill both enemies. However, it can be shown that no $ p $ selected will damage both enemies at the same time, so the answer is $ -1 $ .

In the fourth testcase, selecting $ p=1 $ will enable us to defeat the first enemy in $ 6969697 $ attacks.

In the fifth testcase, selecting $ p=10 $ will make each enemy take $ 1 $ damage per attack. Both enemies will be defeated in $ 15 $ attacks.

## 样例 #1

### 输入

```
6
5 5 3
7 7 7 7 7
1 2 3 4 5
9 5 9
2 4 6 8 10 8 6 4 2
1 2 3 4 5 6 7 8 9
2 10 2
1 1
1 20
2 10 1
69696969 420420420
1 20
2 10 2
10 15
1 19
2 2 2
1000000000 1
1 3
```

### 输出

```
2
2
-1
6969697
15
1000000000
```



---

---
title: "Present"
layout: "post"
diff: 普及+/提高
pid: CF460C
tag: ['模拟', '线段树', '差分']
---

# Present

## 题目描述

Little beaver is a beginner programmer, so informatics is his favorite subject. Soon his informatics teacher is going to have a birthday and the beaver has decided to prepare a present for her. He planted $ n $ flowers in a row on his windowsill and started waiting for them to grow. However, after some time the beaver noticed that the flowers stopped growing. The beaver thinks it is bad manners to present little flowers. So he decided to come up with some solutions.

There are $ m $ days left to the birthday. The height of the $ i $ -th flower (assume that the flowers in the row are numbered from $ 1 $ to $ n $ from left to right) is equal to $ a_{i} $ at the moment. At each of the remaining $ m $ days the beaver can take a special watering and water $ w $ contiguous flowers (he can do that only once at a day). At that each watered flower grows by one height unit on that day. The beaver wants the height of the smallest flower be as large as possible in the end. What maximum height of the smallest flower can he get?

## 输入格式

The first line contains space-separated integers $ n $ , $ m $ and $ w $ $ (1<=w<=n<=10^{5}; 1<=m<=10^{5}) $ . The second line contains space-separated integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=10^{9}) $ .

## 输出格式

Print a single integer — the maximum final height of the smallest flower.

## 说明/提示

In the first sample beaver can water the last 3 flowers at the first day. On the next day he may not to water flowers at all. In the end he will get the following heights: \[2, 2, 2, 3, 2, 2\]. The smallest flower has height equal to 2. It's impossible to get height 3 in this test.

## 样例 #1

### 输入

```
6 2 3
2 2 2 2 1 1

```

### 输出

```
2

```

## 样例 #2

### 输入

```
2 5 1
5 8

```

### 输出

```
9

```



---

---
title: "Cellular Network"
layout: "post"
diff: 普及+/提高
pid: CF702C
tag: ['二分', '差分']
---

# Cellular Network

## 题目描述

在直线上给出n个城市的位置(x坐标)和在同一直线上的m个蜂窝塔的位置(x坐标)。所有的塔都以同样的方式工作——它们为所有城市提供蜂窝网络，这些城市位于离塔不超过r的距离处才能被蜂窝网络覆盖。

你的任务是找出使得每个城市都能被蜂窝网络覆盖的最小r值，即每个城市在距离r的范围内至少有一个蜂窝塔。

如果r=0，则塔仅为其所在的位置提供蜂窝网络。一个塔可以为任意数量的城市提供蜂窝网络，但是所有这些城市都必须在距离塔不超过r的距离上。

## 输入格式

第一行包含两个正整数n和m，表示有n个城市与m个蜂窝塔。

第二行包含n个整数a[1],a[2]...a[n](a[i]>=a[i-1])，表示每个城市的位置(x坐标)

第三行包含m个整数b[1],b[2]...b[m](b[i]>=b[i-1])，表示每个蜂窝塔的位置(x坐标)

注意，允许多个城市或蜂窝塔位置相同。

## 输出格式

输出最小的r，使得每个城市都被蜂窝网络覆盖。

## 说明/提示

1<=n,m<=10^5

-10^9<=a[i]<=10^9

-10^9<=b[j]<=10^9

## 样例 #1

### 输入

```
3 2
-2 2 4
-3 0

```

### 输出

```
4

```

## 样例 #2

### 输入

```
5 3
1 5 10 14 17
4 11 15

```

### 输出

```
3

```



---

