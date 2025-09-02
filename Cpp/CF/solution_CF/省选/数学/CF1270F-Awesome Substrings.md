# Awesome Substrings

## 题目描述

Let's call a binary string $ s $ awesome, if it has at least $ 1 $ symbol 1 and length of the string is divisible by the number of 1 in it. In particular, 1, 1010, 111 are awesome, but 0, 110, 01010 aren't.

You are given a binary string $ s $ . Count the number of its awesome substrings.

A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

## 说明/提示

In the first sample, all substrings of $ s $ are awesome.

In the second sample, we have the following awesome substrings of $ s $ : 1 ( $ 2 $ times), 01 ( $ 2 $ times), 10 ( $ 2 $ times), 010 ( $ 2 $ times), 1010, 0101

In the third sample, no substring is awesome.

## 样例 #1

### 输入

```
111
```

### 输出

```
6
```

## 样例 #2

### 输入

```
01010
```

### 输出

```
10
```

## 样例 #3

### 输入

```
0000
```

### 输出

```
0
```

## 样例 #4

### 输入

```
1111100000
```

### 输出

```
25
```

# 题解

## 作者：crashed (赞：11)

# 题目
&emsp;&emsp;[点这里](https://www.luogu.com.cn/problem/CF1270F)看题目。  
# 分析
&emsp;&emsp;设前缀和$s_r=\sum_{i=1}^r [S_i='1']$
&emsp;&emsp;考虑满足要求的子串$(l,r]$的要求：  
$$\exists k\in N_+, r-l=k(s_r-s_l)$$  
&emsp;&emsp;单独计算并不好算，考虑一个分块的优化。设置阈值$T$。  
&emsp;&emsp;对于$1\le k\le T$的$k$，对要求进行变形：  
$$r-l=k(s_r-s_l)\Rightarrow ks_r-r=ks_l-l$$  
&emsp;&emsp;设$f(i,k)=ks_i-i$，那么当$k$固定的时候，设$c(x,k)$为$f(i,k)=x$的数量，答案就是：  
$$\sum_{k=1}^T\sum_{x=0}^{nT}\binom{c(x,k)}{2}$$  
&emsp;&emsp;后面的那个循环，由于有值的$c(x,k)$不会超过$n$个，因此这一部分可以$O(nT)$计算。  
&emsp;&emsp;对于$T< k\le n$的$k$，继续变形：  
$$r-l=k(s_r-s_l)\Rightarrow \frac{r-l}k=s_r-s_l$$  
&emsp;&emsp;由于$k>T$，所以有$s_r-s_l< \frac nT$。也就是说，这种情况下**子串内 1 的数量比较少**。那么我们就可以直接枚举子串的起点（即式子中的$l$）和子串内 1 的数量来计算。  
&emsp;&emsp;当我们确定了 1 的数量的时候，我们也就可以确定此时右端点的范围$(x,y]$，那么也就知道了区间长度的范围$(x-i,y-i]$。此时的询问就变成求区间内的$k$的倍数的数量，可以$O(1)$。  
&emsp;&emsp;需要注意的是，由于这一部分不能前面的记重，因此应该满足：   
$$
\begin{aligned}
k>T&\Rightarrow \frac{r-l}{s_r-s_l}>T\\
   &\Rightarrow r-l>T(s_r-s_l)
\end{aligned}$$  
&emsp;&emsp;即区间长度必须大于$T(s_r-s_l)$，特判一下即可。  
&emsp;&emsp;时间复杂度是$O(nT+\frac{n^2}T)$，取$T=\sqrt n$最优。  
# 代码
```cpp
#include <cmath>
#include <cstdio>
#include <cstring>

typedef long long LL;

const int MAXN = 2e5 + 5, MAXT = 505;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

int buc[MAXN * MAXT];
int s[MAXN], nxt[MAXN];
int N, T;
char S[MAXN];

int main()
{
	LL ans = 0;
	scanf( "%s", S + 1 ), N = strlen( S + 1 ), T = ceil( sqrt( N ) );
	for( int i = 1 ; i <= N ; i ++ ) s[i] = s[i - 1] + S[i] - '0';
	if( s[N] == 0 ) { puts( "0" ); return 0; }
	for( int i = N ; ~ i ; i -- )
	{
		if( s[i] ^ s[i + 1] ) nxt[i] = i + 1;
		else nxt[i] = nxt[i + 1];
	}
	for( int k = 1, t ; k <= T ; k ++ )
	{
		for( int i = 0 ; i <= N ; i ++ ) buc[s[i] * k - i + N] ++;
		for( int i = 0 ; i <= N ; i ++ ) t = buc[s[i] * k - i + N], ans += 1ll * t * ( t - 1 ) / 2, buc[s[i] * k - i + N] = 0;
	}
	int l, r, tl, tr;
	for( int i = 0 ; i < N ; i ++ )
	{
		l = i, r = nxt[i];
		for( int k = 1 ; k <= N / T && s[i] + k <= s[N] ; k ++ )
		{
			l = nxt[l], r = nxt[r];
			tr = r - i - 1, tl = l - i;
			tl = MAX( tl, k * T + 1 );
			if( tl <= tr ) ans += tr / k - ( tl - 1 ) / k;
		}
	}
	write( ans ), putchar( '\n' );
	return 0;
}
```

---

## 作者：xht (赞：8)

## 题意

- 给定一个长度为 $n$ 的 $01$ 串 $s$。
- 求有多少个区间 $[l,r]$ 满足 $r - l + 1$ 是 $s_{l\dots r}$ 中 $1$ 的个数的倍数。
- $n \le 2 \times 10^5$。

## 题解

先求出前缀和 $s_{0\dots n}$，转化为求满足 $0 \le i < j \le n$ 且 $j - i = d(s_j - s_i)$ 的 $(i,j)$ 的个数，其中 $d$ 为 $\in [1,n]$ 的正整数。

考虑给定一个限制 $T$，移项得 $s_jd - j = s_id - i$，设 $f_i(d) = s_id - i$。

对于 $1 \le d \le T$ 的情况，我们对每个 $d$ 求出 $f_{0\dots n}(d)$ 的值，然后对于每个值 $x$，若有 $k$ 个 $i$ 满足 $f_i(d) = x$，则对答案有 $\binom{k}2$ 的贡献。

这一部分实现优秀的话可达到 $\mathcal O(nT)$。

对于 $T < d \le n$ 的情况，由于 $s_j - s_i = \frac{j-i} d < \frac nT$，即有贡献的 $(a,b)$ 对应的区间中 $1$ 的个数 $k < \frac nT$。因此我们对每个 $i$ 和 $k$ 找到 $j$ 的范围 $(l,r]$，其对答案的贡献为 $\lfloor \frac {r - i}k \rfloor - \lfloor \frac {l - i}k \rfloor$ 去掉 $d \le T$ 的部分。

这一部分实现优秀的话可达到 $\mathcal O(n\frac nT)$。

因此总时间复杂度为 $\mathcal O(nT + n\frac nT)$，取 $T = \sqrt n$ 即可达到最优时间复杂度 $\mathcal O(n \sqrt n)$。

```cpp
const int N = 2e5 + 7, M = 507;
int n, T, s[N], a[N*M];
char c[N];
ll ans;

int main() {
	rds(c, n), T = sqrt(n);
	for (int i = 1; i <= n; i++) s[i] = s[i-1] + c[i] - '0';
	for (int d = 1, x; d <= T; d++) {
		vi p;
		for (int i = 0; i <= n; i++) x = s[i] * d - i + n, ++a[x], p.pb(x);
		while (p.size()) x = p.back(), p.pop_back(), ans += 1ll * a[x] * (a[x] - 1) / 2, a[x] = 0;
	}
	for (int k = n / T - (T * T == n); k; k--) {
		int l = 0;
		while (l < n && s[l+1] < k) ++l;
		if (l == n) continue;
		int r = l + 1;
		while (r < n && s[r+1] <= k) ++r;
		for (int i = 0; i < n; i++) {
			if (s[r] - s[i] < k) {
				if (r == n) break;
				l = r;
				while (r < n && s[r+1] - s[i] <= k) ++r;
			}
			if ((r - i) / k > T) ans += (r - i) / k - max((l - i) / k, T);
		}
	}
	print(ans);
	return 0;
}
```

---

## 作者：feecle6418 (赞：6)

根号分治。

枚举 $d$，使 $d(s_r-s_l)=r-l$。$(l\ge 0)$

若 $d\le B$，变形式子为 $ds_r-r=ds_l-l$，设 $A_i=ds_i-i$，对每个 $B$ 求 $A_i$ 中相同对数即可。用 `sort` 实现，时间复杂度为 $O(nB\log n)$。

若 $d>B$，则区间内 `1` 的个数一定小于 $\dfrac{n}{B}$。枚举左端点与 `1` 的个数，可以 $O(1)$ 计算出可能的右端点所在的区间 $[l,r]$，然后除一下就能得到答案数。注意左端点要和 $i+(B+1)j-1$ 取 `max`，避免重复。

取 $B=\sqrt{\dfrac{n}{\log n}}$，总时间复杂度 $O(n\sqrt{n\log n})$。实际上常数非常小，反而比大多数 $O(n\sqrt{n})$ 算法跑得快。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
char str[200005];
int s[200005],n,B=300,a[200005],p[200005],tot;
ll ans=0;
int main(){
	cin>>str+1,n=strlen(str+1);
	for(int i=1;i<=n;i++){
		s[i]=s[i-1]+(str[i]=='1');
		if(str[i]=='1')p[++tot]=i;
	}
	for(int j=1;j<=B;j++){
		for(int i=0;i<=n;i++)a[i]=j*s[i]-i;
		stable_sort(a,a+n+1),a[n+1]=2e9;
		for(int i=0,cnt=0;i<=n+1;i++){
			if(i==0||a[i]^a[i-1])ans+=1ll*cnt*(cnt-1)/2,cnt=1;
			else cnt++;
		}
	}
	for(int i=1;i<=n;i++){
		int l=lower_bound(p+1,p+tot+1,i)-p;
		if(l>tot)break;
		for(int j=1,u=n/B,r;j<=u&&l+j-1<=tot;j++){//p[l]~p[l+j]-1
			int tl=p[l+j-1],tr=(l+j>tot?n:p[l+j]-1);
			ans+=max(0,(tr-i+1)/j-max((tl+j-i)/j,B+1)+1);
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：OIer_Eternity (赞：5)

[更好的阅读体验 - My Blog](https://blog.csdn.net/OIer_Cosmos/article/details/134619611?spm=1001.2014.3001.5501)

# 题目来源

- [CF1270F](https://codeforces.com/contest/1270/problem/F)

- [洛谷](https://www.luogu.com.cn/problem/CF1270F)

# Description

给定一个长度为 $n$ 的 $0/1$ 串 $s$，求有多少个区间 $[l,r]$ 满足 $r-l+1$ 是 $s_{l\cdots r}$ 中 $1$ 的个数的倍数。

- $n\le2\times10^5$。

# Solution

首先看到倍数问题，可以考虑 $\text{polylog}$ 做法和根号分治的做法。

但本题似乎只能使用根号分治的做法，于是我们可以枚举倍数 $k$。

当 $k\le \sqrt n$ 时，我们观察到如果设 $cnt_0,cnt_1$ 分别为区间内 $0$ 和 $1$ 的个数，则应满足 $kcnt_1=cnt_0+cnt_1$。

于是我们可以把 $s$ 中所有的 $1$ 全部赋值为 $k-1$，$0$ 则赋值为 $-1$，则一个区间权值和为 $0$ 和其满足 $kcnt_1=cnt_0+cnt_1$ 互为充要条件。

于是，我们就可以进行前缀和，并开一个桶统计即可（由于前缀和可能为负，需要加个偏移量 $n$）。

而当 $k>\sqrt n$ 时，$1$ 的可能的个数最多为 $\dfrac nk\le\sqrt n$。

因此，我们可以枚举区间的左端点 $l$ 以及 $1$ 的个数 $i$，并计算出满足条件的区间右端点所在的范围 $[r_l,r_r]$。

如何计算？只需要预处理出第 $i$ 个 $1$ 所在的位置 $pos_i$，便可 $O(1)$ 计算。

则满足条件的区间长度范围为 $[r_l-l+1,r_r-l+1]$，可能的倍数范围则为 $\Big[\lceil\dfrac{r_l-l+1}i\rceil,\lfloor\dfrac{r_r-l+1}i\rfloor\Big]$。

其对答案的贡献即为 $\lfloor\dfrac{r_r-l+1}i\rfloor-\max\{\sqrt n,\lfloor\dfrac{r_l-l}i\rfloor\}$，后面部分取 $\max$ 的原因是应把 $k\le\sqrt n$ 的部分去除。

最后输出答案即可，整体的复杂度为 $O(n\sqrt n)$。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,B,sum[200005],pos[200005],cnt[200005*505];
long long ans;
char s[200005];
int main(){
    scanf("%s",s+1);
    n=strlen(s+1),B=sqrt(n); // 根号分治
    for (int k=1;k<=B;k++){ // k<=根号n
        cnt[n]=1;
        for (int i=1;i<=n;i++) sum[i]=sum[i-1]+(s[i]=='1'?k-1:-1),ans+=cnt[sum[i]+n],cnt[sum[i]+n]++; // 1赋值为k-1，0赋值为-1，则符合条件的区间权值和为0
        for (int i=1;i<=n;i++) cnt[sum[i]+n]--,sum[i]=0;
    }
    for (int i=1;i<=n;i++)
        if (s[i]=='1') sum[i]=sum[i-1]+1,pos[sum[i]]=i;
        else sum[i]=sum[i-1];
    pos[sum[n]+1]=n+1;
    for (int l=1;l<=n;l++) // 左端点
        for (int i=1;i<=n/B;i++){ // 1的个数
            int rl=pos[i+sum[l-1]],rr=pos[i+sum[l-1]+1]-1;
            if (rl>0&&rr>0) ans+=max((rr-l+1)/i-max(B,(rl-l)/i),0);
        }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Acc_Robin (赞：2)

# CF1270F Awesome Substrings 题解

链接：[洛谷](https://www.luogu.com.cn/problem/CF1270F) [CodeForces](http://codeforces.com/problemset/problem/1270/F)

[更高更妙的观看角度](https://accrobin.github.io/2021/10/29/solver/CF1270FAwesomeSubstrings/)

## 题意

给定一个长度为 $n$ 的 $01$ 序列 $\{a\}$，求有多少个区间 $[l,r]$ 满足 $ \sum\limits_{i=l}^ra_i\mid (r-l+1)$ 。

$n\le 2\times 10^5$

## 题解

令 $s$ 为 $a$ 的前缀和，那么所求即为有多少对 $(l,r),0\le l< r \le  n$ 满足
$$
(s_r-s_{l})\mid (r-l)
$$

整除问题，没有入手点，考虑根号分治：设 $d=\frac{r-l}{s_r-s_l}$，设阈值为 $B$

- 当 $d\le B$ 时

$$
ds_r-ds_{l}=r-l\\
ds_r-r=ds_l-l
$$

枚举 $d$，令 $f_i=d s_i-i$，问题转化为有多少对 $(i,j)$ 满足 $f_i=f_j$。开个桶扫一遍即可，复杂度 $O(Bn)$。

- 当 $d>B$ 时

有 $s_r-s_l\le \frac nB$ ，那么不妨枚举 $s_r-s_l$ 的值为 $k$。

维护一对双指针 $i,j$ ，$l$ 从 $1$ 向 $n$ 扫。$i$ 和 $j$ 来维护能够使得 $s_r-s_l=k$ 的 $r$ 的区间。那么在 $i$ 到 $j$ 中能够使得 $r-l$ 是 $k$ 的倍数的 $r$ 的个数就是 $\lfloor\frac {j-l}{k}-\frac{i-l}{k}\rfloor$，注意排除掉 $d\le B$ 的情况。

这一段复杂度为 $O(\frac nB\cdot n)$。

总复杂度 $O(Bn+\frac{n^2}B)$，取 $B=\sqrt n$ 时最小为 $O(n\sqrt n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Acc{
 const int N=2e5+9,M=500;
 int a[N],b[N*M],v[N];
 void work(){
  int n,d,i,x,l,r,B,C;string s;long long z=0;
  for(cin>>s,n=s.size(),i=1;i<=n;++i)a[i]=a[i-1]+s[i-1]-48;
  for(B=sqrt(n),d=1;d<=B;++d){
   for(i=0;i<=n;++i)++b[x=d*a[i]-i+n],v[i]=x;
   for(i=0;i<=n;++i)x=v[i],z+=1ll*b[x]*(b[x]-1)/2,b[x]=0; 
  }
  for(C=n/B,d=1;d<=C;++d){
   for(l=r=0,i=1;i<=n;++i){
    for(;a[l]-a[i-1]<d&&l<=n;++l);
    if(l==n+1)break;
    for(;a[r]-a[i-1]<=d&&r<=n;++r);
    if((r-i)/d>B)z+=(r-i)/d-max((l-i)/d,B);
   }
  }
  cout<<z<<'\n';
 }
}
int main(){
 ios::sync_with_stdio(0),cin.tie(0);
 return Acc::work(),0;
}
```



---

## 作者：Arghariza (赞：1)

很显然先求出前缀和 $s_i$，即求：

$$\sum\limits_{0\le l<r\le n}[(s_r-s_l)|(r-l)]$$

没有什么比较有效的 polylog 的想法，所以我们考虑根号分治。

设 $r-l=k(s_r-s_l)$，且 $k$ 为整数。对 $k$ 进行分治：

若 $k\le B$，则考虑 $O(B)$ 枚举 $k$，由于：

$$ks_r-r=ks_l-l$$

开一个桶记录 $a_i=ks_i-i$ 的出现次数即可，总复杂度 $O(nB)$。

若 $k>B$，则 $s_r-s_l<\frac{n}{B}$。枚举 $m=s_r-s_l$，这部分复杂度 $O(\frac{n}{B})$。

于是枚举左端点 $l$，双指针维护 $r$ 的范围 $[L_r,R_r]$，只需要求出满足 $r'\in [L_r,R_r]$，$m\mid (r'-l)$ 且 $r'-l>mB$ 的数的个数即可（为了避免与第一类算重）。总复杂度 $O(\frac{n^2}{B})$。

平衡一下，取 $B=\sqrt n$ 得到复杂度 $O(n\sqrt n)$。

```
#include <bits/stdc++.h>
#define eb emplace_back
#define mt make_tuple
#define mp make_pair
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef tuple<int, int, int> tu;
bool Mbe;

const int N = 2e5 + 5;
const int B = 500;

ll ans;
int n, m, s[N], a[N], ct[N * B];
char c[N];

int calc(int x, int k) {
    if (x < 0) return 0;
    return x / k + 1;
}

void solve() {
	cin >> (c + 1), n = strlen(c + 1), m = sqrt(n);
    for (int i = 1; i <= n; i++) s[i] = (c[i] == '1') + s[i - 1];
    for (int k = 1; k <= m; k++) {
        for (int i = 0; i <= n; i++) a[i] = k * s[i] - i + n, ct[a[i]]++;
        for (int i = 0; i <= n; i++) {
            if (!ct[a[i]]) continue;
            ans += 1ll * ct[a[i]] * (ct[a[i]] - 1) / 2;
            ct[a[i]] = 0;
        }
    }
    for (int k = 1; k <= m; k++) {
        for (int i = 0, l = 1, r = -1; i <= n; i++) {
            while (l <= n && s[l] - s[i] < k) l++;
            if (l == n + 1) break;
            if (r == -1) r = l;
            while (r < n && s[r + 1] - s[i] <= k) r++;
            int L = max(l - i, m * k + 1), R = r - i;
            if (L > R) continue;
            ans += calc(R, k) - calc(L - 1, k);
        }
    }
    cout << ans << '\n';
}

bool Med;
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Mbe - &Med) / 1048576.0 << " MB\n";
	#ifdef FILE
		freopen(".in", "r", stdin);
		freopen(".out", "w", stdout);
	#endif
	int T = 1;
	// cin >> T;
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}
```

---

## 作者：快斗游鹿 (赞：1)

## 思路

根号分治。

设 $s_i$ 表示 $i$ 以前 $1$ 的个数，则题意转化为对于每个区间，只要存在整数 $d$，满足 $r-l=d(s_r-s_l)$，就加入贡献。

先改写一下式子，$r-l=ds_r-ls_l$，移项得 $ds_r-r=ds_l-l$，这启发我们可以枚举 $d$，并开个桶记录每个 $ds_i-i$，统计答案时枚举每个值，若该值出现 $k$ 次，则答案累加 $\dfrac{k(k-1)}{2}$。因为不同的值一定不超过 $n$ 个，所以这部分时间复杂度可以做到 $O(dn)$。

式子也可以改写成 $s_r-s_l=\dfrac{r-l}{d}$。因此我们也可以枚举 $s_r-s_l$ 的值，设为 $d$。枚举左端点，设 $pos_i$ 表示第 $i$ 个 $1$ 出现的位置，那么当左端点确定，且 $[l,r]$ 中有 $d$ 个 $1$ 时，右端点取值范围为 $[pos_{s_{l-1}+i},pos_{s_{l-1}+i+1})$，那么同样可以确定该区间内区间长度是 $d$ 的倍数的区间个数。时间复杂度 $O(\dfrac{n^2}{d})$。

在 $d$ 取 $\sqrt{n}$ 时取到最优，总时间复杂度 $O(n\sqrt{n})$。

## 代码

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
string S;
int a[N],B,ans,s[N],nxt[N],pos[N];
signed t[N*500];
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
signed main(){
	freopen("std.in","r",stdin);
	cin>>S;
	for(int i=0;i<S.length();i++)a[i+1]=S[i]-'0';
	int n=S.length();
	for(int i=1;i<=n;i++){
		s[i]=s[i-1]+a[i];
		if(a[i]==1)pos[s[i]]=i;
	}
	int B=sqrt(n);
	for(int d=1;d<=B;d++){
		for(int i=0;i<=n;i++){
			t[d*s[i]-i+n]++;
			//cout<<d*s[i]-i+n<<endl;
		}
		for(int i=0;i<=n;i++){
			int k=t[d*s[i]-i+n];
			ans+=((k*(k-1))/2);
			t[d*s[i]-i+n]=0;
		}
	}
	pos[s[n]+1]=n+1;
	//cout<<ans<<endl;
	for(int l=1;l<=n;l++){
		for(int i=1;i<=n/B;i++){
			int ra=pos[s[l-1]+i],rb=pos[s[l-1]+i+1];
			if(ra&&rb){
				ans=ans+max(0ll,(rb-l)/i-max(B,(ra-l)/i));
			}
		}
	}
	cout<<ans;
}

```


---

## 作者：tzc_wk (赞：1)

*2600 的 Div.1+Div.2 F，其实还算好，可就是 wtcl 所以想不出来啊。

求出前缀和数组 $s_i$，题目要求 $r-l+1$ 是 $s_r-s_{l-1}$ 的倍数，故我们套路地把这个比值 $\dfrac{s_r-s_{l-1}}{r-l+1}$ 设出来，记作 $t$

这样一来我们可以想到一个很暴力的做法，枚举所有 $t\in[1,n]$，记 $b_i=ts_i-i$，那么 $\dfrac{s_r-s_{l-1}}{r-l+1}=t$ 就等价于 $b_r=b_{l-1}$，用个哈希表记录 $c_x$ 为 $b_i=x$ 的 $i$ 个数，然后算出 $\sum\dbinom{c_x}{2}$ 就行了。时间复杂度平方。

但是这样做显然会炸，那有没有什么优化的方法呢？根号分治。对于 $t\leq\sqrt{n}$，直接算是没问题的。对于 $t>\sqrt{n}$，不难发现 $s_r-s_{l-1}$ 的值顶多为 $\sqrt{n}$，那么我们就转而枚举 $s_r-s_{l-1}$，假设其为 $p$。我们固定区间左端点 $l$，显然满足 $[l,r]$ 中 $1$ 的个数为 $p$ 的 $r$ 组成的集合显然是一个区间，记作 $[L,R]$，这个可以 two pointers 求出，那么现在我们就要求出有多少个 $r\in [L,R]$ 满足 $r-l+1$ 是 $p$ 的倍数，这个直接除一下就行了，注意减去 $\dfrac{s_r-s_{l-1}}{r-l+1}\leq\sqrt{n}$ 的贡献。时间复杂度线性根号。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
template<typename T> void read(T &x){
	x=0;char c=getchar();T neg=1;
	while(!isdigit(c)){if(c=='-') neg=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXN=2e5;
const int MAXT=1e8;
char s[MAXN+5];ll ans=0;
int n,a[MAXN+5],sum[MAXN+5],hst[MAXT+5],blk_sz=0;
int main(){
	scanf("%s",s+1);n=strlen(s+1);blk_sz=(int)pow(n,0.5);
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+(s[i]^48);
	for(int k=1;k<=blk_sz;k++){
		for(int i=0;i<=n;i++) a[i]=k*sum[i]-i+n;
		for(int i=0;i<=n;i++) hst[a[i]]++;
		for(int i=0;i<=n;i++) ans+=1ll*hst[a[i]]*(hst[a[i]]-1)/2,hst[a[i]]=0;
	}
	for(int k=1;k<=n/blk_sz;k++){
		int l=0,r=0;
		for(int i=1;i<=n;i++){
			while(sum[l]-sum[i-1]<k&&l<=n) l++;
			if(l==n+1) break;
			while(sum[r]-sum[i-1]<=k&&r<=n) r++;
			if((r-i)/k>blk_sz) ans+=(r-i)/k-max((l-i)/k,blk_sz);
		}
	} printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：BLuemoon_ (赞：0)

[link](https://www.luogu.com.cn/problem/CF1270F)

## 思路

考虑根号分治，令 $B=\sqrt{n}$，$s_i$ 为长度为 $i$ 的前缀中 $1$ 的数量。

设当前段 $[l,r]$ 满足条件时，$d$ 为 $r-l+1$ 与 $s_r-s_{l-1}$ 的比值。

若 $d\le B$，将式子转化，得到：$ds_r-r=ds_{l-1}-(l-1)$，那么可以枚举 $d$，求出所有 $ds_i-i$，用桶存下来后算答案，这部分时间复杂度为 $O(nB)$。

若 $d>B$，那么 $p=s_r-s_{l-1}<\frac{n}{B}$，于是可以枚举 $p$ 和区间左端点 $l$，那么可以双指针维护 $r$ 的所有可能位置即从 $l$ 开始 $1$ 的数量达到 $p$ 后的极长全 $0$ 连续段。再直接除去 $p$ 就可以了，但是需要保证 $r-l>pB$，否则就会和 $d\le B$ 算重。这部分时间复杂度为 $O(\frac{n^2}{B})$。

总时间复杂度为 $O(nB+\frac{n^2}{B})=O(n\sqrt{n})$。

## 代码

```cpp
// BLuemoon_
#include <bits/stdc++.h>
 
using namespace std;
using LL = long long;
 
const int kMaxN = 2e5 + 5, kMaxB = 455;

LL n, B, s[kMaxN], x, ans;
int cnt[kMaxN * kMaxB];
string t;
 
int main() {
  cin >> t, n = t.size(), t = ' ' + t, B = sqrt(n);
  for (int i = 1; i <= n; i++) {
    s[i] = s[i - 1] + t[i] - '0';
  }
  for (LL j = 1; j <= B; j++) {
    for (int i = 0; i <= n; i++) {
      x = j * s[i] - i + n, cnt[x]++;
    }
    for (int i = 0; i <= n; i++) {
      x = j * s[i] - i + n, ans += 1ll * (cnt[x] - 1) * cnt[x] / 2, cnt[x] = 0;
    }
  }
  for (LL j = 1; j <= B; j++) {
    for (LL i = 0, L = 1, R = -1; i <= n; i++) {
      for (; L <= n && s[L] - s[i] < j; L++) {
      }
      if (L == n + 1) {
        break;
      }
      !~R && (R = L);
      for (; R < n && s[R + 1] - s[i] <= j; R++) {
      }
      LL l = max(L - i, B * j + 1), r = R - i;
      l <= r && (ans += r / j - (l - 1) / j);
    }
  }
  cout << ans << '\n';
  return 0;
}

```

---

## 作者：沉石鱼惊旋 (赞：0)

# 题目翻译

给定长度为 $n$ 的 $\tt 01$ 串，求有多少个区间 $[l,r]$ 满足 $[l,r]$ 中 $\tt 1$ 的个数整除 $r-l+1$。

$1\leq n\leq 2\times 10^5$

# 题目思路

设 $s_i$ 表示 $[1,i]$ 的 $\tt 1$ 的个数。

那么我们就是求 $s_i-s_j \mid i-j$ 的 $(i,j)$ 个数，其中 $0\leq j\lt i\leq n$。

那么我们有 $ks_i-i=ks_j-j$。

一个很暴力的想法是枚举这些 $k$ 然后直接统计，复杂度 $\mathcal O(n^2)$ 依据实现可能多个 $\log$，不可行。

但是由于 $k$ 很大的时候那么 $s_i-s_j$ 必须很小，可以枚举这个。这两个做法一个在 $k$ 小的时候可行一个在 $k$ 大的时候可行，我们可以根号分治。设阈值为 $B$。

对于 $k\leq B$ 我们开桶维护 $ks_i-i$ 的个数。每次修改和清空都只要操作 $\mathcal O(n)$ 个位置。复杂度 $\mathcal O(Bn)$。

对于 $k\gt B$，我们有 $s_i-s_j\leq n/k$。我们枚举 $x=s_i-s_j$ 的值。枚举左端点 $j$，我们可以求出一个合法的右端点区间 $[l,r]$ 表示 $i\in [l,r]$ 之内的时候我们有 $s_i-s_j=x$。那么我们就是计数多少个 $i\in [l,r]$ 满足 $x\mid i-j$。这个也是简单的，注意一下一些边界问题，比如要扔掉 $x\mid i-j \land \frac{i-j}{x}\leq B$ 的情况。

# 完整代码

<https://codeforces.com/contest/1270/submission/306965657>

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int B = 450;
int n;
string str;
int h[100000020];
int s[200020];
ll ans;
int main()
{
    cin >> str;
    n = str.size();
    str = ' ' + str;
    for (int i = 1; i <= n; i++)
        s[i] = s[i - 1] + (str[i] ^ '0');
    for (int d = 1; d <= B; d++)
    {
        for (int i = 0; i <= n; i++)
        {
            int x = d * s[i] - i + n;
            ans += h[x]++;
        }
        for (int i = 0; i <= n; i++)
        {
            int x = d * s[i] - i + n;
            h[x] = 0;
        }
    }
    for (int d = 1; d <= B; d++)
    {
        int l = 1, r = 0;
        for (int i = 1; i <= n; i++)
        {
            while (l <= n && s[l] - s[i - 1] < d)
                l++;
            while (r + 1 <= n && s[r + 1] - s[i - 1] <= d)
                r++;
            ans += max(0, (r - i + 1) / d - max((l - i) / d, B));
        }
    }
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：int08 (赞：0)

## 前言
这是我本来 TLE 的代码：

```cpp
for(i=1;i<=cnt;i++)
	for(j=i;j<=min(cnt,j+399);j++)
```

一键查询精神状态。
# Solution
首先显然有 $O(n^2)$ 的暴力做法（枚举左右端点），不过由于没有很好利用倍数的性质，似乎不好优化。

从另一个角度，枚举倍数试试：先特判掉全 $1$ 的情况，现在我们可以枚举 $0$ 是 $1$ 的 $x$ 倍，这时候有一个方案：将 $0$ 权值记为 $-1$，$1$ 权值记为 $x$，一个子串合法当且仅当权值和为 $0$，可以用桶记录前缀和中某个数出现次数，快速计算。

虽然还是 $O(n^2)$ 的，但是感觉 $x$ 较高时候有优化的前途。

关于倍数一般有两种优化方案：调和级数 $O(n\ln n)$，根号分治 $O(n\sqrt n)$，本题中由于~~时限异常宽松~~固定 $0,1$ 数量不好计数，考虑根号分治。

那我们看一下当 $x>\sqrt n$ 的时候有没有什么特点。

发现了！特点是 $1$ 不超过 $\sqrt{n}$ 个。

利用这个性质，记录下所有 $1$，枚举子串的左端点和最右侧的 $1$，右应该会有一些 $0$ 可以扩展，如果能 $O(1)$ 求出合法的扩展方案数就好了。

于是现在解决这样的问题：有 $x$ 个 $0$，$y$ 个 $1$，还有 $a$ 个 $0$ 在最右侧可选可不选，求 $[x,x+a]$ 中有多少个数是 $y$ 的倍数且倍数大于 $\sqrt n$（否则和前面算重）。

这个显然可以 $O(1)$ 求，于是做完了，复杂度 $O(n\sqrt n)$。

闲话：我的代码实际上枚举的是最左和最右的 $1$，这样也可以做，但是需要求解两个等差数列，复杂很多。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
string s;
#define N 200005
int cnt,one[N];
int n,i,j,ans;
signed tong[N*500];
const int T=500;
signed main()
{
	cin>>s;n=s.length();s='#'+s;
	int combo=0;
	for(i=1;i<=n;i++) if(s[i]=='1') one[++cnt]=i,ans+=++combo;
	else combo=0;
	one[0]=0,one[cnt+1]=n+1;
	for(i=1;i<T;i++)
	{
		int val=n;tong[n]++;
		for(j=1;j<=n;j++) if(s[j]=='1') val+=i,ans+=tong[val]++;
		else val--,ans+=tong[val]++;
		val=n;tong[n]=0;
		for(j=1;j<=n;j++) if(s[j]=='1') val+=i,tong[val]=0;
		else val--,ans+=tong[val]=0;
	}
	if(n<=T) cout<<ans,exit(0);
	for(i=1;i<=cnt;i++)
		for(j=i;j<=min(cnt,i+399);j++)
		{
			int o=j-i+1,z=one[j]-one[i]+1-o,le=one[i]-one[i-1]-1,re=one[j+1]-one[j]-1;
			if(!le&&!re)
			{
				if(z%o==0&&z/o>=T) ans++;
				continue;
			}
			if(le<re) swap(le,re);
			int l=z,r=z+re-1;
			l=max(T,(l+o-1)/o)*o;r=r/o*o;
			if(l<=r)
			{
				int sx=l-z+1,mx=r-z+1,xs=(r-l)/o+1;
				ans+=(sx+mx)*xs/2;
			}
			l=z+re,r=z+le;
			l=max(T,(l+o-1)/o)*o;r=r/o*o;
			if(l<=r)
			{
				int xs=(r-l)/o+1;
				ans+=(re+1)*xs;
			}
			l=z+le+1,r=z+le+re;
			l=max(T,(l+o-1)/o)*o;r=r/o*o;
			if(l<=r)
			{
				int sx=(z+le+re)-r+1,mx=(z+le+re)-l+1,xs=(r-l)/o+1;
				ans+=(sx+mx)*xs/2;
			}
		}
	cout<<ans;
	return 0;
 } 
```
# The End.

---

## 作者：Nelofus (赞：0)

变量过多有点难受，考虑枚举去掉一维，枚举区间长度和区间 $1$ 的个数都不好，那考虑枚举倍数 $d$，对每个 $d$ 计算
$$
r-l=d(pre_{r}-pre_{l})
$$
的个数，这里的 $0\le l<r\le n$，也就是用 $l$ 代替了 $l-1$。

把相同的移到同一侧
$$
r-d\cdot pre_r=l-d\cdot pre_l
$$
这个时候就有复杂度 $\mathcal O(n^2)$ 的做法了。

考虑优化，第一个式子有：
$$
\frac{r-l}{d}=pre_{r}-pre_{l}
$$
这告诉我们在 $d$ 大的时候满足条件的区间 $1$ 的个数不多，启示我们按阈值分治。设阈值为 $B$，对 $d\le B$ 的第一部分用第二条式子的方式进行处理，复杂度 $\mathcal O(nB)$，如果是按 $x-d\cdot pre_{x}$ 排序则是 $\mathcal O(nB\log n)$。

对于 $d> B$ 的第二部分，每个区间的 $1$ 的个数 $\le \frac{n}{B}$，枚举区间 $1$ 的个数 $p$ 以及左端点 $l$，预处理一下前缀和 $=x$ 的区间的左右端点，可以 $\mathcal O(1)$ 找到一个 $pre_r-pre_{l}=x$ 的右端点区间。假设这个区间是 $[sl, sr]$，那么贡献就是
$$
\left\lfloor\frac{sr-l+1}{p}\right\rfloor-\max\left(\left\lfloor\frac{sl-l}{p}\right\rfloor,B\right)
$$
后面与 $B$ 取 $\max$，是因为有一些答案对应的是 $d\le B$ 的情况，会重复计数，需要去掉。
```cpp
// Narcissus & どうか安寧な記憶を

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;

//{{{星光闪耀
template<typename Ta, typename Tb>
inline void chkmax(Ta &a, const Tb &b) {if (a < b)	a = b;}
template<typename Ta, typename Tb>
inline void chkmin(Ta &a, const Tb &b) {if (a > b)	a = b;}
//}}}

constexpr int N = 2e5 + 10;
int n;
std::string s;
int pre[N];
int divide;
std::unordered_map<int, int> cnt;
std::pair<int, int> seg[N];

std::random_device seed;
std::mt19937_64 rng(seed());

int main() {
	std::cin >> s;
	n = s.length();
	s = ' ' + s;
	for (int i = 1; i <= n; i++)
		pre[i] = pre[i - 1] + (s[i] == '1');

	divide = std::min(100, n);
	i64 ans = 0;

	for (int k = 1; k <= divide; k++) {
		cnt.clear();
		for (int i = n; i >= 0; i--) {
			int tval = i - k * pre[i];
			ans += cnt[tval];
			cnt[tval]++;
		}
	}

	for (int i = 0; i <= n; i++)
		seg[i] = std::make_pair(n, 0);
	// 求每个值的区间
	for (int i = 0; i <= n; i++) {
		chkmin(seg[pre[i]].first, i);
		chkmax(seg[pre[i]].second, i);
	}

	for (int d = 1; d <= n / divide; d++) {
		for (int i = 1; i <= n; i++) {
			const auto &[sl, sr] = seg[pre[i - 1] + d];
			if (sl > sr)
				break;
			if ((sr - i + 1) / d > divide)
				ans += (sr - i + 1) / d - std::max((sl - i) / d, divide);
		}
	}
	std::cout << ans << '\n';
	return 0;
}
```

---

## 作者：zcxxnqwq (赞：0)

设表示 $1$ 的个数的前缀和数组为 $s$，题意就是求有多少对 $(l,r)$，使得存在 $k$ 满足 $r-(l-1)=k(s_r-s_{l-1})$，移个项再令 $l\gets l-1$，即有多少对 $l<r$，满足 $ks_r-r=ks_l-l$。

朴素地枚举 $k$ 再枚举点是 $O(n^2)$ 的，观察这个柿子的性质，发现 $k$ 比较大的时候区间内 $1$ 的个数就很小了，于是可以根号分治一波：

- 对于 $k\le\sqrt n$，暴力枚举，用桶存一下（易知值域是 $O(n\sqrt n)$ 的），时间复杂度 $O(n\sqrt n)$。

- 对于 $k>\sqrt n$，$1$ 的个数 $<\sqrt n$，预处理每个位置下一个 $1$ 在哪，然后暴力枚举区间起点和 $1$ 的个数，时间复杂度 $O(n\sqrt n)$。

感觉想到了根号分治以后就很呆呆了。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define rep(i,s,e) for(int i=(s);i<=(e);++i)
#define Rep(i,s,e) for(int i=(e);i>=(s);--i)
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}
const int N=2e5+5,M=sqrt(N)*N;
int n,sum[N],tong[M+N],a[N],nxt[N],m;
char s[N];
signed main(){
    scanf("%s",s+1),n=strlen(s+1),m=sqrt(n);
    rep(i,1,n) sum[i]=sum[i-1]+(s[i]=='1'),a[i]=n-i;
    ll ans=0,tmp;a[0]=n;
    rep(j,1,m){
        rep(i,0,n) a[i]+=sum[i],ans+=tong[a[i]],++tong[a[i]];
        rep(i,0,n) tong[a[i]]=0;
    }
    int pos=n+1;
    Rep(i,0,n){
        nxt[i]=pos;
        if(s[i]=='1') pos=i;
    }
    rep(i,0,n-1){
        for(int l=nxt[i],r=nxt[l]-1,k=1;k<=n/m&&l<=n;++k,l=nxt[l],r=nxt[l]-1){
            int ql=max(l-i,(m+1)*k),qr=r-i;
            if(ql>qr) continue;
            ans+=qr/k-(ql-1)/k;
        }
    }
    printf("%lld\n",ans);
}

```

---

