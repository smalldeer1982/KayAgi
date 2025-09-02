# [ARC167B] Product of Divisors

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc167/tasks/arc167_b

$ A^{B} $ の正の約数の総積は $ A $ で最大何回割り切れますか。

制約から割り切れる回数が有限回であることが示せるので、その答えを $ 998244353 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 2\leq\ A\leq\ 10^{12} $
- $ 0\leq\ B\leq\ 10^{18} $
- 入力は全て整数
 
### Sample Explanation 1

$ A^{B}=8 $ の正の約数は $ 1,2,4,8 $ で、その総積は $ 64 $ となります。 $ 64 $ は $ 2 $ で $ 6 $ 回割り切れるので、$ 6 $ を出力します。

## 样例 #1

### 输入

```
2 3```

### 输出

```
6```

## 样例 #2

### 输入

```
924 167```

### 输出

```
867046524```

## 样例 #3

### 输入

```
167167167167 0```

### 输出

```
0```

# 题解

## 作者：樱雪喵 (赞：11)

大家快看，这里有一个试图在质因数分解后的指数上推点式子，于是卡 B 1h 的樱雪喵 /cf


## Description

给定 $A,B$，问 $A^B$ 所有因数的积不断除以 $A$，最多能除几次。

$A\le 10^{12},B\le 10^{18}$。

## Solution

发现因数是成对的，对每个因数都有 $x\times \frac{A^B}{x}=A^B$，设 $A^B$ 的因数个数为 $n$。

如果 $n$ 是偶数，把因数两两分成 $\frac{n}{2}$ 对，每对的积都是 $A^B$，$A^B$ 的因数之积就是 $A^{(Bn/2)}$，答案是 $\frac{Bn}{2}$。

如果是奇数，说明 $A^B$ 是完全平方数，我们把这个数单独拆出来考虑，$A^B$ 的因数之积是 $A^{B(n-1)/2}\times \sqrt{A^B}$，答案也是这个。

注意完全平方数分为 $A$ 本身是完全平方数和 $B$ 是偶数两种情况。

于是就做完了，时间复杂度瓶颈在质因数分解，$O(\sqrt{A})$。

```cpp
bool flag=0;
signed main()
{
    A=read(),B=read();
    if((int)sqrt((long long)A)*(int)sqrt((long long)A)==A) flag=1;
    for(int i=2;i*i<=A;i++)
    {
        if(A%i==0)
        {
            a[++cnt]=i;
            while(A%i==0) b[cnt]++,A/=i;
        }
    }
    if(A>1) b[++cnt]=1;
    int res=1;
    for(int i=1;i<=cnt;i++) res=res*(b[i]*B%mod+1)%mod;
    if(B%2==0||flag) res=(res+mod-1)%mod;
    res=res*qpow(2,mod-2)%mod*B%mod;
    if(B%2==0||flag) res=(res+B/2)%mod;
    cout<<(long long)res<<endl;
    return 0;
}
```

---

## 作者：大眼仔Happy (赞：4)

~~赛后两分钟调出来是真的想死。~~

[题目传送门](https://www.luogu.com.cn/problem/AT_arc167_b)

## 分析

先将 $A$ 分解，$A=p_{1}^{m_1}p_{2}^{m_2}\cdots p_{k}^{m_k}$，则有 $A^B=(p_{1}^{m_1}p_{2}^{m_2}\cdots p_{k}^{m_k})^B=p_{1}^{m_1\times B}p_{2}^{m_2\times B}\cdots p_{k}^{m_k\times B}$。

考虑求出每个质因数 $p_i$ 对**乘积**贡献多少次。首先得到枚举其他质因数的方案为 $\prod_{j\ne i}(m_jB+1)$，而枚举这个质因数的次数的范围为 $0\sim m_i B$，所以答案应该为：

$$(0+1+\cdots+m_iB)\prod_{j\ne i}(m_jB+1)=\dfrac{m_iB\prod(m_jB+1)}{2}$$

这时 $A$ 中原本就有 $m_i$，所以最后的式子为 $Ans=\lfloor\dfrac{B}{2}\prod(m_iB+1)\rfloor$。

## 坑点

首先这个式子是向下取整的（如果忽略掉这个，你自信的写完代码后会得到 46AC+21WA 的好成绩）

然后就是奇偶性的问题了。由于向下取整则需要判断分子的奇偶性，奇偶性判断需要在取模前面判断，即不能拿取模之后的 $B$ 值判断。（这里我人傻了，获得了 66AC+1WA 的好成绩，然后没能在赛时 AC）

代码过丑，不便观看
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod=998244353,inv=499122177;
ll inline read()
{
	ll num=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){num=(num<<3)+(num<<1)+(ch^48);ch=getchar();}
	return num*f;
}
ll a,b,B,m,flag,ans;
void solve(ll x)
{
	ll i=2;
	while(i*i<=x)
	{
		ll num=0;
		while(!(x%i))x/=i,num++;
		m=(num*b+1)%mod*m%mod;//mi=num*b <-- num*B
		if((num&1)&&(B&1))flag=0;
		i=i+1+(i!=2);
	}
	if(x>1)m=m*(b+1)%mod,flag=0;
}
int main(){
	a=read();B=b=read();flag=B&1;m=b%=mod;
	solve(a);
	ans=(m-flag)*inv%mod;
	printf("%lld",(ans%mod+mod)%mod);
	return 0;
}
```


---

## 作者：STAR_czy (赞：2)

## 题目大意：
输入 $A$ 和 $B$，求 $A^{B}$ 的所有正因数的乘积最多能被 $A$ 整除多少次。

# 思路：
设 $A^{B}$ 为 $n$，有 $m$ 个不同的质因数，$n$ 分解质因数后 $n=\prod_{i=1}^m p_i^{a_i}$，$A$ 分解质因数后为 $A=\prod_{i=1}^m p_i^{b_i}$，即 $n$ 的有 $a_i$ 个质因数 $p_i$，满足对于任意整数 $1 \leq i \leq n$，$a_i=m \times b_i$。

因为 $n$ 的质因数 $p_i$ 在每一个因数中可以为 $p_i$ 的 $0$ 到 $a_i$ 中任意数次方，也就是有 $a_i+1$ 中选择，每个 $p_i$ 的选择数量乘起来即可，所以 $n$ 有 $\prod_{i=1}^m (a_i+1)$ 个因数。设因数个数为 $k$。

对于任意整数 $1 \leq i \leq n$，$n$ 有 $k \times \frac{1}{a_i+1}$ 个因数是只有 $0$ 个因数 $p_i$ 的，有 $k \times \frac{1}{a_i+1}$ 个因数是只有 $1$ 个因数 $p_i$ 的，有 $k \times \frac{1}{a_i+1}$ 个因数是只有 $2$ 个因数 $p_i$ 的，一直到有 $k \times \frac{1}{a_i+1}$ 个因数是只有 $1$ 个因数 $p_i$ 的，有 $k \times \frac{1}{a_i+1}$ 个因数是只有 $a_i$ 个因数 $p_i$ 的，也就是说，$n$ 的所有因数乘积中因数 $p_i$ 的个数为 $k \times \frac{1}{a_i+1} \times \frac{a_i\times(1+a_i)}{2}$，化简得 $\frac{k\times a_i}{2}$，即 $p_i^{\frac{k\times B \times b_i}{2}}$，设每个因数的乘积 $p_i^{\frac{k\times B \times b_i}{2}}$ 为 $m$。

但是，答案是输出 $n$ 能被多少个 $A$ 整除，也就是求 $A$ 的多少次方等于 $n$，即 $\log_{A}{m}=\log_{\prod_{i=1}^m p_i^{b_i}}{\prod_{i=1}^m p_i^{\frac{k\times B \times b_i}{2}}}=\frac{k \times B}{2}$。

最后还要模一个 $998244353$。由于这个式子要除以一个 $2$，因此为了最后除法方便，可以将模数设为 $998244353 \times 2$，这样答案的因数 $2$ 不会被模掉。

# 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
//注意开long long
using namespace std;
const int maxn=2e5+10,mod=998244353<<1;
inline int read(){
	int c,w=0,n=0;
	while((c=getchar())<'0'||'9'<c) w=c=='-';
	do n=n*10+c-'0';while('0'<=(c=getchar())&&c<='9');
	return w?-n:n;
}
inline int write(int n){
	if(n<0) putchar('-'),n=-n;
	if(n>9) write(n/10);
	putchar(n%10+'0');
	return n;
}

int n=read(),m=read()%mod/*m可以取模*/,sum=m;

signed main(){
	for(int i=2;i*i<=n;++i){
		int cnt=0;
		while(n%i==0) n/=i,++cnt;
		(sum*=cnt*m%mod+1)%=mod;//求因数个数
	}
	if(n>1) (sum*=m+1)%=mod;
	write(sum%mod/2);//输出
	return 0;
}
```

---

## 作者：_sunkuangzheng_ (赞：2)

这题真不好评价。

$\textbf{1.1 Describtion}$

给定整数 $a,b(a \le 10^{12},b \le 10^{18})$，问 $a^b$ 所有正约数的乘积能被 $a$ 整除几次，模 $998244353$。

$\textbf{1.2 Hints}$

- $\textbf{1.2.1 Hint 1}$

当 $a$ 是质数时，答案是什么？

- $\textbf{1.2.2 Hint 2}$

当 $a$ 不是质数时，进行质因数分解，转化为上面的情况。

$\textbf{1.2 Solution}$

先考虑 $a$ 是质数时的答案。显然此时 $a^b$ 的约数只有 $a^0,a^1,a^2,\ldots,a^{b-1},a^b$，他们的乘积是 $a^{\frac{b(b+1)}{2}}$，可以被 $a$ 整除 $\dfrac{b(b+1)}{2}$ 次。

当 $a$ 不是质数时，设 $a = \prod\limits_{i=1}^kp_i^{c_i}$，那么 $a^b = \prod\limits_{i=1}^kp_i^{bc_i}$，则共有 $\prod\limits_{i=1}^k(bc_i+1)$ 个约数。我们设一个约数表示成 $x = \prod\limits_{i=1}^kp_i^{d_i}$，钦定当 $d_1 = m$ 时，共有 $\prod\limits_{i=2}^k(bc_i+1)$ 个约数。那么如果我们计算所有约数中，质数 $p_1$ 的次幂和，显然这个值等于 $\dfrac{bc_1(bc_1+1)}{2} \times \prod\limits_{i=2}^k(bc_i+1) = \dfrac{bc_1\prod\limits_{i=1}^k(bc_i+1)}{2}$。

此时计算能被 $p_1$ 整除多少次就很简单了，显然是上面的值除以 $c_1$，也即 $\dfrac{b\prod\limits_{i=1}^k(bc_i+1)}{2}$。

如果你直接照着上面的式子写代码，会发现 WA $21$ 个点。这是因为，我们的所有运算是在模 $998244353$ 下进行的，而上式的值不一定是整数，**不能直接乘以 $2$ 的逆元，需要向下取整**。如何做模意义下的向下取整？在本题里是简单的，我们只需要判断，做除法前，积含不含偶数因子。如果不含，那么 $-1$ 后再乘 $2$ 的逆元。

赛时代码写的很丑，但还是放上来吧 qwq。

[code](https://atcoder.jp/contests/arc167/submissions/46637601)。

---

## 作者：SError_ (赞：1)

求一个最大的 $x$，使得 $\displaystyle A^x\mid \prod_{i|A^B}i$.

答案模 $998244353$.

$A\le 10^{12}$，$B\le 10^{18}$.

---

对 $A$ 分解质因数 $A=p_1^{c_1}p_2^{c_2}\dots p_m^{c_m}$.

对于每个质因子 $p_i$，考虑统计 $p_i$ 在 $A^B$ 中的次数 $cnt_i$，答案即 $\displaystyle\min\lfloor\frac{cnt_i}{c_i}\rfloor$.

现在把 $cnt_i$ 求出来。

由于 $A^B=p_1^{Bc_1}p_2^{Bc_2}\dots p_m^{Bc_m}$，枚举 $p_i$ 处的指数 $x$，显然对于一个固定的 $x$ 有 $\displaystyle\prod_{j\not=i}(Bc_j+1)$ 种方案。

也就是说 $cnt_i$ 的值就是

$$\sum_{x=0}^{Bc_i}x\cdot\prod_{j\not=i}(Bc_j+1)$$

将这个式子对 $c_i$ 下取整：

$$\large\Big\lfloor\frac{\frac{Bc_i(Bc_i+1)}{2}\cdot\prod_{j\not=i}(Bc_j+1)}{c_i}\Big\rfloor$$

令 $\displaystyle S=\prod_{i=1}^{m} (Bc_i+1)$:

$$=\Big\lfloor\frac{Bc_i\cdot S}{2c_i}\Big\rfloor=\Big\lfloor\frac{BS}{2}\Big\rfloor$$

我们发现对于每个 $p_i$ 都可以变成这个定值，可以直接把 $\min$ 去掉。

然后还要处理一个下取整，分 $B$ 和 $S$ 的奇偶性讨论：

- 当 $B$ 为偶数或 $S$ 为偶数时（此时 $S$ 为偶数等价于 $B$ 为奇数且存在一个 $c_i$ 为奇数），可以直接去掉下取整，把 $2$ 的逆元代进去直接乘。

- 当 $B$ 为奇数且 $S$ 为奇数时（即所有 $c_i$ 为奇数），可以维护一堆形如 $2x+1$ 的数，其除以 $2$（向下取整）的值为 $x$.

两数的乘积是 $(2x+1)(2y+1)=2(2xy+x+y)+1$，直接计算即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define P 998244353
using namespace std;
int A,B;
int c[20],cnt;
struct node{
	int x;
	node operator*(const node &t)const{
		return (node){(int)(2*x*t.x%P+x+t.x)%P};
	}
};
void solve(){
	cin>>A>>B;
	for(int i=2;1ll*i*i<=A;i++){
		if(A%i==0){
			cnt++;
			while(A%i==0)c[cnt]++,A/=i;
		}
	}
	if(A>1)c[++cnt]=1;
	bool flag=true;
	int B2=B%2;
	for(int i=1;i<=cnt;i++){
		if((!B2)||(c[i]&1)){flag=false;break;}
	}
	if(!flag){
		B%=P;
		int ans=B*((P+1)>>1)%P;
		for(int i=1;i<=cnt;i++)
			ans=ans*(1ll*B*c[i]%P+1)%P;
		printf("%lld\n",ans);
		return;
	}
	node ans=(node){(int)(B/2%P)};
	B%=P;
	for(int i=1;i<=cnt;i++)
		ans=ans*(node){(int)1ll*c[i]/2*B%P};
	printf("%lld\n",ans.x);
}
signed main(){
	int T=1;
	while(T--)solve();
	
	return 0;
}
```

---

## 作者：AlexandreLea (赞：1)

## 题目大意

给定 $A,B$，求 $A^B$ 的所有因子的乘积可以整除多少个 $A$。结果对 $998244353$ 取模。

$2\le A\le 10^{12},0\le B\le10^{18}$，且 $A,B$ 是整数。

## 题目思路

**十分感谢[蒟蒻·廖子阳](https://www.luogu.com.cn/user/539211)同志，他完成了本篇题解 $\mathbf{80\%}$ 的内容。**

我们可以先想一想特殊情况。当 $A$ 是一个质数，那么 $A^B$ 的所有因子就是 $A^1,A^2,\cdots,A^B$ 那么我们就可以有答案 $(B\cdot(B+1)/2)\bmod M$ 其中 $M=998244353$。

然而不幸的是质数的情况似乎有点少……不过我们可以通过对 $A$ 进行唯一分解：

$$A=\prod p_{A,i}^{e_{p_{A,i}}}$$

那么我们就可以得到它的因子个数为

$$\prod (e_{P_{A,i}}+1)$$

那么我们可以对 $A^B$ 做唯一分解定理

$$A^B=\prod p_{A,i}^{B\cdot e_{p_{A,i}}}$$

那么我们就可以得到 $A^B$ 的因子个数为

$$\prod (Be_{P_{A,i}}+1)$$

我们把这个数记作 $T$，即 $T=\prod (Be_{P_{A,i}}+1)$，而后……怎么办呢？

我们可以把这 $T$ 个数排列出来（这里 $f$ 代表 $A^B$ 的某个因子）：

$$1\ f_1\ f_2\ \cdots\ \frac{A^B}{f_2}\ \frac{A^B}{f_1}\ A^B$$

可以看到，假若 $T$ 是一个偶数的话，我们就有

$$\prod_{f_k| A^B} f_k=(A^B)^{T/2}$$

那么我们就可以找到答案是 ~~（我没有别的意思！我没有！）~~

$$\frac{BT}{2}\bmod M$$

但是如果 $T$ 不是一个偶数，即 $A^B$ 是某个整数的平方，我们就得考虑一下中间的那个数字造成的影响，我们可以把如上的数列重写一遍

$$1\ f_1\ f_2\ \cdots\ A^{B/2}\ \cdots\ \frac{A^B}{f_2}\ \frac{A^B}{f_1}\ A^B$$

那么答案就是

$$\left(\frac{B(T-1)}{2}+\left\lfloor\frac{B}{2}\right\rfloor\right)\bmod M$$

最后的一项是中间的根号贡献的。

需要注意的是你需要取逆元！取逆元需要开 `__int128_t`！另外判定完全平方数不能通过根号的平方！但是下取整不需要！

代码如下。

```cpp
#include <iostream>
#include <cmath>
#define int __int128_t
using namespace std;
const int MOD=998244353;
int sqr(int x){
    return x*x;
}
int pow(int a,int b,int p){
    int ans=1;
    for(;b;b>>=1,a=a*a%p) if(b%2==1) ans=ans*a%p;
    return ans;
}
int inv(int x){
    return pow(x,MOD-2,MOD);
}
signed main(){
    long long v;
    int a,aa,b,tot=1,inv2=inv(2);
    bool flg=false;
    cin>>v,aa=a=v,cin>>v,b=v;
    for(int i=2;i*i<=aa;i++){
        if(a%i==0){
            int cnt=0;
            while(a%i==0) cnt++,a/=i;
            tot*=(cnt*b+1),tot%=MOD;
        }
        if(i*i==aa) flg=true;
    }
    if(a!=1) tot*=(b+1),tot%=MOD;
    if(flg||b%2==0) v=((((tot-1+MOD)*inv2%MOD*b%MOD)%MOD+(b/2)%MOD)%MOD),cout<<v<<endl;
    else v=((tot*inv2%MOD*b%MOD)%MOD),cout<<(long long)v<<endl;
    return 0;
}
```

**再次感谢[蒟蒻·廖子阳](https://www.luogu.com.cn/user/539211)同志!**

**EOF**

---

## 作者：LYY_yyyy (赞：1)

下文中除法均为下取整。

设 $A^B$ 的正因数个数为 $cnt$，答案为 $ans$。显然地，我们有初步结论：$ans=cnt\div2\times B$。然后我们发现它有问题，就是在 $A^B$ 为完全平方数的时候，$cnt$ 为奇数。多出来的那个数给答案有 $B\div2$ 的贡献。记 $flag$ 当 $A^B$ 为完全平方数时为 $1$，否则为 $0$。于是，我们完善一下式子：
$$
ans=cnt\div2\times B+flag\times(B\div2)
$$
在实现时我们发现当 $A$ 是完全平方数或者 $B$ 为偶数时 $A^B$ 是完全平方数，代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int mod=998244353;
long long a,b;
int cnt[1000010];int tot;
bool flag=0;
int qpow(int a,int b)
{
	int x=1,y=a;
	while(b)
	{
		if(b&1) x=(x*1ll*y)%mod;
		y=(y*1ll*y)%mod;
		b>>=1;
	}
	return x;
}
signed main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	bool flag1=0;
	cin>>a>>b;if(b%2==0) flag1=1;
	long long o=b/2;b%=mod;
	long long p=a;int aa=sqrt(a);
	if(aa*1ll*aa==a) flag=1;
	for(int i=2;i<=sqrt(a);i++)
	{
		if(p%i==0) 
		{
			tot++;
			while(p%i==0) p/=i,cnt[tot]++;
		}
	}
	if(p>1) cnt[++tot]++;
	int ccnt=1;
	for(int i=1;i<=tot;i++)
	{
		ccnt=(ccnt*1ll*((cnt[i]*1ll*b+1)%mod))%mod;
	}
	if(flag||flag1) ccnt=(ccnt-1+mod)%mod;
	ccnt=((ccnt*1ll*qpow(2,mod-2))%mod*1ll*b)%mod;
	if(flag||flag1) ccnt=(ccnt+o)%mod;
	cout<<ccnt;
	return 0;
}
```


---

## 作者：escapist404 (赞：1)

求 $A^{B}$ 的所有正因子的乘积最多能被 $A$ 整除多少次，答案模 $998 244 353$。$2 \le A \le {10}^{12}$，$0 \le B \le {10}^{18}$。

---

考虑在质因子上进行一个式子的推。

令 $A$ 的唯一分解为 ${p_1}^{\alpha_1} {p_2}^{\alpha 2} \cdots {p_k}^{\alpha_k}$，则 $A_B$ 的唯一分解为 ${p_1}^{B \cdot \alpha_1} {p_2}^{B \cdot \alpha 2} \cdots {p_k}^{B \cdot \alpha_k}$。

不失一般性地取某一个项 ${p_i}^{B \cdot \alpha_i}$。$A^B$ 的所有因子的 $p_i$ 上的次数为 $0 \sim B \cdot \alpha_i$。只考虑这一部分，这些因子乘积关于 $p_i$ 的次数为 $\frac{B \cdot \alpha_i \cdot \left( B \cdot \alpha_i + 1 \right)}{2}$。对于某一个次数，剩下的所有 $p_i$ 都有 $B \cdot \alpha_i + 1$ 种选法。所有因子的乘积的唯一分解中，$p_i$ 的次数为：

$$
\frac{B \cdot \alpha_i \cdot \left( B \cdot \alpha_i + 1 \right)}{2} \prod_{j \neq i} \left( B \cdot \alpha_j + 1 \right) = \frac{ B \cdot \alpha_i \cdot \prod \left( B \cdot \alpha_j + 1 \right) }{2}
$$

将其除以 $\alpha_i$，可以知道答案为 $\frac{ B \cdot \prod \left( B \cdot \alpha_j + 1 \right) }{2}$。

注意到：当且仅当 $B$ 为奇数，且所有 $\alpha_i$ 都为奇数时，分子为奇数所以除不尽，所以要下取整，答案为 $\frac{ B \cdot \prod \left( B \cdot \alpha_j + 1 \right) - 1}{2}$。

---

```cpp
#include <bits/stdc++.h>

int main() {
  using i64 = long long;

  i64 a, b;
  std::cin >> a >> b;

  std::map<int, int> divisor;
  i64 cur = a;
  for (i64 i = 2; i * i <= a; ++i) {
    if (cur % i == 0) {
      int count = 0;
      while (cur % i == 0) cur /= i, ++count;
      divisor[i] = count;
    }
  }

  if (cur != 1) ++divisor[cur];

  i64 answer = 1;
  const i64 p = 998'244'353;

  bool ok = true;
  for (auto& [prime, time] : divisor) {
    (answer *= (time * (b % p) % p + 1)) %= p;
    if (time % 2 == 1) ok = false;
  }

  (answer *= b % p) %= p;
  if (ok && (b % 2 == 1)) answer -= 1, ((answer %= p) += p) %= p;
  answer = answer % p * 499'122'177 % p;
  std::cout << answer << '\n';
}

```


---

## 作者：Kreado (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc167_b)。

## 思路

对于 $n$，有一个小于 $\sqrt n$ 的因子 $i$，那必定也有一个大于 $\sqrt n$ 的因子 $\dfrac{n}{i}$，两者相乘刚好等于 $n$，如果有因子 $i=\sqrt n$，那么还要算上它的贡献。

那么对于 $A^B$，它所有因子的乘积为 $A^{\lfloor(Bd(A^B))/2\rfloor}$（$d(x)$ 表示 $x$ 的正因子个数），也就说明，得到的数最多能被 $A$ 整除 $\lfloor(Bd(A^B))/2\rfloor$ 次。

将 $x$ 分解质因数 $x=\displaystyle\prod_{i=1}^k p_{i}^{\alpha_i}$，那么有 $d(x)=\displaystyle\prod_{i=1}^k (\alpha_i+1)$，$A^B$ 其实就是将 $A$ 的质因数个数翻了 $B$ 倍，也即是说 $d(A^B)=\displaystyle\prod_{i=1}^k(B\alpha_i+1)$。

但是我们发现在取模运算中不能整除，因此我们还要判断 $Bd(A^B)$ 是奇数还是偶数，这个很好判断，直接在算 $d(A^B)$ 的时候查看是否存在偶因子即可。

注意中间运算可能会超 `long long`。


```cpp
#include <bits/stdc++.h>
#define ll long long
#define lll __int128
using namespace std;
const ll Mod=998244353,inv2=499122177;
ll a,b;
ll ans=1;
bool flg=0;
inline void write(lll x){
	if(x>9) write(x/10);
	putchar('0'+x%10);
}
double lst;
bool ff=0;
inline lll up(lll x){
	return (x%Mod+Mod)%Mod;
}
inline ll d(ll x){
	lll z=1;
	for(ll i=2;i*i<=x;i++){
		if(!(x%i)){
			ll dd=0;
			while(!(x%i)) x/=i,dd++;
			lll xx=(lll)dd*b+1;
			if(xx%2==0) ff=1;
			z=z*xx%(Mod);
		}
	}	
	if(x!=1){
		ll xx=b+1;
		if(xx%2==0) ff=1;
		z=z*xx%(Mod);
	}
	if(b%2==0) ff=1;
	z=z*b%Mod;
	if(ff){
		z=z*inv2%Mod;
	}
	else{
		z=up(z-1)*inv2%Mod;
	}
	return z%(Mod);
}
int main(){
	scanf("%lld%lld",&a,&b);
	ans=d(a);
	cout<<ans;
	return 0;
} 
```


---

## 作者：Feyn (赞：0)

哈哈哈。

对 $A$ 分解质因数，得到 $A=\prod p_i^{c^i}$ 的形式，思考 $A^b$ 中每个质因子的数量，假设我们现在正在对第 $j$ 个质数进行分析。因数的本质是质因数的排列组合，而其它质因数的方案数是 $\prod\limits_{i\ne j}c_ib+1$，而当前质因数从 $1$ 到 $c_jb$ 都是可以取到的，于是 $A^b$ 所有因数的乘积中该质数的出现次数就是二者相乘。而既然要求 $A$ 在乘积中的出现次数我们就需要给上述的式子除上一个 $c_j$，结果如下：

$$
\begin{aligned}
&(\prod\limits_{i\ne j}c_ib+1)\times\dfrac{(c_jb+1)c_jb}{2}\times\dfrac{1}{c_j}\\
=&(\prod\limits_{i}c_ib+1)\times\dfrac{(c_jb+1)c_jb}{2\times(c_jb+1)}\times\dfrac{1}{c_j}\\
=&(\prod\limits_{i}c_ib+1)\times\dfrac{b}{2}
\end{aligned}
$$

然后发现柿子和 $j$ 没有关系了，也就是说所有质因数对数量的限制是相同的，只需要求出这个数就可以了。这是简单的。

但是需要注意如果分子是奇数那么答案要减去二分之一，但是需要注意如果分子是奇数那么答案要减去二分之一。

```cpp
#include<bits/stdc++.h>
// #define feyn
#define int long long
using namespace std;
const int mod=998244353;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}

int aa,bb,ans;

inline int qp(int s1,int s2){
    if(s2==0)return 1;
    int an=qp(s1,s2>>1);
    if(s2&1)return an*an%mod*s1%mod;
    else return an*an%mod;
}
vector<int>p;
void solve(){
    read(aa);read(bb);
    if(bb==0)return puts("0"),void();
    for(int pp=2;pp*pp<=aa;pp++){
        if(aa%pp)continue;
        int now=0;
        while(aa%pp==0)++now,aa/=pp;
        p.push_back(now);
    }
    if(aa>1)p.push_back(1);
    sort(p.begin(),p.end());
    int all=1;
    bool flag=bb%2==1;
    for(int i=0;i<(int)p.size();i++){
        int now=(bb%mod*p[i]+1)%mod;
        flag=flag&&(p[i]%2==0||bb%2==0);
        all=all*now%mod;
    }
    printf("%lld\n",(bb%mod*all%mod*qp(2,mod-2)-flag*qp(2,mod-2)+mod)%mod);
}

signed main(){
	
    #ifdef feyn
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif

    int test=1;
    while(test--)solve();

    return 0;
}
```

---

