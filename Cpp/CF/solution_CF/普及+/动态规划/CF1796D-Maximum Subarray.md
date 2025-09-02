# Maximum Subarray

## 题目描述

You are given an array $ a_1, a_2, \dots, a_n $ , consisting of $ n $ integers. You are also given two integers $ k $ and $ x $ .

You have to perform the following operation exactly once: add $ x $ to the elements on exactly $ k $ distinct positions, and subtract $ x $ from all the others.

For example, if $ a = [2, -1, 2, 3] $ , $ k = 1 $ , $ x = 2 $ , and we have picked the first element, then after the operation the array $ a = [4, -3, 0, 1] $ .

Let $ f(a) $ be the maximum possible sum of a subarray of $ a $ . The subarray of $ a $ is a contiguous part of the array $ a $ , i. e. the array $ a_i, a_{i + 1}, \dots, a_j $ for some $ 1 \le i \le j \le n $ . An empty subarray should also be considered, it has sum $ 0 $ .

Let the array $ a' $ be the array $ a $ after applying the aforementioned operation. Apply the operation in such a way that $ f(a') $ is the maximum possible, and print the maximum possible value of $ f(a') $ .

## 样例 #1

### 输入

```
4
4 1 2
2 -1 2 3
2 2 3
-1 2
3 0 5
3 2 4
6 2 -8
4 -1 9 -3 7 -8```

### 输出

```
5
7
0
44```

# 题解

## 作者：芷陌陌吖 (赞：17)

> update 2023/03/06：题解样式更新

[更好的阅读体验](https://www.cnblogs.com/zhimomoya-blog/articles/Solution-CF1796D.html)

### 题意

给定三个整数 $n,k,x$ 和一个长度为 $n$ 的序列 $a$。

我们要从这 $n$ 个数中选出 $k$ 个数把它的值加上 $x$，同时把其他没有选择的数字减去 $x$。求进行该操作后的序列 $a'$ 的最大子段和。（同时注意考虑空的子段，其和为 $0$）

包含 $t$ 组测试数据，$1\le t\le10^4$。

数据范围：$1\le n\le2\times10^5$，$0\le k\le\min(20,n)$，$-10^9\le a_i,x\le 10^9$。

### 题解

#### 方法一

发现 $k\le20$，考虑 DP。

我们先把 $a$ 都减去 $x$，现在只需要考虑加上 $k$ 个 $2x$。

设 $f_{i,j}$ 表示在 $a$ 序列的 **$1$ 到 $i$ 的位置上已加上了 $j$ 个 $2x$** 的情况下，以 $i$ 为结尾的最大子段和。
$$
f_{i,j}=\max\{f_{i-1,j}+a_i,f_{i-1,j-1}+a_i+2x,0\}
$$
$\max(f_{i-1,j}+a_i,0)$ 表示 $j$ 不变的情况下求最大子段和，$\max(f_{i-1,j-1}+a_i+2x,0)$ 表示把 $a_i$ 加上 $2x$ 然后再考虑进行最大子段和。

考虑 DP 的细节：（可以结合代码理解）

1. 对于 $f_{i,j}$，所有 $i<j$ 的位置均无意义。
2. $f_{i,j}$ 是在 $a$ 序列的 $1$ 到 $i$ 的位置上已加上了 $j$ 个 $2x$ 的情况下，所以在 $i=j$ 时我们要直接强制执行 $max(f_{i-1,j-1}+a_i+2x,0)$ 的转移，并不进行 $max(f_{i-1,j}+a_i,0)$ 的转移，这样才能保证 DP 数组的正确性。
3. $f_{i,j}$ 是在 $a$ 序列的 $1$ 到 $i$ 的位置上已加上了 $j$ 个 $2x$ 的情况下（注意上面加粗的内容），意味着在 $i$ 位置后还有 $k-j$ 个位置需要加上 $2x$。所以当 $i\le n-(k-j)$ 时就应该计算答案，而不能直接让 $ans=\max_{k\le i\le n}\{f_{i,k}\}$，这样会漏算情况。

时间复杂度 $O(nk)$。

完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,K=21;
int T,n,k;
long long x,f[N][K],a[N],ans;
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while (c<'0'||c>'9')
	{
		if (c=='-')
		{
			f=-1;
		}
		c=getchar();
	}
	while (c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
inline void write(long long x)
{
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x>9)
	{
		write(x/10);
	}
	putchar((x%10)^48);
	return;
}
int main()
{
	T=read();
	while (T--)
	{
		n=read();
		k=read();
		x=read();
		for (int i=1;i<=n;i++)
		{
			a[i]=read()-x;     //把所有数都减去 x
		}
		ans=0;
		for (int i=1;i<=n;i++)
		{
			f[i][0]=max(f[i-1][0]+a[i],0ll);
			if (i<=n-k) ans=max(ans,f[i][0]);//细节 3
			for (int j=1;j<=k;j++)
			{
				if (i<j) continue;       //细节 1
				if (i==j) f[i][j]=max(f[i-1][j-1]+a[i]+x*2,0ll);//细节 2
				else f[i][j]=max({f[i-1][j-1]+a[i]+x*2,f[i-1][j]+a[i],0ll});
				if (i<=n-(k-j)) ans=max(ans,f[i][j]);//细节 3
			}
		}
		write(ans);
		puts("");
	}
	return 0;
}
```

#### 方法二

方法一中提到的“细节 3”就是为了处理 $x<0$ 的情况。如果没有想到，我们可以不考虑 DP，考虑对暴力进行优化。

同样把 $a$ 都减去 $x$，现在只需要考虑加上 $k$ 个 $2x$。

分类讨论：

记 $sum_i$ 表示处理后 $a$ 序列的 $\sum_{k=1}^i a_k$，即前缀和数组。

当 $r-l+1\le k$，
$$
\begin{cases}
ans&=&sum_r-sum_{l-1}+(r-l+1)\times 2x &\text{if }x>0\\
&=&sum_r-sum_{l-1}+2xr-2xl+2x\\
&=&(sum_r+2xr)+(-sum_{l-1}-2xl)+2x\\
ans&=&sum_r-sum_{l-1}+[n-r+l-1<k]\times(k-n+r-l+1)\times 2x &\text{if }x<0\\
&=&
\begin{cases}
(sum_r)+(-sum_{l-1})&\text{if }n-r+l-1\ge k\\
(sum_r+2xr)+(-sum_{l-1}-2xl)+2(k-n+1)x&\text{if }n-r+l-1<k\\
\end{cases}
\end{cases}
$$
当 $r-l+1>k$，
$$
\begin{cases}
ans&=&sum_r-sum_l+k\times 2x &\text{if } x>0\\
&=&(sum_r)+(-sum_l)+2kx\\
ans&=&sum_r-sum_{l-1}+[n-r+l-1<k]\times(k-n+r-l+1)\times 2x &\text{if }x<0\\
&=&
\begin{cases}
(sum_r)+(-sum_{l-1})&\text{if }n-r+l-1\ge k\\
(sum_r+2xr)+(-sum_{l-1}-2xl)+2(k-n+1)x&\text{if }n-r+l-1<k\\
\end{cases}
\end{cases}
$$
（$x<0$ 的时候两种情况的方法是一样的）

我们选择 ST 表维护和 $r$ 相关的值，然后枚举 $l$，就可以 $O(n)$ 算出答案。ST 表预处理时间复杂度 $O(n\log n)$，总时间复杂度 $O(n\log n)$。

完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,K=19;
const long long INF=0x3fffffffffffffff;
int T,lg[N];
long long n,k,x,ans;
long long a[N],sum[N];
struct ST         //ST 表
{
	long long f[N][K];
	inline void prework()
	{
		int t=lg[n];
		for (int j=1;j<=t;j++)
		{
			int w=(1<<(j-1));
			for (int i=1,lim=n-(1<<(j-1))+1;i<=lim;i++)
			{
				f[i][j]=max(f[i][j-1],f[i+w][j-1]);
			}
		}
	}
	inline long long query(int l,int r)
	{
		if (l>r) return -INF;
		int t=lg[r-l+1];
		return max(f[l][t],f[r-(1<<t)+1][t]);
	}
}ST1,ST2;
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while (c<'0'||c>'9')
	{
		if (c=='-')
		{
			f=-1;
		}
		c=getchar();
	}
	while (c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
inline void write(long long x)
{
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x>9)
	{
		write(x/10);
	}
	putchar((x%10)^48);
	return;
}
int main()
{
	lg[0]=-1;
	lg[1]=0;
	for (int i=2;i<=200000;i++)   //预处理 log_2 函数
	{
		lg[i]=lg[i>>1]+1;
	}
	T=read();
	while (T--)
	{
		n=read();
		k=read();
		x=read();
		sum[0]=0;
		for (int i=1;i<=n;i++)
		{
			a[i]=read()-x;
			sum[i]=sum[i-1]+a[i];
		}
		ans=0;
		if (x>=0)                         //下面参考上面的式子
		{
			for (int i=1;i<=n;i++)
			{
				ST1.f[i][0]=sum[i]+2ll*x*i;
				ST2.f[i][0]=sum[i];
			}
			ST1.prework();
			ST2.prework();
			long long p1=2ll*x,p2=2ll*k*x;
			for (int l=1;l<=n;l++)
			{
				ans=max(ans,ST1.query(l,min(l+k-1,n))+(-sum[l-1]-2ll*x*l)+p1);
				ans=max(ans,ST2.query(l+k,n)+(-sum[l-1])+p2);
			}
		}
		else
		{
			for (int i=1;i<=n;i++)
			{
				ST1.f[i][0]=sum[i]+2ll*x*i;
				ST2.f[i][0]=sum[i];
			}
			ST1.prework();
			ST2.prework();
			long long p1=(k-n+1)*2ll*x,p2=0;
			for (int l=1;l<=n;l++)
			{
				ans=max(ans,ST1.query(n+l-k,n)+(-sum[l-1]-2ll*x*l)+p1);
				ans=max(ans,ST2.query(l,min(n,n+l-k-1))+(-sum[l-1])+p2);
			}
		}
		write(ans);
		puts("");
	}
	return 0;
}
```

（可以枚举 $r$ 点，用单调队列保存 $l$ 点，可以把时间复杂度优化到 $O(n)$，但懒了qwq）

---

## 作者：_XHY20180718_ (赞：6)

其实这题完全没必要限制 $k$ 的范围，但这样这道题可能就升蓝了。

前置知识：线段树维护最大子段和：[小白逛公园](https://www.luogu.com.cn/problem/P4513)，当然，你也可以直接看我代码中的注释。

## 题意简述：

给你一个序列，让 $k$ 个不同位置加上 $x$，其他位置减去 $x$，然后求可能的最大子段和，最大子段和**可以为空**。

## 思路：

提供一种线段树单点修改区间查询维护最大子段和的方法：

首先，我们~~大胆猜测~~一个结论：$x>0$ 时，$k$ 个不同位置放在一起（连续）一定是最优的。

我们要求的是最大子段和，因此这个结论应该很容易想到，也比较容易证明。

由于我们要求的最大子段和是连续的，假设 $len$ 为最大子段和长度。

那么当 $k\leq len$ 时，我们肯定会贪心的把 $k$ 个位置都放进这个最大子段和的区间内，无论如何排列组合，一定是最优的。

而当 $k>len$ 时，我们肯定会贪心的让最大子段和这个区间内的数都加上 $x$，那么连续不断的 $k$ 有利于我们让最大子段和的整个区间都加上 $x$。

然后想必大神们都可以一眼秒了：

首先，暴力单点修改，让前 $k$ 个位置都加上 $x$，其他位置减去 $x$，随后用线段树求一遍最大子段和。

从左到右暴力枚举每个长度为 $k$ 的区间，然后单点修改上一个被去掉的位置，使其减去 $2x$，单点修改下一个加进来的位置，使其加上 $2x$，每次修改完后均用线段树求一遍最大子段和。

复杂度：$O(n\log n)$。

据说巨佬们都是 $O(n)$ 的单调队列做法，欢迎来 D 爆我。

警示后人：$x<0$ 时，一定要让其反过来，此时，若按照我们上面的证明过程，可以发现如果把连续的 $k$ 个位置全都加上一个负数，原来的最大子段和可能会吸收到，反而会让最大子段和变小。我们可以让其他位置减去 $-x$，这一段区间加上 $-x$，可以轻松把问题转化。笔者模拟赛由于没有判断 $x<0$ 加上恶心的 Subtask 完美保龄。

自认为码风良好的代码，看不懂/有问题可以直接在下面评论：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,inf=2e9+9;
int n,k,x,a[N],ans;
int L,R,K,I,sz,T;
struct tree{
	int l,r,len;
	int ls,rs;
	int w,lw,rw,sum;
}tr[N<<1];
inline void chg(int id,int x)
{tr[id].w+=x,tr[id].lw=tr[id].rw=tr[id].sum=tr[id].w;}
inline tree pushup(tree now,tree lt,tree rt){
	now.sum=lt.sum+rt.sum;//当前区间
	now.lw=max(lt.lw,lt.sum+rt.lw);//当前区间从左端点开始的最大子段和可能就是左区间的(从左端点开始的最大子段和)也可能是整个做区间加上右区间的(从左端点开始的最大子段和)。
	now.rw=max(rt.rw,rt.sum+lt.rw);//当前区间从右端点开始的最大子段和可能就是右区间的(从右端点开始的最大子段和)也可能是整个做区间加上左区间的(从右端点开始的最大子段和)。
	now.w=max(max(lt.w,rt.w),lt.rw+rt.lw);//当前区间的最大子段和可能是左区间或有区间的最大子段和，也可能是左区间从右端点开始的最大子段和加上右区间从左端点开始的最大子段和。
	return now;//返回新的线段树节点
}
inline void build(int l,int r,int id){
	tr[id]=(tree){l,r,r-l+1,0};
	if(l==r){tr[id].w=0,chg(id,a[l]);return;}
	int ls=++sz,rs=++sz,mid=l+(r-l>>1);
	build(l,mid,tr[id].ls=ls);
	build(mid+1,r,tr[id].rs=rs);
	tr[id]=pushup(tr[id],tr[ls],tr[rs]);
}
inline void upd(int id){
	int l=tr[id].l,r=tr[id].r;
	if(l>I||r<I)return;
	if(l==r){chg(id,K);return;}
	int ls=tr[id].ls,rs=tr[id].rs;
	upd(ls),upd(rs);
	tr[id]=pushup(tr[id],tr[ls],tr[rs]);
}
inline tree qry(int id){
	int l=tr[id].l,r=tr[id].r;
	if(L<=l&&r<=R)return tr[id];
	int ls=tr[id].ls,rs=tr[id].rs,mid=l+(r-l>>1);
	if(L<=mid&&r>mid)return pushup(tr[id],qry(ls),qry(rs));//可以减少码量
	if(L<=mid)return qry(ls);if(r>mid)return qry(rs);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T;while(T--){sz=ans=0;//初始化（动态开点线段树节点个数与答案）
		cin>>n>>k>>x;if(x<0)k=n-k,x=-x;//注意转化，保证x>0
		for(int i=1; i<=n; ++i)
			cin>>a[i];build(1,n,++sz);
		for(int i=1; i<=n; ++i)
		{I=i;if(i>k)K=-x;else K=x;upd(1);}//初始化，让最左边长度为k的区间加上x
		L=1,R=n,ans=max(ans,qry(1).w);//纪录一遍答案
		for(int i=2; i<=n-k+1; ++i){
			I=i-1,K=-2*x,upd(1);//把上一次的左端点去掉，由+x变为-x
			I=i+k-1,K=2*x,upd(1);//加上这一次的右端点，由-x变为+x
			L=1,R=n,ans=max(ans,qry(1).w);//纪录一遍新区间的答案
		}cout<<ans<<'\n';//输出
	}return 0;
}

```

---

## 作者：Lu_xZ (赞：1)

**CF1796D		\*2000**

法一：$O(nk)$

设 $f_{i, j}$ 表示以 $i$ 结尾，已经加了 $j$ 个位置的最大子段和，则 $f_{i, j} = \begin{cases}a_i - x + \max(f_{i - 1, j}, 0)\\a_i + x + \max(f_{i - 1, j - 1}, 0) \end{cases}$。

合法方案为所有 $f_{i, j}$ 满足 $i \le n - (k - j)$，因为没填的 $k - j$ 个位置可以在 $i$ 后面随便放。

```cpp
void solve() {
	int n, k, x; cin >> n >> k >> x;
	vector f(n + 1, vector<ll>(k + 1, -1e18));
	vector a(n + 1, 0);
	ll ans = 0;
	for(int i = 1; i <= n; ++ i) cin >> a[i];
	f[0][0] = 0;
	for(int i = 1; i <= n; ++ i) { 
		for(int j = 0; j <= min(i, k); ++ j) {
			if(f[i - 1][j] != -1e18) {
				f[i][j] = a[i] - x + max(0ll, f[i - 1][j]);
			}
			if(j && f[i - 1][j - 1] != -1e18) {
				f[i][j] = max(f[i][j], a[i] + x + max(0ll, f[i - 1][j - 1]));
			}
			if(i <= n - k + j) ans = max(ans, f[i][j]);
		}
	}
	cout << ans << '\n';
}
```

法二：$O(n)$

如果 $x < 0$，令 $k \to n - k,\ \ x \to -x$。

1. 子数组长度 $> k$，不妨将所有 $a_i$ 先减去 $x$，最后再加 $2kx$，设 $s_i = \sum_{j = 1}^i a_j - x$，则最大值为 $2kx + s_i - \min(s_j), \quad j < i -  k$。

2. 子数组长度 $\le k$，数组的每个位置都能加 $x$，设 $s_i = \sum_{j = 1}^i a_j + x$，则最大值为 $s_i - \min(s_j), \quad i -  k\le j < i$，单调队列维护。

```cpp
constexpr int N = 2e5 + 5;

int n, k, a[N], q[N], hh, tt;
ll s[N], x;

void solve() {
	cin >> n >> k >> x;
	if(x < 0) {
		k = n - k;
		x = -x;
	}
	for(int i = 1; i <= n; ++ i) cin >> a[i];
	ll ans = 0;
	
	ll mi = 0;
	for(int i = 1; i <= n; ++ i) {
		s[i] = s[i - 1] + a[i] - x;
		if(i > k) {
			ans = max(ans, s[i] - mi + 2 * k * x);
			mi = min(mi, s[i - k]);
		}
	}
	
	q[hh = tt = 0] = 0; 
	for(int i = 1; i <= n; ++ i) {
		while(hh <= tt && q[hh] < i - k) ++ hh;
		s[i] = s[i - 1] + a[i] + x;
		if(hh <= tt) {
			ans = max(ans, s[i] - s[q[hh]]);
		}
		while(hh <= tt && s[i] <= s[q[tt]]) -- tt;
		q[++ tt] = i;
	}
	cout << ans << '\n';
}
```

---

## 作者：KingPowers (赞：1)

[题目链接](https://codeforces.com/problemset/problem/1796/D)

下面令 $b_i=a_{i}-x$，$b_i'=a_i+x$ 。

因为 $k\le20$，因此考虑一个复杂度与 $k$ 相关的做法。

不妨 dp：设 $f_{i,j,0/1}$ 表示考虑了前 $i$ 个数，对 $j$ 个数加上了 $x$，第 $i$ 个数不加/加，且强制选择第 $i$ 个数的情况下的最大子段和。

转移是平凡的，就类似于正常的求最大子段和：
$$
\begin{aligned}
f_{i,j,0}&=\max(b_i,f_{i-1,j,0}+b_i,f_{i-1,j,1}+b_i) \\
f_{i,j,1}&=\max(b_i',f_{i-1,j-1,0}+b_i',f_{i-1,j-1,1}+b_i')
\end{aligned}
$$
对所有满足 $n-i\ge k-j$ 的 $f_{i,j,0/1}$ 统计答案即可，实现时注意一些边界条件。

时间复杂度 $O(nk)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=(a);i<=(b);i++)
#define Rof(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int N=5e5+5;
int n,k,x,a[N],f[N][22][2];
void Main(){
    cin>>n>>k>>x;
    For(i,1,n) cin>>a[i];
    int ans=0;
    For(i,1,n) For(j,0,min(i,k)){
        int a1=a[i]-x,a2=a[i]+x;
        if(i!=j) f[i][j][0]=max({a1,f[i-1][j][0]+a1,f[i-1][j][1]+a1});
        if(j) f[i][j][1]=max({a2,f[i-1][j-1][0]+a2,f[i-1][j-1][1]+a2});
        if(n-i>=k-j) ans=max({ans,f[i][j][0],f[i][j][1]});
    }
    cout<<ans<<'\n';
    For(i,1,n) For(j,0,k) f[i][j][0]=f[i][j][1]=0;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T=1;cin>>T;
    while(T--) Main();
    return 0;
}
```

---

## 作者：jasonliujiahua (赞：1)

# CF1796D

[题目传送门](https://www.luogu.com.cn/problem/CF1796D)
## 题意简述：
你得到了一个序列 $a_1,a_2,\cdots,a_n$，由 $n$ 个整数组成。并且你还得到了两个整数 $k,x$。

你需要执行**一次**操作：选择**恰好 $k$ 个不同**的位置加上 $x$，其余位置减去 $x$。

比如说：如果 $a=[2,-1,2,3],k=1,x=2$，然后我们选择第一个位置，操作之后的 $a=[4,-3,0,1]$。

定义 $f(a)$ 为 $a$ 序列的子串的最大可能和。$a$ 的子串是 $a$ 的一部分，即序列 $a_i,a_{i+1},\cdots ,a_j$ 对于某个 $1\le i\le j\le n$。同时，空数组也应该被考虑，它的和为 $0$。

让 $a'$ 为 $a$ 操作后的序列，输出 $f(a')$ 的最大可能值。

$1\le t\le 10^4;\;1\le n,\sum n\le 2\cdot 10^5;\;0\le k\le \min(20,n);\;-10^9\le a_i,x\le 10^9$
## 题目分析：
### Step 1：题目转化
可以将题目操作进行如下转化：**先将所有 $a_i$ 减去 $x$，再选恰好 $k$ 个位置加上 $2x$**。
### Step 2：DP
稍稍转化后，就可以进行 dp 了，设 $dp_{i,j}$ 表示前 $i$ 个数中选 $j$ 个进行操作后，以 $i$ 为结尾的最长子串和。有转移方程：
$$dp_{i,j}=\max(dp_{i-1,j}+a_i,\ dp_{i-1,j-1}+a_i+2x,\ 0)$$
注意一下细节：如果当前 $i$ 之前选的 $j$ 个数加上 $i$ 之后所有的数也无法满足题目要求的范围，则不应统计入答案。
## 参考代码：

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
int t,n,k,x,ans,a[maxn],dp[maxn][30];
void init()
{
    cin>>n>>k>>x;
    for(int i=1;i<=n;i++) cin>>a[i],a[i]-=x;
}
void DP()
{
    ans=0;
    for(int i=0;i<=n;i++)
        for(int j=i+1;j<=k;j++)
            dp[i][j]=-1e18;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=min(i,k);j++)
        {
            if(j) dp[i][j]=max(dp[i-1][j]+a[i],
            max(dp[i-1][j-1]+a[i]+2*x,0ll));
            else dp[i][j]=max(0ll,dp[i-1][j]+a[i]);
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=0;j<=min(i,k);j++)
            if(k-j<=n-i) ans=max(ans,dp[i][j]);
    cout<<ans<<endl;
}
signed main()
{
    cin>>t;
    while(t--)
    {
        init();
        DP();
    }
    return 0;
}
```

---

## 作者：masonpop (赞：1)

有点难度的小 dp。

首先，为了避免大量修改，我们先将所有数减去 $x$。这样题目变为：选出 $k$ 个位置加上 $2x$，最大化其最大子段和。

只需要把求最大子段和的 dp 状态略加修改就可以了。设 $f_{i,j}$ 表示以 $i$ 结尾，并且在前 $i$ 个数中已经选择 $j$ 个数操作的最大子段和。那么，仍然分成两类转移：

$(1)$ 修改最后一个位置：需要满足 $j>0$。此时，可以转移到 $f_{i-1,j-1}+a_i+2x$ 和 $a_i+2x$。

$(2)$ 不修改最后一个位置：需要满足前 $i-1$ 个位置足以修改 $j$ 次，即 $j\le i-1$。此时转移到 $a_i$ 和 $f_{i-1,j}+a_i$。

时间复杂度 $O(nk)$。[代码](https://codeforces.com/contest/1796/submission/213487515)。

---

## 作者：SlyCharlotte (赞：1)

[更好的阅读体验？](https://zhuanlan.zhihu.com/p/610522558)

## 题意描述

给你一个长度为 $n$ 的序列，执行一次以下操作：

选 $k$ 个数 $+x$，其余未选择的数 $-x$。

求操作后的最大子段和。

## 简要分析

观察到要求最大子段和，但发现需要对数组进行操作，于是考虑如何改编最大字段和。

这里我们改变使用分治（线段树）的方法求解。

关于如何使用分治（线段树）的方法求解最大子段和这里不再赘述。

观察到在建树时递归到最底端，也就是 $l = r$ 时，此时维护的最大字段和、以左端点为首元素的最大子段和，以右端点为尾元素的最大子段和均等于 $a_l$ 即 $a_r$。

我们可以在这里分类讨论，如果 $k = 0$ 那么只需 $a_l \leftarrow a_l-x$ 即 $a_r \leftarrow a_r-x$ 即可。

若 $k \not= 0$ 要么将 $a_l \leftarrow a_l + x$ 即 $a_r \leftarrow a_r + x$，要么将 $a_l \leftarrow a_l - x$ 即 $a_r \leftarrow a_r -x$。

我们只需讲这两种情况均与另一节点合并至父节点中即可。

合并时仅需枚举配对情况取最大值即可。

事实上，这里看似有 $2^x$ 种合并方式，然而我们只需其中的 $k$ 种。

因为有和多种情况所算出来的答案是相同的。

又因为我们不需要知道怎么选，只需知道最大子段和的值。

所以可以将 $2^x$ 种合并方式简化为 $k$ 种合并方式。

又因为此题仅需一次建树一次查询所以可以省去许多冗余的函数，代码十分简洁。

时间复杂度为 $O(nk)$。

## 代码实现

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

typedef long long ll;
const ll maxn = 2e5 + 7;
const ll INF = 1e18 + 7, MOD = 998244353;

inline ll read() {
    char cCc;
    ll xXx = 0, wWw = 1;
    while (cCc < '0' || cCc > '9')
        (cCc == '-') && (wWw = -wWw), cCc = getchar();
    while (cCc >= '0' && cCc <= '9')
        xXx = (xXx << 1) + (xXx << 3) + (cCc ^ '0'), cCc = getchar();
    xXx *= wWw;
    return xXx;
}

inline void write(ll xXx) {
    if (xXx < 0)
        putchar('-'), xXx = -xXx;
    if (xXx > 9)
        write(xXx / 10);
    putchar(xXx % 10 + '0');
}

struct node {
    ll sum, lq, rq, qs;

    node() {
        sum = -INF, lq = -INF, rq = -INF, qs = -INF;
    }

    node(ll sum, ll lq, ll rq, ll qs) : sum(sum), lq(lq), rq(rq), qs(qs) {}
};

ll n, k, x, a[maxn];

vector<node> solve(ll l, ll r) {
    if (l == r) {
        ll s1 = max(0ll, a[r] + x);
        ll s2 = max(0ll, a[r] - x);
        if (k == 0) return {node(a[r] - x, s2, s2, s2)};
        return {node(a[r] - x, s2, s2, s2), node(a[r] + x, s1, s1, s1)};
    }
    ll mid = (l + r) / 2;
    auto vl = solve(l, mid), vr = solve(mid + 1, r);
    ll len = min(k, r - l + 1) + 1;
    vector<node> ans(len);
    for (ll i = 0; i < vl.size(); i++) {
        for (ll j = 0; j < vr.size() && i + j < len; j++) {
            auto &l = vl[i], &r = vr[j], &u = ans[i + j];
            u.sum = max(u.sum, l.sum + r.sum);
            u.lq = max(u.lq, l.lq);
            u.lq = max(u.lq, l.sum + r.lq);
            u.rq = max(u.rq, r.rq);
            u.rq = max(u.rq, l.rq + r.sum);
            u.qs = max(u.qs, l.qs);
            u.qs = max(u.qs, r.qs);
            u.qs = max(u.qs, l.rq + r.lq);
        }
    }
    return ans;
};

signed main() {
    ll T = read();
    while (T--) {
        n = read(), k = read(), x = read();
        for (ll i = 1; i <= n; i++) a[i] = read();
        cout << solve(1, n)[k].qs << '\n';
    }
}
```


---

## 作者：Priestess_SLG (赞：0)

简单题，考虑简单 dp。发现 $k$ 很小，因此设 $f_{i,j,0/1}$ 表示前 $i$ 个元素，修改了 $j$ 个位置，当前位置不选 / 必选，最大子段和的值。转移类似于普通的 1-D 最大子段和。具体见代码。

```cpp
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define eb emplace_back
#define int long long
using namespace std;
const int N = 200100;
int f[N][22][2], a[N];
signed main() {
    int T;
    cin >> T;
    while (T--) {
        int n, k, x;
        cin >> n >> k >> x;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            a[i] -= x;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= min(i, k); ++j) {
                f[i][j][0] = f[i][j][1] = 0;
            }
        }
        x <<= 1;
        int mx = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= min(i, k); ++j) {
                if (i != j) {
                    f[i][j][0] = max({a[i], f[i - 1][j][0] + a[i], f[i - 1][j][1] + a[i]});
                }
                if (j) {
                    f[i][j][1] = max({a[i] + x, f[i - 1][j - 1][0] + a[i] + x, f[i - 1][j - 1][1] + a[i] + x});
                }
                if (k - j <= n - i) {
                    mx = max({mx, f[i][j][0], f[i][j][1]});
                }
            }
        }
        cout << mx << '\n';
    }
    return 0;
}

/*



*/
```

---

## 作者：Xy_top (赞：0)

一眼题，但这个 $k$ 迷惑了我很久。

由于我初始的思路没考虑 $x<0$，所以我们先默认 $x>0$。

考虑任意一个是最优答案的最大子段和，如果它的长度 $<k$ 那么它的每个元素一定都加上了 $x$，如果它的长度 $>k$，那么它的 $k$ 个元素一定加上了 $x$，剩余的一定减去了 $x$。

小于 $k$ 怎么搞都行，而如果长度大于 $k$，我们可以把 $k$ 个加 $x$ 的移到这个子段的最前面加这样显然不会有影响。

然后枚举这个答案的左端点之后，将左端点右边 $k$ 个都加上 $x$，剩余的都减去 $x$。

该过程可以用线段树维护，时间复杂度为 $O(n\log n)$，但是样例最后一个没过，还以为假了。随便猜了个 $x \to -x$，$k\to n-k$ 便过了样例然后一遍过了。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, k, x, ans = 0;
int c[200005];
struct S {int lmx, rmx, sum, mx;}a[800005];
void merge (S &a, S b, S c) {
	a.lmx = max (b.lmx, b.sum + c.lmx);
	a.rmx = max (c.rmx, c.sum + b.rmx);
	a.mx = max (max (b.mx, c.mx), b.rmx + c.lmx);
	a.sum = b.sum + c.sum;
}
void build (int l, int r, int k) {
	if (l == r) {
		a[k].lmx = a[k].rmx = a[k].sum = a[k].mx = c[l];
		return;
	}
	int mid = l + r >> 1;
	build (l, mid, k << 1);
	build (mid + 1, r, k << 1 | 1);
	merge (a[k], a[k << 1], a[k << 1 | 1]);
}
void update (int l, int r, int k, int x, int y) {
	if (l == r) {
		a[k].lmx += y;
		a[k].rmx += y;
		a[k].sum += y;
		a[k].mx += y;
		return;
	}
	int mid = l + r >> 1;
	if (x <= mid) update (l, mid, k << 1, x, y);
	else update (mid + 1, r, k << 1 | 1, x, y);
	merge (a[k], a[k << 1], a[k << 1 | 1]);
}
void solve () {
	cin >> n >> k >> x;
	if (x < 0) {
		x = -x;
		k = n - k;
	}
	ans = 0;
	For (i, 1, n) {
		cin >> c[i];
		if (i <= k) c[i] += x;
		else c[i] -= x;
	}
	build (1, n, 1);
	For (i, 1, n - k + 1) {
		if (i - 1) {
			update (1, n, 1, i - 1, -2 * x);
			update (1, n, 1, i + k - 1, 2 * x);
		}
		ans = max (ans, a[1].mx);
	}
	cout << ans << '\n';
}
signed main () {
	int _ = 1;
	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}

```


---

## 作者：happybob (赞：0)

提供一个复杂度与 $k$ 无关的算法。

容易发现的是，当 $x<0$ 时，我们令 $x \leftarrow -x$，
$k \leftarrow n-k$，与原题等价。

所以下文我们默认 $x \geq 0$。

我们先考虑最终选择所有长度 $<k$ 的子段，那么这个子段每一个数都可以加上 $x$，且应该加上 $x$，因为 $x \geq 0$。

所以这一部分我们相当于要求 $\max \limits_{l\leq r,r-l<k} 
[\sum \limits_{i=l}^r (a_i+x)]$。

容易发现我们只需要枚举所有长度 $=k-1$ 的区间，求一个最大子段和取 $\max$ 即可，可以线段树维护。

接着第二部分，长度 $\geq k$，容易发现，对于一个区间，若长度 $\geq k$，那么具体选哪些点 $+x$ 是没有意义的，只需要关心 $+x$ 的数有 $k$ 个。

于是我们枚举所有长度为 $k$ 的区间，看成这个区间里每个数都加 $x$，哪么两边每个数 $i$ 的贡献是 $a_i-x$，只需要处理从这个区间左端点能往前走最多的和右端点往右走最多的，容易发现可以线性处理。

所以总体复杂度 $O(n \log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 2e5 + 5;
int t, n, k, x;

int a[N];

class SegmentTree
{
public:
	struct Node
	{
		int l, r;
		int sum, lmax, rmax, tmax;
		Node()
		{
			l = r = sum = 0;
			lmax = rmax = tmax = -1e11;
		}
		friend Node operator+(const Node& x, const Node& y)
		{
			Node p;
			p.sum = x.sum + y.sum;
			p.lmax = max(x.lmax, x.sum + y.lmax);
			p.rmax = max(y.rmax, y.sum + x.rmax);
			p.tmax = max({ x.tmax, y.tmax, x.rmax + y.lmax });
			return p;
		}
	};
	
	Node tree[N << 2];
	
	void CLEAR(int n)
	{
		for (int i = 0; i <= 4 * n; i++)
		{
			tree[i].l = tree[i].r = 0;
			tree[i].sum = 0;
			tree[i].lmax = tree[i].rmax = tree[i].tmax = -1e11;
		}
	}
	
	inline void push_up(int u)
	{
		int tl = tree[u].l, tr = tree[u].r;
		tree[u] = tree[u << 1] + tree[u << 1 | 1];
		tree[u].l = tl, tree[u].r = tr;
	}
	
	inline void build(int u, int l, int r, int *a)
	{
		tree[u].l = l, tree[u].r = r;
		if (l == r)
		{
			tree[u].lmax = tree[u].rmax = tree[u].sum = tree[u].tmax = a[r];
		}
		else
		{
			int mid = (l + r) >> 1;
			build(u << 1, l, mid, a);
			build(u << 1 | 1, mid + 1, r, a);
			push_up(u);
		}
	}
	
	inline void modify(int u, int x, int v)
	{
		if (tree[u].l == x && tree[u].r == x)
		{
			tree[u].lmax = tree[u].rmax = tree[u].sum = tree[u].tmax = v;
		}
		else
		{
			int mid = (tree[u].l + tree[u].r) >> 1;
			if (x <= mid) modify(u << 1, x, v);
			else modify(u << 1 | 1, x, v);
			push_up(u);
		}
	}
	
	Node query(int u, int l, int r)
	{
		if (tree[u].l >= l && tree[u].r <= r) return tree[u];
		int mid = (tree[u].l + tree[u].r) >> 1;
		Node x, y;
		if (l <= mid) x = query(u << 1, l, r);
		if (r > mid) y = query(u << 1 | 1, l, r);
		return x + y;
	}
}sgt;

signed main()
{
	scanf("%lld", &t);
	while (t--)
	{
		scanf("%lld%lld%lld", &n, &k, &x);
		sgt.CLEAR(n);
		if (x < 0)
		{
			x = -x;
			k = n - k;
		}
		int ans = -1e18;
		for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		sgt.build(1, 1, n, a);
		int i = k - 1;
		if (i <= 0) goto E;
		for (int j = 1; j <= i; j++) 
		{
			sgt.modify(1, j, a[j] + x);
		}
		for (int j = 1; j + i - 1 <= n; j++)
		{
			ans = max(ans, sgt.query(1, j, j + i - 1).tmax);
			sgt.modify(1, j, a[j]);
			if (j + i <= n) sgt.modify(1, j + i, a[j + i] + x);
		}
		E:
		long long f1 = 0LL, f2 = 0LL;
		long long sum = 0LL, psum = 0LL;
		for (int i = k + 1; i <= n; i++)
		{
			sum += (a[i] - x);
			f2 = max(f2, sum);
		}
		for (int i = 1; i <= k; i++)
		{
			psum += a[i];
		}
		for (int i = 1; i + k - 1 <= n; i++)
		{
			ans = max(ans, psum + k * x + f1 + f2);
			//printf("!: %lld %lld %lld\n", i, f1, f2);
			f1 += (a[i] - x);
			f1 = max(f1, 0LL);
			if (f2 > 0) f2 -= (a[i + k] - x);
			f2 = max(f2, 0LL);
			psum -= a[i];
			psum += a[i + k];
		}	
		ans = max(ans, 0LL);
		printf("%lld\n", ans);
 	}
	return 0;
}
```


---

