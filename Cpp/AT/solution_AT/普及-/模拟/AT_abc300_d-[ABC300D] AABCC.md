# [ABC300D] AABCC

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc300/tasks/abc300_d

$ N $ 以下の正整数のうち、 $ a\ <\ b\ <\ c $ なる **素数** $ a,b,c $ を用いて $ a^2\ \times\ b\ \times\ c^2 $ と表せるものはいくつありますか?

## 说明/提示

### 制約

- $ N $ は $ 300\ \le\ N\ \le\ 10^{12} $ を満たす整数

### Sample Explanation 1

$ 1000 $ 以下で条件を満たす整数は以下の $ 3 $ つです。 - $ 300\ =\ 2^2\ \times\ 3\ \times\ 5^2 $ - $ 588\ =\ 2^2\ \times\ 3\ \times\ 7^2 $ - $ 980\ =\ 2^2\ \times\ 5\ \times\ 7^2 $

## 样例 #1

### 输入

```
1000```

### 输出

```
3```

## 样例 #2

### 输入

```
1000000000000```

### 输出

```
2817785```

# 题解

## 作者：code_hyx (赞：6)

我赛时想得太复杂了，可能很多人也想复杂了，其实这题就是个纯暴力。  
因为 $a<b<c$，所以 $a^5<a^2 \times b^3<a^2 \times b \times c^2$，那么只要暴力枚举 $a,b,c$，然后预处理素数表就行了，发现已经超过了就 $\text{break}$。  
每一层循环都不会超过 $O(n^{\frac{1}{5}})$，所以总的复杂度是 $O(n^{\frac{3}{5}})$，可以通过本题。  
代码：
```
#include<bits/stdc++.h>
using namespace std;
long long zs[20000005],flag[20000005];
long long n;
long long ans=0;
void getprime()
{
	for(long long i=2;i<=20000005;i++)
	{
		if(flag[i]==1)continue;
		zs[++zs[0]]=i;
		for(long long j=2;i*j<=20000005;j++)flag[i*j]=1;
	}
}
int main()
{
	getprime();
	cin>>n;
	for(long long i=1;i<=n;i++)
	{
		if(zs[i]*zs[i]*zs[i]*zs[i]*zs[i]>n)break;
		for(long long j=i+1;j<=n;j++)
		{
			if(zs[i]*zs[i]*zs[j]*zs[j]*zs[j]>n)break;
			for(long long k=j+1;k<=n;k++)
			{
				if(zs[i]*zs[i]*zs[j]*zs[k]*zs[k]>n)break;
				ans++;
			}
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：lzyqwq (赞：6)

**[更好的阅读体验](https://www.cnblogs.com/MnZnOIerLzy/articles/17364692.html)**

# $\texttt{Description}$

**[AtCoder 题目链接](https://atcoder.jp/contests/abc300/tasks/abc300_d "AtCoder 题目链接")**

> - 给定 $N$，求有多少个正整数 $x$ 满足：
>
>      - $1\le x\le N$。
>
>      - $x=a^2\times b\times c^2$，其中 $a,b,c\in \mathbb{P}$ 且 $a<b<c$。
>
> - $300\le N\le 10^{12}$。

# $\texttt{Solution}$

首先把 $x$ 写成 $(a\times c)^2\times b$，考虑枚举 $a\times c$。

于是枚举 $i\in[10,\lfloor\sqrt{N}\rfloor]$，考虑怎样的 $i$ 满足条件。

记 $num_i$ 为 $i$ 的质因数**集合**的大小，$tot_i$ 为 $i$ 的质因数**可重集**的大小。可以**线性筛预处理**。显然，需要满足 $num_i=2$ 且 $tot_i=2$。同时线性筛处理 $L_i,R_i$ 为 $i$ 的最小/最大质因数。考虑 $b$ 的范围，显然 $b\in\left[1,\left\lfloor\dfrac{N}{i^2}\right\rfloor\right]$ 且 $b\in(L_i,R_i)$，求出交集（无交跳过）。设最终得到 $b\in[p,q]$，再预处理一个 $s_i$ 表示 $1\sim i$ 中质数的个数，满足条件的 $b$ 的个数即为 $s_q-s_{p-1}$。

时间复杂度和空间复杂度均为 $\mathcal{O}(\sqrt{N})$。

# $\texttt{Code}$

**[Submission](https://atcoder.jp/contests/abc300/submissions/41056710 "Submission")**


```cpp
#include<bits/stdc++.h>
#define int long long
#define N 1000005
using namespace std;
int p[N],cnt,num[N],s[N],L[N],R[N],ans,tot[N];
bool is[N];
signed main(){
	memset(is,1,sizeof is);
	is[1]=0; 
	int n;
	cin>>n;
	for(int i=2;i*i<=n;++i){
		s[i]=s[i-1]+is[i];
		if(is[i]){
			tot[i]=num[i]=1;
			L[i]=R[i]=i;
			p[++cnt]=i;
		}
		for(int j=1;j<=cnt&&i*i*p[j]*p[j]<=n;++j){
			is[i*p[j]]=0;
			tot[i*p[j]]=tot[i]+1;
			if(i%p[j]){
				num[i*p[j]]=num[i]+1;
				L[i*p[j]]=p[j];
				R[i*p[j]]=R[i];
			}else{
				num[i*p[j]]=num[i];
				L[i*p[j]]=L[i];
				R[i*p[j]]=R[i];
				break;
			}
		}
	}
	for(int i=sqrt(n);i>=10;--i){
		if(num[i]!=2||tot[i]!=2){
			continue;
		}
		int k=n/(i*i);
		if(k<=L[i]){
			continue;
		}
		if(R[i]-L[i]<=1){
			continue;
		}
		ans+=s[min(k,R[i]-1)]-s[L[i]];
	}
	cout<<ans;
}
 ```

---

## 作者：DengDuck (赞：4)

观察样例，发现总答案是很少的，考虑优化枚举。

首先 $a,b,c$ 都是质数，由于 $a<b<c$，所以 $a^5\leq N$。

就算只满足 $c^2\leq N$，根据 $N\leq 10^{12}$，也可以确定 $c\leq 10^6$。

可以筛出小于 $10^6$ 的所有质数，只枚举质数。

其次，根据 $a<b<c$ ，我们不难根据 $a$ 写出一个判断函数，同理可以写出枚举两个量的判断函数，可参考代码。

我们快速知道了 $a,b$ 之后，可以写一个二分来找有多少个合法的 $c$。

毕竟质数的平方数组显然满足单调性。

这些优化加上后，时间复杂度在 $O(\sqrt{n}\log n)$ 左右。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=1e6;
LL n,tot[N+5],cnt;
int b[N+5];
bool pd(LL i)//a为第i个质数，判断后面是否还有解
{
	LL k=n;
	k/=tot[i]*tot[i];
	k/=tot[i+1];//a<b
	k/=tot[i+2]*tot[i+2];//b<c
	if(k>=1)return true;
	return false;
}
bool pd2(LL i,LL j)//a为第i个质数，b为第j个质数，判断后面是否还有解
{
	LL k=n;
	k/=tot[i]*tot[i];
	k/=tot[j];
	k/=tot[j+1]*tot[j+1];//b<c
	if(k>=1)return true;
	return false;
}
bool pd3(LL i,LL j,LL k)//三个量都知道，判断是否合法
{
	LL t=n;
	t/=tot[i]*tot[i];
	t/=tot[j];
	t/=tot[k]*tot[k];
	if(t>=1)return true;
	return false;
}
int main()
{
	cin>>n;
	for(int i=2;i<=N;i++)
	{
		if(!b[i])
		{
			tot[++tot[0]]=i;
			for(int j=2*i;j<=N;j+=i)b[j]=1;//筛法求质数
		}
	} 
	for(int i=1;i<=tot[0]&&pd(i);i++)//枚举a为第i个质数
	{
		for(int j=i+1;j<=tot[0]&&pd2(i,j);j++)//同理
		{
			LL l=j+1,r=tot[0],ans=0;
			LL L=j+1;
			while(l<=r)//二分求c的数量
			{
				LL mid=(l+r)/2;
				if(pd3(i,j,mid))
				{
					ans=mid;
					l=mid+1;
				}
				else r=mid-1;
			}
			if(ans>=L)
			{
				cnt+=ans-L+1;
			}
		}
	}
	cout<<cnt<<endl;
} 
```


---

## 作者：封禁用户 (赞：3)

## 分析

暴力枚举就行了。

我们先把质数筛出来，然后枚举 $a,b,c$。对于 $a\ <b\ <c$ 的条件，我们可以得知：若想满足 $a^2 × b × c^2 \le n$，则 $a^2 × a × a^2$ 一定也是小于等于 $n$ 的，所以在 $a^2 × a × a^2 \ >n$ 时，我们就没必要继续枚举 $a$ 了。$b,c$ 同理，最后在枚举满足要求的 $c$ 时，答案累加即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
int idx,pri[N];
bool vis[N];
void get_pri()//筛1~1e6之间的质数 
{
	vis[1]=1;
	for(int i=2;i<=N-10;i++)
	{
		if(!vis[i])
		{
			vis[i]=1;
			pri[++idx]=i;
			for(int j=2;pri[idx]*j<=N-10;j++)
				vis[pri[idx]*j]=1;
		}
	}
}
int check(int a,int b,int c){return (a*a)*(b)*(c*c);}//题目的公式 
int n;
int ans;//用来存答案 
signed main()
{
	cin>>n;
	get_pri();
	for(int a=1;a<=idx&&check(pri[a],pri[a],pri[a])<=n;a++)//不越界的前提下满足条件
		for(int b=a+1;b<=idx&&check(pri[a],pri[b],pri[b])<=n;b++)
			for(int c=b+1;c<=idx&&check(pri[a],pri[b],pri[c])<=n;c++)
				ans++; 
	return cout<<ans,0;
}
```


---

## 作者：_Z_F_R_ (赞：3)

### 题意
给定 $N$，求满足如下条件时，$a,b,c$ 可取值的方案数：

- $a < b < c$；
- $a,b,c$ 均为质数；
- $a^2bc^2 \leq n$。

### 思路
枚举量最少的方案，就是枚举 $a,c$，此时 $b$ 最小值为大于 $a$ 的最大的质数，最大值为小于等于 $\min(c-1,\dfrac{n}{a^2c^2})$ 最小的质数。

由于 $b$ 最大为 $\sqrt[3]\dfrac{n}{4}$（$a$ 最小为 $2$，最坏情况 $b=c-1$。因为 $a^2bc^2 \le n$，所以 $b$ 一定小于等于 $\sqrt[3]\dfrac{n}{4}$。实际 $b$ 最大值可能比此还小，但不可能再大了），又因为 $n \le 10^{12}$，所以 $\sqrt[3]\dfrac{n}{4} \le 5 \times 10^3 \times \sqrt[3]{2} \le 10^4$。

用欧氏筛（或埃氏筛）筛出 $2$ 到 $10^4$ 当中的质数，在定义 $dir_i$ 表示 $i$ 是从 $2$ 到 $10^4$ 中第几个质数。

定义数组 $pre$，$pre_i$ 表示 $2$ 到 $i$ 中，最大的质数的位置。所以，$b$ 最小值，大于 $a$ 的最大的质数，位置为 $dir_a+1$；$b$ 最大值，小于等于 $\min(c-1,\dfrac{n}{a^2c^2})$ 最小的质数，位置为 $\large pre_{{\lfloor {\min(c-1,{\frac{n}{a^2c^2}}})\rfloor}}$。

$\large ans \gets ans + (pre_{{\lfloor {\min(c-1,{\frac{n}{a^2c^2}}})\rfloor}} - dir_a)$ 即可。
### 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
 
ll n,a,b,c;
const int N = 1e6 + 5;
ll prime[N],st[N],pre[N],k = 0;
void Init(ll n)
{
    ll i,j;
    for(i = 2;i <= n;i++)
    {
        if(!st[i])
            prime[k++] = i;
        for(j = 0;prime[j] <= n / i;j++)
        {
            st[prime[j] * i] = true;
            if(i % prime[j] == 0)
                break;
        }
    }
    for(i = 0;i < k - 1;i++)
        for(j = prime[i];j < prime[i + 1];j++)
            pre[j] = i;
}
 
int main()
{
    Init((ll)(1e6));//c 可能会取到 10^6
    cin >> n;
    int i,j;
    ll ans = 0;
    for(i = 0;prime[i] <= n / prime[i];i++)//枚举 dir_a
    {
        a = prime[i];
        for(j = i + 2;prime[j] <= n / prime[i] / prime[i] / prime[j];j++)//枚举 dir_c
        {
            c = prime[j];
          	ll maxb = min(c-1,(ll)(n / a / a / c / c));//b 的最大值
            if(maxb <= a)
                break;
            ll maxbi = min((ll)(j - 1),pre[maxb]);//dir_maxb
            ans += maxbi - i;//ans 累加
        }
        if(j == i + 2)//说明第一次就 maxb<=a 了，i 再大下去，maxb 只会更小，不会更大，没有其他方案了
            break;
    }
    printf("%lld",ans);
}
```

---

## 作者：Xy_top (赞：2)

十分简单的暴力题（

首先把 $[1,1000000]$ 中的素数全部筛出来，然后枚举。

$a$ 的范围是 $[1,1000000]$，如果 $a^2> n$，``break``。

$b$ 的范围是 $[a + 1,1000000]$，如果 $a^2\cdot b>n$，``break``。

剩下的同理，可以几乎发现每一个枚举到的数都是合法的数，样例给了一组大的，答案为 $2817785$，所以运算次数在 $2817785$ 左右，显然能过，时间复杂度为 $O(\text{答案})$，最后别忘记开 ``long long``。

代码：

```cpp
#include <iostream>
#define int long long
using namespace std;
int n, cnt, ans;
int primes[1000001];
bool prime[1000001];
signed main () {
	cin >> n;
	for (int i = 2; i <= 1000000; i ++) {
		if (!prime[i]) primes[++ cnt] = i;
		for (int j = 1; j <= cnt && i * primes[j] <= 1000000; j ++) {
			prime[i * primes[j] ] = true;
			if (i % primes[j] == 0) break;
		}
	}
	for (int i = 1; i <= cnt - 2; i ++) {
		if (primes[i] > 251) break;
		for (int j = i + 1; j <= cnt - 1; j ++) {
			if (primes[i] * primes[j] * primes[j] * primes[j] > n) break;
			for (int k = j + 1; k <= cnt; k ++) {
				if (primes[i] * primes[i] * primes[j] * primes[k] * primes[k] <= n) {
					++ ans;
				} else break;
			}
		}
	}
	cout << ans;
	return 0;
}
```


---

## 作者：c20231020 (赞：1)

### 题目链接
[luogu](https://www.luogu.com.cn/problem/AT_abc300_d)

[atcoder](https://atcoder.jp/contests/abc300/tasks/abc300_d)

### 题目大意

有多少个不大于 $N$ 的正整数可以用三个质数 $a,b,c(a<b<c)$ 表示为 $a^2 \times b \times c^2$？

### 思路

我太菜了，直接枚举这个数或 $a,b,c$ 一起枚，（好像）复杂度都爆炸，又不会优化。

但是题面贴心地为我们准备了一组最大的大样例：in：`1000000000000` out：`2817785`。

可以发现，答案是线性的，可以一一枚举符合条件的数，即可以枚举 $a,b,c$。

于是，先枚举 $a$，再枚举 $c$（因为这两个的取值范围比 $b$ 小），最后枚举 $b$，顺便剪枝，计个数即可。因为 $a$ 之多会到 $\sqrt{n}$，于是还要把 $[1,\sqrt{n}]$ 内的质数筛出来。采用欧拉筛，不知道什么玄学复杂度。

---

其实还可以二分 $b$，这样枚举的复杂度应该会小一些，但是代码会长亿些，还是不用那么麻烦。

#### code

跑得飞快。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007
#define ll long long
#define For(i,a,b) for(ll i=(a);i<=(b);++i)
#define N 1000010
ll n,m,p[N],cnt,v[N],ans;
void solve(){
	cin>>n;m=sqrt(n);
	For(i,2,m){
		if(!v[i])p[++cnt]=i;
		for(ll j=1;j<=cnt&&i*p[j]<=m;++j){
			v[i*p[j]]=1;
			if(i%p[j]==0)break;
		}
	}
	For(i,1,cnt){
		For(j,i+2,cnt){
			if((__int128)p[i]*p[i]*p[j]*p[j]>n)break;//剪枝，注意四个 10^6 的数 long long 装不下，需要用 __int128 转一下
			For(k,i+1,j-1){
				if((__int128)p[i]*p[i]*p[j]*p[j]*p[k]>n)break;//剪枝，同上
				++ans;
			}
		}
	}//一定要有两个判断，不然会 T
	cout<<ans<<'\n';
	return;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t=1;
	while(t--)solve();
	return 0;
}
```

---

## 作者：small_john (赞：1)

## 分析

首先，题目中出现了 `质数`，先来一个质数筛。

我们知道，$a^2\times b\times c^2=n(a<b<c)$ 时，$a,c<\sqrt[5]{n}$，那么 $b$ 就是大于 $a$ 且小于 $c$ 的质数。用 $s_i$ 表示小于 $i$ 的质数个数，则对于每个满足条件的 $a,c$，有 $s_{\min\{c-1,\frac{n}{a^2\times c^2}\}}-s_a$ 种。

所以，枚举 $a,c$ 即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6+5;
int n,ans,a[N],cnt,s[N];
bool b[N] = {0,1};
signed main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	for(int i = 2;i<N;i++)//质数筛
	{
		if(b[i]==0) a[++cnt] = i; 
		for(int j = 1;j<=cnt&&i*a[j]<=N;j++) 
		{
			b[i*a[j]] = 1;
			if(i%a[j]==0) break;
		}
	}
	for(int i = 1;i<N;i++)
		s[i] = s[i-1]+(b[i]==0);
	cin>>n;
	for(int i = 1;a[i]*a[i]*a[i+1]*a[i+2]*a[i+2]<=n;i++)
		for(int j = i+2;a[i]*a[i]*a[i+1]*a[j]*a[j]<=n;j++)
			ans+=max(1ll*0,s[min(a[j]-1,n/a[i]/a[i]/a[j]/a[j])]-s[a[i]]);
	cout<<ans;
 	return 0;
}
```

---

## 作者：lfxxx (赞：1)

先考虑枚举 $a,c$。

然后发现 $b \in [a+1,\min(c,\frac{n}{a^2 \times c^2})]$。

随后我们发现最劣情况下 $a=1$，此时 $b \in [1,\min(c,\frac{n}{c^2})]$。

显然 $\min(c,\frac{n}{c^2}) \leq n^{\frac{1}{3}}$。

因此我们可以把区间 $[1,n^{1/2}]$ 内的质数全部处理出来，用来枚举 $a,c$ 以及 $O(1)$ 计算满足要求的 $b$。

那么复杂度就是严格 $O(\sqrt n)$。

实测很快，只跑了 $24ms$。

[代码](https://atcoder.jp/contests/abc300/submissions/41083577)

---

## 作者：Sk_sync_opener (赞：0)

$a^2bc^2=n,n\leq 10^{12}$，不难得出 $a<b<c\leq \sqrt n\leq 10^6$。

那么首先筛出 $[1,10^6]$ 之内的所有素数，然后 $O(\sqrt n)$ 枚举 $a$，再暴力 $O(\sqrt n)$ 枚举 $c$，但是 $a,c$ 均为质数，而且 $a\leq c$，所以不会超。

接下来继续爆搜 $b$，$a<b<c$ 且 $a^2bc^2\leq n$，全部枚举就可以了。

质数筛可以直接暴力：

```cpp
for(int i = 2; i < N; i++) if(!f[i]) {
	p[++cnt] = i; for(int j = i + i; j < N; j += i) f[j] = 1;
}
```

时间复杂度为 $O(ans+\sqrt n\log n)$，$ans$ 表示答案，根据大样例，肯定可以过。

---

## 作者：incra (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc300_e)
### 题解
由于 $a,c$ 能取到的数较少，考虑先枚举 $a,c$ 的取值。

然后可以很容易得到 $b\in[a+1,\dfrac{n}{a^2\times c^2}]$。不难发现 $b$ 的取值范围具有二段性，所以我们可以用二分来优化查找 $b$ 能取到数的范围。

**时间复杂度：** 大概是 $O(cnt\sqrt{cnt}\log_2cnt)$，其中 $cnt$ 是 $1\sim \sqrt{n}$ 的质数个数。时间复杂度足以通过此题。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1000010;
LL n;
LL prime[N],cnt;
bool st[N];
int main  () {
	cin >> n;
	for (int i = 2;i < N;i++) {
        if (!st[i]) prime[++cnt] = i;
        for (int j = 1;prime[j] * i < N;j++) {
            st[prime[j] * i] = true;
            if (i % prime[j] == 0) break;
        }
    }
    LL ans = 0;
    for (int i = 1;i <= cnt;i++) {
    	LL k = prime[i] * prime[i];
    	if (k > n) break;
    	for (int j = i + 2;j <= cnt && k * prime[j] * prime[j] <= n;j++) {
    		if (k * prime[j] > n || k * prime[j] * prime[j] > n) break;
   			LL t = k * prime[j] * prime[j];
   			int l = i + 1,r = j - 1;
			while (l < r) {
   				int mid = l + r + 1 >> 1;
   				if (prime[mid] <= n / t) l = mid;
   				else r = mid - 1;
			}
			if (prime[l] <= n / t) {
//				cout << t << ' ' << l - i << endl;
				ans += l - i;
			}
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：guanyf (赞：0)

### 分析
找到题目的突破点：质数。即使我们用线性的筛法也无法筛出所有的质数。但是观察原式：$a^2 \times b \times c^2$，这就说明当其中的数最大时，也不应超过 $\sqrt{N}$，因此我们只需要筛出 $10^6$ 以内的质数就行了。

### 思路
依次枚举 $a,b,c$，$2 \le a \le \sqrt{N}$，$a < b \le \frac{N}{a}$，$b < c \le \sqrt{\frac{N}{ab}}$，且 $a,b,c$ 都为质数。这样算下来时间复杂度是很小的。

#### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int INF = 1e6;
int n, ans, len;
vector<int> p;
bool isp[INF + 5];
void init() {
  for (int i = 2; i <= INF; i++) {
    if (!isp[i]) p.push_back(i);
    for (auto j : p) {
      (i * j <= INF) && (isp[i * j] = 1);
      if (i % j == 0 || i * j > INF) break;
    }
  }
}
signed main() {
  ios::sync_with_stdio(0);
  init();
  cin >> n, len = p.size();
  for (int i = 0; i < len && p[i] * p[i] <= n; i++) {
    for (int j = i + 1; j < len && n / p[i] / p[i] >= p[j]; j++) {
      for (int k = j + 1; k < p.size() && n / p[i] / p[i] / p[j] >= p[k] * p[k]; k++) {
        ans++;
      }
    }
  }
  cout << ans;
  return 0;
}
```
### 扩展
实际上我们只需要枚举 $a,b$，再算出 $\sqrt{\frac{N}{a^2b}}$ 里质数的个数减去 $b$ 以内的质数个数就行了。我们可以在筛质数的时候用数组 $cnt$ 记录小于等于 $i$ 以内质数的的个数。由于这个值可能是负数，因此需要变成 $\max(0,cnt_{\sqrt{\frac{N}{a^2b}}}-cnt_b)$。

#### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int INF = 1e6;
int n, ans, len, cnt[INF + 5];
vector<int> p;
bool isp[INF + 5];
void init() {
  for (int i = 2; i <= INF; cnt[i++] = p.size()) {
    if (!isp[i]) p.push_back(i);
    for (auto j : p) {
      (i * j <= INF) && (isp[i * j] = 1);
      if (i % j == 0 || i * j > INF) break;
    }
  }
}
signed main() {
  ios::sync_with_stdio(0);
  init();
  cin >> n, len = p.size();
  for (int i = 0; i < len && p[i] * p[i] <= n; i++) {
    for (int j = i + 1; j < len && n / p[i] / p[i] >= p[j]; j++) {
      ans += max(0ll, cnt[signed(sqrt(n / (p[i] * p[i] * p[j])))] - cnt[p[j]]);
    }
  }
  cout << ans;
  return 0;
}
```


---

