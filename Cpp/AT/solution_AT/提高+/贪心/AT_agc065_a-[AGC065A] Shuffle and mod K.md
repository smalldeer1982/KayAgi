# [AGC065A] Shuffle and mod K

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc065/tasks/agc065_a

長さ $ N $ の整数列 $ A=(A_1,A_2,\dots,A_N) $ が与えられます。

あなたは $ A $ を自由に並び替えることが出来ます。並び替えた後の $ \sum_{i=1}^{N-1}\ ((A_{i+1}\ -\ A_i)\ \bmod\ K) $ としてあり得る最大値を求めてください。

ここで、$ x\ \bmod\ K $ とは $ 0\ \le\ y\ <\ K $ かつ $ x\ -\ y $ が $ K $ の倍数になる整数 $ y $ のことを指します。例えば、$ -3\ \bmod\ 8\ =\ 5,9\ \bmod\ 6\ =\ 3 $ となります。

## 说明/提示

### 制約

- $ 2\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ K\ \le\ 10^9 $
- $ 0\ \le\ A_i\ <\ K $
 
### Sample Explanation 1

最適な例として、$ A\ =\ (2,1,0) $ と並び替えると $ (1\ -\ 2)\ \bmod\ 4\ +\ (0\ -\ 1)\ \bmod\ 4\ =\ 3\ +\ 3\ =\ 6 $ が達成できます。

## 样例 #1

### 输入

```
3 4
0 1 2```

### 输出

```
6```

## 样例 #2

### 输入

```
7 123
11 34 56 0 32 100 78```

### 输出

```
638```

# 题解

## 作者：_sunkuangzheng_ (赞：6)

注意到 $0 \le a_{i+1} - a_i < k$，那么原式即 $a_n-a_1+pk$，其中 $p$ 是满足 $a_i > a_{i+1}(1 \le i \le n-1)$ 的下标 $i$ 数量。显然若 $c$ 是 $p$ 能取到的最大值，只有 $p \ge c-1$ 时才能产生最优解。

简单的想法是，直接降序排序，看起来就可以最大化 $p$ 的值，但是当数组中有重复元素的时候就会假。设出现次数最多的元素出现了 $m$ 次，那么把所有元素的每一次出现放进不同的组里，每一组里降序排序，$c = n-m$。

我们先考虑 $p=c$ 时能得到的最大答案，此时只需要最大化 $a_n - a_1$。但是这时这个值是唯一确定的，即出现了 $m$ 次里的数字的最小值 $x_1$，减去出现了 $m$ 次里的数字的最大值 $x_2$。考虑怎么构造：大于 $x_2$ 的元素不放在第一组，小于 $x_1$ 的元素不放在最后一组。此时答案即是 $ck + x_1 - x_2$。

考虑 $p = c - 1$，此时相当于分成 $m+1$ 组。对于出现次数不到 $m$ 次的，全都扔进中间，否则我们决定到底不放进第一组还是最后一组。我们可以定一个阈值 $x$，大于 $x$ 的不放在第一组，小于等于 $x$ 的不放在最后一组。那么，此时的答案是 出现 $m$ 次且大于 $x$ 的最小值 减去 出现 $m$ 次且小于等于 $x$ 的最大值。排序出现 $m$ 次里的数字，枚举相邻项的差即可。设差是 $d$，答案是 $d + (c-1)k$。

取 $\max$ 即可，时间复杂度 $\mathcal O(n \log n)$。

---

## 作者：Acoipp (赞：0)

## 分析

容易发现相邻的 $a_i,a_{i+1}$ 的贡献要么是 $a_{i+1}-a_i$ 要么是 $a_{i+1}-a_i+k$，取前者的时候是 $a_{i+1}\ge a_i$，取后者是 $a_{i+1}<a_i$。

先不考虑 $k$ 的贡献，那么整个序列的贡献就是 $a_n-a_1$，我们发现 $a_n-a_1<k$，因此我们尽可能让 $k$ 的贡献大。

我们可以根据 $a$ 中出现次数最大的数来得到 $k$ 的贡献，设其出现 $c$ 次，那么 $k$ 就可以造成 $0 \sim (n-c)k$ 的贡献，最大值就是把 $a$ 分成 $c$ 个严格下降子序列即可。

但是 $-k < a_n-a_1<k$，所以我们需要分别讨论 $k$ 造成 $(n-c)k$ 的贡献还是 $(n-c-1)k$ 的贡献，即把 $a$ 分成 $c$ 或者 $c-1$ 个严格下降子序列的情况都需要考虑，这里只介绍 $c$ 的情况，$c-1$ 的情况是一样的。

首先 $c=1$ 的时候需要特判一下，有的写法不用。

然后枚举 $a_1$，然后贪心的选择最大的 $a_n$ 即可。

具体来说，如果 $x \in [1,a_1]$ 并且 $x \in [a_n,k-1]$ 那么 $x$ 的出现次数必须小于等于 $c$，如果 $x \in [1,a_1],x \not\in [a_n,k-1]$，那么 $x$ 的出现次数必须小于等于 $c-1$，如果 $x \not\in [1,a_1],x \in [a_n,k-1]$，那么 $x$ 的出现次数必须小于等于 $c-1$，否则 $x$ 的出现次数一定小于等于 $c-2$。

具体的实现略，找到 $a_1,a_n$ 可以用 `set` 等数据结构（或者仅仅是一个变量）维护，时间复杂度 $O(n \log n)$，瓶颈在于排序。

## 代码

代码如下，仅供参考：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 500005 
using namespace std;
struct node{ll x,y;}p[N];
ll n,k,a[N],i,j,b,ans1=LLONG_MIN,ans2=LLONG_MIN,tot,func,l=LLONG_MAX,r=LLONG_MIN,sam,pos;
set<ll> op;
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>k;
	for(i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	p[0].x=-1;
	for(i=1;i<=n;i++){
		if(p[tot].x==a[i]) p[tot].y++;
		else p[++tot] = (node){a[i],1};
	}
	for(i=1;i<=tot;i++) func=max(func,p[i].y);
	sam=func,pos=0;
	op.clear();
	for(i=1;i<=tot;i++) if(p[i].y>=sam) op.insert(p[i].x);
	for(i=tot;i>=1;i--){
		if(pos<sam){
			if(op.size()) ans1=max(ans1,*op.begin()-p[i].x);
			else ans1=max(ans1,a[n]-p[i].x);
		}
		if(p[i].y>=sam-1) op.insert(p[i].x);	
		pos=max(pos,p[i].y);
	}
	sam=func+1,pos=0;
	op.clear();
	for(i=1;i<=tot;i++) if(p[i].y>=sam) op.insert(p[i].x);
	for(i=tot;i>=1;i--){
		if(pos<sam){
			if(op.size()) ans2=max(ans2,*op.begin()-p[i].x);
			else ans2=max(ans2,a[n]-p[i].x);
		}
		if(p[i].y>=sam-1) op.insert(p[i].x);	
		pos=max(pos,p[i].y);
	}
	cout<<max(ans1+(n-func)*k,ans2+(n-func-1)*k)<<endl;
	return 0;
}
```

---

