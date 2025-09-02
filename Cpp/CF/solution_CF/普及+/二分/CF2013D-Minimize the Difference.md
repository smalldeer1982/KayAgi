# Minimize the Difference

## 题目描述

给你一个长度为 $n$ 的数 $a_1,a_2,…,a_n$ 我们可以对数组进行任意数量(可能是零)的运算。

在每次操作中，我们选择一个位置 $i$ ( $1 \le i \le n−1 $
 ) ，使 $a_i-1,a_{i+1}+1$

求 $max(a_1,a_2,…,a_n)−min(a_1,a_2,…,a_n)$ 的最小可能值。

## 说明/提示

在第三个测试案例中，您可以使用 $i=1$
 执行两次操作。
之后，数组为 $[2,3,2,3]$
 所以 $ans=max(2,3,2,3)−min(2,3,2,3)=3−2=1$
 。

## 样例 #1

### 输入

```
5
1
1
3
1 2 3
4
4 1 2 3
4
4 2 3 1
5
5 14 4 10 2```

### 输出

```
0
2
1
1
3```

# 题解

## 作者：lsc72 (赞：5)

### 题解：Minimize the Difference
由于可以执行**任意次**操作，所以原操作可以转化为将前面的数转移到后面。  
也就是说，前面的数可以任意小，而后面的数则可以变大。  

然后答案一定是要更接近均值才更优（使得极差更小）。

因此最小值我们可以从前往后扫描每个数，计算前缀平均值（向下取整）并取最小值来得到。  
而最大值可以从后向前扫描每个数，计算后缀平均值（向上取整）并取最大值。

可以证明这是正确的。

记 $sq$ 为前缀和序列，$sh$为后缀和序列。  
事实上最后答案求的正是：
$$ \overset{n}{\max_{i=1}}\lceil sh_{n-i+1}/i \rceil - \overset{n}{\min_{i=1}}\lfloor sq_i/i \rfloor $$
### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll T,n,a[200010];
int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	cin>>T;
    while (T--){
        cin>>n;
        for (int i=1;i<=n;i++) cin>>a[i];
        ll sum1=0,sum2=0,ans1=1e18,ans2=-1e18;
        for (int i=1;i<=n;i++) sum1+=a[i],ans1=min(ans1,sum1/i);
        for (int i=n;i>=1;i--) sum2+=a[i],ans2=max(ans2,((sum2-1)/(n-i+1)+1));
        cout<<ans2-ans1<<'\n';
    }
	return 0;
}
```

---

## 作者：DYYqwq (赞：3)

这题有两个做法。

### 做法一。

首先有一个显然的结论：如果 $a_i > a_{i + 1}$，那么在 $i$ 位置执行操作就是有利的。

于是得到最终数组是不递减的。

于是考虑用一个有序的栈维护整个数组。其中有很多对 $(val,cnt)$，就是表示值 $val$ 和其出现次数 $cnt$。

我们一定希望数组尽量平均。

记录一个东西 $(sum,num)$ 表示删掉的数字和以及删掉的数字个数的总数。初始值设成 $(a_i , 1)$。

于是每次要向栈内扔 $a_i$ 的时候观察一下，如果栈顶元素 $> \frac{sum}{num}$，那么删除它，直到栈顶元素 $\le \frac{sum}{num}$ 为止。在这期间要一直统计 $sum$ 和 $num$。

最后考虑会向栈内抛入什么。一个是  $(\frac{sum}{num} + 1,sum \operatorname{mod} num)$，然后发现没抛完全，会有一部分的 $\frac{sum}{num}$ 没抛进去，那就再抛一个 $(\frac{sum}{num},num - sum \operatorname{mod} num)$。

但是注意顺序，因为我们的栈是有序的，要先抛进去 $\frac{sum}{num}$ 的，再抛 $\frac{sum}{num} + 1$ 的。

最后输出栈顶减栈底。

这样做每个 $a_i$ 只会导致加入两个元素，且每个元素被移除就没有再加回来的可能，因此时间复杂度  $O(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node
{
	int sum , cnt;
};
int t , n , a[200010];
stack<node> s;
signed main()
{
	scanf("%lld" , &t);
	while(t --)
	{
		while(!s.empty()) s.pop();
		scanf("%lld" , &n);
		for(int i = 1 ; i <= n ; i ++) scanf("%lld" , &a[i]);
		for(int i = 1 ; i <= n ; i ++)
		{
			int sum = a[i] , num = 1;
			while(!s.empty())
			{
				node tmp = s.top();
				if(tmp.sum < sum / num) break;
				sum += tmp.sum * tmp.cnt , num += tmp.cnt;
				s.pop();
			}
			s.push({sum / num , num - sum % num});
			if(sum % num) s.push({sum / num + 1 , sum % num});
		}
		int head = s.top().sum;
		while(s.size() > 1) s.pop();
		int tail = s.top().sum;
		printf("%lld\n" , head - tail);
	}
	return 0;
}
```

### 做法二。

这种做法比较简单，但是不容易理解。

直接计算最小前缀平均值与最大后缀平均值的差值即可。

因为我们一定有手段使得前面的一段都变成那么小的平均值，且让后面一段变成那么大的平均值，并且让中间那一段没有影响。

感知了一下应该挺对，但是不知道怎么证。

其实这个做法是抄的楼上的，问了他，他现在还没回我。

无耻的再放个代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t , n , a[200010] , lsum[200010] , rsum[200010];
signed main()
{
	scanf("%lld" , &t);
	while(t --)
	{
		int lmn = 9e18 , rmx = -9e18;
		scanf("%lld" , &n);
		for(int i = 1 ; i <= n ; i ++) scanf("%lld" , &a[i]);
		for(int i = 1 ; i <= n ; i ++) lsum[i] = lsum[i - 1] + a[i];
		for(int i = n ; i >= 1 ; i --) rsum[i] = rsum[i + 1] + a[i];
		for(int i = 1 ; i <= n ; i ++) lmn = min(lmn , (int)floor(lsum[i] / i));
		for(int i = n ; i >= 1 ; i --) rmx = max(rmx , (int)ceil((rsum[i] - 1) / (n - i + 1)) + 1);
		printf("%lld\n" , rmx - lmn);
	}
	return 0;
}
```

---

## 作者：wuxigk (赞：2)

### 前言

搜了一圈都没有看到对“最小极差等于最大后缀平均值向上取整减去最小前缀平均值向下取整”这一结论的证明，因此在这里补一个。证明过程还是有一定的技巧性的，尤其是引理二，其中用到了一些取整函数的性质，不熟悉的同学可以自行了解。

### 一些记号

对于长度为 $n$ 的序列 $A$，记：

- 下标为 $1\sim n$ 组成的连续子序列为 $A_{1\sim n}$；

- $A$ 中的最小值为 $\min(A)$，$A$ 中的最大值为 $\max(A)$；

- $A$ 的元素之和为 $S(A)$；

- $A$ 中前 $i$ 个数组成的前缀平均值为 $L(A,i)=\frac{S(A_{1\sim i})}{i}$；

- $A$ 的最小前缀平均值为 $L(A)=\min_{i=1}^nL(A,i)$；

- $A$ 中第 $i$ 个数开始组成的后缀平均值为 $R(A,i)=\frac{S(A_{i\sim n})}{n-i+1}$；

- $A$ 的最大后缀平均值为 $R(A)=\max_{i=1}^nR(A,i)$；

- 若 $A_i>A_{i+1}$，称 $(i,i+1)$ 上的操作是“平衡”的。

### 引理一

对序列 $A$ 进行任意次操作得到序列 $B$， 则 $\min(B)\le\lfloor L(A)\rfloor$且$\max(B)\ge\lceil R(A)\rceil$。

### 引理一证明

记序列长度为 $n$，假设 $\min(B)>\lfloor L(A)\rfloor$。令 $i$ 为某个满足 $L(A,i)=L(A)$ 的正整数，因为 $L(B,i)\ge\min(B)$，故：

$$\lfloor L(B,i)\rfloor\ge\lfloor\min(B)\rfloor=\min(B)\\>\lfloor L(A)\rfloor=\lfloor L(A,i)\rfloor$$

因此 $L(B,i)>L(A,i)$，即 $S(B_{1\sim i})>S(A_{1\sim i})$。

然而，$\forall j\ne i$，在 $(j,j+1)$ 上进行的操作不会影响 $S(B_{1\sim i})$，而在 $(i,i+1)$ 上进行的操作使得 $S(B_{1\sim i})$ 变小，因此最终一定有 $S(B_{1\sim i})\le S(A_{1\sim i})$，矛盾。

对于后缀平均值的命题同理可证。

### 引理二

对序列 $A$ 进行任意次**平衡**操作得到序列 $B$，则 $\lfloor L(A)\rfloor=\lfloor L(B)\rfloor$ 且 $\lceil R(A)\rceil=\lceil R(B)\rceil$。

### 引理二证明

只需证明命题对单次平衡操作成立，记该平衡操作在 $(i,i+1)$ 上进行。不难发现，$\forall j\ne i,L(A,j)=L(B,j)$，而 $L(B,i)=L(A,i)-\frac{1}{i}<L(A,i)$，因此 $L(B)\le L(A)$，所以 $\lfloor L(B)\rfloor\le\lfloor L(A)\rfloor$，下面证明一定取等。

假设 $\lfloor L(B)\rfloor<\lfloor L(A)\rfloor$，则 $\forall j\ne i,\lfloor L(B,i)\rfloor<\lfloor L(B,j)\rfloor$。（否则 $\exists k\ne i,\lfloor L(B)\rfloor=\lfloor L(B,k)\rfloor=\lfloor L(A,k)\rfloor\ge\lfloor L(A)\rfloor$，矛盾）

若 $i=1$ ，则 $\lfloor L(B,1)\rfloor<\lfloor L(B,2)\rfloor$，即 $A_1-1<\left\lfloor\frac{A_1+A_2}{2}\right\rfloor$。讨论 $A_2$ 的大小：若 $A_2\le A_1-2$，则 $\left\lfloor\frac{A_1+A_2}{2}\right\rfloor\le A_1-1$，矛盾；若 $A_2=A_1-1$，则 $\left\lfloor\frac{A_1+A_2}{2}\right\rfloor= A_1-1$，亦矛盾。

若 $i>1$ ，一方面有 $\lfloor L(B,i)\rfloor<\lfloor L(B,i-1)\rfloor$，因此 $L(B,i)<L(B,i-1)$，展开并整理得到：

$$S(A_{1\sim i-1})>(i-1)(A_i-1)$$

另一方面，对 $L(B,i)$ 与 $L(B,i+1)$ 作差，利用 $A_{i+1}\le A_i-1$ 以及前面的不等式整理得到：

$$L(B,i)-L(B,i+1)>-\frac{1}{i+1}$$

将不等式左边拆成“整数部分加小数部分”的形式，整理得到：

$$\{L(B,i)\}>\lfloor L(B,i+1)\rfloor-\lfloor L(B,i)\rfloor-\frac{1}{i+1}+\{L(B,i+1)\}$$

其中 $\lfloor L(B,i+1)\rfloor-\lfloor L(B,i)\rfloor\ge 1,\{L(B,i+1)\}\ge 0$，因此 $\{L(B,i)\}>\frac{i}{i+1}$。但 $L(B,i)$ 可表示为分母为 $i$ 的有理数，因此 $\{L(B,i)\}\le\frac{i-1}{i}$，矛盾。

综上，一定有 $\lfloor L(A)\rfloor=\lfloor L(B)\rfloor$，同理可证明 $\lceil R(A)\rceil=\lceil R(B)\rceil$。

### 最优解的构造及证明

对于长度为 $n$ 的序列 $A$，在其上反复使用平衡操作，直到得到单调不减的序列 $B$。由于 $B$ 单调不减，显然有 $\min(B)=B_1=L(B)=\lfloor L(B)\rfloor$ 以及 $\max(B)=B_n=R(B)=\lceil R(B)\rceil$。根据引理二，$\lfloor L(B)\rfloor=\lfloor L(A)\rfloor$ 且 $\lceil R(B)\rceil=\lceil R(A)\rceil$，因此序列 $B$ 的极差 $\max(B)-\min(B)=\lceil R(A)\rceil-\lfloor L(A)\rfloor$。

另一方面，根据引理一，无论在 $A$ 上进行怎样的操作，最终得到的序列 $C$ 一定满足 $\max(C)-\min(C)\ge\lceil R(A)\rceil-\lfloor L(A)\rfloor$，因此上述序列 $B$ 已经达到了最优解，故最终答案为 $\lceil R(A)\rceil-\lfloor L(A)\rfloor$。

### 代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;
int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<ll> a(n);
		for (auto& x : a)
			cin >> x;
		vector<ll> pre_avg(n), suf_avg(n);
		pre_avg[0] = a[0];
		for (int i = 1; i < n; i++)
			pre_avg[i] = pre_avg[i - 1] + a[i];
		for (int i = 0; i < n; i++)
			pre_avg[i] /= i + 1;
		suf_avg[n - 1] = a[n - 1];
		for (int i = n - 2; i >= 0; i--)
			suf_avg[i] = suf_avg[i + 1] + a[i];
		for (int i = n - 1; i >= 0; i--)
			suf_avg[i] = (suf_avg[i] + n - i - 1) / (n - i);
		cout << *ranges::max_element(suf_avg) - *ranges::min_element(pre_avg) << '\n';
	}
}
```

---

## 作者：Meickol (赞：0)

提供一个二分的解法。

由题意条件可知，因为我们让 $a_i-1,a_{i+1}+1$，并且我们希望使得序列中极差最小。

虽然原序列并未保证单调，但是我们可将原序列通过若干次题目给定的操作使其构造成单调不降的序列，因为题目操作相当于从前面拿一部分给后面，并且保证构造后的序列每个值尽可能接近。

保证了序列单调性后，即可考虑二分答案，我们要使得数列中极差最小只需要使得序列中的最大值最小且序列中的最小值最大。

通过两次二分答案求出这两个值后做差即可得到答案。

关于二分答案函数的细节，当确定一个二分值 $x$ 时，我们枚举整个序列，如果序列当前位置的值大于 $x$，我们可以考虑将当前这个位置的数不断 $-1$ 使其变成 $x$，然后因为我们对这个位置 $-1$ 操作，相应的减的次数可以留给后面需要的数让它们进行 $+1$ 操作。

对于求最小值的最大时时，我们只需要判一下我们前面减一的操作提供给后面加一的机会（即余量）是否够弥补后面加一的需要即可。

对于求最大值的最小时，我们即需要判断前面减一操作提供给后面加一的机会（即余量）是否消耗完即可，若没消耗完，则说明可以继续加，说明最小值会比 $x$ 更大。

```cpp
#define rep(x,y,z) for(int x=y;x<=z;x++)
typedef long long LL;
const int N=2e5+5;
int n;
LL a[N];
bool check(LL x){
	LL res=0;
	rep(i,1,n){
		if(a[i]>x) res+=a[i]-x;
		if(a[i]<x){
			if(res<x-a[i]) return false; //余量不够，即无法让最小值无法增大到x，说明x偏大
			res-=x-a[i];
		}
	}
	return true;
}
bool check2(LL x){
	LL res=0;
	rep(i,1,n){
		if(a[i]>x) res+=a[i]-x;
		if(a[i]<x){
			res-=x-a[i];
			res=max(res,0LL);
		}
	}
	if(res>0) return false; //有余量，即无法让序列最大值减小到x，说明x偏小
	else return true;
}
void solve(){
	cin>>n;
	rep(i,1,n) cin>>a[i];
	LL l=1,r=1e12;
	while(l<r){
		LL mid=(l+r+1)>>1;
		if(check(mid)) l=mid;
		else r=mid-1;
	}
	LL minx=l;
	l=1,r=1e12;
	while(l<r){
		LL mid=l+r>>1;
		if(check2(mid)) r=mid;
		else l=mid+1;
	}
	LL maxx=l;
	cout<<maxx-minx;
}
```

---

