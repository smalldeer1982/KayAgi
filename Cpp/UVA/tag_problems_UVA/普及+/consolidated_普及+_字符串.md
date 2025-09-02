---
title: "Power Strings"
layout: "post"
diff: 普及+/提高
pid: UVA10298
tag: ['字符串', '枚举', 'KMP 算法']
---

# Power Strings

## 题目描述

### 题意简述：

求一个字符串最多由多少个重复的子串连接而成。

例如 `ababab` 由三个 `ab` 连接而成，`abcd` 由一个 `abcd` 连接而成。

## 输入格式

**本题多组数据**。

每一组数据仅有一行，这一行仅有一个字符串 $s$。

输入的结束标志为一个 `.`。

## 输出格式

对于每一组数据，输出这组字符串最多由多少个重复的子串连接而成。

## 说明/提示

$1\le |s|\le 10^6$。

## 样例 #1

### 输入

```
abcd
aaaa
ababab
.
```

### 输出

```
1
4
3
```



---

---
title: "划分成回文串 Partitioning by Palindromes"
layout: "post"
diff: 普及+/提高
pid: UVA11584
tag: ['字符串', '动态规划 DP', '搜索']
---

# 划分成回文串 Partitioning by Palindromes

## 题目描述

回文子串(palind)

**问题描述：**

当一个字符串正序和反序是完全相同时，我们称之为“回文串”。例如“racecar”就是一个回文串，而“fastcar”就不是。现在给一个字符串s，把它分割成若干个互不相交的回文子串，求分割的回文子串的最少个数。

## 输入格式

第一行为正整数t(≤10)，表示数据组数；接下来t行，每行一个完全由小写字母组成的字符串，长度不超过1000。

## 输出格式

对于每组数据，输出最少回文子串数。

由 @C919 提供翻译

## 样例 #1

### 输入

```
3
racecar
fastcar
aaadbccb
```

### 输出

```
1
7
3
```



---

---
title: ""strcmp()" Anyone?"
layout: "post"
diff: 普及+/提高
pid: UVA11732
tag: ['字符串', '概率论', '字典树 Trie']
---

# "strcmp()" Anyone?

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=117&page=show_problem&problem=2832

[PDF](https://uva.onlinejudge.org/external/117/p11732.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11732/f9f4156b815a0febb856755194643aee4268928f.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11732/eb2d36585a3a7d37aed581131a6ea2ce899370cb.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11732/8c26b864fca1312c55a0ae313d6d122bb1a75557.png)

## 样例 #1

### 输入

```
2
a
b
4
cat
hat
mat
sir
0
```

### 输出

```
Case 1: 1
Case 2: 6
```



---

---
title: "Period"
layout: "post"
diff: 普及+/提高
pid: UVA1328
tag: ['字符串', 'KMP 算法']
---

# Period

## 题目描述

对于给定字符串 $S$ 的每个前缀，我们想知道它是否为周期串（周期串定义为由若干最小循环节拼接而成的字符串），若是，输出前缀长度和循环节数量。

## 输入格式

多组数据，每组数据第一行一个整数 $n$，表示字符串 $s$ 的长度，若 $n=0$ 则结束输入。

若 $n\ne0$，则第二行一个字符串 $S$，如题意。

## 输出格式

对于第 $i$ 组输出，第一行一个字符串 `Test case #i`。

之后若干行一行两个整数，表示如果字符串 $S$ 的一个前缀是周期串，它的长度和循环节数量（注意这里的循环节是指**长度最小的**循环节）。

之后再空一行。

## 说明/提示

$n\leq10^6$，字符串 $S$ 均由小写字母构成。

## 样例 #1

### 输入

```
3
aaa
12
aabaabaabaab
0

```

### 输出

```
Test case #1
2 2
3 3

Test case #2
2 2
6 2
9 3
12 4

```



---

---
title: "Keyboarding"
layout: "post"
diff: 普及+/提高
pid: UVA1714
tag: ['字符串', '枚举', '广度优先搜索 BFS']
---

# Keyboarding

## 题目描述

## 题目背景

输入一条信息需要敲几下键？或许你会认为它相当于文本中的字符数，但只有在按键与字符一一对应时方才如此。对于小型设备来说，输入文本通常很麻烦。有些设备只提供几个按钮，比字符数量少得多。对于这样的设备，键入一个字符就需要一系列操作。

现在就有一套这样的输入机制：屏幕虚拟键盘，上面有一个光标，可以在键与键来回移动来选择字符。四个箭头按钮控制光标的移动，当光标的位置在合适的虚拟键上时，按确认按钮即可输入相应的字符，且在文本的末尾必须回车。


现在给你一段字符串，并且你只有「上、下、左、右，确认」这五个按钮。本题中，你会得到一个虚拟键盘布局。你的任务是确定键入给定文本所需的最少操作数，按下一个按钮即视为一次操作。虚拟键分布在一个矩形网格中，这样每个虚拟键占用网格中一个或多个相连的单元方格。光标初始均在左上角并可四向移动，且每次都沿该方向移到下一个不同字符的虚拟键。光标不能移动到无效的格上。

每个虚拟键与字符唯一对应，其由一个或多个方格组成，这些方格相连为一块区域。

## 输入格式

**本题有多组数据**。

对于每组数据：

第一行三个整数 $n,m,k$，分别为虚拟键盘网格的行数和列数。

接下来 $r$ 行，每行 $c$ 个字符，为大写字母、数字、横杠或星号（表示回车键）其中之一。

最后一行为一个非空字符串，是要输入的文本，最多有10000个除星号外的有效字符。

## 输出格式

对于每组数据，输出键入整个文本所需的最少操作数，**包括最后按下的回车**。

## 样例

### 样例输入

```text
4 7
ABCDEFG
HIJKLMN
OPQRSTU
VWXYZ**
CONTEST
5 20
12233445566778899000
QQWWEERRTTYYUUIIOOPP
-AASSDDFFGGHHJJKKLL*
--ZZXXCCVVBBNNMM--**
--------------------
ACM-ICPC-WORLD-FINALS-2015
2 19
ABCDEFGHIJKLMNOPQZY
X*****************Y
AZAZ
6 4
AXYB
BBBB
KLMB
OPQB
DEFB
GHI*
AB
```

### 样例输出

```text
30
160
19
7
```

## 说明/提示

![](https://cdn.luogu.com.cn/upload/image_hosting/uvrfluzd.png)

插图描述了一种经过30次操作后输入 `CONTEST` 的方式，红点表示按下该虚拟键。

#### 数据规模

- $1\le r,c\le50,|S|\le 100001\le r,c\le 50,|S|\le 10000$。
---
翻译: @QQzhi (UID:525682)



---

---
title: "MPI Maelstrom"
layout: "post"
diff: 普及+/提高
pid: UVA423
tag: ['字符串']
---

# MPI Maelstrom

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=6&page=show_problem&problem=364

[PDF](https://uva.onlinejudge.org/external/4/p423.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA423/620b48e988d4826466e382f01c3dcee7d7e821bf.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA423/3df347ad588012e63a8fca84f52ca55091b02457.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA423/03cc7c4b3dd0f07be6457141bd0530655ffc8c03.png)

## 样例 #1

### 输入

```
5
50
30 5
100 20 50
10 x x 10
```

### 输出

```
35
```



---

---
title: "Immediate Decodability"
layout: "post"
diff: 普及+/提高
pid: UVA644
tag: ['字符串', '字典树 Trie']
---

# Immediate Decodability

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=8&page=show_problem&problem=585

[PDF](https://uva.onlinejudge.org/external/6/p644.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA644/ef8ec58ea23c0b0f28ccca6a9cb8b526b259834f.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA644/0ee74805dbc651412fb0404c157882e6ec4e2061.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA644/7baa231aedb25634c7086f9142d101700faddf53.png)

## 样例 #1

### 输入

```
01
10
0010
0000
9
01
10
010
0000
9
```

### 输出

```
Set 1 is immediately decodable
Set 2 is not immediately decodable
```



---

---
title: "Permutations"
layout: "post"
diff: 普及+/提高
pid: UVA941
tag: ['字符串', '康托展开']
---

# Permutations

## 题目描述

## 题目大意：

输入一个不超过20个字符并且全由小写字母构成的字符串以及一个数N，输出原字符串重新排列顺序得到的所有字符串中字典序从小到大第N+1个的字符串。

## 输入格式

第一行：
一个数T，表示有T组数据。
此后每组数据两行，
第一行表示原字符串，
第二行表示N。

## 输出格式

对于每组数据，输出一行，表示第N+1小的字符串。


感谢 @JXPGSWT_54088  提供的翻译。

## 样例 #1

### 输入

```
2
abc
3
abcde
119
```

### 输出

```
bca
edcba
```



---

