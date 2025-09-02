# [ABC215G] Colorful Candies 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc215/tasks/abc215_g

$ N $ 個のキャンディが左右一列に並んでいます。  
 それぞれのキャンディは、色 $ 1 $、色 $ 2 $、$ \ldots $ 、色 $ 10^9 $ の、$ 10^9 $ 種類の色のうちいずれかの色をしています。  
 $ i\ =\ 1,\ 2,\ \ldots,\ N $ について、左から $ i $ 番目のキャンディの色は色 $ c_i $ です。

高橋君は並んでいる $ N $ 個のキャンディのうち $ K $ 個を選び、選んだ $ K $ 個のキャンディをすべてもらいます。  
 ここで、$ N $ 個のキャンディから $ K $ 個を選ぶ組み合わせの個数は二項係数を用いて $ \binom{N}{K} $ 個と表せますが、 高橋君は $ \binom{N}{K} $ 通りの選び方のうちいずれか一つを等確率でランダムに選びます。

高橋君はいろいろな色のキャンディを食べたいので、もらうキャンディに含まれる色の種類数が多いほどうれしい気持ちになります。  
 $ K\ =\ 1,\ 2,\ \ldots,\ N $ のそれぞれの場合について、高橋君がもらうキャンディに含まれる色の種類数の期待値を求めてください。  
 ここで、求める答えは有理数となることが証明できます。答えとなる有理数を注記で述べるように $ \bmod\ 998244353 $ で出力してください。

## 说明/提示

### 注記

有理数を出力する際は、まずその有理数を分数 $ \frac{y}{x} $ として表してください。ここで、$ x,\ y $ は整数であり、$ x $ は $ 998244353 $ で割り切れてはなりません（この問題の制約下で、そのような表現は必ず可能です）。そして、$ xz\ \equiv\ y\ \pmod{998244353} $ を満たすような $ 0 $ 以上 $ 998244352 $ 以下の唯一の整数 $ z $ を出力してください。

### 制約

- $ 1\ \leq\ N\ \leq\ 5\ \times\ 10^4 $
- $ 1\ \leq\ c_i\ \leq\ 10^9 $
- 入力はすべて整数

### Sample Explanation 1

$ K\ =\ 1 $ のとき、高橋君がもらうキャンディの組み合わせは、「 $ 1 $ 番目のみ」「 $ 2 $ 番目のみ」「 $ 3 $ 番目のみ」の $ 3 $ 通りがあります。 いずれの場合も、含まれる色は $ 1 $ 種類です。よって、含まれる色の種類数の期待値は $ 1 $ となります。 $ K\ =\ 2 $ のとき、高橋君がもらうキャンディの組み合わせは、「 $ 1 $ 番目と $ 2 $ 番目」「 $ 2 $ 番目と $ 3 $ 番目」「 $ 1 $ 番目と $ 3 $ 番目」の $ 3 $ 通りがあります。 - 「 $ 1 $ 番目と $ 2 $ 番目」をもらう場合、含まれる色は $ 2 $ 種類 - 「 $ 2 $ 番目と $ 3 $ 番目」をもらう場合、含まれる色は $ 1 $ 種類 - 「 $ 1 $ 番目と $ 3 $ 番目」をもらう場合、含まれる色は $ 2 $ 種類 となりますから、含まれる色の種類数の期待値は、$ \frac{1}{3}\ \cdot\ 2\ +\ \frac{1}{3}\ \cdot\ 1\ +\ \frac{1}{3}\ \cdot\ 2\ =\ \frac{5}{3} $ です。 注記に述べたように、$ \bmod\ 998244353 $ で出力することに注意してください。 $ K\ =\ 3 $ のとき、高橋君がもらうキャンディの組み合わせは、「 $ 1,\ 2,\ 3 $ 番目のすべて」の $ 1 $ 通りのみであり、含まれる色は $ 2 $ 種類です。 よって、含まれる色の種類数の期待値は $ 2 $ となります。

## 样例 #1

### 输入

```
3
1 2 2```

### 输出

```
1
665496237
2```

## 样例 #2

### 输入

```
11
3 1 4 1 5 9 2 6 5 3 5```

### 输出

```
1
725995895
532396991
768345657
786495555
937744700
574746754
48399732
707846002
907494873
7```

# 题解

## 作者：run_away (赞：4)

## 题意概括

有 $n$ 个糖果，每种都有一个颜色 $c_i$，求对于所有 $k\in [1,n]$，求出 $C_n^k$ 种方案中糖果种类的期望数，**对** $998244353$ **取模**。
## 分析

通过期望的定义，设 $vis_i$ 表示每种颜色有没有被选，颜色总数为 $m$，则期望为 $E(\sum\limits_{j=1}^{m}vis_j)$，由线性期望的性质，$E(\sum\limits_{j=1}^{m}vis_j)=\sum\limits_{j=1}^{m}E(vis_j)$。

因为一个颜色的期望为：出现的方案数/总方案数=(总方案数-未出现的方案数)/总方案数，设每种颜色的总数为 $cnt_j$，所以 $E(vis_j)=\frac{C_{n}^{k}-C_{n-cnt_j}^{k}}{C_n^k}$。

可以把 $c$ 数组离散化，再计算 $cnt$，因为 $\sum\limits_{i=1}^{m}cnt_i=n$，可把式子转化成 $m_{max}(m_{max}+1)=2n$，所以 $m$ 严格小于 $\sqrt n$，总时间复杂度在 $O(n\sqrt n)$ 级别。

因为空间足够，且调用次数较多，预处理出 $1\sim n$ 的阶乘和逆元，用于 $O(1)$ 求解组合数。
## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const ll mod=998244353;
ll n,m,c[50005],b[50005],col[50005],cnt[50005],jc[50005],inv[50005];
inline ll qpow(ll a,ll b){
    ll res=1;
    while(b){
        if(b&1)res=res*a%mod;
        a=a*a%mod,b>>=1;
    }
    return res;
}
inline void init(ll x){
    jc[0]=1;
    for(ll i=1;i<=x;++i){
        jc[i]=jc[i-1]*i%mod;
    }
    inv[x]=qpow(jc[x],mod-2);
    for(ll i=x-1;i>=0;--i)inv[i]=inv[i+1]*(i+1)%mod;
}
inline ll C(ll n,ll m){
    if(m<0||n<m)return 0;
    return jc[n]*inv[n-m]%mod*inv[m]%mod;
}
map<ll,ll>mp1,mp2;
signed main(){
    cin>>n,init(n);
    for(ll i=1;i<=n;++i)cin>>c[i],mp1[c[i]]++;
    for(auto i:mp1)mp2[i.second]++;
    for(auto i:mp2)c[++m]=i.first,cnt[m]=i.second;
    for(ll i=1;i<=n;++i){
        ll ans=0;
        for(ll j=1;j<=m;++j){
            ans=(ans+(C(n,i)-C(n-c[j],i)+mod)%mod*cnt[j]%mod)%mod;
        }
        ans=ans*qpow(C(n,i),mod-2)%mod;
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：AKPC (赞：1)

对于一个 $k$ 以及出现 $c$ 次的数，其出现的概率为 $\frac{{n\choose k}-{n-c\choose k}}{n\choose k}$，所以记录 $c_i$ 表示 $i$ 出现的次数，那么 $k$ 的答案为：

$$\sum_{i=1}^{10^9}\frac{{n\choose k}-{n-c_i\choose k}}{n\choose k}$$

显然我们将 $a$ 离散化，可以将复杂度优化为 $n^2$。

进一步优化，我们记录 $t_i$ 表示 $c_j=i$ 的 $j$ 的个数，然后将出现次数 $i$ 的贡献乘以 $t_i$ 倍。容易猜到 $t_i>0$ 的 $i$ 至多 $\sqrt n$ 个，故复杂度被优化为 $n\sqrt n$。

[code](https://www.luogu.com.cn/paste/2wz761rb)。

---

## 作者：A6n6d6y6 (赞：1)

## 前言
[传送门](https://www.luogu.com.cn/problem/AT_abc215_g)

做之前：在刷概率与期望题目。欸？怎么这道题还没刷？

做当中：思路知道了，写好代码：怎么TLE了 ？？？

做之后：原来还能这么做题。
## 正文

言归正传，糖果的贡献显然与颜色无关，只与每种颜色的个数有关。

首先离散化，设一共有 $m$ 中不同的颜色，离散化后为 $1,2,3,\cdot\cdot\cdot,m$。设 $c_i$ 为颜色为 $i$ 的糖果数量。

依次考虑每次选择 $k$ 个糖果：定义离散型随机变量 $x_i=1/0$ 表示第 $i$ 种类的糖果选/不选。那么期望为 $E(\sum\limits_{i=1}^m x_i)=\sum\limits_{i=1}^mE(x_i)$（和的期望等于期望的和）。

显然，一个颜色出现的期望为：$E(x_i)=\dfrac{C_n^k-C_{n-c_i}^k}{C_n^k}$。

如果直接枚举 $i,k$，时间复杂度为 $O(n^2)$。考虑优化。

优化：如果有 $t$ 种颜色的糖果，数量均为 $c_i$，则只需计算 $t\times E(x_i)$。设 $c$ 中不同颜色糖果有 $b$ 种，而 $\sum\limits_{i=1}^mc_i=n$，所以 $b$ 的上界显然为 $\sqrt n$。

## 坑点

- 不能每次都用费马小定理求逆元，这样时间复杂度是 $O(n\sqrt n\log n)$。需要预处理从 $1$ 到 $n$ 的逆元，这样时间复杂度为 $O(n\sqrt n)$；
- 时限 $4$ 秒，但注意你的常数，否则你就会[这样](https://www.luogu.com.cn/record/146209167)（就差0.1秒）。

## AC Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
    int x=0;char ch;
    for(ch=getchar();!isdigit(ch);ch=getchar());
    for(;isdigit(ch);ch=getchar())x=x*10+ch-'0';
    return x;
}//卡常快读
void write(int x){
    if(x>9)write(x/10);
    putchar(x%10+'0');
    return;
}//卡常快写
const int maxn=5e4+10,mod=998244353;
int n,m,T,ans,a[maxn],c[maxn],f[maxn],g[maxn];
unordered_map<int,int>lsh,cnt;
int ksm(int x,int b){
	int ans=1;
	while(b){
		if(b&1)ans=ans*x%mod;
		x=x*x%mod,b>>=1;
	}
	return ans;
}//快速幂
int inv(int x){
    if(x<=5e4)return g[x];//如果预处理过就返回预处理后的值
    return ksm(x,mod-2);//否则直接算
}
int C(int x,int y){
	if(x<0||y<0||x<y)return 0;
	return f[x]*inv(f[y]*f[x-y]%mod)%mod;
}//组合数
signed main(){
	f[0]=1;for(int i=1;i<=5e4;i++)f[i]=f[i-1]*i%mod;
	for(int i=1;i<=5e4;i++)g[i]=ksm(i,mod-2);//预处理
	n=read();
	for(int i=1;i<=n;i++)lsh[a[i]=read()]++;
	for(auto i:lsh)cnt[i.second]++;
	for(auto i:cnt)m++,a[m]=i.first,c[m]=i.second;//离散化+统计出现次数
	for(int k=1;k<=n;k++){
		ans=0;
		for(int j=1;j<=m;j++)
			ans=(ans+(C(n,k)-C(n-a[j],k)+mod)%mod*c[j]%mod)%mod;
		ans=ans*inv(C(n,k))%mod;
		write(ans);putchar('\n');//计算并输出
	}
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/146229683)，~~极限数据3.96秒爬过去的~~。

---

## 作者：qwer6 (赞：0)

## Description

现在有 $x$ 颗糖果，第 $i$ 颗糖果有一个颜色 $c_i$，现在定义快乐值为取出的糖果中颜色种类数，要求对于 $k\in[1,n]$，求出随机取出 $k$ 颗糖果的快乐值的期望。

## Solution

初一看并不好做，因为看起来可能需要状压每一种颜色是否获得过了，但是我们可以想到，一种颜色在第 $k$ 次抽取中做出贡献的概率，就是在前 $k-1$ 次中都没能抽出来的概率乘上在第 $k$ 次抽取中抽出这种颜色的概率，所以一种颜色在第 $k$ 次抽取中的贡献的期望为 $p\times \frac{cnt}{n-k}$，其中 $p$ 表示前 $k-1$ 次都没有抽出这种颜色的概率，$cnt$ 表示这种颜色的糖果共有几颗。

那么我们枚举 $k$，然后在求解过程中维护 $p$ 就可以了，$p$ 的计算方式显然，之前抽不到的概率乘上这次也抽不到的概率即可。

但是时间复杂度为 $O(n^2)$，必然得到超时的结果，所以考虑优化。

显然，我们可以发现，对于所有 $cnt$ 相同的颜色，在每一次计算中做出的贡献也是相同的，所以我们记录一个 $cntt_i$ 表示出现 $cnt=i$ 的颜色的个数，然后只需枚举颜色出现的次数，计算贡献，乘上 $cntt$ 即可。

时间复杂度为 $O(nm)$，其中 $m$ 表示 $cnt$ 可能值的个数，想要 $cnt$ 可能值的个数最多，可以使用如下构造：第 $i$ 种颜色出现 $i$ 次，$m$ 大约为 $\sqrt n$，所以总时间复杂度为 $O(n\sqrt n)$，可以通过此题。

## Code

```c++
/*by qwer6*/
/*略去缺省源和快读快写*/
const int mod=998244353;
const int N=5e4+5;
int n,tot,tott,ans;
int c[N],tmp[N],p[N],cnt[N],cntt[N],inv[N];
int mul(int x,int y){
	long long res=1ll*x*y;
	if(res>=mod)return res%mod;
	return res;
}
int add(int x,int y){
	x+=y;
	if(x>=mod)return x-mod;
	return x;
}
int binpow(int a,int b){
	int res=1;
	while(b){
		if(b&1)
			res=mul(res,a);
		a=mul(a,a);
		b>>=1;
	}
	return res;
}
signed main(){
	read(n);
	for(int i=1;i<=n;i++)tmp[i]=read(c[i]);
	sort(tmp+1,tmp+n+1);
	tot=unique(tmp+1,tmp+n+1)-tmp-1;
	for(int i=1;i<=n;i++){
		c[i]=lower_bound(tmp+1,tmp+tot+1,c[i])-tmp;
		cnt[c[i]]++;
	}
	for(int i=1;i<=tot;i++)tmp[i]=cnt[i];
	sort(tmp+1,tmp+tot+1);
	tott=unique(tmp+1,tmp+tot+1)-tmp-1;
	for(int i=1;i<=tot;i++){
		cnt[i]=lower_bound(tmp+1,tmp+tott+1,cnt[i])-tmp;
		cntt[cnt[i]]++;
	}
	for(int i=1;i<=tott;i++)p[i]=1;
	inv[1]=1;
	for(int i=2;i<=n;i++)
		inv[i]=mul(mod-mod/i,inv[mod%i]);
	for(int i=1,Inv,j;i<=n;i++){
		Inv=inv[n-i+1];
		for(int j=1;j<=tott;j++){
			ans=add(ans,mul(mul(mul(p[j],tmp[j]),Inv),cntt[j]));
			if(i>n-tmp[j])p[j]=0;
			else p[j]=mul(mul(p[j],n-i+1-tmp[j]),Inv);
		}
		write(ans),Nxt;
	}
}
```

---

## 作者：FreedomKing (赞：0)

同学推荐的作为 900AC 的神秘数学题。

### 思路

下文中$a_i$表示 $i$ 在序列中的出现次数，离散化肯定是要做的，下文默认已离散化。

因为有 $E(\sum p_i)=\sum E(p_i)$，故可以想到将种颜色分开讨论计算期望然后求和，即得到 $\sum\tfrac{C_n^k-C_{n-a_i}^k}{C_n^k}$，但对于每一个 $k$ 都需要 $O(m)$ 地计算一遍答案故时间复杂度是 $O(n^2)$ 的。

考虑优化，$k$ 一定是要枚举的，所以观察后面的式子 $\tfrac{C_n^k-C_{n-a_i}^k}{C_n^k}$，发现在 $k$ 固定时只有 $n-a_i$ 是变量即只有 $a_i$ 是变量，如果把 $a_i$ 相同的数一起统计则只需要统计 $a_i$ 不同的个数的次数，想让这个次数最大化一定是要让 $a_i$ 内的元素互异的，也就是说形如 $a=1,2,3,4,5,\dots$ 这样，设 $m$ 为 $a$ 的元素数量即得 $\sum_{i=1}^mi=\tfrac{m(m+1)}{2}=n$，得到 $m$ 的数量级约只有 $\sqrt n$。也就是说最终的式子 $\sum_{i=1}^m\tfrac{C_n^k-C_{n-a_i}^k}{C_n^k}\times cnt_i$ 的时间复杂度为 $O(n\sqrt n)$，可以接受，其中 $cnt_i$表示出现次数为 $i$ 的数的个数。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,mN=5e4+5,mod=998244353;
namespace FreedomKing_qwq{
	inline int qread(){
#define qr qread()
		int x=0,c=getchar(),t=1;
		while(c<'0'||c>'9'){
			t^=(c=='-');
			c=getchar();
		}
		while(c>='0'&&c<='9'){
			x=(x<<3)+(x<<1)+c-'0';
			c=getchar();
		}
		return (t?x:-x);
	}
	inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
		if(x<0) putchar('-'),x=-x;
		if(x>9) qw(x/10);
		putchar(x%10+'0');
		return;
	}
	inline int qpow(int x,int p,int mod){
		mod=(mod?mod:LONG_LONG_MAX);
		x=(p?(x%mod):1);
		int t=1;
		while(p>1){
			if(p&1) t=(t*x)%mod;
			x=(x*x)%mod;
			p>>=1;
		}
		return (x*t)%mod;
	}
	int fct[N],infct[N];
	pair<int,int>a[N];
	map<int,int>mp,mp1;
	inline int C(int n,int m){
		if(n<m) return 0;
		return (((fct[n]*infct[n-m])%mod)*infct[m])%mod;
	}
	signed main(){
		int n=qr;
		fct[0]=1;
		for(int i=1;i<=n;i++) fct[i]=(fct[i-1]*i)%mod;
		infct[n]=qpow(fct[n],mod-2,mod);
		for(int i=n-1;i>=0;i--) infct[i]=(infct[i+1]*(i+1))%mod;
		for(int i=1;i<=n;i++) mp[qr]++;
		for(auto p:mp) mp1[p.second]++;
		int m=0;
		for(auto p:mp1) a[++m]=p;
		for(int i=1;i<=n;i++){
			int ans=0;
			for(int j=1;j<=m;j++) (ans+=(C(n,i)-C(n-a[j].first,i)+mod)%mod*a[j].second%mod)%=mod;
			(ans*=qpow(C(n,i),mod-2,mod))%=mod;
			qwe(ans);
		}
		return 0;
	}
}
signed main(){return FreedomKing_qwq::main();}
```

---

## 作者：Kreado (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc215_g)。

水题。

### 思路

显然答案和颜色种类没有关系，将 $c_i$ 离散化，记 $V=\max\{c_i\}$，**考虑每个颜色出现次数对答案的贡献**，不妨记 $col_i$  表示颜色 $i$ 在序列里出现的次数，那么选 $k$ 个糖果的期望值就为 $\sum_{i=1}^V\dfrac{\binom{n}{k}-\binom{n-col_i}{k}}{\binom{n}{k}}$，直接求是 $O(n^2)$ 的。

注意到 $col_i$ 有很多重复的，最坏情况下有 $col=\{1,2,\cdots,k\}$，显然有 $\dfrac{k(k-1)}{2}\le n$，因此本质不同 $col_i$ 只有 $\Theta(\sqrt n)$ 量级，那么总时间复杂度就是 $O(n\sqrt n)$ 的。

由于 $n$ 的数据范围比较小，所以我们可以使用 `map`，时间复杂度 $O(n\sqrt {n\log n})$。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const ll Mod=998244353;

template<typename T>
inline T up(T x){
	return (x%Mod+Mod)%Mod;
}

inline ll ksm(ll a,ll b,ll mod){
	ll z=1;
	while(b){
		if(b&1) z=z*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return z;
}
inline ll getInv(ll a,ll mod){
	return ksm(a,mod-2,mod);
}

const ll Maxn=1e5+7;
ll n,k,a[Maxn],fac[Maxn],Inv[Maxn],ans;

inline void init(ll N){
	fac[0]=1;
	for(ll i=1;i<=N;i++) fac[i]=fac[i-1]*i%Mod;
	Inv[N]=getInv(fac[N],Mod);
	for(ll i=N-1;~i;i--) Inv[i]=Inv[i+1]*(i+1)%Mod;
}
inline ll Binom(ll x,ll y){
	if(y>x) return 0;
	return fac[x]*Inv[x-y]%Mod*Inv[y]%Mod;
}

map<ll,int>col,lmx;  

int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++) scanf("%lld",&a[i]),col[a[i]]++;
	for(auto i:col) lmx[i.second]++;
	init(Maxn-3);
	for(k=1;k<=n;k++){
		ans=0;
		for(auto i:lmx){
			ll res=up(Binom(n,k)-Binom(n-i.first,k));res=res*i.second%Mod;
			ans=up(ans+res*getInv(Binom(n,k),Mod)%Mod);
		}
		printf("%lld\n",ans);
	}
	
	return 0;
}



```


---

## 作者：syysongyuyang (赞：0)

拆贡献入门题。

注意到要求期望，考虑拆贡献。将贡献拆成每种颜色的贡献。

对每种颜色分别考虑。假设当前要取 $k$ 个，则对于颜色 $i$，贡献为 $p_i \times w_i$，$p_i$ 为抽到的 $k$ 个有颜色 $i$ 的概率，$w_i$ 为权。这里的 $w_i=1$。

则 $E=\sum\limits_{i=1}^n p_i$。考虑怎么求出颜色 $i$ 的出现概率。简单容斥一下，随便选的方案数是 $\binom {n} {k}$，一个颜色 $i$ 都没选到的方案数是 $\binom {n-c_i} {k}$。则 $p_i = \frac {\binom {n} {k}-\binom {n-c_i} {k}} {\binom {n} {k}}$。

注意到我们要对 $k \in [1,n]$ 求出答案。对于这类问题，常用的套路是考虑根号分治或者从上次的状态继承，考虑根号或者是多只 $\log$ 的算法。首先我们注意到可以将 $c_i$ 相同的颜色合并计算，这样答案就变成了 $E=\sum\limits_{i=1}^{tot}  \frac {\binom {n} {k}-\binom {n-c_i} {k}} {\binom {n} {k}} \times cnt_i$。根据 [【UR #26】石子合并](https://uoj.ac/problem/821)，可以注意到一个经典结论：实际上不同的 $c_i$ 只有 $\Theta (\sqrt n)$ 量级。处理出所有不同的颜色种类数暴力计算即可，时间复杂度 $\Theta (n \sqrt n)$。

---

## 作者：WaterSun (赞：0)

# 思路

定义 $vis_i$ 表示数 $i$ 在序列中出现的次数。如果我们选出 $k$ 个数，答案就是（其中 $m$ 表示 $\max(c_i)$）：

$$
\sum_{i = 1}^m\frac{\binom{n}{x} - \binom{n - vis_i}{k}}{\binom{n}{x}}
$$

显然，我们只枚举序列中存在的元素，时间复杂度 $\Theta(n^2)$，过不了，考虑优化。

不难发现，对于答案的贡献与其权值无关，之和出现的次数有关。那么，对于所有满足 $i \neq j \wedge vis_i = vis_j$ 的元素，对于答案的贡献都是一样的。因此将其看作一种元素考虑。

答案就转变为了（$p$ 为压缩后的序列大小，$a$ 为压缩后的序列）：

$$
\sum_{i = 1}^p(cnt_i \times \frac{\binom{n}{k} - \binom{n - vis_{a_i}}{k}}{\binom{n}{k}})
$$

时间复杂度为 $\Theta(np)$，因为在最坏情况下，出现次数分别是：$1,2,3,\dots$。所以 $p$ 是 $\Theta(\sqrt n)$ 级别的。

因此，时间复杂度为 $\Theta(n \sqrt n)$。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 5e4 + 10,mod = 998244353;
int n,m;
int arr[N],brr[N],mul[N],inv[N];
map<int,int> vis,mp;

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline int exgcd(int a,int b,int &x,int &y){
	if (!b){
		x = 1;
		y = 0;
		return a;
	}
	int d = exgcd(b,a % b,y,x);
	y = y - a / b * x;
	return d;
}

inline void init(){
	mul[0] = 1;
	for (re int i = 1;i <= n;i++) mul[i] = mul[i - 1] * i % mod;
	for (re int i = 0;i <= n;i++){
		int a = mul[i],p = mod,x,y;
		exgcd(a,p,x,y);
		inv[i] = (x % mod + mod) % mod;
	}
}

inline int C(int n,int m){
	if (n < m) return 0;
	return mul[n] * inv[n - m] % mod * inv[m] % mod;
}

signed main(){
	n = read();
	init();
	for (re int i = 1;i <= n;i++){
		int x;
		x = read();
		vis[x]++;
	}
	for (auto it = vis.begin();it != vis.end();it++) mp[it -> second]++;
	for (auto it = mp.begin();it != mp.end();it++){
		m++;
		arr[m] = (it -> first);
		brr[m] = (it -> second);
	}
	for (re int i = 1;i <= n;i++){
		int ans = 0;
		for (re int j = 1;j <= m;j++) ans = (ans + ((C(n,i) - C(n - arr[j],i)) % mod + mod) % mod * brr[j] % mod) % mod;
		int a = C(n,i),p = mod,x,y;
		exgcd(a,p,x,y);
		int iv = (x % mod + mod) % mod;
		printf("%lld\n",ans * iv % mod);
	}
	return 0;
}
```

---

## 作者：WRuperD (赞：0)

显然这题只与单种颜色数量有关，与到底是那种颜色无关。所以靠虑直接预处理出数组 $b_i$ 为第 $i$ 种颜色有多少个糖果。设总共有 $N$ 个糖果。对于选择 $x$ 个糖果，则答案为 

$$ {\sum\limits_{i=1}\limits^{N}{{N\choose x} - {N-b_i \choose x}}} \over {N\choose x}$$

但这东西是 $n^2$ 的。靠虑最多出现 $\sqrt{n}$ 种不同的 $b_i$，靠虑把相同的 $b_i$ 合并起来算即可。复杂度 $O(n\sqrt{n})$。

---

