---
title: "Indexing Web Pages"
layout: "post"
diff: 难度0
pid: UVA368
tag: []
---

# Indexing Web Pages

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=5&page=show_problem&problem=304

[PDF](https://uva.onlinejudge.org/external/3/p368.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA368/5ce31d48dcbcab98556f1e44f38b1811b1ef9cb2.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA368/ffc803ba5e8f6422b416d53b929ee9f3287f65af.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA368/33a451d17cca518122cd60cb3ae2ffc30283bfd6.png)

## 样例 #1

### 输入

```
&lt;HTML&gt;
&lt;HEAD&gt;
&lt;TITLE&gt;Indexing Web Pages&lt;/TITLE&gt;
&lt;/HEAD&gt;
&lt;BODY&gt;
&lt;P&gt;Write a program to create an index of a small collection
of World Wide Web pages. Each "page" is a text file in a
special format called HTML (HyperText Markup Language). The
HTML format includes regular text and special HTML commands,
which are always enclosed in angle braces. For example, the
string &lt;A HREF="layout.htm"&gt; is an HTML command meaning that
the following text should be highlighted; a user click on
the highlighted text would cause a web browser to fetch and
display the file layout.htm.&lt;/P&gt;
&lt;H1&gt;Following Links&lt;/H1&gt;
&lt;P&gt;Don't forget that links can be &lt;A HREF="index.htm"&gt;
self-referential&lt;/A&gt;!&lt;/P&gt;
&lt;/BODY&gt;
&lt;/HTML&gt;
&lt;A bunch of gibberish and a word&gt;
Note that there is no rule that the file needs to be legal HTML
(if you know the rules), or that words really be wordseiwlaoieu;a.
&lt;A HREF="index.htm"&gt;Watch out for mutual references!
&lt;/HTML&gt;
file
index
html
HTML
recursion
word
is
```

### 输出

```
"file" can be found in the following pages:
index.htm
layout.htm
"index" can be found in the following pages:
index.htm
"html" can be found in the following pages:
index.htm
layout.htm
"HTML" can be found in the following pages:
index.htm
layout.htm
"recursion" can not be found in any page.
"word" can not be found in any page.
"is" can be found in the following pages:
index.htm
layout.htm
```

