---
title: "Puzzles"
layout: "post"
diff: 普及+/提高
pid: CF696B
tag: []
---

# Puzzles

## 题目描述

Barney lives in country USC (United States of Charzeh). USC has $ n $ cities numbered from $ 1 $ through $ n $ and $ n-1 $ roads between them. Cities and roads of USC form a rooted tree (Barney's not sure why it is rooted). Root of the tree is the city number $ 1 $ . Thus if one will start his journey from city $ 1 $ , he can visit any city he wants by following roads.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF696B/ba3e1e6f719802c9fe4b318c8d8513024bc088eb.png)Some girl has stolen Barney's heart, and Barney wants to find her. He starts looking for in the root of the tree and (since he is Barney Stinson not a random guy), he uses a random DFS to search in the cities. A pseudo code of this algorithm is as follows:

```plain
let starting_time be an array of length n
current_time = 0
dfs(v):
	current_time = current_time + 1
	starting_time[v] = current_time
	shuffle children[v] randomly (each permutation with equal possibility)
	// children[v] is vector of children cities of city v
	for u in children[v]:
		dfs(u)
```

As told before, Barney will start his journey in the root of the tree (equivalent to call dfs(1)).

Now Barney needs to pack a backpack and so he wants to know more about his upcoming journey: for every city $ i $ , Barney wants to know the expected value of starting\_time\[i\]. He's a friend of Jon Snow and knows nothing, that's why he asked for your help.

## 输入格式

The first line of input contains a single integer $ n $ ( $ 1<=n<=10^{5} $ ) — the number of cities in USC.

The second line contains $ n-1 $ integers $ p_{2},p_{3},...,p_{n} $ ( $ 1<=p_{i}&lt;i $ ), where $ p_{i} $ is the number of the parent city of city number $ i $ in the tree, meaning there is a road between cities numbered $ p_{i} $ and $ i $ in USC.

## 输出格式

In the first and only line of output print $ n $ numbers, where $ i $ -th number is the expected value of starting\_time\[i\].

Your answer for each city will be considered correct if its absolute or relative error does not exceed $ 10^{-6} $ .

## 样例 #1

### 输入

```
7
1 2 1 1 4 4

```

### 输出

```
1.0 4.0 5.0 3.5 4.5 5.0 5.0 

```

## 样例 #2

### 输入

```
12
1 1 2 2 4 4 3 3 1 10 8

```

### 输出

```
1.0 5.0 5.5 6.5 7.5 8.0 8.0 7.0 7.5 6.5 7.5 8.0 

```

