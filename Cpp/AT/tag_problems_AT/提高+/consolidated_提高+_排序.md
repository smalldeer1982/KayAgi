---
title: "[AGC040B] Two Contests"
layout: "post"
diff: 提高+/省选-
pid: AT_agc040_b
tag: ['排序', '分类讨论']
---

# [AGC040B] Two Contests

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc040/tasks/agc040_b

$ 1 $ から $ 10^9 $ までの番号のついた $ 10^9 $ 人が参加する大会があります． この大会では，$ 2 $ 回のコンテストが行われます．

コンテストで出題する問題として，$ 1 $ から $ N $ までの番号のついた $ N $ 問が準備されています． 問題 $ i $ が出題された場合，番号が $ L_i $ 以上 $ R_i $ 以下の参加者は全員正解し，逆にそれ以外の参加者は誰も解けません．

これらの $ N $ 問を，$ 2 $ 回のコンテストに分けて出題します． どの問題も，ちょうど $ 1 $ 回のコンテストで出題されなくてはいけません． また，どちらのコンテストも，少なくとも $ 1 $ 問以上の問題が出題される必要があります．

それぞれのコンテストの**楽しさ**は，そのコンテストの全ての問題を解く参加者の人数です． $ 2 $ 回のコンテストの楽しさの和としてありうる最大の値を求めてください．

## 输入格式

入力は以下の形式で標準入力から与えられる．

> $ N $ $ L_1 $ $ R_1 $ $ L_2 $ $ R_2 $ $ \vdots $ $ L_N $ $ R_N $

## 输出格式

$ 2 $ 回のコンテストの楽しさの和としてありうる最大の値を出力せよ．

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ L_i\ \leq\ R_i\ \leq\ 10^9 $
- 入力される値はすべて整数である．

### Sample Explanation 1

以下のようにするのが最適です． - $ 1 $ 回目のコンテストで問題 $ 1,3 $ を出題する．人 $ 5,6,7 $ がこのコンテストの問題を全て解くので，コンテストの楽しさは $ 3 $ である． - $ 2 $ 回目のコンテストで問題 $ 2,4 $ を出題する．人 $ 2,3,4 $ がこのコンテストの問題を全て解くので，コンテストの楽しさは $ 3 $ である． - $ 2 $ 回のコンテストの楽しさの和が $ 6 $ になる．楽しさの和を $ 6 $ より大きくすることは出来ない．

## 样例 #1

### 输入

```
4

4 7

1 4

5 8

2 5
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4

1 20

2 19

3 18

4 17
```

### 输出

```
34
```

## 样例 #3

### 输入

```
10

457835016 996058008

456475528 529149798

455108441 512701454

455817105 523506955

457368248 814532746

455073228 459494089

456651538 774276744

457667152 974637457

457293701 800549465

456580262 636471526
```

### 输出

```
540049931
```



---

---
title: "[ARC053C] 魔法使い高橋君"
layout: "post"
diff: 提高+/省选-
pid: AT_arc053_c
tag: ['贪心', '排序']
---

# [ARC053C] 魔法使い高橋君

## 题目描述

高桥君会 $N$ 个魔法。将这些魔法分别编号为 $1$ 到 $N$ 。

开始时，气温为 $0$ 度。高桥君咏唱第 $i$ 个魔法后，气温会先上升 $a_i$ 度再下降 $b_i$ 度。

高桥君会将所有魔法都咏唱一遍。这期间气温的最大值为 $X$ 度。高桥君可以自己决定咏唱魔法的顺序，来使 $X$ 的值尽量小。

求最小的 $X$ 值。

## 输入格式

输入按以下形式：
$$ N $$
$$ a_1 \space b_1 $$
$$ : $$
$$ a_N \space b_N $$

## 输出格式

输出 $X$ 的最小值。

## 输入输出样例
### 输入样例1
```
1
10 20
```
### 输出样例1
```
10
```
### 样例解释1
咏唱唯一一个魔法。气温的变化如下：$0 → 10 → -10$ 。
### 输入样例2
```
2
30 20
10 20
```
### 输出样例2
```
20
```
### 样例解释2
先咏唱第 $2$ 个魔法，再咏唱第 $1$ 个魔法，气温变化如下： $0 →10 → -10 → 20 → 0$ 。
### 输入样例3
```
5
5 10
10 5
10 15
15 10
20 20
```
### 输出样例3
```
10
```
### 样例解释3
举例来说，可以按 $1,3,5,2,4$ 的顺序咏唱魔法。

## 说明/提示

- $1 \le N \le 10^5$
- $a_i,b_i$ 都是整数。
- $1 \le a_i,b_i \le 10^9$



---

---
title: "[ARC082F] Sandglass"
layout: "post"
diff: 提高+/省选-
pid: AT_arc082_d
tag: ['线段树', '排序']
---

# [ARC082F] Sandglass

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc082/tasks/arc082_d

パーツAとパーツBからなる砂時計があります。これらのパーツにはいくらかの砂が入っています。 砂時計を置くときはパーツAとパーツBのどちらかが上になり、そうでないほうが下になります。

$ 1 $ 秒間に $ 1 $ \[g\] の砂が上にあるパーツから下にあるパーツに落ちます。 ただし、上のパーツにもう砂が残っていない場合は砂は落ちません。

はじめ時刻 $ 0 $ にパーツAが上にあり、$ a $ \[g\] の砂がパーツAに入っていて、$ X-a $ \[g\] の砂がパーツBに入っています(すなわち、合計 $ X $ \[g\] の砂が入っています)。

時刻 $ r_1,r_2,\ ..,\ r_K $ に砂時計をひっくり返します。この操作は瞬間的に行われ、時間はかからないものとします。なお、時刻 $ t $ とは時刻 $ 0 $ の $ t $ 秒後を指します。

クエリが $ Q $ 個与えられます。 各クエリは $ (t_i,a_i) $ の形をしています。 各クエリに対し、$ a=a_i $ だとして、時刻 $ t_i $ にパーツAに入っている砂の量が何gか答えてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ X $ $ K $ $ r_1 $ $ r_2 $ .. $ r_K $ $ Q $ $ t_1 $ $ a_1 $ $ t_2 $ $ a_2 $ $ : $ $ t_Q $ $ a_Q $

## 输出格式

各クエリの答えを $ 1 $ 行ごとに出力せよ。

## 说明/提示

### 制約

- $ 1\ <\ =X\ <\ =10^9 $
- $ 1\ <\ =K\ <\ =10^5 $
- $ 1\ <\ =r_1\ <\ r_2\ <\ ..\ <\ r_K\ <\ =10^9 $
- $ 1\ <\ =Q\ <\ =10^5 $
- $ 0\ <\ =t_1\ <\ t_2\ <\ ..\ <\ t_Q\ <\ =10^9 $
- $ 0\ <\ =a_i\ <\ =X\ (1\ <\ =i\ <\ =Q) $
- 入力値はすべて整数

### Sample Explanation 1

$ 1 $ つめのクエリでは、はじめパーツAに $ 90 $ \\\[g\\\] 入っていた砂が $ 30 $ \\\[g\\\] 減り、$ 60 $ \\\[g\\\] になります。 $ 2 $ つめのクエリでは、はじめパーツAに入っていた $ 1 $ \\\[g\\\] の砂がパーツBに落ちた後、$ 59 $ 秒間変化は起こりません。ここで砂時計をひっくり返し、その $ 1 $ 秒後にパーツAに入っている砂の量を聞かれているため、答えは $ 1 $ \\\[g\\\] になります。

### Sample Explanation 2

どのクエリでもはじめにパーツAに入っている砂は $ 100 $ \\\[g\\\] で、砂時計をひっくり返す前の時間での値を聞いています。

## 样例 #1

### 输入

```
180

3

60 120 180

3

30 90

61 1

180 180
```

### 输出

```
60

1

120
```

## 样例 #2

### 输入

```
100

1

100000

4

0 100

90 100

100 100

101 100
```

### 输出

```
100

10

0

0
```

## 样例 #3

### 输入

```
100

5

48 141 231 314 425

7

0 19

50 98

143 30

231 55

342 0

365 100

600 10
```

### 输出

```
19

52

91

10

58

42

100
```



---

---
title: "[ARC154D] A + B > C ?"
layout: "post"
diff: 提高+/省选-
pid: AT_arc154_d
tag: ['排序']
---

# [ARC154D] A + B > C ?

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc154/tasks/arc154_d

PCT 君は $ (1,2,\dots,N) $ の順列 $ (P_1,P_2,\dots,P_N) $ を持っています。あなたには $ N $ のみが伝えられます。

あなたは PCT 君に以下の質問を $ 25000 $ 回以下行うことができます。

- $ 1\ \le\ i,j,k\ \le\ N $ を満たす整数の組 $ (i,j,k) $ を $ 1 $ 個指定し、$ P_i\ +\ P_j\ >\ P_k $ かどうかを聞く。
 
$ P_1,P_2,\dots,P_N $ を全て求めてください。

### Input &amp; Output Format

**この問題はインタラクティブな問題**（あなたの作成したプログラムとジャッジプログラムが入出力を介して対話を行う形式の問題）である。

まず、あなたのプログラムに標準入力から順列の長さ $ N $ が与えられる。

> $ N $

その後、あなたは質問を行うことが出来る。 質問は標準出力に以下の形式で出力せよ。(末尾に改行を入れること。)

> ? $ i $ $ j $ $ k $

質問が正当な場合、その質問の答え $ ans $ が標準入力から与えられる。

> $ ans $

ここで、$ ans $ は `Yes` または `No` である。

質問のフォーマットが間違っている、または質問を規定の回数より多く行ったという理由で質問が不正と判断された場合、`-1` が標準入力から与えられる。

 ```
-1
```

この時、提出はすでに不正解と判定されている。ジャッジプログラムはこの時点で対話を終了するため、あなたのプログラムも終了するのが望ましい。

$ P_1,P_2,\dots,P_N $ が全て分かったら、標準出力に以下の形式で出力せよ。(末尾に改行を入れること。)

> ! $ P_1 $ $ P_2 $ $ \dots $ $ P_N $

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 2000 $
- $ P $ はプログラムとジャッジの対話の開始前に決定される。
 
### ジャッジ

- **出力を行うたびに、末尾に改行を入れて標準出力を flush せよ。そうしなかった場合、ジャッジ結果が TLE となる可能性がある。**
- 答えを出力したら(または `-1` を受け取ったら)直ちにプログラムを正常終了せよ。そうしなかった場合、ジャッジ結果は不定である。
- 余計な改行は不正なフォーマットの出力とみなされることに注意せよ。
 
### 入出力例

以下は、$ N\ =\ 4,P=(3,1,2,4) $ の場合の入出力例です。

    入力 出力 説明     `4`  $ N $ が与えられます。    `?` `1` `2` `3` $ 1 $ 個目の質問として、$ P_1\ +\ P_2\ >\ P_3 $ かどうかを聞きます。   `Yes`  $ P_1\ +\ P_2=4,P_3=2 $ であるため、返答は `Yes` です。     `?` `2` `3` `3` $ 2 $ 個目の質問として、$ P_2\ +\ P_3\ >\ P_3 $ かどうかを聞きます。   `Yes`  $ P_2\ +\ P_3=3,P_3=2 $ であるため、返答は `Yes` です。     `?` `2` `3` `4` $ 3 $ 個目の質問として、$ P_2\ +\ P_3\ >\ P_4 $ かどうかを聞きます。   `No`  $ P_2\ +\ P_3=3,P_4=4 $ であるため、返答は `No` です。     `!` `3` `1` `2` `4` $ P_1,P_2,P_3,P_4 $ を出力します。実際に、$ P=(3,1,2,4) $ であるため、AC となります。



---

---
title: "[ARC179C] Beware of Overflow"
layout: "post"
diff: 提高+/省选-
pid: AT_arc179_c
tag: ['贪心', '二分', '排序']
---

# [ARC179C] Beware of Overflow

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc179/tasks/arc179_c

この問題は**インタラクティブな問題**（あなたの作成したプログラムとジャッジシステムが入出力を介して対話を行う形式の問題）です.

正整数 $ N $ が与えられます.

ジャッジシステムは正整数 $ R $ および $ N $ 個の整数 $ A_1,A_2,\dots\ ,A_N $ を隠し持っています. ここで $ |A_i|\le\ R,\ \left|\displaystyle\sum_{i=1}^{N}A_i\right|\ \le\ R $ を満たすことが保証されます.

絶対値が $ R $ 以下の整数しか書き込むことができない黒板があり, はじめは何も書き込まれていません.

ジャッジシステムは, 黒板に $ A_1,A_2,\ \dots\ ,A_N $ の値を **この順で** 書き込みました. あなたは, 黒板にただ $ 1 $ つの値 $ \displaystyle\sum_{i=1}^{N}A_i $ が書き込まれている状態にする必要があります.

あなたは $ R $ および $ A_i $ の値を直接知ることはできませんが, その代わりにジャッジシステムに対して次のやり取りを $ 25000 $ 回まで行うことができます.

正整数 $ i $ について, $ i $ 番目に黒板に書き込まれた整数を $ X_i $ とします. 特に, $ i=1,2,\dots\ ,N $ について $ X_i=A_i $ です.

$ 1 $ 回のやり取りでは, 相異なる正整数 $ i,j $ を指定し, 次のいずれかを選んで行います.

- 足し算をしてもらう. ジャッジシステムは黒板から $ X_i,X_j $ を消し, 新たに $ X_i+X_j $ の値を黒板に書き込む.
  - $ |X_i+X_j|\le\ R $ を満たしていなくてはならない.
- 大小比較をしてもらう. ジャッジシステムは $ X_i\lt\ X_j $ の真偽を答える.

ただし, 各やり取りを始める時点で $ i,j $ 番目に黒板に書き込まれた整数がすでに黒板から消されていてはなりません.

適切にやり取りを行って, 全てのやり取りを終えた後に黒板にただ $ 1 $ つの値 $ \displaystyle\sum_{i=1}^{N}A_i $ が書き込まれている状態にしてください.

$ R $ および $ A_i $ はプログラムとジャッジシステムの対話の開始前に決定されます.

### Input &amp; Output Format

この問題はインタラクティブな問題（あなたの作成したプログラムとジャッジシステムが入出力を介して対話を行う形式の問題）です.

最初に, $ N $ を標準入力から受け取ってください.

> $ N $

次に, 黒板にただ $ 1 $ つの値 $ \displaystyle\sum_{i=1}^{N}A_i $ が書かれている状態になるまで, やり取りを繰り返してください.

足し算をしてもらうときは, 以下の形式で標準出力に出力してください. 末尾に改行を入れてください. ここで $ i,j $ は相異なる正整数です.

> + $ i $ $ j $

これに対するジャッジシステムの応答は, 次の形式で標準入力から与えられます.

> $ P $

ここで $ P $ は整数で,

- $ P\geq\ N+1 $ の場合は, $ X_i+X_j $ の値が黒板に書き込まれ, それが $ P $ 番目に書き込まれたことを表します.
- $ P=-1 $ の場合は, $ i,j $ が制約を満たしていないか, やり取りの回数が $ 25000 $ 回を超えたことを表します.

大小比較をしてもらうときは, 以下の形式で標準出力に出力してください. 末尾に改行を入れてください. ここで $ i,j $ は相異なる正整数です.

> ? $ i $ $ j $

これに対するジャッジシステムの応答は, 次の形式で標準入力から与えられます.

> $ Q $

ここで $ Q $ は整数で,

- $ Q=1 $ の場合は, $ X_i\ <\ X_j $ が真であることを表します.
- $ Q=0 $ の場合は, $ X_i\ <\ X_j $ が偽であることを表します.
- $ Q=-1 $ の場合は, $ i,j $ が制約を満たしていないか, やり取りの回数が $ 25000 $ 回を超えたことを表します.

足し算をしてもらうやり取りおよび大小比較をしてもらうやり取りのいずれについても, ジャッジシステムの応答が $ -1 $ であった場合は, プログラムはすでに不正解とみなされています. この場合, ただちにプログラムを終了してください.

黒板にただ $ 1 $ つの値 $ \displaystyle\sum_{i=1}^{N}A_i $ が書かれている状態になったら, 以下の形式でそのことをジャッジシステムに報告してください. ただし, これはジャッジシステムとのやり取りの回数に計上されません. その後, ただちにプログラムを終了してください.

```
!
```

上記のいずれの形式にも当てはまらない出力を行った場合は, `-1` が標準入力から与えられます.

```
-1
```

このときも, プログラムはすでに不正解とみなされています. ただちにプログラムを終了してください.

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 1000 $
- $ 1\leq\ R\leq\ 10^9 $
- $ |A_i|\leq\ R $
- $ \left|\displaystyle\sum_{i=1}^{N}A_i\right|\ \le\ R $
- $ N,R,A_i $ は整数.

### 注意点

- **出力を行うたびに, 末尾に改行を入れて標準出力を flush してください. そうしなかった場合, ジャッジ結果が TLE となる可能性があります.**
- 解答を出力したら（または `-1` を受け取ったら）ただちにプログラムを終了してください. そうしない場合, ジャッジ結果は不定です.
- 余計な改行は不正なフォーマットの出力とみなされることに注意してください.

### 入出力例

$ N=3,R=10,A_1=-1,A_2=10,A_3=1 $ のときの対話の一例を示します.

入力出力説明`3`まず整数 $ N $ が与えられます。`? 1 2`大小比較をしてもらいます.`1`$ X_1\lt\ X_2\ (-1\lt\ 10) $ なのでジャッジシステムは $ 1 $ を返します. `+ 1 3`足し算をしてもらいます.`4`ジャッジシステムは $ X_1=-1,X_3=1 $ を黒板から消し, $ X_1+X_3=0 $ の値を黒板に書き込みました. $ 4 $ 番目の書き込みでした.`+ 2 4`足し算をしてもらいます.`5`ジャッジシステムは $ X_2=10,X_4=0 $ を黒板から消し, $ X_2+X_4=10 $ の値を黒板に書き込みました. $ 5 $ 番目の書き込みでした.`!`黒板にはただ $ 1 $ つの値 $ \displaystyle\sum_{i=1}^{N}A_i $ が書き込まれている状態になったので, そのことをジャッジシステムに報告します.



---

---
title: "Dictionary for Shiritori Game"
layout: "post"
diff: 提高+/省选-
pid: AT_code_festival_2015_okinawa_d
tag: ['博弈论', '拓扑排序']
---

# Dictionary for Shiritori Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2015-okinawa-open/tasks/code_festival_2015_okinawa_d



## 输入格式

Inputs will be given by standard input in following format.

> $ N $ $ M $ $ p_1 $ $ q_1 $ $ p_2 $ $ q_2 $ : $ p_M $ $ q_M $

- At the first line, an integer $ N(1≦N≦100,000) $、$ M(1≦M≦200,000) $ will be given.
- From the second line there are $ M $ lines that represent all the words in this dictionary. For the $ i_{th} $ line, integer $ p_i(1≦p_i≦N) $ and $ q_i(1≦q_i≦N) $ will be given divided by space.

It is possible that there are different words that begin with the same character and end with the same character. In other words, it is possible that $ p_i\ =\ p_j $ and $ q_i\ =\ q_j $ even when $ i\ \neq\ j $.

## 输出格式

Assume that two players will try their best. Output `Snuke` if the first player wins, output `Sothe` if the second player wins in one line. If the game will never halt, output `Draw` in one line.

Print a newline at the end of output.

## 说明/提示

### Problem

In a country where $ N $ different kinds characters are being used, there is a dictionary that contains $ M $ entries, each entry is a definition for a word. All the kinds of characters are listed as character $ 1 $, character $ 2 $, ..., character $ N $. The $ i_{th} $ entry (as a word) of this dictionary begins with the letter $ p_i $, and ends with the letter $ q_i $.

 Cat Snuke and Wolf Sothe will use this dictionary to play a game called **Shiritori** . (Please note that Shiritori in this game is different from a normal Shiritori game.)

- The first move will be made by Cat Snuke, then two players will move alternately.
- For the first move, the player in turn has to say a word the begins with character $ 1 $. If there are no any words that begin with character $ 1 $, the player in turn loses.
- For the rest moves, the player of that turn has to say any word that begins with the last character of the word being said in the previous move from the dictionary. If there is not any appropriate word, the player in turn loses.
- **Any word can be said any number of times** .

There should be some dictionaries that two players can not change the result of the game even if they tried their best. For these dictionaries, in this case, we want to find out if the first player or the second player will win, or even the game will never halt.

All the words in the dictionary will be given. We can assume that the two players will try their best. Please decide if the first player (Cat Snuke) or the second player (Wolf Sothe) will win, or even the game will never halt.

### Sample Explanation 1

\- For the first move, Cat Snuke has to say the first word. - For the second move, if Wolf Sothe said the 6th word, Cat Snuke will have no appropriate word to say for the next move, thus Wolf Sothe wins.

### Sample Explanation 4

Please note that for the first move it is possible that there is no appropriate word that can be said.

## 样例 #1

### 输入

```
6 5

1 2

2 3

3 4

4 2

2 5
```

### 输出

```
Sothe
```

## 样例 #2

### 输入

```
6 6

1 2

2 3

3 4

4 2

2 5

5 6
```

### 输出

```
Draw
```

## 样例 #3

### 输入

```
6 8

1 2

1 3

3 4

3 5

2 1

4 5

4 6

5 6
```

### 输出

```
Snuke
```

## 样例 #4

### 输入

```
4 8

2 3

2 3

3 4

4 1

3 1

2 2

4 2

4 3
```

### 输出

```
Sothe
```



---

