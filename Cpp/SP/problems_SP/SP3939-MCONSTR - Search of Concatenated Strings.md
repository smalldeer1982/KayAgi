---
title: "MCONSTR - Search of Concatenated Strings"
layout: "post"
diff: 难度0
pid: SP3939
tag: []
---

# MCONSTR - Search of Concatenated Strings

## 题目描述

随着互联网上信息量的迅速增加，我们必须在这个信息爆炸的时代中，通过访问仅包含与个人需求相关信息的网页来生存。关键词搜索是实现这一目标的重要技术之一。通过使用知名的搜索引擎，我们可以轻松访问到包含我们所需信息的网页。

在关键词搜索的问题中，有很多的变体。若在给定文本中搜索一个单独的字符串，问题相对简单。但如果要搜索一个由多个字符串组成的模式，或者使用像正则表达式这样的复杂标记法，则需要更加复杂的算法来高效完成任务。

在本题中，给定若干个字符串（称为元素字符串），它们不是直接被搜索的目标。我们的目标是找到所有可能的元素字符串的不同组合并在文本中搜索这些组合。

例如，给定三个元素字符串 "aa"、"b" 和 "ccc"，我们要查找以下六个组合在文本中的位置：

```
aabccc
aacccb
baaccc
bcccaa
cccaab
cccbaa
```

文本中可能会出现这些组合多次。你需要计算这些组合在文本中出现的位置数目。值得注意的是，两个或多个组合可能是同一个字符串，例如，如果元素字符串是 "x" 和 "xx"，则字符串 "xxx" 既是 "x" 和 "xx" 连接的结果，也是 "xx" 和 "x" 连接的结果。在这种情况下，尽管组合方式不同，但只作为一个位置进行计算。

需要注意的是，多次出现可能发生重叠。例如，字符串 "xxxx" 中组合 "xxx" 可以在两个不同的位置出现，这样的情况计为两个位置。

## 输入格式

输入包含多组数据，每组数据包含一组元素字符串和一段文本。每组数据的格式如下：

```
n m
e1
e2
.
.
.
en
t1
t2
.
.
.
tm
```

第一行包含两个用空格分隔的整数。$n$ 是元素字符串的数量，$m$ 是文本的行数。$n$ 的范围是 1 到 12。接下来的 $n$ 行是元素字符串，每个字符串的长度在 1 到 20 之间。最后 $m$ 行表示文本，文本被分成这些行以避免过长的单行，但行与行之间的换行符不是文本的一部分。

每行的长度在 1 到 100 之间。文本的总长度在 1 到 5000 之间。元素字符串和文本都只包含小写字母。

输入以两零（"0 0"）结尾。

```
示例输入
3 1
aa
b
ccc
aabccczbaacccbaazaabbcccaa
3 1
a
b
c
cbbcbcbabaacabccaccbaacbccbcaaaccccbcbcbbcacbaacccaccbbcaacbbabbabaccc
3 4
aaaaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
0 0
```

## 输出格式

对于输入中的每组数据，输出一行，表示匹配的路径位置数目。输出时不带多余字符。

```
示例输出
5
12
197
```

 **本翻译由 AI 自动生成**

