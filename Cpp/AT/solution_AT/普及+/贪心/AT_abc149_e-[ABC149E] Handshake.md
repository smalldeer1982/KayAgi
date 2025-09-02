# [ABC149E] Handshake

## 题目描述

Takahashi  作为特殊嘉宾参加一个晚会 , 晚会上还有 N 个非特殊嘉宾 , 第 i  个特殊嘉宾有 A_i  的欢乐值.晚会目前的欢乐值是 0 .  
 Takahashi  想跟非特殊嘉宾握 M  次手来提高晚会的欢乐值.每一次握手可以被描述为以下的操作:  
1.  Takahashi  选择两个非特殊嘉宾 x  和 y   
2.  Takahashi  用左手和 x  握手 , 用右手和 y  握手 , 晚会的欢乐值增加 A_x + A_y .    

然而 ,  Takahashi  不能以同一种握手方式握两次手.也就是说 ,  Takahashi  的 M  次握手必须满足以下条件:  
- 假设在第 k  次握手中 ,  Takashi  握了非特殊嘉宾 x_k  的左手和 y_k  的右手 , 则没有一组 p  ,  q  (  1 ≤ p < q ≤ M)  可以满足 (  x_p  ,  y_p  ) = (  x_q  ,  y_q  ) .  

请问:在 M  次握手后 , 晚会的欢乐值最大是多少 ?

## 样例 #1

### 输入

```
5 3
10 14 19 34 33```

### 输出

```
202```

## 样例 #2

### 输入

```
9 14
1 3 5 110 24 21 34 5 3```

### 输出

```
1837```

## 样例 #3

### 输入

```
9 73
67597 52981 5828 66249 75177 64141 40773 79105 16076```

### 输出

```
8128170```

# 题解

## 作者：NATO (赞：7)

首先，我们将题意做一个形式化的理解：

$\forall 1\le i,j\le n$，求 $a_i+a_j$ 前 $k$ 大值之和（**在这里加法存在顺序，即 $a_i+a_j$ 与 $a_j+a_i$ 算两种方案**）。

我们可以很轻松地发现一个结论：

$\forall i<j,a_i>a_j$ 的序列，小于等于 $a_1+a_1$ 的最大两两数之和必然是 $a_1+a_2$ 或 $a_2+a_1$，而小于等于 $a_1+a_2$ 的最大两两数之和又是在 $a_2+a_1,a_1+a_3,a_3+a_1,a_2+a_2$ 中产生的...以此类推。

我们可以得到一个朴素做法：

在选择了一个 $a_p+a_q$ 后，将 $a_{p-1}+a_q,a_q+a_{p-1},a_{q-1}+a_p,a_p+a_{q-1}$ 加入一个大根堆中，再在大根堆中取值，并继续加入上述值，做 $k$ 次即可。

可是复杂度 $O(k\log k)$，$n,k$ 不同阶，无法通过本题。

考虑我们在解决这道题时的“痛点”。

正是因为我们不知到选值的下界（选择所有大于等于该数的和后选择次数小于等于 $k$ 的最小数）是多少，我们才需要一次一次地去选择，如果我们知道选值的下界是多少，那么我们就可以对于每个 $a_i$ 去寻找和大于等于下界又最小的 $a_j$，将所有 $a_p\ge a_j$ 的值计入答案即可，而该操作我们可以在一个从大到小排好序的序列中 $i$ 从前往后扫，一个指针 $j$ 从后往前扫（由于 $\forall i,a_i\ge a_{i-1}$，那么 $a_{i-1}$ 时的 $j'\le j$ 才可能满足 $a_{i-1}+a_j'$ 大于等于选值的下界，故具有单调性），再加上前缀和可以 $O(n)$ 地完成对答案的统计。

那么我们考虑如何寻找选值的下界。

显然，枚举的选值的下界越大，可以选择的和越少，故选择次数关于选值下界具有单调性，可以二分选值下界进行检验，检验的时候就按上文两个指针扫，统计答案并统计选择次数来判断是否合法。

于是本题被我们以 $O(n\log n)$ 的复杂度解决。

**注意，由于本题存在一个和的值可能可以由多种和得出，故需要在检验时特判相等的情况（可参考代码中的实现）**。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define MOD 1000000007ll
#define MAXN 1000000000ll
using namespace std;
ll n,m;
ll a[100005],sum[100005],cs[100005];
ll cnt[100005];
bool cmp(ll a,ll b)
{
	return a>b;
}
ll check(ll ak)
{
	ll j=n,h=0,res=0,gs=0;
	for(ll i=1;i<=n;++i)
	{
		while(j&&a[j]+a[i]<ak)--j;
		h+=cs[j]*cnt[a[i]];res+=cs[j]*cnt[a[i]]*a[i]+cnt[a[i]]*sum[j];
		if(a[j]+a[i]==ak)gs+=cnt[a[j]]*cnt[a[i]];
	}
	if(h<=m)return res;
	if(h-gs<=m)return res-(h-m)*ak;
	return -1;
}//检验二分的选值下界
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(ll i=1;i<=n;++i)
	cin>>a[i],++cnt[a[i]];
	sort(a+1,a+1+n,cmp);
	ll tot=unique(a+1,a+1+n)-a-1;
	n=tot;
	for(ll i=1;i<=n;++i)sum[i]=sum[i-1]+a[i]*cnt[a[i]],cs[i]=cs[i-1]+cnt[a[i]];//离散化方便统计和等于选值下界的情况
	ll l=a[n]+a[n],r=a[1]+a[1],res=0;
	while(l<=r)
	{
		ll mid=l+r>>1;
		ll c=check(mid);
		if(c!=-1)r=mid-1,res=c;
		else l=mid+1;
	}
	cout<<res;
}
```


---

## 作者：louhao088 (赞：4)

二分答案

观察发现 $m$ 很大，不能直接暴力模拟。

我们考虑二分答案。

先对数据从大到小排序。

我们可以二分最小的那个我们取到的数。

然后对于每个数二分能取到的数的个数，判断是否多于 $m$。

因为我们发现会有相等情况，于是我们就统计比他大的和等于它的数。这样就可以判断第 $m$ 个数的大小然后用前缀和统计答案。

时间复杂度 $O(n \log^2 n)$

------------


代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	char ch=getchar();int x=0;bool f=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
const int maxn=1e5+5;
int x,n,m,a[maxn],sum[maxn],l,r,ans;
bool cmp(int x,int y){return x>y;}
int get1(int x)//第一个比x大
{
	int l=1,r=n,res=0;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(a[mid]>x)l=mid+1,res=mid;
		else r=mid-1;
	}return res;
}
int get2(int x)//第一个大于等于x 
{
	int l=1,r=n,res=0;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(a[mid]>=x)l=mid+1,res=mid;
		else r=mid-1;
	}return res;
}
bool check(int x)
{
	int num=0,s=0,res=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i]+a[1]<x)continue;
		else if(a[i]>=x)num+=n,res=res+sum[n]+n*a[i];
		else 
		{
			int u=get1(x-a[i]),v=get2(x-a[i]);
			num+=u;s+=v-u;res+=sum[u]+a[i]*u;
		}
	}
	if(num<=m&&num+s>=m)
	{
		ans=res+x*(m-num);cout<<ans;exit(0); 
	}
	if(num+s<=m)return true;
	else return  false;
}
signed main()
{
	freopen("hand.in","r",stdin);
	freopen("hand.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+a[i];
	int l=1,r=a[1]*2;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(check(mid))r=mid-1;
		else l=mid+1;
	}
	cout<<ans;
	return 0;
}

```






---

## 作者：TG_Space_Station (赞：1)

# 形式化题意
求前 $m$ 大的 $a_i+a_j(1 \le i,j \le n)$ 的和，$a_i+a_j$ 和 $a_j + a_i$ 算两组，但如题意当 $i=j$ 时，不能算作两组。
# 做法
对于这种判断正确性很方便，答案又具有单调性的题，我们可以考虑二分答案。  
但这题我使用的二分所得出的并不是题要我们求的。  
其实也可以二分题要我们求的，但不太方便。  
我们二分的 `check()` 函数求出 $\sum_{1 \le i,j \le n} [a_i+a_j \ge mid]$ 并判断该值是否 $\ge m$。($mid$ 的意义也就在这里了)。  
如果是，则说明可能 $mid$ 取小了或就是正确的，反之则说明取大了，这样进行下去使该值趋于 $m$，这样就符合只填加 $m$ 条边。  
怎么 `check()` 和获取答案呢，我们可以使用双指针 $O(n)$ 或 `lower_bound` $O(n \log{n})$。  
双指针在代码的 `check()` 里，`lower_bound` 在代码的获取答案里。  
剩下的细节看代码，我觉得我写的很清楚。
# [AC code](https://atcoder.jp/contests/abc149/submissions/44563460)

```cpp
#include <bits/stdc++.h>
using namespace std;

long long ans;
long long n, m;
long long l, r, mid;
long long a[100005];
long long suf[100005];//后缀和

bool check()
{
	long long p = n + 1, i, tot = 0;
	
	for(i = 1; i <= n; i++)
	{
		while(p >= 2 && a[i] + a[p - 1] >= mid)
			p--;

		tot += n - p + 1;
	}
	
	return tot >= m;
}

int main()
{
	//freopen("Ngraph.in", "r", stdin);
	//freopen("Ngraph.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	long long i;
	cin >> n >> m;
	
	for(i = 1; i <= n; i++)
		cin >> a[i];

	sort(a + 1, a + n + 1);
	l = 1, r = a[n] * 2;

	for(i = n; i >= 1; i--)
		suf[i] = suf[i + 1] + a[i];
	
	while(l <= r)
	{
		mid = (l + r) >> 1;
		
		if(check())
		{
			ans = mid;
			l = mid + 1;
		}
		else
			r = mid - 1;
	}
	
	long long res = 0, tot = 0;
	
	for(i = 1; i <= n; i++)//获取答案
	{
		long long p = lower_bound(a + 1, a + n + 1, ans - a[i]) - a;
		res += suf[p] + (n - p + 1) * a[i];
		tot += (n - p + 1);
	}
	
	cout << res - (tot - m) * ans;
	return 0;
}
```
做法是我独立完成的，第一篇题解，求过审。QwQ。

---

## 作者：Tx_Lcy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT4898)
## 思路
这题貌似是经典的二分？已经第三次看到这样的题目了，我们显然要二分第 $m$ 大的 $a_i+a_j$ 的值，统计答案可以在 $\verb!check!$ 的时候进行。

这个二分的 $\verb!check!$ 可以用双指针优化到 $O(n \log n)$，但是直接用 $\verb!lower_bound!$ 也不是不行，$n$ 只有 $10^5$，显然是可以过的。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define rint register int
using namespace std;
int const N=1e6+10;
int a[N],sum[N],n,m;
inline bool check(int x){
    int cnt=0;
	for(int i=1;i<=n;i++)
		cnt+=n-(lower_bound(a+1,a+n+1,x-a[i])-a)+1;
	return cnt>=m;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for (rint i=1;i<=n;++i) cin>>a[i];
    sort(a+1,a+n+1);
    for (rint i=1;i<=n;++i) sum[i]=sum[i-1]+a[i];
    int l=0,r=a[n]*2+1;
	while (l+1<r){
		int mid=(l+r)>>1;
		if (check(mid)) l=mid;
		else r=mid;
	}
    int cnt=0,ans=0,x=l;
    for (rint i=1;i<=n;++i){
        int to=lower_bound(a+1,a+n+1,x-a[i])-a;
        ans+=(sum[n]-sum[to-1]+a[i]*(n-to+1)),cnt+=n-to+1;
    }
    if (cnt>m) ans-=l*(cnt-m);
    cout<<ans<<'\n';
    return 0;
}

```


---

## 作者：普罗 (赞：1)

二分答案，先给happy值排序，然后假设所有两数和中第m大的数是ans，然后二分答案ans，找到后暴力算出前m大次握手所获得的值（或者用前缀和），最后要处理一下细节（二分答案出来的分界和实际后m次握手可能会有偏差）
```cpp
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
using namespace std;
long long ha[100005],total[100005];
int inc(const void *a, const void *b)
{
    if(a<b)return -1;
    else return 1;
}
int main()
{
	long long m,n,l=0,r=200005,fenjie,sum,num,mid,kk,temp;
	//fenjie:二分答案的结果 sum:握手好感总和 num:握手次数 kk: 临界点 temp:区别于fenjie的临时值 
    scanf("%lld%lld",&n,&m);
    ha[0]=9999999;
    for(long long i=1;i<=n;i++)scanf("%lld",&ha[i]);
    sort(ha+1,ha+n+1);
    total[0]=0;
    for(long long i=1;i<=n;i++)total[i]=total[i-1]+ha[i];
    mid=(l+r)/2;
    while(l<=r)
	{
        sum=0;num=0;
        for(long long i=1;i<=n;i++)
		{
            kk=lower_bound(&ha[1],&ha[n+1],mid-ha[i])-&ha[0];
            num+=n-kk+1;
        }
		temp=mid;
        if(num>=m)
		{
            fenjie=mid;
            l=mid+1;
        }
        else
		{
			//fenjie=mid;
			r=mid-1;
		}
        mid=(l+r)/2;
    }
    for(long long i=1;i<=n;i++)
	{
        kk=lower_bound(&ha[1],&ha[n+1],temp-ha[i])-&ha[0];
        sum+=total[n]-total[kk-1];
        sum+=ha[i]*(n-kk+1);
    }
    if(m==num)printf("%lld\n",sum);
    else if(m>num)printf("%lld\n",sum+(m-num)*fenjie);
    else printf("%lld\n",sum-(num-m)*fenjie);
}
```


---

## 作者：Meickol (赞：0)

由于 $1 \le M \le 10^{10}$，显然无法使用优先队列的做法。

基于题意，要使获得的总快乐值越高，那么自然要保证每次优先选择较大的快乐值。

我们可以想到使用二分答案加速统计选取操作的过程。

二分答案寻找一个 $x$，使得在有限次握手操作过程中都不会使用快乐值（即一对 $a_i+a_j$）比 $x$ 更小的数。



二分 `check` 函数中使用了 `lower_bound` 加速统计与当前 $a_i$ 可构成的 $a_i + a_j \ge x$ 的 $a_j$ 的个数。

最后基于贡献求答案，输出结果为 `ans+(m-cnt)*l`。



**最终代码**

```c++
#define rep(x,y,z) for(int x=y;x<=z;x++)
typedef long long LL;
const int N=1e5+5;
LL n,m;
int a[N];
LL prefix[N];
void solve(){
	cin>>n>>m;
	rep(i,1,n) cin>>a[i];
	sort(a+1,a+1+n);
	rep(i,1,n) prefix[i]=prefix[i-1]+a[i];
	LL cnt=0,ans=0;
	auto check=[&](int x){
		cnt=ans=0;
		rep(i,1,n){
			int pos=lower_bound(a+1,a+1+n,x-a[i])-a;
			cnt+=n-pos+1; //n-pos+1即满足 a_i+a_j≥x 这个式子的 a_j 的个数
			ans+=prefix[n]-prefix[pos-1]+(LL)(n-pos+1)*a[i]; //累加贡献
		}
		return cnt>=m;
	};
	int l=1,r=a[n]*2;
	while(l<r){
		int mid=l+r+1>>1;
		if(check(mid)) l=mid;
		else r=mid-1;
	}
	cout<<ans+(m-cnt)*l; //输出答案
}
```

双倍经验：[CF1996F Bomb](https://www.luogu.com.cn/article/9onkr6l1)

---

## 作者：Register_int (赞：0)

题意是求前 $m$ 大的 $a_i+a_j$ 之和。设第 $m$ 大的值为 $x$，则贡献有两种:

- 所有 $>x$ 的值之和。
- 与 $x$ 相等的值之和。

可以通过二分算出 $x$。因为排序后 $x-a_i$ 具有单调性，可以用双指针代替检查函数内的二分搜索，时间复杂度为 $O(n\log n)$。之后，统计 $>x$ 的权值之和，同时统计个数 $y$，将答案加上 $x(m-y)$ 即可。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e5 + 10;

int n, a[MAXN]; ll m, cnt, sum, s[MAXN];

inline 
bool check(int x) {
	cnt = 0;
	for (int i = n, j = 1; i; i--) {
		for (; j <= n && a[i] + a[j] <= x; j++);
		cnt += n - j + 1;
	}
	return cnt <= m;
}

int l = 0, r = 2e5, mid;

int main() {
	scanf("%d%lld", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	for (int i = n; i; i--) s[i] = s[i + 1] + a[i];
	for (; l < r; check(mid = l + r >> 1) ? r = mid : l = mid + 1);
	check(l), sum = (m - cnt) * l;
	for (int i = n, j = 1; i; i--) {
		for (; j <= n && a[i] + a[j] <= l; j++);
		sum += s[j] + (ll)a[i] * (n - j + 1);
	}
	printf("%lld", sum);
}
```

---

## 作者：_zexal_ (赞：0)

考虑二分。不妨我换一个问题问你，我给你一个数 $x$ 的情况下，问你在这个 $n \times n$ 的序列内部有多少个数满足大于它，我们不妨令这个个数为 $k$ 个。显然，你只需要对每一个行进行一个二分即可。接下来我们来看这道题，你就会发现，不就是反过来了吗？问题转换为给你 $k$ 这个数，问你多少个大于 $x$ 个数的和吗？我们考虑二分套二分枚举 $x$ 和检查答案，然后就搞完了。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define F(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int Maxn=2e5+5;
int n,m,a[Maxn],sum[Maxn],Max,ans,fck=0,mid;
bool cmp(int x,int y){
	return x>y;
}
signed main(){
	cin>>n>>m;
	F(i,1,n){
		cin>>a[i];
		Max=max(Max,a[i]*2);
	}	
	sort(a+1,a+n+1);
	F(i,1,n){
		sum[i]=sum[i-1]+a[i];
	}
	int l=1,r=Max;
	while(l<=r){
		mid=l+r>>1;
		ans=0,fck=0;
		for(int i=1;i<=n;i++){
			int	k=lower_bound(a+1,a+n+1,mid-a[i])-a;
			fck+=n-k+1;
			ans+=sum[n]-sum[k-1]+a[i]*(n-k+1);
		}
		if(fck>=m) l=mid+1;
		else r=mid-1;
	//	cout<<mid<<endl;
	}
	cout<<ans-(fck-m)*(l-1)-1;
	return 0;
}
 
```


---

## 作者：StevenLiTheOIer (赞：0)

## 思路：
直接模拟握手的过程会超时，我们只能二分答案。因为按照贡献从大到小握手一定是最优的，所以将 $a$ 排序后二分我们最后握手到的人的贡献（即第 $n^2-m+1$ 大的贡献值），最后输出时减去多算的即可。
## Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, m, cnt, ans, a[100006], sum[100006];
bool check(long long x)
{
	cnt = ans = 0;
	for (int i = 1; i <= n; i++)
	{
		int pos = lower_bound(a + 1, a + n + 1, x - a[i]) - a; //因为贡献为 x，第 i 人已经贡献了 a[i]，所以另一人的贡献为 x - a[i] 
		cnt += n - pos + 1;
		ans += sum[n] - sum[pos - 1] + a[i] * (n - pos + 1); //前缀和统计答案 
	}
	return cnt <= m;
}
int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++)
		sum[i] = sum[i - 1] + a[i];
	long long l = 1, r = 2 * a[n];
	while (l <= r) //二分答案 
	{
		long long mid = l + r >> 1;
		if (check(mid)) r = mid - 1;
		else l = mid + 1;
	}
	cout << ans - (cnt - m) * r << endl; //减去多余的 
	return 0;
}
```

---

## 作者：code_hyx (赞：0)

这道题的暴力思路很好想：求出所有的和，选出最大的 $n$ 个，排序或用优先队列维护都可以。  
但是 $N\le10^5$ ，会超时。  
于是考虑二分。  
用二分法找到第 $n^2-m+1$ 大的数即可。  
怎么求呢？先要二分单次操作的欢乐值 $mid$ ，然后计算握多少次手，可以用一个前缀和快速求和。  
代码：
```
#include<bits/stdc++.h>
using namespace std;
long long n,m,a[100005],ans=0,sum[100005],maxx=0;
int main()
{
	//freopen("party.in","r",stdin);
	//freopen("party.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		maxx=max(maxx,2*a[i]);
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	{
		sum[i]=sum[i-1]+a[i];
	}
	long long ans=0,cnt=0,mid,l=0,r=2*maxx;
	while(l<r)
	{
		ans=0;
		cnt=0;
		mid=(l+r+1)/2;
		for(int i=1;i<=n;i++)
		{
			long long k=lower_bound(a+1,a+n+1,mid-a[i])-a;
			cnt+=n-k+1;
			ans+=sum[n]-sum[k-1]+a[i]*(n-k+1);
		}
		if(cnt>=m)l=mid;
		else r=mid-1;
	}
	cout<<ans-(cnt-m)*l;
	return 0;
}  
```


---

