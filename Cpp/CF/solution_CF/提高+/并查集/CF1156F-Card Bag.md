# Card Bag

## 题目描述

你有一个装有 $n$ 张卡牌的卡包，卡包中第 $i$ 张卡牌上写有数字 $a_i$。在接下来的每一个回合，你会从卡包中等概率随机抽出一张卡牌，每一回合抽出的卡牌不会重新放回卡包中。

从第二回合开始，每一回合，你需要对这一回合抽出的卡牌的点数 $x$ 和上一次抽出的卡牌的点数 $y$ 进行比较：

- 如果 $x < y$，游戏失败并结束；
- 如果 $x = y$，游戏胜利并结束；
- 如果 $x > y$，游戏继续。

如果某一次抽牌的时候卡包中没有牌，则游戏失败。

你需要求出游戏胜利的概率，对 $998244353$ 取模。

## 说明/提示

$2 \leq n \leq 5000$，$1 \leq a_i \leq n$。

## 样例 #1

### 输入

```
5
1 1 4 2 3
```

### 输出

```
299473306
```

## 样例 #2

### 输入

```
2
2 2
```

### 输出

```
1
```

## 样例 #3

### 输入

```
5
4 5 1 3 2
```

### 输出

```
0
```

## 样例 #4

### 输入

```
4
1 3 4 3
```

### 输出

```
748683265
```

# 题解

## 作者：Alex_Wei (赞：30)

> [题目传送门](https://www.luogu.com.cn/problem/CF1156F)。

> 题意简述：有 $n$ 张卡牌，每张卡牌有数字 $a_1,a_2,\cdots,a_n$。现在随机抽取卡牌，不放回，设本次抽到的卡牌为 $x$，上次抽到的卡牌为 $y$，若 $x=y$ 则游戏胜利；若 $x<y$ 则输掉游戏；若 $x>y$ 则游戏继续。求获胜概率。

> $a_i\leq n\leq 5\times 10^3$。

下文认为 $a_i$ 与 $n$ 同阶。

---

不难发现我们只关心卡牌上的数字，所以开个桶维护每个数出现了几次。又因为只能从小往大抽，即无后效性，所以考虑 DP。

设 $f_{i,j}$ 为 **共抽了 $j$ 次，每个数最多抽到一次，最后一次抽到数字 $i$** 的概率。

首先考虑如何转移：我们设数字 $i$ 共有 $sz_i$ 个，那么不难列出转移方程

$$f_{i,j}=\sum_{k=0}^{i-1}f_{k,j-1}\times \frac{sz_i}{n-j+1}$$

表示 **在 $[1,i-1]$ 中抽了 $j-1$ 个数** 的概率乘上 **抽到数字 $i$** 的概率。这样转移的时间复杂度为 $\mathcal{O}(n^3)$，无法接受。

如果设 $s_{i,j}$ 为 **在 $i$ 中抽了 $j$ 个数** 的概率，则有

$$s_{i,j}=\sum_{k=1}^{i}f_{i,j}$$

则转移方程可变形为

$$f_{i,j}=\frac{s_{i-1,j-1}sz_i}{n-j+1}$$

预处理逆元做到时间复杂度 $\mathcal{O}(n^2)$，可以接受。

~~这实际上就是具有实际意义的前缀和优化。~~

最后使用滚动数组可以将空间优化到 $\mathcal{O}(n)$。

需要注意初始值 $f_{0,0}=1$。

```cpp
const int N=5e3+5;
ll n,ans,sz[N],f[2][N],s[2][N];
int main(){
	init(),cin>>n,s[0][0]=s[1][0]=1;
	for(int i=1,a;i<=n;i++)cin>>a,sz[a]++;
	for(int i=1,p=1;i<=n;i++,p^=1){
		for(int j=1;j<=i;j++){
			f[p][j]=s[p^1][j-1]*sz[i]%mod*iv[n-j+1]%mod;
			ans=(ans+s[p^1][j-1]*sz[i]*(sz[i]-1)%mod*iv[n-j+1]%mod*iv[n-j])%mod;
			s[p][j]=(s[p^1][j]+f[p][j])%mod;
		}
	} cout<<ans<<endl;
	return 0;
}
```


---

## 作者：too_simple (赞：17)

前言：这道题的思路和原有题解的做法的不太一样，所以决定写一篇题解

---

题意告诉我们只管关心卡牌上的数字，所以我们开个 $cnt$ 数组记录一下每个数出现了几次。

由于本人太菜了，一看到概率就头大，所以联想到了一个很经典的套路，我们计算合法排列的数量，除以全排列的数量，就是答案了。

然后我们发现合法的序列一定是从小到大填数，因此无后效性，所以我们考虑动态规划。

设 $f_{i,j}$ 为我们已经把小于等于 $i$ 的数填进序列里，最后一个数填的 $i$ ，已经填了 $j$ 个数，且没有两个相同的数字的方案数， $g_{i,j}$ 为答案数组，表示我们已经把小于等于 $i$ 的数填进序列里，最后两个数填的，已经填了 $j$ 个数，且只有最后两个数相同的方案数，可以发现每一个 $g_{i,j}$ 就是一个合法的操作过程，同时我们把没用到的数填到这些数之后就是对应的合法排列的数量。

综上， $ans = \sum\limits_{i = 1}^n\sum\limits_{j = 1}^ng_{i,j} * fac_{n-j}$

但是直接转移是 $n^3$ 的，我们考虑优化，~~实际上也没有太难~~，其实也就是加上一个前缀和，具体实现看代码。

### 代码

---

```c++
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

#define int long long

using namespace std;

const int N = 5050, mod = 998244353;

int n, a[N], cnt[N];
int f[N][N], g[N][N];
int fac[N], s[N];

int qmi(int b, int k) {
    int res = 1;
    while(k) {
        if(k & 1) res = res * b % mod;
        b = b * b % mod;
        k >>= 1;
    }
    return res;
}

int C(int v) {
    return v * (v - 1) % mod;
}

signed main() {
    
    cin >> n;
    
    fac[0] = 1;
    
    for(int i = 1; i < N; ++ i) {
        fac[i] = fac[i - 1] * i % mod;
    }
    
    for(int i = 1; i <= n; ++ i) {
        cin >> a[i];
        cnt[a[i]] ++;
    }
    
    s[0] = 1;
    
    for(int i = 1; i <= n; ++ i) {
        for(int j = n; j >= 1; -- j) {
            f[i][j] = s[j - 1] * cnt[i] % mod;
            g[i][j + 1] = s[j - 1] * C(cnt[i]) % mod;
            s[j] = (s[j] + f[i][j]) % mod;
        }
    }
    
    int ans = 0;
    
    for(int i = 1; i <= n; ++ i) {
        for(int j = 1; j <= n; ++ j) {
            ans = (ans + g[i][j] * fac[n - j] % mod) % mod;
        }
    }
    
    cout << ans * qmi(fac[n], mod - 2) % mod << endl;
    
    return 0;
}
```



---

## 作者：zhimao (赞：4)

此题我有一个奇奇怪怪的做法，还跑得飞快，~~暂时~~上了第一~~马上会被赶下~~。
## 分析
首先离散化，搞出点数从大到小的每种牌各有几张。

考虑枚举每组胜利卡牌最后抽的相同两张，设为点数第 i 小的，则之前还可以从前 i-1 种各取一张牌或不取。再枚举一共取 j 张牌，m每组牌有 $\frac{(n-j)!}{n!}$ 的概率抽到，那么我们只要算出有多少组最后两张牌是点数第 i 小的。设点数第 i 小的牌有 $a_i$ 张，从前 i-1 种牌中**合法地**取 j-2 张 的方案数为 $s_{i-1,j-2}$ ，则总方案数为 $a_i\times (a_i-1)\times s_{i-1,j-2}$ ，所以问题就转化为求 $s_{i,j}$ ,这个其实很简单， $s_{i,j}=s_{i-1,j}+s_{i-1,j-1}\times a_i\ s_{i,1}=\sum_{j=1}^ia_j$ ,读者可以自行思考。

小细节：阶乘要预处理，不然会 T 飞。同时 s 数组可以滚动优化一下，让空间变为 $O(n)$ 。

## 代码
真不明白为什么这么快？？？

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=998244353;
long long x,y,inv,ans,s1[10000],s2[10000],a[10000],k,jc[10000];
int n;
void exgcd(int a,int b)
{
	if(b==0)
	{
		x=1;y=0;
		return;
	}
	exgcd(b,a%b);
	long long z=x;
	x=y;
	y=z-(a/b)*y;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		++a[x];
	}
	jc[1]=jc[0]=1;
	for(int i=2;i<=n;i++) jc[i]=jc[i-1]*i%mod;
	exgcd(jc[n],mod);
	inv=(x%mod+mod)%mod;
	s2[0]=1;
        int boo=0;
	for(int i=1;i<=n;i++)
		if(a[i])
		{
			if(a[i]>1)
			{
				boo=1;
				long long anss=0;
				for(int j=0;j<=k;j++) anss=(anss+jc[n-j-2]*s2[j])%mod;
				ans=(ans+(a[i]-1)*a[i]%mod*anss)%mod;
			}
			++k;
			for(int j=1;j<=k;j++) s1[j]=s2[j];
			s2[1]=s1[1]+a[i];
			for(int j=2;j<=k;j++) s2[j]=(s1[j]+s1[j-1]*a[i])%mod;
		}
	if(!boo) puts("0");
	else
	{
		ans=(ans*inv)%mod;
		printf("%lld",ans);
	}
}
```


---

## 作者：feecle6418 (赞：3)

比较简单的概率 dp。

题意可以写为：求选到一个递增子集之后再选到与最后一个数相同的数的概率。

首先离散化，设 $cnt_i$ 为 $i$ 出现的次数，$f_{i,j}$ 为选从小到大前 $i$ 个数，选了 $j$ 个（$i$ 必须选，不必赢）的概率，则：

$$f_{i,j}=\dfrac{cnt_i}{n-j+1}\sum_{k=0}^{i-1} f_{k,j-1}$$

意思是枚举上一个选的数。显然可以用前缀和优化，时间复杂度 $O(n^2)$。答案等于 $\sum\limits_{i,j} f_{i,j}\dfrac{cnt_i-1}{n-j}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=998244353;
int ans=0,n,m,b[5005],cnt[5005],a[5005],f[5005][5005],sum[5005][5005],ny[5005]={0,1};
int main(){
	cin>>m;
	for(int i=1;i<=m;i++)cin>>b[i];
	for(int i=2;i<=m;i++)ny[i]=1ll*(mod-mod/i)*ny[mod%i]%mod;
	sort(b+1,b+m+1);
	for(int i=1;i<=m;i++)if(b[i]^b[i-1])a[++n]=b[i],cnt[n]=1;else cnt[n]++;
	sum[0][0]=1;
	for(int i=1;i<=n;i++){
		sum[i][0]=1;
		for(int j=1;j<=i;j++){
			f[i][j]=1ll*sum[i-1][j-1]*cnt[i]%mod*ny[m-j+1]%mod;
			sum[i][j]=(sum[i-1][j]+f[i][j])%mod;
			ans=(ans+1ll*f[i][j]*ny[m-j]%mod*(cnt[i]-1))%mod;
		}
	}
	cout<<ans;
    return 0;
}
```

---

## 作者：Feyn (赞：2)

[link](https://www.luogu.com.cn/problem/CF1156F) & [my blog](https://feynn.github.io/)

思考取卡的过程。你胜利的过程肯定是这样的：先取了一个单升的序列，然后下一个刚好拿到了一个和前一个卡一样的卡。所以我们就对这两个阶段分别计算。

第一个阶段，显然用 $f_{x,y}$ 代表选出来一个以 $x$ 结尾、长度为 $y$ 的串的概率。显然有 $O(N^3)$ 的做法：

$$f_{x,y}=\sum\limits_{t<x}f_{t,y-1}\times\frac{num_x}{m+1-y}$$

含义是说枚举上一次取的数 $t$，用它的概率乘上下一个刚好取到 $x$ 的概率（总共有 $m+1-y$ 个数没取，其中有 $num_x$ 个 $x$），累加即可。发现系数只和 $x,y$ 有关。所以对 $f$ 做前缀和即可。然后就是 $O(N^2)$ 的了。

第二个阶段更加简单，当前还有 $m-y$ 个数没选，而还剩下 $num_x-1$ 个数，乘起来即可。

```cpp
#include<bits/stdc++.h>
//#define feyn
#define int long long 
using namespace std;
const int N=5010;
const int mod=998244353;
inline void read(int &wh){
	wh=0;char w=getchar();int f=1;
	while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
	while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
	wh*=f;return;
}
inline int qp(int s1,int s2){
	if(s2==1)return s1;int an=qp(s1,s2>>1);
	if(s2&1)return an*an%mod*s1%mod;else return an*an%mod;
}

int m,a[N],num[N],f[2][N],inv[N],ans;

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);for(int i=1;i<=m;i++)read(a[i]),num[a[i]]++;
	f[0][0]=1;for(int i=1;i<=m;i++)inv[i]=qp(i,mod-2);
	for(int len=1;len<=m;len++){
		int nowSum=f[len+1&1][0];
		memset(f[len&1],0,sizeof(f[len&1]));
		for(int x=1;x<=m;x++){
			if(num[x]==0)continue;
			f[len&1][x]=nowSum*num[x]%mod*inv[m+1-len]%mod;
			ans=(ans+f[len&1][x]*(num[x]-1)%mod*inv[m-len]%mod)%mod;
			nowSum=(nowSum+f[len+1&1][x])%mod;
		}
	}
	printf("%lld\n",ans);
	
	return 0;
}
```

---

## 作者：littlebug (赞：1)

很容易的概率 dp。

## Solution

首先我们发现，每个数的具体值是不重要的，有用的只有相对大小，于是可以离散化一下，设卡牌种类数为 $m$，设第 $i$ 种卡牌的数量为 $c_i$。

显然，在这个博弈过程中，「继续」这一状态是重要的，只要得知了达到「继续」状态的概率，就能知道「胜利」的概率了。而又由于满足「继续」状态的时候，选的卡牌只能越选越大，且不能重复选，于是我们可以设 $f_{i,j}$ 为只考虑前 $i$ **种**卡牌，选 $j$ 张且第 $i$ 种必选，可以达到「继续」状态的概率。

转移是容易的，考虑之前选的牌数和选中当前牌的概率即可，可以得到柿子：

$$
f_{i,j} = \frac {c_i} {n-j+1} \sum _{k=0} ^{i-1} f_{k,j-1}
$$

直接转移是 $O(n^3)$ 的，不过可以前缀和把那个 $\sum$ 优化掉，复杂度 $O(n^2)$。

那么统计答案也很简单了，考虑每种「继续」的情况可以直接达到「胜利」状态的概率即可。则答案为：

$$
\sum _{i=1} ^m \sum _{j=1} ^i (\frac {c_i-1} {n-j} f_{i,j})
$$

总复杂度 $O(n^2)$。

如果你 TLE on #7 或以后，注意要预处理逆元做到 $O(n^2)$ 而不是每次 $O(\log n)$ 计算逆元。

## Code

```cpp
signed main()
{
    //freopen(".in","r",stdin),freopen(".out","w",stdout);
    ios::sync_with_stdio(0),ios_base::sync_with_stdio(0),cin.tie(nullptr),cout.tie(nullptr);

    init_inv(0); // 预处理逆元

    read(n); _::r(a,n);
    int m=disc(a,n); // 离散化
    sort(a+1,a+n+1);
    rep(i,1,n) ++c[a[i]];

    f[0][0]=s[0][0]=1;
    rep(i,1,m) s[i][0]=1;
    rep(i,1,m) rep(j,1,i)
    {
        f[i][j]=c[i]*ginv(n-j+1)%mod*s[i-1][j-1]%mod; // ginv(x) 的意思是得到 x 的逆元
        s[i][j]=(s[i-1][j]+f[i][j])%mod;
    }

    int ans=0;
    rep(i,1,m) rep(j,1,i) (ans+=f[i][j]*(c[i]-1)%mod*ginv(n-j)%mod)%=mod;
    write(ans,'\n');

    return ot(),0;
}
```

---

## 作者：wucstdio (赞：1)

首先考虑什么情况下会赢。我们发现当且仅当选出来的数单调上升，且最后两个数字相等。

首先把这个数组排序，然后考虑DP。设$f[i][j]$表示选择了$i$个数，其中第$i$个数是$j$，整个游戏未结束的概率。

为了方便，我们约定当一个数字出现了多次的时候，一定要从左到右选择。这样如果$a[j]==a[j-1]$，那么就说明选到这个数的时候游戏已经赢了，因此可以在DP到这个数的时候统计答案。

需要注意的是，统计答案之后DP数组就不能再填了，因为状态表示的是整个游戏未结束的概率。

状态转移方程就比较简单了：

$$\begin{cases}f[i][j]=\dfrac{cnt[a[j]]}{n-i+1}\sum_{k<j}f[i-1][k]&\text{if $a[j]\neq a[j-1]$}\\Ans+=\dfrac{cnt[a[j]]-1}{n-i+1}f[i-1][j-1]&\text{else}\end{cases}$$

直接DP是$O(n^3)$的，前缀和优化后时间复杂度为$O(n^2)$

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;
const ll MOD=998244353;
ll quick_pow(ll x,ll a)
{
	ll ans=1;
	while(a)
	{
		if(a&1)ans=ans*x%MOD;
		x=x*x%MOD;
		a>>=1;
	}
	return ans;
}
int n,a[5005],num[5005];
ll f[5005][5005],s[5005][5005],inv[5005],ans;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		num[a[i]]++;
		inv[i]=quick_pow(i,MOD-2);
	}
	sort(a+1,a+n+1);
	f[0][0]=1;
	for(int i=0;i<=n;i++)s[0][i]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(a[j]==a[j-1])
			{
				ans+=f[i-1][j-1]*inv[n-i+1]%MOD*(num[a[j]]-1)%MOD;
				continue;
			}
			f[i][j]=s[i-1][j-1]*inv[n-i+1]%MOD*num[a[j]]%MOD;
		}
		for(int j=1;j<=n;j++)
		{
			s[i][j]=s[i][j-1]+f[i][j];
			if(s[i][j]>=MOD)s[i][j]-=MOD;
		}
	}
	printf("%I64d\n",ans%MOD);
	return 0;
}
```

---

## 作者：Yuno (赞：1)

# [CF1156F Card Bag](https://www.luogu.com.cn/problem/CF1156F)

### 题意：

你有一个装有 $n$ 张卡牌的卡包，卡包中第 $i$ 张卡牌上写有数字 $a_i$。在接下来的每一个回合，你会从卡包中等概率随机抽出一张卡牌，每一回合抽出的卡牌不会重新放回卡包中。

从第二回合开始，每一回合，你需要对这一回合抽出的卡牌的点数 $x$ 和上一次抽出的卡牌的点数 $y$ 进行比较：

- 如果 $x < y$，游戏失败并结束；
- 如果 $x = y$，游戏胜利并结束；
- 如果 $x > y$，游戏继续。

### 题解：

一个合法的胜利序列必然是由一个严格递增的序列加上一个与最后一个数相同的数。

考虑枚举胜利的回合数，最终把每回合胜利的概率相加即可。

假设在第 $k$ 回合胜利，合法的胜利序列有 $X$ 个，那么概率即为 **$\frac X {A_n^k}$**

相当于合法数除以总数。

所以只要求出 $X$ ，这道题就做完了。

$f_{i,j}$ 表示以 $a_i$ （注意是 $a_i$ 不是 $i$ ，因为每个数是两两不同的)这个数为结尾，长度为 $j$ 的严格递增序列个数。

则

$f_{i,1}=1$

$f_{i,j}=\sum\limits_{a_k<a_i}f_{k,j-1}$

直接转移是 $O(n^3)$ 的，可以用前缀和优化到 $O(n^2)$

然后做完了。

注意处理排列数时逆元预处理，不然会 $T$ 。

$Code:$

```cpp
#include <bits/stdc++.h>
using std::cin;
using std::cout;
#define int long long
const int mo = 998244353, N = 5007;
int n, a[N], f[N][N], s[N], cnt[N], A[N];

int qp(int base, int p) {
	int res = 1;
	while (p) {
		if (p & 1) (res *= base) %= mo;
		(base *= base) %= mo;
		p >>= 1;
	}
	return res;
}

signed main() {
	std::ios::sync_with_stdio(0);
	cin >> n;
	int max = 0;
	for (int i = 1; i <= n; ++ i) {
		cin >> a[i];
		++ cnt[a[i]];
		max = std::max(max, a[i]);
	}
	for (int i = 1; i <= n; ++ i) f[i][1] = 1;
	for (int j = 1; j < n; ++ j) {
		memset(s, 0, sizeof(s));
		for (int i = 1; i <= n; ++ i) {
			s[a[i]] += f[i][j];
			s[a[i]] %= mo;
		}
		for (int i = 1; i <= max; ++ i) {
			s[i] += s[i - 1];
			s[i] %= mo;
		}
		for (int i = 1; i <= n; ++ i) {
			f[i][j + 1] = s[a[i] - 1];
			f[i][j + 1] %= mo;
		}
	}
	A[n + 1] = 1;
	for (int i = n; i >= 1; -- i) A[i] = A[i + 1] * i % mo;
	for (int i = 1; i <= n; ++ i) A[i] = qp(A[i], mo - 2);
	int ans = 0;
	for (int i = 2; i <= n; ++ i) {//which round
		for (int j = 1; j <= n; ++ j) {//ends up with which number
			int fz = f[j][i - 1] * (cnt[a[j]] - 1) % mo, fm = A[n - i + 1];
			(ans += fz * fm % mo) %= mo;
		}
	}
	cout << ans << '\n';
	return 0;
}
```



---

## 作者：_Weslie_ (赞：0)

复健概率第一题！（好像也只会这一题了。）

## Solution CF1156F

### Idea

显然是 dp。

不妨设 $g_{i,j}$ 为 $[1,i]$ 中选了 $j$ 个胜利情况的数量。

那么显然有 $g_{i,j}$ 表示的每一个状态都是：前面单调递增，然后最后两个数相等。

那么 $g_{i,j}$ 就要从 $[1,i-1]$ 中，选了 $j-2$ 个数，并且单调递增的方案数转移而来。

那么我们设 $f_{i,j}$ 为 $[1,i]$ 中选了 $j$ 个，单调递增的方案数。

下面设 $cnt_i$ 为原序列中 $i$ 的个数。

那么有：

$$f_{i,j}=(\sum_{k=1}^{i-1}f_{k,j-1})cnt_i$$

$$g_{i,j}=(\sum_{k=1}^{i-1} f_{k,j-2})(cnt_j-1)cnt_j$$

我们不妨通过序列来考虑这个转移。如果我们一共执行 $n$ 次取球，我们有 $n!$ 种方案。在这 $n!$ 种方案中，前后均相同，中间两个位置填 $(a,b)$ 和 $(b,a)$ 是不一样的。所以这就是 $g$ 的转移式没有除以 $2$ 的原因。

那么我们注意到 $f$ 和 $g$ 的转移式中都要 $\sum f$，所以我们对 $f$ 求个前缀和 $sum$（注意这个 $sum$ 是选了 $j$ 个数的 $sum$）。

然后答案统计：显然和 $g_{i,j}$ 有关。根据操作序列理论，前 $j$ 个数的方案确定之后，后面 $n-j$ 个数可以随便填，有 $(n-j)!$ 种方案。

别忘了我们求的是方案数，最后需要除以总的排列数 $n!$。

### Code

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=5005,mod=998244353;
ll f[N][N],g[N][N],sum[N];
ll fac[N],cnt[N];
ll qpow(ll a,ll b){
	ll res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
int n,a[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		cnt[a[i]]++;
	}
	fac[0]=1;
	for(int i=1;i<N;i++){
		fac[i]=fac[i-1]*i%mod;
	}
	sum[0]=1;
	for(int i=1;i<=n;i++){
		for(int j=n;j>=1;j--){
			f[i][j]=sum[j-1]*cnt[i]%mod;
			if(j>=2)g[i][j]=sum[j-2]*(cnt[i])%mod*(cnt[i]-1)%mod;
			sum[j]=(sum[j]+f[i][j])%mod;
		}
	}
    ll ans=0;
    
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            ans=(ans+g[i][j]*fac[n-j]%mod)%mod;
        }
    }
	cout<<ans*qpow(fac[n],mod-2)%mod;
	return 0;
}
```

---

## 作者：Jerrywang09 (赞：0)

不是很困难的概率 DP 题。

考虑摸牌的过程是什么样的。其一定形如先摸了若干张权值下降的牌，最后摸了两张权值相同的牌。

不难设出 DP 状态和转移：$f(i,j)$ 表示当前最后一张摸到的牌权值为 $i$，目前一共摸出 $j$ 张牌的概率。转移显然：
$$
f(i,j)=\sum_{k=1}^{i-1} f(k,j-1)\cdot \frac {cnt[i]} {n-j+1}
$$
其中，$cnt[i]$ 表示权值为 $i$ 的牌的数量。

考虑前缀和优化并预处理逆元，维护 $sum(j)=\sum_{k=1}^{i-1}\frac {f(k,j)} {n-j}$，即可保证复杂度。需要枚举最后一步是哪张牌并统计答案。

```cpp
// Title:  Card Bag
// Source: CF1156F
// Author: Jerrywang
#include <cstdio>
#include <iostream>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=5005, mod=998244353;
using namespace std;
char buf[1<<23], *p1=buf, *p2=buf;
#define gc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read()
{
    int x=0, f=1; char c=gc();
    while(c<'0' || c>'9') c=='-' && (f=-1), c=gc();
    while('0'<=c && c<='9') x=(x<<3)+(x<<1)+c-'0', c=gc();
    return x*f;
}
 
int n, cnt[N], a[N]; ll f[N][N], sum[N], inv[N];
inline void upd(ll &x, ll y)
{
    x+=y; if(x>=mod) x-=mod;
}
ll qp(ll x, ll y=mod-2)
{
    ll res=1;
    for(; y; y>>=1, x=x*x%mod) if(y&1) res=res*x%mod;
    return res;
}
 
int main()
{
#ifdef Jerrywang
    freopen("E:/OI/in.txt", "r", stdin); ios::sync_with_stdio(0);
#endif
    n=read();
    rep(i, 1, n) a[i]=read(), cnt[a[i]]++;
    rep(i, 0, n) inv[i]=qp(i);
    rep(i, 1, n)
    {
        f[i][1]=cnt[i]*inv[n]%mod;
        rep(j, 2, n)
        {
            upd(f[i][j], sum[j-1]*cnt[i]%mod);
            // rep(k, 1, i-1)
            // {
            //     f[i][j]=(f[i][j]+f[k][j-1]*cnt[i]%mod*qp(n-j+1)%mod)%mod;
            // }
        }
        rep(j, 1, n)
        {
            upd(sum[j], f[i][j]*inv[n-j]%mod);
        }
    }
    ll res=0;
    rep(i, 1, n) rep(j, 1, n)
    {
        upd(res, f[i][j]*(cnt[i]-1)%mod*inv[n-j]%mod);
    }
    printf("%lld", res);
 
    return 0;
}

```

---

## 作者：xiezheyuan (赞：0)

## 简要题意

有 $n$ 个小球，第 $i$ 个小球上写的数字为 $a_i$。

你需要重复以下操作：

- 如果现在没有小球了，游戏失败，结束操作。
- 从现在的小球中随机选取一个（不放回）。
- 如果你现在手上的小球数 $\geq 2$，则令上一次选取的小球上写的数字为 $x$，此次选取的小球上写的数字为 $y$。若 $x<y$，回到第一步；如果 $x=y$，游戏胜利，结束操作；如果 $x>y$，游戏失败，结束操作。

求游戏胜利的概率。答案对 $998,244,353$ 取模。

$2\leq n\leq 5000$。

## 思路

简单题。

首先考虑一个朴素的 dp，设 $f(i,j)$ 已经拿了 $i$ 个球，最后一次拿的球为第 $j$ 个球的概率，不难列出下面的转移方程：

$$
f(i,j)=\sum_{a_k<a_j} \frac{1}{n-(i-1)}f(i-1,k)
$$

也就是枚举倒数第二个选择的球是 $k$。

我们还需要统计答案，对于每一个 $f(i,j)$，维护答案 $\mathrm{ans}$，则有：

$$
\mathrm{ans}\leftarrow \mathrm{ans}+\sum_{a_k=a_j,k\neq j} \frac{1}{n-(i-1)}f(i-1,k)
$$

直接转移，时间复杂度 $O(n^3)$ 难以承受。

我们不妨将 $a$ 排序，那么可以发现计算 $f(i,j)$ 的时候，本质上在求前缀和，在计算 $\mathrm{ans}$ 的时候，本质上在计算区间和。所以我们可以用前缀和优化转移。

时间复杂度 $O(n^2)$ 可以通过本题。

注意如果你 TLE on #7，那么说明你的时间复杂度是 $O(n^2\log n)$ 的，无法通过本题，需要将每次转移的快速幂求逆元改为预处理逆元。

## 代码

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;

constexpr int mod = 998244353;
int Add(int x, int y){ return (x + y) >= mod ? (x + y - mod) : (x + y); }
int Sub(int x, int y){ return (x - y) < 0 ? (x - y + mod) : (x - y); }
int Mul(int x, int y){ return 1ll * x * y % mod; }

const int N = 5005;
int f[N][N], g[N][N], n, a[N], lst[N], L[N], R[N], inv[N], ans;

int fastpow(int x, int y){
    int ret = 1;
    for(;y;y>>=1,x=Mul(x, x)){ if(y & 1) ret = Mul(ret, x); }
    return ret;
}

map<int,int> mp;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    sort(a + 1, a + n + 1);
    inv[1] = 1;
    for(int i=2;i<=n;i++) inv[i] = Mul(mod - mod / i, inv[mod % i]);
    for(int i=1;i<=n;i++) f[1][i] = inv[n], g[1][i] = Add(g[1][i - 1], f[1][i]);
    fill(L + 1, L + n + 1, n + 1);
    for(int i=1;i<=n;i++){
        if(!mp.count(a[i])) lst[i] = i - 1, mp[a[i]] = i - 1;
        else lst[i] = mp[a[i]];
        L[a[i]] = min(i, L[a[i]]);
        R[a[i]] = max(i, R[a[i]]);
    }
    for(int i=2;i<=n;i++){
        for(int j=1;j<=n;j++){
            ans = Add(ans, Mul(Sub(Sub(g[i - 1][R[a[j]]], g[i - 1][L[a[j]] - 1]), f[i - 1][j]), inv[n - (i - 1)]));
            f[i][j] = Mul(g[i - 1][lst[j]], inv[n - (i - 1)]);
            g[i][j] = Add(g[i][j - 1], f[i][j]);
        }
    }
    cout << ans << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：aoeiuv (赞：0)

怎么才可以获胜？一定是一个单调递增的子序列再添上一个相同的数，所以首先要对数组进行排序。

$\mathcal{O}(n^3)$ 的 DP 是很容易的，记 $f_{i,k}$ 表示以 $i$ 结尾的序列，选了 $k$ 次，游戏仍在继续的概率。转移就是枚举 $i$ 前面每个 $j$，如果 $a_i \neq a_j$，那么就把对应的贡献加上去：$f_{i,k}\leftarrow f_{j,k-1}\times\dfrac{1}{n-k+1}$。最终的答案在转移的过程中一并计算，就是说，如果转移过程中有 $a_i = a_j$，那么 $ans\leftarrow f_{j,k-1}\times\dfrac{1}{n-k+1}$。

优化到 $n^2$ 是容易的！注意到枚举 $j$ 这一维其实很多余，因为 $j$ 只分为了 $a_j = a_i$ 和 $a_j \neq a_i$ 两种情况，对于这两种情况分别开一个前缀和数组统计一下即可。

唯一可能有点疑惑的地方就是我的答案最终需要 $\times 2$，因为在选 $a_i=a_j$ 的时候多算了一个概率……

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 5e3 + 5, P = 998244353;

int n,a[N],f[N][N],ans,g[N],h[N][N];

int inv[N];

signed main(){
    cin >> n;
    for (int i = 1;i <= n;i++) inv[i] = (i == 1 ? 1 : 1ll * (P - P / i) * inv[P % i] % P);
    for (int i = 1;i <= n;i++)
        cin >> a[i];
    sort(a + 1,a + n + 1);
    f[0][0] = 1; g[0] = 1;
    for (int i = 1;i <= n;i++){
        for (int k = 1;k <= i;k++){
            (ans += 1ll * h[a[i]][k - 1] * inv[n - k + 1] % P) %= P;
            (f[i][k] += 1ll * (g[k - 1] - h[a[i]][k - 1] + P) * inv[n - k + 1] % P) %= P;
        }
        for (int k = 1;k <= i;k++)
            (g[k] += f[i][k]) %= P, (h[a[i]][k] += f[i][k]) %= P;
    }
    cout << 1ll * ans * 2 % P;
    return 0;
}
```

能预处理一定要预处理逆元，否则会 T。

---

## 作者：happy_zero (赞：0)

由小往大取，无后效性，因此可以 dp。

记 $cnt_i$ 为点数为 $i$ 的卡牌个数。$f_{i,j}$ 表示取了 $i$ 次还未胜利，其中第 $i$ 次取了 $j$。

转移枚举上一次取了什么：

$$f_{i,j}=\sum_{k=1}^{j-1}f_{i-1,k}\times \frac{cnt_j}{n-i+1}$$

复杂度 $O(n^3)$，但发现可以把 $\frac{cnt_j}{n-i+1}$ 提出来，$k$ 一维前缀和优化掉。

答案统计就是枚举 $i,j$，然后乘上再取一张 $j$ 的概率：

$$ans=\sum_{i=1}^n\sum_{j=1}^n f_{i,j}\times\frac{cnt_j-1}{n-i}$$

复杂度 $O(n^2)$。注意预处理逆元否则可能会被卡常。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5005;
const int P = 998244353;
int f[N][N], cnt[N], s[N], g[N][N], inv[N];
int qpow(int a, int b = P - 2) {
	int res = 1;
	while (b) {
		if (b & 1) res = res * a % P;
		a = a * a % P;
		b >>= 1;
	}
	return res;
}
signed main() {
	int n; cin >> n; inv[0] = 1;
	for (int i = 1, x; i <= n; i++)
		cin >> x, cnt[x]++, inv[i] = qpow(i);
	for (int i = 1; i <= n; i++) 
		g[1][i] = (g[1][i - 1] + cnt[i] * inv[n] % P) % P, s[i] = s[i - 1] + cnt[i];
	int ans = 0;
	for (int i = 1; i <= n; i++) 
		ans = (ans + cnt[i] * inv[n] % P * (cnt[i] - 1) % P * inv[n - 1] % P) % P;
	for (int i = 2; i <= n; i++) 
		for (int j = 1; j <= n; j++) {
			f[i][j] = (f[i][j] + g[i - 1][j - 1] * cnt[j] % P * inv[n - i + 1] % P) % P;
			ans = (ans + f[i][j] * (cnt[j] - 1) % P * inv[n - i] % P) % P;
			g[i][j] = (g[i][j - 1] + f[i][j]) % P;
		}
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：happybob (赞：0)

先离散化，记不同个数为 $m$，每种数出现次数为 $c_i$。

考虑 DP，记 $f_{i,j}$ 表示当前到了第 $i$ 种数，选了 $j$ 次，且选了第 $i$ 种数，目前游戏仍然在继续的概率。

考虑转移，枚举上一次选的数 $k<i$，$f_{i,j} \leftarrow f_{k,j-1} \times \dfrac{c_i}{n-j+1}$。

注意后面的数是定值直接对于每个 $j$ 维护当前的和即可。预处理 $n-j+1$ 的逆元即可做到 $O(n^2)$。

计算答案时对于所有 $i,j$，$ans \leftarrow f_{i,j} \times \dfrac{c_i-1}{n-j}$。

---

## 作者：int08 (赞：0)

## 前言
duel 时候发现的，花了半个小时才切 ~~，对于我做 DP 来说这算很快的~~，不过有人写挂了所以还是没输。

朴素线性 DP 好题。
## Solution
先~~个人习惯性地~~改求方案数，其实在本题没有必要。

首先，深情注视数据范围，得出正解复杂度显然是 $O(n^2)$，一点 $\log$ 都不能带。

那么，$O(n^2)$ 的朴素 DP 一般有两种情况：$O(n)$ 状态和 $O(n)$ 转移，以及 $O(n^2)$ 状态和可优化的 $O(n)$ 转移。

但是本题中，容易发现，方案数跟剩余数字数量和当前位置数都相关，所以前者并不好做。

然后我们发现，能够不失败或者获胜的选中序列顺序显然是单调递增的，所以决定接下来选了某个数会不会失败的只是最后一位，前面的并不重要。

那么，设 $f_{i,j}$ 表示当前已经选中了 $i$ 个数，目前选中的最后一位是 $j$ 且游戏还没失败或者成功的方案数，$t_j$ 表示数字 $j$ 出现次数，则转移是简单的：

$$f_{i,j}=\sum_{x=1}^{j-1}f_{i-1,x}\times t_j$$

解释一下，意思是说，上一位可以从任何一个小于 $j$ 的数，转移过来，而且我可以在 $t_j$ 个 $j$ 中任选一个填入，注意填入这个位置之前显然不可能使用过 $j$，否则序列不满足单调递增游戏就结束了。

然后我们发现这个前缀和的调用是静态的，预处理出结果即可，不用每次重算。

计算答案就是如果对于 $f_{i,j}$，下一位又选 $j$，就赢了，后面咋填都无所谓了，应该等于:

$$f_{i,j}\times (t_j-1)\times (n-1-i)!$$

复杂度变成了 $O(n^2)$，可以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mod 998244353
int n,a,i,j,tong[5080],dp[5080][5080],jc[5000],sm[5080][5080],ans=0;
int qp(int x,int y)
{
	int ans=1;
	for(int i=1,j=x;i<=y;i*=2,j=j*j%mod) if(i&y) ans=ans*j%mod;
	return ans;
}
signed main()
{
	cin>>n;jc[0]=1;
	for(i=1;i<=n;i++) cin>>a,tong[a]++,jc[i]=jc[i-1]*i%mod;
	for(i=1;i<=n;i++) dp[1][i]=tong[i],sm[1][i]=sm[1][i-1]+dp[1][i],ans=(ans+dp[1][i]*(tong[i]-1)%mod*jc[n-2])%mod;
	for(i=2;i<n;i++)
		for(j=1;j<=n;j++) dp[i][j]=sm[i-1][j-1]*tong[j]%mod,sm[i][j]=sm[i][j-1]+dp[i][j],ans=(ans+dp[i][j]*(tong[j]-1)%mod*jc[n-1-i])%mod;
	for(i=1;i<=n;i++) ans=ans*qp(i,mod-2)%mod;
	cout<<ans;
	return 0;
}
```
# The End.

---

## 作者：WRuperD (赞：0)

生日前最后一场比赛阿克了，心情好写篇题解。

### 正文

注意到题目给的限制是什么 $x < y$ 游戏失败。这件事情很好啊，意味着只有 $x \geq y$ 的卡片可以对赢得概率做贡献。还有一个很美好的性质，就是你接下来能取得卡片不用计入状态里面增加额外状态数，原因是假设当前你选了 $x$ 那么你之前选的数都不可能 $> x$ 吧。（好像在说废话）。

大眼瞪完上面的性质之后，考虑设 $f_{i,j}$ 表示你在 $i$ 次抽卡中选到数字 $j$ 后你赢的概率。这里还要对这个状态做一个限制，就是你是第1次选到这个数字。设 $num_i$ 为数字 $i$ 在 $a$ 中出现的次数。所以显然的有 $f_{i,j} = {{num_j-1}\over {n-i}} + \sum \limits_{k=j+1} \limits^{n} f_{i+1,k} \cdot {sum_k \over n -i}$ 这个式子。然后后缀和优化一下即可。

预处理一下逆元，总时间复杂度 $O(n^2)$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long inf = 1e18;
const int mininf = 1e9 + 7;
#define int long long
#define pb emplace_back
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if(x<0){x=~(x-1);putchar('-');}if(x>9)write(x/10);putchar(x%10+'0');}
#define put() putchar(' ')
#define endl puts("")
const int mod = 998244353;
const int MAX = 5e3 + 10;

int a[MAX];
int f[MAX][MAX];
int rt[MAX], sum[MAX];
int inv[MAX];

void solve(){
	int n = read();
	for(int i = 1; i <= n; i++){
		a[i] = read();
		sum[a[i]]++;
	}
	inv[1] = 1;
	for(int i = 2; i <= n; i++){
		inv[i] = inv[mod % i] * (mod - mod / i) % mod;
	}
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++){
		rt[a[i]] = i;
	}
	for(int i = n - 1; i >= 1; i--){
		int pre = 0;
		for(int j = n; j >= i; j--){
			if(!sum[j])	continue;
			int tmp2 = inv[n - i];
			f[i][j] = (sum[j] - 1) * tmp2 % mod;
			f[i][j] += pre;
			f[i][j] %= mod;
			pre += f[i + 1][j] * sum[j] % mod * tmp2 % mod;
			pre %= mod;
		}
	}
	int ans = 0;
	int tmp = inv[n];
	for(int i = 1; i <= n; i++){
		ans += f[1][i] * sum[i] % mod * tmp % mod;
		ans %= mod;
	}
	write(ans), endl;
}

signed main(){
	int t = 1;
	while(t--)	solve();
	return 0;
}
```


---

