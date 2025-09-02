# Kavi on Pairing Duty

## 题目描述

Kavi has $ 2n $ points lying on the $ OX $ axis, $ i $ -th of which is located at $ x = i $ .

Kavi considers all ways to split these $ 2n $ points into $ n $ pairs. Among those, he is interested in good pairings, which are defined as follows:

Consider $ n $ segments with ends at the points in correspondent pairs. The pairing is called good, if for every $ 2 $ different segments $ A $ and $ B $ among those, at least one of the following holds:

- One of the segments $ A $ and $ B $ lies completely inside the other.
- $ A $ and $ B $ have the same length.

Consider the following example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1528B/41a58a6a051949b924acfc162dd6465703f68210.png) $ A $ is a good pairing since the red segment lies completely inside the blue segment.

 $ B $ is a good pairing since the red and the blue segment have the same length.

 $ C $ is not a good pairing since none of the red or blue segments lies inside the other, neither do they have the same size.

Kavi is interested in the number of good pairings, so he wants you to find it for him. As the result can be large, find this number modulo $ 998244353 $ .

Two pairings are called different, if some two points are in one pair in some pairing and in different pairs in another.

## 说明/提示

The good pairings for the second example are:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1528B/26cefe71c208095e0e610c498701d052b950b5a2.png)In the third example, the good pairings are:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1528B/4bfe3f3beac587d75fee5d30f6490c2823b90e1d.png)

## 样例 #1

### 输入

```
1```

### 输出

```
1```

## 样例 #2

### 输入

```
2```

### 输出

```
3```

## 样例 #3

### 输入

```
3```

### 输出

```
6```

## 样例 #4

### 输入

```
100```

### 输出

```
688750769```

# 题解

## 作者：KaisuoShutong (赞：15)

## 翻译

给定一条有 $2n$ 个点的直线，将上面的点两两配对形成圆弧，要求任意不等大的圆弧必然为包含关系。问合法的状态总数模 $998244353$。

$n\leq 10^6$。

## 题解

考虑如何让不等大的圆弧都包含，发现必然是这样的：   
![](https://cdn.luogu.com.cn/upload/image_hosting/jc19h19i.png)

也就是说，不管这个弧长度为多少，都有且仅有一个方法使得中间空出空间。

但这样不对啊，手玩样例发现还可以这样：   
![](https://cdn.luogu.com.cn/upload/image_hosting/fcphsst4.png)

但是这样的话，因为分成了很多块，所以根据题意，内部不能再放东西了，要填满。

所以一个块的大小一定整除 $n$。

说了怎么多，再想想第一种情况中间剩下的东西好像与我无关（长度一定小于我），似乎没有后效性？考虑 Dp。

设 $f_i$ 表示 $2i$ 个点的答案，那么：

$$f_i=\sigma_i+\sum^{i-1}_{j=1}f_j$$

其中，$\sigma_i$ 表示 $i$ 的约数个数，初始 $f_1=1$。

复杂度为 $\mathcal{O}(n\log n)$ 或 $\mathcal{O}(n)$。

点个赞吧。

参考代码：
```cpp
//伟大的导师，伟大的领袖，伟大的统帅，伟大的舵手
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
char __buf[1<<20],*__p1,*__p2;
#define getchar() (__p1==__p2?(__p2=__buf+fread(__p1=__buf,1,1<<20,stdin),__p1==__p2?EOF:*__p1++):*__p1++)
int read() {
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
const int maxn = 1e6+10, mod = 998244353;
int n,f[maxn];
signed main() {
	n=read();
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j+=i) ++f[j];
	f[1]=1;for(int i=2;i<=n;i++) f[i]=(1ll*(f[i-1]<<1)+f[i])%mod;
	cout<<(f[n]-f[n-1]+mod)%mod<<'\n';
	return 0;
}
```

---

## 作者：iMya_nlgau (赞：6)

### 题目大意

给定一条有 $2n$ 个点的直线，将上面的点两两配对形成圆弧，要求任意不等大的圆弧必然为包含关系，求合法的状态总数。

### 思路

设 $f_i$ 表示 $n=i$ 时的答案。

不难发现，对于 $k|i$ 我们可以把 $i$ 个匹配每 $k$ 个分成一堆，这种情况对答案的贡献为 $\sigma_0(i)$，下图是 $i=8,k=4$ 的样子。

![](https://cdn.luogu.com.cn/upload/image_hosting/gdzyhu16.png)

还有一种情况，就是先将 $k$ 个长 $2i-k+1$ 的匹配放在最外面，中间的部分就是 $f_{i-k}$ 的情况，这种情况的贡献是 $\sum\limits_{0<k<i}f_{i-k}$ 下图是 $k=3$ 的样子。

![](https://cdn.luogu.com.cn/upload/image_hosting/6ablnx24.png)

总的状态转移方程就是 $f_i=\sigma_0(i)+\sum\limits_{0<j<i}f_j$，边界 $f_1=1$。

[代码实现](https://www.luogu.com.cn/paste/o5mfaml1)

---

## 作者：FutaRimeWoawaSete (赞：4)

永远铭记让我身败名裂并且阻止我上大分的一道题。               

首先很显然的就是我们可以通过 $DP$ 得到答案。         
        
设 $DP_i$ 表示有 $2i$ 个点时的答案。        

首先我们可以连接首尾点，那么中间的所有线段都被包含了，此时就有一个 $dp_{i - 1}$ 的贡献。            

这么处理一次过后我们剩下就只用考虑首尾不连的情况，在首没连超过 $n$ 之前的点的时候，因为首连接的线段都不能被包含了，我们只能去把所有线段连一样长，即 $n$ 必须被线段长度整除，这类情况的贡献就是 $n$ 的因子个数除去 $n$ 本身。           

当首连接超过 $n$ 以后的点，我们可以还是先把前面的点都往后面连给连成长度一样的点直到连不动为止，我们会发现剩下没有被连接的点都被包含在了当前所连的所有线段内，所以只要内部合法就好了（这里建议自己画一下图）。这类答案的贡献是 $dp_1 \sim dp_{i - 2}$ 的和。     

这里得用到 $O(n \log n)$ 线性筛，因为打CF自己没有调出来……所以线性筛部分是贺的，大家将就看一下代码吧。   

~~其实我中间打了表的但是被制裁了。~~
```cpp
#include "bits/stdc++.h"
using namespace std;
#define int long long
const int max_n = 1e6 + 5;
const long long mod = 998244353;
long long n,m,dp[1000005],sum[1000005],num[1000005];
int prime[max_n + 5] = {0};  //素数表，存储找到的素数
int f[max_n + 5] = {0};             //f[i]表示数字i的因数的个数
int cnt[max_n + 5] = {0};        //cnt[i]表示数字i 最小质因数的幂次
 
void init() {
    for (int i = 2; i <= max_n; i++) {
        if (!prime[i]) {                             //若数字i是素数
            prime[++prime[0]] = i;      //存放在prime数组中
            f[i] = 2;                                     //素数的因数只有1和本身,所以f[i] = 2
            cnt[i] = 1;                                //i = 1 * i，所以最小质因数的幂次为1
        }
         //遍历之前找到的素数，若prime[j] 小于数字i的最小质因数，则我们标记prime[i * prime[j]] = 1
        for (int j = 1; j <= prime[0]; j++) { 
            if (i * prime[j] >  max_n) break;  //我们只要在2到max_n范围内的素数，若超过max_n，此时直接跳出
            prime[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                //这部分解释见下文
                f[i * prime[j]] = f[i] / (cnt[i] + 1) * (cnt[i] + 2);
                cnt[i * prime[j]] = cnt[i] + 1;
                break;
            } else {  //prime[j]是素数，因此i和prime[j]的因数最多是1和prime[j]，又i % prime[j] != 0，所以i和prime[j]互素
                f[i * prime[j]] = f[i] * f[prime[j]]; 
                //两元素互素，因此他们的因数除1外没有交集，所以i * prime[j]的因数个数 = i的因数个数 * prime[j]的因数个数
 
                cnt[i * prime[j]] = 1;
                //因为从prime数组1号位开始向后遍历素数并且i % prime[j] != 0，所以prime[j]始终小于i的最小质因数，
                //所以i * prime[j]最小质因数的幂次为prime[j]的幂次，即为1
            }
        }
    }
    return ;
}
long long Sum(long long x)
{
	long long res = 0;
	for(int i = 1 ; i < x ; i ++) if(x % i == 0) res ++;
	return res;
}
long long Pre(long long x)
{
	return sum[x];
}
signed main()
{
	scanf("%lld",&n);
	init();
	//printf("%lld\n",f[2]);
	dp[0] = sum[0] = 1;
	dp[1] = 1 , sum[1] = 2;
	for(int i = 2 ; i <= n ; i ++) 
	{
		dp[i] = dp[i - 1] + f[i] - 1 + Pre(i - 2) , dp[i] %= mod;
		sum[i] = sum[i - 1] + dp[i] , sum[i] %= mod;
	}
	printf("%lld\n",dp[n]);
	return 0;
}
```

---

## 作者：Iceturky (赞：2)

题解去里怎么全都是 dp，我来贡献一个组合的分析方向。

定义一个长度为 $2i$ 的块为形如![](https://cdn.luogu.com.cn/upload/image_hosting/wcca4y97.png)的圆弧组。

考虑最终形态是否存在包含，若无则一定是由若干长度相同的块组成。

若有则一定为一个嵌套结构：即一个小块放在一个大块的中间，一层层套起来。

但是最里层较为特殊，可以若干长度相同的块并列放在套起它的块内。

不存在包含的方案数即为 $n$ 的因子数。

若存在包含，我们考虑：因为若干块是套起来的，只要我们知道了从里到外每一个块的长度，我们就能唯一确定一个方案。且不同的长度会对应不同的方案。

形式化的说，存在一个长度为 $k$ 的数列 $len$ ，满足 $k>1,\sum len\leq 2n$ 且 $len$ 内元素均为偶数，还需满足 $len_1|(n-\sum len)$。每一个合法的 $len$ 都对应了一组合法方案。

这玩意可以枚举 $len_1$ 和 $x=\frac{n-\sum len}{len1}$ 然后插板求固定了上述两者的满足条件的 $len$ 数量。

注意到板子数量的范围是 $[0,n-len_1\cdot(x+1)-1]$，即不放到放满，直接用 $2^{2-len_1\cdot(x+1)-1}$ 来计算。

但是暴力枚举 $x$ 会超时，我们注意到在固定 $len_1$ 的时候其为一个等比数列，然后就能 $\mathrm{O(n)}$ 计算了。

预处理 $2^n$ 与 $2^{-n}$ 能做到线性，但我没写，就写了现求幂和逆元的 $\mathrm{O(n\log n)}$ 。

code

```cpp
int qp(int x,int y){
	int ans=1;
	for(int i=1;i<=y;i<<=1){
		if(i&y)
			ans=ans*x%mod;
		x=x*x%mod;
	}return ans;
}

signed main()
{
	int n=read();
	int ans=0;
	for(int i=1;i<n;i++){//枚举len1，len1一定小于n，因为要满足k>1（等于1就变成一整块，没有包含关系了）
		ans+=(qp(2,n-1)-qp(2,(n-1)%i)+mod)%mod*qp((qp(2,i)-1+mod)%mod,mod-2);//等比数列求和加速
		ans+=n%i==0;//计算n因子个数
		ans%=mod;
	}print((ans+1)%mod),pc('\n');//还有n
	return 0;
}
```

---

## 作者：HenryHuang (赞：2)

# 「CF1528B」 Kavi on Pairing Duty

[传送门](https://www.luogu.com.cn/problem/CF1528B)

我们将相交的圆弧称为一组。显然只有一种合法的相交方案。

首先有一个很显然的结论：一个合法的连接方案一定是：若干个组层层包含，最内层可以存在多个相同的组。

我们可以考虑枚举最内层每组有 $x$ 条圆弧，有 $y$ 个组。

这样的话就相当于还剩下 $n-xy$ 条圆弧需要按顺序放在外面，我们只需要考虑将其划分成若干组，这相当于做一个有顺序的自然数拆分，方案数为 $2^{\max(n-xy-1,0)}$ 种，这个东西显然可以 $O(1)$ 算。

总时间即为枚举最内层情况的复杂度，为 $O(n\log n)$。

```cpp
/*---Author:HenryHuang---*/
/*---Never Settle---*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll p=998244353;
const ll maxn=1e6+5;
ll ksm(ll a,ll b,ll p){
	ll ans=1;
	while(b){
		if(b&1) ans=1ll*ans*a%p;
		b>>=1,a=1ll*a*a%p;
	}
	return ans;
}
ll pw[maxn];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	ll n; cin>>n;
	ll ans=0;
	pw[0]=1;
	for(ll i=1;i<=n;++i) pw[i]=1ll*pw[i-1]*2%p;
	for(ll k=1;k<=n;++k){
		for(ll i=1;i<=n;++i){
			ll owo=i*k;
			if(n-owo==0) ans+=1;
			else if(n-owo>0) ans+=pw[n-owo-1];
			else break;
			ans%=p;
		}
	}
	cout<<ans<<'\n';
	return 0;
}
```





---

## 作者：Mine_King (赞：1)

[在我的博客获得更好的阅读体验](https://www.cnblogs.com/mk-oi/p/CF1528B.html)

## Problem

[CF1528B Kavi on Pairing Duty](https://www.luogu.com.cn/problem/CF1528B)

**题目大意：**

在数轴上有 $2n$ 个点，相邻两个点的距离为 $1$。现在要将这些点两两匹配成 $n$ 个圆弧，要求任意两个圆弧要么等长，要么其中一个包含另一个，问方案数。

## Solution

首先观察发现好像合法的匹配一定是若干层包含，里面一层并列，也就是这个样子：

![](https://pic.img.ski/1668404946.png)

中间三个句号表示剩下的点组成的圆弧都是等长的。

然后发现被样例 Hack 了：

![](https://pic.img.ski/1668405161.png)

观察发现被 Hack 的原因是可能有若干个等长的圆弧相交，剩下比他们小的圆弧在他们相交的部分中。

于是尝试修改结论：合法的匹配一定是外面若干层，每一层都是若干个等长的圆弧，最里面一层为若干个等长的圆弧。

接下来考虑统计答案，可以把外面的几层与最内层分开统计。

首先考虑外面几层。  
对于每一层，发现唯一合法的匹配长这个样子：

![](https://pic.img.ski/1668405502.png)

所以假设外面几层总共有 $k$ 层，则外面几层的方案数相当于将 $k$ 个数分成若干个区间的方案。  
这个东西相当于要在 $k-1$ 个空隙中插入若干个隔板的方案数。发现每个空隙都有插或不插两种选项，所以方案数为 $2^{k-1}$。

然后考虑最内层。  
由于每个圆弧要等长，所以假设要匹配 $l$ 个圆弧，则每个圆弧的长度必须是 $l$ 的因数。而对于每一确定的长度，则有唯一对应的一种匹配的方案。所以内层的方案数为 $\operatorname{d}(l)$。

所以整个题目的答案就是：
$$
\sum\limits_{i=1}^n (\operatorname{d}(i) \times 2^{n-i-1})
$$


## Code

```cpp
//Think twice,code once.
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int mod=998244353;

int n,f[1000005],pw[1000005];
long long ans;

int main() {
	scanf("%d",&n);
	pw[0]=1;
	for (int i=1;i<=n;i++) pw[i]=2*pw[i-1]%mod;//pw[i] 表示 2^i
	for (int i=1;i<=n;i++)
		for (int j=i;j<=n;j+=i) f[j]++;//f[j] 表示 j 的因数个数。
	for (int i=1;i<=n;i++) ans=(ans+(long long)pw[max(n-i-1,0)]*f[i]%mod)%mod;//统计答案。
	printf("%lld\n",ans);
	return 0;
}
```



---

## 作者：wzt2012 (赞：0)

### 题目意思

$2n$ 个点排列在 $\texttt x$ 轴上，第 $i$ 个点的坐标是 $i$，把这 $2n$ 个点划分成 $n$ 对，问满足下列条件的划分数量：

对于任意点对 $A,B$，连成的线段要不然长度一样，要不然存在包含关系。

$1\le n\le 10^6$

### 解题思路

设 $dp[n]$ 为有 $2n$ 个点的划分方案数，考虑一小步的转移，我们选择长度为 $i$ 的点对连成线段，**因为它们不存在包含关系，所以只有在它们交叉的部分会形成子问题**，我们来讨论两种情况：

- 如果 $i\ge n$，那么在当前问题只有一种划分方案，但是递归下去会形成所有 $x<n$ 的子问题，所以这时候用 $ {\textstyle \sum_{i=0}^{n-1}} dp[i]$ 加上去即可。

- 如果 $i<n$，那么没有递归子问题，必须统计出所有线段没有公共部分的方案，这等价于把 $2n$ 划分成若干个连续段，每个连续段长度为偶数，设 $f[i]$ 为 $i$ **偶数真因数个数**，那么把 $f[2n]$ 加上去即可，这个很容易预处理。

时间复杂度 $\text {O(n\ log\ n)}$


### 参考代码

```
#include<bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
const int M = 2000005;
int n, f[M], dp[M];
int read(){
	int x = 0, f = 1;
	char c;
	while((c = getchar()) < '0' || c > '9'){
		if(c == '-') f = -1;
	}
	while(c >= '0' && c <= '9'){
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return x * f;
}
void init(int n){
	for(int i = 2; i <= n; i += 2){
		for(int j = 2 * i; j <= n; j += i) f[j] ++;
	}
}
signed main(){
	init(2e6);
	n = read();
	for(int i = 1, s = 1; i <= n; i ++){
		dp[i] = (s + f[2 * i]) % MOD;
		s = (s + dp[i]) % MOD;
	}
	printf("%d\n", dp[n]);
	return 0;
}

```

---

## 作者：Erica_N_Contina (赞：0)

# Kavi on Pairing Duty


## 思路

我们首先找到一些性质。首先，圆弧的个数为 $n$。其次，如果存在跨度为 $i$ 的圆弧（这里我们定义跨度 $i$ 为圆弧中包含了几个点，不包括圆弧两端的点），那么一定不存在跨度为 $i+1$ 的点。

我们可以尝试使用 dp 来解决此问题。

我们这里不能定义 $dp_{i}$ 为考虑到第$i$个点的情况数，因为这个问题中我们是大圆弧包小圆弧，大圆弧的左边是要在小圆弧左边的，因此我们总不能记录前面还有多少个空位吧？即使这样我们也不知道空位的位置。

也就是说，本题的 dp 转移不是按从前往后的顺序的，而是按嵌套从小到大的顺序的。也就是说 $dp_i$ 定义为当点的数量为 $2\times i$ 时的答案。

假设现在我们已经处理出了 $dp_1\sim dp_{i-1}$，那么我们要怎么转移到 $dp_i$ 呢？



现在我们来考虑转移。

![](https://cdn.luogu.com.cn/upload/image_hosting/j3o6de79.png)

第一种情况如上图，假设现在 $i=i$，一共有 $2\times i$ 个点，那么我们可以在外面嵌套 $k$ 个跨度为 $2\times i-k-1$ 的圆弧，在中间留下 $2\times i-2\times k$ 个点，这样我们就可以从 $dp_{2i-2k}$ 处转移过来了。


![](https://cdn.luogu.com.cn/upload/image_hosting/iqxtl2an.png)
还有一种情况，我们可以对这 $2\times i$ 个点进行分组，假设 $k$ 是 $2\times i$ 的约数，那么我们就可以把这 $2\times i$ 个点平均分成 $2i\div k$ 组，每一组如上图所示。

这里很显然我们要平均分，因为如果不平均分，我们就会出现点的重复使用或者空缺。

![](https://cdn.luogu.com.cn/upload/image_hosting/3trk89sl.png)
并且对于长度相同的，我们有且只有一种方法只使用统一大小的圆弧并且不重复不漏的使用所有的点。
![](https://cdn.luogu.com.cn/upload/image_hosting/tlpfiuwg.png)
故我们可以证明只有以上两种方法是合法，可以转移的。

那么总结一下，转移方程即为 $dp_i=\sigma (i) + \sum\limits_{k=1}^{i-1} dp_{k}$，其中 $\sigma(i)$ 定义为 $i$ 的约数的个数。

## 代码

```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5,MOD=998244353;

int n,a,b,x,y,ans,res,idx,cnt[N],dp[N];

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j+=i){
			cnt[j]++;//预处理约数的个数
			cnt[j]%=MOD;
		}
	}
	dp[1]=1;
	for(int i=1;i<=n;i++){
		dp[i]=cnt[i];
		for(int k=1;k<=i-1;k++)dp[i]+=dp[k],dp[i]%=MOD;
		
	}
	
	cout<<dp[n]<<endl;
	   return 0;
}

```




---

## 作者：XSean (赞：0)

[Problem - 1528B - Codeforces](https://codeforces.com/problemset/problem/1528/B)

## 基本思路：

思路：

设 $f[i]$ 为 $i$ 组点的合法状态数，$ynum[i]$ 为 $i$ 的约数个数。

可以发现这道题的图形状态只有两种：

1. 分为若干组，最多分为 $n$ 的约数种。

![](https://cdn.luogu.com.cn/upload/image_hosting/8ir72g96.png?x-oss-process=image/resize,m_lfit,h_400,w_400)

2. 从外往内包围，因为要求任意不等大的圆弧必然为包含关系。共有 $\sum_{j = 1}^{i-1}f[j]$ 种情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/6rgc9yg0.png?x-oss-process=image/resize,m_lfit,h_400,w_400)

所以：
$$
f[i] = ynum[i] + \sum_{j = 1}^{i-1}f[j]
$$

## 代码实现：

在实现的过程中 $f[i]$ 是前缀和的意思，所以表达式最后变成了：
$$
f[i]=2\times f[i-1]+ynum[i]-ynum[i-1]
$$
核心代码：

```cpp
//bool stt;
const int N = 1e6 + 10;
const int mod = 998244353;
int n;
LL f[N], ynum[N];
//bool edd;
int main(){
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
//	cerr << (&edd - &stt) / 1024.0 / 1024.0 << endl;
	rd(n);
	rep(i, 1, n) for(int j = i; j <= n; j += i) ynum[j]++;
	f[1] = 1;
	rep(i, 2, n) f[i] = (((f[i - 1] << 1) + ynum[i] - ynum[i - 1]) % mod + mod) % mod;
	prf("%d\n", f[n]);
	return 0;
}
```

**[完整代码](https://codeforces.com/contest/1528/submission/219936912)**



---

