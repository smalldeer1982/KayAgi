---
title: "Tribles"
layout: "post"
diff: 提高+/省选-
pid: UVA11021
tag: ['递推', '期望', '线性递推']
---

# Tribles

## 题目描述

# Tribles

## 题面翻译

### 题目大意

一开始有 $k$ 只生物，这种生物只能活一天，死的时候有 $p_i$ 的概率生成 $i$ 只这种生物（也只能活一天），询问 $m$ 天内所有生物都死的概率（包括 $m$ 天前死亡的情况）


[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=22&page=show_problem&problem=1962

[PDF](https://uva.onlinejudge.org/external/110/p11021.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11021/dc00578efa81b6aad117bc54386f7e892627c921.png)

## 输入格式

第一行输入一个整数 $T$，表示数据总数

每一组先输入三个整数 $n(1<=n<=1000),k(0<=k<=1000),m(0<=m<=1000)$

接下来 $n$ 行，每行一个实数，分别为 $p_0$ 到 $p_{n-1}$


![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11021/08abc60eb45dcabca841e2417b496cd3ae2dca35.png)

## 输出格式

对于每一组数据，先输出"Case #x: "（请注意冒号后有一个**空格**）
再输出答案，精度要求在 1e-6 以内（即保留小数点后七位）

感谢@xMinh 提供翻译


![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11021/77ab0f01844658d722f6868f9a488841f59db741.png)

## 样例 #1

### 样例输入 #1

```
4
3 1 1
0.33
0.34
0.33
3 1 2
0.33
0.34
0.33
3 1 2
0.5
0.0
0.5
4 2 2
0.5
0.0
0.0
0.5
```

### 样例输出 #1

```
Case #1: 0.3300000
Case #2: 0.4781370
Case #3: 0.6250000
Case #4: 0.3164062
```

## 样例 #1

### 输入

```
4
3 1 1
0.33
0.34
0.33
3 1 2
0.33
0.34
0.33
3 1 2
0.5
0.0
0.5
4 2 2
0.5
0.0
0.0
0.5
```

### 输出

```
Case #1: 0.3300000
Case #2: 0.4781370
Case #3: 0.6250000
Case #4: 0.3164062
```

