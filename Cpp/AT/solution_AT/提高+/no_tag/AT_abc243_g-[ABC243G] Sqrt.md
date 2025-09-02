# [ABC243G] Sqrt

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc243/tasks/abc243_g

長さ $ 1 $ の数列 $ A=(X) $ があります。この数列に対して次の操作を $ 10^{100} $ 回行います。

操作：$ A $ の末尾の要素を $ Y $ とする。$ 1 $ 以上 $ \sqrt{Y} $ 以下の整数を自由に選び、$ A $ の末尾に追加する。

$ 10^{100} $ 回の操作後にできる数列は何種類ありますか？

$ T $ 個のテストケースが与えられるので、それぞれについて答えを求めてください。

なお、制約の条件下で答えは $ 2^{63} $ 未満になることが証明されます。

## 说明/提示

### 制約

- $ 1\ \leq\ T\ \leq\ 20 $
- $ 1\ \leq\ X\ \leq\ 9\times\ 10^{18} $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

$ 1 $ つ目のケースでは、操作後の数列として考えられるものは次の $ 5 $ 種類です。 - $ (16,4,2,1,1,1,\ldots) $ - $ (16,4,1,1,1,1,\ldots) $ - $ (16,3,1,1,1,1,\ldots) $ - $ (16,2,1,1,1,1,\ldots) $ - $ (16,1,1,1,1,1,\ldots) $

## 样例 #1

### 输入

```
4
16
1
123456789012
1000000000000000000```

### 输出

```
5
1
4555793983
23561347048791096```

# 题解

## 作者：ran_qwq (赞：22)

### 题意

你现在有一个序列，初始只有一个数 $X$，每次设末尾的数为 $Y$，你可以在 $[1,\sqrt Y]$ 中选择一个 $Z$，把 $Z$ 加入序列的末尾。

执行很多次后，求一共有多少种不同的序列。

### 最暴力的 dp

设 $dp_i$ 为末尾为 $i$ 的方案数。

如果一个序列末尾为 $1$，则它只能再加一个 $1$ 进去，只能有一种情况了。所以边界是 $dp_1=1$。

可以加 $1\sim\sqrt Y$ 的数进去，所以 $dp_i=\sum\limits_{j=1}^{\lfloor\sqrt i\rfloor}dp_j$。

时间复杂度 $O(n\sqrt n)$。

### 稍微优化一点的 dp

其实只需要在 dp 的同时，计算 $s_i=\sum\limits_{j=1}^idp_j$。就可以进行 $O(1)$ 转移了：$dp_i=s_{\lfloor\sqrt i\rfloor}$。

注意要初始化 $s_1=1$。时间复杂度 $O(n)$。

因为 $dp_n=s_{\lfloor\sqrt n\rfloor}$，询问时还可以直接输出 $s_{\lfloor\sqrt n\rfloor}$。时间复杂度 $O(\sqrt n)$。

### 继续优化

$n$ 是 $10^{18}$ 的，这个复杂度仍然接受不了，所以我们要再次优化。

拆开转移方程，得 $dp_n=\sum\limits_{i=1}^{\sqrt{\sqrt n}}(\lfloor\sqrt n\rfloor-i^2+1)dp_i$。

只用处理 $1\sim\sqrt{\sqrt n}$ 的 dp 数组就行了，时间复杂度 $O(\sqrt{\sqrt n})$。

注意精度问题，要手写 sqrt 或者 sqrt 前强转 `long double`。

### 代码

```cpp
void init()
{
	dp[1]=s[1]=1;for(int i=2;i<=N-10;i++) dp[i]=s[Sqrt(i)],s[i]=s[i-1]+dp[i];
}
void solve()
{
	int n=read(),Second=Sqrt(n),y=Sqrt(Second),ans=0;
	for(int i=1;i<=y;i++) ans+=(Second-i*i+1)*dp[i];write(ans,"\n");
}
```

---

## 作者：初雪_matt (赞：13)

可设 $f_i$ 为以 $i$ 开头的方案数，由于最后由于操作数很多所以不用考虑还剩多少次操作，显然可得状态转移方程 $f_i=\sum\limits_{j=1}^{\sqrt i}f_j$，时间复杂度 $O(T+ X\sqrt X)$，空间复杂度 $O(X)$，无法接受。

考虑如何更优，可以发现在 $T$ 次询问中，每次可以直接转移，因此仅需要预处理 $1\sim \sqrt X$ 区间的 $f$，这样让空间降下来了，但是时间复杂度无法接受。

既然 $f_i=\sum\limits_{j=1}^{\sqrt i}f_j$，那么在每次询问中最好的情况是直接知道 $\sum\limits_{j=1}^{\sqrt i}f_j$ 的值，考虑计算出 $1\sim \sqrt[4]{X}$ 的值对所有 $f_j$ 的影响，不难得出 $k$ 的第一次造成影响应从 $k^2$ 起至 $\sqrt[4]{X}$，则将出现次数乘上方案数即为最终答案，答案为 $\sum\limits_{k=1}^{\sqrt[4]{X}}(f_k\times(\sqrt X - k^2+1))$。

注意需要提前预处理 $1\sim \sqrt[4]{X}$ 的 $f$ 值。此题由于数据范围过大，直接用 ``sqrt()`` 肯定有误差，需要先强制转 ``long double`` 类型。

```cpp
#include<bits/stdc++.h>
#define N 2000005
#define mod 998244353
#define int long long
using namespace std;
int n,m,dp[N],f[N];
signed main(){
    int T;
    cin>>T;
    f[1]=1;
    for(int i=2;i<=500000;i++){
        for(int j=1;j<=sqrt((long double)i);j++) f[i]=(f[i]+f[j]);
    }
    while(T--){
        cin>>n;
        int res=0;
        int k=sqrt((long double)n);
        for(int i=1;i<=(int)sqrt((long double)k);i++){
            dp[i]=f[i]*(k-i*i+1);
            res=(res+dp[i]);
        }
        cout<<res<<endl;
    }
}
```

---

## 作者：Luckies (赞：12)

## 题目大意

有一个数列，初始时只有一个数 $X$。你可以对它进行一种操作：设末尾的数为 $Y$，从 $1 \sim \sqrt{Y}$ 中选一个数加到数列的末尾。如此进行 $10^{100}$ 次操作，问数列一共有多少种可能的状态。

## 解法

考虑 DP。

设 $dp_i$ 表示以数字 $i$ 开头的数列可能的状态。设 $i$ 的下一个位置上的数为 $j$，那么显然 $dp_i = \sum\limits_{j = 1}^{\sqrt{i}}{dp_j}$。预处理出 $dp_i$，询问时，答案为 $dp_x$。但此时的时间复杂度为 $\Theta(T+X\sqrt{X})$，对于 $X \le 9 \times10^{18}$ 这种极大的数据范围来说，显然是不可接受的，所以我们需要考虑优化。

设 $j$ 的下一个位置上的数为 $k$，根据前面的转移方程，容易得出 $dp_j = \sum\limits_{k = 1}^{\sqrt{i}}{dp_k}$。我们可以考虑算贡献。贡献是指 $dp_k$ 对 $dp_j$ 的影响，也就是在所有的 $dp_j$ 中，有多少种状态含有 $dp_k$。而 $k$ 的范围是 $1 \sim \sqrt{j}$，也就是 $\sqrt{j} \ge k$ 的 $dp_j$ 才会被 $dp_k$ 所影响，那么对于每一个 $dp_k$，所能贡献的范围就是 $k^2 \sim \sqrt{i}$。这里的 $\sqrt{i}$ 就是所有 $j$ 的范围。这样只需预处理出 $dp_{1 \sim \sqrt[4]{x}}$ 的值，每次询问时，枚举 $1 \sim \sqrt[4]{x}$，也就是 $k$，将所有 $dp_k$ 的贡献加起来即为答案。

这里有几点细节需要注意，由于此题数据范围过大，```sqrt()``` 的精度可能不够，需要将开根的数强制转为 ```long double``` 才行。

## AC Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5;
int t, x, dp[N], f[N];
signed main()
{
	dp[1] = 1;
	for(int i = 2; i <= 1e5; i++)//预处理
		for(int j = 1; j <= sqrt((long double)i); j++)
			dp[i] += dp[j];
	cin >> t;
	while(t--)
	{
		cin >> x;
		int y = sqrt((long double)x);
		int ans = 0;
		for(int i = 1; i <= sqrt((long double)y); i++)
			ans += (y - i * i + 1) * dp[i];//dp[i]产生的贡献的范围是i * i ~ sqrt(sqrt(x))
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：cjh20090318 (赞：6)

## 题意

不说，翻译很清楚。

## 分析

首先看到题面的 $10^{100}$ 次操作，一看就是一个唬人的范围（但是不排除高精度）。

经过观察可以发现，当 $X=10^{18}$ 时，可以发现 $\left\lfloor\sqrt[2^6]X\right\rfloor=1$。

所以说最多添加 $6$ 个数以后就只能添加 $1$ 了，也就意味着此时总方案数不会再变化。

于是我们可以想到**动态规划**。

### 状态设计

设 $f_{i,j}$ 为进行 $i$ 次操作，添加的数为 $j$ 时的情况数。

### 边界条件

$$
f_{0,X}=1
$$

### 状态设计

$$
f_{i,j}=\sum\limits_{k=j^2}^{\sqrt[2^{i-1}]X}f_{i,k}\quad(1\le j \le \sqrt[2^{i-2}]X)
$$

### 最终答案

$$
f_{6,1}
$$

我们可以观察到 $X$ 的范围很大，很难进行存储和转移，所以此时观察规律：
$$
\forall 1 \le j \le \left\lfloor\sqrt{X}\right\rfloor,f_{1,j}=1
$$

$$
\forall 1 \le j \le \left\lfloor\sqrt[4]{X}\right\rfloor,f_{2,j}=\sqrt{X}-j^2+1
$$

此时 $\left\lfloor\sqrt[4]{X}\right\rfloor \le 54722$，可以进行存储了。

转移的时候需要后缀和，才能保证在 $O(1)$  的时间内转移。

时间复杂度 $O(\sqrt[4]X)$。

## 注意事项

$X \le 9 \times 10^{18}$，需要用 `unsigned long long` 存储，`scanf` 的格式符为 `%llu`，~~使用流读入的可以跳过~~。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<cstring>
#include<cmath>
typedef unsigned long long LL;
LL f[11][60000];
LL mysqrt(LL x){//避免浮点误差，进行微调。
	LL ret=sqrt(x);
	for(;ret*ret<=x;++ret);
	for(;ret*ret>x;--ret);
	return ret;
}
int main(){
	int T;scanf("%d",&T);
	for(LL x;T--;){
		memset(f,0,sizeof f);//清空数组。
		scanf("%llu",&x);
		LL sqx=mysqrt(x),ssqx=mysqrt(sqx);
		for(int j=1;j<=ssqx;j++) f[2][j]=sqx-((LL)j*j)+1;//预处理 f[2]。
		for(int j=ssqx-1;j>0;--j) f[2][j]=f[2][j]+f[2][j+1];//进行后缀和。
		for(int i=3;i<=6;i++){
			sqx=ssqx,ssqx=mysqrt(ssqx);
			for(int j=1;j<=ssqx;j++)f[i][j]=f[i-1][(LL)j*j];
			for(int j=ssqx-1;j>0;--j) f[i][j]=(LL)f[i][j]+f[i][j+1];//进行后缀和。
		}
		printf("%llu\n",f[6][1]);
	}
	return 0;
}
```



---

## 作者：XKJie (赞：4)

#### G - Sqrt

显然有限的次数之后 $x$ 会变为 $1$ ，那么之后的操作次数就不需要关心了。

* $O(x^\frac{1}{2})$ 的做法。  

    设 $dp_{x}$ 表示以x开头的种类数. 那么有以下状态转移方程：

    $dp_{x}=\Sigma_{i=1}^{\lfloor \sqrt{x} \rfloor} dp_{i}$

* $O(x^\frac{1}{4})$ 的做法。  
    上述做法对于 $9\times10^{18}$ 的数据范围来说还不够优秀.所以我们要进一步优化。

    注意到我们如果知道了 $A_1=x,A_3=i$ ,那么 $A_2$ 可以为 $i^2\sim\sqrt{x}$ 中的任何一个数。

    那么就有：  
    $dp_{x}=\Sigma_{i=1}^{\lfloor x^{\frac{1}{4}} \rfloor} ({\lfloor \sqrt{x} \rfloor}-i^2+1)dp_{i}$

~~~cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#define ll long long
#define ld long double
#define rep(i,n,m) for(ll i=n;i<=m;++i)
using namespace std;
int t;
ll x,a[25],dp[100000],mx;
int main()
{
    scanf("%d",&t);
    rep(i,1,t)
    {
        scanf("%lld",&a[i]);
        mx=max(a[i],mx);
    }
    ll len=(ll)(sqrt(sqrt((ld)mx)));
    dp[1]=1;
    rep(i,2,len)
    {
        ll l=(ll)(sqrt(sqrt((ld)i))),l2=(ll)(sqrt((ld)i));
        rep(j,1,l)
            dp[i]+=(l2-j*j+1)*dp[j];
    }
  	rep(i,1,t)
    {
        ll ans=0,l=(ll)(sqrt(sqrt((ld)a[i]))),l2=(ll)(sqrt((ld)a[i]));
        rep(j,1,l)
            ans+=(l2-j*j+1)*dp[j];
        printf("%lld\n",ans);
    }
    //system("pause");
    return 0;
}
~~~

* tips: 开根号的时候会出现精度问题.所以我将 $a_{i}$ 从 long long 强制转为了 long double。

    ~~我调了一个小时才发现是这里的问题~~

    或者也可以用以下函数代替原本的 sqrt 来规避精度问题。

    ~~~cpp
    ll isqrt(ll N){
    	ll sqrtN=sqrt(N)-1;
    	while(sqrtN+1<=N/(sqrtN+1))sqrtN++;
    	return sqrtN;
    }
    ~~~


---

## 作者：寄风 (赞：4)

## 前言
模拟赛又出原题，T2考了这题，直接场切。

为方便起见，下文默认 $maxx$ 为 $\max\{x\}$。
## 正文
$10^{100}$ 次操作是完全没有必要的，就算是 $10^{18}$ 开十次根号也只有一点零几了。

然后暴力 dp 是简单的，但是这里还是要讲一下。

容易发现，一个序列进行若干次操作后可能的情况数只与这个数序列的末尾有关，所以我们令 $dp_i$ 表示以 $i$ 结尾进行若干次操作后可能的情况数。

转移方程如下：

$$dp_i=\sum\limits_{j=1}^{\left\lfloor\sqrt{i}\right\rfloor} dp_j$$

预处理出 $maxx$ 以内的 dp 数组，对于每次询问 $O(1)$ 回答。

时空复杂度 $O(maxx)$。

然后对于 $x \le 9 \times 10 ^ {18}$ 的数据，这个复杂度显然无法承受，考虑优化。

可以发现，$dp_i$ 的值其实就是一个从 $dp_1$ 到 $dp_{\left\lfloor\sqrt{i}\right\rfloor}$ 的前缀和。

于是可以处理出 ${\left\lfloor\sqrt{maxx}\right\rfloor}$ 以内的 dp 数组，对于每次询问依然是 $O(1)$ 回答。

时空复杂度 $O(\sqrt{maxx})$。

但是对于这个数据范围，$O(\sqrt{maxx})$ 的时空复杂度显然还不够优秀，考虑继续优化。

考虑算出 $dp_i$ 对答案的贡献。

我们发现，$dp_1$ 对 $dp_{1,2,3,.....}$ 有贡献，$dp_2$ 对 $dp_{4,5,6,.....}$ 有贡献。

易得，$dp_i$ 对 $dp_{i^2,i^2+1,.....}$ 有贡献。

然后处理出 $\left\lfloor maxx^{\frac{1}{4}} \right\rfloor$ 以内的 dp 数组，对于每次询问，按照上面的方式去计算就行了。

注意 `long long` 存不下极限的 $x$，要开 `unsigned long long` 或者 `__int128`。

还有，`sqrt` 有精度误差，要强转 `long double`。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int unsigned long long
int a[1000005] , dp[1000005];
const int mod = 998244353;
signed main(){
//	freopen("quencese.in" , "r" , stdin);
//	freopen("quencese.out" , "w" , stdout);
	int t , x;
	cin >> t;
	dp[1] = 1;
	for(int i = 2;i <= 100000;i++){
		int tmp = sqrt((long double)i);
		for(int j = 1;j <= tmp;j++){
			dp[i] += dp[j];
		}
	}
	while(t--){
		cin >> x;
		int w = sqrt((long double)x);
		int ww = sqrt((long double)w);
		int ans = 0;
		for(int i = 1;i <= ww;i++){
			ans += dp[i] * (w - i * i + 1);
		}
		cout << ans << '\n';
	}
	return 0;
}
```


---

## 作者：出言不逊王子 (赞：2)

因为一个数最多开根 $\log n$ 次就没了，所以一个数列一旦有一位开始变成了 $1$，那么后面全是 $1$，没有统计价值了。

考虑 $f_{i,j}$ 为长度为 $i$ 末尾为 $j$ 的方案数。

很显然对于 $f_{1,j}$，只有 $f_{1,n}$ 是 $1$，其他是 $0$。

对于长度为 $2$ 的数列，末尾的范围变成了 $[1,3\times 10^9]$，还是存不下。

但是我们发现此时对于所有在范围内的值 $x$ 都有 $f_{2,x}=1$，所以我们可以直接标记一下，就不记录了。

对于长度为 $3$ 的数列，末尾的最大值变成了 $\sqrt{
3\times 10^9}<10^5$，可以用数组记录了。

考虑 $f_{i,j}$ 可以被哪些数转移过来。不难发现 $f_{i,j}=\sum_{x=j^2}^{\max j} f_{i-1,x}$，也就是说是上一次时 $f$ 数组的后缀和。

因为我们这个操作只会进行最多 $\log n$ 次，所以每次可以直接暴力做，复杂度是正确的。

最后答案就是 $\sum_{i=1}^{\log n} f_{i,1}$，因为每次转移时 $f_{i,1}$ 会加上 $f_{i-1,1}$，所以最终答案就是 $f_{\log n,1}$。

```cpp
#include<bits/stdc++.h>
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define int long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
#define mid (l+r>>1)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=50001,inf=998244353ll;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
int n,m,f[N],res,p,h[N];
int sqr(int x){
	int l=1,r=1e9,res=1;
	while(l<=r){
		if(mid*mid<=x) res=mid,l=mid+1;
		else r=mid-1;
	}
	return res;
}
void mian(){
	n=read();if(n<4) return void(puts("1"));
	if(n<9) return void(puts("2"));
	if(n<16) return void(puts("3"));
	m=sqr(sqr(n)),p=sqr(n);
	fs(i,1,m,1) f[i]=(p-i*i+1);//上一段的f1没法继承下去了 
	h[m+1]=0;ft(i,m,1,-1) h[i]=(h[i+1]+f[i]);//后缀和 
	while(m!=1){
		p=m,m=sqr(m);//再扣一段 
		fs(i,1,m,1) f[i]=h[i*i];
		h[m+1]=0;ft(i,m,1,-1) h[i]=(h[i+1]+f[i]);
		//现在III的搞完了，要通过III的算IV的 
	} 
	printf("%lld\n",f[1]);
}
signed main(){
//	freopen("x.txt","r",stdin);
//	assert(sqr(1000000000000000000)==sqr(999999999999999999));
//	fs(i,1,100,1) cout<<sqr(i)<<" \n"[i%10==0];
	int t=read();while(t--) mian(); 
	return 0;
}
//显然很多答案都是一样的吧
//显然个锤子
//倒推没法复原啊
//开根的话最多log次就到1了 
//所以我们假设f[i][j]表示长度为i，末尾是j的方案数
//感觉不是很好做，再想想（p=sqn） 
//f[2][1..p]=1
//f[3][1]=p
//f[3][2]=p-1，除了1搞不上来其他都搞的
//答案就是p-[小于自己的平方数的个数]
//然后就可以递推了？因为只要递推到1就可以扔掉 
//不对啊，这个操作是不是还要前缀加什么的
//我想想，哦T是100啊，那这个应该合法
//但是怎么抱枕每次扩张都是O1的？
// 
```

---

## 作者：smallpeter (赞：2)

提供一个预处理 $O(n^{\frac{1}{4}})$，询问 $O(1)$ 的做法。

# 题解

不难发现次数足够多，而每次开跟下降的速度又足够快，于是考虑设 $f_i$ 表示开头为 $i$ 的方案数，答案便是 $f_x$。

考虑如何转移。枚举下一个数选什么，于是得到转移 $f_i={\sum\limits_{j=1}^{\sqrt i}f_j}$。

想到用前缀和维护这个东西，设 $sum_i=\sum\limits_{j=1}^{i}f_j$，则 $f_i=sum_{\sqrt i}$。但是 $x$ 最大为 $9\times 10^{18}$，直接求出所有的 $f_i$ 显然不现实。

考虑再次拆分，变成 $f_i=\sum\limits_{j=1}^{\sqrt i}\sum\limits_{k=1}^{\sqrt j}f_k$。


这下我们舒服了，因为 $k\le \sqrt j\le \sqrt[4]{i}\le6\times10^4$，也就是说我们可以提前预处理出这个范围内的所有数。

再次改进一下式子，变成 $f_i=\sum\limits_{j=1}^{\sqrt i}sum_{\sqrt j}$。此时 $\sqrt j$ 的值域不大，可以考虑把式子转成 $f_i=\sum\limits_{j=1}^{\sqrt[4]i}t_j \times sum_j$，$t_j$ 表示满足 $k\in [1,\sqrt i]$ 且 $\left\lfloor \sqrt k\right\rfloor =j$ 的 $k$ 的个数。可以发现 $t_j=2\times j +1(\sum\limits_{k=1}^jt_k \le i)$。也就是说我们再维护一个前缀和，记作 $sum2$。$sum2_i=\sum\limits_{j=1}^{i} t_j\times sum_j$。设最大的满足 $\sum\limits_{j=1}^{s}t_j \le x$ 的数为 $s$，则 $ans=f_x=sum2_s+(x-\sum\limits_{j=1}^{s}t_j )\times sum_{s+1}$。显然 $s=\left\lfloor \sqrt {\sqrt x+1} -1\right\rfloor$，然后这题就做完了。

# 代码
```cpp
// LUOGU_RID: 116574922
#include<bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
#define fi first
#define se second
#define pb push_back
#define pii pair<LL,LL>
#define mem(a,x) memset((a),(x),sizeof(a))

//#define long long int
#define LLL __int128

template<typename type>
inline void read(type &x)
{
    x=0;bool flag(0);char ch=getchar();
    while(!isdigit(ch)) flag=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    flag?x=-x:0;
}

template<typename type>
inline void write(type x,bool mode=1)//0为空格，1为换行
{
    x<0?x=-x,putchar('-'):0;static short Stack[50],top(0);
    do Stack[++top]=x%10,x/=10; while(x);
    while(top) putchar(Stack[top--]|48);
    mode?putchar('\n'):putchar(' ');
}

LL qsm(LL a,LL b,LL mod){
	LL ans=1,sum=a;
	while(b){
		if(b&1) ans=ans*sum%mod;
		sum=sum*sum%mod;
		b>>=1;
	}
	return ans;
}

const LL N=1e5+10,mod=998244353,INF=3e9;

LL sum[N],f[N],summ[N];

void init(){
	f[1]=1;
	sum[1]=1;
	for(LL i=2;i<N;i++){
		f[i]=sum[(LL)sqrt((LD)i)];
		sum[i]=sum[i-1]+f[i];
	}
	LL nw=3;
	for(LL i=1;i<N;i++){
		summ[i]=summ[i-1]+nw*sum[i];
		nw=nw+2;
	}
}

LL cnt(LL x){
	return 2*x+x*x;
}

void solve(){
	init();
	LL q;
	read(q);
	while(q--){
		LL x;
		read(x);
		x=(LL)sqrt((LD)x);
		LL l=1,r=INF+1,mid,ans=0;
		/*
		while(l<=r){
			mid=l+r>>1;
			if(cnt(mid)<=x){
				ans=mid;
				l=mid+1;
			}
			else r=mid-1;
		}
		*/
		ans=sqrt((LD)(x+1))-1;
		LL sheng=x-cnt(ans);
		printf("%lld\n",summ[ans]+sheng*sum[ans+1]);
	}
}

int main(){
//	freopen("quencese.in","r",stdin);
//	freopen("quencese.out","w",stdout);
	LL T=1;
//	read(T);
	while(T--){
		solve();
	}
}

```

记得在开根前要强转 ```long double```，不然会炸精度。

---

## 作者：Register_int (赞：1)

线性 $dp$ 大家都会，直接 $dp_n=\sum_{i=1}^{\sqrt n}dp_i$ 就可以了，不再赘述。

显然第一次操作没用，范围直降 $3\times10^9$，但还是会寄。

考虑怎么砍掉第二次操作。观察到有很多数开根后结果一样，合并处理就完事了，复杂度直降 $O(\sqrt[4]n)$。

最后，`sqrt` 要手动补足精度误差。

# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

inline 
ll sq(ll x) {
	ll res = sqrt(x);
	for (; res * res > x; res--);
	for (; res * res <= x; res++);
	return res - 1;
}

int t, k;

ll x, dp[54773], res;

int main() {
	dp[1] = 1;
	for (int i = 2; i <= 54772; i++) {
		for (int j = 1; j <= i / j; j++) dp[i] += dp[j];
	}
	for (int i = 2; i <= 54772; i++) dp[i] += dp[i - 1];
	for (scanf("%d", &t); t--;) {
		scanf("%lld", &x);
		if (x <= 3e9) printf("%lld\n", dp[sq(x)]);
		else {
			res = 0, x = sq(x), k = sq(x);
			for (ll i = 1; i < k; i++) res += dp[i] * (i << 1 | 1); res += dp[k] * (x - (ll)k * k + 1);
			printf("%lld\n", res);
		}
	}
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

考虑动态规划算法。

定义 $dp_i$ 表示以第 $i$ 个数开头的方案数。

显然答案是 $\sum\limits_{j=1}^W dp_j$。

状态转移方程为：

$$dp_i=\sum\limits_{j=1}^{\lfloor \sqrt i \rfloor} dp_j$$

时间复杂度为：$O(W \sqrt W)$。

考虑优化，即 $F_i=\sum\limits_{j=1}^i dp_j$，每次可转移为 $F_i=F_{i-1}+dp_i$。

那么原式化为：

$$dp_i=F_{\lfloor \sqrt i \rfloor}$$

时间复杂度优化为：$O(W)$。

同时发现对于 $dp_{\sqrt W \sim W}$ 的值都在 $dp_{1 \sim \lfloor \sqrt W \rfloor}$ 中重复过。

所以我们需要算 $dp_{1 \sim \lfloor \sqrt w \rfloor}$ 即可，每次询问输出 $F_{\lfloor \sqrt x \rfloor}$。

时间复杂度优化为：$O(\sqrt W)$。

因为还是过不去，所以将原式再次爆拆：

$$dp_i=\sum\limits_{j=1}^{\lfloor \sqrt i \rfloor} \sum\limits_{k=1}^{\lfloor \sqrt j \rfloor} dp_k$$

这样的话 $1 \le k \le \sqrt[4]{W}$，大概在 $10^4 \sim 10^5$ 左右。

可以按照上述讲的方法，将 $dp_{1 \sim \sqrt[4]{W}}$ 求出来。

然后试试继续把式子化简：

$$dp_i=\sum\limits_{j=1}^{\lfloor \sqrt i \rfloor} \sum\limits_{k=1}^{\lfloor \sqrt i \rfloor} [j^2 \le k]dp_j$$

然后把 $j^2$ 提出来：

$$dp_i=\sum\limits_{j=1}^{\lfloor \sqrt[4]{i} \rfloor} \sum \limits_{k=j^2}^{\lfloor \sqrt i \rfloor} dp_j$$

现在只需要快速求出 $\sum \limits_{k=j^2}^{\lfloor \sqrt i \rfloor}$ 即可，可以直接化简为：

$$\sum \limits_{k=j^2}^{\lfloor \sqrt i \rfloor}=(\lfloor \sqrt i \rfloor-j^2+1)$$

故原式简化为：

$$dp_i=\sum\limits_{j=1}^{\lfloor \sqrt i \rfloor} \sum\limits_{k=1}^{\lfloor \sqrt i \rfloor} [j^2 \le k]dp_j=\sum\limits_{j=1}^{\lfloor \sqrt[4]{i} \rfloor} (\lfloor \sqrt i \rfloor-j^2+1) \times dp_j$$

时间复杂度为：$O(T \times \sqrt[4]{W})$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=100100; 
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll T,n,t,p,sum=0;
ll dp[N],F[N];
void init(){
	dp[1]=F[1]=1;
	for(int i=2;i<N;i++){
		t=sqrt(i);
		dp[i]=F[t];
		F[i]=F[i-1]+dp[i];
	}
}
int main(){
	init();
	T=read();
	while(T--){
		sum=0;
		n=read();
		t=sqrt(n);
		p=sqrt(t);
		for(ll i=1;i<=p;i++)
		  sum+=(t-i*i+1)*dp[i];
		write(sum);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：__log__ (赞：0)

~~一眼丁真，鉴定为 dp 题一道。~~

~~改3次啦~~
# solution
从计算方案数可以看出使用递推或排列组合，但排列组合明显不靠谱，所以考虑 dp。既然用 dp 就要用 lyl 老师 dp 三件套了。
## $\text{Part 1}$：$\text{dp}$
### $\text{step 1}$：定义状态 & 答案状态
先不考虑 $x \le 2^{63} - 1$ 的数据范围，考虑最暴力的状态。

令 $dp_{i, j}$ 为操作 $i$ 次后序列末尾为 $j$ 的序列数。

但是要操作 $10^{100}$ 次，难道答案 $ans = \sum{dp_{10^{100},x}}$？

但是，我们打开计算器，可以知道操作最多 $7$ 次后序列末尾的数必为 $1$。因为：
$$\sqrt[2^{7}]{2^{64}} = \sqrt{2}=1$$
（在整数意义下）

因此后面的操作就可以忽略。

所以我们可以放心大胆的让 $ans = dp_{7,1}$。
### $\text{step 2}$：求递推式
每次操作序列末尾都会有一个最大值 $Max_{i}$，不难得知 $Max_{i} = \sqrt[2^i]{x}$。

序列末尾为 $j$ 的必要条件是序列上一个值 $j_1 \geq j^{2}$。

所以~~显然~~，状态转移方程为：
$$dp_{i,j} = \sum_{k = j^2}^{Max_{i - 1}}dp_{i - 1,k}$$
含义为在 $i-1$ 次操作后末尾为 $j^2$ 到 $Max_{i-1}$ 的序列末尾再加一个 $j$。然后用前缀和优化。

~~就我一个冤种用树状数组吗？？？~~

令 $preSum_{i,j} = \sum_{k = 1}^{j}dp_{i,k}$，可以改写方程：
$$dp_{i,j} = preSum_{i - 1,Max_{i - 1}}-preSum_{i-1,j^2-1}$$
### $\text{step 3}$：考虑初值
现在考虑 $x \leq 2^{63} - 1$ 的条件，因为不操作的序列只有 $1$ 种可能（只有 $x$），所以 $dp_{0,x} = 1$ ， 但是 $x$ 太大了。

再敲一下计算器，得知 $\sqrt[2^2]{2^{64}}=65536$，这个范围可以用数组维护了，换而言之，从第二次操作开始可以用数组记录了。

那第一次操作怎么记录？~~显然~~结论：$dp_{1,i} = 1(1 \leq i \leq \sqrt{x})$，因为对于每一个 $i$，序列只有 $x,i$ 这一种。

## $\text{Part 2}$：实现细节
1. 记录每次操作的最大值，维护 $Max_i = \sqrt{Max_{i - 1}}$，记住： $Max_0=x$。
2. 对于 $Max_1 = 1$ 的，即 $x \leq 3$，**可以**（非必须）直接特判答案为 $1$。
3. 对第 $2$ 次操作进行特判：
$$dp_{2,i} = \sum_{j = i^2}^{Max_1}dp_{1,j} = Max_1 - i^2 + 1$$
4. 每次操作前缀和记录。
5. 多测。
6. 时间复杂度 $O(\sqrt[4]{x})$。

## $\text{Code}$
[code](https://www.luogu.com.cn/paste/lzbw6qcp)

---

## 作者：Galois_Field_1048576 (赞：0)

令 $f(i)$ 为以 $i$ 结尾的序列总数。容易发现
$$
\begin{aligned}
f(i) &= \sum_{k=1}^{\lfloor\sqrt i\rfloor} f(k) \\
&= \sum_{k=1}^{\lfloor\sqrt i\rfloor} \sum_{l=1}^{\lfloor\sqrt k\rfloor} f(l) \\
&= \sum_{l=1}^{\lfloor\sqrt i\rfloor} \sum_{k=1}^{\lfloor\sqrt i\rfloor} [l^2 \le k]  f(l) \\
&= \sum_{l=1}^{\lfloor i^{1/4}\rfloor} \sum_{k=l^2}^{\lfloor\sqrt i\rfloor} f(l) \\
&= \sum_{l=1}^{\lfloor i^{1/4}\rfloor} (\lfloor\sqrt i\rfloor-l^2+1)f(l).
\end{aligned}
$$
于是考虑 预处理出 $f(1)..f(\max x^{1/4})$，对于每一个询问，按照柿子计算即可。

---

## 作者：xiahaob (赞：0)

# [ABC243G] Sqrt 题解

## 题意

你现在有一个数 $N$。

每次你可以进行以下操作：

> 设末尾的数是 $Y$。在 $1$ 到 $\lfloor \sqrt{Y}\rfloor$ 中选取一个数 $Z$。
>
> 把 $Z$ 加到序列的末尾。

如此进行 $10^{100}$ 次操作，问一共有多少种可能的情况。

$N \le 9 \times 10^{18}$。

## 分析

首先考虑一件事，$10^{100}$ 次操作真的会用完吗？

不难发现极限情况下第 $7$ 个数就变成 $1$ 了。

所以不用管那么多，直接转移即可。

设 $f_i$ 表示以 $i$ 开头时的所有方案。

可以很快得列出方程：

$$
f_i=\sum_{j=1}^{\lfloor\sqrt{i}\rfloor} f_j
$$

然后用一个前缀和优化一下。

设 $sum_i=\sum_{j=1}^{i}f_j$，故 $f_i=sum_{\lfloor\sqrt{i}\rfloor}$。

这样就只需要预处理出 $\sqrt{n}$ 的数据。

但显然对于 $9\times 10^{18}$ 的数据不仅时间会炸，空间也会炸。

继续优化，设 $A_i$ 为第 $i$ 个位置的值。

当我们知道了 $A_1$ 和 $A_3$ 的时候，$A_2$ 就能在 $\left[A_3\times A_3,\sqrt{A_1}\right]$ 中任取一个数。

所以直接枚举 $A_3$。然后直接算答案。


$$
ans=\sum_{i=1}^{\sqrt[4]{N}}(\sqrt{N}-i\times i+1)\times f_i
$$

然后时间复杂度就优化成了 $O(T\times \sqrt[4]{N})$。

#### 细节

此题卡精度。要开 `long double`。

~~考试的时候不要乱开数组，不然会MLE，搞得暴力分都没有。~~

### Code

```cpp
// the code from xhb
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
inline int read(){
	int s=0,w=1;char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')w=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())s=s*10+ch-'0';
	return s*w;
}
const int maxn=9e18;
int T;
int f[60000],sum[60000];
inline void init(){
	int val=sqrt(sqrt((long double)maxn));//实测卡精度!!!
	f[1]=sum[1]=1;
	for(int i=2;i<=val;++i){
		f[i]=sum[(int)sqrt((long double)i)];
		sum[i]=sum[i-1]+f[i];//前缀和优化。
	}
}
inline int getans(int x){
	int ans=0;
	int val=sqrt(sqrt((long double)x));
	int VV=sqrt((long double)x);
	for(int i=1;i<=val;++i)ans+=f[i]*(VV-i*i+1);//计算答案。
	return ans;
}
signed main(){
	init();
	T=read();
	while(T--){
		int x=read();
		printf("%lld\n",getans(x));
	}
}
```


---

