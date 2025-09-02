# 「JYLOI Round 1」性状

## 题目描述

小郭给你 $(n + 1)$ 个非负整数 $a_0 \sim a_n$，对于任意 $0 \leq i \leq n$ 有 $a_i \in \{0, 1, 2\}$，其中 $a_i$ 表示第 $i$ 个人的基因中控制双眼皮的显性基因个数，在下文中也代表着这个生物。

现在对于原序列中的任意一个子序列 $b_{c_1} \sim b_{c_m}$（其中 $1 \leq c_i < c_{i + 1} \leq m$，并且 $1 \leq i < m \leq n$），将 $a_0$ 和 $b_{c_1}$ 进行交配，得到子一代，并将子一代和 $b_{c_2}$ 交配，得到子二代，以此类推，最后将子 $(m - 1)$  代与 $b_{c_m}$ 进行交配，得到子 $m$ 代，我们定义这个子序列的价值为子 $m$ 代为双眼皮的概率。

由于他很忙，于是他现在请你帮他求出所有子序列的价值的平均值在模 $998244353$ 意义下的值。

**提示**：把 0、1、2 分别看作 ``aa``、``Aa``、``AA`` 三种字符串，两个生物进行交配，就是选择每个字符串间长度为 1 的子序列进行大写字母在前，小写在后的合并，其中这样的一个字符串为子代一种可能的基因组成。

其中大写字母开头的为显性性状，小写字母开头为隐性性状。双眼皮为显性性状，单眼皮为隐性性状，结果 ``aa``、``Aa``、``AA`` 分别再对应回数字 0、1、2。

**注意**，在本题中，我们认为眼皮的单双由位于常染色体上的一对等位基因 ``A`` 和 ``a`` 控制，其中 ``A`` 相对 ``a`` 为完全显性。且该性状的遗传遵循孟德尔的分离定律，并不考虑表观遗传、从性遗传、突变、基因表达的相互影响，所有基因型的配子和个体均无致死概率，所有个体均能产生可育配子。

## 说明/提示

## 样例 1 解释

子序列 $\{1\}$、$\{0\}$、$\{1, 0\}$ 的价值分别为 $1$、$1$ 和 $\dfrac{3}{4}$，平均价值为 $\dfrac{11}{12}$，对 $998244353$ 取模后的结果为 $415935148$。

## 数据范围

对于 $100\%$ 的测试数据，$1 \leq n \leq 5 \times 10^6, a_i \in \{0, 1, 2\}$。

对于测试点 1，$n = 1$。

对于测试点 2，$n = 2$。

对于测试点 3~5，$n \leq 5$。

对于测试点 6~10，$n \leq 7.5 \times 10^3$。

本题共有 20 个测试点，每个测试点 5 分，共 100 分。

## 题目来源

「JYLOI Round 1」 B

Idea：abcdeffa & LiuXiangle

Solution：LiuXiangle

Data：LiuXiangle

## 样例 #1

### 输入

```
2
2 1 0```

### 输出

```
415935148```

## 样例 #2

### 输入

```
50
2 1 2 1 0 0 2 2 0 0 1 2 0 0 0 2 0 0 1 2 1 1 1 1 1 0 1 1 1 0 1 2 0 1 1 0 1 1 2 0 1 0 0 1 1 1 0 1 2 1 1```

### 输出

```
576313280```

# 题解

## 作者：zumgze (赞：6)

前置知识： [有理数取余](https://www.luogu.com.cn/problem/P2613)、高中生物

~~另外吐槽一下，我太菜了，没看懂比赛的题解，只好瞎搞了一个做法（算是前缀和吧）~~

首先令$p(i,j)$为以$1...i$为结尾的序列中含有$j$个双眼皮基因的概率和。


所有子序列双眼皮的概率和即为 $p(n,1)+p(n,2)$
。

那么我们的问题就是如何从 $p(i-1,j)$ 求得 $p(i,j)$。

$p(i,j)=p(i-1,j)+$ 以$i$为结尾的序列中含有$j$个双眼皮基因的概率和。

以下分为两种情况： $a_0$直接和$a_i$交配，$a_0$先和$a_{1...i-1}$交配之后才和$a_i$交配。

$a_0$直接和$a_i$交配：直接根据两者基因计算，共九种情况。

$a_0$先和$a_{1...i-1}$交配之后才和$a_i$交配：我们发现，和$a_{1...i-1}$交配的概率就是$p(i-1,j)$，共三种情况，也可以直接计算。

$ a_1 $~$ a_n$的子序列共有$2^n-1$个，统计好答案之后再除以这个数。

### 注意：以上计算过程中需要时时刻刻对mod取模。
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=998244353;
long long a[6000000];
long long p[3];//发现p(i,j)仅与p(i-1,j)有关，所以第一维可省去
long long ksm(long long a,long long n)//用来求逆元
{
	long long ans=1;
	while(n)
	{
		if(n&1)ans=ans*a%mod;
		a=a*a%mod;
		n/=2;
	}
	return ans;
}
int main()
{
	ios::sync_with_stdio(false);
	long long n;
	cin>>n;
	for(long long i=0;i<=n;i++)cin>>a[i];
	long long ans=0;
	long long er=ksm(2,mod-2),si=ksm(4,mod-2);//这两个数用得太多了，就预处理一下
	for(long long i=1;i<=n;i++)
	{
		long long help[3];//储存以i为结尾的序列中含有个双眼皮基因的概率和
		if(a[i]==0)//a0先和a1...ai-1交配之后才和ai交配，分三种情况讨论
		{
			help[0]=(p[0]+p[1]*er%mod)%mod;
			help[1]=(p[2]+p[1]*er%mod)%mod;
			help[2]=0;
		}
		else if(a[i]==1)
		{
			help[0]=(p[0]*er%mod+p[1]*si%mod)%mod;
			help[1]=(p[0]*er%mod+p[1]*er%mod+p[2]*er%mod)%mod;
			help[2]=(p[2]*er%mod+p[1]*si%mod)%mod;
		}
		else if(a[i]==2)
		{
			help[0]=0;
			help[1]=(p[0]+p[1]*er%mod)%mod;
			help[2]=(p[2]+p[1]*er%mod)%mod;
		}
		if(a[0]==0&&a[i]==0)//a0直接和ai交配，分九中情况讨论
		{
			help[0]+=1;
			help[1]+=0;
			help[2]+=0;
		}
		else if(a[0]==0&&a[i]==1)
		{
			help[0]+=er;
			help[1]+=er;
			help[2]+=0;
		}
		else if(a[0]==0&&a[i]==2)
		{
			help[0]+=0;
			help[1]+=1;
			help[2]+=0;
		}
		else if(a[0]==1&&a[i]==0)
		{
			help[0]+=er;
			help[1]+=er;
			help[2]+=0;
		}
		else if(a[0]==1&&a[i]==1)
		{
			help[0]+=si;
			help[1]+=er;
			help[2]+=si;
		}
		else if(a[0]==1&&a[i]==2)
		{
			help[0]+=0;
			help[1]+=er;
			help[2]+=er;
		}
		else if(a[0]==2&&a[i]==0)
		{
			help[0]+=0;
			help[1]+=1;
			help[2]+=0;
		}
		else if(a[0]==2&&a[i]==1)
		{
			help[0]+=0;
			help[1]+=er;
			help[2]+=er;
		}
		else if(a[0]==2&&a[i]==2)
		{
			help[0]+=0;
			help[1]+=0;
			help[2]+=1;
		}
		p[0]=(p[0]+help[0])%mod;
		p[1]=(p[1]+help[1])%mod;
		p[2]=(p[2]+help[2])%mod;
	}
   ans=(p[1]+p[2])%mod;
	cout<<ans*ksm((ksm(2,n)+mod-1)%mod,mod-2)%mod;//最后别忘了要除以子序列的个数
	return 0;
}
```


---

## 作者：daniEl_lElE (赞：0)

## 思路

考虑 $dp_{i,0/1/2}$，表示看到第 $i$ 个人，目前这个人的基因为 `aa,aA,AA` 的所有方案概率之和。考虑对于第 $i$ 个人，我们有两种做法，一种是增加他，一种不增加他，不增加的方案显然：

$$dp_{i,0/1/2}+=dp_{i-1,0/1/2}$$

如果 $a_i=0$，则：

$$dp_{i,0}+=(dp_{i-1,0}+\frac{1}{2}dp_{i-1,1})$$

$$dp_{i,1}+=(dp_{i-1,2}+\frac{1}{2}dp_{i-1,1})$$

如果 $a_i=1$，则：

$$dp_{i,0}+=(\frac{1}{2}dp_{i-1,0}+\frac{1}{4}dp_{i-1,1})$$

$$dp_{i,0}+=(\frac{1}{2}dp_{i-1,0}+\frac{1}{2}dp_{i-1,1}+\frac{1}{2}dp_{i-1,2})$$

$$dp_{i,2}+=(\frac{1}{2}dp_{i-1,2}+\frac{1}{4}dp_{i-1,1})$$

如果 $a_i=2$，则：

$$dp_{i,2}+=(dp_{i-1,2}+\frac{1}{2}dp_{i-1,1})$$

$$dp_{i,1}+=(dp_{i-1,0}+\frac{1}{2}dp_{i-1,1})$$

按转移方程转移即可，复杂度 $\Theta(n)$，即可通过本题。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return ans;
}
int dp[5000005][4];
int a[5000005];
int inv2=499122177;
signed main(){
	int n;
	cin>>n;
	for(int i=0;i<=n;i++) scanf("%lld",&a[i]);
	dp[0][a[0]]=1;
	for(int i=1;i<=n;i++){
		dp[i][0]=dp[i-1][0];
		dp[i][1]=dp[i-1][1];
		dp[i][2]=dp[i-1][2];
		if(a[i]==0){
			//j=0
			dp[i][0]=(dp[i][0]+dp[i-1][0])%mod;
			//j=1
			dp[i][0]=(dp[i][0]+inv2*dp[i-1][1]%mod)%mod;
			dp[i][1]=(dp[i][1]+inv2*dp[i-1][1]%mod)%mod;
			//j=2
			dp[i][1]=(dp[i][1]+dp[i-1][2]%mod)%mod;
		}
		if(a[i]==1){
			//j=0
			dp[i][0]=(dp[i][0]+inv2*dp[i-1][0]%mod)%mod;
			dp[i][1]=(dp[i][1]+inv2*dp[i-1][0]%mod)%mod;
			//j=1
			dp[i][0]=(dp[i][0]+inv2*inv2%mod*dp[i-1][1]%mod)%mod;
			dp[i][1]=(dp[i][1]+inv2%mod*dp[i-1][1]%mod)%mod;
			dp[i][2]=(dp[i][2]+inv2*inv2%mod*dp[i-1][1]%mod)%mod;
			//j=2
			dp[i][2]=(dp[i][2]+inv2*dp[i-1][2]%mod)%mod;
			dp[i][1]=(dp[i][1]+inv2*dp[i-1][2]%mod)%mod;
		}
		if(a[i]==2){
			//j=0
			dp[i][1]=(dp[i][1]+dp[i-1][0]%mod)%mod;
			//j=1
			dp[i][2]=(dp[i][2]+inv2*dp[i-1][1]%mod)%mod;
			dp[i][1]=(dp[i][1]+inv2*dp[i-1][1]%mod)%mod;
			//j=2
			dp[i][2]=(dp[i][2]+dp[i-1][2])%mod;
		}
	}
	dp[n][a[0]]=(dp[n][a[0]]+mod-1)%mod;
	cout<<(dp[n][1]+dp[n][2])%mod*qp(qp(2,n)-1,mod-2)%mod;
	return 0;
}
```

---

