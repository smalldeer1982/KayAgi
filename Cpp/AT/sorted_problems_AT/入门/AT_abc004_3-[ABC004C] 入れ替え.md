---
title: "[ABC004C] 入れ替え"
layout: "post"
diff: 入门
pid: AT_abc004_3
tag: []
---

# [ABC004C] 入れ替え

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc004/tasks/abc004_3

ここにカードが $ 6 $ 枚あり、それぞれ $ 1 $ から $ 6 $ までの整数が書かれています。  
 最初、左から右へ $ 1 $ のカードから $ 6 $ のカードまでがソートされた状態で並んでいます。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc004_3/8f6ba0b6c718be3db1905de008024bbefd8f50fb.png)

 高橋君には整数 $ N $ が与えられます。高橋君は以下の操作を $ i\ =\ 0 $,$ 1 $,$ 2 $, $ ... $ ,$ N-1 $ に対して $ i\ =\ 0 $ から 順番に行います。 - 左から $ (i $ $ mod $ $ 5)+1 $ 番目にあるカードと、左から $ (i $ $ mod $ $ 5)+2 $ 番目にあるカードの位置を入れ替える。
 
 $ mod $ とは、「剰余」を意味し、例えば $ 8 $ $ mod $ $ 5 $ は $ 3 $ であり、$ 15 $ $ mod $ $ 5 $ は $ 0 $ になります。 ここで実際に $ N\ =\ 5 $ のときに行われる操作を例示します。

- $ i\ =\ 0 $ のとき：
 $ (0 $ $ mod $ $ 5)+1 $ $ = $ $ 1 $、$ (0 $ $ mod $ $ 5)+2 $ $ = $ $ 2 $ より、左から $ 1 $ 番目のカード」と、「左から $ 2 $ 番目のカード」を入れ替えます。  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc004_3/9910e34356f567b079a89cb95447c11e913234c1.png)

- $ i\ =\ 1 $ のとき：
 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc004_3/e27b53d42b3efae94e288c0b97bc34e8579fc6fa.png)

- $ i\ =\ 2 $ のとき：
 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc004_3/244c2ec6f9beac0be821d79d7edfd2b166b89e66.png)

- $ i\ =\ 3 $ のとき：
 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc004_3/fac73fa6d6792eacb6baf5a251dde745c56db6d2.png)

- $ i\ =\ 4 $ のとき：
 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc004_3/4b74bb2dc81c4ba42fb5807fe65b2ad2049f5331.png)

- よって、$ N=5 $ のとき、カードの並びは左から`234561`の順に並びます。
 
 あなたは高橋君の代わりに、上記の操作が全て終わった後のカードの並びを答えてください。 入力は以下の形式で標準入力から与えられる。 > $ N $

 $ 1 $ 行目には、高橋君に与えられた整数 $ N(1≦N≦10^9) $ を与える。 - この問題には部分点が設定されている。後述する部分点の項も参照すること。
 
 操作が終わった後のカードの並びを左から順に $ 1 $ 行で出力してください。  
 また、出力の末尾には改行を入れること。 $ 1≦N≦50 $ を満たすテストケース全てに正解すると、$ 100 $ 点満点のうち $ 30 $ 点が与えられる。

 ```
<pre class="prettyprint linenums">
1
```

 ```
<pre class="prettyprint linenums">
213456
```

- 「左から $ 1 $ 番目のカード」と、「左から $ 2 $ 番目のカード」を入れ替えます。
 
```
<pre class="prettyprint linenums">
5
```

 ```
<pre class="prettyprint linenums">
234561
```

- 問題文中で示した例です。
 
```
<pre class="prettyprint linenums">
22
```

 ```
<pre class="prettyprint linenums">
615234
```

 ```
<pre class="prettyprint linenums">
100000000
```

 ```
<pre class="prettyprint linenums">
345612
```

- $ N\ >\ 50 $ なので、部分点ではなく、満点解答のための入力になります。

