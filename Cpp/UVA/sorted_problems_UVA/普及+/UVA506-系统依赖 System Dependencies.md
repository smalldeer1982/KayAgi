---
title: "系统依赖 System Dependencies"
layout: "post"
diff: 普及+/提高
pid: UVA506
tag: []
---

# 系统依赖 System Dependencies

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=447

[PDF](https://uva.onlinejudge.org/external/5/p506.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA506/68afb2e6189fd70cb0193c35ff218476f81b2b02.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA506/00dcbed06d6ffd4ce2337600ff18c4293150ef46.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA506/5eeafd9adb13e67e1498450a046ece96f8f7f995.png)

## 样例 #1

### 输入

```
DEPEND TELNET TCPIP NETCARD
DEPEND TCPIP NETCARD
DEPEND DNS TCPIP NETCARD
DEPEND BROWSER TCPIP HTML
INSTALL NETCARD
INSTALL TELNET
INSTALL foo
REMOVE NETCARD
INSTALL BROWSER
INSTALL DNS
LIST
REMOVE TELNET
REMOVE NETCARD
REMOVE DNS
REMOVE NETCARD
INSTALL NETCARD
REMOVE TCPIP
REMOVE BROWSER
REMOVE TCPIP
END

```

### 输出

```
DEPEND TELNET TCPIP NETCARD
DEPEND TCPIP NETCARD
DEPEND DNS TCPIP NETCARD
DEPEND BROWSER TCPIP HTML
INSTALL NETCARD
Installing NETCARD
INSTALL TELNET
Installing TCPIP
Installing TELNET
INSTALL foo
Installing foo
REMOVE NETCARD
NETCARD is still needed.
INSTALL BROWSER
Installing HTML
Installing BROWSER
INSTALL DNS
Installing DNS
LIST
NETCARD
TCPIP
TELNET
foo
HTML
BROWSER
DNS
REMOVE TELNET
Removing TELNET
REMOVE NETCARD
NETCARD is still needed.
REMOVE DNS
Removing DNS
REMOVE NETCARD
NETCARD is still needed.
INSTALL NETCARD
NETCARD is already installed.
REMOVE TCPIP
TCPIP is still needed.
REMOVE BROWSER
Removing BROWSER
Removing HTML
Removing TCPIP
REMOVE TCPIP
TCPIP is not installed.
END
```

