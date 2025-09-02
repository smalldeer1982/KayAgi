---
title: "東京都"
layout: "post"
diff: 普及-
pid: AT_kupc2015_a
tag: []
---

# 東京都

## 题目描述

[problemUrl]: https://atcoder.jp/contests/kupc2015/tasks/kupc2015_a

KUPC2015は[東京](https://atnd.org/events/70910)と[京都](https://atnd.org/events/70909)の二箇所でオンサイトが開催されている． あなたはKUPCの告知を手伝うことにした． 英小文字からなる文字列が印字されたテープがある．あなたはこのテープを文字同士の間でのみ好きなだけ自由に切ってもよい． あなたは`tokyo`か`kyoto`のいずれかの文字列を含むテープをなるべくたくさん作りたい．ただし，一旦切ったテープを後でくっつけることはできないものとする． 作る事ができる`tokyo`もしくは`kyoto`を含むテープの数の最大値を出力せよ．

## 输入格式

入力は以下の形式で標準入力から与えられる．

> $ T $ $ S_1 $ : $ S_T $

- $ 1 $ 行目にはテストケースの数を表す整数 $ T $ ( $ 1\ \leq\ T\ \leq\ 100 $ ) が与えられる．
- 続いて $ T $ 個のテストケースが順に与えられ， $ i $ ( $ 1\ \leq\ i\ \leq\ T $ ) 行目には英小文字のみからなる文字列 $ S_i $ が与えられる．
- 各文字列の長さは $ 1 $ 以上 $ 100 $ 以下であることが保証される．

## 输出格式

出力は $ T $ 行からなる．各テストケースに対する答えのみを順に出力せよ．

## 说明/提示

### Sample Explanation 1

`higashikyoto`と書かれたテープは`kyoto`を含んでいるので，そのまま切り分けなくても目的のテープが $ 1 $ つ得られる． `kupconsitetokyotokyoto`と書かれたテープを{`kupconsitetokyo`, `to`, `kyoto`}と切り分けると，目的のテープが $ 2 $ つ得られる． どう切り分けても目的のテープが得られない場合も存在しうる．

## 样例 #1

### 输入

```
3
higashikyoto
kupconsitetokyotokyoto
goodluckandhavefun
```

### 输出

```
1
2
0
```

