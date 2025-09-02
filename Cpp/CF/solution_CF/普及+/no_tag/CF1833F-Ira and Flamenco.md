# Ira and Flamenco

## 题目描述

Ira loves Spanish flamenco dance very much. She decided to start her own dance studio and found $ n $ students, $ i $ th of whom has level $ a_i $ .

Ira can choose several of her students and set a dance with them. So she can set a huge number of dances, but she is only interested in magnificent dances. The dance is called magnificent if the following is true:

- exactly $ m $ students participate in the dance;
- levels of all dancers are pairwise distinct;
- levels of every two dancers have an absolute difference strictly less than $ m $ .

For example, if $ m = 3 $ and $ a = [4, 2, 2, 3, 6] $ , the following dances are magnificent (students participating in the dance are highlighted in red): $ [\color{red}{4}\color{black}, 2,\color{red}{2}\color{black},\color{red}{3}\color{black}, 6] $ , $ [\color{red}{4}\color{black}, \color{red}{2}\color{black}, 2, \color{red}{3}\color{black}, 6] $ . At the same time dances $ [\color{red}{4}\color{black}, 2, 2, \color{red}{3}\color{black}, 6] $ , $ [4, \color{red}{2}\color{black}, \color{red}{2}\color{black}, \color{red}{3}\color{black}, 6] $ , $ [\color{red}{4}\color{black}, 2, 2, \color{red}{3}\color{black}, \color{red}{6}\color{black}] $ are not magnificent.

In the dance $ [\color{red}{4}\color{black}, 2, 2, \color{red}{3}\color{black}, 6] $ only $ 2 $ students participate, although $ m = 3 $ .

The dance $ [4, \color{red}{2}\color{black}, \color{red}{2}\color{black}, \color{red}{3}\color{black}, 6] $ involves students with levels $ 2 $ and $ 2 $ , although levels of all dancers must be pairwise distinct.

In the dance $ [\color{red}{4}\color{black}, 2, 2, \color{red}{3}\color{black}, \color{red}{6}\color{black}] $ students with levels $ 3 $ and $ 6 $ participate, but $ |3 - 6| = 3 $ , although $ m = 3 $ .

Help Ira count the number of magnificent dances that she can set. Since this number can be very large, count it modulo $ 10^9 + 7 $ . Two dances are considered different if the sets of students participating in them are different.


## 说明/提示

In the first testcase, Ira can set such magnificent dances: $ [\color{red}{8}\color{black}, 10, 10, \color{red}{9}\color{black}, \color{red}{6}\color{black}, 11, \color{red}{7}\color{black}] $ , $ [\color{red}{8}\color{black}, \color{red}{10}\color{black}, 10, \color{red}{9}\color{black}, 6, 11, \color{red}{7}\color{black}] $ , $ [\color{red}{8}\color{black}, 10, \color{red}{10}\color{black}, \color{red}{9}\color{black}, 6, 11, \color{red}{7}\color{black}] $ , $ [\color{red}{8}\color{black}, 10, \color{red}{10}\color{black}, \color{red}{9}\color{black}, 6, \color{red}{11}\color{black}, 7] $ , $ [\color{red}{8}\color{black}, \color{red}{10}\color{black}, 10, \color{red}{9}\color{black}, 6, \color{red}{11}\color{black}, 7] $ .

The second testcase is explained in the statements.

## 样例 #1

### 输入

```
9
7 4
8 10 10 9 6 11 7
5 3
4 2 2 3 6
8 2
1 5 2 2 3 1 3 3
3 3
3 3 3
5 1
3 4 3 10 7
12 3
5 2 1 1 4 3 5 5 5 2 7 5
1 1
1
3 2
1 2 3
2 2
1 2```

### 输出

```
5
2
10
0
5
11
1
2
1```

# 题解

## 作者：Coffee_zzz (赞：8)

### 分析

因为选出的 $m$ 个数需要满足对于所有的 $1 \le i,j \le m$ 且 $i\neq j$，都有 $a_i \neq a_j$ 且 $|a_i-a_j|<m$，所以选出的 $m$ 个数对应的 $a$ 的值需要形成一个公差为 $1$ 的等差数列。

我们可以将 $a$ 排序，找到 $a$ 中可以形成公差为 $1$ 的等差数列且长度极大的部分，分部分求解答案。

我们设这部分是由 $a_l\sim a_r$ 组成的，若 $a_r-a_l<m-1$，那么显然这部分无法组成等差数列，直接跳出。

反之，我们开个桶 $ma$，存每个数出现的次数。

若我们现在需要求 $k\sim k+m-1$ 能够组成的公差为 $1$ 且长度为 $m$ 的等差数列的个数，根据乘法原理，答案等于 $ma_k \times ma_{k+1} \times ma_{k+2} \times \cdots ma_{k+m-1}$。

那我们再开个桶 $tim$，存这些数的前缀积，利用逆元计算每个部分的答案，最后将每部分的答案相加即可。

最后注意值域较大，可以使用 `map` 替换桶。

### 代码

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
namespace IO{
	char ibuf[(1<<20)+1],*iS,*iT;
	#if ONLINE_JUDGE
	#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read(){
		reg char ch=gh();
		reg long long x=0;
		reg char t=0;
		while(ch<'0'||ch>'9')   t|=ch=='-',ch=gh();
		while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();
		return t?-x:x;
	}
}
using IO::read;
const int mod=1e9+7,N=4e5+5;
int n,m,a[N],cnt;
int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
void solve(){
	map <int,int> ma;
	map <int,int> tim;
	n=read(),m=read();
	int p=1,ans=0;
	for(int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++){
		if(a[i+1]-a[i]>1||i==n){
			if(a[i]-a[p]>=m-1){
				cnt=0;
				for(int j=p;j<=i;j++){
					ma[a[j]]++;
				}
				tim[a[p]-1]=1;
				for(int j=a[p];j<=a[i];j++){
					tim[j]=ma[j]*tim[j-1]%mod;
				}
				for(int j=a[p],k=a[p]+m-1;k<=a[i];j++,k++){
					ans=ans+(tim[k]*ksm(tim[j-1],mod-2)%mod);
					ans=ans%mod;
				}
			}
			p=i+1;
		}
	}
	cout<<ans<<endl;
}
signed main(){
	int T=read();
	while(T--) solve();
	return 0;
}
```

---

## 作者：Little_x_starTYJ (赞：6)

### 解题思路
不难发现，题目要求我们从序列 $a$ 中取 $m$ 个数，满足这 $m$ 个数字两两之差小于 $m$ 相当于在序列 $a$ 中找 $m$ 个数满足它们从小到大排序后是连续的。

所以，对于每一次询问，我们先排一个序，然后去重，接着用线段树查询 $i-m+1 \sim i$ 每个数的出现次数再相乘即可。

CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"
inline int read() {
	int k = 0;
	char c = getchar();
	while (c < '0' || c > '9')
		c = getchar();
	while (c >= '0' && c <= '9')
		k = (k << 1) + (k << 3) + (c ^ 48), c = getchar();
	return k;
}
const int mod = 1e9 + 7;
map<int, int> f;
int a[200010], tree[800010];
inline void buildTree(int k, int l, int r) {
	if (l == r) {
		tree[k] = f[a[l]];
		return;
	}
	int mid = l + r >> 1;
	buildTree(k * 2, l, mid);
	buildTree(k * 2 + 1, mid + 1, r);
	tree[k] = tree[k * 2] * tree[k * 2 + 1] % mod;
}
inline int query(int k, int l, int r, int x, int y) {  //查询区间 x ~ y	
	if (l == x && r == y) {
		return tree[k];
	}
	int mid = l + r >> 1;
	int res = 0;
	if (y <= mid) {
		res += query(k * 2, l, mid, x, y);
	} else if (x > mid) {
		res += query(k * 2 + 1, mid + 1, r, x, y);
	} else {
		res += query(k * 2, l, mid, x, mid) * query(k * 2 + 1, mid + 1, r, mid + 1, y) % mod;
	}
	return res;
}
long long ans;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int t, n, m, id;
	t = read();
	while (t--) {
		f.clear();
		n = read(), m = read(), ans = 0;
		for (register int i = 1; i <= n; i++) {
			a[i] = read();
			f[a[i]]++;
		}
		if (m == 1) {
			cout << n << endl;
			continue;
		}
		sort(a + 1, a + 1 + n);
		int k = unique(a + 1, a + 1 + n) - a - 1;
		buildTree(1, 1, k);
		id = 1;
		for (int i = 2; i <= k; i++) {
			if (a[i] - a[i - 1] == 1) {
				id++;
			} else {
				id = 1;
			}
			if (id == m) {
				int temp = query(1, 1, k, i - m + 1, i);
				ans = (ans + temp) % mod;
				id--;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：hjqhs (赞：6)

原题显然等价于求一个长度为 $m$ 的等差数列，且公差为 $1$。  
显然先排序，然后离散化，再用桶分别记录每个数的数量。  
对于每一个左端点，找到满足条件的右端点，中间数的数量依据乘法原理累乘。  
当然没必要每次都把左端点到右端点的值全部乘起来，每次左端点只变化 $1$，所以直接把左端点的数量除掉即可，因为要取模所以逆元。  
```cpp
memset(a,0,sizeof(a)),cnt.clear();
  ans=0,c=1;
  cin>>n>>m;
  rep(i,1,n){cin>>a[i],++cnt[a[i]];}
  sort(a+1,a+1+n);
  n=unique(a+1,a+1+n)-a-1;
  for(int i=1,j=1;i<=n;++i){
    while(j<=n&&a[j]<a[i]+m)c=c*(cnt[a[j]])%MOD,++j;
    if(j-i==m)ans+=c,ans%=MOD;
    c=c*qpow(cnt[a[i]],MOD-2)%MOD;
  }
  cout<<ans<<'\n';
```

---

## 作者：ran_qwq (赞：4)

提供个不用 map 的解法喵。

---
[CF 传送门](https://codeforces.com/problemset/problem/1833/F)

题目大意：题面很友好，略。

### 朴素算法
选出 $m$ 个互不相同的数，最大的减最小的还有小于 $m$。不难看出，题目可以转化为求有多少个长度为 $m$，公差为 $1$ 的等差数列。

先把数组排个序，设 $c_i$ 为 $i$ 出现的次数。

对于一个末项为 $x$ 的等差数列，根据乘法原理，其方案数为 $\prod\limits_{i=x-m+1}^xc_i$。

把每个末项的方案数加起来就是答案。

把 $a_i$ 离散化再求 $c$ 就可以不用 map。

但是，遗憾地告诉你，直接算是 $O(mV)$ 的（$V$ 表示值域），会超时。

### 优化

注意到第一次算的区间是 $[1,m]$，第二次是 $[2,m+1]$，第三次是 $[3,m+2]$，以此类推。每次只是删掉最前面的一个数，并加入最后面的一个数。

维护当前方案数 $sum$。每次只需要将 $sum$ 乘 $c_x$，再用逆元除以 $c_{x-m}$ 即可。

[CF 提交记录](https://codeforces.com/contest/1833/submission/224679222)

---

## 作者：yanwh1 (赞：2)

# 题目大意
给你一个长度为 $n$ 的序列 $a$，让你选 $m$ 个数，要求 $m$ 个数连续。求有多少种选择方案。
# 思路讲解
直接排序加离散化，并记录序列中每个值出现的次数。在查询处理后的数组时，设处理后的数组为 $s$，不重复的数一共有 $cnt$ 个，枚举 $i(1 \leq i \leq cnt-m+1)$，若 $s_{i+m-1} - s_{i} = m-1$，便说明这个方案是合法的。于是我们把这几个数的个数乘起来，便是该方案的答案。

有人可能就会问：“我要怎么才能快速求出几个数的积呢？”一种方法就是线段树（~~但是我被卡了~~）。另一种就是用逆元。因为我们要求的积其实是连续的，所以我们每次操作后只要把 $s_i$ 的出现个数除掉，再乘上 $s_{i+m}$ 即可。只是因为要取模，所以这里就需要用到逆元。我用的是费马小定理求解（不会的出门左转去学一下逆元谢谢）。
# 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rint register int
inline int read(){
    int f=0,t=0;
    char c=getchar();
    while(!isdigit(c)) t|=(c=='-'),c=getchar();
    while(isdigit(c)) f=(f<<3)+(f<<1)+c-48,c=getchar();
    return t?-f:f;
}
inline void write(int x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar('0'+x%10);
}const int N=2e5+5,mod=1e9+7;
int _s[N],s[N],vis[N],cnt;
inline long long ksm(long long a,int b){
	long long sum=1;
	while(b){
		if(b&1)sum*=a,sum%=mod;
		a*=a,a%=mod,b>>=1;
	}return sum;
}signed main(){
	int T=read();
	while(T--){
		int n=read(),m=read();
		long long ans=0,sum=1;
		for(rint i=1;i<=n;i++)_s[i]=read();
		sort(_s+1,_s+n+1);
		for(rint i=1,j=0;i<=n;i++){
			if(_s[i]!=j)s[++cnt]=_s[i],j=s[cnt];
			vis[cnt]++;
		}for(rint i=1;i<=m;i++)sum*=vis[i],sum%=mod;
		for(rint i=1;i<=cnt-m+1;i++){
			if(s[i+m-1]-s[i]<m)
				ans=(ans+sum)%mod;
			sum*=ksm(vis[i],mod-2)%mod,sum%=mod;
			sum*=vis[i+m],sum%=mod;vis[i]=0;
		}write(ans),puts("");for(rint i=cnt-m+2;i<=cnt;i++)vis[i]=0;
		cnt=0;
	}
	return 0;
}
```

---

## 作者：_AyachiNene (赞：2)

# 思路：
这道题有明显的性质，两两只差严格小于 $m$，只用满足选的数值域为 $\left[l,r\right]$，且 $r-l+1\leq m$ 就行了。直接排个序，由于题目要求不能重复，所以再去个重，每次算出值域 $\left[a_i,a_i+m-1\right]$ 的数有几个，直接组合数就好了。直接算会算重，所以钦定必须选 $a_i$，再从剩下的数里选 $m-1$ 个，在乘上重复的数就可以了。
# Code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int res=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<1)+(res<<3)+(c^48);c=getchar();}
	return res*f;
}
void write(int x)
{
	if(x<0){putchar('-');x=-x;}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int t;
int n,m;
int a[114514<<1];
int ans;
const int mod=1e9+7;
int fac[114514<<1];
inline int ksm(int x,int p)
{
	int res=1;
	while(p)
	{
		if(p&1) res=res*x%mod;
		x=x*x%mod;
		p>>=1;
	}
	return res;
}
inline int C(int x,int y){return fac[x]*ksm(fac[x-y]*fac[y]%mod,mod-2)%mod;}
map<int,int>mp;
int sum[114514<<1];
signed main()
{
	freopen("neat.in","r",stdin);
	freopen("neat.out","w",stdout);
	fac[0]=1;
	for(int i=1;i<=2e5;i++) fac[i]=fac[i-1]*i%mod;
	t=read();
	while(t--)
	{
		mp.clear();
		ans=0;
		n=read(),m=read();
		for(int i=1;i<=n;i++) a[i]=read(),++mp[a[i]];
		sort(a+1,a+n+1);
		int tot=unique(a+1,a+n+1)-a-1;
		a[++tot]=1e9+5;
		sum[0]=1;
		for(int i=1;i<=tot;i++) 
		{
			sum[i]=sum[i-1];
			if(mp[a[i]]>1) sum[i]=sum[i-1]*mp[a[i]]%mod;
		}
		for(int i=1;i<tot;i++)
		{
			int p=upper_bound(a+1,a+tot+1,a[i]+m-1)-a-1;
			if(p-i+1>=m)  ans=(ans+C(p-i,m-1)*sum[p]*ksm(sum[i-1],mod-2)%mod)%mod;
		}
		write(ans),puts("");
	}
	return 0;
}
```
Code：

---

## 作者：luan341502 (赞：1)

由于题目要求 $m$ 个数两两互不相同且极差不超过 $m$，显然构成了一个公差为 $1$ 的等差数列。

我们统计每个数出现的次数，在满足存在一个长度为 $m$，公差为 $1$ 的等差数列时统计答案即可，由于是线性做法，我们要用到乘法逆元来去除统计完的首项。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int tt;
int n,m,a[200005];
map<int,int> t;
long long inv(int k){
	long long ans=1,a=k;
	int b=mod-2;
	while(b){
		if(b&1) ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
void solve(){
	t.clear();
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		t[a[i]]++;
	}
	sort(a+1,a+n+1);
	int cnt=unique(a+1,a+n+1)-a-1,k=0;
	long long ans=0,res=1;
	for(int i=1;i<=cnt;i++){
		if(a[i]==a[i-1]+1) k++;
		else k=1;
		res=res*t[a[i]]%mod;
		if(k==m){
			ans=(ans+res)%mod;
			k--;
			res=res*inv(t[a[i-m+1]])%mod;
		}
	}
	cout<<ans<<"\n"; 
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>tt;
	while(tt--) solve();
	return 0;
}
```


---

## 作者：aeiouaoeiu (赞：1)

发现题目就是要求 $a$ 中有多少个长度为 $m$ 的子序列满足这个子序列为 $[p_1+q,p_2+q,p_3+q,\ldots,p_m+q]$，其中 $p$ 是一个排列，$q$ 是一个非负整数。

我们把每个数（从小到大）出现的次数统计起来（代码中记为 $\operatorname{pi}$），在 $\operatorname{pi}$ 中找到所有长为 $m$ 的连续的一段，将这一段每个数的出现次数累乘起来，将结果累加到答案中即可。

具体实现中，我们可以把所有数的出现次数的逆元求出来，然后求出 $\operatorname{pi}$ 中所有长为 $m$ 的每一段的出现次数乘积，复杂度是 $\mathcal{O}(n\log p)$ 的，其中 $p=10^9+7$。
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define mp make_pair
using namespace std;
typedef long long ll;
const int maxn=200005;
const ll p=1000000007;
//const ll inf=1145141919810ll;
ll qpow(ll a,ll b){
	ll res=1;
	for(;b;b>>=1,a=a*a%p){if(b&1) res=res*a%p;}
	return res;
}
ll n,m,a[maxn],cnt,sum,ans;
map<ll,ll> buc;
pair<ll,pair<ll,ll> > pi[maxn];
int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0);
	ll T=1;
	cin>>T;
	pi[0]=mp(-1,mp(1,1));
	for(int tcs=1;tcs<=T;tcs++){
		cin>>n>>m;
		cnt=ans=0,sum=1,buc.clear();
		for(int i=1;i<=n;i++){
			cin>>a[i];
			buc[a[i]]++;
		}
		for(auto i:buc){
			cnt++,pi[cnt].first=i.first;
			pi[cnt].second=mp(i.second,qpow(i.second,p-2));
		}
		for(int i=1;i<=cnt;i++){
			sum=sum*pi[i].second.first%p;
			if(i<m) continue;
			sum=sum*pi[i-m].second.second%p;
			if(pi[i-m+1].first+m-1==pi[i].first) ans=(ans+sum)%p; //是否连续
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：OIer_Tan (赞：0)

[CF 传送门](https://codeforces.com/problemset/problem/1833/F)  [洛谷传送门](https://www.luogu.com.cn/problem/CF1833F)

越来越唐了，要滚回 whk 了。

## 思路

要选恰好 $m$ 个数，并且任意两数之差不超过 $m$，显然看出这是要选出自然数中连续 $m$ 个数。

考虑 `map` 计数 + 离散化，可以想到选出的这 $m$ 个数一定在离散化后的序列中是连续的一段。这样显然可以直接枚举，每次看是否和前一个数差 $1$，然后计算当前连续的长度。如果连续的长度为 $m$，就更新答案，并将计数减 $1$，这样相当于左端点往右移动一位。

考虑到 `map` 的复杂度，总时间复杂度为 $O(n\log n)$。

## 代码

```cpp
#include<bits/stdc++.h>

#ifndef CRT
#define endl '\n' 
#endif

using namespace std ;

typedef long long ll ;
typedef unsigned long long ull ;
typedef long double ld ;

const ll N = 2e5 + 5 , mod = 1e9 + 7 ;

ll n , m , T , a [N] ;

map <ll,ll> cnt ;

ll init [N] ;

ll ans = 0 ;

ll fast_pow ( ll n , ll m )
{
	if ( m == 1 )
	{
		return n ;
	}
	if ( m & 1 )
	{
		return fast_pow ( n * n % mod , m >> 1 ) * n % mod ;
	}
	return fast_pow ( n * n % mod , m >> 1 ) % mod ;
}

ll C ( ll n , ll m )
{
	if ( n < 0 || m < 0 || n < m ) return 0 ;
	return ( ( init [n] * fast_pow ( init [m] , mod - 2 ) ) % mod * fast_pow ( init [n - m] , mod - 2 ) % mod ) ;
}

void solve ()
{
	cnt.clear () ;
	ans = 0 ;
	cin >> n >> m ;
	for ( ll i = 1 ; i <= n ; i ++ )
	{
		cin >> a [i] ;
		cnt [a [i]] ++ ;
	}
	sort ( a + 1 , a + 1 + n ) ;
	n = unique ( a + 1 , a + 1 + n ) - a - 1 ;
	ll tmp = 1 ;
	for ( ll l = 1 , k = 0 ; l <= n ; l ++ )
	{
		if ( a [l] == a [l - 1] + 1 )
		{
			k ++ ;
		}
		else
		{
			k = 1 ;
		}
		tmp = tmp * cnt [a [l]] % mod ;
		if ( k == m ) 
		{
			ans = ( ans + tmp ) % mod ;
			k -- ;
			tmp = tmp * fast_pow ( cnt [a [l - m + 1]] , mod - 2 ) % mod ;
		} 
	}
	cout << ans << endl ;
	return ; 
}

int main ()
{
//	 freopen ( "neat.in" , "r" , stdin ) ;
//	 freopen ( "neat.out" , "w" , stdout ) ;
	ios::sync_with_stdio ( 0 ) ;
	cin.tie ( 0 ) ;
	cout.tie ( 0 ) ;
//	cout << fast_pow ( 3 , 9 ) << endl ;
	init [0] = 1 ;
	for ( ll i = 1 ; i < N ; i ++ ) init [i] = ( i * init [i - 1] ) % mod ;
	cin >> T ;
	while ( T -- ) 
	{
		solve () ;
	}
	return 0 ;
}
```

---

## 作者：seika27 (赞：0)

### 思路
由于要求两两之差小于 $m$。所以我们可以将数组排序后，去寻找 $a_i+m$ 这个数的位置。

令 $cnt_x$ 表示一个数 $x$，在数组中出现的次数。

那么这一次对于答案的贡献就是 $\prod\limits_{x=a_i+1}\limits^{a_i+m}{cnt_x}$，原因是乘法原理。

那么暴力代码就很简单了，外层遍历每个数，内层遍历每一个数的次数，时间复杂度 $O(nm)$。

首先我认为前缀积这个东西可能会出现问题，所以我们可以用一个线段树维护乘积。

然后这道题就做完了，复杂度 $O(n\log_2m)$。

### code
```cpp
#include <bits/stdc++.h>
#define int long long
#define cin std::cin
#define cout std::cout
int T;
int n,m;
const int N=2e5+5;
const int mod=1e9+7;
int a[N],f[N];
struct num
{
	int l,r;
};
std::map<int,num>q;
#define lx (x<<1)
#define rx (x<<1|1)
#define mid (L+R>>1) 
int mul[N<<2];
void up(int x)
{
	mul[x]=mul[lx]*mul[rx]%mod;
}
void build(int x,int L,int R)
{
	if(L==R)
	{
		mul[x]=q[f[L]].r-q[f[L]].l+1;
		mul[x]%=mod;
		return;
	}
	build(lx,L,mid);
	build(rx,mid+1,R);
	up(x);
}
int query(int x,int L,int R,int l,int r)
{
	if(l<=L&&R<=r)
	{
		return mul[x]%mod;
	}
	int sum=1;
	if(l<=mid)sum=sum*query(lx,L,mid,l,r)%mod;
	if(r>mid)sum=sum*query(rx,mid+1,R,l,r)%mod;
	return sum%mod; 
}
signed main()
{
	std::ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)
	{
		int ans=0;
		cin>>n>>m;
		q.clear();
		for(register int i=1;i<=n;++i)cin>>a[i],f[i]=a[i];
		if(m==1){cout<<n<<'\n';continue;}
		int nl=n<<2;
		for(register int i=1;i<=nl;++i)mul[i]=1;
		std::sort(f+1,f+1+n);
		std::sort(a+1,a+1+n);
		int fl=std::unique(f+1,f+1+n)-f-1;
		int maxx=a[n];
		q[maxx].r=n;
		for(register int i=1;i<=n;++i)
		{
			if(!q[a[i]].l)
			{
				q[a[i]].l=i;
				q[a[i-1]].r=i-1;
			}
		}
		build(1,1,fl);
		for(register int i=1;i<=n;++i)
		{
			int p=std::lower_bound(a+1,a+1+n,a[i]+m-1)-a;
			if(p>n)break;
			if((m>2&&q[a[i]].r+1==q[a[p]].l)||a[p]-a[i]>=m)continue;
			int start=std::lower_bound(f+1,f+1+fl,a[q[a[i]].r+1])-f;
			int finally=std::lower_bound(f+1,f+1+fl,a[p])-f;
			if(finally-start+2!=m)continue;
			ans=(ans%mod+query(1,1,fl,start,finally)%mod)%mod;
		}
		cout<<ans%mod<<'\n';
	}
}
```

---

## 作者：CodingOIer (赞：0)

## CF1833F Ira and Flamenco 题解

### 思路分析

显然的，需要 $m$ 个互不相通数且最大的数减去最小的数严格小于 $m$，所以这 $m$ 个数肯定是连续的。

先去重排序，然后枚举以每一个数作为结尾，并记录目前为止最长的连续。

以每一个数重复出现的次数计算一个前缀积。

由费马小定理得，$a^{p-1} \equiv 1 \pmod{1}$，则 $a^{p - 2} = \dfrac{1}{a}$。

我们便可以简单地算出到目前为止的方案数了。

### 代码实现

```cpp
#include <algorithm>
#include <clocale>
#include <cstdio>
#include <map>
#include <vector>
constexpr int MaxN = 2e5 + 5;
constexpr int Mod = 1e9 + 7;
int n, m;
int p[MaxN];
std::vector<int> v;
std::map<int, int> map;
std::vector<long long> su;
long long fsp(long long x, long long y)
{
    long long res = 1;
    for (; y != 0;)
    {
        if (y & 1)
        {
            res *= x;
            res %= Mod;
        }
        x *= x;
        x %= Mod;
        y >>= 1;
    }
    return res;
}
long long inv(int x)
{
    return fsp(x, Mod - 2);
}
void solve()
{
    map.clear();
    v.clear();
    su.clear();
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
        v.push_back(p[i]);
        map[p[i]]++;
    }
    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());
    su.push_back(map[v[0]]);
    for (int i = 1; i < v.size(); i++)
    {
        su.push_back(su[i - 1] * map[v[i]] % Mod);
    }
    int cnt = 0;
    long long answer = 0;
    for (int i = 0; i < v.size(); i++)
    {
        int x = v[i];
        if (i == 0 || x == v[i - 1] + 1)
        {
            cnt++;
        }
        else
        {
            cnt = 1;
        }
        if (cnt >= m)
        {
            answer += su[i] * (i - m < 0 ? 1 : inv(su[i - m]));
            answer %= Mod;
        }
    }
    printf("%lld\n", answer);
}
int main()
{
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}
```

---

## 作者：xiao7_Mr_10_ (赞：0)

好的如你所见，这题让我们求长度为 $m$ 且其中数互不相同，还要满足其中最大值与最小值的差**严格**小于 $m$。

显然，顺序我们不在意啊，先对原数组进行排序。这样就解决了差最大严格小于 $m$ 的麻烦，双指针启动。

然后考虑第二重限制，每个数字互不相同。显然我们可以再去去重，事先记录每个数出现的次数。根据乘法原理答案相当于把区间内所有数出现的次数乘在一起。

然后就做完了，时间复杂度 $O(n \log n) $。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5,mod=1e9+7;
int t,n,m,a[N];
unordered_map <int,int> col;
int fpow(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans%mod;
}
void work(){
	int ans=0;
	col.clear();
	cin >> n >> m;
	for(int i = 1;i <= n;i++)cin >> a[i],col[a[i]]++;
	sort(a+1,a+1+n);
	n=unique(a+1,a+1+n)-a-1;
	int r = 1,pre=1;
	for(int i = 1;i <= n-m+1;i++){
		 while(a[r]-a[i]<m&&r<=n)pre=pre*col[a[r]]%mod,r++;
		 if(r-i==m)ans=(ans+pre)%mod;
		 pre=pre*fpow(col[a[i]],mod-2)%mod;
	}
	cout << ans << "\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >>t;
	while(t--)work();
	return 0;
}
```

---

## 作者：Laisira (赞：0)

### 题面
在长度为 $n$ 的数组 $\{a\}$ 中选择 $m$ 个数，满足下列要求：

- 恰好选择 $m$ 个数；
- 选中的数互不相同；
- 选中的数两两之差都严格小于 $m$。

求有多少种满足要求的选择方法，答案对 $10^9+7$ 取模。

### 思路
诈骗题，选 $m$ 个数，相差小于 $m$，互不相同。其实就是让你求排序后有多少个长 $m$ 的连续数，这个读者自证不难。

于是直接将他们排序去重，对于一个数列，贡献就是他们各种数个数之积，于是用双指针维护长 $m$ 的合法序列，用前缀积维护区间贡献，还要一个逆元就够了。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long 
#define mod 1000000007 
#define Maxn 400005 
using namespace std;
int a[Maxn],res[Maxn],pre[Maxn];
map<int,int> mp;
int fsp(int x,int k) {
    int cnt = 1;
    while(k) {
        if(k & 1)cnt=cnt*x%mod;
        x = x*x%mod,k>>=1;
    } return cnt;
}
int ny(int x) {
    return fsp(x,mod-2);
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t,n,m;
    cin>>t;
    while(t--) {
        cin>>n>>m;
        mp.clear();
        for(int i=1;i<=n;i++)
            cin>>a[i],mp[a[i]]++;
        sort(a+1,a+1+n);
        n=unique(a+1,a+1+n)-a-1;
        pre[0] = 1;
        for(int i=1;i<=n;i++)
            pre[i] = pre[i-1]*mp[a[i]]%mod;
        int l=1,ans = 0;
        for(int r=1;r<=n;r++) {
            if(a[r]!=a[r-1]+1) {
                l = r;
            } if(r - l + 1 == m) {
                ans=(ans+pre[r]*ny(pre[l-1])%mod)%mod;
                l ++;
            }
        } cout<<ans<<"\n";
    }
    return 0;
}
```

---

## 作者：escapist404 (赞：0)

### Statement

在长度为 $n$ 的数组 $\{a\}$ 中选择 $m$ 个数，满足下列要求：

- 恰好选择 $m$ 个数；
- 选中的数互不相同；
- 选中的数两两之差都严格小于 $m$。

求有多少种满足要求的选择方法，答案对 $10^9+7$ 取模。

### Solution

既要恰好选择 $m$ 个数，又要求极差小于 $m$，甚至要求两两不同，那么只好选择一些形如 $x, x+1, \cdots, x+m-1$ 的数了。

根据乘法原理，这时答案就是 $\prod_{i=x}^{x+m-1} \mathrm{tot}_i$。$\mathrm{tot}_i$ 就是 $i$ 在序列里出现的次数。

保证 $a$ 升序后，枚举下标 $i$，每次先判断第 $i$ 项到第 $i+m-1$ 项能不能构成公差为 $1$ 的等差数列，再求上面那个式子的值，累加到答案中。

那个式子怎么求值呢？离散化后线段树维护就好了。

~~或者，不离散化也可以。~~

### Code

代码中使用主席树维护了区间积。

```cpp
#include <bits/stdc++.h>

using i64 = long long;

const i64 p = 1e9 + 7;

template <typename index_T, typename value_T, value_T (*opt)(value_T, value_T), value_T (*e_val)(),
		  typename tag_T, value_T (*apply)(value_T, tag_T, index_T), tag_T (*attach)(tag_T, tag_T),
		  tag_T (*e_tag)()>
class LazySegmentTree {
private:
	index_T n;
	std::vector<value_T> val;
	std::vector<tag_T> tag;
	mutable std::vector<std::pair<index_T, index_T>> child;
	index_T root;
	const index_T no_child = 0;

	inline void new_node(index_T& index) {
		index = val.size();
		val.push_back(e_val());
		tag.push_back(e_tag());
		child.push_back(std::make_pair(no_child, no_child));
	}

	inline void push_up(const index_T index) {
		val[index] = opt(val[child[index].first], val[child[index].second]);
	}
	inline void push_down(const index_T index, const index_T size) {
		if (child[index].first == no_child) new_node(child[index].first);
		if (child[index].second == no_child) new_node(child[index].second);
		val[child[index].first] = apply(val[child[index].first], tag[index], size / 2);
		val[child[index].second] = apply(val[child[index].second], tag[index], size - size / 2);
		tag[child[index].first] = attach(tag[child[index].first], tag[index]);
		tag[child[index].second] = attach(tag[child[index].second], tag[index]);
		tag[index] = e_tag();
	}
	void set(const index_T _l, const index_T _r, const tag_T _tag, const index_T l, const index_T r,
			 const index_T index) {
		if (_l >= r || _r <= l) return;
		if (_l <= l && r <= _r) {
			val[index] = apply(val[index], _tag, r - l);
			tag[index] = attach(tag[index], _tag);
			return;
		}
		push_down(index, r - l);
		index_T mid = (l + r) >> 1;
		if (_l < mid) set(_l, _r, _tag, l, mid, child[index].first);
		if (_r >= mid) set(_l, _r, _tag, mid, r, child[index].second);
		push_up(index);
	}
	value_T get(const index_T _l, const index_T _r, const index_T l, const index_T r,
				const index_T index) {
		if (_l >= r || _r <= l) return e_val();
		if (_l <= l && r <= _r) return val[index];
		push_down(index, r - l);
		index_T mid = (l + r) >> 1;
		if (_l >= mid) return get(_l, _r, mid, r, child[index].second);
		if (_r < mid) return get(_l, _r, l, mid, child[index].first);
		return opt(get(_l, _r, l, mid, child[index].first),
				   get(_l, _r, mid, r, child[index].second));
	}

public:
	inline void set(const index_T _l, const index_T _r, const tag_T _tag) {
		set(_l, _r, _tag, 0, n, 0);
	}
	inline void set(const index_T _pos, const tag_T _tag) { set(_pos, _pos + 1, _tag, 0, n, 0); }
	inline value_T get(const index_T _l, const index_T _r) { return get(_l, _r, 0, n, 0); }
	inline value_T get(const index_T _pos) { return get(_pos, _pos + 1, 0, n, 0); }
	inline value_T get() { return val.front(); }
	LazySegmentTree(index_T n) : n(n) { new_node(root); }
};

i64 qpow(i64 a, i64 b) {
	return b ? (b & 1 ? (a * qpow(a, b - 1) % p) : (qpow(a * a % p, b / 2) % p)) : 1;
}

i64 opt(i64 a, i64 b) { return a * b % p; }
i64 e_val() { return 1; }
i64 apply(i64 a, i64 b, int size) { return a * b % p; }
i64 attach(i64 a, i64 b) { return a * b % p; }
i64 e_tag() { return 1; }

void solve() {
	int n, m;
	std::cin >> n >> m;

	std::vector<int> a(n), b(n);
	std::map<int, int> tot;
	for (int& i : a) std::cin >> i;
	std::sort(a.begin(), a.end());
	b = a;
	b.erase(std::unique(b.begin(), b.end()), b.end());
	for (int i : a) {
		if (tot.count(i))
			++tot[i];
		else
			tot[i] = 1;
	}

	LazySegmentTree<int, i64, opt, e_val, i64, apply, attach, e_tag> T(b.back() + 1);

	for (auto i : tot) {
		T.set(i.first, i.second);
	}

	i64 ans = 0;
	for (int i = 0; i < (int)b.size(); ++i) {
		int pos = std::lower_bound(b.begin(), b.end(), b[i] + m) - b.begin();
		if (pos - i < m) continue;
		(ans += T.get(b[i], b[i] + m)) %= p;
	}

	std::cout << ans << '\n';
}

int main() {
	int tt;
	std::cin >> tt;
	while (tt--) solve();
	return 0;
}
```


---

