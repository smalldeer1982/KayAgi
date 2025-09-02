# Let's Go Rolling!

## 题目描述

On a number axis directed from the left rightwards, $ n $ marbles with coordinates $ x_{1},x_{2},...,x_{n} $ are situated. Let's assume that the sizes of the marbles are infinitely small, that is in this task each of them is assumed to be a material point. You can stick pins in some of them and the cost of sticking in the marble number $ i $ is equal to $ c_{i} $ , number $ c_{i} $ may be negative. After you choose and stick the pins you need, the marbles will start to roll left according to the rule: if a marble has a pin stuck in it, then the marble doesn't move, otherwise the marble rolls all the way up to the next marble which has a pin stuck in it and stops moving there. If there is no pinned marble on the left to the given unpinned one, it is concluded that the marble rolls to the left to infinity and you will pay an infinitely large fine for it. If no marble rolled infinitely to the left, then the fine will consist of two summands:

- the sum of the costs of stuck pins;
- the sum of the lengths of the paths of each of the marbles, that is the sum of absolute values of differences between their initial and final positions.

Your task is to choose and pin some marbles in the way that will make the fine for you to pay as little as possible.

## 样例 #1

### 输入

```
3
2 3
3 4
1 2
```

### 输出

```
5
```

## 样例 #2

### 输入

```
4
1 7
3 1
5 10
6 1
```

### 输出

```
11
```

# 题解

## 作者：基地A_I (赞：4)

## 前言

这题还是有点意思的。

**题意**： 给你 $n$ （$n<=3000$）  个弹珠，它们位于数轴上。给你弹珠的坐标 $x_i$ 在弹珠 $i$ 上面花费 $C_i$ 的钱 可以使弹珠在原地不动 ($-10^9<=x_i,C_i<=10^9$)，游戏开始时，所有的弹珠向左滚动，直到碰到定在原地不动的弹珠，其花费是其滚动的距离。总花费=开始前的花费+弹珠滚动的花费，问最小的花费是多少

## 题解

首先划分出阶段,，我们可以先将弹珠排序，前 $i$ 个弹珠，最后一个固定的弹珠是 $j$ $(j<i)$

$=>$ 设 $f_{i,j}$ 表示 前 $i$ 个弹珠，最后一个固定的弹珠是 $j$ $(j<i)$ 的最小花费

可以这样想，当最后一个定点 $j$ 在 $i$ 时，是不是就要在 $i$ 的前面找到一个最小的定点继承 所以要找 $1<=k<i$ 中 $f_{i-1,k}$ 最小的这个点，然后加上定 $i$ 点的花费 

而当最后一个定点 $j$ 不在 $i$ 时 只要在 $f_{i-1,j}$ 的基础上加上点 $i$ 到点 $j$ 的距离  
 
转移：

- $f_{i,j}=\min\{f_{i-1,k}\} + C_i (i==j)$

- $f_{i,j}=f_{i-1,j}+x_i-x_j (j<i)$

Code

```cpp
// int下INF=0x3f3f3f3f
// long long 下 INF=1e19 
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cmath>
#define int long long
#define INF 1e19
using namespace std;
inline int read() {
	int x=0,f=1; char ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') { x=(x<<3)+(x<<1)+(ch^48); ch=getchar(); }
	return x * f;
}
const int N = 3007;
int n;
int f[N][N];
struct Marbles {	//弹珠 
	int x,c;
}a[N];
bool cmp(Marbles x,Marbles y) {
	return x.x < y.x;
}
signed main()
{
	n = read();
	for(int i=1;i<=n;++i)
		a[i].x = read(), a[i].c = read();
	sort(a+1, a+1+n, cmp);
	int minn;
	f[1][1] = a[1].c;
	for(int i=2;i<=n;++i) {
		minn = INF;
		for(int j=1;j<i;++j) {
			f[i][j] = f[i-1][j] + a[i].x - a[j].x;
			minn = min(minn, f[i-1][j]);
		}
		f[i][i] = minn + a[i].c;
	}
	int ans = INF;
	for(int i=1;i<=n;++i)
		ans = min(ans, f[n][i]);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Special_Tony (赞：0)

# 思路
首先按照位置从小到大排序。

设 $dp_{i,j}$ 表示对于前 $i$ 个弹珠，最后一个停止的弹珠。当 $j<i$ 时，那么 $i$ 号弹珠要滚到 $j$ 号弹珠的位置，耗费 $x_i-x_j$，$dp_{i,j}=dp_{i-1,j}+x_i-x_j$；当 $j=i$ 时，则直接把它停住，$dp_{i,j}=(\min\limits_{k=1}^{i-1}dp_{i-1,k})+C_i$。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
typedef pair <ll, ll> pll;
const ll inf = 1e18;
int n, tot;
ll dp[3005][3005], minx = inf;
pll a[3005];
bool cmp (const pll& a, const pll& b) {
	return a.first != b.first ? a.first < b.first : a.second < b.second;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n;
	for (int i = 0; i < n; ++ i)
		cin >> a[i].first >> a[i].second;
	sort (a, a + n, cmp);
	dp[0][0] = a[0].second;
	for (int i = 1; i < n; ++ i) {
		dp[i][i] = inf;
		for (int j = 0; j < i; ++ j)
			dp[i][j] = dp[i - 1][j] + a[i].first - a[j].first, dp[i][i] = min (dp[i][i], dp[i - 1][j]);
		dp[i][i] += a[i].second;
	}
	for (int i = 0; i < n; ++ i)
		minx = min (minx, dp[n - 1][i]);
	cout << minx;
	return 0;
}
```

---

## 作者：harmis_yz (赞：0)

## 分析

考虑 DP。

因为 $n \le 3000$，我们可以直接枚举插针的位置。定义状态函数 $f_i$ 表示在从左往右第 $i$ 个小球的位置上插针的最小花费。

枚举该小球右边第一个插针的位置，则 $i$ 到 $j-1$ 的小球都会滚到小球 $i$ 的位置。代价为 $\sum\limits_{k=i}^{j-1}x_k-x_i$。所以有转移方程：$f_i =\min\{f_j+\sum\limits_{k=i}^{j-1}x_k-x_i|i <j \le n+1\}+c_i$。

这是个 $O(n^3)$ 的 DP。但是不难发现 $\sum\limits_{k=i}^{j-1}x_k-x_i$ 可以用前缀和优化掉。令 $s_i=\sum\limits_{j=1}^{i}x_j-x_1$，则有 $\sum\limits_{k=i}^{j-1}x_k-x_i=s_{j-1}-s_i-(j-1-i)\times(x_i-x_1)$。

因为最左边小球的位置必定会插针，所以答案为 $f_1$。复杂度 $O(n^2)$。

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

const int N=3005;
int n;
struct node{
	int x,c,s;
}a[N];
int f[N],s[N];

il bool cmp(node a,node b){
	return a.x<b.x;
}
il int getsum(int l,int r){
	return s[r]-s[l]-(r-l)*a[l].s;
}
il void solve(){
	n=rd;
	for(re int i=1;i<=n;++i) a[i]={rd,rd};
	sort(a+1,a+n+1,cmp);
	for(re int i=1;i<=n;++i) a[i].s=a[i].x-a[1].x,s[i]=a[i].s+s[i-1];
	memset(f,0x3f,sizeof(f));
	f[n+1]=0;
	for(re int i=n;i>=1;--i){
		for(re int lst=i+1;lst<=n+1;++lst){
			f[i]=min(f[i],f[lst]+getsum(i,lst-1)+a[i].c);
		}
	}
	printf("%lld\n",f[1]);
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

## 作者：Hisaishi_Kanade (赞：0)

简单题。

既然从后往前滚我们就先按照坐标升序排一个，然后倒着确定固定的点，$n\le 3000$ 可以随便枚举上一个固定的点。方便转移钦定存在 $n+1$ 这个点固定好了。

然后考虑转移，因为倒序处理，所以这个区间的 $x$ 全部大于当前的 $x_i$，所以绝对值直接拆掉 $\omega=\sum\limits_{j=i+1}^{k-1} (x_j-x_i)=-(k-i-1)x_i+\sum\limits_{j=i+1}^{k-1} x_j$。

设 $f_i$ 表示第 $i$ 个固定后 $[i,n]$ 的最小花费，显然转移是 $f_{i}=\max\{f_{j}+c_i+\omega\}$，$\omega$ 的求解可以前缀和优化。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
#define ll long long
int qt, i, j, n, tot, res; 
const int N=5006;
int x[N], c[N]; ll f[N];
#define p(x, y) max(a[x], a[y]) 
class echinori
{
	public:
		ll x, c;
		inline const bool operator<(const echinori &other) const
		{
			return x<other.x;;
		}
}e[N];
int main()
{
//	freopen("marble.in", "r", stdin);
//	freopen("marble.out", "w", stdout); 
	/*scanf("%d", &qt);*/qt=1; while(qt--)
	{	
		scanf("%d", &n); rep(i, 1, n) scanf("%lld %lld", &e[i].x, &e[i].c);
		sort(e+1, e+n+1);
		rep(i, 1, n) e[i].x+=e[i-1].x; f[n+1]=0;
		req(i, n, 1)
		{
			f[i]=1e18;
			rep(j, i+1, n+1)
			{
//				printf("%d %d -> %d\n", i, j, f[j]+(x[j-1]-x[i])+(j-i-1)*(x[i]-x[i-1])+c[i]);
				f[i]=min(f[j]+(e[j-1].x-e[i].x)-(j-i-1)*(e[i].x-e[i-1].x)+e[i].c, f[i]);
			}
		}
		printf("%lld\n", f[1]);
	} 
	return 0;
} 

```

---

## 作者：technopolis_2085 (赞：0)

分析：

先将数组按 $x$ 坐标从小到大排序。然后我们发现第一个弹珠必须原地不动，否则所有弹珠都会一直向左滚动。

考虑暴力。

暴力很好想，直接枚举每一个弹珠是否原地不动，然后对于要向左滚动的弹珠找一下左边第一个不动的弹珠，加一下距离即可。

正解：

考虑 dp。

令 $dp_j,_i$ 表示当前第 $i$ 个弹珠为最后一个原地不动的，第 $j$ 个为倒数第二个原地不动的。

令 $sum_i$ 表示从 $1$ 到 $i$ 的 $x$ 的加和。

转移：

可以从 $dp_k,_j$ 转移到 $dp_j,_i$，转移时加上 $[j+1,i-1]$ 区间的弹珠向左移动到第 $j$ 个弹珠的位置和距离和。可以用 $sum$ 数组快速计算。

答案为 $dp_j,_i$ 加上 $[i+1,n]$ 区间内弹珠滚动到 $i$ 的距离和的最小值。

这样，时间复杂度是 $O(n^3)$ 的，会超时。

考虑优化。

我们发现转移中的 $dp_k,_j$，我们并不需要知道 $k$ 是多少，而 $[j+1,i-1]$ 区间的弹珠向左移动到第 $j$ 个弹珠的位置和距离和必然是定值，所以可以维护一个最大值数组。

令 $mi_j$ 表示 所有 $dp_k,_j$ 的最大值。

这样就可以降到 $O(n^2)$ 了。

记得开 long long。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int maxn=3010;
struct node{
	int x,c;
	bool operator <(const node &cmp) const{
		return x<cmp.x;
	}
};

node a[maxn];
int dp[maxn][maxn];
int sum[maxn];
int mi[maxn];

int get(int j,int i){
	return (sum[i-1]-sum[j])-(i-j-1)*a[j].x;
}

signed main(){
	int n;
	scanf("%lld",&n);
	
	for (int i=1;i<=n;i++) scanf("%lld%lld",&a[i].x,&a[i].c);
	sort(a+1,a+1+n);
	
	for (int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i].x;
	
	for (int i=1;i<=n;i++){
		mi[i]=1e18;
		for (int j=1;j<=n;j++) dp[i][j]=1e18;
	}
	
	for (int i=1;i<=n;i++){
		if (i==1){
			dp[1][1]=min(dp[1][1],a[1].c);
			mi[1]=min(mi[1],dp[1][1]); 
		}else dp[1][i]=min(dp[1][i],a[1].c+a[i].c+get(1,i)),mi[i]=min(mi[i],dp[1][i]);
	}
	
	if (n==1){
		printf("%lld\n",a[1].c); return 0;
	}
	
	if (n==2){
		printf("%lld\n",dp[2][1]); return 0;
	}
	
	for (int j=2;j<=n;j++){
		for (int i=j+1;i<=n;i++){
			if (i==j+1){
				dp[j][i]=min(dp[j][i],mi[j]+a[i].c);
				mi[i]=min(mi[i],dp[j][i]);
				continue;
			} 
			dp[j][i]=min(dp[j][i],mi[j]+get(j,i)+a[i].c);
			mi[i]=min(mi[i],dp[j][i]);
		}
	}


	int ans=1e18;
	
	ans=min(ans,a[1].c+get(1,n+1));
	for (int j=1;j<=n;j++){
		for (int i=j+1;i<=n;i++){
			if (i<n) ans=min(ans,dp[j][i]+get(i,n+1));
			else ans=min(ans,dp[j][i]);
		}
	}
	
	printf("%lld\n",ans);
	return 0;
}
```


---

