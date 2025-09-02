# [USACO18JAN] Stamp Painting G

## 题目描述

Bessie想拿$M$  种颜色的长为$K$  的图章涂一个长为$N$  的迷之画布。假设他选择涂一段区间，则这段区间长度必须为$K$  ，且涂完后该区间颜色全变成图章颜色。他可以随便涂，但是最后必须把画布画满。问能有多少种最终状态，$N\leq 10^6,M\leq 10^6,K\leq 10^6$ 

对于$75\%$  的数据，$N,K\leq 10^3$

## 样例 #1

### 输入

```
3 2 2```

### 输出

```
6
```

# 题解

## 作者：pluszero (赞：17)

这题是一道很经典的DP，还用了一点点逆向思维。

题目大意:有n个格子，用m种颜色覆盖，每次只能覆盖k个格子，原来有颜色也可以覆盖，问一共有多少种最终状态？

题意看上去貌似有点像数学题，但仔细思索就会发现题目只是要求至少有一个长度为k的相同颜色的块。刚开始以为可以用数学方法，将一个长度为k的块单独拿出来，当成一格，然后算排列组合。交上去只过了2个点。仔细想发现有很多重复，于是就放弃了。

后来经过老师的点拨，发现可以用逆向思维来做，先用排列组合算出没有k这个限制条件的所有可能方案，即n的m次方。再算出不符合方案的情况，也就是没有一个长度至少为k的相同颜色的块减去即可。想要算出不符合的方案总数也很简单，一个简单的一维DP就行了，因为我们规定不能有长度超过k的块，所以最多只有连续k-1个格子颜色相同。所以DP方程为:

f[0]=1

当i<k时，f[i]=f[i-1]*m;

当i>k时，f[i]=(f[i-k+1]+...+f[i-1])*(m-1);
（第i-k位必须与第i-k+1位到第i位不同，所以乘m-1）

最后答案即为总方案数减去不符合方案数。

程序：

```cpp
#include<bits/stdc++.h>
using namespace std;

long long f[1000001];

int main()
{
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    long long sum1=1,sum=0;
    for(int i=1;i<=n;i++) sum1=(sum1*m)%1000000007;
    f[0]=1;
    for(int i=1;i<k;i++) 
    {
        f[i]=(f[i-1]*m)%1000000007;
        sum=(sum+f[i])%1000000007;
    }
    for(int i=k;i<=n;i++)
    {
        f[i]=(sum*(m-1))%1000000007;
        sum=(sum+f[i]+1000000007-f[i-k+1])%1000000007;
    }
    printf("%lld",(sum1+1000000007-f[n])%1000000007);
    return 0;
}
```

---

## 作者：Ynoi (赞：14)


这是一个数学+dp题

（方法其实其他题解有讲，但我详细的补充说明一下）

假如没有任何限制，显然答案是$n^{m}$次方

但现在有限制

显然，其他的东西我们可以涂出来，但是其中有一定有一个区间，连续k个颜色相同（最后一次涂色）

所以，我们就要求出没有连续k个颜色相同的个数

考虑dp

f[i] 表示前i个的方案数

f[0] = 1; 应该不用解释吧

当  i < k 时 这一位没有限制，可以涂m种 所以 f[i]=f[i-1]*m;

当 i >= k时，考虑我们把前面j~i位涂成相同的颜色

其中因为这一段和j-1位的颜色不能相同，所以

这一段可以涂m-1种颜色

所以 f[i]=(f[i-k+1]+...+f[i-1])*(m-1); 

但这样时间复杂度是nk的，只要前缀和优化一下就行了

```
#include<bits/stdc++.h>
using namespace std;

#define LL long long
#define mo 1000000007
#define MAXN 1000005
LL n,m,k;
LL f[MAXN],s[MAXN];

int main()
{
	cin >> n >> m >> k;
	LL ans = 1;
	for(int i = 1; i <= n; i ++)
		ans = ans*m%mo;
		f[0] = 1;
		s[0] = 1;
	for(int i = 1; i <= n; i ++)
	{
		if(i < k) f[i] = f[i-1]*m%mo;
		else f[i] = ((s[i-1] - s[i-k] + mo)%mo*(m-1))%mo;
		s[i] = (s[i-1] + f[i])%mo; 
	} 
	cout<<(ans-f[n] + mo)%mo;
	return 0;
} 
```

---

## 作者：spsicio (赞：9)

# [USACO 18 JAN] Stamp Painting

看到大家都写的前缀和优化到 O(n) 的 DP，我来写个直接就是 O(n) 的 DP。  

## Solution

总状态数为 $M^N$，而不合法状态数为相同颜色连续长度都 < K 的状态数。考虑 DP，设 f[i] 表示前 i 个各自的不合法状态数。

$f[i]=1\quad(i=0)$  
$f[i]=m\times f[i-1]\qquad(i<k)$  
$f[i]=m\times f[i-1]-m\qquad(i=k)$   
$f[i]=m\times f[i-1]-(m-1)\times f[i-k]\qquad(i>k)$  

对于 i>k 的情况:不合法的状态需要排除连续 k 个颜色相邻的情况。假设不排除这个情况，那状态数就是 m\*f[i-1]。考虑计算需要排除的状态数：当前这位填的颜色与前 k-1 位颜色相同，总共占了 k 个位置。在前 i-k 位的状况上加入任意一种其他颜色连续 k 块得到的状态就是不合法的。因此需要减去 (m-1)\*f[i-k]。  

## Attention

对于 i>k 的情况：f[i] 可能计算得负数。因此输出答案的时候 `qkpow(M,N)-f[N]` 要先取模，再加上 1e9+7，最后再取模。另外可以再计算 f[i] 的时候多取一次模。


## Code
```
const int mod=1000000007;
const int MAX_N=1000005;
int N,M,K;
int qkpow(ll a,int b){ int r=1; for(;b;a=a*a%mod,b>>=1) if(b&1) r=r*a%mod; return r; }
int f[MAX_N];
int main(){
	N=rd(),M=rd(),K=rd();
	f[0]=1;
	rep(i,1,N){
		f[i]=(int)(((ll)M*f[i-1])%mod);
		if(i==K) f[i]=(f[i]-M)%mod;
		else if(i>K) f[i]=(int)((f[i]-(M-1ll)*f[i-K])%mod);
	}
	printf("%d\n",((qkpow(M,N)-f[N])%mod+mod)%mod);
	return 0;
}
```

---

## 作者：Sakura_梦瑶 (赞：5)

珂能是我比较弱小,这道题不简单...康过几篇题解发现最终部分的说明缺失或是不严谨,这里会着重说明.

当n块每一块可以涂上任意颜色时视为所有情况也就是n^m.
现在就需要剔除不合法情况也就是**没有一个连续段长度为k且同一颜色**（这个可以简单证明）.

接下来是剔除不合法状态所使用的dp.我们设计二维状态f i j 表示第i位时相同颜色的后缀长度为j的方案数.转移方式就是f[i][j]=f[i-1][j-1],f[i][1]=sig{f[i-1][1 to k-1]*(m-1)}.**注意这在实际代码上也是有严格的顺序的.**
现在是nk的复杂度.

我们尝试在这个基础上进行优化。直接设计一维状态f[i]=长度为i时的所有不合法方案总数.

二维意义下的f[i][1]转移已经能轻易替换为f[i]+=f[i-1] * (m-1)了.
但是前者比较麻烦.我们发现所有原本二维的f[i][j]都是对应着现在的f[i-j] * (m-1),于是合并成现在一维状态意义为f[i]+=sig{f[i-k+1] to f[i-2]}*(m-1).

综上所述,最终转移成为f[i]={sig(f[i-k+1] to f[i-1])*(m-1)},然后自己随便前缀和优化就行了,**以及我再也不相信易证了！！**

于是说明到此结束,不知道易证的大佬们是有更好的理解方式还是我太蒻.枯了.

以下是代码
```cpp
#include<bits/stdc++.h>
#define fer(x,y,z) for(int x=y;x<=z;x++)
#define mod 1000000007
using namespace std;
long long n,m,p,a[1<<20],c=1,s;
main(){
	cin>>n>>m>>p;fer(i,1,n)c=c*m%mod;
	a[0]=1;fer(i,1,p-1)a[i]=a[i-1]*m%mod,s=(s+a[i])%mod;
	fer(i,p,n)a[i]=s*(m-1)%mod,s=(s+a[i]-a[i-p+1])%mod;
	 cout<<(c-a[n]+mod)%mod;
}
```
此题思维难度和代码难度不成正比,谢谢.



---

## 作者：Great_Influence (赞：4)

虽然也是$dp$，但是思路不太一样，所以来发篇题解。

观察一下题目，考虑直接算哪些结果是合法的。稍微推一下，可以发现，一个解果合法当且仅当存在至少一个长度大于$k$的连续序列。

然后这时可以选择全方案减去不合法方案，也可以直接算。此处提供直接算的方法。

设$dp[i][j]$表示到第$i$位，之前未出现长度为$k$，末尾有连续$j$个相同的字符的方案数，则可以得到:

$dp[i][j]=dp[i-1][j-1]$

$dp[i][1]=(m-1)\sum\limits_{j=1}^{k-1}dp[i-1][j]$

答案为:

$\sum\limits_{i=1}^n dp[i][k]$

直接做是$O(n^2)$的。发现上方的转移大部分是从$j-1$转到$j$，只有第一项是前面$dp$值的和，考虑使用队列来维护这个$dp$。开一个队列，每次向队尾加入区间和的$(m-1)$倍，更新一下区间和。然后，如果队列元素超过$k-1$个，将队首加到答案中，然后弹掉。记得更新区间和。

代码：

```cpp
#include<bits/stdc++.h>
#include<cctype>
#define For(i,a,b) for(i=(a),i##end=(b);i<=i##end;++i)
#define Forward(i,a,b) for(i=(a),i##end=(b);i>=i##end;--i)
#define Rep(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;++i)
#define Repe(i,a,b) for(register int i=(a),i##end=(b);i>=i##end;--i)
using namespace std;
template<typename T>inline void read(T &x){
    T s=0,f=1;char k=getchar();
    while(!isdigit(k)&&k^'-')k=getchar();
    if(!isdigit(k)){f=-1;k=getchar();}
    while(isdigit(k)){s=s*10+(k^48);k=getchar();}
    x=s*f;
}
void file(void){
    #ifndef ONLINE_JUDGE
    freopen("water.in","r",stdin);
    freopen("water.out","w",stdout);
    #endif
}

const int MAXN=1e6+7;
const int mod=1e9+7;
static int n,m,k;
inline void init()
{
	read(n);read(m);read(k);
}
static int ans,sum,mp[MAXN],sta[MAXN],h,t;
inline void solve()
{
	mp[0]=1;
	Rep(i,1,n)mp[i]=1ll*mp[i-1]*m%mod;
	sta[h=t=1]=sum=m;
	Rep(i,2,n)
	{
		sta[++t]=1ll*sum*(m-1)%mod;
		sum=1ll*sum*m%mod;
		if(t-h+1>=k)
		{
			ans+=1ll*sta[h]*mp[n-i]%mod;
			if(ans>mod)ans-=mod;
			sum+=mod-sta[h++];
			if(sum>mod)sum-=mod;
		}
	}
	printf("%d\n",ans);
}
int main(void){
    file();
	init();
	solve();
	return 0;
}

```

---

## 作者：一只书虫仔 (赞：4)

> [Problem](https://www.luogu.com.cn/problem/P4187)

就这？就这？这还数论？这不明摆着 dp 吗（那为啥标签还有数论啊 qwq）

### Description

> 给你 $n$ 个长 $m$ 的画布，$k$ 种不同的颜色，你每次可以使用一种颜色涂连续 $k$ 单位长的画布，现在问你在必须把所有格子涂满的情况下，合法的最终结果有多少种。

（从 [这里](https://blog.csdn.net/qq_41955236/article/details/96357056) 看到的，但思路跟这篇题解一点也不一样）

### Solution

因为满足情况的条件很难求，所以我们求的是不满足情况的，再用总数去减就可以了

- 总数：$n^m$
- 不满足情况：
	- 状态表示：$f[i]=\text{Pre } i \text{ length which}<k$
	- 转移方程：$f[i]=\begin{cases}f[i-1]\times m(i<k)\\ \sum f[j]\times(m-1)(i \ge k,i-k<j<i)\end{cases}$
	- 初始化：$f[0]=1$
- 满足情况：$n^m-f[n]$

转移方程可以模拟成分段函数，所以我们打两个循环来求。   
总数有点大，所以我们边求幂边取模，dp 的时候也取模，最后答案也取模就可以保证答案不爆。

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

long long makePow (int n, int m, int mod) {
	long long ans = 1;
	for (int i = 1; i <= n; i++)
		ans = ans * m % mod;
	return ans;
}

long long f[1000086];

int main () {
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	long long sum = 0;
	f[0] = 1;
	for (int i = 1; i < k; i++) {
		f[i] = f[i - 1] * m % 1000000007;
		sum = (sum + f[i]) % 1000000007;
	} // First Part: i < k
	for (int i = k; i <= n; i++) {
		f[i] = sum * (m - 1) % 1000000007;
		sum = (sum - f[i - k + 1] + f[i] + 1000000007) % 1000000007;
	} // Second Part: k <= i <= n 
	printf("%lld", (makePow(n, m, 1000000007)- f[n] + 1000000007) % 1000000007);
	return 0;
}
```

预期得分：$100$ 分   
[Record](https://www.luogu.com.cn/record/34584973)

注意开 long long 就好

---

参考资料：

zmqh-dmfx 大佬的 [Blog](https://blog.csdn.net/a_bright_ch/article/details/83443627)

---

## 作者：Goodenough (赞：2)

#### ~~看到题解这么少而且许多神仙都深藏不露~~
###### ~~本蒟蒻就来凑凑热闹（逃）~~
[TM](https://www.luogu.org/problem/P4187)\
题目大意：n个格子染m种颜色，一次只能染k格，问有几种不同的染色方法\
很明显是dp，需要用到a little的逆向思维
1. 我们首先可以发现，如果不考虑一次只能染k格，那么总共有m^n种方法
2. 考虑一次只能染k格后，染完后至少会有连续的k格为一种颜色
3. 然后用dp求出不合法的方案减一减就好了
### 具体来说
#### （注意每一步都要模一下）
#### 1. i<k时，d[i]=d[i-1]*m
#### 2. i>=k时，d[i]=
####  i-1
##   Σ d[j] *(m-1)
#### j=i-k+1
### 因为考虑从i-k+1到i-1这k-1个格子为同一种颜色，为了使方案不合法，第i个格子不能为这种颜色
##### ~~但是这样做很慢~~
#### 其实我们看见了可爱的Sigma就可以考虑用前缀和优化啦！
于是乎出现了这段代码：
```cpp
#include<cstdio>
#define N 1000005
using namespace std;
const long long p=1e9+7;
int n,m,k;
long long d[N],sum[N],ans;
int main(){
	scanf("%d%d%d",&n,&m,&k);
	ans=1;
	for(int i=1;i<=n;i++) ans=ans*m%p;
	d[0]=sum[0]=1;
	for(int i=1;i<=n;i++){
		if(i<k) d[i]=d[i-1]*m%p;
		else d[i]=(sum[i-1]-sum[i-k]+p)%p*(m-1)%p;
		sum[i]=(sum[i-1]+d[i])%p;//前缀和
	}
	printf("%lld\n",(ans-d[n]+p)%p);//防止负数
	return 0;
}
```
只有19行呢喵喵喵
#### ~~其实我现在心里很方~~

---

## 作者：UperFicial (赞：1)

- 考虑反向思考这个问题。

- 假设你的印章长度是任意的，可以随便盖，将答案设为 $ans_1$；假设你的印章长度是不等于 $k$ 的，那么再将这种条件下的答案设为 $ans_2$，那么真正的答案就是 $ans_1-ans_2$ 了。

- 考虑 $ans_1$ 怎么算，你每个格子都有 $m$ 种可能的颜色覆盖，一共有 $n$ 个格子，所以 $ans_1=m^n$。

- 对于 $ans_2$，考虑通过动态规划来求。

- 设 $f_i$ 表示到了第 $i$ 个格子的答案，所以答案即为 $f_n$。

  - 假设 $i<k$，那么第 $i$ 位可以随便涂，一共有 $m$ 中颜色，所以 $f_i=f_{i-1}\times m$。这里需要定义 $f_0=1$。
  
  - 而若 $i\ge k$，我们发现，最后一次涂，一定会出现长度为 $k$ 的颜色相同的子序列。然后我们设一个 $j$，表示将 $[1,i]$ 分为两段 $[1,j]$ 和 $[j+1,i]$，并且第二段的长度要 $<k$，而第二段只有 $m-1$ 种选择，为什么呢？因为你 $[1,j]$ 的某一段，假设以 $j$ 为右端点，那么，肯定会有一段 $[l,j]$ 使得这一段与 $[j+1,i]$ 构成长度为 $k$ 的颜色序列。所以得到了状态转移方程 $f_i=\sum_{j=i+k-1}^{i-1}f_j\times (m-1)$。
  
  - 但你发现这个 $dp$ 转移时 $O(n^2)$ 的，所以可以套一个前缀和，这道题就做完了。

---

## 作者：KAMIYA_KINA (赞：1)

## Tag

递推，计数。

## Description

一个长为 $n$ 的序列，用 $m$ 中颜色对其染色，要求至少有 $1$ 个长度为 $k$ 的相同颜色的颜色块的方案有多少种。

$\texttt{data range:} n,k,m \leq 10^6$.

## Solution

一道非常有意思的题，如果我们正向考虑的话会很容易发现很难以判断掉重复情况，如果是容斥的话会漏掉一些情况，所以我们要换一种角度考虑：不满足的方案。

根据题目的性质，我们很容易就能找到不满足的方案，那么总共的方案也很好找，就是 $m^n$，那么我们考虑前 $i$ 个方块的不满足方案为 $f_i$，那么我们就很容易知道：
$$
f_i=mf_{i-1}\ \ \ (i < k)
$$
因为前 $k$ 个不可能有可行情况嘛……

然后我么考虑后面的情况，对于长度正好为 $k$ 的时候，我们就应该用**当前不合法情况减去合法情况**，这就是这题十分重要的一个思路：**从合法中找不合法，再从不合法中找合法**。

那么长度正好为 $k$ 的合法情况就只有 $m$ 种，就是正好全都是一个颜色的方案。
$$
f_k=mf_{k-1}-m
$$
然后再考虑大于 $k$ 的情况，那么只要使得第 $i-k$ 个与第 $i$ 个不是相同颜色即可，那么就是：
$$
f_i=mf_{i-1}-(m-1)f_{i-k}\ \ \ (i > k)
$$
然后直接做就可以了，时间复杂度 $O(n)$。

---

## 作者：nydzsf_qwq (赞：1)

由于最后一次涂的一定为一段长为 $K$ 的区间，所以最终结果一定有连续 $K$ 个格子颜色相同。

而对于任意一种有连续 $K$ 个格子相同的涂色结果，这 $K$ 格左侧的从左往右涂，右侧的从右往左涂，最后涂这 $K$ 个，这种结果一定是可行的。

由于正向计算的话需要复杂的容斥原理，所以我们逆向计算。

如果没有限制，结果数一定为 $M^{N}$（没个格子 $M$ 种可能）。

现在只需要计算不存在连续 $K$ 个格子颜色相同的结果数。

设 $dp_{i}$ 为长度为 $i$ 的不符合要求的个数。

当 $i<K$ 时，$dp_{i}=m^{i}$，也可看作是 $dp_{i-1}*m$（定义 $dp_{0}=1$）。

当 $i\geq K$ 时，一定存在一个 $j\in[i-k+1,i-1]$ 使得第 $j+1$ ~ $i$ 格颜色相同，且与第 $j$ 格不同，否则最后 $K$ 格颜色就相同了。

第 $1$ ~ $j$ 格有 $dp[j]$ 种可能，第 $j+1$ ~ $i$ 格的颜色有 $m-1$ 种可能，于是可以得到转移方程 $dp_{i}=\sum\limits_{j=i-k+1}^{i-1} dp_{j}*(m-1)$

使用前缀和优化后可将时间复杂度降为 $O(n)$。

程序写起来没什么困难，需要注意的是要开 `long long`，且取模运算随时要做。

程序如下：

``` c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
ll ksm(ll n,int k) {
	if(k==0) return 1%mod;
	return ksm(n*n%mod,k/2)*((k%2)?n:1)%mod;
}
int n,m,k;
ll dp[1000005],s;
int main() {
	scanf("%d%d%d",&n,&m,&k);
	dp[0]=1;
	for(int i=1;i<k;++i) {
		dp[i]=(dp[i-1]*m)%mod;
		s=(s+dp[i])%mod;
	}
	for(int i=k;i<=n;i++)
    {
        dp[i]=(s*(m-1))%mod;
        s=(s+dp[i]-dp[i-k+1]+mod)%mod;
    }
    printf("%lld\n",(ksm(m,n)-dp[n]+mod)%mod);
	return 0;
}
```

[结果](https://www.luogu.com.cn/record/51543874)

---

## 作者：zjjws (赞：0)

最终状态的条件是：**需要至少有一段连续的长度为 k 的区间**

也就是说，不看最后一次覆盖，所能得到的方案数是 $m^n$，可是如何判重呢？

不管是 DP 式还是容斥，都想不到正确的推导式。

遵循着正难则反的原则，如果将总方案减去**所有连续相同块长度小于 k 的方案数**，这个问题就很简单了。

最朴素的递推式很好写：设 $f_{i,j,p}$ 表示到位置 $i$，当前后缀的连续相同长度是 $j$，当前位的颜色是 $p$ 的方案数。

有:

$$\begin {cases} f_{i,1,p}=\sum_{j=1}^{k-1}\sum_{x=1}^m f_{i-1,j,x}\times [x!=k]\\f_{i,j,p}=f_{i-1,j-1,p},j>1 \end {cases}$$

因为颜色彼此独立，题目也没有什么限制条件，所以我们可以知道：

$$f_{i,j,1}=f_{i,j,2}=\dots f_{i,j,m}$$

那么就可以降成二维，第三维丢掉，变成：

$$\begin {cases} f_{i,1}=\sum_{j=1}^{k-1} f_{i-1,j}\times (m-1)\\f_{i,j}=f_{i-1,j-1},j>1 \end {cases}$$


然后我们又发现：

$$(\sum_{j=1}^{k-1}f_{i,j})=(\sum_{j=1}^{k-1}f_{i-1,j})\times m-f_{i-1,k-1}$$

然后这个 $f_{i-1,k-1}$ 是可以算出来的，设 $s_i$ 等于这个东西，则有：

$$s_i=\begin {cases} 0,i<k\\m,i=k\\f_{i-1,k-1}=f_{i-k+1,1}=f_{i-k}\times (m-1),i>k \end {cases}$$

那么这个方程就可以降成一维：

$$f_i=f_{i-1}\times m-s_i$$

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAX=1e6+3;
const int MOD=1e9+7;
LL f[MAX];
LL rin()
{
    LL s=0;
    char c=getchar();
    bool bj=0;
    for(;(c>'9'||c<'0')&&c!='-';c=getchar());
    if(c=='-')c=getchar(),bj=true;
    for(;c>='0'&&c<='9';c=getchar())s=(s<<1)+(s<<3)+(c^'0');
    if(bj)return -s;
    return s;
}
int main()
{
    int i,j;
    int n,m,k;
    f[0]=1;
    LL s=0;
    n=rin();m=rin();k=rin();
    f[1]=m;
    if(k==1)s=m;
    for(i=2;i<=n;i++)
    {
        if(i>k)s=f[i-k]*(m-1)%MOD;
        if(i==k)s=m;
        f[i]=f[i-1]*m%MOD-s;
        if(f[i]<0)f[i]+=MOD;
    }
    LL ans=1;
    LL sum=m;
    for(i=n;i>0;i>>=1){if(i&1)ans=ans*sum%MOD;sum=sum*sum%MOD;}
    ans-=f[n];
    if(ans<0)ans+=MOD;
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：lgswdn_SA (赞：0)

这道题算是 1/3 个结论题，2/3 个简单 DP。

## 结论

合法的全部都有一个特征：**具有长至少为 $k$** 的子区间满足颜色一样。

证明比较简单，对于这样的一种染色方案，我们安排一下涂色顺序，那个长为 $k$ 的子区间是最后染色的，其他都可以通过叠加的方式达到目的，而只有最后一个覆盖的不可以。

于是有了这个结论，接下来就是很简单的 DP。（真的，我就栽在了这个结论上，我怎么这么菜）。

## DP

接下来要计算所有具有长度至少为 $k$ 的子区间满足颜色相同的染色方案数。很显然，用一个补集转换，可以改为求出所有颜色相同的连续子区间长度 $\le k$ 的个数。

我们设 $f(i)$ 为前 $i$ 个格子的染色方案数，可以得到当 $i>k$ 时

$$
f(i)=\sum_{j=i-k+1}^{i-1}f(j)\times(m-1)
$$

$i\le k$ 时
$$
f(i)=f(i-1)\times m
$$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+9,mod=1e9+7;

int n,m,k,f[N];

void dp() {
	int sum=0; f[0]=1;
	for(int i=1;i<=n;i++)
		if(i<k) f[i]=f[i-1]*m%mod, sum+=f[i], sum%=mod;
		else f[i]=sum*(m-1)%mod, sum+=f[i], sum-=f[i-k+1], sum%=mod;
}

signed main() {
	scanf("%lld%lld%lld",&n,&m,&k);
	dp();
	int tot=1;
	for(int i=1;i<=n;i++) (tot*=m)%=mod;
	printf("%lld",(tot-f[n]+mod)%mod);
	return 0;
}
```

---

## 作者：Heap_Sort (赞：0)

## 题意转化 

在长度为n的，每个点都能填m种数的序列当中，求满足（至少有一个数字相同且长度大于等于k的序列）的序列的数量

再看看数据范围，明显要用动态规划来做。
直接求不容易，可以反过来，求不合法序列，即涂不出来的序列。

用一维数组，dp[i]表示前i位有几种不合法的序列。

当i<k时,可以随便涂,dp[i]=dp[i-1]*m(初始化dp[0]=1);

当i>=k时:
前面有可能涂了长为k-1的相同序列,此时不能再涂相同颜色,否则就合法了，因此只能涂m-1种颜色。   
而因为不能使连续长度>k,所以至少得从dp[i-k+1]推过来，再前面就有可能相同。   
比较难想的是这些长度为什么要涂相同的颜色，因为前面已经把不相同的都考虑进来了，此时只有推过来的一段区间都涂相同颜色才能不重复。

但这样复杂度会到O（n*k），于是还要加一个前缀和优化

下面是代码

```pascal
const mo=1000000007;
var dp:array[0..1000000] of int64;sum:array[0..1000000] of int64;
//longint会爆！中间过程也会算进
  n,m,l,a,c:longint;
  b:int64;
begin
  readln(n,m,l);
  dp[0]:=1;
  sum[0]:=1;
  for a:=1 to l-1 do
   begin
    dp[a]:=(dp[a-1]*m)mod mo;
    sum[a]:=(sum[a-1]+dp[a])mod mo;//前缀和
   end;
  for a:=l to n do
   begin
    dp[a]:=(((sum[a-1]-sum[a-l]+mo)mod mo)*(m-1))mod mo;//这就是前面的公式
    sum[a]:=(sum[a-1]+dp[a])mod mo;
   end;
  b:=1;
  for a:=1 to n do b:=(b*m)mod mo;
  writeln((b+mo-dp[n])mod mo);//最后再一减
end.

```

谢谢大家看到这里

---

