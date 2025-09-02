# Copy or Prefix Sum

## 题目描述

You are given an array of integers $ b_1, b_2, \ldots, b_n $ .

An array $ a_1, a_2, \ldots, a_n $ of integers is hybrid if for each $ i $ ( $ 1 \leq i \leq n $ ) at least one of these conditions is true:

- $ b_i = a_i $ , or
- $ b_i = \sum_{j=1}^{i} a_j $ .

Find the number of hybrid arrays $ a_1, a_2, \ldots, a_n $ . As the result can be very large, you should print the answer modulo $ 10^9 + 7 $ .

## 说明/提示

In the first test case, the hybrid arrays are $ [1, -2, 1] $ , $ [1, -2, 2] $ , $ [1, -1, 1] $ .

In the second test case, the hybrid arrays are $ [1, 1, 1, 1] $ , $ [1, 1, 1, 4] $ , $ [1, 1, 3, -1] $ , $ [1, 1, 3, 4] $ , $ [1, 2, 0, 1] $ , $ [1, 2, 0, 4] $ , $ [1, 2, 3, -2] $ , $ [1, 2, 3, 4] $ .

In the fourth test case, the only hybrid array is $ [0, 0, 0, 1] $ .

## 样例 #1

### 输入

```
4
3
1 -1 1
4
1 2 3 4
10
2 -1 1 -2 2 3 -5 0 2 -1
4
0 0 0 1```

### 输出

```
3
8
223
1```

# 题解

## 作者：fanfansann (赞：13)

## F - Copy or Prefix Sum
**Problem F Cpoy or Prefix Sum**

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210213171729879.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTY5Nzc3NA==,size_16,color_FFFFFF,t_70)
**Translation**

给定一个 $b$ 数组，一个 $a$ 是合法的指对于每一个 $i$ 都有 $b_i=a_i$ $b_i=\sum\limits_{j=1}^{i}a_j$ 。问合法的 $a$ 有多少个。


$1\le t\le 10^4,1\le \sum n\le 2\times 10^5,-10^9\le b_i\le 10^9$

**Word**

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210213174922633.png)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210213171610679.png)


**Solution**


看着这个式子，很明显就是一个DP。

因为题目中 $a$ 可以等于 $b_i=\sum\limits_{j=1}^{i}a_j$，所以DP考虑维护前缀和。$f[i][j]$ 表示前 $i$ 个数中，前缀和为 $j$ 的方案数。初始化经典 $f[0][0]=1$ ，最终的答案很明显就是 $\sum\limits_{j=min}^{max}f[n][j]$。
有了边界，答案，开考虑转移方程。

因为有两种情况，所以分类讨论。

当  $a[i]$ 等于 $b[i]$ 时：

对于 $j\in[min,max]$ 很明显

- 有  $f[i][j]=f[i-1][j-b[i]]$

当 $a[i]$ 等于 $b_i=\sum\limits_{j=1}^{i}a_j$ 时，我们计算前缀和 $sum[i]$，即此时 $a[i]=b[i]-sum[i-1]$：


- 有 $f[i][b[i]]=\sum\limits_{j=-min}^{max}f[i-1][j]$ 

不过由于数据过大，我们不能直接开数组，但是数据量小，所以我们可以使用 `map` 来代替数组，进行转移。


但是我们这样暴力循环递推，并且因为使用到了 `map` ，所以总的时间复杂度为$O(n^2logn)$，而 $1\le n\le 2\times 10^5$，所以考虑如何优化。

我们发现实际上第一个转移方程就是所有的元素全部向右移动 $b[i]$ ，所以对于第一种转移，我们只需要记录一下最终向右移动了多少，然后每次 $O(1)$ 转移。

对于第二个转移方程，实际意义就是 $f[i][b[i]]$ 等于前面的所有元素之和，设原来的全局之和（也就是答案）应该是 $ans$，  $f[i][b[i]]=ans$，原来的  $f[i][b[i]]$ 没了，也就是新的全局和变成了 $ans=ans+ans-f[i][b[i]]$。

最后因为 $-10^9\le b_i\le 10^9$，所以有可能答案为负数，所以最后 mod 的时候注意加上 mod 消掉负数。



**Code**

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
#include <unordered_map>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
typedef int itn;
const int N = 5e5 + 7, M = 1e6 + 7, mod = 1e9 + 7;
const int INF = 1e9 + 7;

int n, m, t, k, q;
ll x, y;
map<ll, ll>mp;
ll b[N];

void solve()
{
    ll deviation = 0, ans = 0;
    scanf("%d", &n);
    mp.clear();

    mp[0] = 1;
    ans = 1;
    for(int i = 1; i <= n; ++ i) {
        scanf("%lld", &b[i]);
    }
    for(int i = 1; i <= n; ++ i) {
        deviation -= b[i];
        ll change = ans - mp[b[i] + deviation];
        mp[b[i] + deviation] = ans;
        ans = ans + change % mod;
    }
    printf("%lld\n", (ans % mod + mod) % mod);
    return ;
}

int main()
{
    scanf("%d", &t);
    while(t -- ) {
        solve();
    }
}
```

  

---

## 作者：Werner_Yin (赞：13)

# Problem

[更好的阅读体验](https://www.cnblogs.com/werner-yin/p/solution-CF-1485-F.html)

传送门：[CF1485F Copy or Prefix Sum](https://codeforces.com/contest/1485/problem/F)

给出一个长度为 $n$ 的序列 $b_1,b_2,\dots ,b_n$ ，求出有多少种序列$a_1,a_2,\dots,a_n$ 满足：

$\forall i \in [1,n],b_i = a_i$ $or$ $ b_i = \sum_{j=1}^i a_j$.

# Sol

考虑当前我们填到第 $i$ 位，所填的数的和是 $S$ , 那么，我们可以填：

1.$b_i$ 

2.$b_i-S$

于是，我们可以记$dp_i$ 代表当前填的数之和为 $i$ 的方案数，于是，两种操作对应这：

1.$dp_{i+b_i} = dp_i$ 

2.$dp_{b_i} = $ $\sum_{j=-\inf}^{\inf}{dp_j}$

但是要注意，当 $b_i = b_i - S$ 也就是 $S = 0$ 时，是只能算一遍的，减去 $dp_0$ 即可。

然后维护一个 $map$ ,代表 $DP$ 数组，维护一个 $totadd$ ,代表全局移位(因为有操作一)，再维护一个目前的 $ans$，就搞完了。

# Code

```cpp
#define in read()
int read(){int x = 0,sgn = 1;char ch = getchar(); for(;!isdigit(ch);ch=getchar())if(ch=='-')sgn=-1;for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);return x*sgn;}

const int N = 2e5+10;
const int mod = 1e9+7;

int n,b[N];

void solve(){
	n = in;for(int i = 1;i <= n;i++) b[i] = in;
	map<ll,ll> f; f.clear();
	f[0] = 1; ll totadd = 0,ans = 1;
	for(int i = 1;i <= n;i++){
		ll tmp; tmp = (ans - f[-totadd] + mod)% mod; ans = (ans + tmp) % mod; (f[-totadd] += tmp) %= mod;
		totadd += b[i];
	}ans = (ans + mod) %mod;
	printf("%lld\n",ans);
}

int main(){
	int test = in;
	while(test--) solve();
	return 0;
}
```

# 彩蛋

1.出题人说 "F is easier than C."确实。

2. 于是我打完 C 后开始搞 F
3. 搞完了 F，确实是正解，但是已经 0 ：53 了，比赛已经结束了 3 分钟
4. 其实 F 早就搞完了，有两个神奇的错误调了一会儿，Can you guess ？

---

## 作者：GsjzTle (赞：7)

## 题目链接

[点我跳转](https://codeforces.com/contest/1485/problem/F) 

## 题目大意

>给定一个长度为 $N$ 的序列 $bi$
>
>问有多少个长度为 $N$ 的序列 $a$ 使得
>
>* $b[i] = a[i]$
>
>或
>
>* $b[i] = ∑a[j] , j∈[1,i]$ 

## 解题思路

>定义 $dp[i][j] $ 表示前 $i$ 项的前缀和为 $j$ 的序列 $a$ 的个数，其中 $dp[0][0] = 1$
>
>( 因为前缀和很大，所以需要用 $map$ 来操作 )
>
>那么：
>
>1. 当 $b[i] = a[i]$ 时 , $dp[i][j] = dp[i - 1][j - b[i]]$
>
>2. 当 $b[i] = ∑a[j] , j∈[1,i]$ 时 , $dp[i][b[i]] = ∑dp[i - 1][j],j∈[-inf,inf]$
>
>对于第一种转移相当于把整个数组的值向右平移  $b[i]$
>
>对于第二种转移需要注意当 $sum[i-1] = 0$ 时，$b[i]$ 既等于 $a[i]$ 又等于 $∑a[j] , j∈[1,i]$
>
>相当于多转移了一次 $dp[i - 1][0]$ ，所以需要减去 $dp[i - 1][0]$
>
>最后的答案 $ans = ∑dp[n][j],j∈[-inf,inf]$ ，复杂度为 $N^2logN$ ( $log$ 的复杂度源于 $map$ )
>
>考虑优化：
>
>定义 $sum[i]$ 表示长度为 $i$ 且满足题目条件的序列 $a$ 的个数
>
>>对于第一种转移，只是把数值向右平移，并不会导致答案的个数增加，所以 $sum[i] = sum[i - 1]$
>>
>>对于第二种转移，$dp[i][b[i]] += sum[i - 1]$ , 同时减去 $dp[i - 1][0]$ ，相当于 $sum[i] += sum[i - 1] , sum[i] -= dp[i - 1][0]$ 
>
>于是我们可以定义 $py$ 表示平移的长度，起初 $py = 0$，每计算完 $sum[i]$ 后 , 令 $py += b[i]$
>
>那么 $dp[i - 1][j]$ 则可以用 $dp[j - py]$ 表示
>
>而 $dp[i][j]$ 则可以用 $dp[j - py - b[i]]$ 表示
>
>于是可得 $sum[i] += sum[i - 1] - dp[0 - py]$ , $dp[b[i] - py - b[i]] += sum[i - ] - dp[0 - py]$
>
>最后的答案 $ans = sum[n]$ , 复杂度为 $NlogN$

## AC_Code

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

const int N = 3e5 + 10 , mod = 1e9 + 7;

map<int , int>dp;

int b[N];

signed main()
{
	int T = 1;
	
	cin >> T;
	
	while(T --)
	{
		dp.clear();
		
		int n , sum = 1 , py = 0;
		
		cin >> n;
		
		for(int i = 1 ; i <= n ; i ++) cin >> b[i];	
		
		dp[0] = 1;
		
		for(int i = 1 ; i <= n ; i ++)
		{
			int add = (sum - dp[0 - py] + mod) % mod;
			
			sum = (sum + add) % mod , py += b[i];
			
			dp[b[i] - py] = (dp[b[i] - py] + add) % mod;
		}
		
		cout << sum << '\n';
	}
	
	return 0;
}
```

---

## 作者：lsj2009 (赞：4)

### Solution

妙妙题。

朴素地，我们考虑设 $f_{i,j}$ 为考虑前 $i$ 个数且 $\sum\limits_{k=1}^i a_k=j$ 的方案总数，但是 $j$ 过大肯定寄飞。但是考虑到转移只有两种：

1. 当取 $a_i=b_i$ 时，$f_{i,j}\gets f_{i-1,j-b_i}$。
2. 当取 $\sum\limits_{k=1}^i a_k=b_i$ 时，$f_{i,b_i}\gets \sum\limits_x f_{i-1,x}$。

第一种转移其实相当于全局位移，我们不妨考虑维护一个 $\Delta=\sum\limits_{k=1}^i b_k$；对于第二种操作，相当于全局求和，我们维护一个 $sum$。当进行第二种操作时，由于是全局求和，所以必然也包含原来的 $f_{\Delta}$，所以需要减去，否则会重复计算。即令 $f'_{\Delta}\gets sum,sum'\gets (sum-f_{\Delta})+f'_{\Delta}$。

然后就做完了。由于数组很大，所以需要开 ``map`` 保存，复杂度 $\Theta(n\log{n})$。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int MOD=1e9+7;
map<int,int> f;
signed main() {
    int T;
    scanf("%lld",&T);
    while(T--) {
        f.clear();
        int n;
        scanf("%lld",&n);
        int res=0,ans=f[0]=1;
        while(n--) {
            int x;
            scanf("%lld",&x);
            int val=ans-f[res];
            f[res]=ans;
            ans=((ans+val)%MOD+MOD)%MOD;
			res-=x;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：sry_ (赞：4)

提供一个更加 $trival$ 的做法。

问题是通过给定的 $b$ 序列通过操作 $1/2$ 生成的 $a$ 序列有多少种本质不同的。

不妨考虑一下如何解决本质不同的问题，即解决存在一个位置填 $1/2$ 均可。

假设当前矛盾的位置为 $u$ ，设之前的最近 $2$ 操作位置为 $v$ 。

当且仅当 $\sum_{i=v}^u A_i=A_u$ 会产生矛盾。

那么我们只需要对上述条件去做 $dp$ ，设 $f_i$ 表示当前考虑到第 $i$ 位，且当前操作位可以填 $2$ 的操作数。

转移枚举上个填 $2$ 的位置。

$f_i=\sum_{j=0}^{i-1} [\sum_{k=j}^iA_k=A_i] f_j$ 

答案即为 $\sum_{i=0}^n f_i$ 。

上式也很好优化到 $\mathcal O(n\log n)$ 。

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<climits>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define int long long
#define mod 1000000007
using namespace std;
inline int read(){
	int f=1,ans=0; char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){ans=ans*10+c-'0';c=getchar();}
	return f*ans;
}
const int MAXN=2e5+11;
int T,A[MAXN],S[MAXN],f[MAXN],N,All; map<int,int> Ma;
signed main(){
	T=read();
	f[0]=1; while(T--){
		N=read(); for(int i=1;i<=N;i++) A[i]=read(),S[i]=S[i-1]+A[i];
		int all=1; Ma.clear(); 
		for(int i=1;i<=N;i++){
			f[i]=all-Ma[S[i]-A[i]]; 
			if(S[i]==A[i]) f[i]--;
			f[i]=((f[i]%mod)+mod)%mod; Ma[S[i-1]]+=f[i],Ma[S[i-1]]%=mod;
			all+=f[i],all%=mod;
			
		}
		int res=0; for(int i=0;i<=N;i++) res+=f[i],res%=mod;
		printf("%lld\n",res);
	}
}/*
1
3
1 -1 1
*/
```


---

## 作者：ZillionX (赞：3)

# Description

给定一个 $b$ 数组，一个 $a$ 是合法的指对于每一个 $i$ 都有 $b_i=a_i$ 或 $b_i=\sum\limits_{j=1}^{i}a_j$。问合法的 $a$ 有多少个。答案对 $10^9+7$ 取模。

$t\le 10^4,\sum n\le 2\times 10^5,|b_i|\le 10^9$，时限 2s。

# Solution

随机找中分段题时找到的，本来想着很简单就不写题解了，结果题解区都是一些非常神秘的通过平移值域优化暴力 DP 的解法……来讲一下我的简单做法。

我们首先把这个题目要求写成可以直接根据前面的数推出 $a_i$ 的形式，其实就是 $a_i=b_i \lor a_i=b_i-\sum\limits_{j=1}^{i-1}a_j$，也就是每步有两个选择，下面称为操作 1 和操作 2。

不妨先推一下前面的 $b_j$ 对当前的 $a_i$ 的贡献形式。容易发现设上一次使用 2 操作的地方为 $u$，容易发现 $u$ 之前的 $b_j$ 都不会产生贡献，因此 $\sum a=\sum\limits_{k=u}^{i-1}b_k$。

因此到这里我们可以设计一个 DP。令 $f_i$ 表示 $i$ 为最后一个使用操作 2 的地方。那么转移可以枚举 $j$ 再用上面那个条件判断。进一步发现可以用前缀和优化。用前面的 $f$ 和减去和对 $a$ 做前缀和后，和 $s_{i-1}$ 相同的 $s_{j-1}$ 对应的 $f_j$ 值即可。

时间复杂度线性。

# Code

```cpp
#define int long long
const int N=2e5+5,mo=1e9+7;
int T,n,a[N];
map<int,int>o;
signed main(){
	scanf("%lld",&T);
	while(T--){
		o.clear();
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		int sm=1,sa=0;o[sa]=1;
		for(int i=2;i<=n;i++){
			sa+=a[i-1];int f=sm;
			sm=(sm+f+(mo-o[sa]))%mo,o[sa]=f;
		}
		printf("%lld\n",sm);
	}
	return 0;
}
```


---

## 作者：JiaY19 (赞：2)

### 思路

考虑 $a_i$ 要么是 $b_i$ 要么是 $b_i - s$。

考虑 $s$ 代表着什么。

它是 $a$ 的前缀和。

那么必然是往前一段 $b$ 的和。

因为每个 $b$ 代表着要么是这一位的 $a$ 或者前面所有的 $a$。

考虑设 $f_i$ 为这个位置填 $b_i$ 的方案数。

$g_i$ 为这个位置填与 $b_i$ 不同的 $b_i - s$ 的方案数。

那么有：

$$f_i=f_{i-1}+g_{i-1}$$

$$g_i=\sum_{j=1}^{i-1}g_j[sum_{i-1}-sum_{j-1}\neq 0]$$

下面这个式子可以直接哈希表优化，实现使用的 $\text{map}$。

### Code

```cpp
/**
 * @file 1485F.cpp
 * @author mfeitveer
 * @date 2023-11-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
#define mp(x, y) make_pair(x, y)
#define fro(i, x, y) for(int i = (x);i <= (y);i++)
#define pre(i, x, y) for(int i = (x);i >= (y);i--)
#define dbg cerr << "Line " << __LINE__ << ": "
#define EVAL(x) #x " = " << (x)

typedef int64_t i64;
typedef uint32_t u32;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef pair<int, int> PII;

bool ed;

const int N = 1000010;
const int mod = 1e9 + 7;

int n, m;
i64 all, g[N], f[N], a[N], sum[N];

inline void mo(i64 &x)
	{ x = (x % mod + mod) % mod; }
inline void solve()
{
	cin >> n;
	fro(i, 1, n) cin >> a[i], sum[i] = sum[i - 1] + a[i];
	map<i64, i64> mp; f[1] = all = mp[0] = 1;
	fro(i, 2, n)
	{
		i64 x = all - mp[sum[i - 1]];
		g[i] = x, f[i] = g[i - 1] + f[i - 1];
		mo(g[i]), mo(f[i]);
		all += g[i], mp[sum[i - 1]] += g[i];
		mo(all), mo(mp[sum[i - 1]]);
	}
	cout << (g[n] + f[n]) % mod << "\n";
}

bool st;

signed main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	double Mib = fabs((&ed-&st)/1048576.), Lim = 1024;
	assert(Mib<=Lim), cerr << " Memory: " << Mib << "\n";
	int t; cin >> t;
	while(t--) solve();
	return 0;
}

```

---

## 作者：Doubeecat (赞：2)

> [F. Copy or Prefix Sum](https://codeforces.ml/contest/1485/problem/F)
> 
> 有一数列 $b$，要求构造数列 $a$，使得每个 $b_i$ 满足 
> - $b_i=a_i$ 或 
> 
> - $b_i = \sum_{k=1}^{i}a_k$ 
> 
> 求构造方案数。
> 
> $n \leq 2 \times 10^5,-10^9 \leq b_i \leq 10^9$

## Solution:

首先思考下为什么答案不是 $2^n$，因为当 $\sum_{k=1}^{i-1}a_k = 0$ 时你会多算一遍。

所以我们先考虑一个比较简单粗暴的 DP，令 $f_{i,j}$ 表示我们当前构造到第 $i$ 个数，前缀和为 $j$ 时的方案数，转移依题意有两种：

- $f_{i,j+b_i} = \sum f_{i-1,j}$ 其中 $a_i = b_i$
- $f_{i,b_i} = \sum f_{i-1,j}$ 其中 $b_i = a_i + \sum_{k=1}^{i-1}a_k$

记得减去第一种 $j = 0$ 的情况。

我们考虑一下怎么去掉第一维：

- 第一种转移，实际上就是将整个 $f$ 数组平移了 $b_i$，这个我们可以通过一个 $delta$ 来解决。
- 第二种转移，实际上就是 $f_{b_i}$ 加上了整个数组的和，但当 $j = 0$ 时重复计算了，而在第一种转移的时候只是让 $f_{b_i}$ 位置变成了 $f_0$ ，所以直接让第二个位置等于所有元素的和就行了。
- 统计全局和，实际上除了 $b_i$ 这个位置全局和变了以外其他都没变，所以这边就直接 $sum = sum \times 2 - b_i$

注意这边 $b_i$ 的范围很抽象，所以我们开个 map 存 $f$ 数组即可。

时间复杂度 $O(n \log n)$

## Code:

```cpp
map <ll,ll> f;

ll n,a[N];

void solve() {
    f.clear();
    read(n);
    for (ll i = 1;i <= n;++i) {
        read(a[i]);
    }
    ll ans = 1,sum = 0;
    f[0] = 1;
    for (ll i = 1;i <= n;++i) {
        ll tmp = f[sum];f[sum] = ans;sum -= a[i];
        ans = (ans + ans - tmp + mod) % mod;
    }
    printf("%lld\n",ans);
}
```

---

## 作者：7KByte (赞：1)

每次有两种操作，如果没有重复方案则$Ans=2^n$。

观察一下，只有$\sum\limits_{j=1}^{i-1}a_j=0$ 时，两种操作是等价的。

所以我们可以设计$\texttt{DP}$，$f[i][j]$ 表示前 $i $ 个数，和为 $j$ 的方案数。

两种操作对应两种转移。

$j\ne a_i$ 时，有 $f[i][j]=f[i-1][j-a[i]]$ 。

$j=a_i$ 时，有 $f[i][j]=\sum\limits_{k\in Z} f[i-1][k]$ 。

观察一下，第一种转移就是将数组整体移动，第二种转移就是单点修改，开一个 $map$ 维护即可。

```cpp

#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 100005
#define P 1000000007
using namespace std;
int n;map<long long,long long>f;
void solve(){
	scanf("%d",&n);
	f.clear();f[0]=1;long long k=0,sum=1;
	rep(i,1,n){
		int x;scanf("%d",&x);
		long long cur=sum;sum=((sum*2-f[-k])%P+P)%P;k+=x;f[x-k]=cur;
	}
	printf("%lld\n",sum);
}
int main(){
	int T;scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：OldVagrant (赞：0)

## 题意
[题意传送门](https://www.luogu.com.cn/problem/CF1485F)
## Solution
首先，考虑 `dp[i]` 表示长度为 $i$ 的本质不同的合法 $a$ 序列的个数。  
对于第 $i$ 个位置而言，直接填 $b_i$ 的话就根本不用管之前的位置填什么，方案数显然等于 `dp[i-1]`。   
而如果选择另一种填法，那么理论上来说，对于每一种长度为 $i-1$ 的合法序列，我们都能找到一个 $a_i$，把它添加在末尾，构造出一个新的长度为 $i$ 的合法序列，那么这样的方案数也是 `dp[i-1]`。那么答案似乎就是 $2^n$ 了？样例都告诉你并不是这样的。      

问题在于，某些序列可能被重复计算。  
在填第 $i$ 个位置时，假如某个长度为 $i-1$ 的合法序列，其总和为  $0$，那么我们会在直接填 $b_i$ 的时候算上它的贡献，在选择另一种填法的时候又算上了它的贡献，而实际上它只能有一份贡献。  
于是，正确的状态转移方程就是要在原来的基础上再减掉这一部分多算的贡献，即 `dp[i]=dp[i-1]*2-sum[i-1][0]`，`sum[i][j]` 就表示长度为 $i$ 的合法序列中，总和为 $j$ 的有多少个。 
  
那么现在要解决的便是如何计算 `sum[i][j]`。同样的，我们也可以采用类似于动态规划的递推方式。
假如第 $i$ 个位置直接填 $b_i$，那么相当于把 $sum$ 数组里所有数集体向右（正方向）平移了 $b_i$ 个位置，其值不变。而如果是另一种填法，那么只会影响到 `sum[i][b[i]]` 的值，也就是使得 `sum[i][b[i]]=dp[i-1]`（前文提过，对于每个长度为 $i-1$ 的合法序列都有一种填法）。注意，这里是直接赋值，而非累加，累加就会像之前一样重复计算某些序列的贡献。   

到了这里，有两种求值的办法，一种是像其他题解里提到的那样，记一个全局累加量（位移量），然后使用 `map` 做一做即可。而我~~比较愚笨~~并未想到，但是也以另一种思路借助 `set` 实现了，具体的方法我以注释的形式附在代码的最后了。

## Code
```cpp
#include <bits/stdc++.h>
#define ll long long
#define gc getchar
#define pc(x) putchar(x)
using namespace std;
const int mod=1e9+7;
int dp[200001];
int read(){
	int x=0,y=1;
	char ch=gc();
	while(ch<48||ch>57){
		if(ch=='-') y=0;
	 	ch=gc();
	}while(ch>47&&ch<58) x=x*10+ch-48,ch=gc();
	return y?x:-x;
}
void write(int x){
    if(x>9) write(x/10);
    pc(x%10+48);
}
signed main(){
	int t=read();
	while(t--){
		int n=read()+1;
		ll sum=0;
		set<pair<ll,int> >s;
		set<pair<ll,int> >::iterator it;
		s.insert(make_pair(0,0)),dp[0]=1,dp[1]=1,s.insert(make_pair(0,1));
		for(int i=2,x;i<=n;i++){
			x=read(),it=s.lower_bound(make_pair(sum,i-1)),dp[i]=(dp[i-1]+dp[i-1])%mod;
			if(it!=s.begin()){
				it--;
				if((*it).first==sum) dp[i]=(dp[i]-dp[(*it).second]+mod)%mod; 
			}sum+=x,s.insert(make_pair(sum,i));
		}write(dp[n]),pc('\n');
	}//fwrite(PUF,1,Pout-PUF,stdout);
	return 0;
}
/*
我们不妨手动模拟一下 sum 数组的递推：
sum[1][b[1]]=dp[0];
sum[2][b[1]+b[2]]=dp[0];
sum[2][b[2]]=dp[1];
sum[3][b[1]+b[2]+b[3]]=dp[0];
sum[3][b[2]+b[3]]=dp[1];
sum[3][b[3]]=dp[2];
....
可以发现，处理到第i个位置时，sum数组里只有值为 b序列里以b[i]结尾的一段连续区间的和 的位置上才有值。
并且，假定这个连续区间是 以 b[j](j<=i) 开头的，那么sum[i][b[j]+b[j+1]+b[j+2]+...+b[i]]=dp[j-1]，想到前缀和了吗？
最重要的一点，这里的操作都是直接赋值，所以假如有多段连续区间的和为0，那么最后留下的只是最后一段的答案。
那么我们就可以开一个set，存的是一些(pre[i],i])，即第i个位置的前缀和，以及位置i。每次在set里找第一关键字等于pre[i-1]的最靠近i的位置，如果能找到，那么就减去这个位置的dp值。
一个小细节，就是在处理第1个位置的时候，如果没有特判的话，那么就要把下标整体右移（正移）1，因为涉及到了pre[-1]。
*/
```


---

