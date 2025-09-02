---
title: "Meta-Loopless Sorts"
layout: "post"
diff: 提高+/省选-
pid: UVA110
tag: []
---

# Meta-Loopless Sorts

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=46

[PDF](https://uva.onlinejudge.org/external/1/p110.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA110/e7616c269157ee4482451a7f36d40055535e4cb7.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA110/d772c32f7b30502663ae983935ebd6a668b3adb4.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA110/7e651b84e37710fc6f17339b7b565f52feaebee1.png)

## 样例 #1

### 输入

```
1
3
```

### 输出

```
program sort(input,output);
var
a,b,c : integer;
begin
readln(a,b,c);
if a < b then
if b < c then
writeln(a,b,c)
else if a < c then
writeln(a,c,b)
else
writeln(c,a,b)
else
if a < c then
writeln(b,a,c)
else if b < c then
writeln(b,c,a)
else
writeln(c,b,a)
end.
```

