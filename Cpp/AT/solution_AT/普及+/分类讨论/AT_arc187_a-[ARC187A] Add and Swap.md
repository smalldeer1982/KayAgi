# [ARC187A] Add and Swap

## 题目描述

给定两个整数 $N,K$ 与一个长度为 $N$ 的数列 $A=(A_1,\dots,A_N)$。

问是否能对 $A$ 执行不超过 $500000$ 次以下的操作，使 $A$ 变为单调不减数列：

- 选择一个 $i$ 满足 $1\le i<N$，将 $A_{i+1}+k \to A_i$ 且 $A_{i}\to A_{i+1}$，注意两种操作同时进行。

如果可以，请输出具体方案。

## 说明/提示

输入的所有数字均为整数。

$2\le N\le 50$

$1\le K\le 50$

$1\le A_i\le 50$

Translated by @[ARIS2_0](https://www.luogu.com.cn/user/1340759)

## 样例 #1

### 输入

```
3 2
3 6 4```

### 输出

```
Yes
1
2```

## 样例 #2

### 输入

```
3 3
1 5 8```

### 输出

```
Yes
2
2 2```

# 题解

## 作者：GoldSpade (赞：5)

### 题意

长为 $n$ 的正整数序列 $a$，操作 $m$ 次：

- 每次操作选择一个 $i(1 \le i < n)$，并交换 $a_i$ 和 $a_{i+1}$，然后使 $a_i \gets a_i + K$。

- $n,K$ 和序列 $a$ 给定，你需要输出让序列 $a$ **非严格递增**的某一个操作序列 $i_1,i_2,\dots,i_m$ 或报告无解。

### 思路

以下的递增都指非严格单调递增，即 $\forall 1\le i < j \le n$，$a_i \le a_j$。

容易发现的一点是**相邻的两项 $\color{black}a_i,a_{i+1}$ 可以通过两次操作变成 $\color{black} a_i+K,a_{i+1}+K$**。我们先挑战让 $a_1,a_2,\dots,a_{n-1}$ 变成递增序列，容易有个简单的思路就是按 $i=2,3,\dots,n-1$ 的顺序，用上面的方法反复使 $a_i \gets a_i + K$, $a_{i+1} \gets a_{i+1}+K$ 直到 $a_{i-1} \le a_i$。

接下来序列只剩下 $a_{n-1}$ 和 $a_n$ 的关系不确定了。

1. 当 $a_{n-1} \le a_n$ 时，整个序列就递增了。

2. 当 $a_{n-1} > a_n$ 时，若只选择 $n-1$ 进行操作，发现有可能 $a_n > a_{n-1}+K$，交换无数次都无法递增，就陷入僵局了。借鉴前面的思路，选择 $n-2$ 进行操作直到 $a_n \le a_{n-1}+K$，然后选择 $n-1$ 操作一次，于是 $a_{n-1} \le a_n$ 了。

最后，再反复操作直到整个序列递增即可。

----

Tips：事实上，上述讨论不包含所有情况，分析一下会发现 $n=2$ 时并不能选择 $n-2$ 来操作，因此有以下三种情况：

1. $a_1 \le a_2$，无需操作。

2. $a_1 > a_2$ 且 $a_2+K \le a_1$，选择 $i=1$ 进行一次操作。

3. $a_1 > a_2$ 且 $a_2+K > a_1$，操作 $114514^{1919810}$ 次都没法子，输出 `No`。

```cpp
#include <bits/stdc++.h>
#define FASTIO ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define rep(i, l, r) for (register int i = l; i <= r; i++)
#define per(i, r, l) for (register int i = r; i >= l; i--)
using namespace std;
const int N = 5e5+5, M = 3e4+5, mod = 1e9+7;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
int n, K;
LL a[N];
vector<int> res;
#define pb(x) push_back(x)
int main() {
	FASTIO;
	cin >> n >> K;
	rep(i, 1, n) cin >> a[i];
	if (n == 2) {
		if (a[1] <= a[2]) {
			cout << "Yes\n";
			cout << "0";
			return 0;
		}
		else if (a[2]+K > a[1]) return cout << "No\n", 0;
		else {
			cout << "Yes\n";
			cout << "1\n1";
			return 0;
		}
	}
	rep(i, 2, n-1) {
		while (a[i] < a[i-1]) {
			a[i] += K, a[i+1] += K;
			res.pb(i), res.pb(i);
		}
	}
	if (a[n] < a[n-1]) {
		while (a[n-1] < a[n]+K) {
			a[n-1]+=K, a[n-2]+=K;
			res.pb(n-2), res.pb(n-2);
		}
		res.pb(n-1);
		swap(a[n-1], a[n]);
		a[n-1]+=K;
		while (a[n-1] < a[n-2]) {
			res.pb(n-1), res.pb(n-1);
			a[n-1] += K, a[n] += K;
		}
	}
	cout << "Yes\n" << res.size() << '\n';
	for (auto it : res) cout << it << ' ';
	return 0;
}
```

---

## 作者：Hadtsti (赞：4)

### 题目分析

这个操作方式很神秘啊，怎么做？但是看到 $N,K,A_i$ 都是 $50$ 级别，而操作次数限制在 $5\times 10^5$ 且不需要最优，这意味着我们使用一些比较不优的做法也可以通过。

我们考虑如果 $K$ 是 $0$ 的话就是冒泡排序。那么我们完全可以通过类似的方式在保持其他数相对顺序不变的前提下移动一个数。如果我们把一个数移到某个位置再移回来，可以发现这样的操作具有很好的性质：经过的数都加上了 $K$，而这个数本身加上了若干个 $K$。形式化地来说，我们可以使用 $2m$ 次操作，使得对于任意一个 $m< i\le n$，使得 $\forall i-m\le j<i,a_j\leftarrow a_j+K$，而 $a_i\leftarrow a_i+mK$。

这有什么帮助呢？我们分析差分序列 $b_i=a_i-a_{i-1}$（$a_0=0$），发现上述操作使得 $b_{i-m}\leftarrow b_{i-m}+K,b_i\leftarrow b_i+(m-1)\times K,b_{i+1}\leftarrow b_{i+1}-m\times K$。我们发现它把 $b_{i+1}$ 这件事情非常不优，我们不妨直接强制 $i=n$，那么一次操作就可以在不减小其他 $b$ 的情况下将一个 $b_i$ 增加 $K$。那么我们只需要不断进行这种操作就一定可以把 $b_2\sim b_{n-1}$ 变成非负的。对于 $b_n$，我们在操作过程中把它也加了一下，但当 $n=2$ 的时候仅通过上述操作 $b_n$ 是一定不会改变的，需要特判。其他情况，如果 $b_n$ 还没变成非负的我们就再随便做几次操作即可。

分析操作次数，最大应该是 $(\sum\limits_{i=2}^{n-1}2[b_i<0]\lceil\frac{-b_i}K\rceil(n-i))+2[b_n<0]\lceil\frac{-b_n}K\rceil\le n^2A_i$。可以通过。

### 代码实现


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[55];
vector<int>ans;
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	if(n==2)
	{
		if(a[1]<=a[2]) 
			puts("Yes\n0");
		else
		{
			if(a[2]+k<=a[1])
				puts("Yes\n1\n1");
			else
				puts("No");
		}
		return 0;
	}
	for(int i=n;i;i--)
		a[i]-=a[i-1];
	for(int i=1;i<n;i++)
		while(a[i]<0)
		{
			for(int j=n-1;j>=i;j--)
				ans.push_back(j);
			for(int j=i;j<n;j++)
				ans.push_back(j);
			a[i]+=k;
			a[n]+=(n-i-1)*k;
		}
	while(a[n]<0)
	{
		for(int j=n-1;j;j--)
			ans.push_back(j);
		for(int j=1;j<n;j++)
			ans.push_back(j);
		a[n]+=(n-2)*k;
	}
	printf("Yes\n%d\n",ans.size());
	for(int i:ans)
		printf("%d ",i);
	return 0;
}
```

---

## 作者：Binah_cyc (赞：4)

一道脑电波题。

首先，我们注意到同一个位置连续操作两次等价于将它和它后面的数增加 $k$。因此，对于 $i \in [2,n-1]$，如果 $a_{i-1}>a_i$，我们都可以通过在 $a_i$ 的位置一直加 $k$ 的方式来使 $a_{i-1}<a_i$。

但是，对于 $a_{n-1}>a_n$，我们却不能这样做。理由很简单：操作的位置不能是 $n$。因此，我们需要进行一些特殊处理。

现在，我们有三个数 $a_{n-2},a_{n-1},a_n$。它们满足 $a_{n-2} \leq a_{n-1} > a_n$。

我们首先操作两次 $n-2$，此时序列变成 $a_{n-2}+k,a_{n-1}+k,a_n$。

随后，我们再操作一次 $n-1$，序列就会变成 $a_{n-2}+k,a_{n}+k,a_{n-1}+k$。这时候，序列满足 $a_n+k<a_{n-1}+k$。但是我们无法保证 $a_{n-2}+k$ 和 $a_n+k$ 的关系。现在只需要不断操作 $n-1$ 即可。

那么什么时候是无解的呢？就是在 $n=2,a_1>a_2 \land a_2+k>a_1$ 的时候。

代码
```c
// Problem: A - Add and Swap
// Contest: AtCoder - AtCoder Regular Contest 187
// URL: https://atcoder.jp/contests/arc187/tasks/arc187_a
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Author: Binah_cyc

#include<bits/stdc++.h>
using namespace std;
constexpr int N=50+5;
int n,k,a[N];
vector<int> ans;
#define print(x) ans.push_back(x)
signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(int i=1,x;i<=n;i++) cin>>x,a[i]=x;
	if(n==2)
	{
		if(a[1]>a[2]&&a[2]+k>a[1]) cout<<"No";
		else if(a[2]+k<=a[1]) cout<<"Yes\n1\n1";
		else cout<<"Yes\n0";
		exit(0);
	}
	ans.reserve(500005);
	for(int i=2;i<n;i++)
	{
		if(a[i]<a[i-1])
		{
			int delta=(a[i-1]-a[i]+k-1)/k;
			for(int t=1;t<=delta;t++) print(i),print(i);
			a[i]+=delta*k,a[i+1]+=delta*k;
		}
	}
	if(a[n-1]>a[n]) print(n-2),print(n-2),print(n-1),a[n-2]+=k,a[n-1]+=k,a[n]+=k,swap(a[n-1],a[n]);
	if(a[n-1]<a[n-2])
	{
		int delta=(a[n-2]-a[n-1]+k-1)/k;
		for(int t=1;t<=delta;t++) print(n-1),print(n-1);
	}
	cout<<"Yes\n";
	cout<<ans.size()<<'\n';
	for(auto x:ans) cout<<x<<' ';
	return 0;
}
```

---

## 作者：happybob (赞：3)

次数限制这么松，该考虑我们随机化算法了！

首先有一个想法是朴素的冒泡排序，操作 $a,b$ 会变为 $b+k,a$，若 $a > b$ 且 $b+k>a$，则操作后并无法改变两数相对顺序。

我们考虑随机化，进行至多 $5 \times 10^5$ 轮，每轮随机一个 $1$ 到 $n$ 的排列 $p_1,p_2,\cdots,p_n$，按照如下操作，直到 $a$ 排好序：

1. 找到最小的 $i$，使得 $p_i \neq n$，$a_{p_i} > a_{p_{i}+1}$ 且 $a_{p_{i}+1}+k \leq a_{p_i}$，对 $p_i$ 进行操作。若不存在这样的 $i$，进行第 $2$ 步。
2. 找到最小的 $i$，使得 $p_i \neq n$ 且 $a_{p_{i}+1} + k \leq a_{p_i}$，对 $p_i$ 操作。若不存在这样的 $i$，进行第 $3$ 步。
3. 找到最小的 $i$，使得 $p_i \neq n$，操作 $p_i$。

实测操作次数不超过 $1.5 \times 10^5$，可以通过。无解当且仅当 $n=2$ 且 $a_2 + k > a_1$。

代码：


```cpp
int cnt = 0;
while (cnt < (int)5e5 && !is_sorted(a.begin() + 1, a.begin() + n + 1))
{
	shuffle(p.begin() + 1, p.begin() + n + 1, rnd);
	bool tag = 0;
	for (int i = 1; i <= n; i++)
	{
		int j = p[i];
		if (j != n && a[j] > a[j + 1] && a[j + 1] + k <= a[j])
		{
			tag = 1;
			pushans(j);
			cnt++;
			break;
		}
	}
	if (!tag)
	{
		for (int i = 1; i <= n; i++)
		{
			int j = p[i];
			if (j != n && a[j + 1] + k <= a[j])
			{
				tag = 1;
				pushans(j);
				cnt++;
				break;
			}
		}
		if (!tag)
		{
			for (int i = 1; i <= n; i++)
			{
				int j = p[i];
				if (j != n)
				{
					tag = 1;
					pushans(j);
					cnt++;
					break;
				}
			}
		}
	}
}
```

---

## 作者：QQzhi (赞：3)

# 逐步详细分析 · 清晰易懂

[题面中文翻译（已提交后台）](https://www.luogu.com.cn/paste/z519muf1)

这道题仅要求正解，要求较低，只需写出一套正确的处理流程即可。

## 审题分析

**性质分析 · 一**

拿到数列的操作方式，我们先来分析一下性质。可知其可拆分为两个行为，后面处理时分别会用到。

```c++
void op(int i){
	hst[top++]=i; // 操作记录数组
	swap(a[i],a[i+1]);
	a[i]+=k;
}
```
先设数列 $A=(a,b,c,d,e,\ldots)$，$n=|A|$。

对数列 $A$ 执行一次操作 $T_i$，可看作为：交换 $A_i,A_{i+1}$ 后，再将 $A_i$ 加上 $k$。

依次进行操作 $T_1,\ldots,T_{n-1}$，分别观察前后变化。

1. 交换后：
   
$$\begin{aligned}
(a,b,c,&d,e,\ldots) 
  \\&\downarrow\\
(b,c,d,&e,\ldots,a)
\end{aligned}$$
2. 加 $k$：

$$\begin{aligned}
(b,c,d,&e,\ldots,a)
  \\&\downarrow\\
(b+k,c+k,d&+k,e+k,\ldots,a)
\end{aligned}$$

我们发现，经过 $n$ 轮操作 $T_1,\ldots,T_{n-1}$ 后，操作后的数列相当于原数列的 $n$ 个元素加上 $k(n-1)$。

故可以定义一个数列操作 $T'_i$，实现任意长度大于 $1$ 的区间的增大，而区间内元素相对大小不变。

**故我们可以通过抬升逆序对其中一方的区间，逐步消除逆序对。**

```c++
void add(int i){
	int len=n-i+1;
	for (int j=0;j<len;j++)
		for (int k=i;k<n;k++)
			hst[top++]=k;
	for (int j=i;j<=n;j++)
		a[j]+=(len-1)*k;
}
```

**性质分析 · 二**

当 $A$ 为一个二元组 $A=(a,b)$时，仅可进行操作 $T_{n-1}$。由前文分析，$A$ 中中元素的相对位置仅在执行奇数次操作 $T$ 后发生改变。

**可知若 $B$ 为逆序对，当且仅当 $A_{n-1}\ge A_n+k$ 时，方可仅通过操作 $T$ 使其单调不减；反之，也由此找到了唯一的无解情况。**（本题数据较小，策略正确的话怎么搞都不会超过最大操作数）

## 解题策略

1. 针对性特判掉长度为 $2$ 的数列
   
   原数列为一个二元组时进行特判，若为逆序对，当 $A_{n-1} \ge A_n+k$ 时，宣布无解，反之进行操作 $T_1$。然后直接快进到输出方案。

3. 消除最后两个元素可能构成的逆序对

  二元组内处理逆序情况限制颇多。既然经过特判，此处可放心引入 $A_{n-2}$。通过进行操作 $T'_{n-1}$，即增大 $A[n-1,n]$，来消除可能的逆序对 $(A_{n-2},A_n)$。

   操作完成后我们不关心 $A_{n-1}$ 或者其他元素的值，执行 $T_{n-2}$ 以交换 $A_{n-2},A_{n-1}$，即可确保数列 $A$ 的后两项有序。

```c++
void judge(){ // 使 (A[n-1],A[n]) 单调不减&决断 
	if (n==2){ // 特判 
		if (a[1]<a[2]+k&&a[1]>a[2])
			cout<<"No",exit(0);
		else{
			if (a[1]>a[2])
				op(1);
			return;
		}
	}
	while (a[n-2]>a[n])
		add(n-1);
	op(n-2);
}
```

5. 尽情消除队列中所有逆序对！

   扫描检查，发现数列中相邻两数为逆序对 $(A_i,A_{i+1})$ 时，通过操作 $T'_{i+1}$，即增大 $A[i+1\ldots n]$，就可以消除该逆序对，且其他数的相对位置不受影响。

```c++
void order(){ // 逐一使 A[i...n-1] 单调不减 
	for (int i=1;i<n-1;i++)
		while (a[i]>a[i+1])
			add(i+1);
}
```

7. 输出方案

## 题解实现

以下供参。

```c++
#include <iostream>
#include <algorithm>
using std::cin;using std::cout;using std::swap;
constexpr int N=1e5+1;
int n,k,a[N],hst[500000],top;
void init(){
	cin>>n>>k;
	for (int i=1;i<=n;i++)
		cin>>a[i];
}
void op(int i){
	hst[top++]=i;
	swap(a[i],a[i+1]);
	a[i]+=k;
}
void add(int i){
	int len=n-i+1;
	for (int j=0;j<len;j++)
		for (int k=i;k<n;k++)
			hst[top++]=k;
	for (int j=i;j<=n;j++)
		a[j]+=(len-1)*k;
}
void judge(){ // 使 (A[n-1],A[n]) 单调不减&决断 
	if (n==2){ // 特判 
		if (a[1]<a[2]+k&&a[1]>a[2])
			cout<<"No",exit(0);
		else{
			if (a[1]>a[2])
				op(1);
			return;
		}
	}
	while (a[n-2]>a[n])
		add(n-1);
	op(n-2);
}
void order(){ // 逐一使 A[i...n-1] 单调不减 
	for (int i=1;i<n-1;i++)
		while (a[i]>a[i+1])
			add(i+1);
}
void solve(){
	judge();
	order();
	cout<<"Yes\n"<<top<<'\n';
	for (int i=0;i<top;i++)
		cout<<hst[i]<<' ';
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	init();
	solve();
}
```

---

## 作者：Msents (赞：3)

神秘题

首先考虑规模较小该怎么做，即 $n=2$。

显然的，若 $a_1>a_2$ 且做了一次操作后仍然是 $a_1>a_2$，此时无解，否则有解。

注意到在一个位置 $i$ 连着操作两次，会导致 $a_i\leftarrow a_i+k，a_{i+1}\leftarrow a_{i+1}+k$，我们称这样的操作叫左脚踩右脚（bushi）。当 $n=2$ 时这样干是没有意义的，但能这启发我们如何构造一个解。

考虑从左到右遍历 $1$ 到 $n-1$ 中的每一个元素。对于当前元素，我们不断执行左脚踩右脚，直到当前元素大于等于上个元素。做完这一步后，序列的 $1$ 到 $n-1$ 都是有序的。

最后一个元素可能不满足条件，这时可以先将这个元素交换到前面去，做足够多次的左脚踩右脚再交换回去，最后在 $n-1$ 这个位置再做几次左脚踩右脚就行了。

容易发现这样总是有解的。

非常好 Adhoc Regular Contest。

赛时码，过程不一样：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MaxN=100000;
int n,k,a[MaxN+1];
vector<int>op;
void Move(int x){
	swap(a[x],a[x+1]);
	a[x]+=k;
	op.push_back(x);
}
void Solve(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	if(n==2){
		if(a[1]>a[2]&&a[2]+k>a[1]){
			cout<<"No";
			return;
		}
		cout<<"Yes\n";
		if(a[1]>a[2])cout<<"1\n1\n";
		else cout<<"0\n";
		return;
	}
	int px=1,py=2;
	bool t=(px>py);
	for(int i=py;i<n;i++)Move(i);
	for(int i=px-1-t;i>=1;i--)Move(i);
	px=1,py=n;
	while(px<n-1){
		Move(px++);
		while(px>2&&a[px-2]>a[px-1]){
			Move(px-1);
			Move(px-1);
		}
	}
	if(a[px]>a[py]){
		Move(px);
		px=n,py=n-1;
		while(a[py]-k<a[px]){
			Move(py-1);
			Move(py-1);
		}
		Move(py);
		px=n-1,py=n;
	}
	while(a[px-1]>a[px]){
		Move(px);
		Move(px);
	}
	for(int i=1;i<=n-1;i++)assert(a[i]<=a[i+1]);
	cout<<"Yes\n"<<op.size()<<'\n';
	for(int v:op)cout<<v<<' ';
}
int main(){
	cin.tie(0)->sync_with_stdio(false);
	Solve();
	return 0;
}
```

---

## 作者：AK_400 (赞：3)

首先掏出一张草稿纸，随便写几种情况，发现可以对 $i$ 进行两次操作后可以将 $a_i,a_{i+1}$ 都加上 $k$。

|$i$|$i+1$|
|:-:|:-:|
|$a_i$|$a_{i+1}$|
|$a_{i+1}+k$|$a_i$|
|$a_i+k$|$a_{i+1}+k$|

于是有了这样一个思路：枚举 $i\in(1,n)$，如果 $a_i<a_{i-1}$，那么反复增加 $a_i,a_{i+1}$，直到 $a_i\ge a_{i-1}$。

看上去很对，但是问题来了，没有办法对 $n$ 操作，如果最后 $a_{n-1}>a_n$，是没有办法解决的。

继续手玩，发现对于长度为 $len$ 的区间 $[l,r]$ 可以通过 $len$ 次 $l,l+1,l+2,\cdots,r-2,r-1$ 操作对区间加 $(len-1)\cdot k$。

一次 $l,l+1,l+2,\cdots,r-2,r-1$ 操作的过程。
|$l$|$l+1$|$\cdots$|$r$|
|:-:|:-:|:-:|:-:|
|$a_l$|$a_{l+1}$|$\cdots$|$a_r$|
|$a_{l+1}+k$|$a_l$|$\cdots$|$a_r$|
|$\vdots$|$\vdots$|$\ddots$|$\vdots$|
|$a_{l+1}+k$|$a_{l+2}+k$|$\cdots$|$a_1$|

 $len$ 次 $l,l+1,l+2,\cdots,r-2,r-1$ 操作的过程。
|$l$|$l+1$|$\cdots$|$r$|
|:-:|:-:|:-:|:-:|
|$a_l$|$a_{l+1}$|$\cdots$|$a_r$|
|$a_{l+1}+k$|$a_{l+2}+k$|$\cdots$|$a_l$|
|$a_{l+2}+2\times k$|$a_{l+3}+2\times k$|$\cdots$|$a_{l+1}+k$|
|$\vdots$|$\vdots$|$\ddots$|$\vdots$|
|$a_{l}+(len-1)\cdot k$|$a_{l+1}+(len-1)\cdot k$|$\cdots$|$a_r+(len-1)\cdot k$|

于是我们可以枚举 $i\in(1,n)$，如果 $a_i<a_{i-1}$，那么反复增加 $a_i,a_{i+1},\cdots,a_n$，直到 $a_i\ge a_{i-1}$，这样就解决了原本 $a_{n-1}\le a_n$，但因为一些操作导致 $a_{n-1}>a_n$ 的问题，因为 $a_{n-1}$ 和 $a_n$ 总是一起增加，所以相对大小关系不变。

如果刚开始就有 $a_{n-1}>a_n$ 怎么办？

显然，如果无法让它俩有序就无解。

当 $n>2$ 时一定有解，反复对 $n-1$ 操作直到 $a_n\ge a_{n-2}$，然后对 $n-2$ 操作，这样就有 $a_n\ge a_{n-1}$。

否则只需要对 $1$ 做一次操作，如果 $a_n\ge a_{n-1}$ 则有解，否则无解。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,a[100];
vector<int>ans;
void add(int pos){//后缀加
    int len=n-pos+1;
    for(int i=1;i<=len;i++){
        for(int j=pos;j<n;j++)ans.push_back(j);
    }
    for(int i=pos;i<=n;i++)a[i]+=k*(len-1);
}
void slv(){
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i];
    if(a[n-1]>a[n]){
        if(n==2){
            swap(a[n],a[n-1]);//对1做一次操作
            a[n-1]+=k;
            if(a[n-1]<=a[n])cout<<"Yes\n1\n1";//不降则有解
            else cout<<"No";//下降则无解
            return;
        }
        while(a[n]<a[n-2]){
            a[n]+=k;
            a[n-1]+=k;
            ans.push_back(n-1),ans.push_back(n-1);
        }
        swap(a[n-1],a[n-2]);
        a[n-2]+=k;
        ans.push_back(n-2);
    }
    for(int i=2;i<n;i++){
        while(a[i]<a[i-1])add(i);//后缀加直到比上一个大
    }
    cout<<"Yes"<<endl;
    cout<<ans.size()<<endl;
    for(int x:ans)cout<<x<<" ";
}
signed main(){
    slv();
    return 0;
}
```

---

## 作者：OneLeft (赞：2)

## 题意

给你整数 $N$、$K$ 和长度为 $N$ 的序列 $A=(A_1,\dots,A_N)$。

请判断是否有可能通过执行下列操作最多 $5\times 10^5$ 次，使 $A$ 不递减，如果可能，请提供一个操作序列。

- 选择一个整数 $i(1\le i<N)$。同时将 $A_i$ 和 $A_{i+1}$ 交换，然后把**交换后**的 $A_i$ 加上 $K$。

## 思路
发现对于一个位置 $i$ 连续操作两次，就相当于把 $A_i$ 和 $A_{i+1}$ 同时加上 $K$，于是我们可以枚举 $1<i<N$，若 $A_{i-1}>A_i$，则给 $A_i$ 和 $A_{i+1}$ 同时加上 $K$ 直到 $A_{i-1}\le A_i$。

但是我们无法通过这样的操作使 $A_N$ 在小于 $A_{N-1}$ 时变大，所以这种情况需要特殊考虑。

我们对 $N-1$ 进行一次操作，于是 $A_{N-1}$ 就变成了 $A'_N+K$，$A_N$ 就变成了 $A'_{N-1}$（$A'$ 是该操作前的序列），然后有如下两种情况：
- 若此时 $A_{N-1}\le A_N$，则立马结束。
- 否则，有 $A_{N-1}>A_N$，也就是 $A'_N+K>A'_{N-1}$，又因为 $A'_{N-1}>A'_N$，所以我们若可以使 $A'_{N-1}$ 加上 $K$，就有 $A'_N+K<A'_{N-1}+K$，可以使 $A_{N-1}\le A_N$，于是我们在对 $N-1$ 操作前，先对 $N-2$ 进行两次操作，大小关系不会改变，也可以使 $A'_{N-1}$ 加上 $K$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=55,M=5e5+5;
int a[N],ans[M];
signed main()
{
    int n,k,tot=0;
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=2;i<n;i++)
    {
        while(a[i-1]>a[i])
        {
            a[i]+=k,a[i+1]+=k;
            ans[++tot]=i,ans[++tot]=i;
        }
    }
    if(n==2&&a[n-1]>a[n]&&a[n]+k>a[n-1])
    {
        cout<<"No\n";
        return 0;
    }
    if(a[n-1]>a[n])
    {
        if(a[n]+k>a[n-1])
        {
            a[n-2]+=k,a[n-1]+=k;
            ans[++tot]=n-2,ans[++tot]=n-2;
        }
        swap(a[n-1],a[n]),a[n-1]+=k,ans[++tot]=n-1;
    }
    while(a[n-2]>a[n-1])
    {
        a[n-1]+=k,a[n]+=k;
        ans[++tot]=n-1,ans[++tot]=n-1;
    }
    cout<<"Yes\n"<<tot<<'\n';
    for(int i=1;i<=tot;i++)cout<<ans[i]<<' ';
    return 0;
}
```

---

## 作者：AmaoFox (赞：2)

一种场上 WA*6 之后想出来的做法。

首先我们可以发现，对 $i$ 操作进行两次可以让 $A_i$ 和 $A_{i+1}$ 分别加上一个 $k$。所以我们可以轻松地通过这种方式把前面 $n-1$ 个数字改成非递减的，因为你可以对于 $i=2,3,\dots,n-1$ 分别进行若干次上面的成对操作。

如果到了最后 $A_{n-1} > A_n$，我们肯定还需要对 $n-1$ 进行额外的操作，从而 $A_{n-1} \leftarrow A_n+k, A_n\leftarrow A_{n-1}$。

但是如果又有 $A_n+k>A_{n-1}$，则不能直接操作。这个时候我们对 $n-2$ 进行多次成对操作，把 $A_{n-1}$ 提升到足够大，然后再进行对 $n-1$ 的一次操作。

如果此时发现 $n=2$ 就可以直接判 `No` 了。否则一直到上述操作进行完以后，输出答案。

``` cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 55;

int a[N];
int n, k;

bool check() {
  for(int i = 1; i < n; i++) {
    if(a[i] > a[i + 1]) {
      return 1;
    }
  }
  return 0;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> k;
  for(int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  vector<int> b;
  for(int i = 2; i < n; i++) {
    while(a[i] < a[i - 1]) {
      b.push_back(i);
      b.push_back(i);
      a[i] += k;
      a[i + 1] += k;
    }
  }
  if(a[n - 1] > a[n]) {
    while(a[n] + k > a[n - 1]) {
      if(n == 2) {
        cout << "No";
        return 0;
      }
      b.push_back(n - 2);
      b.push_back(n - 2);
      a[n - 2] += k;
      a[n - 1] += k;
    }
    b.push_back(n - 1);
    swap(a[n - 1], a[n]);
    a[n - 1] += k;
    while(a[n - 1] < a[n - 2]) {
      b.push_back(n - 1);
      b.push_back(n - 1);
      a[n - 1] += k;
      a[n] += k;
    }
    if(b.size() > 500000) {
      cout << "No";
      return 0;
    }
    cout << "Yes\n" << b.size() << '\n';
    for(int i : b) {
      cout << i << ' ';
    }
  } else {
    if(b.size() > 500000) {
      cout << "No";
      return 0;
    }
    cout << "Yes\n" << b.size() << '\n';
    for(int i : b) {
      cout << i << ' ';
    }
  }
}
```

---

## 作者：Unnamed114514 (赞：2)

前言：本题 AT 原题数据较水，放了部分假做法过。本文的做法是在 AC 的情况下经历多次自我 hack 之后调出来的，把代码放出来也方便大家 hack。

容易发现，对同一个位置操作两次，会导致这个数和后面的那个位置都 $+k$，那么我们可以判掉 $n=2$ 的情况。

对于一段长度 $len\ge 2$ 的序列，我们考虑让序列中的每个元素都加上 $k$，顺序可以改变。因为上面的操作是成对的，所以我们显然要对 $len$ 的奇偶性进行分讨.

- $2\mid len$，直接对 $1,3,5,\cdots,len-1$ 都操作两遍即可。

- $2\nmid len$，对 $1$ 操作一次，然后对 $2,4,6,\cdots,len-1$ 都操作两遍即可。

那么做法就呼之欲出了：钦定 $i(i\le n-2)$ 为后缀最小值，如果 $[i+1,n]$ 的最小值仍然小于 $a_i$，那么让这个后缀整体加 $k$ 即可。

最后剩下两个数，我们并不能保证递增，甚至直接用 $n=2$ 的方法来做会 WA。

注意到此时一定有 $a_{n-1}\ge a_{n-2}$，那么我们只需要保证 $a_n$ 足够大就行了。

注意到操作一次可以把一个数往后移，那么我们把一个足够大的数移动到 $n$ 就行了，容易发现原来的 $n$ 就是此时的 $n-1$。那么我们还不能影响 $n$ 的值。

因为 $n=2$ 已经判掉了，此时 $n\ge 3$，那么我们只需要让 $a_1,a_2$ 同时增加若干次 $k$，然后再把 $a_1$ 移动到 $a_n$ 去即可。容易发现，只需要增加 $O(n)$ 次。

总的操作次数是 $O(n^3)$ 的，带有一些常数。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
int n,k,a[55],ans[500005],tot;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;++i) cin>>a[i];
	if(n==2){
		if(a[1]<=a[2]) cout<<"Yes"<<endl<<0<<endl;
		else if(a[2]+k<=a[1]) cout<<"Yes"<<endl<<1<<endl<<1<<endl;
		else cout<<"No"<<endl;
		return 0;
	}
	for(int i=1;i<=50;++i) ans[++tot]=1,ans[++tot]=1,a[1]+=k,a[2]+=k;
	for(int i=1;i<n;++i) ans[++tot]=i,swap(a[i],a[i+1]),a[i]+=k;
	for(int i=1;i<=n-2;++i) while(1){
		int pos=i+1;
		for(int j=i+1;j<=n;++j) if(a[pos]>a[j]) pos=j;
		if(a[pos]>=a[i]) break; 
		if(n-i&1) ans[++tot]=i+1,swap(a[i+1],a[i+2]),a[i+1]+=k;
		for(int j=n-1;j>i;j-=2) ans[++tot]=j,ans[++tot]=j,a[j]+=k,a[j+1]+=k;
	}
	cout<<"Yes"<<endl;
	cout<<tot<<endl;
	for(int i=1;i<=tot;++i) cout<<ans[i]<<' ';
	cout<<endl;
	return 0;
}
```

---

## 作者：Acoipp (赞：1)

考虑让一个数变得很大，那样的话可以让这个数在交换到最右边的时候把左边的数变成升序。

于是我们先对 $(1,2)$ 执行若干次操作，再对 $(2,3)$ 执行若干次操作，满足 $a_2$ 远远大于其他所有数字。实测这两个操作大概执行 $5 \times 10^3$ 次就够了。

然后再把 $a_2$ 交换到 $a_3$ 的位置，如果此时 $a_3 +k < a_1$，那么再对 $(2,3)$ 执行两次操作，即 $a_2 \gets a_2+2k,a_3 \gets a_3+2k$，这样的话 $a_3$ 迟早会比 $a_1$ 大，$a_4 \dots a_n$ 以此类推即可。

因为 $a_i \le 50$ 并且 $k \le 50$，每个元素最多 $n^2$ 次之后就比上一个元素大，所以执行次数不会超过 $O(n^3)$。

最后 corner case 是 $n=2$，需要特判，即 $a_1 \le a_2$ 一定有解；$a_2+k \le a_1$ 也一定有解，其余情况无解。

---

## 作者：cancan123456 (赞：1)

考虑调整法，找到第一个 $i$ 使得 $A_i>A_{i+1}$，我们需要让 $A_{i+1}$ 增加，如果 $i+2\le n$，那么可以反复操作 $(i+1,i+2)$ 来达成目标。

如果 $i+2>n$，这就说明 $i=n-1$，分类讨论：

1. 如果 $n=2$，只可能操作 $0$ 次或者 $1$ 次，直接特判即可。
2. 如果 $n\ge3$，考虑反复操作 $(n-2,n-1)$ 将 $A_{n-2},A_{n-1}$ 调大，然后操作 $(n-1,n),(n-2,n-1)$ 把 $A_n$ 换过去即可，注意可能需要反复操作 $(n-1,n)$ 将 $A_n$ 调大，直到 $A_n+2k\ge A_{n-2}$。

笑点解析：$n=2$ 特判写反了 WA 了 $8$ 个点。

```cpp
#include <cstdio>
#include <vector>
using namespace std;
int a[55], n, k;
vector < int > ans;
void do_op(int x) {
	ans.push_back(x);
	int pre = a[x + 1] + k, suf = a[x];
	a[x] = pre;
	a[x + 1] = suf;
}
int main() {
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	if (n == 2) {
		if (a[1] <= a[2]) {
			printf("Yes\n0");
		} else if (a[2] + k <= a[1]) {
			printf("Yes\n1\n1");
		} else {
			printf("No");
		}
	} else {
		while (true) {
			bool flag = true;
			bool exit = false;
			for (int i = 1; i < n; i++) {
				if (a[i] > a[i + 1]) {
					if (i + 1 == n) {
						exit = true;
					} else {
						while (a[i] > a[i + 1]) {
							do_op(i + 1);
							do_op(i + 1);
						}
					}
					flag = false;
					break;
				}
			}
			if (exit || flag) {
				break;
			}
		}
		if (a[n - 1] > a[n]) {
			while (true) {
				if (a[n - 2] <= a[n] + 2 * k) {
					break;
				}
				do_op(n - 1);
				do_op(n - 1);
			}
			while (true) {
				if (a[n] + 2 * k <= a[n - 2]) {
					break;
				}
				do_op(n - 2);
				do_op(n - 2);
			}
			do_op(n - 1);
			do_op(n - 2);
		}
		printf("Yes\n%lld\n", ans.size());
		for (int x : ans) {
			printf("%d ", x);
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：block_in_mc (赞：1)

构造题。

很容易注意到对 $p$ 进行两次操作后 $a_p'=a_p+k$，$a_{p+1}'=a_{p+1}+k$。考虑一个基础的操作：给出 $l,r$ 满足 $l<r$，使 $a_l,a_{l+1},\cdots,a_r$ 增加 $k$ 或 $2k$。

* 当区间长度为偶数时，我们依次选择 $p=l,l+2,\cdots$，对 $p$ 执行两次操作，即可令每个数增加 $k$；
* 当区间长度为奇数时，我们先执行 $l,l+1,l+1,l,l+1,l+1$ 六次操作，使得 $a_l,a_{l+1},a_{l+2}$ 均增加 $2k$，再依次选择 $p=l+3,l+5,\cdots$，对 $p$ 执行四次操作，即可令每个数增加 $2k$。

因此，我们可以依次考虑 $i=2,\cdots,n-1$，若 $a_i<a_{i-1}$，对 $[i,n]$ 执行区间加操作，直到 $a_i\ge a_{i-1}$。

唯一的问题是，我们无法对单个数执行区间加操作，因此若 $a_n<a_{n-1}$，无法构造出符合条件的方案。考虑提前进行处理：对 $[n-1,n]$ 执行区间加操作直到 $a_{n-2}\le a_n$，再对 $a_{n-2}$ 进行操作即可使 $a_{n-1}\le a_n$。

需要注意的是，若 $n=2$ 时，无法进行上述操作，可能无解。总操作次数不超过 $2\times n^2 \times a_i=2.5\times10^5$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k, a[60];
vector<int> v;
void upd(int p) {
	swap(a[p], a[p + 1]);
	a[p] += k;
	v.push_back(p);
}
int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	if (n <= 2) {
		if (a[1] <= a[2]) cout << "Yes\n0";
		else if (a[2] + k <= a[1]) cout << "Yes\n1\n1";
		else cout << "No";
		return 0;
	}
	if (a[n - 1] > a[n]) {
		while (a[n] < a[n - 2]) {
			upd(n - 1);
			upd(n - 1);
		}
		upd(n - 2);
	}
	for (int i = 2; i < n; i++) {
		while (a[i] < a[i - 1]) {
			int p = i;
			if ((n - p + 1) % 2 == 1) {
				upd(p), upd(p + 1), upd(p + 1);
				upd(p), upd(p + 1), upd(p + 1);
				p += 3;
				while (p <= n) {
					upd(p), upd(p), upd(p), upd(p);
					p += 2;
				}
			}
			else {
				while (p <= n) {
					upd(p), upd(p);
					p += 2;
				}
			}
		}
	}
	cout << "Yes\n" << v.size() << endl;
	for (int i : v)
		cout << i << " ";
	return 0;
}
```

---

## 作者：a_sad_soul (赞：1)

## A-Add and Swap


### 题意简述 

有一个长度为 $N$ 的序列。

现在有一个操作：

在 $1~n-1$ 中选择一个位置 $i$，让 $i+1$ 加上 $K$，然后交换两个数的位置。

问在 $5\times 10^5$ 内能否让序列单调不减。如果可以，请输出操作序列。


### Solution

我们先从小的地方来讨论一下：

- 当 $n=2$ 时：若 $a_1>a_2$ 且 $a_2+K>a_1$ 无解。原因是重复操作某个位置偶数次，效果是让两个数同时加上偶数除以2个 $K$，且相对大小仍然不变。

- 当 $n=3$ 时：由 $n=2$ 时的结论推广一下，发现可以这样做：让后面的操作200次，前面的操作100次，最后再对中间操作1次，可以保持正确。

- 其它情况：从上述结论出发，我们可以从前往后搞一个长度为3的滑动窗口。先让后加进来的数放到窗口最前面，然后操作一次 $n=3$ 的操作即可。注意到到后面可能有操作完的情况不合法（一个例子就是设 $A_i$ 已经操作结束，那么可能有 $a_1>a_2$ 的情况）。那么我们可以让第 $i$ 次操作乘上 $i$ 的一个偏移量即操作 $200i$ 和 $100i$ 次就可以避开不合法的情况了。不难证明该操作次数一定小于 $5\times 10^5$。

```cpp
//赛时代码可能写的有些冗余，请见谅
#include<bits/stdc++.h>
using namespace std;
vector<int>ans;
int n,k;
int a[100];
void ins(int i){
    ans.push_back(i);
    a[i+1]+=k;swap(a[i],a[i+1]);
}

void PRINT(){
    if(ans.size()>5e5)exit(-1);
    puts("Yes");
    printf("%d\n",ans.size());
    for(int i:ans)printf("%d ",i);
}
bool check(int i){
    if(a[i]<a[i-1]||a[i-1]<a[i-2])return false;
    return true;
}

void change(int i){
    ins(i-1),ins(i-2);
    for(int x=1;x<=(i-2)*200;++x)ins(i-1);
    for(int x=1;x<=(i-2)*150;++x)ins(i-2);
    ins(i-1);
}

void opt(int i){
    change(i);
}
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;++i)cin>>a[i];
    if(n==2){
        if(a[1]>a[2]&&a[2]+k>a[1]){
            puts("No");
            return 0;
        }
        puts("Yes");
        if(a[1]<=a[2])puts("0");
        else cout<<"1\n"<<"1"<<endl;
        return 0;
    }
    for(int i=3;i<=n;++i)opt(i);
    PRINT();
    return 0;
}
```

---

## 作者：Halberd_Cease (赞：1)

对 $pos$ 进行一次操作的本质，其实是将 $a_{pos}$ 和 $a_{pos+1}$ 交换，然后 $a_{pos}\gets a_{pos}+k$。

考虑对同一个位置连续操作两次，实际上就是 $a_{pos}\gets a_{pos}+k$，$a_{pos+1}=a_{pos+1}+k$。

那么我们可以想到一个策略，即顺序遍历 $i\in[2,n-1]$，以两次为单位重复操作 $i$，直到 $a_i>a_{i-1}$。

可以证明的是，这样的操作可以在最多 $30000$ 步之内，将序列的前 $n-1$ 项变不降。

此时如果 $a_n\ge a_{n-1}$ 直接就结束了，后面考虑 $a_n\le a_{n-1}$。

考虑最后一项和倒数第二项的关系，显然只能通过交换一次达成目的，因为交换两次及以上不会改变两者的差。

但是考虑一种情况，即 $a_{n-1}-a_n<k$，此时，进行一次操作无法使 $a_{n-1}\le a_n$。

问题关键点在于 $a_{n-1}-a_n$ 太小，因此考虑操作让这个值增大。

其实上面对同一个位置操作两次这个过程，我们发现操作次数只多不少是符合条件的，即枚举对哪一位操作时，如果当前已经符合条件了，那么再进行操作一定是合法的（前提是不超次数限制）。我们考虑对 $n-2$ 这个位置进行极多次操作，将 $a_{n-2}$ 和 $a_{n-1}$ 都变成远大于这个序列中所有数的值，不改变其相对大小。

然后我们就会发现此时 $a_{n-1}-a_n$ 一定大于 $k$，执行一次操作就能使 $a_n\ge a_{n-1}$。

然后我们发现，此时序列前 $n-2$ 项是单调不减的，后两项是单调不减的，直接操作 $n-1$ 位置，直到整个序列符合条件即可。

考虑 coner case，当 $n=2$ 时无法通过操作 $n-2$，因此如果 $a_1-a_2<k$ 就无解。

要注意操作极大次时不要爆 $500000$ 次。

[submission](https://atcoder.jp/contests/arc187/submissions/59909772)

---

## 作者：_determination_ (赞：1)

强烈谴责 @CuteChat 说 $n>2$ 的时候也有无解情况来释放了十分钟烟雾弹！！！

不算太难，建议评绿。

注意到你对着一个位置连续交换两次就能让相邻的位置同时加 $k$。那么你就可以用这个性质把前 $n-2$ 个数排序。然后最后两个数有序之后对着 $n-1$ 重复此操作即可。

对最后两个数排序的时候如果已经有序不管，否则交换。当然交换之后有可能还是无序，我们就对着 $n-2$ 进行操作使得交换之后 $a_{n-1}<a_{n}$ 即可。当然，记得特判 $n=2$ 的情况。

强烈谴责出题人，$5\times 10^5$ 的操作次数意义不明。

https://atcoder.jp/contests/arc187/submissions/59909694

---

