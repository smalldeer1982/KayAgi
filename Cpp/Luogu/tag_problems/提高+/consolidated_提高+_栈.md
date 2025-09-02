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
title: "地震逃生"
layout: "post"
diff: 提高+/省选-
pid: P1343
tag: ['搜索', '图论', '福建省历届夏令营', '栈']
---
# 地震逃生
## 题目描述

汶川地震发生时，四川\*\*中学正在上课，一看地震发生，老师们立刻带领 $x$ 名学生逃跑，整个学校可以抽象地看成一个有向图，图中有 $n$ 个点，$m$ 条边。$1$ 号点为教室，$n$ 号点为安全地带，每条边都只能容纳一定量的学生，超过楼就要倒塌，由于人数太多，校长决定让同学们分成几批逃生，只有第一批学生全部逃生完毕后，第二批学生才能从 $1$ 号点出发逃生，现在请你帮校长算算，每批最多能运出多少个学生，$x$ 名学生分几批才能运完。
## 输入格式

第一行三个整数 $n,m,x$；  
以下 $m$ 行，每行三个整数 $a,b,c$（$1\leq a,b\leq n$，$0\leq c\leq x$）描述一条边，分别代表从 $a$ 点到 $b$ 点有一条边，且可容纳 $c$ 名学生。
## 输出格式

两个整数，分别表示每批最多能运出多少个学生，$x$ 名学生分几批才能运完。如果无法到达目的地（$n$ 号点）则输出 `Orz Ni Jinan Saint Cow!`。
## 样例

### 样例输入 #1
```
6 7 7
1 2 1
1 4 2
2 3 1
4 5 1
4 3 1
3 6 2
5 6 1

```
### 样例输出 #1
```
3 3

```
## 提示

**【注释】**

比如有图

```plain
1 2 100
2 3 1
```

$100$ 个学生先冲到 $2$ 号点，然后一个一个慢慢沿 $2 \to 3$ 边走过去。

18 神牛规定这样是不可以的……

也就是说，每批学生必须同时从起点出发，并且同时到达终点。

**【数据范围】**

对于 $100 \%$ 的数据，$0 \le x < 2^{31}$，$1 \le n \le 200$，$1 \le m \le 2000$。


---

---
title: "[HNOI2004] 宠物收养场"
layout: "post"
diff: 提高+/省选-
pid: P2286
tag: ['2004', '各省省选', '平衡树', '湖南', '栈']
---
# [HNOI2004] 宠物收养场
## 题目背景

题面修缮来自于 [LaDeX](https://www.luogu.com.cn/user/431658)。
## 题目描述

凡凡开了一间宠物收养场。收养场提供两种服务：收养被主人遗弃的宠物和让新的主人领养这些宠物。

每个领养者都希望领养到自己满意的宠物，凡凡根据领养者的要求通过他自己发明的一个特殊的公式，得出该领养者希望领养的宠物的特点值 $a$（$a$ 是一个正整数，$a<2^{31}$），而他也给每个处在收养场的宠物一个特点值。这样他就能够很方便的处理整个领养宠物的过程了，宠物收养场总是会有两种情况发生：被遗弃的宠物过多或者是想要收养宠物的人太多，而宠物太少。

被遗弃的宠物过多时，假若到来一个领养者，这个领养者希望领养的宠物的特点值为 $a$，那么它将会领养一只目前未被领养的宠物中特点值最接近 $a$ 的一只宠物。（任何两只宠物的特点值都不可能是相同的，任何两个领养者的希望领养宠物的特点值也不可能是一样的）如果有两只满足要求的宠物，即存在两只宠物他们的特点值分别为 $a-b$ 和 $a+b$，那么领养者将会领养特点值为 $a-b$ 的那只宠物。

收养宠物的人过多，假若到来一只被收养的宠物，那么哪个领养者能够领养它呢？能够领养它的领养者，是那个希望被领养宠物的特点值最接近该宠物特点值的领养者，如果该宠物的特点值为 $a$，存在两个领养者他们希望领养宠物的特点值分别为 $a-b$ 和 $a+b$，那么特点值为 $a-b$ 的那个领养者将成功领养该宠物。

一个领养者领养了一个特点值为 $a$ 的宠物，而它本身希望领养的宠物的特点值为 $b$，那么这个领养者的不满意程度为 $|a-b|$。

你得到了一年当中，领养者和被收养宠物到来收养所的情况，请你计算所有收养了宠物的领养者的不满意程度的总和。这一年初始时，收养所里面既没有宠物，也没有领养者。
## 输入格式

第一行为一个正整数 $n$，$n\leq80000$，表示一年当中来到收养场的宠物和领养者的总数。接下来的 $n$ 行，按到来时间的先后顺序描述了一年当中来到收养场的宠物和领养者的情况。每行有两个正整数 $a,b$，其中 $a=0$ 表示宠物，$a=1$ 表示领养者，$b$ 表示宠物的特点值或是领养者希望领养宠物的特点值。（同一时间呆在收养所中的，要么全是宠物，要么全是领养者，这些宠物和领养者的个数不会超过 $10000$ 个）

## 输出格式

仅有一个正整数，表示一年当中所有收养了宠物的领养者的不满意程度的总和对 $1000000$ 取模以后的结果。

## 样例

### 样例输入 #1
```
5                  

0 2                      

0 4                         

1 3

1 2

1 5


```
### 样例输出 #1
```
3

```
## 提示

样例解释：

注：$|3-2| + |2-4|=3$，
最后一个领养者没有宠物可以领养。


---

---
title: "[SCOI2005] 王室联邦"
layout: "post"
diff: 提高+/省选-
pid: P2325
tag: ['搜索', '2005', '四川', '各省省选', 'Special Judge', '深度优先搜索 DFS', '栈']
---
# [SCOI2005] 王室联邦
## 题目描述

“余”人国的国王想重新编制他的国家。他想把他的国家划分成若干个省，每个省都由他们王室联邦的一个成员来管理。

他的国家有 $N$ 个城市，编号为 $1\ldots N$。

一些城市之间有道路相连，任意两个不同的城市之间有且仅有一条直接或间接的道路。

为了防止管理太过分散，每个省至少要有 $B$ 个城市。

为了能有效的管理，每个省最多只有 $3\times B$ 个城市。

每个省必须有一个省会，这个省会可以位于省内，也可以在该省外。

但是该省的任意一个城市到达省会所经过的道路上的城市（除了最后一个城市，即该省省会）都必须属于该省。

一个城市可以作为多个省的省会。

聪明的你快帮帮这个国王吧！
## 输入格式

第一行包含两个数 $N,B$。

接下来 $N－1$ 行，每行描述一条边，包含两个数，即这条边连接的两个城市的编号。
## 输出格式

如果无法满足国王的要求，输出 $0$。

否则第一行输出数 $K$，表示你给出的划分方案中省的个数。

第二行输出 $N$ 个数，第 $I$ 个数表示编号为 $I$ 的城市属于的省的编号。要求城市编号在 $[1,K]$ 范围内。

第三行输出 $K$ 个数，表示这 $K$ 个省的省会的城市编号。

如果有多种方案，你可以输出任意一种。
## 样例

### 样例输入 #1
```
8 2 
1 2 
2 3 
1 8 
8 7 
8 6 
4 6 
6 5 

```
### 样例输出 #1
```
3 
2 1 1 3 3 3 3 2 
2 1 8 

```
## 提示

对于 $100\%$ 的数据，$1\le B\leq N\le 10^3$。

感谢 @[FlierKing](/user/9433) 提供 spj。


---

---
title: "yyy loves Maths VII"
layout: "post"
diff: 提高+/省选-
pid: P2396
tag: ['剪枝', '栈', '状压 DP']
---
# yyy loves Maths VII
## 题目背景

yyy 对某些数字有着情有独钟的喜爱，他叫他们为“幸运数字”；然而他作死太多，所以把自己讨厌的数字称为“厄运数字”。
## 题目描述

一群同学在和 yyy 玩一个游戏。

每次,他们会给 yyy $n$ 张卡片，卡片上有数字，所有的数字都是“幸运数字”，我们认为第 $i$ 张卡片上数字是 $a_{i}$。

每次 yyy 可以选择向前走 $a_{i}$ 步并且丢掉第 $i$ 张卡片。当他手上没有卡片的时候他就赢了。

但是呢，大家对“厄运数字”的位置布置下了陷阱，如果 yyy 停在这个格子上，那么他就输了。注意：**即使到了终点，但是这个位置是厄运数字，那么也输了。**

现在，有些同学开始问：yyy 有多大的概率会赢呢？

大家觉得这是个好问题，有人立即让 yyy 写个程序：“电脑运行速度很快！$24$ 的阶乘也不过就 $620\,448\,401\,733\,239\,439\,360\,000$，yyy 你快写个程序来算一算。”

yyy 表示很无语，他表示他不想算概率，最多算算赢的方案数，而且是对 $10^9+7$ 取模后的值。

大家都不会写程序，只好妥协。

但是这时候 yyy 为难了，$24!$ 太大了，要跑好长时间。

他时间严重不够！需要你的帮助！

某个数字可能既属于幸运数字又属于厄运数字。
## 输入格式

第一行一个整数 $n$。 

下面一行 $n$ 个整数，第 $i$ 个整数代表第 $i$ 张卡片上的数字 $a_i$。

第三行 $m$ 表示 yyy 的厄运数字个数（最多 $2$ 个）。

若 $m>0$，第四行 $m$ 个数 $b_i$ 代表所有的厄运数字。
## 输出格式

输出胜利方案数对 $10^9+7$ 取模的结果。
## 样例

### 样例输入 #1
```
8
1 3 1 5 2 2 2 3
0
```
### 样例输出 #1
```
40320
```
### 样例输入 #2
```
24
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
2
10 15

```
### 样例输出 #2
```
0
```
## 提示

- $10\%$ 的数据 $n \leq 10$；
- $50\%$ 的数据 $n \leq 23$；
- $100\%$ 的数据 $n \leq 24$，$0\le m\le 2$，$1\le a_i,b_i\le 10^9$。


---

---
title: "[USACO08FEB] Hotel G"
layout: "post"
diff: 提高+/省选-
pid: P2894
tag: ['2008', '线段树', 'USACO', '栈']
---
# [USACO08FEB] Hotel G
## 题目描述

The cows are journeying north to Thunder Bay in Canada to gain cultural enrichment and enjoy a vacation on the sunny shores of Lake Superior. Bessie, ever the competent travel agent, has named the Bullmoose Hotel on famed Cumberland Street as their vacation residence. This immense hotel has N (1 ≤ N ≤ 50,000) rooms all located on the same side of an extremely long hallway (all the better to see the lake, of course).

The cows and other visitors arrive in groups of size Di (1 ≤ Di ≤ N) and approach the front desk to check in. Each group i requests a set of Di contiguous rooms from Canmuu, the moose staffing the counter. He assigns them some set of consecutive room numbers r..r+Di-1 if they are available or, if no contiguous set of rooms is available, politely suggests alternate lodging. Canmuu always chooses the value of r to be the smallest possible.

Visitors also depart the hotel from groups of contiguous rooms. Checkout i has the parameters Xi and Di which specify the vacating of rooms Xi ..Xi +Di-1 (1 ≤ Xi ≤ N-Di+1). Some (or all) of those rooms might be empty before the checkout.

Your job is to assist Canmuu by processing M (1 ≤ M < 50,000) checkin/checkout requests. The hotel is initially unoccupied.

第一行输入 $n,m$，$n$ 代表有 $n$ 个房间 $(1\leq n \leq 50,000)$，编号为 $1 \sim n$，开始都为空房，$m$ 表示以下有 $m$ 行操作 $(1\leq m < 50,000)$，以下每行先输入一个数 $i$ ，表示一种操作：

若 $i$ 为 $1$，表示查询房间，再输入一个数 $x$，表示在 $1,2,...,n$ 房间中找到长度为 $x$ 的连续空房，输出连续 $x$ 个房间中左端的房间号，尽量让这个房间号最小，若找不到长度为 $x$ 的连续空房，输出 $0$。若找得到，在这 $x$ 个空房间中住上人。

若 $i$ 为 $2$，表示退房，再输入两个数 $x,y$ 代表房间号 $x \sim x+y-1$ 退房，即让房间为空。

你需要对每个输入 $1$ 输出对应的答案。
## 输入格式

\* Line 1: Two space-separated integers: N and M

\* Lines 2..M+1: Line i+1 contains request expressed as one of two possible formats: (a) Two space separated integers representing a check-in request: 1 and Di (b) Three space-separated integers representing a check-out: 2, Xi, and Di

## 输出格式

\* Lines 1.....: For each check-in request, output a single line with a single integer r, the first room in the contiguous sequence of rooms to be occupied. If the request cannot be satisfied, output 0.

## 样例

### 样例输入 #1
```
10 6
1 3
1 3
1 3
1 3
2 5 5
1 6

```
### 样例输出 #1
```
1
4
7
0
5

```


---

---
title: "[USACO08JAN] Artificial Lake G"
layout: "post"
diff: 提高+/省选-
pid: P2897
tag: ['2008', 'USACO', '栈']
---
# [USACO08JAN] Artificial Lake G
## 题目背景

USACO 2008 January Gold
## 题目描述

The oppressively hot summer days have raised the cows' clamoring to its highest level. Farmer John has finally decided to build an artificial lake. For his engineering studies, he is modeling the lake as a two-dimensional landscape consisting of a contiguous sequence of N soon-to-be-submerged levels (1 ≤ N ≤ 100,000) conveniently numbered 1..N from left to right.


Each level i is described by two integers, its width Wi (1 ≤ Wi ≤ 1,000) and height (like a relative elevation) Hi (1 ≤ Hi ≤ 1,000,000). The heights of FJ's levels are unique. An infinitely tall barrier encloses the lake's model on the left and right. One example lake profile is shown below.

          
```cpp
         *             *  :
         *             *  :
         *             *  8
         *    ***      *  7
         *    ***      *  6
         *    ***      *  5
         *    **********  4 <- height
         *    **********  3
         ***************  2
         ***************  1
Level    |  1 |2|  3   |
```
In FJ's model, he starts filling his lake at sunrise by flowing water into the bottom of the lowest elevation at a rate of 1 square unit of water per minute. The water falls directly downward until it hits something, and then it flows and spreads as room-temperature water always does. As in all good models, assume that falling and flowing happen instantly. Determine the time at which each elevation's becomes submerged by a single unit of water.


```cpp
WATER              WATER OVERFLOWS                     
       |                       |                           
     * |          *      *     |      *      *            *
     * V          *      *     V      *      *            *
     *            *      *    ....    *      *~~~~~~~~~~~~*
     *    **      *      *~~~~** :    *      *~~~~**~~~~~~*
     *    **      *      *~~~~** :    *      *~~~~**~~~~~~*
     *    **      *      *~~~~**~~~~~~*      *~~~~**~~~~~~*
     *    *********      *~~~~*********      *~~~~*********
     *~~~~*********      *~~~~*********      *~~~~*********
     **************      **************      **************
     **************      **************      **************
     After 4 mins        After 26 mins       After 50 mins

     Lvl 1 submerged     Lvl 3 submerged     Lvl 2 submerged
```
Warning: The answer will not always fit in 32 bits.

夏日那让人喘不过气的酷热将奶牛们的烦躁情绪推到了最高点。最终，FJ决定建一个人工湖供奶牛消暑之用。为了使湖看起来更加真实，FJ决定将湖的横截面建成N(1 <= N <= 100,000)个连续的平台高低错落的组合状，所有的平台从左到右按1..N依次编号。当然咯，在湖中注入水后，这些平台都将被淹没。    平台i在设计图上用它的宽度W\_i(1 <= W\_i <= 1,000)和高度（你可以理解为该平台顶离FJ挖的地基的高度）H\_i(1 <= H\_i <= 1,000,000)来描述的。所有平台的高度都是独一无二的。湖的边缘可以视为无限高的平台。下面给出了一张FJ的设计图：


按FJ的设想，在坑挖好后，他会以1单位/分钟的速度往最低的那个平台上注水。水在离开水管后立即下落，直到撞到平台顶或是更早些时候注入的水。然后，与所有常温下的水一样，它会迅速地流动、扩散。简单起见，你可以认为这些都是在瞬间完成的。FJ想知道，对于每一个平台，它的顶部是从哪个时刻开始，与水面的距离至少为1单位长度。

## 输入格式

\* Line 1: A single integer: N

\* Lines 2..N+1: Line i+1 describes level i with two space-separated integers: Wi and Hi

## 输出格式


Lines 1..N: Line i contains a single integer that is the number of minutes that since sunrise when level #i is covered by water of height 1.
## 样例

### 样例输入 #1
```
3
4 2
2 7
6 4
```
### 样例输出 #1
```
4
50
26
```


---

---
title: "[HNOI2008] 水平可见直线"
layout: "post"
diff: 提高+/省选-
pid: P3194
tag: ['计算几何', '2008', '湖南', '栈', '凸包']
---
# [HNOI2008] 水平可见直线
## 题目描述

在 $x-y$ 直角坐标平面上有 $n$ 条直线 $L_1,L_2,…L_n$，若在 $y$ 值为正无穷大处往下看，能见到 $L_i$ 的某个子线段，则称 $L_i$ 为可见的，否则 $L_i$ 为被覆盖的。
例如，对于直线:
$L_1:y=x$;
$L_2:y=-x$;
$L_3:y=0$;
则 $L_1$ 和 $L_2$ 是可见的，$L_3$ 是被覆盖的。给出 $n$ 条直线，表示成 $y=Ax+B$ 的形式($|A|,|B| \le 500000$)，且 $n$ 条直线两两不重合，求出所有可见的直线。
## 输入格式

第一行为 $N$ ($0<N<50000$)，接下来的 $N$ 行输入 $A_i,B_i$
## 输出格式

从小到大输出可见直线的编号，两两中间用空格隔开，最后一个数字后面也必须有个空格。
## 样例

### 样例输入 #1
```
3
-1 0
1 0
0 0
```
### 样例输出 #1
```
1 2
```


---

---
title: "[JLOI2013] 删除物品"
layout: "post"
diff: 提高+/省选-
pid: P3253
tag: ['模拟', '2013', '树状数组', '吉林', '栈']
---
# [JLOI2013] 删除物品
## 题目描述

箱子再分配问题需要解决如下问题：

1. 一共有 $N$ 个物品，堆成 $M$ 堆。

2. 所有物品都是一样的，但是它们有不同的优先级。

3. 你只能够移动某堆中位于顶端的物品。

4. 你可以把任意一堆中位于顶端的物品移动到其它某堆的顶端。若此物品是当前所有物品中优先级最高的，可以直接将之删除而不用移动。

5. 求出将所有物品删除所需的最小步数。删除操作不计入步数之中。

6. 这是一个比较难解决的问题，这里你只需要解决一个比较简单的版本：不会有两个物品有着相同的优先级，且 $M=2$。

## 输入格式

第一行是包含两个整数 $N_1$, $N_2$ 分别表示两堆物品的个数。接下来有 $N_1$ 行整数按照从顶到底的顺序分别给出了第一堆物品中的优先级，数字越大，优先级越高。再接下来的 $N_2$ 行按照同样的格式给出了第二堆物品的优先级。

## 输出格式

对于每个数据，请输出一个整数，即最小移动步数。

## 样例

### 样例输入 #1
```
3 3
1
4
5
2
7
3
```
### 样例输出 #1
```
6
```
## 提示

$1\leq N_1+N_2\leq 100000$



---

---
title: "[POI 2007] MEG-Megalopolis"
layout: "post"
diff: 提高+/省选-
pid: P3459
tag: ['2007', '线段树', '树状数组', 'POI（波兰）', '深度优先搜索 DFS', '栈']
---
# [POI 2007] MEG-Megalopolis
## 题目描述

Byteotia has been eventually touched by globalisation, and so has Byteasar the Postman, who once roamedthe country lanes amidst sleepy hamlets and who now dashes down the motorways. But it is those strolls inthe days of yore that he reminisces about with a touch of tenderness.

In the olden days $n$ Byteotian villages (numbered from $1$ to $n$) were connected by bidirectional dirt roadsin such a way, that one could reach the village number $1$ (called Bitburg) from any other village in exactlyone way. This unique route passed only through villages with number less or equal to that of the startingvillage. Furthermore, each road connected exactly two distinct villages without passing through any othervillage. The roads did not intersect outside the villages, but tunnels and viaducts were not unheard of.

Time passing by, successive roads were being transformed into motorways. Byteasar remembers distinctly,  when each of the country roads so disappeared. Nowadays, there is not a single country lane left  in Byteotia - all of them have been replaced with motorways, which connect the villages into Byteotian  Megalopolis.

Byteasar recalls his trips with post to those villages. Each time he was beginning his journey with letters  to some distinct village in Bitburg. He asks you to calculate, for each such journey (which took place in a      specific moment of time and led from Bitburg to a specified village), how many country roads it led through.

TaskWrite a programme which:

reads from the standard input:

descriptions of roads that once connected Byteotian villages,    sequence of events: Byteasar's trips and the moments when respective roads were transformed    into motorways,            for each trip, calculates how many country roads Byteasar has had to walk,        writes the outcome to the standard output.


有一棵节点数为 $n$ 的树，给定 $m + n - 1$ 组询问，每组询问有两种操作。

1. `A x y`，将 $x$ 节点和 $y$ 节点间的边权改为 $0$，每条边会被修改恰好一次。

2. `W x`，求 $1$ 号点到 $x$ 号点路径上的边权和。

初始所有边权值都为 $1$。
## 输入格式

In the first line of the standard input there is a single integer $n$ ($1\le n\le 250\ 000$),denoting the number of villages in Byteotia. The following $n-1$ lines contain descriptions of the roads, in the form of two integers $a$,$b$ ($1\le a<b\le n$)separated by a single space, denoting the numbers of villages connected with a road. Inthe next line there is a single integer $m$($1\le m\le 250\ 000$),denoting the number of trips Byteasar has made.

The following $n+m-1$ lines contain descriptions of the events, in chronological order:

A description of the form "A $a$ $b$"(for $a<b$) denotes a country road between villages $a$ and $b$ beingtransformed into a motorway in that particular moment.

A description of the from "W $a$" denotes Byteasar's trip from Bitburg to village $a$.

## 输出格式

Your programme should write out exactly $m$ integers to the standard output, one a line, denoting the numberof country roads Byteasar has travelled during his successive trips.

## 样例

### 样例输入 #1
```
5
1 2
1 3
1 4
4 5
4
W 5
A 1 4
W 5
A 4 5
W 5
W 2
A 1 2
A 1 3
```
### 样例输出 #1
```
2
1
0
1
```


---

---
title: "[USACO17JAN] Cow Navigation G"
layout: "post"
diff: 提高+/省选-
pid: P3610
tag: ['2017', 'USACO', '广度优先搜索 BFS', '栈', '队列']
---
# [USACO17JAN] Cow Navigation G
## 题目描述

Bessie has gotten herself stuck on the wrong side of Farmer John's barn again, and since her vision is so poor, she needs your help navigating across the barn.

The barn is described by an $N \times N$ grid of square cells ($2 \leq N \leq 20$), some being empty and some containing impassable haybales. Bessie starts in the lower-left corner (cell 1,1) and wants to move to the upper-right corner (cell $N,N$). You can guide her by telling her a sequence of instructions, each of which is either "forward", "turn left 90 degrees", or "turn right 90 degrees". You want to issue the shortest sequence of instructions that will guide her to her destination. If you instruct Bessie to move off the grid (i.e., into the barn wall) or into a haybale, she will not move and will skip to the next command in your sequence.

Unfortunately, Bessie doesn't know if she starts out facing up (towards cell 1,2) or right (towards cell 2,1). You need to give the shortest sequence of directions that will guide her to the goal regardless of which case is true. Once she reaches the goal she will ignore further commands.


## 输入格式

The first line of input contains $N$.

Each of the $N$ following lines contains a string of exactly $N$ characters, representing the barn. The first character of the last line is cell 1,1. The last character of the first line is cell N, N.

Each character will either be an H to represent a haybale or an E to represent an empty square.

It is guaranteed that cells 1,1 and $N,N$ will be empty, and furthermore it is guaranteed that there is a path of empty squares from cell 1,1 to cell $N, N$.

## 输出格式

On a single line of output, output the length of the shortest sequence of directions that will guide Bessie to the goal, irrespective whether she starts facing up or right.

## 样例

### 样例输入 #1
```
3
EHE
EEE
EEE
```
### 样例输出 #1
```
9
```
## 题目翻译

### 题目描述

Bessie 又一次被困在了 Farmer John 的谷仓的错误一侧，由于她的视力很差，她需要你的帮助来穿过谷仓。

谷仓由一个 $N \times N$ 的方格网格描述（$2 \leq N \leq 20$），其中一些格子是空的，另一些则包含无法通过的干草堆。Bessie 从左下角（格子 1,1）开始，想要移动到右上角（格子 $N,N$）。你可以通过告诉她一系列指令来引导她，每条指令可以是“前进”、“向左转 90 度”或“向右转 90 度”。你需要给出最短的指令序列，以引导她到达目的地。如果你指示 Bessie 移动到网格外（即撞到谷仓墙壁）或进入干草堆，她将不会移动，并跳过你序列中的下一条指令。

不幸的是，Bessie 不知道她最初是面朝上（朝向格子 1,2）还是面朝右（朝向格子 2,1）。你需要给出一个最短的指令序列，无论她最初面朝哪个方向，都能引导她到达目标。一旦她到达目标，她将忽略后续的指令。

### 输入格式

输入的第一行包含 $N$。

接下来的 $N$ 行每行包含一个长度为 $N$ 的字符串，表示谷仓。最后一行的第一个字符是格子 1,1，第一行的最后一个字符是格子 $N,N$。

每个字符要么是 H 表示干草堆，要么是 E 表示空方格。

保证格子 1,1 和 $N,N$ 是空的，并且保证存在一条从格子 1,1 到格子 $N,N$ 的空方格路径。

### 输出格式

输出一行，表示无论 Bessie 最初面朝哪个方向，都能引导她到达目标的最短指令序列的长度。


---

---
title: "[APIO2009] 抢掠计划"
layout: "post"
diff: 提高+/省选-
pid: P3627
tag: ['2009', 'APIO', '强连通分量', '栈']
---
# [APIO2009] 抢掠计划
## 题目描述

Siruseri 城中的道路都是单向的。不同的道路由路口连接。按照法律的规定，在每个路口都设立了一个 Siruseri 银行的 ATM 取款机。令人奇怪的是，Siruseri 的酒吧也都设在路口，虽然并不是每个路口都设有酒吧。  

Banditji 计划实施 Siruseri 有史以来最惊天动地的 ATM 抢劫。他将从市中心出发，沿着单向道路行驶，抢劫所有他途径的 ATM 机，最终他将在一个酒吧庆祝他的胜利。  

使用高超的黑客技术，他获知了每个 ATM 机中可以掠取的现金数额。他希望你帮助他计算从市中心出发最后到达某个酒吧时最多能抢劫的现金总数。他可以经过同一路口或道路任意多次。但只要他抢劫过某个 ATM 机后，该 ATM 机里面就不会再有钱了。 例如，假设该城中有 $6$ 个路口，道路的连接情况如下图所示：  

![](https://cdn.luogu.com.cn/upload/pic/4396.png)  

市中心在路口 $1$，由一个入口符号 → 来标识，那些有酒吧的路口用双圈来表示。每个 ATM 机中可取的钱数标在了路口的上方。在这个例子中，Banditji 能抢劫的现金总数为 $47$，实施的抢劫路线是：$1-2-4-1-2-3-5$。
## 输入格式

第一行包含两个整数 $N,M$。$N$ 表示路口的个数，$M$ 表示道路条数。  

接下来 $M$ 行，每行两个整数，这两个整数都在 $1$ 到 $N$ 之间，第 $i+1$ 行的两个整数表示第 $i$ 条道路的起点和终点的路口编号。  

接下来 $N$ 行，每行一个整数，按顺序表示每个路口处的 ATM 机中的钱数 $a_i$。  

接下来一行包含两个整数 $S,P$，$S$ 表示市中心的编号，也就是出发的路口。$P$ 表示酒吧数目。  

接下来的一行中有 $P$ 个整数，表示 $P$ 个有酒吧的路口的编号。
## 输出格式

输出一个整数，表示 Banditji 从市中心开始到某个酒吧结束所能抢劫的最多的现金总数。
## 样例

### 样例输入 #1
```
6 7 
1 2 
2 3 
3 5 
2 4 
4 1 
2 6 
6 5 
10 
12 
8 
16 
1 
5 
1 4 
4 3 5 6
```
### 样例输出 #1
```
47
```
## 提示

对于 $50\%$ 的数据，保证 $N, M \le 3000$。  

对于 $100\%$ 的数据，保证 $N, M \le 5\times 10^5$，$0 \le a_i \le 4000$。保证可以从市中心沿着 Siruseri 的单向的道路到达其中的至少一个酒吧。


---

---
title: "[USACO17OPEN] Modern Art 2 G"
layout: "post"
diff: 提高+/省选-
pid: P3668
tag: ['贪心', '2017', 'USACO', '栈']
---
# [USACO17OPEN] Modern Art 2 G
## 题目描述

Having become bored with standard 2-dimensional artwork (and also frustrated at others copying her work), the great bovine artist Picowso has decided to switch to a more minimalist, 1-dimensional style.


Although, her paintings can now be described by a 1-dimensional array of colors of length $N$ ($1 \leq N \leq 100,000$), her painting style remains unchanged: she starts with a blank canvas and layers upon it a sequence of "rectangles" of paint, which in this 1-dimensional case are simply intervals. She uses each of the colors $1 \ldots N$ exactly once, although just as before, some colors might end up being completely covered up by the end.


To Picowso's great dismay, her competitor Moonet seems to have figured out how to copy even these 1-dimensional paintings, using a similar strategy to the preceding problem: Moonet will paint a set of disjoint intervals, wait for them to dry, then paint another set of disjoint intervals, and so on. Moonet can only paint at most one interval of each color over the entire process. Please compute

the number of such rounds needed for Moonet to copy a given 1-dimensional Picowso painting.
## 输入格式

The first line of input contains $N$, and the next $N$ lines contain an integer in the range $0 \ldots N$ indicating the color of each cell in the 1-dimensional painting (0 for a blank cell).
## 输出格式

Please output the minimum number of rounds needed to copy this painting, or -1 if this could not have possibly been an authentic work of Picowso (i.e., if she could not have painted it using a layered sequence of intervals, one of each color).

## 样例

### 样例输入 #1
```
7
0
1
4
5
1
3
3
```
### 样例输出 #1
```
2
```
## 提示

In this example, the interval of color 1 must be painted in an earlier round than the intervals of colors 4 and 5, so at least two rounds are needed.
## 题目翻译

### 题目描述

伟大的牛艺术家 Picowso 对标准的二维艺术作品感到厌倦（同时也对其他人抄袭她的作品感到沮丧），于是决定转向一种更极简主义的一维风格。

尽管她的画作现在可以用一个长度为 $N$（$1 \leq N \leq 100,000$）的一维颜色数组来描述，但她的绘画风格保持不变：她从一个空白画布开始，并在其上叠加一系列“矩形”颜料，而在这种一维情况下，这些矩形仅仅是区间。她使用每种颜色 $1 \ldots N$ 恰好一次，尽管和以前一样，某些颜色最终可能会被完全覆盖。

令 Picowso 非常沮丧的是，她的竞争对手 Moonet 似乎已经找到了如何复制这些一维画作的方法，使用的策略与之前的问题类似：Moonet 会绘制一组不相交的区间，等待它们干燥，然后再绘制另一组不相交的区间，依此类推。在整个过程中，Moonet 只能为每种颜色绘制最多一个区间。请计算 Moonet 复制给定的一维 Picowso 画作所需的最少轮数。

### 输入格式

输入的第一行包含 $N$，接下来的 $N$ 行每行包含一个范围在 $0 \ldots N$ 的整数，表示一维画作中每个单元格的颜色（0 表示空白单元格）。

### 输出格式

请输出复制这幅画作所需的最少轮数，如果这幅画作不可能是 Picowso 的真实作品（即她无法通过叠加一系列区间、每种颜色一个区间的方式绘制它），则输出 -1。

### 说明/提示

在这个例子中，颜色 1 的区间必须在颜色 4 和 5 的区间之前绘制，因此至少需要两轮。


---

---
title: "由乃救爷爷"
layout: "post"
diff: 提高+/省选-
pid: P3793
tag: ['洛谷原创', 'O2优化', '栈', 'ST 表', '洛谷月赛']
---
# 由乃救爷爷
## 题目背景

大家看过葫芦娃吧？

没看过也没关系，让由乃告诉你吧

 ![](https://cdn.luogu.com.cn/upload/pic/5725.png) 

 ![](https://cdn.luogu.com.cn/upload/pic/5740.png) 

传说明斯克航空航天局里关着两个坦克，strv103b和krv。

 ![](https://cdn.luogu.com.cn/upload/pic/5733.png) 

 ![](https://cdn.luogu.com.cn/upload/pic/5722.png) 

鼠爷不小心打破了明斯克航空航天局，两个坦克逃了出来，从此其他坦克过上了水深火热的生活。

明斯克航空航天局急忙去告诉一个叫做serb的光头，只有YY出七辆图纸车，才能消灭这两个卖头势力。

serbYY出了七个连图纸都没有的车，却被瑞典人从bbs中窥见 。他们摧毁不了这七个YY车，

就把serb和鼠爷抓去。但是这时候七个坦克模型已经建出来了。

她们分别是 T28原型，T100lt，907工程，蟋蟀15，WZ111，FV215b183，FV215b

她们为了消灭卖头势力，救出serb和鼠爷，一个接一个去与卖头势力搏斗。

 ![](https://cdn.luogu.com.cn/upload/pic/5723.png) 

T28原是正面很硬的TD，但装甲在金币弹面前一点用都没有，直接被krv卖头打死。

 ![](https://cdn.luogu.com.cn/upload/pic/5728.png) 

T100lt是隐蔽超好的眼车，却因为没有视野，被103b活活黑死。

 ![](https://cdn.luogu.com.cn/upload/pic/5724.png) 

907工程是铁头，被krv顶牛直接抽包抽死。

 ![](https://cdn.luogu.com.cn/upload/pic/5727.png) 

蟋蟀15会黑枪，却因为辣鸡的转向被krv绕死。

 ![](https://cdn.luogu.com.cn/upload/pic/5729.png) 

WZ111有三百穿，被103b穿侧面一发爆了弹药架。

 ![](https://cdn.luogu.com.cn/upload/pic/5730.png) 

FV215b183有183炮，103b和krv瑟瑟发抖，不敢打她，于是她解救了其他所有坦克。

 ![](https://cdn.luogu.com.cn/upload/pic/5734.png) 

但是自己的兄弟FV215b因为瑞典人的诱惑，决定叛变（因为183OO大），TK了183一发，然后183着火烧死了，结果所有坦克都被103b和krv降服了。

瑞典人把七个坦克还有鼠爷一起给serb，让serb做出两辆最强坦克加入瑞典阵营。serb用尽了他所有的脑洞，做出了两辆车E100WT和T-50-2

 ![](https://cdn.luogu.com.cn/upload/pic/5731.png) 

 ![](https://cdn.luogu.com.cn/upload/pic/5732.png) 

krv和103b看到之后蛤蛤大笑

krv：E100WT，10mm的脸，不被HE糊死才怪

103b：E100WT，灯塔般的隐蔽，不被黑死才怪

krv：T-50-2，这血量，我一炮就可以打死

103b：T-50-2，看是你机动好还是我黑枪准

serb：百运，胶水，让她们看看你们的厉害

## 题目描述

故事还没讲完

krv骑坡卖头，却发现百运凭借优秀的精度炮炮打穿她的观察孔

krv慌了，跑去城市里面伸缩，被百运站桩撸死

strv103b跑去草后黑枪，看见胶水在肉侦，却发现自己根本打不中她，然后就被胶水点亮了，百运一梭子128的ARCR飞了过来

strv103b怂了，准备跑路了，但是还没等到自己切换回行走模式，胶水已经开始断她的腿了，被胶水断死


瑞典车们高呼不可战胜，从此不敢嚣张了


然后serb把百运和胶水加入了WOT

从此
其他坦克过上了更加水深火热的生活


然而你又不玩WOT，这事情不管你什么事啊

然而yql是大家的妹妹，所以这件事很重要：


yql在AK曼哈顿OI，CTSC，APIO之后，开始研究数学题。

由乃在挂了字符串OI，CTSC，APIO之后，开始研究大母神原型。

yql出了个数学题，由乃画出了一个表示大母神的图腾。

然后把这两个合成了一个题：


然而由于未知原因那个题挂掉了。。。

由乃想起来SCOI 2017 电子科技大学出了个卡常的rmq，然后发生了一件很有趣的事情

就是一位姓王的同学凭借奇奇怪怪的常数优化怒草了那个题，还比标程块了233倍

所以由乃也出了个卡常rmq，因为没题出了

## 输入格式

给你一个随机数生成器

```cpp
namespace GenHelper
{
    unsigned z1,z2,z3,z4,b;
    unsigned rand_()
    {
    b=((z1<<6)^z1)>>13;
    z1=((z1&4294967294U)<<18)^b;
    b=((z2<<2)^z2)>>27;
    z2=((z2&4294967288U)<<2)^b;
    b=((z3<<13)^z3)>>21;
    z3=((z3&4294967280U)<<7)^b;
    b=((z4<<3)^z4)>>12;
    z4=((z4&4294967168U)<<13)^b;
    return (z1^z2^z3^z4);
    }
}
void srand(unsigned x)
{using namespace GenHelper;
z1=x; z2=(~x)^0x233333333U; z3=x^0x1234598766U; z4=(~x)+51;}
int read()
{
    using namespace GenHelper;
    int a=rand_()&32767;
    int b=rand_()&32767;
    return a*32768+b;
}
```
读入三个数n,m,s

你需要srand( s )一下

然后n个数表示a[i]，这个直接调用read函数

然后m个询问，表示区间**最大值**，询问的区间是l = read() % n + 1 , r = read() % n + 1，注意有可能l > r

## 输出格式

输出一个unsigned long long 表示每次询问的答案的和

## 样例

### 样例输入 #1
```
233 233 233
```
### 样例输出 #1
```
243704637294
```
## 提示

```cpp
n,m=1000,1s
n,m=1000,1s
n,m=100000,1s
n,m=500000,1s
n,m=1000000,1s
n,m=10000000,5s
n,m=12000000,5s
n,m=15000000,5s
n,m=20000000,5s
```


---

---
title: "将军令"
layout: "post"
diff: 提高+/省选-
pid: P3942
tag: ['动态规划 DP', '贪心', 'O2优化', '排序', '栈']
---
# 将军令
## 题目背景


> 历史/落在/赢家/之手  
> 至少/我们/拥有/传说  
> 谁说/败者/无法/不朽  
> 拳头/只能/让人/低头  
> 念头/却能/让人/抬头  
> 抬头/去看/去爱/去追  
> 你心中的梦
## 题目描述

又想起了四月。

如果不是省选，大家大概不会这么轻易地分道扬镳吧？  只见一个又一个昔日的队友离开了机房。

凭君莫话封侯事，一将功成万骨枯。


 
梦里，小 F 成了一个给将军送密信的信使。

现在，有两封关乎国家生死的密信需要送到前线大将军帐下，路途凶险，时间紧迫。小 F 不因为自己的祸福而避趋之，勇敢地承担了这个任务。

不过，小 F 实在是太粗心了，他一不小心把两封密信中的一封给弄掉了。

小 F 偷偷打开了剩下的那封密信。他 发现一副十分详细的地图，以及几句批文——原来 这是战场周围的情报地图。他仔细看后发现，在这张地图上标记了 n 个从 1 到 n 标号的 驿站，n − 1 条长度为 1 里的小道，每条小道双向连接两个不同的驿站，并且驿站之间可以 通过小道两两可达。

小 F 仔细辨认着上面的批注，突然明白了丢失的信的内容了。原来，每个驿站都可以驻 扎一个小队，每个小队可以控制距离不超过 k 里的驿站。如果有驿站没被控制，就容易产 生危险——因此这种情况应该完全避免。而那封丢失的密信里，就装着朝廷数学重臣留下的 精妙的排布方案，也就是用了最少的小队来控制所有驿站。

小 F 知道，如果能计算出最优方案的话，也许他就能够将功赎过，免于死罪。他找到了 你，你能帮帮他吗？  当然，小 F 在等待你的支援的过程中，也许已经从图上观察出了一些可能会比较有用的 性质，他会通过一种特殊的方式告诉你。

## 输入格式

从标准输入中读入数据。

输入第 1 行一个正整数 n,k,t，代表驿站数，一支小队能够控制的最远距离，以及特 殊性质所代表的编号。关于特殊性质请参照数据范围。

输入第 2 行至第 n 行，每行两个正整数 $u_i$,$v_i$，表示在 $u_i$ 和 $v_i$ 间，有一条长度为 一里的小道。

## 输出格式

输出到标准输出中。

输出一行，为最优方案下需要的小队数。

## 样例

### 样例输入 #1
```
4 1 0 
1 2 
1 3 
1 4
```
### 样例输出 #1
```
1 
 
```
### 样例输入 #2
```
6 1 0 
1 2 
1 3 
1 4 
4 5 
4 6
```
### 样例输出 #2
```
2 

```
## 提示

【样例 1 说明】

如图。由于一号节点到周围的点距离均是 1，因此可以控制所有驿站。

【样例 2 说明】

如图，和样例 1 类似。



 ![](https://cdn.luogu.com.cn/upload/pic/9813.png) 

子任务会给出部分测试数据的特点。如果你在解决题目中遇到了困难，可以尝试只解 决一部分测试数据。

关于 t 的含义如下： t = 0：该测试点没有额外的特殊性质；  t = 1：保证最多 8 个点的所连接的小道超过 1 条； t = 2：保证所有点到 1 号点的距离不超过 2。


每个测试点的数据规模及特点如下表

![](https://cdn.luogu.com.cn/upload/pic/9812.png)



---

---
title: "[AHOI2006] 基因匹配"
layout: "post"
diff: 提高+/省选-
pid: P4303
tag: ['2006', '各省省选', '树状数组', '安徽', '背包 DP', '栈']
---
# [AHOI2006] 基因匹配
## 题目描述

卡卡昨天晚上做梦梦见他和可可来到了另外一个星球，这个星球上生物的DNA序列由无数种碱基排列而成（地球上只有4种），而更奇怪的是，组成DNA序列的每一种碱基在该序列中正好出现5次！这样如果一个DNA序列有N种不同的碱基构成，那么它的长度一定是5N。 

卡卡醒来后向可可叙述了这个奇怪的梦，而可可这些日子正在研究生物信息学中的基因匹配问题，于是他决定为这个奇怪星球上的生物写一个简单的DNA匹配程序。 

为了描述基因匹配的原理，我们需要先定义子序列的概念：若从一个DNA序列（字符串）s中任意抽取一些碱基（字符），将它们仍按在s中的顺序排列成一个新串u，则称u是s的一个子序列。对于两个DNA序列s1和s2，如果存在一个序列u同时成为s1和s2的子序列，则称u是s1和s2的公共子序列。 

卡卡已知两个DNA序列s1和s2，求s1和s2的最大匹配就是指s1和s2最长公共子序列的长度。 

[任务] 
编写一个程序： 
- 从输入文件中读入两个等长的DNA序列； 
- 计算它们的最大匹配； 
- 向输出文件打印你得到的结果。
## 输入格式

输入文件中第一行有一个整数N，表示这个星球上某种生物使用了N种不同的碱基，以后将它们编号为1…N的整数。 

以下还有两行，每行描述一个DNA序列：包含5N个1…N的整数，且每一个整数在对应的序列中正好出现5次。
## 输出格式

输出文件中只有一个整数，即两个DNA序列的最大匹配数目。
## 样例

### 样例输入 #1
```
2
1 1 1 1 1 2 2 2 2 2 
1 1 1 2 2 2 2 2 1 1 

```
### 样例输出 #1
```
8
```
## 提示

$1 \leq N \leq 20000$


---

---
title: "[IOI 2008] Island"
layout: "post"
diff: 提高+/省选-
pid: P4381
tag: ['动态规划 DP', '2008', 'IOI', 'O2优化', '树的直径', '栈', '队列', '基环树']
---
# [IOI 2008] Island
## 题目描述

你准备浏览一个公园，该公园由 $N$ 个岛屿组成，当地管理部门从每个岛屿 $i$ 出发向另外一个岛屿建了一座长度为 $L_i$ 的桥，不过桥是可以双向行走的。同时，每对岛屿之间都有一艘专用的往来两岛之间的渡船。相对于乘船而言，你更喜欢步行。你希望经过的桥的总长度尽可能长，但受到以下的限制：

- 可以自行挑选一个岛开始游览。
- 任何一个岛都不能游览一次以上。
- 无论任何时间，你都可以由当前所在的岛 $S$ 去另一个从未到过的岛 $D$。从 $S$ 到 $D$ 有如下方法：
  - 步行：仅当两个岛之间有一座桥时才有可能。对于这种情况，桥的长度会累加到你步行的总距离中。
  - 渡船：你可以选择这种方法，仅当没有任何桥和以前使用过的渡船的组合可以由 $S$ 走到 $D$ (当检查是否可到达时，你应该考虑所有的路径，包括经过你曾游览过的那些岛)。

注意，你不必游览所有的岛，也可能无法走完所有的桥。

请你编写一个程序，给定 $N$ 座桥以及它们的长度，按照上述的规则，计算你可以走过的桥的长度之和的最大值。
## 输入格式

第一行包含一个整数 $N$，即公园内岛屿的数目。

随后的 $N$ 行每一行用来表示一个岛。第 $i$ 行由两个以单空格分隔的整数，表示由岛 $i$ 筑的桥。第一个整数表示桥另一端的岛，第二个整数表示该桥的长度 $L_i$。你可以假设对于每座桥，其端点总是位于不同的岛上。
## 输出格式

仅包含一个整数，即可能的最大步行距离。
## 样例

### 样例输入 #1
```
7
3 8
7 2
4 2
1 4
1 9
3 4
2 3
```
### 样例输出 #1
```
24
```
## 提示

**样例解释**：

![样例图示](https://cdn.vijos.org/fs/c82895f1d6f84d5756610176662d6ee644c3e55e)

样例 $N=7$ 座桥，分别为 $(1-3), (2-7), (3-4), (4-1), (5-1), (6-3)$ 以及 $(7-2)$。注意连接岛 $2$ 与岛 $7$ 之间有两座不同的桥。

其中一个可以取得最大的步行距离的方法如下：

- 由岛 $5$ 开始。
- 步行长度为 $9$ 的桥到岛 $1$。
- 步行长度为 $8$ 的桥到岛 $3$。
- 步行长度为 $4$ 的桥到岛 $6$。
- 搭渡船由岛 $6$ 到岛 $7$。
- 步行长度为 $3$ 的桥到岛 $2$。

最后，你到达岛 $2$，而你的总步行距离为 $9+8+4+3=24$。

只有岛 $4$ 没有去。注意，上述游览结束时，你不能再游览这个岛。更准确地说：

- 你不可以步行去游览，因为没有桥连接岛 $2$ (你现在的岛) 与岛 $4$。
- 你不可以搭渡船去游览，因为你可由当前所在的岛 $2$ 到达岛 $4$。一个方法是：走 $(2-7)$ 桥，再搭你曾搭过的渡船由岛 $7$ 去岛 $6$，然后走 $(6-3)$ 桥，最后走 $(3-4)$ 桥。

**数据范围**：

对于 $100\%$ 的数据，$2\leqslant N\leqslant 10^6,1\leqslant L_i\leqslant 10^8$。



---

---
title: "[Wind Festival] Finding RhFe"
layout: "post"
diff: 提高+/省选-
pid: P4741
tag: ['素数判断,质数,筛法', '栈']
---
# [Wind Festival] Finding RhFe
## 题目背景

$[Morning - 8:00 A.M.]$

热衷于结交老铁的$gyx$小哥哥听说了风筝节的举办，一大早就来到了现场，现在他已经迫不及待见到来玩的同学们啦~
## 题目描述

$gyx$的人格魅力是无限哒~

已知风筝节上有$N$($1\le N\le 10^6$)个同学（来玩的人真的很多），每个同学都对$gyx$有一个兴趣程度$c_i$（$ |c_i|\le 10^9$），因为$gyx$的性格特点太明显啦，不存在对$gyx$兴趣程度为$0$的同学，对于每个同学，都可以和$gyx$结交为老铁，$gyx$的高兴程度就是所有结！交！过！成为老铁的同学对$gyx$兴趣程度之和。$gyx$不愿意做令自己伤心的事情，所以如果所有同学对$gyx$感到反感（即兴趣程度为负）$gyx$就会直接离开风筝节。

$gyx$可以选择其中的$k$（$1\le k\le N$）个同学来结交，但一旦选择好，$gyx$的结交顺序就不可以变化了。

因为来风筝节的人实在是太多啦，$gyx$不愿意记住所有的老铁太长的时间，但是$gyx$的脑子里记着与越早结交的老铁的点点滴滴越多，也越难忘记，$gyx$忘记每个人的条件是当且仅当，在$gyx$还记着的老铁里当前的这个老铁是最后结交的。

但是由于$gyx$希望与更多不同性格的同学结交，$gyx$与每一个同学只愿意结交一次，即使遗忘以后也不会再次结交。

当风筝节上$gyx$选择的同学都结交结束后，随着时间的流逝，$gyx$也会渐渐地把所有同学都忘掉，遗忘方式与之前相同，直到最后忘记了自己结交过的所有老铁，再出发前往新的征程。

由于不同的交友并遗忘的顺序可能会发生有趣的事情，$gyx$想知道在保证自己高兴程度最大时选择好结交范围和结交顺序的情况下，$gyx$可以有多少种不同的交友并遗忘的顺序呢？

由于来风筝节的人实在是太多了，$gyx$只想知道不同顺序的方案数的值对$P$（$0<P\le 10^9$）取模后的结果。
## 输入格式

第一行是两个数$N$和$P$，分别表示来风筝节的同学人数和方案数要对P取模；

接下来的$N$行每行一个$c_i$的值，表示第$i$个同学对$gyx$的兴趣程度；
## 输出格式

如果所有人对$gyx$都感到讨厌输出“$Terrible Place$”；

其他情况输出对$P$取模后不同的顺序的方案数的值；
## 样例

### 样例输入 #1
```
8 65
-1
36
21
97
-65
17
1
43
```
### 样例输出 #1
```
2
```
## 提示

对于$30\%$的数据保证$1\le N\le 30$；

对于$70\%$的数据保证$1\le N\le 500$；

对于$100\%$的数据保证$1\le N\le 10^6$，$0<P\le 10^9$，$|c_i|\le 10^9$。



---

---
title: "[USACO15FEB] Censoring S"
layout: "post"
diff: 提高+/省选-
pid: P4824
tag: ['字符串', '2015', '线段树', 'USACO', '栈']
---
# [USACO15FEB] Censoring S
## 题目描述

Farmer John has purchased a subscription to Good Hooveskeeping magazine for his cows, so they have plenty of material to read while waiting around in the barn during milking sessions. Unfortunately, the latest issue contains a rather inappropriate article on how to cook the perfect steak, which FJ would rather his cows not see (clearly, the magazine is in need of better editorial oversight).

FJ has taken all of the text from the magazine to create the string $S$ of length at most 10^6 characters. From this, he would like to remove occurrences of a substring $T$ to censor the inappropriate content. To do this, Farmer John finds the **_first_** occurrence of $T$ in $S$ and deletes it. He then repeats the process again, deleting the first occurrence of $T$ again, continuing until there are no more occurrences of $T$ in $S$. Note that the deletion of one occurrence might create a new occurrence of $T$ that didn't exist before.

Please help FJ determine the final contents of $S$ after censoring is complete.
## 输入格式

The first line will contain $S$. The second line will contain $T$. The length of $T$ will be at most that of $S$, and all characters of $S$ and $T$ will be lower-case alphabet characters (in the range a..z). 
## 输出格式

The string $S$ after all deletions are complete. It is guaranteed that $S$ will not become empty during the deletion process. 
## 样例

### 样例输入 #1
```
whatthemomooofun
moo
```
### 样例输出 #1
```
whatthefun
```
## 题目翻译

### 题目描述

Farmer John 为他的奶牛订阅了《Good Hooveskeeping》杂志，但最新一期包含了一篇不恰当的牛排烹饪文章。为此，FJ 需要将杂志文字组成的字符串 $S$（长度不超过 $10^6$）中所有出现的子串 $T$ 进行删除处理。

删除规则如下：反复找到当前 $S$ 中第一个出现的子串 $T$ 并删除，直到 $S$ 中不再包含 $T$。注意，删除操作可能产生新的 $T$ 子串。

请输出最终处理完成的字符串 $S$。

### 输入格式

第一行输入字符串 $S$。  
第二行输入字符串 $T$。  
保证 $T$ 的长度不超过 $S$，且 $S$ 和 $T$ 均由小写字母组成。删除过程中保证 $S$ 不会变为空。

### 输出格式

输出处理完成后的字符串 $S$。


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

