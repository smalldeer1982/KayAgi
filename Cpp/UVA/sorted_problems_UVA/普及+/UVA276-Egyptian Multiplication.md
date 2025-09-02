---
title: "Egyptian Multiplication"
layout: "post"
diff: 普及+/提高
pid: UVA276
tag: []
---

# Egyptian Multiplication

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=4&page=show_problem&problem=212

[PDF](https://uva.onlinejudge.org/external/2/p276.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA276/3e3850d49e159c782983df24a038f7939bc517c0.png)

## 输入格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA276/bdafcfe3d13afc24653fc114188934a79565e546.png)

## 输出格式

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA276/57310300f70196a1ac7dfecbaa5fd676e0293e9b.png)

## 样例 #1

### 输入

```
||
||
|||
||||
nnnnnn 9
||| n
n
9
|||
8
```

### 输出

```
|                                 || 
|| *                              |||| 
The solution is: |||| 
|                                 ||| 
||                                |||||| 
|||| *                            || n 
The solution is: || n 
| *                               nnnnnn 9 
||                                nn 999 
|||| *                            nnnn 999999 
|||||||| *                        nnnnnnnn 99 8 
The solution is: nnnnnnnn 88 
|                                 n 
||                                nn 
|||| *                            nnnn 
||||||||                          nnnnnnnn 
|||||| n                          nnnnnn 9 
|| nnn *                          nn 999 
|||| nnnnnn *                     nnnn 999999 
The solution is: 8 
|                                 ||| 
||                                |||||| 
||||                              || n 
|||||||| *                        |||| nn 
|||||| n                          |||||||| nnnn 
|| nnn *                          |||||| nnnnnnnnn 
|||| nnnnnn *                     || nnnnnnnnn 9 
|||||||| nn 9 *                   |||| nnnnnnnn 999 
|||||| nnnnn 99 *                 |||||||| nnnnnn 9999999 
|| n 99999 *                      |||||| nnn 99999 8 
The solution is: 888 

```

