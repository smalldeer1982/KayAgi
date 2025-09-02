# [ABC296F] Simultaneous Swap

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc296/tasks/abc296_f

長さ $ N $ の数列 $ A=(A_1,A_2,\ldots,A_N) $, $ B=(B_1,B_2,\ldots,B_N) $ が与えられます。

高橋君は次の操作を好きなだけ ($ 0 $ 回でも良い) 繰り返す事ができます。

> $ 1 $ 以上 $ N $ 以下の、どの $ 2 $ つも互いに相異なる $ 3 $ つの整数 $ i,j,k $ を選ぶ。  
>  $ A $ の $ i $ 番目の要素と $ j $ 番目の要素を交換し、$ B $ の $ i $ 番目の要素と $ k $ 番目の要素を交換する。

高橋君がうまく操作を繰り返すことによって、 $ A $ と $ B $ を一致させる事が可能ならば `Yes` を、不可能ならば `No` を出力してください。  
 ただし、$ A $ と $ B $ が一致しているとは、任意の $ 1\leq\ i\leq\ N $ について $ A $ の $ i $ 番目の要素と $ B $ の $ i $ 番目の要素が等しいことを言います。

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i,B_i\leq\ N $
- 入力はすべて整数
 
### Sample Explanation 1

$ (i,j,k)=(1,2,3) $ として $ 1 $ 回操作を行うことで、$ A_1 $ と $ A_2 $、$ B_1 $ と $ B_3 $ がそれぞれ交換され、 $ A,B $ はともに $ (2,1,1) $ となって一致します。よって、`Yes` を出力します。

### Sample Explanation 2

どのように操作を行っても $ A $ と $ B $ を一致させることはできません。よって、`No` を出力します。

## 样例 #1

### 输入

```
3
1 2 1
1 1 2```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3
1 2 2
1 1 2```

### 输出

```
No```

## 样例 #3

### 输入

```
5
1 2 3 2 1
3 2 2 1 1```

### 输出

```
Yes```

## 样例 #4

### 输入

```
8
1 2 3 4 5 6 7 8
7 8 5 6 4 3 1 2```

### 输出

```
No```

# 题解

## 作者：氧少Kevin (赞：8)

# ABC296F - Simultaneous Swap
- https://atcoder.jp/contests/abc296/tasks/abc296_f
- 逆序对、归纳法

## 题意
分别给出两个长度均为 $n(n\leq 2\cdot 10^5)$ 的序列 $a_i$ 和 $b_i$，可以进行如下操作：
- 选择三个互不相同的数字 $i,j,k$，交换 $a_i$ 和 $a_j$ 的值，交换 $b_i$ 和 $b_k$ 的值。

问：是否可以通过有限次数的操作，使得 $\forall i \in [1,n]$ 有 $a_i=b_i$。

## 思路
首先，若对 $a_i$ 和 $b_i$ 排序后，$a_i$ 和 $b_i$ 仍不相同，则一定不行。

注意到有：
$$a_i = \quad \overgroup{A\ B\ C}$$
$$b_i = \quad \overgroup{A\ B}\ C$$

$$\downarrow$$

$$a_i = \quad \overgroup{C\ B\ A}$$
$$b_i = \quad B \overgroup{A\ C}$$

$$\downarrow$$

$$a_i = \quad A\ B\ C$$
$$b_i = \quad B\ C\ A$$

对于某个 $(i,j,k)(i<j<k)$，能够通过两次操作，做到 $(a_i,a_j,a_k)$ 不变，而 $(b_i,b_j,b_k)$ 轮换，即：$(b_i,b_j,b_k)\rightarrow (b_j,b_k,b_i)$。

### 如果序列中无重复元素

如果序列中无重复元素，不难发现，对于元素两两不同的三元组 $(b_i,b_j,b_k)$，$(b_i,b_j,b_k)\rightarrow (b_j,b_k,b_i)$ 的过程会让三元组 $(b_i,b_j,b_k)$ 的逆序对数量 $+2$ 或者 $-2$，逆序对数量的奇偶性不变。

所以，在序列中无重复元素的情况下，如果 $a_i$ 和 $b_i$ 的逆序对数量奇偶性相同，则可以通过有限次数的操作让两个序列相同。

### 如果序列中有重复元素

如果序列中有重复元素，不难发现，对于其中有恰好两个元素相同的三元组 $(b_i,b_j,b_k)$，$(b_i,b_j,b_k)\rightarrow (b_j,b_k,b_i)$ 的过程会让三元组 $(b_i,b_j,b_k)$ 的逆序对数量 $+1$ 或者 $-1$。

所以，在序列中有重复元素的情况下，一定可以通过有限次数的操作让两个序列相同。

---

## 作者：Register_int (赞：2)

首先判掉数字不同的情况。

接下来考虑分别对这两个数列排序。如果 $A$ 或 $B$ 中有任意重复元素，那么都可以通过反复横跳这两个元素来完成排序。否则，我们需要两者排序次数的奇偶性相同，直接计算逆序对即可。

# AC 代码

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int MAXN = 2e5 + 10;
const int inf = ~0u >> 1;
 
int n, c[MAXN];
 
inline 
int lowbit(int k) {
	return k & -k;
}
 
inline 
void add(int k) {
	for (int i = k; i <= 2e5; i += lowbit(i)) c[i]++;
}
 
inline 
int ask(int k) {
	int res = 0;
	for (int i = k; i; i -= lowbit(i)) res += c[i];
	return res;
}
 
int a[MAXN], b[MAXN], cnt1[MAXN], cnt2[MAXN], ans;
 
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), cnt1[a[i]]++, ans |= cnt1[a[i]] > 1;
	for (int i = 1; i <= n; i++) scanf("%d", &b[i]), cnt2[b[i]]++, ans |= cnt2[b[i]] > 1;
	for (int i = 1; i <= n; i++) if (cnt1[i] != cnt2[i]) return puts("No"), 0;
	if (ans) return puts("Yes"), 0;
	for (int i = n; i; i--) ans ^= ask(a[i] - 1) & 1, add(a[i]);
	for (int i = 1; i <= n; i++) c[i] = 0;
	for (int i = n; i; i--) ans ^= ask(b[i] - 1) & 1, add(b[i]);
	puts(ans ? "No" : "Yes");
}
```

---

## 作者：__Aaaaaaaa (赞：1)

题面翻译：给定两个长度为 $n$ 的序列 $a$ 和 $b$  
操作可以视为一个三元组 $(i,j,k)$ (其中 $i \neq j , j \neq k , i \neq k$) ,表示将 $a$ 序列的第 $i$ 个数和第 $k$ 个数交换位置，并且将 $b$ 序列的第 $j$ 个数和 第 $k$ 个数交换位置。  
判定两个序列能否通过若干次交换后相等。

如果 $a$ 和 $b$ 的元素集是不一样的，即存在一个数 $x$ 使得 $a$ 中 $x$ 的数量与 $b$ 中 $x$ 的数量不相等，则无论如何操作都不能使得 $a$ 和 $b$ 相等。


以下考虑 $a$ 和 $b$ 的元素集相等的情况。  
不难发现一个结论，以 $a$ 序列为“参照物”，那么对于每次操作，可以视为 $a$  不变，$b$ 交换了两次序列中元素的位置。

如果序列中含重复元素，那么可以很轻易的做到每次操作只交换一次元素位置（另一次交换相同元素的位置），那么肯定可以通过操作使得两个序列相等。  
否则，每次必须交换两个位置的元素，逆序对的增减一定是 $2$，那么以 $a$ 为字典序算出 $b$ 的逆序对，最后判定这个逆序对的奇偶即可。
### Don't talk much:
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N=2e5+10;
int n,a[N],b[N],c1[N],c2[N],pos[N];
int tr[N];
void insert(int x,int d){
	for(int i=x;i<=n;i+=i&-i)
		tr[i]+=d;
}
int query(int x){
	int res=0;
	for(int i=x;i;i^=i&-i)
		res+=tr[i];
	return res;
}
bool flag;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	for(int i=1;i<=n;i++)
		scanf("%d",b+i);
	for(int i=1;i<=n;i++)
		c1[a[i]]++;
	for(int i=1;i<=n;i++)
		c2[b[i]]++;
	for(int i=1;i<=n;i++)
		if(c1[i]!=c2[i]){//元素集不同，一定不可能
			puts("No");
			return 0;
		}
		else if(c1[i]>1)//一定可能的情况
			flag=true;
	if(flag){
		puts("Yes");
		return 0;
	}
	for(int i=1;i<=n;i++)
		pos[a[i]]=i;
	for(int i=1;i<=n;i++)//以a为字典序重排b
		b[i]=pos[b[i]];
	ll res=0;
	for(int i=1;i<=n;i++){//求出b的逆序对数量
		res+=query(n)-query(b[i]);
		insert(b[i],1);
	}
	if(res&1)
		puts("No");
	else
		puts("Yes");
	return 0;
}
```

---

