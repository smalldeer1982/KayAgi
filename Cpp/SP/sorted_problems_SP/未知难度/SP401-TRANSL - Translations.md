---
title: "TRANSL - Translations"
layout: "post"
diff: 难度0
pid: SP401
tag: []
---

# TRANSL - Translations

## 题目描述

### 目标
读入语言$A$与语言$B$的词组，生成一本可以将语言$A$翻译为语言$B$的字典

## 输入格式

有多项测试数据。

第$1$行一个正整数$N$($N\le250$ )，表示你需要读入的由两个单词(均只由大小写字母构成)组成的词组的个数。

第$2\backsim2n+1$行，每行读入$1$个词组。

对于第$2\backsim n+1$行，表示语言$A$中的词组。

对于第$n+2\backsim 2n+1$行，表示上述语言$A$词组在语言$B$中的写法。

这些词组最后都按字典序升序排列。

保证对于任何一个测试数据，单词数不会超过$25$，也不会有任何一个单词在所有的短语中出现$10$次以上。

输入最后一行为$0$，表示读入结束。

## 输出格式

对于任意一组测试数据，你需要按语言A单词的字典序升序排列的顺序输出，形如：

语言A单词1/对应的语言B单词

语言A单词2/对应的语言B单词

…………

最后输出一个空行表示分隔不同的测试数据输出。

## 样例 #1

### 输入

```
4
arlo zym
flub pleve
pleve dourm
pleve zym
bus seat
bus stop
hot seat
school bus
2
iv otas
otas re
ec t
eg ec
0
```

### 输出

```
arlo/hot
dourm/stop
flub/school
pleve/bus
zym/seat

iv/eg
otas/ec
re/t
```

