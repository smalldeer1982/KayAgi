# [LMXOI Round 2] Disaster

## 题目背景

LMX 和 HQZ 在一起研究点的划分。

## 题目描述

给定 $n$ 个点，每个点给出了一组限制 $l_i,r_i(0 \le l_i < i < r_i \le n+1)$，定义一个划分是好的当且仅当对于每个点 $i$，$l_i,r_i$ 在划分后均不与 $i$ 在同一区间内，求好的划分的个数，答案对 $998244353$ 取模。

补充：在本题中，一组划分表示将 $n$ 个点分为若干个区间，使得每个点恰好在一个区间内，$l_i=0$ 和 $r_i=n+1$ 可以视为无限制。

## 说明/提示

**样例解释 #1**

样例的 $8$ 种合法划分区间分别是：

$[1,2],[3,5]$

$[1,1],[2,2],[3,5]$

$[1,2],[3,3],[4,5]$

$[1,1],[2,2],[3,3],[4,5]$

$[1,2],[3,4],[5,5]$

$[1,1],[2,2],[3,4],[5,5]$

$[1,2],[3,3],[4,4],[5,5]$

$[1,1],[2,2],[3,3],[4,4],[5,5]$




对于所有数据，$1 \le n\le  2 \times 10^6$，$0 \le l_i < i < r_i \le n+1$。

| 子任务编号 |        $n$         |    特殊性质    | 分值 |
| :--------: | :----------------: | :------------: | :--: |
| Subtask #1 |      $\le 20$      |       无       |  $5$   |
| Subtask #2 |     $\le 500$      |       无       |  $10$  |
| Subtask #3 |     $\le 5000$     |       无       |  $20$  |
| Subtask #4 |     $\le 5 \times 10^5$     | $l_i=0$ |  $10$   |
| Subtask #5 |     $\le 5 \times 10^5$     |无 |  $25$  |
| Subtask #6 |     $\le 2 \times 10^6$     |无 |  $30$  |

## 样例 #1

### 输入

```
5
0 3
0 3
1 6
2 6
2 6```

### 输出

```
8```

# 题解

## 作者：Li00000 (赞：11)

考虑 dp，记 $f_i$ 表示以 $i$ 结尾的方案数，枚举右端点 $R$，找到所有合法区间 $[L,R]$，有转移：
$$f_R=\sum\limits_{L}f_{L-1}$$

考虑题目限制的影响：

- 当 $R<i$ 时，对 $L$ 没有影响。

- 当 $i\le R< r_i$ 时，要求 $L>l_i$。

- 当 $r_i\le R$ 时，要求 $L>i$。

对于每个右端点 $R$，可转移的 $L$ 是以 $R$ 为右端点的一段区间，所以对影响取 $\max$ 找到所有可转移的 $L$，用前缀和优化 dp 转移即可。

时间复杂度 $O(N)$。

## Code

```cpp
#include<bits/stdc++.h>
#define N 2000005
using namespace std;
int n;
int f[N],sum[N];
int mx[N];
int p=1;
const int mod=998244353;
inline int read(){
    int x=0;char ch=getchar();
    while(!isdigit(ch)) ch=getchar();
    while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x;
}
inline int Max(int x,int y){return (x>y)?x:y;}
inline int M(long long x){return (x<mod)?x:x-mod;}
int main(){
    n=read();
    for(int i=1,l,r;i<=n;++i){
        l=read();r=read();
        mx[r]=Max(mx[r],i+1);
        mx[i]=Max(mx[i],l+1);
    }
    f[0]=sum[0]=1;
    for(int i=1;i<=n;++i){
        p=Max(p,mx[i]);
        f[i]=sum[i-1];
        if(p-2>=0) f[i]=M(M(1ll*f[i]-sum[p-2]+mod));
        sum[i]=M(1ll*sum[i-1]+f[i]);
    }
    printf("%d",f[n]);
    return 0;
}
```

---

## 作者：__Chx__ (赞：7)

对于划分个数，考虑动态规划，设 $f_i$ 表示 $[1,i]$ 好的划分的个数，那么我们对于每个合法区间 $[L,R]$，有转移 $f_R=f_R+f_{L-1}$，发现合法区间 $[L,R]$ 满足：

$$\max\limits_{i=L}^{R}l_i<L~\wedge~\min\limits_{i=L}^{R}r_i>R$$

暴力找合法区间并转移可以做到 $O(n^2)$ 的复杂度。

发现如果 $[i,R]$ 是一个合法区间，那么 $[i+1,R]$ 也一定是一个合法区间，所以以每个 $i$ 作为左端点时，其对应的所有合法区间中最大的 $R$ 是单调不降的。

那么就可以预处理出每个 $i$ 对应的最大合法左端点 $R_i$，并进行转移：

$$f_j \gets f_j+f_{i-1}~(j\in [i,R_i])$$

预处理 $R_i$ 时可以使用单调栈维护最小的 $r_i$，转移可以使用差分或前缀和优化从而达到 $O(n)$ 的复杂度，同时数据也放掉了部分 $O(n \log n)$ 的数据结构做法。

~~本题解实现比较繁琐，不建议参考。~~ 更简短的实现可以参考[这一篇代码](https://www.luogu.com.cn/article/skmzr3el)。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+5,mod=998244353;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-48,ch=getchar();}
	return x*f;
}
int n,l[N],r[N],maxr[N],f[N],mr;
int L,R;
pair<int,int> s[N];

inline void Add(int &x,int y){(x+=y)>=mod?x-=mod:0;}

int main(){
	n=read();
	for(int i=1;i<=n;++i) l[i]=read(),r[i]=read();
	L=0,R=1,mr=0;
	for(int i=1;i<=n;++i){
		while(L<=R&&s[L].second<i) ++L;//删掉过期的点
		if(mr==i-1) s[++R]={r[i],i},mr=i;//maxr_i的值至少为i
		while(mr<n&&mr+1<s[L].first&&l[mr+1]<i){//扩展maxr
			++mr;
			while(L<=R&&s[R].first>r[mr]) --R;//单调栈
			s[++R]={r[mr],mr};
		}
		maxr[i]=mr;//记录maxr
	}
	f[1]=1,f[maxr[1]+1]=mod-1;
	for(int i=1;i<n;++i){//差分转移
		Add(f[i],f[i-1]);
		Add(f[i+1],f[i]);
		Add(f[maxr[i+1]+1],mod-f[i]);
	}
	printf("%d",(f[n-1]+f[n])%mod);
	return 0;
}
```

---

## 作者：L_zaa_L (赞：5)

我们很容易写出暴力的代码，就是记录一个 $f_x$，表示分段分到 $x$ 的时候的方案数，然后可以对于一个 $i$，直接枚举一个合法区间 $(i,j)$，让 $f_j+=f_{i-1}$，这个的时间复杂度是 $O(n^2)$ 的。

首先我们可以发现一个性质就是，假如 $(l,r)$ 是一个合法的区间，那么 $(l+1,r),(l,r-1)$ 都应该是合法的区间。

那么对于一个左端点 $l$ 所能最大能达到的右端点为 $r$，$l+1$ 所能达到的最右端的位置 $\ge r$，所以每个 $l$ 需要更新的区间是可以 $O(n)$ 计算出来的。

那么我们就可以用 $f_l$ 直接去更新 $f_{l+1\sim r}$，这个可以直接用树状数组维护，然后每次拓展右端点，这个可以用 ST 表判断是否可以拓展，时间复杂度 $O(n\log n)$。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define ls(x) ((x)*2)
#define rs(x) ((x)*2+1)
#define Debug(...) fprintf(stderr, __VA_ARGS__)
#define For(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define Rof(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define rep(i,  b) for(int i=1,i##end=b;i<=i##end;i++)
using namespace std;
const int N=2e6+5,Mod=998244353;
//char buf[(1<<21)+5],*p1,*p2;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline void chmx(int &x,int y){(x<y)&&(x=y);}
inline void chmn(int &x,int y){(x>y)&&(x=y);}
//inline void Add(int &x,int y){(x=x+y+Mod)%Mod;}
typedef __int128_t i128;
i128 _base=1;
inline int mol(int x){return x-Mod*(_base*x>>64);}
inline int read(){
	int f=0,x=0;
	char ch=getchar();
	while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f?-x:x;
}
int n;
int ll[N],rr[N];
int ans=0;
int dp[N],lg[N],f[N][21]; 
inline int qryST(int l,int r){
	if(r<l) return 1e16;
	int k=lg[r-l+1]-1;
	return (min(f[l][k],f[r-(1<<(k))+1][k])==0?1e16:min(f[l][k],f[r-(1<<(k))+1][k]));
}
inline void GetST(){
//	memset(f,0x3f,sizeof(f));
	For(i,1,n){
		f[i][0]=rr[i];
		lg[i]=lg[i>>1]+1;
	}
	For(i,1,20)For(j,1,n)
		if(j+(1<<(i-1))<=n)f[j][i]=min(f[j][i-1],f[j+(1<<(i-1))][i-1]);
} 
int tr[N];
inline int lowbit(int x){return x&(-x);}
inline void updata(int x,int k){if(x==0){tr[x]+=k;return;}while(x<=n){tr[x]+=k;(tr[x]+=Mod)%=Mod;x+=lowbit(x);}}
inline int query(int x){int res=tr[0];while(x){res+=tr[x];(res+=Mod)%=Mod;x-=lowbit(x);}return res;}
inline void solve(){
	n=read();
	For(i,1,n) ll[i]=read(),rr[i]=read();
	GetST();
	updata(0,1);
	updata(1,-1);
	int R=0;
//	cout<<qryST(2,2)<<endl;
	For(i,1,n) {
		int L=i,maxx=qryST(L,R); 
//		cout<<maxx<<" ";
		while(R+1<maxx&&ll[R+1]<L&&R<n) R++,maxx=min(rr[R],maxx);
		int x=query(i-1);
//		cout<<x<<endl;
		updata(i,x);
		updata(R+1,-x);
//		cout<<maxx<<" "<<L<<" "<<R<<endl;;
	}
	cout<<query(n);
}
signed main(){
	_base=(_base<<64)/Mod;
//	freopen("test.in","r",stdin);
//	freopen("std.out","w",stdout);
	// ios::sync_with_stdio(false);
	// cin.tie(0); cout.tie(0);
	int T=1;
	while(T--){solve();}
#ifdef LOCAL
    Debug("\nMy Time: %.3lfs\n", (double)clock() / CLOCKS_PER_SEC);
#endif
	return 0;
}
```

---

## 作者：哈哈人生 (赞：3)

## 题外话
### [题目传送门](https://www.luogu.com.cn/problem/P10807)

其实这题我第一眼还以为是组合数。

## 思路
考虑动态规划。设 $f_i$ 表示满足前 $i$ 个限制的方案数，则有 $f_i=\sum_{j=L}^{i-1}$，其中 $L$ 为最小的满足点 $L$ 到点 $i$ 满足限制的点的编号。考虑更新 $f_i$ 的 $L$ 需要满足什么条件，不难得出如下结论：
1. $L\ge \max_{j=1}^{i} l_i$。
2. $L\ge \max_{j=1}^{i} j\times [r_j\le i]$。

这其实就是把题目要求的限制反过来想了一下，把对于 $i$，$l_i,r_i$ 的限制变成了对于 $l_i,r_i$，$i$ 的限制。

暴力枚举转移的话时间复杂度是平方级别的，不能通过。代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353; 
int n,l[2000005],r[2000005],f[2000005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>l[i]>>r[i];
	f[0]=1;
	int maxx=0;
	for(int i=1;i<=n;i++){
		maxx=max(maxx,l[i]);
		for(int L=i-1;L>=maxx;L--){
			f[i]+=f[L];
			f[i]%=mod;
			if(r[L]<=i)break;
		}
	}
	cout<<f[n];
	return 0;
}
```
发现我们枚举 $i$ 是单调递增的，所以考虑维护 $r_i$ 的单调性，快速查找 $L$，即通过单调队列转移，时间复杂度就成功降至线性了。至于求和可以用前缀和优化。

## 正解代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353; 
int n,l[2000005],r[2000005],f[2000005],sum[2000005];
int q[2000005],h=0,t=-1;
int query(int l,int r){
	if(l!=0)return sum[r]-sum[l-1];
	else return sum[r]+1;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>l[i]>>r[i];
	f[0]=1;
	r[++t]=0;
	int maxx=0;
	for(int i=1;i<=n;i++){
		maxx=max(maxx,l[i]);
		while(h+1<=t&&r[q[h+1]]<=i)h++;
	    f[i]=query(max(maxx,q[h]),i-1);
	    f[i]%=mod;
		sum[i]=sum[i-1]+f[i];
		while(h<=t&&r[q[t]]>=r[i])--t;
		q[++t]=i;
	}
	cout<<f[n];
	return 0;
}
```

---

## 作者：_Hzx_ (赞：2)

【**解法**】

题意挺简单，就不赘述。

考虑 dp。

首先看下每个点后面最近的一个点能不能在同一区间内，更一般的，就是看这两个点在同一区间内是否冲突。并记录下来。

dp 转移方程式为见下：

$$ dp_i = \sum _ {j = i} ^ {k_i - 1} dp_{j + 1}$$

其中的 $k_{i-1}$ 表示第 $i - 1$ 个点后面第一个会在同一区域相冲突的前一项。

完成转移时间复杂度为 $O(n^2)$。

考虑优化，求和操作就十分明显，不难想到使用前缀和优化。这样，时间复杂度为 $O(n)$，即可通过此题。

初始化 $dp_{n + 1}$ 为 $1$。因为至少会有一种方案。

----

【**核心代码**】

dp 转移的代码。

```cpp
for (int i = n; i >= 1; i--) {
	dp[i] = ((s[i + 1] - s[k[i] + 1]) % mod + mod) % mod;
	s[i] = s[i + 1] + dp[i];
	s[i] %= mod;
}
```

前缀和应该都会写，注意取模即可。

---

## 作者：zjj2024 (赞：2)

### 思路

记录每个点最近和哪个在它后面的点不能在同一区间内。

考虑动态规划。记第 $i$ 个点后面最近的在同一区间内有冲突的点前一项为 $v_i$。状态转移方程为：

$$
f_i=\sum_{j=i}^{v_i-1}f_{j+1}
$$

一开始时设 $f_{n+1}=1$。

考虑使用前缀和。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2000005,MOD=998244353;
typedef long long ll;
ll f[N],n,v[N],s[N];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	ll l,r;
	for(int i=1;i<=n;i++)v[i]=n+1;//一开始设为没有条件
	for(ll i=1;i<=n;i++)
	{
		cin>>l>>r;
		if(l)v[l]=min(v[l],i);//i<r不用考虑l和r的情况
		if(r<=n)v[i]=min(v[i],r);
	}
	for(int i=n-1;i>=1;i--)v[i]=min(v[i],v[i+1]);//的到每一个v[i]，需要考虑到后面的点有冲突的情况
	f[n+1]=1;//初始化
	s[n+1]=1;
	for(int i=n;i>=1;i--)
	{
		f[i]=((s[i+1]-s[v[i]+1])%MOD+MOD)%MOD;//进行取模
		s[i]=s[i+1]+f[i];//用s数组记录前缀和
		s[i]%=MOD;
	}
	cout<<f[1]<<'\n';
	return 0;
}
```

---

## 作者：lzt415 (赞：1)

# 洛谷 P10807
## 题外话
本蒟蒻是通过大佬 @Immunoglobules 的思路做出来的，所以可能各方面比较像，勿喷。
## 题目大意
给你 n 个点，并告诉你每个点的限制区间 $l_i ,r_i$，要求一个合法的划分，使得每个点 $i$ 在划分后与 $l_i$ 和 $l_i,r_i$ 两者皆不冲突，需要计算所有合法的划分方式数量。
## 思路
考虑使用 DP，~~废话，标签上写的~~。我们不妨设一个 $f$ 数组，其中 $f_i$ 表示从第 $i$ 个点开始的所有合法划分的数量。在设一个前缀和数组，其中 $s_i$ 表示从第 $f_i$ 个点到最后一个点 $f_n$ 的值的和，表示为
$$
s_i = \sum_{k = i}^{n+1} f_i
$$
那么如何得出状态转移方程呢？

我们要知道 $f_i$ 表示从 $i$ 开始的合法划分的数量，那么其为由 $f_i+1$ 开始的合法划分去掉一些不合法的划分。故其转移方程为：
$$
f_i = s_i - s_{v_i+1}
$$
注：公式中的 $v_i$ 是从点 $i$ 开始的合法区间的结束点。

好，既然知道了最重要的转移方程，那么 DP 从什么时候开始呢（边界条件）？  
一个 DP 的边界条件一般是一个确定的 $f$ 数组某一个确定的初始值，很显然，这个特殊的值就是 $f_{n+1}$ 虽然它并不存在，但因为它只有一种肯定的情况，那就是不进行任何划分是其唯一的划分，则 $f_{n+1} = 1$。 
## code time

```
#include <bits/stdc++.h>//万能头 
using namespace std;
const int maxn = 2e6+5,mod = 998244353;
typedef long long ll;
ll f[maxn],v[maxn],s[maxn];
inline ll read()
{
	ll f=1,k=0;
	char c;
	c=getchar_unlocked();
	while(c<'0'||c>'9')
	{
		if(c=='-') f=-1;
		c=getchar_unlocked();//一个小小的优化，比getchar快,有的编译器可能过不了 
	}
	while(c>='0'&&c<='9')
	{
		k=k*10+c-'0';
		c=getchar_unlocked(); 
	}
	return f*k;
}//不懂快读的可以去看看 P10815【模板】快速读入 这道题 
int main() 
{
    ll n;
    n=read();
    for(int i=1;i<=n;i++) v[i]=n+1;//注意，don't use memset，本蒟蒻就栽了一次 
    for(ll i = 1; i <= n; i++) 
	{
        ll l, r;
    	l=read(),r=read();
        if (l) v[l] = min(v[l], i); 
        if (r <= n) v[i] = min(v[i], r);
    }
    for(ll i = n - 1; i >= 1; i--) 
	{
        v[i] = min(v[i], v[i + 1]); 
    }
    f[n + 1] = s[n + 1] = 1;
    for (ll i = n; i >= 1; --i) //上面讲了 
	{ 
        int temp = s[i + 1] - s[v[i] + 1];  
        temp = (temp % mod + mod) % mod;  
        f[i] = temp;
        s[i] = (s[i + 1] + f[i]) % mod;  
    }
    cout << f[1] << endl;
    return 0;
}
```

---

## 作者：_LTC_Augenstern_ (赞：1)

根据题意，容易考虑到线性$~$dp。

对于$~dp_i$，我们定义状态为以$~i~$为结尾的最优方案。接下来考虑状态转移。对于元素$~x$，有状态转移公式：

$$~dp_x = \sum_{i=x}^{k_{x-1}}dp_i+1$$

其中，$k_{x-1}~$表示第$~i-1~$个点后面第一个会在同一区域相冲突的前一项。

所以我们需要做一个前缀和然后就可以直接带入状态转移方程了。

具体实现：
```cpp
#include <bits/stdc++.h>
#define endl "\n"
#define IOS ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;
typedef long long ll;
const ll mod = 998244353;
ll n, x, y, now = 1, dp[2000010], sum[2000010], nums[2000010];
int main()
{
	IOS;
	cin >> n;
	for(ll i = 1; i <= n; i ++)
	{
		cin >> x >> y;
		nums[y] = max(nums[y], i + 1) % mod;
		nums[i] = max(nums[i], x + 1) % mod;
	}
	dp[0] = sum[0] = 1;
	for(ll i = 1; i <= n; i ++)
	{
		now = max(now, nums[i]);
		dp[i] = sum[i - 1] % mod;
		if(now >= 2) dp[i] = ((dp[i] - sum[now - 2] + mod) % mod) % mod;
		sum[i] = ((sum[i - 1] + dp[i] + mod) % mod) % mod;
	}
	cout << dp[n];
	return 0;
}
```

---

## 作者：Lyco_Reco (赞：1)

提供一种 $O(n\log{n})$ 的做法。

我们不妨先考虑 $O(n^2)$ 的朴素 dp，设 $dp_i$ 表示前 $i$ 个点的划分方案数，根据题意可以写出状态转移方程：
$$
dp_i \leftarrow dp_i+dp_j 
$$
其中 $j$ 满足
$$
\max_{k=j+1}^{i}\ l_k <j+1 \land \min_{k=j+1}^{i}\ r_k > i
$$
注意到转移条件中含有区间最值，使用 ST 表预处理即可做到 $O(1)$ 查询。

另外，不难发现转移条件是具有单调性的，因此合法的 $j$ 的集合一定是以 $i$ 为右端点的连续的一段，使用二分找到这个连续段的左端点 $l$，再使用前缀和技巧快速求出 $\sum_{k=l}^i dp_k$，即可做到 $O(\log{n})$ 转移，总时间复杂度 $O(n\log{n})$。

```cpp

	int n,lg[maxn],l[maxn],r[maxn],f[2][maxn][21],dp[maxn],s[maxn];
    inline int _max(int x,int y){
		return x>y? x:y;
	}
	inline int _min(int x,int y){
		return x<y? x:y;
	}
	inline int ask_mx(int l,int r){
		int k=lg[r-l+1];
		return _max(f[0][l][k],f[0][r-(1<<k)+1][k]);
	}
	inline int ask_mn(int l,int r){
		int k=lg[r-l+1];
		return _min(f[1][l][k],f[1][r-(1<<k)+1][k]);
	}
	signed main(){
		n=rd();
		rep(i,2,n){
			lg[i]=lg[i>>1]+1;
		}
		rep(i,1,n){
			l[i]=rd(),r[i]=rd();
			f[0][i][0]=l[i];
			f[1][i][0]=r[i];
		}
		rep(j,1,lg[n]){
			rep(i,1,n-(1<<j)+1){
				f[0][i][j]=_max(f[0][i][j-1],f[0][i+(1<<j-1)][j-1]);
				f[1][i][j]=_min(f[1][i][j-1],f[1][i+(1<<j-1)][j-1]);
			}
		}
		dp[0]=1;
		s[0]=1;
		rep(i,1,n){
			int l=-1,r=i;
			while(l+1<r){
				int mid=l+r>>1;
				if(ask_mx(mid+1,i)<mid+1&&ask_mn(mid+1,i)>i){
					r=mid;
				}
				else{
					l=mid;
				}
			}
			dp[i]+=(s[i-1]-(r-1>=0? s[r-1]:0)+mod)%mod;
			if(dp[i]>=mod){
				dp[i]-=mod;
			}
			s[i]=s[i-1]+dp[i];
			if(s[i]>=mod){
				s[i]-=mod;
			}
		}
		wrt(dp[n]);
		return 0;
	}
```

---

## 作者：Night_sea_64 (赞：0)

~~场上就我一个多带 log 做的吗~~

把每个限制都存在右边的那个点上。显然每个点只需要知道存在它那里的最靠右的限制就行了，因为段是连续分的。下面提到的「$i$ 的限制」都指的是存在 $i$ 这里最右边的限制。

然后看着就是 dp 了。设状态 $f_i$ 表示以 $i$ 为某一段结尾的合法方案数。这都是基操。然后转移的时候枚举上一段的结尾在哪里，挨个加上答案。

这肯定需要优化。观察到 $i$ 的上一段结尾可以是 $j$，当且仅当 $j+1$ 到 $i$ 中间所有点的限制都在 $j$ 之前。于是很自然地想到 st 表维护这段区间内的位置的最靠右的限制，并且二分求出最左边的 $j$。

最后维护前缀和来优化。时间和空间复杂度均为 $O(n\log n)$。

```cpp
#include<iostream>
using namespace std;
const int mod=998244353;
int n,maxl[2000010],f[2000010];
int st[2000010][25],lg[2000010];
int s[2000010];
int read()
{
    char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    int num=0;
    while(c>='0'&&c<='9')num=num*10+(c-'0'),c=getchar();
    return num;
}
void pre()
{
    lg[0]=-1;
    for(int i=1;i<=n;i++)lg[i]=lg[i>>1]+1;
    for(int i=1;i<=n;i++)st[i][0]=maxl[i];
    for(int k=1;(1<<k)<=n;k++)
    {
        int len=(1<<k);
        for(int l=1;l+len-1<=n;l++)
            st[l][k]=max(st[l][k-1],st[l+(len>>1)][k-1]);
    }
}
int query(int l,int r)
{
    int k=lg[r-l+1];
    return max(st[l][k],st[r-(1<<k)+1][k]);
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    n=read();
    for(int i=1;i<=n;i++)
    {
        int x,y;
        x=read(),y=read();
        maxl[i]=max(maxl[i],x);
        maxl[y]=max(maxl[y],i);
    }
    pre();
    f[0]=s[0]=f[1]=1,s[1]=2;
    for(int i=2;i<=n;i++)
    {
        int l=1,r=i,pos=0;
        while(l<=r)
        {
            int mid=(l+r)/2;
            if(query(mid,i)<mid)r=mid-1,pos=mid;
            else l=mid+1;
        }
        if(pos==1)f[i]=s[i-1];
        else f[i]=(s[i-1]+mod-s[pos-2])%mod;
        s[i]=(s[i-1]+f[i])%mod;
    }
    cout<<f[n]<<endl;
    return 0;
}
```

---

## 作者：lbmzxhb (赞：0)

[题目传送门](/problem/P10807)

# 思路：

看到题目很容易想到计数 dp。令 $dp_i$ 为前 $i$ 个数中好的划分的方案数，则状态转移方程如下：

$$dp_i=\sum_{j=x_i}^i dp_{j-1}$$

其中 $x_i$ 表示同时满足 $\max\limits_{j=x_i}^il_j<x_i$ 和 $\min\limits_{j=x_i}^ir_j>i$ 的最小值。（说人话就是能使 $x_i$ 与 $i$ 划分到一起的最小值）

但直接暴力转移是 $\mathcal O(n^2)$ 的，于是考虑优化。

注意到 $x_i$ 一定是单调不降的，于是考虑维护一个滑动窗口和分别维护 $\max l_j$ 和 $\min r_j$ 的单调队列，对于不合法的进行弹出，最后用前缀和优化 $dp$ 即可。

时间复杂度 $\mathcal O(n)$。

# 代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
template<typename T>void read(T&a){int f=1;a=0;char c;for(c=getchar();c<'0'||'9'<c;c=getchar())if(c=='-')f=-1;for(;'0'<=c&&c<='9';c=getchar())a=(a<<1)+(a<<3)+(c^48);a*=f;}
template<typename T, typename ...A>void read(T&a,A&...b){read(a),read(b...);}
template<typename T>void _o(T a){if(a>9)_o(a/10);putchar(a%10|48);}
template<typename T>void out(T a){if(a<0)putchar('-'),a=-a;_o(a);}
template<typename T, typename ...A>void out(T&a,A&...b){out(a),putchar(' '),out(b...);}
const int N(2e6 + 5), P(998244353);
int n, l[N], r[N];
int dp[N], s[N];//普通前缀和会有下标出现-1的情况，所以以下的下标都加了1
int upd(int x) {return (x%P+P)%P;}
deque<int> le, ri;
inline int sum(int l, int r) {return s[r + 1] - s[l];}
void work() {
	read(n);
	for (int i = 1; i <= n; i++) read(l[i], r[i]);
	dp[0] = s[1] = 1;
	for (int i = 1, j = 1; i <= n; i++) {
		while (ri.size() && r[ri.back()] > r[i]) ri.pop_back(); ri.push_back(i);
		while (le.size() && l[le.back()] < l[i]) le.pop_back(); le.push_back(i);
		for (; ri.size() && le.size() && !(r[ri.front()] > i && j > l[le.front()]); j++) {
			if (ri.front() == j) ri.pop_front();
			if (le.front() == j) le.pop_front();
		}
		dp[i] = upd(sum(j - 1, i - 1));
		s[i + 1] = upd(s[i] + dp[i]);
	}
	out(dp[n]);
}
signed main() {
	int T(1);
	while(T--) work();
	return 0;
}
```

---

