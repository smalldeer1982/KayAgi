---
title: "Interesting Equation"
layout: "post"
diff: 难度0
pid: AT_xmascon18_i
tag: []
---

# Interesting Equation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/xmascon18/tasks/xmascon18_i

実数 $ X $ が与えられるので，以下の条件を満たす整数 $ a $, $ b $, $ c $, $ d $ を $ 1 $ 組求めよ：

- $ \lvert\ a\ \rvert\ \le\ 10^5 $，
- $ \lvert\ b\ \rvert\ \le\ 10^5 $，
- $ \lvert\ c\ \rvert\ \le\ 10^5 $，
- $ \lvert\ a\ X^3\ +\ b\ X^2\ +\ c\ X\ +\ d\ \rvert\ \le\ 10^{-10} $，
- $ a $, $ b $, $ c $, $ d $ のうち少なくとも $ 1 $ 個は $ 0 $ ではない．

## 输入格式

> $ X $

実数 $ X $ は十進表記で小数点以下ちょうど $ 12 $ 桁で表示される．

## 输出格式

> $ a $ $ b $ $ c $ $ d $

## 说明/提示

### 制約

- $ 0\ \le\ X\ \lt\ 10 $．
- $ X $ は十進表記で小数点以下 $ 12 $ 桁までからなる．
- 以下の条件を満たす整数 $ a $, $ b $, $ c $, $ d $ が存在する：
  - $ \lvert\ a\ \rvert\ \le\ 10^4 $，
  - $ \lvert\ b\ \rvert\ \le\ 10^4 $，
  - $ \lvert\ c\ \rvert\ \le\ 10^4 $，
  - $ \lvert\ a\ X^3\ +\ b\ X^2\ +\ c\ X\ +\ d\ \rvert\ \le\ 10^{-12} $，
  - $ a $, $ b $, $ c $, $ d $ のうち少なくとも $ 1 $ 個は $ 0 $ ではない．

## 样例 #1

### 输入

```
2.018000000000
```

### 输出

```
0 0 1000 -2018
```

## 样例 #2

### 输入

```
1.414213562373
```

### 输出

```
0 1 0 -2
```

## 样例 #3

### 输入

```
3.141592653589
```

### 输出

```
5103 -2893 -4197 -116487
```

