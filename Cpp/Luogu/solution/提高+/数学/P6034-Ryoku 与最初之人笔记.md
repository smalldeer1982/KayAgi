# Ryoku 与最初之人笔记

## 题目背景

Ryoku 在阅读「最初之人」的笔记的时候，发现了一个有趣的运算：$\rm xor$，这个运算的输入是两个数，输出是一个数，对应的运算时将输入的两个数化为二进制，再把每一位进行比较，若相同则输出的二进制中的这一位为 $0$，否则为 $1$。 

在关于运算 $\text{xor}$ 笔记的下面有一道习题。Ryoku 很快就得出了答案，她想要考考你。

## 题目描述

Ryoku 向你复述了题目：求：

$$\sum_{a = 0}^n \sum_{b = a + 1}^n [a\equiv b\pmod {a \text{ xor } b}]$$

即：求满足 $a\equiv b\pmod {a \text{ xor } b}$，且 $a,b$ 均为小于等于 $n$ 的非负整数，$a<b$，的有序二元组 $(a,b)$ 个数。

## 说明/提示

**【样例 1 说明】**

符合题意的数对 $(a,b)$ 的有：$(0,1), (0,2)$。

---

**【数据规模与约定】**

对于 $20\%$ 的数据，$n\le 10^3$。  
对于 $60\%$ 的数据，$n\le 10^6$。  
对于 $70\%$ 的数据，$n\le 10^9$。  
对于 $100\%$ 的数据，$2\le n \le 10^{18}$。  

## 样例 #1

### 输入

```
2```

### 输出

```
2```

## 样例 #2

### 输入

```
42```

### 输出

```
274```

# 题解

## 作者：WYXkk (赞：9)

一般情况下，看到 $\text{xor,and,or},+,-$ 等等毒瘤运算结合的时候，下面这个换元都会非常有效：

设 $y=a\;\text{and}\;b$，$a=x+y$，$b=y+z$，则 $a\;\text{or}\;b=x+y+z$，$a\;\text{xor}\;b=x+z$。

比如本题，采用以上换元，我们可以得到：$x+z|(y+z)-(x+y)$，即 $x+z|z-x$。

由于 $z+x\ge z-x>0$，所以 $x=0$，即 $a$ 的二进制位被 $b$ 的二进制位完全包含。

因此，我们枚举 $b$，对于每个 $b$，很显然有 $2^{f(b)}-1$ 个满足条件的 $a$，其中 $f(b)$ 表示 $b$ 在二进制下为 $1$ 的位的个数。

所以答案为 $\sum\limits_{i=1}^n(2^{f(i)})-n$。

记 $s(n)=\sum\limits_{i=1}^n2^{f(i)}$。

$f(n)$ 显然是可以 $O(\log n)$ 求的：（`ll`代表`long long`，后面同理）

```cpp
inline ll f(ll n){if(!n)return 0;return f(n>>1)+n&1;}
```

即，$f(2n+1)=f(n)+1,f(2n)=f(n)$。

（代码中我使用了另一种实现方式）

由于我们有：

$$\begin{aligned}s(2n)&=\sum_{i=1}^{2n}2^{f(i)}\\&=\sum_{i=1}^n2^{f(2i-1)}+\sum_{i=1}^n2^{f(2i)}\\&=\sum_{i=1}^n2^{f(i-1)+1}+\sum_{i=1}^n2^{f(i)}\\&=2(1+\sum_{i=1}^{n-1}2^{f(i)})+\sum_{i=1}^n2^{f(i)}\\&=2+2s(n-1)+s(n)\\&=3s(n-1)+2^{f(n)}+2\end{aligned}$$

因此我们就可以递归/倍增求 $s(n)$ 了。最后减去 $n$ 即可。

$\texttt{code:}$

```cpp
#include<cstdio>
#include<iostream>
#include<fstream>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define Set(a) memset(a,0,sizeof(a))
#define F(i,a,b) for(register int i=a,i##end=b;i<=i##end;++i)
#define UF(i,a,b) for(register int i=a,i##end=b;i>=i##end;--i)
#define openf(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
#define re register
#define ri re int
#define il inline
typedef long long ll;
typedef unsigned long long ull;
template<typename T> inline T rd(T& x)
{
	T f=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(; isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(T)(c-'0');
	x*=f;
	return x;
}
ll rd(){ll x;rd(x);return x;}
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
const int inf=1<<30;

const ll p=1000000007;
ll p2[70];
ll mod(ll t){return t>=p?t-p:t;}
int bitc(ll x){int ans=0;while(x)x&=x-1,++ans;return ans;}
ll f(ll n){return p2[bitc(n)];}
ll sum(ll n)
{
	if(n==0) return 0;
	if(n&1) return mod(sum(n^1)+f(n));
	ll t=sum((n>>1)-1);
	return (3*t+f(n>>1)+2)%p;
}
int main()
{
	p2[0]=1;F(i,1,64) p2[i]=mod(2*p2[i-1]);
	ll n;
	cin>>n;
	cout<<((sum(n)-n)%p+p)%p<<endl;
	return 0;
}
```



---

## 作者：xiejinhao (赞：5)

# 导言

因为这题没做出来这场比赛我 $360$……（差一点就 $AK$ 了……）

其实正解不难想，而暴力更好想。因此下面会给出两种解题的思路。

也感谢大家能够耐心地阅读完我的这篇题解。

声明：若要转载此文或部分内容，请注明出处。谢谢合作。

# 解法 1

考场上啥都想不出来……（~~是我蠢了~~）咋办呢？

打个暴力！暴力计算是 $O(n^2)$ 的，可以拿到 $20pts$。

暴力打完了可不能坐以待毙啊，于是开始找规律，我发现这个数列在某网站有收录，但都是英文，而且没有通式。（这下完了，连 $60pts$ 都要没了？）

不！有的时候原序列没有规律，不妨换成 **差分** 数列。

我们对 $n=1…20$ 进行一下差分，得到：

~~~
(0) 1 1 3 1 3 3 7 1 3 3 7 3 7 7 15 1 3 3 7 3
~~~

如果能 $O(N)$ 求出差分数组，就可以 $O(N)$ 求出答案。定义差分数组为 $b$。

乍一看没什么规律，但有些数字相等，有些数字是“乘二加一”的关系？看看有没有规律。发现相邻的没有规律，又考虑到数据范围是 $log$ 的，所以看看“除二”之类。果不其然，就让我们找到了：

$$b_i=\begin{cases}0&i=0\\b_{\frac{i}{2}}& i\text{ 为偶数}\\ 2×b_{\frac{i}{2}}+1&i\text{ 为奇数}\end{cases}$$

（上面的除法默认向下取整）

有了这个递推式我们就可以 $O(N)$ 求出 $b$ 数组，最终的答案即为：

$$ans=\sum_{i=1}^{n}b_i$$

这个是比较简单的。这样可以拿到 $60pts$。

接下来考虑优化。（$70pts$ 分段打表即可）

因为原数组可以通过差分数组还原，令原数组为 $S$。（上面已经提到差分数组是 $n=1,2…$ 对应答案的差分数组，所以 $S$ 即为答案数组，最终答案为 $S_n$）

**下面的除法默认向下取整。**

先将上面求 $b$ 的式子变形一下：

$$\begin{cases}b_0=0\\b_{2i}=b_i\\b_{2i+1}=2b_i+1\end{cases}$$

那么考虑，当 $n$ 为偶数的时候：

$$S_n=\sum_{i=1}^{n}b_i=\sum_{i=1}^{n/2}b_{2i-1}+\sum_{i=1}^{n/2}b_{2i}$$

上面的变换是对 $b$ 数组进行奇偶分类，然后我们发现 $b$ 数组已经出现了式子，再次套用上面 $b$ 数组的递推式可以得到：

$$S_n=\sum_{i=1}^{n/2}(2b_{i-1}+1)+\sum_{i=1}^{n/2}b_{i}=\frac{n}{2}+\sum_{i=0}^{n/2-1}2b_{i}+\sum_{i=1}^{n/2}b_{i}$$

因为 $b_0=0$，因此又可以再次变换：

$$S_n=n+2\sum_{i=1}^{n/2-1}b_{i}+\sum_{i=1}^{n/2}b_{i}=2S_{\frac{n}{2}-1}+S_{\frac{n}{2}}+\frac{n}{2}$$

因此我们得到了偶数的 $S$ 递归式。

接下来考虑 $n$ 为奇数。 $n$ 为奇数时唯一不同的是还要计算上 $n$，因为上面的计算方法会忽略掉 $n$ 这个奇数。（可以观察一下奇数部分，左边的和式）

所以重新列式：

$$S_n=\sum_{i=0}^{n/2}b_{2i+1}+\sum_{i=1}^{n/2}b_{2i}$$

（因为与上面变换类似我就不多列一个式子了）

你会发现我们左边的和式变换了一下，这样就可以考虑到 $n$ 也为奇数。

又因为当 $n=1$ 时，也即 $i=0,2i+1=1$，$S_n=1$（打表可以计算，手算也可以），那么我们可以把左边的和式下界 $i$ 从 $0$ 变为 $1$，然后整个式子加一：

$$S_n=1+\sum_{i=1}^{n/2}b_{2i+1}+\sum_{i=1}^{n/2}b_{i}$$

（因为很多部分和上面相同这边直接化开）

继续：

$$S_n=1+\sum_{i=1}^{n/2}(2b_{i}+1)+S_{\frac{n}{2}}=3S_{\frac{n}{2}}+\frac{n}{2}+1$$

（已经说过除法默认下取整）

现在 $n$ 的情况已经讨论完了，题目也解决了。

重新整理一下上面的式子：（据题目的式子知道 $S_0=0$）

$$S_n=\begin{cases}0&n=0\\2S_{\frac{n}{2}-1}+S_{\frac{n}{2}}+\frac{n}{2}&n\text{ 为偶数}\\3S_{\frac{n}{2}}+\frac{n}{2}+1&n\text{ 为奇数}\end{cases}$$

这样我们就可以利用递归求出 $S_n$了，时间复杂度 $O(\text{log }n)$。 记得记忆化，不然会重复算很多，如果懒得手写 $Hash$ 表，就用 $map$，时间复杂度 $O(\text{log}^2n)$。

（当时我多么蠢，就推个式子竟然没想到……）

# 解法 2

考虑把原来的式子变形一下，因为 $a<b$，所以原来的式子相当于：

$$\sum_{a=0}^{n}\sum_{b=a+1}^{n}[ \ b\text{ xor }a\mid b-a\ ]$$

因为异或相当于不退位的减法，所以在二进制下模拟即可发现：

$$b\text{ xor }a≥b-a$$

所以上式的主体部分即 $[ \ b\text{ xor }a=b-a \ ]$。

在二进制下，发现 $a$ 中为 $1$ 的位在 $b$ 中一定要为 $1$，通过枚举 $b$，利用组合数学即可计算。计算方法就是：假设 $i$ 中有 $f(i)$ 位是 $1$，那么我们可以取其中的 $1$ 位，方案即 $C_{f(i)}^1$，同理取 $2$ 位的方案是 $C_{f(i)}^2$，以此类推，这样枚举的方案就是满足 $i\text{ xor }?=i-?$ 的。

这里不用考虑排列，是因为这些数字在 $b$ 中已经排好。

考虑方案总和，因为 $a<b$，即 $a≠b$，因此 $C_{f(i)}^{f(i)}=1$ 的方案排除，那么总方案数（上面的 $S$ 数组，解法 1）有：

$$S_{n}=\sum_{i=1}^{n}(2^{f(i)}-1)=\sum_{i=1}^{n}2^{f(i)}-n$$

使用 $lowbit$ 运算可计算 $i$ 中 $1$ 的数量，均摊是 $O(1)$ 的，可以拿到 $60pts$，总的代码如下：

~~~cpp
#include<bits/stdc++.h>
using namespace std;

#define lowbit(x) (x & -x)

int calc(int x) {
	int cnt = 0;
	for( ; x; x -= lowbit(x))
		cnt++;
	return cnt;
}

int bit[32];

int main() {
	int n;
	scanf("%d", &n);
	bit[0] = 1;
	for(int i = 1; i < 32; i++)
		bit[i] = 1 << i;
	int ans = 0;
	for(int i = n; i; i--)
		ans += bit[calc(i)] - 1;
	printf("%d\n", ans);
	return 0;
}
~~~

接下来考虑优化。

观察 $f$ 数组是否也具有可递归的性质？其实有的，在位运算中，右移一位就是除 $2$，考虑奇数除二，那么 $f_n=f_\frac{n}{2}+1$，这是因为奇数右移的时候最低位的 $1$ 被舍去了；同理偶数 $f_n=f_\frac{n}{2}$，因为偶数最低位为 $0$。

（知道位运算的上面应该比较显然）

整理一下：

$$\begin{cases}f_0=0\\f_{2i}=f_i\\f_{2i+1}=f_i+1\end{cases}$$

然后仍然按照上面的方法推理即可，我记得我翻了一下别人的题解也有这种方法推理的，因为篇幅限制这里就不推了，大家自己尝试一下如何？


但是我记得别人推的情况只有偶数的，建议大家推下奇数的情况看看是否相同。

下面是我推出的结论：

$$S_n=\begin{cases}0&n=0\\2S_{\frac{n}{2}-1}+S_\frac{n}{2}+\frac{n}{2}&n\text{ 为偶数}\\3S_\frac{n}{2}+\frac{n}{2}+1&n\text{ 为奇数}\end{cases}$$

与解法 $1$ 推出来的式子不谋而合，可以 $O(\text{log }n)$ 计算。

# 代码

至此，本题的两种解法就讲完了，第一种想法适合考场写，而第二种想必才能够成为正解。但是考场发现规律也是不容易的，个人认为第一种解法比较实用。

我知道你们只想看代码，但是因为该讲的我讲完了，所以下面的代码不会有任何注释。

因为两种解法的式子相同，代码自然也就相同：

~~~cpp
#include<bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

map<long long, int> f;

int solve(long long n) {
	if(!n) return 0;
	if(f[n]) return f[n];
	if(n & 1) 
		f[n] = (3LL * solve(n >> 1) + (n >> 1) + 1) % mod;
	else f[n] = (2LL * solve((n >> 1) - 1) + solve(n >> 1) + (n >> 1)) % mod;
	return f[n];
}

int main() {
	long long n;
	scanf("%lld", &n);
	printf("%d\n", solve(n));
	return 0;
}
~~~

因为我懒得手写 $Hash$ 表，又不想用 $C++11$ 的 $unordered\_map$，因此选择了 $C++ \ STL$ 中的 $map$，所有操作都是 $O(\text{log }n)$ 的，因此时间复杂度 $O(\text{log}^2n)$，期望得分 $100pts$。

# 后记

感谢大家阅读完这一篇题解，同时我也再次重申：若要转载此文或部分内容，请注明出处。

如果对本文有任何疑问或者指出错误，请私信我（洛谷）。

（~~**不知道我写了这么多可否无耻的求个赞……**~~）

## Update

- $2020-02.02$，自己阅读的时候发现了一些公式错误，进行了修正，没想到第一次修正的时候管理审核那么快，这里说声抱歉，还希望管理重审。

---

## 作者：Transfixion_ (赞：1)

题目链接：[$\texttt{Link}$](https://www.luogu.com.cn/problem/P6034)

## $\textbf{Description}$

给定 $n$，求满足 $a\equiv b\pmod{(a\oplus b)}$ 的有序数对 $(a,b)$ 的个数。

数据范围 $2\le n\le 10^{18}$.

## $\textbf{Solution}$

不妨 $a>b$，则题设化为 $(a\oplus b)\mid (a-b)$，又因为 $a\oplus b\geq a-b$，所以 $a\oplus b=a-b$。

这说明 $b$ 在二进制下是 $a$ 的子集，所以对于每个 $a$，符合条件的 $b$ 数为 $(2^{\operatorname{popcount}(a)}-1)$。

$a$ 取遍 $[1,n]$ 中的所有整数，故答案为：

$$\left(\sum_{i=1}^n 2^{\operatorname{popcount(i)}}\right)-n$$

记这个 $\sum$ 为 $f(n)$。看上去通项不存在或很难求，考虑递归或倍增。

OEIS 一下发现是 [A074330](https://oeis.org/A074330)。从里面找一个形式比较好看的（当然你也可以自己推）：

$$f(2n+1) = 3f(n) + 2$$

看上去没办法求以偶数为下标的 $f$。事实上，任意的 $f(n)-f(n-1)$ 都可以 $\mathcal O(1)$ 求得，因此 $f(2n)$ 和 $f(2n+1)$ 之间可以随意转化。

整理一下就是：

$$f(n)=\begin{cases}3f\left(\left\lfloor n/2\right\rfloor\right)+2,&2\nmid n,\\f(n+1)-2^{\operatorname{popcount}(n+1)},&2\mid n.\end{cases}$$

递归边界为 $f(0)=0$。时间复杂度 $\mathcal O(\log n)$。

稍微注意一下 `long long` 和取模。

---

## 作者：feecle6418 (赞：1)

首先答案为 $\sum_{i=1}^n 2^{f(i)}$，$f(i)$ 为 $i$ 的二进制表示中 $1$ 的个数，证明参见出题人的题解。重点在于如何求它。

枚举 $f(i)=j$，原式等于 $\sum_{j=1}^{64}2^jg(n,j)$，$g(n,j)$ 为小于等于 $n$ 的、二进制表示里有 $j$ 个 $1$ 的数的个数。求 $g(n,j)$ 的方法很多，我用了数位 DP。

记忆化搜索，维护目前 $1$ 的个数，假如到最后一位，$1$ 的个数太多/太少，就返回 $0$。其他的就是标准的模板。

代码如下：

```
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
typedef long long ll;
ll f[80][80][2],c[80],l=0;
const ll mod=1000000007;
void Turn(ll k){
    memset(c,0,sizeof(c));
    while(k)c[++l]=k%2,k/=2;
    return ;
}
ll dp(ll x,bool flag,ll sum){
	if(sum<0)return 0;
	if(!x){
		if(!sum)return 1;
		return 0;
	}
	if(~f[x][sum][flag])return f[x][sum][flag];
	f[x][sum][flag]=0;
	for(int i=0;i<=(flag?c[x]:1);i++){
		f[x][sum][flag]+=dp(x-1,flag&&i==c[x],sum-i);
	}
	return f[x][sum][flag];
}
ll Calc(ll n,ll k){
	memset(f,-1,sizeof(f));
	ll r=dp(l,1,k);
	return r%mod;
}
int main(){
    ll x,ans=0;
    scanf("%lld",&x);
	Turn(x);
    for(int i=1;i<=63;i++)ans=(ans+((1ll<<i)%mod)*(Calc(x,i)%mod)%mod)%mod;
    printf("%lld\n",(ans-x%mod+mod)%mod);
}
//100000000000000000
```

---

## 作者：Error_Eric (赞：0)

### 题意

求满足 $a\equiv b\pmod {a \text{ xor } b}$ 且 $a,b$ 均为小于等于 $n(\le10^{18})$ 的非负整数。

### Sol

等价于求 $\sum_{i=1}^n2^{f(i)}-n$ 其中 $f(i)$,为 $i$ 的二进制表示中 $1$ 的个数，证明参见出题人的题解。（~~既然fee的题解可以这样写钠我也这样写。~~）

这里提供一种更加简单的求值方法。

考虑到 $f(i)$ 很小，可以统计 $f(i)=x$ 的个数。换言之，求一个数组，其中 $c_i\sum_{j=1}^n[f(j)=i]$。这个 $c$ 的长度显然不超过 $\lceil \log n\rceil\approx 60$。

那么怎么求 $c_i$ 呢？

如果 $n+1$ 是二的幂次，那么在二进制下任选一位变成 $1$ ,一共选 $i$ 个，符合组合数的定义，答案显然是 $c_i=C_{\log_2n}^i$。

如果 $n+1$ 不是二的幂次，我们可以分类讨论 $x>n+1-lowbit(n+1)$ 和 $x\le n+1-lowbit(n+1)$ 。（这里 lowbit 就是树状数组 lowbit 的定义），显然后者可以递归求解，前者相当于二的幂次的那种情况加上固定个数个 $1$。

复杂度 $f(n)\log n+\log^2n$ 跑了 31ms，比最优解慢了 1ms 但是比其他题解都快 qwq。

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<vector>
using namespace std;
typedef long long ll;
inline const void readln(ll&I){
    I=0;char C=getchar();
    while(!isdigit(C))C=getchar();
    while( isdigit(C))(I*=10ll)+=(C-'0'),C=getchar();
}
const unsigned long long p=1e9+7;
struct fint{int v;fint(unsigned long long V=0){v=V%p;}};
fint operator+ (fint U,fint V){return (1ull*U.v+V.v)%p;}
fint operator* (fint U,fint V){return (1ull*U.v*V.v)%p;}
fint operator+=(fint&U,fint V){return U=U+V;}
fint operator*=(fint&U,fint V){return U=U*V;}
fint f[61][61],c[61],ans;
fint C(int n,int k){
    fint&ans=f[n][k];
    if(k==0)return 1;
    else if(ans.v!=0)return ans;
    else if((k<<1)>n)return ans=C(n,n-k);
    else return ans=C(n-1,k)+C(n-1,k-1);
}
int ctbt(ll val){
    int res=0;
    while(val)res++,val-=(val&-val);
    return res;
}
ll n;
int q;
int main(){
    readln(n),ans=p-(n%p),q=ctbt(++n);
    for(int i=0;(1ll<<i)<=n;i++){
        if(n&(1ll<<i)){
            --q,n^=(1ll<<i);
            for(int j=0;j<=i;j++)
                c[j+q]+=C(i,j);
        }
    }
    for(int i=1;i<=60;i++)
        ans+=c[i]*((1ll<<i)%p);
    printf("%d\n",ans.v);
}
```

---

## 作者：DerrickLo (赞：0)

不妨将 $a$ 和 $b$ 的顺序互换，也就是假设 $a>b$。

将 $a\equiv b\pmod{a\operatorname{xor}b}$ 转化为 $(a\operatorname{xor}b)\space|\space(a-b)$，因为 $a\operatorname{xor}b\in [a-b,a+b]$，也就是说 $a\operatorname{xor} b\ge a-b$，所以 $a\operatorname{xor} b=a-b$。

我们考虑 $a\operatorname{xor}b=a-b$ 当且仅当 $b$ 在二进制下是 $a$ 的子集，那么对于每个 $a$，这样的 $b$ 的个数就是 $2^{\operatorname{popcount}(a)}-1$。

那答案就是 $\displaystyle{\sum_{i=1}^{n}(2^{\operatorname{popcount}(i)}-1)}$。

因为 $2\le n\le 10^{18}$，所以我们想一些 $\operatorname{polylog}$ 的做法。考虑先枚举 $\operatorname{popcount}(a)=x$，然后再枚举 $a$ 与 $n$ 在二进制下的最长前缀是什么。如果从最高位到第 $i+1$ 位都是相同，而第 $i$ 位不同，设 $n$ 的二进制表示下从最高位到第 $i+1$ 位一共有 $k$ 个 $1$，那么满足的 $a$ 的个数就是 $\dbinom{i-1}{x-k}$。预处理组合数即可。

时间复杂度 $\mathcal O(\log^2 n)$。

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
#define int long long
using namespace std;
int n,ans,C[105][105];
int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0); 
	cin>>n;
	for(int i=1;i<=100;i++)C[i][0]=C[i][i]=1;
	for(int i=1;i<=100;i++)for(int j=1;j<i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	for(int i=1;i<=61;i++){
		int cnt=0;
		for(int j=61;j;j--){
			if(!(n&(1ll<<(j-1))))continue;
			if(cnt>i)continue;
			ans+=(ksm(2,i)-1)*C[j-1][i-cnt]%mod,cnt++; 
		}
	}
	ans+=ksm(2,__builtin_popcountll(n))-1,ans%=mod;
	cout<<ans;
}
```

---

