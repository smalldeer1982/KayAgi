# 「SWTR-2」Magical Gates

## 题目背景

小 $\mathrm{A}$ 找到了一张藏宝图。

他顺着藏宝图上的路线来到了一扇古老的大门前，门上有六芒星的图案。

他把手轻轻地放在六芒星上……

霎时间，六芒星光芒大放，四周亮如白昼。

（新增一组大样例）

## 题目描述

小 $\mathrm{A}$ 面前出现了 $10^{1000}$ 扇门，每个门上都写着它自己的编号，分别为 $1,2,3,\dots,10^{1000}$。

这时，守门人小 $\mathrm{M}$  向小 $\mathrm{A}$ 走来。

“这些门，并不普通，它有魔力。”

“我会给你一些区间 $l,r$，请你求出区间 $[l,r]$ 里所有门的魔力值之**和**与魔力值之**积**。”

“因为结果可能很大，请你将结果 $mod\ p$。 ”

“如果你正确地回答了所有询问，你将会拥有这扇门后的所有宝藏。”

“哦，对了，一扇门的魔力值就是其在二进制下 $1$ 的个数。”

简单来说，记第 $i$ 扇门的魔力值为 $d_i$，给定的区间为 $[l,r]$，请求出：

$$\sum_{l}^{r}d_i\bmod\ p \quad \prod_{l}^{r}d_i\bmod\ p$$

由于门的数量实在太多，小 $\mathrm{A}$ 决定向你请求帮助。

## 说明/提示

---

### 样例说明

数据 $1$：

$$\sum_{3}^{7}d_i=2+1+2+2+3=10$$

$$\prod_{3}^{7}d_i=2\times 1\times 2\times 2\times 3=24$$

数据 $2$：

$$\sum_{1}^{10}d_i=1+1+2+1+2+2+3+1+2+2=17$$

$$\prod_{1}^{10}d_i=1\times 1\times 2\times 1\times 2\times 2\times 3\times 1\times 2\times 2=96$$

---

### 数据范围与约定

![](https://cdn.luogu.com.cn/upload/image_hosting/zv6ppsk4.png)

为了方便拿部分分，输入格式中的 $n$ 为**该测试点的编号**。

所有具有特殊性质的测试点一共 $31\%$。

对于 $100\%$ 的数据，有 $1\leq n\leq 27,1\leq T \leq 10,10^9 \leq p \leq 1.001\times 10^9,1\leq l\leq r\leq 10^{1000}$，**保证 $p$ 为质数**。

---

对于测试点 $1-20$，时限 $300ms$，剩下的 $7$ 个测试点时限 $2s$。

对于所有测试点，空间限制 $256MB$

---

“吱嘎”一声，封尘千年的大门缓缓打开。

刺眼的金光照了出来……

## 样例 #1

### 输入

```
7 1000000007 0
3 7
1 10
1 1048576
20180815 20180830
20180632 20180639
123456789 987654321
123456789987654321 123456789987654321123456789987654321```

### 输出

```
10 24
17 96
10485761 64327945
255 803716286
124 290111979
996409842 54001814
253678327 263109263```

# 题解

## 作者：Alex_Wei (赞：16)

$\color{#9400d3}T4.\ Magical\ Gates$

[$\color{#9400d3}\text{题面}$](https://www.luogu.org/problem/P5674)

$\color{#9400d3}\text{官方题解}$

欢迎爆踩 $\mathrm{std}$ ！

---

你感受过明天就要比赛却在比赛前一天发现有相似类型的题目的绝望吗？

双倍经验，如果你过了这道题目就一定能 $\mathrm{AC}$ 本题：[$P4317$](https://www.luogu.org/problem/P4317)

可以将本题看成该题的~~超级~~加强版（但是我们出题的时候并不知道有该题的存在）

---

本题主要考察数位 $\mathrm{DP}$

暴力分 $:10\%$

- 下文中所有的 $n$ 都代表该测试点的数据范围（可以理解为 $n=\max r$）

- 下文中所有的 $\log$ 以 $2$ 为底

- 下文中，$\binom{i}{j}$ 表示从 $j$ 个不同元素中选出 $i$ 个元素的方案数，即我们通常说的**组合数**，也可表示为 $C_{j}^{i}$，计算公式为 $\frac{j!}{i!(j-i)!}$

---

$Sol\ 1:10\%$

将题目所给代码直接复制 $+$ 暴力即可，可拿到前 $2$ 个测试点的分数，共 $10\%$

---

$Sol\ 2:20\%$

发现题目中所给 get 函数就是求：**一个数在二进制下有多少个 $1$**

对 $1-10^5$ 中的每个数 $\Theta(\log n)$ 预处理出有多少个 $1$

然后暴力回答询问即可

时间复杂度：$\Theta(n\log n)$

---

$Sol\ 3:35\%$

前置知识：乘法逆元和有理数取余，如果不会请先移步 [$P3811$](https://www.luogu.org/problem/P3811/) 和 [$P2613$](https://www.luogu.org/problem/P2613/)

$\Theta(1)$ 预处理出 $1-10^7$ 之间每个数有多少个 $1$，记录一下每个数的前缀和与前缀积，然后就可以 $\Theta(\log p)$ 回答每个询问

因为模数 $p$ 为质数，所以可以费马小定理求逆元

您可能会因为空间/时间被卡而拿不到应得的分数

时间复杂度：$\Theta(n+T\log p)=\Theta(n)$

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#pragma GCC optimize(3)
int t,d[10000005],q[10000005];
ll k[10000005],p,n;
ll ksm(ll a,ll b,ll p){ll ans=1;while(b){if(b&1)ans=(ans*a)%p;b>>=1,a=(a*a)%p;}return ans;}
int lowbit(int x){return x&-x;}
int main()
{
	cin>>t>>p>>n;
	for(int i=1;i<=1e7;i++)
		d[i]=d[i-lowbit(i)]+1;
	k[0]=1;
	for(int i=1;i<=1e7;i++)
		q[i]=q[i-1]+d[i],k[i]=k[i-1]*d[i]%p;
	while(t--){
		int l,r;
		cin>>l>>r;
		cout<<q[r]-q[l-1]<<" "<<k[r]*ksm(k[l-1],p-2,p)%p<<endl;//费马小定理求逆元 
	}
	return 0;
}
```

---

$Sol\ 4:31\%$

前置知识：高精，找规律，欧拉定理，如果不会请先移步 [$P5091$](https://www.luogu.org/problem/P5091)

找规律（或者推出结论），当 $l=1,r=2^k$ 时
$$\sum_{i=l}^{r}d_i=k\times 2^{k-1}+1$$

$$\prod_{i=l}^{r}d_i=\prod_{i=1}^{k}i^{\binom{i}{k}}$$

可以 $\Theta(\log^2 n)$ 预处理出 $\binom{i}{j}
$，再用快速幂 $\Theta(\log n\log\log  n)$ 计算上式

- 根据欧拉定理，因为 $\binom{i}{j}$ 在指数的位置上，且 $p$ 为素数，所以应对 $\varphi(p)=p-1$ 取模

时间复杂度 $\Theta(T(\log^2 n+\log n\log\log n))=\Theta(\log^2 n)$

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll t,p,p2,n,C[3333][3333];
string l,r;
int x[1005];
ll ksm(ll a,ll b){ll s=1,m=a;while(b){if(b&1)s=s*m%p;m=m*m%p;b>>=1;}return s;}
int main()
{
	cin>>t>>p>>n,p2=p-1;
	int N=n<15?70:3332;
	for(int i=1;i<N;i++)
		for(int j=0;j<=i;j++)
			if(j==0||i==j)C[i][j]=1;
			else C[i][j]=(C[i-1][j]+C[i-1][j-1])%p2;
	for(int i=0;i<t;i++){
		cin>>l>>r;
		int top=r.size(),bit=0;
		for(int j=0;j<r.size();j++)
			x[j]=r[r.size()-j-1]-'0';
		while(top){
			bit++;
			int tmp=0;
			for(int j=top-1;j>=0;j--)
				tmp=tmp*10+x[j],x[j]=tmp/2,tmp%=2;
			if(!x[top-1])top--;
		}
		bit--;
		int mul=1;
		for(int j=1;j<=bit;j++)
			mul=mul*ksm(j,C[bit][j])%p;
		cout<<(bit*ksm(2,bit-1)+1)%p<<" "<<mul<<endl;
	}
	return 0;
}
```

---

$Sol\ 5:54\%$

结合 $Sol\ 3$，$Sol\ 4$ 可拿到 $54\%$ 的高分

代码就不贴了

---

$Sol\ 6:100\%$

前置知识：高精，欧拉定理，数位 $\mathrm{DP}$

- 在下文中，$x_{(2)}$ 表示 $x$ 在二进制下表示的数

我们考虑数位 $\mathrm{DP}$

$dp_i$ 表示在 $[1,x]$ 中，**二进制下 $1$ 的个数为 $i$ 个的数有多少个**，然后将 $[1,r]$ 的结果减去 $[1,l)$ 的结果就是 $[l,r]$ 的结果，最后的答案就是 $\sum_{i=1}^{k}i\times dp_i$ 和 $\prod_{i=1}^{k}i^{dp_i}$

$\large Q1:$

如何计算区间 $[1,x]$ 的 $dp_i$？

$\large A1:$

- 设 $x_{(2)}$ 一共有 $k$ 位，**从左往右**遍历 $x_{(2)}$ 的每一位（只有可能为 $0$ 或 $1$）

- 如果该位为 $0$：跳过，不考虑

- **如果该位为 $1$** ：将该位为 $0$，**右边的位为任意值** 的情况讨论到答案中，这样保证了不会 **少计算/多计算/重复计算**，且在接下来的讨论中，**将该位的值看作为 $1$**

即设当前考虑到第 $j(j\in[1,k])$ 位（**从右往左数**），设该位**左边**共有 $cnt$ 个 $1$

对于所有 $dp_{i+cnt}(i\in[0,j))$，加上 $\binom{i}{j-1}$，最后再将 $cnt$ 加 $1$

- 遍历过所有位之后，还要将 $x_{(2)}$ 本身的答案算进去，即 $dp_{cnt}$ 加 $1$

### $Q2:$

为什么我按照 $A1$ 的方法做，却 $\color{red}\mathrm{WA}$ 掉了？

$\large A2:$

因为求积的 $dp_i$ 在指数的位置上，且 $p$ 为质数，所以该部分的 $dp_i$ 应对 $\varphi(p)=p-1$ 取模，而不是 $p$

同样的，上式 $dp_{i+cnt}(i\in[0,j))+\binom{i}{j-1}$ 中的 $\binom{i}{j-1}$ 也应对 $p-1$ 取模

$\large Q3:$

为什么我按照 $A1,A2$ 的方法做，却 $\color{#0000AA}\mathrm{TLE}$ 了？

$\large A3:$

可以先 $\Theta(\log^2 n)$ 预处理出 $\binom{i}{j}$ 对 $p$ 和 $p-1$ 取模的值，计算的时候就不需要再 $\Theta(\log n)$ 处理了（虽然先预处理出阶乘和阶乘逆元也不错，但是常数较大）

千万别小看这个 $\Theta(\log n)$，因为 $n$ 有可能到 $10^{1000}$，所以 $\max\log n\approx 1000\times \log(10)\approx3322$

$\large Q4:$

这个算法的时间复杂度是多少？

$\large A4:$

一次 $A1$ 操作时间复杂度 $\Theta(\log^2n)$，共 $2T$ 次操作且 $T$ 为常数，预处理 $\Theta(\log^2n)$，总时间复杂度 $\Theta(\log^2n)$

$\large Q5:$

说了这么多~~废话~~，赶紧把代码拿出来

$\large A5:$

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=3333; 
ll ksm(ll a,ll b,ll p){ll ans=1;while(b){if(b&1)ans=(ans*a)%p;b>>=1,a=(a*a)%p;}return ans;}
ll t,p,p2,n,k,add[N][N],mult[N][N],prod[N],sum[N];
bool bit[N];//二进制
string l,r;
void change(string s,bool minus)//将字符串转成二进制数，minus 为是否减 1（计算l时需要）
{
	k=0;
	int l=s.size()-1,p[N],high=l;
	for(int i=l;i>=0;i--)p[i]=s[l-i]-'0';//高精度
	if(minus){
		p[0]--;
		int pos=0;
		while(p[pos]<0)p[pos+1]--,p[pos]+=10,pos++;
		if(!p[high])high--;
	}
	while(high>=0){
		k++;
		int res=0;
		for(int i=high;i>=0;i--){
			res=res*10+p[i];
			p[i]=res/2;
			res%=2;
		}
		bit[k]=res;
		if(!p[high])high--;
	}
}
void solve()//一组数据
{
	memset(sum,0,sizeof(sum));
	memset(prod,0,sizeof(prod));
	cin>>l>>r;
	change(r,0);
	int cnt=0;
	for(int j=k;j>0;j--)
		if(bit[j]){
			for(int i=0;i<j;i++)
				sum[i+cnt]=(sum[i+cnt]+add[j-1][i])%p,
				prod[i+cnt]=(prod[i+cnt]+mult[j-1][i])%p2;
			cnt++;
		}
	sum[cnt]++,prod[cnt]++;//计算[1,r]
	change(l,1),cnt=0;
	for(int j=k;j>0;j--)
		if(bit[j]){
			for(int i=0;i<j;i++)
				sum[i+cnt]=(sum[i+cnt]-add[j-1][i]+p)%p,
				prod[i+cnt]=(prod[i+cnt]-mult[j-1][i]+p2)%p2;
			cnt++;
		}
	sum[cnt]=(sum[cnt]-1+p)%p,prod[cnt]=(prod[cnt]-1+p2)%p2;//减去[1,l)
}
void init()
{
	cin>>t>>p>>n,p2=p-1;
	int lim;
	if(n<18)lim=64;
	else if(n<21)lim=333;
	else lim=3333;//避免浪费时间和空间
	add[0][0]=mult[0][0]=1;
	for(int i=1;i<lim;i++){
		add[i][0]=mult[i][0]=1;
		for(int j=1;j<=i;j++){
			add[i][j]=(add[i-1][j]+add[i-1][j-1])%p;
			mult[i][j]=(mult[i-1][j]+mult[i-1][j-1])%p2;
		}
	}//预处理出组合数
}
int main()
{
	init();
	for(ll i=1;i<=t;++i){
		solve();
		ll ans=0;
		for(ll j=1;j<N;j++)
			ans=(ans+sum[j]*j)%p;
		cout<<ans<<" ";
		ans=1;
		for(ll j=1;j<N;j++)
			ans=(ans*ksm(j,prod[j],p))%p;//这里是对 p 取模，因为已经在算最终的答案了
		cout<<ans<<endl;
	}
    return 0;
}
```

当然，解法并不唯一，如果有更好的思路也欢迎大家在题解区发布！

如果题解有误请私信我，或在右侧评论区指出

---

## 作者：dead_X (赞：4)

## 题解
注意到 $p$ 很大而且一定是质数，所以可以直接差分。

差分之后直接将 $x$ 转为二进制表示，考虑快速求出 $[x2^t,(x+1)2^t)$ 的贡献。

显然我们可以通过组合数快速算出有几个 $\text{popcount}$ 为 $z$ 的数。

但是这样我们需要 $\log^2 n$ 次快速幂，时间复杂度为 $O(T\log^2 n\log\log n)$。

注意到我们可以将每个底数的指数累加起来，这样就只要 $\log n$ 次快速幂了。

~~其实你直接分三段或者四段预处理快速幂复杂度是一样的，但是那个东西常数太大了，过不去。~~

时间复杂度为 $O(T\log^2 n)$。
## 代码
```cpp
// Problem: P5674 【SWTR-02】Magical Gates
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5674
// Memory Limit: 256 MB
// Time Limit: 300000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//不回家了，我们去鸟巢！
#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int T=read(),p=read();
typedef unsigned long long ull;
typedef __uint128_t L;
struct FastMod {
    ull b, m;
    FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
    ull r(ull a) {
        ull q = (ull)((L(m) * a) >> 64);
        ull r = a - q * b; // can be proven that 0 <= r < 2*b
        return r >= b ? r - b : r;
    }
};
FastMod Z(p);
int qp(int x,int y)
{
	int res=1;
	for(int t=x; y; y>>=1,t=Z.r(1ll*t*t))
		if(y&1) res=Z.r(1ll*res*t);
	return res;
}
char s[1003];
int t[1003],pr[3503];
int C[3503][3503],D[3503][3503];
bool a[3503];
pair<int,int> solve(bool op)
{
	scanf("%s",s+1);
	int L=strlen(s+1),n=0;
	for(int i=1; i<=L; ++i) t[i]=s[L+1-i]&15;
	while(L)
	{
		a[n++]=t[1]&1;
		for(int i=L; i; --i)
			t[i-1]+=(t[i]&1)*10,t[i]>>=1;
		if(!t[L]) --L;
	}
	int sum=0,prod=1,d=0;
	for(int i=0; i<=n; ++i) pr[i]=0;
	for(int i=n-1; i>=0; d+=a[i--]) if(a[i])
		for(int j=0; j<=i; ++j) if(d+j)
			sum=Z.r(sum+1ll*C[i][j]*(d+j)),
			pr[d+j]+=D[i][j],
			(pr[d+j]>=p-1)&&(pr[d+j]-=p-1);
	for(int i=2; i<=n; ++i)
		prod=Z.r(1ll*prod*qp(i,pr[i]));
	if(op) sum=(sum+d)%p,prod=1ll*prod*d%p;
	return {sum,prod};
}
signed main()
{
	pair<int,int> A,B;
	for(int i=0; i<=3500; ++i)
	{
		C[i][0]=1;
		for(int j=1; j<=i; ++j)
			C[i][j]=C[i-1][j-1]+C[i-1][j],
			(C[i][j]>=p)&&(C[i][j]-=p);
	}
	for(int i=0; i<=3500; ++i)
	{
		D[i][0]=1;
		for(int j=1; j<=i; ++j)
			D[i][j]=D[i-1][j-1]+D[i-1][j],
			(D[i][j]>=p-1)&&(D[i][j]-=p-1);
	}
	for(read(); T--;)
		A=solve(0),B=solve(1),
		printf("%d %llu\n",(B.first+p-A.first)%p,
		Z.r(1ll*qp(A.second,p-2)*B.second));
	return 0;
}
```

---

## 作者：听取MLE声一片 (赞：1)

数位 dp。

首先把 $l-1$ 和 $r$ 转化为二进制，利用高精除单精即可。

按照套路分别求出 $l-1$ 和 $r$，然后利用相反数逆元处理。

定义 $dp_i$ 为包含 $i$ 个 $1$ 的数字个数，答案即为 $\begin{matrix} \sum\limits_{i=1}^{k} i\times dp_i\end{matrix}$ 和 $\begin{matrix} \prod\limits_{i=1}^{k} i^{dp_i} \end{matrix}$。

然后是数位 dp 常用套路。从高位向低位枚举，如果是 $0$ 就继续跑下一位。如果是 $1$，意为加上 $0$ 后面可以随便选，直接组合数即可。

注意指数取模，指数要对 $mod-1$ 取模。

代码：

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=3333;
int mod,T,id;
int ksm(int x,int y){
	int res=1;
	while(y){
		if(y&1)
			res=(res*x)%mod;
		x=(x*x)%mod;
		y>>=1;
	}
	return res;
}
int inv(int x){
	return ksm(x,mod-2);
}
int f[N],g[N];
int C(int x,int y){
	if(x<y)
		return 1;
	return (f[x]*g[x-y]%mod*g[y])%mod;
}
int t[N][N];
int a[N],b[N],ans1,ans2,dp[N],dp1[N];
char s1[N],s2[N];
stack<int>e;
int fa(int n){
	for(int i=1;i<=n;i++)
		if(a[i])
			return 1;
	return 0;
}
int fb(int m){
	for(int i=1;i<=m;i++)
		if(b[i])
			return 1;
	return 0;
}
void solve(){
	int x=0,p=e.size();
	while(!e.empty()){
		if(e.top()==0){
			e.pop();
			continue;
		}
		e.pop();
		int n=e.size();
		for(int i=0;i<=n;i++){
			dp[i+x]=(dp[i+x]+C(n,i))%mod;
			dp1[i+x]=(dp1[i+x]+t[n+1][i+1])%(mod-1);
		}
		x++;
	}
	dp[x]++;
	dp1[x]++;
	int res1=0,res2=1;
	for(int i=1;i<=p;i++){
		res1=(res1+i*dp[i])%mod;
		res2=(res2*ksm(i,dp1[i]))%mod;
	}
	ans1+=res1;
	ans2*=res2;
}
signed main()
{
	T=read(),mod=read(),id=read();
	f[0]=g[0]=1;
	for(int i=1;i<N;i++){
		f[i]=(f[i-1]*i)%mod;
		g[i]=inv(f[i]);
	}
	t[1][1]=1;
	for(int i=2;i<N;i++)
		for(int j=1;j<=i;j++)
			t[i][j]=(t[i-1][j-1]+t[i-1][j])%(mod-1);
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			if(t[i][j]==0)
				t[i][j]=1;
	while(T--){
		ans1=0,ans2=1;
		scanf("%s%s",s1+1,s2+1);
		int n=strlen(s1+1),m=strlen(s2+1);
		for(int i=1;i<=n;i++)
			a[i]=s1[i]-'0';
		for(int i=1;i<=m;i++)
			b[i]=s2[i]-'0';
		for(int i=n;i>=1;i--){
			if(a[i]!=0){
				a[i]--;
				break;
			}
			a[i]=9;
		}
		memset(dp,0,sizeof(dp));
		memset(dp1,0,sizeof(dp1));
		while(fa(n)){
			e.push(a[n]%2);
			int x=0;
			for(int i=1;i<=n;i++){
				a[i]+=x*10;
				x=a[i]%2;
				a[i]/=2;
			}
		}
		solve();
		ans1=-ans1;
		ans2=inv(ans2);
		memset(dp,0,sizeof(dp));
		memset(dp1,0,sizeof(dp1));
		while(fb(m)){
			e.push(b[m]%2);
			int x=0;
			for(int i=1;i<=m;i++){
				b[i]+=x*10;
				x=b[i]%2;
				b[i]/=2;
			}
		}
		solve();
		ans1=(ans1+mod)%mod;
		ans2=(ans2+mod)%mod;
		cout<<ans1<<' '<<ans2<<'\n';
	}
	return 0;
}

```

---

## 作者：St_john (赞：0)

提供一个**只用数位 DP** 的做法（不开 O2 最慢的点不到 500ms）。  


[这道题](https://www.luogu.com.cn/problem/P4317)算是超级弱化版了，没做过的可以先切了它。  

~~切了它，你就会发现这就是个板子。~~

依然是直接记忆化搜索，维护当前所在的最高位 $x$，当前的数字和 $sum$，是否为最高位 $top$，连前导 $0$ 都不用考虑。  

由于这道题的数据范围很大，开个高精度。  
$2^{4000}>10^{1000}$ 空间足够，对两个问题分别处理即可。  
注意 $sum=0$ 的情况就好。

然后这就是一个极其普通的数位 DP 板子了。

复杂度是 $O(\text{能过})$。

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long ll;
#define  il inline
#define pc putchar
#define Re register int
#define _for(i,a,b) for(register int i=(a);i<=(b);++i)
#define __for(i,a,b) for(register int i=(a);i>=(b);--i)
il int re(){
	int x=0;
	char ch=getchar();
	bool f=0;
	while(ch<'0'||ch>'9')
		f|=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
void pr(int x){
	if(x<0) x=-x,pc('-');
	if(x>9) pr(x/10);
	pc(x%10|48);
}
const int A=4e3+10,B=1e3+10,C=260;
int mod;
int f[A][A],g[A][A];
char s1[B],s2[B];

//以下为高精度的板子 
const int limit=1e4;
struct Int{
	int a[C],len;
	Int(){
		memset(a,0,sizeof(a));
		len=1;
	}
};
Int operator - (const Int &x,int y){
	Int z=x;
	z.a[1]-=y;
	_for(i,1,z.len)
		if(z.a[i]>=0)
			break;
		else{
			z.a[i]+=limit;
			--z.a[i+1];
		}
	while(z.len>1&&!z.a[z.len]) --z.len;
	return z;
}
Int operator / (const Int &x,int y){
	Int z=x;
	z.a[0]=0;
	__for(i,z.len,1){
		z.a[i-1]+=z.a[i]%y*limit;
		z.a[i]/=y;
	}
	z.a[0]/=limit;
	while(z.len>1&&!z.a[z.len]) --z.len;
	return z;
}
Int operator * (const Int &x,int y){
	Int z;
	z.len=x.len+1;
	_for(i,1,x.len){
		z.a[i]+=x.a[i]*y;
		z.a[i+1]=z.a[i]/limit;
		z.a[i]%=limit;
	}
	while(z.len>1&&!z.a[z.len]) --z.len;
	return z;
}
Int operator + (const Int &x,int y){
	Int z=x;
	++z.len;
	z.a[1]+=y;
	_for(i,1,x.len)
		if(z.a[i]>=limit){
			z.a[i+1]+=z.a[i]/limit;
			z.a[i]%=limit;
		}
		else break;
	while(z.len>1&&!z.a[z.len]) --z.len;
	return z;
}
bool check(const Int &x){
	return x.len>1||x.a[1]>0;
}
void print(const Int &x){
	pr(x.a[x.len]);
	__for(i,x.len-1,1)
		printf("%04d",x.a[i]);
	pc('\n');
}


int a[A][2],la0,la1;
il int calc1(int a,int b){//加法 
	return a+b>=mod?a+b-mod:a+b;
}
il int calc2(int a,int b){//减法 
	return a-b<0?a-b+mod:a-b;
}
il int pow(int a,int b){
	int c=1;
	while(b){
		if(b&1) c=(ll)c*a%mod;
		a=(ll)a*a%mod;
		b>>=1;
	}
	return c;
}
il int calc3(int a,int b){//除法 
	return (ll)a*pow(b,mod-2)%mod;
}



int dfs1(int x,int sum,int id,bool top){//处理问题1 
	if(!x)
		return sum;
	if(!top&&~f[x][sum]) return f[x][sum];
	int mx=top?a[x][id]:1;
	int ans=0;
	_for(i,0,mx)
		ans=calc1(ans,dfs1(x-1,sum+(i==1),id,top&&(i==mx))); 
		
	if(!top) f[x][sum]=ans;
	return ans;
}

int dfs2(int x,int sum,int id,bool top){//处理问题2 
	if(!x){
		if(!sum) return 1;
		else return sum;
	}
	if(!top&&~g[x][sum]) return g[x][sum];
	int mx=top?a[x][id]:1;
	int ans=1;
	_for(i,0,mx)
		ans=(ll)ans*dfs2(x-1,sum+(i==1),id,top&&(i==mx))%mod;
	if(!top) g[x][sum]=ans;
	return ans;
}

signed main(){
	int t=re();
	mod=re();
	int n=re();
	memset(f,-1,sizeof(f));
	memset(g,-1,sizeof(g));
	while(t--){
		Int l,r;
		scanf("%s%s",s1+1,s2+1);
		int l1=strlen(s1+1),l2=strlen(s2+1);
		_for(i,1,l1){
			l=l*10+(s1[i]^48);
		}
		_for(i,1,l2){
			r=r*10+(s2[i]^48);
		}
		//转成十进制 
		
		l=l-1;
		la0=0;
		while(check(l)){
			l=l/2;
			a[++la0][0]=l.a[0];
		}
		la1=0;
		while(check(r)){
			r=r/2;
			a[++la1][1]=r.a[0];
		}
		//转成二进制 
		
		
		pr(calc2(dfs1(la1,0,1,1),dfs1(la0,0,0,1))),pc(' ');
		pr(calc3(dfs2(la1,0,1,1),dfs2(la0,0,0,1))),pc('\n');
		
	}
	return 0;
}
```


---

## 作者：JackMerryYoung (赞：0)

# 前言

~~退役以后~~ 口胡一道还算不错的 DP. 

由一道我在 LOJ 做过的数位 DP 加强而来: [Link Here](https://www.luogu.com.cn/problem/P4317)

# 正文

看到 $10^{1000}$ 显然就是要在数位上操作，不然你咋做。

显然 20 pts 送的，直接预处理。然鹅想要拿到 100pts 就要祭出数位 DP.

我们考虑把它转换成二进制，最多 $1000 \times \log_2 10$ 位。

那么这个复杂度就差不多可以上数位 DP 了。设 $f_{i, j}$ 为 $[1, i]$ 区间内的，二进制表达下有且仅有 $j$ 位为 $1$ 的数字个数。

那么这就简单了。按照常规套路，数位 DP 要有区间，所以肯定是跟 $f_l, f_r$ 有关的两项相减。

令 $g_i$ 为 $[1, i]$ 区间内的数字的二进制表达中 $1$ 的个数总和，则有 $sum_i = \sum\limits_{j=1}^{\log_2 i}f_{i, j} \times j$，$mul_i = \prod\limits_{j=1}^{\log_2 i}j ^ {f_{i, j}}$。

这样设计的答案 1 为 $sum_r - sum_{l - 1}$，答案 2 为 $\dfrac{mul_r}{mul_{l - 1}}$。问题现在在如何求解 $f_{i, j}$ 上。那么考虑从高到低枚举每一位：

1. 这一位是 $0$

没有任何贡献, Skip.

2. 这一位是 $1$

为了防止多讨论，我们细分一下：

想要统计这一位是 $1$ 但是会被后面限制大小的合法的数，则需要继续考虑。

想要统计这一位是 $0$ 的合法的数，那么直接统计合法的数即可。

---

然鹅代码还是不太好写捏，这里我们不使用刷表法而是改用推表法：

从低到高枚举第 $k$ 位，如果这一位有 $1$ 就去枚举右边 $k - 1$ 个位填了 $t$ 个 $1$。记这一位左边的 $1$ 的个数为 $cnt$，然后 $f_{t, k + cnt}$ 加上一个组合数 $C_{t}^{k - 1}$，表示右边 $k - 1$ 个位填了 $t$ 个 $1$ 的方案个数。

这样子就完成了，记得最后统计不要忘记自己。但是复杂度仍然爆炸，因为有了组合数就要除法，模意义下除法就要乘法逆元。

所以不能采用 $\log_2$ 复杂度的费马小定理每次都求一遍。我们可以花 $\mathcal{O}(\log_2^2 N)$ 预处理组合数，这样就不必再计算了。

这样总的复杂度为 $\mathcal{O}(\log_2^2 N)$ 加上有点巨大的常数，但是仍可以通过此题。

# 后言

数位 DP 加上数论真令人头疼，以前还没碰到过。

---

