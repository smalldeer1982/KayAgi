# Beautiful Pairs of Numbers

## 题目描述

The sequence of integer pairs $ (a_{1},b_{1}),(a_{2},b_{2}),...,(a_{k},b_{k}) $ is beautiful, if the following statements are fulfilled:

- $ 1<=a_{1}<=b_{1}&lt;a_{2}<=b_{2}&lt;...&lt;a_{k}<=b_{k}<=n $ , where $ n $ is a given positive integer;
- all numbers $ b_{1}-a_{1} $ , $ b_{2}-a_{2} $ , $ ... $ , $ b_{k}-a_{k} $ are distinct.

For the given number $ n $ find the number of beautiful sequences of length $ k $ . As the answer can be rather large, print the remainder after dividing it by $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

In the first test sample there is exactly one beautiful sequence: $ (1,1) $ .

In the second test sample, the following sequences are beautiful:

- $ (1,1) $ ;
- $ (1,2) $ ;
- $ (2,2) $ .

In the fourth test sample, the following sequences are beautiful:

- $ (1,1) $ ;
- $ (1,2) $ ;
- $ (1,3) $ ;
- $ (2,2) $ ;
- $ (2,3) $ ;
- $ (3,3) $ .

In the fifth test sample, the following sequences are beautiful:

- $ (1,1),(2,3) $ ;
- $ (1,2),(3,3) $ .

In the third and sixth samples, there are no beautiful sequences.

## 样例 #1

### 输入

```
6
1 1
2 1
2 2
3 1
3 2
3 3
```

### 输出

```
1
3
0
6
2
0
```

# 题解

## 作者：是个汉子 (赞：9)

蒟蒻觉得大佬写的题解过于深奥，所以自己写一篇加深记忆。

### 题意

在一个长度为 $n$ 的序列中，找 $k$ 个**长度互不相同**的区间**互不重叠**，求方案数。

### Solution

经过简单的计算，发现普通的组合数并不能直接把方案数算出来，因为要考虑的情况实在太多了。那么我们可以考虑另一种能够算出方案数的方法——计数DP。

在上面的题意中，我将本题目的重点**加粗**了。那么我们可以设 $f_{i,j}$ 表示 $i$ 个不同的区间，总长度为 $j$ 且区间长度递增的方案数（为什么要递增下面会说）。则状态转移方程为 $f_{0,0}=1,f_{i,j}=f_{i,,j-i}+f_{i-1,j-i}$ ，指的是可以将原方案的 $i$ 个区间都加上一，或者加上一再多一个长度为 $1$ 的区间。

那么这个东西和答案有什么关系呢？

这里我们先把最后答案的式子写出来， $ans=k!\sum\limits_{i=1}^n\binom {n-i+k}kf_{k,i}$ 

意思是枚举区间总长 $i$ ，会出现 $n-i$ 的空隙，那么就是在 $n-i$ 的空隙和 $k$ 个区间中选 $k$ 个区间（或者像上面那份题解一样，将区间看成点），那么那个 $i$ 就是要用到 $f$ 的地方，但是因为是**递增**，所以要乘上 $A_k^k=k!$ 代表全排列，此时答案为 $ans=\sum\limits_{i=1}^n\binom {n-i+k}kk!f_{k,i}$ ，将 $k!$ 提前，就是上面的式子了。

因为阶乘，组合数和 $f$ 在运算过程中和 $n,k$ 无关，所以可以提前预处理，直接查询。

小细节：因为如果选择区间长度为 $1,2,3\cdots$ ，可得 $\dfrac {k(k+1)}2\leq1000$ ，解得 $k\leq 45$ ，所以可以特判一下（我特判的50）

```c++
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ll long long

using namespace std;
const int N=1010,mod=1e9+7;
int t,n,k;
ll fac[N],inv[N],f[60][N],ans[N][60];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

inline ll mul(ll a,ll b){return a*(ll)b%mod;}
inline ll add(ll a,ll b){return a+b>mod?a+b-mod:a+b;}

inline ll fpow(ll a,ll b){
    ll res=1;
    while(b){
        if(b&1) res=mul(res,a);
        a=mul(a,a);
        b>>=1;
    }
    return res;
}

inline void init(){
    fac[0]=1;
    for(int i=1;i<=1000;i++) fac[i]=mul(fac[i-1],i);
    inv[1000]=fpow(fac[1000],mod-2);
    for(int i=1000;i>0;i--) inv[i-1]=mul(inv[i],i);
}

inline ll C(ll n,ll m){
    if(n<m) return 0;
    return mul(fac[n],mul(inv[n-m],inv[m]));
}

int main(){
    init();
    f[0][0]=1;
    for(int i=1;i<=50;i++)
        for(int j=i*(i+1)/2;j<=1000;j++)
            f[i][j]=add(f[i][j-i],f[i-1][j-i]);
    for(int i=1;i<=1000;i++)
        for(int k=1;k<=50;k++){
			for(int j=k*(k+1)/2;j<=i;j++){
				ans[i][k]=add(ans[i][k],mul(C(i-j+k,k),f[k][j]));
			}
			ans[i][k]=mul(ans[i][k],fac[k]);
		}
    t=read();
    while(t--){
        n=read();k=read();
        if(k>50) puts("0");
        else printf("%lld\n",ans[n][k]);
    }
    return 0;
}
```



---

## 作者：_determination_ (赞：2)

给出一个只需要会暴力 dp 和基本的前缀和优化就可以做的方法。

首先我们考虑没有长度不同的限制怎么做。

设 $f_{i,j}$ 表示当前我选了 $j$ 个区间，最后一个区间的最后一个位置为 $i$ 的方案数。

显然，$f_{i,j}=\sum_{k=1}^{k\leq i-j} f_{k,j-1}$。接下来考虑怎样加区间长度限制。

再记一维。$f_{i,j,k}$ 表示当前我选了 $j$ 个区间，最后一个区间的最后一个位置为 $i$ 且最后一个区间长度为 $k$ 的方案数。转移方程类似上面，请读者自行思考。

考虑如何统计答案。我们要分 $k$ 段。所以第二维一定为 $k$。剩下的枚举即可。注意到我们 dp 出的分段方案每一段的长度是有序的，所以还要乘上 $k!$ 才是正确答案。

这样我们就得到了一个 $O(n^5+Tn^2)$ 的做法。需要优化。

看到查询部分，我们显然可以直接前缀和记一下即可。那单次查询就是 $O(1)$ 的。

看到预处理部分。这个做法的转移显然也可以前缀和优化至 $O(n^3)$，空间可以滚动数组压一维。注意到区间数最多为 $\sqrt{n}$ 所以我们第二维可以把状态数压到 $\sqrt{n}$。最后复杂度 $O(n^{2.5}+T)$，可以通过。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int inf=0x3f3f3f3f3f3f3f3f;
int f[1010][2][1010],s[1010][2][1010];
int ans[1010][1010];
/*
f[i][j]表示下标到了i分了j段的方案数
转移显然可以前缀和优化做到n^2
但是你会发现多算了一部分
你的区间长度可能会一样 
这样答案就会错
假定区间的长度升序排列
再记一维
f[i][j][k]表示到了i分了j段最后一段的长度是k的方案数
最后算答案的时候就是(\sum f[i][k][j]  )*k! 

n^5的做法，前缀和优化一下能做到n^4，好像可以n^3??? 

预处理出每个f即可n^2统计答案
前缀和优化就可以做到O(1)

但是我前缀和怎么挂了啊 

好了修好了

压一下空间，50pts到手 
50
*/ 
const int mod=1e9+7;
int jc[1010];
void init()
{
	jc[0]=1;
	for ( int i = 1 ; i <= 1000 ; i++ )jc[i]=jc[i-1]*i%mod;
	f[0][0][0]=1;
	int n=1000,k=50;
	for ( int i = 0 ; i <= n ; i++ )
	{
		for ( int j = 0 ; j <= n ; j++ )
		{
			s[i][0][j]=1;
		}
	}
	for ( int j = 1 ; j <= k ; j++ )
	{
		for ( int i = 0 ; i <= n ; i++ )
		{
			for ( int k = 0 ; k <= n ; k++ )
			{
				f[i][j&1][k]=0;
			}
		}
		for ( int i = (j+1)*j/2 ; i <= n ; i++ )
		{
			for ( int kk = j ; kk <= i ; kk++ )
			{
				f[i][j&1][kk]=s[i-kk][(j&1)^1][kk-1];
			}
		}
		for ( int i = 1 ; i <= n ; i++ )
		{
			for ( int k = 1 ; k <= n ; k++ )
			{
				s[i][j&1][k]=s[i-1][j&1][k]+s[i][j&1][k-1]-s[i-1][j&1][k-1]+f[i][j&1][k];
				s[i][j&1][k]%=mod;
			}
		}
		for ( int i = 1 ; i <= n ; i++ )
		{
			ans[i][j]=s[i][j&1][i];
		}
		if(j==1)
		{
			for ( int i = 0 ; i <= n ; i++ )
			{
				for ( int j = 0 ; j <= n ; j++ )
				{
					s[i][0][j]=0;
				}
			}
		}
	}
}
void solve()
{
	int n,k;
	cin >> n >> k;
	if(k*(k+1)/2>n)
	{
		cout <<0<<endl;
		return;
	}
	cout << (ans[n][k]+mod)%mod*jc[k]%mod << endl;
//	cout << ans[n][k]*jc[k]%mod << endl;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
//	freopen("axis.in","r",stdin);
//	freopen("axis.out","w",stdout);
	int T;
	cin >> T;
	init();
	while(T--)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：万圣节哇 (赞：0)

这题竟然这么少做 ， 感觉是个蛮有意思的题啊 qwq ， 可能是我太垃圾了qwq

dp + 组合数学

```cpp
f[i][j]:区间总长度为i，有j个区间，且任意两个区间的长度不同的方案数
```
然后我们搞两个转移 ， 第一个 只需要把每个区间的size都 ++ 就可 ， 第二个我们一就是每个区间 ++ , 再增添一个size == 1的区间

怎么求答案呢 ？ 
答 ： 枚举区间总长度i，把每个区间缩成一个点，这样就有n-i+k个点，从中选出k个作为区间即可，另外这k个区间的大小顺序还没有定，还要乘上一个全排列

```cpp
    int n=1000,K=1000;fac[0]=1;
    for(int i=1;i<=n;++i) fac[i]=(ll)fac[i-1]*i%mod;
    for(int i=0;i<=n;++i) C[i][0]=1;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=i;++j)
            C[i][j]=(ll)(C[i-1][j]+C[i-1][j-1])%mod;
    f[1][1]=1;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=i;++j){
            if(i+j<=n) inc(f[i+j][j],f[i][j]);
            if(i+j+1<=n) inc(f[i+j+1][j+1],f[i][j]);
        }
    int tst=read();
    while(tst--){
        n=read();K=read();
        if(ans[n][K]){printf("%d\n",ans[n][K]);continue;}
        for(int i=K;i<=n;++i)
            inc(ans[n][K],(ll)f[i][K]*C[n-i+K][K]%mod*fac[K]%mod);
        printf("%d\n",ans[n][K]);
    }
    return 0;
```
撒花了 ！ 

---

