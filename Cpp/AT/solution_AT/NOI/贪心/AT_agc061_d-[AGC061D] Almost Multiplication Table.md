# [AGC061D] Almost Multiplication Table

## 题目描述

给定正整数 $N,\ M$ 和一个 $N \times M$ 的正整数矩阵 $A_{i,j}$。对于两个**严格单调递增**的正整数序列 $X = (X_1, \ldots, X_N),\ Y = (Y_1, \ldots, Y_M)$，定义惩罚值 $D(X, Y)$ 为 $\max_{1 \leq i \leq N,\ 1 \leq j \leq M} |X_i Y_j - A_{i,j}|$。

请你求出能够最小化 $D(X, Y)$ 的两个**严格单调递增**正整数序列 $X,\ Y$。

## 说明/提示

### 限制条件

- $1 \leq N, M \leq 5$
- $1 \leq A_{i,j} \leq 10^9$（$1 \leq i \leq N$，$1 \leq j \leq M$）
- 输入中的所有数值均为整数。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1 1
853922530```

### 输出

```
0
31415
27182```

## 样例 #2

### 输入

```
3 3
4 4 4
4 4 4
4 4 4```

### 输出

```
5
1 2 3 
1 2 3```

## 样例 #3

### 输入

```
3 4
4674 7356 86312 100327
8737 11831 145034 167690
47432 66105 809393 936462```

### 输出

```
357
129 216 1208 
39 55 670 775```

# 题解

## 作者：FZzzz (赞：2)

牛逼题，在肝 EF 之前先来写个这题题解。

先二分答案 $k$，那么相当于要求 $a_{i,j}-k\le x_iy_j\le a_{i,j}+k$。不妨设 $x_n\le y_m$，否则对称处理即可。考虑调整法，初始时置 $x_i=1$，$y_i=+\infty$，之后不断重复以下流程：
1. 依次对 $i=1\dots n$，令 $x_i\gets\max\left\{x_i,x_{i-1}+1,\max\limits_{j=1}^m\left\lceil\dfrac{a_{i,j}-k}{y_j}\right\rceil\right\}$；
2. 依次对 $i=m\dots1$，令 $y_i\gets\min\left\{y_i,y_{i+1}-1,\max\limits_{j=1}^n\left\lfloor\dfrac{a_{j,i}+k}{x_j}\right\rfloor\right\}$；
3. 若 $x_n>y_m$ 或 $y_1\le0$，宣布无解；
4. 若当前的 $x,y$ 合法，宣布找到了一组解。

考虑这个做法的正确性。首先发现 $x_i$ 不会减少，$y_i$ 不会增加，那么可以证明：在任意时刻，任何合法解的 $x_i$ 都不小于当前的 $x_i$，$y_i$ 都不大于当前的 $y_i$。故若算法宣布无解，则一定无解。

又，如果在某一轮中所有 $x_i$ 都没有发生变化，则容易发现当前解一定合法。所以若有解，则算法一定能找到一组解。那么我们证明了这个算法确实可以在有限时间内正确解决问题。

考虑算法的时间复杂度。每一轮的第二步结束后我们都有 $x_ny_m\le a_{n,m}+k$，故当 $x_n>\sqrt{a_{n,m}+k}$ 时算法一定会宣布无解并退出。而容易发现 $k$ 的上界是值域（记为 $a$），也就是说 $x_n$ 至多增加 $O(\sqrt a)$ 次，$x_i$ 至多一共增加 $O(n\sqrt a)$ 次。

又因为算法在除最后一轮以外的每一轮里都会改变至少一个 $x_i$，所以算法至多执行 $O(n\sqrt a)$ 轮。设 $n,m$ 同阶，则算法的时间复杂度为 $O(n^3\sqrt a)$。算上外层的二分，我们以 $O(n^3\sqrt a\log a)$ 的时间解决了原问题。
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
inline ll read(){
	ll x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-') f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=5+5;
int n,m,a[maxn][maxn],x[maxn],y[maxn];
const int inf=2e9;
bool check(int k){
	for(int i=1;i<=n;i++) x[i]=1;
	for(int i=1;i<=m;i++) y[i]=inf;
	y[m+1]=inf+1;
	auto chk=[k](){
		for(int i=1;i<=n;i++) if(x[i]<=0) return 0;
		for(int i=1;i<=m;i++) if(y[i]<=0) return 0;
		for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
			if(abs(1ll*x[i]*y[j]-a[i][j])>k) return 0;
		return 1;
	};
	while(1){
		for(int i=1;i<=n;i++){
			x[i]=max(x[i],x[i-1]+1);
			for(int j=1;j<=m;j++)
				x[i]=max(x[i],(a[i][j]-k-1)/y[j]+1);
		}
		for(int i=m;i>0;i--){
			y[i]=min(y[i],y[i+1]-1);
			for(int j=1;j<=n;j++)
				y[i]=min(y[i],(a[j][i]+k)/x[j]);
		}
		if(y[1]<=0||x[n]>y[m]||chk()) break;
	}
	if(chk()) return 1;
	for(int i=1;i<=n;i++) x[i]=inf;
	for(int i=1;i<=m;i++) y[i]=1;
	x[n+1]=inf+1;
	while(1){
		for(int i=1;i<=m;i++){
			y[i]=max(y[i],y[i-1]+1);
			for(int j=1;j<=n;j++)
				y[i]=max(y[i],(a[j][i]-k-1)/x[j]+1);
		}
		for(int i=n;i>0;i--){
			x[i]=min(x[i],x[i+1]-1);
			for(int j=1;j<=m;j++)
				x[i]=min(x[i],(a[i][j]+k)/y[j]);
		}
		if(x[1]<=0||x[n]<y[m]||chk()) break;
	}
	return chk();
}
int main(){
#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif
	n=read();
	m=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) a[i][j]=read();
	int l=0,r=1e9;
	while(l<r){
		int mid=l+(r-l)/2;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	check(r);
	printf("%d\n",r);
	for(int i=1;i<=n;i++) printf("%d ",x[i]);
	printf("\n");
	for(int i=1;i<=m;i++) printf("%d ",y[i]);
#ifdef LOCAL
	fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
#endif
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc061_d)

**题目大意**

> 给定 $n\times m$ 矩阵 $a$，构造单调递增数列 $x_1\sim x_n,y_1\sim y_m$ 最小化 $\max_{i,j}|a_{i,j}-x_iy_j|$。
>
> 数据范围：$n,m\le 5,a_{i,j}\le 10^9$。

**思路分析**

先二分 $k$，那么相当于 $l_{i,j}\le x_iy_j\le r_{i,j}$，其中 $l_{i,j}=\max(0,a_{i,j}-k),r_{i,j}=a_{i,j}+k$。

不妨假设 $x_n\le y_m$，那么考虑调整法，从最极端情况 $a_i=1,y_i=+\infty$ 开始调整，且每次都进行尽可能少的调整：

- 从小到大考虑 $x_i$，将 $x_i$ 与 $x_{i-1}+1$ 和 $\left\lceil\dfrac{l_{i,j}}{y_j}\right\rceil$ 取 $\max$。
- 从大到小考虑 $y_j$，将 $y_j$ 与 $y_{j+1}-1$ 和 $\left\lfloor\dfrac{r_{i,j}}{x_i}\right\rfloor$ 取 $\min$。
- 如果 $x_n>y_m$ 或 $y_1<1$ 无解，如果当前 $x,y$ 合法那么结束。

然后交换 $x,y$ 再做一次。

感性理解一下这个算法的正确性：首先我们每次都进行了尽可能少的调整，那么 $x_i$ 一定小于任何一组合法的 $x$，$y_i$ 一定大于任何一组合法的 $y$，那么每次调整直到 $x_n>y_m$ 就说明这个区间里根本夹不到任何一组解。

然后分析一下复杂度，我们时刻都有 $x_ny_m\le r_{n,m}$，且 $x_n\le y_m$，那么 $x_n$ 最多 $\mathcal O(\sqrt V)$ 级别。

由于 $x_i$ 递增，那么总和为 $\mathcal O(n\sqrt V)$，且每次不可能让所有 $x$ 都不变，因此调整总数为 $\mathcal O(n\sqrt V)$。

复杂度 $\mathcal O(nm(n+m)\sqrt V\log V)$。

**代码呈现**

```cpp
#include<bits/stdc++.h> 
#define ll long long
using namespace std;
const ll inf=2e9;
int n,m;
ll a[8][8],s[8][8],t[8][8],x[8],y[8];
bool check(ll k) {
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) {
		s[i][j]=max(1ll,a[i][j]-k),t[i][j]=a[i][j]+k;
	}
	auto check=[&]() {
		for(int i=1;i<=n;++i) if(x[i]<=0) return false;
		for(int j=1;j<=m;++j) if(y[j]<=0) return false;
		for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) {
			if(x[i]*y[j]<s[i][j]||t[i][j]<x[i]*y[j]) return false; 
		}
		return true;
	};
	for(int i=1;i<=n;++i) x[i]=1;
	for(int i=1;i<=m;++i) y[i]=inf;
	x[0]=0,y[m+1]=inf+1;
	while(true) {
		for(int i=1;i<=n;++i) {
			x[i]=max(x[i],x[i-1]+1);
			for(int j=1;j<=m;++j) x[i]=max(x[i],(s[i][j]+y[j]-1)/y[j]);
		}
		for(int j=m;j>=1;--j) {
			y[j]=min(y[j],y[j+1]-1);
			for(int i=1;i<=n;++i) y[j]=min(y[j],t[i][j]/x[i]);
		}
		if(check()||x[n]>y[m]||y[1]<=0) break;
	}
	if(check()) return true;
	for(int i=1;i<=n;++i) x[i]=inf;
	for(int i=1;i<=m;++i) y[i]=1;
	y[0]=0,x[n+1]=inf+1;
	while(true) {
		for(int j=1;j<=m;++j) {
			y[j]=max(y[j],y[j-1]+1);
			for(int i=1;i<=n;++i) y[j]=max(y[j],(s[i][j]+x[i]-1)/x[i]);
		}
		for(int i=n;i>=1;--i) {
			x[i]=min(x[i],x[i+1]-1);
			for(int j=1;j<=m;++j) x[i]=min(x[i],t[i][j]/y[j]);
		}
		if(check()||x[n]<y[m]||x[1]<=0) break;
	}
	return check();
}
signed main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) scanf("%lld",&a[i][j]);
	ll l=0,r=inf,res=inf;
	while(l<=r) {
		ll mid=(l+r)>>1;
		if(check(mid)) res=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%lld\n",res),check(res);
	for(int i=1;i<=n;++i) printf("%lld ",x[i]); puts("");
	for(int j=1;j<=m;++j) printf("%lld ",y[j]); puts("");
	return 0;
}
```

---

## 作者：苹果蓝17 (赞：0)

问 $\max$ 的 $\min$，首先二分答案 $K$。设答案的上界 $mx=\max\{A_{i,j},n^2+m^2\}$。

现在问题变为构造 $1 \leq x_1 < \cdots x_n$，$1 \leq y_1 < \cdots y_m$ 使得 $\forall i,j,x_iy_j \in [A_{i,j}-K,A_{i,j}+K]$。

一个很神奇的套路：调整法。考虑令 $x_i$ 始终作为答案的下界，$y_i$ 始终作为答案的上界。初始设 $x_i=i,y_i=mx+K+i$。不断执行以下操作：

- 顺序枚举每个 $i$，令 $x_i \leftarrow \max\{x_i,x_{i-1}+1\}$。检查每个 $j$，若存在 $x_i y_j < A_{i,j}-K$，令 $x_i \leftarrow \lceil \dfrac{A_{i,j}-K}{y_j} \rceil$。

- 倒序枚举每个 $j$，令 $y_j \leftarrow \min\{y_j,y_{j+1}-1\}$。检查每个 $i$，若存在 $x_i y_j > A_{i,j}+K$，令 $y_j \leftarrow \lfloor \dfrac{A_{i,j}+K}{y_j} \rfloor$。

那么每经过两轮，$\sum x_n$ 严格增加，$\sum y_m$ 严格减少，于是一定能找到解或发现无解。然而值域过大，时间复杂度无法接受。

考虑枚举 $x_n,y_m$ 间的大小关系，不妨设 $x_n \leq y_m$（$x_n > y_m$ 的情况可以交换 $n,m$）。那么在每一轮第一种操作后 $x_n y_m \leq mx+K$，于是 $x_n \leq \sqrt{mx+K}$，$\sum x_n \leq n\sqrt{mx+K}$。这意味着在 $O(n\sqrt{mx})$ 轮内必然能结束操作。

总时间复杂度 $O(nm(n+m) \sqrt{mx} \log mx)$。

[**Code**](https://atcoder.jp/contests/agc061/submissions/39066710)

---

