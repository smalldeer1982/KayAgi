# [ABC288E] Wish List

## 题目描述

商店里有 $N$ 件商品，标号 $1\sim N$，第 $i$ 件商品有**底价** $A_i$ 且只有一件。

Takahashi 想要买其中的 $M$ 件商品，分别是标号 $X_1,X_2,\ldots,X_M$ 的商品。

他会按照以下的方式买东西：

若还剩 $r$ 件商品没有购买过，选择一个符合 $1\le j\le r$ 的 $j$，付这件商品的底价加上 $C_j$ 的钱购买其中标号第 $j$ 小的商品。

求出买到它想要的商品所付的最小价钱。

注意他也可以买不想要的商品。

## 样例 #1

### 输入

```
5 2
3 1 4 1 5
9 2 6 5 3
3 5```

### 输出

```
17```

## 样例 #2

### 输入

```
20 8
29 27 79 27 30 4 93 89 44 88 70 75 96 3 78 39 97 12 53 62
32 38 84 49 93 53 26 13 25 2 76 32 42 34 18 77 14 67 88 12
1 3 4 5 8 14 16 20```

### 输出

```
533```

# 题解

## 作者：qzhwlzy (赞：4)

### 题目大意

有 $n$ 件商品，第 $i$ 件有价格 $a_i$，你想要其中的 $m$ 件。每次购买某个商品 $i$ 时，若其在所有未买的商品中是**编号**第 $j$ 小的，你需要付 $a_i + c_j$ 的钱。求买到想要的 $m$ 件商品需要付的最小钱数（可以买不想要的）。

### 思路

想买第 $i$ 件商品时，需要付的钱应该是 $a_i + c_{i-x}$，其中 $x$ 是 $1\sim i-1$ 件商品中已经买了的商品数量。所以买一个物体的价格与之前买的物品数量有关。

注意到每个商品只有买和不买两种方法，所以考虑一个类似 01 背包的 DP。令 $f_{i,j}$ 表示前 $i$ 件商品中买了 $j$ 件需要付的最小钱数。同时记 $m_{i,j} = \min\limits_{k=i-j+1}^{i}c_k$，用来计算若 $i$（包含）之前要买 $j$ 个时，通过合理安排顺序（刚好在这个商品到 $c$ 的最小值时买），购买 $i$ 时所能取到的 $c$ 的最小值。那么：

- 若第 $i$ 件商品要选，则 $f_{i,j} = \min(f_{i,j},f_{i-1,j-1} + m_{i,j} + a_i)$，因为 $i$ 编号最大，首先它不会影响 $f_{i-1,j-1}$ 的相对购买方案，其次也可以在取到 $c$ 最小值时买到；
- 若第 $i$ 件商品不选，则 $f_{i,j} = \min(f_{i,j},f_{i-1,j})$。

关于实现，因为想要的物品编号升序给出，我们可以用一个变量 $pos$ 维护已经选择了前 $pos$ 个，那么 $j$ 的枚举应从 $pos$ 开始，同时在 $j=pos$ 时 $i$ 不能选（选了前面 $pos$ 个必选的物品选不了）；而且 $i = x_{pos+1}$（$x$ 为存一定要选的编号的数组）即 $i$ 必选时 $i$ 不能不选。

```cpp
// 注意这里代码的 pos 和上文略有不同，上文的 pos 应为此处的 pos-1
#include<iostream>
#include<cstdio>
#define maxn 5005
#define ll long long
using namespace std;
int n,m,a[maxn],c[maxn],x[maxn],mmin[maxn][maxn],pos=1; ll f[maxn][maxn],ans;
int main(){
      scanf("%d%d",&n,&m); for(int i=1;i<=n;i++) scanf("%d",&a[i]);
      for(int i=1;i<=n;i++) scanf("%d",&c[i]);
      for(int i=1;i<=m;i++) scanf("%d",&x[i]);
      for(int i=0;i<=n;i++) for(int j=1;j<=n;j++) f[i][j]=2e9*5005LL;
      for(int i=1;i<=n;i++){mmin[i][1]=c[i]; for(int j=2;j<=i;j++) mmin[i][j]=min(mmin[i][j-1],c[i-j+1]);}
      f[0][0]=0LL; for(int i=1;i<=n;i++){
            for(int j=max(pos-1,1);j<=i;j++){
                  if(j!=pos-1) f[i][j]=min(f[i][j],f[i-1][j-1]+1LL*mmin[i][j]+1LL*a[i]); // choose i-th item
                  if(i!=x[pos]) f[i][j]=min(f[i][j],f[i-1][j]); // don't choose i-th item
            } if(i==x[pos]) pos++;
      } ans=f[n][m]; for(int i=m+1;i<=n;i++) ans=min(ans,f[n][i]); printf("%lld",ans);
      return 0;
}
```

---

## 作者：Lucyna_Kushinada (赞：1)

dp 好题，难点在于看清 “编号第 $j$ 小” 的本质，以及对于方程的设计。

令 $dp_{i,j}$ 为前 $i$ 个中买了 $j$ 个，且必买的全买了的最小价值。

于是我们可以套路地是可以从选和不选来转移，但需要注意必买的**只能选**，不可以不选，其他的则没什么关系。

不选显然可以通过 $dp_{i,j}=\min (dp_{i-1,j})$ 转移，下面来讨论选的情况的转移。

在这 $j$ 次购买中，我们既可以决定第 $1$ 次就把 $i$ 买了，也可以第 $j$ 次才买 $i$。如果是第 $1$ 次就把 $i$ 买了，总价就是 $(c_i+a_i)$，如果第 $j$ 次才买 $i$，那么总价就是 $(c_{i-j+1}+a_i)$，因为我们要求最小的，所以贡献就是 $(\min_{k=i-j+1}^{i}c_k+a_i)$，故选第 $i$ 个的转移方程就是 $dp_{i,j}=dp_{i-1,j-1}+\min_{k=i-j+1}^{i}c_k+a_i$。

那么答案就是 $\min_{i=m}^n dp_{n,i}$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,l,r) for(int i=(l);i<=(r);++i)
#define per(i,l,r) for(int i=(r);i>=(l);--i)
#define pr pair<int,int>
#define fi first
#define se second
#define pb push_back

#define N 5055
#define M 13
#define int long long

int n,m,a[N],c[N],x,mn[N][N],dp[N][N];
bitset<N>f;

signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    cin>>n>>m;
    rep(i,1,n){
        cin>>a[i];
    }
    rep(i,1,n){
        cin>>c[i];
    }

    int x;
    rep(i,1,m){
        cin>>x;
        f[x]=1;
    }

    rep(i,1,n){
        mn[i][i]=c[i];
        rep(j,i+1,n){
            mn[i][j]=min(mn[i][j-1],c[j]);
        }
    }

    rep(i,0,n){
        rep(j,0,n){
            dp[i][j]=1e15;
        }
    }
    dp[0][0]=0;

    rep(i,1,n){
        rep(j,1,i){
            dp[i][j]=min(dp[i][j],dp[i-1][j-1]+mn[i-j+1][i]+a[i]);
        }

        if(f[i])continue;

        rep(j,0,i){
            dp[i][j]=min(dp[i][j],dp[i-1][j]);
        }
    }

    int ans=1e15;

    rep(j,m,n){
        ans=min(ans,dp[n][j]);
    }

    cout<<ans;

    return 0;
}
```

---

## 作者：WaterSun (赞：1)

# 思路

定义 $dp_{i,j}$ 表示在标号前 $i$ 个商品中，将所有 $x_k \leq i$  的商品购买，且一共买了 $j$ 件商品的花费最小值。

那么，对于 $i$ 号商品就会有 选/不选，两种状态：

1. 如果选，那么有 $dp_{i,j} = \min(dp_{i - 1,j - 1} + \min_{k = i - j + 1}^i(c_k) + a_i)$。因为对于 $i$ 号商品，如果第一次选择购买 $i$ 号商品，贡献为 $c_i + a_i$；如果最后一次选择购买 $i$ 号商品，贡献为 $c_{i - j + 1} + a_i$。那么，对于第 $i$ 件商品，贡献最少的就是 $\min_{k = i - 1 + 1}^i(c_k) + a_i$。

2. 如果不选，那么有 $dp_{i,j} = \min(dp_{i - 1,j})$。

这里最小值，我用的是 ST 表预处理。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 5010,M = 20,inf = 0x3f3f3f3f3f3f3f3f;
int n,m,ans = inf;
int lg[N],arr[N];
int dp[N][N];
bool st[N];

struct RMQ_ST{
	#define pot(x) (1 << x)
	
	int dp[N][M];
	
	inline void init(){
		lg[1] = 0;
		for (re int i = 2;i <= n;i++) lg[i] = lg[i / 2] + 1;
		for (re int j = 1;j <= lg[n];j++){
			for (re int i = 1;i <= n - pot(j) + 1;i++) dp[i][j] = min(dp[i][j - 1],dp[i + pot(j - 1)][j - 1]);
		}
	}
	
	inline int query(int l,int r){
		int x = lg[r - l + 1];
		return min(dp[l][x],dp[r - pot(x) + 1][x]);
	}
	
	#undef pot
}ST;

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

signed main(){
	memset(dp,inf,sizeof(dp));
	dp[0][0] = 0;
	n = read();
	m = read();
	for (re int i = 1;i <= n;i++) arr[i] = read();
	for (re int i = 1;i <= n;i++) ST.dp[i][0] = read();
	for (re int i = 1;i <= m;i++){
		int x;
		x = read();
		st[x] = true;
	}
	ST.init();
	for (re int i = 1;i <= n;i++){
		for (re int j = 1;j <= i;j++) dp[i][j] = min(dp[i][j],dp[i - 1][j - 1] + ST.query(i - j + 1,i) + arr[i]);
		if (st[i]) continue;//如果 st[i] = true 表示 i 必选，所以下面对于 i 商品不选的情况跳过 
		for (re int j = 0;j <= i;j++) dp[i][j] = min(dp[i][j],dp[i - 1][j]);
	}
	for (re int i = m;i <= n;i++) ans = min(ans,dp[n][i]);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：CQ_Bab (赞：1)

# 思路
我们可以发现这是一道 Dp 题，然后我们就可以来定义状态，我们定义 $f_{i,j}$ 为前 $i$ 个物品中，已经把 $1\sim i$ 中必须选的选了，一共选了 $j$ 个物品的最小价值。然后我们就来想一下状态转移方程，我们还是需要分类讨论，如果第 $i$ 个物品必须选，那么我们 $f_{i,j}=f_{i-1,j}+a_i+minn_{i,j}$ 这里我们定义 $minn_{i,j}$ 为从 $c_i\sim c_{i-j+1}$ 中的最小值，否则 $f_{i,j}=\min(f_{i-1,j},f_{i-1,j}+a_i+minn_{i,j})$ 就是分选它和不选它的两种情况。最后答案就是 $f_{n,m}\sim f_{n,n}$ 了。
# 代码
```cpp
#include <bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(fasle);cin.tie(NULL);cout.tie(NULL)
#define int long long
#define ri register int
#define rep(i,x,y) for(ri i=x;i<=y;i++)
#define rep1(i,x,y) for(ri i=x;i>=y;i--)
#define il inline
#define fire signed
#define pai(a,x,y) sort(a+x,a+y+1)
using namespace std ;
il int qmi(int a,int b) {
	int res=1;
	while(b) {
		if(b&1) res=(res*a);
		a=a*a;
		b>>=1;
	}
	return res;
}
void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
#define gcd(x,y) __gcd(x,y)
#define lcm(x,y) x*y/gcd(x,y)
int n,m;
const int N=5e3+10;
int a[N],c[N],x;
int arr[N];
int minn[N][N];
int f[N][N];
int cnt[N];
fire main() {
	cin>>n>>m;
	rep(i,1,n) cin>>a[i];
	rep(i,1,n) cin>>c[i];
	rep(i,1,m) {
		cin>>x;
		arr[x]=1;
	}
	rep(i,1,n) cnt[i]=cnt[i-1]+arr[i];
	memset(f,0x3f,sizeof f);
	f[0][0]=0;
	rep(i,1,n) {//预处理
		minn[i][1]=c[i];
		rep(j,2,i) minn[i][j]=min(minn[i][j-1],c[i-j+1]);
	}
	rep(i,1,n) {
		rep(j,cnt[i],i) {
			if(arr[i]) { //分类讨论
				f[i][j]=f[i-1][j-1]+a[i]+minn[i][j];
			}else f[i][j]=min(f[i-1][j],f[i-1][j-1]+a[i]+minn[i][j]);
		}
	}
	int res=LONG_LONG_MAX;
	rep(i,m,n) res=min(res,f[n][i]); //求答案
	print(res);
	return false;
}

```

---

## 作者：yr409892525 (赞：0)

### [AT_abc288_e [ABC288E] Wish List](https://www.luogu.com.cn/problem/AT_abc288_e)
定义 $f_{i,j}$ 代表前 $i$ 个物品选了 $j$ 个的最小花费。                       
由于可以买不想买的，所以最终买的物品数量不知道，所以答案为 $\min_{i=m}^n f_{n,i}$。                             

1. 不买第 $i$ 个物品，$f_{i,j}=f_{i-1,j}$。
2. 买第 $i$ 个物品
   注意到第 $i$ 个物品是前 $i$ 个物品中编号最大的物品，所以 $i$ 的购买顺序不会对 $f_{i-1,j-1}$ 造成影响。                   
   若第 $1$ 次购买物品 $i$，代价为 $a_i+c_i$，若第 $j$ 次购买物品 $i$，代价为 $a_i+c_{i-j+1}$。                         
   即 $f_{i,j}=f_{i-1,j-1}+a_i+\min_{k=i-j+1}^i c_k$。

区间最小值可以预处理出来。                           

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5005;
int n,m,a[N],c[N];
int dp[N][N],st[N][N],b[N];
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>c[i];
	}
	for(int i=1,x;i<=m;i++){
		cin>>x;
		b[x]=1;
	}
	for(int i=1;i<=n;i++){
		st[i][i]=c[i];
		for(int j=i+1;j<=n;j++){
			st[i][j]=min(st[i][j-1],c[j]);
		}
	}
	memset(dp,0x3f,sizeof dp);
	dp[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=i;j++){
			j && (dp[i][j]=dp[i-1][j-1]+st[i-j+1][i]+a[i]);
			if(!b[i]){
				dp[i][j]=min(dp[i][j],dp[i-1][j]);
			}
		}
	}
	int ans=1e18;
	for(int i=m;i<=n;i++){
		ans=min(ans,dp[n][i]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：yr409892525 (赞：0)

### [AT_abc159_f [ABC159f] Knapsack for All Segments](https://www.luogu.com.cn/problem/AT_abc159_f)
当一个左端点为 $l$，右端点为 $r$ 的子序列的和为 $S$，对答案的贡献为 $l\times (n-r+1)$。                  
可以枚举右端点 $r$，计算左端点 $l$ 的和。                   
定义 $f_{i,j}$ 代表前 $i$ 个数中所有总和为 $j$ 的左端点总和。                     
答案 $\sum_{i=1}^n f_{i,S}$。               
1. 选当前元素，$f_{i,j}+f_{i-1,j-a_i}$，$f_{a_i}+i$。
2. 不选当前元素，$f_{i,j}+f_{i-1,j}$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3005,mod=998244353;
int n,s;
int dp[N],sum;
signed main(){
	cin>>n>>s;
	for(int i=1,x;i<=n;i++){
		cin>>x;
		for(int j=s-x;j>=1;j--){
			(dp[j+x]+=dp[j])%=mod;
		}
		(dp[x]+=i)%=mod;
		(sum+=dp[s])%=mod;
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：鲤鱼江 (赞：0)

一月二日的作业，简单练手题。

首先考虑我们选不想要的物品一定是为了位移某些想要的物品。

其次发现如果选了比一个物品编号更大的物品，对这个物品的权值是没有影响的。

两个显然的想法出来之后这个题的思路就完善了。我们从前往后 DP，那么后面的物品怎么选都不会影响前面的权值，所以具有无后效性。

设 $dp_{i,j}$ 表示前 $i$ 个数中选了 $j$ 个数的最小代价（想要的物品必须选上）。

有如下 dp 过程，$minn_{i,j}$ 表示，$\min\limits_{i\le k \leq j} C_k$。

对于必选的物品，我们算出其代价为 $dp_{i-1,j-1}+minn_{i-j+1,i}+A_i$。

使用 $minn$ 数组是因为我们可以决定这个物品什么时候选，正确性是显然的，因为无后效性，所以这个物品可以随意插入。

对于不选的情况，直接继承就可以了。

```cpp
	for(int i=1;i<=n;++i){
		if(fg[i]){for(int j=1;j<=i;++j) dp[i][j]=dp[i-1][j-1]+minn[i-j+1][i]+A[i];}
		else{dp[i][0]=dp[i-1][0];for(int j=1;j<=i;++j) dp[i][j]=min(dp[i-1][j],dp[i-1][j-1]+minn[i-j+1][i]+A[i]);}
	}
```

---

## 作者：ZBH_123 (赞：0)

### 思路：动态规划
这是一道很明显的 DP 的题目。既然是 DP，那么肯定就有设计状态、推导状态转移方程和设置边界这三个步骤。那就让我们一步一个脚印，逐渐完善我们的程序。
#### 1.设计状态
对于本题，我们可以设 $dp_{i,j}$ 为在前 $i$ 件物品中选出 $j$ 件，并且这 $j$ 件物品中包含 $1 \sim i$ 中所有想要的物品。那么最终答案肯定就是：
$$\max_{i=M}^{N}{dp_{n,i}}$$
#### 2.状态转移方程
对于在前 $i$ 件物品中选出 $j$ 件物品，我们要分两种情况讨论：一种是第 $i$ 件物品不选，一种是第 $i$ 件物品要选。第 $i$ 件物品不选时的状态转移方程很简单。因为不选第 $i$ 件物品，那自然就是要从前 $i-1$ 件物品中选出 $j$ 件物品喽。所以这种情况下的状态转移方程是：
$$dp_{i,j}=dp_{i-1,j}$$
接下来重点讨论第 $i$ 件物品要选的情况。为避免变量产生歧义，下面用 $k$ 来表示题意中的 $j$。第 $i$ 件物品要选，还要讨论第 $i$ 件物品是第几个选的。如果 $i$ 是第 $1$ 个选的，那么买第 $i$ 件物品所选的 $k$ 必定是 $i$。而第 $i$ 件物品是第 $2$ 个选的，那么在选第 $i$ 件物品之前，必定先选了一件物品，选了前面的一件物品后，第 $i$ 件物品的排名就向前挪了一位，变成了 $i-1$。所以这个情况下选择的 $k$ 便是 $i-1$。第 $i$ 件物品是第 $3 \sim j$ 个选的的情况同理。那么，第 $i$ 件物品在第 $1 \sim j-1$ 个选择，会不会影响前面的物品的选择呢？答案是不会的。因为不管第 $i$ 件物品是第几个选的，它的排名始终在前面的物品的后面。而且 $C$ 数组又是可以重复的，所以第 $i$ 件物品是第几个选的并不影响前面的物品的选择。而第 $i$ 件物品可选择的 $k$ 一定 $\ge i-j+1$，$\le i$。那么，这种情况下的状态转移方程是：
$$dp_{i,j}=dp_{i-1,j-1}+A_i+Min$$
其中：
$$Min=\min_{l=i-j+1}^{i}{C_l}$$
综上所述，本题的状态转移方程为：
$$dp_{i,j}=\min(dp_{i-1,j},dp_{i-1,j-1}+A_i+Min)$$
#### 3.设置边界
由于最开始一切情况下的最优解都不确定，所以整个 $dp$ 数组都应该初始化成极大值。这里有一个特例：在前 $0$ 件物品中选出 $0$ 件物品的最小花费一定是 $0$。为什么呢？因为这种情况下什么物品都没选，那自然是没有花费喽。所以，$dp_{0,0}$ 就应该初始化成 $0$。
#### 代码实现
由于 $j$ 有可能等于 $0$，那么进行状态转移的时候就有可能发生数组越界。这时，我们就可以考虑将状态转移方程中要选第 $i$ 件物品时的 $j$ 整体向后移动 $1$。这样做的话，要选第 $i$ 件物品时的 $dp_{i,j}$ 就要提前计算。而不选第 $i$ 件物品的情况还是按时更新就行了。

根据状态转移方程和上面所说的细节，我们可以写出以下程序片段：
```cpp
for(int i=1;i<=n;i++){
	for(int j=0;j<=i;j++){
		if(!vis[i]){
			dp[i][j]=min(dp[i][j],dp[i-1][j]);
		}
		int Min=0x3f3f3f3f;
		for(int k=i-j;k<=i;k++){
			Min=min(Min,c[k]);
		}
		if(j<i){
			dp[i][j+1]=dp[i-1][j]+a[i]+Min;
		}
	}
}
```
我们会发现寻找 $Min$ 的过程非常耗时。很多人可能会用 ST 表来维护区间最小值，但是比起 ST 表，还要另外一种更加巧妙的方法。我们可以利用寻找 $Min$ 的区间长度不断增长这个特点，更新 $i-j \sim i$ 的 $Min$。

**AC code:**
```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int maxn=5e3+5; 
int n,m,a[maxn],c[maxn],x;
long long ans=2e18,dp[maxn][maxn];
bool vis[maxn];
int main(){
	memset(dp,0x3f,sizeof dp);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>c[i];
	}
	for(int i=1;i<=m;i++){
		cin>>x;
		vis[x]=true;
	}
	dp[0][0]=0;
	for(int i=1;i<=n;i++){
		int Min=c[i];
		for(int j=0;j<=i;j++){
			Min=min(Min,c[i-j]);
			if(!vis[i]){
				dp[i][j]=min(dp[i][j],dp[i-1][j]);
			}
			if(j<i){
				dp[i][j+1]=dp[i-1][j]+a[i]+Min;
			}
		}
	}
	for(int i=m;i<=n;i++){
		ans=min(ans,dp[n][i]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：highkj (赞：0)

# 思路
我们明显可以看出这是一道动态规划题目，所以我们就需要来定义状态，首先我们定义 $f_{i,j}$ 为在前 $i$ 个物品中已经选完了必须选的一共选了 $j$ 个的最小价值。那么我们这里来看一下 $j$ 的范围其实就是在 $cnt_i$ 与 $i$ 之间，这里 $cnt_i$ 为前 $i$ 个数中必须选的个数。那么这里的转移要分两种情况：

- 如果第 $i$ 个数必须选，那么 $f_{i,j}=f_{i-1,j-1}+a_j+\min(c_i\sim c_{i-j+1})$。
- 否则 $f_{i,j}=\min(f_{i-1,j},f_{i-1,j-1}+a_j+\min(c_i\sim c_{i-j+1}))$。

这里我们可以用倍增，或者二维预处理，我使用的是二维。
# 代码
```cpp
#include <bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(fasle);cin.tie(NULL);cout.tie(NULL)
#define int long long
#define ri register int
#define rep(i,x,y) for(ri i=x;i<=y;i++)
#define rep1(i,x,y) for(ri i=x;i>=y;i--)
#define il inline
#define fire signed
#define pai(a,x,y) sort(a+x,a+y+1)
using namespace std ;
il int qmi(int a,int b) {
	int res=1;
	while(b) {
		if(b&1) res=(res*a);
		a=a*a;
		b>>=1;
	}
	return res;
}
void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
#define gcd(x,y) __gcd(x,y)
#define lcm(x,y) x*y/gcd(x,y)
int n,m;
const int N=5e3+10;
int a[N],c[N],x;
int vis[N];
int Min[N][N];
int f[N][N];
int cnt[N];
fire main() {
	cin>>n>>m;
	rep(i,1,n) cin>>a[i];
	rep(i,1,n) cin>>c[i];
	rep(i,1,m) {
		cin>>x;
		vis[x]=1;
	}
	rep(i,1,n) cnt[i]=cnt[i-1]+vis[i];
	memset(f,0x3f,sizeof f);
	f[0][0]=0;
	rep(i,1,n) {
		Min[i][i]=c[i];
		rep(j,i+1,n) Min[i][j]=min(Min[i][j-1],c[j]); //预处理 
	}
	rep(i,1,n) {
		rep(j,cnt[i],i) {
			if(!vis[i]) f[i][j]=f[i-1][j]; //分类讨论 
			f[i][j]=min(f[i][j],f[i-1][j-1]+a[i]+Min[i-j+1][i]);
		}
	}
	int res=LONG_LONG_MAX;
	rep(i,m,n) res=min(res,f[n][i]);
	print(res);
	return false;
}

```

---

## 作者：Otue (赞：0)

## 思路
假设你需要选择 $B_1,B_2,..,B_k$ 这 $K$ 个元素编号。

假设当前你选择 $B_i$ 元素，且前面 $i-1$ 个元素 $B_1,B_2,...,B_{i-1}$ 选择了 $x$ 个（$0\leq x\leq i-1$），那么选择代价就为 $A_{B_i}+C_{B_i-x}$。

那么对于 $x$ 从 $0$ 到 $i-1$ 的最优代价就为：$A_{B_i}+cost(B_i,i-1)$。其中 $cost(i,j)=\min\{C_{i-j},C_{i-j+1},...,C_i\}$。

则总代价为 $\sum ^{k}_{i=1}(A_{B_i}+cost(B_i,i-1))$。

但是现在的问题是你并不知道你需要选择哪些数（你还可以选择 X 数组外其他的数），则需要 dp 进行解决。

定义 $dp_{i,j}$ 表示前 $i$ 个数买了 $j$ 件商品的最小代价。

如果选择第 $i$ 个数（什么时候都能选），$dp_{i,j}=\max\{dp_{i,j},dp_{i-1,j-1}+A_i+cost(i,j-1)\}$   
如果不选择第 $i$ 个数（X 数组没要求选才能选），$dp_{i,j}=\max\{dp_{i,j},dp_{i-1,j}\}$

最后求答案，输出 $\max\{dp_{n,i}\}(m\leq i \leq n)$。

## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 5005; 
int n, m, a[N], c[N], x[N], vis[N];
int f[N][N], dp[N][N];

signed main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> c[i];
	for (int i = 1; i <= m; i++) cin >> x[i], vis[x[i]] = 1;
	memset(f, 0x3f3f3f3f3f3f, sizeof f);
	for (int i = 1; i <= n; i++) {
		f[i][0] = c[i];
		for (int j = 1; j < i; j++) f[i][j] = min(f[i][j - 1], c[i - j]);
	}
	memset(dp, 0x3f3f3f3f3f3f, sizeof dp);
	dp[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + a[i] + f[i][j - 1]);
		if (vis[i]) continue;
		for (int j = 0; j <= i; j++) dp[i][j] = min(dp[i][j], dp[i - 1][j]);
	}
	int res = 1e18;
	for (int i = m; i <= n; i++) res = min(res, dp[n][i]);
	cout << res << endl; 
}
```

---

## 作者：happybob (赞：0)

考虑 DP。

$f_{i,j}$ 表示当前考虑了前 $i$ 个数，选了恰好 $j$ 个的最小答案。

转移分两类，即 $i$ 是否为想要的物品。通过预处理 $s_{i,j} = \min \limits_{x=i}^j c_x$ 可以 $O(1)$ 转移，故总复杂度 $O(n^2)$。

---

