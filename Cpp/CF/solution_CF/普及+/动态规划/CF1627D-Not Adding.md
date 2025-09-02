# Not Adding

## 题目描述

You have an array $ a_1, a_2, \dots, a_n $ consisting of $ n $ distinct integers. You are allowed to perform the following operation on it: 

- Choose two elements from the array $ a_i $ and $ a_j $ ( $ i \ne j $ ) such that $ \gcd(a_i, a_j) $ is not present in the array, and add $ \gcd(a_i, a_j) $ to the end of the array. Here $ \gcd(x, y) $ denotes [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ x $ and $ y $ .

Note that the array changes after each operation, and the subsequent operations are performed on the new array.

What is the maximum number of times you can perform the operation on the array?

## 说明/提示

In the first example, one of the ways to perform maximum number of operations on the array is:

- Pick $ i = 1, j= 5 $ and add $ \gcd(a_1, a_5) = \gcd(4, 30) = 2 $ to the array.
- Pick $ i = 2, j= 4 $ and add $ \gcd(a_2, a_4) = \gcd(20, 25) = 5 $ to the array.
- Pick $ i = 2, j= 5 $ and add $ \gcd(a_2, a_5) = \gcd(20, 30) = 10 $ to the array.

It can be proved that there is no way to perform more than $ 3 $ operations on the original array.

In the second example one can add $ 3 $ , then $ 1 $ , then $ 5 $ , and $ 2 $ .

## 样例 #1

### 输入

```
5
4 20 1 25 30```

### 输出

```
3```

## 样例 #2

### 输入

```
3
6 10 15```

### 输出

```
4```

# 题解

## 作者：Tyyyyyy (赞：14)

# CF1627D

### 题意简述
给定一个长度为 $n$ 的序列 $\{a_1,a_2,\dots,a_n\}$，$a_i$ 互不相同。你可以进行如下操作：选择两个元素 $a_i,a_j$，满足 $\gcd(a_i,a_j)$ 不在当前的序列中，然后将 $\gcd(a_i,a_j)$ 加到序列末端。

请计算你最多可能操作的次数。

$2\leq n\leq 10^6,1\leq a_i\leq 10^6$。

### 题目分析
因为 $\gcd(\gcd(a_i,a_j),a_k)=\gcd(a_i,a_j,a_k)$，所以该问题的本质是求：从原序列中选出一个子序列，能够产生的 $\gcd$ 有多少种。

注意到值域很小，我们可以考虑检查每一个数是否能被生成。具体地，设当前正在检查 $x$ 是否能被生成，则我们知道生成 $x$ 的子序列中所有的数必然是 $x$ 的倍数，且只要子序列中都是 $x$ 的倍数，则子序列中元素越多，它们的 $\gcd$ 越可能是 $x$。

因此，我们可以执行贪心策略：直接求序列中所有是 $x$ 的倍数的元素的 $\gcd$，判断是否为 $x$ 即可。

时间复杂度为 $O(n\log A)$，$A$ 是值域大小。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1000010],ans;
vector<int>fac[1000010];
int f[1000010];
bool isin[1000010];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),isin[a[i]]=1;
	for(int i=1;i<=n;i++)f[a[i]]=a[i];
	for(int i=1;i<=1e6;i++)
	{
		for(int j=1;1ll*i*j<=1e6;j++)
			f[i]=__gcd(f[i],f[i*j]);
		if(f[i]==i&&!isin[i])ans++;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Yizhixiaoyun (赞：9)

[题目传送门](https://www.luogu.com.cn/problem/CF1627D)

## 题目分析

我们使用**桶**记录记录一个值有没有出现。

接着我们**暴力枚举**这个值**可能存在的倍数**，接着我们判断这个倍数的**最大公因数**是否为当前所枚举的数。如果是就可行，只需要依次操作即可。

## 贴上代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=1000005;
int n,a[maxn];
int maxx,ans;
int main(){
	cin>>n;
	for(register int i=1;i<=n;++i){
		int q;cin>>q;
		a[q]=1;
		maxx=max(maxx,q);
	}
	for(register int i=1;i<=maxx;++i){
		if(a[i]!=0) continue;
		int tot=0;
		for(register int j=i;j<=maxx;j+=i){
			if(a[j]!=0) tot=__gcd(tot,j);
		}
		if(tot==i) ans++;
	}
	cout<<ans;
}
```


---

## 作者：0xFF (赞：3)

#### 题目简述


------------
给定一个长度为 $n$ 的数字序列 $\left\{a_{1}, a_{2}, \ldots, a_{n}\right\}$,保证其中 $a_i$ 互不相同。每次可以选择两个元素 $a_{i}$, $a_{j}$,满足 $\operatorname{gcd}\left(a_{i}, a_{j}\right)$ 不在原序列中，将 $\operatorname{gcd}\left(a_{i}, a_{j}\right)$ 加入到原序列末端。询问最多可以进行几次如上操作。

$2 \leq n \leq 10^{6}$，$1 \leq a_{i}^{4} \leq 10^{6}$。

#### 题目分析


------------

因为 $\operatorname{gcd}\left(\operatorname{gcd}\left(a_{i}, a_{j}\right), a_{k}\right)=\operatorname{gcd}\left(a_{i}, a_{j}, a_{k}\right)$ 所以原题可以转化为询问从原序列中取出一个子序列最多能够产生的 $\gcd$ 有多少种，也就是序列中所有可能的最大公约数的数量。

由于 $2 \leq n \leq 10^{6}$ 所以可以枚举写一个数字查看它是否能作为一个最大公约数出现。举个简单的例子：如果我们当前判断的值可能成为最大公约数，那么生成该值的子序列中的所有数都一定是该值的倍数，并且只要子序列中的数都是都是该值的倍数，那么子序列中的元素越多，这个子序列的 $\gcd$ 越有可能是该值。

根据以上思路可以知道，我们只需要查看对于该值的所有倍数是否存在互质的情况。

#### 代码实现

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;

const int N=1e6+5;
int n,a[N],ans;
bool f[N];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
    return x*f;
}

int gcd(int a,int b){
	if(b == 0) return a;
	else return gcd(b,a%b);
}

int main() {
	n = read();
	for(int i=1;i<=n;++i) {
		a[i] = read();
		f[a[i]]=1;
	}
	for(int i=1;i<=1e6;++i) {
		int p=0;
		for(int j=i;j<=1e6;j+=i) {
			if(f[j]) p=gcd(p,j);
		}
		if(p==i) ++ans;
	}
	printf("%d",ans-n);
	return 0;
}
```


---

## 作者：PosVII (赞：2)

**前言**

------------

很棒的一道题，建议评蓝/绿。

**思路**

------------

题意简化一下就是说序列内所有可能的最大公约数数量。注意，值域为 $10^6$，可以枚举查找每个数是否能作为最大公约数出现。此时可以在它的所有存在的倍数中做一个最大公约数，看结果是否为它本身（即对于它的所有倍数是否有倍数互质的情况，只要有就可以得到它本身）

**code**

------------

```
#include<bits/stdc++.h>
using namespace std;
#define max(a,b) (a>b?a:b)
template<typename G>inline void read(G&x){x=0;G f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+(ch^48),ch=getchar();x*=f;}
template<typename G>inline void write(G x){if(x<0) putchar('-'),x=-x;G y=10,len=1;while(y<=x){y*=10;++len;}while(len--){y/=10;putchar(x/y^48);x%=y;}}
const int MAXN=1e6+5;
int n,a[MAXN],ans;
bool f[MAXN];
int main() {
	read(n);
	for(int i=1;i<=n;++i) {
		read(a[i]);
		f[a[i]]=1;
	}
	for(int i=1;i<=1e6;++i) {
		int p=0;
		for(int j=i;j<=1e6;j+=i) {
			if(f[j]) p=__gcd(p,j);
		}
		if(p==i) ++ans;
	}
	printf("%d",ans-n);
	return 0;
}
```

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 1900}$
---
### 解题思路：

首先一个值出现了多少次并不被关心，重点仅在这个只有没有出现，所以直接开一个桶记录下所有的值的存在性。

然后具体考虑每一个值是否可能存在，直接枚举所有这个值可能存在的倍数，只要这些倍数的最大公因数为当前所枚举的数就一定可行，一种可行的操作是依次操作。

总复杂度 $O(n\log n)$。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,a[1000005],x,maxn,ans;
int gcd(int a,int b){
	if(b==0)return a;
	return gcd(b,a%b);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		a[x]=1;maxn=max(maxn,x);
	}
	for(int i=1;i<=maxn;i++){
		if(a[i])continue;
		int now=0;
		for(int j=i;j<=maxn;j+=i)
		if(a[j]!=0)now=gcd(j,now);
		if(now==i)ans++;
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：enucai (赞：1)

### 题意

给你一个序列 $a$，$a$ 中的数互不相同，让你进行一些如下操作：

- 选择 $i,j$ 满足 $1\le i<j\le n$，且 $\gcd(a_i,a_j)$ 不出现在原序列中。删除 $a_i$ 与 $a_j$，并将 $\gcd(a_i,a_j)$ 插入序列末尾。

问最多能进行几次操作。

### 思路

自己**莫名**想到了和官方题解类似的解法。

首先注意到 $a$ 数组中元素值域均为 $[1,10^6]$，且一定有 $\gcd(x,y)\le \min\{x,y\}$。所以最终数组中的元素值域一定也是 $[1,10^6]$。

枚举最终序列中的各个元素，并判断是否可能得到。

有**结论**：若 $x$ 能出现在最后序列中，则比满足如下条件之一：

- $x$ **出现**在原序列中。

- $x$ **不出现**在原序列中**且**所有 $x$ 的**倍数**的 $\gcd$ 为 $x$。

对于第二种情况的**证明**：若所有 $x$ 的倍数的 $\gcd$ 不等于 $x$，而是 $a\times x$（$a\in\{2,3,4,\dots\}$）。那么他们一直取 $\gcd$ 最终也只会得到 $a\times x$，$x$ 必不可能出现在最终序列中。否则**必定**会有一次操作，将原先的 $\gcd$ 与现在的$b\times x$（$b\in\{2,3,4,\dots\}$）取 $\gcd$，变为 $x$。因此这样的 $x$ 能产生一次操作的贡献。

这样求 $x$ 的所有倍数的 $\gcd$ 的算法类似于埃式筛，复杂度为 $\Theta(n+V\log V)$，$V$ 为值域。由于 $V$ 与 $n$ 同阶，所以最终复杂度 $\Theta(n\log n)$，可以通过此题。

### 代码

**Talk is cheap, show me the code.**

[Codeforces Status](https://codeforces.com/contest/1627/submission/143730864)


```cpp
bool ap[1000010];
int n,a[1000010],V=0;
signed main(){
	n=read();
	For(i,1,n) a[i]=read();
	For(i,1,n) ap[a[i]]=1;
	For(i,1,n) ckmx(V,a[i]);
	int cnt=0;
	For(i,1,V){
		if(ap[i]) continue;
		int gcd=0;
		for(int j=2*i;j<=V;j+=i) if(ap[j]){
			if(gcd==0) gcd=j;
			else gcd=__gcd(gcd,j);
		}
		if(gcd==i) cnt++;
	}
	cout<<cnt<<endl;
}
```

---

## 作者：Purslane (赞：0)

## Solution

问题转换后可以得到 : 求一个序列中所有子序列的最大公约数的种类 . 

可以可以发现 , 一个序列的最大公约数不大于其最大值 . 那么答案至多有 $10^6$ 种 .

下面介绍一个小 trick :

> 当遇到最大公约数时 , 枚举最大公约数 .

> 因为这样就可以快速 ( 平均总时间复杂度为 $\text{log}$ 值域 ) 找到可能产生这个最大公约数的所有数 , 然后就可以对它们进行判断 , 不会重复出现很多最大公约数相同的情况 .

那么枚举最大公约数 . 

一个数能被表示 , 相当于它的倍数除以这个数产生的新序列中 , 有两个数互质 .

化归出的新问题也很好解决 : 只要整个序列的最大公约数为 1 , 那么必有两个数互质 ; 反之亦然 .

那么开桶维护值域即可 . 

时间复杂度 : $\text{O(V log V)}$ .

```cpp
n=read();
for(int i=1;i<=n;i++) a[i]=read(),f[a[i]]=a[i];
for(int i=1;i<=1000000;i++) {
	int flg=0,gcd=0;
	for(int j=i;j<=1000000;j+=i) if(f[j]) {
		if(!flg) flg=1,gcd=j;
		else gcd=__gcd(gcd,j);
	}
	if(flg&&gcd==i) ans++;
}
printf("%d",ans-n);
```

---

## 作者：CmsMartin (赞：0)

## 题目描述

[题目传送门](https://www.luogu.com.cn/problem/CF1627D)

## 思路

看到 $10^6$ 的数据很容易想到枚举每一个可能的 $\gcd(i,j)$ 的值，

对于枚举的值，我们可以枚举其倍数（因为只有其倍数与其的 $\gcd$ 可能为其本身），

这样我们就可以算出其与其所有存在的倍数的 $\gcd$，如果这个值是其本身，那就让 $Ans$ 加上 $1$

这样子出来的数包括了输入中的 $n$ 个,

所以答案为 $Ans - n$

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int N;
int A[1000010];
bool Vis[1000010];
int Mx , Ans;

template<class T>
inline char read(T &ret) {
	ret = 0;
	short f = 1;
	char c = getchar();
	while(c < '0' || c > '9') {
		if(c == '-') f = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9') {
		ret = (ret << 3) + (ret << 1) + c - 48;
		c = getchar();
	}
	ret *= f;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	read(N);
	for(int i = 1; i <= N; i++) {
		read(A[i]);
		Mx = max(A[i] , Mx);
		Vis[A[i]] = true;
	}
	for(int i = 1; i <= Mx; i++) {
		int Gcd = 0;
		for(int j = i; j <= Mx; j += i) {
			if(Vis[j] == false) continue;
			Gcd = __gcd(Gcd , j);
		}
		if(Gcd == i) Ans++;
	}
	cout << Ans - N << endl;
	return 0;
}
```

---

## 作者：houpingze (赞：0)

此题我的第一反应大概是：先开个桶标记一下一个数在原数组里有没有出现过，然后暴力枚举每个在值域范围之内的数，对于每个数 $i$ ，判断 $i$ 是否至少有两个自己的倍数出现在原数组中，若是，那么 $i$ 可以加入到新数组中。

但这样显然是错误的。举个例子，我们假设现在枚举到了第 $x$ 个数，然后我们只找到了两个在原数组中的 $x$ 的倍数，设它们为 $ax$ 和 $bx$ ， 这时如果有 $\gcd(ax,bx)=cx$ 且 $c > 1$，那么它们就不能生产（？）出这个新的数 $x$ 了，但是上面的算法会把 $x$ 给算成合法的。

但是这个算法是可以改进的。注意到上面的漏洞的实质是 $x$ 所有出现在原数组中的倍数的 $\gcd$ 和 $x$ 不相等，那么**我们可以把 所有出现在原数组中的 $x$ 的倍数的 $\gcd$  算出来，最后再看这个结果是不是 $x$** 就可以了。

时间复杂度为调和级数 $O(n \log n)$

代码挺好写的，不放了（）

---

## 作者：I_am_Accepted (赞：0)

### Preface

考场上没想出来，我是↑↓。

### Analysis

**先将 $\{a\}$ 按值入桶（正好去重）。**

记 $V=\max\{a\}$ 表示值域。

由于值域只有 $10^6$，我们可以从 $1$ 到 $V$ 检查每一个数是否能表示为 $\{a\}$ 中某些数的 $\gcd$。

考虑类似埃氏筛的算法：记 $\{a\}$ 中 $x$ 的倍数有 $f(x)$ 个，这个 $f$ 我们能在 $O(V\log V)$ 内求出。

如果一个数 $x$ 不能表示成 $\{a\}$ 中某些数的 $\gcd$，则 $\{a\}$ 中 $x$ 的倍数均是 $bx$ 的倍数，其中 $b\in\{2,3,4,\dots\}$ 为常数。

所以我们类似上面的做法遍历 $x$ 的倍数 $y$（不包括 $x$）判断 $[f(x)=f(y)]$ 是否成立。

时间 $O(n+V\log V)$。

### Detail

最后个数记得减去本来存在的那些数。

### Code

[Link](https://codeforces.com/contest/1627/submission/143324559)

---

