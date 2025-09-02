# [ABC126F] XOR Matching

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc126/tasks/abc126_f

以下の条件を満たす、長さ $ 2^{M\ +\ 1} $ の数列 $ a $ = {$ a_1,\ a_2,\ ...,\ a_{2^{M\ +\ 1}} $} を、存在するならば $ 1 $ つ構築してください。

- $ a $ は $ 0 $ 以上 $ 2^M $ 未満の整数を、それぞれちょうど $ 2 $ つずつ含む。
- $ a_i\ =\ a_j $ を満たす任意の $ i,\ j\ (i\ <\ j) $ について、$ a_i\ xor\ a_{i\ +\ 1}\ xor\ ...\ xor\ a_j\ =\ K $ である。

xor (排他的論理和) とは

整数 $ c_1,\ c_2,\ ...,\ c_n $ の xor は以下のように定義されます。

- $ c_1\ xor\ c_2\ xor\ ...\ xor\ c_n $ を二進表記した際の $ 2^k $ ($ k\ \geq\ 0 $) の位の数は、$ c_1,\ c_2,\ ...,\ c_n $ のうち二進表記した際の $ 2^k $ の位の数が $ 1 $ となるものが奇数個ならば $ 1 $、偶数個ならば $ 0 $ である。

例えば、$ 3\ xor\ 5\ =\ 6 $ です (二進表記すると: `011` $ xor $ `101` $ = $ `110` です)。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 0\ \leq\ M\ \leq\ 17 $
- $ 0\ \leq\ K\ \leq\ 10^9 $

### Sample Explanation 1

このケースでは、条件を満たす数列は複数存在します。 例えば $ a $ = {$ 0,\ 0,\ 1,\ 1 $} の場合、$ a_i\ =\ a_j $ を満たす $ (i,\ j)\ (i\ <\ j) $ として $ (1,\ 2) $ と $ (3,\ 4) $ があります。$ a_1\ xor\ a_2\ =\ 0,\ a_3\ xor\ a_4\ =\ 0 $ であるため、この $ a $ は与えられた条件を満たしています。

### Sample Explanation 2

条件を満たす数列は存在しません。

### Sample Explanation 3

条件を満たす数列は存在しません。

## 样例 #1

### 输入

```
1 0```

### 输出

```
0 0 1 1```

## 样例 #2

### 输入

```
1 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
5 58```

### 输出

```
-1```

# 题解

## 作者：StudyingFather (赞：18)

Atcoder 上有关 xor 的构造题还挺多。

容易发现 $k \geq 2^m$ 时显然无解。

接下来先处理些平凡的情况。

- $m=0$，$k=0$：显然只有 `0 0` 这一组解；
- $m=1$，$k=0$：样例给了 `0 0 1 1` 这一组解；
- $m=1$，$k=1$：样例告诉我们无解。

现在开始考虑 $m \geq 2$ 的情况，考虑构造一个 $k \oplus 0 = k$ 的形式。

注意到 $x \oplus x = 0$，于是考虑按如下对称形式构造：

$$
0, 1, \ldots, k-1, k+1, \ldots, 2^m-1, k, 2^m-1, \ldots, k+1, k-1, \ldots, 1, 0, k
$$

对于除了 $k$ 以外的数字，它们形成的子序列是完全对称的，除了 $k$ 之外的数字每个数字均出现恰好两次，于是全部抵消，形成了 $k \oplus 0 = k$ 的形式。

对于 $k$ 来说，它形成的子序列中，$0 \sim 2^m-1$ 中除了 $k$ 之外每个数字只出现一次，$k$ 出现两次。注意到 $0 \sim 2^m-1$ 的异或和总为零（对于每一个二进制位，满足该位上值为 1 的数恰好有 $2^{m-1}$ 个，总是偶数），于是最后还是 $k \oplus 0 = k$ 的形式。

---

## 作者：___w (赞：3)

[[ABC126F] XOR Matching](https://www.luogu.com.cn/problem/AT_abc126_f)

构造好题。

首先，对于任意两个相同的数之间的异或和为 $k$，我们可以考虑先在一个 $k$ 左右两边同时加上一个数，这样之间的数由于出现了两次然后抵消掉，如下所示：

$$1,2\dots k-1,k+1\dots 2^m-1,k,2^m-1\dots k+1,k-1\dots2,1$$

然后我们注意到 $0\oplus1\oplus\dots\oplus2^m-1=0$，上面 $k$ 到末尾的部分的异或和为 $k$，这时候我们可以刚好在后面加一个 $k$，满足构造。

当然要特判一些情况：

- $m=1,k=0$，答案为 $0,0,1,1$。

- $m=1,k=1$，无解。

- $k\ge2^m$，无解。

代码：

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define ll long long
#define space putchar(' ')
#define enter putchar('\n')
using namespace std;

typedef vector <int> vi;
typedef pair <int, int> pii;

inline int rd() { int x = 0, f = 1; char c = getchar(); while (!isdigit(c)) f = c == '-' ? -1 : f, c = getchar(); while (isdigit(c)) x = (x<<3)+(x<<1)+(c^48), c = getchar(); return x*f; }
inline ll rdll() { ll x = 0, f = 1; char c = getchar(); while (!isdigit(c)) f = c == '-' ? -1 : f, c = getchar(); while (isdigit(c)) x = (x<<3)+(x<<1)+(c^48), c = getchar(); return x*f; }
template <typename T> inline void write(T x) { if (x < 0) x = -x, putchar('-'); if (x > 9) write(x/10); putchar(x%10+48); }

int main() {
	int m, k; cin >> m >> k;
	if (k >= 1<<m) puts("-1"), exit(0);
	if (m == 1) puts(k ? "-1" : "0 0 1 1"), exit(0);
	for (int i = 0; i < k; ++i) cout << i << ' ';
	for (int i = k+1; i < 1<<m; ++i) cout << i << ' ';
	cout << k << ' ';
	for (int i = (1<<m)-1; i > k; --i) cout << i << ' ';
	for (int i = k-1; ~i; --i) cout << i << ' ';
	cout << k;
	return 0;
}
```

---

## 作者：Fire_flame (赞：3)

[[题目传送门](https://www.luogu.com.cn/problem/AT4754)]

## $\mathtt{Soulution}$

首先可以解决 $k=0$ 的情况，直接输出 $0,0,1,1,……(n-1),(n-1),n,n$ 即可。

并且如果 $k>2^m-1$ 直接输出无解即可，因为最大的才 $2^m-1$。

然后我们来考虑，$n=2,k=1$ 时答案是：$0,1,2,3,1,0,3,2$

而如果我们把 $n=2$ 改为 $n=3$ 那么把其他的数字成对的插到第 $2$ 个数后面和第 $5$ 个数前面。

![](https://cdn.luogu.com.cn/upload/image_hosting/bt16d7nf.png?x-oss-process=image/resize,m_lfit,h_2500,w_3000)

因为 $x \oplus x=0$ 且 $2 \oplus 3=1$，所以该排列符合要求。

这时通解就很简单了，选出四个数 $a,b,c,d$ 满足上面的情况，然后按照 $a,b,c,d,b,a,d,c$ 排好，再把其他的数插到中间即可。

---

## 作者：Erinyes (赞：2)

## Part 1 : 样例分析

其实这道题并没有看起来那么难，只是样例给得很特殊而已。

比如说下面这组样例：

```
Input：
3 4

Output
0 1 2 3 5 6 7 4 7 6 5 3 2 1 0 4
```

看起来很有规律是不是？

只是把 $0\sim2^m-1$ 的每一个非 $k$ 的数正序输出，然后输出 $k$，再倒序输出一遍非 $k$ 的数，最后输出 $k$。

但是，为什么要这么做？

## Part 2 ：题目分析

结果等于```-1```是很好判断的，由于异或运算的结果必定小于等于进行计算的两个数
，所以 $k$ 必定小于等于整个序列中的任何一个数。
```cpp
if(k>pow(2,m)-1){
    printf("-1");
    return 0;
}
```


------------


首先要明确一点，对于下面这样的一个序列，按位异或后的结果必定为 $1$。

```
0 1 2 3 3 2 1 0
```
因为众所周知，异或 ( xor ) 运算是具有结合性的。

拿上面这个序列来说，就是把

```
0 xor 1 xor 2 xor 3 xor 3 xor 2 xor 1 xor 0
```

分为了

```
0 xor 1 xor 2 xor 3
```
和
```
3 xor 2 xor 1 xor 0
```
因为已知异或是具有交换性的，所以前半段的结果必定等于后半段的结果，那么最终的结果就一定等于 $0$。

更多关于异或的内容可以参见[这里](https://www.ruanyifeng.com/blog/2021/01/_xor.html)。


------------

明确了这一点，要完成这道题目就比较容易了。

现在我们做到了让两个相同的数构成的子序列按位异或结果为 $0$，那么怎么使它为 $k$ 呢？

先分析一个实例:

```
2 3 4 4 3 2
```
这样它的异或结果为 $0$，是因为 $a\oplus a=0$。

如果我们尝试将这个序列分割一下，就会变成

```
(2 3 4) (4 3 2)
```
如果令 ```(2 3 4)``` 为 $A$，那么这个序列按位异或就可以写成

```
A xor A (异或的交换性)
```
上面这个式子等于零，如果要让它等于 $k$,就需要让它变成

```
A xor A xor k
```
因为 $a\oplus 0=a$。

所以再把这个式子还原，就可以写成

```
2 3 4 k 4 3 2
```
就成了 Part 1 部分的样例那样了。



------------
接着就只剩下了 $k$ 的子序列了。

我们接着分析实例：

如果 $m=2$，$k=2$，则结果应该为

```
0 1 3 2 3 1 0 2
```
单独把 $k$ 抓出来，就是

```
2 3 1 0 2
```
把这个序列整理一下，就可以变成

```
0 1 2 3 2
```
经过尝试可以发现，$0\sim2^m-1$ 中的左右数按位异或的值为 $0$。

所以这个序列就成了

```
0 2
```
又因为 $a\oplus 0=a$，所以这个序列的最终结果就是 $2\oplus 0=2$，也就是 $k$。

## Part 3 : 代码

当我做完后，我才发现，其实样例竟然是一个特殊情况？！

所以需要特判。

```cpp
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<math.h>
using namespace std;
int main(){
	int m,k;
	scanf("%d %d",&m,&k);
	if(m==1){ //特判 
		if(k==0) printf("0 0 1 1");
		else printf("-1");
		return 0;
	}
	if(k>=pow(2,m)){
		printf("-1");
		return 0;
	}
	for(int i=0;i<pow(2,m);i++){ //正序 
		if(i==k) continue; //不输出k 
		printf("%d ",i);
	}
	printf("%d ",k);
	for(int i=pow(2,m)-1;i>=0;i--){ //倒序 
		if(i==k) continue; //不输出k 
		printf("%d ",i);
	}
	printf("%d ",k);
	return 0;
}
```


---

## 作者：KazamaRuri (赞：1)

不小心给我想到了，挺有意思的写道题解吧。

## 题意

构造一个长度为 $2^{m+1}$ 的序列 $a$ 满足

- $\forall i \in[1, 2^{m+1}], a_i \in [0, 2^m-1]$ 且每个数都恰好出现两次。
- 对于任意一对 $(i, j)$ 满足 $a_i = a_j$，$a_i\oplus a_{i+1} \oplus \cdots \oplus a_{j-1} \oplus a_j = k$

$\oplus$ 表示按位异或。

若不存在满足要求的序列，输出```-1```。  
若存在多个满足要求的序列，输出任意一个即可。

## 分析

先考虑无解的条件，容易发现是 $k \ge 2^n$。

有解的情况下考虑用最简单的方式构造。

观察这个式子:
$$$
a_i\oplus a_{i+1} \oplus \cdots \oplus a_{j-1} \oplus a_j = k
$$$

由于有些数字出现了两次对异或的值并没有影响，所以异或出 $k$ 的数在 $[i,j]$ 中一定只出现了一次。结合上文所说的，“采用最简单的方式构造”，那么当然是把 $k$ 二进制分解，然后通过若干个 $2^p$ 来构造。

如果不考虑 $2^p$ 第二次出现在哪里，可以构造出如下的序列：
$$$
1,2,3,\cdots,2^{p_1},2^{p_2},2^{p_3},\cdots,2^{p_m},\cdots,3,2,1
$$$

之后只能把 $2^p$ 第二次出现的位置插到这个序列后面。根据 $\oplus_{i=1}\ 2^{p_i} = k$ 还有 $\oplus_{i=0}^{2^n-1}\ i =0\ \ (n \neq 1)$。得到去掉这些 $2^p$，剩下的数的异或值也等于 $k$,那么就能构造出这样的答案序列：
$$$
1,2,\cdots,2^{p_1},2^{p_2},\cdots,2^{p_m},\cdots,2,1,2^{p_m},2^{p_{m-1}},\cdots,2^{p_1}
$$$

## 代码

没有刻意压行。


```cpp
#include <iostream>
using namespace std;
const int N=1<<17;
int n,k; bool p[N];
int main(){
	scanf("%d%d",&n,&k);
	if(k>=(1<<n)||n==1&&k) return puts("-1")&0;
	for(int i=0;i<n;i++)
		if(k>>i&1)
			p[1<<i]=1;
	for(int i=0;i<(1<<n);i++)
		if(!p[i]) printf("%d ",i);
	for(int i=0;i<n;i++)
		if(p[1<<i]) printf("%d ",1<<i);
	for(int i=(1<<n)-1;~i;i--)
		if(!p[i]) printf("%d ",i);
	for(int i=n-1;~i;i--)
		if(p[1<<i]) printf("%d ",1<<i);
	return 0;
}
```

---

## 作者：Rannio (赞：1)

很好的构造题。
### 题意

请构造一个长度为 $2^{m+1}$ 的序列 $a$，该序列满足：

- $\forall i \in[1, 2^{m+1}], a_i \in [0, 2^m-1]$ 且每个数都恰好出现两次。
- 对于任意一对 $(i, j)$ 满足 $a_i = a_j$，$a_i\oplus a_{i+1} \oplus \cdots \oplus a_{j-1} \oplus a_j = k$。

$\oplus$ 表示按位异或。

### 思路

很显然，当 $k>2^m-1$ 时无解。

再考虑平凡的的情况：
- 当 $m$ 为 $0$，$k$ 为 $0$ 时，只有 `0 0` 一组解。
- 当 $m$ 为 $1$，$k$ 为 $0$ 时，样例告诉我们只有 `0 0 1 1` 一组解。
- 当 $m$ 为 $1$，$k$ 为 $1$ 时，样例告诉我们无解。

接下来考虑一般情况：

我们知道，$a \oplus a$ 为零，所以只需构造一个序列形如：

 $$ 0,1 \dots 2^m-1,k,2^m-1 \dots 1,0,k $$

该式满足：对于任意一对 $(i, j)$，$a_i = a_j$，$a_i\oplus a_{i+1} \oplus \cdots \oplus a_{j-1} \oplus a_j = k$。  
显然，这个序列除最后一个元素外是回文的，并且所有数字都出现了 $2$ 次，正好可以相互抵消。  
对于 $k$ 形成的子序列，有一个公式：$0\oplus 1 \oplus 2 \oplus \dots \oplus k=0$，因为在 $0$ 至 $k$ 的序列中，每一位上都出现了偶数个 $1$，全部抵消后便为 $k \oplus 0=k$。 

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a,s,d[100005],f;
ll ans;
int main(){
    scanf("%lld%lld",&a,&s);
    if(a==1&&s==0){
        printf("0 0 1 1");
        return 0;
    } 
	if(s>=pow(2,a)){
		printf("-1");
		return 0;
	}
	for(int i=0;i<pow(2,a);i++){ 
		if(i==s) continue;
		printf("%lld ",i);
	}
	printf("%lld ",s);
	for(int i=pow(2,a)-1;i>=0;i--){ 
		if(i==s) continue;
		printf("%lld ",i);
	}
	printf("%lld",s);
    return 0;
}
```

---

## 作者：crzcqh (赞：1)

遇到这样的异或题其实可以先不往二进制想，因为 $x \oplus x=0$，并且注意到 $a_i=a_j$，这已经在提示我们。也就是说可以构造一个序列，使得 $a_i=a_j,a_{i+1}=a_{j-1},\dots$ 并且在中间包含一个 $k$，这样 $a_i\oplus a_{i+1}\dots a_j=0\oplus k=k$。

把 $i=1,j=2^{m+1}$，则不难构造出这样一个序列：
$0,1,2\dots k-1,k+1,\dots 2^{m-1},k,2^{m-1},\dots k+1,k-1,\dots2,1,0$，再在末尾加一个 $k$，这样保证是满足条件的，因为前面对称且先单调递增后单调递减，能保证数是成对出现的。而最后的 $k,2^{m-1}\dots,k+1,k-1\dots2,1,0,k$ 手动一下可以保证是对的。

无解情况：如果 $k\ge 2^m$，一定无解。

code:

```cpp
#include<iostream>
#include<cmath>
#define F(l,r,i) for(int i=l;i<=r;i++)
#define ll long long
using namespace std;
ll m,k,M;
int main(){
	cin>>m>>k;
	M=pow(2,m);
	if(m==1){
		if(k==0) puts("0 0 1 1");
		else puts("-1");	
	}else if(M<=k) cout<<-1;
	else{
		for(int i=0;i<k;i++) cout<<i<<' ';
		for(int i=k+1;i<M;i++) cout<<i<<' ';
		cout<<k<<' ';
		for(int i=M-1;i>=k+1;i--) cout<<i<<' ';
		for(int i=k-1;i>=0;i--) cout<<i<<' ';
		cout<<k<<' ';
	}
	return 0;
}
```

---

## 作者：Augen_stern (赞：1)

## Part 1：算法分析

首先，$\oplus$ 即为题目中的异或运算（C++ 中的 ``` ^ ```，又称  $\operatorname{xor}$ 运算）;

我们首先必须知道两个异或运算的基本算式： 

1，$0\oplus k=k$；

2，$k\oplus k=0$；


所以有类似于 $234\oplus 543\oplus 234=543$；

所以让我们再看几组更大一点的样例：

#### 输入 #1
```
2 2
```

#### 输出 #1
```
0 1 3 2 3 1 0 2
```

#### 输入 #2
```
4 2
```

#### 输出 #2
```
0 1 3 4 5 6 7 8 9 10 11 12 13 14 15 2 15 14 13 12 11 10 9 8 7 6 5 4 3 1 0 2
```

## Part 2：题目求解

不难可以发现，当构造一组对称的数列时，可以使对于任意一对  $(i,j)$ 满足 $a_i=a_j$ 时，$a_i\oplus a_{i+1} \oplus \cdots \oplus a_{j-1} \oplus a_j =0\oplus k=k$；

证明：任意两个相同的数中都会有一个 $k$，和一些重复了两遍的数，使重复的抵消成 $0$，又 $0\oplus 0=0$，再 $0\oplus k=0$，所以得证；

所以，此时满足题目要求；

题目解法可能不唯一，所以题目可能使用了 Special Judge，请放心食用。

```cpp
	for(int i=0; i<pow(2,m); i++) {
		if(i==k) continue; // 将 k 提出来 
		printf("%d ",i); // 正序 
	}
	printf("%d ",k);
	for(int i=pow(2,m)-1; i>=0; i--) {
		if(i==k) continue;
		printf("%d ",i); // 倒序 
	}
	printf("%d\n",k);
```


再来考虑 $-1$ 的情况，当 $k\ge 2^m$ 时，则无法构造，因为 $a_i\in [0,2^m-1]$；

```cpp
	if(k>=pow(2,m)) {
		puts("-1"); // 无法构建 
		return 0;
	}
```


在此之外，当 $m=1$ 时，是一个特例情况，此时当 $k=1$ 时也没有解（题目中的样例有提及），（感谢样例！）；

```cpp
	if(m==1) {
		if(k==0) printf("0 0 1 1\n");
		else puts("-1");
		return 0; // 特判 
	}
```


**总结：**

 **1，当 $m=1$ 时，只有 $k=0$ 时有解；**

 **2，当 $k\ge 2^m$ 时，则无法构造；**

 **3，剩下的则可以构造：$0,1,2,...,2^m-1,k,2^m-1,2^m-2,...,1,0$。**

## Part 3：CODE

所以我们可以得到：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#define INF 0x7fffffff/2
using namespace std;
int m,k;
signed main() {
	scanf("%d%d",&m,&k);
	if(m==1) {
		if(k==0) printf("0 0 1 1\n");
		else puts("-1");
		return 0; // 特判 
	}
	if(k>=pow(2,m)) {
		puts("-1"); // 无法构建 
		return 0;
	}
	for(int i=0; i<pow(2,m); i++) {
		if(i==k) continue; // 将 k 提出来 
		printf("%d ",i); // 正序 
	}
	printf("%d ",k);
	for(int i=pow(2,m)-1; i>=0; i--) {
		if(i==k) continue;
		printf("%d ",i); // 倒序 
	}
	printf("%d\n",k);
	return 0;
}
```

谢谢观赏！

2021.11.16 14:10 初稿成；

2021.11.16 18:05 进行部分修正。

---

## 作者：SpeedStar (赞：1)


#### 算法分析

注意到，$0 \oplus 1 \oplus 2 \oplus 3 = 0$

可推广为：$0 \oplus 1 \oplus 2 \oplus 3 \cdots \oplus (2^{m} - 1) = 0$


- 当 $m \geqslant 2$ 且 $0 \leqslant k \leqslant 2^m - 1$ 时，序列 $\{a\}$ 可构造为：

$$(0, 1, 2, \cdots), k, (\cdots, 2, 1, 0), k$$

也就是对于两个相同的数$a_l$和$a_r$，要想 $a_l \oplus \cdots \oplus a_r$ 之后获得 $k$，他们必须关于 $k$ 对称。

- 当 $m = 1$ 且 $k = 1$ 时， 无解

- 当 $m = 1$ 且 $k = 0$ 时，可构造为 $0 \ 0 \ 1 \ 1$

- 当 $k \geqslant 2^m$ 时也无解，因为小于 $2^m$ 的非负整数的异或和不会达到 $2^m$. 

#### C++ 代码
```
#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::vector;

int main() {
	int m, k;
	cin >> m >> k;
	
	if (k >= (1 << m)) {
		cout << "-1\n";
		return 0;
	}
	
	if (m == 1) {
		if (k == 1) {
			cout << "-1\n";
			return 0;
		}
		else {
			cout << "0 0 1 1\n";
			return 0;
		}
	}
	
	int n = (1 << m);
	vector<int> res;
	for (int i = 0; i < n; ++i) {
		if (i != k) res.push_back(i);
	}
	res.push_back(k);
	for (int i = n - 1; i >= 0; --i) {
		if (i != k) res.push_back(i);
	}
	res.push_back(k);
	
	for (auto x : res) cout << x << " ";
	
	return 0;
}
```

---

## 作者：DengDuck (赞：0)

第一次五分钟想出蓝色构造，纪念一下。

也许和大家的做法看起来是不太一样的，但是本质一样。

首先特判一下无解和 $k=0$，这个是简单的。

然后我们暴力跑一些解观察一下，发现这样的解比较有规律：

- 开头一个 $0,k,0$。
- 然后连续的一段 $1\sim 2^n-1$，不包含 $k$。
- 中间一个 $k$。
- 然后连续的一段 $2^n-1\sim 1$，不包含 $k$（注意顺序变了）。

这个做法的正确性十分显然，原理其实是：

$$
\bigoplus_{i=1}^{2^n-1} i=0 (n>1)
$$

首先不难发现除了 $k$ 之外的数字，都是两个数字之间把相同的抵消之后只剩下 $k$，显然是合法的。

对于 $k$ 来说，其之间应该恰好是除了 $k$ 之外的所有数字异或起来，这就是上面的式子少异或一个 $k$，不难得出异或和的结果为 $k$。

然后做完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int main()
{
	scanf("%d%d",&n,&k);
	if(k>=(1<<n)||(n==1&&k==1))
	{
		puts("-1");
		return 0;
	}
	if(k==0)
	{
		for(int i=0;i<(1<<n);i++)
		{
			printf("%d %d ",i,i);
		}
		return 0;
	}
	printf("%d %d %d ",0,k,0);
	for(int i=1;i<(1<<n);i++)
	{
		if(i!=k)printf("%d ",i);
	}
	printf("%d ",k);
	for(int i=(1<<n)-1;i>=1;i--)
	{
		if(i!=k)printf("%d ",i);
	}	
}
```

---

## 作者：linyuhuai (赞：0)

[更好的阅读体验。](https://by505244.github.io/oi_blogs/2024/03/26/ABC126F/)

### 题意：

给定 $m,k$，构造一个序列 $a$ 使得 $[0,2^m-1]$ 中的每一个整数有且仅有出现 $2$ 次。且 $\forall i,j$ 满足 $a_i=a_j,i<j$，有 $\oplus_{g=i}^{j}a_g=k$。无解输出 `-1`。

### 解法：

我们需要把 $[0,2^m-1]$ 分别划分为 $2$ 段异或和为 $k$ 的段 $A,B$，规定 $A',B'$ 分别与原序列的顺序相反，此时可以采用 $ABA'B'$ 的方式排布（因为方向相反，所以 $B$ 中的后 $i$ 元素和 $B'$ 的前 $i$ 个元素相同，对应元素相互异或相抵消，所以此时 $B$ 中的任意一个元素到 $B'$ 的对应位置异或和为 $A'=k$）。

容易发现当 $m >1$ 时，$\oplus_{i=0}^{2^m-1}i=0$（$\oplus$ 表示异或和），那么我们把 $k$ 提取出来作为 $A$ 序列，把剩余的数作 $B$ 数列，则 $B$ 序列此时的异或和也为 $k$。当 $m=1$ 时特判输出方案即可。

---

## 作者：lrb12345 (赞：0)

一道 $xor$ 构造题
## 题意
构造一个长度 $2^{m+1}$ 的序列 $a$ 满足：

- $\forall i \in[1, 2^{m+1}], a_i \in [0, 2^m-1]$ 且每个数都恰好出现两次。
- 对于任意一对 $(i, j)$ 满足 $a_i = a_j$，$a_i\oplus a_{i+1} \oplus \cdots \oplus a_{j-1} \oplus a_j = k$

温心提示：$\oplus$ 是按位异或运算。

## 思路
首先我们根据题意可以看出 $k>2^m-1$ 时肯定是无解的，然后我们要知道一个定理：

因为 $a\oplus a=0$ 所以可得

$1\oplus2\oplus3\oplus4\oplus\dots\oplus2\oplus1=0$

且 $0\oplus a=a$

所以这题我们只需要构造一个

$0,1,2,\dots2^m-1,k,2^m-1\dots,2,1,0,k$

的序列就可以了。
### 注意
有种特殊情况
- $m=1,k=0$ 时是有解的。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
long long m,k;

int main()
{
	cin>>m>>k;
	if(m==1)//特判
	{
		if(k==0)
		cout<<"0 0 1 1";
		else
		cout<<-1;
		return 0;
	}
	if(k>=pow(2,m)){
	cout<<-1;
	return 0;}
	long long j=pow(2,m);
	for(int i=0;i<j;i++)
	{
		if(i!=k)
		cout<<i<<" "; 
	}
	cout<<k<<" ";
	for(int i=j-1;i>=0;i--)
	{
		if(i!=k)
		cout<<i<<" ";
	}
	cout<<k;
}
```

---

## 作者：wangyishan (赞：0)

# [ABC126F] XOR Matching 题解

[原题Link](https://www.luogu.com.cn/problem/AT_abc126_f)

一道挺有意思的题，写篇题解。

先考虑无解：当 $ k>2^m-1 $ 时，一定无解。

注意到异或的性质：

+ $0 \oplus x = x$
+ $x \oplus x = 0$

这代表着如果想让序列的异或和为 $k$，就必须让除了 $k$ 以外的所有数出现次数为偶数。然后经过漫长的思考和打表之后我们发现，我们考虑按对称的形式构造：

$0,1,\dots,k-1,k+1,\dots,2^m-1,k,2^m-1,\dots,k+1,k-1,1,0,k$

对于除了 $k$ 以外的数字，它内部包含的数字都出现了两遍，所以答案一定是 $k$。

对于 $k$ 本身，我们发现从 $0$ 到 $2^m-1$ 的异或和一定是 $0$，因为每一位上的 $1$ 都出现了 $2^{m-1}$ 次，答案仍然为 $k$。

然后我们会发现样例是 $2$ 组特殊情况：
- 当 $m=1,k=0$ 时，一组答案为 $0 0 1 1$;
- 当 $m=1,k=1$ 时，无解；
- 当 $m=0,k=0$ 时，答案为 $0 0$。

另外，为什么洛谷rmj爬不过来 AC 啊？

[Code](https://atcoder.jp/contests/abc126/submissions/46926468)
```cpp
#include<bits/stdc++.h>
using namespace std;
int m,k;
int main(){
    cin>>m>>k;
    if(m==1&&k==0)cout<<"0 0 1 1\n";
    else if(m==0&&k==0)cout<<"0 0\n";
    else if(m==1&&k==1)cout<<"-1\n";
    else if(k>=(1<<m))cout<<"-1\n";
    else{
        for(int i=0;i<(1<<m);i++){
            if(i==k)continue;
            cout<<i<<" ";
        }
        cout<<k<<" ";
        for(int i=(1<<m)-1;i>=0;i--){
            if(i==k)continue;
            cout<<i<<" ";
        }
        cout<<k<<"\n";
    }
    return 0;
}
```



---

## 作者：StevenLiTheOIer (赞：0)

## 思路：
当 $k\ge 2^m$ 时，显然无解。样例给定的两组数据不具备参考价值，但要作为特判。

来看一个正常的样例：

```
3 3
```

则我们有初始序列：

```
0 0 1 1 2 2 3 3 4 4 5 5 6 6 7 7
```

当 $a_i=a_j=7$ 时，显然 $a_i\oplus a_j=0$，则它们之间的式子异或和为 $3$。所以我们把 $3$ 夹在两个相同的 $7$ 的中间：

```
7 3 7
```

同理，当 $a_i=a_j=6$ 时，它们之间的式子异或和为 $3$。所以我们把 $6$ 夹在 $7$ 外面：

```
6 7 3 7 6
```

以此类推，最后我们就得到了长这样的式子：

```
0 1 2 4 5 6 7 3 7 6 5 4 2 1 0
```

但是另一个 $3$ 怎么办？因为 $0\oplus1\oplus2\oplus\cdots\oplus2^{m-1}=0$ （易证每一位上 $1$ 的个数恒为偶数），所以把它放在末尾，让从另一个 $3$ 开始一段的异或和为 $0$，而 $0\oplus3=3$：

```
0 1 2 4 5 6 7 3 7 6 5 4 2 1 0 3
```

显然，这一规律对所有数都适用。最后加上特判，就做完了。
## Code：
```
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n, k;
	cin >> n >> k;
	if ((1 << n) - 1 < k)
	{
		cout << -1 << endl;
		return 0;
	}
	if (n == 1)
	{
		k == 1 ? cout << -1 << endl : cout << "0 0 1 1" << endl;
		return 0;
	}
	for (int i = 0; i <= (1 << n) - 1; i++)
		if (i != k) cout << i << " ";
	cout << k << " ";
	for (int i = (1 << n) - 1; i >= 0; i--)
		if (i != k) cout << i << " ";
	cout << k << endl;
	return 0;
}
```

---

## 作者：_lyx111 (赞：0)

# [ABC126F] XOR Matching

[link](https://atcoder.jp/contests/abc126/tasks/abc126_f)

## 分析

首先当 $2^m\le k$ 时，无解（考虑二进制下的第 $m+1$ 位可知）。

下面考虑 $k<2^m$ 的情况。

对于 $\oplus$ 有个性质：$x\oplus x=0$，那么要求 $a_i\oplus a_{i+1} \oplus \cdots \oplus a_{j-1} \oplus a_j=k$ 就是 $a_{i+1} \oplus \cdots \oplus a_{j-1}=k$，那么对 $a_i=x,a!=k$ 的情况这样考虑：

$$0,1,\cdots,k-1,k+1,\cdots2^m-1,k,2^m-1,\cdots,k+1,k-1,\cdots,1,0$$

那么对于 $a_i=k$ 的情况，可以发现 $0\oplus 1\oplus \cdots \oplus (2^m-1)=0$（逐位考虑就可以知道这一点），那么 $0\oplus 1\oplus \cdots (k-1) \oplus (k+1)\oplus\cdots\oplus (2^m-1)=0$（少 $\oplus$ 一个 $k$ 和多 $\oplus$ 一个 $k$ 是等价的），那么我们只需要在刚才构造出来的序列的最前面加上一个 $k$ 即可：

$$k,0,1,\cdots,k-1,k+1,\cdots2^m-1,k,2^m-1,\cdots,k+1,k-1,\cdots,1,0$$

那么我们只需要将这个序列输出即可。

## 细节

注意样例中的 $m=1,k=0$ 和 $m=1,k=1$，这两个情况比较特殊，要特判，[不特判能过所有测试点但样例过不去，$0$ 分/lb](https://atcoder.jp/contests/abc126/submissions/37900975)。

## 代码

~~~cpp
#include <bits/stdc++.h>
using namespace std;
int m,k;
int pw; //2^m
int main()
{
	scanf("%d%d",&m,&k);
	pw=1;
	for(int i=1;i<=m;i++)
		pw=pw*2;
	if(k>=pw||(m==1&&k!=0))
	{
		printf("-1\n");
		return 0;
	}
	if(m==1&&k==0)
	{
		printf("0 0 1 1\n");
		return 0;
	}
	printf("%d ",k);
	for(int i=0;i<=pw-1;i++)
		if(i!=k) printf("%d ",i);
	printf("%d ",k);
	for(int i=pw-1;i>=0;i--)
		if(i!=k) printf("%d ",i);
	printf("\n");
	return 0;
}
~~~

[AC记录](https://atcoder.jp/contests/abc126/submissions/37900953)

## 写在最后

蒟蒻很菜，如果写的有不清楚或不对的地方望读者私信我指出，我会及时修正。

---

## 作者：tZEROちゃん (赞：0)

为了方便描述，下文令 $b = 2^m-1$。

考虑构造这样一个序列：

$$1, 2,\cdots, k-1, k+1, \cdots,b-1, b,k, b,b-1, \cdots,k+1,k-1,\cdots, 2, 1, k$$


简单描述一下就是，先把 $k$ 放在最中间，然后将 $1\sim b$ 的数依次 **对称** 放在 $b$ 的两边，然后在最后放一个 $k$ 就可以了。

下面说一下原因。

我们知道

- $a \oplus 0 = a$
- $a \oplus a = 0$

所以说我们发现任意 $(i,j)\ (i < j, a_i \not  = k, a_i = a_j)$ 他们出现的除 $k$ 以外的数都是两个。

比如说对于以下序列（$m = 3, k = 5$）：

$$0, 1, 2, 3, 4, 6, 7, 5, 7, 6, 4, 3, 2, 1, 0, 5$$

比如我们取 $i = 6, j = 10$，此时 $a_i = a_j = 6$，不难发现这个部分中 $6,7$ 都出现了 $2$ 次，异或以来等于 $0$，然后中间的 $a_8 = 5$，所以异或起来答案是 $5$，不难发现是符合要求的，当然，根据第二行的序列的格式也可以得到这个结论。

另一个问题，两个 $k$ 之间异或起来等于 $k$ 吗？

不难发现 $0\sim b$ 之间所有数异或起来是 $0$，又异或了一个 $k$，所以 $0\oplus k = k$，发现还是正确的。

需要注意一些特殊情况。
- 当 $k \ge 2^m$ 时，无解；
- 当 $k = 0$ 时，从 $1$ 到 $b$ 依次升序输出，再从 $b$ 到 $1$ 降序输出；
- 其他情况
  - 当 $k \not = 0$ 且 $m = 1$ 时，无解；
  - 当 $k \not = 0$ 且 $m \not = 1$ 时，按照上述方法操作即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for(auto i = (l); i <= (r); i ++)
#define per(i, r, l) for(auto i = (r); i >= (l); i --)

void solve() {
  int m, k;
  cin >> m >> k;
  if (k >= (1<<m)) {
    cout << "-1";
  } else if (k == 0) {
    rep (i, 0, (1<<m) - 1) cout << i << ' ';
    per (i, (1<<m) - 1, 0) cout << i << ' ';
  } else if (k != 0) {
    if (m == 1) {
      cout << "-1";
    } else {
      rep (i, 0, (1<<m) - 1) if (i != k) cout << i << ' ';
      cout << k << ' ';
      per (i, (1<<m) - 1, 0) if (i != k) cout << i << ' ';
      cout << k << ' ';
    }
  }
  cout << endl;
}

int main(){
  solve();
  return 0;
}
```

---

