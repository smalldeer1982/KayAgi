# Round Subset

## 题目描述

我们把一个数的 roundness 值定义为它末尾 $0$ 的个数。

给你一个长度为 $n$ 的数列，要求你从中选出 $k$ 个数，使得这些选出的数的积的 roundness 值最大。

## 样例 #1

### 输入

```
3 2
50 4 20
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 3
15 16 3 25 9
```

### 输出

```
3
```

## 样例 #3

### 输入

```
3 3
9 77 13
```

### 输出

```
0
```

# 题解

## 作者：_stellar (赞：22)

### [点￥這#里体验题目巛♂性的版♀本](https://www.luogu.org/problemnew/show/CF837D)



------------

## Part1:做题感想：

+ 马上就要NOIP了，本蒟蒻DP也是非常的蒻。正好集训班ZHHX神犇讲了这道题，发现是道思维挺不错的题目，就过来水了。

+ 如果细心的话会发现这道题某个人的记录占了一页（⑨次）~~（就是我）~~
+ 快读出锅害死人

+ 这是本人第一次写题解，如果有纰漏的地方函请斧正。



------------

## Part2.动态规划心得：

名言1：
```
DP进阶:堆维度和删维度就是了。——鲁迅
```

当然，我们不能盲目堆。
**我在这里要讲的更多一些DP的小技巧**，以便以后dalao们能更好的了解DP而不是日日夜夜头疼想状态转移方程。


------------

## Part3.有用的小技巧：

### 1.增加维数。
我们拿到一道题且无从下手时，其正解一般是DP。
为什么我们做不出来？因为其中有很多很多**因变量**不受我们控制。也就是说，我们在考虑该状态转移的过程中应该尽量多的选择具有后效性的状态，而后再想着怎么优化降维。

### 2.巧用其他数据结构。

我在这里举个栗子大家就懂了：去年PJ组最后一道题**[跳房子](https://www.luogu.org/problemnew/show/P3957)**。我们都能想到用dp[i]来表示最大值，但是时间复杂度太大了。

P.S.
```
动态规划时间复杂度：状态数*状态转移复杂度
```

我们就很自然地想到用单调队列来维护最大值。

同理，当我们苦思冥想dp方程怎么优化时不妨回顾一下自己刷过的题，或许会有灵感哦。

### 3.整体与部分的转化（即可行性转最优）。

我们在某题~~（BZOJ1079）~~可能会暴力出来一个~~1e9~~维的dp方程。不妨再想想：

#### 可不可以把其中一个维度扔出来作为dp的含义呢？

很高兴的是，这道题就是那么优化的，待会我们再讲。

### 4.合并本质相同的维度。

在某些问题里，我们会发现有几个维度的意思（本质目的）是一样的。那我们不如合并降维，结为异姓兄弟。

### 5.再说。

下面我们就开始正式讲这道题。



------------

## Part4.不做成背包的本题做法：


Cthugha告诉我说这是背包，我反正没看出来QAQ。不过我们不能只会背包，我们必须搞明白动态规划的普遍做法而不是每道题都想着怎么套模板。~~（其实就是没看出来怎么用背包）~~

刚才我们提到了第三点：整体与部分的转化，我们现在就开始具体讲讲。


+ 这题怎么做？看不懂啊QAQ



------------

### DP方程初步分析：

```
我们把一个数的 roundness 值定义为它末尾 0 的个数。

给你一个长度为 n 的数列，要求你从中选出 k 个数，使得这些选出的数的积的 roundness 值最大。
```
我们至少能得到几条信息：

#### 1.有什么对roundness末位的0具有较大贡献
#### 2.0不能对roundness产生贡献

有时候我们的直觉是对的： 
### Key1:只有2和5才能凑成末位0。（10嘛）
### 且乘下来0的个数由min(sum_2,sum_5)决定哦
换句话说，2与5的贡献最大。

其他的就好想多了：
我们需要最优的子结构，就可以安排一个i作为前i个已经选取的数，但是一些数我们可以不选啊，就在安排一个j作为已经选取的数


自此我们摸出了一个简单的四维dp方程：dp[i][j][x][y]

### Key2：四维dp方程表示前i个数已经选取了j个数，其中2为质因数的数个数为x,5为质因数的数的个数为y。dp表示一个bool值，可以选取则为true,反之则为false



------------

### 初步DP方程的转移方程：

Dp[i+1][t+1][ x+sum_2[i+1] ][ y+sum_5[i+1] ]=true;

Dp[i+1][t][x][y]=true;

最后总得计算一次roundness最大值即可。时间复杂度：O（$N^{2}$*$(Nlog N)^{2}$） 太大了。



------------

### 运用知识点三解决本道题:

我们不妨将**[y+sum_5[i+1]]**移出来，作为dp的含义。
即：

### Key3：dp[i][j][x]=y;
### dp[i][j][x]表示将前i个数选出t个，已经有x个2，dp值代表最多有多少个5。

那么状态转移方程即为：
#### Dp[i+1][j][x]=max(dp[i+1][j][x],dp[i][j][x]);
#### Dp[i+1][j+1][x+sum_2]=max(Dp[i+1][j+1][x+sum_2],dp[i][j][x]+sum_5);（有前提）

时间复杂度是：O（$N^{2}$*Nlog N）

当然，还有优化方法：



------------
### 运用状态压缩优化本问题：

具体请看AC代码，这里不多讲，因为状压dp很常用就是了。

------------
### AC代码：

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#include<stack>
#include<queue>
#include<cmath>
//#include<mrwang>
#define ll long long
#define mp make_pair
using namespace std;
/*
inline ll read() {
    int x=0,w=0;
    char ch=0;
    while(!isdigit(ch)) {
        w|=ch=='-';
        ch=getchar();
    }
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return w?-x:x;
}*/
int get_lower(ll x,int p) { //求某个因数的次数
	int ass=0;//贫穷限制了我的想象力
	while(x%p==0) {
		x/=p;
		ass++;
	}
	return ass;
}
ll n,k;//题目给出
ll a[200+5];//不要忘了开大一点哦
//bool dp[3][200+50][5000][5000];//原四维未优化dp方程
ll dp[2][200+5][6000];//前i位已经选出了j个数，其中因数2的个数为k所代表的因数5的个数
ll sum_two,sum_five,sum,ans;//计算2,5出现次数
ll cur;//状压
inline void ready() {//本人习惯 
//    n=read(),k=read();
	scanf("%d%d",&n,&k);
	for(ll i=1; i<=n; i++)
//	a[i]=read();
		scanf("%lld",&a[i]);
	memset(dp,-1,sizeof(dp));//这个是老习惯 
}
int main() {
	ready();
	dp[0][0][0]=0;//不要忘了初始情况 
	for(ll i=1; i<=n; i++) {
		sum_two=get_lower(a[i],2);//计算质因数2的出现次数 
		sum_five=get_lower(a[i],5);//同上 
		cur^=1; 
		sum+=sum_two;//计算总次数 
		for(ll j=0; j<=k&&j<=i; j++) { //因为是取出i个数
			for(ll x=0; x<=sum; x++) {
				dp[cur][j][x]=max(dp[cur^1][j][x],dp[cur][j][x]);
				//决策一：考虑当前数是否有贡献
				if(j>=1&&dp[cur^1][j-1][x-sum_two]>=0&&x-sum_two>=0)
					dp[cur][j][x]=max(dp[cur^1][j-1][x-sum_two]+sum_five,dp[cur][j][x]);
				//决策二：考虑取出当前数是否对当前产生最大贡献
			}
		}
	}
	for(ll i=0; i<=sum; i++) {
		ans=max(ans,min(i,dp[cur][k][i]));//乘下来0的个数由2质因子和5质因子的数量来决定
	} //即min(i,dp)
	printf("%lld",ans);
	return 0;
}
```




------------

### 后记：

~~明明我快读没写错啊为什么会卡在第8个点上啊QAQ~~

## 祝各位NOIP2018都400score++，拿到自己想要的好成绩！

学累了可以找我来玩哦。

感谢帮我debug的各位神仙

END.



---

## 作者：tzl_Dedicatus545 (赞：15)

这道题很容易即可发现是道 DP 题，那么我们分成 $3$ 各部分来做：

# Part 1: 定义状态

这道题的状态很好想：

根据幼儿园大班数学知识可得： $1$ 个数的 $\texttt{roundness }$ 值只取决于质因数 $2$ 和 $5$ 的最小值。

那么，可以想到 $\texttt{dp}[i][j][k]$ 的含义是：在前 $i$ 个数中选 $j$ 个数，质因数 $5$ 的数量为 $k$ ，含义是质因数 $2$ 的数量。

# Part 2: 状态转移

状态转移方程也不难想，对于每一个不为 $0$ 的数，有两种选择：选或者不选，那么，状态转移方程即为：

$$ \texttt{dp} [i][j][k]=\max{(\texttt{dp}[i-1][j][k] , \texttt{dp}[i-1][j-1][k-PrimeFactor5[i]]+PrimeFactor2[i])}$$

# Part 3：数组初值

因为每个状态最开始都是不可达的，所以 $\texttt{dp}$ 数组全部初始化为负无穷大， $\texttt{dp}[1][0][0]$ 初始化为 $0$ 。

# AC Code:

```cpp
//By Luogu@wangdemao(308854)
#include <iostream>
#include <cstring>

using namespace std;

int GetPrimeFactor2InANum(long long num);
int GetPrimeFactor5InANum(long long num);

long long PrimeFactor2[220],PrimeFactor5[220];
long long dp[220][10020];
long long Numbers[220];
int n,k;

int main()
{
	cin>>n>>k;
	
	for(int i=1;i<=n;i++)
	{
		cin>>Numbers[i];

		PrimeFactor2[i]=GetPrimeFactor2InANum(Numbers[i]);

		PrimeFactor5[i]=GetPrimeFactor5InANum(Numbers[i]);
	}
	
	memset(dp,~0x3f,sizeof(dp));
	
	dp[0][0]=0;
	
	for(int i=1;i<=n;i++)
	{
		for(int j=k;j>=1;j--)
		{
			for(int l=10000;l>=PrimeFactor5[i];l--)
			{
				if(Numbers[i]!=0)
					dp[j][l]=max(dp[j][l],dp[j-1][l-PrimeFactor5[i]]+PrimeFactor2[i]);
			}
		}
	}
	
	long long ans=0;
	
	for(long long i=0;i<=10000;i++)
	{
		ans=max(ans,min(i,dp[k][i]));
	}
	cout<<ans;
	
	return 0;
}

int GetPrimeFactor2InANum(long long num)
{
	int cnt=0;
	
	if(num==0)
		return 0;
	
	while(num%2==0)
		num/=2,cnt++;
		
	return cnt;	
}

int GetPrimeFactor5InANum(long long num)
{
	int cnt=0;
  
	if(num==0)
		return 0;

	while(num%5==0)  
		num/=5,cnt++;
		
	return cnt;	
}
```


---

## 作者：Zzzzzzzm (赞：14)

### 1.什么情况下会有$0$。
可以通过$1$年级数学知识得知若设该数$2$的因子个数为$two$，$5$的因子个数为$five$，可知0的个数为$\min(two,five)$。

### 2.如何得到最优解
我们可以设$dp[j][k]$表示当前已经到了$j$并且有$k$个因子$5$时最大的因子$2$的个数。

所以，我们可以推出式子：

$dp[j][k]=max(dp[j][k],dp[j-1][k-five[i]]+two[i])$

$i$为当前枚举到的数，$j$为以选择个数，$k$为$5$因子数。


```cpp
for(register int i = 1; i <= n; ++i)
	for(register int j = i; j >= 1; --j)
		for(register int p = 6200; p >= five[i]; --p)
			dp[j][p] = max(dp[j][p], dp[j-1][p-five[i]]+two[i]);

```

### 3.如何查询
从$6200$到$1$查询，$ans = \max(dp[k][i],i)$，若$ans>i$，则直接输出$ans$，因为此后$i$只会越来越小直到找不到就输出$ans$。

------------

**Q1**:为何$p$是$6200$->$five[i]$：有$200$个数，每个数大概最多是$30$因子左右，所以最多也不超过$6200$。

**Q2**:为何$p$是从大到小枚举：如果从小到大会选多次（可参考完全背包）。

**Q3**:为何要初始化$dp$数组：部分状态可能存在非法情况（根本无法到达），如果不$memset$就会让他更新别的状态，导致错误答案。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;

int n, k, ans;
int dp[205][6205];

long long num[205];
int two[205], five[205];

template<typename T>									//快读快写 
inline void read(T&x){
	x=0; char q; bool f=1;
	while(!isdigit(q = getchar()))	if(q == '-')	f = 0;
	while(isdigit(q)){
		x = (x<<1)+(x<<3)+(q^48);
		q = getchar();
	}
	x = f?x:-x;
}

template<typename T>
inline void write(T x){
	if(x<0){
		putchar('-');
		x = -x;
	}
	if(x>9)	write(x/10);
	putchar(x%10+'0');
}

int main(){
	read(n), read(k);
	for(register int i = 1; i <= n; ++i){
		read(num[i]);									//输入 
		while(num[i] % 2 == 0){							//循环找two[i] 
			++two[i];
			num[i] /= 2;
		}
		while(num[i] % 5 == 0){							//循环找five[i] 
			++five[i];
			num[i] /= 5;
		}
	}
	memset(dp, -0x3f, sizeof(dp)); 						//初始化dp数组 
	dp[0][0] = 0; 
	for(register int i = 1; i <= n; ++i)
		for(register int j = i; j >= 1; --j)
			for(register int p = 6200; p >= five[i]; --p)
				dp[j][p] = max(dp[j][p], dp[j-1][p-five[i]]+two[i]);
	for(register int i = 6200; i >= 1; --i){
		ans = max(ans, min(i, dp[k][i]));							//寻找ans 
		if(ans > i){
			write(ans);
			return 0;
		}
	}
	write(ans);											//输出 
	return 0;
}
```
#### update 3.16修正了查询时的问题

---

## 作者：wenge (赞：9)

看见没有二维数组的版本，所以放一下。

本题就是个二维费用背包。

由于一维01背包的状态转移方程是
$$dp[j]=max(dp[j],dp[j-c[i]]+w[i])(j\geq c[i])$$
所以一般二维费用背包压掉一维的方法也类似：
$$dp[j][k]=max(dp[j][k],dp[j-c[i]][k-d[i]]+w[i])(j\geq c[i],k\geq d[i])$$
本题中为
$$dp[j][k]=max(dp[j][k],dp[j-1][k-b[i]]+a[i])(j\geq 1,k\geq b[i])$$
其中$dp[j][k]$表示拿了$j$个数，共有$k$个因子$5$的情况下因子$2$的最大数量。$b[i]$表示第$i$个数因子$5$的数量，$a[i]$表示第$i$个数因子$2$的数量。

$dp$数组的第二维大小最多也只有$20\times log_5\ 10^{18}≈5150$。为了保险起见可以开$6000$。

最后提醒一下，$j$和$k$两维都要倒序枚举（想一想，为什么）

AC代码：
```cpp
#pragma GCC optimize(2) 
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdio>
#include <queue>
#include <map>
//int mod=1000000007;
using namespace std;
typedef long long ll;

ll a[205],b[205];
ll dp[205][10005];//max:5150

ll n,m;
ll ans;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	memset(dp,-1,sizeof(dp));
	dp[0][0]=0;
	
	cin>>n>>m;
	
	for(int i=1;i<=n;i++){
		ll t;
		cin>>t;
		while(t%2==0)t/=2,a[i]++;
		while(t%5==0)t/=5,b[i]++;
	}
	
	for(int i=1;i<=n;i++){
		for(int j=m;j>=0;j--){
			for(int k=10000;k>=0;k--){
				if(j>=1&&k>=b[i]&&dp[j-1][k-b[i]]!=-1)dp[j][k]=max(dp[j][k],dp[j-1][k-b[i]]+a[i]);
			}
		}
	}
	
	for(int i=0;i<=10000;i++){
		ans=max(ans,min((ll)i,dp[m][i]));
	}
	cout<<ans;
    return 0;
}
```


---

## 作者：傅思维666 (赞：7)


## 题解：

~~2019.10.29模拟赛T1原90分场~~

思路假了被出题人@ysy20021208把数据卡成了70.感谢出题人（笔芯.jpg）

一开始的思路是把原数拆分成2和5，然后设置$dp[i][j]$表示前$i$个数中选择$j$个数的最大的$roundness$值，状态转移就是：
$$
dp[i][j]=max(dp[i-1][j],dp[i-1][j-1]+cnt5[i]);
$$
（$cnt5[]$为5的数量）

我犯了一个想当然的错误：质因数分解后一定$5$的数量会更少一些。当然，如果把$2,5$的数量取$min$，这个思路也是不对的，连样例都过不去。

后来重新捋思路：发现这道题的一个症结所在就是协调质因子中2和5的关系使得选取的数对后导零有最大的贡献。这个贡献不仅跟某一个数质因子中2，5的数量有关，还跟这个数列中我们选取了什么数有关。

那么这道题就变成了一个这样的背包问题：

我们设置$dp[i][j]$表示选取$i$个数、5有$j$个的最大2的个数。

那么会有这样的一个转移方程：
$$
dp[i][j]=max(dp[i][j],dp[i-1][j-cnt5[i]]+cnt2[i]);
$$
当然，这个数组只是处理出一个最优矩阵。我们最终出解的时候还要进行统计答案。

具体操作详见代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define int long long
using namespace std;
int n,m,ans,tmp;
int a[210],cnt2[210],cnt5[210];
int dp[210][20000];
//设dp[i][j]表示选i个物品,5有j个时2的最多数量。
signed main()
{
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        tmp=a[i];
        while(tmp%2==0)
            cnt2[i]++,tmp/=2;
        while(tmp%5==0)
            cnt5[i]++,tmp/=5;
    }
    memset(dp,-1,sizeof(dp));
    dp[0][0]=0;
    for(int i=1;i<=n;i++)
        for(int j=m;j>=1;j--)
            for(int k=10000;k>=cnt5[i];k--)
                dp[j][k]=max(dp[j][k],dp[j-1][k-cnt5[i]]+cnt2[i]);
    for(int i=0;i<=10000;i++)
        ans=max(ans,min(i,dp[m][i]));
    printf("%lld",ans);
    return 0;   
}
```



---

## 作者：Sol1 (赞：4)

理解了WA到绝望的人看到没有题解时的痛苦，写一篇题解吧！

# 典型的背包。

因为$log_2(N)<log_5(N)$对于$N∈R$恒成立，所以$2$作为价值，$5$作为费用。至于容量。。~~随便设一个INF就行了，比如6000。~~

所以我们要如何递推呢？

设```f[i][j][k]```为在前```i```个数里选择```j```个，其中包含```k```个质因数$5$时，最多的质因数$2$的个数。

于是我们就有递推式：

设```sum2[i]```为第$i$个数中$2$的个数，```sum5[i]```为第$i$个数中$5$的个数，有：

$f[\ i\ ][\ j\ ][\ k\ ]=\max\ f[\ i\!-\!1\ ][\ j\!-\!1\ ][\ k\!-\!sum5[\ i\ ]\ ]$。

边界条件：

$f[\ 0\ ][\ 0\ ][\ 0\ ]=0$

答案：

$\max f[\ N\ ][\ K\ ][\ i\ ]$对于$i\ ∈\ [\ 0,6000\ ]$。

还不懂？看我代码。

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 205;
int f[2][MAXN][6005], sum2[MAXN], sum5[MAXN];
int main()
{
	int N, K;
	scanf("%d%d", &N, &K);
	for (int i = 1;i <= N;i++)
	{
		long long x;
		cin >> x;//CF不让用%lld。。。 
        //分离2
		while ((x & 1) == 0)
		{
			sum2[i]++;
			x >>= 1;
		}
        //分离5
		while (x % 5 == 0)
		{
			sum5[i]++;
			x /= 5;
		}
	}
	memset(f, -1, sizeof(f));
	f[0][0][0] = 0;//初始条件
	for (int i = 1;i <= N;i++)
		for (int j = 0;j <= K;j++)
			for (int k = 0;k <= 6000;k++)
			{
				f[i % 2][j][k] = f[(i - 1) % 2][j][k];
				if (j >= 1 && k >= sum5[i] && f[(i + 1) % 2][j - 1][k - sum5[i]] != -1)
					f[i % 2][j][k] = max(f[i % 2][j][k], f[(i - 1) % 2][j - 1][k - sum5[i]] + sum2[i]);//递推方程
			}
    //计算答案
	int ans = 0;
	for (int k = 0;k < 6000;k++)
		ans = max(ans, min(k, f[N % 2][K][k]));
	printf("%d", ans);
	return 0;
}
```

---

## 作者：pomelo_nene (赞：2)

~~本来一眼秒了但是调了很久就很尴尬（~~

我们把一个数的 $\operatorname{roundness}$ 值定义为它末尾 $0$ 的个数。显然构成一个 $\operatorname{roundness}$，需要一个因子 $2$ 和因子 $5$。

于是首先我们把没有因子 $2$ 和 $5$ 的数抽出去，然后再考虑。

通过分解我们可以得到一个数 $a_i$ 的表示：$a_i=2^x 5^y z$。其中的 $x$ 与 $y$ 可以随便求。（$z$ 不用管它，因为它对我们的解题及贡献没有任何作用）

考虑这个问题。我们的答案取决于最后我们选出的 $k$ 个数 $x$ 与 $y$ 的总和的最小值，即 $\min(\sum x,\sum y)$。如果我们把 $x_i$ 抽象成价值，$y_i$ 抽象成费用。这道题难道不就是一个背包了吗？

注：关于不使用 $y_i$ 为价值，$x_i$ 为费用的原因是因为这样会稍微慢一些。

定义 $dp_{i,j,k}$ 为前 $i$ 个数中选取 $j$ 个数，选取的数中 $\sum y=k$。

用背包的方法去转移它。分类讨论：

- 如果不选，直接继承上一次的状态，$dp_{i,j,k}=dp_{i-1,j,k}$；   
- 如果选，由上一次的状态转移，$dp_{i,j,k}=\max \{ dp_{i-1,j-1,k-y_i}+x_i\} $，条件：$j>0,k \geq y_i$（费用足够，选择数不为 $0$）并且上一个转移点存在（或者说，合法？）。

答案即为：

$$\displaystyle \max_{i=0}^{\sum_{j=1}^n y_i} \{ \min(i,dp_{n,K,i})\}$$

哦对了这样会 MLE，注意开个滚动数组。

另外谁能告诉我为什么我枚举下一个状态会 WA 掉啊（（（

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
struct node{
	LL t,f;
	node(){t=f=0;}
	node(LL T,LL F){t=T,f=F;}
}p[205];
LL n,k,a[205],dp[2][205][5005];
int main(){
	cin>>n>>k;
	for(LL i=1;i<=n;++i)
	{
		cin>>a[i];
//		if(!(a[i]%2==0 || a[i]%5==0))	--n,--i;
	}
	for(LL i=1;i<=n;++i)
	{
		LL t=0,f=0;
		while(a[i]%2==0)	++t,a[i]/=2;
		while(a[i]%5==0)	++f,a[i]/=5;
		p[i]=node(t,f);
	}
	memset(dp,-1,sizeof dp);
	dp[0][0][0]=0;
	LL up=0;
	for(LL i=1;i<=n;++i)
	{
		LL now=i&1;
		up+=p[i].f;
		for(LL j=0;j<=min(i,k);++j)
		{
			for(LL l=0;l<=up;++l)
			{
				dp[now][j][l]=dp[now^1][j][l];
				if(j && l>=p[i].f && ~dp[now^1][j-1][l-p[i].f])	dp[now][j][l]=max(dp[now][j][l],dp[now^1][j-1][l-p[i].f]+p[i].t);
			}
		}
	}
	LL ans=0;
	for(LL i=0;i<=up;++i)	ans=max(ans,min(i,dp[n&1][k][i]));
	cout<<ans;
	return 0;
}
```

---

## 作者：crn1 (赞：1)

## 题目大意
给出 $n$ 个数，从中选择 $k$ 个数，是其乘积末尾的 $0$ 最多，求最多的 $0$ 的个数。

## 题解
因为 $10 = 2\times 5$，所以求 $k$ 个数乘积末尾 $0$ 的个数，其实就是求选出 $k$ 个数，使得 $2$ 和 $5$ 配对个数最多。

设 $\mathrm{dp}$ 状态 $f[j][k]$ 表示选择 $j$ 个数，包含 $k$ 个质因子 $5$，质因子 $2$ 最多有多少个。$a_i,b_i$ 分别表示第 $i$ 个数的 $5$ 和 $2$ 的质因子个数，转移方程为 $f[j][k]=max(f[j][k],\ f[j-1][k - a[i]]+b[i])$。( 注意 $j$ 和 $k$ 都要倒序遍历 )

因为最多包含 $\log_{5}10^{18}\times200\approx5150$ 个质因子 $5$，所以 $k$ 最大为 $5150$。

最后遍历质因子 $5$ 的个数，求出最终答案。

## 代码
```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#define ll long long

const int N = 205, M = 5152;
int a[N], b[N], f[N][M + 5];

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		ll x; scanf("%lld", &x);
		while (x % 5 == 0) a[i]++, x /= 5; // 求质因子 5 的个数
		while (x % 2 == 0) b[i]++, x /= 2; // 求质因子 2 的个数
	}
	memset(f, -0x3f, sizeof f);
	f[0][0] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = i; j; j--)
			for (int k = M; k >= a[i]; k--)
				f[j][k] = std::max(f[j][k], f[j - 1][k - a[i]] + b[i]);
	int ans = 0;
	for (int i = M; i; i--) ans = std::max(ans, std::min(f[m][i], i));
	printf("%d", ans);
	return 0;
}
```

---

## 作者：linaonao (赞：1)

## 思路讲解
可以用背包的思维去理解。

首先我们知道末尾的 $0$ 是由数字中因数$2$和$5$相乘得来的，所以用背包或$dp$解决就很显然了：

按找这类题的思路，我们会有一维记录到底几个数一维记录用了几个，所以$dp[i][j][k]$表示到第$i$个数，使用了$j$个数，且已经有$k$个$2$因数时去到多少$5$因数，而这里则有点背包思维，将$2$的数量看做重量，$5$的数量看做价值。

递推式就是：
```cpp
dp[i][j][k]=max(dp[i-1][j][k],dp[i][j][k]);
dp[i][j][k]=max(dp[i-1][j-1][k-num2]+num5,dp[i][j][k]);
```

关于$i$这一维我们可以直接滚掉。

关于$k$这一维我的处理方法是保险起见直接上$10^{18}$关于$2$的对数值作为2的个数，再乘数字个数。

最后贴上代码：
## 代码

```cpp
#include<bits/stdc++.h>
#define int long long//超级懒惰 
template<typename T>inline void read(T &x){
	T f=0;x=0;char ch=getchar();
    for(;!isdigit(ch);ch=getchar())f|=ch=='-';
    for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    x=f?-x:x;
}
template<typename T>inline void write(T x){
	if(x<0){putchar('-');x=-x;}
	if(x>9)write(x/10);
	putchar(x%10+48);
}//快读快写板子 
using namespace std;
inline int getnum(int n,int p){
	int cnt=0;
	while(n%p==0){n/=p;++cnt;}
	return cnt;
}//统计n中因数p的个数 
int dp[2][205][60*200+5];//log(10)/log(2)*18约等于60，这里是保险起见直接用10^18关于2的对数防止RE 
int a[205],n,kkk;//用kkk做变量名没问题吧（逃 
int sum2,ans;//统计至此为止因数2的个数和答案 
signed main(){ 
	memset(dp,-1,sizeof(dp)); dp[0][0][0]=0;//因为要做后面有dp>=0的询问所以初值设为-1,而dp[0][0][0]显然为0 
	read(n),read(kkk);
	for(int i=1;i<=n;++i) read(a[i]);
	int gg=1;//滚掉一维数组 
	for(int i=1;i<=n;++i){
		int num2=getnum(a[i],2),num5=getnum(a[i],5);sum2+=num2;
		for(int j=0;j<=i&&j<=kkk;++j){
			for(int k=0;k<=sum2;++k){
				dp[gg][j][k]=max(dp[gg^1][j][k],dp[gg][j][k]);//见上面的讲解 
				if(j>=1&&k>=num2&&dp[gg^1][j-1][k-num2]>=0){
					dp[gg][j][k]=max(dp[gg^1][j-1][k-num2]+num5,dp[gg][j][k]);
				}
			}
		}
		gg^=1;
	} 
	for(int i=0;i<=sum2;++i){
			ans=max(ans,min(i,dp[gg^1][kkk][i])); 
	}
	write(ans);
	return 0;
}//完成！ 
```


---

## 作者：derta (赞：1)

[CF837D Round Subset](https://www.luogu.com.cn/problem/CF837D)

首先，设 $2^{p_i} \mid a_i,2^{p_i+1} \nmid a_i$ 且 $5^{q_i} \mid a_i,5^{q_i+1} \nmid a_i$

那么问题转化为：选 $k$ 组数，设编号分别是 $d_1,d_2,d_3,\cdots,d_k$，你需要求出

$$\max\{\min(\sum_{i=1}^{k}p_{d_i},\sum_{i=1}^{k}q_{d_i})\}$$

考虑 dp：设 $f_{i,j,l}$ 为前 $i$ 个数中选 $j$ 个的 $\sum_{t=1}^{j}q_{d_t}$ 之和为 $l$ 时 $\sum_{t=1}^{j}p_{d_t}$ 的最大值，那么有转移方程

$$f_{i,j,l}=\max(f_{i-1,j,l},f_{i-1,j-1,l-q_i}+p_i)$$

初始化 $f_{i,0,0}=0$，$f_{i,j,l}=-\infty$

最后滚动数组滚掉一维，否则 `memset0` 很耗时间（

```cpp
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
const int MAXN = 205, MAXK = 205, MAXlog5A = 6005;
int f[MAXK][MAXlog5A], ans;
int n, k, p[MAXN], q[MAXN];
long long a;

inline int Min(int x, int y)
{ return x < y ? x : y; }

inline int Max(int x, int y)
{ return x > y ? x : y; }

int main() {
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; ++i) {
		scanf("%lld", &a);
		while((a & 1) == 0) { //求p 
			++p[i];
			a >>= 1;
		}
		while(a%5 == 0) { //求q 
			++q[i];
			a /= 5;
		}
	}
	memset(f, CHAR_MIN, sizeof(f)); //初始化 
	f[0][0] = 0; //边界 
	int limit, sum = 0;
	for(int i = 1; i <= n; ++i) {
		limit = Min(i, k);
		sum += q[i];
		for(int j = limit; j >= 1; --j)
			for(int l = sum; l >= q[i]; --l)
				f[j][l] = Max(f[j][l], f[j - 1][l - q[i]] + p[i]); //转移 
	}
	for(int i = 1; i <= limit; ++i) //统计答案 
		for(int j = 0; j <= sum; ++j)
			ans = Max(ans, Min(f[i][j], j));
	printf("%d", ans);
	return 0;
}
```

---

## 作者：nofind (赞：1)

题意：https://www.luogu.org/problem/CF837D

综合了DP设计状态套路的一道题

显然一个数后面0的个数是它质因数分解后2和5的个数中取个min(其实肯定是5的个数)

设$f[i][j][k][u]$表示选了前i个数中j个数,质因数分解后有k个2,u个5,是否存在

显然要删减状态

按照背包滚动数组将i那维删了,再将一维记入状态中

$f[j][k]$表示选j个数,质因数中5有k个,质因数中2最多有几个

对每个数求出只有质因数分解后2和5的个数,正常背包即可

code:
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=210;
const int maxm=210;
const int logsize=60;
const int nlogsize=maxn*logsize;
int n,m,ans;
int a[maxn],cnt2[maxn],cnt5[maxn];
int f[maxm][nlogsize];
signed main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)
	{
		int tmp=a[i];
		while(tmp%2==0)cnt2[i]++,tmp/=2;
		while(tmp%5==0)cnt5[i]++,tmp/=5;
	}
	memset(f,0xcf,sizeof(f));f[0][0]=0;
	for(int i=1;i<=n;i++)
		for(int j=m;j>=1;j--)
			for(int k=10000;k>=cnt5[i];k--)
				f[j][k]=max(f[j][k],f[j-1][k-cnt5[i]]+cnt2[i]);
	for(int i=0;i<=10000;i++)ans=max(ans,min(i,f[m][i]));
	printf("%lld",ans);
	return 0;	
}
```



---

## 作者：long_long (赞：0)

这是又一道DP题。而且还是CFDP题。
# 题目大意：

我们把一个数的 roundness 值定义为它末尾 0 的个数。

给你一个长度为 n 的数列，要求你从中选出 k 个数，使得这些选出的数的积的 roundness 值最大。

举几个例子：

在第一个例子中，有三种选法。[50,4][50,4] 的积是 200，roundness 值是 2；[4,20][4,20] 的积是 80，roundness 值是 1；[50,20][50,20] 的积是 1000，roundness 值是 3。

第二个例子中选法 [15,16,25][15,16,25] 的积是 6000，roundness 值是 3。

第三个例子中所有的选法的积的 roundness 值都是 0。

# 思路：

这道题用DP可以（暴力也行吧）。

请看代码注释。

# 代码：

```
#include<iostream>
#include<cstring>
using namespace std;
int a[255],b[255],dp[255][10005];
int ans;
int main(){
	memset(dp,-1,sizeof(dp));//初始化
	int n,k;
	cin>>n>>k;//输入
	for(int i=1;i<=n;i++){
		long long x;
		cin>>x;//输入，不必保存
		while(x%2==0){//统计
			a[i]++;
			x/=2;
		}
		while(x%5==0){//统计
			b[i]++;
			x/=5;
		}
	}
  	//核心代码开始
	dp[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=k;j>=1;j--){
			for(int h=10000;h>=b[i];h--){
				if(dp[j-1][h-b[i]]!=-1){
					dp[j][h]=max(dp[j][h],dp[j-1][h-b[i]]+a[i]);//动态转移
				}
			}
		}
	}
  	//核心代码结束
	for(int i=0;i<=10000;i++){
		ans=max(ans,min(i,dp[k][i]));
	}//统计最大roundness值
	cout<<ans<<endl;//输出
	return 0;//华丽结束
}
```


---

## 作者：littleseven (赞：0)

# CF 837D Round Subset

**题目链接：**[洛谷 CF 837D Round Subset](https://www.luogu.org/problem/CF837D)		[CF 837D Round Subset](https://codeforces.com/problemset/problem/837/D)

**算法标签:**  `DP`、`思维`

## 题目描述：

我们定义一个数的幸运值是这个数末尾 $0$ 的个数，

给你一个长度为 $n$ 的数列，在这个数列中选出来 $k$ 个数，使得选出来的所有数的积的幸运值最大。

## 题解：

考场上 $yy$ 贪心，卡过去两个点，后来改 DP RE7个点，我真棒（%……&#￥%&￥%……￥……*）

现在开始口胡正解：

**DP**

首先在看完题之后一定可以发现，这道题和每个数分解质因数之后 $2$ 和 $5$ 的因数个数有关系，之后考虑怎么做。

这道题考场上和旁边巨佬有那么~~小声且友好又和平的~~交流了几句，算上正解，我们搞出了两种解法（DP状态）：

- $dp[i][j][k]$ 为当前是第 $i$ 个，选出了 $j$ 个 $2$，选出了 $k$ 个 $5$ 的方案数。
- $dp[i][j][k]$ 为当前是第 $i$ 个，选出了 $j$ 个数，并且有 $k$ 个 $5$ 时候选出来 $2$ 的个数。

##### 我们来分析一下这两种的问题：

​	按照数据范围来看，我们有 $200$ 个`longlong`，每一个`longlong`最大可以存下 $2^{63}-1$ ，那么分解完质因数就至少有 $62$ 个 $2$，那么我们要枚举所有 $2$ 的情况，当然就是 $200 \times 62 = 12400$ 种。那么对于 $5$ 来说，测试之后大概一个`longlong`可以存下 $30$ 个左右，那么就是 $200 \times 30 = 6000$ 种。

​	如果使用第一种，我们需要在第二维中跑这 $12400$ 种情况，又在第三维中跑这 $6000$ 种情况，显然办不到。

​	如果使用第二种，我们第三维要选择 $5$ ，更简单计算，并且数组可以开的下，如果选择有 $k$ 个 $2$ 的话就很危险。

##### 下面再来考虑如何转移：

​	我们考虑枚举的顺序，首先枚举当前是第几个数字，这是 $i=1 \rightarrow n$ 。之后是当前选择的个数 $j=1 \rightarrow i$，最后是当前选择 $5$ 的个数 $p=6200 \rightarrow five[i]$。

​	那么显然，如果选这个数，那么就从选择的个数为 $j-1$ ，并且选择 $5$ 的个数 $p-five[i]$来转移到当前这个位置。

​	所以转移方程就是：

​										$\boxed{dp[j][p] = max(dp[j][p], dp[j-1][p-five[i]]+two[i])}$

##### 最后考虑答案：

​	答案一定是某一个 $min(p, dp[j][p])$ ，这代表 $2$ 的个数和 $5$ 的个数当中取最小的就是末尾 $0$ 的个数。由于我们的限定条件，我们会发现 $j \le k$，而且$1\le p \le 6200$。所以只需要循环找到答案的最大值就可以。

## AC代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define setI(x) freopen(x".in", "r", stdin); 
#define setO(x) freopen(x".out", "w", stdout); 
#define setIO(x) setI(x) setO(x)

int n, k, ans;

int dp[220][6500];

struct Node {
	ll num;
	int two, five;
} node[220];

void deal(int x) {
	ll now = node[x].num;
	while (now % 2 == 0) {
		now /= 2;
		node[x].two ++ ;
	}
	while (now % 5 == 0) {
		now /= 5;
		node[x].five ++ ;
	}
}

int main() {
// setIO("dynamic-programming")

	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i ++ ) {
		scanf("%lld", &node[i].num);
		deal(i);
	}
	// puts("1");
	memset(dp, -0x3f, sizeof dp); 	
	dp[0][0] = 0;
	for (int i = 1; i <= n; i ++ ) {
		for (int j = i; j >= 1; j -- ) {
			for (int p = 6200; p >= node[i].five; p -- ) {
				dp[j][p] = max(dp[j][p], dp[j - 1][p - node[i].five] + node[i].two);
			}
		}
	}
	for (int i = 1; i <= k; i ++ ) {
		for (int j = 6200; j >= 1; j -- ) {
			ans = max(ans, min(j, dp[i][j]));
		}
	}
	printf("%d\n", ans);
	return 0;
	
}
```

---

