# Kleene Inversion

## 题目描述

[problemUrl]: https://atcoder.jp/contests/jsc2019-qual/tasks/jsc2019_qual_b

長さ $ N $ の整数列 $ A~=~A_0,~A_1,~...,~A_{N\ -\ 1} $ があります。

$ A $ を $ K $ 回繰り返した長さ $ K\ \times\ N $ の整数列を $ B $ とします。たとえば $ A~=~1,~3,~2 $、$ K~=~2 $ のとき、 $ B~=~1,~3,~2,~1,~3,~2 $ です。

$ B $ の転倒数を $ 10^9\ +\ 7 $ で割った余りを求めてください。

ここで $ B $ の転倒数は、整数の順序対 $ (i,~j)~(0\ \leq\ i\ <\ j\ \leq\ K\ \times\ N\ -\ 1) $ であって $ B_i\ >\ B_j $ を満たすものの個数として定義されます。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 1\ \leq\ N\ \leq\ 2000 $
- $ 1\ \leq\ K\ \leq\ 10^9 $
- $ 1\ \leq\ A_i\ \leq\ 2000 $

### Sample Explanation 1

このケースでは $ B~=~2,~1,~2,~1 $ です。 - $ B_0\ >\ B_1 $ - $ B_0\ >\ B_3 $ - $ B_2\ >\ B_3 $ であり、$ B $ の転倒数は $ 3 $ です。

### Sample Explanation 2

$ A $ は同じ数を複数含むこともあります。

### Sample Explanation 3

$ 10^9\ +\ 7 $ で割った余りを出力することに注意してください。

## 样例 #1

### 输入

```
2 2
2 1```

### 输出

```
3```

## 样例 #2

### 输入

```
3 5
1 1 1```

### 输出

```
0```

## 样例 #3

### 输入

```
10 998244353
10 9 8 7 5 6 3 4 2 1```

### 输出

```
185297239```

# 题解

## 作者：chl090410 (赞：7)

## The Solution to AT_jsc2019_qual_b Kleene Inversion

### Description

有一个长度为 $N$ 的数组 $A$，数组 $B$ 由 $K$ 个数组 $A$ 首尾拼接而成，求数组 $B$ 中逆序对的个数。 

### Solution

设 $A$ 数组中有 $ans$ 对逆序对，$cnt$ 对顺序对。

设原数组中有 $(X,Y)$ 这一对逆序对，因为数组 $B$ 由 $K$ 个数组 $A$ 首尾拼接而成，所以在这 $K$ 个数组中都能找到 $Y$ 使 $(X,Y)$ 为逆序对。

同理，第二个数组中也有元素 $X$，在第二个及接下来的 $A$ 数组中也能找到元素 $Y$ 构成 $K-1$ 对逆序对。

以此类推，逆序对 $(X,Y)$ 在 $B$ 数组中共出现了 $\large\sum_{i=1}^K K-i+1$ 次，用等差数列求和公式可将其化简为 $\dfrac{K\times(K+1)}{2}$ 次。

而 $A$ 中共有 $ans$ 对逆序对，$B$ 数组中就一定有 $ans\times\dfrac{K\times(K+1)}{2}$ 对逆序对。

若你以为此题到此就结束了，那就大错特错了。

举个例子，$A$ 中的元素为 $1,2,3$，$K$ 为 $2$，$B$ 数组则为 $1,2,3,1,2,3$，按刚才的算法，$B$ 数组中就有 $0$ 对逆序对，但显然这个答案是错的，比如 $(3,1)$ 就是一对。

那么，问题到底出在哪里呢？

我们可以发现：$A$ 数组中除了有逆序对，还有一些顺序对，设其中一对为 $(S,T)$，那么虽然这一对不会被计入答案，但 $T$ 与下一个 $A$ 数组中的 $S$
 可以构成逆序对，而我们少算的，正是这部分逆序对。
 
 而这部分逆序对的数量计算起来也并不麻烦，设第一个 $A$ 数组中有顺序对 $(S,T)$，则后 $K-1$ 个 $A$ 数组中就有 $K-1$ 个 $S$ 与 $T$ 构成逆序对，共有 $K-1$ 对逆序对。
 
 类似的办法我们可以计算出第二个 $A$ 数组中的 $T$ 与其后面的 $S$ 可构成 $K-2$ 对逆序对，而逆序对 $(T,S)$ 共出现了 $\large\sum_{i=1}^K K-i=\dfrac{K\times(K-1)}{2}$ 次，因为有 $cnt$ 对顺序对，所以共可以产生 $cnt\times\dfrac{K\times(K-1)}{2}$ 对逆序对。
 
 综上，总共有 $ans\times\dfrac{K\times(K+1)}{2}+cnt\times\dfrac{K\times(K-1)}{2}$ 对逆序对。
 
 而 $N\le2000$，所以无论使用什么办法求逆序对、顺序对的个数都行。
 
 ### AC code 如下：
 
 ```
 #include<bits/stdc++.h>
#define int long long
#define p 1000000007
using namespace std;
int n,m,a[10005],ni[10005],s[10005],ans,cnt; 
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(a[i]>a[j]) ans++;
			if(a[i]<a[j]) cnt++;
		}
	}
	cout<<(ans*((m*(m+1)/2)%p)%p+cnt*((m*(m-1)/2)%p)%p)%p;
	return 0;
}

---

## 作者：BqtMtsZDnlpsT (赞：2)

[传送门](https://www.luogu.com.cn/problem/AT5165)

$\text{update}$：
- $2021/6/7$ 更新了 $O(N\log N+N)$ 的做法。

### 题意简述：
给你一个长度为 $N$ 的数组 $A$，其中元素为 $A_0 \sim A_{n-1}$。

使长度为 $N\times K$ 数组 $B$，为 $K$ 个 $A$ 首尾相连而成。

求 $B$ 中逆序对的数目 $\bmod\;10^9+7$。

### 思路分析：
- 首先可以想到按照一般做法，先按题意生成 $B$ 数组，再用树状数组或归并排序求逆序对，复杂度 $O(NK\log(NK))$。

- 然后就会发现上面做法慢就慢在它有好几组逆序对重复计算，比如 $A$ 数组中有一个逆序对 $(A_i,A_j)$，但是在 $B$ 数组中，因为复制了 $K$ 遍，所以可以发现存在一些数值上相等的逆序对：$(B_i,B_j)$、$(B_{i+n},B_{j+n})$……$(B_{i+n\times(K-1)},B_{j+n\times(K-1)})$，以及$(B_i,B_{j+n})$、$(B_{i+n},B_{j+2\times n})$ 这类的，都是在数值上相等的逆序对。

- 所以，在上述条件下，对于 $B_i$，有 $K$ 个 $B_j$ 与之对应，对于 $B_{i+n}$，有 $K-1$ 个 $B_j$ 与之对应……

- 最后我们发现，对于原数组 $A$ 中的任意一个逆序对，在 $B$ 中数值上相同的逆序对组数为：
$$\sum_{i=1}^{K}i$$

由高斯加法可以得到，组数为 $\dfrac{K\times (K+1)}{2}$。

所以，我们只要求出，$A$ 中逆序对个数，在乘上 $\dfrac{K\times (K+1)}{2}$ 即可。

真的结束了吗？

- 显然没有，我们发现在 $A$ 数组中比如 $i<j$ 且 $A_i<A_j$，但是在 $B$ 数组中可以发现 $j<i+n$ 且 $B_j>B_{i+n}$ 的一组逆序对。

- 所以我们 $N^2$ 考虑，在 $A$ 中，一个数 $A_i$ 前面有多少个比它小的，后面有多少个比它小的。
	- 后面的比它小的。就乘 $\dfrac{K\times (K+1)}{2}$（如上推导）。
    - 前面的比它小的。显然少了由 $B_i$ 与所有 $B_{j+n\times v}$（$v$ 为 $0$ 到 $K-1$ 之间的自然数）的 $K$ 组逆序对，所以乘 $\dfrac{K\times (K-1)}{2}$。

代码，复杂度 $O(N^2)$（其实挺短的）：

[记录](https://www.luogu.com.cn/record/51542543)

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define int long long
using namespace std;
const int M=1e9+7;
int n,k,a[2005],ans,l,r;
signed main()
{
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++){
		l=r=0;
		for(int j=1;j<i;j++)//前面比它小的
			if(a[j]<a[i])++l;
		for(int j=i+1;j<=n;j++)//后面比它小的
			if(a[j]<a[i])++r;
		ans=(ans+(l%M)*(k*(k-1)/2%M)%M)%M;//如上
		ans=(ans+(r%M)*(k*(k+1)/2%M)%M)%M;
	}
	printf("%lld\n",ans);
	return 0;
}
```

因为 $1\le N\le2000$，所以以上代码可以过。

但是：路漫漫其修远兮，吾将上下而求索。――屈原

~~而且也挺好想的。~~


定义在一个数组 $M$ 中：
1. 若 $i<j$ 且 $M_i>M_j$，则称 $(M_i,M_j)$ 为一组逆序对。
1. 若 $i<j$ 且 $M_i<M_j$，则称 $(M_i,M_j)$ 为一组顺序对。
1. 若 $i<j$ 且 $M_i=M_j$，则称 $(M_i,M_j)$ 为一组无序对。

- 所以，我们可以发现之前分析式子就是求 $A$ 中逆序对的数量 $\times\dfrac{K(K+1)}{2}$，加上 $A$ 中顺序对的数量 $\times\dfrac{K(K-1)}{2}$。

- 逆序对或顺序对的数量可以 $O(N\log N)$ 用归并排序或树状数组做，所以可以 $O(2\; N\log N)$ 完成。

- 但是可以发现，$A$ 数组中，一对数不是逆序对，就是顺序对或无序对。

- 我们发现 $1\le A_i\le 2000$，所以求无序对的数量可以用标记+桶，来统计每个数出现次数，对于一个出现 $x$ 次的数，其中每一个都可以与另外任意一个组合，形成一个无序对。所以总共形成的无序对个数为 $\dfrac{x(x-1)}{2}$ 个。

- 然后只要用 $A$ 中数对总个数 $-$ 逆序对个数 $-$ 无序对个数，就能得到顺序对个数。

代码（归并排序），复杂度约为 $O(N\log N+N)$（其实也挺短）：

[记录（快了好多）](https://www.luogu.com.cn/record/51588325)

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define int long long
using namespace std;
const int M=1e9+7;
int n,k,a[2005],c[2005],ans,q[2005],l[2005],yy,s1,s2;
void MS(int l,int r)//求逆序对数量
{
	if(l==r)return;
	int mid=(l+r)/2,i=l,j=mid+1,kk=l;
	MS(l,mid),MS(mid+1,r);
	while((i<=mid)&&(j<=r))
		if(a[i]<=a[j])c[kk++]=a[i++];
		else c[kk++]=a[j++],s1+=mid-i+1;
	while(i<=mid)c[kk++]=a[i++];
	while(j<=r)c[kk++]=a[j++];
	for(int v=l;v<=r;v++)a[v]=c[v];
}
signed main()
{
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		if(!q[a[i]])l[++yy]=a[i];//标记
		++q[a[i]];//桶
	}
	MS(1,n);
	for(int i=1;i<=yy;i++)s2+=(q[l[i]]*(q[l[i]]-1))/2;//无序对数量
	ans=((n*(n-1)/2-s1-s2)%M)*(k*(k-1)/2%M)%M;//加顺序对数量
	ans=(ans+(s1%M)*(k*(k+1)/2%M)%M)%M;//加逆序对数量
	printf("%lld\n",ans);
	return 0;
}
```

如果你不知道逆序对怎么做，移步[P1908](https://www.luogu.com.cn/problem/P1908)。

---

## 作者：dulinfan2023 (赞：0)

## 思路：
因为共有 $k$ 段 $A$ 序列，所以逆序对分为两种：

1. 在不同的 $A$ 序列中。
2. 在相同的 $A$ 序列中。

第 $1$ 种情况就是求出 $1 \le i \le n$，$1 \le j \le n$，$a_i>a_j$ 组成的数对的个数乘上 $\frac{k\times(k-1)}{2}$，表示对于所有第 $l$ 个序列和第 $r$ 个序列组成的数对，保证 $1 \le l \le r \le k$。

第 $2$ 种情况就是在所有 $k$ 个序列中的逆序对，共有 $A$ 序列的逆序对个数乘上 $k$。
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define il inline
int n,a[2005],k,s,ss;
const int mod=1e9+7;
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[j]>a[i])s++,s%=mod;
		}
	}
	int kk=k*(k-1)/2;
	kk%=mod;
	s*=kk;
	s%=mod;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(a[j]<a[i])ss++;
		}
	}
//	cout<<s<<" "<<kk<<" "<<ss<<" "<<k<<'\n';
	cout<<(s+ss*k%mod)%mod;
}
```
~~易如反掌~~

---

