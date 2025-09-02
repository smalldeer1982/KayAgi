---
title: "YOKOH - The Best Name for Your Baby"
layout: "post"
diff: 难度0
pid: SP7581
tag: []
---

# YOKOH - The Best Name for Your Baby

## 题目描述

在某个遥远的未来，29XX 年，一个小国为了保护自己独特的文化，制定了一项新法律，规定人们只能使用传统的名字。为了限制名字的过度流行，法律还要求每个人的名字长度根据出生日期计算确定。自法律实施以来，给新生儿起名字时，父母们的共同任务就是找到给定长度下字典序最小的合法名字，因为在他们的文化中，字母顺序靠前的名字有很多好处。

合法的名字是通过反复应用一套规则集，从最初始的字符串「S」（仅包含单个大写字母 S）生成的纯小写字母的字符串。

应用规则集，即从规则集中选择一条规则并作用于字符串。每条规则的格式为 $A \rightarrow \alpha$，其中 $A$ 表示大写字母，$\alpha$ 是一个由大小写字母组成的字符串。应用规则就是将字符串中的字母 $A$ 替换为字符串 $\alpha$。例如，当字符串的形式为「$\beta A \gamma$」时，$\beta$ 和 $\gamma$ 是任意（可能为空）字符串，应用规则后，字符串变为「$\beta \alpha \gamma$」。如果原始字符串中有多个 $A$，可任意选择其中一个进行替换。

以下是一个例子规则集：

> S $\rightarrow$ aAB  
> (1) A $\rightarrow$   
> (2) A $\rightarrow$ Aa  
> (3) B $\rightarrow$ AbbA  

应用规则 (1) 在「S」，得到「aAB」。接着，用规则 (2) 将其变为「aB」，因为 A 被替换为空字符串。然后，可以用规则 (3) 将其变为「aAbbA」。使用规则 (3) 替换第一个 A 得到「aAabbA」。最后对末尾的 A 应用规则 (2)，得到「aAabb」。再对余下的 A 应用规则 (2)，最终得到「aabb」，此时没有大写字母，生成了合法名字「aabb」。

这整个生成过程可以这样表示：

> S $\;\stackrel{{\mbox{\tiny (1)}}}{{\longrightarrow}}\;$ aAB $\;\stackrel{{\mbox{\tiny (2)}}}{{\longrightarrow}}\;$ aB $\;\stackrel{{\mbox{\tiny (3)}}}{{\longrightarrow}}\;$ aAbbA $\;\stackrel{{\mbox{\tiny (3)}}}{{\longrightarrow}}\;$ aAabbA $\;\stackrel{{\mbox{\tiny (2)}}}{{\longrightarrow}}\;$ aAabb $\;\stackrel{{\mbox{\tiny (2)}}}{{\longrightarrow}}\;$ aabb

有时，语言学家可能定义一些奇怪的规则集。例如：

> S $\rightarrow$ sA  
> (1) A $\rightarrow$ aS  
> (2) B $\rightarrow$ b  

该规则集唯一可能的重写序列是：

> S $\;\stackrel{{\mbox{\tiny (1)}}}{{\longrightarrow}}\;$ sA $\;\stackrel{{\mbox{\tiny (2)}}}{{\longrightarrow}}\;$ saS $\;\stackrel{{\mbox{\tiny (1)}}}{{\longrightarrow}}\;$ sasA $\;\stackrel{{\mbox{\tiny (2)}}}{{\longrightarrow}}\;$ … 

这个过程会永远进行下去，无法终止，意味着没有合法名字。此外，因为 B 从未出现过，因此规则 (3) 从未使用。

在极端情况下，某些大写字母在重写过程中甚至可能没有任何对应规则，这样情况下自然不会有合法名字出现。某些婴儿因此可能无名，这真令人叹息！

现在，你的任务是编写一个程序，找到符合规则且给定长度的合法名字中字典顺序最靠前的一个。

## 输入格式

输入由若干个数据集组成，数据集以一行"0 0"结束。每个数据集以两个整数 $n$ 和 $l$ 开始，分别表示规则数（0 ≤ $n$ ≤ 50）和所需名字长度（0 ≤ $l$ ≤ 20）。接下来的 $n$ 行每行代表一条规则，以大写字母（A 到 Z）开头，之后是一个等号 "=", 再接规则的右侧，由字母 A 到 Z 和 a 到 z 组成，字符串长度不超过 10，可以为空，每条规则中不包含空格。

## 输出格式

对于每个数据集，按输入顺序输出答案，每行是一个小写字母字符串，表示符合规则且给定长度的字典序最小的合法名字。如果没有符合条件的字符串，输出"-"。输出中不应包含其他字符。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
 4 3
A=a
A=
S=ASb
S=Ab
2 5
S=aSb
S=
1 5
S=S
1 0
S=S
1 0
A=
2 0
A=
S=AA
4 5
A=aB
A=b
B=SA
S=A
4 20
S=AAAAAAAAAA
A=aA
A=bA
A=
0 0
```

### 输出

```
 
abb
-
-
-
-

aabbb
aaaaaaaaaaaaaaaaaaaa
```

