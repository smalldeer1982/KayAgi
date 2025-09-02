---
title: "[LSOT-2] 笼中鸟"
layout: "post"
diff: 省选/NOI-
pid: P10158
tag: ['线段树', '哈希 hashing']
---
# [LSOT-2] 笼中鸟
## 题目背景

> 「笼中鸟，笼中鸟」
>
> 「笼中有只小小鸟」
>
> 「何时才能出囚笼」
>
> 「黎明时分的夜晚」
>
> 「仙鹤灵龟都滑倒」
>
> 「猜猜身后是何人」
## 题目描述

榎本在 SPHIA 的小黑屋内实验神秘转移装置。

实验体是 $m$ 个长度为 $n$ 的数列，他要在这些数列上验证转移装置是否能够正常运行。

这个转移装置的主要功能是将两个序列的部分交换，也就是说他会选择 $(i,j),[l,r]$，然后将序列 $i$ 的 $[l,r]$ 与序列 $j$ 的 $[l,r]$ 交换。

当然了，为了验证是否成功交换，他会查询某个序列的某个区间的和与预期值是否相同，并且为了避免偶然现象，他会给某个序列的某个区间加上一个值。

榎本知道 self 非常喜欢斐波那契数列，于是为了更好的困住 self，他还加了一个功能，就是判断数列 $f$ 的某个区间是不是满足 $f_i\equiv\sum_{j=1}^kf_{i-j}\pmod p$ 的特殊数列。

形式化题面：

1. 给定 $x,l,r$，求 $\sum_{i=l}^ra_{x,i}\bmod p$。

2. 给定 $x,l,r,f$，询问命题 $\forall i\in[l+f,r],a_{x,i}\equiv \sum_{j=1}^fa_{x,i-j}\pmod p$ 是否是真命题。
3. 给定 $x,l,r,k$，$\forall i\in[l,r],a_{x,i}← a_{x,i}+k$。
4. 给定 $x,y,l,r$，$\forall i\in[l,r],\text{swap}(a_{x,i},a_{y,i})$。

## 输入格式

第一行四个正整数 $n,m,q,p$，$q$ 代表榎本的操作数。

接下来 $m$ 行每行 $n$ 个整数，第 $i$ 行的第 $j$ 个数代表 $a_{i,j}$。

接下来 $q$ 行，每行四个或五个整数。

若输入为 `1 x l r` 则代表对区间 $[l,r]$ 进行一次 $1$ 操作，若输入为 `2 x l r f` 则代表对区间 $[l,r]$ 进行一次 $2$ 操作，若输入为 `3 x l r k` 则代表对区间 $[l,r]$ 进行一次 $3$ 操作，若输入为 `4 x y l r ` 则代表对区间 $[l,r]$ 进行一次 $4$ 操作。
## 输出格式

对于每个 $1$ 操作，一行一个正整数表示答案。

对于每个 $2$ 操作，如果是真命题输出 `where is self?`，否则输出 `infinity loop!`。
## 样例

### 样例输入 #1
```
5 2 6 1000000007
1 1 2 3 5
0 0 0 0 0
1 1 2 3
1 2 2 3
2 1 1 5 2
4 1 2 2 3
1 1 1 4
1 2 1 4
```
### 样例输出 #1
```
3
0
where is self?
4
3
```
## 提示

**「本题采用捆绑测试」**

$\texttt{Subtask 1(20pts)：}n,q\le100$。

$\texttt{Subtask 2(25pts)：}n,q\le10^5$。

$\texttt{Subtask 3(25pts)：}$不存在 $2$ 操作。

$\texttt{Subtask 4(30pts)：}$无特殊性质。

对于所有数据，$1\le n,q\le5\times10^5$，$1\le m\le10$，$0\le a_{i,j},k< p$，$1\le l\le r\le n$，$1\le f\le n$，$1\le x,y\le m$，$x\not=y$。保证 $p$ 是 $10^{9}$ 到 $2\times 10^9$ 中随机生成的质数。



------------
2024/2/13 本题赛后添加两组 hack 数据（Subtask #5）


---

---
title: "[COTS 2023] 下 Niz"
layout: "post"
diff: 省选/NOI-
pid: P10833
tag: ['线段树', '2023', 'O2优化', '分治', '哈希 hashing', 'COCI（克罗地亚）', '单调栈']
---
# [COTS 2023] 下 Niz
## 题目背景


译自 [Izborne Pripreme 2023 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2023/) D2T2。$\texttt{1s,0.5G}$。

祝 NaCly_Fish 生日快乐！（2024.7.28）
## 题目描述


给定长度为 $N$ 的序列 $a$，求满足以下条件的 $(l,r)$ 对数：

- $1\le l\le r\le N$；
- $a_l,a_{l+1},\cdots,a_{r-1},a_r$ 是 $1\sim r-l+1$ 的排列。

## 输入格式


第一行，一个正整数 $N$，表示序列长度；

第二行，$N$ 个正整数，描述序列 $a$。
## 输出格式

一行一个整数，即满足条件的 $(l,r)$ 的数量。
## 样例

### 样例输入 #1
```
3
3 1 2 
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
5
3 2 1 2 3
```
### 样例输出 #2
```
5
```
### 样例输入 #3
```
7
2 1 3 1 2 3 4
```
### 样例输出 #3
```
8
```
## 提示


### 样例解释

样例 $3$ 解释：满足条件的 $(l,r)$ 有 $(2,2),(1,2),(1,3),(4,4),(4,5),(4,6),(4,7),(3,5)$。   

#### 数据范围

对于 $100\%$ 的数据，保证：

- $1\le N\le 10^6$；
- $1\le a_i\le N$。

| 子任务编号 | 分值 | 约束  |
|:-----:|:------:|:-------:|
| $1$  | $13$  | 每个数只在序列中出现一次  |
| $2$  | $20$  | $N\le 5\, 000$  |
| $3$  | $33$  | $N\le 50\, 000$ |
| $4$  | $34$  | 无额外约束 |






---

---
title: "【MX-S6-T3】「KDOI-11」简单的字符串问题 2"
layout: "post"
diff: 省选/NOI-
pid: P11291
tag: ['字符串', '贪心', '倍增', 'Special Judge', 'O2优化', '哈希 hashing', '前缀和', 'KMP 算法', '梦熊比赛']
---
# 【MX-S6-T3】「KDOI-11」简单的字符串问题 2
## 题目背景

原题链接：<https://oier.team/problems/S6C>。
## 题目描述

给定 $n$ 个字符串 $S_1, \ldots, S_n$ 以及一个字符串 $T$。

对于一个字符串 $R$，定义 $|R|$ 表示 $R$ 的长度、$R_{[l,r]}$ 表示 $R$ 的第 $l\sim r$ 个字符组成的字符串。字符串 $R'$ 是字符串 $R$ 的前缀当且仅当存在 $1\leq p\leq |R|$ 且 $p$ 为整数使得 $R'=R_{[1,p]}$。

定义一个字符串 $R$ 是**好的**当且仅当它是某个 $S_i$ 的前缀**或** $R$ **为空**。

对于若干字符串 $R_1,R_2,\dots,R_k$，定义 $R_1+R_2+\dots+R_k$ 为 $R_1,R_2,\dots,R_k$ 顺次拼接得到的字符串。

定义一个三元组 $(l,r,k)$（$l,r,k$ 均为整数）是好的当且仅当 $1\leq l\leq r\leq|T|$，$1\leq k\leq K$ 且存在 $k$ 个**好的**字符串 $R_1,R_2,\dots,R_k$ 使得 $R_1+R_2+\dots+R_k=T_{[l,r]}$。

请你求出好的三元组的数量，并对于每个 $i$ 求出有多少好的三元组 $(l,r,k)$ 满足 $l\leq i\leq r$。如果你只能求出两者中其一，也可以获得部分分数，见【**输出格式**】。
## 输入格式

第一行，三个非负整数 $id,n,K$，其中 $id$ 表示测试点编号（所有样例满足 $id=0$），$n$ 表示字符串数量，$K$ 表示对好的三元组的限制。

接下来 $n$ 行，每行一个字符串 $S_i$。

接下来一行，一个字符串 $T$。
## 输出格式

第一行，一个非负整数，表示好的三元组的数量。

第二行，$\lvert T\rvert$ 个非负整数，第 $i$ 个表示满足 $l\leq i\leq r$ 的好的三元组 $(l,r,k)$ 的数量。

本题使用**自定义校验器**进行评分，对于每个测试点：

* 如果你的程序正确地求出了好的三元组的数量并正确地对于每个 $1\leq i\leq |T|$ 求出了满足 $l\leq i\leq r$ 的好的三元组 $(l,r,k)$ 的数量，你可以获得该测试点 $100\%$ 的分数。
* 如果你的程序未能正确地求出了好的三元组的数量但正确地对于每个 $1\leq i\leq |T|$ 求出了满足 $l\leq i\leq r$ 的好的三元组 $(l,r,k)$ 的数量，你可以获得该测试点 $80\%$ 的分数。
* 如果你的程序正确地求出了好的三元组的数量但未能正确地对于每个 $1\leq i\leq |T|$ 求出了满足 $l\leq i\leq r$ 的好的三元组 $(l,r,k)$ 的数量，你可以获得该测试点 $60\%$ 的分数。
* 否则，你不能获得该测试点的任何分数。

注意，即使你希望获得某测试点 $80\%$ 或 $60\%$ 的分数，你也需要在第一行输出一个数并在第二行输出 $\lvert T\rvert$ 个数。
## 样例

### 样例输入 #1
```
0 1 2
ab
abaab
```
### 样例输出 #1
```
13
5 3 5 6 3
```
### 样例输入 #2
```
0 3 2
abc
ac
b
bacabcab
```
### 样例输出 #2
```
27
4 9 6 11 10 5 6 5
```
### 样例输入 #3
```
0 10 10
wooogpgpoo
owpwgwwp
ooogpgpooo
gppwppgwoo
wooogpgpoo
wowooogpgp
gwwp
ggggogwgpp
wowooogpgp
pgpoooowpw
pgwgwggggggogwgppwppgwooggoogwowooogpgpoooowpwgwwp
```
### 样例输出 #3
```
7698
183 390 577 792 990 1213 1422 1651 1780 1889 1984 2099 2235 2355 2491 2458 2435 2426 2439 2466 2478 2498 2503 2489 2481 2477 2477 2483 2491 2527 2532 2559 2571 2540 2489 2433 2372 2276 2163 2041 1932 1803 1662 1491 1308 1111 900 702 486 252
```
## 提示

**【样例解释 #1】**

符合要求的 $(l,r,k)$ 有以下 $13$ 组：

* $(1,1,1)$；
* $(1,1,2)$；
* $(1,2,1)$；
* $(1,2,2)$；
* $(1,3,2)$；
* $(3,3,1)$；
* $(3,3,2)$；
* $(3,4,2)$；
* $(3,5,2)$；
* $(4,4,1)$；
* $(4,4,2)$；
* $(4,5,1)$；
* $(4,5,2)$。

**【样例 #4】**

见附件中的 `string/string4.in` 与 `string/string4.ans`。

该组样例满足测试点 $1\sim3$ 的约束条件。

**【样例 #5】**

见附件中的 `string/string5.in` 与 `string/string5.ans`。

该组样例满足测试点 $4\sim6$ 的约束条件。

**【样例 #6】**

见附件中的 `string/string6.in` 与 `string/string6.ans`。

该组样例满足测试点 $7\sim10$ 的约束条件。

**【样例 #7】**

见附件中的 `string/string7.in` 与 `string/string7.ans`。

该组样例满足测试点 $13\sim14$ 和测试点 $16\sim17$ 的约束条件。

**【样例 #8】**

见附件中的 `string/string8.in` 与 `string/string8.ans`。

该组样例满足测试点 $18\sim20$ 的约束条件。

**【数据范围】**

对于所有测试数据，保证：$1\leq n\leq10$，$1\leq |S_i|\leq5\times10^4$，$1\leq |T|,K\leq5\times10^5$，字符串仅包含小写英文字母 $\texttt{a}\sim\texttt{z}$。

| 测试点编号 | $n\leq$ | $\lvert S_i\rvert\leq$ |  $\lvert T\rvert\leq$ | $K\leq$ | 特殊性质 |
|:--:|:--:|:--:|:--:|:--:|:--:|
| $1\sim3$ | $10$ | $50$ | $50$ | $50$ | 无 |
| $4\sim6$ | $10$ | $100$ | $300$ | $300$ | 无 |
| $7\sim10$ | $10$ | $1000$ | $5000$ | $5000$ | 无 |
| $11\sim12$ | $10$ | $5\times10^4$ | $5\times10^5$ | $1$ | 无 |
| $13\sim14$ | $10$ | $5\times10^4$ | $5\times10^5$ | $10$ | 无 |
| $15$ | $10$ | $5\times10^4$ | $5\times10^5$ | $5\times10^5$ | 所有字符均为 $\texttt{a}$ |
| $16\sim17$ | $10$ | $5\times10^4$ | $5\times10^5$ | $5\times10^5$ | 所有字符在 $\{\texttt{a},\texttt{b}\}$ 中独立均匀随机生成 |
| $18\sim20$ | $10$ | $5\times10^4$ | $5\times10^5$ | $5\times10^5$ | 无 |


---

---
title: "[COTS 2016] 删除 Brisanje"
layout: "post"
diff: 省选/NOI-
pid: P11305
tag: ['2016', '二分', '哈希 hashing', '后缀数组 SA', 'COCI（克罗地亚）']
---
# [COTS 2016] 删除 Brisanje
## 题目背景


译自 [Izborne Pripreme 2016 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2016/) D1T2。$\texttt{4s,0.5G}$。


为了卡掉理论复杂度较劣的解法，在 Subtask 0 添加了 Hack 数据（#35~#39，感谢 @Hoks 和 @N_z_），同时将时限改为 1.5s。欢迎对数据的加强。

## 题目描述


给定字符串 $s$。

定义 $s(l,r)$ 为 $s$ 第 $l\sim r$ 个字符组成的字符串。

定义 $t(l,r)$ 为 $s$ 删除第 $l\sim r$ 个字符后得到的字符串。

找到最长的区间 $[l,r]$，使得 $s(l,r)$ 在 $t(l,r)$ 中作为子串出现。

## 输入格式

一行一个字符串 $s$。

## 输出格式

输出一个整数，表示最长可能的区间长度。  

## 样例

### 样例输入 #1
```
abcxyzabc

```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
bbcdbcbbcbadadda
```
### 样例输出 #2
```
5
```
## 提示


#### 样例解释

不难注意到 $\texttt{bbcdbcb\underline{bcbad}adda} \to \texttt{bbcd\underline{bcbad}da}$。

#### 数据范围

对于 $100\%$ 的数据，保证：

- $1\le |s| \le 10^5$；
- $s$ 中只有小写字母。


| 子任务编号 | $\vert s\vert \in $ | 得分 |  
| :--: | :--: | :--: | 
| $ 1 $    | $ [1,400] $    |   $ 16 $   |  
| $ 2 $    | $ (400,5000] $   |  $ 24 $   |  
| $ 3 $    | $ (5000,10^5]$ | $ 60 $   |  




---

---
title: "时空轮回"
layout: "post"
diff: 省选/NOI-
pid: P11471
tag: ['O2优化', '哈希 hashing', '离线处理']
---
# 时空轮回
## 题目描述

在时空中有 $n$ 个**时空节点**，有 $n-1$ 条时空通道将所有时空节点连接成一个连通块，每条时空通道连接着两个时空节点。

你初始在 $1$ 号时空节点，你每次可以选择一条时空通道来穿梭到另一个时空节点，由于时空穿梭的特殊性，每条时空通道至多通过一次。

每个时空节点有一个**风景**，第 $i$ 个时空节点的风景为 $a_i$。一段**风景序列**由若干个风景构成，一个长度为 $k$ 的风景序列为 $a_{i_1}a_{i_2}\dots a_{i_k}$。你可以通过若干次时空穿梭经过若干时空节点，这些时空节点按照经过顺序构成了一个风景序列，记这个风景序列为**重现的风景**。

定义一个风景序列 A 在风景序列 B 中的出现次数为：最多将风景序列 B 分为多少个连续且不相交的部分，使得风景序列 A 是每个部分的**子串**。

你有 $q$ 段**留恋的风景**，每段留恋的风景是一个风景序列，记第 $i$ 段留恋的风景为 $s_i$，其长度为 $m_i$，记 $s_i$ 中的第 $j$ 个风景为 $s_{i,j}$。对于每段留恋的风景，你都需要从 $1$ 号时空节点出发进行时空穿梭，得到重现的风景，你需要求出该留恋的风景在重现的风景中的出现次数的最大值。

注：

- 每段留恋的风景所对应的重现的风景相互独立。
- 原序列中任意个连续的数字组成的序列称为该序列的子串。
## 输入格式

**本题有多组数据**。

第一行一个正整数 $T$，表示数据组数。

对于每组数据：

第一行 $2$ 个正整数 $n,q$。

第二行 $n$ 个正整数，第 $i$ 个正整数表示 $a_i$。

接下来 $n-1$ 行每行两个正整数 $u,v$，表示 $u$ 和 $v$ 之间存在一条时空通道。

接下来 $q$ 行，每行先输入一个正整数 $m_i$，然后输入 $m_i$ 个正整数，表示 $s_i$。
## 输出格式

对于每组数据：

输出 $q$ 行，表示每段留恋的风景对应的答案。
## 样例

### 样例输入 #1
```
2
8 8
1 2 8 1 1 2 2 1
1 2
1 3
2 4
2 5
2 6
4 7
4 8
1 1
2 1 1
2 1 2
2 2 1
2 2 2
3 1 2 2
4 1 2 2 1
2 1 8
5 2
1 2 1 2 1
1 2
2 3
3 4
4 5
3 1 2 1
2 1 1
```
### 样例输出 #1
```
3
1
2
1
1
1
0
1
1
0

```
## 提示

$1\le T\le10^5$，$1\le n,q,m_i\le10^5$，$1\le a_i,s_{i,j},u,v\le n$，$\sum n,\sum q,\sum m_i\le10^5$。

**注意本题不寻常的时空限制**。


---

---
title: "[PumpkinOI Round 1] 造树据"
layout: "post"
diff: 省选/NOI-
pid: P11618
tag: ['2025', 'Special Judge', 'O2优化', '树形 DP', '哈希 hashing', '洛谷比赛']
---
# [PumpkinOI Round 1] 造树据
## 题目背景

> 拍上了，舒服。
## 题目描述

小 P 正在造数据对拍，可是他拍了 $114514$ 组都没有拍出来。他去请教大佬，但被大佬 D 了，他被告知他随机生成树的期望高度是 $O(\log n)$ 的，强度不够。

小 P 很难过，以至于无法思考。所以他想请问你，对于他给出的任意一棵**无根树**，以他的随机生成方式，生成出与其形态相同的树即与其**同构**的树的概率。

小 P 随机生成一棵**无根树**的方式为：

- 对于 $2\le i\le n$ 的结点，等概率向 $[1,i-1]$ 中连一条边 
## 输入格式

第一行输入一个正整数 $n$。

接下来 $2$ 至 $n$ 行，每行输入两个正整数 $u,v$，表示在 $u$ 和 $v$ 之间连一条边。

保证输入的数据是一棵树。
## 输出格式

输出一行一个非负整数，表示概率对 $998244353$ 取模的值。
## 样例

### 样例输入 #1
```
3
1 3
2 3
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
5
5 3
2 3
1 4
4 3
```
### 样例输出 #2
```
83187030
```
### 样例输入 #3
```
5
1 3
4 1
2 4
3 5
```
### 样例输出 #3
```
332748118
```
## 提示

**本题采用子任务捆绑/依赖**

对于 $10\%$ 的数据，保证 $2\le n\le 10$。

对于 $30\%$ 的数据，保证 $2\le n\le 20$。

对于 $50\%$ 的数据，保证 $2\le n\le 10^3$。

对于另外 $10\%$ 的数据，保证给出的是一条链。

对于另外 $10\%$ 的数据，保证给出的树按照题面中小 P 随机生成树的方式生成。

对于 $100\%$ 的数据，$2\le n\le 5\times 10^5$。



---

---
title: "[NHSPC 2023] A. 演化樹分析"
layout: "post"
diff: 省选/NOI-
pid: P11902
tag: ['2023', 'O2优化', '树形 DP', '哈希 hashing', '台湾']
---
# [NHSPC 2023] A. 演化樹分析
## 题目描述

彼得是一位生物學家。有次他在兩筆資料中分析同一群現存物種集合 $\Sigma = \{1, 2, \ldots, n\}$ 間的演化關係，卻得到了不太一樣的演化樹，想知道這兩棵演化樹的類似程度。

一棵演化樹 $T$ 是一棵無向無根樹 (undirected, unrooted tree)，其中葉節點為現存物種 $1, 2, \ldots, n$，其他節點則為已滅絕物種。設 $v \in V(T)$，我們用 $\deg(v)$ 來表示與節點 $v$ 相鄰的節點個數。在一棵演化樹中，每個代表已滅絕物種的節點 $v$ 均有 $\deg(v) \ge 3$。對於一個現存物種的子集合 $X \subseteq \Sigma$，我們用 $T\{X\}$ 來代表 $X$ 中的現存物種在 $T$ 上的演化關係所形成的「演化子樹」，建構方式如下：

1. 對所有 $X$ 中的任兩點，標記其在 $T$ 上的簡單路徑，並將所有不在 $X$ 且未被標記的點刪除以得到 $T'$。
1. 從 $T'$ 中不斷刪除滿足 $\deg(v) = 2$ 的非葉節點 $v$ 以得到 $T\{X\}$：將與 $v$ 連結的兩條邊合併成一條，並移除 $v$。

以下圖的演化樹 $T$ 為例。$T$ 裡的現存物種集合為 $\Sigma = \{1, 2, 3, 4, 5\}$，若取 $X = \{3, 4, 5\}$，則經步驟 $1$ 後會得到 $T'$，再經過步驟 $2$ 後會得到 $T\{X\}$。注意當 $X = \emptyset$ 時，根據定義我們有 $T\{X\} = \emptyset$。

![](https://cdn.luogu.com.cn/upload/image_hosting/c2xg13m0.png)

從一棵演化樹 $T$ 中移除大小為 $k \ge 0$ 的任意邊集合 $K$，可以得到 $k+1$ 棵子樹 $T^{(1)}, T^{(2)}, \ldots, T^{(k+1)}$，其中每棵子樹 $T^{(i)}$ 上的物種在 $T$ 中的演化關係都會構成一棵**演化子樹**，我們稱它們為從 $T$ 中移除 $K$ 所導出的**演化森林**。注意我們有

1. $T$ 自身為移除 $\emptyset$ 後導出的演化森林。
1. 若一棵子樹 $T^{(i)}$ 上沒有任何現存物種，對應的演化子樹為空。

以上圖中的 $T$ 為例，移除 $K = \{(1, 7), (7, 8), (2, 8), (5, 8)\}$ 四條邊可以得到五棵子樹 $T^{(1)}, T^{(2)}, \ldots, T^{(5)}$，接著導出演化森林：

![](https://cdn.luogu.com.cn/upload/image_hosting/10jt4cii.png)

比較兩座現存物種相同的演化森林時，我們只關注現存物種間的關係，因此已滅絕物種（即非葉節點）的編號並不重要。設 $F_1$ 與 $F_2$ 為兩座現存物種相同的演化森林，若移除它們的非葉節點編號後變得完全相同，我們就稱 $F_1$ 與 $F_2$ 類似。更精確地說，我們稱 $F_1$ 與 $F_2$ 類似，若且唯若存在某個一對一函數 $\Phi: V(F_1) \to V(F_2)$，滿足

1. 對任意 $u \in \Sigma = \{1, 2, \ldots, n\}$，我們有 $\Phi(u) = u$。
1. 對任意 $u, v \in V(F_1)$，我們有
$$(u, v) \in E(F_1) \iff (\Phi(u), \Phi(v)) \in E(F_2).$$

以下圖為例，如果將 $T_1, T_2, T_3$ 的非葉節點編號都移除，會發現 $T_1$ 與 $T_2$ 不類似，而 $T_2$ 與 $T_3$ 類似。

![](https://cdn.luogu.com.cn/upload/image_hosting/8vu59rjm.png)

設 $T_1$ 與 $T_2$ 為現存物種相同的兩棵演化樹。若存在從 $T_1$ 與 $T_2$ 中各刪除 $k$ 條邊的方法，使得兩者導出的演化森林類似，則稱 $T_1$ 與 $T_2$ 的差異不大於 $k$，而滿足此條件的最小整數 $k^*$ 稱為 $T_1$ 與 $T_2$ 的**差異數**。如上圖中 $T_2$ 與 $T_3$ 的差異數為 $0$，而 $T_1$ 與 $T_2$ 的差異數為 $1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/scjhebou.png)

從 $T_1$ 與 $T_2$ 各刪除 $1$ 條邊 | 導出了類似的演化森林

設從 $T_1$ 與 $T_2$ 中刪除的邊集合分別為 $K_1$ 與 $K_2$，兩種刪除方法被視為不同若且唯若 $K_1$ 不同或 $K_2$ 不同。現給定兩棵物種集合均為 $\Sigma$ 的演化樹 $T_1, T_2$ 以及一個整數上限 $k$，彼得想知道它們的差異數 $k^*$ 是否不大於 $k$；如果 $1 \le k^* \le k$，彼得也想知道有多少種從 $T_1$ 和 $T_2$ 中各刪除 $k^*$ 條邊的方法，可以使它們導出類似的演化森林。
## 输入格式

> $n$ $m_1$ $m_2$ $k$   
> $u_1$ $v_1$   
> $u_2$ $v_2$   
> $\vdots$   
> $u_{n+m_1-1}$ $v_{n+m_1-1}$   
> $u_1'$ $v_1'$   
> $u_2'$ $v_2'$   
> $\vdots$   
> $u_{n+m_2-1}'$ $v_{n+m_2-1}'$

* $n$ 代表現存物種集合 $\Sigma = \{1, 2, \ldots, n\}$ 的大小。
* $m_1$ 代表在 $T_1$ 中已滅絕物種（以 $n+1, n+2, \ldots, n+m_1$ 表示）的數量。
* $m_2$ 代表在 $T_2$ 中已滅絕物種（以 $n+1, n+2, \ldots, n+m_2$ 表示）的數量。
* $k$ 代表彼得設定的上限。
* $u_i, v_i$ 代表 $T_1$ 有一條邊從 $u_i$ 連接到 $v_i$。
* $u_i', v_i'$ 代表 $T_2$ 有一條邊從 $u_i'$ 連接到 $v_i'$。
## 输出格式

如果 $k^* = 0$，請輸出

> $0$

如果 $1 \le k^* \le k$，請輸出

> $k^*$  
> $S$

其中 $S$ 為一整數，代表從 $T_1$ 與 $T_2$ 中各刪除 $k^*$ 條邊後導出的演化森林類似的刪除方法數。如果 $k^* > k$，請輸出

> $-1$
## 样例

### 样例输入 #1
```
5 3 3 2
1 7
2 8
3 6
4 6
5 8
6 7
7 8
1 6
2 8
3 6
4 7
5 8
6 7
7 8
```
### 样例输出 #1
```
1
4
```
### 样例输入 #2
```
4 2 2 0
1 5
2 5
3 6
4 6
5 6
1 6
2 6
3 5
4 5
5 6
```
### 样例输出 #2
```
0
```
### 样例输入 #3
```
6 3 3 2
1 7
2 7
3 7
4 8
5 9
6 9
7 8
8 9
1 7
2 7
3 9
4 9
5 8
6 8
7 8
8 9
```
### 样例输出 #3
```
2
9
```
### 样例输入 #4
```
6 1 4 2
1 7
2 7
3 7
4 7
5 7
6 7
1 7
2 7
3 8
4 8
5 9
6 9
7 10
8 10
9 10
```
### 样例输出 #4
```
-1
```
## 提示

### 測資限制

* $n \ge 2$。
* $0 \le m_1 \le 300-n$。
* $0 \le m_2 \le 300-n$。
* $k \in \{0, 1, 2\}$。
* $1 \le u_i \le n+m_1$。
* $1 \le v_i \le n+m_1$。
* $1 \le u_i' \le n+m_2$。
* $1 \le v_i' \le n+m_2$。
* 給定的 $T_1$ 與 $T_2$ 保證連通，且
  1. 若 $u \in \{1, 2, \ldots, n\}$，則在 $T_1$ 與 $T_2$ 中 $\deg(u) = 1$。
  1. 若 $u \in \{n+1, n+2, \ldots, n+m_1\}$，則在 $T_1$ 中 $\deg(u) \ge 3$。
  1. 若 $u \in \{n+1, n+2, \ldots, n+m_2\}$，則在 $T_2$ 中 $\deg(u) \ge 3$。
* 輸入的數皆為整數。

### 評分說明

本題共有四組子任務，條件限制如下所示。
每一組可有一或多筆測試資料，該組所有測試資料皆需答對才會獲得該組分數。

|  子任務  |  分數  | 額外輸入限制 |
| :------: | :----: | ------------ |
| 1 | $21$ | $k = 0$ |
| 2 | $13$ | $k \in \{0, 1\}$ |
| 3 | $23$ | $n+m_1 \le 30$ 且 $n+m_2 \le 30$ |
| 4 | $43$ | 無額外限制 |


---

---
title: "[GCJ 2021 Finals] Slide Circuits"
layout: "post"
diff: 省选/NOI-
pid: P13044
tag: ['图论', '2021', '哈希 hashing', 'Google Code Jam']
---
# [GCJ 2021 Finals] Slide Circuits
## 题目描述

Gooli is a huge company that owns $\mathbf{B}$ buildings in a hilly area. Five years ago, Gooli built slides that allowed employees to go from one building to another (they are not bidirectional), starting a tradition of building slides between buildings. Currently, $\mathbf{S}$ slides exist.

Melek is Gooli's Head of Transportation and a problem-solving enthusiast. She was tasked with keeping the slides enjoyable to use. The idea she came up with was disabling some slides such that only circuits remained. A circuit is a set of two or more buildings $b_{1}, b_{2}, \ldots, b_{k}$ such that there is exactly one slide enabled from building $b_{i}$ to building $b_{i+1}$, for each $i$, and exactly one slide enabled from building $b_{k}$ to building $b_{1}$. No other slides from or to any of those buildings should be enabled, to prevent misdirection. A state of the slides is then called fun if each building belongs to exactly one circuit.

Slides in Gooli's campus are numbered with integers between 1 and $\mathbf{S}$, inclusive. Melek created a slide controlling console that supports two operations: enable and disable. Both operations receive three parameters $\ell, r$, and $m$ and perform the operation on each slide $x$ such that $\ell \leq x \leq r$ and $x$ is a multiple of $m$. An enable operation is valid only if all affected slides are in a disabled state right before the operation is performed. Similarly, a disable operation is valid only if all affected slides are in an enabled state right before the operation is performed.

The following picture illustrates a possible succession of states and operations. The layout has 3 buildings and 3 slides. Slides are light grey when disabled and dark grey when enabled.

![](https://cdn.luogu.com.cn/upload/image_hosting/9vcfdd3y.png)

1. Initial state. All sides are disabled.
2. After enable operation with $\ell=1$, $r=2$, and $m=1$.
3. After enable operation with $\ell=3$, $r=3$, and $m=1$.
4. After disable operation with $\ell=1, r=3$, and $m=2$.
5. After disable operation with $\ell=1, r=3$, and $m=3$.
6. After enable operation with $\ell=1, r=2$, and $m=2$.

Unfortunately, Sult, Melek's cat, found the console and started performing several valid enable and disable operations. After every console operation performed by Sult, Melek wants to know if the state of the slides can be made fun by enabling exactly one currently disabled slide. Note that Melek does not actually enable this slide.

In the picture above, we can see that after the first, third, and last operations, Melek could enable the only disabled slide and get to a fun state. After the second operation, there are two issues. One issue is that there are no currently disabled slides, so Melek cannot enable any. Additionally, the state is already fun, so even if there were additional disabled slides, enabling anything would result in a not fun state. After the fourth operation, there are two disabled slides, but enabling either would not yield a fun state.

All slides are initially disabled, then Sult performs its operations one at a time. After each of Sult's operations, determine which disabled slide, if any, Melek can enable to put the slides in a fun state.
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case starts with a line containing three integers $\mathbf{B}$, $\mathbf{S}$, and $\mathbf{N}$: the number of buildings, slides, and operations to process, respectively. Then, $\mathbf{S}$ lines follow. The $i$-th of these lines contains two integers $\mathbf{X}_{i}$ and $\mathbf{Y}_{i}$, indicating that the slide with number $i$ goes from building $\mathbf{X}_{i}$ to building $\mathbf{Y}_{i}$. Finally, $\mathbf{N}$ lines represent the operations. The $j$-th of these lines contains a character $\mathbf{A}_{j}$ and three integers $\mathbf{L}_{j}, \mathbf{R}_{j}$, and $\mathbf{M}_{j}$, describing the $j$-th operation. $\mathbf{A}_{j}$ describes the type of operation using an uppercase $\mathbf{E}$ for enable and an uppercase $\mathbf{D}$ for disable. The operation is to be performed on slides with numbers that are simultaneously a multiple of $\mathbf{M}_{j}$ and between $\mathbf{L}_{j}$ and $\mathbf{R}_{j}$, inclusive.
## 输出格式

For each test case, output one line containing `Case #x:` $y_{1}\ y_{2}\ \ldots\ y_{N}$, where $x$ is the test case number (starting from 1) and $y_{j}$ is an uppercase $\mathbf{X}$ if there is no way to turn the state of slides created by the first $j$ console operations into a fun state by enabling exactly one disabled slide. Otherwise, $y_{j}$ should be an integer representing that enabling the $y_{j}$-th slide would turn the state created by the first $j$ console operations into a fun state.
## 样例

### 样例输入 #1
```
2
3 3 5
1 2
2 3
3 1
E 1 2 1
E 3 3 1
D 1 3 2
D 1 3 3
E 1 2 2
5 8 10
1 5
5 3
4 1
3 2
2 4
2 5
2 1
1 4
E 1 8 2
D 4 8 2
E 3 5 1
E 1 1 3
E 1 1 1
E 5 8 2
D 1 8 3
D 5 8 4
D 4 5 1
E 3 4 1
```
### 样例输出 #1
```
Case #1: 3 X 2 X 3
Case #2: 3 X 1 1 X X X 3 X 5
```
## 提示

**Sample Explanation**

Sample Case #1 is the one depicted in the problem statement.

The following picture shows the building and slide layout of Sample Case #2.

![](https://cdn.luogu.com.cn/upload/image_hosting/gc127wx5.png)

The sets of enabled slides after each operation are:

- $\{2,4,6,8\}$,
- $\{2\}$,
- $\{2,3,4,5\}$,
- $\{2,3,4,5\}$,
- $\{1,2,3,4,5\}$,
- $\{1,2,3,4,5,6,8\}$,
- $\{1,2,4,5,8\}$,
- $\{1,2,4,5\}$,
- $\{1,2\}$, and
- $\{1,2,3,4\}$.

**Limits**

- $1 \leq \mathbf{X}_{i} \leq \mathbf{B}$, for all $i$.
- $1 \leq \mathbf{Y}_{i} \leq \mathbf{B}$, for all $i$.
- $\mathbf{X}_{i} \neq \mathbf{Y}_{i}$, for all $i$.
- $\left(\mathbf{X}_{i}, \mathbf{Y}_{i}\right) \neq\left(\mathbf{X}_{j}, \mathbf{Y}_{j}\right)$, for all $i \neq j$.
- $\mathbf{A}_{j}$ is either uppercase $\mathbf{E}$ or uppercase $\mathbf{D}$, for all $j$.
- $1 \leq \mathbf{L}_{j} \leq \mathbf{R}_{j} \leq \mathbf{S}$, for all $j$.
- $1 \leq \mathbf{M}_{j} \leq \mathbf{S}$, for all $j$.
- Each operation is valid.

**Test Set 1 (10 Pts, Visible Verdict)**

- Time limit: 10 seconds.
- $1 \leq \mathbf{T} \leq 100$.
- $2 \leq \mathbf{B} \leq 100$.
- $2 \leq \mathbf{S} \leq 1000$.
- $1 \leq \mathbf{N} \leq 1000$.

**Test Set 2 (20 Pts, Hidden Verdict)**

- Time limit: 120 seconds.
- $1 \leq \mathbf{T} \leq 30$.
- $2 \leq \mathbf{B} \leq 3 \times 10^{4}$.
- $2 \leq \mathbf{S} \leq 3 \times 10^{5}$.
- $1 \leq \mathbf{N} \leq 3 \times 10^{5}$.


---

---
title: "[GCJ 2014 Finals] Symmetric Trees"
layout: "post"
diff: 省选/NOI-
pid: P13266
tag: ['模拟', '2014', '树形 DP', '哈希 hashing', 'Google Code Jam']
---
# [GCJ 2014 Finals] Symmetric Trees
## 题目描述

Given a vertex-colored tree with $\mathrm{N}$ nodes, can it be drawn in a 2D plane with a line of symmetry?

Formally, a tree is line-symmetric if each vertex can be assigned a location in the 2D plane such that:

* All locations are distinct.
* If vertex $\mathbf{v}_{\mathrm{i}}$ has color $\mathbf{C}$ and coordinates $\left(\mathrm{x}_{\mathrm{i}}, \mathrm{y}_{\mathrm{i}}\right)$, there must also be a vertex $\mathbf{v}_{\mathrm{i}}^{\prime}$ of color $\mathbf{C}$ located at $\left(-\mathrm{x}_{\mathrm{i}}, \mathrm{y}_{\mathrm{i}}\right)$ -- Note if $\mathrm{x}_{\mathrm{i}}$ is 0, $\mathbf{v}_{\mathrm{i}}$ and $\mathbf{v}_{\mathrm{i}}^{\prime}$ are the same vertex.
* For each edge $\left(\mathbf{v}_{\mathrm{i}}, \mathbf{v}_{\mathrm{j}}\right)$, there must also exist an edge $\left(\mathbf{v}_{\mathrm{i}}^{\prime}, \mathbf{v}_{\mathrm{j}}^{\prime}\right)$.
* If edges were represented by straight lines between their end vertices, no two edges would share any points except where adjacent edges touch at their endpoints.
## 输入格式

The first line of the input gives the number of test cases, $\mathrm{T}$. $\mathrm{T}$ test cases follow.

Each test case starts with a line containing a single integer $\mathrm{N}$, the number of vertices in the tree.

$\mathrm{N}$ lines then follow, each containing a single uppercase letter. The $\mathrm{i}$-th line represents the color of the $\mathrm{i}$-th node.

$\mathrm{N}-1$ lines then follow, each line containing two integers $\mathrm{i}$ and $\mathrm{j}(1 \leq \mathrm{i}<\mathrm{j} \leq \mathrm{N})$. This denotes that the tree has an edge from the $\mathrm{i}$-th vertex to the $\mathrm{j}$-th vertex. The edges will describe a connected tree.
## 输出格式

For each test case, output one line containing "Case #x: y", where $\mathrm{x}$ is the case number (starting from 1) and $\mathrm{y}$ is "SYMMETRIC" if the tree is line-symmetric by the definition above or "NOT SYMMETRIC" if it isn't.
## 样例

### 样例输入 #1
```
3
4
R
G
B
B
1 2
2 3
2 4
4
R
G
B
Y
1 2
2 3
2 4
12
Y
B
Y
G
R
G
Y
Y
B
B
B
R
1 3
1 9
1 10
2 3
3 7
3 8
3 11
4 8
5 7
6 7
8 12
```
### 样例输出 #1
```
Case #1: SYMMETRIC
Case #2: NOT SYMMETRIC
Case #3: SYMMETRIC
```
## 提示

**Sample Explanation**

The first case can be drawn as follows:

![](https://cdn.luogu.com.cn/upload/image_hosting/ithqougs.png)

No arrangement of the second case has a line of symmetry:

![](https://cdn.luogu.com.cn/upload/image_hosting/0kmct7ap.png)

One way of drawing the third case with a symmetry line is as follows:

![](https://cdn.luogu.com.cn/upload/image_hosting/9yzlvp9q.png)

**Limits**

- $1 \leq T \leq 100$

**Small dataset(7 Pts)**

- Time Limit: ~~60~~ 3 seconds
- $2 \leq N \leq 12$

**Large dataset(18 Pts)**

- Time Limit: ~~120~~ 5 seconds
- $2 \leq N \leq 10000$


---

---
title: "[GCPC 2024] Headline Heat"
layout: "post"
diff: 省选/NOI-
pid: P13723
tag: ['2024', '哈希 hashing', 'AC 自动机', 'ICPC']
---
# [GCPC 2024] Headline Heat
## 题目描述

The German ICPC scene is widely considered one of the most competitive.
At least, that's what we tell our students.
Countless rivalries form a complex web of envy, despair, glory, and triumph woven around and manifested in the unrelenting echoes of two scoreboards -- Winter Contest and GCPC.
While generations of participants tend to forget the grudges of their predecessors, we coaches, acting as timeless beacons of continuity, preserve these petty conflicts between long forgotten teams.
Striving for perfect balance, we express our dedication to our coaching duties in a furious outcry on social media against every unfair news article.
That is, a coach gets mad if a news article is published that contains a rival university name more often than their own.

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/81caxzmt.png)

Top 10 scoreboard of Winter Contest 2024.
:::


To smoothen the waves of conflict in this ocean of rage, a newly appointed authority is tasked with proofreading media coverage of GCPC and Winter Contest to prevent uneven coverage.
## 输入格式

The input consists of:
- One line with the number of universities $n$, rivalries $m$, and articles $k$. \\
    ($1\leq n,m,k\leq 10^5$)
- $n$ lines containing the name of a university $p_i$.
- $m$ lines containing two integers $u,v$, meaning that universities $u$ and $v$ are rivals. \\
    ($1\leq u,v \leq n, u\neq v$)
- $k$ lines containing a news article $t_i$.

If a university $u$ is a rival of university $v$, then $v$ is also a rival of $u$. Moreover, there are no duplicate rivalries.

Names and articles are strings of lowercase Latin letters and spaces.
The first and last character of a name or article are never a space.
Names can overlap and be contained in other names.

The summed length of all names and articles is at most $10^6$, i.e. $\sum_{i=1}^{n} |p_i| + \sum_{i=1}^{k} |t_i| \leq 10^6$.
## 输出格式

For each article, output "$\texttt{no}$" if it will draw the wrath of at least one coach and "$\texttt{yes}$" otherwise.
## 样例

### 样例输入 #1
```
3 1 4
hpi
fau
kit
1 3
kit destroys hpi at wintercontest
gcpc is great
team moshpit from hpi beats kit teams
whats the abbreviation for university of erlangen nuremberg
```
### 样例输出 #1
```
yes
yes
no
yes
```
### 样例输入 #2
```
6 3 5
uds
cu
tum
rwth
uni ulm
uni
4 1
2 5
1 3
last gcpc rwth had a team in top ten two places behind tum
who is team debuilding from constructor university bremen
top ten teams last year are from kit cu uds hpi tum and rwth
uni ulm cu uni ulm
sunday alright lets go
```
### 样例输出 #2
```
no
yes
no
no
yes
```


---

---
title: "[ZJOI2006] GameZ游戏排名系统"
layout: "post"
diff: 省选/NOI-
pid: P2584
tag: ['2006', '平衡树', '浙江', 'O2优化', '哈希 hashing']
---
# [ZJOI2006] GameZ游戏排名系统
## 题目描述

GameZ为他们最新推出的游戏开通了一个网站。世界各地的玩家都可以将自己的游戏得分上传到网站上。这样就可以看到自己在世界上的排名。得分越高，排名就越靠前。当两个玩家的名次相同时，先上传记录者优先。由于新游戏的火爆，网站服务器已经难堪重负。为此GameZ雇用了你来帮他们重新开发一套新的核心。

排名系统通常要应付三种请求：上传一条新的得分记录、查询某个玩家的当前排名以及返回某个区段内的排名记录。当某个玩家上传自己最新的得分记录时，他原有的得分记录会被删除。为了减轻服务器负担，在返回某个区段内的排名记录时，最多返回 $10$ 条记录。

## 输入格式

输入文件的第一行是一个整数 $n$ $( n \ge 10 )$ 表示请求总数目。接下来n行每行包含了一个请求。请求的具体格式如下：

``+Name Score`` 上传最新得分记录。``Name`` 表示玩家名字，由大写英文字母组成，不超过 $10$ 个字符。``Score`` 为最多 $10$ 位的正整数。

``?Name`` 查询玩家排名。该玩家的得分记录必定已经在前面上传。

``?Index`` 返回自第 ``Index`` 名开始的最多 $10$ 名玩家名字。``Index`` 必定合法，即不小于 $1$，也不大于当前有记录的玩家总数。



## 输出格式

对于每条查询请求，在文件中输出相应结果。

对于 ``?Name`` 格式的请求，应输出一个整数表示该玩家当前的排名。

对于 ``?Index`` 格式的请求，应在一行中依次输出从第 ``Index`` 名开始的最多 $10$ 名玩家姓名，用一个空格分隔。

## 样例

### 样例输入 #1
```
20
+ADAM 1000000
+BOB 1000000 
+TOM 2000000
+CATHY 10000000
?TOM 
?1
+DAM 100000 
+BOB 1200000
+ADAM 900000 
+FRANK 12340000 
+LEO 9000000
+KAINE 9000000 
+GRACE 8000000 
+WALT 9000000 
+SANDY 8000000 
+MICK 9000000 
+JACK 7320000 
?2 
?5  
?KAINE
```
### 样例输出 #1
```
2
CATHY TOM ADAM BOB
CATHY LEO KAINE WALT MICK GRACE SANDY JACK TOM BOB
WALT MICK GRACE SANDY JACK TOM BOB ADAM DAM
4

```
## 提示

20
+ADAM 1000000     加入ADAM的得分记录

+BOB 1000000       加入BOB的得分记录

+TOM 2000000       加入TOM的得分记录

+CATHY 10000000    加入CATHY的得分记录

?TOM               输出TOM目前排名

?1                  目前有记录的玩家总数为4，因此应输出第1名到第4名。

+DAM 100000        加入DAM的得分记录

+BOB 1200000       更新BOB的得分记录

+ADAM 900000      更新ADAM的得分记录（即使比原来的差）

+FRANK 12340000   加入FRANK的得分记录

+LEO 9000000       加入LEO的得分记录

+KAINE 9000000     加入KAINE的得分记录

+GRACE 8000000    加入GRACE的得分记录

+WALT 9000000      加入WALT的得分记录

+SANDY 8000000    加入SANDY的得分记录

+MICK 9000000      加入MICK的得分记录

+JACK 7320000      加入JACK的得分记录

?2                  目前有记录的玩家总数为12，因此应输出第2名到第11名。

?5                  输出第5名到第13名。

?KAINE             输出KAINE的排名

输入文件总大小不超过 2M。

NOTE：用 C++ 的 fstream 读大规模数据的效率较低


---

---
title: "[ZJOI2009] 对称的正方形"
layout: "post"
diff: 省选/NOI-
pid: P2601
tag: ['2009', '二分', '各省省选', '浙江', '哈希 hashing']
---
# [ZJOI2009] 对称的正方形
## 题目描述

Orez 很喜欢搜集一些神秘的数据，并经常把它们排成一个矩阵进行研究。最近，Orez 又得到了一些数据，并已经把它们排成了一个 $n$ 行 $m$ 列的矩阵。通过观察，Orez 发现这些数据蕴涵了一个奇特的数，就是矩阵中上下对称且左右对称的正方形子矩阵的个数。Orez 自然很想知道这个数是多少，可是矩阵太大，无法去数。只能请你编个程序来计算出这个数。

## 输入格式

文件的第一行为两个整数 $n$ 和 $m$。接下来 $n$ 行每行包含 $m$ 个正整数，表示 Orez 得到的矩阵。

## 输出格式

文件中仅包含一个整数 $ans$，表示矩阵中有 $ans$ 个上下左右对称的正方形子矩阵。

## 样例

### 样例输入 #1
```
5 5

4 2 4 4 4 

3 1 4 4 3 

3 5 3 3 3 

3 1 5 3 3 

4 2 1 2 4 
```
### 样例输出 #1
```
27
```
## 提示

- 对于 $30\%$ 的数据 $1\le n,m\le 100$；
- 对于 $100\%$ 的数据 $1\le n,m\le 1000$，矩阵中的数的大小不超过 $10^9$。



---

---
title: "[国家集训队] 等差子序列"
layout: "post"
diff: 省选/NOI-
pid: P2757
tag: ['线段树', 'O2优化', '哈希 hashing']
---
# [国家集训队] 等差子序列
## 题目描述

给一个 $1$ 到 $N$ 的排列 $\{A_i\}$，询问是否存在

$$1 \le p_1<p_2<p_3<p_4<p_5<…<p_{Len} \le N (Len \ge 3)$$

使得 $Ap_1,Ap_2,Ap_3,\cdots,Ap_{Len}$ 是一个等差序列。

## 输入格式

输入的第一行包含一个整数 $T$，表示组数。

下接 $T$ 组数据，每组第一行一个整数 $N$，每组第二行为一个 $1$ 到 $N$ 的排列，数字两两之间用空格隔开。

## 输出格式

对于每组数据，如果存在一个等差子序列，则输出一行 Y，否则输出一行 N。

## 样例

### 样例输入 #1
```
2
3
1 3 2
3
3 2 1
```
### 样例输出 #1
```
N
Y
```
## 提示

对于后 $20$ 个测试点的数据，$1 \leq N \leq10000,T\leq 7$，时限 2s。

对于前 $5$ 个测试点的数据，$1 \leq N \leq 5\times 10^5,T \leq 5$，时限 5s。


---

---
title: "[USACO15FEB] Censoring G"
layout: "post"
diff: 省选/NOI-
pid: P3121
tag: ['2015', 'USACO', '哈希 hashing', '栈', 'AC 自动机']
---
# [USACO15FEB] Censoring G
## 题目描述

FJ 把杂志上所有的文章摘抄了下来并把它变成了一个长度不超过 $10^5$ 的字符串 $s$。他有一个包含 $n$ 个单词的列表，列表里的 $n$ 个单词记为 $t_1 \cdots t_n$。他希望从 $s$ 中删除这些单词。

FJ 每次在 $s$ 中找到最早出现的列表中的单词（最早出现指该单词的开始位置最小），然后从 $s$ 中删除这个单词。他重复这个操作直到 $s$ 中没有列表里的单词为止。注意删除一个单词后可能会导致 $s$ 中出现另一个列表中的单词。

FJ 注意到列表中的单词不会出现一个单词是另一个单词子串的情况，这意味着每个列表中的单词在 $s$ 中出现的开始位置是互不相同的。

请帮助 FJ 完成这些操作并输出最后的 $s$。
## 输入格式

第一行是一个字符串，表示文章 $s$。

第二行有一个整数，表示单词列表的单词个数 $n$。

第 $3$ 到第 $(n + 2)$ 行，每行一个字符串，第 $(i + 2)$ 行的字符串 $t_i$ 表示第 $i$ 个单词。
## 输出格式

输出一行一个字符串，表示操作结束后的 $s$。
## 样例

### 样例输入 #1
```
begintheescapexecutionatthebreakofdawn 
2 
escape 
execution 

```
### 样例输出 #1
```
beginthatthebreakofdawn 

```
## 提示

#### 数据规模与约定

对于全部的测试点，保证：

- $1 \leq |s|, \sum\limits_{i = 1}^n |t_i|, n \leq 10^5$。
- 字符串均只含小写字母。
- 操作结束后 $s$ 不会被删成空串。
- 对于所有的 $i \neq j$，$t_i$ 不是 $t_j$ 的子串。

其中对于一个字符串 $x$，约定 $|x|$ 表示 $x$ 的长度。

---

#### 提示

操作过程中 $s$ 有可能某一个前缀子串被完全删除，请格外注意这一点。



---

---
title: "[HNOI2008] 神奇的国度"
layout: "post"
diff: 省选/NOI-
pid: P3196
tag: ['2008', '湖南', '广度优先搜索 BFS', '哈希 hashing', '弦图']
---
# [HNOI2008] 神奇的国度
## 题目描述

K国是一个热衷三角形的国度,连人的交往也只喜欢三角原则.他们认为三角关系:即AB相互认识,BC相互认识,CA相互认识,是简洁高效的.为了巩固三角关系,K国禁止四边关系,五边关系等等的存在.

所谓N边关系,是指N个人 A1A2...An之间仅存在N对认识关系:(A1A2)(A2A3)...(AnA1),而没有其它认识关系.比如四边关系指ABCD四个人 AB,BC,CD,DA相互认识,而AC,BD不认识.全民比赛时,为了防止做弊，规定任意一对相互认识的人不得在一队，国王相知道，最少可以分多少支队。

## 输入格式

第一行两个整数N，M。1<=N<=10000,1<=M<=1000000.表示有N个人，M对认识关系. 接下来M行每行输入一对朋友

## 输出格式

输出一个整数，最少可以分多少队

## 样例

### 样例输入 #1
```
4 5
1 2
1 4
2 4
2 3
3 4
```
### 样例输出 #1
```
3
```
## 提示

一种方案(1,3)(2)(4)



---

---
title: "[HNOI2014] 抄卡组"
layout: "post"
diff: 省选/NOI-
pid: P3234
tag: ['字符串', '2014', '湖南', '哈希 hashing', '前缀和']
---
# [HNOI2014] 抄卡组
## 题目描述

一天闲着无聊的小L找来了当前正火爆的游戏《炉石传说》来玩，但是怎么打怎么输，于是他大喊一声”我要抄卡组！“就找来了游戏传说组第一名的游戏高手小H的直播来看。

但是小L家的网络技术还停留在拨号，看着直播画面又是卡顿又是花屏，他不给力的网络让他完全无法记录小H展示的给力的卡组。小L周围都是学霸没有人玩游戏想去帮他这个忙，但是学霸们热衷于讨论各种信息学问题。

于是他想到了一个方法：由于每次花屏的屏幕位置不一样，于是小H每次总能记录下卡组的一些部分，如果这样记录多次，不就有可能还原出小L想要的一个卡组么？

但是存在的一个问题是，小H每次展示的卡组有可能不一样，所以他想知道他每次看直播抄下来几次的卡组碎片是否一致。

这样一来小H将他遇到的游戏问题抽象成这样一个学术问题让学霸（你）解决：'\*'可以匹配任意长度个的字符 （包含0个），问所有字符串是否两两匹配。

## 输入格式

第一行包含一个正整数T，表示了数据组数。    接下来包含T组数据：    每组数据的第一行是一个正整数N，表示该组数据酌字符串个数。    接下来N行，每行一个字符串，字符串仅包含小写字母、数字、通配符术。注意:数据为UNIX格式，中间包含空行,你可以采用逐字符读入的方式

## 输出格式

输出包含T行，每行一个字母Y或者N，Y表示这组数据中所有字符串两两匹配，N表示这组数据中至少有一对字符串不匹配。

## 样例

### 样例输入 #1
```
10
2
1234567890*1234567890
1234567890a1234567890
2
1234567890*1234567890
1234567890*1234567890
2
1234*67890a1234567890
1234567890*1234567890
2
1234567890*1234567890
1234567890a12345*7890
2
1234567890*1234567890
*12345
2
12345*67890
1234567890*1234567890
2
1234567890*1234567890
12345*
2
1234567890*1234567890
*67890
2
67890*
1234567890*1234567890
2
1234567890*a*1234567890
1234567890*1234567890
```
### 样例输出 #1
```
Y

Y

Y

Y

N

Y

Y

Y

N

Y
```
## 提示

对于100%的数据，满足N<= 100000，T= 10，输入文件不超过10M，N\*最长字符串长度不超过2x10^8

目前有且仅有 hack 数据中 $T = 1$。


---

---
title: "[HNOI2014] 米特运输"
layout: "post"
diff: 省选/NOI-
pid: P3237
tag: ['数学', '2014', '湖南', '树形 DP', '哈希 hashing']
---
# [HNOI2014] 米特运输
## 题目描述

米特是 D 星球上一种非常神秘的物质，蕴含着巨大的能量。在以米特为主要能源的 D 星上，这种米特能源的运输和储存一直是一个大问题。

D 星上有 $N$ 个城市，我们将其顺序编号为 $1$ 到 $N$，$1$ 号城市为首都。这 $N$ 个城市由 $N-1$ 条单向高速通道连接起来，构成一棵以 $1$ 号城市（首部）为根的树，高速通道的方向由树中的儿子指向父亲。树按深度分层：根结点深度为 $0$，属于第 $1$ 层；根结点的子节点深度为 $1$，属于第 $2$ 层；依此类推，深度为 $i$ 的结点属于第 $i+1$ 层。

建好高速通道之后，D 星人开始考虑如何具体地储存和传输米特资源。由于发展程度不同，每个城市储存米特的能力不尽相同，其中第 $i$ 个城市建有一个容量为 $A_i$ 的米特储存器。这个米特储存器除了具有储存的功能，还具有自动收集米特的能力。

如果到了晚上六点，有某个储存器处于未满的状态，它就会自动收集大气中蕴含的米特能源，在早上六点之前就能收集满；但是，只有在储存器完全空的状态下启动自动收集程序才是安全的，未满而又非空时启动可能有安全隐患。

早上六点到七点间，根节点城市（$1$ 号城市）会将其储存器里的米特消耗殆尽。根节点不会自动搜集米特，它只接受子节点传输来的米特。

早上七点，城市之间启动米特传输过程，传输过程逐层递进：先是第 $2$ 层节点城市向第 $1$ 层（根节点城市，即 $1$ 号城市）传输，直到第 $1$ 层的储存器满或第 $2$ 层的储存器全为空；然后是第 $3$ 层向第 $2$ 层传输，直到对于第 $2$ 层的每个节点，其储存器满或其子节点（位于第 $3$ 层）的储存器全为空；依此类推，直到最后一层传输完成。传输过程一定会在晚上六点前完成。

由于技术原因，运输方案需要满足以下条件：

1. 不能让某个储存器到了晚上六点传输结束时还处于非空但又未满的状态，这个时候储存器仍然会启动自动收集米特的程序，而给已经储存有米特的储存器启动收集程序可能导致危险，也就是说要让储存器到了晚上六点时要么空要么满；

2. 关于首都——即 $1$ 号城市的特殊情况，  每天早上六点到七点间 $1$ 号城市中的米特储存器里的米特会自动被消耗殆尽，即运输方案不需要考虑首都的米特怎么运走；

3. 除了 $1$ 号城市，每个节点必须在其子节点城市向它运输米特之前将这座城市的米特储存器中原本存有的米特全部运出去给父节点，不允许储存器中残存的米特与外来的米特发生混合；

4. 运向某一个城市的若干个来源的米特数量必须完全相同，不然，这些来源不同的米特按不同比例混合之后可能发生危险。

现在 D 星人已经建立好高速通道，每个城市也有了一定储存容量的米特储存器。为了满足上面的限制条件，可能需要重建一些城市中的米特储存器。你可以，也只能，将某一座城市（包括首都）中原来存在的米特储存器摧毁，再新建一座任意容量的新的米特储存器，其容量可以是小数（在输入数据中，储存器原始容量是正整数，但重建后可以是小数），不能是负数或零，使得需要被重建的米特储存器的数目尽量少。
## 输入格式

第一行是一个正整数 $N$，表示城市的数目。    
接下来 $N$ 行，每行一个正整数，其中的第 $i$ 行表示第 $i$ 个城市原来存在的米特储存器的容量。    
再接下来是 $N-I$ 行，每行两个正整数 $a，b$ 表示城市 $b$ 到城市 $a$ 有一条高速通道 $(a≠b)$。
## 输出格式

输出文件仅包含一行，一个整数，表示最少的被重建（即修改储存器容量）的米特储存器的数目。
## 样例

### 样例输入 #1
```
5
5
4
3
2
1
1 2
1 3
2 4
2 5
```
### 样例输出 #1
```
3
```
## 提示

【样例解释】

一个最优解是将 $A_1$ 改成 $8$，$A_3$ 改成 $4$，$A_5$ 改成 $2$。这样，$2$ 和 $3$ 运给 $1$ 的量相等，$4$ 和 $5$ 运给 $2$ 的量相等，且每天晚上六点的时候，$1$，$2$ 满，$3$，$4$，$5$ 空，满足所有限制条件。

对于 $100\%$ 的数据满足 $N<500000，A_j<10^8$


---

---
title: "[SDOI2013] 刺客信条"
layout: "post"
diff: 省选/NOI-
pid: P3296
tag: ['动态规划 DP', '2013', '山东', '费用流', '哈希 hashing']
---
# [SDOI2013] 刺客信条
## 题目描述

故事发生在1486 年的意大利，Ezio 原本只是一个文艺复兴时期的贵族，后来因为家族成员受到圣殿骑士的杀害，决心成为一名刺客。最终，凭借着他的努力和出众的天赋，成为了杰出的刺客大师，他不仅是个身手敏捷的武林高手，飞檐走壁擅长各种暗杀术。刺客组织在他的带领下，为被剥削的平民声张正义，赶跑了原本统治意大利的圣殿骑士首领-教皇亚历山大六世。在他的一生中，经历了无数次惊心动魄、扣人心弦的探险和刺杀。


曾经有一次，为了寻找Altair 留下的线索和装备，Ezio 在佛罗伦萨中的刺客墓穴进行探索。这个刺客墓穴中有许多密室，且任何两个密室之间只存在一条唯一的路径。这些密室里都有一个刺客标记，他可以启动或者关闭该刺客标记。为了打开储存着线索和装备的储藏室，Ezio 必须操作刺客标记来揭开古老的封印。要想解开这个封印，他需要通过改变某些刺客标记的启动情况，使得所有刺客标记与封印密码“看起来一样”。


在这里，“看起来一样”的定义是：存在一种“标记”密室与“密码”密室之间一一对应的关系，使得密室间的连接情况和启动情况相同（提示中有更详细解释）。幸运的是，在Ezio 来到刺客墓穴之前，在Da Vinci 的帮助下，Ezio 已经得知了打开储藏室所需要的密码。


而你的任务则是帮助Ezio 找出达成目标所需要最少的改动标记次数。

## 输入格式

第一行给出一个整数n, 表示密室的个数,


第二行至第 n 行, 每行绐出两个整数 a 和 b, 表示第 a 个密室和第 b 个密室之间存在一条通道.


第 n+1行1 绐出 n 个整数1 分别表示当时每个密室的启动情况 {0表示关闭, 1表示启动).


第 n+2 行7 给出 n 个整数, 分别表示密码中每个密室的启动情况.

## 输出格式

输出只有一行，即输出最少改动标记次数

## 样例

### 样例输入 #1
```
4
1 2
2 3
3 4
0 0 1 1
1 0 0 0
```
### 样例输出 #1
```
1
```
## 提示

密室的编号是可以变的！将第三个密室关闭后，在当前标记和密码之间，存在1->4,2->3,3->2,4->1 的对应关系，重新编号后连接情况没有改变，且标记与密码对应。对于更一般的情况，存在一个1 到n 的置换P，使得对于任意密室之间的道路u-v，都一定有密码密室中的道路P(u)-P(v)；如果不存在密室之间的道路u-v，则一定没有密码密室中的道路P(u)-P(v)。


对于100%的数据，n<=700，且每个密室至多与11个密室相通



---

---
title: "[SDOI2013] 泉"
layout: "post"
diff: 省选/NOI-
pid: P3298
tag: ['2013', '山东', '哈希 hashing', '容斥原理']
---
# [SDOI2013] 泉
## 题目描述

作为光荣的济南泉历史研究小组中的一员，铭铭收集了历史上x个不同年份时不同泉区的水流指数，这个指数是一个小于. 2^30的非负整数。第i个年份时六个泉区的泉水流量指数分别为 A(i,l)，A(i,2)，A(i,3)，A(i,4)， A(i,5)与 A(i,6)。

现在铭铭希望知道有多少对不同的年份：i和j,满足这两年恰好有K个泉区的泉水流S指数对应相同。

## 输入格式

第一行有2个整数，分别是N和K

之后N行，每行有6个整数。第i行的第j个数字A(i，j)表示第i个年份中第j个泉区的泉水流量指数。

## 输出格式

一个整数表示有多少对不同的年份满足恰有K个区的泉水流量指数对应相同。

## 样例

### 样例输入 #1
```
3 3
1 2 3 4 5 6
1 2 3 0 0 0
0 0 0 4 5 6
```
### 样例输出 #1
```
2
```
## 提示

对于 100%的数据, 0<=K <=6, 且所有数据中K是等概率出现的, 即对于任意的 0<=x都有大约 1/7 的数据中 K=x.
N<=100000


---

---
title: "[SDOI2015] 双旋转字符串"
layout: "post"
diff: 省选/NOI-
pid: P3318
tag: ['字符串', '2015', '山东', '哈希 hashing']
---
# [SDOI2015] 双旋转字符串
## 题目描述

给定两个字符串集合 S 和 T 。其中 S 中的所有字符串长度都恰好为 N ，而 T 中所有字符串长度都恰好为 M 。且 N+M 恰好为偶数。如果记 S 中字符串全体为 S1，S2，...，STotalS ,而 T 中字符串全体为 T1，T2，...，TTotalT 。现在希望知道有多少对 <i,j> ，满足将 Si 和 Tj 拼接后得到的字符串 Si+Tj 满足双旋转性。

一个长度为偶数字符串 W 可以表示成两段长度相同的字符串的拼接，即 W=U+V。如果 V 可以通过 U 旋转得到，则称 W 是满足双旋转性的。比如说字符串 U=”vijos“可以通过旋转得到”ijosv“，”josvi“，”osvij“ 或”svijo“。那么”vijosjosvi“就是满足双旋转性的字符串。

## 输入格式

第一行输入四个正整数，分别为 TotalS，TotalT，N 和 M，依次表示集合 S 的大小，集合 T 的大小，集合 S 中字符串的长度和集合 T 中字符串的长度。之后 TotalS 行，依次给出 S 中所有的字符串 Si，1<=i<=TotalS。保证每一个字符串长度都恰为 N ，且字符串只由 26 个小写字母组成。之后 TotalT 行，依次给出 T 中所有的字符串 Ti，1<=i<=TotalT。保证每一个字符串长度都恰为 M ，且字符串只由 26 个小写字母组成。1<=N<=100；1<=M<=100；1<=TotalS<=100；1<=Total^T<=100,2<=N\*TotalS+M\*TotalT<=4&times;10^6

## 输出格式

输出一个整数，表示满足要求的数字对 <i,j> 有多少个。

## 样例

### 样例输入 #1
```
4 4 7 3
vijosvi
josvivi
vijosos
ijosvsv
jos
vij
ijo
jos
```
### 样例输出 #1
```
6
```


---

---
title: "[ZJOI2013] 丽洁体"
layout: "post"
diff: 省选/NOI-
pid: P3333
tag: ['动态规划 DP', '贪心', '2013', '浙江', '哈希 hashing']
---
# [ZJOI2013] 丽洁体
## 题目描述

平时的练习和考试中，我们经常会碰上这样的题：命题人给出一个例句，要我们类比着写句子。这种往往被称为仿写的题，不单单出现在小学生的考试中，也有时会出现在中考中。许多同学都喜欢做这种题，因为较其它题显得有趣。仿写的句子往往具有“A\_\_B\_\_C”的形式，其中A，B，C是给定的由一个或多个单词组成的短句，空的部分需要学生填写。当然，考试的时候空在那里也是可以的。例如，“其实天不暗阴云终要散，其实 ，其实 ，其实路不远一切会如愿，艰难困苦的日子里我为你祈祷，请你保重每一天”。再比如，“见了大海的汹涌，没见过大山的巍峨，真是遗憾；见了大山的巍峨，没见过 ，还是遗憾。出发吧，永远出发。 ，人有不老的心情。”

由于现在是网络时代，我们不再只能仿写命题人命的题，我们可以仿写网上各种句子和段落。2011年3月26日，某人在博客上发布了的消息就惹来了很多人的仿写。


很难过吧。。。考得完爆了。。。

。。。。。。其实也没什么可以说的。。。都是蒟蒻的借口罢了。。。

。。。自己果然还只是半吊子水平呢。。。。

。。。祝大家都能进省队。。。其实只要不要有遗憾就好了呢。。。

虽然我很遗憾或许不能走下去了。。。。。

886

在网络上广泛流传的仿写，因为在某些地方有独到之处，大都被命名为“某某体”。打开人人，刷新微博，你也能发现这样和那样的体，比如，对不起体，**说明他爱你体等等。金先生注意到了这一现象，他敏锐地认为这是一个很有价值的研究课题，于是就其展开研究，打算发一篇paper。由于在网上发消息，人们有了更大的灵活度，人们有时因为表达的需要，还往原本固定的A, B, C中添加一些修饰的词语。这就给辨别一个句子或段落是否是另一个句子或段落的仿写增加了困难。

金先生现在研究一种形如“A\*B\*C”的体作品，其中A, B, C分别是某个由若干单词组成的短句，\*代表0个或多个单词。他在网上找了大量的体作品，不过很多体作品不太合乎原作者的格式，也就是相当于在正规的体作品中插入了0个或多个单词。

由于数据量太大，金先生无法一个一个看过去，于是想请你帮忙，去掉尽量少的单词，使它成为指定的体。

## 输入格式

包含4行。

第一行是某个也许不规范的体作品T，

接下来三行分别代表A, B, C。

## 输出格式

仅一行，包含一个数，即最少的去除单词数。

## 样例

### 样例输入 #1
```
xiang yao yi zhi ai zhe mou wu de hua yi yao guai zhi si lai shuo tai chang le xiang yao shi xian yi qie meng xiang de hua yi ren lei zhi sheng lai shuo tai duan le
yao
tai chang le yao
tai duan le
```
### 样例输出 #1
```
2
```
## 提示

【样例说明】

在上述样例中，不规范的体作品为：“想要一直爱着某物的话，以妖怪之死来说太长了；想要实现一切梦想的话，以人类之生来说太短了”。

规范的体形如：“要\*太长了要\*太短了”。

修改后的规范的体为：“要一直爱着某物的话，以妖怪之死来说太长了；要实现一切梦想的话，以人类之生来说太短了”。


【数据规模与约定】

对于20%的数据，1≤|T|, |A|, |B|, |C|≤10。 
对于40%的数据，1≤|T|, |A|, |B|, |C|≤100。 
对于70%的数据，1≤|T|, |A|, |B|, |C|≤1000。 
对于100%的数据，1≤|T|, |A|, |B|, |C|≤50000；所有单词长度不超过5，出现次数不超过500；数据保证答案总存在。



---

---
title: "[POI 2006] PAL-Palindromes"
layout: "post"
diff: 省选/NOI-
pid: P3449
tag: ['2006', 'POI（波兰）', '哈希 hashing', '字典树 Trie']
---
# [POI 2006] PAL-Palindromes
## 题目描述

Little Johnny enjoys playing with words. He has chosen $n$ palindromes (a palindrome is a wordthat reads the same when the letters composing it are taken in the reverse order, such as dad, eye orracecar for instance) then generated all $n^2$ possible pairs of them and concatenated the pairs intosingle words. Lastly, he counted how many of the so generated words are palindromes themselves.

However, Johnny cannot be certain of not having comitted a mistake, so he has asked you to repeatthe very same actions and to give him the outcome. Write a programme which shall perform thistask for you.

TaskWrite a programme which:

reads the palindromes given by Johnny from the standard input,        determines the number of words formed out of pairs of palindromes from the input, which are palindromes    themselves,        writes the outcome to the standard output.

## 输入格式

The first line of the standard input contains a single integer $n$, $n\ge 2$, denoting the number ofpalindromes given by Johnny. The following $n$ lines contain a description of the palindromes. The $(i+1)$'st line contains a single positive integer $a_i$ denoting the length of $i$'th palindrome and apalindrome of $a_i$ small letters of English alphabet. The number $a_i$ is separated from the palindromeby a single space. The palindromes in distinct lines are distinct. The total length of all palindromesdoes not exceed $2\ 000\ 000$.

## 输出格式

The first and only line of the standard output should contain a single integer: the number of distinctordered pairs of palindromes which form a palindrome upon being concatenated.

## 样例

### 样例输入 #1
```
6
2 aa
3 aba
3 aaa
6 abaaba
5 aaaaa
4 abba
```
### 样例输出 #1
```
14
```
## 题目翻译

### 题目描述

Johnny 喜欢玩文字游戏。

他写下了 $n$ 个回文串，随后将这些串两两组合，合并成一个新串。容易看出，一共会有 $n^2$ 个新串。

两个串组合时顺序是任意的，即 `a` 和 `b` 可以组合成 `ab` 和 `ba`，另外自己和自己组合也是允许的。

现在他想知道这些新串中有多少个回文串，你能帮帮他吗？

### 输入格式

第一行一个整数 $n$。

接下来 $n$ 行，第 $i$ 行包含一个数 $a_i$ 和一个长度为 $a_i$ 的回文串。

保证所有串只包含小写字母，且所有串两两不同，所有回文串的长度和不超过 $2 \times 10^6$。

### 输出格式

输出一个整数，代表满足条件的新串的数量。


---

---
title: "[POI 2008] POC-Trains"
layout: "post"
diff: 省选/NOI-
pid: P3471
tag: ['2008', '平衡树', 'POI（波兰）', '离散化', '哈希 hashing']
---
# [POI 2008] POC-Trains
## 题目描述

The Trains of Colour Parade begins tomorrow in Byteotia.

Intense preparations are already in progress at the station's auxiliary tracks. There are $n$ parallel tracks at the station, numbered from $1$ to $n$. The train no. $i$ occupies the $i^{th}$ track.

Every train consists of $l$ cars and each car is painted with one of 26 colours (denoted by non-capital letters of the English alphabet).

We say that two trains look the same, if their corresponding cars are painted the same colour.

Throughout the parade a crane will switch places of certain pairs of cars. The real parade, however, will take place tomorrow.

Today the train dispatcher, Byteasar, watched the general rehearsal    closely. He even wrote down the sequence of car swaps.

Byteasar particularly dislikes many trains looking the same.

For each train $p$ he would like to calculate the maximum number    of trains that at some moment look the same as the train $p$ at the very same moment.

## Task

Write a programme that:

- reads descriptions of the trains occupying tracks and the sequence of car swaps,

- for each train determines the maximum number of trains that look the same as it at certain moment,

- writes out the result.


给出n个字符串，长度均为len；

有m次操作，每次将两个字符交换；

求每个字符串在任何时点上，与相同的它最多的字符串个数；

## 输入格式

The first line of the input contains three integers $n$, $l$ and $m$ ($2 \le n \le 1000$, $1 \le l \le 100$, $0 \le m \le 100\ 000$), denoting respectively the number of trains, their common length and the number of car swaps. The following $n$ lines contain descriptions of the trains on successive tracks. The

$k^{th}$ line consists of $l$ small letters of the English alphabet denoting the colours of successive cars of the $k^{th}$ train. Then $m$ lines describing the car swaps follow, in the order of the swaps. The $r^{th}$ line contains four integers $p_1$, $w_1$, $p_2$, $w_2$ ($1 \le p_1, p_2, \le n$, $1 \le w_1, w_2 \le l$, $p_1 \ne p_2$ or $w_1 \ne w_2$) denoting the $r^{th}$ car swap-the car no. $w_1$ of the train no. $p_1$ is swapped with the car no. $w_2$ of the train no. $p_2$.

## 输出格式

Your programme should write out exactly $n$ lines. The $k^[th}$ line should contain one integer-the number of trains looking the same as the train no. $k$ at certain moment.

## 样例

### 样例输入 #1
```
5 6 7
ababbd
abbbbd
aaabad
caabbd
cabaad
2 3 5 4
5 3 5 5
3 5 2 2
1 2 4 3
2 2 5 1
1 1 3 3
4 1 5 6

```
### 样例输出 #1
```
3
3
3
2
3

```
## 提示

The figure presents the successive car swaps:

```cpp
track 1:  ababbd    ababbd    ababbd    ababbd    aaabbd    aaabbd    aaabbd    aaabbd
track 2:  abbbbd    ababbd    ababbd    aaabbd    aaabbd    acabbd    acabbd    acabbd
track 3:  aaabad -> aaabad -> aaabad -> aaabbd -> aaabbd -> aaabbd -> aaabbd -> aaabbd
track 4:  caabbd    caabbd    caabbd    caabbd    cabbbd    cabbbd    cabbbd    dabbbd
track 5:  cabaad    cabbad    caabbd    caabbd    caabbd    aaabbd    aaabbd    aaabbc
           (0)       (1)       (2)       (3)       (4)       (5)       (6)       (7)
```

The number of trains looking the same as either of the trains no. 1, 2 or 3 was maximal at time (4) (when all three looked the same). The number of trains looking the same as the train no. 5 was maximal at time (5) and (6). The number of trains looking the same as the train no. 4 was maximal at time (2).



---

---
title: "[POI 2012] PRE-Prefixuffix"
layout: "post"
diff: 省选/NOI-
pid: P3546
tag: ['字符串', '2012', 'POI（波兰）', '哈希 hashing', '线性递推', 'KMP 算法']
---
# [POI 2012] PRE-Prefixuffix
## 题目描述

We consider strings consisting of lowercase letters of the English alphabet in this problem.

An initial fragment of a given string is called its prefix.

A final (terminal) fragment of a given string is called its suffix.

In particular, the empty string is both a prefix and a suffix of any string.

Two strings are cyclically equivalent if one of them can be obtained from another by    moving its certain suffix from the end of the string to its beginning.

For example, the strings ![](http://main.edu.pl/images/OI19/pre-en-tex.1.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.2.png) are cyclically equivalent, whereas the strings ![](http://main.edu.pl/images/OI19/pre-en-tex.3.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.4.png) are not.

In particular, every string is cyclically equivalent to itself.

A string ![](http://main.edu.pl/images/OI19/pre-en-tex.5.png) consisting of ![](http://main.edu.pl/images/OI19/pre-en-tex.6.png) letters is given.

We are looking for its prefix ![](http://main.edu.pl/images/OI19/pre-en-tex.7.png) and suffix ![](http://main.edu.pl/images/OI19/pre-en-tex.8.png) of equal length such that:

![](http://main.edu.pl/images/OI19/pre-en-tex.9.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.10.png) are cyclically equivalent,                  the common length of ![](http://main.edu.pl/images/OI19/pre-en-tex.11.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.12.png) does not exceed ![](http://main.edu.pl/images/OI19/pre-en-tex.13.png)        (i.e., the prefix ![](http://main.edu.pl/images/OI19/pre-en-tex.14.png) and the suffix ![](http://main.edu.pl/images/OI19/pre-en-tex.15.png) do not overlap in ![](http://main.edu.pl/images/OI19/pre-en-tex.16.png)), and                  the common length of ![](http://main.edu.pl/images/OI19/pre-en-tex.17.png) and ![](http://main.edu.pl/images/OI19/pre-en-tex.18.png) is maximized.

对于两个串 $S_1, S_2$，如果能够将 $S_1$ 的一个后缀移动到开头后变成 $S_2$，就称 $S_1$ 和 $S_2$ 循环相同。例如串 ababba 和串 abbaab 是循环相同的。

给出一个长度为 $n$ 的串 $S$，求满足下面条件的最大的 $L(L\leq \frac n 2)$：$S$ 的 $L$ 前缀和 $S$ 的 $L$ 后缀是循环相同的。
## 输入格式

The first line of the standard input contains a single integer ![](http://main.edu.pl/images/OI19/pre-en-tex.19.png)      (![](http://main.edu.pl/images/OI19/pre-en-tex.20.png)) denoting the length of the string ![](http://main.edu.pl/images/OI19/pre-en-tex.21.png).

The second line of input contains the string ![](http://main.edu.pl/images/OI19/pre-en-tex.22.png) itself, consisting of ![](http://main.edu.pl/images/OI19/pre-en-tex.23.png) lowercase letters of the English alphabet.

In tests worth 30% of the points the condition ![](http://main.edu.pl/images/OI19/pre-en-tex.24.png) holds in addition.

In tests worth 50% of the points the condition ![](http://main.edu.pl/images/OI19/pre-en-tex.25.png) holds in addition.

## 输出格式

Your program should print a single integer in the first and only line of the standard output,      namely the common length of the prefix ![](http://main.edu.pl/images/OI19/pre-en-tex.26.png) and the suffix ![](http://main.edu.pl/images/OI19/pre-en-tex.27.png) that we are looking for.

## 样例

### 样例输入 #1
```
15
ababbabababbaab
```
### 样例输出 #1
```
6
```
## 提示

数据范围：

- 对于 $30\%$ 的数据，保证 $n\le 500$；
- 对于 $50\%$ 的数据，保证 $n\le 5000$；
- 对于 $100\%$ 数据，保证 $1\le n\le 10^6$。


---

---
title: "[POI 2013] SPA-Walk"
layout: "post"
diff: 省选/NOI-
pid: P3552
tag: ['数学', '2013', 'POI（波兰）', '哈希 hashing']
---
# [POI 2013] SPA-Walk
## 题目描述

The names of towns in Byteotia are unique sequences of exactly $n$ bits.

There are $2^n-k$ towns in Byteotia, and thus,only $k$ sequences of $n$ bits do not correspond to any town.

Some pairs of towns are connected with roads.

Specifically, two towns are directly linked by a road if and only if their names differ in a single bit.

The roads do not cross outside of towns.

Byteasar intends to take a stroll - he intends to walk from the town $x$ to the town $y$, taking the existing roads.

Your task is to write a program that will determine if such a walk is possible.

有2^n个长度为n的01串，两个01串之间有边当且仅当这两个01串只有一位不同，现在从这2n个串中拿掉k个，问指定两个串之间能否到达

## 输入格式

In the first line of the standard input, there are two integers,$n$ and $k$($1\le n\le 60$, $0\le k\le 1\ 000\ 000$, $k\le 2^n-1$, $n\times k\le 5\ 000\ 000$),      separated by a single space.

These are the length of town names in bits and the the number of $n$-bit sequences that do not correspond to any town, respectively.

In the second line, there are two strings, separated by a single space,      each consisting of $n$ characters 0 and/or 1.

These are the names of the towns $x$ and $y$.

In the $k$ lines that follow, all the sequences of $n$ bits that do not correspond to any town are given, one sequence per line.In the $k$ lines that follow, all the sequences of $n$ bits that do not correspond to any town are given, one sequence per line.Each such sequence is a string of $n$ characters 0 and/or 1.You may assume that $x$ and $y$ are not among those $k$ sequences.

## 输出格式

Your program should print to the standard output the word TAK (Polish for yes) if walking from the town x to the town y is possible, and the word NIE (Polish for no) otherwise.

## 样例

### 样例输入 #1
```
4 6
0000 1011
0110
0111
0011
1101
1010
1001

```
### 样例输出 #1
```
TAK

```
## 提示

有2^n个长度为n的01串，两个01串之间有边当且仅当这两个01串只有一位不同，现在从这2n个串中拿掉k个，问指定两个串之间能否到达



---

---
title: "[POI 2015] POD"
layout: "post"
diff: 省选/NOI-
pid: P3587
tag: ['2015', '单调队列', 'POI（波兰）', '哈希 hashing']
---
# [POI 2015] POD
## 题目描述

长度为 $n$ 的一串项链，每颗珠子是 $k$ 种颜色之一。第 $i$ 颗与第 $i-1,i+1$ 颗珠子相邻，第 $n$ 颗与第 $1$ 颗也相邻。

切两刀，把项链断成两条链。要求每种颜色的珠子只能出现在其中一条链中。

求方案数量（保证至少存在一种），以及切成的两段长度之差绝对值的最小值。
## 输入格式

第一行 $n,k$（$2\leq k\leq n\leq 10^6$）。颜色从 $1$ 到 $k$ 标号。

接下来 $n$ 个数，按顺序表示每颗珠子的颜色。（保证 $k$ 种颜色各出现至少一次）。 
## 输出格式

一行两个整数：方案数量，和长度差的最小值。
## 样例

### 样例输入 #1
```
9 5
2 5 3 2 2 4 1 1 3
```
### 样例输出 #1
```
4 3
```
## 提示

**【样例解释】**

四种方法中较短的一条分别是 $(5),(4),(1,1),(4,1,1)$。相差最小值 $6-3=3$。 

----

原题名称：Podział naszyjnika。 


---

---
title: "[NOI2017] 蚯蚓排队"
layout: "post"
diff: 省选/NOI-
pid: P3823
tag: ['字符串', '2017', 'NOI', 'O2优化', '哈希 hashing']
---
# [NOI2017] 蚯蚓排队
## 题目描述

蚯蚓幼儿园有 $n$ 只蚯蚓。幼儿园园长神刀手为了管理方便，时常让这些蚯蚓们列队表演。

所有蚯蚓用从 $1$ 到 $n$ 的连续正整数编号。每只蚯蚓的长度可以用一个正整数表示，根据入园要求，所有蚯蚓的长度都不超过 $6$ 。神刀手希望这些蚯蚓排成若干个队伍，初始时，每只蚯蚓各自排成一个仅有一只蚯蚓的队伍，该蚯蚓既在队首，也在队尾。

神刀手将会依次进行 $m$ 次操作，每个操作都是以下三种操作中的一种：

1. 给出 $i$ 和 $j$ ，令 $i$ 号蚯蚓与 $j$ 号蚯蚓所在的两个队伍合并为一个队伍，具体来说，令 $j$ 号蚯蚓紧挨在 $i$ 号蚯蚓之后，其余蚯蚓保持队伍的前后关系不变。

2. 给出 $i$ ，令 $i$ 号蚯蚓与紧挨其后的一只蚯蚓分离为两个队伍，具体来说，在分离之后， $i$ 号蚯蚓在其中一个队伍的队尾，原本紧挨其后的那一只蚯蚓在另一个队伍的队首，其余蚯蚓保持队伍的前后关系不变。

3. 给出一个正整数 $k$ 和一个长度至少为 $k$ 的数字串 $s$ ，对于 $s$ 的每个长度为 $k$ 的连续子串 $t$ （这样的子串共有 $|s|-k+1$ 个，其中 $|s|$ 为 $s$ 的长度），定义函数 $f(t)$，询问所有这些 $f(t)$ 的**乘积**对 $998244353$ 取模后的结果。其中 $f(t)$ 的定义如下：

对于当前的蚯蚓队伍，定义某个蚯蚓的**向后 $k$ 数字串**为：从该蚯蚓出发，沿队伍的向后方向，寻找最近的 $k$ 只蚯蚓（包括其自身），将这些蚯蚓的长度视作字符连接而成的数字串；如果这样找到的蚯蚓不足 $k$ 只，则其没有**向后$k$数字串**。例如蚯蚓的队伍为 $10$ 号蚯蚓在队首，其后是 $22$ 号蚯蚓，其后是 $3$ 号蚯蚓（为队尾），这些蚯蚓的长度分别为 $4$ 、 $5$ 、 $6$ ，则 $10$ 号蚯蚓的**向后 $3$ 数字串**为 `456`， $22$ 号蚯蚓没有**向后 $3$ 数字串**，但其**向后 $2$ 数字串**为 `56`，其**向后 $1$ 数字串**为 `5`。

而 $f(t)$ 表示所有蚯蚓中，**向后 $k$ 数字串**恰好为 $t$ 的蚯蚓只数。
## 输入格式

输入文件的第一行有两个正整数 $n,m$ ，分别表示蚯蚓的只数与操作次数。

第二行包含 $n$ 个不超过 $6$ 的正整数，依次表示编号为 $1,2,\dots,n$ 的蚯蚓的长度。

接下来 $m$ 行，每行表示一个操作。每个操作的格式可以为：

* `1` $i$ $j$（$1 \leq i, j \leq n$）表示：令 $i$ 号与 $j$ 号蚯蚓**所在**的两个队伍合并为一个队伍，新队伍中， $j$ 号蚯蚓紧挨在 $i$ 号蚯蚓之后。保证在此操作之前， $i$ 号蚯蚓在某个队伍的队尾，$j$ 号蚯蚓在某个队伍的队首，且两只蚯蚓不在同一个队伍中。

* `2` $i$（$1 \leq i \leq n$）表示：令 $i$ 号蚯蚓与紧挨其后一个蚯蚓分离为两个队伍。保证在此操作之前， $i$ 号蚯蚓不是某个队伍的队尾。

* `3` $s$ $k$（$k$为正整数，$s$为一个长度至少为$k$的数字串）表示：询问 $s$ 的每个长度为 $k$ 的子串 $t$ 的 $f(t)$ 的乘积，对 998244353 取模的结果。 $f(t)$ 的定义见题目描述。

同一行输入的相邻两个元素之间，用恰好一个空格隔开。

输入文件可能较大，请不要使用过于缓慢的读入方式。
## 输出格式

依次对于每个形如 `3 s k` 的操作，输出一行，仅包含一个整数，表示询问的结果。
## 样例

### 样例输入 #1
```
5 9
3 1 3 5 3
3 333135 2
3 333135 1
1 1 3
1 2 5
1 3 2
1 5 4
3 333135 2
3 333135 1
3 333135 3
```
### 样例输出 #1
```
0
81
1
81
0
```
### 样例输入 #2
```
2 10
6 6
3 666666 1
1 1 2
3 666666 2
3 666666 4
3 666666666666666666666666666666 1
2 1
1 2 1
3 666666 2
3 666666 4
3 666666666666666666666666666666 1
```
### 样例输出 #2
```
64
1
0
75497471
1
0
75497471
```
## 提示

保证 $n \leq 2 \times 10^{5}$，$m \leq 5 \times 10^{5}$，$k \leq 50$ 。

设 $\sum |s|$ 为某个输入文件中所有询问的 $s$ 的长度总和，则 $\sum |s| \leq 10^{7}$  。

设 $c$ 为某个输入文件中形如 `2 i` 的操作的次数，则 $c \leq 10^{3}$ 。

每个测试点的详细信息见下表：

| 测试点编号 | $n$ | $m$ | $k$ | $\sum \|s\|$ | $c$ | 全为 $\texttt{1}$ |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| 1 | $=1$ | $\leq 10^{3}$ | $=1$ | $\leq 10^{3}$ | $=0$ | No |
| 2 | $\leq 20$ | $\leq 40$ | $\leq 10$ | $\leq 10^{3}$ | $=0$ | No |
| 3 | $\leq 150$ | $\leq 2,000$ | $\leq 50$ | $\leq 10^{3}$ | $\leq 10^{3}$ | No |
| 4 | $\leq 500$ | $\leq 600$ | $\leq 50$ | $\leq 10^{3}$ | $=0$ | No |
| 5 | $\leq 10^{3}$ | $\leq 2,000$ | $\leq 50$ | $\leq 10^{3}$ | $\leq 10^{3}$ | No |
| 6 | $\leq 5 \times 10^{4}$ | $\leq 6 \times 10^{4}$ | $\leq 5$ | $\leq 5 \times 10^{4}$ | $\leq 10^{3}$ | No |
| 7 | $\leq 5 \times 10^{4}$ | $\leq 6 \times 10^{4}$ | $\leq 50$ | $\leq 5 \times 10^{4}$ | $=0$ | Yes |
| 8 | $\leq 5 \times 10^{4}$ | $\leq 6 \times 10^{4}$ | $\leq 50$ | $\leq 5 \times 10^{4}$ | $=0$ | No |
| 9 | $\leq 5 \times 10^{4}$ | $\leq 6 \times 10^{4}$ | $\leq 50$ | $\leq 5 \times 10^{4}$ | $\leq 10^{3}$ | No |
| 10 | $\leq 5 \times 10^{4}$ | $\leq 8 \times 10^{4}$ | $\leq 50$ | $\leq 2.5 \times 10^{6}$ | $=0$ | No |
| 11 | $\leq 5 \times 10^{4}$ | $\leq 8 \times 10^{4}$ | $\leq 50$ | $\leq 2.5 \times 10^{6}$ | $\leq 10^{3}$ | No |
| 12 | $\leq 10^{5}$ | $\leq 1.1 \times 10^{5}$ | $\leq 6$ | $\leq 10^{5}$ | $\leq 10^{3}$ | No |
| 13 | $\leq 10^{5}$ | $\leq 1.1 \times 10^{5}$ | $\leq 50$ | $\leq 10^{5}$ | $=0$ | Yes |
| 14 | $\leq 10^{5}$ | $\leq 1.1 \times 10^{5}$ | $\leq 50$ | $\leq 10^{5}$ | $=0$ | No |
| 15 | $\leq 10^{5}$ | $\leq 1.1 \times 10^{5}$ | $\leq 50$ | $\leq 10^{5}$ | $\leq 10^{3}$ | No |
| 16 | $\leq 10^{5}$ | $\leq 1.5 \times 10^{5}$ | $\leq 50$ | $\leq 5 \times 10^{6}$ | $=0$ | No |
| 17 | $\leq 10^{5}$ | $\leq 1.5 \times 10^{5}$ | $\leq 50$ | $\leq 5 \times 10^{6}$ | $\leq 10^{3}$ | No |
| 18 | $\leq 2 \times 10^{5}$ | $\leq 5 \times 10^{5}$ | $=1$ | $\leq 10^{7}$ | $=0$ | No |
| 19 | $\leq 2 \times 10^{5}$ | $\leq 5 \times 10^{5}$ | $=1$ | $\leq 10^{7}$ | $\leq 10^{3}$ | No |
| 20 | $\leq 2 \times 10^{5}$ | $\leq 2.5 \times 10^{5}$ | $\leq 7$ | $\leq 2 \times 10^{5}$ | $\leq 10^{3}$ | No |
| 21 | $\leq 2 \times 10^{5}$ | $\leq 2.5 \times 10^{5}$ | $\leq 50$ | $\leq 2 \times 10^{5}$ | $=0$ | Yes |
| 22 | $\leq 2 \times 10^{5}$ | $\leq 2.5 \times 10^{5}$ | $\leq 50$ | $\leq 2 \times 10^{5}$ | $=0$ | No |
| 23 | $\leq 2 \times 10^{5}$ | $\leq 2.5 \times 10^{5}$ | $\leq 50$ | $\leq 2 \times 10^{5}$ | $\leq 10^{3}$ | No |
| 24 | $\leq 2 \times 10^{5}$ | $\leq 3 \times 10^{5}$ | $\leq 50$ | $\leq 10^{7}$ | $=0$ | No |
| 25 | $\leq 2 \times 10^{5}$ | $\leq 3 \times 10^{5}$ | $\leq 50$ | $\leq 10^{7}$ | $\leq 10^{3}$ | No |

如果一个测试点的“全为`1`”的一列为“Yes”，表示该测试点的所有蚯蚓的长度均为 1，并且所有询问串 $s$ 的每一位也均为`1`。


---

---
title: "[JSOI2008] 火星人"
layout: "post"
diff: 省选/NOI-
pid: P4036
tag: ['字符串', '2008', '各省省选', '平衡树', '江苏', '哈希 hashing']
---
# [JSOI2008] 火星人
## 题目描述

火星人最近研究了一种操作：求一个字串两个后缀的公共前缀。

比方说，有这样一个字符串：madamimadam，我们将这个字符串的各个字符予以标号：
```
序号 1 2 3 4 5 6 7 8 9 10 11 
字符 m a d a m i m a d a m
```
现在，火星人定义了一个函数 $LCQ(x, y)$，表示：该字符串中第 $x$ 个字符开始的字串，与该字符串中第 $y$ 个字符开始的字串，两个字串的公共前缀的长度。比方说，$LCQ(1, 7) = 5, LCQ(2, 10) = 1, LCQ(4, 7) = 0$

在研究 $LCQ$ 函数的过程中，火星人发现了这样的一个关联：如果把该字符串的所有后缀排好序，就可以很快地求出 $LCQ$ 函数的值；同样，如果求出了 $LCQ$ 函数的值，也可以很快地将该字符串的后缀排好序。

尽管火星人聪明地找到了求取 $LCQ$ 函数的快速算法，但不甘心认输的地球人又给火星人出了个难题：在求取 $LCQ$ 函数的同时，还可以改变字符串本身。具体地说，可以更改字符串中某一个字符的值，也可以在字符串中的某一个位置插入一个字符。地球人想考验一下，在如此复杂的问题中，火星人是否还能够做到很快地求取 $LCQ$ 函数的值。
## 输入格式

第一行给出初始的字符串。第二行是一个非负整数 $M$ ，表示操作的个数。接下来的M行，每行描述一个操作。操作有 $3$ 种，如下所示

1. 询问。语法：$Q$ $x$ $y$ ，$x$ ,$y$ 均为正整数。功能：计算 $LCQ(x,y)$ 限制：$1$ $\leq$ $x$ , $y$ $\leq$ 当前字符串长度 。
2. 修改。语法：$R$ $x$ $d$，$x$ 是正整数，$d$ 是字符。功能：将字符串中第 $x$ 个数修改为字符 $d$ 。限制：$x$ 不超过当前字符串长度。
3. 插入：语法：$I$ $x$ $d$ ，$x$ 是非负整数，$d$ 是字符。功能：在字符串第 $x$ 个字符之后插入字符 $d$ ，如果 $x=0$，则在字符串开头插入。限制：$x$ 不超过当前字符串长度
## 输出格式

对于输入文件中每一个询问操作，你都应该输出对应的答案。一个答案一行。
## 样例

### 样例输入 #1
```
madamimadam
7
Q 1 7
Q 4 8
Q 10 11
R 3 a
Q 1 7
I 10 a
Q 2 11
```
### 样例输出 #1
```
5
1
0
2
1
```
## 提示

1. 所有字符串自始至终都只有小写字母构成。
2. $M\leq150,000$
3. 字符串长度L自始至终都满足$L\leq100,000$
4. 询问操作的个数不超过 $10,000$ 个。

对于第 $1$，$2$ 个数据，字符串长度自始至终都不超过 $1,000$
对于第 $3$，$4$，$5$ 个数据，没有插入操作。

2024/07/40 更新一组 hack。


---

---
title: "Hash?"
layout: "post"
diff: 省选/NOI-
pid: P4235
tag: ['字符串', '哈希 hashing', '概率论']
---
# Hash?
## 题目背景

**zhoutb2333**学习了哈希算法，他于是去统计给定一些字符串，其中有多少个本质不同的字符串。


但是**zhoutb2333**突发奇想，如果哈希采用的$base$每次随机，那么结果会变成什么样呢？

**辣鸡出题人又出锅了！subtask3的数据有问题，现在统一将模数改为65537**

题目来源：[zhoutb2333](https://www.luogu.org/space/show?uid=31564)
## 题目描述

他通过某种办法，获得了一个函数:$int \ Rand(int  \ x)$，它会等概率地返回一个$[0,x)$中的整数。

他写下了这样的代码：
``` cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int x=10,maxn=35,maxlen=16010;
ll HASH[maxn];
const ll p=65537;
char str[maxlen];
ll Hash(){
    int base=Rand(x);
    ll ret=0;
    for(int i=1;str[i];i++)
        ret=(ret*base+str[i]-'a'+1)%p;
    return ret;
}
int main(){
    int ans=0,n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%s",str+1),HASH[i]=Hash();
    sort(HASH+1,HASH+n+1);
    HASH[0]=-1;
    for(int i=1;i<=n;i++)
        ans+=(HASH[i]!=HASH[i-1]);
    printf("%d\n",ans);
    return 0;
}
```
**zhoutb2333**想问你，给定一些字符串和参数$x$，答案$ans$的期望是多少呢？

$65537= 2^{16}+1$**是质数**

**参数$x$在这个程序中是确定的$10$，但是每次输入会给定。**
## 输入格式

第一行三个整数$x,N$，表示$base$生成的参数和字符串的个数

接下来$N$行每行一个字符串，字符串仅由小写字母组成。
## 输出格式

一行一个小数，表示答案$ans$的期望，**模$65537$输出**。

即：如果你的答案为$\frac{q}{p}$（$gcd(p,q)=1$），那么输出使得$px \equiv q \ (mod \ 65537$的最小正整数$x$。可以证明答案$ans$一定为正有理数，并且这样的$x$一定存在。
## 样例

### 样例输入 #1
```
2 2
aa
aa
```
### 样例输出 #1
```
32770

```
### 样例输入 #2
```
3 6
i
dont
know
what
to
say
```
### 样例输出 #2
```
58261

```
## 提示

本题由$3$个$subtask$组成，设$M$为这$N$个字符串中，每个字符串长度的最大值。

对于$subtask \ 1$：$1 \le N \le 8 , M \le 10,x \le 4$，分值为$20$，时间限制为$1s$。

对于$subtask \ 2$：$1 \le N \le 30 , M \le 500,x \le 500$，分值为$50$，时间限制为$1s$。

对于$subtask \ 3$：$1 \le N \le 5 , M \le 16000,x \le 16000$，分值为$30$，时间限制为$4.5s$。

**样例#1解释：**

参数$x=2$，那么可能的哈希$base$为$0,1$。

如果哈希第一个`aa`采用的$base$和第二个`aa`的$base$相同，那么答案为$1$。

如果两个$base$不相同，那么答案为$2$。

分析发现这两种情况发生的概率相同，都是$\frac{1}{2}$，那么答案$ans$的期望为$1 * \frac{1}{2} + 2 * \frac{1}{2}=\frac{3}{2}$。使得$2x \equiv 3 \ (mod \ 65537)$的最小正整数$x$为$32770$。

**样例#2解释：**

求得答案为$\frac{53}{9}$。使得$9x \equiv 53 \ (mod \ 65537)$的最小正整数$x$为$58261$。

**注意：本题允许手动开$O2$优化以避免被卡常数，方法如下：**
``` cpp
%:pragma GCC optimize(2)
/*程序*/
```


---

---
title: "[JSOI2016] 独特的树叶"
layout: "post"
diff: 省选/NOI-
pid: P4323
tag: ['2016', '江苏', '深度优先搜索 DFS', '哈希 hashing']
---
# [JSOI2016] 独特的树叶
## 题目描述

JYY有两棵树 $A$ 和 $B$ ：树 $A$ 有 $N$ 个点，编号为 $1$ 到 $N$ ；树 $B$ 有$N+1$ 个节点，编号为 $1$ 到$N+1$

JYY 知道树 $B$ 恰好是由树 $A$ 加上一个叶节点，然后将节点的编号打乱后得到的。他想知道，这个多余的叶子到底是树 $B$ 中的哪一个叶节点呢？
## 输入格式

输入一行包含一个正整数 $N$。 接下来 $N-1$ 行，描述树$ A$，每行包含两个整数表示树 $A$ 中的一条边； 接下来 $N$ 行，描述树 $B$，每行包含两个整数表示树 $B$ 中的一条边。
## 输出格式

输出一行一个整数，表示树 $B$ 中相比树 $A$ 多余的那个叶子的编号。如果有多个符合要求的叶子，输出 $B$ 中编号最小的那一个的编号。
## 样例

### 样例输入 #1
```
5
1 2
2 3
1 4
1 5
1 2
2 3
3 4
4 5
3 6
```
### 样例输出 #1
```
1

```
## 提示

对于所有数据，$1 \leq n \leq 10 ^ 5$


---

---
title: "【XR-3】系统设计"
layout: "post"
diff: 省选/NOI-
pid: P5537
tag: ['字符串', '线段树', '二分', '树状数组', 'O2优化', '哈希 hashing']
---
# 【XR-3】系统设计
## 题目描述

小 X 需要你设计一个系统。

这个系统首先需要输入一棵 $n$ 个点的有根树和一个长度为 $m$ 的序列 $a$，接下来需要实现 $q$ 个操作。

操作分两种：

1. `1 x l r` 表示设定起点为有根树的节点 $x$，接下来依次遍历 $l \sim r$。当遍历到 $i$ 时，从当前节点走向它的编号第 $a_i$ 小的儿子。如果某一时刻当前节点的儿子个数小于 $a_i$，或者已经遍历完 $l \sim r$，则在这个点停住，并输出这个点的编号，同时停止遍历。
2. `2 t k` 表示将序列中第 $t$ 个数 $a_t$ 修改为 $k$。
## 输入格式

第一行 $3$ 个正整数 $n,m,q$，分别表示树的点数、序列的长度和操作个数。

第二行 $n$ 个整数 $f_{1 \dots n}$，其中 $f_i$ 表示点 $i$ 在树中的父亲节点编号，特别地，设根节点为 $rt$，则 $f_{rt} = 0$。

第三行 $m$ 个正整数 $a_{1 \dots m}$，表示序列 $a$。

接下来 $q$ 行，每行描述一个操作。

**数据范围：**

- $1 \le n,m,q \le 5 \times 10 ^ 5$。
- $1 \le a_i \le n$。
- 对于操作 $1$，保证 $1 \le x \le n$，$1 \le l \le r \le m$。
- 对于操作 $2$，保证 $1 \le t \le m$，$1 \le k \le n$。
## 输出格式

对于每个操作 $1$，一行一个正整数，表示答案。
## 样例

### 样例输入 #1
```
6 6 10
0 1 2 2 1 5
1 2 2 1 2 1
1 1 1 3
1 5 2 6
1 6 5 6
1 2 3 5
1 2 4 4
2 2 1
1 1 1 6
1 1 2 4
2 1 2
1 1 1 5

```
### 样例输出 #1
```
4
5
6
4
3
3
4
6

```
## 提示

本题读入、输出量较大，请使用[读入、输出优化](https://oi-wiki.org/misc/io/)。

【样例说明】

第一个操作为 `1 1 1 3`，即 $1 \rightarrow 2 \rightarrow 4$，因此答案为 $4$。

第九个操作后，序列变为 `2 1 2 1 2 1`。

第十个操作为 `1 1 1 5`，即 $1 \rightarrow 5 \rightarrow 6$，因此答案为 $6$。


---

---
title: "秩序魔咒"
layout: "post"
diff: 省选/NOI-
pid: P5555
tag: ['字符串', '后缀自动机 SAM', '哈希 hashing', '回文自动机 PAM']
---
# 秩序魔咒
## 题目描述

现代魔法师小L和小K正在研究魔咒。

“你知道如何使用魔咒吗？”

“当然知道，这是一个现代魔法师最基本的修养。”

“那你对魔咒的发展史了解多少？”

“课上讲的我还记得一点。那是在很久很久之前了。当时，世界上还没有人会使用魔咒，而混沌魔法成为了魔法界当时的主流魔法。这是一种邪恶的法术，不需要技巧，不需要规则，内心越黑暗，力量越强。于是，邪恶的魔法师们自相残杀，弄得天昏地暗，血流成河。其中，以自称‘混沌恶魔’的魔法师为首的魔法师集团通过极其肮脏的手段控制了几乎整个魔法界，让那些向往秩序与和平的魔法师难以生存。就在这个时候，世界救星的救星出现了。名为莱赫穆拉和肯埋多卡的两名魔法师勇敢地站了出来，仅凭两个人的力量就与混沌恶魔集团展开了决战，可终究寡不敌众，被逼到了绝境。就在混沌恶魔的最后一击打中他们的身体时，莱赫穆拉和肯埋多卡利用这一击的巨大魔力，将两人余下的全部魔法与意志升格成了概念，创造了秩序魔咒体系，扭转了世界理论，使得混沌魔法被永远封印。而混沌恶魔也在这强烈的扭曲中灰飞烟灭。从此，魔法界由混沌纪元进入了秩序纪元，人们遵循莱赫穆拉和肯埋多卡这两位圣人的遗志，在秩序魔咒体系下使用魔咒，直到现在。”

“原来是这样。我们如今需要遵循一系列原则来使用魔咒，是这个原因啊。”

“是啊，这正是两位圣人为维持现在这个世界不退回混沌纪元而做的努力。话说，你是上个星期才刚刚上了第一堂魔法课，你还记得使用魔咒的几个原则吗？”

“我想想。第一，必须出现在秩序序列中。当时二位圣人留下来的体系，经过后代魔法师不懈的努力，被翻译成了名为秩序序列的存在。为了方便现代魔法师使用，**秩序序列只由英文小写字母组成**。由于体系的力量过于强大而不能仅仅限制在一个序列中，**魔法师们分别将两位圣人的遗志转移到了两个秩序序列里**。魔咒必须受到秩序序列的限制。**具体来说，是必须出现在秩序序列里（是秩序序列的子串）**。由于二位圣人的遗志不可分割，**魔咒必须同时出现在两个秩序序列里**。第二，为了让魔咒稳定而精确，秩序体系规定了魔咒的形态。**具体来说，魔咒的第一个字符需要与魔咒的倒数第一个字符相同，魔咒的第二个字符需要与魔咒的倒数第二个字符相同，以此类推**。这样就可以使魔咒对称而有秩序了。还有的话，让我看看……”

“别看了别看了，最重要的就是这些了。还有，你说不定还不知道，魔咒越长，力量越强大。”

“是这样的吗？难怪那天老师演示的魔咒魔力比我的大那么多。”

“是的是的。你是不是已经发现了，魔咒的力量是有最高限制的？”

“啊，好像没错。但老师那天说，最强魔咒的使用者还没出现？”

“对。使用者自身必须要有与魔咒同样程度的能力，才可能顺利地使用这个魔咒。我们这些初学者，不知道何年何月才能达到这个程度呢……”

“唉……不如，我们来数一数力量最强的魔咒的长度，和它们有多少个吧。”

“嗯，反正没事可做，我们就来干一干这种力所能及的事吧。”

于是，小L和小K就开始数最强魔咒的长度和个数。可过了不一会儿，它们就坚持不住了，因为秩序序列实在太长太长了。

现在，你作为一个资深魔法师，有必要告诉他们这种基本的常识。你当然已经知道两个秩序序列的形态，请你帮小L和小K算出最强魔咒的长度和个数。
## 输入格式

第一行，两个整数$n,m$，分别表示两个秩序序列的长度。

接着第二行与第三行，两个字符串，表示两个秩序序列，长度分别为$n,m$。
## 输出格式

一行两个整数，用单个空格隔开，分别表示最强魔咒的长度与个数。
## 样例

### 样例输入 #1
```
6 7
aaabab
ababaaa
```
### 样例输出 #1
```
3 3
```
### 样例输入 #2
```
10 10
bbaabaaaac
bbaabaaaac
```
### 样例输出 #2
```
5 1
```
## 提示

**样例解释**

样例1：符合规定的魔咒有$a,b,aa,aaa,aba,bab$，其中最强的有$aaa,aba,bab$，长度为$3$，共$3$个。

样例2：符合规定的魔咒有$a,b,aa,aaa,aaaa,bb,baab,aba,aabaa,c$，其中最强的有$aabaa$，长度为$5$，共$1$个。

**数据范围**

由于某些原因，本题需要使用$Subtask$。为取得一个$Subtask$的得分，你需要通过此$Subtask$中的所有数据点。
|  | 分值 | $n,m$取值范围 | 特殊性质 |
| :----------: | :----------: | :----------: | :----------: |
| $Subtask1$ | $0$ | $1\le n,m\le260817$ | 是样例 |
| $Subtask2$ | $5$ | $1\le n,m\le260817$ | 两个秩序序列由同一字符组成 |
| $Subtask3$ | $5$ | $1\le n,m\le10$ | 无 |
| $Subtask4$ | $10$ | $1\le n,m\le300$ | 无 |
| $Subtask5$ | $10$ | $1\le n,m\le2000$ | 无 |
| $Subtask6$ | $30$ | $1\le n,m\le260817$ | 两个秩序序列相同 |
| $Subtask7$ | $40$ | $1\le n,m\le260817$ | 无 |

显然，相同的魔咒数量只计一次。保证至少存在一个长度不小于$1$的符合规定的魔咒。

注意时限为$3s$。


---

---
title: "[JSOI2015] isomorphism"
layout: "post"
diff: 省选/NOI-
pid: P6084
tag: ['2015', '各省省选', '江苏', '哈希 hashing']
---
# [JSOI2015] isomorphism
## 题目描述

一个无向树的度数为 $2$ 的结点称为假结点，其它结点称为真结点。一个无向树的简化树其结点由原树的全体真结点组成，两个真结点之间有边当且仅当它们在原树中有边，或者在原树中有一条联结这两个结点的路，其中间节点全是假结点。两个无向树各自的简化树如果同构，即存在结点之间的一一对应，使得在一个树中的任意两个结点之间有边当且仅当它们的对应结点在另一个树中有边，则称原来的两个无向树实质同构。

给定若干个无向树，将相互实质同构的无向树只保留一个其余删除。统计剩下的相互不实质同构的无向树个数，并将它们的简化树结点个数从小到大输出。
## 输入格式

第一行只有一个正整数 $m$。

后面依次输入 $m$ 棵无向树，每棵无向树先用一行输入结点个数 $n$，结点就用 $1$ 到 $n$ 表示，然后用 $n-1$ 行输入 $n-1$ 条无向边，每行有两个 $1$ 到 $n$  之间的不同的正整数，用一个空格隔开，代表这两个结点之间有无向边。两棵树之间无空行。

## 输出格式

第一行输出一个正整数，即输入中不计实质同构包含无向树的个数 $m_0\ (1\leq m_0\leq m)$。

第二行包含不严格递增的 $m_0$ 个正整数，表示这 $m_0$ 棵无向树的简化树结点个数。相邻两数用一个空格隔开。
## 样例

### 样例输入 #1
```
2
4
1 4
2 4
3 4
5
1 3
2 3
3 4
4 5
```
### 样例输出 #1
```
1
4
```
## 提示

#### 数据范围

对于 $100\%$ 的数据，$2\leq m\leq 20, 2\leq n\leq 10^4$。


---

---
title: "「SWTR-5」String"
layout: "post"
diff: 省选/NOI-
pid: P6652
tag: ['动态规划 DP', 'O2优化', '广度优先搜索 BFS', '哈希 hashing']
---
# 「SWTR-5」String
## 题目描述

小 A 有一个字符串 $t$。他可以进行以下操作：切掉 $t$ 的一个前/后缀，满足切掉的前/后缀为**切割后** $t$ 的子串。小 A 想得到字符串 $s$，请问他最少需要进行多少次操作。无解输出 $-1$。
## 输入格式

两行字符串分别表示 $t,s$。
## 输出格式

一行一个整数，表示答案。
## 样例

### 样例输入 #1
```
abbabb
ba
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
fxofoxxooffoxooo
fox
```
### 样例输出 #2
```
8
```
### 样例输入 #3
```
abcdefghijklmnopq
rstuvwxyzz
```
### 样例输出 #3
```
-1
```
### 样例输入 #4
```
ycxcy
cxy
```
### 样例输出 #4
```
-1
```
## 提示

「样例说明」

样例 $1$：$\texttt{abbabb}\to \texttt{abba}\to \texttt{bba}\to \texttt{ba}$。方案不唯一。

样例 $2$：$\texttt{fxofoxxooffoxooo}\to\texttt{xofoxxooffoxooo}\to\texttt{foxxooffoxooo}\to\texttt{xooffoxooo}\to\texttt{ffoxooo}\to\texttt{ffoxoo}\to\texttt{ffoxo}\to\texttt{ffox}\to\texttt{fox}$。方案不唯一。

「数据范围与约定」

**本题采用捆绑测试。**

- Subtask 1（1 points）：$s=t$。
- Subtask 2（9 points）：$s$ 仅包含字母 $\texttt{a}$。
- Subtask 3（15 points）：$|t|\leq 100$。
- Subtask 4（17 points）：$|t|\leq 500$。
- Subtask 5（18 points）：$|t|\leq 1.5\times 10^3$。
- Subtask 6（15 points）：$|s|=4$，*数据随机。
- Subtask 7（25 points）：无特殊限制。

对于 $100\%$ 的数据：$1 \leq |s| \leq |t| \leq 5\times 10^3$，字符集 $\in[\texttt{a,z}]$。

*数据随机：$s,t$ 字符均随机，字符集 $\in[\texttt{a,c}]$。

**请注意常数优化。**

---

「题目来源」

[Sweet Round 05](https://www.luogu.com.cn/contest/28195) E。    
idea & solution：[Isaunoya](https://www.luogu.com.cn/user/96580) & [Alex_Wei](https://www.luogu.com.cn/user/123294)。


---

---
title: "[YsOI2020] 造林"
layout: "post"
diff: 省选/NOI-
pid: P6653
tag: ['树形数据结构', 'O2优化', '树形 DP', '哈希 hashing']
---
# [YsOI2020] 造林
## 题目背景

「承前」

Ysuperman 响应号召，决定在幼儿园外造林。

呐呐，如果这样的话，Ysuperman 便能在这炎热的夏天与小朋友们玩游戏了呢。
## 题目描述

为了落实环保工作，Ysuperman 购进了一批树，它们都长一个样。由于树还没有种下去，所以这些树还没有根，可以认为是**无根树**。

Ysuperman 觉得全都种长得一样的树太无聊了，于是 TA 请到了园艺公司帮 TA 规划。园艺公司提供给了 TA 一个方法——「嫁接」。

下面给出「嫁接」操作的定义：

定义「叶子节点」为树上度数为 $1$ 的节点。
 
「嫁接」操作指：在一棵**无根树**上接入一个新的「叶子节点」。

例如：  
![](https://cdn.luogu.com.cn/upload/image_hosting/jfaksqwy.png)

图 2 是由图 1 的树进行一次合法的嫁接操作后得到的树，图 3 也是由图 1 的树进行一次合法的嫁接操作后得到的树。

那么，我们还知道，树有一个基本属性：「品种」。

一棵树的「品种」是指**每个点的最大子树大小所构成的可重集**。

两棵树的「品种」不同，当且仅当**每个点的最大子树大小所构成的可重集不同**。

这里的一个点的**最大子树大小**指将这个点删掉后**最大的联通块所包含的点数**。

例如：  
![](https://cdn.luogu.com.cn/upload/image_hosting/zzyznfl7.png)

图 4 的树的每个点的最大子树大小所构成的可重集为：$ \{ 2,2,3,3 \} $  
图 5 的树的每个点的最大子树大小所构成的可重集为：$ \{ 2,2,3,3 \} $  
图 6 的树的每个点的最大子树大小所构成的可重集为：$ \{ 1,3,3,3 \} $  
所以说，图 4 的树与图 5 的树「品种」相同，与图 6 的树「品种」不同。

Ysuperman 想知道，通过一次「嫁接」操作，可以构造出的树包含多少不同的「品种」，以及对于每个「品种」，有多少不同的「嫁接」方法可以构造。请**从小到大**输出每个「品种」的「嫁接」方法数。

两个「嫁接」方案不同，当且仅当在「嫁接」操作中与新接入的「叶子节点」直接相连的点不同。

## 输入格式

第一行一个数 $n$ 。  
接下来 $n-1$ 行，每行两个数 $u,v$ 表示 $u,v$ 之间有一条**无向边**。
## 输出格式

第一行一个数 $cnt$，表示可以构造出的树包含多少不同的「品种」。  
第二行到第 $cnt+1$ 行，**从小到大**输出每个「品种」的「嫁接」方法数。
## 样例

### 样例输入 #1
```
5
1 2
2 3
3 4
4 5

```
### 样例输出 #1
```
3
1
2
2

```
### 样例输入 #2
```
7
1 2
1 3
2 4
2 5
3 6
3 7

```
### 样例输出 #2
```
3
1
2
4

```
### 样例输入 #3
```
25
15 9
22 15
23 22
25 15
13 23
6 22
12 15
1 23
19 13
18 9
11 15
17 1
4 25
3 1
8 9
20 1
10 18
21 20
16 8
2 22
24 1
7 19
5 16
14 7

```
### 样例输出 #3
```
17
1
1
1
1
1
1
1
1
1
1
2
2
2
2
2
2
3

```
## 提示

**本题采用捆绑测试。**
### 样例解释 1
可以构造出 1 种「品种」为 $\{2,4,4,5,5,5\}$ 的树。  
可以构造出 2 种「品种」为 $\{3,3,4,5,5,5\}$ 的树。  
可以构造出 2 种「品种」为 $\{3,3,4,4,5,5\}$ 的树。
### 样例解释 2
可以构造出 1 种「品种」为 $\{3,5,5,7,7,7,7,7\}$ 的树。  
可以构造出 2 种「品种」为 $\{4,4,5,7,7,7,7,7\}$ 的树。  
可以构造出 4 种「品种」为 $\{4,4,5,6,7,7,7,7\}$ 的树。


对于 100% 的数据，满足 $1 \le n\le2\cdot 10^6$。

定义「链」为所有节点度数不超过 $2$ 的树。  
定义「菊花」为包含 $n-1$ 个「叶子节点」的树。

特殊性质 1：保证树的形态为一条「链」。  
特殊性质 2：保证树的形态为一朵「菊花」。  
特殊性质 3：保证树的形态为一棵完全二叉树。

| subtask | $n$ | 特殊性质 | 分值 | 时间限制 |
| :-----------: | :-----------: | :-----------: | :--------:| :---------:|
| 1 | $\le 2\cdot 10^6$ | 2 | 2 | 4s |
| 2 | $\le 2\cdot 10^6$ | 1 | 3 | 4s |
| 3 | $\le 300$ | 无 | 5 | 1s |
| 4 | $\le 2\cdot10^6$ | 3 | 7 | 4s |
| 5 | $\le 5000$ | 无 | 23 | 1s |
| 6 | $\le 5\cdot10^4$ | 无 | 29 | 2s |
| 7 | $\le 2\cdot10^6$ | 无 | 31 | 4s |

### 提示：

如果你不知道完全二叉树是什么意思，Ysuperman 提供了一个链接：[Link](https://zh.wikipedia.org/zh/%E4%BA%8C%E5%8F%89%E6%A0%91#%E5%AE%8C%E5%85%A8%E4%BA%8C%E5%8F%89%E6%A0%91)。

输入输出较大，请使用较快的输入输出方式。

如果您使用了所需栈空间较大的递归算法，可以在本地（NOI linux 下）先使用 ```sudo su``` 获取权限，再使用 ```ulimit -s unlimited ``` 命令开启无限栈。

题目并不难。


---

---
title: "「Wdsr-2」白泽教育"
layout: "post"
diff: 省选/NOI-
pid: P6736
tag: ['2020', '递归', '数论', '洛谷原创', 'O2优化', '哈希 hashing', '根号分治', '欧拉降幂']
---
# 「Wdsr-2」白泽教育
## 题目背景

上白泽慧音在给雾之湖的妖精们讲课。

某天，慧音在上数学课时，提到了一种非常有趣的记号：**高德纳箭号表示法**。它可以用来描述非常巨大的数字。~~比如紫的年龄。~~

对于非负整数 $a, b$ 和正整数 $n$，高德纳箭号表示法的定义为：

$$a \uparrow^n b = \begin{cases}
1\ (b = 0) \\
a^b\ (n = 1\ \operatorname{and}\ b > 0) \\
a \uparrow^{n - 1} (a \uparrow^n (b - 1))\ (n > 1\ \operatorname{and}\ b > 0)
\end{cases}$$

一些简单的例子：

- $2 \uparrow 31 = 2^{31} = 2147483648$

- $2 \uparrow \uparrow 4 = 2^{2^{2^2}} = 2^{2^4} = 2^{16} = 65536$

注：
1. $a \uparrow b$ 与 $a \uparrow^1 b$ 相同；

2. $a \uparrow \uparrow b$ 与 $a \uparrow^2 b$ 相同；

3. 请注意幂运算的顺序。
## 题目描述

慧音希望琪露诺解决以下关于 $x$ 的方程：

$$a \uparrow^n x \equiv b \pmod p$$

其中，$a, n, b, p$ 为已知的常数，$x$ 为未知数。

琪露诺被高德纳箭号表示法搞得云里雾里的，但是她不想被头槌。你能帮帮她吗？
## 输入格式

**本题有多组测试数据。**

第一行，一个整数 $T$，表示数据组数。

对于每组数据：

一行，四个整数 $a, n, b, p$。
## 输出格式

对于每组数据，输出一行，一个整数，如果原方程有解，输出该方程的最小非负整数解；否则，输出 $-1$。
## 样例

### 样例输入 #1
```
3
2 1 1 3
3 1 2 7
7 1 2 4
```
### 样例输出 #1
```
0
2
-1
```
### 样例输入 #2
```
3
2 2 4 7
3 2 4 6
5 2 1 3
```
### 样例输出 #2
```
2
-1
0
```
### 样例输入 #3
```
3
4 3 5 8
2 3 9 11
6 3 1 5
```
### 样例输出 #3
```
-1
3
0
```
## 提示

**本题开启捆绑测试。**

| Subtask | $n$ | $p$ | $T$ | 分值 | 时限 |
| :------: | :------: | :------: | :------: | :------: | :------: |
| $1$ | $n = 1$ | $2 \leq p \leq 10^9$ 且 $p$ 为质数 | $1 \leq T \leq 100$ | $15 \operatorname{pts}$ | $2.00 \operatorname{s}$ |
| $2$ | $n = 2$ | 无特殊限制 | $1 \leq T \leq 5 \times 10^3$ | $25 \operatorname{pts}$ | $1.00 \operatorname{s}$ |
| $3$ | $n = 3$ | 无特殊限制 | 无特殊限制 | $60 \operatorname{pts}$ | $2.00 \operatorname{s}$ |

对于 $100\%$ 的数据，$1 \leq a \leq 10^9$，$1 \leq n \leq 3$，$0 \leq b < p \leq 10^9$，$1 \leq T \leq 2 \times 10^4$。


---

---
title: "[ICPC 2014 WF] Maze Reduction"
layout: "post"
diff: 省选/NOI-
pid: P6896
tag: ['2014', '哈希 hashing', 'ICPC']
---
# [ICPC 2014 WF] Maze Reduction
## 题目描述

Jay runs a small carnival that has various rides and attractions. Unfortunately, times are tough. A recent roller coaster accident, flooding in the restrooms, and an unfortunate clown incident have given Jay’s carnival a bad reputation with the public. With fewer paying customers and reduced revenue, he will need to cut some costs to stay in business.

One of the biggest carnival attractions is a large, confusing maze. It consists of a variety of circular rooms connected by narrow, twisting corridors. Visitors love getting lost in it and trying to map it out. It has come to Jay’s attention that some of the rooms might be effectively identical to each other. If that’s the case, he will be able to reduce its size without anyone noticing.

Two rooms $A$ and $B$ are effectively identical if, when you are dropped into either room $A$ or $B$ (and you know the map of the maze), you cannot tell whether you began in $A$ or $B$ just by exploring the maze. The corridor exits are evenly spaced around each room, and you cannot mark or leave anything in a room (in particular, you cannot tell whether you have previously visited it). The only identifying feature that rooms have is their number of exits. Corridors are also twisty enough to be indistinguishable from each other, but when you enter a room you know which corridor you came from, so you can navigate a little by using the order they appear around the room.

Jay has appealed to the Association for Carnival Mazery for help. That’s you! Write a program to determine all the sets of effectively identical rooms in the maze.
## 输入格式

The input consists of a single test case. The first line contains an integer $n$, the number of rooms in the maze ($1 \leq n \leq 100$). Rooms are numbered from 1 to $n$. Following this are $n$ lines, describing each room in order. Each line consists of an integer $k$, indicating that this room has $k$ corridors ($0 \leq k < 100$), and then $k$ distinct integers listing the rooms each corridor connects to (in clockwise order, from an arbitrary starting point). Rooms do not connect to themselves.
## 输出格式

Display one line for each maximal set of effectively identical rooms (ignoring sets of size 1) containing the room numbers in the set in increasing order. Order the sets by their smallest room numbers. If there are no such sets, display none instead.
## 样例

### 样例输入 #1
```
13
2 2 4
3 1 3 5
2 2 4
3 1 3 6
2 2 6
2 4 5
2 8 9
2 7 9
2 7 8
2 11 13
2 10 12
2 11 13
2 10 12

```
### 样例输出 #1
```
2 4
5 6
7 8 9 10 11 12 13

```
### 样例输入 #2
```
6
3 3 4 5
0
1 1
1 1
2 1 6
1 5

```
### 样例输出 #2
```
none

```
## 提示

Time limit: 2000 ms, Memory limit: 1048576 kB. 

 International Collegiate Programming Contest (ACM-ICPC) World Finals 2014
## 题目翻译

Jay经营着一家小型游乐场，其中有各种游乐设施和景点。不幸的是，由于顾客和收入的锐减，他将需要削减成本以维持业务。

一个大型迷宫是最大的景点之一，它由不同的圆形房间组成。这些房间通过狭窄且扭曲的走廊相连，而某些游客喜欢迷失在迷宫中并试图将其绘制出来。Jay已经注意到，有些房间可能一模一样。如果出现这样的情况，他就能减小迷宫的尺寸而不会被任何人发现。

当您进入AA或是BB房间（并且您知道迷宫的地图）时，两个房间AA和BB是相同的，那么您仅通过探索迷宫就无法分辨是从AA还是BB开始行动。走廊出口在每个房间周围均等分布，您不能在房间内标记或留下任何东西（您无法判断是否进入过该房间）。房间唯一的标识是出口数量。走廊很曲折，彼此之间无法区分，但是当您进入一个房间时，您会知道您来自哪个走廊，因此您可以通过它们在房间周围出现的顺序来指引方向。

Jay向你寻求帮助，请编写程序以找出迷宫中所有相同房间的集合。

Translated by EndlIa


---

---
title: "[COCI 2019/2020 #3] Lampice"
layout: "post"
diff: 省选/NOI-
pid: P7206
tag: ['2019', '二分', '哈希 hashing', 'COCI（克罗地亚）']
---
# [COCI 2019/2020 #3] Lampice
## 题目描述

Mirko 用 $N$ 个 LED 灯来装饰圣诞树，它们的颜色是已知的，并且通过 $(N-1)$ 条电线连接。

Mirko 在大功告成后，仔细地品味自己的作品。他被一种叫作「回文段」的特殊图案所吸引。「回文段」指一条从 $u$ 至 $v$ 的路径，它满足从 $u$ 到 $v$ 的路径所包含灯的颜色等于从 $v$ 到 $u$ 的路径所包含灯的颜色。

求出圣诞树中最长的「回文段」。
## 输入格式

第一行，输入一个整数 $N$，表示 LED 灯的数量。

第二行，输入一个由 $N$ 个英文小写字母组成的字符串，其中第 $i$ 个字母代表第 $i$ 个灯的颜色。

接下来的 $(N-1)$ 行，每行输入两个整数 $A,B$，表示 $A,B$ 之间用一条电线连接。
## 输出格式

输出圣诞树中最长的「回文段」。
## 样例

### 样例输入 #1
```
7
imanade
1 2
2 3
3 4
4 5
5 6
6 7
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
4
aabb
1 2
1 3
3 4
```
### 样例输出 #2
```
2
```
### 样例输入 #3
```
8
acdbabcd
1 6
6 7
6 3
3 4
4 5
5 2
8 5
```
### 样例输出 #3
```
5
```
## 提示

#### 数据范围及约定

| Subtask | 分值 | 数据范围及约定 |
| :----------: | :----------: | :----------: |
| $1$ | $17$ | $N \le 3000$ |
| $2$ | $25$ | 第 $i$ 个与第 $i+1$ 个灯直接相连（$1 \le i \lt N$） |
| $3$ | $31$ | 至多有 $100$ 个灯与另一个灯直接相连 |
| $4$ | $37$ | 无 |

对于 $100\%$ 的数据，$1 \le N \le 5 \times 10^4, 1 \le A,B \le N, A \neq B$。

#### 说明

**本题分值按 COCI 原题设置，满分 $110$。**

**题目译自 [COCI2019-2020](https://hsin.hr/coci/archive/2019_2020/) [CONTEST #3](https://hsin.hr/coci/archive/2019_2020/contest3_tasks.pdf)  _T4 Drvca_ 。**


---

---
title: "[CERC2018] The ABCD Murderer"
layout: "post"
diff: 省选/NOI-
pid: P7456
tag: ['字符串', '2018', '哈希 hashing', 'AC 自动机', 'KMP 算法', '后缀数组 SA', 'ICPC']
---
# [CERC2018] The ABCD Murderer
## 题目描述

**译自[ [CERC2018]](https://contest.felk.cvut.cz/18cerc/) [The ABCD Murderer](https://contest.felk.cvut.cz/18cerc/solved/abcd.pdf)**

Oscar 特别喜欢看犯罪电影。他钦佩那些罪犯，因为他们富有创造力。他也想展示他的创造力。但很可惜的是，他没什么经验，也想不出来什么原创伎俩。所以他想从已有的招数中寻找灵感。他一直喜欢看罪犯从报纸上剪下字母，然后用这些字母拼勒索信的桥段。然而 Oscar 根本不想抄袭，所以他自己想了一个这种方法的变体。他觉得把字母一个一个拼成文本既无聊又费时间。所以他决定通过剪下一整个单词的方式拼出自己的勒索信。

Oscar 买来一些主流报纸，这样他几乎就有了无限的单词库。他可以多次剪出任意特定的单词。然而，他还是被报纸中出现的的单词集限制。问题是一些单词根本没在报纸中出现。为了让这项工作更简单，他决定去除勒索信中所有的标点符号和空格并且忽略字母的大小写。他同时允许剪出的单词互相重叠，只需要重叠部分相同。现在 Oscar 想知道他至少要剪下多少次单词才能拼成他想要的勒索信。
## 输入格式

第一行包含一个整数 $L$，表示在报纸中发现的单词数；

下一行包含勒索信的内容 $s$。保证内容非空并且只包含小写英文字母。

接下来 $L$ 行，每行包含一个在报纸中出现的单词 $a_i$，保证只出现小写英文字母。这些单词中没有空串，也没有比勒索信长的单词。所有报纸中单词在输入中出现至少一次。
## 输出格式

输出 Oscar 最少要从报纸中剪下多少次单词才能组成勒索信、如果不能组成，输出 $-1$ 。每个单词都要被记实际从报纸剪下那么多次。
## 样例

### 样例输入 #1
```
3
aaaaa
a
aa
aaa
```
### 样例输出 #1
```
2
```
### 样例输入 #2
```
5
abecedadabra
abec
ab
ceda
dad
ra
```
### 样例输出 #2
```
5
```
### 样例输入 #3
```
9
icpcontesticpc
international
collegiate
programming
contest
central
europe
regional
contest
icpc
```
### 样例输出 #3
```
3
```
## 提示

$1≤L,|s|,∑|a_i|≤3×10^5$


---

---
title: "[ONTAK2015] Bajtocja"
layout: "post"
diff: 省选/NOI-
pid: P8026
tag: ['2015', '并查集', '树上启发式合并', '哈希 hashing']
---
# [ONTAK2015] Bajtocja
## 题目描述

给定 $d$ 张无向图，每张图都有 $n$ 个点。一开始，在任何一张图中都没有任何边。接下来有 $m$ 次操作，每次操作会给出 $a, b, k$，意为在第 $k$ 张图中的点 $a$ 和点 $b$ 之间添加一条无向边。你需要在每次操作之后输出有序数对 $(a, b)$ 的个数，使得 $1 \leq a, b \leq n$，且 $a$ 点和 $b$ 点在 $d$ 张图中都连通。
## 输入格式

第一行，三个整数 $d, n, m$；

接下来 $m$ 行，每行三个整数 $a, b, k$。
## 输出格式

$m$ 行，每行一个整数，表示所求的值。
## 样例

### 样例输入 #1
```
3 4 10
1 2 1
2 1 2
1 2 3
3 4 1
1 3 2
2 3 3
2 4 2
3 4 3
3 4 2
1 3 1
```
### 样例输出 #1
```
4
4
6
6
6
6
6
8
8
16
```
## 提示

对于 $100\%$ 的数据，$1 \leq d \leq 200$，$1 \leq n \leq5 \times 10^3$，$1\leq m \leq 10^6$，$1 \leq a, b \leq n$，$1 \leq k \leq d$。


---

---
title: "[CSP-S 2022] 星战"
layout: "post"
diff: 省选/NOI-
pid: P8819
tag: ['2022', 'O2优化', '哈希 hashing', 'CSP-S 提高级']
---
# [CSP-S 2022] 星战
## 题目描述

在这一轮的星际战争中，我方在宇宙中建立了 $n$ 个据点，以 $m$ 个单向虫洞连接。我们把终点为据点 $u$ 的所有虫洞归为据点 $u$ 的虫洞。

战火纷飞之中这些虫洞很难长久存在，敌人的打击随时可能到来。这些打击中的有效打击可以分为两类：

1. 敌人会摧毁某个虫洞，这会使它连接的两个据点无法再通过这个虫洞直接到达，但这样的打击无法摧毁它连接的两个据点。
2. 敌人会摧毁某个据点，由于虫洞的主要技术集中在出口处，这会导致该据点的所有还未被摧毁的虫洞被一同摧毁。而从这个据点出发的虫洞则**不会摧毁**。

注意：摧毁只会导致虫洞不可用，而不会消除它的存在。

为了抗击敌人并维护各部队和各据点之间的联系，我方发展出了两种特种部队负责修复虫洞：

- A 型特种部队则可以将某个特定的虫洞修复。
- B 型特种部队可以将某据点的所有损坏的虫洞修复。

考虑到敌人打击的特点，我方并未在据点上储备过多的战略物资。因此只要这个据点的某一条虫洞被修复，处于可用状态，那么这个据点也是可用的。

我方掌握了一种苛刻的空间特性，利用这一特性我方战舰可以沿着虫洞瞬移到敌方阵营，实现精确打击。

为了把握发动反攻的最佳时机，指挥部必须关注战场上的所有变化，为了寻找一个能够进行反攻的时刻。总指挥认为：

- 如果从我方的任何据点出发，在选择了合适的路线的前提下，可以进行无限次的虫洞穿梭（可以多次经过同一据点或同一虫洞），那么这个据点就可以**实现反击**。
- 为了使虫洞穿梭的过程连续，尽量减少战舰在据点切换虫洞时的质能损耗，当且仅当**只有一个从该据点出发的虫洞可用**时，这个据点可以**实现连续穿梭**。
- 如果我方所有据点都可以**实现反击**，也都可以**实现连续穿梭**，那么这个时刻就是一个绝佳的**反攻**时刻。

总司令为你下达命令，要求你根据战场上实时反馈的信息，迅速告诉他当前的时刻是否能够进行一次**反攻**。
## 输入格式

输入的第一行包含两个正整数 $n,m$。

接下来 $m$ 行每行两个数 $u,v$，表示一个从据点 $u$ 出发到据点 $v$ 的虫洞。保证 $u \ne v$，保证不会有两条相同的虫洞。初始时所有的虫洞和据点都是完好的。

接下来一行一个正整数 $q$ 表示询问个数。

接下来 $q$ 行每行表示一次询问或操作。首先读入一个正整数 $t$ 表示指令类型：

- 若 $t = 1$，接下来两个整数 $u, v$ 表示敌人摧毁了从据点 $u$ 出发到据点 $v$ 的虫洞。保证该虫洞存在且未被摧毁。
- 若 $t = 2$，接下来一个整数 $u$ 表示敌人摧毁了据点 $u$。如果该据点的虫洞已全部被摧毁，那么这次袭击不会有任何效果。
- 若 $t = 3$，接下来两个整数 $u, v$ 表示我方修复了从据点 $u$ 出发到据点 $v$ 的虫洞。保证该虫洞存在且被摧毁。
- 若 $t = 4$，接下来一个整数 $u$ 表示我方修复了据点 $u$。如果该据点没有被摧毁的虫洞，那么这次修复不会有任何效果。

在每次指令执行之后，你需要判断能否进行一次反攻。如果能则输出 `YES` 否则输出 `NO`。
## 输出格式

输出一共 $q$ 行。对于每个指令，输出这个指令执行后能否进行反攻。
## 样例

### 样例输入 #1
```
3 6
2 3
2 1
1 2
1 3
3 1
3 2
11
1 3 2
1 2 3
1 1 3
1 1 2
3 1 3
3 3 2
2 3
1 3 1
3 1 3
4 2
1 3 2

```
### 样例输出 #1
```
NO
NO
YES
NO
YES
NO
NO
NO
YES
NO
NO

```
## 提示

**【样例解释 \#1】**

虫洞状态可以参考下面的图片, 图中的边表示存在且未被摧毁的虫洞：

![](https://cdn.luogu.com.cn/upload/image_hosting/giqzyc7r.png)

**【样例 \#2】**

见附件中的 `galaxy/galaxy2.in` 与 `galaxy/galaxy2.ans`。

**【样例 \#3】**

见附件中的 `galaxy/galaxy3.in` 与 `galaxy/galaxy3.ans`。

**【样例 \#4】**

见附件中的 `galaxy/galaxy4.in` 与 `galaxy/galaxy4.ans`。

**【数据范围】**

对于所有数据保证：$1 \le n \le 5 \times {10}^5$，$1 \le m \le 5 \times {10}^5$，$1 \le q \le 5 \times {10}^5$。

| 测试点 | $n \le$ | $m \le$ | $q \le$ | 特殊限制 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| $1 \sim 3$ | $10$ | $20$ | $50$ | 无 |
| $4 \sim 8$ | ${10}^3$ | ${10}^4$ | ${10}^3$ | 无 |
| $9 \sim 10$ | $5 \times {10}^5$ | $5 \times {10}^5$ | $5 \times {10}^5$ | 保证没有 $t = 2$ 和 $t = 4$ 的情况 |
| $11 \sim 12$ | $5 \times {10}^5$ | $5 \times {10}^5$ | $5 \times {10}^5$ | 保证没有 $t = 4$ 的情况 |
| $13 \sim 16$ | ${10}^5$ | $5 \times {10}^5$ | $5 \times {10}^5$ | 无 |
| $17 \sim 20$ | $5 \times {10}^5$ | $5\times 10^5$ | $5 \times {10}^5$ | 无 |


---

---
title: "「DBOI」Round 1 人生如树"
layout: "post"
diff: 省选/NOI-
pid: P9399
tag: ['倍增', '二分', 'O2优化', '树链剖分', '树论', '哈希 hashing']
---
# 「DBOI」Round 1 人生如树
## 题目背景

> _永远这么酷 永远永远这么酷_\
_像个冒险家一样 不断探着山顶的路_\
——《Hustle》

张均好望着窗外，朱芝心走过来坐在他旁边，折了一架纸飞机飞出去。他对张均好说，要带着对未来的期待，往前走，别回头。

正如 [命运](https://www.luogu.com.cn/problem/P6773) 所述，每个人的人生都是一棵树。它总在无限的随机与缘分中伸展，有的枝丫茂盛了，有些却也不可避免地枯萎。
## 题目描述

朱芝心用魔法得到了张均好的人生树。

这是一棵 $n$ 个节点的树，节点 $i$ 上有权值 $w_i$。

朱芝心想要观测 $m$ 次张均好的人生：

设**当前**张均好人生树上的节点数量为 $s$。

1. 输入四个整数 $u_1,v_1,u_2,v_2$。令 $u_1\to v_1$ 的简单路径上**顺次组成**的数组为 $a$，$u_2\to v_2$ 的简单路径上**顺次组成**的数组为 $b$。朱芝心认为张均好这两段人生的相似度是 $LRP(a,b)$，希望你求出它。保证 $1\leq u_1,v_1,u_2,v_2 \leq s$。

2. 输入两个整数 $u,w'$。朱芝心观测到了张均好的另外一种可能，因此你需要新建一个点权为 $w'$ 的节点，编号为 $s+1$，建立一条 $(s+1,u)$ 的无向边，其中 $u\leq s$。显然，此后 $s\leftarrow s+1$。

对于两个数组 $a,b$，设它们的相似度 $LRP(a,b)$ 表示最大的 $i$ 满足 $i\leq \min\{|a|, |b|\}$ 且**对于所有** $1\leq j\leq i$，都有 $b_j=a_j+j$。其中 $|a|$ 表示数组 $a$ 的长度。特殊地，若不存在这样的 $i$，则 $LRP(a,b) = 0$。

## 输入格式

第一行三个正整数 $n,m,idx$，分别表示树的节点数量，操作数量和该测试点所在 Subtask 编号。对于样例，有 $idx = 0$。

接下来一行 $n$ 个整数，第 $i$ 个整数表示 $w_i$，即点 $i$ 上的权值。

接下来 $n - 1$ 行，每行两个正整数 $u_i,v_i$，表示有一条 $(u_i,v_i)$ 的无向边。

接下来 $m$ 行，每行一个操作。每行第一个整数是 $opt$，后面的若干整数表示操作的具体内容。$opt=1$ 时表示是操作 $1$，$opt=2$ 时表示是操作 $2$。
## 输出格式

对于每个操作 $1$，输出一行，表示当前询问的 $LRP(a, b)$。
## 样例

### 样例输入 #1
```
9 3 0
7 3 2 4 6 5 5 3 7
1 2
2 3
2 4
4 5
4 6
1 7
7 8
7 9
2 9 10
1 3 5 8 10
1 3 6 8 10
```
### 样例输出 #1
```
4
3
```
### 样例输入 #2
```
13 5 0
15 12 9 11 5 6 16 14 15 10 12 1 2
7 8
5 6
2 9
1 2
4 5
8 2
9 10
2 3
10 11
3 4
3 13
3 12
1 1 6 7 11
1 12 12 13 13
2 1 10
2 2 11
1 14 14 15 15
```
### 样例输出 #2
```
6
1
1
```
## 提示

### 样例解释

对于样例一，第一个操作结束后，$w_{10}=10$，树如图所示：

![](https://s1.ax1x.com/2023/04/26/p9MV9pV.png)

- 对于第二个操作，第一条路径为 $3\to 2\to 4\to 5$，故 $a=\{2, 3, 4, 6\}$，第二条路径为 $8\to 7\to 9\to 10$，故 $b=\{3, 5, 7, 10\}$，由于 $3=2+1$，$5=3+2$，$7=4+3$，$10=6+4$，所以答案为 $4$；
- 对于第三个操作，$a=\{2, 3, 4, 5\}$，$b=\{3, 5, 7, 10\}$，由于 $3=2+1$，$5=3+2$，$7=4+3$，$10\ne 5+4$，所以答案为 $3$。

对于样例二，初始的树如图所示：

![](https://s1.ax1x.com/2023/04/26/p9MVZkR.png)


| Subtask | $n \le$ | $m \le$ | 特殊性质 | 分值 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| Subtask 1 | $5000$ | $5000$ | 无 | $10$ |
| Subtask 2 | $10^5$ | $5\times{10}^4$ | A & B | $30$ |
| Subtask 3 | $10^5$ | $5\times{10}^4$ | B | $30$ |
| Subtask 4 | $10^5$ | $5 \times {10}^4$ | 无 | $20$ | 
| Subtask 5 | $10^5$ | $10^5$ | 无 | $10$ |

特殊性质 A：$v_i=u_i+1$。

特殊性质 B：保证无操作 2。

对于 $100\%$ 的数据，$1\leq n,m\leq 10^5$，$1\leq w_i,w'\leq 10^6$，$1\leq u_i,v_i\leq n$。  



---

---
title: "「TAOI-2」Ciallo～(∠・ω< )⌒★"
layout: "post"
diff: 省选/NOI-
pid: P9576
tag: ['二分', '树状数组', '洛谷原创', 'O2优化', '哈希 hashing', '洛谷月赛']
---
# 「TAOI-2」Ciallo～(∠・ω< )⌒★
## 题目背景

柚子厨差不多得了。

~(·<)~(·<)~(·<)~(·<)~(·<)~(·<)~(·<)~(·<)~(·<)~(·<)~(·<)~(·<)~(·<)~(·<)

![](https://cdn.luogu.com.cn/upload/image_hosting/0nqiwonz.png)
## 题目描述

小 δ 喜欢造词。他学习了一种造词方法。

首先，他拥有一个「模板串」，设为 $s$。然后他会选择一对 $1 \le l \le r \le |s|$，将 $s$ 的第 $l$ 至 $r$ 个字符删掉，把两边的字符串拼起来，他设得到的这个新字符串为 $s'$。

接下来，他会选择一对新的 $1 \le l' \le r' \le |s'|$，然后设 $s'$ 的第 $l'$ 至 $r'$ 个字符组成的字符串为 $s''$。他所造出的这个词就是 $s''$。

例如，如果「模板串」为 $s=\texttt{cciaohalloo}$，那么一种造词方法是，选择 $l=5$，$r=7$，得到 $s'=\texttt{ccialloo}$，然后选择 $l'=2$，$r'=7$，得到 $s''=\texttt{ciallo}$。

现在小 δ 有一个「目标串」 $t$，他想知道有多少种不同的方案，可以使用「模板串」$s$ 造出单词 $t$。定义两种方案相同当且仅当选择的 $l,r,l',r'$ 均相同。
## 输入格式

共两行，分别为字符串 $s$ 和 $t$。
## 输出格式

共一行，代表造出「目标串」$t$ 的方案数。
## 样例

### 样例输入 #1
```
aabbaaba
aba
```
### 样例输出 #1
```
23
```
### 样例输入 #2
```
ciaohallo
ciallo
```
### 样例输出 #2
```
2
```
### 样例输入 #3
```
babacbbaababbacbababbabbbaaabaabababbabbabababba
ababab
```
### 样例输出 #3
```
1535
```
### 样例输入 #4
```
sssssssssssssssssssssssssssssssssssss
sss
```
### 样例输出 #4
```
15470
```
### 样例输入 #5
```
abcbbbcbcbcbacbacbaaabcbcbcbaabacbca
cb
```
### 样例输出 #5
```
3995
```
## 提示

### 数据范围

**本题采用捆绑测试**。

- Subtask 0（6 points）：$|s| \le 400$，$|t| \le 200$。
- Subtask 1（10 points）：$|s| \le 700$，$|t| \le 300$。
- Subtask 2（10 points）：$\forall i,j,s_i=t_j$。
- Subtask 3（10 points）：$|t|=1$。
- Subtask 4（20 points）：$|s| \le 10^4$，$|t| \le 3 \times 10^3$。
- Subtask 5（14 points）：$|t|=2$。
- Subtask 6（30 points）：无特殊限制。

对于所有测试数据，$1 \le |s| \le 4 \times 10^5$，$1 \le |t| \le 2 \times 10^5$。$s,t$ 只包含小写英文字母。


---

---
title: "[NFLSPC #6] 啊，忘记了。"
layout: "post"
diff: 省选/NOI-
pid: P9935
tag: ['字符串', '线段树', 'O2优化', '哈希 hashing', '虚树', '字典树 Trie', 'AC 自动机']
---
# [NFLSPC #6] 啊，忘记了。
## 题目背景

> 好像忘了什么事…… 算了，想必不是什么重要的事吧。
## 题目描述



你在你的电脑上发现了 $n$ 份文本。冥冥之中，你没来由地感觉这似乎全都是一份记录的复制。

- 首先，原始记录是一个长度未知（甚至可以为空）的字符串，称作 **记录串**。对于一份复制，其将记录串切成了三段 **可以为空** 的字符串 **片段**。**每份复制中切割方案不保证相同**。你暂且将这三份 **片段** 依次称作 **前面**，**中间** 和 **后面**。
- 某些复制中的某些片段可能被忘记了。具体而言，前面有可能被替换为 `QIANMIANWANGLE`，中间有可能被替换为 `ZHONGJIANWANGLE`，后面有可能被替换为 `HOUMIANWANGLE`；在发生替换的场合，表示这一段片段被 **完全遗忘** 了；否则，表示该片段被 **完整保存**。
- 你有一种预感，记录串中的所有字符都是 **小写英文字符**。
- $n$ 份复制不一定自洽。

你的目标是，寻找初始的记录串。这个记录串需要满足所有字符均是小写英文字符。你希望其匹配尽量多的复制串。

- 记录串与复制串匹配的要求是，存在记录串的一种划分，使得其中记录串的三段与复制串的三段分别相同，或者复制串中这段划分忘了（此时本段划分中，记录串为任何可以为空的小写英文字符串均合法）。

你希望求出该记录串能匹配的最多复制串数目。**至于记录串本身，你感觉它并不是很重要，所以你不需要求出它**。

> / 我，毋畏遗忘 /
## 输入格式

**为了避免输入过大，输入进行了一定程度的压缩。请务必认真阅读输入格式**。

第一行一个正整数 $n$，表示记录数目。

接下来 $n$ 行，每行三个非空字符串，其中第一段要么是非空小写字符串，要么是 `Q`（表示 `QIANMIANWANGLE`），要么是 `E` 表示这是一段空串（因为空串不可见所以选取 `E` 作为占位符），不存在其它可能；第二段则是非空小写字符串、`Z`（表示 `ZHONGJIANWANGLE`）、`E` 三者之一；最后一段是非空小写字符串、`H`（表示 `HOUMIANWANGLE`）、`E` 三者之一。
## 输出格式

一行一个整数，表示所有记录串中，能匹配的最多的复制的数目。

## 样例

### 样例输入 #1
```
3
nflsalgo Z H
Q nflspc H
Q Z qidong

```
### 样例输出 #1
```
3

```
## 提示

### 样例 1 解释

你希望这个串是 `nflsalgonflspcqidong`。你确信，不会再有其它串比它更匹配现存的记录了。

### 数据范围与约定

对于所有数据，保证输入的所有字符串长度之和不超过 $5\times 10 ^ 5$。

- 子任务 1（$30$ 分）：保证所有复制的 “后面” 段都是 `H`。
- 子任务 2（$70$ 分）：无特殊限制。

Source：NFLSPC #6 K by Troverld


---

---
title: "[USACO23DEC] A Graph Problem P"
layout: "post"
diff: 省选/NOI-
pid: P9984
tag: ['线段树', 'USACO', '并查集', '2023', 'Kruskal 重构树', 'O2优化', '哈希 hashing', '启发式合并']
---
# [USACO23DEC] A Graph Problem P
## 题目描述

为了丰富自己的数学知识，Bessie 选修了一门图论课程，她发现她被下面的问题困住了，请帮帮她！

给出一张连通的无向图，包含编号为 $1\dots N$ 的节点和编号为 $1\dots M$（$2 \le N \le 2\cdot 10^5$，$N - 1 \le M \le 4 \cdot 10^5$）的边，下边的操作将被实施：

1. 假设集合 $S=\{v\}$，变量 $h=0$。
2. 当 $|S|<N$，重复执行：
	1. 仅有一个顶点在集合 $S$ 中的边中，找到编号最小的那条，编号记为 $e$。
    2. 将 $e$ 不在 $S$ 中的那个顶点加入集合 $S$。
    3. 将 $h$ 修改为 $10h+e$。
3. 返回 $h$ 对 $10^9+7$ 取模的值。

输出这个过程的全部返回值。
## 输入格式

第一行包含 $N$ 和 $M$。接下来 $M$ 行，每行包含第 $e$ 条边的顶点 $(a_e,b_e)$，保证图连通，没有重边。
## 输出格式

输出 $N$ 行，第 $i$ 行包含在节点 $i$ 开始过程的返回值。
## 样例

### 样例输入 #1
```
3 2
1 2
2 3
```
### 样例输出 #1
```
12
12
21
```
### 样例输入 #2
```
5 6
1 2
3 4
2 4
2 3
2 5
1 5
```
### 样例输出 #2
```
1325
1325
2315
2315
5132
```
### 样例输入 #3
```
15 14
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
10 11
11 12
12 13
13 14
14 15
```
### 样例输出 #3
```
678925929
678925929
678862929
678787329
678709839
678632097
178554320
218476543
321398766
431520989
542453212
653475435
764507558
875540761
986574081
```
## 提示

### 样例解释 2

考虑在 $i=3$ 开始执行。首先，选择 $2$ 号边，$S=\{3,4\}$，$h=2$。然后，选择 $3$ 号边，$S=\{2,3,4\}$，$h=23$。接着，选择 $1$ 号边，$S=\{1,2,3,4\}$，$h=231$。最后，选择 $5$ 号边，$S=\{1,2,3,4,5\}$，$h=2315$。因此，$i=3$ 的答案是 $2315$。

### 样例解释 3

确保答案对 $10^9+7$ 取模。

### 测试点性质

- 测试点 $4$ 满足 $N,M \le 2000$。
- 测试点 $5-6$ 满足 $N \le 2000$。
- 测试点 $7-10$ 满足 $N \le 10000$。
- 测试点 $11-14$ 满足对于所有边，有 $a_e+1=b_e$。
- 测试点 $15-23$ 没有额外限制。


---

