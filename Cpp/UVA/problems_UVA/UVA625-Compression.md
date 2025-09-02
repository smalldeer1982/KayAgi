---
title: "Compression"
layout: "post"
diff: 难度0
pid: UVA625
tag: []
---

# Compression

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=8&page=show_problem&problem=566

[PDF](https://uva.onlinejudge.org/external/6/p625.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA625/b62d83c828c3a5d69030e3840fa3ffe7fc09ead4.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA625/d365510b55b04666c3a3437a58232df7904fa85f.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA625/c2a4607f72e500ca378cd290678a66680d602abd.png)

## 样例 #1

### 输入

```
1
program Test;
var n :integer;
function harmonic(number :integer):real;
var i :integer;
result :real;
begin
result := 0;
for i := 1 to number do
begin
number := number + 1/i;
end;
harmonic := result;
end;
begin
writeln('Get n:');
readln(n);
writeln('harmonic number for n: ');
writeln(harmonic(n));
end.
```

### 输出

```
program Test;
&amp;0 n :integer;
&amp;14 harmonic(number :&amp;18):real;
&amp;0 i :&amp;18;
result :&amp;21;
&amp;10
&amp;22 := 0;
&amp;2 i := 1 to &amp;20 do
&amp;10
&amp;20 := &amp;20 + 1/i;
&amp;1;
&amp;19 := &amp;22;
&amp;1;
&amp;10
writeln('Get n:');
readln(n);
&amp;23('&amp;19 &amp;20 &amp;2 n: ');
&amp;23(&amp;19(n));
&amp;1.
```

