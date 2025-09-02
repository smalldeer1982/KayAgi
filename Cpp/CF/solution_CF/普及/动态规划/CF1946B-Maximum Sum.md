# Maximum Sum

## 题目描述

You have an array $ a $ of $ n $ integers.

You perform exactly $ k $ operations on it. In one operation, you select any contiguous subarray of the array $ a $ (possibly empty) and insert the sum of this subarray anywhere in the array.

Your task is to find the maximum possible sum of the array after $ k $ such operations.

As this number can be very large, output the answer modulo $ 10^9 + 7 $ .

Reminder: the remainder of a number $ x $ modulo $ p $ is the smallest non-negative $ y $ such that there exists an integer $ q $ and $ x = p \cdot q + y $ .

## 说明/提示

In the first test case, it is advantageous to take an empty subarray of the array twice and insert the sum of the empty subarray (zero) anywhere, then the sum of the resulting array will be $ (-4) + (-7) + 0 + 0 = -11 $ , modulo $ 10^9 + 7 $ this is $ 999\,999\,996 $ .

In the second test case, it is advantageous to take the sum of the entire array three times and place it anywhere in the array, then one of the possible sequences of actions: \[ $ 2, 2, 8 $ \] $ \rightarrow $ \[ $ 2, 2, 8, 12 $ \] $ \rightarrow $ \[ $ 2, 2, 8, 12, 24 $ \] $ \rightarrow $ \[ $ 2, 2, 8, 12, 24, 48 $ \], the sum of the final array is $ 2 + 2 + 8 + 12 + 24 + 48 = 96 $ .

In the fourth test case, it is advantageous to take a subarray of the array consisting of the first three numbers (i.e. consisting of the numbers $ 4, -2 $ and $ 8 $ ) and insert its sum at the beginning of the array, thereby obtaining the array \[ $ 10, 4, -2, 8, -12, 9 $ \], the sum of this array is $ 17 $ .

In the seventh test case, it will always be advantageous for us to take an empty subarray of the array. In this case, the sum of the resulting array will not differ from the sum of the original. The answer will be the sum of the original array, taken modulo — $ 42 $ , because $ (-6 \cdot (10^9 + 7) + 42 = -6\,000\,000\,000) $ .

## 样例 #1

### 输入

```
12
2 2
-4 -7
3 3
2 2 8
1 7
7
5 1
4 -2 8 -12 9
7 4
8 14 -9 6 0 -1 3
7 100
5 3 -8 12 -5 -9 3
6 1000
-1000000000 -1000000000 -1000000000 -1000000000 -1000000000 -1000000000
2 1
1000000000 8
5 4
0 0 0 0 0
6 10
48973 757292 58277 -38574 27475 999984
7 1
-1000 1000 -1000 1000 -1000 1000 -1000
10 10050
408293874 -3498597 7374783 295774930 -48574034 26623784 498754833 -294875830 283045804 85938045```

### 输出

```
999999996
96
896
17
351
716455332
42
2
0
897909241
0
416571966```

# 题解

## 作者：KazamaRuri (赞：6)

## 题目 CF1946B

题目大意：给定一个长度为 $n$ 的序列，并执行 $k$ 次操作：将数组中任意一段连续的子段（可以为空）的和，插入到数组的任意位置。在执行完所有操作后，输出数组能够得到的所有元素之和的最大值。

## 解析

当 $k = 1$ 时，答案就是最大子段和加上数组所有元素之和，因为只有插入**最大子段和**才能使操作的利益最大化。

当 $k$ 更大时，我们要把每一轮的最大子段和插入到哪里才能使答案更大？贪心地想，由于插入的最大子段和一定是**非负数**，为了使下次操作能获得更大的利益，一定要让当前操作后的最大子段和更大，那只能将**最大子段和之和插入到最大子段和当中**，这样下次操作的最大子段和就会是这一轮操作的最大子段和的两倍。记最初数组的最大子段和 $sum1$，数组所有元素之和为 $sum2$，最终的答案就是：
$$
sum1 \cdot  (1 + 2 + 4 + \dots + 2^{k-1}) + sum2
$$
经过等比数列的求和公式化简得到：
$$
sum1 \cdot 2^k - sum1 + sum2
$$
$2$ 的 $k$ 次方可以用快速幂优化，最终每个测试样例的时间复杂度为 $O(n + \log_{2}(k))$。

## 代码
```cpp
#include <iostream>
using namespace std;

const int N=2e5+5,mod=1e9+7;
typedef long long ll;
int T,n,k,a[N];
ll ans,sum,all_sum;
ll qp(ll x,int y){
	ll mul=1;
	while(y){
		if(y&1) mul=mul*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return mul;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++)
			scanf("%d",a+i);
		ans=sum=all_sum=0;
		for(int i=1;i<=n;i++){
			sum=sum+a[i];
			ans=max(ans,sum);
			sum=max(sum,0ll);
			all_sum=all_sum+a[i];
		}
		printf("%d\n",(1ll*ans%mod*qp(2,k)%mod+(all_sum%mod-ans%mod+mod)%mod+mod)%mod);
	}
	
	return 0;
}
```

---

## 作者：oyoham (赞：5)

### Problem

[CF传送门 CF1946B](https://codeforces.com/problemset/problem/1946/B)

### Solution

观察题目可以发现，每一次将序列中的最大子段和插入到其后面即可有最优。  
设最大子段和为 $mx$，数组总和为 $sum$，那么除去最大子段和剩余部分为 $sum-mx$，因为有 $k$ 次操作，所以可以是其最大子段和变为原来的 $2^k$ 倍，所以答案就是 $sum-mx+mx \times 2^k$。考虑快速幂优化。

### Code
代码如下
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
inline ll read(){
	ll x=0;
	short f=1;
	char c=getchar();
	while(c>57||c<48){
		if(c==45) f=-1;
		c=getchar();
	}
	while(c<58&&c>47){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
inline void write(ll x){
	if(x<0ll) putchar(45),x=~x+1;
	if(x>9ll) write(x/10);
	putchar(x%10|48);
}
#define mod 1000000007
int T;
int a[200005];
int dp[200005];
int mx,sum;
int fp(int a,int b,int p=mod){
	int base=a;
	int ans=1;
	while(b){
		if(b&1){
			ans=ans*base%p;
		}
		base=base*base%p;
		b>>=1;
	}
	return ans;
}
signed main(){
	T=read();
	while(T--){
		int n=read(),k=read();
		mx=sum=0;
		for(int i=1;i<=n;i++) a[i]=read();
		for(int i=1;i<=n;i++) dp[i]=max(dp[i-1]+a[i],0ll);
		for(int i=1;i<=n;i++) mx=max(mx,dp[i]);
		mx%=mod;
		for(int i=1;i<=n;i++) sum+=a[i];
		sum%=mod;
		int fn=(((fp(2,k)*mx%mod)+sum-mx)%mod+mod)%mod;
		write(fn);
		putchar(10);
		for(int i=1;i<=n;i++) dp[i]=0;
	}
} 
```
~~听说不用快速幂好像也能过。~~

---

## 作者：cute_overmind (赞：4)

考虑贪心：

第一次显然拿最大的子段，即 [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)。

那么我们应该把它放到哪里呢，考虑到要让下一次的子段最大，显然插入原先的最大子段中，就可以让下次最大，就会最优。

第二次如果再次计算，显然 $O(nk)$ 会爆，于是发现第二次的和一定是第一次的 $2$ 倍，转化为等比数列求和，快速幂即可。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 200010;
const int mod = 1000000007;
int a[N];
int qp(int a, int b, int p){
	int sum = 1;
	while (b){
		if(b & 1)
			sum =  sum * a % p;
		b >>= 1;
		a = a * a % p;
	}
	return sum;
}
void solve(){
	int n, sum = 0, mx = 0, k;
	cin >> n >> k;
	for(int i = 1 ; i <= n ; i ++) cin >> a[i];
	for(int i = 1 ; i <= n ; i ++){
		if(sum < 0) sum = 0;
		sum += a[i];
		mx = max(mx, sum);
	}
	sum = 0;
	for(int i = 1 ; i <= n ; i ++) sum += a[i];
	while(sum < 0) sum += mod;
	sum = ((sum % mod) + (qp(2, k, mod) - 1) % mod * (mx % mod) % mod) % mod;
	cout << sum << '\n';
}

signed main(){
	int t;
	cin >> t;
	while(t --)
		solve();

	return 0;
}
```

---

## 作者：littlebug (赞：4)

## Description

给定一个长度为 $n$ 的数组 $a$，进行 $k$ 次操作，使得数组所有元素的和最大，结果对 $10^9+7$ 取模。

定义一次操作为：

1. 选择 $a$ 数组的任意一个**子区间** $[l,r]$。
2. 计算区间 $[l,r]$ 的和为 $sum$，将 $sum$ 插入到数组 $a$ 的任意位置（此时数组 $a$ 的长度增加 $1$）。


## Solution

可以采取贪心的思路，每次对数组求**最大子段和**，并将其加入插入数组中。

先看第 $1$ 次操作，将原始序列的最大子段和其插入数组中，接下来讨论需要插到哪个位置。在第 $2$ 次操作时，出现了这样一种情况：有数组 $a$ 和一个元素 $sum$，求将 $sum$ 插入到数组 $a$ 的哪个位置时，数组的最大子段和最大。

很容易想到，将 $sum$ 插入到原数组 $a$ 的最大子段区间中的任意位置，一定会使 $a$ 的最大子段和最大。因为这是 $a$ 的最大子段和为 $sum\times2$，如果插到别的地方，那么最大字段和就一定 $<sum\times2$ 了。

如果直接模拟，时间复杂度为 $O(nk)$，会TLE，所以考虑是否能简化过程。

设 $\sum a$ 为数组 $a$ 的所有元素的和。

1. 第 $1$ 次操作时，设 $sum_1=$ 数组 $a$ 的最大子段和，$\sum a$ 增加了 $sum_1$。
2. 第 $2$ 次操作时，$sum_2=$ 第 $1$ 次操作后的最大子段和，就是 $sum_1\times2$。
3. 同理，第 $3$ 次操作时，$sum_3=sum_2\times2=sum_1\times2^2$。

所以，可以推出，第 $i$ 次操作的 $sum_i=sum_1\times2^{i-1}$。

接下来，只需要 $O(n)$ 求出原数组的最大字段和，然后 $O(k)$ 递推即可。

还有就是，因为数组 $a$ 中可能出现负数，所以对 $x$（$x$ 为任意数）取模时要 $(x\bmod p+p)\bmod p$。

关于最大子段和的求法，这里就不再赘述了，dp $O(n)$ 解之即可，不会的话可以看这道题：[link](https://www.luogu.com.cn/problem/P1115)。

## Code

```cpp
#include<iostream>
#include<cstdio>
#define il inline
#define ll long long
using namespace std;
const ll mod=1e9+7;
const int MAXN=2e5+5;
int n;
ll k;
ll a[MAXN];
ll f[MAXN];
il void solve()
{
	cin>>n>>k;
	ll sum=0;
	for(int i=1;i<=n;++i)
	{
		f[i]=0;
		cin>>a[i];
		sum+=a[i];
	}
	sum=(sum%mod+mod)%mod;
	ll mx=0;
	for(int i=1;i<=n;++i)
	{
		f[i]=max(a[i],f[i-1]+a[i]);
		mx=max(f[i],mx);
	}
	ll mul=1;
	mx%=mod;
	for(ll i=1;i<=k;++i)
	{
		sum=(sum+mul*mx%mod+mod)%mod;
		mul=mul*2%mod;
	}
	cout<<sum<<'\n';
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
		solve();
	return 0;
}

```

---

## 作者：T_TLucas_Yin (赞：3)

容易想到，要使得最后数组的和最大，每次加入的肯定是数组的最大子段和。如果最大子段和小于 $0$ 的话，就要加入 $0$。

这样一来每次加入的数肯定是非负的。因此每插入一个数，所有包含这个数的子段和肯定都会变大。我们可以把这个数插在刚刚取的最大子段里，这个子段的和就会成为所有插入情况中最大的一个。此时我们再把这个子段的和作为下一次插入的目标，并再次插入该段里，则依旧最大。如此就构造了最优策略。

既然我们每次取的子段是一样的（都是一开始的最大子段），所以每一次操作加入子段和到这个子段里，其实相当于让这个子段的和变成了原来的 $2$ 倍。我们就可以先统计出整个数组的和，然后找出最大子段和，进行 $k$ 次将最大子段和乘 $2$ 后加入原数组的操作即可。

注意取模别乱了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=1e9+7;
int t,n,m,a[1000005];
long long f[1000005];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d %d",&n,&m);
		long long maxn=0,sum=0;
		for(int i=1;i<=n;i++) scanf("%d",&a[i]),f[i]=0,sum+=a[i];//初始化子段和与整个数组的和
		sum=(sum%M+M)%M;//取模要保持在正数
		for(int i=1;i<=n;i++) f[i]=max(f[i-1],0ll)+a[i],maxn=max(maxn,f[i]);//求最大子段和
		for(int i=1;i<=m;i++) sum=((sum+maxn)%M+M)%M,maxn=maxn*2%M;//k(就是m)次操作
		printf("%lld\n",sum);//最终的数组和
	}
	return 0;
}
```

---

## 作者：Bc2_ChickenDreamer (赞：2)

## CF1946B

### Sol

放在前面的话：记得取模！

显而易见的，要使得你插入的和**最大**，那么必须要插入**最大子段**的和（如 $[-2, 4, -1, -2, 6]$ 需插入最大子段 $[4, -1, -2, 6]$ 的和 $7$）。

所以，我们先 $O(n)$ 找到最大子段和，然后模拟插入 $k$ 次。但**注意**，我们不能**直接**插入。我们发现，设 $M$ 为数组的最大子段和，插入 $k$ 次数组总和会增加 $M \times (1 + 2 + 4 + \cdots + 2^{k - 1}$）。所以我们只需把数组之和加上这个值即为答案。

但**需要注意**的是，如果 $M \le 0$，那么**不用**进行操作。

最大子段和公式：$\max_{i = 1}^{n} (\sum_{j = 1}^{i} a_j - \min_{j = 1}^{i} (\sum_{k = 1}^{j} a_k))$，但要 $O(n)$ 解决，详见代码。

### Code

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
 
using namespace std;
 
using ll = long long;
 
const int kMaxN = 2e5 + 20, kInf = (((1 << 30) - 1) << 1) + 1, kMod = 1e9 + 7;
const ll kLInf = 9.22e18; 
 
ll n, k, a[kMaxN], b[kMaxN];
 
ll MaxA() { // 找到最大子段和
  ll sum = 0, m = kLInf, ans = -kLInf;
  for (int i = 0; i <= n; ++ i) {
    sum += a[i]; // 记录总和
    ans = max(ans, sum - m); // 取 max
    m = min(m, sum); // 每次更新左端点
  }
  return ans;
}
 
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t;
  for (cin >> t; t; -- t) {
    cin >> n >> k;
    for (int i = 1; i <= n; ++ i) {
      cin >> a[i];
    }
    ll mx = MaxA(), Ans = 0; // 求出最大子段和 mx
    if (mx <= 0) { // 如果 mx <= 0，那么直接求和，不用进行任何操作
      Ans = 0;
      for (int i = 1; i <= n; ++ i) { // 求和，记得取模！
        Ans = (Ans + a[i] + kMod) % kMod;
      }
      cout << (Ans + kMod) % kMod << '\n';
      continue; // 开始下一个询问
    }
    Ans = 0;
    for (int i = 1; i <= n; ++ i) { // 求数组和
      Ans = (Ans + a[i] + kMod) % kMod;
    }
    for (int i = 1; i <= k; ++ i) { // 加上插入 k 次数组总和会增加的值
      Ans = (Ans + mx + kMod) % kMod;
      mx = (mx * 2 + kMod) % kMod;
    }
    cout << Ans << '\n';
  }
  return 0;
}
```

---

## 作者：Stars_visitor_tyw (赞：1)

## CF1946B Maximum Sum 题解
### 题意
给定一个包含 $n$ 个整数的数组 $a$。

你需要进行 $k$ 次操作。每次操作，你可以选择数组中的一个连续子数组（可以为空），并在数组中的任意位置插入这个子数组的和。

你的任务是找到进行 $k$ 次操作后数组可能的最大和。

由于这个数可能很大，输出答案时需要对 $10^9+7$ 取模。

提示：一个数 $x$ 对 $p$ 取模的余数是满足存在整数 $q$ 和 $x=p \times q+y$ 的最小非负数 $y$。
### 分析
首先求出最大子段和 $maxi$，然后第一次操作我们需要加上的子数组和是 $sum=maxi$，然后剩余操作每次需要增加的和都是上一次的两倍，最后输出 $k$ 次操作总共增加的值加上原数组的和即可。

提示：由于有负数，在取模时需先加上模数再进行取模。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, a[200005], k;
int dp[200005];
const int mod=1e9+7;
signed main()
{
//    freopen("xxx.out","w",stdout);
    int t;
    for(cin>>t;t;t--)
    {
        int sum1=0;
        cin>>n>>k;
        dp[0]=0;
        for(int i=1;i<=n;i++)
        {
            cin>>a[i];
            sum1+=a[i];
            dp[i]=max(dp[i-1]+a[i],a[i]);
        }
        int maxi=-1e18, sum=0;
        for(int i=1;i<=n;i++)
        {
            maxi=max(maxi,dp[i]);
        }
        if(maxi<0)
        {
            maxi=0;
        }
        sum=maxi;
        for(int i=1;i<k;i++)
        {
            maxi=max((maxi+mod)%mod+(maxi+mod)%mod,0ll);
            sum+=maxi;
        }
        cout<<(((sum1+mod)%mod+(sum+mod)%mod)+mod)%mod<<"\n";
    }
	return 0;
}
```

---

## 作者：kczw (赞：1)

# 题意
给定一个长 $n$ 的序列 $a$，操作 $k$ 次，每次择其一子序列（可为空），将其和插入 $a$ 的任意位置，求最后 $a$ 的和的最大值。
# 思路
每次操作可以看作使 $a$ 原本的和增加一个数，这个数就是其某一子序列和。

那么我们只需要求出这个最大子序列之和即可，因为如果增加了一个数，那么我们将这个数放入这个和最大的子序列中，那么子序列的和翻倍一次，总共翻倍 $k$ 次。

设原 $a$ 的和为 $sum$，而最大子序列和为 $max$，答案即为 $sum+max\times(2^k-1)$
# 代码
```cpp
#include<bits/stdc++.h>
 
#define int long long
#define mod 1000000007
 
using namespace std;
 
const int N=2e5+5;
 
int t,n,k,a[N],mn,mx;
 
main(){
 
    // freopen("c.out","w",stdout);
 
    scanf("%lld",&t);
 
    while(t--){
 
        mn=0;
        mx=-1e18;
 
        scanf("%lld%lld",&n,&k);
        for(int i=1;i<=n;i++){
            scanf("%lld",&a[i]),
 
            a[i]+=a[i-1];
            mn=min(mn,a[i]);
            mx=max(mx,a[i]-mn);
        }
        
        int res=mx;
        for(int i=1;i<=k;i++)res=(res+res)%mod;
        res=((res-mx)%mod+mod)%mod;
 
        printf("%lld\n",(a[n]%mod+mod+res)%mod);
    }
}
```

---

## 作者：Weekoder (赞：1)

#### 思路

考虑贪心。

$O(n)$ 求出最大子段和，发现一共有 $2^k$ 个最大子段和，即 $2^k\times \max_{i=1}^n dp_i$。快速幂 $O(\log n)$ 求出 $2^k$。

若 $\max_{i=1}^n dp_i$ 小于零，则需要插入空子序列 $0$，直接计算整个区间和。

记得取模。

# $\text{Code:}$

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 2e5 + 5, MOD = 1e9 + 7;

int T, n, k;

ll a[N], dp[N];

ll expow(ll x, ll y) {
    ll r = 1;
    while (y) {
        if (y & 1) r = r * x % MOD;
        x = x * x % MOD, y >>= 1;
    }
    return r % MOD;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> T;
    while (T --) {
        cin >> n >> k;
        for (int i = 1; i <= n; i++)
            cin >> a[i], dp[i] = a[i];
        int start = 1, end = 1, p = 1;
        ll maxi = a[1];
        for (int i = 2; i <= n; i++) {
            if (dp[i - 1] + a[i] >= dp[i]) 
                dp[i] = dp[i - 1] + a[i];
            else
                p = i;
            if (dp[i] > maxi)
                maxi = dp[i], start = p, end = i;
        }
        ll sum = 0;
        if (maxi >= 0) {
            ll tmp = expow(2, k);
            sum = maxi % MOD * tmp % MOD;
            for (int i = 1; i < start; i++) sum = (sum + a[i]) % MOD;
            for (int i = end + 1; i <= n; i++) sum = (sum + a[i]) % MOD;
        }
        else 
            for (int i = 1; i <= n; i++)
                sum = (sum + a[i]) % MOD;
        if (sum < 0) 
            while (sum < 0) sum += MOD;
        cout << sum % MOD << "\n";
    }
    return 0;
} 
```

---

## 作者：King_duck (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1946B)

这道题的主要意思是给你一个数组 $a$，长度为 $n$，然后执行 $k$ 次操作，每一次操作指的是：从数组 $a$ 截取一段子数组，这段子数组中所有的数的和为 $sum$，然后将 $sum$ 插入数组 $a$ 中。最后要求出经过 $k$ 次操作后数组的最大和。

这道题明显是要用贪心的。

第一次拿最大的子段，考虑到要让下一次的子段最大，所以插入原先的最大子段中，就可以让下次最大，就会最优。

第二次如果再次计算，显然 $O(nk)$ 会爆，然后我们发现第二次的和一定是第一次的 $2$ 倍，所以就转化为等比数列求和，快速幂就可以了。

上代码。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,mod=1e9+7;
int a[N];
int ksm(int a,int b,int mod)
{
	int sum=1;
	while(b)
	{
		if(b&1)
		{
			sum=sum*a%mod;			
		}
		b>>=1;
		a=a*a%mod;
	}
	return sum;
}
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,sum=0,m=0,k;
		cin>>n>>k;
		for(int i=1;i<=n;i++) 
		{
			cin>>a[i];
		}
		for(int i=1;i<=n;i++)
		{
			if(sum<0) 
			{
				sum=0;
			}
			sum+=a[i];
			m=max(m,sum);
		}
		sum=0;
		for(int i=1;i<=n;i++) 
		{
			sum+=a[i];
		}
		while(sum<0) 
		{
			sum+=mod;
		}
		sum=((sum%mod)+(ksm(2,k,mod)-1)%mod*(m%mod)%mod)%mod;
		cout<<sum<<'\n';
	}
	return 0;
}
```

---

## 作者：haokee (赞：0)

## 题目大意

给定一个长度为 $n$ 的数组 $a$，你需要进行 $k$ 次操作，每一次操作都可以选择一个连续的子序列（可以为空），然后将这个子序列的和作为一个元素插入到这个数组当中。问你最后数组的和最大能够是多少，对 $10^9+7$ 取模。

## 思路

首先，题目告诉了我们这题是「最大值取模」而不是「取模后的最大值」，因此我们可以考虑贪心。我们可以先找到最大字段和，然后把它的和插入到旁边这个操作等同于对最大字段和的值 $\times 2$，而不会新加入其他的元素。因此，我们直接模拟就可以了。

## 代码

```cpp
#include <iostream>

using namespace std;
using LL = long long;

const LL kMaxN = 2e5 + 5, kMod = 1e9 + 7;

LL a[kMaxN], dp[kMaxN], t, n, k, mx, ans;

int main() {
  for (cin >> t; t; t--) {
    cin >> n >> k, ans = mx = 0;
    for (LL i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (LL i = 1; i <= n; i++) {  // 求最大字段和
      mx = max(mx, dp[i] = max(dp[i - 1] + a[i], a[i]));
    }
    ans = -mx;  // 注意 ans 需要额外减去原来的部分
    for (; k--; mx = mx * 2 % kMod) { }  // 增长 n 次
    for (LL i = 1; i <= n; i++) {
      ans = (ans + a[i] + kMod) % kMod;  // 求数组和
    }
    cout << (ans + mx + kMod) % kMod << '\n';  // 加起来
  }
  return 0;
}
```

---

## 作者：DFbd (赞：0)

## 思路
首先，我们要选择第一次操作的子段，于是对数组 $a$ 求最大子段和。

求得最大子段和后，由于题目中说了，和可以插入到数组中的任意位置，所以我们把这个和插入到最大子段的旁边，这样新一次操作的最大子段和就是上一次的两倍。

进行 $k$ 次操作，就会把和增加原数组最大子段和的 $2^k - 1$ 倍。

所以输出原数组和加原数组最大子段和的 $2^k - 1$ 倍。

计算过程中不要忘记取模（负数要加模数再取模）。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
int t,n,k,a[200005],dp[200005],s[200005],sum;
signed main(){
    s[0]=1;
    for(int i=1;i<=200000;i++){
        s[i]=s[i-1]*2%mod;//预处理2的k次方
    }
    cin >> t;
    while(t--){
        cin >> n >> k;
        sum=0;
        int maxn=0;
        for(int i=1;i<=n;i++){
            cin >> a[i];
            dp[i]=max(dp[i-1]+a[i],a[i]);
            sum=(sum+(a[i]+mod)%mod)%mod;//原数组和
            maxn=max(maxn,dp[i]);//最大子段和
        }
        cout << (maxn%mod*(s[k]-1)%mod+sum)%mod << "\n";
    }
    return 0;
}
```

---

## 作者：hao_zi6366 (赞：0)

## 题意分析
显然，为了让数组最大，我们每次都要复制当前的最大子段和，把他放到最大的子段里，一开始可以用 DP 来寻找最大字段，不过要注意，如果最大字段和仍小于 0，就要用 0 来代替。

小贴士：
- 为了让输出是整数，记得模之前先加上模数，即：`m=((m)%mod+mod)%mod;`


## 完整代码
```cpp
#include<bits/stdc++.h>
#define inf 0x7fffffff
typedef long long ll;

const int mod=1e9+7;				//模数
int main(){
	/*freopen("xxx.in","r",stdin);
	freopen("xxx.out","w",stdout);*/
	std::ios::sync_with_stdio(0);
	std::cout.tie(0);
	std::cin.tie(0);
	
    int t;
	std::cin>>t;
	while(t--){
		int n,k;
		std::cin>>n>>k;
		std::vector<ll> a(n+1);
		for(int i=1;i<=n;i++)std::cin>>a[i];
        ll mxx=a[1],mx=-inf;
        mx=std::max(mxx,mx);
		for(int i=2;i<=n;i++){
            mxx=std::max(a[i],mxx+a[i]);	//进行DP
            mx=std::max(mxx,mx);			//mx是最大子段和		
        }
    	mx=std::max(mx,(ll)0);	//是否大于0
		ll m=mx;
        for(int i=1;i<=k;i++){
            m*=2;				//每次插入再复制就相当于乘二
            m=((m)%mod+mod)%mod;	//记得模数
        }
        ll sum=0;
        for(int i=1;i<=n;i++){		//统计答案
            sum+=a[i];
        }
        std::cout<<((sum-mx+m)%mod+mod)%mod<<'\n';
	}
	return 0;
}
```

---

