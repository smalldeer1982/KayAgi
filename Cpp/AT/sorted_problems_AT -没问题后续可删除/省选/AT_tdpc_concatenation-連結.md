---
title: "連結"
layout: "post"
diff: 省选/NOI-
pid: AT_tdpc_concatenation
tag: []
---

# 連結

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tdpc/tasks/tdpc_concatenation

入力は以下の形式で標準入力から与えられる。

> $ N $ $ L $ $ w_1 $ $ ... $ $ w_N $

 答えを一行に出力せよ。 ```

4 10
00
01
10
11
```

```

1024
```

```

3 5
01
10
0
```

```

14
```

## 说明/提示

### Constraints

 $ N $ 個の 0, 1 からなる文字列 $ w_1 $, ..., $ w_N $ がある。すぬけ君は、この中から文字列をいくつか選び、好きな順番で連結して文字列を作ることにした (同じ文字列を複数回選んでもよい)。このようにして作ることのできる長さ $ L $ の文字列の個数を mod 1,000,000,007 で求めよ。ただし、文字列として同じであれば、連結のしかたが異なるものも同じであるとみなす。

- - - - - -

- $ 1\ <\ =\ N\ <\ =\ 510 $
- $ 1\ <\ =\ |w_i|\ <\ =\ 8 $
- $ 1\ <\ =\ L\ <\ =\ 100 $
- Each character in $ w_i $ will be either '0' or '1'.
- $ w_i $ are pairwise distinct.

