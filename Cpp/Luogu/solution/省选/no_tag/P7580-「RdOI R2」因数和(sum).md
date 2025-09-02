# 「RdOI R2」因数和(sum)

## 题目背景

monsters 喜欢因数，所以他要出一道关于因数的题。

## 题目描述

众所周知，$i$ 的标准分解形式为：$\prod\limits_{j=1}^{k_i}p_{i,j}^{c_{i,j}}$。

给定一个序列 $a$，长度为 $n$。

定义 $f(x)=\sum\limits_{d|x}\left({a_{\frac{x}{d}}\times\prod\limits_{i=1}^{k_d}{C_{c_{d,i}+m}^{m}}}\right)$，现在需要你求出 $f(1),f(2),f(3),\cdots ,f(n)$，其中 $m$ 是给定常数。

由于 monsters 不喜欢太大的数，他需要你输出答案模 $998244353$ 的值。

另外，为了避免过大的输入输出量，本题使用随机数生成数据，并且只需要你输出所有答案的异或和。

如果你不知道 $C$ 是什么，$C_n^m=\dfrac{n!}{m!(n-m)!}$，其中 $!$ 代表阶乘。

## 说明/提示

**数据生成器**

C/C++:
```cpp
#define uint unsigned int
uint seed;
inline uint randomdigit(){
	seed^=seed<<13;
	seed^=seed>>17;
	seed^=seed<<5;
	return seed;
}
```
pascal:
```pascal
var seed:dword;
function randomdigit:dword;
begin
	seed:=seed xor(seed shl 13);
	seed:=seed xor(seed shr 17);
	seed:=seed xor(seed shl 5);
	randomdigit:=seed;
end;
```

python3:
```python
seed = 0 # please input seed
mod = 1 << 32
def randomdigit():
    global seed
    seed ^= (seed << 13) % mod
    seed ^= (seed >> 17) % mod
    seed ^= (seed << 5) % mod
    return seed
```

---

**样例解释**

序列 $a$ 为 $506005380,3857352168,531380003$。

$f(1),f(2),f(3)$ 模 $998244353$ 的值分别为 $506005380,370380136,39141030$。

---

**数据范围**

对于 $100\%$ 的数据，$0\le m\le 10^5,1\le n\le 10^7,0\le a_1,a_2,\cdots,a_n,seed<2^{32}$。

- Subtask $1$（$30\%$ 的数据）：$n\le 10^6,m\le 10^5$。

在此 Subtask 中：

有 $10\%$ 的数据，满足 $m=0$。

另有 $10\%$ 的数据，满足 $n\le 100$。
- Subtask $2$（剩下 $70\%$ 的数据）：$n\le 10^7,m\le 3$。

**提示**

请注意空间限制和常数因子对程序运行效率的影响

## 样例 #1

### 输入

```
3 0 12345678```

### 输出

```
175092810```

## 样例 #2

### 输入

```
114514 100000 1919810```

### 输出

```
212218651
```

## 样例 #3

### 输入

```
9919810 2 12121121```

### 输出

```
204065242```

# 题解

## 作者：Prean (赞：12)

设：
$$ g(x)=\prod_{i=1}^{k_i}\binom {m} {c_{d,i}+m} $$
那么很明显有：
$$ f= a * g $$
再看一眼 $ g $，我们发现 $ g $ 是积性函数。

使用[P5495](https://www.luogu.com.cn/problem/P5495)的办法即可做到 $ O(m+n\log \log n) $，轻松通过此题。
```cpp
#include<cstdio>
const int M=1e7+5,mod=998244353;
typedef unsigned uint;
int n,m,top,f[24],g[M],pri[M],C[M];uint ans,b[M],a[M];
int fac[M],ifac[M];bool zhi[M];
uint seed;
inline int Add(const int&a,const int&b){
    return a+b>=mod?a+b-mod:a+b;
}
inline uint randomdigit(){
    seed^=seed<<13;
    seed^=seed>>17;
    seed^=seed<<5;
    return seed;
}
signed main(){
    register int i,j,x;
    scanf("%d%d%u",&n,&m,&seed);
    a[1]=randomdigit()%mod;
    fac[0]=ifac[0]=fac[1]=ifac[1]=1;
	fac[2]=2;ifac[2]=499122177;
	for(i=3;i<=m+24;++i){
		fac[i]=1ll*fac[i-1]*i%mod;
		ifac[i]=1ll*(mod-mod/i)*ifac[mod%i]%mod;
	}
	for(i=1;i<=m+24;++i)ifac[i]=1ll*ifac[i]*ifac[i-1]%mod;
    for(i=0;i<24;++i){
        f[i]=1ll*ifac[i]*ifac[m]%mod*fac[i+m]%mod;
    }
    for(i=2;i<=n;++i){
        a[i]=randomdigit()%mod;
        if(!zhi[i])pri[++top]=i;
        for(j=1;j<=top&&(x=i*pri[j])<=n;++j){
            zhi[x]=1;if(!(i%pri[j]))break;
        }
    }
    for(i=1;i<=top;++i){
        for(j=n/pri[i];j;--j){
        	for(long long x,k=pri[i],cnt=1;(x=j*k)<=n;++cnt,k*=pri[i]){
                a[x]=Add(a[x],1ll*a[j]*f[cnt]%mod);
            }
        }
    }
    for(i=1;i<=n;++i)ans^=a[i];
    printf("%u",ans);
}
```

---

## 作者：monstersqwq (赞：6)

Subtask 1：

随便打打就完了 估计是 $O(n\log n)$ 级别的，反正咋都能过。

Subtask 2：

$f(x)=\sum\limits_{d|x}{a_{\frac{x}{d}}\times\prod\limits_{i=1}^{k_d}{C_{c_{d,i}+m}^{m}}}$

$=\sum\limits_{d|x}{a_{\frac{x}{d}}\times\prod\limits_{i=1}^{k_d}{C_{c_{d,i}+m}^{c_{d,i}}}}$

最后的那坨显然是插板法的结果，化成在 $c_{d,i}+m+1$ 个 $1$ 中插 $m$ 个板，版不能重合，分成 $m+1$ 段的方案数。

前面的 $m$ 似乎没啥关系，我们把每段 $-1$，即把 $c_{d,i}$ 分成 $m+1$ 段的方案数，每段可以等于 $0$。

考虑再转化一步，是一个长度为 $m+2$ 段的非严格递增序列满足第一个数是 $0$ 且最后一个数是 $c_{d,i}$ 的方案数。

把那个乘积整体考虑，得到是一个长度为 $m+2$ 的序列满足后一个数是前一个数的倍数（可以相等）且第一个数是 $1$ 最后一个数是 $d$ 的方案数。

这似乎是在统计 $a_{\frac{x}{d}}$ 对答案的贡献，发现它是每次都取 当前数的一个因数（一开始当前数是 $x$），取 $m+1$ 次后恰好取到 $\dfrac{x}{d}$ 的方案数。

到这里应该比较明显了，这是一个 Dirichlet 前缀和，做 $m+1$次，就有了 $f$ 所有的取值。

复杂度 $O(mn\log \log n)$。

然后你会发现这么写过不了，至少是比较卡。

可以在取模的时候加一个优化，在读入的时候取模，剩下的因为全是加，可以先加，如果大于等于 mod 就减掉。

[代码](https://www.luogu.com.cn/paste/vxucs527)

~~说句闲话 因为有简单的 $O(m+n\log\log n)$ 的做法，出题人发现这题实际上应该出成做 $m$ 次上述前缀和~~

---

