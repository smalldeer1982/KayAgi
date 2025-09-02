---
title: "[语言月赛202211] String Problem"
layout: "post"
diff: 普及/提高-
pid: B3683
tag: ['字符串', '2022', 'O2优化', '语言月赛']
---
# [语言月赛202211] String Problem
## 题目背景

扶苏很喜欢研究制糊串问题。
## 题目描述

扶苏给你了两个长度为 $n$ 的字符串 $s$ 和 $t$，请你判定这两个字符串是否相同。

扶苏觉得这个问题太简单了，所以她还给出了 $q$ 次操作，每次操作是修改其中一个字符串的某个位置的字符。每次操作过后，都请你回答一次 $s$ 和 $t$ 是否相同。

字符串下标从 1 开始编号。例如，若字符串 $s$ 为 $\texttt {abc}$，要将它的第二个位置修改为 $d$，则修改后的字符串为 $\texttt{adc}$。
## 输入格式

**本题单测试点内有多组测试数据**。

输入的第一行是一个整数 $T$，表示数据组数。接下来按顺序给出每组数据的输入：

对每组数据，第一行是两个整数，依次表示字符串长度 $n$ 和操作的次数 $q$。  
第二行是一个长度为 $n$ 的字符串，表示 $s$。  
第三行是一个长度为 $n$ 的字符串，表示 $t$。  
接下来 $q$ 行，每行两个整数 $o, p$ 和一个字符 $c$，其中 $o$ 是 $0$ 或 $1$。
- 若 $o = 0$，则表示将字符串 $s$ 的第 $p$ 个字符修改成 $c$。
- 若 $o = 1$，则表示将字符串 $t$ 的第 $p$ 个字符修改成 $c$。
## 输出格式

对每组数据，依次输出答案。

每组数据共需要输出 $q + 1$ 行。  
首先对初始给定的字符串 $s$ 和 $t$，若他们相同，则输出一行 `Yes`，否则输出一行 `No`。  
接下来，对每次操作，若操作后两字符串相同，输出一行 `Yes`，否则输出一行 `No`。
## 样例

### 样例输入 #1
```
2
3 2
abc
abc
1 2 d
0 2 d
5 0
abdce
acdce

```
### 样例输出 #1
```
Yes
No
Yes
No
```
## 提示

### 样例 1 解释

对第一组数据：  
- 输入的字符串 $s = t$，故第一行输出为 `Yes`。  
- 第一次操作，将 $t$ 的第 2 位改为 $\texttt d$，此时 $s = \texttt{abc}$，$t = \texttt{adc}$，$s \neq t$，故第二行输出为 `No`。
- 第二次操作，将 $s$ 的第 2 位改为 $\texttt d$，此时 $s = \texttt{adc}$，$t = \texttt{adc}$，$s = t$，故第三行输出为 `Yes`。

对第二组数据：  
- 输入的字符串 $s \neq t$，故第四行输出为 `No`。

### 数据规模与约定

本题共 10 个测试点，各测试点的规模见下表

| 测试点编号 | $n = $ | $q =$ |
| :-: | :-: | :-:|
| 1 | $1$ | $0$ |
| 2 | $1000$ | $0$ |
| 3 | $1000$ | $0$ |
| 4 | $1000$ | $1000$|
| 5 | $1000$ | $1000$ |
| 6 | $1000$ | $1000$ |
| 7 | $10^6$ | $10^6$ |
| 8 | $10^6$ | $10^6$ |
| 9 | $10^6$ | $10^6$ |
| 10 | $10^6$ | $10^6$ |

对全部的测试点，保证 $T = 5$，$s,t$ 均只含小写英文字母，输入的换行符不含 `\r`，$o \in \{0, 1\}$，$1 \leq p \leq n$，$c$ 为小写英文字母。

### 提示

请注意大量的数据读入输出对程序效率造成的影响。

By 一扶苏一


---

---
title: "[厦门小学生 C++ 2024] 有趣子序列"
layout: "post"
diff: 普及/提高-
pid: B4181
tag: ['字符串', '2024', '福建', '科创活动', '小学活动']
---
# [厦门小学生 C++ 2024] 有趣子序列
## 题目背景

本试题为 2024 年厦门市小学生 C++ 语言**复赛**试题，数据为洛谷自造。

**初赛**为笔试。
## 题目描述

小唐最近在研究一个长为 $n$ 的 $01$ 字符串 $S$（下标从 $1$ 开始）。

他很喜欢其子区间和子序列，例如：如下表的 $01$ 字符串 $S = \tt{01011010}$。

| $S_1$ | $S_2$ | $S_3$ | $S_4$ | $S_5$ | $S_6$ | $S_7$ | $S_8$ |
|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|
| $0$   | $1$   | $0$   | $1$   | $1$   | $0$   | $1$   | $0$   |

- 子区间 $[2,4]$ 即为：$S_2, S_3, S_4$ 这样一个在原 $S$ 串中连续的一段序列；
- 子序列即类如：$S_2, S_4, S_6, S_7$ 这样一个按原 $S$ 串顺序的，可连续、可不连续的序列。

所以，子区间肯定是子序列，但子序列不一定是子区间。

小唐会询问你 $Q$ 次，每次询问给出一个 $S$ 的子区间 $[l,r]$，他想知道是否存在 $S$ 的一个“有趣子序列”，其满足：

1. “有趣子序列”和询问的子区间 $[l,r]$ 相同；   
例：如果询问的子区间是 $[2,4]$，其中，子序列 $S_2, S_6, S_7$ 和询问的子区间 $S_2, S_3, S_4$ 中的字符按顺序一一对应相同;

2. “有趣子序列”不是从 $S$ 中选出的一段子区间。    
例：子序列 $S_2, S_6, S_7$ 并不是原 $S$ 串中连续的一段序列，即不是原 $S$ 串的一段子区间。

请对于每次询问 $[l,r]$，输出 $\tt{Yes}$ 或 $\tt{No}$，分别表示存在或不存在这样的 “有趣子序列”。
## 输入格式

**本题有多组数据。**
- 第一行一个非负整数 $T$，表示数据组数。
- 接下来 $T$ 组数据，对于每组数据：
  - 第一行两个非负整数 $n$ 和 $q$，表示字符串长度和询问数。
  - 第二行一个 $01$ 字符串 $s$。
  - 接下来 $q$ 行，每行两个正整数 $l,r$，表示询问的子区间。
## 输出格式

对于每组数据：
- 对于每个询问，输出一行 $\tt{Yes}$ 或 $\tt{No}$ 表示答案。
## 样例

### 样例输入 #1
```
2
6 3
011100
2 4
1 3
3 5
5 2
11111
1 5
2 3
```
### 样例输出 #1
```
No
Yes
Yes
No
Yes
```
## 提示

### 样例解释 1

- 对于第一组数据，可以选择的子序列下标依次为：不存在，$(1,2,4)$，$(3,4,6)$。
- 对于第二组数据，可以选择的子序列下标依次为：不存在，$(1,3)$。

### 数据范围

对于所有数据，满足 $1 \leq n \leq 1 \times 10^5$，$1 \leq q \leq 1 \times 10^5$，$1 \leq l\ {\color{red}\leq}\ r \leq n$。

| 数据点编号 | $T\leq$ | $n\leq$ | $q\leq$ | 特殊性质 |
|:------------:|:----:|:----:|:----:|:----------:|
| $1$          | $100$ | $4$  | $1$  |          |
| $2$          | $100$ | $10$ | $10$ |          |
| $3$          | $10$ | $12$ | $100$ |          |
| $4$          | $10$ | $100$ | $100$ |          |
| $5, 6$       | $10$ | $1000$ | $1000$ |          |
| $7$          | $5$  | $1 \times 10^5$| $1 \times 10^5$| $l=1$       |
| $8, 9, 10$   | $5$  | $1 \times 10^5$| $1 \times 10^5$|          |

特殊性质：$l=1$ 表示子区间左边界为 $1$。


---

---
title: "[常州市赛 2021] 特殊字符"
layout: "post"
diff: 普及/提高-
pid: B4205
tag: ['数学', '2021', '江苏', '字符串（入门）', '科创活动', '小学活动']
---
# [常州市赛 2021] 特殊字符
## 题目背景

搬运自 <http://czoj.com.cn/p/441>。数据为民间数据。
## 题目描述

$\gdef\u{\underline}$
小 $\text{X}$ 接到了一个破译任务。他收到了一个仅包含小写英文字母字符串。  
这个字符串十分特殊：在 $26$ 个英文字母中，潜藏着一个特殊字符，这个字符的实际意义是一个字符串指令！  
$x$ 个特殊字符相连的含义是：把后面 $x$ 个字符组成的字符串**变成**它本身复制 $x$ 遍的结果。例如，若特殊字符是 $\tt w$，那么字符串 $\tt\red{ww}\u{abc}$ 的破译结果就是 $\tt\u{abab}c$。  
特殊的，若后面字符总数已经不足 $x$ 个，则字符串改为由后面所有字符组成。例如，若特殊字符是 $\texttt{w}$，那么字符串 $\tt\red{wwww}\u{abc}$ 的破译结果就是” $\tt\u{abcabcabcabc}$ ”。  
字符串**保证**连续 $x$ 个 $c$ 字符后的 $x$ 个字符都不会是 $c$ 字符。例如 $\tt aaaba$ 不会是你要破解的字符串（也就是特殊字符是不可能被复制的）。  
但是小 $\text{X}$ 还不知道特殊字符是什么。所以他想问问你，对于每一种可能的特殊字符，破译结果的第 $K$ 位是什么。
## 输入格式

第一行两个整数 $n,K$，分别表示字符串的长度和询问第 $K$ 位。   
第二行一个字符串。
## 输出格式

输出一行包含一个长度为 $26$ 字符串，分别表示若特殊字符是 $\texttt{a,b,c,d,\dots,y,z}$，那么破译结果的第 $K$ 位是什么。  
**若破译结果长度小于 $K$，输出`*`。**
## 样例

### 样例输入 #1
```
10 10
aaaabbbccd
```
### 样例输出 #1
```
bd**dddddddddddddddddddddd
```
## 提示

### 样例解释
若特殊字符是 $\texttt{a}$，破译结果是 $\texttt{bbbcbbbcb\red bbcbbbccd}$；  
若特殊字符是 $\texttt{b}$，破译结果是 $\texttt{aaaaccdcc\red dccd}$；  
若特殊字符是 $\texttt{c}$，破译结果是 $\texttt{aaaabbbdd}$；  
若特殊字符是 $\texttt{d}$，破译结果是 $\texttt{aaaabbbcc}$；  
若特殊字符是其他，破译结果是 $\texttt{aaaabbbcc\red d}$。
### 数据范围
本题共有 $10$ 个测试点。  
对于所有数据，满足 $1\le n\le10^6,1\le K\le 10^9$。  
|测试点编号|$n$|$K$|
|:-:|:-:|:-:|
|$1\sim4$|$\le500$|$\le500$|
|$5\sim7$|$\le10^6$|$\le10^6$|
|$8\sim10$|$\le10^6$|$\le10^9$|



---

---
title: "[常州市赛 2022] 文本找数"
layout: "post"
diff: 普及/提高-
pid: B4212
tag: ['模拟', '字符串', '2022', '江苏', '科创活动', '小学活动']
---
# [常州市赛 2022] 文本找数
## 题目背景

搬运自 <http://czoj.com.cn/p/460>。数据为民间数据。


## 题目描述

正当小 $\text{X}$ 带着大家玩三角形游戏的时候，小 $\text{Y}$ 在编程中遇到了一个难题，来请教小 $\text{X}$。

小 $\text{Y}$ 遇到的难题是需要在一行文本中找最大的数，这一行文本中有整数和实数，也有字母、空格等其它各种字符。这一行文本最多包括 $10000$ 个字符，其中每个数的长度不超过 $100$（包括小数点），所有的数都没有正负符号，并且没有前导 $0$，所谓前导 $0$ 是指一个数中开头可 以省略的 $0$，如 $007$ 中的两个 $0$ 就是前导 $0$，$0.618$ 中小数点前的 $0$ 不是前导 $0$。也就是说文本中出现的整数必定是一串连续的阿拉伯数字，除了 $0$ 以外所有整数的首位一定不是 $0$。文本中出现的实数必定是一串连续的阿拉伯数字并且中间夹杂着一个唯一的小数点，该小数点两侧必须是数字，并且小数点左侧一定是上文所述的整数。
## 输入格式

输入数据仅有一行包含一个字符串，表示要查找的文本。保证文本中小数点的前后位置一定都是数字，并且不存在一串连续的阿拉伯数字的前后各有一个小数点的情况，像 $\texttt{120.78.90.206}$ 这样的字符串是不可能出现在文本中的。
## 输出格式

一行一个整数或实数（按照文本中原来的样子原封不动输出）。如果最大的数不止一个，则输出长度最长的那个数。
## 样例

### 样例输入 #1
```
120 315 513 512 153 0
```
### 样例输出 #1
```
513
```
### 样例输入 #2
```
5r2.1q 4p 3.77442qw cock5.0$
```
### 样例输出 #2
```
5.0
```
## 提示

### 样例解释
对于样例 $1$，有 $120,315,513,512,153,0$ 六个数，最大的数为 $513$。

对于样例 $2$，有 $5,2.1,4,3.77442,5.0$ 五个数，最大的数有两个，$5.0$ 的长度更长。

### 数据规模与约定
对于 $10\%$ 的数据，文本为用空格隔开的若干个非负整数（范围在 int 以内），且最后一个数为 $0$，其余的数都不为 $0$； 

对于另外 $40\%$ 的数据，文本中不包含小数点；

对于 $100\%$ 的数据，文本长度 $≤10^4$，单个数的长度 $≤100$。


---

---
title: "[NOIP 1998 提高组] 拼数"
layout: "post"
diff: 普及/提高-
pid: P1012
tag: ['字符串', '1998', 'NOIP 提高组', '排序']
---
# [NOIP 1998 提高组] 拼数
## 题目描述

设有 $n$ 个正整数 $a_1 \dots a_n$，将它们联接成一排，相邻数字首尾相接，组成一个最大的整数。

## 输入格式

第一行有一个整数，表示数字个数 $n$。

第二行有 $n$ 个整数，表示给出的 $n$ 个整数 $a_i$。
## 输出格式

一个正整数，表示最大的整数

## 样例

### 样例输入 #1
```
3
13 312 343

```
### 样例输出 #1
```
34331213

```
### 样例输入 #2
```
4
7 13 4 246
```
### 样例输出 #2
```
7424613
```
## 提示

对于全部的测试点，保证 $1 \leq n \leq 20$，$1 \leq a_i \leq 10^9$。

NOIP1998 提高组 第二题


---

---
title: "[NOIP 2000 提高组] 单词接龙"
layout: "post"
diff: 普及/提高-
pid: P1019
tag: ['字符串', '搜索', '2000', 'NOIP 提高组']
---
# [NOIP 2000 提高组] 单词接龙
## 题目背景

注意：本题为上古 NOIP 原题，不保证存在靠谱的做法能通过该数据范围下的所有数据。

本题为搜索题，本题不接受 hack 数据。[关于此类题目的详细内容](https://www.luogu.com.cn/paste/isdgwj5l)

NOIP2000 提高组 T3
## 题目描述

单词接龙是一个与我们经常玩的成语接龙相类似的游戏，现在我们已知一组单词，且给定一个开头的字母，要求出以这个字母开头的最长的“龙”（每个单词都最多在“龙”中出现两次），在两个单词相连时，其重合部分合为一部分，例如 `beast` 和 `astonish`，如果接成一条龙则变为 `beastonish`，另外相邻的两部分不能存在包含关系，例如 `at` 和 `atide` 间不能相连。

## 输入格式

输入的第一行为一个单独的整数 $n$ 表示单词数，以下 $n$ 行每行有一个单词，输入的最后一行为一个单个字符，表示“龙”开头的字母。你可以假定以此字母开头的“龙”一定存在。

## 输出格式

只需输出以此字母开头的最长的“龙”的长度。

## 样例

### 样例输入 #1
```
5
at
touch
cheat
choose
tact
a

```
### 样例输出 #1
```
23

```
## 提示

样例解释：连成的“龙”为 `atoucheatactactouchoose`。

$n \le 20$。


---

---
title: "[NOIP 2000 普及组] 计算器的改良"
layout: "post"
diff: 普及/提高-
pid: P1022
tag: ['模拟', '字符串', '数学', '2000', 'NOIP 普及组']
---
# [NOIP 2000 普及组] 计算器的改良
## 题目背景

NCL 是一家专门从事计算器改良与升级的实验室，最近该实验室收到了某公司所委托的一个任务：需要在该公司某型号的计算器上加上解一元一次方程的功能。实验室将这个任务交给了一个刚进入的新手 ZL 先生。

## 题目描述

为了很好的完成这个任务，ZL 先生首先研究了一些一元一次方程的实例：

- $4+3x=8$。
- $6a-5+1=2-2a$。
- $-5+12y=0$。

ZL 先生被主管告之，在计算器上键入的一个一元一次方程中，只包含整数、小写字母及 `+`、`-`、`=` 这三个数学符号（当然，符号“`-`”既可作减号，也可作负号）。方程中并没有括号，也没有除号，方程中的字母表示未知数。

你可假设对键入的方程的正确性的判断是由另一个程序员在做，或者说可认为键入的一元一次方程均为合法的，且有唯一实数解。

## 输入格式

一个一元一次方程。

## 输出格式

解方程的结果（精确至小数点后三位）。

## 样例

### 样例输入 #1
```
6a-5+1=2-2a

```
### 样例输出 #1
```
a=0.750
```


---

---
title: "[NOIP 2001 提高组] 统计单词个数"
layout: "post"
diff: 普及/提高-
pid: P1026
tag: ['字符串', '动态规划 DP', '2001', 'NOIP 提高组', '枚举']
---
# [NOIP 2001 提高组] 统计单词个数
## 题目描述

给出一个长度不超过 $200$ 的由小写英文字母组成的字母串（该字串以每行 $20$ 个字母的方式输入，且保证每行一定为 $20$ 个）。要求将此字母串分成
 $k$ 份，且每份中包含的单词个数加起来总数最大。  

每份中包含的单词可以部分重叠。当选用一个单词之后，其第一个字母不能再用。例如字符串 `this` 中可包含 `this` 和 `is`，选用 `this` 之后就不能包含
 `th`。

单词在给出的一个不超过 $6$ 个单词的字典中。

要求输出最大的个数。

## 输入格式

每组的第一行有两个正整数 $p,k$。
$p$ 表示字串的行数，$k$ 表示分为 $k$ 个部分。

接下来的 $p$ 行，每行均有 $20$ 个字符。

再接下来有一个正整数 $s$，表示字典中单词个数。
接下来的 $s$ 行，每行均有一个单词。

## 输出格式

$1$个整数，分别对应每组测试数据的相应结果。

## 样例

### 样例输入 #1
```
1 3
thisisabookyouareaoh
4
is
a
ok
sab

```
### 样例输出 #1
```
7

```
## 提示

【数据范围】  
对于 $100\%$ 的数据，$2 \le k \le 40$，$1 \le s \le 6$。

【样例解释】
划分方案为 this / isabookyoua / reaoh

**【题目来源】**

NOIP 2001 提高组第三题


---

---
title: "[SHUPC 2024] 栅栏密码"
layout: "post"
diff: 普及/提高-
pid: P10312
tag: ['模拟', '字符串', '2024', '高校校赛']
---
# [SHUPC 2024] 栅栏密码
## 题目描述

栅栏密码（rail fence）是一种很基础的移位密码。

我们将明文 `Hello,World!` 按如下方式排列：

```
H...o...r
.e.l.,.o.l.!
..l...W...d
```

即把明文 `Hello,World!` 排列成若干个 `\/\/\/` 的形状，然后再逐行按从左到右的顺序取出字符，形成密文。例如第一行为 `Hor`，第二行为 `el,ol!`，第三行为 `lWd`，最终形成的密文为 `Horel,ol!lWd`。

若按上述方式排列的密文有 $h$ 行，则称该栅栏密码的高度为 $h$。

现在我们给出高度 $h$ 和一行密文字符串 $s$，请你输出一行明文字符串 $plain$。

## 输入格式

第一行读入一个数字 $h\ (2\le h \le10)$，表示密码的高度。

第二行读入一个字符串 $s\ (1\le |s| \le 10^5)$，表示密文。
## 输出格式

一个字符串 $plain$，表示明文。
## 样例

### 样例输入 #1
```
3
Horel,ol!lWd
```
### 样例输出 #1
```
Hello,World!
```
### 样例输入 #2
```
5
ccehgyaefnpeoobe{lcirg}epriec_ora_g
```
### 样例输出 #2
```
cyberpeace{railfence_cipher_gogogo}
```


---

---
title: "[NOIP 2008 普及组] 立体图"
layout: "post"
diff: 普及/提高-
pid: P1058
tag: ['模拟', '字符串', '2008', 'NOIP 普及组', '枚举']
---
# [NOIP 2008 普及组] 立体图
## 题目描述

小渊是个聪明的孩子，他经常会给周围的小朋友们讲些自己认为有趣的内容。最近，他准备给小朋友们讲解立体图，请你帮他画出立体图。

小渊有一块面积为 $m \times n$ 的矩形区域，上面有 $m \times n$ 个边长为 $1$ 的格子，每个格子上堆了一些同样大小的积木（积木的长宽高都是 $1$），小渊想请你打印出这些格子的立体图。我们定义每个积木为如下格式，并且不会做任何翻转旋转，只会严格以这一种形式摆放：

$$
\def\arraystretch{1e-10}
\begin{aligned}
&\verb!  +---+!\\
&\verb! /   /|!\\
&\verb!+---+ |!\quad\textsf{高}\\
&\verb!|   | +!\\
&\verb!|   |/ !\quad\textsf{宽}\\
&\verb!+---+  !\\
& \quad\textsf{长}
\end{aligned}$$


每个顶点用 $1$ 个加号 `+` 表示，长用 $3$ 个 `-` 表示，宽用 $1$ 个 `/`，高用两个 `|` 表示。字符 `+`，`-`，`/`，`|` 的 ASCII 码分别为 $43$，$45$，$47$，$124$。字符 `.`（ASCII 码 $46$）需要作为背景输出，即立体图里的空白部分需要用 `.` 来代替。立体图的画法如下面的规则：

若两块积木左右相邻，图示为：


$$
\def\arraystretch{1e-10}
\begin{aligned}
\verb!..+---+---+!\\
\verb!./   /   /|!\\
\verb!+---+---+ |!\\
\verb!|   |   | +!\\
\verb!|   |   |/.!\\
\verb!+---+---+..!\\
\end{aligned}
$$

若两块积木上下相邻，图示为：


$$
\def\arraystretch{1e-10}
\begin{aligned}
\verb!..+---+!\\
\verb!./   /|!\\
\verb!+---+ |!\\
\verb!|   | +!\\
\verb!|   |/|!\\
\verb!+---+ |!\\
\verb!|   | +!\\
\verb!|   |/.!\\
\verb!+---+..!\\
\end{aligned}
$$

若两块积木前后相邻，图示为：

$$
\def\arraystretch{1e-10}
\begin{aligned}
\verb!....+---+!\\
\verb!.../   /|!\\
\verb!..+---+ |!\\
\verb!./   /| +!\\
\verb!+---+ |/.!\\
\verb!|   | +..!\\
\verb!|   |/...!\\
\verb!+---+....!\\
\end{aligned}
$$

立体图中，定义位于第 $(m,1)$ 的格子（即第 $m$ 行第 $1$ 列的格子）上面自底向上的第一块积木（即最下面的一块积木）的左下角顶点为整张图最左下角的点。

## 输入格式

第一行有用空格隔开的$2$个整数 $m$ 和 $n$，表示有 $m \times n$ 个格子 $(1 \le m,n \le 50)$。

接下来的 $m$ 行，是一个 $m \times n$ 的矩阵，每行有 $n$ 个用空格隔开的整数，其中第 $i$ 行第 $j$ 列上的整数表示第 $i$ 行第 $j$ 列的格子上摞有多少个积木（$1 \le $ 每个格子上的积木数 $ \le 100$）。

## 输出格式

输出包含题目要求的立体图，是一个 $K$ 行 $L$ 列的字符串矩阵，其中 $K$ 和 $L$ 表示最少需要 $K$ 行 $L$ 列才能按规定输出立体图。


## 样例

### 样例输入 #1
```
3 4
2 2 1 2
2 2 1 1
3 2 1 2

```
### 样例输出 #1
```
......+---+---+...+---+
..+---+  /   /|../   /|
./   /|-+---+ |.+---+ |
+---+ |/   /| +-|   | +
|   | +---+ |/+---+ |/|
|   |/   /| +/   /|-+ |
+---+---+ |/+---+ |/| +
|   |   | +-|   | + |/.
|   |   |/  |   |/| +..
+---+---+---+---+ |/...
|   |   |   |   | +....
|   |   |   |   |/.....
+---+---+---+---+......
```
## 提示

NOIP2008普及组第四题



---

---
title: "删数问题"
layout: "post"
diff: 普及/提高-
pid: P1106
tag: ['字符串', '贪心']
---
# 删数问题
## 题目描述

键盘输入一个高精度的正整数 $n$（不超过 $250$ 位），去掉其中任意 $k$ 个数字后剩下的数字按原左右次序将组成一个新的非负整数。编程对给定的 $n$ 和 $k$，寻找一种方案使得剩下的数字组成的新数最小。
## 输入格式

输入两行正整数。

第一行输入一个高精度的正整数 $n$。

第二行输入一个正整数 $k$，表示需要删除的数字个数。
## 输出格式

输出一个整数，最后剩下的最小数。

## 样例

### 样例输入 #1
```
175438 
4

```
### 样例输出 #1
```
13
```
## 提示

用 $\operatorname{len}(n)$ 表示 $n$ 的**位数**，保证 $1 \leq k < \operatorname{len}(n) \leq 250$。


---

---
title: "「ALFR Round 3」C 割"
layout: "post"
diff: 普及/提高-
pid: P11447
tag: ['字符串', '贪心', '洛谷原创', 'O2优化', '鸽笼原理', '洛谷月赛']
---
# 「ALFR Round 3」C 割
## 题目背景

[English Statement](https://www.luogu.com.cn/problem/U517305).

**upd:** 添加的 hack 在 Sub 7。
## 题目描述

设 $f(S)$ 表示字符串 $S$ 字典序最大的子序列，给定 $k$，你需要将原字符串 $S$ 分割成 $k$ 段，设第 $i$ 段子串为 $a_i$，则该分割方案的权值为 $\max f(a_i)$，其中 $1\le i\le k$。由于分割方案有很多种，你需要求出所有分割方案中**字典序最小的权值**。

注：这里的权值实际上指的是字符串。

关于子序列的定义：某个序列的子序列是从最初序列通过去除某些元素但不破坏余下元素的相对位置（在前或在后）而形成的新序列。

关于字典序的定义：在字典序中，首先比较两个字符串的第一个字符，如果不同，则第一个字符较小的字符串更小；如果相同，则继续比较下一个字符，依此类推，直到比较完所有字符。如果一个字符串是另一个字符串的前缀，则较短的字符串更小。
## 输入格式

输入共两行。

第一行两个整数 $n,k$，$n$ 表示字符串 $S$ 的长度，$k$ 表示你需要将字符串分割为 $k$ 段。

第二行为一个字符串，即 $S$。
## 输出格式

输出一个字符串表示所有分割方案中字典序最小的权值。
## 样例

### 样例输入 #1
```
7 2
skyaqua
```
### 样例输出 #1
```
y
```
## 提示

### 样例解释
可以将字符串 $S$ 分割成 `sky`、`aqua` 这 $2$ 段，这 $2$ 段的 $f$ 分别为 `y`、`ua`，其中字典序最大的 $f$ 为 `y`，所以该分割方案的权值为 `y`。可以证明 `y` 是所有分割方案中字典序最小的权值。

### 数据范围

| 子任务 | 分值 | 限制 |
| :----------: | :----------: | :----------: |
| $1$ | $10$ | $n\le 10$ |
| $2$ | $20$ | $n\le 10^2$ |
| $3$ | $20$ | $n\le 3\times 10^2$| 
| $4$ | $10$ | 保证字符串 $S$ 中所有字符都相等 |
| $5$ | $10$ | $k=1$ |
| $6$ | $30$ | - |

对于 $100\%$ 的数据，$1\le k\le n\le 2\times10^5$，且字符串 $S$ 中的字符均为小写英文字母。


---

---
title: "[USACO24DEC] It's Mooin' Time B"
layout: "post"
diff: 普及/提高-
pid: P11451
tag: ['字符串', 'USACO', '2024']
---
# [USACO24DEC] It's Mooin' Time B
## 题目描述

Farmer John 正在试图向 Elsie 描述他最喜欢的 USACO 竞赛，但她很难理解为什么他这么喜欢它。他说「竞赛中我最喜欢的部分是 Bessie 说 『现在是哞哞时间』并在整个竞赛中一直哞哞叫」。

Elsie 仍然不理解，所以 Farmer John 将竞赛以文本文件形式下载，并试图解释他的意思。竞赛被定义为一个长度为 $N$（$3≤N≤20000$）的小写字母字符串。一种哞叫一般地定义为子串 $c_ic_jc_j$，其中某字符 $c_i$ 之后紧跟着 $2$ 个某字符 $c_j$，且 $c_i≠c_j$。根据 Farmer John 的说法，Bessie 哞叫了很多，所以如果某种哞叫在竞赛中出现了至少 $F$（$1≤F≤N$）次，那可能就是 Bessie 发出的。

然而，Farmer John 的下载可能损坏，文本文件可能存在至多一个字符与原始文件不同。将可能的误差考虑在内，输出所有可能是 Bessie 发出的哞叫，按字典序顺序排序。
## 输入格式

输入的第一行包含 $N$ 和 $F$，表示字符串的长度以及 Bessie 的哞叫的频次下限。

第二行包含一个长度为 $N$ 的小写字母字符串，表示竞赛。
## 输出格式

输出可能是 Bessie 发出的哞叫的数量，以下是按字典序排序的哞叫列表。每行输出一种哞叫。
## 样例

### 样例输入 #1
```
10 2
zzmoozzmoo
```
### 样例输出 #1
```
1
moo
```
### 样例输入 #2
```
17 2
momoobaaaaaqqqcqq
```
### 样例输出 #2
```
3
aqq
baa
cqq
```
### 样例输入 #3
```
3 1
ooo
```
### 样例输出 #3
```
25
aoo
boo
coo
doo
eoo
foo
goo
hoo
ioo
joo
koo
loo
moo
noo
poo
qoo
roo
soo
too
uoo
voo
woo
xoo
yoo
zoo
```
## 提示

### 样例 #1 解释

在这个样例中，任何字符变化都不会影响答案。唯一 Bessie 可能发出的哞叫是 $\tt{moo}$。

### 样例 #2 解释

在这个样例中，位置 $8$（从零开始索引）的 $\tt{a}$ 可能是由 $\tt b$ 损坏导致的，这使得 $\tt baa$ 成为一种 Bessie 发出两次的可能的哞叫。此外，位置 $11$ 的 $\tt q$ 可能是由 $\tt c$ 损坏导致的，这使得 $\tt cqq$ 成为一种 Bessie 可能的哞叫。$\tt aqq$ 可以通过将 $\tt c$ 换成 $\tt a$ 来达到。

### 测试点性质
- 测试点 1-3：样例。
- 测试点 4-8：$N≤100$。
- 测试点 9-13：没有额外限制。


---

---
title: "[USACO1.3] 最长的回文 Calf Flac"
layout: "post"
diff: 普及/提高-
pid: P1210
tag: ['字符串', '搜索', 'USACO', '枚举']
---
# [USACO1.3] 最长的回文 Calf Flac
## 题目描述

据说如果你给无限只母牛和无限台巨型便携式电脑（有非常大的键盘 ), 那么母牛们会制造出世上最棒的回文。你的工作就是去寻找这些牛制造的奇观（最棒的回文）。

在寻找回文时不用理睬那些标点符号、空格（但应该保留下来以便做为答案输出）, 只用考虑字母 ${\tt A}\sim {\tt Z}$ 和 ${\tt a}\sim {\tt z}$。要你寻找的最长的回文的文章是一个不超过 $20{,}000$ 个字符的字符串。我们将保证最长的回文不会超过 $2{,}000$ 个字符（在除去标点符号、空格之前）。
## 输入格式

输入文件不会超过 $20,000$ 字符。这个文件可能一行或多行，但是每行都不超过 $80$ 个字符（不包括最后的换行符）。
## 输出格式

输出的第一行应该包括找到的最长的回文的长度。

下一行或几行应该包括这个回文的原文（没有除去标点符号、空格），把这个回文输出到一行或多行（如果回文中包括换行符）。

如果有多个回文长度都等于最大值，输出最前面出现的那一个。

## 样例

### 样例输入 #1
```
Confucius say: Madam, I'm Adam. 
```
### 样例输出 #1
```
11
Madam, I'm Adam
```
## 提示

题目翻译来自NOCOW。

USACO Training Section 1.3



---

---
title: "[蓝桥杯 2025 省 A] 好串的数目"
layout: "post"
diff: 普及/提高-
pid: P12143
tag: ['字符串', '2025', '蓝桥杯省赛']
---
# [蓝桥杯 2025 省 A] 好串的数目
## 题目描述

对于一个长度为 $n$ 的字符串 $s = s_0s_1 \cdots s_{n-1}$ 来说，子串的定义是从中选出两个下标 $l, r$ $(0 \leq l \leq r \leq n-1)$，这之间所有的字符组合起来的一个新的字符串：$s' = s_ls_{l+1} \cdots s_r$ 就是其中一个子串。

现在给出一个只有数字字符 $0 \sim 9$ 组成的数字字符串，小蓝想要知道在其所有的子串中，有多少个子串是好串。一个子串是好串，当且仅当它满足以下两个条件之一：
1. 单字符子串一定是好串，即当子串长度为 $1$ 时，它总是好串；
2. 长度大于 $1$ 时，可以拆分为两个**连续非递减子串**：
   一个串 $p = p_0p_1 \cdots p_{k-1}$ 为**连续非递减子串**是指，对于所有 $1 \leq i < k$，满足 $p_i = p_{i-1}$ 或 $p_i = p_{i-1} + 1$。即数字串中的每一个数字，要么等于上一个数字，要么等于上一个数字加 $1$。例如 `12233`、`456` 是连续非递减子串。
## 输入格式

输入一行包含一个字符串 $s$。
## 输出格式

输出一行包含一个整数表示答案，即好串的数目。
## 样例

### 样例输入 #1
```
12258
```
### 样例输出 #1
```
12
```
### 样例输入 #2
```
97856
```
### 样例输出 #2
```
13
```
## 提示

### 样例说明 1

- 长度为 $1$ 的好串：`1`、`2`、`2`、`5`、`8`，共 $5$ 个；
- 长度为 $2$ 的好串：`12`、`22`、`25`、`58`，共 $4$ 个；
- 长度为 $3$ 的好串：`122`、`225`，共 $2$ 个；
- 长度为 $4$ 的好串：`1225`，共 $1$ 个；

总计 $5 + 4 + 2 + 1 = 12$ 个。

### 样例说明 2
- 长度为 $1$ 的好串：`9`、`7`、`8`、`5`、`6`，共 $5$ 个；
- 长度为 $2$ 的好串：`97`、`78`、`85`、`56`，共 $4$ 个；
- 长度为 $3$ 的好串：`978`、`785`、`856`，共 $3$ 个；
- 长度为 $4$ 的好串：`7856`，共 $1$ 个；

总计 $5 + 4 + 3 + 1 = 13$ 个。

### 评测用例规模与约定

- 对于 $20\%$ 的评测用例，$1 \leq n \leq 5$；
- 对于 $40\%$ 的评测用例，$1 \leq n \leq 20$；
- 对于 $60\%$ 的评测用例，$1 \leq n \leq 100$；
- 对于 $70\%$ 的评测用例，$1 \leq n \leq 10^3$；
- 对于 $80\%$ 的评测用例，$1 \leq n \leq 10^4$；
- 对于所有评测用例，$1 \leq n \leq 10^5$，$s$ 中只包含数字字符 $0 \sim 9$。


---

---
title: "[蓝桥杯 2023 国 Java B] 不完整的算式"
layout: "post"
diff: 普及/提高-
pid: P12219
tag: ['模拟', '字符串', '2023', '蓝桥杯国赛']
---
# [蓝桥杯 2023 国 Java B] 不完整的算式
## 题目描述

小蓝在黑板上写了一个形如 $A \quad op \quad B = C$ 的算式，其中 $A$、$B$、$C$ 都是非负整数，$op$ 是 $+$、$-$、$\times$、$/$（整除）四种运算之一。

不过 $A$、$op$、$B$、$C$ 这四部分有一部分被不小心的同学擦掉了。

给出这个不完整的算式，其中被擦掉的部分（被擦掉的部分是被完整的擦掉，不会出现留下若干位数字的情况）用 $\tt{?}$ 代替。请你输出被擦掉的部分。
## 输入格式

输入只有一行，包含一个字符串代表如上文所述的不完整的算式。
## 输出格式

如果被擦掉的部分是 $A$、$B$、$C$ 之一，请输出一个整数代表答案。如果被擦掉的部分是 $op$，请输出 $\tt{+}$、$\tt{-}$、$\tt{*}$、$\tt{/}$ 四个字符之一代表答案。
## 样例

### 样例输入 #1
```
1+?=2
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
10?3=3
```
### 样例输出 #2
```
/
```
## 提示

### 评测用例规模与约定

- 对于 $20\%$ 的数据，被擦掉的部分是 $C$。
- 对于 $40\%$ 的数据，被擦掉的部分是 $op$。
- 对于 $100\%$ 的数据，算式长度不超过 $10$，不包含空格。算式中出现的整数不包含多余的前导 $0$。输入保证合法且有唯一解。


---

---
title: "[蓝桥杯 2023 国 C] 定时任务"
layout: "post"
diff: 普及/提高-
pid: P12240
tag: ['模拟', '字符串', '2023', '枚举', '蓝桥杯国赛']
---
# [蓝桥杯 2023 国 C] 定时任务
## 题目描述

Cron 表达式在定时任务中经常被使用，在这里我们用了一种简化后的版本 SimpleCron 表达式：SimpleCron 表达式是一个具有时间含义的字符串，字符串以 $4$ 个空格隔开，分为 $5$ 个域，格式为 $X \ X \ X \ X \ X$，其中 $X$ 是一个域的占位符。$5$ 个域从左至右依次为秒 $(0 - 59)$、分钟 $(0 - 59)$、小时 $(0 - 23)$、日期 $(1 - 31)$、月份 $(1 - 12)$，其中括号内为他们各自的取值范围。同时域内取值也可以使用一些特殊字符（每个域内只能使用一种特殊字符）：

1. 特殊字符 $\tt{*}$（ASCII 码为 $42$）表示所有可能的值。例如：在分钟域内表示每一分钟；在日期域内表示月内的每一天。
2. 特殊字符 $\tt{,}$（ASCII 码为 $44$）表示列出枚举值。例如：在秒域内，$3,20$ 表示分别在 3 秒和 20 秒执行一次任务。
3. 特殊字符 $\tt{-}$（ASCII 码为 $45$）表示范围，可以视为连续的若干个枚举值。例如：$1 - 5$ 等价于 $1,2,3,4,5$。

例如，

$$ 421,3,151 - 31 * $$

表示的含义是每个月份中的每一天中的 $01:02:04$、$03:02:04$、$15:02:04$ 这三个时刻各执行一次，在 $2023$ 年一共会执行 $1095$ 次。

现在给出你一个合法的 SimpleCron 表达式，其中用到的所有数字均没有前导零。请问在 $2023$ 一整年当中，使用了这个表达式的定时任务总计会执行多少次？
## 输入格式

输入一行，包含一个 SimpleCron 字符串。
## 输出格式

输出一行，包含一个整数表示答案。
## 样例

### 样例输入 #1
```
4 2 1,3,15 1-31 *
```
### 样例输出 #1
```
1095
```
## 提示

### 评测用例规模与约定

对于所有评测用例，$0 \leq$ 秒域的取值 $\leq 59$，$0 \leq$ 分钟域的取值 $\leq$ $59$，$0 \leq$ 小时域的取值 $\leq 23$，$1 \leq$ 日期域的取值 $\leq 31$，$1 \leq$ 月份域的取值 $\leq 12$。


---

---
title: "[蓝桥杯 2024 国 Python A/Java A] 记事本"
layout: "post"
diff: 普及/提高-
pid: P12281
tag: ['模拟', '字符串', '2024', '蓝桥杯国赛']
---
# [蓝桥杯 2024 国 Python A/Java A] 记事本
## 题目描述

小蓝经常用记事本记录文字，最近他发现记事本功能太少，因此他写了一款插件用来支持记事本更多的文本编辑功能，这些功能如下表所示：

| 命令 | 功能 |
| :---: | :---: |
| $[n]\mathrm{h}$ | 光标向左移动 $[n]$ 个字符（到最左侧则停止）。 |
| $[n]\mathrm{l}$ | 光标向右移动 $[n]$ 个字符（到最右侧则停止）。 |
| $\mathrm{insert}$ "$[text]$" | 在当前光标位置插入文本 $[text]$，同时光标移动到 $[text]$ 右侧。 |
| $\mathrm d [n]\mathrm{h}$ | 删除光标左侧 $[n]$ 个字符（不足 $[n]$ 则全删除）。 |
| $\mathrm d [n]\mathrm{l}$ | 删除光标右侧 $[n]$ 个字符（不足 $[n]$ 则全删除）。 |

小蓝建立了一个新的文本文件，初始是空白的，在经过若干次上述操作之后，请将文本内容输出。
## 输入格式

输入的第一行包含一个整数 $T$，表示操作次数。

接下来 $T$ 行，每行包含一个命令，格式如上表所示。
## 输出格式

输出一行包含一个字符串表示最终文本内容。
## 样例

### 样例输入 #1
```
9
d1h
insert "hello"
insert " world"
7h
d2h
insert "11"
3l
d1l
insert "0"
```
### 样例输出 #1
```
he11o w0rld
```
## 提示

### 评测用例规模与约定

对于所有评测用例，$1 \leq T \leq 100$，$1 \leq |text| \leq 100$，$1 \leq n \leq 100$，$text$ 仅包含大小写字母、数字、空格。


---

---
title: "[蓝桥杯 2024 国 C] 集合的数量"
layout: "post"
diff: 普及/提高-
pid: P12314
tag: ['模拟', '字符串', '2024', '蓝桥杯国赛']
---
# [蓝桥杯 2024 国 C] 集合的数量
## 题目背景

截止 2025 年 4 月 23 日，蓝桥杯官网本题测试数据不符合测试点范围要求，存在类似如下的数据：

```
9
{}
{}
{""}
{"ejoa"}
{"aehr","ncuy"}
{"lidm","dgxy"}
{"fzxh"}
{"vtfh","vtfh","ksoc","vtfh"}
{"ksoc","vtfh","ksoc","vtfh"}
```

洛谷的数据剔除了此类情况。如果需要在蓝桥杯题库提交本题请注意这个问题。
## 题目描述

小蓝有 $n$ 个集合，这些集合中的元素还未去重。每个集合 $S_i$ 最多含有 $5$ 个长度不大于 $4$ 的仅含小写字母的字符串 $S_{i,j}$。

你需要计算小蓝的这些集合去重后有多少个（集合内的元素和集合之间都要去重）。

每个集合用 `{"abc"}`，`{"a","b","c","d"}` 的形式输入 (无空格)。

## 输入格式

输入的第一行包含一个整数 $n$。

接下来 $n$ 行，每行包含一个字符串，描述一个集合 $S_i$。
## 输出格式

输出一行包含一个整数表示答案。
## 样例

### 样例输入 #1
```
3
{"a","b","b","b"}
{"a","a","b","b"}
{"a","a","a","b"}
```
### 样例输出 #1
```
1
```
## 提示

### 样例说明

三个集合本质上都是 `{"a","b"}`。

### 评测用例规模与约定
- 对于 $40\%$ 的评测用例，$n \leq 10$；
- 对于所有评测用例，$1 \leq n \leq 1000$，$|S_i| \leq 5$，$|S_{i,j}| \leq 4$ 。



---

---
title: "穿睡衣军训"
layout: "post"
diff: 普及/提高-
pid: P12597
tag: ['模拟', '字符串', '有限状态自动机', '双指针 two-pointer']
---
# 穿睡衣军训
## 题目背景

在本题中，我们称一个串 $x$ 是一个串 $y$ 的**子串**当且仅当在 $y$ 开头和结尾删除若干个（可以为 $0$ 个）字符后得到的字符串与 $x$ 相同。例如，$\texttt{bc}$,$\texttt{abc}$,$\texttt{a}$,$\texttt{abcd}$ 都是字符串 $\texttt{abcd}$ 的子串，但 $\texttt{abd}$ 不是。

我们称一个串 $x$ 是一个串 $y$ 的**子序列**当且仅当在 $y$ 中删除若干个（可以为 $0$ 个）字符后得到的字符串与 $x$ 相同。例如，$\texttt{bc}$,$\texttt{abc}$,$\texttt{a}$,$\texttt{abcd}$,$\texttt{abd}$ 都是字符串 $\texttt{abcd}$ 的子串，但 $\texttt{dcba}$ 不是。

特别的，空串是任何串的子串，也是任何串的子序列。
## 题目描述

给定两个字符串 $s,t$，扶苏想让你求出一个字符串 $x$，满足：

- $x$ 是 $s$ 的**子串**。
- $x$ 是 $t$ 的**子序列**。
- 在所有满足前述两条的字符串中，$x$ 的长度最长。
- 在所有满足前述三条的字符串中，$x$ 的字典序最小。

请你帮她求出这样的字符串 $x$。
## 输入格式

**本题单个测试点内有多组测试数据**，第一行是一个整数，表示数据组数 $T$。

对每组数据，输入两行，每行一个字符串，依次表示 $s$ 和 $t$。
## 输出格式

对每组数据，输出一行一个字符串，表示你找到的 $x$。  
特别的，如果 $x$ 是空串，你需要输出一个空行。
## 样例

### 样例输入 #1
```
3
xyzdabc
xaybzc
abc
xyz
abbcd
aabbdcd
```
### 样例输出 #1
```
abc

abbcd
```
## 提示

## 数据规模与约定

用 $|x|$ 表示字符串 $x$ 的长度。

- 对 $10\%$ 的数据，$T = 0$。
- 对 $30\%$ 的数据，$|s| = 1$。
- 对 $50\%$ 的数据，$|s|, |t| \leq 10$。
- 对 $80\%$ 的数据，$|s|, |t| \leq 100$。
- 对 $100\%$ 的数据，保证 $0 \leq T \leq 10$，$1 \leq |s|\leq 10^3$，$1 \leq |t| \leq 10^5$，输入字符串只含小写英文字母。


---

---
title: "字串距离"
layout: "post"
diff: 普及/提高-
pid: P1279
tag: ['字符串', '动态规划 DP']
---
# 字串距离
## 题目描述

设有字符串 $X$，我们称在 $X$ 的头尾及中间插入任意多个空格后构成的新字符串为 $X$ 的扩展串，如字符串 $X$ 为$\verb!abcbcd!$，则字符串 $\verb!abcb␣cd!$，$\verb!␣a␣bcbcd␣!$ 和 $\verb!abcb␣cd␣!$ 都是 $X$ 的扩展串，这里 $\verb!␣!$ 代表空格字符。

如果 $A_1$ 是字符串 $A$ 的扩展串，$B_1$ 是字符串 $B$ 的扩展串，$A_1$ 与 $B_1$ 具有相同的长度，那么我们定义字符串 $A_1$ 与 $B_1$ 的距离为相应位置上的字符的距离总和，而两个非空格字符的距离定义为它们的 ASCII 码的差的绝对值，而空格字符与其他任意字符之间的距离为已知的定值K，空格字符与空格字符的距离为 $0$。在字符串 $A$、$B$ 的所有扩展串中，必定存在两个等长的扩展串 $A_1$，$B_1$，使得 $A_1$ 与 $B_1$ 之间的距离达到最小，我们将这一距离定义为字符串 $A$，$B$ 的距离。

请你写一个程序，求出字符串 $A$，$B$ 的距离。

## 输入格式

输入文件第一行为字符串 $A$ ，第二行为字符串 $B$。$A$，$B$ 均由小写字母组成且长度均不超过 $2000$。第三行为一个整数 $K(1\leq K\leq 100)$，表示空格与其他字符的距离。

## 输出格式

输出文件仅一行包含一个整数，表示所求得字符串 $A,B$ 的距离。

## 样例

### 样例输入 #1
```
cmc

snmn

2


```
### 样例输出 #1
```
10


```


---

---
title: "[蓝桥杯 2025 国 B] 子串去重"
layout: "post"
diff: 普及/提高-
pid: P12838
tag: ['字符串', '二分', '2025', '蓝桥杯国赛']
---
# [蓝桥杯 2025 国 B] 子串去重
## 题目背景

洛谷数据默认字符串由小写字母构成。
## 题目描述

给定一个字符串 $S$ 以及若干组询问，每个询问包含两个区间 $(L_a, R_a)$, $(L_b, R_b)$，你需要判定 $S_{L_a}, S_{L_a+1}, \ldots, S_{R_a}$ 与 $S_{L_b}, S_{L_b+1}, \ldots, S_{R_b}$ 去重后有多少个位置上的字符是不同的。

这里的去重指的是每个子串对于每种字符，只保留第一个出现的那个，后续出现的直接丢弃。

例如 $\tt{aabcbac}$ 在选中区间 $[1,5]$ 时，得到子串 $\tt{aabcb}$，去重后为 $\tt{abc}$，选中区间 $[3,6]$ 时得到 $\tt{bcba}$，去重后为 $\tt{bca}$。

特别地，两个长度不同的子串中，较长串的多出的部分每个位置都视为不同。
## 输入格式

输入第一行包含一个字符串 $S$。

第二行包含一个整数 $m$，表示询问次数。

接下来 $m$ 行，每行包含四个整数，表示一次询问。
## 输出格式

输出共 $m$ 行，每行一个整数对应每次询问的答案。
## 样例

### 样例输入 #1
```
aabcbabacdab
3
1 1 2 2
1 10 6 9
4 7 9 12
```
### 样例输出 #1
```
0
1
2
```
## 提示

**【评测用例规模与约定】**

对于 40% 的评测用例，$|S| \leq 10$, $m = 1$。

对于 60% 的评测用例，$|S|, m \leq 5000$。

对于 100% 的评测用例，$1 \leq |S|, m \leq 10^5$, $1 \leq L_a \leq R_a \leq |S|$, $1 \leq L_b \leq R_b \leq |S|$。


---

---
title: "[GCJ 2020 #1A] Pattern Matching"
layout: "post"
diff: 普及/提高-
pid: P13053
tag: ['字符串', '2020', 'Special Judge', 'Google Code Jam']
---
# [GCJ 2020 #1A] Pattern Matching
## 题目描述

Many terminals use asterisks (`*`) to signify "any string", including the empty string. For example, when listing files matching `BASH*`, a terminal may list BASH, BASHER and BASHFUL. For `*FUL`, it may list BEAUTIFUL, AWFUL and BASHFUL. When listing `B*L`, BASHFUL, BEAUTIFUL and BULL may be listed.

In this problem, formally, a pattern is a string consisting of only uppercase English letters and asterisks (`*`), and a name is a string consisting of only uppercase English letters. A pattern $p$ matches a name $m$ if there is a way of replacing every asterisk in $p$ with a (possibly empty) string to obtain $m$. Notice that each asterisk may be replaced by a different string.

Given $\mathrm{N}$ patterns, can you find a single name of at most $10^{4}$ letters that matches all those patterns at once, or report that it cannot be done?
## 输入格式

The first line of the input gives the number of test cases, $\mathrm{T}$. $\mathrm{T}$ test cases follow. Each test case starts with a line with a single integer $\mathrm{N}$: the number of patterns to simultaneously match. Then, $\mathrm{N}$ lines follow, each one containing a single string $\mathrm{P}_{\mathrm{i}}$ representing the $\mathrm{i}$-th pattern.
## 输出格式

For each test case, output one line containing `Case #x: y`, where $\mathrm{x}$ is the test case number (starting from 1) and $\mathrm{y}$ is any name containing at most $10^{4}$ letters such that each $\mathrm{P}_{\mathrm{i}}$ matches $\mathrm{y}$ according to the definition above, or `*` (i.e., just an asterisk) if there is no such name.
## 样例

### 样例输入 #1
```
2
5
*CONUTS
*COCONUTS
*OCONUTS
*CONUTS
*S
2
*XZ
*XYZ
```
### 样例输出 #1
```
Case #1: COCONUTS
Case #2: *
```
## 提示

**Sample Explanation**

In Sample Case #1, there are other possible answers, including COCOCONUTS and ILIKECOCONUTS. Neither COCONUTSAREGREAT nor COCOANUTS would be acceptable. Notice that the same pattern may appear more than once within a test case.

In Sample Case #2, there is no acceptable name, so the answer is `*`.

The following cases could not appear in Test Set 1, but could appear in Test Set 2 or Test Set 3:
```
  4
  H*O
  HELLO*
  *HELLO
  HE*
```
HELLO and HELLOGOODBYEHELLO are examples of acceptable answers. OTHELLO and HELLOO would not be acceptable.
```
  2
  CO*DE
  J*AM
```
There is no name that matches both patterns, so the answer would be `*`.
```
  2
  CODE*
  *JAM
```
CODEJAM is one example of an acceptable answer.

The following cases could not appear in Test Set 1 or Test Set 2, but could appear in Test Set 3:
```
  2
  A*C*E
  *B*D*
```
ABCDE and ABUNDANCE are among the possible acceptable answers, but BOLDFACE is not.
```
  2
  A*C*E
  *B*D
```
There is no name that matches both patterns, so the answer would be `*`.

**Limits**

- $1 \leqslant \mathrm{T} \leqslant 100$.
- $2 \leqslant \mathrm{N} \leqslant 50$.
- $2 \leqslant$ length of $\mathrm{P}_{\mathrm{i}} \leqslant 100$, for all $\mathrm{i}$.
- Each character of $\mathrm{P}_{\mathrm{i}}$ is either an uppercase English letter or an asterisk (*), for all $\mathrm{i}$.
- At least one character of $\mathrm{P}_{\mathrm{i}}$ is an uppercase English letter, for all $\mathrm{i}$.

**Test set 1 (5 Pts, Visible Verdict)**

- Exactly one character of $\mathrm{P}_{\mathrm{i}}$ is an asterisk (*), for all $\mathrm{i}$.

- The leftmost character of $\mathrm{P}_{\mathrm{i}}$ is the only asterisk (*), for all $\mathrm{i}$.

**Test set 2 (5 Pts, Visible Verdict)**

- Exactly one character of $\mathrm{P}_{\mathrm{i}}$ is an asterisk (*), for all $\mathrm{i}$.

**Test set 3 (18 Pts, Visible Verdict)**

- At least one character of $\mathrm{P}_{\mathrm{i}}$ is an asterisk (*), for all $\mathrm{i}$.



---

---
title: "logo语言"
layout: "post"
diff: 普及/提高-
pid: P1322
tag: ['字符串', '搜索', '递归']
---
# logo语言
## 题目描述

Logo 语言命令可以指挥海龟在屏幕中爬行。本问题只使用 Logo 语言的三个语句：前进 `FD`，倒退 `BK` 和重复 `REPEAT`，因此，海龟只在一条直线上来回爬行。输入一行 logo 的命令行，输出海龟在屏幕中离开原来位子的距离（假设屏幕很大，可以让海龟移开 $10^9$ 的距离）。

例如：

- 输入 `FD 100` ，输出：$100$。

- 输入 `FD 100 BK 150`， 输出：$50$。

- 输入 `REPEAT 5[FD 100 BK 50]`， 输出：$250$。

- 输入 `REPEAT 5[FD 50 REPEAT 10[FD 100]]`， 输出：$5250$。
## 输入格式

一行，一个字符串，符合上述规定的 logo 命令行。
## 输出格式

一个数据，海龟离开原来位子的距离。
## 样例

### 样例输入 #1
```
FD 100

```
### 样例输出 #1
```
100

```
## 提示

每个语句输入数据的绝对值不超过 $1000$。输出结果不会超过 $10^9$。



---

---
title: "删数问题"
layout: "post"
diff: 普及/提高-
pid: P1323
tag: ['模拟', '字符串', '贪心', '优先队列', '队列']
---
# 删数问题
## 题目描述

一个集合有如下元素：$1$ 是集合元素；若 $P$ 是集合的元素，则 $2\times P+1$，$4\times P+5$ 也是集合的元素。

取出此集合中最小的 $k$ 个元素，按从小到大的顺序组合成一个多位数，现要求从中删除 $m$ 个数位上的数字，使得剩下的数字最大，编程输出删除前和删除后的多位数字。

注：不存在所有数被删除的情况。
## 输入格式

只有一行两个整数，分别代表 $k$ 和 $m$。
## 输出格式

输出为两行两个整数，第一行为删除前的数字，第二行为删除后的数字。

## 样例

### 样例输入 #1
```
5  4
```
### 样例输出 #1
```
137915
95
```
## 提示

#### 数据规模与约定

- 对于 $30\%$ 的数据，保证 $1\le k,m\le300$。
- 对于 $100\%$ 的数据，保证 $1\le k,m\le3\times10^4$。


---

---
title: "[GCJ 2014 #1B] The Repeater"
layout: "post"
diff: 普及/提高-
pid: P13250
tag: ['字符串', '贪心', '2014', 'Google Code Jam']
---
# [GCJ 2014 #1B] The Repeater
## 题目描述

Fegla and Omar like to play games every day. But now they are bored of all games, and they would like to play a new game. So they decided to invent their own game called "The Repeater".

They invented a $2$ player game. Fegla writes down $N$ strings. Omar's task is to make all the strings identical, if possible, using the minimum number of actions (possibly $0$ actions) of the following two types:

- Select any character in any of the strings and repeat it (add another instance of this character exactly after it). For example, in a single move Omar can change "abc" to "abbc" (by repeating the character 'b').
- Select any two adjacent and identical characters in any of the strings, and delete one of them. For example, in a single move Omar can change "abbc" to "abc" (delete one of the 'b' characters), but can't convert it to "bbc".

The $2$ actions are independent; it's not necessary that an action of the first type should be followed by an action of the second type (or vice versa).

Help Omar to win this game by writing a program to find if it is possible to make the given strings identical, and to find the minimum number of moves if it is possible.
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. Each test case starts with a line containing an integer $N$ which is the number of strings. Followed by $N$ lines, each line contains a non-empty string (each string will consist of lower case English characters only, from 'a' to 'z').
## 输出格式

For each test case, output one line containing "Case #$x$: $y$", where $x$ is the test case number (starting from $1$) and $y$ is the minimum number of moves to make the strings identical. If there is no possible way to make all strings identical, print "Fegla Won" (quotes for clarity).
## 样例

### 样例输入 #1
```
5
2
mmaw
maw
2
gcj
cj
3
aaabbb
ab
aabb
2
abc
abc
3
aabc
abbc
abcc
```
### 样例输出 #1
```
Case #1: 1
Case #2: Fegla Won
Case #3: 4
Case #4: 0
Case #5: 3
```
## 提示

**Limits**

- $1 \leq T \leq 100$.
- $1 \leq \text{length of each string} \leq 100$.

**Small dataset(10 Pts)**

- Time limit: $60$ seconds.
- $N = 2$.

**Large dataset(13 Pts)**

- Time limit: $120$ seconds.
- $2 \leq N \leq 100$.


---

---
title: "[GCJ 2013 #1C] Consonants"
layout: "post"
diff: 普及/提高-
pid: P13291
tag: ['字符串', '2013', '组合数学', '前缀和', 'Google Code Jam']
---
# [GCJ 2013 #1C] Consonants
## 题目描述

In English, there are $26$ letters that are either **vowels** or **consonants**. In this problem, we consider a, e, i, o, and u to be vowels, and the other $21$ letters to be consonants.

A tribe living in the Greatest Colorful Jungle has a tradition of naming their members using English letters. But it is not easy to come up with a good name for a new member because it reflects the member's social status within the tribe. It is believed that the less common the name he or she is given, the more socially privileged he or she is.

The leader of the tribe is a professional linguist. He notices that hard-to-pronounce names are uncommon, and the reason is that they have too many **consecutive consonants**. Therefore, he announces that the social status of a member in the tribe is determined by its n-value, which is the number of substrings with at least $n$ consecutive consonants in the name. For example, when $n = 3$, the name "quartz" has the n-value of $4$ because the substrings quartz, uartz, artz, and rtz have at least $3$ consecutive consonants each. A greater n-value means a greater social status in the tribe. Two substrings are considered different if they begin or end at a different point (even if they consist of the same letters), for instance "tsetse" contains $11$ substrings with two consecutive consonants, even though some of them (like "tsetse" and "tsetse") contain the same letters.

All members in the tribe must have their names and $n$ given by the leader. Although the leader is a linguist and able to ensure that the given names are meaningful, he is not good at calculating the n-values. Please help the leader determine the n-value of each name. Note that different names may have different values of $n$ associated with them.
## 输入格式

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. The first line of each test case gives the name of a member as a string of length $L$, and an integer $n$. Each name consists of one or more lower-case English letters.

## 输出格式

For each test case, output one line containing "Case #x: y", where $x$ is the case number (starting from $1$) and $y$ is the n-value of the member's name.
## 样例

### 样例输入 #1
```
4
quartz 3
straight 3
gcj 2
tsetse 2
```
### 样例输出 #1
```
Case #1: 4
Case #2: 11
Case #3: 3
Case #4: 11
```
## 提示

**Limits**

- $1 \leqslant T \leqslant 100$.
- $0 < n \leqslant L$.

**Small dataset (8 Pts, Test set 1 - Visible)**

- $1 \leqslant L \leqslant 100$.

**Large dataset (20 Pts, Test set 2 - Hidden)**

- $1 \leqslant L \leqslant 10^6$.
- The input file will be no larger than 6MB.


---

---
title: "[COCI 2020/2021 #1] Bajka"
layout: "post"
diff: 普及/提高-
pid: P13425
tag: ['字符串', '动态规划 DP', '2020', '深度优先搜索 DFS', '记忆化搜索', 'COCI（克罗地亚）']
---
# [COCI 2020/2021 #1] Bajka
## 题目描述

Little Fabijan got bored with picture books, so he decided to read his first fairytale. Unfortunately, Fabijan often encounters a word that scares him. To overcome his fear, he will play a game he invented.

The scary word can be represented as an array of $n$ lowercase letters. To start the game, Fabijan puts his finger on some position of the array and writes the letter from that position on a piece of paper. He then performs one of the following moves an arbitrary number of times:

- He moves the finger to a position that is one place to the left or to the right of the current position, if that position exists. Also, Fabijan will then write the letter from the new position on the paper, after the last written letter.
- He moves the finger to any position with the same letter as the current one. Fabijan will not write anything on the paper in this case.

It takes him $|x - y|$ seconds to move the finger from position $x$ to position $y$.

Fabijan will overcome his fear of the word if, at the end of the game, his favourite word is written on the paper. He wants to finish the fairytale as soon as possible, so he asks you to tell him the minimum number of seconds it will take him to overcome his fear of the given scary word.
## 输入格式

The first line contains integers $n$ and $m$ ($1 \leq n, m \leq 300$).

The second line contains $n$ lowercase letters, the word that scares Fabijan.

The third line contains $m$ lowercase letters, Fabijan's favourite word.
## 输出格式

Print the shortest possible time in seconds Fabijan needs to write his favourite word on the paper, or $-1$ if that is not possible.
## 样例

### 样例输入 #1
```
2 2
wa
ac
```
### 样例输出 #1
```
-1
```
### 样例输入 #2
```
7 7
monolog
nogolom
```
### 样例输出 #2
```
10
```
### 样例输入 #3
```
14 5
niskoobrazovan
boook
```
### 样例输出 #3
```
5
```
## 提示

Clarification of the third example:

Fabijan will first put his finger on position 7 and write down the letter 'b'. He will then move the finger two times to the left, and each time write down the letter 'o'. In the next step, he will move the finger to position 6 using the second type of move. Finally, he will again move the finger two times to the left, and write down the letters 'o' and 'k'. It took him five seconds in total, one second per move.

### Scoring

In test cases worth $20$ points, letters in the word that scares Fabijan will be pairwise distinct.


---

---
title: "[USACO2.3] 零的数列 Zero Sum"
layout: "post"
diff: 普及/提高-
pid: P1473
tag: ['字符串', '搜索', '数学', 'USACO', '进制']
---
# [USACO2.3] 零的数列 Zero Sum
## 题目描述

请考虑一个由 $1$ 到 $N$ 的数字组成的递增数列：$1, 2, 3, \ldots, N$。

现在请在数列中插入 `+` 表示加，或者 `-` 表示减，` `（空格） 表示空白（例如 `1-2 3` 就等于 `1-23`），来将每一对数字组合在一起（请不要在第一个数字前插入符号）。

计算该表达式的结果并判断其值是否为 $0$。 请你写一个程序找出所有产生和为零的长度为N的数列。

## 输入格式

单独的一行表示整数 $N$（$3 \leq N \leq 9$）。

## 输出格式

按照 ASCI I码的顺序，输出所有在每对数字间插入 `+`，`-`，` `（空格） 后能得到结果为零的数列。

## 样例

### 样例输入 #1
```
7

```
### 样例输出 #1
```
1+2-3+4-5-6+7
1+2-3-4+5+6-7
1-2 3+4+5+6+7
1-2 3-4 5+6 7
1-2+3+4-5+6-7
1-2-3-4-5+6+7
```
## 提示

翻译来自NOCOW

USACO 2.3



---

---
title: "迎春舞会之数字舞蹈"
layout: "post"
diff: 普及/提高-
pid: P1538
tag: ['模拟', '字符串']
---
# 迎春舞会之数字舞蹈
## 题目背景

HNSDFZ 的同学们为了庆祝春节，准备排练一场舞会。
## 题目描述

在越来越讲究合作的时代，人们注意的更多的不是个人物的舞姿，而是集体的排列。  

为了配合每年的倒计时，同学们决定排出——“数字舞蹈”。顾名思义就是所有人一起排成若干个数字 -\_\_\_-||||  更为创新的是，每个人都是趴在地上，保证横竖。  

现在给出数字及其要求摆出的大小，请你编程，模拟同学们的优美姿态。

## 输入格式

第一行为 $k$。$k$ 表示要摆出数字的大小。

第二行为全部由数字组成的字符串，即要摆出的几个数字。
## 输出格式

按题目要求输出。详见样例。

## 样例

### 样例输入 #1
```
2
1234567890

```
### 样例输出 #1
```
      --   --        --   --   --   --   --   -- 
   |    |    | |  | |    |       | |  | |  | |  |
   |    |    | |  | |    |       | |  | |  | |  |
      --   --   --   --   --        --   --      
   | |       |    |    | |  |    | |  |    | |  |
   | |       |    |    | |  |    | |  |    | |  |
      --   --        --   --        --   --   -- 

```
## 提示

### 数据范围及约定

对于全部数据，$k \le 30$，$ 0<|s|\le 255$。除了第一个数字之外，每个数字之前有 $1$ 个空格，所有数字全部对齐。

建议大家直接输出，不要保存。

如果对于大小和 $k$ 有疑问，请自行理解。


---

---
title: "yyy loves Easter_Egg I"
layout: "post"
diff: 普及/提高-
pid: P1580
tag: ['模拟', '字符串', '洛谷原创', '队列']
---
# yyy loves Easter_Egg I
## 题目背景

Soha 的出题效率着实让人大吃一惊。OI，数学，化学的题目都出好了，物理的题还没有一道。于是，Huntfire，absi2011，redbag 对 soha 进行轮番炸，准备炸到 soha 出来，不料，人群中冲出了个 kkksc03……
## 题目描述

![](https://cdn.luogu.com.cn/upload/pic/1456.png)

![](https://cdn.luogu.com.cn/upload/pic/1455.png)

yyy loves OI（Huntfire），yyy loves Maths（redbag），yyy loves Chemistry（absi2011）对 yyy loves Physics（soha）进行轮番炸，轰炸按照顺序进行，顺序为 Huntfire，redbag，absi2011。

现在这一题中，我们不考虑太复杂的队形形式。我们认为只要这一句内含有且恰好含有一次@，@的人和上一句话一样就算为队形。

比如以下也视为队形：

- `yyy loves OI : @yyy loves Microelectronic`
- `yyy loves Maths : @yyy loves Microelectronic 我佩服soha的出题效率`
- `yyy loves OI : @yyy loves Microelectronic +1`
- `yyy loves Chemistry : +1 @yyy loves Microelectronic`

若 @ 的人与第一个人不同，就算队形被打破。若这个人在队形被打破之前出来发言了，或者就是他打破队形了，就算（油）炸成功了。

若（油）炸成功，输出 `Successful @某某某 attempt`，若队形被破坏先输出 `Unsuccessful @某某某 attempt`，再输出队形第一次被破坏的行数与第一次破坏队形的人的 $\text{id}$。

如果队形一直没被打破，就先输出 `Unsuccessful @某某某 attempt`，再输出队形的长度，最后输出 `Good Queue Shape`。

~~p.s.yyy loves Microelectronic 是 kkksc03~~


## 输入格式

$N$ 行，为轰炸开始后的一段消息记录，每行一条消息。消息格式：「消息发送者+`:`+消息内容」，每行消息长度不超过 $1000$。（中文用拼音代替）


## 输出格式

若（油）炸成功，输出 `Successful @某某某 attempt`，若队形被破坏第一行输出 `Unsuccessful @某某某 attempt`，接下来一行输出队形第一次被破坏的行数，第三行输出第一次破坏队形的人的 $\text{id}$。
如果队形一直没被打破，就先输出 `Unsuccessful @某某某 attempt`，再输出队形的长度，最后输出 `Good Queue Shape`。
## 样例

### 样例输入 #1
```
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Maths : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Chemistry : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Microelectronic : ni men wu liao me 
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv


```
### 样例输出 #1
```
Unsuccessful @yyy loves Physics attempt
4
yyy loves Microelectronic

```
### 样例输入 #2
```
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Maths : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Chemistry : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Maths : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Chemistry : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Maths : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Chemistry : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Physics : ni men gou le 


```
### 样例输出 #2
```
Successful @yyy loves Physics attempt

```
## 提示

**@yyy loves Physics 我佩服你的出题效率**

此题仅吐槽 soha，纪念出题者的队形，此队形长达 $91$ 行。

对于 $100\%$ 的数据,每行消息长度 $\le$ $10^3$。 

- 保证行数不超过 $5\times 10^4$；
- 保证输入文件大小不超过 $4\text{MB}$；
- 保证第一个说话的一定在 @ 某人；
- 保证大家的名字都是 $\text{yyy loves ***}$ 的格式；
- 保证每个人说的话中没有 `:`；
- 保证第一个说话的一定艾特了一个人且只 @ 了一个人；
- 保证第一个说话的一定不会艾特自己；
- 保证文件结束一定有一行空行，方便你判定文件结束；
- 并不保证后面说话的艾特了几个人 然而艾特人数不为一个人视为破坏队形；
- 并不保证后面说话是否会反复艾特同一个人；
- 并不保证被炸的人一定破坏队形；
- 并不保证这一题是或不是压轴题；
- 并不保证这一套比赛存在压轴题；
- 并不保证下一套比赛和这一套比赛一样水；
- 并不保证群里除了这 $4$ 个人和 kkksc03 以外没有别人了；
- 并不保证你没 AC 这题的情况下吐槽 soha 不会出事儿；
- AC 了可以吐槽 soha 一句，soha 不会介意。


---

---
title: "失踪的7"
layout: "post"
diff: 普及/提高-
pid: P1590
tag: ['模拟', '字符串', '数学', '进制']
---
# 失踪的7
## 题目描述

远古的 Pascal 人也使用阿拉伯数字来进行计数，但是他们又不喜欢使用 $7$ ，因为他们认为 $7$ 是一个不吉祥的数字，所以 Pascal 数字 $8$ 其实表示的是自然数中的 $7$，$18$ 表示的是自然数中的 $16$ 。请计算，在正整数 $n$ 范围以内包含有多少个 Pascal 数字。

## 输入格式

第一行为正整数 $t$，接下来 $t$ 行，每行一个正整数 $n$，且保证输入 $n$ 的是 Pascal 数字


## 输出格式

对于每个正整数 $n$，输出 $n$ 以内的 Pascal 数的个数。

## 样例

### 样例输入 #1
```
2
10
20
```
### 样例输出 #1
```
9
18
```
## 提示

对于所有数据，$1 \leq t \leq 10000$，$1 \leq n \leq 2^{32}-1$。


---

---
title: "爱与愁的一千个伤心的理由"
layout: "post"
diff: 普及/提高-
pid: P1617
tag: ['模拟', '字符串', '洛谷原创']
---
# 爱与愁的一千个伤心的理由
## 题目背景

（本道题目隐藏了两首歌名，找找看哪~~~）

《爱与愁的故事第一弹·heartache》第二章。

经历了心痛后，爱与愁大神不行了。

## 题目描述

月落乌啼问爱与愁大神为什么，爱与愁大神写了一个数字 $n$（$n \le 9999$），说翻译成英语就知道为什么了。月落乌啼接过这个数字后，本想翻译成英语，但是班主任叫他去帮个忙。他想尽快知道答案，于是这个艰巨的任务就拜托你了。

标准美式英语，仅在末两位 $ \le 10$ 时加 `and` 且没有连字符。
## 输入格式

只有一行，一个数 $n$（$n \le 9999$）
## 输出格式

一行英文，表示 $n$ 翻译成英语的答案。
## 样例

### 样例输入 #1
```
5208

```
### 样例输出 #1
```
five thousand two hundred and eight

```
### 样例输入 #2
```
5280
```
### 样例输出 #2
```
five thousand two hundred eighty
```
### 样例输入 #3
```
5000
```
### 样例输出 #3
```
five thousand
```
### 样例输入 #4
```
5028
```
### 样例输出 #4
```
five thousand and twenty eight

```
## 提示

输出行初不大写。按标准美式英语输出，即两个非零的数中间没零则不加 `and`，行末无句号。


---

---
title: "解一元二次方程的烦恼"
layout: "post"
diff: 普及/提高-
pid: P1619
tag: ['模拟', '字符串', '数学', '洛谷原创']
---
# 解一元二次方程的烦恼
## 题目背景

JosephZheng 在写数学作业的预习。他往往使用 Casio 来帮忙解一元二次方程。但是 Casio 有一个问题，就是当 $\Delta=b^2-4ac$ 为一个大素数或大合数时，其开平方的结果会以小数显示，而不是老师要求的二次根式形式。JosephZheng 很是苦恼，一遇到这种情况就要手动解方程。一天他再也忍不住了，于是打开了电脑，编了一个 prime 程序……于是悲剧的 OIer 们就要跟着疯狂的 JosephZheng 一起编这个程序，呵呵……

## 题目描述

废话少说，给你一个大数 $N$（不一定在 int64 范围内），让你进行素性判断，然后分解质因数。当然，初中数学题不可能有大于 int64 的数让你判断素性，因此超过范围的数可以忽略不计。为了让程序更加贴心，JosephZheng 多了一些要求，会在输入输出中给出具体情况。

## 输入格式

一个大数 $N$（$N$ 为非负整数），其中这个数的各个数位之间可以插入各种符号，例如 $1234$ 可以为 `1 - 2alsdkjf3！@￥%！@@@##￥……！￥#-4` 等。你需要在这一长串乱码中找出这个要判断的数。输入数据可能有多组，如果读到一行没有数字的字串即结束。字符串长度可能大于 $255$。

## 输出格式

在读入数据之前先输出 `Enter the number=`，需要换行。

然后输出 `Prime?`，问号后有一个空格，但不要换行。

如果是质数则输出 `Yes!` 否则输出 `No!`。此时换行。

若果是质数就 halt，若是小于 $2$ 的数则在输出 `No!` 后也 halt。若是合数则分解质因数。如果该数大于四千万则输出 `The number is too large!`，然后 halt。否则分解质因数。输出结果的方式在输出样例中会详细给出。每组数据之间空一行。

## 样例

### 样例输入 #1
```
4
eed

```
### 样例输出 #1
```
Enter the number=
Prime? No!
4=2^2

Enter the number=

```
### 样例输入 #2
```
2
end

```
### 样例输出 #2
```
Enter the number=
Prime? Yes!

Enter the number=

```
### 样例输入 #3
```
-1
adfs

```
### 样例输出 #3
```
Enter the number=
Prime? No!

Enter the number=

```
### 样例输入 #4
```
1234###24#@13#@￥！1
hehe

```
### 样例输出 #4
```
Enter the number=
Prime? No!
The number is too large!

Enter the number=

```
### 样例输入 #5
```
1.5
1
1234324123512343123
@~@~@~@

```
### 样例输出 #5
```
Enter the number=
Prime? No!
15=3^1*5^1

Enter the number=
Prime? No!

Enter the number=
Prime? No!
The number is too large!

Enter the number=

```
### 样例输入 #6
```
12
halt@@

```
### 样例输出 #6
```
Enter the number=
Prime? No!
12=2^2*3^1

Enter the number=

```
## 提示

编这道题的 JosephZheng 有些无聊，但是很考验基本功哦！仔细审题！

水题一道。。。



---

---
title: "洛谷的文件夹"
layout: "post"
diff: 普及/提高-
pid: P1738
tag: ['模拟', '字符串', '树形数据结构', '洛谷原创', '枚举']
---
# 洛谷的文件夹
## 题目描述

kkksc03 是个非凡的空想家！在短时间内他设想了大量网页，然后总是交给可怜的 lzn 去实现。

洛谷的网页端，有很多文件夹，文件夹还套着文件夹。

例如：$\verb!/luogu/application/controller!$ 表示根目录下有一个名称为 $\verb!luogu!$ 的文件夹，这个文件夹下有一个名称 $\verb!application!$ 的文件夹，其中还有名为 $\verb!controller!$ 的文件夹。

每个路径的第 $1$ 个字符总是 $\verb!/!$，且没有两个连续的 $\verb!/!$，最后的字符不是 $\verb!/!$。所有名称仅包含数字和小写字母。

目前根目录是空的。kkksc03 想好了很多应该有的文件夹路径名。问题是，需要是使这些文件夹都存在，需要新建几个文件夹呢？

## 输入格式

输入文件第 $1$ 行为一个正整数 $N$。

接下来 $N$ 行，每行为一个描述路径的字符串，长度均不超过 $100$。
## 输出格式

输出应包含 $N$ 行，每行 $1$ 个正整数，第 $i$ 行输出若要使第 $1$ 个路径到第 $i$ 个路径存在，最少需要新建多少个文件夹。
## 样例

### 样例输入 #1
```
2
/luogu/application/controller
/luogu/application/view

```
### 样例输出 #1
```
3
4

```
### 样例输入 #2
```
3
/chicken
/chicken/egg
/chicken
```
### 样例输出 #2
```
1
2
2
```
### 样例输入 #3
```
4
/a
/a/b
/a/c
/b/b
```
### 样例输出 #3
```
1
2
3
5
```
## 提示

### 数据范围及约定


- 对于 $20\%$ 数据，有 $N \le 20$；
- 对于 $50\%$ 数据，有 $N \le 200$；
- 另有 $30\%$ 数据，有对于所有路径最多存在两个 $\verb!/!$（包含第 $1$ 个字符）；
- 对于所有数据，$N \le 1000$。


---

---
title: "Moo"
layout: "post"
diff: 普及/提高-
pid: P1885
tag: ['模拟', '字符串', '递归', '分治']
---
# Moo
## 题目描述

奶牛 Bessie 最近在学习字符串操作，它用如下的规则逐一的构造出新的字符串：

$S(0) =$ `moo`

$S(1) = S(0) +$ `m` $+$ `ooo` $+ S(0) =$ `moo` $+$ `m` $+$ `ooo` $+$ `moo` $=$ `moomooomoo`

$S(2) = S(1) +$ `m` $+$ `oooo` $+ S(1) =$ `moomooomoo` $+$ `m` $+$ `oooo` $+$  `moomooomoo` $=$ `moomooomoomoooomoomooomoo`

$\dots$

Bessie 就这样产生字符串，直到最后产生的那个字符串长度不小于读入的整数 $N$ 才停止。

通过上面观察，可以发现第 $k$ 个字符串是由：第 $k-1$ 个字符串 $+$ `m` $+$  $(k+2$ 个 $o) +$ 第 $k-1$ 个字符串连接起来的。

现在的问题是：给出一个整数 $N (1 \leq N \leq 10^9)$，问第 $N$ 个字符是字母 `m` 还是 `o`？

## 输入格式

一个正整数 $N$。

## 输出格式

一个字符，`m` 或者 `o`。

## 样例

### 样例输入 #1
```
11
```
### 样例输出 #1
```
m
```
## 提示

样例解释：

由题目所知：字符串 $S(0)$ 是 `moo`, 现在要求第 $11$ 个字符，显然字符串 $S(0)$ 不够长；

同样 $S(1)$ 的长度是 $10$，也不够长；$S(2)$ 的长度是 $25$，够长了，$S(2)$ 的第 $11$ 个字符是 `m`，所以答案就输出 `m`。



---

---
title: "凯撒密码"
layout: "post"
diff: 普及/提高-
pid: P1906
tag: ['字符串']
---
# 凯撒密码
## 题目描述

在元老院的支持下，Caesar率领罗马军团进攻高卢地区。但是他的军事行动并不顺利，他急需你的支持。

一天，你突然受到Caesar从前线写来的信。为了防止敌军偷窃情报，Caesar决定用自创的密码来写这封信。但是面对满纸的乱码，你也无从下手。于是你前往元老院询问这种密码的玄机。

元老们告诉你，这是凯撒移位密码（世界上最早的加密术——编者注），解读它非常的简单：

对于明文中的每个字母，Caesar会用它后面的第t个字母代替。例如，当t=3时，字母A将变成C，字母B将变成D，……，字母Y将变成A，字母Z将变成B（假设字母表是循环的）。

这样一来，字母表：A B C D E F G H I J K L M N O P Q R S T U V W X Y Z

将变成： C D E F G H I J K L M N O P Q R S T U V W X Y Z A B

明文：  I Need Soldiers  将加密为

密文：  K Pggf Uqnfkgtu

如此一来，需要传达的信息在外人看来就如同天书了。加上Caesar会不时更换t的值，使得密码变得更加难以捉摸。

你的任务是将Caesar的密码翻译为明文。

## 输入格式

你将得到若干段Caesar的密码，我们保证这是一句成文的英文句子。输入文件将保证小于50KB。

每个句子以一行“START”开始，下一行描述这个句子，再下一行以“END”结束。整个输入文件以“ENDOFINPUT”结束。

## 输出格式

对于每个句子，输出翻译后的明文

输出全部转为大写！

## 样例

### 样例输入 #1
```
START

NS BFW, JAJSYX TK NRUTWYFSHJ FWJ YMJ WJXZQY TK YWNANFQ HFZXJX

END

START

N BTZQI WFYMJW GJ KNWXY NS F QNYYQJ NGJWNFS ANQQFLJ YMFS XJHTSI NS WTRJ

END

START

IFSLJW PSTBX KZQQ BJQQ YMFY HFJXFW NX RTWJ IFSLJWTZX YMFS MJ

END

ENDOFINPUT


```
### 样例输出 #1
```
IN WAR, EVENTS OF IMPORTANCE ARE THE RESULT OF TRIVIAL CAUSES

I WOULD RATHER BE FIRST IN A LITTLE IBERIAN VILLAGE THAN SECOND IN ROME

DANGER KNOWS FULL WELL THAT CAESAR IS MORE DANGEROUS THAN HE


```
## 提示

1.如果你有看过《福尔摩斯探案集》的话，请回忆“跳舞娃娃”密码破译第一步；

2.我想这些可能会对你有帮助：

e 0.1268

t 0.0978

a 0.0788

o 0.0766

i 0.0707

n 0.0706

s 0.0634

r 0.0594



---

---
title: "外星密码"
layout: "post"
diff: 普及/提高-
pid: P1928
tag: ['模拟', '字符串', '递归', '分治']
---
# 外星密码
## 题目描述

有了防护伞，并不能完全避免 2012 的灾难。地球防卫小队决定去求助外星种族的帮助。经过很长时间的努力，小队终于收到了外星生命的回信。但是外星人发过来的却是一串密码。只有解开密码，才能知道外星人给的准确回复。解开密码的第一道工序就是解压缩密码，外星人对于连续的若干个相同的子串 $\texttt{X}$ 会压缩为 $\texttt{[DX]}$ 的形式（$D$ 是一个整数且 $1\leq D\leq99$），比如说字符串 $\texttt{CBCBCBCB}$ 就压缩为 $\texttt{[4CB]}$ 或者$\texttt{[2[2CB]]}$，类似于后面这种压缩之后再压缩的称为二重压缩。如果是 $\texttt{[2[2[2CB]]]}$ 则是三重的。现在我们给你外星人发送的密码，请你对其进行解压缩。

## 输入格式

输入一行，一个字符串，表示外星人发送的密码。

## 输出格式

输出一行，一个字符串，表示解压缩后的结果。
## 样例

### 样例输入 #1
```
AC[3FUN]
```
### 样例输出 #1
```
ACFUNFUNFUN
```
## 提示

【数据范围】

对于 $50\%$ 的数据：解压后的字符串长度在 $1000$ 以内，最多只有三重压缩。

对于 $100\%$ 的数据：解压后的字符串长度在 $20000$ 以内，最多只有十重压缩。保证只包含数字、大写字母、`[` 和 `]`。



---

---
title: "最长括号匹配"
layout: "post"
diff: 普及/提高-
pid: P1944
tag: ['字符串', '动态规划 DP', 'NOI 导刊']
---
# 最长括号匹配
## 题目描述

对一个由(,),[,]括号组成的字符串，求出其中最长的括号匹配子串。具体来说，满足如下条件的字符串成为括号匹配的字符串：

  1.(),[]是括号匹配的字符串。

2.若A是括号匹配的串，则(A),[A]是括号匹配的字符串。

3.若A,B是括号匹配的字符串，则AB也是括号匹配的字符串。

例如：(),[],([]),()()都是括号匹配的字符串，而][,[(])则不是。

字符串A的子串是指由A中连续若干个字符组成的字符串。

例如，A,B,C,ABC,CAB,ABCABCd都是ABCABC的子串。空串是任何字符串的子串。

## 输入格式

输入一行，为一个仅由()[]组成的非空字符串。

## 输出格式

输出也仅有一行，为最长的括号匹配子串。若有相同长度的子串，输出位置靠前的子串。

## 样例

### 样例输入 #1
```
([(][()]]()

```
### 样例输出 #1
```
[()]

```
### 样例输入 #2
```
())[]
```
### 样例输出 #2
```
()
```
## 提示

【数据范围】

对20%的数据，字符串长度<=100.

对50%的数据，字符串长度<=10000.

对100%的数据，字符串长度<=1000000.



---

---
title: "脑力达人之分割字串"
layout: "post"
diff: 普及/提高-
pid: P2031
tag: ['字符串', '动态规划 DP', '线性数据结构']
---
# 脑力达人之分割字串
## 题目背景

好吧，该来的废话还是要来的。

画外音：

终于，在两轮的重重选拔之后，我们的海选终于结束了。现在进入我们的循环赛环节。循坏赛一共有四场，最后选出得分最高的 $16$ 人进入对决，得分相同则和按用时排名，若仍有不能确定 $16$ 人的情况，则去尾处理。

欢迎您收看有洛谷卫视重磅推出的综合性文艺知识类节目“开心玩游戏，轻松赢比赛”，我是 LUWM。学编程，就选洛谷， 感谢洛谷 Online Judge 对本节目的大力支持。下面，我们有请 $10$ 位选手上台，由大屏幕给出题目。

## 题目描述

现在有一个字符串，你可以对这个字符串进行拆分，如 `abcvsdaas` 可以拆分为 `abc|vs|d|aas`，现在再给你一个字典，要求分割成的每一个子串必须要有包含其中的任意一个单词。那么最多可以分为几个子串呢？

## 输入格式

第一行，一行字符串

第二行一个正整数 $N$，表示字典中字符串的数量

接下来 $N$ 行，每行一个字符串 $A_i$，表示字典中的一个字符串。

## 输出格式

一个整数，表示最多的分割数。

## 样例

### 样例输入 #1
```
asdsd

3

as

sd

ds
```
### 样例输出 #1
```
2
```
## 提示

特殊情况：

如果原字符串不能被分割，请输出 $0$。



数据范围：

对于 $20\%$ 的数据，$1\leq |s| \leq 50,1\leq n\leq 50$。

对于 $100\%$ 的数据，$1\leq |A_i| \leq |s|\leq 300，1\leq N\leq 500$。

其中，$|s|,|A_i|$ 表示字符串 $s$ 与 $A_i$ 的长度。


---

---
title: "电话号码"
layout: "post"
diff: 普及/提高-
pid: P2037
tag: ['模拟', '字符串', '搜索']
---
# 电话号码
## 题目描述

一串由长长的数字组成的电话号码通常很难记忆。为了方便记忆，有种方法是用单词来方便记忆。例如用 `Three Tens` 来记忆电话 `3-10-10-10`。

电话号码的标准形式是七位数字，中间用连字号分成前三个和后四个数字（例如：`888-1200`）。电话号码可以用字母来表示。以下是字母与数字的对应：

 - `A`，`B` 和 `C` 对应 `2`；
 - `D`，`E` 和 `F` 对应 `3`；
 - `G`，`H` 和 `I` 对应 `4`；
 - `J`，`K` 和 `L` 对应 `5`；
 - `M`，`N` 和 `O` 对应 `6`；
 - `P`，`R` 和 `S` 对应 `7`；
 - `T`，`U` 和 `V` 对应 `8`；
 - `W`，`X` 和 `Y` 对应 `9`。

你会发现其中没有字母 `Q` 和 `Z`。电话中的连字号是可以忽略。例如 `TUT-GLOP` 的标准形式是 `888-4567`，`310-GINO` 的标准形式是 `310-4466`，`3-10-10-10` 的标准形式是 `310-1010`。

如果两个电话号码的标准形式是一样的，那么这两个电话号码就是一样的。

现在有一本电话簿，请从中找出哪些电话号码是重复的。

## 输入格式

第一行一个正整数 $N$，表示有多少个电话号码。

以下 $N$ 行，每行一个电话号码，电话号码由数字、大写字母（除 `Q`、`Z`）和连字符组成。电话号码长度不会超过 $1000$。所有电话号码都合法。

## 输出格式

将所有重复的电话号码按字典序以标准形式输出，并且在每个电话号码后跟一个整数，表示该电话号码共出现了多少次，电话号码和整数间用一个空格隔开。不要输出多余空行。

如果没有重复的电话号码，则输出：`No duplicates.`（注意最后一个字母 `s` 有一个点。）

## 样例

### 样例输入 #1
```
3

TUT-GLOP

3-10-10-10

310-1010


```
### 样例输出 #1
```
310-1010 2
```
## 提示

【数据范围】

对于 $30\%$ 的数据，$N\le20$。

对于 $50\%$ 的数据，$N\le10000$。

对于 $100\%$ 的数据，$N\le10^5$。



---

---
title: "二进制"
layout: "post"
diff: 普及/提高-
pid: P2104
tag: ['模拟', '字符串', '离散化']
---
# 二进制
## 题目描述

小 Z 最近学会了二进制数，他觉得太小的二进制数太没意思，于是他想对一个巨大二进制数做以下 $4$ 种基础运算：

运算 $1$：将整个二进制数加 $1$。

运算 $2$：将整个二进制数减 $1$。

运算 $3$：将整个二进制数乘 $2$。

运算 $4$：将整个二进制数整除 $2$。

小 Z 很想知道运算后的结果，他只好向你求助。

（Ps：为了简化问题，数据保证 `+`，`-` 操作不会导致最高位的进位与退位）
## 输入格式

第一行两个正整数 $n,m$，表示原二进制数的长度以及运算数。

接下来一行 $n$ 个字符，分别为 `0` 或 `1` 表示这个二进制数。

第三行 $m$ 个字符，分别为 `+`，`-`，`*`，`/`，对应运算 $1,2,3,4$。
## 输出格式

一行若干个字符，表示经过运算后的二进制数。

## 样例

### 样例输入 #1
```
4 10
1101
*/-*-*-/*/
```
### 样例输出 #1
```
10110
```
## 提示


对于 $30\%$ 的数据，$1 \leq n,m \leq 1000$。

对于 $60\%$ 的数据，$1 \leq n,m \leq 10^5$。

对于 $100\%$ 的数据，$1 \leq n,m \leq 5 \times 10^6$。


---

---
title: "小Z的关系距离"
layout: "post"
diff: 普及/提高-
pid: P2138
tag: ['模拟', '字符串', '动态规划 DP']
---
# 小Z的关系距离
## 题目描述

小 Z 学习了辩证唯物主义，知道了联系具有普遍性。他看着草稿纸上的字符串，就想挖掘它们之间的关系。

小 Z 认为，对于两个字符串 $a,b$，如果它们各自删除不超过其自身长度一半的字符能够相等，则称 $a,b$ 有距离为 $1$ 的关系。而如果存在另一个字符串 $c$，它和 $a$ 有距离为 $1$ 的关系，和 $b$ 有距离为 $n$ 的关系，则称 $a,b$ 有距离为 $n + 1$ 的关系。

现在小 Z 随机挑选出了两个小写字母字符串 $a,b$，想知道它们之间关系的最小距离，希望你帮帮他。
## 输入格式

第一行包含一个字符串 $a$。

第二行包含一个字符串 $b$。
## 输出格式

第一行包含一个整数，表示 $a,b$ 之间关系的最小距离。

## 样例

### 样例输入 #1
```
abcdef
axcyd
```
### 样例输出 #1
```
1
```
### 样例输入 #2
```
a
b
```
### 样例输出 #2
```
2
```
### 样例输入 #3
```
abb
baa
```
### 样例输出 #3
```
2
```
## 提示

对于 $30\%$ 的数据，$a,b$ 由同一字母构成。

对于 $100\%$ 的数据，$1 \leq |a|,|b| \leq 100$。


---

---
title: "一中校运会之百米跑"
layout: "post"
diff: 普及/提高-
pid: P2256
tag: ['字符串', '并查集']
---
# 一中校运会之百米跑
## 题目背景

在一大堆秀恩爱的 \*\* 之中，来不及秀恩爱的苏大学神踏着坚定（？）的步伐走向了 $100$ 米跑的起点。这时苏大学神发现，百米赛跑的参赛同学实在是太多了，连体育老师也忙不过来。这时体育老师发现了身为体育委员的苏大学神，便来找他帮忙。

可是苏大学神需要热身，不然跑到一半就会抽（筋）、于是他就找到了你。。。如果你帮助体育老师解决了问题，老师就会给你 $5$ 个积分。
## 题目描述

假设一共有 $N$（$2\leq N\leq 2\times 10^4$）个参赛选手。（尼玛全校学生都没这么多吧）

老师会告诉你这 $N$ 个选手的名字。

接着会告诉你 $M$（$1\leq M\leq 10^6$）句话，即告诉你学生 A 与学生 B 在同一个组里。

如果学生 A 与学生 B 在同一组里，学生 B 与学生 C 也在同一组里，就说明学生 A 与学生 C 在同一组。

然后老师会问你 $K$（$1\leq K\leq 10^6$）句话，即学生 X 和学生 Y 是否在同一组里。

若是则输出 `Yes.`，否则输出 `No.`。
## 输入格式

第一行输入 $N$ 和 $M$。

接下来 $N$ 行输入每一个同学的名字。

再往下 $M$ 行每行输入两个名字，且保证这两个名字都在上面的 $N$ 行中出现过，表示这两个参赛选手在同一个组里。

再来输入 $K$。

接下来输入 $K$ 个体育老师的询问。
## 输出格式

对于每一个体育老师的询问，输出 `Yes.` 或 `No.`。
## 样例

### 样例输入 #1
```
10 6
Jack
Mike
ASDA
Michel
brabrabra
HeHe
HeHE
papapa
HeY
Obama
Jack Obama
HeHe HeHE
brabrabra HeHe
Obama ASDA
papapa Obama
Obama HeHE
3
Mike Obama
HeHE Jack
papapa brabrabra

```
### 样例输出 #1
```
No.
Yes.
Yes.

```


---

---
title: "情书"
layout: "post"
diff: 普及/提高-
pid: P2264
tag: ['字符串']
---
# 情书
## 题目背景

一封好的情书需要撰写人全身心的投入。CYY同学看上了可爱的c**想对她表白，但却不知道自己写的情书是否能感动她，现在他带着情书请你来帮助他。


## 题目描述

为了帮助CYY，我们定义一个量化情书好坏的标准感动值。判断感动值的方法如下:

1. 在情书的一句话中若含有给定词汇列表中的特定单词，则感动值加1，但每一单词在同一句话中出现多次感动值不叠加，不同单词不受影响。保证输入的单词不重复。
2. 每句话以英文句号定界。
3. 全文不区分大小写。

## 输入格式

第一行包含一个数字n，表示导致感动值提升的词汇列表中单词的数量，随后n行是给定单词，每行一个。保证单词只包含英文字母。

最后一行为情书正文，保证只包含以下几种字符: 英文字母、数字、空格、英文逗号、英文句号。

## 输出格式

一个数字g，表示情书带来的感动值。

## 样例

### 样例输入 #1
```
3
love
so
much
I love you so much.

```
### 样例输出 #1
```
3
```
## 提示

对于所有的数据，保证1 ≤ n ≤ 100，每个单词不超过50字符，全文不超过1000字符。



---

---
title: "yyy2015c01 的 IDE 之 Watches"
layout: "post"
diff: 普及/提高-
pid: P2366
tag: ['模拟', '字符串', '洛谷原创']
---
# yyy2015c01 的 IDE 之 Watches
## 题目背景

在 2020 年的某一天，我们的 yyy2015c01 同学想要开发一套 IDE。
## 题目描述

作为他开发团队中的一员，你不幸地被选入了 Debugger 的开发组。

yyy2015c01 设想的 Debugger 由几部分组成，其中的一个小组件就是 Watches——中文称之为“变量观察器”。

由于 IDE 目前还是内测版，开发组需要先编一个能观察 int 类型变量值的 Watches 来看看效果如何。这个任务交由你来完成。

开发组假想的 Watches 能实现如下 3 种语句运行后监测相应变量值的功能：
- `n=1;` 将常量赋给变量，保证这个常量的位数不大于 $9$。
- `a=b;` 变量之间赋值：若原变量（在本例中是 $b$）未被赋值则认为其初始值为 $0$。
- `m=1+2;` $A+B$ 表达式赋值，只有 `+` 且只有两个数或者变量，$A$ 和 $B$ 都介于 $1$ 至 $10^6$ 之间。

请你编写一个 Watches，并在所有语句运行完后对所有被赋值过的变量按标识符的字典序输出它们的值（保证不会有变量的值大于 int 的最大值）。

## 输入格式

输入共 $n+1$ 行。

第一行是一个正整数 $n$，表示共有 $n$ 条赋值语句；

第二行到第 $n+1$ 行，每行是一条赋值语句（格式为“变量名=赋值式子;”），保证不会有多余的其他字符。
## 输出格式

输出共 $n$ 行：每行是一个被赋值过的变量标识符及它的值。
## 样例

### 样例输入 #1
```
3
a=233;
b=a;
c=a+b;
```
### 样例输出 #1
```
a 233
b 233
c 466
```
### 样例输入 #2
```
3
a=233;
b=1+1;
a=b;
```
### 样例输出 #2
```
a 2
b 2
```
## 提示

数据很弱，直接模拟过哟~

（别想着变量标识符只有一位哟！）

另：向本题主人公 yyy2015c01 同学致敬！


---

---
title: "查单词"
layout: "post"
diff: 普及/提高-
pid: P2412
tag: ['字符串', '搜索', '线段树', '洛谷原创']
---
# 查单词
## 题目背景

滚粗了的 HansBug 在收拾旧英语书，然而他发现了什么奇妙的东西。

## 题目描述

蒟蒻 HansBug 在一本英语书里面找到了一个单词表，包含 $N$ 个单词（每个单词内包含大小写字母）。现在他想要找出某一段连续的单词内字典序最大的单词。

## 输入格式

第一行包含两个正整数 $N, M$，分别表示单词个数和询问个数。

接下来 $N$ 行每行包含一个字符串，仅包含大小写字母，长度不超过 $15$，表示一个单词。单词**大小写不敏感**。

再接下来 $M$ 行每行包含两个整数 $x, y$，表示查询求从第 $x$ 到第 $y$ 个单词中字典序最大的单词。如果有两个单词忽略大小写情况下字典序相同，**输出靠后的那个**。
## 输出格式

输出包含 $M$ 行，每行为一个字符串，分别依次对应 $M$ 个询问的结果。

## 样例

### 样例输入 #1
```
5 5
absi
hansbug
lzn
kkk
yyy
1 5
1 1
1 2
2 3
4 4
```
### 样例输出 #1
```
yyy
absi
hansbug
lzn
kkk

```
## 提示

### 样例说明

第一次操作：在{absi,hansbug,lzn,kkk,yyy}中找出字典序最大的，故为yyy

第二次操作：在{absi}中找出字典序最大的，故为absi

第三次操作：在{absi,hansbug}中找出字典序最大的，故为hansbug

第四次操作：在{hansbug,lzn}中找出字典序最大的，故为lzn

第五次操作：在{kkk}中找出字典序最大的，故为kkk

### 数据规模

 ![](https://cdn.luogu.com.cn/upload/pic/2274.png) 



---

---
title: "[AHOI2004] 奇怪的字符串"
layout: "post"
diff: 普及/提高-
pid: P2543
tag: ['字符串', '2004', '各省省选', '安徽']
---
# [AHOI2004] 奇怪的字符串
## 题目描述

![](https://cdn.luogu.com.cn/upload/pic/1654.png)

## 输入格式

输入文件中包含两个字符串X和Y。当中两字符串非0即1。序列长度均小于9999。

## 输出格式

X和Y的最长公共子序列长度。

## 样例

### 样例输入 #1
```
01010101010 00000011111
```
### 样例输出 #1
```
6
```
### 样例输入 #2
```
01011 010010101111111111
```
### 样例输出 #2
```
5
```


---

---
title: "于是他错误的点名开始了"
layout: "post"
diff: 普及/提高-
pid: P2580
tag: ['字符串', '搜索', '字典树 Trie']
---
# 于是他错误的点名开始了
## 题目背景

XS中学化学竞赛组教练是一个酷爱炉石的人。

他会一边搓炉石一边点名以至于有一天他连续点到了某个同学两次，然后正好被路过的校长发现了然后就是一顿欧拉欧拉欧拉（详情请见已结束比赛 CON900）。
## 题目描述

这之后校长任命你为特派探员，每天记录他的点名。校长会提供化学竞赛学生的人数和名单，而你需要告诉校长他有没有点错名。（为什么不直接不让他玩炉石。）
## 输入格式

第一行一个整数 $n$，表示班上人数。

接下来 $n$ 行，每行一个字符串表示其名字（互不相同，且只含小写字母，长度不超过 $50$）。

第 $n+2$ 行一个整数 $m$，表示教练报的名字个数。

接下来 $m$ 行，每行一个字符串表示教练报的名字（只含小写字母，且长度不超过 $50$）。
## 输出格式

对于每个教练报的名字，输出一行。

如果该名字正确且是第一次出现，输出 `OK`，如果该名字错误，输出 `WRONG`，如果该名字正确但不是第一次出现，输出 `REPEAT`。
## 样例

### 样例输入 #1
```
5  
a
b
c
ad
acd
3
a
a
e

```
### 样例输出 #1
```
OK
REPEAT
WRONG

```
## 提示

- 对于 $40\%$ 的数据，$n\le 1000$，$m\le 2000$。
- 对于 $70\%$ 的数据，$n\le 10^4$，$m\le 2\times 10^4$。
- 对于 $100\%$ 的数据，$n\le 10^4$，$m≤10^5$。

---

$\text{upd 2022.7.30}$：新增加一组 Hack 数据。


---

---
title: "编辑距离"
layout: "post"
diff: 普及/提高-
pid: P2758
tag: ['字符串', '动态规划 DP', '数学']
---
# 编辑距离
## 题目描述

设 $A$ 和 $B$ 是两个字符串。我们要用最少的字符操作次数，将字符串 $A$ 转换为字符串 $B$。这里所说的字符操作共有三种：

1. 删除一个字符；
2. 插入一个字符；
3. 将一个字符改为另一个字符。

$A, B$ 均只包含小写字母。

## 输入格式

第一行为字符串 $A$；第二行为字符串 $B$；字符串 $A, B$ 的长度均小于 $2000$。

## 输出格式

只有一个正整数，为最少字符操作次数。

## 样例

### 样例输入 #1
```
sfdqxbw
gfdgw

```
### 样例输出 #1
```
4

```
## 提示

对于 $100 \%$ 的数据，$1 \le |A|, |B| \le 2000$。


---

---
title: "[USACO16JAN] Build Gates S"
layout: "post"
diff: 普及/提高-
pid: P2771
tag: ['模拟', '字符串', '搜索', '2016', 'USACO']
---
# [USACO16JAN] Build Gates S
## 题目描述

FarmerJohn 打算在他农场的一部分，建设一个围栏。但是因为没有认真做事，建造完成后，围栏变成一个很奇怪的形状。

具体来说，FJ 从 $(0,0)$ 出发，走了 $N$ 步，每步移动一单位（向东、向南、向西或向北）。

他走过的每一步，都会留下一段单位长度的围栏。例如，如果他的第一步向北，他建造一单位从 $(0,0)$ 到 $(0,1)$ 的围栏。

FJ 可能重复到达点多次，他也可能重复建造一段围栏多次。如果他的路径穿过一段已经建成的围栏，他的围栏也有可能会有交叉。

不用说，FJ 看到完成的围栏时，一定很沮丧。特别的，他发现一些区域被围栏封闭起来，从而无法到达。FJ 想在围栏上，安装一些门来解决这个问题。

门可以安装在任意一段单位长度（注：必须是之前走过的某一步）的围栏上，从而可以穿越这段围栏的两侧。

请计算 FJ 最少需要安装多少个门，才能保证农场上任意区域到任意区域都可到达。
## 输入格式

第一行一个整数 $N$。

第二行包含一个长度为 $N$ 的字符串，描述 FJ 的路径。每个字符为 $\tt N$（北），$\tt E$（东），$\tt S$（南），或 $\tt W$（西）。
## 输出格式

输出一个整数，表示为了保证农场所有区域的连通性，FJ 最少需要安装多少个门。
## 样例

### 样例输入 #1
```
14
NNNESWWWSSEEEE
```
### 样例输出 #1
```
2
```
## 提示

注意，如果农场初始连通，答案就是 $0$。

### 数据范围

$1\le n\le 1000$。



---

---
title: "英语1（eng1）- 英语作文"
layout: "post"
diff: 普及/提高-
pid: P2786
tag: ['字符串', '树形数据结构', '平衡树', '洛谷原创']
---
# 英语1（eng1）- 英语作文
## 题目背景

蒟蒻 HansBug 在英语考场上，挠了无数次的头，可脑子里还是一片空白。
## 题目描述

眼下出现在 HansBug 蒟蒻面前的是一篇英语作文，然而智商捉急的 HansBug 已经草草写完了，此时他发现离考试结束还有 $40$ 分钟，于是他打算估计一下这篇共有 $M$ 个单词的英语作文的含金量如何。众所周知的是，在中高考英语作文中使用高级词汇可以有效提高文章的含金量，从而获得更好的分数。已知蒟蒻HansBug知道 $N$ 个高级词汇，该词汇为 $A_i$（词汇长度为 $L_i$ ，包含数字、大小写字母），该高级词汇的含金量为 $B_i$，则该高级词汇每出现一次便可增加 $B_i$ 的含金量。可是他脑细胞和 RP 已经消耗殆尽，所以这个伟大的任务就交给你啦！
## 输入格式

第一行包含两个整数 $N$ 和 $P$ ， $N$ 表示HansBug共知道的高级词汇个数， $P$ 为模数

第 $2-N+1$行，每行包含一个单词 $A_i$ （长度为Li）和一个整数 $B_i$ ，其中 $B_i(0<B_i\le 10^5)$ 表示该单词的含金量

接下来直到输入结束的若干行为一篇英语作文，其中包含共计 $M$ 个单词，以及若干的分隔符（分隔符包含且仅包含`,`、`.`、`!`、`?`）
## 输出格式

一行，包含一个整数，为该文章的总含金量对 $P$ 的模。
## 样例

### 样例输入 #1
```
5 99
hansbug 1
kkksc03 2
yyy 3
absi2011 4
lzn 100
hansbug is a juruo!but absi2011 not.!?!
one day absi2011 laughed at yyy and hansbug.
then kkksc03 and lzn blamed him for that.

```
### 样例输出 #1
```
16
```
### 样例输入 #2
```
5 99
yyyy 1
kkksc03 2
yyy 3
absi2011 4
lzn 100
yyyy is a juruo!but absi2011 not.!?!
one day absi2011 laughed at yyy and yyyy.
then kkksc03 and lzn blamed him for that.

```
### 样例输出 #2
```
16
```
## 提示

样例 $1$ 中，共计出现了 $2$ 次`hansbug`、 $2$ 次`absi2011` 、 $1$ 次 `yyy` 、 $1$ 次`kkksc03`、 $1$ 次  `lzn` ，所以总含金量为 $1\times2+2\times4+3\times1+4\times1+100\times1=115$，对 $99$ 取模就是 $16$ 。

样例 $2$ 中，和样例 $1$ 基本一样，值得注意的是整体的 `yyyy` 不可以被认为是 `yyy` 出现 $2$ 次，请注意这是一篇英语作文，一切以单词为最小单位。

此题目中大小写敏感。

数据范围（设所有单词的最大长度为 $Lmax$ ）：

![](https://cdn.luogu.com.cn/upload/pic/2228.png)



---

---
title: "家谱"
layout: "post"
diff: 普及/提高-
pid: P2814
tag: ['字符串', '搜索', '图论', '线性数据结构', '并查集']
---
# 家谱
## 题目背景

现代的人对于本家族血统越来越感兴趣。

## 题目描述

给出充足的父子关系，请你编写程序找到某个人的最早的祖先。

## 输入格式

输入由多行组成，首先是一系列有关父子关系的描述，其中每一组父子关系中父亲只有一行，儿子可能有若干行，用 `#name` 的形式描写一组父子关系中的父亲的名字，用 `+name` 的形式描写一组父子关系中的儿子的名字；接下来用 `?name` 的形式表示要求该人的最早的祖先；最后用单独的一个 `$` 表示文件结束。
## 输出格式

按照输入文件的要求顺序，求出每一个要找祖先的人的祖先，格式为：本人的名字 $+$ 一个空格 $+$ 祖先的名字 $+$ 回车。
## 样例

### 样例输入 #1
```
#George
+Rodney
#Arthur
+Gareth
+Walter
#Gareth
+Edward
?Edward
?Walter
?Rodney
?Arthur
$
```
### 样例输出 #1
```
Edward Arthur
Walter Arthur
Rodney George
Arthur Arthur
```
## 提示

规定每个人的名字都有且只有 $6$ 个字符，而且首字母大写，且没有任意两个人的名字相同。最多可能有 $10^3$ 组父子关系，总人数最多可能达到 $5 \times 10^4$ 人，家谱中的记载不超过 $30$ 代。


---

---
title: "IPv6地址压缩"
layout: "post"
diff: 普及/提高-
pid: P2815
tag: ['模拟', '字符串']
---
# IPv6地址压缩
## 题目背景

（友情提示：IPv6 基础知识曾多次出现在 NOIP 初赛中）Internet Protocol，互联网协议，即为我们常说的 IP。我们目前常说的 IP 主要指它的第四版，即 IPv4，它由 IETF 于 1981 年发布。它的地址长度是 $32$ 个二进制位，因此也就有 $2^{32}$ 个 IP 地址可供使用，约为 $43$ 亿，在当时，谁也没有料想到 IPv4 如此庞大的地址长度会有用完的一天。

在 21 世纪的今天，互联网的蓬勃发展早就了我们如今便利的生活。当下，世界人口已超过 70 亿，计算机和各种联网设备已经走入千家万户，而不再仅是上个世纪 80 年代科学家们的工具。此时便出现了人们日益增长的联网设备需要同落后 IPv4 地址长度之间的矛盾。尽管可以通过网络地址翻译能技术来共享 IP 地址，临时解决枯竭的问题，但显然不是长久之计。

IETF 也有先见之明，早早地于 1998 年发布了 IPv6 协议，从微软 2006 年发布的 Windows Vista 开始成为默认安装的网络协议。作为 IPv4 的继任者，它的地址长度为 $128$ 个二进制位，也就是 $2^{128}$ 个IP地址可供使用。然而面对这冗长的地址，一位记忆力不好的网络工程师小明在配置路由表时遇到了许许多多多的困难，现在他找到了你，希望你帮忙编写一个程序来按照 IPv6 地址标准的格式压缩规则来压缩 IPv6 地址。
## 题目描述

**【IPv6 格式】**

IPv6 二进位制下为 $128$ 位长度，以 $16$ 位为一组，每组以冒号“`:`”隔开，可以分为 $8$ 组，每组以 $4$ 位十六进制方式表示。

比如 `2001:0db8:0000:0000:0123:4567:89ab:cdef` 是一个合法的 IPv6 地址。

同时 IPv6 地址在某些条件下可以压缩：

1. 每组数字代表的独立十六进制数可以省略前位的 `0`。

比如上面的 IPv6 地址可被压缩为 `2001:db8:0:0:123:4567:89ab:cdef`。

2. 可以用双冒号 `::` 表示一组 `0` 或多组连续的 `0`，但只能出现一次。

比如上面的 IPv6 地址可被压缩为 `2001:db8::123:4567:89ab:cdef`。

请你帮助记忆力不好的网络工程师小明解决他遇到的问题。

**【规则补充】**

1. 输入数据为完全展开的 IPv6 地址，确保输入的 IPv6 地址不含双冒号，每组地址省略的 `0` 都会被补充上去。

2. 双冒号只能使用一次，因此我们压缩最长的全 `0` 组。

比如 `2001:0db8:0000:0000:1:0000:0000:0000`，压缩为 `2001:db8:0:0:1::`，而非 `2001:db8::1:0:0:0`。

3. 双冒号只能使用一次，因此我们在我们遇到地址中多个连续全 `0` 组长度相同时，我们压缩最前面的一个。

比如 `2001:0db8:0000:0000:ffff:0000:0000:1`，压缩为 `2001:db8::ffff:0:0:1`，而非 `2001:db8:0:0:ffff::1`。

4. 输入的 IPv6 地址可能无法被压缩，此时请照原样输出。

提示：本题所示的压缩规则与 macOS (Darwin) 默认的 IPv6 地址显示方式相同，而 Windows 和 Linux 只遇到一组全 `0` 时不会使用 `::` 进行压缩。但用此方法压缩过的 IPv6 地址一样可以被 Windows 和 Linux 正确识别。

比如 `2001:0db8:ffff:0000:0123:4567:89ab:cdef`，Darwin 压缩为 `2001:db8:ffff::123:4567:89ab:cdef`，而 Linux 和 Windows 压缩为 `2001:db8:ffff:0:123:4567:89ab:cdef`。
## 输入格式

一串 $39$ 个字符的字符串，代表一个完全展开的 IPv6 地址。
## 输出格式

一串压缩后的 IPv6 地址。
## 样例

### 样例输入 #1
```
2406:0840:f990:0000:0000:0000:0000:0001
```
### 样例输出 #1
```
2406:840:f990::1
```
### 样例输入 #2
```
2a13:1801:018a:00cf:0100:0000:0000:0000
```
### 样例输出 #2
```
2a13:1801:18a:cf:100::
```
### 样例输入 #3
```
2001:4860:4860:0000:0000:0000:0000:8888
```
### 样例输出 #3
```
2001:4860:4860::8888
```
### 样例输入 #4
```
2001:0db8:0000:0000:0000:0000:0000:0001
```
### 样例输出 #4
```
2001:db8::1
```
### 样例输入 #5
```
0000:0000:0000:0000:0000:0000:0000:0000
```
### 样例输出 #5
```
::
```
### 样例输入 #6
```
0000:0000:0000:0000:0000:0000:0000:0001
```
### 样例输出 #6
```
::1
```
### 样例输入 #7
```
2001:0db8:ffff:0000:0123:4567:89ab:cdef
```
### 样例输出 #7
```
2001:db8:ffff::123:4567:89ab:cdef
```
### 样例输入 #8
```
1234:5678:9abc:def0:1234:5678:9abc:def0
```
### 样例输出 #8
```
1234:5678:9abc:def0:1234:5678:9abc:def0
```
### 样例输入 #9
```
0001:0000:0000:0000:0000:0000:0000:0001
```
### 样例输出 #9
```
1::1
```
### 样例输入 #10
```
0000:0000:0000:0000:0000:0000:0001:0002
```
### 样例输出 #10
```
::1:2
```


---

---
title: "[USACO11FEB] Best Parenthesis S"
layout: "post"
diff: 普及/提高-
pid: P3015
tag: ['模拟', '字符串', '2011', 'USACO', '栈']
---
# [USACO11FEB] Best Parenthesis S
## 题目描述

Recently, the cows have been competing with strings of balanced parentheses and comparing them with each other to see who has the best one.

Such strings are scored as follows (all strings are balanced): the string '()' has score 1; if 'A' has score s(A) then '(A)' has score 2\*s(A); and if 'A' and 'B' have scores s(A) and s(B), respectively, then 'AB' has score s(A)+s(B). For example, s('(())()') = s('(())')+s('()') = 2\*s('()')+1 = 2\*1+1 = 3.

Bessie wants to beat all of her fellow cows, so she needs to calculate the score of some strings. Given a string of balanced parentheses of length N (2 <= N <= 100,000), help Bessie compute its score.

给定一个只包含左右括号的字符串，得分规则如下：

如果一对括号内没有括号，那么这对括号的得分为1；如果两对括号互不包含（即并列存在），那这两对括号的得分相加；如果括号内包含一对括号，那么这个括号的得分纪为内部括号序列的得分\*2。

例如：对于这样一个字符串："() ()"，两对括号并列存在，则得分为1+1=2;

而对于这样一个字符串："(())"，最外层的括号内层包含一对括号，则得分为2\*1=2.


Bessie想击败所有同事的牛，所以她需要计算某个字符串的评分。给定一个长度为n、只包含括号的字符串（2≤N≤100000），计算其得分帮助Bessie。

## 输入格式

\* Line 1: A single integer: N

\* Lines 2..N + 1: Line i+1 will contain 1 integer: 0 if the ith character of the string is '(',  and 1 if the ith character of the string is ')'

## 输出格式

\* Line 1: The score of the string. Since this number can get quite large, output the  score modulo 12345678910.

## 样例

### 样例输入 #1
```
6 
0 
0 
1 
1 
0 
1 

```
### 样例输出 #1
```
3 

```
## 提示

This corresponds to the string "(())()". 

As discussed above.

输出答案要mod12345678910



---

---
title: "[USACO1.2] 命名那个数字 Name That Number"
layout: "post"
diff: 普及/提高-
pid: P3864
tag: ['模拟', '字符串', '搜索', 'USACO', '枚举', '深度优先搜索 DFS']
---
# [USACO1.2] 命名那个数字 Name That Number
## 题目描述

在威斯康辛州牛守志大农场经营者之中，都习惯于请会计部门用连续数字给母牛打上烙印。但是,母牛本身并没感到这个系统的便利,它们更喜欢用它们喜欢的名字来呼叫它们的同伴，而不是用像这个的语句"C'mon, #4364, get along."。请写一个程序来帮助可怜的牧牛工将一只母牛的烙印编号翻译成一个可能的名字。因为母牛们现在都有手机了，使用标准的按键的排布来把将数目翻译为文字:( 除了 "Q" 和 "Z")

```
2: A,B,C     5: J,K,L    8: T,U,V
3: D,E,F     6: M,N,O    9: W,X,Y
4: G,H,I     7: P,R,S
```
可接受的名字都被放在这样一个叫作"dict.txt" 的文件中，它包含一连串的少于 5,000个（准确地说是4617个）可被接受的牛的名字。 (所有的名字都是大写的且已按字典序排列) 请读入母牛的编号并返回那些能从编号翻译出来并且在字典中的名字。举例来说,编号 4734 能产生的下列各项名字: GPDG GPDH GPDI GPEG GPEH GPEI GPFG GPFH GPFI GRDG GRDH GRDI GREG GREH GREI GRFG GRFH GRFI GSDG GSDH GSDI GSEG GSEH GSEI GSFG GSFH GSFI HPDG HPDH HPDI HPEG HPEH HPEI HPFG HPFH HPFI HRDG HRDH HRDI HREG HREH HREI HRFG HRFH HRFI HSDG HSDH HSDI HSEG HSEH HSEI HSFG HSFH HSFI IPDG IPDH IPDI IPEG IPEH IPEI IPFG IPFH IPFI IRDG IRDH IRDI IREG IREH IREI IRFG IRFH IRFI ISDG ISDH ISDI ISEG ISEH ISEI ISFG ISFH ISFI 碰巧，81个中只有一个"GREG"是有效的(在字典中)。

写一个程序来对给出的编号打印出所有的有效名字，如果没有则输出NONE。编号可能有12位数字。

## 输入格式

第一行一行包含一个编号(长度可能从1到12)。

接下来4617行，每行一个字符串表示可以被接受的名字
## 输出格式

(file namenum.out)

以字典顺序输出一个有效名字的不重复列表，一行一个名字。 如果没有有效名字，输出'NONE'。 //注释：似乎数字只有8^4种排列（1与0不能用）

## 样例

### 样例输入 #1
```
4734
NMSL
GREG
LSDC
....(太多了不写了)
```
### 样例输出 #1
```
GREG

```


---

---
title: "[JLOI2008] 提示问题"
layout: "post"
diff: 普及/提高-
pid: P3880
tag: ['模拟', '字符串', '2008', '各省省选', '吉林']
---
# [JLOI2008] 提示问题
## 题目描述

最近在 JLOI 网上的一个流行游戏中，选手要回答很难的问题。假如在规定时间内不能回答，系统将给出 $1$ 个提示，之后再依次给出第 $2,3$ 个提示。出现在答案中的是字母和下列字符：

$\verb|. , : ; ! ? - |$ 和空格（空格不会在开头和结尾出现）。

字母是指：小写字母 $\verb!a! \cdots \verb!z!$ 大写字母 $\verb!A! \cdots \verb!Z!$，其中 a e i o u A E I O U 是元音字母。

生成提示的规则：

- 第 $1$ 个提示：简单的将所有字母换成 $\verb!.!$ 即可；
- 第 $2$ 个提示：从第 $1$ 个提示而来，将所有字母的个数求出，再将总个数除以三，得到的最接近商的自然数 $N$，将第 $1$ 个提示中的前 $N$ 个字母显示；
- 第 $3$ 个提示：从第 $2$ 个提示而来，将剩下的元音字母显示。假如没有可显示的元音字母，则从第 $1$ 个提示而来，即我们将前 $2/3$ 的字母显示（同样如不能被 $3$ 整除则取最接近的整数）。
## 输入格式

仅一行，给出问题，问题字符数最多不超过 $50$。

## 输出格式

三行：按规则输出的三行提示。

## 样例

### 样例输入 #1
```
Upomoc! Lpv s nm pkrl sv smglsnk.
```
### 样例输出 #1
```
......! ... . .. .... .. ........ 
Upomoc! Lp. . .. .... .. ........ 
Upomoc! Lpv s nm pkrl s. ........

```


---

---
title: "[CERC2015] ASCII Addition"
layout: "post"
diff: 普及/提高-
pid: P4346
tag: ['模拟', '字符串', '2015', '枚举']
---
# [CERC2015] ASCII Addition
## 题目背景

Nowadays, there are smartphone applications that instantly translate text and even solve math problems if you just point your phone’s camera at them. Your job is to implement a much simpler functionality reminiscent of the past – add two integers written down as ASCII art.
## 题目描述

An ASCII art is a matrix of characters, exactly 7 rows high, with each individual character either a dot or the lowercase letter x.

An expression of the form a + b is given, where both a and b are positive integers. The expression is converted into ASCII art by writing all the expression characters (the digits of a and b as well as the + sign) as 7  5 matrices, and concatenating the matrices together with a single column of dot characters between consecutive individual matrices. The exact matrices corresponding to the digits and the + sign are as follows:

![](https://cdn.luogu.com.cn/upload/pic/16222.png )

Given an ASCII art for an expression of the form a + b, find the result of the addition and write it out in the ASCII art form.
## 输入格式

Input consists of exactly 7 lines and contains the ASCII art for an expression of the form a + b, where
both a and b are positive integers consisting of at most 9 decimal digits and written without leading
zeros.
## 输出格式

Output 7 lines containing ASCII art corresponding to the result of the addition, without leading zeros.
## 样例

### 样例输入 #1
```
....x.xxxxx.xxxxx.x...x.xxxxx.xxxxx.xxxxx.......xxxxx.xxxxx.xxxxx
....x.....x.....x.x...x.x.....x.........x...x...x...x.x...x.x...x
....x.....x.....x.x...x.x.....x.........x...x...x...x.x...x.x...x
....x.xxxxx.xxxxx.xxxxx.xxxxx.xxxxx.....x.xxxxx.xxxxx.xxxxx.x...x
....x.x.........x.....x.....x.x...x.....x...x...x...x.....x.x...x
....x.x.........x.....x.....x.x...x.....x...x...x...x.....x.x...x
....x.xxxxx.xxxxx.....x.xxxxx.xxxxx.....x.......xxxxx.xxxxx.xxxxx
```
### 样例输出 #1
```
....x.xxxxx.xxxxx.xxxxx.x...x.xxxxx.xxxxx
....x.....x.....x.x.....x...x.x.........x
....x.....x.....x.x.....x...x.x.........x
....x.xxxxx.xxxxx.xxxxx.xxxxx.xxxxx.....x
....x.x.........x.....x.....x.....x.....x
....x.x.........x.....x.....x.....x.....x
....x.xxxxx.xxxxx.xxxxx.....x.xxxxx.....x
```
## 提示

样例：1234567+890=1235457

Central Europe Regional Contest 2015 Problem A
## 题目翻译

# 题目背景

现在，如果你只是用手机的相机对着它们，智能手机应用可以即时翻译文本，甚至解决数学问题。您的工作是实现一个更简单的功能，回忆过去——添加两个作为ASCII艺术的整数。

# 题目描述

ASCII艺术是一个字符矩阵，正好是7行高，每个字符都是点或小写字母X。

给出了A +B形式的表达式，其中A和B都是正整数。通过将所有的表达式字符（A和B的数字以及符号）作为7 5个矩阵，将这些矩阵转换成ASCII艺术，并将矩阵与单个字符的单个列串联在连续的各个矩阵之间。对应于数字和+符号的精确矩阵如下：

![](https://cdn.luogu.org/upload/pic/16222.png)

给定一个ASCII艺术来表达A+B的形式，找到加法的结果并用ASCII艺术形式写出。

# 输入输出格式

#### 输入格式：

输入由7行组成，包含用于A+B形式的表达式的ASCII技术，其中A和B都是由至多9个十进制数字组成的正整数，并且没有前导零。

#### 输出格式：

输出包含ASCII艺术的7行，对应于加法的结果，没有前导零。

感谢@剑圣夜雨声烦 提供的翻译


---

---
title: "Hillwer编码"
layout: "post"
diff: 普及/提高-
pid: P5000
tag: ['模拟', '字符串', '高精度']
---
# Hillwer编码
## 题目背景

在Z国的高科技研究中心，科研人员使用的都是最“先进”的Hillwer编码（毕竟这里可是国家机密库，储存着最重要的机密资料~~QwQ）。
## 题目描述

Z国的科技十分发达，一直是各国觊觎的目标，Y国就是其中之一。经过Y国黑客夜以继日的奋斗，终于获得了Z国**Hillwer**编码的转换方式，并且截获了n条原码。 BUT（总是有那么多但是~），Y国的黑客们呕心沥血研究**Hillwer**，都累得趴下了……所以，转换**Hillwer**编码的任务他们就无法完成。

Y国元首听说在遥远的东方国度，有一群才华横溢的少年——就是坐在电脑前的你们！元首希望你能够帮助Y国转换编码，他将赠予你**NOIP_AK荣耀桂冠**！

**Hillwer**编码的转换规则如下： 对于每一条原码$ S $，保证仅由26个大写字母组成。将每个字母后移R位，得到中转码$ S1 $（当$ S $=‘XYZ’,R=2时，$ S1 $=‘ZAB’。即变成当前字母后$ R $个字母，超过 ‘Z’则从‘A’开始）。接着，将中转码进行“符转数”操作，将$ S1 $每一位的ACS码（即ASCLL码）相乘，得到数串$ Q $。转换后的编码即为$ Q $。

元首为了检查你是不是偷懒，还要求你把中转码$ S1 $也输出。
## 输入格式

第1行，读入$ n $，$ R $。
第2~$ n $+1行，每行一条编码S。

## 输出格式

共$ n $*2行，
奇数行，每行一条中转码$ S1 $；
偶数行，每行一条转换后的编码$ Q $。
## 样例

### 样例输入 #1
```
2 6
HELLOWORLD
LETUSGO
```
### 样例输出 #1
```
NKRRUCUXRJ
10167740864629920000
RKZAYMU
20957073637500

```
## 提示

对于 $ 30\% $ 的数据，$ 1 \leq n \leq 10 ,1 \leq R \leq 10 $；

对于 $ 50\% $ 的数据，$ 1 \leq n \leq 500 ,1 \leq R \leq 10^3 $；

对于 $ 100\% $ 的数据，$ 1 \leq n \leq 500 ,1 \leq R \leq 10^5 $。

另外保证 原码长度小于600


---

---
title: "打字练习"
layout: "post"
diff: 普及/提高-
pid: P5587
tag: ['字符串', '洛谷月赛']
---
# 打字练习
## 题目描述

R 君在练习打字。

有这样一个打字练习网站，给定一个范文和输入框，会根据你的输入计算准确率和打字速度。可以输入的字符有小写字母、空格和 `.`（英文句号），输入字符后，光标也会跟着移动。

输入的文本有多行，R 君可以通过换行键来换行，换行后光标移动到下一行的开头。

R 君也可以按退格键（为了方便，退格键用 `<` 表示），以删除上一个打的字符，并将光标回移一格。特殊的，如果此时光标已经在一行的开头，则不能继续退格（即忽略此时输入的退格键）。

网站的比较方式遵循以下两个原则：

- 逐行比较，即对于范文和输入的每一行依次比较，不同行之间不会产生影响，多余的行会被忽略。
- 逐位比较，即对于两行的每一个字符依次比较，当且仅当字符相同时才会被算作一次正确，否则会被算作错误。计算答案时，只统计相同的字符个数。

需要注意的是，回车键不会被计入正确的字符个数。

R 君看到网站上显示他花了 $T$ 秒完成了这次的打字游戏，请你计算出他的 KPM（Keys per minutes，每分钟输入的字符个数），答案四舍五入保留整数部分。

## 输入格式

R 君会依次告诉你网站的范文，他的输入和花费的时间。

其中范文和输入将会这样读入：给定若干行字符串，以单独的一行 `EOF` 结束，其中 `EOF` 不算入输入的文本。

最后一行一个整数 $T$，表示他打字花费了 $T$ 秒。

可以参考样例输入输出文件和样例解释辅助理解。
## 输出格式

一行一个整数，表示 KPM。
## 样例

### 样例输入 #1
```
hello world.
aaabbbb
x
EOF
heelo world.
aaacbbbb
y<x
EOF
60
```
### 样例输出 #1
```
18
```
## 提示

#### 样例解释

第一行的正确字符数为 11。  
第二行的正确字符数为 6，错误的字符 `c` 仍会占据一个位置。  
第三行的正确字符数为 1，R 君使用退格键删除了被打错的字符 `y`

#### 数据范围

对于 $20\%$ 的数据，不存在换行键。  
对于 $40\%$ 的数据，不存在退格键。  
对于 $100\%$ 的数据，$T \leq 10^3$，保证每个文本段的总字符数（包括换行）不超过 $10^5$ 个且总行数不超过 $10^4$。



---

---
title: "[RC-02] 求和"
layout: "post"
diff: 普及/提高-
pid: P6051
tag: ['字符串']
---
# [RC-02] 求和
## 题目描述

小 Q 给你了几行字符串，字符串中间包含有一些整数，整数之间可能会有其他字符。你需要输出每行中所有整数的和。如果一个行里面一个数都没有则不要输出。**每两个整数之间一定有间隔字符（见样例 $3$）。**

请注意，题目中的整数都是简单的整数，即：整数前面没有多余的符号。假如数据中有 `.`，视作分隔符。
## 输入格式

每行一个字符串。
## 输出格式

对于每一个包含了整数的字符串，输出一行一个数，即其中数的和。
## 样例

### 样例输入 #1
```
su57jdkjth54hjsns-321d 8 ejre
erg(&-^%

weruy4uhnd-
```
### 样例输出 #1
```
-202
4
```
### 样例输入 #2
```
          4532984       d    -1
```
### 样例输出 #2
```
4532983
```
### 样例输入 #3
```
1-1
1 -1
1--5
1-----------1
-1-1
--1
-2.3
```
### 样例输出 #3
```
2
0
-4
0
0
-1
1
```
## 提示

【样例解释】

- 第一个样例中，第一行有 $57,54,-321,8$ 几个数，和为 $-202$；第二、三行没有数字；第四行只有一个 $4$，输出 $4$。
- 第二个样例中只有一行，有两个数，和为 $4532893$。
- 第三个样例的第一行，由于每两个整数之间一定有间隔字符，所以把 `-` 视为间隔字符，输出 $2$。第五行，第一个数为 $-1$，因此把第二个 `-` 视为间隔字符，和为 $-1+1=0$。第七行，将 `.` 视为间隔字符，和为 $-2+3=1$。

【数据范围】

说明：「条件 A」指数据中不存在除数字、空格、换行、水平制表符之外的其他字符；「条件 B」指每两个数之间一定用且只用一个空格隔开。

**由于数据在 Windows 下制造，行末可能有多余的 `\r` 字符。请注意。**

对于 $10\%$ 的数据，满足条件 A 和 B，每行一定有且仅有 $10$ 个数；

对于 $40\%$ 的数据，满足条件 A 和 B，且不存在空行；

对于 $50\%$ 的数据，满足条件 A 和 B；

对于 $70\%$ 的数据，满足条件 A；

对于 $100\%$ 的数据，不存在除水平制表符、空格、换行外的不可见字符，每行不超过 $1000$ 个字符，每行最多包含 $200$ 个整数，不超过 $100$ 行，每个整数均 $\in[-10^7,10^7]$。


---

---
title: "[NEERC 2016] Hard Refactoring"
layout: "post"
diff: 普及/提高-
pid: P6123
tag: ['字符串', '2016', 'ICPC']
---
# [NEERC 2016] Hard Refactoring
## 题目描述

对于一个变量 $x$，给出一些约束条件，形如 $x \geq a$，$x \le a$ 
这些约束条件之间用```||```连接，然后你需要将这些约束条件简化，最后输出简化后的约束条件。
## 输入格式

输入不超过 $10^3$ 行，每行要么是两个用 ```&&``` 连接的约束条件，要么就是单个的约束条件。

如果一行有两个约束条件，第一个约束条件总是 $x \geq a$ 的形式，第二个约束总是 $x \leq a$ 的形式。

除了输入的最后一行，每一行末尾都有一个 ```||```。

并且所有的字符（除了`>=`，`<=`，`&&`，`||`）之间均由空格隔开，且没有多余的前置、后置空格。
## 输出格式

输出若干行，表示最简的约束条件的形式（也就是使输出的行数尽量少），其余格式与输入格式保持一致。

输出的若干行可以不按照特定的顺序输出。

特别地，如果对于任意的 $x∈[-32768,32767]$，$x$均能满足约束条件，仅输出一行```true```，反之，若对于任意的 $x∈[-32768,32767]$，$x$均不能满足约束条件，仅输出一行```false```。
## 样例

### 样例输入 #1
```
x >= 5 && x <= 10 ||
x >= 7 && x <= 20 ||
x <= 2 ||
x >= 21 && x <= 25 ||
x >= 8 && x <= 10 ||
x >= 100
```
### 样例输出 #1
```
x <= 2 ||
x >= 5 && x <= 25 ||
x >= 100
```
## 提示

对于所有在这一题中出现的数字（包括 $x$），都$\ge -32768$（$-2^{15}$） 且 $\le 32767 $（$2^{15}-1$）。


---

---
title: "『MdOI R2』Mayuri"
layout: "post"
diff: 普及/提高-
pid: P6380
tag: ['字符串', '贪心', '洛谷月赛']
---
# 『MdOI R2』Mayuri
## 题目背景

「万由里……怎么会？为什么你要……」

『我是灵力的结晶体，实施了封印，我当然会消失，不是吗？』

「封印？但是你和我……」

『第一次见面不能封印吗？笨蛋，我可是从大家的灵力里出生的，怎么可能讨厌你？从一出生，我就爱着你。』

「万由里……」

『虽然我竭力不让自己去想，但我一定是很羡慕大家……』

「等一下，万由里，不要消失……」

『但是我还是有一件能向大家炫耀的事，只有我和士道一样……』

「一样？」

『我已经不再是只为了消失而出生的生命。因为我遇见了你……已经足够了。』

「万由里……」

『谢谢你，士道。 』

![](https://cdn.luogu.com.cn/upload/image_hosting/9w6a0deg.png)
## 题目描述

在离开这个世界前，万由里想要寻找属于她的 Lucky Number。

万由里会给出一个数 $a$，以及一个长度为 $b$ 的 01 串 $S$。

简单的说，她的 Lucky Number 是满足以下条件的**正整数** $n$：

 - $n$ 的位数为 $b$ 且不含前导 $0$。

 - 若 $S$ 的第 $i$ 位为 $1$，则 $n$ 的前 $i$ 位组成的数是 $a$ 的倍数，否则 $n$ 的前 $i$ 位组成的数不是 $a$ 的倍数。

对于一个数，前 $i$ 位组成的数是指这个数前 $i$ 个数码依次拼接形成的数。例如 $312311$ 前 $3$ 位组成的数为 $312$，前 $5$ 位组成的数为 $31231$。


现在，请你帮助万由里计算一下，她的 Lucky Number 是多少。

由于满足条件的数可能会有多个，你需要输出**最小**的一个。若不存在，则请输出 `-1`。
## 输入格式

输入数据由两行构成。

第一行两个整数 $a,b$，意义见题目描述。

第二行一个长度为 $b$ 的字符串 $S$。
## 输出格式

一行，满足条件的**最小**的数 $n$。如果不存在满足条件的数，输出 `-1`。
## 样例

### 样例输入 #1
```
2 2
01
```
### 样例输出 #1
```
10
```
### 样例输入 #2
```
10 1 
1
```
### 样例输出 #2
```
-1
```
### 样例输入 #3
```
6 6
110100
```
### 样例输出 #3
```
601210
```
## 提示

【帮助与提示】

为方便选手测试代码，本题额外提供一组附加样例供选手使用。

[样例输入](https://www.luogu.com.cn/paste/5gnn8mg0) [样例输出](https://www.luogu.com.cn/paste/sgxjkbjd)

------
【样例解释】

对于样例一，$10$ 是 $2$ 位数，且 $10$ 的前 $1$ 位组成的数 $1$ 不是 $2$ 的倍数，而前 $2$ 位组成的数 $10$ 是 $2$ 的倍数。由于 $10$ 已经是最小的两位数，故不存在比 $10$ 更小的满足条件的数。

对于样例二，我们需要构造一个 $1$ 位数，满足这个 $1$ 位数整除 $10$。显然，这样的数不存在。

---

【数据范围】

**本题采用捆绑测试**


| 子任务编号 | $a \leq$ | $b\le$  | 分值   |
| ---------- | -------- | :------ | ------ |
| Subtask 1  | $10$     | $ 1$    | $20$   |
| Subtask 2  | $10 $    | $2$     | $20$  |
| Subtask 3  | $10 $    | $ 6$    | $20$  |
| Subtask 4  | $ 2$     | $ 18$   | $20$ |
| Subtask 5  | $ 10$    | $ 10^5$ | $20$ |


对于全部数据，保证 $2\le a\le 10$，$1\le b\le 10^5$，$S$ 中只包含 `0` 和 `1`。


---

---
title: "[COCI 2009/2010 #2] RIMSKI"
layout: "post"
diff: 普及/提高-
pid: P7773
tag: ['模拟', '字符串', '2009', '枚举', '其它技巧', 'COCI（克罗地亚）']
---
# [COCI 2009/2010 #2] RIMSKI
## 题目背景

本题为[$\texttt{COCI 2009-2010}\ 2^\texttt{nd}\ \texttt{round}\ \text{T2 RIMSKI}$](https://hsin.hr/coci/archive/2009_2010/contest2_tasks.pdf)。

分值按原题设置，满分 $50$。
## 题目描述

给定一个罗马数字 $B$，把 $B$ 的字符重新排列，要求让排列后的数字最小。
## 输入格式

一行一个罗马数字 $B$。
## 输出格式

一行一个罗马数字，为你重排后能得到的最小的数字。
## 样例

### 样例输入 #1
```
VIII
```
### 样例输出 #1
```
VIII
```
### 样例输入 #2
```
VI
```
### 样例输出 #2
```
IV
```
### 样例输入 #3
```
III
```
### 样例输出 #3
```
III
```
### 样例输入 #4
```
LI
```
### 样例输出 #4
```
LI
```
## 提示

$1\leq B< 100$。

注意，在本题中`I`如果在大数字之前，它只能在`V` 、`X`之前。输入遵循同样的规则。（这就是样例 $4$ 的输出为什么是 `LI` 而不是 `IL`。）


---

---
title: "「小窝 R3」心の記憶"
layout: "post"
diff: 普及/提高-
pid: P7814
tag: ['字符串', '贪心', 'Special Judge', 'O2优化']
---
# 「小窝 R3」心の記憶
## 题目背景

> 淡い夕暮れ飲み込まれて  
「君」の消えかけて姿を  
忘れさせるように走ってた   
新しい平和の世界に  
——[《心の記憶》](https://music.163.com/song?id=1847928316)
## 题目描述

- 本题中「**子串**」的定义如下：

字符串 $S$ 的子串是 $S$ 中**连续**的任意个字符组成的字符串。$S$ 的子串可用起始位置 $l$ 与终止位置 $r$ 来表示，记为 $S(l,r)$（$1 \leq l \leq r \leq |S |,|S|$ 表示 $S$ 的长度）。

- 本题中「**子序列**」的定义如下：

对于字符串 $S$ 和一个长度为 $n$ 的严格单调递增数列 $k_1,k_2,\cdots,k_n(\forall 1\le i\le n,1\le k_i\le |S|)$，$S_{k_1},S_{k_2},\cdots,S_{k_n}$ 所组成的字符串即为 $S$ 的子序列。

---------------

现有 $T$ 次询问。
每次询问给定一个长度为 $n$ 的 01 串，记为 $A$。回答应是一个字符串 $B$，满足：

- $B$ 是长度为 $m$ 的 01 串。
- $B$ 中不存在任意一个**子串**与 $A$ 相同。
- $B$ 中存在**至少**一个**子序列**与 $A$ 相同。

输出任意一个满足要求的字符串 $B$ 即可。
## 输入格式

第一行，一个正整数：$T$，表示询问次数。

对于每一次询问，第一行两个正整数： $n,m(n\le m)$，分别表示 01 串 $A,B$ 的长度。

第二行，一个长度为 $n$ 的 01 串 $A$。
## 输出格式

共 $T$ 行，每行一个长度为 $m$ 的 01 串 $B$。无解则输出 `-1`。
## 样例

### 样例输入 #1
```
4
1 1
1
3 5
010
4 8
1101
5 6
11111
```
### 样例输出 #1
```
-1
01110
10100101
111101
```
## 提示

### 样例解释

在第二次询问中，`01101` 和 `10110` 是另外合法的方案。

### 数据范围

| Subtask | 分值 | $\sum m\le$ | 特殊性质 |
| :-----------: | :-----------: | :-----------: | :-----------: |
| $1$  | $10$ | $2\times10^6$ | $A$ 只由 `0` 组成 |
| $2$ | $10$ | $15$ | 无 |
| $3$ | $20$ | $2000$ | 无 |
| $4$  | $30$ | $10^6$ | $A$ 随机生成 |
| $5$ | $30$ | $2\times 10^6$ | 无 |

对于 $100\%$ 的数据，$1\le n\le m$，$1\le \sum m\le 2\times 10^6$。保证 $A$ 只由 `0` 和 `1` 组成。


---

---
title: "【模板】字典树"
layout: "post"
diff: 普及/提高-
pid: P8306
tag: ['字符串', 'O2优化', '字典树 Trie']
---
# 【模板】字典树
## 题目描述

给定 $n$ 个模式串 $s_1, s_2, \dots, s_n$ 和 $q$ 次询问，每次询问给定一个文本串 $t_i$，请回答 $s_1 \sim s_n$ 中有多少个字符串 $s_j$ 满足 $t_i$ 是 $s_j$ 的**前缀**。

一个字符串 $t$ 是 $s$ 的前缀当且仅当从 $s$ 的末尾删去若干个（可以为 0 个）连续的字符后与 $t$ 相同。

输入的字符串大小敏感。例如，字符串 `Fusu` 和字符串 `fusu` 不同。
## 输入格式

**本题单测试点内有多组测试数据**。  

输入的第一行是一个整数，表示数据组数 $T$。

对于每组数据，格式如下：  
第一行是两个整数，分别表示模式串的个数 $n$ 和询问的个数 $q$。  
接下来 $n$ 行，每行一个字符串，表示一个模式串。  
接下来 $q$ 行，每行一个字符串，表示一次询问。
## 输出格式

按照输入的顺序依次输出各测试数据的答案。  
对于每次询问，输出一行一个整数表示答案。
## 样例

### 样例输入 #1
```
3
3 3
fusufusu
fusu
anguei
fusu
anguei
kkksc
5 2
fusu
Fusu
AFakeFusu
afakefusu
fusuisnotfake
Fusu
fusu
1 1
998244353
9
```
### 样例输出 #1
```
2
1
0
1
2
1
```
## 提示

### 数据规模与约定

对于全部的测试点，保证 $1 \leq T, n, q\leq 10^5$，且输入字符串的总长度不超过 $3 \times 10^6$。输入的字符串只含大小写字母和数字，且不含空串。

### 说明
std 的 IO 使用的是关闭同步后的 cin/cout，本题不卡常。


---

---
title: "伟大的神"
layout: "post"
diff: 普及/提高-
pid: P8437
tag: ['字符串', '洛谷原创', 'Special Judge', 'O2优化', '构造', '洛谷月赛']
---
# 伟大的神
## 题目背景

伟大的神 $\text{T}\color{red}\text{nyieldingUrilobite}$ （以下简称 TU）喜欢字符串，在 AK 了 IOI 后的第 $998244353$ 天后，伟大的神 TU 勒令小 s 找出他喜欢的字符串。

否则，小 s 就要被吊打 $10^{998244353}$ 年。（虽然找出来了也要被吊打）
## 题目描述

伟大的神 TU 认为 ，一个所有出现的字符的数量相等的字符串是属于神的，他称之为神之字符串。

对于一个字符串 $S$，如果它的一个子串为神之字符串，即称这个子串为神之子串。

神 TU 认为，他喜欢的字符串只能由 `l` 和 `r` 构成，并且还要满足以下条件：

   - 字符串的长度为 $n$。
   - 字符串中最长神之子串长度为 $m$。
   - 字符串中连续的相同的字符的数量不能超过 $k$。

弱小的神小 s 找不出神 TU 喜欢的字符串，现在他找到了你，你能帮帮他吗？
## 输入格式

一行三个整数，分别为 $n,m,k$。

题目保证输入的 $m$ 是偶数。
## 输出格式

请输出任意一种神 TU 喜欢的字符串。

数据保证可以找出神 TU 喜欢的字符串。
## 样例

### 样例输入 #1
```
10 6 3
```
### 样例输出 #1
```
lllrrlrlll
```
## 提示

**本题采用捆绑测试。**

对于 $100\%$ 的数据，保证 $1\le k\le10^5$，$4\le m\le n \le 10^5$。

数据保证可以找出神 TU 喜欢的字符串。

Subtask 1：对于 $5\%$ 的数据，保证 $k=1$。

Subtask 2：对于另外 $10\%$ 的数据，保证 $n=m$。

Subtask 3：对于另外 $30\%$ 的数据，保证 $k \ge 3$。

Subtask 4：无特殊性质。




---

---
title: "[传智杯 #3 初赛] 终端"
layout: "post"
diff: 普及/提高-
pid: P8824
tag: ['字符串', '传智杯']
---
# [传智杯 #3 初赛] 终端
## 题目描述

有一天您厌烦了电脑上又丑又没用的终端，打算自己实现一个 Terminal。

具体来说，它需要支持如下命令:

1. `touch filename`：如果名为 `filename` 的文件不存在，就创建一个这样的文件，如果已经存在同名文件的话则不进行任何操作。

2. `rm name`：删除名为 `name` 的文件。如果不存在这样的文件，就不进行任何操作。

3. `ls`：按**创建时间为顺序**，显示当前已经存在的未被删除的所有文件。
4. `rename xxx yyy`：将名为`xxx`的文件名字改为 `yyy` 。如果不存在这样的文件，或者已经存在文件名为 `yyy` 的文件，则不做任何操作。

这里所有涉及的文件名都仅由大写或者小写的英文字母构成，且文件名区分大小写。
## 输入格式

第一行一个整数 $n$ ，表示总共要执行的操作数。

接下来 $n$ 行，每行一个字符串，表示一条命令。
## 输出格式

对于每个 `ls` 命令，请输出若干行，每行一个字符串，表示一个文件，如果当前并没有任何文件，则什么都不输出。

请注意本题时限为 3s，输入输出规模较大，请注意常数因素对耗时的影响，我们不会给使用 Java 和 Python 的选手增加额外的运行时间。
## 样例

### 样例输入 #1
```
6
touch yyh
touch yyhtql
rename yyh yyhnb
touch qwq
rename qwq qaq
ls
```
### 样例输出 #1
```
yyhnb
yyhtql
qaq
```
## 提示

对于 $20\%$ 的数据，只存在 $1,3$ 操作 

对于另外 $20\%$ 的数据，只存在 $1,2,3$ 操作

对于另外 $20\%$ 的数据，只存在 $1,3,4$ 操作

对于 $100\%$ 的数据，满足 $1 \leq n \leq 1000$

保证所有命令的长度不超过 $2000$ 个字符。


---

---
title: "[COCI 2022/2023 #2] Prijateljice"
layout: "post"
diff: 普及/提高-
pid: P9738
tag: ['字符串', '2022', 'COCI（克罗地亚）']
---
# [COCI 2022/2023 #2] Prijateljice
## 题目描述

Leona 和 Zoe 拿到了一些单词。他们打算用这些单词玩一个游戏：

在每一个回合中，两人轮流说单词。这个单词需要满足以下要求：

它比前一个单词的字典序大，且开头字母必须和前一个字母相同，或在字母表上正好在前一个单词的开头字母的后面一个。

Leona 先说，他会选择字典序最小的单词说出来。轮到谁时，他说不出单词了，他就输了。

两人在玩这个游戏时，都会采用最优策略，也就是说，选择符合条件的单词中字典序最小的那个。

现在他们想知道，谁会赢呢。
## 输入格式

第一行，两个整数 $n$，$m$（$1 \le n,m \le 10^5$）。

接下来 $n$ 行，每行一个字符串，表示 Leona 拥有的单词。

接下来 $m$ 行，每行一个字符串，表示 Zoe 拥有的单词。

输入的单词均为小写字母，且互不相同。它们的总长度不超过 $10^6$，且按字典序排序。

## 输出格式

输出一行，一个字符串，为 $\texttt{Leona}$ 或 $\texttt{Zoe}$，表示获胜者。
## 样例

### 样例输入 #1
```
2 1
avokado
dabar
brazil
```
### 样例输出 #1
```
Zoe
```
### 样例输入 #2
```
3 3
ananas
atlas
banana
albatros
cikla
nogomet

```
### 样例输出 #2
```
Leona
```
### 样例输入 #3
```
2 2
hrvatska
zastava
bijeli
galeb
```
### 样例输出 #3
```
Leona
```
## 提示

|$\text{Subtask}$|分值|特殊性质|
|:-:|:-:|:-:|
|$1$|$20$|$n,m\le100$，每个单词的长度不超过 $10$|
|$2$|$30$|$n,m\le1000$|
|$3$|$60$|无|

**本题满分 $110$ 分。**


---

