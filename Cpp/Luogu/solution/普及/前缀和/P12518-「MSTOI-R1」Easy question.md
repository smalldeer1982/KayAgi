# 「MSTOI-R1」Easy question

## 题目描述

给一个序列 $a$，长度为 $n$，你需要进行下面三种操作：

1. `1 l r` 表示求 $\sum\limits_{i=l}^{r}a_i$。

2. `2 l r k` 表示求 $\sum\limits_{i=l}^{r}{a_i}^k$。

3. `3 l r` 表示求 $(r-l+1)\cdot \sum\limits_{i=l}^r\left(a_i-\overline a\right)^2$，其中 $\overline a$ 为序列中 $[l,r]$ 的平均数。

输出答案对 $998244353$ 取模的结果。

## 说明/提示

**样例解释：**

第一次询问求 $[3,5]$ 的和，答案为 $4+2+3=9$。

第二次询问求 $[1,5]$ 的和，答案为 $1+5+4+2+3=15$。

第三次询问答案为 $1^3+5^3+4^3=1+125+64=190$。

第四次询问，$[2,3]$ 的平均数为 $\frac{5+4}{2}=4.5$，答案为 $(3-2+1)\times((5-4.5)^2+(4-4.5)^2)=2\times(0.25+0.25)=1$。 

**数据范围：**

对于 $20\% $ 的数据，$1\leq n,q,a_i\leq 100,1\leq k\leq 3$。

另有 $10\%$ 的数据，只有询问 $1$。

另有 $10\%$ 的数据，只有询问 $2$。

对于 $70\%$ 的数据，$1\leq n,q\leq10^5 $，这些测试点包括了只有询问 $1$ 和只有询问 $2$ 的测试点。

对于 $100\%$ 的数据，$1\leq n,q\leq10^6,1\leq k\leq 20,1\leq a_i\leq10^9$。

保证所有询问的答案都是整数。

**本题输入输出数据较大，请务必使用较快的读入输出方式。**

## 样例 #1

### 输入

```
5 4
1 5 4 2 3
1 3 5
1 1 5
2 1 3 3
3 2 3```

### 输出

```
9
15
190
1```

# 题解

## 作者：MinimumSpanningTree (赞：10)

[题目链接](https://www.luogu.com.cn/problem/P12518)

由于我们在操作时需要用到区间和以及区间次方和，而 $k$ 最大只有 $20$，所以完全可以直接开一个数组维护次方和。定义 $s_{i,j}$ 表示 $\sum\limits_{k=1}^{i}a^j$。

对于操作 1，直接输出预处理的一次方区间和 $s_{r,1}-s_{l-1,1}$。

对于操作 2，直接输出预处理的 $k$ 次方和 $s_{r,k}-s_{l-1,k}$。

对于操作 3，我们考虑将式子拆开。

$$
\begin{aligned}
{}&(r-l+1) \sum_{i=l}^r\left(a_i-\overline a\right)^2&\\
=&(r-l+1)\sum_{i=l}^{r}{a_i}^2+\overline a^2-2a_i\overline a&\\
=&(r-l+1)[(\sum_{i=l}^r{a_i}^2)+(r-l+1)\overline a^2-2\overline a(\sum_{i=l}^ra_i)]&\\
=&(r-l+1)[(\sum_{i=l}^r{a_i}^2)+(\sum_{i=l}^ra_i)\overline a-2\overline a(\sum_{i=l}^ra_i)]&\\
=&(r-l+1)[(\sum_{i=l}^r{a_i}^2)-\overline a(\sum_{i=l}^ra_i)]&\\
=&(r-l+1)(\sum_{i=l}^r{a_i}^2)-(r-l+1)\overline a(\sum_{i=l}^ra_i)&\\
=&(r-l+1)(\sum_{i=l}^r{a_i}^2)-(\sum_{i=l}^ra_i)^2
\end{aligned}
$$

再使用预处理的 $s$ 数组，可以得到 $ans=(r-l+1)(s_{r,2}-s_{l-1,2})-(s_{r,1}-s_{l-1,1})^2$。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
const int N=1e6+100,K=25;
const ll MOD=998244353;
int n,q,op;
ll a[N],s[N][K],u,v,w,ans;
int main() 
{
	//freopen("data1.in","r",stdin); 
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) 
	{
		scanf("%lld",&a[i]);
		s[i][0]=1;
		for(int j=1;j<=20;j++) s[i][j]=s[i][j-1]*a[i]%MOD;
		for(int j=1;j<=20;j++) 
		{
			s[i][j]=(s[i][j]+s[i-1][j])%MOD; 
			//printf("%d %d %lld\n",i,j,s[i][j]);
		}
	}
	while(q--)
	{
		scanf("%d%lld%lld",&op,&u,&v);
		if(op==1) ans=(s[v][1]+MOD-s[u-1][1])%MOD;
		else if(op==2)
		{
			scanf("%d",&w);
			ans=(s[v][w]+MOD-s[u-1][w])%MOD;
		}
		else ans=((v-u+1)*(s[v][2]+MOD-s[u-1][2])%MOD+MOD-(s[v][1]+MOD-s[u-1][1])%MOD*(s[v][1]+MOD-s[u-1][1])%MOD)%MOD;
		printf("%lld\n",ans);
	} 
	return 0;
}
```

---

## 作者：er_mao_jpg (赞：4)

## P12518 「MSTOI-R1」Easy question
### 写在之前
（机房大佬：我第一眼以为有修改操作，就想到建20棵树。）~~实际上不用建20棵树，学算法学多了导致的。~~
### 题意大意

给一个序列 $a$，长度为 $n$，你需要进行下面三种操作：

1. `1 l r` 表示求 $\sum\limits_{i=l}^{r}a_i$。

2. `2 l r k` 表示求 $\sum\limits_{i=l}^{r}{a_i}^k$。

3. `3 l r` 表示求 $(r-l+1)\cdot \sum\limits_{i=l}^r\left(a_i-\overline a\right)^2$，其中 $\overline a$ 为序列中 $[l,r]$ 的平均数。

### 思路分析
#### 操作1
发现就是求序列区间 $[l,r]$ 的和，于是很容易想到前缀和做法，前缀和用数组 $sum$ 存储。

#### 操作2
求序列区间 $[l,r]$ 中每个数的 $k$ 次方的和。一通计算下来发现没有时间复杂度合理的简便计算。然后想到在输入原序列时对每个数的 $k$ 次方进行预处理，同样可以进行前缀和操作，于是将前缀和数组开成二维数组，其中 $sum_{i,j}$ 表示序列前 $i$ 个数的 $j$ 次方的和。

#### 操作3
一个形似求方差的操作，我们可以将这个式子先写出来：设 $ans = (r-l+1)\cdot \sum\limits_{i=l}^r\left(a_i-\overline a\right)^2$。

则可以推出如下式子。

$\begin{aligned} 
ans &= (r - l + 1) \cdot [(a_l - \overline a)^2 + (a_{l+1} - \overline a)^2 + \cdots + (a_r -\overline a)^2] \\
&= (r - l + 1) \cdot [(a_l^2 - 2a_l\overline a + {\overline a}^2) + (a_{l+1}^2 - 2a_{l+1}\overline a + {\overline a}^2) + \cdots + (a_r^2 - 2a_r\overline a + \overline a^2)] \\
&=(r - l + 1) \cdot [\sum\limits_{i=l}^{r}{a_i}^2 - 2\overline a \cdot \sum\limits_{i=l}^{r}{a_i} + (r - l + 1) \cdot \overline a^2]
\end{aligned}$

而根据 $\overline a = \frac{\sum\limits_{i=l}^{r}{a_i}}{r-l+1}$，将 $(r - l + 1)$ 乘入括号，得到式子：$ans = (r - l + 1)\cdot \sum\limits_{i=l}^{r}{a_i}
^2 - 2(\sum\limits_{i=l}^{r}{a_i})^2 + (\sum\limits_{i=l}^{r}{a_i})^2$。

最后化简可得$ans = (r - l + 1)\cdot \sum\limits_{i=l}^{r}{a_i}
^2 - (\sum\limits_{i=l}^{r}{a_i})^2$。

化简后可知答案一定是一个整数。

而我们已经用了前缀和数组存储了序列前 $i$ 个数的 $2$ 次方的和，因此操作3的时间复杂度为 $O(1)$。
### 代码

```c++
long long n, q;
unsigned long long opt, l, r, k, ans, a;
unsigned long long sum_1, sum_2;
unsigned long long mod = 998244353;
unsigned long long num[1000010];//原数组
unsigned long long sum[1000010][21];//前缀和数组，sum[i][j] 表示序列前i个数的j次方的和 
int main(){
	ios::sync_with_stdio(false);//解绑操作，加快数据输入输出速度 
	cin.tie(0);
	cout.tie(0);
	
	cin >> n >> q;
	for(int i = 1; i <= n; i++){
		cin >> num[i];
		a = num[i];
		for(int j = 1; j <= 20; j++){//前缀和数组预处理 
			sum[i][j] =(sum[i - 1][j] + a + mod) % mod;
			a = a * num[i] % mod;
		}
	}
	
	for(int i = 1; i <= q; i++){
		cin >> opt;
		if(opt == 1){//操作1 
			cin >> l >> r;
			ans = sum[r][1] - sum[l - 1][1];
		} else if(opt == 2){//操作2 
			cin >> l >> r >> k;
			ans = sum[r][k] - sum[l - 1][k];
		}else{//操作3 
			cin >> l >> r;
			sum_1 = sum[r][1] - sum[l - 1][1];//区间和 
			sum_2 = sum[r][2] - sum[l - 1][2];//区间平方和 
			ans = ((sum_2 + mod) % mod * (r - l + 1 + mod) % mod - (sum_1 * sum_1) % mod + mod) % mod;
		}
		ans += mod;
		cout << ans % mod << '\n';
	}
	return 0;
} 
```
### 写在最后
赛时被模数嗯控，最后40分遗憾离场，本蒟蒻要重修语法了（悲）。

帮到你的话请点赞题解喵，点赞题解谢谢喵

---

## 作者：xw_qwq (赞：2)

## P12518 「MSTOI-R1」Easy question
[题目传送门](https://www.luogu.com.cn/problem/P12518)
### 题目思路
前缀和好题。

对于第一问，要我们求如下公式的值：
$$
\sum_{i=l}^{r} a_i
$$
很明显，可以使用最基础的前缀和解决。

对于第二问，要我们求如下公式的值：
$$
\sum_{i=l}^{r} a_i^k
$$
观察到 $1 \le k \le 20$，则我们可以多开一维前缀和数组，记录下所有 $k$ 时的前缀和数组，可以使用双重循环预处理。

对于第三问，考虑拆公式。
$$
(r - l + 1) \cdot \sum_{i=l}^r (a_i -  \overline a)^2
$$
令 $len = r - l + 1$，则可得：
$$
\begin{aligned}
{} & len \cdot \sum_{i=l}^r (a_i -  \overline a)^2 & \\
= & len \cdot \sum_{i=l}^{r} (a_i^2 - 2a_i\overline a + \overline a^2) \\
= & len \cdot (\sum_{i=l}^{r} a_i^2 - 2\overline a\sum_{i=l}^r a_i + len\cdot \overline a^2) \\
\end{aligned}
$$
不妨令 $s_1 = \sum_{i=l}^{r} a_i^2$，$s_2 = \sum_{i=l}^{r} a_i$，则又可得：
$$
\begin{aligned}
{} & len \cdot (\sum_{i=l}^{r} a_i^2 - 2\overline a\sum_{i=l}^r a_i + len\cdot \overline a^2) \\
= & len \cdot (s_1 - 2\overline a \cdot s_2 + len\cdot \overline a^2) \\
= & len \cdot s_1 - len \cdot 2\overline a \cdot s_2 + len^2 \cdot \overline a^2 \\
= & len \cdot s_1 - 2 \cdot s_2^2 + s_2^2 \\
= & len \cdot s_1 - s_2^2 \\
\end{aligned}
$$
那么通过在第二问已经处理好的前缀和即可 $O(1)$ 回答问题。
时间复杂度：$O(kn + q)$。
### code

```cpp
#include <bits/stdc++.h>
#define int unsigned long long
using namespace std;
const int mod = 998244353;
int a[1000005], sum[25][1000005];
signed main()
{
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
	{
		int tmp = a[i];
		sum[1][i] = (sum[1][i - 1] + tmp) % mod;
		for (int j = 2; j <= 20; j++)
		{
			tmp = tmp * a[i] % mod;
			sum[j][i] = (sum[j][i - 1] + tmp) % mod;
		}
	}
	while (q--)
	{
		int op, l, r;
		cin >> op >> l >> r;
		if (op == 1)
			cout << (sum[1][r] - sum[1][l - 1] + mod) % mod << "\n";
		if (op == 2)
		{
			int k;
			cin >> k;
			cout << (sum[k][r] - sum[k][l - 1] + mod) % mod << "\n";
		}
		if (op == 3)
		{
			int len = r - l + 1;
			int s1 = (sum[1][r] - sum[1][l - 1] + mod) % mod;
			int s2 = (sum[2][r] - sum[2][l - 1] + mod) % mod;
			cout << ((len * s2 % mod - s1 * s1 % mod) + mod) % mod << "\n";
		}
	}
	return 0;
}
```

---

## 作者：jcf666 (赞：1)

# 题目大意
根据输入进行以下操作：

1. 求第 $l$ 到第 $r$ 个数字的累加和。

1. 求第 $l$ 到第 $r$ 个数字每个数字的 $k$ 次方的累加和。

1. 求第 $l$ 到第 $r$ 个数字的方差。

# 个人思路
操作 $1$ 可以用前缀和预处理求解，和[这题](https://www.luogu.com.cn/problem/B3612)一样，定义一个数组 $b$ 存储数组 $a$ 的前缀和结果，预处理公式就是 $b_i=a_i+b_{i-1}$，调用公式就是 $b_r-b_{l-1}$。

操作 $2$ 可以也可以用前缀和预处理求解,定义二位数组 $c$，设 $c_{i,j}$ 为 $\sum_{k = 1}^{i} a_k^j$ 取余后的结果，然后就可以用和操作 $1$ 差不多的思路进行前缀和预处理了。

操作 $3$ 就略显麻烦，直接暴力精度问题一大堆，我们可以推一推式子。
$$
\begin{aligned}

(r-l+1)\cdot \sum\limits_{i=l}^r\left(a_i-\overline a\right)^2

&=(r-l+1)\cdot \sum\limits_{i=l}^r\left(a_i^2-2a_i\overline a+\overline a^2\right) \\
&=(r-l+1)\cdot \left(\sum\limits_{i=l}^ra_i^2-2\overline a\sum\limits_ {i=l}^ra_i + \sum\limits_{i=l}^r \overline a^2 \right) \\

\end{aligned}
$$
我们可以发现，$\sum\limits_{i=l}^ra_i$ 和 $\sum\limits_{i=l}^ra_i^2$ 能直接从操作 $1$ 和操作 $2$ 的与处理数组中获取，我将其设为 $sum$ 和 $sum2$，并设 $len$ 为 $r-l+1$，那么式子中的 $\overline a$ 就可以看作 $\frac{sum}{len}$，原式可以化为：
$$
\begin{aligned}
(r-l+1)\cdot \left(\sum\limits_{i=l}^ra_i^2-2\overline a\sum\limits_ {i=l}^ra_i + \sum\limits_{i=l}^r \overline a^2 \right) &= len\cdot \left(sum2-2\cdot\frac{sum}{len}\cdot sum+len\cdot \frac{sum^2}{len^2}\right)\\
&=sum2 \cdot len - 2 \cdot len \cdot \frac{sum}{len} \cdot sum + len^2 \cdot \frac{sum^2}{len^2}\\
&=sum2\cdot len-2\cdot sum^2+sum^2\\
&=sum2\cdot len-sum^2
\end{aligned}
$$
答案就出来了，还没有精度问题烦恼。在编写代码时注意取模的方式，我就是因为这个卡在 $40$ 分好久。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q,op,l,r,k,a[1000005],b[1000005],c[1000005][25];
const int mod=998244353;
int qpow(int a,int b){
	int res=1;
	for(int i=1;i<=b;i++)res=(res*a)%mod;
	return res;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i],b[i]=b[i-1]+a[i];
		for(int j=1;j<=20;j++)c[i][j]=qpow(a[i],j)+c[i-1][j];
	}
	while(q--){
		cin>>op;
		if(op==1){
			cin>>l>>r;
			cout<<(b[r]-b[l-1]+mod)%mod<<"\n";
		}
		if(op==2){
			cin>>l>>r>>k;
			cout<<(c[r][k]-c[l-1][k]+mod)%mod<<"\n";
		}
		if(op==3){
			cin>>l>>r;
			int pf1=(c[r][2]-c[l-1][2])%mod,zh=(b[r]-b[l-1])%mod,len=(r-l+1)%mod;
			cout<<((pf1*len%mod-zh*zh%mod+mod)%mod)<<"\n";
		}
	}
	return 0;
}

```

---

## 作者：W_C_B_H (赞：1)

由于本题只有查询操作，没有修改操作，所以我们可以想到使用前缀和进行预处理。具体地，我们设 $\begin{aligned}sum_{i,j}=\left(\sum_{k=1}^{i}{a_k}^j\right)\bmod 998244353\end{aligned}$，那么：

- 对于操作 $1$，根据前缀和相关知识，输出 $(sum_{r,1}-sum_{l-1,1}+998244353)\bmod 998244353$ 即可（加上 $998244353$ 是因为减法可能减出负数，此时直接取模会 WA，下面同理），实际实现时将其当作 $k=1$ 的操作 $2$ 更简便，时间复杂度 $O(1)$；

- 操作 $2$ 与操作 $1$ 类似，输出 $(sum_{r,k}-sum_{l-1,k}+998244353)\bmod 998244353$ 即可，时间复杂度 $O(1)$；

- 操作 $3$ 需要推一些式子（所以我个人认为这道题难度应该不止橙），我们记 $len=r-l+1$，则：

  $\begin{aligned}
&(r-l+1)\times\sum_{i=l}^r(a_i-\overline a)^2\\
=&len\times\sum_{i=l}^r(a_i-\overline a)^2\\
=&len\times\sum_{i=l}^r({a_i}^2-2a_i\times\overline a+\overline a^2)\\
=&\sum_{i=l}^rlen\times({a_i}^2-2a_i\times\overline a+\overline a^2)\\
=&\sum_{i=l}^rlen\times {a_i}^2-len\times 2a_i\times\overline a+len\times \overline a^2\\
=&\sum_{i=l}^rlen\times {a_i}^2 - \sum_{i=l}^rlen\times 2a_i\times\overline a + \sum_{i=l}^rlen\times \overline a^2\\
=&len\times(sum_{r,2}-sum_{l-1,2}) - 2\sum_{i=l}^r a_i\times(sum_{r,1}-sum_{l-1,1}) + \sum_{i=l}^r(sum_{r,1}-sum_{l-1,1})\times \overline a\\
=&len\times(sum_{r,2}-sum_{l-1,2}) - 2\times(sum_{r,1}-sum_{l-1,1})^2 + (sum_{r,1}-sum_{l-1,1})^2\\
=&len\times(sum_{r,2}-sum_{l-1,2}) - (sum_{r,1}-sum_{l-1,1})^2
\end{aligned}$

  所以我们输出 $len\times(sum_{r,2}-sum_{l-1,2}) - (sum_{r,1}-sum_{l-1,1})^2$ 对 $998244353$ 取模的结果即可，注意要边算边模。显然该式的值（即操作 $3$ 的答案）可以以 $O(1)$ 的时间复杂度求出。

综上，我们可以在 $O(1)$ 的时间复杂度内完成一次查询，总时间复杂度 $O(kn+q)$，可以通过本题。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 1000005
#define K 25
const int mod=998244353;
int n,q,a[N],sum[N][K];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		for(int j=1,p=a[i];j<=K-5;j++)
		{
			sum[i][j]=(sum[i-1][j]+p)%mod;
			p=p*a[i]%mod;
		}
	}
	while(q--)
	{
		int op,l,r,k=1;
		cin>>op>>l>>r;
		if(op==2)
		{
			cin>>k;
		}
		if(op<3)
		{
			cout << ( sum[r][k] - sum[l-1][k] + mod ) % mod << "\n";
		}
		else
		{
			int sum1 = (sum[r][1]-sum[l-1][1]+mod) % mod, sum2 = (sum[r][2]-sum[l-1][2]+mod) % mod;
			cout << ( (r-l+1)*sum2 - sum1*sum1%mod + mod ) % mod << "\n";
		}
	}
	return 0;
}
```

---

## 作者：yihang2011 (赞：0)

### [P12518 「MSTOI-R1」Easy question](https://www.luogu.com.cn/problem/P12518)

数学题，建议评黄/绿。

操作一为区间和，使用前缀和解决即可。

操作二为区间次方和，且发现指数 $k$ 满足 $1 \le k \le 20$，可以借用前缀和的思想，令 $\displaystyle s_{j, k} = \sum^{j}_{i = 1}{a_i^k}$，则 $\displaystyle \sum^{r}_{i = l}{a_i^k} = s_{r, k} - s_{l - 1, k}$。

操作三，考虑拆式子：

首先发现 $\displaystyle \bar{a} = \frac{\sum^r_{i = l}{a_i}}{r - l + 1}$，将其带入。

$$

\begin{aligned}

& (r - l + 1) \cdot \sum^r_{i = l}{(a_i - \bar{a})}^2 \\

= & (r - l + 1) \cdot \sum^r_{i = l}{(a_i - \frac{\sum^r_{i = l}{a_i}}{r - l + 1})}^2 \\

= & (r - l + 1) \cdot \sum^r_{i = l}{[a_i^2 + (\frac{\sum^r_{i = l}{a_i}}{r - l + 1})^2 - 2\frac{\sum^r_{i = l}{a_i}}{r - l + 1} \cdot a_i]} \\

= & (r - l + 1) \cdot [\sum^r_{i = l}{a_i^2} + (r - l + 1)(\frac{\sum^r_{i = l}{a_i}}{r - l + 1})^2 - 2\frac{\sum^r_{i = l}{a_i}}{r - l + 1} \cdot \sum^r_{i = l}{a_i}] \\

= & (r - l + 1) \cdot [\sum^r_{i = l}{a_i^2} + \frac{(\sum^r_{i = l}{a_i})^2}{r - l + 1} - 2\frac{(\sum^r_{i = l}{a_i})^2}{r - l + 1}] \\

= & (r - l + 1) \cdot [\sum^r_{i = l}{a_i^2} - \frac{(\sum^r_{i = l}{a_i})^2}{r - l + 1}] \\

= & (r - l + 1)\sum^r_{i = l}{a_i^2} - (\sum^r_{i = l}{a_i})^2

\end{aligned}
$$

最终，$\displaystyle \sum^r_{i = l}{a_i^2} = s_{r, 2} - s_{l - 1, 2}$，$\displaystyle \sum^r_{i = l}{a_i} = s_{r, 1} - s_{l - 1, 1}$。

操作三的结果为 $(r - l + 1)(s_{r, 2} - s_{l - 1, 2}) - (s_{r, 1}- s_{l - 1, 1})^2$。

具体实现。令 $p_{j, k} = a_j^k$，若直接求 $a_j^k$ 会超时，考虑递推。$p_{j, k} = p_{j, k - 1} \cdot a_j$，$p_{j, 0} = 1$，则 $s_{j, k} = s_{j - 1, k} + p_{j, k}$，这两个数组可以合二为一。注意结果对 $998244353$ 取模。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, q;
long long a[1000010];
long long s[1000010][30];
const int mod = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        s[i][0] = 1;
        for (int j = 1; j <= 20; j++) {
            s[i][j] = s[i][j - 1] * a[i] % mod;
        }
        for (int j = 1; j <= 20; j++) {
            s[i][j] = (s[i - 1][j] + s[i][j]) % mod;
        }
    }
    while (q--) {
        int op, l, r, k;
        cin >> op >> l >> r;
        if (op == 1) {
            cout << (s[r][1] + mod - s[l - 1][1]) % mod << endl;
        } else if (op == 2) {
            cin >> k;
            cout << (s[r][k] + mod - s[l - 1][k]) % mod << endl;
        } else {
            cout << ((r - l + 1) * (s[r][2] + mod - s[l - 1][2]) % mod + mod - (s[r][1] + mod - s[l - 1][1]) % mod * (s[r][1] + mod - s[l - 1][1]) % mod) % mod << endl;
        }
    }
    return 0;
}
```

[AC Record](https://www.luogu.com.cn/record/217562192)

---

## 作者：aaa1145141919810 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/P12518)

说实话，第一眼看到这道题目很像 [P1471 方差](https://www.luogu.com.cn/problem/P1471)，所以自然而然的想到了这道题应该是一道 ~大力推柿子~ 略有思考难度的题目，是一道不错的题

这道题目的解法和它的数据范围有很大联系：$1\le n \le 10^6,1\le k\le20$，我们发现可以开一个大小为 $kn$ 的前缀和数组来记录每一个指数下的前缀和，简单来说就是：定义 $sum_{i,j}=\sum_{k=1}^ia_k^j$。

定义好前缀和数组，操作 1、2 就可以在 $O(1)$ 时间复杂度内解决，输出 $sum_{r,k}-sum_{l-1,k}$ 即可（若是操作 1 则令 $k=1$）

那么接下来就是本题最大难点：操作 3 了。上面的定义和 [P1471 方差](https://www.luogu.com.cn/problem/P1471) 启示我们将后面的完全平方式拆开，从而使用平方和与和来表示这个式子。大力推式子环节在这：

$$\begin{aligned}(r-l+1)\cdot\sum_{i=l}^r(a_i-\overline{a})^2&=(r-l+1)\cdot\sum_{i=l}^r(a_i^2-2a_i\overline{a}+\overline{a}^2)\\&=(r-l+1)\sum_{i=l}^ra_i^2-2(\sum_{i=l}^ra_i)^2+(\sum_{i=l}^ra_i)^2\\&=(r-l+1)\sum_{i=l}^ra_i^2-(\sum_{i=l}^ra_i)^2\\&=(r-l+1)(sum_{r,2}-sum_{l-1,2})-(sum_{r,1}-sum_{l-1,1})^2\end{aligned}$$

这样我们就愉快的使用预处理好的前缀和数组来 $O(1)$ 回答操作 3 了。

思路环节结束，接下来上代码，还有警示后人：**别忘了对 $998244353$ 取模！**


```cpp
#include<bits/stdc++.h>
using namespace std;
using LL = long long;

const LL mod = 998244353;

inline LL read()
{
	LL x = 0, t = 1;
	char ch = getchar();
	while(!isdigit(ch)){if(ch == '-')t=-1;ch = getchar();}
	while(isdigit(ch)){x = x*10 + (ch&15);ch = getchar();}
	return x*t;
}
inline void write(LL x)
{
	int st[105], top = 0;
	if(x < 0){putchar('-');x=-x;}
	do st[++top]=x%10, x/=10; while(x);
	while(top)
	{
		putchar(st[top--]|48);
	}
	return;
} 

const int N = 1e6+5;
int n, q;
LL a[N], sum[N][25];

int main()
{
	n = read(), q = read();
	for(int i = 1; i <= n; i++)a[i] = read();
	
	for(int i = 1; i <= n; i++)
		for(LL j = 1, k = a[i]; j <= 20; j++)
		{
			sum[i][j] = (sum[i-1][j]+k)%mod;
			k = (k*a[i])%mod;
		}
		
	while(q--)
	{
		int opt = read(), l = read(), r = read();
		if(opt == 1)
		{
			write((sum[r][1]-sum[l-1][1]+mod)%mod);
			putchar('\n');
		}
		else if(opt == 2)
		{
			int k = read();
			write((sum[r][k]-sum[l-1][k]+mod)%mod);
			putchar('\n');
		}
		else
		{
			write(((r-l+1)%mod*(sum[r][2]-sum[l-1][2]+mod)%mod-(sum[r][1]-sum[l-1][1]+mod)%mod*(sum[r][1]-sum[l-1][1]+mod)%mod+mod)%mod);//减法要先加 mod 再对 mod 取模
			putchar('\n');
		}
	}
	
	return 0;
}
```

---

