---
title: "RPLG - Goto & labels"
layout: "post"
diff: 难度0
pid: SP11493
tag: []
---

# RPLG - Goto & labels

## 题目描述

Vero 在一家重要的公司工作，但老板发现她在编写代码时使用了 `goto` 标签。老板希望她停止这种编程方式，并警告说每当有标签和 `goto` 语句之间的代码行时，都会扣减她的工资。

由于 Vero 不会使用循环结构，现在十分苦恼。她请你帮忙编写程序，以计算每对标签和 `goto` 语句之间代码行的数量。注意，所有 `goto` 语句都会跳转到一个已定义的标签。这些标签由字母 'a' 到 'z' 和 'A' 到 'Z' 组成，格式为 `_<label>:`，而 `goto` 语句的格式为 `goto <label>;`。在这些标签和 `goto` 语句之前可能存在的空格也算作代码的一部分。

需要注意的是，大小写标签区分大小写，例如：'abc' 和 'ABC' 是不同的标签。

## 输入格式

第一行是一个整数 $T$，表示测试用例的数量。接下来有 $T$ 个测试用例，每个测试用例的第一行是一个整数 $N$，表示代码的行数。随后的 $N$ 行中，每行包含一个字符串 $S$。

## 输出格式

对于每一个测试用例，输出形式为 `Scenario #i: `，其中 $i$ 是测试用例的编号，后面紧跟着标签和 `goto` 语句之间代码行数量的总和。

## 说明/提示

- $1 \leq N \leq 10000$
- 1 \leq 字符串长度 \leq 1000

**样例数据**

**输入**

```
3
6
A:
    SPACES will InDeNt the CoDe
    No TaBs ArE iN the >> test << data
goto A;
B:
goto B;
7
B:
A:
cin >> n;
 if(n<0) then
 goto A;
 else
 goto B;
7
 A:
 TumbaBicho:
 printf("goto TumbaBicho");
 printf("goto TumbaBicho");
 goto TumbaBicho;
AA:
 goto A;
```

**输出**

```
Scenario #1: 2
Scenario #2: 7
Scenario #3: 7
```

 **本翻译由 AI 自动生成**

