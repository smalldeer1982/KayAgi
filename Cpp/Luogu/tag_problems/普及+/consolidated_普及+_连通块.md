---
title: "「Cfz Round 5」Mata rainen"
layout: "post"
diff: 普及+/提高
pid: P11486
tag: ['洛谷原创', 'Special Judge', 'O2优化', '连通块', '树论', '构造', '洛谷月赛']
---
# 「Cfz Round 5」Mata rainen
## 题目背景

[English statement](https://www.luogu.com.cn/problem/U517657). **You must submit your code at the Chinese version of the statement.**

---

题目名称意为：明年见。

小 R 是一个正在上高三的女孩子。她在升入高三的暑假复习了[《种树郭橐（tuó）驼传》](https://baike.baidu.com/item/%E7%A7%8D%E6%A0%91%E9%83%AD%E6%A9%90%E9%A9%BC%E4%BC%A0)，便编出了这道与树有关的题。

在把这道题目丢给出题组后，她决定把全部时间和精力投入到高考的旅程中，期待在 2025 年的暑假在算法竞赛中与大家再会。
## 题目描述

请判断是否存在一棵树满足如下条件。若存在，请尝试给出构造。

树中包含 $n$ 个结点，编号为 $1\sim n$。另外，给定 $m$ 个点对 $(s_i,t_i)$，要求树上这 $m$ 条从点 $s_i$ 到点 $t_i$ 的路径覆盖每条边**恰好**一次 $^\dagger$。

**若你正确判断了是否有解，但不会构造出这棵树，也可以获得一定的分数，详见【评分方式】。**

$\dagger$ 称从点 $s$ 到点 $t$ 的路径覆盖一条边 $(u,v)$，当且仅当边 $(u,v)$ 在点 $s$ 到点 $t$ 的最短路径上。
## 输入格式

第一行包含两个整数 $n,m$，表示这棵树的点数和给出的点对数。

接下来 $m$ 行，每行两个整数 $s_i,t_i$，表示一个点对。
## 输出格式

第一行输出一个字符串 `Yes` 或 `No`（大小写不敏感），表示是否有解。

若有解，继续输出 $n-1$ 行，每行包含两个整数 $u_i,v_i$，描述一条边。**你需要保证 $\bm{1\le u_i,v_i\le n}$ 且所有边构成一棵树。**
## 样例

### 样例输入 #1
```
6 2
1 2
3 4
```
### 样例输出 #1
```
Yes
1 5
2 5
3 5
4 6
5 6
```
### 样例输入 #2
```
3 3
1 2
2 3
1 3
```
### 样例输出 #2
```
No
```
## 提示

#### 「样例解释 #1」

![](https://cdn.luogu.com.cn/upload/image_hosting/rgnwakkq.png)

左上图为样例输出中给出的树。边 $(1,5),(5,2)$ 被路径 $(1,2)$ 覆盖，边 $(3,5),(5,6),(6,4)$ 被路径 $(3,4)$ 覆盖，符合题目要求。

右上图中边 $(5,6)$ 被路径 $(1,2)$ 和 $(3,4)$ 覆盖，不符合题目要求。

左下图中边 $(5,6)$ 未被任何路径覆盖，不符合题目要求。

右下图不是一棵树，不符合题目要求。

#### 「样例解释 #2」

可以证明不存在符合要求的树。

#### 「评分方式」

本题采用自定义校验器（Special Judge）进行评测。

对于每个测试点：

- 若第一行格式错误或与答案不匹配（大小写不敏感），得 $0\%$ 的分数。
- 若第一行答案正确且为 `No`，得 $100\%$ 的分数。
- 若第一行答案正确且为 `Yes`，**但后 $n-1$ 行格式错误**，得 $0\%$ 的分数。  
因此，**请务必保证输出为一棵树**。
- 若第一行答案正确且为 `Yes`，后 $n-1$ 行格式正确但树不符合要求，得 $20\%$ 的分数。
- 若第一行答案正确且为 `Yes`，后 $n-1$ 行格式正确且树符合要求，得 $100\%$ 的分数。

也就是说，对于第一个样例，在正确输出 `Yes` 的基础上，输出左上图可以得到满分，输出右上图、左下图可以得到 $20\%$ 的分数，输出右下图不能得到任何分数；对于第二个样例，正确输出 `No` 即可得到满分。

#### 「数据范围」

对于所有测试数据，保证：

- $2\le n\le 3\times 10^5$；
- $1\le m\le 3\times 10^5$；
- $1\le s_i,t_i\le n$ 且 $s_i\ne t_i$。

**本题采用捆绑测试。**

- Subtask 0（10 points）：$n\le 3$，$m\le 3$。
- Subtask 1（10 points）：$n\le 10$，$m\le 10$。
- Subtask 2（20 points）：$m=1$。
- Subtask 3（10 points）：$n\le 300$，$m\le 300$。
- Subtask 4（10 points）：$n\le 2\times 10^3$，$m\le 2\times 10^3$。
- Subtask 5（20 points）：$m\le 2\times 10^3$。
- Subtask 6（20 points）：无特殊限制。

#### 「Hack 数据」

本题于赛后添加了部分 Hack 数据。这些数据均满足 Subtask 6 对数据规模的限制，他们被添加到 Subtask 7 中。这些数据不计分，但只有通过所有数据，才算做 AC 本题。

- Subtask 7（0 points）：赛后添加的 Hack 数据。


---

---
title: "[JSOI2008] 星球大战"
layout: "post"
diff: 普及+/提高
pid: P1197
tag: ['2008', '并查集', '各省省选', '江苏', '连通块']
---
# [JSOI2008] 星球大战
## 题目描述

很久以前，在一个遥远的星系，一个黑暗的帝国靠着它的超级武器统治着整个星系。

某一天，凭着一个偶然的机遇，一支反抗军摧毁了帝国的超级武器，并攻下了星系中几乎所有的星球。这些星球通过特殊的以太隧道互相直接或间接地连接。

但好景不长，很快帝国又重新造出了他的超级武器。凭借这超级武器的力量，帝国开始有计划地摧毁反抗军占领的星球。由于星球的不断被摧毁，两个星球之间的通讯通道也开始不可靠起来。

现在，反抗军首领交给你一个任务：给出原来两个星球之间的以太隧道连通情况以及帝国打击的星球顺序，以尽量快的速度求出每一次打击之后反抗军占据的星球的连通块的个数。（如果两个星球可以通过现存的以太通道直接或间接地连通，则这两个星球在同一个连通块中）。
## 输入格式

输入文件第一行包含两个整数，$n,m$，分别表示星球的数目和以太隧道的数目。星球用 $0 \sim n-1$ 的整数编号。

接下来的 $m$ 行，每行包括两个整数 $x,y$，表示星球 $x$ 和星球 $y$ 之间有 “以太” 隧道，可以直接通讯。

接下来的一行为一个整数 $k$ ，表示将遭受攻击的星球的数目。

接下来的 $k$ 行，每行有一个整数，按照顺序列出了帝国军的攻击目标。这 $k$ 个数互不相同，且都在 $0$ 到 $n-1$ 的范围内。
## 输出格式

第一行是开始时星球的连通块个数。接下来的 $k$ 行，每行一个整数，表示经过该次打击后现存星球的连通块个数。
## 样例

### 样例输入 #1
```
8 13
0 1
1 6
6 5
5 0
0 6
1 2
2 3
3 4
4 5
7 1
7 2
7 6
3 6
5
1
6
3
5
7

```
### 样例输出 #1
```
1
1
1
2
3
3
```
## 提示

【数据范围】  
对于 $100\%$ 的数据，$1\le m \le 2\times 10^5$，$1\le n \le 2m$，$x \neq y$。

[JSOI2008]



---

---
title: "[蓝桥杯 2023 省 Java B] 合并区域"
layout: "post"
diff: 普及+/提高
pid: P12328
tag: ['模拟', '搜索', '2023', '连通块', '蓝桥杯省赛']
---
# [蓝桥杯 2023 省 Java B] 合并区域
## 题目背景

本题测试数据可能较水，仅供参考。
## 题目描述

小蓝在玩一款种地游戏。现在他被分配给了两块大小均为 $N \times N$ 的正方形区域。这两块区域都按照 $N \times N$ 的规格进行了均等划分，划分成了若干块面积相同的小区域，其中每块小区域要么是岩石，要么就是土壤，在垂直或者水平方向上相邻的土壤可以组成一块土地。现在小蓝想要对这两块区域沿着边缘进行合并，他想知道合并以后可以得到的最大的一块土地的面积是多少（土地的面积就是土地中土壤小区域的块数）？

在进行合并时，小区域之间必须对齐。可以在两块方形区域的任何一条边上进行合并，可以对两块方形区域进行 $90$ 度、$180$ 度、$270$ 度、$360$ 度的旋转，但不可以进行上下或左右翻转，并且两块方形区域不可以发生重叠。
## 输入格式

第一行一个整数 $N$ 表示区域大小。

接下来 $N$ 行表示第一块区域，每行 $N$ 个值为 $0$ 或 $1$ 的整数，相邻的整数之间用空格进行分隔。值为 $0$ 表示这块小区域是岩石，值为 $1$ 表示这块小区域是土壤。

再接下来 $N$ 行表示第二块区域，每行 $N$ 个值为 $0$ 或 $1$ 的整数，相邻的整数之间用空格进行分隔。值为 $0$ 表示这块小区域是岩石，值为 $1$ 表示这块小区域是土壤。

## 输出格式

一个整数表示将两块区域合并之后可以产生的最大的土地面积。
## 样例

### 样例输入 #1
```
4
0 1 1 0
1 0 1 1
1 0 1 0
1 1 1 0
0 0 1 0
0 1 1 0
1 0 0 0
1 1 1 1
```
### 样例输出 #1
```
15
```
## 提示

### 样例说明

第一张图展示了样例中的两块区域的布局。第二张图展示了其中一种最佳的合并方式，此时最大的土地面积为 $15$。

![](https://cdn.luogu.com.cn/upload/image_hosting/5eaxcwcv.png)

### 评测用例规模与约定

- 对于 $30\%$ 的数据，$1 \leq N \leq 5$。
- 对于 $60\%$ 的数据，$1 \leq N \leq 15$。
- 对于 $100\%$ 的数据，$1 \leq N \leq 50$。


---

---
title: "[USACO17FEB] Why Did the Cow Cross the Road III S"
layout: "post"
diff: 普及+/提高
pid: P3663
tag: ['2017', 'USACO', '广度优先搜索 BFS', '深度优先搜索 DFS', '连通块']
---
# [USACO17FEB] Why Did the Cow Cross the Road III S
## 题目描述

Why did the cow cross the road? Well, one reason is that Farmer John's farm simply has a lot of roads, making it impossible for his cows to travel around without crossing many of them.

FJ's farm is arranged as an $N \times N$ square grid of fields ($2 \leq N \leq 100$), Certain pairs of adjacent fields (e.g., north-south or east-west) are separated by roads, and a tall fence runs around the external perimeter of the entire grid, preventing cows from leaving the farm. Cows can move freely from any field to any other adjacent field (north, east, south, or west), although they prefer not to cross roads unless absolutely necessary.

There are $K$ cows ($1 \leq K \leq 100, K \leq N^2$) on FJ's farm, each located in a different field. A pair of cows is said to be "distant" if, in order for one cow to visit the other, it is necessary to cross at least one road. Please help FJ count the number of distant pairs of cows.
## 输入格式

The first line of input contains $N$, $K$, and $R$. The next $R$ lines describe $R$ roads that exist between pairs of adjacent fields. Each line is of the form $r$ $c$ $r'$ $c'$ (integers in the range $1 \ldots N$), indicating a road between the field in (row $r$, column $c$) and the adjacent field in (row $r'$, column $c'$). The final $K$ lines indicate the locations of the $K$ cows, each specified in terms of a row and column.
## 输出格式

Print the number of pairs of cows that are distant.
## 样例

### 样例输入 #1
```
3 3 3
2 2 2 3
3 3 3 2
3 3 2 3
3 3
2 2
2 3
```
### 样例输出 #1
```
2
```
## 题目翻译

### 题目描述

奶牛为什么要过马路？其中一个原因是 Farmer John 的农场有很多道路，使得他的奶牛在四处走动时不可避免地要穿过许多道路。

FJ 的农场被安排成一个 $N \times N$ 的方形网格田地（$2 \leq N \leq 100$），某些相邻的田地（例如南北向或东西向）被道路分隔，整个网格的外部有一圈高高的围栏，防止奶牛离开农场。奶牛可以从任何田地自由移动到相邻的田地（北、东、南或西），尽管它们除非绝对必要，否则不愿意穿过道路。

农场上有 $K$ 头奶牛（$1 \leq K \leq 100, K \leq N^2$），每头奶牛位于不同的田地。如果一头奶牛要拜访另一头奶牛时必须至少穿过一条道路，那么这对奶牛被称为“远距离”对。请帮助 FJ 计算远距离奶牛对的数量。

### 输入格式

输入的第一行包含 $N$、$K$ 和 $R$。接下来的 $R$ 行描述了 $R$ 条存在于相邻田地之间的道路。每行的格式为 $r$ $c$ $r'$ $c'$（范围为 $1 \ldots N$ 的整数），表示位于（行 $r$，列 $c$）的田地与相邻的（行 $r'$，列 $c'$）的田地之间有一条道路。最后的 $K$ 行表示 $K$ 头奶牛的位置，每行用行和列指定。

### 输出格式

输出远距离奶牛对的数量。


---

---
title: "[USACO17OPEN] Where's Bessie? S"
layout: "post"
diff: 普及+/提高
pid: P3671
tag: ['搜索', '2017', 'USACO', '枚举', '连通块']
---
# [USACO17OPEN] Where's Bessie? S
## 题目描述

Always known for being quite tech-savy, Farmer John is testing out his new automated drone-mounted cow locator camera, which supposedly can take a picture of his field and automatically figure out the location of cows. Unfortunately, the camera does not include a very good algorithm for finding cows, so FJ needs your help developing a better one.


The overhead image of his farm taken by the camera is described by an $N \times N$ grid of characters, each in the range $A \ldots Z$, representing one of 26 possible colors. Farmer John figures the best way to define a potential cow location (PCL) is as follows: A PCL is a rectangular sub-grid (possibly the entire image) with sides parallel to the image sides, not contained within any other PCL (so no smaller subset of a PCL is also a PCL).  Furthermore, a PCL must satisfy the following property: focusing on just the contents of the rectangle and ignoring the rest of the image, exactly two colors must be present, one forming a contiguous region and one forming two or more contiguous regions.



```cpp
AAAAA
ABABA
AAABB
```



For example, a rectangle with contents would constitute a PCL, since the A's form a single contiguous region and the B's form more than one contiguous region. The interpretation is a cow of color A with spots of color B. 

A region is "contiguous" if you can traverse the entire region by moving repeatedly from one cell in the region to another cell in the region taking steps up, down, left, or right. 

Given the image returned by FJ's camera, please count the number of PCLs.

## 输入格式

The first line of input contains $N$, the size of the grid ($1 \leq N \leq 20$).

The next $N$ lines describe the image, each consisting of $N$ characters.

## 输出格式

Print a count of the number of PCLs in the image.

## 样例

### 样例输入 #1
```
4
ABBC
BBBC
AABB
ABBC
```
### 样例输出 #1
```
2
```
## 提示

In this example, the two PCLs are the rectangles with contents

```cpp
ABB
BBB
AAB
ABB
```


and

```
BC
BC
BB
BC
```
## 题目翻译

## 题目描述

Farmer John 一直以精通技术而闻名，他正在测试他的新型无人机搭载的奶牛定位相机。这款相机据说可以拍摄他的田地并自动确定奶牛的位置。不幸的是，相机的算法并不擅长寻找奶牛，因此 Farmer John 需要你的帮助来开发一个更好的算法。

相机拍摄的农场俯视图由一个 $N \times N$ 的字符网格描述，每个字符在 $A \ldots Z$ 范围内，代表 26 种可能的颜色之一。Farmer John 认为，定义潜在奶牛位置（PCL）的最佳方式如下：一个 PCL 是一个矩形子网格（可能是整个图像），其边与图像的边平行，并且不包含在任何其他 PCL 中（因此 PCL 的较小子集不能也是 PCL）。此外，PCL 必须满足以下属性：仅关注矩形内的内容并忽略图像的其余部分，必须恰好存在两种颜色，其中一种颜色形成一个连续区域，另一种颜色形成两个或更多连续区域。

例如，一个矩形的内容如下：

```
AAAAA  
ABABA  
AAABB  
```

这将构成一个 PCL，因为 A 形成一个连续区域，而 B 形成多个连续区域。解释为一只颜色为 A 的奶牛带有颜色为 B 的斑点。

一个区域是“连续的”，如果可以通过向上、向下、向左或向右移动，从一个区域中的单元格反复移动到另一个区域中的单元格来遍历整个区域。

给定 Farmer John 的相机返回的图像，请计算 PCL 的数量。

## 输入格式

输入的第一行包含 $N$，表示网格的大小（$1 \leq N \leq 20$）。

接下来的 $N$ 行描述图像，每行包含 $N$ 个字符。

## 输出格式

输出图像中 PCL 的数量。

## 说明/提示

在这个例子中，两个 PCL 分别是内容如下的矩形：

```
ABB  
BBB  
AAB  
ABB
```

和

```
BC  
BC  
BB  
BC  
```


---

---
title: "「C.E.L.U-02」学术精神"
layout: "post"
diff: 普及+/提高
pid: P7474
tag: ['动态规划 DP', '数学', 'Special Judge', '动态规划优化', '连通块', '期望']
---
# 「C.E.L.U-02」学术精神
## 题目描述

提供 **一句话题意** 阅读。

某地有 $n$ 个小朋友，每个小朋友都有一个**独特的**  idea，其中第 $i$ 个小朋友的 idea 的 **编号** 为 $i$。老师让这个每一个小朋友在一组编号分别为 $1\sim n$ 的卡片中随机抽一个，**抽完后把卡片放回去**，这个小朋友会和编号为卡片上数字的小朋友**交换** idea（交换指**两人**把**所有**自己知道的 idea 告诉对方）。因为自己和自己交换 idea 在他们眼中也许是一件很傻的事情，所以如果**卡片上的编号与自己的相同**，他将再抽一次（此时他已经把卡片放回去了），**直到编号不是自己**的为止。

不久，每个小朋友都抽完了一遍，每个小朋友将把收集到的**所有** idea 出成一场比赛，因为有 idea 的交换，有很多比赛之间都是**有联系**的。

如果两场比赛中存在 idea **相同**的题目，我们认为这两场比赛是有联系的。「联系」具有**传递性**：**如果比赛 $\mathbf A$、$\mathbf B$ 有联系，比赛 $\mathbf B$、$\mathbf C$ 有联系，则比赛 $\mathbf A$、$\mathbf C$ 也有联系**。为了避免理解错误，在这举一个例子：

若仅有四场比赛：比赛一出现了 idea $1$、$2$；比赛二出现 idea $2$、$5$ ；比赛三出现 idea $3$、$5$、$8$，比赛四出现 idea $4$、$7$。则比赛一、二之间有**直接联系**。比赛一、三之间虽然没有公共 idea，但它们之间是**有联系**的。比赛四与其他所有比赛没有联系。  

而所有有联系的比赛都将属于同一个比赛集，没有联系的比赛处在不同的比赛集。

上例中比赛一、二、三属于一个比赛集，比赛四属于另一个。

求所有人**抽球卡片的次数和**的期望 $E_0$ 和比赛集的个数 $s$ 的期望 $E_1$。

---

**一句话题意：**

对于每个点 $i$ 随机与 $[1,n]$ 中的一点连无向边，若连向自己，则保留该边并再次连边，一直重复至连到别的点上为止，求边数与连通块个数期望。
## 输入格式

输入一行一个正整数 $n$。
## 输出格式

第一行输出一个数 $E_0$ ，第二行输出一个数 $E_1$ ，可以证明它们都是**有理数**。

为了避免精度误差，您只需要输出它们对质数 $998244353$ 取模的结果即可，如果您不会分数取模，您可以查找关于费马小定理与乘法逆元的相关资料。

如果输出格式错误或两问答案均错误，该测试点得 $0$ 分；

如果仅答对第一问，该测试点得 $3$ 分；

如果仅答对第二问，该测试点得 $7$ 分；

如果两问均正确，该测试点得 $10$ 分。

**请务必输出两个整数。**
## 样例

### 样例输入 #1
```
2
```
### 样例输出 #1
```
4
1
```
### 样例输入 #2
```
7
```
### 样例输出 #2
```
166374067
539688692
```
## 提示

---

### 样例解释  

**样例解释一**

- 每个小朋友摸卡片次数为 $1$ 的概率为 $\dfrac{1}{2}$，摸卡片次数为 $2$ 的概率为 $\dfrac{1}{4}$，摸卡片次数为 $i$ 的期望次数为 $\dfrac{1}{2^i}$，期望摸卡片次数为 $2$，总摸卡片次数为 $4$。

- $1$ 号小朋友一定会和 $2$ 号小朋友交换 idea，所以他们出的比赛之间一定是属于同一个比赛集。$E_1=1$。

**样例解释二**

- 第一问取模前的答案为 $\dfrac{49}{6}$。

- 第二问取模前的答案为 $\dfrac{2245}{1944}$。

---

### 数据范围

| 测试点编号 | $n$ | 测试点编号 | $n$ | 
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $\leq 3$ | $5$ | $\leq 1000$ |
| $2$ | $\leq 5$ | $6$ | $\leq 2000$ | 
| $3$ | $\leq 9$ | $7\sim8$ | $\leq 5000$ | 
| $4$ | $\leq 12$ | $9\sim 10$ | $\leq10^4$ | 

对于 $100\%$ 的数据，有 $2\leq n\leq10^4$。

---



---

---
title: "[USACO22OPEN] Visits S"
layout: "post"
diff: 普及+/提高
pid: P8269
tag: ['USACO', '2022', '拓扑排序', '连通块', '强连通分量', '基环树']
---
# [USACO22OPEN] Visits S
## 题目描述

Bessie 的 $N$（$2\le N\le 10^5$）个奶牛伙伴（编号为 $1\cdots N$）每一个都拥有自己的农场。对于每个 $1\le i\le N$，伙伴 i 想要访问伙伴 $a_i$（$a_i\neq i$）。

给定 $1\ldots N$ 的一个排列 $(p_1,p_2,\ldots, p_N)$，访问按以下方式发生。

对于 $1$ 到 $N$ 的每一个 $i$：

- 如果伙伴 $a_{p_i}$ 已经离开了她的农场，则伙伴 $p_i$ 仍然留在她的农场。
- 否则，伙伴 $p_i$ 离开她的农场去访问伙伴 $a_{p_i}$ 的农场。这次访问会产生快乐的哞叫 $v_{p_i}$ 次（$0\le v_{p_i}\le 10^9$）。


对于所有可能的排列 $p$，计算所有访问结束后可能得到的最大哞叫次数。
## 输入格式

输入的第一行包含 $N$。

对于每一个 $1\le i\le N$，第 $i+1$ 行包含两个空格分隔的整数 $a_i$ 和 $v_i$。
## 输出格式

输出一个整数，为所求的答案。

**注意这个问题涉及到的整数可能需要使用 64 位整数型（例如，C/C++ 中的 "long long"）。**
## 样例

### 样例输入 #1
```
4
2 10
3 20
4 30
1 40
```
### 样例输出 #1
```
90
```
## 提示

【样例解释】


如果 $p=(1,4,3,2)$，则

- 伙伴 $1$ 访问伙伴 $2$ 的农场，产生 $10$ 次哞叫。
- 伙伴 $4$ 看到伙伴 $1$ 已经离开了农场，所以无事发生。
- 伙伴 $3$ 访问伙伴 $4$ 的农场，又产生 $30$ 次哞叫。
- 伙伴 $2$ 看到伙伴 $3$ 已经离开了农场，所以无事发生。

这样总计得到了 $10+30=40$ 次哞叫。

另一方面，如果 $p=(2,3,4,1)$，则

- 伙伴 $2$ 访问伙伴 $3$ 的农场，产生 $20$ 次哞叫。
- 伙伴 $3$ 访问伙伴 $4$ 的农场，产生 $30$ 次哞叫。
- 伙伴 $4$ 访问伙伴 $1$ 的农场，产生 $40$ 次哞叫。
- 伙伴 $1$ 看到伙伴 $2$ 已经离开了农场，所以无事发生。

这样总计得到了 $20+30+40=90$ 次哞叫。可以证明这是所有可能的排列 $p$ 中访问结束后得到的最大可能的哞叫次数。


---

---
title: "【模板】点双连通分量"
layout: "post"
diff: 普及+/提高
pid: P8435
tag: ['图论', 'Special Judge', '连通块', 'Tarjan']
---
# 【模板】点双连通分量
## 题目描述

对于一个 $n$ 个节点 $m$ 条无向边的图，请输出其点双连通分量的个数，并且输出每个点双连通分量。
## 输入格式

第一行，两个整数 $n$ 和 $m$。

接下来 $m$ 行，每行两个整数 $u, v$，表示一条无向边。
## 输出格式

第一行一个整数 $x$ 表示点双连通分量的个数。

接下来的 $x$ 行，每行第一个数 $a$ 表示该分量结点个数，然后 $a$ 个数，描述一个点双连通分量。

你可以以任意顺序输出点双连通分量与点双连通分量内的结点。
## 样例

### 样例输入 #1
```
5 8
1 3
2 4
4 3
1 2
4 5
5 1
2 4
1 1
```
### 样例输出 #1
```
1
5 1 2 3 4 5
```
### 样例输入 #2
```
5 3
1 2
2 3
1 3
```
### 样例输出 #2
```
3
1 4
1 5
3 1 2 3
```
### 样例输入 #3
```
6 5
1 3
2 4
1 2
4 6
2 3
```
### 样例输出 #3
```
4
2 6 4
2 4 2
3 3 2 1
1 5
```
### 样例输入 #4
```
7 8
1 3
2 4
3 5
2 5
6 4
2 5
6 3
2 7
```
### 样例输出 #4
```
3
2 7 2
5 5 2 4 6 3
2 3 1
```
### 样例输入 #5
```
1 1
1 1
```
### 样例输出 #5
```
1
1 1
```
## 提示

**样例四解释：**

![](https://cdn.luogu.com.cn/upload/image_hosting/huvwgbuo.png)

相同颜色的点为同一个分量里的结点。

**温馨提示：请认真考虑孤立点与自环（样例五）的情况。**

------------
**数据范围：**
对于 $100\%$ 的数据，$1 \le n \le 5 \times10 ^5$，$1 \le m \le 2 \times 10^6$。

| subtask | $n$ | $m$ | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $1 \le n \le 100$ | $1 \le m \le 500$ | $25$ |
| $2$ | $1 \le n \le 5000$ | $1 \le m \le 5 \times 10^4$ | $25$ |
| $3$ | $1 \le n \le 2\times 10^5$ | $1 \le m \le 5\times 10^5$ | $25$ |
| $4$ | $1 \le n \le 5 \times10 ^5$ | $1 \le m \le 2 \times 10^6$ | $25$ |

本题不卡常，时间限制与空间限制均已开大，正确的解法均可通过。

------------

### 数据更新
- $2022/7/14$ 加强数据
- $2022/11/26$  新增 $10$ 组较小的数据（$1\le n, m \le 10$)，方便选手调试。
- $2022/12/31$ 重组 $subtask$，并加入若干组极端数据。
- $2023/1/1$ 发现昨天新加入的数据出了问题，已修改。
------------

惊喜：AC 后记得把鼠标放到测试点上看反馈信息，有惊喜哦。


---

---
title: "【模板】边双连通分量"
layout: "post"
diff: 普及+/提高
pid: P8436
tag: ['图论', 'Special Judge', '连通块', 'Tarjan']
---
# 【模板】边双连通分量
## 题目描述

对于一个 $n$ 个节点 $m$ 条无向边的图，请输出其边双连通分量的个数，并且输出每个边双连通分量。
## 输入格式

第一行，两个整数 $n$ 和 $m$。

接下来 $m$ 行，每行两个整数 $u, v$，表示一条无向边。

**不保证图为简单图，图中可能有重边和自环。**
## 输出格式

第一行一个整数 $x$ 表示边双连通分量的个数。

接下来的 $x$ 行，每行第一个数 $a$ 表示该分量结点个数，然后 $a$ 个数，描述一个边双连通分量。

你可以以任意顺序输出边双连通分量与边双连通分量内的结点。
## 样例

### 样例输入 #1
```
5 8
1 3
2 4
4 3
1 2
4 5
5 1
2 4
1 1
```
### 样例输出 #1
```
1
5 1 5 4 2 3
```
### 样例输入 #2
```
5 3
1 2
2 3
1 3
```
### 样例输出 #2
```
3
3 1 3 2
1 4
1 5
```
### 样例输入 #3
```
6 5
1 3
2 4
1 2
4 6
2 3
```
### 样例输出 #3
```
4
3 1 2 3
1 4
1 5
1 6
```
### 样例输入 #4
```
7 8
1 3
2 4
3 5
2 5
6 4
2 5
6 3
2 7
```
### 样例输出 #4
```
3
1 1
5 2 5 3 6 4
1 7
```
## 提示

**样例四解释：**

![](https://cdn.luogu.com.cn/upload/image_hosting/0bzdfzeq.png)

相同颜色的点为同一个连通分量。


------------

**数据范围：**
对于 $100\%$ 的数据，$1 \le n \le 5 \times10 ^5$，$1 \le m \le 2 \times 10^6$。

| subtask | $n$ | $m$ | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $1 \le n \le 100$ | $1 \le m \le 500$ | $25$ |
| $2$ | $1 \le n \le 5000$ | $1 \le m \le 5 \times 10^4$ | $25$ |
| $3$ | $1 \le n \le 2\times 10^5$ | $1 \le m \le 5\times 10^5$ | $25$ |
| $4$ | $1 \le n \le 5 \times10 ^5$ | $1 \le m \le 2 \times 10^6$ | $25$ |

### 数据更新
- $2022/7/14$ 加强数据
- $2022/11/26$  新增 $10$ 组较小的数据（$1\le n, m \le 10$)，方便选手调试。
- $2022/12/31$ 重组 $subtask$，并加入若干组极端数据。
- $2023/1/1$ 发现昨天新加入的数据数据出了问题，已修改。
------------

本题不卡常，时间限制与空间限制均已开大，正确的解法均可通过。


------------

惊喜：AC 后记得把鼠标放到测试点上看反馈信息，有惊喜哦。


---

