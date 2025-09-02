---
title: "Lingua Romana"
layout: "post"
diff: 入门
pid: CF1331G
tag: []
---

# Lingua Romana

## 题目描述

```
per nextum in unam tum XI conscribementis fac sic
    vestibulo perlegementum da varo.
    morde varo.
    seqis cumula varum.
cis

per nextum in unam tum XI conscribementis fac sic
    seqis decumulamenta da varo.
    varum privamentum fodementum da aresulto.
    varum tum III elevamentum tum V multiplicamentum da bresulto.
    aresultum tum bresultum addementum da resulto.

    si CD tum resultum non praestantiam fac sic
        dictum sic f(%d) = %.2f cis tum varum tum resultum egresso describe.
        novumversum egresso scribe.
    cis
    si CD tum resultum praestantiam fac sic
        dictum sic f(%d) = MAGNA NIMIS! cis tum varum egresso describe.
        novumversum egresso scribe.        
    cis
cis
```

## 输入格式

输入包含多行数据，每一行有一个数 $n$，保证 $\large -50 \le n \le 50$。

## 输出格式

输出若干行，每行对于所给出的数据输出答案。

## 样例 #1

### 输入

```
0
1
-2
-3
-4
-5
-6
-7
-8
-9
10
```

### 输出

```
f(10) = MAGNA NIMIS!
f(-9) = -3642.00
f(-8) = -2557.17
f(-7) = -1712.35
f(-6) = -1077.55
f(-5) = -622.76
f(-4) = -318.00
f(-3) = -133.27
f(-2) = -38.59
f(1) = 6.00
f(0) = 0.00
```

