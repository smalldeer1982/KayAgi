# Up the Strip

## 题目描述

### 题面描述

你有一张 $ 1 \times n $ 的纸带，由 $ n $ 个格子组成。初始有一个点在 $ n $ 号格子（即左数第 $ n $ 个）中。

假设现在这个点在 $ x\ (x > 1) $ 号格子，每次你可以对这个点进行如下操作中的一种：

1. 减法。选择一个 $ [1, x - 1] $ 中的正整数 $ y $，将点移动到 $ x - y $ 号格子中。

2. 除法。选择一个 $ [2, x] $ 中的正整数 $ z $，将点移动到 $ \lfloor \frac{x}{z} \rfloor $ 号格子中。

当点在 $ 1 $ 号格子中时无法移动，操作结束。

求将点从 $ n $ 号格子移到 $ 1 $ 号格子的方案数，答案对给定的模数取模。

两个方案不同当且仅当有一步选择的操作或选择的数不同。例如：$ x = 5 $ 时，选择操作 $ 1 $ 且 $ y = 4 $，或选择操作 $ 2 $ 且 $ z = 3\ 或\ 4\ 或\ 5 $ 时，点都将被移到 $ 1 $ 号格子，但这些都是不同的方案。

## 说明/提示

$ 2 \leqslant n \leqslant 4 \cdot 10^6, 10^8 < m < 10^9, m $ 是质数。

## 样例 #1

### 输入

```
3 998244353```

### 输出

```
5```

## 样例 #2

### 输入

```
5 998244353```

### 输出

```
25```

## 样例 #3

### 输入

```
42 998244353```

### 输出

```
793019428```

## 样例 #4

### 输入

```
787788 100000007```

### 输出

```
94810539```

# 题解

## 作者：henrytb (赞：18)

这道题分了简单版和正常版。我先想出了简单版，然后才做出了正常版。

### 简单版

题目中的数据范围是 $2\le n\le 2\cdot 10^5$，那么 $O(n\sqrt{n})$ 做法可过。

我们设 $f_i$ 表示从 $n$ 走到 $i$ 的方案数。

那么如果我们已经转移完了 $f_i$，$f_i$ 便可以转移到 $\left\lfloor\frac{i}{2}\right\rfloor,\left\lfloor\frac{i}{3}\right\rfloor,\cdots,\left\lfloor\frac{i}{i}\right\rfloor$。

这个式子很熟悉，我们可以 **整除分块**！

另外还要考虑通过减法到达 $i$ 的情况，在转移 $f_i$ 的时候我们加上后缀和即可。

```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
int _,n,p;
int f[200005];
signed main() {
    scanf("%lld%lld",&n,&p);
    f[n]=1;
    rep(i,1,n-1) f[i]=0;
    int sum=1;
    int l=2,r;
    for(;l<=n;l=r+1) {
        r=n/(n/l);
        f[n/l]=(f[n/l]+(r-l+1)*f[n])%p;
    }
    per(i,n-1,1) {
        f[i]=(f[i]+sum)%p;
        l=2;
        for(;l<=i;l=r+1) {
            r=i/(i/l);
            f[i/l]=(f[i/l]+(r-l+1)*f[i])%p;
        }
        sum=(sum+f[i])%p;
    }
    printf("%lld\n",f[1]);
    return 0;
}
```

### 正常版

数据范围 $2\le n\le 4\cdot 10^6$，貌似不能 $O(n\sqrt{n})$ 了。

但是我们可以换个角度，不考虑 $f_i$ 可以转移到谁了，转而考虑谁能转移到 $f_i$。

通过减法转移到 $f_i$ 的显然是 $f_{i+1\sim n}$。

通过除以 $2$ 转移到 $f_i$ 的是 $f_{2i\sim 2i+1}$。

通过除以 $3$ 转移到 $f_i$ 的是 $f_{3i\sim 3i+2}$。

以此类推，通过除以 $z$ 转移到 $f_i$ 的是 $f_{zi\sim zi+z-1}$。

那么我们可以做一个 $f$ 的后缀和，然后对于每个 $f_i$ 枚举 $z$，使用后缀和转移。

时间复杂度 $O(n\log n)$，$\log$ 的来历是调和级数。

```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
int _,n,p;
int f[4000005],sum[4000005];
signed main() {
    scanf("%lld%lld",&n,&p);
    f[n]=1;
    sum[n]=1;
    rep(i,1,n-1) f[i]=0;
    per(i,n-1,1) {
        f[i]=(f[i]+sum[i+1])%p;
        for(int j=2;i*j<=n;++j) {
            // i*j ~ i*j+(j-1)
            f[i]=(f[i]+sum[i*j]-sum[min(i*j+j,n+1)])%p;
            f[i]=(f[i]+p)%p;
        }
        sum[i]=(sum[i+1]+f[i])%p;
    }
    printf("%lld\n",f[1]);
    return 0;
}
```

---

## 作者：SSerxhs (赞：4)

设 $f_x$ 表示 $n=x$ 的答案，dp 方程显然是 $f_i=\sum\limits_{j=1}^{i-1} f_j+\sum\limits_{j=2}^i f_{[i/j]}$。

直接利用这个式子计算，运用整除分块，可以得到 $O(\sum\limits_{i=1}^n\sqrt{i})$ 的做法。考虑到 $\frac{n\sqrt{n}}{2\sqrt{2}}=\sum\limits_{i=n/2}^n\sqrt {n/2}\le\sum\limits_{i=1}^n\sqrt{i}\le n\sqrt n$，复杂度为 $O(n\sqrt n)$。

考虑反过来，思考 $j$ 可以对哪些 $i$ 贡献。第一部分贡献可以在 dp 的同时记录前缀和实现。

第二部分，记当前要贡献的下标是 $k$，设 $[i/q]=k$，令 $i=kq+r$（$0\le r<q$，相当于对 $q$ 作带余除法），那么可以看出，对任意一个 $q$，$k$ 能对区间 $[kq,kq+q)$ 贡献一次。这个操作可以通过差分实现。

总复杂度 $O(\sum \dfrac{n}i)=O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int p;
inline void inc(register int &x,const int y)
{
	if ((x+=y)>=p) x-=p;
}
inline void dec(register int &x,const int y)
{
	if ((x-=y)<0) x+=p;
}
const int N=4e6+2,M=1e6+2,inf=1e9;
int a[N],s[N],d[N];
int T,n,m,c,i,j,k,x,y,z,ans,la,ksiz,ks;
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>p;
	a[1]=s[1]=1;
	for (i=1;i<=n;i++)
	{
		inc(d[i],d[i-1]);inc(a[i],s[i-1]);inc(a[i],d[i]);
		for (j=2;i*j<=n;j++) inc(d[i*j],a[i]),dec(d[min((i+1)*j,n+1)],a[i]);
		s[i]=s[i-1];
		inc(s[i],a[i]);
	}
	cout<<a[n]<<endl;
}

```

---

## 作者：Leasier (赞：2)

请先阅读[这篇](https://www.luogu.com.cn/blog/Leasier/solution-CF1561)题解。

考虑对 $dp_{i, 2}$ 差分。

由于 $\lfloor \frac{n}{m} \rfloor - \lfloor \frac{n - 1}{m} \rfloor = [m \mid n]$ 对于任意正整数 $n, m$ 都成立，考虑在算出当前 $i$ 的 $dp_{i, j}$ 后向它的倍数累加贡献。

时间复杂度为 $O(n \ln n)$。

同样需要注意涉及 $dp_{1, i}$ 的情况的处理。

代码：
```cpp
#include <stdio.h>

int dp[4000001][2], sum[4000001][2];

int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	for (register int i = 2; i <= n; i++){
		int t;
		dp[i][0] = (sum[i - 1][0] + sum[i - 1][1] + 1) % m;
		if (i == 2){
			dp[i][1] = 1;
		} else {
			dp[i][1] = (dp[i][1] + dp[i - 1][1] - (i % 2 == 0 ? 1 : 0) + 1) % m;
		}
		t = ((dp[i][0] + dp[i][1] - dp[i - 1][0] - dp[i - 1][1]) % m + m) % m;
		sum[i][0] = (sum[i - 1][0] + dp[i][0]) % m;
		sum[i][1] = (sum[i - 1][1] + dp[i][1]) % m;
		for (register int j = i * 2; j <= n; j += i){
			dp[j][1] = (dp[j][1] + t) % m;
		}
	}
	printf("%d", (dp[n][0] + dp[n][1]) % m);
	return 0;
}
```

---

## 作者：白鲟 (赞：1)

### 前言
翻车 vp……

### 题目分析
设 $f_i$ 为由 $i$ 跳到 $1$ 的方案数，容易得到转移方程为 $f_i=\sum_{j=1}^{i-1}f_{j}+\sum_{j=2}^{i}f_{\lfloor\frac{i}{j}\rfloor}$。

分成两部分转移。前一部分直接记录前缀和，后一部分整除分块，可以得到简单版的做法，时间复杂度为 $\operatorname{O}(n\sqrt n)$。

考虑优化第二部分转移。可以联想到类似变枚举因数为枚举倍数的方法，依靠调和级数的 $\operatorname{O}(n\log n)$ 复杂度求解。

考虑 $f_i$ 可以对每个 $f_j$ 产生多少次贡献。易知对于每个满足 $\lfloor\dfrac{j}{k}\rfloor=i$ 的 $k$，$f_i$ 均会对 $f_j$ 产生贡献 。对此进行转化，对于一对既定的 $i,k$，若 $\lfloor\dfrac{j}{k}\rfloor=i$，根据整除定义有 $j-ik\in[0,k-1]$。于是对于每个可相交区间 $[ik,ik+k-1]$ 内的 $j$，$f_i$ 均会产生一次贡献。注意特判不允许自我转移。

于是问题转化为区间加单点查询，若使用树状数组则时间复杂度为 $\operatorname{O}(n\log^2n)$，无法通过。然而由于查询位置单增，修改的位置均在最近的查询位置之后，直接差分即可，时间复杂度为 $\operatorname{O}(n\log n)$。

### 代码
```cpp
#include<bits/stdc++.h>
#define loop(i,from,to) for(int i=(from);i<=(to);++i)
using namespace std;
const int maxn=4e6;
int n,mod,sum,sumdelta,f[maxn+1],delta[maxn+2];
inline void add(int l,int r,int value){delta[l]=(delta[l]+value)%mod,delta[r+1]=(delta[r+1]+mod-value)%mod;return;}
int main(){
	scanf("%d%d",&n,&mod),sum=f[1]=1;
	loop(i,2,n)add(i,min(n,2*i-1),f[1]);
	loop(i,2,n){
		f[i]=(sum+(sumdelta=(sumdelta+delta[i])%mod))%mod,sum=(sum+f[i])%mod;
		loop(j,1,n/i)add(j*i+(j==1),min(n,j*i+j-1),f[i]);
	}
	printf("%d",f[n]);
	return 0;
}
```

---

## 作者：LRL65 (赞：1)

### 题意：
有 $n$ 个格子，标号 $1\sim n$ ，其中有一个令牌在第 $n$ 格，你需要将它移至第 $1$ 格。每次移动有两种方式，可以任选其一：

1. 向上移动任意格
1. 设当前格为 $x$ ，那么可移至 $\lfloor \frac{x}{z} \rfloor $ ，$z$ 为任意整数。

现在问从第 $n$ 格到第 $1$ 格有多少种方案数，对 $m$ 取模后输出。


------------

### 方法：

很容易想到是 $dp$ 。

我们设 $f_i$ 为从第 $n$ 格到达第 $i$ 格的方案数。

1. 对于第一种方式，很容易想到，状态转移方程为 $f_i=\sum\limits_{j=i+1}^{n}f_j$ 。

1. 然而对于第二种方式，我们要考虑当前格是从哪里转移来的。因为是下取整，所以第 $i$ 格是从 $i\times k \sim \min(i\times k+k-1,n)(i\times k\leqslant n)$ 转移来的。那么状态转移方程为 $f_i=\sum\limits_{j=i\times k}^{\min(i\times k+k-1,n)}f_j(i\times k\leqslant n)$ 。

所以我们要准备一个后缀和数组即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,f[4000005],s[4000005];
int main() {
    cin>>n>>m;
    memset(f,0,sizeof(f));
    f[n]=1;s[n]=1;
    int sum=1;
    for(int i=n-1;i>=1;i--) {
        f[i]=sum%m;
        for(int j=2;j<=n/i;j++) {
            int t=i*j;
            if(t+j>n)f[i]=(f[i]+s[t])%m;
            else f[i]=(f[i]+(s[t]+m-s[t+j])%m)%m;
        }
        sum=(sum+f[i])%m;
        s[i]=sum%m;
    }
    cout<<f[1]%m<<endl;
}
```


---

## 作者：gyh20 (赞：1)

看到 $4\times 10^6$ 和 $6s$ 的时限考虑一个时间 $O(n\log n)$，空间 $O(n)$ 的做法，大概可以往枚举倍数的方向想。

两种走的方式对应着 DP 的两种转移，第一种直接前缀和，只考虑第二种。

观察 $\lfloor{\dfrac n x}\rfloor=k$ 这个式子，$kx$ 明显是可以枚举的，对于一对枚举的 $(x,k)$ 合法的 $n$ 是属于 $[kx,(k+1)x-1]$（直接根据整除的式子得出），这里可以直接用差分优化。

时间复杂度 $O(n\log n)$，空间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int n,m,f[4000002],M,ans,s,tg[4000002];
inline void add(re int &x,re int y){(x+=y)>=M?x-=M:x;}
inline int Mod(re int x){return x>=M?x-M:x;}
int main(){
	s=1,n=read(),M=read(); 
	for(re int i=1;i<=n;++i){
		add(tg[i],tg[i-1]),f[i]=s;
		add(f[i],tg[i]);
		for(re int j=i+i,cnt=1;j<=n;j+=i,++cnt){
			add(tg[j],f[i]);
			if(j+cnt+1<=n)add(tg[j+cnt+1],M-f[i]);
		}
		if(i^1)add(s,f[i]);
	}
	printf("%d",f[n]);
}

```


---

