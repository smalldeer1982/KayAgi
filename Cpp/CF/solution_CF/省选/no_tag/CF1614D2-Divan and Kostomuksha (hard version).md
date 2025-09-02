# Divan and Kostomuksha (hard version)

## 题目描述

This is the hard version of the problem. The only difference is maximum value of $ a_i $ .

Once in Kostomuksha Divan found an array $ a $ consisting of positive integers. Now he wants to reorder the elements of $ a $ to maximize the value of the following function: 
$$ \sum_{i=1}^n \operatorname{gcd}(a_1, \, a_2, \, \dots, \, a_i), $$
where $ \operatorname{gcd}(x_1, x_2, \ldots, x_k) $  denotes the [greatest common divisor](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers  $ x_1, x_2, \ldots, x_k $ , and  $ \operatorname{gcd}(x) = x $  for any integer  $ x$.

Reordering elements of an array means changing the order of elements in the array arbitrary, or leaving the initial order.

Of course, Divan can solve this problem. However, he found it interesting, so he decided to share it with you.

## 说明/提示

In the first example, it's optimal to rearrange the elements of the given array in the following order: $ [6, \, 2, \, 2, \, 2, \, 3, \, 1] $ :

 $\operatorname{gcd}(a_1) + \operatorname{gcd}(a_1, \, a_2) + \operatorname{gcd}(a_1, \, a_2, \, a_3) + \operatorname{gcd}(a_1, \, a_2, \, a_3, \, a_4) + \operatorname{gcd}(a_1, \, a_2, \, a_3, \, a_4, \, a_5) + \operatorname{gcd}(a_1, \, a_2, \, a_3, \, a_4, \, a_5, \, a_6) = 6 + 2 + 2 + 2 + 1 + 1 = 14. $
 
It can be shown that it is impossible to get a better answer.

In the second example, it's optimal to rearrange the elements of a given array in the following order:  $ [100, \, 10, \, 10, \, 5, \, 1, \, 3, \, 3, \, 7, \, 42, \, 54]$.

## 样例 #1

### 输入

```
6
2 3 1 2 6 2```

### 输出

```
14```

## 样例 #2

### 输入

```
10
5 7 10 3 1 10 100 3 42 54```

### 输出

```
131```

# 题解

## 作者：Blunt_Feeling (赞：11)

## CF1614D2 Divan and Kostomuksha 题解

给定一个序列 $a$，定义其权值为：

$$\sum_{i=1}^n\gcd(a_1,a_2,...,a_i)$$

要使重排后的权值最大。

可以发现，这个权值是由 $n$ 个最大公因数的值加起来获得的。这说明这个权值只与 $a_i$ 的因数有关。所以可以把 $a_1\sim a_n$ 的所有因数离散出来，设计 DP 使所有因数的贡献最大。

考虑从大因数枚举到小因数，$f_i$ 表示到因数 $i$ 为止使用过的所有因数贡献的 $\gcd$ 之和的最大值。

$f_i$ 的初始值为 $i\times num_i$，$num_i$ 为因数 $i$ 在原数列中出现的总次数。接着枚举质数，构造所有可能的含 $i$ 为因子的数，设这个数为 $k\leftarrow i\times prime_j$，算出（新的含有因子 $i$，但不含有因子 $i\times prime_j$ 的数的个数）$\times$ 因数 $i$ 的值为贡献，加上 $f_k$，取 $\max$ 进行转移。表示为状态转移方程为：

$$f_i=\max f_k+(num_i-num_k)\times i$$

如果 $num_i=n$，就更新 $ans$，此时 $n$ 个原数都含有因数 $i$。

### Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
inline int read() {
	char c=getchar();int x=0;bool f=0;
	for(;!isdigit(c);c=getchar())f^=!(c^45);
	for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
	if(f)x=-x; return x;
}
const int maxn=2e7+50;
int n,Big,prime[10000010],cnt=0,num[maxn]; //num开桶存放所有因数
ll f[maxn],ans=0;
bool isprime[maxn];
void getprime(int x) //质数筛
{
	memset(isprime,true,sizeof(isprime));
	isprime[1]=false;
	For(i,2,x)
	{
		if(isprime[i]) prime[++cnt]=i;
		for(int j=1;prime[j]*i<=x;j++)
		{
			isprime[i*prime[j]]=false;
			if(i%prime[j]==0) break; //质数筛的关键
		}
	}
}
signed main()
{
	n=read();
	For(i,1,n)
	{
		int x=read();
		Big=max(Big,x); //求阈值
		int sqrtx=sqrt(x);
		For(j,1,sqrtx)
			if(x%j==0)
			{
				++num[x/j];
				if(j*j!=x) ++num[j];
			}
	}
	getprime(Big);
	Rep(i,Big,1) //i枚举所有可能的因数
	{
		if(num[i]) f[i]=1ll*i*num[i];
		for(int j=1;j<=cnt&&prime[j]*i<=Big;j++) //枚举质数构造所有含i为因子的数且不重复
			f[i]=max(f[i],f[i*prime[j]]+1ll*(num[i]-num[i*prime[j]])*i); //状方
			//从i*prime[j]推过来，(新增的符合含有因子i但不含有因子i*prime[j]的数的个数)*新的因数i
		if(num[i]==n) ans=max(ans,f[i]); //n个数都含有因数i，一般i已经较小了
	}
	cout<<ans<<endl;
	return 0;
}
```
感谢 @[jun头吉吉](https://www.luogu.com.cn/user/174304) 的代码帮助。分析过程均为小蒟蒻自己推出，如有不对之处请帮忙指出。

---

## 作者：DaiRuiChen007 (赞：8)

# CF1614D2 题解

## 题目大意

给定一个有 $n$ 个数的数组 $a$，现在可以让你任意重排这个 $a$ 数组，请求出 $\sum_{i=1}^{n}\gcd(a_1,a_2,\dots,a_i)$ 的最大值。

数据范围保证：$n\le2\times10^7,a_i\le 2\times 10^7$。

## 思路分析

约定用 $x$ 表示满足 $\gcd(a_1,a_2,\dots,a_x)>1,\gcd(a_1,a_2,\dots,a_{x+1})=1$ 的 $x$， $w=\max(a_i)\le2\times 10^7$，表示 $a$ 的值域。

显然本题考虑 dp，用 $dp_i$ 表示重排 $a$ 后满足 $i\mid \gcd(a_1,a_2,\dots,a_x)$ 时 $\sum_{i=1}^x \gcd(a_1,a_2,\dots,a_x)$ 的最大值。

用 $cnt_i$ 表示 $a$ 中满足 $i\mid a_i$ 数的个数。

那么 dp 的边界条件就应该是 $dp_i=i\times cnt_i$，因为最开始的时候肯定是把 $cnt_i$ 个 $i$ 的倍数放在最前面，其他的贡献还没有考虑。

然后考虑 dp 的状态转移，状态转移方程应该是：
$$
dp_i=\max_{i\mid j}^{j\le w} (dp_j+i\times(cnt_i-cnt_j))
$$
这个方程的含义是，从每个 $i$ 的倍数 $j$ 处转移，考虑前面填的数的 $\gcd$ 是 $i$ 的某个倍数的情况（也就是 $dp_j$ ），再加上后面 $a$ 中所有满足 $i \mid x$ 且 $j\not \mid x$ 的数放在后面，这部分的数的 $\gcd$ 是 $i$，而一共有 $cnt_i-cnt_j$ 个，这就是状态转移方程的含义。

然后考虑统计答案，$dp_i$ 可能成为答案的充分必要条件是其对应的 $x=n$，也就是 $cnt_i=n$。

所以可以写出统计答案的式子：
$$
ans=\max_{i=1} (dp_i\times[cnt_i=n])
$$


这个做法的时间复杂度分为两部分。

1. 读入并预处理 $cnt$ 数组，复杂度 $\Theta(n\sqrt{w})$。
2. 进行 dp 的状态转移，复杂度 $\Theta(\sum_{i=1}^w\dfrac{w}{i})=\Theta(w\ln w)$。

总的时间复杂度是 $\Theta(n\sqrt w+w\ln w)$，本题会 TLE ~~（不过你卡常好的话是可以 AC 的）~~。

考虑对状态转移方程进行优化，注意到每次转移都要枚举所以 $i$，的倍数，比较麻烦，注意到每个数都可以分解冲若干个质数之积，所以每次转移时只需要考虑质数，而其他的已经在之前考虑过了，那么优化过的状态转移方程如下：（$\mathbb{P}$表示全体质数集）
$$
dp_i=\max_{p\in\mathbb{P}}^{i\times p\le w}(dp_{i\times p}+i\times(cnt_i-cnt_{i\times p}))
$$
优化后状态转移的复杂度变成了 $\Theta(w\log\log w)$，总的时间复杂度优化到了 $\Theta(n\sqrt w+w\log\log w)$ 可以通过本题。

注意，这里如果全部开 `long long` 会超时。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+1,MAXV=2e7+1;
vector <int> p; //p里面是所有质数 
bool isc[MAXV]; 
int a[MAXN],cnt[MAXV],n,w;
long long dp[MAXV],ans; //注意开long long 
signed main() {
	for(register int i=2;i<MAXV;++i) {
		//筛出值域内所有素数，线性筛预处理 
		if(!isc[i]) p.push_back(i);
		for(register int j=0;j<p.size()&&i*p[j]<MAXV;++j) {
			isc[i*p[j]]=true;
			if(i%p[j]==0) break;
		}
	}
	scanf("%d",&n);
	for(register int i=1;i<=n;++i) {
		scanf("%d",&a[i]);
		w=max(w,a[i]);
		for(register int j=1;j*j<=a[i];++j) {
			if(a[i]%j==0) {
				//预处理a[i]的每个因数并统计进cnt里面 
				++cnt[j];
				if(j*j<a[i]) ++cnt[a[i]/j];
			}
		}
	}
	for(register int i=w;i>0;--i) {
		dp[i]=(long long)i*(long long)cnt[i]; //dp边界条件 
		if(dp[i]) {  
		//剪枝，如果本身cnt[i]=0也就是没有i的倍数就不考虑 
			for(register int j=0;j<p.size()&&i*p[j]<=w;++j) {  
				//考虑乘上每个质数 
				if(dp[i*p[j]]) {
					dp[i]=max(dp[i],dp[i*p[j]]+(long long)i*((long long)cnt[i]-(long long)cnt[i*p[j]]));
				}
			}
		}
		if(cnt[i]==n) ans=max(ans,dp[i]); //统计答案 
	}
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：laboba (赞：8)

观察数据范围，盲猜dp状态只与值域 $MaxA$ 有关。事实上同时和 $n$  及值域相关不太可能，而只跟 $n$ 有关重排这件事是非常难处理的，所以最后的状态是设 $f_i$ 表示最后一个 $gcd$ 是 $i$ 时的最大值，其中 $n$ 个数不一定都用完。

设重排后的序列为 $q$ ，经过分析可以贪心出这样一个性质：对任意 $gcd(q_1,q_2,...,q_i)$ ， $q_{i+1},q_{i+2}...,q_n$ 均不是它的倍数。感性理解下，$gcd$ 序列显然是单调不增的，如果有一个 $j>i$ 满足 $q_j$ 是前 $i$ 个数 $gcd$ 的倍数，把 $j$ 放到 $i+1$ 位结果只增不减。

于是根据这个性质，转移方程可以得出：$f_i=max(f_j+(num_i - num_{j})\times i),i\mid j$ 其中 $num$ 表示 $a$ 中能被 $i$ 整除的数的个数。方程的含义是枚举上一个不同于 $i$ 的 $gcd$ 为 $j$，设  $gcd(q_1,q_2....,q_k)=j$，则在 $j+1$ 至 $f_i$ 所在位置全部填上 $a$ 中是 $i$ 的倍数但不是 $j$ 的倍数的数，这段的贡献是 $(num_i - num_{j})\times i$。

这时复杂度是 $O(MaxA\times log(MaxA))$ 只能通过easy version 。考虑优化式子，发现对于 $f_i$ ，我们只用从 $i$ 的质数倍考虑就可以了，因为 $i$ 其他倍数的 $f$ 值都已经更新到 $i$ 的质数倍的 $f$ 中过了。然后关于 $num$ 的统计，直接对每个 $a_i$ 枚举因数是 $O(n \sqrt {MaxA})$ 的，4s时限实测能过，当然也可以分解质因数进一步优化。

UPD:修改了一处笔误

```cpp
#include<cstdio>
#include<algorithm> 
using namespace std;
const int N=100100,A=20001000;
int a[N],num[A],v[A],q[A];
long long f[A];
int n;
int main(){
	scanf("%d",&n);
	int m=0,tot=0;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),f[a[i]]+=a[i],m=max(m,a[i]);
	for(int i=2;i<=m;i++){//筛素数 
		if(v[i]==0)q[++tot]=i,v[i]=i;
		for(int j=1;j<=tot&&q[j]<=v[i]&&q[j]*i<=m;j++)v[q[j]*i]=q[j];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j*j<=a[i];j++){
			if(a[i]%j)continue;
			num[j]++;
			if(j*j!=a[i])num[a[i]/j]++;
		}
	}
	for(int i=m;i>=1;i--){
		for(int j=1;q[j]*i<=m&&j<=tot;j++){
			f[i]=max(f[i],f[q[j]*i]+1ll*(num[i]-num[q[j]*i])*i);
		}
	}
	long long ans=0;
	for(int i=1;i<=m;i++)ans=max(ans,f[i]);
	printf("%lld",ans);
}
```


---

## 作者：daniEl_lElE (赞：4)

[话 接 上 文（没看过的及其建议看一下，本篇只讲优化）：](https://www.luogu.com.cn/blog/116664/CF1614D1-tijie)

## 思路

考虑如何优化。

对于第一个部分（即计算 $cnt$ 数组），有一个东西叫做[狄利克雷前缀和](https://www.luogu.com.cn/problem/P5495)，这个东西就可以在 $O(n\log\log n)$ 的复杂度内计算我们所需要的。具体实现是对于每个素数做一遍后缀和（原题为前缀和），相当于一种高维后缀和。

第二部分，我们发现转移给 $i$ 时从 $ij$ 转移（$j\not\in \mathbf{P}$）总是不划算的，因为假设 $j=j_1\times j_2,j_1,j_2\not=0$，可以将 $ij$ 转移到 $ij_1$ 再转移到 $i$，就算 $cnt_{ij_1}=cnt_{ij}$ 也不会因此减少贡献。于是我们转移时枚举素数即可。

第二部分转化一下发现其实他也是 $\sum_{i\in\mathbf{P}}\frac{m}{i}=O(n\log\log n)$ 的。故总复杂度为 $O(n\log\log n)$，可以通过。

你放心，四秒呢。

## 代码

```cpp
#include <bits/stdc++.h>
#define double long double
#define int long long
using namespace std;
int cnt[20000005];
int f[20000005];
bool isp[20000005];
int prm[20000005],tot;
signed main(){
	for(int i=2;i<=20000000;i++) isp[i]=1;
	for(int i=2;i<=20000000;i++){
		if(isp[i]){
			prm[++tot]=i;
			for(int j=i*2;j<=20000000;j+=i){
				isp[j]=0;
			}
		}
	}
	int n;
	cin>>n;
	int a[n+1];
	for(int i=1;i<=n;i++) cin>>a[i],cnt[a[i]]++;
	for(int i=1;i<=tot;i++){
		for(int j=20000000/prm[i];j>=1;j--){
			cnt[j]+=cnt[j*prm[i]];
		}
	}
	for(int i=20000000;i>=1;i--){
		f[i]=cnt[i]*i;
		for(int j=1;prm[j]*i<=20000000&&j<=tot;j++){
			f[i]=max(f[i],(cnt[i]-cnt[prm[j]*i])*i+f[prm[j]*i]);
		}
	}
	cout<<f[1];
	return 0;
} 
```

---

## 作者：sanwei (赞：3)

## CF1614D2 题解

~~反正我现场没写出来~~

### 题目大意

给你一个长度为 $n$ 的序列 $A$。定义长度同为 $n$ 序列 $B$，其中 $b_i=\gcd(a_1,a_2\cdots a_i)$。

现在你可以重新排列 $A$，即打乱它。定义此时 $A$ 的价值 $V=\sum_{1\le i \le n} b_i$ 求 $V$ 的最大值。

### 数据范围

$1\le n\le 10^5$

$1\le a_i\le 2\times 10^7$

### 题目分析

性质1：观察 $B$ 序列，容易发现 $B$ 序列是单调不增的，而且满足 $b_{i}|b_{i-1}$。

性质2：如果 $b_i\ne b_{i+1}$，且存在 $b_i|a_j,j>i$，那么将 $a_j$ 插入 $a_i$ 前，一定会使 $V$ 更大。

那么设计 dp 状态：$dp_i$ 表示此时 $B$ 序列**一个前缀**的末尾为 $i$，$V$ 的最大值。

设 $cnt_i$ 表示 $A$ 序列中，以 $i$ 为因数的数量。那么 $cnt_i=\sum_{i\times j \le maxA}cnt_{i\times j}$。

那么转移方程便是：
$$
\large dp_i=\max_{i\times j\le maxA}\{ dp_{i\times j}+i\times(cnt_i-cnt_{i\times j}) \}
$$

对转移方程的理解：

将重排操作看做把元素全部取出来后一个个放回去。

转移所对应的：将所有 $a_x$ 满足 $i|a_x$ 放到此时的序列结尾，有 $cnt_i-cnt_{i\times j}$ 个，每一个的贡献为 $i$。

明显的，转移的复杂度是一个调和级数。

至此，复杂度为 $O(A \log A)$（其中 $A$ 表示值域），可以通过 CF1614D1（D1 与 D2 唯一的不同点是 D1 中 $1\le a_i\le 5\times 10^6$）

code：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1e5+100;
const int MAXA=2e7+100;
int N,a[MAXN];
ll cnt[MAXA];
const int A=5e6;
ll dp[MAXA];
int main(void){
	scanf("%d",&N);
	for(int i=0;i<N;++i)scanf("%d",a+i),cnt[a[i]]++;
	for(int i=1;i<=A;++i)
		for(int j=2;i*j<=A;++j)
            cnt[i]+=cnt[i*j];
	for(int i=A;i>=1;--i){
		dp[i]=1ll*cnt[i]*i;
		for(int j=2;i*j<=A;++j)
			dp[i]=max(dp[i],dp[i*j]+1ll*i*(cnt[i]-cnt[i*j]));
	}
	printf("%lld",dp[1]);
	return 0;
}
```



当你信心满满的把这份代码提交时，你会~~惊讶的~~发现他 TLE 了。接下来开始优化。

dp 转移的过程中，容易发现，可能会出现这种情况：$dp_i$ 被 $dp_{2i}$ 更新了，又被 $dp_{4i}$ 更新了。实际上这是个冗余的转移。而且 $n$ 的数量只有 $10^5$，会出现很多 $cnt_i-cnt_{i\times j}=0$ 的情况。

所以~~容易~~想到，调和级枚举的时候，**只**对**质数**进行转移。

更改转移方程：
$$
\large dp_i=\max_{i\times j\le maxA,\ j\ is \ a \ prime}\{ dp_{i\times j}+i\times(cnt_i-cnt_{i\times j}) \}
$$

此时 dp 转移的复杂度成功降至 $O(A \log \log A)$（其中 $A$ 表示值域），可以通过本题。

需要注意的是，cnt 的求解也需要进行更改，方法类似，详细过程可以参考代码。

code：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1e5+100;
const int MAXA=2e7+100;
int N,a[MAXN];
ll cnt[MAXA];
const int A=2e7;
ll dp[MAXA];
bool is[MAXA];
vector<int>prm; 
int main(void){
	scanf("%d",&N);
	for(int i=0;i<N;++i)scanf("%d",a+i),cnt[a[i]]++;
	for(int i=2;i<=A;++i)if(!is[i]){
		prm.push_back(i);
		for(int j=2;i*j<=A;++j)is[i*j]=1;
	}
	for(int j=0;j<prm.size();++j)
		for(int i=A/prm[j];i>=1;--i)
            cnt[i]+=cnt[i*prm[j]];
	for(int i=A;i>=1;--i){
		dp[i]=1ll*cnt[i]*i;
		for(int j=0;j<prm.size()&&i*prm[j]<=A;++j)
			dp[i]=max(dp[i],dp[i*prm[j]]+1ll*i*(cnt[i]-cnt[i*prm[j]]));
	}
	printf("%lld",dp[1]);
	return 0;
}
```




---

## 作者：orz_z (赞：2)

## 题目大意

给定序列 $a_1,a_2,...,a_n$，要求重排 $a$，使得

$$
\sum\limits_{i=1}^n \gcd(a_1,a_2,...,a_i)
$$



最大。

输出这个最大值。

## 解题思路

显然，一道 `dp`。

设 $cnt_i$ 表示数组 $a$ 中是 $i$ 的倍数的元素个数，$dp_i$ 表示时能得到已含有因数 $i$ 结尾排列能获得的最大值。

此时有转移方程
$$
dp_i=\max_{j=1}{f_{i \times pri_j} + i \times (cnt_i - cnt_{i \times pri_j})}
$$
最后答案为满足 $cnt_i=n$ 的 $dp_i$ 的最大值。

求 $cnt$ 可先筛出所有质数，再枚举 $i$ 和质数集 $pri$，计算 $cnt_i$。

时间复杂度 $\mathcal O(w \log \log w)$，其中 $w$ 为值域。

具体实现见代码。

## CODE

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * f;
}

const int _ = 2e7 + 1;

int n;

int ans;

int cnt[_ + 7];

int dp[_ + 7];

bool vis[_];

vector<int> primes;

void init()
{
    for (int i = 2; i < _; ++i)
    {
        if (!vis[i])
            primes.push_back(i);
        for (auto p : primes)
        {
            if (p * i > _)
                break;
            vis[p * i] = 1;
            if (i % p == 0)
                break;
        }
    }
}

signed main()
{
    init();
    n = read();
    for (int i = 1, x; i <= n; ++i)
        cnt[read()]++;
    for (auto p : primes)
        for (int j = _ / p; j >= 1; --j)
            cnt[j] += cnt[j * p];
    for (int i = _ - 1; i >= 1; --i)
    {
        dp[i] = cnt[i] * i;
        for (auto p : primes)
        {
            int j = p * i;
            if (j > _)
                break;
            dp[i] = max(dp[i], dp[j] + i * (cnt[i] - cnt[j]));
        }
        if (cnt[i] == n)
            ans = max(ans, dp[i]);
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：pengyule (赞：1)

> 重排数组 $a(n\le 10^6,a_i\le 2\cdot 10^7)$，使 $\sum_{i=1}^n\gcd(a_1,a_2,...,a_i)$ 最大化，输出最大值。

这很像一个 DP。我们会发现随着 $i$ 的增大， $q_i=\gcd(a_1,a_2,...,a_i)$ 的变化应该是有 $q_i\mid q_{i-1}$。那么设 $f_i$ 表示数 $i$ 作为 $q$ 的结末，最大的所求值。于是 ${f_i}\gets \max_{i|j}\{f_j+i\cdot(cnt_i-cnt_j)\}$，其中 $cnt_i$ 表示 $a$ 中有多少个数是 $i$ 的倍数。

考虑如何计算 $cnt_i$。一个十分巧妙的方法是从小到大枚举值域内的所有质数（$p$），并将当前的 $cnt_i$ 加给 $cnt_{i\div p}$。由于枚举的有序性可以有效地避免进行容斥。（注：初始时只处理出 $cnt_{a_i}$。）

考虑如何优化 $f_i$ 的求解，因为这样是欧拉筛的复杂度。发现只有当 $\frac{j}{i}$ 为质数时才是有必要的，不然一定可以通过多次为质数的更新替代（矛盾）。这样我们从所有数都要枚举变成了只需要枚举质数，复杂度大幅减少，可以通过。

数论方面的复杂度我不会分析，请高人指点。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5,M=2e7;
int n,m,ans,x,a[N],cnt[M+5],f[M+5],v[M+5],prime[M+5];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		cnt[a[i]]++;
	}
	for(int i=2;i<=2e7;i++){
		if(!v[i])prime[++m]=i;
		for(int j=1;j<=m&&i*prime[j]<=2e7;j++){
			v[i*prime[j]]=prime[j];
			if(i%prime[j]==0)break;
		}
	}
	for(int i=1;i<=m;i++)
		for(int j=2e7/prime[i];j;j--)cnt[j]+=cnt[j*prime[i]];
	for(int i=2e7;i;i--){
		if(!cnt[i])continue;
		f[i]=i*cnt[i];
		for(int j=1;j<=m&&i*prime[j]<=2e7;j++)f[i]=max(f[i],f[i*prime[j]]+(cnt[i]-cnt[i*prime[j]])*i);
		if(ans<f[i])ans=f[i],x=cnt[i];
	}
	cout<<ans+n-x;
}
```

---

## 作者：EuphoricStar (赞：1)

## 题意

给定序列 $a_1,a_2,...,a_n$，要求重排 $a$，使得

$$\sum\limits_{i=1}^n \gcd(a_1,a_2,...,a_i)$$

最大。输出这个最大值。

## 思路

考虑 dp 求解。

设 $cnt_i$ 为序列中有因数 $i$ 的数字个数，例如如果 $a = [6,2,3,4]$，那么 $cnt_2$ 为 $2$。这个可以枚举每个 $a_i$ 的因数，$O(n \sqrt{w})$（$w$ 为值域，下同）求出。

然后是 dp 部分。设 $f_i$ 为 以 含有因数 $i$ 结尾的 重排后前缀 $\operatorname{gcd}$ 和 的最大值，初值为 $f_i = cnt_i \times i$（表示把含有因数 $i$ 的数排到前面）。转移枚举每个质数，$f_i = \max\limits_{j=1}{f_{i \times pr_j} + i \times (cnt_i - cnt_{i \times pr_j})}$。这里 $i \times (cnt_i - cnt_{i \times pr_j})$ 表示的是将含有因数 $i$ 的剩余元素添加到序列产生的新贡献，$cnt_{i \times pr_j}$ 由于在计算 $f_{i \times pr_j}$ 时已经算过一遍所以要减去。这部分的时间复杂度为 $O(w \log \log w)$。

最后答案为所有满足 $cnt_i = n$ 的 $f_i$ 的最大值，$cnt_i = n$ 说明 $i$ 为序列所有数的 $\operatorname{gcd}$ 的因数。

总时间复杂度为 $O(n \sqrt{w} + w \log \log w)$。

## 代码

```cpp
void prepare() {
	for (int i = 2; i <= 20000000; ++i) {
		if (!vis[i]) {
			pr[++tot] = i;
		}
		for (int j = 1; j <= tot && i * pr[j] <= 20000000; ++j) {
			vis[i * pr[j]] = 1;
			if (i % pr[j] == 0) {
				break;
			}
		}
	}
}

void solve() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; ++i) {
		int x;
		scanf("%d", &x);
		for (int j = 1; j * j <= x; ++j) {
			if (x % j == 0) {
				++cnt[j];
				if (j * j != x) {
					++cnt[x / j];
				}
			}
		}
	}
	for (int i = 20000000; ~i; --i) {
		f[i] = cnt[i] * i;
		for (int j = 1; j <= tot && i * pr[j] <= 20000000; ++j) {
			f[i] = max(f[i], f[i * pr[j]] + 1LL * i * (cnt[i] - cnt[i * pr[j]]));
		}
	}
	ll ans = 0;
	for (int i = 1; i <= 20000000; ++i) {
		if (cnt[i] == n) {
			ans = max(ans, f[i]);
		}
	}
	printf("%lld", ans);
}
```


---

## 作者：E1_de5truct0r (赞：0)

在 D1 中，我们有一个 $O(n \sqrt{w}+w \ln w)$ 的做法，具体是：

- 对 $a_i$ 进行因数分解，记其中有 $c_i$ 个 $i$ 的倍数。复杂度 $O(n \sqrt{w})$。

- 令 $f_i$ 表示 $\gcd$ 为 $i$ 的答案，每次枚举 $i$ 的倍数 $j$，则贡献为 $f_j+(c_j-c_i) \cdot i$。复杂度 $O(w \ln w)$。

- 最后对所有 $c_i=n$ 的 $f_i$ 取最大值。

考虑两点优化。

- 因数分解，可以改为把所有的 $a_i$ 放在桶里，每次枚举 $i$，统计 $i$ 的倍数。复杂度从 $O(n \sqrt{w})$ 变为 $O(w \ln w)$。

- 每次的转移，不一定要枚举 $i$ 的全部倍数，只需要枚举质数倍数即可，因为其他的倍数可以通过这样不断乘出来，且答案一定不劣。这样可以把复杂度降到更低，但是我不知道这到底是啥复杂度，就当常数更小了吧（

然后就可以轻松通过此题。

---

## 作者：intel_core (赞：0)

令 $b_i=\gcd(a_1,a_2,\cdots,a_i)$，那么有 $b_{i+1}|b_i$。

贪心的，如果存在 $i<j$ 满足 $b_i|a_j$，那么可以交换 $a_i,a_j$。

令 $f_i$ 表示把为 $i$ 的倍数的 $a$ 都排进数列中，此时已确定 $\sum b_i$ 的最大值。

考虑转移，由前面的分析，如果 $f_i$ 可以从 $f_j$ 转移过来，那么必须满足 $i|j$。

所以 $f_i=\max\{c_i\times i,\max\limits_{i|j}\{f_j+(c_i-c_j)\times i\} \}$。

这里 $c_i$ 表示 $\{a_n \}$ 中 $i$ 的倍数的个数。

求 $c_i$ 和 $f_i$ 都可以在 $O(n \sqrt{V})$ 时间内完成，可以通过 $\text{D1}$。

但是 $\text{D2}$ 的 $\text{V}$ 特别大，考虑优化求 $f_i$ 的过程。

我们发现转移的时候只需枚举 $j$ 是 $i \times p$ 的情况就可以，这里 $p$ 是质数。

原来的转移过程的 $j \to i$ 被拆成了若干步，每一步让 $\frac{j}{i}$ 除掉一个质数。

总复杂度 $O(V \log \log V)$。

```cpp
#pragma GCC optimize("Ofast")
#pragma GCC comment("sse,sse2,unroll-loops")
#include<bits/stdc++.h>
using namespace std;
const int NR=1e5+10;
const int MR=2e7+10;
#define ll long long
int n,a[NR],buc[MR];ll f[MR];

int prime[MR],vis[MR],tot;
void init(){
	for(int i=2;i<=2e7;i++){
		if(!vis[i])prime[++tot]=i;
		for(int j=1;j<=tot&&i*prime[j]<=2e7;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}	
}

signed main(){
	cin>>n;init();
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		for(int j=1;j<=sqrt(a[i])+0.5;j++)
			if(a[i]%j==0){
				if(j*j==a[i])buc[j]++;
				else buc[j]++,buc[a[i]/j]++;
			}
	}
	for(int i=2e7;i>=1;i--){
		f[i]=1ll*i*buc[i];
		for(int j=1;j<=tot&&i*prime[j]<=2e7;j++)f[i]=max(f[i],f[i*prime[j]]+1ll*(buc[i]-buc[i*prime[j]])*(1ll*i));
	}	
	ll ans=0;
	for(int i=1;i<=2e7;i++)ans=max(ans,f[i]);
	cout<<ans<<endl;
	return 0;
}
```

---

