# Little Elephant and LCM

## 题目描述

The Little Elephant loves the LCM (least common multiple) operation of a non-empty set of positive integers. The result of the LCM operation of $ k $ positive integers $ x_{1},x_{2},...,x_{k} $ is the minimum positive integer that is divisible by each of numbers $ x_{i} $ .

Let's assume that there is a sequence of integers $ b_{1},b_{2},...,b_{n} $ . Let's denote their LCMs as $ lcm(b_{1},b_{2},...,b_{n}) $ and the maximum of them as $ max(b_{1},b_{2},...,b_{n}) $ . The Little Elephant considers a sequence $ b $ good, if $ lcm(b_{1},b_{2},...,b_{n})=max(b_{1},b_{2},...,b_{n}) $ .

The Little Elephant has a sequence of integers $ a_{1},a_{2},...,a_{n} $ . Help him find the number of good sequences of integers $ b_{1},b_{2},...,b_{n} $ , such that for all $ i $ $ (1<=i<=n) $ the following condition fulfills: $ 1<=b_{i}<=a_{i} $ . As the answer can be rather large, print the remainder from dividing it by $ 1000000007 $ $ (10^{9}+7) $ .

## 样例 #1

### 输入

```
4
1 4 3 2
```

### 输出

```
15
```

## 样例 #2

### 输入

```
2
6 3
```

### 输出

```
13
```

# 题解

## 作者：xtx1092515503 (赞：4)

# [Portal](https://www.luogu.com.cn/problem/CF258C)

因为 $\operatorname{lcm}\{b_i\}=\max\{b_i\}$ 它等价于所有的 $b_i$ 都是 $\max\{b_i\}$ 的因数，所以我们可以构思出如下的算法：

我们从 $1$ 到 $\max\{a_i\}$ 枚举 $\max\{b_i\}$，设一个值 $i$ 表示它。然后，我们求出 $i$ 的所有因数，并将其从小到大排序。设排完序后我们得到了 $p_1,p_2,\dots,p_m$。

则我们枚举每段间隙 $[p_1,p_2),[p_2,p_3),\dots,[p_{m-1},p_m),[p_m,\max\{a_i\}]$，并求出每段间隙中有多少个 $a$ 中的数。则间隙 $[p_k,p_{k+1})$ 中的每一个数，都有 $k$ 种不同的取值（即 $p_1\sim p_k$），答案乘上 $k^{num}$，其中 $num$ 是个数。

但是需要特判的是最后一个间隙 $[p_m,\max\{a_i\}]$，它里面每个数都有 $m$ 种不同取值，但是必须保证**至少有一个数**取到了 $p_m$。故这里乘上的应是 $m^{num}-(m-1)^{num}$。

关于如何求出每段间隙的 $num$，这个可以通过将 $a$ 排序后在里面二分求出，但这样要多一个 $\log$；另一个方法是通过 two-pointers+前缀和求出，是 $O(1)$ 的，可以参见代码。

最后是复杂度分析。显然它的复杂度应是 $O(\sum\limits_{i=1}^{\max\{a_i\}}d_i)$ 的，其中 $d_i$ 是因数个数。乍一看这是 $O(n\sqrt{n})$ 的，但实际上是 $O(n\log n)$ 的，因为关于每个因数的贡献分析后会发现它就等于调和级数。

$O(n\sqrt{n})$ 的做法是对于每个 $i$ 都 $\sqrt{i}$ 地暴力求出因数；而 $O(n\log n)$ 的做法是预处理因数（某个数 $i$ 是所有形如 $\alpha i$ 的数的因数，而 $\alpha\in[1,\dfrac{\max\{a_i\}}{i}]$）。这里为了方便是 $O(n\sqrt{n})$ 的方法。

[代码戳这儿](https://www.luogu.com.cn/record/37523282)

---

## 作者：chenxia25 (赞：2)

这题就属于随便做的题目了吧（

> [洛谷题目页面传送门](https://www.luogu.com.cn/problem/solution/CF258C) & [CF 题目页面传送门](http://codeforces.com/contest/258/problem/C)

> 题意见洛谷里的翻译。

注意到，所有数的 LCM 等于最大值，可以转化为每个数都是最大值的因数。

考虑枚举最大值，显然最大值不同的序列 $b$ 一定是不同的，于是它们互相独立，算了之后加起来即可。

先不考虑「需要有一个数等于当前枚举的最大值」这个条件，那么每个位置 $i$ 的 $b_i$ 取值数量就是当前枚举的最大值的因数中 $\leq a_i$ 的数量。这个只需要，一开始将 $a$ 排序，然后枚举当前最大值的因数一通 `lower_bound`，确定出取值数量为每个数时的区间，然后快速幂乘到当前答案中即可。

现在来考虑「需要有一个数等于当前枚举的最大值」这个条件。那只需要减去不满足的即可，跟上面类似算，只不过取值数量等于当前枚举的最大值的因数数量的数的取值数量都要减一。

这样，总因数个数是调和级数，$\mathrm O(n\log n)$。`lower_bound` 的话，可以 two-pointers 预处理出来，变成 $\mathrm O(n)$；至于快速幂，就避免不了了。所以复杂度 $\mathrm O\!\left(n\log^2n\right)$（那么对于 `lower_bound` 的预处理优化其实是徒劳），ymx 说是 1log 的，不知道他啥心态（大雾

或者有人会 1log 的做法可以评论哦，反正我逛了一圈没有。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
const int mod=1000000007;
int qpow(int x,int y){
	int res=1;
	while(y){
		if(y&1)res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return res;
}
int inv(int x){return qpow(x,mod-2);}
const int N=100000,A_I=100000;
int n;
int a[N+1];
int lwb[A_I+1];
vector<int> dsr[A_I+1];
int main(){
	freopen("a.in","r",stdin);freopen("a.out","w",stdout);
	cin>>n;
	int mx=0;
	for(int i=1;i<=n;i++)scanf("%d",a+i),mx=max(mx,a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=mx;i++){
		lwb[i]=lwb[i-1]-1;
		while(lwb[i]+1<=n&&a[lwb[i]+1]<i)lwb[i]++;
		lwb[i]++;
	}
	for(int i=1;i<=mx;i++)for(int j=i;j<=mx;j+=i)dsr[j].pb(i);
	int ans=0;
	for(int i=1;i<=mx;i++){
		int prod=1;
		for(int j=0;j<dsr[i].size();j++){
			int l=lwb[dsr[i][j]],r=j+1==dsr[i].size()?n:lwb[dsr[i][j+1]]-1;
			prod=1ll*prod*qpow(j+1,r-l+1)%mod;
			if(j+1==dsr[i].size())(ans+=(prod-1ll*prod*inv(qpow(j+1,r-l+1))%mod*qpow(j,r-l+1)%mod)%mod)%=mod;
		}
//		cout<<ans<<"!\n";
	}
	cout<<(ans+mod)%mod<<"\n";
	return 0;
}
```

---

## 作者：Miracle_1024 (赞：1)

### 分析：

枚举最大数，然后找出它所有因数 $a_i\cdots p_k$，从中任意选取一些数，这些数的 $\operatorname{lcm}$ 或这个数且，这些数的最大 $\operatorname{lcm} $ 就是枚举的这个数，且若$p_i \le a_j \le p_i+1$ 则前 $i$ 个数可以放在 $j$ 这个位置，即 $j$ 这个位置有$cj$ 种选择，总方案数就是 $c_1\times c_2\times \cdots \times c_j$。

作为优化，对于每个 $p_i$，我们枚举有 $aj$ 满足 $p_i \le a_j \le p_i+1$ 的个数记为 $q_i$。

但这些方案包含不选择最大数的情况，则最后一项应为 $q^qk-(q-1)^qk$。

### 代码：

```
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
#define MAXN 100000
#define MOD 1000000007
long long a[MAXN+10],n,p[MAXN+10],cnt,ans;
void Read(long long &x){
    char c;
    while((c=getchar())&&c!=EOF){
        if(c>='0'&&c<='9'){
            x=c-'0';
            while((c=getchar())&&c>='0'&&c<='9')
                x=x*10+c-'0';
            ungetc(c,stdin);
            return;
        }
    }
}
void isfactor(long long n){
    long long t=sqrt(n+0.5),i;
    cnt=0;
    for(i=1;i<=t;i++)
        if(n%i==0)
            p[++cnt]=i;
    i=cnt;
    cnt*=2;
    if(t*t==n)
        cnt--,i--;
    for(;i;i--){
        p[cnt-i+1]=n/p[i];
    }
}
long long pow(long long a,long long b){
    long long ret=1;
    while(b){
        if(b&1)
            ret=ret*a%MOD;
        b>>=1;
        a=a*a%MOD;
    }
    return ret;
}
int main()
{
    long long i,j,k,t,s;
    Read(n);
    for(i=1;i<=n;i++)
        Read(a[i]);
    sort(a+1,a+n+1);
    for(i=1;i<=a[n];i++){
        isfactor(i);
        t=0;
        s=1;
        for(j=2;j<=cnt;j++){
            k=lower_bound(a+t+1,a+n+1,p[j])-a-1;
            s=s*pow(j-1,k-t)%MOD;
            t=k;
        }
        s=s*(pow(cnt,n-t)+MOD-pow(cnt-1,n-t))%MOD;         
        ans=(ans+s)%MOD;
    }
    printf("%I64d\n",ans);
}
```


---

## 作者：Coros_Trusds (赞：1)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15996770.html)

$\verb!upd:!$ 之前逻辑有点错误，修改一下。

花了 ** 三天又$4$ 个小时在这道题上才理解。。。

修改是半个月之后。

# 题目大意

对于一个数组 $a$,有数组 $b$ 使得 $b_i\le a_i$ 并且 $b$ 中所有数的最小公倍数等于 $b$ 中所有数字的最大值，求这样的数组 $b$ 的个数 $\bmod 10^9+7$.

# 题目分析

因为 $b$ 数组的最大值等于 $\operatorname{lcm}\{b_i\}$，所以 $b$ 数组所有数一定为 $\max\{b_i\}$ 的因子。又因为 $\forall i,b_i\le a_i$，所以可以枚举 $b$ 数组的最大数，范围从 $1$ 到 $\max\{a_i\}$。

因为 $a$ 数组的顺序不会对答案有影响，所以我们将 $a$ 数组升序排列，对于枚举的 $i=\max\{b\}$，遍历 $i$ 所有因子，从小到大记为 $divi_0,divi_1,\cdots,divi_{m-1}$，通过二分找出 $a$ 序列中小于 $divi_j,j\in [0,m-1]$ 的位置 $at$，计算贡献即可。

枚举间隙 $[divi_0,divi_1),[divi_1,divi_2),\cdots,[divi_{m-3},divi_{m-2}),[divi_{m-2},divi_{m-1}),[divi_{m-1},\max\{a_i\}]$。

对于前面的一堆左闭右开区间 $[divi_j,divi_{j+1}),j\in [0,m-2]$，单看一个的贡献为 $num$ 个 $j+1$ 的积（$j+1$ 即 $divi_0,divi_1,\cdots,divi_j,divi_{j+1}$ 这些可能的因数个数），即 $(j+1)^{num}$（$num$ 表示区间内有多少个 $a$ 序列中的数），如果不是很清楚下面会解释。对于最后一个闭区间，区间内每个数都有 $m$ 种取值，但我们必须有一个数取到了 $\max\{a_i\}$，此时贡献为 $m^{num}-(m-1)^{num}$。

举个例子：`1 2 3 4`。枚举最大值，比如说是 $4$，$a$ 序列中包含 $4$ 的因子为 $1,2,4$，此时方案数就为 $1\times 2\times 2\times (4-3)=4$。

------

可以利用 `vector` $\mathcal{O(max_{a_i}\log max_{a_i})}$ 预处理出 $1\sim max_{a_i}$ 的因数。幂运算快速幂就够了。

总时间复杂度为 $\mathcal{O(n\log^2n)}$。

# 代码

```cpp
//2022/3/11
//2022/3/12
//2022/4/3
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#include <vector>
#define int long long
#define enter() putchar(10)
#define debug(c,que) cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) cout << arr[i] << w;
#define speed_up() cin.tie(0),cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define Abs(x) ((x) > 0 ? (x) : -(x))
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if (x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;
using namespace std;

const int ma = 1e5 + 5;
int a[ma];
vector<int>divi[ma];
int n;
inline void init() {
	for (register int i = 1;i <= 1e5; ++ i) {
		for (register int j = i;j <= 1e5;j += i) {
			divi[j].push_back(i);
		}
	}
	for (register int i = 1;i <= 1e5; ++ i) sort(divi[i].begin(),divi[i].end());
}
inline int ksm(int n,int m,int p) {
	int res = 1;
	for(;m;m >>= 1ll) {
		if (m & 1ll) res = res * n % p;
		n = n * n % p;
	}
	return res % p;
}
#undef int
int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	#define int long long
	init();
	n = read();
	for (register int i = 1;i <= n; ++ i) a[i] = read();
	sort(a + 1,a + n + 1);
	int ans = 0;
	for (register int i = 1;i <= a[n]; ++ i) {
		int prod = 1,cnt = divi[i].size();
		for (register int j = 0;j < cnt - 1; ++ j) {
			int num = lower_bound(a + 1,a + n + 1,divi[i][j + 1]) - lower_bound(a + 1,a + n + 1,divi[i][j]);
			prod = MOD(prod * ksm(j + 1,num,mod));
		}
		int num = lower_bound(a + 1,a + n + 1,a[n] + 1) - lower_bound(a + 1,a + n + 1,divi[i][cnt - 1]);
		prod = MOD(prod * MOD(ksm(cnt,num,mod) - ksm(cnt - 1,num,mod)));
		ans = MOD(ans + prod);
	}
	printf("%lld\n",ans);

	return 0;
}
```

---

