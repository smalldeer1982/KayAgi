# Survival of the Weakest (easy version)

## 题目描述

This is the easy version of the problem. It differs from the hard one only in constraints on $ n $ . You can make hacks only if you lock both versions.

Let $ a_1, a_2, \ldots, a_n $ be an array of non-negative integers. Let $ F(a_1, a_2, \ldots, a_n) $ be the sorted in the non-decreasing order array of $ n - 1 $ smallest numbers of the form $ a_i + a_j $ , where $ 1 \le i < j \le n $ . In other words, $ F(a_1, a_2, \ldots, a_n) $ is the sorted in the non-decreasing order array of $ n - 1 $ smallest sums of all possible pairs of elements of the array $ a_1, a_2, \ldots, a_n $ . For example, $ F(1, 2, 5, 7) = [1 + 2, 1 + 5, 2 + 5] = [3, 6, 7] $ .

You are given an array of non-negative integers $ a_1, a_2, \ldots, a_n $ . Determine the single element of the array $ \underbrace{F(F(F\ldots F}_{n-1}(a_1, a_2, \ldots, a_n)\ldots)) $ . Since the answer can be quite large, output it modulo $ 10^9+7 $ .

## 说明/提示

In the first test, the array is transformed as follows: $ [1, 2, 4, 5, 6] \to [3, 5, 6, 6] \to [8, 9, 9] \to [17, 17] \to [34] $ . The only element of the final array is $ 34 $ .

In the second test, $ F(a_1, a_2, \ldots, a_n) $ is $ [2, 2, 2, 8, 8, 8, 8, 8] $ . This array is made up of $ 3 $ numbers of the form $ 1 + 1 $ and $ 5 $ numbers of the form $ 1 + 7 $ .

In the fourth test, the array is transformed as follows: $ [10^9, 10^9, 777] \to [10^9+777, 10^9+777] \to [2 \cdot 10^9 + 1554] $ . $ 2 \cdot 10^9 + 1554 $ modulo $ 10^9+7 $ equals $ 1540 $ .

## 样例 #1

### 输入

```
5
1 2 4 5 6```

### 输出

```
34```

## 样例 #2

### 输入

```
9
1 1 1 7 7 7 9 9 9```

### 输出

```
256```

## 样例 #3

### 输入

```
7
1 7 9 2 0 0 9```

### 输出

```
20```

## 样例 #4

### 输入

```
3
1000000000 1000000000 777```

### 输出

```
1540```

# 题解

## 作者：falling_cloud (赞：1)

提供一种只能过 easy version 的解法。

对于 $n  \leq 3000$，考虑暴力合并 $F$ 数组，每次保留前 $k$ 小的和值 $a_i+a_j$，可以使用堆贪心：对于一个有序数组 $a$，$a_i+a_j\leq a_i+a_{j+1}$，用堆维护 $a_i+a_j$ 的最小值，开始时将 $n$ 个二元组 $(i,1)$ 放入堆中，每次拿出最小值之后将二元组 $(i,j)$ 改为 $(i,j+1)$ 后再放去，这样可以在 $(n+k)\log k$ 的时间复杂度下完成选择前 $k$ 大的和值这一操作。

但是还有一个问题：$F$ 数组中的数字增长速度太快了。使用高精度的话时间复杂度又将变得不可接受。而如果相对大小不改变，选择的数也不会被改变，所以我们考虑再每一次迭代后，将 $F$ 中的每个元素都减去 $F$ 数组中的最小值 $F_1$，而 $F_1$ 在对最终答案产生贡献之前，还会被合并若干轮，每一轮的 $F_1$ 都将会被倍增（因为无论怎么合并元素，其中都是默认含有 $F_1$ 的），也就是说，对于第 $i$ 轮合并后被减掉的 $F_1$，还会被合并 $n-i-1$ 轮，所以其对答案的贡献就是 $F_1\times 2^{n-i-1}$，于是只要在每轮迭代完成后将所有数减去 $F_1$ 并累加到贡献上就可以了，时间复杂度 $\Theta(n^2\log n)$。

接下来证明为什么这样做之后数列中的元素就不会超过 `int` 范围：对于一个长度为 $k$ 的数组 $F$，产生的后续数组 $F'$ 中最小的元素显然是 $F_1+F_2$，而最大的元素 $F'_{k-1} \leq F_1+F_{k-1}$。所以在减去最小值之后，数组的最大值 $F'_{k-1}\leq(F_1+F_{k-1})-(F_1+F_2) = F_{k-1}-F_2 \leq F_k$，也就是 $F$ 数组的最大值在每次迭代之后单调不升，因此保证了无论何时 $F$ 数组中的所有的元素不会超过 $10^9$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3000 + 5;
const int M = 1e9 + 7;
int a[N],b[N],pw[N];
struct pi
{
	int x,y;
	bool operator > (const pi &ti) const
	{
		return a[x]+a[y]>a[ti.x]+a[ti.y];
	}
}t;
priority_queue <pi,vector<pi>,greater<pi> > q; 
void solve()
{
	int n,m,i,j,l,r,x,y,tag=0;
	cin>>n;	pw[0]=1;
	for(i=1;i<=n;i++)	pw[i]=pw[i-1]*2%M;
	for(i=1;i<=n;i++)	cin>>a[i];
	sort(a+1,a+n+1);
	for(i=n;i>=2;i--)
	{
		while(!q.empty())	q.pop();
		for(j=1;j<i;j++)
			q.push((pi){j,j+1});
		for(j=1;j<i;j++)
		{
			t=q.top();	q.pop();
			b[j]=a[t.x]+a[t.y];
			q.push((pi){t.x,t.y+1});
		}
		tag=(tag+b[1]*pw[i-2])%M;
		for(j=i-1;j>=1;j--)
			b[j]-=b[1];
		for(j=1;j<i;j++)
			a[j]=b[j]%M;
	}
	cout<<(a[1]+tag)%M;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);
	int Ti;
//	for(cin>>Ti;Ti;Ti--)
		solve();	
	return 0;
}

```

---

## 作者：Xy_top (赞：1)

先来考虑只做一次该怎么办，容易想到堆贪心。

由于一个对子 $(x,y)$ 与 $(y,x)$ 重复，所以我们规定 $x<y$。

首先把 $a$ 数组排序，然后把 $a_i+a_{i+1}$ 放到优先队列中，每次取出和最小的那个，设其为 $a_x+a_y$，将 $a_x+a_{y+1}$ 放进优先队列中即可，时间复杂度为 $O(n\log n)$。

现在需要做 $n$ 次，由于时限 $3s$ 加上 $n$ 是不断变小的该算法常数较小，所以我们考虑做 $n$ 次。

然后就完事了？交上去发现错了。原来是因为 $a$ 中元素增长速率极快导致爆 LL 了。

这时需要应用一个新的套路，把 $a$ 中的所有元素减去 $a$ 中的最小元素 $a_1$，最后再把 $a_1$ 在最终答案中出现的次数加上去。

这样做一定是可行的，不妨来证明一下，$k$ 轮后的最小值 $a_{k,1}$ 一定等于 $a_{k-1,1}+a_{k-1,2}$，$k$ 轮后的最大值 $a_{k,n}$ 减去了 $a_{k-1,1}+a_{k-1,2}$ 变为 $a_{k,n}-a_{k-1,1}-a_{k-1,2}$。

发现仍不好得出结论，此时考虑将 $a_{k,n}$ 变下形，有个结论显然：$a_{k,n}\leq a_{k-1,1}+a_{k-1,n}$，这是因为比不等式右边小的就有 $a_{k-1,1}+a_{k-1,x}(1\leq x<n)$，共 $n-1$ 个，所以它最小也得是是第 $n$ 小。

为什么选择 $a_{k-1,1}+a_{k-1,n}$，因为可以消掉了，代回 $a_{k,n}-a_{k-1,1}-a_{k-1,2}$ 得 $a_{k-1,1}+a_{k-1,n}-a_{k-1,1}-a_{k-1,2}=a_{k-1,n}-a_{k-1,2}$，而这个东西是 $<a_{k-1,n}$ 的。

这时被减数增大了（根据上文），减数没变，所以差变大了，于是可以得出 $a_{k,n}<a_{k-1,n}$，这个方法正确。

还有一个问题，$a_{k,1}$ 对答案的贡献如何？我们是将每个数都减去了 $a_{k,1}$，所以每个数中都包含至少一个 $a_{k,1}$，不妨看下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/71vb0ugp.png)

所以我们就能够写出代码了：

```cpp
#include<queue>
#include<iostream>
#include<algorithm>
using namespace std;
int n,tmp;
int a[3005],b[3005],pre[3005];
const int mod=1000000007;
struct Pair{
	int x,y;
	bool operator>(const Pair &s) const{return a[x]+a[y]>a[s.x]+a[s.y];}
};
priority_queue<Pair,vector<Pair>,greater<Pair>>q;
signed main(){
	pre[0]=1;
	for(int i=1;i<=3000;i++)pre[i]=pre[i-1]*2%mod;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=n;i>=2;i--){
		while(!q.empty())q.pop();
		for(int j=1;j<i;j++)q.push({j,j+1});
		for(int j=1;j<i;j++){
			Pair t=q.top();
			q.pop();
			b[j]=a[t.x]+a[t.y];
			q.push({t.x,t.y+1});
		}
		tmp=(tmp+(long long)(b[1])*pre[i-2])%mod;
		for(int j=i-1;j>=1;j--)b[j]-=b[1];
		for(int j=1;j<i;j++)a[j]=b[j];
	}
	cout<<(a[1]+tmp)%mod;
	return 0;
}
```


---

## 作者：happybob (赞：0)

先对 $a$ 排序。

直接做 $n-1$ 次，每次用堆做到 $O(n \log n)$ 是可以通过 easy version 的，但是问题在于要求答案对 $10^9+7$ 取模，但操作过程中并不取模，直接做肯定不对。

考虑一个特殊情况，当 $a_1 =0 $ 时，进行一次操作后，数的值域不会变大，因为可以选 $(1,2),(1,3),\cdots,(1,n)$。

直接在每次操作的时候令 $a_i \leftarrow a_i - a_1(2 \leq i \leq n)$，然后令 $a_1=0$，就可以在每次操作的时候保证值域在范围内了。

剩下的就是考虑每次 $a_1$ 的贡献。不难得到 $a_1$ 的贡献倍数是一个 $2$ 的幂次，直接累加答案即可。时间复杂度 $O(n^2 \log n)$。

---

## 作者：daniEl_lElE (赞：0)

显然高精度又慢又难写，考虑一些性质。

容易发现 $a_i+a_j$ 的第 $n-1$ 小者一定不超过 $a_1+a_n$。所以说每次操作完最大值和最小值的差一定不超过 $a_n-a_2$。归纳可得在操作中最大值和最小值的差均不超过原来的 $a_n-a_2$。于是我们可以把每个数记为 $a_1+b_i$。

接下来问题转化成了一个经典题，就是找 $a_i+a_j$ 的第 $k$ 小，显然我们可以用堆维护，复杂度 $O(n+k\log n)$。

总复杂度 $O(n^2\log n)$，可以通过。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
const int mod=1e9+7;
signed main(){
	int n; cin>>n; int a[n+1],minv=1e18;
	for(int i=1;i<=n;i++) cin>>a[i],minv=min(minv,a[i]);
	for(int i=1;i<=n;i++) a[i]-=minv;
	sort(a+1,a+n+1);
	for(int i=n;i>=2;i--){
		priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>> pq;
		for(int j=1;j<i;j++) pq.push(make_pair(a[j]+a[j+1],make_pair(j,j+1)));
		int b[n+1];
		for(int j=1;j<i;j++){
			auto f=pq.top(); pq.pop();
			b[j]=f.first;
			if(f.second.second!=i){
				pq.push(make_pair(a[f.second.first]+a[f.second.second+1],make_pair(f.second.first,f.second.second+1)));
			}
		}
		(minv*=2)%=mod;
		(minv+=b[1])%=mod;
		for(int j=1;j<i;j++){
			a[j]=b[j]-b[1];
		}
	}
	cout<<minv<<" ";
	return 0;
}

```

---

## 作者：hsaht2426 (赞：0)

首先考虑**简单情形**，考虑只做一次时的情况。

这个问题很典，经典贪心，不在此处解释。

那你暴力合并 $O(n^2 \log n)$ 即可。

但是注意到取模，分析后发现值域似乎会很大，暴力合并结合高精时间无法接受。

你考虑**简化一下集合**，考虑我们只关心 $a_i+a_j$ 的大小关系。

回顾一下问题，我们尝试分析值域的变化，取一点**特殊位置**尝试**递推分析**，我们发现最小值会变成原来的两倍，所以值域每次至少会变成原来的两倍。

考虑如何处理，首先考虑**最小值的简单情形**，不难考虑为 $0$ 的情况，此时不会对值域产生增大影响。

对于其他情况，我们可以直接将所有数减去 $a_1$ ，直接提前计算 $a_1$ 的贡献。

于是暴力 $O(n^2 \log n)$ 递推即可。

---

