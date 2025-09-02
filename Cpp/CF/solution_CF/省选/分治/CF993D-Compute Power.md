# Compute Power

## 题目描述

You need to execute several tasks, each associated with number of processors it needs, and the compute power it will consume.

You have sufficient number of analog computers, each with enough processors for any task. Each computer can execute up to one task at a time, and no more than two tasks total. The first task can be any, the second task on each computer must use strictly less power than the first. You will assign between 1 and 2 tasks to each computer. You will then first execute the first task on each computer, wait for all of them to complete, and then execute the second task on each computer that has two tasks assigned.

If the average compute power per utilized processor (the sum of all consumed powers for all tasks presently running divided by the number of utilized processors) across all computers exceeds some unknown threshold during the execution of the first tasks, the entire system will blow up. There is no restriction on the second tasks execution. Find the lowest threshold for which it is possible.

Due to the specifics of the task, you need to print the answer multiplied by 1000 and rounded up.

## 说明/提示

In the first example the best strategy is to run each task on a separate computer, getting average compute per processor during the first round equal to 9.

In the second task it is best to run tasks with compute 10 and 9 on one computer, tasks with compute 10 and 8 on another, and tasks with compute 9 and 8 on the last, averaging (10 + 10 + 9) / (10 + 10 + 5) = 1.16 compute power per processor during the first round.

## 样例 #1

### 输入

```
6
8 10 9 9 8 10
1 1 1 1 1 1
```

### 输出

```
9000
```

## 样例 #2

### 输入

```
6
8 10 9 9 8 10
1 10 5 5 1 10
```

### 输出

```
1160
```

# 题解

## 作者：攀岩高手 (赞：5)

官方题解给的做法是 $O(n^3\log10^{11})$ 的，实际上这个题可以做到 $O(n^2\log10^{11})$。

先把这 $n$ 个任务按 $a_i$ 从大到小排序，$a_i$ 相等的合并成一个元素，内部再按 $b_i$ 从大到小排序。下面设共有 $m$ 种 $a_i$ 不同的元素。

然后二分答案，`check(k)` 表示答案是否不大于 $k$。那么每个要在第二次执行的任务都要匹配到一个 $a_i$ 严格大于它的在第一次执行的任务，并且对于在第一次执行的任务要有 $\sum a_i-kb_i\leq 0$。我们不妨求出这个和式满足约束条件时的最小值。下面将 在第一次执行的任务称作“选中的元素”。

由 Hall 定理可知，对于处理过程中的每一个前缀 $i(i\leq m)$ ，都要满足 $i-1$ 前选了的元素个数大于等于 $i$ 前没选的元素个数。然后 DP ，设 $f(i,j)$ 表示前 $i$ 个中选了 $j$ 个的最小值。那么问题就变成了一个多重背包，因为 $a_i$ 相同的任务肯定会优先选 $b_i$ 大的。物品的总数为 $O(n)$ ，所以复杂度是 $O(n^2)$。

### 代码 ###
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const int MAXN=55;
struct Task
{
	int a, b;
	bool operator < (const Task& rhs) const
	{
		return a>rhs.a||a==rhs.a&&b>rhs.b;
	}
} t[MAXN];
int n, m;
vector<int> v[MAXN];
ll f[MAXN][MAXN];
bool check(ll r)
{
	memset(f, 0X3F, sizeof f);
	f[0][0]=0;
	for (int i=1, c=0; i<=m; i++)
	{
		c+=v[i].size();
		for (int j=0; j<=c; j++)
		{
			ll s=0;
			for (int k=0; k<=v[i].size()&&k<=j&&j-k>=c-j; k++)
			{
				if (k) s+=1000ll*t[v[i][k-1]].a-r*t[v[i][k-1]].b;
				f[i][j]=min(f[i][j], f[i-1][j-k]+s);
			}
		}
	}
	for (int i=0; i<=n; i++)
		if (f[m][i]<=0) return 1;
	return 0;
}
int main()
{
//	freopen("D.in", "r", stdin);
//	freopen("D.out", "w", stdout);
	scanf("%d", &n);
	for (int i=1; i<=n; i++) scanf("%d", &t[i].a);
	for (int i=1; i<=n; i++) scanf("%d", &t[i].b);
	sort(t+1, t+n+1);
	for (int i=1; i<=n; i++)
	{
		if (t[i].a!=t[i-1].a) m++;
		v[m].push_back(i);
	}
	ll l=0, r=1E11;
	while (l<r)
	{
		ll mid=l+r>>1;
		if (check(mid)) r=mid;
		else l=mid+1;
	}
	printf("%lld\n", l);
	return 0;
}

---

## 作者：奇卡 (赞：5)

### [我的博客](https://www.cnblogs.com/PsychicBoom/p/10473320.html)

------------


一看到这种求$min/max\left \{ \frac{\sum a_i}{\sum b_i}  \right \}$的题肯定是$01$分数规划，大概可以算作一种二分？

设$ans$为当前枚举到的答案，对于本题，如果想把答案往更小的方向更新，必须满足：

$$\sum a_i-ans*\sum b_i \leq 0$$

即：

$$\sum a_i-ans* b_i \leq 0$$

二分从来都是套板子的事，难点是如何写一个$check$函数

发现枚举第一个做的任务不现实（有后面跟着第二个任务和不跟第二个任务两种情况，不好讨论），考虑枚举第二个做的任务的**最大总价值**，用 $总价值-第二个任务的价值$ 即可,

这个可以用$Dp$求：设$f[i][j]$表示枚举到在数列$a$中**排名**为$i$的任务，一共做了$j$个任务时的最大价值。转移方程为：

$$f[i][j+k]=max\left \{ f[i+1][j]+W[i][k](0\leq k \leq cnt[i]) \right \}$$

$W[i][j]$为把排名为$i$的任务中，价值$(a-ans*b)$ 最大的$j$个任务的价值和

时间复杂度$O(n^3log1e8)$

注意的事：

1、向上取整

2 、**用cout一定要输出long long！！**

代码：
```cpp
#include <bits/stdc++.h>
#define rd(x) scanf("%d",&x)
#define N 55
#define getrank(x) lower_bound(p+1,p+sz+1,x)-p
#define rnk(i) x[i].rnk
#define ll long long
using namespace std;

const double eps=1e-7;
struct qwq{
    int a,b,rnk;
    double v;
}x[N];
int n,cnt[N],pre[N],num[N],sz;
double f[N][N],p[N],W[N][N];

bool cmp(const qwq &x,const qwq &y){ return (x.a==y.a)?x.v>y.v:x.a>y.a; }

double check(double tmp){
    double tot=0,ans=0;int i,j,k;
    for(i=1;i<=n;++i){
        x[i].v=(double)x[i].a-tmp*x[i].b;
        tot+=x[i].v;
    }
    sort(x+1,x+n+1,cmp);memset(f,0xc0,sizeof(f));memset(num,0,sizeof(num));
    for(i=1;i<sz;++i) W[i][0]=0;
    for(i=1;i<=n;++i) W[rnk(i)][++num[rnk(i)]]=W[rnk(i)][num[rnk(i)]-1]+x[i].v;
    ans=f[0][0];
    if(sz==1) return tot-W[sz][num[1]];
    for(int j=0;j<=min(num[sz],num[sz-1]);++j) f[sz-1][j]=W[sz-1][j];
    for(i=sz-2;i>=1;--i){
        for(j=0;j<=pre[sz-1]-pre[i];++j)
            for(k=0;k<=num[i];++k)
                if(n-pre[i]-2*j>=k) f[i][j+k]=max(f[i+1][j]+W[i][k],f[i][j+k]);		
    }
    for(i=0;i<=pre[sz-1];++i) ans=max(ans,f[1][i]);
    return tot-ans;
}

int main(){
    int i;
    rd(n);
    for(i=1;i<=n;++i) rd(x[i].a),p[i]=x[i].a;
    for(i=1;i<=n;++i) rd(x[i].b);
    sort(p+1,p+n+1);sz=unique(p+1,p+n+1)-p-1;
    for(i=1;i<=n;++i) cnt[x[i].rnk=getrank(x[i].a)]++;
    for(i=1;i<=sz;++i) pre[i]=pre[i-1]+cnt[i];
    if(sz==1){
        ll aa=0,bb=0;
        for(i=1;i<=n;++i) aa+=1ll*x[i].a,bb+=1ll*x[i].b;
        double qwq=(double)aa/bb*1000.0;
        printf("%I64d",(ll)ceil(qwq));return 0;
    }
    double l=0,r=1e8;
    while(r-l>eps){
        double mid=(r-l)*0.5+l;
        if(check(mid)<=0) r=mid;
        else l=mid;
    }
    l*=1000.0;
    printf("%I64d",(ll)ceil(l));
}
```



---

## 作者：Purslane (赞：0)

# Solution

分数规划。考虑判定答案能否 $\le t$。

将 $a$ 排序。设 $dp_{i,j,k}$ 表示考虑了前 $i$ 大的 $a$，有 $j$ 个 $>a_i$ 任务产生的代金券，有 $k$ 个 $=a_i$ 产生的代金券，$\sum a - t b$ 的最小值。

当 $a_i \neq a_{i+1}$ 时，应当令 $j \leftarrow j+k$，$k \leftarrow 0$。

从 $(i-1,j,k)$ 转移。

如果买，转移到 $dp_{i,j,k+1}$；如果不买，转移到 $dp_{i,j-1,k}$。看最后 $dp_{n,*,*}$ 的最小值是否 $\le 0$。

复杂度 $O(n^3 \log V)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=50+10;
int n,a[MAXN],b[MAXN],dp[MAXN][MAXN][MAXN];
vector<pair<int,int>> vc;
int check(int dt) {
	memset(dp,0x3f,sizeof(dp));
	dp[0][0][0]=0;
	ffor(i,1,n) ffor(lst1,0,n) ffor(lst2,0,n) if(lst1+lst2<=i-1) {
		int v1=lst1,v2=lst2;
		if(a[i]!=a[i-1]) v1+=v2,v2=0;
		dp[i][v1][v2+1]=min(dp[i][v1][v2+1],dp[i-1][lst1][lst2]+a[i]-b[i]*dt);
		if(v1) dp[i][v1-1][v2]=min(dp[i][v1-1][v2],dp[i-1][lst1][lst2]);
	}
	ffor(i,0,n) ffor(j,0,n) if(dp[n][i][j]<=0) return 1;
	return 0;
}
int bfind(int l,int r) {
	int ans=-1,mid;
	while(l<=r) {
		mid=l+r>>1;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) cin>>a[i],a[i]*=1000;
	ffor(i,1,n) cin>>b[i],vc.push_back({a[i],b[i]});
	sort(vc.begin(),vc.end());
	ffor(i,1,n) a[n-i+1]=vc[i-1].first,b[n-i+1]=vc[i-1].second;
//	ffor(i,1,n) cout<<a[i]<<' '; cout<<'\n';
//	ffor(i,1,n) cout<<b[i]<<' '; cout<<'\n';
	cout<<bfind(1,100000000000);
//	check(9001);
//	ffor(i,0,n) ffor(j,0,n) cout<<dp[n][i][j]<<' ';
	return 0;
}
```

---

## 作者：幻影星坚强 (赞：0)

提供一个不用 01 分数规划的做法。

俩东西相除同时分子分母同时加非常难维护，所以我们可以固定一个东西，这样另外一个东西只要保证它最大或最小就行了。

首先有一个第二个选的功率更小的限制，所以我们要实现对其进行排序。之后会产生许多功率相同的段， 对于每一段他都是可以接到前面为第一个选的任务后面，这样我们就消除了后效性。

因为处理器个数非常的小，所以我们把它记录到状态里，然后对于相同效率的一段整体进行转移。记录 $dp_{i,j,k}$ 表示当前处理到第 $i$ 大的功率，有 $j$ 个计算机可以放第二个任务，此时的处理器个数为 $k$ 时最小的功率和。

这看上去非常能转移，但实际上我们有一个小问题，就是我们并不知道当前要选哪些任务。有一个非常显然的贪心，就是所有功率相同的任务中，我们放在第一个任务的一定是处理器最大的那几个（否则可以交换他们放的位置使得分子不变，分母变大）。那么我们将所有功率相同的任务按处理器个数从大到小排序，然后转移时枚举当前功率的任务有多少个要放在第一个即可。具体来说，设 $t_i$ 表示功率第 $i$ 大的个数， $p_{i,j}$ 表示当前功率第 $j$ 大的处理器个数，那么有

$$dp_{i,j,k} = \min_{o=1}^{s_i}(dp_{i-1,j+s_i-o,k-{\sum_{x=1}^{o} p_{i,x}}} + a_i \times o)$$

前缀和处理一下 $p_i$ 就行了。

然后每一段效率转移都是 $O(100\times s_i n^2)$ 的，时间复杂度 $O(100 \times n^3)$ 。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 52;
struct computer
{
	int a, b;
}c[N];
bool pd(computer i, computer j)
{
	return i.a > j.a || (i.a == j.a && i.b > j.b);
}
int n;
long long dp[N][N][N * N << 1];
long long qzh[N];
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i) scanf("%d", &c[i].a);
	for (int i = 1; i <= n; ++ i) scanf("%d", &c[i].b);
	sort(c + 1, c + 1 + n, pd);
	for (int i = 0; i <= n + 1; ++ i)
	{
		for (int j = 0; j <= n + 1; ++ j)
		{
			for (int k = 0; k <= 100 * n + 1; ++ k)
			{
				dp[i][j][k] = 1e18;
			}
		}
	}
	dp[0][0][0] = 0;
	int be = 0;
	for (int i = 1; i <= n; ++ i)
	{
		int to = i;
		qzh[1] = c[to].b;
		while(c[to + 1].a == c[to].a) ++ to, qzh[to - i + 1] = qzh[to - i] + c[to].b;
		for (int siz = 0; siz <= to - i + 1; ++ siz)
			for (int j = 0; j + siz <= to && j + (to - i + 1 - siz) <= to; ++ j)
				for (int k = 0; k <= 100 * n; ++ k)
					if(k >= qzh[siz])
					dp[i][j + siz][k] = min(dp[i][j + siz][k], dp[be][j + (to - i + 1 - siz)][k - qzh[siz]] + 1ll * c[i].a * siz);
		be = i;
		i = to;
	}
	double mins = 1e18;
	for (int i = 0; i <= n; ++ i)
	for (int j = 1; j <= 100 * n; ++ j)
	mins = min(mins, 1.0 * dp[be][i][j] / j);
	printf("%.0Lf", mins * 1000 + 0.5);
}
```


---

