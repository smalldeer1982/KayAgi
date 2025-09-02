---
title: "「OICon-02」maxiMINImax"
layout: "post"
diff: 提高+/省选-
pid: P10173
tag: ['线段树', 'O2优化', '笛卡尔树', '单调栈']
---
# 「OICon-02」maxiMINImax
## 题目描述

给出一个长度为 $n$ 的排列 $a$。定义一个子区间 $[l,r]$ 中 $a_i$ 的最小值为 $\min_{[l,r]}$，$a_i$ 的最大值为 $\max_{[l,r]}$。对于所有子区间三元组 $([l_1,r_1],[l_2,r_2],[l_3,r_3])$ 使得 $1\leq l_1\leq r_1<l_2\leq r_2<l_3\leq r_3\leq n$，求 $\max(0,\min_{[l_2,r_2]}-\max_{[l_1,r_1]})\times\max(0,\min_{[l_2,r_2]}-\max_{[l_3,r_3]})$ 之和，对 $9712176$ 取模。
## 输入格式

第一行，一个正整数 $n$，表示排列的长度。

第二行，$n$ 个正整数 $a$，表示给出的排列 $a$。
## 输出格式

一行，一个正整数，表示 $\max(0,\min_{[l_2,r_2]}-\max_{[l_1,r_1]})\times\max(0,\min_{[l_2,r_2]}-\max_{[l_3,r_3]})$ 之和，对 $9712176$ 取模。
## 样例

### 样例输入 #1
```
4
1 3 4 2
```
### 样例输出 #1
```
14
```
### 样例输入 #2
```
10
1 3 6 2 7 9 4 10 8 5
```
### 样例输出 #2
```
1992
```
## 提示

### 样例解释

对于样例 $1$：

* $([l_1,r_1],[l_2,r_2],[l_3,r_3])=([1,1],[2,2],[3,3])$：$\max(0,\min_{[l_2,r_2]}-\max_{[l_1,r_1]})\times\max(0,\min_{[l_2,r_2]}-\max_{[l_3,r_3]})=0$；
* $([l_1,r_1],[l_2,r_2],[l_3,r_3])=([1,1],[2,2],[3,4])$：$\max(0,\min_{[l_2,r_2]}-\max_{[l_1,r_1]})\times\max(0,\min_{[l_2,r_2]}-\max_{[l_3,r_3]})=0$；
* $([l_1,r_1],[l_2,r_2],[l_3,r_3])=([1,1],[2,2],[4,4])$：$\max(0,\min_{[l_2,r_2]}-\max_{[l_1,r_1]})\times\max(0,\min_{[l_2,r_2]}-\max_{[l_3,r_3]})=2$；
* $([l_1,r_1],[l_2,r_2],[l_3,r_3])=([1,1],[2,3],[4,4])$：$\max(0,\min_{[l_2,r_2]}-\max_{[l_1,r_1]})\times\max(0,\min_{[l_2,r_2]}-\max_{[l_3,r_3]})=2$；
* $([l_1,r_1],[l_2,r_2],[l_3,r_3])=([1,1],[3,3],[4,4])$：$\max(0,\min_{[l_2,r_2]}-\max_{[l_1,r_1]})\times\max(0,\min_{[l_2,r_2]}-\max_{[l_3,r_3]})=6$；
* $([l_1,r_1],[l_2,r_2],[l_3,r_3])=([1,2],[3,3],[4,4])$：$\max(0,\min_{[l_2,r_2]}-\max_{[l_1,r_1]})\times\max(0,\min_{[l_2,r_2]}-\max_{[l_3,r_3]})=2$；
* $([l_1,r_1],[l_2,r_2],[l_3,r_3])=([2,2],[3,3],[4,4])$：$\max(0,\min_{[l_2,r_2]}-\max_{[l_1,r_1]})\times\max(0,\min_{[l_2,r_2]}-\max_{[l_3,r_3]})=2$。

所有 $([l_1,r_1],[l_2,r_2],[l_3,r_3])$ 的 $\max(0,\min_{[l_2,r_2]}-\max_{[l_1,r_1]})\times\max(0,\min_{[l_2,r_2]}-\max_{[l_3,r_3]})$ 总和为 $0+0+2+2+6+2+2=14$。

### 数据范围

**本题采用捆绑测试。**

| $\text{Subtask}$ | 特殊性质 | $\text{Score}$ |
|:--:|:--:|:--:|
| $1$ | $n\leq60$ | $5$ |
| $2$ | $n\leq100$ | $9$ |
| $3$ | $n\leq200$ | $9$ |
| $4$ | $n\leq500$ | $9$ |
| $5$ | $n\leq2000$ | $19$ |
| $6$ | $n\leq6000$ | $11$ |
| $7$ | $n\leq10^5$ | $19$ |
| $8$ | 无特殊限制 | $19$ |

对于 $100\%$ 的数据：$1\leq n\leq10^6$，$1\leq a_i\leq n$，保证 $a$ 为 $\{1,2,\dots,n\}$ 的一个排列。


---

---
title: "「OICon-02」Great Segments"
layout: "post"
diff: 提高+/省选-
pid: P10174
tag: ['线性数据结构', 'O2优化', '树论', '单调栈']
---
# 「OICon-02」Great Segments
## 题目背景

upd：时间限制改为 400ms

[加强版题目推荐](https://www.luogu.com.cn/problem/P11291)
## 题目描述

给定一个长度为 $n$ 的无重复元素序列 $a$。

对于一个区间 $[l,r]$，我们定义它是好的，有以下条件：

1. 定义一个序列 $b=\{ a_l,\max(a_l,a_{l+1}),\max(a_l,a_{l+1},a_{l+2}),\ ...\ ,\max(a_l,a_{l+1},\ ... \ ,a_r)\}$，将该序列进行去重操作后，该序列的长度不超过 $k$ 且大于 $1$；
2. $\max(a_l,a_{l+1},\ ... \ ,a_r)=a_r$。

请你解决这样一个问题：对于每一个 $i \ (1 \le i \le n)$，有多少个好的区间 $[l,r]$ 满足 $l \le i \le r$。
## 输入格式

第一行两个整数 $n,k$。

第二行 $n$ 个整数，第 $i$ 个数表示 $a_i$。
## 输出格式

$n$ 行，每行一个整数，第 $i$ 行的数表示序列中有多少个好的区间 $[l,r]$ 满足 $l \le i \le r$。
## 样例

### 样例输入 #1
```
4 2
1 3 2 4
```
### 样例输出 #1
```
1
2
2
2
```
## 提示

### 样例解释

对于样例 $1$，满足条件的区间有：

1. $[1,2]$；
2. $[2,4]$；
3. $[3,4]$。

故当 $i=1,2,3,4$ 时，分别有以下区间满足 $l\leq i\leq r$（根据上述的区间编号）：

1. $1$ 区间；
2. $1,2$ 区间；
3. $2,3$ 区间；
4. $2,3$ 区间。

### 数据范围

**本题采用捆绑测试。**

| $\text{Subtask}$ | 特殊性质 | $\text{Score}$ |
| :----------: | :----------: | :----------: |
| $1$ | $n \le 200$ | $5$ |
| $2$ | $n\leq 2000$ | $10$ | 
| $3$ | $\{a\}$ 递增 | $10$ |
| $4$ | $k\leq 5$ | $12$ |
| $5$ | $k=n$ | $13$ |
| $6$ | $n \le 3 \times 10^5$ | $20$ |
| $7$ | 无特殊限制 | $30$ |

对于 $100\%$ 的数据：$1\leq k\leq n\leq 10^6$，$0\leq a_i\leq 10^9$。


---

---
title: "[USACO24FEB] Milk Exchange G"
layout: "post"
diff: 提高+/省选-
pid: P10194
tag: ['USACO', '2024', 'O2优化', '前缀和', '差分', '单调栈']
---
# [USACO24FEB] Milk Exchange G
## 题目描述

Farmer John 的 $N$（$1\le N \le 5\cdot 10^5$）头奶牛排成一圈。第 $i$ 头奶牛有一个容量为整数 $a_i$（$1\le a_i\le 10^9$）升的桶。所有桶初始时都是满的。

每一分钟，对于 $1\le i<N$，奶牛 $i$ 会将其桶中所有牛奶传递给奶牛 $i+1$，奶牛 $N$ 将其牛奶传递给奶牛 $1$。所有交换同时发生（即，如果一头奶牛的桶是满的，送出 $x$ 升牛奶同时收到 $x$ 升，则她的牛奶量保持不变）。如果此时一头奶牛的牛奶量超过 $a_i$，则多余的牛奶会损失。

在 $1,2,\ldots,N$ 的每一分钟后，所有奶牛总共还余下多少牛奶？ 
## 输入格式

输入的第一行包含 $N$。

第二行包含 $a_1,a_2,\ldots,a_N$。
## 输出格式

输出 $N$ 行，其中第 $i$ 行包含 $i$ 分钟后所有奶牛总共余下的牛奶量。
## 样例

### 样例输入 #1
```
6
2 2 2 1 2 1
```
### 样例输出 #1
```
8
7
6
6
6
6
```
### 样例输入 #2
```
8
3 8 6 4 8 3 8 1
```
### 样例输出 #2
```
25
20
17
14
12
10
8
8
```
### 样例输入 #3
```
10
9 9 10 10 6 8 2 1000000000 1000000000 1000000000
```
### 样例输出 #3
```
2000000053
1000000054
56
49
42
35
28
24
20
20
```
## 提示

### 样例解释 1

最初，每个桶中的牛奶量为 $[2,2,2,1,2,1]$。

- $1$ 分钟后，每个桶中的牛奶量为 $[1,2,2,1,1,1]$，因此总牛奶量为 $8$。
- $2$ 分钟后，每个桶中的牛奶量为 $[1,1,2,1,1,1]$，因此总牛奶量为 $7$。
- $3$ 分钟后，每个桶中的牛奶量为 $[1,1,1,1,1,1]$，因此总牛奶量为 $6$。
- $4$ 分钟后，每个桶中的牛奶量为 $[1,1,1,1,1,1]$，因此总牛奶量为 $6$。
- $5$ 分钟后，每个桶中的牛奶量为 $[1,1,1,1,1,1]$，因此总牛奶量为 $6$。
- $6$ 分钟后，每个桶中的牛奶量为 $[1,1,1,1,1,1]$，因此总牛奶量为 $6$。

### 样例解释 2

$1$ 分钟后，每个桶中的牛奶量为 $[1,3,6,4,4,3,3,1]$，因此总牛奶量为 $25$。

### 测试点性质

- 测试点 $4-5$：$N\le 2000$。
- 测试点 $6-8$：$a_i\le 2$。
- 测试点 $9-13$：所有 $a_i$ 在范围 $[1,10^9]$ 内均匀随机生成。
- 测试点 $14-23$：没有额外限制。


---

---
title: "「LAOI-4」石头"
layout: "post"
diff: 提高+/省选-
pid: P10371
tag: ['O2优化', '单调栈', '洛谷比赛']
---
# 「LAOI-4」石头
## 题目描述

有一个长度为 $n$ 的排列 $a$，初始可以任意染白一个数，然后接下来每一步可以染白最小的一个与已经被染白的数相邻的数，显然 $n$ 步之后所有数都会被染白。

现在我们称满足以下要求的数对 $(i,j)$ 是好的数对：

- $1\leq i\leq j\leq n$。
- 存在一个 $k$，满足若从 $a_i$ 开始染白，$a_j$ 会在第 $k$ 步被染白；若从 $a_j$ 开始染白，$a_i$ 也会在第 $k$ 步被染白。

求好的数对的数量。
## 输入格式

由于输入数据过大，现给出数据辅助生成器。

```cpp
int a[/*数组大小*/];
namespace GenHelper
{
    unsigned z1, z2, z3, z4, b;
    unsigned rand_()
    {
        b = ((z1 << 6) ^ z1) >> 13;
        z1 = ((z1 & 4294967294U) << 18) ^ b;
        b = ((z2 << 2) ^ z2) >> 27;
        z2 = ((z2 & 4294967288U) << 2) ^ b;
        b = ((z3 << 13) ^ z3) >> 21;
        z3 = ((z3 & 4294967280U) << 7) ^ b;
        b = ((z4 << 3) ^ z4) >> 12;
        z4 = ((z4 & 4294967168U) << 13) ^ b;
        return (z1 ^ z2 ^ z3 ^ z4);
    }
}
void srand_(unsigned x, int n)
{
    using namespace GenHelper;
    z1 = x;
    z2 = (~x) ^ 0x233333333U;
    z3 = x ^ 0x1234598766U;
    z4 = (~x) + 51;
    for (int i = 1; i <= n; ++i)
        a[i] = i;
    if (!x)
        return;
    for (int i = 1; i <= n; ++i)
    {
        int j = rand_() % i + 1, k;
        k = a[i], a[i] = a[j], a[j] = k;
    }
}
```

输入两个整数 $n$ 和 $s$，分别表示排列长度和随机数种子。

你需要恰好调用一次 `srand_(s,n)`，在此之后 $a_i$ 已经储存在 `a[i]` 中，注意下标从 $1$ 开始，不要忘记规定数组大小。
## 输出格式

共一行一个正整数，表示好的数对的数量。
## 样例

### 样例输入 #1
```
5 114514
```
### 样例输出 #1
```
9
```
### 样例输入 #2
```
10 113037
```
### 样例输出 #2
```
23
```
### 样例输入 #3
```
20 73555
```
### 样例输出 #3
```
49
```
## 提示

### 样例解释

对于样例组 #1，$a=\{4,3,1,5,2\}$，好的数对分别是：$(1,1),(1,3),(1,5),(2,2),(2,3),(2,4),(3,3),(4,4),(5,5)$。

### 数据范围

**「本题采用捆绑测试」**

|子任务编号|$n$|特殊性质|分值|
|:-:|:-:|:-:|:-:|
|$1$|$\le10^3$|无|$15$|
|$2$|$\le10^5$|无|$30$|
|$3$|$\le10^7$|$\text{A}$|$5$|
|$4$|$\le10^7$|无|$50$|

对于 $100\%$ 的数据，保证 $1\le n\le 10^7$，$0\leq s\leq 114514$，$a$ 为 $n$ 的排列。  

特殊性质 $\text{A}$：$a_i$ 单调递增，此时 $s=0$。  


---

---
title: "【烂题杯 Round 1】消灭劳嗝"
layout: "post"
diff: 提高+/省选-
pid: P10891
tag: ['O2优化', '容斥原理', '单调栈']
---
# 【烂题杯 Round 1】消灭劳嗝
## 题目描述

你需要消灭劳嗝。

给定一个长度为 $n$ 的排列 $A=a_1,a_2,\cdots,a_n$，定义 $S_i=\{x|x\ge i\land \max_{i\le k\le x}a_k\le a_x\}$，您可以把它理解为以 $i$ 开头的后缀的前缀最大值的下标集合。例如对于 $A=\{3,5,2,1,4\}$，$S_1=\{1,2\}$，$S_3=\{3,5\}$。

有 $q$ 次询问，每次询问给出 $l,r$，求：

$$
\left(\left(\sum_{l\le x\le y\le r} |S_x\cup S_y|-\sum_{\substack{{1\le x<l}\\{r<y\le n}}} |S_x\cup S_y|\right)\bmod P+P\right)\bmod P
$$

其中，$P=998244353$。
## 输入格式

由于输入文件过大无法上传，接下来我们将会以一种诡异的方式读入数据。

第一行输入两个非负整数 $n$、$X$。表示排列长度、随机种子。

初始令 $a_i=i$，接下来输入一行一个整数 $c$，表示对排列的操作次数。

接下来我们将会对排列 $A$ 进行 $c$ 次操作，对于下标从 $1$ 开始的第 $i$ 次操作，令 $l=(X\times (X\oplus i))\bmod n+1,r=(X\oplus(i\times i))\bmod n+1$，你需要交换 $a_l$ 与 $a_r$。$\oplus$ 表示按位异或。

对于 C++，代码实现如下：

```cpp
l = (1ll * X * (X ^ i)) % n + 1;
r = (X ^ (1ll * i * i)) % n + 1;
```

接下来输入一行一个整数 $q$，表示询问组数。

对于下标从 $1$ 开始的第 $i$ 次询问，我们令 $l=\min((X\times i+(X\oplus (X\times i)))\bmod n,(X-i+(X\oplus (X+i)))\bmod n)+1,r=\max((X\times i+(X\oplus (X\times i)))\bmod n,(X-i+(X\oplus (X+i)))\bmod n)+1$。表示询问的参数。

对于 C++，代码实现如下：

```cpp
l = min((1ll * X * i + (X ^ (1ll * X * i))) % n, (X - i + (X ^ (X + i))) % n) + 1;
r = max((1ll * X * i + (X ^ (1ll * X * i))) % n, (X - i + (X ^ (X + i))) % n) + 1;
```
## 输出格式

由于输出文件过大无法上传，接下来我们将会以一种诡异的方式输出数据。

输出一行一个整数，表示 $q$ 次询问中所有答案的异或和。
## 样例

### 样例输入 #1
```
5 3
4
5
```
### 样例输出 #1
```
998244304
```
### 样例输入 #2
```
10 114514
191981
3
```
### 样例输出 #2
```
998244191
```
## 提示

**样例 1 解释：**

操作后 $A=\{1,5,4,2,3\}$。

对询问解密后真实询问如下：

```
4 5
2 3
1 5
3 4
3 5
```

对输出解密后真实输出如下：

```
5
998244350
33
1
11
```

对于第一个询问，$S_4=\{4,5\}$，$S_5=\{5\}$，$|S_4\cup S_4|+|S_4\cup S_5|+|S_5\cup S_5|=5$。

对于倒数第二个询问，不要忘了 $1\le x<l,r<y\le n$ 的项。

**数据范围：**

对于 $20\%$ 的数据，满足 $1\le n\le 100$、$1\le q\le 100$。

对于 $40\%$ 的数据，满足 $1\le n\le 100$、$1\le q\le 10^5$。

对于 $60\%$ 的数据，满足 $1\le n\le 10^5$、$1\le q\le 10^5$。

对于 $80\%$ 的数据，满足 $1\le n\le 3\times10^6$、$1\le q\le 3\times10^6$。

对于 $100\%$ 的数据，满足 $1\le n\le 10^7$，$1\le q\le 10^7$，$0\le c\le 10^7$，$0\le X\le 10^9$，$a_i$ 互不相同。

**请各位选手注意常数因子的影响。**


---

---
title: "Range | Sum | Maximum"
layout: "post"
diff: 提高+/省选-
pid: P12498
tag: ['O2优化', '差分', '单调栈', '洛谷比赛']
---
# Range | Sum | Maximum
## 题目描述

给出一个长度为 $n$ 的序列 $a$，定义一个区间 $[l,r]$ 的权值为 $\max_{l\le L\le R\le r}|\sum_{i=L}^Ra_i|$。

对于 $k=1,2,3,\dots,n$，求所有长度为 $k$ 的区间权值和。
## 输入格式

本题有多组测试数据，第一行输入一个正整数 $T$，代表数据组数。

对于每组数据，第一行输入一个正整数 $n$。

第二行输入 $n$ 个整数，代表序列 $a$。
## 输出格式

为了避免输出量过大，设长度为 $k$ 的区间权值和为 $ans_k$，对于每组测试数据，你只需要输出：

$$\bigoplus_{i=1}^nans_i\bmod i^2$$

（其中 $\oplus$ 表示按位异或运算）

正解做法不依赖于该输出方式。
## 样例

### 样例输入 #1
```
5
3
1 -1 2
7
1 -2 -3 4 5 -6 -7
7
-1 2 3 -4 -5 6 7
4
1 1 2 3
5
1 4 -5 -2 6
```
### 样例输出 #1
```
1
31
31
4
11
```
## 提示

#### 【样例解释】

样例中五组数据的 $ans$ 分别为：
- $\{4,3,2\}$
- $\{28,39,41,36,31,22,13\}$
- $\{28,39,41,36,31,22,13\}$
- $\{7,10,10,7\}$
- $\{18,23,19,14,7\}$

其中，对于第一组数据，各个区间的权值分别如下：

- $[1,1]:1$
- $[2,2]:1$
- $[3,3]:2$
- $[1,2]:1$
- $[2,3]:2$
- $[1,3]:2$

其中，长度为 $1$ 的区间有 $[1,1],[2,2],[3,3]$，权值和为 $4$；长度为 $2$ 的区间有 $[1,2],[2,3]$，权值和为 $3$；长度为 $3$ 的区间有 $[1,3]$，权值和为 $2$。

#### 【数据范围】

对于所有数据，保证：
- $1\le T\le10^4$
- $1\le n,\sum n\le10^6$
- $-10^6\le a_i\le10^6$

**本题采用打包测试**，各测试包描述如下：

| Subtask | $\sum n\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $500$ | 无 | $5$ |
| $2$ | $5000$ | 无 | $20$ |
| $3$ | $10^6$ | $a_i\ge 0$ | $25$ |
| $4$ | $3\times10^5$ | 无 | $25$ |
| $5$ | $10^6$ | 无 | $25$ |



---

---
title: "[GCJ 2019 #1B] Fair Fight"
layout: "post"
diff: 提高+/省选-
pid: P13111
tag: ['2019', '单调栈', 'Google Code Jam']
---
# [GCJ 2019 #1B] Fair Fight
## 题目描述

En garde! Charles and Delila are about to face off against each other in the final fight of the Swordmaster fencing tournament.

Along one wall of the fencing arena, there is a rack with $\mathbf{N}$ different types of swords; the swords are numbered by type, from 1 to $\mathbf{N}$. As the head judge, you will pick a pair of integers $(L, R)$ (with $1 \leqslant \mathbf{L} \leqslant \mathbf{R} \leqslant \mathbf{N}$), and only the L-th through R-th types of swords (inclusive) will be available for the fight.

Different types of sword are used in different ways, and being good with one type of sword does not necessarily mean you are good with another! Charles and Delila have skill levels of $\mathbf{C}_i$ and $\mathbf{D}_i$, respectively, with the i-th type of sword. Each of them will look at the types of sword you have made available for this fight, and then each will choose a type with which they are most skilled. If there are multiple available types with which a fighter is equally skilled, and that skill level exceeds the fighter's skill level in all other available types, then the fighter will make one of those equally good choices at random. Notice that it is possible for Charles and Delila to choose the same type of sword, which is fine — there are multiple copies of each type of sword available.

The fight is *fair* if the absolute difference between Charles's skill level with his chosen sword type and Delila's skill level with her chosen sword type is at most $\mathbf{K}$. To keep the fight exciting, you'd like to know how many different pairs $(L, R)$ you can choose that will result in a fair fight.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each case begins with a line containing the two integers $\mathbf{N}$ and $\mathbf{K}$, as described above. Then, two more lines follow. The first of these lines contains $\mathbf{N}$ integers $\mathbf{C}_i$, giving Charles's skill levels for each type of sword, as described above. Similarly, the second line contains $\mathbf{N}$ integers $\mathbf{D}_i$, giving Delila's skill levels.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the number of choices you can make that result in a fair fight, as described above.
## 样例

### 样例输入 #1
```
6
4 0
1 1 1 8
8 8 8 8
3 0
0 1 1
1 1 0
1 0
3
3
5 0
0 8 0 8 0
4 0 4 0 4
3 0
1 0 0
0 1 2
5 2
1 2 3 4 5
5 5 5 5 10
```
### 样例输出 #1
```
Case #1: 4
Case #2: 4
Case #3: 1
Case #4: 0
Case #5: 1
Case #6: 7
```
## 提示

**Sample Explanation**

- In Sample Case #1, the fight is fair if and only if Charles can use the last type of sword, so the answer is $4$.
- In Sample Case #2, there are $4$ fair fights: $(1, 2)$, $(1, 3)$, $(2, 2)$, and $(2, 3)$. Notice that for pairs like $(1, 3)$, Charles and Delila both have multiple swords they could choose that they are most skilled with; however, each pair only counts as one fair fight.
- In Sample Case #3, there is $1$ fair fight: $(1, 1)$.
- In Sample Case #4, there are no fair fights, so the answer is $0$.
- In Sample Case #5, remember that the *duelists* are not trying to make the fights fair; they choose the type of sword that they are most skilled with. For example, $(1, 3)$ is not a fair fight, because Charles will choose the first type of sword, and Delila will choose the third type of sword. Delila will not go easy on Charles by choosing a weaker sword!
- In Sample Case #6, there are $7$ fair fights: $(1, 3)$, $(1, 4)$, $(2, 3)$, $(2, 4)$, $(3, 3)$, $(3, 4)$, and $(4, 4)$.

**Limits**

- $1 \leqslant \mathbf{T} \leqslant 100$.
- $0 \leqslant \mathbf{K} \leqslant 10^5$.
- $0 \leqslant \mathbf{C}_i \leqslant 10^5$, for all $i$.
- $0 \leqslant \mathbf{D}_i \leqslant 10^5$, for all $i$.

**Test set 1 (14 Pts, Visible)**

- $1 \leqslant \mathbf{N} \leqslant 100$.

**Test set 2 (28 Pts, Hidden)**

- $\mathbf{N} = 10^5$, for exactly 8 test cases.
- $1 \leqslant \mathbf{N} \leqslant 1000$, for all but 8 test cases.


---

---
title: "[GCJ 2019 #3] Pancake Pyramid"
layout: "post"
diff: 提高+/省选-
pid: P13120
tag: ['2019', '单调栈', 'Google Code Jam']
---
# [GCJ 2019 #3] Pancake Pyramid
## 题目描述

You have just finished cooking for some diners at the Infinite House of Pancakes. There are $\mathbf{S}$ stacks of pancakes in all, and you have arranged them in a line, such that the i-th stack from the left (counting starting from 1) has $\mathbf{P}_\mathbf{i}$ pancakes.

Your supervisor was about to bring out the stacks to the customers, but then it occurred to her that a picture of the stacks might make for a good advertisement. However, she is worried that there might be too many stacks, so she intends to remove the $\mathbf{L}$ leftmost stacks and the $\mathbf{R}$ rightmost stacks, where $\mathbf{L}$ and $\mathbf{R}$ are nonnegative integers such that $\mathbf{L} + \mathbf{R} \leq \mathbf{S} - 3$. (Notice that at least 3 stacks of pancakes will remain after the removal.)

Your supervisor also thinks the remaining stacks will look aesthetically pleasing if they have the pyramid property. A sequence of $\mathbf{N}$ stacks of heights $\mathbf{H}_1, \mathbf{H}_2, \ldots, \mathbf{H}_\mathbf{N}$ has the pyramid property if there exists an integer $\mathbf{j}$ ($1 \leq \mathbf{j} \leq \mathbf{N}$) such that $\mathbf{H}_1 \leq \mathbf{H}_2 \leq \ldots \leq \mathbf{H}_{\mathbf{j}-1} \leq \mathbf{H}_\mathbf{j}$ and $\mathbf{H}_\mathbf{j} \geq \mathbf{H}_{\mathbf{j}+1} \geq \ldots \geq \mathbf{H}_{\mathbf{N}-1} \geq \mathbf{H}_\mathbf{N}$. (It is possible that this sequence might not look much like a typical "pyramid" — a group of stacks of the same size has the pyramid property, and so does a group in which the stack heights are nondecreasing from left to right, among other examples.)

Note that the sequence of stacks remaining after your supervisor removes the $\mathbf{L}$ leftmost and $\mathbf{R}$ rightmost stacks might not yet have the pyramid property... but you can fix that by adding pancakes to one or more of the stacks! The pyramidification cost of a sequence of stacks is the minimum total number of pancakes that must be added to stacks to give the sequence the pyramid property.

While your manager is carefully deciding which values of $\mathbf{L}$ and $\mathbf{R}$ to choose, you have started to wonder what the sum of the pyramidification costs over all valid choices of $\mathbf{L}$ and $\mathbf{R}$ is. Compute this sum, modulo the prime $10^9+7$ ($1000000007$).

## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each begins with one line containing one integer $\mathbf{S}$: the number of stacks of pancakes. Then, there is one more line containing $\mathbf{S}$ integers $\mathbf{P}_1, \mathbf{P}_2, \ldots, \mathbf{P}_\mathbf{S}$. The i-th of these is the number of pancakes in the i-th stack from the left.

## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the sum of the pyramidification costs over all valid choices of $\mathbf{L}$ and $\mathbf{R}$, modulo the prime $10^9+7$ ($1000000007$).
## 样例

### 样例输入 #1
```
3
3
2 1 2
5
1 6 2 5 7
4
1000000000 1 1 1000000000
```
### 样例输出 #1
```
Case #1: 1
Case #2: 16
Case #3: 999999991
```
## 提示

**Sample Explanation**

In Sample Case #1, your supervisor must choose $\mathbf{L} = 0$ and $\mathbf{R} = 0$, so that is the only scenario you need to consider. The optimal strategy for that scenario is to add a single pancake to the middle stack. Although the resulting sequence of stacks looks flat, notice that it has the pyramid property; in fact, any index will work as the $\mathbf{j}$ value.

In Sample Case #2, here are all possible choices of $\mathbf{L}$ and $\mathbf{R}$, the corresponding remaining stacks, and what you should do in each scenario.

* $\mathbf{L} = 0$, $\mathbf{R} = 0$: $\mathbf{H} = [1 \ 6 \ 2 \ 5 \ 7]$. The optimal solution is to add four pancakes to the third stack and one pancake to the fourth stack. Then we have $[1 \ 6 \ 6 \ 6 \ 7]$, which has the pyramid property with $\mathbf{j} = 5$.
* $\mathbf{L} = 0$, $\mathbf{R} = 1$: $\mathbf{H} = [1 \ 6 \ 2 \ 5]$. The optimal solution is to add three pancakes to the third stack. Then we have $[1 \ 6 \ 5 \ 5]$, which has the pyramid property with $\mathbf{j} = 2$.
* $\mathbf{L} = 0$, $\mathbf{R} = 2$: $\mathbf{H} = [1 \ 6 \ 2]$. This already has the pyramid property with $\mathbf{j} = 2$.
* $\mathbf{L} = 1$, $\mathbf{R} = 0$: $\mathbf{H} = [6 \ 2 \ 5 \ 7]$. The optimal solution is to add four pancakes to the second stack and one pancake to the third stack. Then we have $[6 \ 6 \ 6 \ 7]$, which has the pyramid property with $\mathbf{j} = 4$.
* $\mathbf{L} = 1$, $\mathbf{R} = 1$: $\mathbf{H} = [6 \ 2 \ 5]$. The optimal solution is to add three pancakes to the second stack. Then we have $[6 \ 5 \ 5]$, which has the pyramid property with $\mathbf{j} = 1$.
* $\mathbf{L} = 2$, $\mathbf{R} = 0$: $\mathbf{H} = [2 \ 5 \ 7]$. This already has the pyramid property with $\mathbf{j} = 3$.

So the answer is $(5 + 3 + 0 + 5 + 3 + 0)$ modulo $(10^9 + 7)$, which is $16$.

In Sample Case #3, we only need to add extra pancakes to create the pyramid property when $\mathbf{L} = 0$ and $\mathbf{R} = 0$. In that case, it is optimal to add $999999999$ pancakes to each of the second and third stacks. (We hope the diners are hungry!) So the answer is $(999999999 + 999999999)$ modulo $(10^9 + 7) = 999999991$.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $1 \leq \mathbf{P}_\mathbf{i} \leq 10^9$, for all $\mathbf{i}$.

**Test set 1 (5 Pts, Visible)**

- $\mathbf{S} = 3000$, for up to 20 test cases.
- $3 \leq \mathbf{S} \leq 500$, for all remaining cases.

**Test set 2 (17 Pts, Hidden)**

- $\mathbf{S} = 10^6$, for up to 1 test case.
- $\mathbf{S} = 10^5$, for up to 3 test cases.
- $3 \leq \mathbf{S} \leq 10000$, for all remaining cases.


---

---
title: "蓬莱「凯风快晴　−富士火山−」"
layout: "post"
diff: 提高+/省选-
pid: P9210
tag: ['树形 DP', '传智杯', '单调栈']
---
# 蓬莱「凯风快晴　−富士火山−」
## 题目背景

富士山，被当地人称为「神山」。这是一座休眠火山，最近一次喷发在 $300$ 年前。

向这样的山中投入不死之药，想必会直接喷发吧。如此便理解为什么月岩笠最终抗命。
## 题目描述

所谓的山，是一种上细下粗的结构。能不能在「树」里也找到这样的结构呢？

给定一个以 $1$ 为根的大小为 $n$ 的有根树 $T$。你需要找到满足宽度单调不减的**导出子树**中最大的一棵：

- 记该导出子树为 $T_0$，共有 $k$ 层。
- 记 $T_0$ 的根节点的深度为 $1$，计算出 $T_0$ 中每个结点的深度 $d_i$。由此定义 $T_0$ 第 $i$ 层的宽度 $w_i$ 为「所有深度为 $i$ 的节点的个数」。
- 你需要使得 $w_i$ 单调不减。即，$w_1\le w_2\le \cdots \le w_k$。

记原树的点集和边集分别为 $V,E$。导出子树是原树的一个**连通块**，它的点集 $V_0\subseteq V$，边集 $E_0$ 是 $E$ 当中所有端点均在 $V_0$ 内的边。导出子树的根，是组成它的所有节点中**在原树内深度最浅的那一个**。$T$ 也可以被认为是自身的一棵导出子树。

![](https://cdn.luogu.com.cn/upload/image_hosting/wcbeo1a0.png)

如图所示，绿色的区域和橙色的区域分别是原树的导出子树。它们的根分别为 $2$ 和 $13$。

**注意**：导出子树的定义略微不同于子树的定义。请不要将两者混淆。

请找到最大的符合条件的导出子树的大小。
## 输入格式

第一行一个正整数 $n$，表示整棵树的大小。

接下来 $n-1$ 行，每行两个整数 $u,v$，描述树上的一条边。
## 输出格式

输出共一行一个整数，表示最大的符合条件的导出子树的大小。
## 样例

### 样例输入 #1
```
10
1 2
2 3
3 4
3 5
2 6
6 7
1 8
8 9
8 10
```
### 样例输出 #1
```
9
```
### 样例输入 #2
```
17
1 2
2 3
3 4
4 5
4 6
3 7
7 8
7 9
7 10
2 11
2 12
1 13
13 14
14 15
14 16
13 17
```
### 样例输出 #2
```
16
```
## 提示

### 样例解释

![](https://cdn.luogu.com.cn/upload/image_hosting/pzq47a3e.png)

如图所示，标灰的节点是两个样例中选出来的导出子树。

- 样例 $1$ 找到的导出子树，每一层的宽度分别为 $\{1,2,3,3\}$。
- 样例 $2$ 找到的导出子树，每一层的宽度分别为 $\{1,2,4,4,5\}$。
### 数据范围及约定

对于全部数据，$1\le n\le 5\times 10^5$。


---

---
title: "「EZEC-14」众数 II"
layout: "post"
diff: 提高+/省选-
pid: P9461
tag: ['洛谷原创', 'O2优化', '洛谷月赛', '链表', '单调栈']
---
# 「EZEC-14」众数 II
## 题目背景

dXqwq 是一个不可爱的男孩子。他在 NOI2022 中的众数一题定义了 $10^6$ 个 ``std::deque`` 并成功 MLE。
## 题目描述

给定一个长度为 $n$ 的序列 $a$，我们通过以下方式构造序列 $b$：

- 初始时 $b$ 为空序列。
- 对于 $i=1,2,\cdots,n$，我们依次向 $b$ 的尾部插入 $1,2,\cdots,a_i$。

dXqwq 定义一个序列的**最小众数**为所有出现次数最大的数的最小值。例如 $[1,1,4,5,1,4]$ 的最小众数为 $1$，而 $[1,14,5,14,19,19,8,10]$ 的最小众数为 $14$。

你需要求出 $b$ 的每个子区间的**最小众数**的和。由于答案可能很大，你只需要输出它对 $998244353$ 取模后的值。
## 输入格式

第一行输入一个整数 $n$。

第二行输入 $n$ 个整数 $a_i$。
## 输出格式

输出一个整数，代表 $b$ 的每个子区间的最小众数的和对 $998244353$ 取模的值。
## 样例

### 样例输入 #1
```
3
1 2 3
```
### 样例输出 #1
```
28
```
### 样例输入 #2
```
9
9 9 8 2 4 4 3 5 3
```
### 样例输出 #2
```
1912

```
## 提示

**【样例解释】**

在第一个样例中，$b=[1,1,2,1,2,3]$。

有 $15$ 个区间的最小众数为 $1$，$5$ 个区间的最小众数为 $2$，$1$ 个区间的最小众数为 $3$，因此答案为 $15\times 1+5\times 2+1\times 3=28$。

**【提示】**

开 $10^6$ 个 ``std::deque`` 在空间限制为 512MB 时一定会 MLE。

**【数据范围】**

**本题采用捆绑测试。**

- Subtask 1（10 pts）：$\sum a_i\leq 100$。
- Subtask 2（20 pts）：$\sum a_i\leq 10^3$。 
- Subtask 3（20 pts）：$\sum a_i\leq 10^6$。
- Subtask 4（10 pts）：$n\leq 2$。
- Subtask 5（20 pts）：$n\leq 10^3$。
- Subtask 6（10 pts）：$a_i\leq 2$。
- Subtask 7（10 pts）：无特殊限制。 

对于 $100\%$ 的数据，$1\leq n\leq 10^6$，$1\leq a_i\leq 10^6$。


---

