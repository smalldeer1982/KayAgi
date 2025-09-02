---
title: "Way Too Long Words"
layout: "post"
diff: 入门
pid: CF71A
tag: ['模拟', '字符串']
---

# Way Too Long Words

## 题目描述

有时候，像“localization”或“internationalization”这样的词汇如此之长，以至于在一篇文章中多次写下这些词语令人厌烦。

让我们考虑一个词太长，如果它的长度严格超过 10个字符。太长的单词应该用一个特殊的缩写代替。

这个缩写是这样写的：我们写下一个单词的第一个和最后一个字母，并在它们之间写出第一个和最后一个字母之间的字母数。该数字是十进制系统，不包含任何前导零。

因此，“localization”将拼写为“l10n”，而“internationalization”将拼写为”i18n”。

建议您使用缩写来自动更改单词的过程。因为所有太长的单词应该用缩写代替，不太长的单词不应该经历任何改变。

## 输入格式

第一行包含一个整数 n（ 1 <= N <= 100 1 < = n < = 1 0 0）。以下各项 n 行包含一个词。所有的单词由小写拉丁字母组成， 并且拥有从1到100个字符的长度。 _ _

## 输出格式

输出n行。第i行应包含来自输入数据的第 i个字替换的结果。

## 样例 #1

### 输入

```
4
word
localization
internationalization
pneumonoultramicroscopicsilicovolcanoconiosis

```

### 输出

```
word
l10n
i18n
p43s

```

