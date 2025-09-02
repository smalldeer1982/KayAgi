# Shuffle

## 题目描述

You are given a binary string (i. e. a string consisting of characters 0 and/or 1) $ s $ of length $ n $ . You can perform the following operation with the string $ s $ at most once: choose a substring (a contiguous subsequence) of $ s $ having exactly $ k $ characters 1 in it, and shuffle it (reorder the characters in the substring as you wish).

Calculate the number of different strings which can be obtained from $ s $ by performing this operation at most once.

## 说明/提示

Some strings you can obtain in the first example:

- to obtain 0110110, you can take the substring from the $ 1 $ -st character to the $ 4 $ -th character, which is 1100, and reorder its characters to get 0110;
- to obtain 1111000, you can take the substring from the $ 3 $ -rd character to the $ 7 $ -th character, which is 00110, and reorder its characters to get 11000;
- to obtain 1100101, you can take the substring from the $ 5 $ -th character to the $ 7 $ -th character, which is 110, and reorder its characters to get 101.

In the second example, $ k = 0 $ so you can only choose the substrings consisting only of 0 characters. Reordering them doesn't change the string at all, so the only string you can obtain is 10010.

## 样例 #1

### 输入

```
7 2
1100110```

### 输出

```
16```

## 样例 #2

### 输入

```
5 0
10010```

### 输出

```
1```

## 样例 #3

### 输入

```
8 1
10001000```

### 输出

```
10```

## 样例 #4

### 输入

```
10 8
0010011000```

### 输出

```
1```

# 题解

## 作者：xzzduang (赞：12)

[传送门](https://codeforces.com/problemset/problem/1622/D)

这题发现用 dp 不好处理，于是考虑怎么处理掉本质不同这个限制，就有了一个很妙的办法，我们只关注最终的序列，并不关注在哪个区间操作了，所以可以枚举值发生变化的第一个位置 $i$ 和最后一个位置 $j$ 。发现对于不同的 $i,j$ ，最终的序列是肯定不相同的，因为 $i,j$ 这两个位置的值是一定改变了的。

现在我们处理好了本质不同这个限制，我们还要满足对于 $k\in[i,j],a_k$​ 中的 1 的个数不能超过 $k$​ ，且全局中 1 的个数要大于等于 $k$​  ，这使得这一对 $i,j$​ 是合法的。$i,j$​ 中间的 01 可以随意填，$a_i,a_j$​ 要强制改变，方案数为 $\binom{c_0+c_1}{c_0}$​ ，$c_0,c_1$​ 代表可填的 0,1 的个数。

时间复杂度 $O(n^2)$ 。

```cpp
#include<iostream>
#include<stdio.h>
#include<ctype.h>
#define N 5005
#define mo 998244353
using namespace std;
inline int read(){
	int x=0,f=0; char ch=getchar();
	while(!isdigit(ch)) f|=(ch==45),ch=getchar();
	while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return f?-x:x;
}
inline int read01(){
	char ch=getchar();
	while(ch!='0' && ch!='1') ch=getchar();
	return (ch=='1');
}
int n,k,a[N],C[N][N],ans=1,sum;
inline void red(int &x){x>=mo?x-=mo:0;}
int main(){
	n=read(),k=read();
	for(int i=1;i<=n;++i) a[i]=read01(),sum+=a[i];
	if(sum<k) return puts("1")&0;
	C[0][0]=1;
	for(int i=1;i<=n;++i){
		C[i][0]=1;
		for(int j=1;j<=i;++j){
			red(C[i][j]=C[i-1][j-1]+C[i-1][j]);
		}
	}
	for(int i=1;i<=n;i++){
		int cnt=a[i];
		int c0=0,c1=0;
		if(a[i]==1) c0--,c1++;
		else c1--,c0++;
		for(int j=i+1;j<=n;++j){
			c0+=(a[j]==0),c1+=(a[j]==1);
			cnt+=a[j];
			if(cnt>k) break;
			int cc0=c0,cc1=c1;
			if(a[j]) cc0--;
			else cc1--;
			if(cc0>=0 && cc1>=0) red(ans+=C[cc0+cc1][cc0]);
		}
	}
	cout<<ans;
	return 0;
}

```



---

## 作者：TKXZ133 (赞：6)

[Shuffle](https://www.luogu.com.cn/problem/CF1622D)

### 题目大意

给定一个长度为 $n$ 的 01 序列 $a$，你可以进行至多一次以下操作：

- 选定 $a$ 的一个连续段，满足连续段内恰好有 $k$ 个 $1$，将该连续段任意排列。

问能产生多少种不同的 01 序列。

### 思路分析

（这题 $n$ 完全可以开到 $10^6$ 或是 $10^7$，因为存在 $O(n)$ 的做法。）

考虑 DP。

设 $f_i$ 表示只考虑 $1\sim i$ 中的字符，能产生多少种不同的 01 序列。

那么可以列出 DP 方程：

$$f_i=\begin{cases}f_{i-1}+{m-1\choose k-1}&s_i=0\\f_{i-1}+{m-1\choose k}&s_i=1\end{cases}$$

其中，$m$ 是 $i$ 往左的极长 $k$ 个 $1$ 的连续段的长度。

解释一下：

我们在考虑 $f_{i-1}$ 时，是把 $s_i$ 恒定为 $s_i$ 做的，而在考虑 $f_i$ 时为了避免算重，我们强制钦定在 $i$ 的位置放 $s_i$ 的相反的数，也就是说，若 $s_i=0$，我们强制这个位置放 $1$，那么方案数就是 ${m-1\choose k-1}$，在前 $m-1$ 个位置上放剩下的 $k-1$ 个数。$s_i=1$ 类似。

注意初值，当 $m$ 第一次存在时，$f_i={m\choose k}$，这是因为 $f_i$ 前面没有人算它的重。

实现方式有很多种，我使用了二分实现，时间复杂度为 $O(n\log n)$。

### 代码

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <set>

using namespace std;
const int N = 1001000, L = 1000000, mod = 998244353;
#define inf 0x3f3f3f3f
#define int long long

int n, k, ans;
int fac[N], inv[N], sum[N];

set <int> S;

char s[N];

int q_pow(int a, int b){
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int C(int n, int m){
    if (n < m) return 0; 
    return fac[n] * inv[n - m] % mod * inv[m] % mod;
}

int find(int s, int k){ // 找到从 s 往左的第 k + 1 个 1 的位置的右边
    if (sum[s] < k) return inf;
    int l = 1, r = s, ans = 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (sum[s] - sum[mid - 1] <= k) r = mid - 1, ans = mid;
        else l = mid + 1;
    }
    return *(--S.lower_bound(ans)) + 1;
}

signed main(){
    fac[0] = 1;
    for (int i = 1; i <= L; i ++) fac[i] = fac[i - 1] * i % mod;
    inv[L] = q_pow(fac[L], mod - 2);
    for (int i = L; i >= 1; i --) inv[i - 1] = inv[i] * i % mod;
    scanf("%lld %lld", &n, &k);
    scanf("%s", s + 1);
    for (int i = 1; i <= n; i ++) sum[i] = sum[i - 1] + (s[i] == '1');
    S.insert(0);
    for (int i = 1; i <= n; i ++) if (s[i] == '1') S.insert(i);
    int flag = 0;
    for (int i = 1; i <= n; i ++) {
        if (sum[i] == k && !flag) ans = (ans + C(i, k)) % mod, flag = 1;
        else ans = (ans + C(i - find(i, k), k - (s[i] == '0'))) % mod;
    }
    if (!flag) ans = 1;
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：Tyyyyyy (赞：6)

# CF1622D
### 题意简述
给定一个长为 $n$ 的 $\text{01}$ 串，你可以进行以下操作**最多一次**：

选定一个**恰好**包含 $k$ 个 $\text{1}$ 的**子串**，并将其**任意重排**。其中，$k$ 是给定的常数。

求你最多能变换出多少种不同的字符串。答案对 $998244353$ 取模。

$1\leq n\leq 5000,0\leq k\leq n$。

### 题目分析
首先，为了方便讨论，我们选择的子串一定是**极长的**，即不能再扩展的子串。证明显然，因为包含某个短串的串的变换方案一定包含了所有该短串的变换方案。

我们先不考虑算重的情况，则设当前的极长字串内 $\text{1}$ 的个数为 $cnt$，子串长度为 $len$，则该子串的变换方案为 $C_{len}^{cnt}$ 种。

接下来我们考虑什么时候会算重复。设有两个相邻的极长子串 $[l_1,r_1],[l_2,r_2]$，且满足 $l_1<l_2<r_1<r_2$。那么它们的变换方案会产生重复，当且仅当 $[l_1,l_2),(r_1,r_2]$ 中的 $\text{1}$ 保持原位。读者可以自己写下样例的所有方案来理解。

也就是说，对于这样的两个子串，设 $[l_2,r_1]$ 中有 $cnt$ 个 $\text{1}$，则重复的方案数为 $C_{r_1-l_2+1}^{cnt}$。

因此，我们只需要找到所有的极长子串，再进行上述的计算即可。注意因为可以不进行操作，所以上述的方案数应当减去 $1$（不变的情况），最后再给答案加上 $1$ 即可。

Code：
```cpp
#include<bits/stdc++.h>
#define int long long
const int mod=998244353;
using namespace std;
int n,k,ans,jc[5010],inv[5010],a[5010];
char s[5010];
int power(int x,int y)
{
	int t=1;
	while(y)
	{
		if(y&1)t=1ll*t*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return t;
}
vector<pair<int,int> >v;
signed main()
{
	scanf("%lld%lld",&n,&k);
	scanf("%s",s+1);
	if(k<1){printf("1");return 0;}
	for(int i=1;i<=n;i++)a[i]=a[i-1]+(s[i]=='1');
	jc[1]=inv[1]=jc[0]=inv[0]=1;
	for(int i=2;i<=n;i++)jc[i]=1ll*jc[i-1]*i%mod,inv[i]=power(jc[i],mod-2);
	for(int i=1;i<=n;i++)
	{
		if(s[i-1]=='0')continue;
		int j,l;
		for(j=i,l=0;j<=n;j++)
		{
			if(s[j]=='1'&&l==k)break;
			if(s[j]=='1')l++;
		}
		if(l<k)break;
		if(s[j]=='1'||j>n)j--;
		if(i>j)continue;
		int len=j-i+1;
		ans=(ans+1ll*jc[len]*inv[k]%mod*inv[len-k]%mod-1+mod)%mod;
		v.push_back({i,j});
		if(j==n)break;
	}
	for(int i=1;i<(int)v.size();i++)
	{
		int l=v[i].first,r=v[i-1].second;
		if(l>r)continue;
		int cnt=a[r]-a[l-1];
		if(cnt)ans=(ans-1ll*jc[r-l+1]*inv[cnt]%mod*inv[r-l+1-cnt]%mod+1+mod)%mod;
	}
	printf("%lld",(ans+1)%mod);
	return 0;
}
```

---

## 作者：This_Rrhar (赞：2)

考虑枚举结果序列 $a'$ 相对于原始序列 $a$ 发生了变化的区间 $[l,r]$，且 $a'_l\ne a_l$,$a'_r\ne a_r$，那么显然有 $\sum\limits_{i=l}^ra'_i\le k$。

由于 $(l,r)$ 可以任意变化，故区间 $[l,r]$ 的方案总数为 $C_{r-l-1}^{s}$，其中 $s$ 为 $(l,r)$ 中 $0$ 或 $1$ 的数量。

最后注意特判 $\sum\limits_{i=l}^r<k$ 的情况。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define _r return*this
#define _o &operator
namespace IO
{
	const int _S=1<<21;
	char b[_S],*p1=b,*p2=b,pb[_S],*pp=pb;
	void fl(){fwrite(pb,1,pp-pb,stdout),pp=pb;}
	struct input
	{
		char getchar(){if(p1==p2)p2=(p1=b)+fread(b,1,_S,stdin);return p1==p2?' ':*p1++;}
		input _o>>(char&num){do num=getchar();while(num==' '||num=='\n'||num=='\r'||num=='\t');_r;}
		template<typename T>input _o>>(T&x)
		{
			char c=getchar();T f=1;
			for(x=0;!isdigit(c);)(c=='-'?f=-1:1),c=getchar();
			while(isdigit(c))x=(x*10)+(c^48),c=getchar();
			x*=f;_r;
		}
		input(){}
	}in;
	long long read(){long long x;return in>>x,x;}
	struct output
	{
		void putchar(char num){*pp++=num;if(pp-pb==_S)fl();}
		output _o<<(char num){putchar(num);_r;}
		template<typename T>output _o<<(T x)
		{
			if(!x){putchar(48);_r;}
			if(x<0)putchar('-'),x=-x;
			int s[64],t=0;
			while(x)s[++t]=x%10,x/=10;
			while(t)putchar(s[t--]+48);
			_r;
		}
		output _o<<(const char*s2){int num=0;while(s2[num])putchar(s2[num++]);_r;}
		output(){}
	}out;
	struct fe{~fe(){fl();}}fls;
}
using IO::in;
using IO::out;
using IO::read;
using ll=long long;

#define N 5001ll
#define MOD 998244353ll

ll fac[N],inv[N];
ll qpow(ll x,ll y)
{
	ll s=1;
	while(y)
	{
		if(y&1)(s*=x)%=MOD;
		(x*=x)%=MOD,y>>=1;
	}
	return s;
}
void build()
{
	fac[0]=fac[1]=1;
	for(int i=2;i<N;i++)fac[i]=fac[i-1]*i%MOD;
	inv[N-1]=qpow(fac[N-1],MOD-2);
	for(int i=N-2;i>=0;i--)inv[i]=inv[i+1]*(i+1)%MOD;
}
inline ll A(ll n,ll m){return(n<m)?0:fac[n]*inv[n-m]%MOD;}
inline ll C(ll n,ll m){return(n<m)?0:A(n,m)*inv[m]%MOD;}

ll n,k;

bool a[N];

ll l=1,r;

ll s,s0,s1;

ll ans=1;

int main()
{
	in>>n>>k,build();
	for(int i=1;i<=n;i++)s+=(a[i]=in.getchar()-'0');
	if(s<k)return out<<"1",0;
	while(l<n)
	{
		s=a[l],s0=!a[l]-a[l],s1=a[l]-!a[l],r=l+1;
		while(r<=n)
		{
			s+=a[r],s0+=!a[r],s1+=a[r];
			if(s>k)break;
			if(s0-a[r]>=0&&s1-!a[r]>=0)(ans+=C(r-l-1,s0-a[r]))%=MOD;
			r++;
		}
		l++;
	}
	out<<ans;
}
```

---

## 作者：yingkeqian9217 (赞：2)

# 前言

由于本人大脑发热，没看到 $n$ 的范围，搞了个 $O(n)$ 做法。

# 分析

下面先证几个引理，其中 $f(l,r)$，表示区间 $[l,r]$ 的排列数，定义空区间的方案数为零。

**引理 1**：$l\le r,f(l,r)={\sum_{i=l}^{ r} a_i\choose r-l+1}$。

由于原序列为 01 数列，显然。

**引理 2**：如果两个所选区间相互包含，那么只需要计算其中较大者的方案数。

考虑对整体而言，小区间的一切方案都在大区间的方案中，得证。

**引理 3**：如果 $l_1\le l_2 \le r_1 \le r2$，那么区间 $[l_1,r_2]$ 的方案数为 $f(l_1,r_1)+f(l_2,r_2)-f(l_2,r_1)$。

固定左区间 $[l_1,r_1]$，另一个区间与左区间重合的方案数即为 $f(l_2,r_1)$，那么贡献即为 $f(l_2,r_2)-f(l_2,r_1)$，得证。

**引理 3'**：如果存在区间 $l_1\le l_2 \le...\le l_k$，且两两不包含，则总区间的方案数为 $f(l_1,r_1)+\sum_{i=2}^{k}(f(l_i,r_i)-f(l_i,r_{i-1}))$。

由于两两不包含，显然 $r_1\le r_2 \le...\le r_n$，由引理 3，$k=2$ 时成立。

考虑加入区间 $[l_k,r_k]$，那么此时已经处理了 $[l_1,r_{k-1}]$，于是新区间的贡献就是 $f(l_k,r_k)-f(l_k,r_{k-1})$，得证。

------------

然后，我们就只需要知道所有满足条件的区间就能进行计算了，由于引理 1，我们只需要用尺取法，使得当前区间 $a_{l-1}=a_{r+1}=1$，同时限制 $\sum_{i=l}^{r} a_i=k$ 即可。

# code:

```cpp
#include<bits/stdc++.h>
#define maxn 2900001
#define int long long
using namespace std;
const int Mod=998244353;
int n,k,ans,a[maxn],fac[maxn],inv[maxn];
int qpow(int x,int y){
	int sum=1;
	while(y){
		if(y&1) sum=sum*x%Mod;
		x=x*x%Mod;
		y>>=1;
	}
	return sum;
}
int C(int x,int y){
	if(y<0) return 0;
	return fac[x]*inv[x-y]%	Mod*inv[y]%Mod;
}
signed main(){
	fac[0]=1;
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++) scanf("%1lld",&a[i]),fac[i]=fac[i-1]*i%Mod;
	inv[n]=qpow(fac[n],Mod-2);
	for(int i=n-1;i>=0;i--) inv[i]=inv[i+1]*(i+1)%Mod;
	int l=1,r=0,sum=0;
	while(r<=n&&sum<=k) sum+=a[++r];
	sum-=a[r--];
	if(sum!=k) return puts("1"),0;
	ans=C(r-l+1,k);
	while(l<=r&&r<=n){
		int rr=r;
		while(l<=r&&sum==k) sum-=a[l++];
		while(r<=n&&sum<=k) sum+=a[++r];
		sum-=a[r--];
		if(sum!=k||r<l) break;
		ans=(ans+(C(r-l+1,k)-C(rr-l+1,k-1)+Mod)%Mod)%Mod;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：XL4453 (赞：2)

### $\text{Difficulty : 2000}$
---
### 解题思路：

还算正常的数数题。

对于任意一个有 $cnt$ 个 $1$，且长度为 $len$ 的区间，将这个区间任意重排得到的可能区间种数共有：$C_{len}^{cnt}$。

但关键是如果直接单独考虑每一个可能的区间，会有很多重复的方案是不可取的，需要减去这些方案数。可以发现，当两个区间有交集的时候，只有当左右两个区间的独立的部分没有作出变化的时候，两个区间的交集内部的方案算重复了，所以也就是多出的方案数为两个交集的这个区间的方案数。此外，完全没有变化的情况即使没有相交的区间也会多算，所以可以先将所有的区间算出来的方案数减去 $1$，最后再补上 $1$。

实现的时候直接对于每一个位置作为起点向右拓展一下就可以了。复杂度 $O(n^2)$，不优秀，但是好写，能过。

注意预处理的时候不要漏掉 $0$ 的阶乘的逆元。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
#define int long long
int MOD=998244353;
int n,k,a[100005],A[100005],cnt,f[100005],F[100005],ll,lr,l,r,ans;
int pow(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=(ans*a)%MOD;
		a=(a*a)%MOD;
		b=b>>1;
	}
	return ans;
}
void init(){
	f[0]=1;
	for(int i=1;i<=100000;i++)f[i]=(f[i-1]*i)%MOD;
	F[100000]=pow(f[100000],MOD-2);
	for(int i=99999;i>=0;i--)F[i]=(F[i+1]*(i+1))%MOD;
}
int calc_(int cnt,int len){
	return (f[len]*(F[cnt]*F[len-cnt]%MOD))%MOD;
}
void calc(int l,int r,int ll,int lr){
	ans=(ans+calc_(k,r-l+1)-1+MOD)%MOD;
	int cnt=0,len=0;
	for(int i=l;i<=lr;i++){
		if(a[i]==1)cnt++;
		len++;
	}
	if(len==0)return;
	ans=(ans-calc_(cnt,len)+1+MOD)%MOD;
}
signed main(){
	init();
	scanf("%I64d%I64d",&n,&k);
	if(k==0){
		printf("1\n");
		return 0;
	}
	for(int i=1;i<=n;i++)scanf("%1d",&a[i]);
	for(int i=1;i<=n;i++){
		int cnt=0;
		for(r=i;r<=n;r++){
			if(a[r]==1)cnt++;
			if(cnt==k+1)break;
		}
		if(cnt<k)break;
		if(cnt==k+1||r>n)r--;
		l=i;
		calc(l,r,ll,lr);
		ll=l;lr=r;
	}
	printf("%I64d\n",(ans+1)%MOD);
	return 0;
}
```


---

## 作者：_Flame_ (赞：1)

### $\text{solution}$

数据范围允许 $n^2$ 跑过，所以很明显可以枚举要修改的第一个位置 $i$ 和最后一个位置 $j$。

然后考虑对于一个枚举出来的从 $i$ 到 $j$ 的区间，我们可以怎么修改。

显然如果我们改变了两个端点 $i$ 和 $j$ 的值，所得到的序列肯定与原来是不同的，而中间的数就可以随便填了，所以我们只要求出从 $i$ 到 $j$ 的子区间中有 $cnt1$ 个可以填的 $1$ 与 $cnt0$ 个可以填的 $0$，答案即为 $C_{cnt0}^{cnt1+cnt0}$。

$cnt1$ 与 $cnt0$ 的个数显然可以用前缀和处理出来，按照 $i$ 位置与 $j$ 位置的值分类讨论一下即可。

### $\text{code}$

```cpp
string s;
int n,k;

int l,r;

int ans=1;

int fac[maxn],inv[maxn];

void init(){
	fac[0]=1;
	for(int i=1;i<=maxn;i++){
		fac[i]=fac[i-1]*i%mod;
	}
	inv[1]=1;
	for (int i=2;i<=maxn;i++){
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	}
	inv[0]=1;
	for (int i=1;i<=maxn;i++) {
		inv[i]=inv[i-1]*inv[i]%mod;
	}
}

int C(int n,int m){
	if(n<m||n<0||m<0){
		return 0;
	}
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}

int sum[maxn];

void solve(){
	n=read(),k=read();
	cin>>s;
	s=" "+s;
	init();
	for(int i=1;i<=n;i++){
		sum[i]=(sum[i-1]+(s[i]-'0'))%mod;
//		cout<<sum[i]<<" ";
	}
//	cout<<endl;
	if(sum[n]<k){
		puts("1");
		return ;
	}
	for(int i=1;i<=n;i++){
		int cnt0=0,cnt1=0;
		for(int j=i+1;j<=n;j++){
			cnt1=sum[j]-sum[i-1];
			cnt0=(j-i+1)-cnt1;
			if(cnt1>=k+1){
				continue ;
			}
			if(s[i]=='0'&&s[j]=='0'){
				cnt1-=2;
			}
			else if((s[i]=='0'&&s[j]!='0')||(s[j]=='0'&&s[i]!='0')){
				cnt1--;
				cnt0--;
			}
			else{
				cnt0-=2;
			}
//			cout<<C(cnt1+cnt0,cnt0)<<" "<<cnt1<<" "<<cnt0<<endl;
			ans=(ans+C(cnt1+cnt0,cnt0)%mod)%mod;
		}
	}
	write(ans%mod);
	puts("");
	return ;
}

signed main(){
	//	freopen("puxi.in","r",stdin);
	//	freopen("puxi.out","w",stdout);
	int T=1;
	//	T=read();
	while(T--){
		solve();
	}
	return 0;
}

```

---

## 作者：daniEl_lElE (赞：1)

## 分析

首先，我们考虑对整个序列提炼出一个数组 $a_i$，记录第 $i$ 个 $1$ 所在的位置。

这时，我们考虑每一段长度为 $k$ 的连续的 $a$ 的子串。

对于 $a_i$ 至 $a_{i+k-1}$，我们考虑调整这一段所用的方案数。

通过推理，我们发现调整 $a_i$ 至 $a_{i+k-1}$ 的方案数其实只是要考虑将 $a_{i-1}+1$ 到 $a_{i+k}-1$ 这一段区间内所有的数排列开即可。

但是，我们发现重叠的两个区间可能会有许多方案的重复。哪些方案会让 $a_i$ 至 $a_{i+k-1}$ 和 $a_{i+1}$ 至 $a_{i+k}$ 都考虑进去呢？我们考虑这两段区间所能影响位置的交集，即 $a_i+1$ 至 $a_{i+k}-1$ 这一段区间。

那么，我们只需减去重复的 $a_i+1$ 至 $a_{i+k}-1$ 这一段区间的排列方案即可。

## 公式

$$\sum_{i=1}^{m-k+1}(C_{(a_{i+k}-1)-(a_{i-1})}^{k}-C_{(a_{i+k}-1)-(a_i)}^{k-1})$$

只需根据上述分析进行一定的组合数学推倒即可。在此我们定义 $m$ 为 $1$ 的个数，$a_0=0,a_{m+1}=n$。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
const int maxn=1000000;
int fact[maxn+5];
int inv[maxn+5];
int power(int a,int b){
	int now=a,ans=1;
	while(b){
		if(b%2==1){
			ans*=now;
			ans%=mod;
		}
		now*=now;
		now%=mod;
		b/=2; 
	}
	return ans;
}
void init(){
	fact[0]=1;
	for(int i=1;i<=maxn;i++){
		fact[i]=fact[i-1]*i;
		fact[i]%=mod;
	}
	inv[maxn]=power(fact[maxn],mod-2);
	for(int i=maxn-1;i>=0;i--){
		inv[i]=inv[i+1]*(i+1);
		inv[i]%=mod;
	}
}
int C(int i,int j){
	if(i<j){
		return 0;
	}
	return ((fact[i]*inv[j])%mod*inv[i-j])%mod;
}
signed main(){
	init();
	int n,k;
	cin>>n>>k;
	string s;
	int a[n+2],l=0;
	cin>>s;
	s=" "+s;
	for(int i=1;i<s.size();i++){
		if(s[i]=='1'){
			l++;
			a[l]=i;
		}
	}
	int ans=1;
	if(k==0){
		cout<<1<<endl;
		return 0;
	}
    a[l+1]=n+1; 
	a[0]=0;
	for(int i=k;i<=l;i++){
		int j=i-k+1;
		int dist=a[i+1]-a[j-1];
		dist-=2;
		if(i!=l) ans+=(C(a[i+1]-a[j-1]-1,k)-C(a[i+1]-a[j],k)+C(a[i+1]-a[j]-1,k)+998244353)%998244353;
		else  ans+=(C(dist+1,k)+998244352)%mod;
		ans%=mod;
	}
	cout<<ans<<endl;
	return 0;
}
```

比较有意思的一道数学类的题目吧，需要一定量的分析。

---

## 作者：Claire0918 (赞：0)

首先，对于均满足条件的 $[l_1, r_1] \sub [l_2, r_2]$，显然 $[l_1, r_1]$ 中的每一种排序 $[l_2, r_2]$ 中都可以得到，所以我们不考虑 $[l_1, r_1]$，即只考虑极大的区间。

我们对于一个 $a_i = 1$ 的 $i$，找到最小的 $l$ 和最大的 $r$ 使得 $\sum_{j = l}^{i - 1} a_j = 0$ 且 $\sum_{j = i}^{r} a_j = k$，这样的 $l$ 和 $r$ 可以使用二分以 $\mathcal{O}(\log n)$ 的复杂度处理出。此时显然 $[l, r]$ 是一个极大的满足条件的区间，且这样可以使极大区间和位置 $i$ 满足双射。

考虑仅计算一个极大区间的排序方案数。特别地，我们要求不能与原序列相同，否则会出现大量的重复。我们对于区间 $[l, r]$，显然地，这时的答案是 $\displaystyle {r - l + 1 \choose k} - 1$。我们有基本的答案 $\displaystyle \sum_{[l, r]} {r - l + 1 \choose k} - 1$。

但是，如果对于极大的 $[l_1, r_1]$ 和 $[l_2, r_2]$，存在一个不是极大的 $[l, r]$ 使得 $[l, r] \sub [l_1, r_1]$ 且 $[l, r] \sub [l_2, r_2]$，那么 $[l, r]$ 中的排序就会被重复计算。

考虑如何删除重复的计算。

我们注意到当 $a_i = 1$ 的 $i$ 上升时，序列的左右端点均上升，即序列具有单调性，所以包含非极大 $[l, r]$ 的区间在极大区间的序列中是连续的，我们记这个连续段的两个端点是 $p$ 和 $q$。

显然 $[l, r] \sub [l_1, r_1]$ 且 $[l, r] \sub [l_2, r_2]$ 的充分必要条件是 $[l, r] \sub [l_1, r_1] \cap [l_2, r_2]$。于是，在 $[p, q]$ 子串中任意选取两个相邻的序列，它们的交必然包含 $[l, r]$，且这样的相邻对恰有 $q - p$ 个，比 $[l, r]$ 被计算的次数少 $1$。所以去除相邻对数量次 $[l, r]$ 的贡献恰可以使 $[l, r]$ 的贡献被计算 $1$ 次，这是我们希望得到的。

于是，我们得到做法：先枚举 $a_i = 1$ 的 $i$，二分出 $l$ 和 $r$，加上 $[l, r]$ 的贡献，减去其和上一个 $i$ 得到的 $[l', r']$ 的交的贡献，即 $[l, r']$ 的贡献，注意 $[l, r']$ 区间中有 $k - 1$ 个 $1$。

时间复杂度 $\mathcal{O}(n \log n)$。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 5000 + 10, mod = 998244353;

int n, k, res = 0;
int a[maxn], pre[maxn], fac[maxn], ifac[maxn];

template<typename Tp_x, typename Tp_y>
inline int mod_add(Tp_x x, Tp_y y){
    x += y;
    return x >= mod ? x -= mod : x;
}

inline long long ksm(long long a, long long b){
    long long res = 1;
    while (b){
        if (b & 1){
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

inline long long inv(long long x){
    return ksm(x, mod - 2);
}

inline long long c(int n, int m){
    return (long long)fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int main(){
    scanf("%d %d", &n, &k);
    getchar();
    fac[0] = 1;
    for (int i = 1; i <= n; i++){
        fac[i] = (long long)fac[i - 1] * i % mod;
        pre[i] = pre[i - 1] + (a[i] = getchar() - '0');
    }
    ifac[n] = inv(fac[n]);
    for (int i = n - 1; ~i; i--){
        ifac[i] = (long long)ifac[i + 1] * (i + 1) % mod;
    }
    for (int i = 1, lstr = 0; i <= n; i++){
        if (a[i]){
            const int l = lower_bound(pre, pre + n + 1, pre[i] - 1) - pre + 1, r = lower_bound(pre + 1, pre + n + 1, pre[i] + k) - pre - 1;
            if (pre[r] == pre[i] + k - 1){
                res = mod_add(res, mod_add(c(r - l + 1, k), mod - 1));
                if (lstr >= l){
                    res = mod_add(res, mod - mod_add(c(lstr - l + 1, k - 1), mod - 1));
                }
                lstr = r;
            }
        }
    }
    printf("%d", mod_add(res, 1));

return 0;
}
```

---

## 作者：Zhao_daodao (赞：0)

# Shuffle

为什么数据范围是 $n\le 5000$，明明可以 $O(n)$，应该开到 $5\times 10^6$。

对于最后的 $a$，肯定有一种构造方式是每一次都操作极长连续段。

记录右端点为 $i$ 时的极长连续段为 $[lst_i,i]$。

因为至多操作 `1` 次，所以算出每一个右端点对应的答案，加起来就可以了。

---

但是会有重复计算。

在什么时候会有重复呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/id9ncvmz.png)

如果你当前的右端点是 $i$，然后在 $[lst_i,lst_{i+1}-1]$ 中的数全部相等，那么，你现在的重排相当于重排 $[lst_{i+1},i]$，会在 $[lst_{i+1},i+1]$ 中被计算。把这一部分去掉就可以了。

定义 $s(l,r)=\sum\limits_{i=l}^{r}a_i$。

每一个 $i$ 的答案：
$$
ans_i=\binom{i-lst_i+1}{s(lst_i,i)}-\binom{i-lst_{i+1}+1}{s(lst_{i+1},i)}
$$
最后求和就可以了。复杂度 $O(n)$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
//modint
const int MAXN=5e3+5,N=5e3;
int n,k,a[MAXN],s[MAXN];
int lst[MAXN];
mint fac[MAXN],inv[MAXN];
inline void init(){
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=fac[i-1]*i;
    inv[N]=fac[N].inv();for(int i=N-1;i>=0;i--)inv[i]=inv[i+1]*(i+1);
}
inline mint C(int n,int m){
    if(n<m||n<0||m<0)return 0;
    return fac[n]*inv[m]*inv[n-m];
}
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    cin>>n>>k;init();
    for(int i=1;i<=n;i++){
        char x;cin>>x;
        a[i]=(x=='1');
    }
    for(int i=1;i<=n;i++)s[i]=s[i-1]+a[i];
    for(int i=1;i<=n;i++){
        if(s[i]<k){
            lst[i]=-1;
            continue;
        }else{
            if(s[i]==k){
                lst[i]=1;
                continue;
            }
            lst[i]=lst[i-1];
            while(lst[i]<i&&s[i]-s[lst[i]-1]>k)lst[i]++;
        }
    }
    mint ans=1;bool flag=0;
    for(int i=1;i<=n;i++)if(lst[i]!=-1){
        flag=1;
        int L=lst[i],R=i;
        mint res=(C(R-L+1,s[R]-s[L-1])-1);
        if(i<n){
            L=lst[i+1],R=i;
            res-=(C(R-L+1,s[R]-s[L-1])-1);
        }
        ans+=res;
    }
    if(!flag)ans=1;
    cout<<ans<<"\n";
}
```

---

## 作者：封禁用户 (赞：0)

因为符合条件的子串有可能有很多个，如果只是选取包含 $k$ 个 $1$ 的子串然后重新排列，则需要判断每个子串重新排序后形成的字符串是否重复，这个很难实现。

于是考虑固定子串的起点和终点，这样子每个子串重新排序之后形成的字符串就不会出现重复的情况，我们可以假设子串的起点和终点都是 $1$，可以通过嵌套循环去选取起点和终点，然后计算能形成的不同子串的数量就可以了。

而计算一个子串重排列后能够形成多少个不同的字符串，需要知道子串含 $1$ 的数量，记 $0$ 的数量为 $a$，$1$ 的数量为 $b$，那么总共能形成 ${C}_{b}^{a+b}$ 不同的字符串，这样子长度为 $a+b$。因为符合条件的子串有可能有很多个，如果只是选取包含 $k$ 个 $1$ 的子串然后重新排列，则需要判断每个子串重新排序后形成的字符串是否重复，这个很难实现。
 
于是考虑固定子串的起点和终点，这样子每个子串重新排序之后形成的字符串就不会出现重复的情况，我们可以假设子串的起点和终点都是 $1$，可以通过嵌套循环去选取起点和终点，然后计算能形成的不同子串的数量就可以了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
int n, k;
string s;
void solve(){
	int ans = 1;
	cin >> n >> k >> s;
	vector <int> p(n + 1, 0);
	for (int i = 1; i <= n; i++)
		p[i] = p[i - 1] + (s[i - 1] - '0');  //求出 1 的数量的前缀和
	if (p[n] < k){
		cout << "1\n";
		return;
	}
	vector <vector <int> > cnt(n + 1);
	for (int i = 0; i <= n; i++){  //计算长为 i，包含 j 个 1 的字符串重排列后能形成不同的字符串
		cnt[i].resize(i + 1);
		cnt[i][0] = cnt[i][i] = 1;
		for (int j = 1; j < i; j++)
			cnt[i][j] = (cnt[i - 1][j] + cnt[i - 1][j - 1]) % mod;
	}
	for (int i = 0; i < n; i++){
		for (int j = i + 1; j < n; j++){
			int a = j - i - 1;
			int b = p[j + 1] - p[i];
			if (b > k) continue;
			b -= ((s[i] - '0') ^ 1) + ((s[j] - '0') ^ 1);  //固定起点和终点为 1
			if(b < 0 || a < 0 || b > a) continue;
			ans = (ans + cnt[a][b]) % mod;
		}
	}
	cout << ans << "\n";
}
int main(){
	solve();
	return 0;
}

``````

---

## 作者：Erica_N_Contina (赞：0)

## 思路

题面很简洁，重点看思维。首先的首先，如果 $\sum a_i<k$，一定无解。

如果是暴力的做法，那么这道题我们就需要这几个步骤：枚举合法区间，枚举修改，判重。看起来每一个环节都不容易优化，所以我们考虑其他的思路——emm，直接做好像是没什么头绪，那么就要善用**正难则反。**

为了跳过判重这个步骤，我们可以考虑直接枚举最终的序列。我们枚举最终的序列在区间 $[l,r]$ 发生了改变，并且很显然我们要限制必须有两个修改分别位于 $l,r$ 处。

现在来考虑另外一个限制：原区间合法。我们考虑到，假设我们枚举区间 $[l,r]$ 被修改了，这不能代表我们选择的区间就是 $[l,r]$，只能说明我们选择的区间包含了 $[l,r]$。因此，我们只要保证 $\sum a_i,i\in[l,r]≤k$ 即可。

对于一个合法的 $[l,r]$，$(l,r)$ 中的数字可以任意填 $0$ 或者 $1$（注意修改前后区间内 $01$ 的数量不能改变，因为题目要求是“任意**排列”**），端点的必须固定修改。方案数用组合数计算即可。

---

```C++
#include<bits/stdc++.h>
#define rep(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define per(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
#define int long long
#define pii pair<int,int>

#define lc(x) (x<<1)
#define rc(x) (x<<1|1)

#define rd read()
inline int read()
{
	int xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}

const int N=5e3+5;
const int INF=1e18+5;
const int MOD=998244353;
int ans,m;

int a[N],c[N][N],n,k,qzh[N];

int C(int n,int m){
	if(n<0||m<0)return 0;
	return c[n][m];
}

void init(){
	c[0][0]=1;//从0开始！
	for(int i=1;i<=n;i++){
		c[i][0]=1;
		for(int j=1;j<=n;j++){
			c[i][j]=c[i-1][j]+c[i-1][j-1]%MOD;
		}
	}
//	for(int i=0;i<=10;i++){
//		for(int j=0;j<=i;j++){
//			cerr<<c[i][j]<<' ';
//		}
//		cerr<<endl;
//	}
}

signed main(){
	n=rd,k=rd;
	
	init();
	
	string s;
	cin>>s;
	for(int i=1;i<=n;i++)a[i]=s[i-1]-'0';
	for(int i=1;i<=n;i++)qzh[i]=qzh[i-1]+a[i];
//	for(int i=1;i<=n;i++)cerr<<qzh[i]<<' ';
	
	if(qzh[n]<k){
		cout<<1;return 0;
	}
	int cnt1=0,cnt0=0;
	for(int l=1;l<=n;l++){
		if(a[l])cnt1=1,cnt0=0;
		else cnt0=1,cnt1=0;
		for(int r=l+1;r<=n;r++){//注意l不能=r，合法但是会重复
			if(l>r)continue;
			if(a[r])cnt1++;//统计区间内的01总个数
			else cnt0++;
			
			if(qzh[r]-qzh[l-1]>k)break;
			
			int c1=cnt1,c0=cnt0;
			if(a[l])c0--;
			else c1--;
			if(a[r])c0--;
			else c1--;//计算可随便填的01个数
			
//			cerr<<"l,r="<<l<<' '<<r<<" cnt0,cnt1="<<cnt0<<' '<<cnt1<<endl;
//			cerr<<"l,r="<<l<<' '<<r<<" c0,c1="<<c0<<' '<<c1<<endl;
			ans+=C(c1+c0,c0);
			ans%=MOD;
		}
	}
	cout<<(ans+1)%MOD<<endl;
	return 0;
}

```




---

