# [SNCPC2019] Digit Product

## 题目描述

定义正整数 $x$ 的 "数字乘积" $f(x)$ 为其所有数字的乘积。例如，$f(1234) = 1 \times 2 \times 3 \times 4 = 24$，$f(100) = 1 \times 0 \times 0 = 0$。

给定两个整数 $l$ 和 $r$，请计算以下值：
$$(\prod_{i=l}^r f(i)) \mod (10^9+7)$$ 
如果你不知道 $\prod$ 表示什么，上述表达式等同于 
$$(f(l) \times f(l+1) \times \dots \times f(r)) \mod (10^9+7)$$

## 样例 #1

### 输入

```
2
1 9
97 99
```

### 输出

```
362880
367416
```

# 题解

## 作者：Jasoncwx (赞：9)

## 题目思路
不难发现，只要 $[l,r]$ 中出现至少一个整十数，也就是存在至少一个 $l\le i\le r$，使得 $i\bmod10=0$，这样 $f(i)$ 的最终结果肯定为 $0$，导致了 $\prod_{i=l}^r f(i)$ 也会为 $0$。

那我们在什么情况下输出 $0$ 呢？

可以证明，在 $r-l+1\ge10$ 的情况下，至少会出现一个整十数。因为要使得一个区间内没有整十数，这个区间内不能多于 $9$ 个数。

顾名思义，"整十数"就是每隔 $10$ 个整数会出现一次，所以我们要避免这种情况就只能不多于 $9$ 个数了。

所以在 $r-l+1\ge10$ 时直接输出 $0$，其它情况直接暴力枚举即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
long long f(int n){
    string s=to_string(n);
    long long sum=1;
    for(int i=0;i<s.size();i++)sum*=s[i]-'0';
    return sum;
}//计算 f(n)
int main(){
    int t;
    cin>>t;
    while(t--){
        int l,r;cin>>l>>r;
        if(r-l+1>=10)puts("0");//区间中出现整十数
        else{
            long long sum=1;
            for(int i=l;i<=r;i++){
                sum=(sum*f(i))%mod;//答案
            }
            cout<<sum<<endl;
        }
    }
}
```

---

## 作者：tiger2008 (赞：4)

这道题应该是这场比赛最简单的题了吧。

因为这道题求的是一个乘积，所以说只要在运算中出现了一个 $0$，最终的答案就一定是 $0$。

所以这道题就直接暴力并判断一下是否出现了 $0$ 就可以了。

### Code

```cpp
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int mod=1000000007;
int T;
signed main(){
	cin>>T;
	while(T--){
		int l,r;
		cin>>l>>r;
		int ans=1;
		for(int i=l;i<=r;i++){
			int tmp=i;
			while(tmp){
				ans=ans*(tmp%10)%mod;
				tmp/=10;
			}
			if(ans==0)break;
		}
		cout<<ans<<"\n";
	}
	return 0;
}

```


---

## 作者：Dws_t7760 (赞：2)

我们定义一个变量 $s$ 用于记录答案，对于所有在 $l$ 和 $r$ 之间的整数 $i$，我们将 $s$ 乘以 $i$ 的每一位上的数字并取模，但是如果在任意时刻，$s$ 的值变为 $0$，我们可以直接跳出循环并输出 $s$ 的值，因为在这种情况下 $s$ 的值一定为 $0$，没必要继续循环下去了，可以节省运行时间。

AC 代码：

```cpp
#include<iostream>
using namespace std;
long long n,l,r,s,st,t,mod=1e9+7;
int main() {
	cin>>n;
	for(int i=0;i<n;i++) {
		cin>>l>>r,s=1;
		for(int j=l;j<=r&&s;j++) {
			t=j;
			while(t&&s) s*=(t%10),s%=mod,t/=10;
		}
		cout<<s<<'\n';
	}
	return 0;
}
```

---

## 作者：Teto_etf (赞：0)

题目看起来计算量十分大。但容易知道，当区间内有任何一个数为 $0$ 时，答案为 $0$。

接下来用我们的脑子想一下，可以发现每 $10$ 个数中存在一个个位为 $0$ 的数，也就是能被 $10$ 整除的数。我们可以直接判断 $l$ 和 $r$ 的首位那么我们直接算到这个数就输出就可以了。

```cpp
#include <bits/stdc++.h>
using namespace std;

int t;
long long l, r, t1, t2;
long long tot = 1;
const int mod = 1e9 + 7;

int main() {
	cin >> t;
	while (t--) {
		cin >> l >> r;
		if (l / 10 != r / 10) { // 如果 l 和 r 的第一位不一样，那么说明 [l,r] 区间的长度肯定是超过 10 了
        tot = 1, cout << "0" << endl;
        continue;
      }
		if (l / 10 == r / 10) { // 否则
			tot = 1;
			t1 = l / 10, t2 = 1;
			if (t1) {
				while (t1 / 10) t2 *= t1 % 10, t1 /= 10;
				t2 *= t1;
			}
			for (long long i = l; i <= r; i++) tot = tot * t2 % mod * (i % 10) % mod;
			cout << tot << endl;
		}
	}
	return 0;
}
```

---

## 作者：luan341502 (赞：0)

显然是签到题。

我们发现如果有一个数中含有数位 $0$，那么答案就是 $0$，所以如果区间中包含末尾是 $0$ 的数，答案就为 $0$。其余情况区间长度一定小于 $10$,暴力即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int main(){
	int t;
	cin>>t;
	while(t--){
		int l,r;
		cin>>l>>r;
		if(l/10!=r/10||l%10==0) puts("0");
		else{
			long long ans=1;
			for(int i=l;i<=r;i++){
				for(int j=i;j;j/=10){
					ans=ans*(j%10)%mod;
				}
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
```


---

## 作者：SDLTF_凌亭风 (赞：0)

来自某位不愿意透露姓名的队友。

---
签到题。

首先我们知道，如果一个数中有 $0$ 那么答案显然是 $0$。同时，每 $10$ 个连续的数中一定存在一个个位为 $0$ 的数，所以直接暴力就好了，算到 $0$ 的时候退出循环。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=3e5+51,MOD=1e9+7;
ll test,l,r,res;
inline ll read()
{
	register ll num=0,neg=1;
	register char ch=getchar();
	while(!isdigit(ch)&&ch!='-')
	{
		ch=getchar();
	}
	if(ch=='-')
	{
		neg=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		num=(num<<3)+(num<<1)+(ch-'0');
		ch=getchar();		
	}
	return num*neg;
}
inline ll calc(ll x)
{
	ll res=1;
	while(x)
	{
		res=(li)res*(x%10)%MOD,x/=10;
	}
	return res;
}
inline void solve()
{
	l=read(),r=read(),res=1;
	for(register int i=l;i<=r;i++)
	{
		res=(li)res*calc(i)%MOD;
		if(res==0)
		{
			return (void)(puts("0"));	
		}	
	} 
	printf("%d\n",res);
}
int main()
{
	test=read();
	for(register int i=1;i<=test;i++)
	{
		solve();
	}
}
```



---

## 作者：skyskyCCC (赞：0)

## 前言。
一道基础的模拟题，稍加分析即可做出。
## 分析。
题意：将从 $l$ 到 $r$ 的区间内的每一个数的每位上的数相乘，求最终结果。

首先，很容易想到，因为 $0$ 乘任何数都得 $0$ 的情况存在，所以只要有一个数字的某一位是 $0$ 则最终答案一定为 $0$。 

当 $r-l \geqslant 10$ 时，其中必然存在至少一个数，其中一位为 $0$ 所以特判即可。

然后现在就只剩下 $r-l<10$ 的情况了，直接拆分各个数位，然后相乘即可。

代码如下，仅供参考：
```
#include<iostream>
const int mod=1e9+7;
using namespace std;
int t;
long long l,r;
long long fenj(long long x){
	long long res=1;
	while(x){
		res*=x%10%mod;
		x/=10;
	}
	return res%mod;
}
int main(){
	cin>>t;
	while(t--){
		cin>>l>>r;
		if(l/10!=r/10){
			cout<<"0\n";
		}
		else{
			long long ans=1;
			for (int i=l;i<=r;i++){
				ans=ans*fenj(i)%mod;
			}
			cout<<ans%mod<<"\n";
		}
	}
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：myyyIisq2R (赞：0)

## [P9651 SNCPC2019 Digit Product](https://www.luogu.com.cn/problem/P9651)

### Solution
用 $\text{string}$ 保存每一个枚举的 $\text{l}$ 到 $\text{r}$ 之间的整数，逐位相乘，不断取模即可得到最终答案。

注意当 $\text{l}$ 到 $\text{r}$ 的距离大于等于 $\text{l0}$ 时，即可直接输出 $\text{0}$，因为这其中至少有一个数位上的数字是 $\text{0}$，乘积必然为 $\text{0}$，因此我们最多只需要计算 $\text{81}$ 次，可以通过此题。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD =1e9+7;
int divi(int x)
{
	int ans{1};
	string s = to_string(x);
	for(int i{};i<s.length();i++)
	{
		ans *= s[i]-'0';
		ans %=MOD;
	}
	return ans;
}
signed main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int l,r;
		cin>>l>>r;
		if(r-l>=10) 
		{
			cout<<0<<endl;
			continue;
		}
		int ans{1};
		for(int i{l};i<=r;i++)
		{
			ans*= divi(i);
			ans%=MOD;
		}
		cout<<ans<<endl;
	}
	
 } 
```

---

## 作者：lemon_qwq (赞：0)

签到题。

因为 $0$ 乘任何数都是 $0$，所以 $l\sim r$ 只要有一个数字的一个数位是 $0$，那么最终答案就一定是 $0$。

考虑最坏情况，每 $10$ 个数个位一定会出现一个 $0$，所以如果 $r-l\geq 10$，结果就一定是 $0$。

剩下的情况计算量就很少了，直接暴力拆分数位即可。

赛时代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define mode 1000000007
using namespace std;
int T;
int a,b,anss,c,d,ans;
int sw(int a){
	c=1;
	d=0;
	while(1){
		if(a/c!=0){
			c*=10;
			d++;
		}else{
			return d;
		}
	}
}
int sw2(int a){
	c=1;
	d=0;
	while(1){
		if(a/c!=0){
			c*=10;
			d++;
		}else{
			return c/10;
		}
	}
}
int f(int x){
	ans=1;
	int a[10];
	int a1=sw(x),a2=sw2(x),a3=a1;
	while(a1--){
		a[a1]=(x%(a2*10)/a2)%mode;
		a2/=10;
	}
	for(int i=0;i<a3;i++){
		ans*=a[i];
		ans%=mode;
//		cout<<a[i]<<" ";
	}
	return ans%mode;
}
main(){
//	while(1){
//		cin>>a;
//		f(a);
//		cout<<sw(a)<<" "<<sw2(a)<<" "<<f(a);
//	}
	cin>>T;
	while(T--){
		cin>>a>>b;
		if(b-a<10){
			anss=1;
			for(int i=a;i<=b;i++){
				anss*=f(i);
				anss%=mode;
			}
			cout<<anss%mode<<endl;
		}else{
			cout<<0<<endl;
		}
	}
	return 0;
}
```

赛时由于出了一点小差错，导致代码整体来说有点乱。

差错具体来说就是：

```cpp
anss*=f(i);
ans%=mode;
```

没想到是取模取错数了，调了半个小时，希望大家引以为戒吧。

完结撒花！

---

