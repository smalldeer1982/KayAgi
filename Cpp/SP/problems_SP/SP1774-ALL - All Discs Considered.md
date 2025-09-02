---
title: "ALL - All Discs Considered"
layout: "post"
diff: 难度0
pid: SP1774
tag: []
---

# ALL - All Discs Considered

## 题目描述

 Operating systems are large software artefacts composed of many packages, usually distributed on several media, e.g., discs. You probably remember the time when your favourite operating system was delivered on 21 floppy discs, or, a few years later, on 6 CDs. Nowadays, it will be shipped on several DVDs, each containing tens of thousands of packages.

 The installation of certain packages may require that other packages have been installed previously. Therefore, if the packages are distributed on the media in an unsuitable way, the installation of the complete system requires you to perform many media changes, provided that there is only one reading device available, e.g., one DVD-ROM drive. Since you have to start the installation somehow, there will of course be one or more packages that can be installed independently of all other packages.

 Given a distribution of packages on media and a list of dependences between packages, you have to calculate the minimal number of media changes required to install all packages. For your convenience, you may assume that the operating system comes on exactly 2 DVDs.

## 输入格式

 The input contains several test cases. Every test case starts with three integers `N $ _{1} $ , N $ _{2} $ , D`. You may assume that `1<=N $ _{1} $ ,N $ _{2} $ <=50000` and `0<=D<=100000`. The first DVD contains `N $ _{1} $ ` packages, identified by the numbers `1, 2, ..., N $ _{1} $ `. The second DVD contains `N $ _{2} $ ` packages, identified by the numbers `N $ _{1} $ +1, N $ _{1} $ +2, ..., N $ _{1} $ +N $ _{2} $ `. Then follow `D` dependence specifications, each consisting of two integers `x $ _{i} $ , y $ _{i} $ `. You may assume that `1<=x $ _{i} $ ,y $ _{i} $ <=N $ _{1} $ +N $ _{2} $ ` for `1<=i<=D`. The dependence specification means that the installation of package `x $ _{i} $ ` requires the previous installation of package `y $ _{i} $ `. You may assume that there are no circular dependences. The last test case is followed by three zeros.

## 输出格式

 For each test case output on a line the minimal number of DVD changes required to install all packages. By convention, the DVD drive is empty before the installation and the initial insertion of a disc counts as `one` change. Likewise, the final removal of a disc counts as `one` change, leaving the DVD drive empty after the installation.

## 样例 #1

### 输入

```
3 2 1
1 2
2 2 2
1 3
4 2
2 1 1
1 3
0 0 0
```

### 输出

```
3
4
3
```

