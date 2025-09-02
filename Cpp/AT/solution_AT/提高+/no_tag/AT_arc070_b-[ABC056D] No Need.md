# [ABC056D] No Need

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc056/tasks/arc070_b

シカのAtCoDeerくんは正整数が書かれたカードを $ N $ 枚持っています。$ i(1≦i≦N) $ 枚目に書かれている数は $ a_i $ です。 AtCoDeerくんは大きい数が好きなので、カードに書かれた数の総和が $ K $ 以上になるようなカードの部分集合を*よい集合*と呼びます。

そして、各カード $ i $ に対して、そのカードが*不必要*かどうかを次のように判定します。

- 「カード $ i $ を含む任意の*よい集合*に対して、その集合からカード $ i $ を除いたものも*よい集合*」 ならカード $ i $ は*不必要*
- それ以外の場合は、*不必要*でない

不必要なカードの枚数を求めてください。ただし、それぞれの判定は独立に行われ、不必要だからと言ってカードが途中で捨てられたりすることはありません。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1≦N≦5000 $
- $ 1≦K≦5000 $
- $ 1≦a_i≦10^9\ (1≦i≦N) $

### 部分点

- $ N,K≦400 $ を満たすデータセットに正解した場合は、部分点として $ 300 $ 点が与えられる。

### Sample Explanation 1

よい集合は {$ 2,3 $} と {$ 1,2,3 $} の二つです。 カード $ 1 $ を含むよい集合は {$ 1,2,3 $} しかなく、これから $ 1 $ を取り除いた {$ 2,3 $} もよい集合なので、カード $ 1 $ は不必要です。 また、よい集合である {$ 2,3 $} から $ 2 $ を取り除いた集合 {$ 3 $} はよい集合ではないため、カード $ 2 $ は不必要ではありません。 カード $ 3 $ も同様に不必要ではないため、答えは $ 1 $ です。

### Sample Explanation 2

この場合よい集合は存在しないため、全てのカードは不必要となります。

## 样例 #1

### 输入

```
3 6
1 4 3```

### 输出

```
1```

## 样例 #2

### 输入

```
5 400
3 1 4 1 5```

### 输出

```
5```

## 样例 #3

### 输入

```
6 20
10 4 3 10 25 2```

### 输出

```
3```

# 题解

## 作者：Achtoria (赞：16)

这里介绍几种做法。

### 解法一

首先可以转化一下题意，$\forall i$ 如果 $i$ 不是可有可无的当且仅当不用 $i$ 能拼出 $[K - a_i, K)$ 中的数。

基于观察可以发现，对于 $\forall i$ 如果 $i$ 不是可有可无的，那么 $\forall j, a_j \ge a_i$ 都不是可有可无的，证明如下：

> 取出使得对于 $i$ 能拼出 $[K - a_i, K)$ 中一个数的集合 $S$，分以下两种情况讨论：
> 
> * > 若 $j \in S$，考虑用 $a_i$ 替换 $a_j$ 使得对于 $j$ 合法。
> 
> 则可知 $K - a_i \le |S| \le K \Rightarrow K \le |S| + a_i \le K - a_i$
> 
> 于是有 $K - a_j \le |S| + a_i - a_j \le K + a_i - a_j \le K$ 因此替换是可行的。
> 
> * > 若 $j \notin S$ 直接使用 $S$ 即可满足 $j$ 的要求。

因此我们先按照 $a_i$ 从小到大排序，可替换的必然是一段前缀，直接二分加背包判断即可，复杂度 $O(nk \log n)$。

### 解法二

一个直接的想法在于求出不使用 $i$ 能拼成的数字有哪些。

暴力的做法就是 $\forall i$ 枚举 $j \ne i$ 进行暴力 $dp$。

但是你会发现有对于一些 $i$ 有很多 $j$ 都是能枚举的，换而言之每一对点对 $(i, j)(i < j)$ 都会在 $i, j$ 上分别用对方 $dp$ 一次。

对于这种点对对答案的贡献问题，经常可以考虑使用 $\rm CDQ$ 分治解决。

那么我们在分治 $[l, r]$ 这个区间时可以发现，$[l, mid]$ 内的所有数会对 $[mid + 1, r]$ 内所有数的 $dp$ 数组造成贡献。

因此我们直接考虑枚举左区间的每个数 $i$ 让其在右区间恰好 $dp$ 一次，对于右区间同理。

那么分治下去的时候就要同时将整个区间的 $dp$ 数组传递下去，不难发现这样的复杂度实际上只枚举了 $n \log n$ 个点，因此复杂度是 $O(nk \log n)$ 的。

### 解法三

注意到我们要求的实质上是去除掉 $i$ 以后的 $dp$ 数组，不难让我们想起了 [消失之物](https://www.luogu.com.cn/problem/P4141) 这题的退背包做法。

但是本题的 $dp$ 是判定性的，不存在可加性，怎么办呢？

不难发现只需要改写 $dp$ 状态让其满足可加性即可，即我们将存储的值由是否可行变为方案数。

那么一个数不能被拼出来当且仅当方案数为 $0$。

于是先 $dp$ 出总方案数，然后从左至右做退背包即可。

由于方案数过大，需要取模，复杂度 $O(nk)$。

### 解法四

考虑另一个暴力合并 $dp$ 数组的做法，先记录 $pre, suf$ 两个前缀/后缀 $dp$ 数组。

$\forall i$，在 $i$ 处暴力合并 $pre_{i - 1}, suf_{i + 1}$，复杂度 $O(nk ^ 2)$。

但实际上我们并不关心具体的 $dp$ 数组，我们只关心 $[K - a_i, K)$ 之间有没有一个数能被拼出来。

为了尽量满足存在这样一个数，我们这样来看待这个问题：在满足和小于 $K$ 的情况下最大化总和。

因此在合并的时候我们从小到大枚举 $pre_{i - 1}$ 中一个可行的数 $j$，找到 $suf_{i + 1}$ 中满足 $j + k < K$ 的最大的 $k$。

不难发现在 $j$ 从小到大枚举的过程中，$k$ 单调不升，因此这样寻找的复杂度就变为了 $O(nk)$。


---

## 作者：Lynkcat (赞：9)

我的做法是 $O(nk)$ 的，一个简单的回退背包。

可以发现一个结论，若把物品 $i$ 去掉后存在和在 $k-a_i\sim k-1$ 的方案那么物品 $i$ 就不能成为可有可无的物品。

这样子容易想到 $O(n^2k)$ 的暴力可行性背包，时间复杂度爆炸。

考虑把上面的可行性背包换成方案数背包。

$f_i$ 表示和为 $i$ 的方案数，先做一遍普通的 $01$ 背包。然后考虑去掉物品 $i$ 相当于将这个转移回退回去，也就是 $f_j=f_j-f_{j-a_i}$。然后我们再在 $k-a_i\sim k-1$ 这段区间里查找是否有 $f_j>0$ 的值。

但是方案数很大，我们可以考虑模一个大质数，这样子一个 $f_k$ 实际不为 $0$ 但取模为 $0$ 的概率很小，所以完全能保证正确性。

```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
#define ll long long
#define F(i,a,b) for (int i=(a);i<=(b);i++)
#define R(i,a,b) for (int i=(a);i<(b);i++)
#define D(i,a,b) for (int i=(a);i>=(b);i--)
#define go(i,x) for (int i=head[x];i;i=e[i].nx)
#define IOS ios::sync_with_stdio(false)
#define mp make_pair
#define pb push_back
#define pa pair < int,int >
#define fi first
#define se second
#define re register
#define be begin()
#define en end()
#define sqr(x) ((x)*(x))
#define ret return puts("-1"),0;
#define put putchar('\n')
#define inf 1000000005
#define mod 1000000007
#define int ll
#define N 50005
using namespace std;
inline char gc(){static char buf[1000000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int n,m,f[N],a[N],ans;
signed main()
{
	n=read(),m=read();
	f[0]=1;
	for (int i=1;i<=n;i++)
	{
		a[i]=read();
		for (int j=m*2;j>=a[i];j--)
			f[j]=(f[j]+f[j-a[i]])%mod;
	}
	for (int i=1;i<=n;i++)
	{
		int x=0;
		if (a[i]>=m) continue;
		else
		{
			for (int j=a[i];j<=m*2;j++)
				f[j]=(f[j]-f[j-a[i]]+mod)%mod;
			for (int j=m-a[i];j<m;j++)
				if (f[j]) x=1;
			if (!x) ans++;
			for (int j=m*2;j>=a[i];j--)
				f[j]=(f[j]+f[j-a[i]]+mod)%mod;
		}
	}
	writeln(ans);
}
/*

*/
```


---

## 作者：wind_seeker (赞：8)

对于题目，先考虑性质。

先是一个朴素的性质：我们作背包，对于一个数，如果有一个方案，满足插入这个数前 $< k$，插入之后 $\ge k$，那么这个数不是可有可无。

然后就可以推出一个性质，如果我们把它降序排序以后再插入 ,可有可无的数字变成了一段后缀，下面是证明。

如果 $a_i$ 满足朴素的性质，假设用前 $i-1$ 个数拼成了 $num$ 使得 $num<k$ 并且 $a_i+num\ge k$，那么考虑 $j<i$：

- 如果 $a_j$ 被用来凑成 $num$：满足 $num+a_i-a_j< k\le num+a_i$。
- 如果 $a_j$ 不被用来凑成 $num$：显然 $a_j+num\ge k$，此时它也不是可有可无。


然后我们可以证明最后一个不是可有可无的数字 $a_i$ 一定可以用它之前的数拼成 $num$。假设我们拼成了 $num$ 满足 $num<k\le num+a_i$（注意这个 $num$ 可以使用除了 $a_i$ 剩下的所有数），那么找到一个 $a_j$ 满足 $j>i$ 并且被用来凑成 $num$：

- 如果 $num+a_i-a_j\ge k$，那么我们可以在 $num$ 中删去 $a_j$。
- 否则 $num'=num+a_i-a_j$，那么 $num'<k\le num'+a_j$，$a_j$ 并不是可有可无，与 $i$ 是最后一个不是可有可无矛盾。

所以只要从前往后往背包里加数即可。

时间复杂度：$\mathcal O(nk)$。使用 `bitset` 可以优化到 $\mathcal O(nk/w)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5010;

int n,k,a[N],dp[N],ans,al;

int read(){
	int res=0,f=1;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) res=(res<<3)+(res<<1)+(c^48);
	return res*f;
}

bool cmp(int x,int y){return x>y;}

int main(){
	haha,wozhendeshijuedingcongming,xinhaibukuishiwolaopo
	n=read(),k=read();
	for(int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+n+1,cmp);
	dp[0]=1;
	for(int i=1;i<=n;i++){
		if(a[i]>=k) {ans=i;continue;}
		for(int j=k-1;j>=0;j--){
			if(dp[j]&&j+a[i]>=k) ans=i;
			else if(dp[j]) dp[j+a[i]]=1;
		}
	}
	printf("%d\n",n-ans);
	return 0;
}
```


---

## 作者：Nemlit (赞：7)

~~这种题都能撞到我也是醉了（貌似楼上有位写了我这个做法）~~

考虑暴力，一个数不会算入答案，当且仅当它比$m$大（肯定可以减少它本身这个集合），或者是不考虑它，有其他的值可以和他凑成$\ge m$的数

于是我们可以背包，对于每一个数，把他忽略做一遍$01$背包，然后检查$[m - a[i], m)$是否可以凑成即可

发现任意两个点的背包有很多重复信息，于是我们考虑分治。

分治中每一个节点存储的是**不**包括这个节点所代表的点的$dp$数组，然后每一次分治的时候$[l, mid]$对$[mid + 1, r]$这个节点的贡献加进去，$[mid + 1, r]$对$[l, mid]$这个结点的贡献加进去即可（不理解可以参考代码）

这样复杂度是$O(NMlogN)$的，你可以使用$bitset$优化，但是本题数据叫水，不需要$bitset$也是可以的
### $\rm Code:$
```cpp
/* This code is written by Nemlit */
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define re register
#define rep(i, a, b) for(re int i = (a); i <= (b); ++ i)
#define drep(i, a, b) for(re int i = (b); i >= (a); -- i)
il int read() {
    re int x = 0, f = 1; re char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
    return x * f;
}
#define maxn 5005
int n, m, ans, dp[maxn][maxn], a[maxn], d[maxn];
long long sum;
il void solve(int l, int r, int *Dp) {
	if(l == r) {
		rep(i, 0, m) dp[l][i] = Dp[i];
		return;
	}
	int DP[m + 5], mid = (l + r) >> 1;
	memcpy(DP, Dp, sizeof(DP));
	rep(i, l, mid) drep(j, a[i], m) DP[j] |= DP[j - a[i]];
	rep(i, mid + 1, r) drep(j, a[i], m) Dp[j] |= Dp[j - a[i]];
	solve(l, mid, Dp), solve(mid + 1, r, DP);
}
signed main() {
	n = read(), m = read(), d[0] = 1;
	rep(i, 1, n) a[i] = read(), sum += a[i], ans += a[i] >= m;
	solve(1, n, d);
	if(sum >= m) rep(i, 1, n) if(a[i] < m) rep(j, m - a[i], m - 1) if(dp[i][j]) { ++ ans; break; }
	printf("%lld", n - ans);
	return 0;
}

```

---

## 作者：封禁用户 (赞：6)

首先这是一个很明显的背包问题，如果一个点是有用的，那么必定可以从所有其他数中选出一些数使得这些书的和为【k-ai,k)（左闭右开）;

我们可以设dp(i,j)表示在前i个数中是否可以选一些数使他们的和为j。

状态转移方程为dp(i,j)=dp(i-1,j)|(dp(i-1,j-ai)

考虑到如果一个数大于k，那么我们取k的效果是一样的，于是状态总数只有nk个，转移为O(1)。

于是现在的复杂度为O(n^2*k)，但很明显是不行的。

仔细一想，如果一个数是不合法的，那么比他小的数都是不合法的，可以通过反证法得证，如果一个数是合法的，那么比他大的数一定合法。

所以答案满足单调性，我们可以将数列进行排序，然后使用二分查找。

现在的复杂度为O(nlogn*k)，约为3e8，勉强能过去，对于O(n)需要用到许多其他知识，我就不讲了，避免新人受到误导。

帖一份用上述思路AC的代码

```
#include<bits/stdc++.h>
using namespace std;
const int N=5005;
int n,k,sum;
int a[N],dp[N][N];
bool check(int x)
{
	memset(dp,0,sizeof(dp));
	if(x==1)
	{
		dp[2][0]=1;
		dp[2][a[2]]=1;
		for(int i=3;i<=n;i++)
		{
			for(int j=0;j<=k;j++)
			{
				dp[i][j]=dp[i-1][j];
				if(j>=a[i])
					dp[i][j]=dp[i-1][j]|dp[i-1][j-a[i]];	
			}
		}
	}
	else
	{
		dp[1][0]=1;
		dp[1][a[1]]=1;
		for(int i=2;i<=n;i++)
		{
			if(x==i)
			{
				for(int j=0;j<=k;j++)
					dp[i][j]=dp[i-1][j];
				continue;
			}
			for(int j=0;j<=k;j++)
			{
				dp[i][j]=dp[i-1][j];
				if(j>=a[i])
					dp[i][j]=dp[i-1][j]||dp[i-1][j-a[i]];	
			}
		}
	}
	/*
	printf("x:%d\n",x);
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=k;j++)	
			printf("%d ",dp[i][j]);
		printf("\n");
	}
	*/
	for(int i=k-a[x];i<k;i++)
		if(dp[n][i])
			return true;
	return false;
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);	
		a[i]=min(a[i],k);
	}
	if(n==1)
	{
		if(a[1]>=k)
			printf("0\n");
		else
			printf("1\n");
		return 0;
	}
	sort(a+1,a+n+1);
	int lb=0,ub=n+1;
	while(lb+1<ub)
	{
		int mid=(lb+ub)/2;
		if(check(mid))	
			ub=mid;
		else 
			lb=mid;
	}
	printf("%d\n",lb);
	return 0;
}

```

---

## 作者：Blunt_Feeling (赞：4)

## ABC056D No Need 题解

~~很好奇为什么 URL 是 arc。~~

和 @wind_seeker 翻了所有的题解，共 [hack](https://www.luogu.com.cn/discuss/show/670871) 掉了 $4$ 篇。这些题解都有一个共性：没有使用背包，复杂度与 $k$ 无关。这道题的难点在于计算不选当前这个数时的背包，可以使用分治做到 $\mathcal{O}(nk\log_2 n)$，如果再加入 `bitset` 进行整体更新，更是可以再优化到 $\mathcal{O}(\dfrac{nk}{w})$ （$w$ 为常数）；或者你也可以像 @wind_seeker 一样推出足够强的性质进行优化。

这里再提供一种折半 DP 的做法，时间复杂度 $\mathcal{O}(nk)$。总体思路是用空间换时间，预处理时记录下从左边开始每一位的 01 背包数组，再从右边开始做背包，左右两边做合并，判断当前这一位是否多余。这样做要多开 $\mathcal{O}(nk)$ 的 `bool` 数组，但是完全可以接受。

这里具体讲讲怎么做合并。假设当前从右往左枚举到 $i$，可以枚举 $i$ 左边选的数之和的取值（下简称“取值”），判断 $i$ 右边是否有取值，使得左右两边的取值加起来在 $[k-a_i,k-1]$ 之内，若存在，则 $a_i$ 不多余。为了 $\mathcal{O}(1)$ 查询右边的背包数组，在查询之前先 $\mathcal{O}(k)$ 做一遍前缀和。

### Code
```cpp
// LUOGU_RID: 122577766（UKE了一天，但是 AT 实测 AC）
#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
inline int read() {
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x; return x;
}
const int maxn=5050;
int N,n,k,a[maxn],sum[maxn],ans=0;
bool f0[maxn][maxn],f1[maxn]; //左右两边的背包数组
int calc(int r,int l)
{
    if(l<=0) return sum[r];
    return sum[r]-sum[l-1];
}
signed main()
{
    N=n=read(); k=read();
    For(i,1,n) a[i]=read(),sum[0]+=a[i];
    if(sum[0]<k) return cout<<n<<endl,0;
    sum[0]=0;
    sort(a+1,a+n+1,greater<>());
    For(i,1,n) if(a[i]>=k) ans++;
    rotate(a+1,a+ans+1,a+n+1);
    n-=ans; //这里改了n，因此后面还有N
    f0[0][0]=true;
    For(i,1,n)
    {
        For(j,0,k) f0[i][j]=f0[i-1][j];
        Rep(j,k,a[i]) f0[i][j]|=f0[i-1][j-a[i]];
    }
    f1[0]=true;
    Rep(i,n,1)
    {
        sum[0]=1;
        For(j,1,k) sum[j]=sum[j-1]+f1[j];
        For(j,0,k-1)
            if(f0[i-1][j]&&calc(k-1-j,k-a[i]-j))
                {ans++; break;}
        Rep(j,k,a[i]) f1[j]|=f1[j-a[i]];
    }
    cout<<N-ans<<endl;
    return 0;
}
```

---

## 作者：zhaoyp (赞：2)

# Description

> 给定一个大小为 $n$ 的正整数集合，一个元素和不小于 $k$ 的非空子集被称为优秀的，问有多少个元素满足把它改成 $0$ 而不会影响优秀子集的个数。

# Solution
有一个重要的性质：若 $x$ 是必须的，则比 $x$ 大的所有数都是必须的。

设最小的一个必须的数为 $x$。

考虑一个含有 $x$ 的优秀的集合且其他元素的和小于 $k$，由于 $x$ 是必须的，所以这样的集合一定存在。集合里的元素都是必须的，那么 $x$ 是集合里最小的数。

把 $x$ 替换成其它任意比 $x$ 大的数，显然新集合也是不可删数的优秀的集合，可知替换上的元素也是必须的。

于是我们只要将 $a$ 降序排序之后找最后一个必须的数 $x$ 的位置。

考虑它的一个必要条件：

比 $x$ 大的数可以组成一个和小于 $k$ 大于等于 $k - x$ 的集合（含空集）。

然后一边扫一边做背包就行了，时间复杂度 $O(nk)$。

可以用`bitset`优化到 $O(n \log n)$。

# code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e3 + 5;
int f[maxn],n,k,a[maxn],cnt; 
bool cmp(int a,int b){return a > b;}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i = 1;i <= n;i++)
		scanf("%d",&a[i]);
	sort(a + 1,a + 1 + n,cmp);
	f[0] = 1;
	for(int i = 1;i <= n;i++)
	{
		if(a[i] >= k)
			cnt = i;
		else 
			for(int j = k - 1;j >= k - a[i];j--)
				if(f[j])
					{cnt = i;break;}
		for(int j = k;j >= a[i];j--)
			f[j] |= f[j - a[i]];
	}
	cout << n - cnt;
	return 0 ;
}
```

---

## 作者：sycqwq (赞：2)

我们观察他给出的这个定义。

发现对于一个 $a_i$，若存在一个不包括 $a_i$ 的子集和加上 $a_i$ 会成为一个优秀的集合，则这个 $a_i$ 不是可有可无的数字，反之则为。

我们可以发现，满足该条件的子集和的范围一定在 $[k-a_i,k)$ 内。

那么，我们可以发现，这个东西是可以用一个可行性背包来做的。

而对于少一样物品的背包，自然地，可以联想到 [P4095 [HEOI2013]Eden 的新背包问题](https://www.luogu.com.cn/problem/P4095)

可以模仿这题的从左往右做一次背包，再从右往左做一次背包，然后合并的思路。

我们发现，上面说的题目是给出了固定的价钱，然后进行合并，所以他的合并是 $O(k)$ 的。

而这道题，暴力合并的话，需要枚举和，然后进行合并，总复杂度就会达到 $O(nk^2)$。

可以考虑只进行枚举左边背包所贡献的和，然后发现，右边背包可以进行贡献的范围是一段连续的区间。

就可以对右边的背包进行一次前缀和，然后枚举左边的背包贡献的和，前缀和看一下右边背包是否有满足条件的数，就可以了。

总复杂度 $O(nk)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
    int s=0,f=0;
    char ch=getchar();
    while(!isdigit(ch)){
        f|=ch=='-';
        ch=getchar();
    }
    while(isdigit(ch)){
        s=(s<<1)+(s<<3)+(ch^48);
        ch=getchar();
    }
    return f?-s:s;
}
const int maxn=5005;
int n,a[maxn],k,f[maxn][maxn],l[maxn][maxn];
int main()
{ 
    n=read(),k=read();
    for(int i=1;i<=n;i++)
        a[i]=read();
    f[0][0]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=k;j++)
            f[i][j]|=f[i-1][j];
        for(int j=k-a[i];j>=0;j--)
            f[i][j+a[i]]|=f[i][j];
    }
    l[n+1][0]=1;
    for(int i=n;i>=1;i--)
    {
        for(int j=0;j<=k;j++)
            l[i][j]|=l[i+1][j];
        for(int j=k-a[i];j>=0;j--)
            l[i][j+a[i]]|=l[i][j];
    }
    for(int i=1;i<=n+1;i++)
        for(int j=1;j<=k;j++)
            l[i][j]=l[i][j-1]+l[i][j]; 
    int s=0;
    for(int i=1;i<=n;i++)
    {
        int t=0,ll=max(k-a[i],0),rr=k-1; 
        for(int j=0;j<k;j++)
        {
            if(!f[i-1][j])
                continue;
            int tl=max(ll-j,0),tr=rr-j; 
            if((l[i+1][tr]-l[i+1][tl-1])>0)
            { 
                t=1;
                break;
            }
        }
        s+=(t^1);
    }
    cout<<s;
    return 0;
}
```

---

## 作者：unicorn1220 (赞：1)

先考虑一下对于一个数 $x$，什么时候他是**需要的**。

很简单，如果说除掉他本身之外，能够凑出一个数 $y$，使得 $y<k$ 且 $x+y \ge k$，那么就是需要的。

我们可以看作在上限为 $k-1$ 的前提下凑出最大的数，因为这样最有希望满足条件二。

这不就是背包嘛。

那如何解决除掉一个数之外来找的问题呢？

还是很简单，只要正倒各跑一遍，再循环枚举平摊 $k-1$ 的上限就好。

时间复杂度 $O(nk)$。

当然，显然如果一个数是不需要的，那么比他小的数也都是不需要的，所以还可以搭配二分使用，优化一点常数。

Code

```
#include<bits/stdc++.h>
using namespace std;
int ans,n,k,a[5005],dp1[5005][5005],dp2[5005][5005];
signed main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=k;j++)
            dp1[i][j]=(j>=a[i]?max(dp1[i-1][j-a[i]]+a[i],dp1[i-1][j]):dp1[i-1][j]);
    for(int i=n;i>=1;i--)
        for(int j=1;j<=k;j++)
            dp2[i][j]=(j>=a[i]?max(dp2[i+1][j-a[i]]+a[i],dp2[i+1][j]):dp2[i+1][j]);
    for(int i=1;i<=n;i++)
    {
        int t=1;
        for(int j=0;j<k;j++)
            if(dp1[i-1][j]+dp2[i+1][k-1-j]>=k-a[i]) 
            {
                t=0;
                break;
            }//这里没用二分
        if(t==1) ans++;
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：BigJoker (赞：1)

一个很显然的贪心，那些不必要的可有可无的 $k$ 个数字一定是最小的 $k$ 个数字。

因此考虑先对 $a$ 序列按照升序排序，然后二分答案，这里的答案本质上也是在二分位置。

考虑如何写 check，其实思路很明显。

将可有可无的数字和记为 $s$，如果不是可有可无的数字中可以选出一种的组合为 $t$，满足 $t<k,s+t\ge k$ 那么说明这些数字并不是可有可无的。

现在的难点是计算后 $i$ 个数和为 $t$ 的情况了。

考虑 dp，设 $f_{i,j}$ 表示后 $i$ 个有多少种选择能满足 $\ge j$，当然这里的 $j$ 的上限是 $k$，那么计算和为 $t$ 的情况出现也就并不困难了，即 $f_{i,t}-f_{i,t+1}$ 一个比较典的 trick.

dp 式也比较好写：

$f_{i,j}\gets f_{i+1,j}+f_{i+1,\max\{j-a_i,0\}}$

初始设 $f_{n+1,0}\gets 1$，然后 check 就行了。

---

## 作者：Claire0918 (赞：0)

首先注意到可以删除具有单调性。具体来说，如果 $a_i < a_j$ 且 $a_i$ 不可删，则 $a_j$ 必然不可删。

下面给出证明。

先考虑存在一个 $b \sub \{a_i\} \setminus \{a_i, a_j\}$，使得 $\sum_{x \in b} x < k$ 且 $\sum_{x \in b} x + a_i \geq k$。

不难发现此时有 $\sum_{x \in b} x + a_j > \sum_{x \in b} x + a_i \geq k$。从而证明了 $a_j$ 是不可删的。

再考虑不存在上文中要求的 $b$，即任何 $b$ 使得 $\sum_{x \in b} x < k$ 且 $\sum_{x \in b} x + a_i \geq k$ 都满足 $a_j \in b$。

此时如果删除 $a_j$ 则原本任意一个的 $b$ 都变得不满足了，故 $a_j$ 不可删。

我们证明了该结论。$\square$

由单调性不难想到二分最后一个可删的位置。检查 $p$ 时考虑数列去掉第 $p$ 位剩余的数是否存在一个子集的和属于 $[k - a_i, k - 1]$。如果存在则该数不可删。

子集的和只需要考虑小于 $k$ 的即可，使用 bitset 优化 dp 可以做到 $\mathcal{O}(\frac{nk}{\omega})$。

特别地，如果有 $a_p \geq k$，则显然该数不可删。

时间复杂度 $\mathcal{O}(\frac{nk\log n}{\omega})$，可以通过。

Code：

```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 5000 + 10, maxk = 5000 + 10;

int n, k;
int a[maxn];

inline bool check(int x){
    if (a[x] >= k){
        return false;
    }
    bitset<maxk> f;
    f.set(0);
    for (int i = 1; i <= n && a[i] < k; i++){
        if (i != x){
            f |= f << a[i];
        }
    }
    for (int i = k - a[x]; i < k; i++){
        if (f[i]){
            return false;
        }
    }
    return true;
}

int main(){
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    sort(a + 1, a + n + 1);
    int l = 0, r = n;
    while (l < r){
        const int mid = l + r + 1 >> 1;
        if (check(mid)){
            l = mid;
        }else{
            r = mid - 1;
        }
    }
    printf("%d", l);

return 0;
}
```

---

## 作者：紊莫 (赞：0)

和现有题解稍有不同的做法。

假设原来的优秀集合个数为 $x$，我们假设 $a_i$ 是必须的，那么也就是 $x$ 个集合中的每个集合都包含了 $a_i$。

我们把 **原序列集合** 分为有 $a_i$ 的集合 $S$，和没有 $a_i$ 的集合 $T$。

结论是：求出去掉 $a_i$ 之后的优秀集合个数 $y$，若 $2y = x$，那么这个元素就是必须的。

必要性：

因为对 $T$ 中的每一个元素加入一个 $a_i$ 就可以得到 $S$，所以这两个集合大小是相等的，去掉 $a_i$ 后，因为这是必须的，所以 $S$ 集合将不存在，新的满足条件的集合大小变成一半。

充分性：

如果 $a_i$ 不是必须的，那么去掉 $a_i$ 后 $S$ 集合内一定还有东西，也就不满足 $2y = x$。

统计合法的集合个数是 $\mathcal{O}(nV)$ 的，但是转化为统计不合法的就可以变成 $\mathcal{O}(nk)$，这个可以用退背包实现，[参考代码](https://atcoder.jp/contests/abc056/submissions/55719998)。

---

## 作者：namelessgugugu (赞：0)

之前的题解全都是 $O(NKlogN)$，我来氵一篇 $O(NK)$ 的，毕竟5000的数据范围多一个log多少还是有点危的。

------------

#### 题意：
给定一个大小为 $N$ 非负整数集合 $A$，一个元素和不小于 $K$ 的 $A$ 的非空子集被称为优秀的，问 $A$ 中有多少个元素满足把它改成0而不会影响优秀子集的个数。$N,K \leqslant 5000,1 \leqslant A_i \leqslant 10^9$。

------------

#### 思路：
我们先考虑什么样的元素能成为一个**不满足条件**的数（其实正着考虑也可以，难度差不多），即改变它后会影响优秀子集的个数。显然，我们肯定能找到一个包含该元素的优秀子集，满足它的和减去该元素小于 $K$。这样我们就得到了 $O(2^NN)$ 的做法，显然过不了，我们还需要进一步优化。

由于 $A_i$ 范围太大，没了它又不好做题，先考虑减小它的范围。对于大于 $K$ 的元素， 肯定不满足条件 ，先把它们踢出去，对于一个元素和大于 $2K$ 的子集，也可以不考虑，因为就算减去 $K$ 也比 $K$ 大，还是优秀的。

经过这样一通操作，现在我们要考虑的子集的元素和都和 $K$ 同级了，可以用**背包**求出来所有子集和它们对应的元素和。但是光有子集的元素和不够啊，想要求解答案仍需要继续分析。

我们发现，这个答案好像是有**单调性**的，假如元素 $x$ 不是答案，大于 $x$ 的所有数也不是答案。因为可以找到包含 $x$ 的原优秀子集 $S$，$x$ 变为0后它的元素和小于 $K$，把 $x$ 替换成任意大于它的元素，它前后“优秀性”的改变仍然是永恒的事实。

现在，我们只需要尝试对每个优秀子集找到最小的能使它变为不优秀的子集就好了。最正常的思路肯定是把子集元素排序后从小往大扫一遍。假如现在遍历到的第一个元素 $x$ （即子集的最小元素）并不能使 $S$ 变得不优秀，那么就算去掉它，$S$ 肯定也是一个优秀的子集，而且求出来的答案只会比原来的小，由单调性，这样是完全正确的。因此，我们只需要再保存一下每个子集的最小值就好了。

------------

#### 实现：

上面说了，要用背包求出所有子集，那么如何求出它们的最小值呢，我们考虑把 $A$ 从大到小排序，这样一个子集的最小值肯定是最后加入这个子集的元素。

考虑转移方程 $f(i,j) = f(i-1,j)\ or\ f(i,j-A_i)$。其中$f(i,j)$表示前 $i$ 个元素能否凑出元素和为 $j$ 的元素，是布尔值，$or$ 是逻辑或。

同时开一个$2K \times N$ 的二维辅助数组 $g$，$g_i$ 存的是所有元素和为 $i$ 的子集的最小值对应下标。如果转移时 $f(i,j-A_i) = true$，我们就往 $g_j$ 里压入一个 $i$。这里我们相当于把很多最小值，元素和都相同的子集当成一个子集，于是子集数量就变成 $NK$ 级别的了。

然后我们遍历一下从 $K$ 到 $2K$ 的 $g$ 里的下标，打上标记，最后看一下哪些元素自身和前面的所有元素都没有标记，统计答案就做完了。实际上你可以在dp的时候就给元素打标记，并不需要 $g$。

下面是代码，由于比较短就没加多少注释。
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
const int N = 5005;
int n, k, a[N]; 
bool f[N*2], can[N]; 
int main(void)
{
	scanf("%d%d", &n, &k);
	for(int i = 1;i <= n;++i)
		scanf("%d", a+i);
	std::sort(a+1, a+1+n, std::greater<int>());
	//这里是把a从大到小排序，懒得写cmp了 
	f[0] = 1;
	for(int i = 1;i <= n;++i)
		if(a[i] < k)
			for(int j = k*2;j >= a[i];--j)
				if(f[j-a[i]])
				{
					f[j] = 1;
					if(j >= k && j-a[i] < k)//如果当前优秀子集去掉ai不优秀了就打上标记 
						can[i] = 1;
				} 
	int ans = 0;
	for(int i = n;i >= 1 && a[i] < k && !can[i];--i)//注意大于k的ai也不能计入答案 
		++ans;
	printf("%d\n", ans);
	return 0;
}
```

---

