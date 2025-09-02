---
title: "The Last Non-zero Digit."
layout: "post"
diff: 提高+/省选-
pid: UVA10212
tag: ['枚举', '概率论', '构造']
---

# The Last Non-zero Digit.

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=14&page=show_problem&problem=1153

[PDF](https://uva.onlinejudge.org/external/102/p10212.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10212/4e8f810bc4e7a305f60b05b1e511704f8aa33548.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10212/0894c564af5b074b1fa71eba4f22eddd87c8094a.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10212/f87ef3743b89683c4cc1e3cc87091658d956339f.png)

## 样例 #1

### 输入

```
10 10
10 5
25 6
```

### 输出

```
8
4
2
```



---

---
title: "古代象形符号 Ancient Messages"
layout: "post"
diff: 提高+/省选-
pid: UVA1103
tag: ['连通块', '进制', '构造']
---

# 古代象形符号 Ancient Messages

## 题目描述

为了理解早期文明，考古学家经常研究用古代语言编写的文本。在3000多年前的埃及使用的一种语言是基于称为象形文字的字符。如图显示了六个象形文字及其名称，在这个题目中，您需要编写一个程序来识别这六个字。

![]("C:\Users\白文礼\Desktop\4_1.png")

输入INPUT：
```

## 输入格式

输入由几个测试用例组成，每个测试用例描述一个包含一个或多个的图像。 象形文字选自图所示的那些。图像以一系列水平扫描线的形式给出，这些水平扫描线由黑色像素（由1表示）和白色像素（由0表示）组成。在输入数据中，每个扫描线以十六进制表示法编码。 例如，序列将表示八个像素10011100（一个黑色像素，后面是两个白色像素，依此类推） 十六进制表示法为9c。 在十六进制中仅使用数字和小写字母a到f编码。每个测试用例的第一行包含两个整数，H和W。H（0＜H≤200）是 图像中的扫描行数。 W（0＜W≤50）是每行中十六进制字符的数量 。 接下来的H行包含图像的十六进制字符，从上到下。
输入图像符合以下规则：
图像仅包含图1中所示的象形文字。
每个图像至少包含一个有效的象形文字。
图像中的每个黑色像素都是有效象形文字的一部分。
每个象形文字由一组连邻的黑色像素组成，即每个黑色像素至少和一个位于其顶部，底部，左侧或右侧的其他黑色像素相临。
象形文字间不相连，一个象形文字中不包含其他象形文字。
对角线顶点接触的两个黑色像素必然具有共同的相邻的黑色像素。
象形文字可能会扭曲，但其在拓扑结构上一定等同于图1中的一个符号。 （两个图形的拓扑结构等同是说一个图形通过扭曲拖拽可以成为另一个图形，但是不能撕裂。） 
在输入所有测试用例之后换行并输入两个零，表示结束。

输入样例
100 25 
0000000000000000000000000 
0000000000000000000000000 
...(50 lines omitted)... 
00001fe0000000000007c0000 
00003fe0000000000007c0000 
...(44 lines omitted)... 
0000000000000000000000000 
0000000000000000000000000
150 38 
00000000000000000000000000000000000000
00000000000000000000000000000000000000 
...(75 lines omitted)... 
0000000003fffffffffffffffff00000000000 
0000000003fffffffffffffffff00000000000 
...(69 lines omitted)... 
00000000000000000000000000000000000000
00000000000000000000000000000000000000 
0 0
```

输出OUTPUT：

```

## 输出格式

对于每个测试用例，输出其测试用例编号，后跟一个字符串，字符串包含的每一个字符都代表一个图像中的象形文字，具体对应关系如下：
Ankh：A
Wedjat：J
Djed：D 
Scarab：S
Was：W
Akhet：K

输出样例
Case 1: AKW
Case 2: AAAAA
```



---

---
title: "生成排列 Generating Permutations"
layout: "post"
diff: 提高+/省选-
pid: UVA11925
tag: ['字符串', '构造']
---

# 生成排列 Generating Permutations

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=229&page=show_problem&problem=3076

[PDF](https://uva.onlinejudge.org/external/119/p11925.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11925/4ae01d3bad0e00d10dd54ea1a36732d8994153c9.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11925/39a915f8fa7c330f6d88d2084592f1cdbcc50f29.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11925/b09493d267f3d2d325027cbace89abb524055c4a.png)

## 样例 #1

### 输入

```
3 2 1 3
3 2 3 1
4 4 2 3 1
0
```

### 输出

```
1
2
12122
```



---

---
title: "Fast Matrix Operations"
layout: "post"
diff: 提高+/省选-
pid: UVA11992
tag: ['线段树', '构造']
---

# Fast Matrix Operations

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=229&page=show_problem&problem=3143

[PDF](https://uva.onlinejudge.org/external/119/p11992.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11992/9b4b07db5bbb2af0ec8d2e58971ff9ef667aba18.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11992/c66d9d68dcf16d53358935e75ad9c88d099a7046.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11992/97cd09c03cc7c50c54aa53c6a7fd6478eaa7a1cf.png)

## 样例 #1

### 输入

```
4 4 8
1 1 2 4 4 5
3 2 1 4 4
1 1 1 3 4 2
3 1 2 4 4
3 1 1 3 4
2 2 1 4 4 2
3 1 2 4 4
1 1 1 4 3 3
```

### 输出

```
45 0 5
78 5 7
69 2 7
39 2 7
```



---

---
title: "旋转游戏 The Rotation Game"
layout: "post"
diff: 提高+/省选-
pid: UVA1343
tag: ['剪枝', '启发式迭代加深搜索 IDA*', '构造']
---

# 旋转游戏 The Rotation Game

## 题目描述

　　如图 $1$ 所示，有一个 “#” 形的棋盘，上面有 $1,2,3$ 三种数字各 $8$ 个。给定 $8$ 种操作，分别为图中的 $\text{A}\sim \text{H}$。这些操作会按照图中字母与箭头所指明的方向，把一条长度为 $8$ 的序列循环移动 $1$ 个单位。例如下图最左边的 “#” 形棋盘执行操作 $\text{A}$ 时，会变为图中间的 “#” 形棋盘，再执行操作 $\text{C}$ 后会变为图中最右边的 “#” 形棋盘。
![](https://cdn.luogu.org/upload/pic/40731.png)
$$\text{图 1}$$
　　现给定一个初始状态，请使用最少的操作次数，使 “#” 形棋盘最中间的 $8$ 个格子里的数字相同。

## 输入格式

　　输入包括不超过 $30$ 组测试数据。每个测试数据只包括一行，包含 $24$ 个整数，每相邻两个整数之间用 $1$ 个空格隔开，表示这个 “#” 形棋盘的初始状态。（这些整数的排列顺序是从上至下，同一行的从左至右。例如 $\text{1 1 1 1 3 2 3 2 3 1 3 2 2 3 1 2 2 2 3 1 2 1 3 3}$ 表示图 $1$ 最左边的状态。）每两组测试数据之间没有换行符。输入文件以一行 $0$ 结束。

## 输出格式

　　对于每组测试数据，输出两行。第一行用字符 $\text{A}\sim \text{H}$ 输出操作的方法，**每两个操作字符之间没有空格分开**，如果不需要任何步数，输出 `No moves needed`。第二行输出最终状态中最中间的 $8$ 个格子里的数字。如果有多组解，输出操作次数最少的一组解；如果仍有多组解，输出字典序最小的一组。任意相邻两组测试数据的输出之间不需输出换行符。



---

