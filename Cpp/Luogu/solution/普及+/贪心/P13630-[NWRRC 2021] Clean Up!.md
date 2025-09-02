# [NWRRC 2021] Clean Up!

## 题目描述

有一天，Charlie 决定通过删除 Downloads 目录下的所有文件来开始新生活。使用 $\texttt{bash}$ shell 可以很容易地完成这个操作！它有两个有用的功能：$\texttt{rm}$ 命令可以删除作为参数传入的所有文件，通配符可以在执行命令前将其替换为所有匹配的文件列表。

Charlie 执行了 $\texttt{rm *}$，但收到了 $\texttt{Argument list too long}$ 的提示。原来，在 $\texttt{bash}$ 将 $\texttt{*}$ 替换为 Downloads 目录下所有文件名后，由于参数过多，命令无法执行。

经过一些实验，Charlie 发现他可以执行 $\texttt{rm abc*}$ 来删除所有以 $\texttt{abc}$ 开头的文件，前提是这样的文件数量不超过 $k$ 个。如果匹配该模式的文件超过 $k$ 个，则这些文件都不会被删除。当然，他可以用任意字符串替换 $\texttt{abc}$。

请你帮助 Charlie 计算，删除所有文件所需的最少 $\texttt{rm}$ 命令次数。假设他只能使用形如 $\texttt{rm <prefix>*}$ 的命令，其中 $\texttt{<prefix>}$ 由小写英文字母组成（可以为空）。

## 说明/提示

在第一个样例测试中，Charlie 可以执行 $\texttt{rm ab*}$ 删除文件 $\texttt{abc}$ 和 $\texttt{abd}$，然后执行 $\texttt{rm~*}$ 删除文件 $\texttt{a}$ 和 $\texttt{b}$。注意，他不能一开始就执行 $\texttt{rm *}$，因为最初所有四个文件都匹配空前缀。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 2
a
abc
abd
b```

### 输出

```
2```

## 样例 #2

### 输入

```
4 2
d
c
ab
a```

### 输出

```
2```

## 样例 #3

### 输入

```
5 3
please
remove
all
these
files```

### 输出

```
3```

