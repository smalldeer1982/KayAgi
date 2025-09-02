# Mishka and Divisors

## 题目描述

在玩完美丽的数列后， $Mishka$ 决定学习一些数学。现在她已经学习了乘法，除法和除数的定义，并对以下问题很感兴趣。

对于给定的正整数 $k$ 和长度为 $n$ 的数列 $a$ ，求出在所有元素乘积能被 $k$ 整除的情况下，所含元素最少的非空子集

换句话说，在数组 $a$ 中选出 $m$ 个数，使它们的乘积能被 $k$ 整除，并最小化 $m$ $(m≠0)$

如果有多种符合要求的选择，取所选元素总和最小的一种

## 样例 #1

### 输入

```
5 60
2 4 6 5 2
```

### 输出

```
3
4 3 1 ```

# 题解

## 作者：Zesty_Fox (赞：7)

也许更好的阅读体验：[我的 cnblogs 博客](https://www.cnblogs.com/acceptedzhs/p/15359393.html)

为啥这题没有人写题解啊……~~是这道*2600太水了吗~~

考虑 DP，记 $f(i,j)$ 表示前 $i$ 个数中选出若干个数乘积为 $j$ 的方案中，元素个数最少为多少。

根据题目要求，可以再记一个 $g(i,j)$ 表示元素个数最少的前提下元素之和的最小值。

由于最后乘积要是 $k$ 的倍数（而不是恰好为 $k$），所以使用刷表法更好。转移式很好列出：（$g(i,j)$ 类似）
$$
f(i+1,\gcd(j\times a_i,k))=\min(f(i+1,\gcd(j\times a_i,k)),f(i,j)+1)
$$
但是这样显然是 $O(nk\log k)$ 的，无法通过。

不过，我们发现有很多状态都是无用的。根据转移式，$f(i,j)$ 中的 $j$ 显然只能是 $k$ 的因数，而 $10^{12}$ 以内因数个数最多的数仅有 $6720$ 个因数。

于是，我们预处理出 $k$ 的因数，每次转移时 $j$ 只选择 $k$ 的因数转移即可。

输出方案有一些细节。

时间复杂度 $O(n \operatorname{d}(k)\log k)$ 。

Code:

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;

template<typename T>
inline T read(){
    T x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

#define rdi read<int>
#define rdll read<ll>
#define fi first
#define se second
#define pb push_back
#define mp make_pair

template<typename T>
inline T gcd(T x,T y){return !x?y:gcd(y%x,x);}

const int N=1010,M=7010,INF=0x3f3f3f3f;
int n;
ll a[N],b[N],k;

struct Node{
    int cnt,fr;
    bool use;
    ll sum;
    bool operator < (const Node &rhs)const{
        return cnt!=rhs.cnt?cnt<rhs.cnt:sum<rhs.sum;
    }
};

vector<ll> d;
int cnt;
unordered_map<ll,int> id;
Node f[N][M];

int main(){
#ifdef LOCAL
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
#endif
    n=rdi(),k=rdll();
    for(int i=1;i<=n;i++) a[i]=rdll(),b[i]=gcd(a[i],k);

    if(k==1){
        int tmp=min_element(a+1,a+n+1)-a;
        printf("1\n%d\n",tmp);
        return 0;
    }

    for(ll i=1;i<=k/i;i++){
        if(k%i==0){
            d.pb(i);
            if(i!=k/i) d.pb(k/i);
        }
    }
    sort(d.begin(),d.end());cnt=d.size();
    for(int i=cnt-1;i>=0;i--) id[d[i]]=i;

    for(int i=0;i<=n;i++){
        for(int j=0;j<cnt;j++) f[i][j]={INF,0,0,0};
    }
    f[0][0]={0,0,0,0};
    
    for(int i=0;i<n;i++){
        for(int j=0;j<cnt;j++){
            if(f[i][j].cnt==INF) continue;
            f[i+1][j]=min(f[i+1][j],{f[i][j].cnt,j,0,f[i][j].sum});

            int nxt=id[gcd((__int128)d[j]*b[i+1],(__int128)k)];
            f[i+1][nxt]=min(f[i+1][nxt],{f[i][j].cnt+1,j,1,f[i][j].sum+a[i+1]});
        }
    }
    if(f[n][cnt-1].cnt==INF) puts("-1");
    else{
        ll nowx=n,nowy=cnt-1;vi res;
        while(nowx){
            if(f[nowx][nowy].use) res.pb(nowx);
            nowy=f[nowx][nowy].fr,nowx--;
        }
        printf("%lu\n",res.size());
        for(auto x:res) printf("%d ",x);
        puts("");
    }
    return 0;
}
```



---

## 作者：封禁用户 (赞：1)

首先 $x$ 是 $k$ 的倍数等价于 $\gcd(x, k) = k$，于是我们只关心乘积与 $k$ 的 $\gcd$。

记 $f_{i,j}$ 表示前 $i$ 个数选的数的乘积 $\gcd(x, k) = j$ 的最小总和，转移不难。

复杂度为 $\mathcal O(n \times k)$，不能接受。

发现 $k$ 的因子个数不会很多，而只有 $j$ 是 $k$ 的因数的状态是合法的，所以复杂度可以降到 $\mathcal O(n \times d(k))$。其中 $d(k)$ 为 $k$ 的因子个数，最大为 $6720$，可以通过。

---

## 作者：TernaryTree (赞：1)

一眼了，用洛谷更新的专栏写个题解。考虑 $f_{i,S}$ 表示前 $i$ 个数，选数的乘积中**有用的**部分状态为 $S$ 的最小选数个数。

什么是“**有用的**”呢？假设乘积为 $M$，那么我们实际上只关心 $\gcd(M,k)$。我们注意到 $\gcd(i,k)$ 只有 $d(k)$ 个，而 $10^{12}$ 以内最大因子个数为 $6720$，压下来即可。

转移的时候需要枚举 $a_i$ 的所有质因数转移。同时 $\max \omega(x)$ 是 $11$。方案就 dp 时记录一下最优的 dp 值的来源，最终回溯回去还原方案。所以我们 $\Theta(nd(k)\omega(V))$ 解决了这道题。

注意特判 $k=1$ 的情况。

```cpp
#include <bits/stdc++.h>
#define fs first
#define sc second
#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid ((l + r) >> 1)
#define lc ls, l, mid
#define rc rs, mid + 1, r
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define per(i, r, l) for (int i = (r); i >= (l); --i)
#define gc getchar
#define pc putchar

using namespace std;
using pii = pair<int, int>;
using vi = vector<int>;
using ll = long long;

const int maxn = 1e3 + 10;
const bool multidata = 0;

template<typename T = int>
T read() {
	T x = 0, f = 1; char c = gc();
	while (c < '0' || c > '9') { if (c == '-') f = -f; c = gc(); }
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = gc();
	return x * f;
}

template<typename T = int>
void write(T x) {
	if (x < 0) pc('-'), x = -x;
	if (x < 10) return void (pc(x + '0'));
	write<T>(x / 10), pc(x % 10 + '0');
}

int n; ll k;
ll a[maxn], c[maxn];
pair<int, ll> g[maxn][6721];
pii lst[maxn][6721];
pair<ll, int> bk[maxn];
int m;

void init(ll k) {
	rep(i, 2, sqrt(k)) {
		if (k % i == 0) bk[++m].fs = i;
		while (k % i == 0) ++bk[m].sc, k /= i;
	}
	if (k > 1) bk[++m] = {k, 1};
}

int f(ll x) {
	int now = 1, S = 0;
	rep(j, 1, m) {
		pair<ll, int> i = bk[j];
		int c = 0;
		while (x % i.fs == 0) x /= i.fs, ++c;
		S += now * c;
		now *= (i.sc + 1);
	}
	return S;
}

int trans(int S, int P) {
	int now = 1, T = 0;
	rep(j, 1, m) {
		pair<ll, int> i = bk[j];
		int c = min(S / now % (i.sc + 1) + P / now % (i.sc + 1), i.sc);
		T += now * c, now *= (i.sc + 1);
	}
	return T;
}

int b[maxn];

void dfs(int u, int S) {
	if (!S) return;
	b[u] = lst[u][S].sc;
	dfs(u - 1, lst[u][S].fs);
}

void fake_main() {
	n = read(), k = read<ll>(), init(k);
	rep(i, 1, n) a[i] = f(__gcd(k, c[i] = read<ll>()));
	if (k == 1) {
		puts("1");
		ll ans = c[1];
		rep(i, 1, n) ans = min(ans, c[i]);
		rep(i, 1, n) if (c[i] == ans) return write(i);
	}
	int U = f(k);
	assert(U <= 6720);
	rep(i, 0, n) {
		g[i][0] = {0, 0};
		rep(j, 1, U) g[i][j] = {n + 1, 0};
	}
	rep(i, 0, n - 1) {
		rep(j, 0, U) {
			int nj = trans(j, a[i + 1]);
			if (g[i][j] < g[i + 1][j]) {
				g[i + 1][j] = g[i][j];
				lst[i + 1][j] = {j, 0};
			}
			if (pair<int, ll>{g[i][j].fs + 1, g[i][j].sc + c[i + 1]} < g[i + 1][nj]) {
				g[i + 1][nj] = {g[i][j].fs + 1, g[i][j].sc + c[i + 1]};
				lst[i + 1][nj] = {j, 1};
			}
		}
	}
	if (g[n][U].fs > n) return void (puts("-1"));
	dfs(n, U);
	write(g[n][U].fs), pc('\n');
	rep(i, 1, n) if (b[i]) write(i), pc(' ');
}

signed main() {
	int T = multidata ? read() : 1;
	while (T--) fake_main();
	return 0;
}

```

---

## 作者：2018ty43 (赞：0)

首先考虑 DP，$f_{i,j}$ 表示前 $i$ 个数，积为 $j$ 的最小选择个数。  
这样复杂度是 $O(nk)$ 不可接受。

发现如果当前选的集合积为 $j$，那么这个集合对转移有贡献的只有 $j$ 的质因数分解中，$k$ 每个质因子出现的次数，且不多于在 $k$ 中的次数的前几次出现才是有用的。  
于是可以对 $j$ 状态进行压缩，用一个新字符串 $l_0l_1l_2\sim l_{\omega(k)}$（$\omega(k)$ 表示 $k$ 的质因子个数）表示，其中 $l_i$ 表示 $j$ 的质因数分解中 $k$ 的第 $i$ 个质因子的次数。  
将其排序后可作为数组下标进行转移（或者把它当成每位进制不同的一个数）。  
最后发现状态数最多只有 $d(k)$ 种（$d(k)$ 表示 $k$ 的约数个数）。

最终时间复杂度 $O(nd(k)\omega(k))$。	

题目样例中的样例输入的倒序也是回溯转移路径的顺序。

代码
```c++
#include<cstdio>
#include<cstring>
int n;
long long k;
long long w[90],cs[90],cj[90],tot;
int tc[99];
short f[1009][9000];
long long sum[1009][9000];
short from[1009][9000];
int from2[1009][9000];
long long a[1009];
inline int min(int u,int v)
{
	return (u<v)?u:v;
}
int main()
{
	scanf("%d%lld",&n,&k);
	if(k==1)
	{
		int tk(1);
		for(int i(1);i<=n;++i)scanf("%lld",a+i),tk=(a[tk]<a[i])?tk:i;
		printf("1\n%d",tk);
		return 0;
	}
	cj[0]=1;
	for(int i(2);(long long)i*i<=k;++i)
	{
		if(k%i==0)
		{
			w[++tot]=i;
			while(k%i==0)k/=i,++cs[tot];
			cj[tot]=cj[tot-1]*(cs[tot]+1);
		}
	}
	if(k>1)
	{
		w[++tot]=k;
		cs[tot]=1;
		cj[tot]=cj[tot-1]*(cs[tot]+1);
	}
	cj[tot+1]=1000000000;
	memset(f,63,sizeof(f));
	f[0][0]=0;
	for(int i(1);i<=n;++i)
	{
		scanf("%lld",a+i);
		for(long long j(1),aa(a[i]);j<=tot;++j)
		{
			tc[j]=0;
			while(aa%w[j]==0)aa/=w[j],++tc[j];
		}
		for(int j(cj[tot]);j>=0;--j)
		{
			f[i][j]=f[i-1][j];
			from[i][j]=from[i-1][j];
			from2[i][j]=from2[i-1][j];
			sum[i][j]=sum[i-1][j];
			int jj(0);
			for(int k(1);k<=tot;++k)
			{
				int u(j%cj[k]/cj[k-1]);
				jj+=cj[k-1]*min(u+tc[k],cs[k]);
			}
		//	printf("%d %d %d  %d %d\n",j,jj,cj[tot],cj[1],cj[2]);
			if(f[i][jj]>f[i-1][j]+1||(f[i][jj]==f[i-1][j]+1&&sum[i][jj]>sum[i-1][j]+a[i]))
			{
				f[i][jj]=f[i-1][j]+1;
				sum[i][jj]=sum[i-1][j]+a[i];
				from[i][jj]=i;
				from2[i][jj]=j;
			}
		}
	}
	int now(n),nn(cj[tot]-1);
	if(f[n][cj[tot]-1]>n)
	{
		puts("-1");
		return 0;
	}
	printf("%d\n",f[n][cj[tot]-1]);
	while(f[now][nn])
	{
		printf("%d ",from[now][nn]);
		int te(from2[now][nn]);
		now=from[now][nn]-1;
		nn=te;
	}
}
```

---

