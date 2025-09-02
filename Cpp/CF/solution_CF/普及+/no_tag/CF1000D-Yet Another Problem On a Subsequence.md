# Yet Another Problem On a Subsequence

## 题目描述

**题目大意：**

如果一个数组$[a_1,a_2,a_3,...,a_n]a_1=n-1$并且$a1>0$，这个数组就被叫为好数组，如果一个序列能正好分为多个好数组，ta就被叫为好序列，现在给定一个序列，求这个序列有多少好子序列，答案对$998244353$取模

## 样例 #1

### 输入

```
3
2 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
1 1 1 1
```

### 输出

```
7
```

# 题解

## 作者：jiangXxin (赞：7)

这道题读完题目，嗯，是**DP**没错了,我们可以定义一个$dp_i$,表示以第i位为一个好的序列开头，可以得到的答案数，(如果第i位数字为0，那么就是没有答案，**则$dp_i$为0**)考虑到我们是以i为开头，所以我们状态转移就只能从后面来转移.

从哪里来转移呢？

我们发现，我需要得到一个好序列，**只需要得到它的开头那个就好了**,那么我们可以枚举一个$j$,**表示拼接的结尾**，

则有->如果以i为开头，得到好的序列，那么我们要从j-i-1个位置中，选出a[i]个数的组合，乘以我们以$j$为开头，得到的好的序列数，所以我们可以得到状态转移方程：

![mTturt.png](https://s2.ax1x.com/2019/08/28/mTturt.png)


**（蒟蒻用不来markdown,只能手写了）**

那么代码也就很好写了:

```cpp
 /**
 *    author:  a2954898606
 *    created: 28.08.2019 11:03:16       
**/
#include<bits/stdc++.h>
#define REP(A,B,I) for(int I=(A);I<=(B);I++)
#define PER(A,B,I) for(int I=(A);I>=(B);I--)
#define max(X,Y) ((X)<(Y)?(Y):(X))
#define min(Y,X) ((X)<(Y)?(X):(Y))
#define read(FILENAME) freopen((FILENAME + ".txt"), "r", stdin);
#define write(FILENAME) freopen((FILENAME + ".txt"), "w", stdout);
#define LL long long
#define M 1200
#define mod 998244353
using namespace std;
const int N=2e6+12;
long long dp[N],a[N],c[M][M];
int main(){
    //read(1)
    //write(1)
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    REP(0,M-1,i){
        c[i][0]=c[i][i]=1;
        REP(1,i-1,j){
            c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
        }//初始化出一个组合数
    }
    int n;
    cin>>n;
    REP(1,n,i){
        cin>>a[i];//输入数据
    }
    dp[n+1]=1;//初始化
    PER(n,1,i){//因为要从小到大转移，所以这里倒着来
        if(a[i]<=0)continue;//不符合条件
        REP(i+a[i]+1,n+1,j){
            dp[i]+=(dp[j]*1LL*c[j-i-1][a[i]])%mod;//转移方程
            dp[i]%=mod;
        }
    }
    long long ans=0;
    REP(1,n,i){
        ans+=dp[i];
        ans%=mod;
    }
    cout<<ans<<endl;
    return 0;
}

```


---

## 作者：jch123 (赞：3)

## 思路：

设 $dp(i,j)$ 表示前 $i$ 个数所有子序列中，接上 $j$ 个数能形成好的子序列的个数。显然答案为 $dp(n,0)$。转移分三种情况。

1. 不考虑第 $i$ 个数，$dp(i,j) \leftarrow dp(i-1,j)$。
2. 接到上一个段，$dp(i,j) \leftarrow dp(i-1,j+1)$。
3. 新起一段，$dp(i,a_i) \leftarrow dp(i-1,0)+1$。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1005;
ll a[N],dp[N][N];//前i个数所有子序列中，接上j个数能形成好的子序列的个数
const ll mod=998244353;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<n;j++)
			dp[i][j]=(dp[i][j]+dp[i-1][j])%mod;
		for(int j=0;j<n;j++)
			dp[i][j]=(dp[i][j]+dp[i-1][j+1])%mod;
		if(a[i]>=1&&a[i]<=n)	
			dp[i][a[i]]=(dp[i][a[i]]+dp[i-1][0]+1)%mod;
	}
	cout<<dp[n][0];
	return 0;
}
```

---

## 作者：vme50xiex2 (赞：3)

怎么没人跟我做法一样。

设 $f(i,j)$  表示前 $i$ 个数的所有子序列中，还需要接上 $j$ 个数才能形成好的子序列的方案数，则答案为 $f(n,0)$。

转移比较简单：

1. 第 $i$ 个数作为新的一个子段。$f(i,a_i)=f(i-1,0)+1$。
1. 第 $i$ 个数接在最后一个子段上。$f(i,j)=f(i-1,j+1)$。
1. 第 $i$ 个数不出现。$f(i,j)=f(i-1,j)$。

做完了。时间复杂度 $\mathcal{O}(n^2)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
const int MOD = 998244353;
int n, a[N], f[N][N];
void Add(int &x, int y) {
	x += y; 
	if(x >= MOD) x -= MOD;
}
int main() {
	//freopen("data.in", "r", stdin);
	//freopen("code.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for(int i = 1; i <= n; ++i) {
		if(a[i] >= 1 && a[i] <= n) Add(f[i][a[i]], f[i - 1][0] + 1);
		for(int j = 0; j <= n; ++j) Add(f[i][j], f[i - 1][j + 1]);
		for(int j = 0; j <= n; ++j) Add(f[i][j], f[i - 1][j]);
	}
	printf("%d\n", f[n][0]);
	return 0;
}
```

---

## 作者：墨染琉璃殇 (赞：2)

## 本蒟蒻又来发题解了......

因为是一道绿题，所以不是特别难，通过读题，我们可以发现，这是一道 $DP$ 题，但是，这种颜色的题也肯定不会是裸的 $DP$ ，所以我们需要做一点小小的调整。

## 思路如下：

我们可以定义一个 $dp[i]$ ，考虑令 $dp[i]$ 表示前 $i$ 个数，第 $i$ 个数为重要的数的方案数。如果没有答案，则 $dp[i]=0$ 。

转移即为： $dp[i]*C(j-i-1,a[i])->dp[j]$ ，其中 $C(n,k)$ 为组合数。组合数可以通过 $C(n,k)=C(n-1,k-1)+C(n-1,k)$ 预处理。

时间复杂度为 $O(n^2)$ ，可以过。

然后，我们就可以得出答案了。

### $AC$ $Code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=998244353;
long long n,c[2005][2005],a[1005],dp[1005];
int main()
{
	cin>>n;
	for (long long i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	c[0][0]=1;
	for (long long i=1;i<=n;i++)
	{
		c[i][0]=1;
		for (long long j=1;j<=i;j++)
		c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;//边处理边取模，不然要炸。
	}
	dp[0]=1;
	for (long long i=1;i<=n;i++)
	{
		dp[i]=1;
		for (long long j=i-1;j>=1;j--)
		{
			if (a[j]>0 && i-j+1>=a[j]+1)dp[i]=(dp[i]+dp[j-1]*c[i-j][a[j]])%mod;//状态转移方程。
		}
	}
	dp[n]--;
	if(dp[n]<0) dp[n]+=mod;
	cout<<dp[n];
	return 0;
}
```
~~思路借鉴老师~~

---

## 作者：forest114514 (赞：1)

我们记 $f_i$ 为以 $i$ 为结尾的好序列数量，我们考虑枚举包含 $i$ 的好数组的开头 $j$，首先这个好数组限定选择 $j$ 和 $i$，所以如果 $a_j>0$，那么这个好数组的方案数为 $\binom{i-j-1}{a_j-1}$。

所以状态转移方程为：
$$
f_i=\sum\limits_{j=1}^{i-1}\binom{i-j-1}{a_j-1}\times\sum_{k=1}^{j-1}f_{k}
$$
后面的 $\sum_{k=1}^{j-1}f_{k}$ 显然可以前缀和 $O(1)$ 计算，最后答案为 $\sum_{i=1}^{n}f_{i}$，所以时间复杂度为 $O(N^2)$ 的。

CODE：

```cpp
const int N=1005,mod=998244353;
int n,a[N];
LL f[N],s[N],c[N][N];
signed main(){
	read(n);
	rep(i,1,n) read(a[i]);
	f[0]=s[0]=1;
	c[0][0]=1;
	rep(i,1,n){
		c[i][0]=1;
		rep(j,1,i) c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
	}
	rep(i,1,n){
		rep(j,1,i-1){
			if(a[j]>0&&a[j]-1<=i-j-1) f[i]=(f[i]+s[j-1]*c[i-j-1][a[j]-1]%mod)%mod;
		}
		s[i]=(s[i-1]+f[i])%mod;
	}
	write((s[n]-1+mod)%mod,'\n');
	return 0;
}
```





---

## 作者：qczrz6v4nhp6u (赞：1)

## 思路
DP+组合数学。很明显吧。

设 $f_i$ 表示前 $i$ 项里的好子序列数量，此时答案即为 $f_n$。  
下面考虑状态转移方程：

设当前为 $j$ ，令 $i$ 小于 $j$ 且 $a_i>0$。   
对于每一个 $f_j$ ，有 $f_j=\sum\limits_{a_i\leq j-i}(f_{i-1}+1)\times C_{j-i}^{a_i}$，其中 $C_n^m$ 代表组合数。

下面将对 $(f_{i-1}+1)\times C^{a_i}_{j-i}$ 做出解释：

因为要求长度是 $a_i+1$，去掉开头的 $a_i$，我们可以在 $[i+1,j]$ 中选取 $a_i$ 个数。  
此时区间长度就是 $j-i$。  
根据组合数的定义，我们可以得到以 $a_i$ 开头好数组个数是 $C_{j-i}^{a_i}$。

生成了新的好数组后，我们还可以把它和前面生成的好子序列拼接在一起。  
对于每一个新的好数组，有拼与不拼两种选择：  
若不拼，则有 $1$ 种方案；若拼接，则有 $f_{i-1}$ 种方案。  
一共就是 $f_{i-1}+1$ 种方案。

根据乘法原理，将他们俩乘起来就是新增加的方案数了。

## 做法
按照上面的方程DP转移即可。

组合数可以通过杨辉三角预处理求出。

最终时间复杂度： $O(n^2)$。
## 核心代码
组合数预处理：
```cpp
void init(){
	C[0][0]=1;//C(0,0)=1
	for(int i=1;i<=n;i++){
		C[i][0]=C[i][i]=1;
		for(int j=1;j<i;j++){
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;//组合数递推公式
		}
	}
}
```
逆向DP：
```cpp
void dp(){
	for(int j=1;j<=n;j++){
		for(int i=1;i<j;i++){
			if(a[i]>0&&a[i]<=j-i){
				f[j]=(f[j]+1ll*(f[i-1]+1)*C[j-i][a[i]])%mod;
			}
		}
	}
	printf("%d",f[n]);
}
```
正向DP：
```cpp
void dp(){
	for(int i=1;i<=n;i++){
		if(a[i]>0){
			for(int j=i+a[i];j<=n;j++){
				f[j]=(f[j]+1ll*(f[i-1]+1)*C[j-i][a[i]])%mod;
			}
		}
	}
	printf("%d",f[n]);
}
```
实际上两者是差不多的，但是正向DP少枚举了一些状态，所以快一内内

---

## 作者：Tx_Lcy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1000D)
## 思路
这显然是一道 $\verb!DP!$。我们不妨设 $f_{i,j}$ 为 $i$ 到 $j$ 的好序列个数，但是，经过~~本人亲身~~实验，发现这个状态萎掉了。

我们需要改变一下思路，设 $f_i$ 为前 $i$ 个数，$i$ 为一个好序列的开头的方案数，至于**为什么要设这个状态**，主要是因为前面那个状态萎掉了，而前面那个状态为什么不对，主要是因为我们没法转移，所以我们要设一个好转移的状态。

又因为一个好序列只要确定开头就行，所以我们把开头塞进状态。

转移也非常简单，$f_i=\sum_{j=1}^{i-1} f_{j-1} \times C_{i-j}^{a_j}$，这个组合数费马小定理求个逆元即可。

初始 $f_i=1$，注意最后要减回去。

接下来就可以愉快地 $\verb!AC!$ 了！
## 代码
不放了，自己写。


---

## 作者：complete_binary_tree (赞：0)

好的序列……这不就直接 $\sum_{i=1}^{n}C_{n-i}^{a_i}$ 吗？

奥，是 **能分成几个好数组** 的子序列。

那就 $\text{DP}$ 做！我们定义 $dp_i$ 为以 $i$ 为开头可以获得的好的序列数。然后就有以下情况：

- $a_i\le 0$

这时候不用管它，直接跳过。

- $a_i>0$

此时我们可以枚举一个 $j$，把 $n$ 到 $i+a_i+1$ 划分为两段：$(i,j)$ 和 $[j,n]$。

那么我们就可以在 $(i,j)$ 区间内选择 $a_i$ 个数，即 $C_{j-i-1}^{a_i}$，再乘上 $dp_j$，即 $j$ 的方案数。

当然，我们也可以直接将 $(i,n]$ 划分给 $a_i$。为了方便处理，我们增加个虚拟的 $dp_{n+1}$，并且赋初值为 $1$。这样，这种情况就相当于划分为 $(i,n]$ 和 $n+1$。

最终答案就是所有的 $dp_{i}$ 加起来。即：

$$dp_i=\sum_{j=i+a_i+1}^{n+1}C_{n-i}^{a_i}\times dp_j$$

$$ans=\sum_{i=1}^{n}dp_i$$

时间复杂度 $O(n^2)$。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e3 + 5, mod = 998244353;

int ksm(int a, int b){
	long long x = a, ans = 1;
	while(b){
		if(b & 1) ans = ans * x % mod;
		x = x * x % mod, b >>= 1;
	}
	return ans;
}

int jc[N], ny[N];

void csh(){
	jc[0] = 1;
	for(int i = 1; i <= 1e3; ++i) jc[i] = 1ll * jc[i - 1] * i % mod;
	ny[int(1e3)] = ksm(jc[int(1e3)], mod - 2);
	for(int i = 1e3 - 1; i >= 0; --i) ny[i] = 1ll * ny[i + 1] * (i + 1) % mod;
}

int C(int n, int m){
	return 1ll * jc[n] * ny[m] % mod * ny[n - m] % mod;
}

int a[N], n;
int ans[N], _ans;

int main(){
	scanf("%d", &n);
	csh();
	for(int i = 1; i <= n; ++i){
		scanf("%d", &a[i]);
	}
	ans[n + 1] = 1;
	for(int i = n; i >= 1; --i){
		if(a[i] <= 0) continue;
		for(int j = i + a[i] + 1; j <= n + 1; ++j){
			ans[i] = (0ll + ans[i] + 1ll * ans[j] * C(j - i - 1, a[i]) % mod) % mod;
		}
		_ans = (_ans + ans[i]) % mod;
//		printf("!%d %d\n", i, ans[i]);
	}
	printf("%d", _ans);
	return 0;
}
```

---

## 作者：Silvestorm (赞：0)

### 题目大意

[题目链接](https://www.luogu.com.cn/problem/CF1000D)。

如果一个数组 $[a_1,a_2,a_3,...,a_n]a_1=n-1$ 并且 $a_1>0$，这个数组就被叫为好数组，如果一个序列能正好分为多个好数组，它就被叫为好序列，现在给定一个序列，求这个序列有多少好子序列，答案对 $998244353$ 取模。

对于所有数据：$n\le 10^3$。

### 题目类型

dp，组合数学。

### 解题思路

~~一眼 dp，鉴定为赛时不会。~~

先来一个小思路，对于一个 $a_i$，我们往右取 $a_i$ 个数，这些数可以不用像 $(a_{i+1},a_{i+2},a_{i+3})$ 这样挨着，也就是说取数涉及到组合数学。取完数之后，这个好序列可以和其他好序列拼接，注意，拼接的好序列不能出现重叠。

由于组合数会常用到，可以预处理，存进 $f$ 数组中。接下来讲如何 dp。

令 $dp[i]$ 为区间 $[i,n]$ 中所有好序列。那么 $dp[i]$ 有两部分，不包含 $a_i$ 的所有好序列，以及包含 $a_i$ 的所有好序列。前者可以用 $dp[i]=dp[i+1]$ 转移，后者需要计算。

计算为：取 $a_i$ 为好序列开头，它在区间 $[i+1,i+x](a_i\le x\le n-i)$ 取数，然后对区间 $[i+x+1,n]$ 的好序列拼接。后者可以处理为 $dp[i+x+1]$。

### code

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
long long num[30305], m = 998244353, dp[10000], n, f[1003][1003], ans;
void solve(int x)
{
	dp[x] = dp[x + 1];						 // 第一部分
	if (num[x] > 0)							 // 第二部分·
		for (int i = x + num[x]; i < n; i++) // i是取数的区间右端点
		{
			dp[x] += (1 + dp[i + 1]) * f[i - x - 1][num[x] - 1];
			dp[x] = dp[x] % m;
		}
	return;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	f[0][0] = 1;
	for (int i = 1; i <= 1000; i++) // 预处理组合数
		for (int j = 0; j <= i; j++)
		{
			if (j == 0)
				f[i][j] = 1;
			else
				f[i][j] = f[i - 1][j - 1] + f[i - 1][j];
			f[i][j] = f[i][j] % m;
		}
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> num[i];
	for (int i = n - 1; i >= 0; i--)
		solve(i);
	cout << dp[0] << endl;
	return 0;
}
```


---

