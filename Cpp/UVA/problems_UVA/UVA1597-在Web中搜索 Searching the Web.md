---
title: "在Web中搜索 Searching the Web"
layout: "post"
diff: 提高+/省选-
pid: UVA1597
tag: []
---

# 在Web中搜索 Searching the Web

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4472

[PDF](https://uva.onlinejudge.org/external/15/p1597.pdf)

## 样例 #1

### 输入

```
4
A manufacturer, importer, or seller of
digital media devices may not (1) sell,
or offer for sale, in interstate commerce,
or (2) cause to be transported in, or in a
manner affecting, interstate commerce,
a digital media device unless the device
includes and utilizes standard security
technologies that adhere to the security
system standards.
**********
Of course, Lisa did not necessarily
intend to read his books. She might
want the computer only to write her
midterm. But Dan knew she came from
a middle-class family and could hardly
afford the tuition, let alone her reading
fees. Books might be the only way she
could graduate
**********
Research in analysis (i.e., the evaluation
of the strengths and weaknesses of
computer system) is essential to the
development of effective security, both
for works protected by copyright law
and for information in general. Such
research can progress only through the
open publication and exchange of
complete scientific results
**********
I am very very very happy!
What about you?
**********
6
computer
books AND computer
books OR protected
NOT security
very
slick
```

### 输出

```
want the computer only to write her
---------
computer system) is essential to the
==========
intend to read his books. She might
want the computer only to write her
fees. Books might be the only way she
==========
intend to read his books. She might
fees. Books might be the only way she
---------
for works protected by copyright law
==========
Of course, Lisa did not necessarily
intend to read his books. She might
want thea computer only to write her
midterm. But Dan knew she came from
a middle-class family and could hardly
afford the tuition, let alone her reading
fees. Books might be the only way she
could graduate
---------
I am very very very happy!
What about you?
==========
I am very very very happy!
==========
Sorry, I found nothing.
==========
```

