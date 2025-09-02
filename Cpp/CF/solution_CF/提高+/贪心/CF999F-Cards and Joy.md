# Cards and Joy

## 题目描述

有 $n$ 个玩家坐在桌子旁。每个玩家都有一个喜欢的数字。第 $j$ 个玩家的喜欢数字是 $f_j$。

桌子上有 $k \cdot n$ 张卡牌。每张卡牌都包含一个整数：第 $i$ 张卡牌包含数字 $c_i$。此外，您还会得到一个序列 $h_1, h_2, \dots, h_k$。下面将解释它的含义。

玩家们分配所有卡牌后，应使每个玩家都持有恰好 $k$ 张卡牌并使他们的欢乐值总和最大。在分配完所有卡牌后，每个玩家计算他手中包含他喜欢的数字的卡牌数量。如果玩家持有 $t$ 张包含他喜欢数字的卡牌，则他的欢乐值等于 $h_t$。如果玩家没有得到他喜欢数字的卡牌（即 $t=0$），则他的欢乐值为 $0$。

输出在分配卡牌后玩家的最大可能总欢乐值。请注意，序列 $h_1, \dots, h_k$ 对于所有玩家都是相同的。

## 样例 #1

### 输入

```
4 3
1 3 2 8 5 5 8 2 2 8 5 2
1 2 2 5
2 6 7
```

### 输出

```
21
```

## 样例 #2

### 输入

```
3 3
9 9 9 9 9 9 9 9 9
1 2 3
1 2 3
```

### 输出

```
0
```

# 题解

## 作者：guanyf (赞：7)

### 题意：
有 $n$ 个人，每个人都喜欢一个幸运数字 $f_i(1 \le i \le n)$。每次他们可以选择 $k$ 个数，当他们选择了 $j(1 \le j \le k)$  个幸运数字后，幸福值是 $h_j$。现在给定 $n \times k$ 个数字 $c_x(1 \le x \le n \times k)$，求最多能得到多少幸福值。
### 导入：
最容易想到的就是暴搜前 $i$ 个人选了哪些数设状态为 $i,j,v$，表示前 $i-1$ 个人有了 $v$ 的幸福值时第 $i$ 个人选择了 $j$ 个数。当 $j \le k$，就选择一个没有被选择的数，当选了自己的幸运数字时就将计数器 $sum$ 加一，然后转移到 $i,j+1,v$，否则转移到 $i+1,1,v+h_{sum}$。当 $i > n$ 时，则更新答案。

代码：[TLE の 记录](https://codeforc.es/contest/999/submission/201623363)

显而易见，肯定超时。这时候，就要考虑优化了：对于每个相同的 $i,j,v$，因为它们对答案的贡献完全一致，因此只需要保留一个就行了。这个剪枝虽然可能优化时间，却不会优化时间复杂度，并且它为了保证答案的正确性，就只能优化 $i$ 这一维，$j$ 是完全优化不了，因此没有任何用。
### 分析：
为了真正的优化时间，就只能优化状态和改变处理方式了。首先，要明白一个显而易见的性质：**假设当前是第 $i$ 个人，那么 $c$ 中不是 $f_i$ 的数对答案就没有影响。而当若干个人的幸运数字相同时，他们本质上没有任何区别**。因此我们就可以考虑对于相同幸运数字的人，将他们分成一组。然后对于每个组，计算最大的幸福值，在计算的过程中，只需要考虑 $c$ 中与 $f_i$ 相同的数的分配就行了。最后，将幸福值相加就是最终答案。

根据上述结论，就会延伸出一个问题：**如何保证每个人都选了 $k$ 个数字**？实际上，我们在操作过程中是可以令每个人选的数量都 $\le k$。接着，对于每个选择数量 $<  k$ 的人来说，我们可以用用不到的数来填满它。注意：**那些可以用到但多出来的数也是可以用来填的**。上述思路只是一个理解，并不需要实现这个过程，我们只需要完成填补前的操作就行了。

为了更方便的理解问题，我们可以只考虑其中一组最多能达到的幸福值，然后再将每个组的答案相加。为了能更清楚的表现出当前的局面，因此不妨考虑状态为 $i,j,v$，分别表示前 $i$ 个人已经选了 $j$ 个幸运数字之后有 $v$ 的幸福值。每个人都可以选择 $x(1 \le \min(j,k))$ 个幸运数字，因此转移就是：
$$i,j,v \rightarrow i-1,j-x,v+h_x$$
每次转移就是当前这个人选择了 $x$ 个幸运数字后的状态，答案就是幸福值最多的一条路径。

对于每一个相同的 $i,j,v$，它们对答案的贡献完全相同，只有选择的方案不同，因此可以只保留一个。对于答案来说，我们不需要知道它每次选择的方案，只需要知道它的代价，因此我们只需要保留单个状态就行了。

算法：搜索。

时间复杂度：$\operatorname{O}(n \times k^2)$

不会去重导致几乎全部超时：[TLE の 记录](https://codeforc.es/contest/999/submission/200972364)

### 思路：
这题的状态图一看就是有拓扑序的，因此可以动态规划。首先优化一下状态，考虑状态分组。可以发现，对于每一个 $i,j$，只要它的 $v$ 最优，那么它作最优的转移之后就不会比其他状态作最优的转移后更劣。因此我们就可以将 $i,j$ 分在一起，$v$ 作为附带属性。对于每个 $i,j$ 相等的状态，只需要保留 $v$ 最优的那个就行了。

由于我们并不知道每次转移是不是最优的，因此转移是无法优化的。

状态数量依旧是 $n \times k$，转移不变，因此时间复杂度也不变。

状态转移方程： 	
$$dp_{i,j}=\max(dp_{i,j},dp_{i-1,j-x}+h_x)$$

#### 代码：
```cpp
#include <algorithm>
#include <iostream>
#include <unordered_map>
using namespace std;
const int MAXN = 5005;
int n, k, v[MAXN], ans, dp[MAXN][MAXN];
unordered_map<int, int> a, b;
int main() {
  ios::sync_with_stdio(0);
  cin >> n >> k;
  for (int i = 1, x; i <= n * k; i++) {
    cin >> x, a[x]++;  // 值为x的数字出现的次数
  }
  for (int i = 1, x; i <= n; i++) {
    cin >> x, b[x]++;  // 幸运数字为x的人出现的次数，等同于分组
  }
  for (int i = 1; i <= k; i++) {
    cin >> v[i];
  }
  for (auto i : b) {                            // 对于每个组
    for (int j = 1; j <= i.second; j++) {       // 枚举人
      for (int x = 1; x <= a[i.first]; x++) {   // 枚举数字
        for (int y = 1; y <= min(x, k); y++) {  // 枚举选了多少数字
          dp[j][x] = max(dp[j][x], dp[j - 1][x - y] + v[y]);
        }
      }
    }
    ans += dp[i.second][a[i.first]];
    fill(dp[0], dp[n] + k + 1, 0);
  }
  cout << ans;
  return 0;
}
```

### 拓展延伸
实际上我们并不需要对于每个分组都进行考虑，因为真正影响答案的是数出现的次数而不是值。因此我们可以预处理出前 $i$ 个人选了 $j$ 个数字的最大幸福值，然后对于每个分组都依次累加答案就行了。

#### 代码
```cpp
#include <algorithm>
#include <iostream>
#include <unordered_map>
using namespace std;
const int MAXN = 5005;
int n, k, v[MAXN], ans, dp[MAXN][MAXN];
unordered_map<int, int> a, b;
int main() {
  ios::sync_with_stdio(0);
  cin >> n >> k;
  for (int i = 1, x; i <= n * k; i++) {
    cin >> x, a[x]++;
  }
  for (int i = 1, x; i <= n; i++) {
    cin >> x, b[x]++;
  }
  for (int i = 1; i <= k; i++) {
    cin >> v[i];
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n * k; j++) {
      for (int x = 1; x <= min(j, k); x++) {
        dp[i][j] = max(dp[i][j], dp[i - 1][j - x] + v[x]);
      }
    }
  }
  for (auto i : b) {
    ans += dp[i.second][a[i.first]];
  }
  cout << ans;
  return 0;
}
```


---

## 作者：Rushroom (赞：4)

传送门 [CF999F Cards and Joy](https://www.luogu.com.cn/problem/CF999F)

可以发现，对于每个人，只有拿到自己喜欢的数字才有用，拿到其他数字都没用。因为每个人只有一个喜欢的数字，如果得到一张没有他喜欢的数字的卡片，他的快乐值不会变化。因此可以只考虑每个人只拿到自己喜欢的数字，使快乐值最大，显然可以用 dp 解决。

### 状态

设 $dp_{i,j}$ 表示有 $i$ 个人喜欢同样的数字，这种数字的牌有 $j$ 个，最多能获得多少分。

我们用两个数组 $p$ 和 $num$ 分别表示喜欢 $i$ 这个数字有多少人和有多少个数字 $i$。

### 状态转移方程

 $$dp_{i,j}=max(dp_{i-1,j-x}+h_x)$$
 
 $$ans=\sum_{i=1}^{10^5}dp_{p_i,num_i}$$
 
 时间复杂度为 $O(n^2k^2)$。
 

### AC代码
 
 ```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define forr(i, a, n) for (int i = a; i <= n; i++)
#define rep(i, n) forr(i, 0, n - 1)
#define repp(i, n) forr(i, 1, n)
#define pb push_back
#define mp make_pair
#define init(a, i) memset(a, i, sizeof(a))
#define fi first
#define se second
#define mod 1000000007
#define MOD 998244353
#define MAXN 0x3f3f3f3f
int T, case_;
int n, k, c, f, h[11], p[100005], num[100005];
int dp[510][5100], ans = 0;
void solve()
{
    cin >> n >> k;
    rep(i, n * k)
    {
        cin >> c;
        num[c]++;
    }
    rep(i, n)
    {
        cin >> f;
        p[f]++;
    }
    repp(i, k) cin >> h[i];
    repp(i, n)
    {
        rep(j, n * k + 1)
        {
            rep(l, min(k, j) + 1)
            {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - l] + h[l]);
            }
        }
    }
    repp(i, 100000) ans += dp[p[i]][num[i]];
    cout << ans;
}
int main()
{
    T = 1;
    //cin>>T;
    for (case_ = 1; case_ <= T; case_++)
        solve();
    return 0;
}
```


---

## 作者：永不复行 (赞：3)

   题意：
   
   有n个玩家坐在一张桌子前面，每一个玩家都有自己喜欢的数字，第j个人的喜欢数字为fj一共有k*n张卡牌在桌子上，每一张牌都有一个数字ci，然后把卡牌分发给所有人，每人都要获得k张卡牌。现在给你一个数列h1,h2...hk，表示每个人拿到i张印着自己喜欢数字的卡牌时能获得的快乐值，现在问最大快乐值之和是多少
    
所以不在h数组里的ci无用 

先用o（n）排掉无用卡

注意，dp的是第j人持t张卡（塞人进去）

```cpp
#include<bits/stdc++.h>
using namespace std;
	long long n,k,c[5100],f[510],h[11],dp[5100][510],hash1[300001],hash2[300001];
	long long ans;
int main(){
	scanf("%lld%lld",&n,&k);
	for(long long i=1;i<=n*k;i++)scanf("%lld",&c[i]),hash1[c[i]]++;
	for(long long i=1;i<=n;i++)scanf("%lld",&f[i]),hash2[f[i]]++;
	for(long long i=1;i<=k;i++)scanf("%lld",&h[i]);
	sort(f+1,f+n+1); long long tmp=f[1]-1;
	for(long long i=1;i<=n*k;i++){
		long long mn=min(i,k);
		dp[i][1]=h[mn]; 
		for(long long j=2;j<=n;j++)for(long long t=1;t<=mn;t++)dp[i][j]=max(dp[i][j],dp[i-t][j-1]+h[t]);
	}
	for(long long i=1;i<=n;){
		tmp=f[i];
		i+=hash2[tmp];
		ans+=dp[hash1[tmp]][hash2[tmp]];
	}
	printf("%lld\n",ans);
}
    
```
    



---

## 作者：Daniel_7216 (赞：2)

题目大意：有 $n$ 个人均分 $k\times n$ 个数字，每个人都有一个喜欢的数字，当分到 $i$ 个自己喜欢的数字时就会获得 $h_i$ 的得分，求最大得分。

因为最后的得分取决于每个人获得喜欢数字的个数，所以我们可以考虑对于每一种牌的分配，都抽象为 $i$ 个人分 $j$ 张纸牌时的最大开心值，用 $dp_{i,j}$ 表示。不妨假设这 $i$ 个人喜欢同一种数字，然后我们可以写出方程：

$$dp_{i,j}=\max\limits_{k=0}^j (dp_{i-1,k}+h_{j-k})$$ 

这样，我们统计答案时就只关心每种牌有多少张，有多少人喜欢，具体来说，设第 $i$ 种牌喜欢的人有 $num_i$，这种牌有 $cnt_i$ 张。最后答案就是：

$$\sum\limits_{i}dp_{num_i,cnt_i}$$

提前预处理出 $dp$ 数组，然后用一个桶来辅助统计答案即可。

---

## 作者：Phartial (赞：2)

注意到 $f_i$ 不同的人之间没有关联，则可以将问题转化成如下问题：

> 将 $n$ 张牌分给 $m$ 个人，一个人如果拿到了 $i$ 张牌喜悦值就是 $h_i$，求最大的喜悦值。

不难看出状态为 $f_{i,j}$，即将 $i$ 张牌分给 $j$ 个人的最大喜悦值，可以推出转移方程如下：

$$ f_{i,j}=\max_{k=0}^{i} f_{i-k,j-1}+h_k $$

然后直接暴力算就好了。

```cpp
#include <algorithm>
#include <iostream>

using namespace std;

const int kN = 502, kK = 11;

int n, k, c[kN * kK], f[kN], h[kK], dp[kN * kK][kN], ans;

int main() {
  cin >> n >> k;
  for (int i = 1; i <= n * k; ++i) {
    cin >> c[i];
  }
  for (int i = 1; i <= n; ++i) {
    cin >> f[i];
  }
  for (int i = 1; i <= k; ++i) {
    cin >> h[i];
  }
  for (int j = 1; j <= n; ++j) {
    for (int i = 1; i <= n * k; ++i) {
      for (int u = 0; u <= min(i, k); ++u) {
        dp[i][j] = max(dp[i][j], dp[i - u][j - 1] + h[u]);
      }
    }
  }
  sort(f + 1, f + n + 1);
  for (int i = 1, j = 0; i <= n + 1; ++i, ++j) {
    if (f[i] != f[i - 1]) {
      ans += dp[count(c + 1, c + n * k + 1, f[i - 1])][j], j = 0;
    }
  }
  printf("%d", ans);
  return 0;
}
```

---

## 作者：legendgod (赞：1)

[CF999F Cards and Joy](https://www.luogu.com.cn/problem/CF999F)

我们首先考虑题目的本质，对于答案产生了贡献的只有一个人拿到了自己喜欢的牌。我们考虑将每一种牌分开进行考虑，可以发现对于每一种牌，其产生贡献的方式是完全相同的。这也就意味着我们可以对于每一种牌分开计算答案。

我们考虑怎么计算，首先需要知道这个牌喜欢的人数，然后要将这么多牌分给很多人。这其实就和背包类似，每一张牌的容量为 1。我们设 $dp[i][j]$ 表示有 i 个人，j 张牌的最大贡献。我们可以通过枚举最后一个人拿了几张牌进行转移。

```cpp
#include <bits/stdc++.h>
using namespace std;

//#define Fread

#ifdef Fread
#define getchar() ((p1 == p2 && p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin)) ? EOF : *p1 ++)
char buf[1 << 21], *p1, *p2;
#endif // Fread

template <typename T>
void r1(T &x) {
	x = 0;
	char c(getchar());
	int f(1);
	for(; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for(; isdigit(c);c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
	x *= f;
}
#define int long long
const int maxn = 5e3 + 100;
const int maxm = maxn << 1;

typedef int room[maxn];

int n, k;
int ctr[maxn * 2], ctp[maxn * 2];
int c[maxn * 2], a[maxn * 2], tot(0), h[maxn * 2], f[maxn * 2];
int dp[505][maxn], vis[maxn * 2];
signed main() {
//    freopen(".in", "r", stdin);
//    freopen(".out", "w", stdout);
	int i, j;
    r1(n), r1(k);
    for(i = 1; i <= n * k; ++ i) r1(a[i]), c[i] = a[i];
    tot = n * k;
    for(i = 1; i <= n; ++ i) r1(f[i]), c[++ tot] = f[i];
    sort(c + 1, c + tot + 1); int len = unique(c + 1, c + tot + 1) - c - 1;
    for(i = 1; i <= n * k; ++ i) a[i] = lower_bound(c + 1, c + len + 1, a[i]) - c, ctp[a[i]] ++;
    for(i = 1; i <= n; ++ i) f[i] = lower_bound(c + 1, c + len + 1, f[i]) - c, ctr[f[i]] ++;
    for(i = 1; i <= k; ++ i) r1(h[i]);
    for(i = 1; i <= n; ++ i) {
        for(j = 1; j <= n * k; ++ j) {
            for(int z = 1; z <= min(k, j); ++ z) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - z] + h[z]);
            }
        }
    }
    int ans(0);
    for(i = 1; i <= n; ++ i) if(!vis[f[i]]) ans += dp[ctr[f[i]]][ctp[f[i]]], vis[f[i]] = 1;
    printf("%lld\n", ans);
	return 0;
}

```


---

## 作者：kodiak (赞：1)

**题目大意：有$n$个玩家坐在一张桌子前面，每一个玩家都有自己喜欢的数字，第$j$个人的喜欢数字为$f_j$
一共有$k\times n$张卡牌在桌子上，每一张牌都有一个数字$c_i$，然后把卡牌分发给所有人，每人都要获得$k$张卡牌。**

**现在给你一个数列$h_1,h_2...h_k$，表示每个人拿到$i$张印着自己喜欢数字的卡牌时能获得的快乐值，现在问最大快乐值之和是多少**

------------

可以发现这个题中只有玩家喜欢的牌是有意义的

因此储存的时候只需要记录每一种牌喜欢的人数就行了

这里以防万一用了离散化，但好像不用离散化也行

------------
然后就是答案的处理，可以看出来是背包

我们设$do[i][j]$为有$i$个人，$j$张牌的情况下最大的快乐值之和

$dp$方程就是$dp[i][j]=max(dp[i-1][j-l]+h[l])$

对于每一种牌(有$a$个人喜欢，共有$b$张，可以分得的最大快乐之和就是$dp[a][b]$


代码
```ccp
#include<bits/stdc++.h>
using namespace std;
#define MAXN 510
#define MAXM 20
vector<int>vc;
vector<int>cnt;
int val[MAXN];
int ha[MAXN];
int cnt1[MAXN*MAXM];
int dp[MAXN][MAXM*MAXN];
int main()
{
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n*k;i++)
	{
		int x;
		scanf("%d",&x);
		if(vc.empty())
		{
			vc.push_back(x);
			cnt.push_back(1);
			continue;
		}
		int pl=lower_bound(vc.begin(),vc.end(),x)-vc.begin();
		if(vc[pl]==x)
		{
			cnt[pl]++;
		}
		else
		{
			vc.insert(vc.begin()+pl,x);
			cnt.insert(cnt.begin()+pl,1);
		}
	}//离散化
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&val[i]);
		int pl=lower_bound(vc.begin(),vc.end(),val[i])-vc.begin();
		if(vc[pl]==val[i])
		{
			cnt1[pl]++;
		}
	}//统计
	for(int i=1;i<=k;i++)
	{
		scanf("%d",&ha[i]);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n*k;j++)
		{
			for(int l=1;l<=j&&l<=k;l++)
			{
				dp[i][j]=max(dp[i-1][j-l]+ha[l],dp[i][j]);
			}
		}
	}//dp
	int ans=0;
	for(int i=0;i<vc.size();i++)
	{
		int p=cnt[i];
		ans+=dp[cnt1[i]][cnt[i]];
	}
	cout<<ans;
}
```
	2.33s /  23.74MB /  1.03KB C++

---

## 作者：大菜鸡fks (赞：1)

注意到每个人是同质的。

dp[i][j]表示选j个人用i张牌得到的最大价值。随便转移

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100005;
typedef long long ll;
int n,K,w[11],cnt[N],ton[N];
inline void init(){
	scanf("%d%d",&n,&K);
	for (int i=1;i<=n*K;i++){
		int x; scanf("%d",&x);
		cnt[x]++;
	}
	for (int i=1;i<=n;i++){
		int x; scanf("%d",&x);
		ton[x]++;
	}
	for (int i=1;i<=K;i++){
		scanf("%d",&w[i]);
	}
} 
int dp[5005][505];
ll ans;
inline void solve(){
	for (int i=1;i<=n*K;i++){
		dp[i][1]=w[min(i,K)];
		for (int j=2;j<=n;j++){
			for (int k=1;k<=min(i,K);k++){
				dp[i][j]=max(dp[i][j],dp[i-k][j-1]+w[k]);
			}
		}
	}
	for (int i=0;i<=1e5;i++){
		ans+=dp[cnt[i]][ton[i]];
	}
	printf("%I64d\n",ans); 
}
int main(){
	init();
	solve();
	return 0;
} 
```

---

