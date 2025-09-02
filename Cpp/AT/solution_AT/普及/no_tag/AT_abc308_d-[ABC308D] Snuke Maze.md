# [ABC308D] Snuke Maze

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc308/tasks/abc308_d

$ H $ 行 $ W $ 列のグリッドがあります。 以下、上から $ i $ 行目、左から $ j $ 列目のマスを $ (i,j) $ と表記します。 グリッドの各マスには英小文字が書かれており、$ (i,j) $ に書かれた文字は与えられる文字列 $ S_i $ の $ j $ 文字目と一致します。

すぬけくんは、辺で隣接するマスに移動することを繰り返して $ (1,1) $ から $ (H,W) $ まで移動しようと思っています。 訪れるマス （最初の $ (1,1) $ と 最後の $ (H,W) $ を含む）に書かれた文字が、 訪れる順に `s` $ \rightarrow $ `n` $ \rightarrow $ `u` $ \rightarrow $ `k` $ \rightarrow $ `e` $ \rightarrow $ `s` $ \rightarrow $ `n` $ \rightarrow\ \dots $ となるような経路が存在するか判定してください。 なお、$ 2 $ つのマス $ (i_1,j_1),(i_2,j_2) $ は $ |i_1-i_2|+|j_1-j_2|\ =\ 1 $ を満たすとき、またそのときに限り「辺で隣接する」といいます。

より厳密には、マスの列 $ ((i_1,j_1),(i_2,j_2),\dots,(i_k,j_k)) $ であって以下の条件を全て満たすものが存在するか判定してください。

- $ (i_1,j_1)\ =\ (1,1),(i_k,j_k)\ =\ (H,W) $
- すべての $ t\ (1\ \leq\ t\ <\ k) $ について、$ (i_t,j_t) $ と $ (i_{t+1},j_{t+1}) $ は辺で隣接する
- すべての $ t\ (1\ \leq\ t\ \leq\ k) $ について、$ (i_t,j_t) $ に書かれた文字は `snuke` の $ ((t-1)\ \bmod\ 5)\ +\ 1 $ 文字目と一致する

## 说明/提示

### 制約

- $ 2\leq\ H,W\ \leq\ 500 $
- $ H,W $ は整数
- $ S_i $ は英小文字からなる長さ $ W $ の文字列
 
### Sample Explanation 1

$ (1,1)\ \rightarrow\ (1,2)\ \rightarrow\ (2,2)\ \rightarrow\ (2,3) $ という経路は、訪れたマスに書かれた文字が訪れた順に `s` $ \rightarrow $ `n` $ \rightarrow $ `u` $ \rightarrow $ `k` となるため条件を満たします。

## 样例 #1

### 输入

```
2 3
sns
euk```

### 输出

```
Yes```

## 样例 #2

### 输入

```
2 2
ab
cd```

### 输出

```
No```

## 样例 #3

### 输入

```
5 7
skunsek
nukesnu
ukeseku
nsnnesn
uekukku```

### 输出

```
Yes```

# 题解

## 作者：Elairin176 (赞：5)

[传送门](https://www.luogu.com.cn/problem/AT_abc308_d)     
bfs 水题。    
## 题意
从左上角到右下角，判断顺序形如 `snukesnuke...` 的顺序是否存在。          
## 解法
我们这题可以用 dfs 也可以用 bfs，这里介绍 bfs 写法。          
我们设 `snuke` 为 $s$，请注意这里的下标从 $0$ 开始。       
我们每次记录 $3$ 个信息：$x$ 坐标，$y$ 坐标，$t$。$t$ 指这个坐标是 $s_t$。    
那么我们初始需要特判一下：如果左上角的位置就不是 `s`，那么肯定无解。         
我们很容易发现下一个格子的 $t$ 值应该是 $(t+1)\bmod 5$。        
之后我们进行 bfs 即可。      
时间复杂度为 $O(nm)$，可以通过。      
[CODE](https://www.luogu.com.cn/paste/amhejvzj)

---

