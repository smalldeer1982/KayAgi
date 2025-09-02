# [ABC253E] Distance Sequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc253/tasks/abc253_e

長さ $ N $ の整数からなる数列 $ A=(A_1,\ldots,A_N) $ であって、以下の条件を全て満たすものは何通りありますか？

- $ 1\le\ A_i\ \le\ M $ $ (1\ \le\ i\ \le\ N) $
- $ |A_i\ -\ A_{i+1}|\ \geq\ K $ $ (1\ \le\ i\ \le\ N\ -\ 1) $

ただし、答えは非常に大きくなることがあるので、答えを $ 998244353 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 1000 $
- $ 1\ \leq\ M\ \leq\ 5000 $
- $ 0\ \leq\ K\ \leq\ M-1 $
- 入力は全て整数

### Sample Explanation 1

条件を満たす数列は以下の $ 6 $ つです。 - $ (1,2) $ - $ (1,3) $ - $ (2,1) $ - $ (2,3) $ - $ (3,1) $ - $ (3,2) $

### Sample Explanation 2

条件を満たす数列は以下の $ 2 $ つです。 - $ (1,3,1) $ - $ (3,1,3) $

### Sample Explanation 3

答えを $ 998244353 $ で割った余りを出力してください。

## 样例 #1

### 输入

```
2 3 1```

### 输出

```
6```

## 样例 #2

### 输入

```
3 3 2```

### 输出

```
2```

## 样例 #3

### 输入

```
100 1000 500```

### 输出

```
657064711```

# 题解

## 作者：Hog_Dawa_IOI (赞：3)

应该是第一道校内模拟赛时切掉的 dp 题，为自己感到自豪。   
我们设 $f_{i,j}$ 表示长度为 $i$，最后一个数为 $j$ 的序列的数量，则     
$f_{i,j}=(\sum_{s=1}^{j-m} f_{i-1,s})+(\sum_{s=j+m}^{m} f_{i-1,s})$。   

但是这样的话时间复杂度为 $O(nm^2)$，无法通过此题。    
留意到两部分所求和的区间是连续的，我们可以使用前缀和优化。    
设 $qz_{i,j}=\sum_{s=1}^j f_{i,s}$，则
$$f_{i,j}=qz_{i-1,j-k}\times(j-k>=1)$$
$$+(qz_{i-1,m}-qz_{i-1,j+k-1})\times(j+k<=m)$$
$$-f_{i-1,j}\times(k=0).$$
式子有点长，结合上面的铺垫理解理解。此处括号内的表达式取值为 $1$ 或 $0$，具体取值取决于表达式的真假，如果是真则为 $1$，否则为 $0$。  
至于为什么 $k=0$ 的时候要减去 $f_{i-1,j}$ 是因为前面两种情况都算了一遍 $f_{i-1,j}$，多算了一次。    
在求 $f_{i,j}$ 的时候，$qz_{i,j}$ 也可以顺便更新。   
于是这道题就以 $O(nm)$ 的时间复杂度做完啦！    
提醒各位取模的时候要记得先加上 $998244353$ 再取模，为了避免负数的出现。   
代码：    
```cpp
#include<stdio.h>
int n,m,k;long long f[1005][5005],qz[1005][5005];
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;i++) f[1][i]=1,qz[1][i]=qz[1][i-1]+1;//初始化
    for(int i=2;i<=n;i++) for(int j=1;j<=m;j++)
    {
        if(j-k>=1) f[i][j]=(f[i][j]+qz[i-1][j-k])%998244353;
        if(j+k<=m) f[i][j]=(f[i][j]+qz[i-1][m]-qz[i-1][j+k-1]+998244353)%998244353;
        if(k==0) f[i][j]=(f[i][j]-f[i-1][j]+998244353)%998244353;
        qz[i][j]=(qz[i][j-1]+f[i][j])%998244353;
    }
    printf("%lld",qz[n][m]%998244353);//这里一次性算出了从1~m的结果之和，因为最后的数从1~m都有可能，而长度必须是n
}
```

---

## 作者：DengDuck (赞：3)

我们设 $f_{i,j}$ 表示第 $i$ 数字为 $j$ 的方案数。

则显然有状态转移方程：

$$
f_{i,j}=\sum_{k\leq |l-j|,1\leq l \leq m} f_{i-1,l}
$$

理性分析，其时间复杂度为 $O(n^3)$，需要优化。

不难发现我们可以看作是先取 $\sum\limits_{j=1}^mf_{i-1,j}$，然后在中间选一些数不取。

而这些不取的数字是连续的，所以我们有前缀和优化 DP 就可以解决问题，时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL mod=998244353;
const LL N=1005,M=5005;
LL n,m,k,f[N][M],sum[N][M],ans;
int main()
{
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=1;i<=m;i++)f[1][i]=1,sum[1][i]=(sum[1][i-1]+1)%mod;
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			LL l=max(1ll,j-k+1),r=min(j+k-1,m);
			LL t=sum[i-1][r]-sum[i-1][l-1];
			if(l>r)t=0;
			f[i][j]=((sum[i-1][m]-t)%mod+mod)%mod;
			sum[i][j]=(sum[i][j-1]+f[i][j])%mod;
		}
	}
	for(int i=1;i<=m;i++)ans=(ans+f[n][i])%mod;
	printf("%lld",ans);
}

```

---

## 作者：Gaode_Sean (赞：2)

这是一道 dp $+$ 前缀和 题。

考虑 dp，设 $f_{i,j}$ 表示长度为 $i$ 且以 $j$ 结尾的合法序列数。

不难推出转移方程：$f_{i,j}=\sum_{l=1}^{j-k} f_{i-1,l}+ \sum_{l=j+k}^m f_{i-1,l}$。这个算法的复杂度是 $\mathcal O(n^2m)$ 的，无法通过本题。

可以用前缀和优化。注意到第一维中的 $i$ 只会由 $i-1$ 转移而来，因此可以做一个前缀和 $s_j=\sum_{l=1}^j f_{i,l}$ 。这样就能 $\mathcal{O}(1)$ 计算 $f_{i,j}$。

经过优化后的算法复杂度是 $\mathcal{O}(nm)$ 的。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005,M=5005;
typedef long long ll;
ll mod=998244353,f[N][M],ans,sum[M];
int n,m,s;
int main()
{
	scanf("%d%d%d",&n,&m,&s);
	for(int i=1;i<=m;i++) f[1][i]=1,sum[i]=i;
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(!s){f[i][j]=(f[i][j]+sum[m])%mod;continue;}
			if(j-s>=1) f[i][j]=(f[i][j]+sum[j-s])%mod;
			if(j+s<=m) f[i][j]=(f[i][j]+sum[m]-sum[j+s-1]+mod)%mod;
		}
		for(int j=1;j<=m;j++) sum[j]=(sum[j-1]+f[i][j])%mod;
	}
	for(int i=1;i<=m;i++) ans=(ans+f[n][i])%mod;
    printf("%lld",ans);
	return 0;
}
```

---

## 作者：Fkxxx (赞：1)

### 题意

构造长为 $n$ 的数列 $a$，要求 $a_i\leq m$ 并且 $|a_i-a_{i-1}|\leq k$，求方案数。

### 题解

对于这种方案数的序列问题，我们很容易就能想到计数 dp。

接下来，我们来讨论 dp 的状态。

首先，基本的第一层状态，表示长度为多少时的方案数，也就是步数。

接下来，为了区分不同方案最后一位以便确定下一位的添加区间，我们开第二层状态，表示结尾数字。

有了这些，整理一下，结果如下：

$f_{i,j}$：长度为 $i$，以 $j$ 结尾的合法区间方案数。

显然的，转移方程如下：

$$f_{i,j}\to \sum_{v=1}^{m}f_{i-1,v}-\sum_{v=-k}^{k-1}f_{i-1,j+v}$$

这样就能 $O(n^3)$ 解决这个问题。

但是显然 $O(n^3)$ 还不够，需要继续优化。

再看转移方程……求和！是区间求和！我们用简单的前缀和就可以轻松把区间求和转化为 $O(1)$ 操作。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 998244353 ;
int n , m , k , f[1005][5005] , sum[1005][5005] ;
signed main(){
    cin >> n >> m >> k ;
    for( int i = 1 ; i <= m ; i ++ ) sum[1][i] = i ;
    for( int i = 2 ; i <= n ; i ++ ){
        for( int j = 1 ; j <= m ; j ++ ){
            if( j - k >= 1 ) f[i][j] = sum[i - 1][j - k] ;
            if( j + k <= m ) f[i][j] = ( f[i][j] + sum[i - 1][m] - sum[i - 1][j + k - 1] + MOD ) % MOD ;
            if( k == 0 ) f[i][j] = sum[i - 1][m] ;
            sum[i][j] = ( sum[i][j - 1] + f[i][j] ) % MOD ;
        }
    }
    cout << sum[n][m] ;
    return 0 ;
}
```

---

## 作者：Mingrui_Yang (赞：1)

[luogu 传送门](https://www.luogu.com.cn/problem/AT_abc253_e)

考虑 DP。

令 $f_{i, j}$ 为表示长度为 $i$ 且以 $j$ 结尾的合法序列数。  
状态转移方程就很显然了。
$$
f_{i, j} = \sum_{l = 1}^{j - k}f_{i - 1, l} + \sum_{l = j + k}^{m}f_{i - 1, l}
$$
如果 $k = 0$ 只用加一次。

时间复杂度 $\mathcal{O}(n^3)$，考虑优化。   

考虑使用前缀和，我们发现 $f_{i,j}$ 仅由 $f_{i - 1, l}$ 转移。  
可维护一个前缀和 $s_i$ 表示上一次转移的前缀和，每一转移更新即可。

## CODE

```cpp
#include <bits/stdc++.h>

#define int long long 

using namespace std;

const int N = 1005, M = 5005;
const int Mod = 998244353;

int n, m, k;
int f[N][M], sum[M];   // 表示长度为 i 且以 j 结尾的合法序列数

signed main()
{
	cin >> n >> m >> k;
	for(int i = 1; i <= m; i ++ )
		f[1][i] = 1, sum[i] = i;
	
	for (int i = 2; i <= n; i ++ )
	{
		for (int j = 1; j <= m; j ++ )
		{
			if (k == 0) // 注意特判
			{
				f[i][j] = (f[i][j] + sum[m]) % Mod;
				continue;
			}
			
			if (j - k >= 1)
				f[i][j] = (f[i][j] + sum[j - k]) % Mod;
			if (j + k <= m)
				f[i][j] = (f[i][j] + sum[m] - sum[j + k - 1] + Mod) % Mod;
		}
		for(int j = 1; j <= m; j ++ )
			sum[j] = (sum[j - 1] + f[i][j]) % Mod;
	}
	
	int ans = 0;
	for(int i = 1; i <= m; i ++ )
		ans = (ans + f[n][i]) % Mod;
    cout << ans << endl;
    
	return 0;
}
```

---

## 作者：max666dong123 (赞：1)

## 思路

这是一道``DP``与前缀和的题，我们用背包来分析，很容易推出状态转移方程：

$$f_{i,j}=\sum^{j-k}_{k=1}f_{i-1,k}+\sum^{m}_{k=j+k}f_{i-1,k}$$ 

但枚举 $i,j,k$ 是 $O(n^3)$ 的时间复杂度，明显过不了。我们看到求和就可以想到前缀和，但用前缀和要特判边界。
答案也很容易推出为 $\sum_{i=1}^{m} f_{n,i}$。

改了之后，会发现卡在第 $18$ 个点上，我们测试这组数据就可以发现问题：
```
2 5 0
```
输出是 $6$，手算算出答案应该是 $4$，特判 $k=0$ 输出 $m^n$ 就可以了！

## AC代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
const int N=5e3+10;
const int MOD=998244353;
int n,m,k;
int f[N][N];
int s[N];
int qpow(int a,int b){//快速幂
	if(b==1)return a;
	if(b==0)return 1;
	int sum=qpow(a,b/2);
	sum%=MOD;
	sum*=sum;
	sum%=MOD;
	if(b&1){
		sum*=a;
		sum%=MOD;
	}
	return sum;
}
signed main(){
	IOS;
	cin>>n>>m>>k;
	if(k==0){//特判
		cout<<qpow(m,n);return 0;
	}
	s[0]=0;
	for(int i=1;i<=m;i++){
		f[1][i]=1;
		s[i]=s[i-1]+1;
		s[i]%=MOD;
//		cout<<s[i]<<endl;
	}
	for(int i=2;i<=n;i++){
		for(int j=1;j<=m;j++){
//			for(int l=1;l<=j-k;l++){
//				f[i][j]+=f[i-1][l];
//				
//			}
			if(j-k>=1){
				f[i][j]+=s[j-k];
				f[i][j]%=MOD;			
			}
//			cout<<f[i][j]<<endl;
//			for(int l=j+k;l<=m;l++){
//				f[i][j]+=f[i-1][l];
//				
//			}	
			if(j+k<=m){
				f[i][j]=(((f[i][j]+s[m])%MOD)-s[j+k-1])%MOD;
				f[i][j]%=MOD;	
			}
			f[i][j]%=MOD;
			
//			cout<<f[i][j]<<endl;
		}
		s[0]=0;//初始化
		for(int j=1;j<=m;j++){
			s[j]=s[j-1]+f[i][j];//更新前缀和
			s[j]%=MOD;
//			cout<<s[j]<<" ";
		}
//		cout<<endl;
	}
	int sum=s[m]%MOD;//答案是1~m的和
//	for(int i=1;i<=m;i++){
//		sum+=f[n][i];
//		sum%=MOD;
//	}
	cout<<(sum+MOD)%MOD<<endl;
	return 0;
}

```

---

## 作者：WaterSun (赞：1)

# 思路

我们定义 $dp_{i,j}$ 表示当前填到第 $i$ 个位置，且第 $i$ 个位置填 $j$ 的方案数。

那么，我们能得出如下的状态转移方程：

$$dp_{i,j} = \sum_{|a - j| \geq k}{dp_{i - 1,a}}$$

即：

$$dp_{i, j} = \sum_{a = 1}^{j - k}dp_{i - 1,a} + \sum_{a = j + k}^{m}dp_{i - 1,a}$$

需要注意的是 $k = 0$ 的时候，需要减去 $dp_{i - 1,j}$。

考虑正常写法，时间复杂度 $\Theta(nm^2)$。[Link](https://www.luogu.com.cn/paste/7ihd2scs)

于是利用前缀和优化，时间复杂度 $\Theta(nm)$。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 5010,mod = 998244353;
int n,m,k;
int sp[N],sn[N],dp[N];

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

signed main(){
	n = read();
	m = read();
	k = read();
	for (re int i = 1;i <= m;i++){
		sp[i] = i;
		sn[i] = m - i + 1;
	}
	for (re int i = 2;i <= n;i++){
		for (re int j = 1;j <= m;j++){
			dp[j] = 0;
			if (!k){
				dp[j] = sp[m];
				continue;
			}
			if (j + k <= m) dp[j] = (dp[j] + sn[j + k]) % mod;
			if (j - k >= 1) dp[j] = (dp[j] + sp[j - k]) % mod;
		}
		for (re int j = 1;j <= m;j++) sp[j] = (sp[j - 1] + dp[j]) % mod;
		for (re int j = m;j;j--) sn[j] = (sn[j + 1] + dp[j]) % mod;
	}
	printf("%lld",sp[m]);
	return 0;
}
```

---

## 作者：wnsyou (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc253_e)

简单的动态规划题。

绝对详细！

## 题意

给定三个整数 $n$、$m$ 和 $k$，求有多少个序列满足以下条件：

- 对于 $1 \leqslant i \leqslant n$，$1 \leqslant a_i \leqslant m$。
- 对于 $1 < i \leqslant n$，$\left\vert a_i - a_{i - 1} \right\vert \geqslant k$。

**答案对 $998244353$ 取模。**

## 思路

求方案数？首先考虑用动态规划。

- 状态：$dp_{i,j}$ 表示考虑前 $i$ 个数，且第 $i$ 个数为 $j$ 的方案数。
- 转移：
  - 如果 $k \neq 0$，则 $dp_{i,j} = (\sum\limits_{1 \leqslant l \leqslant j - k} dp_{i - 1,l} + \sum\limits_{j + k \leqslant l \leqslant m} dp_{i - 1,l})$。
  - 如果 $k = 0$，则 $dp_{i,j} = \sum\limits_{1 \leqslant l \leqslant m} dp_{i-1,l}$。
- 初始状态：对于 $1 \leqslant i \leqslant m$，$dp_{1,i}=1$。
- 目标状态：$\sum\limits_{1 \leqslant i \leqslant m} dp_{n,i}$。

我们可以敲出一个暴力，时间复杂度：$O(n ^ 2 \times m)$，[点这里](https://atcoder.jp/contests/abc253/submissions/40885423)，可以发现只能过一半的测试点。

这时，我们发现：转移是一段区间的和！考虑前、后缀和优化，将转移优化至 $O(1)$。

由于有了前后缀和，我们就可以省略掉 $i$ 这个维度，**记得取模**。

### 时空复杂度

- 时间复杂度：$O(n \times m)$。
- 空间复杂度：$O(m)$。

## 代码

```cpp
#include <iostream>

using namespace std;
using ll = long long;

const int mod = 998244353;

ll dp[5010], sum[5010], num[5010]; // 我为了防止爆 int，开了 long long
int n, m, k;

int main () {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m >> k;
  for (int i = 1; i <= m; i++) { // 初始状态
    sum[i] = sum[i - 1] + 1;
  }
  for (int i = m; i; i--) {
    num[i] = num[i + 1] + 1;
  }
  for (int i = 2; i <= n; i++) { // 枚举处理前几个，第 1 个已经处理了
    for (int j = 1; j <= m; j++) { // 枚举当前位置上的数值
      if (k == 0) { // 分类讨论，因为当 k = 0 时上一位数值为 j 的方案数会算两次
        dp[j] = sum[m];
      } else {
        dp[j] = 0;
        if (j > k) { // 确保下标不越界
          dp[j] = sum[j - k]; // 前缀
        }
        if (j + k <= m) {
          dp[j] = (dp[j] + num[j + k]) % mod; // 后缀
        }
      }
    }
    for (int j = 1; j <= m; j++) { // 更新前缀和
      sum[j] = (sum[j - 1] + dp[j]) % mod;
    }
    for (int j = m; j; j--) { // 更新后缀和
      num[j] = (num[j + 1] + dp[j]) % mod;
    }
  }
  cout << sum[m]; // 偷懒，sum[m] = dp[1] + dp[2] + ... + dp[m]，不用再算一遍，同理 num[1] 也可以
  return 0;
}
```



---

## 作者：Tsawke (赞：1)

# [[ABC253E] Distance Sequence](https://www.luogu.com.cn/problem/AT_abc253_e) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC253E)

## 题面

给定 $ n, m, k $，求有多少序列 $ a_n $，满足：

* $ 1 \le a_i \le m (1 \le i \le m) $。
* $ \lvert a_i - a_{i + 1} \rvert \ge k (1 \le i \le n - 1) $。

## Solution

一看题意和数据范围，DP 显然，不难想到设状态 $ dp(i, j) $ 为长度为 $ i $ 的以 $ j $ 为结尾的合法序列的方案数。也不难想到一个 $ \texttt{2D1D} $ 的转移，即：
$$
dp(i, j) = \sum_{k = j + k}^{m}dp(i - 1, k) + \sum_{k = 1}^{j - k}dp(i - 1, k)
$$
同时注意转移前需要判断是否满足 $ j + k \le m $ 和 $ j - k \ge 1 $。然后这个式子也很显然可以前缀和优化成 $ \texttt{2D0D} $，最后复杂度也就是 $ O(nm) $ 的。然后滚动数组也可以压掉一维，不过没必要，空间开的下。

然后按照这个做完会发现 WA 了两个点，具体看一下就会发现，按照这个式子，如果 $ k = 0 $，那么 $ dp(i - 1, j) $ 就会被加两次，所以此时还需要特判一下减去一个 $ dp(i - 1, j) $。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define MOD (ll)(998244353ll)

template < typename T = int >
inline T read(void);

int N, M, K;
ll dp[1100][5100];
ll sum[5100];

int main(){
    N = read(), M = read(), K = read();
    for(int i = 1; i <= M; ++i)dp[1][i] = 1, sum[i] = i;
    for(int i = 2; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            (dp[i][j] += j + K <= M ? (sum[M] - sum[j + K - 1] + MOD) % MOD : 0) %= MOD;
            (dp[i][j] += j - K >= 1 ? sum[j - K] : 0) %= MOD;
            if(!K)(dp[i][j] += -(sum[j] - sum[j - 1]) + MOD) %= MOD;
        }
        for(int j = 1; j <= M; ++j)
            sum[j] = (sum[j - 1] + dp[i][j]) % MOD;
    }printf("%lld\n", sum[M]);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_12_05 初稿

---

