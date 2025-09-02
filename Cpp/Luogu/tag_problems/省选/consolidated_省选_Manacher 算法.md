---
title: "[SHOI2011] 双倍回文"
layout: "post"
diff: 省选/NOI-
pid: P4287
tag: ['字符串', '2011', '各省省选', '上海', '回文自动机 PAM', 'Manacher 算法']
---
# [SHOI2011] 双倍回文
## 题目描述

记字符串 $w$ 的倒置为 $w^{\mathsf R}$。例如$\tt (abcd)^{\mathsf R}=dcba$，$\tt (abba)^{\mathsf R}=abba$。

对字符串 $x$，如果 $x$ 满足 $x^{\mathsf R}=x$，则称之为回文。例如 $\tt abba$ 是一个回文，而 $\tt abed$ 不是。

如果 $x$ 能够写成 $ww^{\mathsf R} ww^{\mathsf R}$ 形式，则称它是一个“双倍回文”。换句话说，若要 $x$ 是双倍回文，它的长度必须是 $4$ 的倍数，而且 $x$，$x$ 的前半部分，$x$ 的后半部分都要是回文。例如 $\tt abbaabba$ 是一个双倍回文，而 $\tt abaaba$ 不是，因为它的长度不是 $4$ 的倍数。

- $x$ 的子串是指在 $x$ 中连续的一段字符所组成的字符串。例如 $\tt be$ 是 $\tt abed$ 的子串，而 $\tt ac$ 不是。
- $x$ 的回文子串，就是指满足回文性质的 $x$ 的子串。
- $x$ 的双倍回文子串，就是指满足双倍回文性质的 $x$ 的子串。

你的任务是，对于给定的字符串，计算它的最长双倍回文子串的长度。
## 输入格式

输入分为两行。

第一行为一个整数，表示字符串的长度。  
第二行有个连续的小写的英文字符，表示字符串的内容。
## 输出格式

输出文件只有一行即输入数据中字符串的最长双倍回文子串的长度，如果双倍回文子串不存在，则输出 $0$。
## 样例

### 样例输入 #1
```
16
ggabaabaabaaball
```
### 样例输出 #1
```
12
```
## 提示

### 数据范围及约定

对于全部数据，$1\le N \le 500000$。


---

---
title: "[蓝桥杯 2015 国 AC] 切开字符串"
layout: "post"
diff: 省选/NOI-
pid: P8631
tag: ['2015', '枚举', '前缀和', 'Manacher 算法', '蓝桥杯国赛']
---
# [蓝桥杯 2015 国 AC] 切开字符串
## 题目描述

Pear 有一个字符串，不过他希望把它切成两段。

这是一个长度为 $N$（$ \le 10^5$）的字符串。

Pear 希望选择一个位置，把字符串不重复不遗漏地切成两段，长度分别是 $t$ 和 $N-t$（这两段都必须非空）。

Pear 用如下方式评估切割的方案：

定义“正回文子串”为：长度为奇数的回文子串。

设切成的两段字符串中，前一段中有 $A$ 个不相同的正回文子串，后一段中有 $B$ 个不相同的非正回文子串，则该方案的得分为 $A \times B$。

注意，后一段中的 $B$ 表示的是：“ ... 非正回文 ... ”，而不是：“ ... 正回文 ... ”。

那么所有的切割方案中，$A \times B$ 的最大值是多少呢？
## 输入格式

输入第一行一个正整数 $N$（$ \le 10^5$）

接下来一行一个字符串，长度为 $N$。该字符串仅包含小写英文字母。
## 输出格式

一行一个正整数，表示所求的 $A \times B$ 的最大值。
## 样例

### 样例输入 #1
```
10
bbaaabcaba
```
### 样例输出 #1
```
38
```
## 提示

对于 $20\%$ 的数据，$N \le 100$。

对于 $40\%$ 的数据，$N \le 1000$。

对于 $100\%$ 的数据，$N \le 10^5$。

时限 1 秒, 512M。蓝桥杯 2015 年第六届国赛


---

---
title: "[SNCPC2019] Paper-cutting"
layout: "post"
diff: 省选/NOI-
pid: P9646
tag: ['2019', 'O2优化', '陕西', 'Manacher 算法', 'XCPC']
---
# [SNCPC2019] Paper-cutting
## 题目描述

Paper-cutting is one of the oldest and most popular folk arts in China. It can be geographically divided into a southern and a northern style. The southern style, represented by works from Yangzhou in Jiangsu Province and Yueqing in Zhejiang Province, features ingenious and beautiful designs, exquisite carving and interesting shapes. The northern style, mainly from Yuxian and Fengning in Hebei Province and best represented by works from northern Shaanxi, features exaggerated shapes, vigorousness, vivid depictions, and diverse patterns.

There are basic cut-outs, consisting of a single image, and symmetrical designs, that are usually created by some folding over a proportioned crease, and then cutting a shape, so that when unfolded, it forms a symmetrical design. Chinese paper cuttings are usually symmetrical. The paper cutouts are usually in an even number series of $2$, $4$, $24$, etc.

You are given a piece of paper in the shape of a matrix of size $n \times m$. It is partitioned into $n \times m$ blocks of size $1 \times 1$. The piece of paper can be folded in the following way:

- You choose a vertical line between two of its columns or a horizontal line between two of its rows. This line splits the paper into two sides. 
- You use the line as the folding axis and fold the smaller side of the paper onto the larger one going over the axis. If both sides of the paper are of equal size, you may fold from either side.

You would like to make a paper-cutting masterpiece from this paper. At first, you fold the paper using the method above several times (including zero times). Then you use scissors to cut the paper. Each time you cut, you can cut out a connected component from the folded paper (even if the component is not reachable from outside) and throw it away. Note that two $1 \times 1$ blocks are connected if they share an edge.

Given the final look of the paper, which is a matrix of size $n \times m$ containing $0$s and $1$s, you would like to know the minimum number of cuts needed when using the scissors. 

## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$, indicating the number of test cases. For each test case:

The first line contains two integers $n$ and $m$ ($1 \le n \times m \le 10^6$): the size of the paper.

Each of the next $n$ lines contains a binary string of length $m$, where $\texttt{0}$ means the $1 \times 1$ block is cut out and $\texttt{1}$ means the $1 \times 1$ block remains on the final paper-cutting.

It is guaranteed that the sum of $n \times m$ over all test cases does not exceed $10^6$.
## 输出格式

For each test case output one line containing one integer, indicating the minimum number of cuts needed.
## 样例

### 样例输入 #1
```
3
2 5
11001
11001
5 7
1001100
0110011
0101101
0010010
1000000
3 2
11
11
11
```
### 样例输出 #1
```
1
4
0
```
## 提示

For the first sample test case, you can fold in the following way and cut the only $0$ out:
$$\begin{array}{ccc|cc} 1&1&0&0&1\\1&1&0&0&1\end{array} \to \begin{array}{ccc} 1&1&0\\ \hline 1&1&0\end{array} \to \begin{array}{ccc} 1&1&0\end{array}$$

For the second sample test case, you can fold in the following way and cut the $4$ connected components of $0$s out:
$$\begin{array}{cccc|ccc} 1&0&0&1&1&0&0\\0&1&1&0&0&1&1\\0&1&0&1&1&0&1\\0&0&1&0&0&1&0\\1&0&0&0&0&0&0\end{array} \to \begin{array}{cccc} 1&0&0&1\\0&1&1&0\\0&1&0&1\\0&0&1&0\\1&0&0&0\end{array}$$
## 题目翻译

剪纸是中国最古老、最受欢迎的民间艺术之一。它在地理上可以分为南方风格和北方风格。以江苏扬州、浙江乐清作品为代表的南方风格，设计巧妙美观，雕刻精美，造型有趣。北方风格以河北蔚县、丰宁为主体，以陕北作品为代表，造型夸张、气势恢宏、刻画生动、图案多样。

基本的裁剪由单个图像组成，还有对称的设计，通常是通过在成比例的折痕上折叠，然后裁成一个形状，当展开时，就形成了对称的设计。中国剪纸通常是对称的。剪纸通常是 $2$、 $4$ 、 $24$ 等偶数系列。

你会得到一张大小为 $n \times m$ 的纸， 它被划分为 $n \times m$ 个大小为 $1 \times 1$ 的块在。这张纸可以按以下方式折叠：

- 可以在两列之间选择一条垂直线，也可以在两行之间选择一条水平线。这条线把纸分成两面。

- 你用这条线作为对称轴，把小的一面折到大的一面上。如果纸的两面大小相等，从两边对折。

你想用这张纸做一幅剪纸杰作。首先，使用上述方法将纸张折叠几次（包括零次）。然后你用剪刀剪纸。每次剪切时，都可以从折叠的纸上剪切出一个连接的部分（即使从外面无法接触到该部分并将其扔掉。请注意，如果两个 $ 1\times 1$ 的块共享一条边，则它们是连接的。

纸张的最终外观是一个包含 $0$ 和 $1$ 的大小为 $n \times m$ 的矩阵，你想知道需要使用剪刀时的最小裁剪次数。

## 输入格式

有多个测试数据。输入的第一行包含一个整数 $T$ ，表示测试数据的数量。对于每个测试数据：

第一行包含两个整数 $n$ 和 $m$ ( $1 \le n \times m \le 10^6$ )表示纸张的大小。

接下来的 $n$ 行中的每一行都包含一个长度为 $m$ 的01字符串，其中 $\texttt{0}$ 表示 $1\times 1$ 块被剪切掉， $\texttt{1}$ 意味着 $1 \times 1$ 块保留在最后的剪纸上。

保证所有测试数据的 $n \times m$ 之和不超过 $10^6$ 。

## 输出格式

对于每个测试数据输出一行，其中包含一个整数，表示所需的最小裁剪次数。

## 样例 #1

### 样例输入 #1

```
3
2 5
11001
11001
5 7
1001100
0110011
0101101
0010010
1000000
3 2
11
11
11
```

### 样例输出 #1

```
1
4
0
```

## 提示

对于样例一,你可以通过这种方式将唯一的 $0$ 剪出:
$$\begin{array}{ccc|cc} 1&1&0&0&1\\1&1&0&0&1\end{array} \to \begin{array}{ccc} 1&1&0\\ \hline 1&1&0\end{array} \to \begin{array}{ccc} 1&1&0\end{array}$$

对于样例二，你可以按照以下方式折叠并裁剪出 $0$ 的 $4$ 个连通块：
$$\begin{array}{cccc|ccc} 1&0&0&1&1&0&0\\0&1&1&0&0&1&1\\0&1&0&1&1&0&1\\0&0&1&0&0&1&0\\1&0&0&0&0&0&0\end{array} \to \begin{array}{cccc} 1&0&0&1\\0&1&1&0\\0&1&0&1\\0&0&1&0\\1&0&0&0\end{array}$$


---

