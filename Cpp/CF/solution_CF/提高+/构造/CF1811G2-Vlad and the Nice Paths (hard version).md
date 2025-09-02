# Vlad and the Nice Paths (hard version)

## 题目描述

This is hard version of the problem, it differs from the easy one only by constraints on $ n $ and $ k $ .

Vlad found a row of $ n $ tiles and the integer $ k $ . The tiles are indexed from left to right and the $ i $ -th tile has the color $ c_i $ . After a little thought, he decided what to do with it.

You can start from any tile and jump to any number of tiles right, forming the path $ p $ . Let's call the path $ p $ of length $ m $ nice if:

- $ p $ can be divided into blocks of length exactly $ k $ , that is, $ m $ is divisible by $ k $ ;
- $ c_{p_1} = c_{p_2} = \ldots = c_{p_k} $ ;
- $ c_{p_{k+1}} = c_{p_{k+2}} = \ldots = c_{p_{2k}} $ ;
- $ \ldots $
- $ c_{p_{m-k+1}} = c_{p_{m-k+2}} = \ldots = c_{p_{m}} $ ;

Your task is to find the number of nice paths of maximum length. Since this number may be too large, print it modulo $ 10^9 + 7 $ .

## 说明/提示

In the first sample, it is impossible to make a nice path with a length greater than $ 0 $ .

In the second sample, we are interested in the following paths:

- $ 1 \rightarrow 3 \rightarrow 4 \rightarrow 5 $
- $ 2 \rightarrow 4 \rightarrow 5 \rightarrow 7 $
- $ 1 \rightarrow 3 \rightarrow 5 \rightarrow 7 $
- $ 1 \rightarrow 3 \rightarrow 4 \rightarrow 7 $

In the third example, any path of length $ 8 $ is nice.

## 样例 #1

### 输入

```
5
5 2
1 2 3 4 5
7 2
1 3 1 3 3 1 3
11 4
1 1 1 1 1 1 1 1 1 1 1
5 2
1 1 2 2 2
5 1
1 2 3 4 5```

### 输出

```
1
4
165
3
1```

# 题解

## 作者：苏联小渣 (赞：11)

序列分段，还是子序列，不难想到 dp。

设 $f_i$ 表示以 $i$ 为结尾，且最后一段颜色为 $a_i$ 的子序列最大长度。

设 $g_i$ 表示以 $i$ 为结尾，且最后一段颜色为 $a_i$ 的长度最大的子序列个数。

转移时，我们只需要枚举最后的一段。那么从 $j$ 转移到 $i$，$j$ 合法的条件是：

$$\sum_{x=j+1}^i[a_x=a_i] \ge k$$

那么我们枚举每一个 $j$。如果 $j$ 合法，那么容易写出 $f_i$ 的转移方程：

$$f_i=\max_{j}\{f_j+k\}$$

转移完 $f_i$ 之后，我们只需要从最终状态出发转移 $g_i$：对于所有满足 $f_j+k=f_i$ 的 $j$，假设从 $j+1$ 到 $i$ 这一段，一共有 $col_j$ 个颜色 $a_i$，可以写出 $g_i$ 的转移方程：

$$g_i=\sum_{j} f_j \times {col_j-1 \choose k-1}$$

原因就是 $a_i$ 必须得选，其它的只要随意挑 $k-1$ 个就行了。

预处理组合数，时间复杂度 $O(n^2)$。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
#define N 5000
int t, n, k, ans, mx, a[5010], f[5010], s[5010], jc[5010], inv[5010];
const int mo = 1e9 + 7;
int power(int x, int y){
	int ret = 1;
	while (y){
		if (y&1) ret = 1LL * ret * x % mo;
		x = 1LL * x * x % mo;
		y >>= 1;
	}
	return ret;
}
int C(int x, int y){
	return 1LL*jc[x]*inv[y]%mo*inv[x-y]%mo;
}
int main(){
	scanf ("%d", &t);
	jc[0] = 1;
	for (int i=1; i<=5000; i++){
		jc[i] = 1LL * jc[i-1] * i % mo;
	}
	inv[N] = power(jc[N], mo-2);
	for (int i=N-1; i>=0; i--){
		inv[i] = 1LL * inv[i+1] * (i+1) % mo;
	}
	while (t --){
		scanf ("%d%d", &n, &k);
		for (int i=1; i<=n; i++){
			s[i] = f[i] = 0;
			scanf ("%d", &a[i]);
		}
		s[0] = 1;
		for (int i=k; i<=n; i++){
			int now = 0;
			for (int j=i; j>=0; j--){
				if (now >= k){
					if (f[j] + k > f[i]){
						f[i] = f[j] + k;
						s[i] = (1LL * s[j] * C(now-1, k-1)) % mo;
					}
					else if (f[j] + k == f[i]){
						s[i] = (s[i] + 1LL * s[j] * C(now-1, k-1) % mo) % mo;
					}
				}
				if (a[j] == a[i]) now ++; 
			}
		}
		mx = -1, ans = 0;
		for (int i=0; i<=n; i++){
			if (f[i] > mx) mx = f[i], ans = s[i];
			else if (f[i] == mx) ans = (ans + s[i]) % mo;
		}
		printf ("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：IGA_Indigo (赞：6)

## 题目大意
和简单版一样，还是一个叫 Vlad 的人找到了 $n$ 块瓦片（也不知道为什么翻译成了跳粉丝这么抽象的设定），这几块瓦片有不同的颜色，要求找到一个好的序列满足题目中所给的颜色要求，问最长的好的序列有几种情况。
## 大体思路
看到这个题先是想到的简单而暴力的 $O(n^3)$ 做法，就是设定 $f[i][j]$ 为处理前 $i$ 个人，选了 $j$ 个人的最大值。

但很显然这种方法无法 A 掉这道题，在累加的时候太费时间了，我们不难想出可以用组合数的方法来优化一下。

首先先用 $zh[i][j]$ 数组存 $C_j^i$ 的组合数，就是一个杨辉三角，然后开始每一组的 DP。
### 状态设置
$f[i]$ 表示以 $i$ 个数的为最后一个数，考虑完前 $i$ 个数的最长长度，他要问的个数我们再定义一个 $fs[i]$ 代表长度为 $f[i]$ 时的可能方案数。
### 状态转移
设第 $j+1$ 个元素前面有 $d$ 个跟 $c[i]$ 相同颜色的瓦片，所以我们得到 $f$ 和 $fs$ 的转移方程：

因为如果 $j+1$ 到 $i$ 和 $c[i]$ 相同的颜色大于 $k$ 就可以转移，所以：

- 如果 $f[j]+k>f[i]$，说明 $f[i]$ 可以更新，我们就能写出：

	$f[i]=f[j]+k$.
    
    $fs[i]=fs[j]\times zh[d-1][k-1]$.
    
- 如果 $f[j]+k==f[i]$，说明情况是一样的，他们可以加在一起，就有：

   $fs[i]=fs[i]+fs[j]\times zh[d-1][k-1]$.
### 答案输出
枚举每个 $f[i]$，求出最大的 $f[i]$，然后存他的方案数 $g[i]$，最后输出就行。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long f[5005],fs[5005];
long long c[5005];//输入的粉丝颜色 
long long zh[5005][5005];//C(i,j)组合数预处理 
int main(){
	int t;
	cin>>t;
	zh[0][0]=1;
	for(int i=1;i<=5000;i++){
		zh[i][0]=1;
		for(int j=1;j<=i;j++){
			zh[i][j]=(zh[i-1][j]+zh[i-1][j-1])%1000000007;//C(n,m)=C(n-1,m-1)+C(n,m-1) 
		}
	}//将组合数预处理出来 
	while(t--){
		int n,k;
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			f[i]=0;
			fs[i]=0;
		}//清零数组
		for(int i=1;i<=n;i++){
			cin>>c[i];
		}
		fs[0]=1;//初始化 
		for(int i=1;i<=n;i++){
			int d=1;//和i一个颜色的有几个
			for(int j=i-1;j>=0;j--){
				if(j!=i-1&&c[j+1]==c[i]){//因为每一个f[i]和g[i]都是求j+1~i之间至少有k个颜色c[i]，所以就有了这里的抽象代码 
					d++;//如果和c[i]相等就++ 
				}
				if(d<k){
					continue ;
				}//不行就换一个 
				if(f[j]+k>f[i]){
					f[i]=(f[j]+k)%1000000007;
					fs[i]=(fs[j]*zh[d-1][k-1])%1000000007;
				}//比f[i]大，可以更新的情况，就更新一下 
				else if(f[j]+k==f[i]){
					fs[i]=(fs[i]+fs[j]*zh[d-1][k-1])%1000000007;
				}//如果正好是f[i]，那就加上就行了 
			}
		}
		long long maxx=0,ans=0;
		for(int i=0;i<=n;i++){
			if(f[i]>maxx){
				maxx=f[i];
				ans=fs[i];
			}
			else if(f[i]==maxx){
				ans=(ans+fs[i])%1000000007;
			}
		}//找出最大的，最后输出他的方案数 
		cout<<ans%1000000007<<'\n';
	}
	return 0;
}
```

---

## 作者：WaterSun (赞：4)

因为我是彩笔，所以我不会组合数，只会暴力。

# 思路

由 Easy Version 得到的状态转移方程：

$$
dp_{i,j} = \left\{\begin{matrix}
\sum_{p = 1}^{p < i}{dp_{p,j - 1}} & (j \bmod k = 1)\\
\sum_{p = 1}^{p < i \wedge c_p = c_i}{dp_{p,j - 1}} & (\operatorname{otherwise})
\end{matrix}\right.
$$

然后你发现对于上面的式子你可以用一个前缀和优化成 $\Theta(n^2)$ 的，对于第二个式子你考虑也运用类似与前缀和的方式解决。

定义 $f_{i,j}$ 表示，当前取出 $j$ 个颜色为 $i$ 的瓷砖的方案数，于是第二个式子就可以转化成 $f_{c_i,j - 1}$。然后对于每一个 $i$，都可以将 $f_{c_i,j}$ 更新为 $f_{c_i,j} + dp_{i,j}$。

**毒瘤警告：有毒瘤 Hack 使得答案的总和模 $10^9 + 7$ 等于 $0$，所以你还需要额外的标记数组判断这个位置是为是真的有值。**

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define Add(a,b) (((a) + (b)) % mod)

using namespace std;

const int N = 5010,mod = 1e9 + 7;
int n,k;
int arr[N],dp[N][N],s[N][N],f[N][N];
bool sdp[N][N],ss[N][N],sf[N][N];

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

inline void solve(){
    dp[0][0] = s[0][0] = 1;
    sdp[0][0] = ss[0][0] = true;
    n = read();
    k = read();
    for (re int i = 1;i <= n;i++) arr[i] = read();
    for (re int i = 1;i <= n;i++){
        for (re int j = 0;j <= n;j++){
            dp[i][j] = s[i][j] = f[i][j] = 0;
            sdp[i][j] = ss[i][j] = sf[i][j] = false;
        }
    }
    for (re int i = 1;i <= n;i++){
        for (re int j = i;~j;j--){
            if (j % k == 1){
                dp[i][j] = Add(dp[i][j],s[i - 1][j - 1]);
                sdp[i][j] |= ss[i - 1][j - 1];
            }
            else if (j){
                dp[i][j] = Add(dp[i][j],f[arr[i]][j - 1]);
                sdp[i][j] |= sf[arr[i]][j - 1];
            }
            s[i][j] = Add(s[i - 1][j],dp[i][j]);
            ss[i][j] |= ss[i - 1][j] | sdp[i][j];
            f[arr[i]][j] = Add(f[arr[i]][j],dp[i][j]);
            sf[arr[i]][j] |= sdp[i][j];
        }
    }
    for (re int j = n;~j;j--){
        if (j % k == 0){
            int ans = 0;
            bool falg = false;
            for (re int i = 1;i <= n;i++){
                ans = Add(ans,dp[i][j]);
                falg |= sdp[i][j];
            }
            if (falg){
                printf("%d\n",ans);
                return;
            }
        }
    }
    puts("1");
}

int main(){
    int T;
    T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：zhangchengqi666 (赞：4)

## 说在前面

第一道自己想出来的蓝题 DP，写篇题解纪念一下。

前置芝士：组合计数、子序列 DP。

## 题目分析

题目说了那么久，实际上就是求从一个序列中选出另一个序列，使它可以分成长度相等的几段，每一段的长度都是 $k$，且颜色相同。

问**最长的可以构成的序列**有多少种可能。

### DP 定义

题目问了最长的序列，那么可以定义 $g_i$ 表示最后一段的颜色都是 $c_i$ 的序列的最长长度；$f_i$ 表示长度为 $g_i$，最后一段的颜色都是 $c_i$ 的方案数。

### 转移

如果要从状态 $j$ 转移到状态 $i$ 的话，要满足以下几个条件：

1. $j \le i$。
2. 设 $tmp$ 为 $i$ 和 $j$ 之间 $c_i$ 的个数，则 $tmp \ge k$。

现在，分类讨论：

1. 当 $g_j + k > g_i$ 时，存在更优方案，更新 $g_i \gets g_j + k$，$f_i \gets f_j \times C _ {tmp - 1} ^ {k - 1}$。$tmp$ 和 $k$ 都减一的原因是：**第 $i$ 个已经确定。**

2. 当 $g_j + k = g_i$ 时，利用加法原理直接相加：$f_i \gets f_i + f_j \times C _ {tmp - 1} ^ {k - 1}$。

所以，提前预处理出 $C _ i ^ j$，在转移时直接使用即可。

### 答案

依次枚举找到最大的 $g_i$ 然后把所有 $f_i$ 加起来即为答案。

## 注意事项

1. 记得开 `long long`。
2. 别忘了取模。

## 完整代码：

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 5000 + 5, mod = 1000000007;

int a[N], c[N][N], f[N], g[N];

int t, n, k;

signed main() {
	cin >> t;
	for (int i = 0; i <= 5000; i++) {
		c[i][0] = 1ll;
	}
	for (int i = 1; i <= 5000; i++) {
		for (int j = 1; j <= 5000; j++) {
			c[i][j] = (c[i - 1][j - 1] % mod + c[i - 1][j] % mod) % mod;
		}
	}
	while (t--) {
		memset(g, 0, sizeof g);
		memset(f, 0, sizeof f);
		cin >> n >> k;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		f[0] = 1;
		for (int i = k; i <= n; i++) {
			int tmp = 0;
			for (int j = i; j >= 0; j--) {
				if (tmp >= k) {
					if (g[j] + k == g[i]) {
						f[i] = (f[i] % mod + f[j] % mod * (c[tmp - 1][k - 1] % mod) % mod) % mod;
					}
					if (g[j] + k > g[i]) {
						g[i] = g[j] + k;
						f[i] = f[j] % mod * (c[tmp - 1][k - 1] % mod) % mod;
					}
				}
				if (a[j] == a[i]) {
					tmp++;
				}
			}
		}
		int mx = -1, ans = 0;
		for (int i = 0; i <= n; i++) {
			if (g[i] == mx) {
				ans = (ans % mod + f[i] % mod) % mod;
			}
			if (g[i] > mx) {
				mx = g[i];
				ans = f[i] % mod;
			}
		}
		cout << ans % mod << endl;
	}
	return 0;
}
```

## 说在后面

写题解不易，望点赞。

---

## 作者：hjyowl (赞：3)

### 思路

特殊条件子序列计数，考虑动态规划。

定义 $f_i$ 为从 $1$ 到 $i$ 最长的好路径长度，$cnt_i$ 为 $1$ 到 $i$ 的最长好路径数量，两者都需要满足以 $i$ 结尾。

考虑枚举 $i$，倒着往前枚举 $j$，令 $t$ 为 $j$ 到 $i$ 中和 $a_i$ 一样的数的个数。

对于 $k \le t$ 时，更新 $f_i$，如果 $f_j+k \le f_i$，那么 $f_i$ 等于 $f_j+k$ 然后数量等于 $cnt_j \times C_{t-1}^{k-1}$。如果 $f_i$ 等于 $f_j+k$ 那就把 $cnt_i$ 加上 $cnt_j \times C_{t-1}^{k-1}$。

至于为什么是 $cnt_j \times C_{t-1}^{k-1}$，前面的 $cnt_j$ 是 $1$ 到 $j$ 的方案，$C_{t-1}^{k-1}$ 是 $j+1$ 到 $i$ 那 $t-1$ 个里面选择 $k-1$ 个（因为必须选择 $a_i$）。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N = 5010,mod = 1e9 + 7;
long long qmi(long long a,long long k){
	long long res = 1;
	while (k){
		if (k & 1){
			res = (res * a) % mod;
		}
		a = (a * a) % mod;
		k >>= 1;
	}
	return res;
} 
long long fact[N],infact[N];
long long n,k;
long long a[N];
long long f[N],cnt[N];
long long C(long long a,long long b){
	return ((fact[a] * infact[b]) % mod) * infact[a - b] % mod;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	long long T;
	cin >> T;
	fact[0] = 1;
	for (long long i = 1; i < N; i ++ ){
		fact[i] = fact[i - 1] * i % mod;
	}
	for (long long i = N - 1; i >= 0; i -- ){
		infact[i] = qmi(fact[i],mod - 2);
	}
	while (T -- ){
		cin >> n >> k;
		memset(f,0,sizeof f);
		memset(cnt,0,sizeof cnt);
		for (long long i = 1; i <= n; i ++ ){
			cin >> a[i];
		}
		cnt[0] = 1; 
		for (long long i = k; i <= n; i ++ ){
			long long s = 0;
			for (long long j = i; j >= 0; j -- ){
				if (s >= k){
					long long c = f[j] + k,t = (C(s - 1,k - 1)) % mod;
					if (c > f[i]){
						f[i] = c;
						cnt[i] = (cnt[j] * t) % mod;
					}
					else if (c == f[i]){
						cnt[i] = (cnt[i] + (cnt[j] * t) % mod) % mod;
					}
				}
				if (a[i] == a[j]){
					s ++ ;
				}
			}
		}
		long long mx = -1e9,res = 0;
		for (long long i = 0; i <= n; i ++ ){
			if (f[i] > mx){
				mx = max(mx,f[i]);
				res = 0;
				res = (res + cnt[i]) % mod;
			}
			else if (f[i] == mx){
				res = (res + cnt[i]) % mod;
			}
		}
		cout << res << endl;
	}
	return 0;
} 

```

---

## 作者：MYiFR (赞：3)

### 题目大意
~~太难翻了。~~

定义好的路径：

给定一个整数 $k$ 和一个序列 $C$，在其中选择一个子序列 $A$，如果：
1. $|A|\bmod k = 0$
2. 	- $ A_1=A_2=A_3=\cdots =A_k$
	- $ A_{k+1}=A_{k+2}=A_{k+3}=\cdots =A_{2k}$
	- $ \cdots$
	- $ A_{n-k+1}=A_{n-k+2}=A_{n-k+3}=\cdots =A_n$
    
那么称 $A$ 是一条好的路径。如果 $|A|=0$，那么 $A$ 同样是一条好的路径。

给定一个序列 $C$ 和一个整数 $k$，问你这个序列最长的好的路径有几条。

### 解题思路
很显然，这是一道 dp 题。

做 dp 题的思路很明确，第一步想状态，第二步想转移，第三步想优化。当然其实还有一个“第零步”，想这题它能不能 dp，与此同时也多出来一个“第一点五步”，想这个状态它能不能 dp。

但这题的状态还是很好想的。$dp_{i,j}$ 表示在枚举到 $C_i$，子序列长度为 $j$ 的方案数。

想完状态来想转移方程，方程也好想，根据题意，当 $j\bmod k=1$ 时，所选的 $C_i$ 不必和前一个选中的 $C_{i'}$ 相等，否则就要相等。

那么就可以开两个求和的数组，$sum_{i,j}$ 表示长度为 $i$，最后一个为 $j$ 的所有方案数之和，$cnt_i$ 表示最后一个为 $i$ 的所有方案数之和。同时注意到如果从小到大枚举子序列长度，那么对于 $C_i$，较短长度所更新的答案可能会被统计进较长长度的答案里，所以我们需要从大到小枚举长度，更新答案。

注意了，因为所有的答案在统计时会 $\bmod(10^9+7)$，所以我们不能简单地枚举 $cnt_i$，因为长度更长的路径的方案数可能 $\bmod(10^9+7)=0$，所以我们还要开几个标记数组来确认这个状态时到底有没有案。（详见 Test 29）

### AC 代码
```
#include<bits/stdc++.h>
#define ll long long
#define DEBUG
using namespace std;
const ll N=5e3+5,mod=1e9+7;
ll t,n,k,c[N],dp[N][N],cnt[N],sum[N][N];
bool book1[N],book2[N][N];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;++i) scanf("%d",&c[i]);
		for(int i=0;i<=n;++i){
			cnt[i]=0;
			book1[i]=0;
			for(int j=0;j<=n;++j){
				sum[i][j]=dp[i][j]=book2[i][j]=0;
			}
		}
		cnt[0]=sum[0][0]=dp[0][0]=book1[0]=book2[0][0]=1;
		for(int i=1;i<=n;++i){
			for(int j=i-1;j>=1;--j){
				if(j%k==0){
					if(book1[j]){
						dp[i][j+1]=cnt[j];
						book1[j+1]=book2[j+1][c[i]]=1;
					}
				}
				else if(book2[j][c[i]]){
					dp[i][j+1]=sum[j][c[i]];
					book1[j+1]=book2[j+1][c[i]]=1;
				}
				(sum[j+1][c[i]]+=dp[i][j+1])%=mod;
				(cnt[j+1]+=dp[i][j+1])%=mod;
			}
			dp[i][1]=1;
			(sum[1][c[i]]+=1)%=mod;
			(cnt[1]+=1)%=mod;
			book1[1]=1;
			book2[1][c[i]]=1;
			#ifdef DEBUG
			for(int j=1;j<=i;++j) printf("%d ",dp[i][j]);
			printf("\n");
			#endif
		}
		for(int i=(n/k)*k;i>=0;i-=k){
			if(book1[i]){
				printf("%lld\n",cnt[i]);
				break;
			}
		}
	}
	return 0;
}
```

代码不长也要养成自己写的习惯，不是吗？

---

## 作者：cqsunny (赞：2)

建议在[博客](https://blog.csdn.net/m0_64542522/article/details/147137462)查看。

由于题目中有从某个地方跳到右边，考虑进行 dp。

我原本想设 $f_{i, j}$ 表示以 $i$ 结尾的优美路径选了 $j$ 个方案数，显然这样会超时。

定义两个 dp 数组，$f_{i}$ 表示以 $i$ 结尾的优美路径最长的长度，$g_{i}$表示以 $i$ 结尾的优美路径最长的方案数。

正序枚举 $i$，倒序从 $i$ 枚举 $j$，统计 $a_j = a_i$ 的个数，如果 $cnt \ge k$，说明可以转移，$f_i = f_j \times C_{cnt - 1}^{k - 1}$，然后同时更新一下方案数。

注意优美路径长度为 $0$ 时方案数为 $1$，如果 WA#30 可能是你没开 long long。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
int T, n, k;
int iv[5010][5010];
int f[5010];
long long g[5010];
int a[5010]; 
int main(){
	//预处理组合数
	for(int i = 0; i <= 5000; ++ i){
		iv[i][0] = iv[i][i] = 1;
		for(int j = 1; j < i; ++ j){
			iv[i][j] = (iv[i - 1][j] + iv[i - 1][j - 1]) % mod;
		}
	}
	scanf("%d", &T);
	while(T --){
		memset(f, 0, sizeof(f));
		memset(g, 0, sizeof(g));
		scanf("%d %d", &n, &k);
		for(int i = 1; i <= n; ++ i){
			scanf("%d", &a[i]);
		} 
		g[0] = 1; 
		for(int i = 1; i <= n; ++ i){
			int s = 1;
			for(int j = i - 1; j >= 0; -- j){
				if(s >= k){
					if(f[j] + k > f[i]){
						f[i] = f[j] + k;
						g[i] = g[j] * iv[s - 1][k - 1] % mod; 
					}
					else if(f[j] + k == f[i]){
						g[i] += g[j] * iv[s - 1][k - 1] % mod;
						g[i] %= mod;
					}
				}
				if(a[i] == a[j]) ++ s;//注意由于转移是从f[j]转移的，因此不包括a[j]
			}
		}
		int ans = 0;
		long long ansp = 1;
		for(int i = 1; i <= n; ++ i){
			if(f[i] > ans) ans = f[i], ansp = g[i];
			else if(f[i] == ans) ansp += g[i], ansp %= mod;
		}
		printf("%lld\n", ansp);
	}
	return 0;
}
```

---

## 作者：SegTree (赞：2)

首先你要会 G1 的 $\mathcal{O}(n^3)$ 做法，[Link](https://www.luogu.com.cn/blog/modulo-998244353/solution-cf1811g1)。

状态很难降下去，考虑降低转移的复杂度。

不难想到维护一个 $mx_{s,j}$ 和 $sm_{s,j}$ 表示 $\max_{l<i} dp_{l,j}$ 和 $\sum_{l<i}[dp_{l,j}=mx_{s,j}]dp2_{l,j}$，然后 $j\ne 1$ 就能直接 $\mathcal{O}(1)$ 转移过来。

$j=1$ 只需要维护一个 $mxk$ 和一个 $smk$ 表示 $\max_{l<i}dp_{l,k}$ 和 $\sum_{l<i}[dp_{l,k}=mxk]dp2_{l,k}$ 即可 $\mathcal{O}(1)$ 转移。

算完 $dp$ 值之后更新一下这两个东西即可，时间复杂度就降低到了 $\mathcal{O}(n^2)$。

[Record](https://codeforces.com/contest/1811/submission/228398571)。

---

## 作者：_sunkuangzheng_ (赞：1)

**【题目分析】**

最优方案计数题，我们得先知道最优方案的大小。设 $f_i$ 表示只考虑前 $i$ 个颜色**且强制以 $i$ 结尾**的最长长度，显然有转移方程：$f_i = \max\limits_{j=1}^i\{f_j + k\}$，其中 $j$ 需要满足的条件是 $j+1 \sim i$ 之间至少有 $k$ 个颜色 $c_i$。

考虑如何统计方案数量。设 $g_i$ 表示只考虑前 $i$ 个颜色且强制以 $i$ 结尾的最长长度数量，枚举 $j$。设当前 $j+1 \sim i$ 之间有 $p$ 个 $c_i$ 颜色。

- 如果当前的 $j$ 能够更新 $f_i$，即 $f_j + k > f_i$，那么我们需要从 $1 \sim j$ 中找出长度为 $f_j$ 的序列，这一步有 $g_j$ 种方法；还需要从 $j+1 \sim n$ 种找出 $k$ 个颜色为 $c_i$ 的数字，**注意 $i$ 位置是钦定要选的**，所以我们的方案数是 $\dbinom{p-1}{k-1}$，所以 $g_i = \dbinom{p-1}{k-1}g_j $。

- 如果当前的 $j$ 得到的答案恰好是 $f_i$，那么我们需要让 $f_i$ 加上 $j$ 的贡献。类似的，这里 $g_i \gets g_i + \dbinom{p-1}{k-1}g_j$。

我们先预处理组合数，然后枚举 $i,j$ 进行转移。两部分的时间复杂度都是 $\mathcal O(n^2)$，可以通过本题。

**【代码】**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 5e3+5,mod = 1e9+7;
int t,n,f[maxn],g[maxn],c[maxn],k,h[maxn][maxn];
signed main(){
    cin >> t,h[0][0] = 1;
    for(int i = 1,j;i <= 5000;i ++)
        for(j = h[i][0] = 1;j <= i;j ++) h[i][j] = (h[i-1][j] + h[i-1][j-1]) % mod;
    while(t --){
        cin >> n >> k,g[0] = 1;
        for(int i = 1;i <= n;i ++){
            cin >> c[i],f[i] = 0,g[i] = 0;
            if(k == 1) f[i] = 1;
            for(int j = i-1,tp = 1;j >= 0;tp += (c[j --] == c[i])){
                if(tp < k) continue;int d = j;
                if(f[d] + k > f[i]) f[i] = f[d] + k,g[i] = g[d] * h[tp-1][k-1] % mod;
                else if(f[d] + k == f[i]) g[i] = (g[i] + g[d] * h[tp-1][k-1]) % mod;
            }
        }int mx = 0,ans = 0; 
        for(int i = 0;i <= n;i ++) if(f[i] > mx) mx = f[i],ans = g[i]; else if(f[i] == mx) ans = (ans + g[i]) % mod;
        cout << ans << "\n"; 
    }
}
```

---

## 作者：N1K_J (赞：0)

不妨设 $dp_i$ 是前 $i$ 个最长能多长，$sum_i$ 是方案数。

我们考虑从 $dp_{j < i}$ 转移到 $dp_i$。

注意到能转移相当于 $c_{j+1},c_{j+2},\cdots,c_i$ 中有 $D \ge k$ 个和 $c_i$ 相同的数，此时 $dp_i$ 可以为 $dp_j+k$。

如果 $dp_i < dp_j$，令 $dp_i \leftarrow dp_j$，$sum_i \leftarrow sum_j \cdot C_{D-1}^{k-1}$，即在除了 $c_i$ 之外的 $D-1$ 个与其相等的中选 $k-1$ 个来构成这 $k$ 个相同的。

如果 $dp_i = dp_j$，令 $dp_i \leftarrow dp_i+dp_j$，$sum_i \leftarrow sum_i+sum_j \cdot C_{D-1}^{k-1}$，理由同上。

若均不满足，不用更新。

整体复杂度 $O(n^2)$。

[Code](https://codeforces.com/contest/1811/submission/280053902)

---

## 作者：happybob (赞：0)

有一种比较暴力，不需要组合数的 DP。

先考虑在 G1 的限制（即 $n\leq 100$）下怎么做。

有一个比较显然的 DP，$f_{i,j,k}$ 表示前 $i$ 个，长度为 $j$，最后一个的颜色为 $k$。转移时可以朴素地 $O(1)$ 转移，注意 $j \equiv 1(\bmod m)$ 时可以从 $f_{i-1}$ 的任意一个 $k$ 转过来，于是需要在 DP 的同时维护一下和以防复杂度退化。

回到 G2，考虑上文的状态就已经是三次方，首先要优化这个东西。这一步是容易的，因为 $f_i$ 仅有 $f_{i-1}$ 而来，滚动数组即可。

接着是转移过程。注意到上文中既有 $k=a_i$ 时才真正进行了 DP 值的修改，于是不枚举 $k$，只枚举 $j$ 即可。

然而这么写有个问题是，如果最终某个 $f_{i,j,k}$ 的方案数是 $10^9+7$ 的倍数，取模变成 $0$，我们会认为不存在这种长度，于是会在第 $29$ 个点 WA。于是在 DP 时顺便记录一个 `bool` 数组表示这种情况是否有可能，转移和 DP 转移类似。

顺带一提：没注意到这个问题仍然能过 G1，可能是数据比较弱。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 5005;
const long long MOD = 1e9 + 7;

int t, n, m, a[N];
long long f[N][N];
long long sum[N];
bool cb[N][N];
bool cc[N];

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> t;
	while (t--)
	{
		cin >> n >> m;
		for (int i = 1; i <= n; i++) cin >> a[i];
		for (int i = 0; i <= n; i++)
		{
			for (int j = 0; j <= n; j++) 
			{
				f[i][j] = 0ll, cb[i][j] = 0, sum[i] = 0ll, cc[i] = 0;
			}
		}
		f[0][0] = 1ll;
		sum[0] = 1ll;
		cb[0][0] = 1;
		cc[0] = 1;
		for (int i = 1; i <= n; i++)
		{
			for (int j = n; j >= 1; j--)
			{
				sum[j] = (sum[j] - f[j][a[i]] + MOD) % MOD;
				f[j][a[i]] = (f[j][a[i]] + f[j - 1][a[i]]) % MOD;
				cb[j][a[i]] |= cb[j - 1][a[i]];
				if (j % m == 1)
				{
					f[j][a[i]] = (f[j][a[i]] + sum[j - 1]) % MOD;
					cb[j][a[i]] |= cc[j - 1];
					f[j][a[i]] = (f[j][a[i]] - f[j - 1][a[i]] + MOD) % MOD;
				}
				sum[j] = (sum[j] + f[j][a[i]]) % MOD;
				cc[j] |= cb[j][a[i]];
			}
		}
		long long ans = 0ll;
		for (int j = 0; j <= n; j += m) 
		{
			long long sum = 0ll;
			bool flg = 0;
			for (int k = 0; k <= n; k++) 
			{
				sum = (sum + f[j][k]) % MOD;
				flg |= cb[j][k];
				//cout << "!!!: " << j <<" " << k << " " << f[n][j][k] << "\n"; 
			}
			if (flg)
			{
				ans = sum;
			}
		}
		cout << ans << "\n";
	}
	return 0;
}
```


---

## 作者：ncwzdlsd (赞：0)

序列问题，考虑 DP。

设计状态 $f(i,j)$ 表示当前选了 $i$ 个点，最后一个点颜色为 $j$ 的方案数。

当 $a_i\bmod k=1$ 时，该点的颜色可以任意选择，否则必须跟上一个点颜色相同。对于每个点，我们考虑它的不同颜色转移即可。

注意到对于 $a_i\bmod k=1$ 的点，它的转移会退化成 $O(n^3)$ 的。我们用 $g_i$ 记录第 $i$ 个完整的段的方案数即可优化转移。

注意转移时要从大到小枚举子序列长度，否则可能会出现小长度的答案重复更新大长度答案的情况。

维护两个标记：

- $c1_i$ 表示编号为 $i$ 的一个长度为 $k$ 的子序列是否统计完毕。

- $c2$ 维护当前子序列的颜色。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int mod=1e9+7,maxn=5005;
int c[maxn],g[maxn],f[maxn][maxn];
bool c2[maxn][maxn],c1[maxn];

void solve()
{
    int n,k;cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>c[i],g[i]=0,c1[i]=0;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) f[i][j]=0,c2[i][j]=0;
    f[0][0]=1,g[0]=1,c2[0][0]=1,c1[0]=1;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j;j--)
        {
            if(j%k==1)
            {
                if(c1[j/k]) c2[j][c[i]]=1,f[j][c[i]]+=g[j/k],f[j][c[i]]%=mod;
            }
            else if(c2[j-1][c[i]]) c2[j][c[i]]=1,f[j][c[i]]+=f[j-1][c[i]],f[j][c[i]]%=mod;
            if(!(j%k)&&c2[j][c[i]]) c1[j/k]=1,g[j/k]+=f[j-1][c[i]],g[j/k]%=mod;
        }
    for(int i=n/k;i>=0;i--) if(c1[i]) {cout<<g[i]<<'\n';break;}
}

signed main()
{
    int t;cin>>t;
    while(t--) solve();
	return 0;
}
```

---

## 作者：__vector__ (赞：0)

纪念一下第一次不看题解，不看算法标签做出 CF 评分 2200。   
虽然实际上最多提高组 T1。  
## G1 做法  
G2 做法只需要在 G1 基础上稍微修改。  

很自然想到设 $dp_{i,j}$ 表示第 $i$ 位是路径的第 $j$ 个点的方案数。  

想一下如何转移，对于 $i = 1$，显然方案数是 $1$。  
对于 $i \ge  2$，分一下类：  
1. 若 $i \equiv 1 \pmod k$，那么对于所有 $j \le i-1$，从 $dp_{j,i-1}$ 转移，颜色不用管。   
2. 否则，还要在情况 1 的基础上加上一条限制：第 $i$ 个点与 $j$ 点颜色相同。  

主要思想就是这个。  

关于怎么统计之前符合某些条件的状态答案综合，这个开个数组记一下就行了，都把 dp 设计出来了，这么简单的想必都会。  

剩下的就是从大到小枚举 $m$，每次跑一遍 dp，找到答案就终止。  

dp 复杂度 $O(n^2)$。  

枚举最劣复杂度 $O(n)$。 

总复杂度 $O(n^3)$。  

## G2 做法  
dp 不大可能优化了，看枚举过程很方便优化。  

主要就是优化寻找最长路径长度的过程。  

我们可以先做一遍 dp，看路径长度最高到多少，使得答案不为 $0$。  

然后对这个路径长度 dp 一下就行了。  

UPD：做法麻烦了，实际上直接 dp 一遍就行了。  

## Code  
```cpp
// LUOGU_RID: 107120197
#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define REP(i, a, b) for (int i = a; i >= b; i--)
#define pb push_back()
#define mkpr make_pair
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int maxn = 5005;
typedef long long ll;
const ll mod = 1e9 + 7;
int t;
int n, k;
int c[maxn];
ll dp[maxn][maxn];  // 第 i 位状态为 j
ll sum[maxn][maxn]; // 颜色为 i，状态为 j，dp 值和
ll sum2[maxn];      // 状态为 i dp 总和
bool dp2[maxn][maxn],sum21[maxn][maxn],sum22[maxn];
inline int turn(int status)
{
    if (status % k == 0)
        return k;
    return status % k;
}
int main()
{
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &n, &k);
        FOR(i, 1, n)
        {
            scanf("%d", &c[i]);
        }
        ll ans = 0;
        FOR(i, 1, n)
        {
            dp2[i][1]=1;
            FOR(j, 2, n)
            {
                if (turn(j) == 1)
                {
                    dp2[i][j]|=sum22[j-1];
                }
                else
                {
                    dp2[i][j]|=sum21[c[i]][j-1];
                }
            }
            FOR(j, 1, n)
            {
                sum22[j] |= dp2[i][j];
                sum21[c[i]][j] |= dp2[i][j];
            }
        }
        int blocks = n / k;
        bool isansoutputed=0;
        for (int m = blocks * k; m > 0; m -= k)
        {
            bool flag = 0;
            FOR(i, 1, n)
            {
                if (dp2[i][m])
                {
                    flag = 1;
                    break;
                }
            }
            if (flag)
            {
             //   printf("m = %d\n", m);
                FOR(i, 1, n)
                {
                    dp[i][1] = 1;
                    FOR(j, 2, m)
                    {
                        if (turn(j) == 1)
                        {
                            dp[i][j] += sum2[j - 1];
                        }
                        else
                        {
                            dp[i][j] += sum[c[i]][j - 1];
                        }
                        dp[i][j] %= mod;
                    }
                    FOR(j, 1, m)
                    {
                        sum2[j] += dp[i][j];
                        sum2[j]%=mod;
                        sum[c[i]][j] += dp[i][j];
                        sum[c[i]][j] %= mod;
                    }
                }
                FOR(i, 1, n)
                {
                    ans += dp[i][m];
                    ans%=mod;
                    FOR(j, 1, n)
                    {
                        //    printf("dp[%d][%d] = %d\n",i,j,dp[i][j]);
                        dp[i][j] = 0;
                        sum[i][j] = 0;
                    }
                    sum2[i] = 0;
                }
                isansoutputed=1;
                break;
            }
        }
        if (!isansoutputed)
            ans++;
        printf("%lld\n", ans % mod);
        FOR(i, 1, n)
        {
            sum2[i] = sum22[i]=0;
            FOR(j, 1, n)
            {
                dp[i][j] = dp2[i][j]=0;
                sum[i][j] = sum21[i][j]=0;
            }
        }
    }
    return 0;
}
```


---

