# Dynamic Array Problem

## 题目描述

你有一个序列长度为 $n$ 的序列 $a$！初始时序列只有两端有隔板，其他位置没有。

你可以插入任意多个隔板，隔板不重合，且隔板不起到分割序列的作用。插入后，选择至多 $k$ 对 **可以不相邻** 的隔板，将他们之间的序列元素翻转。它们之间的隔板的位置不受影响，只改变元素位置，要求一个元素至多被翻转一次。

如果两个隔板相邻且他们之间的元素下标是 $l$ 到 $r$，则会对总贡献产生的权值为：$\sum\limits_{i=l}^{r} a_i \times (i - l + 1)$。求操作后的总贡献的最大值。


## 说明/提示

**【样例解释 $\mathbf 1$】**

序列初始两端各有一个隔板。在序列第 $2$ 个位置，第 $7$ 个位置，第 $8$ 个位置后添加隔板。并将第 $1$ 个位置到第 $7$ 位置中间的元素翻转。最后得到的序列权值为 $10$。可以证明不存在比这更大的权值。

**【样例解释 $\mathbf 2$】**

本题提供大样例，该数据满足 `Subtask 3` 的限制。具体求解不做解释。

---

**【数据规模与约定】**

**本题开启子任务捆绑测试**。本题自动开启 O2 优化。


* Subtask 1（15 pts）：$n\leq 20$。
* Subtask 2（45 pts）：$n\leq 100$。
* Subtask 3（40 pts）：$n\leq 550$。

对于所有测试点满足 $1\leq n \leq 550$，$1\leq k \leq n$，$-10^9 \leq a_i \leq 10^9$。


## 样例 #1

### 输入

```
10 1
1 1 5 -4 -7 4 -8 0 -3 2 ```

### 输出

```
10```

# 题解

## 作者：_LFL_ (赞：2)

出题人题解。

## 前置
易得：
* 翻转时隔板固定和不固定对**最终的最大值**没影响，所以**隔板可以当成不固定来看**。

* 由上文可以得到：求翻转后大区间最大的权值，其实就是求把大区间划分为多个小区间，翻转每个小区间后的权值的和的最大值

  例：原区间：`| 1 | 2 3 | 4 5|`， 翻转整个区间，则变为：`| 5 4 | 3 2 | 1 |`，此时的权值与 `| 1 | 3 2 | 5 4 |` 相同。


注：此部分在正解预处理或暴力贪心时会有用。

## Subtask 1 (15 pts)：$n\leq20$。

暴力枚举隔板，然后贪心。

## Subtask 2~3 (100 pts)：$n\leq550$。

可以改变一下顺序，先选 $k$ 个互不重叠的区间进行翻转，然后在每个区间的两端插入隔板。这样，问题退化为分割问题。

考虑 dp：$dp_{i,j}$ 表示考虑前 $i$ 个元素，翻转 $j$ 次的最大权值，则转移为：

$$dp_{ij}=\max\{\max\limits_{k=j}^{i} \{dp_{k-1,j-1} + calc(k,i)\},\max\limits_{k=j + 1}^{i} \{dp_{k-1,j} + cost(k,i)\}\}$$

$calc(i,j)$ 表示翻转 $[i,j]$ 后，在这一段区间插入隔板可以做到此区间的最大权值。

$cost(i,j)$ 表示不翻转 $[i,j]$ 后，在这一段区间插入隔板可以做到此区间的最大权值。


dp 预处理 $cost$ 和 $calc$ 即可做到 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;

const int MAXN = 555;
int n, K, a[MAXN], dp[MAXN][MAXN], sum[2][MAXN][MAXN], val[2][MAXN][MAXN];

signed main(){
	IOS;
	cin >> n >> K;
	for(int i = 1; i <= n; i++) cin >> a[i];
	//预处理 
	
	memset(sum, 0xc0, sizeof sum);
	memset(dp, 0xc0, sizeof dp);
	//每个区间不翻转且中间没有隔板时的权值 
	for(int i = 1; i <= n; i++)
		for(int j = i; j <= n; j++)
			val[0][i][j] = val[0][i][j - 1] + a[j] * (j - i + 1);
	//每个区间翻转且中间没有隔板时的权值 
	for(int i = 1; i <= n; i++)
		for(int j = i; j >= 1; j--)
			val[1][j][i] = val[1][j + 1][i] + a[j] * (i - j + 1);
	//每个区间不翻转且中间可以有隔板时的最大权值 
	for(int i = 1; i <= n; i++)
		for(int j = i; j <= n; j++){
			sum[0][i][i - 1] = 0;
			for(int k = j; k >= i; k--)
				sum[0][i][j] = max(sum[0][i][j], sum[0][i][k - 1] + val[0][k][j]); 
		}
	//每个区间翻转且中间可以有隔板时的最大权值 
	for(int i = 1; i <= n; i++)
		for(int j = i; j >= 1; j--){
			sum[1][i + 1][i] = 0;
			for(int k = j; k <= i; k++)
				sum[1][j][i] = max(sum[1][j][i], sum[1][k + 1][i] + val[1][j][k]);//由前置可得，求翻转后大区间最大的权值，其实就是求把大区间划分为多个小区间，翻转每个小区间后的权值的和的最大值 
		}

	//初始化 
	dp[0][0] = 0;
	for(int i = 1; i <= n; i++) dp[i][0] = sum[0][1][i];
	
	//DP 
	int ans = dp[n][0];
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= min(i, K); j++){
			for(int k = i; k >= j; k--){
				dp[i][j] = max(max(dp[i][j], dp[k - 1][j] + sum[0][k][i]), dp[k - 1][j - 1] + sum[1][k][i]);
			}
			if(i == n) ans = max(ans, dp[i][j]);
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：_lmh_ (赞：1)

令 $g_{l,r}$ 为：只考虑下标 $[l,r]$ 中元素（$l$ 左侧和 $r$ 右侧都放隔板），中间随意放隔板，不整体翻转的最大收益，$h_{l,r}$ 为整体翻转时的最大收益，这个区间 dp 是简单的。

然后令 $f_{i,j}$ 为前 $i$ 个数进行了 $j$ 次区间翻转的最大收益，直接转移即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=557;
ll n,k,ans=-1e18,a[N],f[N][N],g[N][N],h[N][N];
int main(){
	cin>>n>>k;
	for (int i=1;i<=n;++i){cin>>a[i];g[i][i]=h[i][i]=a[i];}
	for (int len=2;len<=n;++len) for (int l=1,r=len;r<=n;++l,++r){
		g[l][r]=g[l][r-1]+a[r]*(r-l+1);
		h[l][r]=h[l+1][r]+a[l]*(r-l+1);
	}
	for (int len=2;len<=n;++len) for (int l=1,r=len;r<=n;++l,++r) for (int k=l;k<r;++k){
		g[l][r]=max(g[l][r],g[l][k]+g[k+1][r]);
		h[l][r]=max(h[l][r],h[l][k]+h[k+1][r]);
	}
	memset(f,-0x3f,sizeof(f));f[0][0]=0;
//	for (int l=1;l<=n;++l) for (int r=l;r<=n;++r) cout<<l<<' '<<r<<' '<<g[l][r]<<' '<<h[l][r]<<endl;
	for (int i=1;i<=n;++i) for (int j=0;j<=k;++j){
		for (int l=0;l<i;++l) f[i][j]=max(f[i][j],f[l][j]+g[l+1][i]);
		if (j) for (int l=0;l<i;++l) f[i][j]=max(f[i][j],f[l][j-1]+h[l+1][i]);
//		cout<<i<<' '<<j<<' '<<f[i][j]<<endl;
	}
	for (int i=0;i<=k;++i) ans=max(ans,f[n][i]);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：poembelief (赞：1)

# 题目
[题目传送门](https://www.luogu.com.cn/problem/P11743)
# 分析
这题一看就知道，要么贪心要么 DP，而这题看着不像是能贪的，所以我们考虑 DP。

我们先不考虑翻转的现象，那么这题是非常显然的线性 DP，预处理后从前往后枚举最近一个隔板的位置即可。

根据线性 DP 的转移，我们可以发现如果只用一个数组去存状态，空间复杂度和时间复杂度都会爆炸，所以我们考虑用两个数组，一个用来记录原数组的信息，另一个用来记录翻转后的数组信息，然后分别转移，最后再合并信息即可，具体实现可见代码。

因为本题存在负数，所以一定要记得**初始化**！！！

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
/*
	f[i][j]：原数组考虑区间[i,j]
	g[i][j]：反转后数组考虑区间[i,j]
*/
const int N=1005;
int n,m;
long long f[N][N],g[N][N],ans[N][N],sum[N],tot[N],sum1[N],tot1[N],a[N],b[N];
int main(){
	memset(f,0xc0,sizeof(f));
	memset(g,0xc0,sizeof(g));
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	freopen("tx.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		b[n-i+1]=a[i];
		f[i][i]=a[i];
		sum[i]=sum[i-1]+a[i]*i;
		tot[i]=tot[i-1]+a[i];
	}
	for(int i=1;i<=n;i++){
		g[i][i]=b[i];
		sum1[i]=sum1[i-1]+b[i]*i;
		tot1[i]=tot1[i-1]+b[i];
	}
	for(int len=2;len<=n;len++){
		for(int i=1,j=len;j<=n;i++,j++){
			f[i][j]=sum[j]-sum[i-1]-(tot[j]-tot[i-1])*(i-1);
			g[i][j]=sum1[j]-sum1[i-1]-(tot1[j]-tot1[i-1])*(i-1);
			for(int mid=i;mid<j;mid++){
				f[i][j]=max(f[i][j],f[i][mid]+f[mid+1][j]);
				g[i][j]=max(g[i][j],g[i][mid]+g[mid+1][j]);
			}
		}
	}
	for(int i=1;i<=n;i++){
		ans[i][0]=f[1][i];
		for(int k=1;k<=m;k++){
			ans[i][k]=ans[i][k-1];
			for(int j=1;j<=i;j++){//从j开始考虑 
				ans[i][k]=max(ans[i][k],ans[j-1][k]+f[j][i]);
				ans[i][k]=max(ans[i][k],ans[j-1][k-1]+g[n-i+1][n-j+1]);
			}
		}
	}
	printf("%lld\n",ans[n][m]);
	return 0;
}
```

---

## 作者：ForgetOIDuck (赞：0)

### 题意：

给定一个长度为 $N$ 的数列 $A$，可以在空隙里任意插隔板，开始时开头结尾已有隔板。

可以以隔板为端点选择不超过 $K$ 个 **不相交** 区间并将其 **数字** 翻转，隔板不动。

最后计算的总贡献：若两隔板 $l, r$ 相邻产生贡献为 $\sum_{i=l} ^r A_i\times (i - l + 1)$。

求可能的最大总贡献。

### 思路：

发现翻转区间不相交一眼 dp。

设 $dp_{i,j}$ 表示前 $i$ 个数中已经翻转 $j$ 次的最大总贡献。

易得 $dp_{i,j}=\max_{1\le k\le i}\{dp_{k - 1,j} + w1(k, i), dp_{k - 1, j - 1}+w2(k,i)\}$，其中 $w1(l,r)$ 表示 **不翻转**，可以在中间任意插隔板，所能获得这个区间的最大贡献；$w2(l,r)$ 表示 **翻转** 这个区间，可以在中间任意插隔板，所能获得这个区间的最大贡献。

但是我们发现 $w1$ 其实是不需要的，因为我们计算 $dp$ 数组时也相当于在区间内插隔板，也能取得相同效果。

于是变成 $dp_{i,j}=\max_{1\le k\le i}\{dp_{k - 1,j} + c(k, i), dp_{k - 1, j - 1}+w(k,i)\}$，其中 $c(l,r)$ 表示 **不翻转**，**不** 插隔板，所能获得这个区间的最大贡献；$w(l,r)$ 同 $w2(l,r)$。

$c(l,r)=\sum_{i=l}^r A_i\times(i-l+1)$ 可以直接暴力算出来，我们看看怎么搞这个 $w$。

我们发现计算时不需要真正地把区间转过来，我们只要假装转了然后把 $r$ 当成 $l$ 用和 $c$ 一样的计算方法即可。

把一个大的区间翻转过来再插隔板计算贡献，其实等价于把隔板分成的每个区间单独翻过来计算贡献然后加一起，不需要在意这几个区间的顺序，我们只需要知道这几个是一起翻转的。

类似地，我们有了和 $c$ 一样的对 $w$ 意义的简化方法：$w$ 表示，翻转这个区间，**不** 插隔板，所能获得这个区间的最大贡献。

于是它也有了和 $c$ 一样的计算方法：$w(l,r)=\sum_{i=l}^r A_i\times(r-i+1)$。

最终答案 $\min_{0\le i\le K}\{dp_{n,i}\}$。

我们来计算一下时间复杂度：$c,w$ 可预处理，时间复杂度是 $O(N^2)$ 的，dp 需要枚举 $i,j,k$，时间复杂度是 $O(N^2K)$ 的，由于 $N,K$ 同级加起来是 $O(N^3)$ 级别的。

当然我不知道这东西满不满足四边形不等式，可能还能优化。

$c,w$ 的计算也是可以拆开来然后优化成 $O(n)$ 的。不过这种卡常小寄巧对于本题似乎没什么用。

### AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[552], c[552][552], w[552][552], dp[552][552], n, K;
int main() {
	cin >> n >> K;
	for (ll i = 1; i <= n; i ++ ) cin >> a[i];
	for (ll l = 1; l <= n; l ++ ) for (ll r = l; r <= n; r ++ ) c[l][r] = c[l][r - 1] + a[r] * (r - l + 1);
	for (ll r = n; r; r -- ) for (ll l = r; l; l -- ) w[l][r] = w[l + 1][r] + a[l] * (r - l + 1);
	for (ll i = 1; i <= n; i ++ ) for (ll j = 0; j <= K; j ++ ) {
		dp[i][j] = -1e18;
		for (ll k = 0; k <= i; k ++ ) {
			dp[i][j] = max(dp[i][j], dp[k][j] + c[k + 1][i]);
			if (j) dp[i][j] = max(dp[i][j], dp[k][j - 1] + w[k + 1][i]);
		}
	}
	ll ans = 0;
	for (ll i = 0; i <= K; i ++ ) ans = max(ans, dp[n][i]);
	cout << ans;
}
```

---

