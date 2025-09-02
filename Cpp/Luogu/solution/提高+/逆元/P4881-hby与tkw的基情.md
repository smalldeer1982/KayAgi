# hby与tkw的基情

## 题目背景

> 基情恒久远，一对永流传。

hby 和 tkw 是一对好基友，他们经常在一起做♂游♂戏 (/滑稽)。


## 题目描述

他们喜欢玩字符串游戏，尤其喜欢玩回文串。每次 hby 会给出一个数 $n$，那么 tkw 就需要给出 $Ans=\sum\limits_{i=1}^ni\times s[i]\times[i\bmod 2]$。其中 $s[i]$ 代表长度为 $i$ 的回文串的个数（只考虑小写字母），最后面是 bool 表达式

不过由于 tkw 最近学 ycz 找妹纸去了，于是他就将这个问题交给了你，如果你不能在 $1\rm s$ 内答出来，那么 hby 和 tkw 的基情将会破裂！~~（不过那样 tkw 就可以安心地找妹纸了）~~

由于答案会非常大，所以你只需要输出答案 $\bmod 10^9+7$ 的值即可

## 说明/提示

对于 $10\%$的数据，$n\le 5$。

对于另外 $20\%$ 的数据，$\sum n\le 10^7$。

对于另外 $20\%$ 的数据，$T=1$。

对于 $100\%$ 的数据，$1\le T\le 5\times 10^5$，$1\le n\le 10^9$。

## 样例 #1

### 输入

```
2
1
3```

### 输出

```
26
2054```

# 题解

## 作者：Wolfycz (赞：7)

首先要得出s[i]的递推式，s[i]=s[i-2]*26,s[1]=s[2]=26，然后T=1可以用矩乘快速幂，~~（O2可能可以AC所有数据）~~

我们发现这个式子实际上要求
$$Ans=\sum\limits_{i=1}^m(2i-1)\times 26^i$$
这个显然是差比数列，可以裂项相减
$$26Ans=\sum\limits_{i=1}^m(2i-1)\times 26^{i+1}$$
减去之前的式子有
$$25Ans=-26+(2n-1)\times 26^{n+1}-2\sum\limits_{i=2}^m 26^i$$
把-26挪到最后好看一些，然后把后面用等比数列求和来表示
$$25Ans=26+(2n-1)\times 26^{n+1}-2\times\dfrac{26^{n+1}-26}{25}$$
然后就可以直接算了

ps:我的代码做了一点优化，例如提取$26^{n+1}$这些同类项，减少了%和快速幂，但是按原式直接写也可以，大家可以自己推一下
``` cpp
/*program from Wolfycz*/
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define inf 0x7f7f7f7f
using namespace std;
typedef long long ll;
typedef unsigned int ui;
typedef unsigned long long ull;
inline int read(){
    int x=0,f=1;char ch=getchar();
    for (;ch<'0'||ch>'9';ch=getchar())	if (ch=='-')    f=-1;
    for (;ch>='0'&&ch<='9';ch=getchar())	x=(x<<1)+(x<<3)+ch-'0';
    return x*f;
}
inline void print(int x){
    if (x>=10)	print(x/10);
    putchar(x%10+'0');
}
const int p=1e9+7,inv=2.8e8+2,inv2=5.6e8+5;
int mlt(int a,int b){
    int res=1;
    for (;b;b>>=1,a=1ll*a*a%p)	if (b&1)	res=1ll*res*a%p;
    return res;
}
int main(){
    for (int T=read();T;T--){
        int n=(read()+1)>>1;
        int Ans=1ll*(1ll*mlt(26,n+1)*((n<<1)-inv2+p)%p+26ll*inv2%p)%p*inv%p;
        printf("%d\n",Ans);
    }
    return 0;
}
```

---

## 作者：Alarm5854 (赞：6)

这道题目是一道推式子的题目，如果把式子推出来了，那么一切都好解决了。

首先看一开始的式子，发现其实只要求奇数长度回文串的个数。接下来设 $n$ 为奇数，$m=(n+1)/2$，则 $s_n=26^m$，记答案为 $S$，则答案可表示为：

$$S=\sum_{i=1}^{m}(2i-1)\times 26^i=26+3\times 26^2+5\times 26^3+\dots+n\times 26^m$$

若直接解决，时间复杂度为 $O(Tn)$，若预处理则可做到 $O(T+n)$，但无法通过本题。

看一眼式子，发现有规律，将答案乘以 $26$，则：

$$26S=\sum_{i=1}^m(2i-1)\times 26^{i+1}=1\times 26^2+3\times 26^3+\dots+(n-2)\times 26^m+n\times 26^{m+1}$$

这两个式子相减，得：

$$25S=n\times 26^{m+1}-(1352\times\sum_{i=0}^{m-2}26^i+26)$$

利用等比数列求和公式：

$$25S=n\times 26^{m+1}-(1352\times\dfrac{26^{m-1}-1}{25}+26)$$

这个式子就可以解了，算出 $25$ 的逆元，用快速幂解决时间复杂度为 $O(T\log n)$，可以通过本题，注意多取模。

-------



然而，如果 $T=10^7$ 呢？这个时候快速幂就无法通过了。那么，有没有时间复杂度比 $O(T\log n)$ 更优的做法呢？答案是肯定的。

想一想快速幂的本质，其实就是按照进制拆分，它是处理出所有 $x^{2^i}$ 的结果，然后将指数二进制拆分的。其实不一定要为二进制，可以为其它进制，假设为 $b$ 进制，那么就需要处理出所有 $x^{i\times b^j}$ 的结果，其中 $0\le i<b,b^j\le n$。将其记录至数组 $f$，$f_{i,j}=x^{i\times b^j}$。对于这道题目而言，令 $b=2^{15},x=26$，则只需要两个一维数组。预处理后，每次计算只需要进行一次乘法即可，总时间复杂度为 $O(T)$，抢到了最优解。

$O(T)$ 代码如下：

```cpp
#include<ctime>
#include<cstdio>
#include<cctype>
#define ll long long
using namespace std;
const ll HgS=1e9+7;//机房里有个巨佬叫做HgS，故把他当模数
const ll inv=2.8e8+2;//25的逆元
const ll N=1<<15;
ll read() {
	char c;
	ll x=0,f=1;
	while(!isdigit(c=getchar()))
		f-=2*(c=='-');
	while (isdigit(c)){
		x=x*10+(c-48)*f;
		c=getchar();
	}
	return x;
}
ll T,a[N|1],b[N|1];
ll calc(ll x){
	return a[x&(N-1)]*b[x>>15]%HgS;//其实本质就是把x转化为32768进制
}
void solve(){
	ll n=read();
	if(!(n&1))//数据中n不一定为奇数，所以要判偶数
		--n;
	ll m=(n+1)>>1;
	ll x=calc(m+1)*n%HgS;
	ll y=(1352*(calc(m-1)-1)%HgS*inv+26)%HgS;//注意这里要取两次，防止中间过程溢出
	printf("%lld\n",(x-y+HgS)%HgS*inv%HgS);//取模后x可能小于y
}
int main() {
	#ifndef ONLINE_JUDGE
	freopen("P4881.in","r",stdin);
	freopen("P4881.out","w",stdout);
	#endif
	clock_t t1=clock();
	//--------
	a[0]=1;//a[i]代表26^(i*32768^0)
	b[0]=1;//b[i]代表26^(i*32768^1)
	for(ll i=1;i<=N;++i)
		a[i]=a[i-1]*26%HgS;
	for(ll i=1;i<=N;++i)
		b[i]=b[i-1]*a[N]%HgS;//a[N]就是26^32768
	T=read();
	while(T--)
		solve();
	//--------
	clock_t t2=clock();
	fprintf(stderr,"time:%0.3lfs",1.0*(t2-t1)/CLOCKS_PER_SEC);
	return 0;
}
```



---

## 作者：jianhe (赞：4)

**upd**：修改了一个错别字（另 $\rightarrow$ 令）。

### 前言：
挺简单的一道推式子题。
### 思路：
首先令 $m \leftarrow \lfloor\frac{n-1}{2}\rfloor$，$S \leftarrow \sum\limits_{i=0}^{m} s_{2i+1} \times (2i+1)$。

其中，$s_{2i+1}$ 代表长度为 $2i+1$ 的回文串的个数，也就是中间的可以随便填，左半部分也可以随便填，右半部分只要和左半对称填就可以了，方案数为 $26^{i+1}$。

也就是 $S=\sum\limits_{i=0}^{m} (2i+1) \times 26^{i+1}$。

左右同乘 $26$，得 $26S=\sum\limits_{i=0}^{m} (2i+1) \times 26^{i+2}$。

错位相减，得 $25S=26^{m+2} \times (2m+1)-26-2 \times \sum\limits_{i=0}^{m} 26^{i+1}$。

再另 $S_2 \leftarrow \sum\limits_{i=0}^{m} 26^{i+1}$。

左右同乘 $26$，得 $26S_2=\sum\limits_{i=0}^{m} 26^{i+2}$.

错位相减，得 $25S_2=26^{m+2}-26^2$。

带入得 $S=\frac{26^{m+2} \times (2m+1)-26-2\times\frac{26^{m+2}-26^2}{25}}{25}$。

取模勤快一点即可。
### 代码：
```cpp
/*
 * @Author: jianhe
 * @Date: 2025-03-05 14:38:03
 * @LastEditTime: 2025-03-05 14:53:54
 */
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod=1e9+7;
ll T,n,ans;
ll qp(ll a,ll b,ll ct=1){while(b){if(b&1) ct=ct*a%mod;a=a*a%mod,b>>=1;}return ct;}
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;ans=qp(26,(n-1)/2+2)*((n-1)/2*2+1)%mod-26-2*(qp(26,(n-1)/2+2)-26*26)*qp(25,mod-2)%mod;ans*=qp(25,mod-2);
        cout<<(ans%mod+mod)%mod<<"\n";
    }
    return 0;
}
```

---

## 作者：Captain_Paul (赞：3)

看到这题第一反应就是找规律（毕竟被小凯练出来了）

首先从$s[i]$入手，它表示长度为$i$的只包含小写字母的回文串个数

手算或者打表可以发现它是一个这样的数列

$26,26,26^2,26^2,26^3,26^3...$

这样就搞定了$s[i]$

再观察一下题目的式子，发现后面有个$i\%2$

那偶数项不就没有了？2333

这样就只需要求奇数项的和了

打个表看一下，只看奇数项的序列是这样的：

$1*26,3*26^2,5*26^3......(2n-1)*26^n$

那么每次询问要做的就是求出它的前$n$项之和

因为$n$非常大，所以不能直接求，先化简一下看一看

($26$看起来非常麻烦，把它写成$x$)

记$S=x+3x^2+5x^3+......+(2n-1)x^n$

则$xS=x^2+3x^3+5x^4+......+(2n-1)x^{n+1}$

用错位相减法，得$(1-x)S=x+2(x^2+x^3+x^4+......+x^n)-(2n-1)x^{n+1}$

中间括号内用等比数列求和公式，得

$(1-x)S=x+2x^2(1-x^{n-1})/(1-x)-(2n-1)x^{n+1}$

为了方便，两边同时取相反数，移项得

$S=[(2n-1)x^{n+1}-x-2x^2(x^{n-1}-1)/(x-1)]/(x-1)$

因为有模数，所以除法要用$25$在模$1e9+7$意义下的逆元

```
#include<cstdio>
using namespace std;
typedef long long ll;
const int mod=1e9+7,inv25=280000002;
int T,n;
ll quickpow(ll n,ll k)
{
	ll s=1;
	while (k)
	{
		if (k&1) s=s*n%mod;
		n=n*n%mod; k>>=1;
	}
	return s;
}
int main()
{
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d",&n);
		if (!(n&1)) --n; n=(n+1)>>1;
		ll x1=(2*n-1)*quickpow(26,n+1)%mod,x2=mod-26;
		ll x3=1352*(quickpow(26,n-1)-1+mod)%mod*inv25%mod;
		ll ans=(x1+x2-x3+mod)%mod*inv25%mod;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：114514xxx (赞：2)

## 题意
求 $\displaystyle\sum\limits_{i=1}^ni\times s_i\times[i\bmod 2]$。其中 $s_i$ 代表长度为 $i$ 的回文串的个数（只考虑小写字母）。答案对 $10^9+7$ 取模。
## 思路
考虑 $O(T \log n)$ 的做法。我们可以将求和式转变为递推式进而使用矩阵快速幂进行求解。

设 $\displaystyle f_i=\sum\limits_{i=1}^ni\times s_i\times[i\bmod 2]$。根据回文串的定义，容易得到 $s_{i+2}=s_i\times 26$。因此我们可以得到 $f_i$ 的递推式：

$$\begin{aligned}
      f_{i+2}=f_i+(i+2)\cdot 26^{\lfloor \frac{k}{2}\rfloor +1}\\
            
      f_{i+4}=f_{i+2}+(i+4)\cdot 26^{\lfloor \frac{k}{2}\rfloor +2}\\
  \end{aligned}
$$

这显然是可以用矩阵快速幂进行求解的。我们可以构建如下加速矩阵 $A$ 用来求解：
$$ 
A = \begin{bmatrix} 1 & 0 & 0 \\ 26 & 26  & 0 \\ 26 & 26 & 26\end{bmatrix} 
$$

若要求 $f_n$，只需求出 $A^{\lfloor \frac{n-1}{2} \rfloor}$ 即可。

至此，这道就被我们解决了。
## 代码


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int ans[10][10],a[10][10];
const int MOD=1e9+7;
inline int read(){
    register int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f-=2;
        c=getchar_unlocked();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar_unlocked();
    }
    return x*f;
}
void matrix_pow1(){
    int c[10][10]={0};
    for(int k=1;k<=3;++k)
        for(int i=1;i<=3;++i)
            for(int j=1;j<=3;++j)
                c[i][j]=(c[i][j]+ans[i][k]*a[k][j])%MOD;
    for(int i=1;i<=3;++i)
        for(int j=1;j<=3;++j)
            ans[i][j]=c[i][j];
}
void matrix_pow2(){
    int c[10][10]={0};
    for(int k=1;k<=3;k++)
        for(int i=1;i<=3;i++)
            for(int j=1;j<=3;j++)
                c[i][j]=(c[i][j]+a[i][k]*a[k][j])%MOD;
    for(int i=1;i<=3;i++)
        for(int j=1;j<=3;j++)
            a[i][j]=c[i][j];
}
inline void init(){
    for(int i=1;i<=3;i++)
        for(int j=1;j<=3;j++)
            ans[i][j]=0;
    ans[1][1]=1,ans[2][2]=1;
    ans[3][3]=1;
    a[1][1]=1,a[1][2]=0,a[1][3]=0;
    a[2][1]=26,a[2][2]=26,a[2][3]=0;
    a[3][1]=26,a[3][2]=26,a[3][3]=26;
}
inline void write(int x) {
    static int sta[40];
    int top=0;
    do{sta[top++]=x%10,x/=10;}while(x);
    while(top)putchar_unlocked(sta[--top]+48);
}
signed main(){
    int t;
    t=read();
    int x;
    while(t--){
        init();//多测记得清空
        x=read();
        x--;
        int p=floor(x*1.0/2.0);
        while(p){
            if(p&1)matrix_pow1();
            matrix_pow2();
            p>>=1;
        }
        write(((26*(ans[1][1]+ans[2][1]+2*ans[3][1])%MOD)%MOD));
        puts("");
    }
}
```

---

## 作者：zzx0102 (赞：2)

很显然只计算长度是奇数的回文串，乘法原理可以知道个数是 $26^{(m+1)/2}$，如果 $n$ 是偶数我们就将 $n$ 减一，令 $m=\dfrac{n+1}{2}$，然后直接列式：

$$
S=\sum\limits_{i=1}^m (2i-1)\times 26^i
$$

考虑直接消掉，两边同时乘 $26$：

$$
26S=\sum\limits_{i=1}^m (2i-1)\times 26^{i+1}
$$

上下相减可得到 $S$：

$$
S=\dfrac{n\times 26^{m+1}-(1352\times\dfrac{26^{m-1}-1}{25})+26}{25}
$$

直接算 $25$ 的逆元，然后快速幂算，复杂度 $\mathcal{O}(T\log n)$。

如果你愿意，也可以光速幂，这样是 $\mathcal{O}(T+\sqrt n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int p = 1e9 + 7;
int Pow(int a, int b) {
	int ans = 1;
	while(b) {
		if(b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
int ni;
int cal(int m, int n) {
	int a = m * Pow(26, n + 1) % p;
	int b = 1352 * ni % p * (Pow(26, n - 1) - 1) % p + 26;
//	cout << a << ' ' << b << '\n';
	return ni * (a - b + p) % p;
}
signed main() {
	ios::sync_with_stdio(0);
	ni = Pow(25, p - 2);
//	cout << ni << '\n';
	int T; cin >> T;
//	assert(T == 1);
	while(T--) {
		int n; cin >> n; if(n % 2 == 0) n--;
//		assert(n <= 5);
		int m = (n + 1) / 2;
		cout << cal(n, m) << '\n';
	}
	return 0;
}
```

**在本句话之前没有任何一句需要看，后面的才是重要的。**

退役了一年，原本是在八月底复出，然后因为我自己都不知道的原因似了，就没复出。

准备 CSP2024 最后博一次，如果成功尚有机会。

不知道能不能成功，希望能吧，如果不能那我也不知道该何去何从了。

因为在 OI 中失败加上一些人的围剿然后被逼去学 whk 竞赛而放弃了一整年 OI，六月七月八月没有 AC 任何一题，但是竞赛眼看就要成功了，结果也没成功，浪费了一整年，接下来一年也差不多浪费了，导致 s5o 现在之比六年级的时候强了那么一点点。

先复活到 CSP2024，如果成功再做打算，如果没成功也再做打算。我也不知道成功是 1= 还是 7 级。

---

## 作者：irris (赞：1)

## Preface

小学奥数 op 恶评题，建议降橙。

## Solution

显然对于一个长度为 $i$ 的回文串，前 $\lceil \dfrac i2 \rceil$ 个字符任选，后面的字符根据回文规则是固定的。

设 $\lceil \dfrac n2 \rceil = k$，那么原式就可以化为：

$$ans = \displaystyle\sum_{i=1}^k (2i - 1) 26^i$$

小学奥数，错位相减，得到：

$$25ans = (2k - 1)26^{k+1} - 26 - 2\displaystyle\sum_{i=2}^k 26^i$$

后面再用一次等比数列求和，得到：

$$ans = \dfrac{26}{25}\left((2k - 1)26^k - 1 - \dfrac{2}{25}(26^k - 26)\right)$$

预处理一下 $25^{-1}$，对于 $26^k$ 直接光速幂即可，时间复杂度复杂度 $\mathcal O(T + \sqrt{n})$。

## Postscript

本来想贴代码的，结果一发最优解，就不贴了。

---

## 作者：asuldb (赞：1)

这是一道数学题

一个长度为$n$的回文串我们可以先选择$n/2+1$的位置为对称轴，之后向左右两边两边扩展，这左右两边两两相对的共有$n/2$个位置

所以根据乘法原理，有$26^{n/2}$中方案，同时对称轴上的那个位置可以从$26$中选一个

所以

$$s[i]=26^{i/2+1}$$

所以我们求得实际上是

$$\sum_{i=1}^{(n+1)/2}i*26^{(i+1)/2}$$

这是一个非常好看的等差乘以等比，我们可以使用错位相减法将其转化为一个等差数列

比如说$n=5$时数列是

$$1*26^1\text{ } \text{ }\text{ }3*26^2\text{ } \text{ }\text{ }5*26^3$$

我们可以将这个数列整体乘上公差$26$

得到

$$1*26^2\text{ } \text{ }\text{ }3*26^3\text{ } \text{ }\text{ }5*26^4$$

之后我们将新得到的数列整体右移一位，使得指数相同的对齐

之后我们上下一减

差为

$$5*26^4-2*26^3-2*26^2-1*26^1$$

里面有一个等比数列，我们划出来

$$5*26^4-2*(26^3+26^2)-1*26^1$$

这个等比数列我们可以用等比数列求和公式搞出来，于是就是一个快速幂了

最后除以$26-1$就好了，当然这里需要求一个逆元

代码
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#define re register
#define LL long long 
const LL M=1e9+7;
const LL inv=280000002;//25在mod1e9+7意义下的逆元
inline LL quick(LL a,LL b)
{
	LL S=1;
	while(b)
	{
		if(b&1ll) S=S*a%M;
		b>>=1ll;
		a=a*a%M;
	}
	return S;
}
LL n,x,y;
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lld",&n);
		n++,n>>=1ll;
		if(n==1) puts("26");
		else 
		{
			LL ans=((2*(26*26*(quick(26,n-1)-1)%M*inv%M)%M)+26)%M;
			ans=((n*2-1)*quick(26,n+1)%M-ans+M)%M;
			ans=(ans*inv%M)%M;
			printf("%lld\n",ans);
		}
	}
	return 0;
}
```

---

## 作者：Kalista (赞：1)

对于题意，因为是一个长度为奇数回文串，且只用小写字母，只需要确定前一半和中间的一个就可以得到一个方案。

我们的任务就是把这样一个数列求和：

$$a_i=(2\times i-1)\times 26^i$$

这是一个等差乘等比，根据数列知识，可以想到错位相减。

这是求和式：

$$S_n=1\times 26^1+3\times 26^2+5\times 26^3+...+(2n-1)\times 26^n$$

将该式子两边同乘26，再与原式联立并对齐：

$\begin{cases}S_n=1\times 26^1+3\times 26^2+5\times 26^3+...+(2n-1)\times 26^n \\ 26S_n=\ \ \ \ \ \ \ \ \ \ \ \ \ \ 1\times 26^2+3\times 26^3+...+(2n-3)\times 26^{n}+(2n-1)\times 26^{n+1} \end{cases} $

上式减下式（个人习惯）可以得到这样一个式子：

$$-25S_n=26+2\times (26^2+26^3+...+26^n)-(2n-1)\times 26^{n+1}$$

对中间的式子上等比求和公式，为了方便起见将其视为一个$26\times 26^n$的等比数列，有$n-1$项：

$$-25S_n=26+2\times \frac{26^2\times (26^{n-1}-1)}{25}-(2n-1)\times 26^{n+1}$$

将左边的系数移到右边可得最终结果（可能有点小丑，见谅）：

$$S_n=\frac{(2n-1)\times 26^{n+1}-2\times \frac{26^{n+1}-676}{25}-26}{25}$$

然后用逆元直接算就可以，时间复杂度$O(Tlogn)$

---

## 作者：Φρανκ (赞：0)

题意：给定 $n$ ，求 $\sum_{i=1}^ni\times s(i)\times [i\bmod 2]$ 。

核心思想：快速幂

解：

容易发现， 只要求求 $i$ 为奇数时的状况。此时 $s(i)=26^{\frac{i+1}{2}}$ 。

令 $f(x)$ 为 $n=x$ 时问题的答案， $g(x)=\sum_{i=1}^x26^i=\frac{26^{x+1}-26}{25}$ 。

若 $n\equiv 1\pmod 2,$

有 $f(n)=26^1+3\times 26^2+...+n\times26^{\frac{n+1}{2}}$

即 $g(\frac{n+1}{2})+2(26^1g(\frac{n+1}{2}-1)+26^2g(\frac{n+1}{2}-2)+...+26^{\frac{n+1}{2}-1}g(1))$

展开得 $\frac{26^{\frac{n+1}{2}+1}-26+2(26^{\frac{n+1}{2}+1}-26^2+...-...+26^{\frac{n+1}{2}+1}-26^{\frac{n+1}{2}})}{25}$

即 $\frac{n26^{\frac{n+1}{2}+1}-2g(\frac{n+1}{2})+26}{25}$ ，运用快速幂和逆元求算即可。

逆元可以预处理得到，$g(\frac{n+1}{2})$ 也可以用快速幂和逆元直接求算得到。（上式中的 $+26$ 项是因为 $26$ 在 $-2g(\frac{n+1}{2})$ 项中多减了一遍）

若 $n\equiv 0\pmod 2$ ，由最上面的结论有 $f(n)=f(n-1)$ 。

代码：
```
#include <bits/stdc++.h>
using namespace std;
const long long mod=1000000007;
const long long inv=280000002;//逆元
long long t, n, res;
long long qp(long long x, long long y)
{
	if(y==0)
		return 1;
	long long temp=qp(x, y/2);
	if(y%2==0)
		return temp*temp%mod;
	else
		return temp*temp%mod*x%mod;
}//快速幂
long long ge(long long x)
{
	return (qp(26, x+1)-26+mod)%mod*inv%mod;
}//等比数列求和
int main()
{
	cin>>t;
	for(int i=1; i<=t; i++)
	{
		cin>>n;
		if(n%2==0)
			n--;//偶数处理
		cout<<(qp(26, (n+1)/2+1)*n%mod-2*ge((n+1)/2)%mod+26+mod)%mod*inv%mod<<endl;//计算
	}
	return 0;
}

```


---

## 作者：DiruiXiao (赞：0)

## [P4881 hby与tkw的基情](https://www.luogu.com.cn/problem/P4881)

**【题目简述】**

~~有着奇怪的名字~~

设 $s_i$ 表示长度为 $i$ 的所有可能的字符串(仅包含小写字母)中属于回文串的数量。

题目给定了 $n$，求
$$
\sum_{i=1}^{n}i\cdot s_i\cdot (i\bmod 2)
$$
即求出所有奇数长度串中所有回文串的数量乘以长度之和，答案对 $1e9+7$ 取模。

**【解题思路】**

首先考虑求出 $s_i$。

那么对于当前串 $s_i$，可能是从 $s_{i-2}$ 分别在头、尾放两个相同的字母转移而来。则有 $s_i = 26\times s_{i-2}$。若只考虑奇串，且显然有 $s_1 = 26$。则可以推出 $s_i=26^{\frac{i+1}{2}}$。

设长度为 $n$ 的结果为 $S_n$，则有：
$$
S_n=1\times26+3\times26^2+5\times26^3+...+(2n-1)\times 26^{n}
$$

$$
26S_n=1\times 26^2+3\times 26 ^ 3+...+(2n-3)\times 26^{n} +(2n-1)\times 26 ^{n+1}
$$

$$
-25S_n=1\times26 + 2\times 26^2+2\times 26^3 + ...+2\times 26^{n}-(2n-1)\times 26 ^ {n+1}
$$

$$
-25S_n=26 + 2\times\left(\frac{676(1-26^{n})}{-25}\right)-(2n-1)\times 26^{n+1}
$$

$$
S_n=-\frac{26 + 2\times\left(\dfrac{676(1-26^{n})}{-25}\right)-(2n-1)\times 26^{n+1}}{25}
$$

$$
= - \dfrac{\dfrac{650}{25}-\dfrac{1352-52\times 26^{n+1}}{25}-\dfrac{25\times (2n-1)\times^{n+1}}{25}}{25}
$$

$$
= -\dfrac{-702+52\times^{n+1}-(50n-25)\times 26^{n+1}}{625}
$$

$$
=\frac{(50n-27)\times26^{n+1}+702}{625}
$$

带入快速幂求值即可(注意除法要用逆元, 开 `long long`)。时间复杂度 $O(T\log n)$ 。

```cpp
#include<cstdio>
#include<iostream>
typedef long long ll;
using namespace std;
const ll inverse = 571200004, mod = 1000000007; // 625在模1e9+7意义下的逆元
inline ll quickPow(ll a, ll b) { // 快速幂
	ll ans = 1;
	while (b) {
		if (b & 1) ans = (ans * a) % mod;
		a = (a * a) % mod, b >>= 1;
	}
	return ans;
}
int main() {
	ll T; scanf("%lld", &T);
	while (T--) {
		ll N, ans = 0; scanf("%lld", &N);
		ll n = (N & 1) ? ((N + 1) >> 1) : (N >> 1);
		ans = (((((50 * n - 27) % mod) * quickPow(26, n + 1)) % mod + 702) % mod) * inverse;
		ans = ((ans % mod) + mod) % mod; // 保证答案为正数
		printf("%lld\n", ans);
	}
	return 0;
}
```


---

