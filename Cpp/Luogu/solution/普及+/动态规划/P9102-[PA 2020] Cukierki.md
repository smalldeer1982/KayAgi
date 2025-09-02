# [PA 2020] Cukierki

## 题目描述

**题目译自 [PA 2020](https://sio2.mimuw.edu.pl/c/pa-2020-1/dashboard/) Runda 5 [Cukierki](https://sio2.mimuw.edu.pl/c/pa-2020-1/cuk/)**

Bytie 要去参加 Bitek 的生日聚会。他知道 Bitek 喜欢吃甜食，所以他想送他一些糖果作为礼物。他买了 $n$ 袋糖，其中第 $i$ 袋包含 $a_i$ 个糖果。

然而，这些糖相当重，Bytie 想知道他是否需要把它们全都给 Bitek。他决定，他将选择一个非空的袋装糖果子集，把它们拿给 Bitek，并对他说：「我这里总共有 $x$ 颗糖果，你想要多少？」，其中 $x$ 将是带到派对上的包装里的糖果总数。Bitek 听到这个问题后，可能会选择区间 $[1, x]$ 中的任何整数 $y$。无论 Bitek 的回答如何，他都希望能够从带到派对上的糖中选择一部分（其余的留给自己），这样这些袋糖中的糖果总数正好等于 $y$。当然，不可以撕毁包装纸——给散装的糖果是不礼貌的。

因此，Bytie 在想，他能给 Bitek 带去多少种非空的袋装糖果子集，以便在不考虑 Bitek 的选择的情况下，能够送给他所需数量的糖果。请帮助他计算一下吧！由于这种子集的数量可能非常大，请输出它对 $10^9+7$ 取模后的结果。

## 说明/提示

#### 样例 1 解释

Bytie 可以带去 $8$ 种非空子集：$\{5\}, \{1, 5\}, \{1, 3, 5\}, \{1, 4, 5\}, \{1, 3, 4, 5\}, \{1, 2, 3, 5\}, \{1, 2, 4, 5\}$ 和 $\{1, 2, 3, 4, 5\}$。例如，Bytie 带去的子集是 $\{1,2,4,5\}$，Bitek 想要 $9$ 颗糖果时，Bytie 只能给他第 $1,2$ 包糖。Bytie 不可以带去 $\{1,2,5\}$ 子集，如果 Bitek 想要 $6$ 颗糖的话 Bytie 就犯难了。

------------

#### 数据范围

**本题采用捆绑测试**

对于 $100\%$ 的数据，保证 $1\le n\le 5\times 10^3$，$1\le a_i\le 5\times 10^3$。

## 样例 #1

### 输入

```
5
2 7 4 4 1```

### 输出

```
8```

# 题解

## 作者：ZM____ML (赞：2)

## 思路
比较明显的一道动态规划题。

定义状态 $dp_{i,j}$ 表示前 $i$ 个数能够表达 $1\sim j$ 之间所有的数字，那么我们可以看出，$dp_{i,j}$ 可以从两个状态转移过来：

1. $dp_{i-1,j}$ 不选第 $i$ 个数字。

1. $dp_{i-1,j-a_i}$ 选第 $i$ 个数字。

跟背包的形式很像，因为都是从 $i-1$ 转移过来的，所以说这一维可以滚掉。

为了方便判断，我们把数组排一下序，保证如果当前状态加上 $a_i$ 大于总数之后，那么加上后面的任意一个数都会大于总数。

**注意**：转移时需要保证 $a_i\le j+1$。

## 代码
```c
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=5e3+5,mod=1e9+7;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return x*f;
}
int n,a[N],f[N],ans;
signed main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);
	f[0]=1;
	for(int i=1;i<=n;i++)
		for(int j=N-5;j>=a[i]-1;j--)
			f[min(j+a[i],N-5)]+=f[j],f[min(j+a[i],N-5)]%=mod;
	for(int i=1;i<=N-5;i++)ans=(ans+f[i])%mod;
	printf("%d",ans);
	return 0;
}
```


---

## 作者：MspAInt (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P9102)

略有修改的典题。

首先按直觉 `sort` 一遍。

定义 dp 状态 $dp_{i,j}$ 表示前 $i$ 个数能够表达出区间 $[1,j]$ 的所有数字。

两种转移方式：

1. $dp_{i,j}=dp_{i-1,j}$（表示不选择第 $i$ 个数）。
2. $dp_{i,j}=dp_{i-1,j-a_i}$（表示加入第 $i$ 个数）。

显然 $i$ 这一维可以被滚掉。

特别地，第二种转移时需要保证 $a_i\leq j+1$。因为之前的状态仅能表示到 $j$，后来的数字越来越大，那么 $[j+1,a_i-1]$ 这段区间就不可能被覆盖了。

代码中为方便使用刷表法。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e3+10,mod=1e9+7;
int n,a[N],dp[N],ans;
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	dp[0]=1;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
		for(int j=N-10;j>=a[i]-1;j--)
			dp[min(j+a[i],N-10)]+=dp[j],dp[min(j+a[i],N-10)]%=mod;//下标取min防止爆数组
		//不加数时不变
	for(int i=1;i<=N-10;i++)ans+=dp[i],ans%=mod;
	printf("%d\n",ans);
	return 0;
}
```

不滚动数组：[link](https://www.luogu.com.cn/record/104535288)

滚动数组优化：[link](https://www.luogu.com.cn/record/104535801)

两者在空间上的差距尤为显著。

---

## 作者：_•́へ•́╬_ (赞：2)

感觉见过这题。

## 思路

$a$ 数组升序排序。

考虑 dp，设 $f[x]$，$x$ 就是题面里的意思，表示合法方案数。

转移的时候，$\forall i\in[a-1,+\infin)$，贡献 $f[i]\rightarrow f[i+a]$，意思是可以选上当前这个 $a$。

对于更小的 $i(i<a-1)$，不能选，因为可以原来可以凑出 $[1,i]$，选后可以凑出 $[1,i]\cup[a+1,a+i]$，显然不能凑出 $a-1$。

直接做是 $\mathcal O(n^2a)$ 的。

考虑剪枝。我们发现，$\forall i\in[5000,+\infin)$，它无论如何都是会有转移的，而转移之后 $i$ 更大了，对于之后的 $a$，也是一定会有转移的。所以，$f[5000]$ 与 $f[5001]$ 从此就没有区别了。

改一下状态。
$$
g[x]=\begin{cases}f[x]&x<5000\\\sum\limits_{i=5000}^\infin f[i]\quad&x=5000\end{cases}
$$
酱紫就是 $\mathcal O(na)$ 的。

## code

```cpp
#include<stdio.h>
#include<algorithm>
#define N 5009
#define mod 1000000007
using namespace std;
inline char nc()
{
	static char buf[9999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,9999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int n,a[N],b[N],ans;
main()
{
	read(n);for(int i=0;i<n;read(a[i++]));sort(a,a+n);
	b[0]=1;
	for(int i=0;i<n;++i)for(int j=5000,k;j>=a[i]-1;--j)
	{
		k=min(j+a[i],5000);
		b[k]+=b[j]-mod;b[k]>>31&&(b[k]+=mod);
	}
	for(int i=1;i<N;++i)ans+=b[i]-mod,ans>>31&&(ans+=mod);
	printf("%d",ans);
}
```



---

## 作者：Alice2012 (赞：1)

假设当前已经可以凑出 $[1,x]$ 的糖果，现在来了一堆个数为 $a_i$ 的糖果，那么现在可以凑出的糖果数量为 $[1,x] \cup [a_i+1,a_i+x] \cup a_i$。显然需要满足 $x\geq a_i-1$，不然就没办法凑出 $a_i-1$。

即：若 $a_i\leq x$，则选择 $a_i$ 可以将右边界 $x$ 拓展至 $x+a_i$。不妨称这个过程为“吞并”。

于是考虑从小到大将 $a$ 排序，这样显然不劣，因为这样可以保证新的 $a_i$ 尽量小，更能够满足 $a_i-1\leq x$ 的条件。

然后考虑 DP，$dp_{i,j}$ 表示选到了前 $i$ 堆糖果，目前可以凑出 $[1,j]$ 的方案数。转移如下：

- 不选 $a_i$，即 $dp_{i,j}=dp_{i-1,j}$。
- 选 $a_i$，即对于 $j\geq a_i-1$，$dp_{i,j+a_i}\leftarrow dp_{i-1,j}$。即将右边界 $j$ 拓展至 $j+a_i$。

发现这样设计 $j$ 极大，考虑优化。我们发现，当 $j\geq \max a_i$ 时，无论如何都存在转移，不妨设 $\max a_i=K$，那么 $dp_{i,K}$ 和 $dp_{i,K+1}$ 本质上没有区别，因为它们都可以选择所有的 $a_i$ 进行“吞并”。此时我们将所有 $dp_{i,j},j\geq K$ 都归为一类，计算入 $dp_{i,K}$ 之中。此时 $j$ 最大为 $5\times 10^3$。

最后答案为 $\sum_{i=1}^K dp_{n,i}$。

该算法时间复杂度和空间复杂度均为 $\mathcal{O}(nK)$，可以通过。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e3+5,mod=1e9+7;
int n,ans,a[N],dp[N][N];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	dp[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=a[n];j>=0;j--)dp[i][j]=dp[i-1][j];
		for(int j=a[n];j>=a[i]-1;j--)
			dp[i][min(j+a[i],a[n])]+=dp[i-1][j],dp[i][min(j+a[i],a[n])]%=mod;
	}
	for(int i=1;i<=a[n];i++)ans+=dp[n][i],ans%=mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：_Weslie_ (赞：0)

一道 dp 题。

## Solution P9102

### Idea

我们对 $a$ 数组升序排序。

设 $dp_{i,j}$ 为前 $i$ 个数，保证 $1$ 到 $j$ 区间内所有的数能够全部被包含的方案数。

那么转移就是 $dp_{i,j}=dp_{i-1,j}+dp_{i-1,j-a_i}$。原因也十分简单：选与不选求和。注意转移时**不可以让下标越界**。

第一维可以滚掉。

### Code

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=5005,mod=1000000007;
int a[N],n;
ll dp[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	dp[0]=1;
	for(int i=1;i<=n;i++){
		for(int j=N-5;j>=a[i]-1;j--){
			(dp[min(a[i]+j,N-5)]+=dp[j])%=mod;
		}
	}
	ll ans=0;
	for(int i=1;i<=N-5;i++)ans=(ans+dp[i])%mod;
	printf("%lld",ans);
	return 0;
}
```

### Tip

为什么要升序排序？假如不排序，如果在一次转移中，$dp_k=dp_k+dp_j$，但是 $dp_j$ 还未被转移完，转移就是错误的。

可以用

```
3
1 2 1
```

手搓一下。

---

## 作者：BBD186587 (赞：0)

先将 $a_i$ 从小到大排序。

记 $f_{i,j}$ 表示考虑了前 $i$ 个数的选择情况，能表示出 $1 \sim j$ 中所有数的方案数。

考虑转移：

- 不选第 $i+1$ 个数，则 $f_{i,j} \rightarrow f_{i+1,j}$。
- 选第 $i+1$ 个数。注意此时需要满足 $a_{i+1} \leq j+1$，否则 $[j+1,a_{i+1}-1]$ 这段数就无法表示了（因为 $a_i$ 是排序过的，后面的数只会更大）。转移是 $f_{i,j} \rightarrow f_{i+1,j+a_{i+1}}$。

状态的第二维似乎是 $\sum a_i$ 级别的，但注意到第二维 $> \max a_i$ 后就本质相同了，可以把这些状态压到一起。

```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
using namespace std;
const int N=5010;
const int p=1e9+7;
int n;
int a[N];
int f[N][N];
int MIN(int x,int y){return x<y?x:y;}
void upd(int &x,int y){x+=y;if(x>=p) x-=p;}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1),f[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=a[i]-1;j<N;j++)
			if(f[i-1][j]) upd(f[i][MIN(j+a[i],N-1)],f[i-1][j]);
		for(int j=0;j<N;j++) upd(f[i][j],f[i-1][j]);
	}
	int ans=0;
	for(int i=0;i<N;i++) upd(ans,f[n][i]);
	printf("%d",(ans-1+p)%p);
	return 0;
}
```

---

