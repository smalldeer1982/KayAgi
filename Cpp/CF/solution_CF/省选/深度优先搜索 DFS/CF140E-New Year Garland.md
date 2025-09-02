# New Year Garland

## 题目描述

As Gerald, Alexander, Sergey and Gennady are already busy with the usual New Year chores, Edward hastily decorates the New Year Tree. And any decent New Year Tree must be decorated with a good garland. Edward has lamps of $ m $ colors and he wants to make a garland from them. That garland should represent a sequence whose length equals $ L $ . Edward's tree is $ n $ layers high and Edward plans to hang the garland so as to decorate the first layer with the first $ l_{1} $ lamps, the second layer — with the next $ l_{2} $ lamps and so on. The last $ n $ -th layer should be decorated with the last $ l_{n} $ lamps, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF140E/42a70ee20282a88c2096038b0f0078e30892d44c.png)

Edward adores all sorts of math puzzles, so he suddenly wondered: how many different ways to assemble the garland are there given that the both following two conditions are met:

1. Any two lamps that follow consecutively in the same layer should have different colors.
2. The sets of used colors in every two neighbouring layers must be different. We consider unordered sets (not multisets), where every color occurs no more than once. So the number of lamps of particular color does not matter.

Help Edward find the answer to this nagging problem or else he won't manage to decorate the Tree by New Year. You may consider that Edward has an unlimited number of lamps of each of $ m $ colors and it is not obligatory to use all $ m $ colors. The garlands are considered different if they differ in at least one position when represented as sequences. Calculate the answer modulo $ p $ .

## 说明/提示

In the first sample the following variants are possible: 121|1|12, 121|1|21, 121|2|12, 121|2|21, 212|1|12, 212|1|21, 212|2|12, 212|2|21. In the second sample the following variants are possible: 12|13, 12|23, 12|31, 12|32 and so on.

 Figure for the first sample: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF140E/43a99e6af3db8b6061dcc0d84dc8f7d3d9524c52.png)

## 样例 #1

### 输入

```
3 2 1000
3 1 2
```

### 输出

```
8
```

## 样例 #2

### 输入

```
2 3 1000
2 2
```

### 输出

```
24
```

## 样例 #3

### 输入

```
1 1 1000
5
```

### 输出

```
0
```

# 题解

## 作者：是个汉子 (赞：28)

同机房大佬[minxu](https://www.luogu.com.cn/user/251572)讲解了这个题，使蒟蒻我受益匪浅。

再加上蒟蒻写的计数DP题不超过 0 道，所以遇到这种好题赶紧写题解加深印象。

### Solution

因为每一层之间是有互相影响的，所以不能直接用组合数求解，考虑使用计数DP。

**我们先处理只在一行内的彩球的方案数**

设 $g_{i,j}$ 表示有 $i$ 个小球串起来，一共用了 $j$ 种颜色的方案数。

因为每种颜色是等价的，所以我们可以强制给每个颜色一个编号，并使得编号小的第一次出现在前面，大的在后面。因为这样可以使得转移的时候简单一些，最后求答案的时候乘上一个阶乘即可（他们都说这叫最小表示法）。

现在我们可以写转移方程： 
$$
g_{i,j}=g_{i-1,j-1}+(j-1)\cdot g_{i-1,j}
$$
意思是可以在 $i-1$ 个小球后加一个新颜色的小球或者加一个和第 $i-1$ 个颜色不一样的小球，有 $j-1$ 种颜色选择。

**再思考行与行之间的影响**

设 $f_{i,j}$ 为前 $i$ 行，其中第 $i$ 行选了 $j$ 种颜色的方案数。

如果没有题目中的那个限制，是有一个比较显然的转移方程：
$$
f_{i,j}=\dbinom mjg_{l_i,j}\times \sum_{k=1}^{\min(l_{i-1},m)} f_{i-1,k}
$$
意思就是在前 $i-1$ 层可能的状态基础上，从 $m$ 种颜色中选出 $j$ 种来构成第 $i$ 层

那么加上了限制，就是：
$$
f_{i,j}=\binom mjg_{l_i,j}\times \sum_{k=1}^{\min(l_{i-1},m)} f_{i-1,k}-g_{l_i,j}\times f_{i-1,j}
$$
其实就是减去了一个 $i-1$ 层和 $i$ 层颜色完全相同的情况

此时再把一直没加上的阶乘加上就是 $f_{i,j}=j!\cdot\left(\binom mjg_{l_i,j}\times \sum_{k=1}^{\min(l_{i-1},m)} f_{i-1,k}-g_{l_i,j}\times f_{i-1,j}\right)$ 

而最后的答案是 $ans=\sum_{i=1}^{\min(m,l_n)}f_{n,i}$ 

~~完结撒发~~

等等，不会你以为这就完了吧

**last but not least**

1. 当你敲着敲着发现：因为一个没确定的 $p$ ， $\binom mj$ 仿佛一个毒瘤。你想起了 $exLucas$ 这种代码可能比DP转移方程代码还长的东西。

   但是我们其实不需要。

   因为将 $j!$ 扔回括号里，原式就会变成 $f_{i,j}=A_m^j\times g_{l_i,j}\times \sum_{k=1}^{\min(l_{i-1},m)} f_{i-1,k}-j!\times g_{l_i,j}\times f_{i-1,j}$ 

   此时预处理 $A_m^j$ 和 $j!$ 即可。

2. 现在你打完了整个程序，满心欢喜的交上去，会~~更欢喜~~发现它T飞了，所以我们还得优化**时间**复杂度。

   观察方程可以发现 $\sum_{k=1}^{\min(l_{i-1},m)}f_{i-1,k}$ 才是让你时间复杂度变成 $O((\sum l_i)^2)$ 的罪魁祸首。优化方式是在 $i-1$ 层记录前缀和，这样就可以做到 $O(1)$ 转移。

3. 终于，你开开心心的加上了前缀和，又交了上去，正准备和机房同学炫耀的时候，发现它又M飞了，仔细一看内存是 $250MB$ ，所以还得优化**空间**复杂度。

   继续看方程吧。又发现 $g$ 数组在 $f$ 转移的时候有大用，但是 $f$ 只和它的前一层有关系，所以将可以将它的前一维抹去。

   还有细微的小优化，因为 $A_m^j$ 中底下的 $m$ 是不变的，只有 $j$ 会变，所以这也是个一维数组(●'◡'●)。

时间复杂度： $O(\sum l_i)+O(l_i^2)$ ，空间复杂度： $O(l_i^2+m)$ 

### 代码

```c++
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ll long long

using namespace std;
const int L=5010,N=1e6+10;
int n,m,p;
ll A[N],l[N],f[L],fac[L],tmp[L];//tmp就是滚动数组
int g[L][L];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

inline void init(){
    A[0]=1;
    for(int i=1;i<=m;i++)
        A[i]=A[i-1]*(m-i+1)%p;
    g[0][0]=1;
    for(int i=1;i<=5000;i++)
        for(int j=1;j<=min(i,m);j++){
            g[i][j]=(ll)g[i-1][j]*(j-1)%p+g[i-1][j-1];
            g[i][j]%=p;
        }
    fac[0]=1;
    for(int i=1;i<=5000;i++) fac[i]=fac[i-1]*i%p;
}

int main(){
    n=read();m=read();p=read();
    init();
    for(int i=1;i<=n;i++) l[i]=read();
    ll sum=1,res;
    for(int i=1;i<=n;i++){
        res=0;
        for(int j=1;j<=l[i];j++)
            f[j]=(sum*A[j]%p*g[l[i]][j]%p-g[l[i]][j]*tmp[j]%p*fac[j]%p+p)%p,
        	//防止减法出现负数，所以+p
        	res=(res+f[j])%p;
        sum=res;
        for(int j=1;j<=l[i-1];j++) tmp[j]=0;
        for(int j=1;j<=l[i];j++) tmp[j]=f[j];
    }
    printf("%lld\n",sum);
    return 0;
}
```

看到这里的小伙伴一定发现我直接把最后一层的 $sum$ 输出了。

观察我前缀和优化时间复杂度的式子 $\sum_{k=1}^{\min(l_{i-1},m)}f_{i-1,k}$ 和最后答案的式子 $\sum_{i=1}^{\min(l_n,m)}f_{n,i}$ ，是不是惊奇的发现他们长得一样。

其实是因为虚无的第 $n+1$ 层没有小球，也没有颜色，第 $n$ 层怎么选都行\^o^/

---

## 作者：daniEl_lElE (赞：10)

首先先计算一行 $i$ 个位置 $j$ 种不同颜色的方案数。考虑 $f_{i,j}$。转移只需要考虑选择一个已经用过的颜色或一个未用过的颜色即可。

$$f_{i,j}=f_{i-1,j}\times(j-1)+f_{i-1,j-1}$$

然后考虑如何满足相邻行颜色集合不同的要求。考虑 $g_{i,j}$ 表示 $i$ 行 $j$ 种不同颜色的方案数。转移枚举上一个几种颜色，不同直接随便选颜色集合，相同则需要扣减一样的情况。

$$k\neq j:g_{i,j}\leftarrow g_{i-1,k}\times f_{l_i,j}\times\binom{m}{j}\times j!$$

$$k=j:g_{i,j}\leftarrow g_{i-1,k}\times f_{l_i,j}\times(\binom{m}{j}-1)\times j!$$

计 $h_i=\sum_{j=1}^{l_i}g_{i,j}$。

$$g_{i,j}=f_{l_i,j}\times(h_i\times\binom{m}{j}-g_{i-1,j})\times j!$$

```cpp
#include <bits/stdc++.h>
#define int long long
#pragma GCC optimize(2,3,"Ofast","inline")
using namespace std;
int mod;
int qp(int a,int b){
	if(b<0){
		return qp(qp(a,mod-2),-b);
	}
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
}
int C[5005],fac[5005];
int dp[5005][5005];
int f[5005],g[5005];
signed main(){
	int n,m; cin>>n>>m>>mod;
	int l[n+1]; l[0]=0; for(int i=1;i<=n;i++) cin>>l[i];
	C[0]=fac[0]=1;
	for(int i=1;i<=min(5000ll,m);i++) C[i]=C[i-1]*(m-i+1)%mod,fac[i]=fac[i-1]*i%mod;
	dp[0][0]=1;
	for(int i=1;i<=5000;i++){
		for(int j=0;j<=5000;j++){
			if(j>1) (dp[i][j]+=dp[i-1][j]*(j-1))%=mod;
			(dp[i][j+1]+=dp[i-1][j])%=mod;
		} 
	}
	f[0]=1;
	for(int i=1;i<=n;i++){
		int sum=0; 
		for(int j=0;j<=l[i-1];j++){
			(sum+=f[j])%=mod;
		}
		for(int j=0;j<=l[i];j++){
			g[j]=sum*C[j]%mod*dp[l[i]][j]%mod;
			if(j<=l[i-1]) (g[j]+=mod-f[j]*fac[j]%mod*dp[l[i]][j]%mod)%=mod;
		}
		for(int j=0;j<=l[i];j++) f[j]=g[j];
	}
	int ans=0;
	for(int i=0;i<=l[n];i++) (ans+=f[i])%=mod;
	cout<<ans;
	return 0;
} 
```

---

## 作者：小超手123 (赞：5)

##### 题意：

用 $m$ 种颜色的彩球装点 $n$ 层的圣诞树。圣诞树的第 $i$ 层恰由 $l_{i}$个彩球串成一行，且同一层内的相邻彩球颜色不同，同时相邻两层所使用彩球的颜色集合不同。求有多少种装点方案。

$n,m \le 10^6, 1 \le l_{i} \le 3 \times 10^3,\sum l_{i} \le 10^7$。

##### 分析：

考虑 dp。

记 $f_{i,j}$ 表示用 $j$ 种颜色布置 $i$ 个球的方案数（钦定第 $x$ 种颜色的球最早出现的位置比 $x+1$ 的小）。因此用 $f_{i,j} \times j!$ 就是原来的方案。

不难得到 $f_{i,j}=f_{i-1,j-1}+f_{i-1,j} \times (j-1)$。要么第 $i$ 个球新用一种颜色，要么用以前的颜色（不能和上一个相同）。

可是题目需要求 $n$ 层耶。再记 $dp_{i,j}$ 表示前 $i$ 层，第 $i$ 层恰用了 $j$ 种颜色的方案数。

如果不考虑相邻两层所使用彩球的颜色集合不同的限制，那么：
$$
dp_{i,j}=C_{m}^{j} \times j! \times f_{l_{i},j} \times \sum_{k=1}^{\min(l_{i-1},m)} dp_{i-1,k}
$$
加上这个限制，只需要减掉相邻两层所用彩球颜色集合一样的方案数：
$$
dp_{i,j}=C_{m}^{j} \times j! \times f_{l_{i},j} \times \sum_{k=1}^{\min(l_{i-1},m)} dp_{i-1,k}-dp_{i-1,j} \times f_{l_{i},j} \times j!
$$
时间复杂度 $O(L^2+\sum L)$。

---

## 作者：minxu (赞：3)

[题目](https://www.luogu.com.cn/problem/CF140E)


可以发现这是计数$dp$

我们考虑如何表示状态 一般状态的设计是问什么设什么

设$g[i][j]$表示第$i$层用$j$种颜色之前随意且合法的方案数

因为要求相邻两行集合不能一样 我们想到可以算出总方案数然后减去重复的即可

那么考虑总方案数如何求 如果在不考虑相邻两行不合法的情况 那么相邻的是互不影响的 所以我们只要求出一行的 再乘法原理即可

我们设$f[i][j]$表示一行前$i$个用了$j$种颜色的方案数 这里我们用一种类似最小表示法的方法 即强制要求第$j+1$种颜色第一次出现的位置大于第$j$种颜色第一次出现的位置

那么转移就有$f[i][j]=f[i-1][j-1]+f[i-1][j]*(j-1)$

意思是如果第$i$位要么是第$j$这种 那么就随便放$j-1$种(不能和上一个相同) 

这样最后再乘个阶乘和组合数就是总方案了

那么 $g[i][j]=\sum_{k=1}^{\min(l[i-1],m)} g[i-1][k]*f[l[i]][j]*C_m^j*j!-g[i-1][j]*j!*f[l[i]][j]$

因为要减去的是集合相同的 所以相当于$j$种是已经固定了 就不用再选$j$种了

$ans=\sum_{i=1}^{\min(m,l[n])}g[n][i]$

然后把第一维滚动一下空间就够了

```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 10;
int n, m, mod;
ll fac[N], c[N], l[N], g[5005], p[5005];
ll f[5005][5005], ans = 1, tmp;
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int main()
{
    cin >> n >> m >> mod;
    for (int i = 1; i <= n; ++i)
        l[i] = read();
    c[0] = 1;
    for (int i = 1; i <= m; ++i)
        c[i] = c[i - 1] * (m - i + 1) % mod;
    f[0][0] = 1;
    for (int i = 1; i <= 5000; ++i)
        for (int j = 1; j <= min(i, m); ++j)
        {
            f[i][j] = (f[i - 1][j] * 1ll * (j - 1) % mod + f[i - 1][j - 1]) % mod;
        }
    fac[1] = 1;
    for (int i = 2; i <= 5000; ++i)
        fac[i] = fac[i - 1] * i % mod;
    for (int i = 1; i <= n; ++i)
    {
        tmp = 0;
        for (int j = 1; j <= min(l[i], 1ll * m); ++j)
            g[j] = (ans * c[j] % mod * f[l[i]][j] % mod - f[l[i]][j] * p[j] % mod * fac[j] % mod + mod) % mod;
        for (int j = 1; j <= min(l[i], 1ll * m); ++j)
            tmp = (tmp + g[j]) % mod;
        ans = tmp;
        for (int j = 1; j <= min(l[i - 1], 1ll * m); ++j)
            p[j] = 0;
        for (int j = 1; j <= min(l[i], 1ll * m); ++j)
            p[j] = g[j];
    }
    printf("%lld", ans);
    return 0;
}
```

---

## 作者：Erica_N_Contina (赞：2)

## 思路

我们把这个问题分成两个问题来考虑。

### 每一层之内的分配方式

由于我们要考虑层与层之间的关系，所以我们就需要知道当前层选择了某些颜色的方案数。故我们不能简单地用排列组合来计算每一层的情况数，而是要使用计数 dp 来统计。



我们记录 $f_{i,j}$ 表示考虑到该层的第 $i$ 个小球。使用了 $j$ 种颜色的情况数量。



我们先不考虑怎么样来计算，而是先通过计算层与层之间的答案数来说明记录 $f$ 数组的必要性。

### 层与层之间的答案

我们要计算层与层之间的答案，那么我们同样记录 $dp_{i,j}$ 表示第 $i$ 层用了 $j$ 种颜色的情况数量。

那么如果没有“相邻的两层的小球集合不相同”这个条件，那么我们转移可以写成：

$dp_{i,j}=C(m,j)\times f_{l_i,j}\times \sum_{k=1}^{s_{i-1}} dp_{i-1,k}$，这里的 $s_i$ 定义为 $s_i=\min(l_i,m)$ 即最多可能的颜色种类数量，转移 $\sum $ 上面的项目是 $s_{i-1}$ 而不是 $s_i-1$。因为我们要枚举使用了那些颜色，从 $m$ 种中选择 $j$ 种。

于是很显然，我们要使用到 $f$ 数组的信息。

现在我们再考虑“相邻的两层的小球集合不相同”这个条件这个条件。那么很显然，我们只需要把“相邻的两层的小球集合相同”这个情况减去即可。

转移为 $dp_{i,j}=C(m,j)\times f_{l_i,j}\times \sum_{k=1}^{s_{i-1}} dp_{i-1,k}-f_{l_{i},j}\times dp_{i-1,j}$，注意这里的 $f_{l_{i},j}\times dp_{i-1,j}$。



现在我们回去考虑怎么样来计算 $f_{i,j}$。

其实很简单，因为对于每一层内部，相邻的小球的都不相同，所以 $f_{i,j}=f_{i-1,j}\times (j-1)+f_{i-1,j-1}$，注意这里的 $f_{i-1,j}\times (j-1)$ 即没有添加新的颜色的球，但是加入的求可能是前面j种颜色中的 $j-1$ 种（有一种不能取即和它前面的那个球一样的颜色不能取）

### 最后问题&优化

但是还有最后一个问题，那就是我们考虑取的颜色是默认从 $1\sim j$ 排序的对吧？但是实际上可能不是这样排序的。所以我们要对 $j$ 种颜色考虑其一一映射的情况数。即我们把我们之间讨论的“颜色”全部看成颜色的编号，现在我们要考虑的就是把真实的颜色和颜色编号对应起来。

这里可能需要仔细理解一下。实际就是就是一个全排列，即情况数为 $j!$。



所以最后的转移为 $dp_{i,j}=j!\times C(m,j)\times f_{l_i,j}\times \sum_{k=1}^{s_{i-1}} dp_{i-1,k}-f_{l_{i},j}\times dp_{i-1,j}\times j!$。



有了前车之鉴（~~题解~~）我们知道本题需要滚动数组。那么很简单，$dp_{i,j}$ 只需要用到 $dp_{i-1,k}$ 的信息，但是我们不知道 $k,j$ 之间的关系，恐怕不能优化掉一个维度，只能写滚动数组。

对于转移方程中的项目 $j!\times C(m,j)$，我们将其展开后可以发现：

$j!\times C(m,j)=j!\times \frac{A(m,j)}{j!}=A(m,j)$。所以我们可以直接展开成排列数。

还有一点，就是对于项目 $\sum_{k=1}^{s_{i-1}} dp_{i-1,k}$，我们要使用前缀和的优化。

**没错本题卡常。**

## 代码

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . FancyKnowledge .
       . Prove Yourself .
/*////////ACACACACACACAC///////////

//
#include<bits/stdc++.h>

//
#define int long long
#define ull unsigned long long
#define db double
#define endl '\n'
#define err(fmt, ...) fprintf(stderr, "[%d] : " fmt "\n", __LINE__, ##__VA_ARGS__)
///*
#define pr pair<double,int>
#define pf first
#define ps second
#define pb push_back
//*/

//
using namespace std;
//
const int N=1e6+5;
const int M=5e3+5;
int MOD;
const int MMOD=903250223;
const int INF=1e9;
const int IINF=1e18;
const db eps=1e-9;
//
int n,m,dp[N],b,q,fac[N],op,idx,l[N],ans,res,tmp,qzh[N];
int dpi[N];//滚动数组
int f[M][M];
int tot,A[N];
int L;
vector<int> e[N];

/*
//I think you won't use these...

int rd() {}
int ksm(int c,int k,int p) {}
//*/



void init(){
	//nothing to init?
	A[0]=1;
    for(int i=1;i<=5000;i++)A[i]=A[i-1]*(m-i+1)%MOD;//预处理排列数
    fac[0]=1;
    for(int i=1;i<=5000;i++){
    	fac[i]=fac[i-1]*i%MOD;//预处理阶乘
	}
	return ;
}



signed main(){

//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	freopen(".txt","w",stderr);

//	cin>>n>>m>>MOD;
	scanf("%lld%lld%lld",&n,&m,&MOD);
	init();
	
	int mxl=0;
	for(int i=1;i<=n;i++){
		scanf("%lld",&l[i]);
//		cin>>l[i];
		mxl=max(mxl,l[i]);
	}
	
	f[0][0]=1;//记得初始值
	for(int i=1;i<=5000;i++){
//		cerr<<endl;-
		for(int j=1;j<=min(i,m);j++){
			f[i][j]=f[i-1][j]*(j-1)%MOD+f[i-1][j-1];
			f[i][j]%=MOD;
//			cerr<<f[i][j]<<' ';
		}
	}
	int sum=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=l[i];j++){
			dp[j]=A[j]*sum%MOD*f[l[i]][j]%MOD-f[l[i]][j]*dpi[j]%MOD*fac[j]%MOD;
			dp[j]=(dp[j]%MOD+MOD)%MOD;
//			cerr<<A[j]<<"=A[j]"<<endl;
//			cerr<<f[l[i]][j]<<"=f[l[i]][j]"<<endl;
//			cerr<<sum<<"=sum"<<endl;
//			cerr<<dp[j]<<"=dp[j]"<<endl;
//			cerr<<endl;
		}
		sum=0;
		memset(dpi,0,sizeof dpi);
		for(int j=1;j<=l[i];j++)dpi[j]=dp[j],sum+=dpi[j],sum%=MOD;
	}
	
	for(int i=1;i<=l[n];i++)ans=(ans+dp[i])%MOD;
	
	printf("%lld\n",ans);
//	cout<<ans<<endl;
	
	return 0;
}

//check your long long and the size of memery!!!

```




---

## 作者：Unstoppable728 (赞：2)

[博客欢迎来踩QAQ](https://www.cnblogs.com/blog-Dr-J/p/10356883.html)

要求相邻两行小球颜色集合不同，并且限制行内小球相邻不同。

由此可得：每行小球排列都是独立与外界的，

所以答案应该是对于所有行的颜色集合分类，在将行内的答案乘到上面。

先考虑如何分类:

我们可以确定对于每行所取的颜色种类$x=|S|$，

若相邻两行$i,j$，其$x_i!=x_j$，那么一定是合法的，有$C_m^x$种选择方法。

而对于相邻两行$x_i=x_j$，对于行$i$的一种方案，只有一种可能使得$S_i=S_j$,

所以可以使用容斥来计算答案

综上所述，按照每行的颜色种类数来分类或许是可行的。

所以说我们表示出答案：

设该行共用$x$种颜色的方案数为$f(x)$，$f(x)$是对于所有的种类进行计数的，所以可以直接与颜色数为$x$的其他计数变量相乘，设第$n$行中颜色为$i$对整体的贡献为$ans_{n,i}$则：

$ans_n=C_m^x*f(x)*ans_{n-1}-f(x)*ans_{n-1,j}$

$ans_n=\sum\limits_{c=1}^{l_n}ans_{n,c}$

用函数$g_{i,j}$表示就是$ans_i=\sum g_{i,j}$表示前$i$行中最后一行用$j$个颜色方案数。

行间计数搞定了，就该考虑如何计算$f(x)$
由于刚才设$f(x)$为该行的方案数。这个看起来不太好求。

考虑什么决定了这个方案数。

是该行的球数以及颜色数。

所以不妨改写一下，$f(i,j)$表示用了$i$个球，共$j$种颜色的方案数，那么第$i$行的$f(x)$重写为$f(l_i,x)$

考虑一个一个来添加球，由于要求和前一个颜色不同，即可获得递推式：

$f(i,j)=f(i-1,j-1)+f(i-1,j)*(j-1)$

由于每次用到没有用过的颜色顺序是有序的，而所求的是对球颜色顺序无要求，那么最后使用的时候应写成：
$j!*f(i,j)$

球颜色数不会多于总数，那么$f(i,j)$，可以用二维数组来储存


最后一个问题就是p不是质数不能直接用逆元。

~~难不成要用拓展Lucas？~~

组合数可以提出来：

那么答案就是：

$g_{i,j}=A_{m}{j}*f(i,j)*\sum{g_{i-1}}-j!*f(i,j)*g_{i-1,j}$

 其中$f_{(i,j)},j!,A_m^j$预处理就可以很愉快地A掉这道题目了
 
 代码：
 ```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long lnt;
lnt n,m,p;
lnt lmax;
lnt Am[50001];
lnt fac[50001];
lnt l[2000000];
lnt f[5010][5010];
lnt g[2][5010];
int main()
{
    scanf("%lld%lld%lld",&n,&m,&p);
    fac[0]=Am[0]=f[0][0]=1;
    for(int i=1;i<=n;i++)
        scanf("%lld",&l[i]),lmax=std::max(lmax,l[i]);
    for(int i=1;i<=lmax;i++)Am[i]=Am[i-1]*(m-i+1)%p;
    for(int i=1;i<=lmax;i++)fac[i]=fac[i-1]*i%p;
    for(int i=1;i<=lmax;i++)for(int j=1;j<=i&&j<=m;j++)
        f[i][j]=(f[i-1][j-1]+f[i-1][j]*(j-1))%p;
    lnt ans=1,sum=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=l[i];j++)
        {
            lnt tmp=(Am[j]*ans-g[i&1^1][j]*fac[j])%p;
            g[i&1][j]=f[l[i]][j]*tmp%p;
            sum+=g[i&1][j];
        }
        ans=(sum%p+p)%p;
        sum=0;
        memset(g[i&1^1],0,sizeof(g[0]));
    }
    printf("%lld\n",ans);
    return 0;
}

```

---

## 作者：high_sky (赞：1)

挺不错的动态规划题目。

## 思路

一看到题目便可以知道每一层和层与层之间是要分开来算的（这种类似的动态规划还有很多）。

我们先看看层与层之间的。

### 层与层

题目要求：**相邻的两层的小球颜色集合不相同**。

那么区分相邻两层小球颜色集合不同可以通过**数量不同来区分**，然后再进行讨论即可。

根据上述，显然地，设 $f_{i,j}$ 表示已经完成前 $i$ 层，到了第 $i$ 层小球颜色集合的数量为 $j$ 的总方案。

我们先抛开重不重复不谈，那么它的总方案肯定是从前面的那一层转移过来，即 $f_{i-1,k}$，其中 $k\in [1,l_{i-1}]$。

那么是不是就是
$$
f_{i,j}=\sum_{k=1}^{l_{i-1}}f_{i-1,k}
$$
呢？显然不是，这里的 $j$ 是数量，并不是选了什么，因此还要有 $C_m^j$ 来确定选 $j$ 种颜色球的方案（这是对于当前 $i$ 的）。

### 每一层

我们还需要当前这一层的贡献，而每一层的贡献求法类似，根据我们的总状态可以设 $g_{i,j}$ 表示长度为 $i$ 的位置给你放 $j$ 种颜色（此处颜色确定，并且按从大到小的顺序排列）的球的放的方案是多少。

转移也是显然的：
$$
g_{i,j}=g_{i-1,j-1}+g_{i-1,j}\times (j-1)
$$
 后面之所以要乘上 $(j-1)$ 是因为有 $j$ 种颜色，并且不能与上一个相等，故为 $(j-1)$ 个。

### 合起来！

我们可以预先求出 $g_{i,j}$，因此这个处理的复杂度为 $\mathcal{O}((\max l_i)^2)$。

根据上述，我们不难把 $f_{i,j}$（不考虑层与层之间的要求）的求法合并为：
$$
f_{i,j}=C_{m}^j\times g_{i,j}\times j! \times \sum_{k=1}^{l_{i-1}}f_{i-1,k}
$$
实际上我们的每一层方案不一定是要从小到大排列的，因此我们乘上 $j!$ 来保证每一种可能（这个可以理解为将这 $j$ 个不同颜色原本按照一个一个编号排着，想通颜色的是同一个标号，然后你决定要将每个编号的每种可能都取到，这样就要乘上 $j!$），还不理解可以参考下述：

>按照原本的转移我得到的所有可能情况是 $\{a_i\}$。
>
>比如说，我有 $j$ 种颜色，将它们依次标号为：$\{1,2,3,\dots,j\}$。
>
>实际上我可以是：$\{2,1,j,\dots,4\}$，或者是 $\{4,1,j-1,\dots,j\}$ 等等都有可能。
>
>但是这所有的情况总和便是 $j!$。触类旁通，枚举所有可能全排列（长度为 $n$）的时间复杂度就是 $\mathcal{O}(n!)$。
>
>如果你还是不能理解就可以用数学的思想考虑：
>
>总共有 $j$ 个位置，我填在第 $1$ 位的方案为 $j$，第 $2$ 位的为 $j-1$。
>
>易有：第 $i$ 位的方案为 $j-i$。
>
>最后填完 $j$ 个位置的方案为 $j!$。

由于模数 $p$ 不一定是质数，这就导致我们的 $C_{m}^j$ 不能用逆元求解，但是我们发现：
$$
P_{m}^j=C_{m}^j\times j!
$$
于是合并一下：
$$
f_{i,j}=P_m^j\times g_{i,j}\times \sum_{k=1}^{l_{i-1}}f_{i-1,k}
$$
真是棒极了！现在我们考虑与上一层不同的情况，我们发现两层颜色集合相等的两种情况的充分条件是 $k=j$。

然后我们又发现，两者颜色集合完全相等在 $C_{m}^j$ 种只有一种情况。

故我们可以得到：
$$
f_{i,j}=P_m^j\times g_{i,j}\times \sum_{k=1}^{l_{i-1}}f_{i-1,k}-f_{i-1,j}\times g_{i,j}\times j!
$$
这个乘上 $j!$ 与上述同理。

### 一些提示（思考后再看）

我给出两个提示：一是怎么求 $P_{m}^j$，二是怎么优化。

有人说：
$$
P_{m}^j=\frac{m!}{(m-j)!}
$$
这不还是要逆元吗？

但我说：
$$
P_m^j=\prod_{i=m-j+1}^mi
$$
而显然：
$$
P_m^0=m
$$
然后从 $i-1$ 做到 $i$ 不就行了，每次只多乘上一个数。

**如何优化？**

其实很简单。

我们发现：$\sum_{k=1}^{l_{i-1}}f_{i-1,k}$ 其实跟 $j$ 没有任何关系，直接在枚举 $i$ 的时候加一下不就完了。

## 代码

令 $L=\max l_i$，总时间复杂度为 $\mathcal{O}(L^2+\sum l_i)$。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define int long long
#define N 1000006
#define M 5005
using namespace std;
int n,m,mod,l[N],g[M][M],mxm,p[N],f[2][M],jc[M];
signed main(){
	cin >> n >> m >> mod;
	for (int i = 1;i <= n;i ++) cin >> l[i],mxm = max(mxm,l[i]);
	jc[0] = 1;
	for (int i = 1;i <= mxm;i ++) jc[i] = jc[i - 1] * i % mod;
	g[1][1] = 1;
	for (int i = 2;i <= mxm;i ++)
		for (int j = 1;j <= min(i,m);j ++)
			g[i][j] = (g[i - 1][j - 1] + g[i - 1][j] * (j - 1) % mod) % mod;
//	cout << g[2][2] << ' ' << p[2] << ' ' << p[1] << endl;
	p[0] = 1;
	for (int i = 1;i <= mxm;i ++)
		p[i] = p[i - 1] * (m - i + 1) % mod;
	for (int j = 1;j <= min(l[1],m);j ++)
		f[1][j] = g[l[1]][j] * p[j] % mod;
	for (int i = 2;i <= n;i ++) {
		int sum = 0;
		for (int k = 1;k <= min(m,l[i - 1]);k ++)
			sum = (sum + f[i - 1 & 1][k]) % mod;
//		cout << sum << endl;
		for (int j = 1;j <= min(m,l[i]);j ++) {
			f[i & 1][j] = sum * g[l[i]][j] % mod * p[j] % mod;
			if (j <= l[i - 1]) f[i & 1][j] = (f[i & 1][j] - f[i - 1 & 1][j] * g[l[i]][j] % mod * jc[j] % mod + 5 * mod) % mod;
//			cout << f[i & 1][j] << endl;
		}
	}
	int ans = 0;
	for (int j = 1;j <= l[n];j ++)
		ans = (ans + f[n & 1][j]) % mod;
	cout << ans;
	return 0;
}
```

提示一个很容易错的点：**直接算 $f_1$ 的时候记得取模，不然大数据过不了**。

---

## 作者：Lu_xZ (赞：0)

[Link](https://www.cnblogs.com/Luxinze/p/18115414#cf140e)

题意：一棵 $n$ 层的树，每层由 $l_i$ 个小球组成。

+ 同一层相邻的小球的颜色都不相同。

+ 相邻的两层的小球颜色集合不相同。

一共有多少种合法装饰方案，对 $p$ 取模。


钦定颜色列表 $[c_1, c_2, c_3, \dots, c_i, \cdots]$，令 $f_{i, j}$ 表示一层内前 $i$ 个位置恰好用前 $j$ 种颜色的方案。

+ 如果 $[1, i - 1]$ 用了 $j - 1$ 种颜色，位置 $i$ 只能放 $c_j$。
+ 如果 $[1, i - 1]$ 用了 $j$ 种颜色，位置 $i$ 可以放 $c_k$，$c_k != a_{i - 1}$。

因此
$$
f_{i, j} = f_{i - 1, j - 1} + f_{i - 1, j} \times (j - 1)
$$

令 $g_{i, j}$ 表示第 $i$ 层，钦定颜色列表，且恰好用 $j$ 种颜色的方案，
$s_i$ 表示第 $i$ 层的方案总数。

由于每层的颜色列表可以随意选择并排列：
$$
s_i = \sum \limits_{j = 1}^{l_i} g_{i, j} \times A_m^j
$$

$g_{i, j}$ 不能从全部 $s_{i - 1}$ 种前置状态转移过来，
如果 $j \le l_{i - 1}$，则有 $g_{i - 1, j} \times j!$ 个状态与当前钦定的颜色集合相同，所以

$$
g_{i, j} = f_{l_i, j} \times (s_{i - 1} - [j \le l_{i - 1}]g_{i - 1, j} \times j!)
$$

注意：
+ 本题的 $p$ 不是特殊的，采用 $A_m^i = \prod \limits_{j = 1}^{i} (m - j + 1)$ 计算。

[submission](https://codeforces.com/contest/140/submission/257700189)

---

## 作者：Benzenesir (赞：0)

>现在小 $A$ 手上有 $m$ 种小球，他要用这些小球装饰一棵圣诞树。
这是一棵神奇的圣诞树，一共有 $n$ 层，每层由 $l_i$ 个小球组成。
对于每一层内部，相邻的小球的颜色都不相同。
同时，外部来看，相邻的两层的小球颜色集合不相同。
现在小 $A$ 想要知道一共有多少种合法装饰方案，答案对 $p$ 取模。
数据范围： ($1≤n,m≤10^6,2≤p≤10^9,1≤l_i≤5000,\sum\limits^n_{i=1}l_i≤10^7$)

DP 好题。

先来看一个子问题，求出长度为 $i$，颜色种类为 $j$ 的相邻不重合的序列数量。

不难考虑 DP： $f_{i,j}=f_{i-1,j}\times (j-1)+f_{i-1,j-1}$

对于行数的问题，颜色是等价的，我们并不关心颜色到底是哪几种，而是关心在当前数量之下，有多少个正确的情况。

设 $dp_{i,j}$ 为考虑了前 $i$ 行，最后一行的颜色种类数为 $j$ 的方案数。

先列出朴素贡献式子，

$dp_{i,j} \leftarrow \sum_{k=1} dp_{i-1,k}\times f_{len_i,j} \times m^{\underline{i}}$

再从其中减去不合法的方案数：

$dp_{i,j} \leftarrow -dp_{i-1,j}*f_{len_i,j} \times j!$

其中第一个柿子可以前缀和优化，$dp$ 数组可以使用 `vector` 来存，代码里用了滚动数组。

```c++
const int N=1e6+10,M=5005;
int n,m,mod;
int len[N];
int f[M][M];
ll dp[2][M],sum[N],fac[N],down[N];

void prepare(){
	fac[0]=1;
	fp(i,1,N-10) fac[i]=(fac[i-1]*i)%mod;
	down[0]=1;
	fp(i,1,m){down[i]=down[i-1]*(m-i+1)%mod;}
}
//f_{i,j}=f_{i-1,j-1}+f_{i-1,j}*(j-1)
//dp_{i,j}=Sum_{i-1}*f_{len_i,j}*m^{\underline{j}} - f_{len_i,j}*j!*dp_{i-1,j}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	n=rd(),m=rd(),mod=rd();
	int maxx=0;
	fp(i,1,n) len[i]=rd(),maxx=max(maxx,len[i]);
	f[1][1]=1;
	prepare();
	fp(i,2,maxx) fp(j,1,min(i,m)) f[i][j]=(f[i-1][j-1]+f[i-1][j]*(j-1)%mod)%mod;
	sum[0]=1;
	fp(i,1,n){
		fp(j,1,min(len[i],m))
			dp[i&1][j]=
				(sum[i-1]*f[len[i]][j]%mod*down[j]%mod+mod-
				f[len[i]][j]*fac[j]%mod*dp[(i-1)&1][j]%mod)%mod;
		fp(j,1,min(len[i],m)) sum[i]=(sum[i]+dp[i&1][j])%mod;
		fp(j,1,min(len[i-1],m)) dp[(i-1)&1][j]=0;
	}
	cout<< sum[n] << endl;
	return 0;
}
```

---

