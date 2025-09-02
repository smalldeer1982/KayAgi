# [AGC053A] >< again

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc053/tasks/agc053_a

長さ $ N $ の文字列 $ S $ があります。$ S $ の各文字は `<` または `>` です。

要素数 $ N+1 $ の非負整数列 $ X_0,X_1,\ldots,X_N $ は、すべての $ 1\ \leq\ i\ \leq\ N $ について次の条件を満たすとき *良い非負整数列* と呼ばれます。

- $ S_i $ が `<` のとき : $ X_{i-1}\ <\ X_i $
- $ S_i $ が `>` のとき : $ X_{i-1}\ >\ X_i $

良い非負整数列 $ A $ が与えられるので、この数列をできるだけ多くの良い非負整数列に分解してください。 つまり、正の整数 $ k $ および $ k $ 個の良い非負整数列 $ B_1,B_2,\ldots,\ B_k $ であって、次の条件を満たすもののうち、 $ k $ が最大のものを $ 1 $ つ求めてください。

- すべての $ 0\ \leq\ i\ \leq\ N $ について $ B_1,\ldots,B_k $ の $ i $ 項目の値の合計は $ A_i $ と等しい。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ 0\ \leq\ A_i\ \leq\ 10^4 $
- $ S $ は `<` と `>` からなる長さ $ N $ の文字列である。
- $ A $ は良い非負整数列である。特に、要素数は $ N+1 $ である。

## 样例 #1

### 输入

```
3
<><
3 8 6 10```

### 输出

```
2
1 5 4 7
2 3 2 3```

# 题解

## 作者：joke3579 (赞：2)

## $\text{Statement}$

给定长为 $n$ 的字符串 $S$，其由 `<` 与 `>` 组成。

我们称一个长度为 $n+1$ 的非负整数序列 $x=(x_0,x_1,\dots,x_n)$ 是好的，当且仅当对于任意 $1\le i\le n$，有：
- 若 $S_i$ 为 `<`，则 $x_{i-1} < x_i$；
- 若 $S_i$ 为 `>`，则 $x_{i-1} > x_i$；

给定一个好的非负整数序列 $A$，你需要将其拆分为尽可能多的好的非负整数序列。具体地说，你需要找到正整数 $k$ 以及 $k$ 个好的非负整数序列 $B_1,B_2,\dots,B_k$，满足对于任意 $0\le i \le n$，$\sum_{j=1}^k B_{j,i} = A_i$。

你需要最大化 $k$ 的值。输出这个值，以及你所构造的 $k$ 个长度为 $n + 1$ 的串。   
如果有多组解，输出任意一组即可。

$1\le n \le 100, 0\le a_i\le 10^4$。

## $\text{Solution}$

令 $d_i = |A_i - A_{i-1}|$。我们断言，$k = \min_{i=1}^n d_i$。

证明：   
首先证明 $k \le \min_{i=1}^n d_i$。   
由 $B$ 序列的性质，有 $d_i = \sum_{j=1}^k |B_{j,i} - B_{j,i-1}|$。由于 $B$ 是好的，因此在求和项内各项必定 $>0$。因此 $d_i = \sum_{j=1}^k |B_{j,i} - B_{j,i-1}| \ge \sum_{j=1}^k 1 = k$。因此有 $k \le \min_{i=1}^n d_i$。

然后证明 $k$ 可以取到所确定的最大值。   
我们可以将 $A$ 序列的每个值均匀地分给 $k$ 个 $B$ 序列。即 $B_{i,j} = \left\lfloor\frac{A_j + i - 1}k\right \rfloor$。容易发现通过这样的分法可以使 $k = \min_{i=1}^n d_i$。

因此我们证明了断言。  
证明同样给出了构造方法，因此我们可以在 $O(nk)$ 的时间复杂度内完成构造。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i,s,t) for (register int i = (s), i##_ = (t) + 1; i < i##_; ++ i)
int n, a[105], k = 1e9; 
char ch[105];
signed main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> n >> ch + 1; rep(i,0,n) cin >> a[i];
	rep(i,1,n) k = min(k, abs(a[i] - a[i - 1]));
	cout << k << '\n';
	rep(i,1,k) {
		rep(j,0,n) cout << (a[j] + i - 1) / k << ' ';
		cout << '\n';
	}
}
```

---

## 作者：abensyl (赞：0)

原题：[AGC053A >< again](https://www.luogu.com.cn/problem/AT_agc053_a)。

一道构造好题。

## 思路

先考虑求出 $k$ 的值，可以使用二分查找。

在二分时，我们的判断条件应该是前后两数在最有情况下不同，那么也就是说换种说法，令 $mid$ 表示二分中点，$a_i$ 需要满足下述两个条件：

- 若两数之间的符号是大于号，要求前数与后数除以 $mid$ 后取整值不相同，且前数对 $mid$ 取模的取模的值要大于后数；  
- 若两数之间的符号是小数号，要求前数与后数除以 $mid$ 后取整值不相同，且前数对 $mid$ 取模的取模的值要小于后数；  

在查找到 $k$ 的值之后，那么需要构造数列方案，这个过程比较简单，对于 $j\in [1,a_i \bmod r]$，$b_{i,j}=\lfloor{a_i\over k}\rfloor+1$，对于 $j\in [(a_i \bmod r)+1,n]$，$b_{i,j}=\lfloor{a_i\over k}\rfloor$。

最后输出构造好的 $b$ 数组即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e4+3;
int n,a[N],m[N];
short g[N][N];
string s;
bool check(int u) { //二分 check 函数
	bool flag=1;
	for(int i=2;i<=n;++i) {
		if(abs(a[i]/u-a[i-1]/u)>1) continue;
		if(a[i]/u==a[i-1]/u) flag=0;
		if(a[i-1]%u>a[i]%u&&s[i-1]=='<') flag=0;
		if(a[i-1]%u<a[i]%u&&s[i-1]=='>') flag=0;
	} return flag;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	++n;
	cin>>s;
	s=" "+s;
	a[0]=-1e9;
	for(int i=1;i<=n;++i) cin>>a[i];
	int l=1,r=10000;
	while(l<=r) {
		int mid=l+r>>1;
		if(check(mid)) l=mid+1;
		else r=mid-1;
	}	cout<<r<<'\n';
    //二分查找 k
	for(int i=1;i<=n;++i) m[i]=a[i]%r;
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m[i];++j)
			g[j][i]=a[i]/r+1;
		for(int j=m[i]+1;j<=r;++j)
			g[j][i]=a[i]/r;
	} //构造答案
	for(int i=1;i<=r;++i) {
		for(int j=1;j<=n;++j) {
			cout<<g[i][j]<<' ';
		} cout<<'\n';
	} //输出答案
	return 0;
}
```

[我的 AC 记录。](https://www.luogu.com.cn/record/116016533)

---

