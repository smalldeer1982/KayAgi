---
title: "「CZOI-R1」卡牌"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P10800
tag: ['线段树', '树状数组', 'O2优化']
---
# 「CZOI-R1」卡牌
## 题目背景

Alice 和 Bob 正在玩卡牌游戏。

## 题目描述

每张卡牌有四个属性：攻击、防御、速度、血量。

我们称一张卡牌能胜过另一张卡牌，当且仅当其至少有三个属性都大于另一张卡牌。

Bob 拥有 $m$ 张卡牌，而 Alice 拥有每个属性值在 $[1, n]$ 的所有 $n^4$ 张卡牌。

现在 Alice 想知道：她有多少张卡牌可以胜过所有 Bob 的卡牌？
## 输入格式

第一行包含两个整数 $n, m$，分别表示属性值上限和 Bob 的卡牌数量。

接下来 $m$ 行，每行四个整数 $a_i, b_i, c_i, d_i$，表示 Bob 一张卡牌的属性。
## 输出格式

输出一行一个整数，表示答案对 $2^{32}$ 取模后的结果。
## 样例

### 样例输入 #1
```
5 5
2 2 1 2
3 4 2 4
4 3 2 2
1 4 2 3
1 2 4 4

```
### 样例输出 #1
```
32

```
### 样例输入 #2
```
10 10
7 8 5 2
5 9 9 4
3 8 4 3
5 6 5 1
5 5 2 4
9 5 5 1
3 7 2 5
4 4 5 4
9 6 1 5
3 7 3 7

```
### 样例输出 #2
```
243

```
## 提示

**【数据范围】**

**本题采用捆绑测试**。

- Subtask #1（$10\text{ pts}$）：$n, m \le 50$。
- Subtask #2（$10\text{ pts}$）：$n, m \le 5 \times 10^3$。
- Subtask #3（$20\text{ pts}$）：$d_i = 1$。
- Subtask #4（$20\text{ pts}$）：$n, m \le 10^5$。
- Subtask #5（$40\text{ pts}$）：无特殊限制。

对于所有测试数据，$1 \le n, m \le 5 \times 10^5$，$1 \le a_i, b_i, c_i, d_i \le n$。


---

---
title: "[COTS 2017] 模板 Z1"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P11288
tag: ['动态规划 DP', '2017', '线段树', '树状数组', '容斥原理', 'COCI（克罗地亚）']
---
# [COTS 2017] 模板 Z1
## 题目背景


译自 [Izborne Pripreme 2017 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2017/) D2T2。$\texttt{4s,0.5G}$。

## 题目描述


> **题目**（【模板】RMQ）。
>
> 给定整数序列 $a_1,a_2,\cdots,a_n$，值域为 $[0,h)$。
> 
> 有 $m$ 次询问。第 $i$ 次询问给定 $l_i,r_i$，求出 $\displaystyle \max_{k\in [l_i,r_i]} \{a_k\}$。


给定 $n,m,h$，每个询问和对应的答案。求出一共有多少个可能的 $a$ 序列满足条件。只需要求出答案对 $(10^9+7)$ 取模后的结果。
## 输入格式



第一行，三个正整数 $n,m,h$;

接下来 $m$ 行，每行三个整数 $l_i,r_i,x_i$，表示 $\displaystyle \max_{k\in [l_i,r_i]} \{a_k\}=x_i$。
## 输出格式

输出一行一个整数，表示答案对 $(10^9+7)$ 取模后的结果。

## 样例

### 样例输入 #1
```
3 2 3
1 2 1
2 2 0
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
7 10 3
1 3 1
3 4 1
3 6 2
4 5 2
1 1 1
1 2 1
3 3 0
1 1 1
3 3 0
3 6 2
```
### 样例输出 #2
```
18
```
## 提示


#### 样例解释

样例 $1$ 解释：只有 $[1,0,0]$，$[1,0,1]$，$[1,0,2]$ 满足条件。

#### 数据范围

对于 $100\%$ 的数据，保证：

- $1\le n,m,h\le 10^6$；
- $1\le l_i\le r_i\le n$；
- $0\le x_i\lt h$。


| 子任务编号 | $n\le $ |得分 |  
| :--: | :--: | :--: | 
| $ 1 $    | $ 100 $    | $ 20 $   |  
| $ 2 $    | $ 10^3 $   |   $ 30 $   |  
| $ 3 $    | $10^6$ |  $ 50 $   |  





---

---
title: "[集训队互测 2024] 人间应又雪"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P12483
tag: ['动态规划 DP', '二分', '集训队互测', '树状数组', '2024', '动态规划优化']
---
# [集训队互测 2024] 人间应又雪
## 题目描述

长度为 $n$ 的街道被积雪覆盖，将街道划分为 $n$ 段，第 $i$ 段的积雪量为 $a_i$，保证 $0\le a_i\le m$ 且 $a_i$ 为整数。

天依与言和要来清理积雪，每次清理有 $2$ 种选择。

+ 天依从位置 $1$ 走到位置 $x$，将积雪清理掉 $c$，再走回位置 $1$，同时，因为在雪地上移动，位置 $1\sim x$ 的积雪量减少 $1$，即 $\forall i\in[1,x-1],a_i:=a_i-1,a_x:=a_x-c-1$。
+ 言和从位置 $n$ 走到位置 $x$，将积雪清理掉 $c$，再走回位置 $n$，同时，因为在雪地上移动，位置 $x\sim n$ 的积雪量减少 $1$，即 $\forall i\in[x+1,n],a_i:=a_i-1,a_x:=a_x-c-1$。。

任意时刻，积雪量对 $0$ 取 $\max$。

天依与言和想知道，最少进行多少次清理后（**即最小化两人清理次数总和**），能将所有积雪清除，即 $\forall i\in [1,n],a_i=0$。
## 输入格式

**本题有多组测试数据。**

首先输入一行两个数 $T,tid$，$T$ 表示数据组数，$tid$ 表示子任务编号（样例的子任务编号为 $0$）。

对于每组数据：

第一行三个整数 $n,m,c$。

第二行 $n$ 个整数 $a_{1\sim n}$。
## 输出格式

对于每组数据，输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
1 0
5 5 1
1 3 2 3 1
```
### 样例输出 #1
```
2
```
## 提示

### 样例解释 1

天依走到位置 $4$ 清理，积雪量变为 $[0,2,1,1,1]$。

言和走到位置 $2$ 清理，积雪量变为 $[0,0,0,0,0]$。

共 $2$ 次清理。

### 样例解释 2

见附加文件中的 `snow.in` 与 `snow.ans`。  
这个样例中有 $100$ 组 $n=10,m=10$ 的数据。

### 数据范围

对于 $100\%$ 的数据，$1\le T\le 10^5$，$1\le n,m\le 5\times 10^5$，$\sum n,\sum m\le 10^6$，$0\le a_i\le m$，$0\le c\le 5\times 10^5$。

| 子任务编号 |        $n$         |        $m$         |            特殊限制             | 分值 | 子任务依赖 |
| :--------: | :----------------: | :----------------: | :-----------------------------: | :--: | :--------: |
|    $1$     | $\le 5\times 10^5$ | $\le 5\times 10^5$ |              $c=0$              | $2$  |            |
|    $2$     | $\le 5\times 10^5$ |      $\le 2$       |               无                | $3$  |            |
|    $3$     |      $\le 5$       |      $\le 5$       |            $T\le 10$            | $5$  |            |
|    $4$     |      $\le 50$      |      $\le 50$      |     $\sum n,\sum m\le 200$      | $10$ |    $3$     |
|    $5$     |     $\le 300$      |     $\le 300$      |     $\sum n,\sum m\le 600$      | $10$ |    $4$     |
|    $6$     |     $\le 2000$     |     $\le 2000$     |     $\sum n,\sum m\le 4000$     | $10$ |    $5$     |
|    $7$     | $\le 5\times 10^4$ | $\le 5\times 10^4$ | $c\le 20,\sum n,\sum m\le 10^5$ | $20$ |            |
|    $8$     | $\le 5\times 10^4$ | $\le 5\times 10^4$ |     $\sum n,\sum m\le 10^5$     | $15$ |   $6,7$    |
|    $9$     | $\le 5\times 10^5$ | $\le 5\times 10^5$ |            $c\le 20$            | $10$ |   $1,7$    |
|    $10$    | $\le 5\times 10^5$ | $\le 5\times 10^5$ |               无                | $15$ |  $2,8,9$   |


---

---
title: "[GCJ 2013 Finals] Let Me Tell You a Story"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13306
tag: ['动态规划 DP', '2013', '树状数组', '组合数学', 'Google Code Jam']
---
# [GCJ 2013 Finals] Let Me Tell You a Story
## 题目描述

The story goes...

A long, long time ago, King Tyrone the Fair had 4 ministers. The first minister (the king's top adviser) was paid 7 gold pieces per week. The second minister was paid 4 gold pieces per week. The third and fourth ministers were each paid 6 gold pieces per week. Unfortunately, Tyrone accidentally forgot the Ministerial Compensation List in the photo copier one day, and the List ended up on the front page of the Kingdom Times newspaper. At this point, the second minister requested to speak to the king, upset that his own salary was lower than that of the lower ranked third minister.

His Fairness King Tyrone saw no other solution than to fire the third minister. After all, lowering the third minister's salary, raising the salary of the second minister, or changing job titles were all unfair solutions to the problem, in the king's opinion. And who are we to question King Tyrone? Of course, firing the third minister did not solve the problem. The second minister continued to complain because his salary was still lower than that of the fourth minister. So King Tyrone fired the fourth minister as well. At this point, neither of the two remaining ministers complained, and everyone lived happily ever after.

...wait a minute. I messed that up. I'm sorry. My memory is not what it used to be. One moment please... Right. King Tyrone the Fair. Four ministers. Paid 7, 4, 6, and 6 respectively. Ah, yes. The ending went like this...

When the second minister complained of unfairness, King Tyrone fired the first minister. Some might say this was a bit harsh, as the first minister wasn't involved in any way, but we shouldn't question King Tyrone. Obviously, the second minister still complained, so King Tyrone simply fired him. Of the remaining two ministers, each one was being paid at least as much as any minister below him, so none of them complained. And everyone lived happily ever after.

Much better... I think? Now I'm not sure anymore. I know for certain that there were $N$ ministers, and I clearly remember their salaries. I also know that every time a minister's salary was lower than the salary of a minister below him, somebody would complain, and some minister got fired; but that it could have been any minister, regardless of whether that minister had anything at all to do with the problem. Ministers continued to be fired until no one complained because all of the salaries were non-increasing. At that point, the firings stopped. But I do not remember in which order the ministers got fired.

Can you help me fix my story? Or at least please tell me how many different stories I could have told. Two stories are different if the sequences of fired ministers in them are not the same.

## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each one consists of two lines. The first line will contain an integer $N$, and the second line will contain $N$ space-separated integers denoting the ministers' salaries, in order from the first minister to the $N$'th minister.
## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the case number (starting from 1) and $y$ is the number of stories I could tell you, modulo 10007.
## 样例

### 样例输入 #1
```
3
4
7 4 6 6
8
90 80 70 60 50 50 40 30
2
7 8
```
### 样例输出 #1
```
Case #1: 14
Case #2: 1
Case #3: 2
```
## 提示

**Limits**

- Each salary will be positive and at most 10000.

**Small dataset (14 Pts, Test set 1 - Visible)**

- Time limit: ~~60~~ 6 seconds.
- $1 \leq T \leq 100.$
- $1 \leq N \leq 100.$

**Large dataset (50 Pts, Test set 2 - Hidden)**

- Time limit: ~~120~~ 12 seconds.
- $1 \leq T \leq 20.$
- For 80% of test cases, $1 \leq N \leq 2000.$
- For all test cases, $1 \leq N \leq 8000.$



---

---
title: "[GDCPC 2024] 田字格"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13351
tag: ['树状数组', '2024', '广东', '扫描线', 'XCPC']
---
# [GDCPC 2024] 田字格
## 题目背景

数据、标程、题解等资源的获取：<https://gitlink.org.cn/thusaa/gdcpc2024>
## 题目描述

小 I 正在学习练字，可当他打开白纸时才想起来自己之前无聊在白纸上将 $n$ 条线段涂黑了，纸上其他部分都是白的。

这 $n$ 条被涂黑的线段都是水平的或者竖直的：以白纸中心为原点，平行白纸的某条边构建 $x$ 轴，另一条边构建 $y$ 轴，那么每条被涂黑的线段的两个端点 $(x_1,y_1)$ 和 $(x_2,y_2)$ 满足：$x_1 = x_2$ 和 $y_1 = y_2$ 恰有一个成立。同时，任意两条水平的线段没有交点，任意两条竖直的线段没有交点。

尽管涂黑的线段很让小 I 糟心，深谙福祸相依的小 I 还是发现，涂黑的 $n$ 条线段构成了若干田字格，而他可以在这些田字格上练字。

田字格可以由三元组 $(x_0, y_0, d)$ 描述。一个三元组 $(x_0, y_0, d)$ 是田字格当且仅当以下条件成立：

- $x_0, y_0 \in \mathbb{R}$, $d \in \mathbb{R}^+$；
- 设 $R = [x_0-d,x_0+d] \times [y_0-d,y_0+d]$，即横坐标在 $[x_0-d,x_0+d]$ 内、纵坐标在 $[y_0-d,y_0+d]$ 内的所有点。那么 $R$ 中被涂黑的部分恰好构成六条线段，且这六条线段分别是 $x=x_0-d,x=x_0,x=x_0+d,y=y_0-d,y=y_0,y=y_0+d$ 这六条直线与 $R$ 的交。

小 I 于是想想算算白纸上有几个田字格，也就是有多少个满足以上条件的三元组 $(x_0,y_0,d)$。但按照惯例小 I 不会算，所以这个任务交给了你。
## 输入格式

输入的第一行一个整数 $n (1 \le n \le 3 \times 10^5)$ 表示线段数。接下来 $n$ 行每行四个整数 $x_1,y_1,x_2,y_2 (-10^9 \le x_1 \le x_2 \le 10^9, -10^9 \le y_1 \le y_2 \le 10^9)$ 表示一条线段。

输入的每条线段满足 $x_1 = x_2$ 和 $y_1 = y_2$ 恰有一个成立，且任意两条满足 $x_1 = x_2$ 的线段间没有交点，任意两条满足 $y_1 = y_2$ 的线段间没有交点。

## 输出格式

输出一行一个整数表示田字格的数量。
## 样例

### 样例输入 #1
```
10
-10 -10 -10 10
0 -10 0 10
10 -10 10 10
-10 -10 10 -10
-10 0 10 0
-10 10 10 10
5 -10 5 10
-10 5 10 5
-2 0 -2 10
-5 -5 10 -5
```
### 样例输出 #1
```
3
```
## 提示

![](https://cdn.luogu.com.cn/upload/image_hosting/9hq95rak.png)

如上图所示，$(5, 5, 5), (5, 0, 5), (5, -5, 5)$ 是三个合法的田字格。注意以下几个都不是田字格：

- $(0, 0, 10)$，因为除了需要的六条线段以外还有其他部分被涂黑了；
- $(-5, 5, 5)$，因为 $x=-5$ 与正方形的交没有被涂黑。


---

---
title: "[NWRRC 2023] H-Shaped Figures"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P13588
tag: ['计算几何', '树状数组', '2023', 'ICPC', '极角排序', 'NWRRC']
---
# [NWRRC 2023] H-Shaped Figures
## 题目描述

After a huge success of the last year's "K-Shaped Figures" problem, we've come up with an innovative "H-Shaped Figures" problem for this year. And we have some plans for the next 24 years.

Let's say that three segments $PQ$, $a$, and $b$ on a plane form an H-shaped figure if:

- point $P$ lies strictly inside segment $a$, and segments $PQ$ and $a$ are not collinear;
- point $Q$ lies strictly inside segment $b$, and segments $PQ$ and $b$ are not collinear;
- segments $a$ and $b$ do not have common points.

![](https://cdn.luogu.com.cn/upload/image_hosting/5qwh7w8x.png)

You are given the coordinates of points $P$ and $Q$, along with $n$ candidate segments for $a$ and $b$. Note that some of the given segments may coincide, but they should still be treated as different segments.

Find the number of possible ways to choose one of the given $n$ segments as $a$ and another one as $b$ to form an H-shaped figure along with the given segment $PQ$.
## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^5$). The description of the test cases follows.

The first line of each test case contains four integers $x_P, y_P, x_Q, y_Q$, denoting the coordinates of points $P$ and $Q$ ($-10^9 \le x_P, y_P, x_Q, y_Q \le 10^9$). Points $P$ and $Q$ do not coincide.

The second line contains a single integer $n$, denoting the number of candidate segments ($2 \le n \le 2 \cdot 10^5$).

The $i$-th of the following $n$ lines contains four integers $x_{i,1}, y_{i,1}, x_{i,2}, y_{i,2}$, denoting the coordinates of the endpoints of the $i$-th segment ($-10^9 \le x_{i,1}, y_{i,1}, x_{i,2}, y_{i,2} \le 10^9$). All segments have positive lengths.

It is guaranteed that the sum of $n$ over all test cases does not exceed $2 \cdot 10^5$.
## 输出格式

For each test case, print the number of ways to form an H-shaped figure using the given segment $PQ$ and two of the candidate segments.
## 样例

### 样例输入 #1
```
1
0 0 4 0
8
0 0 2 1
-1 -1 2 2
3 3 5 -3
0 2 6 -1
2 -2 5 1
-1 1 3 -3
-1 0 2 0
-1 -1 2 2
```
### 样例输出 #1
```
6
```


---

---
title: "期望逆序对"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4223
tag: ['树状数组', '枚举', '期望', '矩阵乘法']
---
# 期望逆序对
## 题目背景

WXH大定理定律n
## 题目描述

mcfx领导的修道院试图通过古老的膜法阵召唤出传说中的膜法处佬WXH。在他把召唤用具准备齐全后，mcfx在众人的键盘声中启动了召唤阵。

这时，天地突然暗了下来，膜法阵中心电闪雷鸣。一道金光从天而降，金色的代码飘在了半空中。不一会，一个登陆界面显现了出来。mcfx仔细观察后发现上面有如下文字：

"WXHCoder是过去到未来所有的题目都有的题库。如果想要登陆它，你们必须解决接下来这道题。"

这道题目是这样子的：给你一个长为$n$的排列，有$k$次操作，每次随机选择两个不同的数交换，问期望逆序对数乘${{n}\choose{2}}^k$的结果。

mcfx发现数据范围是$n,k≤10^{20010910}$，他打算先探究更小的$n,k$。

${n}\choose{2}$表示在$n$个球中选两个的方案数
## 输入格式

第一行两个整数$n,k$

第二行一个$1$到$n$的排列
## 输出格式

输出期望逆序对数乘${{n}\choose{2}}^k$的结果模$10^9+7$
## 样例

### 样例输入 #1
```
5 4 
1 5 4 3 2
```
### 样例输出 #1
```
50000
```
## 提示

$n≤500000,k≤10^9$


---

---
title: "[Ynoi Easy Round 2016] 镜中的昆虫"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4690
tag: ['2016', '树状数组', '递归', 'O2优化', '分治', 'Ynoi']
---
# [Ynoi Easy Round 2016] 镜中的昆虫
## 题目背景

镜子的世界里会有美丽的东西吗？

镜子的世界里会有快乐的事情吗？

镜子世界的我，像我一样摆着一副无聊的表情

——出自《镜之国的爱丽丝》

![](https://cdn.luogu.com.cn/upload/pic/21104.png)

两个少女的战斗故事

文学代表强烈的意志，化学是对抗物理世界的力量

她们只有这两样对抗现实的武器

![](https://cdn.luogu.com.cn/upload/pic/21105.png)

啊，勒布雷！

我今天要登上乳白色的月球了！

不需要发明是机器，真是如此，我要一跃而出！

没错朋友！那个月亮的世界！

才是为我们创造的世界！

不止一个我所爱的人，大概都被放逐到那里...然后在等着我...

苏格拉底！伽利略！

物质的基本要素的灵魂就是...

这是...不，这有问题...哥白尼说过！

没错朋友们，究竟为何，会中了魔障？

究竟为何，会中了魔障，他到底去双桅战船上干什么呢？

作为哲学家！

物理学家！

诗人！

剑客！

音乐家！

空中旅行家！

针尖对麦芒的辩士！

他无所不能

作为至高...但是...

却又一事无成...

...没错，你们这些家伙，想夺走我的一切！

...来，夺走吧，夺走就是了...

但是...无论你们再怎么叫嚷，在去往新世界的路上，我还是会带走一个！

让我看看你坚强的心吧！

没错，你帽子上的羽饰！

象征你内心的勇气的纹章...毛子上的羽饰！

对不起，我该走了，我不能让人久等！

你们看...月亮来迎接我了！

Mon panache！

![](https://cdn.luogu.com.cn/upload/pic/21106.png)

我往空中踏出一步

两人拼命地想要拉住我

但是我往空中踏出一步

没错

我要为了崭新的世界，从天而降

为了获得新的力量

为了新的真实

我踏出了这一步

从手上，感到了两人的颤抖

没关系...

我在你们身边！

Sora！

![](https://cdn.luogu.com.cn/upload/pic/21109.png)

我完全投身于空中

我的身体瞬间从空中向地面落去

我紧紧地握住两人手腕，拉着两人

看见两人的表情...

她们边哭边笑...

似乎很害怕...

却又似很高兴的表情...

啊...

什么嘛，飞翔好舒服啊

宛如变成了天使一般...

好快的速度...

好快的风...

但是却听不见声音...

世界在静静地回转

已经，马上就要到地面了...

空气力学的先驱者...

我知道一切都在回转的天空，

还有包容着我的大地

还差一点，就抵达世界了...

还差一点，就抵达地面了...

接近着的影子

地面映出我的身影

## 题目描述

您正在欣赏 galgame 的 HS，然后游戏崩溃了，于是您只能做数据结构题了：

维护一个长为 $n$ 的序列 $a_i$，有 $m$ 次操作。

1. 将区间 $[l,r]$ 的值修改为 $x$。

2. 询问区间 $[l,r]$ 出现了多少种不同的数，也就是说同一个数出现多次只算一个。

## 输入格式

第一行两个整数 $n,m$。

第二行 $n$ 个整数表示 $a_i$。

后面 $m$ 行每行为 $1\ l\ r\ x$ 或者 $2\ l\ r$ ，分别表示修改和询问。
## 输出格式

对于每个询问，输出一个数表示答案。
## 样例

### 样例输入 #1
```
5 5
1 2 3 4 5
2 1 5
1 2 3 4
2 1 5
2 3 3
2 2 4
```
### 样例输出 #1
```
5
3
1
1
```
## 提示

Idea：nzhtl1477，Solution：nzhtl1477，Code：nzhtl1477，Data：nzhtl1477

$1\leq n , m \leq 10^5$，$1\leq a_i\leq 10^9$。


---

---
title: "[NOI2018] 冒泡排序"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P4769
tag: ['2018', '树状数组', 'NOI', 'O2优化', 'Catalan 数', '栈']
---
# [NOI2018] 冒泡排序
## 题目背景

请注意，题目中存在 $n=0$ 的数据。
## 题目描述

最近，小 S 对冒泡排序产生了浓厚的兴趣。为了问题简单，小 S 只研究对 **$1$ 到 $n$ 的排列**的冒泡排序。

下面是对冒泡排序的算法描述。

```plain
输入：一个长度为 n 的排列 p[1...n]
输出：p 排序后的结果。
for i = 1 to n do
	for j = 1 to n - 1 do
		if(p[j] > p[j + 1])
			交换 p[j] 与 p[j + 1] 的值
```

冒泡排序的交换次数被定义为交换过程的执行次数。可以证明交换次数的一个下界是 $\frac 1 2 \sum_{i=1}^n \lvert i - p_i \rvert$，其中 $p_i$ 是排列 $p$ 中第 $i$ 个位置的数字。如果你对证明感兴趣，可以看提示。

小 S 开始专注于研究长度为 $n$ 的排列中，满足交换次数 $= \frac 1 2 \sum_{i=1}^n \lvert i - p_i \rvert$ 的排列（在后文中，为了方便，我们把所有这样的排列叫「好」的排列）。他进一步想，这样的排列到底多不多？它们分布的密不密集？

小 S 想要对于一个给定的长度为 $n$ 的排列 $q$，计算字典序严格大于 $q$ 的“好”的排列个数。但是他不会做，于是求助于你，希望你帮他解决这个问题，考虑到答案可能会很大，因此只需输出答案对 $998244353$ 取模的结果。
## 输入格式

输入第一行包含一个正整数 $T$，表示数据组数。

对于每组数据，第一行有一个正整数 $n$，保证 $n \leq 6 \times 10^5$。

接下来一行会输入 $n$ 个正整数，对应于题目描述中的 $q_i$，保证输入的是一个 $1$ 到 $n$ 的排列。
## 输出格式

输出共 $T$ 行，每行一个整数。

对于每组数据，输出一个整数，表示字典序严格大于 $q$ 的「好」的排列个数对 $998244353$ 取模的结果。
## 样例

### 样例输入 #1
```
1
3
1 3 2
```
### 样例输出 #1
```
3
```
### 样例输入 #2
```
1
4
1 4 2 3
```
### 样例输出 #2
```
9
```
## 提示

### 更多样例

更多样例请在附加文件中下载。

#### 样例 3

见附加文件中的 `inverse3.in` 与 `inverse3.ans`。

### 样例 1 解释

字典序比 $1 \ 3 \ 2$ 大的排列中，除了 $3 \ 2 \ 1$ 以外都是「好」的排列，故答案为 $3$。

### 数据范围

下面是对本题每个测试点的输入规模的说明。

对于所有数据，均满足 $T = 5$（样例可能不满足）。

记 $n_\mathrm{max}$ 表示每组数据中 $n$ 的最大值，$\sum n$ 表示所有数据的 $n$ 的和。

| 测试点 | $n_\mathrm{max} =$ | $\sum n \leq$ | 特殊性质 |
|:-:|:-:|:-:|:-:|
| 1 | $8$ | $5 \ n_\mathrm{max}$ | 无 |
| 2 | $9$ | $5 \ n_\mathrm{max}$ | 无 |
| 3 | $10$ | $5 \ n_\mathrm{max}$ | 无 |
| 4 | $12$ | $5 \ n_\mathrm{max}$ | 无 |
| 5 | $13$ | $5 \ n_\mathrm{max}$ | 无 |
| 6 | $14$ | $5 \ n_\mathrm{max}$ | 无 |
| 7 | $16$ | $5 \ n_\mathrm{max}$ | 无 |
| 8 | $16$ | $5 \ n_\mathrm{max}$ | 无 |
| 9 | $17$ | $5 \ n_\mathrm{max}$ | 无 |
| 10 | $18$ | $5 \ n_\mathrm{max}$ | 无 |
| 11 | $18$ | $5 \ n_\mathrm{max}$ | 无 |
| 12 | $122$ | $700$ | $\forall i \enspace q_i = i$ |
| 13 | $144$ | $700$ | 无 |
| 14 | $166$ | $700$ | 无 |
| 15 | $200$ | $700$ | 无 |
| 16 | $233$ | $700$ | 无 |
| 17 | $777$ | $4000$ | $\forall i \enspace q_i = i$ |
| 18 | $888$ | $4000$ | 无 |
| 19 | $933$ | $4000$ | 无 |
| 20 | $1000$ | $4000$ | 无 |
| 21 | $266666$ | $2000000$ | $\forall i \enspace q_i = i$ |
| 22 | $333333$ | $2000000$ | 无 |
| 23 | $444444$ | $2000000$ | 无 |
| 24 | $555555$ | $2000000$ | 无 |
| 25 | $600000$ | $2000000$ | 无 |

### 提示

下面是对交换次数下界是 $\frac 1 2 \sum_{i=1}^n \lvert i - p_i \rvert$ 的证明。

排序本质上就是数字的移动，因此排序的交换次数应当可以用数字移动的总距离来描述。对于第 $i$ 个位置，假设在初始排列中，这个位置上的数字是 pi，那么我们需要将这个数字移动到第 $p_i$ 个位置上，移动的距离是 $\lvert i - p_i \rvert$。从而移动的总距离就是 $\sum_{i=1}^n \lvert i - p_i \rvert$，而冒泡排序每次会交换两个相邻的数字，每次交换可以使移动的总距离至多减少 $2$。因此 $\frac 1 2 \sum_{i=1}^n \lvert i - p_i \rvert$ 是冒泡排序的交换次数的下界。

并不是所有的排列都达到了下界，比如在 $n = 3$ 的时候，考虑排列 $3 \ 2 \ 1$，这个排列进行冒泡排序以后的交换次数是 $3$，但是 $\frac 1 2 \sum_{i=1}^n \lvert i - p_i \rvert$ 只有 $2$。


---

---
title: "「Wdoi-1」完美冻结"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P6528
tag: ['莫队', '树状数组']
---
# 「Wdoi-1」完美冻结
## 题目背景

琪露诺是一个喜欢研究数表的女孩子。
## 题目描述

琪露诺有 $n$ 个正整数 $a_1,a_2,...,a_n$，她会按照如下方式构造一个大小为 $n\times n$ 的数字表格：  

- 定义数表的左下角为 $(1,1)$，右上角为 $(n,n)$，从左向右数第 $x$ 列，从下向上数第 $y$ 行的位置为 $(x,y)$。在数表的每个位置填入数字 $0$，然后在每个 $(i,i) (1\le i\le n)$ 处填入 $a_i$  

- 枚举数表中的每一个 $2\times 2$ 大小的子矩阵，当子矩阵左下角和右上角的数字**都不为 $0$** 时，记该子矩阵中从左到右，从上到下的数字分别为 $a,b,c,d$，进行以下操作：  

	- 若 $a=0$，$d=0$，则在数表中 $a,d$ 所处的位置填入 $b+c$  
    - 若 $a=0$，$d\neq 0$，则在数表中 $a$ 所处的位置填入 $b+c-d$  
    - 若 $a\neq 0$，$d=0$，则在数表中 $d$ 所处的位置填入 $b+c-a$  
    
- 重复第二步操作直至数表中的每一个位置都填有**正整数**  。

- 最后，将数表中的每个数 $a_{ij}$ 变为 $\lfloor \frac{a_{ij}}{k} \rfloor $，其中 $k$ 是一给定常数，$\lfloor x \rfloor$ 表示不超过 $x$ 的最大整数。  

构造完 $n\times n$ 的巨大数表后，琪露诺会进行 $q$ 次查询，每次询问数表中以  $(x_1,y_1)$ 为左下角，$(x_2,y_2)$ 为右上角的子矩阵中所有数字的和。  

头脑简单的琪露诺想了一天又一天，却始终没有头绪，因此她找到了聪明的你帮她解决这个问题。  

当然，由于答案可能很大，你只需要输出答案对 $998244353$ 取模后的结果即可。
## 输入格式

第一行三个整数 $n,q,k$。  

第二行 $n$ 个正整数，表示 $a_i$。  

之后 $q$ 行，每行四个正整数 $x_1,y_1,x_2,y_2$，表示询问子矩阵的左下角和右上角坐标。
## 输出格式

共 $q$ 行，每行一个整数，表示每一个询问的答案对 $998244353$ 取模后的结果。
## 样例

### 样例输入 #1
```
3 2 2
1 2 3
1 2 2 3
1 1 3 3
```
### 样例输出 #1
```
7
14
```
### 样例输入 #2
```
6 3 3
1 1 4 5 1 4
1 1 6 6
1 2 3 4
2 2 5 5
```
### 样例输出 #2
```
87
14
32
```
## 提示

#### 样例 1 解释
第一步操作后的数表：  

$
\begin{bmatrix}
0 & 0 & 3 \cr  %\cr是换行功能
0 & 2 & 0  \cr
1 & 0 & 0
\end{bmatrix}
$  

进行一次第二步操作后的数表：  

$
\begin{bmatrix}
0 & 5 & 3 \cr  %\cr是换行功能
3 & 2 & 5  \cr
1 & 3 & 0
\end{bmatrix}
$  

进行两次第二步操作后的数表：   

$
\begin{bmatrix}
6 & 5 & 3 \cr  %\cr是换行功能
3 & 2 & 5  \cr
1 & 3 & 6
\end{bmatrix}
$  

进行第三步操作(对 $k=2$ 向下取整)后的数表：  

$
\begin{bmatrix}
3 & 2 & 1 \cr  %\cr是换行功能
1 & 1 & 2  \cr
0 & 1 & 3
\end{bmatrix}
$    

询问 `1 2 2 3` 的答案为 $1+1+3+2=7$  
询问 `1 1 3 3` 的答案为 $0+1+3+1+1+2+3+2+1=14$

#### 数据范围：   

对于 $100\%$ 的数据，$1 \le n,q \le 2\times 10^5$  ，$0 < a_i ,k \le 10^9$  ，$1 \le x_1 \le x_2 \le n$，$1 \le y_1 \le y_2 \le n$。

子任务编号 | $\max(n,q)$  | 特殊限制 | 分值
:-: | :-: | :-: | :-:
$1$ | $100$ | 无特殊限制 | $5$
$2$ | $500$ | 无特殊限制 | $5$
$3$ | $5000$ | 无特殊限制 | $10$
$4$ | $10^5$ | $q=1$ 且询问子矩阵为整个数表 | $20$  
$5$ | $10^5$ | $k=1$ | $15$
$6$ | $10^5$ | $k=2$ | $15$
$7$ | $2*10^5$ | 无特殊限制 | $30$  

**注意：本题采取捆绑测试**


---

---
title: "[JOISC 2020] 収穫"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7217
tag: ['树形数据结构', '2020', '树状数组', 'JOI（日本）']
---
# [JOISC 2020] 収穫
## 题目背景

JOI 君是 IOI 庄园的庄园主。
## 题目描述

现在 IOI 庄园有 $N$ 名员工，在周长为 $L$ 的湖的湖岸边有 $M$ 棵苹果树。

第 $i$ 名员工从湖的最北点顺时针走了 $A_i$ 米，第 $i$ 棵苹果树长在从湖的最北点顺时针的 $B_i$ 米。

因为特殊原因，每棵苹果树上最多长一个苹果，初始时刻每棵苹果树上都有 $1$ 个苹果，如果一棵树上的苹果被摘掉了，在恰好 $C$ s 后会长出一个苹果。

每名员工在初始时刻都在自己原本的位置，每过一个时刻就会顺时针走 $1$ 米，遇到有成熟苹果的苹果树就会把苹果摘下来。

现在 JOI 君给定了 $Q$ 个询问，第 $i$ 个询问为：

- 询问第 $V_i$ 个员工在时刻 $T_i$ 结束后收获到几个苹果。
## 输入格式

第一行四个整数 $N,M,L,C$ 代表员工数，苹果树数，湖的周长，苹果每隔一定时间成熟。      
第二行 $N$ 个整数 $A_i$ 如题目所示。   
第三行 $M$ 个整数 $B_i$ 去题目所示。    
第四行一个整数 $Q$ 代表询问次数。    
接下来 $Q$ 行每行两个整数 $V_i,T_i$ 代表一个询问。
## 输出格式

$Q$ 行每行一个整数代表答案。
## 样例

### 样例输入 #1
```
3 2 7 3
1 4 6
0 5
3
1 7
2 3
3 8
```
### 样例输出 #1
```
2
1
1
```
### 样例输入 #2
```
5 3 20 6
0 4 8 12 16
2 11 14
9
4 1932
2 93787
1 89
5 98124798
1 2684
1 137598
3 2
3 8375
4 237
```
### 样例输出 #2
```
146
7035
7
7359360
202
10320
0
628
18
```
### 样例输入 #3
```
8 15 217 33608
0 12 71 96 111 128 152 206
4 34 42 67 76 81 85 104 110 117 122 148 166 170 212
14
2 223544052420046341
3 86357593875941375
4 892813012303440034
1 517156961659770735
7 415536186438473633
6 322175014520330760
7 557706040951533058
6 640041274241532527
5 286263974600593111
8 349405886653104871
1 987277313830536091
5 989137777159975413
2 50689028127994215
7 445686748471896881
```
### 样例输出 #3
```
33230868503053
3
5
1
123542793648997
8
165811220737767
8
7
1
1
7
7535161012043
132506837660717
```
## 提示

#### 样例 1 解释

- 在时刻 $1$：
	- 员工 $2$ 到达第 $2$ 棵苹果树，并采摘了成熟的苹果
    - 员工 $3$ 到达第 $1$ 棵苹果树，并采摘了成熟的苹果
- 在时刻 $3$：
	- 员工 $2$ 到达第 $1$ 棵苹果树，但没有成熟的苹果

到时刻 $3$ 结束后，员工 $2$ 共采摘了 $1$ 个苹果，对应样例 $1$ 的第 $2$ 个询问。

- 在时刻 $4$：
	- 员工 $1$ 到达第 $2$ 棵苹果树，并采摘了成熟的苹果
- 在时刻 $6$：
	 - 员工 $1$ 到达第 $1$ 棵苹果树，并采摘了成熟的苹果
     - 员工 $3$ 到达第 $2$ 棵苹果树，但没有成熟的苹果

到时刻 $7$ 结束后，员工 $1$ 共采摘了 $2$ 个苹果，对应样例 $1$ 的第 $1$ 个询问。

- 在时刻 $8$：
	- 员工 $2$ 到达第 $2$ 棵苹果树，并采摘了成熟的苹果
    - 员工 $3$ 到达第 $1$ 棵苹果树，但没有成熟的苹果

到时刻 $8$ 结束后，员工 $3$ 共采摘了 $1$ 个苹果，对应样例 $1$ 的第 $3$ 个询问。

#### 子任务

|子任务|特殊性质|分数|
|:-:|:-:|:-:|
|$1$|$N,M,Q \le 3000$|$5$|
|$2$|$T_i \ge 10^{15}$|$20$|
|$3$|无|$75$|

对于 $100\%$ 的数据，$1 \le N,M,Q \le 2 \times 10^5$，$N+M \le L$，$1 \le C,L \le 10^9$，$0 \le A_i,B_i < L$，$A_i<A_{i+1}$，$B_i<B_{i+1}$，$A_i \ne B_i$，$1 \le V_i \le N$，$1 \le T_i \le 10^{18}$。

#### 说明

翻译自 [第１９回日本情報オリンピック　春季トレーニング合宿](https://www.ioi-jp.org/camp/2020/2020-sp-tasks/index.html) [Day3 B 収穫](https://www.ioi-jp.org/camp/2020/2020-sp-tasks/day3/harvest.pdf)。


---

---
title: "「RdOI R2」风雨(rain)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7582
tag: ['树状数组', '2021', 'O2优化', '分块', 'AC 自动机', 'KMP 算法']
---
# 「RdOI R2」风雨(rain)
## 题目背景

经历过风雨的洗礼，小 Soup 才更懂得珍惜。他认为所有的一切对他来说都有重要的意义。为了能让这一切被自己牢牢铭记，小 Soup 决定用一些手段将它们记录下来。  

[$\text\color{white}{真正的题目背景}$](https://z3.ax1x.com/2021/03/29/c9xbLj.gif)

## 题目描述

小 Soup 在这段时间中记录了 $n$ 个有意义的东西，他把它们用字符串表示了出来，第 $i$ 个东西被表示成 $s_i$，并定义了它的价值 $a_i$。下面，小 Soup 会进行 $m$ 次操作。  
操作 $1$：小 Soup 将区间 $l,r$ 里的 $a_i$ 都加上一个常数 $k$。  
操作 $2$：小 Soup 将区间 $l,r$ 里的 $a_i$ 都赋值成一个常数 $k$。  
操作 $3$：小 Soup 给出了一段回忆，这段回忆形成了一个字符串 $S$，他想求 $S$ 在区间 $l,r$ 中的意义有多大。定义 $cnt_i$ 为 $s_i$ 在 $S$ 中的出现次数，则 $S$ 在区间 $l,r$ 中的意义为 $\sum\limits_{i=l}^r cnt_i\times a_i$。
## 输入格式

第一行两个数，$n,m$。  
接下来 $n$ 行第 $i$ 行一个字符串 $s_i$ 和一个数 $a_i$。  
接下来 $m$ 行每行一个操作，先有三个数，$op,l,r$。其中 $op$ 代表操作类型。$op=3$ 时，多输入一个字符串 $S$，否则多输入一个数 $k$。
## 输出格式

对于每个 $3$ 操作输出一个数，代表总价值。
## 样例

### 样例输入 #1
```
3 4
ab 1
ba 2
a 1
3 1 3 aba
1 1 2 1
2 2 3 2
3 1 2 abab
```
### 样例输出 #1
```
5
6
```
### 样例输入 #2
```
6 6
aba 3
ba 2
aa 2
c 1
abac 4
ab 2
3 2 5 abac
2 3 5 3
3 4 6 abc
1 2 3 1
3 1 3 aabaa
3 2 5 aabac
```
### 样例输出 #2
```
7
5
14
13
```
### 样例输入 #3
```
6 3
b 1
aa 8
cc 9
cac 8
ab 10
a 7
2 1 3 2
3 1 4 acac
3 1 6 ccaba
```
### 样例输出 #3
```
8
28
```
## 提示

**样例 $1$ 解释**

对于第一次询问，$s_1$ 出现了 $1$ 次，对价值贡献为 $1$；$s_2$ 出现了 $1$ 次，对价值贡献为 $2$；$s_3$ 出现了 $2$ 次，对价值贡献为 $2$，总价值为 $5$。  
对于第二次询问，$s_1$ 出现了 $2$ 次，对价值贡献为 $4$；$s_2$ 出现了 $1$ 次，对价值贡献为 $2$，总价值为 $6$。 

---

**数据范围**

|数据编号|$\sum s,\sum S$|$n,m$|特殊性质|
|:---:|:---:|:---:|:---:|
|$1\sim 2$|$\le5\times10^3$|$10^3$|$\diagdown$|
|$3\sim 4$|$\le2\times 10^5$|$3\times10^4$|没有 $1$ 操作|
|$5\sim 8$|$\le2\times 10^5$|$3\times10^4$|没有 $1,2$ 操作|
|$9\sim 13$|$\le2\times 10^5$|$3\times10^4$| $\diagdown$|

对于 $100\%$ 的数据，$1\le n,m\le3\times10^4,k\ge 1,\sum |S|,\sum |s|\le2\times10^5$，任何时刻 $1\le a_i\le2\times10^4$，保证只会出现 $a,b,c$ 三种字符。


---

---
title: "[CCO 2021] Loop Town"
layout: "post"
diff: NOI/NOI+/CTSC
pid: P7833
tag: ['树状数组', '2021', '离散化', 'CCO（加拿大）']
---
# [CCO 2021] Loop Town
## 题目描述

循环镇有 $n$ 个公民、$n$ 座房子、$n$ 个办公室。每个公民住在一座房子中，并在一个办公室工作。没有两个公民住在同一座房子，也没有两个公民在同一个办公室工作。

循环镇是一个环形城市，绕城一圈路程为 $l$。循环镇的 $2n$ 栋建筑（房子和办公室）都在环上的整点上，其位置可以用 $[0, l - 1]$ 范围内的整数来描述，且这 $2n$ 栋建筑位置是互不相同的。

每天早上，每个公民同时从自己的房子出发，沿着环路走到自己的办公室。公民到达办公室之后不会立刻进去工作，而是要等到所有公民都到达办公室之后才会同时进入办公室开始工作。

一场疫情的到来打破了常规，领导人要求每个公民保持社交距离。围绕城市的环状道路很窄，两个公民的线路存在相互交叉时会很不方便（必须一个人暂时离开道路才能使另一个人通过），而三个人或以上禁止同时走到同一个地方。

领导人可以给每个公民规定上班路线，即走城市环路的哪一边。领导人的目标是任意两个公民线路交叉的总次数最小，求这个最小值。
## 输入格式

第一行，两个整数 $n, l$；

接下来 $n$ 行，每行两个整数 $a_i, b_i$，表示第 $i$ 个公民的房子和办公室的位置。
## 输出格式

一行，一个整数，表示所求的值。
## 样例

### 样例输入 #1
```
3 100
10 50
30 20
60 40
```
### 样例输出 #1
```
0
```
### 样例输入 #2
```
4 100
30 70
10 12
60 75
90 50
```
### 样例输出 #2
```
1
```
## 提示

#### 数据范围
对于 $\frac{4}{13}$ 的数据，$1 \leq n \leq 5 \times 10^3$；

对于 $\frac{8}{13}$ 的数据，$1 \leq n \leq 10^5$；

对于 $100\%$ 的数据，$1 \leq n \leq 10^6$，$1 \leq l \leq 10^9$，$0 \leq a_i, b_i < l$，**保证 $a_i, b_i$ 互不相同**。
#### 题目来源
[CCO2021](https://cemc.math.uwaterloo.ca/contests/computing/2021/index.html) D2T3


---

