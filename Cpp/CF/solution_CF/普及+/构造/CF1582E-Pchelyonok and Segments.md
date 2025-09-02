# Pchelyonok and Segments

## 题目描述

Pchelyonok decided to give Mila a gift. Pchelenok has already bought an array $ a $ of length $ n $ , but gifting an array is too common. Instead of that, he decided to gift Mila the segments of that array!

Pchelyonok wants his gift to be beautiful, so he decided to choose $ k $ non-overlapping segments of the array $ [l_1,r_1] $ , $ [l_2,r_2] $ , $ \ldots $ $ [l_k,r_k] $ such that:

- the length of the first segment $ [l_1,r_1] $ is $ k $ , the length of the second segment $ [l_2,r_2] $ is $ k-1 $ , $ \ldots $ , the length of the $ k $ -th segment $ [l_k,r_k] $ is $ 1 $
- for each $ i<j $ , the $ i $ -th segment occurs in the array earlier than the $ j $ -th (i.e. $ r_i<l_j $ )
- the sums in these segments are strictly increasing (i.e. let $ sum(l \ldots r) = \sum\limits_{i=l}^{r} a_i $ — the sum of numbers in the segment $ [l,r] $ of the array, then $ sum(l_1 \ldots r_1) < sum(l_2 \ldots r_2) < \ldots < sum(l_k \ldots r_k) $ ).

Pchelenok also wants his gift to be as beautiful as possible, so he asks you to find the maximal value of $ k $ such that he can give Mila a gift!

## 样例 #1

### 输入

```
5
1
1
3
1 2 3
5
1 1 2 2 3
7
1 2 1 1 3 2 6
5
9 6 7 9 7```

### 输出

```
1
1
2
3
1```

# 题解

## 作者：Cht_master (赞：3)

- 题意简述：给定数列 $a$，求最大的 $k$ 使得能从 $a$ 中选出 $k$ 个区间 $[l(i),r(i)]$ 满足 $r(i)-l(i)+1=n-i+1$ 且 $\sum_{j=l(i-1)}^{r(i-1)}a(j)<\sum_{j=l(i)}^{r(i)}a(j)$。

- 题目解析：

  - 观察数据范围，考虑 DP。从前往后难以设计状态，套路性的，考虑从后往前。

  - 定义 $f(i,k)$ 表示从 $[i,n]$ 中选 $k$ 个满足题意的区间，最末一个区间的和的最大值。容易得到状态转移方程：
    $$
    f(i,k)=\max(f(i+1,k),sum(i,i+k-1))
    $$
    从第二个状态转移需要满足：
    $$
    k\ge1,i+k-1\le n,sum(i,i+k-1)< f(i+k,k-1)
    $$

- ```cpp
  #include<bits/stdc++.h>
  #define ll long long
  using namespace std;
  const int mxN(1e5),mxK(5e2);
  const ll INF(1e16);
  int n,a[mxN+5];
  ll psm[mxN+5],f[mxN+5][mxK+5];
  ll SUM(int l,int r){return psm[r]-psm[l-1];}
  int main(){
  	int T;scanf("%d",&T);
  	while(T--){
  		scanf("%d",&n);
  		for(int i(1);i<=n;++i)scanf("%d",&a[i]),psm[i]=psm[i-1]+a[i];
  		
  		for(int i(0);i*i<=((n+1)<<1);++i)f[n+1][i]=-INF;f[n+1][0]=INF;//f(n+1,0)=INF保证了最后k至少大于等于0.
  		
  		for(int i(n);i>=1;--i)
  			for(int j(0);j*j<=((n+1)<<1);++j){
  				f[i][j]=f[i+1][j];
  				if(j&&i+j-1<=n&&SUM(i,i+j-1)<f[i+j][j-1])f[i][j]=max(f[i][j],SUM(i,i+j-1));
  			}
  		for(int i(sqrt((n+1)<<1));;--i)if(f[1][i]>0){printf("%d\n",i);break;}
  	}
  	return 0;
  }
  ```

  

---

## 作者：Alex_Wei (赞：2)

1582E. [Pchelyonok and Segments](https://codeforces.com/contest/1582/problem/E)

简单 DP。如果从前往后考虑，我们不知道第一个区间长度是多少，因此从后往前 DP。设 $f_{i,j}$ 表示计算到第 $i$ 位的后缀，存在一个满足条件且最长区间长度 $[l,r]$ 为 $j$ 的 $[l,r]$ 区间和的最大值。

转移首先 $f_{i,j}\gets f_{i+1,j}$，然后计算 $[i,i+j-1]$ 的区间和 $s$，若 $s<f_{i+j,j-1}$ 则可以选择 $[i,i+j-1]$，令 $f_{i,j}\gets \max(f_{i,j},s)$。

由于区间最长不超过 $\sqrt n$ 故时间复杂度为 $\mathcal{O}(n\sqrt n)$。赛时因为没开 long long 挂了一发 /yun。

```cpp
const int N=1e5+5;
const int K=555;

ll t,n,a[N],s[N];
ll f[N][K];
void solve(){
	cin>>n,mem(f,0,n+5);
	for(int i=1;i<=n;i++)cin>>a[i],s[i]=s[i-1]+a[i];
	for(int i=n;i;i--)
		for(int j=1;j<K&&i+j-1<=n;j++){
			f[i][j]=f[i+1][j];
			if(j==1)cmax(f[i][j],a[i]);
			else if(s[i+j-1]-s[i-1]<f[i+j][j-1])cmax(f[i][j],s[i+j-1]-s[i-1]);
		}
	for(int i=K-1;i;i--)if(f[1][i])return cout<<i<<endl,void();
}

int main(){
	int T; cin>>T;
	while(T--)solve();
    return 0;
}
```

---

## 作者：KSToki (赞：2)

# 题目大意
给定一个长度为 $n$ 的数组 $a$，求最大的 $k$，使得能够从前往后选 $k$ 段，第 $i$ 段长度为 $k-i+1$，且 $k$ 段的和严格递增。
# 题目分析
这个 $k$ 最大只有 $\sqrt n$ 级别，所以可以暴力枚举 $k$，复杂度是 $O(n\sqrt n)$ 的。首先长度递减没办法利用 $k-1$ 的时候的答案，我们可以将数组翻转过来，那么要求改为第 $i$ 段长度为 $i$，且 $k$ 段的和严格递减。既然这样可以利用 $k-1$，肯定更好做。

暴力设出状态 $f[i][j]$ 表示前 $i$ 个数里最长的那段达到了 $j$ 的段和的最大值，每次选择是不是在 $i$ 这里开的长度为 $j$ 的段，判断合法转移即可，还可以不加继承 $f[i-1][j]$ 的值。

代码还是比较简单，注意边界问题。
# 代码
```cpp
#include<bits/stdc++.h>
#define YPC rubbish 
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define LL __int128
#define db double
using namespace std;
#define pb push_back
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first
#define se second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define chkmin(x,y) (x=min(x,y))
#define chkmax(x,y) (x=max(x,y))
#define inv(x) ksm(x,mod-2)
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
#define For(i,x,y) for(R int i=x;i<=y;++i)
#define For2(i,x,y,k) for(R int i=x;i<=y;i+=k)
#define Rof(i,x,y) for(R int i=x;i>=y;--i)
#define Rof2(i,x,y,k) for(R int i=x;i>=y;i-=k)
#define ForG(i,edge,x) for(auto i:edge[x])
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,a[100001];
ll s[100001],f[100001][501];
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		For(i,1,n)
		{
			a[i]=read();
			For(j,0,500)
				f[i][j]=0;
		}
		reverse(a+1,a+n+1);
		For(i,1,n)
			s[i]=s[i-1]+a[i];
		f[0][0]=INF;
		For(i,1,n)
		{
			f[i][0]=INF;
			For(j,1,min(i,500))
			{
				f[i][j]=f[i-1][j];
				if(s[i]-s[i-j]<f[i-j][j-1])
					f[i][j]=max(f[i][j],s[i]-s[i-j]);
			}
		}
		Rof(i,500,1)
			if(f[n][i])
			{
				putint(i);
				break;
			}
	}
	return 0;
}
```

---

## 作者：mazy (赞：2)

写篇简单的题解

注意到区间 $i$ 一定在 $j$ 左边，于是这便是一个线性 DP 可以解决的问题。

感觉区间长度由长变短有些别扭，可以先 `reverse` 一下。这样对应的区间长度就是 $1,2,\cdots,k$ 了，此时我们要使得 $sum$ 严格单调减,可以预处理一下前缀和的区间长度。

发现如果我们设 $dp[i][j]$ 表示前 $i$ 个数中最大区间和为 $j$ 的区间数会炸掉空间,还不好转移。
套路式的，我们交换代价和dp维护的内容：设 $dp[i][j]$ 表示前 $i$ 个数中选了 $j$ 个区间的最大当前区间和。求一个使 $dp[i][j]\not= 0$ 的最大的 $j$ 的值( $\sup\{j\}$ )。

转移方程:

$$
\begin{cases}
	dp[i][j]=\max(dp[i][j],dp[i-1][j]+a[i]-a[i-j])
    \quad sat. COND1.
    \\
    dp[i][j]=\max(dp[i][j],pre[i]-pre[i-j])
    \quad sat.COND2
\end{cases}
$$

$$
\begin{cases}
	COND1:sum(i-j,i-1)=dp[i-1][j])\wedge (dp[i-1][j]+a[i]-a[i-j]<dp[i-j-1][j-1]
    \\
    COND2:sum(i,j)<dp[i-j][j-1]
\end{cases}
$$

对于第一种情况 (COND1):

我们考虑将长度为 $j$ 的区间从 $i-1$ 平移到 $i$ ，第 $i-1$ 个和就是从 $dp[i-1][j]$ 扩展到 $dp[i][j]$ ,只需要计算变化即可，注意维护 $sum$ 单调。

对于第二种情况 (COND2):

我们考虑将长度为 $j-1$ 的长度的区间往后加一个长度为 $j$ 的区间。当前区间长度为差分的 $pre[i]-pre[i-j]$ ,注意维护 $sum$ 单调。

由于 $n=\sum_{j=1}^k j$ ,所以 $k$ 为 $\sqrt{n}$ 级别的。

时间复杂度 $O(n\sqrt{n})$。

**特别提醒：**

此时 dp 值的设定是前缀中最大的，而我们第一种情况的转移要求的是第 $i-1$ 个位置是第二种情况算出来的最大值，(否则不是连续区间，不能扩展）因此要判断 $sum(i-j,i-1)=dp[i-1][j]$。
(我被这个问题卡了好久)

附AC代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int INF = 0x3f3f3f3f;
const int MAXN= (int)1e5+7;

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<48||ch>57) {if(ch=='-') f=-1;ch=getchar();}
    while(ch>=48&&ch<=57)   x=x*10+ch-48,ch=getchar();
    return x*f;
}

int n;
ll dp[MAXN][507],pre[MAXN],sum[507],a[MAXN];

void solve()
{
	for(int i=1;i<=n;i++)	pre[i]=pre[i-1]+a[i];
	int ans=1;
	for(int i=1;i<=n;i++)	dp[i][1]=max(dp[i-1][1],a[i]);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;sum[j]<=i;j++)
		{
			if(j^1)	dp[i][j]=dp[i-1][j];
			if(pre[i-1]-pre[i-j-1]==dp[i-1][j]&&dp[i-1][j]+a[i]-a[i-j]<dp[i-j-1][j-1])
				dp[i][j]=max(dp[i][j],dp[i-1][j]+a[i]-a[i-j]);
			if(pre[i]-pre[i-j]<dp[i-j][j-1])
			{
				ans=max(ans,j);
				dp[i][j]=max(dp[i][j],pre[i]-pre[i-j]);
			}
		}
	}
	printf("%d\n",ans);
}

signed main()
{
	int T=read();
	for(int i=1;i<=500;i++)	sum[i]=sum[i-1]+(ll)i;
    while(T--)
	{
		n=read();
		for(int i=1;i<=n;i++)	a[i]=read();
		reverse(a+1,a+n+1);
		solve();
	}
    return 0;
}
```

---

## 作者：XiaoQuQu (赞：1)

考虑 DP，发现 $k$ 最多不超过 $O(\sqrt n)$，所以设 $f_{i,j}$ 表示考虑后 $i$ 个数，分成 $j$ 段，当前这段（也就是长度为 $j$ 的这一段）的和的最大值，发现可以简单转移，即 $f_{i,j}=\max(f_{i+1,j},(sum_{i+j-1}-sum_{i-1})[sum_{i+j-1}-sum_{i-1} > f_{i+j,j-1}])$。

最后时间复杂度 $O(n \sqrt n)$。

```cpp
const int MAXN = 500, MAXQ = 1e5 + 5;
int n, f[MAXQ][MAXN], a[MAXQ], s[MAXQ];

void work() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + a[i];
	for (int i = n; i >= 1; --i) {
		f[i][1] = max(a[i], f[i + 1][1]);
		for (int j = 2; j <= (n - i + 1); ++j) {
			if (j * (j + 1) / 2 > (n - i + 1)) break;
			f[i][j] = f[i + 1][j];
			if (f[i + j][j - 1] > s[i + j - 1] - s[i - 1]) 
				f[i][j] = max(f[i][j], s[i + j - 1] - s[i - 1]);
		}
	}
	int ans = 0;
	for (int i = 1; i < MAXN; ++i) {
		if (f[1][i] > 0) ans = i;
	}
	for (int i = n; i >= 1; --i) {
		for (int j = 1; j <= (n - i + 1); ++j) {
			if (j * (j + 1) / 2 > (n - i + 1)) break;
			f[i][j] = INT_MIN;
		}
	}
	cout << ans << endl;
}
```


---

## 作者：Day_Tao (赞：0)

题目的要求约束感觉有点大，不妨给转化成翻转序列之后划分区间长度增加、区间和递减。观察这个数据范围很根号，分析了一下发现最多划分 $\mathcal{O}(\sqrt{n})$ 段。考虑从这里入手。

不难发现，对于同一个前缀划分同一种段数，我们不关心具体怎么划分的，只会关心这样划分的最后一段的区间和是多少。这样我们就可以设 $f_{i,j}$ 表示以 $i$ 结尾，已经划分了 $j$ 段最后一段区间之和。记 $s$ 为前缀和数组。转移：

$$f_{i,j}=\begin{cases}f_{i-1,j}&f_{i-j,j-1}\le s_i-s_{i-j}\\\max\{f_{i-1,j},s_i-s_{i-j}\}&f_{i-j,j-1}>s_i-s_{i-j}\end{cases}$$

初始化为 $f_{0,j}=\infty$。时间复杂度 $\mathcal{O}(n\sqrt{n})$。

**Code：**

```cpp
int n,f[N][500],a[N],s[N],ans;
inline void SOLVE(){
	n=rd();for(int i=1;i<=n;i++)a[i]=rd(),f[i][0]=INF;f[0][0]=INF;
	reverse(a+1,a+n+1);for(int i=1;i<=n;i++)s[i]=s[i-1]+a[i];
	for(int i=1;i<=n;i++)for(int j=1;j*(j+1)/2<=i;j++)
		if(f[i-j][j-1]<=s[i]-s[i-j])f[i][j]=f[i-1][j];
		else f[i][j]=max(f[i-1][j],s[i]-s[i-j]);
	for(int i=1;i*(i+1)/2<=n;i++)if(f[n][i])ans=i;
	printf("%lld\n",ans);return ;
}
```

---

## 作者：laboba (赞：0)

一个不是很难的DP。首先很容易猜到状态 $f_{i,j}$ 表示表示考虑 $i\sim n$ 选出 $j$ 个区间时第 $j$ 个区间，但是会发现如果储存是否能取到 $(i,j)$，会十分难转移，因为 $sum(l_j,r_j)<sum(l_{j-1},r_{j-1})$ 这个限制很难体现。所以可以让   $f_{i,j}$ 表示 $i\sim n$ 选出 $j$ 个区间时第 $j$ 个区间的和所能取到的最大值。

接下来考虑转移：显然有两种可能：第 $j$ 个区间包含或不包含 $a_i$，分别对应 $sum_{i\sim i+j-1}$、$f_{i+1,j}$，其中第一种转移需要满足条件 $sum_{i\sim i+j-1}<f_{i+j,j-1}$ 最后答案就是满足 $f_{1,i}>0$ 最大的 $i$。

Code：
```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int N=100100,sqN=500;
int n;
int a[N];
long long sum[N];
long long f[N][sqN];
void init(){
	for(int i=1;i<=n;i++)sum[i]=0;
	for(int i=1;i<=n;i++)for(int j=1;j*(j+1)/2<=n;j++)f[i][j]=0;
}
int main(){
	int t;
	scanf("%d",&t);
	for(int i=1;i<N;i++)f[i][0]=1000000000000000;//f[i][1]没有转移限制 
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]),sum[i]=sum[i-1]+a[i];
		for(int i=n;i>=1;i--){
			for(int j=1;i+j*(j+1)/2-1<=n;j++)f[i][j]=max(f[i+1][j],(sum[i+j-1]-sum[i-1]<f[i+j][j-1])*(sum[i+j-1]-sum[i-1]));	
		}
		for(int i=sqrt(n*2)+1;i>=1;i--)if(f[1][i]){printf("%d\n",i);break;}
		init();
	}
}
```


---

