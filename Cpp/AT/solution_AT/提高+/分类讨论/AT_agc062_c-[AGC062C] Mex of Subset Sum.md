# [AGC062C] Mex of Subset Sum

## 题目描述

给定一个长度为 $N$ 的整数序列 $A=(A_1,A_2,\dots,A_N)$。

请按从小到大的顺序，找出满足以下条件的 $K$ 个正整数 $X$：

- 存在 $A$ 的一个非空（不要求连续）子序列，其元素之和等于 $X$ 的情况**不存在**。

## 说明/提示

### 限制条件

- $1\leq N\leq 60$
- $1\leq K\leq 1000$
- $1\leq A_i\leq 10^{15}$
- 输入的所有值均为整数

### 样例解释 1

$A$ 的所有子序列包括 $(1),(2),(1,2),(5),(1,5),(2,5),(1,2,5)$，它们的元素和分别为 $1,2,3,5,6,7,8$。因此，对于 $X=1,2,3,5,6,7,8$，存在元素和为 $X$ 的 $A$ 的子序列。另一方面，对于 $X=4,9,10$，不存在元素和为 $X$ 的 $A$ 的子序列。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 3
1 2 5```

### 输出

```
4 9 10```

## 样例 #2

### 输入

```
20 10
324 60 1 15 60 15 1 60 319 1 327 1 2 60 2 345 1 2 2 15```

### 输出

```
14 29 44 59 74 89 104 119 134 149```

# 题解

## 作者：Smallbasic (赞：5)

首先，让 $A_i$ 从小到大排序。设 $S_i$ 为 $A$ 的前缀和，我们定义 $X_i$ 为所有小于 $S_i$ 切不能被前 $i$ 个数表示的正整数集合。由于值域很大， $|X_i|$ 也会很大，但我们只用求前 $K$ 个不能被表示的数，所以 $X_i$ 中有用的数的级别很小（实际上不超过 $Ki$，之后的解题过程会证明）。

我们思考加入一个 $A_i$ 之后如何维护 $X_i$，不难发现维护的方法与 $A_i$ 和 $S_{i-1}$ 的相对大小有关。考虑分类讨论：

## Case1 : $S_{i-1}<A_i$

此时对于正整数 $x\in X_{i}$  成立当且仅当满足如下条件中任意一个：

1. $x\in X_{i-1}$

2. $x\in(S_{i-1},A_i)$

3. $x-A_i \in X_{i-1}$

容易发现，前两类的 $x$ 一定小于 $A_i$。由于我们将 $A$ 升序排列，后面的数不论怎么加进来都不能表示出它们。因此如果加前两类的时候个数已经超过 $K$ 就可以直接输出答案。

否则考察加入完三类数之后 $X_i$ 相较于 $X_{i-1}$ 增加了多少。考虑前两类数的个数是 $|X_{i-1}|+A_i-S_{i-1}-1<K$，而第三类的数的个数为 $|X_{i-1}|$，所以增加的总个数为 $|X_{i-1}|+A_i-S_{i-1}-1+|X_{i-1}|-|X_{i-1}|=|X_{i-1}|+A_{i}-S_{i-1}-1<K$，故 $|X_i|<|X_{i-1}|+K$,即每加入一个 $A_i$ 只会增加小于 $K$ 个数。

## Case2 : $A_i\le S_{i-1}$

此时对于正整数 $x\in X_{i}$  成立当且仅当满足如下条件中任意一个：

1. $x\in X_{i-1}\cup [1,A_i)$

2. $x\in X_{i-1}\cup (A_i,S_{i-1}]$  且 $x-A_i\in X_{i-1}$

3. $x\in (S_{i-1},S_i)$ 且  $x-A_i\in X_{i-1}$

同样的，第一类的 $x$ 之后不论怎么加数都一定在集合中。如果第一类的个数大于等于 $K$，那么就可以直接输出答案。

否则考虑加入第二类和第三类，容易发现它们的个数不超过 $|X_{i-1}|$，因此仍有 $|X_i|<|X_{i-1}|+K$

综上，每加入一个数，要么可以直接输出答案，要么使得集合的大小增加不超过 $K$。用 `std::set` 维护的话总复杂度为 $\Theta\left(\sum\limits_{i=1}^n iK\log iK\right)=\Theta(nK\log (nK))$

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 65;

int n, k;
ll a[N];
set<ll> res, tmp;

inline void print() {
	int cnt = 0;
	for (ll i : res) {
		printf("%lld ", i);
		if (++cnt == k) exit(0);
	}
}

int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	sort(a + 1, a + n + 1); ll sum = 0;
	for (int i = 1; i <= n; ++i) {
		if (a[i] > sum) {
			tmp = res;
			for (ll j = sum + 1; j < a[i]; ++j) {
				res.insert(j);
				if (res.size() >= k) print(); 
			}
			for (ll j : tmp) res.insert(j + a[i]);
		} else {
			tmp.clear();
			for (ll j : res)
				if (j < a[i]) tmp.insert(j);
			if (tmp.size() >= k) { res = tmp; print(); }
			for (ll j : res) {
				if (j > a[i] && res.find(j - a[i]) != res.end()) tmp.insert(j);
				if (j + a[i] > sum) tmp.insert(j + a[i]);
			}
			res = tmp;
		}
		sum += a[i];
	}
	for (ll i = sum + 1; res.size() < k; ++i) res.insert(i);
	print(); return 0;
}
```


---

## 作者：0xyz (赞：1)

## 一、题目大意

给定 $N$ 个正整数组成的集合 $(A_1,A_2,…,A_N)$，求不能表示为它的子集和的前 $K$ 小正整数。

- $N\le 60,K\le 1000,A_i\le 10^{15}$。

## 二、做法

神仙思维题。甚至有 $\color{black}{\text{L}}\color{red}{\text{GM}}$ 做出来了但是不会证明时间复杂度。

本篇题给出一个严谨的证明（当然证明来自官方题解）。

首先由于 $N\le 60$，所以搜索显然是不可能的。将所有的 $A_i$ 按照从小到大排序，令 $S_i=\sum\limits_{j=1}\limits^{i}A_j$，集合 $EX_i$ 表示 $1,2,…,S_i$ 中不能表示为集合 $(A_1,A_2,…,A_i)$ 的子集和的所有正整数。方便起见，令 $EX_0$ 为空集。然后我们的答案就是 $EX_n$ 的前 $K$ 个数。

然后尝试使用 $EX_{i-1}$ 推出 $EX_i$。容易发现 $|EX_{i-1}|\to|EX_i|$ 是指数级增长的。但是我们可以通过恰当的处理，使得 $|EX_i|\le Ki$。

------------

我们针对 $A_i$ 与 $S_{i-1}$ 的关系进行讨论。

### $1.A_i>S_{i-1}$

那么其实有一些数已经确定是在 $EX_i$ 里了。

- $EX_{i-1}$ 里的所有数。
- $S_{i-1}+1,S_{i-1}+2,…,A_i-1$。

并且容易知道 $1,2,…,A_i$ 中只有以上这 $2$ 种数不能表示为集合 $(A_1,A_2,…,A_i)$ 的子集和，并且由于 $A_i$ 单调不减，所以它们也不可能表示为 $(A_1,A_2,…,A_n)$ 的子集和。所以如果这些数的个数大于等于 $K$，那么直接输出最小的 $K$ 个，结束程序（※）。

然后如果这些数的个数小于 $K$ 个，我们再考虑 $A_i+1,A_i+2,…,S_i$ 里的哪一些数属于 $EX_i$。很明显 $\forall j\in(A_i,S_i],j\in EX_i$ 当且仅当 $j-A_i\in EX_{i-1}$。一共 $|EX_{i-1}|$ 个，直接加进去即可。

所以我们有 $|EX_i|<K+|EX_{i-1}|$。

### $2.A_i\le S_{i-1}$

那么其实有一些数已经确定是在 $EX_i$ 里了。

- $EX_{i-1}$ 里小于 $A_i$ 的所有数。

并且容易知道 $1,2,…,A_i$ 中只有以上这种数不能表示为集合 $(A_1,A_2,…,A_i)$ 的子集和，并且由于 $A_i$ 单调不减，所以它们也不可能表示为 $(A_1,A_2,…,A_n)$ 的子集和。所以如果这些数的个数大于等于 $K$，那么直接输出最小的 $K$ 个，结束程序（※）。

然后如果这些数的个数小于 $K$ 个，我们再考虑 $A_i+1,A_i+2,…,S_{i-1}$ 里的哪一些数属于 $EX_i$。很明显 $\forall j\in(A_i,S_{i-1}],j\in EX_i$ 当且仅当 $j-A_i\in EX_{i-1}\text{且}j\in EX_{i-1}$。最后就是 $S_{i-1}+1,S_{i-1}+2,…,S_i$ 里的哪一些数属于 $EX_i$。很明显 $\forall j\in(S_{i-1},S_i],j\in EX_i$ 当且仅当 $j-A_i\in EX_{i-1}$。

注意到后 $2$ 类的一个共同要求是 $j-A_i\in EX_{i-1}$，所以这 $2$ 类中不同 $j$ 的个数不超过 $|EX_{i-1}|$。直接加进去即可。

所以我们有 $|EX_i|<K+|EX_{i-1}|$。

------------

综上所述，我们证明了只要我们在（※）时结束程序，那么一定有 $|EX_i|<|EX_{i-1}|+K$，又因为 $|EX_0|=0$，所以有 $|EX_i|\le Ki$，所以 $|EX_i|$ 不会超过 $KN$ 个数。

所以我们枚举 $i$，按照以上的方法分类讨论即可。用 `set` 维护 $EX_i$，那么总的时间复杂度是 $O(N^2K\log (NK))$，可以通过此题。

## 三、代码

细节比较多。

1. 用 $u$ 表示 $EX_{i-1}$，用 $v$ 表示 $EX_i$。
2. 用 `out` 控制输出个数。
3. 在中间枚举 $j$ 时，注意有时候在正整数域上直接遍历再判断可能会超时，所以如果这一类的限制与 $EX_{i-1}$ 有关，那么要枚举 $EX_{i-1}$ 的元素后进行处理。
4. 拷贝 `set` 时记得清空。
3. 注意最后如果 $EX_n$ 的大小不够 $K$，要在 $S_n$ 往后遍历。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,k,a[70],s[70],cnt=0;
set<ll>u,v;
inline void out(ll x){
	cout<<x<<' ';
	if(++cnt==k)exit(0);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>k;
	for(ll i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	for(ll i=1;i<=n;i++){
		s[i]=s[i-1]+a[i];
		if(a[i]>s[i-1]){
		for(auto j:u)v.insert(j);
			for(ll j=s[i-1]+1;j<a[i];j++){
				v.insert(j);
				if(v.size()>=k)for(auto z:v)out(z);
            }
			for(auto j:u)v.insert(j+a[i]);
			u.clear();
			for(auto j:v)u.insert(j);
			v.clear();
		}else{
			for(auto j:u)if(j<a[i])v.insert(j);
			if(v.size()>=k)for(auto z:v)out(z);
			for(auto j:u)if(j>a[i]&&u.count(j-a[i]))v.insert(j);
			for(auto j:u)if(j+a[i]>s[i-1])v.insert(j+a[i]);
			u.clear();
			for(auto j:v)u.insert(j);
			v.clear();
		}
	}
	for(auto z:u)out(z);
	for(ll i=1;;i++)out(s[n]+i);
	return 0;
}
```


---

## 作者：AC_love (赞：0)

我们不妨直接维护一个集合 $P$ 存储哪些数不能被表示出来。这样的数有很多，但考虑到本题 $K$ 并不大，所以实际维护的数还是比较少的。

首先把 $A$ 从小到大排序，对排序后的 $A$ 求一个前缀和 $S$。

假设当前维护了前 $i$ 位不能表示的数，我们考虑如何维护 $i + 1$ 位。

不妨分类讨论：可以分出两种情况，分别是 $A_{i + 1} \ge S_i$ 和 $A_{i + 1} < S_i$

当 $A_{i + 1} \ge S_i$ 时，$x \in P_{i + 1}$ 当且仅当：

- $x\in P_i$
- $S_i < x < A_{i + 1}$
- $x - A_{i + 1} \in P_i$

对于第一项和第三项而言，只会让 $P_i$ 的大小翻倍。

第二项可能有很多，但我们发现：当第一项和第二项的个数加起来大于等于 $K$ 时，我们就可以直接输出了。所以如果我们没有直接输出的话，实际上第二项也不会有很多。

接下来考虑 $A_{i + 1} < S_i$，此时 $x \in P_{i + 1}$ 当且仅当：

- $x < A_{i + 1}$ 且 $x \in P_i$
- $x \in P_i$ 且 $x - A_{i + 1} \in P_i$
- $x > S_i$ 且 $x - A_{i + 1} \in P_i$

如果第一种可能的 $x$ 大于等于 $K$，我们也可以直接输出。

第一种和第二种加起来最大也不会超过 $P_i$，而第三种同样不会超过 $P_i$，所以维护的数最多只会翻倍，不会变得太多。

[code](https://atcoder.jp/contests/agc062/submissions/59545712)

---

