# Yaroslav and Arrangements

## 题目描述

如果一个数列相邻两项之差的绝对值均为 $1$（我们认为首项和末项也相邻），并且首项是数列中最小的元素之一，那么我们称之为良好数列。如果一个数列单调不降且长度在 $[1,n]$ 之间，数列中每个数的值在 $[1,m]$ 之间，且重排后能得到至少 $1$ 个至多 $k$ 个良好数列，那么我们称之为优秀数列。给出 $n, m, k$，求优秀数列的个数。答案对 $10^9+7$ 取模。

Translated by @Kirito_Rivaille

## 说明/提示

$1 \le n,m,k \le 100$。

## 样例 #1

### 输入

```
1 1 1
```

### 输出

```
0
```

## 样例 #2

### 输入

```
3 3 3
```

### 输出

```
2
```

# 题解

## 作者：moonbowqwq (赞：6)

[题目链接](https://codeforces.com/problemset/problem/301/E)

## 题意简述

~~直接拷题面的。~~

如果一个数列相邻两项之差的绝对值均为 $1$（我们认为首项和末项也相邻），并且首项是数列中最小的元素之一，那么我们称之为良好数列。

如果一个数列单调不降且长度在 $1$ 到 $n$ 之间，数列中每个数的值在 $1$ 到 $m$ 之间，且重排后能得到至少 $1$ 个至多 $k$ 个良好数列，那么我们称之为优秀数列。

给出 $n, m, k$，求优秀数列的个数。答案对 $10^9 + 7$ 取模。

## 解题思路

先思考一下如何构造一个良好的序列，我们从最小的数字 $1$ 开始。由于首项和末项相邻，且首项是数列中最小的元素之一，所以我们让序列的开头和末尾都为 $1$，那么初始序列就为 $1, 1$。现在我们考虑加入数字 $2$，可以发现，如果要满足良好序列的要求，那么我们只能将序列变成这样 $1, 2, 1$，但是这样就没办法加入数字 $3$ 了。想想如何才能加入数字 $3$，可以发现，如果我在原序列的基础上再在 $2$ 旁边加入几个 $2$，那么我们就有地方加入数字 $3$ 了。多次尝试后可以发现，假设上次加入的数字为 $i$，如果我们想加入数字 $i + 1$，那么就必须存在至少一对相邻的数字 $i$，然后我们才能把 $i + 1$ 放在这两个 $i$ 的中间。更近一步的，假设我想加入 $x$ 个数字 $i + 1$，原来有 $y$ 对相邻的数字 $i$，那么加入数字 $i + 1$ 后就会产生 $x - y$ 对相邻的数字 $i + 1$。注意，由于我们不会再加入比 $i + 1$ 小的数字，所以我们必须要保证不存在任意一对小于 $i + 1$ 且相邻的数，以确保我们最终产生的序列一定是良好的，因而我们要满足 $x \geq y$ 且 $y > 0$，而当 $y$ 为 $0$ 时，良好序列就产生了。

接下来我们尝试把良好序列和优秀序列对应起来。可以发现，对应同一个优秀序列的良好序列，其所含有的各种数字的数量是相同的，比如说良好序列 $1, 2, 3, 2, 1, 2, 1$ 和 $1, 2, 1, 2, 3, 2, 1$ 对应的优秀序列都是 $1, 1, 1, 2, 2, 2, 3$，并且它们 $1, 2, 3$ 的数量都是相同的。那么既然所有数字的数量都相同，对应同一个优秀序列的良好序列，其不同的原因就只是插入方案不一样了。由前面可知，如果加入的各种数字的数量都相同，那么其在加入某种数字后所产生的相邻数字的对数也是相同的，这样我们就可以计算在数字相同的情况下，所能产生的良好序列个数了。假设我们加入的数字是 $d_1, d_2, \cdots, d_x$，对应的数量是 $q_1, q_2, \cdots, q_x$，设 $k_i$ 表示我在加入第 $i$ 个数字后所产生的相邻的数字的个数，由上文可知：$k_1 = d_1 - 1, \forall i \in [2, x], k_i = d_i - k_{i - 1}$，因为每个相邻的数字之间都要加入至少一个更大的数字，所以所能产生的良好序列个数就为：

$$\large \prod_{i = 2}^{x} \operatorname{C}_{d_i - 1}^{k_{i - 1} - 1}$$

由于题目要求，所以我们只需要统计出该值在 $[1, k]$ 的优秀序列个数即可。

那么具体该如何统计呢，我们可以用动规来实现。设 $f_{i, j, k, l}$ 表示当前考虑到第 $i$ 个数，总共加入了 $j$ 个数字（保证每个数字至少有一个），目前有 $k$ 对相邻的数字 $i$，能产生的良好序列个数为 $l$ 的优秀序列个数。假设我加入了 $x$ 个数字 $i + 1$，那么转移的话就是：

$$\large f_{i + 1, j + x, x - k, l \times \operatorname{C}_{x - 1}^{k - 1}} = \sum f_{i, j, k, l}$$

答案就为：

$$\large \sum_{i = 1}^{m} (m - i + 1) \times \sum_{j = 1}^{n} \sum_{l = 1}^{k} f_{i, j, 0, l}$$

然后这道题就做完了。

## 代码实现

```
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int R = 100, mod = 1e9 + 7;

int c[R + 5][R + 5];

int n, m, k, f[2][R + 5][R + 5][R + 5], ans;
//考虑到第 ln 个数字/总共有 num 个数/当前有 gap 个空隙/对应的优秀串有 have 个良好串

int qpow(int a, int b){
  int res = 1;
  while(b > 0){
    if(b & 1)
      res = (ll)res * a % mod;
    a = (ll)a * a % mod;
    b >>= 1;
  }
  return res;
}

int main(){
  c[0][0] = 1;
  for(int i = 1; i <= R; ++i)
    for(int j = 0; j <= i; ++j)
      c[i][j] = min(R + 1, (j > 0 ? c[i - 1][j - 1] : 0) + c[i - 1][j]);
  cin >> n >> m >> k;
  for(int i = 1; i <= n; ++i)
    f[1][i][i][1] = 1;
  for(int ln = 2; ln <= m; ++ln){//large number
    bool now = ln & 1, old = ln & 1 ^ 1;
    memset(f[now], 0, sizeof(f[now]));
    for(int num = ln - 1; num < n; ++num)
      for(int gap = num - ln + 2; gap >= 1; --gap)
        for(int have = 1; have <= k; ++have)
          if(f[old][num][gap][have] > 0)
            for(int in = n - num; in >= gap; --in){//increase
              int new_have = have * c[in - 1][gap - 1];
              if(new_have <= k){
                f[now][num + in][in - gap][new_have] += f[old][num][gap][have];
                f[now][num + in][in - gap][new_have] %= mod;
              }
            }
    for(int num = ln; num <= n; ++num)
      for(int have = 1; have <= k; ++have)
        ans = (ans + (ll)f[now][num][0][have] * (m - ln + 1) % mod) % mod;
  }
  cout << ans;
  return 0;
}
```

---

## 作者：Saka_Noa (赞：5)

### $\text{Description}:$

给定一个长为 $s$ 序列 $a$，如果 $a_1 = \min_{i=1}^{r} a_i$。
令 $a_{s + 1} = a_1$，有 $\forall i ,\left | a_i-a_{i+1} \right | =1$，我们称这个序列是良好的。  

给定一个长为 $s$ ($1 \le s \le n$) 单调不降的序列 $b$，如果 $\forall i ,1 \le b_i \le m$ 且将 $b$ 重新排列至少可以得到 $1$ 个良好序列，至多得到 $k$ 个良好序列，我们称 $b$ 是优秀的。  

给定 $n,m,k$ 求有多少个优秀的序列。结果对 $1e9+7$ 取模。   
数据范围：$1 \le n,m,k \le100$  

### $\text{Solution}:$   

要求优秀序列的方案数，首先想如何构造出一个这样的序列。但即使求至少 $1$ 良好序列也不好找出一些条件来描述这样的数列。所以我们尝试去构造良好的序列。  

如果我们从高位数字开始构造，当考虑到 $i$ 时，设有 $x$ 对相邻的 $i + 1$，当前我们要填入 $y$ 个数。发现有 $x$ 个 $i$ 要填在 $i + 1$ 之间，剩下的 $y-x$ 个 $i$ 可以与已经填的 $x$ 个 $i$ 构成 $y-x$ 对相邻的 $i$。至此，我们成功想出了一个构造方案，而且将我们构造的良好的序列还原回去可以得到至少能构造出一个良好序列的优秀序列。  

但是还有 $k$ 的限制，我们不妨再设一维状态 $l$ 表示当前良好序列所对应的优秀序列能排列出良好序列的方案数。  
设 $f_{i,j,k,l}$ 表示考虑到数 $i$，已经填了 $j$ 个数，还剩 $k$ 对要填的数，方案数为 $l$。则可以推出转移方程：
$$\Large f_{i,j+y,y-x,l \times C_{y-1}^{x-1}} = \sum f_{i+1,j,x,l}$$   


~~剩下的细节你自己想吧~~ 详见代码。  

Code  

```cpp

#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 105;
const int M = 1e9 + 7;

int n, m, k, cs;
ll f[2][N][N][N];
int c[N][N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr), cout.tie(nullptr);
    
    cin >> n >> m >> k;
    c[0][0] = 1;
    for(int i = 1; i < N; ++i) {
        for(int j = 0; j <= i; ++j) 
        if(!j) c[i][j] = c[i - 1][j];
        else c[i][j] = min(k + 1, c[i - 1][j] + c[i - 1][j - 1]);
    }   
    ll ans = 0; n++;
    
    f[cs][0][1][1] = 1;
    for(int i = 0; i <= m; ++i) {
        cs ^= 1;
        if(i) {
            ll sum = 0;
            for(int t = 2; t <= n; ++t) {
                for(int l = 1; l <= k; ++l)
                    sum = (sum + f[cs ^ 1][t][0][l]) % M;
            }
            ans = (ans + (m - i + 1) * sum % M) % M;
        }
        memset(f[cs], 0, sizeof f[cs]);
        for(int j = 0; j <= n; ++j) {
            for(int x = 1; x <= n; ++x) 
                for(int l = 1; l <= k; ++l) 
                    if(f[cs ^ 1][j][x][l])
                    for(int y = x; y + j <= n; ++y) 
                    (f[cs][j + y][y - x][min(k + 1, l * c[y - 1][x - 1])] += f[cs ^ 1][j][x][l]) %= M;
        }
    }

    cout << ans;
    return 0;
}

```







---

## 作者：syzf2222 (赞：3)

考虑$dp$，由于$n,m,k\le 100$，不妨多设几维状态。

想象一下，构造$\text{good array}$的过程实际上就是把最大的往次大的中间插空。

设$dp[i][j][k][l]$代表最大数为$i$，用了$j$个数，次大数有$k$个空隙，已经有$l$种方法。

枚举$i+1$的个数$t$，$k\le t$，不妨考虑次大数往最大数中插空。

每个空位只能加入一个次大数，故剩余$t-k$个空，方案数为$C_{t-1}^{k-1}$

故$dp[i][j][k][l]\rightarrow dp[i+1][j+t][t-k][l*C_{t-1}^{k-1}]$

方便起见，断环为链，设$a[n+1]=a[1]$，不妨设$a[1]=1$，结果乘以$m-i+1$即可。

初始条件：$dp[0][0][1][1]=1$

```
#include <bits/stdc++.h>
#define ll long long
#define mod 1000000007
#define N 109
using namespace std;
int c[N][N],n,m,K,dp[2][N][N][N],ans;
void add(int &x,int y){x=(x+y>=mod)?x+y-mod:x+y;}
int main(){
	cin>>n>>m>>K;n++;
	c[0][0]=1;
	for(int i=1;i<=K;i++)
		for(int j=0;j<=i;j++){
			c[i][j]=(j?c[i-1][j-1]:0)+c[i-1][j];
			if(c[i][j]>K)c[i][j]=K+1;
		}
	int now=1,las=0;
	dp[now][0][1][1]=1;
	for(int i=1;i<=m;i++){
		las=now,now^=1;
		memset(dp[now],0,sizeof(dp[now]));
		for(int j=0;j<=n;j++)
			for(int k=1;k<=n;k++)
				for(int l=1;l<=K;l++)
					if(dp[las][j][k][l])
						for(int t=k;t<=n-j;t++)
							if(l*c[t-1][k-1]<=K)
								add(dp[now][j+t][t-k][l*c[t-1][k-1]],dp[las][j][k][l]);
		int tmp=0;
		for(int j=2;j<=n;j++)
			for(int l=1;l<=K;l++)add(tmp,dp[now][j][0][l]);
		add(ans,(ll)tmp*(m-i+1)%mod);
	}
	cout<<ans<<'\n';
	return 0;
}
```

思路&代码借鉴[此博客](https://blog.csdn.net/wzf_2000/article/details/78856259)

深深地感到自己的弱小。

---

## 作者：UKE_Automation (赞：0)

### CF301E Yaroslav and Arrangements

[$\text{Link}$](https://codeforces.com/problemset/problem/301/E)

做这道题前需要注意我们的计数对象是优秀数列而不是良好数列。不过良好数列的性质还是需要分析的，不难发现，假如现在给出一个良好序列，其最大值为 $m$，如果要插入 $m+1$，显然只能放在 $m$ 的空隙中，并且每新增加一个 $m+1$ 实际上会增加两个数（一个 $m+1$ 和一个 $m$）。

我们先钦定首项为 $1$，最后只需要通过最大值就可以算出有多少不同的首项。设 $dp(i,j,k,l)$ 表示当前最大值为 $i$，序列总长为 $j$，最大值有 $k$ 个，能重排后得到 $l$ 个良好序列的序列个数。转移时先枚举 $i+1$ 放入 $p$ 个，根据上面的结论，总长会变成 $j+2p$。考虑此时多出的方案数，实际上就是将 $p$ 个数划分为 $k$ 个可空集合，这个是经典插板法，方案有 $\binom{p+k-1}{k-1}$ 种。

综上转移方程为：
$$
dp\left(i+1,j+2p,p,l\times \binom{p+k-1}{k-1}\right)=\sum dp(i,j,k,l)
$$
复杂度是 $O(n^5)$ 的，不过常数非常小，因此可以通过。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int Maxn = 100 + 5;
const int Inf = 2e9;
const int Mod = 1e9 + 7;

int add(int x, int y) {return x + y >= Mod ? x + y - Mod : x + y;}
void pls(int &x, int y) {x = add(x, y);}
int del(int x, int y) {return x - y < 0 ? x - y + Mod : x - y;}
void sub(int &x, int y) {x = del(x, y);}

int n, m, lim;
int C[Maxn][Maxn];
int dp[2][Maxn][Maxn][Maxn];

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> m >> lim;
	C[0][0] = 1;
	for(int i = 1; i <= n; i++) {
		C[i][0] = 1;
		for(int j = 1; j <= n; j++) {
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % Mod;
		}
	}
	int now = 0, nxt = 1;
	dp[0][1][1][1] = 1;
	int ans = 0;
	for(int i = 1; i <= m; i++) {
		for(int j = 1; j <= n + 1; j++) {
			for(int k = 1; k <= j; k++) {
				for(int l = 1; l <= lim; l++) {
					if(j != 1) ans = add(ans, dp[now][j][k][l] * (m - i + 1) % Mod);
					for(int p = 1; p <= n + 1 - j; p++) {
						int nl = l * C[p + k - 1][k - 1];
						if(nl > lim || j + 2 * p > n + 1) break;
						pls(dp[nxt][j + 2 * p][p][nl], dp[now][j][k][l]);
					}
					dp[now][j][k][l] = 0;
				}
			}
		}
		swap(now, nxt);
	}
	cout << ans << '\n';
	return 0;
}
```

貌似和题解区中的转移都不太一样？不过本质是差不多的。

---

## 作者：daniEl_lElE (赞：0)

考虑从小到大枚举，每次把数填到间隔里面。

考虑 $dp_{i,j,k,l}$ 表示看到 $i$，总共选出了 $j$ 个数放到序列中，$i+1$ 可以插入的连续段有 $k$ 个，重排之后有 $l$ 个符合要求的序列。我们容易发现符合要求的序列到 $i$ 位置的情况一定是相同的。

转移的时候枚举 $i$ 有 $x$ 个，容易发现 $j'=j+x$，$k'=x-k$（可以看作有 $x$ 个间隔，但是上一位有 $k$ 个间隔，已经占据了其中 $k$ 个），$l'=l\times\binom{k-1}{x-1}$（插板法）。

答案就是所有 $dp_{i,N,0,j}$，其中 $1\leq i\leq M$，$1\leq j\leq K$。

这样做是 $O(n^5)$，然而远跑不满（$\binom{k-1}{x-1}\times l\leq K$ 的情况很少），所以可以通过。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define add(i,j) ((i+j>=mod)?i+j-mod:i+j)
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7;
int C[105][105];
int dp[2][105][105][105];
signed main(){
	int n,m,K; cin>>n>>m>>K;
	for(int i=0;i<=100;i++) C[i][0]=1;
	for(int i=1;i<=100;i++){
		for(int j=1;j<=i;j++){
			C[i][j]=C[i-1][j]+C[i-1][j-1];
		}
	}
	int ans=0;
	for(int i=1;i<=m;i++){
		memset(dp[i&1],0,sizeof(dp[i&1]));
		for(int j=1;j<=n/2;j++) dp[i&1][j][j][1]=1;
		for(int j=1;j<=n;j++){
			for(int k=1;j+k<=n;k++){
				for(int l=k;(j+l<=n)&&(C[l-1][k-1]<=K);l++){
					for(int p=1;p*C[l-1][k-1]<=K;p++){
						if(l==k) ans=add(ans,dp[(i&1)^1][j][k][p]);
						else dp[i&1][j+l][l-k][p*C[l-1][k-1]]=add(dp[i&1][j+l][l-k][p*C[l-1][k-1]],dp[(i&1)^1][j][k][p]);
					}
				}
			}
		}
	}
	cout<<ans;
	return 0;
} 
```

---

