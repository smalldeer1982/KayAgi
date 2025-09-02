# Good Key, Bad Key

## 题目描述

你有 $n$ 个箱子。第 $i$ 个箱子中有 $a_i$ 个硬币。你需要按照从箱子 $1$ 号到箱子 $n$ 号的顺序打开所有 $n$ 个箱子。

你可以用以下两种钥匙之一打开一个箱子：
- 好钥匙：使用一次消耗 $k$ 个硬币。
- 坏钥匙：使用时不消耗硬币，但会使所有未打开的箱子中的硬币数减半（包括正要打开的这个箱子）。硬币减半时向下取整。比如，用坏钥匙打开箱子 $i$ 号时，$a_i=a_i/2$，$a_{i+1}=a_{i+1}/2$，$......$，$a_n=a_n/2$。

所有钥匙用过一次就会断掉（别想着买一把好钥匙开完所有箱子了），好钥匙需要重复付费，坏钥匙效果会重复计算。

也就是说，你总共需要使用 $n$ 把钥匙，每个箱子用一把。开始时，你没有硬币和钥匙，如果想用好钥匙，你就得去买。值得注意的是，在这个过程中你可以赊账买钥匙；例如，如果你只有 $1$ 个硬币，你也可以购买价值 $k=3$ 个硬币的好钥匙，你的余额会变成 $-2$ 个硬币。

你需要求出开完所有箱子之后你能获得的最大硬币数量（显然大于等于 $0$ ）。

## 样例 #1

### 输入

```
5
4 5
10 10 3 1
1 2
1
3 12
10 10 29
12 51
5 74 89 45 18 69 67 67 11 96 23 59
2 57
85 60```

### 输出

```
11
0
13
60
58```

# 题解

## 作者：蒟蒻炒扇贝 (赞：17)

考虑动态规划。

设 $f_{i,j}$ 为开到第 $i$ 个箱子，已经用了 $j$ 次坏钥匙所能得到的最大金币数。设 $a_{i,j}$ 为用了 $j$ 次坏钥匙时，第 $i$ 个箱子里所拥有的金币数。

我们容易得到状态转移方程：

$f_{i,j}=\max(f_{i-1,j}+a_{i,j}-k,f_{i-1,j-1}+a_{i,j})$

其中逗号前的那一部分式子表示在之前状态的基础上使用好钥匙的情况，逗号后的那部分便表示在之前状态的基础上使用坏钥匙的情况。

如果暴力转移，那么时间复杂度就是 $\mathop{O(n^2)}$ 的。因为你需要 $\mathop{O(n)}$ 枚举开到了哪一个箱子，又要在此基础上 $\mathop{O(n)}$ 枚举使用坏钥匙的次数。时间空间会双双爆炸。

那该怎么办呢？

引入一个结论。我们发现一个数 $a_i$ 如果被除 $2$ 的次数大于等于 $\log_2{a_i}$，那么这个数就会变为 $0$。由于 $a_i$ 最大是 $10^9$，所以 $\log_2{a_i}$ 的最大值便约等于 $30$。

~~这就好办了~~，我们只要将之前的状态转移方程中 $j$ 的值域缩小到 $[0,30]$，时间复杂度和空间复杂度就会大大减小到 $\mathop{O(n\log a_i)}$ 了！

但是这道题并没有到此结束，如果你只是这样改的话会喜提 ```Wrong answer on test 4```。

问题出在哪了呢？

原来，仅仅是缩小值域的话，会让这个状态转移方程无法考虑到使用坏钥匙次数多于 $30$ 次的情况。

意识到当使用坏钥匙次数大于等于 $30$ 次时结果是相同的（因为我们用好钥匙的话收益可能为负，所以使用坏钥匙是最优的，但是此时所有盒子中的金币数均为 $0$，收益便不会改变），换句话说，对于任意的 $i$ ，当 $i$ 是一个定值，且 $j\ge30$ 时， $f_{i,j}$ 的数值是相等的。考虑将这些状态“压缩”到 $f_{i,30} (i\ge31)$ 中，让 $f_{i,30}$ 代替所有的 $f_{i,j}(j\ge31)$，问题便能迎刃而解了。

### 代码时间！
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=1e5+5;
int T,n,k,a[MAXN][35],f[MAXN][35];
signed main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>k;
		for(int i=1;i<=n;i++)for(int j=0;j<=30;j++)f[i][j]=-1e18;
		for(int i=1;i<=n;i++)cin>>a[i][0];
		for(int i=1;i<=n;i++)
		 for(int j=1;j<=30;j++)a[i][j]=a[i][j-1]/2;
		for(int i=1;i<=n;i++)
		{
			for(int j=0;j<=min(i,30ll);j++)
			 {
				f[i][j]=max(f[i-1][j]+a[i][j]-k,f[i][j]);
				if(j-1>=0)f[i][j]=max(f[i-1][j-1]+a[i][j],f[i][j]);//注意当j-1<0时状态是不存在的，我们不能从一个不存在的状态转移！ 
			 }
			if(i>=31)f[i][30]=max(f[i-1][30]+0,f[i][30]);//这里的0其实就是a[i][j](j>=31)
		}
		int maxn=-1e18;
		for(int j=0;j<=30;j++)maxn=max(maxn,f[n][j]);
		cout<<maxn<<endl;
	}
}
```
感谢阅读！

---

## 作者：fuxuantong123 (赞：8)

# CF1703G Good Key, Bad Key 题解
## 思路
看题解区一堆大佬用动态规划，其实暴力枚举就行了。

首先，一定是先用好钥匙再使用坏钥匙更优（一个简单的贪心），所以我们枚举使用好钥匙数量，统计答案即可。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long a[100010];
long long sum[100010];
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n;
		long long k;
		scanf("%d%lld",&n,&k);
		long long fw=0;
		sum[0]=0;
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			sum[i]=sum[i-1]+a[i];
			fw=max(fw,a[i]);
		}
		long long mx=-9e18;
		for(int i=0;i<=n;i++){
			long long ans=sum[i];
			long long sin=1;
			for(int j=i+1;j<=n;j++){
				sin*=2;
				if(sin>fw){
					break;
				}
				ans+=a[j]/sin;
			}
			ans-=i*k;
			mx=max(ans,mx);
		}
		printf("%lld\n",mx);
	}
return 0;
}
```


---

## 作者：Tx_Lcy (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/CF1703G)

怎么题解都是 $\verb!DP!$，我来一发贪心的题解。
## 思路
我们先钦定每个箱子都用好钥匙打开，我们发现如果我们要用坏钥匙，使用坏钥匙的箱子一定是从 $n$ 开始的连续的一段，因为这样**对原箱子的影响最小**。

但这样又有一个问题，我们无法计算后面一段箱子的价值，难道要暴力算？是的，就是暴力算，因为我们发现 $\log_2 10^9$ 是一个很小的数，所以我们很快就可以把箱子的价值除到 $0$，这样这道题就做完了。
## 代码
```cpp
//A tree without skin will surely die. 
//A man without face is invincible.
#include<bits/stdc++.h>
#define int long long
#define rint register int
using namespace std;
int const N=1e5+10;
int a[N],sum[N];
signed main(){
    ios::sync_with_stdio(false);
    cout.tie(0),cout.tie(0);
    int T;cin>>T;
    while (T--){
        int n,k,ans=0;cin>>n>>k;
        for (int i=1;i<=n;++i) 
            cin>>a[i],ans+=a[i],sum[i]=sum[i-1]+a[i];
        ans-=(n*k);int la=n;
        for (int i=n;i>=1;--i){
            int num=0;
            for (int j=i;j<=la;++j) a[j]/=2,num+=a[j];
            while (!a[la]) --la;
            ans=max(ans,sum[i-1]-(i-1)*k+num);
        }
        cout<<max(0LL,ans)<<'\n';
    }
    return 0;
}

```


---

## 作者：GWBailang (赞：3)

#### [原题传送](https://www.luogu.com.cn/problem/CF1703G)
好钥匙：使用一次消耗 $k$ 个金币并获得 $a_i$ 枚金币。

坏钥匙：使用一次消耗 $0$ 个金币但是 $a_i$ 至 $a_n$ 都减半，减完后获得 $a_i$ 枚金币。

乍一看像是 DP，但是细想，如果要使用好钥匙，那么一定要在使用第 $1$ 把坏钥匙前使用，否则得到的价值就不可能是最优。并且坏钥匙最多使用 $31$ 把，再多用不会获得更多的价值，因为 $2^{31}$ 已经超过了 $10^9$。

想到这剩下的就好办了，我们只需要暴力枚举用几把好钥匙，用前缀和计算出能获得的价值，取最大即可，时间复杂度为 $O(n \log n)$。

#### 代码：
```
#include<bits/stdc++.h>
using namespace std;
long long a[100005];
long long er[]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216,33554432,67108864,134217728,268435456,536870912,1073741824,2147483648};
//二的i次方
long long qzh[100005];//前缀和
int main(){
	long long t,n,k,da=0,zhi;
	cin>>t;
	while(t--){
		cin>>n>>k;
		da=0;//记录最大价值
		for(long long i=1;i<=n;i++){
			cin>>a[i];
			qzh[i]=qzh[i-1]+a[i];//计算前缀和
		}
		for(long long i=0;i<=n;i++){//枚举用几把好钥匙
			zhi=qzh[i]-i*k;//计算用i把好钥匙可以获得的价值
			for(long long j=i+1;j<=min(i+31,n);j++){
				//坏钥匙最多用31把
				zhi+=a[j]/er[j-i];
				//第i+1到n号箱子都用坏钥匙
			}
			//后面再用坏钥匙不会再有价值，所以不用再计算。
			da=max(da,zhi);//取最大的价值
		}
		cout<<da<<endl;
	}
	return 0;
}
```
#### 依旧是那句话：“十年 OI 一场空，不开 long long 见祖宗！”。

---

## 作者：郑朝曦zzx (赞：3)

# 解题思路

本题考虑**动态规划**，我们令 $dp_{i,j}$ 表示截止到第 $i$ 个箱子，恰好用了 $j$ 把钥匙时的最大金币数，由于 $a_i$ 不超过 $10^9$ 所以 $j$ 的上限只有 $30$ 左右，复杂度足以通过此题。

状态转移，情况有 $2$ 种：

- 用好的钥匙开这个箱子，则 $dp_{i,j} = dp_{i - 1,j} + a_{i,j} - k$。

$a_{i,}$ 表示用 $j$ 次坏的钥匙后开第 $i$ 个箱子后能获得的金币数。

- 用坏的钥匙，$dp_{i,j} = dp_{i-1,j-1} + a_{i,j}$

温馨提示，本题有两个坑点：

- 不要每组数据都 memset, 不然测试点 $2$ 会 TLE。

- 最终的答案是所有 $dp_{i,j}$ 的最大值，而不是 $dp_{n,i}$ 的最大值，因为，我们虽然只更新 $\log(a_i)$ 约等于 $30$ 次 $j$ 但是实际上我们使用坏的钥匙的次数可能超过 $30$，不然您将无法通过测试点 $4$。

## 代码
```cpp
# include <bits/stdc++.h>
typedef long long ll;
using namespace std;
int t, n, k;
ll a[100010][35];
ll dp[100010][35];
int main()
{
	scanf("%d", &t);
	while (t--)
	{
		for (int i = 0; i <= n; ++i)
			for (int j = 0; j <= 31; ++j)
				dp[i][j] = 0;
		scanf("%d %d", &n, &k);
		for (int i = 1; i <= n; ++i)
		{
			scanf("%lld", &a[i][0]);
			for (int j = 1; j <= 31; ++j)
				a[i][j] = a[i][j - 1] / 2;
		}
		ll ans = -1e18;
		for (int i = 1; i <= n; ++i)
		{
			for (int j = 0; j <= 31; ++j)
			{
				dp[i][j] = dp[i - 1][j] + a[i][j] - k;
				if (j >= 1) dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + a[i][j]);
				ans = max(ans, dp[i][j]);
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```


---

## 作者：skyskyCCC (赞：2)

## 前言。
题意传送门：[CF1703G](https://www.luogu.com.cn/problem/CF1703G)

一道很有意思的**动态规划**题。
## 分析。
考虑动态规划。

我们设 $dp_{i,j}$ 表示已经开到了第 $i$ 个箱子，用了 $j$ 把钥匙时所能获得的最大金币数。  

如果我们用好的钥匙，那我们用这个好钥匙开锁获得的金币就是这个箱子里的金币加上之前获得的金币，再减去买这个钥匙所花的 $k$ 元钱，用转移方程式表示为 $dp_{i,j}=a_{i,j}+dp_{i-1,j}-k$。

但是如果我们用坏钥匙，那么编号在区间 $[i,n]$ 里面的金币数会变为原来的二分之一，当然，下取整。

那么我们用坏钥匙时，所获得的金币，就是在用上一把钥匙打开上一个箱子所获的最大金币数，加上这个箱子里的金币数，用转移方程表示为 $dp_{i,j}=dp_{i-1,j-1}+a_{i,j}$

注意：上面的式子中的 $a_{i,j}$ 是用了 $j$ 次**坏**钥匙后打开第 $i$ 个箱子后，能获得的金币数。

然后我们发现这个动态转移方程时间复杂度是 $O(n^2)$ 的，肯定会超时。  
但是由于 $a_i\leq 10^9$，所以 $j$ 的数量大约在 $30$ 左右，我们就可以缩减时间复杂度至 $O(30n)$ 的。

注意：实际上我们使用坏的钥匙的次数可能超过 $30$ 次，因为答案是所有 $dp_{i,j}$ 中的最大值。

代码如下，仅供参考：
```
#include<bits/stdc++.h>
using namespace std;
long long t,n,k,ans=-1e17;//ans一定要开的足够大。
long long a[100005][40],dp[100005][40];
template <typename T> void read(T &x){//快读
	x = 0;
	bool f = 0;
	char c = getchar();
	while (c < '0' || c > '9') f |= c == '-', c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	if (f) x = -x;
}
template <typename T> void write(T x){//快输（没有换行）
	if (x < 0) putchar('-'), x = -x;
	if (x < 10) putchar(x + '0');
	else write(x / 10), putchar(x % 10 + '0');
}
int main(){
	read(t);
	while(t--){
		memset(dp,0,sizeof(dp));
		ans=-1e17;//注意初始化
		read(n);read(k);
		for (int i=1;i<=n;i++){
			read(a[i][0]);
			for (int j=1;j<=31;j++){//j的上限要大于30
				a[i][j]=a[i][j-1]/2;//统计
			}
		}
		for (int i=1;i<=n;i++){
			for (int j=0;j<=31;j++){
				dp[i][j]=dp[i-1][j]+a[i][j]-k;
				if(j>=1){
				    dp[i][j]=max(dp[i][j],dp[i-1][j-1]+a[i][j]);
				}
				ans=max(ans,dp[i][j]);
			}
		}
		write(ans);
		printf("\n");
	}
	return 0;
}
```
但是我们交上去，惊喜地发现测试点 $2$ 超时了。

为什么呢？

因为 ```memset``` 相当于一次从头到尾的遍历，其本身的时间复杂度是 $O(n)$ 线性级别的，与 $for$ 循环遍历整个数组并且依次赋值并没有其他的区别，如果在极其苛刻的时间复杂度条件下这个函数将会消耗大量的时间。

所以 ```memset``` 函数使时间复杂度升高了，导致运行时间增长，所以超时了。

我们将它改成：
```
for (int i=0;i<=n;i++){
    for (int j=0;j<=31;j++){
        dp[i][j]=0;
    }
}
```
就能成功通过本题了。
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：Hisaishi_Kanade (赞：1)

### upd on 2023.4.30 更正了一个笔误。

+ 约定 $p_{i}=2^i$。

显然是动态规划题。

套路地，设 $f_{i,j}$ 表示前 $i$ 个里用了 $j$ 次坏钥匙的最大硬币数。

+ 如果这一个箱子是好钥匙开的，那么好钥匙花掉 $k$ 个硬币，开箱得到 $\dfrac {a_{i}} {p_j}$，则 $f_{i,j}=f_{i-1,j}-k+\lfloor\dfrac {a_{i}} {p_{j}}\rfloor$。

+ 另一种情况，坏钥匙开的，那么 $f_{i,j}=f_{i-1,j-1}+\lfloor\dfrac {a_{i}} {p_{j}}\rfloor$。

综上，$f_{i,j}=\max\{f_{i-1,j}-k+\dfrac {a_{i}} {p_{j}},f_{i-1,j-1}+\lfloor \dfrac {a_{i}} {p_{j}}\rfloor\}$。

但是，$i,j$ 的枚举都是 $O(n)$ 的，则时间复杂度 $O(n^2)$，不能接受。

考虑降掉一维，我们发现，当 $j\ge \log a_{i}$ 时，$\lfloor \dfrac {a_{i}} {p_{j}}\rfloor=0$。

则我们的 $j$ 只需要枚举到 $\max\log a_i$，本题范围内约为 $30$。

考虑到一个问题，坏钥匙总次数超过 $30$ 次也不是没有可能，怎么办？

不难发现，$j>30$ 时，$f_{i,j}=f_{i,30}$，因为此时开箱没有任何贡献了。

那么只要在原来的转移上，补上 $f_{i,30}=\max\{f_{i,30},f_{i-1,30}\}$。

这时候其实 $f_{i,30}$ 表示的是坏钥匙使用次数 $\ge 30$ 时的最大价值。

显然结果为 $\max\{f_{n,j}\}$。

时间复杂度蜕变为 $O(n\log a_i)$。

```cpp
/*
f[i][j] -> 1 to i, used j.
f[i][j]=max(f[i-1][j]-w+a[i]/pw[j],f[i-1][j-1]+a[i]/pw[j])
O(n^2)
j 不需要到 n，a[i]/pw[log[a[i]]]=0
j=max(log[a[i]])约29
*/
#include <stdio.h>
#define rep(i,l,r) for(i=l;i<=r;++i)
using ll=long long;
int n,k,i,t,j;
const ll inf=1ll<<60;
inline ll min(ll x,ll y){return x<y?x:y;}
inline ll max(ll x,ll y){return x>y?x:y;}
ll a[100005],f[100005][35],pw[30];
ll ret;
int main()
{
	pw[0]=1;
	rep(i,1,30)
		pw[i]=pw[i-1]<<1;
	scanf("%d",&t);
	while(t--)
	{
		ret=-inf;
		scanf("%d %d",&n,&k);
		rep(i,1,n)
			rep(j,0,30)
				f[i][j]=-inf;
		rep(i,1,n)
			scanf("%lld",a+i);
		rep(i,1,n)
		{
			rep(j,0,min(i,30))
			{
				if(j>=1)
					f[i][j]=max(f[i-1][j]-k+a[i]/pw[j],f[i-1][j-1]+a[i]/pw[j]);
				else
					f[i][j]=max(f[i-1][j]-k+a[i]/pw[j],f[i][j]);
			}
			f[i][30]=max(f[i][30],f[i-1][30]);
		}
		rep(i,0,30)
			ret=max(ret,f[n][i]);
		printf("%lld\n",ret);
	}
}
```

---

## 作者：yingkeqian9217 (赞：1)

## 前言

看了一眼题解区，都写得挺繁琐的，我来提供一种方便一点的写法。

## 题目描述

你有 $n$ 个箱子。第 $i$ 个箱子中有 $a_i$ 个硬币。你需要按照从箱子 $1$ 号到箱子 $n$ 号的顺序打开所有 $n$ 个箱子。

你可以用以下两种钥匙之一打开一个箱子：
- 好钥匙：使用一次消耗 $k$ 个硬币。
- 坏钥匙：使用时不消耗硬币，但会使所有未打开的箱子中的硬币数减半（包括正要打开的这个箱子）。硬币减半时向下取整。比如，用坏钥匙打开箱子 $i$ 号时，$a_i=a_i/2$，$a_{i+1}=a_{i+1}/2$，$......$，$a_n=a_n/2$。

所有钥匙用过一次就会断掉（别想着买一把好钥匙开完所有箱子了），好钥匙需要重复付费，坏钥匙效果会重复计算。

也就是说，你总共需要使用 $n$ 把钥匙，每个箱子用一把。开始时，你没有硬币和钥匙，如果想用好钥匙，你就得去买。值得注意的是，在这个过程中你可以赊账买钥匙；例如，如果你只有 $1$ 个硬币，你也可以购买价值 $k=3$ 个硬币的好钥匙，你的余额会变成 $-2$ 个硬币。

你需要求出开完所有箱子之后你能获得的最大硬币数量（显然大于等于 $0$ ）。

## 分析

既然是按顺序，且有几种钥匙选择，那我们就可以尝试动态规划。第一眼想到 $f_i$ 表示前 $i$ 个的最大金币数，但是模拟一下样例就会发现是不行的。那么考虑使用二维，即 $f_{ij}$ 表示前 $i$ 个用了 $j$ 次坏钥匙之后的最大金币数。为什么是记录坏钥匙的使用次数呢？因为这样方便于计算后面的箱子里的剩余金币数。

对于每一步，一共是用好钥匙或者坏钥匙两种选择。所以我们不难列出状态转移方程式：

$ f_{i,j} = \begin{cases}
   f_{i-1,j} -k &\text{if j = 1}  \\
   \max(f_{i-1,j}+\lfloor\dfrac{a_i}{2^j}\rfloor-k,f_{i-1,j-1}+\lfloor\dfrac{a_i}{2^j}\rfloor) &\text{if } j>1
\end{cases}$

其中 $f_{i,j}$ 初始值设为 $-\infty$，不过显然使用坏钥匙的肯定不会 $<0$，所以我们其实只要对使用好钥匙的取一次 $-\infty$ 即可。

当然这样枚举肯定是会时间超限的，考虑优化第二重循环 $j$，不难发现，当 $j=31$ 时， $\lfloor\dfrac{a_i}{2^j}\rfloor$ 的值肯定为零，所以我们直接枚举 $j\le31$ 即可。

但是这样的话还是有些问题，那就是如果用了多于 $31$ 次的话，可能会无法计算到。这也不难解决，因为后边都是 $0$ 了，所以直接把当前状态计入答案即可。

不过这样空间还是太大了，我们其实可以把空间压缩到常数的。因为我们可以开滚动数组，类似于背包，因为当前状态取决于上一个，所以我们倒序遍历，就可以做到一维的效果。

## AC Code:
```
#include<bits/stdc++.h>
#define g(y) (x/(1<<y))
#define inf (long long)(-1e18)
using namespace std;
long long T,n,k,x,ans,f[32];//不开 long long 见祖宗
int main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&n,&k);
		ans=-1e18,memset(f,0,sizeof(f));//注意初始化
		for(int i=1;i<=n;i++){
			scanf("%lld",&x);
			for(int j=31;j>=0;j--)//倒序遍历
			 ans=max(ans,f[j]=max(f[j]+g(j)-k,(j?f[j-1]+g(j):inf)));
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```
~~超短代码新鲜出炉。~~


---

## 作者：sto_Micnation_orz (赞：1)

官方的贪心做法。

考虑在 $i$ 使用 `good key`，在 $i + 1$ 使用 `bad key` 的局面：  
耗费 $k$，第 $i$ 个仍然是 $a_i$，第 $i + 1$ 个是 $\dfrac{\lfloor a_{i+1} \rfloor}{2}$，第 $i + 1$ 后面的全部除以 $2$ 并向下取整。

考虑在 $i + 1$ 使用 `bad key`，在 $i$ 使用 `good key` 的局面：  
耗费 $k$，第 $i$ 个是 $\dfrac{\lfloor a_i \rfloor}{2}$，第 $i + 1$ 个是 $\dfrac{\lfloor a_{i+1} \rfloor}{2}$，第 $i + 1$ 后面的全部除以 $2$ 并向下取整。

显然，第一个方案一定不会比第二个方案更劣。所以直接枚举 $i$，然后贪心即可。

除以 $2$ 的时候，最多往后找 $40$ 个数就行了，因为 $2^{40} > 10^9$。

$\texttt{AC}$ 代码：
```cpp
#include <iostream>

using namespace std;
#define int long long

const int N = 100010;
const int M = 105;

int T;
int a[N], b[N];

signed main() {
    cin >> T;
    while (T--) {
        int n, k; scanf("%lld%lld", &n, &k);
        for (int i = 1; i <= n; i++) scanf("%lld", a + i), b[i] = a[i];
        int ans = 0, res = 0;
        for (int i = 0; i <= n; i++) {
            res += (i ? a[i] - k : 0);
            int tot = 1, sum = 0;
            for (int j = i + 1; j <= min(i + 40, n); j++) {
                int x = tot, y = a[j];
                while(x) y /= 2, x--;
                sum += y, tot++;
            }
            ans = max(ans, sum + res);
        }
        cout << ans << endl;
    }
    return 0;
}
```


---

## 作者：activeO (赞：1)

## 题目大意

~~（这我也提交了翻译）~~

有 $ n $ 个箱子，钥匙有好钥匙和坏钥匙，$ 1 $ 把好钥匙要花费 $ k $ 元，坏钥匙不用钱，现在你要一次打开这 $ n $ 个箱子。

对于第 $ i $ 个箱子，如果用的是坏钥匙，那么编号在区间 $ [i,n] $ 里面的金币数会变为原来的一半（下取整），如果用的是好钥匙，那么就会花费 $ k $ 个金币（可以欠债）！

## 思路

很容易想到 dp。

设 $ dp_{i,j} $ 表示已经开箱到第 $ i $ 个箱子，用了 $ j $ 把坏钥匙。
因为用坏钥匙的数量会直接影响后面的金币数，所以这里要记录坏钥匙的状态。

如果我们提前预处理出 $ a_{i,j} $ 表示第 $ i $ 个箱子，在前面用了 $ j $ 个坏钥匙的情况下，剩下的金币数。所以 $ a_{i,j}=a_{i,j-1}/2 $，初始化读入 $ a_{i,0} $ 就可以推出状态转移方程 $ dp_{i,j}=\max{dp_{i-1,j}-k+a_{i,j},dp_{i-1,j-1}+a_{i,j}} $。

然后发现时间复杂度是 $ O(n^2) $ 的，范围：$ n \leq 10^5 $，过不了。

然后开始仔细研究这个式子，发现题目中：$ a_i \leq 10^9 $，所以当 $ j \geq \log 10^9 \approx 30 $ 时，$ a_{i,j} $ 都为 $ 0 $！

所以实际上就 $ j $ 只用枚举到 $ 30 $，当 $ i>30 $ 时,$ dp_{i,30} $ 就代替所有 $ j>30 $ 的结果，就为 $ dp_{i-1,30} $。

时间复杂度：$ O(30n) $，可以通过此题。

## 代码

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int maxn=1e5+5;
const int inf=0x3f3f3f3f3f3f3f3f;
const int maxm=30;
int dp[maxn][maxm+5];
int a[maxn][maxm+5];

signed main(){
	
	int q;
	
	scanf("%lld",&q);
	
	while(q--){
		int n,k;
		scanf("%lld %lld",&n,&k);
		for(int i=1;i<=n;i++) scanf("%lld",&a[i][0]);
		for(int i=1;i<=n;i++){
			for(int j=0;j<=maxm;j++){
				dp[i][j]=-inf;
				if(j) a[i][j]=a[i][j-1]/2;
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=0;j<=min(i,maxm);j++){
				dp[i][j]=max(dp[i][j],dp[i-1][j]-k+a[i][j]);
				if(j) dp[i][j]=max(dp[i][j],dp[i-1][j-1]+a[i][j]);
			}
			if(i>maxm) dp[i][maxm]=max(dp[i][maxm],dp[i-1][maxm]);
		}
		int ans=-inf;
		for(int i=0;i<=maxm;i++) ans=max(ans,dp[n][i]);
		printf("%lld\n",ans);
	}
	
	return 0;
}
```


---

## 作者：liyuteng (赞：0)

一开始，枚举使用几次好钥匙，后面就全部用坏钥匙，就这样，很简单。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a[100100],sum[100100];
int main(){
	ll t,n,k;
	cin>>t;
	while(t--){
		ll mmax=0;
		cin>>n>>k;
		ll md=0;
		sum[0]=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			md=max(md,a[i]);
			sum[i]=sum[i-1]+a[i];
		}
		for(int i=0;i<=n;i++){
			ll ans=sum[i],cnt=1;
			for(int j=i+1;j<=n;j++){
				cnt*=2;
				if(cnt>md)break;
				ans+=a[j]/cnt;
			}
			ans-=i*k;
			mmax=max(mmax,ans);
		}
		cout<<mmax<<endl;
	}
	return 0;
}
```


---

## 作者：__stick (赞：0)

# 题意

给出 $n$ 个有硬币的盒子，可以花费 $k$ 个硬币用好钥匙打开，也可以用坏钥匙打开，并使在它之后的所有盒子硬币数减半，问按顺序打开最多获得多少硬币。

# 思路

一道比较明显的 dp，因为最多使用 $30$ 次坏钥匙，多了就没有意义（全是 $0$），所以考虑将使用了多少次坏钥匙存进状态，则使用了多少次坏钥匙，那硬币数就直接右移多少位即可。

定义 $F_{i,j}$ 表示打开前 $i$ 个盒子，使用了 $j$ 次坏钥匙最多可以获得的金币数量，最后取 $\max$ 就可以了。

转移不难想到，总共两种情况，用好钥匙，或者坏钥匙，所以有： 
$$F_{i,j}=\max(F_{i-1,j}+\lfloor\frac{a_i}{2^j} \rfloor-k,F_{i-1,j-1}+\lfloor\frac{a_i}{2^j} \rfloor)$$


明显可以滚调第一维，并且可以使用位运算方便的处理 $\lfloor\frac{a_i}{2^j} \rfloor$，于是开一个 $30$ 的 dp 数组即可。

# 代码

```cpp
#include<iostream>
#include<vector>
#include<array>
#include<algorithm>
using namespace std; 
typedef long long ll;

int main()
{
//	ios::sync_with_stdio(0);cin.tie(nullptr);
	int T;cin>>T;
	while(T--)
	{
		ll n,k;cin>>n>>k;
		int x;
		vector<ll>F(34);
		ll ans=0;
		for(int i=1;i<=n;i++)
		{
			cin>>x;	//记得倒序，不然就覆盖了上次的答案
			for(int j=min(31,i);j>=1;j--)F[j]=max(F[j]+(x>>j)-k,F[j-1]+(x>>j));
			F[0]=F[0]+x-k;
			ans=max(ans,*max_element(F.begin(),F.end()));
            //每次都要更新答案，因为有可能后面的全是零，只能使用坏钥匙，这样次数就超过了数组中存的
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```


---

## 作者：tzyt (赞：0)

题目链接[（CF](https://codeforces.com/problemset/problem/1703/F)，[洛谷）](https://www.luogu.com.cn/problem/CF1703F) | 强烈推荐[博客](https://ttzytt.com/2022/07/CF1703/)中观看。

## 思路（来源于官方题解）

我们能发现，对于所有的盒子，交错的使用好钥匙和坏钥匙总是更加不合算的。

并且，连续的，在前面的盒子使用好钥匙会更合算。（或者说使用好钥匙作为前缀）。

假设我们在一个好钥匙之前使用了一个坏钥匙，那么我们获得的收益是：

$$
\lfloor \frac{a_i}{2} \rfloor + (\lfloor \frac{a_{i + 1}}{2} \rfloor - k)
$$

但如果先使用好钥匙，后使用坏钥匙，获得的收益是：

$$
(a_i - k) +  \lfloor \frac{a_{i + 1}}{2} \rfloor
$$

很明显，先使用好钥匙更合算。

更直观一点的解释是，不管先使用哪种钥匙，都会减去 $k$ 的收益，但是如果先使用坏钥匙，我们会把两个盒子的收益减半，但如果先使用好钥匙，就只会把一个盒子的收益减半。

所以我们只会在最后的部分使用坏钥匙，在某些 $k$ 比较大的情况下，可能相比减去 $k$，把 $a_i$ 减半更合算。

所以只需要枚举一个使用好钥匙和坏钥匙的分割点，在这个点前面全部使用好钥匙，后面全部使用坏钥匙。

我们设这个分割点为 $x$。

那么在分割点 $x$ 后面使用坏钥匙，每个盒子的收益就会变成：

$$
a_{x + i} = \lfloor a_{x + i} \div 2^{i} \rfloor
$$

能发现这个 $2^i$ 会增长的很快，在某个点之后，$a_i$ 就会变成 $0$。那么在这个点之后我们就没必要再计算了。

因为最大的 $a_i$ 为 $10^9$，所以 $\log_2(10^9) \approx 30$ 之后就没必要计算了。（或者你可以想，一直右移一个数，那么过了某个点整个数的二进制形式就没有 $1$ 了）。

## 代码

```cpp 
#include <bits/stdc++.h>
using namespace std;
#define ll long long
// author: ttzytt (ttzytt.com)
// ref: https://codeforces.com/blog/entry/104786
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        ll psum = 0, ans = 0;
        // psum 是使用好钥匙获得的收益
        for (int i = -1; i < n; i++) {
            if (i != -1) psum += (ll)(a[i] - k);
            ll cur = psum;
            // 枚举 i 这个分割点
            for (int j = i + 1; j < min(n, i + 32); j++) {
                // 过了 i + 32 就没必要继续计算了
                int bkval = a[j];
                bkval >>= (j - i);  // i + 1 要 / 2, i + 2 要 / 4 ...
                cur += bkval;
            }
            ans = max(ans, cur);
        }
        cout << ans << endl;
    }
}
```

---

## 作者：codemap (赞：0)

#### 题目分析

这道题的主要问题在于选择好坏钥匙的顺序。

可以发现，选择坏钥匙之后，最优解一定是之后都选择坏钥匙，下证：

假设有两个箱子，分别有价值 $x$ 和 $y$，而好钥匙花费为 $k$，那么有四种好坏钥匙的选择方式。

- 两个都选好钥匙，总价值 $x+y-2k$
- 第一个选好钥匙，第二个选坏钥匙，总价值为 $x+\frac{y}{2}-k$
- 第一个选坏钥匙，第二个选好钥匙，总价值为 $\frac{x}{2}+\frac{y}{2}-k$
- 两个都选坏钥匙，总价值为 $\frac{x}{2}+\frac{y}{4}$

可以发现，这四个值中，唯一一对一个值严格小于等于另一个值的就是 $\frac{x}{2}+\frac{y}{2}-k \le x+\frac{y}{2}-k$，也就是说选择坏钥匙后在选择好钥匙一定不是最优解。

这样，我们只用从前到后枚举，每次都有两种情况，这次用好钥匙和后面都用坏钥匙，计一下数然后取最大值既可。

每次计算都用坏钥匙的复杂度是 $\log$ 的，总复杂度为 $O(n \log n)$，可以通过此题。

#### 代码

```cpp
#include<iostream>
using namespace std;
long long n,a[100001];
//计算坏钥匙的函数
long long calc(long long x)
{
    long long i,S=2,t=0;
    for(i=x;i<=n;i++)
    {
        t+=a[i]/S;
        if(S<1e9)
            S*=2;
        //超过1e9可直接返回
        else
            return t;
    }
    return t;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long t,k,i,x,S,mmax;
    cin>>t;
    while(t--)
    {
        cin>>n>>k;
        for(i=1;i<=n;i++)
            cin>>a[i];
        S=0;
        mmax=0;
        for(i=1;i<=n;i++)
        {
            //如剩下都为坏钥匙
            mmax=max(mmax,S+calc(i));
            //这次用好钥匙
            S+=a[i]-k;
            mmax=max(mmax,S);
        }
        cout<<mmax<<"\n";
    }
    return 0;
}
```


---

