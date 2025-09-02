---
title: "DoubleCamelCase Sort"
layout: "post"
diff: 普及-
pid: AT_past201912_f
tag: ['模拟']
---

# DoubleCamelCase Sort

## 题目描述

[problemUrl]: https://atcoder.jp/contests/past201912-open/tasks/past201912_f

文字列 $ S $ が与えられる。これは、$ 1 $ つ以上の単語を (間に空白などを挟まずに) 連結したものである。ここで、各単語は $ 2 $ 文字以上であり、最初の文字と最後の文字のみが英大文字、それ以外の文字は全て英小文字である。

これらの単語を辞書順に並べ (大文字小文字の違いは無視する)、同様に連結して出力するプログラムを作成せよ。

例えば、$ S\ = $ `FisHDoGCaTAAAaAAbCAC` とする。これは `FisH`, `DoG`, `CaT`, `AA`, `AaA`, `AbC`, `AC` の $ 7 $ つの単語を連結したものである。これらを辞書順に並べると `AA`, `AaA`, `AbC`, `AC`, `CaT`, `DoG`, `FisH` となるため、`AAAaAAbCACCaTDoGFisH` と出力すればよい。

## 输入格式

入力は以下の形式で標準入力から与えられる。

> $ S $

## 输出格式

問題文で指示された通りの文字列を出力せよ。

## 说明/提示

### 注意

この問題に対する言及は、2019年12月29日 05:00 JST まで禁止されています。言及がなされた場合、賠償が請求される可能性があります。

試験後に総合得点や認定級を公表するのは構いませんが、どの問題が解けたかなどの情報は発信しないようにお願いします。

### 制約

- $ S $ は長さ $ 2 $ 以上 $ 100,000 $ 以下の文字列である。
- $ S $ の各文字は英大文字または英小文字である。
- $ S $ は問題文で述べたような単語の連結である。

### Sample Explanation 1

問題文で用いた例である。

### Sample Explanation 2

同じ単語が複数個存在する可能性があることに注意せよ。

## 样例 #1

### 输入

```
FisHDoGCaTAAAaAAbCAC
```

### 输出

```
AAAaAAbCACCaTDoGFisH
```

## 样例 #2

### 输入

```
AAAAAjhfgaBCsahdfakGZsZGdEAA
```

### 输出

```
AAAAAAAjhfgaBCsahdfakGGdEZsZ
```

