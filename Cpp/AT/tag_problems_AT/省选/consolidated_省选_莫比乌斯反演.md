---
title: "[AGC038C] LCMs"
layout: "post"
diff: 省选/NOI-
pid: AT_agc038_c
tag: ['数学', '莫比乌斯反演']
---

# [AGC038C] LCMs

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc038/tasks/agc038_c

長さ $ N $ の整数列 $ A_0,A_1,\cdots,A_{N-1} $ があります。 次式の値を求めてください。

- $ \sum_{i=0}^{N-2}\ \sum_{j=i+1}^{N-1}\ \mathrm{lcm}(A_i,A_j) $

ここで、$ \mathrm{lcm}(x,y) $ は、$ x $ と $ y $ の最小公倍数を意味します。 なお、答えは非常に大きくなることがあるので、$ 998244353 $ で割ったあまりを求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ A_0\ A_1\ \cdots\ A_{N-1} $

## 输出格式

$ \sum_{i=0}^{N-2}\ \sum_{j=i+1}^{N-1}\ \mathrm{lcm}(A_i,A_j) $ の値を $ 998244353 $ で割ったあまりを出力せよ。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 200000 $
- $ 1\ \leq\ A_i\ \leq\ 1000000 $
- 入力される値はすべて整数である。

### Sample Explanation 1

$ \mathrm{lcm}(2,4)+\mathrm{lcm}(2,6)+\mathrm{lcm}(4,6)=4+6+12=22 $ です。

## 样例 #1

### 输入

```
3

2 4 6
```

### 输出

```
22
```

## 样例 #2

### 输入

```
8

1 2 3 4 6 8 12 12
```

### 输出

```
313
```

## 样例 #3

### 输入

```
10

356822 296174 484500 710640 518322 888250 259161 609120 592348 713644
```

### 输出

```
353891724
```



---

---
title: "[ARC155D] Avoid Coprime Game"
layout: "post"
diff: 省选/NOI-
pid: AT_arc155_d
tag: ['博弈论', '莫比乌斯反演', 'SG 函数']
---

# [ARC155D] Avoid Coprime Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc155/tasks/arc155_d

$ 2 $ つの非負整数 $ x,\ y $ に対し $ \gcd(x,y) $ を $ x $ と $ y $ の最大公約数とします（ただし、 $ x=0 $ のときは $ \gcd(x,y)=\gcd(y,x)=y $ とします）。

黒板に $ N $ 個の整数が書かれており、そのうち $ i $ 番目の整数は $ A_i $ です。これら $ N $ 個の整数の最大公約数は $ 1 $ です。

高橋君と青木君が $ 2 $ 人で対戦ゲームをします。整数 $ G $ を $ G=0 $ で初期化した後、$ 2 $ 人は高橋君から始めて交互に以下の操作を繰り返します。

- 黒板に書かれている数のうち、$ \gcd(G,a)\neq\ 1 $ をみたす数 $ a $ を選んで消し、$ G $ を $ \gcd(G,a) $ で置き換える。
 
先に操作を行えなくなったほうが負けです。

各 $ i\ (1\leq\ i\ \leq\ N) $ について、高橋君が最初の手番で $ i $ 番目の整数を選んだ後、両者が最善を尽くした場合、どちらが勝つか判定してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ A_1 $ $ A_2 $ $ \dots $ $ A_N $

## 输出格式

$ N $ 行出力せよ。$ i $ 行目には高橋君が最初の手番で $ i $ 番目の整数を選んだ後、両者が最善を尽くした場合、高橋君が勝つ場合は `Takahashi` を、青木君が勝つ場合は `Aoki` を出力せよ。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 2\ \leq\ A_i\ \leq\ 2\ \times\ 10^5 $
- $ N $ 個の整数 $ A_i\ (1\leq\ i\ \leq\ N) $ の最大公約数は $ 1 $
- 与えられる入力はすべて整数
 
### Sample Explanation 1

例えば高橋君が最初の手番で $ 4 $ 番目の整数 $ A_4=6 $ を選んだ場合、青木君が $ 2 $ 番目の整数 $ A_2=3 $ を選ぶと $ G=3 $ となります。この後高橋君が選べる整数は存在しないので、青木君の勝利となります。よって $ 4 $ 行目には `Aoki` を出力します。

### Sample Explanation 2

黒板には同じ整数が複数個書かれていることがあります。

## 样例 #1

### 输入

```
4

2 3 4 6
```

### 输出

```
Takahashi

Aoki

Takahashi

Aoki
```

## 样例 #2

### 输入

```
4

2 155 155 155
```

### 输出

```
Takahashi

Takahashi

Takahashi

Takahashi
```

## 样例 #3

### 输入

```
20

2579 25823 32197 55685 73127 73393 74033 95252 104289 114619 139903 144912 147663 149390 155806 169494 175264 181477 189686 196663
```

### 输出

```
Takahashi

Aoki

Takahashi

Aoki

Takahashi

Takahashi

Takahashi

Takahashi

Aoki

Takahashi

Takahashi

Aoki

Aoki

Aoki

Aoki

Aoki

Takahashi

Takahashi

Aoki

Takahashi
```



---

