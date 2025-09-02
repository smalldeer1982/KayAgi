---
title: "Compare Directories"
layout: "post"
diff: 难度0
pid: UVA10435
tag: []
---

# Compare Directories

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1376

[PDF](https://uva.onlinejudge.org/external/104/p10435.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10435/1fcd6b67f8d16a4722e458f3486581338ef7d7bf.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10435/83ed1cca9d2286e7101032ba72b75e48a2b62921.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10435/c3a5b737102893d69d89d22107d1646f45e97c9f.png)

## 样例 #1

### 输入

```
12/23/2001
/usr/bin
suman &lt;DIR&gt; 7
BigBro &lt;DIR&gt; 2
1.exe 987
2.exe 987
NewFile 109
directory &lt;DIR&gt; 3
hi 108
thisFile 203
xlog &lt;DIR&gt; 1
xlog.log 111
extra 1029
underConstruction &lt;DIR&gt; 3
index.html 12395
p0.html 1333
p1.html 2287
wrt.doc 1987
zlib &lt;DIR&gt; 0
/home
suman &lt;DIR&gt; 8
AAA.dat 60000
BigBro &lt;DIR&gt; 2
3.exe 387
4.exe 223
NewFile 109
directory &lt;DIR&gt; 3
hi 108
thisFile 203
xlog &lt;DIR&gt; 1
xlog.log 111
extra 1029
underConstruction &lt;DIR&gt; 3
index.html 11005
p0.htm 1333
p1.htm 2287
wrt.doc 1987
zLib &lt;DIR&gt; 2
bin &lt;DIR&gt; 2
gzip 299
gzip.log 300
zlib.so 23098
10/3/2002
/CDrive
ACMHelper &lt;DIR&gt; 1
acmhelper.exe 100
/tmp
Helper &lt;DIR&gt; 1
acmhelper.exe 100
11/2/2000
/CDrive
Prog &lt;DIR&gt; 2
ACMHelper &lt;DIR&gt; 1
acmhelper.exe 100
newDoc.rtf 2024
/tmp
CopyProg &lt;DIR&gt; 2
Helper &lt;DIR&gt; 1
acmhelper.exe 100
noname.c 1002
```

### 输出

```
==== Begin of Comparison ====
Transaction #1 : Date 12/23/2001
Comparing "/usr/bin/suman" with "/home/suman".
Comparing "/usr/bin/suman/BigBro" with "/home/suman/BigBro".
Totally different.
Comparing "/usr/bin/suman/directory" with "/home/suman/directory".
Comparing "/usr/bin/suman/directory/xlog" with "/home/suman/directory/xlog".
No difference.
No difference.
Comparing "/usr/bin/suman/underConstruction" with "/home/suman/underConstruction".
File size mismatch : "/usr/bin/suman/underConstruction/index.html (12395)" ...
... and "/home/suman/underConstruction/index.html (11005)".
"/usr/bin/suman/underConstruction" lacks of following file(s)
p0.htm 1333 byte(s)
p1.htm 2287 byte(s)
"/home/suman/underConstruction" lacks of following file(s)
p0.html 1333 byte(s)
p1.html 2287 byte(s)
Difference(s) encountered.
"/usr/bin/suman" lacks of following file(s)
AAA.dat 60000 byte(s)
zLib &lt;DIR&gt; 2 object(s)
"/home/suman" lacks of following file(s)
zlib &lt;DIR&gt; 0 object(s)
Difference(s) encountered.
Transaction #2 : Date 10/3/2002
Comparing "/CDrive/ACMHelper" with "/tmp/Helper".
No difference.
Transaction #3 : Date 11/2/2000
Comparing "/CDrive/Prog" with "/tmp/CopyProg".
Totally different.
==== End of Comparison ====
```

