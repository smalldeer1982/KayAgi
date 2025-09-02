---
title: "SOAP Response"
layout: "post"
diff: 难度0
pid: UVA11869
tag: []
---

# SOAP Response

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=226&page=show_problem&problem=2980

[PDF](https://uva.onlinejudge.org/external/118/p11869.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11869/6463134421895921dc09c95e8af4548d53e74e8f.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11869/e4fb07b9db836ed4e3216aa8a05c2176fe9f43f2.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11869/c3d5d78afded5cb86d952e4253cc0d9308c5d869.png)

## 样例 #1

### 输入

```
1
8
&lt;a good="true" wants="no"&gt;
&lt;b&gt;
&lt;c contest="running"&gt;
&lt;d ballon="no"&gt;
&lt;/d&gt;
&lt;/c&gt;
&lt;/b&gt;
&lt;/a&gt;
4
a.b.c.d["ballon"]
a.c["contest"]
a.b.c["contest"]
c["contest"]
```

### 输出

```
Case 1:
no
Undefined
running
Undefined
```

