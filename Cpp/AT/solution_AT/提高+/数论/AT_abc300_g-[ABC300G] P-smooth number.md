# [ABC300G] P-smooth number

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc300/tasks/abc300_g

$ k $ 以下の素数のみを素因数に持つ正整数を $ k $-smooth number と呼びます。  
 整数 $ N $ および $ 100 $ 以下の素数 $ P $ が与えられるので、 $ N $ 以下の $ P $-smooth number の個数を求めてください。

## 说明/提示

### 制約

- $ N $ は $ 1\ \le\ N\ \le\ 10^{16} $ を満たす整数
- $ P $ は $ 2\ \le\ P\ \le\ 100 $ を満たす素数
 
### Sample Explanation 1

$ 36 $ 以下の $ 3 $-smooth number は $ 1,2,3,4,6,8,9,12,16,18,24,27,32,36 $ の $ 14 $ 個です。 $ 1 $ は任意の素数 $ k $ に対して $ k $-smooth number であることに注意してください。

## 样例 #1

### 输入

```
36 3```

### 输出

```
14```

## 样例 #2

### 输入

```
10000000000000000 97```

### 输出

```
2345134674```

# 题解

## 作者：zhouyuhang (赞：5)

根据 $\lfloor\frac{a}{bc}\rfloor=\lfloor\frac{\lfloor\frac{a}{b}\rfloor}{c}\rfloor$，我们可以实现以下代码（使用 dfs）：

```cpp
#include <iostream>
using namespace std;
long long n;
int p, num = 0, prime[26];
inline void init() {
    static int mark[110];
    for (int i = 2; i <= p; i++) {
        if (!mark[i]) {
            prime[num++] = i;
        }
        for (int j = 0, t = 2; j < num
                && i * t <= p; t = prime[++j]) {
            mark[i * t] = 1;
            if (i % t == 0) {
                break;
            }
        }
    }
}
unsigned int ans = 0;
void dfs(long long n, int p) {
    if (!p) {
        ans += __lg(n) + 1;
        return;
    }
    dfs(n, p - 1);
    if (n >= prime[p]) {
        dfs(n / prime[p], p);
    }
}
int main() {
    cin >> n >> p;
    init(), dfs(n, num - 1);
    cout << ans << endl;
    return 0;
}
```

注意：代码对 $p=2$ 时的情形作了特别处理。此时的答案是 $\lfloor\log_2n\rfloor+1$。

但是这段代码在极限数据下需要运行大约 7 秒。我们应该如何优化它呢？

**记忆化搜索！** 当然，如果记忆化的范围非常大，它会运行得很慢。因此，我们仅在值范围相对较小时记录答案（例如 $2^{16}$）。

```cpp
#include <iostream>
using namespace std;
long long n;
int p, num = 0, prime[26];
inline void init() {
    static int mark[110];
    for (int i = 2; i <= p; i++) {
        if (!mark[i]) {
            prime[num++] = i;
        }
        for (int j = 0, t = 2; j < num
                && i * t <= p; t = prime[++j]) {
            mark[i * t] = 1;
            if (i % t == 0) {
                break;
            }
        }
    }
}
const int N = 1 << 16;
unsigned int ans = 0, f[25][N];
void dfs(long long n, int p) {
    if (n < N && f[p][n]) {
        ans += f[p][n];
        return;
    }
    if (!p) {
        ans += __lg(n) + 1;
        return;
    }
    unsigned int Ans = ans;
    dfs(n, p - 1);
    if (n >= prime[p]) {
        dfs(n / prime[p], p);
    }
    if (n < N) {
        f[p][n] = ans - Ans;
    }
}
int main() {
    cin >> n >> p;
    init(), dfs(n, num - 1);
    cout << ans << endl;
    return 0;
}
```

这段代码完全足以通过问题，它只需要运行大约 250 毫秒。

但是我们也可以通过将记忆化更改为 dp 预处理来减少常数。（它只需要运行大约 160 毫秒。）

```cpp
#include <iostream>
using namespace std;
long long n;
int p, num = 0, prime[26];
const int N = 1 << 18;
unsigned int ans = 0, f[25][N];
inline void init() {
    static int mark[110];
    for (int i = 2; i <= p; i++) {
        if (!mark[i]) {
            prime[num++] = i;
        }
        for (int j = 0, t = 2; j < num
                && i * t <= p; t = prime[++j]) {
            mark[i * t] = 1;
            if (i % t == 0) {
                break;
            }
        }
    }
    for (int i = 1; i < N; i++) {
        f[0][i] = __lg(i) + 1;
    }
    for (int i = 1; i < num; i++) {
        for (int t = prime[i], j = 0; j < N; j += t) {
            unsigned int V = f[i][j / t];
            for (int k = j; k < N && k < j + t; k++) {
                f[i][k] = V + f[i - 1][k];
            }
        }
    }
}
void dfs(long long n, int p) {
    if (n < N) {
        ans += f[p][n];
        return;
    }
    if (!p) {
        ans += __lg(n) + 1;
        return;
    }
    dfs(n, p - 1);
    if (n >= prime[p]) {
        dfs(n / prime[p], p);
    }
}
int main() {
    cin >> n >> p;
    init(), dfs(n, num - 1);
    cout << ans << endl;
    return 0;
}
```

---

## 作者：syxmz (赞：4)

### 1 解法分析

这道题看着很像搜索，于是你可以写出来一份 TLE 代码。

$dfs(x,y)$ 表示在 $(x, prm[y])$ 下的答案。
其中 $prm[37]$ 来存下 $100$ 内的所有质数，因只有 $25$ 个所以直接存即可（推荐打表）。

接下来考虑优化。

首先就是一个记忆化搜索，然后再剪枝。

十分显然的，从大质数向小质数搜可以有效避免无意义的搜索。

于是复杂度玄学起来，你也就 AC 了。

注：$prm$ 数组中的最后一项 $1145141919810$ 的目的是为了防止跳质数的时候跳出去，当然也可以用特判避免跳出。
### 2 解法总结

记搜 + 剪枝。

### 3 AC Code
```cpp
#include <bits/stdc++.h>
#define int long long
#define N 1000000
using namespace std;

int ans;
int n, m, inf;
int dp[26][2000007];

int prm[37] = {
	2, 3, 5, 7,
	11, 13, 17, 19,
	23, 29, 31, 37,
	41, 43, 47,
	53, 59, 61, 67,
	71, 73, 79,
	83, 89, 97,
	1145141919810
};


void dfs(int x, int y) {
	if (x <= N && dp[y][x]) {
		ans += dp[y][x];
		return ;
	}
	if (!y) {
		ans = ans + __lg(x) + 1;
		return ;
	}
	int cnt = ans;
	dfs(x, y - 1);
	if (x >= prm[y])
		dfs(x / prm[y], y);
	if (x <= N)
		dp[y][x] = ans - cnt;
}

signed main() {
	scanf("%lld%lld", &n, &m);
	for (; prm[inf + 1] <= m; ++inf)
		;
	dfs(n, inf);
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Jie_Xu_Sheng (赞：4)

### 题意

在 $1$ 到 $n$ 中，有多少个数的所有质因数均不超过 $p$ $(p\leq100)$。

### 解法

meet-in-the-middle

看到极端数据的输出仅仅 $2345134674$ , 可以采用类似 meet-in-the-middle 的方法来解决。

分别存储小于等于 $n$ 的数中只由 $2,3,5,7,11,13$ 这 $6$ 个质因数组成的数和只由 $\geq17$ 的质数组成的数。极端数据下，第一个数组有 $511985$ 个数，第二个数组有 $8860016$ 个数，$4s$ 的限时刚好可以把两个数组排序完成。然后再枚举第一个数组中的数，二分第二个数组可以取到的数的位置。还需要特判 $p<17$ 的情况。 细节具体见代码。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[30]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101};
int c235[600010] /*存储2，3，5，7，11，13构成的数的数组*/;
int cnt,tot,p,k,ans;
int c123[9000010] /*存储>=17的质数构成的数的数组*/;
void dfs235(int x,int j){
	if(x==7){
		c235[++cnt]=j;
		return ;
	}
	dfs235(x+1,j);
	for(int i=1;;i++){
		j*=a[x];
		if(j>n) return ;
		dfs235(x+1,j);
	}
}
void dfs(int x,int j){
	if(x==k+1){
		c123[++tot]=j;
		return ;
	}
	dfs(x+1,j);
	for(int i=1;;i++){
		j*=a[x];
		if(j>n) return ;
		dfs(x+1,j);
	}
}
void dfs1(int x,int j){
	if(x==k+1){
		ans++;
		return ;
	}
	dfs1(x+1,j);
	for(int i=1;;i++){
		j*=a[x];
		if(j>n) return ;
		dfs1(x+1,j);
	}
}
signed main(){
	cin>>n>>p;
	dfs235(1,1);
	sort(c235+1,c235+cnt+1);
	for(int i=1;i<=27;i++){
		if(a[i]<=p) k=i;
		else break;
	}
	if(k>=7){
		dfs(7,1);
		sort(c123+1,c123+tot+1);
		for(int i=1;i<=cnt;i++){
			int kk=n/c235[i];
			int l=1,r=tot,rt=0;
			while(l<=r){
				int mid=(l+r)/2;
				if(c123[mid]<=kk){
					rt=mid;
					l=mid+1;
				}else r=mid-1;
			}
			ans+=rt;
		}
		cout<<ans;
		return 0;
	}else{ //特判p<17的情况 
		dfs1(1,1);
		cout<<ans<<endl;
		return 0;
	}
}
```


---

## 作者：elbissoPtImaerD (赞：2)

G 放这个？

观察到：$p$ 很小，考虑用 $\prod p_i ^ {\alpha _ i}$ 的形式计数。

不难想到：枚举 $\alpha_i$，一算复杂度好像不大好看？

可以套路地 meet-in-middle：将 $\le p$ 的所有素数分成大小相等的两组，先对左边枚举指数，再对右边枚举指数，把右边的每一个结果在左边计数即可。

可以将素数随机分成两组，更均摊，复杂度更正确。

细节看代码：
```cpp
const int N=103;
bool*MS;
int p,m;
ll n,ans;
bool vis[N];
sd vector<int>a;
sd vector<ll>b;
bool*MT;
void dfs(int o,ll w,bool tag)
{
	if(!~o)
	{
		if(tag) ans+=sd upper_bound(begin(b),end(b),n/w)-begin(b);
		else b.push_back(w);
		return;
	}
	for(;w<=n;w*=a[o]) dfs(o-1,w,tag);
	return;
}
void Solve()
{
	rd(n,p);
	for(int i=2;i<=p;++i)
	{
		vis[i]||(a.push_back(i),7);
		for(int j=i;j<=p;j+=i) vis[j]|=1;
	}
	sd random_shuffle(begin(a),end(a)),m=a.size()-1>>1,dfs(m,1,false);
	sd stable_sort(begin(b),end(b)),sd reverse(begin(a),end(a)),m=a.size()-1-m-1,dfs(m,1,true);
	wrt(ans);
	return;
}
```

[$\color{green}{\checkmark}$](https://atcoder.jp/contests/abc300/submissions/42097882)

---

## 作者：Register_int (赞：2)

不得不说 ABC 的 G 真的是一场比一场科幻。

可以发现在极限数据下状态也没多少个，直接考虑记忆化。然而，直接记忆化无法通过，考虑如下两个剪枝：

1. 当搜索到 $p=2$ 时直接返回答案 $(\log_2 n)+1$。
2. 对 $n$ 做出限制，在 $n$ 较小时再记忆化。

额然后就过了，复杂度 $O(\text{玄学})$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e2 + 10;

int p[MAXN], tot; bool vis[MAXN];

inline 
void init(int n) {
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) p[tot++] = i;
		for (int j = 0; j < tot; j++) {
			if (i * p[j] > n) break;
			vis[i * p[j]] = 1;
			if (i % p[j] == 0) break;
		}
	}
}

ll dp[25][114514];

inline 
ll dfs(ll n, int k) {
	if (n < 114514 && dp[k][n]) return dp[k][n];
	if (!k) return __lg(n) + 1;
	ll ans = dfs(n, k - 1);
	if (n >= p[k]) ans += dfs(n / p[k], k);
	return n < 114514 ? dp[k][n] = ans : ans;
}

ll n; int k;

int main() {
	scanf("%lld%d", &n, &k), init(k);
	printf("%lld", dfs(n, tot - 1));
}
```

---

## 作者：rzh01014 (赞：1)

## [ABC300G P-smooth number](https://www.luogu.com.cn/problem/AT_abc300_g)
### 前言
第一次做这么水的 G 题，蒟蒻竟然可以场切。
### 题目描述
一个正整数被称为“$k$ 阶平滑数”，当且仅当它的任意一个素因子不超过 $k$。
给定正整数 $N$ 和素数 $P$。问不超过 $N$ 的“$P$ 阶平滑数”有多少个。

### 做法
读懂题目后，可以先打个 DFS 暴力，枚举所有情况。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+5;
int n,p,prime[N],cnt,ans;
int vis[N];
void init(int x){
	vis[1]=1;
	for(int i=2;i<=x;i++){
		if(!vis[i]){
			vis[i]=2;
			prime[cnt++]=i;
		}
		for(int j=0;j<cnt;j++){
			if(i*prime[j]>x) break;
			vis[i*prime[j]]=1;
			if(i%prime[j]==0) break;
		}
	}
}
void dfs(int u,int noww){
	if(noww>n) return;
	ans++;
	if(noww*prime[u]>n||prime[u]>p) return;
	int k=prime[u];
	while(noww*k<=n){
		dfs(u+1,noww*k);
		k*=prime[u];
	}
	for(int i=u+1;i<cnt;i++){
		if(noww*prime[i]>n||prime[i]>p) break;
		dfs(i,noww*prime[i]);
	}
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>p;
	init(105);
	dfs(0,1);
	cout<<ans;
	return 0;
}
```
不难发现，题目的时限不允许暴力通过，这份代码跑 $n=10^{16}$ 的极限约为 $7.5$ 秒。此时就需要其它的减枝。   
我们可以发现在暴力的过程中，会重复枚举许多情况，因此可以进行记忆化搜索。   
对于本题也可以进行折半搜索，可以从样例中发现，在最大情况下只有 $2\times 10^9$ 种情况，折半搜索所需的情况不会超过 $10^6$ 种。   
下面的代码中使用的是折半搜索，先进行一次搜索记录小于 $2\times 10^5$ 的情况，在第二次搜索时在当期值大于 $\frac{n}{2\times 10^5}$ 时进行剪枝。   
由于是搜索，此题的复杂度为玄学。
### Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+5;
int n,p,prime[N],cnt,ans,sum[200005][105];
int vis[N];
void init(int x){
	vis[1]=1;
	for(int i=2;i<=x;i++){
		if(!vis[i]){
			vis[i]=2;
			prime[cnt++]=i;
		}
		for(int j=0;j<cnt;j++){
			if(i*prime[j]>x) break;
			vis[i*prime[j]]=1;
			if(i%prime[j]==0) break;
		}
	}
}
void dfs1(int u,int noww,int minn){
	if(noww>200000) return;
	sum[noww][minn]++;
	if(noww*prime[u]>200000||prime[u]>p) return;
	int k=prime[u];
	while(noww*k<=200000){
		dfs1(u+1,noww*k,min(u,minn));
		k*=prime[u];
	}
	for(int i=u+1;i<cnt;i++){
		if(noww*prime[i]>200000||prime[i]>p) break;
		dfs1(i,noww*prime[i],min(i,minn));
	}
}
void dfs(int u,int noww){
	if(noww>n) return;
	if(n/noww<=200000){
		ans+=sum[n/noww][u];
		return;
	}
	ans++;
	if(noww*prime[u]>n||prime[u]>p) return;
	int k=prime[u];
	while(noww*k<=n){
		dfs(u+1,noww*k);
		k*=prime[u];
	}
	for(int i=u+1;i<cnt;i++){
		if(noww*prime[i]>n||prime[i]>p) break;
		dfs(i,noww*prime[i]);
	}
}
void dfs3(int u,int noww){
	if(noww>n) return;
	ans++;
	if(noww*prime[u]>n||prime[u]>p) return;
	int k=prime[u];
	while(noww*k<=n){
		dfs3(u+1,noww*k);
		k*=prime[u];
	}
	for(int i=u+1;i<cnt;i++){
		if(noww*prime[i]>n||prime[i]>p) break;
		dfs3(i,noww*prime[i]);
	}
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>p;
	init(105);
	if(n<=1e8){
		dfs3(0,1);
		cout<<ans;
	}
	else{
		dfs1(0,1,100);
		for(int i=1;i<=200000;i++){
			for(int j=1;j<=100;j++){
				sum[i][j]+=sum[i-1][j];
			}
		}
		for(int j=100;j>=1;j--){
			for(int i=1;i<=200000;i++){
				sum[i][j]+=sum[i][j+1];
			}
		}
		dfs(0,1);
		cout<<ans;
	}
	return 0;
}
```

---

## 作者：AC_love (赞：1)

从样例二可以看出：本题答案的上界为 $2.3 \times 10^9$。因此对于复杂度为 $O(\text{答案})$ 的爆搜必定会 TLE，考虑其他方式计算答案。

我们可以将质数分成两部分，分别处理前后两部分的所有因数。

注意到：前面一部分的因数和后面一部分的因数相乘可以得到一个新的 $P$ 阶平滑数。我们只需要统计有多少个新的 $P$ 阶平滑数小于等于 $N$ 即可。

问题转化成：给出两个数组，判断有多少个跨数组的乘积小于等于 $N$。

这玩意很板，提供两种做法：

- 将第二个数组排序，然后对于每个第一个数组中的数，都在第二个数组中二分找它能配对的最大的数，复杂度 $O(n \log n)$。
- 将两个数组都排序，注意到当第一个数组中的数增大时，第二个数组中可选的最大数一定单调不增，因此可以双指针，复杂度 $O(n)$。

两个数组的大小 $n$ 大概在 $10^6$ 的级别，两种方法都可以过。

[code](https://atcoder.jp/contests/abc300/submissions/59071753)

---

## 作者：ktq_cpp (赞：1)

题目大意：给你两个数 $n$ 和 $p$，问有多少个数 $1 \leq x \leq n$ 它的质因子都小于等于 $p$，保证 $p$ 为质数。

装换一下题意，可以改变成枚举 $1$ 到 $p$ 中的质数的指数，并使得最终乘积小于等于 $n$。

考虑折半搜索，我们将 $1$ 到 $p$ 中的质数分为两半，先计算前一半能达到的数的情况，然后再枚举后半段的情况，看前半段有多少个质数和后半段的乘积小于等于 $n$，对于所有这样的情况求和即可。

这里有一个小优化，如果将小的质数全放前面或后面，那么前半段的情况数和后半段的情况数差距过大，会增大常数，所以可以采取每个大的质数后面跟一个小的质数，加快程序运行速度。

```cpp
#include<bits/stdc++.h>
#define int long long
#define repe(i,l,r) for(int (i)=l;(i)<=r;(i)++)
#define rep(i,n) for(int (i)=1;(i)<=n;(i)++)
#define FOR(i,r,l) for(int (i)=r;(i)>=l;(i)--)
#define INF 0x3f3f3f
#define pii pair<int,int>
#define mpr make_pair
#define pb push_back
#define ALL(v) (v).begin(),(v).end()
#define rsort(v) sort(ALL(v),greater<int>())
#define lb(v,x) (int)(lower_bound(ALL(v),x)-v.begin())
#define ub(v,x) (int)(upper_bound(ALL(v),x)-v.begin())
#define uni(v) v.resize(unique(ALL(v))-v.begin())
using namespace std;
int read(){int sum=0,f=1;char c;c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){sum=(sum<<1)+(sum<<3)+(c-'0');c=getchar();}return sum*f;}
void out(int x){if(x<0){x=-x;putchar('-');}if(x>=10)out(x/10);putchar(x%10+'0');}
template <typename T>void die(T s){cout<<s<<endl;exit(0);}
int fast(int a,int b,int P){int res=1;if(P<=0){while(b){if(b&1)res=res*a;a=a*a;b>>=1;}}else{while(b){if(b&1)res=res*a%P;a=a*a%P;b>>=1;}}return res;}
template <typename T>void chkmax(T& a,T b){if(a<b)a=b;return;}
template <typename T>void chkmin(T& a,T b){if(a>b)a=b;return;}
int n,P;
int pri[105],cnt;
int pos[105];
bool vis[105];
void init(){
	repe(i,2,P){
		if(!vis[i])pri[++cnt]=i,pos[i]=cnt;
		for(int j=i+i;j<=P;j+=i)vis[j]=1;
	}
	return;
}
int ans;
vector<int> v;
void dfs(int p,int x){
//	cout<<p<<' '<<x<<endl;
	if(p==cnt/2+1){
//		cout<<u<<endl;
		v.pb(x);
		return;
	}
	for(int i=0;x<=n;i++){
		dfs(p+1,x);
		x*=pri[p];
	}
	return;
}
void get_ans(int p,int x){
	if(p==cnt/2){
		ans=ans+(upper_bound(ALL(v),n/x)-v.begin());
		return;
	}
	for(int i=0;x<=n;i++){
		get_ans(p-1,x);
		x*=pri[p];
	}
	return;
}
signed main(){
	n=read(),P=read();
	init();
	for(int i=1;i<=cnt/2;i+=2){
		swap(pri[i],pri[cnt-i+1]);
	}
	dfs(1,1);
	sort(ALL(v));
	get_ans(pos[P],1);
	out(ans);
	return 0;
}
```

---

## 作者：Jian_Yu (赞：0)

注意到极限数据的输出很小，考虑直接搜索，但是发现不仅会 TLE 还会 MLE。

然后发现 $p$ 很小，考虑 meet in middle，这个过程中可以用 `random_shuffle` 来保证时间和空间上两半的平衡。

具体实现中，可以先用两次搜索把两半的数全部与处理出来并排序，然后直接双指针即可快速统计答案。

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>
#include <set>
using namespace std;
const int N = 1e3 + 5, MOD = 998244353;
#define For(i,a,b) for(int i(a);i<=(b);++i)
#define Rep(i,a,b) for(int i(a);i<(b);++i)
typedef long long i64;

inline int isprime(int x) {
	for(int i = 2; i * i <= x; ++i)
		if(x % i == 0) return 0;
	return 1;
}

i64 n, p, ans = 0;
basic_string<i64> pri, pp;
basic_string<i64> v1, v2;

void dfs(int i, i64 val) {
	if(i == (int)pri.size()) {
		v1 += val;
		return ;
	}
	i64 powv = 1;
	for(int j = 0; j < n; ++j) {
		dfs(i + 1, val * powv);
		powv *= pri[i];
		if(val * powv > n) return ;
	}
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> p;
	for(int i = 2; i <= p; ++i) if(isprime(i)) pp += i;
	random_shuffle(pp.begin(), pp.end());
	for(int i = 0; i < (int)pp.size()/2; ++i)
		pri += pp[i];
	dfs(0, 1);
	swap(v1, v2);
	pri.clear();
	for(int i = (int)pp.size()/2; i < (int)pp.size(); ++i)
		pri += pp[i];
	dfs(0, 1);
	int k = v2.size() - 1;
	sort(v1.begin(), v1.end()), sort(v2.begin(), v2.end());
	for(int i = 0; i < (int)v1.size(); ++i) {
		i64 w = n / v1[i];
		while(v2[k] > w && k >= 0) --k;
		if(k == -1) break;
		ans += k + 1;
	}
	cout << ans << "\n";
}
```

---

## 作者：sunkuangzheng (赞：0)

题解区都在记忆化 / meet-in-the-middle，但是事实上直接爆搜就能过。

预处理质数和其次幂，从后往前枚举每一个质数的次数，当 $p=2$ 是直接返回 $\log$ 的值。注意到极端数据答案只有 $2\times10^9$，去除掉 $p=2$ 的部分情况数量会更少。$4$ 秒还是能跑过的。

$3.1$ 秒喜提最劣解 /cf

```cpp
/**
 *    author: sunkuangzheng
 *    created: 20.02.2024 19:59:49
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
using tril = __int128;
const int N = 5e5+5;
using namespace std;
int T,P; ll n,ans; vector<int> pr; tril pw[105][42];
void dfs(int d,ll pd){
    if(!d) return ans += __lg(n / pd) + 1,void();
    for(int i = 0;i <= 60;i ++){
        if(pw[pr[d]][i] * pd > n) break;
        dfs(d - 1,pd * pw[pr[d]][i]);
    }
}void los(){
    cin >> n >> P;
    auto ck = [&](int x){for(int i = 2;i * i <= x;i ++) if(x % i == 0) return 0; return 1;};
    for(int i = 2;i <= P;i ++) if(ck(i)) pr.push_back(i);
    for(int i = 1;i <= 100;i ++){
        pw[i][0] = 1;
        for(int j = 1;j <= 40;j ++) 
            if(pw[i][j-1] * i >= 1e18) break; else pw[i][j] = pw[i][j-1] * i;
    }dfs(pr.size() - 1,1),cout << ans;
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    for(T = 1;T --;) los();
}
```

---

