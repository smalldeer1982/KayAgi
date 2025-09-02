---
title: "Office Ninja"
layout: "post"
diff: 难度0
pid: AT_indeednow_2015_finala_b
tag: []
---

# Office Ninja

## 题目描述

[problemUrl]: https://atcoder.jp/contests/indeednow-finala-open/tasks/indeednow_2015_finala_b

 Indeed 社のオフィスは正六角形を組み合わせることによって構成されている。  
 新入社員の A 君は運動が得意なため、正六角形を区切っている仕切りを飛び越えて移動することが可能である。  
 いま、A 君は地点 $ s $ から地点 $ t $ へと急いで移動する必要がある。  
 しかし、$ s $ から $ t $ へ移動するために、正六角形のスペースに入った場合、そこにいる人に "How are you?" と聞かれるため、時間がかかってしまう。  
 しかも、一つの正六角形のスペースに $ n $ 人の人がいた場合、A 君は $ n $ 回 "How are you?" と聞かれてしまう。  
 A 君が $ s $ から $ t $ へ移動する際、最低で何回 "How are you?" と聞かれるだろうか。  
 ただし、地点 $ s $ と $ t $ では、"How are you?" と聞かれることがないものとする。

## 输入格式

入力は以下の形式で与えられる。

> $ R $ $ C $ $ a_{11} $ $ a_{12} $ $ ... $ $ a_{1C} $ $ a_{21} $ $ a_{22} $ $ ... $ $ a_{2C} $ $ ... $ $ a_{R1} $ $ a_{R2} $ $ ... $ $ a_{RC} $

- $ 1 $ 行目には、オフィスを構成する正六角形のスペースの行数 $ R $ と列数 $ C $ ($ 1\ \leq\ R,C\ \leq\ 100 $, $ R\ \times\ C\ \geq\ 2 $) が与えられる。
- $ 2 $ 行目から続く $ R $ 行には、オフィスのそれぞれの正六角形にいる人の数の情報 $ a_{ij} $ が与えられる。
- $ a_{ij} $ は `s`, `t`, `0` から `9` のいずれかからなる。
- 全ての $ a_{ij} $ のうち、ちょうど $ 1 $ つが `s` であり、ちょうど $ 1 $ つが `t` であることが保証される。
- $ a_{ij} $ と実際に与えられる値の対応は下図を参考にせよ。
 
![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_indeednow_2015_finala_b/cddde52e7d93b29c5e87ed4d353c8d2451956ca1.png)

## 输出格式

求める値を一行で出力せよ。

## 说明/提示

### Sample Explanation 1

!\[\](/img/other/indeednow-finala/sample1.png)

## 样例 #1

### 输入

```
3 4
s120
0321
220t
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 5
s0010
12032
11303
12114
5001t
```

### 输出

```
1
```

