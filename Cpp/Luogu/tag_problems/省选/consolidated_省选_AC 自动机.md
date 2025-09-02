---
title: "[GDCPC 2024] 腊肠披萨"
layout: "post"
diff: 省选/NOI-
pid: P13352
tag: ['2024', '广东', '容斥原理', 'AC 自动机', 'KMP 算法', 'XCPC']
---
# [GDCPC 2024] 腊肠披萨
## 题目背景

数据、标程、题解等资源的获取：<https://gitlink.org.cn/thusaa/gdcpc2024>
## 题目描述

宇宙北大街上新开了一家披萨店。这家披萨店主打使用腊肠的披萨，被顾客亲切地称为“腊肠披萨店”。这种中西合璧的做法听上去很离经叛道，但是品尝过腊肠披萨的顾客都对其称赞有加，吸引了众多食客蜂拥而至。

除了配料极具特色，腊肠披萨店的 Wi-Fi 密码也是它的流量密码。菜单上写着：“本店的 Wi-Fi 密码是

$$
\sum_{i=1}^L \sum_{j=1}^L C^{\left|LCPS\left(s_i, s_j\right)\right|} \bmod{P},
$$

其中 $LCPS\left(s_i, s_j\right)$ 表示 $s_i$ 和 $s_j$ 的最长公共前后缀，即最长的同时是 $s_i$ 前缀和 $s_j$ 后缀的字符串（可能为空，也可能为整个串）；每天的 $s_1,\cdots,s_L$ 都不一样，服务员会在点餐后提供用于当天的 Wi-Fi 密码的字符串。每天将会从前 100 名连上 Wi-Fi 的顾客中随机抽取一位免单。”

你计划下周和朋友一起来这家店聚餐，因此你想设计一个算法，快速求出这家店的 Wi-Fi 密码。
## 输入格式

输入的第一行包含三个正整数 $L, C, P$，表示字符串的数量、底数及模数。保证 $1\le L\le 3\times 10^6$，$2\le C<P<2^{30}$。

接下来 $L$ 行，每行输入一个仅由小写字符构成的字符串 $s_i$。保证 $1\le \left|s_i\right| \le 3\times 10^6$，$\sum_{i=1}^L \left|s_i\right| \le 3\times 10^6$。

## 输出格式

输出一个非负整数，表示腊肠披萨店的 Wi-Fi 密码。
## 样例

### 样例输入 #1
```
4 2 378323747
shop
pizza
piazza
pizzala
```
### 样例输出 #1
```
286
```
### 样例输入 #2
```
9 99 998244353
asap
peace
piece
pizza
sapiens
dazzling
andromeda
sakurasaku
kokorosaku
```
### 样例输出 #2
```
161369438
```
## 提示

### 样例 1 解释

对于 $1\le i,j\le 4, i\ne j$，

- $LCPS($ `pizza` $,$ `shop` $ )=LCPS($ `piazza` $,$ `shop` $)=LCPS($ `pizzala` $,$ `shop` $)=$ `p`；
- $LCPS($ `pizzala` $,$ `pizza` $)=$ `pizza`；
- 其余的 $LCPS\left(s_i, s_j\right)=\varepsilon$。

因此对应的 Wi-Fi 密码为

$$
2^4 + 2^0 + 2^0 + 2^0 + 2^1 + 2^5 + 2^0 + 2^0 + 2^1 + 2^0 + 2^6 + 2^0 + 2^1 + 2^5 + 2^0 + 2^7 = 286.
$$

腊肠披萨店在制作披萨时使用了绝密配方。在没有专业人士指导的情况下，请不要轻易模仿。


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
title: "[HNOI2004] L 语言"
layout: "post"
diff: 省选/NOI-
pid: P2292
tag: ['2004', '各省省选', '湖南', 'O2优化', 'AC 自动机', '状压 DP']
---
# [HNOI2004] L 语言
## 题目描述

标点符号的出现晚于文字的出现，所以以前的语言都是没有标点的。现在你要处理的就是一段没有标点的文章。  

一段文章 $T$ 是由若干小写字母构成。一个单词 $W$ 也是由若干小写字母构成。一个字典 $D$ 是若干个单词的集合。我们称一段文章 $T$ 在某个字典 $D$ 下是可以被理解的，是指如果文章 $T$ 可以被分成若干部分，且每一个部分都是字典 $D$ 中的单词。  

例如字典 $D$ 中包括单词 $\texttt{is},\texttt{name},\texttt{what},\texttt{your}$，则文章 $\texttt{whatisyourname}$ 是在字典 $D$ 下可以被理解的，因为它可以分成 $4$ 个单词：$\texttt{what},\texttt{is},\texttt{your},\texttt{name}$，且每个单词都属于字典 $D$，而文章 $\texttt{whatisyouname}$ 在字典 $D$ 下不能被理解，但可以在字典 $D'=D\cup\{\texttt{you}\}$ 下被理解。这段文章的一个前缀 $\texttt{whatis}$，也可以在字典 $D$ 下被理解，而且是在字典 $D$ 下能够被理解的最长的前缀。  

给定一个字典 $D$，你的程序需要判断若干段文章在字典 $D$ 下是否能够被理解。并给出其在字典 $D$ 下能够被理解的最长前缀的位置。
## 输入格式

第一行两个整数 $n$ 和 $m$，表示字典 $D$ 中有 $n$ 个单词，且有 $m$ 段文章需要被处理。

接下来 $n$ 行，每行一个字符串 $s$，表示字典 $D$ 中的一个单词。

接下来 $m$ 行，每行一个字符串 $t$，表示一篇文章。
## 输出格式

对于输入的每一篇文章，你需要输出一行一个整数，表示这段文章在字典 $D$ 可以被理解的最长前缀的位置。
## 样例

### 样例输入 #1
```
4 3 
is
name
what
your
whatisyourname
whatisyouname
whaisyourname

```
### 样例输出 #1
```
14
6
0

```
## 提示

#### 样例 1 解释

- 对于第一个询问，整段文章 `whatisyourname` 都能被理解。
- 对于第二个询问，前缀 `whatis` 能够被理解。
- 对于第三个询问，没有任何前缀能够被理解。

#### 数据规模与约定

- 对于 $80\%$ 的数据，保证 $m \leq 20$，$|t| \leq 10^6$。
- 对于 $100\%$ 的数据，保证 $1 \leq n \leq 20$，$1 \leq m \leq 50$，$1 \leq |s| \leq 20$，$1 \leq |t| \leq 2 \times 10^6$，$s$ 与 $t$ 中均只含小写英文字母。

#### 提示

- 请注意数据读入对程序效率造成的影响。
- 请注意【数据规模与约定】中标注的串长是单串长度，并不是字符串长度和。

#### 说明

本题数据有加强，其中前 $80\%$ 的数据为原测试数据。


---

---
title: "[SCOI2012] 喵星球上的点名"
layout: "post"
diff: 省选/NOI-
pid: P2336
tag: ['2012', '四川', '莫队', '各省省选', 'AC 自动机', '后缀数组 SA']
---
# [SCOI2012] 喵星球上的点名
## 题目描述

a180285 幸运地被选做了地球到喵星球的留学生。他发现喵星人在上课前的点名现象非常有趣。

假设课堂上有 $n$ 个喵星人，每个喵星人的名字由**姓**和**名**构成。喵星球上的老师会选择 $m$ 个串来点名，每次读出一个串的时候，如果这个串是一个喵星人的姓或名的**子串**，那么这个喵星人就必须答到。

然而，由于喵星人的字码如此古怪，以至于不能用 ASCII 码来表示。为了方便描述，a180285 决定用数串来表示喵星人的名字。



现在你能帮助 a180285 统计每次点名的时候有多少喵星人答到，以及 $m$ 次点名结束后每个喵星人答到多少次吗？

## 输入格式

首先定义喵星球上的字符串给定方法：

先给出一个正整数 $l$，表示字符串的长度，接下来 $l$ 个整数，第 $i$ 个整数 $a_i$ 表示字符串的第 $i$ 个字符。

输入的第一行有两个整数，分别表示喵星人的个数 $n$ 个点名次数 $m$。  
接下来 $n$ 行，每行两个喵星球上的字符串，按照定义的方法给出，依次表示第 $i$ 只喵的姓和名。  
接下来 $m$ 行，每行一个喵星球上的字符串，表示一个老师点名的串。
## 输出格式

对于每个老师点名的串，输出一行一个整数表示有多少只喵答到。  
然后在最后一行输出 $n$ 个用空格隔开的整数，第 $i$ 个整数表示第 $i$ 个喵星人被点到的次数。

## 样例

### 样例输入 #1
```
2 3
6 8 25 0 24 14 8 6 18 0 10 20 24 0
7 14 17 8 7 0 17 0 5 8 25 0 24 0
4 8 25 0 24
4 7 0 17 0
4 17 0 8 25

```
### 样例输出 #1
```
2
1
0
1 2
```
## 提示

#### 样例 1 解释

事实上样例给出的数据如果翻译成地球上的语言可以这样来看

```plain
2 3
izayoi sakuya
orihara izaya
izay
hara
raiz
```

#### 数据规模与约定

- 对于 $30\%$ 的数据，保证 $n, m \le 10^3$，喵星人的名字总长不超过 $4\times10^3$，点名串的总长不超过 $2\times10^3$。
- 对于$100\%$ 的数据，保证 $1 \leq n\le 5 \times 10^4$，$1 \leq m \le 10^5$，喵星人的名字总长和点名串的总长分别不超过 $10^5$，保证喵星人的字符串中作为字符存在的数不超过 $10^4$ 。


---

---
title: "[NOI2011] 阿狸的打字机"
layout: "post"
diff: 省选/NOI-
pid: P2414
tag: ['字符串', '树形数据结构', '2011', 'NOI', '深度优先搜索 DFS', 'AC 自动机']
---
# [NOI2011] 阿狸的打字机
## 题目描述

阿狸喜欢收藏各种稀奇古怪的东西，最近他淘到一台老式的打字机。打字机上只有 $28$ 个按键，分别印有 $26$ 个小写英文字母和 `B`、`P` 两个字母。经阿狸研究发现，这个打字机是这样工作的：

* 输入小写字母，打字机的一个凹槽中会加入这个字母(这个字母加在凹槽的最后)。
* 按一下印有 `B` 的按键，打字机凹槽中最后一个字母会消失。
* 按一下印有 `P` 的按键，打字机会在纸上打印出凹槽中现有的所有字母并换行，但凹槽中的字母不会消失。

例如，阿狸输入 `aPaPBbP`，纸上被打印的字符如下：

```
a
aa
ab
```

我们把纸上打印出来的字符串从 $1$ 开始顺序编号，一直到 $n$。打字机有一个非常有趣的功能，在打字机中暗藏一个带数字的小键盘，在小键盘上输入两个数 $(x,y)$（其中 $1\leq x,y\leq n$），打字机会显示第 $x$ 个打印的字符串在第 $y$ 个打印的字符串中出现了多少次。

阿狸发现了这个功能以后很兴奋，他想写个程序完成同样的功能，你能帮助他么？

## 输入格式

输入的第一行包含一个字符串，按阿狸的输入顺序给出所有阿狸输入的字符。

第二行包含一个整数 $m$，表示询问个数。

接下来 $m$ 行描述所有由小键盘输入的询问。其中第 $i$ 行包含两个整数 $x, y$，表示第 $i$ 个询问为 $(x, y)$。

## 输出格式

输出 $m$ 行，其中第 $i$ 行包含一个整数，表示第 $i$ 个询问的答案。

## 样例

### 样例输入 #1
```
aPaPBbP
3
1 2
1 3
2 3
```
### 样例输出 #1
```
2
1
0
```
## 提示

### 数据范围

对于 $100\%$ 的数据，$1\leq n\leq 10^5$，$1\leq m\leq10^5$，第一行总长度 $\leq 10^5$。

|测试点|$n$ 的规模|$m$ 的规模|字符串长度|第一行长度|
|:-:|:-:|:-:|:-:|:-:|
|$1,2$|$1\leq n\leq 100$|$1\leq m\leq 10^3$| - |$\leq 100$|
|$3,4$|$1\leq n\leq 10^3$|$1\leq m\leq 10^4$|单个长度 $\leq 10^3$，总长度 $\leq 10^5$|$\leq 10^5$|
|$5\sim 7$|$1\leq n\leq 10^4$|$1\leq m\leq 10^5$|总长度 $\leq 10^5$|$\leq 10^5$|
|$8\sim 10$|$1\leq n\leq 10^5$|$1\leq m\leq 10^5$| - |$\leq 10^5$|




---

---
title: "[POI 2000] 病毒"
layout: "post"
diff: 省选/NOI-
pid: P2444
tag: ['字符串', '2000', 'POI（波兰）', 'AC 自动机']
---
# [POI 2000] 病毒
## 题目描述

二进制病毒审查委员会最近发现了如下的规律：某些确定的二进制串是病毒的代码。如果某段代码中不存在任何一段病毒代码，那么我们就称这段代码是安全的。现在委员会已经找出了所有的病毒代码段，试问，是否存在一个无限长的安全的二进制代码。

示例：

例如如果 $\{011, 11, 00000\}$ 为病毒代码段，那么一个可能的无限长安全代码就是 $010101 \ldots$。如果 $\{01, 11, 000000\}$ 为病毒代码段，那么就不存在一个无限长的安全代码。

现在给出所有的病毒代码段，判断是否存在无限长的安全代码。
## 输入格式

第一行包括一个整数 $n$，表示病毒代码段的数目。

以下的 $n$ 行每一行都包括一个非空的 $01$ 字符串，代表一个病毒代码段。

## 输出格式

如果存在无限长的安全代码，输出 `TAK`，否则输出 `NIE`。
## 样例

### 样例输入 #1
```
3
01 
11 
00000

```
### 样例输出 #1
```
NIE
```
## 提示

$1 \leq n \leq 2000$，所有病毒代码段的总长度不超过 $3 \times 10^4$。


---

---
title: "[ZJOI2008] 无序运动"
layout: "post"
diff: 省选/NOI-
pid: P2603
tag: ['2008', '各省省选', '浙江', '向量', 'AC 自动机']
---
# [ZJOI2008] 无序运动
## 题目描述

D 博士对物理有着深入的研究，经典物理、天体物理、量子物理都有着以他的名字命名的定理。最近 D 博士着迷于研究粒子运动的无规则性。对圣经深信不疑的他相信，上帝创造的任何事物必然是有序的、有理可循的，而不是无规则的、混沌的。

经过长时间的研究，D 博士找到了很多出现相当频繁的轨迹片断，他把这些轨迹片断储存在一个很大的数据库内。他需要你帮助他写一个程序，对于一个给出的粒子运动轨迹，统计数据库中每个轨迹片断的出现的次数。

为清楚起见，我们定义一个粒子的轨迹为二维平面上的一个点列 $(P_1, P_2, \dots, P_N)$。点列 $P$ 的一个子列 $[i, j]$ 定义为 $P$ 中一段连续的子序列 $(P_i, P_{i + 1}, \dots, P_j)$。点列 $P$ 的一个子列 $[u, v]$ 被称为点列 $Q = (Q_1, Q_2, \dots, Q_{v - u + 1})$ 在 $P$ 中的一次出现，当且仅当 $Q$ 经过有限次的平移、旋转、翻转、放缩之后得到 $Q'$ 满足 $\forall 1 \le k \le u - v + 1$，$ Q'_k = P_{u + k - 1}$。

对点列进行四种操作的解释：
|操作名称|解释|
|:-:|:-:|
|平移|设平移向量为 $(d_x, d_y)$，则任意点 $(x, y)$ 平移后的结果为 $(x + d_x, y + d_y)$|
|旋转|设旋转角为 $t$，则任意点 $(x, y)$ 旋转后的结果为 $(x \cos t - y \sin t, x \sin t + y \cos t)$|
|翻转|任意点 $(x, y)$ 翻转后的结果为 $(x, -y)$
|放缩|设放缩比例为 $p(p \ne 0)$，则任意点 $(x, y)$ 放缩后的结果为 $(px, py)$|
## 输入格式

第一行两个整数 $N, M$，分别描述待处理的粒子运动轨迹的点列大小与数据库内的轨迹片断个数。

接下来 $M$ 行依次给出每个轨迹片断。每行先是一个正整数 $K$，表示该轨迹片断点列的长度。然后 $2K$ 个整数，依次描述点列中的 $K$ 个点的横坐标与纵坐标。

接下来一行 $2N$ 个整数，依次描述待处理的粒子运动轨迹的点列中 $N$ 个点的横坐标与纵坐标。

注：输入中的每条轨迹中任意相邻两点不会相同。
## 输出格式

应包含 $M$ 行，依次给出每个片段在待处理运动轨迹中的出现次数。
## 样例

### 样例输入 #1
```
3 2
2 17 0 10 1
3 0 0 1 0 1 -1
0 0 1 0 1 1

```
### 样例输出 #1
```
2
1

```
## 提示

记片段总长度为 $L$。

对于 $30\%$ 的测试数据，满足 $N, M, K \le 100$，$L \le 500$;

对于 $50\%$ 的测试数据，满足 $N, M, K \le 1000$，$L \le 5000$;

对于 $100\%$ 的测试数据，满足 $N, K \le 2 \times 10 ^ 5$，$L \le 2 \times 10 ^ 6$，保证输入中给出所有点坐标绝对值均不大于 $10 ^ 4$。


---

---
title: "[USACO12JAN] Video Game G"
layout: "post"
diff: 省选/NOI-
pid: P3041
tag: ['动态规划 DP', '2012', 'USACO', 'O2优化', 'AC 自动机']
---
# [USACO12JAN] Video Game G
## 题目描述

Bessie 在玩一款游戏，该游戏只有三个技能键 `A`，`B`，`C` 可用，但这些键可用形成 $n$ 种特定的组合技。第 $i$ 个组合技用一个字符串 $s_i$ 表示。

Bessie 会输入一个长度为 $k$ 的字符串 $t$，而一个组合技每在 $t$ 中出现一次，Bessie 就会获得一分。$s_i$ 在 $t$ 中出现一次指的是 $s_i$ 是 $t$ 从某个位置起的连续子串。如果 $s_i$ 从 $t$ 的多个位置起都是连续子串，那么算作 $s_i$ 出现了多次。

若 Bessie 输入了恰好 $k$ 个字符，则她最多能获得多少分？
## 输入格式

输入的第一行是两个整数，分别表示组合技个数 $n$ 和 Bessie 输入的字符数 $k$。

接下来 $n$ 行，每行一个字符串 $s_i$，表示一种组合技。
## 输出格式

输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
3 7 
ABA 
CB 
ABACB 

```
### 样例输出 #1
```
4 

```
## 提示

#### 样例 1 解释

Bessie 如果输入 `ABACBCB`，则 `ABA` 出现了一次，`ABACB` 出现了一次，`CB` 出现了两次，共得到 $4$ 分。可以证明这是最优的输入。

#### 数据规模与约定

对于全部的测试点，保证：

- $1 \leq n \leq 20$，$1 \leq k \leq 10^3$。
- $1 \leq |s_i| \leq 15$。其中 $|s_i|$ 表示字符串 $s_i$ 的长度。
- $s$ 中只含大写字母 `A`，`B`，`C`。


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
title: "[SDOI2014] 数数"
layout: "post"
diff: 省选/NOI-
pid: P3311
tag: ['字符串', '动态规划 DP', '2014', '山东', 'O2优化', '数位 DP', 'AC 自动机']
---
# [SDOI2014] 数数
## 题目描述

我们称一个正整数 $x$ 是幸运数，当且仅当它的十进制表示中不包含数字串集合 $s$ 中任意一个元素作为其子串。例如当 $s = \{22, 333, 0233\}$ 时，$233$ 是幸运数，$2333$、$20233$、$3223$ 不是幸运数。给定 $n$ 和 $s$，计算不大于 $n$ 的幸运数个数。

答案对 $10^9 + 7$ 取模。
## 输入格式

第一行有一个整数，表示 $n$。

第二行有一个整数，表示 $s$ 中的元素个数 $m$。

接下来 $m$ 行，每行一个数字串 $s_i$，表示 $s$ 中的一个元素。
## 输出格式

输出一行一个整数，表示答案对 $10^9 + 7$ 取模的结果。
## 样例

### 样例输入 #1
```
20
3
2
3
14
```
### 样例输出 #1
```
14
```
## 提示

#### 样例 1 解释

除了 $3, 13, 2, 12, 20, 14$ 以外，不大于 $20$ 的整数都是幸运数字。

#### 数据规模与约定

对于全部的测试点，保证：

$1 \leq n < 10^{1201}$，$1 \leq m \leq 100$，$1 \leq \sum_{i = 1}^m |s_i| \leq 1500$，$\min_{i = 1}^m |s_i| \geq 1$，其中 $|s_i|$ 表示字符串 $s_i$ 的长度。$n$ 没有前导 $0$，但是 $s_i$ 可能有前导 $0$。


---

---
title: "[POI 2010] CHO-Hamsters"
layout: "post"
diff: 省选/NOI-
pid: P3502
tag: ['2010', 'POI（波兰）', '矩阵加速', 'AC 自动机']
---
# [POI 2010] CHO-Hamsters
## 题目描述

Byteasar breeds hamsters.

Each hamster has a unique name,    consisting of lower case letters of the English alphabet.

    The hamsters have a vast and comfortable cage.

    Byteasar intends to place a display under the cage to visualize the names of his hamsters.

    This display is simply a sequence of letters, each of which can be either lit or not independently.

Only one name will be displayed simultaneously.

The lit letters forming the name have to stand next to each other,    i.e., form a contiguous subsequence.

Byteasar wants to be able to display the names of the hamsters on at least ![](http://main.edu.pl/images/OI17/cho-en-tex.1.png) different positions.

However, he allows displaying the same name on multiple different positions,    and does not require to be able to display each and every hamster's name.

Note that the occurrences of the names on the display can overlap.

You can assume that no hamster's name occurs (as a contiguous fragment) in any other hamster's name.

Bytesar asks your help in determining the minimum number of letters the display has to have.

In other words, you are to determine the minimum length of a string    (consisting of non-capital letters of the English alphabet)    that has at least ![](http://main.edu.pl/images/OI17/cho-en-tex.2.png) total occurrences of the hamsters' names (counting multiplicities).

(We say that a string ![](http://main.edu.pl/images/OI17/cho-en-tex.3.png) occurs in the string ![](http://main.edu.pl/images/OI17/cho-en-tex.4.png) if ![](http://main.edu.pl/images/OI17/cho-en-tex.5.png) forms a contiguous fragment of ![](http://main.edu.pl/images/OI17/cho-en-tex.6.png).)


## 输入格式

The first line of the standard input holds two integers ![](http://main.edu.pl/images/OI17/cho-en-tex.7.png) and ![](http://main.edu.pl/images/OI17/cho-en-tex.8.png)      (![](http://main.edu.pl/images/OI17/cho-en-tex.9.png), ![](http://main.edu.pl/images/OI17/cho-en-tex.10.png)), separated by a single space, that denote      the number of Byteasar's hamsters and the minimum number of occurrences of the hamsters' names on the display.

Each of the following ![](http://main.edu.pl/images/OI17/cho-en-tex.11.png) lines contains a non-empty string of non-capital letters of the English alphabet      that is the hamster's name.

The total length of all names does not exceed ![](http://main.edu.pl/images/OI17/cho-en-tex.12.png) letters.

## 输出格式

The first and only line of the standard output should hold a single integer      - the minimum number of letters the display has to have.

## 样例

### 样例输入 #1
```
4 5
monika
tomek
szymon
bernard
```
### 样例输出 #1
```
23
```
## 提示

$1\le n\le 200$，$1\le m\le 10^9$ ，所有字符串的总长 $\le 10^5$。

## 题目翻译

给出 $n$ 个互不包含的字符串，要求你求出一个最短的字符串 $S$，使得这 $n$ 个字符串在 $S$ 中总共至少出现 $m$ 次，问 $S$ 最短是多少。


---

---
title: "[BJOI2017] 魔法咒语"
layout: "post"
diff: 省选/NOI-
pid: P3715
tag: ['字符串', '2017', '各省省选', '矩阵加速', 'AC 自动机', '构造']
---
# [BJOI2017] 魔法咒语
## 题目描述

Chandra 是一个魔法天才。

从一岁时接受火之教会洗礼之后，Chandra 就显示出对火元素无与伦比的亲和力，轻而易举地学会种种晦涩难解的法术。这也多亏 Chandra 有着常人难以企及的语言天赋，让她能轻松流利地说出咒语中那些极其拗口的魔法词汇。

直到十四岁，开始学习威力强大的禁咒法术时，Chandra 才遇到了障碍。

根据火之魔法规则，禁咒的构成单位是 $N$ 个基本词汇。施法时只要凝聚精神力，说出一段用这些词语组成的长度恰好等于 $L$ 的语言，就能释放威力超乎想象的火法术。过去的魔法师们总结了几种表达起来最连贯的组合方式，方便施法者以最快语速完成法术。

但具有魔法和语言双重天才的 Chandra 不满足于这几种流传下来的禁咒，因为她可以毫无困难地说出普通人几乎不可能表达的禁咒语句。然而，在实际施法时，Chandra 发现有些自创禁咒念出后不但没有预期效果，反而会使自己的精神力迅速枯竭，十分难受。

这个问题令 Chandra 万分不解。她大量阅读典籍，到处走访魔法学者，并且不顾精神折磨一次又一次尝试新咒语，希望找出问题的答案。

很多年过去了，在一次远古遗迹探险中，Chandra 意外闯进了火之神艾利克斯的不知名神殿。根据岩土特征分析，神殿应该有上万年的历史，这是极其罕见的。Chandra 小心翼翼地四处探索，沿着魔力流动来到一间密室。她看见密室中央悬浮着一本书籍。在魔法保护下书籍状况完好。精通上古语言的 Chandra 读过此书，终于解开了多年的困惑。


禁咒法术之所以威力强大，是因为咒语借用了火之神艾利克斯的神力。这本书里记载了艾利克斯生平忌讳的 $M$ 个词语，比如情敌的名字、讨厌的植物等等。使用禁咒法术时，如果语言中含有任何忌讳词语，就会触怒神力而失效，施法者也一并遭受惩罚。

例如，若 `banana` 是唯一的忌讳词语，`an`、`ban`、`analysis` 是基本词汇，禁咒长度须是 $11$，则 `bananalysis` 是无效法术，`analysisban`、`anbanbanban` 是两个有效法术。注意：一个基本词汇在禁咒法术中可以出现零次、一次或多次；只要组成方式不同就认为是不同的禁咒法术，即使书写形式相同。

谜题破解，Chandra 心情大好。她决定计算一共有多少种有效的禁咒法术。

由于答案可能很大，你只需要输出答案模 $10 ^ 9 + 7$ 的结果。

## 输入格式

第一行，三个正整数 $N, M, L$。

接下来 $N$ 行，每行一个只含小写英文字母的字符串，表示一个基本词汇。

接下来 $M$ 行，每行一个只含小写英文字母的字符串，表示一个忌讳词语。

## 输出格式

仅一行，一个整数，表示答案（模 $10^9+7$）。

## 样例

### 样例输入 #1
```
4 2 10
boom
oo
ooh
bang
ob
mo
```
### 样例输出 #1
```
14
```
### 样例输入 #2
```
3 1 3
a
ab
aba
aaa
```
### 样例输出 #2
```
3
```
### 样例输入 #3
```
3 1 14
ban
an
analysis
banana
```
### 样例输出 #3
```
15
```
## 提示

【样例解释 1】

有效的禁咒法术共有 $14$ 种：`boom/bang/oo`，`oo/oo/oo/oo/oo`，`oo/oo/ooh/ooh`，`oo/ooh/oo/ooh`，`oo/ooh/ooh/oo`，`ooh/oo/oo/ooh`，`ooh/oo/ooh/oo`，`
ooh/ooh/boom`，`ooh/ooh/oo/oo`，`ooh/ooh/bang`，`ooh/bang/ooh`，`bang/oo/oo/oo`，`bang/ooh/ooh`，`bang/bang/oo`。

【样例解释 2】

有效的禁咒法术有 `a/ab`，`ab/a`，`aba` 共三种。注意，`ab/a` 和 `aba` 算成两种不同的禁咒法术。

【数据规模与约定】

本题一共有 $10$ 个测试点。

下表是每个测试点的数据规模和约定：

 ![](https://cdn.luogu.com.cn/upload/pic/5191.png) 

对于 $100\%$ 的数据，$1 \le N, M \le 50，1 \le L \le 10^8$，基本词汇的长度之和不超过 $100$，忌讳词语的长度之和不超过 $100$。保证基本词汇不重复，忌讳词语不重复。



---

---
title: "[JSOI2009] 密码"
layout: "post"
diff: 省选/NOI-
pid: P4045
tag: ['字符串', '2009', '各省省选', '江苏', 'AC 自动机', '状压 DP']
---
# [JSOI2009] 密码
## 题目描述

众所周知，密码在信息领域起到了不可估量的作用。对于普通的登陆口令以，唯一的破解方法就是暴力破解——逐个尝试所有可能的字母组合，但这是一项很耗时又容易被发现的工作。所以，为了获取对方的登陆口令，在暴力破解密码之前，必须先做大量的准备工作。经过情报的搜集，现在得到了若干有用信息，形如：

> ​     “我观察到，密码中含有字符串*。”

例如，对于一个 $10$ 位的密码以及观察到的字符串 `hello` 与 `world`，可能的密码组合为 `helloworld`与 `worldhello`；而对于 $6$ 位的密码以及到的字符串 `good` 与 `day`,可能的密码组合为 `gooday`。

有了这些信息，就能够大大地减少尝试的次数了。请编一个程序，计算所有密码组合的可能。密码中仅可能包含 `a-z` 之间的小写字母。
## 输入格式

输入数据首先输入两个整数 $L,N$，分别表示密码的长度与观察到子串的个数。

接下来 $N$ 行，每行若干个字符，描述了每个观察到的字符串。

## 输出格式

输出数据第一行为一个整数，代表了满足所有观察条件字符串的总数。

若这个数字小于等于 $42$，则按字典顺序输出所有密码的可能情况，每行一个，否则，只输出满足所有观察条件字符串的总数即可。

## 样例

### 样例输入 #1
```
10 2
hello
world
```
### 样例输出 #1
```
2
helloworld
worldhello
```
## 提示

对于 $100\%$ 的数据，$1\leq L\leq 25,1\leq N\leq 10$，每个观察到的字符串长不超过 $10$，并且保证输出结果小于 $2^{63}$。



---

---
title: "[JSOI2007] 文本生成器"
layout: "post"
diff: 省选/NOI-
pid: P4052
tag: ['动态规划 DP', '2007', '各省省选', '江苏', 'O2优化', 'AC 自动机']
---
# [JSOI2007] 文本生成器
## 题目描述

JSOI 交给队员 ZYX 一个任务，编制一个称之为“文本生成器”的电脑软件：该软件的使用者是一些低幼人群，他们现在使用的是 GW 文本生成器 v6 版。

该软件可以随机生成一些文章——总是生成一篇长度固定且完全随机的文章。 也就是说，生成的文章中每个字符都是完全随机的。如果一篇文章中至少包含使用者们了解的一个单词，那么我们说这篇文章是可读的（我们称文章 $s$ 包含单词 $t$，当且仅当单词 $t$ 是文章 $s$ 的子串）。但是，即使按照这样的标准，使用者现在使用的 GW 文本生成器 v6 版所生成的文章也是几乎完全不可读的。ZYX 需要指出 GW 文本生成器 v6 生成的所有文本中，可读文本的数量，以便能够成功获得 v7 更新版。你能帮助他吗？

答案对 $10^4 + 7$ 取模。
## 输入格式

第一行有两个整数，分别表示使用者了解的单词总数 $n$ 和生成的文章长度 $m$。

接下来 $n$ 行，每行一个字符串 $s_i$，表示一个使用者了解的单词。
## 输出格式

输出一行一个整数表示答案对 $10^4 + 7$ 取模的结果。
## 样例

### 样例输入 #1
```
2 2
A
B

```
### 样例输出 #1
```
100
```
## 提示

#### 数据规模与约定

对于全部的测试点，保证：

- $1 \leq n \leq 60$，$1 \leq m \leq 100$。
- $1 \leq |s_i| \leq 100$，其中 $|s_i|$ 表示字符串 $s_i$ 的长度。
- $s_i$ 中只含大写英文字母。


---

---
title: "[BJWC2011] 禁忌"
layout: "post"
diff: 省选/NOI-
pid: P4569
tag: ['字符串', '2011', '北京', 'Special Judge', '矩阵乘法', 'AC 自动机']
---
# [BJWC2011] 禁忌
## 题目描述

Magic Land上的人们总是提起那个传说：他们的祖先John在那个东方岛屿帮助Koishi与其姐姐Satori最终战平。而后，Koishi恢复了读心的能力……

如今，在John已经成为传说的时代，再次造访那座岛屿的人们却发现Koishi遇到了新麻烦。

这次她遇到了Flandre Scarlet——她拥有可以使用禁忌魔法而不会受到伤害的能力。

为了说明什么是禁忌魔法及其伤害，引入以下概念：

1. 字母集$A$上的每个非空字符串对应了一个魔法。其中$A$是包含了前alphabet个小写字母的集合。
2. 有一个集合$T$，包含了$N$个字母集$A$上的字符串。$T$中的每一串称为一个禁忌串（Taboo string）
3. 一个魔法，或等价地，其对应的串$s$因为包含禁忌而对使用者造成的伤害按以下方式确定：把$s$分割成若干段，考虑其中是禁忌串的段的数目，不同的分割可能会有不同的数目，其最大值就是这个伤害。

由于拥有了读心的能力，Koishi总是随机地使用Flandre Scarlet的魔法，可以确定的是，她的魔法正好对应字母集$A$上所有长度为$len$的串。

但是，Flandre Scarlet所使用的一些魔法是带有禁忌的，由于其自身特性，她可以使用禁忌魔法而不受到伤害，而Koishi就不同了。可怜的Koishi每一次使用对方的魔法都面临着受到禁忌伤害的威胁。

你现在需要计算的是如果Koishi使用对方的每一个魔法的概率是均等的，那么每一次随机使用魔法所受到的禁忌伤害的期望值是多少。
## 输入格式

第一行包含三个正整数 $N$、$len$、$alphabet$。  
接下来$N$行，每行包含一个串$T_i$，表示禁忌串。
## 输出格式

一个非负实数，表示所受到禁忌伤害的期望值。你的答案需要保证绝对误差不超过 $10^{-6}$。
## 样例

### 样例输入 #1
```
2 4 2
aa
abb
```
### 样例输出 #1
```
0.75

```
## 提示

【样例1解释】
一共有$2^4 = 16$种不同的魔法。

需要注意的是“aabb”的禁忌伤害是1而不是2。

### 数据范围

有不少于40%的数据中：$N = 1$。  
100%的数据中$N ≤ 5$，$len ≤10^9$，$1 ≤ alphabet ≤ 26$。  
数据保证每个串$T_i$的长度不超过$15$，并且不是空串。  
数据保证每个$T_i$均仅含有前$alphabet$个小写字母。  
数据保证集合$T$中没有相同的元素，即对任意不同的$i$和$j$，有$T_i \neq T_j$。


---

---
title: "[JSOI2012] 玄武密码"
layout: "post"
diff: 省选/NOI-
pid: P5231
tag: ['字符串', '2012', '各省省选', '江苏', '后缀自动机 SAM', 'O2优化', 'AC 自动机', '后缀数组 SA']
---
# [JSOI2012] 玄武密码
## 题目背景

在美丽的玄武湖畔，鸡鸣寺边，鸡笼山前，有一块富饶而秀美的土地，人们唤作进香河。相传一日，一缕紫气从天而至，只一瞬间便消失在了进香河中。老人们说，这是玄武神灵将天书藏匿在此。 

很多年后，人们终于在进香河地区发现了带有玄武密码的文字。更加神奇的是，这份带有玄武密码的文字，与玄武湖南岸台城的结构有微妙的关联。于是，漫长的破译工作开始了。
## 题目描述

 经过分析，我们可以用东南西北四个方向来描述台城城砖的摆放，不妨用一个长度为 $n$ 的序列 $s$ 来描述，序列中的元素分别是 `E`，`S`，`W`，`N`，代表了东南西北四向，我们称之为母串。而神秘的玄武密码是由四象的图案描述而成的 $m$ 段文字。这里的四象，分别是东之青龙，西之白虎，南之朱雀，北之玄武，对东南西北四向相对应。 

现在，考古工作者遇到了一个难题。对于每一段文字 $t$，求出其最长的前缀 $p$，满足 $p$ 是 $s$ 的子串。
## 输入格式

第一行有两个整数，分别表示母串的长度 $n$ 和文字段的个数 $m$。

第二行有一个长度为 $n$ 的字符串，表示母串 $s$。

接下来 $m$ 行，每行一个字符串，表示一段带有玄武密码的文字 $t$。
## 输出格式

对于每段文字，输出一行一个整数，表示最长的 $p$ 的长度。
## 样例

### 样例输入 #1
```
7 3
SNNSSNS
NNSS
NNN
WSEE

```
### 样例输出 #1
```
4
2
0
```
## 提示

#### 数据规模与约定

- 对于 $20\%$ 的数据，保证 $n \leq 100$，$m \leq 50$。
- 对于 $40\%$ 的数据，保证 $n \leq 2 \times 10^4$，$m \leq 2 \times 10^3$。
- 对于 $70\%$ 的数据，保证 $n \leq 10^6$，$m \leq 2 \times 10^4$。
- 对于 $100\%$ 的数据，保证 $1 \leq n \leq 10^7$，$1 \leq m \leq 10^5$，$1 \leq |t| \leq 100$，$s, t$ 中均只含字母 `E` `S` `W` `N`。


---

---
title: "[BJOI2019] 奥术神杖"
layout: "post"
diff: 省选/NOI-
pid: P5319
tag: ['2019', '各省省选', '北京', 'Special Judge', 'AC 自动机']
---
# [BJOI2019] 奥术神杖
## 题目描述

Bezorath 大陆抵抗地灾军团入侵的战争进入了僵持的阶段，世世代代生活在 Bezorath 这片大陆的精灵们开始寻找远古时代诸神遗留的神器，试图借助神器的神秘力量帮助她们战胜地灾军团。

在付出了惨痛的代价后，精灵们从步步凶险的远古战场取回了一件保存尚完好的神杖。但在经历过那场所有史书都视为禁忌的“诸神黄昏之战”后，神杖上镶嵌的奥术宝石已经残缺，神力也几乎消耗殆尽。精灵高层在至高会议中决定以举国之力收集残存至今的奥术宝石，并重金悬赏天下能工巧匠修复这件神杖。

你作为神术一脉第五百零一位传人，接受了这个艰巨而神圣的使命。
神杖上从左到右镶嵌了 $n$ 颗奥术宝石，奥术宝石一共有 $10$ 种，用数字 "`0123456789`" 表示。有些位置的宝石已经残缺，用 "`.`" 表示，你需要用完好的奥术宝石填补每一处残缺的部分（每种奥术宝石个数不限，且不能够更换未残缺的宝石）。古老的魔法书上记载了 $m$ 种咒语 $(S_i,V_i)$ ，其中 $S_i$ 是一个非空数字串，$V_i$ 是这种组合能够激发的神力。

神杖的初始神力值 $Magic = 1$，每当神杖中出现了连续一段宝石与 $S_i$ 相等时，神力值 $Magic$ 就会乘以 $V_i$。但神杖如果包含了太多咒语就不再纯净导致神力降低：设 $c$ 为神杖包含的咒语个数（若咒语类别相同但出现位置不同视为多次），神杖最终的神力值为 $ \sqrt[c]{Magic}$。（若 $c = 0$ 则神杖最终神力值为 $1$ ）

例如有两种咒语 $(01,3)$ 、$(10,4)$ ，那么神杖 “`0101`” 的神力值为 $\sqrt[3]{ 3 \times 4 \times 3}$

你需要使修复好的神杖的最终的神力值最大，输出任何一个解即可。
## 输入格式

第一行两个正整数 $n$ 、$m$ ，表示宝石数和咒语数。

第二行为一个长度为 $n$ 的字符串 $T$ ，表示初始的神杖。

接下来 $m$ 行每行一个非空数字串 $S_i$ 和一个正整数 $V_i$ ，表示每种咒语。
## 输出格式

输出最终神杖上从左到右镶嵌的宝石，多解时任意输出一个即可。
## 样例

### 样例输入 #1
```
4 3
....
1 2
2 2
3 1
```
### 样例输出 #1
```
2019
```
### 样例输入 #2
```
5 4
..0..
0 2
00 2
01 4
10 3
```
### 样例输出 #2
```
11012
```
### 样例输入 #3
```
18 6
...2.1.0.1..1.0..1
011 6
111 4
010 12
121 7
101 5
10 3
```
### 样例输出 #3
```
121211203112120121
```
## 提示

样例 1 ：法杖最终神力值为 $2$ 。

样例 2 ：法杖最终神力值为 $\sqrt[3]{2 \times 3 \times 4}$

设 $s = \sum_{i=1}^{m} |S_i|$ ，即所有咒语的串长之和。
![](https://cdn.luogu.com.cn/upload/pic/57052.png)


---

---
title: "[COCI 2015] Divljak"
layout: "post"
diff: 省选/NOI-
pid: P5840
tag: ['2015', '线段树', '树状数组', 'AC 自动机', '差分', 'COCI（克罗地亚）']
---
# [COCI 2015] Divljak
## 题目描述

Alice 有 $n$ 个字符串 ${S}_1, {S}_2, \ldots, {S}_n$，Bob 有一个字符串集合 ${T}$，一开始集合是空的。

接下来会发生 $q$ 个操作，操作有两种形式：

1. `1 P`：Bob 往自己的集合里添加了一个字符串 ${P}$。
2. `2 x`：Alice 询问 Bob，集合 ${T}$ 中有多少个字符串包含串 ${S}_x$（我们称串 ${A}$ 包含串 ${B}$，当且仅当 ${B}$ 是 ${A}$ 的子串）。
## 输入格式

第一行一个整数 $n$。

接下来 $n$ 行，第 $i$ 行一个字符串 ${S}_i$。

接下来一行一个整数 $q$。

接下来 $q$ 行，每行一个操作。
## 输出格式

对每个 `2 x` 操作，一行一个整数，表示答案。
## 样例

### 样例输入 #1
```
3
a
bc
abc
5
1 abca
2 1
1 bca
2 2
2 3

```
### 样例输出 #1
```
1
2
1

```
## 提示

对于 $100\%$ 的数据，$1 \leq n,q \leq 10^5$，字符串由小写字母构成，$S$ 和 $P$ 的总长分别 $\le 2 \times 10^6$。



---

---
title: "[JSOI2009] 有趣的游戏"
layout: "post"
diff: 省选/NOI-
pid: P6125
tag: ['字符串', '动态规划 DP', '2009', '高斯消元', 'AC 自动机']
---
# [JSOI2009] 有趣的游戏
## 题目描述

小阳阳发明了一个有趣的游戏：有 $n$ 个玩家，每个玩家都有一个长度为 $l$ 的字母序列，任何两个玩家的字母序列不同。共有 $m$ 种不同的字母，所有的字母序列都由这 $m$ 种字母构成。为了方便，我们取大写字母的前 $m$ 个字母。   
例如 $m=3,l=4,\texttt{ABAA}$ 和 $\texttt{CBCA}$ 是两个合法的字母序列。       
现在由小阳阳来操控一台神奇的机器，每个时刻机器会随机产生一个字母，其中第 $i$ 种字母随机出来的概率为 $\dfrac{p_i}{q_i}$ ，显然 $\sum \limits_{k=1}^m \dfrac{p_i}{q_i}=1$。  
这样 $T$ 个时刻后机器会产生一个长度为 $T$ 的字母序列。  
如果某个时刻某个玩家发现自己的字母序列在机器产生的字母序列中出现了，“出现”的定义是玩家的字母序列是机器产生的字母序列中连续的一段，那么我们称这个玩家获胜，游戏结束。       
现在小阳阳感兴趣的一个问题是，每个玩家分别有多大的概率能获得这场游戏的胜利呢？  
## 输入格式

第一行有三个正整数 $n,l,m$ 表示有 $n$ 个人，每个字母的序列长度均为 $l$，共有 $m$ 个字母。   
接下来 $m$ 行，每行有两个非负整数 $p, q$，表示随机到第 $i$ 个字母的概率为 $\frac{p}{q}$。   
接下来 $n$ 行，每行有一个长度为 $l$ 的字母序列，表示第 $i$ 个人的字母序列。
## 输出格式

包含 $n$ 行，每行一个实数，表示第 $i$ 个人获胜的概率，输出结果四舍五入到两位小数。 
## 样例

### 样例输入 #1
```
3 2 2
1 2
1 2
AB
BA
AA
```
### 样例输出 #1
```
0.25
0.50
0.25
```
### 样例输入 #2
```
3 4 2
1 2
1 2
AABA
ABAA
BAAA
```
### 样例输出 #2
```
0.31
0.33
0.37
```
## 提示

$1 \leq n,l,m \leq 10$，$0 \leq p_i \leq q_i \leq 10$ 且 $\gcd(p,q) = 1$。


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
title: "[LSOT-1] Crosspain"
layout: "post"
diff: 省选/NOI-
pid: P8451
tag: ['洛谷原创', '树论', 'AC 自动机']
---
# [LSOT-1] Crosspain
## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/xcjot9ob.png)
## 题目描述

令 $S_0=\varnothing$，维护一个数据结构，要求支持以下操作：
- `1 hoc s`，令 $S_i=S_{hoc}\cup\{s\}$，其中 $s$ 是字符串（保证操作前 $s\notin S_{hoc}$） .
- `2 hoc s`，令 $S_i=S_{hoc}$，并查询 $S_i$ 中的所有字符串在给出的字符串 $s$ 中出现的次数之和 .
## 输入格式

第一行包含一个正整数 $q$，表示询问次数 .

接下来 $q$ 行，每行一个操作，格式见题目描述 .
## 输出格式

对于每个操作 2，输出一行答案 .
## 样例

### 样例输入 #1
```
5
1 0 abc
2 0 abc
1 2 def
2 3 defg
2 1 abcd
```
### 样例输出 #1
```
0
1
1
```
## 提示

### 样例解释

第三行中，询问版本 $0$ 中的串在 `abc` 中出现几次，因为版本 $0$ 为空，所以出现 $0$ 次 .

第五行中，询问版本 $3$ 中的串在 `defg` 中出现几次，因为版本 $3$ 有字符串 `def`，所以出现 $1$ 次 .

第六行中，询问版本 $1$ 中的串在 `abcd` 中出现几次，因为版本 $1$ 有字符串 `abc`，所以出现 $1$ 次 .

### 数据范围及约定

**「本题采用捆绑测试」**

- $\texttt{Subtask 1(10 pts)：} \displaystyle \sum|s_i|\le 1000$；
- $\texttt{Subtask 2(20 pts)：}$所有添加的字符串长度相同；
- $\texttt{Subtask 3(20 pts)：}$所有添加的字符串只包含一种字符；
- $\texttt{Subtask 4(20 pts)：}q\le 10^3$；
- $\texttt{Subtask 5(30 pts)：}$无特殊限制。

对于全部数据，$1\le q\le  5\times10^5$，$\displaystyle 1\le \sum_i|s_i|\le 10^6$ . 所有字符串仅含小写字母 .


---

---
title: "[CERC2019] K==S"
layout: "post"
diff: 省选/NOI-
pid: P9613
tag: ['动态规划 DP', '2019', '矩阵乘法', 'AC 自动机', 'ICPC']
---
# [CERC2019] K==S
## 题目背景

**题目译自 [CERC 2019](https://contest.felk.cvut.cz/19cerc/solved.html) 「[K==S](https://contest.felk.cvut.cz/19cerc/solved/kequalss.pdf)」**
## 题目描述

渐进式硬八度摇滚曲调（所谓的“phorts”）是使用特定的音符创作的。这种摇滚风格只建立在 $13$ 个不同的音符音高上，其他音高（在其他八度中）被认为是过时的音乐基石。每个音符可以是长的，也可以是短的。因此，摇滚中正好有 $26$ 个不同的音符。

你将在你朋友的生日之际创作一首 phort 曲调，并与你的乐队在主要的城市广场上表演。在创作词缀时，你需要避免使用某些音乐短语，这些短语由于大型唱片公司赞助的长期研究而受到版权保护。已经证实，这些短语非常朗朗上口，易于记忆，可以用来将听众下意识地与某个特定的音乐公司联系起来，该公司会在他们的制作中使用这些短语。

曲调是一连串的音符。一个音乐短语也是一个音符序列，如果它的音符形成曲调的连续子序列，则它被认为包含在曲调中，这意味着相同的音符以相同的顺序出现在曲调中。

幸运的是，到目前为止，只有少数禁用短语获得了专利。因此，你可以相对自由地创作自己的曲调。特别是，您对某些长度的可接受的曲调的数量感兴趣。可接受的曲调是指任何不包含禁用短语的曲调。曲调的长度等于它所包含的音符数。
## 输入格式

第一行包含两个整数 $N, Q\ (1\le N\le 10^9, 1\le Q\le 100)$。$N$ 是曲调的长度，$Q$ 是禁用音乐短语的数量。

接下来 $Q$ 行，每行都描述了一个禁用短语。禁用短语的描述以一个表示其长度的正整数 $L$ 开头，后跟一个由 $L$ 个小写英文字母组成的字符串。每个字母代表一个摇滚音符，不同的字母代表不同的音符。

所有禁用短语的长度总和不超过 $100$。
## 输出格式

输出长度为 $N$ 的不同可接受曲调的数量对 $1\,000\,000\,007$ 取模的值。
## 样例

### 样例输入 #1
```
2 3
1 a
1 b
1 c

```
### 样例输出 #1
```
529

```
### 样例输入 #2
```
3 3
2 aa
1 a
1 a

```
### 样例输出 #2
```
15625

```
### 样例输入 #3
```
3 1
2 ab

```
### 样例输出 #3
```
17524

```


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

