# [ABC273G] Row Column Sums 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc273/tasks/abc273_g

非負整数を要素とする $ N $ 次正方行列であって、下記の $ 2 $ つの条件をともに満たすものの個数を $ 998244353 $ で割ったあまりを出力してください。

- すべての $ i\ =\ 1,\ 2,\ \ldots,\ N $ について、$ i $ 行目の要素の和は $ R_i $ である。
- すべての $ i\ =\ 1,\ 2,\ \ldots,\ N $ について、$ i $ 列目の要素の和は $ C_i $ である。

入力で与えられる $ R_i $ および $ C_i $ は $ 0 $ 以上 $ 2 $ 以下の整数であることに注意してください（制約参照）。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 5000 $
- $ 0\ \leq\ R_i\ \leq\ 2 $
- $ 0\ \leq\ C_i\ \leq\ 2 $
- 入力はすべて整数

### Sample Explanation 1

条件を満たす行列は下記の $ 3 $ つです。 ``` 0 1 0 0 0 1 0 0 1 ``` ``` 0 0 1 0 1 0 0 0 1 ``` ``` 0 0 1 0 0 1 0 1 0 ```

### Sample Explanation 3

$ 998244353 $ で割ったあまりを出力することに注意してください。

## 样例 #1

### 输入

```
3
1 1 1
0 1 2```

### 输出

```
3```

## 样例 #2

### 输入

```
3
1 1 1
2 2 2```

### 输出

```
0```

## 样例 #3

### 输入

```
18
2 0 1 2 0 1 1 2 1 1 2 0 1 2 2 1 0 0
1 1 0 1 1 1 1 1 1 1 1 1 2 1 1 0 2 2```

### 输出

```
968235177```

# 题解

## 作者：bugmaker3243 (赞：12)

约定：为方便描述，将 “和为 $2$ 的行”简称为 $2$ 类行，“和为 $1$ 的行”简称为 $1$ 类行，列同理。

设有 $c_1$ 个 $1$ 类行，$c_2$ 个 $2$ 类行，$c_3$ 个 $1$ 类列， $c_4$ 个 $2$ 类列。

# 基本分析

我们可以固定每行的和为 $R_i$，将 $R_i$ 拆开放在行中的不同位置，来满足每列的和为 $C_i$ 的要求。

因为 $0\leq R_i,C_i \leq 2$，容易想到使用动态规划。

# 具体实现

#### 状态

设 $f_{i,j,k,l}$ 表示还剩下 $i$ 个 $1$ 类行和 $j$ 个 $2$ 类行，来满足 $k$ 个 $1$ 类列和 $l$ 个 $2$ 类列的方案数。

显然，若 $i+2\times j \ne k+2\times l$，肯定无解，所以所有的 $(i,j,k,l)$ 一定满足 $i+2\times j = k+2\times l$。

#### 转移

对于所有的 $1$ 类行，我们放到最后来考虑。

对于每一个 $2$ 类行，它有这四种转移：

- 拆成 $1+1$ 来满足两个 $1$ 类列，方案数为 $f_{i,j-1,k-2,l}\times \binom{k}{2}$。

- 拆成 $1+1$ 来满足一个 $1$ 类列，并将一个 $2$ 类列变成 $1$ 类列，方案数为 $f_{i,j-1,k,l-1}\times k\times l$。

- 拆成 $1+1$ 将两个 $2$ 类列变成 $1$ 类列，方案数为 $f_{i,j-1,k,l-2}\times \binom{l}{2}$。

- 满足一个 $2$ 类列，方案数为 $f_{i,j-1,k,l-1}\times l$。

#### 边界条件

$j=0$ 时，剩下 $i$ 个 $1$ 类行，满足 $k$ 个 $1$ 类列和 $l$ 个 $2$ 类列。

即 $f_{i,0,k,l}=\binom{k}{1}\binom{k-1}{1}\dots\binom{2\times l+1}{1}\binom{2\times l}{2}\binom{2\times l-2}{2}\dots\binom{2}{2}=\frac{k!}{2^l}$。

#### 时间复杂度

状态数为 $O(n^4)$，转移 $O(1)$，时间复杂度为 $O(n^4)$，无法通过。

## 优化状态数

所有状态的第一维 $i$ 均是不变的，可以省掉这一维。

于是现在的状态 $f_{j,k,l}$ 表示还剩下 $c_1$ 个 $1$ 类行和 $j$ 个 $2$ 类行，来满足 $k$ 个 $1$ 类列和 $l$ 个 $2$ 类列的方案数。

还记得在这篇题解最开始提到的那个等式吗： $i+2\times j = k+2\times l$。

所以 $k$ 可以表示为 $i+2\times j -2\times l$。

那么现在的状态即 $f_{j,l}$ 表示还剩下 $c_1$ 个 $1$ 类行和 $j$ 个 $2$ 类行，来满足 $c_1+2\times j -2\times l$ 个 $1$ 类列和 $l$ 个 $2$ 类列的方案数。

#### 转移

设 $k=i+2\times j -2\times l$。

于是 $f_{j,l}=f_{j-1,l}\times \binom{k}{2} + f_{j-1,l-1}\times k\times l+ f_{j-1,l-2}\times \binom{l}{2} + f_{j-1,l-1}\times l $。

#### 边界条件

$f_{0,l}=\frac{c_1!}{2^l}$。

#### 时间复杂度

状态数为 $O(n^2)$，转移 $O(1)$，时间复杂度为 $O(n^2)$，可以通过。

# 代码（请勿抄袭）

```cpp
#include<bits/stdc++.h>
#define mod 998244353
#define int long long
using namespace std;
namespace Binom//组合数板子 
{
	#define N 50005//注意预处理需要处理2倍n长度 
	int st[N],qp[N];
	int qpow(int x,int n)
	{
		if(x<0) return 0;
		if(!n) return 1;
		int t=qpow(x,n/2);
		if(n&1) return t*t%mod*x%mod;
		return t*t%mod;
	}
	void C_init()
	{
		st[0]=1;
		for(int i=1;i<N;i++) st[i]=st[i-1]*i%mod;
		qp[N-1]=qpow(st[N-1],mod-2);
		for(int i=N-2;i>=0;i--) qp[i]=qp[i+1]*(i+1)%mod;
	}
	int C(int n,int m)
	{
		if(n<0||m<0||m>n) return 0;
		return st[n]*qp[n-m]%mod*qp[m]%mod;
	}
	int A(int n,int m)
	{
		if(n<0||m<0||m>n) return 0;
		return st[n]*qp[n-m]%mod;
	}
	#undef N 
}
using namespace Binom;
#define N 5005
int n,r[N],c[N],f[N][N];
void add(int &x,int y){x=(x+y)%mod;}
signed main()
{
	C_init();
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&r[i]);
	for(int i=1;i<=n;i++) scanf("%lld",&c[i]);
	int c1=0,c2=0,c3=0,c4=0;
	for(int i=1;i<=n;i++)
	{
		if(r[i]==1) c1++;
		if(r[i]==2) c2++;
		if(c[i]==1) c3++;
		if(c[i]==2) c4++;
	}
	if(c1+c2*2!=c3+c4*2) return puts("0"),0;
	for(int i=0;i<=c4;i++) f[0][i]=st[c1]*qpow(qpow(2,i),mod-2)%mod;//边界条件 
	for(int j=1;j<=c2;j++)
		for(int l=0;l<=c4;l++)//转移 
		{
			int k=c1+2*j-2*l;
			if(k>=2) add(f[j][l],f[j-1][l]*C(k,2)%mod);//拆1+1给1+1
			if(l&&k) add(f[j][l],f[j-1][l-1]*k%mod*l%mod);//拆1+1给1+2 
			if(l>=2) add(f[j][l],f[j-1][l-2]*C(l,2)%mod);//拆1+1给2+2 
			if(l) add(f[j][l],f[j-1][l-1]*l%mod);//给2 
		}
	printf("%lld",f[c2][c4]);
	return 0;
}
```


---

## 作者：_•́へ•́╬_ (赞：8)

## 思路

数一下读入的里面，行上有 $cnt_1$ 个 $1$，行上有 $cnt_2$ 个 $2$，列上有 $cnt_3$ 个 $1$，列上有 $cnt_4$ 个 $2$ 的答案。

当且仅当 

$$
cnt_1+2\times cnt_2\neq cnt_3+2\times cnt_4
$$

无解。

-----------------

设 $f(i,j,k,l)$ 为行上有 $i$ 个 $1$，行上有 $j$ 个 $2$，列上有 $k$ 个 $1$，列上有 $l$ 个 $2$ 的答案。

考虑转移。

- 当 $l>0$ 时：注意有 $i+2\times j=k+l\times 2$ 成立！

考虑分配一个 列上为 $2$ 的东西：

- 给行上的一个 $1$ 和一个 $2$：$f(i-1+1,j-1,k,l-1)\times i\times j$。（就是那个 $1$ 没了，$2$ 变成 $1$ 了）
- 给行上的两个 $1$：$f(i-2,j,k,l-1)\times C_i^2$。
- 给行上的两个 $2$：$f(i+2,j-2,k,l-1)\times C_j^2$。
- 给行上的一个 $2$：$f(i,j-1,k,l-1)\times j$。

当 $l=0$ 时：注意有 $i+2\times j=k$ 成立！（这点对于理解下面的式子很重要）

答案就是
$$
C_k^1\times C_{k-1}^1\times \cdots\times C_{2\times j+1}^1\times C_{2\times j}^2\times C_{2\times(j-1)}^2\times\cdots\times C_2^2
$$

$$
=\frac{k!}{2^j}
$$

---------------

注意到在转移的过程中 $k$ 始终不变，就是 $cnt_3$。

另外因为始终有那个等式成立（不成立就无解了），所以得到 $i,j,l$ 中的两个就能算出另一个，所以只需要吧其中的两个作为数组下标存着。

复杂度 $\mathcal{O}(n^2)$。

## code

```cpp
#include<stdio.h>
#include<string.h>
#define mod 998244353
inline char nc()
{
 	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int n,a,cnt1,cnt2,cnt3,cnt4,ans[5001][5001],fac[5001];
inline long long ksm(long long a,int b)
{
	long long ans=1;
	for(;b;b>>=1,a*=a,a%=mod)if(b&1)ans*=a,ans%=mod;
	return ans;
}
inline long long dfs(const int&i,const int&j,const int&k,const int&l)
{
	if(!l)return fac[k]*ksm(ksm(2,j),mod-2)%mod;
	if(~ans[i][l])return ans[i][l];
	ans[i][l]=0;
	if(i&&j)ans[i][l]=(ans[i][l]+dfs(i,j-1,k,l-1)*i%mod*j)%mod;
	if(i>1)ans[i][l]=(ans[i][l]+dfs(i-2,j,k,l-1)*(i*(i-1ll)>>1))%mod;
	if(j>1)ans[i][l]=(ans[i][l]+dfs(i+2,j-2,k,l-1)*(j*(j-1ll)>>1))%mod;
	if(j)ans[i][l]=(ans[i][l]+dfs(i,j-1,k,l-1)*j)%mod;
	return ans[i][l];
}
main()
{
	fac[0]=1;for(int i=1;i<5001;fac[i]=(long long)(fac[i-1])*i%mod,++i);
	memset(ans,-1,sizeof(ans));read(n);
	for(int i=n;i--;read(a),a==1&&++cnt1,a==2&&++cnt2);
	for(int i=n;i--;read(a),a==1&&++cnt3,a==2&&++cnt4);
	if(cnt1+cnt2+cnt2^cnt3+cnt4+cnt4){putchar('0');return 0;}
	printf("%lld",dfs(cnt1,cnt2,cnt3,cnt4));
}
```

---

## 作者：cwfxlh (赞：8)

# [AT_abc273_g](https://www.luogu.com.cn/problem/AT_abc273_g)    

将限制分为行限制 $1$，行限制 $2$，列限制 $1$，列限制 $2$。考虑先计算行限制 $2$。    

令 $dp_{i,j}$ 表示有 $i$ 个列限制 $1$，$j$ 个列限制 $2$，$\frac{i+j}{2}$ 个行限制 $2$ 时的方案数。这时可以枚举 $i+j$ 转移。   

具体的转移可以考虑：列限制 $2$ 填一个行限制 $2$，两个列限制 $1$ 填一个行限制 $2$，一个列限制 $1$ 和一个列限制 $2$ 填一个行限制 $2$ 并且多出一个列限制 $1$，两个列限制 $2$ 填一个行限制 $2$ 并多出两个列限制 $1$。   

转移完后，考虑行限制 $1$，再次 DP 即可（这里注意对于上一轮的 DP 值，行限制 $2$ 数量不够的要清掉）。转移时考虑用一个列限制 $1$ 填一个行限制 $1$，用一个列限制 $2$ 填一个行限制 $1$ 并多出一个列限制 $1$。      

代码：   

```cpp
#include<bits/stdc++.h>
#define int long long
#define MOD 998244353
using namespace std;
int n,v[4][4],k1,k2,dp[10003][5003];
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&k1);
		v[0][k1]++;
	}
	for(int i=1;i<=n;i++){
		scanf("%lld",&k1);
		v[1][k1]++;
	}
	if(v[0][1]+v[0][2]*2!=v[1][1]+v[1][2]*2){
		puts("0");
		return 0;
	}
	dp[0][0]=1;
	for(int sum=2;sum<=v[0][2]*2;sum+=2){
		for(int j=0,u=sum/2;j<=sum&&u>=0;j+=2,u--){
			if(j>=2)dp[j][u]=(dp[j][u]+dp[j-2][u]*((j*(j-1)/2)%MOD))%MOD;
			if(u)dp[j][u]=(dp[j][u]+dp[j][u-1]*u)%MOD;
			if(j&&u)dp[j][u]=(dp[j][u]+dp[j][u-1]*(j*u%MOD))%MOD;
			if(u>=2)dp[j][u]=(dp[j][u]+dp[j+2][u-2]*(u*(u-1)/2))%MOD;
		}
	}
	for(int sum=2;sum<v[0][2]*2;sum+=2){
		for(int j=0,u=sum/2;j<=sum&&u>=0;j+=2,u--)dp[j][u]=0;
	}
	for(int sum=2*v[0][2]+1;sum<=2*v[0][2]+v[0][1];sum++){
		for(int j=(sum%2),u=(sum/2);j<=sum&&u>=0;j+=2,u--){
			if(j)dp[j][u]=(dp[j][u]+dp[j-1][u]*j)%MOD;
			if(u)dp[j][u]=(dp[j][u]+dp[j+1][u-1]*u)%MOD;
		}
	}
	printf("%lld",dp[v[1][1]][v[1][2]]);
	return 0;
}
```


---

## 作者：daniEl_lElE (赞：3)

Luogu 爬 Atcoder 后我的第一篇 Atcoder 题解！

首先既然没有评难度建议管理员审核本题解时先加上难度紫，算法“动态规划”，“组合数学”。

## 思路

比较经典的 dp 问题，考虑看到 $R_i,C_i\leq 2$，我们可以设计 $dp_{i,j,k}$ 表示目前看到 $R_i$，组合出来了 $j,k$ 个列上放置了分别 $1,2$ 个棋子的列的方案数。转移的时候根据 $R_i=0,R_i=1,R_i=2$ 分别考虑即可。

* $R_i=0:dp_{i-1,j,k}\to dp_{i,j,k}$；
* $R_i=1:dp_{i-1,j,k}\times (n-j-k)\to dp_{i,j+1,k},dp_{i-1,j,k}\times j\to dp_{i,j-1,k+1}$；
* $R_i=2:dp_{i-1,j,k}\times\binom{n-j-k}{2}\to dp_{i,j+2,k},dp_{i-1,j,k}\times\binom{j}{2}\to dp_{i,j-2,k+2},dp_{i-1,j,k}\times(n-j-k)\times(j+1)\to dp_{i,j,k+1}$；

考虑到后面两维其实枚举一维另一位即可计算，可以滚动其中之一，也可以滚动最前面的第一维，总之复杂度 $O(n^2)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
int mod=998244353;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return ans;
}
int fac[10000005],inv[10000005];
void init(){
	fac[0]=1;
	for(int i=1;i<=10000000;i++) fac[i]=fac[i-1]*i%mod;
	inv[10000000]=qp(fac[10000000],mod-2);
	for(int i=9999999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int i,int j){
	if(i<0||j<0||i<j) return 0;
	return fac[i]*inv[i-j]%mod*inv[j]%mod;
}
int read(){
	char c; int ans=0; int z=1;
	while(!isdigit(c=getchar()))z-=2*(c=='-');
	do{ans=(ans*10+c-'0');}while(isdigit(c=getchar()));
	return ans*z;
}
void print(int x){
	if(x<0) putchar('-');
	if(llabs(x)>=10) print(llabs(x)/10);
	putchar((llabs(x)%10)+'0');
}
void endl(){
	putchar(10);
}
int dp[5005][5005];
int cnt[5005];
signed main(){
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	init();
	int n;
	cin>>n;
	int r[n+1],c[n+1],tot1=0,tot2=0;
	for(int i=1;i<=n;i++) tot1+=(r[i]=read());
	for(int i=1;i<=n;i++) cnt[c[i]=read()]++,tot2+=c[i];
	if(tot1!=tot2){
		cout<<0;
		return 0;
	}
	int sum=0;
	dp[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n;j++){
			if(sum-j*2<0||n-sum+j*2-j<0){
				continue;
			}
			int num1=sum-j*2,num2=j;
			if(r[i]==1&&n-num1-num2>0) dp[num1+1][num2]=(dp[num1+1][num2]+dp[num1][num2]*(n-num1-num2))%mod;
			if(r[i]==1&&num1>=1) dp[num1-1][num2+1]=(dp[num1-1][num2+1]+dp[num1][num2]*num1)%mod;
			if(r[i]==2&&n-num1-num2>1) dp[num1+2][num2]=(dp[num1+2][num2]+dp[num1][num2]*(((n-num1-num2)*(n-num1-num2-1)/2)%mod))%mod;
			if(r[i]==2&&n-num1-num2>0&&num1>=1) dp[num1][num2+1]=(dp[num1][num2+1]+dp[num1][num2]*(n-num1-num2)%mod*num1)%mod;
			if(r[i]==2&&num1>=2) dp[num1-2][num2+2]=(dp[num1-2][num2+2]+dp[num1][num2]*((num1*(num1-1)/2)%mod))%mod;
			if(r[i]==2&&n-num1-num2>0) dp[num1][num2+1]=(dp[num1][num2+1]+dp[num1][num2]*(n-num1-num2))%mod;
		}
		sum+=r[i];
	}
	cout<<dp[cnt[1]][cnt[2]]*fac[cnt[0]]%mod*fac[cnt[1]]%mod*fac[cnt[2]]%mod*inv[n]%mod;
	return 0;
}
```

---

## 作者：Tsawke (赞：2)

#  [[ABC273G] Row Column Sums 2](https://www.luogu.com.cn/problem/AT_abc273_g) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC273G)

## 题面

给定 $ n $，给定序列 $ R_n, C_n $，求有多少个 $ n \times n $ 的矩阵满足第 $ i $ 行的数之和为 $ R_i $，第 $ i $ 列的数之和为 $ C_i $，保证 $ 0 \le R_i, C_i, \le 2 $，答案对 $ 998244353 $ 取模。

## Solution

提供一种较为好理解且转移较为好实现的做法，核心思路来自 @sssmzy。

设计状态 $ dp(i, j, k) $ 表示考虑前 $ i $ 行剩余 $ j $ 列需要再添 $ 1 $，$ k $ 列需要再添 $ 2 $ 的方案数，考虑对于每一行可以去消除一些 $ j $ 或 $ k $，考虑转移：

对于 $ R_i = 0 $，显然无法产生贡献。
$$
R_i = 0 : dp(i, j, k) \leftarrow dp(i - 1, j, k)
$$
对于 $ R_i = 1 $，考虑要么将其补全一个 $ j $，要么将其去补到 $ k $ 使得减少一个 $ k $ 并多一个 $ j $。
$$
R_i = 1 : dp(i, j, k) \leftarrow dp(i - 1, j + 1, k) \times (j + 1) + dp(i - 1, j - 1, k + 1) \times (k + 1)
$$
对于 $ R_i = 2 $，考虑可以补全两个 $ j $，或补全一个 $ k $，或将两个 $ k $ 转化为两个 $ j $，或补全一个 $ j $ 并将一个 $ k $ 转换为 $ j $。
$$
R_i = 2 : dp(i, j, k) \leftarrow dp(i - 1, j + 2, k) \times {j + 2 \choose 2} + dp(i - 1, j, k + 1) \times (k + 1) + dp(i - 1, j - 2, k + 2) \times {k + 2 \choose 2} + dp(i - 1, j, k + 1) \times (k + 1) \times j
$$
此为 $ \texttt{3D0D} $，考虑在每一层转移中，$ j + k $ 的值应为固定的，于是当我们已知 $ j $ 时 $ k $ 就是固定的，具体来说维护一个 $ \sum C_i $，然后每次转移时删去当前次贡献的 $ R_i $ 即可。于是以此可以无需枚举最后一维（同理也可以选择删去 $ i $ 或 $ j $），优化为 $ \texttt{2D0D} $，可以通过。

Tips：注意需要特判 $ \sum R_i \neq \sum C_i $ 时无解，答案为 $ 0 $。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW void* Edge::operator new(size_t){static Edge* P = ed; return P++;}
#define ROPNEW_NODE void* Node::operator new(size_t){static Node* P = nd; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define MOD (998244353ll)

template < typename T = int >
inline T read(void);

int N;
ll sumC(0);
ll dp[5100][5100];
int R[5100], C[5100];
int cnt1(0);

int main(){
    // freopen("in.txt", "r", stdin);
    N = read();
    for(int i = 1; i <= N; ++i)R[i] = read();
    for(int i = 1; i <= N; ++i)sumC += (C[i] = read());
    for(int i = 1; i <= N; ++i)if(C[i] == 1)++cnt1;
    dp[0][cnt1] = 1;
    for(int i = 1; i <= N; ++i){
        sumC -= R[i];
        for(int j = 0; j <= N; ++j){
            if((sumC - j) & 1)continue;
            int k = (sumC - j) >> 1;
            switch(R[i]){
                case 0:{
                    dp[i][j] = dp[i - 1][j];
                    break;
                }
                case 1:{
                    (dp[i][j] += dp[i - 1][j + 1] * (j + 1) % MOD) %= MOD;
                    if(j - 1 >= 0)(dp[i][j] += dp[i - 1][j - 1] * (k + 1) % MOD) %= MOD;
                    break;
                }
                case 2:{
                    (dp[i][j] += dp[i - 1][j + 2] * ((j + 2) * (j + 1) / 2 % MOD) % MOD) %= MOD;
                    (dp[i][j] += dp[i - 1][j] * (k + 1) % MOD) %= MOD;
                    if(j - 2 >= 0)(dp[i][j] += dp[i - 1][j - 2] * ((k + 2) * (k + 1) / 2 % MOD) % MOD) %= MOD;
                    (dp[i][j] += dp[i - 1][j] * (k + 1) % MOD * j % MOD) %= MOD;
                    break;
                }
            }
        }
    }
    printf("%lld\n", sumC ? 0 : dp[N][0]);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2023_02_20 初稿

---

## 作者：happybob (赞：0)

题意：

给定正整数 $n$ 和两个长为 $n$ 的序列 $r_i, c_i$，求有多少个 $n\times n$ 的矩阵满足以下条件:

- 所有元素是非负整数。
- 对于所有 $1\leq i\leq n$，第 $i$ 行上所有元素之和为 $r_i$。
- 对于所有 $1\leq i\leq n$，第 $i$ 列上所有元素之和为 $c_i$。

答案对 $998244353$ 取模。

$1 \leq N \leq 5000$，$0 \leq r_i, c_i \leq 2$。

解法：

首先容易发现具体每行每列和是 $0,1,2$ 并不重要，我们只关心 $0,1,2$ 在行列中成为和的个数。

记 $f_{i,j}$ 表示考虑了前 $i$ 行，有 $j$ 列的和为 $2$ 的方案数。发现此时和为 $0$ 与 $1$ 的列可以直接算出，故可以 $O(1)$ 转移，总复杂度 $O(n^2)$。

[Submission Link.](https://atcoder.jp/contests/abc273/submissions/60691891)

---

## 作者：xiezheyuan (赞：0)

## 简要题意

有一个 $n\times n$ 的矩阵，现在我们知道第 $i$ 行所有数的和为 $r_i$，第 $i$ 列的所有数的和为 $c_i$。你需要求出这样的矩阵有多少个。

$1\leq n\leq 5000,0\leq r_i,c_i\leq 2$。

## 思路

非常厉害的题目，让我深深感受到自己的弱小。感谢 @\_Aurore\_ 提供的训练题文档。

首先有一个非常平凡的 dp，设 $f(i,j,k,l)$ 表示考虑到第 $i$ 行，有 $j$ 列不能填数，$k$ 列可以再填一个 $1$，$l$ 列可以再填两个 $1$ 或者一个 $2$ 的方案数。转移的话分类讨论这一行我们怎么填就好了。

时间复杂度和空间复杂度为 $O(n^4)$ 难以接受。考虑减少状态数量。

首先发现 $j$ 这一维是没有必要的，因为不能填数的列对答案没有实际上的影响。

到这里时间复杂度和空间复杂度都是 $O(n^3)$ 同样难以接受。考虑继续减少状态数量。

然后我们发现其实 $k$ 和 $l$ 中只需要保留一个。为什么呢？考虑到假设我们整个矩阵所有数的和为 $S$，$i$ 行之前（不包括这一行）填的所有数的总和为 $T_i$，那么实际上有下面的等式：

$$
S-T_i=2l+k
$$

原因其实比较显然，接下来可以填 $S-T_i$ 个元素，有 $k$ 是 $1$ 的贡献，有 $l$ 是 $2$ 的贡献。至于这一行本身填的数的问题，可以考虑刷表法来规避。

我们将 $l$ 这一维干掉，设 $f(i,j)$ 表示考虑前 $i$ 行剩余 $j$ 列可以填一个 $1$ 的方案数。接下来考虑转移（也就是大分类讨论）：

对于 $r_i=0$ 的情况，这一行不能填数，自然也就没有额外方案贡献，$f(i,j)\leftarrow f(i-1,j)$。

对于 $r_i=1$ 的情况，这一行可以填一个 $1$，不过填的位置，不确定，需要分类讨论：

- 假如填在原先只能填 $1$ 的列，那么减少了一个只能填 $1$ 的列，也就是 $f(i,j-1)\leftarrow f(i-1,j)\cdot j$。
- 假如填在原先只能能填 $2$ 的列，那么新增了一个只能填 $1$ 的列，也就是 $f(i,j+1)\leftarrow f(i-1,j)\cdot x$，其中 $x=\frac{1}{2}(S-T_i-j)$ 表示可以填 $2$ 的列的数量，下同。

对于 $r_i=2$ 的情况，比较复杂，我们需要细致讨论：

- 假如在两个原先只能填 $1$ 的列中都填一个 $1$，那么减少了一个只能填 $1$ 的列，也就是 $f(i,j-2)\leftarrow f(i-1,j)\cdot \binom{j}{2}$。
- 假如在两个原先只能填 $2$ 的列都填一个 $1$，那么新增了两个只能填 $1$ 的列，也就是 $f(i,j+2)\leftarrow f(i-1,j)\cdot \binom{x}{2}$。
- 假如在一个原先只能填 $1$ 的列填一个 $1$，然后再一个可以填 $2$ 的列中填一个 $1$，那么恰好多一个只能填 $1$ 的列，少一个只能填 $1$ 的列，相当于只能填 $1$ 的列数量没有增加。也就是 $f(i,j)\leftarrow f(i-1,j)\cdot jx$。
- 假如在一个原先只能填 $2$ 的列中填一个 $2$，那么只能填 $1$ 的列的数量没有发生变化。也就是 $f(i,j)\leftarrow f(i-1,j)\cdot x$。

最后答案显然是 $f(n,0)$。不过注意判一下无解。

时间复杂度 $O(n^2)$ 可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;

const int N = 5005;
int n, r[N], c[N], f[N][N];

constexpr int mod = 998244353, inv2 = (mod + 1) >> 1;
int Add(int x, int y){ return (x + y) >= mod ? (x + y - mod) : (x + y); }
int Sub(int x, int y){ return (x - y) < 0 ? (x - y + mod) : (x - y); }
int Mul(int x, int y){ return 1ll * x * y % mod; }

int binom2(int x){ return Mul(Mul(x, x - 1), inv2); }

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> r[i];
    for(int i=1;i<=n;i++) cin >> c[i];
    int s = 0, t = 0, onecnt = 0;
    for(int i=1;i<=n;i++){
        onecnt += (c[i] == 1);
        s = Add(s, c[i]);
    }
    f[0][onecnt] = 1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=n;j++){
            int x = (s - t - j) >> 1;
            if(r[i] == 0) f[i][j] = f[i - 1][j];
            else if(r[i] == 1){
                if(j) f[i][j - 1] = Add(f[i][j - 1], Mul(f[i - 1][j], j));
                f[i][j + 1] = Add(f[i][j + 1], Mul(f[i - 1][j], x));
            }
            else{
                if(j >= 2) f[i][j - 2] = Add(f[i][j - 2], Mul(f[i - 1][j], binom2(j)));
                f[i][j + 2] = Add(f[i][j + 2], Mul(f[i - 1][j], binom2(x)));
                f[i][j] = Add(f[i][j], Mul(f[i - 1][j], Mul(j, x)));
                f[i][j] = Add(f[i][j], Mul(f[i - 1][j], x));
            }
        }
        t += r[i];
    }
    if(s != t) cout << 0 << '\n';
    else cout << f[n][0] << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_abc273_g)

**题目大意**

> 求有多少个 $n\times n$ 正整数矩阵使得其第 $i$ 行和是 $r_i$，第 $j$ 列和是 $c_j$。
>
> 数据范围：$n\le 5000,r_i,c_j\le 2$。

**思路分析**

显然 $\sum r_i\ne\sum c_j$ 无解，不妨记 $m=\sum r_i=\sum c_j$。

否则我们可以看成二分图，$r_i=0$ 不建点，$r_i=2$ 拆成两个点，右部 $c_j$ 同理，两个点 $(i,j)$ 匹配表示 $A_{i,j}$ 上 $+1$。

但是对于 $r_i=2,c_j=1,c_k=1$ 此时 $i_0\to j,i_1\to k$ 和 $i_0\to k,i_1\to j$ 是同一种方案，因此假设 $r_i,c_j$ 中分别有 $x,y$ 个 $2$，那么答案要除以 $2^{x+y}$。

但这并不完全对，假如 $r_i=2,c_j=2$，且 $(i_0,i_1)\to(j_0,j_1)$，此时只是重复计算了两倍贡献但除以了 $4$，因此对于这样的匹配要乘回一个 $2$。

因此我们枚举 $i$ 表示有多少这样的 $r_p=c_q=2$ 且互相匹配，对答案的贡献就是对应匹配数 $\times 2^i$，那么我们要求剩余部分没有这样的匹配，可以容斥原理解决：
$$
\mathrm{Ans}=\dfrac{1}{2^{x+y}}\sum_{i=0}^{\min(x,y)} 2^i\binom xi\binom yii!2^i\sum_{j=0}^{\min(x,y)-i}\binom{x-i}j\binom{y-i}jj!2^j(m-2i-2j)!
$$
其中乘第二个 $2^i$ 是这 $i$ 对 $(p_0,p_1),(q_0,q_1)$ 中每对有两种匹配方式。

时间复杂度 $\mathcal O(n^2)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1e4+5,MOD=998244353,i2=(MOD+1)/2;
ll fac[MAXN],ifac[MAXN],ans;
int s,n,m,x,y;
ll ksm(ll a,ll b=MOD-2,ll p=MOD) {
	ll ret=1;
	for(;b;a=a*a%p,b>>=1) if(b&1) ret=ret*a%p;
	return ret;
}
ll C(int a,int b) { return fac[a]*ifac[b]%MOD*ifac[a-b]%MOD; }
signed main() {
	scanf("%d",&s);
	for(int i=1,p;i<=s;++i) scanf("%d",&p),n+=p,x+=(p==2);
	for(int i=1,p;i<=s;++i) scanf("%d",&p),m+=p,y+=(p==2);
	if(n^m) return puts("0"),0;
	for(int i=fac[0]=ifac[0]=1;i<=n;++i) ifac[i]=ksm(fac[i]=fac[i-1]*i%MOD);
	for(int i=0;i<=min(x,y);++i) {
		ll v=C(x,i)*C(y,i)%MOD*fac[i]%MOD*ksm(2,2*i)%MOD,pw=1;
		for(int j=0;i+j<=min(x,y);++j,pw=pw*2%MOD) {
			ans=(ans+(j&1?-1:1)*C(x-i,j)*C(y-i,j)%MOD*fac[j]%MOD*pw%MOD*fac[n-2*i-2*j]%MOD*v)%MOD;
		}
	} 
	printf("%lld\n",(ans*ksm(i2,x+y)%MOD+MOD)%MOD);
	return 0;
}
```

---

## 作者：weirdoX (赞：0)

我们用 $dp_{i,j}$ 表示考虑到前 $i$ 行，有 $j$ 个 $2$ 的方案数。  

设有 $k$ 个 $1$（因为我们对于每一行都有固定的和，所以 $k$ 计算可得）。  

- $a_{i+1} = 0$：

  - $dp_{i,j} \to dp_{i+1,j}$

- $a_{i+1}=1$：

  - $dp_{i,j}\times(n-j-k) \to dp_{i+1,j}$ 

  - $dp_{i,j}\times k \to dp_{i+1,j+1}$

- $a_{i+1}=2$：

  - $dp_{i,j}\times \tbinom{n-j-k}{2} \to dp_{i+1,j}$

  - $dp_{i,j} \times (n - j - k) \times k \to dp_{i+1,j+1}$

  - $dp_{i,j} \times \tbinom{k}{2} \to dp_{i+1,j+2}$

  - $dp_{i,j} \times \tbinom{n-j-k}{1} \to dp_{i,j+1}$

组合数公式：
$\tbinom{n}{m} = \frac{n!}{(n-m)!m!}$

### AcCode:

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 1e4 + 10, inf = INT_MAX, P = 998244353;
int n;
int a[N], b[N], sum[N];
ll dp[N], tmp[N], f[N], inv[N];

ll rp(ll a, int b) {
	ll res = 1;
	for (; b; (a *= a) %= P, b /= 2)
		if (b & 1)
			(res *= a) %= P;
	return res;
}

void init() {
	f[0] = 1;
	for (int i = 0; i <= n; i++) {
		if (i) f[i] = f[i - 1] * i % P;
		inv[i] = rp(f[i], P - 2);
	}
}

ll C(int a, int b) {
	if (a < b) return 0;
	return f[a] * inv[a - b] % P * inv[b] % P;
}

int main() {
	scanf("%d", &n);
	init();
	int cnt = 0, t1 = 0, t2 = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		sum[i] = sum[i - 1] + a[i];
		t1 += a[i];
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &b[i]);
		cnt += (b[i] == 2);
		t2 += b[i];
	}
	if (t1 != t2) {
		puts("0");
		return 0;
	}
	tmp[0] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= n; j++) {
			int k = sum[i] - j * 2;// k个1
			if (!tmp[j] || k < 0 || n - j - k < 0) continue;
			if (a[i + 1] == 0)
				(dp[j] += tmp[j]) %= P;
			else if (a[i + 1] == 1) {
				(dp[j] += tmp[j] * (n - j - k) % P) %= P;
				(dp[j + 1] += tmp[j] * k % P) %= P;
			} else {
				(dp[j] += tmp[j] * C(n - j - k, 2) % P) %= P;
				(dp[j + 1] += tmp[j] * (n - j - k) % P * k % P) %= P;
				(dp[j + 1] += tmp[j] * C(n - j - k, 1) % P) %= P;
				(dp[j + 2] += tmp[j] * C(k, 2) % P) %= P;
			}
		}
		for (int j = 0; j <= n; j++) {
			tmp[j] = dp[j];
			dp[j] = 0;
		}
	}
	int tot = sum[n] - cnt * 2;
	ll ans = tmp[cnt];
	ans = ans * rp(C(n, cnt), P - 2) % P;
	ans = ans * rp(C(n - cnt, tot), P - 2) % P;
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：shinkuu (赞：0)

感觉，有时候把问题往网络流上想，不失为一种好的思路。

我们考虑 $(i,j)$ 上填一个 $c$ 的意义。则第 $i$ 行和第 $j$ 列需要填的和都会减少 $c$。如果把他看作是一条 $(i.j)$ 之间的边，问题就变为：在两个点集之间连边，**可以有重边**，$a_{i,0/1}$ 表示第 $1/2$ 个点集的第 $i$ 个点度数为 $a_{i,0/1}$，匹配的方案数。

此时发现值域只有 $3$，并且知道总数和其中一个就可以推出另外两个。联想到 [AT_dp_j](https://www.luogu.com.cn/problem/AT_dp_j)。从前往后匹配 $a_{i,0}$，$dp_{i,j}$ 表示考虑第一个点集的前 $i$ 个点，第二个点集中还剩 $j$ 个 $1$ 没匹配。转移是 naive 的，可以参考代码。

时空 $O(n^2)$，注意边界条件。

code：

```cpp
int n,m,dp[N][N],a[N],b[N];
il int Mod(int x,int y){return x+y>=mod?x+y-mod:x+y;}
void Yorushika(){
	scanf("%d",&n);
	int x=0,y=0,z=0;
	rep(i,1,n)scanf("%d",&a[i]),x+=a[i];
	rep(i,1,n)scanf("%d",&b[i]),y+=b[i],z+=b[i]==1;
	if(x!=y)return puts("0"),void(0);
	dp[0][z]=1;int s=x;
	rep(i,1,n){
		if(!a[i]){
			rep(j,0,n)dp[i][j]=dp[i-1][j];
			continue;
		}
		rep(j,0,n){
			if((s-j)&1)continue;
			int k=(s-j)/2;
			if(k<0)continue;
			if(a[i]==2){
				if(j>=2)dp[i][j-2]=Mod(dp[i][j-2],1ll*dp[i-1][j]*(1ll*j*(j-1)/2%mod)%mod);
				if(k>=2)dp[i][j+2]=Mod(dp[i][j+2],1ll*dp[i-1][j]*(1ll*k*(k-1)/2%mod)%mod);
				if(k>=1)dp[i][j]=Mod(dp[i][j],1ll*dp[i-1][j]*k%mod*(j+1)%mod);
			}else{
				if(j>=1)dp[i][j-1]=Mod(dp[i][j-1],1ll*dp[i-1][j]*j%mod);
				if(k>=1)dp[i][j+1]=Mod(dp[i][j+1],1ll*dp[i-1][j]*k%mod);
			}
		}
		s-=a[i];
	}
	printf("%d\n",dp[n][0]);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```
作者以为只能是 01 矩阵，调了半个小时。什么时候才能不看错题啊。

---

## 作者：_abcd_ (赞：0)

约定：$ \sum\limits_{i=1}^N R_i = n,\sum\limits_{i=1}^N C_i = m,\sum\limits_{i=1}^N [R_i=2] = ca,\sum\limits_{i=1}^N [C_i=2]=cb $。

称 $R_i=2$ 的行为二类行，$R_i=1$ 的行为一类行，列同理。

首先发现当 $ n \neq m $ 时，显然无解。

考虑 $ n = m $ 的情况。我们可以将这个问题转化成小球连线问题，左边第 $i$ 个小球向右边第 $j$ 个小球连线表示将 $a_{i,j}$ 加 $1$，这样答案就为 $n!$。

但是显然没有这么简单。我们发现，当两个 一类行连向一个 二类列，那么答案就会被算两次。一个二类行连向两个一类列和一个二类行连向一个二类列同理。可以参考下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/tgpy5tvm.png)

这两种连线方式都表示
| 1 | 1 |
| -----------: | -----------: |

因此要除以 $2^{ca+cb}$。但是还是不对，因为对于一个二类行连向一个二类的列的情况中（一下称为第三类情况），会同时消耗一个二类行和一个二类列，但是只需要除以 $2$。

因此，我们只需要枚举这一种情况的数量，然后对于其他情况直接算就行了。这个可以通过容斥解决，具体的，我们钦定有 $i$ 个第三类情况，那么想算出有多少种连线方式有恰好 $i$ 个第三类情况，即不存在其他的第三类情况，只需要再钦定有 $j$ 个多余的第三类情况，总共就有 $i+j$ 个第三类情况，对应的连线方式有 $\frac {C_{ca}^i \times A_{cb}^i \times C_{ca-i}^j \times A_{cb-i}^j \times 2^j \times (n-2i-2j)!}{2^{ca-i+cb-i}}$ 种，意思是先选出 $i$ 个二类行，然后每个二类行选一个二类列连线，再在剩余的二类行中选出 $j$ 个并连线，同时这 $j$ 个有两种连法（就是我的第一个连你的第一个，或者我都第二个连你的第一个），因此要乘上 $2^{j}$ 种连接方式，至于其他没有被枚举到的小球随意连线即可，同时要除以 $2^{\text{剩下的二类行列的数量}}$，原因上面解释过。对于每个 $j$ 对应的方案数，乘上 $(-1)^j$，再求和就行了。

总结一下，答案为

$$\sum\limits_{i=0}^{min(ca,cb)} \sum\limits_{j=0}^{min(ca,cb)-i} (-1)^j \times \frac {C_{ca}^i \times A_{cb}^i \times C_{ca-i}^j \times A_{cb-i}^j \times 2^j \times (n-2i-2j)!}{2^{ca-i+cb-i}} $$

附上代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define il inline
#define pn putchar('\n')
#define maxint 2147483647
#define min(x,y) (x<y?x:y)
#define max(x,y) (x>y?x:y)
#define maxn 10005
#define int ll
#define mod 998244353
using namespace std;
int N,n,m,ca,cb,ans;
int jc[maxn],inv[maxn],mi[maxn];
il int A(int x,int y)
{
    if(x<y)return 0;
    return jc[x]*inv[x-y]%mod;
}
il int C(int x,int y)
{
    return A(x,y)*inv[y]%mod;
}
il int ksm(int x,int y)
{
    int ret=1;
    while(y)
    {
        if(y&1)ret=ret*x%mod;
        x=x*x%mod,y>>=1;
    }
    return ret;
}
il void upd(int &x,int y)
{
    x+=y;
    if(x>=mod)x-=mod;
    if(x<0)x+=mod;
}
signed main()
{
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    #endif
    n=1e4;
    jc[0]=1;
    for(int i=1;i<=n;i++)
        jc[i]=jc[i-1]*i%mod;
    inv[n]=ksm(jc[n],mod-2);
    for(int i=n;i;i--)
        inv[i-1]=inv[i]*i%mod;
    mi[0]=1;
    for(int i=1;i<=n;i++)
        mi[i]=mi[i-1]*2%mod;
    n=0;
    scanf("%lld",&N);
    for(int i=1;i<=N;i++)
    {
        int x;
        scanf("%lld",&x);
        if(x==2)
            ca++;
        n+=x;
    }
    for(int i=1;i<=N;i++)
    {
        int x;
        scanf("%lld",&x);
        if(x==2)
            cb++;
        m+=x;
    }
    if(n!=m)return puts("0"),0;
    for(int i=0;i<=ca&&i<=cb;i++)
    {
        int ss=0;
        for(int j=0,fl=1;i+j<=ca&&i+j<=cb;j++,fl*=-1)
            upd(ss,fl*C(ca,i)*A(cb,i)%mod*C(ca-i,j)%mod*A(cb-i,j)%mod*mi[j]%mod*jc[n-2*i-2*j]%mod);
        ss=ss*ksm(mi[ca-i+cb-i],mod-2)%mod;
        upd(ans,ss);
    }
    printf("%lld",ans);
    return 0;
}
```

---

