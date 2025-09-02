---
title: "[常州市赛 2025] 金币"
layout: "post"
diff: 提高+/省选-
pid: B4395
tag: ['数学', '2025', '数论', '江苏', '科创活动', '小学活动']
---
# [常州市赛 2025] 金币
## 题目背景

搬运自 <http://czoj.com.cn/p/1412>。数据为民间数据。
## 题目描述

有 $n$ 个人在争夺一枚金币。

所有人排成一队，然后位于第 $1,1+k,1+2k,\cdots,1+\left(\left\lceil\dfrac nk\right\rceil−1\right)k$ 个的人被淘汰，这里 $\left\lceil\dfrac nk\right\rceil$ 为 $n$ 除以 $k$ 上取整，上取整操作会将一个小数变成大于或等于它的最小整数，如 $\left\lceil\dfrac{33}5\right\rceil=\left\lceil6.6\right\rceil=7$。 重复这一操作，直到仅剩一个人。最终剩下的这个人获得这枚金币。

小 Y 是所有人中最聪明的。他想知道，要想最终获得金币，一开始他应该站在第几个位置？
## 输入格式

一行包含两个正整数 $n$ 和 $k$，表示总人数以及淘汰时用到的参数。
## 输出格式

输出一行一个整数，表示小 Y 应该处于的初始队列中的位置。
## 样例

### 样例输入 #1
```
6 2
```
### 样例输出 #1
```
4
```
### 样例输入 #2
```
8 3
```
### 样例输出 #2
```
8
```
### 样例输入 #3
```
10000 2
```
### 样例输出 #3
```
8192
```
### 样例输入 #4
```
1919810 114514
```
### 样例输出 #4
```
1919805
```
## 提示

### 样例 $\textbf 1$ 解释
起初，队列 $=[1,2,3,4,5,6]$，因为 $k=2$，所以位于第 $1,3,5$ 的人被淘汰，队列 $=[2,4,6]$，然后位于第 $1,3$ 的人被淘汰，队列 $=[4]$，只剩下一个人，所以小 Y 一开始应该站在 $4$ 号位置。
### 样例 $\textbf 2$ 解释
起初，队列 $=[1,2,3,4,5,6,7,8]$，因为 $k=3$，所以位于 $1,4,7$ 的人被淘汰，队列= $[2,3,5,6,8]$，然后位于 $1,4$ 的人被淘汰，队列=$[2,5,8]$，然后位于 $1$ 的人被淘汰，队列 $=[5,8]$，然后位于 $1$ 的人被淘汰，队列 $=[8]$，只剩下一个人，所以小 Y 一开始应该站在 $8$ 号位置。
### 数据范围
本任务共有 $12$ 个数据。

对于全部数据，$2\le n,k\le10^{12}$。
|测试点编号|特殊性质|
|:-:|:-:|
|$1$|$n=k=2$|
|$2\sim4$|$n,k\le 10^3$|
|$5\sim8$|$k\le 10^6$|
|$9\sim12$|无|


---

---
title: "[LMXOI Round 1] Dreamer"
layout: "post"
diff: 提高+/省选-
pid: P10117
tag: ['数论', 'O2优化']
---
# [LMXOI Round 1] Dreamer
## 题目背景

[加强版链接](https://www.luogu.com.cn/problem/U402756)。

这是一道数学题，可是 LMX 给 HQZ 出的。
## 题目描述

定义积性函数 $f(n)=(\mu \ast\operatorname{Id_2})(n)$。

给定 $n,k$，你需要求出 

$$\sum_{i_1\mid n}\sum_{i_2\mid i_1}\cdots\sum_{i_k\mid i_{k-1}}f(i_k)i_1i_k\mu^2\left(\dfrac{i_1}{i_k}\right)$$

#### Tips：

$\mu$ 表示莫比乌斯函数。

关于 $f$，$f(n)=\displaystyle \sum_{d\mid n}\mu(d)\left(\dfrac{n}{d}\right)^2$。
## 输入格式

本题有多组数据，第一行输入一个正整数 $T$，表示数据组数。

考虑到 $n$ 很大，所以我们会给出 $n$ 的标准质因子分解 $n=\displaystyle \prod_{i=1}^t p_i^{\alpha_i}$。

对于每一组询问，我们首先给出两个整数 $k,m$。

第二行给出 $t$，下面 $t$ 行每行两个整数表示 $p_i,\alpha_i$。

（保证 $p_i\ge p_{i-1},i\ge 2$，$\alpha_i\ge 1$）。

## 输出格式

对于每个询问，输出一行表示答案 $\mod m$ 的值。
## 样例

### 样例输入 #1
```
5
3 998244353
3
3 2
5 1
7 1
4 1000000009
2
2 1
3 2
1 998244353
2
2 2
3 1
11451 191981012
11
2 1
3 1
5 1
7 1
11 1
13 1
17 1
19 1
23 1
29 1
31 1
514 520
2
2 10
3 10
```
### 样例输出 #1
```
189282114
124678
14965
82966193
260

```
## 提示

对于 $100\%$ 的数据，有 $T \le 20,n\le 10^{24},1\le k\le 10^6,m\le 1.14\times 10^9$。

| 测试点编号 |      $n$      |    $k$     |   $T$    | 特殊性质 |
| :--------: | :-----------: | :--------: | :------: | :------: |
|    $1$     |   $\le 80$    |  $\le 4$   | $\le 5$  |   $N$    |
|    $2$     |  $\le 10^6$   |  $\le 10$  | $\le 5$  |   $N$    |
|    $3$     | $\le 10^{12}$ |  $\le 20$  | $\le 20$ |   $N$    |
|    $4$     | $\le 10^{18}$ |  $\le 1$   | $\le 20$ |   $N$    |
|    $5$     | $\le 10^{18}$ | $\le 10^3$ | $\le 20$ |   $N$    |
|    $6$     | $\le 10^{18}$ | $\le 10^5$ | $\le 20$ |   $A$    |
|    $7$     | $\le 10^{18}$ | $\le 10^6$ | $\le 20$ |   $B$    |
|    $8$     | $\le 10^{24}$ | $\le 10^6$ | $\le 20$ |   $B$    |
|    $9$     | $\le 10^{24}$ | $\le 10^6$ | $\le 20$ |   $C$    |
|    $10\sim20$    | $\le 10^{24}$ | $\le 10^6$ | $\le 20$ |   $N$    |

性质 $A$：保证 $t\le 10$。

性质 $B$：保证 $n$ 的质因子分解 $\displaystyle\prod_{i=1}^t p_i^{\alpha_i}$ 中 $\alpha_i=1$。

性质 $C$：$m$ 是素数，且保证 $\gcd(n,m)=1$。




---

---
title: "[DTCPC 2024] 取模"
layout: "post"
diff: 提高+/省选-
pid: P10171
tag: ['2024', '数论', '快速傅里叶变换 FFT', '洛谷月赛']
---
# [DTCPC 2024] 取模
## 题目描述

给定序列 $\{a_n\}$ 和 $[L,R]$，问有多少个 $k\in [L,R]$ 满足 $a_i\bmod k$ 互不相同。
## 输入格式

第一行三个正整数 $n,L,R$（$n\leq 5\times 10^4,1\leq L\leq R\leq 10^9$）。

第二行 $n$ 个正整数，表示 $\{a_n\}$（$0 < a_i\leq 4\times10^5$）。
## 输出格式

一行一个数，表示答案。
## 样例

### 样例输入 #1
```
3 1 3
11 7 6
```
### 样例输出 #1
```
1
```


---

---
title: "奉献（Dedication）"
layout: "post"
diff: 提高+/省选-
pid: P10321
tag: ['数学', '数论', '洛谷原创', 'Special Judge', 'O2优化', '素数判断,质数,筛法', '最大公约数 gcd', '洛谷比赛']
---
# 奉献（Dedication）
## 题目背景

不断鞭策自己的数学精神 —— 奉献。
****
「奉献之光」丽莎，既是「秩序之神」派拉的神官，亦为「无秩序之神」迪奥尼斯的信徒。

丽莎最近学习了[高精度除法](https://www.luogu.com.cn/problem/P5432)，她能以 $\Theta(n \log n)$ 的时间复杂度计算 $n$ 位整数除法了。
## 题目描述



丽莎想要制作一张 $n$ 以内正整数的除法表。具体来说，是一张记录了 $\lfloor a/b \rfloor$（$1\leq b \leq a \leq n$，$a,b$ 均为整数）的表格。她使用如下方法来制作：

>以 $a$ 为第一关键字从小到大，以 $b$ 为第二关键字从小到大的顺序枚举位置 $(a,b)$。若 $(a,b)$ 位置**未被填写**，则：
>
>计算 $\lfloor a/b \rfloor$，这需要消耗的**魔力**为 $d_a \log_2 d_a$（其中 $d_a$ 表示 $a$ 在十进制下的位数，即 $d_a=\lfloor 1+ \log_{10}a\rfloor$）。然后枚举正整数 $i$，找到所有**未被填写**的 $(ai,bi)$（$ai\leq n$）位置都填写入 $\lfloor a/b \rfloor$。每次填写需要消耗的魔力为 $d_i$。

由于美娜已经做过一张乘法表，丽莎无需魔力就可以直接计算乘法。现在丽莎想要知道，制作整个除法表需要消耗多少魔力。


为了防止精度问题，只要你的输出与标准输出的**相对误差**不超过 $10^{-6}$ 则视为正确。保证标准输出与实际答案的相对误差不超过 $10^{-10}$。
## 输入格式

输入一行一个正整数 $n$，表示要制作大小为 $n$ 的除法表。
## 输出格式

输出一行一个实数，表示答案。
## 样例

### 样例输入 #1
```
6
```
### 样例输出 #1
```
21.0000000
```
### 样例输入 #2
```
20
```
### 样例输出 #2
```
422.0000000
```
### 样例输入 #3
```
233
```
### 样例输出 #3
```
99838.0384544
```
## 提示

【样例 $1$ 解释】  

由于 $a \leq 6$，$d_a=1$，从而 $d_a \log_2 d_a=0$。也就是说在此范围下只有填写数字会消耗魔力。而每次 $i$ 也不超过 $6$，满足 $d_i=1$，每次填写都消耗固定 $1$ 点魔力，要填写全部 $1+2+3+4+5+6=21$ 个数消耗的魔力就是 $21$。

故答案为 $21$。

【数据范围】  

**本题采用捆绑测试。**  

Subtask 1（15 pts）：$n\le 5000$；  
Subtask 2（15 pts）：$n\le 10^5$；  
Subtask 3（30 pts）：$n\le 2 \times 10^6$；  
Subtask 4（40 pts）：无特殊限制。

对于全部的数据，$1\le n \le 2 \times 10^7$。  

【提示】

$\log_2 n$ 读作「以 $2$ 为底的 $n$ 的对数」。设 $x=\log_2n$，它表示 $2^x=n$。


---

---
title: "The Luckiest Number"
layout: "post"
diff: 提高+/省选-
pid: P10496
tag: ['数论']
---
# The Luckiest Number
## 题目描述

Chinese people think of '8' as the lucky digit. Bob also likes digit '8'. Moreover, Bob has his own lucky number L. Now he wants to construct his luckiest number which is the minimum among all positive integers that are a multiple of L and consist of only digit '8'.
## 输入格式

The input consists of multiple test cases. Each test case contains exactly one line containing L(1 ≤ L ≤ 2,000,000,000).

The last test case is followed by a line containing a zero.
## 输出格式

For each test case, print a line containing the test case number( beginning with 1) followed by a integer which is the length of Bob's luckiest number. If Bob can't construct his luckiest number, print a zero.
## 样例

### 样例输入 #1
```
8
11
16
0
```
### 样例输出 #1
```
Case 1: 1
Case 2: 2
Case 3: 0
```
## 题目翻译

**【题目描述】**

中国人认为“8”是幸运数字。Bob 也喜欢数字“8”。此外，Bob 有自己的幸运数字 $L$。现在，他想构造出自己的最幸运的数字，即所有仅由数字“8”组成且是 $L$ 的倍数的正整数中的最小值。

**【输入格式】**

多个测试用例组成（不超过 $10$ 组）。每个测试用例包含一行，其中包含 $L$（$1 ≤ L ≤ 2,000,000,000$）。

最后一个测试用例后跟着一行，其中包含零。

**【输出格式】**

对于每个测试用例，输出一行，包含测试用例编号（从 $1$ 开始），后跟一个整数，该整数是 Bob 最幸运的数字的长度。如果 Bob 无法构造他最幸运的数字，则输出零。

翻译来自于：[ChatGPT](https://chatgpt.com/)


---

---
title: "『STA - R8』挑战 Goldbach 猜想"
layout: "post"
diff: 提高+/省选-
pid: P11212
tag: ['数学', '数论', 'O2优化']
---
# 『STA - R8』挑战 Goldbach 猜想
## 题目描述

$q$ 次询问，每次给一个正整数 $n$，问有多少个不超过 $n$ 的正整数 $i$ 使得 $i$ 和 $n\bmod i$ 都是质数。


## 输入格式

第一行一个正整数 $q$。

后 $q$ 行，每行一个正整数 $n$。
## 输出格式

$q$ 行，每行回答一组询问。
## 样例

### 样例输入 #1
```
5
5
55
555
5555
55555
```
### 样例输出 #1
```
1
3
22
93
447
```
## 提示

**本题采用捆绑测试。**

数据范围：

- Subtask 1 (30pts)：$q=1$。
- Subtask 2 (70pts)：无特殊限制。

对于全部数据，$1\le n,q\le2\times10^5$。

洛谷代码长度限制：50 KB。


---

---
title: "「CZOI-R2」天平"
layout: "post"
diff: 提高+/省选-
pid: P11373
tag: ['平衡树', '数论', 'O2优化', '最大公约数 gcd', '差分', '洛谷比赛']
---
# 「CZOI-R2」天平
## 题目描述

你有 $n$ 个**砝码组**，编号为 $1$ 至 $n$。对于第 $i$ 个**砝码组**中的砝码有共同的正整数质量 $a_i$，每个**砝码组**中的**砝码**数量无限。

其中，有 $q$ 次操作：

- `I x v`：在第 $x$ 个**砝码组**后新增一组单个**砝码**质量为 $v$ 的**砝码组**，当 $x=0$ 时表示在最前面新增；
- `D x`：删除第 $x$ 个**砝码组**；
- `A l r v`：把从 $l$ 到 $r$ 的所有**砝码组**中的砝码质量加 $v$；
- `Q l r v`：判断能否用从 $l$ 到 $r$ 的**砝码组**中的砝码，称出质量 $v$。每个砝码组中的砝码可以使用任意个，也可以不用。

对于操作 `I` 和 `D`，操作后编号以及 $n$ 的值自动变化。

称一些**砝码**可以称出质量 $v$，当且仅当存在将这些砝码分别放在天平两边的摆放方法，使得将 $1$ 个质量为 $v$ 的物体摆放在某边可以让天平平衡。
## 输入格式

第一行输入 $2$ 个整数 $n,q$。

第二行输入 $n$ 个整数，第 $i$ 个整数为 $a_i$。

接下来 $q$ 行，每行表示一个操作。
## 输出格式

对于每个 `Q` 操作，输出一行 `YES` 或者 `NO`，表示能否称出重量 $v$。
## 样例

### 样例输入 #1
```
5 5
1 10 8 4 2
I 2 1
A 1 4 4
A 2 4 4
D 5
Q 1 4 4
```
### 样例输出 #1
```
YES
```
### 样例输入 #2
```
10 10
2 2 1 4 2 10 8 7 10 6
Q 5 6 1
Q 5 7 7
I 5 1
Q 4 5 3
Q 2 9 2
A 3 5 1
Q 7 8 5
D 7
A 3 9 7
Q 3 7 6
```
### 样例输出 #2
```
NO
NO
NO
YES
NO
YES
```
## 提示

**【样例解释】**

对于样例组 $1$，最后有 $5$ 个中的**砝码组**，质量分别为 $5,18,9,16,2$。在天平左边放上 $1$ 个**砝码组一**中的**砝码**，右边放上 $1$ 个**砝码组三**的砝码，即可称出质量 $4$。

![](https://cdn.luogu.com.cn/upload/image_hosting/lwd6643t.png)

**【数据范围】**

**本题采用捆绑测试**。

记 $m_1$ 为所有时刻中 $a_i$ 与 $v$ 的最小值，$m_2$ 为所有时刻中 $a_i$ 与 $v$ 的最大值。

- Subtask #1（$5\text{ pts}$）：$1\le n,q\le 10$，$1\le m_1\le m_2 \le50$。
- Subtask #2（$15\text{ pts}$）：$1\le n,q\le 4\times10^2$。
- Subtask #3（$20\text{ pts}$）：没有操作 `I` 与操作 `D`。
- Subtask #4（$60\text{ pts}$）：无特殊性质。

对于 $100\%$ 的数据，$1\le n,q\le 10^5$，$1\le m_1\le m_2\le 10^{18}$，保证所有操作合法，且任意时刻至少存在一个砝码组。


---

---
title: "[Sloi 2024]D1T1 精卫"
layout: "post"
diff: 提高+/省选-
pid: P11417
tag: ['数论', '深度优先搜索 DFS', '素数判断,质数,筛法']
---
# [Sloi 2024]D1T1 精卫
## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/p38htsuu.png)
## 题目描述

$f(x)$ 为积性函数，且满足 $f(p^k)=p^{2k}+k$（$p$ 为素数）。

令 $g(x)=\prod\limits_{d|x}f(d)\space \bmod\space (10^9+7)$ ，请计算 $g(i)\space (1\le i \le n)$ 的异或和。
## 输入格式

一行一个正整数 $n$。
## 输出格式

一行一个非负整数。
## 样例

### 样例输入 #1
```
5
```
### 样例输出 #1
```
78
```
### 样例输入 #2
```
142857
```
### 样例输出 #2
```
67850062
```
### 样例输入 #3
```
10000000
```
### 样例输出 #3
```
505679580
```
## 提示

**本题采用捆绑测试**

| Subtask | n | Score |
| :----------: | :----------: | :----------: |
| $1$ | $\le10^4$ | $10$ |
| $2$ | $\le 5\times 10^6$ | $30$ |
| $3$ | $\le 2\times 10^7$ | $30$ |
| $4$ | $\le 5\times10^7$ | $30$ |

对 $100\%$ 的数据，$1\le n \le 5\times10^{7} $。



---

---
title: "[COCI 2024/2025 #2] 差异 / Različitost"
layout: "post"
diff: 提高+/省选-
pid: P11431
tag: ['2024', '数论', '前缀和', 'COCI（克罗地亚）', 'Ad-hoc']
---
# [COCI 2024/2025 #2] 差异 / Različitost
## 题目背景

译自 [COCI 2024/2025 #2](https://hsin.hr/coci/) T3。$\texttt{2s,0.5G}$。满分为 $90$。
## 题目描述


给定无限长的，周期长度为 $n$ 的非负整数序列 $a$ 的前 $n$ 项 $a_1,a_2,\cdots,a_n$。

给定无限长的，周期长度为 $m$ 的非负整数序列 $b$ 的前 $m$ 项 $b_1,b_2,\cdots,b_m$。

给定正整数 $k$，求出 $\displaystyle \left(\sum_{1\le i\le k} a_i\oplus b_i\right)\bmod \left(10^9+7\right)$。
## 输入格式



第一行，三个正整数 $n,m,k$。

第二行，$n$ 个正整数 $a_1,\cdots,a_n$。

第三行，$m$ 个正整数 $b_1,\cdots,b_m$。
## 输出格式

输出一行一个整数表示答案。

## 样例

### 样例输入 #1
```
3 2 10
1 6 4
5 2
```
### 样例输出 #1
```
33
```
### 样例输入 #2
```
10 5 30
5 16 2 10 7 2 4 20 5 12
4 11 14 23 5
```
### 样例输出 #2
```
435
```
## 提示


对于 $100\%$ 的数据，保证：

- $1\le n,m\le 2\times 10^5$；    
- $1\le k\le 10^{18}$；
- $0\le a_i,b_i\le 10^{18}$。


| 子任务编号 | $k\le$ |  特殊性质 | 得分 |  
| :--: | :--: | :--: |:--: | 
| $ 1 $    | $2\times 10^5$ |    |   $ 25 $   |  
| $ 2 $    | $10^{18}$ |  A |  $ 13 $   |  
| $ 3 $    | $10^{18}$  | B | $ 19$   |
| $ 4 $    | $10^{18}$  |  | $ 43 $   |

- 特殊性质 A：$n=m$。
- 特殊性质 B：$n=1$。



---

---
title: "[Algo Beat Contest 001 F] Foolish Math Homework"
layout: "post"
diff: 提高+/省选-
pid: P11684
tag: ['数论', 'O2优化', '分块']
---
# [Algo Beat Contest 001 F] Foolish Math Homework
## 题目背景

|               Problem               | Score |                         Idea                          |                             Std                              |                      Data                       |                            Check                             |                           Solution                           |
| :---------------------------------: | :---: | :---------------------------------------------------: | :----------------------------------------------------------: | :---------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
| $\text{F - Foolish Math Homework}$  | $550$ |    [joe_zxq](https://www.luogu.com.cn/user/623577)    |      [fanchuanyu](https://www.luogu.com.cn/user/706256)      | [joe_zxq](https://www.luogu.com.cn/user/623577) |      [orchardist](https://www.luogu.com.cn/user/347582)      | [Link](https://www.luogu.com.cn/article/6ib0zaqc) by [fanchuanyu](https://www.luogu.com.cn/user/706256) |
## 题目描述

小 F 的数学老师 H 老师给小 F 留了一道数学作业。

> 给定 $a,b,c,d$ 的值，求有多少正整数对 $(x,y)$ 满足以下所有条件。这里，$\gcd(x,y)$ 表示 $x$ 和 $y$ 的最大公约数。
> - $x \le y$。
> - $a \le x \le b$。
> - $c \le y \le d$。
> - $y-x=\gcd(x,y)$。

小 F 觉得这个作业实在是太过愚蠢了，信心满满地写满了暴力，结果发现 $a,b,c,d \le 10^{12}$。你是**作业帮**，你需要帮小 F 完成作业。
## 输入格式

一行四个正整数 $a,b,c,d$，表示 $x$ 和 $y$ 取值的左右边界。
## 输出格式

一行一个正整数，表示答案。
## 样例

### 样例输入 #1
```
2 5 3 7
```
### 样例输出 #1
```
7
```
### 样例输入 #2
```
1 100 1 100
```
### 样例输出 #2
```
382
```
### 样例输入 #3
```
114 514 191 9810
```
### 样例输出 #3
```
2433
```
### 样例输入 #4
```
21899 314099 61699 104699
```
### 样例输出 #4
```
493292
```
## 提示

#### 样例解释 #1

满足条件的 $(x,y)$ 如下所示：

- $(2,3)$
- $(2,4)$
- $(3,4)$
- $(3,6)$
- $(4,5)$
- $(4,6)$
- $(5,6)$

#### 数据范围

对于 $100\%$ 的数据，保证 $1 \le a \le b \le 10^{12}$，$1 \le c \le d \le 10^{12}$。


---

---
title: "檐牙覆雪"
layout: "post"
diff: 提高+/省选-
pid: P11770
tag: ['数论', '洛谷原创', 'O2优化', '洛谷月赛']
---
# 檐牙覆雪
## 题目背景

**为避免卡常，本题时限为比赛时的 2 倍。**

“雨打在窗沿，下坠，一级一级。”

但这次是雪啦！天依与阿绫靠在窗边，赏着乍到的飞雪。
## 题目描述

还是熟悉的地方：一共有 $n$ 级窗沿，从高到低编号，最高层编号为 $1$，最底层编号为 $n$。天依注意到，每一级窗沿上的积雪都可以看作包含若干雪团的可重集合，一开始，第 $1$ 级窗沿上有一团体积为 $1$ 的雪，其他窗沿上没有任何积雪。忽然，一阵夹杂着雪的风刮过，片刻间积雪产生了 $n$ 次变换——

第 $i$ 次变换中，第 $i$ 级窗沿上的**每一团**雪都会被卷起，由于奇妙的物理原因，所有编号是 $i$ 的整数倍（**不包括** $i$ 自身）的窗沿都会接收到新的积雪。具体地，设一团被卷起的雪体积为 $V$，则在上述窗沿中，编号最大者会得到一团体积为 $V+1$ 的积雪，次大者会得到一团体积为 $V+2$ 的积雪，以此类推。最后，被卷起的雪团神奇地回到第 $i$ 级窗沿，也就是说本次变换后，第 $i$ 级窗沿上的积雪没有任何变化。

阿绫知道天依正在好奇：$n$ 次变换之后，每级窗沿上**体积最大的一团**雪的总体积是多少呢？既然她们正静静赏雪，就由你来回答这个问题叭！
## 输入格式

第一行一个整数 $T$，表示数据组数。

第 $2\sim T+1$ 行每行一个整数，分别表示每组数据的 $n$。
## 输出格式

共 $T$ 行，分别表示每组数据的答案。
## 样例

### 样例输入 #1
```
5
1
5
3
114514
2000000
```
### 样例输出 #1
```
1
18
6
18057023450
5575638612615
```
## 提示

**样例解释**

$n=5$ 时的终态如下：

第 $1$ 级窗沿上有体积为 $1$ 的雪团；  
第 $2$ 级窗沿上有体积为 $5$ 的雪团；  
第 $3$ 级窗沿上有体积为 $4$ 的雪团；  
第 $4$ 级窗沿上有体积为 $3,6$ 的雪团；  
第 $5$ 级窗沿上有体积为 $2$ 的雪团；  

体积最大值之和为 $1+5+4+6+2=18$。

### 数据规模与约定

**本题采用捆绑测试。** 仅当你通过了该子任务的全部测试数据才能获得该子任务的分值。

对于 $100\%$ 的数据，$1\le T\le5\times10^5$，$1\le n\le2\times10^6$。

对于不同的子任务，作如下约定：

| 子任务编号 | $T$ | $n$ | 子任务分值 |
| :---: | :---: | :---: | :---: |
| $1$ | $\leq 100$ | $\leq 3\times10^4$ | $15$ |
| $2$ | $\leq 100$ | $\leq 2\times10^6$ | $35$ |
| $3$ | $\leq 3\times10^4$ | $\leq 3\times10^4$ | $15$ |
| $4$ | $\leq 2\times10^5$ | $\leq 2\times10^5$ | $15$ |
| $5$ | $\leq 5\times10^5$ | $\leq 2\times 10^6$ | $20$ |


---

---
title: "[GESP202503 五级] 原根判断"
layout: "post"
diff: 提高+/省选-
pid: P11961
tag: ['2025', '原根', '数论', 'GESP', '欧拉函数']
---
# [GESP202503 五级] 原根判断
## 题目背景

截止 2025 年 3 月，本题可能超出了 GESP 考纲范围。在该时间点下，原根是 NOI 大纲 8 级知识点（NOI 级），而相对简单的无需原根知识的做法中，使用的费马小定理与欧拉定理也属于 NOI 大纲 7 级知识点（提高级），且均未写明于 GESP 大纲中。需要注意，GESP 大纲和 NOI 大纲是不同的大纲。

若对题目中原根这一概念感兴趣，可以学习完成 [【模板】原根](https://www.luogu.com.cn/problem/P6091)。
## 题目描述

小 A 知道，对于质数 $p$ 而言，$p$ 的原根 $g$ 是满足以下条件的正整数：

+ $1<g<p$；
+ $g^{p-1}\bmod{p}=1$；
+ 对于任意 $1\le i<p-1$ 均有 $g^i\bmod{p}\neq1$。

其中 $a\bmod{p}$ 表示 $a$ 除以 $p$ 的余数。

小 A 现在有一个整数 $a$，请你帮他判断 $a$ 是不是 $p$ 的原根。
## 输入格式

第一行，一个正整数 $T$，表示测试数据组数。

每组测试数据包含一行，两个正整数 $a,p$。
## 输出格式

对于每组测试数据，输出一行，如果 $a$ 是 $p$ 的原根则输出 `Yes`，否则输出 `No`。
## 样例

### 样例输入 #1
```
3
3 998244353
5 998244353
7 998244353
```
### 样例输出 #1
```
Yes
Yes
No
```
## 提示

#### 数据范围

对于 $40\%$ 的测试点，保证 $3\le p\le10^3$。

对于所有测试点，保证 $1\le T\le20$，$3\le p\le10^9$，$1<a<p$，$p$ 为质数。


---

---
title: "[USTCPC 2025] 公平抉择"
layout: "post"
diff: 提高+/省选-
pid: P12040
tag: ['2025', '数论', '概率论', '期望', '高校校赛']
---
# [USTCPC 2025] 公平抉择
## 题目背景

考虑到评测机性能差异，改为 400ms 时限。USTCPC 时限为 600ms。

**请注意本题非常规时空限制！**

所以要“费厄”，最好是首先看清对手，倘是些不配承受“费厄”的，大可以老实不客气；待到它也“费厄”了，然后再与它讲“费厄”不迟。(节选自鲁迅《论“费厄泼赖”应该缓行》)

克露丝卡尔酱选择困难！她甚至无法抉择午饭去吃什么，作为她的朋友，你需要和她一起完整**公平的抉择**。
## 题目描述

克露丝卡尔酱在做选择，食堂共有 $n$ 种菜品可选，而她手里只有一个 $k$ 面的骰子(如果 $k = 2$ 则为硬币)。

为了落实公平抉择的理念，她希望她的策略选择到每个菜品的概率相等。

求她期望投掷次数的最小值，**答案对质数 $M$ 取模**。
## 输入格式

一行三个正整数 $n, k, M$ ,分别表示选项数、骰子面数和模数。

$2 \le k \le n \le 3 \times 10^6$，$10^8 \le M \le 10^9$，**保证 $M$ 为质数且对于任意 $1 \le i \le n,k^i \bmod M > 1$**。
## 输出格式

一个整数表示模意义下的答案。

关于分数取模：设答案为 $\dfrac{q}{p}$ 且 $M \nmid p,q$，那么取模结果 $x$ 为 唯一 $x\in[0,M)$ 使得 $px\equiv q\pmod M$。
## 样例

### 样例输入 #1
```
3 2 998244353
```
### 样例输出 #1
```
665496238
```
### 样例输入 #2
```
10 2 998244353
```
### 样例输出 #2
```
798595487
```
## 提示

在样例 $1$ 中，不妨设答案为 $E$。考虑扔两次硬币，得到四种情况，出现概率各为 $\dfrac{1}4$。前三种情况分配给三种菜品，第四种情况重投。故 $E=2+\dfrac{E}4$，解得 $E=\dfrac{8}3$。


---

---
title: "[NWRRC2024] Defective Script"
layout: "post"
diff: 提高+/省选-
pid: P12108
tag: ['2024', '数论', '高斯消元', 'ICPC', '俄罗斯西北']
---
# [NWRRC2024] Defective Script
## 样例

### 样例输入 #1
```
5
4
9 9 6 8
2
3 5
9
9 9 8 2 4 4 3 5 3
3
777 777 777
6
0 1 0 1 0 1
```
### 样例输出 #1
```
5
1
0
777
0
```


---

---
title: "DerrickLo's Buildings (UBC002D)"
layout: "post"
diff: 提高+/省选-
pid: P12181
tag: ['数论', 'O2优化', '期望', '整除分块']
---
# DerrickLo's Buildings (UBC002D)
## 题目描述

在某游戏中，DerrickLo 的任务是操作一堆建筑。这些建筑被摆放在了编号为 $1$ 到 $M$ 的空位上，它们的高度也分别为 $1$ 到 $M$。一开始，对于所有 $i = 1, 2, \dots, M$，高度为 $i$ 的建筑被摆在了 $i$ 号位置上。

在这个游戏中，有 $M$ 个挑战。具体地，第 $i$ 个挑战都会指定一个高度因数 $l = i$ 和目标长度 $N$，这个挑战的**得分**为在重新摆放建筑后，对于所有 $j = 1, 2, \dots N$，满足高度为 $j$ 的建筑被摆在了 $j \times l$ 号位置的数量。**注意：所有挑战的目标长度都是相同的，但高度因数是互不相同的。**

为了重新摆放这些建筑，DerrickLo 需要指定一个调换排列 $v$，每执行一次调换，就会**同时**将位置 $i$ 上的建筑移到 $v(i)$ 处。

由于 DerrickLo 并不是很看重得分是否最高，因此他指定的排列 $v$ 将是从所有 $1$ 到 $M$ 的排列中**等概率**选取的一个。不过，他还是很好奇，对于每一个挑战 $i$，在他分别调换 $1, 2, \dots, V$ 次时，他的期望得分是多少。

由于挑战的个数以及调换的次数实在太多，DerrickLo 希望你告诉所有这些得分之和模 $998244353$ 之后的结果。即：
$$
\left(\sum_{i=1}^M\sum_{k=1}^VE\left(\sum_{j=1}^N[v_k(j) = i \times j]\right)\right)\bmod 998244353
$$
其中 $v_k(j)$ 表示根据排列 $v$ 调换了 $k$ 次之后，高度为 $j$ 的建筑所在的位置编号。
## 输入格式

**本题有多组测试数据。**

第一行，一个正整数 $T$，表示测试数据的个数。

接下来 $T$ 行，每行三个整数 $N, M, V$，描述一个测试数据。

**注意：输入数据不一定在 `int` 范围内。**

## 输出格式

共 $T$ 行，每行一个整数，表示答案。

## 样例

### 样例输入 #1
```
1
1 2 1
```
### 样例输出 #1
```
1
```
## 提示

在样例中，$v$ 只有 $\{1, 2\}$ 与 $\{2, 1\}$ 两种取值。你需要计算：
$$
\sum_{i=1}^2E([v(1) = i])
$$
当 $i=1$ 时，$E([v(1) = 1]) = \frac 1 2$；当 $i=2$ 时，$E([v(1) = 2]) = \frac 1 2$。因此，求和之后是 $\frac{1 + 1}{2} = 1$。

---

对于所有测试数据：

- $1 \le T \le 5$。
- $1 \le N \le M \le 10^{12}$。
- $2 \le (M \bmod 998244353)$。
- $1 \le V \le 10^{12}$。

**注意：输入数据不一定在 `int` 范围内。**



---

---
title: "[蓝桥杯 2024 国 Python B] 全 X 数"
layout: "post"
diff: 提高+/省选-
pid: P12272
tag: ['2024', '数论', '蓝桥杯国赛', '欧拉函数']
---
# [蓝桥杯 2024 国 Python B] 全 X 数
## 题目描述

我们称 $22222, 3333, 7777$ 等由单一数字组成的十进制数为全 $X$ 数。

给定一个整数 $n$，小蓝想知道 $n$ 的所有倍数中最小的全 $X$ 数是多少。由于答案可能很大，你只需要输出答案对 $998244353$ 取模的结果。如果不存在任何答案，请输出 $-1$。
## 输入格式

输入一行包含一个整数 $n$。
## 输出格式

输出一行包含一个整数表示答案。
## 样例

### 样例输入 #1
```
12 
```
### 样例输出 #1
```
444
```
## 提示

### 评测用例规模与约定

- 对于 $50\%$ 的评测用例，$n \leq 5000$；
- 对于 $75\%$ 的评测用例，$n \leq 10^6$；
- 对于所有评测用例，$1 \leq n \leq 10^9$。


---

---
title: "Easy Equation"
layout: "post"
diff: 提高+/省选-
pid: P12388
tag: ['数论', 'O2优化']
---
# Easy Equation
## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/q0ae6v6a.png)

（图：某位不愿透露姓名的热心 /ˈfɜri/ 网友）
## 题目描述

定义：
$$f(n)=\sum_{i=1}^n\sum_{j=1}^n[\operatorname{popcount}(i+j)\gcd(i,j)=\max(i,j)]$$
其中 $\operatorname{popcount}(x)$ 是 $x$ 在二进制下 $1$ 的个数，$\gcd(i,j)$ 是 $i,j$ 的最大公约数。

现在给定正整数 $n$，你需要求出 $f(1)\oplus f(2)\oplus\cdots\oplus f(n)$ 的值。其中 $\oplus$ 是按位异或。
## 输入格式

一行一个正整数 $n$。
## 输出格式

一行一个自然数，表示 $f(1)\oplus f(2)\oplus\cdots\oplus f(n)$ 的值。
## 样例

### 样例输入 #1
```
10
```
### 样例输出 #1
```
13
```
### 样例输入 #2
```
10000
```
### 样例输出 #2
```
3159
```
## 提示

**本题采用捆绑测试。**

- Subtask 1 (10pts)：$n\le 10$。
- Subtask 2 (10pts)：$n\le 10^3$。
- Subtask 3 (20pts)：$n\le 10^5$。
- Subtask 4 (30pts)：$n\le 10^6$。
- Subtask 5 (30pts)：$n\le 10^7$。

对于全部数据，$1\le n\le 10^7$。


---

---
title: "[Math×Girl] 平均律"
layout: "post"
diff: 提高+/省选-
pid: P12469
tag: ['数论', 'O2优化', '莫比乌斯反演', '逆元', 'Stern-Brocot 树']
---
# [Math×Girl] 平均律
## 题目背景

>只见盈盈的双手在键盘上游移，速度越来越快。毫无秩序的音符间填上了其他的音符。一堆杂乱无章的音符中诞生了小小的图案，然后无数的图案开始交织，形成了更大的图案。  
>然后，就从离散走向了连续!

_※ 为了题面的简洁性，我删去了其中与音乐有关的内容。_
## 题目描述

我们定义一个数的近似分数为：  
在允许的误差内分母最小的分数。  
_※ 这里允许分数的分母为 $1$。_

请问允许的误差为 $\pm\delta$ 时，  
任选一数 $\xi\in[0,1]$，  
其近似分数的分母为 $n$ 的概率是多少？
## 输入格式

本题有多组数据，第一行输入一个整数 $T$，表示数据组数。  

对于每一组询问，我们给出 $n,a,b$，  
为了避免浮点误差，令 $\delta=\frac ab$。  

## 输出格式

对于每组数据，一行输出一个数表示概率。  
为了避免整型溢出，输出分数对 $998244353$ 取模后的结果即可。  

## 样例

### 样例输入 #1
```
3
3 1 9
3 2 35
114514 233 87654321
```
### 样例输出 #1
```
332748118
969723086
590198578
```
## 提示

### 样例解释

第一个例子取模前的结果为 $\frac{1}{3}$。  
第二个例子取模前的结果为 $\frac{8}{35}$。  

### 数据范围

**UPD：$n=1$ 时对于子任务限制的描述不正确，请进行特判。**

| 子任务 | 分值 | 限制 |
| :----------: | :----------: | :----------: |
| $0$ | $10$ | $\frac{1}{n}<\delta,n\in[1,10^6]$ |
| $1$ | $10$ | $\delta<\frac{1}{2n^2},n\in[1,10^6]$ |
| $2$ | $15$ | $n\in[1,10^3]$ |
| $3$ | $15$ | $n\in[1,10^4]$ |
| $4$ | $15$ | $n\in[1,10^5]$ |
| $5$ | $15$ | $n\in[1,2\times10^6]$ |
| $6$ | $20$ | $T=1$ |

对于 $100\%$ 数据，保证 $T\in[1,5],n\in[1,10^7],a,b\in[1,10^{18}],998244353\nmid b$。

对于计算有理数取模的方法，请参考[模板题](https://www.luogu.com.cn/problem/P2613)。


---

---
title: "「FAOI-R6」魂灵之影"
layout: "post"
diff: 提高+/省选-
pid: P12604
tag: ['图论', '数论', '交互题', 'O2优化', '二分图']
---
# 「FAOI-R6」魂灵之影
## 题目背景

此题因撞题已移出 FAOI Round 6.

> Draw me to the light, let the curse be lifted  
We can rise above the roar  
With the bite of every devil  
We've felled before  
Drown them out  
Let the fog give way to clarity  
There is power in the strain of every drop I bleed  
I am the venom and the cure  
Take me  
Through the fear, through the heart that's broken  
Our world lies in wait for me  
Every tear, every scar left open  
This is the taming of the beast  
I'll end this war you started  
I'll stitch this wound with bloodshed  
You are my wicked victory  

<https://music.163.com/#/song?id=2672191019>
## 题目描述

给定一个无向**连通**图，边带权，可能存在重边自环。有 $q$ 次查询，每次给定 $x,y,z$，求所有以 $x$ 为起点，$y$ 为终点的路径（不要求为简单路径）中，边权和 $\bmod\ z$ 的最小值是多少。

### 交互方式

**本题为交互题，只支持 C++ 语言提交，并且不支持 C++14 (GCC 9)。**

你需要编写以下三个函数：

```cpp
void Ready(int T, int subtask_id)
```

该函数在每个测试点中仅会调用一次，两个参数表示该测试点的数据组数和子任务编号。样例的子任务编号为 $-1$。

```cpp
void Set(int n, int m, int q, vector <int> u, vector <int> v, vector <int> w)
```

在调用 `Ready` 之后，该函数会（在每个测试点中）被调用 $T$ 次，其中 $n,m$ 分别表示图的边数和点数。$u,v,w$ 的大小均为 $m$，$u[i],v[i],w[i]$ 表示图的一条边。

```cpp
int Go(int x, int y, int z)
```

每次调用 `Set` 之后，该函数会（在每组数据中）被调用 $q$ 次，每次调用表示一次查询。返回值应为本次查询的答案。

你可以直接以下发文件中的 `template.cpp` 为基础编写。
## 输入格式

**以下格式只对本地测试有效，但变量名的含义与实际评测相同。在实际评测中，请不要试图从标准输入（stdin）读取任何内容。**

**本题有多组数据。**

第一行两个非负整数 $T$ 和 $\text{subtask\_id}$，分别表示数据组数和 Subtask 编号。

特别地，样例满足 $\text{subtask\_id}=-1$。

对于每组数据：
- 第一行是空行。
- 第二行三个非负整数 $n,m,q$。
- 接下来 $m$ 行，每行三个非负整数 $u,v,w$，表示一条边。
- 接下来 $q$ 行，每行三个正整数 $x,y,z$，表示一次查询。
## 输出格式

**以下格式只对本地测试有效，但变量名的含义与实际评测相同。在实际评测中，请不要试图向标准输出（stdout）打印任何内容。**

对于每组数据：
- 第一行是空行。
- 下面 $q$ 行，每行一个非负整数，表示答案。
## 样例

### 样例输入 #1
```
2 -1
2 1 1
1 2 1
1 2 2
3 3 1
1 2 1
2 3 1
1 3 1
1 3 2
```
### 样例输出 #1
```
1
0
```
## 提示

#### 【样例解释】

对于第 $1$ 组数据的唯一一组询问，所有路径均形如 $1\to 2\to 1\to \dots \to 1\to 2$，可以证明所有路径的权值均为 $1$。

对于第 $2$ 组数据的唯一一组询问，路径 $1\to 2\to 3$ 权值为 $2\bmod 2=0$，路径 $1\to 3$ 的答案为 $1\bmod 2=1$，所以答案为 $0$。

#### 【数据范围】

对于 $100\%$ 的数据，$0\le T\le 1.5 \times 10^4$，$-1 \le \text{subtask\_id} \le 9$，$0\le n,m,q\le 10^6$，$1\le u,v,x,y\le n$，$0\le w\le 10^9$，$1\le z\le 10^9$，保证图连通。

请下载附件中的 `judge_result.jpeg` 以了解交互库所占用资源的规模。如果你不想下载附件的话，我们在这里用一句话概括一下：保证交互库的运行时间不超过 0.15 秒，占用的内存不超过 60 MB。

**本题开启子任务捆绑测试。**

- Subtask 0 - Subtask 4（10 pts）：$n,m,q,w,z\le 10$，$T \le 1.5 \times 10^4$。
  - Subtask 0（2 pts）：$n=0$。
  - Subtask 1（2 pts）：$n=1$。
  - Subtask 2（1 pts）：$n=2$，$m \le 3$。
  - Subtask 3（4 pts）：$n \le 4$，$m \le 6$，$w \le 8$。
  - Subtask 4（1 pts）：在 Subtask 0 - Subtask 4 下无特殊限制。
- Subtask 5 - Subtask 9（90 pts）：$n,m,q\le 10^6$，$w,z \le 10^9$，$T=1$。
  - Subtask 5（20 pts）：$n,m,q,w,z\le 100$。
  - Subtask 6（20 pts）：$n,m,q,w,z\le 10^3$。
  - Subtask 7（10 pts）：$w,z\le 5$。
  - Subtask 8（10 pts）：$w=1$。
  - Subtask 9（30 pts）：在 Subtask 5 - Subtask 9 下无特殊限制。


Idea：ppip，Solution：喵仔牛奶，Code：ppip，Data：035966_L3

[如何调试？](https://www.luogu.com.cn/paste/3x0kjgps)


---

---
title: "[NAC 2025] A Totient Quotient"
layout: "post"
diff: 提高+/省选-
pid: P12620
tag: ['2025', '数论', 'ICPC', '欧拉函数', 'NAC']
---
# [NAC 2025] A Totient Quotient
## 题目描述

For a positive integer $k$, Euler's totient function $\phi(k)$ is defined as the number of positive integers less than or equal to $k$ and relatively prime to $k$.
For example, $\phi(9) = 6$, $\phi(24) = 8,$ and $\phi(1) = 1$. (As a reminder, the greatest common divisor (gcd) of two positive integers $a$ and $b$ is the greatest positive integer that divides both $a$ and $b$. Two positive integers are relatively prime if their gcd is $1$.)

Euler's product formula gives the value of $\phi(k)$ in terms of the prime factorization of $k$. For a prime $p$, let $\nu_p(k)$ be the highest power of $p$ which divides $k$ (so for example, $\nu_2(48) = 4$, $\nu_3(48)=1$, and $\nu_5(48)=0$). If $k$ is a product of powers of prime factors, $k = \prod_{i=1}^j p_i^{\nu_{p_i}(k)}$ (where the product only includes primes $p_i$ with $\nu_{p_i}(k) > 0$), 
then 
$$ \phi(k) = \prod_{i=1}^j \left[(p_i - 1)\left(p_i^{\nu_{p_i}(k)-1}\right)\right].$$

A recent edition of The American Mathematical Monthly (Li et al., *Positive Rational Numbers of the Form $\phi(m^2)/\phi(n^2)$*, 128(2), 2021) proved the following fact about totient quotients: for any pair of positive integers $a$, $b$ there is a unique pair of positive integers $m$, $n$ for which:
- $\frac{a}{b} = \frac{\phi(m^2)}{\phi(n^2)};$
- if a prime $p$ divides the product $mn$, then $\nu_p(m) \neq \nu_{p}(n)$;
- $\gcd(m,n)$ is square-free: that is, for every prime $p$, $\gcd(m,n)$ is not divisible by $p^2$.

Conditions 2 and 3 guarantee that $m$ and $n$ are the unique smallest pair of positive integers satisfying condition 1.

You'd like to verify this claim numerically. Write a program which takes as input two integers $a$ and $b$ and outputs the corresponding pair $m, n$.
## 输入格式

The only line of input contains two space-separated integers $a$ and $b$ ($ 1 \leq a, b \leq 10\,000$). These two integers are guaranteed to be relatively prime. Additionally, $a$ and $b$ will be chosen so that output values $m$ and $n$ are less than $2^{63}$.
## 输出格式

Print the two positive integers $m$ and $n$ satisfying all three of the conditions of The American Mathematical Monthly's theorem, separated by a space. It is guaranteed that $ m, n < 2^{63}$.
## 样例

### 样例输入 #1
```
9 13
```
### 样例输出 #1
```
18 13
```
### 样例输入 #2
```
19 47
```
### 样例输出 #2
```
13110 18612
```


---

---
title: "最接近的分数"
layout: "post"
diff: 提高+/省选-
pid: P1298
tag: ['数学', '数论']
---
# 最接近的分数
## 题目描述

给出一个正小数，找出分子（分子 $ \ge 0$）不超过 $M$，分母不超过 $N$ 的最简分数或整数，使其最接近给出的小数。“最接近”是指在数轴上该分数距离给出的小数最近，如果这个分数不唯一，输出 ``TOO MANY``。
## 输入格式

输入共有 $2$ 行，第一行包含两个用空格隔开的正整数 $M$ 和 $N$，表示要求的分数其分子不超过 $M$，分母不超过 $N$；第二行为小数 $R(R>0)$，$R$ 的整数部分为一个阿拉伯数字，小数部分最多有十位。
## 输出格式

输出仅 $1$ 行，若解唯一则输出 `分子/分母`（整数 $K$ 写成 $\dfrac{K}{1}$），否则输出 ``TOO MANY``。
## 样例

### 样例输入 #1
```
360 120
3.1415926536

```
### 样例输出 #1
```
355/113

```
## 提示

### 数据范围及约定

对于全部数据，保证 $1\le M,N\le 10^7$。


---

---
title: "[GCJ 2021 #1A] Prime Time"
layout: "post"
diff: 提高+/省选-
pid: P13027
tag: ['数学', '2021', '数论', 'Google Code Jam']
---
# [GCJ 2021 #1A] Prime Time
## 题目描述

You are playing a new solitaire game called Prime Time. You are given a deck of cards, and each card has a prime number written on it. Multiple cards may have the same number.

Your goal is to divide the cards into two groups in such a way that the sum of the numbers in the first group is equal to the product of the numbers in the second group. Each card must belong to exactly one of the two groups, and each group must contain at least one card. The sum or product of a group that consists of a single card is simply the number on that card.

![](https://cdn.luogu.com.cn/upload/image_hosting/n1zowb5r.png)

For example, in the image above, the left group has cards whose sum is $25$ and the right group has cards whose product is $25$. Therefore, this is a valid split into groups.

Your score is the sum of the numbers in the first group (which is equal to the product of the numbers in the second group), or $0$ if you cannot split the cards this way at all. What is the maximum score you can achieve?
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. The first line of each test case contains a single integer $\mathbf{M}$, representing the number of distinct prime numbers in your deck. Each of the next $\mathbf{M}$ lines contains two values: $\mathbf{P}_i$ and $\mathbf{N}_i$, representing that you have exactly $\mathbf{N}_i$ cards with the prime $\mathbf{P}_i$ written on them.

Note that the total number of cards in your deck is the sum of all $\mathbf{N}_i$s.
## 输出格式

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from 1) and $y$ is the maximum score you can achieve.
## 样例

### 样例输入 #1
```
4
5
2 2
3 1
5 2
7 1
11 1
1
17 2
2
2 2
3 1
1
2 7
```
### 样例输出 #1
```
Case #1: 25
Case #2: 17
Case #3: 0
Case #4: 8
```
## 提示

**Sample Explanation**

In Sample Case #1, the optimal split is: $11 + 2 + 7 + 3 + 2 = 5 \cdot 5$. Another split is also possible: $5 + 7 + 3 + 2 + 5 = 11 \cdot 2$, but it gives a lower score.

In Sample Case #2, note that cards with the same number can be placed in different groups.

**Limits**

- $1 \leq \mathbf{T} \leq 100$.
- $1 \leq \mathbf{M} \leq 95$. (Note that there are exactly 95 distinct primes between 2 and 499)
- $2 \leq \mathbf{P}_i \leq 499$, for all $i$.
- Each $\mathbf{P}_i$ is prime.
- $\mathbf{P}_i < \mathbf{P}_{i+1}$, for all $i$. (The primes are given in strictly increasing order)
- $1 \leq \mathbf{N}_i$, for all $i$.

**Test Set 1 (7 Pts, Visible Verdict)**

- $2 \leq \mathbf{N}_1 + \mathbf{N}_2 + \cdots + \mathbf{N}_\mathbf{M} \leq 10$.

**Test Set 2 (13 Pts, Visible Verdict)**

- $2 \leq \mathbf{N}_1 + \mathbf{N}_2 + \cdots + \mathbf{N}_\mathbf{M} \leq 100$.

**Test Set 3 (15 Pts, Hidden Verdict)**

- $2 \leq \mathbf{N}_1 + \mathbf{N}_2 + \cdots + \mathbf{N}_\mathbf{M} \leq 10^{15}$.


---

---
title: "[GCJ 2011 #1C] Perfect Harmony"
layout: "post"
diff: 提高+/省选-
pid: P13373
tag: ['数学', '2011', '数论', 'Google Code Jam']
---
# [GCJ 2011 #1C] Perfect Harmony
## 题目描述

Jeff is a part of the great Atlantean orchestra. Each player of the orchestra has already decided what sound will he play (for the sake of simplicity we assume each player plays only one sound). We say two sounds are in harmony if the frequency of any one of them divides the frequency of the other (that's a pretty restrictive idea of harmony, but the Atlanteans are known to be very conservative in music). Jeff knows that the notes played by other players are not necessarily in harmony with each other. He wants his own note to improve the symphony, so he wants to choose his note so that it is in harmony with the notes all the other players play.

Now, this sounds simple (as all the frequencies are positive integers, it would be enough for Jeff to play the note with frequency $1$, or, from the other side, the Least Common Multiple of all the other notes), but unfortunately Jeff's instrument has only a limited range of notes available. Help Jeff find out if playing a note harmonious with all others is possible.
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case is described by two lines. The first contains three numbers: $N$, $L$ and $H$, denoting the number of other players, the lowest and the highest note Jeff's instrument can play. The second line contains $N$ integers denoting the frequencies of notes played by the other players.

## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the case number (starting from $1$) and $y$ is either the string "NO" (if Jeff cannot play an appropriate note), or a possible frequency. If there are multiple frequencies Jeff could play, output the lowest one.
## 样例

### 样例输入 #1
```
2
3 2 100
3 5 7
4 8 16
1 20 5 2
```
### 样例输出 #1
```
Case #1: NO
Case #2: 10
```
## 提示

**Limits**

- $1 \leq T \leq 40$.

**Small dataset (8 Pts, Test set 1 - Visible)**

- $1 \leq N \leq 100$.
- $1 \leq L \leq H \leq 10000$.
- All the frequencies are no larger than $10000$.
- Time limit: ~~30~~ 3 seconds.

**Large dataset (35 Pts, Test set 2 - Hidden)**

- $1 \leq N \leq 10^4$.
- $1 \leq L \leq H \leq 10^{16}$
- All the frequencies are no larger than $10^{16}$
- Time limit: ~~60~~ 6 seconds.


---

---
title: "[GCJ 2009 #1B] Square Math"
layout: "post"
diff: 提高+/省选-
pid: P13436
tag: ['数学', '图论', '2009', '数论', '广度优先搜索 BFS', 'Google Code Jam']
---
# [GCJ 2009 #1B] Square Math
## 题目描述

Say we have a square that has $W$ cells on each side and, therefore, $W^2$ cells total. Let's go further and fill each cell with one of the following:

* A digit from 0 to 9;
* The addition sign (+);
* The subtraction sign (-).

If, finally, we add a constraint that no 2 digits are horizontally or vertically adjacent and no 2 operators (+ or -) are horizontally or vertically adjacent, then our square can be called an "arithmetic square".

Square Math is the name of a puzzle where, given an arithmetic square, we start from any numeric cell and move either horizontally or vertically a cell at a time, finally ending in a numerical cell. The mathematical expression we get from the traversal is evaluated to get a single value. For example:

```
2+3
+4-
1+0
```

The above is a valid arithmetic square of size $W = 3$. If we start from "2", move horizontally right, then vertically down, we'll get "2+4", which gives a value of "6". If we further move horizontally right, then vertically up, we'll get "2+4-3", which is equal to "3".

In Square Math, there is no limit to how many times you can use a particular cell. It is perfectly legal to move from a cell to its neighbor, then back to the original cell. Given an arithmetic square and a list of queries, your task is to find a Square Math expression which evaluates to each query.
## 输入格式

The first line of input contains a single integer, $T$. $T$ test cases follow. The first line of each test case contains 2 integers, $W$ and $Q$. $W$ lines follow, each containing $W$ characters, representing the arithmetic square. Don't worry, all arithmetic squares in the input are well-formed. The following line contains a space separated list of $Q$ integers, representing the values which need to be computed by using Square Math (the queries). You can assume that all given values will have at least one possible Square Math solution.
## 输出格式

For each test case, begin output with "Case #$X$:" on a line by itself, where $X$ is the test case number, starting from 1. Then, for each query within the test case, print the Square Math expression which evaluates to the query on a line by itself.

In the case where there are multiple possible Square Math expressions, print the one that is shortest. If there is still a tie, print the lexicographically smallest expression. Remember that '+' is lexicographically smaller than '-'.
## 样例

### 样例输入 #1
```
2
5 3
2+1-2
+3-4+
5+2+1
-4-0-
9+5+1
20 30 40
3 2
2+1
+4+
5+1
2 20
```
### 样例输出 #1
```
Case #1:
1+5+5+9
3+4+5+9+9
4+9+9+9+9
Case #2:
2
5+5+5+5
```
## 提示

**Limits**

- $1 \leq T \leq 60$

**Small dataset**

- Time limit: ~~30~~ 3 seconds.
- $2 \leq W \leq 10$
- $1 \leq Q \leq 20$
- $1 \leq \text{each query} \leq 50$

**Large dataset**

- Time limit: ~~60~~ 12 seconds.
- $2 \leq W \leq 20$
- $1 \leq Q \leq 50$
- $1 \leq \text{each query} \leq 250$


---

---
title: "【MGVOI R1-D】图上的数（graph）"
layout: "post"
diff: 提高+/省选-
pid: P13732
tag: ['数学', '数论', 'Special Judge', 'O2优化', '素数判断,质数,筛法', '排列组合']
---
# 【MGVOI R1-D】图上的数（graph）
## 题目描述

你有一张有向图 $G$，这张图中有着无穷多个节点，这些节点的编号为 $1,2,3,...$。

对于任意两个正整数 $i,j$ 而言，当且仅当 $i$ 是 $j$ 的倍数，并且 $i \neq j$ 时，在图 $G$ 中存在一条由 $i$ 号节点指向 $j$ 号节点的边（其长度为 $1$）。

* 下图为 $G$ 中前 $6$ 号节点的状态示例：（点击查看）

::::info[示例]
![](https://cdn.luogu.com.cn/upload/image_hosting/wjfq1qxt.png)
::::

---

对任意的正整数 $x$，给出如下定义：

1. 从 $x$ 号节点到 $1$ 号节点的 **最长路径的长度** 为 $E(x)$；
     
2. 从 $x$ 号节点到 $1$ 号节点的 **最长路径的条数** 为 $T(x)$；
     
3. 设在所有满足 $E(y)=E(x)$ 的正整数 $y$ 中，$T(y)$ 的最大值为 $\max \{ T(y) \}$，则定义 $A(x)$ 的值为 $\dfrac{\max \{ T(y) \} }{T(x)}$；
     
4. 特殊地，规定 $E(1)=0$，$T(1)=A(1)=1$。

可以证明，$A(x)$ 一定是正整数。以下是几个便于你理解上述定义的例子：（点击查看）

::::info[示例]
1. $E(6)=2$，$T(6)=2$，因为从 $6$ 号节点到 $1$ 号节点最多可以经过 $2$ 条边，其对应的 $2$ 条最长路径分别为 $6\rightarrow 3\rightarrow 1$ 和 $6\rightarrow 2\rightarrow 1$。同理可知，$E(4)=2$，$T(4)=1$。

2. $A(6)=1$，因为在所有满足 $E(y)=2$ 的正整数 $y$ 中，可以证明，$T(y)$ 的最大值即为 $2$，与 $T(6)$ 恰好相等。

3. $A(4)=2$，因为在所有满足 $E(y)=2$ 的正整数 $y$ 中，$T(y)$ 的最大值 $2$ 恰好为 $T(4)$ 的 $2$ 倍。

::::


---


给定一个正整数 $N=a^b$，在此基础上，你可以按如下规则构造出一个 $N$ 行 $N$ 列的方格图 $S_N$。

对于正整数 $i,j$（$1\le i,j\le N$）而言：

* 当 $N$ 是 $i$ 的倍数，**并且** $i$ 是 $j$ 的倍数时，第 $i$ 行第 $j$ 列的方格上写有数字 $i\times j\times A(j)$；

* 否则，第 $i$ 行第 $j$ 列的方格上写有数字 $1$。

不难验证 $A(1)=A(2)=A(3)=A(6)=1$。以下是方格图 $S_6$ 的示例：（点击查看）

::::info[示例]
|$1$|$1$|$1$|$1$|$1$|$1$|
|:-:|:-:|:-:|:-:|:-:|:-:|
|$2$|$4$|$1$|$1$|$1$|$1$|
|$3$|$1$|$9$|$1$|$1$|$1$|
|$1$|$1$|$1$|$1$|$1$|$1$|
|$1$|$1$|$1$|$1$|$1$|$1$|
|$6$|$12$|$18$|$1$|$1$|$36$|
::::

---

你需要回答以下两个问题：

* 第一问：$A(N)$ 的值是多少？

* 第二问：在方格图 $S_N$ 中，所有方格上数字的总和是多少？

由于答案可能很大，请将所有答案对 $10^9+7$ 取模。

## 输入格式

**每个测试点包含多组测试数据，各组测试数据之间相互独立。**

第一行包含一个正整数 $T$，表示测试数据的组数。

对于每组测试数据：仅输入一行，包含两个正整数 $a,b$，表示给定的正整数 $N=a^b$。
## 输出格式

对于每组测试数据：仅需在单独一行输出两个非负整数，用空格隔开，分别表示第一问和第二问的答案（均需对 $10^9+7$ 取模）。

::::warning[注意事项]{open}
即使你不回答其中一问，也需要在对应位置上输出一个小于 $10^9+7$ 的非负整数，以满足输出格式。

本题通过 Special Judge 实现两问分别计分，关于具体的分值分配，请参阅【数据范围】板块。
::::
## 样例

### 样例输入 #1
```
1
6 1
```
### 样例输出 #1
```
1 118
```
### 样例输入 #2
```
5
1 1
2 3
6 2
7 1
15 2
```
### 样例输出 #2
```
1 1
6 577
4 12021
1 103
4 352530
```
## 提示

**【样例 #1】**

::::info[样例 #1 解释]

该样例下，$N=6^1=6$。

在【题目描述】中已经解释过 $A(6)=1$（**即第一问的答案**），并画出了方格图 $S_6$，其中所有方格上数字的总和为 $118$（**即第二问的答案**）。

::::

**【样例 #2】**

::::info[样例 #2 解释（第二组测试数据）]

对于第二组测试数据，$N=2^3=8$。

:::success[第一问的答案说明]

首先可以得到 $E(8)=3$，$T(8)=1$，对应的唯一一条最长路为 $8\rightarrow 4\rightarrow 2\rightarrow 1$。

 其次，在所有满足 $E(y)=3$ 的正整数 $y$ 中，有 $\max \{ T(y) \} =6$（详细说明见下），故 $A(8)=\dfrac{6}{T(8)}=6$（**即第一问的答案**）。

 当 $y=30$ 时，有 $E(y)=3$，$T(y)=6$，其对应的 $6$ 条最长路分别为：
 
 * $30\rightarrow 15\rightarrow 5\rightarrow 1$；

 * $30\rightarrow 15\rightarrow 3\rightarrow 1$；

 * $30\rightarrow 10\rightarrow 5\rightarrow 1$；

 * $30\rightarrow 10\rightarrow 2\rightarrow 1$；

 * $30\rightarrow 6\rightarrow 3\rightarrow 1$；

 * $30\rightarrow 6\rightarrow 2\rightarrow 1$。

可以证明，$T(30)=6$ 就是在所有满足 $E(y)=3$ 的正整数 $y$ 中，$T(y)$ 的最大值。

:::

:::success[第二问的答案说明]

列出 $A(x)$ 的值表：

|$x$|$1$|$2$|$4$|$8$|
|:-:|:-:|:-:|:-:|:-:|
|$A(x)$|$1$|$1$|$2$|$6$|

接下来，画出方格图 $S_8$：

|$1$|$1$|$1$|$1$|$1$|$1$|$1$|$1$|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$2$|$4$|$1$|$1$|$1$|$1$|$1$|$1$|
|$1$|$1$|$1$|$1$|$1$|$1$|$1$|$1$|
|$4$|$8$|$1$|$32$|$1$|$1$|$1$|$1$|
|$1$|$1$|$1$|$1$|$1$|$1$|$1$|$1$|
|$1$|$1$|$1$|$1$|$1$|$1$|$1$|$1$|
|$1$|$1$|$1$|$1$|$1$|$1$|$1$|$1$|
|$8$|$16$|$1$|$64$|$1$|$1$|$1$|$384$|


所有方格上数字的总和为 $577$（**即第二问的答案**）。
:::

::::

---



::::info[样例 #2 解释（第三组测试数据）]

对于第三组测试数据，$N=6^2=36$。

分析可知 $E(36)=4$，$T(36)=6$。而在所有满足 $E(y)=4$ 的正整数中，取 $y=210$ 即可最大化 $T(y)$，有 $\max \{ T(y) \} =T(210)=24$，据此可得到 $A(36)=\dfrac{T(210)}{T(36)}=4$（**即第一问的答案**）。

由于方格图 $S_{36}$ 的篇幅过大，下面仅画出其最后一行（也就是第 $36$ 行）的状态，并标出列编号：


| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 | 31 | 32 | 33 | 34 | 35 | 36 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: 
| $36$ | $72$ | $108$ | $288$ | $1$ | $216$ | $1$ | $1$ | $648$ | $1$ | $1$ | $864$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1296$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $5184$ |

在画出完整的方格图后可以验证，$S_{36}$ 中所有方格上数字的总和为 $12021$（**即第二问的答案**）。

:::warning[温馨提示]
请不要忘记将所有答案对 $10^9+7$ 取模！
:::

::::


**【样例 #3】**

见附件中的 ```graph/graph3.in``` 与 ```graph/graph3.ans```。

这个样例满足测试点 $2 \sim 4$ 的限制。

**【样例 #4】**

见附件中的 ```graph/graph4.in``` 与 ```graph/graph4.ans```。

这个样例满足测试点 $5 \sim 6$ 的限制。

**【样例 #5】**

见附件中的 ```graph/graph5.in``` 与 ```graph/graph5.ans```。

这个样例满足测试点 $7 \sim 10$ 的限制。



---




**【数据范围】**

对于所有测试点，保证 $1\le T\le 100$，$1\le a \le 2\times 10^9$，$1\le b \le 2\times 10^3$。

::cute-table{tuack}

| **测试点编号** | $T \le$ | $a \le$ |  $b \le$ | **特殊性质** |
|:-:|:-:|:-:|:-:|:-:|
| $1$ | $2$ | $10$ | $1$ | **AB**
| $2\sim 4$ | $20$ | $2\times 10^3$ | $10$ | ^
| $5\sim 6$ | $100$ | $2\times 10^9$ | $2\times 10^3$ | **C** | 
| $7\sim 10$ | ^ | ^ | ^ | 无

特殊性质 **A**：保证 $a^b\le 2\times 10^3$，即 $N\le 2\times 10^3$。

特殊性质 **B**：保证存在正整数 $k$（$k\le 5\times 10^5$）满足 $E(k)=E(N)$，$T(k)=A(N)\times T(N)$。

特殊性质 **C**：保证 $a$ 是质数（注意：不保证 $N$ 是质数）。

* 分值分配：每个测试点的分值为 $10$ 分。对于单个测试点，如果你的程序对第一问和第二问均回答正确，则获得满分 $10$ 分；若只回答对了第一问，得 $2$ 分；若只回答对了第二问，得 $8$ 分；若两问均未答对（或输出格式错误），得 $0$ 分。


---

---
title: "[HNOI2002] 跳蚤"
layout: "post"
diff: 提高+/省选-
pid: P2231
tag: ['2002', '各省省选', '数论', '湖南', '最大公约数 gcd', '不定方程', '莫比乌斯反演']
---
# [HNOI2002] 跳蚤
## 题目描述

Z 城市居住着很多只跳蚤。在 Z 城市周六生活频道有一个娱乐节目。一只跳蚤将被请上一个高空钢丝的正中央。钢丝很长，可以看作是无限长。节目主持人会给该跳蚤发一张卡片。卡片上写有 $N+1$ 个自然数。其中最后一个是 $M$，而前 $N$ 个数都不超过 $M$，卡片上允许有相同的数字。跳蚤每次可以从卡片上任意选择一个自然数 $S$，然后向左，或向右跳 $S$ 个单位长度。而他最终的任务是跳到距离他左边一个单位长度的地方，并捡起位于那里的礼物。

比如当 $N=2,M=18$ 时，持有卡片 $(10, 15, 18)$ 的跳蚤，就可以完成任务：他可以先向左跳 $10$ 个单位长度，然后再连向左跳 $3$ 次，每次 $15$ 个单位长度，最后再向右连跳 $3$ 次，每次 $18$ 个单位长度。而持有卡片 $(12, 15, 18)$ 的跳蚤，则怎么也不可能跳到距他左边一个单位长度的地方。

当确定 $N$ 和 $M$ 后，显然一共有 $M^ N$ 张不同的卡片。现在的问题是，在这所有的卡片中，有多少张可以完成任务。

## 输入格式

输入文件有且仅有一行，包括用空格分开的两个整数 $N$ 和 $M$。

## 输出格式

输出文件有且仅有一行，即可以完成任务的卡片数。

$1\le N\le M\le 10^8$，且$M^N\le 10^{16}$。

## 样例

### 样例输入 #1
```
2 4
```
### 样例输出 #1
```
12
```
## 提示

这12张卡片分别是：

$(1, 1, 4), (1, 2, 4), (1, 3, 4), (1, 4, 4), (2, 1, 4), (2, 3, 4)$

$(3, 1, 4), (3, 2, 4), (3, 3, 4), (3, 4, 4), (4, 1, 4), (4, 3, 4)$



---

---
title: "[USACO20FEB] Delegation G"
layout: "post"
diff: 提高+/省选-
pid: P6147
tag: ['2020', 'USACO', '数论', '树的遍历']
---
# [USACO20FEB] Delegation G
## 题目描述

Farmer John 有 $N$ 个牧场，这些牧场通过 $N-1$ 条道路连接，形成了一个树形结构。

但在 28 年的经营后（译者注：USACO 创办于 1992 年），FJ 觉得处理树上问题非常辣手，他认为一条链上的问题更加简单。

因此他决定将整棵树划分为若干条链，将每一条链的管理权授予一位工人。为了避免可能的争端，他希望所有链的长度均相同。

FJ 现在想知道，对于每一个满足 $1 \leq K \leq N-1$ 的 $K$，是否存在一种划分方案，使得整棵树被划分成若干条链，且每条链的长度都**恰好**是 $K$。
## 输入格式

第一行一个整数 $N$（$1 \leq N \leq 10^5$）。

接下来 $N-1$ 行，每行两个整数 $u,v$（$1 \leq u,v \leq N$），描述一条连接 $u,v$ 的道路。
## 输出格式

输出一个长度 $N-1$ 的 0/1 串。第 $i$ 位的值为 $1$ 当且仅当存在一种划分方案，使得整棵树被划分成若干条链，且每条链的长度都恰好是 $i$，否则第 $i$ 位的值为 $0$。
## 样例

### 样例输入 #1
```
13
1 2
2 3
2 4
4 5
2 6
6 7
6 8
8 9
9 10
8 11
11 12
12 13
```
### 样例输出 #1
```
111000000000
```
## 提示

### 样例解释

$K=1,2,3$ 时都存在一种合法的划分方案。

$K=3$ 时的一种划分方案如下：

$13-12-11-8, 10-9-8-6, 7-6-2-3, 5-4-2-1$

### 子任务

- 测试点 $2 \sim 4$ 满足**最多**有一个点的度数大于 $2$。
- 测试点 $5 \sim 8$ 满足 $N \leq 10^3$。
- 测试点 $9 \sim 15$ 没有特殊限制。


---

---
title: "回首过去"
layout: "post"
diff: 提高+/省选-
pid: P6583
tag: ['数论', '洛谷月赛']
---
# 回首过去
## 题目背景

>明天你是否会想起
>
>昨天未调完的题
>
>明天你是否还惦记
>
>考场写挂的暴力

[OEIS 入口](http://oeis.org/)
## 题目描述

在小学时，小 Z 就已经开始学
 OI 了。

有一次，在数学课上，老师问了这样一个问题：
求出有序整数对 $(x,y)$ 的个数，满足 $1\le x,y\le 5$ 且 $\frac{x}{y}$ 可以表示为十进制有限小数。

当然，小 Z 很快就算了出来。

但因为他是学了 OI 的，所以他就推广了一下：

**给定正整数 $n$，求出有序整数对 $(x,y)$ 的个数，满足 $1\le x,y\le n$ 且 $\frac{x}{y}$ 可以表示为十进制有限小数。**

当时，他还是一个菜鸡，只会
 $O(n^2)$ 的暴力。

过了几年，他偶然又翻到了这道题。现在他会了一种更好的方法，于是就把这题出了出来，给你来做做。
## 输入格式

一行一个正整数 $n$。
## 输出格式

一行一个整数表示答案。
## 样例

### 样例输入 #1
```
3
```
### 样例输出 #1
```
7
```
### 样例输入 #2
```
5
```
### 样例输出 #2
```
21
```
## 提示

**样例 1 解释**

$\frac{1}{1}$，$\frac{1}{2}$，$\frac{2}{1}$，$\frac{2}{2}$，$\frac{3}{1}$，$\frac{3}{2}$，$\frac{3}{3}$ 都可以表示为十进制有限小数。

**数据规模与约定**

* Subtask 1（40 分），$1 \le n \le 10^3$；
* Subtask 2（40 分），$1 \le n \le 10^7$；
* Subtask 3（20 分），$1 \le n \le 10^{12}$。


---

---
title: "「MCOI-02」Convex Hull 凸包"
layout: "post"
diff: 提高+/省选-
pid: P6810
tag: ['2020', '数论', '洛谷原创', '最大公约数 gcd']
---
# 「MCOI-02」Convex Hull 凸包
## 题目背景

一场比赛需要一道签到题。
## 题目描述

Leasier 玩 MC 被逮到了，所以他只好算出下面这个式子的值。

$$\displaystyle\sum_{i = 1}^n \sum_{j = 1}^m \tau(i) \tau(j) \tau(\gcd(i, j))$$

由于结果可能很大，所以你只需要求出结果对 $p$ 取模的值。

如果您对本题的数学符号有疑问，请到「提示」区查看提示。
## 输入格式

一行，三个整数 $n, m, p$。
## 输出格式

一行，一个整数，表示所求的值。
## 样例

### 样例输入 #1
```
5 7 9
```
### 样例输出 #1
```
5
```
## 提示

#### 数据规模和约定
**本题开启捆绑测试。**

| Subtask | $n, m$ | 分值 |
| :------: | :------: | :------: |
| $1$ | $1 \leq n, m \leq 10^3$ | $15 \operatorname{pts}$ |
| $2$ | $1 \leq n, m \leq 10^5$ | $25 \operatorname{pts}$ |
| $3$ | $1 \leq n, m \leq 10^6$ | $30 \operatorname{pts}$ |
| $4$ | 无特殊限制 | $30 \operatorname{pts}$ |

对于 $100\%$ 的数据，$1 \leq n, m \leq 2 \times 10^6$，$1 \leq p \leq 10^9$。
#### 提示
作为对萌新友好的签到题，肯定是要给提示的。

- $\sum$ 为求和符号，比如 $\displaystyle\sum_{i = 1}^n i$ 代表 $1 + 2 + \cdots + n$。
- $\tau$ 表示约数个数，比如 $\tau(6) = 4$。
- $\gcd$ 是最大公约数，比如 $\gcd(12, 15) = 3$。
#### 说明
Minecraft OI Round 2 A

- Maker：Leasier
- Tester：happydef


---

---
title: "Chino 与线段树"
layout: "post"
diff: 提高+/省选-
pid: P7122
tag: ['高精度', '2020', 'O2优化', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---
# Chino 与线段树
## 题目描述

Chino 刚学习了一种叫做线段树的数据结构。可是她在写线段树时遇到了一个问题：她不知道该使用多大的空间，只知道线段树的叶子结点个数 $n$ 为一个在范围 $[a,b]$ 之内的正整数。

Chino 设 $f(n)$ 表示一棵 $n$ 个叶子结点的线段树所占的最大数组下标。她觉得如果她知道了

$$\sum_{n=a}^{b}f(n)$$

那么她就能够算出她需要多少使用多大的空间。所以她来请教聪明的你来帮帮她。

具体地，Chino 构建线段树的伪代码如下：

$$
\def\b#1{\textbf{#1}}\def\t#1{\text{#1}}\def\s\qquad\def\P{\mathbb P}\def\l{\underline{\kern{300pt}}}\def\m#1{#1&\,}
\def\if#1{\b{if }#1\b{ then}}\def\endfunc{\b{end function}.}\def\endif{\b{end if}.}\def\func{\b{function}}\def\return{\b{return}}
\begin{aligned}&\l\\&\b{Function: }\t{Build a Segment Tree.}\\[-10pt]&\l\\[-5pt]&\begin{array}{r|l}\\[-9pt]
\m1\func\ \t{BuildSegmentTree}\left(x,l,r\right):\\
\m2\s\if{\left(l\ne r\right)}:\\
\m3\s\s m\gets\left\lfloor\left(l+r\right)/2\right\rfloor.\\
\m4\s\s\t{BuildSegmentTree}\left(2x,l,m\right).\\
\m5\s\s\t{BuildSegmentTree}\left(2x+1,m+1,r\right).\\
\m6\s\endif\\
\m7\endfunc\\[-10pt]\\\end{array}\\[-13pt]&\l\end{aligned}
$$

线段树所占的最大数组下标即为在 $\def\t#1{\text{#1}}\t{BuildSegmentTree}\left(1,1,n\right)$ 后所有调用的 $\def\t#1{\text{#1}}\t{BuildSegmentTree}$ 中参数 $x$ 的最大值。
## 输入格式

输入共二行。

第一行为一个正整数 $a$；第二行为一个正整数 $b$。其意义如题面所述。
## 输出格式

输出一行一个正整数，表示你的答案。
## 样例

### 样例输入 #1
```
1
10

```
### 样例输出 #1
```
108

```
### 样例输入 #2
```
233333
666666

```
### 样例输出 #2
```
588544964910

```
### 样例输入 #3
```
1
1000000000000000000

```
### 样例输出 #3
```
1419691012023749904603586777179575510

```
## 提示

### 样例解释 #1
$1\sim 10$ 个叶子结点的线段树的最大下标分别为 $1,3,5,7,9,13,13,15,17,25$，求和得到 $108$。

### 测试点约束
**本题采用捆绑测试。**

对于全部数据，有 $1\le a\le b\le10^{10^6}$。

每个子任务的具体限制见下表：

| 子任务编号 | 分值 | $b\le$ | $a=b$ |
|:-:|:-:|:-:|:-:|
| 1 | 10 | $10^{10^0}$ | $\times$ |
| 2 | 10 | $10^{10^1}$ | $\times$ |
| 3 | 10 | $10^{10^2}$ | $\times$ |
| 4 | 10 | $10^{10^3}$ | $\surd$ |
| 5 | 10 | $10^{10^3}$ | $\times$ |
| 6 | 10 | $10^{10^4}$ | $\surd$ |
| 7 | 10 | $10^{10^4}$ | $\times$ |
| 8 | 10 | $10^{10^5}$ | $\surd$ |
| 9 | 10 | $10^{10^5}$ | $\times$ |
| 10 | 10 | $10^{10^6}$ | $\times$ |


---

---
title: "[CoE R4 B/Stoi2041] 龙拳"
layout: "post"
diff: 提高+/省选-
pid: P8302
tag: ['模拟', '数学', '数论', '洛谷原创', 'O2优化', '枚举', '洛谷月赛']
---
# [CoE R4 B/Stoi2041] 龙拳
## 题目背景

![](bilibili:BV1fx411N7bU?page=28)
## 题目描述

对于 $n \in \mathbb{Z_{\ge 2}}$，设 $g(n)$ 为 $n$ 的小于 $n$ 的最大约数，如 $g(7) = 1, g(12) = 6$。

定义 $f(n) = n + g(n)$。记 $f^{(0)}(n)=n$，且对 $m \in \mathbb{Z_{\ge 0}}$ 有 $f^{(m+1)}(n)=f(f^{(m)}(n))$。

多次询问，每次询问给定正整数 $n,k$，求最小的自然数 $m_0$，使得对于任意 $m \ge m_0$，均有 $f^{(m)}(n) \mid f^{(m+k)}(n)$。

若不存在这样的 $m_0$，则令 $m_0=-1$。
## 输入格式

第一行一个正整数 $T$ 表示询问次数。

接下来 $T$ 行，每行两个正整数 $n,k$，表示一次询问。
## 输出格式

对于每组询问输出一个整数表示答案。
## 样例

### 样例输入 #1
```
2
2 3
3 4

```
### 样例输出 #1
```
0
-1

```
## 提示

### 样例解释

当 $n=2,k=3$ 时，$m_0=0$。

当 $n=3,k=4$ 时不存在满足条件的 $m_0$。

---

### 数据规模

**本题采用捆绑测试。**

- 子任务 $1$（$1$ 分）：$T=k=1$；
- 子任务 $2$（$12$ 分）：$T,n,k \le 10$；
- 子任务 $3$（$24$ 分）：$T \le 10,n \le 10^5$；
- 子任务 $4$（$36$ 分）：$T \le 10^3$；
- 子任务 $5$（$27$ 分）：无特殊限制。

对于 $100\%$ 的数据，保证 $1 \le T \le 2 \times 10^6$，$2 \le n \le 3 \times 10^7$，$1 \le k \le 10^9$。



---

---
title: "「WHOI-1」Derives"
layout: "post"
diff: 提高+/省选-
pid: P8357
tag: ['动态规划 DP', '数论', 'Special Judge', 'O2优化', '记忆化搜索']
---
# 「WHOI-1」Derives
## 题目背景

你的钱里面混进去了一个假币。
## 题目描述

你有 $n$ 枚硬币。经过准确的测量，你发现一定有一枚是假币，假币的质量与其他硬币不同。你想要找出这枚假币。

第 $i$ 轮，假设你当时有 $x_i$ 枚硬币，你会把当前钱堆所有钱分配到若干组，每组 $k_i$ 个，最终剩下的再单独分一组。每个硬币你要拿起来需要 $a$ 秒，那么这将会花费你 $ax_i$ 秒的时间。接下来，你会称量每一组，称量每组需要 $b$ 秒，所以这将会花费你 $b\cdot\lceil\frac{x_i}{k_i}\rceil$ 秒的时间。由于只有一枚假币，那么只会有一堆的质量与正常的质量不同。**在称量所有堆之后**，你将会选出与正常质量不同的那一堆，并进入下一轮，让 $x_{i+1}=k_i$。一直执行，直到 $x_i=1$。假设进行了 $m$ 轮，那么花费时间 $f=\sum\limits_{i=1}^{m}{(ax_i+b\cdot\lceil\frac{x_i}{k_i}\rceil)}$

请问，你在最差情况下（**即每轮选出不正常的都是 $k_i$ 个一堆的**）最少需要多长时间找出那枚假币？
## 输入格式

一行三个正整数，代表 $n,a,b$。
## 输出格式

第一行两个个非负整数 $f,m$，代表最小可能的时间和你的方案的轮数。

接下来一行 $m$ 个正整数，代表 $k_i$。
## 样例

### 样例输入 #1
```
20 1 3
```
### 样例输出 #1
```
51 2
4 1
```
### 样例输入 #2
```
1000 10 100
```
### 样例输出 #2
```
13570 4
72 12 3 1
```
## 提示

**说明**

**你需要尽量使得花费的时间更少。**

本题采用 Special Judge。

首先，你输出的答案一定要合法，也就是你输出的答案要与下面的选择方法符合，否则将获得 $0$ 分。

接下来，评测机会对你的输出进行判断。如果你输出的答案合法且与正确答案的差 $\le9$，那么你将获得 $(10-d)\times100\%$ 的分数。例如，如果你输出的答案与正确答案的差为 $4$，那么你将获得 $60\%$ 的分数。如果你输出的答案等于正确答案，你将获得 $100\%$ 的分数。请不要输出多余的数字或少输出。

**数据范围**

- $\text{subtask 1(10pts)}:$ $1\le n\le2000$。
- $\text{subtask 2(20pts)}:$ $1\le n\le75000$。
- $\text{subtask 3(30pts)}:$ $1\le n\le10^7$。
- $\text{subtask 4(40pts)}:$ $1\le n\le10^9$。

对于所有数据，满足 $0<a,b\le10^9$。

**样例说明**

对于第一个样例，进行两轮。$x_1=20,k_1=4,x_2=4,k_2=1$。答案 $f=20+15+4+12=51$。


---

---
title: "「FAOI-R1」完美的平方数"
layout: "post"
diff: 提高+/省选-
pid: P8447
tag: ['动态规划 DP', '数论', 'O2优化', '背包 DP']
---
# 「FAOI-R1」完美的平方数
## 题目描述

给定一个正整数 $m$。现有 $Q$ 个询问，每个询问给定一个正整数 $n$，要求你从 $1,4,9,16,\ldots,m^2$ 中取出若干个数（**同一个数可以取出多次**），使它们的和**恰好**为 $n$。问最少取出多少个数？（如果无解，则输出 $-1$）
## 输入格式

**本题有多组数据。**

第一行，一个正整数 $T$，代表数据组数。

对于每组数据：

第一行，两个正整数 $m,Q$。

下面 $Q$ 行，每行一个正整数 $n$。

## 输出格式

对于每组数据的每个询问，输出一行一个正整数，表示答案。
## 样例

### 样例输入 #1
```
5
1 5
1
2
3
4
5
5 5
8
20
25
37
49
11 1
179
13 1
507
19 1
841
```
### 样例输出 #1
```
1
2
3
4
5
2
2
1
4
4
3
3
4
```
## 提示

样例解释：

对于第一组数据，显然答案是 $n$，因为你只能取 $1$。

对于第二组数据：

- $8=2^2+2^2$；
- $20=4^2+2^2$；
- $25=5^2$；
- $37=5^2+2^2+2^2+2^2$；（或 $37=4^2+4^2+2^2+1^2$）
- $49=5^2+4^2+2^2+2^2$；（或 $49=4^2+4^2+4^2+1^2$）
- **请注意，$37=6^2+1^2$ 和 $49=7^2$ 都不是合法的方案，因为该数据中 $m=5$。**

------------

**本题采用捆绑测试。**

| Subtask 编号 | $m\le$ | $n \le$ | 分值 |
| :--: | :--: | :--: | :--: |
| $0$ | $30$ | $10^4$ | $40$ |
| $1$ | $30$ | $10^{18}$ | $30$ |
| $2$ | $500$ | $10^{18}$ | $30$ |

对于 $100\%$ 的数据，$1 \le T \le 30$，$1 \le Q \le 10^4$，$1 \le m \le 500$，$1 \le n \le 10^{18}$，单个测试点中所有数据的 $m$ 的和（$\sum m$）满足 $1 \le \sum m \le 500$。


---

---
title: "[LSOT-1] 记忆崩塌"
layout: "post"
diff: 提高+/省选-
pid: P8450
tag: ['动态规划 DP', '原根', '数论', '洛谷原创', '交互题', 'Special Judge', 'O2优化']
---
# [LSOT-1] 记忆崩塌
## 题目背景

“铃铃铃”，上课铃打响。一阵眩晕，小 H 突然倒在地上。只是隐约间，感受到周围有人赶过来。

“这是哪里？我不是在上课吗？”小 H 望向周围。

“欢迎来到 OI 世界。我负责带你熟悉 OI 世界。”一个奇怪的人走到这里来。

“OI 世界？”

“对。这里没有文化课，你可以在这里尽情学习 OI。”那人解释道。

紧接着，那人将小 H 带到了一个自称是心理学家的人面前。

“你在干什么？”小 H 望着那个心理学家。他正准备把一个奇怪的东西戴到小 H 头上。

“这个可以帮你恢复你在 whk 世界的记忆。”心理学家淡淡地说。

仪器戴到头上后，小 H 大喊：“我什么都想起来了！”

然而，真的什么都想起来了吗……

从那个人带着小H前往OI世界观光开始，这一切，全都乱了……
## 题目描述

**这是一道交互题。**

小 H 失忆了。

现在，小 H 过去的记忆化成了 $n$ 个记忆碎片。医生拥有 $n$ 种长度的取样条（长度为 $1\dots n$）。记忆碎片会与长度为 $i$ 的取样条发生大小为 $\gcd(n,i)$ 的情感共鸣。

医生有一个机器，可以测出长度为 $i$ 的取样条与小 H 产生的情感共鸣大小。现在你可以用这个机器测量一定的次数，医生希望你能告诉他若用完 $n$ 种长度的取样条小 H 总共会发生多大的情感共鸣。

### 交互格式
你可以用以下格式来询问医生你想知道的东西：

`TheSame? m`：下接 $m$ 行，每行两个数 $p_i,k_i$，医生会告诉你数小 H 的记忆碎片数量是否与 $\displaystyle\prod_{i=1}^mp_i^{k_i}$ 相等。`Yes` 代表相同或 `No` 代表不同。

`GetGCD. m`：下接 $m$ 行，每行两个数 $p,k$ ，医生会告诉你$\displaystyle\prod_{i=1}^mp_i^{k_i}$  与小 H 的记忆碎片产生的情感共鸣大小。

所有询问的 $p_i$ 为素数，$k_i$ 为正整数，不符合上述限制的交互不保证交互库会做出预期行为。

***

你可以用以下格式来告诉医生你知道的东西：

`IFoundTheAnswer! m`：以此来告诉评测器我已经知道了小 H 总共产生的情感共鸣大小为 $m$，并评判是否正确。

***

你一共可以与医生交互 $1050$ 次。交互库的所有输出与你输出的答案均应对 $998244353$ 取模。

***

你需要从**标准输出**中输出，代表你询问的内容。

每一次询问后都应当**清空缓冲区**，不然你会无缘无故 TLE。

你可以使用如下语句来清空缓冲区：

- 对于 C/C++：`fflush(stdout)`；
- 对于 C++：`std::cout << std::flush`；
- 对于 Java：`System.out.flush()`；
- 对于 Python：`stdout.flush()`；
- 对于 Pascal：`flush(output)`；
- 对于其他语言，请自行查阅对应语言的帮助文档。

特别的，对于 C++ 语言，在输出换行时如果你使用 `std::endl` 而不是 `'\n'`，也可以自动刷新缓冲区。

然后你需要从**标准输入**中输入，代表评测机返回的结果。
## 输入格式

见「交互格式」。

## 输出格式

见「交互格式」。

## 样例

### 样例输入 #1
```
1
No
2
Yes
```
### 样例输出 #1
```
GetGCD. 0
TheSame?  0
GetGCD. 1
2 1
TheSame? 1
2 1
IFoundTheAnswer! 3
```
## 提示

【数据范围】

**「本题采用捆绑测试」**

- $\texttt{Subtask 1(10 pts)：}1 \le\ n\le 500$；
- $\texttt{Subtask 2(25 pts)：}1 \le\ n\le 10^6$；
- $\texttt{Subtask 3(25 pts)：}$保证 $n$ 的唯一分解形式仅有前 $100$ 个质数；
- $\texttt{Subtask 4(40 pts)：}$无特殊限制。

对于 $100\%$ 的数据，满足 $n$ 的唯一分解形式质数数量不超过 $1000$，且质因子最大不超过 $7919$（注：$7919$ 为第 $1000$ 个质数），且质数的次数不超过 $10000$。

【其他提示】

因为交互库的效率较低，所以附件中给出交互库的代码。如果你想利用下面的交互库代码进行调试，你可以在官方的 [SPJ 说明](https://www.luogu.com.cn/blog/luogu/special-judge) 中下载 ```testlib.h``` 头文件后将两个程序的输出输入到另一个程序中。当然，你也可以模拟交互库的计算来手动输入到你的程序中。


---

---
title: "「Wdoi-2」夜空中的 UFO 恋曲"
layout: "post"
diff: 提高+/省选-
pid: P8540
tag: ['数学', '数论', '洛谷原创', 'O2优化', '洛谷月赛']
---
# 「Wdoi-2」夜空中的 UFO 恋曲
## 题目背景

土地变得泥泞，曾被寒冰覆盖的大地上，万物开始复苏。  
覆盖着幻想乡的少量积雪，封住了在这个冬天苏醒的地灵们，   
也足以使妖精们的活动变得迟钝。这样安稳沉睡的季节也即将告一段落。

博丽神社的巫女博丽灵梦从居住在森林里的魔法使那儿听到了一个传闻说，有人目击到云的缝隙中有不可思议的船在空中飞行。

——船中空空如也。  
曾在船中的金银财宝早已散佚，剩下的东西也散发着  
陈年霉臭。  
仅凭凛冽春风，仍不足以将那霉味吹散。  
但是，只有那位大人留下的宝物，即使变成碎片也不会失去威力吧。

只是那些碎片依旧以不可思议不可理解的形态飘在幻想乡各处，对扑簌迷离的真相加盖了疑问的迷雾。

貌似有很深的原因。我们不知道的某种东西，在酝酿着什么。
## 题目描述

### 简要题意
给定正整数 $a,b,c$，满足 $a,b,c\textcolor{red} > 1$。对于函数 $f_k$，给出如下定义：

$$f_{k}(x)=\begin{cases}
x^{2c}\oplus c & k = 1\\
f_{k-1}(x^{2c}\oplus c) & k > 1
\end{cases}$$

其中 $\oplus$ 表示二进制下的异或操作。

现在要求计算出 $\operatorname{lowbit}(f_{b}(a))$。其中 $\operatorname{lowbit}(x)$ 表示二进制下 $x$ 最右侧的 $1$ 所在位置对应的二进制值，例如：

$$\operatorname{lowbit}(101101\cdots 10\textcolor{red}1\underbrace{00\cdots000}_{k\text{ 个 }0})=2^k$$

特别地，若 $x=0$，则 $\operatorname{lowbit}(x)=0$。
### 原始题意
为了去除碎片上附加的「不明的因子」，主角组需要破开[【正体不明】](https://www.luogu.com.cn/user/35891)附加的法术。

不明的因子是一种小蛇一般的飞行物，在不同人的眼中具有不同的形象。  
当有人看到它时，会按照自己的常识，把它看成自己认识的、认为合理的东西。

碎片的表面有一个由红蓝组成的长串，妖怪贤者发现，若将红看作 $0$，蓝看作 $1$，它就成了一个二进制数字 $x$。  
碎片上一共有 $k$ 层不明因子，每破开一层都会使数字 $x$ 变为 $x^{2c}\oplus c$（其中 $\oplus$ 表示二进制下的异或操作）。  
为了破解法术，主角组需要根据给定的常数 $c$，初始值 $a$ 和层数 $k=b$ 先破开所有的不明因子，然后计算剩下的数字所代表的串中， 最右侧的「蓝色」所在位置对应的二进制值。

经过主角们一定的分析，她们发现了 $a,b,c\textcolor{red} > 1$。

紫把[式神计算机](https://www.luogu.com.cn/user/149196)搬了出来就回去睡觉了，把编制程序的任务交给了可怜的金发小女孩。你的任务就是帮她完成程序的编制，彻底肃清异变的影响，找回丢失的记忆。
## 输入格式

第一行有三个正整数 $a,b,c$，含义如题面所示。

再次强调，$a,b,c\textcolor{red} > 1$。
## 输出格式

输出共一行一个整数，表示 $\operatorname{lowbit}(f_b(a))$ 的值。
## 样例

### 样例输入 #1
```
5 2 4
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
1000000000000000000 1000000000000000000 1000000000000000000
```
### 样例输出 #2
```
262144
```
## 提示

### 样例 1 解释

- $f_{2}(5)=f_1(5^8\oplus 4)=f_1(390{,}629)$；
- $f_1(390{,}629)=390{,}629^8\oplus 4=542{,}145{,}496{,}755{,} 385{,}548{,}075{,}315{,}235{,}215{,}044{,}149{,}100{,}456{,}165$；
- 容易发现，$f_{2}(5)$ 的 $\text{lowbit}$ 值为 $1$。

### 数据范围及约定

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|c|}\hline
\textbf{Subtask} & \bm{a,b,c\le} & \textbf{特殊性质} & \textbf{分值} \cr\hline
1 & 11 & - & 25 \cr\hline
2 & 10^{18} & \text{A} & 35 \cr\hline
3 & 10^{18} & - & 40 \cr\hline
\end{array}$$

- **特殊性质** $\textbf{A}$：保证 $c$ 为偶数。

对于全部数据，保证 $1 \textcolor{red}< a,b,c\le 10^{18}$。


---

---
title: "[蓝桥杯 2016 国 B] 广场舞"
layout: "post"
diff: 提高+/省选-
pid: P8645
tag: ['计算几何', '2016', '数论', '蓝桥杯国赛']
---
# [蓝桥杯 2016 国 B] 广场舞
## 题目描述

LQ 市的市民广场是一个多边形，广场上铺满了大理石的地板砖。

地板砖铺得方方正正，就像坐标轴纸一样。

以某四块砖相接的点为原点，地板砖的两条边为两个正方向，一块砖的边长为横纵坐标的单位长度，则所有横纵坐标都为整数的点都是四块砖的交点（如果在广场内）。

广场的砖单调无趣，却给跳广场舞的市民们提供了绝佳的参照物。每天傍晚，都会有大批市民前来跳舞。

舞者每次都会选一块完整的砖来跳舞，两个人不会选择同一块砖，如果一块砖在广场边上导致缺角或者边不完整，则没人会选这块砖。

（广场形状的例子参考图）

![](https://cdn.luogu.com.cn/upload/image_hosting/kjgaxse9.png)

现在，告诉你广场的形状，请帮 LQ 市的市长计算一下，同一时刻最多有多少市民可以在广场跳舞。
## 输入格式

输入的第一行包含一个整数 $n$，表示广场是 $n$ 边形的（因此有 $n$ 个顶点）。

接下来 $n$ 行，每行两个整数，依次表示 $n$ 边形每个顶点的坐标（也就是说广场边缘拐弯的地方都在砖的顶角上。数据保证广场是一个简单多边形。
## 输出格式

输出一个整数，表示最多有多少市民可以在广场跳舞。
## 样例

### 样例输入 #1
```
5
3 3
6 4
4 1
1 -1
0 4
```
### 样例输出 #1
```
7
```
### 样例输入 #2
```
3 3
```
### 样例输出 #2
```
4
```
## 提示

**【样例说明】**

广场如图所示，一共有 $7$ 块完整的地板砖，因此最多能有 $7$ 位市民一起跳舞。

**【数据规模与约定】**

对于 $30\%$ 的数据，$n$ 不超过 $100$，横纵坐标的绝对值均不超过 $100$。

对于 $50\%$ 的数据，$n$ 不超过 $1000$，横纵坐标的绝对值均不超过 $1000$。

对于 $100\%$ 的数据，$n$ 不超过 $1000$，横纵坐标的绝对值均不超过 $10^8$。

时限 1 秒, 256M。蓝桥杯 2016 年第七届


---

---
title: "[蓝桥杯 2018 国 B] 矩阵求和"
layout: "post"
diff: 提高+/省选-
pid: P8670
tag: ['2018', '数论', '蓝桥杯国赛']
---
# [蓝桥杯 2018 国 B] 矩阵求和
## 题目描述

经过重重笔试面试的考验，小明成功进入 Macrohard 公司工作。

今天小明的任务是填满这么一张表：

表有 $n$ 行 $n$ 列，行和列的编号都从 $1$ 算起。

其中第 $i$ 行第 $j$ 个元素的值是 $\gcd(i, j)$ 的平方，$\gcd$ 表示最大公约数，以下是这个表的前四行的前四列：

```
1  1  1  1
1  4  1  4
1  1  9  1
1  4  1 16
```

小明突然冒出一个奇怪的想法，他想知道这张表中所有元素的和。
由于表过于庞大，他希望借助计算机的力量。

## 输入格式

一行一个正整数 $n$ 意义见题。
## 输出格式

一行一个数，表示所有元素的和。由于答案比较大，请输出模 $1000000007$（即$10^9+7$）后的结果。
## 样例

### 样例输入 #1
```
4
```
### 样例输出 #1
```
48
```
## 提示

对于 $30\%$ 的数据，$n\le 1000$。

存在 $10\%$ 的数据，$n = 10^5$。

对于 $60\%$ 的数据，$n\le 10^6$。

对于 $100\%$ 的数据，$n\le 10^7$。



---

---
title: "「CGOI-3」残暴圣所"
layout: "post"
diff: 提高+/省选-
pid: P8958
tag: ['洛谷原创', 'O2优化', '快速傅里叶变换 FFT', '快速数论变换 NTT']
---
# 「CGOI-3」残暴圣所
## 题目背景

终于打过春二心门的 ac 来到了春三，并决定预测一下残暴圣所（Ferocious Sanctuary）的难度。

[![](https://cdn.luogu.com.cn/upload/image_hosting/xolrra48.png?x-oss-process=image/resize,m_lfit,h_340,w_450)](//www.bilibili.com/video/BV1Cg411v7Ji)
## 题目描述

为了通关残暴圣所，ac 需要在接下来的 $2n$ 个时刻进行 $n$ 次操作。第 $i$ 次操作需要在时刻 $l_i$ 按下某个按键，此后一直按住这个按键，直到时刻 $r_i$ 松开它（$l_i<r_i$）。在每个时刻，ac 要么按下一个按键，要么松开一个按键，但是可以同时按住多个按键。

第 $i$ 次操作形成了一个操作区间 $[l_i,r_i]$，满足 $l_i$ 严格递增。并且，由于残暴圣所的关卡设计，任意两个操作形成的操作区间之间，要么不交，要么包含。

ac 设计了 $2n$ 个难度系数 $a_1,a_2,\dots,a_{2n}$。第 $i$ 次操作的难度可以用 $a_{l_i}\times a_{r_i}$ 来评估，而通关残暴圣所的难度即为所有操作的难度之和。

然而，由于 ac 卡在了残暴圣所的第一面，所以他并不知道每个操作的操作区间。在给定 $n$ 和 $\{a\}$ 的前提下，请你计算对于所有可能的情况，通关残暴圣所的难度之和，对 $998244353$ 取模。

#### 形式化题意：

给定一个长为 $2n$ 的数列 $a_1,a_2,\dots,a_{2n}$。

定义“区间组”由 $n$ 个区间组成，第 $i$ 个区间为 $[l_i,r_i]\ (1\le l_i<r_i\le2n)$，求所有满足下列条件的区间组的 $\sum_{i=1}^na_{l_i}\times a_{r_i}$ 之和对 $998244353$ 取模：

1. $l_1,r_1,l_2,r_2,\dots,l_n,r_n$ 是 $1,2,\dots,2n$ 的一个排列。
2. $\forall 1\le i<n$，$l_i<l_{i+1}$。
3. $\forall i,j$，$[l_i,r_i]\cap[l_j,r_j]=\varnothing$ 或 $[l_i,r_i]\sube[l_j,r_j]$ 或 $[l_j,r_j]\sube[l_i,r_i]$。

## 输入格式

第一行一个整数 $n$，表示区间数。

第二行 $2n$ 个整数 $a_i$，含义如上所述。
## 输出格式

一行一个整数，表示答案对 $998244353$ 取模的值。
## 样例

### 样例输入 #1
```
2
114 514 1919 810
```
### 样例输出 #1
```
2691692
```
### 样例输入 #2
```
3
1 1 4 5 1 4
```
### 样例输出 #2
```
98
```
### 样例输入 #3
```
8
275272885 418731188 289662326 114331587 192436268 885936831 877490593 508774565 633402863 149033362 995239139 494498006 168828873 138947653 983144753 844326228
```
### 样例输出 #3
```
349824160
```
## 提示

#### 样例说明

对于样例 1，可能的两个操作区间只有两种情况：

1. $[1,2],[3,4]$，通关难度为 $a_1a_2+a_3a_4=1612986$。
2. $[1,4],[2,3]$，通关难度为 $a_1a_4+a_2a_3=1078706$。

难度之和为 $1612986+1078706=2691692$，对 $998244353$ 取模后仍为 $2691692$。

以下几种情况是不合法的：

1. $[3,4],[1,2]$，因为要求 $l_i$ 严格递增，而 $l_1\ge l_2$。
2. $[1,1],[2,4]$，因为要求 $l_i<r_i$，而 $l_1\ge r_1$。
3. $[1,3],[2,3]$，因为要求在每个时刻，要么按下一个按键，要么松开一个按键，而第三个时刻松开了两个按键，第四个时刻没有按下或松开任何一个按键。
4. $[1,3],[2,4]$，因为要求任意两个操作区间不交或包含，而这两个区间之间有交，并且没有包含关系。

---

#### 数据范围

对于 $10\%$ 的数据，$n\le15$。

对于 $30\%$ 的数据，$n\le200$。

对于 $50\%$ 的数据，$n\le3000$。

对于另 $5\%$ 的数据，$a_i=1$。

对于 $100\%$ 的数据，$1\le n\le5\times10^5$，$0\le a_i<998244353$。


---

---
title: "「WHOI-4」ggcd"
layout: "post"
diff: 提高+/省选-
pid: P8961
tag: ['数论', 'Special Judge', 'O2优化', '素数判断,质数,筛法', '中国剩余定理 CRT']
---
# 「WHOI-4」ggcd
## 题目背景

如何输入输出 `__int128`：

```cpp
__int128 read() {
  char c = getchar();
  __int128 x = 0;
  bool f = 0;
  for (; !isdigit(c); c = getchar()) f ^= !(c ^ 45);
  for (; isdigit(c); c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
  if (f) x = -x;
  return x;
}
void write(__int128 x, char c = '\0') {
  if (x < 0) putchar('-'), x = -x;
  if (x > 9) write(x / 10);
  putchar(x % 10 + '0');
  if (c != '\0') putchar(c);
}
```
## 题目描述

**本题已新增一组样例，请注意查看。**

小 Y 给了你长度为 $n$ 的数组 $y$ 以及一个正整数 $m$，保证 $0\le y_i<m$，请你构造一个同样长为 $n$ 的数组 $x$，使得：

1. $x_i$ 在 `__int128` 范围内；
2. $x_i\bmod m=y_i$；
3. $\gcd(|x_1|,\cdots,|x_n|)\bmod m$ 最大。

注意，$x_i$ **可以为负**，此时 $m\mid (x_i-y_i)$ 且 $0\le y_i<m$。 
## 输入格式

第一行两个正整数 $n,m$。

接下来一行 $n$ 个非负整数，代表 $x_i \bmod m$ 的值。
## 输出格式

第一行一个非负整数 $g$，代表 $\gcd(|x_1|,|x_2|,\cdots,|x_n|)\mod m$ 的可能最大值。

接下来一行 $n$ 个整数，代表 $x_i$。
## 样例

### 样例输入 #1
```
1 10
4
```
### 样例输出 #1
```
6
-6
```
### 样例输入 #2
```
1 10
7
```
### 样例输出 #2
```
7
7
```
### 样例输入 #3
```
2 9
3 3
```
### 样例输出 #3
```
6
12 -6
```
### 样例输入 #4
```
10 7
1 2 3 4 5 6 0 1 2 3
```
### 样例输出 #4
```
6
36 30 24 18 12 6 42 -6 30 24
```
## 提示

**数据范围**

**本题采用捆绑测试。**

Subtask 1（$30$ pts）：$m$ 是素数。

Subtask 2（$70$ pts）：无特殊限制。

对于所有数据，保证 $2\le m \le10^9$，$1\le n\le10^6$。

**关于 Special Judge**

对于每个测试点：

如果你输出的格式不正确，你将会获得 $0$ 分。

如果你输出的数中有不在 `__int128` 范围的数，可能导致溢出所以你可能无法获得预期的分数。

如果你的数列 $x$ 不符合题目给定的 $y$，你将会获得 $0$ 分。

如果你的数列 $x$ 不符合你输出的 $g$，你将会获得 $0$ 分。

如果你的 $g$ 不为最大，你将会获得 $0$ 分。

否则你将获得该测试点的所有分数。


---

---
title: "[入门赛 #9] 最澄澈的空与海 (Hard Version)"
layout: "post"
diff: 提高+/省选-
pid: P9007
tag: ['数学', '2023', '数论', 'O2优化', '素数判断,质数,筛法', '逆元', '语言月赛']
---
# [入门赛 #9] 最澄澈的空与海 (Hard Version)
## 题目背景

材料 1：

> 请小心地计算下面的算式：$138 - 108 \div 6 = ?$  
> 你大概难以置信，这个算式的计算结果竟然是 $5!$

材料 2：

> 对于一个正整数 $x$，$x! = 1 \times 2 \times \cdots \times (x - 1) \times x$。我们称 $x!$ 为 $x$ 的阶乘。  
> 特别的，$0! = 1$。

显然，「$138 - 108 \div 6 = 5$」是错误的，而「$(138 - 108) \div 6 = 5$」是正确的，所以对材料 1 中的内容，部分读者会认为「作者没有搞清加减乘除的运算优先级关系而犯错」。

然而，材料 1 最后一行的叹号并不是标点符号，而是材料 2 提到的「阶乘」。

考虑到这一点，「$138 - 108 \div 6 = 5! = 1 \times 2 \times \cdots \times 5 = 120$」显然就是正确的了。
## 题目描述

然而，此题可能与上面的题目背景关系不是很大。

我们会给你 $T$ 组数据，每组数据包括一个正整数 $n$。

对于每组数据，请你帮助求出满足以下条件的整数三元组 $(x, y, z)$ 的组数：

1. $x \geq 0$，$z \geq 1$。
2. $x - y \div z = n!$ 且 $(x - y) \div z = \dfrac{n!}{n}$。

由于答案可能过大，因此你需要输出答案对 $998244353$ 取模后的结果。

不难注意到答案有可能为 $\infty$，这时请按照「输出格式」要求进行处理。

**请注意此处应满足 $(x - y) \div z = \dfrac{n!}{n}$ 而不是 $= n$。**

请注意这里的 $\div$ 不是向下取整的整除，这显然意味着你需要保证 $y \div z$ 和 $(x - y) \div z$ 为整数。
## 输入格式

输入共 $T + 1$ 行。

第一行为一个整数 $T$。

接下来 $T$ 行，每行一个整数 $n$。
## 输出格式

输出共 $T$ 行，每行一个整数或一个字符串。

对第 $i$ 行，如果对于输入数据中第 $i + 1$ 行的 $n$，满足 $x - y \div z = n!$ 且 $(x - y) \div z = \dfrac{n!}{n}$ 的整数三元组 $(x, y, z)$ 有无限个，则输出一行 `inf`，否则输出满足条件的三元组的数量对 $998244353$ 取模后的结果。
## 样例

### 样例输入 #1
```
3
2
3
4
```
### 样例输出 #1
```
1
3
6
```
## 提示

### 样例 1 解释

样例中的具体三元组如下：

| $n$ | 所有可能的三元组 |
| :----------: | :----------: |
| $2$ | $(2, 0, 2)$ |
| $3$ | $\begin{matrix}(8, 4, 2) & (5, -5, 5) & (6, 0, 3)\end{matrix}$ |
| $4$ | $\begin{matrix}(19, -95, 19) & (21, -21, 7) & (24, 0, 4) \\ (27, 9, 3) & (20, -40, 10) & (36, 24, 2)\end{matrix}$ |

### 数据规模与约定

对于前 $20\%$ 的数据，保证 $T \leq 10$，$n \leq 10$。

对于前 $40\%$ 的数据，保证 $n \leq 10 ^ 3$。

对于另外 $20\%$ 的数据，保证 $T = 1$。

对于 $100\%$ 的数据，保证 $1 \leq T \leq 10 ^ 5$，$1 \leq n \leq 10 ^ 6$。


---

