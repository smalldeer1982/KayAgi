# Trails (Medium)

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

## 作者：Engulf (赞：4)

思路参考[官方题解](https://codeforces.com/contest/1970/attachments/download/25401/contest-41026-en-tutorial-v2.pdf)。

令 $t_i = s_i + l_i$，即联通小屋 $i$ 的总路径数。

因为至少要走一条短路，考虑容斥，从小屋 $i$ 到小屋 $j$ 的合法方案数就是总方案数减去都走长路的方案也就是 $t_it_j-l_il_j$。

考虑一个 dp，设 $f_{i, j}$ 为第 $i$ 天停留在 $j$ 的方案数。状态转移方程为

$$f_{i, j} = \sum_{k=1}^{m}f_{i - 1,k}\cdot (t_kt_j - l_kl_j)$$

可以矩阵快速幂进行优化，设

$$f_i = [f_{i, 1}, f_{i, 2} \dots f_{i, m}]$$

$$A = \begin{bmatrix}
t_1t_1-l_1l_1  & t_1t_2-l_1l_2 &  \dots  & t_1t_m-l_1l_m \\
t_2t_1-l_2l_1  &  &  &  &\\
  &  & t_it_j-l_il_j  &  & \\
  &  &  & t_mt_m-l_ml_m &
\end{bmatrix}$$

即，$A_{i,j} = t_it_j - l_il_j$。

那么，$f_0 = [1, 0, \dots 0]$，$f_n = f_0 \times A^n$，答案为 $\sum\limits_{j = 1}^n f_{n,j}$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int M = 105, mod = 1e9 + 7;

int n, m;

int s[M], l[M], t[M];

int f[M][M];

int A[M][M];

void mul(int c[][M], int a[][M], int b[][M]) {
    static int t[M][M];
    memset(t, 0, sizeof t);
    for (int k = 1; k <= m; k++)
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= m; j++)
                t[i][j] = (t[i][j] + 1ll * a[i][k] * b[k][j]) % mod;
    memcpy(c, t, sizeof t);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> m >> n;
    for (int i = 1; i <= m; i++) cin >> s[i];
    for (int i = 1; i <= m; i++) cin >> l[i], t[i] = s[i] + l[i];

    f[1][1] = 1;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++)
            A[i][j] = (1ll * t[i] * t[j] - 1ll * l[i] * l[j] + mod) % mod;

    while (n) {
        if (n & 1) mul(f, f, A);
        mul(A, A, A);
        n >>= 1;
    }

    int ans = 0;
    for (int i = 1; i <= m; i++) ans = (ans + f[1][i]) % mod;

    cout << ans << "\n";

    return 0;
}
```

---

## 作者：FFTotoro (赞：2)

[点这里前往游记。](https://www.luogu.com.cn/article/u3edqf6r)

考虑 E1 做法，此时 $n,m$ 很小，所以考虑如下简单 DP。因为一天至少要走一条短的小路，令 $f_{i,j}$ 表示在第 $i$ 天时的终点为 $j$ 的方案数，则有：

$$f_{i,j}\leftarrow f_{i,j}+f_{i-1,k}(s_js_k+s_jl_k+s_kl_j)$$

边界条件 $f_{0,1}=1$。

考虑 E2 做法，此时 $n\le 10^9$，$m$ 仍然 $\le 10^3$。发现对于每一对 $(j,k)$，转移时乘上的系数都是一定的，为 $s_js_k+s_jl_k+s_kl_j$。这是个矩阵乘法的形式，于是考虑建出转移矩阵 $A$ 满足 $a_{i,j}=s_is_j+s_il_j+s_jl_i$，使用矩阵快速幂处理出 $A^n$。根据上面 DP 的边界条件，初始时有一个序列（向量）$V=\{1,0,0,\ldots,0,0\}$，令 $R=V\times A^n$，则答案为 $\sum R_i$。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef vector<vector<int> > matrix;
const int p=1e9+7;
inline void add(int &x,int y){
  if((x+=y)>=p)x-=p;
} // 模意义下的加法，比 (x+=y)%=p 快很多
matrix operator *(matrix &a,matrix &b){
  matrix c(a.size(),vector<int>(b[0].size()));
  for(int i=0;i<a[0].size();i++)
    for(int j=0;j<a.size();j++)
      for(int k=0;k<b[0].size();k++)
        add(c[j][k],a[j][i]*b[i][k]%p);
  return c;
} // 矩阵乘法
main(){
  ios::sync_with_stdio(false);
  int m,n,c=0; cin>>m>>n;
  vector<int> s(m),l(m);
  for(auto &i:s)cin>>i;
  for(auto &i:l)cin>>i;
  matrix a(m,vector<int>(m)),b=a,w(1,vector<int>(m));
  for(int i=0;i<m;i++)
    for(int j=0;j<m;j++)
      b[i][j]=(i==j),a[i][j]=((s[i]+l[i])*s[j]%p+s[i]*l[j]%p)%p;
  w[0][0]=1;
  while(n){
    if(n&1)b=b*a;
    a=a*a,n>>=1;
  } // 进行矩阵快速幂
  w=w*b;
  for(auto i:w)for(int j:i)add(c,j); // 统计答案
  cout<<c<<endl;
  return 0;
}
```

---

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

## 作者：Daniel_yao (赞：0)

# Solve

设 $dp_{i,j}$ 表示在第 $i$ 天，最后待在了 $j$ 号房子中的总方案数。

先考虑从 $i$ 号房间走到 $j$ 号房间的方案数如何计算。不考虑限制，单次方案数为 $(s_j+l_j)\times (s_k+l_k)$，然后由于不能存在同时为长路径的情况，于是把 $(l_j \times l_k)$ 减掉即可。

枚举回合 $i$，起点 $j$，终点 $k$，于是有：

$$
dp_{i,j}=\sum\limits_{k=1}^m dp_{i-1,k} \times \max(0, (s_j+l_j)\times (s_k+l_k) - (l_j \times l_k))
$$

答案为 $\sum\limits_{i=1}^m dp_{n,i}$，记得初始化 $dp_{0,1}=1$。

考虑到 $n=10^9$，无法在 $O(nm^2)$ 的时间复杂度下通过此题。

我们令 $r_i=s_i+l_i$，则有：

$$
dp_{i,j}=\sum\limits_{k=1}^m dp_{i-1,k} \times \max(0, r_jr_k-l_jl_k)
$$

发现式子有乘，有加，于是考虑构造矩阵进行加速。

$$
\begin{bmatrix}
r_1r_1-l_1l_1&r_1r_2-l_1l_2&\cdots&r_1r_m-l_1l_m\\
r_2r_1-l_2l_1&r_2r_2-l_2l_2&\cdots&r_2r_m-l_2l_m\\
\vdots&\vdots&\ddots&\vdots\\
r_mr_1-l_ml_1&r_mr_2-l_ml_2&\cdots&r_mr_m-l_ml_m
\end{bmatrix}
$$

对此矩阵进行快速幂（迭代 $n$ 次）的结果矩阵乘上

$$
\begin{bmatrix}
dp_{1,1}\\
dp_{2,1}\\
\vdots\\
dp_{m,1}
\end{bmatrix}
$$

得到矩阵

$$
\begin{bmatrix}
dp_{1,n}\\
dp_{2,n}\\
\vdots\\
dp_{m,n}
\end{bmatrix}
$$

答案便为 $\sum\limits_{i=1}^m dp_{i,n}$，记得初始化矩阵 $dp_{1,1}=1$。

时间复杂度 $O(m^3\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long 
#define For(i,l,r) for(int i=l;i<=r;++i)
#define FOR(i,r,l) for(int i=r;i>=l;--i)
#define mod 1000000007

using namespace std;

const int MM = 105, N = 1005;

int n, m, s[MM], l[MM], ans, r[MM];

struct Matrix {
  int M[MM][MM];
  void clean() {
    For(i,1,m) For(j,1,m) M[i][j] = 0;
  }
  void init() {
    For(i,1,m) M[i][i] = 1; 
  }
  Matrix friend operator * (const Matrix a, const Matrix b) {
    Matrix Ans; Ans.clean();
    For(i,1,m) {
      For(j,1,m) {
        For(k,1,m) {
          Ans.M[i][j] = (Ans.M[i][j] + (a.M[i][k] % mod * b.M[k][j] % mod) % mod) % mod;
        }
      }
    }
    return Ans;
  }
};

Matrix qpow(Matrix a, int b) {
  Matrix Ans;
  Ans.init();
  for (; b; b >>= 1) {
    if(b & 1) Ans = Ans * a;
    a = a * a;
  }
  return Ans;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> m >> n;
  For(i,1,m) {cin >> s[i]; s[i] %= mod;}
  For(i,1,m) {cin >> l[i]; r[i] = (s[i] + l[i] % mod) % mod;}
  Matrix T, Ans;
  Ans.clean();
  Ans.M[1][1] = 1;
  For(i,1,m) {
    For(j,1,m) {
      T.M[i][j] = max(0ll, (r[i] * r[j]) - (l[i] * l[j]));
    }
  }
  Ans = qpow(T, n) * Ans;
  For(i,1,m) (ans += Ans.M[i][1]) %= mod;
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

