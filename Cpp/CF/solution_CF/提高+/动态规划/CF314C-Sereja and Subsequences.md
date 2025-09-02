# Sereja and Subsequences

## 题目描述

Sereja has a sequence that consists of $ n $ positive integers, $ a_{1},a_{2},...,a_{n} $ .

First Sereja took a piece of squared paper and wrote all distinct non-empty non-decreasing subsequences of sequence $ a $ . Then for each sequence written on the squared paper, Sereja wrote on a piece of lines paper all sequences that do not exceed it.

A sequence of positive integers $ x=x_{1},x_{2},...,x_{r} $ doesn't exceed a sequence of positive integers $ y=y_{1},y_{2},...,y_{r} $ , if the following inequation holds: $ x_{1}<=y_{1},x_{2}<=y_{2},...,x_{r}<=y_{r} $ .

Now Sereja wonders, how many sequences are written on the lines piece of paper. Help Sereja, find the required quantity modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 样例 #1

### 输入

```
1
42
```

### 输出

```
42
```

## 样例 #2

### 输入

```
3
1 2 2
```

### 输出

```
13
```

## 样例 #3

### 输入

```
5
1 2 3 4 5
```

### 输出

```
719
```

# 题解

## 作者：_edge_ (赞：2)

理解一下题意，就是给定一个序列，然后拿出来若干个不下降子序列，对于每一个子序列求出有多少个序列，使得序列长度和子序列一样，并且字典序小于等于子序列，相同的序列只算一次。

如果没有相同的限制，可以利用树状数组很快速地秒掉。

具体的，设 $f_i$ 表示以 $i$ 这个点为结尾，然后求一下上面那种序列有多少种，转移就是 $f_i=\sum f_j \times a_i$ 并且 $a_j \le a_i$。

然后考虑如何判重，首先，可以发现，如果出现了两个数，$a_i$ 和 $a_j$ 满足 $a_i=a_j$ 且 $i<j$，那么 $i$ 结尾的不下降子序列 $j$ 也可以更新的到。

因此，如果我们出现了以上这种情况，就把 $i$ 这个位置给清空即可。

时间复杂度 $O(n \log n)$。

```cpp
#include <iostream>
#include <cstdio>
#define int long long 
using namespace std;
const int INF=1e6+5;
const int Mod=1e9+7;
int n,a[INF],f[INF],tree[INF],vis[INF],pre[INF];
void add(int x,int y) {for (int i=x;i<=1e6;i+=i&-i) tree[i]+=y,tree[i]%=Mod;return ;}
int query(int x) {int sum=0;for (int i=x;i;i-=i&-i) sum+=tree[i],sum%=Mod;return sum;}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=1;i<=n;i++) cin>>a[i];
	int ans=0;
	for (int i=1;i<=n;i++) {
		f[i]=(query(a[i])+1)*a[i]%Mod;
		if (pre[a[i]]) add(a[i],-f[pre[a[i]]]),f[pre[a[i]]]=0;
		pre[a[i]]=i;
		add(a[i],f[i]);
	}
	for (int i=n;i;i--)
		ans+=f[i],ans%=Mod;
	cout<<(ans%Mod+Mod)%Mod<<"\n";
	return 0;
}
```


---

## 作者：liuyifan (赞：1)

## DP
f[i]表示前i项内以a[i]结尾的不同子序列权值和

倒叙枚举j，如果a[j]第一次出现(开个vis统计一下)，则a[j]就涵盖了1-j中所有以a[j]结束的不同子序列；

所以状态转移是f[i]=(1+sum{f[j]})*a[i] 

然后同上倒叙枚举最终答案即可

dp的过程中可以使用树状数组优化一下,具体见代码

code:
```cpp
#include<bits/stdc++.h>//万能头文件
#define reg register
#define ll long long
#define inf 0x3f3f3f3f
#define lowbit(x) x&(-x)//树状数组模板
using namespace std;
ll n,a[1000005],c[1000005],f[1000005],vis[1000005],ans;//注意本题卡long long
//CF的很多题都要开LONG LONG,小心
inline void add(reg ll x,reg ll v)
{
    for(;x<=1000000;x+=x&(-x))c[x]=(c[x]+v)%1000000007;
}
inline ll sum(reg ll x)
{
    reg ll ans=0;
    for(;x;x-=lowbit(x))ans=(ans+c[x])%1000000007;
    return ans;
}//树状数组模板
//树状数组个人觉得能用就尽量用,常数小,码量小,
int main()
{
    scanf("%lld",&n);
    for(reg int i=1;i<=n;i++)scanf("%lld",&a[i]);
    for(reg int i=1;i<=n;i++)
    {
        f[i]=a[i]+sum(a[i])*a[i];//DP
        add(a[i],(f[i]-sum(a[i])+sum(a[i]-1)+1000000007)%1000000007);//树状数组优化
    }
    for(reg int i=n;i;i--)
	if(!vis[a[i]])ans=(ans+f[i])%1000000007,vis[a[i]]=1;//查询答案
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：rsy_ (赞：0)

先可以写出 $\mathcal O(n^2)$ 的 dp，这个还是非常显然的。

设 $f_x$ 表示以 $x$ 结尾的子序列的乘积的总和，用树状数组求一个前缀和乘一下 $a_x$ 就可以了，记得每次加之前要把以前的贡献删掉。

```
#include <bits/stdc++.h>
#define lb(x) (x&-x)
#define L(i,j,k) for(int i=(j);i<=(k);++i)
#define R(i,j,k) for(int i=(j);i>=(k);--i)
#define int long long

using namespace std;
using i64 = long long;

typedef pair<int, int> pii;
typedef long long ll;
typedef unsigned long long ull;
void chmin(int &x, int c) {
	x = min(x, c);
}
void chmax(int &x, int c) {
	x = max(x, c);
}

namespace fast_IO {
#define IOSIZE 100000
	int precision = 3, POW[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
	char ibuf[IOSIZE], obuf[IOSIZE], *p1 = ibuf, *p2 = ibuf, *p3 = obuf;
#ifdef ONLINE_JUDGE
	#define getchar() ((p1==p2)and(p2=(p1=ibuf)+fread(ibuf,1,IOSIZE,stdin),p1==p2)?(EOF):(*p1++))
	#define putchar(x) ((p3==obuf+IOSIZE)&&(fwrite(obuf,p3-obuf,1,stdout),p3=obuf),*p3++=x)
	#define isdigit(ch) (ch>47&&ch<58)
	#define isspace(ch) (ch<33)
#endif
	template<typename T>inline T read() {
		T s = 0;
		int w = 1;
		char ch;
		while (ch = getchar(), !isdigit(ch) && (ch != EOF))if (ch == 45)w = -1;
		if (ch == EOF)return 0;
		while (isdigit(ch))s = s * 10 + ch - 48, ch = getchar();
		return s * w;
	} template<typename T>inline bool read(T&s) {
		s = 0;
		int w = 1;
		char ch;
		while (ch = getchar(), !isdigit(ch) && (ch != EOF))if (ch == 45)w = -1;
		if (ch == EOF)return 0;
		while (isdigit(ch))s = s * 10 + ch - 48, ch = getchar();
		return s *= w, 1;
	} inline bool read(char&s) {
		while (s = getchar(), isspace(s));
		return 1;
	} inline bool read(char*s) {
		char ch;
		while (ch = getchar(), isspace(ch));
		if (ch == EOF)return 0;
		while (!isspace(ch))*s++ = ch, ch = getchar();
		*s = '\000';
		return 1;
	} template<typename T>inline void print(T x) {
		if (x < 0)putchar(45), x = -x;
		if (x > 9)print(x / 10);
		putchar(x % 10 + 48);
	} inline void print(char x) {
		putchar(x);
	} inline void print(char*x) {
		while (*x)putchar(*x++);
	} inline void print(const char*x) {
		for (int i = 0; x[i]; i++)putchar(x[i]);
	} inline bool read(std::string&s) {
		s = "";
		char ch;
		while (ch = getchar(), isspace(ch));
		if (ch == EOF)return 0;
		while (!isspace(ch))s += ch, ch = getchar();
		return 1;
	} inline void print(std::string x) {
		for (int i = 0, n = x.size(); i < n; i++)putchar(x[i]);
	} inline bool read(bool&b) {
		char ch;
		while (ch = getchar(), isspace(ch));
		b = ch ^ 48;
		return 1;
	} inline void print(bool b) {
		putchar(b + 48);
	} inline bool read(double&x) {
		int a = 0, b = 0;
		char ch = getchar();
		bool f = 0;
		while (ch < 48 || ch > 57) {
			if (ch == 45)f = 1;
			ch = getchar();
		}
		while (47 < ch && ch < 58) {
			a = (a << 1) + (a << 3) + (ch ^ 48);
			ch = getchar();
		}
		if (ch != 46) {
			x = f ? -a : a;
			return 1;
		}
		ch = getchar();
		while (47 < ch && ch < 58) {
			b = (b << 1) + (b << 3) + (ch ^ 48), ch = getchar();
		}
		x = b;
		while (x > 1)x /= 10;
		x = f ? -a - x : a + x;
		return 1;
	} inline void print(double x) {
		if (x < 0) {
			putchar(45), x = -x;
		}
		x = round((long double)x * POW[precision]) / POW[precision], print((long long)x), putchar(46), x -= (long long)(x);
		for (int i = 1; i <= precision; i++)x *= 10, putchar(x + 48), x -= (int)x;
	} template<typename T, typename...T1>inline int read(T& a, T1&...other) {
		return read(a) + read(other...);
	} template<typename T, typename...T1>inline void print(T a, T1...other) {
		print(a), print(other...);
	} struct Fast_IO {
		~Fast_IO() {
			fwrite(obuf, p3 - obuf, 1, stdout);
		}
	} io;
	template<typename T>Fast_IO& operator>>(Fast_IO&io, T&b) {
		return read(b), io;
	} template<typename T>Fast_IO& operator<<(Fast_IO&io, T b) {
		return print(b), io;
	}
#define cout io
#define cin io
#define endl '\n'
} using namespace fast_IO;
const int maxn = 1e6 + 10, mod = 1e9+7;
int n,a[maxn],f[maxn];
int c[maxn];
void add(int id,int x){
	id++;
	for(int i=id;i<=1000001;i+=lb(i))
		c[i]+=x,c[i]%=mod,c[i]+=mod,c[i]%=mod; 
}
int sum(int x){
	int res=0;
	x++;
	while(x)res+=c[x],x-=lb(x),res%=mod;
	res+=mod,res%=mod;
	return res;
}

void solve() {
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	add(0,1);
	for(int i=1;i<=n;i++){
		int t=sum(a[i])-sum(a[i]-1); t%=mod,t+=mod,t%=mod;
		add(a[i],sum(a[i])*a[i]%mod),add(a[i],-t);
	} 
	cout<<(sum(1000000)-1+mod)%mod<<'\n';
}

signed main() {
	int T = 1;
	while (T--)solve();
	return 0;
}
```

---

## 作者：Drind (赞：0)

### 题目解析

这道题让我们求原序列每个不同不降子序列的和他等同长度且字典序小于他的数列个数和。我们先改装一下题目，改成求每个在原数列位置不同就算不同的不降子序列，那么我们设 $f_i$ 为前 $i$ 项中满足条件的数列和，于是我们有 $f_i=a_i\sum_{j=0}^{i-1}f_j[a_j\le a_i]$，这个东西可以用权值树状数组维护，复杂度 $O(n\log n)$。

我们发现，如果 $a_i=a_j$ 且 $j\lt i$，那么 $f_j$ 不应该被别的值拿来转移，因为会重复，于是我们每次加入一个新的 $a_i$ 时把之前所有和 $a_i$ 值一样的全部删除即可。

注意取模。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;
const int p=1e9+7;

int tree[N];

inline int lowbit(int x){
	return x&(-x);
}

void modify(int p,int val){
	while(p<N){
		tree[p]+=val;
		p+=lowbit(p);
	}
}

int query(int p){
	int ans=0;
	while(p){
		ans+=tree[p];
		ans%=(1000000007);
		p-=lowbit(p);
	}
	return ans;
}

int dp[N],a[N];
int pre[N];

inline void fake_main(){
	int n; cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		dp[i]=(query(a[i])+1)*a[i]%p;//dp式子，注意可以取dp[0]所以加一
		if(pre[a[i]]){
			modify(a[i],-dp[pre[a[i]]]);//删除
			dp[pre[a[i]]]=0;
		}
		pre[a[i]]=i;
		modify(a[i],dp[i]);
	}
	int ans=0;
	for(int i=n;i>=1;i--){
		ans+=dp[i]; ans%=p;
	}
	
	cout<<ans<<"\n";
}

signed main(){
	ios::sync_with_stdio(false);
	int t; t=1;
	while(t--) fake_main();
}

```

---

