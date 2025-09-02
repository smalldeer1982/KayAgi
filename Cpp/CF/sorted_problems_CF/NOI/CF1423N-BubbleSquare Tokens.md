---
title: "BubbleSquare Tokens"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1423N
tag: []
---

# BubbleSquare Tokens

## 题目描述

BubbleSquare social network is celebrating $ 13^{th} $ anniversary and it is rewarding its members with special edition BubbleSquare tokens. Every member receives one personal token. Also, two additional tokens are awarded to each member for every friend they have on the network. Yet, there is a twist – everyone should end up with different number of tokens from all their friends. Each member may return one received token. Also, each two friends may agree to each return one or two tokens they have obtained on behalf of their friendship.

## 输入格式

First line of input contains two integer numbers $ n $ and $ k $ ( $ 2 $ $ \leq $ $ n $ $ \leq $ $ 12500 $ , $ 1 $ $ \leq $ $ k $ $ \leq $ $ 1000000 $ ) - number of members in network and number of friendships.

Next $ k $ lines contain two integer numbers $ a_i $ and $ b_i $ ( $ 1 $ $ \leq $ $ a_i $ , $ b_i $ $ \leq $ $ n $ , $ a_i $ $ \neq $ $ b_i $ ) - meaning members $ a_i $ and $ b_i $ are friends.

## 输出格式

First line of output should specify the number of members who are keeping their personal token.

The second line should contain space separated list of members who are keeping their personal token.

Each of the following $ k $ lines should contain three space separated numbers, representing friend pairs and number of tokens each of them gets on behalf of their friendship.

## 说明/提示

In the first test case, only the first member will keep its personal token and no tokens will be awarded for friendship between the first and the second member.

In the second test case, none of the members will keep their personal token. The first member will receive two tokens (for friendship with the third member), the second member will receive one token (for friendship with the third member) and the third member will receive three tokens (for friendships with the first and the second member).

## 样例 #1

### 输入

```
2 1
1 2
```

### 输出

```
1
1 
1 2 0
```

## 样例 #2

### 输入

```
3 3
1 2
1 3
2 3
```

### 输出

```
0
1 2 0
2 3 1
1 3 2
```

