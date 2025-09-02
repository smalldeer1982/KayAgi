# Game With Triangles: Season 2

## 题目描述

Frontman 欢迎你来到这场生存游戏的最终回合。给定一个具有 $n$ 条边的正则多边形（$n \ge 3$），其顶点按顺时针顺序编号为 $1,2,\ldots,n$。每个顶点 $i$ 上被粉色士兵写有一个正整数 $a_i$。你需要基于这个正则多边形进行如下定义的游戏。

初始时你的得分为 $0$。你可以通过以下操作任意次来增加得分：

- 选择三个未被选择过的不同顶点 $i$、$j$、$k$，并绘制这三个顶点形成的三角形。
  - 此时你的得分增加 $a_i \cdot a_j \cdot a_k$。
  - 但若该三角形与之前绘制的任意三角形存在正面积的公共区域，则不能执行此操作。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2074G/55083de687b4289529b3eb64dfe6b29a4f1f6e75.png)  

左图为两次操作后的合法状态，右图状态不合法，因为两个三角形存在正面积的公共区域。  
你的目标是最大化得分。请计算你在这场游戏中能获得的最大得分。


## 说明/提示

第一个测试用例中，只能绘制一个三角形。选择 $i=1$、$j=2$、$k=3$ 的三角形可得最大得分 $6$。

第二个测试用例中，只能绘制一个三角形。选择 $i=1$、$j=3$、$k=4$ 的三角形可得最大得分 $24$。

第三个测试用例中，可以绘制两个三角形。通过两次操作可得最大得分 $5$。

第四个测试用例中，可以绘制两个三角形。但绘制两次得分可能为 $6+5=11$、$15+2=17$ 或 $10+3=13$。选择仅绘制 $i=2$、$j=4$、$k=6$ 的三角形可得最大得分 $30$。

第五个测试用例中，可以绘制三个三角形。通过以下方式绘制三个三角形可得最大得分 $732$：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2074G/51aa3904604e991d60da4548ed36f974e23a2cf2.png)

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
6
3
1 2 3
4
2 1 3 4
6
2 1 2 1 1 1
6
1 2 1 3 1 5
9
9 9 8 2 4 4 3 5 3
9
9 9 3 2 4 4 8 5 3```

### 输出

```
6
24
5
30
732
696```

# 题解

## 作者：未来姚班zyl (赞：3)

区间 dp。

$dp_{l,r}$ 转移还是很简单的。如果 $l,r$ 不在同一次选择中就枚举断点，否则枚举第三个点即可，这个判断本质上无需断环为链。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R x<<1|1
#define mid ((l+r)>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,m
#define OK Ll<=l&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(int x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N=5e5+5,M=1e6+5,inf=(1LL<<30)-1,mod=1e9+7;
const ll llf=1e18;
inline void add(int &a,int b){if(b<0)b+=mod;((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){add(b,mod);return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,ll b){if(!b)return 1;int c=qp(a,b>>1LL);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
int n,a[N];
int dp[405][405];
inline void Main(){
	n=read();
	repn(i)a[i]=read();
	rep(i,0,n+1)rep(j,0,n+1)dp[i][j]=0;
	rep(len,3,n){
		rep(l,1,n-len+1){
			int r=l+len-1;
			rep(k,l+1,r-1)dp[l][r]=max(dp[l][r],a[l]*a[r]*a[k]+dp[l+1][k-1]+dp[k+1][r-1]);
			rep(k,l,r)dp[l][r]=max(dp[l][r],dp[l][k]+dp[k+1][r]);
		}
	}
	cout <<dp[1][n]<<'\n';
}
signed main(){
	int T=read();
	while(T--)Main();
	return 0;
}
```

---

## 作者：postpone (赞：1)

题目要求选择的三角形集合中，两两无公共面积，想一想这种情况要怎么转移。

枚举选择的三个点中的，处于两端的点 $l$ 和 $r$，再枚举 $l$ 和 $r$ 中的第三个点 $i$。在这种情况下，$l$ 和 $i$ 中间，以及 $i$ 和 $r$ 中间，可以选三角形出来而没有公共部分。则有

$$
f_{l, r} \leftarrow \max_{i \in (l, r)}\left\{ f_{l + 1, i - 1} + f_{i + 1, r - 1} + a_l\cdot a_i\cdot a_r \right\}
$$

看上去好像没问题，但还有一种情况，就是 $l$ 和 $r$ 里面有更优的解，那就直接用里面的作为结果，即

$$
f_{l, r} \leftarrow \max_{i\in -[l, r)} \left\{f_{l, i} + f_{i + 1, r}\right\}
$$

把这两个合起来，这道题就做出来了。

```cpp
void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    vector dp(n, vector<i64>(n));
    for (int r = 2; r < n; r++) {
        for (int l = r - 2; l >= 0; l--) {
            for (int i = l + 1; i < r; i++) {
                dp[l][r] = max(dp[l][r], dp[l + 1][i - 1] + dp[i + 1][r - 1] + a[l] * a[i] * a[r]);
            }
            for (int i = l; i < r; i++) {
                dp[l][r] = max(dp[l][r], dp[l][i] + dp[i + 1][r]);
            }
        }
    }
    cout << dp[0][n - 1] << "\n";
}
```

---

## 作者：bluewindde (赞：1)

断环成链。

设 $dp_{l, r}$ 表示选顶点在区间 $[l, r]$ 间的三角形的最大分数。

答案是

$$\max\limits_{1 \leqslant i \leqslant n}(dp_{i, i + n - 1})$$

强制选 $l, r$，转移

$$dp_{l, r} \leftarrow \max\limits_{l < i < r}(dp_{l + 1, i - 1} + dp_{i + 1, r - 1} + a_l \cdot a_i \cdot a_r)$$

继承

$$dp_{l, r} \leftarrow \max\limits_{l \leqslant i < r}(dp_{l, i} + dp_{i + 1, r})$$

时间复杂度 $O(n^3)$。

```cpp
#include <iostream>

#define int long long

using namespace std;

int n;
int a[805];

bool vis[805][805];
int dp[805][805];
static inline int solve(int l, int r) {
    if (l > r)
        return 0;
    if (vis[l][r])
        return dp[l][r];
    vis[l][r] = true;
    int ret = 0;
    for (int i = l + 1; i < r; ++i)
        ret = max(ret, solve(l + 1, i - 1) + solve(i + 1, r - 1) + a[l] * a[r] * a[i]);
    for (int i = l; i < r; ++i)
        ret = max(ret, solve(l, i) + solve(i + 1, r));
    return dp[l][r] = ret;
}

static inline void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i + n] = a[i];
    }
    for (int i = 1; i <= 2 * n; ++i)
        for (int j = 1; j <= 2 * n; ++j)
            vis[i][j] = false;
    solve(1, 2 * n);
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        if (vis[i][i + n - 1])
            ans = max(ans, dp[i][i + n - 1]);
    cout << ans << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
```

---

## 作者：Defy_HeavenS (赞：0)

## [Problem - 2074G - Codeforces](https://codeforces.com/problemset/problem/2074/G)
区间 DP，设 $f_{l,r}$ 表示区间 $[l,r]$ 内的最大得分。

转移考虑区间 $[l,r]$ 内有没有一个三角形的两顶点为 $l,r$。

1. 如果有一个三角形的两顶点为 $l,r$，那么枚举第三个顶点 $i$，贡献为这个三角形的分数，加上另外两个区间的最大分数，即 $a_l a_r a_i+f_{l+1,i-1}+f_{i+1,r-1}$。

2. 否则没有，那么这个区间一定可以被分成两半，两半之间没有三角形横跨（横跨就是，一个三角形某些顶点在左区间，某些顶点在右区间），所以枚举分界点 $i$，贡献为两区间的最大分数之和，即 $f_{l,i}+f_{i+1,r}$。

为什么这样能保证三角形没有公共部分？首先思考什么时候会有公共部分，对于两个三角形 $A,B$，如果三角形 $A$ 的某些顶点夹在三角形 $B$ 的两个相邻顶点之间，而三角形 $A$ 的其他顶点不在这中间，则 $A$ 的两条边一定穿过 $B$ 的其中一条边，也一定穿过 $B$ 的面积。

对于情况 1，我们假设 $f_{l+1,i-1},f_{i+1,r-1}$ 内都是无公共部分的，对于那个顶点包含 $l,r$ 的大三角形，这两部分的三角形的三个顶点都在大三角形 $li,ri$ 两条边之下，没有相交。

对于情况 2，假设 $f_{l,i},f_{i+1,r}$ 内无公共部分，两区间连接不会产生相交。

由于三角形三个顶点没有顺序，所以不用破环为链。

时间复杂度 $\mathcal{O}(n^3)$。

启示：区间 DP，转移考虑区间端点的各情况。

```cpp
#include<bits/stdc++.h>
#define umap unordered_map
#define uset unordered_set
#define mset multiset
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define yes cout<<"Yes\n"
#define no cout<<"No\n"
#define all(x) (x).begin(),(x).end()
#define tmax(a,b) (a)=max((a),(b))
#define tmin(a,b) (a)=min((a),(b))
#define debug(x) cout<<"line "<<__LINE__<<" : "<<#x<<": "<<x<<"\n"
#define cout(x) cout<<fixed<<setprecision(x)

using namespace std;
typedef long long LL;typedef pair<LL,LL> PII;
typedef vector<LL> vi;typedef vector<PII> vp;

const LL N=4e2+5;
LL n,a[N],dp[N][N];

void clear(){
	for(LL i=1;i<=n;i++){
		for(LL j=1;j<=n;j++){
			dp[i][j]=0;
		}
	}
}
void solve(){
	cin>>n;
	for(LL i=1;i<=n;i++){
		cin>>a[i];
	}
	for(LL len=3;len<=n;len++){
		for(LL l=1,r;l<=n-len+1;l++){
			r=l+len-1;
			for(LL i=l+1;i<r;i++){
				tmax(dp[l][r],a[l]*a[r]*a[i]+dp[l+1][i-1]+dp[i+1][r-1]);
			}
			for(LL i=l;i<r;i++){
				tmax(dp[l][r],dp[l][i]+dp[i+1][r]);
			}
		}
	}
	cout<<dp[1][n]<<"\n";
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	LL t=1;cin>>t;
	while(t--) clear(),solve();
	return 0;
}
```

---

## 作者：ATION001 (赞：0)

设 $dp_{l,r}$ 表示在区间 $[l,r]$ 范围的点能凑出来的最大价值。

由于图形是一个环，因此我们需要断环为链。

接下来枚举区间 $[l,r]$，状态转移：

$$
dp[l][r]=\max\{dp_{l,r},dp_{l+1,k-1}+dp_{k+1,r-1}+a_l\times a_k\times a_r,dp_{l,k-1}+dp_{k,r},dp_{l,k}+dp_{k+1,r}\}
$$

最后，答案为 $\max\{dp_{i,i+n-1}\}$。
### 实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,a[805],dp[805][805];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	for(cin>>t;t;t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			a[i+n]=a[i];
		}
		fill(dp[0],dp[n*2+1],0);
		for(int len=2;len<=n;len++){
			for(int l=1;l<=n*2-len+1;l++){
				int r=l+len-1;
				for(int k=l+1;k<r;k++){
					dp[l][r]=max({dp[l][r],dp[l+1][k-1]+dp[k+1][r-1]+a[l]*a[k]*a[r],dp[l][k-1]+dp[k][r],dp[l][k]+dp[k+1][r]});
				}
			}
		}
		int ans=0;
		for(int i=1;i<=n;i++){
			ans=max(ans,dp[i][i+n-1]);
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

