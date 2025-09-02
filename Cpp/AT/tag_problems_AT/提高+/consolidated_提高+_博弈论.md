---
title: "[AGC033C] Removing Coins"
layout: "post"
diff: 提高+/省选-
pid: AT_agc033_c
tag: ['博弈论', '树的直径']
---

# [AGC033C] Removing Coins

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc033/tasks/agc033_c

高橋君と青木君は木を用いてゲームをすることにしました。 ゲームに用いる木は $ N $ 頂点からなり、各頂点には $ 1 $ から $ N $ の番号が割り振られています。 また、$ N-1 $ 本の辺のうち、 $ i $ 本目の辺は頂点 $ a_i $ と頂点 $ b_i $ を結んでいます。

ゲーム開始時、各頂点にはコインが一枚ずつ置いてあります。 高橋君と青木君は高橋君から始めて以下の操作を交互に行い、操作を行えなくなった方が負けになります。

- コインが置いてある頂点を一つ選び、その頂点 $ v $ に置いてあるコインをすべて取り除く。
- その後、木上に残っているコインをすべて、今置いてある頂点に隣接する頂点のうち $ v $ に一番近い頂点に移動させる。

つまり、木上にコインが残っていない状態で手番となった人の負けです。 二人が最適に行動したとき、どちらが勝つか求めてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ N $ $ a_1 $ $ b_1 $ $ a_2 $ $ b_2 $ : $ a_{N-1} $ $ b_{N-1} $

## 输出格式

先手の高橋君が勝つなら `First` を、後手の青木君が勝つなら `Second` を出力せよ。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 2\ \times\ 10^5 $
- $ 1\ ≦\ a_i,\ b_i\ ≦\ N $
- $ a_i\ \neq\ b_i $
- 入力で与えられるグラフは木である。

### Sample Explanation 1

ゲームは例えば以下のように進行します。 - 高橋君が頂点 $ 1 $ からコインを取り除く。操作後は、頂点 $ 1 $ に一つ、頂点 $ 2 $ に一つコインがある。 - 青木君が頂点 $ 2 $ からコインを取り除く。操作後は、頂点 $ 2 $ に一つコインがある。 - 高橋君が頂点 $ 2 $ からコインを取り除く。操作後は、木上にコインは残っていない。 - 青木君は木上にコインがない状態で手番となってしまったので、負けとなる。

## 样例 #1

### 输入

```
3

1 2

2 3
```

### 输出

```
First
```

## 样例 #2

### 输入

```
6

1 2

2 3

2 4

4 6

5 6
```

### 输出

```
Second
```

## 样例 #3

### 输入

```
7

1 7

7 4

3 4

7 5

6 3

2 1
```

### 输出

```
First
```



---

---
title: "[ARC137C] Distinct Numbers"
layout: "post"
diff: 提高+/省选-
pid: AT_arc137_c
tag: ['贪心', '博弈论']
---

# [ARC137C] Distinct Numbers

## 题目描述

给定长为 $N$ 的非负整数列 $A=(A_1,\dots,A_N)$，保证 $A$ 中元素互不相同。

Alice 和 Bob 在玩游戏。Alice 为先手，两人轮流操作。每次操作选手可以如下进行：

+ 选择当前 $A$ 中最大的元素，将其替换为一个更小的非负整数。要求替换后 $A$ 中元素仍然互不相同。

首先无法操作的一方失败。当两人都采取最优策略时，求谁有必胜策略。

## 输入格式

第一行一个正整数 $N$；

第二行 $N$ 个非负整数表示 $A_1,\dots,a_N$。

## 输出格式

如果 Alice 有必胜策略则输出 `Alice`，如果 Bob 有必胜策略则输出 `Bob`。

## 说明/提示

+ $2 \le N \le 3 \times 10^5$

+ $0 \le A_1<A_2<\dots<A_N\le10^9$

#### 样例 1 解释

第一回合 Alice 可以将 $4$ 变为 $0,1,3$，如果 Alice 将 $4$ 变为 $0,1$ 中的一个，则 Bob 可以将 $2$ 变为 $0,1$ 中另一个，Alice 无法操作从而落败；如果 Alice 将 $4$ 变为 $3$，则此时 Bob 需要将 $3$ 变为 $0,1$ 中一个，同上知 Bob 必败。因此 Alice 有必胜策略。

## 样例 #1

### 输入

```
2

2 4
```

### 输出

```
Alice
```

## 样例 #2

### 输入

```
3

0 1 2
```

### 输出

```
Bob
```



---

---
title: "[ARC170D] Triangle Card Game"
layout: "post"
diff: 提高+/省选-
pid: AT_arc170_d
tag: ['贪心', '博弈论']
---

# [ARC170D] Triangle Card Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc170/tasks/arc170_d

Alice と Bob でゲームをします．

はじめ，Alice, Bob はそれぞれ $ N $ 枚のカードを持っていて，Alice が持っている $ i $ 番目のカードには整数 $ A_i $ が，Bob が持っている $ i $ 番目のカードには整数 $ B_i $ が書かれてます．

ゲームは以下の手順で行われます．

- 何も書かれていない黒板を用意する．
- Alice が持っているカードを一枚食べ，食べたカードに書かれた整数を黒板に書く．
- 次に，Bob が持っているカードを一枚食べ，食べたカードに書かれた整数を黒板に書く．
- 最後に，Alice が持っているカードを一枚食べ，食べたカードに書かれた整数を黒板に書く．
 
黒板に書かれた $ 3 $ 個の整数を $ 3 $ 辺の長さとする（非退化な）三角形が存在すれば Alice の勝ちで，そうでないとき Bob の勝ちです．

両者が最適な行動をするとき，どちらが勝つか判定してください．

$ T $ 個のテストケースが与えられるので，それぞれについて答えてください．

## 输入格式

入力は以下の形式で標準入力から与えられる．

> $ T $ $ \mathrm{case}_1 $ $ \vdots $ $ \mathrm{case}_T $

各ケースは以下の形式で与えられる．

> $ N $ $ A_1 $ $ \ldots $ $ A_N $ $ B_1 $ $ \ldots $ $ B_N $

## 输出格式

$ T $ 行出力せよ．$ i $ 行目 $ (1\ \leq\ i\ \leq\ T) $ には， $ i $ 番目のテストケースについて，Alice が勝つ場合 `Alice` を，Bob が勝つ場合 `Bob` を出力せよ．

## 说明/提示

### 制約

- $ 1\ \leq\ T\ \leq\ 10^5 $
- $ 2\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i,B_i\leq\ 10^9 $
- 入力される数値は全て整数
- $ 1 $ つの入力に含まれるテストケースについて，$ N $ の総和は $ 2\times\ 10^5 $ 以下
 
### Sample Explanation 1

$ 1 $ 番目のテストケースでは，例えばゲームは以下のように進行します． - Alice が $ 2 $ を書かれたカードを食べ，黒板に $ 2 $ を書く． - Bob が $ 4 $ を書かれたカードを食べ，黒板に $ 4 $ を書く． - Alice が $ 1 $ を書かれたカードを食べ，黒板に $ 1 $ を書く． - 黒板に書かれた数は $ 2,4,1 $ であり，$ 3 $ 辺の長さが $ 2,4,1 $ であるような三角形は存在しないので Bob の勝ちとなる． このテストケースについて，上記の手順が必ずしも両者にとって最適な行動とは限りませんが，両者が最適な行動をした場合勝利するのは Bob であることが示せます．

## 样例 #1

### 输入

```
3

3

1 2 3

4 5 6

4

6 1 5 10

2 2 4 5

10

3 1 4 1 5 9 2 6 5 3

2 7 1 8 2 8 1 8 2 8
```

### 输出

```
Bob

Alice

Alice
```



---

---
title: "[ARC186C] Ball and Box"
layout: "post"
diff: 提高+/省选-
pid: AT_arc186_c
tag: ['贪心', '博弈论']
---

# [ARC186C] Ball and Box

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc186/tasks/arc186_c

球橋さんと箱木さんはボールと箱を使ったゲームをします。

最初、球橋さんは $ M $ 種類のボールをそれぞれ $ 10^{100} $ 個ずつ持っていて、 箱木さんは $ 10^{100} $ 円持っています。 また、$ N $ 個の箱があり、$ i $ 番目の箱の容量は $ V_i $ で、値段は $ P_i $ 円です。ゲーム中、箱木さんはいつでも好きな箱を買うことができます。

このゲームでは、ゲームが終わるまで以下の操作を繰り返します。

1. 球橋さんはボールを $ 1 $ つ選び、箱木さんに渡す。
2. 箱木さんは渡されたボールを受け取るか、受け取らずにゲームを終えるかを選ぶ。
3. ボールを受け取った場合、箱木さんは購入済みの箱を $ 1 $ つ選び、受け取ったボールを入れる。
4. ボールを入れた箱が以下の条件を満たしている場合、箱木さんは $ 1 $ 円をもらう。そうでない場合、ゲームを終える。
  - 箱の中のボールの個数は、その箱の容量以下である。
  - 箱の中のボールの種類は、すべて同じである。

球橋さんは、ゲーム終了時の箱木さんの所持金がなるべく少なくなるための最適な行動をし、反対に、箱木さんはなるべく多くなるための最適な行動をします。 ゲームを通して、箱木さんの所持金はいくら増えますか？

ただし、両者ともにすべての情報が公開されているとします。特に、球橋さんは、それぞれの箱について、容量と値段、どの種類のボールがいくつ入っているかを見ることができます。 また、箱木さんの初期の所持金は十分多く、お金が足りなくて箱が買えなくなることはないことに注意してください。

$ 1 $ つの入力ファイルにつき、$ T $ 個のテストケースを解いてください。

## 输入格式

入力は以下の形式で標準入力から与えられる。ここで $ \mathrm{case}_i $ は $ i $ 番目のテストケースを意味する。

> $ T $ $ \mathrm{case}_1 $ $ \mathrm{case}_2 $ $ \vdots $ $ \mathrm{case}_T $

各テストケースは以下の形式で与えられる。

> $ N $ $ M $ $ V_1 $ $ P_1 $ $ V_2 $ $ P_2 $ $ \vdots $ $ V_N $ $ P_N $

## 输出格式

両者が最適に行動したときの、箱木さんの最終的な所持金と最初の所持金の差を出力せよ。

## 说明/提示

### 制約

- $ 1\le\ T,N,M\le\ 3\times\ 10^5 $
- $ 1\le\ V_i,P_i\ \le\ 10^9 $
- $ T $ 個のテストケースに対する $ N $ の総和は $ 3\times\ 10^5 $ 以下
- 入力はすべて整数

### Sample Explanation 1

最初のテストケースでは $ 2 $ 種類のボールと $ 3 $ つの箱を使います。 $ 2 $ 種類のボールをそれぞれ白のボールと黒のボールと呼び、$ i $ 種類目の箱を箱 $ i $ と呼ぶことにします。 このテストケースについて、所持金が $ 2 $ 円増えるゲームの進み方の例を示します。 1. 球橋さんが白のボールを選び、渡す。 2. 箱木さんはボールを受け取り、箱 $ 2 $ を $ 1 $ 円で買って白のボールを入れる。 - 箱 $ 2 $ には白のボールが $ 1 $ 個入っている。これは条件を満たしているため、箱木さんは $ 1 $ 円をもらう。 3. 球橋さんが白のボールを選び、渡す。 4. 箱木さんはボールを受け取り、箱 $ 2 $ に白のボールを入れる。 - 箱 $ 2 $ には白のボールが $ 2 $ 個入っている。これは条件を満たしているため、箱木さんは $ 1 $ 円をもらう。 5. 球橋さんが黒のボールを選び、渡す。 6. 箱木さんはボールを受け取り、箱 $ 3 $ を $ 1 $ 円で買って黒のボールを入れる。 - 箱 $ 3 $ には黒のボールが $ 1 $ 個入っている。これは条件を満たしているため、箱木さんは $ 1 $ 円をもらう。 7. 球橋さんが白のボールを選び、渡す。 8. 箱木さんはボールを受け取り、箱 $ 2 $ に白のボールを入れる。 - 箱 $ 2 $ には白のボールが $ 3 $ 個入っている。これは条件を満たしているため、箱木さんは $ 1 $ 円をもらう。 9. 球橋さんが白のボールを選び、渡す。 10. 箱木さんは受け取らずにゲームを終えることを選ぶ。 最終的に、箱 $ 2 $ には白のボールが $ 3 $ 個、箱 $ 3 $ には黒のボールが $ 1 $ 個入っています。 合計で $ 2 $ 円使って $ 4 $ 円もらったので、所持金は $ 2 $ 円増えました。 $ 2 $ つめのテストケースでは、球橋さんは、箱木さんにお金を稼がせないような行動ができます。

## 样例 #1

### 输入

```
3
3 2
1 1000000000
3 1
3 1
1 300000
1000000000 1
10 4
22 5
26 45
72 21
47 39
97 2
75 35
82 24
17 46
32 22
28 67
```

### 输出

```
2
0
28
```



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

---
title: "素数取りゲーム"
layout: "post"
diff: 提高+/省选-
pid: AT_ttpc2019_d
tag: ['数学', '博弈论', '素数判断,质数,筛法', '位运算']
---

# 素数取りゲーム

## 题目描述

# 素数取り游戏



东工大的安酱和爱酱玩了一个叫做石头取走游戏的两人游戏，但是因为知道必胜法，所以不再感兴趣了。

于是，安酱考虑了一个基于素数的石头取回游戏，并将它命名为“素数取回游戏”。

素数取回游戏的规则如下：

- 开始时有 $N$ 堆小石子，在第 $i$ 堆中有 $X_i$ 个（$X_i$ 是素数）小石子。
- 两个玩家轮流选择存在小石堆的那一堆，并从那里拿走一些石子。
- **只能同时获取素数枚石子，并且在剩余的石子数量为 $0$ 或素数枚时才能继续进行**
- 先无法拿走石头的玩家输掉比赛。

虽然这条规则新颖，但似乎安和爱仍然知道怎样获胜。

请问当安穗是先手，爱穗是后手，面对由 $X_1$，$X_2$，$\ldots$，$X_N$ 个石头组成的 $N$ 堆石头时，假设他们采取最优策略，谁将获胜？

## 输入格式

从标准输入中按以下格式给出输入：

> $ N $ $ X_1 $ $ X_2 $ $ \ldots $ $ X_N $

## 输出格式

如果先手安穂赢了，输出 `An`；如果后手爱赢了，则输出 `Ai`。

## 样例 #1

### 输入

```
1

13
```

### 输出

```
An
```

## 样例 #2

### 输入

```
2

17 13
```

### 输出

```
An
```

## 样例 #3

### 输入

```
6

49529 868033 52361 519803 19289 386501
```

### 输出

```
Ai
```



---

