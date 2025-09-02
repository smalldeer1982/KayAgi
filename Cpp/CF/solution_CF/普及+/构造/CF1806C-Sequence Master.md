# Sequence Master

## 题目描述

For some positive integer $ m $ , YunQian considers an array $ q $ of $ 2m $ (possibly negative) integers good, if and only if for every possible subsequence of $ q $ that has length $ m $ , the product of the $ m $ elements in the subsequence is equal to the sum of the $ m $ elements that are not in the subsequence. Formally, let $ U=\{1,2,\ldots,2m\} $ . For all sets $ S \subseteq U $ such that $ |S|=m $ , $ \prod\limits_{i \in S} q_i = \sum\limits_{i \in U \setminus S} q_i $ .

Define the distance between two arrays $ a $ and $ b $ both of length $ k $ to be $ \sum\limits_{i=1}^k|a_i-b_i| $ .

You are given a positive integer $ n $ and an array $ p $ of $ 2n $ integers.

Find the minimum distance between $ p $ and $ q $ over all good arrays $ q $ of length $ 2n $ . It can be shown for all positive integers $ n $ , at least one good array exists. Note that you are not required to construct the array $ q $ that achieves this minimum distance.

## 说明/提示

In the first test case, it is optimal to let $ q=[6,6] $ .

In the second test case, it is optimal to let $ q=[2,2,2,2] $ .

## 样例 #1

### 输入

```
4
1
6 9
2
1 2 2 1
2
-2 -2 2 2
4
-3 -2 -1 0 1 2 3 4```

### 输出

```
3
2
5
13```

# 题解

## 作者：六楼溜刘 (赞：11)

## 题意
给你一个长度为 $2n$ 的整数序列 $p$，你要构造一个长度同样为 $2n$ 的整数序列 $q$，满足若令 $U=\{1,2,3\dots2n\}$，$\forall S \subseteq U$ 且 $\left| S \right|=m$，$\prod_{i \in S}q_i=\sum_{i \in U \setminus S}q_i$。只需要输出最小的 $\sum_{i=1}^{n}\left| p_i-q_i \right|$。
## 题解
已经有一篇题解给出打表得到的结论了，那我来证明一下。

- 假如 $q$ 中所有元素相等。

显然，有 $q_1^n=n\cdot q_1$。

解得 $n=1$ 或 $q_1=0$ 或 $n=2$ 且 $q_1=2$。

- 假如 $q$ 中有元素不与其他相等。

首先，最终答案与顺序无关，那么我们钦定两个元素 $q_1$ 和 $q_2$ 不相等，很显然不会影响答案。由限制条件可得：

$$q_1 \times \prod_{i=3}^{n+1}q_i=q_2+\sum_{i=n+2}^{2n}q_i$$
$$q_2 \times \prod_{i=3}^{n+1}q_i=q_1+\sum_{i=n+2}^{2n}q_i$$

两式相减，可得：

$$(q_1-q_2) \times \prod_{i=3}^{n+1}q_i=(q_2-q_1)$$

即：

$$(q_1-q_2) \times (\prod_{i=3}^{n+1}q_i+1)=0$$

由于 $q_1\not=q_2$，故 $\prod_{i=3}^{n+1}q_i=-1$。

注意，由于要求所有长度为 $n$ 的子序列都满足条件，故所有不包含 $q_1$ 和 $q_2$ 且长度为 $n-1$ 的子序列均要求乘积为 $-1$。

假如 $n$ 为奇数，无法构造这样的 $q$。因为 $n-1$ 为偶数，则需要构造一些 $1$ 和一些 $-1$ 使得任意子序列中有奇数个 $-1$，无论如何，都会有至少一个长度合适的子序列乘积为 $1$，不满足条件。

假如 $n$ 为偶数，很显然只需要使 $q_3$ 至 $q_{2n}$ 的所有数均等于 $-1$ 即可。

此时，由 $q_1 \times \prod_{i=3}^{n+1}q_i=q_2+\sum_{i=n+2}^{2n}q_i$ 可得，$q_1 \times (-1)=q_2-(n-1)$，即 $q_1+q_2=n-1$。

由条件可知，$\prod_{i=1}^{n}q_i = \sum_{i=n+1}^{2n}q_i$。故$q_1 \cdot q_2 \cdot (-1)^{n-2} = -1 \times n$，又由于 $n$ 为偶数，故 $q_1\cdot q_2=-n$。

解得 $q_1=-1,q_2=n$。

综合下来，我们只要先算一下全部相等的情况，（对于偶数 $n$）再枚举一个 $q_2$ 算一下不相等的情况，取最小值即可得到答案。

## ~~很丑的~~code

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#define int long long
#define forup(i,s,e) for(register int i=(s);i<=(e);i++)
#define fordown(i,s,e) for(register int i=(s);i>=(e);i--)
using namespace std;
inline int read(){
	int x=0,f=1;char c;
	while(!isdigit(c=getchar()))if(c=='-')f=-1;
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
const int N=2e5+5,inf=1e18;
int t,n,a[N<<1],s1,s2,s3,ans;
signed main(){
	t=read();
	while(t--){
		n=read();s1=s2=s3=0;
		ans=inf;
		forup(i,1,n<<1){
			a[i]=read();
			s1+=abs(a[i]);
			s2+=abs(a[i]+1);
			if(n==2) s3+=abs(a[i]-2);
		}
		if(n==1){
			printf("%lld\n",abs(a[1]-a[2]));
			continue;
		}
		if(n%2==1){
			printf("%lld\n",s1);
			continue;
		}
		ans=min(ans,s1);
		if(n==2){
			ans=min(ans,s3);
		}
		forup(i,1,n<<1){
			ans=min(ans,s2-abs(a[i]+1)+abs(a[i]-n));
		}
		printf("%lld\n",ans);
	}
}
```


---

## 作者：Xy_top (赞：9)

也是一道有意思的诈骗题，可是我硬是吃了 5 次 WA，导致排名损失约 400，最终没有进三位数排名，所以纪念一下。

这种题目看上去很难很难，不过我们可以用拥有强大算力的电脑帮我们计算。

随便写个程序枚举发现当 $n\geq 3$ 时，如果 $n$ 为奇数，那么合法方案只有一个，就是全 $0$，否则有一种构造方式是 $2\times n - 1$ 个 $-1$ 加上一个 $n$。

还有一些特殊情况需要考虑，$n=2$ 时需要考虑全 $2$ 的情况，$n=1$ 时两个相同的数就可以，所以答案为 $a[1]-a[2]$ 的绝对值。

然后看 $n\geq 3$ 的情况，我们的 $n$ 和 $p$ 中的哪个数匹配呢？显然是最大的数，那么我们 $O(n)$ 求出最大值
，或者直接一遍 sort 就行了。

因为是赛时代码，很慌所以有点乱：

```cpp

#include <cmath>
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;
int t, n, ans;
int a[400005];
signed main () {
	cin >> t;
	while (t --) {
		ans = 0;
		cin >> n;
		for (int i = 1; i <= 2 * n; i ++) {
			cin >> a[i];
			ans += abs (a[i]);
		}
		if (n == 1) {
			cout << abs (a[2] - a[1]) << "\n";
			continue;
		}
		int tmp = 0, ma = -1000000000;
		if (n == 2) ans = min (ans,  abs (a[1] - 2) + abs (a[2] - 2) + abs(a[3] - 2) + abs (a[4] - 2) );
		if (n & 1) {
			cout << ans << "\n";
			continue;
		}
		sort (a + 1, a + 2 * n + 1);
		for (int i = 1; i <= 2 * n - 1; i ++) tmp += abs (a[i] + 1);
		cout << min (ans, tmp + abs (a[2 * n] - n) ) << "\n";
	}
	return 0;
}
```


---

## 作者：olegekei (赞：5)

## 题意
给定长为 $2n$ 的数组 $p$，你需要构造一个长度为 $2n$ 的数组 $q$，满足 $ S \subseteq U $ 且 $ |S|=m $，$ \prod\limits_{i \in S} q_i = \sum\limits_{i \in U \setminus S} q_i $。

且你构造的 $q$ 数组需要让 $ans = \sum\limits_{i=1}^k|a_i-b_i| $ 最小，输出这个 $ans$。
## 思路
不难构造一个全零数组 $q$，即可满足题目要求。

接下来观察样例，由第一组样例发现 $n=1$ 时容易构造 $q=\{q_1,q_1\}$，即可使答案最小。

由第二组样例发现 $n=2$ 时可以构造 $q=\{2,2,2,2\}$，可能可以使答案最小。

第三组样例发现很难找出什么性质，甚至无法手玩出样例，此时尝试写一个爆搜程序暴力枚举 $q$ 数组，观察样例输出 $5$，$p=\{-2,-2,2,2\}$，所以我们可以尝试将 $p$ 数组的每个元素都加上 $-5 \sim 5$ 来尝试得到 $q$ 数组，当枚举出一个 $q$ 数组时就更新一下答案。

发现最后得到的 $q=\{-1,-1,-1,2\}$，尝试将 $n$ 推广到更大，发现当 $n$ 为偶数时可以构造出 $q=\{-1,-1,……,-1,n\}$，而 $n$ 为奇数时则无法构造。

最后观察第四组样例，进一步确认了 $q=\{-1,-1,……,-1,n\}$ 的正确性。

分讨一下 $n \le 2$ 的情况和 $n$ 的奇偶即可。
## 代码
```cpp
#include<cmath>
#include<iostream>
using namespace std;
int n;
long long a[400015];
int main(){
ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
int t;
cin>>t;
while(t--){
	cin>>n;
	int m=n<<1;
	long long maxn=-1e9;
	long long ans=0,res=0;
	for(int i=1;i<=m;i++){
		cin>>a[i];
		ans+=abs(a[i]);
		if(a[i]>maxn)maxn=a[i];
	}
	if(n==1){
		cout<<abs(a[1]-a[2])<<'\n';continue;
	}
	if(n&1){
		for(int i=1;i<=m;i++){
			res+=abs(a[i]);
		}
		cout<<res<<'\n';continue;
	}
	if(n==2){
		ans=min(abs(a[1])+abs(a[2])+abs(a[3])+abs(a[4]),abs(a[1]-2)+abs(a[2]-2)+abs(a[3]-2)+abs(a[4]-2));
	}
	for(int i=1;i<=m;i++){
		res+=abs(a[i]+1);
	}
	res-=abs(maxn+1);
	res+=abs(maxn-n);
	ans=min(ans,res);
	cout<<ans<<'\n';
}
return 0;
}
```

---

## 作者：Leasier (赞：3)

打表发现只有下面这几种类型的好序列：

- $[x, x]$。
- $[2, 2, 2, 2]$。
- $[0, 0, \cdots, 0]$。
- 长为 $2n$ 的 $[-1, -1, \cdots, -1, n]$，且 $n$ 为偶数。

直接模拟即可。注意最后一种序列中 $n$ 可以放在任意位置。~~一开始钦定 $m$ 只能放在最后一个位置 WA 了一发 /fn~~

------------

下面来证明好序列只有这几种。

考虑每次把一个长为 $n$ 的 $a$ 重排。

讨论 $\{1, 3, 4, \cdots, n + 1\}$ 和 $\{2, 3, 4, \cdots, n + 1\}$，得：

- $a_1 \displaystyle\prod_{i = 3}^{n + 1} a_i = a_2 + \sum_{i = n + 2}^{2n} a_i$。
- $a_2 \displaystyle\prod_{i = 3}^{n + 1} a_i = a_1 + \sum_{i = n + 2}^{2n} a_i$。

相减可得 $(a_2 - a_1) \displaystyle\prod_{i = 3}^{n + 1} a_i = a_1 - a_2$，于是有两种情况：

- $a_1 = a_2$。
- $\displaystyle\prod_{i = 3}^{n + 1} a_i = -1$。

只要有一项为 $0$ 则必须全 $0$；当 $a$ 中元素全部相等，则 $a_1^n = n a_1$，唯二解为 $n = 1$ 和 $n = a_1 = 2$。

排除上面两种情况后，考虑钦定 $a_1 \neq a_2$，则 $[3, 2n]$ 的任意子集积均为 $-1$，唯一解为 $a_3 = a_4 = \cdots = a_{2n} = -1$，此时 $a_1 = -1, a_2 = n$。

代码：
```cpp
#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int p[400007];

inline ll min(ll a, ll b){
	return a < b ? a : b;
}

int main(){
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++){
		int n, m;
		scanf("%d", &n);
		m = n * 2;
		for (int j = 1; j <= m; j++){
			scanf("%d", &p[j]);
		}
		if (n == 1){
			printf("%d\n", abs(p[1] - p[2]));
			continue;
		}
		ll x = 0, y, z = 0x7fffffffffffffffll;
		for (int j = 1; j <= m; j++){
			x += abs(p[j]);
		}
		if (n == 2){
			y = (ll)abs(p[1] - 2) + abs(p[2] - 2) + abs(p[3] - 2) + abs(p[4] - 2);
		} else {
			y = 0x7fffffffffffffffll;
		}
		if (n % 2 == 0){
			ll sum = 0;
			for (int j = 1; j <= m; j++){
				sum += abs(p[j] + 1);
			}
			for (int j = 1; j <= m; j++){
				z = min(z, sum - abs(p[j] + 1) + abs(p[j] - n));
			}
		}
		printf("%lld\n", min(x, min(y, z)));
	}
	return 0;
}
```

---

## 作者：Inexistented (赞：3)

## 题目意思

一个包含 $2m$ 个数的序列是好的。

给定一个序列 $a$ , 将它分成 $2$ 个都包含 $m$ 个数的序列时，使其中任意一个序列的元素积等于另一个序列的元素和。

求出一个与给定序列距离最小的序列（距离的定义：两个序列对应元素差的绝对值的总和）。

## 解析

一共有四种情况。

令 $max$ 为该序列的最大数。

- 当 $m=1$ ，则最短距离为 $|a[1]-a[2]|$ 。

- 当 $m=2$ ，则最短距离为 $\sum\limits_{i=1}^m|a_i|$    与 $\sum\limits_{i=1}^m|a_i-2|$ 中的较小数。

- 当 $m=>2$ 的奇数，则最短距离为 $\sum\limits_{i=1}^m|a_i|$ 。

- 当 $m=>2$ 的偶数，则最短距离为 $\sum\limits_{i=1}^m|a_i|$ 与 $\sum\limits_{i=1}^m|a_i|+|max-n|-|max+1|$ 中的较小数。

## 代码

```c
#include <bits/stdc++.h>
using namespace std;

long long a[400001];

void solve()
{
	int i,n,m;
	
	long long sum=0,ans=0,MAX=-1e9;
	
	cin>>n;
	
	m=n*2;
	
	for(i=1;i<=m;i++)
	{
		cin>>a[i];
		
		ans=ans+abs(a[i]);
		
		if(a[i]>MAX)
		{
			MAX=a[i];
		}
	}
	
	if(n==1)
	{
		cout<<abs(a[1]-a[2])<<endl;
		
		return ;
	}
	if(n==2)
	{
		ans=min(abs(a[1])+abs(a[2])+abs(a[3])+abs(a[4]),abs(a[1]-2)+abs(a[2]-2)+abs(a[3]-2)+abs(a[4]-2));
	}
	if(n%2==1)
	{
		for(i=1;i<=m;i++)
		{
			sum=sum+abs(a[i]);
		}
		
		cout<<sum<<endl;
		
		return ;
	}
	for(i=1;i<=m;i++)
	{
		sum=sum+abs(a[i]+1);
	}
	
	sum=sum+abs(MAX-n)-abs(MAX+1);
	
	ans=min(ans,sum);
	
	cout<<ans<<endl;
}
int main()
{
	int Time;
	
	cin>>Time;
	
	while(Time--)
	{
		solve();
	}
	
	return 0;
}
```


---

## 作者：隐仞Mrsu (赞：2)

# 题意
给定正整数 $n$，以及长度为 $2n$ 的数组 $p$。

要求构造出一个长度同样为 $2n$ 的数组 $q$，在满足 $q$ 合法的条件下，使得 $ans=\sum_{i=1}^{2n} \lvert p_i-q_i \rvert$ 最小，输出这个 $ans$。

长度为 $2n$ 的数组 $q$ 合法的条件是：**任意地**将 $q$ 平均分成长度为 $n$ 的两份，一部分的连乘与另一部分的连加**都相等**。


# 分析
### 当 $n=1$ 时
此时长度 $len=2$。对于要构造出的数组 $q$，平均分成两份后，每份仅有一个数。那么 $q$ 中包含两个相等的数 $a$ 就是合法的了。

因此，答案就是 $\lvert p_1-a\rvert + \lvert p_2-a\rvert$。要使答案最小，根据绝对值的相关性质，令 $a$ 的值在 $p_1$ 与 $p_2$ 之间即可，此时答案可以推出为 $\lvert p_1-p_2\rvert$。

### 当 $n=2$ 时
此时长度 $len=4$，能够构造出的 $q$ 数组如下：
```
0	0	0	0
2	2	2	2
-1	-1	-1	2
-1	-1	2	-1
-1	2	-1	-1
2	-1	-1	-1
```

说明：当 $q$ 为 $-1,-1,-1,2$ 时，满足 $-1\times -1=-1+2=1$ 以及 $-1\times 2=-1-1=-2$，故该 $q$ 数组合法，其余同理。

为了让 $\sum_{i=1}^{2n} \lvert p_i-q_i \rvert$ 最小，应该让两数组中，值小的元素相减，值大的元素相减。

因此，首先对 $p$ 由小到大排序，构造出的 $q$ 数组只使用值从左到右不下降的，即上面列出的前三个。然后用这三个 $q$ 数组分别求结果，取最小值为答案。

### 当 $n\ge3$ 且 $n$ 为奇数时
此时的 $q$ 数组只能为 $0,0,\ldots,0$。

则先将 $p$ 数组由小到大排序，用上述 $q$ 数组求结果，输出答案。

### 当 $n\ge4$ 且 $n$ 为偶数时
此时的 $q$ 数组可以为 $0,0,\ldots,0,0$ 或 $-1,-1,\cdots,-1,n$。

对 $p$ 数组由小到大排序，分别用上述两种 $q$ 数组求结果，取最小值为答案。

# 代码
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 1e6+6;
LL _,n,p[N];
void work(){
	cin>>n;
	for(LL i=1;i<=2*n;i++){
		cin>>p[i];
	}
	sort(p+1,p+1+2*n);
	if(n==1){
		cout<<abs(p[2]-p[1])<<'\n';
		return;
	}
	LL res=2e15,r=0;
	if(n==2){
		for(LL i=1;i<=2*n;i++){
			r+=abs(p[i]);
		}
		res=min(res,r);
		r=0;
		for(LL i=1;i<=2*n;i++){
			r+=abs(p[i]-2);
		}
		res=min(res,r);
		r=0;
		for(LL i=1;i<2*n;i++){
			r+=abs(p[i]+1);
		}
		r+=abs(p[2*n]-2);
		res=min(res,r);
		cout<<res<<'\n';
		return;
	}
	if(n%2==1){
		for(LL i=1;i<=2*n;i++){
			r+=abs(p[i]);
		}
		res=min(res,r);
		cout<<res<<'\n';
	}
	else{
		for(LL i=1;i<=2*n;i++){
			r+=abs(p[i]);
		}
		res=min(res,r);
		r=0;
		for(LL i=1;i<2*n;i++){
			r+=abs(p[i]+1);
		}
		r+=abs(p[2*n]-n); 
		res=min(res,r);
		cout<<res<<'\n'; 
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin>>_;
	while(_--){
		work();
	}
}
```
# 坑点
当时错了两发。

第一次是由于我结果值 $res$ 后面要取最小值，所以初始值要设一个比较大的值。
```cpp
res = 0x3f3f3f3f // wa了的代码
```
然而这个值设小了，因为 $n\le2\cdot 10^5$，且 $p_i\le10^9$，所以应该设 $res\ge 2\cdot 10^{14}$。

还有一个地方有问题是我对 $p$ 数组排序的时候，只对 $p_1$ 到 $p_n$ 排序，然而右边应该是 $p_{2n}$。 

---

## 作者：_ZSR_ (赞：1)

## [Sequence Master ](https://www.luogu.com.cn/problem/CF1806C)
很容易想到，好的序列的个数一定是非常少的，因为它的约束特别强，那么对于一个约束这么强的序列它究竟有什么性质呢？

首先，对于序列中的每个元素都相等的情况，即 $q_i^n=n \times q_i$。解得 $q_i=1,n=1$ 或者 $q_i=2,n=2$ 或者任意 $q_i=0$。

那对于序列中的元素不都相等的情况有什么性质呢？我们列几个方程来看一下。
$$q_1 \times q_3 \times ... \times q_{n+1}=q_2+q_{n+2}+...+q_{2n}$$
$$q_2 \times q_3 \times ... \times q_{n+1}=q_1+q_{n+2}+...+q_{2n}$$

这里令 $q_1 \neq q_2$

上下相减可以得到：
$$(q_1-q_2) \times (q_3 \times ...\times q_{n+1}+1)=0$$

因为 $q_1-q_2 \neq 0$，所以 $q_3 \times ... \times q_{n+1}=-1$

类似的，对于 $q_3,q_4,...,q_{2n}$ 中的任意 $n-1$ 个数，其乘积也一定是 $-1$。那么就可以得到 $q_3=q_4=...=q_{2n}$。又因为 $q_3^{n-1}=-1$，所以 $2|n$。

根据好的序列的定义，我们还可以得到两个式子：
$$q_1 \times q_2 \times ... \times q_n=q_{n+1}+...+q_{2n}$$
$$q_1+q_2+...+q_n=q_{n+1} \times ... \times q_{2n}$$

结合上面推出的性质，我们可以得出 $q_1 \times q_2=-n,q_1+q_2=n-1$，那么 $q_1=n,q_2=-1$。

综上所述，当序列的值都相等的时候，我们很好计算距离，因为好的序列只有那几个。对于不都相等的情况，我们令 $S=\sum_{i=1}^{2n} q_i-(-1)$，枚举每一个数，记当前枚举的数为 $i$，$ans= \min (S-|q_i-(-1)+|q_i-n|)$，即讨论好的序列中哪一位的值为 $n$。

code

```
#include <bits/stdc++.h>
using namespace std;
const int N=400010;
typedef long long ll;
int n,T;
ll a[N];
int main()
{
	scanf("%d",&T);
	while (T--)
	{
		ll sum=0,ans=0;
		scanf("%d",&n);
		for (int i=1;i<=(n<<1);++i)
		{
			scanf("%lld",&a[i]);
			sum+=abs(a[i]-(-1));
			ans+=abs(a[i]);//全部变为0肯定是好的序列
		}
		if (n==1) ans=min(ans,abs(a[1]-a[2]));
		if (n==2) ans=min(ans,abs(a[1]-2)+abs(a[2]-2)+abs(a[3]-2)+abs(a[4]-2));
        //这里不能写else if，因为n=2必然n%2=0，此时我们要看哪一个距离更近
		if (n%2==0)//注意，只有当n%2==0时才有这样的性质
		{
			for (int i=1;i<=(n<<1);++i)
			{
				ans=min(ans,sum-abs(a[i]-(-1))+abs(a[i]-n));
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：fast_photon (赞：1)

**0. 前言**  
Upd 过审之前改不用写吧（

**0.5 题意**  
给定序列 $b$，求出一个好的序列 $a$ 到 $b$ 的最短距离。好的序列的定义是，对于一个长度为 $2n$ 的序列，若任意的 $n$ 个元素积等于其余元素和，则它是好的。两个序列的距离是对应元素差的绝对值的和。  

**1. 分析**  
先特判 $n=1$，这个不用说了吧。  
若所有元素相等为 $a$：  
>$a+a+\dots+a=a\times a\times\dots\times a$  
即 $n\times a=a^n$  
若 $a\neq 0$，有 $n=a^{n-1}$。  

即 $a=0$ 或 $a=\sqrt[n-1]{n}$。  
第一个解显然符合题意，我们来考虑第二个解。  
找个网站画一下函数图像就可以发现，对于任意 $n>2$ 有 $1<\sqrt[n-1]{n}<2$，取不到整数。  
所以“好的”序列已经有：$\{0,0,\dots,0\}$ 和 $\{2,2,2,2\}$  

还有一个显然的结论，序列全部元素的积是不变的。但是想到从这里入手不容易。  
若不是两两相同的序列，就可以找到一对不等元素 $a,b$，考虑划分 $\{a,\dots\},\{b,\dots\}$，我们假设两个子序列里其余元素的和分别为 $c,d$，积为 $e,f$。再考虑两个子序列交换 $a,b$ 这对元素的划分。  

根据不同划分元素总乘积相等，有 $ae\times bf=af\times be$，根据好序列性质代换可得 $(b+d)(a+c)=(a+d)(b+c)$。  
化简，得 $(b-a)(c-d)=0$。因为 $b-a\neq 0$，所以 $c-d=0$。  
我们就有了一个结论：两个子序列去除任意一对不等元素后，元素和相等。  
>首先，至少有某一个序列有至少两个元素两两不等。若两个序列都由单一元素构成，交换除首元素的任意一对元素之后得到这样的序列。  

>其次，假设两个序列分别是 $\{x,\dots,x,y,\dots,y,\dots\}$（$x\neq y$）和 $\{z_1,\dots,z_n\}$，对于任意 $x\neq z_i$：  
>>若 $y\neq z_i$，则两个序列分别去除 $x,z_i$ 后的和与分别去除 $y,z_i$ 后的和应该一样（因为第二个序列的去除方案并未改变），但根据假设（$x\neq y$），第一个序列的剩余和会改变。矛盾。  

>则对于任意 $x\neq z_i$，有 $y=z_i$。同理对于任意 $y\neq z_i$，有 $x=z_i$。  
我们将两个序列互换，可以得到这样一个结论：两个序列都是若干个 $a$ 和 $b$ 组成的。  

而如果这是一个好序列，我们就可以将它任意划分都满足性质。它只由两种数组成，那必有一种达到了至少一半，我们就可以将达到一半的那一种划分到一起。
>我们进行形如 $\{a,\dots,a,b,\dots,b\}$ 和 $\{b,\dots,b\}$ 的划分。将两组分别去掉一个 $a$ 和一个 $b$，得 $(k-1)a+[(n-1)-(k-1)]b=(n-1)b$，化简得 $(k-1)(a-b)=0$。根据假设，$a\neq b$，所以 $k=1$。  

这意味着，原序列必然是形如 $a,b,\dots,b$ 的形式。  
我们将它任意分割，可以得到 $a+(n-1)b=b^n$ 和 $a\times b^{n-1}=b\times n$。两侧分别相减并化简得 $a-b=-(a-b)b^{n-1}$，根据假设 $a\neq b$，所以 $b^{n-1}=-1$。  

$\sqrt[n-1]{-1}$ 只当 $n$ 是偶数时有 $-1$ 一个根。此时有 $a=n$ （$b=-1$ 带入上一段后式）。  
也就是说，任意的偶数 $n$ 有一组额外的 $\{n,-1,\dots,-1\}$ 解。  

**2. 结论**  
这是我写题解第一次给结论单分一个版块。  
对于 $n=1$，任意 $\{a,a\}$ 均可。  
对于 $n>1$，有 $\{0,\dots,0\}$  
对于 $n=2k$，额外有 $\{n,-1,\dots,-1\}$  
对于 $n=2$，额外有 $\{2,2,2,2\}$。  

**2.5 统计**  
对于 $\{n,-1,\dots,-1\}$ 的情况，我们考虑枚举 $n$ 放在哪一位去统计，先假设所有的位都是 $-1$，然后计算将其中某一个替换成 $n$ 能节约的距离。即 $|a_i-n|-|a_i+1|$ 的最小值。这建立在改变某一元素的值并不改变其他元素的距离上。

**3. 代码**  
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm> 
#define int long long
#define maxn 200005

using namespace std;

int _, n, a[maxn * 2];
void work() {
	int ans = 0, asn = 0, mn = 0x3f3f3f3f3f3f3f3fll;
	cin >> n;
	for(int i = 0; i < n * 2; i++) {
		cin >> a[i], ans += abs(a[i]), asn += abs(a[i] + 1);
		if(n % 2 == 0) mn = min(mn, abs(a[i] - n) - abs(a[i] + 1));
	}
	if(n == 1) {
		cout << abs(a[0] - a[1]) << endl;
		return ;
	}
	if(n == 2) {
		ans = min(ans, abs(a[0] - 2) + abs(a[1] - 2) + abs(a[2] - 2) + abs(a[3] - 2));
	}
	ans = min(ans, asn + mn);
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin >> _;
	while(_--) work();
}
```

---

## 作者：robinyqc (赞：1)

Upd on 2023/3/25：修正了一点错误。

推荐使用[我的博客](https://www.cnblogs.com/robinyqc/articles/17233505.html)阅读，它拥有更好的排版。

### 题意简述

令全集 $U=\{1,2,3,\dots,2m\}$。

一个序列 $Q$ 是**好**的，当且仅当 $\forall (S\subseteq U,s.t.\ |S|=m),\prod \limits_{i\in S}{Q_i}=\sum \limits_{j\in(\complement_US)} Q_j$

定义两个长度为 $k$ 的序列 $A$ 和 $B$ 的**距离**是 $\sum\limits_{i=1}^k{|A_i-B_i|}$。

给定长度为 $2n$ 的序列 $P$，请找出与 $P$ **距离最小**的**好**的序列 $Q$，输出它们的距离。



### 解题思路

思考怎样一个序列满足它是好的。

显然，当 $n=1$ 时，$(x,x),s.t.\ x\in \mathbb{Z}$ 都是可以的。因此我们只用考虑 $n\geq2$ 的情况。

不妨先讨论 $n=2$ 时的答案。它应当满足四元轮换对称方程组 $(1.1)$：
$$
\left \{
\begin{aligned}
	ab=c+d\\
	ac=b+d\\
	ad=b+c\\
	bc=a+d\\
	bd=a+c\\
	cd=a+b\\
\end{aligned}
\right.
$$
它的必要条件显然是 $(1.2)$：
$$
ab=c+d,cd=a+b
$$
式子 $(1.2)$ 的必要条件又是（就是把两式相加）$(1.3)$：
$$
a+b+ab=c+d+cd\iff (a+1)(b+1)=(c+1)(d+1)
$$
由轮换性质可得 $(1.4)$：
$$
|a+1|=|b+1|=|c+1|=|d+1|
$$

*为什么有绝对值？举个例子：$(-2,-2,0,0)$，它们无论顺序如何都满足 $(a+1)(b+1)=(c+1)(d+1)$。*

或 $(1.5)$：
$$
\sum[a=-1]\geq3
$$
式子 $(1.5)$ 就是说四个未知数中有三个都是 $-1$，此时 $(1.3)$ 等式两边都是 $0$。

***

先讨论式子 $(1.4)$。设 $x$，显然四个数要么是 $x$，要么是 $-x-2$。

若同时存在 $-x-2$ 和 $x$：

1. 当 $x=-1$ 时，$a=b=c=d=-1$，带回原式，不成立。

2. 当 $x\neq-1$ 时，四个数的正负不尽相同。不妨令 $x\geq0$,那么 $-x-2\leq-2<0$。

   1. 若有一个数为负，不妨令 $a$ 为负，那么式子 $ab=c+d$ 一定不成立（左负右非负）。

   2. 若有两个，不妨令 $a,b$ 为负，那么式子 $cd=a+b$ 一定不成立（左非负右负）。

   3. 若有三个，不妨令 $a,b,c$ 为负，那么:
      $$
      ab=c+d\iff (-x-2)^2=-2
      $$
      无解。

因此，仅存在 $a=b=c=d=x$ 的情况。

可得方程：
$$
x^2=2x
$$
解得 $x=0\text{ 或 }2$。带回原方程，发现都成立。

再来看式子 $(1.5)$，发现很好解：$x=2$。即 $a=2,b=c=d=-1$ 是一组解，带回原方程组，可行。

***

推广一下，至 $n\geq2$。当 $n>2$ 时，情况只会比 $n=2$ 时更苛刻，不会存在比 $n=2$ 时更多的情况。

式子 $(1.4)$ 可以推广为 $(2.1)$：
$$
x^n=nx
$$
解得：$x=0$ 或 $x=\sqrt[n-1]n$ ，在 $n>2$ 时，$\sqrt [n-1]{n}$ 一定不是整数，因为显然 $1<\sqrt[n-1]{n-1}< \sqrt[n-1]n<\sqrt[n-1]{2^{n-1}}=2$。

式子 $(1.5)$ 可以推广为 $(2.2)$：
$$
(-1)^{n-1}\cdot x=-n\text { 且 }x-n+1=(-1)^n
$$
发现只有当 $n\bmod 2=0$ 时，才有解，解为 $x=n$。

***

综上所述，有四种情况：

1. 当 $n=1$ 时，任意整数二元组即可。
2. 当 $n=2$ 时，存在解 $(2,2,2,2)$。
3. 当 $n\bmod2=0$ 时，存在解 $(n,-1,-1,\cdots)$，顺序可以改变。
4. 当 $n\geq2$ 时，存在解 $(0,0,\cdots)$。



### 代码实现

```cpp
//省略了头文件
#define int long long
using namespace std;

#define R myio::read_int()
//也就是说，R 代表的是读入的数。这里省略了快读。
int solve() {
	int n=R;
	int *a=new int[2*n+1];
	for(int i=1;i<=2*n;i++) a[i]=R;
	int minans=9e18;
	if(n==1) minans=abs(a[2]-a[1]);
	if(n==2) {
		int sum=0;
		for(int i=1;i<=4;i++) 
			sum+=abs(2-a[i]);
		minans=min(minans,sum);
	} if(n%2==0) {
		int sum=0;
		for(int i=1;i<=2*n;i++) sum+=abs(-1-a[i]);	//先求和
		for(int i=1;i<=2*n;i++) 
			minans=min(minans,sum-abs(-1-a[i])+abs(n-a[i]));	//再改值
	} int sum=0;
	for(int i=1;i<=2*n;i++) sum+=abs(a[i]);
	delete []a;
	return min(minans,sum);
}
signed main(){
	int t=R;
	while(t--) myio::print_int(solve());
	return 0;
}
```

##### 小尾巴

+ *实际上这份证明在 $n\geq 2$ 的推广处的证明并不严谨：为什么情况会更少？我只能感性理解，没法讲清楚。希望有懂的人能够解答。*

+ *强烈推荐有条件的同学去官网上看原题解，那个肯定是严谨的。我的这篇题解仅提供一种其它的思路。*

---

## 作者：whdywjd (赞：1)

考虑什么样的数组是好的。

1. $q$ 中有多于 $n$ 个 $0$。

由于任意 $n$ 个数乘积为 $0$，因此任意 $n$ 个数和也为 $0$，所以所有数相等且等于 $0$。

2. $q$ 中有恰好 $n$ 个 $0$。

取所有 $0$ 加起来，和为 $0$，则剩下的非 $0$ 部分乘积也为 $0$，矛盾。

3. $q$ 中有 $0$ 且有少于 $n$ 个 $0$。

从 $q$ 的非 $0$ 部分中任选 $n$ 个数，其和都等于另一部分的乘积 $0$。因此非 $0$ 部分所有数相等且等于 $0$，矛盾。

综上，如果 $q$ 中有 $0$，则必然全是 $0$。

4. $q$ 中所有数相等且非 $0$。

设所有数都等于 $x$。

则 $x^n=nx$，可得 $x^{n-1}=n$。

$n=1$ 时，$x$ 可以是任意非 $0$ 整数。

$n>1$ 时，$|x|\neq1$，因此 $n=|n|=|x^{n-1}|\geq2^{n-1}$。此时由 $n\geq2^{n-1}$ 得 $n=2$。

$n=2$ 时，解得 $x=2$。

5. 其它情况（所有数非 $0$ 且存在 $2$ 个数不相等）。

考虑任意 $2$ 个数 $c,d$ 应满足的性质。

设剩下的 $2n-2$ 个数中，其中 $n-1$ 个的乘积为 $a$，另外 $n-1$ 个的和为 $b$。

则有：

$ac=b+d$

$ad=b+c$

两式相减，得 $a(c-d)=d-c$

因此有 $c=d$ 或 $a=-1$。

为了避免 $c=d$，我们选取 $2$ 个不同的数。

这样，对于除 $c,d$ 外的任意 $n-1$ 个数，其乘积为 $-1$。

由于没有 $0$，因此除 $c,d$ 外的所有数都相等。

设其余 $2n-2$ 个数均为 $x$，则 $x^{n-1}=-1$。

得到 $x=-1$ 且 $2|n$。也就是说，$n$ 是奇数时这部分情况无解。

现在我们有 $2n-2$ 个 $-1$，$1$ 个 $c$，$1$ 个 $d$。考虑 $c,d$ 之间的关系。

选取 $c,d$ 和 $n-2$ 个 $-1$ 求和，另外 $n$ 个 $-1$ 求积，得 $c+d-n+2=1$。

选取 $c,d$ 和 $n-2$ 个 $-1$ 求积，另外 $n$ 个 $-1$ 求和，得 $cd=-n$。

即：

$c+d=n-1$

$cd=-n$

解得 $c=n,d=-1$ 或 $c=-1,d=n$。

总结一下好的序列满足的充分条件：
- 所有数为 $0$。

- $n=1$ 且 $q_1=q_2$。

- $n=2$ 且 $q_1=q_2=q_3=q_4=2$。

- $2|n$ 且 $q$ 中有 $1$ 个 $n$ 和 $2n-1$ 个 $-1$。

枚举 $4$ 种情况即可。

---

## 作者：liujy_ (赞：1)

 题目看起来很难，没有什么思路。   
 $n=1$ 时显然取任意两个相同的数都可以。但是我们手玩一下样例就会发现似乎只有全为 $0$ 可以满足条件，$n=2$ 时特判四个 $2$ 的情况。   
 然后我们就发现样例过不去，写个程序打个表发现 $n=2$ 时还有一种情况为三个 $-1$ 和一个 $n$。  
 考虑这样为什么是合法的，如果 $n$ 在属于当前集合，那么这个集合还有奇数个 $-1$，则乘积为 $-n$，另一边是 $n$ 个 $-1$，和也是 $-n$。如果 $n$ 不在选中的集合，那么乘积为 $n$ 个 $-1$ 相乘，和即为 $1$。  
 也就是这种几个 $-1$ 加一个 $n$ 的情况可以推广到所有 $n$ 为偶数的情况。打个表发现是对的，并且打不出其它情况。    
 那就几种情况取一个最大值就行了。    
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#define int long long
using namespace std;
const int N=4e5+5;
int t,n,c[N];long long ans;
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);n*=2;
		if(n==2){
			int x,y;
			scanf("%lld %lld",&x,&y);
			ans=abs(x-y);
		}else {
			ans=0;int cnt=0;
			for(int i=1;i<=n;i++)scanf("%lld",&c[i]),ans+=abs(c[i]),cnt+=(c[i]<0);
			if(n%4==0){
				long long tmp=0,tmp2=ans;
				if(n==4){
					for(int i=1;i<=n;i++)tmp+=abs(c[i]-2);
					ans=min(ans,tmp);
				}
				tmp2-=cnt;tmp2+=(n-cnt);
				int x=abs(c[1]-(n/2)),y=abs(c[1]+1);
				ans=min(ans,tmp2-y+x);
				for(int i=2;i<=n;i++){
					int x=abs(c[i]-(n/2)),y=abs(c[i]+1);
					ans=min(ans,tmp2-y+x);
				}
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}

```     

打表程序。   
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#define int long long
using namespace std;
const int N=2e5+5;
int t,n,a[N];
bool dfs1(int x,int s1,int s2,int cnt1,int cnt2){
	if(x>n)return s1==s2;
	if(cnt1<n/2&&!dfs1(x+1,s1+a[x],s2,cnt1+1,cnt2))return 0;
	if(cnt2<n/2&&!dfs1(x+1,s1,s2*a[x],cnt1,cnt2+1))return 0;
	return 1;
}
bool check(){
	return dfs1(1,0,1,0,0);
}
void dfs(int x){
	if(x>n){
		if(check()){
			for(int i=1;i<=n;i++)printf("%d ",a[i]);
			printf("\n");
		}
		return ;
	}
	for(int i=-n/2;i<=n/2;i++)a[x]=i,dfs(x+1);
}
signed main(){
	for(n=4;n<=12;n++)dfs(1);
	return 0;
}

```


---

## 作者：Citnaris (赞：0)

## 题目描述

给定长度为 $2\times n$ 的序列 $a$，构造同等长度的序列 $b$，使得 $b$ 的任意 $n$ 个数相乘都等于另外 $n$ 个相加，且 $\sum_{i=1}^{2\times n}|a_i -b_i|$ 最小。

## 题目分析

假设 $b$ 序列所有数全部相等，不妨设其全部等于 $z$，所以 $z^n=z\times n$，分三类讨论如下

* $n = 1$：那么 $z=z$，恒成立；
* $n = 2$：那么 $z^2=2\times z$，解方程可得 $x=0$ 或 $x=2$；
* $n\ge 3$：如果 $|z|=1$，那么 $|z\times n|\ge 3,|z^n|=1$，显然不可能相等；如果 $|z|\ge 2$，显然有 $|z\times 3|\le |z^3|$ ，并且当 $z$ 变大时左边的增长比右边快，所以永远不可能 $z^n=z\times n$. 所以只可能 $z=0$.

对于至少存在一对不等数的情况，我们考虑 $b$ 序列的两个不同的数 $x, y(x>y)$，并且假设剩下 $2\times(n - 1)$ 个数中的 $n - 1$ 个乘积为 $p$，另外 $n - 1$ 个和为 $q$，那么有
$$\left\{\begin{matrix} 
  x+q=y\times p \\  
  y+q=x\times p
\end{matrix}\right. $$

两式相减可得 $x-y=(y-x)\times q$，即 $-(y - x) = (y - x)\times q$，由于 $x\neq y$，所以 $q = -1$，由对称性显然可得，这剩余的 $2\times(n-1)$ 个数中任意 $n - 1$ 个相乘都等于 $-1$. 

我们知道这些数里面都没有 $0$，所以这 $2\times (n-1)$ 个数全部相等，又因为任意 $n-1$ 个相乘得 $-1$，所以这些数全是 $-1$，并且要求 $n-1$ 是奇数，$n$ 是偶数。根据以上，我们还可以发现另一组等式

$$\left\{\begin{matrix} 
  x+y+(-1)\times(n - 2) = (-1)^n = 1\\  
  x\times y\times (-1)^{n-2}=x\times y=(-1)\times n
\end{matrix}\right. $$

即

$$\left\{\begin{matrix} 
  x+y=n-1 \\  
  x\times y=-n
\end{matrix}\right.$$ 

考虑 $(x - y)^2=(x+y)^2-4\times x\times y=(n+1)^2$，且 $n+1>0, x-y>0$，所以 $x - y = n + 1$，结合一下 $x+y=n-1$，可得 $x = n, y = -1$.

综上，我们可以得出符合条件的 $b$ 序列以及如何计算最小的答案

* $n=1$，$b=\{x\}(x\in\mathbb Z)$ 时满足条件，显然 $x=a_1$ 或 $a_2$ 时答案最小；
* $n=2$，$b=\{0, 0, 0,0\}$ 或 $b=\{2, 2, 2, 2\}$，分别计算一遍即可；
* $n\ge 3$，$b=\{0, 0\cdots 0\}$ ，计算一遍即可；
* $n$ 是偶数，$b=\{-1, -1\cdots -1, n\}$ ，先计算全为 $-1$ 时的答案然后依次将每个数换成 $n$ 取最小即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int NR = 4e5 + 5;

int T, n, a[NR];

inline void solve() {
    cin >> n; int m = 2 * n;
    for (int i = 1; i <= m; ++i) cin >> a[i];
    // all same
    int ans = 1e18;
    if (n == 1) {
        ans = abs(a[1] - a[2]);
    }
    if (n == 2) {
        int tmp = 0;
        for (int i = 1; i <= m; ++i) tmp += abs(a[i]);
        ans = min(ans, tmp);
        tmp = 0;
        for (int i = 1; i <= m; ++i) tmp += abs(a[i] - 2);
        ans = min(ans, tmp);
    }
    if (n >= 3) {
        int tmp = 0;
        for (int i = 1; i <= m; ++i) tmp += abs(a[i]);
        ans = tmp;
    }
    // -1 -1 -1 ... -1 -1 n
    if (n % 2 == 0) {
        int tmp = 0;
        for (int i = 1; i <= m; ++i) tmp += abs(a[i] + 1);
        for (int i = 1; i <= m; ++i) {
            int tmpp = tmp - abs(a[i] + 1) + abs(a[i] - n);
            ans = min(ans, tmpp);
        }
    }
    cout << ans << '\n';
}

signed main() {
    cin >> T;
    while (T --) solve();
    return 0;
}
```



---

## 作者：free_fall (赞：0)

# 题目大意
给定好的数组和距离的定义，求距离之和最小的好的数组。
# 思路
很容易想到，当 $n=1$ 时，只需构造一个两个数字相同的数组（这个数组必定为好数组），当这两个相同的数在给定的数组中的两个数之间时，距离之和最小，故答案为 $a_2-a_1$ （$a_2$ 大于 $a_1$）。

注意：当 $n=2$ 时，有一个特殊情况，可以构造一个全为 $2$ 的数组，它一定是一个好数组（因为 $2 \times 2=2+2$）。

接下来可以打表寻找规律，首先，数组中所有的数全为 $0$ 时一定为好数组。其次，当 $n$ 是偶数时，可以证明前 $2n-1$ 个数为 $-1$，第 $2n$ 个数为 $n$ 的数组一定为好的数组。

因此将原数组排序，根据 $n$ 来判断构造数组。
# 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int T,n,a[N<<1],ans;
signed main(){
	scanf("%lld",&T);
	while(T--){
		ans=0x3f3f3f3f3f3f3f3f;
		scanf("%lld",&n);
		for(int i=1;i<=n*2;i++){
			scanf("%lld",&a[i]);
		}
		sort(a+1,a+n*2+1);
		if(n==1){
			printf("%lld\n",a[2]-a[1]);
			continue;
		}
		if(n==2){
			int sum=0;
			for(int i=1;i<=n*2;i++){
				sum+=abs(2-a[i]);
			}
			ans=min(ans,sum);
		}
		if(n%2==0){
			int sum=0;
			for(int i=1;i<=n*2-1;i++){
				sum+=abs(-1-a[i]);
			}
			sum+=abs(n-a[n*2]);
			ans=min(sum,ans);
		}
		int sum=0;
		for(int i=1;i<=n*2;i++){
			sum+=abs(0-a[i]);
		}
		ans=min(sum,ans);
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

