# Jury Meeting

## 题目描述

$ n $ people gathered to hold a jury meeting of the upcoming competition, the $ i $ -th member of the jury came up with $ a_i $ tasks, which they want to share with each other.

First, the jury decides on the order which they will follow while describing the tasks. Let that be a permutation $ p $ of numbers from $ 1 $ to $ n $ (an array of size $ n $ where each integer from $ 1 $ to $ n $ occurs exactly once).

Then the discussion goes as follows:

- If a jury member $ p_1 $ has some tasks left to tell, then they tell one task to others. Otherwise, they are skipped.
- If a jury member $ p_2 $ has some tasks left to tell, then they tell one task to others. Otherwise, they are skipped.
- ...
- If a jury member $ p_n $ has some tasks left to tell, then they tell one task to others. Otherwise, they are skipped.
- If there are still members with tasks left, then the process repeats from the start. Otherwise, the discussion ends.

A permutation $ p $ is nice if none of the jury members tell two or more of their own tasks in a row.

Count the number of nice permutations. The answer may be really large, so print it modulo $ 998\,244\,353 $ .

## 说明/提示

Explanation of the first test case from the example:

There are two possible permutations, $ p = [1, 2] $ and $ p = [2, 1] $ . For $ p = [1, 2] $ , the process is the following:

1. the first jury member tells a task;
2. the second jury member tells a task;
3. the first jury member doesn't have any tasks left to tell, so they are skipped;
4. the second jury member tells a task.

So, the second jury member has told two tasks in a row (in succession), so the permutation is not nice.

For $ p = [2, 1] $ , the process is the following:

1. the second jury member tells a task;
2. the first jury member tells a task;
3. the second jury member tells a task.

So, this permutation is nice.

## 样例 #1

### 输入

```
4
2
1 2
3
5 5 5
4
1 3 3 7
6
3 4 2 1 3 3```

### 输出

```
1
6
0
540```

# 题解

## 作者：XL4453 (赞：9)

### 解题思路：

数学题。

如果最大的数有不止一个，那么无论怎么排列都是合法的，直接输出 $n!$ 即可。

否则如果最大的比次大的大至少二，那么无论怎么排列都不可能合法，直接输出 $0$。

这两种都比较显然，需要思考的是最大的数只有一个而次大的仅比最大的数小一的情况。

---
首先发现这里其他的数放在那里都没有影响，所以直接考虑最大的和次大的两种数就可以了。

如果最大的那一个放在了最后一个，当倒数第二轮循环结束时最大的数还剩下一，且是最后一个取的，那么在下一次循环的时候这个最大的数就又被取了一次，导致不合法。

否则的话在倒数第二轮的时候虽然最大的数还剩下一，但此时最后一个取到的是某一个次大的数，是合法的。

所以说方案数其实就是不把最大的一个数放在所有的次大的数后面的方案数。

---
然后考虑如何求这样的一个方案数。

统计次大的数的数量，假设其为 $cnt$。这 $cnt$ 个数中一共有 $cnt+1$ 个空位，其中 $cnt$ 个是合法的，那么总方案数就是 $\dfrac{n!\times cnt}{cnt+1}$


---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long T,n,a[200005],cnt;
long long ans,MOD=998244353;
void work(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	scanf("%lld",&a[i]);
	sort(a+1,a+n+1);
	ans=1;
	if(a[n]==a[n-1]){
		for(long long i=1;i<=n;i++)ans=ans*i%MOD;
		printf("%lld\n",ans);
		return;
	}
	if(a[n]-a[n-1]>1){
		printf("0\n");
		return;
	}
	cnt=1;
	for(int i=n-2;i>=1;i--){
		if(a[i]!=a[i+1])break;
		cnt++;
	}
	for(long long i=1;i<=n;i++)
	if(i!=cnt+1)ans=ans*i%MOD;
	else ans=ans*(i-1)%MOD;
	printf("%lld\n",ans);
}
int main(){
	scanf("%d",&T);
	while(T--){
		work();
	}
	return 0;
}
```


---

## 作者：SSerxhs (赞：6)

可以注意到，答案只会和最大的两个数有关（因为到后面的轮次时只会剩下这两个数）。设最大为 $a$，出现了 $A$ 次；次大为 $b$，出现了 $B$ 次。

当 $a\ge b+2$ 时，手动模拟可以发现是无解的；

当 $A\ge 2$ 时，同样可以发现任意排列都是合法的；

比较麻烦的是 $a=b+1$ 的情况，注意此时 $A=1$。条件等价于至少有一个 $b$ 放在 $a$ 的后面。从概率角度考虑，在全排列的情况下只考虑 $a,b$，那么 $a$ 不放在最后的概率是 $\frac B{B+1}$。因此答案为 $n!\frac B{B+1}$。

---

## 作者：Cht_master (赞：2)

- 题意简述：给定序列 $a1,a2...a_n$，你可以将数列任意排列。每轮游戏会将整个序列中的非 0 元素减 1，直到整个序列为空时停止。例如 $[1,2]$，第一轮后变为 $[0,1]$，被减的数的位置序列是 $[1,2]$；第二轮后变为 $[0,0]$，被减的数的位置序列是 $[1,2,2]$——其中有连续的两个 2。现在希望求使位置序列中不出现连续相同的数的序列 $a$ 的排列方案数。答案对 $998244353$ 取模。

- 数据范围：$T(1\le T\le 10^4),2\le n\le 2\cdot 10^5,1\le a\le 10^9$

- 题目解析：

  - 记 $mx,mx'$ 分别为最大值，次大值；$cnt(x)$ 为等于 $x$ 的数的个数。

  - 容易分为如下 3 种情况讨论：

    1. $cnt(mx)>1$

       - 直接将 $a$ 全排列即可。

    2. $mx-mx'>1$

       - 显然无解。

    3. $cnt(mx)=1$ 且 $mx-mx'\le1$

       - 考虑计算不合法的方案数。此时一种排列不合法，当且仅当所有 $mx'$ 都在 $mx$ 的左边。对于 $mx$ 在位置 $i$ 时，$mx'$ 在左侧的方案数为 $C(i-1,cnt(mx'))\cdot cnt(mx')!$，剩下的数可以直接全排列。则不合法的方案总数为：
         $$
         sum=\sum_{i=cnt(mx')+1}^n C(i-1,cnt(mx'))\cdot cnt(mx')!\cdot cnt(n-cnt(mx')-1)!
         $$
         则 $n!-sum$ 即为所求。

       - 组合数的递推根据
         $$
        \left\{
        \begin{aligned}
        C(n,m)=\dfrac{n-m+1}{m}\cdot C(n,m-1)\\
        C(n,m)=C(n-1,m-1)+C(n-1,m)\\
        \end{aligned}
        \right.\\
        \Longrightarrow C(n+1,m)=(\dfrac{n+1}{n-m+1})\cdot C(n,m)
        $$
        
         所以需要预处理出 $[0,n]$ 在模 $998244353$ 意义下的阶乘以及 $[1,n]$ 关于 $998244353$ 的逆元。

- Code：

  ```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod(998244353);
const int mxN(2e5);
ll n,p[mxN+5],fac[mxN+5],inv[mxN+5];
void init(){
		fac[0]=1;for(ll i(1);i<=mxN;++i)fac[i]=fac[i-1]*i%mod;
		inv[1]=1;for(ll i(2);i<=mxN;++i)inv[i]=(1ll)*(mod-mod/i)*inv[mod%i]%mod;
}
int main(){
		init();
		int T;scanf("%d",&T);
		while(T--){
			scanf("%lld",&n);
			ll mx(0),mxx(0),cntmx(0),cntmxx(0),ans(0);
			for(int i(1);i<=n;++i)scanf("%lld",&p[i]),mx=max(mx,p[i]);
			for(int i(1);i<=n;++i)if(p[i]==mx)++cntmx;
			if(cntmx>=2){printf("%lld\n",fac[n]);continue;}
			for(int i(1);i<=n;++i)if(p[i]>mxx&&p[i]!=mx)mxx=p[i];
			if(mx-mxx>1){printf("0\n");continue;}
			//此时最大值一定只有一个.
			for(int i(1);i<=n;++i)if(p[i]==mxx)++cntmxx;
			ll C1(1),C2;
			for(ll i(cntmxx+1);i<=n;++i)
				ans=(ans+C1*fac[cntmxx]%mod*fac[n-1-cntmxx]%mod)%mod,
				C2=C1*cntmxx%mod*inv[i-cntmxx]%mod,C1=(C1+C2)%mod;
			printf("%lld\n",(fac[n]-ans+mod)%mod);
		}
		return 0;
}
  
  ```

  

---

## 作者：NiLu (赞：1)

## 分析
- 注意，如果至少有两个成员具有 $a_i$ 的最大值，那么任何排列都是好的。
- 现在我们考虑只有一个最大值的情况。我们来看看什么时候排列合适。设 $x$ 为任务数最多的评审团成员的索引。然后，在第一轮的讨论中，他们将是唯一一个告诉自己任务的人，因为评审团的其他成员已经告诉了他们所有的任务。所以在第 $(a_x-1)$ 一轮讨论中，应该有一位陪审员在第 $x$ 位陪审员之后告诉一个任务。
- 设k是数组 $a = a_x-1$ 中元素的个数。然后，如果 $k$ 个陪审员中至少有一个在排列中追随陪审员 $x$ ，那么排列就很好。利用这个，我们将计算坏排列的数量。我们把不等于 $a_x$ 或 $a_x-1$ 的元素固定下来，有 $n-k-1$ 个，那么方法的数量是 $n!/(k+1)!$ 它仍然是放置 $k+1$ 个元素，使最大值在它们的最后一个位置，有k!这样的方式。错误排列的总数是 $n!/(k+1)$ 。所以答案是 $n!-n!/(k+1)$。


---

## 作者：int1 (赞：1)

设最大值为 $mx$，个数为 $cm$，严格次大值为 $se$，个数为 $cs$ ，可以证明答案一定只与这些量有关。

首先处理一些特殊情况：

- $cm > 1$，任何排列方式均可，答案为 $n!$；
- $cm = 1, mx - se > 1$，任何排列方式均不合法，答案为 $0$。

现在就只剩下了 $cm = 1, mx - se = 1$ 的情况。

注意到一个排列方式合法的充要条件是至少存在一个 $se$ 在 $mx$ 后面。

“至少”的条件要是直接处理的话需要奇怪的容斥，不是很好办，因此考虑用总方案数减去不合法方案数，即所有的 $se$ 都在 $mx$ 前的情况。

这样，就是先在序列中选出 $cs + 1$ 个空位，把所有的 $se$ 和 $mx$ 放到里头，然后剩下的 $n - cs - 1$ 个 $< se$ 的数可以任意排列，所有的 $se$ 也可以任意排列，故总的答案为：

$$n! - \dbinom{n}{cs + 1}(n - cs - 1)!(cs)!$$

---

## 作者：Maysoul (赞：0)

## 简述思路：

如果一个人一直说个没完，这种情况只会在别人都说完了时候发生。只要有另外一个人没说完，那么就不会出现说个没完的状况，因此我们容易发现，这道题只和 $a_{i}$ 最大的两个人有关。

如果这两个人的 $a_{i}$ 相等，你说一句我说一句，到最后两个人同时说完，皆大欢喜。此时无论怎么排列都一定是可行的，所以结果就是这个排列的全排列 $n!$。

我们发现，无论怎么调换顺序，这两个人的所演讲的个数差都会不会超过 1，所以如果最大值比次大值高出 1 以上，我们认为无论怎么排列，这个人都会说个没完。

那么我们重点研究的对象，就是两者之差等于一的时候，在这个时候，最大值必须要在所有次大值之后，所以我们先统计出所有次大值的数量记为 $res$，那么最终答案就是 $n!\tfrac{res}{res+1} $。

## AC CODE:

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int MAXN=1e6+10;
const int MOD=998244353;
int num,ans=1;
int mx,mcnt,a[MAXN];
int jie(int n)
{
	int res=1;
	for (int i=1;i<=n;i++) res=(res*i)%MOD;
	return res;
}
signed main()
{
	int t,n;
	cin>>t;
	while(t--){
		int res=0,ans=1;
		cin>>n;
		for (int i=1;i<=n;i++) cin>>a[i];
		sort(a+1,a+1+n);
		if(a[n]==a[n-1]){
			cout<<jie(n)<<endl;
			continue;
		}
		if(a[n]-a[n-1]>=2){
			cout<<"0"<<endl;
			continue;
		}
		int goal=a[n-1];
		for (int i=n-1;i>=1;i--){
			if(a[i]==goal) res++;
		}
		for (int i=1;i<=n;i++){
			if(i!=res+1) ans=(ans*i)%MOD;
			else ans=(ans*(i-1))%MOD; 
		}
		cout<<ans<<endl;
	}
	return 0;
}

```


---

## 作者：CRTL_xzh2009 (赞：0)

设问题数最大值为 $mx$，次大值为 $nextmx$，次大值数目为 $num$，满足条件答案数 $ans$。

提供一种不用逆元的思路。

对于 $mx$ 只有一个，且 $mx-nextmx=1$，合法的方案数，至少要有一个次大值在最大值的右边，设 $x$ 是次大值的个数，则 $ans=n! \times \dfrac{x}{x+1}$。

考虑 $x$ 个 $nextmx$ 和 $1$ 个 $mx$，共 $x+1$ 个最大和次大值。

$n!$ 种排列中任意一种排列，总能找到 $(x+1)!$ 个排列，仅有最大和次大值排列不同。这 $(x+1)!$ 个排列中有 $x!$ 个非法方案（最大值在所有次大值的右边），即每 $x+1$ 中有 $1$ 个非法方案，那么每 $x+1$ 中有 $x$ 个是合法方案。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=2e5+5;
const ll mod=998244353;
int T,n,a[N];
int main(){
	for(cin>>T;T;T--){
		cin>>n;
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		int mx=0,mmx=0;
		for(int i=1;i<=n;i++){
			if(a[i]>mx)mmx=mx,mx=a[i];
			else if(a[i]>mmx)mmx=a[i];
		}
		if(mx>=mmx+2){
			puts("0");continue;
		}
		if(mx==mmx){
			ll ans=1;
			for(int i=1;i<=n;i++)
				ans=1ll*ans*i%mod;
			printf("%lld\n",ans);
			continue;
		}
		sort(a+1,a+n+1);
		int cnt=0;
		for(int i=n-2;i>=1&&a[i]==a[i+1];i--,cnt++);
		ll ans=1;
		for(int i=1;i<=n;i++){
			int tmp=i;
			if(i-2==cnt)tmp--;
			ans=1ll*ans*tmp%mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}

```


---

## 作者：lilong (赞：0)

这题是个分类讨论题。

要使得没有人连续两次提议，关键在于最大值和次大值。

因此分三类情况。

记最大值为 $a$，出现次数 $cnta$，次大值 $b$，出现次数 $cntb$。

- $cnta \ge 2$

最大值不止一个，说明有多个人会同时在第 $a$ 轮结束，因此无论任何情况都不会有人连续两次提议。任何顺序均可，因此答案为 $n!$。

- $a-b \ge 2$

在进行了 $b$ 轮后，$a$ 还剩多于一个提议，但已经没有其他人了，因此不得不连续两次提议，不符合要求，因此答案为 $0$。

- $a-b = 1$

不难发现，只有当 $a$ 在所有次大值的右边的时候，才不得不连续两次提议。因此，原来 $a$ 的位置有 $cntb+1$ 个选择，现在剩下 $cntb$ 个，因此求完 $n!$ 后要乘 $\dfrac{cntb}{cntb+1}$。答案为 $\dfrac{n! \times cntb}{cntb+1}$。

代码实现如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define int long long
#define MOD 998244353

using namespace std;
int n,a[1000001],ans,cnt;
signed main()
{
	int T;
	cin >> T;
	while( T-- )
	{
		ans = 1,cnt = 1;
		cin >> n;
		for( int i = 1 ; i <= n ; i++ )
			cin >> a[i];
		sort( a + 1 , a + n + 1);
		if ( a[n] - a[n-1] >= 2) cout << 0 <<endl;
		else if ( a[n] == a[n-1] )
		{
			for( int i = 1 ; i <= n ; i++ ) 
				ans = ans * i % MOD;
			cout << ans << endl;
		}
		else
		{
			int i;
			for( i = n - 1 ; i >= 1 && a[i] == a[i-1]; i-- );
			i = n - i;
			for( int j = 1 ; j <= n ; j++)
				if( j != i + 1) ans = ans * j % MOD;
			cout << ans * i % MOD << endl;
		}
	}
}
```


---

