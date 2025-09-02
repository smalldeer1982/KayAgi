# [USACO16DEC] Team Building P

## 题目描述

每年，Farmer John 都会带着他的 $N$ 头奶牛参加州展览会的“最佳展示”比赛。他的劲敌 Farmer Paul 也会带着他的 $M$ 头奶牛参加比赛（$1 \leq N \leq 1000, 1 \leq M \leq 1000$）。

参加比赛的每头 $N + M$ 头奶牛都会获得一个单独的整数得分。然而，今年的最终比赛将由 $K$ 头奶牛组成的团队决定（$1 \leq K \leq 10$），规则如下：Farmer John 和 Farmer Paul 各自选择 $K$ 头奶牛组成团队进行比赛。这两个团队的奶牛将按得分高低配对：FJ 团队中得分最高的奶牛与 FP 团队中得分最高的奶牛配对，FJ 团队中得分第二高的奶牛与 FP 团队中得分第二高的奶牛配对，依此类推。如果在每一对中，FJ 的奶牛得分都更高，那么 FJ 获胜。

请帮助 FJ 计算他和 FP 可以选择团队的不同方式的数量，使得 FJ 能够赢得比赛。也就是说，每个不同的（FJ 的 $K$ 头奶牛集合，FP 的 $K$ 头奶牛集合）对，只要 FJ 获胜，都应被计入。输出结果对 $1\,000\,000\,009$ 取模。

## 样例 #1

### 输入

```
10 10 3
1 2 2 6 6 7 8 9 14 17
1 3 8 10 10 16 16 18 19 19```

### 输出

```
382```

# 题解

## 作者：大头 (赞：18)

为啥我是一血（233）

dp水题。

快排预处理。

f[i][j][k]表示匹配上了i头牛，FJ选择的是他的前j头牛，FP选择的是前K头牛的方案数。

状态转移见代码。

时间效率O（nmk）

```cpp
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#define mo 1000000009
using namespace std;
int a[1005],b[1005],f[12][1005][1005],n,m,p;
int main(){
    scanf("%d%d%d",&n,&m,&p);
    for (int i=1;i<=n;i++) scanf("%d",&a[i]);
    for (int i=1;i<=m;i++) scanf("%d",&b[i]);
    sort(a+1,a+n+1);
    sort(b+1,b+m+1);
    for (int i=0;i<=n;i++)
        for (int j=0;j<=m;j++) f[0][i][j]=1;
    for (int i=1;i<=p;i++){
        for (int j=1;j<=n;j++)
            for (int k=1;k<=m;k++)
                if (a[j]>b[k]) f[i][j][k]=f[i-1][j-1][k-1];
        for (int j=1;j<=n;j++)
            for (int k=1;k<=m;k++) f[i][j][k]=(f[i][j][k]+f[i][j][k-1])%mo;
        for (int j=1;j<=n;j++)
            for (int k=1;k<=m;k++) f[i][j][k]=(f[i][j][k]+f[i][j-1][k])%mo;
        }
    printf("%d",f[p][n][m]);
}
```

---

## 作者：冷月冰瞳 (赞：6)

这里提供另一种DP的思路，复杂度为O((N+M)K^2)。

将所有牛按照分数从大到小排，分数相同的FP的排前面，然后我们按该顺序依次看这个牛选不选。

F[i, j, k]表示前 i 头牛，选了 FJ 的 j 头牛，选了 FP 的 k 头牛。那么我们在转移的过程中，始终要保证 j >= k。因为一旦有出现 j < k 的情况，根据我们排序的顺序，后面没有能击败 FP 多出来的这 k - j 头牛了。但是如果整个过程，都有 j >= k，那么 FJ 的牛始终都能击败对应的牛。

根据当前牛是FJ的还是FP的，还有选还是不选来进行转移。

0. 不选该奶牛：F[i+1, j, k] += F[i, j, k]

0. 选该奶牛：如果该奶牛是FJ的，那么F[i+1,j+1,k] += F[i, j, k]；如果该奶牛是FP的，那么F[i+1,j,k+1]+=F[i, j, k]，但需要满足 j > k才能转移。


---

## 作者：guanjinquan (赞：3)

定义$dp[i][j][k]$为考虑前$i$头FJ的牛，前$j$头FP的牛，共选了$k$对的情况数。
那么就不难想到转移：

$if(a[i] > b[j])\space dp[i][j][k] += dp[i-1][j-1][k-1]$ ，这个转移是考虑添加一对牛的情况。

然后还有，考虑到我们定义的状态是前$i$头和前$j$头，所以我们还要sum一遍，比如说：
```cpp
for (int t1 = 1; t1 < i;t1++) { 
  for (int t2 = 1; t2 < j;t2++) {
		dp[i][j][k] += dp[t1][t2][k];	
	}
}      
```
那么这个转移我们可以使用二维前缀和优化掉。
代码如下：

```cpp
int n, m, K, a[maxn], b[maxn];
ll f[maxn][maxn][11], ans;

inline void add(ll& x, ll y) {
  x += y;
  if (x >= mod) x -= mod;
  if (x < 0) x += mod;
}

inline void solve() {
  cin >> n >> m >> K;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= m; i++) cin >> b[i];
  sort(a + 1, a + 1 + n), sort(b + 1, b + 1 + m);
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= m; j++) f[i][j][0] = 1;
  for (int k = 1; k <= K; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        add(f[i][j][k], f[i - 1][j][k]);
        add(f[i][j][k], f[i][j - 1][k]);
        add(f[i][j][k], -f[i - 1][j - 1][k]);
        if (a[i] > b[j]) add(f[i][j][k], f[i - 1][j - 1][k - 1]);
      }
    }
  }
  cout << f[n][m][K] % mod << endl;
}
```



---

## 作者：一颗赛艇 (赞：2)

我们列出了两个动态规划的方法，在这里，一个是o（NMK）这是一个和 o（（N M）K二）。


我们首先注意到有一个o（N二M二K）动态规划算法。让F（N，M，K）在一些银行的方式到火柴K对第一N农民约翰的 奶牛和第一M农民保罗的牛，农夫约翰胜。我们可以 减少K如果我们把一个得分最高的牛，农夫约翰和 农民保罗使用。与o（NM）转换和o（NMK）美国，我们得到一个o（N二M二K）算法.


而不是遍历所有o（NM）过渡，如果我们保持一个前缀求和， 我们可以F（N，M，K）进入o（1）时间

另一种方法来减少状态空间是利用的事实K小。


而不是明确的配对得分最高的奶牛，农民约翰和 农民保罗使用，我们将遍历从牛 得分最低得分最高。我们跟踪有多少奶牛农民约翰我们已分配 多少奶牛农民约翰我们已分配。我们要求我们 从未分配更多的奶牛农民约翰比Farmer Paul（否则 农民约翰会选择一头牛会不会赢）。


这DPo（（N M）K2）和o（1）转换。


代码：













```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
struct Node {
    int value;
    bool isFj;
    bool operator<(Node const& other) const {
        if (value == other.value) {
            return isFj && !other.isFj;
        }
        return value < other.value;
    }
};
#define NMAX 1000
#define KMAX 10
#define MOD 1000000009
unsigned int dp[2 * NMAX + 1][KMAX + 1][KMAX + 1];
int main() {
    int n, m, k;
    scanf("%d", &n);
    scanf("%d", &m);
    scanf("%d", &k);
    vector<Node> nodes;
    for (int i = 0; i < n; i++) {
        Node n;
        scanf("%d", &n.value);
        n.isFj = true;
        nodes.push_back(n);
    }
    for (int i = 0; i < m; i++) {
        Node n;
        scanf("%d", &n.value);
        n.isFj = false;
        nodes.push_back(n);
    }
    sort(nodes.begin(), nodes.end());
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= k; j++) {
            dp[nodes.size()][i][j] = (i == 0 && j == 0 ? 1 : 0);
        }
    }
    for (int pos = nodes.size() - 1; pos >= 0; pos--) {
        for (int i = 0; i <= k; i++) {
            for (int j = 0; j <= k; j++) {
                if (j > i) {
                    dp[pos][i][j] = 0;
                } else {
                    if (nodes[pos].isFj) {
                        dp[pos][i][j] = (dp[pos+1][i][j] + (i > 0 ? dp[pos+1][i-1][j] : 0)) % MOD;
                    } else {
                        dp[pos][i][j] = (dp[pos+1][i][j] + (j > 0 ? dp[pos+1][i][j-1] : 0)) % MOD;
                    }
                }
            }
        }
    }
    printf("%d\n", dp[0][k][k]);
}
```

---

## 作者：JYX0924 (赞：1)

一道简单的动态规划题，令 $dp_{i,j,k}$ 表示考虑到 $a_{i}$ 和 $b_{j}$，连胜 $k$ 局的方案数。

转移显而易见，$dp_{i,j,k}=dp_{i-1,j,k}+dp_{i,j-1,k}-dp_{i-1,j-1,k}$。若 $k=1$ 且 $a_{i}>b_{j}$，$dp_{i,j,k}=dp_{i,j,k}+1$。若 $a_{i}>b_{j}$，$dp_{i,j,k}=dp_{i,j,k}+dp_{i-1,j-1,k-1}$。

同时还要注意取模，以免出现负数。


```c
#include<bits/stdc++.h>
#define ll long long 
#define mod 1000000009
using namespace std;
ll n,m,k,a[1005],b[1005],dp[1005][1005][15];
//dp[i][j][k]表示考虑到a[i]，b[j]，全胜k局的方案数 
void add(ll &x,ll y)
{
	if(y<0) {y=abs(y); while(x<y) x+=mod; x=(x-y)%mod; return;}
	x=(x+y)%mod;
}
void DP()
{
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	for(int l=1;l<=k;l++)
	{
		add(dp[i][j][l],dp[i-1][j][l]); add(dp[i][j][l],dp[i][j-1][l]); add(dp[i][j][l],-dp[i-1][j-1][l]);
		if(a[i]>b[j]) add(dp[i][j][l],dp[i-1][j-1][l-1]);
        if(l==1&&a[i]>b[j]) dp[i][j][l]++,dp[i][j][l]%=mod;
 	}
	cout<<dp[n][m][k]%mod;
}
int main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>n>>m>>k; for(int i=1;i<=n;i++) cin>>a[i]; for(int i=1;i<=m;i++) cin>>b[i];
	sort(a+1,a+n+1); sort(b+1,b+m+1); DP();
	return 0;
}
```
谢谢大家！！！

---

## 作者：zzy0618 (赞：1)

## 题解：P2098 [USACO16DEC] Team Building P

这里提供两种 dp 的方法，一种强制，一种不强制。看 $dp_{i,j,k}$ 怎么表示。

一种，$dp_{i,j,k}$ 表示 FJ 选前 $i$ 头，FP 选前 $j$ 头，一共匹配了 $k$ 组，且 $i,j$ 必须匹配为一对的方案数。这样做，状态转移方程为 $dp_{i,j,k}=\sum_{x=0}^{i-1}\sum_{y=0}^{j-1}dp_{x,y,k-1}(a_i>b_j)$。

当然，这里转移需要前缀和优化，且最终答案为 $\sum_{i=0}^{n}\sum_{j=0}^{m}dp_{i,j,k}$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1002,K=12,mod=1e9+9;
int n,m,k;
int a[N],b[N];
int dp[N][N][K],s[N][N];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;++i)cin>>a[i];
	for(int i=1;i<=m;++i)cin>>b[i];
	sort(a+1,a+n+1);sort(b+1,b+m+1);
	dp[0][0][0]=1;
	for(int i=0;i<=n;++i)
		for(int j=0;j<=m;++j)
			s[i][j]=1;
	for(int l=1;l<=k;++l){
		for(int i=0;i<=n;++i)
			for(int j=0;j<=m;++j)
				if(a[i]>b[j])
					dp[i][j][k]=s[i-1][j-1];
		for(int i=0;i<N;++i)
			for(int j=0;j<N;++j)
				s[i][j]=0;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j){
				s[i][j]=(dp[i][j][k]+s[i-1][j]+s[i][j-1]-s[i-1][j-1]+mod)%mod;
			}
	}cout<<s[n][m]<<'\n';
	return 0;
}
```

另一种，$dp_{i,j,k}$ 表示 FJ 选前 $i$ 头，FP 选前 $j$ 头，一共匹配了 $k$ 组，但是不强制 $i,j$ 匹配。这样做，就要分类讨论。如果最后一组匹配，有 $dp_{i-1,j-1,k-1}$ 种方式，且要 $a_i>b_j$；如果不匹配，有 $dp_{i-1,j,k}+dp_{i,j-1,k}-dp_{i-1,j-1,k}$ 种方式。

这样就不用前缀和，且最终答案为 $dp_{n,m,k}$，相对于前一种要更加方便。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1002,K=12,mod=1e9+9;
int n,m,k;
int a[N],b[N],dp[N][N][K];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;++i)cin>>a[i];
	for(int i=1;i<=m;++i)cin>>b[i];
	sort(a+1,a+n+1);sort(b+1,b+m+1);
	for(int i=0;i<=n;++i)
		for(int j=0;j<=m;++j)
			dp[i][j][0]=1;
	for(int l=1;l<=k;++l){
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				dp[i][j][l]=(dp[i-1][j][l]+dp[i][j-1][l]-dp[i-1][j-1][l]+mod)%mod;
				if(a[i]>b[j])(dp[i][j][l]+=dp[i-1][j-1][l-1])%=mod;
			}
		}
	}cout<<dp[n][m][k]<<'\n';
	return 0;
}
```

所以有时考虑一下最后是否强制能够降低转移和实现的难度，这题就是很好的例子。

---

## 作者：xixisuper (赞：1)

# [USACO16DEC] Team Building P 题解

一道比较好想的 dp 题。

形式化题目：

- 给定一个长度为 $N$ 的正整数序列 $A$，以及一个长度为 $M$ 的正整数序列 $B$。
- 从序列 $A$ 和 $B$ 中分别取出一个长度为 $K$ 的子序列$C$ 、$D$。
- 询问有多少组 $C$、$D$ 满足 $C$ 中第 $i$ 大的数大于 $D$ 中第 $i$ 大的数，$1 \leq i \leq K$。

## 思路

看一眼题目，$N$，$M$，$K$ 都比较小，时间复杂度 $O(NMK)$ 也许大概可以过，直接考虑搜索 or dp。

FJ 的第 $i$ 头牛的分数为 $A_i$，FP 的第 $j$ 头牛的分数为 $B_j$，我们设 $dp_{i,j,k}$ 表示，FJ 的**前 $i$ 头牛**和 FP 的**前 $j$ 头牛**中**各选 $k$ 头牛** FJ 所能获胜的次数，那么显然答案为 $dp_{N,M,K}$。

我们考虑转移方程，能够发现的是 $dp_{i,j,k}$ 中一定包含 $dp_{i-1,j,k}$ 和 $dp_{i,j-1,k}$，而 $dp_{i-1,j,k}$ 与 $dp_{i,j-1,k}$ 又同时包含 $dp_{i-1,j-1,k}$，那么根据容斥原理，就能够推得：$dp_{i,j,k}=dp_{i-1,j,k}+dp_{i,j-1,k}-dp_{i-1,j-1,k}$

结束了吗？显然没有，根据 $dp$ 的定义我们发现，上述表达式仅统计了**不同时包含 FJ 的第 $i$ 头牛和 FP 的第 $j$ 头牛**的情况，所以当 $A_i > B_j$ 时，$dp_{i,j,k}$ 需要再加上 $dp_{i-1,j-1,k-1}$。

综上所述，我们就可以得到这道题的转移方程式：

$$
dp_{i,j,k} = 
\begin{cases}
dp_{i-1,j,k}+dp_{i,j-1,k}-dp_{i-1,j-1,k}+dp_{i-1,j-1,k-1}     &A_i > B_j \\
dp_{i-1,j,k}+dp_{i,j-1,k}-dp_{i-1,j-1,k}    &\text{otherwise}
\end{cases}
$$

注意边界条件：

- 当 $i < k$ 或 $j < k$ 时，$dp_{i,j,k}=0$
- 当 $k=0$ 时，$dp_{i,j,k}=1$

~~啊？你问这边界条件怎么推出来的？那当然是照着样例读出来的......~~

集训模拟赛时的一道题，赛时已 A。

## 代码

```cpp
#include <iostream>
#include <algorithm>
#define ll int
using namespace std;
const ll MOD=1e9+9;
const ll N=1002;
const ll M=1002;
const ll K=12;
ll f[N][M][K],n,m,kkk;
ll A[N],B[M];
bool cmp(ll a,ll b){return a>b;}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m>>kkk;
	for(ll i=1;i<=n;i++) cin>>A[i];
	for(ll j=1;j<=m;j++) cin>>B[j];
	for(register ll k=0;k<=kkk;k++){
		for(register ll i=0;i<=n;i++){
			for(register ll j=0;j<=m;j++){
				if(k==0) f[i][j][k]=1;
				else{
					if(i<k||j<k) f[i][j][k]=0;
					else{
						f[i][j][k]=(f[i-1][j][k]+f[i][j-1][k])%MOD;
						f[i][j][k]=(f[i][j][k]-f[i-1][j-1][k]+MOD)%MOD;
						if(A[i]>B[j]) f[i][j][k]=(f[i][j][k]+f[i-1][j-1][k-1])%MOD;
					}
				}
			}
		}
	}
	cout<<f[n][m][kkk];
	return 0;
}
```

---

## 作者：Y2y7m (赞：1)

前缀和优化 $\text{dp}$ 板子题。

定义状态 $f_{i,j,k}$ 为 $\text{fj}$ 到了第 $i$ 头牛，$\text{fp}$ 到了第 $j$ 头牛，已经匹配了 $k$ 对牛，且 $\text{fj}$ 的第 $i$ 头牛和 $\text{fp}$ 的第 $j$ 头牛组成最新的一对。

状态转移为：

$$f_{i,j,k}=\sum_{p,q}^{a_p>b_q}{f_{p,q,k-1}}$$

其中 $a$ 数组为 $\text{fj}$ 的牛，$b$ 数组为 $\text{fp}$ 的牛。

当然，这里同时也需要保证 $a_i>b_j$ 才是合法状态。

发现对于这个式子可以进行前缀和优化。

定义 $sum_{i,j,k}$ 为已经配对了 $k$ 对牛时，所有用于配对的 $\text{fj}$ 的牛都在他的第 $i$ 头牛以前，所有用于配对的 $\text{fp}$ 的牛都在他的第 $j$ 头牛前的所有情况总数。

显然这是 $f$ 数组的二维前缀和。

code:

```cpp
//
//  main.cpp
//  [USACO16DEC] Team Building P
//
//  Created by Y2y7m on 2023/8/30.
//  Copyright © 2023年 Slip. All rights reserved.
//

#include <bits/stdc++.h>

using namespace std;
#define int long long
const int mod=1e9+9;
int n,m,k;
int a[1010],b[1010];
int f[1010][1010][12];
int sum[1010][1010];
signed main()
{
    ios::sync_with_stdio(false);
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+1+n);
    for(int i=1;i<=m;i++) cin>>b[i];
    sort(b+1,b+1+m);
    for(int i=0;i<=n;i++) for(int j=0;j<=m;j++) sum[i][j]=1;
    f[0][0][0]=1;
    for(int e=1;e<=k;e++)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                if(a[i]>b[j]) f[i][j][e]=sum[i-1][j-1];
            }
        }
        memset(sum,0,sizeof(sum));
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                sum[i][j]=(sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+f[i][j][e]+mod)%mod;
            }
        }
    }
    cout<<sum[n][m]<<endl;
    return 0;
}

```


---

## 作者：onglu (赞：1)

下面两个$O((n+m)k^2)$的 题解要么奇奇怪怪要么不丢代码。这里丢一个完整的。  

把所有牛放在一起从大到小排序，相同则$A$的牛放在前面，问题变为从序列中选择一些元素，使得任意前缀$A$入选的个数大于$B$入选的个数。  

$f[i][j][k]$表示考虑了前$i$头牛，$A$入选了$j$头，$B$比$A$少$k$头，转移就判断下一头牛是$A$的还是$B$的，如果是$B$还要判断当前状态$k$是不是等于$0$。  
  
具体看代码吧。  
  
```cpp
#include <bits/stdc++.h>
#define Mid ((l + r) >> 1)
#define lson (rt << 1)
#define rson (rt << 1 | 1)
using namespace std;
const int mod = 1e9 + 9;
int read(){
	char c; int num, f = 1;
	while(c = getchar(),!isdigit(c)) if(c == '-') f = -1; num = c - '0';
	while(c = getchar(), isdigit(c)) num = num * 10 + c - '0';
	return f * num;
}
struct node {
	int x, t;
} a[2009];
int n, m, p, f[2009][2009][20];
int cmp(node a, node b) {
	return (a.x == b.x && a.t > b.t) || a.x > b.x;
}
void up(int &a, int b) {a = (a + b) % mod;}
signed main()
{
	n = read(); m = read(); p = read();
	for(int i = 1; i <= n; i++) a[i] = (node){read(), 1};
	for(int i = 1; i <= m; i++) a[i + n] = (node){read(), 2};
	sort(a + 1, a + 1 + n + m, cmp); f[0][0][0] = 1;
	for(int i = 0; i <= n + m; i++) {
		for(int j = 0; j <= min(i, p); j++) {
			for(int k = 0; k <= j; k++) {
				up(f[i + 1][j][k], f[i][j][k]);
				if(a[i + 1].t == 1) up(f[i + 1][j + 1][k + 1], f[i][j][k]);
				if(a[i + 1].t == 2 && k) up(f[i + 1][j][k - 1], f[i][j][k]);
			}
		}
	}
	printf("%lld\n", f[n + m][p][0]);
	return 0;
}
```

---

## 作者：wizard（偷开O2 (赞：0)

一道动态规划好题。

### 题意

有两个序列 $A,B$，每次可以从两个序列中各选择 $k$ 个数字组成两支队伍，我们令其为 $q1,q2$，需要保证所有的 $q1_{i}>q2_{i}$，农场主才能胜利。

问：有多少种选队方法？

### 分析

我们可以设 $dp_{i,j,k}$ 为从 $A$ 中前 $i$ 个，$B$ 中前 $j$ 个中各选 $k$ 个数字组成队伍。

对于初态设定，分析可以得到如果一个数字都不选的话，有 $1$ 种方法；如果选择的 $k$ 个数字中有数字不包含在前 $i$ 或 $j$ 个数中，就说明不可能成立，那么答案一定为 $0$。

这一点不难理解，难理解的是状态转移。

不难发现：$dp_{i,j,k}$ 的前一个状态是 $dp_{i-1,j,k}$ 和 $dp_{i,j-1,k}$，而这两个状态有有交集，且交集为 $dp_{i-1,j-1,k}$。

所以状态转移方程就是 $dp_{i,j,k} = dp_{i-1,j,k} + dp_{i,j-1,k} - dp_{i-1,j-1,k}$。

另外，如果 $a_{i}>b_{j}$ 就是 $dp_{i,j,k} = dp_{1,j,k} + dp_{i-1,j-1,k-1}$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long 
const int modd=1e9+9;
const int maxn=1e6+10;
const int maxdp=1004;
int dp[maxdp][maxdp][15];
//表示FJ从前i头，FP从前j头中选k头牛进行比赛 
//end:dp[i][j][k]
//下一个状态一定包含上一个状态 
int n,m,k;
int a[maxn],b[maxn];
signed main(){
	cin >> n >> m >> k;
	for(int i=1;i<=n;i++)cin >> a[i];
	for(int i=1;i<=m;i++)cin >> b[i];
	//sort(a+1,a+n+1,cmp),sort(b+1,b+m+1,cmp);
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++){
			dp[i][j][0]=1;
			//一头牛都不选，所以答案唯一 
		}
	}
	for(int q=1;q<=k;q++){
		for(int i=0;i<=n;i++){
			for(int j=0;j<=m;j++){
				if(i<q||j<q)dp[i][j][q]=0;
				else{
					dp[i][j][q]=(dp[i-1][j][q]+dp[i][j-1][q])%modd;
					dp[i][j][q]=(dp[i][j][q]-dp[i-1][j-1][q]+modd)%modd;
					if(a[i]>b[j]){
						dp[i][j][q]=(dp[i][j][q]+dp[i-1][j-1][q-1])%modd;
					}	
				}
			}
		}
	}
	cout << dp[n][m][k] <<endl;
	return 0;
}
```

---

