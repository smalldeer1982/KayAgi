# KOSARE - KOSARE

## 题目描述

Mirko found N boxes with various forgotten toys at his attic. There are M different toys, numbered 1

## 样例 #1

### 输入

```
1:
3 3
3 1 2 3
3 1 2 3
3 1 2 3```

### 输出

```
1:
7```

# 题解

## 作者：E_huan (赞：7)

### 高维前缀和/SOSDP
本文提到的 $i$ 包含 $j$ 的意思是二进制下 $j$ 是 $1$ 的位 $i$ 都是 $1$。

$m$ 范围很小，考虑状态压缩。

于是转化成求二进制下子集/超集满足某些条件的方案数，考虑高维前缀和。

$ans_i$ 表示或和恰好为 $i$ 的方案数（最终答案是
 $ans_{(1<<m)-1}$）。

$g_i$ 表示或和被 $i$ 包含的方案数。
发现 $g_i$ 是 $ans_i$ 的高维前缀和，求出 $g_i$ 后差分即可求出 $ans_i$。

令 $f_i$ 表示被 $i$ 包含的数的个数。

则 $g_i=2^{f_i}-1$ （$-1$ 是因为不能是空集）。

开桶统计每个数出现次数 $T_i$。

$f_i=\sum\limits_{i包含j}{ T_j } $

这里 $f_i$ 的统计也可以用高维前缀和。

代码实现上可以省略一些数组，具体细节见下方代码。

#### 代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4000100,mod=1000000007;
int n,m,a[N],f[N],g[N];
inline int qmi(int x,int y)
{
    int res=1;
    while(y)
    {
        if(y&1) res=1ll*res*x%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return res;
}
inline void add(int &x,int y)
{   
    x+=y;
    if(x<0) x+=mod;
    if(x>=mod) x-=mod;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,cnt;i<=n;i++)
    {
        scanf("%d",&cnt);
        int u=0;
        for(int j=1,a;j<=cnt;j++)
        {
            scanf("%d",&a);
            u|=(1<<(a-1));
        } 
        f[u]++;
    }
    for(int i=0;i<m;i++)
        for(int j=0;j<(1<<m);j++)
            if((1<<i)&j)
                add(f[j],f[j^(1<<i)]);
    for(int i=0;i<(1<<m);i++) g[i]=(qmi(2,f[i])-1+mod)%mod;
    for(int i=0;i<m;i++)
        for(int j=0;j<(1<<m);j++)
            if((1<<i)&j)
                add(g[j],-g[j^(1<<i)]);
    printf("%d\n",g[(1<<m)-1]);
    return 0;
}
```

---

## 作者：ZqlwMatt (赞：5)

首先观察到数据特征 M≤20 ，很容易地联想到 **状压DP** 。~~出于种种原因，~~状态转移方程很难很难写。。。所以这里有一种很~~奇妙~~的思路

>原题的等价形式为：**总方案减去至少不出现一种玩具的方案数**。

考虑容斥原理：
$$\bigcup_{i=1}^{n}A_{i}=\sum_{k=1}^{n}(-1)^{k-1}\sum_{1\leqslant i_{1}< i_{2}...<i_{k}\leqslant n}\left | A_{i_{1}}\cap A_{i_{2}}\cap ...\cap A_{i_{k}} \right |$$

我们设 f[S] 表示状态为 $S$ 时所有元素都在集合 $S$ 中的方案数。（不要求包含 $S$ 中的所有元素）然后用容斥原理算一下即可。

---

如果你还看得一头雾水，这里举例说明：
举个简单的例子：

**Sample input:**

```
3 2
1 1
1 2
2 1 2
```

**Sample output:**

```
5
```

首先我们可以计算出 f[01]=f[10]=f[11]=1 （这里 f[s] 的 $S$ 表示集合相应元素）

然后可以更新 f[11]=f[11]+f[10]+f[01]=3;

那么考虑到 f[11]=3 其元素分别为 {1} , {2} , {1,2} 也就是说 共有 $2^{3}$ 种选择方案。（即在 f[11] 内选择（或不选）{1} , {2} , {1,2} ） 于是我们求出了 **总方案数** 。

类似的，我们可以求出至少不出现一种玩具的方案数，当然两部分可能会有重复的情况，所以需要运用容斥原理。（需要注意：每次的方案数都要-1，因为要考虑选出空集的情况）

（接下去的计算过程：**$(2^{3}-1)-(2^{1}-1)-(2^{1}-1)=5$**）

具体细节请见代码：
（部分变量解释：skd=所有元素都存在的状态，f\[\] 同上 ，_2\[i\] $2^{i}$，t\[i\] 容斥原理前的系数（可以通过发现含的元素个数确定qwq））

---

#### **AC代码**

```cpp
#include<cstdio>
#define re register int
#define rep(i,a,b) for(re i=(a);i<=(b);++i)
#define N (1<<20)
const int p=1000000007;
inline void read(int &x){
    x=0;
    int f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while ('0'<=ch&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    x*=f;
}
int n,m,k,x,res;
int f[N],t[N],_2[N]={1},skd;
int ans=0;

int main(){
    read(n),read(m);skd=(1<<m)-1;
    rep(i,1,n){
        read(k),res=0;
        rep(z,1,k)
            read(x),res|=1<<(x-1);
        ++f[res]; 
    }
    rep(i,1,m)
        rep(j,1,skd)
            if(j & (1<<(i-1)))    f[j]+=f[j^(1<<(i-1))]; //所有元素都在j内的方案数 
    rep(i,1,n){
        _2[i]=_2[i-1]<<1;
        if(_2[i]>=p)    _2[i]-=p;
    }
    rep(i,0,skd){
        t[i]=t[i>>1]+i&1; //容斥原理 
        if(!((m-t[i])&1))    ans+=_2[f[i]]-1;
        else ans-=_2[f[i]]-1;
        
        if(ans>=p)    ans-=p;
        else if(ans<0)    ans+=p;
    }
    printf("%d\n",ans);
}
```

---

如果题解有疏漏之处请[联系我](mailto:2268236614@qq.com) 感谢！

---

## 作者：_Arahc_ (赞：2)

子集反演例题，这里补充一下子集反演的式子吧：

$$
\text{let }F_S=\sum_{T\subset S} G_T
$$
$$
\text{then }G_S=\sum_{T\subset S} (-1)^{\left|S-T\right|} F_T
$$

可以用 FWT 实现。

## 题目大意

题目传送门：[Link to Luogu](https://www.luogu.com.cn/problem/SP13106)。

> 给定 $n$ 个集合，全集共有 $m$ 个元素。求选择一些集合使其并起来是全集的方案数。
>
> $n\leqslant 10^6,m\leqslant 20$。

## 题目分析

$m$ 的数据范围很小，从这里入手，考虑状压。

但是状压 DP 貌似很难实现？

设 $f_S$ 表示集合为 $S$ **的子集**的集合个数。那么 $f_S$ 是可以直接高维前缀和求出来的，FWT 或一下即可。

考虑 $f_S$ 和答案有什么关系？

设 $F_S$ 表示选择的集合的并集为 $S$ **的子集**的方案数，那么只要这个集合是 $S$ 的子集，就可以选（也可以不选，要记得去掉都不选的情况），因此 $F_S=2^{f_S}-1$。

要求的是选择的集合的并集恰好为集合 $S$ 的方案数，子集反演一下即可。

复杂度 $\mathcal O(m\times 2^m+n)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int max_n=2000006,mod=1000000007;
inline int read(){
    int x=0;bool w=0;char c=getchar();
    while(c<'0' || c>'9') w|=c=='-',c=getchar();
    while(c>='0' && c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return w?-x:x;
}
inline void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10^48);
}
inline int mi(int a,int p=mod-2){
    int res=1;
    while(p){
        if(p&1) res*=a,res%=mod;
        a*=a,a%=mod,p>>=1;
    }
    return res;
}

int n,m,S,f[max_n],F[max_n],ans;

inline void OR(int *f,int x=1){
    for(register int k=1,l=2;l<=S;l<<=1,k<<=1)
        for(register int i=0;i<S;i+=l)
            for(register int j=0;j<k;++j)
                f[i+j+k]+=f[i+j]*x%mod,
                f[i+j+k]=(f[i+j+k]+mod)%mod;
}

signed main(){
    n=read(),m=read(),S=(1<<m);
    for(register int i=1;i<=n;++i){
        int k=read(),st=0;
        for(register int i=1;i<=k;++i){
            int p=read()-1;
            st|=(1<<p);
        }
        ++f[st];
    }
    OR(f);
    for(register int i=0;i<S;++i)
        F[i]=mi(2,f[i])-1;
    OR(F,-1);
    write(F[S-1]);
    return 0;
}
```



---

## 作者：Hypercube (赞：1)

纠正一下本题高维前缀和做法的一个误区（虽然不影响通过本题）。

既然 $m$ 很小，考虑将每个箱子的状态压成二进制数 $S$。原题所求即选择若干个二进制数，使得它们或起来为 `(1<<m)-1` 的方案数。

如果我们直接算选择若干个数使它们或起来等于 $S$ 的方案数是困难的。但注意到或运算性质特殊，故而我么尝试计算选择若干个数，使得它们或起来为 $S$ 子集的方案数，设为 $g_S$。

如果我们尝试设 $f_S$ 表示二进制表示下是 $S$ 子集的箱子个数，那么显然有 $g_S=2^{f_S}$。（这一步有不止一篇题解认为应当减去空集，实际上是没有道理的。当然减去空集也不影响所求答案。）

于是我们通过高维前缀和求出 $f_S$，然后求出 $g_S$，再对 $g_S$ 做一遍高维差分即可（也就是高维前缀和的逆运算）。

时间复杂度 $O(n2^n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
inline ll read() {
	ll f=1,x=0;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)) {x=x*10+ch-48;ch=getchar();}
	return x*f;
}
const ll N=1000006,p=1000000007;
ll n,m,f[N],g[N];
ll qpow(ll a,ll b) {
	ll ans=1,base=a;
	while(b) {
		if(b%2) (ans*=base)%=p;
		b/=2;
		(base*=base)%=p;
	}
	return ans;
}
int main() {
	n=read(),m=read();
	for(int i=1;i<=n;i++) {
		int k=read(),nw=0;
		for(int j=1;j<=k;j++) {
			int bt=read();
			nw|=(1ll<<(bt-1));
		}
		f[nw]++;
	}
	for(int i=0;i<m;i++) {
		for(int j=0;j<(1ll<<m);j++) {
			if(j&(1ll<<i)) f[j]+=f[j^(1ll<<i)];
		}
	}
	for(int i=0;i<(1ll<<m);i++) {
		g[i]=qpow(2,f[i]);
	}
	for(int i=0;i<m;i++) {
		for(int j=0;j<(1ll<<m);j++) {
			if(j&(1ll<<i)) g[j]-=g[j^(1ll<<i)],(g[j]+=p)%=p;
		}
	}
	cout<<g[(1ll<<m)-1]<<'\n';
	return 0;
}

```


---

## 作者：ZillionX (赞：0)

# Description

给定 $n$ 个集合，全集共有 $m$ 个元素，求选定一部分集合（可以全选）使得它们的并集为全集的方案数。答案对 $10^9+7$ 取模。

$n \le 10^6, m\le 20$，时限 438ms。

# Solution

不妨设每个集合内的元素为 $a_{i}$（将其看作一个二进制数）。

构造集合幂级数 $F_i(x)$ 使得 $[x^0]F_i(x)=[x^{a_{i}}]F_i(x)=1$，这样 Or 卷积中，卷到 $x^0$ 的意义即为不选，卷到 $x^{a_i}$ 的意义即为选。

不难发现最终答案即为 $[x^{S}]\prod\limits_{i=1}^n F_i(x)$（这里的乘法是 Or 卷积，$S$ 是全集）。

如果直接做的话复杂度是 $\mathcal O(n^2 \log n)$，不可行。注意到任意一个多项式只有两个非零项，我们知道

$$[x^i]{\rm DWT}(F(x))= \sum_{i|j=i}^n [x^j]F(x)$$

因此我们有

$$[x^i]{\rm DWT}(F(x))=[i|0=i]+[i|a_i=i]=1+[i|a_i=i]$$

由于给 $F_i(x)$ 做了 DWT 后，Or 卷积转化为了点积，因此我们设

$$[x^i]P(x)=\prod_{i=1}^n[x^i]{\rm DWT}(F_i(x))$$

此时 $[x^S]{\rm IDWT}(P(x))$ 即为答案。

观察发现 $[x^i]P(x)$ 为若干个 $2$ 和若干个 $1$ 相乘的结果。只要知道 $2$ 的个数，跑一遍快速幂即可求出 $[x^i]P(x)$。

构造多项式 $Q(x)$ 使得 $[x^{a_i}]Q(x)$ 为 $a_i$ 在众集合中出现的次数。不难发现 $[x^i]{\rm DWT}(Q(x))$ 即为 $[x^i]P(x)$ 中 $2$ 的个数。

至此我们就在 $\mathcal O(m2^m)$ 的时间复杂度下完成了本题。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int S=(1<<20)+5;
const LL mod=1e9+7;
int n,m;
LL f[S];
LL Qpow(LL x,LL y) {
	LL Mul=1;
	while (y) {
		if (y&1) Mul=Mul*x%mod;
		x=x*x%mod,y>>=1;
	}
	return Mul;
}
int main() {
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) {
		int k,sta=0;
		scanf("%d",&k);
		for (int j=1;j<=k;j++) {
			int x;scanf("%d",&x);
			sta|=(1<<(x-1));
		}
		f[sta]++;
	}
	for (int i=2,j=1;i<=(1<<m);i<<=1,j<<=1)
			for (int k=0;k<(1<<m);k+=i)
				for (int l=0;l<j;l++)
					f[j+k+l]=(f[j+k+l]+f[k+l])%mod;
	for (int i=0;i<(1<<m);i++)
		f[i]=Qpow(2,f[i]);
	for (int i=2,j=1;i<=(1<<m);i<<=1,j<<=1)
			for (int k=0;k<(1<<m);k+=i)
				for (int l=0;l<j;l++)
					f[j+k+l]=(f[j+k+l]-f[k+l]+mod)%mod;
	printf("%lld",f[(1<<m)-1]);
	return 0;
}
```


---

