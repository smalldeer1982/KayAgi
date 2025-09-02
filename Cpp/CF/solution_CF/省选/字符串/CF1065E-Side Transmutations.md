# Side Transmutations

## 题目描述

考虑一个字符集合$A$（$A$中元素互不相同）和一个长度为$n$的字符串$S$，其中$S$中的字符都属于集合$A$。

给你一个包含 $m$ 个整数的序列 $b$  ($b_1<b_2<\dots<b_m$)。你可以对字符串 $S$ 作以下的操作：

1.选择一个合法的 $i$ ,并且令 $k=b_i$ ;

2.取出 $S$ 中前 $k$ 个字符 $Pr_k$ ;

3.取出 $S$ 中后 $k$ 个字符$Su_k$ ;

4.将 $S$ 中前 $k$ 个字符替换成翻转后的 $Su_k$ ;

5.将 $S$ 中后 $k$ 个字符替换成翻转后的 $Pr_k$ ;

举个例子，我们令 $S=$ "abcdefghi"，$k=2$ 。这时$Pr_2=$ "ab"，$Su_2=$ "hi"，翻转后有 $Pr_2=$ "ba"，$Su_2=$ "ih"，那么最终得到的字符串 $S$ 就是 "ihcdefgba"。

这个操作可以被执行许多次（可能是零次），任何一个 $i$ 也可以被使用多次。

我们将字符串 $S$ 和 $T$ 称为相等的字符串，当且仅当存在一个操作序列，将字符串 $S$ 变成 $T$。对于上面的例子来说，"abcdefghi" 和 "ihcdefgba" 是相等的。注意到 $S$ 和它自己也是相等的。
你的任务很简单，数出互不相同的字符串的个数。
最终的答案可能会非常大，因此你只需要输出答案 $mod$ $998244353$ 的结果。

## 样例 #1

### 输入

```
3 1 2
1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
9 2 26
2 3
```

### 输出

```
150352234
```

## 样例 #3

### 输入

```
12 3 1
2 5 6
```

### 输出

```
1
```

# 题解

## 作者：猪脑子 (赞：15)

~~（哇，居然没有题解？赶紧水一发）~~

对于这道题，我们首先可以将一个字符串通过 $b_i$ **划分成几个段**：

![](https://cdn.luogu.com.cn/upload/pic/39069.png)

然后我们再考虑其他事情。

首先对于任意 $b_i$ 到 $b_{i+1}$ 这一段（也包括从 $0$ 到 $b_{i-1}$），我们可以通过选择 $i$ 和 $i+1$ 来实现将这一段与右边对应的一段翻转。

其次，对于 $b_m$ 以及它与中点对称的位置组成的一段，我们是无法进行翻转的。

那么我们就可以将每一段分开考虑。

对于前面的（这里指 $i < m$）每一段，我们设 $len$ 为这一段的长度（即 $b_i-b_{i-1}$），那么考虑两种情况：

1.将这一段翻到右边去所得到的字符串与原串不相同，那么对于左边的部分，有 $|A|^{len}$ 种可能，而对于每种可能，右边都有 $|A|^{len}-1$ 种方式与之对应，使得翻转后与原串不相同。因此，这种情况对答案的贡献就是 $ \frac{|A|^{len} * (|A|^{len}-1)}{2}$，其中除以 $2$ 的原因是因为我们将正反两种情况都算了一遍，而这两种情况实际上是等价的（比如左边是 "ab"、右边是 "cd" 和左边是 "dc"，右边是 "ba" 的情况）；

2.将这一段翻到右边去所得到的字符串与原串相同，易知对于左边的 $|A|^{len}$ 种可能，右边都只有一种情况与之对应，使得翻转后新串与原串相同。那么这种情况对答案的贡献就是 $|A|^{len}$。

综上，对于这两种情况，对答案的贡献就是 $\frac{|A|^{len} * (|A|^{len}-1)}{2}+|A|^{len}$。

那么对于中间的 $n-2 * b_m$ 个字符，它们是无法翻转的，因此它们对答案的贡献就是 $|A|^{n-2 * b_m}$。

那么，最终答案就是讲每一块的贡献乘起来的到的结果。

~~（我讲的好不好，快夸夸我）~~

## 贴代码啦~~~

```
#include<iostream>
#include<algorithm>
#include<cstdio>
#define Mod 998244353
using namespace std;
long long fpow(long long a,long long b)
{
	long long ans=1,t=a;
	while(b)
	{
		if(b&1)ans=ans*t%Mod;
		t=t*t%Mod;
		b>>=1;
	}
	return ans;
}
int n,m,A;
int b[200010];
int main()
{
	scanf("%d %d %d",&n,&m,&A);
	for(int i=1;i<=m;i++)
		scanf("%d",&b[i]);
	long long ans=1;
	for(int i=1;i<=m;i++)//每个小段的贡献
		ans=(ans*((long long)fpow(A,b[i]-b[i-1])
        +(long long)fpow(A,b[i]-b[i-1])
        *(fpow(A,b[i]-b[i-1])-1)%Mod
        *fpow(2,Mod-2)%Mod)%Mod+Mod)%Mod;
	ans=ans*fpow(A,n-b[m]-b[m])%Mod;//中间段的贡献
	printf("%I64d\n",ans);
	return ~~(0-0);//日常卖萌
}
```

~~（~所以要不要点个赞啊~）~~

---

## 作者：George1123 (赞：4)

[$\Huge{\color{#e0a920}{\tt My~Cnblogs}}$](https://www.cnblogs.com/Wendigo/p/12976171.html)

---
> [CF1065E Side Transmutations](https://www.luogu.com.cn/problem/CF1065E)

> $n$ 和 $m$ 和 $k$ 和序列 $b_i(1\le i\le m,1\le b_i\le b_{i+1}\le \frac n2)$。对于字符串 $s$，如果选其 $b_i$ 前缀和 $b_i$ 后缀翻转并交换能变成字符串 $s'$，则 $s,s'$ 是相等的。求有多少个长度为 $n$ 的字符串，字符集大小为 $k$，互不相等。答案 $\bmod 998244353$。

> 数据范围：$2\le n\le 10^9$，$1\le m\le \min(\frac n2,2\cdot 10^5)$，$1\le k\le 10^9$。

---
听神仙说这是群论，是 $\tt Polya$，小蒟蒻没有听说过，但是手推出来这题了。

既然**蒟蒻啥都不会**，那么就慢慢做这题。

---
把字符串分成 $2m+1$ 段。

如 $m=2$ 字符串就是 $\overrightarrow{A}\overrightarrow{B}\overrightarrow{C}\overrightarrow{D}\overrightarrow{E}$：

> $\overrightarrow{S}$ 指的是一个有顺序的字符串。

$\overrightarrow{A}$ 表示 $s_{1\to b_1}$。

$\overrightarrow{B}$ 表示 $s_{b_1+1\to b_2}$。

$\overrightarrow{C}$ 表示 $s_{b_2+1\to n-b_2}$。

$\overrightarrow{D}$ 表示 $s_{n-b_2+1\to n-b_1}$。

$\overrightarrow{E}$ 表示 $s_{n-b_1+1\to n}$。

---
- **解决 $m=1$ 的情况：**

$$\overrightarrow{A}\overrightarrow{B}\overrightarrow{C}=\overleftarrow{C}\overrightarrow{B}\overleftarrow{A}$$

如果 $\overrightarrow{A}=\overleftarrow{C}$：$k^{n-b_1}$ 种。

如果 $\overrightarrow{A}\not=\overleftarrow{C}$：$(k^n-k^{n-b_1})\cdot 2^{-1}$ 种。

**答案为 $k^{n-b_1}+(k^n-k^{n-b_1})\cdot 2^{-1}=(k^n+k^{n-b_1})\cdot 2^{-1}$ 种。**

---
- **解决 $m=2$ 的情况：**

$$\overrightarrow{A}\overrightarrow{B}\overrightarrow{C}\overrightarrow{D}\overrightarrow{E}=\overleftarrow{E}\overrightarrow{B}\overrightarrow{C}\overrightarrow{D}\overleftarrow{A}=\overrightarrow{A}\overleftarrow{D}\overrightarrow{C}\overleftarrow{B}\overrightarrow{E}=\overleftarrow{E}\overleftarrow{D}\overrightarrow{C}\overleftarrow{B}\overleftarrow{A}$$

如果 $\overrightarrow{A}=\overleftarrow{E}\&\overrightarrow{B}=\overleftarrow{D}$：$k^{n-b_2}$ 种。

如果 $\overrightarrow{A}\not=\overleftarrow{E}\&\overrightarrow{B}=\overleftarrow{D}$：$(k^{n-b_2+b_1}-k^{n-b_2})\cdot 2^{-1}$ 种。

如果 $\overrightarrow{A}=\overleftarrow{E}\&\overrightarrow{B}\not=\overleftarrow{D}$：$(k^{n-b_1}-k^{n-b_2})\cdot 2^{-1}$ 种。

如果 $\overrightarrow{A}\not=\overleftarrow{E}\&\overrightarrow{B}\not=\overleftarrow{D}$：$(k^n-k^{n-b_1}-k^{n-b_2+b_1}+k^{n-b_2})\cdot 2^{-2}$ 种。

**答案为 $(k^n+k^{n-b_1}+k^{n-b_2+b_1}+k^{n-b_2})\cdot 2^{-2}$ 种。**

--- 
**小蒟蒻于是就发现规律了：**

令集合 $st=\{b_1,b_2-b_1,...,b_m-b_{m-1}\}$。

$$Ans=2^{-m}\sum_{sub\in st}k^{n-\sum_{x\in sub}x}$$ 

看似诡异，但是其实这个一把这个式子裂开就发现是可以合并的：

![如果图炸了在评论区中D蒟蒻](https://i.loli.net/2020/05/28/aDFbRkqwN6VcLS7.jpg)


然后就做完了。因为还要 $\bmod 998244353$，所以**时间复杂度为 $\Theta(m\log mod)$**。

---
- **代码**

```cpp
#include <bits/stdc++.h>
using namespace std;

//Start
typedef long long ll;
typedef double db;
#define mp(a,b) make_pair(a,b)
#define x first
#define y second
#define b(a) a.begin()
#define e(a) a.end()
#define sz(a) int((a).size())
#define pb(a) push_back(a)
const int inf=0x3f3f3f3f;
const ll INF=0x3f3f3f3f3f3f3f3f;

//Data
const int N=2e5;
const int mod=998244353;
int n,m,k,b[N+7];

//Pow
int Pow(int a,int x){
	if(!a) return 0; int res=1;
	for(;x;a=(ll)a*a%mod,x>>=1)if(x&1) res=(ll)res*a%mod;
	return res;
}

//Main
int main(){
	scanf("%d%d%d",&n,&m,&k),k%=mod; //这句不加 Wrong on test 11
	for(int i=1;i<=m;i++) scanf("%d",&b[i]);
	int res=1;
	for(int i=1;i<=m;i++) res=(ll)res*(Pow(k,b[i]-b[i-1])+1)%mod;
	res=(ll)res*Pow(k,n-b[m])%mod;
	res=(ll)res*Pow(Pow(2,m),mod-2)%mod;
	printf("%d\n",res);
	return 0;
}
```
---
**祝大家学习愉快！**

---

## 作者：蒟蒻tyy (赞：1)

$\mathcal Desciption:$

$\quad$ [传送门](https://www.luogu.com.cn/problem/CF1065E)

$\mathcal Solution:$

$\quad$ 憨憨题，一眼就是 $\mathrm{Burnside}$ 裸题，希望管理帮忙打个 $\mathrm{tag}$ ~~（这题解区里写的都是啥）~~。

$\quad$ 首先，一个操作不可能用两次，不然就是白给。那么显然置换群的大小为 $2^m$，也就是每个 $b$ 用或者不用。

$\quad$ 对于一个 $y = b$ 的操作，其实是对应二元组位置的交换：

$$
(1,n) \ \ (2,n-1) \ \ (3,n-3) \ \  \cdot\cdot\cdot \ \ (b,n-b+1) 
$$

$\quad$ 对于单个置换的不动点很好算，但是若干置换组合起来就很尴尬。

$\quad$ 这启发我们对 $b$ 数组进行差分：$b_i-b_{i-1} \to b_i$ 。不妨记录为 $c$，显然 $b,c$ 是等价的置换群。

$\quad$ 那么最后的答案为：

$$
ans = \frac{1}{2^m}\sum\limits_{C}t^{n-\sum c}
$$

$\quad$ 按照上面式子利用一定的技巧计算即可。

```
#include <bits/stdc++.h>
using namespace std ;
const int mod = 998244353,N = 2e5+10 ;
inline int add(int a,int b){ return a+b >= mod ? a+b-mod : a+b ; }
inline int sub(int a,int b){ return a >= b ? a-b : a-b+mod ; }
inline int mul(int a,int b){ return 1ll*a*b%mod ; }
inline int power(int a,int b){
	int res = 1 ;
	for( ; b ; b >>= 1){
		if(b&1) res = mul(res,a) ;
		a = mul(a,a) ; 
	}
	return res ;
}
int n,m,t,ans,a[N] ; 
int main(){
	//freopen("in.txt","r",stdin) ;
	ios::sync_with_stdio(false) ; 
	cin >> n >> m >> t ;
	for(int i = 1 ; i <= m ; i++) cin >> a[i] ;
	ans = power(t,n-a[m]) ;
	for(int i = m ; i >= 1 ; i--) a[i] -= a[i-1] ;
	ans = mul(ans,power(power(2,m),mod-2)) ;
	for(int i = 1 ; i <= m ; i++) ans = mul(ans,add(1,power(t,a[i]))) ;
	cout << ans << endl ; 
	return 0 ; 
}
```

---

## 作者：Aigony (赞：0)

本文节选自 [Burnside 引理 与 Pólya 定理 学习笔记](https://www.cnblogs.com/ying-xue/p/burnside-polya.html)。

首先可以发现翻转是可以抵消的。如果我们操作 $b_1$，再操作 $b_2$，再操作 $b_1$，这相当于只操作了一个 $b_2$。也就是说，想要得到最终状态我们只关心每个 $b_i$ 被操作次数的奇偶性。

考虑 Polya 定理，但是发现不动点看起来不好算。

进一步对 $b_i$ 进行转化，考虑将字符串分成形如 $[b_1,b_2),[b_2,b_3),\dots$ 的若干段。那么我们统计不动点的时候只关心每一段是否被翻转。
不难看出，字符串每段的翻转状态与 $b$ 的操作次数奇偶性序列构成双射。设 $len_i$ 表示第 $i$ 段的长度。

那么如果第 $i$ 段被翻转了，这一段本身的贡献是 $|A|^{len_i}$；否则为 $|A|^{2len_i}$。而对于中间长度为 $n-2len_m$ 且永远不会被翻转的段，贡献恒为 $|A|^{n-2len_m}$。

故设 $T=\{1,2,\dots,n\}$，本质不同的方案数为

$$
\begin{aligned}
&\frac{|A|^{n-2len_m}}{2^m}\sum_{S\subseteq T}([i\in S]|A|^{len_i})+([i\notin S]|A|^{2len_i})\\
=&\frac{|A|^{n-2len_m}}{2^m}\prod_{i=1}^m (|A|^{len_i}+|A|^{2len_i})
\end{aligned}
$$

直接计算即可，时间复杂度为 $\mathcal{O}(m\log n)$。

```cpp
#define int long long
const int N=2e5+5,mod=998244353;
int n,m,A,b[N];
int l[N];
il int qpow(int n,int k=mod-2)
{
    int res=1;
    for(;k;n=n*n%mod,k>>=1) if(k&1) res=res*n%mod;
    return res;
}
signed main()
{
    n=read(),m=read(),A=read();
    for(int i=1;i<=m;i++) b[i]=read();
    for(int i=1;i<=m;i++) l[i]=b[i]-b[i-1];
    int sum=1,ans=0;
    for(int i=1;i<=m;i++) sum=sum*(qpow(A,l[i])+qpow(A,2*l[i]))%mod;
    ans=sum*qpow(A,n-2*b[m])%mod;
    ans=ans*qpow(qpow(2,m))%mod;
    printf("%lld\n",ans);
    return 0;
}
```

---

