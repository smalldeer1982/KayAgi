---
title: "Jabber ID"
layout: "post"
diff: 普及-
pid: CF21A
tag: ['模拟', '字符串']
---

# Jabber ID

## 题目描述

一个地址由 `<username>@<hostname>[/resource]` 组成，其中 `[/resource]` 可以被省略。

- `<username>` 字段允许大写、小写字母，数字、下划线，其长度应在 $1$ 到 $16$ 之间。
- `<hostname>` 字段允许用 `.` 来分隔。每一段的要求同  `<username>` 字段，分隔出的每一部分长度在 $1$ 到 $16$，`<hostname>` 字段的总长度在 $1$ 到 $32$ 之间。
- `<resource>` 字段要求同 `<username>` 字段。


给出一个地址，询问是否合法。

## 输入格式

一行，一个字符串，表示一个地址（保证地址的字符的 ASCII 在 $33$ 到 $127$ 间），地址长度不超过 $100$ 字符。

## 输出格式

一行，如果合法输出 `YES`，否则输出 `NO`。

## 样例 #1

### 输入

```
mike@codeforces.com

```

### 输出

```
YES

```

## 样例 #2

### 输入

```
john.smith@codeforces.ru/contest.icpc/12

```

### 输出

```
NO

```

