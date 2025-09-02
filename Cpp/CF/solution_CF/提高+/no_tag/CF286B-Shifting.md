# Shifting

## 题目描述

John Doe has found the beautiful permutation formula.

Let's take permutation $ p=p_{1},p_{2},...,p_{n} $ . Let's define transformation $ f $ of this permutation:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF286B/25e74201607d55d0e22ffd7930ca53b5830fbc7a.png)where $ k $ $ (k&gt;1) $ is an integer, the transformation parameter, $ r $ is such maximum integer that $ rk<=n $ . If $ rk=n $ , then elements $ p_{rk+1},p_{rk+2} $ and so on are omitted. In other words, the described transformation of permutation $ p $ cyclically shifts to the left each consecutive block of length $ k $ and the last block with the length equal to the remainder after dividing $ n $ by $ k $ .

John Doe thinks that permutation $ f(f( ... f(p=[1,2,...,n],2) ... ,n-1),n) $ is beautiful. Unfortunately, he cannot quickly find the beautiful permutation he's interested in. That's why he asked you to help him.

Your task is to find a beautiful permutation for the given $ n $ . For clarifications, see the notes to the third sample.

## 说明/提示

A note to the third test sample:

- $ f([1,2,3,4],2)=[2,1,4,3] $
- $ f([2,1,4,3],3)=[1,4,2,3] $
- $ f([1,4,2,3],4)=[4,2,3,1] $

## 样例 #1

### 输入

```
2
```

### 输出

```
2 1 
```

## 样例 #2

### 输入

```
3
```

### 输出

```
1 3 2 
```

## 样例 #3

### 输入

```
4
```

### 输出

```
4 2 3 1 
```

# 题解

## 作者：pythoner713 (赞：3)

去年集训时做过这题，~~水一波原来写的题解~~：

>这道题理解起来容易，写起来就难了。看一眼测试数据，1≤ n ≤10^6，这是在要求我们写$O(n\log{n})$的算法啊。可是如果直接模拟的话，需要迭代n次，每次数组中的n个数每个数都要移动至少一位，怎么着也得$O(n^2)$，如何优化呢？下面是一位dalao给出的解决方案：

>就设n=6吧，一开始这个数组是这样的：

$$1,2,3,4,5,6$$

>但是我们不这么开，我们开一个两倍长度的数组，后面的n位全空着先：

$$1,2,3,4,5,6,0,0,0,0,0,0$$

>这时候k从2开始，一直枚举到6，每次都将数组带入$f(A,k)$算一次。让我们观察一下题目“也就是把a 分段，每段k 个（最后如果不足k 个，全部分到新的一段里，见样例），然后将每段的第一个移动到该段的最后一个”，那么很容易得出如果i%k=1，那么$A_i$是要被移到该段的最后一个的。那么我们先把要移动的数标记一下：

$$\textcolor{red}1,2,\textcolor{red}3,4,\textcolor{red}5,6,0,0,0,0,0,0$$

>这时候如果我们把每个标记的数都移到下一个标记的数（其中最后一个标记的数移到序列尾）的话......

$$0,2,\textcolor{red}1,4,\textcolor{red}3,6,\textcolor{red}{5},0,0,0,0,0$$

>就会惊奇地发现新序列就相当于把$f(A,2)$向右移了一位！如此，我们还可以对k=3时进行相同的操作：

$$0,\textcolor{red}2,1,4,\textcolor{red}3,6,5,0,0,0,0,0$$
$$\downarrow$$
$$0,0,1,4,\textcolor{red}2,6,5,\textcolor{red}3,0,0,0,0$$

>是不是很神奇？！接下来的操作同理：

$$0,0,\textcolor{red}1,4,2,6,\textcolor{red}5,3,0,0,0,0$$
$$\downarrow$$
$$0,0,0,4,2,6,\textcolor{red}1,3,\textcolor{red}5,0,0,0$$
$$\downarrow$$
$$0,0,0,\textcolor{red}4,2,6,1,3,\textcolor{red}5,0,0,0$$
$$\downarrow$$
$$0,0,0,0,2,6,1,3,\textcolor{red}4,\textcolor{red}5,0,0$$
$$\downarrow$$
$$0,0,0,0,\textcolor{red}2,6,1,3,4,5,0,0$$
$$\downarrow$$
$$0,0,0,0,0,6,1,3,4,5,\textcolor{red}2,0$$

>完啦！最终结果就是6,1,3,4,5,2了！时间复杂度$O(n\log{n})$搞定！剩下的就是写代码和调试了~

---

```cpp
#include<bits/stdc++.h>
using namespace std;

int ans[2000010];

int main(){
	int i, k, N, shift = 0;
	cin >> N;
	memset(ans, 0, sizeof(ans));
	for(i = 1; i <= N; i++){
		ans[i] = i;
	}
	for(k = 2; k <= N; k++){
		ans[N + shift + 1] = ans[N + shift + 1 - (N - (N / k) * k)];
		for(i = (N / k) * k + shift + 1; i >= shift + 1; i -= k){
			ans[i] = ans[i - k];
		}
		shift++;
	}
	for(i = shift + 1; i <= N + shift; i++){
		cout << ans[i] << " ";
	}
	return 0;
}
```

---

## 作者：kimidonatsu (赞：1)

观察最后的排列 $p$ 形如：

$$p_2, p_3, p_4, \dots, p_k, p_1, p_{k + 2}, p_{k + 3}, \dots, p_{2k}, p_{k + 1}, \dots, p_{rk + 2}, \dots, p_{n}, p_{rk + 1}$$

可以发现发生位置变化的只有：

* $p_1 \to p_{k + 1}$
* $p_{k + 1} \to p_{2k + 1}$
* $\dots$

从头到尾遍历一遍一小块一小块处理就可以了。

数组大小记得开两倍。

[Submission](https://codeforces.com/contest/286/submission/268333369)

---

