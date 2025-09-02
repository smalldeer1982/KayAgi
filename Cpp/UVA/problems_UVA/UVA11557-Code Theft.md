---
title: "Code Theft"
layout: "post"
diff: 难度0
pid: UVA11557
tag: []
---

# Code Theft

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=27&page=show_problem&problem=2593

[PDF](https://uva.onlinejudge.org/external/115/p11557.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11557/f2775765e3c2a7051ac3272b9541419abb199357.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11557/5015e5debedaf971aeac8b410736cff38ac00376.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11557/04d7f171af83291afe6120cf796922dd12f98d47.png)

## 样例 #1

### 输入

```
2
HelloWorld.c
int Main() {
printf("Hello %d\n",i);
}
***END***
Add.c
int Main() {
for (int i=0; i&lt;10; i++)
sum += i;
printf("SUM %d", sum);
}
***END***
int Main() {
printf("Hello %d\n",i);
printf("THE END\n");
}
***END***
2
HelloWorld1.bas
10 PRINT "*******************"
20 PRINT "*******************"
30 PRINT "--- HELLO WORLD ---"
40 PRINT "*******************"
50 PRINT "*******************"
***END***
HelloWorld2.bas
10 PRINT "-------------------"
20 PRINT "*******************"
30 PRINT "--- HELLO WORLD ---"
40 PRINT "*******************"
50 PRINT "-------------------"
***END***
10 REM Hello ver 1.0 (c) Acme 2008
20 PRINT "*******************"
30 PRINT "--- HELLO WORLD ---"
40 PRINT "*******************"
50 END
***END***
```

### 输出

```
2 HelloWorld.c
3 HelloWorld1.bas HelloWorld2.bas
```

