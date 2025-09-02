---
title: "[ABC020B] 足し算"
layout: "post"
diff: 入门
pid: AT_abc020_b
tag: ['字符串', '概率论']
---

# [ABC020B] 足し算

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc020/tasks/abc020_b

$ 2 $ つの正整数 $ A, $ $ B $ が与えられます。 $ A $ の十進表記の右に $ B $ の十進表記（先頭に $ 0 $ を付けない）を連結して得られる整数を $ 2 $ 倍したものを出力してください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ A $ $ B $

- $ 1 $ 行目に、 $ 2 $ 個の整数 $ A, $ $ B $ ($ 1 $ $ ≦ $ $ A, $ $ B $ $ ≦ $ $ 999 $) がスペース区切りで与えられる。

## 输出格式

標準出力に指示された値を出力せよ。

末尾の改行を忘れないこと。

## 说明/提示

### Sample Explanation 1

$ 123\ ×\ 2\ =\ 246 $ となります。

## 样例 #1

### 输入

```
1 23
```

### 输出

```
246
```

## 样例 #2

### 输入

```
999 999
```

### 输出

```
1999998
```



---

---
title: "[ABC073C] Write and Erase"
layout: "post"
diff: 入门
pid: AT_abc073_c
tag: ['模拟', '排序', '概率论']
---

# [ABC073C] Write and Erase

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc073/tasks/abc073_c

あなたは、joisinoお姉ちゃんと以下のようなゲームをしています。

- 最初、何も書いていない紙がある。
- joisinoお姉ちゃんが一つの数字を言うので、その数字が紙に書いてあれば紙からその数字を消し、書いていなければその数字を紙に書く。これを $ N $ 回繰り返す。
- その後、紙に書かれている数字がいくつあるかを答える。

joisinoお姉ちゃんが言った数字が、言った順番に $ A_1,\ ...\ ,A_N $ として与えられるので、ゲーム終了後に紙に書かれている数字がいくつあるか答えてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ A_1 $ $ : $ $ A_N $

## 输出格式

ゲーム終了後に紙に書かれている数字の個数を出力せよ。

## 说明/提示

### 制約

- $ 1≦N≦100000 $
- $ 1≦A_i≦1000000000(=10^9) $
- 入力は全て整数である。

### Sample Explanation 1

以下の操作を行うこととなります。 - 紙に $ 6 $ は書かれていないので、$ 6 $ を書く。 - 紙に $ 2 $ は書かれていないので、$ 2 $ を書く。 - 紙に $ 6 $ は書かれているので、$ 6 $ を消す。 よって、最後に書いてあるのは $ 2 $ だけなので、答えは $ 1 $ です。

### Sample Explanation 2

最後に紙に数字が一つも書かれていない場合もあります。

## 样例 #1

### 输入

```
3

6

2

6
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4

2

5

5

2
```

### 输出

```
0
```

## 样例 #3

### 输入

```
6

12

22

16

22

18

12
```

### 输出

```
2
```



---

---
title: "P(X or Y)"
layout: "post"
diff: 入门
pid: AT_abc407_b
tag: ['枚举', '概率论']
---

# P(X or Y)

## 题目描述

有两个每一面分别为 $1,2,3,4,5,6$ 的六面骰子，现在投掷两个骰子，求出下面两个条件至少满足一个的概率。
- 两个骰子的点数之和大于或等于 $X$。
- 两个骰子点数之差的绝对值大于或等于 $Y$。

骰子每个面的可能性是相同的，两个骰子是独立的，一个骰子投出的点数不影响另一个骰子投出的点数。

## 输入格式

输入共一行，两个整数 $X,Y$。

## 输出格式

输出两个条件至少满足一个的概率。你的答案被判为正确当且仅当你的答案和正确答案的绝对误差小于 ${10}^{-9}$。

## 说明/提示

### 数据范围
$2 \le X \le 13,\ 0 \le Y \le 6$
### 样例解释 #1
记两个骰子的点数分别为 $x$ 和 $y$，以下用 $(x,y)$ 表示每一种结果。
- 两个骰子点数的和至少为 $9$ 的结果有 $(3,6),(4,5),(4,6),(5,4),(5,5),(5,6),(6,3),(6,4),(6,5),(6,6)$。
- 两个骰子点数差的绝对值至少为 $3$ 的结果有 $(1,4),(1,5),(1,6),(2,5),(2,6),(3,6),(4,1),(5,1),(5,2),(6,1),$ $(6,2),(6,3)$。

至少满足一个条件的结果有 $(1,4),(1,5),(1,6),(2,5),(2,6),(3,6),(4,1),(4,5),(4,6),(5,1),$ $(5,2),(5,4),(5,5),(5,6),(6,1),(6,2),(6,3),(6,4),(6,5),(6,6)$ 共 $20$ 种，可能的结果有 $36$ 种，因此答案为 $\dfrac{20}{36}=\dfrac{5}{9}=0.55555555555555\ldots$。由于你的答案被允许与标准答案有小于 ${10}^{-9}$ 的绝对误差，因此输出 `0.5555555565`、`0.55555555456789` 等都会被认为正确。
### 样例解释 #2

两个骰子点数的和不可能大于等于 $13$，点数差的绝对值也不可能大于等于 $6$，因此答案是 $0$。

## 样例 #1

### 输入

```
9 3
```

### 输出

```
0.555555555555555555555555555555
```

## 样例 #2

### 输入

```
13 6
```

### 输出

```
0
```

## 样例 #3

### 输入

```
10 3
```

### 输出

```
0.5
```



---

---
title: "[ARC003A] GPA計算"
layout: "post"
diff: 入门
pid: AT_arc003_1
tag: ['模拟', '字符串', '概率论']
---

# [ARC003A] GPA計算

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc003/tasks/arc003_1

高橋君はアメリカに留学しようと考えており、成績表を提出することになりました。  
 アメリカ留学の成績表には、学力を測る指標であるGPAを表記する必要があります。  
 GPAとは各単位に対する評価(A,B,C,D,F)を点数に換算して平均した値で、点数への換算は以下のようになります。

- A評価 → $ 4 $ 点
- B評価 → $ 3 $ 点
- C評価 → $ 2 $ 点
- D評価 → $ 1 $ 点
- F評価 → $ 0 $ 点
 
 全てF評価だった場合は、GPAは $ 0 $ になります。  
 高橋君の各単位に対する評価をもとにGPAを求めなさい。 入力は以下の形式で標準入力から与えられる。 > $ N $ $ r_{1}r_{2}...r_{N} $

- $ 1 $ 行目は、単位の総数を表す整数 $ N\ (1\ ≦\ N\ ≦\ 100) $ が与えられる。
- $ 2 $ 行目には、単位に対する評価を表す $ N $ 文字の文字列が与えられる。
- $ i $ 文字目の文字 $ r_{i} $ は `A`, `B`, `C`, `D`, `F` のいずれかである。

 入力として与えられた単位の評価をもとにしたGPAを標準出力に $ 1 $ 行で出力せよ。  
 誤差は絶対誤差あるいは相対誤差の少なくとも片方が $ 1e-9 $ 以下であれば許容する。$ (1e-9=10^{-9}) $  
 なお、最後には改行を出力せよ。 ```
<pre class="prettyprint linenums">
34
ABABAAABACDDDABADFFABABDABFAAABFAA
```

 ```
<pre class="prettyprint linenums">
2.79411764705882
```

- 各評価の個数は以下のようになります。
- A評価 … $ 16 $ 個
- B評価 … $ 8 $ 個
- C評価 … $ 1 $ 個
- D評価 … $ 5 $ 個
- F評価 … $ 4 $ 個

- したがって、点数の総和は $ 4×16+3×8+2×1+1×5+0×4=95 $ になり、平均は $ 95÷34=2.79411764705882 $ です。
 
```
<pre class="prettyprint linenums">
5
FFFFF
```

 ```
<pre class="prettyprint linenums">
0
```

- F評価が $ 5 $ つなのでGPAは $ (0×5)÷5=0 $ になります。



---

---
title: "[ARC038A] カードと兄妹"
layout: "post"
diff: 入门
pid: AT_arc038_a
tag: ['排序', '概率论']
---

# [ARC038A] カードと兄妹

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc038/tasks/arc038_a

$ N $ 枚のカードがあり、$ i\ (1\ ≦\ i\ ≦\ N) $ 枚目のカードには整数 $ A_i $ が書かれています。ゲーム好きの兄妹はこれらのカードを使ってゲームをしようとしています。

- 最初に全てのカードを、カードに書かれた整数が見えるようにテーブルの上に並べる。
- プレイヤーは自分のターンに、テーブルの上にあるカードからちょうど $ 1 $ 枚のカードを選んで取る。
- テーブルの上にカードがなくなるまで、交互にターンを繰り返す。
- 最終的に、自分が取ったカードに書かれた整数の和がプレイヤーの **スコア** となる。

$ 2 $ 人ともが自分のスコアを出来るだけ大きくしようとしたとき、先手のスコアはいくつになるでしょうか？

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ A_1 $ $ A_2 $ ... $ A_N $

- $ 1 $ 行目には、カードの枚数を表す整数 $ N\ (1\ ≦\ N\ ≦\ 1000) $ が与えられる。
- $ 2 $ 行目には、各カードに書かれた整数を表す $ N $ 個の整数が空白区切りで与えられる。このうち $ i\ (1\ ≦\ i\ ≦\ N) $ 番目の整数 $ A_i\ (1\ ≦\ A_i\ ≦\ 1000) $ は、$ i $ 枚目のカードに書かれた整数を表す。

## 输出格式

先手のスコアを $ 1 $ 行に出力せよ。出力の末尾に改行を入れること。

## 说明/提示

### Sample Explanation 1

この例では、ゲームは以下のように進行します。 - 先手が $ 2 $ 枚目のカードを取る。 - 後手が $ 1 $ 枚目のカードを取る。 このとき、先手のスコアは $ 628 $ となり、後手のスコアは $ 400 $ となります。

### Sample Explanation 2

この例では、ゲームは以下のように進行します。 - 先手が $ 3 $ 枚目のカードを取る。 - 後手が $ 4 $ 枚目のカードを取る。 - 先手が $ 2 $ 枚目のカードを取る。 - 後手が $ 5 $ 枚目のカードを取る。 - 先手が $ 1 $ 枚目のカードを取る。 このとき、先手のスコアは $ 16 $ となり、後手のスコアは $ 11 $ となります。

## 样例 #1

### 输入

```
2

400 628
```

### 输出

```
628
```

## 样例 #2

### 输入

```
5

2 5 9 6 5
```

### 输出

```
16
```



---

---
title: "○×ブロック"
layout: "post"
diff: 入门
pid: AT_chokudai003_a
tag: ['字符串', '概率论']
---

# ○×ブロック

## 题目描述

[problemUrl]: https://atcoder.jp/contests/chokudai003/tasks/chokudai003_a

$ N $ × $ N $ の正方形のブロックが与えられます。 ブロックは、 `o`ブロック、 `x`ブロック、 `.`ブロックの $ 3 $ つが与えられています。

しばらくすると`.`ブロックが全て消滅し、上にあるブロックが落ちてくることを知っています。

あなたは、ブロックが消滅する前に、`.` ブロックを、以下の $ 2 $ 種類のブロックのどちらかに変換することが可能です。

- `+`ブロック：消滅しない普通のブロック
- `-`ブロック：消滅しないことに加え、自由落下もしないブロック

あなたは、書き換えた後に、`.`ブロック消滅後の、上下左右方向に連結する`o`ブロックの最大数と、同様に連結する`x`ブロックの最大数の和を できるだけ大きくしたいです。

ブロックを変更する前の状態が与えられるので、ブロックを変更した後の状態を出力してください。

## 输入格式

> $ S_1 $ $ S_2 $ : $ S_N $

## 输出格式

変更後のブロックの配置を、入力のフォーマットと同様の形で出力せよ。 ただし、`+`ブロックは`+`、`-`ブロックは`-`で表現するものとする。

連結数の和がそのケースの得点となり、 $ 10 $ 個の入力の点数の和が、あなたの提出の得点となる。

## 说明/提示

### 制約

- $ N $ = $ 50 $
- $ S_i $ は $ N $ 文字の文字列であり、 $ j $ 番目の文字 $ S_{i,j} $ は、`o`,`x`,`.`の $ 3 $ 種類のどれかである。
- 入力は、各文字に対し、$ 50% $ の確率で `.`、残りの $ 25% $ の確率で`o`か`x`になるようにランダムで生成される。

### Sample Explanation 1

この入力は、説明のため、実際には存在しない小さい入力を使用しております。 全ての `.`ブロックが消滅したとき、以下のような状態になります。 図は、`o`ブロックを○、`x`ブロックを×、`+`ブロックを★、`-`ブロックを■で表現したものになります。 !\[例\](https://atcoder.jp/img/chokudai003/board.png)

## 样例 #1

### 输入

```
o.xx..ox..

..o.xx.o.x

.xxoo...o.

o..x.ox.x.

..o.o..ox.

..x..oo..x

.o.x.xxo..

x..xo.xxoo

.o..oox...

x.o.x.ox.x
```

### 输出

```
o.xx..ox..

..o.xx.o.x

-xxoo...o.

o..x.ox.x.

..o.o+.ox.

..x..oo..x

.o.x.xxo..

x.+xo-xxoo

.o..oox+++

x.o.x.ox.x
```

## 样例 #2

### 输入

```
.oo...x....xoo.xooooo.xx..xxo..xx.xoox.o..x..oo.o.

o..ox.xoxxox.xo..ooxx.ox.o.xooo.....x...ooxxo.o..x

x...x..oxxox.o..oxox.xoxo...oxo..oo....oxx.x...x.x

.xoo.........xo.xxx...x.o.xoox...o.o.x..ox.xx.oxo.

o.x...x.x.o.o...xo..oxxxo.xoo.xo.xo.ox.o...o...o..

xo.o.x..o.xx..o.....x..o.o....x.....ooo.oo.ooxx..o

.xx.o.xoo.x.xxx.x.o.xxoo.ox.o.oo.x.xxo..ox.x.o.o.o

.ox.o..xxo.ooxo.x.x.xx.xx.x...ooo.o..x....xo....ox

xx..ox.xx.x.x...ooxxox.oxx.o.oo.xo.o..x.x.xx..xxx.

o....o..x..xoxxx....o....x....x.o.o.x....ooo...o..

.xo.x...xox.............xo..xo....x..xoo.xx...x.ox

.oxxxxx.xx..o.oxoxx...x...x..x.oxxoxxo..oxx..xx...

.o..x.x.o...x..oo..o.x..xxox..o.oo.....x..x..o.oo.

ox.xo.xx.x..xo.oxooo..o.xxo.xox.o.x..xoo..o.x..oo.

.xoox...xoox...ooxx......o.oox....x.x.ox..o.ox.o.x

.o..x.xx..x....o..x.ox...oxooo....x..x.......o..x.

.o.xx..x..ox...o.o.xoo..oxx..oxo.oo..o.x.o.o....oo

x..xx.....x...o.xx.x..xo..x.oxx...xo.o...xx...xo.o

xx.oox.oxxo...ox...o.x..xo.oooxo..x..ox.ox...o...x

.oo...o.....o...xooxoxox.x.x...oo..xo.x.oo.x.xxxo.

oox..o.x.xo...oox.x..x..o.x.xxxo.x.x...o.o..o.....

xo.xx.o.x.xx.xo..oox..o..xoo...xo.o..ooo......oxox

.o..xx..xxo.....x...o.x..xxoxooxo..ooo.xx.....x..o

o..o.x..x.o.ox.oxx.o.xo.xox.o....o.o.x.ox...x.xox.

...o..oxoooo.x.o..oo....xo.xxxxxox..o.o.o....oo.o.

.xxo..x.x.oxoo.x.o....xxoxoo...ooxx.ox...ooo..x.x.

.xo..xxx.o..ox.oo....oox...xxo...oxx.o.ooo.o...oox

....ox.x.oo.o.x..x....o...o...x.oxx.oxo..o...oooo.

xxx..ox...x.x.x.o.x......xx..xx.ox.x......o.x..o.x

...oox.xox.ox.xx.x....x.oxxx..xxoxo.o.o....oxx...x

xoo.....ooxxxoxxxxx.....oxxx.....x..x...x..o.x..oo

..xo.oooxo...xx..x....x..oox.x.oxooo.oxoox...oxxo.

...ox.o.xo.oxxx....o..xooxox..x.xo...oo.xooo.x.xox

xx..o.oo...ox.x.x.ooxxxox...o..ox...ox....xx..xo..

xx.ooo..o.xoox.x.oox.o.xxxoooox.o..oo..x.x.xx....o

.oo...oxo.x.o.xx.o..xoxxox..x.xx.......xoxoxx.oxoo

...ox.ooooo.xxx.x..o.x.x.....xo..oo.xx..xo....ooox

.o.xx..o..xoxxo.xoo..xooo.xx.ox.xxxo.o.xo..o...x..

.xx...xoo.x.x.o.xo.o.xoxxo..oxo.ox....xoox.ox.xxxo

x.x..xox.....oxo..oo.ooxo...xo...ox.o..oo....ox.xo

.xx....xx.o....x.xoo.x.x.oxxooxxo..x..x..xxxxxo.ox

.o.x.x..x.oxoxx.xo..ox...ox.o......x.xxo...oo.oxx.

xx.xoxo.oo....ooxoxxxxxxxxoxxxx...oxx.o..oo.xo..xo

xx....o.o.xo.oox...o..o.x..o..x..x..xoxooxo.ox.oox

o.x..o.x..o.oo..ooo.x.......x.xx.o...oo..ox.x.xxx.

.xxoxoxxoo.o.o......xx..xxo.x....oox.x.xo.x..x....

oxx.oox....oxxx....x.oox..o.xx..xoxx.x.oo.o.o.x..x

....x.x.ox.xooxo.x..x.xo....oxoo..o.x.oo..o..x..x.

..o.o.xx....o...oooo...x.oox..oxox.x.x.x.xx...o.oo

..x.o.xo...xxx.x.ox.....oxo..ooxo..x.o.x..ooooxxox
```

### 输出

```
.oo...x....xoo.xooooo.xx..xxo..xx.xoox.o..x..oo.o.

o..ox.xoxxox.xo..ooxx.ox.o.xooo.....x...ooxxo.o..x

x...x..oxxox.o..oxox.xoxo...oxo..oo....oxx.x...x.x

.xoo.........xo.xxx...x.o.xoox...o.o.x..ox.xx.oxo.

o.x...x.x.o.o...xo..oxxxo.xoo.xo.xo.ox.o...o...o..

xo.o.x..o.xx..o.....x..o.o....x.....ooo.oo.ooxx..o

.xx.o.xoo.x.xxx.x.o.xxoo.ox.o.oo.x.xxo..ox.x.o.o.o

.ox.o..xxo.ooxo.x.x.xx.xx.x...ooo.o..x....xo....ox

xx..ox.xx.x.x...ooxxox.oxx.o.oo.xo.o..x.x.xx..xxx.

o....o..x..xoxxx....o....x....x.o.o.x....ooo...o..

.xo.x...xox.............xo..xo....x..xoo.xx...x.ox

.oxxxxx.xx..o.oxoxx...x...x..x.oxxoxxo..oxx..xx...

.o..x.x.o...x..oo..o.x..xxox..o.oo.....x..x..o.oo.

ox.xo.xx.x..xo.oxooo..o.xxo.xox.o.x..xoo..o.x..oo.

.xoox...xoox...ooxx......o.oox....x.x.ox..o.ox.o.x

.o..x.xx..x....o..x.ox...oxooo....x..x.......o..x.

.o.xx..x..ox...o.o.xoo..oxx..oxo.oo..o.x.o.o....oo

x..xx.....x...o.xx.x..xo..x.oxx...xo.o...xx...xo.o

xx.oox.oxxo...ox...o.x..xo.oooxo..x..ox.ox...o...x

.oo...o.....o...xooxoxox.x.x...oo..xo.x.oo.x.xxxo.

oox..o.x.xo...oox.x..x..o.x.xxxo.x.x...o.o..o.....

xo.xx.o.x.xx.xo..oox..o..xoo...xo.o..ooo......oxox

.o..xx..xxo.....x...o.x..xxoxooxo..ooo.xx.....x..o

o..o.x..x.o.ox.oxx.o.xo.xox.o....o.o.x.ox...x.xox.

...o..oxoooo.x.o..oo....xo.xxxxxox..o.o.o....oo.o.

.xxo..x.x.oxoo.x.o....xxoxoo...ooxx.ox...ooo..x.x.

.xo..xxx.o..ox.oo....oox...xxo...oxx.o.ooo.o...oox

....ox.x.oo.o.x..x....o...o...x.oxx.oxo..o...oooo.

xxx..ox...x.x.x.o.x......xx..xx.ox.x......o.x..o.x

...oox.xox.ox.xx.x....x.oxxx..xxoxo.o.o....oxx...x

xoo.....ooxxxoxxxxx.....oxxx.....x..x...x..o.x..oo

..xo.oooxo...xx..x....x..oox.x.oxooo.oxoox...oxxo.

...ox.o.xo.oxxx....o..xooxox..x.xo...oo.xooo.x.xox

xx..o.oo...ox.x.x.ooxxxox...o..ox...ox....xx..xo..

xx.ooo..o.xoox.x.oox.o.xxxoooox.o..oo..x.x.xx....o

.oo...oxo.x.o.xx.o..xoxxox..x.xx.......xoxoxx.oxoo

...ox.ooooo.xxx.x..o.x.x.....xo..oo.xx..xo....ooox

.o.xx..o..xoxxo.xoo..xooo.xx.ox.xxxo.o.xo..o...x..

.xx...xoo.x.x.o.xo.o.xoxxo..oxo.ox....xoox.ox.xxxo

x.x..xox.....oxo..oo.ooxo...xo...ox.o..oo....ox.xo

.xx....xx.o....x.xoo.x.x.oxxooxxo..x..x..xxxxxo.ox

.o.x.x..x.oxoxx.xo..ox...ox.o......x.xxo...oo.oxx.

xx.xoxo.oo....ooxoxxxxxxxxoxxxx...oxx.o..oo.xo..xo

xx....o.o.xo.oox...o..o.x..o..x..x..xoxooxo.ox.oox

o.x..o.x..o.oo..ooo.x.......x.xx.o...oo..ox.x.xxx.

.xxoxoxxoo.o.o......xx..xxo.x....oox.x.xo.x..x....

oxx.oox....oxxx....x.oox..o.xx..xoxx.x.oo.o.o.x..x

....x.x.ox.xooxo.x..x.xo....oxoo..o.x.oo..o..x..x.

..o.o.xx....o...oooo...x.oox..oxox.x.x.x.xx...o.oo

..x.o.xo...xxx.x.ox.....oxo..ooxo..x.o.x..ooooxxox
```



---

---
title: "人気投票ゲーム"
layout: "post"
diff: 入门
pid: AT_code_thanks_festival_14_qualb_c
tag: ['概率论']
---

# 人気投票ゲーム

## 题目描述

在某个国家，“狐狸派”和“兔子派”正在进行人气投票。你作为“狐狸派”的参谋，需要考虑怎样才能在这次的人气投票中获胜。

这个国家共有$N$个地区，每个地区都会进行投票。这里给出各个地区的总投票数和其中“狐狸派”的得票数，请你编写一个程序，计算“狐狸派”获得过半数选票的地区个数。

但请注意：“过半数”表示比一半大的数量。

例如，总投票数为$100100$时，得票数为$5050$也不能说是过半数。

## 输入格式

第$1$行一个整数$N(1\le n\le 100)$。表示地区的个数。

第$2$行，有$N$个整数。其中第$i（1\le i\le N）$个数为$V_i(1\le \ V_i\le\ 1000）$，表示第$i$个地区的总投票数。

在第$3$行中，有$N$个整数。其中第$i（1\le i\le N）$个数$F_i(0\le \ F_i\le \ V_i）$，表示第$i$个地区的“狐狸派”的得票数。

## 输出格式

输出共$1$行，为“狐狸派”获得过半数投票的地区的个数。

输出结束后要换行。

#### 样例1解释

在第$1$个地区和第$4$个地区，“狐狸派”获得了过半数的票，所以输出$2$。在第$3$个地区，“狐狸派”正好获得了总投票数的一半的票，但是没有过半数，请注意不要记录上。

#### 样例2解释

只有在第$3$个地区，“狐狸派”获得了过半数的票。

## 样例 #1

### 输入

```
5

150 130 100 200 150

100 60 50 101 70
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5

5 4 3 2 1

2 2 2 1 0
```

### 输出

```
1
```



---

---
title: "天下一人力比較"
layout: "post"
diff: 入门
pid: AT_tenka1_2013_qualB_a
tag: ['字符串', '排序', '概率论']
---

# 天下一人力比較

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tenka1-2013-qualb/tasks/tenka1_2013_qualB_a

下記の文字列が標準入力から与えられる。問題文においてカズキ君の渡された文字列と同じである。

 ```

ABGGEGBCFEBFBAF
FFGFACCCECDGCDGAFFFACGDA
EEDCAEAFBDDEEDGGA
GDCAGFFAACBGEDBAFBCDECGAE
EDB
GADGADEDBCGABDDCBBDBEAD
GADBB
DFCE
BFGCGCBEDC
EDGADBGGDDFEEGGFDGCAFBFGFAAD
DDAEBGACDFDGDAB
EEDCECFFAE
ADDBEEABFEAB
FEEBFDGAADAE
GB
```

 辞書順比較で $ 7 $ 番目に小さい文字列を標準出力に $ 1 $ 行で出力せよ。  
 なお、行の終端には改行が必要である。

## 说明/提示

### 辞書順比較について

 天下一株式会社に勤めるカズキ君は、以下の文字列の中から辞書順比較で $ 7 $ 番目に小さいものを選ぶという仕事を言い渡された。

 あなたは唖然とするカズキ君を助けるためにプログラムを書いて、答えを見つけることにした。

- ABGGEGBCFEBFBAF
- FFGFACCCECDGCDGAFFFACGDA
- EEDCAEAFBDDEEDGGA
- GDCAGFFAACBGEDBAFBCDECGAE
- EDB
- GADGADEDBCGABDDCBBDBEAD
- GADBB
- DFCE
- BFGCGCBEDC
- EDGADBGGDDFEEGGFDGCAFBFGFAAD
- DDAEBGACDFDGDAB
- EEDCECFFAE
- ADDBEEABFEAB
- FEEBFDGAADAE
- GB

- - - - - -

 文字列 $ A $ に対して、 $ A_i $ で $ i $ 番目の文字を表し、 $ |A| $ で文字列 $ A $ の文字数を表すことにすると、文字列 $ A $ と文字列 $ B $ を辞書順比較で比較するとは、

- $ A_i\ \neq\ B_i $ となる最小の $ i $ $ (1\ \leq\ i\ \leq\ {\rm\ min}(|A|,\ |B|)) $に対して
- $ A_i\ であれば、文字列\ A $ は文字列 $ B $ より小さい
- $ A_i\ >\ B_i $ であれば、文字列 $ A $ は文字列 $ B $ より大きい

- そのような $ i $ が存在しなければ、文字数が少ない方を小さいとする

 として文字列 $ A $ と文字列 $ B $ の大小関係を決めることである。

 なお、アルファベットの大小関係は、 `A` $ \lt{} $ `B` $ \lt{} $ `C` $ \lt{} $ $ ... $ $ \lt{} $ `Y` $ \lt{} $ `Z` である。  
 例えば、 `AA`, `B`, `BA`, `AB`, `A` の中から辞書順比較で $ 3 $ 番目に小さいものは `AB`である。(`A` $ \lt{} $ `AA` $ \lt{} $ `AB` $ \lt{} $ `B` $ \lt{} $ `BA` である。)



---

---
title: "プログラミングコンテスト"
layout: "post"
diff: 入门
pid: AT_utpc2011_1
tag: ['数学', '枚举', '概率论']
---

# プログラミングコンテスト

## 题目描述

[problemUrl]: https://atcoder.jp/contests/utpc2011/tasks/utpc2011_1





---

