# [USACO09FEB] Bulls And Cows S

## 题目背景

一年一度的展会要来临了，Farmer John 想要把 $N$（$1 \leq N \leq 100,000$）只奶牛和公牛安排在单独的一行中。 John 发现最近公牛们非常好斗；假如两只公牛在这一行中靠的太近，他们就会吵架，以至于斗殴，破坏这和谐的环境。

## 题目描述

John 非常的足智多谋，他计算出任何两只公牛之间至少要有 $K$（$0 \leq K \lt N$）只奶牛，这样才能避免斗殴。John 希望你帮助他计算一下有多少种安排方法，可避免任何斗殴的的发生。John 认为每头公牛都是一样的，每头奶牛都是一样的。因而，只要在一些相同的位置上有不同种类的牛，那这就算两种不同的方法。

## 说明/提示

下面的就是 FJ 思考出可行的 6 种方案（C 代表奶牛，B 代表公牛）：
- CCCC
- BCCC
- CBCC
- CCBC
- CCCB
- BCCB

## 样例 #1

### 输入

```
4 2```

### 输出

```
6```

# 题解

## 作者：houzhiyuan (赞：21)

# P6191 【[USACO09FEB]Bulls And Cows S】

##  [题目传送门](https://www.luogu.com.cn/problem/P6191)

## 管理员大大，这只是个更新，审核求过

## 1.递推做法（速度较快，适合初学者）

这题是一个十分恶心的递推。

怎么推递推式呢，先看各种错误方法的分析：

### 1.由于两头公牛之间至少有k头奶牛，那么直接加上前i-k头奶牛的可能性，得到以下代码：
```cpp
f[i]=f[i-1];//放奶牛
if(i>k+1)f[i]+=f[i-k-1];//放公牛
```
然而，听取WA声一片。为什么呢？因为可以在i的地方放公牛的方案i-k没有全部包括进去，考虑将公牛和奶牛分开。

### 2.用两个数组储存最后一个放奶牛和公牛的方案数，得到以下代码：
```cpp
fn[i]=fn[i-1]+fg[i-1];//前面一个无论是什么，都可以放奶牛
if(i>k+1)fg[i]=fg[i-k-1];//放公牛
```
然而还是错的。**因为当i-k-1位置就算放奶牛，第i个位置仍然可以放公牛，并且当`i<=k+1`时，可以直接放一头公牛。**

得到正确的递推式：
```cpp
fn[i]=fn[i-1]+fg[i-1];
if(i>k+1)fg[i]=fg[i-k-1]+fn[i-k-1];
else fg[i]=1;
```
附上完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int fn[100001],fg[100001],n,k;
int main(){
	cin>>n>>k;
	fn[1]=1;//先赋初值
	fg[1]=1;
	for(int i=2;i<=n;i++){
		fn[i]=(fn[i-1]+fg[i-1])%5000011;
		if(i>k+1){//上面的递推式
			fg[i]=(fg[i-k-1]+fn[i-k-1])%5000011;
		}
		else{
			fg[i]=1;	
		}
	}
	cout<<(fg[n]+fn[n])%5000011<<endl;
	return 0;
}
```
## 2.组合做法（速度较慢，对于大佬来说较为简单）


###### ~~（下面是初学组合者教学，大佬勿喷）~~
从 n 个不同元素中，任取 m $( m\leq n )$ 个元素组成一个集合，叫做从 n 个不同元素中取出 m 个元素的一个组合；，叫做从 n 个不同元素中取出 m 个元素的组合数。用符号 $\mathrm C_n^m$ 来表示。

即$\mathrm C_n^m = \frac{\mathrm A_n^m}{m!} = \frac{n!}{m!(n - m)!}$

求组合数可以用乘法逆元，详情见[乘法逆元](https://www.luogu.com.cn/problem/P3811)

那么我们枚举放的公牛数，每放一头公牛，可以放公牛的位置就会$-k$，在这些位置中随意拿出$i$个位置来放公牛就是方案数，即 

$$ \sum_{i=0}^{n/(k+1)} \mathrm C_{n-k*i}^i  $$

由于处理$i$循环上线的问题，将原式变成： 

$$ (\sum_{i=0}^{(n-1)/(k+1)} \mathrm C_{n-k*i}^{i+1})+1  $$

问题得以解决。

---

## 作者：zplqwq (赞：11)

# Bulls And Cows题解

ello 我们来看下这道题

看到这道题，一般不是**很容易**想到dp，尤其是初学者。

因为dp在初学者（起码是我）印象中是专门处理**最优解**问题的。

但是，dp其实还可以处理一下问题：

- 最优解
- 总和
- 判断对错
- ....

## 题目分析

既然提到了dp，那么我们就开始顺着dp的方向想。

首先，我们需要考虑**第一步选择**是啥。

如何考虑这个问题？

- 其实这道题你可以考虑最后一个位置（或者第一个位置）放奶牛还是公牛

这就是我们的第一步选择。

做出第一步选择后，我们可以发现这个问题就转化成了一个几乎同样的子问题。

为什么？

我们分两种情况讨论：

- 第一种，如果要是最后一个位置（或者第一个位置）放的是奶牛，那么，我们就直接考虑第n-1个位置是公牛还是母牛，因为在第n个位置放奶牛并不影响前面的任何一个位置。
- 第二种，如果要是最后一个位置（或者第一个位置）放的是公牛，那么，我们第n-k-1个位置放公牛还是母牛，因为在第n个位置放公牛就代表着n~n-k之间的位置已经固定了。

综上，最后的$dp[i]$其实就是$dp[i-1]+dp[i-k-1]$。

最后，还有一个问题，初始化。

我们如何考虑？

首先，我们需要知道什么东西需要初始化。

- dp[0~k]
- 因为他们之间是不可能有>2头公牛的。

其次，要考虑初始值。

- dp[i]=i+1

好！那现在你们应该会写了吧...

对了，别忘了**取模**

关键代码：

```c++
	for(int i=0;i<=k;i++)
	{
		dp[i]=i+1; 
	}
	for(int i=k+1;i<=n;i++)
	{
		dp[i]+=dp[i-1]+dp[i-k-1];
		dp[i]%=5000011;
	}
```





---

## 作者：Soohti (赞：7)

# 组合数学解法  

------------

### 前置知识  

- [排列组合](https://oi-wiki.org/math/combination/)
- [乘法逆元](https://oi-wiki.org/math/inverse/)  

### 思路  

首先，我们可以发现，放置公牛的数量是**无限制**的。  

从放置 $1$ 头公牛开始考虑，此时该公牛可放在任何位置。  
考虑放 $2$ 头公牛，此是必须在它们之间放 k 头奶牛，公牛可以放置的格子数为 $n-k$ 。  
考虑放 $3$ 头公牛，此时必须在1和2、2和3之间都放 k 头奶牛，公牛可以放置的格子数为 $n-2\times k$。  

由此类推，放 $i$ 头公牛时，共放置了 $(i-1)\times k$ 头奶牛，公牛可以放置的格子数为 $n-(i-1)\times k$ 。  

在这些格子数种放 $i$ 头公牛，方案数即为 $\displaystyle \binom{n-(i-1)\times k}{i}$ 。  

由于放置公牛的数量没有限制，故总方案数为 $\sum_{i=0}^n\binom{n-(i-1)\times k}{i}$ 。  

然而掌握了这些还不够，还需要用逆元的知识对组合数进行取模运算~~以及将 `int` 转换为 `long long` 防止溢出~~。  

### 代码  

```cpp
#include<bits/stdc++.h>
using namespace std;
const int p=5000011;
int fac(int x){
	int res=1;
	for(int i=2;i<=x;i++)res=1LL*res*i%p;
	return res;
}
int pmod(int a,int b){
	int res=1;
	for(;b;b>>=1,a=1LL*a*a%p)if(b&1)res=1LL*res*a%p;
	return res;
}
int C(int n,int m){
	if(n<m)return 0;
	return 1LL*fac(n)*pmod(fac(m),p-2)%p*pmod(fac(n-m),p-2)%p;
}
int main(){
	int n,k,ans=0;
	cin>>n>>k;
	for(int i=0;i<=n;i++)ans=(ans+C(n-(i-1)*k,i))%p;
	cout<<ans;
	return 0;
}
```


---

## 作者：A_Đark_Horcrux (赞：4)

用 $f_{i,0/1}$ 表示第 $i$ 位是/不是公牛的方案数，0代表不是，1代表是。

如果当前位不是公牛，则前一位是或不是都无所谓，则 $f_{i,0}=f_{i-1,0}+f_{i-1,1}$ 

如果当前位是公牛，那上一头公牛只能是第 $i-k-1$ 头牛或之前的某一头牛。由于我们是顺推，上一头公牛在前面的方案数已经包含在第 $i-k-1$ 头牛的方案数中。所以 $f_{i,1}=f_{i-k-1,0}+f_{i-k-1,1}$ 

递推式已经出来了，还有考虑一下初始化。最开始的 $i\;(i \leq k+1)$ 头牛里最多只有1头公牛，因此 $f_{i,1}=1;$ 在考虑 $f_{i,0}$ ，如果放一头公牛，这一头公牛有 $i-1$ 种可能的位置，加上没有公牛的一种情况，$f_{i,0}=i-1+1=i.$ 

然后就搞定啦awa

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int mod=5000011;
int n,k,i,j,f[100010][2];
int main()
{
	scanf("%d %d",&n,&k);
	for(i=1;i<=k+1;i++) f[i][1]=1,f[i][0]=i;//初始化
	for(i=k+2;i<=n;i++)
	{
		f[i][1]+=(f[i-k-1][0]+f[i-k-1][1])%mod;
		f[i][0]+=(f[i-1][0]+f[i-1][1])%mod;//递推
	}
	printf("%d",(f[n][0]+f[n][1])%mod);//输出最后一位放与不放的总方案数
	return 0;//完结awa
}
```


---

## 作者：yinhee (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P6191)

解题思路：组合数+逆元

看到题面时，可以产生一个简单的思路：枚举公牛的数量 $i$，计算每个 $i$ 所有的情况数。

但我们会发现一个问题：由于公牛之间的距离，这个情况数不好直接计算。那我们就要把它转换成最简单的情况：公牛之间距离为 $1$。此时母牛数量为 $j$，情况数明显为 $C^i_{j+1}$。

那我们该怎么把所以情况转变为这种情况呢？可以想到，既然他原来要求相距 $k$ 头母牛，不如直接把每两头牛之间需要的 $k-1$ 头母牛删去，剩下的就可以直接按照上述方法计算了。所以当有 $i$ 头公牛时，情况数就为 $C^i_{j-i}$。

code：

```cpp
#include<cstdio>
#include<cmath>
#include<cstring>
#include<iostream>
#include<iomanip>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn=1e5+7,inf=2147483647;
const ll mod=5e6+11;
ll n,m,ans;
ll qpow(ll x,ll y){
	if(y==1)return x%mod;
	ll now=qpow(x,y>>1);
	return y&1?now*now%mod*x%mod:now*now%mod;
}
ll solve(ll x,ll y){
	ll a=1,b=1;
	for(ll i=y;i>=y-x+1;i--)a=a*i%mod;
	for(ll i=1;i<=x;i++)b=b*i%mod;
	return a*qpow(b,mod-2)%mod;//逆元
}
signed main(){
	scanf("%lld%lld",&n,&m);n++;
	for(ll i=1;2*i<=n;i++){
		ans=(ans+solve(i,n-i)%mod);
		n-=m-1;//每多一头公牛，就多删去m-1头母牛
	}
	printf("%lld",(ans+1)%mod);//最后别忘了全是母牛的情况
}
```

---

## 作者：dbodb (赞：2)

为了简化，将两种牛分成01。

状态表示：f[i]f[i]表示有i个数，最后一位是1的方案总数。

划分转移：倒数第二个1的位置。

因为两个1之间必须有k个0隔开，所以上一个1只能从$f[i-k-1]$转移过来

状态计算：

$ f [ i ] = f [ i − k − 1 ] + f [ i − k − 2 ] + … + f [ 0 ]$

状态划分：求的是所有方案，将所有方案以最后一个1所在位置划分为：

第0位(没有1)、第一位、第二位、… ，即$f[0]+f[1]+f[2]+…+f[n]$也就是f[]数组的前缀和，同时发现$f[i]$也

就等于$s[i-k+1]$，于是我们可以维护一个前缀和$s$，这样可把时间复杂度由$O(n^2)$变成$O(n)$

代码

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 100010 , mod = 5000011 ;
int f[N] , s[N];
int main()
{
    int n , k;
    cin >> n >> k;
    f[0] = s[0] = 1;//当i-k-1<0时，因为在i是1前面全是0的方案是可行的，所以为了加上这个方案，需要把f[0]设置为0
    for(int i = 1 ; i <= n ; i++)
    {
        f[i] = s[max(i - k - 1 , 0)];
        s[i] = (s[i - 1] + f[i]) % mod;
    }

    cout << s[n] << endl;
    return 0;
}

```





---

## 作者：pitiless0514 (赞：2)

# P6191 【[USACO09FEB]Bulls And Cows S】
##### 1.题目：年一度的展会要来临了，Farmer John 想要把 N（1≤N≤100,000）只奶牛和公牛安排在单独的一行中。 John 发现最近公牛们非常好斗；假如两只公牛在这一行中靠的太近，他们就会吵架，以至于斗殴，破坏这和谐的环境。两只公牛之间至少要有 K（0≤K<N）只奶牛，这样才能避免斗殴。
------------
2.题目重点：两只公牛之间至少要有 K（0≤K<N）只奶牛，这样才能避免斗殴。

### 3.选方法：我们在题目中很明显看出这道题可以用dp来做，而更明显的是组合，既然已经有两个大佬写了dp，~~我dp又没做~~，那我就来写组合吧
### 4.组合定义：
从n个不同元素中取出 m个元素进行组合（不考虑顺序），产生的不同组合数量，称为组合数用符号C（m,n）来表示。
tips:我不会数学符号


------------

#### 5.分为奶牛和公牛，公牛之间要间隔，所以我们就枚举公牛的数量，设有x头公牛，则就一定有（x-1）*k头奶牛，理由如下：
      1     2     3
      设有三头公牛，那么他们之间间隔k头奶牛，也就是：
      
     1CCC2CCC3，这里设k=3。又因为x头公牛，
     中间有（x-1）个间距，所以为(x-1)*k头奶牛。
#### 那么由此可得，公牛也只能在n-（x-1）*k个位置上选，（总共n头牛，奶牛占了（x-1)*k个位置）。所以方案数就是C（x,n-(x-1)*k），那么这里还要注意两个地方，【1】那就是有可能位置不够选，所以到x>n-(x-1)*k时退出。【2】可以一头公牛都没有，所以最后答案加1
   ```cpp
	long long ans=1; //还有一头
	for(int i=1;i<=n;i++){
		long long temp=n-k*(i-1);//公牛选的位置
		if(i>temp)break;//特判
		ans+=Lucas(temp,i)%p;//Lucas定理求组合
	}
```


------------

### 【6】关键！：
因为这里的n值较大，所以直接算会超时，而且内存也不一定够。所以我们选择用Lucas定理来算要快一点：
```cpp
long long power(long long a,long long b){
    long long ans=1;
    while(b){
    if(b&1) ans=(ans*a)%p;
    b>>=1;
    a=(a*a)%p;
    }
    return ans%p;
}//快速幂，很有用
long long C(long long n,long long m）{	
long long a=1,b=1;
for(long long i=n-m+1;i<=n;i++)	a=(a*i)%p;
for(long long i=2;i<=m;i++)	b=(b*i)%p;
return (a*power(b,p-2))%p;	
}
long long Lucas(long long x,long long y){
	if(!y) return 1; 
	if(x<y) return 0;
	if(x<p&&y<p)	return C(x,y);
 return ((Lucas(x%p,y%p)%p*Lucas(x/p,y/p))%p)%p;
}
```
最后附上完整代码：
```cpp

#include<bits/stdc++.h>//
#pragma GCC optimize(2)//O2优化
#pragma GCC optimize(3,"Ofast","inline")//O3优^_^
#define p 5000011
int n,k;
using namespace std;
long long power(long long a,long long b){
    long long ans=1;
    while(b){
    if(b&1) ans=(ans*a)%p;
    b>>=1;
    a=(a*a)%p;
    }
    return ans%p;
}
long long C(long long n,long long m)	 
{	
	long long a=1,b=1;
	for(long long i=n-m+1;i<=n;i++)	a=(a*i)%p;
	for(long long i=2;i<=m;i++)	b=(b*i)%p;
	return (a*power(b,p-2))%p;	
}
long long Lucas(long long x,long long y){
	if(!y) return 1; 
	if(x<y) return 0;
	if(x<p&&y<p)	return C(x,y);
	return ((Lucas(x%p,y%p)%p*Lucas(x/p,y/p))%p)%p;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin>>n>>k;
	long long ans=1;
	for(int i=1;i<=n;i++){
		long long temp=n-k*(i-1);
		if(i>temp)break;
		ans+=Lucas(temp,i)%p;
	}
	cout<<ans%p;
	return 0;
} 
```
### 拜拜！





---

## 作者：VitrelosTia (赞：1)

少见的自己推出来的数学题，好像题解区没有类似的思路，写篇题解纪念一下。

大力枚举公牛的数量 $a$ 和奶牛的数量 $b$。对于每两头公牛，他们中间都必须有 $k$ 头奶牛，又因为同类牛之间两两相同，所以可以直接排出必须要有的基本队列，举个例子，$a = 3, k = 2$ 的时候就先排成 ```BCCBCCB```。

那么现在就剩下 $b - a\times(k - 1)$ 只奶牛了，这些奶牛就可以随便放到两头公牛中间或者队列两侧，也就是 $a + 1$ 个位置。这就是最经典的插板法问题。

由于本人懒得考虑枚举 $a, b$ 的值域，所以求组合数时特判一些情况。
```cpp
#define int long long
int C(int n, int m) {
	if (n < 0 || m < 0 || n - m < 0) return 0;
	return fac[n] * infac[m] % p * infac[n - m] % p;
}
int lemma(int n, int m) { // n 个相同球放 m 个不同盒子
	return C(n + m - 1, m - 1);
}

signed main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int n, k; cin >> n >> k;
	int ans = 0; init(N - 1);
	for (int a = 0; a <= n; a++) {
		int b = n - a;
		ans = (ans + lemma(b - (a - 1) * k, a + 1)) % p;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Gaode_Sean (赞：1)

设 $f_i$ 为第 $i$ 头牛是奶牛，$1 \sim i$ 头牛有几种排列方法。

设 $g_i$ 为第 $i$ 头牛是公牛，$1 \sim i$ 头牛有几种排列方法。

那么初始化 $f_i=g_i=1$。

因为奶牛的位置不用受前面的牛的影响，所以 $f_i=f_{i-1}+g_{i-1}$

若第 $i$ 头牛为公牛，则默认 $i-k \sim i-1$ 这 $k$ 头牛全为奶牛。则 $g_i=f_{i-k-1}+g_{i-k-1}$。

## AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+2,mod=5000011;
int n,k,f[maxn],g[maxn];
int main()
{
	scanf("%d%d",&n,&k);
	f[1]=g[1]=1;
	for(int i=2;i<=n;i++){
		f[i]=(f[i-1]+g[i-1])%mod;
		if(i<=k+1) g[i]=1;
		else g[i]=(f[i-k-1]+g[i-k-1])%mod;
	}
	printf("%d",(f[n]+g[n])%mod);
	return 0;
}
```

---

## 作者：Skies (赞：0)

### 这道题的思路比较普通，比较好理解, 代码也精简
## 思路
递推，f[n]表示：

#### 前n头牛，在n这个位置上放一头公牛的解的数量

因为要间隔k头牛，所以倒数第二头牛的位置可以是0（表示没有公牛）,1~n-k-1

所以
$$
f[i]=\Sigma_{j=0}^{i-k-1}f[j]
$$

很容易发现这是一个前缀和，所以我们可以再开一个数组s[]记录前缀和

$$
s[j]=\Sigma_{i=0}^{j}f[i]
$$

这样我们就可以再O(1)的时间内获得f[i]的值了

那如何统计答案？

$$
ans=\Sigma_{i=0}^{n}f[i]=s[n]
$$

为什么？

因为对于f[i],并没有考虑i后面(即i+1~n)中有公牛

所以把它们累加起来即可

# code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m;
int f[N],s[N];
int mod=5000011;

int main()
{
	cin>>n>>m;
	f[0]=s[0]=1;
	for(int i=1;i<=n;i++)
	{
		f[i]=s[max(0,i-m-1)];//如果i-m-1<0,说明随便放公牛
		s[i]=(s[i-1]+f[i])%mod;//维护s[]数组
//		cout<<i<<":"<<f[i]<<" "<<s[i]<<endl;
	}
	cout<<s[n];//输出ans
	
	return 0;
}
```
~~管理员小哥哥辛苦！~~

---

