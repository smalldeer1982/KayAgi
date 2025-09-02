---
title: "bHTML Tables Analisys"
layout: "post"
diff: 提高+/省选-
pid: CF51B
tag: []
---

# bHTML Tables Analisys

## 题目描述

在这个问题中，使用了一个非常简单的HTML表格标记版本(bHTML)。 请把这个陈述作为题目的一部分，并仔细阅读。

如果一个字符串符合语法，它就是一个bHTML表

语法: <br></br>TABLE ::= <table>ROWS</table><br></br>ROWS ::= ROW | ROW ROWS<br></br>ROW ::= <tr>CELLS</tr><br></br>CELLS ::= CELL | CELL CELLS<br></br>CELL ::= <td></td> | <td>TABLE</td><br></br> 解释: 在语法中，只是为了说明的目的，在给定的数据中不会有空格。 bHTML表格非常类似于一个简单的普通HTML表格，其中只符合下列标签：“table”，“tr”，“td”，所有标签都配对，表格至少包含一行和至少一个单元格。在每一行中。为了更深入了解题意，请你看看样本测试，将其作为表格的例子。

可以看出，表格可以嵌套。 给你一个表（可能包含多组数据）。 你需要编写一个分析所有表格的程序，并找出每个表格中的单元格数量。 这些表格不需要是矩形的。

## 输入格式

为了方便起见，输入数据可以以任意方式分成非空行。 输入数据不超过10行。 将所有输入行组合（连接）成一个，以获得指定表的文本表示。 字符串s对应于给定的语法（语法的根元素是TABLE），其长度不超过5000.只有小写字母用于写入标记。给定的字符串中没有空格。

## 输出格式

以非递减的顺序输出所有表格的大小。

Translated by @Franco

## 样例 #1

### 输入

```
<table><tr><td></td></tr></table>

```

### 输出

```
1 
```

## 样例 #2

### 输入

```
<table>
<tr>
<td>
<table><tr><td></td></tr><tr><td></
td
></tr><tr
><td></td></tr><tr><td></td></tr></table>
</td>
</tr>
</table>

```

### 输出

```
1 4 
```

## 样例 #3

### 输入

```
<table><tr><td>
<table><tr><td>
<table><tr><td>
<table><tr><td></td><td></td>
</tr><tr><td></td></tr></table>
</td></tr></table>
</td></tr></table>
</td></tr></table>

```

### 输出

```
1 1 1 3 
```

