---
title: "「Cfz Round 9」Lone"
layout: "post"
diff: 入门
pid: P11204
tag: ['数学', '洛谷原创', 'O2优化', '洛谷比赛']
---
# 「Cfz Round 9」Lone
## 题目背景

[Click here (or at the bottom of this page) to download the English version of statements for this contest (PDF).](https://www.luogu.com.cn/fe/api/problem/downloadAttachment/of2k8jng?contestId=205839)
## 题目描述

她有一根长度为 $m$ 的木棍。

她希望你把这根木棍分成 $n$ 根小木棍，使得每一根小木棍的长度均为**正整数**，且从中任选 $3$ 根小木棍都可以通过首尾相连的方式组成一个三角形。

你想求出，你能否满足她的愿望。
## 输入格式

**本题有多组测试数据。**

输入的第一行包含一个正整数 $T$，表示测试数据组数。

接下来依次输入每组测试数据。对于每组测试数据，输入共一行，包含两个整数 $n,m$。
## 输出格式

对于每组测试数据，输出一行一个字符串：

- 若你能满足她的愿望，则输出 `Yes`；
- 若你不能满足她的愿望，则输出 `No`。
## 样例

### 样例输入 #1
```
3
4 7
3 4
5 21
```
### 样例输出 #1
```
Yes
No
Yes
```
## 提示

#### 「样例解释 #1」

对于第 $1$ 组测试数据，可以把木棍分成长度分别为 $1,2,2,2$ 的小木棍。

对于第 $2$ 组测试数据，可以证明不存在满足要求的方案。

对于第 $3$ 组测试数据，其中一种满足要求的方案为把木棍分成长度分别为 $3,4,4,5,5$ 的小木棍。

#### 「数据范围」

对于所有测试数据，保证：

- $1 \le T \le 100$；
- $3 \le n \le m \le 10^9$。

**本题采用捆绑测试。**

- Subtask 0（18 points）：$m \le 500$，$n=3$。
- Subtask 1（15 points）：$n=3$。  
- Subtask 2（32 points）：$n\times 2 \ge m$。  
- Subtask 3（35 points）：无特殊限制。


---

---
title: "「CZOI-R2」糖果"
layout: "post"
diff: 入门
pid: P11371
tag: ['数学', '数论', 'O2优化', '洛谷比赛']
---
# 「CZOI-R2」糖果
## 题目描述

幼儿园里有 $n$ 个小朋友，第 $i$ 个小朋友最开始有 $a_i$ 个糖果。幼儿园老师可以进行无限次操作，每次操作选择一个小朋友，并给他 $k$ 个糖果。

为了避免小朋友因为愤怒而吃掉别的小朋友，幼儿园老师希望所有小朋友的糖果数量相同。若她的目标可以达成，输出 ```YES``` 和她最少的操作次数；若不可以，则直接输出 ```NO```。
## 输入格式

第一行输入 $2$ 个整数 $n,k$，表示小朋友数量、每次操作给予糖果数量。

第二行输入 $n$ 个整数 $a_i$，表示第 $i$ 个小朋友初始的糖果数量。
## 输出格式

第一行输出 ```YES``` 或 ```NO```。若输出 ```YES```，则再输出 $1$ 个整数，表示答案。
## 样例

### 样例输入 #1
```
6 3
1 1 4 5 1 4
```
### 样例输出 #1
```
NO
```
### 样例输入 #2
```
3 2
9 1 5
```
### 样例输出 #2
```
YES 6
```
## 提示

**【数据范围】**

**本题采用捆绑测试**。

- Subtask #1（$20\text{ pts}$）：$n,k\le10^3$，$a_i\le10^3$。
- Subtask #2（$30\text{ pts}$）：$k=1$。
- Subtask #3（$50\text{ pts}$）：无特殊限制。

对于 $100\%$ 的数据，$1\le n,k\le10^5,0 \le a_i\le 2^{31}-1$。


---

---
title: "「FAOI-R5」becoder"
layout: "post"
diff: 入门
pid: P11654
tag: ['模拟', '2025', '洛谷原创', 'O2优化', '洛谷比赛']
---
# 「FAOI-R5」becoder
## 题目背景

**警告：请不要试图使用 AI，使用者按作弊处理。[](U2FsdGVkX1+8wT+JZ1ip+v0oY6hhnMxzAjstIUBCUdCVwJ2Z0rlSh6uXq4IA+5ZrYH1RdrAQA+OJv3OGw4QGK0iXAIoA4YnMa7Kw/ekc7pwrCPvNf3IhE6viz6n/tN1N2c1Rt4hkYR9cwV5eDe0EK8wAzJTkvViv6QdJCaOl5MjmmB8nT2WYOFQnv7w6SF1YxfHxnufxKWTFdB0UYHW6+VMJdiBUCGRu/1sRklBNIS5UOiGnlQuCuaKO3sCUsiAKALbwovP6dJSSZ3iE/Z3R7DTIjrV3j0vGwG2phyR64wvO3d9dsc2djlGauYnyy3sMfQswoW6b41z3hDfeZw/DnXKjhuaGbHs+7Ajqm4TBA+fYvl6cJ91kP9J379ApOCYPrPY1h19IWA9e38qwSVBOKWHHo7H3EmKfkwQOUvLtbc8iBEtXBvFDkY1eVE8n9OKVWpVM4drlBxksDUjAdvgjQrHcjH+hR38X4SwnYkw74UAfVDmPMfj7eRx9RH99Qnz86UfSMf7IwSdRg4apkYQfgd2remtAjn01tRt+44K468y9VLSVX/RfRCbZ9Yyf1IUyAbZMUyBXZ0wqA+J7m841WDvkfbUxUyrmXxx6OMKG8r5tueIc+lS5Ex0rDYYBMybbo4RXvhw0fSPCIDJlXBZkkxV7FGIEJyFRJ+26Z5W+rXmx1blPe2UeTo5SV1ggNMEsRdbKkzwQVr+E2fi8bwknTba5+P0fkoiepvvgszZh+ujJ7cskkprvRrZDwhCZ9I06uBU26O1teI4Bydqfm8zrGdNlMDRX5wT2GnAL/NV80p3w22UHWG4Mv1Vx2E8V/Dd81I8ePKkKhQEbvSmxIujtROCSLQhl8TxBZcUKxPdfseP4uEKdTNGl5y2kQ7o1JpCnP7wpBe3SF6Iab9XvCn3yQxk6PRSMsXUO2rkzZe/KK9Fs9XnULoMHvqehKE4Aksw8NQcmFiQsdLVu0YnN+jjCP5eEVUiSE+6FveWVyD2mIjnkJaTEcoj9jpqcpBTb5DLuAy9GS83aKInoPxZsxe1QF1ug7/K4DglFF0gK9PEHdWbiC/iIImZsWVV8/JfhQaLd+nwePbt1rVaC2X1D9gsY2D6CKGlxDGNfkbvquU/wLzKVG5cEBJcMNANz/y9msVKaWM1kv2uAcM2LW8x4RoSGiaePD/WTCjTgRaccK2op1a2Z46cp2M5iDZ0lgT73CCl9YdPHIn5EOZXN9i42bHMdt7vkA8f+8BiFjs/iYGgHRfMd3b0mmX4PVy3NpcuWSe6TTg1RvG8cBkoI7dFZ3kICQ0N66U9yIzVVDjk28Mu/cuUaBKLWfeS2pTqGpDYMT2p7QPptI/LiKG6ZE5JguXZYTUhqkwp7D5hV48R6Ep+Wr9Joeo3U3tKT6DpQ+CVwOmPt5UZjMLiFBgqWamjnWmgT4i6+xVMkRBM69OpUz9tE9Fw=)**

[$\text {becoder}$ - 最快的中文 OJ](https://www.becoder.com.cn/)。
## 题目描述

$\text {becoder}$ 拥有所有中文 OJ 中最快的评测机，现在评测机需要处理 $n$ 次题目的评测。已知第 $i$ 次题目的评测在某中文 OJ 上跑了 $T_i$ 秒，空间耗费 $M_i$。

$\text {becoder}$ 的评测机实在是太快了，你可以把 $\text {becoder}$ 跑第 $i$ 个评测的时间视为 $\left \lfloor \frac{T_i}{2} \right \rfloor $。

告诉你 $\text {becoder}$ 上 $n$ 次题目评测的时间限制 $t_i$ 和空间限制 $m_i$。以及，在测评 $[L,R]$ 内的题目时，$\text {becoder}$ 的评测机会打瞌睡。

$\text {becoder}$ 的评测机按如下规则评判提交：
- 如果 $\text {becoder}$ 的评测机在打瞌睡，评测结果会返回 ```System Error```；
- 如果 $\text {becoder}$ 的评测机没有打瞌睡，且你的代码空间超限，即 $M_i > m_i$，评测结果会返回 ```Memory Limit Exceeded```；
- 如果 $\text {becoder}$ 的评测机没有打瞌睡，且你的代码空间不超限，时间超限，即 $M_i \le m_i,\left \lfloor \frac{T_i}{2} \right \rfloor > t_i$，评测结果会返回 ```Time Limit Exceeded```。
- 否则，$\text {becoder}$ 评测机会返回 ```Accepted```。

请你输出所有 $\text {becoder}$ 对于每个测评会返回的结果。你不考虑除上述四种返回结果以外的情况。
## 输入格式

第一行三个正整数，$n,L,R$，代表询问的次数，和评测机睡觉的区间。

接下来 $n$ 行，每行两个正整数代表 $T_i,M_i$。

接下来 $n$ 行，每行两个正整数代表 $t_i,m_i$。
## 输出格式

共 $n$ 行，第 $i$ 行一个字符串代表第 $i$ 次评测的结果。
## 样例

### 样例输入 #1
```
5 3 3
10 2
12 4
3 6
8 7
9 3
5 2
5 7
1 7
4 6
10 5
```
### 样例输出 #1
```
Accepted
Time Limit Exceeded
System Error
Memory Limit Exceeded
Accepted
```
## 提示

**本题开启捆绑测试**。

+ Subtask 1（30 pts）：$1 \le n,m \le 10^3$。
+ Subtask 2（30 pts）：$1 \le T_i,M_i,t_i,m_i \le 10^3$。
+ Subtask 3（40 pts）：无附加限制。

对于 $\text{100}\%$ 的数据，$1 \le L \le R \le n \le 10^5,1\le T_i,M_i,t_i,m_i \le 10^9$。


---

---
title: "「MSTOI-R1」MST Find"
layout: "post"
diff: 入门
pid: P12517
tag: ['洛谷原创', '洛谷比赛']
---
# 「MSTOI-R1」MST Find
## 题目描述

给你一个字符串，查询字符串中 `M`，`S` 和 `T` 的个数。

不区分大小写。

保证输入的字符串长度 $n$ 不超过 $10^5$。
## 输入格式

一行输入一个字符串，保证只包含大小写字母和空格。

注意：**空格也属于字符串的一部分**。
## 输出格式

一行输出三个自然数，中间用空格隔开，分别表示字符串中 `M`，`S` 和 `T` 的个数。
## 样例

### 样例输入 #1
```
MinimumSpanningTree MSTqwq
```
### 样例输出 #1
```
4 2 2
```
### 样例输入 #2
```
You must DO your hOMeWork
```
### 样例输出 #2
```
2 1 1
```
## 提示

假设输入的字符串的长度为 $n$，则 $1\le n\le 10^5$，保证只包含大小写字母和空格。


---

