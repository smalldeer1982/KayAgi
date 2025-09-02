# Vasilije in Cacak

## 题目描述

Aca and Milovan, two fellow competitive programmers, decided to give Vasilije a problem to test his skills.

Vasilije is given three positive integers: $ n $ , $ k $ , and $ x $ , and he has to determine if he can choose $ k $ distinct integers between $ 1 $ and $ n $ , such that their sum is equal to $ x $ .

Since Vasilije is now in the weirdest city in Serbia where Aca and Milovan live, Cacak, the problem seems weird to him. So he needs your help with this problem.

## 说明/提示

In the first test case $ n = 5,\ k=3,\ x=10 $ , so we can choose the numbers: $ 2 $ , $ 3 $ , $ 5 $ , whose sum is $ 10 $ , so the answer is "YES".

In the second test case $ n = 5, \ k=3, \ x=3 $ , there is no three numbers which satisfies the condition, so the answer is "NO". It can be shown that there are no three numbers whose sum is $ 3 $ .

## 样例 #1

### 输入

```
12
5 3 10
5 3 3
10 10 55
6 5 20
2 1 26
187856 87856 2609202300
200000 190000 19000000000
28 5 2004
2 2 2006
9 6 40
47202 32455 613407217
185977 145541 15770805980```

### 输出

```
YES
NO
YES
YES
NO
NO
YES
NO
NO
NO
YES
YES```

# 题解

## 作者：Richard1211 (赞：12)

# 题意简述
每次给你三个数 $n,k,x$ 问从 $1$ 到 $n$ 中能否选出 $k$ 个不同的数使得他们的和为 $x$，如果可以输出 `Yes` 否则输出 `No`。

# 题目分析
我们直接大胆猜想，小心求证。赛时我直接通过观察样例发现了不合法情况的条件为  
$$x< \sum^k_{i=1}i\lor x>\sum^n_{i=n-k+1}$$  
然后我直接猜测除了不合法的条件以外其他条件都是合法的，然后过了这题。接下来我们考虑如何证明这个结论。  

我们考虑使用数学归纳法。假设 $x=\sum^k_{i=1}a_i$ 满足 $\forall i∈[1,k],a_i∈[1,n],a_i>a_{i-1}\And\forall i,j∈[1,k],a_i≠a_j$  
考虑证明 $x+1$ 可以被表示出来，容易发现 $\exists ind∈[1,n],a_{ind}\geq a_{ind-1}+2$，那么此时 $x+1=\sum^{ind-1}_{i=1}a_i+1+\sum^n_{j=ind}a_j$  

那么我们就证明了只要答案不是 `No` 就一定是 `Yes`。  

如果这时我们在程序中直接 for 循环进行加和，会导致 TLE。所以我们考虑使用高斯等差数列求和公式  
$$\sum^{end}_{i=begin}a_i=\frac{(a_{begin}+a_{end})(end-begin+1)}{2}$$  
那么我们只需要在  
$$x<\frac{k(k+1)}{2}\lor x>\frac{k(n+n-k+1)}{2}$$  
的时候输出 `No` 否则输出 `Yes` 即可，每次操作的复杂度是 $O(1)$ 的，于是时间复杂度为 $O(t)$，可以通过本题。  

具体实现可以参考代码。

# $Code$
```cpp
#define YES printf("YES\n")
#define Yes printf("Yes\n")
#define yes printf("yes\n")
#define NO printf("NO\n")
#define No printf("No\n")
#define no printf("no\n")
constexpr long long N=1000100;
long long t,n,k,x;
int main(){
    t=read();
    for(register int T=1;T<=t;++T){
        n=read();
        k=read();
        x=read();
        if(x<k*(k+1)/2||x>k*(n+n-k+1)/2){
            No;
        }
        else{
            Yes;
        }
    }
    return 0;
}

---

## 作者：cherry2010 (赞：6)

## CF1878C Vasilije in Cacak 题解

### 做题思路

看到 $x$ 的大小，立刻放弃暴力枚举……

先考虑一些显而易见的 `NO`：

> 如果最小的 $k$ 个数加起来仍然比 $x$ 大，无法凑出 $x$（情况 1）

> 如果最大的 $k$ 个数加起来仍然比 $x$ 小，无法凑出 $x$（情况 2）

想到剩下的数，如果先选 $1-k$，**那么肯定可以通过将其中某些数更新为更大的数来凑出** $x$。因为最极限的情况就是将全部 $1-k$ 都更换为 $(n-k+1)-n$，而这时 $k$ 个数的和是肯定大于等于 $x$ 的（情况 2 已经判断过了）。

总结一下，就是**除了上面两种情况为 `NO`，其余情况均为 `YES`。**

### 代码

```
#include <bits/stdc++.h>
using namespace std;
long long t,n,k,x;
int main() {
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%lld",&n,&k,&x);
		if(k*(1+k)/2>x)		//情况 1
		{
			printf("NO\n");
		}
		else if(k*(n-k+1+n)/2<x)	//情况 2
		{
			printf("NO\n");
		}
		else
		{
			printf("YES\n");
		}
	}
	
	return 0;
}
```

---

## 作者：wanghaoran00 (赞：2)

### 翻译
给定三个数 $n,k,x$ 从 $1$ 到 $n$ 中选不重复的 $k$ 个数使其和为 $x$，可以输出 YES，否则输出 NO。（多测）
### 思路
$k$ 个数之和最大时为 $n-k$ 到 $k$ 之和为 $\frac{(n-k+n+1)\times k}{2}$，最小时为 $1$ 到 $k$ 之和为 $\frac{(k+1)\times k}{2}$，如果大于最小值且小于最大值，可以通过将差值分到每一项中，在两极值中间都可以取到，使用求和公式计算即可。

ACcode
```
#include <bits/stdc++.h>
using namespace std;
long long n,k,x,t,minn,maxn;
int main(){
    cin>>t;
    while(t--){
        scanf("%lld%lld%lld",&n,&k,&x);
        maxn=(n-k+n+1)*k/2;
        minn=(1+k)*k/2;
        if(maxn>=x&&minn<=x||x==minn||x==maxn){
            printf("YES\n");
        }
        else{
            printf("NO\n");
        }
    }
	return 0;
}


```

---

## 作者：InversionShadow (赞：2)

我们只需要判断在 $1\sim n$ 选后 $k$ 个数的和大于 $x$ 和在 $1 \sim n$ 选前 $k$ 个数（$1 \sim k$）小于 $x$ 就可以啦！

因为你要让 $x$ 在 $1 \sim n$ 选 $k$ 个数的范围内，仅当 $\sum\limits_{i=1}^ki \le x \le \sum\limits_{n-k+1}^ni$。

但是你暴力去求会 $\texttt{TLE}$，然后你运用胎前教育可知高斯求和公式，然后就没了。

感性理解一下：

我们可以先设 $a_1=1,a_2=2\ldots a_k=k$，那么和就是 $\dfrac{(k+1) \times k}{2}$，我们将它设为 $r$，然后我们可以将 $a_k$ 不断更新为 $a_k+1$，设加上的和为 $pos$，那么显然 $r+pos \le \dfrac{k \times (n + (n - k + 1))}{2}$，$pos$ 也可以为 $0$，所以下限就是 $r$，所以 `YES` 的区间范围就是 $\dfrac{(k + 1) \times k}{2} \le x \le \dfrac{k \times (2 \times n - k + 1)}{2}$。
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int t, n, k, x;

void solve() {
	cin >> n >> k >> x;
	int sum = 0;
	// (末项 + 首项) * 项数 / 2
	sum = (long long)((n + n - k + 1) * k) / 2;
	int ans = 0;
	ans = (long long)((1 + k) * k) / 2;
//	for (int i = n - k + 1; i <= n; i++) {
//		sum += i;
//	}
//	int ans = 0;
//	for (int i = 1; i <= k; i++) {
//		ans += i;
//	}
	//cout << ans << ' ' << sum << endl; 
	if (ans > x || sum < x) {
		cout << "NO\n";
		return ;
	}
	cout << "YES\n";
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;	
}
```

---

## 作者：hzoi_Shadow (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1878C)

# 简化题意

有 $t$ 组询问，每次询问是否能从 $1 \sim n$ 中选择 $k$ 个数使得它们的和为 $x$。

# 解法

考虑临界情况，从 $1 \sim n$ 中选择最小的 $k$ 个数时和为 $\sum\limits_{i=1}^k i=\dfrac{(k+1)k}{2}$，从 $1 \sim n$ 中选择最大的 $k$ 个数时和为 $\sum\limits_{i=n-k+1}^n i=\dfrac{(n-k+1+n)k}{2}$。
  - 当 $x<\dfrac{(k+1)k}{2}$ 或 $x>\dfrac{(n-k+1+n)k}{2}$ 时一定无解，证明显然。
  - 当 $\dfrac{(k+1)k}{2} \le x \le \dfrac{(n-k+1+n)k}{2}$ 时一定有解，因为可以将 $x-\dfrac{(k+1)k}{2}$ 分给选出的 $k$ 个数。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define sort stable_sort 
#define endl '\n'
int main()
{
	ll t,i,n,k,x;
	cin>>t;
	for(i=1;i<=t;i++)
	{
		cin>>n>>k>>x;
		if((k+1)*k/2>x||(n-k+1+n)*k/2<x)
		{
			cout<<"NO"<<endl;
		}
		else
		{
			cout<<"YES"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：tbdsh (赞：0)

# 题意简述
[洛谷原题传送门](https://www.luogu.com.cn/problem/CF1878c)

[CodeForces 原题传送门](http://codeforces.com/problemset/problem/1878/c)

有 $t$ 组数据。每组数据给定 $n,k,x$。

请你判断能否在 $1\sim n$ 中**不重复的恰好**选出 $k$ 个数使得这 $k$ 的数的和为 $x$。

可以选出输出 `YES`，否则输出 `NO`。

# 分析
首先来分析一下选出 $k$ 个数的和的取值范围。

首先，选出 $k$ 的数的和最小值为 $(1+k)\times k\div 2$，最大值是 $(2\times n-k+1)\times k\div 2$。

给出结论：选出 $k$ 个数的和的取值范围 $p$ 为 $(1+k)\times k\div 2 \sim (2\times n-k+1)\times k\div 2$。

我们来感性理解这个结论。

我们可以这么选择：

首先令 $a_1=1,a_2=2,\dots,a_k=k$。此时取到最小值 $(1+k)\times k\div 2$。

我们不断让 $a_k$ 更新为 $a_k+1$，那么此时可以取到 $(1+k)\times k\div 2\sim (1+k)\times k\div 2 + n - k$。

然后让 $a_{k - 1}$ 不断更新为 $a_{i-1}+1$，此时可以取到 $(1+k)\times k\div 2 + n - k\sim(1+k)\times k\div 2 + 2\times n - 2\times k - 1$

以此类推，最后 $a$ 数组应该是 $a_1=n-k+1,a_2=n-k+2,\dots,a_{k-1}=n-1,a_k=n$。

此时取到最大值 $(2\times n-k+1)\times k\div 2$。

由于我们每一次都只给一个数加一，那么 $(1+k)\times k\div 2 \sim (2\times n-k+1)\times k\div 2$ 中的所有数就都是可以取到的。

那么我们就只需要判断 $x$ 是否满足 $(1+k)\times k\div 2 \le x\le  (2\times n-k+1)\times k\div 2$ 即可。

# Code
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;
const int MAXN = 2e5 + 5;
void Solve(){
  long long n, k, x;
  cin >> n >> k >> x;
  cout << ((1 + k) * k / 2 <= x && x <= k * (n + n - k + 1) / 2 ? "YES\n" : "NO\n");
}
signed main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while (t--){
    Solve();
  }
  return 0;
}
```

---

## 作者：zgy_123 (赞：0)

~~div 3 真简单啊~~

此题建议评橙。

首先根据题意及数据范围，可知单次询问时间复杂度在 $\log$ 及以下。思考可知应该是数学题。

首先，我们可以定义如下的函数：

$$\operatorname{sum}(l,r)=\sum_{i=l}^ri=\frac{(l+r)(r-l+1)}{2}$$

然后，根据直觉，对于任意的 $1\le len\le n$ 及 $1\le left\le n-len+1$，都有：

$$\operatorname{sum}(1,len)\le\operatorname{sum}(left,left+len-1)\le \operatorname{sum}(n-len+1,n)$$

即在题目中，如果满足，则：

$$\operatorname{sum}(1,k)\le x \le \operatorname{sum}(n-k+1,n)$$

所以直接判断有无解即可。总复杂度 $O(t)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll sum(ll l,ll r){
	return (l+r)*(r-l+1)/2;
}
int main(){
	int t;
	cin>>t;
	while(t--){
		ll n,k,x;
		cin>>n>>k>>x;
		if(x>=sum(1,k)&&x<=sum(n-k+1,n)) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}

```
---
- 注意开 `long long`
- CSP RP++!!!

---

## 作者：__JiCanDuck__ (赞：0)

# 闲话
啊！赛时过的！因为 B 挂了 $3$ 发，然后看 C 发现好简单......

# 翻译
多组数据，在 $1$ 至 $n$ 的数中，选择 $k$ 个，使和为 $x$ 是否可行。

# 思考

那么贪心考虑什么时候非法，如果最大的情况仍然小于 $x$，那永远没有满足。 如何找最大值呢？取最大的 $k$ 个。最小值也一样，取最小的 $k$ 个。如果最大值小了或者最小值大了，那一定不行了。不然一定可以， 因为可以贪心，比方说选大了，那就小一， 反之亦然。

使用幼儿园就会的求和公式，就可以写出 C。

# 代码

```cpp; 

int main() 
  int t;
  for (cin >> t; t; t--) {
    cin >> n >> k >> s;
    if ((n - k + 1 + n) * k / 2 < s || (1 + k) * k / 2 > s) cout << "No\n";
    else cout << "Yes\n";
  }
}
```

放主函数差不多了吧！

管理大人求过！！！

---

## 作者：phigy (赞：0)

我们会发现在 $1$ 至 $n$ 中取 $k$ 个数最小值为 $\dfrac{(k+1)k}{2}$ 最大值为 $\dfrac{(2n-k+1)k}{2}$。

然后我们会发现假如我们已经得到了 $1$ 至 $n$ 中取 $k$ 个数和为
 $x$ 的方案，我们现在研究 $x+1$ 是否也有方案。
 
我们可以将和为 $x$ 的取得数排序，尝试将数列中最大的那个比后面或 $n+1$ 小至少 $2$ 的数加上 $1$ 这样可以得到 $x+1$ 的方案。

而唯一不可行的情况就是不存在这样的一项，即和已经为最大值。

所以 $\dfrac{(k+1)k}{2}\leq x\leq \dfrac{(2n-k+1)k}{2}$ 的 $x$ 都可以取到。

```cpp
#include <iostream>

#define int long long

using namespace std;

int T;
int n,m,q;
int a[1000005];

signed main()
{
    int i,j,k;
    cin>>T;
    while(T--)
    {
        cin>>n>>m>>q;
        if(m*(m+1)/2<=q&&q<=(2*n-m+1)*m/2)
        {
            cout<<"YES"<<endl;
        }
        else
        {
            cout<<"NO"<<endl;
        }
    }
    return 0;
}

```


---

## 作者：Yun_Mengxi (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1878C)

## 题意

问是否在 $1\sim n$ 中选 $k$ 个数和能为 $x$。

## 分析

分析一下，最小肯定是 $1+2+\ldots+(k-1)+k$，最大肯定是 $(n-k+1)+(n-k+2)+\ldots+n$，对于式子套一下求和公式，最小是 $\dfrac{(1+k)\times k}{2}$，最大是 $\dfrac{(n+n-k+1)\times k}{2}$，然后判断一下 $x$ 是否在这个区间中就行了。

## 代码

```cpp
#include <bits/stdc++.h>

#define IOS ios::sync_with_stdio(0);\
cin.tie(0), cout.tie(0)

using namespace std;

const int kMaxN = 2e5 + 5;

int t;
long long n, k, x;

signed main() {
	IOS;
	cin >> t;
	while (t--) {
		cin >> n >> k >> x;
		if ((2ll * n - k + 1) * k / 2 < x || (1 + k) * k / 2 > x) {
			cout << "NO\n";
		} else {
			cout << "YES\n";
		}
	}
	return 0;
}

```

---

