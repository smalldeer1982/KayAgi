# [ABC281D] Max Multiple

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc281/tasks/abc281_d

非負整数列 $ A=(a_1,a_2,\ldots,a_N) $ が与えられます。

$ A $ の(添え字が相異なる) $ K $ 個の項の和として考えられる非負整数の集合を $ S $ とします。

$ S $ に含まれる $ D $ の倍数の最大値を求めてください。ただし、$ S $ に $ D $ の倍数が含まれない場合、代わりに `-1` と出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ K\ \leq\ N\ \leq\ 100 $
- $ 1\ \leq\ D\ \leq\ 100 $
- $ 0\ \leq\ a_i\ \leq\ 10^9 $
- 入力はすべて整数
 
### Sample Explanation 1

$ A $ から $ 2 $ 個の項を選ぶ方法を列挙すると - $ a_1 $ と $ a_2 $ を選ぶ。選ばれた項の和は $ 1+2=3 $ となる。 - $ a_1 $ と $ a_3 $ を選ぶ。選ばれた項の和は $ 1+3=4 $ となる。 - $ a_1 $ と $ a_4 $ を選ぶ。選ばれた項の和は $ 1+4=5 $ となる。 - $ a_2 $ と $ a_3 $ を選ぶ。選ばれた項の和は $ 2+3=5 $ となる。 - $ a_2 $ と $ a_4 $ を選ぶ。選ばれた項の和は $ 2+4=6 $ となる。 - $ a_3 $ と $ a_4 $ を選ぶ。選ばれた項の和は $ 3+4=7 $ となる。 となり、$ S=\{3,4,5,6,7\} $ となります。$ S $ に含まれる $ 2 $ の倍数のうち最大のものは $ 6 $ なので、$ 6 $ と出力します。

### Sample Explanation 2

この例では $ S=\{1,3,5\} $ です。$ S $ に含まれる非負整数はいずれも $ 2 $ の倍数でないため、`-1` と出力します。

## 样例 #1

### 输入

```
4 2 2
1 2 3 4```

### 输出

```
6```

## 样例 #2

### 输入

```
3 1 2
1 3 5```

### 输出

```
-1```

# 题解

## 作者：_dijkstra_ (赞：18)

很套路的 DP。

## 思路

设 $dp_{i, j, r}$ 表示：前 $i$ 个数，选了 $j$ 个，当前选的数的和 $sum \bmod d = r$，此时的最大和值。

那么就有一个很显然的 DP：

$dp_{i, j, r} = \begin{cases}dp_{i - 1, j, r}\\dp_{i - 1, j - 1, (r - x) \bmod d} + x & j \ne 0\end{cases}$

写成代码就做完了，答案即为 $dp_{n, k, 0}$。

初始化 $-\infty$，如果 $dp_{n, k, 0}$ 也是一个很小的数，说明根本没有状态可以转移到答案里，输出 $-1$ 即可。

## 代码

```cpp
const int N = 105; //记得long long
ll dp[N][N][N]; //dp[i][j][r] : 前i个数，选了j个，当前%的结果为r，最大答案
void solve()
{
	memset(dp, -0x3f, sizeof dp);
	dp[0][0][0] = 0;
	int n, k, d;
	scanf("%d%d%d", &n, &k, &d);
	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		for (int j = 0; j <= k; j++)
			for (int r = 0; r < d; r++)
			{
				dp[i][j][r] = max(dp[i][j][r], dp[i - 1][j][r]);
				if (j) dp[i][j][r] = max(dp[i][j][r], dp[i - 1][j - 1][((r - x) % d + d) % d] + x);
			}
	}
	if (dp[n][k][0] < 0) puts("-1"); else cout << dp[n][k][0] << '\n';
}
```

---

## 作者：Neil_Qian (赞：5)

# [ABC281D] Max Multiple 题解

给你 $N$ 个数 $a_i$，选出 $K$ 个数，使得它们的和是 $D$ 的倍数且最大。

显然，它**不能用贪心**，因为选最大的有可能不是 $D$ 的倍数。我们应该考虑**动态规划**。

先思考状态。首先有一维表示考虑到了第 $i$ 个数，其次有一维表示选了 $j$ 个数。本题还要考虑余数，因此最后一维是它的和对 $D$ 取模的值为 $l$，$dp_{i,j,l}$ 表示上述状态的和的最大值。

再思考转移。我们考虑到了第 $i$ 个数，这个数为 $a_i$，分两种情况：

- 不选 $a_i$，则可以从 $dp_{i-1,j,l}$ 转移而来。
- 选择 $a_i$，则可以从 $dp_{i-1,j-1,(l-a_i+D\times inf)\mod d}$ 转移而来。

重点解释一下第二个。现在我们的和为 $l$，原来的和设为 $x$，则满足 $(x+a_i)\mod D=l$，因为 $a_i$ 过大，所以要加上很多倍的 $D$ 使得它不会变成负数。以上，我们的到了动态规划的全过程，答案即为 $dp_{n,k,0}$。枚举状态是三重循环，一个 $N$，一个 $K$，一个 $D$，转移是常数级别，时间复杂度是 $O(N\times K\times D)$，可以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;typedef long long ll;//注意long long。
#define _for(i,a,b) for(ll i=(a);i<=(ll)(b);i++)
ll n,k,d,a[102],dp[102][102][102];//也可以用滚动数组优化一维，但本题没有必要。
int main(){
	scanf("%lld%lld%lld",&n,&k,&d);
	for(ll i=1;i<=n;i++)scanf("%lld",&a[i]);
	memset(dp,-0x3f,sizeof(dp)),dp[0][0][0]=0;//初始化。
	_for(i,1,n)_for(j,0,min(j,k))_for(l,0,d-1){
		ll& w=dp[i][j][l];//这里是把dp[i][j][l]替换成w，可以减少代码量，w变化dp[i][j][l]也会变化。
		if(j>0)w=max(dp[i-1][j-1][(ll)(l-a[i]+d*1e12)%d]+a[i],w);//要选的话。
		w=max(w,dp[i-1][j][l]);//不选的话。
	}
	return printf("%lld\n",dp[n][k][0]>=0?dp[n][k][0]:-1),0;//如果和大于等于0的话有解，否则无解。
}
```


---

## 作者：Composite_Function (赞：4)

# 翻译

给出 $A$ 为 $(a_1, a_2, ...a_n)$。求其中 $K$ 个数的且能被 $D$ 整除的最大和。

------------

# 思路

裸 DP。

状态：$dp[i][j][k]$ 表示到 $i$，选出 $j$ 个数，余数为 $k$。

转换方程：$dp[i + 1][j + 1][(l + a[i + 1]) \mod d] = max(dp[i + 1][j + 1][(l + a[i + 1]) \mod d], max(dp[i][j][l] + a[i + 1], dp[i][j + 1][(l + a[i + 1]) \mod d]))$

初始值：$\forall i = 0, 1, ..., n, dp[i][0][0] = 0$

------------

# 代码

```cpp
# include <bits/stdc++.h>
using namespace std;
# define int long long
const int N = 110;
int n, k, d, a[N], dp[N][N][N];
signed main()
{
	cin >> n >> k >> d;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	memset(dp, 0x80, sizeof(dp));
	for (int i = 0; i <= n; ++i)
		dp[i][0][0] = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < k; ++j)
			for (int l = 0; l < d; ++l)
				dp[i + 1][j + 1][(l + a[i + 1]) % d] = max(dp[i + 1][j + 1][(l + a[i + 1]) % d], max(dp[i][j][l] + a[i + 1], dp[i][j + 1][(l + a[i + 1]) % d]));
	cout << (dp[n][k][0] <= -1e9? -1 : dp[n][k][0]) << endl;
	return 0;
}
```

---

## 作者：sunzz3183 (赞：1)

# [ABC281D] Max Multiple

## 题意

给定一个长度为 $n$ 的序列 $a$，求一个最大的长度为 $k$ 的子序列和 $sum$，满足 $d|sum$。

## 分析

这是一道 DP 题。

我们设 $f_{i,j,l}$ 为前 $i$ 个数，选了 $j$ 个数，对 $d$ 取余后的结果为 $l$ 的最大 $sum$（注意 $j\leq \min(i,k)$）。

那 $f_{i,j,l}$ 可以转移到 $f_{i+1,j,l}$ 和 $f_{i+1,j+1,(l+a_{i+1})\bmod d}$。

所以，状态转移方程为 $f_{i+1,j,l}=\max(f_{i+1,j,l},f_{i,j,l}),f_{i+1,j+1,(l+a_{i+1})\bmod d}=\max(f_{i+1,j+1,(l+a_{i+1})\bmod d},f_{i,j,l}+a_{i+1})$。

但由于某些情况是无法得到的，所以都初始化为 $-1$，只有 $f_{0,0,0}=0$。

每次转移时，当 $f_{i,j,l}\neq -1$ 时才能转移。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||'9'<c){if(c=='-')f=-1;c=getchar();}
    while('0'<=c&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
    return x*f;
}
const int N=105;
int n,k,d,a[N],f[N][N][N];
signed main(){
    n=read();k=read();d=read();
    memset(f,-1,sizeof(f));
    for(int i=1;i<=n;i++)a[i]=read();
    f[0][0][0]=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<=min(i,k);j++)
            for(int l=0;l<d;l++)
                if(f[i][j][l]>=0)
                    f[i+1][j][l]=max(f[i+1][j][l],f[i][j][l]),
                    f[i+1][j+1][(l+a[i+1])%d]=max(f[i+1][j+1][(l+a[i+1])%d],f[i][j][l]+a[i+1]);
    printf("%lld",f[n][k][0]);
    return 0;
}
```


---

## 作者：Cczzyy20150005 (赞：1)

## 题意
有 $n$ 个数，选其中的 $K$ 个数，要求它们的和为 $d$ 的倍数，现在求满足这个条件的和的最大值。
## 思路
贪心显然不行。考虑 $dp$。

设状态为 $dp[i][j][k]$，表示前 $i$ 个数选 $j$ 个数，被 $d$ 除余数为 $k$ 时最大是 $d$ 的多少倍。 

那么我们可以类似背包那样转移，所以转移方程就是：
1. 当 $ dp[i-1][j-1][(k-a[i] \bmod d+d)\bmod d] \neq -1$ 时，$dp[i][j][k]=\max(dp[i-1][j][k],dp[i-1][j-1][(k-a[i] \bmod d+d)\bmod d]+\lfloor a[i]\div d \rfloor+(k<a[i]\bmod d?1:0)$。
2. 否则，$dp[i][j][k]=dp[i-1][j][k]$。

所以答案就是 $dp[n][K][0] \times d$。

由于这是背包，那么我们可以省去 $i$ 这一维，然后再将 $j$ 倒序枚举就可以了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define FS(a) fixed<<setprecision(a)
#define endl "\n"
long long dp[101][101],a[101];
int n,d,k;
int main(){
	IOS;
	cin>>n>>k>>d;
	for(int i=1;i<=n;i++)cin>>a[i];
	memset(dp,-1,sizeof(dp));//初始化全为-1，因为要判无解
	dp[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=k;j>=1;j--){//倒序枚举，省去一维
			for(int p=0;p<d;p++){
				if(dp[j-1][(p-a[i]%d+d)%d]!=-1)
				dp[j][p]=max(dp[j][p],dp[j-1][(p-a[i]%d+d)%d]+a[i]/d+(p<a[i]%d?1:0));//解释一下转移方程的最后一段：如果p<a[i]%d，说明它在之前选的数的和上又多了一倍，所以要加1
			}
		}
	}
	cout<<(dp[k][0]==-1ll?-1:dp[k][0]*d);//判无解
	return 0;
}

```

---

## 作者：_zhy (赞：0)

[Link](https://www.luogu.com.cn/problem/AT_abc281_d)。

这道题是一道较基础的动态规划。

我们定义 $f[i][j][k]$ 表示前 $i$ 个数中（包含第 $i$ 个数），选 $j$ 个数，余数为 $k$ 的最佳答案。

那我们改怎样进行转移呢？只需枚举 $i$ 的前一个数即可。

假设 $i$ 的前一个数为 $l$，那么$f[i][j][k] = max(f[i][j][k], f[l][j - 1][(k - a[i] + d) \% d])$，注意 $k - a[i]$ 可能小于 $0$，所以要加一个 $d$ 再模 $d$。

同时我们要保证每一个转移都存在，也就是说你转移 $f[i][j][k]$ 时要保证前 $i$ 个数选 $j$ 个余数为 $k$ 存在，也就要保证 $f[l][j - 1][(k - a[i] + d) \% d]$ 合法，所以我们再开一个数组 $ff[i][j][k]$，表示前 $i$ 个数选 $j$ 个余数为 $k$ 是否存在。如果存在才可以转移。

初始化很明显就是 $ff[0][0][0] = ff[i][1][a[i]] = f[i][0][0] = 1$。

### code

```cpp
#include <cstdio>
#include <iostream>
#define LL long long

using namespace std;

const int N = 105;

LL n, K, d, a[N], b[N], f[N][N][N], ans;
bool ff[N][N][N], flag;

signed main() {
	scanf("%lld %lld %lld", &n, &K, &d);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]), b[i] = a[i] % d, ff[i][0][0] = true, ff[i][1][b[i]] = true; //a[i]用来计算答案，b[i]用来在dp中算余数，因为b[i]模了d。 
	ff[0][0][0] = true;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= i && j <= K; j++)
			for (int k = 0; k < d; k++)
				for (int l = j - 1; l < i; l++)
					if (ff[l][j - 1][(k - b[i] + d) % d]) {
						ff[i][j][k] = true;
						f[i][j][k] = max(f[i][j][k], f[l][j - 1][(k - b[i] + d) % d] + a[i]);	//按刚才的状态转移方程转移即可。 
						if (!k && j == K)	//如果k==0说明渠道这些数是d的倍数，若又刚好取了k个数说明有答案。 
							flag = true;
					}
	if (!flag) {
		puts("-1");
		return 0;
	}
	for (int i = K; i <= n; i++)
		ans = max(ans, f[i][K][0]);
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：MoyunAllgorithm (赞：0)

一个较简单的 dp 题 ^_^

**题意**

给你 $N$ 个**非负整数**的集合。从这些数中选择任意恰好 $K$ 个相加可以得到一个和。所有这些和构成的集合中，最大的 $D$ 的倍数是什么？

$N,K,D \le 100$。从我打比赛时的经历看，本题似乎是把 $0$ 视为所有数的倍数的。

**分析**

首先可以显而易见的发现，我们不可能把所有的和都求出来，那太多了。对于“想找到某些最值且不遍历所有值”的问题，可以尝试**dp**求解。而且应该是一个 $O(N^3)$ 的dp。

一个dp分三步：一设计状态，二确认答案如何用 $dp$ 数组表示，三推导转移。

因为是 $O(N^3)$ 的dp，所以在设计状态时先考虑三维。故先想到

$dp_{i,j,k}$ 代表前 $i$ 个数，选 $j$ 个，且目前的结果 $ \equiv k \pmod{D}$ 的最大值。

答案可以表示为 $dp_{N,K,0}$。

转移方程非常好想：从左到右扫这个集合 $a$。 对于 $a_i$，我们遍历所有的 $j \in [0,K-1]$ 和 $k \in [0,D-1]$。之后我们分别把这些状态加上 $a_i$ 就行。但写到这里会发现，$dp$ 数组的第一维是没用的！所以调整一下 $dp$ 数组的状态：

$dp_{j,k}$ 表示目前选了 ${j}$ 个数，目前的和 $ \equiv k \pmod{D}$ 的最大值。

那么在转移时，遍历每个 $j$ 和 $k$，

$dp_{j+1,((k+a_i) \mod D)} = \max ( dp_{j,k}+a_i,dp_{j+1,((k+a_i) \mod D)})$

为了避免重复赋值，采用了新增一维 $0/1$ 的滚动数组。

**AC CODE**
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=105;
long long dp[2][MAXN][MAXN];
int a[MAXN];
int N,K,D;
int main()
{
	scanf("%d %d %d",&N,&K,&D);
	for(int i=1;i<=N;i++) scanf("%d",&a[i]);
	memset(dp,-1,sizeof(dp));//由于0是有效结果，所以初始值应为-1。
	dp[1][1][a[1]%D]=a[1];
	dp[1][0][0]=0;
	for(int i=2;i<=N;i++)
	{
		for(int j=0;j<=K;j++)
		{
			for(int k=0;k<D;k++)
			{
				int rest=a[i]%D;
				if(dp[1][j][k]!=-1) 
				{
					dp[0][j+1][(k+rest)%D]=max(dp[0][j+1][(k+rest)%D],dp[1][j][k]+a[i]);
				}
			}
		}
		for(int k=0;k<=K;k++)
		for(int j=0;j<D;j++)
		dp[1][k][j]=max(dp[1][k][j],dp[0][k][j]);
        //滚动数组处理
 	}
	printf("%lld\n",dp[1][K][0]);
	return 0;
}
```






---

## 作者：c20231020 (赞：0)

### 题目链接
[luogu](https://www.luogu.com.cn/problem/AT_abc281_d)

[atcoder](https://atcoder.jp/contests/abc281/tasks/abc281_d)

### 题目大意

给出一个非负整数序列 $A=(a_1,a_2,\ldots,a_N)$。

$S$ 是一个非负整数集合，表示 $A$ 中任意选择 $K$ 个数的和（有不同的下标）。

求 $S$ 中最大的数满足是 $D$ 的倍数。如果 $S$ 中没有 $D$ 的倍数，则输出 `-1`。

题面不好理解，把样例解释放上来：
> 列举如何从 $A$ 中选择 $2$ 项。

> - 选择 $a_1$ 和 $a_2$。 所选项之和为 $1+2=3$。
> - 选择 $a_1$ 和 $a_3$。 所选项之和为 $1+3=4$。
> - 选择 $a_1$ 和 $a_4$。 所选项之和为 $1+4=5$。
> - 选择 $a_2$ 和 $a_3$。 所选项之和为 $2+3=5$。
> - 选择 $a_2$ 和 $a_4$。 所选项之和为 $2+4=6$。
> - 选择 $a_3$ 和 $a_4$。 所选项之和为 $3+4=7$。
>
> 所以 $S={3,4,5,6,7}$。$S$ 中 $2$ 的最大倍数是 $6$，所以输出 $6$。

- $ 1 \leq K \leq N \leq 100 $
- $ 1 \leq D \leq 100 $
- $ 0 \leq a_i \leq 10^9 $

### 思路

设 $dp_{i,j,k}$ 表示当前状态在第 $i$ 个数，选了 $j$ 个数，当前模 $D$ 结果为 $k$ 的最大值。

dp 方程很好推：

$$
dp_{i,j,k}=\max(dp_{i-1,j,k},dp_{i-1,j-1,(k-a_i) \mod D}+a_i)
$$

其中，前半部分代表不选第 $i$ 个数，后半部分代表选第 $i$ 个数。

最终状态就是 $dp_{n,k,0}$。

注意 $(k-a_i) \mod D$ 的负数问题。

#### code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll dp[110][110][110];//选择的数之和可能超过 int 范围
int k,n,d,a[110];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>k>>d;
	for(int i=1;i<=n;++i)cin>>a[i];
	memset(dp,-0x3f,sizeof(dp));
	dp[0][0][0]=0;
	for(int i=1;i<=n;++i){
		dp[i][0][0]=0;//初始化边界条件
		for(int j=1;j<=min(i,k);++j){
			for(int l=0;l<d;++l){
				dp[i][j][l]=max(dp[i-1][j][l],dp[i-1][j-1][(l-a[i]%d+d)%d]+a[i]);//避免 mod D 出现负数
			}
		}
	}
	if(dp[n][k][0]<0)cout<<-1;//判断无解
	else cout<<dp[n][k][0]<<'\n';
	return 0;
}
```

---

## 作者：Pethly_Cat (赞：0)

题意简述：给定 $N$ 个数，在其中选出 $K$ 个，使得选出的数之和能被 $D$ 整除且尽可能大，输出这个最大值。若无解，输出 ```-1``` 。

线性 dp 。

定义 $f_{i,j,k}$ 表示在前 $i$ 个数中选了 $j$ 个，这些数之和 $\text{mod}\space d=k$ 情况下的最大值。

若已知 $f_{i,j,k}$ ，显然分为两种情况：

- 第 $i+1$ 个数不选：$f_{i+1,j,k}=\text{max}\{f_{i,j,k}\}$

- 第 $i+1$ 个数选：$f_{i+1,j+1,(k+a_{i+1})\space\text{mod}\space d}=\text{max}\{f_{i,j,k}+a_{i+1}\}$

时间复杂度 $O(n^3)$ 。( $n,k,d$ 同阶 )

#### Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k,d,a[105],f[105][105][105];
signed main(){
	cin>>n>>k>>d;
	memset(f,-1,sizeof(f));
	for(int i=1;i<=n;i++)
		cin>>a[i];
	f[0][0][0]=0;
	for(int i=0;i<=n;i++)
		for(int j=0;j<=k;j++)
			for(int p=0;p<d;p++){
				if(f[i][j][p]==-1) continue;//去除不可行的情况
				f[i+1][j+1][(p+a[i+1])%d]=max(f[i+1][j+1][(p+a[i+1])%d],f[i][j][p]+a[i+1]);
				f[i+1][j][p]=max(f[i+1][j][p],f[i][j][p]);
			}
	cout<<f[n][k][0];
	return 0;
}
```


---

