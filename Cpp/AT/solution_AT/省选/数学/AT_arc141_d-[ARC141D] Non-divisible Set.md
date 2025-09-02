# [ARC141D] Non-divisible Set

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc141/tasks/arc141_d

正整数からなる集合 $ S $ について、任意の $ a,\ b\ \in\ S\ (a\neq\ b) $ について $ b $ が $ a $ の倍数でないとき、 $ S $ を「良い集合」と呼びます。

$ N $ 個の $ 1 $ 以上 $ 2M $ 以下の整数からなる集合 $ S=\lbrace\ A_1,\ A_2,\ \dots,\ A_N\rbrace $ が与えられます。

各 $ i=1,\ 2,\ \dots,\ N $ に対し、$ A_i $ を含む $ S $ の部分集合であって、要素数が $ M $ である「良い集合」が存在するか判定してください。

## 说明/提示

### 制約

- $ M\ \leq\ N\ \leq\ 2M $
- $ 1\ \leq\ M\ \leq\ 3\ \times\ 10^5 $
- $ 1\ \leq\ A_1\ <\ A_2\ <\ \dots\ <\ A_N\ \leq\ 2M $
- 入力される値はすべて整数

### Sample Explanation 1

$ A_1=1 $ を含む「良い集合」は明らかに $ \lbrace\ 1\rbrace $ しか存在せず、要素数は $ 1 $ しかないため、$ i=1 $ に対する答えは `No` です。 $ A_2=2 $ を含む「良い集合」としては例えば $ \lbrace\ 2,\ 3,\ 5\rbrace $ が考えられます。このことから $ i=2 $ に対する答えは `Yes` です。

## 样例 #1

### 输入

```
5 3
1 2 3 4 5```

### 输出

```
No
Yes
Yes
Yes
Yes```

## 样例 #2

### 输入

```
4 4
2 4 6 8```

### 输出

```
No
No
No
No```

## 样例 #3

### 输入

```
13 10
2 3 4 6 7 9 10 11 13 15 17 19 20```

### 输出

```
No
No
Yes
Yes
Yes
Yes
Yes
Yes
Yes
Yes
Yes
Yes
No```

# 题解

## 作者：tzc_wk (赞：4)

朴素实现需要用 dilworth 定理进行对偶后转最小链覆盖，赛时写的这坨东西也没能过去。

考虑抓住值域 $2m$ 和选出的数的个数 $m$ 之间的关系。显然对于所有形如 $k·2^i(k\in\text{odd})$ 的数，我们最多选出一个，因此总共可能选出的数的个数的上界就是 $m$，而要使选出的数的个数为 $m$，我们也必须恰好选择一个。

我们假设对于奇数 $k$，我们选择 $k·2^{p_k}$，那么合法的要求是 $\forall k_1\mid k_2,p_{k_2}<p_{k_1}$。因此我们考虑求出 $p_k$ 的上下界 $L_k,R_k$，这显然可以调和级数地预处理出来。

那么什么样的 $i$ 满足 $k·2^i$ 可能合法呢？答案是所有 $L_k\le i\le R_k$ 都合法，因为显然我们可以取 $p=\{R_1,R_3,\cdots,R_{k-2},i,L_{k+2},L_{k+4},\cdots,L_{2n-1}\}$。

这样总复杂度就是 $n\ln n$。

---

## 作者：white_carton (赞：2)

[更好的阅读体验](https://starback24.github.io)

[题目链接](https://atcoder.jp/contests/arc141/tasks/arc141_d)

锻炼思维的好题。

### 题意

给定大小为 $n$ 的**不可重集** $S$，值域为 $\left[1,2m\right]$，对于每个元素 $x$，求是否存在大小为 $m$ 的集合 $T\subseteq S$ 使 $x\in T$ 且 $\forall a,b\in T,a\nmid b$。

### 分析

对值域做一个分析。

把每个数拆成 $k\cdot2^p$ 的形式，其中 $k\in odd$，我们可以发现，在值域内最多有 $m$ 个不同的 $k$，对于同一个 $k$ 来说，显然不能同时选，因此我们将集合内的元素按照 $k$ 分类，可以把问题转化为有 $m$ 个集合，从每个集合中选一个数，使选出的数两两之间不包含整除关系。显然，如果没有 $m$ 个不同的 $k$，是全部无解的。

考虑一下两个数 $x=k_1\cdot2^{p_{1}},y=k_2\cdot2^{p_{2}}\left(x\le y\right)$ 有整除关系的条件：$k_1\mid k_2$ 且 $p_1\le p_2$。

每种 $k$ 都必须选一种，前者无法下手，所以我们只能从后者下手，合法的条件为 $k_1\mid k_2$ 且 $p_1>p_2$，也就是说 $k_i$ 的每个倍数的 $p$ 都必须小于 $p_i$。于是我们对每个 $p_i$ 求一个上界 $R_i$ 和一个下界 $L_i$，对于 $L_i\le j\le R_i$，我们可以构造 $p=\left\{R_1,R_3,\ldots,R_{j-2},j,L_{j+2},\ldots,L_{2n-1}\right\}$，所以每个在上下界内的数都可取。

### code

```cpp
//缺省源
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Dor(i,a,b) for(int i=a;i>=b;i--)
#define pb push_back
const int N=3e5+100;
int n,m;
int a[N<<1],vis[N<<1];
int l[N<<1],r[N<<1];
vector<int> v[N<<1],d[N<<1];
void no(){
	For(i,1,n){
		cout<<"No"<<endl;
	}
	exit(0);
}
int ans[N<<1];
signed main(){
	cin>>n>>m;
	For(i,1,n){
		cin>>a[i];
		vis[a[i]]=1;
	}
	for(int i=1;i<=2*m;i+=2){
		for(int j=i;j<=2*m;j*=2)
			v[i].pb(j);
		r[i]=v[i].size()-1;
	}
	for(int i=1;i<=2*m;i+=2){
		while(r[i]>=0&&!vis[v[i][r[i]]])
			r[i]--;
		if(r[i]<0)
			no();
		for(int j=i+(i<<1);j<=2*m;j+=(i<<1)){
			r[j]=min(r[j],r[i]-1);
			d[j].pb(i);
		}
	}
	for(int i=2*m-1;i>=0;i-=2){
		while(l[i]<v[i].size()&&!vis[v[i][l[i]]])
			l[i]++;
		if(l[i]>v[i].size())
			no();
		for(int j:d[i]){
			l[j]=max(l[j],l[i]+1);
		}
	}
	for(int i=1;i<=2*m;i+=2){
		For(j,l[i],r[i]){
			ans[v[i][j]]=1;
		}
	}
	For(i,1,n){
		if(ans[a[i]]){
			cout<<"Yes"<<endl;
		}
		else{
			cout<<"No"<<endl;
		}
	}
}
//吾日三省吾身
//输入多而不read()乎？
//1e18而不开longlong乎？
//多测不清乎？
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc141_d)

**题目大意**

> 给定 $n$ 个数的集合，值域 $[1,2m]$，对于每个 $a_i$ 求出是否存在一个大小为 $m$ 的子集包含 $a_i$ 且任意两个数不为倍数关系。
>
> 数据范围：$m\le 3\times 10^5$。

**思路分析**

注意到值域很小，因此考虑每个数的奇数部分，即把每个数拆成 $k\times 2^d$ 其中 $k$ 为奇数。

对于同一个 $k$，显然至多选一个元素，又因为不同的 $k$ 只有 $m$ 个，因此每个 $k$ 恰好贡献一个数。

对于 $p\mid k$，那么 $p\times 2^c$ 和 $k\times 2^d$ 同时选必须有 $c>d$，那么对于每个 $k$，其因数全部选尽可能大的 $2^c$，倍数全部选尽可能小的 $2^c$。

具体的构造直接让因数从小到到大贪心取，倍数从大到小贪心取即可。

因此对于每个 $k$，合法的 $d$ 是一个区间，且该区间可以快速求出，即 $l_k\ge \max_{k\mid p}\{l_p+1\},r_k\le \max_{p\mid k}\{r_p-1\}$，找到区间内第一个和最后一个存在的 $d$ 即可。

时间复杂度 $\mathcal O(m\log m)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=6e5+5;
vector <int> q[MAXN];
int a[MAXN],w[MAXN],l[MAXN],r[MAXN];
signed main() {
	int n,m;
	scanf("%d%d",&n,&m),m<<=1;
	for(int i=1;i<=n;++i) {
		scanf("%d",&a[i]);
		while(a[i]%2==0) ++w[i],a[i]>>=1;
		q[a[i]].push_back(w[i]);
	}
	for(int i=1;i<=m;i+=2) if(q[i].empty()) {
		for(int j=1;j<=n;++j) puts("No");
		return 0;
	}
	for(int i=1;i<=m;i+=2) l[i]=0,r[i]=20;
	for(int i=1;i<=m;i+=2) {
		if(q[i].front()>r[i]) {
			for(int j=1;j<=n;++j) puts("No");
			return 0;
		}
		r[i]=*--upper_bound(q[i].begin(),q[i].end(),r[i]);
		for(int j=i*3;j<=m;j+=i*2) r[j]=min(r[j],r[i]-1);
	}
	for(int i=m-1;i>0;i-=2) {
		for(int j=i*3;j<=m;j+=i*2) l[i]=max(l[i],l[j]+1);
		if(q[i].back()<l[i]) {
			for(int j=1;j<=n;++j) puts("No");
			return 0;
		}
		l[i]=*lower_bound(q[i].begin(),q[i].end(),l[i]);
	}
	for(int i=1;i<=m;i+=2) if(l[i]>r[i]) {
		for(int j=1;j<=n;++j) puts("No");
		return 0;
	}
	for(int i=1;i<=n;++i) puts(l[a[i]]<=w[i]&&w[i]<=r[a[i]]?"Yes":"No");
	return 0;
}
```

---

## 作者：JWRuixi (赞：1)

### 题意

给定大小为 $n$ 的不可重整数集合 $S$，满足 $\forall x \in S : x \in [1, 2m]$。

求对于每个 $x \in S$，是否存在集合 $T$ 满足 $T \subseteq S, |T| = m, x \in T$，且 $\forall x, y \in T : x \not \mid y$。

$1 \le m \le n \le 2m, m \le 3 \times 10^5$，提交地址：<https://atcoder.jp/contests/arc141/tasks/arc141_d>。

### 分析

先考虑若 $S = [1, 2m]$ 怎么做。

打表发现对于一个大于 $m$ 的奇数，一定要出现在 $T$ 中。我们不妨考虑将奇数提取出来，依据它们分组。考虑每个偶数都可以写成 $2^kx$，其中 $x$ 是一个奇数，依据 $x$ 分组。

有一个极强的限制是 $|T| = m$，不难发现此时恰分成 $m$ 组。进一步的观察告诉我们同一组中只能选择一个，所以我们的限制变成每个组中恰选一个。

分析一下现在的限制：要求两个组所选的书之间不存在倍数关系。设 $(x, y)$ 表示的数为 $x2^y$，考虑表格上 $(x, y)$ 和 $(x^\prime,y^\prime)$ 之间有倍数关系的条件（不妨设 $x < x^\prime$）：$x \mid x^\prime \land y \le y^\prime$。

我们不能控制第一部分，但是我们能控制第二部分，所以若数 $x$ 选择了 $y$，它所有的倍数选择的 $y^\prime$ 就必须小于它。这个递推关系显然是线性无后效性的。所以正反个做一遍 dp 就能解决这一部分，复杂度 $\mathcal O(m\ln m)$。

考虑如果 $S \subseteq [1, 2m]$ 怎么办，我们只需要在递推的时候找到第一个在 $S$ 中的就可以了，复杂度 $\mathcal O(m\ln m + n)$。

### Code

提交记录：<https://atcoder.jp/contests/arc141/submissions/45969420>。

---

