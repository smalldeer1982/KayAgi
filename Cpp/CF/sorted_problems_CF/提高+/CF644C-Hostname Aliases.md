---
title: "Hostname Aliases"
layout: "post"
diff: 提高+/省选-
pid: CF644C
tag: []
---

# Hostname Aliases

## 题目描述

有一些网站可以通过不同的地址进行访问。比如，过去 Codeforces 可以通过两个网址 codeforces.com 和 codeforces.ru 访问。

现提供一个网页地址查询列表。为简化问题，我们假设所有地址的格式为 http://<hostname>\[/<path>\]，其中：

- <hostname> 是服务器名，由单词组成，可能存在用点隔开的情况；
- /<path> 是可选部分，其中 <path> 由斜杠隔开的单词组成。

如果针对第一个 <hostname> 的每个查询，在第二个 <hostname> 上也有完全相同的查询，并且反之亦然——对于第二个 <hostname> 的每个查询，在第一个 <hostname> 上同样存在，那么我们就认为这两个 <hostname> 对应于同一个网站。具体情况请参考示例。

你的任务是确定哪些服务器名称属于同一个网站，且忽略只包含一个服务器名称的情况。

需要特别注意，按照上面的定义，查询 http://<hostname> 与 http://<hostname>/ 被视为不同的查询。

## 输入格式

输入的第一行是一个整数 $n$（$1 \leq n \leq 100000$），表示页面查询的数量。接下来有 $n$ 行，每行包含一个地址，其格式为 http://<hostname>\[/<path>\]，其中：

- <hostname> 是由小写字母和点组成，且不允许连续两个点，同时不能以点开头或结尾。其长度为正且不超过 $20$ 个字符。
- <path> 是由小写字母、点和斜杠组成，不能有连续的斜杠，也不能以斜杠开头，且其长度不超过 $20$ 个字符。

注意，这些地址不一定是唯一的。

## 输出格式

首先输出 $k$，表示对应同一网站的服务器名称组的数量。只需统计大小超过一个的组。

接下来的 $k$ 行中，每行描述一个组。对于每个组，输出所有服务器名称，使用空格分隔，顺序可以随意。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
10
http://abacaba.ru/test
http://abacaba.ru/
http://abacaba.com
http://abacaba.com/test
http://abacaba.de/
http://abacaba.ru/test
http://abacaba.de/test
http://abacaba.com/
http://abacaba.com/t
http://abacaba.com/test

```

### 输出

```
1
http://abacaba.de http://abacaba.ru 

```

## 样例 #2

### 输入

```
14
http://c
http://ccc.bbbb/aba..b
http://cba.com
http://a.c/aba..b/a
http://abc/
http://a.c/
http://ccc.bbbb
http://ab.ac.bc.aa/
http://a.a.a/
http://ccc.bbbb/
http://cba.com/
http://cba.com/aba..b
http://a.a.a/aba..b/a
http://abc/aba..b/a

```

### 输出

```
2
http://cba.com http://ccc.bbbb 
http://a.a.a http://a.c http://abc 

```

