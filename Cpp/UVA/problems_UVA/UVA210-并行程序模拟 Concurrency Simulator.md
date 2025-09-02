---
title: "并行程序模拟 Concurrency Simulator"
layout: "post"
diff: 普及+/提高
pid: UVA210
tag: []
---

# 并行程序模拟 Concurrency Simulator

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=4&page=show_problem&problem=146

[PDF](https://uva.onlinejudge.org/external/2/p210.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA210/47a8ebbcee2e250c00bc6a307fdd5bc936840928.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA210/23e8aa9b18423f56e43bc0db38efeeafe25d2e05.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA210/d18eb294963e1caf3ef55b142c42c327a6d1c43e.png)

## 样例 #1

### 输入

```
3 1 1 1 1 1 1
a = 4
print a
lock
b = 9
print b
unlock
print b
end
a = 3
print a
lock
b = 8
print b
unlock
print b
end
b = 5
a = 17
print a
print b
lock
b = 21
print b
unlock
print b
end
```

### 输出

```
1: 3
2: 3
3: 17
3: 9
1: 9
1: 9
2: 8
2: 8
3: 21
3: 21
```

