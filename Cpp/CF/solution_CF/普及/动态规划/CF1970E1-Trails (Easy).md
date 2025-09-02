# Trails (Easy)

## 题目描述

Harry Potter is hiking in the Alps surrounding Lake Geneva. In this area there are $ m $ cabins, numbered 1 to $ m $ . Each cabin is connected, with one or more trails, to a central meeting point next to the lake. Each trail is either short or long. Cabin $ i $ is connected with $ s_i $ short trails and $ l_i $ long trails to the lake.

Each day, Harry walks a trail from the cabin where he currently is to Lake Geneva, and then from there he walks a trail to any of the $ m $ cabins (including the one he started in). However, as he has to finish the hike in a day, at least one of the two trails has to be short.

How many possible combinations of trails can Harry take if he starts in cabin 1 and walks for $ n $ days?

Give the answer modulo $ 10^9 + 7 $ .

## 样例 #1

### 输入

```
3 2
1 0 1
0 1 1```

### 输出

```
18```

# 题解

## 作者：Shxt_Plus (赞：1)

### 题目大意：

小湖有 $m$ 个休息点，小湖中间有一个小岛，每天小 $A$ 要去中间小岛观赏风景，然后去一个休息点休息。每个休息点离中间小岛有 $a_i$ 条短路和 $b_i$ 条长路。每天小 $A$ 至少要走一条短路，问 $n$ 天总共有多少种路径。

### Easy Version：

首先可以想到最朴素的 DP，设 $f_{i,j}$ 为第 $i$ 天走到第 $j$ 个休息点的方案数。

令 $p_i=a_i+b_i$，显然从 $i$ 号休息点走到 $j$ 号休息点有 $p_i\times p_j-b_i\times b_j$ 种方案。

则有转移式：

$$ f_{i,j}=\sum_{k=1}^n f_{i-1,k} \times (p_j \times p_k-b_j \times b_k) $$

复杂度： $O(n\times m^2)$

因为 $n,m$ 都很小，直接转移即可。

### Middle Version：

显然可以用矩阵快速幂优化。

令 $g_{i,j}=p_i\times p_j-b_i\times b_j$。

构造矩阵：
$$
\begin{bmatrix}
 g_{1,1} & g_{1,2} & g_{1,3} & \cdots\\
 g_{2,1} & g_{2,2} & g_{2,3} & \cdots\\
 g_{3,1} & g_{3,2} & g_{3,3} & \cdots\\
 \cdots & \cdots & \cdots & \cdots
\end{bmatrix}
$$

时间复杂度：$O(m^3 \times \log n)$

因为 $m$ 只有 $100$，可以通过此题。

### Hard Version：
显然 E2 的做法已经难以优化了，考虑从 E1 的做法下手。

首先显然可以把转移式拆成两部分：

$$
\begin{aligned}
f_{i,j}&=\sum_{k=1}^m f_{i-1,k} \times p_j \times p_k -\sum_{k=1}^m  f_{i-1,k} \times b_j \times b_k \\
&=p_j\times \sum_{k=1}^m f_{i-1,k} \times p_k-b_j\times \sum_{k=1}^m f_{i-1,k} \times b_k
\end{aligned}

$$

令 $s_i=\sum_{k=1}^m f_{i,k}\times p_k$，$g_i=\sum_{k=1}^m f_{i,k}\times b_k$。

则 $f_{i,j}=p_j\times s_i-b_j\times g_i$。

显然我们只需要求出 $s_{n-1}$，$g_{n-1}$ 就可以求出 $\sum_{k=1}^m f_{n,k}$ 了。

进一步化式子：

$$
\begin{aligned}
s_i&=\sum_{k=1}^m f_{i,k}\times p_k\\
&=\sum_{k=1}^m p_k\times p_k \times s_{i-1}-p_k \times b_k \times g_{i-1}\\
&=\sum_{k=1}^m p_k^2 \times s_{i-1} -\sum_{k=1}^m p_k \times b_k \times g_{i-1}\\
&=s_{i-1}\times \sum_{k=1}^m p_k^2- g_{i-1}\times \sum_{k=1}^m p_k \times b_k
\end{aligned}
$$

$g_i$ 的转移也同理。

显然可以用矩阵快速幂优化。

构造矩阵：
$$
\begin{bmatrix}
 \sum_{i=1}^m p_i \times p_i & -\sum_{i=1}^m p_i \times b_i\\
 \sum_{i=1}^m p_i \times b_i & -\sum_{i=1}^m b_i \times b_i\\
\end{bmatrix}
$$

时间复杂度： $O(2^3 \log n)$。

[Code](https://codeforces.com/contest/1970/submission/285973377)

---

## 作者：KukCair (赞：1)

### 基本思路

设 $dp_{i,j}$ 为第 $i$ 天时在第 $j$ 个小屋的方案数，$r_j$ 为第 $j$ 个小屋共有多少条路连接（即 $s_j+l_j$）。

易得转移方程为

$$dp_{i,j} = \sum_{k=1}^{m}dp_{i-1,k} \cdot (r_j\cdot r_k-l_j\cdot l_k)$$

（因为至少走一条短路，所以减去全长路的情况）

### 代码实现

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 1e9 + 7;
int n, m, s[105], l[105], r[105], dp[1005][105];
// dp[i][j]:第 i 天时在第 j 个小屋的方案数
signed main(){
	cin >> m >> n;
	for(int i = 1; i <= m; i++) cin >> s[i];
	for(int i = 1; i <= m; i++){
		cin >> l[i];
		r[i] = l[i] + s[i];
	}
	dp[0][1] = 1;
	for(int i = 1; i <= n; i++){ //天数
		for(int j = 1; j <= m; j++){ //小屋编号
			int sum = 0;
			for(int k = 1; k <= m; k++){
				sum += (r[j] * r[k] - l[j] * l[k]) * dp[i - 1][k];
				sum %= MOD;
			}
			dp[i][j] = sum;
		}
	}
	int sum = 0;
	for(int i = 1; i <= m; i++){
		sum += dp[n][i];
		sum %= MOD;
	}
	cout << sum;
	return 0;
}
```

---

## 作者：huhangqi (赞：0)

### 对于 Easy 部分的做法：

很容易想到统计下来每个点的位置，枚举到达的点，然后进行转移统计即可。

时间复杂度 $O(m^2n)$。

由于个人习惯，代码中的 $n$ 和 $m$ 与原题目不同。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,m,s[100005],l[100005],t[2][100005];
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>s[i];
	for(int i=1;i<=n;i++)cin>>l[i];
	t[0][1]=1;
	int cnt=0;
	for(int i=1;i<=m;i++){
		cnt^=1;
		for(int j=1;j<=n;j++)t[cnt][j]=0;
		for(int j=1;j<=n;j++){
			for(int k=1;k<=n;k++){
				t[cnt][k]+=((t[cnt^1][j]*s[j])%mod*s[k])%mod;
				t[cnt][k]%=mod;
				t[cnt][k]+=((t[cnt^1][j]*s[j])%mod*l[k])%mod;
				t[cnt][k]%=mod;
				t[cnt][k]+=((t[cnt^1][j]*l[j])%mod*s[k])%mod;
				t[cnt][k]%=mod;
			}
		}
	}
	int sum=0;
	for(int i=1;i<=n;i++)sum=(sum+t[cnt][i])%mod;
	cout<<sum;
	return 0;
}

``````

### 对于 Medium 部分的做法：

我们不难发现上一步转移形式很固定，甚至正好是乘上某数再加起来，而且正好每次更新同时更新了所有值。

那么我们很容易想到用矩阵优化。

直接模版把上一步的内容放到矩阵中，快速幂即可。

由于个人习惯，代码中的 $n$ 和 $m$ 与原题目不同。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,m,s[100005],l[100005],t[2][100005];
struct MT{
	int n,m,c[105][105];
	MT(){
		n=m=0;
		memset(c,0,sizeof(c));
	}
	MT friend operator*(MT a,MT b){
		MT c;
		c.n=a.n,c.m=b.m;
		for(int i=1;i<=a.n;i++){
			for(int j=1;j<=b.m;j++){
				for(int k=1;k<=a.m;k++){
					c.c[i][j]+=(a.c[i][k]*b.c[k][j])%mod;
					c.c[i][j]%=mod;
				}
			}
		}
		return c;
	}
}base,be;
void ksm(MT a,int b){
	while(b){
		if(b&1)be=be*a;
		a=a*a;
		b>>=1;
	}
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>s[i];
	for(int i=1;i<=n;i++)cin>>l[i];
	be.n=1,be.m=n;
	be.c[1][1]=1;
	base.n=base.m=n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			base.c[i][j]=((s[i]*s[j]%mod+s[i]*l[j]%mod)%mod+l[i]*s[j]%mod)%mod;
		}
	}
	ksm(base,m);
	int sum=0;
	for(int i=1;i<=n;i++)sum=(sum+be.c[1][i])%mod;
	cout<<sum;
	return 0;
}

``````

### 对于 Hard 部分的做法：

这里应该才是最难的一步，可以直接将绿题变成紫题。

我们发现矩阵里如果存下所有点的数字，那么矩阵乘法做一次就超时了。

但是这 $n$ 又非常大，也不好直接推导数学做法。

这时候我们想到在第一个点出来以后，我们走到湖中间上时去哪里只受到前面走了什么路的影响。

那么此时有多少种可能的做法就固定了。

走到下一个屋子，还要再回来，那么此时的点也确定了。

我们将这两步放到一起，从湖中间出发再走回来，在矩阵中记录上次走长路和短路的总方案数，这样就可以用矩阵快速求解了。

我们只需要先走到中间，再矩阵求方案数，再枚举回来的点，就可以得到答案了。

关于矩阵的具体推算可以看代码。

由于个人习惯，代码中的 $n$ 和 $m$ 与原题目不同。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,m,s[100005],l[100005];
struct MT{
	int c[5][5],n,m;
	MT(){
		n=m=0;
		memset(c,0,sizeof(c));
	}
	MT friend operator*(MT a,MT b){
		MT c;
		c.n=a.n,c.m=b.m;
		for(int i=1;i<=a.n;i++){
			for(int j=1;j<=b.m;j++){
				for(int k=1;k<=a.m;k++)c.c[i][j]=(c.c[i][j]+(a.c[i][k]*b.c[k][j])%mod)%mod;
			}
		}
		return c;
	}
}base,be;
void ksm(MT a,int b){
	while(b){
		if(b&1)be=be*a;
		a=a*a;
		b>>=1;
	}
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>s[i];
	for(int i=1;i<=n;i++)cin>>l[i];
	be.n=1,be.m=2;
	be.c[1][1]=s[1],be.c[1][2]=l[1];
	base.n=base.m=2;
	int sum=0;
	for(int i=1;i<=n;i++)sum=(sum+((l[i]*s[i])%mod+(s[i]*s[i])%mod)%mod)%mod;
	base.c[1][1]=sum;
	sum=0;
	for(int i=1;i<=n;i++)sum=(sum+(s[i]*s[i])%mod)%mod;
	base.c[2][1]=sum;
	sum=0;
	for(int i=1;i<=n;i++)sum=(sum+((l[i]*s[i])%mod+(l[i]*l[i])%mod)%mod)%mod;
	base.c[1][2]=sum;
	sum=0;
	for(int i=1;i<=n;i++)sum=(sum+(s[i]*l[i])%mod)%mod;
	base.c[2][2]=sum;
	ksm(base,m-1);
	sum=0;
	for(int i=1;i<=n;i++){
		sum+=(s[i]*be.c[1][1])%mod;
		sum%=mod;
		sum+=(l[i]*be.c[1][1])%mod;
		sum%=mod;
		sum+=(s[i]*be.c[1][2])%mod;
		sum%=mod;
	}
	cout<<sum;
	return 0;
}
/*
s->s
s l s
s s s
l->s
l s s
s->l
s l l
s s l
l->l
l s l
*/


``````

---

## 作者：The_foolishest_OIer (赞：0)

一眼 DP。

令 $dp_{i,j}$ 为第 $i$ 天走到 $j$ 的方案总数。

对于 $dp_{i,j}$，我们可以从前一天的所有点转移过来，即 $dp_{i,j} = \sum_{k = 1}^m dp_{i - 1,k} \times (s_j \times s_k + s_j \times t_k + t_j \times s_k)$。

所以答案就是 $\sum_{i = 1}^m dp_{n,i}$。

初始化 $dp_{0,1} = 1$。

时间复杂度：$O(nm^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 1e3 + 10;
const int M = 105;
const int mod = 1e9 + 7;
int T,n,m;
int a[M],b[M];
int dp[N][M];
void close(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
}
void solve(){
	cin >> m >> n;
	for (int i = 1 ; i <= m ; i++) cin >> a[i];
	for (int i = 1 ; i <= m ; i++) cin >> b[i];
	dp[0][1] = 1;
	for (int i = 1 ; i <= n ; i++){
		for (int j = 1 ; j <= m ; j++){
			for (int k = 1 ; k <= m ; k++){
				if (!a[j] && !a[k]) continue;
				else if (!a[j]) dp[i][j] = (dp[i][j] + dp[i - 1][k] * a[k] * b[j]) % mod;
				else if (!a[k]) dp[i][j] = (dp[i][j] + dp[i - 1][k] * a[j] * b[k]) % mod;
				else dp[i][j] = (dp[i][j] + dp[i - 1][k] * (a[j] * b[k] + a[k] * b[j] + a[j] * a[k])) % mod; // 可以只写一行
			}
		}
	}
	int ans = 0;
	for (int i = 1 ; i <= m ; i++) ans = (ans + dp[n][i]) % mod;
	cout << ans << endl;
}
signed main(){
	close();
    T = 1;
	//cin >> T;
	while (T--) solve(); 
	return 0;
}
```

---

## 作者：daitangchen2008 (赞：0)

## 思路
令 $a_{i}$ 为从 $i$ 走到湖的短路，再令 $b_{i}$ 为从 $i$ 走到湖的长路。  
设 $mp_{i,j}$  表示从 $i$ 走到 $j$ 的方案数，则有：
$$mp_{i,j}=a_{i}\times b_{j}+b_{i}\times a_{j}+a_{i}\times a_{j}$$  
我们设 $dp_{i,j}$ 为在第 $i$ 天走到第 $j$ 小木屋的方案数。  
则有动态转移方程:
$$dp_{i,j}=\sum_{k=1}^ndp_{i-1,k}\times mp_{j,k}$$
即可求出答案。
## 代码  

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD=1e9+7;
const int N=2e3+10;
int a[N];
int b[N];
int dp[N][N];
int mp[N][N];
signed main()
{
    int m,n;
    cin>>m>>n;
    dp[0][1]=1;
    for(int i=1;i<=m;i++)
        cin>>a[i];
    for(int i=1;i<=m;i++)   
        cin>>b[i];
    for(int i=1;i<=m;i++)
        for(int j=1;j<=m;j++)
        mp[i][j]=a[i]*b[j]+a[j]*b[i]+a[i]*a[j];
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            for(int k=1;k<=m;k++)
            {
                dp[i][j]+=((dp[i-1][k]*mp[k][j]%MOD));
                dp[i][j]%=MOD;
            }
        }
    }
    int ans=0;
    for(int i=1;i<=m;i++)
        ans+=dp[n][i],ans%=MOD;
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：joker_opof_qaq (赞：0)

考虑状态转移。

设 $dp_{i,j}$ 表示在第 $i$ 天最终待在 $j$ 号房子的总方案数。

先考虑从 $i$ 号房间转移到 $j$ 号房间怎么计算，若无限制，方案数自为 $(s_j+l_j) \times (s_k+l_k)$，然而长路径不能同时存在，所以将 $l_j \times l_k$ 删除即可。

枚举回合数 $i$，起点 $j$，中点 $k$。

$dp_{i,j}=\sum_{k=1}^{m}dp_{i-1,k} \times \max(0,(s_j+l_j) \times (s_k+l_k) - (l_j \times l_k))$

别忘记赋初值和取模，答案是第 $n$ 天所有数之和。

---

## 作者：Daniel_yao (赞：0)

# Solve

很暴力的计数题。

设 $dp_{i,j}$ 表示在第 $i$ 天，最后待在了 $j$ 号房子中的总方案数。

先考虑从 $i$ 号房间走到 $j$ 号房间的方案数如何计算。不考虑限制，单次方案数为 $(s_j+l_j)\times (s_k+l_k)$，然后由于不能存在同时为长路径的情况，于是把 $(l_j \times l_k)$ 减掉即可。

枚举回合 $i$，起点 $j$，终点 $k$，于是有：

$$
dp_{i,j}=\sum\limits_{k=1}^m dp_{i-1,k}  \times \max(0, (s_j+l_j)\times (s_k+l_k) - (l_j \times l_k))
$$

答案为 $\sum\limits_{i=1}^m dp_{n,i}$，记得初始化 $dp_{0,1}=1$。

时间复杂度 $O(nm^2)$。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long 
#define For(i,l,r) for(int i=l;i<=r;++i)
#define FOR(i,r,l) for(int i=r;i>=l;--i)
#define mod 1000000007

using namespace std;

const int M = 105, N = 1005;

int n, m, s[M], l[M], dp[N][M];

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> m >> n;
  For(i,1,m) cin >> s[i];
  For(i,1,m) cin >> l[i];
  dp[0][1] = 1;
  For(i,1,n) {
    For(j,1,m) {
      For(k,1,m) {
        dp[i][j] += (dp[i-1][k] % mod * (max(0ll, (s[j] + l[j]) * (s[k] + l[k]) - (l[j] * l[k])) % mod)) % mod;
      } 
    } 
  }
  int ans = 0;
  For(i,1,m) {
    ans += dp[n][i];
    ans %= mod;
  }
  cout << ans << '\n';
  return 0;
}
```

---

## 作者：_Weslie_ (赞：0)

## 前置知识

E1：dp。

E2：矩阵快速幂。

## 思路

### 暴力 dp

不难想到一个思路就是暴力 dp。

设 $dp_{i,j}$ 表示走了 $i$ 天，到达点 $j$ 的方案数，显然有方程：

$$dp_{i,j}=\sum_{k=1}^{n}(sum_j\times sum_k-l_j\times l_k)dp_{i-1}{k}$$

其中 $sum_j=l_j+s_j$。

原因很明显：如果没有限制，根据乘法原理，可以有 $sum_j\times sum_k$ 种。但是有了限制，全选长的就不行，答案就得剪掉全选长的的数量。

```
#include<bits/stdc++.h>
using namespace std;
int n,m;
long long s[105],l[105],sum[105],dp[1005][105],ans; 
int main(){
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)scanf("%lld",&s[i]);
	for(int i=1;i<=m;i++){
		scanf("%lld",&l[i]);
		sum[i]=l[i]+s[i];
	}
	dp[0][1]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int k=1;k<=m;k++){
				dp[i][j]=(dp[i][j]+((sum[k]*sum[j]-l[k]*l[j])%1000000007)*dp[i-1][k])%1000000007;
			}
		}
	}
	for(int i=1;i<=m;i++){
		ans+=dp[n][i];
		ans%=1000000007;
	}
	printf("%lld",ans%1000000007);
	return 0;
}
```

时间复杂度 $\operatorname{O}(nm^2)$。

### 矩阵优化

显然对于 E2 上面做法是过不去的。

考虑一下：每次我们转移，对于一个确定的 $k$，我们在 $dp_{i-1,k}$ 前乘的系数是一定的，不难联想到矩阵优化。

因为矩阵有结合律，所以我们可以使用[矩阵快速幂](https://www.luogu.com.cn/problem/P3390)优化。

在矩阵优化题中，最重要的就是构造转移矩阵。这个题的转移矩阵就是 $dp_{i-1,k}$ 的系数，即下面的矩阵：

$$
\begin{bmatrix}
sum_1\times sum_1-l_1\times l_1 & sum_2\times sum_1-l_2\times l_1 & \cdots & sum_m\times sum_1-l_m\times l_1\\
sum_1\times sum_2-l_1\times l_2 & sum_2\times sum_2-l_2\times l_2 & \cdots & sum_m\times sum_2-l_m\times l_2\\
\vdots &\vdots &\ddots & \vdots\\
sum_m\times sum_1-l_m\times l_1 &sum_m\times sum_2-l_m\times l_2 &\cdots &sum_m\times sum_m-l_m\times l_m
\end{bmatrix}
$$

如果不理解，可以试着去手搓下面柿子的值：

$$
\begin{bmatrix}
dp_{i-1,1} & dp_{i-1,2} & \cdots & dp_{i-1,m}
\end{bmatrix}
\times
\begin{bmatrix}
sum_1\times sum_1-l_1\times l_1 & sum_2\times sum_1-l_2\times l_1 & \cdots & sum_m\times sum_1-l_m\times l_1\\
sum_1\times sum_2-l_1\times l_2 & sum_2\times sum_2-l_2\times l_2 & \cdots & sum_m\times sum_2-l_m\times l_2\\
\vdots &\vdots &\ddots & \vdots\\
sum_m\times sum_1-l_m\times l_1 &sum_m\times sum_2-l_m\times l_2 &\cdots &sum_m\times sum_m-l_m\times l_m
\end{bmatrix}
$$

就会得到：

$$
\begin{bmatrix}
dp_{i,1} & dp_{i,2} & \cdots & dp_{i,m}
\end{bmatrix}
$$

所以这个矩阵是对的。

```
#include<bits/stdc++.h>
using namespace std;
struct matrix{
	long long a[105][105];
};
int m;
long long n;
matrix operator *(matrix a,matrix b){
	matrix c;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			c.a[i][j]=0;
		}
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			for(int k=1;k<=m;k++){
				c.a[i][j]+=a.a[i][k]*b.a[k][j];
				c.a[i][j]%=1000000007;
			}
		}
	}
	return c;
}
matrix qpow(matrix a,long long b){
	matrix res;
	for(int i=1;i<=m;i++){
		res.a[1][i]=0;
	}
	res.a[1][1]=1;
	while(b){
		if(b&1)res=res*a;
		a=a*a;
		b>>=1;
	}
	return res;
}
long long s[105],l[105],sum[105],tot;
matrix a;
matrix ans;
int main(){
	scanf("%d%lld",&m,&n);
	for(int i=1;i<=m;i++)scanf("%lld",&s[i]);
	for(int i=1;i<=m;i++){
		scanf("%lld",&l[i]);
		sum[i]=l[i]+s[i];
	}
	for(int i=1;i<=m;++i){
		for(int j=1;j<=m;j++){
			a.a[i][j]=(sum[i]*sum[j]-l[i]*l[j])%1000000007;
		}
	} 
	ans=qpow(a,n);
	for(int i=1;i<=m;i++){
		tot=(tot+ans.a[1][i])%1000000007; 
	}
	printf("%lld",tot);
	return 0;
}
```

---

## 作者：jiangjiangQwQ (赞：0)

### 思路
这题需要用到一些组合数学的知识，一天走两条道路，其中至少走一条短路，发现直接求满足题意的方案数比较难，但是**正难则反**，我们可以考虑从总方案数中减去没有走短路的方案数，发现题目给出两个要素即时间和小路，我们可以设计出下面这个转移：$f[i][j]$ 表示第 $i$ 天在第 $j$ 号小屋的方案数，初始时 $f[0][1]=1$，因为一开始自己位于 $1$ 号小屋，最后的答案即为最后一行的元素和。
### 代码
```cpp
#include<iostream>
using namespace std;
const int N=1e3+5,Mod=1e9+7;
#define int long long
int n,s[N],t[N],m;
int f[N][N];
signed main(){
    cin>>m>>n;
    for(int i=1;i<=m;i++) cin>>s[i];
    for(int i=1;i<=m;i++) cin>>t[i];
    f[0][1]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int k=1;k<=m;k++){
                f[i][j]=f[i][j]+f[i-1][k]*((s[j]+t[j])*(s[k]+t[k])-t[j]*t[k]);
                f[i][j]%=Mod;
            }
        }
    }
    int ans=0;
    for(int i=1;i<=m;i++) ans=(ans+f[n][i])%Mod;
    cout<<ans;
    return 0;
}
```

---

## 作者：Genshin_ZFYX (赞：0)

很明显的 dp。

$dp_{i,j}$ 表示第 $i$ 停在 $j$ 的方案数。

从一个点到另一个点，有三种走法：短至长，长至段，短至短。

使用三重循环，依次枚举天数、目前点、从哪个点到目前点（可以是目前点），枚举三种方法相加取模。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
long long dp[105][1005],s[1005],l[1005],ans;
signed main()
{
	cin.tie(0)->sync_with_stdio(0);
	int m,n;cin>>m>>n;
	for(int i=1;i<=m;i++)cin>>s[i];
	for(int i=1;i<=m;i++)cin>>l[i];
	dp[0][1]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=1;k<=m;k++)
			{
				dp[i][j]+=dp[i-1][k]*(s[j]*s[k])%mod;
				dp[i][j]+=dp[i-1][k]*(l[k]*s[j])%mod;
				dp[i][j]+=dp[i-1][k]*(l[j]*s[k])%mod;
				dp[i][j]%=mod;
			}
	for(int i=1;i<=m;i++)
	ans=(ans+dp[n][i])%mod;
	cout<<ans;
	return 0;
 }
```

---

## 作者：Manki23333333 (赞：0)

------------

### 思路简述

使用记忆化搜索。

令 $ dp_{i,j} $ 表示在第 $ i $ 个小屋，第 $ j $ 天时的方案数，然后依次枚举用短路和长路。

### 时间复杂度

单个 `dfs` 函数的复杂度且不计算递归的复杂度为 $ O (m) $  。

最多有 $ nm $ 个状态，也就是极端情况下 `dfs` 会被调用 $ nm $ 次。

时间复杂度 $ O (m  \times nm) = O (nm^2) $ ，可以通过本题。

### 细节

注意长路不能用两次。

还有就是要开 `long long` ，步步取模。 

### 代码

```
#include <bits/stdc++.h>
#define int unsigned long long

using namespace std;

const int mod = 1e9 + 7;

int m, n, s [105], l [105];
int dp [105] [1005]; // 在第 i 个小屋，第 j 天

int dfs (int i, int j) {
	if (dp [i] [j])
		return dp [i] [j] % mod;
		
	if (j > n)
		return 1;
	
	int sum = 0;
	
	for (int k = 1 ; k <= m ; k ++) { // 用短路
		sum += (s [i] * s [k]) % mod * dfs (k, j + 1) % mod;
		sum %= mod;
		
		sum += (s [i] * l [k]) % mod * dfs (k, j + 1) % mod;
		sum %= mod;
	}
	
	for (int k = 1 ; k <= m ; k ++) { // 用长路
		sum += (l [i] * s [k]) % mod * dfs (k, j + 1) % mod;
		sum %= mod;
	}
	
	return (dp [i] [j] = sum % mod);
}

signed main () {
	cin >> m >> n;
	
	for (int i = 1 ; i <= m ; i ++)	
		cin >> s [i];
		
	for (int i = 1 ; i <= m ; i ++)	
		cin >> l [i];

	cout << dfs (1, 1) % mod;
	
	return 0;
}
```

---

## 作者：gaomingyang101011 (赞：0)

# CF1970E1 Trails (Easy) 题解

## 思路：

首先我们都知道如果有 $A$,$B$,$C$ 三点，且 $B$ 点与 $A$ 和 $C$ 两点有若干条道路相连，那么从 $A$ 点走到 $C$ 点的方案数就是 $A$ 到 $B$ 的路径数与 $B$ 到 $C$ 的路径数相乘。

这是一道较为简单的动态规划题，我们已知在一天内可以走两条路到所有小屋中的任何一个（也包括我们开始时的小屋），并且这两条路中至少有一条是短路，也就是说，我们在一天中只算路的种类有三种走的方法，分别是短到短，短到长，长到短。

我们就可以用一个二维数组来表示在第 $i$ 天走到第 $j$ 个小屋的路径总数，最后再将在最后一天所有小屋的路径总数相加就是最终答案了。

要记得把数组开大一些，不然可能过不了。

## 代码：

```cpp
#include<iostream>
using namespace std;
const int mod=1e9+7;
long long m,n;
long long s[10001],l[10001];
// 变量名与题目说的相同 
long long dp[1001][2001];
long long ans;
int main(){
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++) scanf("%d",&s[i]);
	for(int i=1;i<=m;i++) scanf("%d",&l[i]);
	dp[0][1]=1;
	// 因为一开始在第一间小屋，所以将第一间小屋赋值为一 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int k=1;k<=m;k++){
				dp[i][j]=(dp[i][j]+dp[i-1][k]*s[j]*s[k])%mod;
				// 短到短 
				dp[i][j]=(dp[i][j]+dp[i-1][k]*s[j]*l[k])%mod;
				// 短到长 
				dp[i][j]=(dp[i][j]+dp[i-1][k]*l[j]*s[k])%mod;
				// 长到短 
			}
		}
	}
	for(int i=1;i<=m;i++) ans+=dp[n][i];
	cout<<ans%mod;
	return 0;
}
```

---

