---
title: "Uncompress"
layout: "post"
diff: 难度0
pid: UVA245
tag: []
---

# Uncompress

## 题目描述

创建文本文件压缩版本的简单方案可用于不包含数字字符的文件。压缩方案要求在未压缩文件中列出单词。当在未压缩文件中遇到非字母字符时，将直接将其复制到压缩文件中。当在未压缩文件中遇到某个单词时，只有当这是该单词的第一次出现时，才会直接将其复制到压缩文件中。这样的话，这个词就放在名单的前面。如果不是第一次出现，则不将该单词复制到压缩文件中。相反地，它在列表中的位置被复制到压缩文件中，该单词被移动到列表的前面。列表位置的编号从$1$开始。请编写一个以压缩文件作为输入并生成原始未压缩文件作为输出的程序。

## 输入格式

你可以假设没有任何单词包含超过$50$个字符，而且原始的未压缩文件不包含任何数字字符。 单词是大小写敏感的$——$“$abc$”这个词和“$Abc$”这个词不一样。 例如，\
$x-ray$包含$2$个单词$:$$x$和$ray$$;$\
$mary's$包含$2$个单词$:$$mary$和$s$\
$it's$ $a$ $winner$包含$4$个单词$:$$it$和$s$以及 $a$和$winner$。\
输入文件中不同单词的数量没有上限。 输入文件的末尾由一行数字$“$0$”$结束。 终止的$“$0$”$只表示输入结束，不应成为程序输出的一部分。

## 样例 #1

### 输入

```
Dear Sally,
Please, please do it--1 would 4
Mary very, 1 much. And 4 6
8 everything in 5’s power to make
14 pay off for you.
-- Thank 2 18 18--
0
```

### 输出

```
Dear Sally,
Please, please do it--it would please
Mary very, very much. And Mary would
do everything in Mary’s power to make
it pay off for you.
-- Thank you very much--
```

