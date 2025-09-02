---
title: "[ARC166F] Tangent Addition Formula"
layout: "post"
diff: NOI/NOI+/CTSC
pid: AT_arc166_f
tag: ['原根', '数论', '标签453']
---

# [ARC166F] Tangent Addition Formula

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc166/tasks/arc166_f

素数 $ p $ および，非負整数 $ a,\ b $ が与えられます．

長さ無限の非負整数列 $ t\ =\ \bigl(t(0),\ t(1),\ t(2),\ \ldots) $ であって，以下の条件を全て満たすものが存在するか否かを判定してください．

- 任意の非負整数 $ x $ に対して $ 0\leq\ t(x)\ <\ p $．
- 任意の非負整数 $ x,\ y $ に対して $ t(x+y)\bigl(1-t(x)t(y)\bigr)\equiv\ t(x)+t(y)\pmod{p} $．
- $ t(a)=b $．
 
$ T $ 個のテストケースが与えられるので，それぞれについて答えを求めてください．

## 输入格式

入力は以下の形式で標準入力から与えられます．

> $ T $ $ \text{case}_1 $ $ \vdots $ $ \text{case}_T $

各テストケースは以下の形式で与えられます．

> $ p $ $ a $ $ b $

## 输出格式

$ T $ 行出力してください．$ i $ 行目には $ i $ 番目のテストケースについて，条件を満たす非負整数列 $ t $ が存在するならば `Yes` を，存在しないならば `No` を出力してください．

## 说明/提示

### 制約

- $ 1\leq\ T\leq\ 2\times\ 10^5 $
- $ p $ は $ 1\leq\ p\leq\ 10^9 $ を満たす素数．
- $ 0\leq\ a\leq\ 10^{9} $
- $ 0\leq\ b\ <\ p $
 
### Sample Explanation 1

\- $ p=11,\ a=1,\ b=0 $ の場合：定数列 $ t\ =\ (0,0,0,0,\ldots) $ が条件を満たします． - $ p=11,\ a=1,\ b=5 $ の場合：周期 $ 3 $ の数列 $ t\ =\ (0,5,6,0,5,6,\ldots) $ が条件を満たします．

## 样例 #1

### 输入

```
4

11 1 0

11 1 1

11 1 3

11 1 5
```

### 输出

```
Yes

No

No

Yes
```

## 样例 #2

### 输入

```
5

5 0 0

5 1 1

5 2 2

5 3 3

5 4 4
```

### 输出

```
Yes

No

Yes

Yes

No
```

## 样例 #3

### 输入

```
7

2 3 1

2 5 0

5 0 1

5 0 2

7 1 4

11 12345 5

13 12345 5
```

### 输出

```
Yes

Yes

No

Yes

No

No

Yes
```



---

