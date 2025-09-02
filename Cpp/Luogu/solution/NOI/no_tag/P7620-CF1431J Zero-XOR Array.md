# CF1431J Zero-XOR Array

## 题目背景

这是一道来自 Kotlin Heroes 的题目。但是这里允许其他语言提交。

## 题目描述

给定一个包含 $n$ 个整数的序列 $a$，其中第 $i$ 个整数为 $a_i$。这个序列满足单调不递减性质，即 $a_1 \le a_2 \le \ldots \le a_n$。

你需要找出所有包含 $2n-1$ 个整数的序列 $b$，使其满足以下条件：

* $b_{2i−1}=a_i$ ($1\leq i\leq n$)；

* $b$ 满足单调不递减性质；

* $b1\oplus b2\oplus \ldots \oplus b_{2n−1}=0$（$\oplus$ 表示按位异或运算。在 Kotlin 语言中，用函数 `xor` 表示）。

请计算出不同的序列 $b$ 的个数对 $998244353$ 取模的结果。

## 说明/提示

![](https://cdn.luogu.com.cn/upload/image_hosting/aq4idgel.png)

## 样例 #1

### 输入

```
3 2
0 1 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 3
0 3 6 7
```

### 输出

```
6
```

## 样例 #3

### 输入

```
5 5
1 5 9 10 23
```

### 输出

```
20
```

## 样例 #4

### 输入

```
10 7
39 62 64 79 81 83 96 109 120 122
```

### 输出

```
678132
```

# 题解

## 作者：panyf (赞：5)

记 $s=a_1\oplus a_2\oplus...\oplus a_n$。

题意可以转化为求长度为 $n-1$ 的整数序列 $c_i$，满足 $a_i\leq c_i\leq a_{i+1}$，且 $c_1\oplus c_2\oplus...\oplus c_{n-1}=s$ 的方案数。

从高位到低位枚举。设当前枚举到第 $k$ 位（最低位为第 $0$ 位），$c_i$ 一定属于以下状态之一：

1.第 $k+1$ 位到第 $m-1$ 位的前缀和 $a_{i}$ 的前缀相同；

2.前缀和 $a_{i+1}$ 相同且不和 $a_{i}$ 相同；

3.前缀和 $a_{i+1}$ 及 $a_{i}$ 都不同。

发现一个性质：

某一时刻，若存在一个 $c_i$ 满足状态 3，记 $l_j$ 为确定了前缀后 $c_j$ 可以取到的最小值，$r_j$ 为最大值，则方案数为 $\Pi_{j\neq i}(r_j-l_j+1)$。

原因：任意选择除 $i$ 以外的 $c_j$，因为 $c_i$ 满足状态 3，所以后 $k$ 位的 $2^k$ 种情况都可以取到，所以其中有且仅有一种情况可以使异或和等于 $s$。

考虑枚举 $k$，表示在第 $k$ 位时第一次出现一个数满足状态 3。

暴力枚举第 $k+1$ 位时所有数的状态，因为只存在前两种，所以至多 $2^{n-1}$ 种状态。

先判断状态是否合法。

若合法，考虑 dp。

记 $f_0$ 表示当前异或和为 $0$，且不存在数满足状态 3。

$f_1$ 表示当前异或和为 $1$，且不存在数满足状态 3。

$f_2$ 表示当前异或和为 $0$，且存在数满足状态 3。

$f_3$ 表示当前异或和为 $1$，且存在数满足状态 3。

具体转移方程见代码，设 $s$ 的第 $k$ 位为 $x$，则 $f_{2|x}$ 即为方案数。

时间复杂度 $O(2^nnm)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int P=998244353;
ll a[19],b[19],s;
int n,m,p[19],f[4],g[4];
bool chk(int o,int k){//判断第k位状态o是否合法
	ll w=0;
	for(int i=0;i<n;++i){
		if(o>>i&1){
			if(p[i]<k)return 0;
			w^=b[i];
		}else w^=a[i];
	}
	return(w>>k)==(s>>k);
}
void wk(int x,ll v){v%=P;for(int i=0;i<4;++i)g[i^x]=(g[i^x]+f[i]*v)%P;}//非状态3的转移
void wk2(int x,ll v){v%=P,g[2^x]=(g[2^x]+f[2]*v+f[0])%P,g[3^x]=(g[3^x]+f[3]*v+f[1])%P;}//状态3的转移
int main(){
	int o,ans=0,i,j,k;
	for(scanf("%d%d",&n,&m),--m,i=0;i<n;++i)scanf("%lld",a+i),s^=a[i];
	for(i=0,--n;i<n;++i)for(b[i]=a[i+1],j=m,p[i]=-1;~j;--j)if((a[i]>>j&1)!=(b[i]>>j&1)){p[i]=j;break;}//p[i]表示最大的k满足a[i]和a[i+1]的第k位不同
	for(o=1<<n,i=0;i<o;++i)if(chk(i,0))++ans;//处理不存在状态3的情况
	for(k=0;k<m;++k)for(j=0;j<o;++j)if(chk(j,k+1)){
		f[0]=1,f[1]=f[2]=f[3]=0;
		for(i=0;i<n;memcpy(f,g,16),memset(g,0,16),++i){
			if(p[i]<k)wk(a[i]>>k&1,b[i]-a[i]+1);
			else if(p[i]==k)wk(0,(b[i]>>k<<k)-a[i]),wk(1,b[i]-(b[i]>>k<<k)+1);
			else if(j>>i&1){
				if(b[i]>>k&1)wk(1,b[i]-(b[i]>>k<<k)+1),wk2(0,1ll<<k);
				else wk(0,b[i]-(b[i]>>k<<k)+1);
			}else{
				if(a[i]>>k&1)wk(1,(1ll<<k)-a[i]+(a[i]>>k<<k));
				else wk(0,(1ll<<k)-a[i]+(a[i]>>k<<k)),wk2(1,1ll<<k);
			}
		}
		ans=(ans+f[2|(s>>k&1)])%P;
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：tzc_wk (赞：3)

[洛谷题面传送门](https://www.luogu.com.cn/problem/P7620)

首先显然题目等价于求有多少个长度 $n-1$ 的序列 $b$ 满足 $a_i\le b_i\le a_{i+1}$，满足 $b_1\oplus b_2\oplus\cdots\oplus b_{n-1}=a_1\oplus a_2\oplus\cdots\oplus a_n=S$。

考虑入手解决这个问题，注意到 $n$ 数据范围很小，只有 $18$，而值域非常大，高达 $2^{60}$，因此可以考虑拆位后 $2^n$ 枚举个什么状态后计算。但是究竟枚举什么状态呢？我们不妨先来分析一些性质：

> Observation 1. 对于某个 $b_i$ 的第 $j$ 位，总共有 $3$ 种可能：
>
> 1. $b_i$ 的第 $j$ 位到第 $m-1$ 位（最高位）组成的前缀与 $a_i$ 对应前缀相同
> 2. $b_i$ 的第 $j$ 位到第 $m-1$ 位组成的前缀不同于 $a_i$，但与 $a_{i+1}$ 相同
> 3. $b_i$ 的第 $j$ 位到第 $m-1$ 位组成的前缀既不同于 $a_i$，也不同于 $a_{i+1}$

也就是将每个 $b_i$ 的每一段前缀分为达到上界、达到下界和即每达到上界也没达到下界三种情况。

但是知道这个性质之后有什么用吗？

> Observation 2. 对于某个 $b_i$ 的某个 $j$，如果它满足上面的第三种情况，并且我们已经固定了每个 $b_i$ 第 $j$ 位到第 $m-1$ 位的取值，那么记 $l_x$ 为 $b_x$ 的后 $j$ 位可以达到的最小值，$r_x$ 为 $b_x$ 的后 $j$ 位可以达到的最大值，那么有 $\prod\limits_{t\ne i}(r_t-l_t+1)$ 种合法的序列 $\{b\}$。

为什么？因为由于 $b_i$ 即没有达到上界，也没有达到下界，因此 $b_i$ 的后 $j$ 位可以取遍 $[0,2^j)$ 中所有的值，因此对于任意一种其他位置后 $j$ 位的填法都唯一存在一个 $b_i$ 的后 $j$ 位的填法，满足它们的异或和等于 $S$。

知道了这个性质之后，我们考虑枚举第一位存在某个 $b_i$ 出现第三种情况的位置：第 $j$ 位。那么对于第 $j+1$ 位到第 $m-1$ 位而言，每个 $b_i$ 只有达到上界和达到下界两种可能，我们考虑再 $2^n$ 枚举这个状态 $st$，$st$ 的第 $i-1$ 位为 $0$ 表示 $b_i$ 的第 $j+1$ 到 $m-1$ 位达到下界，第 $i-1$ 位为 $1$ 表示 $b_i$ 的第 $j+1$ 到 $m-1$ 位达到上界。

枚举这两个值之后，擅长解决计数问题的 $dp$ 就要派上用场了，我们考虑记 $dp_{i,0/1/2/3}$ 表示当前决策了前 $i$ 个数的第 $j$ 位的值，后面一维的定义如下：

- $0$ 表示当前没有出现第三种情况，且该位异或和为 $0$
- $1$ 表示当前没有出现第三种情况，且该位异或和为 $1$
- $2$ 表示当前出现了第三种情况，且该位异或和为 $0$
- $3$ 表示当前出现了第三种情况，且该位异或和为 $1$

转移就分这一位填 $0$ 和这一位填 $1$ 两种情况处理即可，具体来说：

- 如果 $a_{i+1}$ 和 $a_i$ 的第 $j$ 位到第 $m-1$ 位都相同，那么第 $j$ 位只能填与 $a_i$ 的第 $j$ 位相同的值，方案数为 $a_{i+1}-a_i+1$
- 如果 $a_{i+1}$ 和 $a_i$ 的第 $j+1$ 位到第 $m-1$ 位都相同，但第 $j$ 位不同，那么记 $X=\lfloor\dfrac{a_{i+1}}{2^j}\rfloor\times 2^j$，$b_i$ 第 $j$ 位填 $0$ 有 $X-a_i$ 种可能，填 $1$ 有 $a_{i+1}-X+1$ 种可能，并且都不会出现情况 $3$，随便转移一下即可。
- 否则如果 $st$ 的第 $i-1$ 位为 $0$，则 $b_i$ 的第 $j+1$ 到 $m-1$ 位与 $a_i$ 相同，继续分情况讨论：
  - 如果 $a_i$ 的第 $j$ 位为 $1$，那么 $b_i$ 的第 $j$ 位只能填 $1$，方案数为 $\lfloor\dfrac{a_{i}}{2^j}\rfloor\times 2^j+2^j-a_i$，并且不会出现情况 $3$
  - 如果 $a_i$ 的第 $j$ 位为 $0$，那么 $b_i$ 的第 $j$ 位可 $0$ 可 $1$，填 $0$ 的方案数依旧是 $\lfloor\dfrac{a_{i}}{2^j}\rfloor\times 2^j+2^j-a_i$，填 $1$ 的方案数则是 $2^j$，并且会出现情况 $3$。
- 如果 $st$ 的第 $i-1$ 位为 $1$，与 $st$ 的第 $i-1$ 位为 $0$ 的情况类似，镜像一下即可。

最终累加入答案的值即为 $dp_{n-1,2+d}$，其中 $d$ 为 $S$ 第 $j$ 位的值。

时间复杂度 $2^n·nm$

```cpp
const int MAXN=17;
const int MOD=998244353;
int n,m,ans=0,dif[MAXN+5];ll l[MAXN+5],r[MAXN+5],sum=0;
bool check(int st,int k){
	ll ss=0;
	for(int i=1;i<n;i++){
		if(st>>(i-1)&1){
			if(dif[i]<k) return 0;
			ss^=r[i];
		} else ss^=l[i];
	} return (ss>>k)==(sum>>k);
}
int dp[MAXN+3][4];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lld",&l[i]),r[i-1]=l[i],sum^=l[i];
	for(int i=1;i<n;i++){
		dif[i]=-1;
		for(int j=m-1;~j;j--) if((l[i]>>j&1)^(r[i]>>j&1)){
			dif[i]=j;break;
		}
	}
	for(int i=0;i<(1<<n-1);i++) if(check(i,0)) ans++;
	for(int i=0;i<m;i++) for(int j=0;j<(1<<n-1);j++) if(check(j,i+1)){
		memset(dp,0,sizeof(dp));dp[0][0]=1;
		for(int p=1;p<n;p++){
			if(dif[p]<i){
				int d=l[p]>>i&1,num=(r[p]-l[p]+1)%MOD;
				for(int t=0;t<4;t++) dp[p][t]=(dp[p][t]+1ll*dp[p-1][t^d]*num)%MOD;
			} else if(dif[p]==i){
				ll lim=l[p]|((1ll<<i)-1);int num0=(lim-l[p]+1)%MOD,num1=(r[p]-lim)%MOD;
				for(int t=0;t<4;t++){
					dp[p][t]=(dp[p][t]+1ll*dp[p-1][t]*num0)%MOD;
					dp[p][t]=(dp[p][t]+1ll*dp[p-1][t^1]*num1)%MOD;
				}
			} else if(j>>(p-1)&1){
				if(r[p]>>i&1){
					ll lim=r[p]>>i<<i;
					int num0=(1ll<<i)%MOD,num1=(r[p]-lim+1)%MOD;
					for(int t=0;t<4;t++) dp[p][t]=(dp[p][t]+1ll*dp[p-1][t^1]*num1)%MOD;
					for(int t=2;t<4;t++) dp[p][t]=(0ll+dp[p][t]+1ll*num0*dp[p-1][t]+dp[p-1][t&1])%MOD;
				} else {
					ll lim=r[p]>>i<<i;
					int num0=(r[p]-lim+1)%MOD;
					for(int t=0;t<4;t++) dp[p][t]=(dp[p][t]+1ll*dp[p-1][t]*num0)%MOD;
				}
			} else {
				if(~l[p]>>i&1){
					ll lim=l[p]|((1ll<<i)-1);
					int num0=(lim-l[p]+1)%MOD,num1=(1ll<<i)%MOD;
					for(int t=0;t<4;t++) dp[p][t]=(dp[p][t]+1ll*dp[p-1][t]*num0)%MOD;
					for(int t=2;t<4;t++) dp[p][t]=(0ll+dp[p][t]+1ll*num1*dp[p-1][t^1]+dp[p-1][(t^1)&1])%MOD;
				} else {
					ll lim=l[p]|((1ll<<i)-1);
					int num1=(lim-l[p]+1)%MOD;
					for(int t=0;t<4;t++) dp[p][t]=(dp[p][t]+1ll*dp[p-1][t^1]*num1)%MOD;
				}
			}
		}
		int d=sum>>i&1;
		ans=(ans+dp[n-1][2|d])%MOD;
	} printf("%d\n",ans);
	return 0;
}
```



---

## 作者：andychen_2012 (赞：0)

## 解题思路

我们可以将问题简化如下：

我们需要寻找 $n-1$ 个数 $b_i$ 使得 $a_i \le b_i \le a_{i+1}$。

并且使得 $b_1 \oplus b_2 \oplus \cdots \oplus b_{n-1} = a_1 \oplus a_2 \oplus \cdots \oplus a_n$。

我们可以从每一个位去解决这个问题。

在位 $p$ 上，对于每一个 $b_i$ 都包含在一个区间 $[l,r]$ 内。

那么让我们定义数 $x$ 的第 $p$ 位为 $x(p)$。

如果 $l(p)=r(p)$，$b_i$ 除了 $l$ 外，就没有任何其他选择，并且 $[l,r]$ 没有任何变化。

否则的话，如果 $l(p)=0,r(p)=1$，那我们对于 $b_i$ 有两种选择：

- 如果我们选择的 $b_i$ 使得 $b_i(p)=0$，那么 $l$ 就不会有改变，但是 $r$ 就会变成 $2^p-1$。

- 如果我们选择的 $b_i$ 使得 $b_i(p)=1$，那么 $r$ 就不会有改变，但是 $l$ 就会变成 $0$。

我们可以发现，$b_i$ 的最小值要么是 $l$，要么是 $0$；最大值要么是 $r$，要么是 $2^p-1$。

那么这使我们想到了一个有四维的状压 dp，时间复杂度大约是 $O(4^nn^2)$，肯定炸了。

我们开始考虑优化。

### 1.$l=0$ 且 $r=2^p-1$

我们再往下思考，就会发现，如果 $b_i$ 的区间为 $[0,2^p-1]$，

这种情况下，我们可以先把其它数确定，剩下的这个位置就只有 $1$ 种可能了。

我们的答案就是除了这个数位之外其它数位的可能情况的乘积。


### 2.$l=0$ 或 $r=2^p-1$

这种情况下，$l,r$ 将会一直持续，直到我们选择的数与之前选择的数相反时。

例如之前的 $b_i(p)$ 选的都是 $0$，而现在选择的 $b_i(p)$ 是 $1$，那此时 $l,r$ 就会变成 $l=0,r=2^p-1$。

### 总结

很明显的状压背包了，现在就是推 dp 式子。

我们可以做出每一次 $b_i$ 的选择了。我们使得 $b_i$ 的第 $i$ 位中有连续的几个 $0$，然后是 $1$，反之亦然。

这仅仅是第 $2^{n-1}$ 次的状压选择。

我们对每一次的状压，迭代第一个位 $p$，并且在迭代之前就先进行一遍判断是否有特殊情况1。

为了计算 $p$ 的答案，我们可以为 $b_i$ 找到唯一确定的，不会重复的区间 $[l,r]$，使得 $b_i$ 的取值在且尽可能在这个区间内。

然后我们可以计算在第 $msk$ 次状压，第 $bit$ 次迭代的时候的 $f[i][sum][use]$，表示的是在 $[0,pos]$ 中 $b_i$ 的取值在 $[l,r]$ 中，

且 $b_1(bit) \oplus b_2(bit) \oplus \cdots \oplus b_{n-1}(bit) = sum$，

而 $use$ 表示的是是否至少有一个 $b_i(bit)$ 与 $msk(bit)$ 相反。

那么我们最终的答案就是每一次状压时迭代 $bit$ 时的 $f[n-1][(a_1 \oplus a_2 \oplus \cdots \oplus a_n)(bit)][1]$ 之和。

我们可以得出时间复杂度最多是 $O(n2^n)$，常数为 $60$。

至此，本题结束。

## 解题代码

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long ll;
ll mod=998244353;
ll inv[61];
int n;
ll a[20];
ll f[20][2][2];
inline bool jud(ll bit,ll msk){
    ll sum=0;
    for(int i=0;i<n;++i)
        sum=sum^(a[i]>>bit);
    for(int i=0;i<n-1;++i)
        sum=sum^((((msk>>i)&1)==0?a[i]:a[i+1])>>bit);
    return sum==0;
}
int main(){
//	freopen("xor30.in","r",stdin);
//	freopen("xor30.out","w",stdout);
    scanf("%d",&n);
    for(int i=0;i<n;++i)
        scanf("%lld",a+i);
    ll ans=0,m=1<<(n-1);
    for(int msk=0;msk<m;++msk){
        if(jud(0,msk)){		//判断当前这个数是否满足特殊情况1 
            ll ways=1;
            for(int i=0;i<n-1;++i)
                if(a[i+1]==a[i]&&((msk>>i)&1)==1)
                    ways=0;
            if(ways)
                ans=(ans+ways)%mod;
        }
        for(int bit=0;bit<60;++bit){	//a[i]最大不到2^60 
            if(!jud(bit+1,msk)) continue;
            memset(f,0,sizeof(f));
            f[0][0][0]=1;
            for(int i=0;i<n;++i){
                for(int sum=0;sum<2;++sum){
                    for(int use=0;use<2;++use){
                        ll ways=f[i][sum][use];
                        if(ways==0) continue;
                        if(i==n-1) break;
                        ll side=(msk>>i)&1;
                        //表示的是msk(i) 
                        ll lh=(a[i]>>bit)&1;
                        ll rh=(a[i+1]>>bit)&1;
                        bool same=(a[i]>>(bit+1))==(a[i+1]>>(bit+1));
                        //same表示的是当前这个a[i](bit+1)和a[i+1](bit+1)相不相等 
                        for(int mg=0;mg<2;++mg){
                            if((same||side==0)&&mg<lh||(same||side==1)&&mg>rh)
                                continue;
                            if(same&&lh!=rh&&side!=mg)
                                continue;
                            if(same&&lh==rh&&side==1)
                                continue;
                            ll ns=sum^mg;
                            ll dif=side==0&&mg>lh||side==1&&mg<rh;
                            ll mlt=0;
                            if(dif)		//情况1，如果msk(i)=1并且这次的循环将之前的0切换成1或者msk(i)=0并且这次的循环将之前的1切换成0，就有2^bit种可能 
                                mlt=1ll<<bit;
                            else if(same&&lh==rh)		//情况2，如果a[i]和a[i+1]的bit与bit+1数位都相等，那么可能的方案就有a[i+1]-a[i]+1种 
                                mlt=a[i+1]-a[i]+1;
                            else if(side==0)		//情况3，如果msk(i)是0，那么就有a[i]>>bit+2^bit种可能，因为此时还可以加上原来a[i]的高位的方案数 
                                mlt=(((a[i]>>bit)+1)<<bit)-a[i];
                            else		//这个和上面情况2相像 
                                mlt=a[i+1]-((a[i+1]>>bit)<<bit)+1;
                            if(use==0&&dif)
                                f[i+1][ns][1]=(f[i+1][ns][1]+ways)%mod;
                            else
                                f[i+1][ns][use]=(f[i+1][ns][use]+ways*(mlt%mod)%mod); 
                        }
                    }
                }
            }
            ll want=0;
            for(int i=0;i<n;++i)
                want=want^((a[i]>>bit)&1);
            if(f[n-1][want][1]!=0)
                ans=(ans+f[n-1][want][1])%mod;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Kubic (赞：0)

发现数据范围的特点 $n$ 小 $m$ 大，尝试从中入手。

从高位到低位依次考虑，设当前位为 $i$，对于第 $j$ 个数，如果在 $(j,m)$ 中的每一位 $a_j$ 和 $a_{j+1}$ 都对应相等，那么当前能够填进去的数显然一定唯一。

剩下还有 $3$ 种情况：只有上界限制，只有下界限制，上下界都没有限制。

此时就可以得到一个 $O(nm3^n)$ 的状压 dp 算法。

但这显然过不去，考虑优化。

发现如果在第 $j$ 个数出现了第三种情况，那么显然它后面能够取到 $[0,2^i)$ 中的每一个值。此时别的数在后面任意取，都可以对应到其中唯一的一种取法使得其异或和为 $0$。此时的方案数为 $\prod_{j\neq k} w_k$，其中 $w_k$ 表示第 $k$ 个数在后面的取法总数。

有了这个结论之后就很容易做了。

由于每一个数在 dp 过程中不可能既在某一时刻只有上界限制又在另一时刻有下界限制，于是我们可以直接 $O(2^n)$ 枚举每一个数的状态。再枚举在哪一**位**上首次出现了第三种情况。

定义 $dp_{i,0/1,0/1}$ 表示当前这一位上考虑到第 $i$ 个数，异或和为 $0/1$，否$/$是 出现过第三种情况的总方案数和。根据限制枚举当前填 $0/1$ 分别转移即可。有较多细节，建议读者自行思考。

注：有一个细节是如果在某一位 $dp_{n-1,0,0}=0$ 就要终止 dp，~~由于我比较懒~~，代码中直接判断了 $dp_{n-1,0,0}$ 是否为 $0$，这并不严谨。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 25
#define M 65
#define STT 1<<17
#define MOD 998244353
#define ll long long
int n,m,ans,ps[N],dp[N][2][2];ll s,a[N];
void W(int &x,int y) {x=(x+y)%MOD;}
int slv(ll stt)
{
	int mn=m,res=0;
	for(int i=1;i<n;++i) if(stt>>i-1&1) mn=min(mn,ps[i]);
	if(mn==-1) return 0;
	for(int i=m-1,t,w;i>=0;--i)
	{
		dp[0][0][0]=1;
		for(int j=1;j<n;++j)
		{
			ll l=a[j]&(1ll<<i)-1,r=a[j+1]&(1ll<<i)-1;
			if(ps[j]>=i) {if(stt>>j-1&1) l=0;else r=(1ll<<i)-1;}
			w=(r-l+1)%MOD;
			dp[j][0][0]=dp[j][1][0]=dp[j][0][1]=dp[j][1][1]=0;
			if(ps[j]<=i)
			{
				if(ps[j]<i) t=a[j]>>i&1;else t=stt>>j-1&1;
				W(dp[j][0][0],1ll*dp[j-1][t][0]*w%MOD);
				W(dp[j][1][0],1ll*dp[j-1][t^1][0]*w%MOD);
				W(dp[j][0][1],1ll*dp[j-1][t][1]*w%MOD);
				W(dp[j][1][1],1ll*dp[j-1][t^1][1]*w%MOD);
			}
			else if(stt>>j-1&1)
			{
				if(a[j+1]>>i&1)
				{
					W(dp[j][0][0],1ll*dp[j-1][1][0]*w%MOD);
					W(dp[j][1][0],1ll*dp[j-1][0][0]*w%MOD);
					W(dp[j][0][1],1ll*dp[j-1][1][1]*w%MOD);
					W(dp[j][1][1],1ll*dp[j-1][0][1]*w%MOD);
					
					W(dp[j][0][1],dp[j-1][0][0]);
					W(dp[j][1][1],dp[j-1][1][0]);
					W(dp[j][0][1],(1ll<<i)%MOD*dp[j-1][0][1]%MOD);
					W(dp[j][1][1],(1ll<<i)%MOD*dp[j-1][1][1]%MOD);
				}
				else
				{
					W(dp[j][0][0],1ll*dp[j-1][0][0]*w%MOD);
					W(dp[j][1][0],1ll*dp[j-1][1][0]*w%MOD);
					W(dp[j][0][1],1ll*dp[j-1][0][1]*w%MOD);
					W(dp[j][1][1],1ll*dp[j-1][1][1]*w%MOD);
				}
			}
			else
			{
				if(!(a[j]>>i&1))
				{
					W(dp[j][0][0],1ll*dp[j-1][0][0]*w%MOD);
					W(dp[j][1][0],1ll*dp[j-1][1][0]*w%MOD);
					W(dp[j][0][1],1ll*dp[j-1][0][1]*w%MOD);
					W(dp[j][1][1],1ll*dp[j-1][1][1]*w%MOD);
					
					W(dp[j][0][1],dp[j-1][1][0]);
					W(dp[j][1][1],dp[j-1][0][0]);
					W(dp[j][0][1],(1ll<<i)%MOD*dp[j-1][1][1]%MOD);
					W(dp[j][1][1],(1ll<<i)%MOD*dp[j-1][0][1]%MOD);
				}
				else
				{
					W(dp[j][0][0],1ll*dp[j-1][1][0]*w%MOD);
					W(dp[j][1][0],1ll*dp[j-1][0][0]*w%MOD);
					W(dp[j][0][1],1ll*dp[j-1][1][1]*w%MOD);
					W(dp[j][1][1],1ll*dp[j-1][0][1]*w%MOD);
				}
			}
		}t=s>>i&1;if(i<=mn) W(res,dp[n-1][t][1]);
		if(!dp[n-1][t][0]) return res;
	}return res+1;
}
int main()
{
	scanf("%d %d",&n,&m);for(int i=1;i<n;++i) ps[i]=-1;
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]),s^=a[i];
	for(int i=0;i<m;++i) for(int j=1;j<n;++j)
		if((a[j]>>i&1)<(a[j+1]>>i&1)) ps[j]=i;
	for(int i=0;i<1<<n-1;++i) W(ans,slv(i));
	printf("%d\n",ans);return 0;
}
```

---

