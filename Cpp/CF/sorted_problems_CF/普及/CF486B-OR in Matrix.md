---
title: "OR in Matrix"
layout: "post"
diff: 普及/提高-
pid: CF486B
tag: []
---

# OR in Matrix

## 题目描述

Let's define logical $ OR $ as an operation on two logical values (i. e. values that belong to the set $ {0,1} $ ) that is equal to $ 1 $ if either or both of the logical values is set to $ 1 $ , otherwise it is $ 0 $ . We can define logical $ OR $ of three or more logical values in the same manner:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF486B/406211f13f2a7c95dc14e24b4ae950d102f218cc.png) where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF486B/83308fae1dcded561005b623c7c1ed2fdfdfe04f.png) is equal to $ 1 $ if some $ a_{i}=1 $ , otherwise it is equal to $ 0 $ .

Nam has a matrix $ A $ consisting of $ m $ rows and $ n $ columns. The rows are numbered from $ 1 $ to $ m $ , columns are numbered from $ 1 $ to $ n $ . Element at row $ i $ ( $ 1<=i<=m $ ) and column $ j $ ( $ 1<=j<=n $ ) is denoted as $ A_{ij} $ . All elements of $ A $ are either 0 or 1. From matrix $ A $ , Nam creates another matrix $ B $ of the same size using formula:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF486B/157692e348a7a47f249e1d0e7ed60b12dc8cb619.png).

( $ B_{ij} $ is $ OR $ of all elements in row $ i $ and column $ j $ of matrix $ A $ )

Nam gives you matrix $ B $ and challenges you to guess matrix $ A $ . Although Nam is smart, he could probably make a mistake while calculating matrix $ B $ , since size of $ A $ can be large.

## 输入格式

The first line contains two integer $ m $ and $ n $ ( $ 1<=m,n<=100 $ ), number of rows and number of columns of matrices respectively.

The next $ m $ lines each contain $ n $ integers separated by spaces describing rows of matrix $ B $ (each element of $ B $ is either $ 0 $ or $ 1 $ ).

## 输出格式

In the first line, print "NO" if Nam has made a mistake when calculating $ B $ , otherwise print "YES". If the first line is "YES", then also print $ m $ rows consisting of $ n $ integers representing matrix $ A $ that can produce given matrix $ B $ . If there are several solutions print any one.

## 样例 #1

### 输入

```
2 2
1 0
0 0

```

### 输出

```
NO

```

## 样例 #2

### 输入

```
2 3
1 1 1
1 1 1

```

### 输出

```
YES
1 1 1
1 1 1

```

## 样例 #3

### 输入

```
2 3
0 1 0
1 1 1

```

### 输出

```
YES
0 0 0
0 1 0

```

