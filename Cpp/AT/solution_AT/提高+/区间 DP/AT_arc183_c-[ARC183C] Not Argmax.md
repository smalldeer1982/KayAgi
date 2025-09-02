# [ARC183C] Not Argmax

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc183/tasks/arc183_c

$ (1,2,\cdots,N) $ の順列 $ P=(P_1,P_2,\cdots,P_N) $ であって，次の $ M $ 個の条件をすべて満たすものの個数を $ 998244353 $ で割ったあまりを求めてください．

- $ i $ 番目の条件: $ P_{L_i},P_{L_i+1},\cdots,P_{R_i} $ の中の最大値は $ P_{X_i} $ **ではない**． ここで，$ L_i,R_i,X_i $ は入力で与えられる整数である．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 500 $
- $ 1\ \leq\ M\ \leq\ 10^5 $
- $ 1\ \leq\ L_i\ \leq\ X_i\ \leq\ R_i\ \leq\ N $
- 入力される値はすべて整数

### Sample Explanation 1

条件を満たすのは $ P=(1,2,3) $ の $ 1 $ 通りのみです．

## 样例 #1

### 输入

```
3 2
1 3 2
1 2 1```

### 输出

```
1```

## 样例 #2

### 输入

```
5 1
1 1 1```

### 输出

```
0```

## 样例 #3

### 输入

```
10 5
3 8 4
3 10 4
1 7 2
1 8 3
3 8 7```

### 输出

```
1598400```

## 样例 #4

### 输入

```
15 17
2 11 9
2 15 13
1 14 2
5 11 5
3 15 11
1 6 2
4 15 12
3 11 6
9 13 10
2 14 6
10 15 11
1 8 6
6 14 8
2 10 2
6 12 6
3 14 12
2 6 2```

### 输出

```
921467228```

# 题解

## 作者：Starrykiller (赞：9)

数据范围启示我们区间 DP。

考虑一个区间内最有代表性的是什么。不难发现就是它的最大元素；于是我们考虑在转移时枚举这个最大元素的位置。

假设我们考虑到了区间 $[l,r]$，枚举到最大元素位置为 $k\in [l,r]$，显然若 $\exists [L,R]\subseteq [l,r]$，使得 $[L,R]$ 内位置 $k$ 不能作为最大值，那么 $[l,r]$ 的最大值就不能在位置 $k$。否则我们就可以递归到子问题。

下面我们说明正确性。注意到我们只考虑了 $[L,R]\subseteq [l,r]$，否则的话一定会跨过一个比 $[l,r]$ 内最大值更大的值，例如 $p_{l-1}$ 或 $p_{r+1}$。那么这样的 $[L,R]$ 一定合法，不需要考虑。

那么我们就可以设计状态了：设 $f(l,r)$ 为在 $[l,r]$ 内填入 $(r-l+1)$ 个互不相同的整数，使得合法的方案数——注意我们并不关心到底是哪些整数。转移显然就是

$$f(l,r)=\sum_{l\le k\le r}[k\text { is valid}]{r-l\choose k-l} f(l,k-1)\cdot f(k+1,r)$$

至于条件的判断，随便预处理即可做到 $\Theta(1)$ 查询。最终总时间复杂度 $\Theta(N^3)$。

[代码](https://atcoder.jp/contests/arc183/submissions/57141119)。

小圆真的好可爱 www，喜欢小圆！

---

## 作者：EmptyAlien (赞：6)

~~我连蓝都场切不了了，可以退役了。~~

首先，看到这个题很像 DP。

为什么呢？因为他要统计数量，而这个数量还要取模，样例也告诉我们，这个答案不是可枚举的，而这个限制数又非常多，没法容斥，所以考虑 DP。

那是什么 DP 呢？看数据范围，首先先想想正常从左向右扫的DP，发现这个维护时间复杂度会爆炸，进行优化又没有 $O(n) \to O(1)$ 的比如单调队列，斜率优化之类的优化方法，这个数据范围看起来就不像带 $\log$ 的所以抛弃这个想法。

注意到这个 $1 \le n \le 500$，他提示我们复杂度有个 $O(n^3)$。

跟区间有关，又是 $O(n^3)$ 那不是区间 DP 吗？

接下来思路就渐渐明确了：设 $f_{l,r}$ 是只考虑 $[l,r]$ 的答案。

我们的转移枚举最大值 $k\in [l,r]$，这样我们就只要检查这个值能不能做最大值就行啦！

下文称满足条件的 $k$ 的集合为 $S$。

$$
f_{l,r}=\sum_{k\in S} C_{r-l}^{k-l} \times f_{l, k-1} \times f_{k+1, r}
$$

再来解释一下这个转移方程。

分类讨论，枚举最大值 $P_k$，这样根据加法原理把它加起来就行了。

对于每一项，左右区间互不影响，而我们还要把这个区间中的其他数（不包括最大值）分配到两边，所以应该是左边的方案数乘右边的方案数再乘上分配的方案数，即 $C_{r-l}^{k-l}$。

恭喜你，你成功学会了这道题！

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=505;
const int M=998244353;
int n,m,f[N][N],C[N][N];
vector<pair<int,int>>v[N];
int main(){
    cin>>n>>m;
    C[0][0]=1;
    for(int i=1;i<=n;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++)
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%M;
    }
    for(int i=1,l,r,x;i<=m;i++)
        cin>>l>>r>>x,v[l].push_back({r,x});
    for(int i=0;i<=n;i++)f[i+1][i]=1;
    for(int r=1;r<=n;r++){
        vector<int>st(r+1,1);
        for(auto[x,y]:v[r])if(x<=r)st[y]=0;
        f[r][r]=st[r];
        for(int l=r-1;l>=1;l--){
            for(auto[x,y]:v[l])if(x<=r)st[y]=0;
            for(int k=l;k<=r;k++)
                (f[l][r]+=(__int128)f[l][k-1]*f[k+1][r]*C[r-l][k-l]*st[k]%M)%=M;
        }
    }
    cout<<f[1][n]<<endl;
    return 0;
}
```

---

## 作者：bryce (赞：3)

## [[ARC183C] Not Argmax](https://www.luogu.com.cn/problem/AT_arc183_c)
### 思路
注意到 $N$ 很小，考虑区间 dp。

设 $dp_{l, r}$ 表示在 $[l,r]$ 中放入 $r - l + 1$ 个不同的数的方案数，那么考虑枚举最大值所在的位置进行转移，设 $k$ 是最大值的位置，若 $k$ 合法，那么有如下的递推式：

$$dp_{l, r} = \sum\limits_{k = l} ^ {r}\binom{r - l}{k - l}\times dp_{l, k - 1}\times dp_{k + 1, r}$$

下面来解释一下这个递推式，等号左边是枚举 $k$，中间的组合数表示除了最大值确定以外将剩下 $r - l$ 个数分 $k - l$ 个到左边的方案数，由于左边的数确定了，右边的数也就确定了，那么对于每种分法左边有 $dp_{l, k - 1}$ 种排列方式，也就是将 $k - l$ 个数放入 $[l, k - 1]$ 中的方案数，右边同理也要乘起来。

递推式解决了，还要知道那些 $k$ 合法才能通过它转移，若此是**被转移**的区间是 $[l, r]$，有一个区间 $[L, R]$ 里的 $k$ 不能是这个区间的最大值，那么如果 $[L, R]\subseteq [l, r]$ 那么肯定最大值不能为 $k$，无法转移，如果不是包含的关系而是有交集呢？$k$ 还是能够转移给 $[l, r]$，因为在 $[l, r]$ 区间内 $k$ 可以为最大值，接下来它会不断转移给其他区间，$k$ 能够成为某些区间的最大值，但如果有区间出现了上面的情况就不会再通过 $k$ 转移了，于是这样转移肯定是不重不漏的。

如何处理一个位置 $k$ 能否转移给 $[l, r]$ 呢？当输入 $L, R, x$ 时，那么 $x$ 在 $\forall[l, r](l\in [1, L], r\in [R, n])$ 中都不能转移，于是直接左右拓展标记不合法的区间即可。
### 代码
```cpp
#include<iostream>
#include<bitset>
#define int long long

using namespace std;

inline int read(){register int x = 0, f = 1;register char c = getchar();while (c < '0' || c > '9'){if (c == '-') f = -1;c = getchar();}while (c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}return x * f;}

const int N = 510, M = 1e5 + 10, mod = 998244353;
int n, m;
bitset<N> g[N][N];
int dp[N][N];
int mul[N], inv[N];
int qpow(int a, int b){
    int ans = 1;
    while (b){
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}
void init(){
    for (int len = 2; len <= n; len++)
        for (int l = 1; l + len - 1 <= n; l++){
            int r = l + len - 1;
            g[l][r] |= g[l + 1][r] | g[l][r - 1];
        }
    mul[0] = inv[0] = 1;
    for (int i = 1; i <= n; i++) mul[i] = mul[i - 1] * i % mod, inv[i] = qpow(mul[i], mod - 2);
}
int C(int n, int m){
    return mul[n] * inv[n - m] % mod * inv[m] % mod;
}

signed main(){
    n = read(), m = read();
    for (int i = 1; i <= m; i++){
        int l = read(), r = read(), x = read();
        if (l == r){
            cout << '0';
            return 0;
        }
        g[l][r][x] = 1;
    }
    init();
    for (int i = 0; i <= n; i++) dp[i][i] = dp[i + 1][i] = 1;
    for (int len = 2; len <= n; len++){
        for (int l = 1; l + len - 1 <= n; l++){
            int r = l + len - 1;
            for (int k = l; k <= r; k++){
                if (g[l][r][k]) continue;
                dp[l][r] = (dp[l][r] + dp[l][k - 1] * dp[k + 1][r] % mod * C(r - l, k - l) % mod) % mod;
            }
        }
    }
    cout << dp[1][n];
    return 0;
}
```

---

## 作者：SJZ2010 (赞：3)

场上做不出来呜呜呜……真是越学越菜了……

---

我们发现如果确定了一个区间的最大值，且保证这个最大值合法的话，最大值的两边的区间，就可以是满足其内部条件的任意答案。

可以发现这样就把大问题分割成了小问题，即这是一种区间 dp 的方法。

我们可以通过种种条件来确定：我们可以在这个区间的哪些位置上放最大值。按照以下方法：假如我们在处理区间 $[l, r]$，那么对于满足 $[L_i, R_i] \subseteq  [l, r]$ 的条件的 $X_i$ 显然是不能成为最大值的，把这些位置排除掉就行。

考虑如何合并。我们就先命令我们求 $dp_{l, r}$ 时，$P_l, P_{l + 1}, \dots, P_r$ 填的数都在 $1$ 和 $r - l + 1$ 之间，可以认为我们只保留了数字的相对大小关系，因此合并的时候我们还要决定把哪些数放到哪边。于是转移方程如下：

$$dp_{l, r} = \sum_{l \le k \le r, ok_k=1} dp_{l, k - 1} \times dp_{k + 1, r} \times \binom{r - l}{r - k}$$

其中的 $\binom{r - l}{r - k}$ 即是考虑把具体的数字放到右边去。

[AC.](https://atcoder.jp/contests/arc183/submissions/57142256)

唉，dp 训少了。

---

## 作者：Gordon_Song (赞：1)

设 $dp_{i,j}$ 表示有多少种满足限制的 $i$ 到 $j$ 的大小顺序。转移时枚举 $i$ 到 $j$ 中的最大位置 $k$，统计贡献，除去不满足限制的最大值位置。不满足限制的位置可以通过另一个简单的 dp 求得。具体的 dp 柿子如下：

$dp_{i,j}=\sum dp_{i,k-1} \times dp_{k+1,j} \times \binom{j-i}{k-i}$（$i \leq k \leq j$ 且 $\forall 1\leq P \leq m$，$[l_P,r_P] \not\subset [i,j]$ 或 $x_P \not = k$）

接下来思考这个 dp 如何想到，以及为什么是对的。

题目给的限制条件很古怪，经过尝试可以发现不进行区间 dp 很难维护古怪的限制，因为限制涉及的区间。又由于与区间最大值位置有关的要么是区间的大小顺序，要么是每个位置实际敲定的值。后者很显然在这题中不可行。而枚举满足限制的区间最大值，将原区间分成两边考虑，则可以保证所有包含于其中的限制都会被满足，且很容易算出结果。

具体实现：


```cpp
ll ca(int x,int y){
	if(x<0||y<0||x<y){
		return 0;
	}
	return zh[x][y];
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&l[i],&r[i],&c[i]);
		if(l[i]==r[i]){
			printf("0");return 0;
		}
		can[l[i]][r[i]][c[i]]=true;
		//cnt[l[i]][r[i]].push_back(c[i]);
	}
	zh[0][0]=1;
	for(int i=1;i<=n;i++){
		zh[i][0]=zh[i-1][0];
		for(int j=1;j<=n;j++){
			zh[i][j]=(zh[i-1][j-1]+zh[i-1][j])%mod;
			//printf("%d %d=%d\n",i,j,zh[i][j]);
		}
	}
	for(int i=1;i<=n+1;i++){
		for(int j=0;j<i;j++){
			sum[i][j]=1; 
		}
	}
	for(int i=1;i<=n;i++){
		sum[i][i]=1;
	}
	for(int len=2;len<=n;len++){
		for(int i=1;i<=n-len+1;i++){
			int j=i+len-1;
			for(int k=i;k<=j;k++){
				can[i][j][k]|=can[i+1][j][k]|can[i][j-1][k];
			}
		}
	}
	for(int len=2;len<=n;len++){
		for(int i=1;i<=n-len+1;i++){
			int j=i+len-1;
			for(int k=i;k<=j;k++){
				//printf("%d %d %d %d\n",i,j,k,ca(j-i+1-1,(k-1)-i+1));
				if(!can[i][j][k]){
					t[k]=sum[i][k-1]*sum[k+1][j]%mod*ca(j-i+1-1,(k-1)-i+1)%mod;
					//printf(":%d %d %d\n",i,j,k);
				}else{
					t[k]=0;
				}
			}
			//for(int k=0;k<cnt[i][j].size();k++)t[cnt[i][j][k]]=0;
			for(int k=i;k<=j;k++)(sum[i][j]+=t[k])%=mod;
			//printf("%d %d %d\n",i,j,sum[i][j]);
		}
	}
	printf("%lld",sum[1][n]);
}
```

---

## 作者：SFlyer (赞：1)

设 $dp_{l,r}$ 为填 $l\sim r$ 的方案数。填的时候枚举这一段最大值在哪儿。设在 $p$，则 $dp_{l,r}\leftarrow dp_{l,r}+dp_{l,p-1}\times dp_{p+1,r}\times \binom{r-l}{p-l}$。

考虑最大值能在哪儿。容易发现对于所有限制 $(L,R,X)$，如果 $l\le L,R\le r$，那么最大值不能在 $X$。这个用另外一个 $f_{l,r}$ 记录每一位可不可以，按照长度，$f_{L,R,x}=1$，$f_{l,r}=f_{l,r}|f_{l+1,r}|f_{l,r-1}$。时间复杂度 $\mathcal{O}(n^3)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 5e2+2;
const int M = 1e5+5; 
const ll mod = 998244353;

int n,m,l[M],r[M],x[M];
bitset<N> f[N][N];
ll dp[N][N],C[N][N];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>n>>m;
	for (int i=0; i<N; i++){
		C[i][0]=1;
		for (int j=1; j<=i; j++){
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
		}
	}
	for (int i=1; i<=m; i++){
		cin>>l[i]>>r[i]>>x[i];
		if (l[i]==r[i]){
			cout<<"0\n";
			return 0;
		}
		f[l[i]][r[i]][x[i]]=1;
	}	
	for (int i=2; i<=n; i++){
		for (int j=1; j+i-1<=n; j++){
			int k=j+i-1;
			f[j][k]|=f[j+1][k];
			f[j][k]|=f[j][k-1];
		}
	}
	dp[1][0]=1;
	for (int i=1; i<=n; i++){
		dp[i][i]=1;
		dp[i+1][i]=1;
	}
	for (int i=2; i<=n; i++){
		for (int j=1; j+i-1<=n; j++){
			int k=j+i-1;
			for (int p=j; p<=k; p++){
				if (!f[j][k][p]){
					dp[j][k]=(dp[j][k]+dp[j][p-1]*dp[p+1][k]%mod*C[i-1][p-j]%mod)%mod;
				}
			}
		}
	}
	cout<<dp[1][n]<<"\n";
	return 0;
}
```

---

## 作者：nb_jzy (赞：0)

# 题意
让你统计满足以下条件，长度为 $n$ 的排列的个数。

给了你 $m$ 个限制，$l_i,r_i,x_i$ 表示 $l_i\sim r_i$ 这段区间内的最大值**不能**是 $x_i$ 这个位置。
# 思路
根据数据范围 $n$ 只有 $500$，那么这就在暗示我们这和**区间 dp** 相关。

再结合十分典型的**统计排列**的区间 dp 的思路，我们一般设 $dp_{l,r}$ 表示区间 $l\sim r$ 这段区间放 $1\sim r-l+1$ 的方案数。而转移就是**枚举当前区间的最大值在哪个地方**：
$$dp_{l,r}=\sum_{k=l}^r dp_{l,k-1}\times dp_{k+1,r}\times C_{r-l}^{k-l}$$

以上转移第一遍看估计十分抽象，其具体含义可以理解为：既然已经**固定了最大值**，那么最大值在不同的两种方案一定互不重复，我们剩下就只需要考虑**最大值的左边/右边放哪些数**，而**这些数的选择方案**自然就是用一个**组合**来表示，但是我们选完之后还不知道**其摆放的顺序**，所以还要再**乘上左右两边的顺序**。（这里的 dp 值与其摆放的顺序数是等价的，因为我们可以将 $1\sim r-l+1$ 抽象成**其在当前区间的排名**，那么**选的这些数的相对顺序**就可以和排名的方案数等价）

那么既然我们有了这种典型的区间 dp，这道题给我们的限制无疑就可以转换为：假设当前 $l\sim r$ 这段区间中 $x_1,x_2...x_m$ 这些位置**不能作为最大值**，那我直接**不转移这些位置**不就行了吗？

所以转移就变成了：
$$dp_{l,r}=\sum_{k=l}^r [k\notin x_1,x_2...x_m]\times dp_{l,k-1}\times dp_{k+1,r}\times C_{r-l}^{k-l}$$

# 问题转换

于是我们的问题就转换为了：如何求得每一段区间的所有 $x$，也就是不能作为最大值的位置。

有的人会想，这不直接给了我们 $m$ 个限制，直接照搬不就行了吗？

但是这个想法显然是**错误的**，因为对于一段区间 $l\sim r$ 如果 $x$ 这个位置不是它的最大值，那么显然对于所有满足 $l'\le l,r \le r'$ 的区间 $l'\sim r'$，即**包含它的所有区间**，$x$ 这个位置仍然不能作为最大值。 

而我们如果直接暴力遍历 $1\sim l$，$r\sim n$，其复杂度为 $\mathcal O(n ^2\times m)$ 显然过不去。

而优化的方式有很多，赛时我用的以下方法：

我们记录一个数组 $minn_{x,i}$ 表示第 $x$ 个位置，以 $i$ 作为左端点时，**最近的一个右端点的位置**。

这样记录之后，对于每个 $x$，以及他的所有左端点 $i$，我们就知道了，从 $i$ 到 $minn_{x,i}\sim n$ 这一段区间都不能以 $x$ 作为最大值。

这样，我们预处理的时间复杂度就变成了 $\mathcal O(n\times m + n^3)$。

所以再加上区间 dp 的复杂度，总复杂度即为 $\mathcal O(n\times m + n^3)$

# 参考代码
代码常数较大，所以跑的很慢：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=505,mod=998244353;
int f[maxn][maxn],n,m,c[maxn][maxn],minn[maxn][maxn];
vector<int> g[maxn][maxn];
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			minn[i][j]=n+1;
		}
	}
	for(int i=1;i<=m;i++){
		int l,r,x;
		scanf("%lld%lld%lld",&l,&r,&x);
		for(int i=1;i<=l;i++){
			minn[x][i]=min(minn[x][i],r);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			for(int k=minn[i][j];k<=n;k++){
				g[j][k].push_back(i);
			}
		}
	}
	c[0][0]=1;
	for(int i=1;i<=n;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++){
			c[i][j]=c[i-1][j-1]+c[i-1][j];
			c[i][j]%=mod;
		}
	}
	for(int i=0;i<=n;i++){
		f[i+1][i]=1;
	}
	for(int i=n;i>=1;i--){
		for(int j=i;j<=n;j++){
			if(i==j){
				if(g[i][j].empty()){
					f[i][j]=1;
				}
				else{
					f[i][j]=0;
				}
			}
			else{
				int l=0;
				for(int k=i;k<=j;k++){
					bool fl=0;
					while(l<g[i][j].size()&&g[i][j][l]==k){
						l++;
						fl=1;
					}
					if(fl)continue;
					f[i][j]+=f[i][k-1]*f[k+1][j]%mod*c[j-i][k-i];
					f[i][j]%=mod;
				}
			}
		}
	}
	printf("%lld",f[1][n]);
	return 0;
}
```

---

## 作者：Fire_flame (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc183_c)

## $\mathtt{Solution}$

难度不算很难的 DP，赛时写假了没过。

考虑 $f_{i,j}$ 表示 $[i,j]$ 区间已经确定的答案数量。

转移的时候每一次都要在已有的区间内选出一个点 $i\le k\le j$，代表它是区间内部的最大值，如果它是区间最大值不满足条件的话就不能转移。

此时以 $k$ 为中心把 $[i,j]$ 拆成 $[i, k - 1]$ 和 $[k + 1, j]$ 两个区间，显然区间内的数会有 $C^{k-i}_{j-i}$ 种情况（不用考虑大小，因为每个数相对其他数的大小在转移的过程中已经确定了的）。

所以可以得到 $f_{i,j}=f_{i,k - 1} \times f_{k + 1, j}\times C^{k-i}_{j-i}$。

对于 $k$ 能否成为 $[i,j]$ 最大值的话，定义 $g_{i,l}$ 为给定 $l$ 比 $g_{i,l}$ 大的 $r$ 都不能以 $i$ 为最大值，这个是好计算的。

时间复杂度 $O(n^3+nm)$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(!isdigit(ch)){if(ch == '-')f = -1;ch = getchar();}
	while(isdigit(ch)){s = s * 10 + ch - '0';ch = getchar();}
	return s * f;
}
void write(int x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int MAXN = 5e2 + 5, MR = 1e5 + 5, MOD = 998244353;
int n, m, f[MAXN][MAXN], fac[MAXN], inv[MAXN], g[MAXN][MAXN];
int fpow(int a, int b){
	int res = 1;
	while(b){
		if(b & 1ll)res = res * a % MOD;
		a = a * a % MOD;
		b >>= 1ll;
	}
	return res;
}
int C(int a, int b){
	return fac[a] * inv[b] % MOD * inv[a - b] % MOD;
}
signed main(){
	n = read(), m = read();
	fac[0] = 1;
	for(int i = 1;i <= n;i ++)fac[i] = fac[i - 1] * i % MOD;
	inv[n] = fpow(fac[n], MOD - 2);
	for(int i = n - 1;i >= 0;i --)inv[i] = inv[i + 1] * (i + 1) % MOD;
	for(int i = 1;i <= n;i ++){
		for(int j = 1;j <= n;j ++)g[i][j] = n + 1;
	}
	for(int i = 1;i <= m;i ++){
		int l = read(), r = read(), x = read();
		for(int j = 1;j <= l;j ++)g[x][j] = min(g[x][j], r);
	}
	for(int i = 1;i <= n;i ++)f[i][i] = (g[i][i] != i);
	for(int i = 1;i <= n + 1;i ++)f[i][i - 1] = 1;
	for(int l = 2;l <= n;l ++){
		int i = 1;
		for(int j = l;j <= n;j ++, i ++){
			for(int k = i;k <= j;k ++){
				if(g[k][i] <= j)continue;
				f[i][j] = (f[i][j] + f[i][k - 1] * f[k + 1][j] % MOD * C(j - i, k - i) % MOD) % MOD;
			}
		}
	}
	printf("%lld\n", f[1][n]);
	return 0;
}

```

---

## 作者：ax_by_c (赞：0)

考虑一个判断过程，我们对于每个数找到以它为最大值的区间并一一判断即可。

于是考虑笛卡尔树分治的过程，每次枚举最大值位置并判断，然后向两边分治，唯一问题是需要保证两边的数互不相同。

这其实是简单的，我们先把两边都当作子问题来做，最后只需要选出一些数放左边，也就是乘上一个组合数。

那么不难想到一个 dp 的做法，设 $f_{i,j}$ 表示当前的分治区间为 $[i,j]$ 的答案。

那么每次枚举最大值位置 $p$，需要对于每个 $X=p$ 都没有 $i\le L,R\le j$。若合法则可以加上 $f_{i,p-1}f_{p+1,r}\binom{r-l}{p-l}$。

但是分析一下就会发现每个限制都会被判 $O(n^2)$ 次，所以时间复杂度是错误的。于是我们对所有 $i,p$ 预处理出最小的 $R$ 满足 $i\le L,X=p$，这是简单的。

时间复杂度 $O(n^3)$，可以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ax_by_c{
typedef long long ll;
typedef pair<int,int> pii;
const ll mod=998244353;
ll ksm(ll a,ll b,ll p){
    a=a%p;
    ll r=1;
    while(b){
        if(b&1){
            r=r*a%p;
        }
        a=a*a%p;
        b>>=1;
    }
    return r%p;
}
const int N=505;
int n,m;
ll fac[N],inv[N];
void Init(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=fac[i-1]*i%mod;
    }
    inv[n]=ksm(fac[n],mod-2,mod);
    for(int i=n;i>=1;i--){
        inv[i-1]=inv[i]*i%mod;
    }
}
ll C(int n,int m){
    if(n<0||m<0||n<m)return 0;
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
vector<pii>a[N];
int mn[N][N];
ll f[N][N];
void main(){
    scanf("%d %d",&n,&m);
    Init(n);
    for(int i=1,l,r,p;i<=m;i++){
        scanf("%d %d %d",&l,&r,&p);
        a[p].push_back({l,r});
    }
    for(int i=1;i<=n+1;i++){
        f[i][i-1]=1;
    }
    for(int p=1;p<=n;p++){
        for(int l=1;l<=p;l++){
            mn[p][l]=n+1;
        }
        for(auto x:a[p]){
            mn[p][x.first]=min(mn[p][x.first],x.second);
        }
        for(int l=p-1;l>=1;l--){
            mn[p][l]=min(mn[p][l],mn[p][l+1]);
        }
    }
    for(int len=1;len<=n;len++){
        for(int l=1,r=len;r<=n;l++,r++){
            for(int p=l;p<=r;p++){
                if(mn[p][l]>r){
                    f[l][r]=(f[l][r]+f[l][p-1]*f[p+1][r]%mod*C(r-l,p-l)%mod)%mod;
                }
            }
        }
    }
    printf("%lld\n",f[1][n]);
}
}
int main(){
    ax_by_c::main();
    return 0;
}
```

---

## 作者：Night_sea_64 (赞：0)

场上 A 先是脑子抽想了 20min，然后 B 不会，然后这题又想了很久才做出来。感觉自己水平太低了。。。

我自己赛时的思路就是如果我有一棵这个排列的**笛卡尔树**，就可以很容易判断出来是不是符合条件了。然后又知道显然要用 dp 做，于是想怎么 dp 来构建它。然后就知道是区间 dp 了。

不知道笛卡尔树也没关系，下面的内容还是能看。

$f_{l,r}$ 表示 $l\sim r$ 的区间，$l-1$ 和 $r+1$ 都不存在或比 $l\sim r$ 的最大值还大的方案数。这对应着笛卡尔树的一个子树。

然后肯定自然想要找这棵子树的根。所以枚举 $l\sim r$ 中的最大值位置 $maxp$ 然后判断这个位置能不能是 $l\sim r$ 中最大的。

那显然如果一个限制 $(L_i,R_i,maxp)$ 的区间 $[L_i,R_i]$ 被当前的 $[l,r]$ 包含，那么就是不行的。否则是一定可以的。

现在枚举到这里已经 $O(n^3)$ 了，只能使用 $O(1)$ 的办法来判断区间包含。很容易预处理出位置为 $i$，左端点 $\ge j$ 的限制，右端点的最小值。这样就能判断了。

转移很简单。$l\sim r$ 中有 $r-l+1$ 个不同的值。然后最大值去掉了，左右两边一共 $r-l$ 个值。现在要随便分给左边 $maxp-l$ 个值，右边 $r-maxp$ 个值，显然有 $C_{r-l}^{maxp-l}$ 种方案。然后这题就做完了。时间复杂度 $O(n^3)$，空间复杂度 $O(n^2+m)$。

```cpp
#include<iostream>
#include<cstring>
#define int long long
using namespace std;
const int mod=998244353;
int n,m,l[100010],r[100010],p[100010];
int c[510][510];
int minr[510][510];
int f[510][510];
signed main()
{
  cin>>n>>m;
  for(int i=0;i<=n;i++)
  {
    c[i][0]=1;
    for(int j=1;j<=i;j++)
      c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
  }
  memset(minr,999999,sizeof(minr));
  for(int i=1;i<=m;i++)
  {
    cin>>l[i]>>r[i]>>p[i];
    minr[p[i]][l[i]]=min(minr[p[i]][l[i]],r[i]);
  }
  for(int i=1;i<=n;i++)
    for(int j=i;j>=1;j--)
      minr[i][j]=min(minr[i][j+1],minr[i][j]);
  for(int i=1;i<=n+1;i++)f[i][i-1]=1;
  for(int len=1;len<=n;len++)
    for(int l=1;l+len-1<=n;l++)
    {
      int r=l+len-1;
      for(int maxp=l;maxp<=r;maxp++)
        if(minr[maxp][l]>r)
        {
          f[l][r]=(f[l][r]+f[l][maxp-1]*f[maxp+1][r]%mod*c[len-1][maxp-l]%mod)%mod;
        }
    }
  cout<<f[1][n]<<endl;
  return 0;
}
```

---

