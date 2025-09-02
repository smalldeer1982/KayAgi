# [ABC332G] Not Too Many Balls

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc332/tasks/abc332_g

いくつかのボールがあります。 各ボールは色 $ 1 $ 、色 $ 2 $ 、$ \ldots $ 、色 $ N $ のうちのいずれかであり、 $ i\ =\ 1,\ 2,\ \ldots,\ N $ について、色 $ i $ のボールは全部で $ A_i $ 個あります。

また、$ M $ 個の箱があります。 $ j\ =\ 1,\ 2,\ \ldots,\ M $ について、$ j $ 番目の箱には合計で $ B_j $ 個までのボールを入れることができます。

ただし、$ 1\ \leq\ i\ \leq\ N $ と $ 1\ \leq\ j\ \leq\ M $ を満たすすべての整数の組 $ (i,\ j) $ について、 色 $ i $ のボールを $ j $ 番目の箱に入れる個数は $ (i\ \times\ j) $ 個以下でなければなりません。

$ M $ 個の箱の中に入れることができるボールの合計個数の最大値を出力してください。

## 说明/提示

### 制約

- 入力される値は全て整数
- $ 1\ \leq\ N\ \leq\ 500 $
- $ 1\ \leq\ M\ \leq\ 5\ \times\ 10^5 $
- $ 0\ \leq\ A_i,\ B_i\ \leq\ 10^{12} $
 
### Sample Explanation 1

下記の通りにボールを箱に入れることで、問題文中の条件を満たした上で合計 $ 14 $ 個のボールを箱に入れることができます。 - 色 $ 1 $ のボールを、$ 1 $ 番目の箱に $ 1 $ 個、$ 2 $ 番目の箱に $ 1 $ 個、$ 3 $ 番目の箱に $ 3 $ 個入れる。 - 色 $ 2 $ のボールを、$ 1 $ 番目の箱に $ 2 $ 個、$ 2 $ 番目の箱に $ 2 $ 個、$ 3 $ 番目の箱に $ 5 $ 個入れる。

## 样例 #1

### 输入

```
2 3
8 10
4 3 8```

### 输出

```
14```

## 样例 #2

### 输入

```
1 1
1000000000000
0```

### 输出

```
0```

## 样例 #3

### 输入

```
10 12
59 168 130 414 187 236 330 422 31 407
495 218 351 105 351 414 198 230 345 297 489 212```

### 输出

```
2270```

# 题解

## 作者：Wuyanru (赞：5)

[题目链接](https://www.luogu.com.cn/problem/AT_abc332_g)。

## 题意

现在有 $ n $ 种球和 $ m $ 个盒子，第 $ i $ 种球有 $ a_i $ 个，第 $ j $ 个箱子里最多放 $ b_j $ 个球。

除此之外，第 $ j $ 个箱子里最多放 $ i\times j $ 个第 $ i $ 种球。

求最多能放多少个球。

$ 1\le n\le 500 $。

$ 1\le m\le 5\times 10^5 $。

$ 1\le a_i,b_i\le 10^{12} $。

## 题解

这个问题看上去就可以流，但是显然会 T。

我们不妨把这个图建出来。

这张图共有 $ n+m+2 $ 个点，分别为源点 $ s $，汇点 $ t $，代表第 $ i $ 种小球的点 $ x_i $，以及代表第 $ j $ 个箱子的点 $ y_j $。

边也分为三种：

1. 边 $ s\to x_i $，流量为 $ a_i $；
2. 边 $ y_j\to t $，流量为 $ b_j $；
3. 边 $ x_i\to y_j $，流量为 $ i\times j $。

~~显然，直接跑是不行的。~~

众所周知，最大流与最小割相等，那么存不存在什么快速的方法，求出这张图的最小割呢？

为方便使用公式，我们首先定义 $ X\gets \{x_1,x_2,\dots,x_n\} $ 为左部点的集合，$ Y\gets \{y_1,y_2,\dots,y_m\} $ 为右部点的集合。

考虑枚举 $ X $ 中与源点 $ s $ 联通的点集 $ P $，枚举 $ Y $ 中与汇点 $ t $ 联通的点集 $ Q $，那么对于上述的三种边：

1. 对于边 $ s\to x_i $，若 $ x_i\notin P $，则需要割掉这条边，流量为 $ a_i $；
2. 对于边 $ y_j\to t $，若 $ t_i\notin Q $，则需要割掉这条边，流量为 $ b_j $；
3. 对于边 $ x_i\to y_j $，若 $ x_i\in P\wedge y_j\in Q $，则需要割掉这条边，流量为 $ i\times j $。

那么我们就可以将最小割的值用一个式子表示出来！

$$
\min_{P\subseteq X}\min_{Q\subseteq Y}\left(\sum_{x_i\notin P}a_i+\sum_{y_j\notin Q}b_j+\sum_{x_i\in P}\sum_{y_j\in Q}ij\right)
$$

不太好算，考虑枚举 $ k=\sum\limits_{x_i\in P}i $ 的值。

$$
\begin{aligned}
&\min_{P\subseteq X}\min_{Q\subseteq Y}\left(\sum_{x_i\notin P}a_i+\sum_{y_j\notin Q}b_j+\sum_{x_i\in P}\sum_{y_j\in Q}ij\right)\\
=&\min_{P\subseteq X}\min_{Q\subseteq Y}\left(\sum_{x_i\notin P}a_i+\sum_{y_j\notin Q}b_j+\sum_{x_i\in P}i\sum_{y_j\in Q}j\right)\\
=&\min_{k=0}^{\frac{n(n+1)}{2}}\min_{P\subseteq X\wedge \sum_{x_i\in P}i=k}\min_{Q\subseteq Y}\left(\sum_{x_i\notin P}a_i+\sum_{y_j\notin Q}b_j+\sum_{x_i\in P}i\sum_{y_j\in Q}j\right)\\
=&\min_{k=0}^{\frac{n(n+1)}{2}}\min_{P\subseteq X\wedge \sum_{x_i\in P}i=k}\min_{Q\subseteq Y}\left(\sum_{x_i\notin P}a_i+\sum_{y_j\notin Q}b_j+\sum_{y_j\in Q}kj\right)\\
=&\min_{k=0}^{\frac{n(n+1)}{2}}\min_{P\subseteq X\wedge \sum_{x_i\in P}i=k}\left(\sum_{x_i\notin P}a_i+\min_{Q\subseteq Y}\left(\sum_{y_j\notin Q}b_j+\sum_{y_j\in Q}kj\right)\right)\\
=&\min_{k=0}^{\frac{n(n+1)}{2}}\min_{P\subseteq X\wedge \sum_{x_i\in P}i=k}\left(\sum_{x_i\notin P}a_i+\sum_{j=1}^m\min(b_j,kj)\right)\\
\end{aligned}
$$

考虑枚举 $ k $ 的值，那么前面关于 $ a $ 的部分可以使用 dp 计算。

后面的值，对于每一个 $ j $ 来说都是一个分段函数（前一段为 $ y=kj $，后一段为 $ y=b_j $），也是容易计算的。

时间复杂度 $ O(n^3+nm) $。

## 代码

```c++
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f3f3f3f3fll
using namespace std;
using ll=long long;
inline int read()
{
    int s=0,w=1;char ch;
    while((ch=getchar())>'9'||ch<'0') if(ch=='-') w=-1;
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
inline ll lread()
{
    ll s=0,w=1;char ch;
    while((ch=getchar())>'9'||ch<'0') if(ch=='-') w=-1;
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
ll prek[150001];
ll preb[150001];
ll dp[150001];
ll b[500001];
ll a[501];
int n,m,Lim;
int main()
{
    n=read(),m=read(),Lim=(ll)n*(n+1)/2;
    memset(dp,0x3f,sizeof(dp)),dp[Lim]=0;
    for(int i=1;i<=n;i++)
    {
        a[i]=lread();
        for(int j=0;j+i<=Lim;j++) dp[j]=min(dp[j],dp[j+i]+a[i]);
    }
    for(int j=1;j<=m;j++)
    {
        b[j]=lread();ll s=b[j]/j;
        prek[1]+=j;
        if(s<Lim) prek[s+1]-=j,preb[s+1]+=b[j];
    }
    ll ans=inf;
    for(int i=0;i<=Lim;i++)
    {
        prek[i]+=prek[i-1],preb[i]+=preb[i-1];
        ans=min(ans,dp[i]+prek[i]*i+preb[i]);
    }
    printf("%lld\n",ans);
    return 0;
}
```

感谢观看！

---

## 作者：Sharpsmile (赞：2)



有 $n\leq 500$ 种球，第 $i$ 种有 $a_i$ 个。有 $i$ 个盒子，第 $i$ 个盒子最多放 $b_i$ 个球，除此之外，最多放 $ij$ 个 $j$ 颜色的球。求最多放多少球。

首先有一个显然的最大流。然后因为最大流等于最小割，我们可以尝试通过 $dp$ 求出最小割。首先考虑如果左边的割掉的边集确定了，那么怎么求剩下部分的最小割。会发现就是 $\sum\min(b_j,j\sum\limits_{i\in S}i)$，其中 $S$ 为没有被割的点。

然后会发现这玩意只和 $\sum\limits_{i\in S}i$ 有关，令 $w_p$ 表示 $\sum\limits_{i\in S}i=p$ 的时候上面那坨式子的和。令 $f_{i,j}$ 表示考虑前 $i$ 个点，没被割的点的和为 $j$ 的最小代价。那么答案就是 $\min f_{n,i}+w_i$。$f$ 易得。$w$ 暴力维护的复杂度是 $O(n^2m)$ 的。容易发现上面那坨式子中，$\min$ 两边其中一个单调，另一个是常量，所以存在恰一个位置这里取的方案发生转变，把右边点的每个更改方案的位置记录下来，维护得出 $w$。可以在 $O(n^2+m)$ 的复杂度内解决。

总复杂度 $O(n^3+m)$。


---

## 作者：OIer_Eternity (赞：1)

设 $x_i,y_j$ 分别表示第 $i$ 个球和第 $j$ 个盒子，$X,Y$ 分别表示与源点、汇点直接相连的点的集合。

则最小割可以用如下公式表示：
$$
\min\Big\{\sum_{i\not\in X}a_i+\sum_{i\in X,j\in Y}i\cdot j+\sum_{j\not\in Y}b_j\Big\}
$$
令 $S=\sum\limits_{i\in X}i$，则上式可以转化为：
$$
\min\Big\{\sum_{i\not\in X}a_i+\sum_{j\in Y}S\cdot j+\sum_{j\not\in Y}b_j\Big\}=\min\sum_{i\not\in X}a_i+\sum_j\min\{S\cdot j,b_j\}
$$
则设 $f(S)=\min\sum\limits_{i\not\in X}a_i$，可以用动态规划 $O(nS)=O(n^3)$ 计算得到。

即 $\sum\limits_{i\in X}i$ 确定时，需要取到最大的 $\sum\limits_{i\in X}a_i$，可以通过背包处理，体积为 $i$，价值 $a_i$。

同时，设 $g(S)=\sum\limits_j\min\{S\cdot j,b_j\}$，可以发现对于每个 $j$ 可以算出 $S\cdot j$ 和 $b_j$ 大小关系互换的分界点 $S_0=\lfloor\dfrac{b_j}j\rfloor$，达到分界点转换贡献即可。

因此，只需要枚举 $S$，依次计算 $f(S)+g(S)$ 即可，复杂度 $O(n^3+m)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,V;
long long a[505],b[500005],sum,f[130005],Min=1e18;
vector<int> pos[130005];
int main(){
    scanf("%d%d",&n,&m),V=n*(n+1)/2;
    for (int i=1;i<=n;i++) scanf("%lld",&a[i]),sum+=a[i];
    for (int i=1;i<=m;i++){
        scanf("%lld",&b[i]);
        if (b[i]/i<V) pos[b[i]/i+1].push_back(i);
    }
    for (int i=1;i<=n;i++) for (int S=V;S>=i;S--) f[S]=max(f[S],f[S-i]+a[i]);
    long long s1=1ll*m*(m+1)/2,s2=0; // s1=∑j s2=∑b_j
    for (int S=0;S<=V;S++){ // S为与源点直接相连的点的下标和
        for (int j:pos[S]) s1-=j,s2+=b[j];
        Min=min(Min,sum-f[S]+s1*S+s2);
    }
    printf("%lld\n",Min);
    return 0;
}
```

---

## 作者：Jerrywang09 (赞：1)

一道综合性非常强的好题。

首先，本题的基本模型是一个非常裸的最大流：

原点向颜色 $i$ 连容量 $a_i$ 的边；

颜色 $i$ 向盒子 $j$ 连容量 $i\cdot j$ 的边；

盒子 $j$ 向汇点连容量 $b_j$ 的边。

但暴力连边并跑最大流会超时。

考虑到无法优化建边，将最大流转化为最小割，尝试解决。

记集合 $A=[1,n],B=[1,m]$，如果割掉 $(s,i)$ 边，记 $i$ 在集合 $S$ 中；割掉 $(j,t)$ 边，记 $j$ 在集合 $T$ 中。最小割就是：
$$
\min(\sum_{i\in S}a_i+\sum_{i\in A-S,j\in B-T}i\cdot j+\sum_{j\in T}b_j)
$$
中间一项的意思是，如果 $(i,j)$ 边左连原点，右连汇点，就需要割断。

看到 $n$ 很小，考虑枚举 $k$，感性理解为左边不割的下标和。记：
$$
k=\sum_{i\in A-S}i
$$
原式改写为：
$$
\min(\sum_{i\in S}a_i+\sum_{j\in B-T}k\cdot j+\sum_{j\in T}b_j)
$$
再想一下，右边两项可以理解为，对每个 $j$ 可以自由地选择割掉容量为 $b_j$ 的边或容量为 $k\cdot j$ 的边。
$$
\min(\sum_{i\in S}a_i+\sum_{j\in B}\min(k\cdot j,b_j))
$$
外层枚举着 $k$，贪心地对每个 $j$ 自由选择，至于左边那一项，可以预处理 DP。

DP 的具体思路：

> 记 $f(i,j)$ 表示到下标 $i$ 为止，选择了若干 $i'$ 不割掉 $(s,i')$ 边，$\sum i'=j$（$j$ 其实就是上文提到的 $k$），最小割。
> 
> 转移有：割 $(s,i)$，$f(i,j)=f(i-1,j)+a_i$；不割，$f(i,j)=f(i-1,j-i)$。

贪心的具体思路：

> 对每一个 $j$ 预处理 $b_j\le j\cdot k$ 的最小 $k$，也就是到达这个 $k$ 就开始选择 $b_j$。移项得 $k\ge b_j/j$，$k$ 的最小整数值即为 $b_j/j$ 上取整。按这个值排序。
>
> 一开始假设每个 $j$ 都选 $j\cdot k$。随着 $k$ 的增长，$j\cdot k$ 会逐步被 $b_j$ 替代掉，按照先前制定的顺序依次修改即可。

```cpp
// Title:  Not Too Many Balls
// Source: ABC332G
// Author: Jerrywang
#include <bits/stdc++.h>
#define F first
#define S second
#define pii pair<ll, int>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cout<<#x<<":"<<x<<endl;
const int N=505, M=500010;
using namespace std;
inline ll read()
{
    ll x=0, f=1;
    char c=getchar();
    while(!isdigit(c)) {if(c=='-') f=-1; c=getchar();}
    while(isdigit(c)) {x=(x<<3)+(x<<1)+c-'0'; c=getchar();}
    return x*f;
}

int n, m; ll a[N], b[M]; pii t[M];
ll f[N][N*N]; // a数组到i为止，不割掉的下标和为j，最小总和
int main()
{
    #ifdef Jerrywang
    freopen("in.txt", "r", stdin);
    #endif
    n=read(), m=read();
    rep(i, 1, n) a[i]=read();
    rep(i, 1, m) b[i]=read();
    rep(i, 1, n) rep(j, 0, n*n)
    {
        f[i][j]=f[i-1][j]+a[i];
        if(j>=i) f[i][j]=min(f[i][j], f[i-1][j-i]);
    }
    rep(i, 1, m) t[i]={(b[i]+i-1)/i, i}; // b[j]<=jk的最小k
    sort(t+1, t+m+1);
    int i=1;
    ll sum1=(ll)m*(m+1)/2, sum2=0, ans=LLONG_MAX;
    rep(k, 0, n*n)
    {
        while(i<=m && t[i].F==k)
        {
            sum1-=t[i].S; sum2+=b[t[i].S];
            i++;
        }
        ans=min(ans, f[n][k]+k*sum1+sum2);
    }
    printf("%lld", ans);
    
    return 0;
}
```

---

## 作者：2008verser (赞：1)

> 第 $i$ 种球有 $a_i$ 个，共 $n$ 种。
>
> 第 $i$ 种箱子最多共装 $b_i$ 个球。共 $m$ 种。
>
> 第 $i$ 种球在第 $j$ 种箱子里至多放 $ij$ 个。
>
> 问所有箱子放的球数最多是多少。
>
> $1\leq n\leq 500,1\leq m\leq 5\times 10^5,0\leq a_i,b_i\leq 1\times 10^{12}$。

很容易建出网络流模型。从上至下依次有 $1,n,m,1$ 个点。但是图实在太大了。

考虑求最小割。那就是要把上下共 $n+m$ 个点划分为两类。

将它表示出来。设上下的全集分别为 $X=\{1,2,...,n\},Y=\{1,2,...,m\}$。

上下分别选了 $P\subseteq X,Q\subseteq Y$ 归于源点集合。（以下所有式子所有求和条件略去这两个）
$$
\sum_{i\in X/P}a_i+\sum_{i\in P}i\sum_{j\in Y/Q}j+\sum_{i\in Q}b_i
$$
这个东西的最小值不好求。因为既要考虑 $P$ 也要考虑 $Q$。

观察到数据范围很小，考虑枚举一点东西来把问题划分成独立的两个问题。枚举中间项左侧的 $k=\sum_{i\in X}i$。

有 $0\leq k\leq n(n+1)/2$。

那么对最左项的限制就是选一些求和为 $k$ 的 $i$，作为 $P$。剩下的 $a_i$ 加起来作为这一项。

写在求和的条件上就是：
$$
\sum_{i\in X/P,k=\sum_{i\in X/P} i}a_i+k\sum_{i\in Y/Q}i+\sum_{i\in Q}b_i
$$
下面一行要么纳入源点集合，在第三项计算。否则在第二项计算。

发现此时下面一行对于是否纳入源点集合不受约束。贪心地让它取较小的，使得整个式子最小。
$$
\sum_{i\in X/P,k=\sum_{i\in X/P} i}a_i+\sum_{1\leq i\leq m}\min(ik,b_i)
$$
那么可以分别求出左侧和右侧对于每个 $k$ 的最小值，相加。

左侧可以用 $O(n^3)$ 的 DP 算出，右侧可以发挥智慧写出 $O(n^2+m)$。这部分比较简单。

总时间复杂度为 $O(n^3+m)$。

```c++
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define rg register
#define ld long double
#define ull unsigned long long
#define gc getchar
#define pc putchar
#define pob pop_back
#define ump unordered_map
#define vi vector<int>
#define vl vector<ll>
#define fo(i,l,r) for(rg int i=(l);i<=(r);++i)
using namespace std;
inline int re() {
	rg int x=0,p=0;rg char c=getchar();
	while(c<'0'||c>'9') (!p)?(p=c=='-'):(p=p),c=getchar();
	while('0'<=c&&c<='9') (x*=10)+=c-48,c=getchar();
	if(p) x=-x;
	return x;
}
inline ll rel() {
	rg ll x=0;rg int p=0;rg char c=getchar();
	while(c<'0'||c>'9') (!p)?(p=c=='-'):(p=p),c=getchar();
	while('0'<=c&&c<='9') (x*=10)+=c-48,c=getchar();
	if(p) x=-x;
	return x;
}
inline void wt(rg int x) { if(x>9) wt(x/10);pc(x%10+48); }
inline void wtl(rg ll x) { if(x>9) wtl(x/10);pc(x%10+48); }

const int N=505;
const int M=5e5+5;
const ll inf=1e18;
int n,m;
ll a[N],b[M],f[N*(N+1)/2],ans=inf;
ll minl(ll a,ll b) { return a<b?a:b; }
struct pr { ll t;int i; }c[M];
bool cmp_by_t(pr a,pr b) { return a.t<b.t; }
int main() {
//	freopen(".in","r",stdin),freopen(".out","w",stdout);
	n=re(),m=re();
	fo(i,1,n) {
		a[i]=rel();
	}
	fo(i,1,m) {
		b[i]=rel();
	}
	vector<vl>f(n+1,vl(n*(n+1)/2+1,inf));
	int sum=0;
	f[0][0]=0;
	fo(i,0,n-1) {
		for(int j=sum;j>=0;j--) {
			f[i+1][j+i+1]=minl(f[i+1][j+i+1],f[i][j]);
			f[i+1][j]=minl(f[i+1][j],f[i][j]+a[i+1]);
		}
		sum+=i+1;
	}
	ll s1=0,s2=0,si=0;
	fo(i,1,m) {
		si+=i;
		c[i].t=b[i]/i;
		c[i].i=i;
//		printf("%d : %d\n",i,c[i].t);
	}
	sort(c+1,c+m+1,cmp_by_t);
	int z=1;
	fo(k,0,n*(n+1)/2) {
//		printf("%d : %lld %lld %lld\n",k,s1,s2,f[n][k]);
		ans=minl(ans,f[n][k]+s1+s2);
		while(z<=m&&c[z].t==k) {
			s1-=1ll*k*c[z].i;
			s2+=b[c[z].i];
			si-=c[z].i;
			z++;
		}
		s1+=si;
	}
	wtl(ans);
}
```

---

## 作者：User_Unauthorized (赞：1)

可以转化为最大流模型，设节点 $x_i$ 代表第 $i$ 种球，$y_j$ 代表第 $j$ 个盒子。考虑如下建边方案：

- $S \rightarrow x_i$，容量为 $A_i$
- $x_i \rightarrow y_j$，容量为 $i \times k$
- $y_j \rightarrow T$，容量为 $B_j$

可以发现该网络的最大流即为答案，但是由于边数是 $\mathcal{O}(NM)$ 级别的，直接求最大流会超时。根据最大流最小割定理，若我们可以求出该网络的最小割，那么我们也可以获得答案，下面考虑如何求出最小割。

首先考虑如何表示出最小割的值，设点集 $X = \left\{x_1, x_2, \cdots, x_N\right\}, Y = \left\{x_1, x_2, \cdots, x_N\right\}$，$P$ 表示最小割方案中 $X$ 中与 $S$ 在同一连通块内的点集，$Q$ 表示最小割方案中 $Y$ 中与 $S$ 在同一连通块内的点集。那么考虑三条边中都有哪些边被割掉，可以得出最小割的表达式：

$$\begin{aligned}
\mathbf{mincut} &= \min\limits_{P \subseteq X} \min\limits_{Q \subseteq Y} \left(\sum\limits_{x_i \in X \setminus P} A_i + \sum\limits_{x_i \in P}\sum\limits_{y_j \in Y \setminus Q} i \times j + \sum\limits_{y_j \in Q} B_j\right)
\end{aligned}$$

设 $k = \sum\limits_{x_i \in P} i, L = \dfrac{N\left(N + 1\right)}{2}$，通过枚举 $x$ 的值，我们有：

$$\begin{aligned}
\mathbf{mincut} &= \min\limits_{0 \le k \le L} \min\limits_{P \subseteq X \land \sum\limits_{x_i \in P} i = k}\min\limits_{Q \subseteq Y} \left(\sum\limits_{x_i \in X \setminus P} A_i + \sum\limits_{x_i \in P}\sum\limits_{y_j \in Y \setminus Q} i \times j + \sum\limits_{y_j \in Q} B_j\right)\\
&= \min\limits_{0 \le k \le L} \min\limits_{P \subseteq X \land \sum\limits_{x_i \in P} i = k}\min\limits_{Q \subseteq Y} \left(\sum\limits_{x_i \in X \setminus P} A_i + \sum\limits_{y_j \in Y \setminus Q} k \times j + \sum\limits_{y_j \in Q} B_j\right) \\
&= \min\limits_{0 \le k \le L} \min\limits_{P \subseteq X \land \sum\limits_{x_i \in P} i = k}\left(\sum\limits_{x_i \in X \setminus P} A_i + \sum\limits_{y_j \in Y} \min\left\{k \times j, B_j\right\}\right)
\end{aligned}$$

其中最后一步转化是因为 $Y$ 中的每个节点要么属于 $Q$，要么属于 $Y \setminus Q$，也就是其会产生 $k \times j$ 或 $B_j$ 的贡献，故可以直接取最小值。

对于上式的前半部分，即 $f_k = \min\limits_{P \subseteq X \land \sum\limits_{x_i \in P} i = k}\sum\limits_{x_i \in X \setminus P} A_i$。我们可以使用 $\tt{01}$ 背包在 $\mathcal{O}(NL)$ 的时间内求出对于 $0 \le k \le L$ 的所有 $f_k$ 的值。

对于上式的后半部分，即 $g_k = \sum\limits_{y_j \in Y} \min\left\{k \times j, B_j\right\}$。可以发现当 $k = 0$ 时，所有的节点均会从 $k \times j$ 来产生贡献，而由于 $k \times j$ 随 $k$ 的增长而单调递增，因此对于所有满足 $y_j \in Y$ 的 $j$，均存在一个 $k_0$ 使得当 $k \ge k_0$ 时，其会产生 $B_j$ 而不是 $k \times j$ 的贡献，所以有 $\forall k \ge k_0, B_j \le k \times j$，解得 $k_0 = \dfrac{B_j}{j}$。因此我们对于每个 $j$ 求出出其对应的 $k_0$ 后遍历 $0 \le k \le L$ 并求出 $g_k$ 即可。

最终答案即为 $\min\limits_{0 \le k \le L} f_k + g_{L - k}$。复杂度为 $\mathcal{O}(N^3 + M)$。

---

## 作者：Phartial (赞：1)

考虑以下网络流建模：

- 对第 $i$ 种球建点 $X_i$，对第 $j$ 个盒子建点 $Y_j$；
- 对第 $i$ 种球，连边 $(S,X_i,A_i)$；
- 对第 $j$ 个盒子，连边 $(Y_j,T,B_j)$；
- 对第 $i$ 种球与第 $j$ 个盒子，连边 $(X_i,Y_j,ij)$。

则 $S$ 到 $T$ 的最大流即为答案。显然过不去，考虑优化。

根据最大流最小割定理，我们可以将所求转化为 $S$ 到 $T$ 的最小割。枚举左边割掉的边与右边割掉的边，则答案为：

$$
\min_{P\subseteq X,Q\subseteq Y}\left\{\sum_{X_i\in P}A_i+\sum_{Y_i\in Q}B_i+\left(\sum_{X_i\not\in P}i\right)\left(\sum_{Y_j\not\in Q}j\right)\right\}
$$

考虑枚举 $k=\sum_{X_i\not\in P}i$，则有：

$$
\begin{aligned}
  &\min_{P\subseteq X,Q\subseteq Y}\left\{\sum_{X_i\in P}A_i+\sum_{Y_i\in Q}B_i+\left(\sum_{X_i\not\in P}i\right)\left(\sum_{Y_j\not\in Q}j\right)\right\}\\
  =&\min_{k}\min_{\substack{P\subseteq X\\ \sum_{X_i\not\in P}i=k}}\min_{Q\subseteq Y}\left\{\sum_{X_i\in P}A_i+\sum_{Y_i\in Q}B_i+k\sum_{Y_j\not\in Q}j\right\}\\
  =&\min_{k}\min_{\substack{P\subseteq X\\ \sum_{X_i\not\in P}i=k}}\left\{\sum_{X_i\in P}A_i+\min_{Q\subseteq Y}\left\{\sum_{Y_i\in Q}B_i+\sum_{Y_j\not\in Q}kj\right\}\right\}\\
  =&\min_{k}\min_{\substack{P\subseteq X\\ \sum_{X_i\not\in P}i=k}}\left\{\sum_{X_i\in P}A_i+\sum_{1\le i\le m}\min(B_i,ki)\right\}\\
  =&\min_{k}\left\{\min_{\substack{P\subseteq X\\ \sum_{X_i\not\in P}i=k}}\left\{\sum_{X_i\in P}A_i\right\}+\sum_{1\le i\le m}\min(B_i,ki)\right\}\\
\end{aligned}
$$

对于该式的前半部分，考虑设 $f_{i,k}=\displaystyle\min_{\substack{P\subseteq \{1,2,\cdots,i\}\\ \sum_{j\not\in P}j=k}}\left\{\sum_{i\in P}A_i\right\}$，由 $i$ 是否 $\in P$ 分类，则有转移方程 $f_{i,k}=\min(f_{i-1,k}+A_i,f_{i-1,k-i})$，我们可以在 $\mathcal{O}(N^3)$ 的时间复杂度内得到所有的 $f_{i,k}$，该式的前半部分即为 $f_{N,k}$。

对于该式的后半部分，我们可以将 $B_i$ 排序并从小到大枚举 $k$，则式子必然形如 $\displaystyle\left(\sum_{1\le i<p}B_i\right)+\left(\sum_{p\le i\le m}ki\right)$ 且 $p$ 单调不减，使用双指针即可做到 $\mathcal{O}(N^2+M)$。

总时间复杂度 $\mathcal{O}(N^3+M)$。

```cpp
#include <iostream>
#include <algorithm>

using namespace std;
using LL = long long;

const int kN = 501, kM = 5e5 + 1;
const LL kI = 1e18;

int n, m, d[kM];
LL a[kN], b[kM], f[kN][kN * kN], ans = kI;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= m; ++i) {
    cin >> b[i];
    d[i] = i;
  }
  for (int i = 1; i <= n * n; ++i) {
    f[0][i] = kI;
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= n * n; ++j) {
      f[i][j] = min(f[i - 1][j] + a[i], j >= i ? f[i - 1][j - i] : kI);
    }
  }
  sort(d + 1, d + m + 1, [](int i, int j) { return b[i] / i < b[j] / j; });
  LL s = 0, ds = m * (m + 1LL) / 2;
  for (int k = 0, p = 1; k <= n * n; ++k) {
    for (; p <= m && 1LL * k * d[p] >= b[d[p]]; ++p) {
      s += b[d[p]] - k * d[p], ds -= d[p];
    }
    ans = min(ans, f[n][k] + s);
    s += ds;
  }
  cout << ans;
  return 0;
}
```


---

## 作者：233L (赞：1)

首先有一个显然的最大流模型，但是边数是 $O(NM)$ 的，直接爆了。这个模型很特殊，考虑模拟它。

**先转化为求最小割**。记第 $i$ 种颜色的球为 $x_i$，$X=\{x_i\}$；第 $i$ 个箱子为 $y_i$，$Y=\{y_i\}$。然后在最小割中，与 $S$ 联通的部分分别记作 $P \subseteq X,Q \subseteq Y$。那么最小割就为
$$
\sum_{x_i\in X/P}a_i+\sum_{x_i\in P}i\sum_{y_j\in Y/Q}j+\sum_{y_i\in Q}b_i
$$
也就是我们要选择 $P,Q$，最小化上式。观察数据范围，$N$ 比较小，$\sum_{x_i\in P}i$ 也比较小，不妨钦定 $\sum_{x_i\in P}i=k$，那么式子变成
$$
\sum_{x_i\in X/P}a_i+k\sum_{y_j\in Y/Q}j+\sum_{y_i\in Q}b_i
$$
这个时候就很明显了，后半部分可以快速算，并且只与 $k$ 有关
$$
\sum_{x_i\in X/P}a_i+\sum_{y_i\in Y}\min(ik,b_i)
$$
于是对于每个 $k\in[1,\frac{n(n+1)}{2}]$，预处理出 $f_k=\sum_{y_i\in Y}\min(ik,b_i)$。显然对于每个 $i$，随着 $k$ 的增加，贡献分为前后两部分，$ik<b_i$ 和 $ik\ge b_i$，分界点在 $x=\left \lfloor \frac{b_i}{i} \right \rfloor$。
$$
1i,2i,3i,\dots xi,b_i,b_i,b_i,\dots,b_i
$$
差分一下
$$
i,i,i,\dots i,b_i-xi,0,0,\dots,0
$$
再差分一下
$$
i,0,0,\dots 0,b_i-(x+1)i,xi-b_i,0,\dots,0
$$


可以 $O(1)$ 修改 **2 次差分**数组，最后再前缀和回来，时间复杂度 $O(M+N^2)$。

然后预处理出前半部分
$$
g_k=\min_{P\in X,\sum_{i\in P}=k}\sum_{x_i\in X/P}a_i
$$
直接背包，时间复杂度 $O(N^3)$。

答案就是 $\min_k f_k+g_k$。

---

## 作者：Otomachi_Una_ (赞：0)

显然的最大流。正着不好做，考虑转最小割。

即选择一些左部点，右部点割掉。没有割掉的就要把中间链接的边割掉。

形式化地，$S\subset[n],T\subset[m]$，最小化 $\sum_{i\not\in S}a_i+\sum_{j\not \in T}b_j+(\sum_{i\in S}i)(\sum_{j\in T}j)$，

$n$ 很小。考虑直接枚举 $\sum_{i\in S}i$，通过背包算出 $\min \sum_{i\not\in S}a_i$。然后最小值就相当于在 $\sum_{i=1}^m\min(b_i,i\sum_{j\in S}j)$。前缀和优化即可。

---

## 作者：Filberte (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT_abc332_g)

## 思路

有一个较为简单的网络流做法。设立源点 $s$，汇点 $t$，$n$ 个左部点 $x_1 \sim x_n$ 表示 $n$ 种球，$m$ 个右部点 $y_1 \sim y_m$ 表示 $m$ 个盒子。进行如下连边：

- $\forall i\in[1,n]$ ，由 $s$ 向 $x_i$ 连接一条容量限制为 $a_i$ 的边。
- $\forall i\in[1,m]$，由 $y_i$ 向 $t$ 连接一条容量限制为 $b_i$ 的边。
- $\forall i\in[1,n],j\in[1,m]$，由 $i$ 向 $j$ 连接一条容量限制为 $ij$ 的边。

此图上的最大流即为答案。

但此构图的点数和边数都远远超出了可接受范围，因为最大流等于最小割，尝试求解此图中的最小割。

令集合 $X = \{x_1,x_2\dots x_n\}$，$Y = \{y_1,y_2\dots,y_m\}$。考虑一个合法割中源点能走到的 $X$ 集合中所有点构成的集合记为 $s$，同理把 $Y$ 集合中能走到汇点的所有点构成的集合记为 $t$，我们需要求出两个合法集合 $s$ 和 $t$，使得割掉的边权和最小，开始简化式子：


$$
\begin{aligned}
&\min_{s\in X \land t\in Y} (\sum\limits_{x_i \not\in s} a_i +  \sum\limits_{y_i \not\in t} b_i + \sum\limits_{x_i \in s \land y_j \in t} ij)\\
&= \min_{s\in X} \min_{ t\in Y} (\sum\limits_{x_i \not\in s} a_i +  \sum\limits_{y_i \not\in t} b_i + \sum\limits_{x_i \in s} i \sum\limits_{y_j \in t}j)\\
&= \min_{k = 0}^{\frac{n(n+1)}{2}}\min_{s\in X \land \sum\limits_{x_i \in S}a_i = k} \min_{ t\in Y} (\sum\limits_{x_i \not\in s} a_i +  \sum\limits_{y_i \not\in t} b_i + k \sum\limits_{y_j \in t}j)\\
&= \min_{k = 0}^{\frac{n(n+1)}{2}}\min_{s\in X \land \sum\limits_{x_i \in S}a_i = k} \min_{ t\in Y} (\sum\limits_{x_i \not\in s} a_i +  \sum\limits_{i = 1}^m\min(b_i,ik))\\
\end{aligned}
$$
$s$ 的取值并不影响式子后半部分的值，可以使用动态规划求解，用 $O(n^3)$ 的复杂度求出 $k$ 固定时所对应最小的 $\sum a_i$。而式子后半部分，对于每个 $i$ 而言时一个分段函数，拐点前都取 $ik$，拐点后都取 $b_i$，这个随着 $k$ 递增时易于维护的。

总时间复杂度 $O(n^3 + m)$，且常数很小，可以通过此题。

本体的技巧在于最大流不好考虑时转化为最小割的求解，以及通过枚举 $\sum\limits_{x_i\not\in s} a_i$ 的值来简化式子。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long 
using namespace std;
ll f[250050];
int n, m, Mx;
ll a[505], b[500050];
vector<pair<int, ll>> vc[250050];
int main(){
    cin >> n >> m;Mx = n * (n + 1) / 2;
    memset(f, 0x3f, sizeof(f));f[0] = 0;
    for(int i = 1;i <= n;i++){
        cin >> a[i];
        for(int j = Mx;j >= i;j--) f[j] = min(f[j], f[j - i] + a[i]);
    }
    for(int i = 1;i <= m;i++){
        cin >> b[i];
        ll g = b[i] / i + 1;
        if(g <= Mx) vc[g].push_back({i, b[i]});
    }
    ll ans = 1e18, sum = 0, sid = 0;
    for(int k = 0;k <= Mx;k++){
        ll cur = 1ll * m * (m + 1) / 2 * k;
        for(auto [id, s] : vc[k]) sid += id, sum += s;
        ans = min(ans, f[Mx - k] + cur + sum - sid * k);
    }
    cout << ans << endl;
}
```

---

## 作者：BreakPlus (赞：0)

容易想到建立网络流模型。

+ 从源点 $s$ 连向第 $i$ 个球，流量为 $a_i$。

+ 从第 $i$ 个球连向第 $j$ 个盒子，流量为 $i \times j$。

+ 从第 $j$ 个盒子连向汇点 $t$，流量为 $b_j$。

考虑最大流转最小割。令 $P$ 为包含所有割掉的 $s \to i$ 的边的 $i$ 集合，$Q$ 为包含所有割掉的 $j \to t$ 的 $j$ 的集合。

发现如果 $s \to i_0$ 没割，$j_0 \to t$ 没割，则必须割掉 $i_0 \to j_0$ 的边。于是我们就可以表示出固定 $P,Q$ 时答案为 $\sum_{i \in P}a_i + \sum_{j \in Q}b_j + \sum_{i \notin P}\sum_{j \notin Q} ij$。

进行一个微不足道的转化：$\sum_{i \in P}a_i + \sum_{j \in Q}b_j + (\sum_{i \notin P}i)(\sum_{j \notin Q} j)$。令 $K = \sum_{i \notin P}i$，$B = \sum_{i \in P}a_i$。

由于 $n \le 500$，启发我们固定 $K$。当 $K$ 固定时，$B$ 肯定越小越好。所以对于任意 $i \in [0, \dfrac{n(n+1)}{2}]$ 求出 $K=i$ 时的 $\min B$，可以背包做，$\mathcal{O}(n^3)$。

问题简化为求 $\min\{ K \times (\sum_{j \notin Q} j) + \sum_{j \in Q}b_j \}$。**也就是一个物品在 $Q$ 里贡献为 $b_j$，不在则贡献为 $K \times j$。** 显然二者区最小值更优。

对每个 $j$ 记录 $K \times j$ 反超 $b_j$ 的时间，从小到大枚举 $K$，将当前时刻从 $K \times j$ 变成 $b_j$ 的修改。这是平凡的，$\mathcal{O}(m)$。

```cpp
ll f[130005], n, m, a[505], b[500005];
vector<ll>vec[130005];
void solve(){
    n=read(), m=read();
    ll w1 = 0;
    for(ll i=1;i<=n;i++) a[i]=read(),w1+=a[i];
    for(ll i=1;i<=m;i++) b[i]=read();
    ll N = n * (n+1) / 2;
    memset(f, 128, sizeof(f));
    f[0] = 0;
    for(ll i=1;i<=n;i++){
        for(ll j=N; j>=i; j--){
            f[j] = max(f[j], f[j-i] + a[i]);
        }
    }
    for(ll i=0;i<=N;i++) f[i] = w1 - f[i];
    for(ll i=1;i<=m;i++){
        if(b[i]/i <= N) vec[(b[i] + i - 1) / i].pb(i);
    }
    ll lft = 0, all = m * (m+1) / 2, ans = f[0];
    for(auto t: vec[0]){
        lft += b[t]; all -= t;
    }
    for(ll i=1;i<=N;i++){
        for(auto t: vec[i]){
            lft += b[t]; all -= t;
        }
        chkmin(ans, lft + all * i + f[i]);
    }
    printf("%lld\n", ans);
}
```

---

