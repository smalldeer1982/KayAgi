---
title: "ORDERSET - Order statistic set"
layout: "post"
diff: 省选/NOI-
pid: SP3273
tag: []
---

# ORDERSET - Order statistic set

## 题目描述

维护一个支持以下操作的动态数组S：

- 将x插入S（INSERT(S,x)）

    如果x不在S里，将x插入S。
    
- 从S中删除x（DELETE(S,x)）

    如果x在S里，从S中删除x。
    
- 查询S中第k小的元素（K_TH(S)）

    返回S中第k小的元素。
    
- 计数（COUNT(S,x)）

    返回S中小于x的元素个数

## 输入格式

第一行：一个正整数Q，表示操作数目。

接下来Q行：一个字符，表示操作（I、D、K、C），即INSERT,DELETE,K_TH,COUNT的缩写和一个整数，整数为对应操作的参数。

保证$ 0 \leq \left|x\right|\leq 10^{9} $，$ 1 \leq k \leq 10^{9} $。

## 输出格式

对于每个查询，输出一行一个数表示结果。

如果K操作中$ k>S $中元素个数，输出一行"invalid"（不带引号）

=5088)

## 样例 #1

### 输入

```
8
I -1
I -1
I 2
C 0
K 2
D -1
K 1
K 2
```

### 输出

```
1
2
2
invalid
```

