# Strip

## 题目描述

Alexandra has a paper strip with $ n $ numbers on it. Let's call them $ a_{i} $ from left to right.

Now Alexandra wants to split it into some pieces (possibly $ 1 $ ). For each piece of strip, it must satisfy:

- Each piece should contain at least $ l $ numbers.
- The difference between the maximal and the minimal number on the piece should be at most $ s $ .

Please help Alexandra to find the minimal number of pieces meeting the condition above.

## 说明/提示

For the first sample, we can split the strip into $3$ pieces: $[1,3,1], [2,4], [1,2]$.

For the second sample, we can't let $1$ and $100$ be on the same piece, so no solution exists.

## 样例 #1

### 输入

```
7 2 2
1 3 1 2 4 1 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
7 2 2
1 100 1 100 1 100 1
```

### 输出

```
-1
```

# 题解

## 作者：critnos (赞：12)

设 $dp_i$ 为序列 $[1,i]$ 的答案，要求的就是 $dp_n$。

这个就是套路的 1D/1D dp（序列分段类的问题的套路）。即 $dp_i=\min_{j=l}^r val(j,i)+dp_{j-1}$。


对于第二个限制，设 $w$ 为满足 $\max(a[w,i])-\min(a[w,i])\le s$ 的最小的数，发现 $w$ 随 $i$ 不减（反证易得）。那么转移区间为 $[w,i]$。对于第一个限制显然转移区间是 $[1,i-l+1]$。这个 $val$ 函数就是新开一段区间，就是 $1$ 嘛。这两个区间的并集为 $[w,i-l+1]$。

即 $dp_i=\min_{j=w}^{i-l+1} dp_{j-1}+1$

那么维护方式就很显然了。

三个量（$i,i-l+1,w$）都不减所以可以全部使用单调队列。

$w$ 不减所以我们维护关于 $a$ 区间 $[w,i]$ 的维护最大值和最小值的单调队列，直接扫描过去即可。再对 $dp$ 的 $[w-1,i-l]$ 区间维护单调队列。$\Theta(n)$ 的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[100005];
int a[100005];
deque<int> dpmn,mn,mx;
int main()
{
	memset(dp,127,sizeof(dp));
	int n,l,s,p,i,j,w;
	scanf("%d%d%d",&n,&s,&l);
	for(i=1;i<=n;i++)
		scanf("%d",&a[i]);
	w=1;
	dp[0]=0;
	for(i=1;i<l;i++)
	{
		while(mn.size()&&a[mn.back()]>=a[i])
			mn.pop_back();
		mn.push_back(i);
		while(mx.size()&&a[mx.back()]<=a[i])
			mx.pop_back();
		mx.push_back(i);
	}
	for(i=l;i<=n;i++)
	{
		while(mn.size()&&a[mn.back()]>=a[i])
			mn.pop_back();
		mn.push_back(i);
		while(mx.size()&&a[mx.back()]<=a[i])
			mx.pop_back();
		mx.push_back(i);
		for(;w<=i;w++)
		{
			while(mn.front()<w) mn.pop_front();
			while(mx.front()<w) mx.pop_front();
			if(a[mx.front()]-a[mn.front()]<=s) break;
		}
		while(dpmn.size()&&dp[dpmn.back()]>=dp[i-l]) dpmn.pop_back();
		dpmn.push_back(i-l);
		while(dpmn.size()&&dpmn.front()<w-1) dpmn.pop_front();
		if(w<=i-l+1&&dpmn.size())
			dp[i]=dp[dpmn.front()]+1;
	}
	cout<<(dp[n]>1e9?-1:dp[n]);
}
```

---

## 作者：Honor誉 (赞：10)

[我的博客](https://blog.csdn.net/qq_35019468/article/details/102019674)

直接RMQ即可，最后套一个简单DP。

RMQ求出区间的元素的最大值和最小值。

后面直接一遍DP。

dp[i]表示前i个数最少要分成多少份。

满足条件时：

$dp[i]=min(dp[i],dp[ok]+1)$

```cpp
#include<bits/stdc++.h>
#define inf 2147483647
#define N 100010
using namespace std;
int maxn[N][22],minn[N][22],n,s,ll,dp[N],cnt;
int ask(int l,int r)//求差的最大值
{
	int ans=0;
	while((1<<(ans+1))<=r-l+1)
	{
		ans++;
	}
	return max(maxn[l][ans],maxn[r-(1<<ans)+1][ans])-min(minn[l][ans],minn[r-(1<<ans)+1][ans]);
}
int read()
{
	int sum=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f=-1;
		}
		ch=getchar();
	}
	while(ch<='9'&&ch>='0')
	{
		sum=sum*10+ch-'0';
		ch=getchar();
	}
	return sum*f;
}
int main()
{
	n=read();
	s=read();
	ll=read();
	for(int i=1;i<=n;i++)
	{
		maxn[i][0]=minn[i][0]=read();
	}
	for(int i=1;(1<<i)<=n;i++)
	{
		for(int j=1;j+(1<<i)-1<=n;j++)
		{
			minn[j][i]=min(minn[j][i-1],minn[j+(1<<(i-1))][i-1]);
			maxn[j][i]=max(maxn[j][i-1],maxn[j+(1<<(i-1))][i-1]);
		}
	}
	for(int i=1;i<=n;i++)
	{
		dp[i]=inf;
	}
	for(int i=ll;i<=n;i++)//DP
	{
		while(i-cnt>=ll&&(ask(cnt+1,i)>s||dp[cnt]==inf))
		{
			cnt++;
		}
		if(i-cnt>=ll)
		{
			dp[i]=min(dp[i],dp[cnt]+1);
		}
	}
	if(dp[n]==inf)
	{
		puts("-1");
	}else{
		printf("%d\n",dp[n]);
	}
	return 0;
}
```

---

## 作者：rainygame (赞：8)

感觉第一篇题解讲的不太详细，而且我的单调队列做法更加简单，所以也写了一个题解。

显然，本题是 DP 题，所以我们要设置状态和转移方程。

设 $f_i$ 为 $[1,i]$ 最少分得的段数，那么显然 $f_0 = 0$。状态转移方程为：

$$
f_i = \min\limits_{j=1}^{i-l+1}f_j+1 \ (\max\limits_{k=j+1}^ia_i-\min\limits_{k=j+1}^ia_i \leq s)
$$

如果就这样DP的话，时间复杂度是 $\mathcal{O}(n^3)$ 的，无法通过此题。因此我们需要考虑优化。

我们发现，我们其实可以不用每次都枚举 $j$。因为如果 $[j,i]$ 的极差已经超过了 $s$，那么 $[j-1,i]$ 的极差肯定也超过了 $s$，所以不需要考虑前面的 $j$，只需要维护一个决策点 $c$ 即可。同时，如果 $c$ 越大，$f_c$ 也会更大或不变（因为分得的段数会更多），所以，我们只需要找最小的合法的 $c$ 即可。

这样，时间复杂度就降到了 $\mathcal{O}(n^2)$。还需要继续优化。

考虑优化极差的计算。既然 $c$ 和 $i$ 都递增，那我们就可以考虑用单调队列来优化极差的计算。我们只需要在每次遍历 $i$ 的时候维护一下单调性，然后在查询的时候维护一下区间范围即可。这样，我们总的时间复杂度就可以降到 $\Theta(n)$ 了。可以通过此题。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define MAXN 100005
#define INF 0x3f3f3f3f

int n, k, s, c;
int dp[MAXN], b[MAXN];
deque<int> minn, maxn;

inline int query(){  // 查询极差
	while (!minn.empty() && minn.front() < c+1) minn.pop_front();
	while (!maxn.empty() && maxn.front() < c+1) maxn.pop_front();
	return b[maxn.front()] - b[minn.front()];
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	memset(dp, 0x3f, sizeof(dp));
	cin >> n >> s >> k;
	for (int i=1; i<=n; i++) cin >> b[i];
	dp[0] = 0;  // 边界条件
	
	for (int i=1; i<=n; i++){
		while (!minn.empty() && b[minn.back()] >= b[i]) minn.pop_back();  // 维护单调性
		minn.push_back(i);
		while (!maxn.empty() && b[maxn.back()] <= b[i]) maxn.pop_back();
		maxn.push_back(i);
		if (i >= k){
			while ((i-c >= k) && (query() > s || dp[c] == INF)) c++;  // 维护决策点
			if (i-c >= k) dp[i] = dp[c]+1;  // 转移
		}
	}
	
	cout << (dp[n] == INF ? -1 : dp[n]);  // 注意转移不到的问题
	
	return 0;
}
```

其它的题解也讲得很详细，可以看一下。

~~第一次写紫题题解，管理员求过。~~

---

## 作者：一只书虫仔 (赞：6)

#### Description

> 给定一个长为 $n$ 的序列 $a_i$，求把 $a_i$ 分成若干部分使得：
>
> 1. 每一部分长度至少为 $l$。
> 2. 每一部分的极差不超过 $s$。
>
> 求最少能分成多少份。

#### Solution

ST 表优化动态规划（不知道能不能这么说）好玩题。

首先先 dp，定义 $dp_i$ 为截止到 $a_i$  的答案，则有；

$$dp_i=\min\{dp_j\ (j \in [1, i - l],\max\{a_k\ (k \in [j,i])\}-\min\{a_k\ (k\in [j,i])\})\}+1$$

不难发现，后面这一段约束 $\max\{a_k\ (k \in [j,i])\}-\min\{a_k\ (k\in [j,i])\}$（即求极差）可以用 ST 表进行优化。

但是这样直接这样 dp 是 $\mathcal O(n^2)$ 的，我们需要优化为 $\mathcal O(n \log n)$。

假设我们现在分别在若干个位置 $c_1,c_2,\cdots,c_p$ 对这个序列进行了分割，那么这时如果我们要移动 $c_1$ 往右，剩下的分割点就会逐渐紧凑。题目中要求的是最少能分成多少份，分的越松散越好。

因此我们在优化的时候可以不让 $j$ 在 $[1,i-l]$ 询问，可以建立一个变量 $tmp$，在这一轮的转移充当着上一轮的答案，然后往右找，直到满足要求，就转移。

最后当转移不到 $n$ 时，就代表不存在满足条件的区间，输出 $-1$。

注意有一个比较小的细节，就是 $dp$ 数组最好全部初始化为 $\infty$，这样有助于转移和特判无解。

---

## 作者：pldzy (赞：3)

## Solution

没想到这道题就个 RMQ + 简单 dp。从小到大遍历 $l$ 到 $n$，对于每个确定的区间右端点 $i$，记 $f_i$ 表示 $[1,i]$ 中最少能分成几段。那么显然，$f_i = \min(f_j|j\in[1,i - l + 1]) + 1$。当然，前提是 $f_j$ 可被分为若干段。

下面先贴上代码，后面会详讲优化及其原因。
   
   （看见前面几篇题解都没有提到这个优化的具体原因。）

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(register int i = a; i <= b; ++i)
#define per(i, a, b) for(register int i = a; i >= b; --i)
typedef long long ll ;
const int inf = 2147483647;
inline int rd(){
    int x = 1, s = 0; char ch = getchar();
    while(ch < '0' or ch > '9'){if(ch == '-') x = -1; ch = getchar();}
    while(ch >= '0' and ch <= '9') s = s * 10 + ch - '0', ch = getchar();
    return x * s;
}
inline void wr(int x){
    if(x < 0) putchar('-'), x *= -1;
    if(x > 9) wr(x / 10);
    putchar(x % 10 + '0');
}
const int maxn = 1e5 + 5;
//----------------------------------//
int n, l, s;
int mn[maxn][30], mx[maxn][30], rec;
int lg[maxn], f[maxn];

inline void pre(){
	for(int i = 1; (1 << i) <= n; ++i)
		for(int j = 1; j + (1 << i) - 1 <= n; ++j)
			mn[j][i] = min(mn[j][i - 1], mn[j + (1 << (i - 1))][i - 1]),
			mx[j][i] = max(mx[j][i - 1], mx[j + (1 << (i - 1))][i - 1]);
}

inline int chck(int L, int R){
	int k = 0;
	while((1 << (k + 1)) <= R - L + 1) k += 1;
	int mi = min(mn[L][k], mn[R - (1 << k) + 1][k]);
	int ma = max(mx[L][k], mx[R - (1 << k) + 1][k]);
	return ma - mi;
}
	
int main(){
	n = rd(), s = rd(), l = rd();
	rep(i, 1, n) f[i] = inf, mx[i][0] = mn[i][0] = rd();
	pre();
	rep(i, l, n){
		while(i - rec + 1 > l and ((f[rec] == inf) or (chck(rec + 1, i) > s)))
			rec += 1;
		if(i - rec + 1 > l) f[i] = min(f[i], f[rec] + 1);
	}
	if(f[n] != inf) wr(f[n]);
	else wr(-1);
}
```

    
   
   在上面的代码中可以看到具体实现。这里有个优化：为什么每次枚举到一个新的右端点，不需要从头再选一次 $f$ 值最小的左端点 $j$ 呢？这时候要注意到一个很重要的性质：对于一个区间 $[p,q]$，若将 $q+1$ 这个节点也加进来，它要么对这个区间的极差没有影响，要么只会将这个极差变得更大。所以，若是一个左端点 $j$，满足区间 $[j,i-1]$ 的极差大于 $s$，那么区间 $[j,i]$ 的极差也必定大于 $s$（其他情况同理）。同时，左端点 $j$ 越往右，$f_j$ 只会不变或更大。
    
   综上，我们只需要继续上一个枚举的 $i$ 的左端点的位置往后枚举新的左端点，并且取最左边的合法左端点即可。

------------
感谢阅读。

辛苦管理员审核，如有问题烦请指出。

---

## 作者：BreakPlus (赞：3)

额，为啥没有线段树优化 dp 的题解啊…… 这题我的第一反应就是线段树优化  dp。

我们可以先推出状态转移方程。设 $f_i$ 表示前 $i$ 个数至少分成几段：

$f_i=\operatorname{min} \{ f_j\}+1 \ \ \ (j\le i-l)$ 

注意：其中区间 $[j+1,i]$ 需要满足极差 $\le s$。

容易知道满足条件的 $j$ 是连续的一段，因为 $j$ 不断向左移动，极差只会变大或不变。我们可以用 ST 表求区间 RMQ，然后二分 $j$ 的最小值。至于 $f_j$ 的求 $\operatorname{min}$，显然可以用线段树维护啦。

虽说线段树 + ST 表码量有亿点大，可是思路还是比较好想的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define Maxn 400010
#define int long long
int n,s,l,a[Maxn];
int f[25][Maxn],g[25][Maxn],p;
int ls[Maxn],rs[Maxn],val[Maxn],dp[Maxn];
inline int maxx(int a,int b){return a>b?a:b;}
inline int minn(int a,int b){return a<b?a:b;}
inline void startRMQ(){
	for(int i=1;i<=n;i++) f[0][i]=g[0][i]=a[i];
	p=log2(n);
	for(int i=1;i<=p;i++)
		for(int j=1;j<=(n-(1<<i)+1);j++)
			f[i][j]=maxx(f[i-1][j],f[i-1][j+(1<<(i-1))]);
	for(int i=1;i<=p;i++)
		for(int j=1;j<=(n-(1<<i)+1);j++)
			g[i][j]=minn(g[i-1][j],g[i-1][j+(1<<(i-1))]);
}// ST 表的预处理
inline int RMQmax(int x,int y){
	int p2=log2(y-x+1);
	return maxx(f[p2][x],f[p2][y-(1<<p2)+1]);
}
inline int RMQmin(int x,int y){
	int p2=log2(y-x+1);
	return minn(g[p2][x],g[p2][y-(1<<p2)+1]);
}// 查询
inline void pushup(int pos){
	val[pos]=minn(val[pos<<1],val[pos<<1|1]);
}
inline void build(int l,int r,int pos){
	ls[pos]=l,rs[pos]=r;
	if(l==r){
		val[pos]=dp[l];
		return;
	}
	int mid=l+r>>1;
	if(l<=mid) build(l,mid,pos<<1);
	if(mid<r)  build(mid+1,r,pos<<1|1);
	pushup(pos);
}
inline void Update(int l,int num,int pos){
	if(ls[pos]==rs[pos]){
		val[pos]=num;
		return;
	}
	int mid=ls[pos]+rs[pos]>>1;
	if(l<=mid) Update(l,num,pos<<1);
	else Update(l,num,pos<<1|1);
	pushup(pos); 
}
inline int Query(int l,int r,int pos){
	if(l<=ls[pos] && rs[pos]<=r) return val[pos];
	int mid=ls[pos]+rs[pos]>>1,ans=9e18;
	if(l<=mid) ans=Query(l,r,pos<<1);
	if(mid<r)  ans=minn(ans,Query(l,r,pos<<1|1));
	return ans;
} // 以上线段树板子（
signed main(){
	cin>>n>>s>>l;
	for(int i=1;i<=n;i++) cin>>a[i];
	memset(dp,127,sizeof dp); dp[0]=0; // 初始化
	startRMQ(); build(0,n,1); // 建树要带上 0 求值的时候需要用到，自行理解
	for(int i=l;i<=n;i++){
		int lft=1,rht=i,ans=-1;
		while(lft<=rht){
			int mid=lft+rht>>1;
			if(RMQmax(mid,i)-RMQmin(mid,i)<=s){
				ans=mid;
				rht=mid-1;
			}else lft=mid+1;
		} // 二分出左端点
		if(ans==-1 || ans>(i-l+1)) continue; // 没有可以转移的
		dp[i]=Query(ans-1,i-l,1)+1; // 计算
		Update(i,dp[i],1); // 修改
	//	cout<<ans<<" "<<i<<" "<<dp[i]<<endl;
	}
	if(dp[n]>1e7) cout<<(-1)<<endl;
	else cout<<dp[n]<<endl;
	return 0;
}

```

---

## 作者：qfpjm (赞：2)

# 题解

- $s,l$ 如题，设$\{a_i\}$ 为原数组，$dp_i$ 为第 $i$ 位时最少的分段数，则 $dp$ 方程为：

$$dp_i=\min\{dp_j+1\}(j\in[1,i-l],\max\{a_k(k\in[j,i])\}-\min\{a_k(k\in[j,i]\}\le s)$$

- 显然可以发现，后面的 $\max\{a_k(k\in[j,i])\}-\min\{a_k(k\in[j,i]\}$ 可以用 $ST$ 表来维护，时间复杂度 $O(n\log n)$，十分简单就不详讲。

- 但是即使用了 $ST$ 表，$dp$ 状态转移时间复杂度仍为 $O(n^2)$。我们可以用一个变量，记录下最右侧的分割点，每次从这个分割点的答案往右找，由于这个分割点会不断往右，所以时间复杂度很低，接近 $O(n)$。

- 最后当转移不到 $n$ 时，输出 $-1$ 即可。

- 最终时间复杂度为 $O(n\log n+n)$。

---

## 作者：chihik (赞：2)


一道并不难的 $dp$ 题。转移式很好列：

$$
dp[i]=min\{ dp[j]+1 \} ~~~~ (0 \le j \le i - l~\&\&max(j+1,i)-min(j+1,i)<=s)
$$

看到区间的最大值与最小值之差，我们很容易想到用 $st$ 表维护。这样可以$\Theta(n^2)$解决。

很显然的一个结论是，决策点是单调递增的。因为 $i$ 不断向右，区间的最值递增，决策点也必须向右调整。

并且，为了使答案更优，我们每次一定会选择最靠左的那个决策点。

所以，只需要维护最左边的决策点即可，转移复杂度$\Theta(n)$。

总时间复杂度$\Theta(nlogn+n)$

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define INF 0x3f3f3f3f

const int MAXN = 100000 , MAXK = 20;
int n , l , s , a[ MAXN + 5 ] , f[ 2 ][ MAXN + 5 ][ MAXK + 5 ]; //0->max 1->min
int dp[ MAXN + 5 ];

void Init( ) {
    memset( f[ 1 ] , 0x3f , sizeof( f[ 1 ] ) );
    
    for( int i = 1 ; i <= n ; i ++ )
        f[ 0 ][ i ][ 0 ] = f[ 1 ][ i ][ 0 ] = a[ i ];
    for( int j = 1 ; ( 1 << j ) <= n ; j ++ )
        for( int i = 1 ; i + ( 1 << j ) - 1 <= n ; i ++ ) {
            f[ 0 ][ i ][ j ] = max( f[ 0 ][ i ][ j - 1 ] , f[ 0 ][ i + ( 1 << j - 1 ) ][ j - 1 ] );
            f[ 1 ][ i ][ j ] = min( f[ 1 ][ i ][ j - 1 ] , f[ 1 ][ i + ( 1 << j - 1 ) ][ j - 1 ] );
        }
}
int Query( int l , int r ) {
    int k = log2( r - l + 1 );
    return max( f[ 0 ][ l ][ k ] , f[ 0 ][ r - ( 1 << k ) + 1 ][ k ] ) - min( f[ 1 ][ l ][ k ] , f[ 1 ][ r - ( 1 << k ) + 1 ][ k ] );
}

int main( ) {
    scanf("%d %d %d",&n,&s,&l);
    for( int i = 1 ; i <= n ; i ++ ) 
        scanf("%d",&a[ i ]);
    Init( );

    memset( dp , 0x3f , sizeof( dp ) ); dp[ 0 ] = 0;
    int chk = 0;
    for( int i = l ; i <= n ; i ++ ) {
        while( ( i - chk >= l && ( Query( chk + 1 , i ) > s ) || dp[ chk ] == INF ) ) chk ++;
        if( i - chk >= l ) dp[ i ] = dp[ chk ] + 1;
    }
    printf("%d", dp[ n ] == INF ? -1 : dp[ n ] );
    return 0;
}
```


---

## 作者：int_stl (赞：1)

遇到这种题先别急，先想着打暴力。

我们想象一个转移方程，令 $f_i$ 表示以 $i$ 结尾的子串划分的最小段数，有：

$$
f_i = \min_{\max_{j \le k \le i}\{a_i\}-\min_{j \le k \le i}\{a_i\} \le s,i-j+1 \ge l} \{f_{j - 1}\} + 1.
$$

接下来我们当然希望可以缩小 $j$ 的范围，那么我们对于每个 $i$，都可以确定这个范围：

- 右端点：显然地，我们要令 $j_{\text{max}} + l - 1 = i$，故 $j_{\text{max}} = i - l + 1$。

- 左端点：我们要找到一个 $j_{\text{min}}$ 以满足：

  $$
  \max_{j_{\text{min}} \le k \le i}\{a_i\}-\min_{j_{\text{min}} \le k \le i}\{a_i\} \le s.
  $$

  我们尝试考虑当 $j_{\text{min}}$ 左右移动时的情况：

  > - $j_{\text{min}}$ 向左移动：加入的数变多，最大值不减，最小值不增，此时区间极差不减。
  > - $j_{\text{min}}$ 向右移动：加入的数变少，最大值不增，最小值不减，此时区间极差不增。

  可见，极差在这里拥有「单调性」，故可以使用单调队列去记录 $j_{\text{min}}$，设其为 $p_i$，则 $j_{\text{min}} = p_i$。

确定完转移区间后，原转移方程变为：

$$
\begin{aligned}
f_i &= \min_{j \in [p_i, i - l + 1]}\{f_{j - 1}\} + 1 \\ &= \min_{j \in [p_i - 1, i - l]}\{f_j\} + 1.
\end{aligned}
$$

接下来就是线段树求区间最小值，线段树单点修改优化的事了。时间复杂度可以做到 $O(n\log n)$。

参考代码：

```cpp
#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e5 + 6, INF = 1e18;

struct DS {
    std::vector<int> c;
    int m;
    DS(int n) {
        for (m = 1; m <= n + 1; m <<= 1);
        c.resize(m << 1, INF);
    }
    void update(int p, int v) {
        c[p += m] = v;
        for (p >>= 1; p; p >>= 1) {
            c[p] = std::min(c[p * 2], c[p * 2 + 1]);
        }
    }
    int query(int l, int r) {
        int ans = INF;
        for (l += m - 1, r += m + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
            if (~l & 1) {
                ans = std::min(ans, c[l ^ 1]);
            }
            if (r & 1) {
                ans = std::min(ans, c[r ^ 1]);
            }
        }
        return ans;
    }
};

void solve() {
    int n, l, d;
    std::cin >> n >> d >> l;
    std::vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    std::vector<int> minL(n + 1, 1);
    std::deque<int> min_dq, max_dq;
    int p = 1;
    for (int i = 1; i <= n; ++i) {
        while (!min_dq.empty() && a[min_dq.back()] >= a[i])
            min_dq.pop_back();
        min_dq.push_back(i);
        while (!max_dq.empty() && a[max_dq.back()] <= a[i])
            max_dq.pop_back();
        max_dq.push_back(i);
        while (!max_dq.empty() && !min_dq.empty()
            && a[max_dq.front()] - a[min_dq.front()] > d) {
            if (min_dq.front() == p)
                min_dq.pop_front();
            if (max_dq.front() == p)
                max_dq.pop_front();
            ++p;
        }
        minL[i] = p;
    }
    std::vector<int> dp(n + 1, INF);
    dp[0] = 0;
    DS seg(n + 1);
    seg.update(0, dp[0]);  
    for (int i = 1; i <= n; i++) {
        int L = minL[i] - 1, R = i - l;
        if (L <= R && R >= 0) {
            int x = seg.query(L, R);
            if (x != INF) dp[i] = x + 1;
        }
        seg.update(i, dp[i]);
    }
    std::cout << (dp[n] >= INF ? -1 : dp[n]) << "\n";
}

int32_t main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0), std::cout.tie(0);

  int t;
  // std::cin >> t;
  t = 1;

  while (t--) {
    solve();
  }

  return 0;
}
```

---

## 作者：Carey_chen (赞：1)

这是一种双指针+ ST 表做法。

首先可以想到一个简单的 $dp$ ，定义 $dp_i$ 表示 $[1, i]$ 至少需要分成的段数。

可以得到：

$$dp_{i} = \min_{1 \leq j \leq i-l}\{dp_j + 1\}\,\,\,(\max_{j < k \leq i} \{a_k\} - \min_{j < k \leq i} \{a_k\} \leq s)$$

这个式子可以 $O(n^2)$ 转移：在枚举 $j$ 时可顺便更新区间的的最大值和最小值。

还可以进一步优化，由于越往后分得的段数越多， $dp$ 数组除去无解部分一定单调不降。即： $j$ 越小，它越容易成为那个最小值。所以要对每一个 $dp_{i}$ 找到一个最小的 $j$ 满足题目要求。

在同一序列中，$[j, i]$ 的最大值和最小值之差一定大于等于 $[j+1, i]$ 的，**所以在 $i$ 递增时 $j$ 一定不降**，可以使用双指针维护 $j$，再加上 ST 表求最大值和最小值之差。

```cpp
#include <bits/stdc++.h>

using namespace std;

int a[100010], dp[100010];
int Max[100010][30], Min[100010][30], nxt[100010][30];

int QMax(int l, int r) {...} // 求区间最大值
int QMin(int l, int r) {...} // 求区间最小值

int main()
{
	int n, s, l;
	scanf("%d %d %d", &n, &s, &l);
	
	memset(Min, 0x3f, sizeof(Min));
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		Max[i][0] = a[i];
		Min[i][0] = a[i];
		nxt[i][0] = i + 1;
	}
	
	for(int j = 1; j <= 20; j++)
	{
		for(int i = 1; i <= n; i++)
		{
			nxt[i][j] = nxt[nxt[i][j-1]][j-1];
			Max[i][j] = max(Max[i][j-1], Max[nxt[i][j-1]][j-1]);
			Min[i][j] = min(Min[i][j-1], Min[nxt[i][j-1]][j-1]);
		}
	}
	
	dp[0] = 0;
	
	for(int i = 1, j = 0; i <= n; i++)
	{
		while(j + 1 < i && (QMax(j + 1, i) - QMin(j + 1, i) > s || dp[j] == 1e9))
		{
			j++;
		}
		if(i - j >= l)
		{
			dp[i] = dp[j] + 1;
		}
		else
		{
			dp[i] = 1e9;
		}
	}
	
	printf("%d", dp[n] == 1e9 ? -1 : dp[n]);
	
	return 0;
}
```

---

## 作者：刘嘉琦 (赞：1)

结合数据范围，这题的思路较为明显：dp（总不能贪心吧）。

我们定义一个 $dp$ 数组，其中 $dp_i$ 表示前 $i$ 个数最少能分成的段数。

**初值**：很显然，$dp_0 = 0$。

**递推**：如何得到 $dp_i$？我们以最后一段的长度分类，循环每一种长度，将所有满足条件的最后一段（长度不小于 $l$，极差不超过 $s$） 前面一个位置的 $dp$ 值取最小值加 $1$，就是 $dp_i$。即：
$$dp_i = \min dp_j + 1 (i - j \geq l, \max_{k=j+1}^ia_i - \min_{k=j+1}^ia_i \leq s)$$

每次检查极差时，我们可以用 ST 表 $O(1)$ 查询极差。

但是这样整个 dp 是 $O(n^2)$ 的！还要怎么优化呢？

首先，我们要知道，在一个固定的数列当中，假如增加一些数，极差只可能不变或增大，一定不可能减小，反之亦然。这是因为，每当加入一个数时，整个数列的最大值不可能变小，最小值也不会变大，因此极差也不会变小。

既然如此，我们就可以维护一个指针 $cur$，表示 dp 中最后一段前一个位置最右的可能值。在当前查询的最后一段极差超过 $s$ 时，$cur$ 右移（因为在后面的 dp 过程中，只会增加数，而 $cur$ 左移也是增加数的操作，这样会使得极差更大）。

还有一点：既然我们想要 $dp$ 值中的最小值，何不用另一个 ST 表维护呢？虽然说 ST 表不支持插入操作，但是指向末尾插入元素是可以 $O(\log n)$ 解决的。

经过这样的优化，整体复杂度变为 $O(n \log n)$。

**代码**
```cpp
#include <cstdio>
namespace LJQ {
	const int INF = 0x7fffffff, mINF = 0x3f3f3f3f;
	const long long INFll = 0x7fffffffffffffff, mINFll = 0x3f3f3f3f3f3f3f3f;
	template <typename T>
	T& read(T& s) {
		s = 0;
		T f = 1;
		char ch = getchar();
		while (ch < '0' || ch > '9') {
			if (ch == '-')
				f = -1;
			ch = getchar();
		}
		while ('0' <= ch && ch <= '9')
			s = s * 10 + ch - '0', ch = getchar();
		return s *= f;
	}
	template <typename T>
	inline T max(T x, T y) {
		return x > y ? x : y;
	}
	template <typename T>
	inline T min(T x, T y) {
		return x < y ? x : y;
	}
   	template <typename T>
	inline void swap(T& x, T& y) {
		T tmp = x;
		x = y;
		y = tmp;
	}
}
using namespace LJQ;

const int N = 100005;
int n, s, l, a[N];
int pw[25], log2[N];
int st1[N][25], st2[N][25];
int dp[N], st_dp[N][25], cnt = 0;

void initST() {
	for (int i = 1; i <= n; i++)
		st1[i][0] = st2[i][0] = a[i];
	for (int j = 1; pw[j] <= n; j++)
		for (int i = 1; i + pw[j] - 1 <= n; i++) {
			st1[i][j] = max(st1[i][j - 1], st1[i + pw[j - 1]][j - 1]);
			st2[i][j] = min(st2[i][j - 1], st2[i + pw[j - 1]][j - 1]);
		}
}

void init() {
	pw[0] = 1;
	for (int i = 1; i <= 20; i++)
		pw[i] = pw[i - 1] << 1;
	log2[1] = 0;
	for (int i = 2; i <= n; i++)
		log2[i] = log2[i >> 1] + 1;
	initST();
}

int qry(int a, int b) {
	int j = log2[b - a + 1];
	return max(st1[a][j], st1[b - pw[j] + 1][j])
		 - min(st2[a][j], st2[b - pw[j] + 1][j]);
}

// 插入操作，把 ST 表每一层的最后一段更新就好了
void ins(int x) {
	st_dp[++cnt][0] = x;
	for (int j = 1; pw[j] <= cnt; j++) {
		int i = cnt - pw[j] + 1;
		st_dp[i][j] = min(st_dp[i][j - 1], st_dp[i + pw[j - 1]][j - 1]);
	}
}

int qry_dp(int x, int y) {
	int j = log2[y - x + 1];
	return min(st_dp[x][j], st_dp[y - pw[j] + 1][j]);
}

int main()
{
	read(n), read(s), read(l);
	for (int i = 1; i <= n; i++)
		read(a[i]);
	init();
	int cur = 0;
	dp[0] = 0; // 初值
	for (int i = 1; i <= n; i++) {
		// 当最后一段的长度即将超过 l 时，就不要再移动 cur 了
		// 否则，当最后一段极差超过 s，或前一位 dp 值为不可能，cur 右移 
		while (i - cur >= l && (qry(cur + 1, i) > s || dp[cur] == INF))
			cur++;
		// 如果前 i 个数无法分段，则 dp 值为正无穷
		// 这样插入 ST 表时就不会影响其他有效 dp 值的最小值 
		if (i - cur < l)
			dp[i] = INF;
		else {
			int res = qry_dp(cur, i - l);
			// 当前面的 dp 值都为不可能时，说明 dp[i] 也无效 
			if (res == INF)
				dp[i] = INF;
			else 
				dp[i] = res + 1;
		}
		ins(dp[i]);
	}
	if (dp[n] == INF)
		printf("-1\n");
	else
		printf("%d\n", dp[n]);
	return 0;
}
```

---

## 作者：crashed (赞：1)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.com.cn/problem/CF487B)看题目。  
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;不难看出这是一个$dp$:  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$f(i)$：前$i$个数分组的最少数量。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;设$\displaystyle mx(i,j)=\max_{i\le k\le j}a_k,mn(i,j)=\min_{i\le k\le j}a_k$然后可以看出转移：  
$$f(i)=\min_{0<j\le i,mx(j,i)-mn(j,i)\le S}\{f(j)+1\}$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;时间$O(n^2)$。考虑优化。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;假如我们从左边开始往右边推。对于$f(i)$，用它去更新后面的那些$f(j)$。发现题目的限制条件之二非常熟悉。如果把限制条件二提出来，这个其实是一道经典的单调队列的题目——也就是说，我们可以使用单调队列，求出以一个点为左端点的时候，右端点的最大值。这个可以均摊$O(1)$。然后，假如以$i$为左端点的最大右端点为$r_i$，那么用$i$更新的时候，区间$[i+l,r_{i+1}]$的部分都可以用$i$更新（注意，此时的下一个段是从$i+1$开始的，所以右边界是$r_{i+1}$）。区间修改单点查询的问题，自然就想到了用线段树来维护这个$f$。时间是$O(n\log_2n)$。
# 代码
```cpp
#include <cstdio>

#define isLeaf( a ) ( segTree[a].l == segTree[a].r )

const int INF = 0x3f3f3f3f;
const int MAXN = 1e5 + 5;

template<typename _T>
void read( _T &x )
{
	x = 0; char s = getchar();int f = 1;
	while( s < '0' || '9' < s ) { f = 1; if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ) { x = ( x << 3 ) + ( x << 1 ) + s - '0', s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ) { putchar( '-' ), x = -x; }
	if( 9 < x ) { write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

struct segmentTreeNode
{
	int l, r;
	int mn; bool tag;
}segTree[MAXN << 2];

int deq1[MAXN], h1, t1;
int deq2[MAXN], h2, t2;
int a[MAXN];
int N, S, L;

void build( const int now, const int left, const int right )
{
	segTree[now].l = left, segTree[now].r = right, segTree[now].mn = INF, segTree[now].tag = false;
	if( isLeaf( now ) ) return ;
	build( now << 1, left, left + right >> 1 ), build( now << 1 | 1, ( left + right >> 1 ) + 1, right );
}

void cover( const int now, const int val ) 
{ 
	if( val < segTree[now].mn ) segTree[now].mn = val, segTree[now].tag = true;
}

void normalize( const int now )
{
	if( ! segTree[now].tag ) return ;
	cover( now << 1, segTree[now].mn ), cover( now << 1 | 1, segTree[now].mn );
	segTree[now].tag = false;
}

void update( const int now, const int segL, const int segR, const int val )
{
	if( segR < segTree[now].l || segTree[now].r < segL ) return ;
	if( segL <= segTree[now].l && segTree[now].r <= segR ) { cover( now, val ); return ; }
	if( isLeaf( now ) ) return ; normalize( now );
	update( now << 1, segL, segR, val ), update( now << 1 | 1, segL, segR, val );
}

int query( const int now, const int indx )
{
	if( indx < segTree[now].l || segTree[now].r < indx ) return INF;
	if( indx <= segTree[now].l && segTree[now].r <= indx ) return segTree[now].mn;
	if( isLeaf( now ) ) return INF; normalize( now );
	return MIN( query( now << 1, indx ), query( now << 1 | 1, indx ) );
}

int main()
{
	read( N ), read( S ), read( L );
	for( int i = 1 ; i <= N ; i ++ ) read( a[i] );
	build( 1, 0, N ), update( 1, 0, 0, 0 );
	h1 = h2 = 1, t1 = t2 = 0;
	for( int i = 0, r = 0 ; i <= N - L ; i ++ )
	{
		while( h1 <= t1 && deq1[h1] <= i ) h1 ++;
		while( h2 <= t2 && deq2[h2] <= i ) h2 ++;
		while( r < N && 
			 ( h1 > t1 || h2 > t2 || ( MAX( a[r + 1], a[deq2[h2]] ) - MIN( a[r + 1], a[deq1[h1]] ) ) <= S ) )
		{
			r ++;
			while( h1 <= t1 && a[deq1[t1]] >= a[r] ) t1 --; deq1[++ t1] = r;
			while( h2 <= t2 && a[deq2[t2]] <= a[r] ) t2 --; deq2[++ t2] = r;
		}
		int f = query( 1, i );
		update( 1, i + L, r, f + 1 );
	}
	int res = query( 1, N );
	write( res == INF ? -1 : res ), putchar( '\n' );
	return 0;
}
```

---

## 作者：hnczy (赞：0)

$dp_i$ 表示 $1\sim i$ 的最小分段数

$dp_i = \min_{1}^{i-l}(dp_j)+1 \wedge \max(j+1,i)-\min(j+1,i)\le S $

应该是用一个 $O(n^2)$ 的暴力算法即可。

而我们发现一个区间如果去掉左端点，那么最大值不会上升只会减少，而最小值只会上升不会减少。所以可以发现最大值减最小值是一个单调递减的数。

可以维护一个变量，直接记一个左端点。

然后直接用一个线段树维护一个区间小值即可。

我比较懒，直接用两个线段树维护了。

```c++
#include<bits/stdc++.h>
#define ls p<<1
#define rs p<<1|1
using namespace std;
const int N=1E5+5;
int n,s,l,a[N];
struct SEG {
	struct node {
		int mx,mi;
		node operator +(const node &a)const {
			return {max(mx,a.mx),min(mi,a.mi )};
		}
		node operator +(const int &a)const {
			return {mx+a,mi+a};
		}
		int delta() {
			return mx-mi;
		}
	} c[N<<2];
	void pushup(int p) {
		c[p]=c[ls]+c[rs];
	}
	void build(int p,int l,int r) {
		if(l==r) return void (c[p]={a[l],a[l]});
		int mid=l+r>>1;
		build(ls,l,mid);
		build(rs,mid+1,r);
		pushup(p);
	}
	void change(int p,int l,int r,int x,int v) {
		if(l==r) return void (c[p]={v,v});
		int mid=l+r>>1;
		if(x<=mid)change(ls,l,mid,x,v);
		else change(rs,mid+1,r,x,v);
		pushup(p);
	}
	node query(int p,int l,int r,int L,int R) {
		if(L<=l&&r<=R)return c[p];
		int mid=l+r>>1;
		if(L<=mid&&R>mid)return query(ls,l,mid,L,R)+query(rs,mid+1,r,L,R);
		if(R>mid)return query(rs,mid+1,r,L,R);
		if(L<=mid)return query(ls,l,mid,L,R);
	}
} seg1,seg2;
int main() {
	scanf("%d%d%d",&n,&s,&l);
	for(int i=1; i<=n; i++)
		scanf("%d",&a[i]);
	seg1.build(1,1,n);
	int st=1;
	for(int i=1;i<l;i++)
		seg2.change(1,0,n,i,1e9);
	for(int i=l; i<=n; i++) {
		while(seg1.query(1,1,n,st,i).delta()>s)st++;
		if(st<=i-l+1)seg2.change(1,0,n,i,seg2.query(1,0,n,st-1,i-l).mi+1);
		else seg2.change(1,0,n,i,1e9);
	}
	int ans=seg2.query(1,0,n,n,n).mi;
	if(ans>=1e9)puts("-1");
	else printf("%d",ans);
	return 0;
}

---

## 作者：内拉组里 (赞：0)

这题也可以用单调队列优化与单调栈 + 线段树优化写，

但是都太烧脑了~~其实是我懒~~，所以本文介绍一种在线段树上二分优化 dp 的作法。

# Thoughts :

> 首先要写出最最最最暴力的原始 dp 方程：
>
> 令 $ dp[i] $ 表示最少能把 $ [1,i] $ 的数字分成多少片段。
>
> 转移 $ dp[i] = \min\{dp[j] + 1\} \qquad (\max_{[j + 1,i]} - \min_{[j + 1,i]} \le s) $ 
>
> 简单的写就是第一层 $ \Theta (N) $ 枚举 $ i $，第二层 $ \Theta (N) $ 枚举 $ j $，第三层 $ \Theta (N) $ 计算最大值。
>
> 共计 $ \Theta (N^3) $，非常暴力。

# Optimizations :

> - 对于第三层循环，很容易想到用一些数据结构进行优化（如倍增表，单调队列等），
>
>   这里为了统一起见采用线段树维护，优化到 $ \Theta (\log{N}) $。
>
> - 对于第二层循环，当右端点一定时，随着区间长度的增大，区间内最大值单调不降，最小值单调不升。
>
>   于是考虑二分左端点，优化到了 $ \Theta (\log{N}) $。

# Details :

> - 下标从 0 开始，因为 $ dp[0] = 0 $。
> - check 的区间长度 $ \ge l $。
> - 二分时可能会出现 $ i \lt 0 $ 的情况，应该特判。
> - 输入 $ a $ 数组时要用 scanf，不然会~~稳稳 T 飞~~。

# Analyses :

> 总时间复杂度 $ \Theta (N \log^2{N}) $。
>
> 总空间复杂度 $ \Theta (N) $。

# Code :

```cpp
#include	<iostream>
using namespace std;
constexpr int inf = 0x3f3f3f3f;
constexpr int maxn = 1e5+4;

int n, s, l;
namespace SegTree
{
	int mx[maxn << 2];
	int mn[maxn << 2];
	int dp[maxn << 2];
	
	void pushup (int rt)
	{
		mx[rt] = max (mx[rt << 1], mx[rt << 1 | 1]);
		mn[rt] = min (mn[rt << 1], mn[rt << 1 | 1]);
		dp[rt] = min (dp[rt << 1], dp[rt << 1 | 1]);
	}
	
	void build (int l, int r, int rt)
	{
		if (l == r)
		{
			if (l)
			{
				scanf ("%d", &mx[rt]);
				mn[rt] = mx[rt];
				dp[rt] = inf;
			}
			else
			{
				mx[rt] = -inf;
				mn[rt] = inf;
			}
			return ;
		}
		int mid = (l + r) >> 1;
		build (l, mid, rt << 1);
		build (mid + 1, r, rt << 1 | 1);
		pushup (rt);
	}
	
	void update (int L, int R, int c, int l, int r, int rt)
	{
		if (L <= l && r <= R)
		{
			dp[rt] = c;
			return ;
		}
		int mid = (l + r) >> 1;
		if (L <= mid) update (L, R, c, l, mid, rt << 1);
		if (mid < R) update (L, R, c, mid + 1, r, rt << 1 | 1);
		pushup (rt);
	}
	
	int querymx (int L, int R, int l, int r, int rt)
	{
		if (L <= l && r <= R) return mx[rt];
		int ans = -inf;
		int mid = (l + r) >> 1;
		if (L <= mid) ans = max (ans, querymx (L, R, l, mid, rt << 1));
		if (mid < R) ans = max (ans, querymx (L, R, mid + 1, r, rt << 1 | 1));
		return ans;
	}
	
	int querymn (int L, int R, int l, int r, int rt)
	{
		if (L <= l && r <= R) return mn[rt];
		int ans = inf;
		int mid = (l + r) >> 1;
		if (L <= mid) ans = min (ans, querymn (L, R, l, mid, rt << 1));
		if (mid < R) ans = min (ans, querymn (L, R, mid + 1, r, rt << 1 | 1));
		return ans;
	}
	
	int querydp (int L, int R, int l, int r, int rt)
	{
		if (L <= l && r <= R) return dp[rt];
		int ans = inf;
		int mid = (l + r) >> 1;
		if (L <= mid) ans = min (ans, querydp (L, R, l, mid, rt << 1));
		if (mid < R) ans = min (ans, querydp (L, R, mid + 1, r, rt << 1 | 1));
		return ans;
	}
	
	void print (int l, int r, int rt)
	{
		if (l == r)
		{
			if (!l) return ;
			if (dp[rt] >= inf) cout << '-' << ' ';
			else cout << dp[rt] << ' ';
			return ;
		}
		int mid = (l + r) >> 1;
		print (l, mid, rt << 1);
		print (mid + 1, r, rt << 1 | 1);
	}
}
using namespace SegTree;

signed main (void)
{
	cin >> n >> s >> l;
	build (0, n, 1);
	for (int i = 1; i <= n; i++)
	{
		int l = 0;
		int r = i - ::l;
		int flag = 0;
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			if (querymx (mid + 1, i, 0, n, 1) - querymn (mid + 1, i, 0, n, 1) <= s)
			{
				r = mid - 1;
				flag = 1;
			}
			else l = mid + 1;
		}
		if (!flag) continue;
		int ans = querydp (r + 1, i - ::l, 0, n, 1) + 1;
		update (i, i, ans, 0, n, 1);
	}
//	print (0, n, 1);
//	return 0;
	if (querydp (n, n, 0, n, 1) > n) cout << -1 << endl;
	else cout << querydp (n, n, 0, n, 1) << endl;
	return 0;
}
```

---

## 作者：ivyjiao (赞：0)

暴力 dp 是 $O(n^3)$ 的，直接似了。

考虑到由于极差越往左不会减小，所以每次的 dp 区间一定是 $[c_i,i]$，其中 $c_i\leq c_{i+1}$，若 $i-l\geq c_i$ 则无效。其中要段数最少，选择 $c_i$ 明显最优，优化到 $O(n^2)$。

剩下的极差部分显然能单调队列优化维护最大值和最小值，时间复杂度 $O(n)$，可以通过。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+1;
int n,s,l,c,a[N],dp[N],q1[N],q2[N],h1,t1,h2,t2;
int query(){
    while(h1<=t1&&q1[h1]<=c) h1++;
    while(h2<=t2&&q2[h2]<=c) h2++;
    return a[q2[h2]]-a[q1[h1]];
}
int main(){
    cin>>n>>s>>l;
    for(int i=1;i<=n;i++) cin>>a[i];
    memset(dp,0x3f,sizeof dp);
    dp[0]=0;
    for(int i=1;i<=n;i++){
        while(h1<=t1&&a[q1[t1]]>=a[i]) t1--;
        q1[++t1]=i;
        while(h2<=t2&&a[q2[t2]]<=a[i]) t2--;
        q2[++t2]=i;
        if(i>=l){
            while(i-c>=l&&(query()>s||dp[c]==0x3f3f3f3f)) c++;
            if(i-c>=l) dp[i]=dp[c]+1;
        }
    }
    cout<<(dp[n]==0x3f3f3f3f? -1:dp[n]);
}
```

---

