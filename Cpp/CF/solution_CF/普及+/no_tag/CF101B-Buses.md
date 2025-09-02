# Buses

## 题目描述

Little boy Gerald studies at school which is quite far from his house. That's why he has to go there by bus every day. The way from home to school is represented by a segment of a straight line; the segment contains exactly $ n+1 $ bus stops. All of them are numbered with integers from $ 0 $ to $ n $ in the order in which they follow from Gerald's home. The bus stop by Gerald's home has number $ 0 $ and the bus stop by the school has number $ n $ .

There are $ m $ buses running between the house and the school: the $ i $ -th bus goes from stop $ s_{i} $ to $ t_{i} $ ( $ s_{i}&lt;t_{i} $ ), visiting all the intermediate stops in the order in which they follow on the segment. Besides, Gerald's no idiot and he wouldn't get off the bus until it is still possible to ride on it closer to the school (obviously, getting off would be completely pointless). In other words, Gerald can get on the $ i $ -th bus on any stop numbered from $ s_{i} $ to $ t_{i}-1 $ inclusive, but he can get off the $ i $ -th bus only on the bus stop $ t_{i} $ .

Gerald can't walk between the bus stops and he also can't move in the direction from the school to the house.

Gerald wants to know how many ways he has to get from home to school. Tell him this number. Two ways are considered different if Gerald crosses some segment between the stops on different buses. As the number of ways can be too much, find the remainder of a division of this number by $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

The first test has the only variant to get to school: first on bus number one to the bus stop number one; then on bus number two to the bus stop number two.

In the second test no bus goes to the third bus stop, where the school is positioned. Thus, the correct answer is $ 0 $ .

In the third test Gerald can either get or not on any of the first four buses to get closer to the school. Thus, the correct answer is $ 2^{4}=16 $ .

## 样例 #1

### 输入

```
2 2
0 1
1 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 2
0 1
1 2
```

### 输出

```
0
```

## 样例 #3

### 输入

```
5 5
0 1
0 2
0 3
0 4
0 5
```

### 输出

```
16
```

# 题解

## 作者：__Hacheylight__ (赞：4)

题意：
有一个人要从0到n，其间有m趟公交车，这个人可以从$s_i->t_i-1$的位置上车，必须在$t_i$下车。他想问有多少种方法（$\% \ 10^9+7$）

解法：

很明显要离散，怎么离散就不讲了。车也要按照终点排序

很容易发现这是一道dp题，并且想出dp状态

dp[i]表示乘坐第i趟公交车到达终点的方案数，答案就是所有终点是n的dp值
转移枚举前面那趟公交车进行转移，时间复杂度$O(m^2)$

如何优化？

似乎很容易，我们的上一趟公交车肯定是在$s_i->t_i-1$范围转移来的，所以我们只要把从$s_i->t_i-1$的dp值加到dp[i]就行了，而因为排序，起点在前的一定编号小，于是我们只要在原序列中进行$lower\_bound$就行了，

再通过前缀和求出一段dp值加入到dp[i]里，就OK了

别看总场通常，那是因为头文件的原因，真正main函数里的代码还是挺短的

```cpp
#include <map>
#include <set>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <vector>
#include <bitset>
#include <cstdio>
#include <cctype>
#include <string>
#include <cstring>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std ;

#define rep(i, a, b) for (int (i) = (a); (i) <= (b); (i)++)
#define Rep(i, a, b) for (int (i) = (a) - 1; (i) < (b); (i)++)
#define REP(i, a, b) for (int (i) = (a); (i) >= (b); (i)--)
#define clr(a) memset(a, 0, sizeof(a))
#define Sort(a, len, cmp) sort(a + 1, a + len + 1, cmp)
#define ass(a, sum) memset(a, sum, sizeof(a))

#define ls ((rt) << 1)
#define rs ((rt) << 1 | 1)
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define endl '\n'
#define ENDL cout << endl
#define SZ(x) ((int)x.size())

typedef long long ll ;
typedef unsigned long long ull ;
typedef vector <int> vi ;
typedef pair <int, int> pii ;
typedef pair <ll, ll> pll ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
typedef map <ll, ll> mll ;

const int N = 100010 ;
const double eps = 1e-8 ;
const int iinf = INT_MAX ;
const ll linf = 2e18 ;
const double dinf = 1e30 ;
const int MOD = 1000000007 ;

inline int read(){
    int X = 0, w = 0 ;
	char ch = 0 ;
    while (!isdigit(ch)) { w |= ch == '-' ; ch = getchar() ; }
    while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar() ;
    return w ? - X : X ;
}

void write(int x){
     if (x < 0) putchar('-'), x = - x ;
     if (x > 9) write(x / 10) ;
     putchar(x % 10 + '0') ;
}

void print(int x) {
	cout << x << endl ;
	exit(0) ;
}

void PRINT(string x) {
	cout << x << endl ;
	exit(0) ;
}

void douout(double x){
	 printf("%lf\n", x + 0.0000000001) ;
}

int dp[N], sum[N] ;
int n, m, ans ;

int main() {
	scanf("%d%d", &n, &m) ;
	vector <pii> a(m) ; vi v(m) ;
	for (int i = 0, s, t; i < m; i++) {
		scanf("%d%d", &s, &t) ;
		a[i] = mp(t, s) ;
		v[i] = t ;
	}
	sort(a.begin(), a.end()) ; sort(v.begin(), v.end()) ;
	for (int i = 0; i < m; i++) {
		int f = a[i].se, t = a[i].fi ;
		if (f == 0) dp[i] = 1 ;
		int S = lower_bound(v.begin(), v.end(), f) - v.begin() ;
		int T = lower_bound(v.begin(), v.end(), t) - v.begin() ;
		dp[i] = (dp[i] + sum[T] - sum[S] + MOD) % MOD ;
		sum[i + 1] = (sum[i] + dp[i]) % MOD ;
	}
	for (int i = 0; i < m; i++) if (a[i].fi == n) ans = (ans + dp[i]) % MOD ;
	printf("%d\n", ans) ;
}

/*
写代码时请注意：
	1.是否要开Long Long？数组边界处理好了么？
	2.实数精度有没有处理？
	3.特殊情况处理好了么？
	4.做一些总比不做好。
思考提醒：
	1.最大值和最小值问题可不可以用二分答案？
	2.有没有贪心策略？否则能不能dp？
*/

```

---

## 作者：傅思维666 (赞：3)

## 题解：

计数类题想DP。

首先想：状态可以设成$dp[i]$表示到车站$i$下车有多少种方式。答案是$dp[n]$。但是发现$n$很大，而且不太好转移。所以开始思考：到车站$i$下车，只能是终点在$i$的车次。既然$m$的范围可以，又有这个性质，能不能直接用车次代替位置来维护呢？

可以：设状态为$dp[i]$表示第$i$趟车（当然要在$t[i]$下车）的方案数，最终答案是所有$t[i]=n$的$dp[i]$的和。转移也非常好想：能在$t[i]$下车，一定会在$s[i]-t[i]$这段路上上车，所以只需要枚举有哪些车次的终点在这段路上，这些车都可以转移到当前状态。

那就麻烦了，怎么找到这些转移的车次呢？

我们可以考虑对其按右端点进行排序，这样，转移而来的那些车次一定在当前车次之前。那么，就可以通过二分查找来找到这个东西。

代码：

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int maxm=1e5+5;
const int mod=1e9+7;
int n,m,ans;
vector<pair<int,int> >e;
vector<int> f;
int dp[maxm],sum[maxm];
int main()
{
    scanf("%d%d",&n,&m);
    e.push_back(make_pair(0,0));
    f.push_back(0);
    for(int i=1;i<=m;i++)
    {
        int s,t;
        scanf("%d%d",&s,&t);
        e.push_back(make_pair(t,s));
        f.push_back(t);
    }
    sort(e.begin(),e.end());
    sort(f.begin(),f.end());
    for(int i=1;i<=m;i++)
    {
        int x=e[i].second,y=e[i].first;//x,y是当前路线的起终点
        if(!x)
            dp[i]=1;
        int s=lower_bound(f.begin(),f.end(),x)-f.begin();
        int t=lower_bound(f.begin(),f.end(),y)-f.begin();
        dp[i]=(dp[i]+sum[t]-sum[s]+mod)%mod;
        sum[i+1]=(sum[i]+dp[i])%mod;
    }
    for(int i=1;i<=m;i++)
        if(e[i].first==n)
            ans=(ans+dp[i])%mod;
    printf("%d\n",ans);
    return 0;
}
```



---

## 作者：tonyre (赞：2)

# CF101B Bus 题解

## 1 题解

看到统计方法数，首先思考 dp。

### 1.1 表示状态

首先容易想到 $dp[i]$ 表示到 $i$ 车站的总方案数，但这样很难转移。（其实这道题的难点就是状态的表示。）

可以想到这种情况下 $dp[i]$ 都是由满足 $t_x=i$ 的车站 $x$ 决定的，而且 $m$ 范围不大，**所以考虑 $dp[i]$ 表示坐 $i$ 公交到终点的总方案数**。

### 1.2 状态转移

状态转移就好想多了。想乘坐公交 $x$，则一定在 $[s_x,t_x)$ 区间内上车。我们枚举终点在这个区间所有公交线路，再将这里所有公交线路的 dp 值求和即可。

### 1.3 优化

假如暴力写，时间复杂度为 $O(m^2)$，显然过不了，我们考虑优化。

首先我们可以提前按照终点排序，这样枚举终点在区间内的公交线路可以通过二分查找实现（找左端点和右端点）。求 dp 值可以通过前缀和实现（因为提前排过序）。**时间复杂度 $O(m\log m)$。**

### 1.4 总结

一道有一定思维难度的 dp 题。~~这题为什么能评紫？~~

## 2 参考代码

```c++
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
const int MAXM=100005;
const int MOD=1e9+7;
struct Bus
{
    int s,t;
}a[MAXM];
int dp[MAXM];
int sum[MAXM];
bool cmp(Bus x,Bus y)
{
    if(x.t==y.t) return x.s<y.s;
    return x.t<y.t;
}
signed main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++) cin>>a[i].s>>a[i].t;
    sort(a+1,a+m+1,cmp);
    for(int i=1;i<=m;i++)
    {
        if(!a[i].s) dp[i]=1;
        int l=1,r=i-1;
        int mid;
        int ans1=-1;
        while(l<=r)
        {
            mid=(l+r)>>1;
            if(a[mid].t>=a[i].s)
            {
                r=mid-1;
                ans1=mid;
            }
            else l=mid+1;
        }
        l=1,r=i-1;
        int ans2=-1;
        while(l<=r)
        {
            mid=(l+r)>>1;
            if(a[mid].t<a[i].t)
            {
                l=mid+1;
                ans2=mid;
            }
            else r=mid-1;
        }
        if(ans1!=-1&&ans2!=-1)
        {
            dp[i]+=sum[ans2]-sum[ans1-1];
            dp[i]=(dp[i]+MOD)%MOD;
        }
        sum[i]=(sum[i-1]+dp[i])%MOD;
    }
    int cnt=0;
    for(int i=1;i<=m;i++)
        if(a[i].t==n)
        {
            cnt+=dp[i];
            cnt=(cnt+MOD)%MOD;
        }
    cout<<cnt<<endl;
    return 0;
}
```

---

## 作者：CQ_Bob (赞：1)

## 分析

考虑 DP。

由于 $n$ 很大，而 $m$ 可以接受，考虑根据公交车定义状态函数。很容易想到一种状态函数：$f_i$ 表示做第 $i$ 辆公交车到 $t_i$ 的方案数。根据题意，就有转移方程：$f_i=\sum f_j [s_i \le t_j \le t_i-1]+k$，$k$ 在 $s_i=0$ 时为 $1$，其余为 $0$。

然后这题就会了。求和部分用线段树优化，答案为 $\sum f_i[t_i=n]$。复杂度 $O(m \log m)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define pii pair<int,int>
#define x first
#define y second
#define gc getchar()
#define rd read()
#define debug() puts("------------")

namespace yzqwq{
	il int read(){
		int x=0,f=1;char ch=gc;
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
		while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
		return x*f;
	}
	il int qmi(int a,int b,int p){
		int ans=1;
		while(b){
			if(b&1) ans=ans*a%p;
			a=a*a%p,b>>=1;
		}
		return ans;
	}
	il auto max(auto a,auto b){return (a>b?a:b);}
	il auto min(auto a,auto b){return (a<b?a:b);}
	il int gcd(int a,int b){
		if(!b) return a;
		return gcd(b,a%b);
	}
	il int lcm(int a,int b){
		return a/gcd(a,b)*b;
	}
	il void exgcd(int a,int b,int &x,int &y){
		if(!b) return x=1,y=0,void(0);
		exgcd(b,a%b,x,y);
		int t=x;
		x=y,y=t-a/b*x;
		return ;
	}
	mt19937 rnd(time(0));
}
using namespace yzqwq;

const int N=1e5+10,p=1e9+7;
int n,m;
int f[N];
int b[N<<2],idx;
struct node{
	int s,t;
}a[N];
struct Tree{
	int l,r,s;
}tr[N<<3];

il bool cmp(node a,node b){
	if(a.t!=b.t) return a.t<b.t;
	return a.s<b.s;
}

il void up(int now){
	tr[now].s=(tr[now<<1].s+tr[now<<1|1].s)%p;
}
il void build(int now,int l,int r){
	tr[now].l=l,tr[now].r=r;
	if(l==r) return tr[now].s=0,void(0);
	int mid=l+r>>1;
	build(now<<1,l,mid),build(now<<1|1,mid+1,r);
	return ;
}
il void insert(int now,int x,int k){
	if(tr[now].l==tr[now].r) return tr[now].s=(tr[now].s+k)%p,void(0);
	int mid=tr[now].l+tr[now].r>>1;
	if(x<=mid) insert(now<<1,x,k);
	else insert(now<<1|1,x,k);
	return up(now),void(0);
}
il int query(int now,int l,int r){
	if(tr[now].l>=l&&tr[now].r<=r) return tr[now].s;
	int ans=0,mid=tr[now].l+tr[now].r>>1;
	if(l<=mid) ans=(ans+query(now<<1,l,r))%p;
	if(mid<r) ans=(ans+query(now<<1|1,l,r))%p;
	return ans;
}

il void solve(){
	n=rd,m=rd,++n,b[++idx]=1,b[++idx]=n;
	for(re int i=1;i<=m;++i) 
		a[i]={rd+1,rd+1},
		b[++idx]=a[i].s,
		b[++idx]=a[i].t;
	sort(b+1,b+idx+1),sort(a+1,a+m+1,cmp);
	idx=unique(b+1,b+idx+1)-(b+1);
	for(re int i=1;i<=m;++i) 
		a[i].s=lower_bound(b+1,b+idx+1,a[i].s)-b,
		a[i].t=lower_bound(b+1,b+idx+1,a[i].t)-b;
	build(1,1,idx);
	for(re int i=1;i<=m;++i) f[i]=(a[i].s==1);
	for(re int i=1;i<=m;++i){
		f[i]=(f[i]+query(1,a[i].s,a[i].t-1))%p;
		insert(1,a[i].t,f[i]);
	}
	n=lower_bound(b+1,b+idx+1,n)-b;
	int ans=0;
	for(re int i=1;i<=m;++i){
		if(a[i].t==n) ans=(ans+f[i])%p;
	}
	printf("%lld\n",ans);
	return ;
}

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int t=1;while(t--)
	solve();
	return 0;
}
```


---

## 作者：Leaper_lyc (赞：0)

首先，可以很明显地感受到这题可以用 dp 解决。

设 $f_i$ 表示乘坐第 $i$ 辆车走到 $t_i$ 的方案数。

转移时，考虑上一次乘坐的是哪辆车，假设上一辆乘坐的是第 $j$ 辆车，那么 $j$ 需要满足 $t_j\in[s_i,t_i-1]$，那么 $f_i$ 就等于这些 $f_j$ 的和。还有一种要特判的就是 $s_i=0$ 的情况，这种情况下可以直接在第 $0$ 号车站乘坐第 $i$ 辆车，对 $f_i$ 有 $1$ 的贡献。

这样做至少是 $O(m^2)$ 的，接下来开始优化。

由于区间范围 $n$ 太大，于是离散化。

离散化后，记 $g_i$ 表示所有满足 $t_j=i$ 的 $f_j$ 的和。那么转移方程就可以写成：$f_i=\sum\limits_{j=s_i}^{t_i-1} g_j$。

这个求和可以用线段树/树状数组/前缀和等等方式优化调。我是用树状数组。

代码是好写的，注意取模和特判。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 10;
const int mod = 1e9 + 7;
int n, m;
int b[N], cnt;
int f[N];
struct node {
    int s, t;
    bool operator<(const node &tmp) const { return t < tmp.t; }
} a[N];
struct BIT {
    int c[N];
    inline void add(int x, int v) {
        for (; x <= cnt; x += x & (-x)) c[x] = (c[x] + v) % mod;
    }
    inline int qry(int x) {
        int res = 0;
        for (; x; x -= x & (-x)) res = (res + c[x]) % mod;
        return res;
    }
} T;
signed main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> a[i].s >> a[i].t;
        b[++cnt] = a[i].s, b[++cnt] = a[i].t;
    }
    b[++cnt] = n;
    sort(b + 1, b + cnt + 1);
    cnt = unique(b + 1, b + cnt + 1) - b - 1;
    if (b[1] != 0) return cout << "0\n", 0;
    for (int i = 1; i <= m; i++) {
        a[i].s = lower_bound(b + 1, b + cnt + 1, a[i].s) - b;
        a[i].t = lower_bound(b + 1, b + cnt + 1, a[i].t) - b;
    }
    sort(a + 1, a + m + 1);
    for (int i = 1; i <= m; i++) {
        f[i] = (T.qry(a[i].t - 1) - T.qry(a[i].s - 1) + mod) % mod;
        if (a[i].s == 1) f[i]++;
        T.add(a[i].t, f[i]);
    }
    cout << (T.qry(cnt) - T.qry(cnt - 1) + mod) % mod;
}
```

---

## 作者：wz20201136 (赞：0)

### 题意
[见题面](https://www.luogu.com.cn/problem/CF101B)
### 题解
注意到最终的答案只与每辆公交车起点终点的大小关系有关，考虑离散化+动态规划。

离散化后 $dp_i$ 表示到达第 $i$ 个车站的总方案数转移时枚举每一辆在第 $i$ 个车站停车的公交车，得到了若干个可以上车的区间 $[l,r]$ 求和时前缀和优化即可。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
vector<int> lst[200005];//第i个车站停车的公交车
int n,m,s[200005],t[200005],dp[200005][2];//0:dp;1:sum
const int mod=1e9+7;
signed main()
{
	cin>>n>>m;
	vector<int> vc;
	vc.push_back(n);
	for(int i=1;i<=m;i++)
	{
		cin>>s[i]>>t[i];
		vc.push_back(s[i]),vc.push_back(t[i]);
	}
	map<int,int> ls;
	sort(vc.begin(),vc.end());
	if(vc[0]) return puts("0"),0;
	ls[vc[0]]=0;
	int cnt=0;
   //离散化
	for(int i=1;i<vc.size();i++)
	{
		if(vc[i]==vc[i-1]) continue;
		ls[vc[i]]=++cnt;
	}
	for(int i=1;i<=m;i++) s[i]=ls[s[i]],t[i]=ls[t[i]];
	for(int i=1;i<=m;i++) lst[t[i]].push_back(s[i]);//第i个车站停车的公交车
	dp[0][0]=dp[0][1]=1;
	for(int i=1;i<=cnt;i++)
	{
		for(int j=0;j<lst[i].size();j++) dp[i][0]=(dp[i][0]+dp[i-1][1]-(!lst[i][j]?0:dp[lst[i][j]-1][1]/*防止访问到-1*/)+mod)%mod;
		dp[i][1]=(dp[i-1][1]+dp[i][0])%mod;
	}
	cout<<dp[cnt][0];
	return 0;
}
```

---

## 作者：_lxy_ (赞：0)

### 题意

有 $n$ 个公交站， $m$ 辆车，只能从 $[s_i,t_i-1]$ 范围里的公交站上车，问有多少种到第 $n$ 站的方案。

### 分析

这显然是一道 dp 题。 $dp_i$ 表示坐第 $i$ 辆车到 $t_i$ 站的方案数。首先将所有公交车按照终点从小到大排序，这样就可以二分找到终点符合条件的一段公交车的左端点 $l$ 和右端点 $r$ ，$dp_i= \sum\limits_{j=l}^r dp_j$ ，特判一下起点为 $0$ 的情况，用前缀和优化即可。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int inf=2139062143;
const int MAXN=1e5+7;
const int mod=1e9+7;
inline void qread(){}template<class T1,class ...T2>
inline void qread(T1 &a,T2&... b)
{
	register T1 x=0;register bool f=false;char ch=getchar();
	while(ch<'0') f|=(ch=='-'),ch=getchar();
	while(ch>='0') x=(x*10)+(ch^48),ch=getchar();
	x=(f?-x:x);a=x;qread(b...);
}
int n,m,dp[MAXN],pre[MAXN],ans;
struct node{int s,t;node(){;}node(int _s,int _t):s(_s),t(_t){}bool operator < (const node &o)const{return t<o.t;}};
vector<node>a;
signed main()
{
    qread(n,m);int i,j;
    for(i=0;i<m;i++){int x,y;qread(x,y);a.push_back(node{x,y});}
    sort(a.begin(),a.end());
    for(i=0;i<m;i++)
    {
        int l=a[i].s,r=a[i].t;
        int t1=lower_bound(a.begin(),a.end(),node{0,l})-a.begin();
        int t2=lower_bound(a.begin(),a.end(),node{0,r})-a.begin();
        dp[i]=(pre[t2]-pre[t1]+mod)%mod;
        if(!l) dp[i]++;
        pre[i+1]=(pre[i]+dp[i])%mod;
        if(r==n) ans=(ans+dp[i])%mod;
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：_HMZ_ (赞：0)

看见各位大佬都是前缀和啊……用线段树的小蒟蒻表示不服。

## 解题思路：

类似 dp，$dp_i$ 表示走到当前这一条路线的情况个数。

如何转移呢？所有终点在当前路线中间的都可以加进当前答案。

但是有两个问题。

第一个，区间无序，如果暴力扫描肯定会超时。

既然无序，那就让区间按照右端点排个序，这样一二分就知道哪一段要统计了。

第二个问题，如何快速求出一段的和。

看见各位大佬都是用的前缀和，但是我表示不太理解。

换个方式，这其实是一个数据结构，需要单点修改和区间查询。

诶，这不是线段树模板吗？（当然如果你会树状数组就当我什么也没说）

于是就可以愉快的 AC 这道题了。

## AC代码：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
#define int long long//十年OI一场空，不开long long见祖宗。
const int mo=1e9+7;
int n,m,tree[1000005],tag[1000005],sum;
struct node
{
    int l,r;
}s[1000005];
void push_down(int now,int l,int r)//线段树就不多解释了。
{
    int mid=(l+r)/2;
    tag[now*2]+=tag[now]%mo;
    tag[now*2]%=mo;
    tag[now*2+1]+=tag[now]%mo;
    tag[now*2+1]%=mo;
    tree[now*2]+=(mid-l+1)*tag[now]%mo;
    tree[now*2]%=mo;
    tree[now*2+1]+=(r-mid)*tag[now]%mo;
    tree[now*2+1]%=mo;
    tag[now]=0;
}
void update(int now,int l,int r,int x,int y,int w)
{
    if(l>y || r<x)  return;
    if(x<=l && r<=y)
    {
        tree[now]+=(r-l+1)*w%mo;
        tree[now]%=mo;
        tag[now]+=w%mo;
        tag[now]%=mo;
        return;
    }
    int mid=(l+r)/2;
    push_down(now,l,r);
    update(now*2,l,mid,x,y,w);
    update(now*2+1,mid+1,r,x,y,w);
    tree[now]=(tree[now*2]+tree[now*2+1])%mo;
    tree[now]%=mo;
}
int query(int now,int l,int r,int x,int y)
{
    if(l>y || r<x)  return 0;
    if(x<=l && r<=y)
        return tree[now];
    int mid=(l+r)/2;
    push_down(now,l,r);
    int res=(query(now*2,l,mid,x,y)+query(now*2+1,mid+1,r,x,y))%mo;
    tree[now]=(tree[now*2]+tree[now*2+1])%mo;
    tree[now]%=mo;
    return res;
}
bool cmp(node x,node y)//排序
{
    if(x.r==y.r)
        return x.l<y.l;
    else
        return x.r<y.r;
}
int search(int now)//手动二分。
{
    int l=1,r=m,ans=-1;
    while(l<=r)
    {
        int mid=(l+r)/2;
        if(s[mid].r<=now)
            l=mid+1,ans=mid;
        else
            r=mid-1;
    }
    return ans;
}
int search2(int now)
{
    int l=1,r=m,ans=-1;
    while(l<=r)
    {
        int mid=(l+r)/2;
        if(s[mid].r>=now)
            r=mid-1,ans=mid;
        else
            l=mid+1;
    }
    return ans;
}
signed main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
        cin>>s[i].l>>s[i].r;
    sort(s+1,s+1+m,cmp);
    for(int i=1;i<=m;i++)
        if(s[i].l==0)
            update(1,1,m,i,i,1);//如果起点是0，则赋初值。
    for(int i=1;i<=m;i++)
    {
        int pos1=search2(s[i].l),pos2=search(s[i].r-1);//找一段可行的区间。
        if(pos2==-1 || pos1==-1 || pos1>pos2)    continue;
        update(1,1,m,i,i,query(1,1,m,pos1,pos2));//线段树修改。
    }
    for(int i=1;i<=m;i++)
        if(s[i].r==n)
            sum+=query(1,1,m,i,i),sum%=mo;//统计答案。
    cout<<sum;
    return 0;
}
```


---

